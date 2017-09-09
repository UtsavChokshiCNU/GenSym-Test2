;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; if.lsp -- handling for IF, COND, other conditionals
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  29 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;
;;; Most of the conditional constructs whose handlers appear in this
;;; file are treated in a similar way.  Generally, there is a "simple"
;;; C construct that can be applied in value-returning contexts where there
;;; are no side-effect statements, and a "hard" expansion that always
;;; succeeds but that is more verbose and involves using temporary 
;;; variables.  The problem is that we would like to use the "simple"
;;; construct but we can't tell whether it is safe to do so without
;;; walking subforms.  So the approach taken is to try the simple version
;;; first, and if it fails to start over and re-walk the forms for the
;;; hard case.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/if.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/07/10 16:57:57 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Handling for IF
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; IF can turn into either an if-statement or a conditional-operator.
;;; The only situation in which it can turn into a conditional-operator
;;; is in a value-returning context (:value, :predicate, or l-value)
;;; when there are no side-effect statements from either the "then"
;;; or "else" clauses.  Otherwise, turn it into an if-statement.

(deftranslate if (&whole form test then &optional else &rest more-elses)
  (if more-elses
      ;; Symbolics Common Lisp accepts this, but we don't.
      (error "IF statement contains multiple ELSE clauses.~
	    ~%This is not legal Common Lisp syntax.~
	    ~%~S" form)
      (if (and (side-effecting-context-p *context*)
	       (not (lvalue-context-p *context*)))
	  (do-if-statement test then else *context* *result-type*)
	  (multiple-value-bind (success-p statements value type temps)
	      (do-if-expression test then else *result-type*)
	    (cond (success-p
		   (values statements value type temps))
		  ((lvalue-context-p *context*)
		   (do-if-statement test then else *context* *result-type*))
		  (t
		   (with-temporary-for-value context
		     (do-if-statement test then else context
				      *result-type*))))))))


;;; A helper function:  walk the test in a :predicate context and return
;;; an unboxed result.

(defun walk-the-test (test)
  (unless (eq *context* ':result-type-only)
    (multiple-value-bind (test-statements test-value test-type test-temps)
	(multiple-value-call #'expression-ize
	  (translate-form test *environment* *predicate-context*))
      (setq test-value (coerce-to-pseudo-boolean test-value))
      (values test-statements test-value test-type test-temps))))

;;; Transform a target form into a form that has value 0 or non-zero,
;;; as appropriate, but may be of either C type int or C type Object.
;;; This can only be used in contexts where C doesn't care about
;;; the type, such as the test of an if, for, or while, or within
;;; an and or or expression.

(defun coerce-to-pseudo-boolean (expression)
  (if *nil-is-zero*
      (let ((new-expression (discard-box-unbox expression)))
	(if (and (eq (target-form-type new-expression) 'macro-call)
		 (eq 'trun:%not
		     (let ((name (cadr new-expression)))
		       (if (environment-entry-p name)
			   (environment-entry-name name)
			   name))))
	    (make-target-form 'not-operator (third new-expression))
	    new-expression))
      ;; Should add code here to transform TRUEP(NOT(foo))
      ;; to foo == NIL when nil is not zero.
      expression))
			  
;;; Here's the simple case.  The only hair is for handling the four
;;; permutations of the presence of THEN and ELSE statements.
;;; Note that this function is *never* called with :value or :predicate
;;; contexts -- the caller is careful to allocate a temporary so that
;;; both branches of the IF put the result in the same place.

(defun do-if-statement (test then else context result-type)
  (multiple-value-bind (then-statements then-value then-type then-temps)
      (translate-form then *environment* context result-type)
    (multiple-value-bind (else-statements else-value else-type else-temps)
	(translate-form else *environment* context result-type)
      (merge-error-check then-value else-value 'if context)
      (let ((result-type (or-value-types then-type else-type *environment*)))
	(cond ((eq *context* ':result-type-only)
	       (values nil nil result-type nil))
	      ((not (or then-statements else-statements))
	       (translate-form test *environment* *ignore-context*))
	      (t
	       (multiple-value-bind (test-statements
				     test-value test-type test-temps)
		   (walk-the-test test)
		 (declare (ignore test-type))
		 (cond ((and then-statements else-statements)
			(values (cons (make-target-form
				       'if-statement test-value
				       (one-statement then-statements)
				       (one-statement else-statements))
				      test-statements)
				then-value
				result-type
				(append test-temps then-temps else-temps)))
		       (then-statements
			(values (cons (make-target-form
				       'if-statement test-value
				       (one-statement then-statements))
				      test-statements)
				then-value
				result-type
				(append test-temps then-temps)))
		       (else-statements
			(values (cons (make-target-form
				       'if-statement
				       (negate test-value)
				       (one-statement else-statements))
				      test-statements)
				else-value
				result-type
				(append test-temps else-temps)))))))))))


;;; Here's the hard case.  Give up and return NIL if either of the
;;; "then" or "else" forms involves side-effect statements.
;;; If the context is an l-value, instead of propagating it to the
;;; then/else forms, walk them in an ordinary :value context and then
;;; do the assignment to the result of the conditional expression.

;(success-p statements value type temps)
(defun do-if-expression (test then else result-type)
  (with-statements-excluded
    (do-if-expression-1 test then else result-type)))

(defun do-if-expression-1 (test then else result-type)
  (let ((context (if (lvalue-context-p *context*)
		     (lvalue-context-foreign-type *context*)
		     *context*)))
    (multiple-value-bind (then-statements
			  then-value then-type then-temps)
	(multiple-value-call #'comma-ize
	  (translate-form then *environment* context result-type))
      (if then-statements
	  (values nil nil nil nil)
	  (multiple-value-bind (else-statements
				else-value else-type else-temps)
	      (multiple-value-call #'comma-ize
		(translate-form else *environment* context result-type))
	    (if else-statements
		(values nil nil nil nil)
		(with-statements-allowed
		  (multiple-value-bind (test-statements
					 test-value test-type test-temps)
		      (walk-the-test test)
		    (declare (ignore test-type))
		    (multiple-value-bind (statements value type temps)
			(handle-context
			  test-statements
			  (make-target-form 'conditional-operator
					    test-value
					    then-value
					    else-value)
			  (or-value-types then-type else-type *environment*)
			  (append test-temps then-temps else-temps))
		      (values t statements value type temps))))))))))

;;; A helper function: combine "statements" into a compound statement
;;; if necessary.

(defun one-statement (statements)
  (cond ((null statements)
	 (make-target-form 'null-statement))
	((cdr statements)
	 (apply-make-target-form
		'compound-statement (nreverse statements)))
	(t
	 (car statements))))


;;; Another helper:  Check to make sure that all branches of a conditional
;;; put the result in the same place.

(defun merge-error-check (value1 value2 signaller &optional
				 (context *context*))
  (unless (cond ((lvalue-context-p context)
		 (target-form-equal value1 value2))
		((value-context-p context)
		 t) ; should fix this
		(t
		 t))
    (error "Merge error in ~s: ~s ~s" signaller value1 value2)))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Handling for COND
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; COND generally turns into an if/else if/else series, instead of into
;;; a conditional operator expression.  The reason for this is that
;;; long chains of conditional operators are ugly looking and hard to
;;; read.  Treat a cond with only one or two clauses like IF, though,
;;; if both clauses have consequents (else a temp is still needed).

(deftranslate cond (&rest cases)
  (cond ((null cases)
	 (translate-constant nil))
	((and (null (cdr cases))
	      (cdr (car cases)))
	 (re-translate-form
	  `(if ,(car (car cases)) (progn ,@(cdr (car cases))))))
	((and (null (cddr cases))
	      (eq (car (cadr cases)) 't)
	      (cdr (car cases))
	      (cdr (cadr cases)))
	 (re-translate-form
	  `(if ,(car (car cases))
	       (progn ,@(cdr (car cases)))
	       (progn ,@(cdr (cadr cases))))))
	((value-context-p *context*)
	 (let ((temp (make-symbol "TEMP"))
	       (type (translator-foreign-type-lisp-type
		      (context-foreign-type *context*))))
	   (re-translate-form
	    `(let ((,temp (cond ,@cases)))
	       (declare (type ,type ,temp))
	       ,temp))))
	(t
	 (translate-cond-aux cases))))


;;; This function is also never called with a :value or :predicate
;;; context.  COND is actually pretty straightforward except for dealing
;;; with singleton clauses, where the form provides both a test and a
;;; return value.
;;; Note that there isn't a final "else" clause unless the COND includes
;;; an explicit "T" test as its final clause, or unless it's necessary to
;;; establish a return value.

(defun translate-cond-aux (cases)
  (cond ((eq *context* ':result-type-only)
	 (values nil nil
		 (if (null cases)
		     'null
		     (reduce #'or-value-types
			     (mapcar #'(lambda (case)
					 (get-result-type
					  (if (cdr case)
					      `(values ,(car case))
					      `(progn ,@case))))
				     cases)))))
	((null cases)
	 (translate-constant nil))
	((and (null (cdr cases)) (eq (car (car cases)) t))
	 (if (cdr (car cases))
	     (translate-progn-body
	       (cdr (car cases)) *environment* *context* nil *result-type*)
	     (translate-constant t)))
	((or (cdr (car cases)) (eq *context* *ignore-context*))
	 (multiple-value-call #'do-cond-aux
	   (cdr cases)
	   (multiple-value-call #'expression-ize
	     (translate-form (car (car cases)) *environment*
			     *predicate-context*))
	   (translate-progn-body
	    (cdr (car cases)) *environment* *context* nil *result-type*)))
	((lvalue-context-p *context*)  ; singleton clause in l-value context
	 (multiple-value-call #'do-cond-singleton-clause
	   (multiple-value-call #'expression-ize
	     (translate-form (car (car cases)) *environment* *context*))
	   *context* (cdr cases)))
	(t  ; singleton clause in :values or :return context
	 (with-temporary-for-value context
	   (multiple-value-call #'do-cond-singleton-clause
	     (translate-form (car (car cases)) *environment* context)
	     context (cdr cases))))))


(defun do-cond-aux (cases test-statements test-value test-type test-temps
			  then-statements then-value then-type then-temps)
  (declare (ignore test-type))
  (setq test-value (coerce-to-pseudo-boolean test-value))
  (if (or cases (not (eq *context* *ignore-context*)))
      (multiple-value-bind (else-statements else-value else-type else-temps)
	  (translate-cond-aux cases)
	(merge-error-check then-value else-value 'cond)
	(values (unless (eq *context* ':result-type-only)
		  (cons (make-target-form 'if-statement
					  test-value
					  (one-statement then-statements)
					  (one-statement else-statements))
			test-statements))
		then-value
		(or-value-types then-type else-type *environment*)
		(append test-temps then-temps else-temps)))
      (values (unless (eq *context* ':result-type-only)
		(cons (make-target-form 'if-statement
					test-value
					(one-statement then-statements))
		      test-statements))
	      then-value
	      then-type
	      then-temps)))


(defun do-cond-singleton-clause (test-statements
				 test-value test-type test-temps
				 value cases)
  (multiple-value-bind (then-statements then-value then-type then-temps)
      (handle-context nil value test-type nil)
    (do-cond-aux cases
                 test-statements test-value test-type test-temps
		 then-statements then-value then-type then-temps)))


;;; These two guys are really easy!

(define-translator-macro when (test &body forms)
  (if forms
      `(if ,test (progn ,@forms))
      `(progn ,test nil)))

(define-translator-macro unless (test &body forms)
  (if forms
      `(if (not ,test) (progn ,@forms))
      `(progn ,test nil)))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    CASE, TYPECASE, and friends
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; CASE is a macro that expands into a COND.
;;; It doesn't expand into a C "switch" statement because of the limitations
;;; on what the case labels can be -- even if they are constants in Lisp,
;;; the C switch accepts only int constants.

(defun lisp-type->case-foreign-type (type)
  (lisp-type->foreign-type-cond type
   :signed-8bit
   :unsigned-8bit
   :signed-16bit
   :unsigned-16bit
   :signed-32bit
   :unsigned-32bit
   :signed-64bit
   :unsigned-64bit))

(define-translator-macro case (keyform &rest clauses &environment env)
  (let* ((otherwise-p nil)
	 (all-keys (mapcan #'(lambda (clause)
			       (let ((keylist (car clause)))
				 (cond ((listp keylist)
					(copy-list keylist))
				       ((or (eq keylist 't)
					    (eq keylist 'otherwise))
					(setq otherwise-p t)
					nil)
				       (t
					(list keylist)))))
			   clauses))
	 foreign-type (max nil) (min nil))
    (cond ((null all-keys)
	   (case-internal keyform clauses env))
	  ((every #'characterp all-keys)
	   `(switch ,keyform ,(translator-foreign-type ':char)
		    ,@clauses
		    ,@(unless otherwise-p `((t nil)))))
	  ((dolist (key all-keys
		    (setq foreign-type
			  (lisp-type->case-foreign-type `(integer ,min ,max))))
	     (unless (integerp key) (return nil))
	     (if max
		 (setq max (max max key)
		       min (min min key))
		 (setq max key
		       min key)))
	   `(switch ,keyform ,foreign-type
		    ,@clauses
		    ,@(unless otherwise-p `((t nil)))))
	  (t
	   (case-internal keyform clauses env)))))

(defun case-internal (keyform clauses env)
  (let ((transform (apply-macros keyform env)))
    (if (or (symbolp transform)
	    (translator-constantp transform env))
	`(cond ,@(expand-case transform clauses nil nil))
	(let ((temp (make-symbol "TEMP")))
	  `(let ((,temp ,keyform))
	     (cond ,@(expand-case temp clauses nil nil)))))))

(defun make-labels (labels statement)
  (if (null labels)
      statement
      (make-target-form 'labeled-statement
			(car labels)
			(make-labels (cdr labels) statement))))

(deftranslate switch (key foreign-type &rest clauses)
  (cond ((eq *context* ':result-type-only)
	 (values nil nil
		 (if (null clauses)
		     'null
		     (reduce #'(lambda (t1 t2)
				 (or-value-types t1 t2 *environment*))
			     (mapcar #'(lambda (clause)
					 (get-result-type
					  `(progn ,@(cdr clause))))
				     clauses)))))
	((value-context-p *context*)
	 (let ((temp (make-symbol "TEMP"))
	       (type (lisp-type (context-foreign-type *context*))))
	   (re-translate-form
	    `(let ((,temp (switch ,key ,foreign-type ,@clauses)))
	       (declare (type ,type ,temp))
	       ,temp))))
	(t
	 (let ((key-type (get-first-result-type key))
	       (type (lisp-type foreign-type)))
	   (if (translator-subtypep key-type type)
	       (translate-switch key foreign-type clauses)
	       (re-translate-form
		(once-only* (key) *environment*
	          `(if (not (tcl:typep (the ,key-type ,key) ',type))
		       (progn
			 ,@(cdr (or (assoc 't clauses)
				    (assoc 'otherwise clauses))))
		       (switch (the ,type ,key) ,foreign-type ,@clauses)))))))))

(defun translate-switch (key foreign-type clauses)
  (multiple-value-bind (key-statements key-value key-type key-temps)
      (translate-form key *environment* foreign-type)
    (declare (ignore key-type))
    (let ((swich-statement
	   (make-target-form
	    'switch
	    key-value
	    (apply-make-target-form
	     'compound-statement
	     (mapcan #'(lambda (clause)
			 (let* ((body-statements
				 (translate-progn-body
				  (cdr clause) *environment*
				  *context* nil))
				(statements
				 (if (eq *context* ':return)
				     (nreverse body-statements)
				     (nreconc
				      body-statements
				      (list (make-target-form
					     'break-statement 0))))))
			   (cons (make-labels
				  (let ((keylist (car clause)))
				    (if (or (eq keylist 't)
					    (eq keylist 'otherwise))
					(list :default)
					(if (listp keylist)
					    keylist
					    (list keylist))))
				  (or (car statements)
				      (make-target-form 'null-statement)))
				 (cdr statements))))
		     clauses)))))
      (values (cons swich-statement key-statements)
	      (if (lvalue-context-p *context*)
		  *context*
		  (translate-constant-aux 'nil))
	      (if (lvalue-context-p *context*)
		  (lisp-type (context-foreign-type *context*))
		  'null)
	      key-temps))))


;;; TYPECASE is similar.

(define-translator-macro typecase (keyform &rest clauses &environment env)
  (let ((transform  (apply-macros keyform env)))
    (if (or (symbolp transform)
	    (translator-constantp transform env))
	`(cond ,@(expand-case transform clauses nil t))
	(let ((temp (make-symbol "TEMP")))
	  `(let ((,temp ,keyform))
	     (cond ,@(expand-case temp clauses nil t)))))))


;;; Helper functions for CASE and TYPECASE.

(defun expand-case (keyform clauses t-p typecase-p)
  (cond ((null clauses)
	 nil)
	((or (eq (car (car clauses)) 't) (eq (car (car clauses)) 'otherwise))
	 (if t-p
	     (error "Multiple T or OTHERWISE clauses in ~s."
		    (if typecase-p 'typecase 'case)))
	 (cons `(t (progn ,@(cdr (car clauses))))
	       (expand-case keyform (cdr clauses) t typecase-p)))
	((or typecase-p (not (consp (car (car clauses)))))
	 (cons `(,(make-case-test keyform (car (car clauses)) typecase-p)
		  (progn ,@(cdr (car clauses))))
	       (expand-case keyform (cdr clauses) t-p typecase-p)))
	(t
	 (cons `(,(make-case-tests keyform (car (car clauses)) typecase-p)
		  (progn ,@(cdr (car clauses))))
	       (expand-case keyform (cdr clauses) t-p typecase-p)))))

;;; This is generally naive about doing things like transforming EQL tests
;;; into EQ test, or the MEMBER test into a bunch of ORs.  These are better
;;; done as general optimizations on EQL or MEMBER.

(defun make-case-test (keyform constant typecase-p)
  (if typecase-p
      `(tcl:typep ,keyform ',constant)
      `(eql ,keyform ',constant)))

(defun make-case-tests (keyform constants typecase-p)
  (cond ((null constants)
	 nil)
	((null (cdr constants))
	 (make-case-test keyform (car constants) typecase-p))
	(t
	 `(member ,keyform ',constants))))



;;;*** Remember to do ECASE, CCASE, ETYPECASE, CTYPECASE at some point.
;;; These are alive and well and living in emacros.lisp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    AND
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; The general approach with AND is similar to that for IF.  If we're
;;; in a :value, :predicate, or l-value context we would like to
;;; get an AND-EXPRESSION expression if possible.  If this fails, then
;;; the AND has to be turned into a series of nested IFs,
;;; like
;;;     (and exp1 exp2 exp3) =>
;;;     (if exp1
;;;         (if exp2
;;;             exp3
;;;             nil)
;;;         nil)


(deftranslate and (&rest forms)
  (cond ((eq *context* ':result-type-only)
	 (values nil nil '(values &rest t))) ; not right, but safe.
	((null forms)
	 (translate-constant t))
	((null (cdr forms))
	 (re-translate-form (car forms)))
	((and (side-effecting-context-p *context*)
	      (not (lvalue-context-p *context*)))
	 (do-and-aux forms))
	(t
	 (multiple-value-bind (success-p statements value type temps)
	     (do-and-expression forms nil nil nil)
	   (if success-p
	       (values statements value type temps)
	       (do-and-aux forms))))))


;;; Recursively decompose the AND into a chain of IFs.  Instead of
;;; going with an all-or-nothing approach, unwind the nested forms
;;; one by one from the end and try again at each step.

(defun do-and-aux (forms)
  (re-translate-form
   `(if (and ,@(butlast forms))
	,(car (last forms))
	nil)))



;;; Try turning the AND form into a C && expression.  If any of the subforms
;;; other than the first expand into side-effect statements, report failure.
;;; Walk all but the last form in a :predicate context.  The default
;;; context is propagated to the last form unless it is an lvalue context,
;;; in which case we walk it in a :value context and move the assignment
;;; outside (in the same way that conditional expressions are handled for
;;; IF).

;(success-p statements value type temps)
(defun do-and-expression (forms init-statements tests temps)
  (with-statements-excluded
    (do-and-expression-1 forms init-statements tests temps)))

(defun do-and-expression-1 (forms init-statements tests temps)
  (if (cdr forms)
      (multiple-value-bind (statements value type new-temps)
	  (multiple-value-call #'comma-ize
	    (translate-form (car forms) *environment* *predicate-context*)
	    (eq *context* *ignore-context*))
	(declare (ignore type))
	(when (and statements tests)
	  (return-from do-and-expression-1 (values nil nil nil nil)))
	(setq value (coerce-to-pseudo-boolean value))
	(do-and-expression (cdr forms) (or statements init-statements)
			   (cons value tests) (append new-temps temps)))
      (let ((context (if (lvalue-context-p *context*)
			 (lvalue-context-foreign-type *context*)
			 *context*)))
	(multiple-value-bind (statements value type new-temps)
	    (multiple-value-call #'comma-ize
	      (translate-form (car forms) *environment* context)
	      (eq *context* *ignore-context*))
	  (if statements
	      (values nil nil nil nil)
	      (make-and-expression value context type init-statements tests
				   (append new-temps temps)))))))

;;; Make an "and" expression.  If we are in a :predicate context,
;;; use the C && operator and the whole expression returns an unboxed
;;; boolean.  If we are in a value-returning context, turn
;;;     (and <exp1> <exp2> ... <expn>) 
;;; into
;;;     (<exp1> && <exp2> ...) ? <expn> : nil)
;;; Note that the argument "value" is tagged but each of the "tests" 
;;; is an untagged boolean.

(defun make-and-expression (value context type init-statements tests temps)
  (multiple-value-bind (statements value type temps)
      (handle-context
       init-statements
       (unless (eq *context* ':result-type-only)
	 (if (eq *context* *predicate-context*)
	     (apply-make-target-form
	      'and-expression
	      (append (nreverse tests)
		      (list (coerce-to-pseudo-boolean value))))
	     (make-target-form
	      'conditional-operator
	      (if (cdr tests)
		  (apply-make-target-form
		   'and-expression
		   (nreverse tests))
		  (car tests))
	      value
	      (let ((*context* context))
		(multiple-value-bind (statements value)
		    (translate-constant nil)
		  (declare (ignore statements))
		  value)))))
       (or-value-types type 'null *environment*)
       temps)
    (values t statements value type temps)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    OR
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Handling for OR is quite similar to that for AND.  The major difference
;;; is that the nonterminating forms in the list can propagate their
;;; return value, which tends to make the details of things a lot more hairy.
;;; In particular, since each of the intermediate forms can return a
;;; value as well as being tested in a predicate situation, we have to
;;; watch out for using the inline C || operator which operates on and
;;; returns untagged C booleans.

(defmacro with-temporary-for-value--or (new-context &body forms)
  (let* ((temp (make-symbol "TEMP"))
	 (ft (make-symbol "FT"))
	 (tft (make-symbol "TFT")))
    `(let* ((,ft (context-foreign-type *context*))
	    (,tft (if (eq ,ft (translator-foreign-type :boolean))
		      ,ft
		      (translator-foreign-type :object)))
	    (,temp (allocate-temporary ,tft))
	    (,new-context (make-target-form 'local-variable ,temp)))
       (multiple-value-bind (statements value type temps)
	   (progn ,@forms)
	 (values statements value type (cons ,temp temps) ,tft)))))

(deftranslate or (&rest forms)
  (cond ((eq *context* ':result-type-only)
	 (values nil nil '(values &rest t) nil)) ; not right, but safe.
	((null forms)
	 (translate-constant nil))
	((null (cdr forms))
	 (re-translate-form (car forms)))
	((eq *context* *predicate-context*)
	 ;; In a predicate context, first try to make an OR-EXPRESSION.
	 ;; If that fails, bind a temporary and make a chain of
	 ;; IF-STATEMENTs.  Use the temporary as the context for the
	 ;; "then" and "else" parts of the IF-STATEMENT as well as the test.
	 (multiple-value-bind (success-p statements value type temps)
	     (do-or-expression forms nil nil 'null nil)
	   (if success-p
	       (values statements value type temps)
	       (with-temporary-for-value context
		 (do-or-aux forms context context)))))
	((and (temporary-context-p *context* *environment*)
	      (let ((ft (context-foreign-type *context*)))
		(or (eq ft (translator-foreign-type :boolean))
		    (eq ft (translator-foreign-type :object)))))
	 ;; If the context is a temporary, re-use it.  First try making
	 ;; an OR-EXPRESSION (as we did for :predicate) and if that fails
	 ;; make an IF-STATEMENT.
	 ;; The reason why we don't just use lvalue-context-p here is
	 ;; because of an order-of-evaluation problem; since the value of
	 ;; each of the subforms is written into the lvalue in sequence,
	 ;; we have to make that lvalue is not referenced by any of the
	 ;; subsequent subform evaluations.
	 (multiple-value-bind (success-p statements value type temps)
	     (do-or-expression forms nil nil 'null nil)
	   (if success-p
	       (values statements value type temps)
	       (do-or-aux forms *context* *context*))))
	((or (value-context-p *context*)
	     (lvalue-context-p *context*))
	 ;; We've got some other kind of value-producing context.  Make
	 ;; a temporary and reduce to the temporary-context-p case.
	 (multiple-value-call #'handle-context
	   (with-temporary-for-value--or context
	     (translate-form `(or ,@forms) *environment* context))))
	((eq *context* *ignore-context*)
	 ;; In an :ignore context, we can simplify the form to walking
	 ;; an OR in a :predicate context and maybe avoid having to
	 ;; allocate a temp.
	 (re-translate-form
	  `(if (not (or ,@(butlast forms))) ,(car (last forms)))))
	(t
	 ;; Otherwise it's a :values or :return context.  Make a chain
	 ;; of IF-STATEMENTs.  We need a temporary for the "test" part
	 ;; of the IF-STATEMENT, but *context* is propagated to the
	 ;; "then" and "else" parts.
	 (with-temporary-for-value context
	   (do-or-aux forms context *context*)))))
	   

;;; Recursively decompose an OR into a chain of IF-STATEMENTS.  This is
;;; similar to handling for AND, but since the subforms might be used
;;; both as predicate tests and as values, things are more complicated
;;; and we have to do things directly with target language instead of
;;; relying strictly on a source-to-source transformation.

(defun do-or-aux (forms test-context context)
  (let ((test-form   `(or ,@(butlast forms)))
	(else-form   (car (last forms))))
    (multiple-value-bind (test-statements test-value test-type test-temps)
	(translate-form test-form *environment* test-context)
      (multiple-value-bind (then-statements then-value then-type then-temps)
	  (let ((*context* context))
	    (handle-context nil test-value test-type nil))
	(multiple-value-bind (else-statements else-value else-type)
	    (translate-form else-form *environment* context)
	  (merge-error-check then-value else-value 'OR context)
	  (values (unless (eq *context* ':result-type-only)
		    (cons (make-target-form
			   'if-statement
			   (coerce-to-pseudo-boolean test-value)
			   (one-statement then-statements)
			   (one-statement else-statements))
			  test-statements))
		  then-value
		  (or-value-types then-type else-type *environment*)
		  (append then-temps test-temps)))))))


;;; This predicate returns true if the context is an l-value referring 
;;; to a variable that is not lexically bound in the environment env.
;;; It is used as a quick check to determine that no form walked in env 
;;; can possibly reference the value of the l-value.  

(defun temporary-context-p (context env)
  (and (lvalue-context-p context)
       (eq (target-form-type context) 'local-variable)
       (not (translator-variable-information
	     (variable-record-name (cadr context)) env))))



;;; And here's the code for trying to produce an expression.  This only
;;; gets called when *context* is :predicate (all of the subforms are 
;;; being evaluated strictly for their truth/falsity values) or an l-value
;;; which refers to a temporary.  Note that since the *context* is inherited
;;; by the subforms, if it's an l-value context then that l-value will
;;; contain the result of the OR.  In other words,
;;; (setq temp (or exp1 exp2 ... expn)) =>
;;; (Truep(temp=exp1) || Truep(temp=exp2) ... || Truep(temp=exp3))

;(success-p statements value type temps)
(defun do-or-expression (forms init-statements tests result-type temps)
  (with-statements-excluded
    (do-or-expression-1 forms init-statements tests result-type temps)))

(defun do-or-expression-1 (forms init-statements tests result-type temps)
  (multiple-value-bind (statements value type new-temps)
      (multiple-value-call #'comma-ize
	(translate-form (car forms) *environment* *context*)
	(eq *context* *ignore-context*))
    (when (and statements (or (null (cdr forms)) tests))
      (return-from do-or-expression-1 (values nil nil nil nil nil)))
    (setq value (coerce-to-pseudo-boolean value))
    (if (cdr forms)
	(do-or-expression (cdr forms) (or statements init-statements)
			  (cons value tests)
			  (or-value-types type result-type *environment*)
			  (append temps new-temps))
	(make-or-expression value type init-statements tests
			    result-type (append temps new-temps)))))

;;; The value and all of the tests received as arguments are untagged 
;;; :booleans.  Remember that *context* is either :predicate or an l-value.

(defun make-or-expression (value type init-statements tests result-type temps)
  (if (eq *context* *predicate-context*)
      (multiple-value-bind (statements value type temps)
	  (handle-context init-statements
			  (apply-make-target-form
			   'or-expression
			   (nreverse (cons value tests)))
			  (or-value-types type result-type *environment*)
			  temps)
	(values t statements value type temps))
      (progn
	(values
	 t
	 (push (apply-make-target-form
		'or-expression
		(nreverse (cons value tests)))
	       init-statements)
	 *context*
	 (or-value-types type result-type *environment*)
	 temps))))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Handling for NOT
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; NULL gets transformed into NOT via a source-to-source.  So we
;;; only need to treat NOT specially here.

;;; Note that this depends on the fact that coerce-from-c-type :boolean will
;;; still work correctly if given an Object instead of a boolean when nil = 0.

;;; Now that NOT returns a boolean, this can be handled by a transform
;;; instead of a special form.

#|
(deftranslate not (form)
  (multiple-value-bind (statements value)
      (translate-form form *environment* *predicate-context*)
    (setq value (negate (coerce-to-pseudo-boolean value)))
    (handle-context
     statements
     (coerce-from-c-type (translator-foreign-type :boolean) value)
     'symbol)))
|#


;;; Negate a C boolean, returning another C boolean.  Look for some
;;; obvious simplifications.

;;; negate may also be passed a pseudo C boolean (A value that is zero or
;;; non-zero, as apppropriate). It will then return another pseudo C boolean.

;;; "Real" (type int) boolean in, "real" boolean out.

(defun negate (expression)
  (let ((operator (target-form-type expression)))
    (cond ((eq operator 'not-operator)
	   (cadr expression))
	  ((and (eq operator 'unbox-value)
		(eq (cadr expression) (translator-foreign-type :boolean)))
	   (make-target-form 'macro-call 'trun:%not (caddr expression)))
	  ((and (eq operator 'macro-call)
		(eq (cadr expression) 'not))
	   (make-target-form 'unbox-value (translator-foreign-type :boolean)
			     (caddr expression)))
	  (t
	   (let ((args (cdr expression)))
	     (case operator
	       (==-operator (make-target-form '!=-operator args))
	       (!=-operator (make-target-form '==-operator args))
	       (<-operator  (make-target-form '>=-operator args))
	       (>-operator  (make-target-form '<=-operator args))
	       (<=-operator (make-target-form '>-operator args))
	       (>=-operator (make-target-form '<-operator args))
	       (t (make-target-form 'not-operator expression))))))))


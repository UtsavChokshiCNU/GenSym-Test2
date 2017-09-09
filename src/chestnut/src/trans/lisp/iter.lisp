;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; iter.lisp -- various iteration macros
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  02 Jul 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/iter.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:07 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    high-level iteration constructs
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#|| ; See loop.lisp
;;; This is the simple version of loop.
;;; It contains a hook to look for a host definition if the
;;; call uses CLtL2 LOOP; however, note that it punts the environment,
;;; so any macroexpansion which LOOP itself performs which relies
;;; on surrounding macrolet's, for example, will break.
;;; This is an interim solution until we provide a "native" definition.

(define-translator-macro loop (&whole form &body body)
  (if (member-if #'atom body)
      (if (macro-function 'loop)
	  (macroexpand-1 form)
	  (error "Only the simple version of LOOP is supported now."))
      `(block nil (forever ,@body))))
||#

;;; DO and DO* make use of a common helper function.
;;; If we're in a context where a value is returned (as opposed to a
;;; side-effecting context), allocate a temporary now to store the
;;; value in.

(deftranslate do (step-clauses end-test-clause &body body)
  (do-do step-clauses end-test-clause body 'do 'let 'psetq))

(deftranslate do* (step-clauses end-test-clause &body body)
  (do-do step-clauses end-test-clause body 'do* 'let* 'setq))

(defun do-do (step-clauses end-test-clause body doer binder setter)
  (cond ((eq *context* ':result-type-only)
	 (values nil nil '(values &rest t))) ; not right, but safe.
	((value-context-p *context*)
	 (let ((temp  (make-symbol "TEMP")))
	   (re-translate-form
	    `(let ((,temp  (,doer ,step-clauses ,end-test-clause ,@body)))
	       ,temp))))
	(t
	 (do-do-aux step-clauses end-test-clause body binder setter))))


;;; DO and DO* expand into an appropriate binding construct and a nested
;;; call to a hack special form, DO-BODY, which is in turn handled below.
;;; The motivation for doing this is that it permits us not to have to
;;; duplicate the code involved in setting up the bindings of the DO
;;; variables from that which is already done by LET and LET*.  DO-BODY
;;; gives us a hook back into things at the point where the bindings
;;; have already been established.
;;; *** The DO-BODY business is really broken.  I think the right thing
;;; *** to do here is to have a naive canonical expansion in terms of 
;;; *** LOOP and then pattern-match on the resulting target language to 
;;; *** look for particular idioms.

(defun do-do-aux (step-clauses end-test-clause body binder setter)
  (multiple-value-bind (variables init-forms steppers)
      (canonicalize-do-bindings step-clauses)
    (multiple-value-bind (real-body decls) (parse-body body nil)
      (let ((end-test     (car end-test-clause))
	    (result-form  (if (cddr end-test-clause)
			      `(progn ,@(cdr end-test-clause))
			      (cadr end-test-clause))))
	(multiple-value-call #'compress-for variables binder
			     (re-translate-form
			      `(block nil
				 (,binder ,(mapcar #'list variables init-forms)
					  (declare ,@decls)
					  (do-body ,variables
					    ,end-test
					    ,result-form
					    (,setter ,@steppers)
					    (tagbody ,@real-body))))))))))

(defun canonicalize-do-bindings (list)
  (let ((variables  nil)
	(init-forms nil)
	(steppers   nil))
    (dolist (l list)
      (if (atom l)
	  (progn
	    (push l variables)
	    (push nil init-forms))
	  (progn
	    (push (car l) variables)
	    (push (cadr l) init-forms)
	    (when (cddr l)
	      (push (car l) steppers)
	      (push (caddr l) steppers)))))
    (values
     (nreverse variables)
     (nreverse init-forms)
     (nreverse steppers))))


;;; If we got a FOR statement back from translating a DO or DO*, DO-BODY
;;; just made the initialization expression be empty.  The actual 
;;; initializations for the DO variables were made elsewhere by the LET 
;;; or LET* binding code.  
;;; The purpose of this function is to look for cases where the LET/LET* 
;;; binding initializations can be moved into the FOR statement.
;;; The pattern we are looking for is
;;;    `((with-lexical-bindings <bindings>
;;;          ,@inits
;;;          (for-statement <init> <test> <step> <body> <finally>)))
;;; which is what is normally produced by LET and LET* if there are no
;;; special bindings involved or other bizarre things, like returns
;;; from the block in the initialization forms.  Anyway, if we don't 
;;; find exactly this pattern or if any of the initializations involve
;;; things that are not expressions, leave things exactly the way they are.

(defun compress-for (variables binder statements value type temps)
  (let ((tbinder nil)
	(for     nil)
	(inits   nil))
    (if (and (null (cdr statements))
	     (eq (target-form-type (setq tbinder (car statements)))
		 'with-lexical-bindings)
	     (eq (length variables) (length (cadr tbinder)))
	     (eq (target-form-type (setq for (car (last (cddr tbinder)))))
		 'for-statement)
	     (setq inits (butlast (cddr tbinder)))
	     (every #'expression-p inits)
	     (or (null (cdr inits))
		 (and (not *avoid-comma-operator*)
		      (eq binder 'let)))) ; avoid some sort of C bug
	(values
	 (list (make-target-form
		'with-lexical-bindings
		(cadr tbinder)
		(apply-make-target-form
		 'for-statement
		 (apply-make-target-form 'comma-operator inits)
		 (third for)
		 (fourth for)
		 (fifth for)
		 (when (sixth for) (list (sixth for))))))
	 value type temps)
	(values statements value type temps))))


;;; DOLIST and DOTIMES
;;; These are just macros with the obvious expansions.
;;; *** It's not clear from CLtL whether providing a declaration for the
;;; *** iteration variable is really correct because of the possibility of
;;; *** setq'ing it in the body.  CLtL says doing so "will have
;;; *** unpredictable, possibly implementation-dependent results", but
;;; *** it's not clear whether that means "unspecified" or "undefined".
;;; *** If the former, then providing the declaration is wrong, since
;;; *** violation of the declaration is "undefined".
;;; *** We might try to be clever by having DOTIMES propagate type 
;;; *** information from a non-constant count-form to the count variable.
;;; *** We might also provide a global declaration as an extension to
;;; *** control whether DOTIMES automagically declares its iteration variable
;;; *** to be a fixnum.

(define-translator-macro dolist ((variable list-form &optional result-form)
		                 &body body)
  ;; CLtL requires that there be a single binding for VARIABLE
  ;; which is also available to RESULT-FORM.
  ;; If possible, it's stylistically better to assign the
  ;; variable within the body of the macro.
  ;; *** Kludge alert:  Test for whether to use
  ;; *** "compulsive form" isn't general;
  ;; *** Leaves redundant NIL assignment (this could be eliminated
  ;; *** if there were a WITH-LEXICAL-BINDING form)
  (multiple-value-bind (real-body decls) (parse-body body nil)
    (let ((tail  (make-symbol "TAIL")))
      (if result-form
	  ;; Must bind variable before result-form
	  `(do* ((,tail  ,list-form (cdr ,tail))
		 (,variable  (car ,tail) (car ,tail)))
		((endp ,tail) ,result-form)
	     (declare (type list ,tail) ,@decls)
	     ,@real-body)
	  `(do* ((,tail ,list-form (cdr ,tail))
		 ,variable)
		((endp ,tail) ,result-form)
	     (declare (type list ,tail) ,@decls)
	     (setq ,variable (car ,tail))
	     ,@real-body)))))
	        
(define-translator-macro dotimes ((variable count-form &optional result-form)
				  &body body &environment env)
  (multiple-value-bind (real-body decls) (parse-body body nil)
    (let ((variable-type
	   (block variable-type
	     (dolist (decl-spec decls nil)
	       (dolist (var-info (tutil::parse-declaration decl-spec env))
		 (when (and (eq (car var-info) variable)
			    (eq (cadr var-info) 'type))
		   (return-from variable-type (caddr var-info))))))))
      (multiple-value-bind (count-value valuep constantp)
	  (let ((expanded (apply-macros count-form env)))
	    (translator-constant-value expanded env))
	(if (not constantp)
	    (let ((count (make-symbol "LIMIT")))
	      `(do ((,count ,count-form)
		    (,variable 0 (1+ ,variable)))
		   ((>= ,variable ,count) ,result-form)
		 (declare ,(if variable-type
			       `(type ,variable-type ,count)
			       `(type integer ,variable ,count))
			  ,@decls)
		 ,@real-body))
	    `(do ((,variable 0 (1+ ,variable)))
		 ((>= ,variable ,count-form) ,result-form)
	       (declare ,@(unless variable-type
			    `((type (integer 0 ,(if valuep
						    (max count-value 0)
						    '*))
				    ,variable)))
			,@decls)
	       ,@real-body))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Low-level stuff
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Loop forever.  Corresponds to a C while(TRUE) loop, but we have
;;; a special target language construct.

(deftranslate forever (&body body)
  (multiple-value-bind (statements value type temps)
      (translate-iteration-block `(,@body (dont-return)))
    (values (list (make-target-form
		   'forever-statement
		   (one-statement statements)))
	    value type temps)))


;;; Translate-iteration-block establishes a BLOCK binding in the environment
;;; and hints that any RETURNs from the block should be turned into C
;;; "break" statements instead of "goto"s.
;;; Additionally, we have to do something to indicate that the forms
;;; within the BLOCK don't return any value at all instead of being
;;; treated as an implicit PROGN.  We can't just specify context :ignore
;;; because that that would be inherited by any RETURNs inside the
;;; BLOCK, which must inherit the return context of the looping construct
;;; instead.  Anyway, we get around that by introducing this place-holder
;;; as the last form of the loop body.

(deftranslate dont-return ()
  (handle-nonreturning-context nil nil))


;;; Here's the hack special form for handling DO and DO*.  At this point
;;; all of the bindings have been made.
;;; Try to turn the DO or DO* into a C for statement whenever possible.
;;; There are all sorts of things that can go wrong with this, notably:
;;; * the end-test can't be expressed as an expression.
;;; * the setter can't be expressed as an expression.
;;; * we have to put code for returning the result-form someplace and
;;;   we can't put it at the end of the loop because there are "breaks"
;;;   from the loop.
;;; As soon as we notice something has gone wrong, give up on producing
;;; a for and produce a FOREVER instead, putting an explicit IF test
;;; for the return inside the loop body.
;;;
;;; Note that walking the setter-form in an :ignore context but then trying
;;; to turn it into an expression really is the right thing, since the
;;; value of the stepper expression in the for-statement is ignored too.
;;; The translate-form will return NIL as its "value" value, and
;;; comma-ize is smart enough to deal with it.  The only tricky part is
;;; where the setter-form is something like an empty SETQ; in this case,
;;; the setter-value will be returned as NIL, which represents an empty
;;; stepper expression in the for-statement.

(deftranslate do-body (variables end-test-form result-form setter-form
				 body-form)
  (when (value-context-p *context*)
    (error "Internal error:  DO-BODY not for side effect"))
  (when (eq *context* ':result-type-only)
    (return-from do-body
      (values nil nil '(values &rest t)))) ; not right, but safe
  (multiple-value-bind (end-test-statements end-test-value)
      (multiple-value-call #'comma-ize
	(translate-form end-test-form *environment*
			*predicate-context*))
    (setq end-test-value (coerce-to-pseudo-boolean end-test-value))
    (if end-test-statements
	(return-from do-body
	  (do-body-as-forever end-test-form result-form setter-form
			      body-form)))
    (multiple-value-bind (setter-statements setter-value)
	(multiple-value-call #'comma-ize
	  (translate-form setter-form *environment* *ignore-context*))
      (if setter-statements
	  (return-from do-body
	    (do-body-as-forever end-test-form result-form setter-form
				body-form)))
      (multiple-value-bind
	    (body-statements body-value body-type body-temps returns-p)
	  (translate-iteration-block `(,body-form (dont-return)))
	(declare (ignore body-value body-temps))
	(if (not (or (null returns-p)
		     (eq *context* :return)
		     (and (eq *context* *ignore-context*)
			  (variable-or-constant-p result-form
						  *environment*))))
	    (return-from do-body
	      (do-body-as-forever end-test-form result-form
				  setter-form body-form)))
	(multiple-value-bind
	      (result-statements result-value result-type)
	    (translate-form result-form *environment* *context*)
	  (values
	   (if (or variables setter-value)
	       (list
		(apply-make-target-form
		 'for-statement
		 nil
		 (negate end-test-value)
		 setter-value
		 (one-statement body-statements)
		 (if result-statements
		     (list (one-statement result-statements)))))
	       (append
		result-statements
		(list
		 (make-target-form
		  'while-statement
		  (negate end-test-value)
		  (one-statement body-statements)))))
	   result-value
	   (or-value-types result-type body-type *environment*)))))))

(defun do-body-as-forever (end-test-form result-form setter-form body-form)
  (re-translate-form
   `(forever
     (if ,end-test-form
	 (return ,result-form))
     ,body-form
     ,setter-form)))

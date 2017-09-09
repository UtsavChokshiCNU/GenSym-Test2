;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; values.lsp -- constructs for handling multiple values
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  30 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/values.lisp,v $"
 "$Revision: 1.5 $"
 "$Date: 2007/07/13 18:16:53 $")

;;; These must not be greater than supplied by the corresponding RTL macros.
(defparameter *max-values-inline-store* 15)    ; VALUES_n
(defparameter *max-values-inline-assign* 10)   ; MVS_n

;;; VALUES is normally opencoded.  If there are too many arguments, or
;;; if the arguments are complex enough to potentially overwrite the 
;;; multiple values vector, give up and generate a call to the ordinary
;;; VALUES function instead.


(defun get-first-result-type-with-type (form type)
  (multiple-value-bind (statements value result-type temps)
      (translate-form form *environment* :result-type-only type)
    (declare (ignore statements value temps))
    result-type))

(defmacro value-type-iterator (type &body body)
  (let ((type-list-var (make-symbol "TYPE-LIST")))
    `(let ((,type-list-var ,type))
       (if (and (consp ,type-list-var)
		(eq (car ,type-list-var) 'values))
	   (pop ,type-list-var)
	   (setq ,type-list-var (list ,type-list-var)))
       (flet ((next-value-type ()
		(case (car ,type-list-var)
		  ((&optional &key)
		   (setq ,type-list-var '(&rest t))))
		(case (car ,type-list-var)
		  (&rest
		   (cadr ,type-list-var))
		  (t
		   (pop ,type-list-var)))))
	 ,@body))))

;see /home/rh/deftranslate-values.diffs
;The idea is to use a declaration of the type
;of more than just the first result.
(deftranslate values (&rest args)
  (cond ((eq *context* ':result-type-only)
	 (values nil nil
		 (value-type-iterator
		   *result-type*
		   (if (and args (null (cdr args)))
		       (get-first-result-type-with-type
			 (car args)
			 (next-value-type))
		       `(values
			  ,@(mapcar #'(lambda (arg)
					(get-first-result-type-with-type
					  arg
					  (next-value-type)))
				    args))))
		 nil))
	((or (multiple-value-context-p *context*)
	     (value-saving-context-p *context*))
	 (if (> (length args) *max-values-inline-store*)
	     ;; When too many arguments, generate out-of-line call.
	     (translate-function-call `(values ,@args))
	     (multiple-value-bind (statements result-exprs result-types temps)
		 ;; Using translate-arguments here does a bit more temping than
		 ;; is strictly necessary, since the values macros ensure
		 ;; left-to-right ordering of all argument expressions except
		 ;; the first.  However, the frequency with which extra temps
		 ;; will be generated seems likely to be sufficiently small to
		 ;; not be worth the extra code needed to check for it.
		 (translate-arguments
		  args
		  (value-type-iterator
		    *result-type*
		    (mapcar #'(lambda (arg)
				(get-first-result-type-with-type
				  arg
				  (next-value-type)))
			    args))
		  ;; In addition to the reasons for temping normally used
		  ;; for arguments, also temp any arguments that are values
		  ;; affecting or consing.  In both cases, this is needed
		  ;; because the values count gets set before executing the
		  ;; value producing expressions. In particular,
		  ;; it is necessary to temp consing expressions because
		  ;; otherwise the GC will use potenitally unititialized
		  ;; or garbage parts of the values buffer as part of
		  ;; its root set.
		  (if (endp (cdr args))
		      ;; Consing doesn't matter if there is only one
		      ;; argument, since first value is in a special place
		      ;; rather than in the values buffer.
		      #'(lambda (value stmts exprs)
			  (declare (ignore stmts exprs))
			  (values-changing-expression-p value))
		      #'(lambda (value stmts exprs)
			  (declare (ignore stmts exprs))
			  (or (values-changing-expression-p value)
			      (not (nonrelocating-expression-p value))))))
	       (handle-context statements
			       (apply-make-target-form 'values result-exprs)
			       `(values ,@result-types)
			       temps
			       (translator-foreign-type :object)))))
	;;((null (cdr args)) (re-translate-form (car args)))
	(t (re-translate-form `(prog1 ,@args)))))


;;; Assume VALUES-LIST is treated like an ordinary function call.

;;; MULTIPLE-VALUE-LIST has a primitive in the RTL.

(deftranslate multiple-value-list (form)
  (if (eq *context* ':result-type-only)
      (values nil nil 'list nil)
      (multiple-value-bind (statements value type temps)
	  (let ((*reason-for-multiple-values-context*
		  (list :explicit-multiple-values (current-function-name))))
	    (translate-form form *environment* :values))
	(declare (ignore type temps))
	(handle-context statements
			(make-target-form 'foreign-call 'trun:%mv-list value)
			'list
			nil
			(translator-foreign-type :object)))))

;;; MULTIPLE-VALUE-CALL collects multiple values from argument forms on the
;;; stack.
;;; *** Perhaps the protocol should be changed so that last form is executed in
;;; *** :values context, with boolean argument to MV_FUNCALL specifying whether
;;; *** any arguments saved on stack.

(deftranslate multiple-value-call (function &rest forms)
  (if (endp forms)
      (re-translate-form `(funcall ,function))
      (multiple-value-bind (stmts value type temps)
	  (translate-form function *environment* *value-context*)
	(declare (ignore type))
	(labels ((translate-mv-call-args (args context)
		   (cond ((null args) nil)
			 ((null (cdr args))
			  (translate-mv-call-arg (car args) context))
			 (t
			  (nconc
			    (with-stack-level
			      (translate-mv-call-args (cdr args) :more-values))
			    (translate-mv-call-arg (car args) context)))))
		 (translate-mv-call-arg (arg context)
		   (let ((*reason-for-multiple-values-context*
			   (list :explicit-multiple-values (current-function-name))))
		     (translate-form arg *environment* context)))
		 (handle-call (fstmts fvalue args temps)
		   (handle-context
		     (nconc (translate-mv-call-args args :save-values) fstmts)
		     (make-target-form 'foreign-call 'trun:%mv-funcall fvalue)
		     t
		     temps
		     (translator-foreign-type :object))))
	  (if (and (not (state-using-expression-p value))
		   (not (state-changing-expression-p value)))
	      (handle-call stmts value forms temps)
	      (with-temporary-for-value context
		(push (make-target-form 'setq context value) stmts)
		(handle-call stmts value forms temps)))))))
	      
;;; MULTIPLE-VALUE-PROG1 saves values from first form on the stack while
;;; executing the remaining forms.

(deftranslate multiple-value-prog1 (first &body forms)
  (cond	((or (endp forms)
	     (eq *context* ':result-type-only))
	 (re-translate-form first))
	((multiple-value-context-p *context*)
	 (multiple-value-bind (statements value type temps)
	     (translate-form first *environment* :save-values)
	   (handle-context
	     (nconc (with-stack-level
		      (translate-progn-body forms
					    *environment*
					    *ignore-context*
					    nil))
		    statements)
	     value type temps)))
	((value-saving-context-p *context*)
	 (multiple-value-bind (statements value type temps)
	     (translate-form first *environment* *context*)
	   (values (nconc (with-stack-level
			    (translate-progn-body forms
						  *environment*
						  *ignore-context*
						  nil))
			  statements)
		   value type temps)))
	(t
	 (re-translate-form `(prog1 ,first ,@forms)))))

;;; Multiple-value-bind is similar to LET and LAMBDA binding.  See
;;; binding.lsp.

(deftranslate multiple-value-bind (names value-form &body body)
  (cond ((null names)
	 ;; When no names, execute value-form for side-effect and execute body.
	 (re-translate-form
	  ;; Arrange for proper scoping of declarations.  ANSI excludes value
	  ;; form from scope of declarations, CLtL includes.
	  (if *ansi-semantics*
	      `(progn ,value-form (locally ,@body))
	      (multiple-value-bind (real-body decls) (parse-body body)
		`(locally (declare ,@decls) ,value-form ,@real-body)))))
	((null (cdr names))
	 ;; If only a single variable binding bound, use let instead.  This may
	 ;; produce better code because the value form will be generated for
	 ;; single value rather than multiple values.
	 (re-translate-form `(let ((,(car names) ,value-form)) ,@body)))
	(t
	 (multiple-value-bind (real-body decls) (parse-body body)
	   (multiple-value-bind (bound-decls free-decls)
	       (parse-variable-declarations names decls *environment*)
	     (translate-let-aux names bound-decls free-decls real-body
				*environment*
				#'(lambda (records outer-env)
				    (translate-mv-bind-init-forms
				     value-form records outer-env))))))))
	 

;;; Return two values, the list of records to be bound and a list of
;;; initialization statements.
;;; *** If only one variable used, should transform into nth-value (or just
;;; *** first value if only the first is used).

(defun translate-mv-bind-init-forms (value-form records outer-env)
  (with-temporary-variables
    (let ((temp (when (dolist (record records nil)
			(unless (variable-binding-used-p record)
			  (return t)))
		  (allocate-temporary))))
      (when temp
	;; When there are unused records, replace them with a temp record.
	(setf records (mapcar #'(lambda (record)
				  (if (variable-binding-used-p record)
				      record
				      temp))
			      records))
	;; Do some cleaning up on the records, removing trailing temp records.
	(let ((index (position temp records :test-not #'eq :from-end t)))
	  (if (null index)
	      ;; No used variables!
	      (return-from translate-mv-bind-init-forms
		(values nil (translate-form value-form outer-env
					    *ignore-context*)))
	      (progn
		;; Some trailing variables unused.  Get rid of them.
		(setf (cdr (nthcdr index records)) nil)
		(when (= index (position temp records :test-not #'eq))
		  ;; The first used variable is also the last, so only one
		  ;; used.  Use nth-value instead of mv-setq to compute the
		  ;; initialization.
		  (return-from translate-mv-bind-init-forms
		    (translate-single-mv-bind-init index
						   (nth index records)
						   value-form
						   outer-env)))
		(unless (member temp records :test #'eq) (setf temp nil))))))
      (multiple-value-bind (statements value type temps)
	  (let ((*reason-for-multiple-values-context*
		  (list :explicit-multiple-values (current-function-name))))
	    (translate-form value-form outer-env :values))
	(declare (ignore type))
	(multiple-value-bind (mvs-statements mvs-temps)
	    (compute-mv-setq-assignments
	     (mapcar #'(lambda (record)
			 (make-target-form 'local-variable record))
		     records)
	     value)
	  (setq temps (nconc temps mvs-temps))
	  (when temp
	    ;; Mark temp as ignorable.
	    (setf (variable-record-needs-gc-protection temp) nil)
	    (setf (variable-record-ignorable-p temp) t)
	    ;; Remove all but one occurance of temp from records.
	    (setf records
		  (delete temp records
			  :start (1+ (position temp records)))))
	  (values records
		  (with-bound-temporary-variables
		      (if temp
			  (cons temp temps)
			  temps)
		    (nconc mvs-statements statements))))))))

(defun translate-single-mv-bind-init (index record value-form env)
  (values (list record)
	  (translate-form `(nth-value ,index ,value-form)
			  env
			  (make-target-form 'local-variable record))))

;;; See SETQ in binding.lsp.  The wrinkle here is symbol macros.  If we
;;; find any symbol macros at all, treat this like SETF of VALUES.
;;; *** We might make this smart enough at some point to be able to
;;; *** treat assignment of L-values specially.  The expansion in terms
;;; *** of SETF of VALUES produces a bunch of individual assignments, not
;;; *** a single values-assign.

(deftranslate multiple-value-setq (names value-form)
  (cond ((and (eq *context* *ignore-context*)
	      (consp value-form)
	      (eq (car value-form) 'values))
	 (re-translate-form 
	   (let* ((vars names)
		  (forms (cdr value-form))
		  (temps (mapcar #'(lambda (var form)
				     (declare (ignore var form))
				     (make-symbol "TEMP"))
				 vars forms)))
	     
	     `(let ,(mapcar #'list temps forms)
		(setf ,@(mapcan #'(lambda (var)
				    (pop forms)
				    (list var (pop temps)))
				vars))
		,@forms))))	      
	((null names)			; return single value from value-form
	 (re-translate-form `(values ,value-form)))
	((null (cdr names))		; only one value needed
	 (re-translate-form `(setq ,(car names) ,value-form)))
	(t
	 (multiple-value-bind (failurep places types)
	     (mv-setq-places names)
	   (when failurep
	     (return-from multiple-value-setq
	       (re-translate-form
		`(values (setf (values ,@names) ,value-form)))))
	   (multiple-value-bind (statements value type temps)
	       (let ((*reason-for-multiple-values-context*
		       (list :explicit-multiple-values (current-function-name))))
		 (translate-form value-form *environment* :values))
	     (setq type (and-types (single-value-type type *environment*)
				   (or (car types) 'null)
				   *environment*))
	     (when (eq *context* ':result-type-only)
	       (return-from multiple-value-setq
		(values nil nil type nil)))
	     (if (or (eq *context* *ignore-context*)
		     (eq (target-form-type (car places)) 'local-variable))
		 (multiple-value-bind (a-statements a-temps)
		     (compute-mv-setq-assignments places value)
		   (handle-context
		    (nconc a-statements statements)
		    (car places) type (nconc temps a-temps)
		    (unless (eq *context* *ignore-context*)
		      (variable-record-foreign-type (cadar places)))))
		 (with-temporary-for-value context
		   (multiple-value-bind (a-statements a-temps)
		       (compute-mv-setq-assignments places value)
		     (handle-context
		      (nconc a-statements
			     (cons (make-target-form
				    'setq
				    (copy-target-form context)
				    (first-multiple-value))
				   statements))
		      context type (nconc temps a-temps))))))))))

(defun compute-mv-setq-assignments (places values-expression &optional
					   (count (length places)))
  (cond ((some #'(lambda (place)
		   (not (eq (translator-foreign-type :object)
			    (context-foreign-type place))))
	       places)
	 (let ((alist nil))
	   (dolist (place places)
	     (unless (or (eq (translator-foreign-type :object)
			     (context-foreign-type place))
			 (assoc place places :test #'equal))
	       (push (cons place (allocate-temporary)) alist)))
	   (let ((new-places
		  (mapcar #'(lambda (place)
			      (let ((a (assoc place alist :test #'equal)))
				(if a
				    (make-target-form 'local-variable (cdr a))
				    place)))
			  places)))
	     (multiple-value-bind (statements temps)
		 (compute-mv-setq-assignments
		  new-places values-expression count)
	       (dolist (a alist)
		 (let ((*context* (car a))
		       (record (cdr a)))
		   (setq statements
			 (handle-context
			  statements 
			  (make-target-form 'local-variable record)
			  t
			  nil
			  (translator-foreign-type :object)))))
	       (values statements temps)))))
	(t
	 (values (list (apply-make-target-form 'values-assign places)) nil))))

(defun mv-setq-places (names)
  (let ((places nil)
	(types nil))
    (dolist (name names)
      (multiple-value-bind (place type)
	  (get-variable-place name)
	(if (or (null place)
		(and (consp place) (eq (target-form-type place) 'macro-call)))
	    (return-from mv-setq-places t)    ; return failure indicator
	    (progn
	      (push place places)
	      (push type types)))))
    (values nil (nreverse places) (nreverse types))))

(defun get-variable-place (name)
  (multiple-value-bind (place type) (variable-place name t)
    (cond (place (values place type))
	  ((symbolp (setf name (translator-macroexpand-1 name *environment*)))
	   (get-variable-place name))
	  (t (values nil nil)))))


;;; Nth-value corresponds directly to the nth-value expression in the
;;; target language.  Just make sure that the value of the index expression
;;; is something that can safely be evaluated after the values-producing
;;; expression.

(deftranslate nth-value (n form)
  ;; If n is a constant zero, translate form for single value.
  (let ((expanded (apply-macros n *environment*)))
    (when (eql 0 (translator-constant-value expanded *environment*))
      (return-from nth-value
	(re-translate-form `(values ,form)))))
  (multiple-value-bind (n-statements n-value n-type n-temps)
      (translate-form n *environment* (translator-foreign-type :int))
    (declare (ignore n-type))
    (when (or (state-changing-expression-p n-value)
	      (state-using-expression-p n-value)
	      (values-changing-expression-p n-value)
	      ;; *** Perhaps there should be some heuristic here to also temp
	      ;; *** `expensive' expressions, since n gets evaluated multiple
	      ;; *** times.
	      )
      (let ((*context* (translator-foreign-type :int)))
	(multiple-value-setq (n-statements n-value n-type n-temps)
	  (with-temporary-for-value context
	    (translate-form n *environment* context)))))
    (handle-context
     (nconc
       (let ((*reason-for-multiple-values-context*
	       (list :explicit-multiple-values (current-function-name))))
	 (translate-form form *environment* :values))
       n-statements)
     (make-target-form 'nth-value n-value)
     t
     n-temps
     (translator-foreign-type :object))))

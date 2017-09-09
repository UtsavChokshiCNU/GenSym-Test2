;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; catch.lisp -- catch, throw, and unwind-protect
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  30 Jun 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/catch.lisp,v $"
 "$Revision: 1.4 $"
 "$Date: 2007/07/13 18:16:52 $")

;;; Catch, throw, and unwind-protect are implemented using the C
;;; "setjmp" and "longjmp" library functions.
;;;
;;; The idea is that CATCH allocates a new catch frame and pushes it
;;; onto the catch stack.  The catch frame contains the tag, a jmp_buf
;;; structure, and a pointer to the dynamic binding stack.  Then it
;;; calls setjmp which returns zero in the normal case and non-zero
;;; in the case where longjmp was called.  We do the appropriate things
;;; (either executing the body forms or moving the stored value from 
;;; the throw, as appropriate) and then pop the catch frame from the
;;; stack before continuing.
;;;
;;; UNWIND-PROTECT is similar to CATCH.  It creates a catch frame in
;;; the same way, with a magic tag to identify it as being an
;;; unwind-protect instead of an ordinary catch.  The main difference
;;; is that after executing the cleanup forms, you have to go back and
;;; see if there was a THROW in progress and continue throwing down
;;; the stack if so.
;;;
;;; THROW is handled almost entirely by a routine in the run-time library.
;;; All we have to do is store the results of the value-returning form
;;; as normal multiple values and then pass the tag off to the library
;;; routine.
;;;
;;; The library routine for THROW should first check to make sure that there
;;; is a matching tag and signal an error if there isn't.  Then it should
;;; scan down the catch stack again looking for unwind-protect frames
;;; as well.  When it reaches an unwind-protect frame, it must pop the
;;; dynamic binding stack and push the throw values and current throw tag 
;;; onto a stack of its own, and then do a longjmp.  UNWIND-PROTECT
;;; needs some kind of a helper routine to re-throw using the information
;;; on the stack.  Finally, when you find the frame on the catch stack
;;; matching the throw tag, you pop the dynamic binding stack again, and
;;; do another longjmp.  So the CATCH should end up seeing the values
;;; from the THROW in the normal multiple values storage area.



;;; If context is :value or :ignore, allocate a temporary variable.
;;; If context is :return, change it to :values and do the return on the
;;; result.

(deftranslate catch (tag &body body)
  (cond ((eq *context* ':result-type-only)
	 (values nil nil '(values &rest t) nil))
	((value-context-p *context*)
	 (with-temporary-for-value context (do-catch-aux tag body context)))
	((or (eq *context* :return)
	     (value-saving-context-p *context*))
	 (multiple-value-call #'handle-context-multiple-values
	   (do-catch-aux tag body :values)))
	(t
	 (do-catch-aux tag body *context*))))

;;; Return the value if the tag is a compile-time constant, otherwise
;;; return :unknown.
(defun get-tag-value (tag-expression)
  (cond
    ((memq (target-form-type tag-expression) '(constant initial-symbol))
     (second tag-expression))
    ((eq (target-form-type tag-expression) 'local-variable)
     ;; for catches introduced by hard-case return-from,
     ;; we match up the catch and throw using the
     ;; variable in which the unique catch tag is stored.
     ;; In theory, this is not quite conservative; the same
     ;; variable might be used at different times to store
     ;; two different tags, one at the time of a catch and
     ;; another at the time of a throw. But even G2 code isn't that
     ;; convoluted.
     (get-variable-record-uid (second tag-expression)))
    (t (values))))

#| old version: mostly works.

;;; we don't want to expose variable records to the outside world,
;;; so instead, use this hash table to produce a UID for each one
;;; instead.
(defparameter *variable-record-uid-table* (make-hash-table :test #'eq))

(defun get-variable-record-uid (record)
  (or (gethash record *variable-record-uid-table*)
      (setf (gethash record *variable-record-uid-table*)
	    (gentemp "RECORD-ID-"))))

|#

(defparameter *variable-record-uid-table* (make-hash-table :test #'eq))

(defun record-variable-containing-compiler-introduced-catch-tag (var)
    (setf (gethash var *variable-record-uid-table*) var))

(defun get-variable-record-uid (record)
  (gethash (variable-record-name record) *variable-record-uid-table*))

(defun do-catch-aux (tag body context)
  (multiple-value-bind (tag-statements tag-value tag-type tag-temps)
      (translate-form tag *environment* *value-context*)
    (declare (ignore tag-type))
    (when (memq *context* '(:return :save-values :values :more-values))
      (report-tail-call (multiple-value-call #'list :catch (get-tag-value tag-value))))
    (let ((catcher (cons nil nil)))
      (multiple-value-bind (body-statements body-value body-type body-temps)
	  (translate-progn-body body
				(bind-catcher catcher *environment*)
				context
				nil)
	(declare (ignore body-type))
	(let ((catch (apply-make-target-form 'with-catch
		       nil
		       tag-value
		       (apply-make-target-form 'compound-statement
					       (nreverse body-statements))
		       (fiddle-with-catch-context context))))
	  (setf (car catcher) catch)
	  (values (cons catch tag-statements)
		  body-value '(values &rest t)
		  (append tag-temps body-temps)))))))

(defun fiddle-with-catch-context (context)
  (unless (eq context *ignore-context*)
    (let ((*context* context))
      (list (apply-make-target-form
	     'compound-statement
	     (handle-context nil (catch-values)
			     '(values &rest t) nil
			     (translator-foreign-type :object)))))))

;;; Parallel to FIRST-MULTIPLE-VALUE:  Generate a target language
;;; form which returns the values stored by THROW.

(defun catch-values ()
  (make-target-form 'foreign-call 'trun:%catch-values))

;;; Throw is a bit simpler.  If the tag isn't a constant, allocate a new
;;; temporary variable to hold it to be sure that its value won't change
;;; during the evaluation of the value form.

(deftranslate throw (tag value-form)
  (if (eq *context* ':result-type-only)
      (values nil nil nil nil)
      (multiple-value-call #'do-throw-aux
	(if (variable-or-constant-p tag *environment*)
	    (translate-form tag *environment* *value-context*)
	    (with-temporary-for-value context
	      (translate-form tag *environment* context)))
	value-form)))

(defun do-throw-aux (tag-statements tag-value tag-type tag-temps value-form)
  (declare (ignore tag-type))
  (handle-nonreturning-context
   (cons (make-target-form 
	  'macro-call
	  'trun:%throw 
	  tag-value
	  (first-multiple-value))
	 (let ((*reason-for-multiple-values-context* (multiple-value-call #'list :throw (current-function-name) (get-tag-value tag-value))))
	   (append (translate-form value-form *environment* :values)
		   tag-statements)))
   tag-temps))


;;; Unwind-protect is like a cross between CATCH and MULTIPLE-VALUE-PROG1.
;;; The problem is that the return value(s) from the protected-form have
;;; to be saved someplace where they won't get overwritten by evaluating
;;; the cleanup forms.

(deftranslate unwind-protect (protected-form &body cleanup-forms)
  (if (or (eq *context* ':result-type-only)
	  (eq *context* *ignore-context*)
	  (value-saving-context-p *context*))
      (do-unwind-protect-aux protected-form cleanup-forms *context*)
      (multiple-value-call #'handle-context
	(if (multiple-value-context-p *context*)
	    (do-unwind-protect-aux protected-form cleanup-forms :save-values)
	    (let ((*reason-for-multiple-values-context* '(:unwind-protect)))
	      (translate-form `(unwind-protect
				    (values ,protected-form)
				 ,@cleanup-forms)
			      *environment*
			      :values)))
	(translator-foreign-type :object))))

(defun do-unwind-protect-aux (protected cleanups context)
  (multiple-value-bind (pstmts pvalue preturn-type ptemps)
      (translate-form protected
		      (bind-catcher 'unwind-protect *environment*)
		      context)
    (declare (ignore pvalue ptemps))
    (if (eq *context* ':result-type-only)
	(values nil nil preturn-type nil)
	;; Note that cleanups must be translated with a new stack level, even
	;; if the context is :ignore, since throw might have pushed values on
	;; the stack.
	(let ((cstmts (with-stack-level
			(translate-progn-body cleanups
					      *environment*
					      *ignore-context*
					      nil))))
	  (values (list (make-target-form
			 'with-unwind-protect
			 nil
			 (one-statement pstmts)
			 (one-statement cstmts)))
		  (unless (eq context *ignore-context*)
		    (make-target-form 'restore-values))
		  preturn-type nil)))))

;;; PROGV is an unwind-protect with an implicit cleanup form that restores the
;;; saved bindings.

(deftranslate progv (syms vals &body body)
  (cond ((eq *context* ':result-type-only)
	 (translate-progn-body body *environment* *context* nil *result-type*))
	((value-context-p *context*)
	 (with-temporary-for-value context
	  (do-progv-aux syms vals body context *result-type*)))
	((or (multiple-value-context-p *context*)
	     (value-saving-context-p *context*))
	 (multiple-value-call #'handle-context-multiple-values
	   (do-progv-aux syms vals body :values *result-type*)))
	(t
	 (do-progv-aux syms vals body *context* *result-type*))))


(defun do-progv-aux (syms vals body context return-type)
  (multiple-value-bind (val-stmts val-value val-type val-temps)
      (translate-form vals *environment* *value-context*)
    (declare (ignore val-type))
    (flet ((do-progv-aux-1 (syms sym-context val-stmts val-value val-temps
				 body context return-type)
	     (multiple-value-bind (sym-stmts sym-value sym-type sym-temps)
		 (translate-form syms *environment* sym-context)
	       (declare (ignore sym-type))
	       (multiple-value-bind (body-stmts
				     body-value body-type body-temps)
		   (translate-progn-body
		    body
		    (bind-catcher 'unwind-protect *environment*)
		    context nil return-type)
		   (values (cons (make-target-form
				  'with-progv
				  'nil
				  sym-value
				  val-value
				  (apply-make-target-form
				   'compound-statement
				   (nreverse body-stmts)))
				 (append val-stmts sym-stmts))
			   body-value
			   body-type
			   (append val-temps sym-temps body-temps))))))
      (if (null val-stmts)
	  (do-progv-aux-1 syms *value-context* nil val-value val-temps
			  body context return-type)
	  (with-temporary-for-value sym-context
	    (do-progv-aux-1 syms sym-context val-stmts val-value val-temps
			    body context return-type))))))


;;; WITH-AREA is an unwind-protect with an implicit cleanup form
;;; that restores the former consing area.

(deftranslate trun:with-area (area-keyword &body body)
  (cond ((eq *context* ':result-type-only)
	 (translate-progn-body body *environment* *context* nil *result-type*))
	((value-context-p *context*)
	 (with-temporary-for-value context
	   (do-with-area-aux area-keyword body context *result-type*)))
	((or (multiple-value-context-p *context*)
	     (value-saving-context-p *context*))
	 (multiple-value-call #'handle-context-multiple-values
	   (do-with-area-aux area-keyword body :values *result-type*)))
	(t
	 (do-with-area-aux area-keyword body *context* *result-type*))))

(defun do-with-area-aux (area-keyword body context result-type)
  (multiple-value-bind (body-stmts body-value body-type body-temps)
      (translate-progn-body
       body
       (bind-catcher 'unwind-protect *environment*)
       context nil result-type)
    (values (list (make-target-form
		   'with-area
		   nil
		   nil
		   area-keyword
		   (apply-make-target-form
		    'compound-statement
		    (nreverse body-stmts))))
	    body-value body-type body-temps)))

;;; WITH-DYNAMIC-AREA, WITH-STATIC-AREA, and WITH-LOCAL-AREA
;;; are implemented as macros based on WITH-AREA.

(define-translator-macro tx:with-dynamic-area (&body body)
  `(trun:with-area :dynamic ,@body))

(define-translator-macro tx:with-static-area (&body body)
  `(trun:with-area :static ,@body))

(define-translator-macro tx:with-local-area (&body body)
  `(trun:with-area :local ,@body))

;;; WITH-DYNAMIC-ALLOCATION is similar but binds *gc-inhibit*
;;; and calls ALLOW-GC.

(define-translator-macro tx:with-dynamic-allocation ((&key (dynamic 0)) &body body)
  `(tx:with-dynamic-area
    (trun:allow-gc ,dynamic 0)
    (let ((trun:*gc-inhibit* t))
      ,@body)))

;;; WITH-LOCAL-ALLOCATION is an unwind-protect with an implicit
;;; cleanup form that restores the former local area frontier,
;;; then restores the former consing area.

(deftranslate tx:with-local-allocation (&body body)
  (cond ((eq *context* ':result-type-only)
	 (translate-progn-body body *environment* *context* nil *result-type*))
	((value-context-p *context*)
	 (with-temporary-for-value context
	   (do-with-local-allocation-aux body context *result-type*)))
	((or (multiple-value-context-p *context*)
	     (value-saving-context-p *context*))
	 (multiple-value-call #'handle-context-multiple-values
	   (do-with-local-allocation-aux body :values *result-type*)))
	(t
	 (do-with-local-allocation-aux body *context* *result-type*))))

(defun do-with-local-allocation-aux (body context result-type)
  (multiple-value-bind (body-stmts body-value body-type body-temps)
      (translate-progn-body
       body
       (bind-catcher 'unwind-protect *environment*)
       context nil result-type)
    (values (list (make-target-form 'with-local-allocation
				    nil nil nil
				    (apply-make-target-form
				     'compound-statement
				     (nreverse body-stmts))))
	    body-value body-type body-temps)))


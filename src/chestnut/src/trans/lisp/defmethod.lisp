;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; The DEFMETHOD macro.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/defmethod.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2006/03/14 22:03:57 $")

(define-translator-macro defmethod (name &rest stuff &environment env)
  (with-translator-message `(defmethod ,name)
    (multiple-value-bind (qualifiers specialized-lambda-list body)
	(parse-method-stuff stuff)
      (let* ((lambda-list (extract-lambda-list specialized-lambda-list))
	     (method-name `(method ,name ,@qualifiers
				   ,(extract-specializer-names
				     specialized-lambda-list))))
	`(progn
	   (eval-when (:compile-toplevel)
	     (print-progress-message "Method"
				     ,@(mapcar #'(lambda (n) `',n)
					       (cdr method-name)))
	     (ensure-translator-defmethod-function
	      ',name
	      ',lambda-list
	      ',(translator-environment-name env)))
	   (eval-when (:load-toplevel :execute)
	     (generic-function-setup ,name)
	     (let ()
	       ;; Put this at not-top-level, so that all the effort that goes
	       ;; into this is avoided when just doing top-level stuff.
	       (defmethod-1 ,name ,qualifiers ,specialized-lambda-list ,@body))
	     ))))))

(define-translator-macro defmethod-1
        (name qualifiers lambda-list &body body)
  ;; There used to be more stuff here.
  `(defmethod-2 ,name ,qualifiers ,lambda-list ,@body))

(define-translator-macro defmethod-2
    (name qualifiers lambda-list &body body &environment env)
  (let ((message `(method ,name ,@qualifiers
			  ,(extract-specializer-names
			    lambda-list))))
    (with-translator-message message
      (multiple-value-bind (binding declspecs add-form)
	  (make-add-method `',name name qualifiers lambda-list body env)
	`(flet (,binding)
	   (declare (trans:translator-message ,@message))
	   (declare ,@declspecs)
	   ,add-form)))))

(defun make-add-method (gf name qualifiers lambda-list body env)
  (let* ((specializers (extract-specializer-names lambda-list))
	 (mname (make-method-name name qualifiers specializers))
	 ;; Make a dummy name for use in the flet and function reference
	 (fname (make-name "~A" (principal-name-of-function-name name))))
    (multiple-value-bind (lambda initargs)
	(make-method-function name lambda-list body env)
      (when qualifiers
	(setf (cgetf initargs :qualifiers) `',qualifiers))
      (values `(,fname ,@(cdr lambda))
	      ;; At one time I thought I could attach a dynamic-extent
	      ;; declaration to the local function, since add-named-method
	      ;; simply extracts the pointer to the C function and the
	      ;; environment from the function to store them in the method
	      ;; object, throwing away the function (at least, it does so when
	      ;; *method-function-uses-inline-slot* is true).  Unfortunately,
	      ;; such a declaration would potentially confuse closure
	      ;; processing, permitting the environment to be allocated with
	      ;; dynamic-extent too, and that would be very bad.  Oh well.
	      `((function-name ,fname ,mname))
	      `(tclos-run:add-named-method ,gf #',fname ,@initargs)))))

(defun parse-method-stuff (stuff)
  (let ((qualifiers ()))
    (do ((tail stuff (cdr tail)))
	((endp tail) (error "Invalid method body: ~S." stuff))
      (let ((next (car tail)))
	(if (listp next)
	    (return (values (nreverse qualifiers)
			    (car tail)
			    (cdr tail)))
	    (push next qualifiers))))))

(defun ensure-translator-defmethod-function (name lambda-list &optional env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (let ((record (generic-function-record-for-defmethod name env)))
    (if (null record)
	(translator-ensure-generic-function
	     name
	     :lambda-list
	     (generic-function-lambda-list-from-defmethod lambda-list)
	     :environment env)
	(let ((gf-ll (generic-function-record-lambda-list record)))
	  (unless (congruent-lambda-list-p gf-ll lambda-list)
	    (error "The lambda-list for method on ~S is not congruent with~@
                    the lambda-list for the generic function:~%  Method ~
                    lambda-list: ~S~%  Generic function lambda-list: ~S"
		   name
		   lambda-list
		   gf-ll))))))

(defun generic-function-lambda-list-from-defmethod (lambda-list)
  (multiple-value-bind (required optional rest keyp keys alwky aux)
      (parse-lambda-list-into-components lambda-list)
    (declare (ignore keys alwky aux))
    `(,@required
      ,@(when optional (cons '&optional (mapcar #'car optional)))
      ,@(when rest (list '&rest rest))
      ,@(when keyp (list '&key)))))

;;; Check congruence of lambda-lists.

(defun congruent-lambda-list-p (generic-lambda-list method-lambda-list)
  (multiple-value-bind (preq popt prest pkeyp pkeys)
      (parse-lambda-list-into-components generic-lambda-list)
    (multiple-value-bind (mreq mopt mrest mkeyp mkeys malwky)
	(parse-lambda-list-into-components method-lambda-list)
      (and (= (length preq) (length mreq))    ; required parameters must match
	   (= (length popt) (length mopt))    ; optional parameters must match
	   (cond (pkeyp
		  ;; If generic-function specifies &key, then the method must
		  ;; accept all of the keyword arguments mentioned by the
		  ;; generic-function by either specifying &allow-other-keys,
		  ;; specifying &rest but not &key, or by mentioning all of
		  ;; them explicitly.
		  (if mkeyp
		      (or malwky (subsetp pkeys mkeys :key #'cadr))
		      mrest))
		 ;; If generic-function specifies &rest but not &key, then the
		 ;; method must specify either &rest or &key.
		 (prest (or mrest mkeyp))
		 ;; Otherwise (generic-function specifies neither &rest nor
		 ;; &key) the method must NOT specify either &rest or &key.
		 (t (not (or mrest mkeyp))))
	   ))))

;;; TRANS:*WARN-ON-DEFMETHOD-WITHOUT-DEFGENERIC*
;;;   If this is true and a toplevel global method defining form is encountered
;;;   without a preceding defgeneric (or other method definition) having been
;;;   encountered, signal a warning.

(define-translator-parameter *warn-on-defmethod-without-defgeneric* nil)

(defun generic-function-record-for-defmethod (name &optional env)
  (or (translator-find-generic-function-record name nil env)
      (unless (defined-as-generic-function name env)
	(when (or *warn-on-defmethod-without-defgeneric* *verbose-warnings*)
	  ;; This should probably be a style warning.
	  (warn "Defining method for ~S without preceding ~S."
		name 'defgeneric)))))

(define-principal-function-name METHOD (name)
  (principal-name-of-function-name (second name)))

(defun make-method-name (name qualifiers specializers &optional env)
  (declare (ignore env))
  (list 'method name qualifiers specializers))

(timpl::define-c-function-name-generator METHOD (name prefix)
  (destructuring-bind (fname qualifiers specializers) (cdr name)
    (when (consp fname)
      (setf prefix (sformat "~ASETF_" prefix)
	    fname (second fname)))
    (multiple-value-bind (string case)
	(string-canonicalize-case (string-trim-stars fname))
      (values (string->legal-c-name string case prefix)
	      prefix
	      (make-method-name-suffix qualifiers specializers)
	      case
	      fname))))

(defun make-method-name-suffix (qualifiers specializers)
  (concatenate
       'string
       ;; Need to add leading "__" after conversion to legal C name, since that
       ;; function transforms leading "_".
       "__"
       (string->legal-c-name
	    (format nil "~:[Primary~;~:*~{~:(~A~)~^_~}~]~@[__~{~(~A~)~^_~}~]"
		    qualifiers
		    ;; Remove trailing 'T specializers.
		    (nreverse (member-if #'(lambda (specializer)
					     (not (eq specializer T)))
					 (reverse specializers))))
	    :preserve
	    "")))


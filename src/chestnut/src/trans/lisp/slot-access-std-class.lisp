;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Optimizing slot accesses for standard-class.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

;;; This file contains the methods specialized on standard-class for the
;;; following generic functions:
;;;   ESTABLISH-SLOT-OPTIMIZATION-CONTEXT
;;;   OPTIMIZE-SLOT-VALUE
;;;   OPTIMIZE-SLOT-BOUNDP
;;;   OPTIMIZE-SLOT-EXISTS-P
;;;   OPTIMIZE-SET-SLOT-VALUE
;;;   OPTIMIZE-SLOT-MAKUNBOUND
;;; There are actually two methods defined on each of these functions, one for
;;; standard-class and one for tclos:funcallable-standard-class, since we can't
;;; depend on a common ancestor for these classes in the host environment.

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/slot-access-std-class.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:11 $")

(defmacro specializer-std-class-access-vars (specializer)
  `(getf (specializer-plist ,specializer) 'std-class-access-vars))

(define-translator-type wrapper () 'trun:class-wrapper)

(defun make-std-class-slot-access-bindings (variable specializer)
  (let* ((wrapper (make-variable "~A-WRAPPER" variable))
	 (vars (list wrapper)))
    (setf (specializer-std-class-access-vars specializer) vars)
    (values `((,wrapper (tclos-run:%instance-wrapper ,variable)))
	    vars
	    `((ignorable ,wrapper) (wrapper ,wrapper)))))

(defmacro specializer-std-class-reader/writer-vars (specializer)
  `(specializer-std-class-access-vars ,specializer))

(defmacro specializer-std-class-reader-vars (specializer)
  `(specializer-std-class-reader/writer-vars ,specializer))

(defmacro specializer-std-class-writer-vars (specializer)
  `(specializer-std-class-reader/writer-vars ,specializer))

(macrolet
    ((define-optimize (class)
       `(defmethod establish-slot-optimization-context
	        ((class ,class) variable env continuation)
	  (let ((specializer (specializerp variable env)))
	    (if (null specializer)
		(call-next-method class variable env continuation)
		(multiple-value-bind (bindings variables declspecs)
		    (make-std-class-slot-access-bindings variable specializer)
		  `(let* ,bindings
		     (declare ,@declspecs)
		     ,(call-next-method
		           class
		           variable
		           (translator-augment-environment
			        env
			        :variable variables
			        :declare declspecs)
		           continuation))))))))

  (define-optimize standard-class)
  (define-optimize tclos:funcallable-standard-class)

  )

(defun slot-access-specializer (instance-form env)
  (setf instance-form
	(strip-the (walk:walk-form instance-form :environment env)))
  (and (symbolp instance-form) (specializerp instance-form env)))

(macrolet
    ((define-optimize (class)
       `(defmethod optimize-slot-value
	     ((class ,class)
	      (slotd tclosx:standard-effective-local-slot-definition)
	      form env)
	  (destructuring-bind (instance slot) (cdr form)
	    (let* ((specializer (slot-access-specializer instance env))
		   (type (tclos:slot-definition-type slotd))
		   (index `(slot-index ,(tclos:slot-definition-name slotd))))
	      (cond ((tclosx:elide-access-method-p class slotd :read)
		     (wrap-the `(slot-value--std-class ,instance
				                       ,slot
				                       ,index)
			       type))
		    ((null specializer)
		     (let ((newform (call-next-method)))
		       (if (eq newform form)
			   ;; Don't wrap THE form in this case.  Doing so would
			   ;; cause infinite regress!
			   form
			   (wrap-the newform type))))
		    (t
		     (wrap-the
		        `(slot-value-using-wrapper
			      ,instance
			      ,slot
			      ,@(specializer-std-class-reader-vars specializer)
			      ,index)
			type))))))))

  (define-optimize standard-class)
  (define-optimize tclos:funcallable-standard-class)

  )

(define-translator-macro slot-value--std-class (instance slot-name index)
  `(tclos-run:%slot-value ,instance ,slot-name ,index))

(deftranslate slot-value-using-wrapper (instance slot-name wrapper index)
  (timpl::re-translate-form
    (if (timpl::variable-bound-at-current-function-level wrapper)
	`(tclos-run:%slot-value-using-wrapper
	      ,instance ,slot-name ,wrapper ,index)
	`(tclos-run:%slot-value-indexed ,instance ,slot-name ,index))))

(define-internal-function slot-value-using-wrapper (object slot index wrapper))

(macrolet
    ((define-optimize (class)
       `(defmethod optimize-set-slot-value
	     ((class ,class)
	      (slotd tclosx:standard-effective-local-slot-definition)
	      form env)
	  (destructuring-bind (instance slot value) (cdr form)
	    (let* ((specializer (slot-access-specializer instance env))
		   (slot-type (tclos:slot-definition-type slotd))
		   (type (and-types slot-type
				    (form-type (walk:walk-form value
							       :environment
							       env)
					       env)
				    env))
		   (index `(slot-index ,(tclos:slot-definition-name slotd))))
	      (cond ((tclosx:elide-access-method-p class slotd :write)
		     (wrap-the `(set-slot-value--std-class
				     ,instance
				     ,slot
				     ,(wrap-the value slot-type)
				     ,index)
			       type))
		    ((null specializer)
		     (let ((newform (call-next-method)))
		       (if (eq form newform)
			   ;; Don't wrap the forms here.  Doing so would lead
			   ;; to infinite regress.
			   form
			   (wrap-the newform type))))
		    (t
		     (wrap-the
		        `(set-slot-value-using-wrapper
			      ,instance
			      ,slot
			      ,(wrap-the value slot-type)
			      ,@(specializer-std-class-writer-vars specializer)
			      ,index)
			  type))))))))

  (define-optimize standard-class)
  (define-optimize tclos:funcallable-standard-class)

  )

(define-translator-macro set-slot-value--std-class
    (instance slot-name value index &environment env)
  (if (not (translator-constantp slot-name env))
      (improper-slot-name-for-accessor 'set-slot-value--std-class slot-name)
      `(tclos-run:%set-slot-value ,instance ,value ,index)))

(defun improper-accessor-usage-error (accessor format-string &rest arguments)
  (error "Improper use of ~S -- ~?" accessor format-string arguments))

(defun improper-slot-name-for-accessor (accessor slot-name)
  (improper-accessor-usage-error accessor
				 "slot-name must be a constant: ~S."
				 slot-name))

(deftranslate set-slot-value-using-wrapper
      (instance slot-name value wrapper index)
  (timpl::re-translate-form
       (if (timpl::variable-bound-at-current-function-level wrapper)
	   `(tclos-run:%set-slot-value-using-wrapper
	         ,instance ,slot-name ,value ,wrapper ,index)
	   `(tclos-run:%set-slot-value-indexed
	         ,instance ,slot-name ,value ,index))))

(define-internal-function set-slot-value-using-wrapper
      (object slot value index wrapper))

(macrolet
    ((define-optimize (class)
       `(defmethod optimize-slot-boundp
	     ((class ,class)
	      (slotd tclosx:standard-effective-local-slot-definition)
	      form env)
	  (destructuring-bind (instance slot) (cdr form)
	    (let ((specializer (slot-access-specializer instance env))
		  (index `(slot-index ,(tclos:slot-definition-name slotd))))
	      (cond ((tclosx:elide-access-method-p class slotd :read)
		     `(slot-boundp--std-class ,instance ,slot ,index))
		    ((null specializer) (call-next-method))
		    (t
		     `(slot-boundp-using-wrapper
		           ,instance
		           ,slot
		           ,@(specializer-std-class-reader-vars specializer)
		           ,index))))))))

  (define-optimize standard-class)
  (define-optimize tclos:funcallable-standard-class)

  )

(define-translator-macro slot-boundp--std-class
      (instance slot-name index &environment env)
  (if (translator-constantp slot-name env)
      `(tclos-run:%slot-boundp ,instance ,index)
      (improper-slot-name-for-accessor 'slot-boundp--std-class slot-name)))

(deftranslate slot-boundp-using-wrapper (instance slot-name wrapper index)
  (timpl::re-translate-form
    (if (timpl::variable-bound-at-current-function-level wrapper)
	`(tclos-run:%slot-boundp-using-wrapper ,instance
					       ,slot-name
					       ,wrapper
					       ,index)
	`(tclos-run:%slot-boundp-indexed ,instance ,slot-name ,index))))

(define-internal-function slot-boundp-using-wrapper
      (object slot index wrapper))

(macrolet
    ((define-optimize (class)
       `(defmethod optimize-slot-makunbound
	     ((class ,class)
	      (slotd tclosx:standard-effective-local-slot-definition)
	      form env)
	  (destructuring-bind (instance slot) (cdr form)
	    (let ((specializer (slot-access-specializer instance env))
		  (index `(slot-index ,(tclos:slot-definition-name slotd))))
	      (cond ((tclosx:elide-access-method-p class slotd :write)
		     `(slot-makunbound--std-class ,instance ,slot ,index))
		    ((null specializer) (call-next-method))
		    (t
		     `(slot-makunbound-using-wrapper
		        ,instance
			,slot
			,@(specializer-std-class-writer-vars specializer)
			,index))))))))

  (define-optimize standard-class)
  (define-optimize tclos:funcallable-standard-class)

  )

(deftranslate slot-makunbound--std-class (instance slot-name index)
  (let ((env timpl::*environment*))
    (cond ((not (translator-constantp slot-name env))
	   (improper-slot-name-for-accessor 'slot-makunbound--std-class
					    slot-name))
	  ((not (eq timpl::*context* timpl::*ignore-context*))
	   ;; If *context* is not :ignore, then need to arrange for the proper
	   ;; return value, since tclos-run:%slot-makunbound doesn't
	   ;; return the instance.
	   (let ((expanded (walk:walk-form instance :environment env)))
	     (timpl::re-translate-form
	          (if (symbolp (strip-the expanded))
		      `(progn
		         (tclos-run:%slot-makunbound ,expanded ,index)
		         ,expanded)
		      (let ((ovar (make-variable "OBJECT")))
			`(let ((,ovar ,instance))
			   (tclos-run:%slot-makunbound ,ovar ,index)
			   ,ovar))))))
	  (t
	   (timpl::re-translate-form
	        `(tclos-run:%slot-makunbound ,instance ,index))))))

(define-internal-function slot-makunbound--std-class (object slot index))

(deftranslate slot-makunbound-using-wrapper (instance slot-name wrapper index)
  (timpl::re-translate-form
       (if (eq timpl::*context* timpl::*ignore-context*)
	   `(tclos-run:%slot-makunbound-using-wrapper
	         ,instance ,slot-name ,wrapper ,index)
	   ;; If *context* is not :ignore, then need to arrange for the proper
	   ;; return value, since tclos-run:%slot-makunbound-using-wrapper
	   ;; doesn't return the instance.
	   (let ((expanded (walk:walk-form instance
					   :environment timpl::*environment*)))
	     (if (symbolp (strip-the expanded))
		 `(progn
		    (tclos-run:%slot-makunbound-using-wrapper
		         ,expanded ,slot-name ,wrapper ,index)
		    ,expanded)
		 (let ((ovar (make-variable "OBJECT")))
		   `(let ((,ovar ,instance))
		      (tclos-run:%slot-makunbound-using-wrapper
		           ,ovar ,slot-name ,wrapper ,index)
		      ,ovar)))))))

(define-internal-function  slot-makunbound-using-wrapper
      (object slot index wrapper))

;;; Note that this method only gets invoked when static-class-p is false.

(macrolet
    ((define-optimize (class)
       `(defmethod optimize-slot-exists-p
	     ((class ,class)
	      (slotd tclosx:standard-effective-local-slot-definition)
	      form env)
	  (destructuring-bind (instance slot) (cdr form)
	    (let ((specializer (slot-access-specializer instance env)))
	      (if (null specializer)
		  (call-next-method)
		  `(slot-exists-p-using-wrapper
		        ,instance
		        ,slot
		        ,@(specializer-std-class-reader-vars specializer)
		        (slot-index ,(tclos:slot-definition-name slotd)))
		  ))))))

  (define-optimize standard-class)
  (define-optimize tclos:funcallable-standard-class)

  )

(define-translator-macro slot-exists-p--std-class
      (var slot-name index &environment env)
  (cond ((not (translator-constantp slot-name env))
	 (improper-slot-name-for-accessor 'slot-exists-p--std-class slot-name))
	((not (translator-constantp index env))
	 (improper-accessor-usage-error 'slot-exists-p--std-class
					"index must be a constant: ~S."
					index))
	(t
	 `(let () (progn ,var t)))))

(deftranslate slot-exists-p-using-wrapper (instance slot-name wrapper index)
  (timpl::re-translate-form
    (if (timpl::variable-bound-at-current-function-level wrapper)
	`(tclos-run:%slot-exists-p-using-wrapper ,instance
						 ,slot-name
						 ,wrapper
						 ,index)
	`(tclos-run:%slot-exists-p-indexed ,instance ,slot-name ,index))))

(define-internal-function slot-exists-p-using-wrapper
      (object slot index wrapper))

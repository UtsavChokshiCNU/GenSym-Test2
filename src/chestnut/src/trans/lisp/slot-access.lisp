;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Translating the slot access functions.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/slot-access.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:12 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Translation of the access functions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; The basic routine for all the slot access functions is
;;;
;;; 1. If the class of the object argument can be determined from information
;;; in the environment, and the slot name argument is a constant, try using
;;; the optimizer for the accessor function.  If the optimizer returns a
;;; transformed form, translate that instead of the original form.
;;;
;;; 2. If the optimizer fails to transform but the slot name argument is a
;;; constant with a known global slot index, translate a call to the indexed
;;; accessor function.
;;;
;;; 3. Otherwise, treat the form as a function call.

(defun slot-access-optimization-info (object slot-name env)
  (let ((exp-object (walk:walk-form object :environment env))
	(exp-name (walk:walk-form slot-name :environment env)))
    (multiple-value-bind (value therep)
	(translator-constant-value exp-name env)
      (let ((class (cond ((symbolp exp-object)
			  (class-of-type (variable-type exp-object env) env))
			 ((and (consp exp-object)
			       (eq (first exp-object) 'the))
			  (class-of-type (second exp-object) env))
			 (t nil))))
	(values exp-object
		class
		(and class
		     therep
		     (tclosx:find-effective-slot-definition class value))
		exp-name
		(when therep `(slot-index ,value)))))))

(defun use-indexed-slot-access-p (env)
  (let ((qualities (translator-declaration-information 'optimize env)))
    ;; Use indexed accessors if speed >= space.
    (<= (cadr (assoc 'space qualities)) (cadr (assoc 'speed qualities)))))

(defun translate-slot-access (form env &optional index indexed-function)
  (if (and index (use-indexed-slot-access-p env))
      (timpl::re-translate-form `(,indexed-function ,@(cdr form) ,index))
      (timpl::translate-function-call form)))

(define-translator-macro slot-index (slot-name &environment env)
  (global-slot-index slot-name env))

(macrolet ((define-slot-access (name optimizer indexed)
	     `(deftranslate ,name (&whole form object slot-name)
		(let ((env timpl::*environment*))
		  (multiple-value-bind (exp-object class slotd name index)
		      (slot-access-optimization-info object slot-name env)
		    (when (and index class slotd)
		      (let* ((exp-form (list ',name exp-object name))
			     (newform (,optimizer class slotd exp-form env)))
			(when (not (eq newform exp-form))
			  (return-from ,name (timpl::re-translate-form newform)))))
		    (translate-slot-access form env index ',indexed))))))

  (define-slot-access slot-boundp
                      optimize-slot-boundp
                      tclos-run:%slot-boundp-indexed)
  
  (define-slot-access slot-makunbound
                      optimize-slot-makunbound
                      tclos-run:%slot-makunbound-indexed)

  )

(deftranslate slot-exists-p (&whole form object slot-name)
  (let ((env timpl::*environment*))
    (multiple-value-bind (exp-object class slotd name index)
	(slot-access-optimization-info object slot-name env)
      (when (and index class)
	(when slotd
	  (let* ((exp-form (list 'slot-exists-p exp-object name))
		 (newform (optimize-slot-exists-p class slotd exp-form env)))
	    (when (not (eq newform exp-form))
	      (return-from slot-exists-p (timpl::re-translate-form newform)))))
	;; When the class and slot-name are known but the slot is not present
	;; in the specified class, if the class is static and non of its direct
	;; or indirect subclasses provides the slot either then transform into
	;; a progn that evaluates the arguments and returns Nil.
	(when (and (static-class-p class)
		   (do ((table (make-hash-table :test 'eq))
			(name (translator-constant-value name env))
			(pending (tclos:class-direct-subclasses class)))
		       ((endp pending) t)
		     (let ((c (pop pending)))
		       (unless (gethash c table)
			 (if (tclosx:find-effective-slot-definition c name)
			     (return nil)
			     (setf pending
				   (append (tclos:class-direct-subclasses c)
					   pending)))))))
	  (return-from slot-exists-p
	    (timpl::re-translate-form `(progn ,object ,slot-name nil)))))
      (translate-slot-access form
			     env
			     index
			     'tclos-run:%slot-exists-p-indexed))))

(timpl::define-local-temp-emitter tclos-run:%slot-value (key)
  (declare (ignore key))
  (timpl::emit-newline-indent)
  (timpl::emit-string "Declare_slot_value;"))

(deftranslate slot-value (&whole form object slot-name)
  (let ((env timpl::*environment*))
    (multiple-value-bind (exp-object class slotd name index)
	(slot-access-optimization-info object slot-name env)
      (when slotd
	(let* ((exp-form (list 'slot-value exp-object name))
	       (newform (optimize-slot-value class slotd exp-form env)))
	  (return-from slot-value
	    (if (not (eq newform exp-form))
		(timpl::re-translate-form newform)
		(multiple-value-bind (statements result-form result-type temps)
		    (translate-slot-access
		         form env index 'tclos-run:%slot-value-indexed)
		  (values statements
			  result-form
			  (and-types (tclos:slot-definition-type slotd)
				     (single-value-type result-type env)
				     env)
			  temps))))))
      (translate-slot-access form env index 'tclos-run:%slot-value-indexed))))

(deftranslate trun:set-slot-value (&whole form object slot-name value)
  (let ((env timpl::*environment*))
    (multiple-value-bind (exp-object class slotd name index)
	(slot-access-optimization-info object slot-name env)
      (when slotd
	(let* ((type (tclos:slot-definition-type slotd))
	       (exp-form `(trun:set-slot-value ,exp-object
			                       ,name
			                       ,(wrap-the value type)))
	       (newform (optimize-set-slot-value class slotd exp-form env)))
	  (return-from trun:set-slot-value
	    (if (not (eq newform exp-form))
		(timpl::re-translate-form newform)
		(multiple-value-bind (statements result-form result-type temps)
		    (translate-slot-access
		         exp-form env index 'tclos-run:%set-slot-value-indexed)
		  (values statements
			  result-form
			  (and-types (tclos:slot-definition-type slotd)
				     (single-value-type result-type env)
				     env)
			  temps))))))
      (translate-slot-access
           form env index 'tclos-run:%set-slot-value-indexed))))

(deftranslate tclos-run:%slot-makunbound-indexed
    (&whole form object slot-name index)
  (let ((env timpl::*environment*))
    (if (eq timpl::*context* timpl::*ignore-context*)
	(translate-slot-access form env)
	;; If *context* is not :ignore, then need to arrange for the proper
	;; return value, since tclos-run:%slot-makunbound-indexed doesn't
	;; return the instance.
	(let ((expanded (walk:walk-form object :environment env)))
	  (timpl::re-translate-form
	       (if (let ((stripped (strip-the expanded)))
		     (or (symbolp stripped)
			 (translator-constantp stripped env)))
		   `(progn
		      (tclos-run:%slot-makunbound-indexed ,expanded
		                                          ,slot-name
							  ,index)
		      ,expanded)
		   (let ((ovar (make-variable "OBJECT")))
		     `(let ((,ovar ,object))
			(tclos-run:%slot-makunbound-indexed ,ovar
							    ,slot-name
							    ,index)
			,ovar))))))))
      
(translator-defsetf tclosx:standard-object-ref
  :type :l-value
  :access-fn-arg-count 2
  :update-fn tclos-run:set-standard-object-ref
  :doc
  "The setf method for STANDARD-OBJECT-REF.")

(define-translator-setf-method slot-value (access-form env)
  (if (eq (car access-form) 'apply)
      (get-applied-slot-value-setf access-form env)
      (get-slot-value-setf access-form env)))

;;; *** This could be improved.

(defun get-applied-slot-value-setf (access-form env)
  (declare (ignore access-form env))
  (unknown-apply-of-place-error 'slot-value))

;;; This is kind of gross, but it works.  There are several problems that this
;;; addresses.
;;;
;;;   1. If the slot-name is a constant form, we want the access and update
;;;   forms to contain a reference to the constant rather than to a temp
;;;   variable bound to the value of the constant form.  Without this, indexed
;;;   slot accesses can't be generated.  Now that the implementation of setf
;;;   methods can be relied upon to remove temps bound to constant forms, this
;;;   isn't actually a problem.
;;;
;;;   2. We want certain declarations on the object form to be propogated to
;;;   the associated temp variable.  Type declarations should always be
;;;   propogated.
;;;
;;;   3. As a special case, if the object form is a reference to a specializer,
;;;   no temp variable is needed, since specializer variables are guaranteed to
;;;   be unmodified (the code which introduces a specializer declaration is
;;;   responsible for detecting any modifications and redoing macroexpansions
;;;   without the presence of a specializer on the offending variable).

(defun get-slot-value-setf (access-form env)
  (destructuring-bind (object slot-name) (cdr access-form)
    (let ((temps ())
	  (values ())
	  (arglist ())
	  (declarations ())
	  (store (make-setf-method-temp-var "NEW-VALUE")))
      ;; Generate temp for slot-name.
      ;; *** Note: This assumes that implementation of setf methods will
      ;; *** remove unnecessary temps bound to constants, so that if the
      ;; *** slot-name is a constant then the references in the setter and
      ;; *** getter forms will be to the constant rather than to a temp.
      ;; *** The translator's implementation of setf methods does in fact do
      ;; *** this for us.
      (let ((temp (make-setf-method-temp-var "SLOT-NAME")))
	(push temp arglist)
	(push temp temps)
	(push slot-name values))
      (multiple-value-bind (expanded type)
	  (strip-the (walk:walk-form object :environment env) env)
	(let ((specializer (and (symbolp expanded)
				(specializerp expanded env))))
	  (if specializer
	      ;; If object form is a reference to a specialized variable, then
	      ;; no temp is needed.  Just use the object form as the first arg.
	      (push object arglist)
	      ;; Not a specialized variable, so generate a temp to be bound to
	      ;; the value of the object form.
	      (let ((ovar (make-setf-method-temp-var "OBJECT")))
		(push object values)
		(push ovar temps)
		(push ovar arglist)
		;; Propagate type information from the object form to the temp.
		(setf type (and-types type (form-type expanded env) env))
		(setf type (single-value-type type env))
		(unless (eq type T)
		  (push `(type ,type ,ovar) declarations)))))
	(values temps
		values
		(list store)
		(if (null declarations)
		    `(trun:set-slot-value ,@arglist ,store)
		    `(locally
		       (declare ,@declarations)
		       (trun:set-slot-value ,@arglist ,store)))
		(if (null declarations)
		    `(slot-value ,@arglist)
		    `(locally
		       (declare ,@declarations)
		       (slot-value ,@arglist))))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Optimizing slot accesses
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defgeneric OPTIMIZE-SLOT-VALUE (class slotd form env)
  (:generic-function-class translator-generic-function)
  (:documentation
   "This generic-function is called to optimize calls to the SLOT-VALUE
function when the type of the object being accessed can be infered from
declarations or other information.  It can either return a new form which will
presumably result in a faster access, or the original form unchanged (meaning
that no optimization was done)."))

(defgeneric OPTIMIZE-SLOT-BOUNDP (class slotd form env)
  (:generic-function-class translator-generic-function)
  (:documentation
   "This generic-function is called to optimize calls to the SLOT-BOUNDP
function when the type of the object being accessed can be infered from
declarations or other information.  It can either return a new form which will
presumably result in a faster access, or the original form unchanged (meaning
that no optimization was done)."))

(defgeneric OPTIMIZE-SET-SLOT-VALUE (class slotd form env)
  (:generic-function-class translator-generic-function)
  (:documentation
   "This generic-function is called to optimize calls to the SET-SLOT-VALUE
function when the type of the object being accessed can be infered from
declarations or other information.  It can either return a new form which will
presumably result in a faster update, or the original form unchanged (meaning
that no optimization was done)."))

(defgeneric OPTIMIZE-SLOT-MAKUNBOUND (class slotd form env)
  (:generic-function-class translator-generic-function)
  (:documentation
   "This generic-function is called to optimize calls to the SLOT-MAKUNBOUND
function when the type of the object being accessed can be infered from
declarations or other information.  It can either return a new form which will
presumably result in a faster update, or the original form unchanged (meaning
that no optimization was done)."))

(defgeneric OPTIMIZE-SLOT-EXISTS-P (class slotd form env)
  (:generic-function-class translator-generic-function)
  (:documentation
   "This generic-function is called to optimize calls to the SLOT-EXISTS-P
function when the type of the object being accessed can be infered from
declarations or other information.  It can either return a new form which will
presumably result in a faster test, or the original form unchanged (meaning
that no optimization was done)."))

;;; The following :AROUND methods for each of the optimize generic-functions
;;; are specialized on the classes CLASS and EFFECTIVE-SLOT-DEFINITION and
;;; provide the following functionality:
;;;
;;; * Prevent optimization when improper number of arguments to the function.
;;;
;;; Note that these methods assume the existance of the primary methods defined
;;; below (along with any metaclass specific methods), since these methods
;;; blindly call CALL-NEXT-METHOD, rather than first calling NEXT-METHOD-P to
;;; ensure the presence of a next method to call.
;;;
;;; At one time I thought that these methods should also just return the form
;;; if elide-access-method-p returned false.  I have since decided that whether
;;; to call elide-access-method-p or not should be determined by the specific
;;; optimizer methods.  The reason is that an optimizer method might generate
;;; code that makes use of runtime calls to elide-access-method-p to decide
;;; whether to do an inline access or call the generic function.

(macrolet ((define-base-around-optimize-method (name length)
	     (check-type length (integer 3))
	     `(defmethod ,name :around
	           ((class class)
		    (slotd tclosx:effective-slot-definition)
		    form env)
		(declare (ignore env))
		(if (/= (length form) ,length)
		    form
		    (call-next-method)))))

  (define-base-around-optimize-method optimize-slot-value 3)
  (define-base-around-optimize-method optimize-slot-boundp 3)
  (define-base-around-optimize-method optimize-set-slot-value 4)
  (define-base-around-optimize-method optimize-slot-makunbound 3)

  )

;;; This method prevents optimization when the wrong number of arguments are
;;; supplied, and transforms into a trivial progn returning true when the class
;;; is static, since the slot must exist in that case.

(defmethod optimize-slot-exists-p :around
    ((class class)
     (slotd tclosx:effective-slot-definition)
     form
     env)
  (declare (ignore env))
  (cond ((/= (length form) 3) form)
	((static-class-p class) `(let () (progn ,@(cdr form) t)))
	(t (call-next-method))))

;;; The following methods for each of the optimize generic-functions are
;;; specialized on the classes CLASS and EFFECTIVE-SLOT-DEFINITION and provide
;;; the following functionality:
;;;
;;; * Provide a bottoming out point for the slot access optimizations.

(macrolet ((define-base-primary-optimize-method (name)
	     `(defmethod ,name ((class class)
				(slotd tclosx:effective-slot-definition)
				form
				env)
		(declare (ignore env))
		form)))

  (define-base-primary-optimize-method optimize-slot-value)
  (define-base-primary-optimize-method optimize-slot-boundp)
  (define-base-primary-optimize-method optimize-set-slot-value)
  (define-base-primary-optimize-method optimize-slot-makunbound)
  (define-base-primary-optimize-method optimize-slot-exists-p)

  )

(defgeneric ESTABLISH-SLOT-OPTIMIZATION-CONTEXT
    (class variable env continuation)
  (:generic-function-class translator-generic-function)
  (:documentation
   "This generic-function is used to optimize calls to slot access functions
within a specific context.  Continuation is a function of one argument, an
environment, and returns a form in which slot accesses have been optimized.
Methods on this generic-function should use CALL-NEXT-METHOD with an
environment which has been augmented to contain data which is used to pass
information between the method and methods on the specific slot access
optimizers.  The primary method specialized on the class CLASS provides the
functionality of calling the continuation function and returning its results.")
  )

(defmethod establish-slot-optimization-context
    ((class class) variable env continuation)
  (declare (ignore variable))
  (funcall continuation env))


;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Translation time definition of functions related to FIND-CLASS.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/find-class.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:05 $")

(defun ensure-legal-class-name (name)
  (or (and (symbolp name)
	   (not (null name)))
      (error "~S is not a valid class name." name)
      ;(error 'simple-type-error
      ;	     :datum name
      ;	     :expected-type '(and symbol (not null))
      ;	     :format-control "~S is not a valid class name."
      ;	     :format-arguments (list name))
      ))

(defun class-for-redefinition (name &optional environment)
  (setf environment (coerce-to-environment environment))
  (or (translator-find-class name nil environment)
      (find-class name nil)))

;;; Return a class object based on the argument.  If it is already a class
;;; object, simply return it.  If it is a class name, use find-class to
;;; get the class, and then ensure that it is of the proper type.
(defun coerce-to-class (class-or-name &optional (errorp t) env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (flet ((require-class (object env errorp)
	   (cond ((translator-typep object 'class env) object)
		 (errorp
		  (error "~S is not a known translator class." object 'class))
		 (t object))))
    (if (symbolp class-or-name)
	(let ((class (translator-find-class class-or-name errorp env)))
	  (when class (require-class class env errorp)))
	(require-class class-or-name env errorp))))

(defun valid-specializer-p (specializer &optional env)
  (if (consp specializer)
      (and (eq (car specializer) 'eql)
	   (consp (cdr specializer))
	   (null (cddr specializer)))
      (and (coerce-to-class specializer nil env) t)))

(defun translator-find-class-or-forward-reference (name env)
  (setf env (coerce-to-environment env))
  (or (translator-find-class name nil env)
      (translator-find-forward-referenced-class name env t)))

(define-translator-property defined-as-forward-referenced-class #'identity)

(defun translator-find-forward-referenced-class (name env createp)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (or (defined-as-forward-referenced-class name env)
      (when createp
	(setf (defined-as-forward-referenced-class name env)
	      (make-translator-forward-referenced-class name env)))))

(defun translator-remove-forward-referenced-class (name env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (translator-environment-remprop name
				  env
				  'defined-as-forward-referenced-class))

;;; CLASS-OF-TYPE
;;;
;;; Try to return the class metaobject that most closely describes the type
;;; specifier argument.  The class returned satisfies the following constraint:
;;;
;;;   if R is the class returned and T is the type specifier argument, then
;;;   there does not exist a class C /= R such that (subtypep T C) and
;;;   (subtypep C R).
;;;
;;; If a class that satisfies the specified constraint can't be identified,
;;; returns Nil instead.
;;;
;;; *** This function could be made much more complete and powerful.

(defun class-of-type (type-spec &optional env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (and (translator-type-specifier-p type-spec env)
       (cond ((symbolp type-spec)
	      (translator-find-class type-spec nil env))
	     ((consp type-spec) nil)
	     (t type-spec))))

(defun proper-class-name (thing &optional env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (cond ((symbolp thing) thing)
	((translator-typep thing 'class env)
	 (let ((name (tclos:class-name thing)))
	   (if (or (null name)
		   (not (eq thing (translator-find-class name nil env))))
	       ;; If class is unnamed, or does not have a proper name, then
	       ;; just return the class.
	       thing
	       ;; Otherwise, return the proper name.
	       name)))
	(t
	 (error "Cannot determine a class name for ~S." thing))))

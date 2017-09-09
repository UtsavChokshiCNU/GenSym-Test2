;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/ensure-generic-function.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:05 $")

;;; ENSURE-GENERIC-FUNCTION {88-002R}
;;;  :lambda-list		{expected type}
;;;  :argument-precedence-order {expected type}
;;;  :declare			{expected type}
;;;  :documentation		{expected type}
;;;  :generic-function-class	class or class name
;;;  :method-combination	method-combination object
;;;  :method-class		class or class name
;;;  :environment		syntactic environment
;;;
;;; Generic Function Initialization {Metaobject Protocol, 6/6/90}
;;;  :lambda-list
;;;  :argument-precedence-order
;;;  :documentation
;;;  :method-combination
;;;  :method-class
;;;
;;;  :initial-methods
;;;
;;;  :declarations
;;;
;;;  :generic-function-class
;;;  :environment
;;;
;;; Arguments must presumably be of the appropriate types.
;;;
;;; ENSURE-GENERIC-FUNCTION {Metaobject Protocol, 6/6/90}
;;;  :environment
;;;
;;; ENSURE-GENERIC-FUNCTION-USING-CLASS {Metaobject Protocol, 6/6/90}
;;;  :generic-function-class
;;;  :environment
;;;
;;; Nothing is said about argument coercions.  Arguments are passed directly
;;; to initialization.

(defun translator-ensure-generic-function
       (name &rest initargs
	     &key (lambda-list (required-keyword :lambda-list))
	          (generic-function-class nil gf-class-p)
		  (method-class nil method-class-p)
		  (documentation nil docp)
		  ((:environment env) nil)
	     &allow-other-keys)
  (ensure-legal-function-name name)
  (setf initargs (copy-list initargs))
  (setf initargs (nstrip-keylist initargs :environment))
  (setf env (coerce-to-environment env))
  (cond ((not gf-class-p)
	 (setf generic-function-class
	       (translator-find-class 'standard-generic-function)))
	(t
	 (setf generic-function-class
	       (or (coerce-to-class generic-function-class nil env)
		   (progn
		     (warn "~S for ~S not recognized as a class name: ~S.~@
                            Using ~S instead."
			   :generic-function-class name generic-function-class
			   'standard-generic-function)
		     (translator-find-class 'standard-generic-function))))
	 (setf initargs (nstrip-keylist initargs :generic-function-class))
	 (setf initargs
	       `(:generic-function-class ,generic-function-class ,@initargs))))
  (when method-class-p
    (setf method-class
	  (or (coerce-to-class method-class nil env)
	      (progn
		(warn "~S for ~S not recognized as a class name: ~S."
		      :method-class name method-class)
		method-class)))
    (setf initargs (nstrip-keylist initargs :method-class))
    (setf initargs `(:method-class ,method-class ,@initargs)))
  (let ((record (generic-function-record name env)))
    ;; Permit other keys so that translation time generic function records
    ;; aren't required to accept all the initargs that the generic function
    ;; accepts at runtime.
    (if (null record)
	(setf (generic-function-record name env)
	      (setf record
		    (apply #'make-instance 'generic-function-record
			   :name name
			   :lambda-list lambda-list
			   :generic-function-class generic-function-class
			   :allow-other-keys t
			   initargs)))
	(apply #'reinitialize-instance record
	       :name name
	       :lambda-list lambda-list
	       :allow-other-keys t
	       initargs))
    (unless docp
      (setf documentation (generic-function-record-documentation record)))
    (timpl::redefine-function name
			      (lambda-list-for-redefinition lambda-list)
			      :documentation documentation
			      :generic-function-p record)))

(defun ensure-legal-function-name (name)
  (or (valid-function-name-p name)
      (error "~S is not a valid function name." name)))

(defun lambda-list-for-redefinition (lambda-list)
  (multiple-value-bind (required optional rest keyp)
      (parse-lambda-list-into-components lambda-list)
    (flet ((augment-arglist (head arglist)
	     (if (null arglist) head
		 (append head arglist)))
	   ;; If &key specified, the set of allowable keywords cannot be
	   ;; determined from the generic-function alone, so permit any
	   ;; keyword specifiers.  Otherwise, use &rest if appropriate.
	   (arglist-tail (rest keyp)
	     (cond (keyp '(&key &allow-other-keys))
		   (rest `(&rest ,rest))
		   (t nil))))
      (augment-arglist
       required
       (if (null optional)
	   (arglist-tail rest keyp)
	   (cons '&optional
		 (augment-arglist
		  optional
		  (arglist-tail rest keyp))))))))


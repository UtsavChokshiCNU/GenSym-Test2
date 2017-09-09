;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Initialization and update of translator class information.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/ensure-translator-class.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:05 $")

;;; The variable *use-remote-classes* is used to control whether the
;;; translation of a defclass will execute the defclass form in the host
;;; environment (using eval-when).  There are various other places that are
;;; conditionalized based on whether they need the execution of the host
;;; defclass form.  The principal place where this matters is in
;;; ensure-translator-class, in which the usage determines the necessary value
;;; for the current host.
(eval-when (compile load eval)

(defparameter *use-remote-classes*
  #+(or LCL4.0 ALLEGRO MCL Genera LispWorks)            t
  #-(or LCL4.0 ALLEGRO MCL Genera LispWorks)
  (error "Must specify a value for ~S." '*use-remote-classes*))

  )

;;; Initialize or update the translator's information about the class.

(defun ensure-translator-class
       (name &key (metaclass 'standard-class metaclassp)
	          (direct-superclasses nil)
	          (direct-slots nil)
		  ((:environment env) nil)
	     &allow-other-keys)
  (setf env (coerce-to-environment env))    ; name => env
  (let (#+genera (metaclass-name metaclass)
	(class (class-for-redefinition name env)))
    (setf metaclass (find-metaclass metaclass env))
    (cond (class
	   (unless (eq (class-of class) metaclass)
	     #+LispWorks
	     (when (forward-referenced-class-p class)
	       (change-class class metaclass))
	     ;; If the metaclasses don't match, signal an warning.  We can't
	     ;; reasonably expect calls to change-class on class metaobjects to
	     ;; be portable.
	     #-LispWorks
	     (when (and metaclassp
			(not *building-initial-class-hierarchy*))
	       (warn "Cannot change metaclass of class ~S to ~S."
		     class metaclass))))
	  ((setf class
		 (translator-find-forward-referenced-class name env nil))
	   ;; class-record will get changed further down.
	   (translator-remove-forward-referenced-class name env)
	   (change-class class metaclass))
	  ;; When we don't already have a class object available, allocate a
	  ;; new one.  This is conditionalized on *use-remote-classes* since
	  ;; it might not be possible to call allocate-instance like this in
	  ;; some implementations.  If that is the case then
	  ;; *use-remote-classes* should be false, and the expansion for
	  ;; defclass will include an eval-when (compile) that will define the
	  ;; class in the host environment.
	  (*use-remote-classes*
	   (setf class (allocate-instance metaclass))
	   #+genera
	   (if (eq metaclass-name 'structure-class)
	       (setf (slot-value class 'clos-internals::name) name)
	       (setf (slot-value class 'clos-internals::bits) 0
		     (class-name class) name))
           #+lcl4.1
           (setf (slot-value class 'clos::name) name)
	   #-(or genera lcl4.1)
	   (setf (class-name class) name))
	  (t
	   (error "No class named ~S found in translator environment."
		  name)))
    (setf (defined-as-class name env) class)
    ;; Transform the superclass list into a list of class metaobjects.
    (setf direct-superclasses
	  (mapcar #'(lambda (c)
		      (if (typep c 'class) c
			  (translator-find-class-or-forward-reference c env)))
		  ;; If no direct supers specified, default based on metaclass.
		  (or direct-superclasses
		      ;; Ensure that T doesn't get any supers.
		      (when (not (eq class (defined-as-class t env)))
			(tclosx:class-default-superclasses
			     (tclos:class-prototype metaclass))))))
    ;; Validate the superclasses.
    (dolist (super direct-superclasses)
      (or (tclosx:validate-superclass class super)
	  (error "~S is not a valid superclass for ~S." super class)))
    ;; Transform the canonic slot specifications into direct slot definition
    ;; metaobjects.
    (setf direct-slots
	  (mapcar #'(lambda (s)
		      (compute-direct-slot-definition class s))
		  direct-slots))
    ;; Create or update the class-record associated with the class.
    (with-class-record (record class nil)
      (if (null record)
	  (setf (class-record class env)
		(make-instance 'class-record
			       :name name
			       :metaclass metaclass
			       :related-class class
			       :direct-superclasses direct-superclasses
			       :direct-slots direct-slots))
	  (reinitialize-instance record
				 :name name
				 :metaclass metaclass
				 :related-class class
				 :direct-superclasses direct-superclasses
				 :direct-slots direct-slots)))))

(defun find-metaclass (metaclass &optional env)
  (setf env (coerce-to-environment env))
  (labels ((find-named-class (name)
	     (let ((host-class (find-class name nil))
		   (translator-class (translator-find-class name nil env)))
	       (cond ((null host-class)
		      (undefined-metaclass-error name :host))
		     ((and (null translator-class)
			   ;; For bootstrapping
			   (not (eq metaclass 'standard-class)))
		      (undefined-metaclass-error name :translator))
		     (t
		      (unless (eq host-class translator-class)
			;; *** Maybe the class record for translator-class
			;; *** should be copied in this case?
			)
		      host-class))))
	   (undefined-metaclass-error (name place)
	     (error "Class ~S is not defined in the ~(~A~) environment."
		    name place)))
    (when (symbolp metaclass) (setf metaclass (find-named-class metaclass)))
    (if (subtypep metaclass 'class)
	metaclass
	(error "Class ~S is not a subtype of ~S." metaclass 'class))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Methods for maintaining class-records for forward-referenced-classes
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun make-translator-forward-referenced-class (name env)
  (let ((class (make-forward-referenced-class-internal name)))
    (setf (class-record class env)
	  (make-instance 'class-record
			 :name name
			 :related-class class
			 ;; For compatibility with runtime.
			 :direct-superclasses (list (find-class t))
			 :direct-slots ()
			 ))
    class))

;;; This function takes a class name and returns a forward-referenced-class
;;; with the specified name.
(defun make-forward-referenced-class-internal (name)
  #+(or LCL4.0 ALLEGRO Genera LispWorks)
  (let ((class (make-instance 'tclos:forward-referenced-class)))
    (setf (class-name class) name)
    class)
  #-(or LCL4.0 ALLEGRO Genera LispWorks)
  (error "Translator does not know how to make instances of ~S for this host."
	 'tclos:forward-referenced-class)
  )

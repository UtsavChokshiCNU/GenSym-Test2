;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Slot initfunctions.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

;; External references:
;;  TRANSLATOR-CONSTANTP
;;  WALK:WALK-FORM

;; Runtime library
;;  TRUN:CONSTANT-INITFUNCTION
;;  TRUN:CONSTANTLY-NIL-INITFUNCTION
;;  TRUN:CONSTANTLY-T-INITFUNCTION

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/initfunctions.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:07 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Slot initfunctions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; We want to avoid generating a seperate initfunction for each slot, since
;;; many initforms will be equivalent (this is especially true when the
;;; initform has a constant value).  However, doing a really complete job of
;;; this is pretty hard (probably impossible except for fairly trivial cases).
;;; Instead, we only recognize the simple case of a constant right now.  This
;;; is the case that gives us the largest single benefit anyway.

;;; Returns two values, the first being a form which can be evaluated to
;;; produce the initfunction, and a second value which is true if the value
;;; returned by the function is a constant (ie. the form has a constant value).
;;; The second value is pessimistic, since it cannot in general be determined
;;; that a form will have a constant value, but we do try.

(defun MAKE-INITFUNCTION-FORM (form environment &optional slot-name)
  (setf environment (coerce-to-environment environment))
  (when (null environment) (setf environment *default-global-environment*))
  (let ((walked (walk:walk-form form :environment environment)))
    (if (translator-constantp walked environment)
	(values (constant-initfunction-form walked environment slot-name) t)
	(values (random-initfunction-form form environment slot-name) nil))))

(defun constant-initfunction-form (form env &optional slot-name)
  (declare (ignore slot-name))
  (multiple-value-bind (value therep)
      (translator-constant-value form env)
    (cond ((and therep (null value))
	   '(initfunction trun:constantly-nil-initfunction))
	  ((and therep (eq value t))
	   '(initfunction trun:constantly-t-initfunction))
	  (t
	   `(trun:constant-initfunction ,form)))))

(defun random-initfunction-form (form env &optional slot-name)
  (declare (ignore env))
  (let ((name (make-initfunction-name slot-name)))
    `(flet ((,name () ,form)) (initfunction ,name))))

(defun make-initfunction-name (&optional slot-name)
  (make-name "~@[~A-~]INITFUNCTION" slot-name))

(define-translator-macro initfunction (name)
  `(function ,name))

(defmacro with-translate-time-initfunctions (&body body)
  `(macrolet ((initfunction (name) `',name)
              (trun:constant-initfunction (form) `'(lambda () ,form)))
    ,@body))

;;; The following functions need to be in the runtime system.
;;;  TRUN:CONSTANT-INITFUNCTION
;;;  TRUN:CONSTANTLY-NIL-INITFUNCTION
;;;  TRUN:CONSTANTLY-T-INITFUNCTION
;
;(defun trun:constantly-t-initfunction ()
;  t)
;
;(defun trun:constantly-nil-initfunction ()
;  nil)
;
;;; CONSTANT-INITFUNCTION is a lot like CONSTANTLY, but the returned function
;;; doesn't need to accept any arguments and it is a good idea to cache the
;;; functions so that only one function per value will ever be generated.  Such
;;; caching might not be a good idea for CONSTANTLY, since then function and
;;; value cannot be GC'ed (assuming that a weak caching mechanism isn't
;;; available).  For initfunctions this isn't such an issue because classes
;;; tend to be pretty long lived and unchanging, so the value and initfunction
;;; are not likely to be available for GC.
;
;(defvar *constant-initfunctions*)
;
;(defun trun:constant-initfunction (value)
;  ;; Initialize table first time through.
;  (unless (boundp '*constant-initfunctions*)
;    (let ((table (make-hash-table :test 'eql)))
;      (setf (gethash nil table) #'trun:constantly-nil-initfunction)
;      (setf (gethash t table) #'trun:constantly-t-initfunction)
;      (setf *constant-initfunctions* table)))
;  ;; Use corresponding function from the table if one exists.
;  (or (gethash value *constant-initfunctions*)
;      ;; Otherwise, cons up a closure over the value, record it in the table
;      ;; for later calls, and return the closure.
;      (setf (gethash value *constant-initfunctions*)
;	    ;; Hopefully, any compiler smart enough to optimize away this
;	    ;; binding will also be smart enough to recognize that the bound
;	    ;; value is closed over and avoid closing over the outer binding
;	    ;; by actually not optimizing away this binding.
;	    (let ((value value)) #'(lambda () ,value)))))


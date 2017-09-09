;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; sbcl-1-0-10-syms.lisp -- host compatibility functions
;;;
;;; starting point mac-2-0-defs.lisp
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/host/sbcl-1-0-10-defs.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2009/04/11 00:00:00 $")

#-SBCL
#.(error "Attempting to use incorrect host database.
This file is for SBCL 1.0.10")

(defmacro hostx:with-dynamic-area (&body forms)
  `(progn ,@forms))

;Can't do this in SBCL either.
(defmacro hostx:with-static-area (&body forms)
  `(progn ,@forms))

;; string-char

(deftype hostx:string-char ()
  'character)

;;;From http://www.sbcl.org/manual/Defining-Constants.html#Defining-Constants
(defmacro host:define-constant (name value &optional doc)
  `(host:defconstant ,name (if (boundp ',name) (symbol-value ',name) ,value)
                           ,@(when doc (list doc))))

(defmacro hostx:define-setf-method (&rest stuff)
  `(host:define-setf-expander ,@stuff))

(defun hostx:enclose (lambda-expression &optional env)
  (declare (ignore lambda-expression env))
  (error "Not implemented."))

(defun hostx:augment-environment (env &optional options)
  (declare (ignore env options))
  (error "Not implemented."))

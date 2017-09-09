;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; sbcl-1-0-52-syms.lisp -- host compatibility functions
;;;
;;; starting point sbcl-1-0-10-defs.lisp
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/host/sbcl-1-0-52-defs.lisp,v $"
 "$Revision: 1.0 $"
 "$Date: 2011/12/12 00:00:00 $")

#-SBCL
#.(error "Attempting to use incorrect host database.
This file is for SBCL 1.0.52")

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

(defmacro hostx:get-setf-method (form &optional env)
  `(host:get-setf-expansion ,form ,env))

(defmacro hostx:get-setf-method-multiple-value (form &optional env)
  `(host:get-setf-expansion ,form ,env))

(defun host:file-namestring (pathname)
  (let* ((real-pathname (pathname pathname))
         (file-pathname (make-pathname :device nil
                                       :directory nil
                                       :defaults real-pathname)))
    (host:namestring file-pathname)))

;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; lispworks-3-defs.lisp -- host compatibility functions for LispWorks
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/lispworks-3-defs.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006-02-28 21:58:59 $")

#-(or LISPWORKS3.1 LispWorks4)
#.(error "Attempting to use incorrect host database.
This file is for Harlequin Common Lisp version 3.1.")

;(define-condition simple-program-error (simple-condition program-error) ())
;    
;(defun simple-program-error (format-control &rest arguments)
;  (error 'simple-program-error
;	   :format-control format-control
;	   :format-arguments arguments))


(deftype base-char () 'common-lisp::base-character)
(deftype extended-char () 'common-lisp::extended-character)

			      
;;; PARSE-ERROR

(define-condition HOST:PARSE-ERROR (error) ())
  
;;; SIMPLE-CONDITION-FORMAT-CONTROL

(defun HOST:SIMPLE-CONDITION-FORMAT-CONTROL (c)
  (lisp:simple-condition-format-string c))


;;; renamed SETF stuff

(defmacro host:define-setf-expander (&rest stuff)
  `(lisp:define-setf-method ,@stuff))

(defun host:get-setf-expansion (form &optional env)
  (lisp:get-setf-method-multiple-value form env))


;;; renamed special-form-p

(defun host:special-operator-p (thing)
    (lisp:special-form-p thing))


;;; things with environment arguments added

(defun host:constantp (thing &optional env)
    (declare (ignore env))
    (lisp:constantp thing))

(defun host:typep (thing type &optional env)
    (declare (ignore env))
    (lisp:typep thing type))

(defun host:subtypep (type1 type2 &optional env)
    (declare (ignore env))
    (lisp:subtypep type1 type2))

(defmacro hostx:with-dynamic-area (&body forms)
  `(progn ,@forms))

(defmacro hostx:with-static-area (&body forms)
  `(progn ,@forms))

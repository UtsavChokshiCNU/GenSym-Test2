;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; lispworks-3-defs.lisp -- host compatibility functions for LispWorks
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/lispworks-5-defs.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2009-04-05 22:38:00 $")

#-(or LispWorks5 LispWorks6)
#.(error "Attempting to use incorrect host database.
This file is for LispWorks 5 & 6.")

;(define-condition simple-program-error (simple-condition program-error) ())
;    
;(defun simple-program-error (format-control &rest arguments)
;  (error 'simple-program-error
;	   :format-control format-control
;	   :format-arguments arguments))

;;; things with environment arguments added

(defmacro hostx:with-dynamic-area (&body forms)
  `(progn ,@forms))

(defmacro hostx:with-static-area (&body forms)
  `(system:in-static-area ,@forms))

(defun hostx:augment-environment (env &optional options)
  (declare (ignore env options))
  (error "No such functions in LispWorks 5."))

;; string-char

(deftype hostx:string-char ()
  'base-char)

;; generic-flet

;; generic-labels

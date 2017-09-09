;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; lispworks-6-1-defs.lisp -- host compatibility functions for LispWorks
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/lispworks-6-1-defs.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2009-04-05 22:38:00 $")

#-(or (and LispWorks6 (not LispWorks6.0)) ; 6.1+
      LispWorks7) ; 7.x
#.(error "Attempting to use incorrect host database.
This file is for LispWorks 6.1+.")

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

;; string-char

(deftype hostx:string-char ()
  'base-char)

;; generic-flet

;; generic-labels

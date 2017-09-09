;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; mcl-5-2-defs.lisp -- host compatibility functions
;;;
;;; author :  Chun Tian (based on MCL 2.0 version by jeff wilson
;;;     based on Allegro version by Andy Latto,
;;;     based on lucid version by Sandy Loosemore
;;;    from original by Kim Barrett)
;;;
;;; date   :  11 Nov 2012
;;;
;;; Copyright (c) 2012, Versata Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/mcl-5-2-defs.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006-02-28 21:58:59 $")

#-MCL
#.(error "Attempting to use incorrect host database.
This file is for MAC Common Lisp version 5.2+")  

(defun host:compiler-macro-function (symbol &optional (env nil env-p))
  (if env-p
      (common-lisp:compiler-macro-function symbol)
      (common-lisp:compiler-macro-function symbol env)))

(defsetf host:compiler-macro-function (symbol &optional (env nil env-p))
    (new-macro)
  `(progn
     (when (and ,env-p ,env)
       (warn "Non-nil environment argument ~S to~
              ~S is not supported on Mac: ignored"
	     ,env 'host:compiler-macro-function))
     (setf (common-lisp:compiler-macro-function ,symbol) ,new-macro)))

(defmacro hostx:with-dynamic-area (&body forms)
  `(progn ,@forms))

;Can't do this in MCL.
(defmacro hostx:with-static-area (&body forms)
  `(progn ,@forms))

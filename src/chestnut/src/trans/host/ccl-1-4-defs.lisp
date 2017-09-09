;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; ccl-1-4-defs.lisp -- host compatibility functions
;;;
;;; based on mac-2-0-defs.lisp
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/ccl-1-4-defs.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2010-04-28 00:00:00 $")

#-clozure
#.(error "Attempting to use incorrect host database.
This file is for Clozure CL version 1.4 and later")


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

(defmacro hostx:with-static-area (&body forms)
  `(progn ,@forms))

;; string-char

(deftype hostx:string-char ()
  'base-char)

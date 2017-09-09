;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; mac-2-0-defs.lisp -- host compatibility functions
;;;
;;; author :  jeff wilson (based on Allegro version by Andy Latto, based
;;;     based on lucid version by Sandy Loosemore
;;;    from original by Kim Barrett)
;;;
;;; date   :  4 Jan 1992
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/mac-2-0-defs.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006-02-28 21:58:59 $")

#-MCL
#.(error "Attempting to use incorrect host database.
This file is for MAC Common Lisp version 2.0")


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
  

(defun host:upgraded-complex-part-type (type &optional env)
  (when env
    (warn "Ignoring environment argument ~S to ~S"
	  env 'host:upgraded-complex-part-type))
  (common-lisp:upgraded-complex-part-type type))


(defun host:upgraded-array-element-type (type &optional env)
  (when env
    (warn "Ignoring environment argument ~A to upgraded-array-element-type"
	  env))
  (common-lisp:upgraded-array-element-type type))

;;; Mac doesn't have forward referenced classes. Put in this stub so that
;;; references to the class forward-referenced-class don't make things die
;;; at compilation time

(defclass HOST-CLOS::FORWARD-REFERENCED-CLASS (standard-class) ())
			      
;;; PARSE-ERROR

(define-condition HOST:PARSE-ERROR (error) ())

;;; STYLE-WARNING

(define-condition HOST:STYLE-WARNING (warning) ())


;;; renamed SETF stuff

(defmacro host:define-setf-expander (&rest stuff)
  `(common-lisp:define-setf-method ,@stuff))

(defun host:get-setf-expansion (form &optional env)
  (common-lisp:get-setf-method-multiple-value form env))

;;; renamed special-form-p

(defun host:special-operator-p (thing)
  (common-lisp:special-form-p thing))


;;; things with environment arguments added

(defun host:constantp (thing &optional env)
  (declare (ignore env))
  (cl::constantp thing))

(defun host:typep (thing type &optional env)
  (declare (ignore env))
  (cl:typep thing type))

(defun host:subtypep (type1 type2 &optional env)
  (declare (ignore env))
  (cl:subtypep type1 type2))


(defun hostx:delq (item list)
  (loop (unless list
	  (return-from hostx:delq list))
	(unless (eq item (car list))
	  (return nil))
	(setq list (cdr list)))
  (let* ((tail list)
	 (next (cdr tail)))
    (loop (unless next
	    (return-from hostx:delq list))
	  (if (eq item (car next))
	      (setf next (cdr next)
		    (cdr tail) next)
	      (setf tail next
		    next (cdr tail))))))

(defmacro hostx:with-dynamic-area (&body forms)
  `(progn ,@forms))

;Can't do this in MCL.
(defmacro hostx:with-static-area (&body forms)
  `(progn ,@forms))

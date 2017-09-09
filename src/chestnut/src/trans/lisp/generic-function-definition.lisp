;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Manipulating generic function definitions in an environment.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/generic-function-definition.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:06 $")

(defun generic-function-definition-error (name type env)
  (declare (ignore env))
  (error "~S is defined as a ~(~A~)." name type))

(defun generic-function-undefined-error (name env)
  (declare (ignore env))
  (error "~S is not defined as a generic function." name))

(defun defined-as-generic-function (name &optional env)
  (let ((descriptor (defined-as-function name env)))
    (when descriptor
      (function-descriptor-generic-function-p descriptor))))

(defun defined-as-non-generic-function (name &optional env)
  (unless (defined-as-generic-function name env)
    (values (translator-function-information name env))))

(defun translator-find-generic-function-record (name &optional errorp env)
  (setf env (coerce-to-environment env))
  (let ((record (defined-as-generic-function name env)))
    (cond ((null record)
	   (let ((type (defined-as-non-generic-function name env)))
	     (cond (type (generic-function-definition-error name type env))
		   (errorp (generic-function-undefined-error name env))
		   (t nil))))
	  ((eq record t)
	   (when errorp
	     (error "Pre-defined generic function ~S not yet initialized."
		    name)))
	  (t record))))


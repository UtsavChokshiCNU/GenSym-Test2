;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; thread.lisp -- Multi-thread API support for Chestnut
;;;
;;; Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
;;; Date   :  06 Apr 2009
;;;
;;; Copyright (c) 2009, Versata Software, Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/thread.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2009/08/10 00:00:00 $")

(define-translator-macro portable-threads:with-lock-held ((lock &key (whostate "With Lock Held"))
                                                          &body body)
  `(progn (trun:%lock ,lock)
     (unwind-protect (progn ,@body)
       (trun:%unlock ,lock))))

(define-translator-macro tx:atomic-exchange (place new-value &environment env)
  (setq place (tcl:macroexpand place env))
  (if (atom place)
      (if (symbolp place)
          `(tx:atomic-exchange-symbol-value ',place ,new-value)
        (error "Invalid place: non-symbol atom (~A)" place))
    (case (car place)
      (symbol-value
       `(tx:atomic-exchange-symbol-value ,(cadr place) ,new-value))
      (t (error "Setf place (~A) is not supported yet" (car place))))))

(define-translator-macro portable-threads:atomic-incf& (place &optional (delta 1) &environment env)
  `(the fixnum (atomic-incf-decf& ,place ,delta)))

(define-translator-macro portable-threads:atomic-decf& (place &optional (delta 1) &environment env)
  `(the fixnum (atomic-incf-decf& ,place (the fixnum (- (the fixnum ,delta))))))

(defmacro atomic-incf-decf& (place delta &environment env)
  (setq place (tcl:macroexpand place env))
  (if (atom place)
      (if (symbolp place)
          `(tx:atomic-incff-symbol-value ',place ,delta)
        (error "Invalid place: non-symbol atom (~A)" place))
    (case (car place)
      (symbol-value
       `(tx:atomic-incff-symbol-value ,(cadr place) ,delta))
      ((car first
            trun:%m-car) ; lvalue
       `(tx:atomic-incff-car ,(cadr place) ,delta))
      ((cdr rest
            trun:%m-cdr) ; lvalue
       `(tx:atomic-incff-cdr ,(cadr place) ,delta))
      (svref
       `(tx:atomic-incff-simple-vector-slot
         ,(second place) ,(third place) ,delta))
      (t (error "Setf place (~A) is not supported yet" (car place))))))

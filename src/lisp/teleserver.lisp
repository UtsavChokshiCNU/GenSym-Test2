;; -*- mode: lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TELESERVER

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David




;;;; TELESERVER


;;; The module teleserver implements the G2 (server) side of Telewindows.
;;; At present, it must be maintained to run on top of both 1.11x and
;;; 2.0. It should NOT be put into any 1.11 file for general distribution, since
;;; it will be an add-on product.




;;;; Window

(def-class (window entity define-predicate)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      70 55 
      ((outline (5 0) (65 0) (65 40) (5 40))
       (lines (5 40) (0 55) (70 55) (65 40))
       (outline (10 13) (arc (12 7)) (18 5)
		(52 5) (arc (58 7)) (60 13)
		(60 27) (arc (58 33)) (52 35)
		(18 35) (arc (12 33)) (10 27))))))

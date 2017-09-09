;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION; Syntax: Common-Lisp -*-
;;;
;;; hpacks.lisp -- set up host package and friends
;;;
;;; author :  Sandra Loosemore
;;; date   :  30 Jan 1998
;;;
;;; Copyright (c) 1991, Chestnut Sofware Inc.
;;;
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/hpacks.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:06 $")

;;; Make all of the packages.

;;; DUMMY is a package for packages that would like not to use any packages,
;;; since (defpackage "FOO" (:use)) is broken in Allegro

(eval-when (compile load eval)

(defparameter *initial-host-packages*
  '(("HOST" "HOST-COMMON-LISP")
    ("HOST-CLOS")
    ("HOSTX" "HOST-EXTENSIONS")
    #+ALLEGRO-V4.0("HOST-DUMMY" "DUMMY")))

(dolist (package-spec *initial-host-packages*)
  (unless (find-package (car package-spec))
    (make-package (car package-spec)
		  :nicknames (cdr package-spec)
		  :use nil)))

)


#+translating
(eval-when (compile)

(when (find-package "OLD-HOST")
  (import (intern "*COMPILE-PRINT*" "OLD-HOST") "HOST")
  (import (intern "*COMPILE-VERBOSE*" "OLD-HOST") "HOST"))

)

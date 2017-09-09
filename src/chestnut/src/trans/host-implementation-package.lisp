;;; -*- Mode: Lisp; Package: CL-USER; Syntax: Common-Lisp -*-
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;

(in-package #-ANSI-CL "USER"
	    #+ANSI-CL "CL-USER")

(defparameter *host-implementation-package-source*
  "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host-implementation-package.lisp,v $")

(defparameter *host-implementation-package-revision*
  "$Revision: 1.2 $")

(defparameter *host-implementation-package-date*
  "$Date: 2007-11-14 22:02:52 $")

;;; Some of the package setup stuff happens in the HOST-IMPLEMENTATION
;;; package.  Make sure it exists. 
(eval-when (compile load eval)
(unless (find-package "HOST-IMPLEMENTATION")
  (make-package "HOST-IMPLEMENTATION"
		:nicknames '("HIMPL")
		:use '(#-ANSI-CL "LISP"
		       #+ANSI-CL "COMMON-LISP")))
)
#-(or MCL clozure SBCL)
(shadow #-harlequin-common-lisp
	'(#+(or lucid kcl excl chestnut) lisp:merge-pathnames
	  lisp:make-pathname
	  lisp:pathname-host lisp:pathname-device lisp:pathname-directory
	  lisp:pathname-name lisp:pathname-type lisp:pathname-version)
	#+harlequin-common-lisp
	'(lisp:make-pathname)
	"HOST-IMPLEMENTATION")
(import #-ANSI-CL
	'(user::*load-binary-files-p*
	  user::*translator-directory*
	  user::*translator-source-type*
	  user::*translator-source-directory*
	  user::*translator-binary-type*
	  user::*translator-binary-directory*
	  user::*host-implementation-package-source*
	  user::*host-implementation-package-revision*
	  user::*host-implementation-package-date*
	  user::translator-version
	  user::*record-files-to-load-p*
	  user::*all-files-to-load*
	  user::*load-binary-files-p*
	  #+lucid
	  user::*compile-print*
	  user::*inhibit-final-translator-initialization*
	  user::load-file)
	#+ANSI-CL
	'(cl-user::*load-binary-files-p*
	  cl-user::*translator-directory*
	  cl-user::*translator-source-type*
	  cl-user::*translator-source-directory*
	  cl-user::*translator-binary-type*
	  cl-user::*translator-binary-directory*
	  cl-user::*host-implementation-package-source*
	  cl-user::*host-implementation-package-revision*
	  cl-user::*host-implementation-package-date*
	  cl-user::translator-version
	  cl-user::*record-files-to-load-p*
	  cl-user::*all-files-to-load*
	  cl-user::*load-binary-files-p*
	  cl-user::*inhibit-final-translator-initialization*
	  cl-user::load-file)
	"HOST-IMPLEMENTATION")
(dolist (name '("NOTE-RCS-REVISION"
		"SHOW-RCS-REVISION"
		"TRANSLATOR-VERSION"
		"DEFINE-SYMBOLS"))
  (export (intern name "HOST-IMPLEMENTATION") "HOST-IMPLEMENTATION"))


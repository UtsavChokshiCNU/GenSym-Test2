;;; -*- Mode: Lisp; Package: CL-USER; Syntax: Common-Lisp -*-
;;;
;;; load-trans.lisp -- load the Lisp->C translator
;;;
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;
;;;

(in-package #-ANSI-CL "USER"
	    #+ANSI-CL "CL-USER")

#-SBCL (proclaim '(special *load-verbose* *compile-verbose*))

(setq *load-verbose* t)
(setq *compile-verbose* t)

(unless (boundp '*compile-print*)
  (setq *compile-print* nil))

#+Genera
(multiple-value-bind (major minor) (sct:get-release-version)
  (etypecase minor
    (integer)
    (string (setf minor (parse-integer minor :junk-allowed t))))
  (pushnew :genera *features*)
  (ecase major
    ((8)
     (pushnew :genera-8 *features*)
     (ecase minor
       ((0) (pushnew :genera-8-0 *features*))
       ((1) (pushnew :genera-8-1 *features*))))))

#+mcl
(let ((version (lisp-implementation-version)))
  (cond ((equal version "Version 2.0")
	 (pushnew :mcl-2.0 *features*))
	((equal version "Version 5.2")
	 (pushnew :mcl-5.2 *features*))
	(t
	 (error "Fix this for ~S" version))))

#+lcl4.1
(when (equal lucid::*lucid-version*
	     "Development Environment Version 4.1.1")
  (pushnew :lcl4.1.1 *features*))

(defparameter *translator-source-type* 
  #+gclisp "lsp"
  #-gclisp "lisp")

(defparameter *translator-binary-type*
  #+chestnut nil
  #-chestnut
  (or (first ; put newer versions first
       '(#+clozure #.(subseq (namestring ccl:*.fasl-pathname*) 1)
	 #+SBCL "fasl"
	 #+gclisp "f2s"
	 #+(and lucid sun LCL5.0)   "sbin-l50"
	 #+(and lucid sun LCL4.2.1) "sbin-l421"
	 #+(and lucid sun LCL4.2)   "sbin-l42"
	 #+(and lucid sun LCL4.1.1) "sbin-l411"
	 #+(and lucid sun LCL4.1)   "sbin-l41"
	 #+(and lucid sun LCL4.0)   "sbin-l40"
	 #+ALLEGRO-V4.1 "fasl-a41"
	 #+ALLEGRO-V4.0 "fasl-a40"
	 #+MCL-2.0 "fasl" ; was "fasl-m20", but limited to 32 char names
	 #+MCL-5.2 "cfsl"
	 #+Genera-8-1 "bin-g81"
	 #+Genera-8-0 "bin-g80"
	 #+(or LispWorks5 LispWorks6) #.system:*binary-file-type*
	 #+LispWorks3.1 "wfasl-lw31"))
      (error "Fix the *translator-binary-type* for this host")))

#+lucid
(unless (member *translator-binary-type* *load-binary-pathname-types*
		:test #'equal)
  (setq *load-binary-pathname-types*
	(append *load-binary-pathname-types*
		(list *translator-binary-type*))))

(defvar *record-files-to-load-p* nil)
(defvar *all-files-to-load* nil)

;; in Clozure CL initial value of *default-pathname-defaults* is #P""
;; So it is needed initialization
#+clozure
(setq *default-pathname-defaults* (pathname (concatenate 'string (ccl::current-directory-name) "/")))

(defun load-file (pathname)
  (if *record-files-to-load-p*
      (push (pathname pathname) *all-files-to-load*)
      (load pathname)))

(defparameter *load-translator-files-defaults*
  (merge-pathnames
   #+lucid  lcl::*load-pathname*
   #+(and excl (not allegro-v4.1)) excl::*source-pathname*
   #+genera sys:fdefine-file-pathname
   #+(or SBCL allegro-v4.1 mcl clozure LispWorks Chestnut) *load-pathname*
   #-(or SBCL genera excl lucid mcl clozure LispWorks Chestnut)
   (error "Fix this")))

(defun load-translator-files (&rest files)
  (let* ((*default-pathname-defaults* *load-translator-files-defaults*)
	 (dev (pathname-device *default-pathname-defaults*))
	 (dir (pathname-directory *default-pathname-defaults*))
	 (rdir (reverse dir))
	 (ndir (if (and (< 2 (length rdir))
			(equalp "lisp" (car rdir))
			(equalp "trans" (cadr rdir)))
		   (reverse (cdr rdir))
		   dir)))
    (setq *default-pathname-defaults*
	  (make-pathname :device dev :directory ndir))
    (let ((defaults
	      (make-pathname
	       :defaults (if (probe-file (merge-pathnames "load-trans.lisp"))
			     *default-pathname-defaults*
			     (make-pathname :device dev :directory dir))
	       :type (or *translator-binary-type*
			 *translator-source-type*))))
      (dolist (name files)
	(load-file (merge-pathnames name defaults))))))

;;; ----------------------------------------------------------------------

(pushnew :optimize-translator *features*)

(setq *load-binary-files-p* t)

(defvar *use-single-file-p*
  (when *translator-binary-type*
    (probe-file (make-pathname :defaults *load-translator-files-defaults*
			       :name "trans"
			       :type *translator-binary-type*))))

(if *use-single-file-p*
    (let (#+mcl (ccl:*warn-if-redefine* nil)
	  #+lucid (lcl:*redefinition-action* nil))
      (load-translator-files "trans"))
    (load-translator-files "host-implementation-package"
			   "host-implementation"
			   "module"
			   "translator"))

(unless *use-single-file-p*
  (himpl:note-rcs-revision
   "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/load-trans.lisp,v $"
   "$Revision: 1.2 $"
   "$Date: 2007-11-14 22:02:53 $")

  (load-module :translator))

(pushnew :chestnut-3 *features*)

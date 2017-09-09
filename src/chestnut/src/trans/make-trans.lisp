;;; -*- Mode: Lisp; Package: CL-USER; Syntax: Common-Lisp -*-
;;;
;;; load-trans.lisp -- load the Lisp->C translator
;;;
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;
;;;

(in-package #-(or SBCL MCL clozure Genera Chestnut) "USER"
	    #+(or SBCL MCL clozure Genera Chestnut) "CL-USER")

#-(or Chestnut MCL)
(proclaim '(special *load-verbose* *compile-verbose*))
#+(or Chestnut MCL)
(declaim (special *load-verbose* *compile-verbose*))

(setq *load-verbose* t)
(setq *compile-verbose* t)

#+lucid
(defvar *compile-print* nil)

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
	(t
	 (error "Fix this for ~S" version))))

(eval-when (compile load eval)

(defparameter *translator-source-type* 
  #+gclisp "lsp"
  #-gclisp "lisp")

(defparameter *translator-binary-type*
  #+chestnut nil
  #-chestnut
  (or (first ; put newer versions first
       '(#+gclisp "f2s"
	 #+(and lucid sun LCL4.1) "sbin-l41"
	 #+(and lucid sun LCL4.0) "sbin-l40"
	 #+ALLEGRO-V4.1 "fasl-a41"
	 #+ALLEGRO-V4.0 "fasl-a40"
	 #+MCL-2.0 "fasl" ; was "fasl-m20", but limited to 32 char names
	 #+Genera-8-1 "bin-g81"
	 #+Genera-8-0 "bin-g80"
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

(defun load-file (pathname)
  (if *record-files-to-load-p*
      (push (pathname pathname) *all-files-to-load*)
      (load pathname)))

)

(defparameter *load-translator-files-defaults*
  (merge-pathnames
   #+lucid  lcl::*load-pathname*
   #+(and excl (not allegro-v4.1)) excl::*source-pathname*
   #+genera sys:fdefine-file-pathname
   #+(or allegro-v4.1 mcl LispWorks Chestnut) *load-pathname*
   #-(or genera excl lucid mcl LispWorks Chestnut)
   (error "Fix this")))

(defun translator-files-defaults ()
  (let* ((dev (pathname-device *default-pathname-defaults*))
	 (dir (pathname-directory *default-pathname-defaults*))
	 (rdir (reverse dir))
	 (ndir (if (and (< 2 (length rdir))
			(equalp "lisp" (car rdir))
			(equalp "trans" (cadr rdir)))
		   (reverse (cddr rdir))
		   dir)))
    (setq *default-pathname-defaults*
	  (make-pathname :device dev :directory ndir))
    (make-pathname
     :defaults (if (probe-file (merge-pathnames "load-trans.lisp"))
		   *default-pathname-defaults*
		   (make-pathname :device dev :directory dir))
     :type (or *translator-binary-type*
	       *translator-source-type*))))

(proclaim '(special *translator-directory*))

(setq *translator-directory*
      (let ((*default-pathname-defaults* *load-translator-files-defaults*))
	(translator-files-defaults)
	*default-pathname-defaults*))

(defun load-translator-files (&rest files)
  (let* ((*default-pathname-defaults* *load-translator-files-defaults*)
	 (defaults (translator-files-defaults)))
    (dolist (name files)
      (let* ((bin (merge-pathnames name defaults))
	     (src (make-pathname :defaults bin
				 :type *translator-source-type*)))
	(unless (and (probe-file bin)
		     (>= (file-write-date bin)
			 (file-write-date src)))
	  (compile-file src :output-file bin))
	(load-file bin)))))

;;; ----------------------------------------------------------------------




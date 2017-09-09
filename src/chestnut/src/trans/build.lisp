;;; -*- Mode: Lisp; Package: CL-USER; Syntax: Common-Lisp -*-
;;;
;;; build.lisp -- build the Lisp->C translator
;;;
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;
;;;

(in-package #-ANSI-CL "USER"
	    #+ANSI-CL "CL-USER")

#+sbcl
(setq sb-ext:*evaluator-mode* :interpret
      *compile-print* nil)  ;make a little less noise.

(setq *load-verbose* t)
(setq *compile-verbose* t)

(unless (boundp '*compile-print*)
  (setq *compile-print* nil))

#+sbcl
(let ((version (lisp-implementation-version)))
  (when (or (string= (subseq version 0 1) "0")         ; 0.x
            (and (string= (subseq version 0 4) "1.0.") ; 1.0.x
                 (< (parse-integer (subseq version 4) :junk-allowed t) 52)))
    ;; push :sbcl-old to SBCL older than 1.0.52
    (pushnew :sbcl-old *features*)))

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
	((equal version "Version 6.0")
	 (pushnew :mcl-6.0 *features*))
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
	 #+MCL-6.0 "cfsl"
	 #+Genera-8-1 "bin-g81"
	 #+Genera-8-0 "bin-g80"
	 #+(or LispWorks5 LispWorks6 LispWorks7) #.system:*binary-file-type*
	 #+LispWorks3.1 "wfasl-lw31"))
      (error "Fix the *translator-binary-type* for this host")))

#+lucid
(unless (member *translator-binary-type* *load-binary-pathname-types*
		:test #'equal)
  (push *translator-binary-type* *load-binary-pathname-types*))

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

(defun translator-files-defaults ()
  (let* ((dev (pathname-device *default-pathname-defaults*))
	 (dir (pathname-directory *default-pathname-defaults*))
	 (rdir (reverse dir))
	 (ndir (if (and (< 2 (length rdir))
			(equalp "lisp" (car rdir))
			(equalp "trans" (cadr rdir)))
		   (reverse (cdr rdir))
		   dir)))
    (setq *default-pathname-defaults*
	  (make-pathname :device dev :directory ndir))
    (make-pathname
     :defaults (if (probe-file (merge-pathnames "load-trans.lisp"))
		   *default-pathname-defaults*
		   (make-pathname :device dev :directory dir))
     :type (or *translator-binary-type*
	       *translator-source-type*))))

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

(pushnew :internal-use *features*)

(load-translator-files "host-implementation-package"
		       "host-implementation"
		       "module"
		       "translator")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/build.lisp,v $"
 "$Revision: 1.5 $"
 "$Date: 2007-11-25 15:32:32 $")

(defvar *compile-and-load-translator-p* t)

(when *compile-and-load-translator-p*
  (compile-module :translator)
  (load-module :translator)
  #+load-patches (himpl::load-patches t)
  (pushnew :chestnut-3 *features*))

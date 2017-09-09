;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION; Syntax: Common-Lisp -*-
;;;
;;; module.lsp -- a program maintenance utility
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  20 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/module.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007-11-15 21:23:18 $")

(defvar *warn-if-source-not-found-p* t)
(defvar *load-binary-files-p* nil)
(defvar *optimize* ; set in translator.lisp
  '(optimize (speed 2) (safety 3) (space 0) #+sbcl (debug 3)
             #+lucid (compilation-speed 3)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Module definition
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; A module definition looks like
;;; (name option*) where option is one of:
;;;    (:source-pathname pathname)
;;;    (:binary-pathname pathname)
;;;    (:package package-or-package-name)
;;;    (:requires module-name-or-pathname*)
;;;    (:module . module-definition)   ; can appear multiple times
;;; Module names are scoped similarly to LET*:  a module can be referenced
;;; in the :requires list of any module defined after it at the same level
;;; or nested within any of those modules.  Names of :modules are not
;;; propagated outside the :module they are defined in.  References to
;;; non-lexically defined module names are taken to be names of
;;; globally-defined modules.

(defun print-module (record stream depth)
  (declare (ignore depth))
  (format stream "#<Module ~s>" (module-name record)))

(defstruct (module (:print-function print-module))
  (name             nil)
  (package          nil)
  (requires         nil)
  (recompile-on     nil)
  (modules          nil)
  (source-pathname  nil)
  (binary-pathname  nil)
  (load-time        nil)
  (max-source-time  nil)
  (max-binary-time  nil)
  (min-binary-time  nil)
  )

(defmacro global-module (name)
  `(get ,name 'module))

(defun find-module (name)
  (or (global-module name)
      (error "No module named ~s has been defined." name)))

(defun parse-module-definition (name options modules-visible-here
				     source-pathname binary-pathname
				     package)
  (let ((requires          nil)
	(recompile-on      nil)
	(modules           nil)
	(parsed-modules    nil))
    (dolist (o options)
      (case (car o)
	(:source-pathname
	 (setq source-pathname
	       (merge-pathnames (pathname (cadr o)) source-pathname)))
	(:binary-pathname
	 (setq binary-pathname
	       (when *translator-binary-type*
		 (merge-pathnames (pathname (cadr o)) binary-pathname))))
	(:package
	 (setq package
	       (if (packagep (cadr o))
		   (cadr o)
		   (or (find-package (cadr o))
		       (cadr o)))))
	(:requires
	 (dolist (r (cdr o))
	   (cond ((stringp r)
		  (push (pathname r) requires))
		 ((pathnamep r)
		  (push r requires))
		 ((not (symbolp r))
		  (error "Bad :requires syntax: ~s" r))
		 (t
		  (push (or (car (member r modules-visible-here
					 :key #'module-name))
			    r)
			requires)))))
	(:recompile-on
	 (dolist (r (cdr o))
	   (cond ((stringp r)
		  (push (pathname r) recompile-on))
		 ((pathnamep r)
		  (push r recompile-on))
		 ((not (symbolp r))
		  (error "Bad :recompile-on syntax: ~s" r))
		 (t
		  (push (or (car (member r modules-visible-here
					 :key #'module-name))
			    r)
			recompile-on)))))
	(:module
	 (push (cdr o) modules))
	(t
	 (error "Unrecognized module option ~s." o))))
    (if modules
	(dolist (m (nreverse modules))
	  (let ((new  (parse-module-definition
		       (car m) (cdr m)
		       modules-visible-here source-pathname binary-pathname
		       package)))
	    (push new parsed-modules)
	    (push new modules-visible-here)))
	(let ((fname (if (symbolp name)
			 (string-downcase (symbol-name name))
			 name)))
	  (setq source-pathname
		(merge-pathnames
		 source-pathname
		 (make-pathname :name fname
				:type *translator-source-type*)))
	  (setq binary-pathname
		(when *translator-binary-type*
		  (merge-pathnames
		   binary-pathname
		   (make-pathname :name fname
				  :type *translator-binary-type*))))))
    (make-module :name name
		 :package package
		 :requires (nreverse requires)
		 :recompile-on (nreverse recompile-on)
		 :modules (nreverse parsed-modules)
		 :source-pathname source-pathname
		 :binary-pathname binary-pathname)))


(defun defmodule-internal (name options)
  (let* ((default *default-pathname-defaults*)
	 (path (make-pathname
		:host (pathname-host default)
		:device (pathname-device default)
		:directory (pathname-directory default))))
    (setf (global-module name)
	  (parse-module-definition name options nil
				   path
				   (when *translator-binary-type* path)
				   *package*)))
  name)

(defmacro defmodule (name &rest options)
  `(defmodule-internal ',name ',options))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Module loading
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Module loading happens in the sequence the modules were defined in,
;;; additionally loading in the things in the :require list.  (Note that
;;; any modules in this list are guaranteed to already have been loaded.)

(defun load-module (object)
  (when (symbolp object)
    (setq object (find-module object)))
  (cache-module-times object 0)
  (load-module-aux object)
  nil)


;;; If the module is already loaded and none of its source, compiled files, and
;;; dependencies have changed since then, do nothing.
;;; If the module's compiled files don't exist or are out of date with its
;;; source or dependencies, load the source files.
;;; Otherwise load the compiled files.

(defun load-module-aux (module)
  (let ((load-time        (module-load-time module))
	(max-source-time  (module-max-source-time module))
	(max-binary-time  (module-max-binary-time module)))
    (when (or (null load-time)
	      (> max-source-time load-time)
	      (and max-binary-time (> max-binary-time load-time)))
      (dolist (r (module-requires module))
	(recursive-load-module r))
      (cond ((module-modules module)
	     (dolist (m (module-modules module))
	       (load-module-aux m)))
	    ((or (null max-binary-time) (< max-binary-time max-source-time))
	     (let* ((*package*  (find-module-package (module-package module)))
		    (source (module-source-pathname module))
		    (binary (module-binary-pathname module)))
	       (if (or (probe-file source) (null binary))
		   (load-file (if (and *load-binary-files-p*
				       binary
				       (probe-file binary))
			      binary
			      source))
		   (if (probe-file binary)
		       (progn
			 (when (and *warn-if-source-not-found-p*
				    (not *load-binary-files-p*))
			   (warn "~A was not found, loading ~A instead"
				 (namestring source) (namestring binary)))
			 (load-file binary))
		       (error "~A does not exist" (namestring source))))))
	    (t
	     (let ((*package*  (find-module-package (module-package module))))
	       (load-file (module-binary-pathname module)))))
      ;;;note:  This is a problem, if the file server is on NFS and clocks are not synch'd.
      (setf (module-load-time module) (get-universal-time)))))

(defun recursive-load-module (object)
  (cond ((stringp object)
	 (load-file (find-random-file (pathname object))))
	((pathnamep object)
	 (load-file (find-random-file object)))
	((symbolp object)
	 (load-module-aux (find-module object)))
	((module-p object)
	 (load-module-aux object))
	(t
	 (error "Invalid argument to RECURSIVE-LOAD-MODULE: ~s" object))))

(defun reset-load-times (object)
  (cond ((stringp object))
	((pathnamep object))
	((symbolp object)
	 (reset-load-times (find-module object)))
	((module-p object)
	 (setf (module-load-time object) nil)
	 (mapc #'reset-load-times (module-modules object)))))

(defun module-load-files (object)
  (let ((*record-files-to-load-p* t)
	(*all-files-to-load* nil)
	(*load-binary-files-p* t))
    (load-module object)
    (nreverse *all-files-to-load*)))  


;;; The intent of this macro is to be like (with-compilation-unit () ...).
;;; However, with-compilation-unit doesn't exist in many implementations yet,
;;; so we make use of implementation-specific definitions when we know about
;;; them.

(defmacro with-warnings-deferred (&body body)
  #+lucid
  `(lucid-common-lisp:with-deferred-warnings ,@body)
  #+(or MCL LispWorks)
  `(with-compilation-unit nil ,@body)
  #+Genera
  `(compiler:compiler-warnings-context-bind ,@body)
  #-(or lucid MCL LispWorks Genera)
  `(progn ,@body))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Compilation
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Compilation is a lot like loading.  The only difference is that you
;;; use the timestamp information to make a decision on whether or not
;;; to compile the file instead of on whether to load the source or binary.

(defun compile-module (object)
  (when *translator-binary-type*
    (when (symbolp object)
      (setq object (find-module object)))
    (cache-module-times object 0)
    (with-warnings-deferred
	(compile-module-aux object nil)))
  nil)

;;; Note that if a submodule requires other submodules that have already
;;; been recompiled, its max-source-time will be incorrect.  Also remember
;;; to update its binary and compile timestamps.
;;; Force recompilation of submodules if requires changed after 
;;; last recompilation.  Otherwise if the earliest binary was created 
;;; after the last modification to the source, submodules can't possibly
;;; need recompilation so don't bother to traverse them.

(defun compile-module-aux (module force-p)
  (let* ((requires-time   (most-recent-of-requires module nil))
	 (max-source-time (max (module-max-source-time module)
			       requires-time))
	 (min-binary-time (module-min-binary-time module))
	 (max-binary-time (module-max-binary-time module)))
    (setf (module-max-source-time module) max-source-time)
    (setq force-p 
	  (or force-p
	      (null max-binary-time)
	      (< max-binary-time requires-time)))
    (unless (and (not force-p)
		 min-binary-time (> min-binary-time max-source-time))
      (dolist (r (module-requires module))
	(recursive-load-module r))
      (cond ((module-modules module)
	     (dolist (m (module-modules module))
	       (compile-module-aux m force-p))
	     (setf (module-max-binary-time module)
		   (apply #'max (mapcar #'module-max-binary-time 
					(module-modules module))))
	     (setf (module-min-binary-time module)
		   (apply #'min (mapcar #'module-min-binary-time 
					(module-modules module)))))
	    ((or force-p
		 (null max-binary-time)
		 (< max-binary-time max-source-time))
	     (let ((*package* (find-module-package (module-package module))))
	       #+genera
	       (format t "~&Compiling ~A.~%"
		       (namestring (module-source-pathname module)))
	       (proclaim *optimize*)
	       (compile-file (module-source-pathname module)
			     :output-file (module-binary-pathname module)))
	     (let ((time  (get-universal-time)))
	       (setf (module-max-binary-time module) time)
	       (setf (module-min-binary-time module) time)))
	    (t
	     nil)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Utilities
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Coerce the thing to be a package.

(defun find-module-package (thing)
  (if (packagep thing)
      thing
      (or (find-package thing)
	  (error "No package named ~s exists." thing))))


;;; Cache source and binary file timestamps for each module.
;;; Note that max-binary-time = nil if none of the binaries exist
;;;           min-binary-time = nil if only some of the binaries exist

(defun cache-module-times (module inherited-max-source-time)
  (setq inherited-max-source-time
	(max inherited-max-source-time (most-recent-of-requires module t)))
  (let ((max-source-time    inherited-max-source-time)
	(max-binary-time    nil)
	(min-binary-time    0))
    (if (module-modules module)
	(dolist (m (module-modules module))
	  (cache-module-times m inherited-max-source-time)
	  (setq max-source-time
		(max max-source-time (module-max-source-time m)))
	  (setq max-binary-time
		(if (module-max-binary-time m)
		    (if max-binary-time
			(max max-binary-time (module-max-binary-time m))
		        (module-max-binary-time m))
		    max-binary-time))
	  (setq min-binary-time
		(if (module-min-binary-time m)
		    (if min-binary-time
			(min min-binary-time (module-min-binary-time m))
		        nil)
		    nil)))
        (progn
	  (setq max-source-time
		(max max-source-time
		     (or (let ((source (module-source-pathname module)))
			   (and (probe-file source)
				(file-write-date source)))
			 (get-universal-time))))
	  (let ((binary (module-binary-pathname module)))
	    (when (and binary (probe-file binary))
	      (let ((time (file-write-date binary)))
		(setq max-binary-time (or time (get-universal-time)))
		(setq min-binary-time (or time 0)))))))
    (setf (module-max-source-time module) max-source-time)
    (setf (module-max-binary-time module) max-binary-time)
    (setf (module-min-binary-time module) min-binary-time)))

(defun most-recent-of-requires (module recurse-p)
  (most-recent-of-requires-aux
   (module-recompile-on module)
   (most-recent-of-requires-aux (module-requires module) 0 recurse-p)
   recurse-p))

(defun most-recent-of-requires-aux (dependencies max-source-time recurse-p)
  (dolist (r dependencies)
    (if (or (stringp r) (pathnamep r))
	(setq max-source-time
	      (max max-source-time
		   (or (file-write-date (find-random-file r))
		       (get-universal-time))))
	(progn
	  (when (symbolp r)
	    (setq r (find-module r))
	    (when recurse-p (cache-module-times r 0)))
	  (setq max-source-time
		(if (module-max-binary-time r)
		    (max max-source-time
			 (module-max-source-time r)
			 (module-max-binary-time r))
		    (module-max-source-time r))))))
  max-source-time)


;;; Find a random file.  If the named file exists without fiddling with
;;; the extension, use it.  Otherwise take binary if it exists, otherwise
;;; the source.  Signal an error if you can't find anything reasonable.

(defun find-random-file (name)
  (let ((temp  nil))
    (cond ((probe-file name)
	   name)
	  ((and *translator-binary-type*
		(probe-file
		 (setq temp
		       (merge-pathnames
			name (make-pathname :type *translator-binary-type*)))))
	   temp)
	  ((probe-file
	     (setq temp
		   (merge-pathnames
		     name (make-pathname :type *translator-source-type*))))
	   temp)
	  (t
	   (error "Could not find file ~s." name)))))

(setf (symbol-function #-ANSI-CL 'user::load-module
		       #+ANSI-CL 'cl-user::load-module)
      #'load-module)

(setf (symbol-function #-ANSI-CL 'user::compile-module
		       #+ANSI-CL 'cl-user::compile-module)
      #'compile-module)

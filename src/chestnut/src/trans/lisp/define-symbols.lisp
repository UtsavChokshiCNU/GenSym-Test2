;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION; Syntax: Common-Lisp -*-
;;;
;;; define-symbols.lisp
;;;
;;; Copyright (c) 1993, Chestnut Sofware Inc.
;;;
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/define-symbols.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/11/14 22:02:54 $")

;;; If *complain-about-missing-symbols* is true, then any symbol that is
;;; not found in the package it's supposed to be imported from (which
;;; defaults to default-package) gets its own warning.  Otherwise we just
;;; collect them all up into *missing-symbols* and complain once at the end.

(eval-when (compile load eval)

(defvar *complain-about-missing-symbols* t)
(defvar *missing-symbols* nil)

)

(defvar *debugging-define-symbols* nil)

(defvar *forms* nil)

(defmacro define-symbols (default-package process-p &rest symbols)
  (unless (packagep default-package)
    (setq default-package (find-package 
			   (if (eq default-package :lisp)
			       #-(or SBCL MCL clozure Genera) "LISP"
			       #+(or SBCL MCL clozure Genera) "COMMON-LISP"
			       default-package))))
  (let ((*package* (find-package "HOST-IMPLEMENTATION"))
	(all-symbols nil)
	(intern-alist nil)
	(import-alist nil)
	(export-alist nil)
	(*missing-symbols* nil)
	(symbol-forms nil)
	(forms nil))
    (macrolet ((add-symbol-to-alist (symbol p alist)
		 `(let ((a (assoc ,p ,alist :test #'eq)))
		    (unless a 
		      (push (setq a (list ,p)) ,alist))
		    (push ,symbol (cdr a)))))
      (dolist (entry symbols)
	(let* ((name (car entry))
	       (usage-list (cdr entry)))
	  (unless (eq (caar usage-list) ':symbol)
	    (error "The first usage must be ~S" ':symbol))
	  (multiple-value-bind (symbol import-packages export-packages)
	      (apply #'initialize-symbol-1 default-package name
		     (cdar usage-list))
	    (if (member symbol all-symbols)
		(warn "The symbol ~S occurs more than once" symbol)
		(push symbol all-symbols))
	    (when process-p
	      (setq forms (nconc (process-entry-form symbol usage-list)
				 forms))
	      (when *debugging-define-symbols*
		(setq *forms* forms)
		(break "Define-symbols: Just added to forms in *forms*")))
	    (dolist (p import-packages)
	      (if (eq p (symbol-package symbol))
		  (add-symbol-to-alist symbol p intern-alist)
		  (add-symbol-to-alist symbol p import-alist)))
	    (dolist (p export-packages)
	      (add-symbol-to-alist symbol p export-alist))))))
    (when (and *missing-symbols*
	       (not *complain-about-missing-symbols*))
      (warn "There were ~s missing symbols declared."
	    (length *missing-symbols*)))
    (dolist (a (nreverse intern-alist))
      (push `(eval-when (compile load eval)
	       (let ((*package* (find-package ',(package-name (car a)))))
		 (mapc #'intern-and-export
		       ',(mapcar #'symbol-name (nreverse (cdr a))))))
	    symbol-forms))    
    (dolist (a (nreverse import-alist))
      (push `(eval-when (compile load eval)
	       (import ',(nreverse (cdr a)) ',(package-name (car a))))
	    symbol-forms))
    (dolist (a (nreverse export-alist))
      (push `(eval-when (compile load eval)
	       (export ',(nreverse (cdr a)) ',(package-name (car a))))
	    symbol-forms))
    `(progn
       ,@(nreverse symbol-forms)
       #+mcl (mapc #'simple-eval ',(nreverse forms))
       #-mcl ,@(mapcar #'(lambda (form)
			   `(,(car form)
			     ,@(mapcar #'(lambda (value) `',value)
				       (cdr form))))
		       (nreverse forms))
       nil)))

(defun simple-eval (form)
  (apply (car form) (cdr form)))

(eval-when (compile load eval)

(defun intern-and-export (name &optional (package *package*))
  (unless (packagep package)
    (setq package (find-package package)))
  (let ((sym (intern name package)))
    (unless sym (setq sym (list sym)))
    (export sym package)))

#+translating
(declaim (special *tcl-package*))
#-translating
(proclaim '(special *tcl-package*))

(defun initialize-symbol-1 (default-package name
			    &key (package *tcl-package*)
			    (import-from default-package)
			    (export nil export-p)
			    &allow-other-keys)
  #+genera
  (when (eq import-from :lisp)
    (let ((fcl (find-symbol name "FUTURE-COMMON-LISP"))
	  (cl (find-symbol name "COMMON-LISP")))
      (setq import-from
	    (if fcl
		(if cl
		    (if (eq cl fcl)
			"COMMON-LISP"
			(progn
			  (warn "~S and ~S are not the same.  Using ~S."
				fcl cl cl)
			  "COMMON-LISP"))
		    "FUTURE-COMMON-LISP")
		(if cl
		    "COMMON-LISP"
		    (if (string= name "NIL")
			"COMMON-LISP"
			(progn
			  (warn "No symbol named ~A appears in either ~S or ~S"
				name "COMMON-LISP" "FUTURE-COMMON-LISP")
			  nil)))))))
  (when (and import-from
	     (multiple-value-bind (s found-p)
		 (find-symbol name import-from)
	       (declare (ignore s))
	       (null found-p)))
    (when *complain-about-missing-symbols*
      (warn "Could not find symbol ~s in package ~s."
	    name import-from))
    (push (cons name import-from) *missing-symbols*)
    (setq import-from nil))
  (flet ((find-package1 (name)
	   (or (find-package name)
	       (error "Package ~S was not found" name))))
    (setq package (find-package1 package))
    (setq export (mapcar #'find-package1 export)))
  (let ((symbol (intern name (or import-from package))))
    (if (null export-p)
	(values symbol (list package) (list package))
	(values symbol
		(if (member package export)
		    export
		    (cons package export))
		export))))

)


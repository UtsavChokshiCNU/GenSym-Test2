;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; defpackage.lisp -- defpackage macro
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  07 Sep 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/defpackage.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:03 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Compiletime support
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Here's the translator-macro for DEFPACKAGE.
;;; When this appears in a file to be translated, it causes code to
;;; set up the package to be generated normally.

(define-translator-macro defpackage (package-name &rest options)
  `(progn
     (eval-when (eval compile load)
       ,(expand-defpackage package-name options))
     (eval-when (compile eval)
       (notice-translator-package ',package-name))))

(defun stringify (thing)
  (etypecase thing
    (string (coerce thing 'simple-string))
    (symbol (symbol-name thing))))

(defun stringify-list (list &optional (delete-duplicates t))
  (setf list (mapcar #'stringify list))
  (if delete-duplicates
      (delete-duplicates list :test #'string=)
      list))

(defun merge-names (old new)
  (nunion old (stringify-list new) :test #'string=))

(defun merge-name-alists (old new)
  (destructuring-bind (key &rest names) new
    (setf key (stringify key))
    (setf names (stringify-list names))
    (when names
      (let ((entry (assoc key old :test #'string=)))
	(if (null entry)
	    (setf old `((,key ,@names) ,@old))
	    (setf (cdr entry) (nunion (cdr entry) names :test #'string=)))))
    old))

(defun conflict-list (x y)
  (intersection x y :test #'string=))

(defun check-conflict (x y pkg-name xtype ytype)
  (let ((conflicts (conflict-list x y)))
    (when conflicts
      ;; Maybe this should be PROGRAM-ERROR?
      (error "DEFPACKAGE ~A has conflicts between ~S and ~S names:~{~%  ~A~}"
	     pkg-name xtype ytype conflicts))))

(defun check-intern-export-conflicts (intern export pkg-name)
  (check-conflict intern export pkg-name :intern :export))

(defun check-shadow-intern-import-conflicts
    (shadow intern shadowing-import import pkg-name)
  (check-conflict shadow intern pkg-name :shadow :intern)
  (check-conflict shadow shadowing-import pkg-name
		  :shadow :shadowing-import-from)
  (check-conflict shadow import pkg-name :shadow :import-from)
  (check-conflict intern shadowing-import pkg-name
		  :intern :shadowing-import-from)
  (check-conflict intern import pkg-name :intern :import-from)
  (check-conflict shadowing-import import pkg-name
		  :shadowing-import-from :import-from))

(defun check-alist-conflict (x y pkg-name type)
  (let ((conflicts (conflict-list (cdr x) (cdr y))))
    (when conflicts
      ;; Maybe this should be PROGRAM-ERROR?
      (error "DEFPACKAGE ~A includes ~S from both ~A and ~A for~{~%  ~A~}"
	     pkg-name type (car x) (car y) conflicts))))

(defun check-import-conflicts (alist type pkg-name)
  (do ((alist alist (cdr alist)))
      ((endp alist))
    (let ((head (car alist)))
      (dolist (next (cdr alist))
	(check-alist-conflict head next pkg-name type))))
  (mapcan #'(lambda (entry) (copy-list (cdr entry))) alist))

(defvar *shadow-not-supported* t)

(defun expand-defpackage (package-name options)
  (let ((nicknames nil)
	(use-default t)
	(use nil)
	(shadow nil)
	(shadowing-import-from nil)
	(import-from nil)
	(export nil)
	(intern nil)
	(size nil)
	(doc nil))
    (setf package-name (stringify package-name))
    (flet ((resolve-single (option value type)
	     (if value
		 ;; This should be PROGRAM-ERROR.
		 (progn
		   (cerror "Ignore additional ~S option."
			   "More than one ~S option in DEFPACKAGE for ~A."
			   (car option)
			   package-name)
		   value)
		 (destructuring-bind (new) (cdr option)
		   (if (typep new type)
		       new
		       (error "Invalid ~S value in DEFPACKAGE for ~A: ~S."
			      (car option)
			      package-name
			      new))))))
      (dolist (option options)
	(macrolet ((simple-merge (old)
		     `(setf ,old (merge-names ,old (cdr option))))
		   (alist-merge (old)
		     `(setf ,old (merge-name-alists ,old (cdr option)))))
	  (case (and (consp option) (car option))
	    (:size
	     (setf size (resolve-single option size '(integer 0))))
	    (:documentation
	     (setf doc (resolve-single option doc 'string)))
	    (:use
	     (setf use-default nil)
	     (simple-merge use))
	    (:nicknames (simple-merge nicknames))
	    (:shadow (simple-merge shadow))
	    (:intern (simple-merge intern))
	    (:export (simple-merge export))
	    (:shadowing-import-from (alist-merge shadowing-import-from))
	    (:import-from (alist-merge import-from))
	    (t
	     ;; This should be PROGRAM-ERROR.
	     (error "Unrecognized DEFPACKAGE option: ~S." option))))))
    (check-shadow-intern-import-conflicts
     shadow
     intern
     (check-import-conflicts shadowing-import-from
			     :shadowing-import-from
			     package-name)
     (check-import-conflicts import-from
			     :import-from
			     package-name)
     package-name)
    (check-intern-export-conflicts intern export package-name)
    (when use-default (setq use '("TCL")))
    (let ((form (make-defpackage-form package-name nicknames
				      shadow shadowing-import-from
				      use import-from intern export)))
      (when (and *shadow-not-supported*
		 (or shadow shadowing-import-from))
	(eval form)
	(let ((package (find-package package-name))
	      (new-import-from-alist nil)
	      (translator-packages-rev (reverse *translator-packages*)))
	  (do-symbols (symbol package)
	    (let ((p (symbol-package symbol)))
	      (unless (eq p package)
		(let* ((p (dolist (rp translator-packages-rev p)
			    (multiple-value-bind (sym therep)
				(find-symbol (symbol-name symbol) rp)
			      (when (and therep (eq sym symbol))
				(return rp)))))
		       (a (assq p new-import-from-alist)))
		  (unless a
		    (push (setq a (cons p nil)) new-import-from-alist))
		  (pushnew symbol (cdr a))))))
	(setq shadow nil
	      shadowing-import-from nil
	      use nil
	      import-from (mapcar #'(lambda (a)
				      `(,(package-name (car a))
					,@(mapcar #'symbol-name (cdr a))))
				  new-import-from-alist)))
	(setq form (make-defpackage-form package-name nicknames
					 shadow shadowing-import-from
					 use import-from intern export)))
      form)))

(defun make-defpackage-form (package-name nicknames
					  shadow shadowing-import-from
					  use import-from intern export)
  (let ((pkg (make-symbol "NEW-PACKAGE")))
    (labels ((make-simple-collector (fname)
	       #'(lambda (name) (list fname name pkg)))
	     (make-import-collector (fname)
	       #'(lambda (entry)
		   (let ((source (car entry)))
		     (mapcan #'(lambda (name)
				 (unless (equal (string name) "NIL")
				   (list (list fname name source pkg))))
			     (cdr entry)))))
	     (collect-simple (fname names)
	       (mapcar (make-simple-collector fname) names))
	     (collect-import (fname alist)
	       (mapcan (make-import-collector fname) alist)))
      `(let ((,pkg (find-package ,package-name)))
	 (if (null ,pkg)
	     (setf ,pkg (make-package ,package-name
				      :nicknames ',nicknames
				      :use nil))
	     (rename-package ,pkg ,package-name ',nicknames))
	 ,@(collect-simple 'trun:defpackage-shadow shadow)
	 ,@(collect-import 'trun:defpackage-shadowing-import-from
			   shadowing-import-from)
	 ,@(collect-simple 'trun:defpackage-use-package use)
	 ,@(collect-import 'trun:defpackage-import-from import-from)
	 ,@(collect-simple 'trun:defpackage-intern intern)
	 ,@(collect-simple 'trun:defpackage-export export)
	 ;; *** Should do something with doc-string here...
	 ,pkg))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Runtime support
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; The real runtime versions of these guys could possibly be defined to take
;;; untagged strings for the "name" arguments, and all the constant strings
;;; in the calls generated by DEFPACKAGE tweaked to be immediate C strings.
;;; These versions are provided so that the (EVAL-WHEN (COMPILE) ...) part
;;; of the expansion of DEFPACKAGE will work correctly.
;;; The return values are not used.

(defun trun:defpackage-shadow (name package)
  (shadow (intern name package) package))

(defun trun:defpackage-shadowing-import-from (name from-package-name package)
  (shadowing-import (dont-intern name from-package-name)
		    package))

(defun trun:defpackage-use-package (package-name package)
  (use-package package-name package))

(defun trun:defpackage-import-from (name from-package-name package)
  (import (dont-intern name from-package-name)
	  package))

(defun trun:defpackage-intern (name package)
  (intern name package))

(defun trun:defpackage-export (name package)
  (export (intern name package) package))


;;; Helper function for handling the :SHADOWING-IMPORT-FROM and 
;;; :IMPORT-FROM clauses.  This is basically just find-symbol that
;;; signals an error if the symbol isn't found.

(defun dont-intern (symbol-name package-name)
  (multiple-value-bind (symbol therep)
      (find-symbol symbol-name package-name)
    (if therep
	symbol
	(progn
	  (cerror "Intern ~s in the ~s package."
		  "There is no symbol named ~s accessible in the ~s package."
		  symbol-name package-name)
	  (intern symbol-name package-name)))))





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Extensions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; This is a *host* macro intended to be executed in the *host* Lisp.
;;; Its intent is to cause the package to be created in the normal way
;;; in the host environment, but also to save information about the
;;; package to enable it to be treated as a "static", initial package.
;;; The use of this macro is essentially a guarantee that the use
;;; relationships involving this package will be exactly the same at
;;; runtime as at translation time and that the listed symbols will
;;; be accessible in exactly the same way at runtime as at translation
;;; time.
;;; There are a couple of additional options supported:
;;; (:runtime-name <name>)
;;; (:runtime-nicknames &rest <nicknames>)
;;;     permits the package to have a different set of names at runtime
;;;     than at translation time

(define-translator-property defined-as-package 'copy-package-descriptor)
(define-translator-property defined-as-symbol
    'copy-symbol-descriptor 'free-symbol-descriptor)

;;; Functional version for forward references

(defun forward-defined-as-symbol (x)
  (defined-as-symbol x))

(defmacro define-static-package (package-name &rest options)
  `(progn
     (defpackage ,package-name
	 ,@(remove-if #'nonstandard-defpackage-option-p options))
     (install-static-package-aux ',package-name ',options)))

(defun nonstandard-defpackage-option-p (option)
  (member (car option)
	  '(:runtime-name
	    :runtime-nicknames)))


;;; This variable is used to ensure that packages are created in the
;;; right order.  It's incremented each time we make a new package
;;; descriptor, and the field is later used to sort the descriptors.

(defvar *package-sequence-number* 0)

(defstruct (package-descriptor
	     (:include descriptor))
    (sequence-number        (incf *package-sequence-number*))
    (size                   nil)
    (name                   nil)
    (nicknames              nil)
    (shadow                 nil)
    (shadowing-import       nil)
    (use                    nil)
    (import                 nil)
    (intern                 nil)
    (export                 nil)
    (documentation          nil)
    (body-variable          nil)    ; Symbol -> Foo_package_body
    (symbol-table           nil)    ; Symbol -> Foo_symtab
    (init-table             nil))   ; Symbol -> Foo_init_table

(defstruct (symbol-descriptor
	     (:include descriptor)
	     (:copier nil)
	     (:constructor %make-symbol-descriptor))
    (package                nil)
    (flags                  0))

(define-flags symbol-descriptor- symbol-descriptor-flags
    (used-by-runtime        nil)
    (magicp                 nil)    ; Don't dump declaration or initializer
    (occurs-in-runtime      nil)
    (quoted-p               nil))

(defvar *first-free-symbol-descriptor* nil)

(defmacro make-symbol-descriptor (&rest args)
  (let ((new-args nil)
	(new-flags nil)
	(flags-p nil) (flags-form nil)
	(flags-var (make-symbol "FLAGS")))
    (loop (unless args (return nil))
	  (let ((key (pop args))
		(form (pop args)))
	    (if (eq key ':flags)
		(setq flags-p t flags-form form)
		(if (member key *symbol-descriptor-flags*)
		    (progn (push key new-flags) (push form new-flags))
		    (progn (push key new-args)  (push form new-args))))))
    (setq new-args `(:flags ,flags-var ,@(nreverse new-args)))
    `(let ((,flags-var ,(if flags-p
			    flags-form
			    `(make-symbol-descriptor-flags
			      ,@(nreverse new-flags)))))
       ,(tutil::make-or-reuse-form new-args
				   '%make-symbol-descriptor
				   '*first-free-symbol-descriptor*
				   'descriptor-file-cookie
				   'symbol-descriptor-
				   *timpl-package*))))

(defun free-symbol-descriptor (sd)
  (setf (symbol-descriptor-package sd) nil)
  (setf (symbol-descriptor-flags sd) 0)
  (shiftf (descriptor-file-cookie sd)
	  *first-free-symbol-descriptor* sd)
  nil)

(defun copy-symbol-descriptor (sd)
  (make-symbol-descriptor
   :file-cookie (descriptor-file-cookie sd)
   :package (symbol-descriptor-package sd)
   :flags (symbol-descriptor-flags sd)))

;;; Parse the package options and make a package descriptor.
;;; Assume that the host DEFPACKAGE has already done some of the trickier
;;; syntax checking.  Also assume that the package has already been set
;;; up and that all of the symbols referenced in the options have
;;; actually been created and installed.

;;; The reason define-static-package can't just replace the "old" package
;;; definition by the new one is that, if *local-symbols* is false,
;;; new symbols are added to the package descriptor as translation is
;;; progressing.  Re-executing a define-static-package form would
;;; leave the Translator in an inconsistent state, with global
;;; "definitions" (defined-as-symbol) for the application's symbols,
;;; but no accounting for them in the package descriptor.  -- wb


(defmacro install-static-package (package-name &rest options)
  `(install-static-package-aux ',package-name ',options))

(defun enter-symbol (symbol hash-table)
    (setf (gethash symbol hash-table) t))

(defun unenter-symbol (symbol hash-table)
    (remhash symbol hash-table))

(defun symbol-entered-p (symbol hash-table)
  (gethash symbol hash-table))

(defparameter *the-lisp-package*
  (find-package #-(or MCL Genera translating) "LISP"
		#+(or MCL Genera) "COMMON-LISP"
		#+translating "TCL"))
(defparameter *the-user-package*
  (find-package #-(or MCL Genera translating) "USER"
		#+(or MCL Genera) "CL-USER"
		#+translating "TCL-USER"))

(defun find-remote-package (package)
  ;; Figure out what package the user probably means, for error-message-
  ;; generation purposes.
  (when (and package
	     ;; If already exists as a static package, presumably the
	     ;; user knows what he's doing; maybe he's renamed TCL
	     (not (defined-as-package package)))
    (cond ((eq package *the-lisp-package*) *tcl-package*)
	  ((eq package *the-user-package*) *tcl-user-package*))))

(defun find-remote-package-name (package)
  (let ((package (find-remote-package package)))
    (when package (package-name package))))

(defun mark-quoted-symbol (symbol)
  ;; Mark SYMBOL as quoted by application
  ;; This function identifies a newly-encountered quoted symbol as
  ;;    `global' and quoted.
  (let ((symbol-descriptor (defined-as-symbol symbol)))
    (unless (and symbol-descriptor
		 (symbol-descriptor-quoted-p symbol-descriptor))
      (let ((package (if symbol-descriptor
			  (symbol-descriptor-package symbol-descriptor)
			  (symbol-package symbol))))
	(if package
	    (let ((package-descriptor (defined-as-package package)))
	      (unless package-descriptor
		(error "Trying to create global symbol ~S, but~
            ~%global package ~A isn't defined statically.~
         ~%~:[Add a DEFPACKAGE form to your application source code~
            ~%before any references to symbols in this package.~;~
              Place the form (IN-PACKAGE ~:*~S) at the top of this file, or~
            ~%use a package qualifier to place this symbol in package ~:*~A.~]"
		       symbol
		       (package-name package)
		       (find-remote-package-name package)))
	      (multiple-value-bind (ignore therep)
		  (find-symbol (symbol-name symbol) package)
		(declare (ignore ignore))
		(enter-symbol-in-package (if (eq therep :external) 'export
					     'intern)
					 symbol
					 package)))
	    (when (null symbol-descriptor)
	      (setf (defined-as-symbol symbol)
		    (make-symbol-descriptor :package nil))))
	(unless symbol-descriptor
	  (setq symbol-descriptor (defined-as-symbol symbol)))
	(unless symbol-descriptor
	  (error "Internal error:  ENTER-SYMBOL-IN-PACKAGE failed ~
             to create symbol descriptor for ~S" symbol))
	(setf (symbol-descriptor-quoted-p symbol-descriptor) t)))))

(defun make-symbol-table ()
  (make-hash-table :test #'eq))

(defun map-symbol-table (function table)
  (maphash #'(lambda (key value)
	       (declare (ignore value))
	       (funcall function key))
	   table))

(defun install-static-package-aux (package-name options)
  (setq package-name (string package-name))
  (let* ((package           (find-package package-name))
	 (therep            (defined-as-package package))
	 (descriptor        (or therep
				(make-package-descriptor))))
    (when (and therep *verbose-warnings*)
      (warn "A definition for static package ~A has already been~
             ~%encountered.  Will merge options from the new definition~
             ~%into the existing definition."
	    package-name))
    (let ((size              (if therep
				 (package-descriptor-size descriptor)
				 nil))
	  (name              (if therep
				 (package-descriptor-name descriptor)
				 package-name))
	  (nicknames         (if therep
				 (package-descriptor-nicknames descriptor)
				 nil))
	  (shadow            (if therep
				 (package-descriptor-shadow descriptor)
				 (make-symbol-table)))
	  (shadowing-import  (if therep
				 (package-descriptor-shadowing-import
				  descriptor)
				 (make-symbol-table)))
	  (use               (if therep
				 (package-descriptor-use descriptor)
				 nil))
	  (use-p             (if therep t nil))
	  (import            (if therep
				 (package-descriptor-import descriptor)
				 (make-symbol-table)))
	  (intern            (if therep
				 (package-descriptor-intern descriptor)
				 (make-symbol-table)))
	  (export            (if therep
				 (package-descriptor-export descriptor)
				 (make-symbol-table)))
	  (documentation     (if therep
				 (package-descriptor-documentation
				  descriptor)
				 nil)))
      (dolist (o options)
	(case (car o)
	  (:size
	   (setq size (cadr o)))
	  (:nicknames
	   (setq nicknames
		 (nunion nicknames (mapcar #'string (cdr o))
			 :test #'string=)))
	  (:runtime-name
	   (setq name (string (cadr o))))
	  (:runtime-nicknames
	   (setq nicknames
		 (nunion nicknames
			 (mapcar #'string (cdr o))
			 :test #'string=)))
	  (:shadow
	   (dolist (n (cdr o))
	     (let ((s  (install-static-symbol (string n) package nil)))
	       (enter-symbol s shadow))))
	  (:shadowing-import-from
	   (let ((package   (string (cadr o))))
	     (dolist (n (cddr o))
	       (let ((s  (find-static-symbol (string n) package)))
		 (enter-symbol s shadowing-import)))))
	  (:use
	   (setq use-p t)
	   (dolist (p (cdr o))
	     (setq p (string p))
	     (find-static-package p)
	     (pushnew (find-package p) use)))
	  (:import-from
	   (let ((package  (string (cadr o))))
	     (dolist (n (cddr o))
	       (let ((s  (find-static-symbol (string n) package)))
		 (enter-symbol s import)))))
	  (:intern
	   ;; The argument can include symbols that are already
	   ;; accessible by inheritance.  Filter them out and
	   ;; collect only "new" symbols for dump.
	   (dolist (n (cdr o))
	     (multiple-value-bind (s therep)
		 (install-static-symbol (string n) package nil)
	       (if (not therep)
		   (enter-symbol s intern)))))
	  (:export
	   ;; The argument can include symbols that are already
	   ;; accessible in the package (by inheritance or by
	   ;; shadow or shadowing-import or import), as well as
	   ;; "new" symbols.
	   ;; Add any symbols that are "new" to the intern list.
	   ;; Add any symbols that aren't already directly accessible
	   ;; in this package to the "import" list.
	   ;; Dump assumes that all symbols on the export list are
	   ;; created elsewhere.
	   (dolist (n (cdr o))
	     (multiple-value-bind (s therep)
		 (install-static-symbol (string n) package t)
	       (cond ((not therep)
		      (enter-symbol s intern))
		     ((not (eq (symbol-descriptor-package therep)
			       package))
		      (enter-symbol s import))
		     ;; This is designed to handle the case
		     ;; where 
		     (t (enter-symbol s intern)))
	       (enter-symbol s export))))
	  (:documentation
	   (setq documentation (cadr o)))
	  (t
	   (warn "Ignoring unrecognized DEFPACKAGE option ~s." o))
	  ))
      (let ((body-variable     (if therep
				   (package-descriptor-body-variable 
				    descriptor)
				   (make-symbol
				    (concatenate 'string name "-PACKAGE"))))
	    (symbol-table      (if therep
				   (package-descriptor-symbol-table
				    descriptor)
				   (make-symbol
				    (concatenate 'string name "-SYMTAB"))))
	    (init-table	 (if therep
			     (package-descriptor-init-table descriptor)
			     (make-symbol
			      (concatenate 'string name "-INIT")))))
	(setf (package-descriptor-size descriptor) size
	      (package-descriptor-name descriptor) name
	      (package-descriptor-nicknames descriptor) nicknames
	      (package-descriptor-shadow descriptor) shadow
	      (package-descriptor-shadowing-import descriptor)
	      shadowing-import
	      (package-descriptor-use descriptor)
	      (if use-p use (list *tcl-package*))
	      (package-descriptor-import descriptor) import
	      (package-descriptor-intern descriptor) intern
	      (package-descriptor-export descriptor) export
	      (package-descriptor-documentation descriptor) documentation
	      (package-descriptor-body-variable descriptor) body-variable
	      (package-descriptor-symbol-table descriptor) symbol-table
	      (package-descriptor-init-table descriptor) init-table)
	(unless therep
	  (notice-translator-package package)
	  (setf (defined-as-package package) descriptor))
	;; Reserve a name for the package
	(c-name-of-package package)
	package-name))))


;;; helper functions

(defun find-static-symbol (name package)
  (multiple-value-bind (symbol therep) (find-symbol name package)
    (cond ((not therep)
	   (error "There is no symbol ~s accessible in package ~s."
		  name package))
	  ((not (symbol-descriptor-package (defined-as-symbol symbol)))
	   (error "~s has not been defined as a static symbol." symbol))
	  (t
	   symbol))))

(defun find-static-package (name)
  (let ((package  (if (packagep name) name (find-package name))))
    (cond ((null package)
	   (error "Package ~s does not exist." name))
	  (t
	   (find-static-package-aux package)))))

(defun find-static-package-aux (package)
  (or (defined-as-package package)
      (error "~s has not been defined as a static package." package)))

(defun install-static-symbol (name package external-p)
  (multiple-value-bind (symbol therep) (find-symbol name package)
    (cond ((not therep)
	   (error "There is no symbol ~s accessible in package ~s."
		  name package))
	  ((and external-p (not (eq therep :external)))
	   (error "The symbol ~s is not external in package ~s."
		  symbol package))
	  ((setq therep (defined-as-symbol symbol))
	   (values symbol therep))
	  (t
	   (setf (defined-as-symbol symbol)
		 (make-symbol-descriptor
		  :package package))
	   (c-name-of-quoted-symbol symbol)
	   (values symbol nil)))))


;;; This is called from declare.lisp while processing the database.

(defun install-exported-symbol (symbol package magicp)
  (when (not magicp)
    (let ((descriptor          (find-static-package-aux package))
	  (symbol-descriptor   (defined-as-symbol symbol)))
      (if (and symbol-descriptor
	       (eq (symbol-descriptor-package symbol-descriptor)
		   package))
	  (enter-symbol symbol (package-descriptor-intern descriptor))
	  (enter-symbol symbol (package-descriptor-import descriptor)))
      (enter-symbol symbol (package-descriptor-export descriptor))))
  symbol)


;;; Handlers for calls to package primitives encountered as
;;; top-level forms with constant arguments when *local-symbols* is false;
;;; this helps provide backwards-compatibility for pre-ANSI applications which
;;; use this idiom.
;;; This is conditionalized for *ansi-semantics* because (kab):
;;; X3J13's decision to eliminate the compile-time behavior of these
;;; functions was a very carefully considered incompatible change that was
;;; enabled by the addition of defpackage to the language.  Programs which
;;; assume ANSI semantics and have explicit calls to package operations
;;; are almost certainly doing tricky things that will very likely be
;;; broken by the code you are generating.

;;; Notes:
;;; - Could define handler for USE-PACKAGE.
;;; - Could clean up expansion of IN-PACKAGE.

(defmacro define-package-primitive-handler (function)
  `(define-translator-compiler-macro ,function
        (&whole form symbols &optional (package (package-name *package*))
		&environment env)
     (expand-package-call ',function form symbols package env)))

(define-package-primitive-handler export)

(define-package-primitive-handler import)

(define-package-primitive-handler shadow)

(define-package-primitive-handler shadowing-import)

(defun expand-package-call (function form symbols-form package-form env)
  (declare (ignore function symbols-form package-form env))
  form)


;;; Helper function to attempt to ensure consistency 
;;; of package descriptor contents

;;; Entries are of the form
;;; (slot preposition accessor conflicts)
;;; where each conflict entry is of the form
;;; (other-slots accessors-to-update error-function accessors-to-remove)

;;; This should be merged for the code in INSTALL-STATIC-PACKAGE-AUX
;;; above; handling of EXPORT is probably buggy (doesn't look
;;; at accessibility, etc.)

(defparameter *package-descriptor-slots*
  '((import "into" package-descriptor-import
	           ((intern shadow shadowing-import)
		    ()
		    error
		    nil)
	           (t (package-descriptor-import) nil nil))
    (intern "in" package-descriptor-intern
	         ((import shadow shadowing-import)
		  () 
		  nil
		  nil)
	         (t (package-descriptor-intern) nil nil))
    (export "from" package-descriptor-export
                   ((import intern shadow shadowing-import)
		    (package-descriptor-export)
		    nil
		    nil)
	           (t
		    (package-descriptor-intern package-descriptor-export)
		    nil
		    nil))
    (shadow "in" package-descriptor-shadow
	         ((import shadowing-import)
		  (package-descriptor-shadowing-import)
		  warn
		  (package-descriptor-import))
	         ((shadowing-import) () error nil)
		 ((intern) () error nil)
		 (t (package-descriptor-shadow) nil nil))
    (shadowing-import "into" package-descriptor-shadowing-import
		      ((import intern shadow) () error nil)
		      (t
		       (package-descriptor-shadowing-import)
		       nil
		       nil))))

(defun enter-symbol-in-package (slot symbols package)
  (let* ((slot-entry (assoc slot *package-descriptor-slots*))
	 (preposition (second slot-entry))
	 (conflicts (cdddr slot-entry))
	 (descriptor (find-static-package package))
	 (package-name (package-name package)))
    (unless slot-entry
      (error "Internal error - Unknown package accessor:  ~S" slot))
    (unless (consp symbols)
      (setq symbols (list symbols)))
    (dolist (symbol symbols)
      (let ((symbol-descriptor (defined-as-symbol symbol))
	    conflict-slot)
	(dolist (other-slot-entry conflicts)
	  (let ((other-slots (car other-slot-entry)))
	    (when (or (eq other-slots t)
		      (setq conflict-slot
			    (find-if
			     #'(lambda (other-slot)
				 (let ((other-accessor
					(third 
					  (assoc other-slot
						 *package-descriptor-slots*))))
				   (symbol-entered-p symbol
				     (funcall other-accessor descriptor))))
			     other-slots)))
	      (destructuring-bind
		  (accessors-to-update error-function accessors-to-remove)
		  (cdr other-slot-entry)
		(when error-function
		    (funcall error-function
			"Attempting to ~(~A~) global symbol ~S ~A package ~A,~
		       ~%but it's already identified as ~(~A~)ed.~
		       ~%To ensure consistency, ~(~A~) the symbol in the ~
		       ~%DEFINE-STATIC-PACKAGE form for package ~S."
			slot symbol preposition package-name conflict-slot
			slot package-name))
		(dolist (a accessors-to-update)
		  (enter-symbol symbol (funcall a descriptor)))
		(dolist (a accessors-to-remove)
		  (unenter-symbol symbol (funcall a descriptor))))
	      (when (null symbol-descriptor)
		(setf (defined-as-symbol symbol)
		      (make-symbol-descriptor
		         :package (symbol-package symbol))))
	      (return)))))))
  t)

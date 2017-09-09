;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; namespaces -- defines the various C namespaces
;;;
;;; Author : John Gilson
;;;
;;; Copyright (C) 1991, Chestnut Software, Inc. All Rights Reserved.

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/namespaces.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2007/05/21 21:57:23 $")



;;; This is the high-level interface to the low-level name mapping utilities.
;;; For objects in the runtime library, we declare or compute the name of the
;;; corresponding C object.

(defmacro define-c-namespace
    (external-accessor internal-accessor lambda-list &body body)
  `(progn
     (define-translator-property ,internal-accessor #'identity)
     ;; This would be a lot more cleanly done with a SETF function, but not
     ;; all implementations support such.
     (defsetf ,external-accessor (name) (string)
       `(progn
	  (multiple-value-bind (.old-c-name. .therep.)
	      (,',internal-accessor ,name)
	    (check-global-c-name ,string .old-c-name. .therep.))
	  (setf (,',internal-accessor ,name) ,string)))
     (defun ,external-accessor (name)
       (or (,internal-accessor name)
	   (setf (,internal-accessor name)
		 ((lambda ,lambda-list ,@body)
		  (if (environment-entry-p name)
		      (environment-entry-name name)
		      name)))))
     ',external-accessor))

(defvar *tell-about-amffpcn* t)

(defun check-global-c-name (c-name old-c-name therep)
  (when (and (or (not therep) (not (string= c-name old-c-name)))
	     (c-name-conflict-p c-name t))
    (if *tell-about-amffpcn*
	(progn
	  (setq *tell-about-amffpcn* nil)
	  (cerror "Use it anyway."
		  "The global C identifier ~S is already in use.~@
                   (Set ~S to T~@
                   to avoid this continuable error.)"
		  c-name 
		  'timpl::*allow-multiple-foreign-functions-per-c-name*))
	(cerror "Use it anyway."
		"The global C identifier ~S is already in use."
		c-name)))
  (record-global-c-name c-name))

(defun symbol-for-function-name (name &optional (prefix ""))
  (cond ((symbolp name)
	 (values name prefix))
	((consp name)
	 (values (principal-name-of-function-name name)
		 (sformat "~A~A_" prefix (car name))))
	((valid-function-name-p name)
	 (error "Translator bug -- Can't determine symbol for ~S." name))
	(t
	 (invalid-function-name-error name))))

(define-c-namespace c-name-of-function-object name-of-function-object (name)
  (multiple-value-bind (name prefix)
      (symbol-for-function-name name "F")
    (multiple-value-bind (string case)
	(string-canonicalize-case (string-trim-stars name))
      (string->c-name string t :case case :symbol name :prefix prefix))))

(define-c-namespace c-name-of-function-entry name-of-function-entry (name)
  (multiple-value-bind (name prefix)
      (symbol-for-function-name name)
    (multiple-value-bind (string case)
	(string-canonicalize-case (string-trim-stars name))
      (string->c-name string t :case case :symbol name :prefix prefix))))

(defun make-capitalized-c-name (string prefix symbol)
  (setf string (nstring-downcase string))
  (setf string (string->legal-c-name string :downcase prefix))
  (unless (zerop (length string))
    (setf (char string 0) (char-upcase (char string 0))))
  (string->c-name string t
		  :case :downcase
		  :symbol symbol
		  :prefix prefix))


;;; Not used any longer....
;(define-c-namespace c-name-of-function-macro name-of-function-macro (name)
;  (multiple-value-bind (name prefix)
;      (symbol-for-function-name name)
;    (make-capitalized-c-name (copy-seq (string-trim-stars name))
;			     prefix
;			     name)))

(define-c-namespace c-name-of-global-variable name-of-global-variable (name)
  (make-capitalized-c-name (copy-seq (string-trim-stars name))
			   ""
			   name))

(define-c-namespace c-name-of-quoted-symbol name-of-quoted-symbol (name)
  (multiple-value-bind (string case)
      (string-canonicalize-case (string-trim-stars name))
    (string->c-name string t
		    :case case
		    :symbol name
		    :prefix (if (keywordp name) "K" "Q"))))

(define-c-namespace c-name-of-package name-of-package (package)
    (let ((name  (make-symbol (package-name package))))
	(multiple-value-bind (string case)
		(string-canonicalize-case (string-trim-stars name))
	    (string->c-name string t
			    :case case
			    :symbol name
			    :prefix "P"))))

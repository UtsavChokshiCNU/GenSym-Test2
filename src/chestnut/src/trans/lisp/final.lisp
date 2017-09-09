;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; final.lisp -- initializing the initial global environment
;;;
;;; Copyright (c) 1993, Chestnut Software Inc.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/final.lisp,v $"
 "$Revision: 1.5 $"
 "$Date: 2007/07/12 18:29:34 $")

#+translator-supports-clos
(tclosi:initialize-generic-functions *default-global-environment*)

;;; This is for patching deftranslate functions.
(defun install-deftranslate (name)
  (when (boundp '*initial-global-environment*)
    (let* ((fn (defined-as-special-form name))
	   (*default-global-environment* *initial-global-environment*))
      (setf (defined-as-special-form name) fn)))
  name)

(defun install-define-translator-macro (name)
  (when (boundp '*initial-global-environment*)
    (let* ((fn (defined-as-macro name))
	   (*default-global-environment* *initial-global-environment*))
      (setf (defined-as-macro name) fn)))
  name)

;;; Not sure where this really belongs. It's from patch-5, and it can't work
;;; until array-symbols has been read. So I'm putting it here.

;;; Probably the Right thing is an additional entry in the symbol definition
;;; for these symbols, and a modification to define-symbols to set this
;;; flag. -alatto, 5/22/07
(dolist (n+name *setf-aref-transforms*)
  (setf (function-descriptor-array-setf-function-p
	 (defined-as-function (cdr n+name)))
	t))

#+translator-supports-clos
(pushnew :translator-supports-clos *features*)

(pushnew :translator-is-loaded *features*)
(pushnew ':dll-function *features*)

#+lucid
(defun fix-hash-tables ()
  ;; there seems to be a bug in lcl 4.1 involving eq hash-tables and disksave.
  (lcl:rehash (tutil::translator-environment-global-simple-part
	       *default-global-environment*))
  (lcl:rehash (tutil::translator-environment-global-setf-symbol-part
	       *default-global-environment*))
  (lcl:rehash (tutil::translator-environment-global-other-part
	       *default-global-environment*))
  (when (boundp '*initial-global-environment*)
    (lcl:rehash (tutil::translator-environment-global-simple-part
		 *initial-global-environment*))
    (lcl:rehash (tutil::translator-environment-global-setf-symbol-part
		 *initial-global-environment*))
    (lcl:rehash (tutil::translator-environment-global-other-part
		 *initial-global-environment*)))
  (dolist (e tutil::*c-names*)
    (lcl:rehash (cdr e)))
  nil)

(defun final-initialization ()
  #+lucid
  (fix-hash-tables)
  (unless (boundp '*initial-global-environment*)
    ;;; Note that loading final will not typically compile and load patches.
    ;;; So the build script is now responsible for loading patches.
    (himpl::load-patches)
    (tutil::reserve-initial-c-names)
    (setq tutil::*c-names* (tutil::get-initial-c-names))
    (setq *initial-global-environment* *default-global-environment*)
    (setq *default-global-environment*
	  (copy-translator-environment *default-global-environment*)))
  (display-license-message))

(define-translator-parameter *inhibit-final-translator-initialization*
  nil)	

(if *inhibit-final-translator-initialization*
    (progn
      #+(and lucid translator-supports-clos)
      (lcl:precompile-generic-functions))
    (final-initialization))

#+lucid
(defvar %%old-top-level-hook-p%%
  (locally
      (declare (special user::*enter-top-level-hook*))
    (eq user::*enter-top-level-hook* #'enter-top-level-hook)))

#+lucid
(defun enter-top-level-hook ()
  (final-initialization))

#+lucid
(when %%old-top-level-hook-p%%
  (locally
      (declare (special user::*enter-top-level-hook*))
    (setq user::*enter-top-level-hook* #'enter-top-level-hook)))

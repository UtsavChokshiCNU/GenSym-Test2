(in-package #-ANSI-CL "USER"
	    #+ANSI-CL "CL-USER")

;; jh, 5/20/93.

;; cd /bt/ab/trans

;; invoke /home/lucid/lucid41/lisp-clos-411

;; load this file itself
;; (load "trans/gensym-load-trans.lisp")

;; run (disksave "/bt/ab/trans/trans-32b3c" :full-gc t)

(setq *inhibit-final-translator-initialization* t)

;;; Change this to load the translator from somewhere else.
(defvar *translator-directory* *default-pathname-defaults*)

(load (merge-pathnames "load-trans.lisp" *translator-directory*))

(pushnew :chestnut-3 *features*)

(defun enter-top-level-hook ()
  (declare (special *enter-top-level-hook*))
  (timpl::final-initialization)
  (setq *enter-top-level-hook* nil))

(compile 'enter-top-level-hook)

(setq *enter-top-level-hook* #'enter-top-level-hook)

(setq *translator-binary-directory*
      (make-pathname :directory
		     (append (pathname-directory *translator-directory*)
			     '("OBIN"))
		     :defaults *translator-directory*))

(setq himpl::*patch-source-directory*
      (make-pathname :directory
		     (append (pathname-directory *translator-directory*)
			     '(:up "patches"))))

#-lcl4.2
(progn
(change-memory-management :expand 5)
(ephemeral-gc t)
(dynamic-gc)
)

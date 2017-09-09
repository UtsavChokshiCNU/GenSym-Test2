(in-package :cl-user)

(setq *inhibit-final-translator-initialization* t)

;;; Change this to load the translator from somewhere else.
(defvar *translator-directory* *default-pathname-defaults*)

(load (merge-pathnames "load-trans.lisp" *translator-directory*))

(pushnew :chestnut-3 *features*)

(defun enter-top-level ()
  ;;Initialize translator
  (timpl::final-initialization)
  ;;Run SBCL's regular top-level.
  ;;(sb-impl::repl-fun nil))

(setq *translator-binary-directory*
      (make-pathname :directory
		     (append (pathname-directory *translator-directory*)
			     '("OBIN"))
		     :defaults *translator-directory*))

(setq himpl::*patch-source-directory*
      (make-pathname :directory
		     (append (pathname-directory *translator-directory*)
			     '(:up "patches"))))

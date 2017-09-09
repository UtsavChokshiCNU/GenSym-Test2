;;;; -*- Mode: Lisp; -*-

(eval-when (:compile-toplevel :load-toplevel :execute)
  (unless (find-package :bundle)
    (defpackage bundle
      (:use :common-lisp))))

(in-package :bundle)

(defvar *skip-compiles* nil)

(defun fam-script-loader (&optional families)
  (unless *skip-compiles*
    (let ((*compile-verbose* nil)
          (*load-verbose*    nil))
      #+(or lispworks sbcl)
      (load (compile-file "package.lisp"))
      (load (compile-file "bundle.lisp"))
      (load (compile-file "createkey.lisp"))))
  (loop for family-symbol in (list families)
	as family = (string-downcase (string family-symbol)) do
    (load (format nil "~a-family.lisp" family))))

(defun new-fam-script-loader (&optional families)
  (unless *skip-compiles*
    (let ((*compile-verbose* nil)
          (*load-verbose*    nil))
      #+(or lispworks sbcl)
      (load (compile-file "package.lisp"))
      (load (compile-file "bundle.lisp"))
      (load (compile-file "createkey.lisp"))))
  (loop with list = (if (listp families) families (list families))
	for family-symbol in list
	as family = (string-downcase (string family-symbol))
	do (load (format nil "~a-family.lisp" family))))

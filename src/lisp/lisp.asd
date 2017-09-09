;;;; 2008-12-16 21:47:10
;;;;
;;;; Think of this as your project file.
;;;; Keep it up to date, and you can reload your project easily
;;;;  by right-clicking on it and selecting "Load Project"

(defpackage #:lisp-asd (:use :cl :asdf))

(in-package :lisp-asd)

; Add all the IDE init code here
(let ((SRCBOX (sb-ext:posix-getenv "SRCBOX")))
  (setf *default-pathname-defaults*
        (truename (concatenate 'string SRCBOX "\\lisp")))
  )
; End of the init block

(defsystem lisp
  :name "lisp"
  :version "0.1"
  :serial t
  :components ((:file "defpackage")
               ; G2 lisp files
               (:file "123" :depends-on ("defpackage"))
               
               ; G2 unit test files
               (:file "tests/123" :depends-on ("123"))
               (:file "tests/panes" :depends-on ("123")))
    :depends-on ())

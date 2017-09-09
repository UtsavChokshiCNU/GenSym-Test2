(asdf:defsystem #:cl-junit-xml.lisp-unit
  :serial t
  :description "cl-junit-xml extensions to work with lisp-unit"
  :author "Ryan Davis <ryan@acceleration.net>"
  :license "MIT"
  :depends-on (#:cl-junit-xml #:iterate #:alexandria #:lisp-unit #:cl-ppcre)
  :components ((:file "lisp-unit")))

(asdf:defsystem #:cl-junit-xml.lisp-unit2
  :serial t
  :description "cl-junit-xml extensions to work with lisp-unit2"
  :author "Ryan Davis <ryan@acceleration.net>"
  :license "MIT"
  :depends-on (#:cl-junit-xml #:iterate #:alexandria #:lisp-unit2 #:cl-ppcre)
  :components ((:file "lisp-unit2")))

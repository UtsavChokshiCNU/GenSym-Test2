;;;; cl-junit-xml.asd

(asdf:defsystem #:cl-junit-xml
  :serial t
  :description "Small library for writing junit XML files"
  :author "Ryan Davis <ryan@acceleration.net>"
  :license "MIT"
  :depends-on (#:cxml #:iterate #:alexandria)
  :components ((:file "package")
               (:file "cl-junit-xml")))

(defmethod asdf:perform ((o asdf:test-op) (c (eql (asdf:find-system :cl-junit-xml))))
  (asdf:load-system :cl-junit-xml.test)
  (let ((*package* (find-package :cl-junit-xml.test)))
    (eval (read-from-string "(run-tests)"))))

(asdf:defsystem #:cl-junit-xml.test
  :serial t
  :description "tests for cl-junit-xml"
  :author "Ryan Davis <ryan@acceleration.net>"
  :license "MIT"
  :depends-on (#:cl-junit-xml #:lisp-unit2)
  :components ((:file "tests")))

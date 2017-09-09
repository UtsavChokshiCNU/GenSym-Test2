;;;; -*- Mode: Lisp; Syntax: ANSI-Common-Lisp; Base: 10 -*-

(defsystem :mock-macro
  :name "Unit test utilities for G2, which must be loaded before building G2"
  :version "1.0"
  :serial t
  :components ((:file "mock-macro-package")
               (:file "mock-macro")) 
  )

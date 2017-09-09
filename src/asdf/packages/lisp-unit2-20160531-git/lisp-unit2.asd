;;;; -*- Mode: Lisp; Syntax: ANSI-Common-Lisp -*-
(in-package :asdf)

(defsystem :lisp-unit2
  :description "Common Lisp library that supports unit testing."
  :version "0.2.0"
  :author "Russ Tyndall <russ@acceleration.net>, Acceleration.net,
           Thomas M. Hermann <thomas.m.hermann@odonata-research.com>"
  :license "MIT"
  :serial t
  :components
  ((:file "package")
   (:file "assert-package")
   (:file "vars")
   (:file "collectors")
   (:file "asserts")
   (:file "lisp-unit")
   (:file "summarize")
   (:file "rational")
   (:file "floating-point")
   (:file "test-anything-protocol")
   (:file "interop"))
  :depends-on (:alexandria :cl-interpol :iterate :symbol-munger))

(defsystem :lisp-unit2-test
  :description "Tests for lisp-unit2 "
  :version "0.2.0"
  :author "Russ Tyndall <russ@acceleration.net>, Acceleration.net,
           Thomas M. Hermann <thomas.m.hermann@odonata-research.com>"
  :license "MIT"
  :serial t
  :components
  ((:module "internal-test"
    :serial t
    :components ((:file "packages")
                 (:file "basics")
                 (:file "floating-point")
                 (:file "example-tests"))))
  :depends-on (:lisp-unit2))

(defmethod asdf:perform ((o asdf:test-op) (c (eql (find-system :lisp-unit2))))
  (asdf:load-system :lisp-unit2-test)
  (let ((*package* (find-package :lisp-unit2-tests)))
    (eval (read-from-string
           "(lisp-unit2:run-tests
             :name :lisp-unit
             :run-contexts #'lisp-unit2:with-summary-context
             :package :lisp-unit2-tests)"))))


#|
  Copyright (c) 2013, Russ Tyndall, Acceleration.net
  Copyright (c) 2009-2012, Thomas M. Hermann

  Permission is hereby granted, free of charge, to any person obtaining 
  a copy of this software and associated documentation files (the "Software"), 
  to deal in the Software without restriction, including without limitation 
  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Software, and to permit persons to whom the 
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included 
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
  OTHER DEALINGS IN THE SOFTWARE.

|#

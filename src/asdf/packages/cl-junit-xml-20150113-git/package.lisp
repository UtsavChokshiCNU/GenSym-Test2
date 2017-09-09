;;;; package.lisp

(defpackage #:cl-junit-xml
  (:use #:cl #:iterate)
  (:export #:write-xml #:make-junit #:make-testcase #:make-testsuite #:add-child)
  (:shadowing-import-from #:cxml
                          #:with-xml-output #:with-element #:attribute #:cdata)
  (:shadowing-import-from #:alexandria
                          #:when-let))

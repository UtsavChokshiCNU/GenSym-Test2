;;
;; system :tests-part-0
(in-package :cl-user)

(defpackage :mock-macro
  (:use :cl)
  (:export
   #:prepare-macro-for-mocking
   #:enable-macroexpand-hook-for-mocking-macros
   #:unprepare-macro-for-mocking
   #:set-default-macroexpand-hook
   #:with-mocked-macros
   )
  )


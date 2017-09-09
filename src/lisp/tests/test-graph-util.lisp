(in-package :tests)

(define-test test-value-to-fixnum
  (assert-equal 10 (ab::value-to-fixnum 10d0)))


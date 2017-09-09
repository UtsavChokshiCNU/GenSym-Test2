(in-package :tests)

#+lispworks
(define-test test-general-get-command-line-argument
  (assert-equal (first system:*line-arguments-list*)
                (ab::general-get-command-line-argument 0)))
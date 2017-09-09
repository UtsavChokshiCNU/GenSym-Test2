(in-package :tests)


(define-test test-load-kb-tokens
  (with-simplest-test-environment ()
    (assert-true (ab::compile-permanent-lexing-table ab::load-kb-tokens))))





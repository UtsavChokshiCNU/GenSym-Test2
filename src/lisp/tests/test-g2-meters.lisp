(in-package :tests)

(define-test test-delta-memory-column-title-constant
  (assert-true (ab::wide-string-compare #w"Delta Memory" 
                                        ab::delta-memory-column-title t t)))

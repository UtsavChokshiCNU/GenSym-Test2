(in-package :tests)

(define-test test-z-modf-quick
  (assert-eql 3 (ab::modf-quick 13 10))
  (let ((result (or (eql 3 (ab::modf-quick -17 10))
		    (eql -7 (ab::modf-quick -17 10)))))
    (assert-true result)))

(in-package :tests)

(define-test do-test-initial-quantity-array-with-int64 ()
  (let ((arr (ab::make-entity (ab::evaluation-symbol-symbol 'quantity-array)))
        (element-arr) (i64))
    (setf (ab::g2-array-length arr) 2)
    (setf (ab::g2-array-initial-values arr) 
          (list (ab::make-g2longint-variable 1) 
                (ab::make-g2longint-variable 2)))
    (setf (ab::managed-g2-array arr) (ab::allocate-managed-g2-array 2 'number))
    (ab::fill-g2-array-with-initial-values-if-possible arr)
    (setf element-arr (ab::g2-array-aref-item-or-evaluation-value arr 0))
    (setq i64 (ab::make-g2longint-variable 1))
    (assert-true (ab::int64-signed-equal-p element-arr i64))
    t))

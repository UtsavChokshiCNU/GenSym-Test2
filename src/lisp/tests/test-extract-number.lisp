(in-package :tests)

(define-test test-managed-long-p 
  (let ((a 1)
        (c (ab::allocate-managed-long 3)))
    (assert-true (eval `(ab::managed-long-p ,c)))))

(defun extract-number-ab-test ()
  (let ((a 1)
        (b (eval '(ab::allocate-managed-float 3.0d0)))
	(c (eval '(ab::allocate-managed-long 3))))
    (and (= (eval `(ab::extract-number ,a)) 1)
         (= (eval `(ab::extract-number ,b)) 3.0d0)
	 (= (eval `(ab::extract-number ,c)) 3)))) 

(define-test test-z-extract-number
  (let ((result (extract-number-ab-test)))
    (assert-true result)))


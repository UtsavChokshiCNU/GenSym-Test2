(in-package :tests)

#|
 causes execution error in SBCL
 (define-test test-create-frame-vector-and-replenish-pool-fill-value
	(ab::with-system-variables ('ab::ab (make-symbol "CURRENT-PROCESS"))
		(assert-equal nil 
		  (svref (ab::create-frame-vector-and-replenish-pool 1) 0))))
|#

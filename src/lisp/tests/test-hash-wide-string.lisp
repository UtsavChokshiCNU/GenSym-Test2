(in-package :tests)

(define-test test-z-hash-wide-string
  (let* ((ws #w"widestring")
	 (ws2 #w"widestring")
	 (hashval (ab::hash-wide-string ws))
	 (hashval2 (ab::hash-wide-string ws2))
	 (result (and (>= hashval 0)
		      (<= hashval 268435455))))
    (assert-true result)
    (assert-eql hashval hashval2)))

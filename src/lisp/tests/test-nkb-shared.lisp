(in-package :tests)

(define-test test-nkc-format-numeric-text
	(assert-true (and (equalp #w"****" (nkc::nkc-format-numeric-text #w"****" #w"dd.ddd"))
				(equalp #w"35.300" (nkc::nkc-format-numeric-text #w"35.3" #w"dd.ddd"))
				)))

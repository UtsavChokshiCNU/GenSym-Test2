(in-package :tests)

;;
;; TODO: Rewrite using system-function-namespace-violations to find not listed
;;       evaluators
;; 
(defparameter *built-in-functions* 
  '(ab::kbf-g2nke-count-history-matching-op-and-eventflag 
    ab::count-datapoints-that-evaluate-true-with-eventflag
    ab::kbf-g2nke-count-history-matching-op
    ab::count-datapoints-that-evaluate-true))

(define-test test-built-in-functions
    (dolist (built-in-function *built-in-functions*) 
      (assert-true (member built-in-function ab::*built-in-functions*) 
                   built-in-function)))

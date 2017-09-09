(in-package :cl-user)

(load "threshold-checking-lib")
(asdf:load-system "lisp-unit")

(import (list 'lisp-unit:define-test 'lisp-unit:assert-equal 
              'lisp-unit:run-tests))

(define-test test-loading-performance-index
  (assert-equal 524.678883511281d0
                (load-performance-index "tests/test-performance-index.txt")))

(define-test test-compare-results-with-scaling
  (assert-equal 0.5126410722732544d0
                (compare 3.065 1.531 :actual-scale (/ 396.4369970091642
                                                      524.678883511281))))

(define-test test-compare-results-without-scaling
  (assert-equal 1.0019595623016357d0 (compare 3.065 1.531)))

(define-test test-compare-zero-results
  (assert-equal 0.0d0 (compare 0 0)))

(define-test test-compare-actual-zero-threshold-above-zero-results
  (assert-equal -1d0 (compare 0 10)))

(define-test test-compare-actual-above-zero-threshold-zero-results
  (assert-equal 1d++0 (compare 10 0)))

(define-test test-compare-results-without-scale
  (assert-equal (list -0.09090912342071533d0 0.0d0 1.0d0 1.5d0)
                (compare-results :actuals (list 1 2 3 5) 
                                 :thresholds (list 1.1 2 1.5 2))))

(define-test test-compare-results-with-scale
  (assert-equal (list 0d0 0d0 0d0 0d0)
                (compare-results :actuals (list 1 2 3 5) 
                                 :thresholds (list 2 4 6 10)
                                 :scale 2)))

;;;
;;; Format failure message
;;;


(define-test test-format-failure-message-for-comparison
  (let ((comparison (make-comparison :name "ext" :value 10 :threshold 20)))
    (assert-equal "Degradation: -0.5
Actual value: 10
Threshold: 20" (format-failure-message-for-comparison comparison))))

(define-test test-format-failure-message-for-comparison-with-tolerance
  (let ((comparison (make-comparison :name "ext" :value 10 :threshold 20 
                                     :tolerance 0.05d0)))
    (assert-equal "Degradation: -0.5
Actual value: 10
Threshold: 20
Tolerance: 0.05" (format-failure-message-for-comparison comparison))))

(define-test test-format-failure-message-for-comparison-with-tolerance-and-performance-indexes
  (let ((comparison (make-comparison :name "ext" :value 10 :threshold 20 
                                     :tolerance 0.05d0
                                     :actual-performance-index 300
                                     :threshold-performance-index 600)))
    (assert-equal "Degradation: -0.75
Actual value: 10
Threshold: 20
Tolerance: 0.05
Actual performance index: 300
Threshold performance index: 600" 
                  (format-failure-message-for-comparison comparison))))



(define-test test-produce-xml-for-comparison
  (let ((comparison (make-comparison :name "ext")))
    (assert-equal "<testcase name=\"ext\"/>" 
                  (produce-xml-for-comparison comparison))))

(define-test test-produce-xml-for-comparison
  (let ((comparison (make-comparison :name "ext" 
                                     :value 3.065d0
                                     :threshold 1.922d0)))
    (assert-equal "<testcase name=\"ext\">
  <failure>
    Degradation is 59.47%, current result is 3.065, threshold is 1.922
  </failure>
</testcase>" (produce-xml-for-comparison comparison))))

(run-tests)


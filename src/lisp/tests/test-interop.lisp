(in-package :tests)

(define-test test-c-g2nke-count-history-matching-op-and-eventflag
  (let ((arg-variable (make-array 18))
        (arg-event-flag (make-array 18)))
    (ab::c-g2nke-count-history-matching-op-and-eventflag 
     arg-variable 40 0 20 arg-event-flag 3 30 2)))
              
(define-test test-c-g2nke-count-history-matching-op
  (let ((arg-variable (make-array 18))
        (arg-event-flag (make-array 18)))
    (ab::c-g2nke-count-history-matching-op
     arg-variable nil nil nil nil 3 30 2 1 0)))

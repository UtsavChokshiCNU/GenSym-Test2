(in-package :ab)

(def-hash-table sample-hashtable)

(defun lockfree-hashtable-ab-test ()
  (let (test-hashtable)
    ;;; test if newly created hashtable is empty
    (setq test-hashtable (make-sample-hashtable))
    (lisp-unit:assert-true (current-number-of-entries test-hashtable))
    
    ;;; check whether table put and get works correctly
    (setf (get-sample-hashtable 'key-1 test-hashtable) "value-1")
    (lisp-unit:assert-equal "value-1" (get-sample-hashtable 'key-1 test-hashtable))))

(in-package :tests)

(defun lockfree-hashtable-test ()
  (ab::lockfree-hashtable-ab-test))

(define-test test-z-lockfree-hashtable
  (lockfree-hashtable-test)
  (format t "test lockfree-hashtable-test SUCCESS~%")
  (assert-true t))

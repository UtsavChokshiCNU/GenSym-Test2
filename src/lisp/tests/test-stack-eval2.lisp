(in-package :tests)

(define-test test-random-real-0
 (with-simplest-test-environment ()
   (let ((ab::*random-state-array-current-pointer* 54)
         (ab::*random-state-array-24-pointer* 30)
         (ab::*random-state-array* (make-array 55 :element-type 'fixnum)))
     (let ((random-real-0-success
            (ignore-errors
              (ab::random-real-0)
              t)))
       (assert-true random-real-0-success)))))

(in-package :tests)

(define-test test-get-sum-of-values
  (with-connection-test-environment ()
    (let ((fv (ab::make-frame 'ab::float-variable)))
      ; set up history setting
      (setf (ab::variable-or-parameter-history-specification? fv) '(ab::history nil 100))
      ; call get-sum-of-values function
      (assert-true (ab::null (ab::get-sum-of-values fv nil 0 50))))))

(in-package :tests)

;; the test make sure sxhash-lisp-object only accept unmoveable objects in LispWorks.

#+lispworks
(defun sxhash-lisp-object-test-1 ()
  (let* ((object-1
	  (ab::with-unmoveable-object-creation
	    (make-array 10 :initial-element 0)))
	 #+development (object-2 (make-array 10 :initial-element 0)))
    (multiple-value-bind (hash-1 error-1)
	(ignore-errors
	  (ab::sxhash-lisp-object object-1))
      (assert-true
       (and (< hash-1 ab::most-positive-fixnum)
            (null error-1))))
    ;; assertion in sxhash-lisp-object is for development only
    #+development 
    (multiple-value-bind (hash-2 error-2)
        (ignore-errors
          (ab::sxhash-lisp-object object-2))
      (and 
       (null hash-2)
       (typep error-2 'error)))))

#+ignore ; TODO: Cannot take CDR of T.
(define-test test-sxhash-lisp-object-1
             (sxhash-lisp-object-test-1))

; RETURN-HERE test define-loop-path hash-value more thoroughly - it is partially covered from test-loop. 

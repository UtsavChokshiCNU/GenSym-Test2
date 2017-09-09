(in-package #:cl-junit-xml)

(defmethod write-xml ((results lisp-unit2:test-results-db) sink &key pretty-p &allow-other-keys)
  (let* ((junit (make-junit))
         (suite (add-child junit (make-testsuite "lisp-unit2")))
         (name (lisp-unit2::name results))
         )
    (labels ((summary (test-result)
               (with-output-to-string (lisp-unit2:*test-stream*)
                 (lisp-unit2:print-summary test-result)))
             (test-class-name (test-result)
               (cl-ppcre:register-groups-bind (c)
                   ("(?:(.*)\\.)?[^\\.]+$" (test-case-name test-result))
                 (format nil "~a.~a" name (or c "root"))))
             (test-case-name (test-result)
               (princ-to-string
                (lisp-unit2::name (lisp-unit2:unit-test test-result)))))

      (iter (for test-result in-sequence (lisp-unit2:results results))
        (add-child suite
                   (make-testcase
                    (test-case-name test-result)
                    (test-class-name test-result)
                    ;; get duration in partial seconds
                    (/ (- (lisp-unit2::internal-end-time test-result)
                          (lisp-unit2::internal-start-time test-result))
                       internal-time-units-per-second)
                    :error (when (lisp-unit2:errors test-result)
                             (summary test-result))
                    :failure (when (lisp-unit2:failed test-result)
                               (summary test-result))))))

    (write-xml junit sink :pretty-p pretty-p)))

(defmethod write-xml ((c lisp-unit2:all-tests-complete) sink &key pretty-p &allow-other-keys)
  (write-xml (lisp-unit2:results c) sink :pretty-p pretty-p))

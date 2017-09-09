;;
;; system :tests-part-0
(in-package :cl-user)

(defpackage :tests
  (:use :cl :mock-macro :lisp-unit))

(eval-when (:load-toplevel :execute)
  ;; Not run (start-with-command-line-args-or-menu)
  (pushnew :under-test *features*)

  ;; Added by Chun Tian (binghe), 2010/6/3
  ;; to achieve the same effect after r81952.
  (pushnew :no-bootstrap *features*))

;;; A patch to lisp-unit (by Denis)
(in-package :lisp-unit)

(defun print-summary (test-result &optional
                      (stream *standard-output*))
  "Print a summary of the test result."
  (let* ((no-of-failed (length (fail test-result)))
         (failed-string (if (= 0 no-of-failed) "" (format nil ", ~S failed" no-of-failed))))
    (format stream "~&~A: ~S assertions passed~A"
            (name test-result)
            (pass test-result)
            failed-string)
    (if (exerr test-result)
        (format stream ", and an execution error.")
      (write-char #\. stream))
    (terpri stream)
    (terpri stream)))

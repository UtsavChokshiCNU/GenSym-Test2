;;;; -*- Mode: Lisp; Syntax: ANSI-Common-Lisp -*-
;;;; SEE Copyright below

(in-package :lisp-unit2)

;;; Symbols exported from the TAP extension

(defun with-tap-context (body-fn)
  (let ((i 0))
    (handler-bind
        ((all-tests-start
           (lambda (c)
             (format *test-stream* "TAP version 13~%1..~d~%"
                     (length (tests (results c))))))
         (test-complete
           (lambda (c) (%write-tap-test-result (result c) (incf i)))))
      (funcall body-fn))))

(defmacro with-tap-summary (() &body body)
  `(with-tap-context (lambda () ,@body)))

(defun %write-tap-test-result (test-result i)
  "Output a single test, taking care to ensure the indentation level
is the same before and after invocation."
  (pprint-test-block ()
    (let ((not-ok? (or (failed test-result)
                       (errors test-result)
                       (warnings test-result))))
      (format *test-stream*
              "~:[ok~;not ok~] ~d ~A (~,2f s)"
              not-ok? i (ignore-errors (short-full-name test-result))
              (run-time test-result))
      (when not-ok?
        ;; indent only takes affect after a newline, so force one
        (format *test-stream* "~4I~@:_---~@:_")
        (pprint-test-block (:per-line-prefix " # ")
          (iter (for s in '(errors failed warnings))
            (print-status-summary test-result s)))
        (format *test-stream* "~@:_..."))
      ;; always reset to zero and force a newline
      (format *test-stream* "~0I~@:_"))))

(defun write-tap (test-results)
  "Write the test results to `stream` in TAP format. Returns the test
results."
  (check-type test-results test-results-db)
  (let ((i 0)
        (*print-pretty* T))
    (format *test-stream* "TAP version 13~%1..~d~%" (length (tests test-results)))
    (iter (for res in-vector (results test-results))
      (%write-tap-test-result res (incf i))))
  test-results)

(defun print-tap (test-results)
  "Alias for write-tap for backwards and forwards consistency"
  (write-tap test-results))

(defun write-tap-to-file (test-results path)
  "write the test results to `path` in TAP format, overwriting `path`.
Returns pathname to the output file"
  (check-type path (or string pathname))
  (ensure-directories-exist path)
  (with-open-file (*test-stream* path :direction :output :if-exists :supersede)
    (write-tap test-results))
  (truename path))

#|

  Test Anything Protocol (TAP) support for LISP-UNIT

  Copyright (c) 2009-2013, Ryan Davis <ryan@acceleration.net>

  Permission is hereby granted, free of charge, to any person obtaining 
  a copy of this software and associated documentation files (the "Software"), 
  to deal in the Software without restriction, including without limitation 
  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Software, and to permit persons to whom the 
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included 
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
  OTHER DEALINGS IN THE SOFTWARE.

  References
  [TAP]: http://testanything.org/wiki/index.php/Main_Page
  
|#
;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

#+g2-lisp-unit
(progn
  (defvar *test-node* nil) ; name of the current test
  (defvar *test-node-count* 0) ; current assertion id
  (defvar *test-results* (gensym-list)) ; test results database
  (defvar *all-tests* (gensym-list)) ; list of test functions

  ;;; Stores a test result '(NODE ID ASSERTION PASSED? EXPECTED ACTUAL)
  ;;; in the test result database
  (defmacro record-test-result (node id assertion passed? expected actual)
    `(gensym-push
      (gensym-list ,node ,id ,assertion ,passed? ,expected ,actual)
      *test-results*))

  ;;; A wrapper for HANDLER-CASE, which is absent from G2
  (defmacro test-handler-case (&body body)
    #+development
    `(cl:handler-case
      (progn ,@body)
      (error (e)
	     (record-test-result *test-node* 0 'runtime-error nil nil e)))
    #-development
    `(progn ,@body))

  ;;; Runs all unit tests
  (defun run-all-unit-tests ()
    (loop for test in *all-tests* collect (funcall test) using gensym-cons))

  ;;; Prints a single test result in RG format
  (defun format-rg-entry (entry)
    (gensym-dstruct-bind
     ((node id assertion passed? expected actual) entry)
     (if passed?
	 (tformat "~a-~a,PASSED~%~a-~a,~%" node id node id)
	 (tformat "~a-~a,FAILED~%~a-~a,~a, expected: ~a, actual: ~a~%"
		  node id node id assertion expected actual))))

  ;;; Prints all test resulst in RG format
  (defun format-rg (results)
    (twith-output-to-gensym-string
      (let ((unix-time-at-start (gensym-get-unix-time)))
        (tformat "LISP-UNIT-TESTS, written ")
        (multiple-value-bind (second minute hour date month year)
            (gensym-decode-unix-time unix-time-at-start)
          (print-decoded-time
           second minute hour date month year))
        (tformat "~%~%")
        (loop for node in results
              do
              (loop for assertion in node
                    do (format-rg-entry assertion)))
        (tformat 
         "~%end-of-file, LISP-UNIT-TESTS, ~a~%---------------------------------------------------------------------------------~%"
         (round (- (gensym-get-unix-time) unix-time-at-start))))))

  ;;; A G2 system procedure which runs all tests and writes the results to a file
  (defun-for-system-procedure g2-run-lisp-unit-tests-and-write-rg (path-to-rg)
     (let ((rg-stream (g2-stream-open-for-output path-to-rg)))
       (cond
	 ((g2-stream-p rg-stream)
	  (unwind-protect
	       (let ((results (run-all-unit-tests)))
		 (unwind-protect
		      (let ((rg-string (format-rg results)))
			(unwind-protect
			     (g2-stream-write-string rg-string rg-stream)
			  (reclaim-gensym-string rg-string)))
		   ;; do we need to reclaim expected and actual values?
		   (loop for r in results 
		      do (reclaim-gensym-list r)) 
		   (reclaim-gensym-list results))
		 t)
	    (g2-stream-close rg-stream)))
	 (t (let ((error-text (most-recent-file-operation-status-as-text)))
	      (warning-message
	       1 "Couldn't open rg ~s:  ~a."
	       path-to-rg error-text)
	      (reclaim-text-string error-text))
	    nil)))))

;;; Returns T if lisp unit tests are included
(defun-for-system-procedure g2-are-lisp-unit-tests-included-p ()
  #+g2-lisp-unit
  evaluation-true-value
  #-g2-lisp-unit
  evaluation-false-value)

;;; Asserts FORM is true; stores the result in test results database
(defmacro assert-true (form)
  #+g2-lisp-unit
  (let ((actual (gensym)))
    `(let ((,actual ,form))
       (record-test-result
	 *test-node* (incff *test-node-count*) 'assert-true ,actual t ,actual)))
  #+lisp-unit
  `(lisp-unit:assert-true ,form))

;;; Asserts ACTUAL is EQ to EXPECTED; stores the result in test results database
(defmacro assert-equal (expected form)
  #+g2-lisp-unit
  (let ((actual (gensym)) (expected-value (gensym)))
    `(let ((,actual ,form)
	   (,expected-value ,expected))
       (record-test-result
	 *test-node* (incff *test-node-count*) 'assert-equal
	 (equal ,expected-value ,actual) ,expected-value ,actual)))
  #+lisp-unit
  `(lisp-unit:assert-equal ,expected ,form))

;;; Defines a test
;;; If LISP-UNIT is loaded, expands to LISP-UNIT:DEFINE-TEST
;;; Otherwise, defines a test function and stores it in *ALL-TESTS*
;;; When run, this function returns a list of assertion results
(defmacro deftest (name &body body)
  #+lisp-unit
  `(lisp-unit:define-test ,(intern (symbol-name name) :tests) ,@body)
  #+g2-lisp-unit
  `(progn
     (defun ,name ()
       (let ((*test-node* ',name)
	     (*test-node-count* 0)
	     (*test-results* (gensym-list)))
	 (test-handler-case ,@body)
	 *test-results*))
     (eval-when (:compile-toplevel :load-toplevel :execute)
       (unless (memq ',name *all-tests*)
	 (gensym-push ',name *all-tests*)))))

;;; Mimics WITH-CONNECTION-TEST-ENVIRONMENT
(defmacro with-empty-test-kb (&body body)
  #-chestnut-3
  `(ab::with-system-variables ('ab::ab 'ab::g2-lisp-unit)
     (setq ab::warning-message-level 0)
     (setq ab::loading-kb-p nil)
     (ab::assign-class-bit-numbers-and-vectors-to-system-classes)
     (setq ab::classes-visited-byte-vector
	   (ab::initialize-classes-visited-byte-vector))
     (ab::switch-to-new-empty-kb)
     (setq ab::module-information (ab::make-frame 'ab::module-information))
     (setq ab::miscellaneous-parameters
	   (ab::make-frame 'ab::miscellaneous-parameters))
     (setq ab::drawing-parameters (ab::make-frame 'ab::drawing-parameters))
     ,@body)
  #+chestnut-3
  `(tx:with-dynamic-area ; we run tests within an existing KB
       ,@body))


(in-package :lisp-unit2)
(cl-interpol:enable-interpol-syntax)

(defvar *test-stream* *standard-output*)
(defvar *test-log-stream* *test-stream*)
(defvar *unit-test* nil
  "The currently executing unit test (bound in %run-test, ie every test
  function)" )
(defvar *results* nil "The current results database (bound in run-tests)")
(defvar *result* nil "The current test result  (bound in %run-test)")

(defparameter *log-level* 5)

(defvar *test-db* nil
  "The unit test database is a list of tests and some hashtable indexes")

(defparameter +statuses+
  '(errors failed warnings passed missing empty)
  "List of statuses in order of priority for categorizing test runs")


;;; Run the tests
(define-condition missing-test (warning)
  ((test-name :accessor test-name :initarg :test-name :initform nil))
  (:documentation "Signaled when a single test is finished.")
  (:report
   (lambda (c s)
     (format s "Warning MISSING-TEST: ~A" (test-name c)))))

(define-condition test-start ()
  ((unit-test :accessor unit-test :initarg :unit-test :initform nil))
  (:documentation "Signaled when a single test starts."))

(define-condition test-complete ()
  ((result :accessor result :initarg :result :initform nil))
  (:documentation
   "Signaled when a single test is finished."))

(define-condition all-tests-start ()
  ((results :accessor results :initarg :results :initform nil))
  (:documentation "Signaled when a single test starts."))

(define-condition all-tests-complete ()
  ((results :accessor results :initarg :results :initform nil)
   (name :accessor name :initarg :name :initform nil
         :documentation "Name for this test results"))
  (:documentation
   "Signaled when a test run is finished."))

(define-condition collect-test-results ()
  ((results :accessor results :initarg :results :initform nil))
  (:documentation "Signaled that with-test-results should collect this test-result-database"))
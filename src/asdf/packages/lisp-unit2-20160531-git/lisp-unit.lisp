;;;-*- Mode: Lisp; Syntax: ANSI-Common-Lisp -*-

(in-package :lisp-unit2)
(cl-interpol:enable-interpol-syntax)

(defun %ts (&optional (time (get-universal-time)))
  "returns a date as {y}{mon}{d}-{h}{min}{s}, defaults to get-universal-time
   intended for use in datestamping filenames
  "
  (multiple-value-bind ( s min h d mon y  )
      (decode-universal-time time)
    (format nil "~d~2,'0d~2,'0d-~2,'0d~2,'0d~2,'0d"  y mon d h min s)))

(defmacro %log (message &key (level 0))
  (when (<= *log-level* level)
    `(format *test-log-stream* "~&~A ~A~%" (%ts) ,message)))

(defmacro %log-around ((message &key (start-level 1) (end-level 0)) &body body)
  `(unwind-protect
    (progn
      (%log #?" START ${,message}" :level ,start-level)
      ,@body)
    (%log #?"   END ${,message}" :level ,end-level)))

(defclass test-database ()
  ((%tests :accessor %tests :initarg :%tests :initform nil)
   (name-index :accessor name-index :initarg :name-index :initform (make-hash-table))
   (package-index :accessor package-index :initarg :package-index :initform (make-hash-table))
   (tag-index :accessor tag-index :initarg :tag-index :initform (make-hash-table))))

(defun reset-test-database ()
  (setf *test-db* (make-instance 'test-database)))

(unless *test-db* (reset-test-database))

(defgeneric tests (db)
  (:method ((db test-database))
    (head (%tests db))))

;;; Global unit test database
(defclass unit-test-control-mixin ()
  ((contexts
    :accessor contexts :initarg :contexts :initform nil
    :documentation "A function that accepts a test thunk and executes
     with a given context (eg: database-connects, html-collectors,
     http-context etc)")
   (data :accessor data :initarg :data :initform nil
         :documentation "Shared data so the context"))
  (:documentation "Helps commonize test construction by providing a
    shared data and dynamic context"))

(defclass unit-test (unit-test-control-mixin)
  ((name :accessor name :initarg :name :initform nil)
   (doc :accessor doc :initarg :doc :initform nil)
   (code :accessor code :initarg :code :initform nil
         :documentation "The forms to produce the fn")
   (tags :accessor tags :initarg :tags :initform nil)
   (most-recent-result :accessor most-recent-result :initarg :most-recent-result :initform nil)
   (eval-package :accessor eval-package :initarg :eval-package :initform nil))
  (:documentation
   "Organize the unit test documentation and code."))

(defmethod print-object ((o unit-test) s)
  "Print the auto-print-items for this instance."
  (print-unreadable-object (o s :type t :identity t)
    (princ (ignore-errors (short-full-name o)) s)))

(defgeneric install-test (unit-test)
  (:documentation
   "Installs a unit test, generally only called from define-test")
  (:method ((u unit-test)
            &aux (package (symbol-package (name u)))
            (db *test-db*))
    (%log #?"Installing test ${u}")
    (uninstall-test u)          ;; prevents duplication, does a lot of work :/
    (%compile u)
    (%collect! u (%tests db))
    (setf (gethash (name u) (name-index db)) u)
    (%collect! u (gethash package (package-index db)))
    (iter (for tag in (alexandria:ensure-list (tags u)))
      (%collect! u (gethash tag (tag-index db))))))

(defun %uninstall-name (n &optional tags
                        &aux (db *test-db*)
                        (package (symbol-package n)))
  (%decollect! n (%tests db) :key #'name)
  (remhash n (name-index db))
  (when package
    (setf (gethash package (package-index db))
          (%decollect! n (gethash package (package-index db)) :key #'name)))
  (when tags
    (if (eql t tags)
        (iter (for (tag vals) in-hashtable (tag-index db))
          (setf
           (gethash tag (tag-index db))
           (%decollect! n (gethash tag (tag-index db)) :key #'name)))
        (iter (for tag in (alexandria:ensure-list tags))
          (setf
           (gethash tag (tag-index db))
           (%decollect! n (gethash tag (tag-index db)) :key #'name)))))
  (ignore-errors (fmakunbound n))
  (ignore-errors (fmakunbound (test-thunk-name n))))

(defgeneric uninstall-test (test)
  (:documentation
   "Uninstalls a previously defined unit test")
  (:method ((n symbol))
    (%uninstall-name n t))
  (:method ((u unit-test) &aux (n (name u)))
    (%log #?"Uninstalling test ${u}")
    (%uninstall-name n t)))

(defun %to-test (id)
  "Coerces its argument to a unit-test argument

   always look up by name so that rerunning a suite after
   uninstalling a test behaves appropriately"
  (or (etypecase id
        (null nil)
        (unit-test (%to-test (name id)))
        (test-result (%to-test (name (unit-test id))))
        (symbol (gethash id (name-index *test-db*))))
      (warn 'missing-test :test-name id)))

(defun get-tests (&key tests tags package reintern-package
                  exclude-tests exclude-tags
                  &aux (db *test-db*) out)
  "finds tests by names, tags, and package

   if reintern-package is provided, reintern all symbols provided for tests
   and tags into the reintern-package.  Mostly provided for easing conversion
   of lisp-unit1 test suites
  "
  (%log-around (#?"get-tests:${tests} tags:${tags} package:${package} reintern-package:${reintern-package} exclude-tags:${exclude-tags} exclude-tests:${ exclude-tests }"
                :start-level 0)
    (setf tests (alexandria:ensure-list tests)
          tags (alexandria:ensure-list tags)
          exclude-tests (alexandria:ensure-list exclude-tests)
          exclude-tags (alexandria:ensure-list exclude-tags))
    (when reintern-package
      (setf tests (%in-package tests reintern-package))
      (setf tags (%in-package tags reintern-package))
      (setf exclude-tests (%in-package exclude-tests reintern-package))
      (setf exclude-tags (%in-package exclude-tags reintern-package)))
    ;; defaults to pulling up all tests in the current package
    (when (and (null tests) (null tags) (null package))
      (setf package (package-name *package*)))
    (let ((gathered))
      (flet ((gathered (&rest them)
               (when them
                 (setf gathered
                       (alexandria:flatten (list gathered them))))
               gathered))
        (iter (for p in (alexandria:ensure-list package))
          (gathered (head (gethash (find-package p) (package-index db)))))
        (iter (for tag in (alexandria:ensure-list tags))
          (gathered (head (gethash tag (tag-index db)))))
        (iter (for name in (alexandria:ensure-list tests))
          (for test = (%to-test name))
          (gathered test))
        (flet ((excluded? (test)
                 (when (find (name test) tests)
                   (return-from excluded? nil))
                 (or (find (name test) exclude-tests)
                     (iter (for tag in (tags test))
                       (thereis (and (find tag exclude-tags)
                                     (not (find tag tags))))))))
          (iter (for test in (gathered))
            (unless (or (null test)
                        (excluded? test)
                        (find test out-tests))
              (collect test into out-tests))
            (finally
             (return out-tests))))))))



(defun null-tests-warning-report (null-tests-warning stream)
  "Write the null-tests-warning to the stream."
  (format stream "No tests defined for package ~A."
          (tests-package-name null-tests-warning)))

(define-condition null-tests-warning (simple-warning)
  ((name
    :type string
    :initarg :name
    :reader tests-package-name))
  (:report null-tests-warning-report))

(defun null-tags-warning-report (null-tags-warning stream)
  "Write the null-tags-warning to the stream."
  (format stream "No tags defined for package ~A."
          (tags-package-name null-tags-warning)))

(define-condition null-tags-warning (simple-warning)
  ((name
    :type string
    :initarg :name
    :reader tags-package-name))
  (:report null-tags-warning-report))

(defgeneric test-thunk-name (test)
  (:method ((u unit-test))
    (test-thunk-name (name u)))
  (:method ((u symbol))
    (symbol-munger:english->lisp-symbol
     (list u 'test-thunk)
     (symbol-package u))))

(defgeneric test-thunk (unit-test)
  (:method ((u unit-test))
    (%compile u)
    (symbol-function (test-thunk-name u))))

(defgeneric %compile (unit-test)
  (:method  ((u unit-test))
    (%log-around (#?"Compiling Test: ${ (name u) }" :start-level 0)
      (let ((*package* (eval-package u)))
        (compile (test-thunk-name u)
                 `(lambda ()
                   (declare (optimize (debug 3))) ,@(code u)))))))


(defun test-name-error-report (test-name-error stream)
  "Write the test-name-error to the stream."
  (format stream "Test name ~S is not of type ~A."
          (type-error-datum test-name-error)
          (type-error-expected-type test-name-error)))

(define-condition test-name-error (type-error)
  ()
  (:default-initargs :expected-type 'symbol)
  (:report test-name-error-report)
  (:documentation
   "The test name error is a type error."))

(defun valid-test-name (name)
  "Signal a type-error if the test name is not a symbol."
  (if (symbolp name)
      name
      (error 'test-name-error :datum name)))

(defun %dequote (it)
  (if (and (listp it) (eql 'quote (first it)))
      (cadr it)
      it))

(defun %in-package (n &optional (package *package*)
                    &aux (*package* (find-package package)))
  (typecase n
    (null n)
    (keyword n)
    ((or string symbol)
     (symbol-munger:english->lisp-symbol
      n *package*))
    (list (mapcar #'%in-package n))))

(defmacro define-test (name (&key tags contexts package) &body body)
  "Defines a new test object, test functions and installs the test
   function in the test database

   name: the name of the test and the test-function

   contexts: a (lambda (fn)...) (or list of) that runs the fn in a dynamic
      context

   tags: symbols that can be used to group tests

   If package is provided, the name and any provided tags are reinterned into
      package before use. Keywords are left alone. This is useful because many
      times tests and the functions they test, coexist (and always could in
      lisp-unit v1, now that we create test functions, we dont want them
      overwriting the original function).

      Note: This should probably not be used (rather opting for
      packaged::symbols), but will be useful when converting from lisp-unit
      1->2.  See also: run-tests, get-tests reintern-package
  "
  (setf tags (mapcar #'%dequote (alexandria:ensure-list (%dequote tags)))
        name (%dequote name))
  (when package
    (setf name (%in-package name package)
          tags (%in-package tags package)))
  `(progn
    (install-test
     (make-instance 'unit-test
      :name ',name
      :doc ,(when (stringp (first body)) (first body))
      :tags ',tags
      :code '(,@body)
      :contexts (combine-contexts ,contexts)
      :eval-package *package*
      ))
    (defun ,name (&key test-contexts)
      (declare (optimize (debug 3)))
      "Runs this test, this fn is useful to help going to test definitions"
      (%run-test-name ',name :test-contexts test-contexts))
    #',name))

(defmacro undefine-test (name (&key tags contexts package) &body body)
  (declare (ignore tags contexts package body))
  `(uninstall-test ',name))

;;; Manage tests

(defun list-tests ()
  "Return a list of all tests,
   use get tests to find tests by package tag or name "
  (tests *test-db*))

(defun test-documentation (name)
  "Return the documentation for the test."
  (let ((unit-test (first (get-tests :tests name))))
    (if (null unit-test)
        (warn "No test ~A in package ~A."
              name (symbol-package name))
        (doc unit-test))))

(defun test-code (name)
  "Returns the code stored for the test name."
  (let ((unit-test (first (get-tests :tests name))))
    (if (null unit-test)
        (warn "No test ~A in package ~A."
              name (symbol-package name))
        (code unit-test))))

(defun remove-tests (&optional (tests :all) (tags nil) (package *package*))
  "Remove individual tests or entire sets."
  (let ((tests (get-tests :tests tests :tags tags :package package)))
    (iter (for test in tests)
      (uninstall-test test))))

;;; Manage tags

(defun list-tags ()
  "Return a list of the tags"
  (iter (for (tag list) in-hashtable (tag-index *test-db*))
    (collect tag)))

(defun remove-tags (&optional tags)
  "Remove individual tags or entire sets."
  (if (eq :all tags)
      (setf (tag-index *test-db*) (make-hash-table))
      (iter (for tag in (alexandria:ensure-list tags))
        (remhash tag (tag-index *test-db*)))))

;;; Test results database

(defclass test-results-mixin ()
  #.`((start-time :accessor start-time :initarg :start-time
                  :initform (get-universal-time))
      (internal-start-time :accessor internal-start-time :initarg :internal-start-time
                           :initform (get-internal-real-time))
      (end-time :accessor end-time :initarg :end-time :initform nil)
      (internal-end-time :accessor internal-end-time :initarg :internal-end-time
                           :initform nil)
      ;; SORRY want to keep this in sync with the +statuses, with minimal
      ;; shenanigans
      ,@(iter
          (for s in +statuses+)
          (collect `(,s :accessor ,s :initform nil)))))

(defun %has? (status thing &aux (n (len (funcall status thing))))
  (when (< 0 n) n))

(defun status ( u )
  (or
   (iter (for s in +statuses+)
     (when (%has? s u)
       (return s)))
   'empty))

(defgeneric run-time (it)
  (:method ((o test-results-mixin))
    (or
     (ignore-errors
      (float (/ (- (internal-end-time o) (internal-start-time o))
                internal-time-units-per-second) 0.0d0))
     (ignore-errors
      (- (end-time o) (start-time o)))
     -1)))

(defclass test-results-db (test-results-mixin unit-test-control-mixin)
  ((name :initarg :name :initform nil)
   (tests :accessor tests :initarg :tests :initform nil)
   (results :accessor results :initarg :results :initform nil)
   (args :accessor args :initarg :args :initform nil))
  (:documentation
   "Store the results of the tests for further evaluation."))

(defmethod name ((o test-results-db))
  (or (slot-value o 'name)
      (symbol-munger:combine-symbols
       (package-names o)
       :package :keyword
       :separator '-&-)))

(defmethod (setf name) (new (o test-results-db))
  (setf (slot-value o 'name) new))

(defgeneric package-names (db)
  (:method ((o test-results-db))
    (iter (for test in-sequence (tests o))
      (adjoining (package-name (symbol-package (name test)))))))

(defmethod initialize-instance :after
    ((ctl test-results-db) &key &allow-other-keys)
  (setf (slot-value ctl 'results)
        (make-array (len (tests ctl)) :initial-element nil :fill-pointer 0 :adjustable t)))

(defclass test-result (test-results-mixin)
  ((unit-test :accessor unit-test :initarg :unit-test :initform *unit-test*)
   (return-value :accessor return-value :initarg :return-value :initform nil)))

(defmethod print-object ((o test-result) s)
  "Print the auto-print-items for this instance."
    (format s "#<RESULT ~A ~A(~d)>" (ignore-errors (short-full-name o))
            (ignore-errors (status o))
            (ignore-errors (len (funcall (status o) o)))))

(defun short-full-name (s)
  (etypecase s
    (null nil)
    ((or assertion-pass assertion-fail test-result test-start)
     (short-full-name (unit-test s)))
    (test-complete
     (short-full-name (unit-test s)))
    (test-results-db
     (short-full-name (name s)))
    (unit-test (short-full-name (name s)))
    (symbol
     (let* ((package (symbol-package s))
            (nick (first (package-nicknames package)))
            (p (or nick (package-name package) "#")))
       (if (eql package (load-time-value (find-package :keyword)))
           #?":${s}"
           #?"${p}::${s}")))
    (string s)))

(defgeneric passed-assertions (it)
  (:method ((n null)) n)
  (:method ((u test-result))
    (passed u))
  (:method ((u test-results-db))
    (iter (for test-result in-vector (results u))
      (while test-result)
      (appending (head (passed-assertions test-result))))))

(defgeneric failed-assertions (it)
  (:method ((n null)) n)
  (:method ((u test-result))
    (failed u))
  (:method ((u test-results-db))
    (iter (for test-result in-vector (results u))
      (while test-result)
      (appending (head (failed-assertions test-result))))))

(defgeneric all-warnings (it)
  (:method ((n null)) n)
  (:method ((u test-result))
    (warnings u))
  (:method ((u test-results-db))
    (iter (for test-result in-vector (results u))
      (while test-result)
      (appending (head (warnings test-result))))))

(defmethod print-object ((o test-results-db) stream)
  "Print the summary counts with the object."
  (print-unreadable-object (o stream :type t :identity t)
    (let ((total (ignore-errors (len (tests o))))
          (passed (ignore-errors (len (passed-assertions o))))
          (failed (ignore-errors (len (failed-assertions o))))
          (errors (ignore-errors (len (errors o))))
          (warnings (ignore-errors (len (all-warnings o)))))
      (format stream "Tests:(~a) Passed:(~a) Failed:(~a) Errors:(~a) Warnings:(~a)"
              total passed failed errors warnings))))

(defun record-result-context (body)
  "as we are finishing a test (ie: it has the right status)
   record the result"
  (unwind-protect (funcall body)
    (record-result *result* *results*)))

(defgeneric record-result (result db)
  (:method ((res test-result) (db test-results-db)
            &aux (status (status res)))
    (vector-push-extend res (results db))
    (funcall (fdefinition `(setf ,status))
             (cons res (funcall status db))
             db)))


(defgeneric run-tests (&key
                       tests tags package name exclude-tests exclude-tags
                       test-contexts
                       run-contexts
                       reintern-package)
  (:documentation
   "Run the specified tests.

    We run all the listed tests, and all tests tagged with tags.  If both test
    and tags are nil (the default), then we run all tests in
    package (defaulting to *package*)

    name is the name of the test run.  Generally expected to be the name of the system
      being tested.  Can be defaulted with the name parameter of with-summary as well.
      can also be defaulted with.

    reintern-package: when looking up tests, first reintern all tests and tags
      in this package. In general this should probably not be used, but is provided
      for convenience in transitioning from lisp-unit 1 to 2 (see: define-test package)

    test-contexts is a list of contexts that will be applied around
      each individual test

    run-contexts is a list of contexts that will be applied around the entire
      suite (around signals)

    exclude-tests, exclude-tags: tests / tags to remove from the
      run. explicit inclusion overrides, explicit exclusion, overrides
      implicit inclusion
      EG: (define-test test-takes-forever (manual stuff) ...)
        (find-test :tags 'stuff :exclude-tags 'manual)
           will not find test-takes-forever
        (find-test :tags '(stuff manual) :exclude-tags 'manual)
        (find-test :tests 'test-takes-forever :exclude-tags 'manual)
           both will find test-takes-forever
  ")
  (:method :around (&key tests tags package name exclude-tests exclude-tags
                    test-contexts run-contexts
                    reintern-package)
    (declare (ignorable tests tags package test-contexts run-contexts
                        exclude-tests exclude-tags
                        reintern-package name))
    (%log-around (#?"Running tests${name}:${tests} tags:${tags} package:${package} context:${test-contexts},${run-contexts}")
      (call-next-method)))
  (:method (&rest args
            &key
            tests tags package reintern-package name exclude-tests exclude-tags
            test-contexts
            run-contexts
            &aux
            (all-tests
             (get-tests :tests tests
                        :tags tags
                        :package package
                        :reintern-package reintern-package
                        :exclude-tests exclude-tests
                        :exclude-tags exclude-tags))
            (results (make-instance 'test-results-db :tests all-tests :name name :args args))
            (*results* results))
    (%log #?"Running tests:${all-tests}" :level 0)
    (flet ((run-tests-body ()
             (with-simple-restart (abort "Cancel this all-tests-start signal")
               (signal 'all-tests-start :results results))
             (unwind-protect
                  (handler-bind ((missing-test
                                   (lambda (c) (%collect! (test-name c) (missing results)))))
                    (iter (for test in all-tests)
                      ;; this calls the test fn so the test source-location is
                      ;;  available in stack traces
                      (funcall
                       (name test)
                       :test-contexts
                       (list #'record-result-context test-contexts))))
               (setf (end-time results) (get-universal-time)
                     (internal-end-time results) (get-internal-real-time))
               (with-simple-restart (abort "Cancel this all-tests-complete signal")
                 (signal 'all-tests-complete :results results)))
             results))
      (do-contexts #'run-tests-body run-contexts)
      )))

(defgeneric tests-with-status (db status)
  (:documentation "Retrieve all tests with a given status from the database")
  (:method ((dbs list) status)
    (iter (for db in dbs)
      (appending (tests-with-status db status))))
  (:method ((db test-results-db) status)
    (iter (for s in (alexandria:ensure-list status))
      (appending (funcall s db)))))

(defgeneric  rerun-tests (test-results-db)
  (:documentation "Rerun all tests from a given run (returns new results)")
  (:method ((dbs list))
    (iter (for db in dbs)
      (collecting (rerun-tests db))))
  (:method ((db test-results-db))
    (apply #'run-tests (args db))))

(defgeneric rerun-failures (test-results-db &key status)
  (:documentation "reruns failed tests")
  (:method ((dbs list) &key status)
    (iter (for db in dbs)
      (collecting (rerun-failures db :status status))))
  (:method ((db test-results-db) &key (status '(failed warnings errors)))
    (run-tests :tests (tests-with-status db status)
               :name (name db)
               :test-contexts (getf (args db) :test-contexts)
               :run-contexts (getf (args db) :run-contexts))))

(defun combine-contexts (&rest contexts)
  "Takes a list of nils and contexts and combines them into a single context
   (or null of no contexts were provided)"
  (labels ((%combine-2-contexts (c0 c1)
             (lambda (body-fn)
               (funcall c0 (lambda () (funcall c1 body-fn)))))
           (%make (contexts &aux (c (first contexts)) (them (rest contexts)))
             (cond
               ((and (null c) (null them) nil))
               ((null them) c)
               (t (%make (cons (%combine-2-contexts c (first them))
                               (rest them)))))))
    (%make (alexandria:flatten contexts))))

(defun do-contexts (body-fn &rest contexts)
  "runs the body-fn inside of contexts, the last context will be the outermost
   all nils in contexts are ignored"
  (let ((c (apply #'combine-contexts contexts)))
    (if c
        (funcall c body-fn)
        (funcall body-fn))))

(defun %run-test-name (u &key test-contexts)
  (iter
    (with-simple-restart (retry "Retry running ~A" u)
      (let ((test (first (get-tests :tests u))))
        (if test
            (%run-test test :test-contexts test-contexts)
            (warn 'missing-test :test-name u)))
      (finish))))

(defun %run-test
    (u &key test-contexts
       &aux
       (result (setf (most-recent-result u)
                     (make-instance 'test-result :unit-test u)))
       (*unit-test* u)
       (*result* result))
  "This should only be called from run-test-name, which everyone else should call
   This ensures our test name is easily in the inspector and the redefining a test
   then retrying calls the new test body"
  (check-type u unit-test)
  ;; todo: clear contexts, data? so that it must be set via signal?
  ;; possibly in an unwind-protect region
  (with-simple-restart (abort "Cancel this test-start signal")
    (signal 'test-start :unit-test u))
  (with-simple-restart (continue "Continue running the next test")
    (unwind-protect
         (handler-bind
             ((assertion-pass (lambda (c) (%collect! (assertion c) (passed result))))
              (assertion-fail (lambda (c) (%collect! (failure c) (failed result))))
              (error (lambda (c)
                       (%collect! c (errors result))
                       (unless *debugger-hook*
                         (return-from %run-test result))))
              (warning (lambda (c) (%collect! c (warnings result)))))
           ;; run the test code
           (setf (return-value result)
                 (do-contexts (test-thunk u)
                   (contexts u)
                   test-contexts)))
      (setf (end-time result) (get-universal-time)
            (internal-end-time result) (get-internal-real-time))
      (with-simple-restart (abort "Cancel this test-complete signal")
        (signal 'test-complete :result result))))
  result)

;; This is written this way so that erroring test fns show up in the
;; stack and then can easily goto-definition
(defgeneric run-test (test &key test-contexts)
  (:method ((n symbol) &key test-contexts )
    (funcall n :test-contexts test-contexts))
  (:method :around ((u symbol) &key test-contexts)
    (declare (ignorable u test-contexts))
    (%log-around (#?"Running Test:${ u } context:${test-contexts}")
      (call-next-method)))
  (:method ((u unit-test) &key test-contexts)
    (run-test (name u) :test-contexts test-contexts)))

(defun test-signals-muffled-context (body-fn)
  (handler-bind ((lisp-unit2::assertion-pass #'abort)
                 (lisp-unit2::assertion-fail #'abort)
                 (lisp-unit2::test-start #'abort)
                 (lisp-unit2::test-complete #'abort)
                 (lisp-unit2::all-tests-start #'abort)
                 (lisp-unit2::all-tests-complete #'abort))
    (funcall body-fn)))

(defmacro with-test-signals-muffled (()&body body)
  `(test-signals-muffled-context (lambda () ,@body)))

(pushnew :lisp-unit2 common-lisp:*features*)


#|
Copyright (c) 2013 Russ Tyndall, Acceleration.net
Copyright (c) 2004-2005 Christopher K. Riesbeck

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
|#

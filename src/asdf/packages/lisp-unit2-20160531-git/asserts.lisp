(in-package :lisp-unit2)
(cl-interpol:enable-interpol-syntax)

(define-condition assertion-pass (condition)
  ((unit-test :accessor unit-test :initarg :unit-test :initform *unit-test*)
   (assertion :accessor assertion :initarg :assertion :initform nil)))

(define-condition assertion-fail (condition)
  ((unit-test :accessor unit-test :initarg :unit-test :initform *unit-test*)
   (assertion :accessor assertion :initarg :assertion :initform nil)
   (failure :accessor failure :initarg :failure :initform nil))
  (:report (lambda (c s)
             (let ((*test-stream* s))
               (format *test-stream* "Failed Assertion in ~A~%"
                       (or (short-full-name c) "<UNIT-TEST>"))
               (print-summary (failure c))))))

(defun set-equal (list1 list2 &rest initargs &key key (test #'equal))
  "Return true if every element of list1 is an element of list2 and
vice versa."
  (setf list1 (alexandria:ensure-list list1)
        list2 (alexandria:ensure-list list2))
  (and (apply #'subsetp list1 list2 initargs :test test :key key)
       (apply #'subsetp list2 list1 initargs :test test :key key)))

(defun logically-equal (x y)
  (or (and x y)
      (and (null x) (null y))))

;;; Assert macros

(defmacro assert-eq (&whole whole expected form &rest extras)
  "Assert whether expected and form are EQ."
  `(expand-assert 'equal-result ,form ,form ,expected ,extras
    :test #'eq
    :full-form ',whole))

(defmacro assert-eql (&whole whole expected form &rest extras)
  "Assert whether expected and form are EQL."
  `(expand-assert 'equal-result ,form ,form ,expected ,extras :test #'eql
    :full-form ',whole))

(defmacro assert-equal (&whole whole expected form &rest extras)
  "Assert whether expected and form are EQUAL."
  `(expand-assert 'equal-result ,form ,form ,expected ,extras :test #'equal
    :full-form ',whole))

(defmacro assert-equalp (&whole whole expected form &rest extras)
  "Assert whether expected and form are EQUALP."
  `(expand-assert 'equal-result ,form ,form ,expected ,extras :test #'equalp
    :full-form ',whole))

(defmacro assert-typep (&whole whole expected-type form &rest extras)
  "Assert whether expected and form are TYPEP."
  `(expand-assert
    'equal-result ,form ,form
    ,expected-type ,extras
    :test #'typep
    :full-form ',whole))

(defun expand-signaled-handler (whole condition form extras should-be-signaled?)
  (alexandria:with-unique-names (signaled rtn)
    `(let (,signaled ,rtn)
      (block ,signaled
        (handler-bind
            ((condition #'(lambda (c)
                            (when (typep c ,condition)
                              (setf ,signaled c)
                              (when (typep c 'warning)
                                (muffle-warning c))
                              (when (typep c 'error)
                                (return-from ,signaled))
                              ))))
          (setf ,rtn (multiple-value-list ,form))))
      (expand-assert 'signal-result
       ,form ,signaled ,should-be-signaled? ,extras
       :full-form ',whole)
      (apply #'values ,rtn))))

(defmacro assert-signal (&whole whole condition form &rest extras)
  (expand-signaled-handler whole condition form extras t))

(defmacro assert-no-signal (&whole whole condition form &rest extras)
  (expand-signaled-handler whole condition form extras nil))

(defmacro assert-warning (condition form &rest extras)
  `(assert-signal ,condition ,form ,@extras))

(defmacro assert-no-warning (condition form &rest extras)
  `(assert-no-signal ,condition ,form ,@extras))

(defmacro assert-error (condition form &rest extras)
  "Assert whether form signals condition."
  `(assert-signal ,condition ,form ,@extras))

(defmacro assert-no-error (condition form &rest extras)
  "Assert whether form signals condition."
  `(assert-no-signal ,condition ,form ,@extras))

(defmacro assert-expands (expansion form &rest extras)
  "Assert whether form expands to expansion."
  `(expand-assert 'macro-result ,form (expand-macro-form ,form) ',expansion ,extras))

(defmacro assert-equality (&whole whole test expected form &rest extras)
  "Assert whether expected and form are equal according to test."
  `(expand-assert 'equal-result ,form ,form ,expected ,extras :test ,test
    :full-form ',whole))

(defmacro assert-prints (&whole whole output form &rest extras)
  "Assert whether printing the form generates the output."
  `(expand-assert 'output-result ,form (expand-output-form ,form)
                  ,output ,extras
    :full-form ',whole))

(defmacro assert-true (&whole whole form &rest extras)
  "Assert whether the form is true."
  `(expand-assert 'equal-result ,form ,form t ,extras
    :test #'(lambda (x y) (and x y))
    :full-form ',whole))

(defmacro assert-false (&whole whole form &rest extras)
  "Assert whether the form is false."
  `(expand-assert 'equal-result ,form ,form nil ,extras
    :test #'(lambda (x y) (and (not x) (not y)))
    :full-form ',whole))

(defmacro expand-assert (type form body expected extras
                         &key (test '#'eql)
                         full-form)
  "Expand the assertion to the internal format."
  `(internal-assert ,type ',form
    (lambda () ,body)
    (lambda () ,expected)
    (expand-extras ,extras)
    ,test
    :full-form (or ,full-form
                '(,type ,expected ,form))))


(defmacro expand-output-form (form)
  "Capture the output of the form in a string."
  (let ((out (gensym)))
    `(let* ((,out (make-string-output-stream))
            (*standard-output*
             (make-broadcast-stream *standard-output* ,out)))
       ,form
       (get-output-stream-string ,out))))

(defmacro expand-macro-form (form &optional env)
  "Expand the macro form once."
  `(let ((*gensym-counter* 1)) (macroexpand-1 ',form ,env)))

(defmacro expand-extras (extras)
  "Expand extra forms."
  `(lambda ()
     (list ,@(mapcan (lambda (form) (list `',form form)) extras))))

(defgeneric record-failure (type form actual expected extras test)
  (:documentation
   "Record the details of the failure.")
  (:method (type form actual expected extras test)
    (make-instance
     type
     :form form :actual actual :expected expected
     :extras extras :test test)))

(defclass failure-result ()
  ((unit-test :accessor unit-test :initarg :unit-test :initform *unit-test*)
   (form :accessor form :initarg :form :initform nil)
   (actual :accessor actual :initarg :actual :initform nil)
   (expected :accessor expected :initarg :expected :initform nil)
   (extras :accessor extras :initarg :extras :initform nil)
   (test :accessor test :initarg :test :initform nil))
  (:documentation
   "Failure details of the assertion."))

(defclass equal-result (failure-result) ()
  (:documentation "Result of a failed equal assertion."))

(defclass error-result (failure-result) ()
  (:documentation "Result of a failed error assertion."))

(defclass signal-result (failure-result) ()
  (:documentation "Result of a failed warning assertion."))

(defclass macro-result (failure-result) ()
  (:documentation "Result of a failed macro expansion assertion."))

(defclass output-result (failure-result) ()
  (:documentation "Result of a failed output assertion."))

(defun %form-equal (form1 form2 &aux (invalid `(/= ,form1 ,form2)))
  "Descend into the forms checking for equality.

   The first unequal part is the second value"
  (typecase form1
    ;; symbols should be name equal (gensyms)
    (symbol
     (or (eql form1 form2)
         ;; two gensyms, one is as good as the other?
         (and (null (symbol-package form1))
              (null (symbol-package form2))
              (string= (symbol-name form1) (symbol-name form2)))
         (values nil `(/= ,form1 ,form2))))

    ;; lists need to match by recursion
    (list
     (multiple-value-bind (res inv)
         (ignore-errors (%form-equal (first form1) (first form2)))
       (if res
           (if (eql (length (rest form1)) (length (rest form2)))
               (%form-equal (rest form1) (rest form2))
               (values nil inv invalid))
           (values nil inv invalid))))

    (t ;; everything else should be equal
     (or (equal form1 form2)
         (values nil invalid)))))

(defgeneric assert-passes? (type test expected actual)
  (:documentation "Return the result of the assertion.")
  (:method (type test expected actual)
    (ecase type
      ((equal-result failure-result)
       (and
        (<= (length expected) (length actual))
        ;; by putting expected in the second position we open up the ability
        ;; to use many more functions as tests (eg: typep)
        (every test actual expected)))
      (signal-result
       ;; These are lists of booleans
       (logically-equal (first expected) (first actual)))
      (error-result
       (or
        ;; todo: whats with eql?
        (eql (car actual) (car expected))
        (typep (car actual) (car expected))))
      (macro-result
       (%form-equal (first expected) (first actual)))
      (output-result
       (string=
        (string-trim '(#\newline #\return #\space) (car actual))
        (string-trim '(#\newline #\return #\space) (car expected)))))))

(defun internal-assert
    (type form code-thunk expected-thunk extras test &key full-form)
  "Perform the assertion and record the results."
  (let* ((actual (multiple-value-list (funcall code-thunk)))
         (expected (multiple-value-list (funcall expected-thunk)))
         (result (assert-passes? type test expected actual)))
    (with-simple-restart (abort "Cancel this assertion")
      (if result
          (signal 'assertion-pass :assertion (or full-form form))
          (signal 'assertion-fail
                  :assertion (or full-form form)
                  :failure (record-failure
                            type full-form actual expected
                            (when extras (funcall extras)) test))))
    ;; Return the actual-values
    (apply #'values actual)))

(defun with-failure-debugging-context (body-fn)
  "A context that invokes the debugger on failed assertions"
  (handler-bind ((assertion-fail #'invoke-debugger))
    (funcall body-fn)))

(defmacro with-failure-debugging (() &body body)
  "A context macro that invokes the debugger on failed assertions"
  `(with-failure-debugging-context (lambda () ,@body)))


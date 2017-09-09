;;;-*- Mode: Lisp; Syntax: ANSI-Common-Lisp -*-
(in-package :lisp-unit2)
(cl-interpol:enable-interpol-syntax)

(defmacro pprint-test-block ((&key per-line-prefix) &body body)
  `(block nil               ;; this prevents outputing an extra newline/prefix
    (pprint-logical-block (*test-stream* nil ,@(when per-line-prefix
                                                 `(:per-line-prefix ,per-line-prefix)))
      (pprint-indent :current 0 *test-stream*)
      ,@body
      (pprint-exit-if-list-exhausted))))

(defun with-assertion-summary-context (body-fn
                                       &aux (*print-pretty* t) rtn)
  (pprint-test-block ()
    (format *test-stream* "~%")
    (handler-bind
        ((assertion-pass
           (lambda (c) (format *test-stream* "~@:_~A:Passed ~A"
                          (or
                           (ignore-errors
                            (short-full-name c))
                           "<No Test>")
                          (assertion c))))
         (assertion-fail
           (lambda (c) (%print-summary (failure c)))))
      (setf rtn (multiple-value-list (funcall body-fn))))
    (format *test-stream* "~0I~%"))
  (apply #'values rtn))

(defun with-test-results-context (body-fn
                                  &key
                                  collection-place-setter
                                  (summarize? nil summarize?-p)
                                  &aux rtn test-result-dbs)
  "A context that collects test-result-databases
   if collection-place-setter (lambda (new) (setf collection-place new)) exists
     anytime we get a new test result we set the place to the new collection

   if summarize? at the end of the block we print the results summary for
     all tests this defaults to T if no collection-place-setter is provided
     and nil otherwise"
  (flet ((collect-test-results (c &aux (results-db (results c)))
           (when results-db
             (%collect! results-db test-result-dbs)
             (when collection-place-setter
               (funcall collection-place-setter (head test-result-dbs))))))
    (handler-bind
        ((all-tests-start #'collect-test-results)
         (collect-test-results  #'collect-test-results))
      (setf rtn (multiple-value-list (do-contexts body-fn +interop-test-result-contexts+)))))
  ;; we tested multiple systems / had multiple calls to run-tests
  ;; inside this block
  (when (or summarize? (and (null summarize?-p)
                            (null collection-place-setter)))
    (iter (for res in (head test-result-dbs))
      (print-failure-summary res)))
  (apply #'values rtn))

(defmacro with-test-results ((&key collection-place (summarize? nil summarize?-p)) &body body)
  "see with-test-results-context"
  `(with-test-results-context
    (lambda () ,@body)
    ,@(when collection-place
        `(:collection-place-setter (lambda (new) (setf ,collection-place new))))
    ,@(when summarize?-p
        `(:summarize? ,summarize?))))

(defun with-summary-context (body-fn
                             &key name
                             &aux (*print-pretty* t) rtn )
  (flet ((ensure-names (c)
           "Syncs the names between this env and our results object"
           (when (and name (null (name (results c))))
             (setf (name (results c)) name))
           (when (and (null name) (name (results c)))
             (setf name (name (results c))))))
    ;; this resets the actual indenting which, for whatever reason gets
    ;; banged by compiler messages without this
    (pprint-test-block () (format *test-stream* "~%"))
    (pprint-test-block ()
      (handler-bind
          ((all-tests-start
             (lambda (c)
               (ensure-names c)
               (if name
                   (format *test-stream* "~0I------- STARTING Testing: ~A ~%" name)
                   (format *test-stream* "~%~0I"))))
           (test-start
             (lambda (c)
               (format *test-stream* "~@:_Starting: ~A~@:_"
                              (short-full-name c))))
           (all-tests-complete
             (lambda (c)
               (ensure-names c)
               (%print-result-summary (results c))
               (if name
                   (format *test-stream* "~%~0I-------   ENDING Testing: ~A ~%" name)
                   (format *test-stream* "~0I~%"))))
           (test-complete (lambda (c) (%print-summary (result c)))))
        (setf rtn (multiple-value-list (funcall body-fn)))))
    (apply #'values rtn)))

(defmacro with-summary ((&key name) &body body)
  `(with-summary-context (lambda () ,@body)
    :name ,name))

(defmacro with-assertion-summary (() &body body)
  `(with-assertion-summary-context (lambda () ,@body)))

(defun %out (s &rest args
               &aux (*print-pretty* t))
  (format *test-stream* "~?~@:_" (or s "") args))

(defgeneric %print-result-summary (db)
  (:method ((o test-results-db))
    (let ((total (len (tests o)))
          (passed (len (passed-assertions o)))
          (failed (len (failed-assertions o)))
          (errors (len (errors o)))
          (warnings (len (all-warnings o)))
          (empty (len (empty o)))
          (missing (len (missing o)))
          (name (short-full-name o)))
      (format *test-stream* "~@:_Test Summary ")
      (if name
          (format *test-stream* "for ~A " name))
      (format *test-stream*       "(~D tests ~,2F sec)~@:_" total (run-time o))
      (format *test-stream* "  | ~D assertions total~@:_" (+ passed failed))
      (format *test-stream* "  | ~D passed~@:_" passed)
      (format *test-stream* "  | ~D failed~@:_" failed)
      (format *test-stream* "  | ~D execution errors~@:_" errors)
      (format *test-stream* "  | ~D warnings~@:_" warnings)
      (format *test-stream* "  | ~D empty~@:_" empty)
      (format *test-stream* "  | ~D missing tests~@:_" missing))))

(defun print-summary (o &aux (*print-pretty* t))
  (pprint-test-block ()
    (%print-summary o))
  o)

(defun print-failure-summary (o &aux (*print-pretty* t))
  (format *test-stream* "~%~0I")
  (pprint-test-block ()
    (print-status-summary o '(failed errors warnings empty))
    (%print-result-summary o))
  o)

(defgeneric %print-summary (o)
  (:documentation "Print a summary of all results to the stream.")
  (:method ((o vector))
    (iter (for res in-vector o)
      (%print-summary res))
    o)
  (:method ((o list))
    (iter (for res in o)
      (%print-summary res))
    o)
  (:method ((o test-results-db))
    (pprint-test-block ()
      (%print-summary (results o))
      (%print-result-summary o))
    o)
  (:method  ((run test-result))
    (let ((not-ok? (or (failed run) (errors run) (warnings run))))
      (format *test-stream* "~@_~A - ~A (~,2Fs) : ~S assertions passed~@:_"
              (ignore-errors (short-full-name run))
              (status run)
              (run-time run)
              (len (passed run)))
      ;; prevents print an extra "\n | "
      (when not-ok?
        (pprint-test-block (:per-line-prefix "  | ")
          (iter (for s in '(errors failed warnings))
            (print-status-summary run s)))))
    run)
  (:method :around ((result failure-result))
    (%out "Failed Form: ~S" (form result))
    (call-next-method)
    (when (extras result)
      (iter (for (f v) on (extras result) by #'cddr)
        (if (equalp f v)
            (%out "~S" f)
            (%out "~S => ~S" f v))))
    result)

  (:method ((result failure-result))
    (%out "Expected ~{~S~^; ~} " (expected result))
    (format *test-stream*
            "~<~:;but saw ~{~S~^; ~}~>"
            (actual result))
    (%out ""))

  (:method ((result error-result))
    (%out "~@[Should have signalled ~{~S~^; ~} but saw~]"
          (expected result))
    (%out "~{~S~^; ~}" (actual result))
    result)

  (:method ((result macro-result))
    (%out "Should have expanded to ~{~S~^; ~} " (expected result))
    (format *test-stream*
            "~<~:;but saw ~{~S~^; ~}~>"
            (actual result))
    (%out "")
    result)

  (:method ((result output-result))
    (format *test-stream* "~@:_| Should have printed ~{~S~^; ~} "
            (expected result))
    (format *test-stream* "~<~:;but saw ~{~S~^; ~}~>"
            (actual result))
    result)
  (:method ((w warning))
    (%out "WARNING: ~A" w)
    (%out "~S" w)
    w)
  (:method ((e error))
    (%out "ERROR: ~A" e)
    (%out "~S" e)
    e)
  (:method (it)
    (%out "~A" it)))

(defgeneric print-status-summary (object status)
  (:method ((db test-results-db) (status list))
    (iter (for s in status)
      (print-status-summary db s)))
  (:method ((db test-results-db) (s symbol) &aux (objs (funcall s db)))
    (when objs
      (iter (for o in (typecase objs
                        (list objs)
                        (list-collector (head objs))))
        (format *test-stream* "~@:_~A (~A)~@:_-----------~@:_" (short-full-name o) (status o))
        (print-status-summary o s))))
  (:method ((o test-result) (s symbol) &aux (objs (funcall s o)))
    (when objs
      (format *test-stream* "~A (~D)~@:_" s (len objs))
      (iter (for o in (typecase objs
                        (list objs)
                        (list-collector (head objs))))
        (%print-summary o))
      (format *test-stream* "~@:_"))
    ))
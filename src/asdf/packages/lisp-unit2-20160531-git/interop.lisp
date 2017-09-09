(in-package :lisp-unit2)

(defgeneric convert-test-results (input test-system-name)
  (:documentation "Convert the test results from a given test system to lisp-unit2:test-results-db"))

(defgeneric convert-test-result (input &optional name)
  (:documentation "Convert the test results from a given test system to lisp-unit2:test-results-db"))

#-asdf
(defun get-system-list (start)
  (declare (ignore (start)))
  (error "Requires asdf"))

#+asdf3
(defun get-system-list (start &aux list)
  (labels ((do-it (sys-name)
             (let* ((sys (asdf/system:find-system sys-name))
                    (deps (slot-value sys 'asdf/component:sideway-dependencies)))
               ;; ensures that all dependencies are before things that depend on them
               (setf list (delete sys-name list :test #'equal))
               (push sys-name list)
               (mapc #'do-it deps))))
    (mapc #'do-it (alexandria:ensure-list start))
    list))

#-asdf3 #+asdf
(defun get-system-list (start &aux list)
  (labels ((do-it (sys-name)
             (let* ((sys (asdf:find-system sys-name))
                    (deps (slot-value sys 'asdf:load-dependencies)))
               ;; ensures that all dependencies are before things that depend on them
               (setf list (delete sys-name list :test #'equal))
               (push sys-name list)
               (mapc #'do-it deps))))
    (mapc #'do-it (alexandria:ensure-list start))
    list))

#-asdf
(defgeneric test-asdf-system-recursive (sys-name &key ignore-systems)
  (:method (sys-name &key ignore-systems)
    (declare (ignore (sys-name ignore-systems)))
    (error "Requires asdf")))

#+asdf
(defgeneric test-asdf-system-recursive (sys-name &key ignore-systems)
  (:method (sys-name &key ignore-systems &aux out)
    (with-test-results (:collection-place out
                        :summarize? t)
      (iter (for system in (get-system-list sys-name))
        (unless (member system ignore-systems)
          (format *test-stream* "~% asdf:test-system: ~A~%" system)
          (asdf:test-system system))))
    out))

#+lisp-unit
(defun lisp-unit1-collection-context (body-fn)
  (lisp-unit:signal-results t)
  (handler-bind ((lisp-unit:test-run-complete
                   (lambda (c) (signal 'lisp-unit2::collect-test-results
                                  :results (convert-test-results
                                            (lisp-unit:results c)
                                            (or #+asdf asdf/operate:*systems-being-operated*
                                                :lisp-unit-test-results))))))
    (funcall body-fn)))

#+lisp-unit
(defmethod convert-test-result ((res lisp-unit::failure-result) &optional name)
  (declare (ignore name))
  (make-instance
   ;; find the class for lisp-unit2 that matches the lisp-unit error class
   (or (ignore-errors
        (class-name (find-class (intern (symbol-name (class-name (class-of res)))
                                        :lisp-unit2))))
       'lisp-unit2:failure-result)
   :actual (lisp-unit::actual res)
   :expected (lisp-unit::expected res)
   :form (lisp-unit::form res)
   :test (lisp-unit::test res)))

#+lisp-unit
(defmethod convert-test-result ((test-res lisp-unit::test-result) &optional name)
  (let ((new (make-instance 'lisp-unit2:test-result
                            :unit-test (make-instance 'lisp-unit2:unit-test))))
    (setf (name (unit-test new)) (or name (lisp-unit::name test-res) ))
    (when (lisp-unit::exerr test-res)
      (%collect! (lisp-unit::exerr test-res) (lisp-unit2:errors new)))
    (iter (for i from 0 below (lisp-unit::pass test-res))
      (%collect! t (lisp-unit2:passed new)))
    (iter (for fail in (lisp-unit::fail test-res))
      (%collect! (convert-test-result fail) (failed new)))
    new))

#+lisp-unit
(defmethod convert-test-results ((res lisp-unit::test-results-db)
                                 test-system-name)
  (let ((new-db (make-instance 'lisp-unit2:test-results-db
                            :name test-system-name)))
    (iter (for (name result) in-hashtable (lisp-unit::database res))
      (for new-res = (convert-test-result result))
      (%collect! (unit-test new-res) (lisp-unit2::tests new-db))
      (lisp-unit2::record-result new-res new-db))
    new-db))


(defparameter +interop-test-result-contexts+
  (list #+lisp-unit #'lisp-unit1-collection-context))
(in-package :cl-user)

(load "asdf/asdf")
(asdf:initialize-source-registry `(:source-registry (:tree ,(truename "./")) 
                                                    :inherit-configuration))
(asdf:load-system "cxml")
(asdf:load-system "cl-fad")

;;;
;;; Utility functions
;;;

(setf *read-default-float-format* 'double-float)

(defun parse-xml-file (file)
  (cxml:parse-file file (cxml-dom:make-dom-builder)))

(defmacro with-new-file ((stream file-save-to) &body body)
  `(with-open-file
      (,stream ,file-save-to :direction :output
               :if-exists :supersede :if-does-not-exist :create)
     ,@body))


;;;
;;; Performance index parser
;;;
(defconstant +score-title+ "Monte Carlo : ")
(defconstant +score-title-length #.(length +score-title+))

(defun load-performance-index (performance-index-file)
  (if performance-index-file
      (with-open-file (stream performance-index-file :direction :input)
        (loop for row = (read-line stream)
           for position = (search +score-title+ row)
           when position 
           return (read-from-string 
                   (subseq row (+ position +score-title-length)))))
      1))
         

;;;
;;; Performance summary parser
;;;

(defun objective-metric-p (metric)
  (string= (dom:get-attribute metric "name") "Objective"))

(defun parse-metric (metric)
  (cons (dom:get-attribute (dom:parent-node metric) "name")
        (read-from-string (dom:node-value (dom:first-child metric)))))

(defun extract-objective-metrics (metrics) 
  (remove-if-not #'objective-metric-p 
                 (dom:get-elements-by-tag-name metrics "Metric")))

(defun parse-performance-measurements (file)
  (map 'list #'parse-metric 
       (extract-objective-metrics (parse-xml-file file))))



;;;
;;; CPD combiner
;;;

(defun get-count-of-duplication-lines (duplication-node)
  (read-from-string (dom:get-attribute duplication-node "lines")))

(defun calculate-duplication-lines-metric-for-nodes (duplication-nodes)
  (loop for node across duplication-nodes
     for count = (get-count-of-duplication-lines node)
     sum (* count count)))

(defun calculate-duplication-line-metric-for-file (file)
  (calculate-duplication-lines-metric-for-nodes
   (dom:get-elements-by-tag-name (parse-xml-file file) "duplication")))

(defun extract-module-name (pathname)
  (subseq (pathname-name pathname) (length "cpd_check_")))

(defun parse-cpd-files (files)
  (map 'list (lambda (file) 
               (cons (extract-module-name file)
                     (calculate-duplication-line-metric-for-file file)))
       files))

(defun generate-xml-for-duplications (duplications)
  (cxml:with-xml-output (cxml:make-string-sink :indentation 2)
    (cxml:with-element "Modules"
      (dolist (duplication duplications)
        (cxml:with-element "Module"
          (cxml:attribute "name" (car duplication))
          (cxml:attribute "duplication" (cdr duplication)))))))

(defun save-duplication-summary (cpd-files save-to)
  (with-new-file (xml-stream save-to)
    (format 
     xml-stream 
     (generate-xml-for-duplications (parse-cpd-files cpd-files)))))

;;;
;;; CPD summary parsing
;;;

(defun parse-cpd-module (module)
  (cons (dom:get-attribute module "name")
        (read-from-string (dom:get-attribute module "duplication"))))

(defun parse-cpd-summary (file)
  (map 'list #'parse-cpd-module 
       (dom:get-elements-by-tag-name (parse-xml-file file) "Module")))


;;;
;;; Threshold comparison 
;;;

(defstruct (comparison (:type vector))
  name
  value
  threshold
  tolerance
  actual-performance-index
  threshold-perfromance-index)

(defun compare (actual threshold &key (actual-scale 1))
  (coerce (if (= threshold 0)
              (if (= actual 0) 0 1d++0)
              (- (/ (* actual actual-scale) threshold) 1)) 'double-float))

(defun format-failure-message-for-comparison (comparison)
  (let ((actual-value (comparison-value comparison))
        (threshold (comparison-threshold comparison))
        (tolerance (comparison-tolerance comparison)))
    (format nil "Degradation: ~a~%Actual value: ~a~%Threshold: ~a~@[
Tolerance: ~a~]"
            (compare actual-value threshold) actual-value threshold 
            tolerance)))

(defun produce-xml-for-comparison (comparison)
  (cxml:with-xml-output (cxml:make-string-sink :indentation 2
                                               :omit-xml-declaration-p t)
    (cxml:with-element "testcase"
      (cxml:attribute "name" (comparison-name comparison))
      (when (/= (comparison-value comparison)
                (comparison-threshold comparison))
        (cxml:with-element "failure"
          (cxml:text
           (let ((actual (comparison-value comparison))
                 (threshold (comparison-threshold comparison)))
             (format 
              nil 
              "Degradation is ~7,2F%, current result is ~a, threshold is ~a~%"
              (* (compare actual threshold) 100)
              actual threshold))))))))
       
(defun compare-results (&key actuals thresholds (scale 1))
  (map 'list (lambda (actual threshold) 
               (compare actual threshold :actual-scale scale))
       actuals thresholds))

(defstruct (comparator-result (:type vector))
  name
  actual-value
  original-value
  difference
  pass-p)
                              
(defun calculate-degradation (actual threshold actual-performance-index
                              threshold-performance-index)
  (if (= threshold 0)
      (if (= actual 0) 0 1d++0)
      (- (/ (* actual (/ actual-performance-index threshold-performance-index))
            threshold) 1)))

(defun check-thresholder (actual-results thresholder tolerance
                          &optional (abs-function #'identity)
                          (actual-performance-index 1)
                          (threshold-performance-index 1))
  (let* ((actual-value
          (cdr (assoc (car thresholder) actual-results :test #'string=)))
         (thresholder-value (cdr thresholder))
         (compare-result 
          (make-comparator-result :name (car thresholder)
                                  :actual-value actual-value
                                  :original-value thresholder-value)))
    (when actual-value
      (setf (comparator-result-difference compare-result)
            (coerce (calculate-degradation actual-value thresholder-value
                                           actual-performance-index
                                           threshold-performance-index)
                    'double-float)
            (comparator-result-pass-p compare-result)
            (<= (funcall abs-function 
                         (comparator-result-difference compare-result))
                tolerance)))
    compare-result))
 
(defun compare-results* (aar-results original-results tolerance abs-function
                         actual-performance-index threshold-performance-index)
  (map 'list 
       (lambda (thresholder) 
         (check-thresholder aar-results thresholder tolerance abs-function
                            actual-performance-index 
                            threshold-performance-index)) 
       original-results))

(defun generate-xml-for-comparison (compare-results)
  (cxml:with-xml-output (cxml:make-string-sink :indentation 2)
    (cxml:with-element "testsuite"
      (cxml:attribute "name" "Thresholder tests")
      (dolist (result compare-results)
        (cxml:with-element "testcase"
          (cxml:attribute "name" (comparator-result-name result))
          (when (not (comparator-result-pass-p result))
            (cxml:with-element "failure"
              (cxml:text
               (if (comparator-result-actual-value result)
                   (format
                    nil 
                    "Degradation is ~7,2F%, current result is ~a, threshold is ~a"
                    (* (comparator-result-difference result) 100)
                    (comparator-result-actual-value result)
                    (comparator-result-original-value result))
                   (format nil "There is no data for ~a" 
                           (comparator-result-name result)))))))))))

(defun compare-files (parser metric-file threshold-file tolerance abs-function
                      actual-performance-index threshold-performance-index)
  (compare-results* 
   (funcall parser metric-file)
   (funcall parser threshold-file) 
   tolerance
   abs-function
   actual-performance-index
   threshold-performance-index))

(defun load-comparison (file)
  (parse-xml-file file))

(defun save-comparison (parser actual thresholder save-to 
                        &key (tolerance 0) (abs-function #'identity)
                        (actual-performance-index 1) 
                        (threshold-performance-index 1))
  (with-new-file (xml-stream save-to)
    (format 
     xml-stream 
     (generate-xml-for-comparison 
      (compare-files parser actual thresholder tolerance abs-function
                     actual-performance-index threshold-performance-index)))))



;;;
;;; Update threshold functionality
;;;

(defun threshold-passed-p (comparison-results)
  (reduce (lambda (passed1 passed2) (and passed1 passed2))
          comparison-results :key #'comparator-result-pass-p))

(defun update-threshold (parser metric-file threshold-file 
                         &key (tolerance 0) (abs-function #'identity)
                         actual-performance-index-file
                         threshold-performance-index-file)
  (when (threshold-passed-p 
         (compare-files 
          parser metric-file threshold-file tolerance 
          abs-function 
          (load-performance-index actual-performance-index-file)
          (load-performance-index threshold-performance-index-file)))
    (fad:copy-file metric-file threshold-file :overwrite t)
    (when actual-performance-index-file 
      (fad:copy-file actual-performance-index-file 
                     threshold-performance-index-file :overwrite t))))



;;;
;;; Global properties
;;;

(defun load-properties (property-file)
  (with-open-file (stream property-file :direction :input)
    (read stream)))

(defun make-global-variable-name (symbol)
  (intern (format nil "*~a*" symbol)))

(defmacro define-global-properties (property-file)
  (let ((properties (load-properties property-file)))
    (cons 'progn
          (loop for property-key in properties by #'cddr
             for property-value in (cdr properties) by #'cddr
             collecting 
               (list 'defvar (make-global-variable-name property-key) 
                     property-value)))))

(define-global-properties "../thresholds/properties.dat")

;;;
;;; Ant targets
;;;

(defun verify-cpd ()
  (save-duplication-summary (directory *cpd-file-mask*) *cpd-summary-file*)
  (save-comparison #'parse-cpd-summary 
                   *cpd-summary-file* 
                   *cpd-threshold* 
                   *cpd-junit-output*))

(defun verify-enterprise-perf-tests ()
  (format t "~%* Performance tolerance is ~a *~%~%" 
          *enterprise-performance-tolerance*)
  (save-comparison #'parse-performance-measurements
                   *performance-summary*
                   *enterprise-performance-threshold*
                   *performance-junit-output*
                   :tolerance *enterprise-performance-tolerance*
                   :actual-performance-index 
                   (load-performance-index 
                    "../../../results/performancetests/performance-index.txt")
                   :threshold-performance-index
                   (load-performance-index 
                    "../thresholds/enterprise-threshold-performance-index.txt")))

(defun verify-standard-perf-tests ()
  (format t "~%* Performance tolerance is ~a *~%~%" 
          *standard-performance-tolerance*)
  (save-comparison #'parse-performance-measurements
                   *performance-summary*
                   *standard-performance-threshold*
                   *performance-junit-output*
                   :tolerance *standard-performance-tolerance*
                   :abs-function #'abs
                   :actual-performance-index
                   (load-performance-index 
                    "../../../results/performancetests/performance-index.txt")
                   :threshold-performance-index
                   (load-performance-index 
                    "../thresholds/standard-threshold-performance-index.txt")))

(defun update-cpd-threshold ()
  (update-threshold #'parse-cpd-summary *cpd-summary-file* *cpd-threshold*))

(defun update-enterprise-perf-threshold ()
  (update-threshold 
   #'parse-performance-measurements
   *performance-summary*
   *enterprise-performance-threshold*
   :tolerance *enterprise-performance-tolerance*
   :actual-performance-index-file 
   "../../../results/performancetests/performance-index.txt"
   :threshold-performance-index-file
   "../thresholds/enterprise-threshold-performance-index.txt"))

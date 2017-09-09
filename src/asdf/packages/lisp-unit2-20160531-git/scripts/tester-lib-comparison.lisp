(in-package :lisp-unit2)
(cl-interpol:enable-interpol-syntax)

;; List pulled by cross-referencing http://www.cliki.net/Test%20Framework
;; with ql-dist
(defparameter +test-systems+
  '(:lisp-unit :lisp-unit2
    :xptest :stefil :clunit :lift :fiveam :ptester :eos :cl-test-more
    :cl-quickcheck :rt :hu.dwim.stefil :testbild :unit-test :xlunit))

(defun find-systems-that-require (s)
  (iter (for system in (ql-dist:provided-systems t))
        (when (member s (ql-dist:required-systems system)
                      :test #'(lambda (x y) (string-equal (string x) (string y))))
          (collect system))))

(defun collect-systems-that-require (&key (systems +test-systems+))
  (let ((ht (make-hash-table)))
    (iter (for s in (alexandria:ensure-list systems))
      (setf (gethash s ht) (find-systems-that-require s)))
    ht))

(defparameter +test-systems-required-from+ (collect-systems-that-require))

(defun print-statistics ( &key (hash +test-systems-required-from+) (stream *test-stream*))
  (format stream "~:{~%~A (~D)~}~%"
          (sort
           (iter (for (k v) in-hashtable hash)
             (collect (list k (len v))))
           #'> :key #'second)))
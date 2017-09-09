(in-package :cl-user)

(eval-when (:compile-toplevel :load-toplevel)
  (error "Don't compile this file"))

(defun pathname-from-here (relative-pathname)
  ; pathname relative to the directory of *load-truename*
  (let* ((path-to-load-truename (make-pathname :defaults (pathname #.*load-truename*) :name nil :type nil)))
    (merge-pathnames relative-pathname path-to-load-truename)))

#+sbcl
(require :sb-posix)

(defun run-tests-getenv (x)
    "getenv. X is a string (variable name). Stolen from UIOP. Name is just to avoid clashes. "
    (declare (ignorable x))
    #+(or clozure ccl) (ccl:getenv x)
    #+lispworks (lispworks:environment-variable x)
    #+sbcl (sb-posix:getenv x)
    #-(or clozure ccl lispworks sbcl)
    (error "~S is not supported on your implementation" 'run-tests-getenv))

#+(or sbcl ccl)
(unless (member :coverage *features*) ; could be assigned in command line by ant, see build.xml/check-coverage
  (when (string= (run-tests-getenv "G2_UNIT_TESTS_CALCULATE_COVERAGE") "yes")
    (pushnew :coverage *features*)))

(defvar *coverage-dir*)

#+coverage
(unless (boundp '*coverage-dir*) ; could be assigned in command line by ant, see build.xml/check-coverage
  (setq *coverage-dir* (pathname-from-here #p"../../../results/coverage/lisp/")))

#+coverage
(setq *coverage-dir* (merge-pathnames #+sbcl "sbcl64/"
				      #+ccl "ccl64/"
				      #+lispworks "lw64/"
				      *coverage-dir*))

;; Delete old report

#+coverage
(defun delete-old-coverage-report ()
  (dolist (extension (list "html" "js" "csv"))
    (let* ((mask (format nil "*.~A" extension))
           (mask-with-path (merge-pathnames mask *coverage-dir*)))
      (dolist (file (directory mask-with-path))
        (format t "~%delete-old-coverage-report: deleting ~A~%" file)
        (delete-file file)))))

#+coverage
(delete-old-coverage-report)

;; Enable coverage data generation 
#+(and sbcl coverage)
(require :sb-cover)

#+(and sbcl coverage)
;;; Turn on generation of code coverage instrumentation in the compiler
(declaim (optimize sb-cover:store-coverage-data))

#+(and sbcl coverage)
;;; This fixes the problem of "Immobile space exhausted"
(setq sb-c::*compile-to-memory-space* :dynamic)

#+(and ccl coverage)
(setq ccl:*compile-code-coverage* t) 

;; Do tests
(load "load-tests.lisp")
(asdf:load-system :lisp-unit :force t)
(asdf:load-system :mock-macro :force t)
(asdf:load-system :cxml :force t)
(asdf:load-system :cl-junit-xml.lisp-unit :force t)
(defpackage :tests
  (:use :cl :mock-macro :lisp-unit))
(load-everything "7rpm")

;; Reset coverage info before running tests
#+(and sbcl coverage) 
(sb-cover:reset-coverage)

#+(and ccl coverage)
(reset-coverage)

(setq lisp-unit:*print-failures* t)

(defvar *test-results*
  (lisp-unit:run-tests :all "TESTS"))

(defvar *test-results-xml*
  (make-pathname :name #+sbcl "lisp-unit-tests_sbcl"
		       #+ccl "lisp-unit-tests_ccl"
		       #+lispworks "lisp-unit-tests_lw"
		 :type "xml"
		 :defaults (pathname-from-here "../../../results/")))

;; Write Lisp unit tests result into XML (JUnit format)
(when *test-results*
  (lisp-unit:print-errors *test-results*)
  (cl-junit-xml:write-xml *test-results* *test-results-xml*
			  :name (format nil "UNIT-TESTS/~A" #+sbcl "SBCL" #+ccl "CCL" #+lispworks "LW")
			  :pretty-p t))

#+coverage
(format t "Reporting Code Coverage ... ")

;; Turn off instrumentation
#+(and sbcl coverage)
(declaim (optimize (sb-cover:store-coverage-data 0)))

#+(and ccl coverage)
(setq ccl:*compile-code-coverage* nil) 

;; Remove unnecessary files from stat, produce a coverage report with total percentage
#+(and sbcl coverage)
(load "post-process-sb-cover-results.lisp")

#+(and sbcl coverage)
(progn
  (sb-cover::delete-unnecessary-coverage-stats)
  (sb-cover::report-with-expression-totals *coverage-dir*))

#+(and ccl coverage) 
(progn
  ; fix misbehaving function in coverage reporting tool
  (assert (not (boundp '*old-report-file-coverage*)) () "Cannot run tests twice in same image")
  (defparameter *old-report-file-coverage* #'ccl::report-file-coverage)
  (let ((ccl:*warn-if-redefine-kernel* nil))
    (defun ccl::report-file-coverage (&rest args)
      (multiple-value-bind (result maybe-error)
          (ignore-errors
            (apply *old-report-file-coverage* args))
        (when (typep maybe-error 'error)
          (format t "~%ccl::report-file-coverage failed on ~S, result can be incomplete~%" args))
        (values)))))

#+(and ccl coverage)
(ccl:report-coverage *coverage-dir*)

(format t "Done and quit.~%")

(cl-user::quit)

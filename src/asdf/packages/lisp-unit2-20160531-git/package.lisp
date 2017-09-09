(in-package :cl-user)

(handler-bind
    ;; fixes sbcl SUPER warnings that prevent automatic fasl loading
    ;; These are generated when the package definition doesnt match
    ;; the one currently in the file (eg: removing an export)
    ((warning (lambda (c)
                (format *error-output* "~A~%~S" c c)
                (muffle-warning c))))
  (defpackage :lisp-unit2
    (:use :common-lisp :iter)
    ;; Print parameters
    (:export #:*test-stream*)
    ;; Forms for assertions
    (:export
     :assert-eq :assert-eql :assert-equal :assert-equalp
     :assert-equality :assert-prints :assert-expands :assert-true
     :assert-false :assert-error :assert-no-error
     :assert-warning :assert-no-warning
     :assert-signal :assert-no-signal
     :assert-typep
     ;; floating point
     :*measure* :*epsilon* :*significant-figures*
     :default-epsilon :sumsq :sump :norm
     :relative-error :relative-error-norm
     :array-error
     :float-equal :assert-float-equal
     :sigfig-equal :assert-sigfig-equal
     :norm-equal :assert-norm-equal
     :number-equal :assert-number-equal
     :numerical-equal :assert-numerical-equal
     ;; rational
     :assert-rational-equal :rational-equal
     )
    ;; signals
    (:export
     :test-start :test-complete :all-tests-start :all-tests-complete
     :missing-test :collect-test-results
     :assertion-pass :assert-fail)
    ;; Functions for managing tests
    (:export
     ;; statuses
     :errors :failed :warnings :passed :missing :empty
     :define-test :*test-db*
     :undefine-test
     :uninstall-test
     :list-tests
     :get-tests
     :test-code
     :test-documentation
     :remove-tests
     :run-tests
     :run-test
     :rerun-tests
     :rerun-failures
     :reset-test-database
     :with-test-signals-muffled
     :unit-test :*unit-test*
     :*results* :*result*
     :test-results-db :test-result
     :failure-result)
    ;; Functions for managing tags
    (:export
     :list-tags
     :tagged-tests
     :remove-tags)
    ;; Functions for reporting test results
    (:export
     :with-summary
     :with-summary-context
     :with-test-results
     :with-test-results-context
     :with-assertion-summary
     :with-assertion-summary-context
     :with-failure-debugging
     :with-failure-debugging-context
     :test-names
     :print-summary
     :print-failure-summary
     :print-status-summary
     :summarize-results
     :with-tap-summary
     :with-tap-context
     :write-tap
     :write-tap-to-file
     :*result* :*results*)
    ;; Functions for extensibility via signals
    (:export #:assertion-pass #:assertion-fail
             #:all-tests-start #:all-tests-complete
             #:test-start #:test-complete
             :results)
    ;; Utility predicates
    (:export :logically-equal :set-equal)))

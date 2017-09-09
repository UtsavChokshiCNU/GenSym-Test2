(in-package :cl-user)

(handler-bind
    ;; fixes sbcl SUPER warnings that prevent automatic fasl loading
    ((warning (lambda (c)
                (format *error-output* "~A~%~S" c c)
                (muffle-warning c))))
  (defpackage :lisp-unit2-asserts
    (:import-from :lisp-unit2
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
     :assert-rational-equal :rational-equal)
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
     )))

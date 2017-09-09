;;;
;;; Copyright (c) 2010 Serhiy Yakovyn
;;; 
;;; Permission is hereby granted, free of charge, to any person obtaining 
;;; a copy of this software and associated documentation files (the "Software"),
;;; to deal in the Software without restriction, including without limitation 
;;; the rights to use, copy, modify, merge, publish, distribute, sublicense, 
;;; and/or sell copies of the Software, and to permit persons to whom the 
;;; Software is furnished to do so, subject to the following conditions:
;;; 
;;; The above copyright notice and this permission notice shall be included 
;;; in all copies or substantial portions of the Software.
;;; 
;;; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
;;; OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
;;; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
;;; THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
;;; OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
;;; ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
;;; OTHER DEALINGS IN THE SOFTWARE.
;;;

(cl:eval-when (:compile-toplevel :load-toplevel :execute)
  (cl:defpackage :mock (:use :cl)
    (:export
     #:expect
     #:with-wrapped-functions*
    )))

(in-package :mock)

(defstruct (call-expectation (:type vector))
  function
  args
  return
  bindings)

(defun make-call-form (expected-call)
  (cons (call-expectation-function expected-call) 
        (call-expectation-args expected-call)))

(defun bind-value-to-var (binding)
    (setf (symbol-value (first binding)) (second binding)))

(defparameter *expected-calls* nil)

(defun check-call (expected-call actual-call)
  (unless (equalp expected-call actual-call)
    (error "Expected ~:[no call~;~:*~a~], but got ~a." 
           expected-call actual-call))
  t)

(defun add-expected-call (function args &key return bind)
  (push (make-call-expectation
         :function function
         :args args
         :return return
         :bindings bind) *expected-calls*))

;;;
;;; Mocking functionality
;;;
(defun mock-function (function args)
  (let ((expected-call (pop *expected-calls*))
        (actual-call (cons function args)))
    (check-call (when expected-call
                  (make-call-form expected-call))
                actual-call)
    (mapc #'bind-value-to-var (call-expectation-bindings expected-call))
    (car (call-expectation-return expected-call))))

(defun extract-functions ()
  (let ((functions))
    (dolist (call-expectation *expected-calls*)
      (pushnew (call-expectation-function call-expectation) functions))
    functions))

(defun create-mocking-lambda (function-symbol)
  (lambda (&rest args) (mock-function function-symbol args)))

(defun set-mock-function (function-symbol)
  (let ((old-symbol-function 
         (cons function-symbol (symbol-function function-symbol))))
    (setf (symbol-function function-symbol) 
          (create-mocking-lambda function-symbol))
    old-symbol-function))

(defun restore-original-function (symbol-and-function)
  (setf (symbol-function (car symbol-and-function)) (cdr symbol-and-function)))

(defun verify ()
  (when *expected-calls*
    (error "Expected:~{ ~a~}, but got nothing" 
           (mapcar #'make-call-form *expected-calls*))))

;;;
;;; Helper functions
;;;
(defmacro expand-binding (var value)
  `(list ',var ,value)) 

(defmacro expand-bindings (bindings)
  `(list ,@(mapcar 
            (lambda (binding) 
              `(expand-binding ,(car binding) ,(second binding)))
            bindings)))

(defmacro transform-call ((&key ((:call (function &rest args))) 
                                ((:return values))
                                ((:bind bindings))))
  `(add-expected-call ',function (list ,@args) :return (list ,@values) 
                      :bind (expand-bindings ,bindings)))

(defmacro with-temp-vars (vars &body body)
  `(let ,(let ((result nil)) 
              (dolist (var vars (nreverse result)) 
                (push (list var `',(make-symbol (symbol-name var))) result)))
     ,@body))

;;;
;;; Expect macro
;;;
(defmacro expect (expected-calls &key ((:for form)))
  "Expect defines expectations for a given call.
E.g. (expect ((:call (func1 3) :return (7))
              (:call (func2 (/ 3 4) 'a) :return ('b)))
             :for (func-under-test 'a 'b 'c))"
  (with-temp-vars (result old-functions)
    `(let ((*expected-calls*)
           (,old-functions)
           (,result))
       ,@(mapcar 
          (lambda (expected-call) `(transform-call ,expected-call))
          expected-calls)
       (setf *expected-calls* (reverse *expected-calls*))
       (setf ,old-functions 
             (mapcar #'set-mock-function (extract-functions)))
       (unwind-protect (setf ,result ,form)
         (mapc #'restore-original-function ,old-functions))
       (verify)
       ,result)))

(defmacro with-wrapped-function ((function-name substitute) &body body)
  (assert (symbolp function-name))
  (with-temp-vars (original-function decorator)
    `(let* ((,original-function (symbol-function ',function-name))
            (,decorator (lambda (&rest args)
                         (apply ,substitute ,original-function args))))
       (unwind-protect
           (progn
             (setf (symbol-function ',function-name) ,decorator)
             ,@body)
         (setf (symbol-function ',function-name) ,original-function)))))

(defmacro with-wrapped-functions* (bindings &body body)
  "Temporarily replaces the global functions according to bindings, and evaluates
  the body. Each binding is of form (symbol substitute-function), where symbol 
  (not evaluated) must name a global function. Substitute-function (evaluated) is 
  a function designator. It is passed same parameters as an original function. 
  Additionally, one parameter, fn, is added in front or actual parameter list. 
  Original, non-modified function object will be passed to substitute-function 
  via fn parameter. With this modifications in scope, body is evaluated in 
  an implicit progn. Bindings are processed sequentially. 
  "
  (cond
   ((null bindings)
    `(progn ,@body))
   (t
    (destructuring-bind (function-name wrapper) (car bindings)
      `(with-wrapped-function (,function-name ,wrapper)
         (with-wrapped-functions* ,(cdr bindings)
                                  ,@body))))))

(defun test-with-wrapped-function-fn (x)
  (* x 2))

(defun assert-with-wrapped-function-works ()
  (assert
      (=
       32
       (+ 
        (with-wrapped-functions* ((test-with-wrapped-function-fn
                                  (lambda (fn y) (* 3 (funcall fn y)))))
          (test-with-wrapped-function-fn 5))
        (test-with-wrapped-function-fn 1)
        ))))

(assert-with-wrapped-function-works)

     
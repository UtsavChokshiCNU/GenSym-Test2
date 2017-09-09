;;  LISP-UNIT Example Tests

(in-package :lisp-unit2-tests)

(defparameter *example-db* (make-instance 'lisp-unit2::test-database))

(define-condition super-test-warning (warning)
  ())

(define-condition sub-test-warning (super-test-warning)
  ())


(let ((lisp-unit2::*test-db* *example-db*))

  (defun false-max (x y)
    "Deliberately wrong"
    (when (eql y :error)
      (error "y is wrong"))
    x)

  (define-test test-my-max (:tags '(examples failed))
    ;; Wrong
    (assert-equal 5 (false-max 2 5))
    (assert-equal 5 (false-max 5 2))
    (assert-equal 10 (false-max -10 10))
    (assert-equal 0 (false-max -5 0)))

  (define-test test-my-max-error (:tags '(examples errors))
    (assert-equal 0 (false-max -5 :Error)))

  (defun my-sqrt (n)
    "Not really."
    (/ n 2))

  (define-test test-my-sqrt (:tags 'examples)
    (dotimes (i 5)
      (assert-equal i (my-sqrt (* i i)) i)))

  (define-test lisp-unit2-test-2::my-sqrt (:tags '(examples cl-user-tests))
    (dotimes (i 5)
      (assert-equal i (my-sqrt (* i i)) i)))

;;; Macro

  (defmacro my-macro (arg1 arg2)
    (let ((g1 (gensym))
          (g2 (gensym)))
      `(let ((,g1 ,arg1)
             (,g2 ,arg2))
        "Start"
        (+ ,g1 ,g2 3))))

  (define-test test-macro (:tags '(examples macros))
    (assert-expands
     (let ((#:G1 A) (#:G2 B)) "Start" (+ #:G1 #:G2 3))
     (my-macro a b)))

;;; Tags

  (defun add-integer (integer1 integer2)
    "Add 2 integer numbers"
    (check-type integer1 integer)
    (check-type integer2 integer)
    (+ integer1 integer2))

  (defun subtract-integer (integer1 integer2)
    "Subtract 2 integer numbers"
    (check-type integer1 integer)
    (check-type integer2 integer)
    (- integer1 integer2))

  (define-test add-integer-test (:tags '(examples add integer examples))
    "Test add-integer for values and errors."
    (assert-eql 3 (add-integer 1 2))
    (assert-error 'type-error (add-integer 1.0 2))
    (assert-error 'type-error (add-integer 1 2.0)))

  (define-test subtract-integer-test (:tags '(subtract integer examples))
    "Test subtract-integer for values and errors."
    (add-integer-test);; just to prove tests calling other tests work
    (lisp-unit2:run-tests :tests 'add-integer-test)
    (assert-eql 1 (subtract-integer 3 2))
    (assert-error 'type-error (subtract-integer 3.0 2))
    (assert-error 'type-error (subtract-integer 2 3.0)))

  (defun add-float (float1 float2)
    "Add 2 floating point numbers"
    (check-type float1 float)
    (check-type float2 float)
    (+ float1 float2))

  (defun subtract-float (float1 float2)
    "Subtract 2 floating point numbers"
    (check-type float1 float)
    (check-type float2 float)
    (- float1 float2))

  (define-test add-float-test (:tags '(add float examples))
    "Test add-float for values and errors."
    (assert-eql 3.0 (add-float 1.0 2.0))
    (assert-error 'type-error (add-float 1.0 2))
    (assert-error 'type-error (add-float 1 2.0)))

  (define-test subtract-float-test (:tags '(subtract float examples))
    "Test subtract-float for values and errors."
    (assert-eql 1.0 (subtract-float 3.0 2.0))
    (assert-error 'type-error (subtract-float 3.0 2))
    (assert-error 'type-error (subtract-float 2 3.0)))

  (defun add-complex (complex1 complex2)
    "Add 2 complex numbers"
    (check-type complex1 complex)
    (check-type complex2 complex)
    (+ complex1 complex2))

  (defun subtract-complex (complex1 complex2)
    "Subtract 2 complex numbers"
    (check-type complex1 complex)
    (check-type complex2 complex)
    (- complex1 complex2))

  (define-test add-complex-test (:tags '(add complex examples))
    "Test add-complex for values and errors."
    (assert-eql #C(3 5) (add-complex #C(1 2) #C(2 3)))
    (assert-error 'type-error (add-integer #C(1 2) 3))
    (assert-error 'type-error (add-integer 1 #C(2 3))))

  (define-test subtract-complex-test (:tags '(subtract complex examples))
    "Test subtract-complex for values and errors."
    (assert-eql #C(1 2) (subtract-complex #C(3 5) #C(2 3)))
    (assert-error 'type-error (subtract-integer #C(3 5) 2))
    (assert-error 'type-error (subtract-integer 2 #C(2 3))))

  (handler-bind ((warning #'muffle-warning))
    (define-test uncaught-warnings (:tags '(warnings))
      (let ((foo 0))
        (warn "Foo"))))

  (define-test warns-some-warnings (:tags '(warnings))

    (assert-warning
     'super-test-warning
     (progn (warn 'super-test-warning) (values)))

    (assert-warning
     'super-test-warning
     (progn (warn 'sub-test-warning) (values)))

    (let (warning?)
      (handler-bind ((warning (lambda (c)
                                (setf warning? c)
                                (muffle-warning c))))
        (assert-no-warning
         'super-test-warning
         (progn (warn "foo") (values))))
      (assert-true warning?))

    (let (warning?)
      (handler-bind ((warning (lambda (c)
                                (setf warning? c)
                                (muffle-warning c))))
        (assert-no-warning
         'sub-test-warning
         (progn (warn 'super-test-warning) (values)))
        (assert-true warning?))))
  ) ;; finish example-database-construction

(defun meta-test-context (body-fn)
  (let ((lisp-unit2::*test-db* *example-db*)
        *debugger-hook*
        (lisp-unit2::*test-stream* (make-broadcast-stream)))
    (handler-bind
        ((warning #'muffle-warning))
      (funcall body-fn))))

(defmacro with-meta-test-context (() &body body)
  `(meta-test-context
    (lambda () ,@body)))

(defun %run-meta-tags (tags
                       &key run-contexts
                       &aux (lisp-unit2::*test-db* *example-db*)
                       (*package* (find-package :lisp-unit2-tests)))
  ;; runs the tags from the example tests with all test signals aborted
  (lisp-unit2:with-test-signals-muffled ()
    (lisp-unit2:run-tests :tags tags :run-contexts run-contexts)))

(define-test test-with-test-results (:tags '(meta-tests)
                                     :contexts #'meta-test-context)
  (let ( results )
    (lisp-unit2:with-test-signals-muffled ()
      (lisp-unit2:with-test-results (:collection-place results)
        (lisp-unit2:run-tests :tags 'warnings)
        (lisp-unit2:run-tests :tags 'examples)))
    ;; subtract-integer-test calls run-tests
    (assert-eql 3 (len results))
    (assert-typep 'lisp-unit2::test-results-db (first results))))

(define-test test-warning-assertions (:tags '(meta-tests)
                                      :contexts #'meta-test-context)
  (let ((res (%run-meta-tags 'warnings)))
    (assert-eql 2 (len (lisp-unit2::tests res)))
    (assert-eql 6 (len (lisp-unit2::passed-assertions res)))
    (assert-eql 1 (len (lisp-unit2::warnings res)))
    (assert-eql 2 (len (lisp-unit2::all-warnings res)))))

(define-test test-failing-assertions (:tags '(meta-tests)
                                      :contexts #'meta-test-context)
  (let ((res (%run-meta-tags 'failed)))
    (assert-eql 1 (len (lisp-unit2::tests res)))
    (assert-eql 3 (len (lisp-unit2::failed-assertions res)))
    (assert-eql 1 (len (lisp-unit2::passed-assertions res)))
    (assert-eql 0 (len (lisp-unit2::errors res)))))

(define-test test-erroring-unit-tests (:tags '(meta-tests)
                                       :contexts #'meta-test-context)
  (let ((res (%run-meta-tags 'errors)))
    (assert-eql 1 (len (lisp-unit2::tests res)))
    (assert-eql 1 (len (lisp-unit2::errors res)))))

(define-test meta-tests (:tags '(meta-tests)
                         :contexts #'meta-test-context)
  (let ((res (%run-meta-tags nil)))
    (assert-eql 12 (len (lisp-unit2::tests res)))
    (assert-eql 6 (len (lisp-unit2::failed-assertions res)))
    (assert-eql 34 (len (lisp-unit2::passed-assertions res)))
    (assert-eql 1 (len (lisp-unit2::errors res)))
    (assert-eql 1 (len (lisp-unit2::warnings res)))))


#|
 Copyright (c) 2010-2012, Thomas M. Hermann
 All rights reserved.

 Redistribution and  use  in  source  and  binary  forms, with or without
 modification, are permitted  provided  that the following conditions are
 met:

   o  Redistributions of  source  code  must  retain  the above copyright
      notice, this list of conditions and the following disclaimer.
   o  Redistributions in binary  form  must reproduce the above copyright
      notice, this list of  conditions  and  the  following disclaimer in
      the  documentation  and/or   other   materials  provided  with  the
      distribution.
   o  The names of the contributors may not be used to endorse or promote
      products derived from this software without  specific prior written
      permission.

 THIS SOFTWARE IS  PROVIDED  BY  THE  COPYRIGHT  HOLDERS AND CONTRIBUTORS
 "AS IS"  AND  ANY  EXPRESS  OR  IMPLIED  WARRANTIES, INCLUDING,  BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES  OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR  CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT LIMITED TO,
 PROCUREMENT OF  SUBSTITUTE  GOODS  OR  SERVICES;  LOSS  OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER  CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER  IN  CONTRACT,  STRICT  LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR  OTHERWISE)  ARISING  IN  ANY  WAY  OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

|#
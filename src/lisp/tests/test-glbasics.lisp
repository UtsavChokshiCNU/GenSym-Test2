(in-package :tests)

(defun test-the ()
  (the fixnum (values 1 2)))

(define-test test-the-behavior
  (assert-equal '(1 2) (multiple-value-list (test-the))))

(defun div0 (number) (ab::/e number 0d0))

(define-test test-division-zero-by-zero
  (assert-true (ab::nanp (div0 0d0))))

(define-test test-division-one-by-zero
  (assert-true (ab::positive-infinity-p (div0 1d0))))

(define-test test-division-minus-one-by-zero
  (assert-true (ab::negative-infinity-p (div0 -1d0))))

(define-test test-expt2
  (assert-equal 0.5d0 (ab::expt2 -1)))


(defmacro i-with-gensyms-for-args-test-macro (x y z)
  (ab::with-gensyms-for-args (x y z) `(list ,x ,y ,z)))


;; UNUSED-CODE with-reusable-gensyms 
(defun i-with-gensyms-for-args-test-body ()
  (mock::expect
   ((:call (ab::gensym-gensym) :return ('+))
    (:call (ab::gensym-gensym) :return ('-))
    (:call (ab::gensym-gensym) :return ('*))
    )
   :for
   (macroexpand-1 '(i-with-gensyms-for-args-test-macro 1 2 3))
   ))

(define-test test-with-gensyms-for-args
  (assert-equalp
   '(AB::LET ((+ 1) (- 2) (* 3)) (LIST + - *))
   (i-with-gensyms-for-args-test-body)))

(define-test test-gensym-make-symbol-good-arg
  (dolist (good-arg '("" "SYMBOL" "Symbol" symbol))
    (assert-true
     (every 'eql
            (string good-arg)
            (string (ab::gensym-make-symbol good-arg))))))


(define-test test-gensym-make-symbol-bad-arg
  (dolist (bad-arg `(123 123.456 1/5 #\c ,*package*)) 
    (assert-error 'error (ab::gensym-make-symbol bad-arg))))

(define-test test-that-make-symbol-and-gensym-gensym-are-nonrepeating
  (assert-false
   (eq (ab::gensym-gensym) (ab::gensym-gensym)))
  (assert-false
   (eq (ab::gensym-make-symbol "A") (ab::gensym-make-symbol "A"))))


(defmacro i-with-make-symbols-for-args-test-macro (x y z)
  (ab::with-make-symbols-for-args (x y z) `(list ,x ,y ,z)))


(defun i-with-make-symbols-for-args-test-body ()
  (mock::expect
   ((:call (ab::gensym-make-symbol 'x) :return ('+))
    (:call (ab::gensym-make-symbol 'y) :return ('-))
    (:call (ab::gensym-make-symbol 'z) :return ('*))
    )
   :for
   (macroexpand-1 '(i-with-make-symbols-for-args-test-macro 1 2 3))
   ))

(define-test test-with-make-symbols-for-args
  (assert-equalp
   '(AB::LET ((+ 1) (- 2) (* 3)) (LIST + - *))
   (i-with-make-symbols-for-args-test-body)))


(define-test def-substitution-macro-regression
  (assert-equalp
   (macroexpand-1 '(ab::def-substitution-macro designation-p (form)
                     (if (atom form)
                         (and form (symbolp form))
                       (designation-operator-or-giver-of-value-p (car form)))))
   (values
    '(progn
       (ab::note-function-call-macro 'designation-p)
       (ab::defmacro designation-p (form)
         (ab::expand-by-substituting-args-if-all-trivial
          (form)
          '(if (atom form)
               (and form
                    (symbolp form))
             (designation-operator-or-giver-of-value-p (car form))))))
    t)))


(define-test test-build-ab-symbol
  "Non-exhaustive test taken from the docstring"
  (assert-eq
   (let ((name 'foo)
         (n 12))
     (ab::build-ab-symbol "fast-Stuff" name :bar N))
   (values 'ab::fast-stuff-foo-bar-12 :internal)))
   
(define-test test-build-ab-symbol-no-hyphens
  "Non-exhaustive test taken from the docstring"
  (assert-eq
   (let ((name 'foo)
         (n 12))
     (ab::build-ab-symbol-no-hyphens "fast-Stuff" name :bar N))
   (values 'ab::fast-stufffoobar12 :internal)))



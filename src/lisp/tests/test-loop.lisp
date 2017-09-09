
(in-package :tests)


;;;; LOOP test suite from SBCL

;;; This software is part of the SBCL system. See the README file for
;;; more information.
;;;
;;; While most of SBCL is derived from the CMU CL system, the test
;;; files (like this one) were written from scratch after the fork
;;; from CMU CL.
;;;
;;; This software is in the public domain and is provided with
;;; absolutely no warranty. See the COPYING and CREDITS files for
;;; more information.


(define-test test-loop-destructuring-conses
  (assert-equal
   '(0.0 1.0 2.0 3.0)
   (eval '(ab::loop with (a . b) = '(0.0 . 1.0)
                    and (c . d) = '(2.0 . 3.0)
                    return (list a b c d)))))

#-exclude-possible-bugs
(define-test test-loop-compound-forms-requirement
  "LOOP syntax requires that forms after INITIALLY, FINALLY, and DO must be compound forms"
  (multiple-value-bind (function warnings-p failure-p)
      (compile nil
               '(lambda ()
                  (ab::loop while t do
                            *print-level*
                            (print t))))
    (declare (ignore function warnings-p))
    (assert-true failure-p)))

;;; a bug reported by Paul F. Dietz (in his ANSI test suite):
;;; duplicate bindings in LOOP must signal errors of type
;;; PROGRAM-ERROR.
(define-test test-loop-duplicate-bindings-must-signal-program-error
  (assert-true (typep (nth-value 1
                                 (eval 
                                  '(ignore-errors
                                     (funcall (lambda ()
                                                (ab::loop for (a . a) in '((1 . 2) (3 . 4))
                                                          return a))))))
                      'error)))

#| ab have no downto
  (define-test test-loop-gcl-ansi-test-loop-1-27
    (assert-equal (ab::loop for x downto 7 by 2 from 13 collect x) '(13 11 9 7))) |#


;; ab loop have no "external-symbols" clause
;; (assert (= (ab::loop for nil being the external-symbols of :cl count t) 978))
;; (assert (= (ab::loop for x being the external-symbols of :cl count x) 977))

;; ab loop have no "each external-symbol" clause
;; (let ((*package* (find-package :cl)))
;;  (assert (= (ab::loop for x being each external-symbol count t) 978)))

(define-test test-loop-return-in-for-assignment
  (assert-eq (eval '(ab::loop for a = (return t) return nil)) t))

(define-test test-loop-the-and-repeat
  (assert-equal (eval '(ab::loop for i from 1 repeat (the (integer 7 7) 7) collect i))
                '(1 2 3 4 5 6 7)))


#|(multiple-value-bind (result error)
    (ignore-errors
      (eval '(ab::loop for i from 1 repeat 7 of-type fixnum collect i)))
  (assert (null result))
  (assert (typep error 'program-error)))|#


(define-test test-loop-repeat-collect
  (assert-error
   t
   (eval '(ab::loop for i from 1 repeat 6.5 collect i)))
  (assert-error
   'error
   (eval '(ab::loop for i from 1 repeat (eval '6.5) collect i))))

(define-test test-loop-return-from-block-and-loop-finish
  (assert-eq
   (eval '(block nil
            (ab::loop named foo do (ab::loop-finish) finally (return :good))
            :bad))
   :good))

(define-test test-loop-with-destructuring-and-return
  (assert-eql (eval '(ab::loop with (a nil) = '(1 2) return a)) 1)
  (assert-eql (eval '(ab::loop with (nil a) = '(1 2) return a)) 2)
  (assert-eql (eval '(ab::loop with (a . nil) = '(1 2) return a)) 1)
  (assert-equal (eval '(ab::loop with (nil . a) = '(1 2) return a)) '(2)))

#-exclude-possible-bugs
(define-test test-loop-collect-always-errs
  (multiple-value-bind (result error)
      (ignore-errors
        (ab::loop for i in '(1 2 3) collect i always (< i 4)))
    (assert-false result)
    (assert-true (typep error 'error))))


(define-test test-loop-collect-into-always-<
  (assert-equal
   (eval '(ab::loop for i in '(1 2 3) collect i into foo always (< i 4)
                    finally (return foo)))
   '(1 2 3)))

(define-test test-loop-collect-into-always-=
  (assert-equal
   (eval '(ab::loop for i in '(1 2 3) collect i into foo always (= i 4)
                    finally (return foo)))
   nil))

#-exclude-possible-bugs
(multiple-value-bind (result error)
    (ignore-errors
      (ab::loop for i in '(1 2 3) always (< i 4) collect i))
  (assert-false result)
  (assert-true (typep error 'program-error)))


(define-test test-loop-always-<-collect-into
 (assert-equal
  (eval '(ab::loop for i in '(1 2 3) always (< i 4) collect i into foo
                   finally (return foo)))
  '(1 2 3)))

(define-test test-loop-always-=-collect-into
  (assert-equal
   (eval '(ab::loop for i in '(1 2 3) always (= i 4) collect i into foo
                    finally (return foo)))
   nil))

#-exclude-possible-bugs
(multiple-value-bind (result error)
    (ignore-errors
      (ab::loop for i in '(1 2 3) thereis (= i 3) collect i))
  (assert-false result)
  (assert-true (typep error 'program-error)))

#-exclude-possible-bugs
(multiple-value-bind (result error)
    (ignore-errors
      (ab::loop with i = 1 for x from 1 to 3 collect x into i))
  (assert-false result)
  (assert-true (typep error 'program-error)))

#-exclude-possible-bugs
(multiple-value-bind (result error)
    ;; this one has a plausible interpretation in terms of LET*, but
    ;; ANSI seems specifically to disallow it
    (eval '(ignore-errors
             (ab::loop with i = 1 with i = (1+ i)
                       for x from 1 to 3
                       collect (+ x i))))
  (assert-true(null result))
  (assert-true(typep error 'program-error)))

(define-test test-loop-weird-collect-vs-let 
  (assert-equal
   ;; this one just seems weird.  Nevertheless...
   (eval '(let ((it 'z)) (ab::loop for i in '(a b c d)
                     when i
                     collect it
                     and collect it)))
   '(a z b z c z d z)))

;; ab have no hash-key
#| (let ((ht (make-hash-table)))
  (setf (gethash 1 ht) 3)
  (setf (gethash 7 ht) 15)
  (assert (= (ab::loop for v fixnum being each hash-key in ht sum v) 8))
  (assert (= (ab::loop for v fixnum being each hash-value in ht sum v) 18))
  #+#.(cl:if (cl:eq sb-ext:*evaluator-mode* :compile) '(and) '(or))
  (assert-error (ab::loop for v float being each hash-value in ht sum v)
                type-error)) |#

;; arithmetic indexes can be NIL or symbols.
;; does not work in AB and seem to be very stupid
;;(assert (equal (ab::loop for nil from 0 to 2 collect nil)
;;               '(nil nil nil)))


;; does not work in AB and seem to be very stupid
;;(assert (equal (ab::loop for nil to 2 collect nil)
;;               '(nil nil nil)))

;; although allowed by the loop syntax definition in 6.2/LOOP,
;; 6.1.2.1.1 says: "The variable var is bound to the value of form1 in
;; the first iteration[...]"; since we can't bind (i j) to anything,
;; we give a program error.
;; In Lispworks, we have error in compiler instead of failure
#-lispworks 
(define-test test-loop-errs-on-destructuring-integers-in-from-clause
  (multiple-value-bind (function warnings-p failure-p)
      (compile nil
               `(lambda ()
                  (ab::loop for (i j) from 4 to 6 collect nil)))
    (assert-true failure-p)))

;; ...and another for indexes without FROM forms (these are treated
;; differently by the loop code right now
;; In Lispworks, we have error in compiler instead of failure
#-lispworks
(define-test test-loop-errs-on-destructuring-integers-in-to-clause
  (multiple-value-bind (function warnings-p failure-p)
      (compile nil
               `(lambda ()
                  (ab::loop for (i j) to 6 collect nil)))
    (assert-true failure-p)))

#|(assert
 (equal
  (let ((x 2d0))
    (ab::loop for d of-type double-float from 0d0 to 10d0 by x collect d))
  '(0d0 2d0 4d0 6d0 8d0 10d0)))
 (assert
 (equal
  (let ((x 2d0))
    (ab::loop for d of-type double-float downfrom 10d0 to 0d0 by x collect d))
  '(10d0 8d0 6d0 4d0 2d0 0d0)))|#

(define-test test-loop-handling-special-variables
  (let ((fn (handler-case
                (compile nil '(lambda ()
                                (declare (special x y))
                                (ab::loop thereis (pop x) thereis (pop y))))
              (warning (c) (error "warned: ~s" c)))))
    (let ((x (list nil nil 1))
          (y (list nil 2 nil)))
      (declare (special x y))
      (assert-equal (funcall fn) 2))))

;;; incorrect list type declaration, reported and patched by teemu
;;; kalvas: end testing is done "as if by atom" so this is supposed
;;; to work.
#+tests-breaking-in-SBCL
(assert-true (equal '(1 2) (eval '(ab::loop for (a . b) on '(1 2 . 3)  collect a))))

;;; detection of duplicate bindings, reported by bruno haible for cmucl.
#-exclude-possible-bugs
(multiple-value-bind (_ condition)
    (ignore-errors
      (macroexpand '(ab::loop with a = 0 for a downfrom 10 to 0 do (print a))))
  (declare (ignore _))
  (assert-true (typep condition 'error)))

;;; ab has no "of-type"
;;; Loop variable with a range excluding 0, reported by Andras Simon.
;;; (Used to signal an error during macroexpansion.)
; (assert (not (ab::loop with foo of-type (single-float 1.0 2.0) = 1.5 do (return))))

;; ab has no of-type
;;; 1.0.26.12 used to signal a bogus type error for this.
;; (ab::loop with x of-type (simple-vector 1) = (make-array '(1))
;;      repeat 1
;;      return x)


;; ab has no of-type
#|(define-test test-loop-bug-540186
  (let ((fun (compile nil `(lambda (x)
                             (ab::loop for i from 0 below (length x)
                                   for vec of-type vector = (aref x i)
                                   collect vec)))))
    (assert-equal '("foo" "bar")
                  (funcall fun
                           (vector "foo" "bar")))))|#

(define-test test-loop-bug-lp613871
  (multiple-value-bind (function warnings-p failure-p)
      (compile nil '(lambda () (ab::loop with nil = 1 repeat 2 collect t)))
    (assert-false warnings-p)
    (assert-false failure-p)
    (assert-equal '(t t) (funcall function)))
  #-exclude-possible-bugs
  (multiple-value-bind (function warnings-p failure-p)
      (compile nil '(lambda () (ab::loop with nil repeat 2 collect t)))
    (assert-false warnings-p)
    (assert-true failure-p)
    (assert-equal '(t t) (funcall function))))


#+lispworks (dspec:define-dspec-alias define-test (name) `(defparameter ,name))

(define-test test-loop-bug-654220-regression
  (assert-eql 32640 (eval '(ab::loop for i to 255
                                     sum i into sum #| of-type fixnum |#
                                     finally (return sum)))))

#|(define-test test-loop-of-type-character-init
  ;; The intention here is to if we initialize C to NIL before iteration start
  ;; by looking for tell-tale types such as (OR NULL CHARACTER). ...not the
  ;; most robust test ever, no.
  (let* ((fun (compile nil `(lambda (x)
                              (ab::loop for c of-type character in x
                                    collect (char-code c)))))
         (consts (ctu:find-code-constants fun :type '(or symbol list))))
    (assert (or (null consts) (equal 'character consts)))))|#

(define-test test-loop-type-of-nilled-vars
  (assert-equal (eval '(ab::loop for (a b) float = '(1.0 2.0)
                       return (list a b)))
                '(1.0 2.0))
  (assert-equal (eval '(ab::loop for (a nil b) float = '(1.0 3.0 2.0)
                                 return (list a b)))
                '(1.0 2.0)))

(define-test test-loop-misplaced-diclarations
  (multiple-value-bind (function warnings-p failure-p)
      (compile nil `(lambda ()
                      (ab::loop with (a) = '(1.0)
                            and (nil f)
                            return (list a f))))
    (assert-false warnings-p)))

(define-test test-loop-duplicate-bindings
  (assert-error
   't
   (funcall (compile nil `(lambda ()
                            (ab::loop with (a b) = '(1.0 2.0)
                                  and (c a) = '(3.0 4.0)
                                  return (list a b c))))))
  #-exclude-possible-bugs
  (assert-error
   'error
   (funcall (compile nil `(lambda ()
                            (ab::loop with a = 10
                                  with ((a) b) = '((1.0) 2.0)
                                  return (list a b))))))
  #-exclude-possible-bugs
  (assert-error
   'error
   (funcall (compile nil `(lambda ()
                            (ab::loop with (b) = '(10)
                                  with (a) = '(3)
                                  for b to 10
                                  collect a)))))
  (assert-error
   't
   (funcall (compile nil `(lambda ()
                            (ab::loop with (a) = '(3)
                                  for b to 10
                                  collect a into b))))))

(define-test test-loop-multiple-maximize
  (multiple-value-bind (function warnings-p failure-p)
      (compile nil `(lambda ()
                      (ab::loop for x to 10 maximize x minimize x)))
    (assert-false warnings-p))
  (multiple-value-bind (function warnings-p failure-p)
   (compile nil `(lambda ()
                   (ab::loop for x to 10 minimize x minimize x)))
    (assert-false warnings-p))
  (multiple-value-bind (function warnings-p failure-p)
   (compile nil `(lambda ()
                   (ab::loop for x to 10 minimize x into z minimize x into z finally (return z))))
    (assert-false warnings-p)))

(define-test test-loop-destructuring-less
  (assert-equal (eval '(ab::loop with (a b) = '() repeat 1 collect (list a b)))
                '((NIL NIL))))

(define-test test-loop-count-with-sum
  ;; fails in LW (assert-eql (ab::loop repeat 1 count 1 sum #c(1 2))
  ;;               #c(2 2))
  (assert-eql (eval '(ab::loop repeat 1 sum 1 count 1))
              2))

;; ab can not iterate over complex
#|(define-test test-loop-iterate-over-complex
  (assert
   (equal
    (ab::loop for c from #c(0 1) repeat 5 collect c)
    '(#C(0 1) #C(1 1) #C(2 1) #C(3 1) #C(4 1)))))|#

(define-test test-loop-side-effecting-start-form
  (assert-equal (eval '(let ((n 0))
                         (ab::loop for x from (incf n) to (+ n 5) collect x)))
                '(1 2 3 4 5 6)))

(define-test test-loop-summing-complex
  (assert-equal (eval '(ab::loop for i from 1 to 4
                                 sum (complex i (1+ i)) #| of-type complex |#))
                #c(10 14)))

(define-test test-loop-negative-repeat
  (assert-true (zerop (eval '(let ((z 0))
                               (ab::loop repeat 0 do (incf z))
                               z))))
  ;; ab does not support repeat with non-fixnums
  #|
  (assert-true (zerop (eval '(let ((z 0))
                               (ab::loop repeat -1.5 do (incf z))
                               z))))
  (assert-true (zerop (eval '(let ((z 0))
                         (ab::loop repeat -1.5 do (incf z))
                         z))))|#
  (assert-true (zerop (eval '(let ((z 0))
                               (ab::loop repeat -1000000 do (incf z))
                               z)))))

;; ab has no of-type
#|(define-test test-loop-of-type-character
  (assert-true (null (ab::loop with a t return a)))
  #+sb-unicode 
  (assert-true (typep (ab::loop with a of-type extended-char return a) 'extended-char))
  (assert-true (typep (ab::loop with a of-type character return a) 'character))
  (assert-true (typep (ab::loop with a of-type base-char return a) 'base-char))
  (assert-true (typep (ab::loop with a of-type standard-char return a) 'standard-char)))|#

;; ab has no of-type
#|(define-test test-loop-empty-type
  (assert-signal
   (compile nil `(lambda ()
                   (ab::loop with a of-type (and fixnum string) return a)))
   warning)
  (assert-signal
   (compile nil `(lambda ()
                   (ab::loop for i to 10 sum i of-type (and fixnum string))))
   warning)) |#

;; this is related to SBCL specific type inference, we're unlikely to need it
#|(define-test test-loop-loop-repeat-const
  ;; without explicit constant-folding in LOOP-DO-REPEAT, the type of this loop's
  ;; counter is INTEGER which unfortunately resulted in generic math throughout,
  ;; since a FOR/THEN clause interacts badly with type inference.
  ;; [if there is no FOR/THEN, the compiler understands the code better,
  ;; and is able to infer a lower bound on decrementing from (+ 1 5)]
  (assert-no-signal
   (compile nil '(lambda ()
                   (declare (optimize speed))
                   (ab::loop repeat (+ 1 5) for baz = 'this then 'that
                         do (print baz)))))) |#

;; ab has no of-type
#|(define-test test-loop-loop-default-init-type
  (assert-no-signal (compile nil
                             '(lambda (list)
                               (declare (optimize speed))
                               (ab::loop for a of-type (simple-vector 4) in list
                                     collect (aref a 2))))
                    sb-ext:compiler-note))|#

(define-test test-loop-with-destructuring
  (assert-true (= (eval '(ab::loop with ((a . b)) = '((1 . 2))
                                   return (+ a b)))
                  3))
  (assert-true (= (eval '(ab::loop with (((a) b)) = '(((1) 3))
                                   return (+ a b)))
             4)))



;;;; Test cases from CLHS

(define-test test-loop-6.1.2.1.1-for-from-by-to-collect
  (assert-equal
   (eval '(let ((x 1)) (ab::loop for i from x by (incf x) to 10 collect i)))
   '(1 3 5 7 9)))

;; didn't work in ab
#|(define-test test-loop-6.1.2.1.1-for-by-from-to-collect
  (assert-equal
   (eval '(let ((x 1)) (ab::loop for i by (incf x) from x to 10 collect i)))
   '(2 4 6 8 10))) |# 
   
(define-test test-loop-6.1.2.1.1.1-print-some-numbers
  (assert-equal
   '(1 2 3)
   (eval '(let (result)
            (ab::loop for i from 1 to 3 do (push i result))
            (reverse result)))))

(define-test test-loop-6.1.2.1.1.1-print-every-third-number
  (assert-equal
   '(10 7 4 1)
   (eval '(let (result)
            (ab::loop for i from 10 downto 1 by 3
                      do (push i result))
            (reverse result)))))

(define-test test-loop-6.1.2.1.1.1-for-i-below-3-push-i
  (assert-equal
   '(0 1 2)
   (eval
    '(let (result)
       (ab::loop for i below 3
                 do (push i result))
       (reverse result)))))

(define-test test-loop-6.1.2.1.2.1-for-i-in-push-i
  (assert-equal
   '(1 2 3)
   (eval
    '(let (result)
       (ab::loop for i in '(1 2 3)
                 do (push i result))
       (reverse result)))))

;; not for in by not supported by ab
#|(define-test test-loop-6.1.2.1.2.1-for-i-in-by-cddr-push-i-and-keywords
  (assert-equal
   '(1 3 5)
   (eval
    '(let (result)
       (ab::loop :for in '(1 2 3 4 5)
                 :by #'cddr
                 :do (push i result))
       (reverse result)))
   ))|#




(define-test test-loop-6.1.2.1.2.1-for-destructuring-unless-sum
  (assert-equal
   4
   (eval
    ;; of-type is not supported so we omit it
    '(ab::loop for (item . x) in '((A . 1) (B . 2) (C . 3))
               unless (eq item 'B) sum x))))



(define-test test-loop-6.1.2.1.3.1-for-sublist-on-collect
  (assert-equal
   '((a b c d) (b c d) (c d) (d))
   (eval '(ab::loop for sublist on '(a b c d)
                    collect sublist))))


(define-test test-loop-6.1.2.1.4.1-for-as-equals-then
  (assert-equal
   '(1 11 21 31 41)
   (eval '(ab::loop for item = 1 then (+ item 10)
                    for iteration from 1 to 5
                    collect item))))

;; for across is not supported by ab
#| (define-test test-loop-6.1.2.1.5.1-for-as-across) 
|#
  

;; We do hash initialization when the test is loading to avoid fake coverage
;; RETURN-HERE test define-loop-path hash-value
(ab::def-hash-table test-loop-6.1.2.1.6-example-hash-table)

(defvar test-loop-6.1.2.1.6-example-hash-table-instance (make-test-loop-6.1.2.1.6-example-hash-table))

(defun fill-test-loop-6.1.2.1.6-example-hash-table-instance ()
  (SET-TEST-LOOP-6.1.2.1.6-EXAMPLE-HASH-TABLE-HASH-VALUE 'a test-loop-6.1.2.1.6-example-hash-table-instance 'b)
  (SET-TEST-LOOP-6.1.2.1.6-EXAMPLE-HASH-TABLE-HASH-VALUE 'c test-loop-6.1.2.1.6-example-hash-table-instance 'd))

(fill-test-loop-6.1.2.1.6-example-hash-table-instance)

(define-test test-loop-6.1.2.1.6-for-as-hash-value.impure
  (assert-true
   (set-equal
    '(b d)
    ;; clause defined in ab::expand-hash-value-loop-iterator
    (eval '(ab::loop for v being each hash-value
                     ab::of test-loop-6.1.2.1.6-example-hash-table-instance
                     collect v)))))

;; 6.1.2.1.7 - for-as-package does not work in ab
;; (ab::loop for s being each symbol of :tests collect s)

(define-test test-loop-6.1.2.2-sequential-binding
  (assert-equal
   '(1 3 6)
   (eval '(ab::loop with a = 1 
                    with b = (+ a 2) 
                    with c = (+ b 3)
                    return (list a b c)))))


(define-test test-loop-6.1.2.2.1-parallel-binding
  (assert-equal
   '(1 7 13)
   (eval '(let ((a 5)(b 10))
            (ab::loop with a = 1 
                      and  b = (+ a 2) 
                      and  c = (+ b 3)
                      return (list a b c))))))

(define-test test-loop-6.1.4.1-repeat-3-times
  (assert-equal
   (list "What I say three times is true"
         "What I say three times is true"
         "What I say three times is true")
   (eval
    '(let (result)
       (ab::loop repeat 3
                 do (push "What I say three times is true" result))
       (reverse result)))))


(define-test test-loop-6.1.4.1-repeat-minus-15-times
  (assert-equal
   nil
   (eval
    '(let (result)
       (ab::loop repeat -15
                 do (push "What you see is what you expect" result))
       (reverse result)))))


(define-test test-loop-6.1.4.2-always-i-less-then-11
  (assert-true
   (eval
    '(ab::loop for i from 0 to 10 always (< i 11)))))

(define-test test-loop-6.1.4.2-always-i-less-than-10-expect-false
  (assert-false
   (eval
    '(ab::loop for i from 0 to 10 always (< i 10)))))


(define-test test-loop-6.1.4.2-always-i-never-greater-then-11
  (assert-true
   (eval
    '(ab::loop for i from 0 to 10 never (> i 11)))))
   

(define-test test-loop-6.1.4.2-always-i-never-greater-then-9-expect-false
  (assert-false
   (eval
    '(ab::loop for i from 0 to 10 never (> i 9)))))


(define-test test-loop-6.1.4.2-for-from-and-thereis
  (assert-equal
   11
   (eval
    '(ab::loop for i from 0 thereis (when (> i 10) i)))))


(define-test test-loop-6.1.4.2-for-always-fails-expect-finally-not-executed
  (assert-eq
   nil
   (eval
    '(ab::loop for i from 0 to 10
               always (< i 9)
               finally (assert-false "you should not see this")))))

(define-test test-loop-6.1.4.2-never-clause-fails-expect-finally-not-executed
  (assert-eq
   nil
   (eval
    '(ab::loop never t
               finally (assert-false "you should not see this")))))

(define-test test-loop-6.1.4.2-thereis-clause-succeeds-expect-finally-not-executed
  (assert-equal
   "Here is my value"
   (eval
    '(ab::loop thereis "Here is my value"
       finally (assert-false "you should not see this")))))
 
(define-test test-loop-6.1.4.2-for-terminates-the-loop-expect-finally-is-executed
  (assert-equal
   (values nil (list 'got-here))
   (eval
    '(let* ((result nil)
            (loop-result
             (ab::loop for i from 1 to 10
                       thereis (> i 11)
                       finally (push 'got-here result))))
       (values loop-result result)))))

;; Replace fermat theorem with finding x^2+y^3=z^2 and check it returns t
(define-test test-loop-6.1.4.2-pseudo-fermat
  (assert-eq
   t
   (eval
    '(ab::loop for z upfrom 2
               thereis
               (ab::loop for n
                         upfrom 2 ; replace 3 with 2 to terminate
                         below (ceiling (log z 2)) ; had to add ceiling as ab fails 
                         thereis
                         (ab::loop for x below z
                                   thereis
                                   (ab::loop for y below z
                                             thereis (= (+ (expt x n) (expt y n))
                                                        (expt z n)))))))))

(define-test test-loop-6.1.4.3-while-hungry-p
  (assert-equal
   '(a b c)
   (eval
    '(let ((data '(a b c))
           (result nil))
       (ab::loop while (identity data)
                 do (push (pop data) result))
       (nreverse result)))))

(define-test test-loop-6.1.4.3-until-not-hungry-p
  (assert-equal
   '(a b c)
   (eval
    '(let ((data '(a b c))
           (result nil))
       (ab::loop until (not (identity data))
                 do (push (pop data) result))
       (nreverse result)))))


(define-test test-loop-6.1.4.3-collect-the-length-and-the-items-of-stack
  (assert-equal
   '(6 a b c d e f)
   (eval
    '(let ((stack '(a b c d e f)))
       (ab::loop for item = (length stack) then (pop stack)
                 collect item
                 while stack)))))


(define-test test-loop-6.1.4.3-use-whild-to-terminate-a-loop
  (assert-equal
   '(3 5)
   (eval
    '(ab::loop for i fixnum from 3
               when (oddp i) collect i
               while (< i 5)))))


(define-test test-loop-6.1.5.1-do-multiple-forms
  (assert-equal
   '(1 1 2 4 3 9)
   (eval
    '(let (result)
       (ab::loop for i from 1 to 3
                 do (push i result)
                 (push (* i i) result))
       (nreverse result)))))

(define-test test-loop-6.1.6.1-when-not-numberp-return
  (assert-equal
   'a
   (eval
    '(ab::loop for item in '(1 2 3 a 4 5)
               when (not (numberp item))
               return item))))


(define-test test-loop-6.1.6.1-when-not-numberp-do-return
  (assert-equal
   'a
   (eval
    '(ab::loop for item in '(1 2 3 a 4 5)
               when (not (numberp item))
               do (return item)))))



(define-test test-loop-6.1.6.1-initially-for-and-when-combined
  (assert-equal
   2
   (eval
    '(let ((buffer "\"a\" \"b\""))
       (ab::loop initially (unless (char= (char buffer 0) #\")
                             (ab::loop-finish))
                 for i from 1 below (length (the string buffer))
                 when (char= (char buffer i) #\")
                 return i)))))


(define-test test-loop-6.1.6.1-return-collected-value-from-when-with-finally
  (assert-equal
   (values '(6 7 8 9 10) (list 'got-here))
   (eval
    '(let* ((output nil)
            (loop-result
             (ab::loop for i from 1 to 10
                       when (> i 5)
                       collect i
                       finally (push 'got-here output))))
       (values loop-result (nreverse output))))))

(define-test test-loop-6.1.6.1-return-number-count-and-number-list
  (assert-equal
   (values 5 (list 6 7 8 9 10))
   (eval
    '(ab::loop for i from 1 to 10
               when (> i 5)
               collect i into number-list
               and count i into number-count
               finally (return (values number-count number-list))))))

(define-test test-loop-6.1.7.1.1-named-clause
  (assert-equal
   (values 'done '(1))
   (eval
    '(let* ((output)
            (loop-result (ab::loop named max
                                   for i from 1 to 10
                                   do (push i output)
                                   do (return-from max 'done))))
       (values loop-result (nreverse output))))))


(define-test test-loop-6.1.8-x-stepped-before-y-stepped
  (assert-equal
   '((1 NIL) (2 2) (3 3) (4 4) (5 5) (6 6) (7 7) (8 8) (9 9) (10 10))
   (eval
    '(ab::loop for x from 1 to 10 
               for y = nil then x 
               collect (list x y)))))



(define-test test-loop-6.1.8-parallel-stepping
  (assert-equal
   '((1 NIL) (2 1) (3 2) (4 3) (5 4) (6 5) (7 6) (8 7) (9 8) (10 9))
   (eval '(ab::loop for x from 1 to 10 
                    and y = nil then x 
                    collect (list x y)))))

(define-test test-loop-6.1.8.1-group-conditional-clauses
  (assert-equal
   (values
    '(1 2345 323 235)
    '(324 2 4 252)
    '(1 terpri 2345 terpri 323 terpri 235 terpri)
    )
   (eval
    '(let (output)
       (multiple-value-bind (r1 r2)
         (ab::loop for i in '(1 324 2345 323 2 4 235 252)
                   when (oddp i)
                   do (push i output)
                   and collect i into odd-numbers
                   and do (push 'terpri output)
                   else                              ; I is even.
                   collect i into even-numbers
                   finally
                   (return (values odd-numbers even-numbers)))
         (values r1 r2 (nreverse output)))))))


(define-test test-loop-6.1.8.1-anaphoric-collect
  (assert-equal
   '(4 5 6)
   (eval
    '(ab::loop for i in '(1 2 3 4 5 6)
               when (and (> i 3) i)
               collect it))))

(define-test test-loop-6.1.8.1-anaphoric-return
  (assert-equal
   4
   (eval
    '(ab::loop for i in '(1 2 3 4 5 6)
               when (and (> i 3) i)
               return it))))


(define-test test-loop-6.1.8.1-nest-conditional-clauses
  (assert-equal
   (values '(3.0 9.8) '(0 4 5) '(APPLE ORANGE BANANA))
   (eval
    '(let ((list '(0 3.0 apple 4 5 9.8 orange banana)))
       (ab::loop for i in list
                 when (numberp i)
                 when (floatp i)
                 collect i into float-numbers
                 else                                  ; Not (floatp i)
                 collect i into other-numbers
                 else                                  ; Not (numberp i)
                 when (symbolp i) 
                 collect i into symbol-list
                 else                                  ; Not (symbolp i)
                 do (assert-false (format nil "found a funny value in list ~S, value ~S~%" list i))
                 finally (return (values float-numbers other-numbers symbol-list)))))))


;; end is not supported in ab
#|(define-test test-loop-6.1.8.1-without-the-end-expression-the-last-end-would-apply-to-inner-if
  (assert-equal
   (values nil '(0 a b c 1 2 a c 3))
   (eval
    '(let* ((output nil)
            (loop-result
             (ab::loop for x from 0 to 3 
                       do (push x output)
                       if (zerop (mod x 2))
                       do (push 'a output)
                       and if (zerop (floor x 2))
                       do (push 'b output)
                       ab::end
                       and do (push 'c output))))
       (values loop-result (nreverse output))))))|#

;;;; some additional tests to improve coverage


(define-test test-loop-loop-named-by-non-symbol-expect-error
  (assert-error
   'error
   (macroexpand-1 '(ab::loop named "nonsense" return 4))))


(define-test test-loop-loop-named-by-occurs-too-late-expect-error
  (assert-error
   'error
   (macroexpand-1 '(ab::loop for i from 1 to 4 named too-late))))


(define-test test-loop-duplicated-named-by-expect-error
  (assert-error
   'error
   (macroexpand-1 '(ab::loop named one named two))))

(define-test test-loop-variable-named-by-non-symbol-expect-error
  (assert-error
   'error
   (eval '(ab::loop with "a" = 5))))


;; Test some macroexpansions
(define-test test-loop-invoke-simple-error-no-datum
  (assert-error
   'error
   (eval '(ab::loop-simple-error "Test loop simple error"))))

(define-test test-loop-invoke-simple-with-no-datum
  (assert-error
   'error
   (eval '(ab::loop-simple-error "test loop simple error" 1))))

(define-test test-loop-copylist*
  (assert-equal
   (values '(copy-list a) t)
   (macroexpand-1 '(ab::loop-copylist* a))))

(define-test test-loop-macroexpand-loop-warn-no-datum
  (assert-equal (values '(warn '"LOOP: Loop warning") t)
                (macroexpand-1 '(ab::loop-warn "Loop warning"))))

(define-test test-loop-macroexpand-loop-warn-with-datum
  (assert-equal (values '(warn "LOOP: Loop warning -- ~{~S~^ ~}" 123) t)
                (macroexpand-1 '(ab::loop-warn "Loop warning" 123))))


(define-test test-loop-macroexpand-loop-pop-source
  (assert-equal (values '(pop ab::loop-source-code) t)
                (macroexpand-1 '(ab::loop-pop-source))))


(define-test test-loop-loop-gentemp
  (assert-equal
   (values (string '#:AB-LOOPVAR-2015)
           2016)
   (eval
    '(let ((ab::loop-gentemp-counter 2015))
       (values (string (ab::loop-gentemp))
               ab::loop-gentemp-counter)))))

(define-test test-loop-loop-gentemp-with-prefix
  (assert-equal
   (values (string '#:AB-MY-PREFIX-2015)
           2016)
   (eval
    '(let ((ab::loop-gentemp-counter 2015))
       (values (string (ab::loop-gentemp 'my-prefix-))
               ab::loop-gentemp-counter)))))

(define-test test-loop-desetq-car-optimization-atom-non-atom-val
  (assert-equal
   '(a b)
   (eval
    '(ab::loop
      with d = '(a b)
      for (i j) = d
      return (list i j)))))

(define-test test-loop-desetq-car-optimization-atom-cadr-val
  (assert-equal
   '(a b)
   (eval
    '(ab::loop
      with d = '((a b))
      for (i j) = (car d)
      return (list i j)))))

(define-test test-loop-desetq-car-optimization-non-atom-cadr-val
  (assert-equal
   '(a b)
   (eval
    '(ab::loop
      with d = '(((a b)))
      for (i j) = (car (car d))
      return (list i j)))))


(define-test test-loop-return-from-named-loop
  "Macroexpansion of return from named block is treated in special way"
  (assert-equal 'a
		(ab::loop named b return 'a)))

(define-test test-loop-loop-tassoc
  "Never reached from other tests, so cover just this macro"
  (assert-equal '(c d)
                (ab::loop-tassoc 'c '((a b) (c d) (e f)))))

(define-test test-loop-macroexpand-loop-tassoc-non-symbol
  "Never reached from other tests, so cover just this macro. Make sure that non-symbols can't be found even if they are in alist"
   (let ((my-cons (cons nil nil)))
     (assert-false
       (ab::loop-tassoc my-cons `((,my-cons b))))))

(define-test test-loop-loop-tmember
  "Never reached from other tests, so cover just this macro"
  (assert-equal '(c d)
		(ab::loop-tmember 'c '(a c d))))

(define-test test-loop-macroexpand-loop-tmember-non-symbol
  "Never reached from other tests, so cover just this macro. Make sure that non-symbols can't be found even if they are in alist"
   (let ((my-cons (cons nil nil)))
     (assert-false
       (ab::loop-tmember my-cons `(a ,my-cons b)))))

(define-test test-loop-loop-end-testify-no-forms
  (assert-equal nil (eval '(ab::loop-end-testify nil))))

(define-test test-loop-loop-end-testify-one-form
  (assert-equal '(when a (go ab::end-loop)) (eval '(ab::loop-end-testify '(a)))))

(define-test test-loop-loop-end-testify-many-forms
  "This variant never happened in any of loop tests"
  (assert-equal '(when (ab::or c b a) (go ab::end-loop))
                (eval '(ab::loop-end-testify (list 'a 'b 'c)))))


(define-test test-loop-implicit-progn-in-for-initializer-expect-warning
  (let ((form '(ab::loop with i = 1
                         for m = (incf i) (incf i)
                         collect i
                         collect m
                         until (> i 7))))
    (multiple-value-bind (function warnings-p failure-p)
        (eval `(compile nil '(lambda () ,form)))
      (declare (ignore function))
      (assert-true warnings-p)
      (assert-true failure-p))
    (assert-equal
     '(3 3 5 5 7 7 9 9)
     (eval form))))


(define-test test-loop-implicit-progn-in-while-expect-warning
  (let ((form '(let ((i 5))
                 (ab::loop while (incf i) (incf i)
                           collect i
                           until (> i 9)))))
    (multiple-value-bind (function warnings-p failure-p)
        (eval `(compile nil '(lambda () ,form)))
      (declare (ignore function))
      (assert-true warnings-p)
      (assert-true failure-p))
    (assert-equal
     '(7 9 11)
     (eval form))))


(defun unintern-symbols-whose-names-contain-substring (substring package-designator)
  "Substring is case-insensitive"
  (do-symbols (sym package-designator)
    (when (search substring (string sym) :test 'char-equal)
      (unintern sym package-designator)
      (assert (not (find-symbol (string sym) package-designator))))))
  

(define-test test-loop-define-loop-path-with-nothing
  "This test is impure. Define a pointless loop path and fix macroexpansion"
  ;; setup 
  (dolist (p '(:ab :tests))
    (unintern-symbols-whose-names-contain-substring
     "test-loop-dummy-loop-path" p))
  ;; act
  (eval `(ab::define-loop-path ,(read-from-string "test-loop-dummy-loop-path")
                               ,(read-from-string "expand-test-loop-dummy-loop-path") ()))
  (eval `(ab::defun-for-macro ,(read-from-string "expand-test-loop-dummy-loop-path")
             (method-name
              iter-var iter-var-data-type prep-phrases inclusive?
              allowed-preps method-specific-data)
           (declare (ignore method-name allowed-preps method-specific-data
                            iter-var iter-var-data-type prep-phrases inclusive?))
           ;; Return a list of the six path elements.
           `((tldlp-init-bindings-1)
             (tldlp-prologue-forms-1)
             (tldlp-pre-step-tests-1)
             (tldlp-steppings-1)
             (tldlp-post-step-tests-1)
             (tldlp-post-step-settings-1))))
  ;; assert
  (assert-equal (values '(ab::let ((tldlp-init-bindings-1 nil))
                           (block nil
                             (ab::let nil
                               (ab::loop-tagbody
                                 tldlp-prologue-forms-1
                                 ab::next-loop
                                 (when (tldlp-pre-step-tests-1) (go ab::end-loop))
                                 (setq tldlp-steppings-1 nil)
                                 (when (tldlp-post-step-tests-1) (go ab::end-loop))
                                 (setq tldlp-post-step-settings-1 nil)
                                 (go ab::next-loop)
                                 ab::end-loop))))
                        t)
                (macroexpand-1 '(ab::loop for x being test-loop-dummy-loop-path))))


(define-test test-loop-define-loop-path-imitating-for
  "This test is impure. Imitate for x in form"
  ;; setup 
  (dolist (p '(:ab :tests))
    (unintern-symbols-whose-names-contain-substring
     "test-loop-my-for-loop-path" p))
  ;; act
  (eval `(ab::define-loop-path ,(read-from-string "test-loop-my-for-loop-path")
                               ,(read-from-string "expand-test-loop-my-for-loop-path") (in-list)))
  (eval `(ab::defun-for-macro ,(read-from-string "expand-test-loop-my-for-loop-path")
             (method-name
              iter-var iter-var-data-type prep-phrases inclusive?
              allowed-preps method-specific-data)
           ;; Should return a list of the six path elements.
           ;; init-bindings
           ;; prologue-forms
           ;; pre-step-test
           ;; steppings
           ;; post-step-test
           ;; post-step-settings
           (let* ((prep-phrase (car prep-phrases))
                  (initial-value (second prep-phrase)))
           `(; these are bindings for let around loop body
             ((dirty-cdr-variable ,initial-value)
              (dummy1 (push 'init-bindings output-stream-imitator)) ; should be ignored - don't know how
              )

             ;; executed before first iteration only
             ((push 'prologue output-stream-imitator))

             ;; single form, execute just after start the iteration to test for termination
             ;; if returns true values, loop is terminated before the current iteration
             (progn (push 'pre-step-test output-stream-imitator)
               (not dirty-cdr-variable))
             
             ;; what to do inside iteration.
             ;; list of places and a form which would produce a list of rhs values to assign to them
             ((output-stream-imitator
               ,iter-var)
              (list
               (cons 'steppings output-stream-imitator)
               (pop dirty-cdr-variable)))

             ;; a form invoked after iteration. When it returns truth, loop is terminated
             (progn (push 'post-step-test output-stream-imitator)
               nil)

             ;; setq invoked after test after iteration. We supply a list of places
             ;; and the form which yields a list to assign to those forms
             ((output-stream-imitator)
              (list
               (cons 'post-step-settings output-stream-imitator)))))))
  (assert-equal 
   (values
    '(a b c)
    '(init-bindings
      initially
      prologue
      pre-step-test
      steppings
      post-step-test
      post-step-settings
      pre-step-test
      steppings
      post-step-test
      post-step-settings
      pre-step-test
      steppings
      post-step-test
      post-step-settings
      pre-step-test
      finally))
   (eval
    '(let (output-stream-imitator)
       (values
        (ab::loop
         initially (push 'initially output-stream-imitator)
         for x being test-loop-my-for-loop-path in-list '(a b c) collect x
         finally (push 'finally output-stream-imitator)
         )
        (nreverse output-stream-imitator))))))


(define-test test-loop-loop-translate-1-pops-loop
  (assert-equal
   (ab::loop-translate-1 '(while i))
   (ab::loop-translate-1 '(ab::loop while i))))
                  
(define-test test-loop-hanging-conditional-expect-error
  (assert-error
   'error
   (eval '(macroexpand-1 '(ab::loop when t)))))

(define-test test-loop-unknown-keyword-expect-error
  (assert-error
   'error
   (eval '(macroexpand-1 '(ab::loop abrakadabra)))))

#-exclude-possible-bugs
(define-test test-loop-junky-tag-in-implicit-do
  "When car of source is not a symbol, implicit do is created. This test fails normally as it is a bug report"
  (assert-false 
   (equal
    '(block nil (ab::let nil (ab::loop-tagbody ab::next-loop 40 (go ab::next-loop) ab::end-loop)))
    (macroexpand-1 '(ab::loop 40)))))

#-exclude-possible-bugs
(define-test test-loop-junky-tag
  (assert-false
   (equal
    3
    (eval '(let ((i 0))
             (ab::loop
              while (< i 3)
              do (incf i)
              (go 45)
              (error "i wont get there")
              45 finally (return i)))))))

(define-test test-loop-missing-code-after-end-expect-error
  "secondary clause misplaced at top level"
  (assert-error
   'error
   (macroexpand-1 '(ab::loop collect 1 and))))



(define-test test-loop--with-no-initializer--expect-coverage-increase
  "Covers this line: 
   (loop-tassoc equals loop-iteration-keyword-alist))
   in loop-do-with
   "
  (assert-equal
   (eval '(ab::loop with a for i = a return i))
   nil))

(define-test test-loop--for-on-by--expect-coverage-increase
  "Covers this line:
   (and (car before) (push (car before) loop-before-loop))
   in loop-optimize-duplicated-code-etc
  "
  (assert-equal
   '((a b)(c d))
   (eval
    '(ab::loop for (property value) on '(a b c d) by 'cddr
               collect (list property value)))))

(define-test test-loop--for-in-list-collect-using-cons--expect-the-same-as-collect
  (assert-equal
   (ab::loop for i in '(1 2 3) collect i)
   (eval '(ab::loop for i in '(1 2 3) collect i using cons))))


(define-test test-loop--for-from-to-collect-using-cons--expect-the-same-as-collect
  (assert-equal
   (ab::loop for i from 1 to 3 collect i)
   (eval '(ab::loop for i from 1 to 3 collect i using cons))))


;;AB 67 > (defun snoc (x y) (cons y x))
;;SNOC
;;
;;AB 68 > (loop for x in '(a b) collect x using snoc)
;;(NIL NIL . B)


;;;; non-covered code report
;;  ab::loop-gentemp - code under #+translator is never tested
;;  ab::loop-make-desetq - loop-user-system-destructuring? is always null
;;  ab::loop-optimize-duplicated-code-etc - loop-duplicated-code is always null. Unable to reach (push b group)
;;  ab::loop-output-group - unable to reach
;;  ab::loop-translate-1: 
;;   (if (symbolp (setq keyword (car loop-source-code)))
;;       (loop-pop-source) - this is a test-loop-junky-tag-in-implicit-do bug
;;   loop-wrappers (cdr l) - unable to reach
;;  (setq keyword 'do) - reached when #-exclude-possible-bugs
;; Further work on improving coverage and also on preparing uncovered code report was suspended 
;; due to the polite request by Architect

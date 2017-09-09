(in-package "TESTS")

(define-test test-make-permanent-integer
  "Called from ab::read-kb. I do not understand if that bignums are ever reclaimed in LW - budden"
  (map-interesting-integers
   (lambda (i)
     (assert-eql i (ab::make-permanent-integer i)))))

; make-permanent-list. Is called from ab::read-kb. It would worth to verify dynamically if it is not really cdr coded
; make-mutable-list. Called from ab::body-of-continue-building-resumable-object , but don't know if it used really. Nothing to test 

(define-test test-permanent-list
  "Seem to be called from two places. Test is trivial. It does not cover where the list is located indeed - there is no portable way to test for it"
  (assert-equalp '(1 a "asdf") (ab::permanent-list 1 'a "asdf")))

(define-test test-make-permanent-list-macro
  (let ((list (ab::make-permanent-list-macro 2)))
    (assert-true (typep list 'cons))
    (assert-eql (length list) 2)
    ))


#-exclude-possible-bugs
(define-test test-static-allocation-of-permanent-conses-and-integers
  "All and every of these tests seem to always fail in LW. We combine them so that spend minimal time waiting for (hcl:clean-down) to complete"
  (let ((objects
         (list
          (ab::make-permanent-integer (+ most-positive-fixnum 1))
          (ab::make-permanent-list 4)
          (ab::make-permanent-list-macro 3)
          (ab::permanent-list 1 'a "asdf")
          ; (vector 1 2 3) this would pass, but this is not what we were asked for
          )))
    (assert-objects-not-moveable-by-gc objects)))

(define-test test-with-temporary-bignum-creation
  (map-interesting-integers
   (lambda (i)
     (lisp-unit::assert-equal i (ab::with-temporary-bignum-creation (progn i))))))

;; Some variables are defined into ALIEN pointers in SBCL, this is fixed by new
;; foreign code for SBCL. -- Glority, 2010/08/09

(define-test test-type-of-array-1
  (lisp-unit::assert-true (typep ab::partition-float-union 'array)))

(define-test test-type-of-array-2
  (lisp-unit::assert-true (typep ab::gensym-time-array 'array)))


(define-test test-def-global-property-name
  "Test that property is setfable, getfable, and is distinct for different symbols"
  (unintern (intern "TEST-GPN" :AB) :AB)
  (eval
   (read-from-string "(ab::def-global-property-name ab::test-gpn)"))
  (eval
   (read-from-string "(setf (ab::test-gpn 'cons) 123)"))
  (eval
   (read-from-string "(setf (ab::test-gpn 'list) 456)"))
  (assert-eql
   (eval (read-from-string "(ab::test-gpn 'cons)")) 123)
  (assert-eql
   (eval (read-from-string "(ab::test-gpn 'list)")) 456)   
  (eval
   (read-from-string "(setf (ab::test-gpn 'cons) 789)"))
  (assert-eql
   (eval (read-from-string "(ab::test-gpn 'cons)")) 789)
  )
 

;; TESTERS-COMMENT map-over-global-property will map only symbols in G2 package

;; mutate-global-property is almost covered by test-def-global-property-name, but there is still work to do

(defun ab-unintern-and-intern (string)
  (unintern (intern string :ab) :ab)
  (assert (not (find-symbol string :ab))) ; just check that there was no inherited symbol
  (intern string :ab))  

(defun prepare-some-properties-and-symbols ()
  (let (properties symbols (rank 25))
    (dotimes (i rank)

      (let ((property
             (ab-unintern-and-intern (format nil "TMGPITLR-PROP-~A" i))))
        (push property properties)
        (eval `(ab::def-global-property-name ,property)))

      (push (ab-unintern-and-intern (format nil "TMGPITLR-SYM-~A" i)) symbols)
      )
    (values (nreverse properties) (nreverse symbols))))
  

(define-test test-mutate-global-property-in-the-long-run-1
  "Test branches where there are more properties and values"
  (multiple-value-bind (properties symbols)
      (prepare-some-properties-and-symbols)
    (let ((i 0) log-w log-r)
      (dolist (s symbols)
        (dolist (p properties)
          (ab::mutate-global-property s i p)
          (push i log-w)
          (incf i)))
    
      (dolist (s symbols)
        (dolist (p properties)
          (push (eval `(,p ',s)) log-r)))

      (assert-equal log-w log-r))))

          
(define-test test-mutate-global-property-in-the-long-run-2
  "The same, but in the other order of symbols vs properties"
  (multiple-value-bind (properties symbols)
      (prepare-some-properties-and-symbols)
    (let ((i 0) log-w log-r)
      (dolist (p properties)
        (dolist (s symbols)
          (ab::mutate-global-property s i p)
          (push i log-w)
          (incf i)))
    
      (dolist (p properties)
        (dolist (s symbols)
          (push (eval `(,p ',s)) log-r)))

      (assert-equal log-w log-r))))

;; Skipping memory and friends . 
;; it was found that variables required are bound in the scheduler-worker-function
;; So it looks like we have to start G2 to use that in fact. 

(define-test test-pm-elt
  (assert-eq (ab::pm-elt '(a b c) 2) 'c)
  (assert-eq (ab::pm-elt #(a b c) 2) 'c)
  (assert-eql (ab::pm-elt 'a 2) -1234567)
  (assert-eql (ab::pm-elt 2 2) -1234567)
  )

(define-test test-pm-nthcdr
  (let ((list (list 'a 'b 'c)))
    (dotimes (i 3)
      (assert-eq (ab::pm-nthcdr list i) (nthcdr i list))))
  (assert-eql (ab::pm-nthcdr 4 4) -1234567))
  
;(define-test pm-type-of
;  (dolist (value-result '((nil . ab::null)
;                          (
(define-test pm-type-of
 (assert-eq (ab::pm-type-of nil) 'null)
 (assert-equal (ab::pm-type-of 'ab::pm-type-of) '(member ab::pm-type-of))
 (assert-equal (ab::pm-type-of "asdf") '(member "asdf"))
 (assert-equal (ab::pm-type-of 123) '(member 123))
 (assert-equal (ab::pm-type-of '(a b)) 'cons)
 (assert-equal (ab::pm-type-of #(1 2 3)) '(array t 3)))


(define-test pm-composite-type-of
  (assert-equal (ab::pm-composite-type-of nil) 'null)
  (assert-equal (ab::pm-composite-type-of 'ab::pm-composite-type-of)
                '(member ab::pm-composite-type-of))
  (assert-equal (ab::pm-composite-type-of "asdf")
                '(ab::composite-object (member "asdf") nil nil nil nil))
  (assert-equal (ab::pm-composite-type-of 123) '(member 123))
  (assert-equal (ab::pm-composite-type-of '(a b))
                '(ab::composite-object cons (member a) (member b)))
  (assert-equal (ab::pm-composite-type-of #(1 2 3))
                '(ab::composite-object (array t 3) (member 1) (member 2) (member 3))))


#-exclude-possible-bugs
(define-test pm-print-wide-string
   (let ((t-if-printed-successfully
          (ignore-errors
            (with-output-to-string (*standard-output*) (pm-print-wide-string #w"asdf"))
            t)))
     (assert-true t-if-printed-successfully)))
  
;; I skip the rest of PM printing as pm-print-wide-string is broken in LW
;; and as the entire thing said to be designed for use from GDB, not from Lisp. 

;; Skip def-kb-specific-variable as it requires that modules exist. I know no way (yet) to load modules from lisp





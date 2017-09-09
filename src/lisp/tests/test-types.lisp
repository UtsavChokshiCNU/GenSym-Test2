(in-package :tests)

(define-test test-type-specification-p
  (assert-true (ab::type-specification-type-p 'RGB85A5FF '(ab::named ab::color-or-metacolor)))
  (assert-true (ab::type-specification-type-p 'ab::foreground'(ab::named ab::color-or-metacolor))) 
  (assert-true (ab::type-specification-type-p 'ab::red '(ab::named ab::color-or-metacolor)))
  (assert-true (ab::type-specification-type-p--with-explanation 'RGB85A5FF '(ab::named ab::color-or-metacolor)))
  (assert-true (ab::type-specification-type-p--with-explanation 'ab::foreground'(ab::named ab::color-or-metacolor))) 
  (assert-true (ab::type-specification-type-p--with-explanation 'ab::red '(ab::named ab::color-or-metacolor))))


(defun evaluation-structure--alloc-and-reclaim--aux-fn (run-assertions inline-p)
  (let* ((frame1 (ab::make-frame 'ab::block))
         (frame2 (ab::make-frame 'ab::block))
         (data (ab::eval-list 'n1 'v1 'n2 'v2 'n3 frame1 'n4 frame2))
         (data-copy data)
         (structure
          (if inline-p
              (ab::allocate-evaluation-structure-inline
                'n1 'v1 'n2 'v2 'n3 frame1 'n4 frame2)
              (ab::allocate-evaluation-structure
               (ab::copy-list-using-eval-conses data))))
         each-evaluation-structure-pair-value-mismatches)
    (ab::delete-frame frame2)
    (ab::loop
     ab::for (n . v) ab::being ab::each ab::evaluation-structure-pair
     ab::of structure
     ab::do (unless (eq n (pop data-copy))
              (push "name mismatch for" each-evaluation-structure-pair-value-mismatches)
              (push n each-evaluation-structure-pair-value-mismatches))
     ab::do
     (let* ((expected-data (pop data-copy))
            (fixed-expected-data
             (if (eq expected-data frame2) nil expected-data)))
       (unless (eq v fixed-expected-data)
         (push "value mismatch for" each-evaluation-structure-pair-value-mismatches)
         (push v each-evaluation-structure-pair-value-mismatches))))
    (when run-assertions
      (assert-eq 'v1 (ab::estructure-slot structure 'n1 nil))
      (assert-eq 'v2 (ab::estructure-slot structure 'n2 nil))
      (assert-eq frame1 (ab::estructure-slot structure 'n3 nil))
      ;; frame2 is reclaimed, so it must be nil
      (assert-eq nil (ab::estructure-slot structure 'n4 'not-a-value))
      (assert-eq 'not-a-value (ab::estructure-slot structure 'not-a-field 'not-a-value))
      (assert-eq nil each-evaluation-structure-pair-value-mismatches))
    (ab::reclaim-evaluation-structure structure)
    (ab::reclaim-eval-list data)
    (ab::delete-frame frame1)
    ))

;;; Structures
(define-test test--evaluation-structure--alloc-and-reclaim--no-memory-leak
  (with-connection-test-environment ()
    (evaluation-structure--alloc-and-reclaim--aux-fn nil nil)
    (ab::compare-memory-allocation nil t)
    (evaluation-structure--alloc-and-reclaim--aux-fn t nil)
    (assert-compare-memory-allocation-is-silent)))


(define-test test--evaluation-structure-inline--alloc-and-reclaim--no-memory-leak
  (with-connection-test-environment ()
    (evaluation-structure--alloc-and-reclaim--aux-fn nil t)
    (ab::compare-memory-allocation nil t)
    (evaluation-structure--alloc-and-reclaim--aux-fn t t)
    (assert-compare-memory-allocation-is-silent)))


(defun evaluation-structure--alloc-from-vector--correct-aux-fn (run-assertions)
  (let* ((data #(n1 v1 n2 v2))
         (structure-1 
          (ab::allocate-evaluation-structure-from-vector data 0 4))
         (structure-2
          (ab::allocate-evaluation-structure-from-vector data 0 2))
         (structure-3
          (ab::allocate-evaluation-structure-from-vector data 2 2)))
    (when run-assertions
      (assert-eq 'v1 (ab::estructure-slot structure-1 'n1 nil))
      (assert-eq 'v2 (ab::estructure-slot structure-1 'n2 nil))
      (assert-eq 'v1 (ab::estructure-slot structure-2 'n1 nil))
      (assert-eq nil (ab::estructure-slot structure-2 'n2 nil))
      (assert-eq nil (ab::estructure-slot structure-3 'n1 nil))
      (assert-eq 'v2 (ab::estructure-slot structure-3 'n2 nil)))
    (ab::reclaim-evaluation-structure structure-1)
    (ab::reclaim-evaluation-structure structure-2)
    (ab::reclaim-evaluation-structure structure-3)
    ))

(define-test test--evaluation-structure--alloc-from-vector--correct-and-no-memory-leak
  (with-simplest-test-environment ()
    (evaluation-structure--alloc-from-vector--correct-aux-fn nil)
    (ab::compare-memory-allocation nil t)
    (evaluation-structure--alloc-from-vector--correct-aux-fn t)
    (assert-compare-memory-allocation-is-silent)))

(defun set-evaluation-structure-slot--aux-fn (do-assertions)
  (let* ((structure
          (ab::allocate-evaluation-structure-inline
            'n1 'v1 'n2 (ab::make-evaluation-text "abc"))))
    (ab::set-evaluation-structure-slot structure 'n2 'v2)
    ;; old value in other cell is conserved
    (when do-assertions
      (assert-eq 'v1 (ab::estructure-slot structure 'n1 nil))
      (assert-eq 'v2 (ab::estructure-slot structure 'n2 nil)))
    (ab::reclaim-evaluation-structure structure)
    ))

;;; `test--reclaim-evaluation-text-twice` and `test--reclaim-frame-twice` are offtopic. 
;;; We check that double reclamation of some data causes an error. 
;;; Using this property, we can simply insert "reclaim-xxx" into
;;; our test text to ensure that xxx is not yet reclaimed. If
;;; xxx is reclaimed, our test will err. 
#+development
(define-test test--reclaim-evaluation-text-twice
  (with-simplest-test-environment ()
    (let ((tx (ab::make-evaluation-text "abc")))
      (ab::reclaim-evaluation-text tx)
      (assert-error 'error
                    (ab::reclaim-evaluation-text tx)))))

#+development
(define-test test--reclaim-frame-twice
   (with-connection-test-environment ()
     (let ((fr (ab::make-frame 'ab::block)))
       (ab::delete-frame fr)
       (assert-error 'error
                     (ab::delete-frame fr)
        ))))
     

(define-test test--set-evaluation-structure--result-correct-and-no-leak
  (with-simplest-test-environment ()
    (set-evaluation-structure-slot--aux-fn nil)
    (ab::compare-memory-allocation nil t)
    (set-evaluation-structure-slot--aux-fn t)
    (assert-compare-memory-allocation-is-silent)))

;;; check that frames are not reclaimed when references to them are overwritten
(defun set-evaluation-structure--replace-frame-with-text--aux-fn (do-assertions)
  (let* ((b (ab::make-frame 'ab::block))
         (s (ab::allocate-evaluation-structure-inline 'n1 b)))
    (ab::set-evaluation-structure-slot s 'n1 (ab::make-evaluation-text "abc"))
    (when do-assertions
      (assert-true (not (ab::deleted-frame-p b))))
    (ab::delete-frame b)
    (ab::reclaim-evaluation-structure s)))

(define-test set-evaluation-structure--overwrite-frame-by-text--frame-not-reclaimed
  (with-connection-test-environment ()
    (set-evaluation-structure--replace-frame-with-text--aux-fn nil)
    (ab::compare-memory-allocation nil t)
    (set-evaluation-structure--replace-frame-with-text--aux-fn t)
    (assert-compare-memory-allocation-is-silent)))


(defun overwrite-evaluation-structure-slot-macro-and-reclaim-data--aux-fn (do-assertions)
  (let* (
         ;; data which is initially in the structure
         (tx (ab::make-evaluation-text "abc"))
         (one (ab::make-evaluation-long 1))

         (s (ab::allocate-evaluation-structure-inline 'one one 'tx tx))

         ;; data to be put into structure and be reclaimed with the structure
         (two (ab::make-evaluation-long 2))
         (three (ab::make-evaluation-long 3))
         (four (ab::make-evaluation-long 4))

         ;; data for comparison - to be reclaimed manually
         (two-2 (ab::make-evaluation-long 2))
         (four-2 (ab::make-evaluation-long 4))

         ;; do replacements and remember some results
         (expected-two (ab::overwrite-evaluation-structure-slot-macro s 'one two))
         (dummy (ab::overwrite-evaluation-structure-slot-macro s 'tx three))
         (expected-four (ab::overwrite-evaluation-structure-slot-macro s 'four four)))

    (declare (ignore dummy))
    (when do-assertions
      (assert-true (ab::evaluation-value-= two-2 expected-two))
      (assert-true (ab::evaluation-value-= four-2 expected-four))
      (assert-true (ab::evaluation-value-= four-2 (ab::estructure-slot s 'four nil))))

    (ab::reclaim-evaluation-structure s)
    ;; reclaim data which was displaced from the structure
    ;; if it is reclaimed already, execution error will occur (in development only!)
    (ab::reclaim-evaluation-value tx)
    (ab::reclaim-evaluation-value one)

    ;; reclaim data used for comparison
    (ab::reclaim-evaluation-long two-2)
    (ab::reclaim-evaluation-value four-2)

    ))
           
(define-test test--overwrite-evaluation-structure-slot-macro-and-reclaim-data--memory-management-ok ()
  (with-connection-test-environment ()
    (overwrite-evaluation-structure-slot-macro-and-reclaim-data--aux-fn nil)
    (ab::compare-memory-allocation nil t)
    (overwrite-evaluation-structure-slot-macro-and-reclaim-data--aux-fn t)
    (assert-compare-memory-allocation-is-silent)))

;; test--obtain-mutable-copy-evaluation-structure-copy--correct-mutability-and-isolation 
;; 
(defun obtain-mutable-copy-evaluation-structure-copy--correct-mutability-and-isolation--aux-fn (do-assertions)
  (let* ((b (ab::make-frame 'ab::block))
         (one (ab::make-evaluation-long 1))
         (s (ab::allocate-evaluation-structure-inline 'b b 'one one))
         (s-is-mutable-upon-creation (ab::mutable-evaluation-structure-p s))
         ;; when we obtain a mutable copy of structure with one reference, copy is eq to original
         (mutable-copy-of-s-when-it-has-one-reference (ab::obtain-mutable-evaluation-structure-copy s))
         (s-eq-its-mutable-copy-when-it-had-one-reference (eq s mutable-copy-of-s-when-it-has-one-reference))
         ;; after s is copied, s and its copy are not mutable 
         (copy-of-s (ab::copy-evaluation-value s))
         (s-is-mutable-after-copying (ab::mutable-evaluation-structure-p s))
         (copy-of-s-is-mutable (ab::mutable-evaluation-structure-p copy-of-s))
         ;; obtain-mutable-copy - s is reclaimed, so we reuse the variable name. Note that
         ;; it is invalid to use mutable-copy-of-s-when-it-has-one-reference after that point
         (s (ab::obtain-mutable-evaluation-structure-copy s))
         (mutable-copy-of-s-is-mutable (ab::mutable-evaluation-structure-p s))
         (copy-of-s-is-mutable-after-obtaining-mutable-copy (ab::mutable-evaluation-structure-p copy-of-s))
         ;; check isolation between copy and original
         (dummy1 (ab::set-evaluation-structure-slot s 'one 'new-value))
         (some-one (ab::estructure-slot copy-of-s 'one nil))
         (one-2 (ab::make-evaluation-long 1))
         (some-one-equals-one (ab::evaluation-value-= some-one one-2)))
    (declare (ignore dummy1))
    (when do-assertions
      (assert-true s-is-mutable-upon-creation)
      (assert-true s-eq-its-mutable-copy-when-it-had-one-reference)
      (assert-false s-is-mutable-after-copying)
      (assert-false copy-of-s-is-mutable)
      (assert-true mutable-copy-of-s-is-mutable)
      (assert-true copy-of-s-is-mutable-after-obtaining-mutable-copy)
      (assert-true some-one-equals-one))
    (ab::reclaim-evaluation-value one-2)
    (ab::reclaim-evaluation-value s)
    (ab::reclaim-evaluation-value copy-of-s)
    (ab::delete-frame b)))


(define-test test--obtain-mutable-copy-evaluation-structure-copy--correct-mutability-and-isolation
  (with-connection-test-environment ()
    (obtain-mutable-copy-evaluation-structure-copy--correct-mutability-and-isolation--aux-fn nil)
    (ab::compare-memory-allocation nil t)
    (obtain-mutable-copy-evaluation-structure-copy--correct-mutability-and-isolation--aux-fn t)
    (assert-compare-memory-allocation-is-silent)))
    
         
(defun c-e-v (x)
  (ab::copy-evaluation-value x))

;; test--remove-evaluation-structure-attribute also touches ab::compare-structure-contents
(defun remove-evaluation-structure-attribute--aux-fn (do-assertions)
  (let* ((one (ab::make-evaluation-long 1))
         (two (ab::make-evaluation-long 2))
         (three (ab::make-evaluation-long 3))
         (original (ab::allocate-evaluation-structure-inline
                     'one (c-e-v one)
                     'two (c-e-v two)
                     'three (c-e-v three)))
         (expected-1 (ab::allocate-evaluation-structure-inline
                       'one (c-e-v one)
                       'three (c-e-v three)))
         (expected-2 (ab::allocate-evaluation-structure-inline
                       'one (c-e-v one)))
         (expected-3 (ab::allocate-evaluation-structure nil))
         (removed-0 (ab::remove-evaluation-structure-attribute original 'not-a-name))
         (removed-1 (ab::remove-evaluation-structure-attribute original 'two))
         (removed-2 (ab::remove-evaluation-structure-attribute removed-1 'three))
         (removed-3 (ab::remove-evaluation-structure-attribute removed-2 'one)))
    (when do-assertions 
      (assert-nil removed-0)
      (assert-true (ab::compare-structure-contents expected-1 removed-1 nil))
      (assert-true (ab::compare-structure-contents expected-2 removed-2 nil))
      (assert-true (ab::compare-structure-contents expected-3 removed-3 nil)))
    (ab::reclaim-evaluation-structure removed-3)
    (ab::reclaim-evaluation-value removed-2)
    (ab::reclaim-evaluation-value removed-1)
    (ab::reclaim-evaluation-value expected-3)
    (ab::reclaim-evaluation-value expected-2)
    (ab::reclaim-evaluation-value expected-1)
    (ab::reclaim-evaluation-value original)
    (ab::reclaim-evaluation-long three)
    (ab::reclaim-evaluation-value two)
    (ab::reclaim-evaluation-value one)))

(define-test test----remove-evaluation-structure-attribute
  (with-simplest-test-environment ()
    (remove-evaluation-structure-attribute--aux-fn nil)
    (ab::compare-memory-allocation nil t)
    (remove-evaluation-structure-attribute--aux-fn t)
    (assert-compare-memory-allocation-is-silent)))

    
    
    
  
 
             


;; More tests to write:
#|

compare-structure-contents - check for order dependency


7. ab::def-evaluation-value-copier - how to test? I guess 

|#

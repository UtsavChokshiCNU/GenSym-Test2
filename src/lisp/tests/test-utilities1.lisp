(in-package :tests)

;; UNIMPORTANT-CODE register-definition

;; RETURN-HERE def-memory-allocation-schemes might be accidentally covered

(proclaim '(optimize debug))


(define-test test--maximum-gensym-string-length-error--pass-small-value--expect-error
  ;; also we test that maximum-gensym-string-length-error refers to
  ;; ab::maximum-gensym-string-length
  (assert-equal
   "Attempting to allocate 50 element string, which is beyond the established maximum of 100."
   (princ-to-string
    (nth-value 1
               (ignore-errors
                 (let ((ab::maximum-gensym-string-length 100))
                   (ab::maximum-gensym-string-length-error 50)))))))


;; RETURN-HERE new-short-simple-gensym-string-vector .. copy-gensym-tree-with-text-strings
;; conser is not covered yet, so it is too early to test this

;; this function ignores AB memory management
(defun make-test-simple-gensym-string-abca-no-conser (&key (string "abca"))
  (let ((s (copy-seq string)))
    (assert (eval `(ab::gensym-string-p ,s)))
    (assert (eval `(ab::simple-gensym-string-p ,s)))
    s))
  

;; this is not a test, but utility function, this is why we use assert, but not assert-true
;; this function ignores AB memory management
(defun make-test-non-simple-gensym-string-abca-no-conser (&key (initial-contents "abcaAd") (fill-pointer 4))
  (let ((result 
         (make-array (list (length initial-contents))
                     :element-type 'character
                     :initial-contents initial-contents
                     :adjustable t
                     :fill-pointer fill-pointer)))
    (assert (ab::gensym-string-p result))
    (assert (null (ab::simple-gensym-string-p result)))
    result))

(defun simple-and-non-simple-string-ignoring-conser (&key (initial-contents "abcaAd") (fill-pointer 4) list-too)
  (list*
   (make-test-simple-gensym-string-abca-no-conser
    :string (subseq initial-contents 0 fill-pointer))
   (make-test-non-simple-gensym-string-abca-no-conser
    :initial-contents initial-contents :fill-pointer fill-pointer)
   (when list-too
     (list (coerce (subseq initial-contents 0 fill-pointer) 'list)))))

(defun test-position-aux-fn (s)
  ;; checks several variants of position-in-gensym-string
  ;; bad test design - needs debugging when test fails
  (and 
   (eql (ab::position-in-gensym-string #\a s) 0)
   (null (ab::position-in-gensym-string #\A s)) ; case-sensitivity. Also check for fill pointer for non-simple strings
   (eql 1 (ab::position-in-gensym-string #\b s))
   (eql 2 (ab::position-in-gensym-string #\c s))
   (null (ab::position-in-gensym-string #\d s)) ; non-present char, but would be found if we didn't obey fill pointer
   ))

(define-test test--position-in-gensym-string--imitate-simple-and-non-simple-gensym-string
  (let ((success t))
    (dolist (s (simple-and-non-simple-string-ignoring-conser))
      (unless (test-position-aux-fn s)
        (show-expr `(:failed ,s))
        (setf success nil)
        (return)))
    (assert-true success)))

(defun test-find-in-sequence-aux-fn (fn s)
  (let ((success t))
    (dolist (char '(#\a #\b #\c))
      (unless (char= char (funcall fn char s))
        (setf success nil)
        (return)))
    (unless (null (funcall fn #\A s))
      (setf success nil))
    success))

(define-test test--find-in-gensym-string--imitate-simple-and-non-simple-gensym-string
  (let ((success t))
    (dolist (s (simple-and-non-simple-string-ignoring-conser))
      (unless (test-find-in-sequence-aux-fn 'ab::find-in-gensym-string s)
        (show-expr `(:failed ,s))
        (setf success nil)
        (return)
        ))
    (assert-true success)))

;; RETURN-HERE
;; (t (find character bag ':test #'char=)))) line is not covered (sequence which is neither gensym-string-p nor listp)
(define-test test--find-gensym-character-in-sequence--give-existing-and-not-existing-item--expect-found-and-not-found
  (let ((success t))
    (dolist (bag (simple-and-non-simple-string-ignoring-conser :list-too t))
     (unless
         (and
          (char= #\a (ab::find-gensym-character-in-sequence #\a bag))
          (char= #\b (ab::find-gensym-character-in-sequence #\b bag))
          (null (ab::find-gensym-character-in-sequence #\A bag))
          (null (ab::find-gensym-character-in-sequence #\d bag))
          )
       (show-expr `(:failed ,bag))
       (setf success nil)
       (return)))
  (assert-true success)))


(defun aux-fn-for-test--position-of-ascii-character-NOT-in-bag (string bag keyargs)
  ;; the function is macro this is why we need eval here
  (eval `(ab::position-of-ascii-character-not-in-bag ',string ',bag ,@keyargs)))
  
(defun aux-fn-for-test--position-of-ascii-character-in-bag (string bag keyargs)
  ;; the function is macro this is why we need eval here
  (eval `(ab::position-of-ascii-character-in-bag ',string ',bag ,@keyargs)))


(define-test test--position-of-ascii-character-in-bag--give-existing-and-not-exsting-items-for-string-and-bag--expect-found-and-not-found
  (let ((success t))
    (block outer-loop
      (dolist (bag (simple-and-non-simple-string-ignoring-conser :list-too t))
        (dolist (string (simple-and-non-simple-string-ignoring-conser))
          (dolist (keyargs
                   '((:end 1) (:start 0 :end 2) (:start 0 :end 3)
                     (:start 0) () (:start 1 :end 2) (:start 1 :start 3)
                     (:start 2 :end 3) (:end 3)))
            (let ((start (or (getf keyargs :start) 0)))
              (unless
                  (and 
                   (null (aux-fn-for-test--position-of-ascii-character-NOT-in-bag string bag keyargs))
                   (eql start (aux-fn-for-test--position-of-ascii-character-in-bag string bag keyargs))
                   )
                (show-expr `(:failed ,string ,bag ,keyargs))
                (setf success nil)
                (return-from outer-loop)))))))
    (assert-true success)))
              

(define-test test--position-of-ascii-character-in-bag--give-corner-cases--expect-reasonable-results
  (let ((success t))
    (dolist (string (simple-and-non-simple-string-ignoring-conser))
      (dolist (bag (simple-and-non-simple-string-ignoring-conser :initial-contents "gdeAab" :list-too t :fill-pointer 4))
        ;; keyargs-both-functions-must-fail
        (dolist (keyargs
                 '((:start 3) (:end 0) (:start 1 :end 1)))
          (unless
            (null (aux-fn-for-test--position-of-ascii-character-in-bag string bag keyargs))
            (show-expr `(:failed ,string ,bag ,keyargs))
            (setf success nil)
            ; skip returning
            ))
        ;; chars from this bag never present - always first char is not from bag
        (dolist (keyargs
                 '((:end 1) (:start 0 :end 2) (:start 0 :end 3)
                   (:start 0) () (:start 1 :end 2) (:start 1 :start 3)
                   (:start 2 :end 3) (:end 3)))
          (let ((start (or (getf keyargs :start) 0)))
            (unless
                (and
                 (null (aux-fn-for-test--position-of-ascii-character-in-bag string bag keyargs))
                 (eql start (aux-fn-for-test--position-of-ascii-character-NOT-in-bag string bag keyargs))
                 )
              (show-expr `(:failed ,string ,bag ,keyargs)))))))
    (assert-true success)))

(define-test test-position-of-ascii-character-not-in-bag-from-end
  ;; code is very similar to that of test-position-of-ascii-character-not-in-bag
  ;; so I add only test cases from docstring
  (assert-equal 7 (ab::position-of-ascii-character-not-in-bag-from-end "  foobar      " " " :start 6  :end 10))
  (assert-equal nil (ab::position-of-ascii-character-not-in-bag-from-end "  foobar      " " " :start 8  :end 10))
  (assert-equal 7 (ab::position-of-ascii-character-not-in-bag-from-end "  foobar      " " "))
  )

;; UNUSED-CODE ab::parse-space-delimited-ascii-text-line-into-list-of-ascii-strings

; RETURN-HERE I (Budden) believe non-ASCII chars are irrelevant for gensym-strings, but I'm not sure 
; So will return here when will know. 


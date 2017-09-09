(in-package :tests)

(proclaim '(optimize debug))

(define-test test--list-prefix-p
  (let ((result
	 (and (ab::list-prefix-p nil nil)
	      (ab::list-prefix-p nil (list '+))
	      (ab::list-prefix-p (list '+) (list '+ '-))
	      (ab::list-prefix-p (list '+ '-) (list '+ '-))
	      (not (ab::list-prefix-p (list '+ '-) (list '- '+)))
	      (not (ab::list-prefix-p (list '+ '-) (list '+)))
	      (not (ab::list-prefix-p (list '+) nil)))))
    (assert-true result)))

(define-test test--list-prefix-p--2
  (assert-true (ab::list-prefix-p nil nil))
  (assert-true (ab::list-prefix-p '(a) '(a)))
  (assert-true (ab::list-prefix-p '(a) '(a b)))
  (assert-false (ab::list-prefix-p '(a b) '(a)))
  (assert-false (ab::list-prefix-p '(b b) '(a b)))
  (assert-false (ab::list-prefix-p (list (string #\a)) (list (string #\a)))))

(define-test test-form-has-side-effects-p
  (let ((result
	 (and (not (ab::form-has-side-effects-p 'abc))
	      (ab::form-has-side-effects-p '(abc))
	      (not (ab::form-has-side-effects-p ''(abc))))))
    (assert-true result)))

(define-test test-make-symbol-for-avoiding-variable-capture-no-uniquify 
  (let* ((result (ab::make-symbol-for-avoiding-variable-capture "ABC" nil))
	 (result-1 (and (eq (symbol-package result) nil)
			(string= (string result) "ABC"))))
    (assert-true result-1)))

(define-test test-make-symbol-for-avoiding-variable-capture-uniquify
  (AB-UNINTERN-AND-INTERN "ABC")
  (let* ((result1 (ab::make-symbol-for-avoiding-variable-capture "ABC" T))
	 (result2 (ab::make-symbol-for-avoiding-variable-capture "ABC" T))
	 (test1 (and
		  (eq (symbol-package result1) nil)
		  (string= (string result1) #+development "ABC-1" #-development "ABC")))
	 (test2 (and
		  (eq (symbol-package result2) nil)
		  (string= (string result2) #+development "ABC-2" #-development "ABC"))))
    (assert-true test1)
    (assert-true test2)))

(defun macroexpand-avoiding-variable-capture-form-1 (form)
  (eval
   '(defmacro avoiding-variable-capture-test-macro-1 (a b &rest keys)
      (ab::avoiding-variable-capture (a b &rest keys)
        `(list ,a ,b ,@keys))))
  (eval `(macroexpand ',form)))

(define-test test-avoiding-variable-capture-1
  (assert-equal
   '(LET ((A-1 (+ A 1))) (LIST A-1 2))
   (mock::expect 
    ((:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "A" T) :return ('a-1))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "B" T) :return ('b-1)))
    :for (macroexpand-avoiding-variable-capture-form-1 '(avoiding-variable-capture-test-macro-1 (+ a 1) 2)))))

(define-test test-avoiding-variable-capture-2
  (assert-equal
   (macroexpand-avoiding-variable-capture-form-1 '(avoiding-variable-capture-test-macro-1 1 2 'x))
   (values '(LIST 1 2 'X) t)))

(define-test test-avoiding-variable-capture-3
  (assert-equal
   (mock::expect 
    ((:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "A" T)
      :return ('ignorable))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "B" T)
      :return ('b-1))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "ELT-0-OF-KEYS" T)
      :return ('ignorable))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "ELT-1-OF-KEYS" T)
      :return ('elt-1-of-keys-1)))
    :for 
    (macroexpand-avoiding-variable-capture-form-1
     '(avoiding-variable-capture-test-macro-1 1 (incf a b) 3 (get-key 'aux))))
   (values
    '(LET ((B-1 (INCF A B)) (ELT-1-OF-KEYS-1 (GET-KEY 'AUX))) (LIST 1 B-1 3 ELT-1-OF-KEYS-1)))))


(defun macroexpand-avoiding-variable-capture-form-2 (form)
  (eval
   '(defmacro avoiding-variable-capture-test-macro-2 (major-version minor-version &rest keys)
      (ab::avoiding-variable-capture 
          (major-version minor-version &rest keys &aux month)
        `(let ((,month (derive-month ,major-version ,@keys)))
           (list ,major-version ,minor-version ,@keys ,month)))))
  (macroexpand form))

;; RETURN-HERE this tests errs in LW, but passes in SBCL.
#|(define-test test-avoiding-variable-capture-4
  (assert-equal
   (mock::expect 
    ((:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "A" T)
      :return ('ignorable))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "B" T)
      :return ('b-1))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "ELT-0-OF-KEYS" T)
      :return ('ignorable))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "ELT-1-OF-KEYS" T)
      :return ('elt-1-of-keys-1)))
    :for 
    (macroexpand-avoiding-variable-capture-form-2
     '(avoiding-variable-capture-test-macro-2 1 2 'remote-gsi-extension)))
   (values
    '(AB::LET ((B-1 (INCF A B)) (ELT-1-OF-KEYS-1 (GET-KEY 'AUX))) (LIST 1 B-1 3 ELT-1-OF-KEYS-1)))))|#

(define-test test-avoiding-variable-capture-4a
  (assert-equal
   '(list 1 2 3 4)
   (macroexpand-avoiding-variable-capture-form-1
    '(avoiding-variable-capture-test-macro-1 1 2 3 4))
   ))

(defun define-test-avoiding-variable-capture-5-macro ()
  (eval
   '(defmacro test-avoiding-variable-capture-5-macro (major-version minor-version &rest keys)
      (ab::avoiding-variable-capture 
          (major-version minor-version &rest keys &aux month)
        `(let ((,month (derive-month ,major-version ,@keys)))
           (list ,major-version ,minor-version ,@keys ,month))))))

(define-test test-avoiding-variable-capture-5-1
  (define-test-avoiding-variable-capture-5-macro)
  (assert-equal
   (mock::expect 
    ((:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "MONTH" T)
      :return ('month-1)))
    :for 
    (macroexpand-1
     '(test-avoiding-variable-capture-5-macro 1 2 'remote-gsi-extension)))
   (values
    '(LET ((MONTH-1 (DERIVE-MONTH 1 'REMOTE-GSI-EXTENSION)))
       (LIST 1 2 'REMOTE-GSI-EXTENSION MONTH-1))
    t)))

(define-test test-avoiding-variable-capture-5-2
  (define-test-avoiding-variable-capture-5-macro)
  (assert-equal
   (mock::expect 
    ((:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "MAJOR-VERSION" T)
      :return ('major-version-1))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "MINOR-VERSION" T)
      :return ('minor-version-1))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "ELT-0-OF-KEYS" T)
      :return ('elt-0-of-keys-0))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "MONTH" T)
      :return ('month-1)))
    :for 
    (macroexpand-1
     '(test-avoiding-variable-capture-5-macro 1 (incf old-minor-version) (get-key))))
   (values
    '(AB::LET ((MINOR-VERSION-1 (INCF OLD-MINOR-VERSION))
               (ELT-0-OF-KEYS-0 (GET-KEY)))
       (LET ((MONTH-1 (DERIVE-MONTH 1 ELT-0-OF-KEYS-0)))
         (LIST 1 MINOR-VERSION-1 ELT-0-OF-KEYS-0 MONTH-1)))
    t)))

(defun define-test-avoiding-variable-capture-6-macro ()
  (eval
   '(defmacro test-avoiding-variable-capture-6-macro 
              (search-for-string in-string 
                                 &key start-in-string end-in-string)
      (ab::avoiding-variable-capture (search-for-string in-string
                                                        &optional (start-in-string 0)
                                                        (end-in-string `(length ,in-string)))
        `(loop for index from ,start-in-string below ,end-in-string
               always (eql (char ,search-for-string index)
                           (char ,in-string index)))))))

(define-test test-avoiding-variable-capture-6-1
  (define-test-avoiding-variable-capture-6-macro)
  (assert-equal
   (mock::expect 
    ((:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "SEARCH-FOR-STRING" T)
      :return ('ignorable))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "IN-STRING" T)
      :return ('ignorable))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "START-IN-STRING" T)
      :return ('start-in-string-1))
     (:call (AB::MAKE-SYMBOL-FOR-AVOIDING-VARIABLE-CAPTURE "END-IN-STRING" T)
      :return ('end-in-string-1)))
    :for 
    (macroexpand-1
     '(test-avoiding-variable-capture-6-macro "lo" "Hello there" 
                                              :start-in-string 3 :end-in-string (+ 2 3))))
   (values
    '(AB::LET ((END-IN-STRING-1 (+ 2 3)))
       (LOOP FOR INDEX FROM 3 BELOW END-IN-STRING-1
             ALWAYS (EQL (CHAR "lo" INDEX) (CHAR "Hello there" INDEX))))
    t)))


(defun all-numeric-lists-of-length (length limit)
  "List of all possible lists combined from elements 0..limit-1. Returns freshly consed list, you can changed it"
  (let (result)
    (cond
     ((= length 0)
      nil)
     ((= length 1)
      (dotimes (i-zeroth limit)
        (push (list i-zeroth) result))
      result)
     (t
      (dolist (sublist (all-numeric-lists-of-length (- length 1) limit))
        (dotimes (i-zeroth limit)
          (push (copy-list (cons i-zeroth sublist)) result)))
      result))))



;;;; Scoped Consing

(defun aux-fn-test--scope-conses--use--make-sure-no-leak-no-intersection (initial-scope-conses-values victim-list-size run-fn)
  ;; bind scope-conses to initial-scope-conses-values;
  ;; exhaust gensym conses 
  ;; feed the victim of given size to gensym conser
  ;; call the code which assumed to use scope-consing
  ;; make sure we did not replenish and did not lose any cons
  (let ((ab::cons-checking-enabled-p nil))
    (with-simplest-test-environment ()
      (assert-scope-conses-not-shared-to-available-conses)
      (exhaust-gensym-conses)
      (let* ((success t)
             (copy-of-initial-scope-cons-values (copy-tree initial-scope-conses-values))
             (ab::scope-conses initial-scope-conses-values)
             (victim (make-list victim-list-size :initial-element 'victim))
             (conses-to-work-with 
              (append
               (all-conses-of-list victim)
               (all-conses-of-list ab::available-gensym-conses)
               ;; scope-cons takes two conses from gensym conser for each entry. 
               ;; first of them becomes a new member of ab::scope-conses 
               ab::scope-conses
               ;; second of them constitutes a structure (nthcdr) of ab::scope-conses itself
               (all-conses-of-list ab::scope-conses)
               ))
             where-conses-to-work-with-should-finally-be)
        (ab::reclaim-gensym-list victim)
        (assert-scope-conses-not-shared-to-available-conses)
        (funcall run-fn)
        (assert-scope-conses-not-shared-to-available-conses)
        (setf where-conses-to-work-with-should-finally-be
              (append 
               (all-conses-of-list ab::available-gensym-conses)
               ab::scope-conses
               (all-conses-of-list ab::scope-conses)
               ))
        ;; make sure we did not lost conses and did not get new ones from the replenish
        (unless (alexandria:set-equal conses-to-work-with where-conses-to-work-with-should-finally-be)
          (show-expr `("failed" ,copy-of-initial-scope-cons-values ,victim-list-size ,run-fn))
          (setf success nil))
        success))))
   
(defun run-fn-scope-conses-10-3-cons ()
  (dotimes (i 10)
    ;; loop here is to make sure deallocation takes place
    ;; when scope-conses gets unbound
    (let ((ab::scope-conses ab::scope-conses))
      (dotimes (j 3)
        (ab::scope-cons j j)))))

(defun run-fn-scope-conses-10-3-cons-nesting ()
  (dotimes (i 10) 
    (let ((ab::scope-conses ab::scope-conses))
      (ab::scope-cons 1 1)
      (let ((ab::scope-conses ab::scope-conses))
        (ab::scope-cons 2 2)
        (let ((ab::scope-conses ab::scope-conses))
          (ab::scope-cons 3 3))))))

(defun run-fn-scope-conses-1-0-list ()
  ;; no need to bind - no allocation expected
  (ab::scope-list))

(defun run-fn-scope-conses-10-3-1-list ()
  (dotimes (i 10) 
    (let ((ab::scope-conses ab::scope-conses))
      (dotimes (j 3)
        (ab::scope-list j)))))

(defun run-fn-scope-conses-10-3-list ()
  (dotimes (i 10) 
    (let ((ab::scope-conses ab::scope-conses))
      (ab::scope-list 'a 'b 'c))))

(defun run-fn-scope-conses-0-make-list ()
  ;; no need to bind - no allocation expected
  (ab::make-scope-list 0))

(defun run-fn-scope-conses-10-3-make-list ()
  (dotimes (i 10) 
    (let ((ab::scope-conses ab::scope-conses))
      (ab::make-scope-list 3))))

(defun run-fn-scope-conses-10-3-copy-list ()
  (let ((lst (list 1 2 3)))
    (dotimes (i 10) 
      (let ((ab::scope-conses ab::scope-conses))
        (ab::copy-list-using-scope-conses lst)))))

(defparameter *run-fn-scope-conses-3-fns*
  '(run-fn-scope-conses-10-3-cons
    run-fn-scope-conses-10-3-cons-nesting
    run-fn-scope-conses-1-0-list
    run-fn-scope-conses-10-3-1-list
    run-fn-scope-conses-10-3-list
    run-fn-scope-conses-0-make-list
    run-fn-scope-conses-10-3-make-list
    run-fn-scope-conses-10-3-copy-list))


;;; this test depends on implementation of scope-conses. 
;;; Scope-conses can be reused in the scope, but they are 
;;; never reclaimed to conser
(define-test test--scope-conses--use--make-sure-no-leak-no-intersection
  (let ((success t))
    (dolist (fn *run-fn-scope-conses-3-fns*)
      (dolist (initial-scope-conses
               (list
                (list (list nil)) ; initial "empty" scope-conses contents
                (list (list nil) (list nil)) ; filled a bit already
                (list (list nil) (list nil) (list nil)) ; filled enough to give 3 conses
                (list (list nil) (list nil) (list nil) (list nil))
                ))
        (let ((copy-of-initial-scope-conses (copy-tree initial-scope-conses)))
          (unless
              (aux-fn-test--scope-conses--use--make-sure-no-leak-no-intersection
               initial-scope-conses
               (* 3 ; we will allocate list of 3 items on scope conses
                  2 ; we consume 2 gensym conses per scope-cons
                  )
               fn)
            (show-expr `("failed: " ,fn ,copy-of-initial-scope-conses))
            (setf success nil)))))
    (assert-true success)))

(define-test test--scope-cons--run-misc-functions--expect-correct-value
  (let ((ab::scope-conses ab::scope-conses))
    (assert-equal (ab::scope-cons 1 2) (cons 1 2))
    (assert-equal (ab::scope-list) (list))
    (assert-equal (ab::scope-list 1) (list 1))
    (assert-equal (ab::scope-list 1 2 3 4) (list 1 2 3 4))
    (dotimes (n 3)
      (let* ((lst (ab::make-scope-list n))
	     (result (and (listp lst)
			  (= n (length lst)))))
	(assert-true result)))
    (assert-equal (ab::copy-list-using-scope-conses (list 1 2 3))
                  (list 1 2 3))))

(define-test test--copy-list-using-scope-conses--run--does-not-modify-original 
  (let* ((lst (list 1 2 3))
         (conses-of-lst (all-conses-of-list lst))
         (ab::scope-conses ab::scope-conses)
         (result (ab::copy-list-using-scope-conses lst)))
    ;; check that original consists of the same conses
    (assert-equal conses-of-lst (all-conses-of-list lst))
    ;; checks that data was not changed
    (assert-equal lst (list 1 2 3))
    ;; check that result is freshly consed
    (assert-false
     (intersection
      (all-conses-of-list lst)
      (all-conses-of-list result)))))

;;;; Sorting 
;; UNUSED-CODE ab::sort-array

(define-test test-sort-list
  (let* ((n 6)
         (failure nil)
         (key-counter 0))
    (dolist (list (all-numeric-lists-of-length n (+ n 1)))
      (setf key-counter (- 1 key-counter))
      (let* ((a1 (copy-seq list))
             (s1 (sort a1 '<))
             (key (ecase key-counter (0 'identity) (1 nil)))
             (list-to-sort (copy-list list)))
        (unless (equalp s1 (ab::sort-list list-to-sort '< key))
          (setf failure t)
          (return))))
    (assert-false failure)))
  

(defun cars-are-eql (x y)
  (eql (car x) (car y)))

(defun cdrs-of-elements-increase-p (list)
  (cond
   ((< (length list) 2) t)
   (t
    (and (< (cdr (first list)) (cdr (second list)))
         (cdrs-of-elements-increase-p (cdr list))))))

(define-test test-delete-duplicates-from-list-1
  "We check against lisp's own implementation. Also we check that order of things didn't change"
  (let ((n 6) (failure nil))
    (dolist (list (all-numeric-lists-of-length n n))
      (let*
          ((list-with-recorded-order
            (loop :for elt :in list
                  :for no :from 0
                  :collect (cons elt no)))
           (l1 (copy-list list-with-recorded-order))
           (l2 (copy-list list-with-recorded-order)))
        (setf l1 (delete-duplicates l1 :test 'cars-are-eql))
        (setf l2 (ab::delete-duplicates-from-list l2 'identity 'cars-are-eql))
        (unless (set-equal (mapcar 'car l1) (mapcar 'car l2))
          ;(format t "~A ~A ~A" list l1 l2)
          (setf failure t)
          (return))
        (unless (cdrs-of-elements-increase-p l2)
          (setf failure t)
          (return))))
    (assert-false failure)))

(define-test test-delete-duplicates-from-list-2
  "Test with null test-function?"
  (assert-equal 
   (ab::delete-duplicates-from-list (list 'a 'a 'b 'b 'c) 'identity)
   '(a b c)))


;; TESTERS-COMMENT delete-item-from-list-and-reclaim-cons-cells has no clear semantics
;; This is what I about it:
;; i) if retain-first-value? is t, it does not look for item to delete in first position of the list.
;; ii) it deletes at least one value it finds. Sometimes it deletes more than one, sometimes just one.

(defun delete-item-from-list-and-reclaim-cons-cells-fn (list item retain-first-value?)
  "Returns (values list-after-deletion t) if all ok. Returns (values something nil) if cons leaked or created"
  (let* ((list (copy-list list))
         (conses-of-list (all-conses-of-list list))
         (reclaimed-cons nil)
         (reclaimer (lambda (x) (push x reclaimed-cons)))
         (new-list 
          (ab::delete-item-from-list-and-reclaim-cons-cells list item reclaimer retain-first-value?))
         (conses-of-new-list (all-conses-of-list new-list)))
    (values
     new-list
     (set-equal (union conses-of-new-list reclaimed-cons) conses-of-list))))
     
     
 
#|
 ; test case generator. Some tests generated are superflous
 (let (known-tests)
   (dolist (list '(nil (+) (+ b) (+ + b) (+ b +) (b + b)
                       (+ + + +) (+ + + b) (+ + b +) (+ + b b) (+ b + b)
                       (+ b b b)))
     (dolist (item list)
       (dolist (retain-first-value? '(nil t))
         (let ((args (list list item retain-first-value?)))
           (unless (member args known-tests :test 'equalp)
             (push args known-tests)             
             (print `(,args
                      ,(apply 'delete-item-from-list-and-reclaim-cons-cells-fn args)))))))))
|#


;;; this data was generated and then reviewed. Buggy cases are commented out and copied to another test
(defparameter *delete-item-from-list-and-reclaim-cons-cells-test-data*
  '(
    (((+) + NIL) NIL) 
    (((+) + T) (+)) 
    (((+ B) + NIL) (B)) 
    (((+ B) + T) (+ B)) 
    (((+ B) B NIL) (+)) 
    (((+ B) B T) (+)) 
    (((+ + B) + NIL) (+ B)) 
    (((+ + B) + T) (+ + B)) 
    (((+ + B) B NIL) (+ +)) 
    (((+ + B) B T) (+ +)) 
    (((+ B +) + NIL) (B)) 
    (((+ B +) + T) (+ B)) 
    (((+ B +) B NIL) (+ +)) 
    (((+ B +) B T) (+ +)) 
    (((B + B) B NIL) (+)) 
    (((B + B) B T) (B +)) 
    (((B + B) + NIL) (B B)) 
    (((B + B) + T) (B B)) 
    (((+ + + +) + NIL) (+)) 
    ; (((+ + + +) + T) (+ +)) 
    (((+ + + B) + NIL) (+ B)) 
    (((+ + + B) + T) (+ + B)) 
    (((+ + + B) B NIL) (+ + +)) 
    (((+ + + B) B T) (+ + +)) 
    (((+ + B +) + NIL) (+ B)) 
    ; (((+ + B +) + T) (+ + B)) 
    (((+ + B +) B NIL) (+ + +)) 
    (((+ + B +) B T) (+ + +)) 
    ; (((+ + B B) + NIL) (+ B B)) 
    (((+ + B B) + T) (+ + B B)) 
    (((+ + B B) B NIL) (+ +)) 
    (((+ + B B) B T) (+ +)) 
    (((+ B + B) + NIL) (B B)) 
    (((+ B + B) + T) (+ B B)) 
    (((+ B + B) B NIL) (+ +)) 
    (((+ B + B) B T) (+ +)) 
    (((+ B B B) + NIL) (B B B)) 
    (((+ B B B) + T) (+ B B B)) 
    (((+ B B B) B NIL) (+)) 
    (((+ B B B) B T) (+)) 
    ))


(defparameter *strange-delete-item-from-list-and-reclaim-cons-cells-test-data*
  '(
    (((+ + + +) + T) (+))  ; actually returns (+ +)
    (((+ + B +) + T) (+ B)) ; actually returns (+ + B)
    (((+ + B B) + NIL) (B B)) ; actually returns (+ B B)
    ))
 

(define-test test-delete-item-from-list-and-reclaim-cons-cells-nil
  (assert-equal (ab::delete-item-from-list-and-reclaim-cons-cells nil 'a 'identity t) nil)
  (assert-equal (ab::delete-item-from-list-and-reclaim-cons-cells nil 'a 'identity nil) nil))

(defun test-delete-item-from-list-and-reclaim-cons-cells-from-data-fn (test-cases)
  (let* ((failed nil))
    (dolist (entry test-cases)
      (destructuring-bind (args expected-result) (copy-tree entry)
        (multiple-value-bind (new-list no-leaky-cons)
            (apply #'delete-item-from-list-and-reclaim-cons-cells-fn args)
          (unless no-leaky-cons
            (setf failed t)
            (return))
          (unless (equalp new-list expected-result)
            (setf failed t)
            (return)))))
    (assert-false failed)))


(define-test test-delete-item-from-list-and-reclaim-cons-cells-normal
  (test-delete-item-from-list-and-reclaim-cons-cells-from-data-fn *delete-item-from-list-and-reclaim-cons-cells-test-data*))

#-exclude-possible-bugs
(define-test test-delete-item-from-list-and-reclaim-cons-cells-strange
  (test-delete-item-from-list-and-reclaim-cons-cells-from-data-fn *strange-delete-item-from-list-and-reclaim-cons-cells-test-data*))

(defun test-nreverse-canonically-fn (list)
  "Returns nil if test case failed"
  (let* ((l (copy-list list))
         (conses (all-conses-of-list l))
         (result (ab::nreverse-canonically l))
         (results-conses-reversed-back (reverse (all-conses-of-list result)))
         (expected (reverse list)))
    (unless (equalp expected result)
      (return-from test-nreverse-canonically-fn nil))
    (loop
     (unless results-conses-reversed-back
       (return))
     (unless (eq (pop results-conses-reversed-back)
                 (pop conses))
       (return-from test-nreverse-canonically-fn nil)))
    t))


(define-test test-nreverse-canonically
  (assert-true
   (every 'test-nreverse-canonically-fn
          (list
           '((a)
             (a b)
             (a b c)
             (a b c d)
             (a b c d e))))))

;;;; Simple Vector Pool 

(define-test test--outstanding-simple-vector-pool-vectors--allocate-some-vectors--expect-reasonable-change-in-value
  (with-initialized-managed-simple-vector-allocator
   (let* ((success t)
          (value-before (ab::outstanding-simple-vector-pool-vectors))
          (vectors
           (loop
            :for i :from 1 :to 1025
            :for expected-value :from (+ value-before 1)
            :collect (ab::allocate-managed-simple-vector i)
            :unless (= (ab::outstanding-simple-vector-pool-vectors) expected-value)
            :do
            (progn
              (setf success nil)
              (show-expr `("failed when allocating:" ,i))))))
     (loop :for vector in vectors
           :for counter from 1
           :for expected-value
           := (- (ab::outstanding-simple-vector-pool-vectors) 1)
           :then (- expected-value 1)
           :do (ab::reclaim-managed-simple-vector vector)
           :unless (= (ab::outstanding-simple-vector-pool-vectors) expected-value)
           :do
           (progn
             (show-expr `("failed when deallocating:" ,counter))
             (setf success nil)))
     (assert-true success))))

(defun aux-fn-expected-allocated-vector-length (requested-length)
  (cond
   ((<= requested-length 0) :none)
   ((<= requested-length 1024) requested-length)
   (t
    (* 1024 (ceiling requested-length 1024)))))

(define-test test--allocate-managed-simple-vector--run--length-is-ok
  (with-initialized-managed-simple-vector-allocator
   (let ((success t))
     (dotimes (i 4098)
       (let* ((n (+ i 1)))
         (let ((v (ab::allocate-managed-simple-vector n)))
           (unless (= (length v) (aux-fn-expected-allocated-vector-length n))
             (show-expr `("failed" ,n))
             (setf success nil))
           (ab::reclaim-managed-simple-vector v))))
     (assert-true success))))

;;; Returns a pool of simple vectors of given size 
;;; We rely upon implementation details
(defun aux-fn-storage-pool-for-simple-vector-of-size (size)
  ;; If either of the following assertion fails, our idea about buffer allocation is wrong
  (assert (<= size ab::maximum-managed-simple-vector-size))
  (assert (< ab::maximum-managed-simple-vector-size (length ab::vector-of-simple-vector-pools)))
  (svref ab::vector-of-simple-vector-pools size))

;;; Calculates a number of vector in the pool of vectors of this size
(defun aux-fn-number-of-reclaimed-simple-vectors-of-size (size)
  (let*
      ((pool (aux-fn-storage-pool-for-simple-vector-of-size size))
       (count 0))
    (do ((x pool))
        ((null pool) count)
      (incf count)
      (setf pool (svref pool 0)))))

(define-test test--reclaim-managed-simple-vector--deallocate-vector-containing-vector--make-sure-allocator-is-not-confused
  (with-initialized-managed-simple-vector-allocator
    (let ((success t))
      (dolist (size '(5 1025 10000))
        (let* ((v (ab::allocate-managed-simple-vector size)))
          (setf (svref v 0) (vector 1 2 3))
          (ab::reclaim-managed-simple-vector v)
          (unless (validate-simple-vector-pools)
            (show-expr `("failed:" size))
            (setf success nil)
            (return)))))))

;; RETURN-HERE
;; tests that must be added to allocator testing
;; check that every vector falls to the appropriate pool upon being reclaimed
;; - for two cases - if the pool is empty and if it is not empty
;; check that if we exhaust pool it is replenished nicely 
;; check that the vector allocated is taken from the pool (when the pool is non -empty)
;; check that as the pool is emplty, correct replenish function is invoked

;; TRIVIAL-CODE reclaim-managed-simple-vector-for-array ...  reclaim-managed-simple-vector-for-skip-list

(defparameter *fill-managed-simple-vector-test-data*
  '(((0 5) #(1 1 1 1 1))
    ((1 5) #(0 1 1 1 1))
    ((2 5) #(0 0 1 1 1))
    ((2 2) #(0 0 0 0 0))
    ((4 5) #(0 0 0 0 1))
    ((1 0) #(0 0 0 0 0))))

(define-test test--fill-managed-simple-vector--run-expect-vector-is-filled
  (let* ((success t)
         (v (ab::allocate-managed-simple-vector 5)))
    (ab::fill-managed-simple-vector v 0 0 5)
    (assert-equalp #(0 0 0 0 0) v)
    (dolist (entry *fill-managed-simple-vector-test-data*)
      (destructuring-bind (args expected-value) entry
        (apply 'ab::fill-managed-simple-vector v 1 args)
        (unless (equalp v expected-value)
          (show-expr `("failed" ,@entry))
          (setf success nil))
        (ab::fill-managed-simple-vector v 0 0 5)))
    (ab::reclaim-managed-simple-vector v)
    (assert-true success)))


;;;; Managed Array Specification

(define-test test--make-partial-buffer-info--call--check-result-layout-and-accessors
  (let ((array (ab::make-partial-buffer-info 10 20 30 40)))
    (assert-equalp '#(10 20 30 40) array)
    (assert-equal (eval `(ab::partial-buffer-max-size ,array)) 10)
    (assert-equal (eval `(ab::partial-buffer-grouping-factor ,array)) 20)
    (assert-equal (eval `(ab::partial-buffer-pool-offset ,array)) 30)
    (assert-equal (eval `(ab::partial-buffer-group-shift ,array)) 40)))

(define-test test--buffer-size-for-partial-buffer--give-managed-array-allocation-scheme--check-results-written-in-comment
  (let* ((success t)
         (needed-sizes--buffer-sizes--multiples-of
          '((0 1 1) ; special case 
            (1 1 1)
            (7 7 1)
            (8 8 1)
            (9 12 4)
            (12 12 4)
            (27 28 4)
            (29 32 4)
            (31 32 4)
            (33 40 8)
            (41 48 8)
            (49 56 8)
            (65 80 8)
            (66 80 16)
            (81 96 16)
            (256 256 16)
            (1023 1024 1)
            (1024 1024 1) ; maximum size (found experimentally, no words in docs about it.
                          ; it looks like we have some margin after 256 which is maximal actual value to use
                          ; this is not so good
            #-development
            (1025 1025 1)))) ; too large - allocation scheme failure and cerror in dev. mode
    (dolist (entry needed-sizes--buffer-sizes--multiples-of)
      (destructuring-bind (needed-size expected-buffer-size multiple-of) entry
        (let ((buffer-size (ab::buffer-size-for-partial-buffer needed-size ab::managed-array-allocation-schemes)))
          (unless (zerop (mod expected-buffer-size multiple-of))
            (show-expr `("failed: expected buffer size is not a multiple of a number given in the comment"
                         ,expected-buffer-size))
            (setf success nil))
          (unless (= buffer-size expected-buffer-size)
            (show-expr `("failed: returned wrong size" ,needed-size))
            (setf success nil)))))
    (assert-true success)))

;;; dotimes limit for some functions which test managed-array pool calculations
(defparameter *buffer-size-and-pool-for-partial-buffer-limit*
  (+ 1 1024 ; we think 256 is real limit of intended use of all these functions 
     ))

(define-test test--buffer-size-for-partial-buffer--give-managed-array-allocation-scheme-and-any-size--check-length-is-sufficient
  (let ((success t))
    (dotimes (needed-size *buffer-size-and-pool-for-partial-buffer-limit*)
      (unless
          (<= needed-size (ab::buffer-size-for-partial-buffer needed-size ab::managed-array-allocation-schemes))
        (show-expr `("failed" ,needed-size))
        (setf success nil)))
    (assert-true success)))


(define-test test--buffer-size-and-pool-for-partial-buffer--give-values--expect-that-coincides-with-buffer-size-for-partial-buffer
  (let ((success t))
    (dotimes (needed-size *buffer-size-and-pool-for-partial-buffer-limit*)
      (unless
          (= (ab::buffer-size-for-partial-buffer needed-size ab::managed-array-allocation-schemes)
             (ab::buffer-size-and-pool-for-partial-buffer needed-size ab::managed-array-allocation-schemes))
        (show-expr `("failed" ,needed-size))
        (setf success nil)))
    (assert-true success)))

;;; If we have the same size, we must have the same pool
(define-test test--buffer-size-and-pool-for-partial-buffer--give-values--expect-that-pool-is-a-function-of-given-size
  (let ((success t)
        pool-size
        pool
        (pool-size-to-pool (make-hash-table :test 'eql))
        old-pool
        (limit *buffer-size-and-pool-for-partial-buffer-limit*))
    (dotimes (needed-size limit)
      (multiple-value-setq (pool-size pool)
          (ab::buffer-size-and-pool-for-partial-buffer needed-size ab::managed-array-allocation-schemes))
      (setf old-pool (gethash pool-size pool-size-to-pool))
      (cond
       (old-pool
        (unless (= old-pool pool)
          (show-expr `("failed" ,needed-size))
          (setf success nil)))
       (t
        (setf (gethash pool-size pool-size-to-pool) pool))))
  (assert-true success)))


(defun aux-fn-test--partial-buffer-pool-index-given-length--give-value--expect-that-coincides-with-buffer-size-and-pool-for-partial-buffer (needed-size)
  (let ((index1
         (nth-value
          1
          (ab::buffer-size-and-pool-for-partial-buffer needed-size ab::managed-array-allocation-schemes)))
        (index2
         (ab::partial-buffer-pool-index-given-length needed-size ab::managed-array-allocation-schemes)))
    (= index1 index2)))
  

(define-test test--partial-buffer-pool-index-given-length--give-non-zero-value--expect-that-coincides-with-buffer-size-and-pool-for-partial-buffer
  (let ((success t))
    (dotimes (needed-size *buffer-size-and-pool-for-partial-buffer-limit*)
      (unless (= needed-size 0) ; this is a special case, see test--partial-buffer-pool-index-given-length--give-0--expect-that-coincides-with-buffer-size-and-pool-for-partial-buffer
        (unless
            (aux-fn-test--partial-buffer-pool-index-given-length--give-value--expect-that-coincides-with-buffer-size-and-pool-for-partial-buffer needed-size)        
          (show-expr `("failed" ,needed-size))
          (setf success nil))))
    (assert-true success)))


#-exclude-possible-bugs
(define-test test--partial-buffer-pool-index-given-length--give-0--expect-that-coincides-with-buffer-size-and-pool-for-partial-buffer
 (assert-true
  (aux-fn-test--partial-buffer-pool-index-given-length--give-value--expect-that-coincides-with-buffer-size-and-pool-for-partial-buffer 0)))

(define-test test--gensym-list-maximum-buffer-sizes--pass-values--expect-result-as-in-the-past
  (with-simplest-test-environment ()
      (assert-equal '(0 1 2 3 4 5 6 7 8
                        12 16 20 24 28 32 40 48 56 64
                        80 96 112 128 160 192 224 256
                        320 384 448 512 640 768 896 1024)
                    (ab::gensym-list-maximum-buffer-sizes ab::managed-array-allocation-schemes))))

;; See also test--svref-and-managed-array-alignment--make-array-fill-it--expect-correct-alignment-and-data
(define-test test--managed-array--imitate-small-array--check-type-and-layout
  (let ((imitated-managed-array (vector ab::managed-array-unique-marker 2 'a 'b)))
    (assert-true (eval `(ab::managed-array-p ,imitated-managed-array)))
    ;; check that random array is not a managed array
    (assert-false (eval `(ab::managed-array-p #(1 2 3))))
    (assert-eq (eval `(ab::managed-array-identity-marker ,imitated-managed-array)) ab::managed-array-unique-marker)
    (assert-eql (eval `(ab::managed-array-length ,imitated-managed-array)) 2)
    ;; check constant index
    (assert-eq (eval `(ab::managed-array-buffer ,imitated-managed-array 1)) 'b)
    ;; check variable index
    (assert-eq (eval `(ab::managed-array-buffer ,imitated-managed-array (read-from-string "0"))) 'a)))


(define-test test--allocate-managed-array--create-small-array--check-layout
  (let* ((ordered-length 2)
         (v (ab::allocate-managed-array ordered-length))
	 (result (ab::managed-array-p v)))
    (assert-true result)
    (assert-eq (ab::managed-array-identity-marker v) ab::managed-array-unique-marker)
    (assert-eql (ab::managed-array-length v) 2)
    ;; check it was initialized by nils
    (let ((result
	   (dotimes (i ordered-length)
	     (unless (eq (ab::managed-array-buffer v 0) nil)
	       (return :failed)))))
      (assert-false result))
    (assert-true (<= (+ 2 ordered-length) (length v)))))

(define-test test--allocate-managed-array--not-initialize--check-not-initialized
  ;; we rely upon stack discipline of allocator
  ;; setup 
  (let* ((ordered-length 8)
         (v (ab::allocate-managed-array ordered-length))
         vv)
    (setf (ab::managed-array-buffer v 0) 123)
    (ab::reclaim-managed-array v)
    ;; run 
    ;; now re-allocate the same v, but do not initialize it
    (setf vv (ab::allocate-managed-array ordered-length t))
    ;; if this assertion fails, our test is incorrect
    (assert-eq v vv)
    ;; is there really a garbage in the array? 
    (assert-eql (ab::managed-array-buffer v 0) 123)))


(defparameter *size-of-service-information-in-managed-array* 2) ; known from implementation details

;;; allocate-managed-simple-vector which implements allocation of buffers for
;;; managed-arrays. Make sure that vector is taken from an appropriate pool
(define-test test--allocate-managed-array--allocate-reclaim-allocate--expect-right-pool
 (let ((ab::cons-checking-enabled-p nil))
  (with-initialized-managed-simple-vector-allocator
   (let* ((success t)
         (sizes (ab::gensym-list-maximum-buffer-sizes ab::managed-array-allocation-schemes)))
    (dolist (buffer-size sizes)
      (when (>= buffer-size *size-of-service-information-in-managed-array*)
        (let* ((ordered-length (- buffer-size *size-of-service-information-in-managed-array*))
               (v (ab::allocate-managed-array ordered-length))
               (no-of-vectors-1 (aux-fn-number-of-reclaimed-simple-vectors-of-size buffer-size))
               (dummy1 (ab::reclaim-managed-array v))
               (no-of-vectors-2 (aux-fn-number-of-reclaimed-simple-vectors-of-size buffer-size))
               (v2 (ab::allocate-managed-array ordered-length))
               (no-of-vectors-3 (aux-fn-number-of-reclaimed-simple-vectors-of-size buffer-size))
               (dummy2 (ab::reclaim-managed-array v))
               (no-of-vectors-4 (aux-fn-number-of-reclaimed-simple-vectors-of-size buffer-size)))
          (unless (and (= no-of-vectors-1 no-of-vectors-3)
                       (= no-of-vectors-2 no-of-vectors-4)
                       (= (+ 1 no-of-vectors-1) no-of-vectors-2))
            (show-expr `("failed" ,buffer-size))
            (setf success nil)))))
    (assert-true success)))))

(defmacro with-initialized-managed-simple-vector-allocator (&body body)
  `(let ((ab::vector-of-simple-vector-pools (ab::allocate-initial-managed-simple-vector-pool-array nil))
         (ab::simple-vector-pool-counts
          (ab::allocate-initial-managed-simple-vector-pool-array 0))
         (ab::vector-of-oversized-simple-vector-pools (ab::allocate-initial-managed-simple-vector-pool-array nil))
         (ab::oversized-simple-vector-pool-counts (ab::allocate-initial-managed-simple-vector-pool-array 0)))
     ,@body))


;;; v is a managed array. buffer-sizes are items of type (buffer-size increment). Each simple vector's 
;;; pool's size must grow by that increment after reclaiming the array. And total 
(defun aux-fn-does-reclaimed-managed-array-fall-into-right-pools (length buffer-sizes)
  (with-initialized-managed-simple-vector-allocator
    (let* ((success t)
           (v (ab::allocate-managed-array length))
           (total-increment 0)
           (old-counts
            (loop :for (buffer-size increment) :in buffer-sizes
                  :do (incf total-increment increment)
                  :collect (aux-fn-number-of-reclaimed-simple-vectors-of-size buffer-size)))
           (old-total (ab::outstanding-simple-vector-pool-vectors))
           (dummy1 (ab::reclaim-managed-array v))
           (dummy2
            (setf
             success
             (and success (validate-simple-vector-pools))))
           (failed-sizes
            (loop :for (buffer-size increment) :in buffer-sizes
                  :for old-count :in old-counts
                  :for new-count = (aux-fn-number-of-reclaimed-simple-vectors-of-size buffer-size)
                  :unless (= (+ old-count increment) new-count)
                  :collect buffer-size))
           (new-total (ab::outstanding-simple-vector-pool-vectors)))
      (declare (ignore dummy1 dummy2))
      (unless (null failed-sizes)
        (show-expr `("failed:" ,length ,buffer-sizes ,failed-sizes))
        (setf success nil))
      (unless (= old-total (+ new-total total-increment))
        ;;(break)
        (show-expr `("failed: total count mismatch" ,length ,buffer-sizes)))
      success)))

(define-test test--allocate-managed-array--deallocate--expect-right-pools
  ;; compare to test--svref-and-managed-array-alignment--make-array-fill-it--expect-correct-alignment-and-data
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 2 '((4 1))))
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 9 '((12 1))))
  (assert-eql 1022 ab::maximum-in-place-array-size)
  (assert-eql 1024 (+ *size-of-service-information-in-managed-array* 1022) ab::maximum-in-place-array-size)
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 1022 '((1024 1))))
   ;; array of size 1022 fills buffer of size 1024. Next size of 1023 is allocated in chunks
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 1023 '((3 1) (1024 1))))
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 1024 '((3 1) (1024 1))))
   ;; at the size 1025, first chunk is exhasted and second chunk is allocated
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 1025 '((4 1) (1024 1) (1 1))))
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 1026 '((4 1) (1024 1) (2 1))))
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 2048 '((4 1) (1024 2))))
   ;; at 2049, third chunk is allocated
  (assert-true (aux-fn-does-reclaimed-managed-array-fall-into-right-pools 2049 '((5 1) (1024 2) (1 1))))
   ;; maximum advertised size of managed array
  (assert-eql ab::maximum-managed-array-size 1046528) ; if it fails, our test is wrong
  (assert-true
   (aux-fn-does-reclaimed-managed-array-fall-into-right-pools ab::maximum-managed-array-size
                                                              '((1024
                                                                 1023 ; 1022 chunks and one top-level vector
                                                                 )))))

(define-test test--managed-array-length--create--test-length-is-as-expected
   (with-initialized-managed-simple-vector-allocator
     (let ((success t))
       (dolist (size '(5 267 1025 10000))
         (let* ((v (ab::allocate-managed-array size)))
           ;(ab::fill-managed-array v 7778)
           (unless (= size (ab::managed-array-length v))
             (show-expr `("failed:" ,size))
             (setf success nil))
           (ab::reclaim-managed-array v)))
       (assert-true success))))


(define-test test--fill-managed-array--fill--check-is-filled
   (with-initialized-managed-simple-vector-allocator
     (let ((success t))
       (dolist (size '(5 267 1025 10000))
         (let* ((v (ab::allocate-managed-array size)))
           (ab::fill-managed-array v 7778)
           (dotimes (i size)
             (unless (= (ab::managed-svref v i) 7778)
               (show-expr `("failed:" ,size ,i))
               (setf success nil)))
           (ab::reclaim-managed-array v)))
       (assert-true success))))

(define-test test--reclaim-managed-array--deallocate-array-containing-vector--make-sure-allocator-is-not-confused
  (with-initialized-managed-simple-vector-allocator
    (let ((success t))
      (dolist (size '(5 267 1025 10000))
        (let* ((v (ab::allocate-managed-array size)))
          (ab::fill-managed-array v (vector 1 2 3))
          (ab::reclaim-managed-array v)
          (unless (validate-simple-vector-pools)
            (show-expr `("failed:" ,size))
            (setf success nil)
            ;(return)
            )))
      (assert-true success))))
  
;; our test is writing. literal arrays cause long log of warnings in SBCL and then test fails
#|(defun aux-fn-fill-array-from-0-to-end-by-eval-constant-index-literal-array (v)
  (dotimes (i (ab::managed-array-length v))
    (eval `(setf (ab::managed-svref ,v ,i) ,i))))
 (defun aux-fn-fill-array-from-0-to-end-no-eval-variable-index-literal-array (v)
  (dotimes (i (ab::managed-array-length v))
    (eval `(setf (ab::managed-svref ,v (read-from-string (prin1-to-string ,i))) ,i))))

 (defun aux-fn-fill-array-from-0-to-end-by-eval-constant-index-variable-array (v)
  (dotimes (i (ab::managed-array-length v))
    (eval
     `(let ((v ,v))
        (setf (ab::managed-svref v ,i) ,i)))))

 (defun aux-fn-fill-array-from-0-to-end-no-eval-variable-index-variable-array (v)
  (dotimes (i (ab::managed-array-length v))
    (eval
     `(let ((v ,v))
        (setf (ab::managed-svref v (read-from-string (prin1-to-string ,i))) ,i)))))|#

(defun aux-fn-fill-array-from-0-to-end (managed-array)
  (dotimes (i (ab::managed-array-length managed-array))
    (setf (ab::managed-svref managed-array i) i)))

(defun managed-svref-fn (managed-array i)
  (ab::managed-svref managed-array i))

(defun aux-fn-array-from-0-to-end-p (managed-array)
  (dotimes (i (ab::managed-array-length managed-array))
    (unless (eql (managed-svref-fn managed-array i) i)
      (return-from aux-fn-array-from-0-to-end-p nil)))
  t)

(defparameter *sample-managed-arrays*
  ;; length and array to compare
  `((2 ,(vector ab::managed-array-unique-marker 2 0 1))
    (9 ,(vector ab::managed-array-unique-marker 9 0 1 2 3 4 5 6 7 8 NIL))
    ;; 1022 is last "small" array which is implemented by a simple-vector
    (1022 ,(vector ab::managed-array-unique-marker 1022 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
            21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46
            47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72
            73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98
            99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118
            119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138
            139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158
            159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178
            179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198
            199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218
            219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238
            239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258
            259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278
            279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298
            299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318
            319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338
            339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358
            359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378
            379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398
            399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418
            419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438
            439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458
            459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478
            479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498
            499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518
            519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538
            539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558
            559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578
            579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598
            599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618
            619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638
            639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658
            659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678
            679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698
            699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718
            719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738
            739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758
            759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778
            779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798
            799 800 801 802 803 804 805 806 807 808 809 810 811 812 813 814 815 816 817 818
            819 820 821 822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838
            839 840 841 842 843 844 845 846 847 848 849 850 851 852 853 854 855 856 857 858
            859 860 861 862 863 864 865 866 867 868 869 870 871 872 873 874 875 876 877 878
            879 880 881 882 883 884 885 886 887 888 889 890 891 892 893 894 895 896 897 898
            899 900 901 902 903 904 905 906 907 908 909 910 911 912 913 914 915 916 917 918
            919 920 921 922 923 924 925 926 927 928 929 930 931 932 933 934 935 936 937 938
            939 940 941 942 943 944 945 946 947 948 949 950 951 952 953 954 955 956 957 958
            959 960 961 962 963 964 965 966 967 968 969 970 971 972 973 974 975 976 977 978
            979 980 981 982 983 984 985 986 987 988 989 990 991 992 993 994 995 996 997 998
            999 1000 1001 1002 1003 1004 1005 1006 1007 1008 1009 1010 1011 1012 1013 1014
            1015 1016 1017 1018 1019 1020 1021))
    ;; at 1023, array is implemented with one chunk
    (1023 ,(vector ab::managed-array-unique-marker 1023
            #(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
                29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54
                55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
                81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104
                105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123
                124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142
                143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161
                162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180
                181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199
                200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218
                219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237
                238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256
                257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275
                276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294
                295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313
                314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332
                333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351
                352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370
                371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389
                390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408
                409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427
                428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446
                447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465
                466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484
                485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503
                504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522
                523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541
                542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560
                561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579
                580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598
                599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617
                618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636
                637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655
                656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674
                675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693
                694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712
                713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731
                732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750
                751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769
                770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788
                789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807
                808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826
                827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845
                846 847 848 849 850 851 852 853 854 855 856 857 858 859 860 861 862 863 864
                865 866 867 868 869 870 871 872 873 874 875 876 877 878 879 880 881 882 883
                884 885 886 887 888 889 890 891 892 893 894 895 896 897 898 899 900 901 902
                903 904 905 906 907 908 909 910 911 912 913 914 915 916 917 918 919 920 921
                922 923 924 925 926 927 928 929 930 931 932 933 934 935 936 937 938 939 940
                941 942 943 944 945 946 947 948 949 950 951 952 953 954 955 956 957 958 959
                960 961 962 963 964 965 966 967 968 969 970 971 972 973 974 975 976 977 978
                979 980 981 982 983 984 985 986 987 988 989 990 991 992 993 994 995 996 997
                998 999 1000 1001 1002 1003 1004 1005 1006 1007 1008 1009 1010 1011 1012 1013
                1014 1015 1016 1017 1018 1019 1020 1021 1022 NIL)))
    ;; at 1025, the first chunk is exhausted and second chunk is added
    (1025 ,(vector ab::managed-array-unique-marker 1025
            #(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
                29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54
                55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
                81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104
                105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123
                124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142
                143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161
                162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180
                181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199
                200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218
                219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237
                238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256
                257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275
                276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294
                295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313
                314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332
                333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351
                352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370
                371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389
                390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408
                409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427
                428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446
                447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465
                466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484
                485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503
                504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522
                523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541
                542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560
                561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579
                580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598
                599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617
                618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636
                637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655
                656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674
                675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693
                694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712
                713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731
                732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750
                751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769
                770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788
                789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807
                808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826
                827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845
                846 847 848 849 850 851 852 853 854 855 856 857 858 859 860 861 862 863 864
                865 866 867 868 869 870 871 872 873 874 875 876 877 878 879 880 881 882 883
                884 885 886 887 888 889 890 891 892 893 894 895 896 897 898 899 900 901 902
                903 904 905 906 907 908 909 910 911 912 913 914 915 916 917 918 919 920 921
                922 923 924 925 926 927 928 929 930 931 932 933 934 935 936 937 938 939 940
                941 942 943 944 945 946 947 948 949 950 951 952 953 954 955 956 957 958 959
                960 961 962 963 964 965 966 967 968 969 970 971 972 973 974 975 976 977 978
                979 980 981 982 983 984 985 986 987 988 989 990 991 992 993 994 995 996 997
                998 999 1000 1001 1002 1003 1004 1005 1006 1007 1008 1009 1010 1011 1012 1013
                1014 1015 1016 1017 1018 1019 1020 1021 1022 1023)
            #(1024)))))

;; Test managed svref. It is macro, so use eval sometimes.
;; Fill array with numbers equal to index and read them back.      
;; See also test--allocate-managed-array--deallocate--expect-right-pools, 
;; test--managed-array--imitate-small-array--check-type-and-layout
(defun aux-fn-test--svref-and-managed-array-alignment--make-array-fill-it--expect-correct-alignment-and-data ()
  (with-initialized-managed-simple-vector-allocator
    (let ((success t))
      (dolist (entry *sample-managed-arrays*)
        (destructuring-bind (size sample) entry
          (let* ((v (ab::allocate-managed-array size)))
            (aux-fn-fill-array-from-0-to-end v)
            (unless (managed-array-equalp v sample)
              (show-expr `("failed - does not match sample" ,v ,size))
              ;;(break)
              (setf success nil))
            (unless (aux-fn-array-from-0-to-end-p v)
              (show-expr `("failed - aux-fn-array-from-0-to-end-p" ,size)))
            (ab::fill-managed-array v nil)
            (ab::reclaim-managed-array v))))
      (assert-true success))))

(define-test test--svref-and-managed-array-alignment--make-array-fill-it--expect-correct-alignment-and-data
  (aux-fn-test--svref-and-managed-array-alignment--make-array-fill-it--expect-correct-alignment-and-data))

(define-test test--managed-svref--eval-with-constant-index--expect-correct-result
  (with-initialized-managed-simple-vector-allocator
    (let* ((success t)
           (sizes '(2 9 1022 1023 1025)))
      (dolist (size sizes)
        (let ((v (ab::allocate-managed-array size)))
          ;; fill some elements of the array
          (dolist (index-plus-1 sizes)
            (let ((index (- index-plus-1 1)))
              (when (< index size)
                (setf (ab::managed-svref v index) index))))
          ;; read them with eval
          ;; to ensure constant index
          ;; and check if it is ok
          (dolist (index-plus-1 sizes)
            (let ((index (- index-plus-1 1)))
              (when (< index size)
                (unless
                    (= index (eval `(ab::managed-svref ,v ,index)))
                  (show-expr `("failed with constant index" ,size ,index))
                  (setf success nil))
                )))
          (ab::reclaim-managed-array v)))
      (assert-true success))))

#|
                (unless
                    (= index
                       (eval
                        `(let ((cons-arr (cons ,v nil)))
                           (ab::managed-svref (car cons-arr) ,index))))
                  (show-expr `("failed with non-constant array" ,size ,index)))
                (unless
                    (= index (eval `(let ((ind ,index))
                                      (ab::managed-svref ,v ind))))
                  (show-expr `("failed with symbolic index" ,size ,index))
                  (setf success nil))
                (unless
                    (= index (eval `(let ((ind ,(* 2 index)))
                                      (ab::managed-svref ,v (/ ind 2)))))
                  (show-expr `("failed with calculated index" ,size ,index))
                  (setf success nil))
|#
(define-test test--managed-svref--call-macroexpansion--1-symbolic-array-constant-index--expect-result
  (eval `(defun aux-fn-generated-by-test-managed-svref-1 (v)
           (ab::managed-svref v 3)))
  (eval `(defun aux-fn-generated-by-test-managed-svref-1a (v)
           (ab::managed-svref v 1024)))

  (eval `(defun aux-fn-generated-by-test-managed-svsetf-1 (v)
           (setf (ab::managed-svref v 3) 3)))
  (eval `(defun aux-fn-generated-by-test-managed-svsetf-1a (v)
           (setf (ab::managed-svref v 1024) 1024)))

  (with-initialized-managed-simple-vector-allocator
    (let* ((sizes '(8
                    1500 ; 1500 is (1024 + some margin)
                    )))
      (dolist (size sizes)
        (let ((v (ab::allocate-managed-array size)))
          (funcall 'aux-fn-generated-by-test-managed-svsetf-1 v)
          (assert-eql 3 (ab::managed-svref v 3))
          (assert-eql 3 (funcall 'aux-fn-generated-by-test-managed-svref-1 v))
          (when (= size 1500)
            (funcall 'aux-fn-generated-by-test-managed-svsetf-1a v)
            (assert-eql 1024 (ab::managed-svref v 1024))
            (assert-eql 1024 (funcall 'aux-fn-generated-by-test-managed-svref-1a v))
            ))))))


(define-test test--managed-svref--call-macroexpansion--2-symbolic-array-symbolic-index
  (eval `(defun aux-fn-generated-by-test-managed-svref-2 (v i)
           (ab::managed-svref v i)))
  (eval `(defun aux-fn-generated-by-test-managed-svsetf-2 (v i)
           (setf (ab::managed-svref v i) i)))
  
  (with-initialized-managed-simple-vector-allocator
    (let* ((sizes '(8
                    1500 ; 1500 is (1024 + some margin)
                    )))
      (dolist (size sizes)
        (let ((v (ab::allocate-managed-array size)))
          (funcall 'aux-fn-generated-by-test-managed-svsetf-2 v 1)
          (assert-eql 1 (ab::managed-svref v 1))
          (assert-eql 1 (funcall 'aux-fn-generated-by-test-managed-svref-2 v 1))
          
          (when (= size 1500)
            (funcall 'aux-fn-generated-by-test-managed-svsetf-2 v 1023)
            (assert-eql 1023 (ab::managed-svref v 1023))
            (assert-eql 1023 (funcall 'aux-fn-generated-by-test-managed-svref-2 v 1023)))
          (ab::reclaim-managed-array v))))))


(define-test test--managed-svref--call-macroexpansion--3-symbolic-array-calculated-index
  (eval `(defun aux-fn-generated-by-test-managed-svref-3 (v 2i)
           (ab::managed-svref v (/ 2i 2))))
  (eval `(defun aux-fn-generated-by-test-managed-svsetf-3 (v 2i)
           (setf (ab::managed-svref v (/ 2i 2)) (/ 2i 2))))
  
  (with-initialized-managed-simple-vector-allocator
    (let* ((sizes '(8
                    1500 ; 1500 is (1024 + some margin)
                    )))
      (dolist (size sizes)
        (let ((v (ab::allocate-managed-array size)))

          (funcall 'aux-fn-generated-by-test-managed-svsetf-3
                   v (* 6 2))
          (assert-eql 6 (ab::managed-svref v 6))
          (assert-eql 6
                      (funcall
                       'aux-fn-generated-by-test-managed-svsetf-3
                       v (* 6 2)))
          
          (when (= size 1500)

            (funcall 'aux-fn-generated-by-test-managed-svsetf-3 v (* 1100 2))
            (assert-eql 1100 (ab::managed-svref v 1100))
            (assert-eql 1100 (funcall 'aux-fn-generated-by-test-managed-svsetf-3 v (* 1100 2)))

            )
          (ab::reclaim-managed-array v))))))


 
(define-test test--managed-svref--call-macroexpansion--4-calculated-array-constant-index--expect-result
  (eval `(defun aux-fn-generated-by-test-managed-svref-4 (list-v)
           (ab::managed-svref (car list-v) 3)))
  (eval `(defun aux-fn-generated-by-test-managed-svref-4a (list-v)
           (ab::managed-svref (car list-v) 1024)))

  (eval `(defun aux-fn-generated-by-test-managed-svsetf-4 (list-v)
           (setf (ab::managed-svref (car list-v) 3) 3)))
  (eval `(defun aux-fn-generated-by-test-managed-svsetf-4a (list-v)
           (setf (ab::managed-svref (car list-v) 1024) 1024)))

  (with-initialized-managed-simple-vector-allocator
    (let* ((sizes '(8
                    1500 ; 1500 is (1024 + some margin)
                    )))
      (dolist (size sizes)
        (let ((v (ab::allocate-managed-array size)))
          (funcall 'aux-fn-generated-by-test-managed-svsetf-4 (list v))
          (assert-eql 3 (ab::managed-svref v 3))
          (assert-eql 3 (funcall 'aux-fn-generated-by-test-managed-svref-4 (list v)))
          (when (= size 1500)
            (funcall 'aux-fn-generated-by-test-managed-svsetf-4a (list v))
            (assert-eql 1024 (ab::managed-svref v 1024))
            (assert-eql 1024 (funcall 'aux-fn-generated-by-test-managed-svref-4a (list v)))
            ))))))


(define-test test--managed-svref--call-macroexpansion--5-symbolic-array-symbolic-index
  (eval `(defun aux-fn-generated-by-test-managed-svref-5 (v i)
           (ab::managed-svref v i)))
  (eval `(defun aux-fn-generated-by-test-managed-svsetf-5 (v i)
           (setf (ab::managed-svref v i) i)))
  
  (with-initialized-managed-simple-vector-allocator
    (let* ((sizes '(8
                    1500 ; 1500 is (1024 + some margin)
                    )))
      (dolist (size sizes)
        (let ((v (ab::allocate-managed-array size)))
          (funcall 'aux-fn-generated-by-test-managed-svsetf-5 v 1)
          (assert-eql 1 (ab::managed-svref v 1))
          (assert-eql 1 (funcall 'aux-fn-generated-by-test-managed-svref-5 v 1))
          
          (when (= size 1500)
            (funcall 'aux-fn-generated-by-test-managed-svsetf-5 v 1023)
            (assert-eql 1023 (ab::managed-svref v 1023))
            (assert-eql 1023 (funcall 'aux-fn-generated-by-test-managed-svref-5 v 1023)))
          (ab::reclaim-managed-array v))))))


(define-test test--managed-svref--call-macroexpansion--6-calculated-array-calculated-index
  (eval `(defun aux-fn-generated-by-test-managed-svref-6 (list-v 2i)
           (ab::managed-svref (car list-v) (/ 2i 2))))
  (eval `(defun aux-fn-generated-by-test-managed-svsetf-6 (list-v 2i)
           (setf (ab::managed-svref (car list-v) (/ 2i 2)) (/ 2i 2))))
  
  (with-initialized-managed-simple-vector-allocator
    (let* ((sizes '(8
                    1500 ; 1500 is (1024 + some margin)
                    )))
      (dolist (size sizes)
        (let ((v (ab::allocate-managed-array size)))

          (funcall 'aux-fn-generated-by-test-managed-svsetf-6
                   (list v) (* 6 2))
          (assert-eql 6 (ab::managed-svref v 6))
          (assert-eql 6
                      (funcall
                       'aux-fn-generated-by-test-managed-svsetf-6
                       (list v) (* 6 2)))
          
          (when (= size 1500)

            (funcall 'aux-fn-generated-by-test-managed-svsetf-6 (list v) (* 1100 2))
            (assert-eql 1100 (ab::managed-svref v 1100))
            (assert-eql 1100 (funcall 'aux-fn-generated-by-test-managed-svsetf-6 (list v) (* 1100 2)))

            )
          (ab::reclaim-managed-array v))))))

;; TRIVIAL-CODE reclaim-if-managed-array

(define-test test-gsi-allocate-managed-array
 (with-initialized-managed-simple-vector-allocator
   (let ((v (ab::gsi-allocate-managed-array 2)))
     (assert-true (typep v 'vector))
     (assert-eql 2 (length v)) ; nothing more is guaranteed
     (ab::gsi-reclaim-managed-array v))
   (let ((vv (ab::gsi-allocate-managed-array 2049)))
     (assert-true (typep vv 'vector))
     (assert-true (> (length vv) 2050)) ; make sure vector is padded. If not, our test is bad
     (assert-eql 2049 (svref vv (- (length vv) 1))) ; length is stored at the end of the vector
     (ab::gsi-reclaim-managed-array vv))))

(define-test test-gsi-managed-array-length
 (with-initialized-managed-simple-vector-allocator
   (let* ((success t)
          (max-length 1026))
       ;; if the following assertion fails, our test is not good enough
     (assert-true (> max-length ab::maximum-managed-array-buffer-size))
     (dotimes (size (+ max-length 1))
       (unless (= size 0))
       (let ((v (ab::gsi-allocate-managed-array size)))
         (unless (= (ab::gsi-managed-array-length v) size)
           (show-expr `("failed" ,size))
           (setf success nil)
           (return))
         (ab::gsi-reclaim-managed-array v))))))

;; TRIVIAL-CODE GSI-RECLAIM-MANAGED-ARRAY
;; TRIVIAL-CODE GSI-ALLOCATE-INTEGER-VECTOR
;; TRIVISL-CODE GSI-RECLAIM-INTEGER-VECTOR

;; This code created accidental coverage for trivial gsi-allocate-integer-vector
;; and gsi-reclaim-integer-vector.
;; TESTERS-COMMENT 
;; Note "integer" is assumed to be "signed-byte 32". integer-vector-aref is used in
;; context of gsi only and it is normal. If someone assume that "integer" is C integer
;; of platform where G2 is built, this will cause problems on 64-bit platforms
;;; test that integer-vector-aref is just svref
(define-test test-integer-vector-avref--read-it--expect-right-data
 (with-initialized-managed-simple-vector-allocator
   (let* ((v (ab::gsi-allocate-integer-vector 3))
          (any-number 81)
          (other-number 1974))
     (setf (svref v 2) any-number) ; magic constant
     ;; run test
     (assert-eql (eval `(ab::integer-vector-aref ,v 2)) any-number)

     (setf (ab::integer-vector-aref v 1) other-number)
     (assert-eql (svref v 1) other-number)
     
     (ab::gsi-reclaim-integer-vector v))))


;tip


;;;; Byte Vector Pool    
    
;; TESTERS-COMMENT test-copy-simple-vector-portion does not check bounds in production

(defun test-copy-simple-vector-portion-fn (source-index element-count destination-index)
  "returns a list of elements in the resulting vector"
  (eval
   `(let* ((dst (make-array '(4) :initial-element 0))
           (src #(1 2 3 4)))
      (ab::copy-simple-vector-portion
       src ,source-index ,element-count dst ,destination-index)
      (coerce dst 'list))))

(define-test test-copy-simple-vector-portion-function
  (assert-true
   (every 'identity
          (list
           (equal (test-copy-simple-vector-portion-fn 0 0 0) '(0 0 0 0))
           (equal (test-copy-simple-vector-portion-fn 0 1 0) '(1 0 0 0))
           (equal (test-copy-simple-vector-portion-fn 0 2 0) '(1 2 0 0))    
           (equal (test-copy-simple-vector-portion-fn 0 3 0) '(1 2 3 0))    
           (equal (test-copy-simple-vector-portion-fn 0 4 0) '(1 2 3 4))
           (equal (test-copy-simple-vector-portion-fn 1 0 0) '(0 0 0 0))
           (equal (test-copy-simple-vector-portion-fn 1 1 0) '(2 0 0 0))
           (equal (test-copy-simple-vector-portion-fn 1 2 0) '(2 3 0 0))
           (equal (test-copy-simple-vector-portion-fn 1 3 0) '(2 3 4 0))
           (equal (test-copy-simple-vector-portion-fn 2 0 1) '(0 0 0 0))
           (equal (test-copy-simple-vector-portion-fn 2 1 1) '(0 3 0 0))
           (equal (test-copy-simple-vector-portion-fn 2 1 2) '(0 0 3 0))
           (equal (test-copy-simple-vector-portion-fn 2 2 2) '(0 0 3 4))
           (equal (test-copy-simple-vector-portion-fn 3 1 3) '(0 0 0 4))
           (equal (test-copy-simple-vector-portion-fn 3 0 3) '(0 0 0 0))
           ))))

;; TRIVISL-CODE copy-simple-vector-portion-function

;;; verifies that first N elements of array are numbers from 0 to N and then there are nils
(defun aux-fn-array-from-0-to-N-1-and-then-nil-p (managed-array length)
  (block function
    (assert (<= length (ab::managed-array-length managed-array)))
    (dotimes (i (ab::managed-array-length managed-array))
      (cond
       ((< i length)
        (unless (eql (managed-svref-fn managed-array i) i)
          (return-from function nil)))
       (t
        (unless (null (managed-svref-fn managed-array i))
          (return-from function nil)))))
    t))

;; This is not a part of the unit test suite but
;; a self test for an utility function.
(defun aux-fn-array-from-0-to-N-1-and-then-nil-p-self-test ()
  (with-initialized-managed-simple-vector-allocator
    (let ((v (ab::allocate-managed-array 4)))
      (setf (ab::managed-svref v 0) 0)
      (setf (ab::managed-svref v 1) 1)
      (setf (ab::managed-svref v 2) 2)
      (assert (not (aux-fn-array-from-0-to-n-1-and-then-nil-p v 1)))
      (assert (not (aux-fn-array-from-0-to-n-1-and-then-nil-p v 2)))
      (assert (aux-fn-array-from-0-to-n-1-and-then-nil-p v 3))
      (assert (not (aux-fn-array-from-0-to-n-1-and-then-nil-p v 4)))
      )))

(aux-fn-array-from-0-to-N-1-and-then-nil-p-self-test)

(defun aux-fn-set-0-to-nil (v)
  (setf (svref v 0) nil)
  v)

(defun aux-fn-set-1023-to-uninitialized (v)
  (setf (svref v 1023) :uninitialized)
  v)

;; list of adjust-managed-array tests
;;    3    3 test--adjust-managed-array--same-length--expect--ok
;;    3    4 test--adjust-managed-array--small-growing--expect-ok
;; 1020 1022 test--adjust-managed-array--small-growing-without-reallocation--expect-ok
;;    3 1023 test--adjust-managed-array--small-growing-to-large--expect-ok
;; 1025 1026 test--adjust-managed-array--large-growing-to-larger-not-adding-buffer-reallocating-buffer--expect-ok
;; 1025 2048 test--adjust-managed-array--large-growing-to-large-to-full-buffer-not-adding-buffer-reallocating-buffer--expect-ok
;; 1023 1025 test--adjust-managed-array--large-growing-to-larger-not-full-buffer-adding-buffer--expect-ok
;; 1023 2048 test--adjust-managed-array--large-growing-to-larger-add-buffer-to-full--expect-ok
;; 2048 2049 test--adjust-managed-array--large-growing-to-larger-full-to-not-full-buffer-adding-buffer--expect-ok
;; 1023 2049 test--adjust-managed-array--large-growing-to-larger-add-more-than-one-buffer--expect-ok

;;    4    3 test--adjust-managed-array--small-shrinking--expect-ok
;; 2048 1023 test--adjust-managed-array--large-shrinking-to-large-deleting-buffer--expect-ok
;; 1023    3 test--adjust-managed-array--large-shrinking-to-small--expect-ok
;; 2048 1025 test--adjust-managed-array--large-shrinking-to-large-full-to-not-full-not-deleting-buffer--expect-ok
;; 2049 2048 test--adjust-managed-array--large-shrinking-to-large-not-full-to-full-deleting-buffer--expect-ok
;;    3    0 test--adjust-managed-array--adjust-to-zero--expect-returned-array

;;; The idea of adjust-managed-array is to share buffers of
;;; old array to the new one when possible. We test it mocking vector (de)allocation.
;; Mocking is not good as it freezes the array layout, but this is unit testing :) 
(defun aux-fn-adjust-managed-array (from-size to-size)
  (let* ((success t)
         (v (ab::allocate-managed-array from-size))
         (adjusted-v nil)
         (filled-length (min from-size to-size)))
    (aux-fn-fill-array-from-0-to-end v)
    (setf adjusted-v (ab::adjust-managed-array v to-size))
    (unless
        (aux-fn-array-from-0-to-n-1-and-then-nil-p adjusted-v filled-length)
      `(show-expr ("failed" ,from-size ,to-size))
      (setf success nil))
    (ab::reclaim-managed-array adjusted-v)
    success))

(define-test test--adjust-managed-array--same-length--expect--ok
  (with-initialized-managed-simple-vector-allocator             
    (assert-true (aux-fn-adjust-managed-array 3 3))))

(define-test test--adjust-managed-array--small-growing--expect-ok
  (mock::expect 
   ((:call (ab::allocate-managed-simple-vector 5) :return ('#(a b c d e)))
    (:call (ab::allocate-managed-simple-vector 6) :return ('#(f g h i j k)))
    (:call (ab::reclaim-managed-simple-vector #(nil 3 0 1 2)) :return nil)
    (:call (ab::reclaim-managed-simple-vector #(nil 4 0 1 2 nil)) :return nil))
   :for
   (assert-true (aux-fn-adjust-managed-array 3 4))))

(define-test test--adjust-managed-array--small-growing-without-reallocation--expect-ok
  (with-initialized-managed-simple-vector-allocator
    (let* ((old (ab::allocate-managed-array 1020))
           (dummy1 (aux-fn-fill-array-from-0-to-end old))
           (new (ab::adjust-managed-array old 1022)))
      (assert-eq old new)
      (assert-true
       (aux-fn-array-from-0-to-n-1-and-then-nil-p new 1020)))))
          
(define-test test--adjust-managed-array--small-growing-to-large--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 5) :return ('#(a b c d e)))
   ;; allocation of resized vector
   (:call (ab::allocate-managed-simple-vector 3) :return ('#(f g h)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((aux-fn-set-1023-to-uninitialized
      (vector-of-gensyms 1024 "NW-" 0))))
   ;; deallocation of initial vector
   (:call (ab::reclaim-managed-simple-vector #(nil 3 0 1 2)) :return nil)
   ;; deallocation of resized vector
   (:call (ab::reclaim-managed-simple-vector
           (aux-fn-set-1023-to-uninitialized
            (vector-0-N-minus-1-then-nils 1024 3)))
    :return nil)
   ;; Slight problem here. In real world, deallocator might modify the zeroth element
   ;; of vector being reclaimed, so thid element below would contain nil (or any 
   ;; other value). Our mock doesn't do that, so the value passed here is different
   ;; from what would be passed in real world
   ;; <<compare to
   ;; (trace ab::reclaim-managed-simple-vector ab::allocate-managed-simple-vector)
   ;; (aux-fn-adjust-managed-array 3 1023)
   ;; >>
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 1023
                   (aux-fn-set-1023-to-uninitialized
                    (vector-0-N-minus-1-then-nils 1024 3))))
    :return nil)
   )
  :for
  (assert-true (aux-fn-adjust-managed-array 3 1023))))


(define-test test--adjust-managed-array--large-growing-to-larger-not-adding-buffer-reallocating-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 4) :return ('#(f g h i)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 0)))
   (:call (ab::allocate-managed-simple-vector 1)
    :return
    ((vector-of-gensyms 1 "INITIAL-" 1024)))

   ;; allocation of a new buffer for a resized vector
   (:call (ab::allocate-managed-simple-vector 2) :return (#(j h)))

   ;; reclaiming of an old last buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1 1024)))

   ;;; reclaiming of resized vector
   ;; first buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 0))
    :return nil)
   ;; second buffer
   (:call (ab::reclaim-managed-simple-vector #(1024 nil))
    :return nil)
   ;; root structure

   ;; IRR, deallocator would modify both buffers setting something to their
   ;; first element
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 1026
            (vector-from-k 1024 0)
            #(1024 nil)))
    :return nil)
   )
  :for 
  (assert-true (aux-fn-adjust-managed-array 1025 1026))))


(define-test test--adjust-managed-array--large-growing-to-large-to-full-buffer-not-adding-buffer-reallocating-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 4) :return ('#(f g h i)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 0)))
   (:call (ab::allocate-managed-simple-vector 1)
    :return (#(z)))

   ;; allocation of a new buffer for a resized vector
   (:call (ab::allocate-managed-simple-vector 1024) :return
    ((vector-of-gensyms 1024 "INITIAL-" 1024)))

   ;; reclaiming of an old last buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1 1024)))

   ;;; reclaiming of resized vector
   ;; first buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 0))
    :return nil)
   ;; second buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-k---k+N-minus-1--then-nils 1024 1024 1))
    :return nil)
   ;; root structure

   ;; IRR, deallocator would modify both buffers setting something to their
   ;; first element
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 2048
            (vector-from-k 1024 0)
            (vector-k---k+N-minus-1--then-nils 1024 1024 1)))
    :return nil)
   )
  :for 
  (assert-true (aux-fn-adjust-managed-array 1025 2048))))


(define-test test--adjust-managed-array--large-growing-to-larger-not-full-buffer-adding-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 3) :return ('#(f g h)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((aux-fn-set-1023-to-uninitialized
      (vector-of-gensyms 1024 "INITIAL-" 0))))

   ;; allocation of root structure for a resized vector
   (:call (ab::allocate-managed-simple-vector 4) :return ('#(a b c d)))
   
   ;; deallocation of initial vector root structure
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 1023 (vector-0-n-minus-1-then-nils 1024 1023)))
    :return nil)

   ;; allocation of and additional buffer for a resized vector
   (:call (ab::allocate-managed-simple-vector 1) :return (#(i)))

   ;;; reclaiming of resized vector
   ;; first buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-0-n-minus-1-then-nils 1024 1023))
    :return nil)
   ;; second buffer
   (:call (ab::reclaim-managed-simple-vector #(nil))
    :return nil)
   ;; root structure

   ;; IRR, deallocator would modify both embedded vectors
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 1025
            (vector-0-n-minus-1-then-nils 1024 1023)
            #(nil)))
    :return nil)
   )
  :for 
  (assert-true (aux-fn-adjust-managed-array 1023 1025))))

(define-test test--adjust-managed-array--large-growing-to-larger-full-to-not-full-buffer-adding-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 4) :return ('#(f g h i)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 0)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 1024)))

   ;; allocation of root structure for a resized vector
   (:call (ab::allocate-managed-simple-vector 5) :return ('#(a b c d e)))
   
   ;; deallocation of initial vector root structure
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 2048
                   (vector-from-k 1024 0)
                   (vector-from-k 1024 1024)))
    :return nil)

   ;; allocation of and additional buffer for a resized vector
   (:call (ab::allocate-managed-simple-vector 1) :return (#(i)))

   ;;; reclaiming of resized vector
   ;; first buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 0))
    :return nil)
   ;; second buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 1024))
    :return nil)
   ;; third buffer
   (:call (ab::reclaim-managed-simple-vector #(nil))
    :return nil)
   ;; root structure

   ;; IRR, deallocator would modify both embedded vectors
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 2049
            (vector-from-k 1024 0)
            (vector-from-k 1024 1024)
            #(nil)))
    :return nil)
   )
  :for 
  (assert-true (aux-fn-adjust-managed-array 2048 2049))))

;; 1023 2048
(define-test test--adjust-managed-array--large-growing-to-larger-add-buffer-to-full--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 3) :return ('#(f g h)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((aux-fn-set-1023-to-uninitialized
      (vector-of-gensyms 1024 "INITIAL-" 0))))

   ;; allocation of a spine for a resized vector
   (:call (ab::allocate-managed-simple-vector 4) :return ('#(a b c d)))
   
   ;; deallocation of initial vector spine
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 1023
                   (vector-0-n-minus-1-then-nils 1024 1023)
                   ))
    :return nil)

   ;; allocation of an additional buffer for a resized vector
   (:call (ab::allocate-managed-simple-vector 1024)
    :return ((vector-of-gensyms 1024 "FINAL-" 1024)))

   ;;; reclaiming of resized vector
   ;; first buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-0-n-minus-1-then-nils 1024 1023))
    :return nil)
   ;; second buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-0-n-minus-1-then-nils 1024 0))
    :return nil)

   ;; spine
   ;; IRR, deallocator would modify both embedded vectors
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 2048
            (vector-0-n-minus-1-then-nils 1024 1023)
            (vector-0-n-minus-1-then-nils 1024 0)
            ))
    :return nil))
  :for 
  (assert-true (aux-fn-adjust-managed-array 1023 2048))))

;; 1023 2049 
(define-test test--adjust-managed-array--large-growing-to-larger-add-more-than-one-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 3) :return ('#(f g h)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((aux-fn-set-1023-to-uninitialized
      (vector-of-gensyms 1024 "INITIAL-" 0))))

   ;; allocation of a spine for a resized vector
   (:call (ab::allocate-managed-simple-vector 5) :return ('#(a b c d e)))
   
   ;; deallocation of initial vector spine
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 1023
                   (vector-0-n-minus-1-then-nils 1024 1023)
                   ))
    :return nil)

   ;; allocation of an additional buffers for a resized vector
   (:call (ab::allocate-managed-simple-vector 1024)
    :return ((vector-of-gensyms 1024 "FINAL-" 1024)))
   (:call (ab::allocate-managed-simple-vector 1) :return (#(i)))

   ;;; reclaiming of resized vector
   ;; first buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-0-n-minus-1-then-nils 1024 1023))
    :return nil)
   ;; second buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-0-n-minus-1-then-nils 1024 0))
    :return nil)
   ;; third buffer
   (:call (ab::reclaim-managed-simple-vector #(nil))
    :return nil)
   ;; spine

   ;; IRR, deallocator would modify both embedded vectors
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 2049
            (vector-0-n-minus-1-then-nils 1024 1023)
            (vector-0-n-minus-1-then-nils 1024 0)
            #(nil)))
    :return nil)
   )
  :for 
  (assert-true (aux-fn-adjust-managed-array 1023 2049))))

#|(define-test i-m-tired-of-it
             (aux-fn-adjust-managed-array 1023 4096)
             (aux-fn-adjust-managed-array 1023 4095)
             (aux-fn-adjust-managed-array 1023 4097)
             )                         |#


(define-test test--adjust-managed-array--small-shrinking-without-reallocation
  (with-initialized-managed-simple-vector-allocator
    (let* ((old (ab::allocate-managed-array 1022))
           (dummy1 (aux-fn-fill-array-from-0-to-end old))
           (new (ab::adjust-managed-array old 1020)))
      (assert-eq old new)
      (assert-true
       (aux-fn-array-from-0-to-n-1-and-then-nil-p new 1020)))))

(define-test test--adjust-managed-array--small-shrinking--expect-ok
  (mock::expect 
   ((:call (ab::allocate-managed-simple-vector 6) :return ('#(g h i j e f)))
    (:call (ab::allocate-managed-simple-vector 5) :return ('#(a b c d e)))
    (:call (ab::reclaim-managed-simple-vector #(nil 4 0 1 2 3)) :return nil)
    (:call (ab::reclaim-managed-simple-vector #(nil 3 0 1 2)) :return nil))
   :for
   (assert-true (aux-fn-adjust-managed-array 4 3))))

(define-test test--adjust-managed-array--large-shrinking-to-large-deleting-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 4) :return ('#(f g h i)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 0)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 1024)))

   ;; deallocation of unnecessary buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 1024))
    :return nil)

   ;; allocation of root structure for a resized vector
   (:call (ab::allocate-managed-simple-vector 3) :return ('#(a b c)))
   
   ;; deallocation of initial vector root structure
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 2048
                   (vector-from-k 1024 0)
                   (vector-from-k 1024 1024)))
    :return nil)

   ;;; reclaiming of resized vector
   ;; buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 0))
    :return nil)

   ;; root structure

   ;; IRR, deallocator would modify buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 1023
            (vector-from-k 1024 0)
            ))
    :return nil)
   )
  :for 
  (assert-true (aux-fn-adjust-managed-array 2048 1023))))

(define-test test--adjust-managed-array--large-shrinking-to-small--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 3) :return ('#(f g h)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((aux-fn-set-1023-to-uninitialized
      (vector-of-gensyms 1024 "NW-" 0))))
   ;; allocation of resized vector
   (:call (ab::allocate-managed-simple-vector 5) :return ('#(a b c d e)))
   ;; deallocation of initial vector
   (:call (ab::reclaim-managed-simple-vector
           (aux-fn-set-1023-to-uninitialized
            (vector-0-N-minus-1-then-nils 1024 1024)))
    :return nil)
   ;; slight problem here, see test--adjust-managed-array--small-growing-to-large--expect-ok
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 1023
                   (aux-fn-set-1023-to-uninitialized
                    (vector-0-N-minus-1-then-nils 1024 1024))))
    :return nil)
   ;; deallocation of resized vector
   (:call (ab::reclaim-managed-simple-vector #(nil 3 0 1 2)) :return nil)
   )
  :for
  (assert-true (aux-fn-adjust-managed-array 1023 3))))


(define-test test--adjust-managed-array--large-shrinking-to-large-full-to-not-full-not-deleting-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 4) :return ('#(f g h i)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 0)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 1024)))

   ;; allocation of new buffer
   (:call (ab::allocate-managed-simple-vector 1) :return ('#(a)))

   ;; deallocation of unnecessary buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 1024))
    :return nil)

   ;;; reclaiming of resized vector
   ;; buffer 1
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 0))
    :return nil)
   ;; buffer 2
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1 1024))
    :return nil)

   ;; root structure

   ;; IRR, deallocator would modify buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 1025
            (vector-from-k 1024 0)
            (vector-from-k 1 1024)
            )) :return nil))
  :for
  (assert-true (aux-fn-adjust-managed-array 2048 1025))))

;; 2049 2048
(define-test test--adjust-managed-array--large-shrinking-to-large-not-full-to-full-deleting-buffer--expect-ok
 (mock::expect 
  (
   ;; allocation of initial vector
   (:call (ab::allocate-managed-simple-vector 5)
    :return ('#(f g h i j)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 0)))
   (:call (ab::allocate-managed-simple-vector 1024)
    :return
    ((vector-of-gensyms 1024 "INITIAL-" 1024)))
   (:call (ab::allocate-managed-simple-vector 1)
    :return
    (#(a)))

   ;; deallocation of unnecessary buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector 2048))
    :return nil)

   ;; allocation of a new spine
   (:call (ab::allocate-managed-simple-vector 4)
    :return ('#(a b c d)))

   ;; deallocation of an old spine
   (:call (ab::reclaim-managed-simple-vector
           (vector nil 2049
                   (vector-from-k 1024 0)
                   (vector-from-k 1024 1024)
                   ; IRR that would vector (nil or anything)
                   (vector 2048))))

   ;;; reclaiming of resized vector
   ;; buffer 1
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 0))
    :return nil)
   ;; buffer 2
   (:call (ab::reclaim-managed-simple-vector
           (vector-from-k 1024 1024))
    :return nil)

   ;; spine

   ;; IRR, deallocator would modify buffer
   (:call (ab::reclaim-managed-simple-vector
           (vector
            nil 2048
            (vector-from-k 1024 0)
            (vector-from-k 1024 1024)
            )) :return nil))
  :for
  (assert-true (aux-fn-adjust-managed-array 2049 2048))))


(define-test test--adjust-managed-array--adjust-to-zero--expect-returned-array
  (mock::expect
   (
    ;; allocation of initial vector
    (:call (ab::allocate-managed-simple-vector 5) :return ('#(a b c d e)))
    ;; allocation of adjusted vector
    (:call (ab::allocate-managed-simple-vector 2) :return ('#(f g)))
    ;; initial vector reclaimed
    (:call (ab::reclaim-managed-simple-vector #(nil 3 0 1 2)) :return nil)
    ;; adjusted vector reclaimed
    (:call (ab::reclaim-managed-simple-vector #(nil 0)) :return nil)
    )
   :for
   (assert-true (aux-fn-adjust-managed-array 3 0))))


;;; end of adjust-managed-array tests
   
;; As we have already tested adjust-managed-array, we only test the contents 
;; of vectors in most of the cases, not the allocation/deallocation
(define-test test--shrink-or-delete-managed-array--all-nils--expect-nil
  (mock::expect
   (
    ;; make sure initial vector reclaimed
    (:call (ab::reclaim-managed-simple-vector #(nil 3 nil nil nil)) :return nil)
    )
   :for
   (with-initialized-managed-simple-vector-allocator
     (let ((v (ab::allocate-managed-array 3)))
       ;(aux-fn-fill-array-from-0-to-end v)       
       (assert-false (ab::shrink-or-delete-managed-array-null-elements v))))))

(define-test test--shrink-or-delete-managed-array--not-all-nils--expect-array
  (with-initialized-managed-simple-vector-allocator
    (let ((ma (ab::allocate-managed-array 3)))
      (aux-fn-fill-array-from-0-to-end ma)
      (setf (ab::managed-svref ma 2) nil)
      (setf ma (ab::shrink-or-delete-managed-array-null-elements ma))
      (assert-true (managed-array-equal-to-vector ma #(0 1)))
      )))

(define-test test--shrink-or-delete-managed-array--no-nils--expect-the-same
  (with-initialized-managed-simple-vector-allocator
    (let ((ma (ab::allocate-managed-array 3))
          (ma2 nil))
      (aux-fn-fill-array-from-0-to-end ma)
      (setf (ab::managed-svref ma 1) nil) ; not at the end
      (setf ma2 (ab::shrink-or-delete-managed-array-null-elements ma))
      (assert-equal ma ma2)
      (assert-true (managed-array-equal-to-vector ma #(0 nil 2)))
      )))

(with-initialized-managed-simple-vector-allocator
  (assert (managed-array-equalp
           (let ((a (ab::allocate-managed-array 3)))
             (dotimes (i 3)
               (setf (ab::managed-svref a i) i)))
           (let ((a (ab::allocate-managed-array 3)))
             (dotimes (i 3)
               (setf (ab::managed-svref a i) i))))))
  

(define-test test--shrink-or-delete-managed-array-not-all-nil--expect-reasonble-result
  (with-initialized-managed-simple-vector-allocator
    (let ((v1 (ab::allocate-managed-array 3))
          (v2 (ab::allocate-managed-array 1)))
      (setf (ab::managed-svref v1 0) 1)
      (setf (ab::managed-svref v2 0) 1)
      (setf v1 (ab::adjust-managed-array v1 1))
      (assert-true (managed-array-equalp v1 v2))
      (ab::reclaim-managed-array v1)
      (ab::reclaim-managed-array v2))))

(define-test test--copy-from-simple-vector-into-managed-array--small
  (with-initialized-managed-simple-vector-allocator
    (let ((ma (ab::allocate-managed-array 3))
          (ve (vector 0 1)))
      (ab::copy-from-simple-vector-into-managed-array ve 0 2 ma 0)
      (assert-true
       (managed-array-equalp
        ma
        (vector ab::managed-array-unique-marker 3 0 1 nil)))
      (ab::copy-from-simple-vector-into-managed-array ve 1 1 ma 0)
      (assert-true
       (managed-array-equalp
        ma
        (vector ab::managed-array-unique-marker 3 1 1 nil)))
      (ab::copy-from-simple-vector-into-managed-array ve 0 2 ma 1)
      (assert-true
       (managed-array-equalp
        ma
        (vector ab::managed-array-unique-marker 3 1 0 1)))
      (ab::reclaim-managed-array ma))))

;; TESTERS-COMMENT - looks like large variant of copy-from-simple-vector-into-managed-array is covered accidentally from somewhere. Let it be.


(define-test test--copy-from-managed-array-into-simple-vector--small
  (with-initialized-managed-simple-vector-allocator
    (let ((ma (ab::allocate-managed-array 2))
          (ve (vector nil nil nil)))
      (aux-fn-fill-array-from-0-to-end ma)
      (ab::copy-from-managed-array-into-simple-vector ma 0 2 ve 0)
      (assert-equalp #(0 1 nil) ve)
      (ab::copy-from-managed-array-into-simple-vector ma 1 1 ve 0)
      (assert-equalp ve #(1 1 nil))
      (ab::copy-from-managed-array-into-simple-vector ma 0 2 ve 1)
      (assert-equalp ve #(1 0 1))
      (ab::reclaim-managed-array ma))))


(define-test test--copy-from-managed-array-into-simple-vector--large
  (with-initialized-managed-simple-vector-allocator
    (let ((ma (ab::allocate-managed-array 1025))
          (ve (vector nil nil nil)))
      (aux-fn-fill-array-from-0-to-end ma)
      (ab::copy-from-managed-array-into-simple-vector ma 1021 2 ve 0)
      (assert-equalp #(1021 1022 nil) ve)
      (ab::copy-from-managed-array-into-simple-vector ma 1024 1 ve 0)
      (assert-equalp ve #(1024 1022 nil))
      (ab::copy-from-managed-array-into-simple-vector ma 1023 2 ve 1)
      (assert-equalp ve #(1024 1023 1024))
      (ab::reclaim-managed-array ma))))

;; most cases are covered by adjust-managed-array tests
;; our goal is the following line:
;; then (minf maximum-managed-array-buffer-size element-count)

(define-test test--copy-managed-array-portion--more-than-one-buffer--expect-ok
  (with-initialized-managed-simple-vector-allocator
    (let ((src (ab::allocate-managed-array 2049))
          (dst (ab::allocate-managed-array 2048)))
      (aux-fn-fill-array-from-0-to-end src)
      (ab::copy-managed-array-portion src 1 2048 dst 0)
      (assert-true
       (managed-array-equal-to-vector dst
                                      (vector-from-k 2048 1)))
      (ab::reclaim-managed-array src)
      (ab::reclaim-managed-array dst)))) 
          
             
(define-test test--rotate-managed-array--trivial-case
  (with-initialized-managed-simple-vector-allocator
    (let ((v (ab::allocate-managed-array 2)))
      (aux-fn-fill-array-from-0-to-end v)
      (ab::rotate-managed-array v 0)
      (assert-true
       (managed-array-equal-to-vector v #(0 1))))))

(define-test test--rotate-managed-array--small
  (with-initialized-managed-simple-vector-allocator
    (let* ((outstanding-1 (ab::outstanding-simple-vector-pool-vectors))
           (v (ab::allocate-managed-array 3))
           (outstanding-2 (ab::outstanding-simple-vector-pool-vectors)))
      (aux-fn-fill-array-from-0-to-end v)
      (ab::rotate-managed-array v 1)
      (assert-true
       (managed-array-equal-to-vector v #(1 2 0)))
      (ab::rotate-managed-array v 2)
      (assert-true
       (managed-array-equal-to-vector v #(0 1 2)))
      (assert-true (no-simple-vector-leak-p outstanding-2))
      (ab::reclaim-managed-array v)
      (assert-true (no-simple-vector-leak-p outstanding-1))
      )))

(define-test test--rotate-managed-array--run-on-large-expect-good-result-and-no-leaks
  (with-initialized-managed-simple-vector-allocator
    (let* ((outstanding-1 (ab::outstanding-simple-vector-pool-vectors))
           (v (ab::allocate-managed-array 1023))
           (outstanding-2 (ab::outstanding-simple-vector-pool-vectors))
           (vector-to-compare (vector-from-k 1023 1)))
      (setf (svref vector-to-compare 1022) 0)
      (aux-fn-fill-array-from-0-to-end v)
      (ab::rotate-managed-array v 1)
      (assert-true
       (managed-array-equal-to-vector v vector-to-compare))
      (assert-true (no-simple-vector-leak-p outstanding-2))
      (ab::reclaim-managed-array v)
      (assert-true (no-simple-vector-leak-p outstanding-1))
      )))

(define-test test--insert-into-managed-array--run-several-times--check-correct-result-and-no-leaks
  (with-initialized-managed-simple-vector-allocator
    (let* ((success t)
           (outstanding-initial (ab::outstanding-simple-vector-pool-vectors))
           (ma (ab::allocate-managed-array 4))
           (li (list 0 1 2 3)))
      (flet ((compare ()
               (let ((expected (coerce li 'vector)))
                 (unless (managed-array-equal-to-vector ma expected)
                   (show-expr `("failed" ,expected))
                   (setf success nil)))))
        (aux-fn-fill-array-from-0-to-end ma)
        (setf ma (ab::insert-into-managed-array ma 2 'a))
        (setf li (insert-into-list li 2 'a))
        (compare)
        ;; make list large enough to use multiple buffers
        (dotimes (i 1023)
          (setf ma (ab::insert-into-managed-array ma (+ i 3) i))
          (setf li (insert-into-list li (+ i 3) i))
          (setf ma (ab::insert-into-managed-array ma 2 (- i)))
          (setf li (insert-into-list li 2 (- i))))
        (compare)
        (ab::reclaim-managed-array ma)
        (assert-true (no-simple-vector-leak-p outstanding-initial))
        (assert-true success)))))



(define-test test--delete-from-managed-array--run-several-times--check-correct-result-and-no-leaks
  (with-initialized-managed-simple-vector-allocator
    (let* ((success t)
           (outstanding-initial (ab::outstanding-simple-vector-pool-vectors))
           (ma (ab::allocate-managed-array 2049))
           (v (vector-from-k 2049 0)))
      (aux-fn-fill-array-from-0-to-end ma)
      (flet ((del-and-compare (i)
               (setf ma (ab::delete-managed-array-element ma i))
               (setf v (delete t v :test (constantly t) :start i :count 1))
               (unless (managed-array-equal-to-vector ma v)
                 (show-expr `("failed" ,i ,v))
                 (setf success nil))))
        ;; some random numbers
        (dolist (i '(345 7 34 2 0 43 68 90 1024 2000 88 3 3 3 3 3 3 3 3 3 3 3))
          (del-and-compare i))
        (dotimes (j 2000)
          (del-and-compare 0))
        (ab::reclaim-managed-array ma)
        (assert-true (no-simple-vector-leak-p outstanding-initial))
        (assert-true success)))))

(define-test test-let*-sim-1
  (let* ((a 4)
	 (that-a 
	  (ab::let*-sim ((a 1)) a (values (+ a 1) t)))
	 (later-a a)
	 (result (and (= that-a 2)
		      (= later-a 4))))
    (assert-true result)))

(define-test test-let*-sim-2
  (let* ((a 3) (b 7)
	 (that-a
	  (ab::let*-sim ((b 2) (a b)) a))
	 (later-a a)
	 (result (and (= that-a 2)
		      (= later-a 3))))
    (assert-true result)))

(defun macroexpand-and-read-possible-ordering-warning-if-it-is (form)
  (let* ((text (with-output-to-string (*error-output*)
                 (macroexpand form))))
    (if (search
         "PROTECTED-LET: possible ordering problem"
         text :test 'char-equal)
        t nil)))               

  
(defparameter validation-suite-for-protected-let ; stolen from utilities0.lisp
	      '(((ab::protected-let ((a b (reclaim a c)) 
                                     (c d (reclaim c)) 
                                     (e f (reclaim e))) 
		   (list a c e))
		 t) ;should generate warning
		((ab::protected-let ((a b (reclaim a)) 
                                     (c d (reclaim c)) 
                                     (e f (reclaim a e))) 
		   (list a c e))
		 nil) ;should not generate warning
		((ab::protected-let ((a b (reclaim a (process c)))
                                     (c d (reclaim c)) 
                                     (e f (reclaim e))) 
		   (list a c e))
		 t)
		((ab::protected-let ((a b (reclaim a)) 
                                     (c d (reclaim c)) 
                                     (e f (reclaim a (process e))))
		   (list a c e))
		 nil)))

(define-test test-protected-let-warnings
  (assert-true
   (every 'identity
          (loop :for (form produces-warning-p) 
                :in validation-suite-for-protected-let
                :collect (eq (macroexpand-and-read-possible-ordering-warning-if-it-is form)
                             produces-warning-p)))))

;; test each phrase in comment to protected-let: 
(define-test test-protected-let-binding
  "Protected-let sets each var to the result of bind-form.  It then executes the body forms and returns a single value from the last such form"
  (assert-eql
   (eval
    '(let (a b)
       (ab::protected-let ((a 1)(b 2))
         (+ a b))))
   3))

;; Don't put this to eval until defun-allowing-unwind is covered by tests
;; we need unwind-protect here to avoid 
;; "UNWIND-PROTECT used in manner not in keeping with AB's coding conventions" warning
;; RETURN-HERE - put these forms under eval when defun-allowing-unwind is covered by tests
(ab::defun-allowing-unwind test-protected-let-cleanup-1-fn () 
  (let (log)
    (ab::protected-let ((a 1 (push "Cleanup for A is invoked" log))
                        (b 2 (push "Cleanup for B is invoked" log)))
      (setq b nil) ; now cleanup for b must be not invoked, 
      ; while cleanup for a still must be invoked
      )
    log))
 
(define-test test-protected-let-cleanup-1
  "Finally, each var which ended up bound to a non-nil form has its corresponding undo-form executed as part of an unwind-protect context."
  (assert-equalp
   (test-protected-let-cleanup-1-fn)
   '("Cleanup for A is invoked")))

;; Don't put this to eval until defun-allowing-unwind is covered by tests
;; we need unwind-protect here to avoid 
;; "UNWIND-PROTECT used in manner not in keeping with AB's coding conventions" warning
(ab::defun-allowing-unwind test-protected-let-cleanup-2-fn () 
  (let (log)
    (ab::protected-let ((x (progn
                             (push "About to exit non-locally from X initialization" log)
                             ;; X cleanup is not invoked as we exit from a initialization
                             (return-from test-protected-let-cleanup-2-fn log))
                         (push "Cleanup for X is invoked" log))
                        (y
                         2
                         ;; Y cleanup is not invoked as we exit before Y initialization
                         (push "Cleanup for Y is invoked" log)))
      nil)
    (error "Must not arrive here")))


(define-test test-protected-let-cleanup-2
  "Note that this excludes vars that did not get bound at all because a return or non-local exit happened
before or during their binding."
  (assert-equalp
   (test-protected-let-cleanup-2-fn)
   '("About to exit non-locally from X initialization")))
  


;; Don't put this to eval until defun-allowing-unwind is covered by tests
;; we need unwind-protect here to avoid 
;; "UNWIND-PROTECT used in manner not in keeping with AB's coding conventions" warning
(ab::defun-allowing-unwind test-protected-let-cleanup-3-fn (logger-fn) 
  (ab::protected-let ((x
                       1
                       (progn
                         (funcall logger-fn "Exiting non-locally from X cleanup")
                         (error "Intentional error")))
                      (y
                       2
                         ;; Will Y cleanup be invoked? It is not specified...
                       (funcall logger-fn "Cleanup for Y is invoked")))
    nil)
  (error "Must not arrive here"))

;; TESTERS-COMMENT ab::protected-let. It is not specified what happens if non-local
;; exit is called from cleanup form. Normally, subsequent cleanups should be invoked 
;; anyway. We assert it by test-protected-let-cleanup-3 .
;; Also it is not clear from the description that in the presence of cleanup forms 
;; bindings become sequential but not parallel. We assert it by test-protected-let-not-parellel-in-presence-of-cleanups

(define-test test-protected-let-cleanup-3
  (let* (log
         (logger-fn (lambda (x) (push x log))))
    (ignore-errors
      (test-protected-let-cleanup-3-fn logger-fn))
    (assert-equalp log
                   '("Exiting non-locally from X cleanup" "Cleanup for Y is invoked"))))




(ab::defun-allowing-unwind test-protected-let-not-parellel-in-presence-of-cleanups-fn ()
  "This is an anomaly. That kind of bindings do not err but give rather unexpected result"
  (let ((x 1)(y 2))
    (declare (ignore x y)) ; we need the declaration as bindings are ignored in fact
    (ab::protected-let ((y x t)(x y t)) (list x y))))

(define-test test-protected-let-not-parallel-in-presence-of-cleanups
  "Note strange behaviour of protected-let"
  (assert-false
   (equal
    (test-protected-let-not-parellel-in-presence-of-cleanups-fn)
    (let ((x 1)(y 2))
      (let ((x y)(y x)) (list x y)))))
  (assert-equal
   (test-protected-let-not-parellel-in-presence-of-cleanups-fn)
   '(AB::UNBOUND-IN-PROTECTED-LET AB::UNBOUND-IN-PROTECTED-LET)))

(define-test test-protected-let-parallel-in-absence-of-cleanups
  (assert-equal
   (let ((x 1)(y 2))
     (ab::protected-let ((y x)(x y)) (list x y)))
   (list 2 1)))

;;; protected-let* is the same as let* when there are no cleanups
(define-test test-protected-let*-sequential-in-absence-of-cleanups
  (assert-equal
   (let ((x 1)(y 2))
     (ab::protected-let* ((y x)(x y)) (list x y)))
   (list 1 1)))


;; When there are cleanups, protected-let* is identical to protected-let - let's check that
(define-test test-protected-let*-the-same-as-protected-let-when-there-are-cleanups
  (assert-true
   (every (lambda (x y) (equalp (macroexpand x) (macroexpand y)))
          '((ab::protected-let  ((y x 1)) x)
            (ab::protected-let  ((y 1 (reclaim y)) (x)) (list x y))
            (ab::protected-let  ((x) (y 1 (reclaim y))) (list x y)))
          '((ab::protected-let* ((y x 1)) x)
            (ab::protected-let* ((y 1 (reclaim y)) (x)) (list x y))
            (ab::protected-let* ((x) (y 1 (reclaim y))) (list x y))))))


;; TESTERS-COMMENT with-flattened-protected-let-forms is seldom used, we skip testing it 
(define-test test-funcall-simple-case
  (assert-equal
   (ab::funcall-simple-case 'list 4 '(a b c d) first second third fourth)
   '(a b c d))
  (assert-equal
   (ab::funcall-simple-case 'list 4 '(a b c d) fourth third second first)
   '(d c b a)))



(define-test test-funcall-simple-case-list
  (assert-equal
   (ab::funcall-simple-case-list 'list '(a b c d))
   '(a b c d)))


(define-test test-do-activity
  (assert-equal
   (ab::do-activity '(list a b c))
   '(a b c)))

;; UNUSED-CODE do-activities reclaim-activities with-activity-enqueing
(define-test test-singleton
  (let ((result
	 (and (ab::singleton? (cons 'a nil)) ; cons with null cdr is only a singleton
	      (not (ab::singleton? (cons 'a 'a)))
	      (not (ab::singleton? 'a)))))
    (assert-true result)))

;; TESTERS-COMMENT Inefficiency in plistp - calculates lengt6h
(define-test test-plistp
  (let ((result
	 (and (ab::plistp '(a 1 b 2))
	      (ab::plistp nil)
	      (not (ab::plistp 'a))
	      (not (ab::plistp '(1 a 2 b))) ; names must be symbols
	      (not (ab::plistp '(a . b))) ; must be a proper list
	      (not (ab::plistp '(a 1 b))) ; must be of even length
	      (not (ab::plistp '(a 1 nil 2))) ; names must not be nil
	      )))
    (assert-true result)))

;; TESTERS-COMMENT it is unspecified what happens if there is more than one occurance of element-1 and/or element-2. Experiment shows that only leftmost occurances are considered
(defun process-order-in-front-test-case (test-data-entry &key reverse-too)
  "Returns true if all ok"
  (destructuring-bind (list expected-changed-something?)
      test-data-entry
    (when reverse-too
      (unless 
          (process-order-in-front-test-case (list (reverse list) (not expected-changed-something?))
                                            :reverse-too nil)
        (return-from process-order-in-front-test-case nil)))
    (let ((victim-list (copy-list list)))
      (multiple-value-bind (new-list changed-something?)
          (ab::order-in-front 'x 'y victim-list)
        (cond
         ((not (eq changed-something? expected-changed-something?))
          nil)
         ((and (not expected-changed-something?) (not (equal new-list list)))
           ;; unless change was expected, list must have return intact
          nil)
         ((not expected-changed-something?)
          t)
         ;; hence something was changed and it was expected. We must check that x is before y
         ((< (position 'y new-list) (position 'x new-list))
          nil)
          ;; also we must check that only x have moved
         ((not (equalp
                (remove 'x new-list)
                (remove 'x list)))
          nil)
         (t t))))))


;; RETURN-HERE check that all branches are covered
(define-test test-order-in-front
  (let (failed)
    (dolist (entry
             '( ;; list element-1 == x and element-2 == y. 
                ;; every entry is (list expected-changed-something?)
                ;; note that for every list reversed list is checked
               ((x y) nil)
               ((x a y) nil)
               ((a y x) t)
               ((y a x) t)
               ((y x a) t)
               ((y + x -) t)
               ((y x + -) t)
               ((+ y - x) t)
               ((+ - y x) t)
               ((* y + x -) t)
               ((y * x + -) t)
               ((+ y - x *) t)
               ((+ - y x *) t)))
      (unless (process-order-in-front-test-case entry :reverse-too t)
        (setf failed t)
        (return)))
    (assert-false failed)))


(define-test test-order-in-front-trivial-cases
  (let ((success t))
    (dolist (entry
             '((nil nil)
               ((x) nil)
               ((y) nil)
               ((x +) nil)
               ((+ x) nil)
               ((+ x +) nil)
               ((y +) nil)
               ((+ y) nil)
               ((+ y +) nil)
               ))
      (unless (process-order-in-front-test-case entry)
        (setf success nil)
        (return)))
    (assert-true success)))
               
             

(define-test test-order-in-front-with-duplicates
  "Behaviour of this test is not specified in docs, see TESTERS-COMMENT above"
  (assert-equal
   (ab::order-in-front 'x 'y (list 'x 'y 'x 'y))
   (values '(x y x y) nil))
  (assert-equal
   (ab::order-in-front 'y 'x (list 'x 'y 'x 'y))
   (values '(y x x y) t)))
  
(define-test test-order-in-back
  "Just a few tests as test-order-in-back delegates to test-order-in-front"
  (let ((success t))
    (dolist (list
             '((x y)
               (y x)
               (y + x -)
               ))
      (unless (equal
               (multiple-value-list 
                (ab::order-in-back 'x 'y (copy-list list)))
               (multiple-value-list
                (multiple-value-bind (result change)
                    (ab::order-in-front 'x 'y (reverse list))
                  (values (nreverse result) change))))
        (setf success nil)
        (return)))
    (assert-true success)))


(define-test test-parse-body-declarations
  (let ((success t))
    (dolist (docstring-list '(("docstring") nil))
      (dolist (declarations-list '(((declare 1)(declare 2)) ((declare 1)) nil))
        (dolist (body-list '(("body") ((progn 1 2 3)) (1 2 3) nil))
          (let* ((body
                  (append (copy-tree docstring-list)
                          (copy-tree declarations-list)
                          (copy-tree body-list)))
                 (expected
                  (list
                   declarations-list
                   body-list
                   (car docstring-list)))
                 (parsed
                  (multiple-value-list
                   (ab::parse-body-declarations
                    body))))
            (cond
             ((and docstring-list (not body-list))
              ;; this is a wrong test case: if there is no body, docstring must be treated as body
              t)
             ((not (equal expected parsed)) ; test failure
              (print `(:expected ,expected :parsed ,parsed))
              (setf success nil)))))))
    (assert-true success)))

(defun aux-fn-test--do-until-time-interval-expires ()
  (let* ((time-before (ab::get-fixnum-time))
         (dummy
          (eval '(ab::do-until-time-interval-expires (100) (sleep 0.01))))
         (time-after (ab::get-fixnum-time)))
    (declare (ignore dummy))
    (ab::>f (ab::fixnum-time-difference time-after time-before))))

(define-test test--do-until-time-interval-expires
  (assert-true (aux-fn-test--do-until-time-interval-expires))) 

(define-test test-squaref
  (assert-true
   (every 'identity
          (mapcar (lambda (f)
                    (= (eval `(ab::squaref ,f)) (ab::*f f f)))
                  '(-35 0 5 15 1005)))))

                 
(defun test-nconc-macro-fn (l1 l2)
  (let* ((copy-l1 (copy-list l1))
         (copy-l2 (copy-list l2))
         (len-l1 (length l1))
         (len-l2 (length l2))
         (result (eval `(ab::nconc-macro ',l1 ',l2))))
    (cond
     ((null copy-l1)
      (and 
       (eq result l2)
       (every 'eq result copy-l2)))
     ((null copy-l2)
      (and (eq result l1)
           (every 'eq result copy-l1)
           (equalp result copy-l1) ; check for length
           ))
     (t ; both list are non-null
      (let ((l2-in-result
             (nthcdr len-l1 result)))
        (and
         (eq result l1)
         (every 'eq copy-l1 result)
         (eq l2-in-result l2)
         (every 'eq l2-in-result copy-l2)
         (= (length result) (+ len-l1 len-l2))))))))
              
     
    
(define-test test-nconc-macro
  (let ((success t))
    (dolist (entry
             '(
               ((a) nil)
               (nil (a))
               ((a b) nil)
               (nil (a b))
               ((a b) (c d))
               ))
      (unless (test-nconc-macro-fn (copy-list (first entry)) (copy-list (second entry)))
        (setf success nil)))
    (assert-true success)))


(define-test test-circular-list
  (let ((success t))
    (dolist (entry
             (list
              '(nil nil)
              '((a) nil)
              '((a b) nil)
              (list (alexandria:make-circular-list 1 :initial-element 'a) t)
              (list (alexandria:make-circular-list 2 :initial-element 'a) t)
              (list (alexandria:make-circular-list 3 :initial-element 'a) t)
              ))
      (destructuring-bind (data expected-result) entry
        (unless (eq (ab::circular-list-p data) expected-result)
          (setf success nil))))
    (assert-true success)))



(defvar *reclaimed-conses-for-test*)
(defun reclaim-to-reclaimed-conses-for-test (x)
  (push x *reclaimed-conses-for-test*))

(defun delete-macro-and-reclaim-cons-cells-fn (element list key test)
  "Returns success"
  (let* ((l (copy-list list))
         (conses-of-list (all-conses-of-list l))
         (*reclaimed-conses-for-test* nil)
         (new-list
          (eval
           `(ab::delete-macro ',element ',l :key ,key :test ,test :reclaimer reclaim-to-reclaimed-conses-for-test)))
         (conses-of-new-list (all-conses-of-list new-list)))
    (cond
     ((not (equal new-list (remove element list :test test :key key)))
      nil)
     ((set-equal (union conses-of-new-list *reclaimed-conses-for-test*) conses-of-list)
      t)
     (t
      nil))))

(defun test-delete-macro-test-key (x)
  (cons x '+))

(defun test-delete-macro-test-test (x y)
  (eq
   (if (atom x) x (car x))
   (if (atom y) y (car y))))

(define-test test-delete-macro
  (let ((success t))
    (dolist (list
             '(nil
               (a)
               (a b)
               (b)
               (b c)
               (a b c)
               (b a c)
               (c b a)
               (a a b c)
               (b a a c)
               (b c a a)
               (a b a c)
               (a b c a)
               (b a c a)
               (a a a a a b a c)
               (a a a a a b a c a a)
               (a a d a a b a c a a)))
      (dolist (key '(identity null test-delete-macro-test-key))
        (dolist (test (list 'eq 'eql 'test-delete-macro-test-test))
          (unless (delete-macro-and-reclaim-cons-cells-fn
                   'a
                   list
                   key
                   test)
            (setf success nil)))))
    (assert-true success)))
        
        

(defun remove-property-macro-and-reclaim-cons-cells-fn (list indicator)
  "Returns success"
  (let* ((l (copy-list list))
         (conses-of-list (all-conses-of-list l))
         (*reclaimed-conses-for-test* nil)
         (new-list
          (eval
           `(ab::remove-property-macro ',l ',indicator reclaim-to-reclaimed-conses-for-test)))
         (conses-of-new-list (all-conses-of-list new-list))
         (l2 (copy-list list))
         (dummy1 (remf l2 indicator)))
    (declare (ignore dummy1))
    (cond
     ((not (equal new-list l2))
      nil)
     ((set-equal (union conses-of-new-list *reclaimed-conses-for-test*) conses-of-list)
      t)
     (t
      nil))))


(defparameter *test-plists-for-remove-property-macro*
  '(nil
    (:a +)
    (:a + :a -)
    (:a + :b - :c -)
    (:a + :b + :a -)
    (:b + :a + :c -)
    (:b + :c + :a +)
    (:b + :c + :a + :a -)
    (:a + :b + :c + :a * :a -)
    (:b +)
    (:b + :b +)
    (:b + :c +)
    (:b + :c + :d +)
               ;; incorrect plists cause errors, don't test them
               ;(:a + :b)
               ;(:b + :a)
    )
  "We will always look for :a and should either get '+ or nothing")
  

(define-test test--remove-property-macro
  (let ((success t))
    (dolist (list *test-plists-for-remove-property-macro*)
      (unless (remove-property-macro-and-reclaim-cons-cells-fn list :a)
        (setf success nil)))
    (assert-true success)))


(define-test test--get-property-macro
  (let ((success t))
    (dolist (list *test-plists-for-remove-property-macro*)
      (let* ((found (eval `(ab::get-property-macro ',list :a :none-found)))
             (expected (getf list :a :none-found)))
      (unless (eq found expected)
        (setf success nil))
      (unless (member found '(+ :none-found))
        (setf success nil))))
    (assert-true success)))
      
;; we use cons as a conser - seem to be ok
(define-test test-set-property-macro-a
  "We always set :a to '++"
  (let ((success t))
    (dolist (list *test-plists-for-remove-property-macro*)
      (let* ((copy1 (copy-list list))
             (copy2 (copy-list list))
             (got (eval `(ab::set-property-macro ',copy2 :a cons '++)))
             (dummy1 (setf (getf copy2 :a) '++)))
        (declare (ignore dummy1))
        (unless (equalp got copy2)
          (print `(:expected ',copy2 :got ',got))
          (setf success nil))))
    (assert-true success)))

(define-test test-car-or-atom
  (let ((result (and (eq (ab::car-or-atom nil) nil)
		     (eq (ab::car-or-atom 'a) 'a)
		     (eq (ab::car-or-atom '(a)) 'a))))
    (assert-true result)))

(define-test test-cdr-or-atom
  (let ((result (and (eq (ab::cdr-or-atom nil) nil)
		     (eq (ab::cdr-or-atom 'a) nil)
		     (eq (ab::cdr-or-atom '(a . b)) 'b))))
    (assert-true result)))

(define-test test-gensym-cons-or-atom
  (with-simplest-test-environment ()
    (assert-equal (ab::gensym-cons-or-atom 'a nil) 'a)
    (assert-equal (ab::gensym-cons-or-atom 'a 'b) '(a . b))
    (assert-equal (ab::gensym-cons-or-atom '(a) nil) '((a)))))

(defun test-do-atom-or-list-of-atoms-fn (list)
  (let* ((l (if (atom list) list (copy-list list)))
         (old-conses (all-conses-of-list list))
         (got
          (eval `(let (result)
                   (ab::do-atom-or-list-of-atoms (x ',l)
                     (push x result))
                   result)))
         (expected
          (cond
           ((atom list)
            (list list))
           (t
            (reverse list)))))
    (and (equal expected got)
         (or (and (atom list) (eq list l))
             ;; test that list was not altered
             (list-contents-eql old-conses (all-conses-of-list l))))))

(define-test test-do-atom-or-list-of-atoms
  (let ((result
	 (and (test-do-atom-or-list-of-atoms-fn 'a)
	      (test-do-atom-or-list-of-atoms-fn 'b)
	      (test-do-atom-or-list-of-atoms-fn 'c))))
    (assert-true result)))

(define-test test-quoted-form
  (let ((result
	 (and (ab::quoted-form-p (list 'quote 'a))
	      (ab::quoted-form-p (cons 'quote 'a)) ; this is strange
	      (ab::quoted-form-p (list 'quote 'a 'b))
	      (not (ab::quoted-form-p (list 'a)))
	      (not (ab::quoted-form-p 4)))))
    (assert-true result)))

(define-test test-unquote
  (let ((result
	 (and (equal (ab::unquote (list 'quote 'a)) 'a)
	      (equal (ab::unquote (list 'quote 'a 'b)) 'a)
	      (equal (ab::unquote (list 'a)) (list 'a))
	      (equal (ab::unquote 4) 4))))
    (assert-true result)))

(define-test test-first-of-cons-etc-1.a
  (let* ((list '(a b c d e f g))
	 (result
	  (and (eq (ab::first-of-cons list) (car list))
	       (eq (ab::second-of-cons list) (second list))
	       (eq (ab::third-of-cons list) (third list))
	       (eq (ab::fourth-of-cons list) (fourth list))
	       (eq (ab::fifth-of-cons list) (fifth list))
	       (eq (ab::cadr-of-cons list) (second list))
	       (eq (ab::cddr-of-cons list) (cddr list)))))
    (assert-true result)))

(define-test test-first-of-cons-etc-1.b
  (let* ((list '((a b) (c d)))
	 (result
	  (and (eq (ab::caar-of-cons list) (caar list))
	       (eq (ab::caadr-of-cons list) (caadr list)))))
    (assert-true result)))

(defun test-alist-to-plist-macro-fn (alist)
  (let* ((expected
          (loop :for entry :in alist
                :collect (car entry)
                :collect (cdr entry)))
         (al (copy-tree alist))
         (got (eval `(ab::alist-to-plist-macro ',al))))
    (or (null expected)
        (list-contents-eql expected got))))

(define-test test-alist-to-plist-macro
  (let ((result
	 (and (test-alist-to-plist-macro-fn nil)
	      (test-alist-to-plist-macro-fn '((a . 1)))
	      (test-alist-to-plist-macro-fn '((a . 1) (b . 2))))))
    (assert-true result)))

(define-test test--alist-to-plist--except--the-same-as-alist-to-plist-macro
  (let ((data '((a . b)(c . d))))
    (assert-equal
     (ab::alist-to-plist (copy-tree data))
     (ab::alist-to-plist-macro (copy-tree data)))))

;; UNUSED-CODE push-onto-end never used
(define-test pushnew-onto-end--push-non-present-value--expect-value-is-added
  (assert-equal
   '(a b)
   (eval
    '(let ((list (list 'a)))
       (ab::pushnew-onto-end 'b list)))))

(define-test pushnew-onto-end--push-present-value--expect-value-is-not-added
  (let ((result
	 (let ((list (list 'a)))
	   (ab::pushnew-onto-end 'a list)
	   list)))
    (assert-equal '(a) result)))

(define-test pushnew-onto-end--push-value-present-by-equal--expect-value-is-added
  (let ((result
	 (let ((list (list "a")))
	   (ab::pushnew-onto-end (copy-seq "a") list)
	   list)))
    (assert-equal '("a" "a") result)))

(define-test push-update--push-non-existing-value--expect-it-in-the-beginning
  (let ((result
	 (let ((place (list '(a . 1))))
	   (ab::push-update '(b . 2) place :key car)
	   place)))
    (assert-equal
      '((b . 2) (a . 1))
      result)))

(define-test push-update--push-existing-value--expect-it-is-replaced
  (let ((result
	 (let ((place (copy-tree '((a . 1) (b . 2) (c . 3)))))
	   (ab::push-update '(b . 0) place :key car)
	   place)))
    (assert-equal
      '((a . 1) (b . 0) (c . 3))
      result)))

(define-test test-outstanding-gensym-cons-counter-function
  ;; setup
  (let ((ab::available-gensym-conses (list 'a 'b 'c))
	(ab::gensym-cons-counter 4))
    (assert-equal
     (ab::outstanding-gensym-conses)
     1)))

(define-test test-gensym-memory-usage
  (let ((ab::gensym-cons-counter 2))
    (assert-equal
      (ab::gensym-cons-memory-usage)
      (* 2 (ab::bytes-per-cons)))))

(defmacro with-some-state-of-gensym-cons-pool (list &body body)
  `(let* ((ab::available-gensym-conses ,list)
          (ab::gensym-cons-counter (length ab::available-gensym-conses))
          (ab::available-gensym-conses-tail (last ab::available-gensym-conses)))
     ,@body))

(defmacro test-something-after-replenish (&body body)
  ;; x variable is captured
  `(dolist (x (list (list 'a 'b 'c) nil))
     (with-some-state-of-gensym-cons-pool
      x
      (let ((ab::cons-pool-conses-to-make-at-a-time 2))
        (ab::replenish-gensym-cons-pool)
        ,@body))))

(define-test test--replenish-gensym-cons-pool--call-it--tail-is-set-appropriately
 (let ((ab::cons-checking-enabled-p nil))
  (test-something-after-replenish
    (assert-eq (last ab::available-gensym-conses)
	       ab::available-gensym-conses-tail))))

(define-test test--replenish-gensym-cons-pool--non-empty--appropriate-contents
 (let ((ab::cons-checking-enabled-p nil))
  (with-some-state-of-gensym-cons-pool
   (list 'a 'b 'c)
   (let ((ab::cons-pool-conses-to-make-at-a-time 2))
     (ab::replenish-gensym-cons-pool)
     (assert-equal (list 'a 'b 'c) ; first element has undefined value
                   (cdr ab::available-gensym-conses))))))

(define-test test--replenish-gensym-cons-pool--call-it--counter-is-set-appropriately
 (let ((ab::cons-checking-enabled-p nil))
  (test-something-after-replenish
   (assert-eql (+ (length ab::available-gensym-conses)
                  1 ; one cons was returned by replenish function
                  )
               ab::gensym-cons-counter))))

(define-test test--reclaim-gensym-list-macro--call-it-not-mocking-conser--expect-list-is-added-to-conser
  ;; don't mock conser
  (let* ((ab::cons-checking-enabled-p nil)
         (list-to-reclaim (list 1 2 3))
         (conses (all-conses-of-list list-to-reclaim))
         (success t))
    (ab::reclaim-gensym-list-macro list-to-reclaim)
    (dolist (cons conses)
      (unless (cons-is-on-list cons ab::available-gensym-conses)
        (setf success nil)))
    (assert-true success)))

;; RETURN-HERE some tests are missing
(define-test test--gensym-list--call-it--expect-result-is-correct-and-conses-are-taken-from-the-conser
  (let* ((ab::cons-checking-enabled-p nil)
         (victim (list 'a 'b 'c 'd 'e))
         (all-conses-to-work-with
          (append (all-conses-of-list ab::available-gensym-conses)
                  (all-conses-of-list victim)))
         (dummy
          (ab::reclaim-gensym-list victim))
          ;; run 
         (result (ab::gensym-list 'a 'b 'c)))
    ;; assert
       ;; check we get what we wanted
    (assert-equal result '(a b c))
       ;; check we get conses from the right place
    (assert-true
     (alexandria:set-equal
      all-conses-to-work-with
      (append (all-conses-of-list ab::available-gensym-conses)
              (all-conses-of-list result))))))

;; RETURN-HERE conser tests do not give any credit so I stop doing them now. 
;; However I won't mock them in subsequent work - budden 2016-05-17

;; RETURN-HERE all up to reclaim-gensym-tree-function is skipped. 
(define-test test--reclaim-gensym-list-function--call-it--expect-all-conses-are-in-the-conser
  ;; Don't mock conser
  ;; RETURN-HERE it is likely the test does not cover everything what is needed to test 
  (let ((success t)
        (ab::cons-checking-enabled-p nil))
    (dolist (list-to-reclaim
             (list
              (list 1 2 3)
              nil))
      (let* ((copy (copy-list list-to-reclaim))
             (conses (all-conses-of-list list-to-reclaim))
             (no-of-conses-to-reclaim (length conses))
             (old-available-cons-count (length ab::available-gensym-conses)))
        (ab::reclaim-gensym-list-macro list-to-reclaim)
        (unless (all-elements-of-list-are-conses-on-list conses ab::available-gensym-conses)
          (show-expr `("failed: failed to reclaim all conses" ,copy))
          (setf success nil))
        (unless (= (length ab::available-gensym-conses)
                   (+ old-available-cons-count no-of-conses-to-reclaim))
          (show-expr `("failed: incorrect amount of conses reclaimed" ,copy))
          (setf success nil))))
    (assert-true success)))
          
(define-test test--reclaim-gensym-tree-function--call-it--expect-all-conses-are-in-the-conser-and-count-updated-correcly
  ;; Don't mock conser
  ;; RETURN-HERE it is likely the test does not cover everything what is needed to test 
  (let ((success t)
        (ab::cons-checking-enabled-p nil))
    (dolist (tree-to-reclaim
             (list
              (list* 1 (list 2) (cons 3 4) 5)
              nil
              (cons 1 2)))
      (let* ((conses (all-conses-of-tree tree-to-reclaim))
             (copy (copy-tree tree-to-reclaim))
             (no-of-conses-to-reclaim (length conses))
             (old-available-cons-count (length ab::available-gensym-conses)))
        (ab::reclaim-gensym-tree-function tree-to-reclaim)
        (unless (all-elements-of-list-are-conses-on-list conses ab::available-gensym-conses)
          (show-expr `("failed: failed to reclaim all conses" ,copy))
          (setf success nil))
        (unless (= (length ab::available-gensym-conses)
                   (+ old-available-cons-count no-of-conses-to-reclaim))
          (show-expr `("failed: incorrect amount of conses reclaimed"
                       ,copy
                       ,no-of-conses-to-reclaim
                       ,old-available-cons-count
                       ,(length ab::available-gensym-conses)))
          (setf success nil))))
    (assert-true success)))


(defun aux-fn-test--copy-tree-using-gensym-conses-function--call-it--expect-all-conses-are-really-gensym-conses (tree-to-copy)
  (let* ((success t)
         (victim-tree (copy-tree tree-to-copy))
         (verbatim-tree (copy-tree tree-to-copy))
         (conses-of-tree (all-conses-of-tree tree-to-copy))
         (additional-cons (cons nil nil)) ; we might need this cons to avoid repleneshing
         (list-of-all-conses-to-work-with
          (append (list additional-cons)
                  (all-conses-of-list ab::available-gensym-conses)
                  (all-conses-of-tree victim-tree)))
         new-tree)
    (ab::reclaim-gensym-tree-function victim-tree)
    (ab::reclaim-gensym-cons additional-cons)
        ;; run
    (setf new-tree (ab::copy-tree-using-gensym-conses-function tree-to-copy))
        ;; test
        ;; check that original tree kept its structure
    (unless (equal tree-to-copy verbatim-tree)
      (show-expr `("failed: initial tree smashed" ,verbatim-tree))
      (setf success nil))
        ;; check that original tree is build from the same conses as before
    (unless (equal conses-of-tree (all-conses-of-tree tree-to-copy))
      (show-expr `("failed: initial tree cons set changed" ,verbatim-tree))
      (setf success nil))
        ;; check that copy is not shared with the original
    (when (intersection conses-of-tree (all-conses-of-tree new-tree))
      (show-expr `("failed: copy is shared with source" ,verbatim-tree))
      (setf success nil))
        ;; check that copy is equal to original
    (unless (equal tree-to-copy new-tree)
      (show-expr `("failed: copy is inexact" ,tree-to-copy))
      (setf success nil))
        ;; check that all conses was taken from the conser and
        ;; that neither of conser's conses were lost on the way
    (unless (alexandria:set-equal
             (union
              (all-conses-of-list ab::available-gensym-conses)
              (all-conses-of-tree new-tree))
             list-of-all-conses-to-work-with)
      (show-expr `("failed: some conses leaked in or out" ,tree-to-copy))
      (setf success nil))
    success))

(define-test test--copy-tree-using-gensym-conses-function--call-it--test-different-things
  (let ((success t)
        (ab::cons-checking-enabled-p nil))
    ;; setup
    (dolist (tree-to-copy
             (list
              (list* 1 (list 2) (cons 3 4) 5)
              nil
              (cons 1 2)))
      ;; run and assert
      (unless (aux-fn-test--copy-tree-using-gensym-conses-function--call-it--expect-all-conses-are-really-gensym-conses
               tree-to-copy)
        (setf success nil)))
    (assert-true success)))


(defun aux-fn-test--reverse-list-using-gensym-conses--call-it--check-that-list-is-reversed-and-that-list-is-built-of-gensym-conses (orig)
  ;; setup
  (let* ((success t)
         (conses-of-orig (all-conses-of-list orig))
         (verbatim-orig (copy-list orig))
         (victim-list (copy-list orig)) ; make sure we have enough conses on pool
         (additional-cons (cons nil nil)) ; we might need this cons to avoid repleneshing 
         (list-of-all-conses-to-work-with
          (append (list additional-cons)
                  (all-conses-of-list ab::available-gensym-conses)
                  (all-conses-of-list victim-list)))
         result)
    (ab::reclaim-gensym-list-function victim-list)
    (ab::reclaim-gensym-list-function additional-cons)
    ;; run 
    (setf result (ab::reverse-list-using-gensym-conses orig))
    ;; assert
       ;; check that original list was not touched
    (unless (equal verbatim-orig orig)
      (show-expr `("failed: original was smashed" ,verbatim-orig))
      (setf success nil))
       ;; check that original list is build from the same conses as before
    (unless (equal conses-of-orig (all-conses-of-list orig))
      (show-expr `("failed: initial list cons set changed" ,verbatim-orig))
      (setf success nil))
       ;; check that list is really reversed
    (unless (equal result (reverse orig))
      (show-expr `("failed: result is not a reverse of an original" ,orig))
      (setf success nil))
       ;; check we tool all conses from the conser and no cons is lost
    (unless
        (alexandria:set-equal
         (union
          (all-conses-of-list result)
          (all-conses-of-list ab::available-gensym-conses))
         list-of-all-conses-to-work-with)
      (show-expr `("failed: some conses leaked in or out" ,orig))
      (setf success nil))
    success))

(define-test test--reverse-list-using-gensym-conses--call-it--check-that-list-is-reversed-and-that-list-is-built-of-gensym-conses
  (let ((success t)
        (ab::cons-checking-enabled-p nil))
    (dolist (lst (list
                  nil
                  (list 'a)
                  (list 'a 'b 'c)))
      (unless (aux-fn-test--reverse-list-using-gensym-conses--call-it--check-that-list-is-reversed-and-that-list-is-built-of-gensym-conses lst)
        (setf success nil)))
    (assert-true success)))

;; TRIVIAL-CODE reclaim-gensym-list-if-list

(defun assert-scope-conses-not-shared-to-available-conses ()
  ;; we check it also before each run
  (assert-false
   (intersection
    ab::scope-conses
    (all-conses-of-list ab::available-gensym-conses))))

(defun exhaust-gensym-conses ()
  ;; allocates and then drops w/o reclaiming almost all available gensym conses. 
  ;; leave 1 element in ab::available-gensym-conses
  ;; reason is to model the situation of limited amount of available conses
  (when (= (length ab::available-gensym-conses) 0) ; situation is rather unexpected
    (ab::reclaim-gensym-cons (ab::gensym-cons 'x 'y)))
  (assert (> (length ab::available-gensym-conses) 0))
  (when (> (length ab::available-gensym-conses) 1)
    (let* ((initial-available-gensym-conses (all-conses-of-list ab::available-gensym-conses))
           (result
            (ab::make-gensym-list (- (length ab::available-gensym-conses) 1)))
           (conses-extracted-and-left
            (append
             (all-conses-of-list result)
             (all-conses-of-list ab::available-gensym-conses))))
    ;; this assertion checks validity of test
      (assert (= (length ab::available-gensym-conses) 1))
    ;; this assertion checks validity of test
      (assert (alexandria:set-equal
               conses-extracted-and-left             
               initial-available-gensym-conses)))))





;;;; Testing compare-memory-allocation and some early memory error diagnosis is available under development only

#+(or development under-test)
(defun assert-compare-memory-allocation-is-silent ()
  (let ((ou
         (with-output-to-string (*standard-output*)
           (ab::compare-memory-allocation))))
    (assert-equal "" ou)))

#+(or development under-test)
(defun assert-pools-are-mentioned-in-compare-memory-allocation (&rest pool-names)
  (let ((ou
         (with-output-to-string (*standard-output*)
           (ab::compare-memory-allocation)))
        (success t))
    (dolist (pool-name pool-names)
      (unless (search pool-name ou :test 'char-equal)
        (show-expr `("failed:" ,pool-name))
        (setf success nil)))
    (assert-true success)))

#+development
(define-test test--debug-consing--double-reclaim--causes-error
  (assert-error
   'error
   (with-simplest-test-environment ()
     (let ((a (ab::gensym-cons 1 1)))
       (ab::reclaim-gensym-cons a)
       (ab::reclaim-gensym-cons a)))))

#+cons-checking
(define-test test--limited-tailp
  (flet ((circular-list (&rest elements)
           (let ((cycle (copy-list elements))) 
             (nconc cycle cycle))))
    (let ((cl (circular-list 1 2 3))
          (l (list 1 2 3)))
      (assert-equal nil (ab::limited-tailp (cdr cl) cl 0))
      (assert-equal 1 (ab::limited-tailp (cdr cl) cl 87))
      (assert-equal 2 (ab::limited-tailp (cddr l) l (length l)))
      (assert-equal nil (ab::limited-tailp 12312 l (length l)))
      )))

#+cons-checking
(define-test test--cons-checking--reclaim-non-allocated-cons--it-is-cons-checking-that-detects-an-error
  ;; ensure that cons-checking is on
  (assert-equal ab::cons-checking-enabled-p t)
  ;; make sure error is captured when cons-checking is on
  (assert-error
   'error
   (with-simplest-test-environment ()
     (let* ((cons1 (cons 1 2)))
       (ab::reclaim-slot-value-cons cons1))))
  ;; temporarily disable cons-checking and find out that we can do the wrong thing
  ;; (reclaim cons which we didn't allocated)
  (assert-true
   (funcall ; thank you lispunit for this necessity of this ugly wrapper
    (lambda ()
      (with-cons-checking-stopped
        (with-simplest-test-environment ()
          (let* ((cons1 (cons 1 2)))
            (ab::reclaim-slot-value-cons cons1)
            t)))))))

#+cons-checking
(define-test test--cons-checking--cons-checking-validate-state-of-conses-available--is-quiet-if-no-corruption
  ;; first of all, it should be quiet if all is ok
  (assert-equal ; after lisp-unit upgrade, assert-true does not accept macros anymore
                ; so we need ugly workarounds like this
   nil
   (let ((ab::cons-checking-enabled-p t))
     (with-connection-test-environment ()
       (let ((a (ab::gensym-list 123)))
         (ab::reclaim-gensym-list a)
         (ab::cons-checking-validate-state-of-conses-available 'ab::gensym))))))

(defun corrupt--available-gensym-list--via-cdr (value)
  (let* ((a (ab::gensym-list 123 456 789))
         (cons-to-write-after-reclaim (cdr a)))
    (ab::reclaim-gensym-list a)
    (setf (cdr cons-to-write-after-reclaim) value)))
  
(defun copy-cons-contents (src dst)
  (setf (car dst) (car src) (cdr dst) (cdr src)))

#+cons-checking
(define-test test--cons-checking--cons-checking-validate-state-of-conses-available--cons-imitating-normally-reclaimed
  ;; lets corrupt some cdr in free-list - we should detect it with ab::cons-checking-validate-state-of-conses-available
  (assert-equal
   t
   (let ((ab::cons-checking-enabled-p t))
     (with-connection-test-environment ()
       (let* ((a (ab::gensym-list 123 456 789))
              (cons-to-write-after-reclaim (cdr a))
              ; we will illegally cons-to-inject into list of avaliable conses 
              ; and make a pretence that it is normal reclaimed cons
              (cons-to-inject (cons nil nil)))
         (ab::reclaim-gensym-list a)
         (copy-cons-contents cons-to-inject cons-to-write-after-reclaim)
         (setf (cdr cons-to-write-after-reclaim) cons-to-inject))
       (not (not (ab::cons-checking-validate-state-of-conses-available 'ab::gensym)))))))

#+cons-checking
(define-test test--cons-checking--cons-checking-validate-state-of-conses-available--is-useful-cdr-atom
  ;; lets corrupt some cdr by atom - it will cause ab::cons-checking-validate-state-of-conses-available to err
  (assert-error
   'error
   (let ((ab::cons-checking-enabled-p t))
     (with-connection-test-environment ()
       (corrupt--available-gensym-list--via-cdr 12312)
       (ab::cons-checking-validate-state-of-conses-available 'ab::gensym)))))

#+cons-checking
(define-test test--cons-checking--cons-checking-validate-state-of-conses-available--cdr-is-null--checking-is-filtered
  ;; lets write nil in some cdr of free-list thus truncating it - it is a special case, but we must detect it
  ;; by the way test that for cons-checking enabled for gensym conses only.
  (assert-eq
   t
   (let ((ab::cons-checking-enabled-p 'ab::gensym))
     (with-connection-test-environment ()
       (corrupt--available-gensym-list--via-cdr nil)
       (not (not (ab::cons-checking-validate-state-of-conses-available 'ab::gensym)))))))

#+cons-checking
(define-test test--cons-checking--cons-checking-validate-state-of-conses-available--corrupt-car
  ;; lets corrupt some car in free-list - we should detect it with ab::cons-checking-validate-state-of-conses-available
  (assert-eq
   t
   (let ((ab::cons-checking-enabled-p t))
     (with-connection-test-environment ()
       (let* ((a (ab::gensym-list 123 456 789))
              (cons-to-write-after-reclaim (cdr a)))
         (ab::reclaim-gensym-list a)
         (setf (car cons-to-write-after-reclaim) 101112)
         (not (not (ab::cons-checking-validate-state-of-conses-available 'ab::gensym))))))))


#+cons-checking
(define-test test--cons-checking--cons-checking-validate-state-of-conses-available--circular-list
  ;; short-circuit free-list by making it circular - validator should complain
  (assert-eq
   t
   (let ((ab::cons-checking-enabled-p t))
     (with-connection-test-environment ()
       (ab::reclaim-gensym-list (ab::gensym-list 123 456 789 101112))
       (setf (cddr ab::available-gensym-conses) (cdr ab::available-gensym-conses))
       (not (not (ab::cons-checking-validate-state-of-conses-available 'ab::gensym)))))))


;;; In the test--cons-checking--maybe-break-on-global-allocation-operation-counter--works
;;; we demonstrate the use of advice on maybe-break-on-global-allocation-operation-counter 
;;; to track events on conses

#+cons-checking
(defun test--cons-checking--maybe-break-on-global-allocation-operation-counter--works--aux-fn (p)
  ;; This is a scenario to demonstrate advicing on 
  ;; ab::maybe-break-on-global-allocation-operation-counter, see the test mathing the name of this fn. 
  ;; 
  ;; p function imitates printing, but it collects objects themselves into a list instead of dumping their
  ;; printed representations to string.
  ;; 
  ;; We allocate the cons, remember it and then reclaim it.
  ;; 
  ;; advice we define on ab::maybe-break-on-global-allocation-operation-counter in the scope of test (below)
  ;; makes use of its parameters (object, pool, and log entry) and current value of 
  ;; ab::*global-allocation-operation-counter*
  (let ((ab::cons-checking-enabled-p t)
        (the-cons nil))
    (with-connection-test-environment
        ()
      (let* ((ab::*cons-checking-log-settings* '(ab::counter ab::backtrace))
             (ab::*global-allocation-operation-counter* 0))
        (funcall p 'init)
        (setq the-cons (ab::gensym-cons nil nil))
        (funcall p 'got-cons)
        (ab::reclaim-gensym-cons the-cons)
        (funcall p 'end)))
    the-cons))

#+cons-checking
(defun test--cons-checking--maybe-break-on-global-allocation-operation-counter--works--aux-fn-2 (e)
  "Here we show how to filter ab::de/allocation-log-entry by backtrace contents"
  (let* ((backtrace (ab::de/allocation-log-entry-backtrace e))
         (data (ab::lisp-backtrace-list backtrace))
         (found (search "test--cons-checking--maybe-break-on-global-allocation-operation-counter--works--aux-fn"
                        (car data) :test 'char-equal)))
    (if found t nil)))

#+cons-checking
(define-test test--cons-checking--maybe-break-on-global-allocation-operation-counter--works
  ;; see the description ~40 lines above
  (let ((pseudo-stream nil) (the-cons nil))
    (flet ((p (x) (push x pseudo-stream)))
      (unwind-protect
          (progn
            ;; In real world, you should compile the advice definition
            (lw:defadvice (ab::maybe-break-on-global-allocation-operation-counter test-advice-1 :around)
                (object pool e)
              (p (list :object object
                       :pool pool
                       :counter ab::*global-allocation-operation-counter*
                       :counter-from-log-entry (ab::de/allocation-log-entry-counter e)
                       :operation (ab::de/allocation-log-entry-operation e)
                       :our-function-is-found-in-backtrace
                       (test--cons-checking--maybe-break-on-global-allocation-operation-counter--works--aux-fn-2 e))))
            ;; Run test scenario, dumping data it produeces to list, and retrieve a cons it allocates
            (setq the-cons
                  (test--cons-checking--maybe-break-on-global-allocation-operation-counter--works--aux-fn #'p))
            )
        (lw:remove-advice 'ab::maybe-break-on-global-allocation-operation-counter 'test-advice-1)))
    (setf pseudo-stream (nreverse pseudo-stream))
    (setf (car the-cons) 'stub (cdr the-cons) 'stub) ; to make printing shorter in case of failure
    (assert-true
     (equalp
      `(init
        (:object ,the-cons
         :pool ab::gensym :counter 1 :counter-from-log-entry 1
         :operation :allocate :our-function-is-found-in-backtrace t)
        got-cons
        (:object ,the-cons
         :pool ab::gensym :counter 2 :counter-from-log-entry 2
         :operation :reclaim :our-function-is-found-in-backtrace t)
        end)
      pseudo-stream))
    (let* ((state (gethash the-cons ab::*cons-table*))
           (current-state (ab::cons-story-status state))
           (story (ab::cons-story-ob state)))
      (assert-eq current-state 'ab::cons-checking-object-status-reclaimed)
      (assert-equal (length story) 2) ; allocated once and reclaimed once
      )))


(defun aux-fn--test--cons-checking--reclaim-cons-twice (&key clear-contents)
  (with-simplest-test-environment ()
    (let* ((cons1 (ab::slot-value-cons 1 2)))
      (ab::reclaim-slot-value-cons cons1)
      (when clear-contents
        (setf (car cons1) nil (cdr cons1) nil))
      (ab::reclaim-slot-value-cons cons1)
      t)))

#+cons-checking
(define-test test--cons-checking--reclaim-cons-twice--it-is-cons-checking-that-detects-an-error
  ;; ensure that cons-checking is set to default value
  (assert-equal ab::cons-checking-enabled-p t)
  ;; error should be detected even though we changed contents of the cons
  (assert-error
   'error
   (aux-fn--test--cons-checking--reclaim-cons-twice :clear-contents t))
  ;; if we disable cons-checking, but do not clear cons, it is captured by normal debugging version
  (with-cons-checking-stopped
   (assert-error
   'error
    (aux-fn--test--cons-checking--reclaim-cons-twice)))
  ;; if we disable cons-checking and clear cons contents before second reclamation,
  ;; nothing prevents the error
  (with-cons-checking-stopped
   (assert-true
    (aux-fn--test--cons-checking--reclaim-cons-twice :clear-contents t)))
  ;; the conclusion from the three examples is that cons-checking is more powerful against double reclamaition than normal debugging checking
  )

(defun aux-fn--test--cons-checking--steal-avaliable-cons-and-reclaim-it ()
  (with-simplest-test-environment ()
    (let* ((cons0 (ab::slot-value-cons nil nil)) ; warm-up
           (cons1 (ab::slot-value-cons 1 2))
           (dummy1 (ab::reclaim-slot-value-cons cons0))
           cons2)
      (declare (ignore dummy1))
      (ab::reclaim-slot-value-cons cons1)
      ;; steal cons2
      (setf cons2 (cdr cons1))
      (assert (eq cons2 cons0) () "Something unexpected in test scenario")
      ;; remove car-marker so that normal debugging checker is helpless
      (setf (car cons2) nil)
      ;; feed this cons as if it was allocated normally 
      (ab::reclaim-slot-value-cons cons2))
    t))

#+cons-checking
(define-test test--cons-checking--steal-available-cons-and-reclaim-it--it-is-cons-checking-that-detects-an-error
  ;; if cons-checking is stopped, we can steal cons from the pool bypassing
  ;; an allocation mechanism and reclaim it w/o error if we change its contents
  (let ((ab::cons-checking-enabled-p nil))
    (assert-true
     (aux-fn--test--cons-checking--steal-avaliable-cons-and-reclaim-it)))
  ;; if cons-checking is enabled, error is detected. By the way we check that ab::cons-checking-enabled-p is set to its default value
  (assert-equal ab::cons-checking-enabled-p t)
  (assert-error
   'error 
   (aux-fn--test--cons-checking--steal-avaliable-cons-and-reclaim-it)))

#+cons-checking
(define-test test--cons-checking--cons-checking-enabled-p-for--pool--works-correctly
  ;; in the test--cons-checking--steal-available-cons-and-reclaim-it--it-is-cons-checking-that-detects-an-error
  ;; assert that if ab::cons-checking-enabled-p is set to t, the following code works. Now we check it for ab::cons-checking-enabled-p 
  ;; set to specific pool

  ;; problem in the pool under control - should catch the problem
  (let ((ab::cons-checking-enabled-p 'ab::slot-value))
    (assert-error 'error
     (aux-fn--test--cons-checking--steal-avaliable-cons-and-reclaim-it)))

  ;; problem in ab::slot-value pool while pool under control is ab::gensym - should miss the problem
  (let ((ab::cons-checking-enabled-p 'ab::gensym))
    (assert-true
     (aux-fn--test--cons-checking--steal-avaliable-cons-and-reclaim-it)))
  )

#+(or development under-test)
(define-test test--compare-memory-allocation--no-reclaim--expect-leak-report
  (with-simplest-test-environment ()
    (ab::compare-memory-allocation nil t)
    (ab::gensym-cons 1 1)
    (assert-pools-are-mentioned-in-compare-memory-allocation "gensym-conses")))

#+(or development under-test)
(define-test test--compare-memory-allocation--good-reclaim--no-noise
  (with-simplest-test-environment ()
    (ab::compare-memory-allocation nil t)
    (ab::reclaim-gensym-cons (ab::gensym-cons 1 1))
    (assert-compare-memory-allocation-is-silent)))
  
;; the following test is development only, because in production all 
;; cons pools are coalesced
#+development
(define-test test--compare-memory-allocation--reclaim-cons-to-wrong-pool--expect-leak-report
  (with-simplest-test-environment ()
    (ab::compare-memory-allocation nil t)
    (ab::reclaim-backtrace-cons (ab::gensym-cons 1 1))
    (assert-pools-are-mentioned-in-compare-memory-allocation
     "Gensym-Conses" "Backtrace-Conses")))


#+development
(define-test test--compare-memory-allocation--reclaim-cons-to-vector--expect-error
  (assert-error
   'error
   (with-simplest-test-environment ()
     (ab::reclaim-managed-simple-vector (ab::gensym-cons 1 1)))))

#+development
(define-test test--debug-consing--reclaim-structure-to-wrong-pool--expect-error
  (assert-error
   'error
   (with-simplest-test-environment ()
     (ab::reclaim-date-format (ab::make-function-info 'a 1)))))

#+development
(define-test test--debug-consing--reclaim-structure-twice--expect-error
  (assert-error
   'error
   (with-simplest-test-environment
       ()
     (let ((fi (ab::make-function-info 'a 1)))
       (ab::reclaim-function-info fi)
       (ab::reclaim-function-info fi)))))

#+(or development under-test)
(define-test test--debug-consing--reclaim-structure-as-vector--expect-leak-report
  (with-simplest-test-environment
      ()
    ;; warm up
    (ab::reclaim-function-info (ab::make-function-info 'a 1))
    ;; test itself
    (ab::compare-memory-allocation nil t)
    (let ((fi (ab::make-function-info 'a 1)))
      (ab::reclaim-managed-simple-vector fi))
    ;(ab::compare-memory-allocation)
    (assert-pools-are-mentioned-in-compare-memory-allocation "function-info" "managed-simple-vectors")))

#+development
(define-test test--debug-consing--modify-and-reclaim-cons--expect-error
  ;; we get circular list and cl:length fails in ab::compare-memory-allocation
  (assert-error
   'error
   (with-simplest-test-environment
       ()
     (ab::compare-memory-allocation nil t)
     (let ((fi (ab::gensym-cons 1 2)))
       (ab::reclaim-gensym-cons fi)
       (setf (car fi) 1)
       (setf (cdr fi) 2)
       (ab::reclaim-gensym-cons fi)
       (ab::compare-memory-allocation)))))

#+(or development under-test)
(define-test test--debug-consing--use-scope-conses--expect-no-noise
  (let ((ab::scope-conses (list (list nil))))
    (with-connection-test-environment ()
      (let ((warm-up (ab::make-gensym-list 2000)))
        (fill warm-up nil)
        (ab::reclaim-gensym-list warm-up))
      (ab::compare-memory-allocation nil t) 
      (let* ((ab::scope-conses ab::scope-conses))
        (dotimes (i 1000) (ab::scope-cons 1 1)))
      (assert-compare-memory-allocation-is-silent))))


;; RETURN-HERE this should go to test-gldebug.lisp
#+(and lispworks development)
(define-test test--start-consing--no-leak--no-report ()
  (with-connection-test-environment ()
    (setf ab::leaking-cons-cells nil)
    (ab::start-consing 'ab::slot-value)
    (ab::reclaim-slot-value-cons
     (ab::slot-value-cons 1 2))
    (ab::stop-consing)
    (assert-equal 0 (length ab::leaking-cons-cells))))

#+(and lispwork development)
(define-test test--start-consing--have-leak--have-report ()
  (with-connection-test-environment ()
    (setf ab::leaking-cons-cells nil)
    (ab::start-consing 'ab::slot-value)
    (ab::slot-value-cons 1 2)
    (ab::stop-consing)
    (assert-equal 1 (length ab::leaking-cons-cells))))


;;;; non-covered code report 

;; ab::managed-array-p :
;; I guess this is a coverage tool anomaly

;; allocate-managed-array :
;; make-exactly is never true (GENSYMCID-1744)

;; grow-managed-array :
;; is only called from adjust-array. 
;; situation where not (/= (length managed-array) new-spine-length) never happens
;; because adjust-final-buffer-of-managed-array is invoked instead of
;; grow-managed-array in this case

;; shrink-managed-array :
;; is only called from adjust-array
;; situation where not (/=f new-spine-length (length managed-array)) 
;; because adjust-final-buffer-of-managed-array is invoked instead of
;; grow-managed-array in this case


;; managed-svref :
;; managed-svsetf :
;;
;;In the following proof, "<==>" is logical equvalence.
;;
;;If we are in that uncovered (neq index-var index) expression
;;it follows from the embracing "if" that:
;;
;;(not (and (eq array-var managed-array)
;;          (eq index-var index)) 
;;     ) [1]

;;By definition of index-var, 
;;(eq index-var index) <==> (symbolp index)  [2]

;;By definition of array-var, 
;;(eq array-var managed-array) 
;;<==> 
;;(or (symbolp managed-array)
;;    (symbolp index)) [3]


;;Substituting [3] and [2] into [1], we get:

;;We are in this line
;;implies 
;;(not (and (eq array-var managed-array)
;;          (eq index-var index)) 
;;     )
;;which is equivalent to 
;;(not (and (or (symbolp managed-array)
;;              (symbolp index))
;;          (symbolp index))) 
;;
;;if (symbolp index) is true, this expression is false, 
;;if (symbolp index) is false, this expression is true,
;;regardless of (symbolp managed-array)
;;
;;Hence, if we are in that line, (symbolp index) is always
;;false and, by [2], index-var eq index. 
;;
;;So only one branch of if is reachable. 


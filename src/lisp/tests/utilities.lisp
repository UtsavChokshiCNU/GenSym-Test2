(in-package :tests)

(proclaim '(optimize debug))

(defun test-hash-function (generate-input-function calculate-hash-code-function 
                           amount-of-times)
  (let ((comparison-count 0)
        (map (make-hash-table)))
    (dotimes (i amount-of-times) 
      (let* ((string (funcall generate-input-function i))
             (hash-code (funcall calculate-hash-code-function 
                                 (ab::stringw string))))
        (if (gethash hash-code map)
            (incf (gethash hash-code map))
            (setf (gethash hash-code map) 1))))
    (maphash #'(lambda (key value)
                 (declare (ignore key))
                 (incf comparison-count (/ (* value (1+ value)) 2)))
             map)
    comparison-count))


(defun map-interesting-integers (fn)
  "Maps function of one argument to some integers, including values around fixnum/bignum boundaries"
  (let (result)
    (dolist (bound (list most-negative-fixnum
                         (floor (/ most-negative-fixnum 2))
                         0
                         (floor (/ most-positive-fixnum 2))
                         most-positive-fixnum))
      (dolist (i
               (list
                (- bound 2)
                (- bound 1)
                bound
                (+ bound 1)
                (+ bound 2)
                ))
        (push (funcall fn i) result)))
    (nreverse result)))


;; In LW 6.0 x64, generation 7 seem to be used for objects that survived image saving. 
;; So if we do (clean-down), all dynamically allocated fresh objects seem to move. 
;; Note that sys:in-static-area and (hcl:switch-static-allocation t) seem to not affect conses.
;; So for conses this test will likely fail.
;; Result of this test can matter for objects that we're going to pass to foreign code, or otherwise
;; use their address, hoping it won't change in time. 
;; There's no reason to test this for SBCL as we're not using it for development so this will be no op (no assertion) for SBCL
(defun assert-objects-not-moveable-by-gc (list-of-objects)
  "For LW 6.0 64, checks that objects are static (non
 moveable by gc). For other LW versions, fail. For other lisps, no-op. For chestnut, fail. Note this
 operation is very slow as it invokes clean-down"
  (let ((kind 
         #+chestnut :failure
         #+lispworks
         #+(and lispworks-64bit win32 lispworks6.0) :run
         #-(and lispworks-64bit win32 lispworks6.0) :failure
         #-(or lispworks chestnut) :success))
    (ecase kind
      (:failure
       (assert-true nil))
      (:success
       (assert-true t))
      (:run
       #+(and lispworks-64bit win32 lispworks6.0)
       (let*
           ((addrs (mapcar 'system:object-address list-of-objects))
            (dummy (hcl:clean-down))
            (new-addrs (mapcar 'system:object-address list-of-objects)))
         (declare (ignore dummy))
         (assert-equalp addrs new-addrs))
       #-(and lispworks-64bit win32 lispworks6.0)
       (error "Something is wrong in assert-objects-not-moveable-by-gc")
       ))))



(defun all-conses-of-list (list)
  (loop :for cdr :on list :collect cdr))

(defun all-conses-of-tree (x)
  (etypecase x
    (null nil)
    (atom nil)
    (cons
     (append
      (list x)
      (all-conses-of-tree (car x))
      (all-conses-of-tree (cdr x))
      ))))

(defun cons-is-on-list (cons list)
  ; true if cons is a part of toplevel structure of list
  (assert (consp cons))
  (loop :for cdr :on list
        :when (eq cons cdr)
        :do (return-from cons-is-on-list t))
  nil)

(defun test-cons-is-on-list ()
  (let ((lst (list 'a 'b 'c)))
    (dolist (x (list lst (cdr lst) (cddr lst)))
      (assert (cons-is-on-list x lst) () "Cons ~S is not on list ~S" x lst))))

(test-cons-is-on-list)

(defun all-conses-of-list-are-on-list (list where-must-be)
  (loop :for cdr :on list
        :unless
        (cons-is-on-list cdr where-must-be)
        :do (return-from all-conses-of-list-are-on-list nil))
  t)

(defun test-all-conses-of-list-are-on-list ()
  (let ((list (list 1 2 3)))
    (assert (all-conses-of-list-are-on-list list list))
    (assert (all-conses-of-list-are-on-list (cdr list) list))
    ))

(test-all-conses-of-list-are-on-list)

(defun all-elements-of-list-are-conses-on-list (list where-must-be)
  (dolist (cons list)
    (unless (cons-is-on-list cons where-must-be)
      (return-from all-elements-of-list-are-conses-on-list nil)))
  t)

(defun test-all-elements-of-list-are-conses-on-list ()
  (let* ((list (list 1 2 3))
         (conses (all-conses-of-list list)))
    (assert (all-elements-of-list-are-conses-on-list conses list))))

(test-all-elements-of-list-are-conses-on-list)

(defun list-contents-eql (l1 l2)
  "Test that correspondint elements of two different lists is eql"
  (assert (not (eq l1 l2)))
  (and
   (= (length l1) (length l2))
   (every 'eql l1 l2)))


(defun make-macroexpander-test-by-example (name docstring form)
  "Generate a test that covers macroexpansion of specific form"
  (let ((*print-case* :downcase)
        (*print-circle* nil)
        (*print-pretty* t)
        (*package* (find-package :tests)))
    (pprint
     `(define-test ,name
        ,@(when docstring (list docstring))
        (assert-equal
         (values ',(macroexpand-1 form) t)
         (macroexpand-1 ',form))))
    (values)))

(defun make-function-result-test-by-example (name docstring form)
  "Generate a test that covers result of evaluation of specific form"
  (let ((*print-case* :downcase)
        (*print-circle* nil)
        (*print-pretty* t)
        (*package* (find-package :tests)))
    (pprint
     `(define-test ,name
        ,@(when docstring (list docstring))
        (assert-equal
         ',(eval form)
         (eval ',form))))
    (values)))


(defmacro show-expr (expr &optional (stream '*trace-output*))
  "Shows expression and its value on the trace-output"
  (let ((e1-sym (make-symbol "show-expr-expr")))
    `(let ((,e1-sym ,expr))
       (format ,stream "~%~S = ~S" ',expr ,e1-sym)
       ,e1-sym)))


;;; If test-expression is false, prints it with the word "failed:" ahead
;;; And sets SUCCESS variable to nil. You should have a local SUCCESS 
;;; variable bound initially to t. Note there is no assertion. If you 
;;; include this macro into test, add (assert-true success) in the end.
(defmacro assert-for-success-maybe-print (test-expression)
  (let ((test-expr (make-symbol "TEST-EXPR")))
    `(let ((,test-expr ,test-expression))
       (unless (eval ,test-expr)
         (print `("failed:" ,,test-expr))
         (setf success nil)))))


(defun fibonacci (i)
  (cond
   ((= i 0) 1)
   ((= i 1) 1)
   (t (+ (fibonacci (- i 1)) (fibonacci (- i 2))))))


(defun validate-simple-vector-pool (pool size)
  (assert (> size 0))
  (let ((success t))
    (unless
        (labels ((i (pool2)
                   (or
                    (null pool2)
                    (and
                     (vectorp pool2)
                     (= (length pool2) size)
                     (i (svref pool2 0))))))
          (i pool))
      (let ((*print-level* 10) (*print-length* 20) (*print-circle* t))
        (show-expr `("failed at validate-simple-vector-pool" ,pool ,size))
        (setf success nil)))
    success))
    
(defun validate-simple-vector-pools ()
  ;; assert that all simple vector pools contain only vectors of proper values
  (let* ((success t)
         
         ) ; with-initialized-managed-simple-vector-allocator
    (loop for pool across ab::vector-of-simple-vector-pools
          for i from 0 do
          (unless (= i 0)
            (unless (validate-simple-vector-pool pool i)
              (setf success nil))))
    (loop for pool across ab::vector-of-oversized-simple-vector-pools
          for i from 0 do
          (unless (= i 0)
            (unless
                (validate-simple-vector-pool
                 pool
                 (* 1024 i))
              (setf success nil))))
    (assert-true success)))

;;; (vector-of-gensyms 3 "GS-" 0) ==> #(#:GS-0 #:GS-1 #:GS-2)
(defun vector-of-gensyms (length prefix initial-counter)
  (let* ((*gensym-counter* initial-counter)
         (result (make-array length)))
    (dotimes (i length)
      (setf (svref result i) (gensym prefix)))
    result))

;;; (vector-0-N-minus-1-then-nils 6 3) ==> #(0 1 2 NIL NIL NIL)
(defun vector-0-N-minus-1-then-nils (length N)
  (assert (>= length N))
  (let ((result (make-array length :initial-element nil)))
    (dotimes (i N)
      (setf (svref result i) i))
    result))

(defun vector-k---k+N-minus-1--then-nils (length k N)
  (assert (>= length N))
  (let ((result (make-array length :initial-element nil)))
    (dotimes (i N)
      (setf (svref result i) (+ i k)))
    result))

(assert (equalp (vector-k---k+N-minus-1--then-nils 3 88 2) #(88 89 NIL)))

 
;;; (vector-from-k 3 4) ==> #(4 5 6)
(defun vector-from-k (length k)
  (let ((result (make-array length :initial-element nil)))
    (dotimes (i length)
      (setf (svref result i) (+ k i)))
    result))


(defun managed-array-equal-to-vector (ma ve)
  (and
   (= (ab::managed-array-length ma) (length ve))
   (progn
     (dotimes (i (length ve))
       (unless
           (equal (ab::managed-svref ma i) (svref ve i))
         (return-from managed-array-equal-to-vector nil)))
     t)))


;; tries to check recursively arrays. When some data on recursion path 
;; becomes not an array, switches to equalp. 
(defun managed-array-equalp (a b)
  (cond
   ((not (equalp (type-of a) (type-of b)))
    nil)
   ((and (ab::managed-array-p a) (ab::managed-array-p b))
    (and
     (= (ab::managed-array-length a) (ab::managed-array-length b))
     (block test
       (dotimes (i (ab::managed-array-length a))
         (unless (managed-array-equalp
                  (ab::managed-svref a i)
                  (ab::managed-svref b i))
           (return-from test nil)))
       t)))
   (t
    (equalp a b))))

(assert (managed-array-equalp '(1 2 3) '(1 2 3)))

(assert (managed-array-equalp #(1 2 3) #(1 2 3)))

;;; Asserts that there is no simple vector leak. 
;;; To test, run with previously recorded (ab::outstanding-simple-vector-pool-vectors value
(defun no-simple-vector-leak-p (outstanding-in-the-past)
  (equal outstanding-in-the-past
         (ab::outstanding-simple-vector-pool-vectors)))


;;; returns a new list
(defun insert-into-list (list position item)
  (assert (>= position 0))
  (cond
   ((= position 0)
    (cons item list))
   (t
    (let ((prevcdr (nthcdr (- position 1) list)))
      (setf (cdr prevcdr) (cons item (cdr prevcdr)))
      list))))


(assert (equalp (insert-into-list (list 0 1 2) 0 'a)
                '(a 0 1 2)))
(assert (equalp (insert-into-list (list 0 1 2) 1 'a)
                '(0 a 1 2)))


(defun simplified-g2-type-of (g2-object)
  "It seems that G2 type system does not work until (assign-class-bit-numbers-and-vectors-to-system-classes), but we want minimal setup, maximum mocking for UT work)"
  (and (typep g2-object 'simple-vector)
       (svref (svref g2-object 1) 1)))

;; Hack to be able to map symbols to the objects they name
;; Stolen from ab::switch-to-new-empty-kb
;; Alternative approach is to decorate ab::switch-to-kb
;; But it is harder to do and I suspect ab::switch-to-kb
;; is invoked too frequently so that we can miss right value
(defun last-anonymous-kb-specific-property-list-property-name ()
  (intern
   (format nil "KB-~D" ab::last-assigned-global-kb-number) :ab))

(defun objects-with-that-name (symbol)
  (let ((ab::*current-kb-specific-property-list-property-name*
         (last-anonymous-kb-specific-property-list-property-name)))
    (ab::frame-or-frames-with-this-name symbol)))

(defun ignore-all (&rest args)
  (declare (ignore args))
  nil)

(defun constantly-t (&rest ignore)
  (declare (ignore ignore))
  t)


;;; Moved here from test-connect4.lisp

(defvar process-handle (make-symbol "UNIT-TEST"))

(defmacro with-test-environment (() &body body)
 `(progn
    #+cons-checking (ab::cons-checking-start-common-part)
    (ab::with-system-variables ('ab::ab process-handle)
     (setq ab::warning-message-level 0)
     (setq ab::loading-kb-p nil)
     ;; these are parts of RUN-AB
     (ab::assign-class-bit-numbers-and-vectors-to-system-classes)
     ;; for COLLECT-SUBCLASSES to work.
     (setq ab::classes-visited-byte-vector
	   (ab::initialize-classes-visited-byte-vector))
     (ab::switch-to-new-empty-kb)
     ,@body)))


(defmacro with-cons-checking-stopped (&body body)
  #+lispworks
  `(progn
     (assert ab::cons-checking-enabled-p () "with-cons-checking-stopped: expected that cons-checking is enabled")
     (let ((ab::cons-checking-enabled-p nil))
       ,@body))
  #-lispworks
  `(progn ,@body))

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

(defvar *thread-pond-test-global* 0)

;; linker complains about lambdas
(defun thread-pond-test-worker (task)
  (incf *thread-pond-test-global* task))

(defun not-our-worker () (sleep 1000))

(deftest test-thread-pond-add-thread
    (let* ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker))
	   (th (ab::thread-pond-add-thread tp)))
      (ab::thread-pond-start tp)
      (assert-true (tx:threadp th))
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-ocean
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let ((tp (ab::make-thread-pond 20 #'thread-pond-test-worker)))
      (ab::thread-pond-start tp)
      (ab::thread-pond-enqueue tp 1)
      (sleep 1)
      (assert-equal 1 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-enqueue
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker)))
      (ab::thread-pond-start tp)
      (ab::thread-pond-enqueue tp 1)
      (sleep 1)
      (assert-equal 1 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-enqueue-add-start
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let ((tp (ab::make-thread-pond 0 #'thread-pond-test-worker)))
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-add-thread tp)
      (ab::thread-pond-start tp)
      (sleep 1)
      (assert-equal 1 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-enqueue-same-task
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker)))
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-start tp)
      (sleep 1)
      (assert-equal 3 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-remove-thread
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let* ((tp (ab::make-thread-pond 0 #'thread-pond-test-worker))
	   (th (ab::thread-pond-add-thread tp)))
      (ab::thread-pond-start tp)
      (assert-true (ab::thread-pond-remove-thread tp th nil))
      (ab::thread-pond-enqueue tp 1)
      (sleep 1)
      (assert-equal 0 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-stop
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker)))
      (ab::thread-pond-start tp)
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-stop tp t)
      (ab::thread-pond-enqueue tp 1)
      (sleep 1)
      (assert-true (> 2 *thread-pond-test-global*))
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-stop-dont-wait
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker)))
      (ab::thread-pond-start tp)
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-stop tp nil)
      (ab::thread-pond-enqueue tp 1)
      (sleep 1)
      (assert-true (> 3 *thread-pond-test-global*))
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-restart
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker)))
      (ab::thread-pond-start tp)
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-stop tp t)
      (ab::thread-pond-enqueue tp 1)
      (ab::thread-pond-start tp)
      (sleep 1)
      (assert-equal 2 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-remove-foreign-thread
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let* ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker))
	   (th
	     (#+chestnut-3 tx:with-dynamic-area #-chestnut-3 progn
	      (tx:spawn-thread "Not ours" #'not-our-worker))))
      (ab::thread-pond-enqueue tp 1)
      (assert-true (null (ab::thread-pond-remove-thread tp th t)))
      (ab::thread-pond-start tp)
      (sleep 1)
      (assert-equal 1 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-remove-non-thread
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let* ((tp (ab::make-thread-pond 1 #'thread-pond-test-worker))
	   (th 1000))
      (ab::thread-pond-enqueue tp 1)
      (assert-true (null (ab::thread-pond-remove-thread tp th t)))
      (ab::thread-pond-start tp)
      (sleep 1)
      (assert-equal 1 *thread-pond-test-global*)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

(deftest test-thread-pond-remove-foreign-thread-from-empty-pond
    ;; threads do not inherit locals
    (setf *thread-pond-test-global* 0)
    (let* ((tp (ab::make-thread-pond 0 #'thread-pond-test-worker))
	   (th
	     (#+chestnut-3 tx:with-dynamic-area #-chestnut-3 progn
	      (tx:spawn-thread "Not ours" #'not-our-worker))))			 
      (ab::thread-pond-enqueue tp 1)
      (assert-true (null (ab::thread-pond-remove-thread tp th t)))
      (ab::thread-pond-start tp)
      #-(and lisp-unit windows (or sbcl ccl))
      (ab::reclaim-thread-pond tp)
      ))

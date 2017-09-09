;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")


;;; Special test - are run-time error caught by the test-framework in dev mode?
#+development
(deftest faulty-test
    (assert-true (/ 1 0)))

(deftest test-eq-hash-table-puthash
    (let ((table (ab::make-eq-hash-table 1 nil nil)))
      (assert-equal 1 (ab::eq-gethash table 1 1))
      (assert-equal 2 (setf (ab::eq-gethash table 1) 2))
      (assert-equal 2 (ab::eq-gethash table 1 1))
      (ab::reclaim-eq-hash-table table)))

(deftest test-eq-hash-table-keys
    (let ((geese (ab::gensym-list 1 2))
	  (table (ab::make-eq-hash-table 2 nil nil)))
      (setf (ab::eq-gethash table 1) t)
      (setf (ab::eq-gethash table 2) t)
      (let ((keys (ab::eq-hash-table-keys table)))
	(assert-true (null (ab::gensym-set-difference-using-equal keys geese)))
	(assert-true (null (ab::gensym-set-difference-using-equal geese keys)))
	(ab::reclaim-gensym-list keys))
      (ab::reclaim-gensym-list geese)
      (ab::reclaim-eq-hash-table table)))

(deftest test-eq-hash-table-keys-empty-table
    (let ((table (ab::make-eq-hash-table 2 nil nil)))
      (let ((keys (ab::eq-hash-table-keys table)))
	(assert-true (null keys))
	(ab::reclaim-gensym-list keys))
      (ab::reclaim-eq-hash-table table)))

(deftest test-eq-hash-table-keys-grown-table
    (let ((geese (ab::gensym-list 1 2))
	  (table (ab::make-eq-hash-table 1 nil nil)))
      (setf (ab::eq-gethash table 1) t)
      (setf (ab::eq-gethash table 2) t)
      (let ((keys (ab::eq-hash-table-keys table)))
	(assert-true (null (ab::gensym-set-difference-using-equal keys geese)))
	(assert-true (null (ab::gensym-set-difference-using-equal geese keys)))
	(ab::reclaim-gensym-list keys))
      (ab::reclaim-gensym-list geese)
      (ab::reclaim-eq-hash-table table)))

(deftest test-eq-hash-table-keys-duplicate-keys
    (let ((geese (ab::gensym-list 1 2))
	  (table (ab::make-eq-hash-table 2 nil nil)))
      (setf (ab::eq-gethash table 1) t)
      (setf (ab::eq-gethash table 2) t)
      (setf (ab::eq-gethash table 1) nil)
      (setf (ab::eq-gethash table 2) nil)
      (setf (ab::eq-gethash table 1) 0)
      (setf (ab::eq-gethash table 2) 0)
      (let ((keys (ab::eq-hash-table-keys table)))
	(assert-true (null (ab::gensym-set-difference-using-equal keys geese)))
	(assert-true (null (ab::gensym-set-difference-using-equal geese keys)))
	(ab::reclaim-gensym-list keys))
      (ab::reclaim-gensym-list geese)
      (ab::reclaim-eq-hash-table table)))


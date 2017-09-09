(in-package :ab)

#-SymScale ; SymScale doesn't use `available-gensym-conses'
(defun reclaim-tree-ab-test ()
	(let* ((c1 (gensym-cons 1 2))
		   (c2 (gensym-cons 3 4))
		   (c3 (gensym-cons 5 6))
		   (c4 (gensym-cons 7 c1))
		   (c5 (gensym-cons c4 c2))
		   (c6 (gensym-cons c3 8))
		   (root (gensym-cons c5 c6))
		   (count1) (count2))
		(setq count1 (length available-gensym-conses))
		(reclaim-gensym-tree root)
		(setq count2 (length available-gensym-conses))
		(lisp-unit:assert-eql 7 (- count2 count1))))

(in-package :tests)

#-SymScale
(defun reclaim-tree-test ()
  (ab::reclaim-tree-ab-test))

#-SymScale
(define-test test-z-reclaim-tree
  (let ((ab::cons-checking-enabled-p nil))
    (reclaim-tree-test)
    (format t "test reclaim-tree-test SUCCESS~%")
    (assert-true t)))

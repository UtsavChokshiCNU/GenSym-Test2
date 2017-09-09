;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

(deftest test-factions-loop-path
    (ab::with-empty-test-kb
	(let ((f (ab::make-frame 'ab::faction))
	      (w (ab::make-new-top-level-kb-workspace 'ab::kb-workspace))
	      (p (ab::make-frame 'ab::connection-post)))
	  (assert-true
	   (null
	    (loop for m being each faction-member of f
	       collect m using gensym-cons)))
	  (ab::add-subworkspace w f)
	  (ab::add-subblock p w)
	  (assert-true (eq f (faction? p)))
	  (assert-true (eq f (faction? w)))
	  (let ((b (ab::gensym-list w p))
		(d (loop for m being each faction-member of f
		      collect m using gensym-cons)))
	    (assert-true (null (ab::gensym-set-difference-using-equal b d)))
	    (assert-true (null (ab::gensym-set-difference-using-equal d b)))
	    (ab::reclaim-gensym-list b)
	    (ab::reclaim-gensym-list d))
	  (ab::remove-as-subblock-if-necessary p)
	  (let ((b (ab::gensym-list w))
		(d (loop for m being each faction-member of f
		      collect m using gensym-cons)))
	    (assert-true (null (ab::gensym-set-difference-using-equal b d)))
	    (assert-true (null (ab::gensym-set-difference-using-equal d b)))
	    (ab::reclaim-gensym-list b)
	    (ab::reclaim-gensym-list d))
	  (assert-true (null (faction? p)))
	  (ab::remove-as-subworkspace-if-necessary w)
	  (assert-true
	   (null
	    (loop for m being each faction-member of f
	       collect m using gensym-cons)))
	  (assert-true (null (faction? w)))
	  (ab::delete-frame p)
	  (ab::delete-frame w)
	  (ab::delete-frame f))))

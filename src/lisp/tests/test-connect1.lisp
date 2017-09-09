(in-package :tests)


;; Here we try using high-level functions to delete connection elements 
;; and to look if we have some memory leaks. 

(defun validate-connection-block-relationship (connection block)
  ;; we only check what we know. Maybe we should check something more
  (let* ((success t);(connections-of-node (ab::connections block))
         (connection-frame (ab::connection-frame-or-class connection)))
    ;; we use eval here to print objects which caused a failure
    (assert-for-success-maybe-print
     `(ab::connection-p ,connection))
    (assert-for-success-maybe-print
     `(ab::connection-frame-p ,connection-frame))
    (assert-for-success-maybe-print
     `(ab::connection-connected-to-block-p ,connection ,block))
    (assert-for-success-maybe-print
     `(ab::get-connection-item ,connection (ab::connections ,block)))
    success
    ))

(defun validate-connection-relationships (connection)
  ;; returns t if all is ok with this connection ends.
  (and
   (assert-true (eq connection
                    (ab::connection-for-this-connection-frame
                     (ab::connection-frame-or-class connection))))
   (validate-connection-block-relationship connection (ab::input-end-object connection))
   (validate-connection-block-relationship connection (ab::output-end-object connection))))
  

(define-test test--validate-connection-block-relationship--*--self-test ()
  (with-connection-test-environment ()
    (destructuring-bind (node1 node2 connection connection-frame workspace)
        (create-two-blocks-and-one-connection-on-a-workspace)
      (assert-true
       (validate-connection-block-relationship connection node1))
      (assert-true 
       (validate-connection-block-relationship connection node2)))))
  

(defun aux-fn--create-two-blocks-and-one-connection--reclaim-all ()
  (destructuring-bind (node1 node2 connection connection-frame workspace)
      (create-two-blocks-and-one-connection-on-a-workspace)
    (reclaim-what-was-created-by-create-two-blocks-and-one-connection-on-a-workspace node1 node2 connection connection-frame workspace)))
    
;;; This is a pattern for all tests which check for absense of memory leaks
(define-test test--create-two-blocks-and-one-connection--reclaim-all--no-memory-leak
  (with-connection-test-environment ()
    ;; warm up of allocator
    (aux-fn--create-two-blocks-and-one-connection--reclaim-all)
    ;; the test itself
    (ab::compare-memory-allocation nil t)
    (aux-fn--create-two-blocks-and-one-connection--reclaim-all)
    (assert-compare-memory-allocation-is-silent)
    ))

(define-test test--connection-flag--set-read-clear-read--expect-reasonable-result
  (with-connection-test-environment ()
    (let ((connection (third (create-two-blocks-and-one-connection-on-a-workspace)))
          (success nil))
      (ab::clear-connection-found-in-search connection)
      (let ((result (ab::connection-found-in-search-p connection)))
	(assert-false result))
      (ab::set-connection-found-in-search connection)
      (let ((result (ab::connection-found-in-search-p connection)))
	(assert-true result))
      (ab::clear-connection-found-in-search connection)
      (let ((result (ab::connection-found-in-search-p connection)))
	(assert-false result)))))

(define-test test--delete-connection-to-stub--call-it--note-deletion-of-connection-is-called
  (with-connection-test-environment ()
    (let ((connection (third (create-two-blocks-and-one-connection-on-a-workspace)))
          (success nil))
      (mock:with-wrapped-functions*
          ((ab::recompute-selection-highlights 'ignore-all))
        (mock:expect
         (
          (:call (ab::note-deletion-of-connection connection)
           :return
           ((progn (setf success t) nil)))
          )
         :for
         (ab::delete-connection-to-stub connection)))
      (assert-true success))))


;; TRIVIAL-CODE clear-connections-found-in-search

;; geometric-change-to-connection-is-temporary-p - never setq-ed, ok to be defvar

;; TESTERS-COMMENT note-change-to-connection RETURN-HERE
;; note-change-to-connection is a serious thing. Failing to call IMO should cause
;; a misbehaviour of the connection. 
;; The following things deserve testing for note-change-to-connection:
;; 1) It really notes change properly when invoked. It is simpler to test.
;; 2) It is called at all places where it is needed. This is much harder. I have no idea
;; how to test it without knowing what does "all places" mean.

(define-test test--note-change-to-connection--call-set-output-end-object--need-indexing-p-flag-is-set
  ;; setup
  (with-connection-test-environment ()
    (let ((connection (third (create-two-blocks-and-one-connection-on-a-workspace))))
      (ab::clear-connection-needs-indexing connection)
      ;; test
      ;; checking pre-conditions - these are not test assertions
      (assert (null ab::noting-changes-to-kb-p))
      (assert (null ab::geometric-change-to-connection-is-temporary-p))
      
      (mock:with-wrapped-functions*
          ((ab::|AB::WORKSPACE-SPACIAL-INDEX? -Mock-function| 'constantly-t))
        (with-mocked-macros (AB::WORKSPACE-SPACIAL-INDEX?)
          (setf (ab::output-end-object connection) nil)))

      ;; assert
      (let ((result (ab::connection-needs-indexing-p connection)))
	(assert-true result)))))

;; RETURN-HERE many code is skipped 

(define-test test--workspace-of-connection?--create-two-blocks-and-one-connection-on-a-workspace--must-exist-end-be-equal-to-that-of-nodes
  (with-connection-test-environment ()
    (destructuring-bind (node1 node2 connection . ignore)
        (create-two-blocks-and-one-connection-on-a-workspace)
      (declare (ignore ignore))
      (let ((ws1 (ab::get-workspace-if-any node1))
            (ws2 (ab::workspace-of-connection? connection)))
        (assert-eq ws1 ws2)))))

(define-test test--workspace-of-connection?--pass-nil--expect-nil
  (assert-eq (ab::workspace-of-connection? nil) nil))

;; RETURN-HERE some code is skipped

(define-test test--input-and-output-connection-predicates--run-on-test-setup--expect-reasonable-values
  (with-connection-test-environment ()
    (destructuring-bind (b1 b2 co . ignore) (create-two-blocks-and-one-connection-on-a-workspace)
      (declare (ignore ignore))
      (assert-true (eval `(ab::output-connection-p ,b1 ,co)))
      (assert-false (eval `(ab::input-connection-p ,b1 ,co)))
      (assert-false (eval `(ab::output-connection-p ,b2 ,co)))
      (assert-true (eval `(ab::input-connection-p ,b2 ,co))))))

;; RETURN-HERE some code is skipped

(define-test test--connection-frame-p--*--true-for-frame--false-for-connection-structure-and-for-block
  (with-connection-test-environment ()
    (destructuring-bind (b1 b2 co cof . ignore)
	(create-two-blocks-and-one-connection-on-a-workspace)
      (declare (ignore b2 ignore))
      (let* ((result1 (ab::connection-frame-p cof))
	     (result2 (ab::connection-frame-p b1))
	     (result3 (ab::framep co)))
	(assert-true result1)
	(assert-false result2)
      ; next assertion is to emphasize that connection structure is not a frame at all
	(assert-false result3))
      ; connection-frame-p expects a frame, hence next eval causes error in development and has undefined consequences in production. This is why it is only tested under #+development. 
      #+development
      (assert-error 'error (eval `(ab::connection-frame-p ,co)))
      )))

;; RETURN-HERE some code is skipped activate & deactivate are missing

#-ccl
(define-test test--ab-workspace-of-connection-frame--*--expect-reasonable-value
  (with-connection-test-environment ()
    (destructuring-bind (b1 b2 co cof w) (create-two-blocks-and-one-connection-on-a-workspace)
      (assert-eq
        w
	(ab::workspace-of-connection-frame cof)))))

;;; Cross-section pattern specification verification

#-lispworks
(define-test test--cross-section-pattern-definition--call-predicates-and-accessors
  (let ((e0 (cons ; pattern with regions
             (list (cons 'a 'b) (cons 'c 'd))
             (list (cons 'e 'f) (cons 'g 'h))))
        (e1 ; stripes only
         (list (cons 'e 'f) (cons 'g 'h)))
        (e0a (ab::make-cross-section-pattern
              (list (cons 'a 'b) (cons 'c 'd))
              (list (cons 'e 'f) (cons 'g 'h))))
        (e1a (ab::make-cross-section-pattern
              nil
              (list (cons 'e 'f) (cons 'g 'h)))))
    (assert-equal e0 e0a)
    (assert-equal e1 e1a)
    (let* ((result1 (ab::cross-section-regions-specified? e0))
	   (result2 (ab::cross-section-regions-specified? e1)))
      (assert-true result1)
      (assert-false result2))
    (assert-equal (ab::get-cross-section-regions e0)
                  '((a . b) (c . d)))
    (assert-equal (ab::get-cross-section-stripes e0)
		  '((e . f)(g . h)))
    (assert-equal (ab::get-cross-section-stripes e1)
                  (ab::get-cross-section-stripes e0))))

(defmacro aux-macro-with-two-connection-posts ((v1 v2) &body body)
  `(with-connection-test-environment ()
       (let ((,v1 (ab::make-entity 'ab::connection-post))
             (,v2 (ab::make-entity 'ab::connection-post)))
         (setf (ab::name-or-names-for-frame ,v1) 'ab::sym1)
         (setf (ab::name-or-names-for-frame ,v2) 'ab::sym2)
         ,@body)))

;;;; Connection post
(define-test test--connection-post-equal--call-for-eq-objects--expect-tl 
  (aux-macro-with-two-connection-posts (a b)
    (assert-true (ab::connection-post-equal a a))))

(define-test test--connection-post-equal--names-like-p--expect-t 
  (aux-macro-with-two-connection-posts (a b)
     (let ((result
	    (mock::expect ((:call (ab::name-or-names-like-p 'ab::sym1 'ab::sym2) :return (t)))
			  :for (ab::connection-post-equal a b))))
       (assert-true result))))

(define-test test--connection-post-equal--not-names-like-p--expect-nil
  (aux-macro-with-two-connection-posts (a b)
    (let ((result
	   (mock::expect ((:call (ab::name-or-names-like-p 'ab::sym1 'ab::sym2) :return (nil)))
			 :for (ab::connection-post-equal a b))))
      (assert-false result))))

;; RETURN-HERE skipped cleanup - don't know what is "unit" there. 

;; Some words must be from ab package, some can be from any package. 
(define-test test--connection-post-and-loop-for-x-being-each-connection--create-some-objects--test-loop-for-connection-of-node
  (with-connection-test-environment ()
    (destructuring-bind (n1 n2 ws1 sw2 cp1 cp2 c1 c2)
        (create-two-blocks-connected-via-connection-post)
      (assert-equal (list c1)
                    (ab::loop for x being each connection ab::of n1
                              collect x)))))


(define-test test--loop-for-x-being-each-connection--create-some-objects--test-loop-for-connection-of-node
  (with-connection-test-environment ()
    (destructuring-bind (node1 node2 connection connection-frame workspace)
        (create-two-blocks-and-one-connection-on-a-workspace)
      ;; let's add third node, connected to nothing
      (let ((node3 (create-node3-on-a-workspace workspace)))

        ;; simple loop 
        (assert-equal (list connection)
                      (ab::loop for x being each connection ab::of node1
                                collect x))
        (assert-equal nil
                      (ab::loop for x being each connection ab::of node3
                                collect x))

        ;; input-connection and output-connection
        (assert-equal (list connection)
                      (ab::loop for x being each output-connection ab::of node1
                                collect x))
        (assert-equal (list connection)
                      (ab::loop for x being each input-connection ab::of node2
                                collect x))

        (assert-equal nil
                      (ab::loop for x being each input-connection ab::of node1
                                collect x))
        (assert-equal nil
                      (ab::loop for x being each output-connection ab::of node2
                                collect x))
        (assert-equal nil
                      (ab::loop for x being each input-connection ab::of node3
                                collect x))
        (assert-equal nil
                      (ab::loop for x being each output-connection ab::of node3
                                collect x))

        ;; of-type
        (assert-equal (list connection)
                      (ab::loop for x being each connection ab::of node1
                                of-type 'ab::connection
                                collect x))
        (assert-equal nil
                      (ab::loop for x being each connection ab::of node1
                                ab::of-type 'ab::some-irrelevant-type
                                collect x))

        ;; connected-to-a-block-of-type
        (assert-equal (list connection)
                      (ab::loop for x being each connection ab::of node1
                                ab::connected-to-a-block-of-type 'ab::free-text
                                collect x))
        
        (assert-equal (list connection)
                      (ab::loop for x being each connection ab::of node1
                                ab::connected-to-a-block-of-type 'ab::block
                                collect x))

        (assert-equal nil
                      (ab::loop for x being each connection ab::of node1
                                ab::connected-to-a-block-of-type 'ab::some-irrelevant-type
                                collect x))

        ;; sides
        (assert-equal (list connection)
                      (ab::loop for x being each connection ab::of node1
                                ab::on-side-or-sides 'ab::top
                                collect connection))

        (assert-equal nil
                      (ab::loop for x being each connection ab::of node1
                                ab::on-side-or-sides '(ab::left ab::right)
                                collect connection))

        ;; port-name
        (assert-equal nil
                      (ab::loop for x being each connection ab::of node1
                                ab::at-port 'fantasy
                                collect connection))
        
        ;; see also test--loop-for-x-being-each-connection--create-some-objects--test-loop-for-connection-of-node
        
        ;; combinations of false conditions
        (assert-equal nil
                      (ab::loop for x being each connection ab::of node3
                                ab::connected-to-a-block-of-type 'ab::block
                                collect x))

        (assert-equal nil
                      (ab::loop for x being each input-connection ab::of node3
                                ab::of-type 'ab::block
                                collect x))

      ))))


;; we don't know how to create a named port, so we use ab::make-transient-connection for that. 
(define-test test--loop-for-x-being-each-connection--create-some-objects--test-loop-for-connection-of-node
  (with-connection-test-environment ()
    ;; warm up of the allocator
    (destructuring-bind (w n1 n2)
        (create-two-blocks-on-a-workspace :make-empty-connection-item-tables nil)
      (let* ((frame
              (mock:with-wrapped-functions*
                  ((ab::recompute-selection-highlights 'ignore-all))
                (ab::make-transient-connection 
                 'ab::connection
                 n1 'ab::if-does-not-exist 'ab::top 5 'ab::input-end-port-of-my-connection
                 n2 'ab::if-does-not-exist 'ab::top 5 'ab::output-end-port-of-my-connection
                 t 'ab::diagonal nil t)))
             (connection
              (ab::connection-for-this-connection-frame frame)
              ))
        (assert-equal (list connection)
                      (ab::loop for x being each connection ab::of n1
                                ab::at-port 'ab::input-end-port-of-my-connection
                                collect x))
        (assert-equal nil
                      (ab::loop for x being each connection ab::of n1
                                ab::at-port 'fantasy
                                collect x))
        ))))


;; It is not clear what "connections" is from the definition of the macro, but we tooks a lool at use
;; cases
(define-test test--connection-exist-p--*--*
  (with-connection-test-environment ()
    (destructuring-bind (ws node1 connection1 node2 connection2 node3)
        (create-three-blocks-chained-with-connections)
      (declare (ignore ws))
      (let ((result1 (ab::connection-exist-p connection1 (ab::connections node1)))
	    (result2 (ab::connection-exist-p connection1 (ab::connections node3)))
	    (result3 (ab::connection-exist-p connection2 (ab::connections node2)))
	    (result4 (ab::connection-exist-p connection2 (ab::connections node3))))
	(assert-true result1)
	(assert-false result2)
	(assert-true result3)
	(assert-true result4)))))

;; RETURN-HERE skipped downgrade-connections
(define-test test--connection-structures--*--*
  (with-connection-test-environment ()
    (destructuring-bind (ws node1 connection1 node2 connection2 node3)
        (create-three-blocks-chained-with-connections)
      (assert-equal (list connection1)
                    (ab::connection-structures node1))
      (assert-true (set-equal (list connection1 connection2)
                              (ab::connection-structures node2))))))

(define-test test--get-connection-class-given-*--*--*
  (with-connection-test-environment ()
    (destructuring-bind (node1 node2 connection connection-frame workspace)
        (create-two-blocks-and-one-connection-on-a-workspace)
      (declare (ignore node1 node2 workspace))
      (let ((result1 (ab::get-connection-class-given-connection connection))
	    (result2 (ab::get-connection-class-given-connection-frame-or-class connection-frame)))
	(assert-eq result1 'ab::connection)
	(assert-eq result2 'ab::connection)))))

(define-test test--slot-description-for-connection-class--right-branch--*
  (with-connection-test-environment ()
    (let* ((result1
	    (ab::ab-typep (ab::slot-description-for-connection-class
			   'ab::connection
			   'ab::cross-section-pattern)
			  'ab::slot-description))
	   (result2
	    (ab::ab-typep (ab::slot-description-for-connection-class
			   'AB::G2GL-STANDARD-CONNECTION
			   'ab::cross-section-pattern)
			  'ab::slot-description)))
    (assert-true result1)
    (assert-true result2))))

(define-test test--slot-description-for-connection-class--odd-branch--*
  ;; this branch acts odd: when we ask for non-existent connection subclass,
  ;; it assumes connection
  (with-connection-test-environment ()
    (let ((result
	   (ab::ab-typep (ab::slot-description-for-connection-class
			  'blub ; non-existant connection class
			  'ab::cross-section-pattern)
			 'ab::slot-description)))
      (assert-true result))))

;; TESTERS-COMMENT 
;; This should be in test-roles.lisp, but IMO it is a good way to cross-check if we set up connections successfully 
#| 
 (define-test test--connection-setup--search-for-directly-connected-entities--should-find-it
  (with-connection-test-environment
      ()
    (destructuring-bind (node1 node2 connection connection-frame workspace)
        (create-two-blocks-and-one-connection-on-a-workspace)
      (mock:with-wrapped-functions* ((ab::serve-item-p 'constantly-t))
        (assert-equal (list connection-frame)
                      (ab::search-for-directly-connected-entities node1 'ab::block nil nil nil nil nil nil))))))
|#

;(define-test test--connection-setup--search-for-directly-connected-entities-through-the-connection-post--should-find-it

#|
 (with-connection-test-environment
      ()
    (destructuring-bind (node1 node2 ws1 ws2 cp1 cp2 c1 c2)
        (create-two-blocks-connected-via-connection-post)
      (mock:with-wrapped-functions* ((ab::serve-item-p 'constantly-t))
        (ab::search-for-directly-connected-entities node1 'ab::block nil nil nil nil nil nil))))
 
 (validate-connection-relationships (ab::connection-for-this-connection-frame (objects-with-that-name 'ab::c4)))

|# 


(define-test test--subclasses--*--*
  (assert-false
   (set-difference
    '(AB::CONNECTION AB::NETWORK-WIRE AB::G2GL-STANDARD-CONNECTION AB::G2GL-LINK-CONNECTION)
    (with-connection-test-environment () (ab::subclasses 'ab::connection)))))

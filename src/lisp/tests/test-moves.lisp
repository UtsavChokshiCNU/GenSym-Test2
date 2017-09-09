(in-package :tests)

;; function is rather trivial, we test it solely due to #+connections-v2 being there
#+(and connections-v2 (or sbcl lispworks))
(defun aux-fn-test--gather-connections-for-block--correct-result ()
  (destructuring-bind (node1 node2 connection connection-frame workspace)
      (create-two-blocks-and-one-connection-on-a-workspace)
    (let ((connection-list (ab::gensym-list 'something-irrelevant)))
      (setq connection-list (ab::gather-connections-for-block node1 connection-list))
      (assert-equal connection-list (list connection 'something-irrelevant))
      (setq connection-list (ab::gather-connections-for-block node1 connection-list))
      (assert-equal connection-list (list connection 'something-irrelevant))
      (ab::reclaim-gensym-list connection-list))
    (reclaim-what-was-created-by-create-two-blocks-and-one-connection-on-a-workspace node1 node2 connection connection-frame workspace)))

#+(and connections-v2 (or sbcl lispworks))
(define-test test--gather-connections-for-block--correct-result
             (with-connection-test-environment ()
               ;; warm up the memory allocator
               (aux-fn-test--gather-connections-for-block--correct-result)))


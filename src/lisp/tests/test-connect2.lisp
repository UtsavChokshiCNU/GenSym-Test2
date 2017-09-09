(in-package :tests)

;; RETURN-HERE many functions skipped

(define-test test--get-block-at-other-end-of-connection--*--*
  (with-connection-test-environment ()
    (destructuring-bind (node1 node2 connection connection-frame workspace)
        (create-two-blocks-and-one-connection-on-a-workspace)
      (let ((node3 (create-node3-on-a-workspace workspace)))
        (assert-eq node1 (ab::get-block-at-other-end-of-connection connection node2))
        (assert-eq node2 (ab::get-block-at-other-end-of-connection connection node1))
        ;; MISSING-ASSERT next assertion shows an undesired result: block is not connected to the connection.  
        ;; Should add (assert-for-develompent (connection-connected-to-block-p connection block)) to the function under test
        ;; In ideal world and under develompent, this assertion should fail
        (assert-eq node1 (ab::get-block-at-other-end-of-connection connection node3))
        ))))

(define-test test--connection-connected-to-block-p--*--*
  (with-connection-test-environment ()
      (destructuring-bind (node1 node2 connection connection-frame workspace)
          (create-two-blocks-and-one-connection-on-a-workspace)
        (let ((node3 (create-node3-on-a-workspace workspace)))
          (assert-true (ab::connection-connected-to-block-p connection node1))
          (assert-true (ab::connection-connected-to-block-p connection node2))
          (assert-false (ab::connection-connected-to-block-p connection node3))
          ))))

(define-test test--get-direction-of-connection--*--*
  (with-connection-test-environment ()
      (destructuring-bind (node1 node2 connection connection-frame workspace)
          (create-two-blocks-and-one-connection-on-a-workspace)
        (assert-eq 'ab::output (ab::get-direction-of-connection connection node1))
        (assert-eq 'ab::input (ab::get-direction-of-connection connection node2))
        ;; RETURN-HERE cover even-if-not-directed?
        ;; this function will return bad result if the block is not connected to the connection
        )))

;; RETURN-HERE set-input-end-of-connection is called from delete-junction-if-appropriate only. We need a test case which invokes it.

(define-test test--set-input-end-of-connection--connect-to-other-block--check-with-loop
  (with-connection-test-environment ()
    (destructuring-bind (node1 node2 connection connection-frame workspace)
        (create-two-blocks-and-one-connection-on-a-workspace)
      (let ((node3 (create-node3-on-a-workspace workspace)))
        ;; run
        (ab::delete-connection-in-block node2 connection t)
        (ab::add-connection-in-block node3 connection)
        ; (ab::set-input-end-of-connection connection node3 'bottom 5)
        ;; assert
        (assert-equal
         (list node1)
         (ab::loop for x being each connection ab::of node3
                   collect (ab::get-block-at-other-end-of-connection connection x)))))))

(defun aux-fn-test--create-stubs-and-connections-and-destroy-them (do-assertions)
  (destructuring-bind (w n1 n2)
      (create-two-blocks-on-a-workspace :make-empty-connection-item-tables nil)
    (ab::make-stubs n1 '((nil
                          ab::connection
                          ab::input
                          ab::top
                          5
                          nil
                          ab::diagonal
                          )))
    (let* ((stub1
            (ab::loop for x being each
                      connection ab::of n1
                      do (return x)))
           ;(leaking-frame-serial-number (ab::frame-serial-number-for-connection stub1))
           )
      (when do-assertions
        (assert-true (validate-connection-relationships stub1)))
      
      (ab::delete-connection stub1)

      ;; uncommenting following together with definition of leaking-frame-serial-number
      ;; will reclaim leaking frame-serial-numbers      
      ; (ab::reclaim-frame-serial-number leaking-frame-serial-number)
      )

    (reclaim-what-was-created-by-create-two-blocks-on-a-workspace w n1 n2
                                                                  :reclaim-connection-item-tables nil)
    ))
  
(define-test test--create-stubs-and-connections--connections-are-fine
  (with-connection-test-environment ()
    (aux-fn-test--create-stubs-and-connections-and-destroy-them t)
    ))

;; GENSYMCID-1806
#-exclude-possible-bugs
(define-test test--create-stubs-and-connections-and-destroy-them--no-leaks
  (with-connection-test-environment ()
    ;; warm up of the allocator
    (aux-fn-test--create-stubs-and-connections-and-destroy-them nil)
    ;; test
    (ab::compare-memory-allocation nil t)
    (aux-fn-test--create-stubs-and-connections-and-destroy-them nil)
    (assert-compare-memory-allocation-is-silent)))

;; read-kb -> g2-stream-with-open-stream -> ab::G2-STREAM-OPEN-FOR-BINARY-INPUT
;; 
        
(defun aux-fn-test--make-transient-connection-and-destroy-it (do-assertions un1 un2)
  (destructuring-bind (w n1 n2)
      (create-two-blocks-on-a-workspace :make-empty-connection-item-tables nil)
    (let* ((frame
            (mock:with-wrapped-functions*
                ((ab::recompute-selection-highlights 'ignore-all))
              (ab::make-transient-connection 
               'ab::connection
               (when un1 n1)
               (when un1 'ab::if-does-not-exist)
               (when un1 'ab::top)
               (when un1 5)
               (when un1 'ab::input-end-port-of-my-connection)

               (when un2 n2)
               (when un2 'ab::if-does-not-exist)
               (when un2 'ab::top)
               (when un2 5)
               (when un2 'ab::output-end-port-of-my-connection)
               
               t 'ab::diagonal nil t)))
           (connection
            (ab::connection-for-this-connection-frame frame)
            ))
      (when do-assertions
        (assert-true (validate-connection-relationships connection)))
      
      (ab::delete-connection connection)
      
      ;; uncommenting following together with definition of leaking-frame-serial-number
      ;; will reclaim leaking frame-serial-numbers      
      ; (ab::reclaim-frame-serial-number leaking-frame-serial-number)
      )
    
    (reclaim-what-was-created-by-create-two-blocks-on-a-workspace w n1 n2
                                                                  :reclaim-connection-item-tables nil)
    ))

(define-test test--make-transient-connection--connection-is-fine
  (with-connection-test-environment ()
    (aux-fn-test--make-transient-connection-and-destroy-it t t t)
    ))

(define-test test--make-transient-connection--connection-is-fine-2
  (with-connection-test-environment ()
    (aux-fn-test--make-transient-connection-and-destroy-it t nil t)
    ))

(define-test test--make-transient-connection--connection-is-fine-3
  (with-connection-test-environment ()
    (aux-fn-test--make-transient-connection-and-destroy-it t t nil)
    ))

;; GENSYMCID-1806
#-exclude-possible-bugs
(define-test test--make-transient-connection--make-connection-and-destroy-it--no-leaks
  (with-connection-test-environment ()
    ;; warm up of the allocator
    (aux-fn-test--make-transient-connection-and-destroy-it nil t t)
    ;; test
    (ab::compare-memory-allocation nil t)
    (aux-fn-test--make-transient-connection-and-destroy-it nil t t))
    (assert-compare-memory-allocation-is-silent)
    )
  

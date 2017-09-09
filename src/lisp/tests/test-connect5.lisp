(in-package :tests)

(defun aux-fn-test--connect-loose-end-to-block--structure-ok (where-to-bend?)
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
           (loose-end
            (ab::input-end-object-internal stub1)))

      (assert-true (ab::loose-end-p-function loose-end))
      
      (let* ((connection
              (ab::connect-loose-end-to-block loose-end n2 'ab::top 6 1 where-to-bend?))
             (connection-p
              (ab::connection-p connection))
             (connection-frame
              (ab::connection-frame-or-class connection)))
        (assert-true connection-p)
        (validate-connection-block-relationship connection n1)
        (validate-connection-block-relationship connection n2)
        (let* ((expected-connection-input-as-list 
                (ab::eval-list 'ab::item n2 'ab::side 'ab::top 'ab::position 6))
               (expected-connection-input
                (ab::allocate-evaluation-structure
                 expected-connection-input-as-list ; list is reclaimed here
                 ))
               (actual-connection-input
                (ab::get-connection-input connection-frame)))
          (assert-true (ab::compare-structure-contents expected-connection-input actual-connection-input t))
          (ab::reclaim-evaluation-structure
           expected-connection-input)
          (ab::reclaim-evaluation-structure
           actual-connection-input)
          (list connection)
          (ab::loop ab::for c2 ab::being ab::each ab::connection ab::of n1 ab::collecting c2))
        (let ((ab::delete-connections-without-leaving-stubs? t))
          (ab::delete-item (ab::connection-frame-or-class connection)))
        
        (reclaim-what-was-created-by-create-two-blocks-on-a-workspace w n1 n2)))))

(define-test test--connect-loose-end-to-block-bending-at-loose-end--structure-ok
   (with-connection-test-environment ()
     (aux-fn-test--connect-loose-end-to-block--structure-ok 'ab::loose-end)))

(define-test test--connect-loose-end-to-block-bending-at-destination--structure-ok
   (with-connection-test-environment ()
     (aux-fn-test--connect-loose-end-to-block--structure-ok 'ab::destination)))



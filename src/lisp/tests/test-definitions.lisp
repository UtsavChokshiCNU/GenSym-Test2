(in-package :tests)

;;;; So far we only test parts of frames4.lisp required to test connections

;;;; Functions to test for connections-v2: 

; optional ab::get-connection-given-stub-designation
;ab::change-portname-given-stub-designation
;ab::insert-portname-for-connection

#+(and connections-v2 (or sbcl lispworks))
(define-test test--insert-portname-for-connection--portname-is-ok-and-no-leaks
  (mock:with-wrapped-functions*
      ((ab::recompute-selection-highlights 'ignore-all))
    (with-connection-test-environment ()
      (destructuring-bind (w n1 n2)
          (create-two-blocks-on-a-workspace)
        (let* ((conn-frame (ab::make-transient-connection 
                            'ab::connection
                            n1
                            'ab::if-does-not-exist
                            'ab::top
                            5
                            nil
                            n2
                            'ab::if-does-not-exist
                            'ab::top
                            7
                            nil
                            t
                            'ab::diagonal
                            nil
                            t))
               (connection
                (ab::connection-for-this-connection-frame conn-frame))
               (item
                (ab::get-connection-item connection (ab::connections n1))))
          
          (ab::insert-portname-for-connection n1 connection 'ab::my-connection-s-name)

          (assert-equal
           '(ab::my-connection-s-name)
           (or (ab::connection-item-output-names item)
               (ab::connection-item-input-names item)))


          (ab::delete-connection connection)
          
          (reclaim-what-was-created-by-create-two-blocks-on-a-workspace w n1 n2
                                                                        :reclaim-connection-item-tables nil)
          
          )))))

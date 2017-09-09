(in-package :tests)

;;;; So far we only test parts of frames4.lisp required to test connections

#+sbcl
(define-test test--get-workspace-if-any--create-two-blocks-and-one-connection-on-a-workspace--must-exist
  (with-connection-test-environment ()
    (destructuring-bind (node1 node2 connect . ignore)
        (create-two-blocks-and-one-connection-on-a-workspace)
      (declare (ignore ignore))
      (let ((ws1 (ab::get-workspace-if-any node1))
            (ws2 (ab::get-workspace-if-any node2)))
        (assert-eq ws1 ws2)
        (assert-eq 'ab::kb-workspace (ab::class ws2))))))

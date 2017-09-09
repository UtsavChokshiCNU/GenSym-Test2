(in-package :tests)

(defun test-conclude-into-attribute-component-1 ()
  (let* ((frame (ab::make-frame 'ab::g2-list)))
    (let ((ret1 (ab::conclude-into-attribute-component
		  frame
		  'ab::list-size
		  nil
		  10
		  nil
		  '(ab::attribute ab::list-size nil ab::*current-computation-frame*)))
	  (ret2 (ab::conclude-into-attribute-component
		  frame
		  'ab::allow-duplicate-elements
		  nil
		  (ab::make-evaluation-truth-value ab::truth)
		  nil
		  '(ab::attribute ab::allow-duplicate-elements nil ab::*current-computation-frame*))))
      (assert-true (ab::string=w ret1 (ab::string-to-wide-string "The attribute LIST-SIZE of G2-LIST-XXX-1 is read-only.")))
      (assert-true (not ret2)))))

(define-test test-conclude-into-attribute-component
  (with-connection-test-environment ()
    (mock::expect
      ((:call (ab::truth-threshold-parameter-function)
        :return (800)))
      :for
      (test-conclude-into-attribute-component-1))))

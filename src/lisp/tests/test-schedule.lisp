(in-package :tests)

(defun my-test-function ())

(defun init-task ()
  (let ((task (ab::make-schedule-task nil)))
    (setf (ab::schedule-task-function task) 'my-test-function)
    (setf (ab::schedule-task-argument-count task) 0)
    task))


(define-test-fixture test-execute-schedule-task
    (:setup ((task (init-task)))
            #+development
            (setf ab::pseudo-run-light-enabled-p nil))

  (:tests
   #+ignore ; thread slot has been removed.
   (test-schedule-task-has-nil-in-thread-slot
    (assert-eq nil (ab::schedule-task-thread task)))))

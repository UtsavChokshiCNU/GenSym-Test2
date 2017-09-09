(in-package :tests)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun make-var (format name)
    (intern (format nil format name)))

  (defun make-args-var (mock-name)
    (make-var "*~a-ARGS*" mock-name))

  (defun make-results-var (mock-name)
    (make-var "*~a-RESULTS*" mock-name)))

(defun funcall-string (function-name args)
  (format nil "(~a~{ ~a~})" function-name args))

(defmacro defmock (name args)
  (let ((results (intern (format nil "*~a-RESULTS*" name)))
        (arguments (make-args-var name)))
    `(progn
       (defparameter ,results nil)
       (defparameter ,arguments nil)
       (defun ,name ,args
         (let ((funcall-form (funcall-string ',name (list ,@args))))
           (when (assert-false (null ,arguments) 
                               (format nil "Unexpected call ~a~%" funcall-form))
             (let ((expected-args (pop ,arguments)))
               (assert-equal expected-args (list ,@args)
                             (format nil "Expected ~a, but received ~a~%" 
                                     (funcall-string ',name expected-args)
                                     funcall-form)))
             (pop ,results)))))))

(defmacro clear (mock-name)
  `(progn
     (setf ,(make-args-var mock-name) nil)
     (setf ,(make-results-var mock-name) nil)))

(defmacro expect ((fn-name &rest args) &optional return results)
  `(progn 
     (push (list ,@args) ,(make-args-var fn-name))
     (push ,results ,(make-results-var fn-name))))

(defmacro verify (fn-name)
  `(assert-false ,(make-args-var fn-name)))


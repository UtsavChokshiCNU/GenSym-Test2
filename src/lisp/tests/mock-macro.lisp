;;;; Mocking macros. 

;;; Author : budden73

;;; So far we only can mock macros which evaluate all their arguments from left to 
;;; right just like functions do. We use *macroexpand-hook*. I didn't find a use of 
;;; *macroexpand-hook* in G2 so I hope we are ok. To mock a macro, do the following:
#|
 (in-package :tests)
 (enable-macroexpand-hook-for-mocking-macros)
 (prepare-macro-for-mocking 'sample-macro-for-mocking)
  ;; macro can be defined after it is prepared for mocking
 (defmacro sample-macro-for-mocking (x y) `(/ (+ ,x ,y) 2))
  ;; recompile all clients of the macro
 (eval '(defun client-of-sample-macro-for-mocking ()
          (sample-macro-for-mocking 1 2)))
 (compile 'client-of-sample-macro-for-mocking)
  ;; do tests
  ;; |TESTS::SAMPLE-MACRO-FOR-MOCKING -Mock-function| will be called instead
  ;; or calling macroexpansion code of sample-macro-for-mocking
 (with-mocked-macros (sample-macro-for-mocking)
  (mock:expect
   (
    (:call (|TESTS::SAMPLE-MACRO-FOR-MOCKING -Mock-function| 1 2) :return ('whatever-i-want))
   )
   :for (client-of-sample-macro-for-mocking))) 
  ==> 
  WHATEVER-I-WANT
 
|#

(in-package :mock-macro)

(defvar *macros-to-support-mocking* nil)

(defun mock-macros-macroexpand-hook (expander form env)
  (cond
   ((and (consp form)
         (member (car form) *macros-to-support-mocking*))
    (values
     `(maybe-mock ,form
       ,(funcall expander form env))
     t))
   (t
    (funcall expander form env))))

(defun prepare-macro-for-mocking (macro-function-name)
  "This macro will support mocking after you recompile all clients of the macro"
  (assert (symbolp macro-function-name))
  (pushnew macro-function-name *macros-to-support-mocking*)
  (let ((mock-function-name (mock-function-name macro-function-name)))
    (eval `(defvar ,mock-function-name nil "This variable is t when this macro is mocked"))
    (eval `(defun ,mock-function-name (&rest args)
             (error "(~S~{ ~S~}) should not be called directly. Mock it" ',mock-function-name args)))))

(defun unprepare-macro-for-mocking (macro-function-name)
  "This function will not support mocking after you recompile all clients of the macro"
  (setf *macros-to-support-mocking* (delete macro-function-name *macros-to-support-mocking*)))

(defun enable-macroexpand-hook-for-mocking-macros ()
  (unless (eq *macroexpand-hook* 'funcall) 
    (cerror "Continue"
     "You are about to replace non-standard *macroexpand-hook* ~S. Bad consequences are expected"
     *macroexpand-hook*))
  (setf *macroexpand-hook* 'mock-macros-macroexpand-hook)
  )


(defun set-default-macroexpand-hook ()
  (setf *macroexpand-hook* 'funcall)
  )

#| FIXME implement this
 (defmacro def-mock-for-macro (macro-function-name args &body body)
  "Defines an argument transformer function which controls evaluation of macro arguments in mocking mode"
  `(defun ,(mock-function-name macro-function-name) (args) 
  )
|#

(defun mock-function-name (macro-function-name)
  "Returns a symbol which would be called instead of that macro"
  (assert (symbolp macro-function-name))
  (let ((*package* (find-package :keyword))
        (macro-function-name-package (symbol-package macro-function-name)))
    (assert macro-function-name-package)
    (intern
     (format nil "~S -Mock-function" macro-function-name)
     macro-function-name-package)))

(defmacro maybe-mock (original-form expanded-form)
  (assert (consp original-form))
  (assert (symbolp (car original-form)))
  (let* ((macro-name (car original-form))
         (mock-function-name (mock-function-name macro-name))
         (original-args (cdr original-form)))
    `(cond
      (,mock-function-name ; this is a reference to variable!
       (,mock-function-name ,@original-args) ; FIXME here we must process args in a special way!
       )
      (t
       ,expanded-form))))

(defmacro with-mocked-macros (macro-function-names &body body)
  "Part of macro mocking suite. See the example at the beginning of file where the macro is defined"
  (dolist (macro-function-name macro-function-names)
    (assert (symbolp macro-function-name))
    ;; It would be better to test in runtime also, but let it be as it is
    (assert (find macro-function-name *macros-to-support-mocking*) ()
      "~S does not support mocking" macro-function-name))
  `(let ,(mapcar (lambda (x) `(,(mock-function-name x) t)) macro-function-names)
     ,@body))

  
      

    

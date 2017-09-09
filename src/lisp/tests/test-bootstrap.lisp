(in-package :tests)

#+lispworks
(progn

  (defmacro define-dspec-test (def-to-test alias)
    (let ((parser-test-name 
           (intern (concatenate 'string "TEST-DSPEC-PARSER-FOR-" 
                                (symbol-name def-to-test))))
          (alias-test-name 
           (intern (concatenate 'string "TEST-DSPEC-ALIAS-FOR-" 
                                (symbol-name def-to-test)))))
      `(progn
         (define-test ,parser-test-name
           (assert-equal 'dspec:name-only-form-parser 
                         (dspec:get-form-parser ',def-to-test)))

         (define-test ,alias-test-name
           (assert-equal '(,alias a) 
                         (dspec:canonicalize-dspec '(,def-to-test a)))))))

  (define-dspec-test ab::defun cl:defun)
  (define-dspec-test ab::defmacro cl:defmacro)
  (define-dspec-test ab::defun-allowing-lisp-pathnames cl:defun)

  (define-test test-ab-defmacro
    (assert-expands '(eval-when (:compile-toplevel :load-toplevel :execute) 
                      (ab::define-dspec-alias defun-a defun) 
                      (defmacro defun-a nil 
                        (ab::record-macro-use (quote defun-a)) NIL))
                      (ab::defmacro defun-a ()))))

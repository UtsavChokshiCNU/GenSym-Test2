(in-package :tests)


(define-test test-gensym-enough-namestring  
  (let ((test-convertible-thing (ab::make-gensym-pathname-structure-macro
                                 :UNSPECIFIC
                                 #w"\d" 
                                 '(:ABSOLUTE #w"branches" #w"trunk" #w"src" #w"kbs")
                                 nil nil nil))
        (default (ab::initialize-default-gensym-pathname-defaults))
        (res))
    (setf res (ab::gensym-enough-namestring  test-convertible-thing default))
    (assert-true (= 0 (ab::wide-string-compare res #w"d:\\branches\\trunk\\src\\kbs\\" nil nil)))))

(define-test test2-gensym-enough-namestring  
  (let ((test-convertible-thing (ab::make-gensym-pathname-structure-macro
                                 :UNSPECIFIC
                                 #w"\d" 
                                 '(:ABSOLUTE #w"branches" #w"trunk" #w"src" #w"kbs")
                                 #w"utilities.kb" nil nil))
        (default (ab::initialize-default-gensym-pathname-defaults))
        (res))
    (setf res (ab::gensym-enough-namestring  test-convertible-thing default))
    (assert-true (= 0 (ab::wide-string-compare res #w"d:\\branches\\trunk\\src\\kbs\\utilities.kb" nil nil)))))
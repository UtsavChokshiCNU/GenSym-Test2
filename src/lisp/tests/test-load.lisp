(in-package :tests)

(define-test test-load-in-package
  (assert-true (car (multiple-value-list 
		     (find-symbol "EXPORT-FROM-AB-LISP-PACKAGE" "CL-USER")))))

(defvar *fasl-extension* 
  #+sbcl sb-fasl:*fasl-file-type* 
  #+clozure (pathname-type ccl:*.fasl-pathname*)
  #+lispworks system:*binary-file-type*)

(defvar *boot-info-patern*
  `(,*fasl-extension* "lisp" "kb" "kl" ab::downcase nil
                      #+sbcl ,(merge-pathnames 
                               (truename "../load.lisp"))
                      #-sbcl ,(truename "../load.lisp") nil nil))

(define-test test-bootstrap-information
  (assert-equal *boot-info-patern* ab::bootstrap-information))

#|
    This test is designed to detect the issue causing 
    "Help! 11 nested errors. SB-KERNEL:*MAXIMUM-ERROR-DEPTH* exceeded."
    error on bootstrap.lisp compilation when translating G2.
|#
(define-test test-AB-uses
  (assert-equal "AB-LISP" (package-name (first (package-use-list "AB")))))

(in-package :tests)

(define-test test-pathname-is-root-directory-p-for-empty-pathname
  (with-connection-test-environment ()
    (assert-false (ab::pathname-is-root-directory-p 
                   (ab::parse-win32-filename "")))))
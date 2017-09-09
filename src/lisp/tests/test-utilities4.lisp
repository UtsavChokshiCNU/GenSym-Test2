(in-package :tests)

(define-test test-compute-text-hash-code
  (let ((test-strings
         (vector "" "uuid-1" "UUID-1" (string (code-char 1055)) 
                 (string (code-char 1087)) "?" 
                 "123456789012345678901234567890a" 
                 "123456789012345678901234567890A"
                 (concatenate '(vector character) "123456789012345678901234567890" 
                              (string (code-char 1103)))
                 (concatenate '(vector character) "123456789012345678901234567890" 
                              (string (code-char 1071)))))
        (test-hash-codes
         (if (ab::g2-enterprise-p)
             (vector 0 221850692 221850692 63 63 63 109119068 109119068
                     109119090 109119090)
             (vector 0 2883 2883 63 63 63 155340885 155340885 155340923 
                     155340923)))
        (string))
    (loop for i below (length test-strings) 
       do
       (setf string (aref test-strings i))
       (assert-equal (aref test-hash-codes i) 
                     (ab::compute-text-hash-code 
                      (ab::stringw string)) string))))

(define-test test-compute-text-hash-code-collisions
  (assert-equal (if (ab::g2-enterprise-p) 1721600 128391432)
                (test-hash-function 
                 #'(lambda (number) (format nil "uuid-~A" number))
                 #'ab::compute-text-hash-code 300000)))

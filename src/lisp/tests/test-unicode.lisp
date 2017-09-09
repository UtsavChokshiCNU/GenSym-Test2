;;;; Created on 2010-01-29 09:49:36
(in-package :tests)

;The function is noly for the length of the 32bit positive fixnum
(defmacro fixnum-length-32bit (fixnum-to-write)
  `(let ((v ,fixnum-to-write))
     (declare (fixnum v))
         (if (< v 10000) ;the scope of fixnum is 0~9999
             (if (< v 100) 
                 (if (< v 10) 1 2)    ;the scope of fixnum is 0~99
                 (if (< v 1000) 3 4)) ;the scope of fixnum is 100~9999
             (if (< v 1000000)  ;the scope of fixnum is 10000 ~ 99999999
                 (if (< v 100000) 5 6) ;the scope of fixnum is 10000 ~ 999999
                 (if (< v 10000000) 7  ;the scope of fixnum is 1000000 ~ 99999999
                     (if (< v 100000000) 8 9))))))

;The function is noly for the length of the number scope 0 ~ 999'999'999'999
(defmacro fixnum-twrite-length-2 (fixnum-to-write)
  `(let ((v ,fixnum-to-write))
     (declare (fixnum v))
     ;;Judge the fixnum whether it is a longer than 999999
     (if (<= v 999999)
         (fixnum-length-32bit v)
         ;;if the fixnum is a long number, calc the floor number with 1000000
         ;;Then calc the length of floor number by fixnum-length function
         ;;The real length of the fixnum is that the floor lenght plus 6
         (multiple-value-bind (tmpf tmpr)
             (floor v 1000000)
             (+ 6 (fixnum-length-32bit tmpf)))))) 
                                                            
 ;The function calc the length of the number scope
 ; 999'999'999'999'999'999 ~ -999'999'999'999'999'999                                                          
(defmacro fixnum-twrite-length (fixnum-to-write)
  `(let ((v ,fixnum-to-write))
     (declare (fixnum v))
     (if (and (<= v 999999) (>= v -999999))
         (+ (if (< v 0) 1 0)
             (fixnum-length-32bit (abs v)))
         ;;if the fixnum is a long number, calc the floor number with 1000000
         ;;Then calc the length of floor number by fixnum-length function
         ;;The real length of the fixnum is that the floor lenght plus 6
         (multiple-value-bind (tmpf tmpr)
             (floor (abs v) 1000000)
              (+ (if (< v 0) 1 0)
                  6
                  (fixnum-twrite-length-2 tmpf)))))) 

(define-test test-fixnum-twrite-length
  (assert-equal '1 (fixnum-twrite-length 0))
  (assert-equal '2 (fixnum-twrite-length 17))
  (assert-equal '3 (fixnum-twrite-length 115))
  (assert-equal '4 (fixnum-twrite-length 1000))
  (assert-equal '5 (fixnum-twrite-length 12589))
  (assert-equal '6 (fixnum-twrite-length 125688))
  (assert-equal '7 (fixnum-twrite-length 5488888))
  (assert-equal '8 (fixnum-twrite-length 58555555))
  (assert-equal '9 (fixnum-twrite-length 100000000))
  (assert-equal '10 (fixnum-twrite-length -100000000))
  (assert-equal '9 (fixnum-twrite-length -12365478))
  (assert-equal '8 (fixnum-twrite-length -1452585))
  (assert-equal '7 (fixnum-twrite-length -152458))
  (assert-equal '6 (fixnum-twrite-length -25845))
  (assert-equal '5 (fixnum-twrite-length -1542))
  (assert-equal '4 (fixnum-twrite-length -458))
  (assert-equal '3 (fixnum-twrite-length -25))
  (assert-equal '2 (fixnum-twrite-length -2)))

(defun get-foreign-string-type (string-length)
  #+lispworks `(simple-array (unsigned-byte 8) (,string-length))
  #+clozure 'ccl:macptr
  #+sbcl '(sb-alien:alien (* (sb-alien:signed 8))))

(defun foreign-string-length (string)
  #+lispworks (length string)
  #+clozure (1+ (length (ccl:%get-cstring string))))

(defun get-foreign-string-char (string position)
  #+lispworks (aref string position)
  #+clozure (ccl:%get-unsigned-byte string position)
  #+sbcl (sb-alien:deref string position))

(defmacro check-copy-foreign-string (string-to-check string-length first-code)
  `(progn 
     (assert-equal 
      (get-foreign-string-type ,string-length) (type-of ,string-to-check))
     #-sbcl (assert-equal 
             ,string-length (foreign-string-length ,string-to-check))
     (assert-equal ,first-code (get-foreign-string-char ,string-to-check 0))
     (assert-equal 
      0 (get-foreign-string-char ,string-to-check (1- ,string-length)))))

(define-test copy-foreign-string-arg-if-appropriate-type-for-simple-string
  (check-copy-foreign-string
   (ab::copy-foreign-string-arg-if-appropriate "black") 6 (char-code #\b)))

(define-test copy-foreign-string-arg-if-appropriate-type-for-word-array
  (check-copy-foreign-string 
   (ab::copy-foreign-string-arg-if-appropriate 
    (replace (ab::make-wide-string-function 2) (list 71 50))) 3 71))

#+lispworks
(define-test test-copy-out-alien-string-into-original-string
  (let* ((foreign-array 
          (fli:allocate-foreign-object 
           :type :char :nelems 10
           :initial-contents (list #\0 #\1 #\Null #\2 #\3 #\4 #\5 #\6 #\7 #\8)))
         (lisp-string "abcdef4512")
         (expected-string "01cdef4512")
         (result-string 
          (ab::copy-out-alien-string-into-original-string foreign-array 
                                                          lisp-string)))
    (setf (aref expected-string 2) #\Null)
    (assert-equal expected-string result-string)
    (fli:free-foreign-object foreign-array)))
    
(define-test test-make-and-initialize-new-decade-table
  (let ((table (ab::make-and-initialize-new-decade-table 16 1)))
    (assert-equal 1d0 (svref table 0))))

(define-test test-hash-wide-string-hash-code-for-empty-string
  (assert-equal 0 (ab::hash-wide-string (ab::stringw ""))))

(define-test test-hash-wide-string-hash-code
  (assert-equal 221850692 (ab::hash-wide-string (ab::stringw "uuid-1"))))

(define-test test-hash-wide-string-collisions
  (assert-equal 1721600 
                (test-hash-function 
                 #'(lambda (number) (format nil "uuid-~A" number))
                 #'ab::hash-wide-string 300000)))

#+ignore ; assert-expands are not consistent among different Lisp platforms.
(define-test test-xor-hash-expr
  (assert-expands 
   '(setq accumulator
         (ab::logxorf (ab::+f (ab::ashf (ab::logandf accumulator 2097151) 7)
                              (ab::ashf accumulator -21))
                      (ab::char-codew (ab::charw wide-string index))))
   (ab::xor-hash-expr accumulator 
                      (ab::char-codew (ab::charw wide-string index)) 7)))


(define-test test--copy-byte-vector-16-portion-carefully
  ;; specially for GENSYMCID-1852, may not cover all cases necessary
  ;; for complete testing of the function
  (with-simplest-test-environment ()
      (assert-true
       (equalp
        (ab::string-to-wide-string "bccde")
        (let ((a (read-from-string "#w\"abcde\""))) 
          ;; must not update literal data so create it every time
          (ab::copy-byte-vector-16-portion-carefully a 1 a 0 2)
          a)))
    (assert-true
     (equalp
      (ab::string-to-wide-string "aabde")
      (let ((a (read-from-string "#w\"abcde\"")))
        ;; must not update literal data so create it every time
        (ab::copy-byte-vector-16-portion-carefully a 0 a 1 2)
        a)))))

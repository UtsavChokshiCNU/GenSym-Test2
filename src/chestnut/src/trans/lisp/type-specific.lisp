;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; type-specific.lisp - Host definitions of type-specific operators
;;;
;;; Author :  Bill Brodie
;;; Date   :  29 Nov 1991
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/type-specific.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:14 $")

(defmacro define-type-specific-operator (result-type arg-type suffixes args &rest operators)
  ;; Generate (Lisp) definitions for type-specific operators
  (let ((form (list 'progn))
	(args-with-types
	 (mapcar #'(lambda (arg) ``(the ,',arg-type ,,arg))
		 args)))
    (dolist (suffix (if (atom suffixes) (list suffixes) suffixes)
		    (nreverse form))
      (dolist (operator operators)
	(let ((new-operator
	       (intern
		(concatenate 'string (string operator) (string suffix))
		"TRUN")))
	  (push
	   `(defmacro ,new-operator ,args
	      `(the ,',result-type
		    (,',operator ,,@args-with-types)))
	   form))))))

(defmacro define-optional-type-specific-operator (result-type arg-type suffixes &rest operators)
  ;; Always (X &OPTIONAL Y); generate 2 possible expansions
  (let ((form (list 'progn)))
    (dolist (suffix (if (atom suffixes) (list suffixes) suffixes)
		    (nreverse form))
      (dolist (operator operators)
	(let ((new-operator
	       (intern
		(concatenate 'string (string operator) (string suffix))
		"TRUN")))
	  (push
	   `(defmacro ,new-operator (x &optional y)
	      (if y
		  `(the ,',result-type
			(,',operator (the ,',arg-type ,x) (the ,',arg-type ,y)))
		`(the ,',result-type
		      (,',operator (the ,',arg-type ,x)))))
	   form))))))

#-gclisp
(define-type-specific-operator fixnum fixnum % (x y)
  + * /)

#-gclisp
(define-type-specific-operator t fixnum % (x y)
  < <= = >= > /=)

(define-type-specific-operator fixnum fixnum % (x y)
  max min mod rem abs ash
  ldb logand logandc2 logior logtest logxor logeqv)

(define-type-specific-operator fixnum fixnum % (x y z)
  dpb)

(define-type-specific-operator fixnum fixnum % (x)
  1+ 1- isqrt logcount lognot)

(define-type-specific-operator t fixnum % (x)
  plusp minusp zerop logbitp evenp oddp)

#-:gclisp
(define-optional-type-specific-operator fixnum fixnum %
  -)

(define-optional-type-specific-operator fixnum fixnum %
  ceiling floor truncate)

(defmacro trun:lsh% (integer bits)
  `(the fixnum (ash (the fixnum ,integer)
		    (the (and fixnum
			      (integer 0 *))
			 ,bits))))

(defmacro trun:rsh% (integer bits)
  `(the fixnum (ash (the fixnum ,integer)
		    (the (and fixnum (integer * 0))
			 (- (the (and fixnum
				      (integer 0 *))
				 ,bits))))))

(define-type-specific-operator double-float double-float (%d %rd) (x y)
  + * / expt max min)

(define-type-specific-operator double-float double-float (%d %rd) (x)
  1+ 1- abs cos exp sin sqrt tan)

(define-type-specific-operator t double-float (%d %rd) (x)
  minusp plusp)

(define-type-specific-operator t double-float (%d %rd) (x y)
  < <= = >= > /=)

(define-optional-type-specific-operator double-float double-float (%d %rd)
  - atan fround log)

(define-optional-type-specific-operator integer double-float (%d %rd)
   ceiling floor round truncate)

(defmacro trun:unbox%d (x)
  `(the double-float ,x))

(defmacro trun:box%d (x)
  `(the double-float ,x))

;;;
;;; Modify macros
;;;

;; Provide both host and Translator definitions for modify macros

(define-modify-macro trun:incf% (&optional (delta 1)) trun:+%)

(define-modify-macro trun:decf% (&optional (delta 1)) trun:-%)

(define-translator-modify-macro trun:incf%
  :post-place-lambda-list (&optional (delta 1))
  :function trun:+%
  :doc
  "The read-modify-write macro INCF%.
   The new-value function is +%.")

(define-translator-modify-macro trun:decf%
  :post-place-lambda-list (&optional (delta 1))
  :function trun:-%
  :doc
  "The read-modify-write macro DECF%.
   The new-value function is -%.")

#|
(defmacro trun:incf% (x &optional y)
  (if y
      `(the fixnum (setf (the fixnum ,x)
			 (trun:+% ,x ,y)))
    `(the fixnum (setf (the fixnum ,x)
		       (trun:1+% ,x)))))

(defmacro trun:decf% (x &optional y)
  (if y
      `(the fixnum (setf (the fixnum ,x)
			 (trun:-% ,x ,y)))
    `(the fixnum (setf (the fixnum ,x)
		       (trun:1-% ,x)))))
|#

;;; Type-specific operators on cons cells.

(defmacro trun:%m-cdr (obj)
  `(cdr (the cons ,obj)))

(defmacro trun:%m-car (obj)
  `(car (the cons ,obj)))

(defmacro trun:%m-caar (obj)
  `(trun:%m-car (trun:%m-car ,obj)))
(defmacro trun:%m-cadr (obj)
  `(trun:%m-car (trun:%m-cdr ,obj)))
(defmacro trun:%m-cdar (obj)
  `(trun:%m-cdr (trun:%m-car ,obj)))
(defmacro trun:%m-cddr (obj)
  `(trun:%m-cdr (trun:%m-cdr ,obj)))

(defmacro trun:%m-caaar (obj)
  `(trun:%m-car (trun:%m-car (trun:%m-car ,obj))))
(defmacro trun:%m-caadr (obj)
  `(trun:%m-car (trun:%m-car (trun:%m-cdr ,obj))))
(defmacro trun:%m-cadar (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-car ,obj))))
(defmacro trun:%m-caddr (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr ,obj))))
(defmacro trun:%m-cdaar (obj)
  `(trun:%m-cdr (trun:%m-car (trun:%m-car ,obj))))
(defmacro trun:%m-cdadr (obj)
  `(trun:%m-cdr (trun:%m-car (trun:%m-cdr ,obj))))
(defmacro trun:%m-cddar (obj)
  `(trun:%m-cdr (trun:%m-cdr (trun:%m-car ,obj))))
(defmacro trun:%m-cdddr (obj)
  `(trun:%m-cdr (trun:%m-cdr (trun:%m-cdr ,obj))))

(defmacro trun:%m-caaaar (obj)
  `(trun:%m-car (trun:%m-car (trun:%m-car (trun:%m-car ,obj)))))
(defmacro trun:%m-caaadr (obj)
  `(trun:%m-car (trun:%m-car (trun:%m-car (trun:%m-cdr ,obj)))))
(defmacro trun:%m-caadar (obj)
  `(trun:%m-car (trun:%m-car (trun:%m-cdr (trun:%m-car ,obj)))))
(defmacro trun:%m-caaddr (obj)
  `(trun:%m-car (trun:%m-car (trun:%m-cdr (trun:%m-cdr ,obj)))))
(defmacro trun:%m-cadaar (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-car (trun:%m-car ,obj)))))
(defmacro trun:%m-cadadr (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-car (trun:%m-cdr ,obj)))))
(defmacro trun:%m-caddar (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-car ,obj)))))
(defmacro trun:%m-cadddr (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr ,obj)))))
(defmacro trun:%m-cdaaar (obj)
  `(trun:%m-cdr (trun:%m-car (trun:%m-car (trun:%m-car ,obj)))))
(defmacro trun:%m-cdaadr (obj)
  `(trun:%m-cdr (trun:%m-car (trun:%m-car (trun:%m-cdr ,obj)))))
(defmacro trun:%m-cdadar (obj)
  `(trun:%m-cdr (trun:%m-car (trun:%m-cdr (trun:%m-car ,obj)))))
(defmacro trun:%m-cdaddr (obj)
  `(trun:%m-cdr (trun:%m-car (trun:%m-cdr (trun:%m-cdr ,obj)))))
(defmacro trun:%m-cddaar (obj)
  `(trun:%m-cdr (trun:%m-cdr (trun:%m-car (trun:%m-car ,obj)))))
(defmacro trun:%m-cddadr (obj)
  `(trun:%m-cdr (trun:%m-cdr (trun:%m-car (trun:%m-cdr ,obj)))))
(defmacro trun:%m-cdddar (obj)
  `(trun:%m-cdr (trun:%m-cdr (trun:%m-cdr (trun:%m-car ,obj)))))
(defmacro trun:%m-cddddr (obj)
  `(trun:%m-cdr (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr ,obj)))))


(defmacro trun:%m-nth (n list)
  `(nth ,n (the cons ,list)))
		
(defmacro trun:%m-rest (obj)
  `(cdr (the cons ,obj)))

(defmacro trun:%m-first (obj)
  `(car (the cons ,obj)))

(defmacro trun:%m-second (obj)
  `(trun:%m-car (trun:%m-cdr ,obj)))

(defmacro trun:%m-third (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr ,obj))))

(defmacro trun:%m-fourth (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr ,obj)))))

(defmacro trun:%m-fifth (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr ,obj))))))

(defmacro trun:%m-sixth (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr
	(trun:%m-cdr (trun:%m-cdr ,obj)))))))

(defmacro trun:%m-seventh (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr
	(trun:%m-cdr (trun:%m-cdr ,obj))))))))

(defmacro trun:%m-eighth (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr
     (trun:%m-cdr (trun:%m-cdr
	(trun:%m-cdr (trun:%m-cdr ,obj)))))))))

(defmacro trun:%m-ninth (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr
     (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr
	(trun:%m-cdr (trun:%m-cdr ,obj))))))))))

(defmacro trun:%m-tenth (obj)
  `(trun:%m-car (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr
     (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr (trun:%m-cdr
	(trun:%m-cdr (trun:%m-cdr ,obj)))))))))))


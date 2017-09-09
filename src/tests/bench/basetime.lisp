;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: USER -*-
(in-package 'user)



;;;; Module BASE-TIME

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All rights reserved.

;; Jim Allard and Chris Morel




;;; This function, `base-time', is used to measure the execution time of
;;; various lisp arithmetic and pointer following operations on various
;;; platforms.  There is a similar function implemented for C.  The result of
;;; this test is used in the benchmark measurements of G2.
;;;
;;; The main loop is executed max-count times and the time elapsed during its
;;; execution is returned.  Time is measured in terms of internal real time.
;;; The elapsed time is divided by internal-time-units-per-second. 
;;;
;;; The test should be efficient and make use of type declarations.  The test
;;; performs some computations involving integer and float arrays and follows
;;; some pointers.




;;; TO RUN: Execute the BASE-TIME function optionally passing in the number of loop
;;;   iterations.  The default is 100,000.  The function init-base-time is
;;;   called at load time.
;;;
;;; OUTPUT: After executing, time statistics are printed.




;;; BEFORE COMPILING (IMPORTANT):
;;;
;;; EXECUTE THE FORM:
;;;   (proclaim '(optimize (speed 3) (safety 0) (compilation-speed 0)))
;;;
;;;   THIS MUST BE DONE BEFORE THE FILE IS COMPILED!!  The same form is executed
;;;   in this file, but it is too late to be noticed by the compiler!
;;;
;;; NO-FLOATS: The base-time test is compiled into the NO-FLOATS version
;;;   when :no-floats pushed onto *features*.  This is the default.
;;;   Computations involving floats would cause a garbage collect and give us
;;;   misleading timing results.
;;;
;;; FLOATS: to compile the floats (and integer) test comment out the following
;;;   form that pushes :no-floats onto *features*.



(proclaim '(optimize (speed 3) (safety 0) (compilation-speed 0)))

(eval-when (compile eval load) (pushnew :no-floats *features*))

;;; If :NO-FLOATS is in *features*, all floating point operations are taken out of
;;; the test.





(defvar int-array (make-array '(100) :initial-element 1))
#-no-floats
(defvar float-array (make-array '(100) :element-type 'double-float :initial-element 1.0d0))


;;; Int-array-list and float-arrary-list are circular lists containing the the
;;; integer array and float array respectively.  These are used to test pointer
;;; access.  They are initialized with init-base-time.

(defvar int-array-list nil)
#-no-floats
(defvar float-array-list nil)

(defun init-base-time () 
  (setq int-array-list (list int-array))
  (setf (cdr int-array-list) int-array-list)

  #-no-floats
  (setq float-array-list (list float-array))
  #-no-floats
  (setf (cdr float-array-list) float-array-list)
  nil)

;; Initialize on load.
(init-base-time)


(defmacro +f (x y)
  `(the fixnum (+ (the fixnum ,x) (the fixnum ,y))))

(defmacro -f (x y)
  `(the fixnum (- (the fixnum ,x) (the fixnum ,y))))

(defmacro *f (x y)
  `(the fixnum (* (the fixnum ,x) (the fixnum ,y))))

(defmacro >=f (x y)
  `(>= (the fixnum ,x) (the fixnum ,y)))

(defmacro mod-f (x y)
  `(the fixnum (mod (the fixnum ,x) (the fixnum ,y))))


(defmacro +e (x y)
  `(the double-float (+ (the double-float ,x) (the double-float ,y))))

(defmacro -e (x y)
  `(the double-float (- (the double-float ,x) (the double-float ,y))))

(defmacro *e (x y)
  `(the double-float (* (the double-float ,x) (the double-float ,y))))

(defmacro /e (x y)
  `(the double-float (/ (the double-float ,x) (the double-float ,y))))




;;; `BASE-TIME' is the top-level function for the base-time test.  It takes an
;;; optional argument which determines the maximum number of iterations for the
;;; test.  It has a default value of 100,000.  The current real time is measured
;;; before and after the test.  Time measurements are printed after the test
;;; completes.  Time is measured in clock time, not cpu time.  This function has
;;; been optimized using type declarations.

(defun base-time (&optional (max-count 100000))
  (declare (fixnum max-count))
  (let ((current-int-array-cons int-array-list)
	#-no-floats
	(current-float-array-cons float-array-list)
	current-int-array
	#-no-floats
	current-float-array
	(start-time nil)
	end-time
	elapsed-time
	elapsed-seconds)
    (format t "~%Starting ~a iterations..." max-count)
    (setq start-time (get-internal-real-time))
    (do ((counter 0 (+f counter 1)))
	((>=f counter max-count)
	 (setq end-time (get-internal-real-time))
	 (setq elapsed-time (- end-time start-time))
	 (setq elapsed-seconds 
	       (* (/ elapsed-time internal-time-units-per-second) 1.0))
	 (format t "~%Start time: ~a~
                    ~%End time:   ~a~
                    ~%Elapsed time: ~a~
                    ~%Internal-time-units-per-second: ~a~
                    ~%Seconds: ~a~
                    ~%Iterations per second: ~a"
		 start-time end-time 
		 elapsed-time internal-time-units-per-second elapsed-seconds
		 (if (= elapsed-seconds 0)
		     ;; prevent division by 0.
		     max-count
		     (/ max-count elapsed-seconds)))

	 (if (= elapsed-seconds 0)
	     max-count
	     (/ max-count elapsed-seconds)))
      (declare (fixnum counter))

      (setq current-int-array-cons (cdr current-int-array-cons))
      (setq current-int-array (car current-int-array-cons))
      #-no-floats
      (setq current-float-array-cons (cdr current-float-array-cons))
      #-no-floats
      (setq current-float-array (car current-float-array-cons))

      (base-time-computation current-int-array
			     #-no-floats current-float-array
			     counter))))




;;; `BASE-TIME-COMPUTATION' is the function that performs the calculations for
;;; the base time test.  It is called once per test iteration with the current
;;; integer and float arrays and the iteration counter.  It computes the array
;;; indices and performs integer and floating point operations, storing the
;;; result in the two arrays.

(defun base-time-computation (current-int-array
			      #-no-floats
			      current-float-array
			      counter)
  (declare (fixnum counter))
  (let ((index-1 0)
	(index-2 0)
	(index-3 0)
	(index-4 0))
    (declare 
      (fixnum index-1) (fixnum index-2) (fixnum index-3) (fixnum index-4))
    
    (setq index-1 (mod-f counter 100))
    (setq index-2 (mod-f (+f counter 1) 100))
    (setq index-3 (mod-f (+f counter 2) 100))
    (setq index-4 (mod-f (+f counter 3) 100))
    
    (setf (svref current-int-array index-1)
	  (mod-f
	    (*f (-f (+f (svref current-int-array index-1)
			(svref current-int-array index-2))
		    (svref current-int-array index-3))
		index-1)
	    ;; prevents bignums.
	    100))

    #-no-floats
    (setf (aref (the (simple-array double-float) current-float-array)
		index-1)
	  (/e
	    (*e (-e (+e (aref (the (simple-array double-float)
				   current-float-array)
			      index-1)
			(aref (the (simple-array double-float)
				   current-float-array)
			      index-2))
		    (aref (the (simple-array double-float) current-float-array)
			  index-3))
		(aref (the (simple-array double-float) current-float-array)
		      index-4))
	    (aref (the (simple-array double-float) current-float-array)
		  index-1)))))


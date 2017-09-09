;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR5

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David


(declare-forward-references
  (explanation-related-features-enabled-func?	function grammar7)
  (compile-simulation-formula-for-stack		function stack-comp))

;;;; Attribute grammar and attribute printing





;; Slot-value compilers should return second arg with bad-phase!!!


;; This is called by writer for default overrides. It gives it a null second arg.


(def-slot-value-writer attribute (attribute)
  (write-attribute attribute))

(defun-simple write-attribute (attribute)
  (setq leave-text-representation-as-a-single-line? t)
  (cond
    ((null attribute) (twrite-string "none"))

    ((managed-float-p attribute)
     (print-constant attribute 'number))

    ((slot-value-number-p attribute)
     (print-constant attribute 'number))

    ((symbolp attribute)
     (print-constant attribute 'symbol))
    
    ((text-string-p attribute)
     (setq leave-text-representation-as-a-single-line? nil)
     (tformat "~s" attribute)		; writes string parsably
     )

    ((slot-constantp attribute)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant attribute)
       (get-unit-from-slot-constant attribute)))

    ((evaluation-value-p attribute)
     (write-evaluation-value attribute))

    ((not (framep attribute))
     #+development
     (cerror
       "Continue"
       "Slot value writer for attribute received ~a, which it couldn't handle."
       attribute)
     (twrite-string "<error printing attribute>"))

    (t    ;must be an entity
     (write-entity-in-slot attribute))))

(def-slot-value-writer item-or-datum-or-no-item-attribute
    (attribute)
  (setq leave-text-representation-as-a-single-line? t)
  (cond
    ((null attribute) (twrite-string "none"))

    ((slot-value-number-p attribute)
     (print-constant attribute 'number))

    ((symbolp attribute)
     (print-constant attribute 'symbol))
    
    ((text-string-p attribute)
     (setq leave-text-representation-as-a-single-line? nil)
     (tformat "~s" attribute))

    ((slot-constantp attribute)
     (let ((slot-value (first attribute)))
       (cond
	 ((text-string-p slot-value)	  
	  (setq leave-text-representation-as-a-single-line? nil)
	  (tformat "~s" slot-value))	; prints string parsably
	 (t
	  (print-constant
	    (get-slot-value-number-or-string-from-slot-constant attribute)
	    (get-unit-from-slot-constant attribute))))))

    ((evaluation-value-p attribute)
     (let ((in-text-for-item-or-value-p t))
       (write-evaluation-value attribute)))
    
    ((entity-p attribute)    ;must be an entity
     (write-entity-in-slot attribute))

    (t
     #+development
     (cerror
       "Continue"
       "Slot value writer for attribute received ~a, which it couldn't handle."
       attribute)
     (twrite-string "<error printing attribute>"))))

(def-slot-value-writer item-or-datum-attribute (attribute)
  (setq leave-text-representation-as-a-single-line? t)
  (cond
    ((null attribute) (twrite-string "none"))

    ((slot-value-number-p attribute)
     (print-constant attribute 'number))

    ((symbolp attribute)
     (print-constant attribute 'symbol))
    
    ((text-string-p attribute)
     (setq leave-text-representation-as-a-single-line? nil)
     (tformat "~s" attribute))

    ((slot-constantp attribute)
     (let ((slot-value (first attribute)))
       (cond
	 ((text-string-p slot-value)	  
	  (setq leave-text-representation-as-a-single-line? nil)
	  (tformat "~s" slot-value))
	 (t
	  (print-constant
	    (get-slot-value-number-or-string-from-slot-constant attribute)
	    (get-unit-from-slot-constant attribute))))))

    ((evaluation-value-p attribute)
     (let ((in-text-for-item-or-value-p t))
       (write-evaluation-value attribute)))

    ((entity-p attribute)    ;must be an entity
     (write-entity-in-slot attribute))

    (t
     #+development
     (cerror
       "Continue"
       "Slot value writer for attribute received ~a, which it couldn't handle."
       attribute)
     (twrite-string "<error printing attribute>"))))

(def-slot-value-writer datum-attribute (attribute)
  (setq leave-text-representation-as-a-single-line? t)
  (cond
    ((null attribute) (twrite-string "none"))

    ((slot-value-number-p attribute)
     (print-constant attribute 'number))

    ((symbolp attribute)
     (print-constant attribute 'symbol))
    
    ((text-string-p attribute)
     (setq leave-text-representation-as-a-single-line? nil)
     (tformat "~s" attribute))

    ((slot-constantp attribute)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant attribute)
       (get-unit-from-slot-constant attribute)))

    ((evaluation-value-p attribute)
     (let ((in-text-for-item-or-value-p t))
       (write-evaluation-value attribute)))))

(def-slot-value-writer structure-attribute (structure)
  (let ((in-text-for-item-or-value-p t))
    (write-evaluation-structure structure)))

(def-slot-value-writer sequence-attribute (sequence)
  (let ((in-text-for-item-or-value-p t))
    (write-evaluation-sequence sequence)))

(def-slot-value-writer number-attribute (number)
  (cond
    ((slot-value-number-p number)
     (print-constant number 'number))
    ((slot-constantp number)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant number)
       (get-unit-from-slot-constant number)))
    (t 
     #+development
     (cerror "grammar5" "error in number-attribute writer"))))

(def-slot-value-writer float-attribute (number)
  (cond
    ((slot-value-number-p number)
     (print-constant number 'number))
    ((slot-constantp number)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant number)
       (get-unit-from-slot-constant number)))
    (t 
     #+development
     (cerror "grammar5" "error in float-attribute writer"))))
  
(def-slot-value-writer integer-attribute (number)
  (cond
    ((slot-value-number-p number)
     (print-constant number 'number))
    ((slot-constantp number)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant number)
       (get-unit-from-slot-constant number)))
    (t
     #+development
     (cerror "grammar5" "error in integer-attribute writer"))))

(defun write-general-interval-attribute (number)
  (cond
    ((slot-value-number-p number)
     (print-constant number 'seconds))
    ((slot-constantp number)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant number)
       'seconds))
    (t
     #+development
     (cerror "grammar5" "error in interval-attribute writer"))))

(def-slot-value-compiler interval-attribute (parse-result)
  (car parse-result))

(def-slot-value-compiler interval-integer-attribute (parse-result)
  (car parse-result))

(def-slot-value-compiler interval-float-attribute (parse-result)
  (coerce-phrase-number-to-float (car parse-result)))


(def-slot-value-writer interval-attribute (number)
  (write-general-interval-attribute number))

(def-slot-value-writer interval-integer-attribute (number)
  (write-general-interval-attribute number))

(def-slot-value-writer interval-float-attribute (number)
  (write-general-interval-attribute number))


(defun write-general-time-stamp-attribute (number)
  (cond
    ((slot-value-number-p number)
     (print-constant number 'time-stamp))
    ((slot-constantp number)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant number)
       'time-stamp))
    (t
     #+development
     (cerror "grammar5" "error in time-stamp-attribute writer"))))

(def-slot-value-writer time-stamp-attribute (number)
  (write-general-time-stamp-attribute number))

(def-slot-value-writer time-stamp-integer-attribute (number)
  (write-general-time-stamp-attribute number))

(def-slot-value-writer time-stamp-float-attribute (number)
  (write-general-time-stamp-attribute number))


;;; The special variable current-ddd.dddd-format? is normally bound to its
;;; global binding of nil.  However, a few key functions for formatting user
;;; defined attributes bind it if appropriately in order to get the writer to
;;; choose the right numeric format.

(defvar current-ddd.dddd-format? nil)

(defun write-general-ddd.dddd-format-attribute (number)
  (let ((value
	  (if (slot-value-number-p number)
	      number
	      (if (slot-constantp number)
		  (get-slot-value-number-or-string-from-slot-constant number)))))
    (if value
	(if current-ddd.dddd-format?
	    (twrite-number-per-format
	      (slot-value-number-value value)
	      current-ddd.dddd-format?)
	    (print-constant value 'number))
	#+development
	(cerror "grammar5" "error in ddd.dddd-format-attribute writer"))))

(def-slot-value-writer ddd.dddd-format-attribute (number)
  (write-general-ddd.dddd-format-attribute number))

(def-slot-value-writer ddd.dddd-format-float-attribute (number)
  (write-general-ddd.dddd-format-attribute number))

(def-slot-value-writer ddd.dddd-format-integer-attribute (number)
  (write-general-ddd.dddd-format-attribute number))

(def-structure (date-format
		    (:constructor
		      make-date-format (date-format-quantity-attribute
					 date-format-integer-attribute
					 date-format-float-attribute
					 date-format-name-string)))
    date-format-quantity-attribute
    date-format-integer-attribute
    date-format-float-attribute
    date-format-name-string)

;;; need function accessors for forward reference in definitions.lisp
(defun date-format-quantity-attribute-function (date-format)
  (date-format-quantity-attribute date-format))

(defun date-format-integer-attribute-function (date-format)
  (date-format-integer-attribute date-format))

(defun date-format-float-attribute-function (date-format)
  (date-format-float-attribute date-format))


(defmacro def-date-format (name interval? grammar-right-hand-sides slot-writer-body)
  (let* ((format-name (if interval? (build-ab-symbol name 'as 'interval) name))
	 (quantity-attribute (build-ab-symbol format-name 'attribute))
	 (integer-attribute (build-ab-symbol format-name 'integer 'attribute))
	 (float-attribute (build-ab-symbol format-name 'float 'attribute))
	 (writer-name (build-ab-symbol 'write format-name 'attribute)))

    `(progn
       (setf (date-format-description ',format-name)
	     (make-date-format
	       ',quantity-attribute
	       ',integer-attribute
	       ',float-attribute
	       ,(twith-output-to-gensym-string
		  (twrite-symbol name)
		  (when interval?
		    (twrite " ")
		    (twrite-symbol 'as)
		    (twrite " ")
		    (twrite-symbol 'an)
		    (twrite " ")
		    (twrite-symbol 'interval)))))
       ,(if interval?
	    `(add-grammar-rules '((attribute-type-modification
				   ('formatted 'as ',name 'as 'an 'interval)
				   (format-override ,format-name))
				  (format? (',name 'as 'an 'interval) ,format-name)))
	    `(add-grammar-rules '((attribute-type-modification
				   ('formatted 'as ',name)
				   (format-override ,format-name))
				  (format? ',name ,format-name))))
       (add-grammar-rules '((,integer-attribute ,quantity-attribute (1) car)
			    (,float-attribute ,quantity-attribute (1) car coerce-phrase-number-to-float)))
       (add-grammar-rules
	 '(,@(loop for rhs in grammar-right-hand-sides
		   collect `(,quantity-attribute ,@rhs))))
       (defun ,writer-name (value)
	 (with-temporary-gensym-float-creation ,writer-name
	   (let ((number (if (slot-value-number-p value)
			     value
			     (get-slot-value-number-or-string-from-slot-constant value))))
	   ,(if interval?
		`(let ((seconds number))
		   ,slot-writer-body)
		`(multiple-value-bind (seconds minutes hours day month year)
		     (decode-current-time number)
		   ;; suppress not-used messages
		   seconds minutes hours day month year
		   ,slot-writer-body)))))
       (def-slot-value-writer ,quantity-attribute (number)
	 (,writer-name number))
       (def-slot-value-writer ,integer-attribute (number)
	 (,writer-name number))
       (def-slot-value-writer ,float-attribute (number)
	 (,writer-name number)))))

(defun decode-current-time (time)
  (let ((unix-time
	  (cond ((fixnump time)
		 (+e (managed-float-value (clock-get g2-time-at-start))
		     (coerce-fixnum-to-gensym-float time)))
		((gensym-float-p time)
		 (+e (managed-float-value (clock-get g2-time-at-start)) time))
		((managed-float-p time)
		 (+e (managed-float-value (clock-get g2-time-at-start))
		     (managed-float-value time)))
		((integerp time) ; bignum case
		 (+e (managed-float-value (clock-get g2-time-at-start))
		     (coerce-to-gensym-float time)))
		(t			; shouldn't happen
		 0.0))))
    (declare (type gensym-float unix-time))
    (if (or (<e unix-time -2.147483648e9) ; signed 32-bit long bounds
	    (>=e unix-time 2-to-31-plus-62-years))
	nil ;;; *** Need error processing here ***
	(gensym-decode-unix-time unix-time))))

(defun transform-and-filter-day-and-time-interval (phrase)
  (let ((seconds (first phrase))
	(minutes (second phrase))
	(hours (third phrase))
	(days (fourth phrase))
	(total 0))
    (unless (or
	      (not seconds)
	      (<=f 0 seconds 59)
	      (and (not minutes) (<= 0 seconds)))
      (return-from transform-and-filter-day-and-time-interval
	(values bad-phrase "Seconds must be between 0 and 59")))
    (when seconds (incff total seconds))
    (unless (or
	      (not minutes)
	      (<=f 0 minutes  59)
	      (and (not hours) (<= 0 minutes)))
      (return-from transform-and-filter-day-and-time-interval
	(values bad-phrase "Minutes must be between 0 and 59")))
    (when minutes (incff total (*f minutes 60)))
    (unless (or
	      (not hours)
	      (<=f 0 hours 24)
	      (and (not days) (<= 0 hours)))
      (return-from transform-and-filter-day-and-time-interval
	(values bad-phrase "Hours must be between 0 and 24")))
    (when hours (incff total (*f hours 3600)))
    (when days (incff total (*f days 86400)))
    total))

(def-date-format dd-hh-mm-ss t
  (((integer '\: non-negative-integer '\: non-negative-integer '\: non-negative-integer) (7 5 3 1) transform-and-filter-day-and-time-interval))
  (let* ((integer-time (cond
			 ((fixnump seconds) seconds)
			 ((gensym-float-p seconds) (floor seconds))
			 ((managed-float-p seconds) (floor (managed-float-value seconds)))))
	 (s (modf integer-time 60))
	 (minutes (floorf integer-time 60))
	 (m (modf minutes 60))
	 (hours (floorf minutes 60))
	 (h (floorf hours 24))
	 (days (modf hours 24)))
    (tformat "~S:~A~S:~A~S:~A~S"
	     days
	     (if (<f h 10) "0" "")
	     h
	     (if (<f m 10) "0" "")
	     m
	     (if (<f s 10) "0" "")
	     s)))

(def-date-format hh-mm-ss t
  (((integer '\: non-negative-integer '\: non-negative-integer) (5 3 1) transform-and-filter-day-and-time-interval))
  (let* ((integer-time (cond
			 ((fixnump seconds) seconds)
			 ((gensym-float-p seconds) (floor seconds))
			 ((managed-float-p seconds) (floor (managed-float-value seconds)))))
	 (s (modf integer-time 60))
	 (minutes (floorf integer-time 60))
	 (m (modf minutes 60))
	 (hours (floorf minutes 60)))
    (tformat "~S:~A~S:~A~S"
	    hours
	    (if (<f m 10) "0" "")
	    m
	    (if (<f s 10) "0" "")
	    s)))

		
(def-date-format hh-mm t
  (((integer '\: non-negative-integer) (nil 3 1) transform-and-filter-day-and-time-interval))
  (let* ((integer-time (cond
			 ((fixnump seconds) seconds)
			 ((gensym-float-p seconds) (floor seconds))
			 ((managed-float-p seconds) (floor (managed-float-value seconds)))))
	 (minutes (floorf integer-time 60))
	 (m (modf minutes 60))
	 (hours (floorf minutes 60)))
    (tformat "~S:~A~S"
	    hours
	    (if (<f m 10) "0" "")
	    m)))

;;; If we have to:  (((t-integer '\: positive-integer) (3 1) transform-and-filter-decimal-hours-interval))

(defun convert-to-seconds (seconds-phrase)
  (let*  ((seconds (car seconds-phrase))
	  (value (if (managed-float-p seconds)
		     (managed-float-value seconds)
		     seconds)))
    (make-phrase-float (*e 3600.0 value))))
  
(def-date-format hh.hh t
  ((float (1) convert-to-seconds))
  (let* ((integer-time (cond
			 ((fixnump seconds) seconds)
			 ((gensym-float-p seconds) (floor seconds))
			 ((managed-float-p seconds) (floor (managed-float-value seconds)))))
	 (hundredths (floorf integer-time 36))
	 (h (modf hundredths 100))
	 (hours (floorf hundredths 100)))
    (tformat "~S.~A~S"
	     hours
	     (if (<f h 10) "0" "")
	     h)))

(def-date-format mm-ss t
  (((positive-integer '\: positive-integer) (3 1) transform-and-filter-day-and-time-interval))
  (let* ((integer-time (cond
			 ((fixnump seconds) seconds)
			 ((gensym-float-p seconds) (floor seconds))
			 ((managed-float-p seconds) (floor (managed-float-value seconds)))))
	 (s (modf integer-time 60))
	 (minutes (floorf integer-time 60)))
    (tformat "~S:~A~S"
	    minutes
	    (if (<f s 10) "0" "")
	    s)))

	 
(add-grammar-rules
  '((m-first-slashed-date (month-number '\/ day '\/ year) (3 1 5) transform-input-phrase-into-universal-date)
    (d-first-slashed-date (day '\/ month-number '\/ year) (1 3 5) transform-input-phrase-into-universal-date)
    (y-first-slashed-date (year '\/ month-number '\/ day) (5 3 1) transform-input-phrase-into-universal-date)
    (time-24 (hour '\: minute '\: second) (1 3 nil 5 t) filter-and-normalize-time-of-day)
    (time-24-no-seconds (hour '\: minute) (1 3 nil nil t) filter-and-normalize-time-of-day)))

;;; Need a transform here to check that it's <=12
(def-grammar-category month-number () (positive-integer))

(def-date-format MM-DD-YYYY-hh-mm-ss nil
    (((m-first-slashed-date time-24) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  ;; This could be done as one big tformat, but it would take more than
  ;; 10 arguments; If it was further from release time, I'd modify tformat
  ;; to take more args. -alatto, 2/11/07
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day
	     year)
    (tformat
      " ~A~S:~A~S:~A~S"
      (if (<f hours 10) "0" "")
      hours
      (if (<f minutes 10) "0" "")
      minutes
      (if (<f seconds 10) "0" "")
      seconds)))

(def-date-format DD-MM-YYYY-hh-mm-ss nil
    (((d-first-slashed-date time-24) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f day 10) "0" "")
	     day
	     (if (<f month 10) "0" "")
	     month
	     year)
    (tformat
      " ~A~S:~A~S:~A~S"
      (if (<f hours 10) "0" "")
      hours
      (if (<f minutes 10) "0" "")
      minutes
      (if (<f seconds 10) "0" "")
      seconds)))

(def-date-format YYYY-MM-DD-hh-mm-ss nil
    (((y-first-slashed-date time-24) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  ;; This could be done as one big tformat, but it would take more than
  ;; 10 arguments; If it was further from release time, I'd modify tformat
  ;; to take more args. -alatto, 2/11/07
  (progn
    (tformat "~S/~A~S/~A~S"
	     year
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day)
    (tformat
      " ~A~S:~A~S:~A~S"
      (if (<f hours 10) "0" "")
      hours
      (if (<f minutes 10) "0" "")
      minutes
      (if (<f seconds 10) "0" "")
      seconds)))

(def-date-format MM-DD-YYYY-hh-mm-ss-am-pm nil
    (((m-first-slashed-date time-of-day-with-seconds) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day
	     year)
    (tformat
      " ~S:~A~S:~A~S ~A"
      (if (or (eql hours 0) (eql hours 12))
	  12
	  (mod hours 12))
      (if (<f minutes 10) "0" "")
      minutes
      (if (<f seconds 10) "0" "")
      seconds
      (if (<=f hours 11)
	  "a.m."
	  "p.m."))))

(def-date-format DD-MM-YYYY-hh-mm-ss-am-pm nil
    (((d-first-slashed-date time-of-day-with-seconds) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f day 10) "0" "")
	     day
	     (if (<f month 10) "0" "")
	     month
	     year)
    (tformat
      " ~S:~A~S:~A~S ~A"
      (if (or (eql hours 0) (eql hours 12))
	  12
	  (mod hours 12))
      (if (<f minutes 10) "0" "")
      minutes
      (if (<f seconds 10) "0" "")
      seconds
      (if (<=f hours 11)
	  "a.m."
	  "p.m."))))

(def-date-format YYYY-MM-DD-hh-mm-ss-am-pm nil
    (((y-first-slashed-date time-of-day-with-seconds) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~S/~A~S/~A~S"
	     year
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day)
    (tformat
      " ~S:~A~S:~A~S ~A"
      (if (or (eql hours 0) (eql hours 12))
	  12
	  (mod hours 12))
      (if (<f minutes 10) "0" "")
      minutes
      (if (<f seconds 10) "0" "")
      seconds
      (if (<=f hours 11)
	  "a.m."
	  "p.m."))))

(def-date-format MM-DD-YYYY-hh-mm-am-pm nil
    (((m-first-slashed-date time-of-day) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day
	     year)
    (tformat
      " ~S:~A~S ~A"
      (if (or (eql hours 0) (eql hours 12))
	  12
	  (mod hours 12))
      (if (<f minutes 10) "0" "")
      minutes
      (if (<=f hours 11)
	  "a.m."
	  "p.m."))))

(def-date-format DD-MM-YYYY-hh-mm-am-pm nil
    (((d-first-slashed-date time-of-day) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f day 10) "0" "")
	     day
	     (if (<f month 10) "0" "")
	     month
	     year)
    (tformat
      " ~S:~A~S ~A"
      (if (or (eql hours 0) (eql hours 12))
	  12
	  (mod hours 12))
      (if (<f minutes 10) "0" "")
      minutes
      (if (<=f hours 11)
	  "a.m."
	  "p.m."))))

(def-date-format YYYY-MM-DD-hh-mm-am-pm nil
    (((y-first-slashed-date time-of-day) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~S/~A~S/~A~S"
	     year
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day)
    (tformat
      " ~S:~A~S ~A"
      (if (or (eql hours 0) (eql hours 12))
	  12
	  (mod hours 12))
      (if (<f minutes 10) "0" "")
      minutes
      (if (<=f hours 11)
	  "a.m."
	  "p.m."))))

(def-date-format MM-DD-YYYY-hh-mm nil
    (((m-first-slashed-date time-24-no-seconds) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day
	     year)
    (tformat
      " ~A~S:~A~S"
      (if (<f hours 10) "0" "")
      hours
      (if (<f minutes 10) "0" "")
      minutes)))

(def-date-format DD-MM-YYYY-hh-mm nil
    (((d-first-slashed-date time-24-no-seconds) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~A~S/~A~S/~S" 
	     (if (<f day 10) "0" "")
	     day
	     (if (<f month 10) "0" "")
	     month
	     year)
    (tformat
      " ~A~S:~A~S"
      (if (<f hours 10) "0" "")
      hours
      (if (<f minutes 10) "0" "")
      minutes)))

(def-date-format YYYY-MM-DD-hh-mm nil
    (((y-first-slashed-date time-24-no-seconds) (1 2) transform-date-phrase-and-time-of-day-into-g2-time-stamp))
  (progn
    (tformat "~S/~A~S/~A~S"
	     year
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day)
    (tformat
      " ~A~S:~A~S"
      (if (<f hours 10) "0" "")
      hours
      (if (<f minutes 10) "0" "")
      minutes)))

(defun add-zero-time-to-date (date)
  (phrase-cons date (phrase-list 0)))

(defun add-zero-time-to-date-list (date-list)
  (rplacd date-list (phrase-list 0)))

(def-date-format YYYY-MM-DD nil
    ((y-first-slashed-date (1) add-zero-time-to-date-list transform-date-phrase-and-time-of-day-into-g2-time-stamp))
    (tformat "~S/~A~S/~A~S"
	     year
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day))

(def-date-format MM-DD-YYYY nil
    ((m-first-slashed-date (1) add-zero-time-to-date-list transform-date-phrase-and-time-of-day-into-g2-time-stamp))
    (tformat "~A~S/~A~S/~S" 
	     (if (<f month 10) "0" "")
	     month
	     (if (<f day 10) "0" "")
	     day
	     year))

(def-date-format DD-MM-YYYY nil
    ((d-first-slashed-date (1) add-zero-time-to-date-list transform-date-phrase-and-time-of-day-into-g2-time-stamp))
    (tformat "~A~S/~A~S/~S" 
	     (if (<f day 10) "0" "")
	     day
	     (if (<f month 10) "0" "")
	     month
	     year))

(defun set-day-of-date-to-1 (date-phrase)
  (rplaca date-phrase 1))

(def-date-format MM-YYYY nil
    (((month-number '\/ year) (day 1 3) set-day-of-date-to-1 transform-input-phrase-into-universal-date add-zero-time-to-date transform-date-phrase-and-time-of-day-into-g2-time-stamp))
    (tformat "~A~S/~S" 
	     (if (<f month 10) "0" "")
	     month
	     year))

(def-date-format YYYY-MM nil
    (((year '\/ month-number) (day 3 1) set-day-of-date-to-1 transform-input-phrase-into-universal-date add-zero-time-to-date transform-date-phrase-and-time-of-day-into-g2-time-stamp))

  (tformat "~S/~A~S"
	     year
	     (if (<f month 10) "0" "")
	     month))
    
(def-slot-value-writer truth-value-attribute (value)
  (print-constant
    (get-slot-value-number-or-string-from-slot-constant value)
    (get-unit-from-slot-constant value)))

(def-slot-value-writer symbol-attribute (value)
  (cond
    ((symbolp value)
     (print-constant value 'symbol))
    (t
     #+development
     (cerror "grammar5" "error in symbol-attribute writer"))))

(def-slot-value-writer text-attribute (attribute)
  (if (slot-constantp attribute)
      (print-constant
	(get-slot-value-number-or-string-from-slot-constant attribute)
	(get-unit-from-slot-constant attribute))
      (let ((write-strings-parsably? t))
	(setq leave-text-representation-as-a-single-line? nil)
	(twrite-string attribute))))

(def-slot-value-writer free-text-attribute (attribute)
  (if (slot-constantp attribute)
      (print-constant
	(get-slot-value-number-or-string-from-slot-constant attribute)
	(get-unit-from-slot-constant attribute)
	t)
      (let ((write-strings-parsably? nil))
	(setq leave-text-representation-as-a-single-line? nil)
	(twrite-string attribute))))

(defun write-entity-in-slot (entity)
  (cond
    ((variable-p entity)
     (with-temporary-gensym-float-creation write-attribute-from-slot
       (let ((value (extract-cached-number-or-value
		      (current-value-of-variable-or-parameter entity)))
	     (expiration (expiration-time-of-current-value entity))
	     (type (data-type-of-variable-or-parameter entity)))
	 (when (eq type 'text)
	   (setq leave-text-representation-as-a-single-line? nil))
	 (cond ((null value)
		(twrite "****"))
	       ((eq expiration 'never)
		(print-constant value type))
	       ((=f expiration *some-time-ago*)
		(twrite "****"))
	       ((<f expiration gensym-time)
		(print-constant value type)
		(twrite " *"))
	       (t				; Value is current, but expires.
		(print-constant value type)
		(schedule-update-for-variable-expiration entity))))))
    ((parameter-p entity)
     (with-temporary-gensym-float-creation write-attribute-from-slot
       (let ((value (extract-cached-number-or-value
		      (current-value-of-variable-or-parameter entity)))
	     (type (data-type-of-variable-or-parameter entity)))
	 (when (eq type 'text)
	   (setq leave-text-representation-as-a-single-line? nil))
	 (cond ((null value)
		;; Only during loading is there a NIL here. ML.
		(twrite "****"))
	       (t
		(print-constant value type))))))
    (t
     (let ((name? (get-primary-name-for-frame-if-any entity))
	   (class (class entity)))
       (cond (name?
	      (tformat "the ~(~A~) " class)
	      (write-name-for-frame name?))
	     (t
	      (write-symbol-with-a-or-an class)))))))







(add-grammar-rules
  
  '(
    ;; The category attribute is identical to item-or-datum-attribute.  See also
    ;; my comments below.  (MHD 4/8/97)
    (attribute item-or-datum-attribute)
    (read-only-attribute attribute);read-only only has meaning with respect to the evaluator
;    (attribute (number neutral-unit-of-measure) (1 . 2))
;    (attribute (number singular-unit-of-measure) (1 . 2) convert-singular-constant)
;    (attribute (number plural-unit-of-measure) (1 . 2))

;    (attribute interval)

;    (attribute number)   
;    (attribute standard-or-class-qualified-symbol)

;    (attribute 'true)
;    (attribute 'false)
;    (attribute 'none)
;    (attribute (number 'true) (1 . truth-value) (check-range-of-element 1 -1 1))

;    (attribute whole-string)
;    (attribute sequence-attribute)
;    (attribute structure-attrubute)
    
    (attribute-name unreserved-symbol)

    #+obsolete (user-defined-or-built-in-attribute-name attribute-name)
    #+obsolete (user-defined-or-built-in-attribute-name system-defined-attribute-name)


    ;; Component frames of variables and history-frame of simulator-frame

    (non-default-number? 'default)
    (non-default-number? number)
    ))

(add-grammar-rules
  '((uuid whole-string)))



(defun make-illegal-length-uuid-string-message (wide-string length)
  (declare (ignore wide-string))
  (tformat-text-string
    "A UUID (as represented internally) must be a text ~D characters long, but ~
       this is ~D characters long"
    uuid-string-length
    length))  

(define-category-evaluator-interface (uuid
				       :access read-write)
    text
  ((set-form (evaluation-text))
   (cond
     ((not (=f (lengthw evaluation-text) uuid-string-length))
      (values
	bad-phrase
	(make-illegal-length-uuid-string-message
	  evaluation-text
	  (lengthw evaluation-text))))
     (t
      (note-use-of-text-string-in-phrase 
	(twith-output-to-text-string
	  (twrite-uuid-printed-representation evaluation-text))))))
  ((get-form (slot-value frame))
   (cond (slot-value
	  (evaluation-item-reference-uuid slot-value))
	 (frame
	  (error "Internal error getting a UUID")))))




(add-grammar-rules
  
  '((item-or-datum-or-no-item-attribute constant-allowing-contained-items)
    ;; The following are replaced by the above rule; constant covers them all.
    ;; Note that constant includes "quantity-interval", but I believe all
    ;; cases that handle interval should handle quantity interval.  If not,
    ;; fix bugs with such cases. (MHD 4/8/97)
;    (item-or-datum-or-no-item-attribute (constant neutral-unit-of-measure) (1 . 2))
;    (item-or-datum-or-no-item-attribute (constant singular-unit-of-measure) (1 . 2)
;     convert-singular-constant)
;    (item-or-datum-or-no-item-attribute (constant plural-unit-of-measure) (1 . 2))
;    (item-or-datum-or-no-item-attribute interval)
;    (item-or-datum-or-no-item-attribute number)
;    (item-or-datum-or-no-item-attribute whole-string)
;    (item-or-datum-or-no-item-attribute structure-attribute)
;    (item-or-datum-or-no-item-attribute sequence-attribute)

    ;; This let's you type in class qualified names as symbols in attribute
    ;; tables.  They get turned into symbols from which we can derive component
    ;; class and attribute names.
    (item-or-datum-or-no-item-attribute
     standard-or-class-qualified-symbol
     1 reject-truth-value-as-symbol)
    
    ;; Grammar for truth-value-attribute (Fuzzy truth values) are now included as
    ;; constant (MHD 4/8/97)
;    (item-or-datum-or-no-item-attribute 'true)
;    (item-or-datum-or-no-item-attribute 'false)
;    (item-or-datum-or-no-item-attribute (number 'true)
;     (1 . truth-value) (check-range-of-element 1 -1 1))
    
    ;; The category item-or-datum-attribute is identical to
    ;; item-or-datum-or-no-item-attribute, except that it allows NONE.  See also
    ;; my comments above.  (MHD 4/8/97)
    (item-or-datum-attribute 'none)
    (item-or-datum-attribute item-or-datum-or-no-item-attribute)
;    (item-or-datum-attribute (constant neutral-unit-of-measure) (1 . 2))
;    (item-or-datum-attribute (constant singular-unit-of-measure) (1 . 2) convert-singular-constant)
;    (item-or-datum-attribute (constant plural-unit-of-measure) (1 . 2))
;    (item-or-datum-attribute interval)
;    (item-or-datum-attribute number)   
;    (item-or-datum-attribute standard-or-class-qualified-symbol)
;    (item-or-datum-attribute 'true)
;    (item-or-datum-attribute 'false)
;    (item-or-datum-attribute (number 'true) (1 . truth-value) (check-range-of-element 1 -1 1))
;    (item-or-datum-attribute whole-string)
;    (item-or-datum-attribute structure-attribute)
;    (item-or-datum-attribute sequence-attribute)

    ;; The category datum-attribute is identical to
    ;; item-or-datum-or-no-item-attribute.  See also my comments above.  (MHD
    ;; 4/8/97)
    (datum-attribute item-or-datum-or-no-item-attribute)
;    (datum-attribute (constant neutral-unit-of-measure) (1 . 2))
;    (datum-attribute (constant singular-unit-of-measure) (1 . 2) convert-singular-constant)
;    (datum-attribute (constant plural-unit-of-measure) (1 . 2))
;    (datum-attribute interval)
;    (datum-attribute number)   
;    (datum-attribute standard-or-class-qualified-symbol)
;    (datum-attribute 'true)
;    (datum-attribute 'false)
;    (datum-attribute (number 'true) (1 . truth-value) (check-range-of-element 1 -1 1))
;    (datum-attribute whole-string)
;    (datum-attribute structure-attribute)
;    (datum-attribute sequence-attribute)

    (number-attribute number)

    (float-attribute float)

    (integer-attribute integer)

    ;; See comments above! (MHD 4/8/97)
    (symbol-attribute standard-or-class-qualified-symbol)

    (text-attribute whole-string)

    ;; added today for 8.0a0. (MHD 4/12/04)
    (interval-attribute quantity-interval)
    (interval-float-attribute quantity-interval) ; compiler coerces to float
    (interval-integer-attribute interval) ; integer only, despite generic name

    (time-stamp-attribute time-stamp-optionally-with-subseconds)
    (time-stamp-float-attribute time-stamp-optionally-with-subseconds-as-float)
    (time-stamp-integer-attribute time-stamp)
    
    (ddd.dddd-format-attribute quantity)
    (ddd.dddd-format-float-attribute float)
    (ddd.dddd-format-integer-attribute integer)))

;; Grammar for truth-value-attribute removed to GRAMMAR0, and changed
;; considerably. (MHD 5/8/97)
       





(def-slot-value-writer simulation-frame? (simulation-frame? variable)
  (let ((simulation-category? (simulation-category? variable)))
    (if (null simulation-category?)
	(progn
	  (twrite "no simulation formula yet")
	  (if simulation-frame?
	      (twrite ", but has specific subtable")))
	(with-temporary-gensym-float-creation writer-for-simulation-frame?
	  (let ((initial-simulated-value?
		  (or (slot-value-number-value
			(non-default-initial-simulated-value? variable))
		      (initial-simulated-value? variable))))	  
	    (twrite simulation-category?)
	    (if (and initial-simulated-value?
		     (memq simulation-category?
			   '(discrete-state continuous-state)))
		(progn
		  (twrite ", with initial value ")
		  (cond
		    ((slot-value-float-p initial-simulated-value?)
		     (twrite (slot-value-float-value initial-simulated-value?)))
		    ((or (consp initial-simulated-value?)
			 (eq initial-simulated-value?
			     'use-initial-value-expression-in-generic-simulation-formula))
		     (twrite "given by an expression"))
		    (t
		     (twrite initial-simulated-value?)))))
	    (if simulation-frame?
		(twrite ", and has specific subtable")))))))

;; If the initial value is a number, the number will be written.  However, if 
;; it is an expression, rather than writing the expression, the phrase 
;; "given by an expression" is written.




;;; The slot value compiler for non-default-number? expects parse-result to be
;;; a number or else a symbol, namely the symbol DEFAULT.

(def-slot-value-compiler non-default-number? (parse-result)
  (if (phrase-number-p parse-result) parse-result nil))

(def-slot-value-writer non-default-number? (number?)
  (cond
    ((slot-value-float-p number?)
     (with-temporary-gensym-float-creation non-default-number?
       (twrite-float (slot-value-float-value number?))))
    (number? (twrite number?))
    (t (twrite "default"))))

;; Consider allowing this to instantiate if there is no such entity, as it once did.

;; Consider, if it has a parent, moving it to have this parent, or interrogating
;; the user in an interactive mode.




;;; The `slot-value compiler for attribute' is just like the slot value compiler
;;; for item-or-datum-or-no-item-attribute.  Therefore, this simply returns the
;;; result of calling the slot value compiler for
;;; item-or-datum-or-no-item-attribute.  Unlike attributes having the
;;; item-or-datum-or-no-item-attribute type feature, however, this cannot accept
;;; frames, which in any case would not go through the compiler.

(def-slot-value-compiler attribute (parse-result frame slot-name defining-class)
  (declare (use-for-default-overrides))
  (compile-item-or-datum-or-no-item-attribute-for-slot
    parse-result frame slot-name defining-class))

(def-slot-value-compiler read-only-attribute
    (parse-result frame slot-name defining-class)
  (declare (use-for-default-overrides))
  (funcall-compiled-function
    (slot-value-compiler 'attribute)
    parse-result frame slot-name defining-class))

(defun copy-evaluation-value-to-phrase (evaluation-value)
  (cond ((null evaluation-value)
	 'none)
	 ((symbolp evaluation-value)
	  evaluation-value)
	 ((evaluation-truth-value-p evaluation-value)
	  ;; the truth-value phrase will be compiled as a slot constant
	  (make-truth-value-phrase
	    (evaluation-truth-value-value evaluation-value)))
	 ((evaluation-structure-p evaluation-value)
	  (make-phrase-structure
	    (loop for (name . value)
		      being each evaluation-structure-pair of evaluation-value
		  nconc (phrase-list name
				     (copy-evaluation-value-to-phrase value)))))
	 ((evaluation-sequence-p evaluation-value)
	  (make-phrase-sequence
	    (loop for value being each evaluation-sequence-element of evaluation-value
		  collect (copy-evaluation-value-to-phrase value) using phrase-cons)))
	 ((framep evaluation-value)
	  (make-phrase-item evaluation-value))
	 (t
	  (copy-for-phrase evaluation-value))))

(define-category-evaluator-interface (attribute :access read-write)
    (or (no-item) symbol truth-value number text (sequence) (structure))
  ((set-form (evaluation-value))
   (if (null evaluation-value)
       'none
       (copy-evaluation-value-to-phrase evaluation-value)))
  ((get-form (slot-value frame?))
   (get-evaluation-value-for-attribute slot-value frame?)))


;;; The category read-only attribute is being introduced to allow
;;; a number of system-defined read only slot to continue to disallow
;;; concludes

(def-slot-value-writer read-only-attribute (attribute)
  (write-attribute attribute))

(define-category-evaluator-interface (read-only-attribute :access read)
    (or (no-item) symbol truth-value number text)
  ((get-form (slot-value frame?))
   (get-evaluation-value-for-attribute slot-value frame?)))



;;; The function `get-evaluation-value-for-attribute' is a subfunction of the
;;; evaluation getter get-form functions for attribute and read-only-attribute.

;;; If frame is supplied, it will be either
;;;     a definition of a variable-or-parameter, or
;;;     a variable-or-parameter
;;; It should be used to process NIL, TRUE, and FALSE

(defun-simple get-evaluation-value-for-attribute (slot-value frame?)  
  (cond ((null slot-value)
	 (if (get-allow-no-value-of-variable-or-parameter-from-frame frame?)
	     nil
	     'none))
	((text-string-p slot-value)
	 (make-evaluation-value slot-value 'text))
	((slot-constantp slot-value)
	 (cast-slot-constant-into-evaluation-value slot-value))
	((managed-float-p slot-value)
	 (copy-evaluation-float slot-value))
	(t
	 (if (eq 'truth-value
		 (get-data-type-of-variable-or-parameter-from-frame frame?))
	     (case slot-value
	       (true (make-evaluation-boolean-value t))
	       (false (make-evaluation-boolean-value nil))
	       (t (copy-if-evaluation-value slot-value)))
	     (copy-if-evaluation-value slot-value)))))




;; This is called by compiler for default-values and relies on only the first
;; argument being used.

;;; The `slot-value compiler for item-or-datum-or-no-item-attribute' is just
;;; like the slot value compiler for item-or-datum-attribute, except that it
;;; additionally handles NONE (being the parse result corresponding to no
;;; value).  If parse-result is other than NONE, this returns the result of
;;; calling the slot value compiler for item-or-datum-attribute.

(def-slot-value-compiler item-or-datum-or-no-item-attribute
    (parse-result frame slot-name defining-class)
  (declare (use-for-default-overrides))
  (cond
    ((eq parse-result 'none)
     nil)
    (t
     (compile-item-or-datum-attribute-for-slot
       parse-result frame slot-name defining-class))))



;;; The `slot-value compiler for item-or-datum-attribute' is just like the slot
;;; value compiler for datum-attribute.  A slot for which this is the type
;;; actually accept frames as their value, but these never go through the
;;; compiler, the compiler can and should ignore that case.  Therefore, this
;;; simply returns the result of calling the slot value compiler for
;;; datum-attribute.

(def-slot-value-compiler item-or-datum-attribute
    (parse-result frame slot-name defining-class)
  (declare (use-for-default-overrides))
  (compile-datum-attribute-for-slot
    parse-result frame slot-name defining-class))



;;; The `slot-value compiler for datum-attribute' rejects a frame or the
;;; symbol NONE as the value of parse-result.  Other values are expected
;;; and accepted are:
;;;
;;;   truth value     as  (n . TRUTH-VALUE)
;;;   phrase number   as a fixnum or a managed float
;;;   symbol          
;;;   text string     
;;;   phrase structure
;;;   phrase sequence
;;;   number of units (e.g., "4.3 METERS")  as (n . unit)

(def-slot-value-compiler datum-attribute (parse-result)
  (cond
    ((eq parse-result 'none)
     bad-phrase)
    ((truth-value-phrase-p parse-result)
     (mutate-truth-value-phrase-into-slot-constant parse-result))
    ((phrase-number-p parse-result)
     (make-slot-constant-using-phrase-conses parse-result 'number))
    ((or (symbolp parse-result)
	 (text-string-p parse-result)
	 (phrase-sequence-p parse-result)
	 (phrase-structure-p parse-result)
	 (phrase-item-denotation-p parse-result))
     parse-result)
    ;; otherwise, now known to be a cons, not a truth value phrase
    ((phrase-number-p (car parse-result))
     ;;  if a number is in the car, it must be a unit-of-measure phrase:
     (mutate-unit-of-measure-phrase-phrase-into-slot-constant parse-result))))

(def-slot-value-compiler number-attribute (parse-result)
  (if (phrase-number-p parse-result)
      (make-slot-constant-using-phrase-conses parse-result 'number)
      bad-phrase))
      

(def-slot-value-compiler float-attribute (parse-result)
  (if (phrase-float-p parse-result)
      (make-slot-constant-using-phrase-conses parse-result 'number)
      bad-phrase))

(def-slot-value-compiler integer-attribute (parse-result)
  (if (fixnump parse-result)
      (make-slot-constant-using-phrase-conses parse-result 'number)
      bad-phrase))

(def-slot-value-compiler symbol-attribute (parse-result)
  (if (symbolp parse-result) parse-result bad-phrase))

(def-slot-value-compiler text-attribute (parse-result)
  (if (text-string-p parse-result) parse-result bad-phrase))

(def-slot-value-compiler free-text-attribute (parse-result)
  (if (text-string-p parse-result) parse-result bad-phrase))

(def-slot-value-compiler truth-value-attribute (parse-result)
  (if (truth-value-phrase-p parse-result)
      (mutate-truth-value-phrase-into-slot-constant parse-result)
      bad-phrase))

(def-slot-value-compiler structure-attribute (parse-result)
  (if (phrase-structure-p parse-result) parse-result bad-phrase))

(def-slot-value-compiler sequence-attribute (parse-result)
  (if (phrase-sequence-p parse-result) parse-result bad-phrase))

(def-slot-value-compiler evaluation-value-constant-allowing-items
    (parse-result frame slot-name defining-class)
  (declare (use-for-default-overrides))
  (if (eq parse-result 'none)
      nil
      (compile-item-or-datum-attribute-for-slot
	parse-result frame slot-name defining-class)))



(def-slot-value-compiler ddd.dddd-format-attribute (parse-result)  
  (if (phrase-number-p parse-result)
      (make-slot-constant-using-phrase-conses parse-result 'number)
      bad-phrase))

(def-slot-value-compiler ddd.dddd-format-float-attribute (parse-result)  
  (if (phrase-float-p parse-result)
      (make-slot-constant-using-phrase-conses parse-result 'number)
      bad-phrase))

(def-slot-value-compiler ddd.dddd-format-integer-attribute (parse-result)
  (if (fixnump parse-result)
      (make-slot-constant-using-phrase-conses parse-result 'number)
      bad-phrase))






;;;; Grammars and Slot Value Writers for Slots of Frames





;;;; Slots of variables

(add-grammar-rules
  '((data-type 'interval seconds)
    (data-type ('time 'stamp) time-stamp)
    (data-type ('truth 'value) truth-value)
    (data-type 'symbol)
    (data-type 'text)
    (data-type 'integer)
    (data-type 'long)
    (data-type 'float)
    (data-type ('pure 'number) pure-number)
    (data-type 'quantity number)
    (data-type neutral-unit-of-measure)
    (data-type plural-unit-of-measure)
    (default-override-data-type ('time 'stamp) time-stamp)
    (default-override-data-type ('truth 'value) truth-value)
    (default-override-data-type 'symbol)
    (default-override-data-type 'text)
    (default-override-data-type 'integer)
    (default-override-data-type 'long)
    (default-override-data-type 'float)
    (default-override-data-type ('pure 'number) pure-number)
    (default-override-data-type 'quantity number)))

(define-category-evaluator-interface (symbol
				       :access read-write)
    symbol
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

;; new
(define-category-evaluator-interface (read-only-symbol-data-type
				       :access read)
    (member symbol)
  ((get-form (slot-value))
   slot-value))

;; new
(define-category-evaluator-interface (read-only-text-data-type
				       :access read)
    (member text)
  ((get-form (slot-value))
   slot-value))

;; new
(define-category-evaluator-interface (read-only-truth-value-data-type
				       :access read)
    (member truth-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (float-data-type
				       :access read-write)
    (or (member float time-stamp)
	symbol)  ;; unit of measure
  ((set-form (evaluation-value))
   (case evaluation-value
     (float 'float)
     (time-stamp 'time-stamp)
     (t
      (if (not (or (memq 'neutral-unit-of-measure
			 (category-symbols-for-symbol-token evaluation-value))
		   (memq 'plural-unit-of-measure
			 (category-symbols-for-symbol-token evaluation-value))))
	  (values
	    bad-phrase
	    (copy-text-string
	      "You must use an appropriate G2-defined type or a KB-defined unit of measure."))
	  evaluation-value))))
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (integer-data-type
				       :access read-write)
    (or (member integer interval)
	symbol)  ;; unit of measure
  ((set-form (evaluation-value))
   (case evaluation-value
     (interval 'seconds)
     (integer 'integer)
     (t
      (if (not (or (memq 'neutral-unit-of-measure
			 (category-symbols-for-symbol-token evaluation-value))
		   (memq 'plural-unit-of-measure
			 (category-symbols-for-symbol-token evaluation-value))))
	  (values
	    bad-phrase
	    (copy-text-string
	      "You must use an appropriate G2-defined type or a KB-defined unit of measure."))
	  evaluation-value))))
  ((get-form (slot-value))
   (case slot-value
     (seconds 'interval)
     (t slot-value))))

;added by SoftServe
(define-category-evaluator-interface (long-data-type
				       :access read-write)
    (or (member long interval)
	symbol)  ;; unit of measure ;possibly incorrect?
  ((set-form (evaluation-value))
   (case evaluation-value
     (long 'long)
     (t
	  (values
	    bad-phrase
	    (copy-text-string
	      "int 64 data type is experimental and does not support units of measure"))
	  )))
  ((get-form (slot-value))
   (case slot-value
     (seconds 'interval)
     (t slot-value))))

;end of changes

(define-category-evaluator-interface (quantitative-data-type
				       :access read-write)
    (or (member quantity)
	(named float-data-type)
	(named integer-data-type))
  ((set-form (evaluation-value))
   (case evaluation-value
     (quantity 'number)
     (float 'float)
     (time-stamp 'time-stamp)
     (t
      ;; use the unit-of-measure checking in either int or float C.E.
      (call-category-setter 'integer-data-type evaluation-value nil nil nil))))
  ((get-form (slot-value))
   (case slot-value
     (number 'quantity)
     ((quantity float time-stamp) slot-value)
     (t
      (call-category-getter 'integer-data-type slot-value nil nil)))))

(define-category-evaluator-interface (data-type
				       :access read-write)
    (or (named quantitative-data-type)
	(member value symbol text truth-value))
  ((set-form (evaluation-value))
   (case evaluation-value
     (value 'datum)
     (symbol 'symbol)
     (text 'text)
     (truth-value 'truth-value)
     (t
      (call-category-setter 'quantitative-data-type evaluation-value nil nil nil))))
  ((get-form (slot-value))
   (case slot-value
     (datum 'value)
     ((value symbol text truth-value) slot-value)
     (t
      (call-category-getter 'quantitative-data-type slot-value nil nil)))))


;;; Data-type is the category for data-type-of-variable-or-parameter
;;; among other uses. (Except that quantitative variables and parameters
;;; uses quantitative-data-type) When this slot is being set, the initial
;;; value could become incompatible. To avoid this, the initial value is
;;; set to nil, except for quantitative-parameters where it is set to 0.0.


(defun-simple fix-data-type (parse-result)
  (case parse-result
    (quantity 'number)
    (interval 'seconds)
    (value 'datum)
    (t parse-result)))

(def-slot-value-compiler data-type (parse-result frame)
  (declare (use-for-default-overrides))
  (let ((fixed-value (fix-data-type parse-result)))

    (when (and (of-class-p frame 'variable-or-parameter)
	       (neq fixed-value (data-type-of-variable-or-parameter frame)))
      (cond
	((frame-of-class-p frame 'integer-parameter)
	 (when (not (fixnump (initial-value-of-variable-or-parameter frame)))
	   (set-slot-value-and-update-representations
	    frame 'initial-value-of-variable-or-parameter 0)))
	((frame-of-class-p frame 'quantitative-parameter)
	 (set-slot-value-and-update-representations
	  frame 'initial-value-of-variable-or-parameter 0.0))
	((frame-of-class-p frame 'variable)
	 (set-slot-value-and-update-representations
	  frame 'initial-value-of-variable-or-parameter nil))))
    
    fixed-value))




(def-slot-value-writer data-type (data-type)
  (twrite-data-type data-type))

(def-slot-value-compiler quantitative-data-type (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-data-type-for-slot parse-result frame nil))

(def-slot-value-compiler float-data-type (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-data-type-for-slot parse-result frame nil))

(def-slot-value-compiler integer-data-type (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-data-type-for-slot parse-result frame nil))

;added by SoftServe
(def-slot-value-compiler long-data-type (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-data-type-for-slot parse-result frame nil))
;end of changes

;; new
(def-slot-value-writer read-only-symbol-data-type (data-type frame)
  (write-data-type-from-slot data-type frame))

;; new
(def-slot-value-writer read-only-text-data-type (data-type frame)
  (write-data-type-from-slot data-type frame))

;; new
(def-slot-value-writer read-only-truth-value-data-type (data-type frame)
  (write-data-type-from-slot data-type frame))

(def-slot-value-writer quantitative-data-type (data-type frame)
  (write-data-type-from-slot data-type frame))

(def-slot-value-writer integer-data-type (data-type frame)
  (write-data-type-from-slot data-type frame))

;added by SoftServe
(def-slot-value-writer long-data-type (data-type frame)
  (write-data-type-from-slot data-type frame))
;end of changes

(def-slot-value-writer float-data-type (data-type frame)
  (write-data-type-from-slot data-type frame))

(add-grammar-rules
  '((quantitative-data-type 'interval seconds)
    (quantitative-data-type ('time 'stamp) time-stamp)
    (quantitative-data-type ('pure 'number) pure-number)
    (quantitative-data-type 'quantity number)
    (quantitative-data-type neutral-unit-of-measure)
    (quantitative-data-type plural-unit-of-measure)
    (quantitative-data-type 'float)
    (quantitative-data-type 'integer)
    (integer-data-type 'interval seconds)
    (integer-data-type ('pure 'number) pure-number)
    (integer-data-type 'integer)
    (long-data-type 'long)
    (integer-data-type neutral-unit-of-measure)
    (integer-data-type plural-unit-of-measure)
    (float-data-type ('time 'stamp) time-stamp)
    (float-data-type ('pure 'number) pure-number)
    (float-data-type 'float)
    (float-data-type neutral-unit-of-measure)
    (float-data-type plural-unit-of-measure)
    (default-override-quantitative-data-type ('time 'stamp) time-stamp)
    (default-override-quantitative-data-type ('pure 'number) pure-number)
    (default-override-quantitative-data-type 'quantity number)))




;;; Type supplied value is for current-value. In order to be editable it needs
;;; to have a check for correct data-type, and then to call put-current-value.
;;; Until then, leave it not user editable.

(def-slot-value-writer supplied-value (value variable-or-parameter)
  (with-temporary-creation supplied-value
    (if (frame-of-class-p variable-or-parameter 'variable)

	(let ((type (data-type-of-variable-or-parameter variable-or-parameter))
	      (expiration
		(expiration-time-of-current-value variable-or-parameter))
	      (value (extract-cached-number-or-value value)))
	  (when (not (eq type 'text))
	    (setq leave-text-representation-as-a-single-line? t))
	  (cond
	    ((or (null value)
		 (null type)
		 (and (numberp expiration)	; implies fixnump here
		      (=f expiration *some-time-ago*)))
	     (twrite "no value"))
	    
	    ((eq expiration 'never)
	     (print-constant value type)
	     (twrite ", valid indefinitely"))
	    
	    ((<f expiration gensym-time)
	     (print-constant value type)
	     (twrite ", expired ")
	     (write-date-and-time expiration))
	    
	    (t
	     (print-constant value type)
	     (twrite ", expires ")
	     (write-date-and-time expiration)
	     (schedule-update-for-variable-expiration variable-or-parameter))))

	(let ((type (data-type-of-variable-or-parameter variable-or-parameter))
	      (value (extract-cached-number-or-value value)))
	  (when (not (eq type 'text))
	    (setq leave-text-representation-as-a-single-line? t))
	  (cond
	    ((null value)		; this case is rarely, if ever, reached; it may
	     (twrite "no value"))	;   be only possible transiently when loading a KB
					;   before all initializations have
					;   finished. (MHD 6/8/99)
	    (t
	     (print-constant value type)))))))




(add-grammar-rules
  '((validity-interval 'supplied)
    (validity-interval 'indefinite)
    (validity-interval interval)
    ))




(define-category-evaluator-interface (validity-interval
				       :access read-write)
    (or (member supplied indefinite)
	integer)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))




(def-slot-value-compiler validity-interval (parse-result variable)
  (declare (ignore variable) (use-for-default-overrides))
  (if (consp parse-result)
      (car parse-result)
      parse-result))


(def-slot-value-writer validity-interval (validity-interval)
  (cond ((symbolp validity-interval)
	 (twrite-symbol validity-interval))
	((numberp validity-interval)		; implies fixnump here
	 (print-constant validity-interval 'seconds))))


;; Sensor-validity-interval is also the type used by minimum-display-interval
;; which is a slot of message-board-parameters.

(add-grammar-rules
  '((sensor-validity-interval 'indefinite)
    (sensor-validity-interval interval)
    )) 

(def-slot-value-compiler sensor-validity-interval (parse-result)
  (if (consp parse-result) (car parse-result) parse-result))


(def-slot-value-writer sensor-validity-interval (validity-interval)
  (cond ((symbolp validity-interval)
	 (twrite-symbol validity-interval))
	((numberp validity-interval)		; implies fixnump here
	 (print-constant validity-interval 'seconds))))

(define-category-evaluator-interface (sensor-validity-interval
				       :access read-write)
    (or (member indefinite supplied)
	integer)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))






(add-grammar-rules
  '((interval? interval)
    (interval? 'none)

    (positive-interval? interval)
    (positive-interval? 'none)

    (execution-interval? interval)
    (execution-interval? 'none)

    (positive-quantity-interval? quantity-interval)
    (positive-quantity-interval? 'none)
    (positive-quantity-interval quantity-interval)))

(def-slot-value-compiler interval? (parse-result)
  (if (eq parse-result 'none) nil (car parse-result)))

(def-slot-value-writer interval? (interval?)
  (cond ((null interval?)
	 (twrite-symbol 'none))
	((numberp interval?)			; implies fixnump here
	 (print-constant interval? 'seconds))))

(define-category-evaluator-interface (positive-quantity-interval?
				       :access read-write)
    (or number (no-item))
  ((set-form (evaluation-value))
   (if evaluation-value
       (phrase-cons
	 (evaluation-quantity-to-phrase-quantity evaluation-value)
	 'seconds)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (if (managed-float-p slot-value)
	   (copy-managed-float-into-evaluation-float slot-value)
	   slot-value)
       nil)))

(def-slot-value-compiler interval (parse-result)
  (car parse-result))

(def-slot-value-writer interval (interval)
  (print-constant interval 'seconds))

(def-slot-value-compiler positive-interval? (parse-result)
  (cond ((eq parse-result 'none) nil)
	((<=i (car parse-result) 0)
	 (values bad-phrase
		 (copy-constant-wide-string #w"The interval must be greater than zero.")))
	(t (car parse-result))))

(def-slot-value-writer positive-interval? (positive-interval?)
  (cond ((null positive-interval?)
	 (twrite-symbol 'none))
	((fixnump positive-interval?)
	 (print-constant positive-interval? 'seconds))))

(def-slot-value-compiler execution-interval? (parse-result)
  (cond ((eq parse-result 'none) nil)
	((<=f (car parse-result) 0)
	 (values bad-phrase
		 (copy-constant-wide-string #w"The interval must be greater than zero.")))
	((>f (car parse-result) #.(* 24 60 60))
	 (values bad-phrase
		 (copy-constant-wide-string #w"The interval must be no more than 24 hours.")))
	(t (car parse-result))))

(def-slot-value-writer execution-interval? (value)
  (write-slot-value 'positive-interval? value nil))

(def-slot-value-compiler quantity-interval (parse-result)
  (car parse-result))

(def-slot-value-writer quantity-interval (quantity-interval)
  (print-constant quantity-interval 'seconds))

(def-slot-value-compiler positive-quantity-interval? (parse-result)
  (if (or (eq parse-result 'none)
	  (eq parse-result nil))
      nil
      (let ((number (car-of-cons parse-result)))
	(if (fixnump number)
	    (if (pluspf number)
		number
		(values
		  bad-phrase
		  (copy-constant-wide-string #w"The interval must be greater than zero.")))
	    (if (with-temporary-gensym-float-creation positive-quanity-compiler
		  (>e (phrase-float-value number) 0.0))
		number
		(values
		  bad-phrase
		  (copy-constant-wide-string #w"The interval must be greater than zero.")))))))

(def-slot-value-compiler positive-quantity-interval (parse-result)
  (let ((number (car-of-cons parse-result)))
    (if (fixnump number)
	(if (pluspf number)
	    number
	    (values
	      bad-phrase
	      (copy-constant-wide-string #w"The interval must be greater than zero.")))
	(if (with-temporary-gensym-float-creation positive-quanity-compiler
	      (>e (phrase-float-value number) 0.0))
	    number
	    (values
	      bad-phrase
	      (copy-constant-wide-string #w"The interval must be greater than zero."))))))

(def-slot-value-writer positive-quantity-interval? (number?)
  (if number?
      (print-constant number? 'seconds)
      (twrite-string "none")))
			
	       


(add-grammar-rules '((interval?-or-default interval?)
		     (interval?-or-default ('use 'default) default)
		     (positive-interval?-or-default positive-interval?)
		     (positive-interval?-or-default ('use 'default) default)
		     (execution-interval?-or-default positive-interval?)
		     (execution-interval?-or-default ('use 'default) default)
		     ))



(def-slot-value-compiler interval?-or-default (parse-result)
  (cond ((eq parse-result 'none) nil)
	((eq parse-result 'default) parse-result)
	((=i (car parse-result) 0)
	 (values bad-phrase
		 (copy-constant-wide-string #w"The interval must not be zero.")))
	(t (car parse-result))))

(define-category-evaluator-interface (interval?-or-default
				       :access read-write)
    (or (no-item)
	(member use-default)
	integer)
  ((set-form (evaluation-value))
   (cond ((integerp evaluation-value)
	  (phrase-cons evaluation-value 'seconds))
	 ((eq evaluation-value 'use-default)
	  'default)
	 (t 'none)))
  ((get-form (slot-value))
   (if (eq slot-value 'default)
       'use-default
       slot-value)))

(def-slot-value-writer interval?-or-default (value)
  (cond ((null value)
	 (twrite-symbol 'none))
	((eq value 'default)
	 (twrite "use default"))
	((numberp value)			; implies fixnump here
	 (print-constant value 'seconds))))


(def-slot-value-compiler positive-interval?-or-default (parse-result)
  (cond ((eq parse-result 'none) nil)
	((eq parse-result 'default) parse-result)
	((<=i (car parse-result) 0)
	 (values bad-phrase
		 (copy-constant-wide-string #w"The interval must be greater than zero.")))
	(t (car parse-result))))


(def-slot-value-writer positive-interval?-or-default (value)
  (cond ((null value)
	 (twrite-symbol 'none))
	((eq value 'default)
	 (twrite "use default"))
	((fixnump value)
	 (print-constant value 'seconds))))

(def-slot-value-compiler execution-interval?-or-default (parse-result)
  (cond ((eq parse-result 'none) nil)
	((eq parse-result 'default) parse-result)
	((<=f (car parse-result) 0)
	 (values bad-phrase
		 (copy-constant-wide-string #w"The interval must be greater than zero.")))
	((>f (car parse-result) #.(* 24 60 60))
	 (values bad-phrase
		 (copy-constant-wide-string #w"The interval must be no more than 24 hours.")))
	(t (car parse-result))))

(define-category-evaluator-interface (execution-interval?-or-default
				       :access read-write)
    (or (no-item) (member use-default) integer)
  ((set-form (evaluation-value))
   (if evaluation-value
       (if (eq evaluation-value 'use-default)
	   'default
	   (phrase-cons evaluation-value 'seconds))
       'none))
  ((get-form (slot-value))
   (if (eq slot-value 'default) 'use-default slot-value)))

(def-slot-value-writer execution-interval?-or-default (value)
  (write-slot-value 'positive-interval?-or-default value nil))






;;;; Slots of simulation frames

;; Grammar for specific-simulation-formula?

(add-grammar-rules
  '((specific-simulation-formula? 'none)
    (specific-simulation-formula? state-variable-simulation-expression)
    (specific-simulation-formula? dependent-variable-simulation-expression)

    (dependent-variable-simulation-expression simulation-expression)
    (state-variable-simulation-expression
      ('state 'variable '\: 'd '\/ 'dt '= simulation-expression '\, 
       'with 'initial 'value simulation-expression) (continuous-state 8 13))
    (state-variable-simulation-expression
      ('state 'variable '\: 'next 'value '= simulation-expression '\,
       'with 'initial 'value simulation-expression) (discrete-state 7 12))))



;; Add grammar for using simulated histories soon.


;;; The slot value compiler for specific-simulation-formula? expects parse-result
;;; to be of the form
;;; 
;;;    simulation-expression;
;;;    ('continuous-state simulation-expression initial-value); or
;;;    ('discrete-state simulation-expression initial-value)
;;;    
;;; Initial-value is a simulation-expression.
;;; The slot value compiler will return a list of the form
;;; (simulation-category simulation-expression initial-value).
;;; In the first of the above cases, simulation-category is 'dependent,
;;; simulation-expression is the compiled version of the simulation-expression
;;; passed in, and initial-value is nil.  The second and third cases are
;;; similar except that simulation-category is 'continuous-state or 
;;; 'discrete-state, and the initial-value is the compiled version of the
;;; initial value passed in.  Simulation-expression and initial-value
;;; (if any) are both compiled by compile-expression and there is no
;;; focus name.

(def-slot-value-compiler specific-simulation-formula? 
    (parse-result simulation-subtable slot-name)
  (declare (ignore slot-name))
  (update-frame-status simulation-subtable nil nil)
  ;; Simulation-subtable starts out O.K.  This can be changed by
  ;; slot compiler or putter.

  (let* ((*current-computation-frame* simulation-subtable)
	 (form-to-return
	   (cond 
	     ((eq parse-result 'none)
	      (phrase-list 
		nil
		(compile-expression nil nil nil)       ; just to get rid of frame notes
		nil))
	     ((or (not (consp parse-result))
		  (not (memq (car parse-result) 
			     '(discrete-state continuous-state))))
	      ;; It is assumed here that 'discrete-state and 'continuous-state will never be
	      ;; operators.
	      
	      ;; dependent category
	      (let ((compiled-expression?
		      (compile-expression 
			parse-result nil nil)))
		(cond
		  (compiled-expression?
		   (phrase-list
		     'dependent
		     compiled-expression?
		     nil))
		  (t
		   (update-frame-status simulation-subtable 'bad nil)
		   (phrase-list 'dependent nil nil)))))
	     (t
	      (let ((compiled-expression?
		      (compile-expression 
			(second parse-result) nil nil))
		    (simulation-category (car parse-result))
		    compiled-initial-value?)
		(cond
		  ((null compiled-expression?)
		   (update-frame-status simulation-subtable 'bad nil)
		   (phrase-list simulation-category nil nil))
		  (t
		   (setq compiled-initial-value?
			 (compile-expression 
			   (third parse-result) nil nil))
		   (cond
		     ((null compiled-initial-value?)
		      (update-frame-status simulation-subtable 'bad nil)
		      (phrase-list simulation-category nil nil))
		     (t
		      (phrase-list 
			simulation-category
			compiled-expression?
			compiled-initial-value?))))))))))
    (cond 
      ((third form-to-return)
       ;; this is to prevent consistency analysis from hosing the compiliation -rdf, 4/24/95
       (change-slot-value
	 simulation-subtable
	 'simulation-subtable-byte-code-body
	 nil)
       (let* ((current-computation-component-particulars
		'(simulation-initial-value *current-computation-frame*))
	      (byte-code-body 
		(compile-simulation-formula-for-stack
		  (third form-to-return) nil nil t)))

	 (change-slot-value
	   simulation-subtable
	   'simulation-subtable-initial-value-byte-code-body
	   byte-code-body)))
      
      
      (t
       (change-slot-value
	 simulation-subtable
	 'simulation-subtable-initial-value-byte-code-body
	 nil)))
    (when (second form-to-return)
      (let ((byte-code-body 
	      (compile-simulation-formula-for-stack
		(second form-to-return) nil nil nil)))
	(change-slot-value
	  simulation-subtable
	  'simulation-subtable-byte-code-body
	  byte-code-body)))
    form-to-return))

;; Note that if specific simulation formula is bad, the simulation frame is
;; given a bad frame status but the variable isn't.

;; May want to adopt frame status update approach used in generic-formulas in
;; specific and generic simulation formulas.  Setting the frame status O.K. is
;; taken care of by slot putter rather than slot value compiler.  



;;; Slot which have a number or "none" (NIL) have type number?

(def-slot-value-writer whole-string? (whole-string?)
  (if whole-string?
      (let ((write-strings-parsably? t))
	(twrite-string whole-string?))
      (twrite-string "none")))

(def-slot-value-compiler whole-string? (parse-result)
  (if (text-string-p parse-result) parse-result nil))

(def-slot-value-writer read-only-whole-string? (whole-string?)
  (if whole-string?
      (let ((write-strings-parsably? t))
	(twrite-string whole-string?))
      (twrite-string "none")))

(add-grammar-rules
  '((number? 'none)
    (number? number)

    (integer? 'none)
    (integer? integer)

    (float? 'none)
    (float? float)
    
    (whole-string? 'none)
    (whole-string? whole-string)

    (symbol? 'none)
    (symbol? symbol)
    
    (truth-value 'true)
    (truth-value 'false)
    (truth-value (number 'true) (1 . truth-value) (check-range-of-element 1 -1 1))

    (truth-value? 'none)
    (truth-value? truth-value)

    (quantity number)
    (quantity interval)
    ;; add time-stamp!!!
    
    (quantity (number singular-unit-of-measure)
	      (1 . 2) 
	      convert-singular-constant)
    (quantity (number plural-unit-of-measure) (1 . 2))
    (quantity (number neutral-unit-of-measure) (1 . 2))
    
    (quantity? quantity)
    (quantity? 'none)))


(define-category-evaluator-interface (truth-value
				       :access read-write)
    truth-value
  ((set-form (evaluation-value))
   (case (evaluation-truth-value-value evaluation-value)
     (#.truth 'true)
     (#.falsity 'false)
     (t
      (with-temporary-gensym-float-creation
	  category-evaluator-interface-for-truth-value
	(make-slot-constant-using-phrase-conses
	  (/e (coerce-fixnum-to-gensym-float (car evaluation-value))
	      (coerce-fixnum-to-gensym-float truth))
	  'truth-value)))))
  ((get-form (slot-value))
   (make-evaluation-truth-value slot-value)))

(define-category-evaluator-interface (truth-value?
				       :access read-write)
    (or (no-item) (named truth-value))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'truth-value evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'truth-value slot-value nil nil)
       nil)))

(define-category-evaluator-interface (non-negative-integer
				       :access read-write)
    integer
  ((set-form (evaluation-value)) evaluation-value)
  ((get-form (slot-value)) slot-value))

(define-category-evaluator-interface (integer
				       :access read-write)
    integer
  ((set-form (evaluation-value)) evaluation-value)
  ((get-form (slot-value)) slot-value))

(define-category-evaluator-interface (integer?
				       :access read-write)
    (or (no-item) (named integer))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'integer evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'integer slot-value nil nil)
       nil)))

(define-category-evaluator-interface (quantity
				       :access read-write)
    number
  ((set-form (evaluation-value))
   (evaluation-quantity-to-phrase-quantity evaluation-value))
  ((get-form (slot-value))
   (if (consp slot-value)
       (if (managed-float-p (car-of-cons slot-value))
	   (copy-managed-float-into-evaluation-float (car-of-cons slot-value))
	   (car-of-cons slot-value))
       (if (managed-float-p slot-value)
	   (copy-managed-float-into-evaluation-float slot-value)
	   slot-value))))

(define-category-evaluator-interface (quantity?
				       :access read-write)
    (or (no-item) (named quantity))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'quantity evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'quantity slot-value nil nil)
       nil)))

(define-category-evaluator-interface (initial-value-float
				       :access read-write)
    float
  ((set-form (evaluation-value))
   (evaluation-quantity-to-phrase-quantity evaluation-value))
  ((get-form (slot-value))
   (copy-managed-float-into-evaluation-float slot-value)))

(define-category-evaluator-interface (initial-value-float?
				       :access read-write)
    (or (no-item) (named initial-value-float))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'initial-value-float evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'initial-value-float slot-value nil nil)
       nil)))
   
(define-category-evaluator-interface (initial-value-integer
				       :access read-write)
    integer
  ((set-form (evaluation-value)) evaluation-value)
  ((get-form (slot-value)) slot-value))

;added by SoftServe
(define-category-evaluator-interface (initial-value-long
				       :access read-write)
    long
  ((set-form (evaluation-value)) evaluation-value)
  ((get-form (slot-value)) slot-value))

(define-category-evaluator-interface (initial-value-long?
				       :access read-write)
    (or (no-item) (named initial-value-long))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'initial-value-long evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'initial-value-long slot-value nil nil)
       nil)))

;end of changes

(define-category-evaluator-interface (initial-value-integer?
				       :access read-write)
    (or (no-item) (named initial-value-integer))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'initial-value-integer evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'initial-value-integer slot-value nil nil)
       nil)))

(define-category-evaluator-interface (standard-or-class-qualified-symbol
				       :access read-write)
    symbol
  ((set-form (evaluation-value)) evaluation-value)
  ((get-form (slot-value)) slot-value))

(define-category-evaluator-interface (standard-or-class-qualified-symbol?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter
	 'standard-or-class-qualified-symbol evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter
	 'standard-or-class-qualified-symbol slot-value nil nil)
       nil)))

(define-category-evaluator-interface (whole-string
				       :access read-write)
    text
  ((set-form (evaluation-value)) (copy-for-phrase evaluation-value))
  ;; I believe the following causes a corruption by not copying the string.
  ;; Adding a copy.  FIND ME, JRA!  -jra 6/16/96
  ((get-form (slot-value))
   (make-evaluation-text slot-value)))

(define-category-evaluator-interface (whole-string?
				       :access read-write)
    (or (no-item) (named whole-string))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'whole-string evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'whole-string slot-value nil nil)
       nil)))

(define-category-evaluator-interface (read-only-whole-string?
				       :access read)
    (or (no-item) (named whole-string))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'whole-string slot-value nil nil)
       nil)))

(define-category-evaluator-interface (positive-integer
				       :access read-write)
    integer
  ((set-form (evaluation-value)) evaluation-value)
  ((get-form (slot-value)) slot-value))

(define-category-evaluator-interface (read-only-positive-integer
				       :access read)
    integer
  ((get-form (slot-value)) slot-value))

(def-slot-value-writer read-only-positive-integer (integer)
  (write-attribute integer))



;;; The `category evaluator interface for read-only-integer' is the same as that
;;; for read-only-positive-integer.

(define-category-evaluator-interface (read-only-integer
				       :access read)
    integer
  ((get-form (slot-value)) slot-value))

(def-slot-value-writer read-only-integer (integer)
  (write-attribute integer))



(define-category-evaluator-interface (positive-integer?
				       :access read-write)
    (or (no-item) (named positive-integer))
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'positive-integer evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'positive-integer slot-value nil nil)
       nil)))

(def-slot-value-writer read-only-positive-integer? (integer)
  (write-attribute integer))

(define-category-evaluator-interface (read-only-positive-integer?
				       :access read)
    (or (no-item) (named positive-integer))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'positive-integer slot-value nil nil)
       nil)))



;; The following grammar form adds intervals and units of measure
;; to the initial values of integer and float parameters and variables.
;; (ghw 4/17/95)

(add-grammar-rules
  '((initial-value-integer integer)
    (initial-value-integer interval)
    (initial-value-integer (integer singular-unit-of-measure)
     (1 . 2) 
     convert-singular-constant)
    (initial-value-integer (integer plural-unit-of-measure) (1 . 2))
    (initial-value-integer (integer neutral-unit-of-measure) (1 . 2))

    (initial-value-integer? initial-value-integer)
    (initial-value-integer? 'none)
    
    (initial-value-long long)
    (initial-value-long? initial-value-long)
    (initial-value-long? 'none)

    (initial-value-float float)
    (initial-value-float (float singular-unit-of-measure)
     (1 . 2) 
     convert-singular-constant)
    (initial-value-float (float plural-unit-of-measure) (1 . 2))
    (initial-value-float (float neutral-unit-of-measure) (1 . 2))

    (initial-value-float? initial-value-float)
    (initial-value-float? 'none)))

(add-grammar-rules
  `((delay-millisecond-time? integer?)))

(defun data-type-of-initial-sensor-value (parse-result)
  (cond ((memq parse-result '(true false)) 'truth-value)
	((phrase-number-p parse-result) 'number)
	((text-string-p parse-result) 'text)  ;fix!!
	((symbolp parse-result) 'symbol)
	(t (cdr parse-result))))

(def-slot-value-compiler initial-sensor-value? (parse-result frame?)
  (declare (use-for-default-overrides))
  (let* ((incoming-type
	  (data-type-of-initial-sensor-value parse-result)))
    (if (or (null frame?)
	    (value-type-compatible
	      incoming-type
	      (data-type-of-variable-or-parameter frame?))
	    (eq parse-result 'none))
	(cond
	  ((eq parse-result 'none) nil)
	  ((eq parse-result 'true) (phrase-list truth 'truth-value))
	  ((eq parse-result 'false) (phrase-list falsity 'truth-value))
	  ((atom parse-result) parse-result)
	  ((eq (cdr parse-result) 'truth-value)
	   (round (* truth (car parse-result))))
	  ((phrase-number-p (car parse-result))
	   (car parse-result))
	  #+development
	  (t (cerror "Continue" "Illegal value passed to the svc for initial-sensor-value?")))

	(values bad-phrase
		(copy-text-string
		  "The initial value must be compatible with the type of the variable.")))))

(def-slot-value-writer initial-sensor-value? (value frame?)
  (cond ((slot-constantp value)
	 (print-constant
	   (get-slot-value-number-or-string-from-slot-constant value)
	   (get-unit-from-slot-constant value)))
	(value
	 (print-constant
	   value
	   (if (framep frame?)
	       (data-type-of-variable-or-parameter frame?)
	     (evaluation-value-type value))))
	(t
	 (twrite-string "none"))))

(define-category-evaluator-interface (initial-sensor-value?
				       :access read-write)
    (or (no-item) symbol truth-value number text)
  ((set-form (evaluation-value))
   (if (null evaluation-value)
       'none
       (copy-evaluation-value-to-phrase evaluation-value)))
  ((get-form (slot-value frame?))
   (get-evaluation-value-for-attribute slot-value frame?)))




;;; The slot value compiler for the dynamic display delay in milliseconds
;;; slot limits the input to positive integers below 60000, or the value none.

(def-slot-value-compiler delay-millisecond-time? (parse-result)
  (cond ((eq parse-result 'none)
	 nil)
	((and (integerp parse-result)
	      (> parse-result 0)
	      (<= parse-result 60000))
	 parse-result)
	(t
	 (values bad-phrase
		 (copy-text-string
		   "Must be \"none\" or an integer from 1 through 60000.")))))

(define-category-evaluator-interface (delay-millisecond-time?
				       :access read-write)
    (named integer?)
  ((set-form (evaluation-value))
   (call-category-setter 'integer? evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'integer? slot-value nil nil)))

(def-slot-value-writer delay-millisecond-time? (value)
  (write-integer?-from-slot value nil))


;; The define-category-evaluator-interface for TRACE-FILE-PATHNAME was
;; moved here from grammar4a because it depends on the category evaluator for
;; whole-string.  - cpm, 7/1/96

(define-category-evaluator-interface (trace-file-pathname
				       :access read-write)
    (or symbol (named whole-string))
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       nil
       (call-category-setter 'whole-string evaluation-value nil nil nil)))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'whole-string slot-value nil nil)
       'none)))

(def-slot-value-writer number? (number? frame)
  (if (null number?)
      (twrite "none")				; fixed for slot value floats by using 
						;   writer for number. (MHD 3/18/91)
      (write-number-from-slot number? frame)))	; see (def-slot-value-writer number ...)

(def-slot-value-compiler quantity (parse-result frame)
  (compile-initial-sensor-value?-for-slot parse-result frame nil))

(def-slot-value-writer quantity (value frame)
  (write-initial-sensor-value?-from-slot value frame))

(def-slot-value-compiler quantity? (parse-result frame)
  (compile-initial-sensor-value?-for-slot parse-result frame nil))

(def-slot-value-writer quantity? (value frame)
  (write-initial-sensor-value?-from-slot value frame))


;;; The slot value compiler for number? expects parse-result to be either a
;;; slot value number or a symbol, namely the symbol NONE.

(def-slot-value-compiler number? (parse-result)
  (if (slot-value-number-p parse-result) parse-result nil))

(define-category-evaluator-interface (number?
				       :access read-write)
    (or (no-item) number)
  ((set-form (evaluation-value))
   (if evaluation-value
       (evaluation-quantity-to-phrase-quantity evaluation-value)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (if (managed-float-p slot-value) 
	   (copy-managed-float-into-evaluation-float slot-value)
	   slot-value)
       nil)))

(def-slot-value-writer number (number)
  (with-temporary-gensym-float-creation writer-for-float
    (let ((number-value				; fixed for slot value floats. (MHD 3/18/91)
	    (slot-value-number-value number)))
      (cond ((floatp number-value)
	     (twrite-float number-value))
	    ((long-p number-value)
	     (twrite-long number-value))
	    (t
	     (twrite number-value))))))

(def-slot-value-writer integer (integer)
  (twrite integer))

(def-slot-value-writer initial-value-integer (integer frame)
  (write-initial-sensor-value?-from-slot integer frame))

(def-slot-value-writer long (long)
  (with-temporary-creation writer-for-long
    (twrite-long long)))

(def-slot-value-writer initial-value-long (i64 frame)
  (write-initial-sensor-value?-from-slot i64 frame))

(def-slot-value-writer float (slot-value-or-gensym-float)
  (with-temporary-gensym-float-creation writer-for-float
    (twrite-float				
      (slot-value-number-value slot-value-or-gensym-float))))

(def-slot-value-writer initial-value-float (slot-value-or-gensym-float frame)
  (write-initial-sensor-value?-from-slot slot-value-or-gensym-float frame))

(def-slot-value-writer float? (slot-value-float-or-nil)
  (if (null slot-value-float-or-nil)
      (twrite-string "none")
      (write-float-from-slot slot-value-float-or-nil nil)))

(def-slot-value-writer initial-value-float? (slot-value-float-or-nil frame)
  (write-initial-sensor-value?-from-slot slot-value-float-or-nil frame))
	
(def-slot-value-writer integer? (integer?)
  (if integer?
      (twrite integer?)
      (twrite-string "none")))

(def-slot-value-writer initial-value-integer? (integer? frame)
  (write-initial-sensor-value?-from-slot integer? frame))

(def-slot-value-writer initial-value-long? (i64? frame)
  (write-initial-sensor-value?-from-slot i64? frame))

(def-slot-value-compiler initial-value-long? (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-initial-sensor-value?-for-slot parse-result frame nil))

(def-slot-value-compiler initial-value-long (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-initial-sensor-value?-for-slot parse-result frame nil))

;;; The slot value compiler for integer? expects parse-result to be either an
;;; integer or a symbol, namely the symbol NONE.

(def-slot-value-compiler integer? (parse-result)
  (if (integerp parse-result) parse-result nil))

(def-slot-value-compiler initial-value-integer? (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-initial-sensor-value?-for-slot parse-result frame nil))

(def-slot-value-compiler float? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-compiler initial-value-float? (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-initial-sensor-value?-for-slot parse-result frame nil))



(def-slot-value-compiler initial-value-integer (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-initial-sensor-value?-for-slot parse-result frame nil))

(def-slot-value-compiler initial-value-float (parse-result frame)
  (declare (use-for-default-overrides))
  (compile-initial-sensor-value?-for-slot parse-result frame nil))

(def-slot-value-writer-as-existing-function
  symbol write-symbol-from-slot)




;;; The slot value compiler for symbol? expects parse-result to be a symbol.
;;; If parse-result is the symbol NONE, the compilation result is NIL; otherwise,
;;; the compilation result is parse-result.

(def-slot-value-compiler symbol? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-compiler standard-or-class-qualified-symbol? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-writer standard-or-class-qualified-symbol? (symbol?)
  (if (null symbol?)
      (twrite-string "none")
      (print-constant symbol? 'symbol)))

(def-slot-value-compiler standard-or-class-qualified-symbol (parse-result)
  parse-result)

(def-slot-value-writer standard-or-class-qualified-symbol (symbol)
  (print-constant symbol 'symbol))
  

;; Notice that this poses special problems for entering the symbol NONE,
;; literally.  (MHD 2/26/91)


(def-slot-value-writer-as-existing-function
  symbol? write-symbol-from-slot)

(def-slot-value-writer whole-string (whole-string)
  (let ((write-strings-parsably? t))
    (twrite-string whole-string)))

(def-slot-value-compiler truth-value (parse-result)
  (compile-truth-value-parse-result parse-result))

(def-slot-value-compiler truth-value? (parse-result)
  (cond ((eq parse-result 'none) nil)
	(t (compile-truth-value-parse-result parse-result))))

(defun compile-truth-value-parse-result (parse-result)
  (cond ((eq parse-result 'true) truth)
	((eq parse-result 'false) falsity)
	(t (with-temporary-gensym-float-creation
	     compile-truth-value-parse-result
	     (round
	       (* truth
		  (if (phrase-float-p (car parse-result))
		      (phrase-float-value (car parse-result))
		      (car parse-result))))))))	; presumably, 1 or 0
;; Compilers for truth-value(?) above fixed to use phrase float abstraction
;; today. (MHD 3/15/91)


(def-slot-value-writer truth-value (value)
  (print-constant value 'truth-value))

(def-slot-value-writer truth-value? (value)
  (if value
      (print-constant value 'truth-value)
      (twrite-string "none")))














;;;; Frame flags for variables

;;; The frame flags involved are: forward-chain, dont-backward-chain, passive,
;;; and depth-first. 

;;; There is an additional frame flag for NUPEC, cache-data-for-explanation.
;;; (this is now generally available -dkuznick, 7/15/98)

;;; There is now another frame-flag: always-forward-chain-if-possible
;;; -dkuznick, 7/23/04 

;;; There are two choices for variables:

;;; First choice:
;;; (1) do not forward chain			forward-chain = 0
;;;
;;; (2) do forward chain			forward chain = 1

;;; Second choice:
;;; (1) do not seek data			dont-backward-chain = 1
;;;						passive = 1
;;;						
;;; (2) do not backward chain			dont-backward-chain = 1
;;; 						passive = 0
;;; 						
;;; (3) depth first backward chain		dont-backward-chain = 0
;;; 						passive = 0
;;; 						depth-first = 1
;;;
;;; (4) breadth first backward chain		dont-backward-chain = 0
;;; 						passive = 0
;;; 						depth-first = 0


(add-grammar-rules
  '(
    (variable-frame-flags (variable-forward-chain-spec '\, variable-backward-chain-spec)
		     (1 dont-always-forward-chain-if-possible-flag 3))
    (variable-frame-flags (variable-forward-chain-spec '\, variable-backward-chain-spec
						       '\, cache-explanation-spec)
			  (1 dont-always-forward-chain-if-possible-flag 3 5))

    (variable-frame-flags (variable-forward-chain-spec
			   variable-always-forward-chain-spec
			   '\, variable-backward-chain-spec)
		     (1 2 4))
    (variable-frame-flags (variable-forward-chain-spec
			   variable-always-forward-chain-spec
			   '\, variable-backward-chain-spec
			   '\, cache-explanation-spec)
			  (1 2 4 6))

    (variable-forward-chain-spec ('do 'forward 'chain) forward-chain-flag)
    (variable-forward-chain-spec ('do 'not 'forward 'chain))	; nil as template?

    (variable-always-forward-chain-spec ('even 'for 'same 'value)
     always-forward-chain-if-possible-flag)

    (variable-backward-chain-spec ('do 'not 'seek 'data) passive-flag)
    (variable-backward-chain-spec ('do 'not 'backward 'chain) dont-backward-chain-flag)
    (variable-backward-chain-spec ('depth 'first 'backward 'chain) depth-first-flag)
    (variable-backward-chain-spec ('breadth 'first 'backward 'chain))  ; nil as template?

    (cache-explanation-spec 
      ('cache 'data 'for 'explanation) cache-data-for-explanation-flag)
    (cache-explanation-spec
      ('do 'not 'cache 'data 'for 'explanation)) ; nil as template?

    (parameter-frame-flags variable-forward-chain-spec
     (1 dont-always-forward-chain-if-possible-flag passive-flag))
    (parameter-frame-flags (variable-forward-chain-spec '\, cache-explanation-spec)
     (1 dont-always-forward-chain-if-possible-flag passive-flag 3))

    (parameter-frame-flags (variable-forward-chain-spec
			    variable-always-forward-chain-spec)
     (1 2 passive-flag))
    (parameter-frame-flags (variable-forward-chain-spec
			    variable-always-forward-chain-spec
			    '\, cache-explanation-spec)
     (1 2 passive-flag 4))

    ))




(define-category-evaluator-interface (variable-frame-flags
				       :access read-write)
    (structure variable-frame-flags-spec
	       ((forward-chain truth-value)
		(forward-chain-even-for-same-value truth-value)
		(backward-chain (member breadth-first depth-first
					do-not-backward-chain do-not-seek-data))
		(explanation-data truth-value))
	       (and forward-chain backward-chain))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value variable-frame-flags-spec)
     (let ((forward-chaining-phrase
	    (if (evaluation-boolean-is-true-p forward-chain)
		'forward-chain-flag
		(phrase-list 'do 'not 'forward 'chain)))
	   (for-same-value-phrase
	     (if (evaluation-boolean-is-true-p
		   forward-chain-even-for-same-value)
		 'always-forward-chain-if-possible-flag
		 'dont-always-forward-chain-if-possible-flag))
	   (backward-chaining-phrase
	    (case backward-chain
	      (do-not-seek-data 'passive-flag)
	      (do-not-backward-chain 'dont-backward-chain-flag)
	      (depth-first 'depth-first-flag)
	      (t (phrase-list 'breadth 'first 'backward 'chain))))
	   (explanation-phrase 
	     (when (evaluation-boolean-is-true-p explanation-data)
	       'cache-data-for-explanation-flag)))
       (phrase-list forward-chaining-phrase for-same-value-phrase
		    backward-chaining-phrase explanation-phrase))))
  ((get-form (slot-value))
   (with-new-structure (variable-frame-flags-spec)
     (let ((backward-chaining-info
	    (cond
	      ((passive-of-flag-vector-p slot-value)
	       'do-not-seek-data)
	      ((dont-backward-chain-of-flag-vector-p slot-value)
	       'do-not-backward-chain)
	      ((depth-first-of-flag-vector-p slot-value)
	       'depth-first)
	      (t
	       'breadth-first))))
       (setf forward-chain (make-evaluation-boolean-value
			     (forward-chain-of-flag-vector-p slot-value)))
       (setf forward-chain-even-for-same-value
	     (make-evaluation-boolean-value
	       (always-forward-chain-if-possible-of-flag-vector-p slot-value)))
       (setf backward-chain backward-chaining-info)
       (when (cache-data-for-explanation-of-flag-vector-p slot-value)
	 (setf explanation-data (make-evaluation-boolean-value t)))))))



(def-slot-value-compiler variable-frame-flags (parse-result variable)
  (if (eq (first parse-result) 'forward-chain-flag)
      (set-forward-chain variable)
      (clear-forward-chain variable))

  (if (eq (second parse-result) 'always-forward-chain-if-possible-flag)
      (set-always-forward-chain-if-possible variable)
      (clear-always-forward-chain-if-possible variable))

  (set-not-passive variable)
  (clear-dont-backward-chain variable)
  (clear-depth-first variable)

  (case (third parse-result)
    (passive-flag
      (set-passive variable)
      (set-dont-backward-chain variable))
    (dont-backward-chain-flag
      (set-dont-backward-chain variable))
    (depth-first-flag
      (set-depth-first variable))
    ;; last case is breadth first - no flags set
    )

  (if (eq (fourth parse-result) 'cache-data-for-explanation-flag)
      (set-cache-data-for-explanation variable)
      (let ((cached-explanation?
	      (cached-explanation variable)))
	;; Clear the flag.
	(clear-cache-data-for-explanation variable)
	;; Clear and reclaim any cached explanation.
	(when cached-explanation?
	  (reclaim-cached-explanation cached-explanation?)
	  (setf (cached-explanation variable) nil))))

  (frame-flags variable))

;; Note that there is a similar decoding for default-overrides


(def-slot-value-compiler parameter-frame-flags (parse-result parameter)
  (if (eq (first parse-result) 'forward-chain-flag)
      (set-forward-chain parameter)
      (clear-forward-chain parameter))

  (if (eq (second parse-result) 'always-forward-chain-if-possible-flag)
      (set-always-forward-chain-if-possible parameter)
      (clear-always-forward-chain-if-possible parameter))

  (clear-depth-first parameter)
  (set-passive parameter)
  (set-dont-backward-chain parameter)

  (if (eq (fourth parse-result) 'cache-data-for-explanation-flag)
      (set-cache-data-for-explanation parameter)
      (let ((cached-explanation?
	      (cached-explanation parameter)))
	;; Clear the flag.
	(clear-cache-data-for-explanation parameter)
	;; Clear and reclaim any cached explanation.
	(when cached-explanation?
	  (reclaim-cached-explanation cached-explanation?)
	  (setf (cached-explanation parameter) nil))))

  (frame-flags parameter))

(define-category-evaluator-interface (parameter-frame-flags
				       :access read-write)
    (structure parameter-frame-flags-spec
	       ((forward-chain truth-value)
		(forward-chain-even-for-same-value truth-value)
		(explanation-data truth-value))
	       (and forward-chain)) ;; symmetric with variable-frame-flags
  ((set-form (evaluation-value))
   (with-structure (evaluation-value parameter-frame-flags-spec)
     (let ((forward-chaining-phrase
	     (if (evaluation-boolean-is-true-p forward-chain)
		 'forward-chain-flag 
		 (phrase-list 'do 'not 'forward 'chain)))
	   (for-same-value-phrase
	     (if (evaluation-boolean-is-true-p
		   forward-chain-even-for-same-value)
		 'always-forward-chain-if-possible-flag
		 'dont-always-forward-chain-if-possible-flag))
	   (explanation-phrase 
	     (when (evaluation-boolean-is-true-p explanation-data)
	       'cache-data-for-explanation-flag)))
       (phrase-list forward-chaining-phrase for-same-value-phrase
		    'passive-flag explanation-phrase))))
  ((get-form (slot-value))
   (with-new-structure (parameter-frame-flags-spec)
     (setf forward-chain (make-evaluation-boolean-value
			   (forward-chain-of-flag-vector-p slot-value)))
     (setf forward-chain-even-for-same-value
	     (make-evaluation-boolean-value
	       (always-forward-chain-if-possible-of-flag-vector-p slot-value)))
     (when (cache-data-for-explanation-of-flag-vector-p slot-value)
       (setf explanation-data (make-evaluation-boolean-value t))))))



;;; `set-appropriate-instance-frame-flags-for-update-slot-description' handles
;;; the frame-flag instances for variable and parameter classes.  The code
;;; follows the slot-value compiler code for variable-frame-flags and
;;; parameter-frame-flags.

(defun set-appropriate-instance-frame-flags-for-update-slot-description
    (class unchanged-slot-init-form new-slot-init-form
	   unchanged-class-level-slot-description)

  (loop for instance being each strict-class-instance of class
	for old-slot-value = (get-slot-description-value-macro
			       instance unchanged-class-level-slot-description)
	do
    (if (memq 'variable (class-inheritance-path (class-description class)))
	;; When the instance flags follow the default, set them to the new
	;; default; otherwise do nothing.
	(when (and (eq (passive-of-flag-vector-p unchanged-slot-init-form)
		       (passive-p instance))
		   (eq (dont-backward-chain-of-flag-vector-p
			 unchanged-slot-init-form)
		       (dont-backward-chain-p instance))
		   (eq (depth-first-of-flag-vector-p unchanged-slot-init-form)
		       (depth-first-p instance))
		   (eq (forward-chain-of-flag-vector-p unchanged-slot-init-form)
		       (forward-chain-p instance))
		   (eq (always-forward-chain-if-possible-of-flag-vector-p
			 unchanged-slot-init-form)
		       (always-forward-chain-if-possible-p instance))
		   (eq (cache-data-for-explanation-of-flag-vector-p
			 unchanged-slot-init-form)
		       (cache-data-for-explanation-p instance)))

	  (if (forward-chain-of-flag-vector-p new-slot-init-form)
	      (set-forward-chain instance)
	      (clear-forward-chain instance))
	  (if (always-forward-chain-if-possible-of-flag-vector-p
		new-slot-init-form)
	      (set-always-forward-chain-if-possible instance)
	      (clear-always-forward-chain-if-possible instance))
	  (set-not-passive instance)
	  (clear-dont-backward-chain instance)
	  (clear-depth-first instance)
		   
	  (when (passive-of-flag-vector-p new-slot-init-form)
	    (set-passive instance)
	    (set-dont-backward-chain instance))
	  
	  (when (dont-backward-chain-of-flag-vector-p
		  new-slot-init-form)
	    (set-dont-backward-chain instance))
	  
	  (when (depth-first-of-flag-vector-p new-slot-init-form)
	    (set-depth-first instance)))

	;; Parameter case.
	(when (eq (forward-chain-of-flag-vector-p unchanged-slot-init-form)
		  (forward-chain-p instance))
      
	  (if (forward-chain-of-flag-vector-p new-slot-init-form)
	      (set-forward-chain instance)
	      (clear-forward-chain instance))

	  (if (always-forward-chain-if-possible-of-flag-vector-p
		new-slot-init-form)
	      (set-always-forward-chain-if-possible instance)
	      (clear-always-forward-chain-if-possible instance))

	  (clear-depth-first instance)
	  (set-passive instance)
	  (set-dont-backward-chain instance)))

    ;; Variables and parameters.
    (if (cache-data-for-explanation-of-flag-vector-p new-slot-init-form)
	(set-cache-data-for-explanation instance)
	(let ((cached-explanation?
		(cached-explanation instance)))
	  ;; Clear the flag.
	  (clear-cache-data-for-explanation instance)
	  ;; Clear and reclaim any cached explanation.
	  (when cached-explanation?
	    (reclaim-cached-explanation cached-explanation?)
	    (setf (cached-explanation instance) nil))))))




(def-slot-value-writer variable-frame-flags (value)
  (twrite
    (if (forward-chain-of-flag-vector-p value)
	(if (always-forward-chain-if-possible-of-flag-vector-p value)
	    "do forward chain even for same value, "
	    "do forward chain, ")
	"do not forward chain, "))
  
  (twrite
    (cond
      ((passive-of-flag-vector-p value) "do not seek data")
      ((dont-backward-chain-of-flag-vector-p value) "do not backward chain")
      ((depth-first-of-flag-vector-p value) "depth first backward chain")
      (t "breadth first backward chain")))
  
  (when (or (explanation-related-features-enabled-func?)
	    (cache-data-for-explanation-of-flag-vector-p value))
    (twrite
      (if (cache-data-for-explanation-of-flag-vector-p value)
	  ", cache data for explanation"
	  ", do not cache data for explanation")))
  )


;; Note that this is called by slot value writer for default-overrides.




(def-slot-value-writer parameter-frame-flags (value)
  (twrite
    (if (/=f 0 (logand value forward-chain-flag))
	(if (always-forward-chain-if-possible-of-flag-vector-p value)
	    "do forward chain even for same value"
	    "do forward chain")
	"do not forward chain"))
  (when (or (explanation-related-features-enabled-func?)
	    (cache-data-for-explanation-of-flag-vector-p value))
    (twrite
      (if (cache-data-for-explanation-of-flag-vector-p value)
	  ", cache data for explanation"
	  ", do not cache data for explanation")))
  )





(add-grammar-rules
  '((simulation-time-increment
     (number second-or-seconds) 1)
    (simulation-time-increment?
     (number second-or-seconds) 1)
    (simulation-time-increment?
     'none)))
;; Time increment is currently always specified in seconds.  Consider 
;; allowing for an interval-like specification which would allow minutes,
;; hours, etc.  It would, however, also have to allow for fractions of 
;; seconds.


(declare-forward-reference minimum-simulation-time-increment variable)

(def-slot-value-compiler simulation-time-increment? (parse-result)
  (cond 
    ((eq parse-result 'none) nil)
    ((with-temporary-gensym-float-creation compile-increment
       (< (phrase-number-value parse-result) minimum-simulation-time-increment))
     (values
       bad-phrase
       (tformat-text-string "Time increment is too small;  must be at least ~f seconds"
	 minimum-simulation-time-increment)))
    (t parse-result)))

(define-category-evaluator-interface (simulation-time-increment?
				       :access read-write)
    (or (no-item) number)
  ((set-form (evaluation-value))
   (if evaluation-value
       (if (evaluation-float-p evaluation-value)
	   (evaluation-quantity-to-phrase-quantity evaluation-value)
	   evaluation-value)
       'none))
  ((get-form (slot-value))
   (if slot-value
       (if (managed-float-p slot-value)
	   (copy-managed-float-into-evaluation-float slot-value)
	   slot-value)
       nil)))

(define-category-evaluator-interface (simulation-time-increment
				       :access read-write)
    number
  ((set-form (evaluation-value))
   (if (evaluation-float-p evaluation-value)
       (evaluation-quantity-to-phrase-quantity evaluation-value)
       evaluation-value))
  ((get-form (slot-value))
   (if (managed-float-p slot-value)
       (copy-managed-float-into-evaluation-float slot-value)
       slot-value)))

(def-slot-value-compiler simulation-time-increment (parse-result)
  (cond 
    ((with-temporary-gensym-float-creation compile-increment
       (< (phrase-number-value parse-result) minimum-simulation-time-increment))
     (values
       bad-phrase
       (tformat-text-string "Time increment is too small;  must be at least ~f seconds"
	 minimum-simulation-time-increment)))
    (t parse-result)))


(def-slot-value-writer simulation-time-increment? (simulation-time-increment?)
  (cond
    ((slot-value-float-p simulation-time-increment?) 
     (with-temporary-gensym-float-creation write-increment
       (tformat "~f" (slot-value-float-value simulation-time-increment?)))
     (print-second-or-seconds simulation-time-increment?))
    (simulation-time-increment? 
     (twrite simulation-time-increment?)
     (print-second-or-seconds simulation-time-increment?))
    (t (twrite "none"))))


(def-slot-value-writer simulation-time-increment (simulation-time-increment)
  (cond
    ((slot-value-float-p simulation-time-increment)
     (with-temporary-gensym-float-creation write-increment
       (tformat "~f" (slot-value-float-value simulation-time-increment)))
     (print-second-or-seconds simulation-time-increment))
    (t
     (twrite simulation-time-increment)
     (print-second-or-seconds simulation-time-increment))))


(defun print-second-or-seconds (time-increment)
  (with-temporary-gensym-float-creation print-second
    (if (= (slot-value-number-value time-increment) 1)
	(twrite " second")
	(twrite " seconds"))))



(add-grammar-rules
  '((integration-algorithm-specification 'Euler)
    (integration-algorithm-specification
      ('Fourth-order 'Runge-Kutta) rk4)
    (simulation-control-specification synchronization-mode (1))
    (simulation-control-specification 
      (synchronization-mode without-time-increment) (1 2))
    (simulation-control-specification 
      (synchronization-mode without-waiting-for-external) (1 nil 2))
    (simulation-control-specification 
      (synchronization-mode without-time-increment without-waiting-for-external)
      (1 2 3))
    (synchronization-mode
      ('run 'synchronously) synchronously)
    (synchronization-mode
      ('run 'as 'fast 'as 'possible) as-fast-as-possible)
    (without-time-increment
      ('\, 'without 'incrementing 'simulation 'time) t)
    (without-waiting-for-external
      ('\, 'without 'waiting 'for 'simulation 'procedure 'or 'gspan
       'external 'simulation 'cycle 'to 'finish) t)))

(def-slot-value-writer integration-algorithm-specification 
		       (integration-algorithm-specification)
  (if (eq integration-algorithm-specification 'euler)
      (twrite "Euler")
      (twrite "Fourth-order Runge-Kutta")))

(define-category-evaluator-interface (integration-algorithm-specification
				      :access read-write)
    (member euler runga-kutta-4)
  ((set-form (evaluation-value))
   (case evaluation-value
     (euler 'Euler)
     (runga-kutta-4 'rk4)))
  ((get-form (slot-value))
   (case slot-value
     (Euler 'euler)
     (rk4 'runga-kutta-4))))

(def-slot-value-writer simulation-control-specification 
		       (simulation-control-specification)
  (if (eq (car simulation-control-specification) 'synchronously)
      (twrite "run synchronously")
      (twrite "run as fast as possible"))
  (when (second simulation-control-specification)
    (twrite ", without incrementing simulation time"))
  (when (third simulation-control-specification)
    (twrite ", without waiting for simulation procedure or gspan external simulation cycle to finish")))

(def-slot-value-compiler simulation-control-specification 
			 (parse-result model-definition)
  (if (or (frame-of-class-p model-definition 'class-definition)
	  (not (model-running-or-paused? model-definition)))
      parse-result
      (values
	bad-phrase
	(copy-constant-wide-string #w"Simulation control specifications cannot be edited while the model is running or paused."))))

(define-category-evaluator-interface (simulation-control-specification
				      :access read-write)
    (structure simulation-control-specification-spec
	       ((synchronization-mode (member run-synchronously run-as-fast-as-possible))
		(without-incrementing-simulation-time truth-value)
		(without-waiting-for-external-simulation-cycle truth-value))
	       (and synchronization-mode))
  ((set-form (evaluation-value))
   (phrase-list (case (evaluation-structure-slot evaluation-value 'synchronization-mode)
		  (run-synchronously 'synchronously)
		  (run-as-fast-as-possible 'as-fast-as-possible))
		(let ((value (evaluation-structure-slot evaluation-value 'without-incrementing-simulation-time)))
		  (and (evaluation-truth-value-p value)
		       (evaluation-boolean-is-true-p value)))
		(let ((value (evaluation-structure-slot evaluation-value 'without-waiting-for-external-simulation-cycle)))
		  (and (evaluation-truth-value-p value)
		       (evaluation-boolean-is-true-p value)))))
  ((get-form (slot-value))
   (allocate-evaluation-structure
    (nconc (eval-list 'synchronization-mode
		      (if (eq (car slot-value) 'synchronously)
			  'run-synchronously
			  'run-as-fast-as-possible))
	   (when (second slot-value)
	     (eval-list 'without-incrementing-simulation-time
			(make-evaluation-boolean-value t)))
	   (when (third slot-value)
	     (eval-list 'without-waiting-for-external-simulation-cycle
			(make-evaluation-boolean-value t)))))))



(add-grammar-rules
  '((positive-integer integer)))


;;; The slot value compiler for positive-integer expects parse-result to be
;;; a fixnum integer.  If parse-result is positive, it is returned; otherwise,
;;; bad-phrase and a text string explaining the problem are returned.

(def-slot-value-compiler positive-integer (parse-result)
  (if (>f parse-result 0)
      parse-result
      (values
	bad-phrase
	(copy-constant-wide-string #w"This value must be a positive integer."))))


(def-slot-value-writer positive-integer (n)
  (twrite n))




(add-grammar-rules
  '((positive-integer? 'none)
    (positive-integer? integer)))



;;; The slot value compiler for positive-integer? expects parse-result to be
;;; either the symbol NONE or a fixnum integer.  If parse-result is NONE, nil
;;; is returned; if parse-result is positive, it is returned; otherwise,
;;; bad-phrase and a text string explaining the problem are returned.

(def-slot-value-compiler positive-integer? (parse-result)
  (cond ((eq parse-result 'none) nil)
	((>f parse-result 0) parse-result)
	(t (values bad-phrase
		   (copy-constant-wide-string #w"This value must be a positive integer.")))))


(def-slot-value-compiler read-only-positive-integer? (parse-result)
  (cond ((eq parse-result 'none) nil)
	((>f parse-result 0) parse-result)
	(t (values bad-phrase
		   (copy-constant-wide-string #w"This value must be a positive integer.")))))

(def-slot-value-writer positive-integer? (n)
  (if (null n)
      (twrite 'none)
      (twrite n)))




(add-grammar-rules
  '((priority integer)))


;;; The slot value compiler for priority expects parse-result to be
;;; a fixnum integer.  If parse-result is between 1 and 10, inclusive, then
;;; it is returned; otherwise, bad-phrase and a text string explaining the
;;; problem are returned.

(def-slot-value-compiler priority (parse-result)
  (if (<=f 1 parse-result 10)
      parse-result
      (values
	bad-phrase
	(copy-constant-wide-string #w"A priority must be an integer from 1 through 10."))))

(def-slot-value-writer priority (n)
  (twrite n))

(define-category-evaluator-interface (priority
				       :access read-write)
    (member 1 2 3 4 5 6 7 8 9 10)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))






(add-grammar-rules
  '((non-negative-integer integer)
    (non-negative-number number)))


;;; The slot value compiler for non-negative-integer expects parse-result to be
;;; a fixnum integer.  If parse-result is negative, then it is returned;
;;; otherwise, bad-phrase and a text string explaining the problem are returned.

(def-slot-value-compiler non-negative-integer (parse-result)
  (if (>=f parse-result 0)
      parse-result
      (values
	bad-phrase
	(copy-constant-wide-string #w"This value must be a non-negative integer."))))

(def-slot-value-writer non-negative-integer (n)
  (twrite n))

(def-slot-value-compiler non-negative-number (parse-result)
  (if (or (and (fixnump parse-result)
	       (>=f parse-result 0))
	  (and (phrase-float-p parse-result)
	       (>=e (phrase-float-value parse-result) 0.0)))
      parse-result
      (values
	bad-phrase
	(copy-constant-wide-string #w"This value must be a non-negative number."))))

(def-slot-value-writer non-negative-number (number)
  (print-constant number 'number))






;;;; Formulas




;;; An instance-formula is a formula for a particular variable. It is a text
;;; slot of the variable. The slot-value-compiler should (1) fill out references
;;; to "the" that have antecedent within the text, (2) reject formulas that are
;;; generic or have free references, and (3) possibly look for type consistency
;;; with the data type of the variable. This should be done when the data type
;;; changes also.

(add-grammar-rules
  '((instance-formula unique-expression)
    (instance-formula 'none)))

(def-slot-value-compiler instance-formula (parse-result variable)
  (let ((compiler-result?
	  (compile-instance-formula parse-result variable)))
    (if (eq compiler-result? bad-phrase)
	(values
	  bad-phrase
	  (copy-text-string
	    "This formula cannot be computed for this variable."))
	compiler-result?)))


(defun compile-instance-formula (parse-result variable)
  (let* ((*current-computation-frame* variable)
	 (current-computation-component-particulars nil)
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame variable)
	 (cell-array? (cell-array variable))
	 (expression-cell?
	   (when cell-array?
	     (managed-svref (g2-cell-array-managed-array cell-array?) 0)))
	 (expression?
	   (if (eq parse-result 'none)
	       nil
	       parse-result)))
    (without-consistency-analysis (variable)
      (cond (expression?
	     (when (not (and cell-array? expression-cell?))
	       (setq cell-array? (make-frame 'g2-cell-array))
	       (change-slot-value variable 'cell-array cell-array?)
	       (make-empty-expression-cell cell-array?)
	       (setf expression-cell?
		     (managed-svref (g2-cell-array-managed-array cell-array?) 0))
	       (when (runnable-p variable)
		 (activate-g2-cell-array cell-array?)))
	     (with-part-description ((get-default-computation-style-of-class))
	       (let ((formula-type
		       (type-specification-held-in-variable-or-parameter
			 variable)))
		 (register-expression-cell-during-compilation
		   cell-array? 0 t expression? formula-type)
		 (cond ((expression-cell-able-to-compute-p expression-cell?)
			(update-frame-status variable nil nil)
			t)
		       (t
			bad-phrase)))))
	    (t
	     ;; When there is no compiled expression, get rid of the cell array
	     ;; and any frame notes for compiler errors.
	     (when cell-array?
	       (when (runnable-p variable)
		 (deactivate-g2-cell-array cell-array?))
	       (change-slot-value variable 'cell-array nil))
	     (remove-compiler-error-and-warning-frame-notes)
	     (update-frame-status variable nil nil)
	     nil)))))

(def-slot-value-writer-as-existing-function
  instance-formula write-symbol-from-slot)

;; The above writer is expected to only be called when the slot is nil;
;; otherwise, the slot would be text, and there would be no need to call a
;; writer.  (MHD 3/7/91)



(add-grammar-rules
  '((logical-instance-formula unique-logical-expression)
    (logical-instance-formula 'none)))

(def-slot-value-compiler logical-instance-formula (parse-result variable)
  (let ((compiler-result?
	  (compile-instance-formula parse-result variable)))
    (if (eq compiler-result? bad-phrase)
	(values
	  bad-phrase
	  (copy-text-string
	    "This formula cannot be computed for this variable."))
	compiler-result?)))

(def-slot-value-writer-as-existing-function
  logical-instance-formula write-symbol-from-slot)

;; The above writer is expected to only be called when the slot is nil;
;; otherwise, the slot would be text, and there would be no need to call a
;; writer.  (MHD 3/7/91)


;;; A generic formula is a statement specifying how an attribute of some class 
;;; is computed.

;;; added class-qualified-name grammar -rdf, 3/10/94

(add-grammar-rules
  '((generic-formula ('let left-side-of-formula '= unique-expression)
		     (2 4) translate-generic-formula)
    (generic-formula ('let left-side-of-formula '= unique-logical-expression)
		     (2 4) translate-generic-formula)

    (left-side-of-formula
      ('the attribute-name 'of 'any class) (2 5))
    (left-side-of-formula
      ('the attribute-name local-name 'of 'any class) ((2 . 3) 6))
    (left-side-of-formula
      ('the attribute-name 'of 'any class local-name) (2 (5 . 6)))
    (left-side-of-formula
      ('the attribute-name local-name 'of 'any class local-name)
     ((2 . 3) (6 . 7)))
    
    (left-side-of-formula
      ('the class '\:\: attribute-name 'of 'any class) ((class-qualified-name 2  4) 7))
    (left-side-of-formula
      ('the  class '\:\:  attribute-name local-name 'of 'any class)
     (((class-qualified-name 2 4) . 5) 8))
    (left-side-of-formula
      ('the class '\:\: attribute-name 'of 'any class local-name)
     ((class-qualified-name 2  4) (7 . 8)))
    (left-side-of-formula
      ('the class '\:\: attribute-name local-name 'of 'any class local-name)
     (((class-qualified-name 2  4) . 5) (8 . 9)))
    ))

(defun translate-generic-formula (phrase)
  (let ((left-side-of-formula (car phrase))
	(rest-of-formula (cdr phrase)))
    (phrase-cons
      (first left-side-of-formula)
      (phrase-cons
	(second left-side-of-formula)
	rest-of-formula))))


(defun is-generic-forumula-executable? (generic-formula)
  (let* ((cell-array? (cell-array generic-formula))
	 (cell-array-index
	   (expression-cell-element-for-generic-formula generic-formula))
	 (expression-cell?
	   (when cell-array?
	     (managed-svref (g2-cell-array-managed-array cell-array?)
			    cell-array-index))))
    (when expression-cell?
      (expression-cell-able-to-compute-p expression-cell?))))


;; add support for class-qualified-names -rdf, 3/10/94

(def-slot-value-compiler generic-formula (parse-result generic-formula)
  (let* ((*current-computation-frame* generic-formula)
	 (current-computation-component-particulars nil)
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame generic-formula)
	 (cell-array (cell-array generic-formula))
	 (cell-array-index
	   (expression-cell-element-for-generic-formula generic-formula))
	 (expression-cell
	   (when cell-array
	     (managed-svref (g2-cell-array-managed-array cell-array)
			    cell-array-index)))
	 (attribute (first parse-result))
	 (simple-attribute-role (simple-role-of-role attribute))
	 (attribute-class-qualifier (class-qualifier simple-attribute-role))
	 (domain (second parse-result))
	 (class-name (atomic-naming-element-of-role domain))
	 (raw-body (third parse-result))
	 (argument-and-type-list
	   (phrase-list
	     (phrase-list
	       class-name
	       (make-class-type-specification class-name)))))
    (when (not (and cell-array expression-cell))
      (setq cell-array (make-frame 'g2-cell-array))
      (change-slot-value generic-formula 'cell-array cell-array)
      (make-empty-expression-cell cell-array)
      (setf expression-cell
	    (managed-svref (g2-cell-array-managed-array cell-array)
			   cell-array-index))
      (when (runnable-p generic-formula)
	(activate-g2-cell-array cell-array)))
    (without-consistency-analysis (generic-formula)
      (cond (raw-body
	     (with-part-description ((get-default-computation-style-of-class))
	       (register-expression-cell-during-compilation
		 cell-array cell-array-index t
		 (phrase-list 'g2-lambda argument-and-type-list raw-body)
		 '(or datum (unknown-datum))
		 domain attribute)
	       ;;changed to add class qualifier here as required -rdf, 3/8/94
	       (cond ((and (expression-cell-able-to-compute-p expression-cell)
			   attribute-class-qualifier)
		      (phrase-list
			(unqualified-name simple-attribute-role)
			(atomic-naming-element-of-role domain)
			attribute-class-qualifier))
		     ((expression-cell-able-to-compute-p expression-cell)
		      (phrase-list
			(unqualified-name simple-attribute-role)
			(atomic-naming-element-of-role domain)))
		     (t
		      (update-frame-status generic-formula 'bad nil)
		      nil))))
	    (t
	     (when (runnable-p generic-formula)
	       (deactivate-g2-cell-array cell-array))
	     (change-slot-value generic-formula 'cell-array nil)
	     (update-frame-status generic-formula 'bad nil)
	     nil)))))




;; Note that in the compiler for generic-formula above, the thing labeled domain
;; is not really a domain, but is instead the role of the domain.  The use of
;; atomic-naming-element-of-role is OK on this, but the local variable names
;; here are misleading.  -jra 5/31/89



(defun translate-generic-simulation-formula (phrase)
  (let ((left-side-of-formula (car phrase))
	(rest-of-formula (cdr phrase)))
    (nconc
      (phrase-cons
	(get-first-role-of-left-side-designation left-side-of-formula)
	(phrase-cons
	  (get-main-class-or-item-of-left-side-designation left-side-of-formula)
	  rest-of-formula))
      (phrase-list
	(copy-tree-using-phrase-conses left-side-of-formula)))))

(defun get-first-role-of-left-side-designation (left-side-designation)
  (when (and (consp left-side-designation)
	     (eq (car left-side-designation) 'the))
    (second left-side-designation)))

(defun get-main-class-or-item-of-left-side-designation (left-side-designation)
  (loop as current-designation = left-side-designation
			       then (third current-designation)
	do
    (cond
      ((symbolp current-designation)
       (return (phrase-list 'item current-designation)))
      ((null (third current-designation))
       (return (second current-designation))))))

;;; added class-qualified-name grammar -rdf, 3/10/94

(add-grammar-rules
  '((generic-simulation-formula state-variable-generic-simulation-formula)
    (generic-simulation-formula dependent-variable-generic-simulation-formula)

    (dependent-variable-generic-simulation-formula
      (left-side-of-simulation-formula
       '= generic-simulation-expression) (1 3 dependent nil nil)
      translate-generic-simulation-formula)
    (dependent-variable-generic-simulation-formula
      (left-side-of-simulation-formula
       '= simulation-literal) (1 3 dependent nil nil)
      translate-generic-simulation-formula)
    (dependent-variable-generic-simulation-formula
      (left-side-of-simulation-formula 
	'= generic-simulation-expression
	'\, 'with 'time 'increment simulation-time-increment)
      (1 3 dependent nil 8)
      translate-generic-simulation-formula)

    (state-variable-generic-simulation-formula
      ('state 'variable '\: 'd '\/ 'dt 
       '\( left-side-of-simulation-formula '\)
       '= generic-simulation-expression 
       state-variable-initial-value)
      (8 11 continuous-state . 12)
      translate-generic-simulation-formula)
    (state-variable-generic-simulation-formula
      ('state 'variable '\: 'next 'value 'of
       left-side-of-simulation-formula
       '= generic-simulation-expression 
       state-variable-initial-value)
      (7 9 discrete-state . 10)
      translate-generic-simulation-formula)

    (state-variable-initial-value
      ('\, 'with 'initial 'value simulation-initial-value-expression) (5 nil))
    (state-variable-initial-value
      ('\, 'with 'initial 'value simulation-initial-value-expression '\,
       'and 'with 'time 'increment simulation-time-increment)
      (5 11))

    (simulation-initial-value-expression simulation-expression)
    (simulation-initial-value-expression 
      ('the 'current 'parameter 'value) (current-parameter-value))

    (generic-simulation-expression simulation-expression)
;    (generic-simulation-expression 
;      ('the 'first 'of 'the 'following 'expressions 'that 'has 'a 'value '\:
;       list-of-generic-simulation-expressions) 
;      (first-successful-evaluation 12) append-listed-expressions-to-operator)

    (list-of-generic-simulation-expressions simulation-expression)
    (list-of-generic-simulation-expressions 
      (simulation-expression '\, list-of-generic-simulation-expressions)
      (2 1 3) simplify-associative-operation)

    (left-side-of-simulation-formula item-name)
    (left-side-of-simulation-formula
      ('the constant-class-phrase-role left-side-of-simulation-formula))
    (left-side-of-simulation-formula
      ('the left-side-class-phrase-role left-side-of-simulation-formula))
    (left-side-of-simulation-formula
      ('the left-side-class-phrase-role left-side-class-designation))
    (left-side-class-designation
      ('any class))
    (left-side-class-designation ('any class local-name) (any (2 . 3)))

    (left-side-class-phrase-role 
      (class constant-preposition) (1 2) translate-role-and-preposition)
;    (left-side-class-phrase-role 
;      (attribute-name constant-preposition) (1 2) translate-role-and-preposition)
    (left-side-class-phrase-role 
      (attribute-name 'of ) (1 2) translate-role-and-preposition)
    (left-side-class-phrase-role 
      (class '\:\: attribute-name 'of )
     ((class-qualified-name 1 3) 4) translate-role-and-preposition)
    (left-side-class-phrase-role 
      (class local-name constant-preposition) 
      (1 2 3) translate-role-local-name-and-preposition)
;    (left-side-class-phrase-role 
;      (attribute-name local-name constant-preposition) 
;      (1 2 3) translate-role-local-name-and-preposition)
;    (left-side-class-phrase-role 
;      (class '\:\: attribute-name local-name constant-preposition) 
;      ((class-qualified-name 1 3) 4 5) translate-role-local-name-and-preposition)
    (left-side-class-phrase-role 
      (attribute-name local-name 'of) 
      (1 2 3) translate-role-local-name-and-preposition)
    (left-side-class-phrase-role 
      (class '\:\: attribute-name local-name 'of) 
      ((class-qualified-name 1 3) 4 5) translate-role-local-name-and-preposition)
    ))

;; A unique-expression will always return one result.  There is no iteration
;; except for within antecedents of embedded ifs, and there is no collection.
;; Unique-expressions are useful for all simulation and inference engine formulas
;; as well as for displays.

;; Currently, unique-expression is used for displays but simulation-expression,
;; which has no quantification at all is used for the simulator since the simulator
;; does not yet have evaluators for there-exists or for-all.  -agh 1/14/88

#+unused
(defun append-listed-expressions-to-operator (operator-and-list)
  (if (and (consp (second operator-and-list))
	   (eq (car (second operator-and-list)) '\,))
      (phrase-cons (first operator-and-list)
		   (cdr (second operator-and-list)))
      operator-and-list))


;;; The slot value compiler for generic-simulation-formula expects parse-result
;;; to be of the form
;;; 
;;;    (attribute-name class simulation-expression simulation-category
;;;     initial-value? time-increment?)
;;; 
;;; Simulation-expression, and initial-value? (if any) are compiled using
;;; compile-expression.  If there are no problems, a value in the above form
;;; with the compiled versions of simulation-expression and initial-value?
;;; is returned.  Note that the simulation category and initial value 
;;; information is not removed;  it is used by the slot putter.  

(def-slot-value-compiler generic-simulation-formula 
			 (parse-result generic-simulation-formula)
  (let ((*current-computation-frame* generic-simulation-formula))
    (cond
      ((with-temporary-gensym-float-creation generic-simulation-formula
	 (let ((time-increment?
		 (phrase-number-value 
		   (simulation-time-increment-given-translation parse-result))))
	   (and time-increment?
		(< time-increment? minimum-simulation-time-increment))))
       (values
	 bad-phrase
	 (tformat-text-string "Time increment is too small;  must be at least ~f seconds"
			      minimum-simulation-time-increment)))
      (t
       (update-frame-status generic-simulation-formula nil nil)
       ;; Generic-simulation-formula starts out O.K.  This can be changed by
       ;; the compile-generic-simulation-formula, or later, the slot putter
       ;; for box-translation-and-text of the generic simulation formula
       ;; (see install).
       
       (let* ((simulation-expression 
		(compiled-simulation-formula-given-translation parse-result))
	      (initial-value-expression? 
		(simulation-initial-value-given-translation parse-result))
	      (simulation-class-or-item
		(simulation-class-or-item-without-local-name
		  (simulation-class-or-item-given-translation parse-result)))
	      (compiled-simulation-expression 
		(compile-generic-simulation-formula
		  simulation-expression simulation-class-or-item
		  (left-side-of-simulation-formula-given-translation parse-result) 
		  generic-simulation-formula nil))
	      (compiled-initial-value-expression? nil))
	 
	 (cond
	   ((null compiled-simulation-expression)
	    (setf (compiled-simulation-formula-given-translation parse-result) nil)
	    (setf (simulation-initial-value-given-translation parse-result) nil)
	    (strip-out-local-names-if-any parse-result)
	    parse-result)
	   (t 
	    (setq compiled-initial-value-expression?
		  (cond
		    ((compile-initial-value-expression? initial-value-expression?)
		     (compile-generic-simulation-formula
		       initial-value-expression? simulation-class-or-item
		       (left-side-of-simulation-formula-given-translation parse-result)
		       generic-simulation-formula t))
		    (t initial-value-expression?)))
	    (strip-out-local-names-if-any parse-result)
	    (cond
	      ((and initial-value-expression? (not compiled-initial-value-expression?))
	       (setf (compiled-simulation-formula-given-translation parse-result) nil)
	       (setf (simulation-initial-value-given-translation parse-result) nil)
	       parse-result)
	      (t
	       (setf (compiled-simulation-formula-given-translation parse-result)
		     compiled-simulation-expression)
	       (setf (simulation-initial-value-given-translation parse-result)
		     compiled-initial-value-expression?)

	       (cond 
		 ((compile-initial-value-expression? compiled-initial-value-expression?)
		  ;; this is to prevent consistency analysis from hosing the compiliation -rdf, 4/24/95
		  (change-slot-value
		    generic-simulation-formula
		    'generic-simulation-formula-byte-code-body
		    nil)
		  (let* ((current-computation-component-particulars
			   '(simulation-initial-value *current-computation-frame*))
			 (byte-code-body 
			   (if (symbolp simulation-class-or-item)       ; if class
			       (compile-simulation-formula-for-stack
				 (simulation-initial-value-given-translation 
				   parse-result)
				 simulation-class-or-item simulation-class-or-item
				 t)
			       (compile-simulation-formula-for-stack
				 (simulation-initial-value-given-translation 
				   parse-result)
				 nil nil t))))
		    (change-slot-value
		      generic-simulation-formula
		      'generic-simulation-initial-value-byte-code-body
		      byte-code-body)))
		 (t
		  (change-slot-value
		    generic-simulation-formula
		    'generic-simulation-initial-value-byte-code-body
		    nil)))
	       (let ((byte-code-body 
		       (if (symbolp simulation-class-or-item)  ; if class
			   (compile-simulation-formula-for-stack
			     (compiled-simulation-formula-given-translation 
			       parse-result)
			     simulation-class-or-item simulation-class-or-item
			     nil)
			   (compile-simulation-formula-for-stack
			     (compiled-simulation-formula-given-translation 
			       parse-result)
			 nil nil nil))))
		 (change-slot-value
		   generic-simulation-formula
		   'generic-simulation-formula-byte-code-body
		   byte-code-body))
	       parse-result
	       )))))))

))

(defun use-current-parameter-value? (initial-value-expression?)
  (and (consp initial-value-expression?)
       (eq (car initial-value-expression?) 'current-parameter-value)))

(defun compile-initial-value-expression? (initial-value-expression?)
  (and initial-value-expression?
       (not (use-current-parameter-value? 
	      initial-value-expression?))))

(defun strip-out-local-names-if-any (translation)
  (setf (simulation-role-given-translation translation)
	(atomic-naming-element-of-role 
	  (simulation-role-given-translation translation)))
  (setf (simulation-class-or-item-given-translation translation)
	(simulation-class-or-item-without-local-name
	  (simulation-class-or-item-given-translation translation)))
  (loop as current-designation 
	   = (left-side-of-simulation-formula-given-translation 
	       translation)
	   then (third current-designation)
	until (not (consp current-designation))
	do
    (setf (second current-designation)
	  (simple-role-of-role (second current-designation)))
    (when (eq (car current-designation) 'any)
      (setf (car current-designation) 'the))))

(defun simulation-class-or-item-without-local-name (simulation-class-or-item)
  (if (not (and (consp simulation-class-or-item)
		(eq (car simulation-class-or-item) 'item)))
      (atomic-naming-element-of-role simulation-class-or-item)
      simulation-class-or-item))





;;;; On Using A-or-an vs. Using A or An



;;; A-or-an must be used whenever it is possible to encounter both a and an
;;; as menus for the next legal choice in the editor menus.  'A or 'AN should
;;; be used if and only if only one or the other can ever be encountered.
;;; For example, in the following rules
;;;
;;; (1)     (stub-info-without-style
;;;           (a-or-an connection-class port-name 'located 'at edge integer)
;;;           (3 2 nil 6 7))
;;;         (stub-info-without-style
;;;           (a-or-an connection-class 'located 'at edge integer)
;;;           (nil 2 nil 5 6))
;;;     
;;; (2)     (stub-info-without-style
;;;           (a-or-an direction connection-class port-name 'located 'at edge integer)
;;;           (4 3 2 7 8))
;;;         (stub-info-without-style
;;;           (a-or-an direction connection-class 'located 'at edge integer)
;;;           (nil 3 2 6 7))
;;;
;;; (3)     (direction 'input)
;;;         (direction 'output)
;;;
;;; None of the rules in rule set (2) should start with "a", since it sounds wrong
;;; to say "a input ..." or "a output ...".  However, because the rules in rule set
;;; (3) can cause "a" to appear at the same point during the input of a stub-info-
;;; without-style expression, it is necessary to supply a-or-an for them.  The rationale
;;; is that it is too confusing to users when they see that "a" or "an" are legal
;;; editor menu choices to have clicking on one or the other go down two different
;;; paths in the grammar.
;;;
;;; On the other hand, using a-or-an means that menus cannot be formed that include
;;; just "a" or "an" within a longer grammar phrase.  So it is nice to use just "a"
;;; or just "an" if only those can appear.  Thus, for example, the following rule
;;;
;;;
;;;    (event-literal (designation 'fails 'to 'receive 'a 'value)
;;;		      (fails-to-receive-a-value 1))
;;;
;;; happens to result in an entire menu choice that reads
;;;
;;;    fails to receive a value
;;;
;;; (after, e.g., "whenever xxx ").  But if a-or-an were used instead of 'a,
;;; then the menu would read
;;;
;;;    fails to receive
;;;
;;; and, after selecting this, users would have to click on A or AN in order
;;; to proceed.  That would annoy users.

;; The above was added here by MHD, 1/11/91.  Search in GRAMMAR1 and GRAMMAR2
;; for "(MHD 1/11/91)" for changes that were made today to implement the above
;; guidelines.  (MHD 1/11/91)





;; End File with CR

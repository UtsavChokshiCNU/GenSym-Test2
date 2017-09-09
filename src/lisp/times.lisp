;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TIMES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Lowell B. Hawkinson, Brian Matthews







;;;; Calendar Time Manipulation Functions




;;; This section contains code moved from CLOCKS into this earlier file to avoid
;;; GSI and TW from needing to load the CLOCKS module, which is really about
;;; ticking the clock for the scheduler.  -jra 3/3/94




;;; The parameter `seconds-from-1900-to-1970' contains the float offset used to
;;; convert UNIX format times into Lisp universal times.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant seconds-from-1900-to-1970 2208988800.0))



;;; The macro `get-temporary-universal-time' returns the current universal time,
;;; the same as get-universal-time.  However, if get-universal-time is to be
;;; called within a temporary bignum context, then this form should be called
;;; instead.  This is because some implementations (namely, Symbolics Genera
;;; 7.2, [now an obsolete platform]) cons up state within get-universal-time which
;;; is retained and reused.  If this occurs within a temporary context, it
;;; breaks the clock and crashes the machine.  This macro is safe to call within
;;; a temporary context.

(defmacro get-universal-time-as-double-float ()
  `(unix-time-to-universal-time (gensym-get-unix-time)))




;;; The function `decode-unix-time-as-managed-float' returns six values for the
;;; decoded time represented in the managed float.  Note that this function
;;; returns all fixnums (i.e. ignores any subsecond component to the given time
;;; by taking the floor of the given value).

(defun decode-unix-time-as-managed-float (managed-float)
  (let (seconds minutes hours date months years weekday dstp time-zone)
    (with-temporary-gensym-float-creation decode-unix-time-as-managed-float
      (multiple-value-setq
	  (seconds minutes hours date months years weekday dstp time-zone)
	(gensym-decode-unix-time (managed-float-value managed-float))))
    (values seconds minutes hours date months years weekday dstp time-zone)))





;;; The function `get-unix-time-to-the-second-as-managed-float' returns a
;;; managed-float which contains the current UNIX format time, accurate only to
;;; the second.

(defun-simple get-unix-time-to-the-second-as-managed-float ()
  (with-temporary-gensym-float-creation
      get-unix-time-to-the-second-as-managed-float
    (allocate-managed-float
      (ffloore-first (gensym-get-unix-time)))))




;;; The macros `universal-time-to-unix-time' and `unix-time-to-universal-time'
;;; are used to convert timestamps in the UNIX time format (seconds since
;;; Midnight, January 1, 1970 UTC) to timestamps in the universal time format
;;; (seconds since Midnight, January 1, 1900 UTC) and back.  These macros take
;;; and return gensym-floats.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro universal-time-to-unix-time (universal-time-gensym-float)
  `(-e ,universal-time-gensym-float seconds-from-1900-to-1970))

(defmacro unix-time-to-universal-time (unix-time-gensym-float)
  `(+e ,unix-time-gensym-float seconds-from-1900-to-1970))
)





;;;; Universal Time and Date Encoders and Decoders



;;; A `universal-date' is a fixnum which specifies a day, taking January 1, 1900
;;; as day 0.

;;; Encode-universal-date take a day, month and year (as numbers) and encodes
;;; the date as a normalized-date.  It uses the Gregorian calendar, and is valid
;;; from 1 AD through 2399 AD.

;;; It is fast, and uses only fixnums.

;;; Leap-year-p defines the Gregorian calendar leap years within the given range.

(defun leap-year-p (year)
  (and (=f 0 (modf-positive year 4))
       (or (/=f 0 (modf-positive year 100))
	   (=f 0 (modf-positive year 400)))))

(defconstant days-before-this-month
	'(0 31 59 90 120 151 181 212 243 273 304 334 365))

(defun valid-date-for-month-p (day month year)
  (fixnum-case month
    ((2) (if (leap-year-p year)
	     (<=f 1 day 29)
	     (<=f 1 day 28)))
    ((4 6 9 11) (<=f 1 day 30))
    (otherwise (<=f 1 day 31))))

(defun encode-universal-date (day month year)
  (let ((normalized-year (-f year 1900)))
    (+f
      ;; Component for years, without leap year correction
      (*f normalized-year 365)
      ;; Leap year correction for years between 1900 and this year
      ;; as if every four years was a leap year.
      (floorf (+f normalized-year 3) 4)
      ;; Correction for centenial years.
      (-f (floorf (+f normalized-year 99) 100))
      ;; Correction for every fourth centenial being a leap year.
      (floorf (+f normalized-year 299) 400)
      ;; Days this year before start of this month, ignoring leap year.
      (nth (-f month 1) days-before-this-month)
      ;; Days of this month before this day.
      (-f day 1)
      ;; Correction for leap day if there is one this year,
      ;; and it has already happened.
      (if (and (leap-year-p year)
	       (>f month 2))   ;March or later in a leap-year
	  1 0)
      )))

;(defun compare-two-methods (ud)
;  (let ((ut (* ud 86400)))
;    (multiple-value-bind (sec min hr d m y)
;	(gensym-decode-universal-time ut 0)
;      (encode-universal-date d m y))))
	 
;(defun compare-over-range (d1 d2)
;  (loop for day from d1 to d2 doing
;    (unless (= day (compare-two-methods day))
;      (cerror "foo" "bar"))))

;(defun decode-ut-speed (n)
;  (loop for i from 1 to n do
;    (encode-universal-date 12 4 2034)))




;;; Decode-universal-date is the inverse of encode-universal-date, It returns
;;; three values, (day month year).

(defun decode-universal-date (universal-date)
  (declare (eliminate-for-gsi))
  (loop named sue with normalized-year =
		    (floorf (* universal-date 4) 1461)
	for begin-this-year = (encode-universal-date 1 1 (+f normalized-year 1900))
	for begin-next-year = (encode-universal-date
				1 1 (+f normalized-year 1901))
	until (and (>=f universal-date begin-this-year)
		   (<f universal-date begin-next-year)) doing
    (setq normalized-year
	  (+f normalized-year (if (<f universal-date begin-next-year) -1 1)))
    
	finally
	  (loop with days-into-year = (-f universal-date begin-this-year)
		with day
		with year = (+f normalized-year 1900)
		for month from 1
		for days-before-first-last-month = nil then days-before-first-this-month
		for days-before-first-this-month in days-before-this-month
		for days-before-first-next-month in (cdr days-before-this-month)
		until (>f days-before-first-next-month days-into-year)
		finally 
		  (setq day (-f days-into-year days-before-first-this-month -1))
		  (when (and (leap-year-p year)
			     (>f month 2))
		    (cond
		      ((>f day 1)
		       (setq day (-f day 1)))
		      ((=f month 3)
		       (setq month (-f month 1))
		       (setq day 29))		       
		      (t (setq month (-f month 1))
			 (setq day
			       (-f days-before-first-this-month
				   days-before-first-last-month)))))
		  (return-from sue (values day month year)))))




;;; Get-universal-date gets the universal-date by reading the current
;;; u.t. and dividing by seconds-per-day. 

;(defun get-universal-date ()
;  (with-temporary-bignum-creation
;    (floor (get-temporary-universal-time) seconds-per-day)))

;; The simpler version above is incorrect because it gives the correct
;; date for time zone 0. This method, which is slower takes advantage of
;; the time zone smarts of get-universal-time, and also adds in the ad hoc
;; correction called clock-adjustment-in-minutes. Compare with
;; get-decoded-real-time.

(defun get-universal-date ()
  (multiple-value-bind (second minute hour day month year)
      (get-decoded-real-time)
    (declare (ignore second minute hour))
    (encode-universal-date day month year)))

;(defun decode-and-encode (ud)
;  (multiple-value-bind (d m y)
;      (decode-universal-date ud)
;    (let ((ud2 (encode-universal-date d m y)))
;      (if (/= ud ud2)
;	  (cerror "no" "no"))
;      )))


;(defun decode-and-encode-range (x y)
;  (loop for i from x to y do
;    (decode-and-encode i)))


;(defun time-decode-universal-date (n)
;  (loop for i from 1 to n do
;	  (decode-universal-date n)))

;; Decode-universal-date timed at 180 u-sec on Tx
;; Encode-universal-date timed at 47 u-sec in Tx

(defun get-current-year ()
  (multiple-value-bind (second minute hour day month year)
      (get-decoded-real-time)
    (declare (ignore second minute hour day month))
    year))



(defconstant seconds-per-day 86400)





;;;; Gensym-encode-unix-time and Friends 




(defvar unix-time-offset-was-computed? nil)

(defvar unix-time-offset-for-encoding nil) ; thread-local?




;;; Declaration:     ENCODE-UNIX-DATE (DAY MONTH YEAR)
;;; Type:            lisp function
;;; Purpose:         transform three fixnums representing day, month and year, into
;;;                  a fixnum unix-time value.
;;; Return behavior: returns a fixnum giving the number of days from
;;;                  1 January 1970 UTC (GMT) until day, month, year.
;;; Users:           gensym-encode-unix-time
;;; Prerequisites:   DAY, MONTH and YEAR must be fixnums, and must represent a valid
;;;                  date.
;;; Side effects:    none
;;; Notes:           

(defun-simple encode-unix-date (day month year)
  (let ((normalized-year (-f year 1900))) ; the code below depends on normalized-year 
    (+f
      ;; correction for unix time, subtract off days up to 1970
      (-f 25567)			;value obtained from (encode-universal-date 1 1 1970)

      ;; Component for years, without leap year correction
      (*f normalized-year 365)
      ;; Leap year correction for years between 1900 and this year
      ;; as if every four years was a leap year.
      (floorf (+f normalized-year 3) 4)
      ;; Correction for centenial years.
      (-f (floorf (+f normalized-year 99) 100))
      ;; Correction for every fourth centenial being a leap year.
      (floorf (+f normalized-year 299) 400)
      ;; Days this year before start of this month, ignoring leap year.
      (nth (-f month 1) days-before-this-month)
      ;; Days of this month before this day.
      (-f day 1)
      ;; Correction for leap day if there is one this year,
      ;; and it has already happened.
      (if (and (leap-year-p year)
               (>f month 2))   ;March or later in a leap-year
          1 0)
      )))




;;; The macro encode-unix-time-using-inferred-offset is an internal of
;;; gensym-encode-unix-time and is only used in cases where the C implementation
;;; of encoding has returned a -1, indicating failure.  This operation uses the
;;; decode operation (in compute-unix-time-offset) to determine what the machine
;;; thinks the current timezone and daylight savings time offsets accumulate to,
;;; and then blindly uses that offset to mimic what the encoder was supposed to
;;; do.  This mechanism is built on the assumption (born out through our past
;;; experience) that there are fewer bugs in the decoders than in the encoders,
;;; so we fall back on them when the going gets tough.  -jra 11/29/94

;;; Notes: this function calls compute-unix-time-offset, which in turn calls
;;; encode-unix-time-using-inferred-offset again.  The global flag
;;; unix-time-offset-was-computed? is used to inhibit the inner invokation from
;;; calling compute-unix- time-offset again, and so recursing infinitely.

;;; This macro returns a gensym-float representing the seconds since midnight
;;; January 1, 1970 UTC for the given calendar time.

(defmacro encode-unix-time-using-inferred-offset
    (second minute hour day month year)
  `(progn
     ;; The offset computation is called once from here,
     ;;  if necessary.
     (unless unix-time-offset-was-computed?
       (compute-unix-time-offset))
     (+e (coerce-fixnum-to-gensym-float (+f ,second (*f ,minute 60) (*f ,hour 3600)))
	 (*e (coerce-fixnum-to-gensym-float seconds-per-day)
	     (coerce-fixnum-to-gensym-float
	       (encode-unix-date ,day ,month ,year)))
	 (managed-float-value unix-time-offset-for-encoding))))




;;; Declaration:     compute-unix-time-offset ()
;;; Type:            lisp function
;;; Purpose:         compute the timezone, daylight-savings-time offset for encoding
;;;                  a decoded time to a floating-point unix time.
;;; Return behavior: returns no useful value
;;; Users:           encode-unix-time-using-inferred-offset
;;; Prerequisites:   none
;;; Side effects:    sets global variables: unix-time-offset-was-computed? and
;;;                                         unix-time-offset-for-encoding
;;; Non-local exits: none
;;; Memory impact:   enters a temporary float creation context to do
;;;                   time computations with floating point numbers.
;;; Notes:           none

(defun-simple compute-unix-time-offset ()

  (unless unix-time-offset-was-computed?
    (setf unix-time-offset-for-encoding (allocate-managed-float 0.0d0)))

  ;; we call encode-unix-time-using-inferred-offset from here; it may have called us,
  ;; and this will terminate the recursion.
  (setq unix-time-offset-was-computed? t)

  ;;must be careful here, since encoding yields a time valid only to the second,
  ;;the unix-time should be truncated.  Otherwise, we end up with noise in the
  ;;subsecond part.
  (with-temporary-gensym-float-creation compute-unix-time-offset

    (let ((unix-time (ffloore-first (gensym-get-unix-time)))
	  (old-unix-time-offset (managed-float-value unix-time-offset-for-encoding)))
      (declare (type gensym-float unix-time old-unix-time-offset))
      (multiple-value-bind (second minute hour day month year weekday dst tz)
	  (gensym-decode-unix-time unix-time)
	(declare (ignore weekday dst tz))
	(let ((internally-encoded-time
		(ffloore-first
		  (encode-unix-time-using-inferred-offset second minute hour day month year))))
	  (declare (type gensym-float internally-encoded-time))
	  (mutate-managed-float-value
	    unix-time-offset-for-encoding
	    (+e old-unix-time-offset
		(-e unix-time internally-encoded-time))))))))




;;; The substitution macro `gensym-encode-unix-time' is the preferred interface
;;; to encoding of timestamps in all of our code.  There still exist many
;;; different flavors of encoding operations, but they all end up calling this
;;; one.  It returns a gensym-float giving the unix-time equivalent to the input
;;; time in "broken down form" (see Harbison&Steele).  The arguments are a
;;; calendar represetation of a time in seconds, minutes, hours, day, month, and
;;; year and the return value is a gensym-float encoding the number of seconds
;;; since Midnight, January 1, 1970, UTC.

;; Note that if there is a problem encoding the time, then this code falls back
;; onto our own homegrown encoder, which works around the bugs in some, but is
;; less time-zone and daylight savings time savvy than the build-in system
;; calls used in c-get_encoded_unix_time.  -jra 11/30/94

(def-substitution-macro gensym-encode-unix-time
    (second minute hour day month year)
  (let ((unix-time (c-get_encoded_unix_time second minute hour day month year)))
    (declare (type gensym-float unix-time))
    (-e (if (=e unix-time -1.0d0)
	    (encode-unix-time-after-failure second minute hour day month year)
	    unix-time)
	(coerce-fixnum-to-gensym-float
	  (*f 60 global-daylight-saving-time-adjustment)))))

(defun-simple gensym-encode-unix-time-as-gensym-float (second minute hour day month year)
  (gensym-encode-unix-time second minute hour day month year))

(defun encode-unix-time-after-failure (second minute hour day month year)
  (let* ((time-since-1970-without-consulting-os
	   (encode-unix-time-using-inferred-offset
	     second minute hour day month year))
	 (time-since-1970-inferred-by-os
	   (c-infer_encoded_unix_time time-since-1970-without-consulting-os)))
    (declare (type gensym-float time-since-1970-without-consulting-os
		   time-since-1970-inferred-by-os))
    (if (=e time-since-1970-inferred-by-os -1.0d0)
	time-since-1970-without-consulting-os
	time-since-1970-inferred-by-os)))

(defun-simple gensym-encode-unix-time-as-managed-float
    (second minute hour day month year)
  (with-temporary-gensym-float-creation gensym-encode-unix-time-as-managed-float
    (allocate-managed-float
      (gensym-encode-unix-time second minute hour day month year))))




;;; The function `get-decoded-real-time' gets the current real time from the
;;; system clock and returns the decoded version.  The values it returns are
;;; seconds, minutes, hour, date, month, year, day-of-week (Monday is 0),
;;; daylight-savings-time-p, and the time-zone.

(defun get-decoded-real-time ()
  (let (second minute hour date month year day-of-week
	       daylight-savings-time-p time-zone)
    (with-temporary-gensym-float-creation get-decoded-real-time
      (multiple-value-setq (second minute hour date month year day-of-week
				   daylight-savings-time-p time-zone)
	(gensym-decode-unix-time (gensym-get-unix-time))))
    (values second minute hour date month year day-of-week
	    daylight-savings-time-p time-zone)))





;;;; Miscellaneous



;;; `year-at-compilation-time'

;; We don't call decode-universal-time or get-universal-time at runtime, instead
;; relying on our equivalents, gensym-decode-unix-time and gensym-get-unix-time,
;; which call into C.  But this is hardly run-time; being a defvar is enough,
;; and the read-time evaluation makes it even more obvious.  -jv, 1/2/04

(defvar year-at-compilation-time
  #.(multiple-value-bind (second minute hour date month year)
	(decode-universal-time (get-universal-time))
      (declare (ignore second minute hour date month))
      year))




;;;; Times and Timestamps




;;; 24-hour-to-12 ...

(def-substitution-macro 24-hour-to-12 (hour)
  (if (or (=f hour 0) (>f hour 12)) (absf (-f hour 12)) hour))

(defun-simple null-or-zero-p (x)
  (with-temporary-gensym-float-creation null-or-zero-p
    (or (null x)
	(and (fixnump x) (=f x 0))
	(and (gensym-float-p x) (=e x 0.0))
	(and (managed-float-p x) (=e (managed-float-value x) 0.0)))))




;;; Select-am-or-pm ... if second? is specified, so must be minute?.  Minute?
;;; and second? effectively default to 0.

(defun select-am-or-pm (hour &optional minute? second?
			do-noon-or-midnight-if-applicable?)
  (if (<f hour 12)
      (or (if do-noon-or-midnight-if-applicable?
	      (if (and (=f hour 0)
		       (null-or-zero-p minute?)
		       (null-or-zero-p second?))
		  "midnight"))
	  "a.m.")
      (or (if do-noon-or-midnight-if-applicable?
	      (if (and (=f hour 12)
		       (null-or-zero-p minute?)
		       (null-or-zero-p second?))
		  "noon"))
	  "p.m."))
  
  ;; PRIOR TO 3.0:   (Yes, said Chicago Manual -- "NO! YUCH!!", said users)
  ;; -- this actually printed m. during the entire hour 12 noon to 12:59 p.m.;
  ;; and it printed p.m. during the entire hour 12 midnight to 12:59 a.m.!!!!
  ;; (MHD 5/15/91)
;    (cond
;      ((=f hour 0)
;       ;; midnight
;       "p.m.")
;      ((=f hour 12)
;       ;; noon
;       "m.")
;      ((<f hour 12) "a.m.")
;      (t "p.m."))
  
  )

;; Rename with "-string" suffix?!





;;; Select-day-of-week-string ... returns a three-letter day-of-the-week string,
;;; which is constant and should not be recycled.  Day-of-week-index is 0-based,
;;; starting with Monday.  For example, (select-day-of-week-string 2) returns
;;; "Wed".

(defun select-day-of-week-string (day-of-week-index)
  (case day-of-week-index
    (0 "Mon") (1 "Tue") (2 "Wed") (3 "Thu") (4 "Fri") (5 "Sat") (6 "Sun")))



;;; Select-month-string ... returns a three-letter month string, which is
;;; constant and should not be recycled.  Month-index is 1-based, starting with
;;; January.  For example, (select-month-string 2) returns "Feb".

(defun select-month-string (month-index)
  (case month-index
    (1 "Jan") (2 "Feb") (3 "Mar") (4 "Apr") (5 "May") (6 "Jun")
    (7 "Jul") (8 "Aug") (9 "Sep") (10 "Oct") (11 "Nov") (12 "Dec")))






;; The following were only ever used, and are only used right now, in GRAPHS2
;; by the function make-text-string-for-time-axis-label.  (MHD 5/15/91)

(defun print-minute-and-second (minute second)
  (tformat
    "~a~d:~a~d"
    (if (<f minute 10) "0" "") minute
    (if (<f second 10) "0" "") second))


(defun print-hour-and-minute (hour minute)
  (print-relative-hours-and-minutes (24-hour-to-12 hour) minute))


(defun print-relative-hours-and-minutes (hours minutes)
  (tformat "~d:~a~d" hours (if (<f minutes 10) "0" "") minutes))


(defun print-day-of-week-and-hour (day-of-week hour)
  (tformat
    "~d~a,~a"
    (24-hour-to-12 hour)
    (select-am-or-pm hour)
    (select-day-of-week-string day-of-week)))


(defun print-relative-hours (hours)
  (tformat "~d h." hours))


(defun print-month-and-date (month date)
  (tformat "~d ~a" date (select-month-string month)))


(defun print-relative-days (days)
  (tformat "~d d." days))			; Would you guess that "3 d." means
						;   "3 days"?!  (MHD)

(defun print-month-and-year (month year)
  (tformat
    "~a ~a~d"
    (select-month-string month) 
    (if (<f year 10) "0" "")
    (mod year 100)))


(defun print-relative-weeks (weeks)
  (tformat "~d w." weeks))

;(defun print-relative-days-and-hours (days hours)
;  (twrite-positive-fixnum days)
;  (if (=f days 1) (twrite-string " day,") (twrite-string " days,"))
;  (twrite-positive-fixnum hours)
;  (if (=f hours 1) (twrite-string " hr") (twrite-string " hrs")))


;(defun print-relative-weeks-and-days (weeks days)
;  (twrite-positive-fixnum weeks)
;  (if (=f weeks 1) (twrite-string "week") (twrite-string "weeks"))
;  (twrite-positive-fixnum days)
;  (if (=f days 1) (twrite-string "day") (twrite-string "days")))




;(defun print-relative-years-and-weeks (years weeks)
;  (twrite-positive-fixnum years)
;  (if (=f years 1) (twrite-string "year") (twrite-string "years"))
;  (twrite-positive-fixnum weeks)
;  (if (=f weeks 1) (twrite-string "week") (twrite-string "weeks")))


;; End of functions just used for GRAPHS2.  (MHD 5/15/91)





;;; Print-relative-time writes number-of-seconds to the current text string as
;;; an interval.  Number-of-seconds may be either a fixnum integer, a gensym
;;; float, or a managed float.

(defun-void print-relative-time (number-of-seconds)
  ;; Bignums are no longer supported (ghw 2/29/96)
;  (when (typep number-of-seconds 'bignum)
;    (setq number-of-seconds (coerce-to-gensym-float number-of-seconds)))
  (cond
    ((fixnump number-of-seconds)
     (loop with positive-number-of-seconds fixnum
	   = (cond ((<f number-of-seconds 0)
		    (twrite-char #.%\-)
		    (-f number-of-seconds))
		   (t number-of-seconds))
	   with remainder fixnum = positive-number-of-seconds
	   with quotient fixnum = 0
	   with how-many fixnum = 0
	   with so-far fixnum = 0
	   for divisor fixnum in '(604800 86400 3600 60 1)
	   for singular-unit in '(week day hour minute second)
	   for plural-unit in '(weeks days hours minutes seconds)
	   initially
	     (when (=f positive-number-of-seconds 0)
	       (twrite-string "0 seconds")
	       (loop-finish))
	     (setq how-many
		   (loop with remainder fixnum = positive-number-of-seconds
			 for divisor fixnum in '(604800 86400 3600 60 1)
			 do
		     (setq quotient (floorf-positive remainder divisor))
		     (setq remainder (modf-positive remainder divisor))
			 count (>f quotient 0)))
	   do
       (setq quotient (floorf-positive remainder divisor))
       (setq remainder (modf-positive remainder divisor))
       (when (>f quotient 0)
	 (incff so-far)
	 (twrite-positive-fixnum quotient)
	 (twrite-char #.%space)
	 (twrite-symbol (if (=f quotient 1) singular-unit plural-unit))
	 (unless (=f so-far how-many)
	   (twrite-string
	     (cond ((and (>f how-many 2) (>f how-many (1+f so-far)))
		    ", ")
		   ((>f how-many 2)
		    ", and ")
		   (t " and ")))))))
    ((or (and (managed-float-p number-of-seconds)
	      (nanp (managed-float-value number-of-seconds)))
	 (and (gensym-float-p number-of-seconds)
	      (nanp number-of-seconds)))
     (twrite-string "NaN"))
    ((or (managed-float-p number-of-seconds) (gensym-float-p number-of-seconds))
     (with-temporary-gensym-float-creation print-relative-time
       (loop with float-number-of-seconds gensym-float
	     = (if (managed-float-p number-of-seconds)
		   (managed-float-value number-of-seconds)
		   number-of-seconds)
	     with positive-number-of-seconds gensym-float
	     = (cond ((<e float-number-of-seconds 0.0)
		      (twrite-char #.%\-)
		      (-e float-number-of-seconds))
		     (t float-number-of-seconds))
	     with remainder gensym-float = positive-number-of-seconds
	     with quotient fixnum = 0
	     with how-many fixnum = 0
	     with so-far fixnum = 0
	     for divisor fixnum in '(604800 86400 3600 60)
	     for float-divisor gensym-float
	     = (coerce-fixnum-to-gensym-float divisor)
	     for singular-unit in '(week day hour minute second)
	     for plural-unit in '(weeks days hours minutes seconds)
	     initially
	       (when (=e positive-number-of-seconds 0.0)
		 (twrite-string "0.0 seconds")
		 (return nil))
	       (setq how-many
		     (loop with remainder gensym-float
			   = positive-number-of-seconds
			   with float-quotient gensym-float = 0.0d0
			   for divisor fixnum in '(604800 86400 3600 60 1)
			   for float-divisor gensym-float
			   = (coerce-fixnum-to-gensym-float divisor)
			   do
		       (if (=f divisor 1)
			   (setq float-quotient remainder)
			   (setq float-quotient
				 (ffloore-first (/e remainder float-divisor))))
		       (setq remainder
			     (-e remainder (*e float-quotient float-divisor)))
			   count (>e float-quotient 0.0)))
	     do
	 (setq quotient (floore-first (/e remainder float-divisor)))
	 (setq remainder (-e remainder
			     (*e (coerce-fixnum-to-gensym-float quotient)
				 float-divisor)))
	 (when (>f quotient 0)
	   (incff so-far)
	   (twrite-positive-fixnum quotient)
	   (twrite-char #.%space)
	   (twrite-symbol (if (=f quotient 1) singular-unit plural-unit))
	   (unless (=f so-far how-many)
	     (twrite-string
	       (cond ((and (>f how-many 2) (>f how-many (1+f so-far)))
		      ", ")
		     ((>f how-many 2)
		      ", and ")
		     (t
		      " and ")))))
	     finally
	       (when (>e remainder 0.0)
		 (twrite-float remainder)
		 (twrite-string " seconds")))))
    (t
     #+development
     (cerror "Continue by printing <unprintable interval>"
	     "Print-relative-time given a non-number: ~a" number-of-seconds)
     (twrite-string "<unprintable interval>"))))

;; The above function newly created out of code teased out of print-constant.
;; (MHD 5/26/92)




;;; Print-decoded-time takes decoded units of time and prints it in the `standard
;;; time format'.  Output is sent to the current text string (using twrite, etc.).
;;; Within the standard there are two variations, with seconds or without.  Callers
;;; that say they they print "in standard time format" should usually specify if they
;;; mean with or without seconds, since either one may be commonly used.

(defun print-decoded-time (seconds? minutes hours day month year)
  (print-decoded-date day month year)
  (twrite-char #.%space)
  (twrite-char #.%space)
  (print-decoded-time-of-day seconds? minutes hours))

;; Removed choice about 4 digit versus 2 digit years. For year 2000 compliance
;; all displays and outputs of years must be 4 digits. ajs (11/21/97)

(defun print-decoded-date (day month year)
  ;; Military standard, Army version (Caps & lowercase)
  ;;   e.g.  10 May 82
  ;;
  ;; BUT: if year-as-4-digits? is true, 
  ;;   e.g.  10 May 1982
  ;;
  ;; As of releases after 5.0r3 always 4 digits for full year
  ;; 2000 compliance.
  (twrite-positive-fixnum day)
  (twrite-char #.%space)
  (twrite-string (select-month-string month))
  (twrite-char #.%space)
  (twrite-positive-fixnum year))

(defun print-decoded-time-of-day (seconds? minutes hours)
  ;; New: (3.0 and later) 
  ;; 
  ;; e.g. 12:00 a.m. [midnight -mhd], 12:00 p.m. [noon -mhd], 3:14 p.m.,
  ;;   11:01 a.m.
  ;;   
  ;; Prior to 5/15/91 (prior to 3.0):
  ;; 
  ;; ;; e.g. 12:00 p.m. [midnight -mhd], 12:00 m. [noon -mhd], 3:14 p.m.,
  ;; ;;   11:01 a.m.
  ;;
  ;; The old way was recommended by Chicago Manual of Style, but it confused
  ;; most people, and no other computer programs do it either, to our knowledge.
  ;; (MHD 5/15/91)
  (twrite-positive-fixnum (24-hour-to-12 hours))
  (twrite-char #.%\:)
  (if (<f minutes 10) (twrite-char #.%\0))
  (twrite-positive-fixnum minutes)
  (when seconds?
     (twrite-char #.%\:)
     (cond ((fixnump seconds?)
	    (when (<f seconds? 10)
	      (twrite-char #.%\0))
	    (twrite-positive-fixnum seconds?))
	   ((or (gensym-float-p seconds?) (managed-float-p seconds?))
	    (with-temporary-gensym-float-creation print-decoded-time-of-day
	      (let ((seconds (if (managed-float-p seconds?)
				 (managed-float-value seconds?)
				 seconds?)))
		(declare (type gensym-float seconds))
		(when (<e seconds 10.0)
		  (twrite-char #.%\0))
		(write-floating-point-number seconds 2 6 8 t nil nil))))))
  (twrite-char #.%space)
  (twrite-string (select-am-or-pm hours minutes seconds? nil)))


;; Same-Gensym-date-p moved to clocks, since this file is loaded into
;; Telewindows, which doesn't use Gensym time.  -jra 3/4/94


;; For the preceeding subsection: Change "print-" to "write-" where appropriate?!

;; And: Change "gensym-time" to "current-gensym-time" where appropriate?!


;; Move the part of print-constant that deals with time intervals here!
;; (MHD 5/15/91)








;;;; Copyright Boilerplate



;;; Boilerplate-lines-of-text is a list of the lines of text in the copyright
;;; notice to be displayed by G2 or Telewindows.  The list should of course be
;;; copied before it is shared with any G2 data structure that subjects it to
;;; reclamation.  This has the property that the lines have been broken in the
;;; right spots for Telewindows, so that that platform need not format them.  G2
;;; will format them to fit in its "title block" table.  It will turn out, as of
;;; 4/8/93, that they end up broken the same way there.  I.e., the wording and
;;; line break positions in the following text match the G2 title block exactly,
;;; but the line height and interword spacing may be slightly different.

;;; Copyright-boilerplate-lines-of-text-1 is just the first two lines, i.e.,
;;;
;;;    Copyright ... Gensym Corporation.
;;;    All Rights Reserved
;;;
;;;
;;; Copyright-boilerplate-lines-of-text-2 are "fine print", including the US
;;; Government Restricted Rights, notification that this is licensed software,
;;; and the advice that the use of the software is at the customer's sole risk.


;;; Copyright-boiler-plate-lines-of-text incorporates both of the above variables'
;;; value, and may share conses and strings between the two.  It inserts two blank
;;; lines, i.e., (<NL> <NL>) between the two lists.

;;; Note that copyright-boilerplate-lines-of-text-1 and
;;; copyright-boilerplate-lines-of-text-2 produce apparently valid texts.
;;; However, the conses are actually gensym conses, rather than slot-value
;;; conses.  This is done so that they can be used in Telewindows.  It should
;;; not matter in practice, though it's a bit of a kludge.
    
(defun copyright-boilerplate-lines-of-text-1 ()
  (gensym-list
    (tformat-text-string
      "Copyright ~c 1986 - ~d Gensym Corporation.~%"
      #.%copyright-sign
      year-at-compilation-time)
    #w"All Rights Reserved."))

(def-system-variable copyright-boilerplate-lines-of-text-1 times
  (:funcall copyright-boilerplate-lines-of-text-1))


;; The following could be defconstants, but defparameter is fine,
;; and also avoids a constant warning in Allegro. (MHD 6/10/00)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter disclaimer-for-release-quality-software
  ;; New Boilerplate per Bob Moore memo of 4/13/90 (included here 4/17/90):
  '(#w"Although this software has been extensively tested, Gensym cannot"
    #w"guarantee error-free performance in all applications.  Accordingly,"
    #w"use of the software is at the customer's sole risk."))

(defparameter disclaimer-for-licensing-and-authorization
  '(#w"The use of this software and related documentation is restricted under"
    #w"the terms of a separate license agreement.  Each copy of this software"
    #w"may be used only on a single designated CPU.  This software is property"
    #w"of Gensym Corporation and may not be copied or used except as specified"
    #w"in the license agreement."))

(defparameter restricted-rights-legend
  '(
    ;; New:
    ;;
    ;;   U.S. Government Restricted Rights: Use, ...
    ;;
    ;; replaces
    ;;
    ;;   RESTRICTED RIGHTS LEGEND Use, ...
    ;;
    ;; per memos between with Lowell Hawkinson, Mark David, and Stephen
    ;; Gregorio today.  (MHD 4/8/93)
    #w"U.S. GOVERNMENT RESTRICTED RIGHTS: Use, duplication, or disclosure by "
    #w"the Government is subject to restrictions as set forth in subparagraph"
    #w"(c) (1) (ii) of the Rights in Technical Data and Computer Software"
    ;;#w"clause at DFARS 252.227-7013. Gensym Corp., 52 Second Avenue, "
    ;;#w"Burlington, MA 01803-4411 - (781) 265-7100 - http://www.gensym.com/"))
    #w"clause at DFARS 252.227-7013. Gensym Corporation Worldwide Headquarters, "
    #w"6011 West Courtyard Drive, Suite 300, Austin, Tx 78730 - (512) 377-9700 - http://www.gensym.com/"))
)


(defmacro copyright-boilerplate-lines-of-text-2-macro ()
  `(gensym-list
     ,@disclaimer-for-release-quality-software
     #.(stringw #.%line-separator)
     #.(stringw #.%line-separator)
     
     ,@disclaimer-for-licensing-and-authorization
     #.(stringw #.%line-separator)
     #.(stringw #.%line-separator)

     ,@restricted-rights-legend
    ))

(defun copyright-boilerplate-lines-of-text-2 ()
  (copyright-boilerplate-lines-of-text-2-macro))

(def-system-variable copyright-boilerplate-lines-of-text-2 times
  (:funcall copyright-boilerplate-lines-of-text-2))



(defun make-copyright-boilerplate-lines-of-text-for-tw ()
  (nconc
    (copy-list-using-gensym-conses
      copyright-boilerplate-lines-of-text-1)
    (gensym-list #.(stringw #.%line-separator)
		 #.(stringw #.%line-separator))
    copyright-boilerplate-lines-of-text-2))

;; The def-system-variables could easily be a defparameters constant if tformat
;; could be used at load time! Note that the list and string structures are not
;; intended to be shared or recycled ever.  (MHD 2/7/96)

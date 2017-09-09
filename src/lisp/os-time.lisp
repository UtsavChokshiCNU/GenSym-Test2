;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module OS-TIME

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson, Nick Caruso

;; 2 February 1992

(declare-forward-references
  (obtain-simple-gensym-string function)
  (copy-null-terminated-string-as-text-string function)
  (copy-text-string function)
  (copy-wide-string-given-length function)	; unicode
  (make-wide-string-function function)		; unicode
  (reclaim-wide-string function)		; unicode
  (reclaim-gensym-string function))

;;; This module contains the machinery with which G2 obtains the operating
;;; system time.  The Lisp facilities for acquiring time information are
;;; untrustworthy, since they often cons or cache bignums.  It was thought that
;;; this machinery is complex enough to rate its own module.  As well, it is
;;; time os-specific modules got more revealing names.






;;;; Reading the Operating System Clock




;;; `C-native-clock-ticks-per-second' returns the number of clock ticks per second
;;; of the native sub-second clock.  This function returns a constant per platform
;;; (so it needs to be called only once).  `c-native-clock-ticks' takes a mask
;;; (2^n - 1, where n is an integer).  The mask is used to prevent
;;; c-native-clock-ticks from returning a bignum and should be
;;; most-positive-fixnum.  C-native-clock-ticks returns the number of clock ticks
;;; from a fix point in the past, modulo n.



(def-gensym-c-function c-native-clock-ticks (:fixnum-long64 "g2ext_g2_clock_ticks")
  ((:fixnum-long64 mask)))


(def-gensym-c-function c-native-clock-ticks-per-second
                       (:fixnum-int "g2ext_g2_clock_ticks_per_second")
  ())

;;; The function `c-unix-time-as-float' returns a gensym-float reflecting the
;;; current time as a number of seconds since Midnight, January 1, 1970 UTC.
;;; Note that this float will have a non-zero fractional part, and should be
;;; able to be used to measure subsecond intervals.  All system clocks have some
;;; granularity of accuracy ranging from 1/60th of a second to microseconds.
;;; The implementation of this function per platform should return the most
;;; accurate value available, but in all cases the granularity must be
;;; subsecond.

;;; The macro `gensym-get-unix-time' is the interface to this operation.

(def-gensym-c-function c-unix-time-as-float
                       (:double-float "g2ext_unix_time_as_float") 
  ())

(defmacro gensym-get-unix-time ()
  `(c-unix-time-as-float))




;;; The macro `gensym-get-local-time' is intended to be the interface to a
;;; function which returns a gensym-float reflecting the current time as a
;;; number of seconds since Midnight, January 1, 1970, in the local time zone.
;;; Note that this float should have a non-zero fractional part, and should be
;;; able to be used to measure subsecond intervals.  All system clocks have some
;;; granularity of accuracy ranging from 1/60th of a second to microseconds.
;;; The implementation of this function per platform should return the most
;;; accurate value available, but in all cases the granularity must be
;;; subsecond.  In actuality, however, the C side for this function is not
;;; implemented, and so gensym-get-local-time always returns 0.0.

(defmacro gensym-get-local-time ()
  `(progn
     #+development
     (cerror "Continue, returning 0.0"
             "gensym-get-local-time is not implemented")
     ;; if it were implemented, we'd call into C here; the stubbed out function
     ;; was named g2ext_local_time_as_float
     0.0))







;;;; Time Zones




;;; `C-time-zone-or-daylight-saving-time' is two functions rolled into one.  This
;;; functions only works on Unix and VMS systems using the ftime() system call.
;;; When this c-time-zone-or-daylight-saving-time is given 0, it will return the
;;; time zone of the system in minutes west of GMT.  (If the system is in Japan,
;;; then a negative number will be returned.) If this function is given 1, a
;;; non-zero positive fixnum is returned if day-light saving is in effect,
;;; otherwise 0 if there is no day-light saving.

;;; Note that VMS always returns 0 for both of these values, since it has no
;;; provision for automatic setting of timezone or daylight savings time.  Since
;;; the documented behavior of G2 is to provide a time at least as good as the
;;; host operating system, this is acceptable.

(def-gensym-c-function c-time-zone-or-daylight-saving-time
                       (:fixnum-int "g2ext_time_zone")
  ((:fixnum-int choice)))

(def-gensym-c-function c-g2ext-is-dst-used
                       (:fixnum-int "g2ext_is_dst_used")
  ())

#+development
(defun lisp-time-zone-in-minutes ()
  (multiple-value-bind (s m h d mon y day daylight-p time-zone)
      (decode-universal-time (get-universal-time))
    (declare (ignore s m h d mon y day daylight-p))
    (let ((zone-in-minutes (* time-zone 60)))
      (gensym-assert (fixnump zone-in-minutes))
      zone-in-minutes)))

(defmacro time-zone-in-minutes ()
  `(c-time-zone-or-daylight-saving-time 0))


(defun time-zone-in-hours ()
  (let ((local-time-zone
          #+development
          (lisp-time-zone-in-minutes)
          #-development
          (time-zone-in-minutes)))
    #+(and development chestnut-3)
    (gensym-assert (>=f local-time-zone 0))
    (multiple-value-bind (quotient remainder)
        (floorf local-time-zone 60)
      (if (>=f remainder 30)
          (1+f quotient)
          quotient))))

(defmacro daylight-saving-time-p-macro ()
  `(let ((daylight-saving-zero
           (c-time-zone-or-daylight-saving-time 1)))
     #+development
     (gensym-assert (>=f daylight-saving-zero 0))
     (/=f daylight-saving-zero 0)))

#+unused
(defun daylight-saving-time-p ()
  (daylight-saving-time-p-macro))

;;; The gensym-c-function `c-g2ext-get-current-time-zone' return string with
;;; current time zone information into buffer and returns -1 if they were error
;;; or buffer string length.

(def-gensym-c-function c-get-current-time-zone
    (:fixnum-int "g2ext_get_current_time_zone")
  ((:wide-string buffer) ; Returned current system time zone information
   (:fixnum-int buflen)))
   
;;; The system-procedure `get-current-time-zone' return string with
;;; current time zone information. 

(defun get-current-time-zone ()
  (let* ((buffer-size 64) ; length of time zone informnation string 
         (buffer? (make-wide-string-function buffer-size))
         (new-length
           (c-get-current-time-zone buffer? buffer-size))
         (time-zone-information?
           (if (>f new-length 0)      
             (copy-wide-string-given-length buffer? new-length)
             (copy-text-string ""))))
    ;; GENSYMCID-1034: Need feature to get the delta between UTC and the time zone of the G2-server
    (multiple-value-prog1
        (values time-zone-information? (time-zone-in-minutes))
      (reclaim-wide-string buffer?))))

;;;; Decoding Universal Time
;;; This section implements functions for decoding time stamps in universal and
;;; unix-time formats.



;;; The constant seconds-from-1900-to-1990 is the bignum result of evaluating
;;; (encode-universal-time 0 0 0 1 1 1990 0).

;;; Note: now we use (* 4838400 587) instead of 2840140800 to prevent bignums
;;; appears directly in translated C code, or the translation results between
;;; 32-bit and 64-bit translator will be different.

(defconstant-excluding-gsi seconds-from-1900-to-1990 (* 4838400 587)) ; = 2840140800





;;; The macro `Gensym-decode-universal-time' is to be called in place of
;;; decode-universal-time.  It is more efficient to call the macro
;;; `gensym-decode-float-universal-time', and both of these are based on
;;; gensym-decode-unix-time.

(defmacro gensym-decode-float-universal-time (float-universal-time)
  `(gensym-decode-unix-time (universal-time-to-unix-time ,float-universal-time)))

(defmacro gensym-decode-universal-time (universal-time)
  `(gensym-decode-float-universal-time (coerce-to-gensym-float ,universal-time)))




;;; The parameter `global-daylight-saving-time-adjustment' defaults to 0.  In
;;; Telewindows, it always remains 0.  In G2, it is maintained as the value of
;;; the clock-adjustment-in-minutes slot of the installed timing-parameters
;;; system table.  Deinstalling that system table must reset this to 0.  This
;;; value should be used only when encoding and decoding timestamps to calendar
;;; times.

(defparameter global-daylight-saving-time-adjustment 0)




;;; The foreign function `c-decode-unix-time' is a primitive of
;;; gensym-decode-unix-time.


(def-gensym-c-function c-decode-unix-time (:fixnum-int "g2ext_decode_unix_time")
  ((:double-float seconds-from-1970)
   (:byte-vector-16 response)))




;;; The macro `gensym-decode-unix-time-macro' takes a gensym-float UNIX time
;;; and returns the normal set of values for a decoded time; seconds, minutes,
;;; hours, date, month, year, day-of-week, daylight-savings-p and time-zone.
;;; The returned time is adjusted by the global-daylight-saving-time-adjustment,
;;; which gets modified in G2 to correspond to the clock-adjustment-in-minutes
;;; of the installed timing-parameters system-table.  Note that this version is
;;; preferable to the universal time equivalent since no consing is required and
;;; the UNIX time is what all of our operating systems already deal with.
;;; The following values are returned:

;;;   second (0-59)
;;;   minute (0-59)
;;;   hour (0-23)
;;;   date (1-31)
;;;   month (1-12)
;;;   year (e.g. 1994)
;;;   day-of-week (0=Monday-6=Sunday)
;;;   daylight-savings (1 = yes, 0 = no)
;;;   time-zone-in-hours (-12 through 12)

(defun-simple make-gensym-time-array ()
  (make-static-array 9 :element-type '(unsigned-byte 16)))

(defvar gensym-time-array (make-gensym-time-array))

(defmacro gensym-decode-unix-time-macro (adjusted-unix-time)
  `(macrolet ((gensym-time-aref (index)
                `(aref (the (simple-array 
                              (unsigned-byte 16) 1)
                            gensym-time-array)
                       ,index)))
     (c-decode-unix-time ,adjusted-unix-time gensym-time-array)
     (values (gensym-time-aref 0)           ;(0) second
             (gensym-time-aref 1)           ;(1) minute
             (gensym-time-aref 2)           ;(2) hour
             (gensym-time-aref 3)           ;(3) date
             (gensym-time-aref 4)           ;(4) month
             (+f (gensym-time-aref 5) 1900) ;(5) year
             (gensym-time-aref 6)           ;(6) day-of-week
             (/=f (gensym-time-aref 7) 0)   ;(7) daylight-savings-p
             (time-zone-in-hours))))        ;(8) time-zone

;;; In order to get timestamps past Jan. 19, 2038 03:14:07 GMT
;;; (2^31 - 1 in seconds from midnight, Jan. 1, 1970 GMT, also
;;; called unix-time), for any number of unix-time seconds >= 2^31:
;;; we subtract off 68 years, decode using the C code, and then add
;;; back the 68 years.  This gives valid timestamps for 62 years because
;;; the years 1970 to 2032 exactly model the years 2038 to 2100 up until
;;; the absence of leap year in 2100, except the day-of-week has to be
;;; adjusted by 1.  So, this gives valid timestamps up to Jan. 19, 2100
;;; 03:14:07 GMT or 2^31 - 1 + 62 years in unix-time. - jpg 11/13/06

;;; `68-years-in-seconds' is the number of seconds from midnight, Jan. 5, 1970
;;; to midnight, Jan. 5, 2038 gotten using encode-universal-time - jpg 11/13/06

(defconstant 68-years-in-seconds 2145916800.0d0)

(defconstant 2-to-31-plus-62-years 4104011648.0d0)


;;; Callers of `gensym-decode-unix-time' need to use with-temporary-gensym-float-creation.

(defun gensym-decode-unix-time (gensym-float-unix-time)
  (let ((adjusted-unix-time
          (+e gensym-float-unix-time
              (coerce-fixnum-to-gensym-float
                (*f 60 global-daylight-saving-time-adjustment)))))
    (if (>=e adjusted-unix-time #.(expt 2.0d0 31))  ; 2147483648.0
        (multiple-value-bind (seconds minutes hours date month year day-of-week
                                      daylight-savings-time-p time-zone)
            (gensym-decode-unix-time-macro
              (if (>=e adjusted-unix-time 2-to-31-plus-62-years)
                  #.(expt 2.0d0 31)  ;; timestamp maxes out
                  (-e adjusted-unix-time 68-years-in-seconds)))
          (values seconds minutes hours date month
                  (if (>=e adjusted-unix-time 2-to-31-plus-62-years)
                      (+f year 62)
                      (+f year 68))
                  (if (>=e adjusted-unix-time 2-to-31-plus-62-years)
                      day-of-week
                      (modf (1+f day-of-week) 7))
                  daylight-savings-time-p time-zone))
        (gensym-decode-unix-time-macro adjusted-unix-time))))



;;;; Encoding Time from the Operating System




;;; Declaration:     c-get_encoded_unix_time
;;; Type:            def-gensym-c-function
;;; Purpose:         call out to a c routine cc_get_encoded_unix_time, which uses
;;;                  the native OS facilities to encode the input "broken down"
;;;                  calendar time as a "unix time", relative to 1970.  This
;;;                  value is returned as a double-float.
;;;
;;; Return behavior: returns a single double-float value giving the time in seconds
;;;                  since 00:00:00 1 jan 1970 GMT equivalent to the input calendar time.
;;; Users:           gensym-encode-unix-time.
;;; Prerequisites:   all six input arguments should represent a legitimate calendar time,
;;;                   e.g., don't pass in 12:14:00 322 November 1995 and expect a
;;;                   reasonable answer.  You may well _get_ a reasonable answer, but
;;;                   you cannot depend on it, because it is not portable.
;;;
;;; Side effects:    none
;;;
;;; Non-local exits: none
;;; Memory impact:   allocates a double-float (the return value)
;;; NOTES:            The POSIX mktime() library routine will return -1 if it
;;;                   can tell that a time is invalid, but it is not guaranteed to
;;;                   catch all invalid times.  Times earlier than midnight, 1 jan
;;;                   1970 (the "Bell Epoch" hee hee) are not defined under the POSIX
;;;                   standard, and so mktime cannot be depended upon to do anything
;;;                   reasonable with them.

 (def-gensym-c-function c-get_encoded_unix_time
                        (:double-float "g2ext_get_encoded_unix_time")
   ((:fixnum-int second)
    (:fixnum-int minute)
    (:fixnum-int hour)
    (:fixnum-int date)
    (:fixnum-int one-based-month)
    (:fixnum-int year-with-century)))

;; Caveat: since we ask mktime to do DST adjustments, if we pass any time
;; between 2 AM and 3 AM on any spring DST adjustment date, mktime will return
;; -1.  There is a special case in the DST calculations on January 6th, 1974,
;; possibly because Daylight Savings Time in the US was pushed back to try to
;; save fuel (during the Arab Oil Embargo), This may be a bug in that special
;; case code.  This happens on the sun4 and the Alpha OSF.  The HP 9000/700
;; returns a time, but it simply doesn't correct for DST, This is a bug.  I have
;; not investigated other platforms.  See my entry in the unix paper trail on
;; this subject.  -ncc, 8/11/94

;; The only caller of this function, gensym-encode-unix-time, will fall back on
;; our own computations of encodings when mktime returns -1, so when it punts,
;; we fill in with "something close".  -jra 11/29/94





;;; The function c-infer_encoded_unix_time takes as argument a gensym-float
;;; number of seconds since 1970, unadjusted for daylight savings time, and asks
;;; the host operating system to adjust it for daylight savings.  This function
;;; assumes the daylight savings setting used in generating the argument was
;;; that of the present moment, and that, since the argument may represent a
;;; time other than the present, this time may be off due to a daylight savings
;;; shift having happened between then and now.  If the operating system cannot
;;; make this adjustment for any reason, c-infer_encoded_unix_time returns -1.
;;; The C side of this function typically makes a call to time() and two calls
;;; to localtime() and is thus much less efficient than c-get_encoded_unix_time.
;;; It is recommended for use only after attempting c-get_encoded_unix_time.

 (def-gensym-c-function c-infer_encoded_unix_time
                       (:double-float "g2ext_infer_encoded_unix_time")
  ((:double-float time-since-1970-no-dst-adjustment)))
  

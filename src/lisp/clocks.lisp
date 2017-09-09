;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CLOCKS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard



(declare-forward-reference warmbooting? variable)
(declare-forward-reference warmbooting-with-catch-up? variable)	; KB-LOAD1
(declare-forward-reference warmboot-current-time variable)	; KB-LOAD2
(declare-forward-reference timing-parameters variable)   	; WORKSTATIONS
(declare-forward-reference warmboot-simulated-time variable)	; KB-LOAD2
(declare-forward-reference scheduler-mode-function function)	; WORKSTATIONS
(declare-forward-reference minimum-scheduling-interval-function
			   function)				; WORKSTATIONS
(declare-forward-reference add-delta-time-to-variables-and-parameters
			   function)				; HISTORIES
(declare-forward-reference update-trend-charts-for-clock-discontinuity
			   function)    			; GRAPHS


;;;; G2 Scheduler Clock Ticking




;;; This module contains code for ticking the clock for G2's scheduler.  This
;;; file is closely tied to SCHEDULE, which implements the queues and handling
;;; functions for the scheduler.  This file implements a time format called
;;; gensym-time and clock ticking for the scheduler.  For functions to print
;;; real-time time-stamps, see the files OS-TIME and UTILITIES3.

;;; The system variable `g2-time-at-start' contains a managed-float holding a
;;; unix-time time stamp.  This value reflects the current-g2-time when the
;;; Start option was chosen for this run of G2.  When G2 is not running or
;;; paused, this value is unreliable.

(def-system-variable g2-time-at-start clocks)

;;; This is sent to remote connections via the ICP version protocol.
;;; It is used to identify the G2 process, so the remote side can tell if
;;; the G2 process has been shut down, and then restarted, or not.
;;; It should not be kept in synch with g2-time-at-start, despite the
;;; similarity of its name.

(def-system-variable g2-time-at-start-as-text-string clocks)





;;;; Efficient Arithmetic for Time Intervals (obsolete)




;;; A suite of fixnum operators has long been defined for intervals in G2.
;;; However, this is now obsolete given the various representations we have for
;;; time intervals.  Fixnum time has its set of operators, gensym-time is a
;;; fixnum, and unix-times are stored as floats.  In reviewing the uses of the
;;; +i suite of operations, at least half of them were not operating on
;;; intervals but on fixnums genericly.  To make this really work on intervals,
;;; one would have to address floating point numbers, and the current set of
;;; fixnum operations makes no provision for this.  So, this suite of operations
;;; is going to be phased out in favor of using +f and +e.  -jra 3/6/94

(def-fixnum-arithmetic-system i)






;;;; Clock Ticking




;;; Within G2 the scheduler has two sets of event queues, one running in real
;;; time and one running in G2 time.  Real time proceeds as you would expect,
;;; but G2 time can vary from real time in several ways.  Within the
;;; timing-parameters system table, the scheduler-mode can be set to simulated
;;; time or to as-fast-as-possible mode.  In these cases G2 time will have
;;; little relation to real-time.  When in real-time mode the G2 time can be
;;; delayed behind real-time by pausing G2, or by imposing a shortest scheduling
;;; interval.  Because of these restrictions there are two sets of times for G2,
;;; the current-real-time and the current-g2-time.  Both of these values are
;;; managed-floats.  While a task is being executed these values will not
;;; increase.  They are only updated by the clock-ticking functions implemented
;;; below, and immediately after these values are advanced, the scheduler queues
;;; must be updated to bring them into sync with the new values.

;;; The previous implementation of this file used a time format called
;;; `gensym-time'.  Because there is so much code in G2 that depends on it, it
;;; will still be provided, but users are encouraged to switch over to the
;;; current-g2-time and current-real-time implementations, in unix-time format.
;;; The gensym-time format is based on Common Lisp universal times, which is
;;; seconds since Midnight, January 1, 1900.  Here is how it worked.  The
;;; special variable `gensym-base-time-as-managed-float' is set to the value of
;;; get-universal-time when G2 is started.  Gensym-times are then fixnum offsets
;;; from this value, so that the sum of a gensym-time and the Gensym base time
;;; yeilds a universal-time.  The variable *initial-value-of-gensym-time* was
;;; intended to be the first fixnum value for a gensym-time in a process, but
;;; this was always 0.  When G2 was started running (i.e. the menu item "Start"
;;; was selected) the gensym-time would be cached into a variable
;;; gensym-time-at-start, and gensym base time would be set again so that the
;;; sum of gensym-time and the base time would be a universal time.  The base
;;; time was set instead of the gensym-time to try and preserve the values in
;;; the gensym-time range, since it is limited to fixnum values.

;;; Within G2, the expression "the current time" then returned the difference
;;; between gensym-time and gensym-time-at-start.  This gave them timestamps
;;; that would start at zero for any run of a G2 KB.  As mentioned earlier, this
;;; will all be maintained for 4.0 by updating the gensym-time variable whenever
;;; the current-g2-time is modified.

(def-concept gensym-time)

(def-concept the-current-time)

(def-concept time)




;;; The system variable `current-real-time' contains a managed-float holding a
;;; unix-time time stamp.  This will be accurate as of the most recent previous
;;; point at which the scheduler started running tasks, whether or not G2 is
;;; currently running.  The system variable `fixnum-time-of-last-real-time-tick'
;;; contains the fixnum time at which the clock was last ticked.

(def-system-variable current-real-time clocks)

(def-system-variable fixnum-time-of-last-real-time-tick clocks)




;;; The system variable `current-g2-time' contains a managed-float holding a
;;; unix-time time stamp.  This value reflects the current time for a running
;;; G2.  When G2 is not running this value will be either the time at which G2
;;; started, or the last time seen in G2 while it was last running, but in
;;; general this value should not be depended upon except when G2 is running or
;;; paused.  The system variable `most-recent-g2-time' will hold the value that
;;; was in current-g2-time before the most recent clock tick.  The system
;;; variable `real-time-of-last-g2-tick' holds a managed float which contains
;;; the UNIX real time at which the last G2 clock tick was taken.  The system
;;; variable `fixnum-time-of-last-g2-tick' contains the fixnum time at which the
;;; last G2 clock tick was taken.

(def-system-variable current-g2-time clocks)

(def-system-variable most-recent-g2-time clocks)

(def-system-variable real-time-of-last-g2-tick clocks)

(def-system-variable fixnum-time-of-last-g2-tick clocks)




;;; The macro `g2-future-interval' takes a fixnum number of seconds and returns
;;; a gensym-float UNIX time that is that many seconds ahead into the future for
;;; G2's time clock.  This macro can be used to convert old scheduler intervals
;;; into current-g2-time style timestamps for the scheduler.

(defmacro g2-future-interval (fixnum-seconds)
  `(+e (managed-float-value current-g2-time)
       (coerce-fixnum-to-gensym-float ,fixnum-seconds)))

(defmacro g2-evaluation-value-to-future-interval (wait-interval)
  `(+e (managed-float-value current-g2-time)
       (if (evaluation-integer-p ,wait-interval)
	   (coerce-fixnum-to-gensym-float (evaluation-integer-value ,wait-interval))
	   (evaluation-float-value ,wait-interval))))


;;; The macro `future-interval' takes a fixnum number of seconds and returns a
;;; gensym-float UNIX time that is that many seconds ahead into the future for
;;; the scheduler's real-time clock.  This macro can be used to convert old
;;; scheduler intervals into current-g2-time style timestamps for the scheduler.
;;; The macro `subsecond-future-interval' is similar, but takes a gensym-float
;;; number of seconds instead of a fixnum number of seconds.  Note that these
;;; functions can create temporary gensym floats, and therefore should be called in
;;; a temporary float creation context.

(defmacro future-interval (fixnum-seconds)
  `(+e (managed-float-value current-real-time)
       (coerce-fixnum-to-gensym-float ,fixnum-seconds)))


;; Should the value of this macro be based on current-real-time or
;; (gensym-get-unix-time), which is the REAL current time.  Dunno for now,
;; choose the cheap current-real-time approach.  -jra 3/17/94

(defmacro subsecond-future-interval (gensym-float)
  `(+e (managed-float-value current-real-time) ,gensym-float))




;;; The constant `fixnum-time-until-real-time-tick' holds a fixnum time interval
;;; used to determine if enough time has passed to warrant ticking the real-time
;;; clock.  This is an internal to the clocks system.  The system-variable
;;; `fixnum-time-until-g2-time-tick' holds a fixnum time interval representing
;;; the amount of time that should pass on the interval timer before we expect
;;; that it will be time to tick the G2 time clock.  This is an internal to the
;;; clocks system.

(defconstant fixnum-time-until-real-time-tick 1)

(def-system-variable fixnum-time-until-g2-time-tick clocks 0)




;;; The system variable `g2-time-to-tick-p-base' holds a fixnum
;;; representing the fixnum time stamp of the last moment at which we took a
;;; tick in current-g2-time, or the last moment that we updated the time to tick
;;; cached values.  This value is only valid while G2 is running or paused, and
;;; is internal to the clocks system.  The system variable
;;; `real-time-to-tick-p-base' holds a fixum representing the fixnum
;;; time stamp of the last moment at which we took a tick in current-real-time,
;;; or the last time we updated the real time to tick cached values.  This is an
;;; internal to the clocks system.

(def-system-variable g2-time-to-tick-p-base clocks)

(def-system-variable real-time-to-tick-p-base clocks)




;;; The following system variables are grandfathered in from a previous clocks
;;; implementation.  They should eventually be removed in favor of the
;;; current-g2-time clock system.  See the gensym-time discussion above for a
;;; description of the values and meanings of these variables.

(def-system-variable gensym-time clocks 0)

(def-system-variable gensym-base-time-as-managed-float clocks nil)

(def-system-variable gensym-time-at-start clocks 0)




;;; The macro `convert-gensym-time-to-unix-time' converts a gensym-time (fixnum)
;;; to a unix-time as a gensym-float.

(defmacro convert-gensym-time-to-unix-time (gensym-time-to-convert)
  `(+e (coerce-fixnum-to-gensym-float
	 (-f ,gensym-time-to-convert gensym-time-at-start))
       (managed-float-value g2-time-at-start)))



;;; The macro `convert-unix-time-to-gensym-time' computes the inverse of the
;;; above.  If the unix time is old, there is the possibility that the
;;; timestamps are out of range of the present gensym time which is a fixnum.
;;; If so, the value will be most-negative-fixnum.  Note that the argument is a
;;; gensym-float, and so this must be called within a temporary float consing
;;; context.

(defmacro convert-unix-time-to-gensym-time (unix-time)
  (let ((float-gensym-time (gensym)))
    `(let ((,float-gensym-time
	      (+e (-e ,unix-time (managed-float-value g2-time-at-start))
		  (coerce-fixnum-to-gensym-float gensym-time-at-start))))
       (if (or (>e ,float-gensym-time most-positive-fixnum-as-float)
	       (<e ,float-gensym-time most-negative-fixnum-as-float))
	   most-negative-fixnum
	   (floore-first ,float-gensym-time)))))






;;;; Fast Predicates for Time to Tick




;;; This section implements fast predicates for determining if it is time to
;;; tick the G2 or real time clocks.

;;; The macro `update-g2-time-to-tick' should be called after changes have been
;;; made to the current-g2-time, the scheduler-quantum, or if it is recognized
;;; that an inconsistency has been introduced between fixnum-time and unix-time,
;;; possibly by someone changing this computer's system clock.  In any of these
;;; cases, the cached values for the g2-time-to-tick-p macro should be updated
;;; with a call to this macro.  The macro `update-g2-time-to-tick-to-asap' takes
;;; the current fixnum time and sets the cached values to allow a tick right
;;; away.  The macro `update-g2-time-to-tick-to-finest-grain-change' takes the
;;; current fixnum time and is used to set the cached values so that the next
;;; tick will be allowed as soon as the finest grain change in the fixnum-time
;;; occurs.

(defmacro update-g2-time-to-tick
    (unix-time-of-next-tick current-unix-time current-fixnum-time)
  `(progn
     (atomic-exchange fixnum-time-until-g2-time-tick
	   (floore-first
	     (*e (coerce-fixnum-to-gensym-float fixnum-time-units-per-second)
		 (maxe 0.0 (-e ,unix-time-of-next-tick ,current-unix-time)))))
     (atomic-exchange g2-time-to-tick-p-base ,current-fixnum-time)
     nil))

(defmacro update-g2-time-to-tick-to-asap (current-fixnum-time)
  `(progn
     (atomic-exchange fixnum-time-until-g2-time-tick 0)
     (atomic-exchange g2-time-to-tick-p-base ,current-fixnum-time)
     nil))

(defmacro update-g2-time-to-tick-to-finest-grain-change (current-fixnum-time)
  `(progn
     (atomic-exchange fixnum-time-until-g2-time-tick 1)
     (atomic-exchange g2-time-to-tick-p-base ,current-fixnum-time)
     nil))



;;; The macro `time-to-tick-g2-time-p' is a fast predicate to tell if the time
;;; has come to take a clock tick yet for the G2 time clock.  This predicate is
;;; based on the interval timer get-fixnum-time, and so may not be consistent
;;; with the conclusive judge of clock ticking, the funcions for actually
;;; ticking the clock.  This predicate is an optimized means of testing whether
;;; you should call the clock ticking functions.

(defmacro time-to-tick-g2-time-p (fixnum-time)
  `(>=f (fixnum-time-difference ,fixnum-time g2-time-to-tick-p-base)
	fixnum-time-until-g2-time-tick))




;;; The macro `update-real-time-to-tick' takes the current UNIX and fixnum times
;;; and will update the values used by the time-to-tick-real-time-p macro.

(defmacro update-real-time-to-tick (current-unix-time current-fixnum-time)
  (declare (ignore current-unix-time))
  `(atomic-exchange real-time-to-tick-p-base ,current-fixnum-time))




;;; The macro `time-to-tick-real-time-p' is a fast predicate to tell if the time
;;; has come to take a clock tick yet for the real-time clock.  This predicate
;;; is based on the interval timer get-fixnum-time, which gives us a faster but
;;; potentially less accurate check for when to tick the clock.  The reasons for
;;; variation could be if someone sets the system clock instead of adjusting it,
;;; for example.

(defmacro time-to-tick-real-time-p (fixnum-time)
  `(>=f (fixnum-time-difference ,fixnum-time real-time-to-tick-p-base)
	fixnum-time-until-real-time-tick))

(defmacro time-since-base-time-as-gensym-float ()
  `(-e
     (managed-float-value current-g2-time)
     (universal-time-to-unix-time
       (managed-float-value gensym-base-time-as-managed-float))))




;;;; Clock Initialization at Process and G2 Starts




;;; The following section implements operations for manipulating gensym-times.

;;; The function `initialize-gensym-time' is called to give initial values to
;;; the time storage functions when the G2 process is first launched.

(defun-void initialize-gensym-time ()
   (unless gensym-base-time-as-managed-float
    (with-temporary-gensym-float-creation initialize-gensym-time
      (let ((current-unix-time (ffloore-first (gensym-get-unix-time)))
	    (current-fixnum-time (get-fixnum-time t)))
	(declare (type gensym-float current-unix-time))
	(setq current-real-time (allocate-managed-float current-unix-time))
	(setq fixnum-time-of-last-real-time-tick current-fixnum-time)
	(setq current-g2-time (allocate-managed-float current-unix-time))
	(setq most-recent-g2-time (allocate-managed-float current-unix-time))
	(setq real-time-of-last-g2-tick
	      (allocate-managed-float current-unix-time))
	(setq fixnum-time-of-last-g2-tick current-fixnum-time)
	(setq g2-time-at-start (allocate-managed-float current-unix-time))
	(setq g2-time-at-start-as-text-string (make-wide-string 4))
	(multiple-value-bind (b1 b2 b3 b4)
	    (partition-managed-float g2-time-at-start)
	  (setf (charw g2-time-at-start-as-text-string 0)
		(code-wide-character b1))
	  (setf (charw g2-time-at-start-as-text-string 1)
		(code-wide-character b2))
	  (setf (charw g2-time-at-start-as-text-string 2)
		(code-wide-character b3))
	  (setf (charw g2-time-at-start-as-text-string 3)
		(code-wide-character b4)))	  
	(setq g2-time-to-tick-p-base current-fixnum-time)
	(setq real-time-to-tick-p-base current-fixnum-time)
	(setq gensym-base-time-as-managed-float
	      (allocate-managed-float
		(unix-time-to-universal-time current-unix-time)))
	(setq gensym-time 0)
	(setq gensym-time-at-start 0)))))




;;; The function `preset-gensym-time-for-initialization' should be called at the
;;; beginning of the process of starting G2.  This will set up a valid
;;; environment for the reference of gensym-time while activating frames and
;;; starting data servers, but does not start the tracking of real time with
;;; gensym time.  It is used to preset gensym-time and gensym-time-at-start so
;;; that they have some meaningful values during the process of starting the
;;; system.

;;; Note that when starting in the warmbooting? case, the values for the time
;;; variables will be drawn from variables set in prepare-to-read-snapshot-if-
;;; appropriate during the loading of the initial plist from the most recently
;;; loaded KB.  In this case, gensym-base-time-as-managed-float and
;;; gensym-time-at-start will already have been set, warmboot-simulated-time
;;; will hold the gensym-time at snapshot save if the KB was running in some
;;; scheduler mode other than real-time when saved, and warmboot-current-time
;;; will hold the gensym-time at snapshot save if we are currently starting this
;;; warmboot in "catch up" mode.

;;; This does not yet start gensym-time tracking real-time.  That is performed
;;; by resynchronize-gensym-time-and-actual-time, which should be called as the
;;; last thing done in the system-start function.

(defun-void preset-gensym-time-for-initialization ()
  (with-temporary-gensym-float-creation preset-gensym-time
    (cond
      (warmbooting?
       (cond
	 (warmbooting-with-catch-up?
	  (atomic-exchange gensym-time warmboot-current-time)
	  (mutate-managed-float-value
	    current-g2-time
	    (+e (universal-time-to-unix-time
		  (managed-float-value gensym-base-time-as-managed-float))
		(coerce-fixnum-to-gensym-float warmboot-current-time)))
	  (mutate-managed-float-value
	    most-recent-g2-time (managed-float-value current-g2-time))
	  (mutate-managed-float-value
	    real-time-of-last-g2-tick (gensym-get-unix-time))
	  (atomic-exchange fixnum-time-of-last-g2-tick (get-fixnum-time))
	  (mutate-managed-float-value
	    g2-time-at-start
	    (-e (managed-float-value current-g2-time)
		(coerce-fixnum-to-gensym-float
		  (-f gensym-time gensym-time-at-start)))))
	 ((neq 'real-time (determine-scheduler-mode-for-current-system))
	  (atomic-exchange gensym-time warmboot-simulated-time)
	  (mutate-managed-float-value
	    current-g2-time
	    (+e (universal-time-to-unix-time
		  (managed-float-value gensym-base-time-as-managed-float))
		(coerce-fixnum-to-gensym-float warmboot-simulated-time)))
	  (mutate-managed-float-value
	    most-recent-g2-time (managed-float-value current-g2-time))
	  (mutate-managed-float-value
	    real-time-of-last-g2-tick (gensym-get-unix-time))
	  (atomic-exchange fixnum-time-of-last-g2-tick (get-fixnum-time))
	  (mutate-managed-float-value
	    g2-time-at-start
	    (-e (managed-float-value current-g2-time)
		(coerce-fixnum-to-gensym-float
		  (-f gensym-time gensym-time-at-start)))))
	 (t
	  (atomic-exchange gensym-time gensym-time-at-start)
	  (mutate-managed-float-value
	    current-g2-time
	    (+e (universal-time-to-unix-time
		  (managed-float-value gensym-base-time-as-managed-float))
		(coerce-fixnum-to-gensym-float gensym-time-at-start)))
	  (mutate-managed-float-value
	    most-recent-g2-time (managed-float-value current-g2-time))
	  (mutate-managed-float-value
	    real-time-of-last-g2-tick (gensym-get-unix-time))
	  (atomic-exchange fixnum-time-of-last-g2-tick (get-fixnum-time))
	  (mutate-managed-float-value
	    g2-time-at-start (managed-float-value current-g2-time)))))
      (t
       (let* ((current-time (gensym-get-unix-time))
	      (current-fixnum-time (get-fixnum-time t))
	      (floored-current-time (ffloore-first current-time)))
	 (declare (type gensym-float current-time floored-current-time))
	 (mutate-managed-float-value
	   gensym-base-time-as-managed-float
	   (-e (unix-time-to-universal-time floored-current-time)
	       (coerce-fixnum-to-gensym-float gensym-time)))
	 (atomic-exchange gensym-time-at-start gensym-time)
	 (mutate-managed-float-value current-g2-time floored-current-time)
	 (mutate-managed-float-value most-recent-g2-time floored-current-time)
	 (mutate-managed-float-value real-time-of-last-g2-tick current-time)
	 (atomic-exchange fixnum-time-of-last-g2-tick current-fixnum-time)
	 (mutate-managed-float-value g2-time-at-start floored-current-time))))))


;;;; Clock Ticking Functions




;;; This section contains functions that tick the G2 and real time clocks.

;;; The variable `force-clock-tick' is used when changing the G2 scheduler-mode.
;;; When this happens while G2 is running we have to get a call to the G2 time
;;; clock ticking functions as soon as possible.  Setting this variable to T
;;; will cause G2 to not sleep until one of the G2 clock ticking functions has
;;; been called.

(defvar force-clock-tick nil)




;;; The function `tick-the-real-time-clock' is called to advance
;;; current-real-time.  If sufficient time as passed to justify the advancing of
;;; this clock, then current-real-time will be given a new value and this macro
;;; will return true.  However, if the real-time-clock was ticked recently
;;; enough to not justify another tick now, then this macro does not modify
;;; current-real-time and returns NIL.

;; Discussion: In a sense, it is always time to tick the real-time clock.
;; However, there are performance concerns about continually making the system
;; calls required to fetch the system time needed to tick this clock.  The
;; interval timer get-fixnum-time has been optimized to not make a system call
;; when its last cached timestamp is still relatively new (50 milliseconds is
;; the currently allowed age).  So, we use get-fixnum-time to check if a "long
;; enough" interval of time has passed before ticking the clock.  This interval
;; is represented as the shortest fixnum time interval allowed, 1
;; fixnum-time-unit.  However, since we limit the rate at which times returned
;; from get-fixnum-time are allowed to update, the actual limit is that
;; determined by the internals of get-fixnum-time.  This set of assumptions
;; about system calls and times may be inaccurate on some platforms (i.e. the
;; overhead may be low) but for most platforms our assumptions about system
;; calls have been born out in performance metering, and it is worth the extra
;; effort to limit system calls.  -jra 3/7/94

;;; When the current time is greater than the value in current-real-time, then
;;; tick forward normally and adjust the time-to-tick cached values.

;;; When the current time is equal to the value in current-real-time, do
;;; nothing.  No time has passed as far as the system clock is concerned.  This
;;; can occur if the get-fixnum-time clock returns new values at a more finely
;;; grained interval than the UNIX time calendar clock (which recent experience
;;; shows to be unlikely but possible).  Do not adjust the
;;; time-to-tick-real-time, just wait for the system clock to to eventually
;;; advance.

;;; When the current time is less than the value in current-real-time, then EEK!
;;; Time has gone backwards!  Someone has set the system clock backwards on this
;;; computer, so go ahead and back up the real-time clocks.  At this point we
;;; could also consider modifying some data structures in G2 to react this
;;; situation, for example moving back the task times of all tasks currently in
;;; the scheduler, adjusting the G2 time, or adjusting the timestamps of values
;;; in histories and graphs.  A difficult set of choices...  -jra 3/10/94

;;; Ok, here are some choices.  A significant clock discontinuity will be one
;;; where the difference between elapsed fixnum time and elapsed unix time is
;;; more than 2 seconds and the difference is more than 10% of the elapsed
;;; fixnum-time, unless the difference in fixnum time is more than 24 hours into
;;; the future, which is the limit of accuracy of the fixnum time clock.  So, if
;;; a significant discontinuity exists between the fixnum and unix clocks, then
;;; the function real-time-clock-discontinuity will be called with the observed
;;; discontinuity in the calendar clock.  -jra 9/9/94

;;; Changed 100 milliseconds above into 2 seconds, which matches the code.  -jra
;;; 10/23/96

(defun-simple tick-the-real-time-clock (current-fixnum-time)
  (with-clock-sync
  (when (time-to-tick-real-time-p current-fixnum-time)
    (with-temporary-gensym-float-creation tick-the-real-time-clock
      (let* ((current-unix-time (gensym-get-unix-time))
	     (most-recent-real-time (managed-float-value current-real-time))
	     (unix-time-delta (-e current-unix-time most-recent-real-time))
	     (fixnum-time-delta
	       (/e (coerce-fixnum-to-gensym-float
		     (fixnum-time-difference
		       current-fixnum-time
		       fixnum-time-of-last-real-time-tick))
		   (coerce-fixnum-to-gensym-float
		     fixnum-time-units-per-second)))
	     (clock-difference (-e unix-time-delta fixnum-time-delta))
	     (absolute-difference (abse clock-difference)))
	(declare (type gensym-float current-unix-time most-recent-real-time
		       unix-time-delta fixnum-time-delta
		       clock-difference absolute-difference))
	(when (and (>e absolute-difference 2d0)
		   (or (<e unix-time-delta 0d0)
		       (and (>e absolute-difference (*e fixnum-time-delta 0.1d0))
			    (<e fixnum-time-delta 86400d0)))) ; 24 hours
	  (let ((discontinuity (allocate-managed-float clock-difference)))
	    (real-time-clock-discontinuity discontinuity)
	    (reclaim-managed-float discontinuity)))
	(unless (=e current-unix-time most-recent-real-time)
	  (mutate-managed-float-value current-real-time current-unix-time)
	  (atomic-exchange fixnum-time-of-last-real-time-tick current-fixnum-time)
	  (update-real-time-to-tick current-unix-time current-fixnum-time)
	  t))))))

(defun-void tick-the-clock-for-tw-or-gsi ()
  (let ((local-fixnum-time (get-fixnum-time t)))
    (when (time-to-tick-real-time-p local-fixnum-time)
      (when (tick-the-real-time-clock local-fixnum-time)
	(unpack-future-tasks-into-current-task-queues nil)))))




;;; The void function `real-time-clock-discontinuity' is called with a managed
;;; float giving the difference perceived between the clock functions
;;; get-fixnum-time (a chronometer measuring the true passage of real time) and
;;; gensym-get-unix-time (the calendar clock time).  This typically indicates
;;; that someone has set the calendar clock on the

(defun-void real-time-clock-discontinuity (managed-float)
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (adjust-task-times-after-clock-discontinuity
    managed-float future-real-time-tasks)))

(defmacro perform-g2-specific-adjustments-for-g2-only (managed-float)
  `(current-system-case
    (ab
     (add-delta-time-to-variables-and-parameters ,managed-float)
     (update-trend-charts-for-clock-discontinuity ,managed-float))
    (t nil)))

;;; The void function `g2-time-clock-discontinuity' is called with a managed
;;; float giving the time difference detected whenever a leap is occurs in
;;; g2-time.  When this happens all those stored timestamps that should maintain
;;; a continuous appearance to the passage of time must be adjusted by the
;;; amount given.  This can happen when a user sets a system clock on the
;;; computer running G2, or if the scheduler mode is changed.  As an example of
;;; an operation done within this function, scheduler task times are stored as
;;; UNIX times, but users perceive them as being more interval-like than
;;; wall-clock like, and so all task times are adjusted.

(defun-void g2-time-clock-discontinuity (managed-float)
  (adjust-g2-clock-times-after-discontinuity-1 managed-float)
  (adjust-task-times-after-clock-discontinuity
    managed-float future-g2-time-tasks)
  (perform-g2-specific-adjustments-for-g2-only managed-float))





;;; The function adjust-g2-clock-times-after-discontinuity-1 is the function
;;; that will adjust the internals of clocks in response to a discontinuity.
;;; An adjustment is made to gensym-base-time so that the interpretation of all
;;; gensym-time based timestamps will be shifted.  Similarly, g2-time-at-start
;;; is adjusted so that the amount of continuous time that G2 has been up does
;;; not jump due to the clock discontinuity.

(defun-void adjust-g2-clock-times-after-discontinuity-1 (managed-float)
  (let ((integral-seconds-of-difference
	  (coerce-fixnum-to-gensym-float
	    (-f (convert-unix-time-to-gensym-time
		  (+e (managed-float-value current-g2-time)
		      (managed-float-value managed-float)))
		gensym-time))))
    (declare (type gensym-float integral-seconds-of-difference))
    (mutate-managed-float-value
      gensym-base-time-as-managed-float
      (+e (managed-float-value gensym-base-time-as-managed-float)
	  integral-seconds-of-difference))
    (mutate-managed-float-value
      g2-time-at-start 
      (+e (managed-float-value g2-time-at-start)
          integral-seconds-of-difference))))






;;; The function `tick-the-g2-real-time-clock' is called in run-scheduler-1 to
;;; tick the clock, updating gensym-time.  For efficiency, this function should
;;; only be called when time-to-tick-g2-time-p has returned true, but it will
;;; not malfunction if this is not the case.  This function will return true if
;;; the clock actually has been moved ahead, or NIL if it has not ticked the
;;; clock.

(defun-simple tick-the-g2-real-time-clock (current-fixnum-time)
  (with-clock-sync
  (with-temporary-gensym-float-creation tick-the-g2-real-time-clock
    (let* ((current-unix-time (gensym-get-unix-time))
	   (cached-g2-time (managed-float-value current-g2-time))
	   (millisecond-minimum-scheduling-interval?
	     (determine-minimum-scheduling-interval-for-current-system))
	   (float-minimum-scheduling-interval
	     (if millisecond-minimum-scheduling-interval?
		 (/e (coerce-fixnum-to-gensym-float
		       millisecond-minimum-scheduling-interval?)
		     1000d0)
		 0d0)))
      (declare (type gensym-float current-unix-time cached-g2-time
		     float-minimum-scheduling-interval))
      (atomic-exchange force-clock-tick nil)
      (cond
	((if millisecond-minimum-scheduling-interval?
	     (or (>=e current-unix-time
		      (+e cached-g2-time float-minimum-scheduling-interval))
		 (<e current-unix-time
		     (-e cached-g2-time float-minimum-scheduling-interval)))
	     (/=e current-unix-time cached-g2-time))
	 (let* ((tick-time
		  (next-tick-at-or-before-time
		    current-unix-time millisecond-minimum-scheduling-interval?
		    float-minimum-scheduling-interval))
		(unix-time-delta (-e tick-time cached-g2-time))
		(fixnum-time-delta
		  (/e (coerce-fixnum-to-gensym-float
			(fixnum-time-difference
			  current-fixnum-time fixnum-time-of-last-g2-tick))
		      (coerce-fixnum-to-gensym-float
			fixnum-time-units-per-second)))
		(clock-difference (-e unix-time-delta fixnum-time-delta))
		(absolute-difference (abse clock-difference)))
	   (declare (type gensym-float tick-time unix-time-delta
			  fixnum-time-delta clock-difference
			  absolute-difference))
	   (when (and (>e absolute-difference 2d0)
		      (or (<e unix-time-delta
			      (if millisecond-minimum-scheduling-interval?
				  (-e float-minimum-scheduling-interval)
				  0d0))
			  (and (>e absolute-difference (*e fixnum-time-delta 0.1d0))
			       (<e fixnum-time-delta 8.64e7))))	; 24 hours
	      (let ((discontinuity (allocate-managed-float
				     (-e tick-time cached-g2-time))))
		(g2-time-clock-discontinuity discontinuity)
		(reclaim-managed-float discontinuity)))
	   (mutate-managed-float-value current-g2-time tick-time)
	   (mutate-managed-float-value most-recent-g2-time cached-g2-time)
	   (mutate-managed-float-value real-time-of-last-g2-tick
				       current-unix-time)
	   (atomic-exchange fixnum-time-of-last-g2-tick current-fixnum-time)
	   (atomic-exchange gensym-time
		(convert-unix-time-to-gensym-time tick-time))
	   (if millisecond-minimum-scheduling-interval?
	       (update-g2-time-to-tick
		 (+e tick-time float-minimum-scheduling-interval)
		 current-unix-time
		 current-fixnum-time)
	       (update-g2-time-to-tick-to-finest-grain-change
		 current-fixnum-time))
	   t))
	(t
	 nil))))))




;;; The function `tick-the-g2-fast-time-clock' is called in run-schedule-cycle
;;; to tick the clock when running in as fast as possible mode.  For efficiency,
;;; this function should only be called when time-to-tick-g2-time-p has returned
;;; true, but it will not malfunction if this is not the case.  This function
;;; will return true if the clock actually has been moved ahead, or NIL if it
;;; has not ticked the clock.

(defun-simple tick-the-g2-fast-time-clock (current-fixnum-time)
  (with-clock-sync
  (with-temporary-gensym-float-creation tick-the-g2-fast-time-clock
    (let* ((future-g2-tasks-exist?
	     (future-tasks-exist-p future-g2-time-tasks))
	   (next-scheduled-task-time
	     (if future-g2-tasks-exist?
		 (unix-time-of-next-future-task future-g2-tasks-exist?)
		 0d0))
	   (millisecond-minimum-scheduling-interval?
	     (determine-minimum-scheduling-interval-for-current-system))
	   (float-minimum-scheduling-interval
	     (if millisecond-minimum-scheduling-interval?
		 (/e (coerce-fixnum-to-gensym-float
		       millisecond-minimum-scheduling-interval?)
		     1000d0)
		 0d0)))
      (declare (type gensym-float next-scheduled-task-time
		     float-minimum-scheduling-interval))
      (atomic-exchange force-clock-tick nil)
      (cond (future-g2-tasks-exist?
	     (let ((tick-time
		     (next-tick-at-or-after-time 
		       next-scheduled-task-time
		       millisecond-minimum-scheduling-interval?
		       float-minimum-scheduling-interval)))
	       (declare (type gensym-float tick-time))
	       (mutate-managed-float-value
		 most-recent-g2-time
		 (managed-float-value current-g2-time))
	       (mutate-managed-float-value current-g2-time tick-time)
	       (mutate-managed-float-value
		 real-time-of-last-g2-tick (gensym-get-unix-time))
	       (atomic-exchange fixnum-time-of-last-g2-tick current-fixnum-time)
	       (atomic-exchange gensym-time
		     (convert-unix-time-to-gensym-time tick-time))
	       (update-g2-time-to-tick-to-asap current-fixnum-time)
	       t))
	    (t
	     nil))))))




;;; The function `tick-the-g2-simulated-time-clock' is called from
;;; run-scheduler-1 to tick the clock when G2 is executing in simulated-time
;;; mode.  In simulated time, the clock is ticked when all current tasks are
;;; completed, but not faster than real-time.

(defun-simple tick-the-g2-simulated-time-clock (current-fixnum-time)
  (with-clock-sync
  (with-temporary-gensym-float-creation tick-the-g2-simulated-time-clock
    (let* ((current-unix-time (gensym-get-unix-time))
	   (elapsed-time-in-tick
	     (-e current-unix-time
		 (managed-float-value real-time-of-last-g2-tick)))
	   (g2-time (managed-float-value current-g2-time))
	   (elapsed-g2-time (+e g2-time elapsed-time-in-tick))
	   (future-g2-tasks-exist?
	     (future-tasks-exist-p future-g2-time-tasks))
	   (next-scheduled-task-time
	     (if future-g2-tasks-exist?
		 (unix-time-of-next-future-task future-g2-tasks-exist?)
		 0d0))
	   (millisecond-minimum-scheduling-interval?
	     (determine-minimum-scheduling-interval-for-current-system))
	   (float-minimum-scheduling-interval
	     (if millisecond-minimum-scheduling-interval?
		 (/e (coerce-fixnum-to-gensym-float
		       millisecond-minimum-scheduling-interval?)
		     1000d0)
		 0d0))
	   (potenial-elapsed-tick-time
	     (next-tick-at-or-before-time
	       elapsed-g2-time millisecond-minimum-scheduling-interval?
	       float-minimum-scheduling-interval))
	   (potential-schedule-tick-time
	     (next-tick-at-or-after-time
	       next-scheduled-task-time millisecond-minimum-scheduling-interval?
	       float-minimum-scheduling-interval))
	   (new-g2-time
	     (if future-g2-tasks-exist?
		 (mine potenial-elapsed-tick-time potential-schedule-tick-time)
		 potenial-elapsed-tick-time)))
      (declare (type gensym-float current-unix-time elapsed-time-in-tick
		     g2-time elapsed-g2-time next-scheduled-task-time
		     float-minimum-scheduling-interval
		     potenial-elapsed-tick-time potential-schedule-tick-time))
      (atomic-exchange force-clock-tick nil)
      (cond ((>e new-g2-time g2-time)
	     (mutate-managed-float-value most-recent-g2-time g2-time)
	     (mutate-managed-float-value current-g2-time new-g2-time)
	     (mutate-managed-float-value real-time-of-last-g2-tick
					 current-unix-time)
	     (atomic-exchange fixnum-time-of-last-g2-tick current-fixnum-time)
	     (atomic-exchange gensym-time
		   (convert-unix-time-to-gensym-time new-g2-time))
	     (if millisecond-minimum-scheduling-interval?
		 (update-g2-time-to-tick
		   (+e current-unix-time float-minimum-scheduling-interval)
		   current-unix-time
		   current-fixnum-time)
		 (update-g2-time-to-tick-to-finest-grain-change
		   current-fixnum-time))
	     t)
	    (t
	     nil))))))




;;; The `NUPEC Catch Up Scheduler Mode' has been implemented as part of a
;;; consulting project to provide enhancements to G2 for NUPEC.  This mode is
;;; used to run the system in as fast as possible mode until the system has
;;; caught up with the real time clock, after which it runs in real time.  This
;;; is used to load snapshot files, and then run as fast as possible reading
;;; other input files until it is caught up to real time.  When the system is
;;; started it will either be in or will immediately set itself into real time
;;; mode.  When a snapshot file is loaded, the function change-current-time-in-
;;; nupec-catch-up-mode is called with the new time in the past that G2 should
;;; roll back to.  This will change the time and set the variable which says
;;; that G2 is still trying to catch up.  When caught up, it again sets the
;;; variable back and will run in real time.

;;; The system variable `nupec-catch-up-mode-caught-up?' is used to store a flag
;;; reflecting when nupec catch up mode has indeed caught up and is now running
;;; in real time mode.

(def-system-variable nupec-catch-up-mode-caught-up? clocks nil)




;;; The function `tick-the-nupec-catch-up-clock' is used to perform clock ticks.
;;; If the system is not caught up, it checks to see if we have now caught up,
;;; and if so changes the variable nupec-catch-up-mode-caught-up? to say that it
;;; is caught up.  Then, if the system is caught up, it calls the tick-the
;;; real-time-clock function.  If the system is not caught up, it calls
;;; tick-the-fast-time-clock.

(defun-simple tick-the-nupec-catch-up-clock (fixnum-time-units-time-stamp)
  (with-clock-sync
  (when (and (null nupec-catch-up-mode-caught-up?)
	     (>=f gensym-time
		  (get-real-gensym-time)))
    (setq nupec-catch-up-mode-caught-up? t))
  (if nupec-catch-up-mode-caught-up?
      (tick-the-g2-real-time-clock fixnum-time-units-time-stamp)
      (tick-the-g2-fast-time-clock fixnum-time-units-time-stamp))))




;;; The function `change-current-time-in-nupec-catch-up-mode' takes a target
;;; gensym-time, and changes the clocks variables such that the existing
;;; gensym-time will be interpreted as the given gensym-time.  This function is
;;; here for the NUPEC Snapshot/Reload facility to set the current time so that
;;; a catchup may happen after loading a snapshot file.  The given target time
;;; must be less than or equal to the current gensym time.

;;; Internally, this function will change the *gensym-base-time* to change the
;;; interpretation of the existing gensym-time values.  Note that we cannot just
;;; decrement gensym-time, since that would hose the scheduler mightily.  This
;;; function should also set the nupec-catch-up-mode-caught-up? variable to NIL,
;;; so that the system will enter "as fast as possible mode" until caught up
;;; again to real time.

(defun-void change-current-time-in-nupec-catch-up-mode
    (target-gensym-time)
  (with-clock-sync
  (let ((clock-adjustment (-f target-gensym-time gensym-time)))
    (unless (=f clock-adjustment 0)
      (with-temporary-gensym-float-creation change-nupec-time
	(let ((float-adjustment
		(coerce-fixnum-to-gensym-float clock-adjustment)))
	  (mutate-managed-float-value
	    gensym-base-time-as-managed-float
	    (+e (managed-float-value gensym-base-time-as-managed-float)
		float-adjustment))
	  (let ((managed-float-adjustment
		  (allocate-managed-float float-adjustment)))
	    (g2-time-clock-discontinuity managed-float-adjustment)
	    (reclaim-managed-float managed-float-adjustment))

	  (mutate-managed-float-value
	    current-g2-time
	    (-e (managed-float-value current-g2-time) float-adjustment))
	  (mutate-managed-float-value
	    most-recent-g2-time
	    (managed-float-value current-g2-time))
	  (mutate-managed-float-value
	    real-time-of-last-g2-tick (gensym-get-unix-time))
	  (atomic-exchange fixnum-time-of-last-g2-tick (get-fixnum-time t))
	  (update-g2-time-to-tick-to-asap (get-fixnum-time))))))
  (setq nupec-catch-up-mode-caught-up? nil)))




;;; The function `update-g2-time-to-tick-after-scheduling-change' is used to
;;; reset the G2 time to tick cached values after a change in the scheduler mode
;;; or the minimum scheduling interval.

(defun-void update-g2-time-to-tick-after-scheduling-change ()
  (with-clock-sync
  (when (or system-is-running system-has-paused)
    (with-temporary-gensym-float-creation update-g2-time-to-tick
      (let* ((current-fixnum-time (get-fixnum-time))
	     (current-unix-time (gensym-get-unix-time))
	     (g2-time (managed-float-value current-g2-time))
	     (millisecond-minimum-scheduling-interval?
	       (determine-minimum-scheduling-interval-for-current-system))
	     (float-minimum-scheduling-interval
	       (if millisecond-minimum-scheduling-interval?
		   (/e (coerce-fixnum-to-gensym-float
			 millisecond-minimum-scheduling-interval?)
		       1000.0)
		   0.0))
	     (mode (determine-scheduler-mode-for-current-system)))
	(declare (type gensym-float current-unix-time g2-time
		       float-minimum-scheduling-interval))
	(case mode
	  ((real-time)
	   ;; If we are changing into real-time mode from another mode, for
	   ;; example as-fast-as-possible, we want to get into the
	   ;; tick-the-g2-real-time clock function, where it will clean up all
	   ;; of the little messes left behind by changing models of time on the
	   ;; fly.  This code used to call update-g2-time-to-tick, but that
	   ;; allowed us to sleep for a long time when the g2-time had ticked
	   ;; far ahead of real-time.  Instead, we want
	   ;; tick-the-g2-real-time-clock to recognize the time discontinuity
	   ;; and deal with it was soon as possible.  -jallard&ncc 8/25/97
	   (if (>e current-unix-time g2-time)
	       (update-g2-time-to-tick-to-asap current-fixnum-time)
	       (update-g2-time-to-tick-to-finest-grain-change
		 current-fixnum-time)))
	  ((fast-time)
	   (update-g2-time-to-tick-to-asap current-fixnum-time))
	  ((simulated-time)
	   (if millisecond-minimum-scheduling-interval?
	       (update-g2-time-to-tick
		 (+e (managed-float-value real-time-of-last-g2-tick)
		     float-minimum-scheduling-interval)
		 current-unix-time
		 current-fixnum-time)
	       (if (>e current-unix-time
		       (managed-float-value real-time-of-last-g2-tick))
		   (update-g2-time-to-tick-to-asap current-fixnum-time)
		   (update-g2-time-to-tick-to-finest-grain-change
		     current-fixnum-time))))
	  ((nupec-catch-up)
	   (if nupec-catch-up-mode-caught-up?
	       (if millisecond-minimum-scheduling-interval?
		   (update-g2-time-to-tick
		     (+e g2-time float-minimum-scheduling-interval)
		     current-unix-time
		     current-fixnum-time)
		   (if (>e current-unix-time g2-time)
		       (update-g2-time-to-tick-to-asap current-fixnum-time)
		       (update-g2-time-to-tick-to-finest-grain-change
			 current-fixnum-time)))
	       (update-g2-time-to-tick-to-asap current-fixnum-time)))
	  (t
	   (error "Unknown scheduler mode in update-g2-time-to-tick ~a"
		mode))))))))


;;; The system variable `inhibit-non-real-time-clock-ticks?' is used to stop the
;;; clock from ticking in fast-time and simulated-time scheduler modes.  This is
;;; currently used by the simulator to stop the clock from ticking while the
;;; simulator is waiting for GSPAN or simulation-procedure RPCs to return from
;;; external systems.  This variable keeps the clock from racing during these
;;; intervals, and allows G2 to idle the process.

(def-system-variable inhibit-non-real-time-clock-ticks? cycles nil)



;;; The macro `milliseconds-to-next-task' returns a fixnum count of milliseconds
;;; until the next scheduled future task, or NIL if there is nothing scheduled
;;; to occur in G2's future.  If the next task is somewhat far into the future,
;;; this macro returns a maximum value of 1 hour.  Note that this operation can
;;; return a negative number when tasks in the future queues are ready to be
;;; unpacked into current queues.

;;; When G2 is not running, the result of this operation is determined by the
;;; time of the next future-real-time task.  When G2 is running, then it is also
;;; determined by the future-g2-time tasks and the scheduler mode.  When in real
;;; time mode, the seconds to next task are determined by difference between the
;;; current time and the next scheduled task time.  This is also true of
;;; nupec-catch-up mode, since we will only call this operation when G2 has
;;; already caught up to real time and it is operating as if it were in real
;;; time mode.  When in fast-time, this operation can be called when we are
;;; waiting for an external system to respond to some network requests, so the
;;; maximum of 1 hour can be used.  When in simulated time mode, the seconds
;;; until the next tick is the time of the next G2 task, minus the current G2
;;; time, minus the difference between the current real time and the real time
;;; at the most recent clock tick.

;; The 1 hour limit is imposed to guarantee that the returned time is always
;; within a fixnum time range.  -jra 10/22/96

(defun-simple milliseconds-to-next-task ()
  (with-clock-sync
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (with-temporary-gensym-float-creation milliseconds-to-next-task
    (let ((scheduler-mode (determine-scheduler-mode-for-current-system))
	  (future-g2-time-tasks?
	    (future-tasks-exist-p future-g2-time-tasks))
	  (future-real-time-tasks?
	    (future-tasks-exist-p future-real-time-tasks)))
      (cond
	((and system-is-running
	      (or force-clock-tick
		  (and (eq scheduler-mode 'fast-time)
		       future-g2-time-tasks?
		       (not inhibit-non-real-time-clock-ticks?))))
	 0)
	((or future-real-time-tasks?
	     (and future-g2-time-tasks? system-is-running))
	 (let* ((unix-time (gensym-get-unix-time))
		(max-sleep 3600.0)
		(seconds-to-next-real-time-task
		  (if future-real-time-tasks?
		      (mine
			(-e (unix-time-of-next-future-task future-real-time-tasks?)
			    unix-time)
			max-sleep)
		      max-sleep)))
	   (declare (type gensym-float unix-time max-sleep
			  seconds-to-next-real-time-task))
	   (if system-is-running
	       (let ((seconds-to-next-g2-task max-sleep))
		 (declare (type gensym-float seconds-to-next-g2-task))
		 (when (setq future-g2-time-tasks?
			     (future-tasks-exist-p future-g2-time-tasks))
		   (case scheduler-mode
		     ((real-time nupec-catch-up)
		      (setq seconds-to-next-g2-task
			    (-e (unix-time-of-next-future-task future-g2-time-tasks?)
				unix-time)))
		     ((simulated-time)
		      (setq seconds-to-next-g2-task
			    (-e (unix-time-of-next-future-task future-g2-time-tasks?)
				(managed-float-value current-g2-time)
				(-e unix-time
				    (managed-float-value
				      real-time-of-last-g2-tick)))))))
		 (floore-first
		   (*e 1000.0
		       (mine seconds-to-next-real-time-task
			     seconds-to-next-g2-task))))
	       (floore-first
		 (*e 1000.0 seconds-to-next-real-time-task)))))
	(t nil)))))))






;;;; Gensym Time Utilities




;;; This section implements utilities and variables used to manipulate gensym
;;; times.

;;; The value of *some-time-ago* is used a resetting value for the expirations
;;; and collection timestamps for variables when they have no value.  This used
;;; to be two weeks before the start of G2, but have been changed to now be 2
;;; weeks after most-negative-fixnum.  This puts the time WAY back into the past
;;; and is unlikely to collide with an actual timestamp of a real value.  -jra
;;; 2/1/90

;;; Note that we could change this value to the moment of the big bang if we
;;; cared to since we now use floats in our timestamps.  -jra 6/11/95

;;; The variable *some-time-ago* will be used in VARIABLES as literal values,
;;; having 64-bit most-negative-fixnum here will cause many regression test
;;; failures. The only solution to get the same translation for 32 and 64-bit
;;; translated C code, is to use most-negative-fixnum32.  -binghe 5/21/2016

(defparameter *some-time-ago*
  (+f most-negative-fixnum32 (*f 2 7 24 60 60)))		; two weeks




;;; The function `get-real-gensym-time' gets the current real time from the
;;; system and returns it in gensym-time format.

(defun-simple get-real-gensym-time ()
  (with-temporary-gensym-float-creation get-real-gensym-time
    (convert-unix-time-to-gensym-time (gensym-get-unix-time))))





;;; The function `decode-gensym-time' takes a gensym-time as its argument and
;;; returns the given time split up into its calendar components.  See the
;;; documentation for decode-gensym-time-leaving-bignums above for details on
;;; the returned values of this function.  The returned values from this
;;; function are second, minute, hour, date, month, year, day-of-week,
;;; daylight-savings-time-p, and the time-zone.

(defun decode-gensym-time (gensym-time)
  (let (second minute hour date month year day-of-week
	daylight-savings-time-p time-zone)
    (with-temporary-gensym-float-creation decode-gensym-time
      (multiple-value-setq
	(second minute hour date month year day-of-week
		daylight-savings-time-p time-zone)
	(gensym-decode-unix-time
	  (convert-gensym-time-to-unix-time gensym-time))))
    (values second minute hour date month year day-of-week
	    daylight-savings-time-p time-zone)))

(defun-simple same-gensym-date-p (gensym-time-1 gensym-time-2)
  (multiple-value-bind (seconds-1 minutes-1 hours-1 day-1 month-1 year-1)
      (decode-gensym-time gensym-time-1)
    (declare (ignore seconds-1 minutes-1 hours-1))
    (multiple-value-bind (seconds-2 minutes-2 hours-2 day-2 month-2 year-2)
	(decode-gensym-time gensym-time-2)
      (declare (ignore seconds-2 minutes-2 hours-2))
      (and (=f month-1 month-2) (=f day-1 day-2) (=f year-1 year-2)))))




;;; The function `encode-gensym-time' takes the arguments second, minute, hour,
;;; date, month, and year, and returns a gensym-time encoding these time
;;; components.

(defun-simple encode-gensym-time (second minute hour date month year)
  (with-temporary-gensym-float-creation encode-gensym-time
    (convert-unix-time-to-gensym-time
      (gensym-encode-unix-time second minute hour date month year))))

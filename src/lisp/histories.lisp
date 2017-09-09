;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module HISTORIES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann



;;;; Overview

;;; Cascaded ring buffer mechanism is currently not used.  Consider hooking up
;;; at some time in the future.  See notes in Cascaded Ring Buffer Accessors
;;; section below.  Note that the cascaded-ring-buffer data structure is used.
;;; The accessors however are simplified and always assume only one ring buffer.



;; Notes

;; Test kbs are
;;   "ma:>agh>history-test.kb"
;;   "ma:>ab>flow.kb"
;;   "ma:>ab>control-sim.kb"


;; To Do

;; Bug that Eric ran into with it returning values from before start
;; time.  This also happens in Chaim's kb.  (verify that fixed)

;; For historic interval functions, when searching for interval, go from newest
;; to oldest rather than the other way, since the interval tends to be at the
;; "new" end of the history ("during the last n seconds" is common).  Use binary
;; search to get newest datapoint, then procede backward linearly.  (see
;; accumulate-historical-result).  Also, in accumulate-historical-result, break
;; out of loop if interval is skipped completely.  Currently, it doesn't break
;; out until it gets to newest-active-element-index.  See how this is done in
;; get-number-of-datapoints-in-interval.  Note that
;; get-number-of-datapoints-in-interval does not have its own with-temporary
;; wrapper since it assumes that no number consing is done inside it.  If this
;; changes (if we use a double float representation for numbers)
;; get-number-of-datapoints-in-interval will have to be replaced with
;; accumulate-historical-result.  Accumulate-historical-result should then be
;; fitted with an option where it does not access history values, only history
;; times.

;; Review grammar for the following: "the value of x as of 10 seconds seconds
;; ...".  This currently is parsed and compiled.

;; Consider providing an option which allocates histories specified with a
;; maximum number of data points upon knowledge base load, or at least upon
;; activation, rather than the first time that a value is put into the variable.
;; This should be an option which does a similar thing for other parts of G2 as
;; well, for example, allocating some maximum number of transient objects up
;; front.

;; The slot data-type-of-variable-or-parameter should have a slot putter which
;; clears histories.  This prevents having different types of values in one
;; history buffer.  When this is done, return-history-value should never have to
;; check if value is a number.

;; The numeric history functions (average, max, etc.) when checking values of
;; the form "during the last 10 seconds" will fail if there is no datapoint in
;; the last 10 seconds, even if there is a value before this time which hasn't
;; expired.  This is a difficult issue.

;; In slot value compilers for history specs, return bad compile if maximum
;; number of data points specified is greater than
;; largest-ring-buffer-vector-size.

;; In make-or-reformat-cascaded-ring-buffer, when maximum number of data points
;; is specified, if existing history buffer is not empty, change its size while
;; preserving data points.  Extend the existing ring buffer enlarge mechanism to
;; allow for both enlarging and shrinking.  This should be low priority,
;; however, since it is an optimization for editing while running.

;; Get rid of the slots specifications-for-cascaded-ring-buffer and
;; specifications-for-individual-ring-buffers-in-cascade in
;; cascaded-ring-buffers.  These are no longer used.

;; Don't allocate cascaded ring buffer structure if it isn't needed.  History
;; slot should be able to contain either a cascaded ring buffer, or an 
;; ordinary ring buffer.

;; Level 1 warnings issued by history functions should become procedure errors
;; when the function is called from a procedure.

;; Make regression test out of "ma:>agh>history-test.kb".

;; Minor problem with store-history-element-in-cascaded-ring-buffer.  In cases
;; where old data is being stored, it is possible for the ring buffer to become
;; one data point shorter than the maximum specified.  This is because this
;; function always first reduces the length by one before storing the new data
;; point.  Afterwards, when the data point overwrites an existing one, no new
;; element is added and the buffer is one shorter than the maximum allowed.

;; History evaluators in inference engine should be abstracted better.

;; Save every datapoint in history (don't overwrite) (need sub-second time
;; intervals for this).
;; (Both possible in version 4.0.  - cpm, 5/24/94)

;; Consider doing some of the error checks currently done in the inference
;; engine and simulation evaluators for history functions in the history
;; functions themselves.  This may eliminate some redundant code.  This is
;; complicated however by the fact that the inference engine and simulator
;; use different type checking.  In any case, try to abstract the error
;; messages.

;; Review slot value compiler for history specification.  Currently guards
;; against non-positive maximum number of data points.  Need better guard
;; for non-positive interval.  Review when doing new cascaded ring buffers
;; for data filtering.

;; Review rule about only allowing one data point per history time
;; (see documentation for store-history-element-in-cascaded-ring-buffer).
;; The problem is that resolution will always be finite, even if history time
;; increments of less than a second are allowed.  Overwriting data points does
;; result in a loss of information but it is currently done since the history
;; functions and the graphs assume one data point per history time.  It would
;; probably not be difficult to allow for more.
;; (NOTE: this is being allowed in version 4.0.  - cpm, 5/24/94)

;; Use interval subdivision technique from
;; get-ring-buffer-element-at-history-time in the history functions, especially
;; get-historical-delayed-value, to improve efficiency.  These currently just
;; find values by iterating from the newest value back.  The interval
;; subdivision is a log-n technique whereas the current algorithms are of order
;; n.  For history functions like rate of change or average, the subdivision
;; scheme could be used to find the index for the first element in the specified
;; interval, after which the iterative algorithm would be used.  This way, the
;; best features of both methods are utilized to maximize efficiency.

;; Review cascaded ring buffers.  Write up spec and distribute as a memo.
;; Abstract filtering capability so that any kind of data consolidation
;; can be done when going to the next cascaded ring buffer.
;; The biggest issue here is how the user should specify the time and
;; datapoint limits and the filtering method for the cascaded ring buffers.
;; This is an issue for discussion with Jim and Mike and then for the
;; Grammar Review Committee.  Try to keep specs simple.  Rather than 
;; having specs for both entire cascaded ring buffer and each individual
;; ring buffer simultaneously, just have specs for each ring buffer.
;; Ex.
;; "keep history with every data point for age less than one hour,
;; every 5th data point for age less than 12 hours"
;; This specifies two ring buffers, the first keeping every data point
;; and holding data for the past hour, the second keeping every 5th data
;; point dropping from the first, and holding data for the past 12 hours.

;; (low priority)
;; Use fixnum operators for history time arithmetic since history times are
;; now always fixnums.  Check with Mike and Jim.

;; (low priority)
;; The loop code for get-standard-deviation-of-value (and other history functions)
;; can be improved a bit (see note under get-standard-deviation-of-value).

;; (low priority)
;; For history functions, abstract finding of first and last data points
;; in interval.  Use sub-division method rather than linear search
;; (see get-value-at-history-time-given-variable).

;; (low priority)
;; Review rate of change.  Make sure interpolation scheme uses data points
;; before and after beginning and end of interval to interpolate.

;; (low priority)
;; Currently, although general expressions can be handled for history functions,
;; they only work if they entity evaluate to a variable (see history evaluators
;; in eval and simulate).  Consider handling any expression using the general
;; history evaluation capability.

;; Data filtering.  
;; Grammar and installation for user specification for cascaded ring buffers.
;; For now, the spec for the entire cascaded-ring-buffer comes from the
;; history specs (if any) entered by the user.  The individual specs for
;; each ring buffer are fixed to be
;;    (nil 300 nil) (nil 3600 60) (nil 86400 3600)
;; Thus, for data 5 minutes or less old, all data is kept, for data between
;; 5 minutes and 1 hour old, the minimum interval between data points is
;; 1 minute, and for data between 1 hour and 1 day old, the minimum interval
;; between data points is one hour.  No data is kept that is more than
;; one day old.
;; Besides the grammar, there are some restrictions on these specifications
;; (see discussion on cascaded ring buffers below) which must be checked by
;; slot value compilers.  There is also the issue of reclaiming cascaded
;; ring buffers, at least if specifications are edited (see next comment).
;; For example, if a limit  on data collection for the entire cascaded ring 
;; buffer is decreased (maximum number of data points goes from 1000 to 500
;; for example) then some runtime specs for the cascade may disappear and
;; the corresponding ring buffers should be recycled.  This is separate
;; from the issue of shrinking the actual ring buffers themselves.
;; Eventually, there should be an "available" list for cascaded ring buffers
;; and a way to reclaim them. 



;;;; Cons Storage Allocation

(defconser history)



;;;; Variable Histories

;;; The following data structures and functions are for keeping
;;; historical values of variables.  These can be used both for the
;;; inference engine value and the simulated value of a variable.



(define-ring-buffer history
    ((history-value . possible-float-array)
     (history-time . possible-float-array)))

;; History-value and history-time contain the values and
;; times of data points.  



;;;; Cascaded Ring Buffers and Data Filtering

;;; Cascaded ring buffers are built out of ring buffers.  They are used in
;;; histories so that data can be filtered efficiently.  This would not be
;;; possible using just ring buffers.  Eventually, it may be desireable to
;;; abstract cascaded ring buffers further and put them in UTILITIES.  For now,
;;; they are only used for histories so they are currently in this module.

;;; A cascaded ring buffer contains, among other things, a list of ring buffers.
;;; Each ring buffer has associated with it a specification of the form
;;;    (maximum-number-of-data-points? maximum-age-of-data-points?
;;;     minimum-interval-between-data-points?)
;;; New data is stored into the first ring buffer on the list; it contains the
;;; most recent data.  Typically, the first ring buffer has no
;;; minimum-interval-between-data-points specified for it so all new data points
;;; are stored.  If there are more ring buffers in the cascade after the first
;;; one, then the first one must have some limit on the amount of data it can
;;; hold specified by either maximum-number-of-data-points?,
;;; maximum-age-of-data-points?  or both.  Thus, when data exceeds the limits of
;;; the first ring buffer, it is dropped into the next ring buffer (if one
;;; exists).  The next ring buffer will typically have a
;;; minimum-interval-between-data-points?  specified resulting in some of the
;;; data coming in being discarded rather than being stored in the ring buffer.
;;; In this way, older data is filtered.

;;; It is impossible to do this efficiently with just one ring buffer.  If this
;;; were to be attempted, it would be necessary to somehow mark the points in
;;; the ring buffer which are obsolete.  This would not, however, change the
;;; size of the ring buffer in any way.  The result would be large "gaps" of
;;; obsolete points between valid points.  While this is not incorrect, it would
;;; be a waste of memory.  The only way to close these gaps would be to
;;; constantly copy large sets of numbers from one location in the ring buffer
;;; to another, something too time consuming to be practical.  Thus,
;;; cascaded-ring-buffers are the best approach.

;;; The specification for each ring buffer in a cascaded-ring-buffer is kept 
;;; in the slot specifications-for-individual-ring-buffers-in-cascade and is
;;; a list of elements of the form
;;;    (maximum-number-of-data-points? maximum-age-of-data-points?
;;;     minimum-interval-between-data-points?)
;;; Age is in seconds.

;;; There are some restrictions on specifications for the individual ring 
;;; buffers:  
;;; 1.  If any specification does not specify a limit by either
;;;     maximum-number-of-data-points?, maximum-age-of-data-points?, or both
;;;     then there should be no more specifications (no more ring buffers)
;;;     after this.
;;; 2.  Maximum-age-of-data-points? must increase for each specification where
;;;     it is specified. 
;;; 3.  Minimum-interval-between-data-points? must increase for each
;;;     specification where it is specified.

;;; Store-history-value will opportunistically create cascaded-ring-buffers
;;; filling in the specifications slots according to user and default
;;; specifications and will add ring buffers to the cascade as necessary.

;; Note that in version 4.0, the Minimum-interval-between-data-points? spec is
;; now implemented and used.  This number specifies the granularity of history
;; intervals.  Only one value may be saved in the history for that interval.
;; Also, the collection time of the saved value is adjusted to be the start of
;; that interval.  - cpm, 5/24/94


(def-structure (cascaded-ring-buffer
		 (:constructor
		   make-cascaded-ring-buffer)
		 (:print-function
		   print-cascaded-ring-buffer))
  (specifications-for-cascaded-ring-buffer nil)
  (specifications-for-individual-ring-buffers-in-cascade nil)
  (runtime-specifications-for-individual-ring-buffers-in-cascade nil)
  (cascaded-ring-buffers nil)
  (old-data-has-been-saved? nil)
  (history-elements-discarded 0)
  (highest-value-ever-in-history? nil)
  (lowest-value-ever-in-history? nil)
  (maintain-high-water-marks-p t)
  (cascaded-ring-buffer-base-time? nil)
  (cascaded-ring-buffer-clients? nil))

;; Are the above specifications-for-cascaded-ring-buffer and
;; specifications-for-individual-ring-buffers-in-cascade slots obsolete?  See
;; comments in the "To Do" part of the "Overview" section.  - cpm, 5/24/94

;; The cascaded-ring-buffer-base-time? was added to the cascaded-ring-buffer
;; structure in version 4.0.  It is used to specify the base, if any, for
;; history timestamps.  This allows history timestamps to be stored as an offset
;; from the base, which allows for a greater range.  In version 3.0, inference
;; engine histories had an implicit base of gensym-time-at-start.  In version
;; 4.0, cascaded-ring-buffer-base-time? contains NIL or a managed-float.  The
;; float is the floor of the current-g2-time (Unix time).
;;
;; As for the base of simulation histories, I need to look into this.  In 3.0,
;; simulation history times had a 0 base because the history time was equal to
;; the simulation time. I'm not certain yet if the simulation history base will
;; change for version 4.0.  - cpm, 5/24/94



(defun copy-cascaded-ring-buffer (cascaded-ring-buffer)
  (let ((new-cascaded-ring-buffer (make-cascaded-ring-buffer)))
    (setf (specifications-for-cascaded-ring-buffer new-cascaded-ring-buffer)
	  (copy-tree-using-history-conses
	    (specifications-for-cascaded-ring-buffer cascaded-ring-buffer)))
    (setf (specifications-for-individual-ring-buffers-in-cascade
	    new-cascaded-ring-buffer)
	  (copy-tree-using-history-conses
	    (specifications-for-individual-ring-buffers-in-cascade
	      cascaded-ring-buffer)))
    (setf (runtime-specifications-for-individual-ring-buffers-in-cascade
	    new-cascaded-ring-buffer)
	  (copy-tree-using-history-conses
	    (runtime-specifications-for-individual-ring-buffers-in-cascade
	      cascaded-ring-buffer)))
    new-cascaded-ring-buffer))

#+development
(defun print-cascaded-ring-buffer (cascaded-ring-buffer stream depth)
  (declare (ignore depth))
  (printing-random-object (cascaded-ring-buffer stream)
    (format stream "CASCADED-RING-BUFFER ~S"
	    (specifications-for-individual-ring-buffers-in-cascade
	      cascaded-ring-buffer))))



;;;; Cascaded Ring Buffer Accessors

;;; An element index for a cascaded ring buffer is a history-cons
;;; of the form (ring-buffer . element-index-for-ring-buffer).
;;; This cons is generated by 
;;; get-newest-active-element-index-for-cascaded-ring-buffer and
;;; get-oldest-active-element-index-for-cascaded-ring-buffer.
;;; The other accessors take a cons of this form as an argument
;;; which can be returned; there is no need to generate new conses.
;;; The cons must be reclaimed somehow (by the calling function when
;;; the element index for the cascaded ring buffer is no longer
;;; needed.

;; Currently, there is never more than one ring buffer in the
;; cascaded-ring-buffers slot of a cascaded-ring-buffer.  Thus, the cascaded
;; ring buffer mechanism is not used, except for the cascaded-ring-buffer
;; structure itself.  Eventually, the mechanism will be used for cases where the
;; user specifies it using the appropriate grammar.  Since this mechanism is not
;; being used, simpler versions of the accessors are used, and the accessors
;; which handle the cascade case have been commented out.

;; Element indices for cascaded ring buffers will have to be reviewed when the
;; cascade mechanism is hooked up again.  Rather than using the current two
;; element list, it would probably be better to switch to a single index with a
;; special variable holding the ring buffer.  This would make it more compatible
;; with the non-cascade case.  If this isn't done, the functions which call
;; these primitives will have to deal with two different types of structures for
;; the indices.

(def-substitution-macro get-newest-active-element-index-for-ring-buffer-or-cascade
			(ring-buffer-or-cascaded-ring-buffer)
  (newest-active-element-index ring-buffer-or-cascaded-ring-buffer))

;(def-substitution-macro get-newest-active-element-index-for-ring-buffer-or-cascade
;			(ring-buffer-or-cascaded-ring-buffer)
;  (if (not (cascaded-ring-buffer-p ring-buffer-or-cascaded-ring-buffer))
;      (newest-active-element-index ring-buffer-or-cascaded-ring-buffer)
;      (get-newest-active-element-index-for-cascaded-ring-buffer
;	ring-buffer-or-cascaded-ring-buffer)))

(defun get-newest-active-element-index-for-cascaded-ring-buffer
       (cascaded-ring-buffer)
  (let ((newest-ring-buffer
	  (car (cascaded-ring-buffers cascaded-ring-buffer))))
    (history-cons
      newest-ring-buffer
      (newest-active-element-index newest-ring-buffer))))

(def-substitution-macro get-oldest-active-element-index-for-ring-buffer-or-cascade
			(ring-buffer-or-cascaded-ring-buffer)
  (oldest-active-element-index ring-buffer-or-cascaded-ring-buffer))

;(def-substitution-macro get-oldest-active-element-index-for-ring-buffer-or-cascade
;			(ring-buffer-or-cascaded-ring-buffer)
;  (if (not (cascaded-ring-buffer-p ring-buffer-or-cascaded-ring-buffer))
;      (oldest-active-element-index ring-buffer-or-cascaded-ring-buffer)
;      (get-oldest-active-element-index-for-cascaded-ring-buffer
;	ring-buffer-or-cascaded-ring-buffer)))

(defun get-oldest-active-element-index-for-cascaded-ring-buffer
       (cascaded-ring-buffer)
  (let ((oldest-ring-buffer
	  (car (last (cascaded-ring-buffers cascaded-ring-buffer)))))
    (history-cons
      oldest-ring-buffer
      (oldest-active-element-index oldest-ring-buffer))))

(def-substitution-macro increment-active-element-index-for-ring-buffer-or-cascade
			(element-index ring-buffer-or-cascaded-ring-buffer)
  (increment-active-element-index
    element-index ring-buffer-or-cascaded-ring-buffer))

;(def-substitution-macro increment-active-element-index-for-ring-buffer-or-cascade
;			(element-index ring-buffer-or-cascaded-ring-buffer)
;  (if (not (cascaded-ring-buffer-p ring-buffer-or-cascaded-ring-buffer))
;      (increment-active-element-index
;	element-index ring-buffer-or-cascaded-ring-buffer)
;      (increment-active-element-index-for-cascaded-ring-buffer
;	element-index ring-buffer-or-cascaded-ring-buffer)))

(defun increment-active-element-index-for-cascaded-ring-buffer
       (element-index cascaded-ring-buffer)
  (let ((ring-buffer
	  (car element-index))
	(element-index-for-ring-buffer
	  (cdr element-index)))
    (if (not (= element-index-for-ring-buffer
		(newest-active-element-index ring-buffer)))
	(setf (cdr element-index)
	      (increment-active-element-index
		element-index-for-ring-buffer ring-buffer))
	(let* ((cascaded-ring-buffers
		 (cascaded-ring-buffers cascaded-ring-buffer))
	       (previous-ring-buffer
		 (if (eq ring-buffer
			 (car cascaded-ring-buffers))
		     (car (last cascaded-ring-buffers))
		     (loop for rest-of-ring-buffers
			       on cascaded-ring-buffers
			   thereis (if (eq (cadr rest-of-ring-buffers)
					   ring-buffer)
				       (car rest-of-ring-buffers))))))
	  (setf (car element-index) 
		previous-ring-buffer
		(cdr element-index)
		(oldest-active-element-index previous-ring-buffer)))))
  element-index)

;; Note that this will wrap around completely.

(def-substitution-macro decrement-active-element-index-for-ring-buffer-or-cascade
			(element-index ring-buffer-or-cascaded-ring-buffer)
  (decrement-active-element-index
    element-index ring-buffer-or-cascaded-ring-buffer))

;(def-substitution-macro decrement-active-element-index-for-ring-buffer-or-cascade
;			(element-index ring-buffer-or-cascaded-ring-buffer)
;  (if (not (cascaded-ring-buffer-p ring-buffer-or-cascaded-ring-buffer))
;      (decrement-active-element-index
;	element-index ring-buffer-or-cascaded-ring-buffer)
;      (decrement-active-element-index-for-cascaded-ring-buffer
;	element-index ring-buffer-or-cascaded-ring-buffer)))

(defun decrement-active-element-index-for-cascaded-ring-buffer
       (element-index cascaded-ring-buffer)
  (let ((ring-buffer
	  (car element-index))
	(element-index-for-ring-buffer
	  (cdr element-index)))
    (if (not (= element-index-for-ring-buffer
		(oldest-active-element-index ring-buffer)))
	(setf (cdr element-index)
	      (decrement-active-element-index
		element-index-for-ring-buffer ring-buffer))
	(let* ((cascaded-ring-buffers
		 (cascaded-ring-buffers cascaded-ring-buffer))
	       (next-ring-buffer
		 (if (eq ring-buffer
			 (car (last cascaded-ring-buffers)))
		     (car cascaded-ring-buffers)
		     (loop for rest-of-ring-buffers
			       on cascaded-ring-buffers
			   thereis (if (eq (car rest-of-ring-buffers)
					   ring-buffer)
				       (cadr rest-of-ring-buffers))))))
	  (setf (car element-index) 
		next-ring-buffer
		(cdr element-index)
		(newest-active-element-index next-ring-buffer)))))
  element-index)

;; Note that this will wrap around completely.



;;; The functions `get-history-g2-time' and `get-history-current-time' are the
;;; external functions for accesing history times.  These forms reconstruct the
;;; timestamp by adding back in the base time (which for non-simulated times is
;;; the G2 time when the history was created).

;;; Get-history-g2-time returns the time in the Unix format.
;;; Get-history-current-time returns the time as an offset from g2-time-at-start
;;; (i.e., the Unix time when G2 was started) or g2-time at the start of the
;;; simulator (or simulation-model).

;;; The base-time argument is a managed-float that is stored in the
;;; cascade-ring-buffer. (unless the only values stored to the history
;;; have been simulated values, in which cse it is nil)

;;; Note that these functions return a gensym-float.  Therefore, these should be
;;; called within a temporary gensym-float area.

(def-substitution-macro get-history-g2-time-1 (cascaded-ring-buffer element-index simulated-value?)
  (let* ((ring-buffer (car (cascaded-ring-buffers cascaded-ring-buffer)))
	 (base-time? (cascaded-ring-buffer-base-time? cascaded-ring-buffer))
	 (history-time
	   (get-history-time-evaluation-value ring-buffer element-index nil))
	 (history-time-float
	   (if (managed-float-p history-time)
	       (managed-float-value history-time)
	       0.0)))
    (declare (type gensym-float history-time-float))
    (when (managed-float-p history-time)
      (reclaim-managed-float history-time))
    (cond
      ((fixnump history-time)
       ;; Must return a float here. Otherwise, the integer could be a bignum.
       (+e (coerce-fixnum-to-gensym-float history-time)
	   (if base-time?
	       (managed-float-value base-time?)
	       0.0)))
      ((or simulated-value?
	   (null base-time?))
       history-time-float)
      (t
       (+e history-time-float
	   (managed-float-value base-time?))))))

(defun get-history-g2-time (cascaded-ring-buffer element-index
			    &optional (simulated-value? nil))
  (get-history-g2-time-1 cascaded-ring-buffer element-index simulated-value?))

(defun get-history-g2-time-as-evaluation-value (cascaded-ring-buffer element-index
					        simulated-value?)
  (allocate-managed-float
    (get-history-g2-time-1 cascaded-ring-buffer element-index simulated-value?)))

(def-substitution-macro get-history-current-time-1
    (cascaded-ring-buffer element-index simulated-history?)
  (if (null simulated-history?)
      (-e (get-history-g2-time cascaded-ring-buffer element-index)
	  (managed-float-value (clock-get g2-time-at-start)))
      ;; Note that the simulated history time is already in terms of the current
      ;; simulated time.
      (get-history-g2-time cascaded-ring-buffer element-index simulated-history?)))

(defun get-history-current-time
       (cascaded-ring-buffer element-index simulated-history?)
  (get-history-current-time-1 cascaded-ring-buffer element-index simulated-history?))

(defun get-history-current-time-as-evaluation-value
       (cascaded-ring-buffer element-index simulated-history?)
  (allocate-managed-float
    (get-history-current-time-1 cascaded-ring-buffer element-index simulated-history?)))

;; The above function replaces get-history-current-g2-time which did not
;; correctly handled times for the simulator.  - cpm, 1/11/95

(def-substitution-macro get-history-value-for-ring-buffer-or-cascade
			(ring-buffer-or-cascaded-ring-buffer element-index)
  (get-history-value ring-buffer-or-cascaded-ring-buffer element-index))

(defun get-history-value-for-ring-buffer-or-cascade-function
       (ring-buffer-or-cascaded-ring-buffer element-index)
  (get-history-value-for-ring-buffer-or-cascade
    ring-buffer-or-cascaded-ring-buffer element-index))

(defun get-history-value-for-cascaded-ring-buffer 
       (cascaded-ring-buffer element-index)
  (declare (ignore cascaded-ring-buffer))
  (get-history-value (car element-index) (cdr element-index)))

(defmacro reclaim-element-index-for-cascaded-ring-buffer
	  (element-index)
  `(reclaim-history-cons ,element-index))

(def-substitution-macro indices-same-for-ring-buffer-or-cascade-p
			(index-1 index-2)
  (=f index-1 index-2))

;(def-substitution-macro indices-same-for-ring-buffer-or-cascade-p
;			(index-1 index-2)
;  (if (not (consp index-1))
;      (=f index-1 index-2)
;      (cascaded-ring-buffer-indices-same-p index-1 index-2)))

(defun cascaded-ring-buffer-indices-same-p
       (index-1 index-2)
  (and (eq (car index-1) (car index-2))
       (=f (cdr index-1) (cdr index-2))))



;;; The following functions `add-cascaded-ring-buffer-client',
;;; `remove-cascaded-ring-buffer-client', and
;;; `clear-cascaded-ring-buffer-clients' define operations to keep track of the
;;; "clients" that are interested in this cascaded-ring-buffer.  The client
;;; should be added to and removed from the list, when necessary, with the add
;;; and remove operations.

;;; This client information is particularly needed when the cascaded-ring-buffer
;;; has been modified and the clients (e.g., trend-charts) need to be notified
;;; of the change.  This can be done by passing a function name to the macro
;;; `map-over-cascaded-ring-buffer-clients'.

;;; `notify-client-of-change-to-cascaded-ring-buffer' is an example of a
;;; function used to map over all clients for a history-buffer.

(defun add-cascaded-ring-buffer-client (thing cascaded-ring-buffer)
  (history-pushnew
    thing
    (cascaded-ring-buffer-clients? cascaded-ring-buffer)))

(defun remove-cascaded-ring-buffer-client (thing cascaded-ring-buffer)
  (setf
    (cascaded-ring-buffer-clients? cascaded-ring-buffer)
    (delete-history-element
      thing
      (cascaded-ring-buffer-clients? cascaded-ring-buffer))))

(defun clear-cascaded-ring-buffer-clients (cascaded-ring-buffer)
  (let ((clients? (cascaded-ring-buffer-clients? cascaded-ring-buffer)))
    (when clients?
      (reclaim-history-list clients?)
      (setf (cascaded-ring-buffer-clients? cascaded-ring-buffer)
	    nil))))

(defmacro map-over-cascaded-ring-buffer-clients
    (mapped-function cascaded-ring-buffer)
  (let ((client (gensym))
	(func (eval mapped-function)))
    `(loop for ,client in (cascaded-ring-buffer-clients? ,cascaded-ring-buffer)
	   do
       (,func ,client))))

(declare-forward-reference
  update-generic-history-for-change-to-cascaded-ring-buffer
  function)

(defun notify-client-of-change-to-cascaded-ring-buffer (frame)
  (when (frame-of-class-p frame 'generic-history)
    (update-generic-history-for-change-to-cascaded-ring-buffer frame)
					; To be finished with JED!!  - cpm,
					; 11/3/94
    nil))



(defun maintain-high-water-marks (cascaded-ring-buffer unnormalized-value)
  ;; highest-value-ever-in-history
  (when (numberp unnormalized-value)
    (with-temporary-gensym-float-creation maintain-high-water-marks
      (let ((value (cond ((fixnump unnormalized-value)
			  (coerce-fixnum-to-gensym-float unnormalized-value))
			 ((long-p unnormalized-value)
			  (convert-g2longint-to-double unnormalized-value))
			 (t
			  (extract-number unnormalized-value)))))
	(cond ((highest-value-ever-in-history? cascaded-ring-buffer)
	       (let ((high-water-mark (highest-value-ever-in-history?
					cascaded-ring-buffer))
		     (low-water-mark (lowest-value-ever-in-history?
				       cascaded-ring-buffer)))
		 (cond ((>e value (managed-float-value high-water-mark))
			(mutate-managed-float-value
			  high-water-mark value))
		       ((<e value (managed-float-value low-water-mark))
			(mutate-managed-float-value
			  low-water-mark value)))))
	      (t
	       (setf (highest-value-ever-in-history? cascaded-ring-buffer)
		     (allocate-managed-float value))
	       (setf (lowest-value-ever-in-history? cascaded-ring-buffer)
		     (allocate-managed-float value))))))))

(defun clear-high-water-marks (cascaded-ring-buffer)
  (when (highest-value-ever-in-history? cascaded-ring-buffer)
    (reclaim-managed-float
      (highest-value-ever-in-history? cascaded-ring-buffer))
    (setf (highest-value-ever-in-history? cascaded-ring-buffer) nil)
    (reclaim-managed-float
      (lowest-value-ever-in-history? cascaded-ring-buffer))
    (setf (lowest-value-ever-in-history? cascaded-ring-buffer) nil)))
    
(defun clear-cascaded-ring-buffer-base-time (cascaded-ring-buffer)
  (when (cascaded-ring-buffer-base-time? cascaded-ring-buffer)
    (reclaim-managed-float
      (cascaded-ring-buffer-base-time? cascaded-ring-buffer))
    (setf (cascaded-ring-buffer-base-time? cascaded-ring-buffer) nil)))


(defun clear-histories (variable)
  (if (variable-or-parameter-history-specification? variable)
      (let ((buffer-of-stored-values?
	      (variable-or-parameter-stored-histories? variable)))
	(when buffer-of-stored-values?
	  (clear-history-buffer buffer-of-stored-values?))))
  (clear-simulation-history variable))

(defun-void clear-simulation-history (variable)
  (if (and (variable-p variable)
	   (simulation-details variable))
      (if (simulation-stored-history-specification? 
	    (simulation-details variable))
	  (let ((buffer-of-stored-values?
		  (simulation-stored-histories? 
		    (simulation-details variable))))
	    (when buffer-of-stored-values?
	      (clear-history-buffer buffer-of-stored-values?))))))

(defun-void clear-simulation-history-at-runtime (variable)
  (let* ((simulation-details?
	   (and (variable-p variable)
		(simulation-details variable)))
	 (buffer-of-stored-values?
	   (and simulation-details?
		(simulation-stored-history-specification? simulation-details?)
		(simulation-stored-histories? simulation-details?))))
    (when buffer-of-stored-values?
      (clear-history-buffer-at-runtime variable buffer-of-stored-values?))))

(defun-void clear-history-buffer-at-runtime
    (variable-or-parameter buffer-of-stored-values)
  (note-change-to-runtime-data-for-block variable-or-parameter)
  (clear-history-buffer buffer-of-stored-values)
  (map-over-cascaded-ring-buffer-clients
    'notify-client-of-change-to-cascaded-ring-buffer
    buffer-of-stored-values))

(defun clear-history-buffer (buffer-of-stored-values)
  (clear-cascaded-ring-buffer-base-time buffer-of-stored-values)
  (clear-history-buffer-and-not-base-time buffer-of-stored-values))


;;; The function `clear-history-buffer-and-not-base-time' clears the element
;;; related information in the history, but not the base-time.  This is
;;; necessary, in the case when old, obsolete values are cleared and new ones
;;; are about to be added.

(defun clear-history-buffer-and-not-base-time (buffer-of-stored-values)
  (clear-high-water-marks buffer-of-stored-values)
  (setf (history-elements-discarded buffer-of-stored-values) 0)
  (loop for ring-buffer 
	    in (cascaded-ring-buffers buffer-of-stored-values)
	do
    (set-newest-active-element-index
      ring-buffer
      0)
    (set-oldest-active-element-index
      ring-buffer
      0)
    (set-ring-buffer-empty? 
      ring-buffer
      t)))



(def-substitution-macro ring-buffer-or-cascade-empty?
			(ring-buffer-or-cascaded-ring-buffer)
  (ring-buffer-empty? ring-buffer-or-cascaded-ring-buffer))

;(def-substitution-macro ring-buffer-or-cascade-empty?
;			(ring-buffer-or-cascaded-ring-buffer)
;  (if (not (cascaded-ring-buffer-p ring-buffer-or-cascaded-ring-buffer))
;      (ring-buffer-empty? ring-buffer-or-cascaded-ring-buffer)
;      (cascaded-ring-buffer-empty? ring-buffer-or-cascaded-ring-buffer)))

(defun cascaded-ring-buffer-empty? (cascaded-buffer)
  (loop for ring-buffer 
	    in (cascaded-ring-buffers cascaded-buffer)
	do
    (if (not (ring-buffer-empty? ring-buffer))
	(return nil))
	finally (return t)))



(def-slot-value-reclaimer variable-or-parameter-stored-histories?
			  (history-buffer? variable)
  (declare (ignore variable))
  (if history-buffer?
      (reclaim-history-buffer history-buffer?)))

(def-slot-value-reclaimer simulation-stored-histories?
			  (history-buffer? simulation-subtable)
  (declare (ignore simulation-subtable))
  (if history-buffer?
      (reclaim-history-buffer history-buffer?)))

(defun reclaim-history-buffer (cascaded-history-ring-buffer)
  (reclaim-history-tree
    (runtime-specifications-for-individual-ring-buffers-in-cascade
      cascaded-history-ring-buffer))
  (setf (runtime-specifications-for-individual-ring-buffers-in-cascade
	  cascaded-history-ring-buffer)
	nil)
  (loop for history-ring-buffer 
	    in (cascaded-ring-buffers cascaded-history-ring-buffer)
	do
    (reclaim-history-ring-buffer history-ring-buffer))
  (reclaim-history-list
    (cascaded-ring-buffers cascaded-history-ring-buffer))
  (clear-high-water-marks cascaded-history-ring-buffer)
  (clear-cascaded-ring-buffer-base-time cascaded-history-ring-buffer)
  (clear-cascaded-ring-buffer-clients cascaded-history-ring-buffer)
  (reclaim-cascaded-ring-buffer cascaded-history-ring-buffer))


;;; This is an uncapped system procedure.  It is called by
;;; `g2-initialize-parameter' in sys-mod.kb.  This code is needed
;;; only when the collection time is older than that of the most 
;;; recent value so that current-value etc. will be set.
;;; *some-time-ago* is used for this purpose to initialize
;;; collection timestamps way back into the past.  E.g., see
;;; `put-evaluation-value-of-variable-or-parameter'.
;;; - jpg 3/6/07

(defun-for-system-procedure g2-initialize-parameter-aux (param)
  (let ((old-collection-time (time-of-most-recent-value param)))
    (when (managed-float-p old-collection-time)
      (reclaim-managed-float old-collection-time))
    (setf (time-of-most-recent-value param) *some-time-ago*)
    nil))



;;;; Storing History Values and Allocating Histories






;;; `adjust-time-for-history'

;;; The history-offset is 0 when storing a simulated time. This means that
;;; the base time is not set and that when a history time value is retrieved
;;; it is specially marked so that no base time is subtracted -rdf, 5/1/96

;; Note that minimum-interval-between-data-points? of the history-specification
;; (mentioned above) was added for version 4.0.  This minimum-interval specifies
;; the smallest interval that may only contain 1 datapoint.  Also, it determines
;; the "granularity" of the history timestamp.  The history value's timestamp is
;; saved as the beginning time of the interval.  Note that if not specified, as
;; when loading 3.0 KB's into 4.0, the default of NIL is interpretted as an
;; interval of 1.  Also, note that a minimum-interval of 0 means that all
;; history values will be kept, even if there are duplicate collection times for
;; some values.  - cpm, 5/24/94

;;; The types of values which can be stored in histories are numbers, symbols,
;;; truth values (numbers), and strings.  Note that many of the history
;;; functions do not work with non-numeric histories (a notify-user message will
;;; be sent explaining the problem).  Also, non-numeric data can not be plotted
;;; on graphs.

;;; History ring buffers are allocated either by
;;; make-or-reformat-cascaded-ring-buffer when the history specifications slots
;;; are edited, or by store-history-element-in-cascaded-ring-buffer when the
;;; first value is stored.  The ring buffers are thus not allocated when a
;;; knowledge base is loaded or started.  Also, they are not reclaimed upon
;;; reset, they are only reclaimed when their variables are deleted.

;;; The cascaded-ring-buffer should already be allocated and passed as an
;;; argument to this function.

;; IMPORTANT: This function now assumes that it is called from within a
;; temporary gensym-float area.  - cpm, 5/24/94

(def-substitution-macro adjust-time-for-history
    (time base-time storing-simulated-value? history-granularity?)
  (let* ((base-time-value (managed-float-value base-time))
	 (time-value (normalize-to-gensym-float time))
	 (time-offset
	   (if storing-simulated-value?
	       0.0d0
	       (-e time-value base-time-value))))
    (declare (type gensym-float base-time-value time-value time-offset))
    ;; Note that granularity is stored in milliseconds.
    (cond ((or (null history-granularity?)
	       (=f history-granularity? 1000))
	   ;; 1 second granularity.  Store the time as an integer.
	   (if (>e time-offset most-positive-fixnum-as-float)
	       (ffloore-first time-offset)
	       (floore-first time-offset)))
	  ((=f history-granularity? 0)
	   ;; Note that a zero granularity means to store all values using
	   ;; the actual, non-granularized time.
	   time-offset)
	  ((>f history-granularity? 1000)
	   ;; Currently, only allow fixnum granularity > 1, multiples of
	   ;; 1000 milliseconds.
	   (let ((integer-granularity
		   (floorf-positive history-granularity? 1000)))
	     (*e (coerce-fixnum-to-gensym-float integer-granularity)
		 (ffloore-first
		   (+e time-offset history-timestamp-epsilon)
		   (coerce-fixnum-to-gensym-float integer-granularity)))))
	  (t ;; 0 < granularity < 1000
	   (let* ((floored-time-float (ffloore-first time-offset))
		  (subsecond-time (-e time-offset floored-time-float))
		  (float-granularity
		    (/e (coerce-fixnum-to-gensym-float
			  history-granularity?)
			1000.0)))
	     (declare
	       (type gensym-float
		     floored-time-float subsecond-time float-granularity))
	     ;; Find the correct granularity interval.
	     (+e floored-time-float
		 (*e float-granularity
		     (ffloore-first
		       (+e subsecond-time history-timestamp-epsilon)
		       float-granularity))))))))

;;; `store-history-value' takes as arguments value-history-cascaded-ring-buffer,
;;; value, and time.  History-specification is assumed to be of the form
;;; ('history maximum-number-of-data-points?  maximum-age-of-data-points?
;;; minimum-interval-between-data-points?).  It stores the value and time as a
;;; data point according to the history-specification.  It is called by
;;; put-current-value in "variables" to store variable histories and by
;;; update-current-value in "simulate" to store simulation histories.

;; The time argument is a g2-time, a float value of the
;; gensym-time-at-start (which is a "unix-time", which
;; is in seconds) plus the number of seconds that G2 has
;; been running (in general).  It can be a gensym-float or
;; a fixnum.

(defun store-history-value
    (value-history-cascaded-ring-buffer history-specification value time
					storing-simulated-value?)
  (gensym-dstruct-bind
      ((nil maximum-number-of-data-points? nil history-granularity?)
       history-specification)
    (when (or (not maximum-number-of-data-points?)
	      (not (= 0 maximum-number-of-data-points?)))
      (let* ((base-time
	       ;; A managed-float adjusted to the granularity, when necessary.
	       (or (and value-history-cascaded-ring-buffer
			(cascaded-ring-buffer-base-time?
			  value-history-cascaded-ring-buffer))
		   (and storing-simulated-value?
			(allocate-managed-float 0.0d0))
		   (allocate-base-time-adjusted-for-granularity
		     history-granularity?)))
	     (time-adjusted-for-history
	       (adjust-time-for-history
		 time base-time storing-simulated-value? history-granularity?))
	     (overwrite-value-if-duplicate-time?
	       (not (and history-granularity? (=f history-granularity? 0)))))
	;; don't initialize the base time if it's a simulated value
	(unless (or (cascaded-ring-buffer-base-time?
		      value-history-cascaded-ring-buffer)
		    storing-simulated-value?)
	  (setf (cascaded-ring-buffer-base-time?
		  value-history-cascaded-ring-buffer)
		base-time))
	(store-history-element-in-cascaded-ring-buffer
	  value-history-cascaded-ring-buffer value time-adjusted-for-history
	  overwrite-value-if-duplicate-time?
	  storing-simulated-value?)
	(map-over-cascaded-ring-buffer-clients
	  'notify-client-of-change-to-cascaded-ring-buffer
	  value-history-cascaded-ring-buffer)))))

;; In certain cases (when data is discrete) it should be possible to store only 
;; when values change (resulting in better memory efficiency for such histories).
;; Perhaps store-history-value should take another argument to indicate whether
;; the value should be stored in this way.  Note that this is not a good method
;; of storage if it is necessary to calculate currency of previous values since
;; data points may be omitted.



;;; The function `allocate-base-time-adjusted-for-granularity' creates a new
;;; base-time managed-float, adjusted down to the nearest history interval.

;;; This means that the history interval is relative to a calendar time and not
;;; to the time that G2 was started or started to collect histories.

;;; Note: this function should be called within a temporary-float area.

(defun allocate-base-time-adjusted-for-granularity (history-granularity?)
  (cond
    ((or (null history-granularity?) (=f history-granularity? 1000))
     ;; Granularity of 1 second.  NULL is the default of 1 second.
     (allocate-managed-float
       (ffloore-first (managed-float-value (clock-get current-g2-time)))))
    ((=f history-granularity? 0)
     ;; No granularity (an event history).
     (copy-managed-float (clock-get current-g2-time)))
    ((>f history-granularity? 1000)
     ;; Integer intervals are currently multiples of 1000.
     (let ((integer-granularity
	     (floorf-positive history-granularity? 1000)))
       (allocate-managed-float
	 (*e (coerce-fixnum-to-gensym-float integer-granularity)
	     (ffloore-first
	       (+e (managed-float-value (clock-get current-g2-time))
		   history-timestamp-epsilon)
	       (coerce-fixnum-to-gensym-float integer-granularity))))))
    (t
     ;; 0 < granularity < 1000
     (let* ((floored-current-time
	      (ffloore-first (managed-float-value (clock-get current-g2-time))))
	    (subsecond-of-current-time
	      (-e (managed-float-value (clock-get current-g2-time)) floored-current-time))
	    (float-granularity
	      (/e (coerce-fixnum-to-gensym-float history-granularity?)
		  1000.0d0)))
       (declare
	 (type gensym-float
	       floored-current-time subsecond-of-current-time
	       float-granularity))
       (cond
	 ((<e subsecond-of-current-time float-granularity)
	  ;; The time is within the 1st granularity interval.
	  ;; Adjust the history time to the "phase", which, in this
	  ;; case, is on the second.
	  (allocate-managed-float floored-current-time))
	 (t
	  ;; Else, find the correct granularity interval.
	  (allocate-managed-float
	    (+e floored-current-time
		(*e float-granularity
		    (ffloore-first
		      (+e subsecond-of-current-time history-timestamp-epsilon)
		      float-granularity))))))))))



;;; The function `get-or-make-history-buffer' returns the cascaded-ring-buffer
;;; for the given frame, if the frame is keeping histories.  If keeping
;;; histories and the buffer does not exists yet, it is created and stored in
;;; the correct location for that frame, as a side-effect.

(defun get-or-make-history-buffer (frame history-spec?)
  (when history-spec?
    (let ((value-history-cascaded-ring-buffer? nil)
	  (variable-or-parameter-p (frame-class-case frame
				     (variable-or-parameter t)
				     (simulation-subtable nil))))
      (setq value-history-cascaded-ring-buffer?
	    (if variable-or-parameter-p
		(variable-or-parameter-stored-histories? frame)
		(simulation-stored-histories? frame)))
      (unless value-history-cascaded-ring-buffer?
	(gensym-dstruct-bind
	    ((nil maximum-number-of-data-points?
		  maximum-age-of-data-points?
		  millisecond-interval-between-data-points?)
	     history-spec?)
	  (setq value-history-cascaded-ring-buffer?
		(make-or-reformat-cascaded-ring-buffer
		  nil
		  maximum-number-of-data-points?
		  maximum-age-of-data-points?
		  millisecond-interval-between-data-points?)))
	;; TODO: not thread-safe, if multiple threads do this together.
	;; When using CAS, if CAS failed, above created buffer should be reclaimed.
	(if variable-or-parameter-p
	    (setf (variable-or-parameter-stored-histories? frame)
		  value-history-cascaded-ring-buffer?)
	    (setf (simulation-stored-histories? frame)
		  value-history-cascaded-ring-buffer?)))
      value-history-cascaded-ring-buffer?)))



(defun make-or-reformat-cascaded-ring-buffer
       (cascaded-ring-buffer?
	maximum-number-of-data-points? maximum-age-of-data-points?
	millisecond-interval-between-data-points?)
  (let ((new-cascaded-ring-buffer
	  (or cascaded-ring-buffer?
	      (make-cascaded-ring-buffer))))
    (when cascaded-ring-buffer?
      (reclaim-history-tree
	(runtime-specifications-for-individual-ring-buffers-in-cascade
	  new-cascaded-ring-buffer))
      (setf (runtime-specifications-for-individual-ring-buffers-in-cascade
	      new-cascaded-ring-buffer)
	    nil))
    (setf (runtime-specifications-for-individual-ring-buffers-in-cascade
	    new-cascaded-ring-buffer)
	  (history-list
	    (history-list
	      maximum-number-of-data-points? maximum-age-of-data-points?
	      millisecond-interval-between-data-points?)))

    (when maximum-number-of-data-points?
      (let ((existing-ring-buffer?
	      (car (cascaded-ring-buffers new-cascaded-ring-buffer))))
	(when existing-ring-buffer?
	  (cond
	    ((ring-buffer-empty? existing-ring-buffer?)
	     (reclaim-history-ring-buffer existing-ring-buffer?)
	     (reclaim-history-list
	       (cascaded-ring-buffers new-cascaded-ring-buffer))
	     (setf (cascaded-ring-buffers new-cascaded-ring-buffer) nil))
	    (t
	     (let ((ring-buffer-size
		     (ring-buffer-size existing-ring-buffer?)))
	       (cond
		 ((>f maximum-number-of-data-points? ring-buffer-size)
		  ; enlarge
		  (enlarge-history-ring-buffer
		    existing-ring-buffer?
		    ring-buffer-size
		    (minf largest-ring-buffer-vector-size
			  maximum-number-of-data-points?)))
		 ((<f maximum-number-of-data-points? ring-buffer-size)
		  ; make smaller
		  (shrink-history-ring-buffer
		    existing-ring-buffer?
		    ring-buffer-size
		    maximum-number-of-data-points?))))))))
      (when (null (cascaded-ring-buffers new-cascaded-ring-buffer))
	(setf (cascaded-ring-buffers new-cascaded-ring-buffer)
	      (history-list 
		(get-or-make-history-ring-buffer
		  maximum-number-of-data-points?)))))
    new-cascaded-ring-buffer))

;; Eventually will pass in more complicated specifications for
;; runtime-specifications-for-individual-ring-buffers-in-cascade.

;; Existing-ring-buffer?  modification stuff will also become more complicated
;; for cascade case.



(defmacro get-current-time ()
  `(-i gensym-time gensym-time-at-start))



(declare-forward-reference current-simulation-time-as-managed-float function)

;;; `store-history-element-in-cascaded-ring-buffer' stores the data point in the
;;; cascaded ring buffer.  Note that if the time is the same as that for some
;;; data point already stored, the new data point can (if specified by the
;;; argument) overwrite the old one.  This is also the case when storing old
;;; data points.  This ensures that there will never be more than one data point
;;; for any history time.

;;; In version 4.0, added a new argument that controls whether an existing value
;;; with the same timestamp is overwritten.

;;; This function notifies clients of this history buffer when the current state
;;; of the history has changed.  This happens when a new history value overwites
;;; an existing one and when a value is added within the history.  It does not
;;; happen when a value is is added to the end of the history, as the most
;;; recent value.  Trend-charts are one potential client of history-buffers.

;;; IMPORTANT: Beginning in version 4.0, this function must be called from
;;; within a temporary gensym-float area because history times can now be
;;; floats.

(defun store-history-element-in-cascaded-ring-buffer
    (cascaded-ring-buffer new-element-value new-element-time
			  &optional (overwrite-value-if-duplicate-time? t)
			  (storing-simulated-value? nil))
  (let* ((runtime-specification
	   (car (runtime-specifications-for-individual-ring-buffers-in-cascade
		  cascaded-ring-buffer)))
	 (ring-buffer
	   (car (cascaded-ring-buffers cascaded-ring-buffer)))
	 (maximum-number-of-data-points?
	   (first runtime-specification))
	 (maximum-age-of-data-points?
	   (second runtime-specification))
	 newest-active-element-index
	 time-of-previous-data-point?
	 (ring-buffer-was-emptied-p nil)) 
    (when (maintain-high-water-marks-p cascaded-ring-buffer)
      (maintain-high-water-marks cascaded-ring-buffer new-element-value))
    (when (null ring-buffer)
      (setq ring-buffer
	    (let ((new-ring-buffer
		    (if maximum-number-of-data-points?
			(get-or-make-history-ring-buffer
			  maximum-number-of-data-points?)
			(get-or-make-smallest-history-ring-buffer))))
	      (setf (cascaded-ring-buffers cascaded-ring-buffer)
		    (nconc (cascaded-ring-buffers cascaded-ring-buffer)
			   (history-cons new-ring-buffer nil)))
	      new-ring-buffer)))

    (when (not (ring-buffer-empty? ring-buffer))
      ;; delete obsolete values
      (when maximum-age-of-data-points?
	(remove-history-values-past-maximum-age
	  cascaded-ring-buffer ring-buffer maximum-age-of-data-points?
	  (if storing-simulated-value? 
	      (current-simulation-time-as-managed-float)
	      (clock-get current-g2-time))))

      (when (ring-buffer-empty? ring-buffer)
	(setf ring-buffer-was-emptied-p t))

      (setq newest-active-element-index
	    (newest-active-element-index ring-buffer))
      (setq time-of-previous-data-point?
	    (get-history-time
	      ring-buffer newest-active-element-index))

      ;; Check ring buffer length.  If too long, delete obsolete values
      ;; (Unless we are overwriting an existing value.)
      (unless (and overwrite-value-if-duplicate-time?
		   ;; May be null, if all values have expired.
		   time-of-previous-data-point?
		   (= new-element-time time-of-previous-data-point?))
	(when (and maximum-number-of-data-points?
		   (= (ring-buffer-length ring-buffer)
		      maximum-number-of-data-points?))
	;  (format t "removing element~%")
	  (incff (history-elements-discarded
		   cascaded-ring-buffer))
	  (cond
	    ((=f (oldest-active-element-index ring-buffer)
		 newest-active-element-index)
	     ;; This can occur if the maximum number of data points = 1.
	     (set-ring-buffer-empty? ring-buffer t)
	     (setf ring-buffer-was-emptied-p t)
	     (increment-oldest-element-index ring-buffer)
	     (increment-newest-element-index ring-buffer))
	    (t
	     (increment-oldest-element-index ring-buffer))))))

    (when (cond ((ring-buffer-empty? ring-buffer)
		 t)
		((null time-of-previous-data-point?)
		 ;; This should never happen when the history is not empty.
		 #+development
		 (cerror "" "Time-of-previous-data-point was nil in history.")
		 t)
		((> new-element-time time-of-previous-data-point?)
		 ;;(format t "history-case=NEWER~%")
		 t)
		((= new-element-time time-of-previous-data-point?)
		 ;; If time is same as that for previously saved point,
		 ;; possibly change value of that point.
		 ;;(format t "history-case=SAME~%")
		 (cond
		   (overwrite-value-if-duplicate-time?
		    (set-history-ring-buffer-element
		      ring-buffer newest-active-element-index
		      new-element-value new-element-time)
		    ;; Notify that the existing history has changed.
		    (map-over-cascaded-ring-buffer-clients
		      'notify-client-of-change-to-cascaded-ring-buffer
		      cascaded-ring-buffer)
		    nil)
		   (t
		    ;; Add the new history value.
		    t)))
		(t        ; (<f new-element-time time-of-previous-data-point?)
		 ;; If time is before previous saved point, handle
		 ;; as special case.
		 ;;(format t "history-case=OLDER~%")
		 (store-old-data-in-history-ring-buffer
		   ring-buffer new-element-value new-element-time
		   overwrite-value-if-duplicate-time?)
		 (setf (old-data-has-been-saved? cascaded-ring-buffer) t)
		 ;; Notify that the existing history has changed.
		 (map-over-cascaded-ring-buffer-clients
		   'notify-client-of-change-to-cascaded-ring-buffer
		   cascaded-ring-buffer)
		 nil))
      (store-new-element-in-history-ring-buffer
	ring-buffer
	'expand-history-ring-buffer
	new-element-value
	new-element-time)
      (when ring-buffer-was-emptied-p
	(map-over-cascaded-ring-buffer-clients          ; (pbk) 11/20/95
	  'notify-client-of-change-to-cascaded-ring-buffer
	  cascaded-ring-buffer)))))



;; Simplified version which does not use cascaded ring buffer mechanism.  Use
;; commented out version below when hooking up cascaded ring buffer mechanism.
;; Keep simplified version for use in non-cascade cases (when user doesn't
;; specify cascade.



(defun store-new-element-in-history-cascaded-ring-buffer
       (cascaded-ring-buffer value time)
  (store-new-element-in-history-ring-buffer
    (car (cascaded-ring-buffers cascaded-ring-buffer))
    'expand-history-ring-buffer
    value time))

(defun store-new-element-evaluation-value-in-history-cascaded-ring-buffer
       (cascaded-ring-buffer value time)
  (store-new-element-evaluation-value-in-history-ring-buffer
    (car (cascaded-ring-buffers cascaded-ring-buffer))
    'expand-history-ring-buffer
    value time))



;(defun store-history-element-in-cascaded-ring-buffer
;       (cascaded-ring-buffer value time)
;  (loop with new-elements-to-store
;	with ring-buffer
;	with cascaded-ring-buffer-limit-reached? = nil
;	with obsolete-elements = nil
;	for runtime-specification 
;	    in (runtime-specifications-for-individual-ring-buffers-in-cascade
;		 cascaded-ring-buffer)
;	as rest-of-ring-buffers?
;	   = (cascaded-ring-buffers cascaded-ring-buffer)
;	   then (cdr rest-of-ring-buffers?)
;	as maximum-number-of-data-points-for-individual-ring-buffer?
;	   = (first runtime-specification)
;	as maximum-age-of-data-points-for-individual-ring-buffer?
;	   = (second runtime-specification)
;	as minimum-interval-between-data-points-for-individual-ring-buffer?
;	   = (third runtime-specification)
;	as first-time? = t then nil
;	while (and 
;		(or first-time?
;		    obsolete-elements)
;		(not cascaded-ring-buffer-limit-reached?)
;		(setq ring-buffer
;		      (if rest-of-ring-buffers?
;			  (car rest-of-ring-buffers?)
;			  (if (>f (length runtime-specification)
;				  (length (cascaded-ring-buffers cascaded-ring-buffer)))
;			      (let ((new-ring-buffer
;				      (get-or-make-smallest-history-ring-buffer)))
;				(setf (cascaded-ring-buffers cascaded-ring-buffer)
;				      (nconc (cascaded-ring-buffers cascaded-ring-buffer)
;					     (history-cons new-ring-buffer nil)))
;				new-ring-buffer)))))
;	;; new ring buffer should only be made once inside this function
;	do
;    (if first-time?
;	(setq new-elements-to-store
;	      (history-list
;		(history-list value time))))

;    (when (not (ring-buffer-empty? ring-buffer))
;      ;; delete obsolete values
;      (let* ((maximum-age?
;	       maximum-age-of-data-points-for-individual-ring-buffer?))
;	(when maximum-age?
;	  (loop initially (if (and (> (- (get-current-time)
;					 (get-history-time
;					   ring-buffer
;					   (oldest-active-element-index ring-buffer)))
;				      maximum-age?)
;				   (not (= (oldest-active-element-index ring-buffer)
;					   (newest-active-element-index ring-buffer))))
;			      (setq cascaded-ring-buffer-limit-reached? t))
;		with newest-active-element-index
;		  = (newest-active-element-index ring-buffer)
;		for oldest-active-element-index
;		    = (oldest-active-element-index ring-buffer)
;		for time-of-storage = (get-history-time
;					ring-buffer
;					oldest-active-element-index)
		
;		while (and (> (- (get-current-time) time-of-storage)
;			      maximum-age?)
;			   (not (= oldest-active-element-index
;				   newest-active-element-index)))
;		do 
;	    (multiple-value-bind
;	      (obsolete-value obsolete-time)
;		(get-history-ring-buffer-element
;		  ring-buffer oldest-active-element-index)
;	      (setq obsolete-elements
;		    (nconc obsolete-elements
;			   (history-list
;			     (history-list obsolete-value obsolete-time)))))
;	    (increment-oldest-element-index ring-buffer)
;		finally (if (> (- (get-current-time) time-of-storage)
;			       maximum-age?)
;			    (progn
;			      (set-ring-buffer-empty? ring-buffer t)
;			      (increment-oldest-element-index ring-buffer)
;			      (increment-newest-element-index ring-buffer))))))
      
;      ;; Check ring buffer length.
;      ;; If too long, delete obsolete values.
;      (if (and maximum-number-of-data-points-for-individual-ring-buffer?
;	       (= (ring-buffer-length ring-buffer)
;		  maximum-number-of-data-points-for-individual-ring-buffer?))
;	  (multiple-value-bind
;	    (obsolete-value obsolete-time)
;	      (get-history-ring-buffer-element
;		ring-buffer (oldest-active-element-index ring-buffer))
;	    (setq obsolete-elements
;		  (nconc obsolete-elements
;			 (history-list
;			   (history-list obsolete-value obsolete-time))))
;	    (cond
;	      ((=f (oldest-active-element-index ring-buffer)
;		   (newest-active-element-index ring-buffer))
;	       ;; This can occur if the maximum number of data points = 1.
;	       (set-ring-buffer-empty? ring-buffer t)
;	       (increment-oldest-element-index ring-buffer)
;	       (increment-newest-element-index ring-buffer))
;	      (t (increment-oldest-element-index ring-buffer))))))

;    ;; May have to filter data when storing it.
;    (loop for element-to-store in new-elements-to-store
;	  as new-element-value = (first element-to-store)
;	  as new-element-time = (second element-to-store)
;	  do
;      (if (or (ring-buffer-empty? ring-buffer)
;	      (let* ((newest-active-element-index
;		       (newest-active-element-index ring-buffer))
;		     (time-of-previous-data-point
;		       (get-history-time
;			 ring-buffer newest-active-element-index)))

;		#+development
;		(if (null time-of-previous-data-point)  ; This should never happen.
;		    (cerror "" "Time-of-previous-data-point was nil in history."))

;		(cond
;		  ((>f new-element-time time-of-previous-data-point)
;		   (or (not minimum-interval-between-data-points-for-individual-ring-buffer?)
;		       (>=f new-element-time
;			    (+f time-of-previous-data-point
;				minimum-interval-between-data-points-for-individual-ring-buffer?))))
;		  ((=f new-element-time time-of-previous-data-point)
;		   ;; If time is same as that for previously saved point,
;		   ;; just change value of that point.
;		   (set-history-ring-buffer-element
;		     ring-buffer newest-active-element-index
;		     new-element-value new-element-time)
;		   nil)
;		  (t  ; (<f new-element-time time-of-previous-data-point)
;		   ;; If time is before previous saved point, handle
;		   ;; as special case.
;		   (store-old-data-in-history-ring-buffer
;		     ring-buffer new-element-value new-element-time)
;		   (setf (old-data-has-been-saved? cascaded-ring-buffer) t)
;		   nil))))

;	  (store-new-element-in-history-ring-buffer
;	    ring-buffer
;	    'expand-history-ring-buffer
;	    new-element-value
;	    new-element-time)))

;    (reclaim-history-tree new-elements-to-store)
;    (setq new-elements-to-store
;	  obsolete-elements)
;	finally (reclaim-history-tree obsolete-elements)))

;; The filtering done here is very primitive.  Data points are simply dropped,
;; rather than averaged in some way.



;;; Store-old-data-in-history-ring-buffer either overwrites an existing old data
;;; point or shifts newer data points up to make room for the old data point
;;; which is inserted in the appropriate place.  It is assumed here that the
;;; ring buffer is not empty (check is made in
;;; store-history-element-in-cascaded-ring-buffer).

(defun store-old-data-in-history-ring-buffer
       (ring-buffer data-point-value data-point-time
		    &optional (overwrite-value-if-duplicate-time? t))
  (when (ring-buffer-full? ring-buffer)
    (expand-history-ring-buffer ring-buffer))
  (or (and overwrite-value-if-duplicate-time?
	   (overwrite-old-data-point?
	     ring-buffer data-point-value data-point-time))
      (make-space-for-and-insert-old-data-point
	ring-buffer data-point-value data-point-time)))

;; Note that this does not currently check if the old data is older than the
;; maximum age given in the history spec.  If it is, it will be removed on the
;; next call to store-history-value.  Therefore, the number of such obsolete
;; data points is limited to one.  This shouldn't present any problems so it
;; isn't really necessary to implement an extra check here.


;;; Overwrite-old-data-point? overwrites an existing data point if the time for
;;; that data point is the same as the one for the data point being stored now.

(defun overwrite-old-data-point?
       (ring-buffer data-point-value data-point-time)
  (multiple-value-bind
    (history-value closest-history-time next-history-time ring-buffer-index)
      (get-ring-buffer-element-at-history-time ring-buffer data-point-time)
    history-value next-history-time
    (cond ((= data-point-time closest-history-time)
	   (set-history-ring-buffer-element
	     ring-buffer ring-buffer-index data-point-value data-point-time)
	   (when (text-string-p history-value)
	     (reclaim-text-string history-value))
	   t)
	  (t
	   (when (text-string-p history-value)
	     (reclaim-text-string history-value))
	   nil))))


;;; Make-space-for-and-insert-old-data-point shifts newer data points up to make
;;; room for the old data point being stored.

(defun make-space-for-and-insert-old-data-point
       (ring-buffer data-point-value data-point-time) 
  (let* ((index-to-copy-to
	   (increment-newest-element-index ring-buffer))
	 (index-to-copy-from
	   (decrement-active-element-index
	     index-to-copy-to ring-buffer)))
    (loop do 
      (if (insert-old-data-point-if-appropriate
	    ring-buffer index-to-copy-to index-to-copy-from
	    data-point-value data-point-time)
	  (return (values)))

	  until 
	    (=f index-to-copy-from (oldest-active-element-index ring-buffer))

	  do
      (setq index-to-copy-to
	    (decrement-active-element-index index-to-copy-to ring-buffer))
      (setq index-to-copy-from
	    (decrement-active-element-index index-to-copy-from ring-buffer))
	  finally
	    ;; Oldest-active-element-index has been reached.
	    (set-history-ring-buffer-element
	      ring-buffer index-to-copy-from
	      data-point-value data-point-time))))


;;; Insert-old-data-point-if-appropriate returns t if the old data point is
;;; inserted, else nil.

(defun insert-old-data-point-if-appropriate
    (ring-buffer index-to-copy-to index-to-copy-from
		 data-point-value data-point-time)
  (multiple-value-bind
      (previous-data-point-value previous-data-point-time)
      (get-history-ring-buffer-element ring-buffer index-to-copy-from)
    (cond
      ((> data-point-time previous-data-point-time)
       ;; Insert new data point if previous data point is older. 
       (set-history-ring-buffer-element
	 ring-buffer index-to-copy-to
	 data-point-value data-point-time)
       (when (text-string-p previous-data-point-value)
	 (reclaim-text-string previous-data-point-value))
       t)
      (t
       ;; Copy previous data point to new location to accomplish shift.
       (set-history-ring-buffer-element
	 ring-buffer index-to-copy-to
	 previous-data-point-value previous-data-point-time)
       (when (text-string-p previous-data-point-value)
	 (reclaim-text-string previous-data-point-value))
       nil))))



(def-substitution-macro get-total-length-of-ring-buffer-or-cascade
			(ring-buffer-or-cascaded-ring-buffer)
  (if (ring-buffer-empty? ring-buffer-or-cascaded-ring-buffer)
      0
      (ring-buffer-length ring-buffer-or-cascaded-ring-buffer)))

;(def-substitution-macro get-total-length-of-ring-buffer-or-cascade
;			(ring-buffer-or-cascaded-ring-buffer)
;  (if (not (cascaded-ring-buffer-p ring-buffer-or-cascaded-ring-buffer))
;      (ring-buffer-length ring-buffer-or-cascaded-ring-buffer)
;      (get-total-cascaded-ring-buffer-length ring-buffer-or-cascaded-ring-buffer)))

(defun get-total-cascaded-ring-buffer-length (cascaded-ring-buffer)
  (or
    (loop for ring-buffer
	      in (cascaded-ring-buffers cascaded-ring-buffer)
	  sum (ring-buffer-length ring-buffer))
    0))



;;; Expand-history-ring-buffer enlarges the history ring buffer if
;;; the size is not already at the limit largest-ring-buffer-vector-size.

(defun expand-history-ring-buffer (value-history-ring-buffer)
  (let ((current-size (ring-buffer-size value-history-ring-buffer)))
    (when (<f current-size largest-ring-buffer-vector-size)
      (enlarge-history-ring-buffer
	value-history-ring-buffer
	current-size))))



;;; The function `verify-oldest-and-newest-history-values-with-new-time' is used
;;; to check that the end values of the history are either not in the future or
;;; not too old based on any maximum age.  Note that the two history values are
;;; checked against the time argument, not the current time.

;;; Note that the maximum age of data-points argument is an integer or NIL.

;;; If the two history value endpoints are valid, non-NIL is returned.
;;; Otherwise, NIL is returned.

(defun verify-oldest-and-newest-history-values-with-given-time
    (buffer-of-stored-values ring-buffer maximum-age-of-data-points?
			     time-as-managed-float)
  (with-temporary-gensym-float-creation
      verify-oldest-and-newest-history-values-with-given-time
    (let* ((time-float-value (managed-float-value time-as-managed-float))
	   (base-time?
	     (if (cascaded-ring-buffer-base-time? buffer-of-stored-values)
		 (managed-float-value
		   (cascaded-ring-buffer-base-time? buffer-of-stored-values))
		 (managed-float-value (clock-get g2-time-at-start))))
	   (oldest-active-element-index
	     (oldest-active-element-index ring-buffer))
	   (oldest-absolute-unix-time-of-datum
	     (+ (get-history-time ring-buffer oldest-active-element-index)
		base-time?))
	   (oldest-age-of-datum
	     (- time-float-value oldest-absolute-unix-time-of-datum))
	   (newest-active-element-index
	     (newest-active-element-index ring-buffer))
	   (newest-absolute-unix-time-of-datum
	     (+ (get-history-time ring-buffer newest-active-element-index)
		base-time?))
	   (newest-age-of-datum
	     (- time-float-value newest-absolute-unix-time-of-datum))
	   (obsolete-old-value?
	     (and maximum-age-of-data-points?
		  (> oldest-age-of-datum maximum-age-of-data-points?)))
	   (invalid-future-value?
	     (< newest-age-of-datum 0)))
      (not (or obsolete-old-value? invalid-future-value?)))))



;;; The function `remove-history-values-past-maximum-age' is used to remove
;;; history values that are no longer valid, based on the given maximum
;;; interval (an integer) and time argument (a managed-float).

;;; This function does not note changes to runtime data for blocks.  This should
;;; be done before the function is called, if necessary.  The function
;;; verify-oldest-and-newest-history-values-with-given-time could be used to
;;; test if a change to the history is needed.

;;; Note that this function does not clear any existing history base-time.

(defun remove-history-values-past-maximum-age
    (cascaded-ring-buffer ring-buffer maximum-age-of-data-points
			  time-as-managed-float)
  (unless maximum-age-of-data-points
    (return-from remove-history-values-past-maximum-age))
  (with-temporary-gensym-float-creation remove-history-values-past-maximum-age
    (let* ((current-time-float
	     (managed-float-value time-as-managed-float))
	   (base-time?
	     (if (cascaded-ring-buffer-base-time? cascaded-ring-buffer)
		 (managed-float-value
		   (cascaded-ring-buffer-base-time? cascaded-ring-buffer))
		 (managed-float-value (clock-get g2-time-at-start))))
	   (newest-active-element-index
	     (newest-active-element-index ring-buffer))
	   (newest-absolute-unix-time-of-datum
	     (+ (get-history-time ring-buffer newest-active-element-index)
		base-time?))
	   (newest-age-of-datum
	     (- current-time-float newest-absolute-unix-time-of-datum))
	   (oldest-active-element-index nil)
	   (absolute-unix-time-of-datum nil)
	   (age-of-datum nil))
      (cond
	((> newest-age-of-datum maximum-age-of-data-points)
	 ;; All values are too old.
	 (clear-history-buffer-and-not-base-time cascaded-ring-buffer))
	(t
	 (loop
	   do
	   ;; Re-enter the temporary-area every 100 elements, so as not to
	   ;; overflow the area.
	   (with-temporary-gensym-float-creation
	       remove-history-values-past-maximum-age
	     (loop for inner-loop-count from 0 below 100
		   do
	       (setq oldest-active-element-index
		     (oldest-active-element-index ring-buffer))
	       (setq absolute-unix-time-of-datum
		     (+ (get-history-time
			  ring-buffer oldest-active-element-index)
			base-time?))
	       (setq age-of-datum
		     (- current-time-float absolute-unix-time-of-datum))

		   while (and (> age-of-datum maximum-age-of-data-points)
			      (not (= oldest-active-element-index
				      newest-active-element-index)))
		   do
	       (increment-oldest-element-index ring-buffer)
	       (incff (history-elements-discarded cascaded-ring-buffer))))

	   ;; Outer loop: comparing the values of the age and indices, bound
	   ;; before the oldest element index was incremented in the inner loop.
	   while (and (> age-of-datum maximum-age-of-data-points)
		      (not (= oldest-active-element-index
			      newest-active-element-index)))
	   finally (if (> age-of-datum maximum-age-of-data-points)
		       (progn
			 (set-ring-buffer-empty? ring-buffer t)
			 (increment-oldest-element-index ring-buffer)
			 (increment-newest-element-index ring-buffer)))))))))



;;; The function `remove-future-history-values' is used to delete history values
;;; that are ahead of the given time argument (a managed-float).

;;; This function does not note changes to runtime data for blocks.  This should
;;; be done before the function is called, if necessary.  The function
;;; verify-oldest-and-newest-history-values-with-given-time could be used to
;;; test if a change to the history is needed.

;;; Note that this function does not clear any existing history base-time.

(defun remove-future-history-values
    (cascaded-ring-buffer ring-buffer time-as-managed-float)
  (with-temporary-gensym-float-creation remove-future-history-values
    (let* ((current-time-float
	     (managed-float-value time-as-managed-float))
	   (base-time?
	     (if (cascaded-ring-buffer-base-time? cascaded-ring-buffer)
		 (managed-float-value
		   (cascaded-ring-buffer-base-time? cascaded-ring-buffer))
		 (managed-float-value (clock-get g2-time-at-start))))
	   (oldest-active-element-index
	     (oldest-active-element-index ring-buffer))
	   (oldest-absolute-unix-time-of-datum
	     (+ (get-history-time ring-buffer oldest-active-element-index)
		base-time?))
	   (oldest-age-of-datum
	     (- current-time-float oldest-absolute-unix-time-of-datum))
	   (newest-active-element-index nil)
	   (absolute-unix-time-of-datum nil)
	   (age-of-datum nil))
      (cond
	((< oldest-age-of-datum 0)
	 ;; All values are too recent (in the future, relative to the given
	 ;; time).
	 (clear-history-buffer-and-not-base-time cascaded-ring-buffer))
	(t
	 (loop 
	   do
	   ;; Re-enter the temporary-area every 100 elements, so as not to
	   ;; overflow the area.
	   (with-temporary-gensym-float-creation remove-future-history-values
	     ;; Loop from the newest value backward.
	     (loop for inner-loop-count from 0 below 100
		   do
	       (setq newest-active-element-index
		     (newest-active-element-index ring-buffer))
	       (setq absolute-unix-time-of-datum
		     (+ (get-history-time
			  ring-buffer newest-active-element-index)
			base-time?))
	       (setq age-of-datum
		     (- current-time-float absolute-unix-time-of-datum))
		   while (and (< age-of-datum 0) ;More recent than the time arg.
			      (not (= oldest-active-element-index
				      newest-active-element-index)))
		   do
	       (decrement-newest-element-index ring-buffer)
	       ;; References to history-elements-discarded should not depend on
	       ;; the discarded values being at the oldest or newest end of the
	       ;; buffer.
	       (incff (history-elements-discarded cascaded-ring-buffer))))

	   ;; Outer loop: comparing the values of the age and indices, bound
	   ;; before the newest element index was decremented in the inner loop.
	   while (and (< age-of-datum 0) ; More recent than the time arg.
		      (not (= oldest-active-element-index
			      newest-active-element-index)))
	  finally (if (< age-of-datum 0)
		      (progn
			(set-ring-buffer-empty? ring-buffer t)
			(decrement-oldest-element-index ring-buffer)
			(decrement-newest-element-index ring-buffer)))))))))



;; Notes on Variable Histories

;; For discrete values, may want to just record changes rather than levels.
;; More memory efficient but will make it more difficult to get previous
;; values: would have to do basically an integration of all changes from an
;; initial value.  





;;;; Searching In Histories

;;; The following functions used to be defined in GRAPHS2, but are more
;;; naturally a part of the history facility.


;; the following variables are bound dynamically in GRAPHS2
;; and are used here.

(defvar previous-cascaded-ring-buffer-accessed)
(defvar previous-index-for-ring-buffer)

;; results-of-element-search is not external

(defmacro adjust-history-time-result (history-time cascaded-ring-buffer)
  (avoiding-variable-capture (history-time cascaded-ring-buffer)
    `(let ((base-time (cascaded-ring-buffer-base-time? ,cascaded-ring-buffer)))
       (cond
	 ((fixnump ,history-time)
	  ;; Must return a float here. Otherwise, the integer could be a bignum.
	  (+e (coerce-fixnum-to-gensym-float ,history-time)
	      (managed-float-value base-time)))
	 (t
	  (+e ,history-time (managed-float-value base-time)))))))

(defun results-of-element-search
       (cascaded-ring-buffer? ring-buffer index next-history-time)
  (progn
    (setq previous-cascaded-ring-buffer-accessed cascaded-ring-buffer?
	  previous-index-for-ring-buffer index)
    (multiple-value-bind
      (history-value history-time)
	(get-history-ring-buffer-element ring-buffer index)
      (values history-value
	      (if cascaded-ring-buffer?
		  (adjust-history-time-result history-time cascaded-ring-buffer?)
		  history-time)
	      (if (and cascaded-ring-buffer? next-history-time)
		  (adjust-history-time-result next-history-time cascaded-ring-buffer?)
		  next-history-time)
	      index))))

;; get-ring-buffer-element-by-linear-search is not-external 

(defun get-history-element-by-linear-search
       (cascaded-ring-buffer absolute-history-time &optional relative-p)
  (with-temporary-gensym-float-creation get-history-element-by-linear-search
    (loop with ring-buffer
	  = (car (cascaded-ring-buffers cascaded-ring-buffer))
	  with history-time
	  = (-e (+e (if (fixnump absolute-history-time)
			(coerce-fixnum-to-gensym-float absolute-history-time)
			absolute-history-time)
		    (if relative-p
			(managed-float-value (clock-get g2-time-at-start))
			0.0d0))
		(managed-float-value (cascaded-ring-buffer-base-time?
				       cascaded-ring-buffer)))
	  with next-index = nil
	  with next-history-time = nil
	  as index = previous-index-for-ring-buffer
		   then next-index
	  do 
      (when (=f index (newest-active-element-index ring-buffer))
	(return 
	  (results-of-element-search
	    cascaded-ring-buffer
	    ring-buffer index nil)))
      (setq next-index (increment-active-element-index index ring-buffer)
	    next-history-time (get-history-time ring-buffer next-index))
	  until (> next-history-time history-time)
	  finally
	    (return 
	      (results-of-element-search
		cascaded-ring-buffer
		ring-buffer index next-history-time)))))

;; get-ring-buffer-element-by-binary-search is not external

(defun get-history-element-by-binary-search
       (cascaded-ring-buffer history-time &optional relative-p)
  (with-temporary-gensym-float-creation get-history-element-by-binary-search
    (get-ring-buffer-element-by-binary-search
      cascaded-ring-buffer
      (car (cascaded-ring-buffers cascaded-ring-buffer))
      (-e (+e (if (fixnump history-time)
		  (coerce-fixnum-to-gensym-float history-time)
		  history-time)
	      (if relative-p
		  (managed-float-value (clock-get g2-time-at-start))
		  0.0d0))
	  (managed-float-value (cascaded-ring-buffer-base-time?
				 cascaded-ring-buffer))))))

(defun get-ring-buffer-element-by-binary-search (cascaded-ring-buffer?
						  ring-buffer history-time)
  (loop with index-for-newest-element-in-interval
	  = (newest-active-element-index ring-buffer)
	with index-for-oldest-element-in-interval
	  = (oldest-active-element-index ring-buffer)
	with index-for-median-element-in-interval
	  = (get-median-element-index 
	      ring-buffer index-for-newest-element-in-interval
	      index-for-oldest-element-in-interval)
	do
    (cond
      ((or (=f index-for-median-element-in-interval
	       index-for-oldest-element-in-interval)
	   (=f index-for-median-element-in-interval
	       index-for-newest-element-in-interval))
       (if (/=f index-for-oldest-element-in-interval
		index-for-newest-element-in-interval)
	   ;; Pick one or the other based on closest to history time.
	   ;; This extra check is necessary when history-time is closest
	   ;; to time for newest or oldest data point.  See notes in design book
	   ;; for 3/30/88.
	   (setq index-for-median-element-in-interval
		 (if (< (abs (- history-time 
				(get-history-time
				  ring-buffer index-for-oldest-element-in-interval)))
			(abs (- history-time 
				(get-history-time
				  ring-buffer index-for-newest-element-in-interval))))
		     index-for-oldest-element-in-interval
		     index-for-newest-element-in-interval)))
       (return
	 (results-of-element-search
	   cascaded-ring-buffer?
	   ring-buffer index-for-median-element-in-interval
	   (when (not (=f index-for-median-element-in-interval
			  (newest-active-element-index ring-buffer)))
	     (get-history-time 
	       ring-buffer
	       (increment-active-element-index
		 index-for-median-element-in-interval ring-buffer))))))
      (t
       (let ((time-for-median-element
	       (get-history-time
			     ring-buffer index-for-median-element-in-interval)))
	 (if (< history-time time-for-median-element)
	     (setq index-for-newest-element-in-interval
		   index-for-median-element-in-interval)
	     (setq index-for-oldest-element-in-interval
		   index-for-median-element-in-interval))
	 (setq index-for-median-element-in-interval
	       (get-median-element-index 
		 ring-buffer index-for-newest-element-in-interval
		 index-for-oldest-element-in-interval)))))))

;; replace with cascaded-ring-buffer version and change both callers in graphs2
;; and the one caller in graph-util

(defun get-history-index-by-binary-search
			(cascaded-ring-buffer history-time relative-p)
  (nth-value
    3 (get-history-element-by-binary-search cascaded-ring-buffer history-time relative-p)))

;; Used in GRAPHS2 - strange but supportable??

(defun get-previous-history-time ()
  (let* ((ring-buffer (car (cascaded-ring-buffers
			     previous-cascaded-ring-buffer-accessed)))
	 (previous-index
	   (if (=f previous-index-for-ring-buffer
		   (oldest-active-element-index ring-buffer))
	       previous-index-for-ring-buffer
	       (decrement-active-element-index
		 previous-index-for-ring-buffer ring-buffer))))
    (get-history-current-time
      previous-cascaded-ring-buffer-accessed previous-index nil)))


;;; Get-ring-buffer-element-using-best-search returns the value, time, and index
;;; of the element immediately preceding history-time.  It also returns the
;;; history time for the next element, if there is one.

;; Only used in GRAPHS2
;; make new function called
;; (defun get-history-element-using-best-search (crb history-time)
;;   ...
;; This will eliminate another ring buffer reference in graphs2.lisp

(defun get-history-element-using-best-search (cascaded-ring-buffer history-time relative-p)
  (if (eq cascaded-ring-buffer previous-cascaded-ring-buffer-accessed)
      (get-history-element-by-linear-search cascaded-ring-buffer history-time relative-p)
      (get-history-element-by-binary-search cascaded-ring-buffer history-time relative-p)))



;; Used in overwriting old data

(defun get-ring-buffer-element-at-history-time (ring-buffer history-time)
  (let ((previous-cascaded-ring-buffer-accessed nil)
	(previous-index-for-ring-buffer nil))
    (get-ring-buffer-element-by-binary-search nil ring-buffer history-time)))

;; Note that this currently only uses binary search.  This is currently
;; used only in histories.  Review and improve so that it uses
;; get-ring-buffer-element-using-best-search!!


(defun get-median-element-index (ring-buffer newest-element-index oldest-element-index)
  (let* ((ring-buffer-size
	   (ring-buffer-size ring-buffer))
	 (ring-buffer-length
	   (if (>=f newest-element-index
		    oldest-element-index)
	       (-f newest-element-index
		   oldest-element-index)
	       (-f (+f newest-element-index
		       ring-buffer-size)
		   oldest-element-index)))
	 (ring-buffer-half-length
	   (halff ring-buffer-length)))
    (modf (+f oldest-element-index ring-buffer-half-length)
	  ring-buffer-size)))




;;;; History Dependent Functions

;; Delay is the most basic history function.  Most others can (at least
;; theoretically) be derived from it.

;; These history functions have to be smart about detecting subtle problems such
;; as when an interval is specified and little or no data was collected during
;; this interval.  Currently, it is up to the user to make sure things are
;; collected and to call history functions only with intervals that have
;; collected data.  Eventually, These functions may be a little smarter about
;; detecting such problems.  Currently, if no value can be found, a warning will
;; be send and all nils will be returned as the value.

;; When a value is stored in a simulation history, the history time stored 
;; is the seconds portion of simulation-time.  When a value is stored in an 
;; inference engine history, the history time stored is gensym-time - 
;; gensym-time-at-start.  Thus, history times, whether for simulated or
;; inference engine histories, always begin at 0 at start.  Therefore,
;; the delay times passed as arguments to these functions must be offset
;; appropriately if necessary.  It is the responsibility of the evaluators
;; to do this.  I made some modifications in the history evaluators in
;; eval so that this would be done correctly.  Simulation evaluators for
;; histories should not have to do this offset since simulation-time
;; begins at 0 at start.

;;; If the no-value-if-empty-history?  argument is non-nil, no-value is returned
;;; when histories are being kept, but the history contains no values.  Most
;;; history-functions will return no value in this case.  An exception is
;;; number-of-datapoints.  When this argument is nil, the defined history
;;; function needs to test if value-history-ring-buffer-or-cascade is nil.  Note
;;; that this argument does not affect the return value when no histories are
;;; being kept.  - cpm, 12/2/91

;;; Note that if the frame-of-class-p is not a variable, there is only one
;;; history buffer, and it is the buffer used. However this buffer has a base
;;; time which is derived from get-unix-time and must be treated in that manner
;;; otherwise the value of the time is not only unaccessaable but
;;; outside of the range of our fixnums -rdf, 4/4/96

(declare-forward-reference simulation-no-value variable)

(defmacro define-history-function
	  (function-name function-args history-values-must-be-numeric? 
	   no-value-if-empty-history? &body body)
  `(defun ,function-name (variable value-requested-by-simulator? ,@function-args)

     (cond
       ((and ,history-values-must-be-numeric?
	     (not (number-subtype-p 
		    (data-type-of-variable-or-parameter variable))))
	(stack-error
	  cached-top-of-stack
	  "The history function ~a, which requires numeric data, ~
               tried to use the history of the variable ~NF, which has a ~
              non-numeric data type."
	  ',function-name variable)
	nil)
       (t
	(let* ((history-being-kept? nil)
	       (referencing-simulation-history? value-requested-by-simulator?)
	       (value-history-cascaded-ring-buffer
		 (if (and value-requested-by-simulator?
			  (frame-of-class-p variable 'variable)) ; not parameter
		     (let* ((simulation-subtable?
			      (simulation-details variable))
			    (simulation-stored-histories?
			      (if simulation-subtable?
				  (simulation-stored-histories?
				    simulation-subtable?))))
		       (setq history-being-kept?
			     (not (null
				    (and simulation-subtable?
					 (simulation-stored-history-specification?
					   simulation-subtable?)))))
		       (if (or (null history-being-kept?)
			       ;(not simulation-subtable?)
			       ;(not (simulation-stored-history-specification? simulation-subtable?))
			       (not simulation-stored-histories?)
			       (cascaded-ring-buffer-empty?
				 simulation-stored-histories?))
			   (progn
;			     (warning-message
;			       3
;			       "Simulated history data was requested for the ~
;                               variable ~a in ~a but none is available."
;			       (get-or-make-up-designation-for-block variable)
;			       (get-or-make-up-designation-for-block *current-computation-frame*))
			     nil)
			   simulation-stored-histories?))
		     (let ((variable-or-parameter-stored-histories?
			     (variable-or-parameter-stored-histories?
			       variable)))
		       (setq referencing-simulation-history? nil)
		       (setq history-being-kept?
			     (not (null
				    (variable-or-parameter-history-specification?
				      variable))))
		       (if (or (null history-being-kept?)
			       ;(not (variable-or-parameter-history-specification? variable))
			       (not (variable-or-parameter-stored-histories?
				      variable))
			       (cascaded-ring-buffer-empty?
				 variable-or-parameter-stored-histories?))
			   (progn
;			     (warning-message
;			       3
;			       "History data was requested for the variable or ~
;                               parameter ~a in ~a but none is available."
;			       (get-or-make-up-designation-for-block variable)
;			       (get-or-make-up-designation-for-block *current-computation-frame*))
			     nil)
			   variable-or-parameter-stored-histories?))))
	       value-history-ring-buffer-or-cascade)
	  (cond
	    ((and (not value-history-cascaded-ring-buffer)
		  (or (null history-being-kept?) ,no-value-if-empty-history?))
	     nil)
	    (t
	     (setq value-history-ring-buffer-or-cascade
		   (and value-history-cascaded-ring-buffer
			(car (cascaded-ring-buffers value-history-cascaded-ring-buffer))))
	     (progn ,@body))))))))

;; When cascaded ring buffer mechanism is hooked up, value-history-ring-buffer-
;; or-cascade should be set to value-history-cascaded-ring-buffer if there is
;; more than one ring buffer in the cascaded-ring-buffers slot.

;; Consider combining portions of define-history-function with-value-history-
;; ring-buffer-or-cascade.

 

;;; `with-value-history-ring-buffer-or-cascade' duplicates some of the
;;; functionality of define-history-function, but has no messages. It is
;;; non-standard in several ways. It expects
;;; variable-parameter-or-simulation-subtable and simulation-subtable? to be
;;; bound to symbols at macro-expand time. The former is the local variable or
;;; argument holding a frame, the later is boolean and (at run time) is t if
;;; the former is a simulation-subtable. 

;;; If there is no history, it does nothing. Otherwsie, it binds
;;; value-history-ring-buffer-or-cascade, and executes the body. It is a
;;; suitable environemnt for iterate-over-history.

(defmacro with-value-history-ring-buffer-or-cascade
    ((variable-parameter-or-simulation-subtable simulation-subtable?)
     &body body)
  `(let ((value-history-cascaded-ring-buffer?
	   (if ,simulation-subtable?
	       (simulation-stored-histories?
		 ,variable-parameter-or-simulation-subtable)
	       (variable-or-parameter-stored-histories?
		 ,variable-parameter-or-simulation-subtable))))
     (when (and value-history-cascaded-ring-buffer?
		(not (cascaded-ring-buffer-empty?
		       value-history-cascaded-ring-buffer?)))
       (let ((value-history-ring-buffer-or-cascade
	       (car (cascaded-ring-buffers
		      value-history-cascaded-ring-buffer?))))
	 ,@body))))



;;; `with-value-history-ring-buffer-or-cascade-1' is a variant of
;;; with-value-history-ring-buffer-or-cascade for use when the buffer is given.

(defmacro with-value-history-ring-buffer-or-cascade-1
	  ((value-history-cascaded-ring-buffer) &body body)
  (let ((cascaded-buffer (gensym)))
    `(let ((,cascaded-buffer ,value-history-cascaded-ring-buffer))
       (when (not (cascaded-ring-buffer-empty? ,cascaded-buffer))
	 (let ((value-history-ring-buffer-or-cascade
		 (car (cascaded-ring-buffers ,cascaded-buffer))))
	   ,@body)))))




;;; `iterate-over-history' is a macro used only with the body of
;;; define-history-function or with-value-history-ring-buffer-or-cascade.  It
;;; iterates over all values in value-history-ring-buffer-or-cascade oldest
;;; first, assigning values to the local variables history-value and
;;; history-collection-time while executing its body.  It does not have a useful
;;; value.  Note that oldest-active-element-index, newest-active-element-index
;;; and element-index are also bound around body.

(defmacro iterate-over-history (&body body)
  `(block iterate-over-history
     (loop with oldest-active-element-index =
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade)
	   with newest-active-element-index =
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade)
	   with history-value
	   with history-collection-time
	   with points-read = 0
	   with element-index = oldest-active-element-index
	   with initial-element-index? = t
	   do
       (with-temporary-gensym-float-creation iterate-over-history
	 (loop do
	   (if initial-element-index?
	       (setq initial-element-index? nil)
	       (setq element-index
		     (increment-active-element-index-for-ring-buffer-or-cascade
		       element-index value-history-ring-buffer-or-cascade)))
	   (multiple-value-setq
	       (history-value history-collection-time)
	     (get-history-ring-buffer-element
	       value-history-ring-buffer-or-cascade element-index))
	   (incff points-read)
	       ,@body
	       until (or (indices-same-for-ring-buffer-or-cascade-p
			   element-index newest-active-element-index)
			 ;; Prevent temporary float area overflow.
			 (=f (modf-positive points-read 500) 0))))
	   until (indices-same-for-ring-buffer-or-cascade-p
		   element-index newest-active-element-index)
;        finally
;          (reclaim-element-index-for-cascaded-ring-buffer
;            oldest-active-element-index) 
;          (reclaim-element-index-for-cascaded-ring-buffer
;            newest-active-element-index)
	 )))


 
;;; The macro `iterate-over-history-using-evaluation-values' is similar to
;;; iterate-over-history, except
;;;
;;;    (a) the block is named iterate-over-history-using-evaluation-values
;;;        rather than iterate-over-history; and
;;;
;;;    (b) there is a required first arg containing a structured
;;;        variable bindings list and a list of parameters (see below)
;;;
;;; The first argument is required and is of the form
;;;
;;;    ((history-value-var history-collection-time-var)
;;;     (cascade use-unix-time-p simulated-history? evaluation-value-type))
;;;
;;; where history-value-var and history-collection-time-var should be
;;; variable symbols which will be bound on each iteration to each
;;; successive value (as an evaluation value) and its collection
;;; time, respectively; and where cascade ..., use-unix-time ...,
;;; simulated-history? ..., and evaluation-value-type is the evaluation
;;; value type (e.g., truth-value, number, etc.) of the elements.
;;;
;;; On each successive iteration, history-value-var is bound to the
;;; corresponding element of the history.  Note that the value is an
;;; evaluation-value copy of what's in the history, and should accordingly
;;; either be absorbed or reclaimed as a result of evaluating the code
;;; in body.
;;;
;;; As with iterate-over-history, note that oldest-active-element-index,
;;; newest-active-element-index and element-index are also bound around body.

(defmacro iterate-over-history-using-evaluation-values
    ((history-value-var history-collection-time-var)
     (cascade logicalp use-unix-time-p simulated-history? &optional absolute-start absolute-end)
     &body body)
  (avoiding-variable-capture (cascade logicalp &aux ring-buffer element-index
				      oldest-active-element-index newest-active-element-index)
    `(loop with ,ring-buffer = (car (cascaded-ring-buffers ,cascade))
 	   with ,oldest-active-element-index
	     = (or ,absolute-start
		   (get-oldest-active-element-index-for-ring-buffer-or-cascade ,ring-buffer))
 	   with ,newest-active-element-index
	     = (or ,absolute-end
		   (get-newest-active-element-index-for-ring-buffer-or-cascade ,ring-buffer))
 	   for ,element-index = ,oldest-active-element-index
 			      then (increment-active-element-index-for-ring-buffer-or-cascade
 				     ,element-index ,ring-buffer)
	   for ,history-value-var
	       = (get-history-value-evaluation-value
		   ,ring-buffer ,element-index ,logicalp)
	   for ,history-collection-time-var
	       = (if ,use-unix-time-p
		     (get-history-g2-time-as-evaluation-value
		       ,cascade ,element-index ,simulated-history?)
		     (get-history-current-time-as-evaluation-value
		       ,cascade ,element-index ,simulated-history?))
 	   do (progn ,@body)
 	   until (indices-same-for-ring-buffer-or-cascade-p
		   ,element-index ,newest-active-element-index))))








(defun return-history-value
       (variable history-value history-operator-string value-must-be-a-number?
	value-requested-by-simulator? computation-involves-interval? interval-ok?
	value-type)
  
  (multiple-value-bind 
    (value expiration? data-type)
      (if history-value
	  (if (or (not value-must-be-a-number?)
		  (numberp history-value))
	      (values history-value 'never value-type)
	      (progn
		(stack-error
		  cached-top-of-stack
		  "Non-numeric value encountered in history for ~NF while computing ~
                      ~a value request.  The value was ~a."
		  variable history-operator-string history-value)
		(if value-requested-by-simulator?
		    simulation-no-value
		    (values nil nil nil))))
	  (progn
	    (when (and computation-involves-interval? (null interval-ok?))
	      (stack-error
		cached-top-of-stack
		"The begin time of the interval specified is greater than the end time ~
                 while computing ~a value for ~NF."
		history-operator-string variable))
	    nil))
    (if value-requested-by-simulator?
	value
	(values value expiration? data-type))))
;; Consider making this a macro.





(defparameter max-number-of-history-evaluations 100)

(defmacro accumulate-total-number (next-history-value total-number)
  (declare (ignore next-history-value))
  (cond 
    ((not (symbolp total-number))
     (error "~%accumulate-total-number requires args to be symbols~%"))
    (t
     `(setq ,total-number (+f ,total-number 1)))))

(defmacro set-first-total-number (next-history-value total-number)
  (declare (ignore next-history-value))
  (cond 
    ((not (symbolp total-number))
     (error "~%set-first-total-number requires args to be symbols~%"))
    (t
     `(setq ,total-number 1))))

(defmacro accumulate-maximum-value (next-history-value max-val)
  (cond 
    ((not (symbolp max-val))
     (error "~%accumulate-minimum-value requires args to be symbols~%"))
    (t
     `(setq ,max-val (max ,max-val ,next-history-value)))))


(defmacro set-first-maximum-value (next-history-value max-val)
  (cond 
    ((not (symbolp max-val))
     (error "~%set-first-minimum-value requires args to be symbols~%"))
    (t
     `(setq ,max-val ,next-history-value))))


(defmacro accumulate-minimum-value (next-history-value min-val)
  (cond 
    ((not (symbolp min-val))
     (error "~%accumulate-minimum-value requires args to be symbols~%"))
    (t
     `(setq ,min-val (min ,min-val ,next-history-value)))))


(defmacro set-first-minimum-value (next-history-value min-val)
  (cond 
    ((not (symbolp min-val))
     (error "~%set-first-minimum-value requires args to be symbols~%"))
    (t
     `(setq ,min-val ,next-history-value))))


(defmacro accumulate-average-value (next-history-value sum number-of-values)
  (cond 
    ((or (not (symbolp sum))
	 (not (symbolp number-of-values)))
     (error "~%accumulate-average-value requires args to be symbols~%"))
    (t
     `(setq ,sum (+ ,sum ,next-history-value)
	    ,number-of-values (+f ,number-of-values 1)))))

(defmacro set-first-average-value (next-history-value sum number-of-values)
  (cond 
    ((or (not (symbolp sum))
	 (not (symbolp number-of-values)))
     (error "~%set-first-average-value requires args to be symbols~%"))
    (t
     `(setq ,sum ,next-history-value
	    ,number-of-values (incf ,number-of-values)))))

(defmacro accumulate-sum-of-values (next-history-value sum)
  (cond 
    ((not (symbolp sum))
     (error "~%accumulate-sum-of-values requires args to be symbols~%"))
    (t
     `(setq ,sum (+ ,sum ,next-history-value)))))

(defmacro set-first-sum-of-values (next-history-value sum)
  (cond 
    ((not (symbolp sum))
     (error "~%set-first-sum-of-values requires args to be symbols~%"))
    (t
     `(setq ,sum ,next-history-value))))

(defmacro accumulate-standard-deviation-value
	  (next-history-value sum square-sum number-of-values)
  (cond 
    ((or (not (symbolp sum))
	 (not (symbolp square-sum))
	 (not (symbolp number-of-values)))
     (error "~%set-first-standard-deviation-value requires args to be symbols~%"))
    (t
     `(setq ,sum (+ ,sum ,next-history-value)
	    ,square-sum (+ ,square-sum
			   (* ,next-history-value ,next-history-value))
	    ,number-of-values (+f ,number-of-values 1)))))


(defmacro set-first-standard-deviation-value
	  (next-history-value sum square-sum number-of-values)
  (cond 
    ((or (not (symbolp sum))
	 (not (symbolp square-sum))
	 (not (symbolp number-of-values)))
     (error "~%set-first-standard-deviation-value requires args to be symbols~%"))
    (t
     `(setq ,sum ,next-history-value
	    ,square-sum (* ,next-history-value ,next-history-value)
	    ,number-of-values (+f ,number-of-values 1)))))



(defmacro accumulate-integral-value
	  (next-history-value running-sum previous-value previous-time)
  (cond 
    ((or (not (symbolp running-sum))
	 (not (symbolp previous-value))
	 (not (symbolp previous-time)))
     (error "accumulate-integral-value requires args to be symbols~%"))
    (t
     `(setq ,running-sum 
	    (+ ,running-sum
	       (* ,previous-value
		  (- storage-time ,previous-time)))
	    ,previous-value ,next-history-value
	    ,previous-time storage-time))))


(defmacro accumulate-final-integral-value
	  (next-history-value running-sum previous-value previous-time)
  (declare (ignore next-history-value))
  (cond 
    ((or (not (symbolp running-sum))
	 (not (symbolp previous-value))
	 (not (symbolp previous-time)))
     (error "accumulate-final-integral-value requires args to be symbols~%"))
    (t
     `(setq ,running-sum 
	    (+ ,running-sum
	       (* ,previous-value
		  (- interval-end-time ,previous-time)))))))


(defmacro set-first-integral-value
	  (next-history-value running-sum previous-value previous-time)
  (cond 
    ((or (not (symbolp running-sum))
	 (not (symbolp previous-value))
	 (not (symbolp previous-time)))
     (error "~%set-first-integral-value requires args to be symbols~%"))
    (t
     `(setq ,running-sum
	    (+ ,running-sum
	       (* ,previous-value
		  (- storage-time interval-begin-time)))
	    ,previous-value ,next-history-value
	    ,previous-time storage-time))))

;;; The times in the `set-first-rate-of-change-value' and
;;; `accumulate-rate-of-change-value' are stored using the managed number
;;; facility because their values will be referenced outside the expansion
;;; of accumulate-historical-result in the function
;;; get-rate-of-change-of-value.  In that function the managed-numbers holding
;;; the four timestamps will be reclaimed if necessary.

(defmacro set-first-rate-of-change-value
	  (next-history-value first-value-in-interval 
	   second-value-in-interval
	   next-to-last-value-in-interval last-value-in-interval)
  (declare (ignore second-value-in-interval
		   next-to-last-value-in-interval last-value-in-interval))
  (cond 
    ((or (not (symbolp first-value-in-interval)))
     (error "~%set-first-rate-of-change-value requires args to be symbols~%"))
    (t
     `(progn (setq ,first-value-in-interval ,next-history-value)
	     (store-managed-number time-of-first-value-in-interval storage-time)))))

(defmacro accumulate-rate-of-change-value
	  (next-history-value first-value-in-interval 
	   second-value-in-interval
	   next-to-last-value-in-interval last-value-in-interval)
  (cond 
    ((or (not (symbolp first-value-in-interval))
	 (not (symbolp second-value-in-interval))
	 (not (symbolp next-to-last-value-in-interval))
	 (not (symbolp last-value-in-interval)))
     (error "accumulate-rate-of-change-value requires args to be symbols~%"))
    (t
     `(cond
	((not ,second-value-in-interval)
	 (setq ,second-value-in-interval ,next-history-value)
	 (store-managed-number time-of-second-value-in-interval storage-time))
	((not ,last-value-in-interval)
	 (setq ,last-value-in-interval ,next-history-value)
	 (store-managed-number time-of-last-value-in-interval storage-time))
	((not ,next-to-last-value-in-interval)
	 (setq ,next-to-last-value-in-interval ,next-history-value)
	 (store-managed-number time-of-next-to-last-value-in-interval storage-time))
	(t
	 (setq ,next-to-last-value-in-interval
	       ,last-value-in-interval
	       ,last-value-in-interval
	       ,next-history-value)
	 (store-managed-number
	   time-of-next-to-last-value-in-interval
	   (extract-number time-of-last-value-in-interval))
	 (store-managed-number
	   time-of-last-value-in-interval
	   storage-time))))))




;;; Accumulate-historical-result modifies the arguments accumulated-value-1,
;;; accumulated-value-2, in-interval?, and element-index.  These are assumed to
;;; always be symbols (a compile time error is flagged if they are not).
;;; Accumulate-historical-result returns t if it finishes.

;;; Accumulate-historical-result is used to deal with temporary float issues.
;;; Rather than wrapping each call to get-history-value-for-cascaded-ring-buffer
;;; with a with-temporary-gensym-float-creation wrapper,
;;; accumulate-historical-result is used to perform more than one iteration
;;; within a temporary context.  The maximum number of iterations is specified
;;; by max-number-of-history-evaluations.

(defmacro accumulate-historical-result
	  (accumulated-value-1 accumulated-value-2 
	   accumulated-value-3 accumulated-value-4
	   element-index in-interval?
	   interval-begin-time interval-end-time
	   operator-to-set-values operator-to-accumulate-values
	   operator-to-accumulate-final-values
	   value-history-ring-buffer-or-cascade
	   value-history-cascaded-ring-buffer
	   newest-active-element-index
	   referencing-simulation-history?)
  (cond 
    ((or (not (symbolp accumulated-value-1))
	 (not (symbolp accumulated-value-2))
	 (not (symbolp accumulated-value-3))
	 (not (symbolp accumulated-value-4))
	 (not (symbolp element-index))
	 (not (symbolp in-interval?)))
     (error "~%accumulate-historical-result requires args to be symbols~%"))
    (t
     (let ((value-of-interval-end-time (gensym))
	   (value-of-ring-buffer (gensym))
	   (value-of-cascade-buffer (gensym)))
       `(let ((,value-of-interval-end-time ,interval-end-time)
	      (,value-of-ring-buffer ,value-history-ring-buffer-or-cascade)
	      (,value-of-cascade-buffer ,value-history-cascaded-ring-buffer)
	      ,@(when accumulated-value-1
		  `((temp-accumulated-value-1 nil)))
	      ,@(when accumulated-value-2
		  `((temp-accumulated-value-2 nil)))
	      ,@(when accumulated-value-3
		  `((temp-accumulated-value-3 nil)))
	      ,@(when accumulated-value-4
		  `((temp-accumulated-value-4 nil))))
	  (with-temporary-gensym-float-creation accumulate-historical-result

	    ,@(when accumulated-value-1
		`((setq temp-accumulated-value-1
			(extract-number ,accumulated-value-1))))
	    ,@(when accumulated-value-2
		`((setq temp-accumulated-value-2
			(extract-number ,accumulated-value-2))))
	    ,@(when accumulated-value-3
		`((setq temp-accumulated-value-3
			(extract-number ,accumulated-value-3))))
	    ,@(when accumulated-value-4
		`((setq temp-accumulated-value-4
			(extract-number ,accumulated-value-4))))

	    (loop with storage-time
		  for i from 1 to max-number-of-history-evaluations
		  do
	      (setq storage-time
		    (get-history-current-time
		      ,value-of-cascade-buffer ,element-index
		      ,referencing-simulation-history?))
	      (if (not ,in-interval?)
		  (when (and (>= storage-time
				 ,interval-begin-time)
			     (not (> storage-time
				     ,value-of-interval-end-time)))
		    (setq ,in-interval? t)
		    (let ((next-history-value
			    (get-history-value-for-ring-buffer-or-cascade
			      ,value-of-ring-buffer ,element-index)))
			  ;;never happens for the current uses of this macro		
		      #|(when (not (numberp next-history-value))
			(setq ,accumulated-value-1 next-history-value)
			(return t))|#
		      (,operator-to-set-values
		       next-history-value 
		       ,@(when accumulated-value-1 `(temp-accumulated-value-1))
		       ,@(when accumulated-value-2 `(temp-accumulated-value-2))
		       ,@(when accumulated-value-3 `(temp-accumulated-value-3))
		       ,@(when accumulated-value-4 `(temp-accumulated-value-4)))))
		  (let ((next-history-value
			  (get-history-value-for-ring-buffer-or-cascade
			    ,value-of-ring-buffer ,element-index)))
			;; never happens for the current uses of this macro		
		    #|(when (not (numberp next-history-value))
		      (setq ,accumulated-value-1 next-history-value)
		      (return t))|#
		    (cond
		      ((> storage-time ,value-of-interval-end-time)
		       ,@(when operator-to-accumulate-final-values
			   `((,operator-to-accumulate-final-values
			      next-history-value
			      ,@(when accumulated-value-1 `(temp-accumulated-value-1))
			      ,@(when accumulated-value-2 `(temp-accumulated-value-2))
			      ,@(when accumulated-value-3 `(temp-accumulated-value-3))
			      ,@(when accumulated-value-4 `(temp-accumulated-value-4)))))
		       ,(when accumulated-value-1
			  `(when temp-accumulated-value-1
			     (store-managed-number ,accumulated-value-1 temp-accumulated-value-1)))
		       ,(when accumulated-value-2
			   `(when temp-accumulated-value-2
			     (store-managed-number ,accumulated-value-2 temp-accumulated-value-2)))
		       ,(when accumulated-value-3
			   `(when temp-accumulated-value-3
			     (store-managed-number ,accumulated-value-3 temp-accumulated-value-3)))
		       ,(when accumulated-value-4
			   `(when temp-accumulated-value-4
			     (store-managed-number ,accumulated-value-4 temp-accumulated-value-4)))
		       (return t))
		      (t
		       (,operator-to-accumulate-values
			next-history-value 
			,@(when accumulated-value-1 `(temp-accumulated-value-1))
			,@(when accumulated-value-2 `(temp-accumulated-value-2))
			,@(when accumulated-value-3 `(temp-accumulated-value-3))
			,@(when accumulated-value-4 `(temp-accumulated-value-4)))))))
	      (when (or (= storage-time ,value-of-interval-end-time)
			(indices-same-for-ring-buffer-or-cascade-p
			  ,element-index ,newest-active-element-index))
		,@(when accumulated-value-1
		    `((when temp-accumulated-value-1
			(store-managed-number ,accumulated-value-1 temp-accumulated-value-1))))
		,@(when accumulated-value-2
		    `((when temp-accumulated-value-2
			(store-managed-number ,accumulated-value-2 temp-accumulated-value-2))))
		,@(when accumulated-value-3
		    `((when temp-accumulated-value-3
			(store-managed-number ,accumulated-value-3 temp-accumulated-value-3))))
		,@(when accumulated-value-4
		    `((when temp-accumulated-value-4
			(store-managed-number ,accumulated-value-4 temp-accumulated-value-4))))
		(return t))
	      (setq ,element-index
		    (increment-active-element-index-for-ring-buffer-or-cascade
		      ,element-index ,value-of-ring-buffer))
		  finally
		    ,@(when accumulated-value-1
			`((when temp-accumulated-value-1
			    (store-managed-number
			      ,accumulated-value-1 temp-accumulated-value-1))))
		    ,@(when accumulated-value-2
			`((when temp-accumulated-value-2
			    (store-managed-number
			      ,accumulated-value-2 temp-accumulated-value-2))))
		    ,@(when accumulated-value-3
			`((when temp-accumulated-value-3
			    (store-managed-number
			      ,accumulated-value-3 temp-accumulated-value-3))))
		    ,@(when accumulated-value-4
			`((when temp-accumulated-value-4			
			    (store-managed-number
			      ,accumulated-value-4 temp-accumulated-value-4))))
		    (return nil))))))))

;; Note the use of temp-accumulated-value-1 to avoid having to use store-managed-number
;; for every iteration.

;; Max-number-of-history-evaluations must be greater than 1.



;;; The function `get-number-of-datapoints-in-interval' counts the number of
;;; datapoints based on a begin and end interval time.  Note that the history
;;; times can be a float, so this function needs to be called from within a
;;; temporary gensym-float area.

(defun get-number-of-datapoints-in-interval
       (interval-begin-time interval-end-time
	value-history-ring-buffer-or-cascade
	value-history-cascaded-ring-buffer
	referencing-simulation-history?)
  (loop with storage-time 
	with oldest-active-element-index
	  = (get-oldest-active-element-index-for-ring-buffer-or-cascade
	      value-history-ring-buffer-or-cascade)
	with element-index 
	  = (get-newest-active-element-index-for-ring-buffer-or-cascade
	      value-history-ring-buffer-or-cascade)
	with in-interval? = nil
	with total-number = 0
	do
    (setq storage-time
	  (get-history-current-time
	    value-history-cascaded-ring-buffer
	    element-index
	    referencing-simulation-history?))
    (when (< storage-time interval-begin-time)
      (return total-number))
    (if (not in-interval?)
	(when (<= storage-time interval-end-time)
	  (setq in-interval? t
		total-number (+f total-number 1)))
	(setq total-number (+f total-number 1)))
    (when (indices-same-for-ring-buffer-or-cascade-p
	    element-index oldest-active-element-index)
      (return total-number))
    (setq element-index
	  (decrement-active-element-index-for-ring-buffer-or-cascade
	    element-index value-history-ring-buffer-or-cascade))))



;;; Get-interpolated-delayed-value takes a variable and a delay-time as an
;;; argument, computes a historical time by subtracting the delay-time from
;;; gensym time, and then interpolates using values stored immediately before
;;; and after the historical time.  If the history doesn't contain numeric
;;; values, then this will fail and an error message will be sent via
;;; notify-user.

(define-history-function get-interpolated-delayed-value (delay-time)
  t t
  (let* ((historical-time
	   delay-time)
	 (oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interpolated-delayed-value
	   (loop for element-index 
		     = newest-active-element-index
		     then (decrement-active-element-index-for-ring-buffer-or-cascade
			    element-index value-history-ring-buffer-or-cascade)
		 for storage-time 
		     = (get-history-current-time
			 value-history-cascaded-ring-buffer element-index
			 referencing-simulation-history?)
		 doing (cond
			 ((= storage-time
			     historical-time)
			  (return
			    (get-history-value-for-ring-buffer-or-cascade
			      value-history-ring-buffer-or-cascade element-index)))
			 ((< storage-time
			     historical-time)
			  (let ((delayed-value-1
				  (get-history-value-for-ring-buffer-or-cascade
				    value-history-ring-buffer-or-cascade element-index))
				(storage-time-1
				  (coerce-to-gensym-float storage-time))
				delayed-value-2
				storage-time-2)
			    (if (numberp delayed-value-1)
				(setq delayed-value-1
				      (coerce-to-gensym-float delayed-value-1))
				(return delayed-value-1))
			    (if (not (indices-same-for-ring-buffer-or-cascade-p
				       element-index
				       newest-active-element-index))
				(setq element-index
				      (increment-active-element-index-for-ring-buffer-or-cascade
					element-index value-history-ring-buffer-or-cascade))
				(return delayed-value-1))
			    (setq storage-time-2
				  (coerce-to-gensym-float
				    (get-history-current-time
				      value-history-cascaded-ring-buffer
				      element-index referencing-simulation-history?)))
			    (setq delayed-value-2
				  (get-history-value-for-ring-buffer-or-cascade
				    value-history-ring-buffer-or-cascade
				    element-index))
			    (if (numberp delayed-value-2)
				(setq delayed-value-2
				      (coerce-to-gensym-float delayed-value-2))
				(return delayed-value-2))
			    (if (= storage-time-1 storage-time-2)
				;; Actually not necessary.
				(return delayed-value-2))
			    (return 
			      (+
				delayed-value-1
				(*
				  (- historical-time storage-time-1)
				  (/ 
				    (- delayed-value-2 delayed-value-1)
				    (- storage-time-2 storage-time-1))))))))
		       
		 while (not (indices-same-for-ring-buffer-or-cascade-p
			      element-index
			      oldest-active-element-index)))))
    (return-history-value
      variable interpolated-delayed-value "an interpolated delayed"
      t value-requested-by-simulator? nil nil
      (type-specification-of-variable-or-parameter-value variable))))

;; Expiration is 'never.  Data-type is obtained from the current data type of
;; the variable.  Thus, if the data type of a variable changes, its history
;; should be cleared.  
;; Have to do some error checking to make sure data is continuous.
;; Also, this will get value delayed by at least delay-time.  The value
;; obtained may have actually be obtained much earlier.  It is up to
;; the user to avoid these kinds of problems, at least for now.


;;; Get-historical-delayed-value is like get-interpolated-delayed-value
;;; except that it doesn't interpolate.  The value stored exactly at
;;; or immediately before the historical time is returned.  Note that the
;;; value does not have to be a number.

(define-history-function get-historical-delayed-value (delay-time)
  nil t
  (let* (bottom
	 top
	 (oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (zero-index-time
	   (get-history-current-time
	     value-history-cascaded-ring-buffer 0
	     referencing-simulation-history?))
	 oldest-time
	 newest-time
	 top-time
	 bottom-time
	 (delayed-value nil)
	 (max-index-time 0)		; See Note!
	 value-time
	 (max-index (-f (ring-buffer-size
			  value-history-ring-buffer-or-cascade)
			     1)))
    (setq newest-time
	  (get-history-current-time
	      value-history-cascaded-ring-buffer newest-active-element-index
	      referencing-simulation-history?))
    (setq oldest-time
	  (get-history-current-time
	      value-history-cascaded-ring-buffer oldest-active-element-index
	      referencing-simulation-history?))


    ;; are we within range?
    (cond ((and (<= delay-time newest-time)
	       (>= delay-time oldest-time))
      ;; don't bother with the complexity if the binary search if the history
      ;; is small
      (cond ((>f max-index most-positive-fixnum) ; 20)
	     (setq zero-index-time (get-history-current-time
				     value-history-cascaded-ring-buffer 0
				     referencing-simulation-history?))
	     ;; set initial indices
	     (cond ((or (=f oldest-active-element-index 0)
			(and (< delay-time newest-time)
			     (> delay-time zero-index-time)))
		    (setq bottom 0)
		    (setq bottom-time zero-index-time)
		    (setq top newest-active-element-index)
		    (setq top-time newest-time))
		   
		   (t
		    (setq bottom oldest-active-element-index)
		    (setq bottom-time oldest-time)
		    (setq top-time
			  (get-history-current-time
			    value-history-cascaded-ring-buffer max-index
			    referencing-simulation-history?))
		    (setq top max-index)))
	     
	     (loop until (or (=f top bottom) delayed-value value-index)
		   with probe-index and probe-time
		   with value-index = nil
		   do (setq probe-index (+ bottom (truncate (- top bottom) 2)))
		      (when (=f probe-index bottom)
			(incff probe-index))
		      (setq probe-time (get-history-current-time
					 value-history-cascaded-ring-buffer probe-index
					 referencing-simulation-history?))
	       
		      (cond
			;;if only a choice of two, just find it
			((=f top (+ 1 bottom))
			 (cond ((> (- top delay-time)
				   (- delay-time bottom-time))
				(setq value-index bottom)
				(setq value-time bottom-time))
			       (t
				(setq value-index top)
				(setq value-time top-time)))
			 (cond ((= value-index 0)
				#+development ; See Note!
				(cerror "continue anyway"
					"Variable MAX-INDEX-TIME is being used in code previously assumed dead!")
				#-development
				(notify-user-at-console
				  "WARNING: suspected historical-delayed-value internal error.  Please report to Gensym.")
				(when (< (- delay-time max-index-time)
					 (- value-time delay-time))
				  (setq value-index max-index)))
			       ((= value-index max-index)
				(when (< (- zero-index-time delay-time)
					 (- delay-time value-time))
				  (setq value-index 0)))))
			((> probe-time delay-time)
			 (setq top-time probe-time)
			 (setq top probe-index))
			((< probe-time delay-time)
			 (setq bottom-time probe-time)
			 (setq bottom probe-index))
			((= probe-time delay-time)
			 (setq delayed-value
			       (get-history-value-for-ring-buffer-or-cascade
				 value-history-ring-buffer-or-cascade probe-index))))
		   finally
		     (unless delayed-value
		       (setq delayed-value
			     (get-history-value-for-ring-buffer-or-cascade 
			       value-history-ring-buffer-or-cascade value-index)))))
	    (t
	     ;; this is just the old algorithm
	     (setq delayed-value
		   (loop for element-index 
			     = newest-active-element-index
			     then (decrement-active-element-index-for-ring-buffer-or-cascade
				    element-index value-history-ring-buffer-or-cascade)
			 for storage-time 
			     = (get-history-current-time
				 value-history-cascaded-ring-buffer element-index
				 referencing-simulation-history?)
			 doing 
		     (if (<= storage-time delay-time)
			 (return
			   (get-history-value-for-ring-buffer-or-cascade
			     value-history-ring-buffer-or-cascade element-index)))
			 while (not (indices-same-for-ring-buffer-or-cascade-p
				      element-index
				      oldest-active-element-index)))))))
	  ((< newest-time delay-time)
	   (setq delayed-value
		 (get-history-value-for-ring-buffer-or-cascade
		   value-history-ring-buffer-or-cascade newest-active-element-index))
	   ))
    
    (return-history-value
      variable delayed-value "a delayed" nil value-requested-by-simulator?
      nil nil (type-specification-of-variable-or-parameter-value variable))))

;; Variable max-index-time.  Previously was implicitly bound to nil, but the
;; compiler noticed this was being used in arithmetic without ever getting set
;; to any useful value.  To still the compiler, it's now bound to 0, which is
;; arbitrary.  It's not currently known if this could ever be reached! Needs
;; research, and/or a check with the author (AGH).  (MHD 6/5/01)


;;; Get-value-of-previous-data-point takes an integer n and returns the value
;;; of the nth previous datapoint before the newest one.
;;; Get-collection-time-of-previous-data-point returns the time
;;; of the nth previous datapoint.

(define-history-function get-value-of-previous-datapoint (n)
  nil t
  (get-value-or-time-of-previous-data-point
    variable value-history-cascaded-ring-buffer
    value-history-ring-buffer-or-cascade
    value-requested-by-simulator?
    referencing-simulation-history?    
    n 'get-history-value-for-ring-buffer-or-cascade-function nil))


(define-history-function get-collection-time-of-previous-datapoint (n)
  nil t
  (get-value-or-time-of-previous-data-point
    variable value-history-cascaded-ring-buffer
    value-history-ring-buffer-or-cascade
    value-requested-by-simulator?
    referencing-simulation-history?
    n 'get-history-current-time t))

(defun get-value-or-time-of-previous-data-point 
       (variable value-history-cascaded-ring-buffer
		 value-history-ring-buffer-or-cascade
		 value-requested-by-simulator?
		 referencing-simulation-history?
		 n accessor-function type-is-time-stamp?)
  (let* ((element-index?
	   (compute-index-for-previous-data-point
	     value-history-ring-buffer-or-cascade n))
	 
	 (value-or-time-of-previous-datapoint
	   (when element-index?
	     (if type-is-time-stamp?
		 (funcall-symbol accessor-function
				 value-history-cascaded-ring-buffer
				 element-index? referencing-simulation-history?)
		 (funcall-symbol accessor-function
				 value-history-ring-buffer-or-cascade
				 element-index?)))))
    (return-history-value
      variable value-or-time-of-previous-datapoint "a previous datapoint" nil 
      value-requested-by-simulator? nil nil 
      (if type-is-time-stamp? 
	  'number
	  (type-specification-of-variable-or-parameter-value variable)))))

(defun compute-index-for-previous-data-point
       (ring-buffer-or-cascade n)
  (let* ((newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     ring-buffer-or-cascade))
	 unwrapped-index)
    (when (not (>=f n (get-total-length-of-ring-buffer-or-cascade
			ring-buffer-or-cascade)))
      (setq unwrapped-index
	    (-f newest-active-element-index n))
      (if (>=f unwrapped-index 0)
	  unwrapped-index
	  (+f (ring-buffer-size ring-buffer-or-cascade) unwrapped-index)))))

;; This will become more sophisticated when the full cascaded ring buffer
;; capability is used.



;;; Number-of-datapoints takes a variable, and optionally, an interval begin time, and
;;; an interval end time.  The number of datapoints stored in the interval will be
;;; returned.  If no interval is specified, the number of datapoints in the entire
;;; history ring buffer (the length of the history ring buffer) is returned.

(define-history-function number-of-datapoints
			 (interval-begin-time? interval-end-time?) 
  nil nil
  (let* ((interval-ok?
	   (or (null interval-begin-time?)
	       (and (not (nanp interval-begin-time?))
		    (not (nanp interval-end-time?))
		    (<= interval-begin-time? interval-end-time?))))
	 (number-of-datapoints
	   (cond
	      ;; History is being kept, but the history is empty.
	     ((null value-history-ring-buffer-or-cascade) 0)
	     ((null interval-begin-time?)   ; no interval specified
	      (get-total-length-of-ring-buffer-or-cascade
		value-history-ring-buffer-or-cascade))
	     (t
	      (when interval-ok?
		(get-number-of-datapoints-in-interval
		  interval-begin-time? interval-end-time?
		  value-history-ring-buffer-or-cascade
		  value-history-cascaded-ring-buffer
		  referencing-simulation-history?))))))
    (return-history-value
      variable number-of-datapoints "number of history datapoints" nil
      value-requested-by-simulator? interval-begin-time? interval-ok? 'integer)))




;;; Get-maximum-value will take a variable, an interval begin time, and
;;; an interval end time.  The maximum of the values stored in the interval
;;; will be returned.  If non-numeric values are encountered in the interval,
;;; then this will fail and an error message will be sent via notify-user.

(define-history-function get-maximum-value 
			 (interval-begin-time interval-end-time) 
  t t
  (let* ((oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interval-ok?
	   (and (not (nanp interval-begin-time))
		(not (nanp interval-end-time))
		(<= interval-begin-time interval-end-time)))
	 (maximum-value
	   (when interval-ok?
	     (loop with in-interval? = nil
		   with max-val? = nil
		   with element-index = oldest-active-element-index
		   as done?
		      = (accumulate-historical-result
			  max-val? nil nil nil
			  element-index in-interval?
			  interval-begin-time interval-end-time
			  set-first-maximum-value
			  accumulate-maximum-value nil
			  value-history-ring-buffer-or-cascade
			  value-history-cascaded-ring-buffer
			  newest-active-element-index
			  referencing-simulation-history?)
		   do
	       (when done?
		 (return (prog1 (extract-number max-val?)
				(reclaim-managed-number-or-value max-val?))))))))
;    (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;    (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)
    (return-history-value
      variable maximum-value "a maximum" t value-requested-by-simulator? t
      interval-ok? (type-specification-of-variable-or-parameter-value variable))))



;;; Get-minimum-value will take a variable, an interval begin time, and
;;; an interval end time.  The minimum of the values stored in the interval
;;; will be returned.  If non-numeric values are encountered in the interval,
;;; then this will fail and an error message will be sent via notify-user.

(define-history-function get-minimum-value 
			 (interval-begin-time interval-end-time)
  t t
  (let* ((oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interval-ok?
	   (and (not (nanp interval-begin-time))
		(not (nanp interval-end-time))
		(<= interval-begin-time interval-end-time)))
	 (minimum-value
	   (when interval-ok?
	     (loop with in-interval? = nil
		   with min-val? = nil
		   with element-index = oldest-active-element-index
		   as done?
		      = (accumulate-historical-result
			  min-val? nil nil nil
			  element-index in-interval?
			  interval-begin-time interval-end-time
			  set-first-minimum-value
			  accumulate-minimum-value nil
			  value-history-ring-buffer-or-cascade
			  value-history-cascaded-ring-buffer
			  newest-active-element-index
			  referencing-simulation-history?)
		   do
	       (when done?
		 (return (prog1 (extract-number min-val?)
				(reclaim-managed-number-or-value min-val?))))))))
;    (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;    (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)
    (return-history-value
      variable minimum-value "minimum" t value-requested-by-simulator? t interval-ok?
      (type-specification-of-variable-or-parameter-value variable))))



;;; Get-averaged-value will take a variable, an interval begin time, and
;;; an interval end time.  The average of the values stored in the interval
;;; will be returned.

(define-history-function get-averaged-value 
       (interval-begin-time interval-end-time)
  t t
  (let* ((oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interval-ok?
	   (and (not (nanp interval-begin-time))
		(not (nanp interval-end-time))
		(<= interval-begin-time interval-end-time)))
	 (averaged-value
	   (when interval-ok?
	     (loop with in-interval? = nil
		   with sum = nil
		   with number-of-values = 0
		   with element-index = oldest-active-element-index
		   with result-sum
		   as done?
		      = (accumulate-historical-result
			  sum number-of-values nil nil
			  element-index in-interval?
			  interval-begin-time interval-end-time
			  set-first-average-value
			  accumulate-average-value nil
			  value-history-ring-buffer-or-cascade
			  value-history-cascaded-ring-buffer
			  newest-active-element-index
			  referencing-simulation-history?)
		   do
	       (when done?
		 (setq result-sum (extract-number sum))
		 (reclaim-managed-number-or-value sum)
		 (if result-sum
		     (if (numberp result-sum)
			 (return
			   (/e (coerce-to-gensym-float result-sum)
			       (coerce-to-gensym-float (extract-number number-of-values))))
			 (return result-sum))
		     (return nil)))))))
;    (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;    (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)
    (return-history-value
      variable averaged-value "average" t value-requested-by-simulator? t interval-ok?
      (type-specification-of-variable-or-parameter-value variable))))

;;; Get-sum-of-values will take a variable, an interval begin time, and
;;; an interval end time.  The sum of the values stored in the interval
;;; will be returned.

(define-history-function get-sum-of-values 
       (interval-begin-time interval-end-time)
  t t
  (let* ((oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interval-ok?
	   (and (not (nanp interval-begin-time))
		(not (nanp interval-end-time))
		(<= interval-begin-time interval-end-time)))
	 (sum-of-values
	   (when interval-ok?
	     (loop with in-interval? = nil
		   with sum = nil
		   with element-index = oldest-active-element-index
		   with result-sum
		   as done?
		      = (accumulate-historical-result
			  sum nil nil nil
			  element-index in-interval?
			  interval-begin-time interval-end-time
			  set-first-sum-of-values
			  accumulate-sum-of-values nil
			  value-history-ring-buffer-or-cascade
			  value-history-cascaded-ring-buffer
			  newest-active-element-index
			  referencing-simulation-history?)
		   do
	       (when done?
		 (setq result-sum (extract-number sum))
		   (when (managed-float-p sum)
			(reclaim-managed-float sum)) ;maybe check for int64 too?
		     (if (numberp result-sum)
			 (return
			   (coerce-to-gensym-float result-sum))
			 (return
			   (coerce-to-gensym-float 0.0))))))))
;    (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;    (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)
    (return-history-value
      variable sum-of-values "sum" t value-requested-by-simulator? t interval-ok?
      (type-specification-of-variable-or-parameter-value variable))))

;; Notes on algorithms of "standard deviation".
;;
;; For all history values falling into the specific time interval, suppose we have
;; the value series as v1,v2,v3,...v_n, then G2 uses following formula to compute
;; the standard deciation:
;;
;;   SQRT of [ (sigma v_i ^ 2, i = 1 to n) / n - vv ^ 2 ]
;; in which
;;   vv = ( sigma v_i, i = 1 to n ) / n

(define-history-function get-standard-deviation-of-value 
       (interval-begin-time interval-end-time)
  t t
  (let* ((oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interval-ok?
	   (and (not (nanp interval-begin-time))
		(not (nanp interval-end-time))
		(<= interval-begin-time interval-end-time)))
	 (standard-deviation
	   (when interval-ok?
	     (loop with in-interval? = nil
		   with sum
		   with square-sum
		   with number-of-values = 0
		   with element-index = oldest-active-element-index
		   with result-sum
		   with result-square-sum
		   as done?
		      = (accumulate-historical-result
			  sum square-sum number-of-values nil
			  element-index in-interval?
			  interval-begin-time interval-end-time
			  set-first-standard-deviation-value
			  accumulate-standard-deviation-value nil
			  value-history-ring-buffer-or-cascade
			  value-history-cascaded-ring-buffer
			  newest-active-element-index
			  referencing-simulation-history?)
		   do
	       (when done?
		 (setq result-sum (extract-number sum)
		       result-square-sum (extract-number square-sum))
		   (when (managed-float-p sum)
			(reclaim-managed-float sum)) ;maybe check for int64 too?
		   (when (managed-float-p square-sum)
			(reclaim-managed-float square-sum)) ;maybe check for int64 too?
		     (if (numberp result-sum)
			 (return
			   (let* ((float-number-of-values
				    (coerce-to-gensym-float
				      (extract-number number-of-values)))
				  (average
				    (/e (coerce-to-gensym-float result-sum)
					float-number-of-values)))
			     (return 
			       (sqrte
				 (abse
				   (-e (/e (coerce-to-gensym-float 
					     result-square-sum)
					   float-number-of-values)
				       (*e average average)))))))
		     (return nil)))))))
;    (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;    (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)
    (return-history-value
      variable standard-deviation "standard deviation" 
      t value-requested-by-simulator? t interval-ok?
      (type-specification-of-variable-or-parameter-value variable))))

;; This is susceptible to floating point roundoff problems in extreme cases
;; (see design book notes for 8/10/88).

;; Notes on algorithms of "rate of change".
;;
;; For all history values falling into the specific time interval, suppose we have
;; the value series as v1,v2,v3,...v_n with correspond time series as t1,t2,t3,...
;; t_n, G2 actually use only the first two and the last two values to get the rate
;; of change.  If all four value were available, G2 uses follow formula to get the
;; result:
;;   (v_b - v_a) / (t_b - t_a) * u
;; in which
;;   v_a = (v1 + v2) / 2, v_b = (v_n-1 + v_n) / 2
;;   t_a = (t1 + t2) / 2, t_b = (t_n-1 + t_n) / 2
;; and u is the time unit in seconds. For example, using "per second" we have the
;; unit as 1, while "per minute" has the unit of 60, because one minute has 60
;; seconds.
;;
;; If there's just three history values, then above formula will be simplified into
;; following form:
;;   (v3 - v1) / (t3 - t1) * u
;; With just two history values, it will be
;;   (v2 - v1) / (t2 - t1) * u
;; And if there's just one history value falling into the time interval, the result
;; is zero (0).

(define-history-function get-rate-of-change-of-value
			 (units interval-begin-time interval-end-time)
  t t
  (let* ((oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interval-ok?
	   (and (not (nanp interval-begin-time))
		(not (nanp interval-end-time))
		(<= interval-begin-time interval-end-time)))
	 
	 (rate-of-change
	   (when interval-ok?
	     (loop with in-interval? = nil
		   with first-value-in-interval = nil
		   with second-value-in-interval = nil		
		   with last-value-in-interval = nil		
		   with next-to-last-value-in-interval = nil		
		   with time-of-first-value-in-interval = nil
		   with time-of-second-value-in-interval = nil		
		   with time-of-last-value-in-interval = nil		
		   with time-of-next-to-last-value-in-interval = nil		
		   with element-index = oldest-active-element-index
		   with first-result-value
		   with second-result-value
		   with next-to-last-result-value
		   with last-result-value
		   ;; time as unmanaged numbers
		   with unmanaged-time-of-first-value = nil
		   with unmanaged-time-of-second-value = nil
		   with unmanaged-time-of-next-to-last-value = nil
		   with unmanaged-time-of-last-value = nil
		   as done?
		      = (accumulate-historical-result
			  first-value-in-interval
			  second-value-in-interval
			  next-to-last-value-in-interval
			  last-value-in-interval
			  element-index in-interval?
			  interval-begin-time interval-end-time
			  set-first-rate-of-change-value
			  accumulate-rate-of-change-value nil
			  value-history-ring-buffer-or-cascade
			  value-history-cascaded-ring-buffer
			  newest-active-element-index
			  referencing-simulation-history?)
		   do
	       (when done?
		 (setq first-result-value
		       (extract-number first-value-in-interval)
		       second-result-value
		       (extract-number second-value-in-interval)
		       next-to-last-result-value
		       (extract-number next-to-last-value-in-interval)
		       last-result-value
		       (extract-number last-value-in-interval)
		       unmanaged-time-of-first-value
		       (if time-of-first-value-in-interval
			   (extract-number time-of-first-value-in-interval))
		       unmanaged-time-of-second-value
		       (if time-of-second-value-in-interval
			   (extract-number time-of-second-value-in-interval))
		       unmanaged-time-of-next-to-last-value
		       (if time-of-next-to-last-value-in-interval
			   (extract-number
			     time-of-next-to-last-value-in-interval))
		       unmanaged-time-of-last-value
		       (if time-of-last-value-in-interval
			   (extract-number time-of-last-value-in-interval)))
		 (reclaim-managed-number-or-value first-value-in-interval)
		 (reclaim-managed-number-or-value second-value-in-interval)
		 (reclaim-managed-number-or-value
		   next-to-last-value-in-interval)
		 (reclaim-managed-number-or-value last-value-in-interval)

		 (reclaim-managed-number-or-value
		   time-of-first-value-in-interval)
		 (reclaim-managed-number-or-value
		   time-of-second-value-in-interval)
		 (reclaim-managed-number-or-value
		   time-of-next-to-last-value-in-interval)
		 (reclaim-managed-number-or-value
		   time-of-last-value-in-interval)

		 (if first-result-value
		     (if (numberp first-result-value)
			 (return
			   (cond
			     ((not first-result-value))
			     ((not second-result-value) 0)
			     ((not last-result-value)
			      (/e
				(coerce-to-gensym-float
				  (- second-result-value
				     first-result-value))
				(coerce-to-gensym-float
				  (- unmanaged-time-of-second-value
				     unmanaged-time-of-first-value))))
			     ((not next-to-last-result-value)
			      (/e
				(coerce-to-gensym-float
				  (- last-result-value
				     first-result-value))
				(coerce-to-gensym-float
				  (- unmanaged-time-of-last-value
				     unmanaged-time-of-first-value))))
			     (t
			      (let ((begin-point-value
				      (+ first-result-value
					 (/e (coerce-to-gensym-float
					       (- second-result-value
						  first-result-value))
					     2.0)))
				    (begin-point-time
				      (+ unmanaged-time-of-first-value
					 (/e
					   (coerce-to-gensym-float
					     (- unmanaged-time-of-second-value
						unmanaged-time-of-first-value))
					     2.0)))
				    (end-point-value
				      (+ next-to-last-result-value
					 (/e (coerce-to-gensym-float
					       (- last-result-value
						  next-to-last-result-value))
					     2.0)))
				    (end-point-time
				      (+ unmanaged-time-of-next-to-last-value
					 (/e
					   (coerce-to-gensym-float
					     (- unmanaged-time-of-last-value
						unmanaged-time-of-next-to-last-value))
					     2.0))))
				(/e
				  (coerce-to-gensym-float
				    (- end-point-value
				       begin-point-value))
				  (coerce-to-gensym-float
				    (- end-point-time
				       begin-point-time)))))))
			 (return first-result-value))
		     (return nil)))))))

;    (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;    (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)

    (if (numberp rate-of-change)
	(setq rate-of-change (* rate-of-change units)))

    (return-history-value
      variable rate-of-change "rate of change" t value-requested-by-simulator? t interval-ok?
      (type-specification-of-variable-or-parameter-value variable))))

;; Notes on algorithms of "integral".
;;
;; For all history values falling into the specific time interval, suppose we have
;; the value series as v1,v2,v3,...v_n with correspond time series as t1,t2,t3,...
;; t_n, then G2 uses following formula to compute the integral:
;;
;;   [ sigma v_i-1 * (t_i - t_i-1), i = 1 to n ] / u
;;
;; in which t_0 is the start time of the specific time interval, v_0 is zero (0.0),
;; and u is the time unit in seconds. For example, using "in seconds of" we have
;; the unit as 1, while "in minutes of" has the unit of 60, because one minute has
;; 60 seconds.

(define-history-function get-integral-of-value-over-interval
       (units interval-begin-time interval-end-time)
  t t
  (let* ((oldest-active-element-index
	   (get-oldest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (newest-active-element-index
	   (get-newest-active-element-index-for-ring-buffer-or-cascade
	     value-history-ring-buffer-or-cascade))
	 (interval-ok?
	   (and (not (nanp interval-begin-time))
		(not (nanp interval-end-time))
		(<= interval-begin-time interval-end-time)))
	 (integral-value
	   (when interval-ok?
	     (loop with in-interval? = nil
		   with running-sum = 0.0
		   with previous-value = 0.0
		   with previous-time = nil
		   with element-index = oldest-active-element-index
		   as done?
		      = (accumulate-historical-result
			  running-sum previous-value previous-time nil
			  element-index in-interval?
			  interval-begin-time interval-end-time
			  set-first-integral-value
			  accumulate-integral-value
			  accumulate-final-integral-value
			  value-history-ring-buffer-or-cascade
			  value-history-cascaded-ring-buffer
			  newest-active-element-index
			  referencing-simulation-history?)
		   do
	       (when done?
		 (return (prog1 (extract-number running-sum)
				(reclaim-managed-number-or-value running-sum)
				(reclaim-managed-number-or-value previous-value)
				(reclaim-managed-number-or-value previous-time))))))))

;    (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;    (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)

    (if (numberp integral-value)
	(setq integral-value (/ integral-value units)))
    (return-history-value
      variable integral-value "integral" t value-requested-by-simulator? t interval-ok?
      (type-specification-of-variable-or-parameter-value variable))))

;; Consider dividing by units for each loop when running sum is being added to.
;; This would decrease efficiency but may increase accuracy in some cases where
;; the integral value may be large.




(define-history-function get-history-ring-buffer-if-any ()
    nil nil
  value-history-ring-buffer-or-cascade)






;;;; Adjusting Histories




;;; The following section includes operations to adjust the collection time of
;;; histories and operations to remove values from the history based on a
;;; given time or time change.




;;; The function `add-delta-to-all-history-buffer-times' is used to adjust all
;;; the history times in a history buffer.

;;; This is necessary in VERSION 3.0 warmboot data which did not have an
;;; explicit history base.  See also add-delta-to-history-buffer-base-time,
;;; which is used starting in VERSION 4.0.

(defun add-delta-to-all-history-buffer-times (buffer delta)
  (with-value-history-ring-buffer-or-cascade-1 (buffer)
    (iterate-over-history
      (null history-value)			; to avoid compiler warning
      (set-history-time
	value-history-ring-buffer-or-cascade
	element-index (+ history-collection-time delta))))
  buffer)



;;; The function `add-delta-to-history-buffer-base-time' is used to adjust the
;;; time-stamps of a history-buffer by adding a delta to the base-time.

;;; Note that base-times were used in version 4.0.  For 3.0 histories, see add-
;;; delta-to-all-history-buffer-times.

;;; If the base-time is not currently set, for example when the history has been
;;; cleared, this function does not modify the base-time.

(defun-void add-delta-to-history-buffer-base-time
    (history-buffer managed-float-delta)
  (let ((base-time? (cascaded-ring-buffer-base-time? history-buffer)))
    (when base-time?
      (with-temporary-gensym-float-creation
	  add-delta-to-history-buffer-base-time
	;; In this case, the new base-time will not be FLOOR'ed, as when the
	;; initial base-time is set.  This will allow the history times to be
	;; accurate to the subsecond, in relation to this delta time adjustment.
	(mutate-managed-float-value
	  base-time?
	  (+e (managed-float-value base-time?)
	      (managed-float-value managed-float-delta)))))))



;;; The function `add-delta-time-to-variables-and-parameters' is used to correct
;;; the history buffer, time of most recent value, etc. for all variables and
;;; parameters.  This function is called when there is a change (forward or
;;; back) in the g2 clock.

(defun add-delta-time-to-variables-and-parameters
    (managed-float-delta)
  (loop for parameter being each class-instance of 'parameter
	for history-buffer? =
	  (variable-or-parameter-stored-histories? parameter)
	do
    ;; Adjust the history base time.
    (when history-buffer?
      (note-change-to-runtime-data-for-block parameter)
      (add-delta-to-history-buffer-base-time
	history-buffer? managed-float-delta)))

  (loop for variable being each class-instance of 'variable
	for current-value-time? = (time-of-most-recent-value variable)
	for history-buffer? =
	  (variable-or-parameter-stored-histories? variable)
	for simulation-subtable? = (simulation-details variable)
	for simulation-history-buffer? =
	  (if simulation-subtable?
	      (simulation-stored-histories? simulation-subtable?))
	do

    (when (or current-value-time? history-buffer? simulation-history-buffer?)
      ;; Note the runtime change before it happens.
      (note-change-to-runtime-data-for-block variable))

    ;; Adjust the time of the most recent value.
    (when (and current-value-time? (managed-float-p current-value-time?))
      (with-temporary-gensym-float-creation
	  add-delta-to-history-buffer-of-variables-and-parameters
	(mutate-managed-float-value
	  current-value-time?
	  (+e (managed-float-value current-value-time?)
	      (managed-float-value managed-float-delta)))))

    ;; Adjust the history base time.
    (when history-buffer?
      (add-delta-to-history-buffer-base-time
	history-buffer? managed-float-delta))

    ;; Adjust the simulation history base time.
    (when simulation-history-buffer?
      ;; Usually the base-time of a simulated history buffer is 0.0.  This is an
      ;; exception.
      (add-delta-to-history-buffer-base-time
	simulation-history-buffer? managed-float-delta))))

;; Note that slots using gensym-times are not adjusted.  Adjusting the gensym
;; base time will correct these.  (This should be done separately.)  These slots
;; using gensym-times include expiration-time-of-current-value for variables,
;; and time-to-send-data-for-one-shot-request?, time-to-send-collected-data-
;; for-interval?, last-time-value-sent-to-inference-engine, and
;; interval-at-which-to-send-value-to-inference-engine in the simulator.

;; If there is code that assumes a 0.0 base time in the simualated-history, then
;; change this code to adjust each time in the simulated history buffer, instead
;; of the base time.  - cpm, 9/8/94



;;; The system-variable `time-used-to-adjust-histories?' is used to hold the
;;; time used in adjusting a history buffer.

(def-system-variable time-used-to-adjust-histories? HISTORIES nil)

;; This global variable is used because the function used in iteration over the
;; simulation-model variables is only passed one argument, the variable.  See
;; adjust-simulation-history-of-model-variables-if-necessary, which is a caller
;; of adjust-simulation-history-at-runtime-if-necessary.  - cpm, 11/3/94



;;; The function `adjust-simulation-history-at-runtime-if-necessary' verifies
;;; that the simulation history of the given variable is still valid, based on a
;;; cached model simulation-time.  Any future values or obsolete old values are
;;; removed from the history.  If a change is made, clients interested in the
;;; history buffer are notified of the change.

;;; IMPORTANT: Note that time-used-to-adjust-histories? should be bound to
;;; contain an evaluation-float (the time used in this function) before this
;;; function is called.  It should be then reclaimed by the caller, who bound
;;; the variable, as necessary.

(defun-void adjust-simulation-history-at-runtime-if-necessary (variable)
  (let* ((simulation-details?
	   (and (variable-p variable) (simulation-details variable)))
	 (buffer-of-stored-values?
	   (and simulation-details?
		(simulation-stored-history-specification? simulation-details?)
		(simulation-stored-histories? simulation-details?))))
    (when (and buffer-of-stored-values? time-used-to-adjust-histories?)
      (adjust-history-at-runtime-if-necessary
	variable buffer-of-stored-values? time-used-to-adjust-histories?))))



;;; The function `adjust-history-at-runtime-if-necessary' verifies that the
;;; history of the variable or parameter is still valid, based on the given time
;;; argument (a managed-float).  Any future or osbolete old values are removed
;;; from the history.  If a change is made, clients interested in the history
;;; buffer are notified of the change.

(defun-void adjust-history-at-runtime-if-necessary
    (variable-or-parameter buffer-of-stored-values managed-float-time)
  (let* ((runtime-specification
	   (car (runtime-specifications-for-individual-ring-buffers-in-cascade
		  buffer-of-stored-values)))
	 (ring-buffer
	   (car (cascaded-ring-buffers buffer-of-stored-values)))
	 (maximum-age-of-data-points?
	   (second runtime-specification)))
    (when (and buffer-of-stored-values (managed-float-p managed-float-time))
      (unless (verify-oldest-and-newest-history-values-with-given-time
		buffer-of-stored-values ring-buffer maximum-age-of-data-points?
		managed-float-time)
	;; Note the change before it happens.
	(note-change-to-runtime-data-for-block variable-or-parameter)
	(when maximum-age-of-data-points?
	  (remove-history-values-past-maximum-age
	    buffer-of-stored-values ring-buffer maximum-age-of-data-points?
	    managed-float-time))
	(remove-future-history-values
	  buffer-of-stored-values ring-buffer managed-float-time)
	(map-over-cascaded-ring-buffer-clients
	  'notify-client-of-change-to-cascaded-ring-buffer
	  buffer-of-stored-values)))))






;;;; Formats for Histories Saved in KBs (as Runtime Data)


;;; Currently, our plan is that 3.0 Kbs containing runtime data will have to be
;;; supported indefinitely into the future.  At first glance, it may seem
;;; bizarre to be warmbooting old KBs into a new version of G2, especially two
;;; versions apart in time, but consider that users sometimes do all development
;;; (i.e., saving and loading) in KBs containing runtime data, e.g., a
;;; Helpdesk-like application.  In such cases, it may in fact be necessary to
;;; load in a snapshot from several years ago.
;;;
;;; Here is the format for histories saved in 3.0 KBs:
;;;
;;;    <H or J> <buffer length> { <value> <collection time> }
;;;
;;; There are two distinct kinds of histories saved in 3.0.  One is a variable
;;; or parameter history.  This kind is prefixed with the letter H.  The other
;;; kind is the variable simulation history, which is prefixed with J.
;;;
;;; At pair of <value> and <collection time>, the time may be stored either as
;;; an absolute timestamp, i.e., a unix time, with the & prefix characters, or
;;; as a relative timestamp, i.e., a small integer offset being the number of
;;; seconds since the previous timestamp that was written, written with either
;;; the ( or ) prefix characters.
;;;
;;; There's one more special case: when a no-value (X) element appears, i.e., as
;;; a value, it is interpreted as no-simulation-value.  This is only valid for
;;; simulation histories (J case).  This was necessary prior to 4.0 because
;;; there did not exist a no-simulation-value (#) element type; that has just
;;; been added as of 4.0 in conjunction with the switch to the new format
;;; described below.
;;;
;;; Really the only reason that we needed to distinguish the variable/parameter
;;; (H) case from the simulation (J) case was to be able to know in which slot
;;; to look for the history keeping spec.
;;;
;;; It's true that in the case of simulation histories that the special no-value
;;; element (X) may appear, and must be interpreted in a special way, i.e., as
;;; no-simulation-value.  But that case can be disambiguated from the variable
;;; history case, since variable histories never contain no-value elements, at
;;; least at present.  (If they wanted to, then the two kinds of histories should
;;; be unified in any case.  Certainly a project for another day.)
;;;
;;; See also the summary description in KB-LOAD1, where all the formats for all
;;; of the runtime data elements are described.
;;;
;;;
;;; In 4.0, what gets saved in the runtime data of a frame saved for a snapshot
;;; are `history buffers and their locations'.  History buffers (aka, "cascaded
;;; ring buffers") now are saved.  They include not only the history (data) that
;;; was previously stored in 3.0 KBs, but also the specifications for the
;;; history buffer, i.e., the history keeping spec.  Here is the format for
;;; histories saved in 4.0 KBs:
;;;
;;;    B <location information> <history buffer information>
;;;      <length>
;;;      <array type> <value array contents>
;;;      <array type> <collection time array contents>
;;;
;;; where <location information> and <history buffer information> are both
;;; lists, and <value array contents> and <collection time array contents> are
;;; the contents of arrays of type <array type> (a symbol), containing runs of
;;; <length> elements, respectively, that make up the contents of the value and
;;; time array, respectively.
;;;
;;; The special-case handling of no-simulation-value can now go away because
;;; there is a new no-simulation-value (#) element type in 4.0.
;;;
;;; <History buffer information> is `history buffer information', which is the
;;; information needed to reconstruct a history buffer structure.  It is a list
;;; of the form
;;;
;;;    (<base time>
;;;      <maximum number of data points?>
;;;      <maximum age of data points?>
;;;      <millisecond interval between data points?>
;;;      <lowest value?>
;;;      <highest value?>
;;;      <value-vector-type>
;;;	 <time-vector-type>)
;;;
;;; <Base time> is an absolute G2 time, which is implemented as a managed float.
;;; This is the time from which the time elements of the history are offset.
;;;
;;; <Maximum number of data points?>, <maximum age of data points?>, and
;;; <millisecond interval between data points?> give the specification for the
;;; history buffer.  These are described above in the section "Cascaded Ring
;;; Buffers and Data Filtering".
;;;
;;; <lowest-value?> - is the lowest value of the history buffer, if any.
;;;
;;; <highest-value?> - is the highest value of the history buffer, if any.
;;;
;;; <Value-vector-type> and <time-vector-type> give the type of the value and
;;; time arrays, respectively.  They should be one of the symbols FLOAT-ARRAY or
;;; MANAGED-ARRAY.  Note that these determine the format in which which the
;;; times and values are written in the KB.  Specifically, in the FLOAT-ARRAY
;;; case, each element of the array is written as a float.  This information can
;;; be (and is) used to make the reading in more efficient, i.e., by avoiding
;;; the intermediate creation of managed floats, but instead transferring raw
;;; gensym floats into the gensym float array.

;;;
;;; <Location information> is `history location information', which designates
;;; the location in the containing frame for this history buffer.  It is a list
;;; of the form
;;;
;;;    (<location type> . <information>)
;;;
;;; Here, <location type> can be any symbol currently defined as a location type.
;;; At present, there are only two kinds of location types:
;;;
;;;    SLOT and SLOT-COMPONENT
;;;
;;; The format of <information> depends on the location type.  For the type
;;; SLOT, it's a list of the form
;;;
;;;    (<slot name> <defining class?>)
;;;
;;; For the type SLOT-COMPONENT, it's a list of the form
;;;
;;;    (<slot name> <defining class?>
;;;       <slot component name?>
;;;       <slot component indicator?>)
;;;
;;;
;;; When the internal buffers are recreated, their length is determined to be
;;; the max of <length> and <maximum number of data points?>, if any.





;;;; Writing and Reading Histories in 4.0 KBs



;;; `Make-history-buffer-information' takes a history buffer and returns a slot
;;; value list of information needed to eventually restore history buffer from a
;;; snapshot.  The resulting list is in the format descibed above for history
;;; buffer information.
;;;
;;; Note that the history buffer and its substructures are not reclaimed or side
;;; effected in any way.  All elements of the resulting list structure are
;;; shared with their corresponding elements in history-buffer.  I.e., the
;;; arrays and floating point times are not copied.

(defun make-history-buffer-information (history-buffer)
  (let* ((history-spec-list?
	   (runtime-specifications-for-individual-ring-buffers-in-cascade
	     history-buffer))
	 (history-spec? (if history-spec-list? (first history-spec-list?)))
	 (maximum-number-of-data-points? (first history-spec?))
	 (maximum-age-of-data-points? (second history-spec?))
	 (minimum-interval-between-data-points? (third history-spec?)))
    (slot-value-list
      (cascaded-ring-buffer-base-time? history-buffer)
      maximum-number-of-data-points?
      maximum-age-of-data-points?
      minimum-interval-between-data-points?
      (lowest-value-ever-in-history? history-buffer)
      (highest-value-ever-in-history? history-buffer))))



;;; `Make-history-buffer-information-into-history-buffer' takes a slot value
;;; list containing the information needed to create a history buffer, creates a
;;; corresponding history buffer, and returns it, after reclaiming the top-level
;;; slot conses of its argument.  The floats and arrays that are contained in
;;; history-buffer-information are assumed fit for use, and incorporated by this
;;; function into the result structure (or recycled).
;;;
;;; The argument is in the format descibed above for history buffer information.

(defun read-history-buffer-from-kb ()
  (let ((history-buffer-information (read-element-for-kb nil))
	(number-of-elements-to-read (read-element-for-kb nil)))
    (gensym-dstruct-bind
	((base-time
	   maximum-number-of-data-points?
	   maximum-age-of-data-points?
	   minimum-interval-between-data-points?
	   lowest-value?
	   highest-value?)
	 history-buffer-information)
      (reclaim-slot-value-list history-buffer-information)
      (let ((history-buffer (make-cascaded-ring-buffer)))
	(setf (runtime-specifications-for-individual-ring-buffers-in-cascade
		history-buffer)
	      (history-list
		(history-list
		  maximum-number-of-data-points?
		  maximum-age-of-data-points?
		  minimum-interval-between-data-points?)))
	
	(let* ((shell (make-history-ring-buffer))
	       (size
		 (if maximum-number-of-data-points?
		     (maxf maximum-number-of-data-points?
			   number-of-elements-to-read)
		     number-of-elements-to-read)))
	  (setf (history-value-vector shell)
		(read-history-buffer-vector-from-kb
		  size number-of-elements-to-read))
	  (setf (history-time-vector shell)
		(read-history-buffer-vector-from-kb
		  size number-of-elements-to-read))
	  
	  (unless (setf (ring-buffer-empty? shell)
			(=f number-of-elements-to-read 0))
	    (setf (newest-active-element-index shell) ; 0 (default) if empty
		  (-f number-of-elements-to-read 1)))
	  (setf (ring-buffer-size shell) size)

	  (setf (cascaded-ring-buffers history-buffer)
		(history-list shell)))

	(setf (cascaded-ring-buffer-base-time? history-buffer) base-time)
	(setf (lowest-value-ever-in-history? history-buffer) lowest-value?)
	(setf (highest-value-ever-in-history? history-buffer) highest-value?)
	
	history-buffer))))


;;; `Read-history-buffer-vector-from-kb' ...

(defun read-history-buffer-vector-from-kb (size number-of-elements-to-read)
  (let* ((vector-type (read-element-for-kb nil)))
    (case vector-type
      (managed-float-array
       ;; this is read/written as a managed float array
       (finish-reading-into-managed-float-array-for-kb
	 (allocate-managed-float-array size)
	 number-of-elements-to-read))
      (t
       ;; this is read/written as a managed array
       (finish-reading-into-managed-array-for-kb
	 (allocate-managed-array size)
	 number-of-elements-to-read)))))



(defun read-past-history-buffer-from-kb (print?)
  (read-past-element-for-kb print?)	; history buffer information
  (let ((ring-buffer-length (read-element-for-kb nil)))
    (when print?
      (format t "~%Value Vector (~d elements): ~%" ring-buffer-length))
    (read-past-element-for-kb print?)	; past type
    (loop repeat ring-buffer-length
	  do (read-past-element-for-kb print?))
    (when print?
      (format t "~%Time Vector (~d elements): ~%" ring-buffer-length))
    (read-past-element-for-kb print?)	; past type
    (loop repeat ring-buffer-length
	  do (read-past-element-for-kb print?))))
  
	



(defun make-history-location-information
    (slot-name defining-class? slot-component-name? slot-component-indicator?)
  (if slot-component-name?
      (slot-value-list
	'slot-component
	  slot-name defining-class?
	  slot-component-name? slot-component-indicator?)
      (slot-value-list
	'slot slot-name defining-class?)))

(defun get-type-of-history-location-information (history-location-information)
  (first history-location-information))



;;; The function `save-history-buffer' saves history-buffer, stored
;;; at the designated location, in the current KB being saved.  No
;;; useful value is returned.
;;;
;;;    B <location information> <history buffer information>
;;;      <length>
;;;      <array type> <value array contents>
;;;      <array type> <collection time array contents>
;;;
;;; This should not be called when the internal ring buffer is empty.

(defun save-history-buffer-for-kb
    (history-buffer slot-name &optional defining-class?
	    slot-component-name? slot-component-indicator?)
  (write-char-for-kb #\B)
  (let ((location-information
	  (make-history-location-information
	    slot-name defining-class?
	    slot-component-name? slot-component-indicator?)))
    (write-element-for-kb location-information)
    (reclaim-slot-value-list location-information))
  (let ((history-buffer-information
	  (make-history-buffer-information history-buffer)))
    (write-element-for-kb history-buffer-information)
    (reclaim-slot-value-list history-buffer-information))
  (let* ((history-ring-buffer
	   (first (cascaded-ring-buffers history-buffer)))
	 (length (ring-buffer-length history-ring-buffer))
	 (newest-index (newest-active-element-index history-ring-buffer))
	 (oldest-index (oldest-active-element-index history-ring-buffer)))
    (write-element-for-kb length)
    (write-vector-from-history-buffer-for-kb
      (history-value-vector history-ring-buffer)
      oldest-index newest-index
      (ring-buffer-size history-ring-buffer))
    (write-vector-from-history-buffer-for-kb
      (history-time-vector history-ring-buffer)
      oldest-index newest-index
      (ring-buffer-size history-ring-buffer))))


;;; `Write-vector-from-history-buffer-for-kb' ...
;;;
;;; Vector is the ring buffer's internal vector.  Vector-length is vector's
;;; actual length.  Oldest-index and newest-index mark the active elements.
;;; Note that newest-index is the index of the last element to be written.
;;;
;;; When newest-index is less than oldest-index, this represents the case
;;; where there the ring buffer has "wrapped around".
;;; 
;;; The number of elements written will be
;;;
;;;   if oldest-index <= newest-index:
;;;   
;;;     (oldest-index - newest-index) + 1;
;;;     
;;;   otherwise:
;;;
;;;     (vector-length - oldest-index) + (0 + newest-index) + 1
;;;
;;; Notice that if oldest-index = newest-index, the active length is one.
;;;
;;; This function is only to be called when there the active length is greater
;;; than zero.

(defun write-vector-from-history-buffer-for-kb
    (vector oldest-index newest-index vector-length)
  (let (start-1 end-1 (start-2? nil) (end-2? nil))
    (setq start-1 oldest-index)
    (cond
      ((<=f oldest-index newest-index)
       (setq end-1 (+f newest-index 1)))
      ;; The history ring buffer has wrapped around.
      (t
       (setq end-1 vector-length)
       (setq start-2? 0)
       (setq end-2? (+f newest-index 1))))
    (cond
      ((managed-float-array-p vector)
       (write-element-for-kb 'managed-float-array)
       (finish-writing-out-managed-float-array-for-kb vector start-1 end-1)
       (when start-2?
	 (finish-writing-out-managed-float-array-for-kb vector start-2? end-2?)))
      (t
       (write-element-for-kb 'managed-array)
       (finish-writing-out-managed-array-for-kb vector start-1 end-1)
       (when start-2?
	 (finish-writing-out-managed-array-for-kb vector start-2? end-2?))))))

;; There were (multiple!) bugs with this function as well as with
;; finish-writing-out-managed-float-array-for-kb.  The upshot is that snapshots
;; of history buffers written 4.0 Beta Phase I and Beta Phase II in house
;; through rev. 30.  The bug prevented this from working except in the (very
;; common) case where start-index was 0, and end-index was > 0.  This is now
;; all better.  (MHD 2/21/95)






;;; The generic method `restore history buffer' is called on a block
;;; with these args:
;;;
;;;    history-buffer - a history buffer as recently recontstructed
;;;      from the KB
;;;    history-location-information - an instance of this type of list
;;;      structure, which is defined above
;;;
;;; This method is called after warmbooting if the user has selected to
;;; start running with runtime data.  Its job is to restore the history
;;; buffer to the designated location in the block, reclaiming the old
;;; value if necessary.
;;;
;;; This method is responsible for incorporating (or reclaiming) the history
;;; buffer itself.  It is not to side-effect any of the list structure within
;;; history-location-information; that is owned by and recycled by the caller.

(def-generic-method restore-history-buffer
    (block history-buffer history-location-information))



;;; The `restore-history-buffer method for variable-or-parameter' and the
;;; `restore-history-buffer method for simulation-subtable' restores
;;; history-buffer to one the designated location in variable-or-parameter and
;;; simulation-subtable, respectively.
;;; 
;;; At present, the only histories saved for instances of these classes are for
;;; either the variable-or-parameter-stored-histories? slot
;;; (variable-or-parameter) or the simulation-stored-histories? slot
;;; (simulation-subtable).  Note that no checking is done to verify that these
;;; slots still exist and hold history buffers, since the need does not arise at
;;; present.  If the slot names were to change, work would be needed here, and
;;; possibly elsewhere.

(def-class-method restore-history-buffer 
  (variable-or-parameter history-buffer history-location-information)
  (restore-history-buffer-to-slot
    variable-or-parameter history-buffer history-location-information))

(def-class-method restore-history-buffer 
  (simulation-subtable history-buffer history-location-information)
  (restore-history-buffer-to-slot
    simulation-subtable history-buffer history-location-information))

(defun restore-history-buffer-to-slot
    (block history-buffer history-location-information)
  (let* ((slot-name (second history-location-information))
	 (defining-class? (third history-location-information))
	 (old-history-buffer?
	   (get-slot-value block slot-name defining-class?)))
    (when old-history-buffer?
      (reclaim-history-buffer old-history-buffer?))
    (set-slot-value block slot-name history-buffer defining-class?)))


;;; The function `read-history-buffer-and-location-for-block' reads in from the
;;; current KB two lists, the first of which contains history buffer information
;;; and the second of which contains location information.  Both of these are
;;; documented in the section above.  These are returned as the first and second
;;; value, respectively.
;;;
;;; The function `read-past-history-buffer-and-location-for-block' just reads
;;; past what the read-history-buffer-and-location-for-block would read.  If
;;; print? is true, it prints a description of what it's reading to the standard
;;; output stream.

(defun read-history-buffer-and-location-for-block ()
  (let* ((location (read-element-for-kb nil))
	 (buffer (read-history-buffer-from-kb)))
    (values buffer location)))

;; Consider revising the order of buffer and location in the name and values.


(defun read-past-history-buffer-and-location-for-block (print?)
  (when print?
    (format
      t "~%; start history reading history buffer and location:~%"))
  (read-past-element-for-kb print?)	; location information
  (read-past-history-buffer-from-kb print?) ;
  (when print?
    (format
      t "~%; end reading history buffer and location:~%")))





;;;; Writing Histories for KB

;;; This section is an extension of the write-...-for-kb functions in KB-SAVE1.

;; `write-history-buffer-for-kb' is part of save-kb abd would normally be found
;; in KB-SAVE1. It is here because it uses macros specific to the
;; history-functions. It is called within a saving-context to write either a
;; inference or simulation history buffer according to the specification in
;; KB-LOAD1.

;; This function is obsolete in version 4.0.  It wrote history warmboot
;; information in the version 3.0 format.  Note that the corresponding reader
;; (read-history-buffer-for-block) is still needed to read 3.0 warmboot
;; snapshot KB's into 4.0.  - cpm, mhd 6/16/94

;(defun write-history-buffer-for-kb
;    (value-history-cascaded-ring-buffer initial-character)
;  (with-value-history-ring-buffer-or-cascade-1
;      (value-history-cascaded-ring-buffer)
;    (write-char-for-kb initial-character)
;    (write-integer-for-kb
;      (ring-buffer-length value-history-ring-buffer-or-cascade))    
;    (iterate-over-history
;      (if (no-simulation-value-p history-value)
;          (write-char-for-kb #\X)
;          (write-element-for-kb history-value))
;      (write-timestamp-for-kb
;        (+f history-collection-time gensym-time-at-start)))))


(defun write-parameter-data-for-kb (parameter)
  (write-left-bracket-if-necessary)
  (with-temporary-gensym-float-creation write-parameter-data-for-kb
    (let* ((collection-time
	     (time-of-most-recent-value parameter))
	   (simulation-runtime-information?
	     (simulation-runtime-information? parameter))
	   (simulation-value?
	     (if simulation-runtime-information?
		 (simulation-value simulation-runtime-information?)))
	   (history-buffer?
	     (variable-or-parameter-stored-histories? parameter)))
      (write-char-for-kb #\P)
      (write-element-for-kb
	(current-value-of-variable-or-parameter parameter))
      (if (or (not (fixnump collection-time))
	      (/=f collection-time *some-time-ago*))
	  (write-element-for-kb collection-time)
	  (write-char-for-kb #\G))
      (when (and history-buffer?
		 (not (cascaded-ring-buffer-empty? history-buffer?)))
	(save-history-buffer-for-kb
	  history-buffer? 'variable-or-parameter-stored-histories?))
      (when simulation-value?
	(write-char-for-kb #\S)
	(write-element-for-kb simulation-value?)))))



(defun write-variable-data-for-kb (variable)
  (write-left-bracket-if-necessary)
  (with-temporary-gensym-float-creation write-variable-data-for-kb
    (let* ((collection-time
	     (time-of-most-recent-value variable))
	   (expiration-time
	     (expiration-time-of-current-value variable))
	   (simulation-runtime-information?
	     (simulation-runtime-information? variable))
	   (simulation-value?
	     (if simulation-runtime-information?
		 (simulation-value simulation-runtime-information?)))
	   (history-buffer? (variable-or-parameter-stored-histories? variable)))
      
      (when (or (not (fixnump collection-time))
		(/=f collection-time *some-time-ago*))
	(write-char-for-kb #\V)
	(write-element-for-kb
	  (current-value-of-variable-or-parameter variable))
	(write-element-for-kb collection-time)
	(cond
	  ((eq expiration-time 'never) (write-char-for-kb #\X))
	  ((=f expiration-time *some-time-ago*)
	   (write-char-for-kb #\G))
	  (t
	   ;; Still in the old gensym-time format.
	   (write-timestamp-for-kb expiration-time))))
      (when (and history-buffer?
		 (not (cascaded-ring-buffer-empty? history-buffer?)))
	(save-history-buffer-for-kb
	  history-buffer? 'variable-or-parameter-stored-histories?))
      (when simulation-value?
	(write-char-for-kb #\S)
	(write-element-for-kb simulation-value?)))))


(defun write-simulation-subtable-data-for-kb (simulation-subtable)
  (let ((history-buffer? (simulation-stored-histories? simulation-subtable)))
      (when (and history-buffer?
                 (not (cascaded-ring-buffer-empty? history-buffer?)))
        (write-left-bracket-if-necessary)
        (save-history-buffer-for-kb
          history-buffer? 'simulation-stored-histories?))))






;;;; Reading Histories from KB

;;; This re-write of read-history-buffer for block clears up one major and one
;;; minor bug.  The major bug was a memory leak associated with receiving floats
;;; floats created by read-element-for-kb not reclaiming them.  The minor bug,
;;; noted but not fixed by ML, was that the with-temp... had too long a
;;; context under some history keeping specs.

(defun read-history-buffer-for-block (block dispatch-char
				       &optional history-keeping-spec?)
  (loop with number-of-points = (read-element-for-kb nil)
	with history-keeping-spec 
	    = (or history-keeping-spec?
		  (case dispatch-char
		    (#\H (variable-or-parameter-history-specification? block))
		    (#\J (simulation-stored-history-specification? block))))
	with ring-buffer
	= (make-or-reformat-cascaded-ring-buffer 
	    nil
	    (second history-keeping-spec)
	    (third history-keeping-spec)
	    (fourth history-keeping-spec))
	with points-read = 0
	do (with-temporary-gensym-float-creation read-history-buffer-for-block
	     (loop
	       do (let ((history-value (read-element-for-kb nil)))
		    (store-history-element-in-cascaded-ring-buffer
		      ring-buffer
		      (extract-number-or-value history-value)
		      (read-element-for-kb nil))
		    (reclaim-if-evaluation-value history-value))
		  (incff points-read)
	       until (or (>=f points-read number-of-points)
			 (=f (modf points-read 500) 0)))) ; stops temp-float-context overflow
	while (<f points-read number-of-points)
	finally
	  (return ring-buffer)))

;(defun read-history-buffer-for-block (block dispatch-char)
;  (with-temporary-gensym-float-creation read-history-buffer-for-block
;    (loop with number-of-points = (read-element-for-kb nil)
;          ;; The block is assumed to be a variable-or-parameter or a
;          ;; simulation-subtable.  There should be a history-keeping-spec.  The
;          ;; second element of it may be NIL, in which case, the third element,
;          ;; age, should be non-nil.  The buffer size will be the number of
;          ;; points specified by the variable-or-parameter if that exists, or
;          ;; the number of data points present.
;          with history-keeping-spec
;            = (case dispatch-char
;                (#\H (variable-or-parameter-history-specification? block))
;                (#\J (simulation-stored-history-specification? block)))
;          with ring-buffer
;            = (make-or-reformat-cascaded-ring-buffer 
;                nil
;                (second history-keeping-spec)
;                (third history-keeping-spec))
;          repeat number-of-points
;          do (store-history-element-in-cascaded-ring-buffer
;               ring-buffer
;               (extract-number-or-value (read-element-for-kb nil))
;               (read-element-for-kb nil))
;          finally
;            (return ring-buffer))))

;; Note reversal of reclaiming from above. Does the with-temorary- have too long
;; an extent? Also, doesn't the outer loop need to take into account the inner
;; loop? ML 9/27/91

(defun-void read-past-history-buffer-for-block (print?)
  (with-temporary-gensym-float-creation read-history-buffer-for-block
    (loop with number-of-points = (read-element-for-kb nil)
	  repeat number-of-points
	  initially
	    (when print?
	      (format t "~%; START HISTORY BUFFER -- ~D POINTS:~%" number-of-points))	    
	  do (read-past-element-for-kb print?) ; value
	     (read-past-element-for-kb print?) ; time
	  finally
	    (when print?
	      (format t "~%; END HISTORY BUFFER -- ~d POINTS:~%" number-of-points)))))



(declare-forward-reference make-variable-simulation-runtime-structure-with-model function)
; (declare-forward-reference unsquirrel-data-for-trend-chart function)

(defun unsquirrel-data-for-block (block)
  (let ((squirreled-data (squirreled-data block)))
    (when squirreled-data
      (loop for element in squirreled-data
	    for (char first second third) = element do
	(character-case char
	  (#\V
	   (reclaim-managed-number-or-value
	     (current-value-of-variable-or-parameter block))
	   (setf (current-value-of-variable-or-parameter block) first)
	   (reclaim-managed-number (time-of-most-recent-value block))
	   (setf (time-of-most-recent-value block) second)
	   ;; Expiration is still in old gensym-time format.
	   (setf (expiration-time-of-current-value block) third)
	   (update-representations-of-variable-or-parameter-value block))
	  (#\P
	   (reclaim-managed-number-or-value
	     (current-value-of-variable-or-parameter block))
	   (setf (current-value-of-variable-or-parameter block) first)
	   (reclaim-managed-number (time-of-most-recent-value block))
	   (setf (time-of-most-recent-value block) second)
	   (update-representations-of-variable-or-parameter-value block))
	  (#\S
	   (let ((simulation-runtime-information?
		   (simulation-runtime-information? block)))
	     (when (null simulation-runtime-information?)
	       (make-variable-simulation-runtime-structure-with-model block)
	       (setq simulation-runtime-information?
		     (simulation-runtime-information? block)))
	     ;; Since we don't know how to store this, we need to call
	     ;; store-managed-number-or-value (which will do reclaims on the old
	     ;; value if necessary) to do the right thing.  Previously, we were
	     ;; winding up with EQ values in the two slots, which screwed us at
	     ;; reclamation time. -dkuznick, 11/12/98 
	     (store-managed-number-or-value
	       (simulation-value simulation-runtime-information?)
	       first)
	     (store-managed-number-or-value
	       (new-simulation-value simulation-runtime-information?)
	       first)
	     ;; WHAT ABOUT TABLES!  LEAVE AS A (PROBABLE) BUG FOR NOW!
	     ;; (MHD/GHW 12/6/94)
	     ))
;	  (#\G
;	     (when (frame-of-class-p block 'trend-chart)
;	       (unsquirrel-data-for-trend-chart block first))) ; JED 12/28/93
	  (#\H
	   (let ((buffer? (variable-or-parameter-stored-histories? block)))
	     (when buffer? (reclaim-history-buffer buffer?)))
	   (setf (variable-or-parameter-stored-histories? block)
		 (add-delta-to-all-history-buffer-times
		   first (-f (clock-get gensym-time-at-start))))
 	   ;; Even though this is the 3.0 history format, reading into 4.0
 	   ;; requires the base-time to be set.  In 3.0, there was an implicit
 	   ;; base-time of gensym-time at start.
 	   (setf (cascaded-ring-buffer-base-time? first)
 		 (allocate-managed-float
 		   (convert-gensym-time-to-unix-time (clock-get gensym-time-at-start)))))
	  (#\J
	   (let ((buffer? (simulation-stored-histories? block)))
	     (when buffer? (reclaim-history-buffer buffer?))
	     (setf (simulation-stored-histories? block)
		   (add-delta-to-all-history-buffer-times
		     first (-f (clock-get gensym-time-at-start))))
	     ;; In version 3.0, warmboot snapshot wrote out the simulation
	     ;; history times as a sum of the history time plus the
	     ;; gensym-time-at-start.  But, the base-time should be restored
	     ;; 0.0, which is now the used for all simulation-histories.  (The
	     ;; simulation history times are in relation to the simulation
	     ;; clock, which is 0 when started.)
 	   (setf (cascaded-ring-buffer-base-time? first)
 		 (allocate-managed-float 0.0d0))))
	  (#\B
	     (let* ((history-buffer first)
		    (history-location-information second))
	       (funcall-method-if-any	; "-if-any" maybe not necessary
		 'restore-history-buffer
		 block history-buffer history-location-information)
	       (reclaim-slot-value-list history-location-information)))

	  (#\R
	     ;; When saving a snapshot kb, we save the permanent relation-
	     ;; instances so that they will persist after a load without
	     ;; the warmboot option.  If the warmboot option is used, we
	     ;; replace that value with the squirrelled data which includes
	     ;; both permanent and transient relation-instances.
	     (reclaim-relation-instances (relation-instances block))
	     (setf (relation-instances block) (second element))
	     ;; GENSYMCID-1699: G2 2015 Testing: Loading snapshot coredumps G2
	     #+relation-instances-v2
	     (upgrade-relation-instance block))
	  (#\A
	     ;; HQ-2173266
	     ;; Read-array-data (called from read-runtime-data-for-block)
	     ;; now reclaims the list of values for permanent arrays before
	     ;; it allocates a managed g2-array and sets the
	     ;; squirreled-data AND managed- g2-array slots with that same
	     ;; array.  The post-loading function for arrays,
	     ;; convert-saved-array-values-to-g2- array-structure, leaves
	     ;; it untouched in the managed-g2-array slot because the
	     ;; value is not a cons.  (ghw 10/5/95)
	     (atomic-exchange (managed-g2-array block) first))
	  (#\L
	     ;; HQ-2173266
	     ;; For permanent lists, the post-loading-function convert-saved-list-
	     ;; values-to- g2-list-structure reclaims the saved list-structure
	     ;; slot value when warmbooting.  The activation code has allocated
	     ;; an empty-list-structure before this code is called.
	     (unsquirrel-list-data block first))
	  (#\O
	     ;; GENSYMCID-1186: Warmboot hash-table content is lost and G2 aborts
	     ;; during warmboot.
	     (unsquirrel-hash-table-data block first)))
	(reclaim-slot-value-list element))
      
      (reclaim-slot-value-list squirreled-data)
      (setf (squirreled-data block) nil))))








;;;; Test and Debugging Functions


#+development
(defun set-all-history-specs (number-of-datapoints)
  (loop for var-or-par being each class-instance of 'variable-or-parameter
	do (when (variable-or-parameter-history-specification? var-or-par)
	     (change-slot-value 
	       var-or-par 'variable-or-parameter-history-specification?
	       (slot-value-list 'history number-of-datapoints)))))



#+development
(defun print-history-for-variable
    (variable &optional print-universal-times-as-well? value-requested-by-simulator?)
  (let* ((value-history-cascaded-ring-buffer
	   (if (and value-requested-by-simulator?
		    (frame-of-class-p variable 'variable))     ; not parameter
	       (let* ((simulation-subtable?
			(simulation-details variable))
		      (simulation-stored-histories?
			(if simulation-subtable?
			    (simulation-stored-histories? simulation-subtable?))))
		 (if (or (not simulation-subtable?)
			 (not (simulation-stored-history-specification? simulation-subtable?))
			 (not simulation-stored-histories?))
		     (format t "~%No simulated history data is available for this variable.")
		     simulation-stored-histories?))
	       (if (or (not (variable-or-parameter-history-specification? variable))
		       (not (variable-or-parameter-stored-histories? variable)))
		   (format t "~%No history data is available for this variable.")
		   (variable-or-parameter-stored-histories? variable))))
	 (value-history-ring-buffer-or-cascade
	   (when value-history-cascaded-ring-buffer
	     (car (cascaded-ring-buffers value-history-cascaded-ring-buffer))))
	 (base-time?
	   (and value-history-cascaded-ring-buffer
		(cascaded-ring-buffer-base-time?
		  value-history-cascaded-ring-buffer)))
	 (base-time-value
	   (if base-time?
	       (extract-number base-time?)
	       (coerce-fixnum-to-gensym-float
		 (truncate (managed-float-value (clock-get current-g2-time)))))))
    (when value-history-ring-buffer-or-cascade
      (print-contents-of-history-buffer 
	value-history-ring-buffer-or-cascade print-universal-times-as-well?
	base-time-value))))

#+development
(defun print-contents-of-history-buffer
       (history-ring-buffer &optional (print-universal-times-as-well? nil)
			    (base-time-for-history 0))
  (format t "~%~%History ring buffer information:")
  (if (ring-buffer-empty? history-ring-buffer)
      (format t "~%  ring buffer is empty (no history)")
      (format t "~%  length (number of points) = ~d" 
	      (ring-buffer-length history-ring-buffer)))
  (format t "~%  size (of vectors) = ~d" 
	  (ring-buffer-size history-ring-buffer))
  (format t "~%  newest active element index = ~d" 
	  (newest-active-element-index history-ring-buffer))
  (format t "~%  oldest active element index = ~d" 
	  (oldest-active-element-index history-ring-buffer))
  (when (not (ring-buffer-empty? history-ring-buffer))
    (if (managed-array-p (history-value-vector history-ring-buffer))
	(format t "~%managed array")
	(format t "~%managed float array"))
    (format t " used for history values")
    (format t "~%  contents =")
    (format t "~%value  time")
    (terpri)
    (loop with history-element-index
	    = (oldest-active-element-index
		history-ring-buffer)
	  do
      (multiple-value-bind
	(history-value history-time)
	  (get-history-ring-buffer-element
	    history-ring-buffer
	    history-element-index)
	(format t "~s, ~s" history-value history-time)
	(if print-universal-times-as-well?
	    (let* ((history-unix-time
		     (coerce-to-gensym-float
		       (+ history-time base-time-for-history)))
		   (second-fraction-float
		     (-e history-unix-time (ffloore-first history-unix-time)))
		   (subsecond-time?
		     (if (/=e second-fraction-float 0.0)
			 second-fraction-float))
		   (time-stamp-string nil))
	    (multiple-value-bind (seconds minutes hours)
		(gensym-decode-unix-time history-unix-time)
	      (if subsecond-time?
		  (setq seconds
			(+e (coerce-fixnum-to-gensym-float seconds)
			    subsecond-time?)))
	      (setq time-stamp-string
		    (twith-output-to-text-string
		      (print-decoded-time-of-day seconds minutes hours)))
	      ; (format t ", ~s:~s:~s~%" hours minutes seconds)
	      (format t ", ~a~%" time-stamp-string)
	      (reclaim-text-string time-stamp-string)))
	    (format t " (i=~s)~%" history-element-index)))

	  until (= history-element-index
		   (newest-active-element-index
		     history-ring-buffer))
	  do
      (setq history-element-index
	    (increment-active-element-index
	      history-element-index
	      history-ring-buffer)))))

;; Consider defining this automatically in define-ring-buffer!



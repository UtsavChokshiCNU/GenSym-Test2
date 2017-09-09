;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")
     
;;;; Module CHECKMEMORY

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin



;;; This module is included in the system only in development.

;;; Check memory creates a snap shot of the size of the various
;;; memory pools, and then monitors those for increases in memory.
;;; When enabled and intialized it dribbles a report stream to
;;; the background stream.

;;; The tools in the module are invoked via the these routines:
;;;   enable-check-memory
;;;   disable-check-memory
;;;   check-memory &optional label
;;; These are documented below, but `Enable-check-memory' and
;;; `Disable-check-memory' toggle the mechinism on or off.  You may
;;; sprinkle lots and lots of calls on check-memory in your code,
;;; guarding them with #+development.



;;; The following declare-forward-reference is to mask the fact that TW doesn't
;;; include CLOCKS and gensym-time, which are referenced in the reporting
;;; functions of this file.  -jra 3/4/94

(declare-forward-reference gensym-time variable)






;;;; Developer's Parameters for Check-Memory





;;; `Check-memory-enabled-p' is internal to check-memory.  It flags if the
;;; mechinism is on or off.  It should be toggled via the functions
;;; {en,dis}able-check-memory.

(defvar check-memory-enabled-p nil)



;;; `Enable-check-memory' and `Disable-check-memory' do just that.

(defun enable-check-memory ()
  (setq cons-pool-conses-to-make-at-a-time 1)
  (setq check-memory-enabled-p t))

;; Aren't there other variables this ought to clamp down?
;; For example shouldn't it clear all the pools?

(defun disable-check-memory ()
  (setq cons-pool-conses-to-make-at-a-time 50)
  (setq check-memory-enabled-p nil))

;; Where did it get the number 50?







;;; The variable `format-output-enabled-for-check-memory-p', if it is non-nil
;;; tells the check-memory function to output its messages using the format
;;; function, otherwise check-memory will use the warning-message function.
;;; However, check-memory will always output using format if it is not running
;;; within a G2 process.

(defvar format-output-enabled-for-check-memory-p t)



;;; The variable `break-enabled-for-check-memory-p' allows check-memory to call
;;; the Lisp function break if a significant memory increment was detected.

(defvar break-enabled-for-check-memory-p nil)




;;; The variable `check-managed-pools-in-check-memory-p' enables the checking
;;; of managed pools by check-memory if it is non-nil, and disables it if it is
;;; nil.

(defvar check-managed-pools-in-check-memory-p t)



;;; The variable `significant-increase-for-memory-usage' specifies a threshold
;;; (an integer) for memory usage increases beyond which the check-memory
;;; function will give warning messages.

(defparameter significant-increase-for-memory-usage 0)



;;; The variable `significant-increase-for-pool-size' specifies a threshold (an
;;; integer) for managed pool size increases beyond which the check-memory
;;; function will give warning messages.

(defparameter significant-increase-for-pool-size 0)



;;; The variable `all-pools-to-be-checked-by-check-memory' is either a list of
;;; names of managed pools to be checked, or t.  If it is t, then all pools
;;; will be checked.  This variable could be set to
;;; names-of-interesting-system-object-pools, for example.

(defvar all-pools-to-be-checked-by-check-memory t)










;;;; Other Internal State for Check-Memory




;;; The variable `number-of-pools-to-be-checked-by-check-memory' records the
;;; number of managed pools which will be monitored by check-memory.

(defvar number-of-pools-to-be-checked-by-check-memory 0)



;;; The variable `last-memory-usage-total-of-check-memory' holds the value
;;; returned by g2-memory-usage (in PRIMITIVES).  Check-memory calls
;;; g2-memory-usage and sets the variable every time it is called.

(defvar last-memory-usage-total-of-check-memory 0)



;;; The variable `last-pool-totals-of-check-memory' is either nil, or an array
;;; of the length of object-pool-meters.

(defvar last-pool-totals-of-check-memory)



;;; The variable `pool-meters-of-check' is either nil, or an array of the
;;; length of object-pool-meters, with elements of pool-meters.

(defvar pool-meters-of-check-memory)



;;; The function `create-arrays-for-check-memory' is a load time
;;; function used to create the data structures used by check memory
;;; to manage it model of the memory in used.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun create-arrays-for-check-memory ()
    (when (and (boundp 'object-pool-meters)
	       (or (not (boundp 'last-pool-totals-of-check-memory))
		   (not (arrayp last-pool-totals-of-check-memory))
		   (/= (length last-pool-totals-of-check-memory)
		       (length object-pool-meters))))
      (let* ((length (length object-pool-meters)))
	(setq last-pool-totals-of-check-memory
	      (make-array length))
	(setq pool-meters-of-check-memory
	      (make-array length))))))


(create-arrays-for-check-memory)



;;; The variable `last-label-of-check-memory' holds the label given to the
;;; function check-memory the last time it was called.

(defvar last-label-of-check-memory nil)







;;;; Functions for Check-Memory


;;; `In-g2-process-p' is an internal function of check memory.

(defmacro in-g2-process-p ()
  `(and (boundp 'current-system-name)
	current-system-name))

;; Current-system-name was recently changed to be bound to nil at top-level.
;; The additional test is therefore now necessary.  The total test would be
;; compatible with the old way (unbound at top level), but contain one redundant
;; subtest.  Easiest and safest is to leave it this way. (MHD 4/21/95)



;;; `Initialize-check-memory' is an internal function of check memory.
;;; It is called automaticly the first time a check memory is done
;;; once it is enabled.  It sets up the data structures and reports
;;; the current confirugation of check memory.

(defun initialize-check-memory ()
  (when check-memory-enabled-p
    (when format-output-enabled-for-check-memory-p
      (when (boundp 'gensym-time)
	(format t "                             gensym-time = ~s~%"
		gensym-time))
      (format t "                  check-memory-enabled-p = ~s~%"
	      check-memory-enabled-p)
      (format t "format-output-enabled-for-check-memory-p = ~s~%"
	      format-output-enabled-for-check-memory-p)
      (format t "        break-enabled-for-check-memory-p = ~s~%"
	      break-enabled-for-check-memory-p)
      (format t "   check-managed-pools-in-check-memory-p = ~s~%"
	      check-managed-pools-in-check-memory-p)
      (format t "   significant-increase-for-memory-usage = ~s~%"
	      significant-increase-for-memory-usage)
      (format t "      significant-increase-for-pool-size = ~s~%"
	      significant-increase-for-pool-size)
      (format t " all-pools-to-be-checked-by-check-memory = ~s~%"
	      all-pools-to-be-checked-by-check-memory))
    (setq last-memory-usage-total-of-check-memory (g2-memory-usage))
    (when (in-g2-process-p)
      (create-arrays-for-check-memory)
      (when (boundp 'object-pool-meters)
	(let* ((count 0))
	  (if (eq all-pools-to-be-checked-by-check-memory t)
	      ;; Then
	      (dolist (pool-meter object-pool-meters)
		(setf (aref last-pool-totals-of-check-memory count) 
		      (pool-entry-object-count pool-meter))
		(setf (aref pool-meters-of-check-memory count) 
		      pool-meter)
		(incf count))
	      ;; Else
	      (dolist (pool-meter object-pool-meters)
		(when (member (pool-entry-name pool-meter)
			      all-pools-to-be-checked-by-check-memory)      
		  (setf (aref last-pool-totals-of-check-memory count) 
			(pool-entry-object-count pool-meter))
		  (setf (aref pool-meters-of-check-memory count) 
			pool-meter)
		  (incf count))))
	  (setq number-of-pools-to-be-checked-by-check-memory count))))))



;;; `Check-memory' does nothing if check-memory is not enabled.  See
;;; enable-check-memory and initialize-check-memory!  Otherwise it compares the
;;; current memory usage with the last recorded memory usage and informs you if
;;; the increase in usage is greater than the specified significant increase.

;;; There are numerous check-memory calls in the G2 sources.  They can be
;;; very noisy to listen too.  Once check memory has been initialized it
;;; maybe enabled and disabled so you can watch memory only in the
;;; extents you are actually concerned about.

;;; Recall that this module is loaded only in development.

(defun check-memory (&optional label)
  (when check-memory-enabled-p
    (let* ((new-memory-usage-total-of-check-memory (g2-memory-usage)))
      (when (in-g2-process-p)
	;; Initialize if necessary.
	(when (or (not (boundp 'last-pool-totals-of-check-memory))
		   (null last-pool-totals-of-check-memory))
	   (initialize-check-memory))
	;; Do the report.
	 (when (check-memory-for-pools 
		 new-memory-usage-total-of-check-memory 
		 label)
	   ;; Update our self checking if necessary.
	   (setq last-memory-usage-total-of-check-memory (g2-memory-usage))))
      (setq last-label-of-check-memory label))))


;; Here's an example of using check-memory to test an isolated function:
;; (defun test ()
;;   (loop doing
;;      (call-function-to-be-tested-here)
;;      (check-memory 'foo)))
;; (compile 'test)                 ;Uncompiled functions produce cons leaks.
;; This is a useful method of isolating leaks.







;;; The function `check-memory-for-memory-usage' ... Returns t if it suspects
;;; that it has consed some memory itself while printing messages, nil if not.

(defun self-check-of-check-memory
       (new-memory-usage-total-of-check-memory)
  ;; When there is a significant increase, give appropriate warnings
  (let* ((memory-usage-increase
	   (- new-memory-usage-total-of-check-memory
	      last-memory-usage-total-of-check-memory)))
    (unless (<= 0
	        memory-usage-increase
	        significant-increase-for-memory-usage)
      (report-check-memory
	'all-memory-regions
	(- new-memory-usage-total-of-check-memory
	   last-memory-usage-total-of-check-memory)
	new-memory-usage-total-of-check-memory
	'start-of-check-memory-reporting
	'end-of-check-memory-reporting)
      t)					       ;return t if memory increase
						       ;  else return nil
    ))



;;; The function `check-memory-for-pools' is an internal function of
;;; check-memory.  It returns t if it suspects that it has consed some memory
;;; itself while printing messages, nil if not.

(defun check-memory-for-pools 
       (new-memory-usage-total-of-check-memory label)
  (let* (last-pool-total
	 new-pool-total
	 pool-meter
	 (at-least-one-pool-changed-p nil)
	 (memory-usage-changed-p nil))
    ;; Report for each pool that changs.
    (when (arrayp last-pool-totals-of-check-memory)
      (dotimes (count number-of-pools-to-be-checked-by-check-memory nil)
	(setq pool-meter (aref pool-meters-of-check-memory count))
	(setq last-pool-total (aref last-pool-totals-of-check-memory count))
	(setq new-pool-total (pool-entry-object-count pool-meter))
	(unless (<= 0
		    (- new-pool-total last-pool-total)
		    significant-increase-for-pool-size)
	  (setq at-least-one-pool-changed-p t)
	  ;; at-least-one-pool-changed implies that memory-usage-changed
	  (report-check-memory
	    (pool-entry-name pool-meter)
	    (- new-pool-total last-pool-total)
	    new-pool-total
	    last-label-of-check-memory
	    label)
	  (setf (aref last-pool-totals-of-check-memory count) new-pool-total))))
    ;; Check that we didn't allocate memory ourselves
    (when (self-check-of-check-memory new-memory-usage-total-of-check-memory)
      (setq memory-usage-changed-p t))
    ;; Return a flag is something changed.
    (or memory-usage-changed-p
	at-least-one-pool-changed-p)))


;;; `report-check-memory' is an internal function of the check memory
;;; mechinism.  All report generation is funnelled thru it.  You may play with
;;; this function to change the reporting, for example to redirect and filter
;;; it.

(defun report-check-memory
    (pool-id this-pool-delta this-pool-total previous-label latest-label)
  (let ((gensym-time-or-zero
	 (if (boundp 'gensym-time) gensym-time 0)))
    (cond
      ((or format-output-enabled-for-check-memory-p
	   (not (in-g2-process-p)))
       ;; format output
       (fresh-line)
       (format 
	 t "~6D CM: ~6d to ~6d ~20S betwn ~20s & ~20s.~%"
	 gensym-time-or-zero   
	 this-pool-delta this-pool-total
	 pool-id
	 previous-label latest-label))
      (t
       ;; (If anyone cares...), this was:
       ;;   (warning-message 1 ...)
       ;; but that forward referenced a macro.  (MHD 2/28/94)
       (notify-user-if-possible
	 "~6D CM: ~20S ~6d to ~6d betwn ~20s & ~20s.~%"
	 gensym-time-or-zero   
	 pool-id
	 this-pool-delta this-pool-total
	 previous-label latest-label))))
  (when break-enabled-for-check-memory-p
    (break-check-memory latest-label)))



;;; The function `break-check-memory' is an internal function of check-memory.
;;; it is invoked, and then does a cerror when break-enabled-for-check-memory-p
;;; has been set to T.

(defun break-check-memory (label)
  (cerror 
    "Continue with program execution."
    "A memory increase was detected by check-memory at the check point ~s."
    label))



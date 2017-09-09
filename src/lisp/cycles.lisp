;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CYCLES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard	     






;;;; Forward References

(declare-forward-reference update-meter-values function)	; in G2-METERS



(declare-forward-reference recursive-attribute-nesting-has-occurred? variable)  ;GRAMMAR6A

(declare-forward-reference repeat-random-function-on-reset?-function function)  ; GRAMMAR2

(declare-forward-reference miscellaneous-parameters variable)   ;GRAMMAR2

(declare-forward-reference update-g2-run-state function) ;GRAMMAR7


(declare-forward-reference cancel-all-field-edits-in-session function)   ;CONTROLS
(declare-forward-reference run-state-change-hook function)
(declare-forward-reference kill-all-instances-of-all-g2gl-processes function) ;G2-BPEL
(declare-forward-reference notify-http-servers-of-g2-reset function) ;WEB-SERVICES

(declare-forward-reference flush-current-coverage-information function) ;COVERAGE


;;;; Clock Tick Inhibiting




;;; The function `resynchronize-gensym-time-and-actual-time' will set up a
;;; clocks environment such that gensym-time track real time, and marks the
;;; beginning of the first clock tick for the schedule cycle.  This function
;;; should be called as the last thing that happens in the process of starting
;;; G2.  This is done so that the G2 clock will not immediately take a multiple
;;; second clock tick after the initialization of large KBs.
;;;   (moved to cycles.lisp from clocks.lisp -ncc, 2 May 1996)

(defun-void resynchronize-gensym-time-and-actual-time ()
  (with-clock-sync
  (with-temporary-gensym-float-creation resynchronize-gensym-time
    (let* ((current-fixnum-time (get-fixnum-time t))
	   (current-unix-time (gensym-get-unix-time))
	   (floored-unix-time (ffloore-first current-unix-time))
	   (old-gensym-time gensym-time)
	   (scheduler-mode (determine-scheduler-mode-for-current-system)))
      (declare (type gensym-float current-unix-time floored-unix-time))
      (cond
	(warmbooting?
	 (when (and (eq scheduler-mode 'real-time)
		    (not warmbooting-with-catch-up?))
	   (atomic-exchange gensym-time
		 (convert-unix-time-to-gensym-time floored-unix-time))
	   (mutate-managed-float-value current-g2-time floored-unix-time)
	   (mutate-managed-float-value most-recent-g2-time floored-unix-time)
	   (mutate-managed-float-value real-time-of-last-g2-tick
				       current-unix-time)
	   (atomic-exchange fixnum-time-of-last-g2-tick current-fixnum-time)))
	(t
	 (atomic-exchange gensym-time-at-start gensym-time)
	 (mutate-managed-float-value
	   gensym-base-time-as-managed-float
	   (-e (unix-time-to-universal-time floored-unix-time)
	       (coerce-fixnum-to-gensym-float gensym-time)))
	 (mutate-managed-float-value current-g2-time floored-unix-time)
	 (mutate-managed-float-value most-recent-g2-time floored-unix-time)
	 (mutate-managed-float-value real-time-of-last-g2-tick
				     current-unix-time)
	 (atomic-exchange fixnum-time-of-last-g2-tick current-fixnum-time)
	 (mutate-managed-float-value g2-time-at-start floored-unix-time)))

      ;; Update the g2 time to tick predicate.
      (let ((millisecond-minimum-scheduling-interval?
	      (determine-minimum-scheduling-interval-for-current-system)))
	(cond ((or (eq scheduler-mode 'real-time)
		   (eq scheduler-mode 'simulated-time))
	       (if millisecond-minimum-scheduling-interval?
		   (let ((float-minimum-scheduling-interval
			   (if millisecond-minimum-scheduling-interval?
			       (/e (coerce-fixnum-to-gensym-float
				     millisecond-minimum-scheduling-interval?)
				   1000.0)
			       0.0)))
		     (update-g2-time-to-tick
		       (+e (if (eq scheduler-mode 'real-time)
			       (managed-float-value current-g2-time)
			       current-unix-time)
			   float-minimum-scheduling-interval)
		       current-unix-time
		       current-fixnum-time))
		   (update-g2-time-to-tick-to-asap current-fixnum-time)))
	      (t
	       (update-g2-time-to-tick-to-asap current-fixnum-time))))

      (unpack-future-tasks-into-current-task-queues t)

      ;; Perhaps this warmbooting operation belongs elsewhere?  -jra 3/10/94
      (when (and warmbooting? (/=f old-gensym-time gensym-time))
	(take-actions-at-start-of-clock-tick 0)) ))))


;;;; Starting, Resetting, and Pausing the System

(defun system-pause (&key abort)
  (atomic-exchange system-is-running nil)
  (atomic-exchange system-has-paused t)
  (when abort
    (atomic-exchange system-has-aborted t))
  (defer-current-g2-running-tasks)
  (update-g2-run-state)
  ;; Finish any file operation in progress.
  (complete-save-after-running-if-necessary)
  (loop for server in list-of-all-data-servers
	for pause-function? = (function-to-pause-data-server? server) doing
    (if pause-function? (funcall-symbol pause-function?)))
  (run-state-change-hook 'pause))

(defun system-start ()
  (with-backtrace-for-internal-error 'system-start
    (cond
      ((ok-to-run-g2?)
       (let ((window-instigating-this-rule-instance? ; for initially rules referring to this window
	       (or (and (boundp 'current-workstation-window)
			current-workstation-window)
		   system-window)))
	 (reset-g2-random-state
	   (not (repeat-random-function-on-reset?-function
		  miscellaneous-parameters)))
	 ;; The indexed attribute hash tables need to be maintained at all times
	 ;; for running while inactive.  FIND ME, JRA!  -jra 9/17/96
	 (make-all-indexed-attribute-hash-tables)
	 (setq debugging-reset nil)
	 (setf (clock-get inhibit-non-real-time-clock-ticks?) nil)
	 (atomic-exchange system-is-running t)
	 (atomic-exchange system-has-paused nil)
         (atomic-exchange system-has-aborted nil)
	 (update-g2-run-state)

	 (preset-gensym-time-for-initialization)
	 
	 ;; See documentation on units of activation at the beginning of
	 ;; file ACTIVATE.
	 (atomic-exchange items-needing-initialization nil)

	 ;; Data server initialization was moved up from after system-table
	 ;; initializations.  The initializations are not dependent on any
	 ;; activation state in system-tables, they are only dependent on the
	 ;; scheduler being able to accept g2-time scheduled tasks.  -jra
	 ;; 9/17/96
	 (loop for server in list-of-all-data-servers doing
	   (funcall-symbol (function-to-initialize-data-server server)))
	 (schedule-immediate-data-server-accept-data-calls)
	 
	 (loop for frame being each class-instance of 'system-frame doing
	   (funcall-method 'activate-if-possible-and-propagate frame))

	 (loop for g2-extension being each class-instance of 'g2-extension do
	   (unless (and (superblock? g2-extension)
			(null (frame-status g2-extension)))
	     (funcall-method 'activate-if-possible-and-propagate g2-extension)))
	 (loop for block being class-instances of 'kb-workspace do
	   (when (and (null (superblock? block))
		      (null (parent-of-subworkspace? block)))
	     (funcall-method 'activate-if-possible-and-propagate block)))

	 ;; Why does this code fetch the message-board with the name message
	 ;; board instead of just iterating over the class message board?  I
	 ;; think this should be changed to an iteration.  -jra 9/17/96
	 (let ((message-board?
		 (get-instance-with-name-if-any 'message-board 'message-board)))
	   (if message-board?
	       (funcall-method 'activate-if-possible-and-propagate message-board?)))

	 ;; Note on warmboot activation. The ordinary activation suffices with two
	 ;; additions. (1) Subworkspaces of entities with activatable-subworkspace
	 ;; capability are activated if their runtime data includes #\K, (2)
	 ;; transient items in limbo are activated.
	 (when warmbooting?
	   (loop for block being each class-instance of 'block
		 when (and (transient-p block)
			   (null (superior-frame block))
			   (or (not (frame-of-class-p block 'connection)) 
			       (null (get-superblock-of-connection-frame block))))
		   do (funcall-method 'activate-if-possible-and-propagate block)))
	 
	 ;; The following is never reset. It is tested in
	 ;; post-workspace-in-pane.
	 (setq g2-has-been-started? t)
	 (collecting-updates-to-sensor-attributes
	   (initialize-items-needing-initialization))
	 (resynchronize-gensym-time-and-actual-time)
	 (notify-data-server-of-start-or-reset t)
	 (c-network-io-trace-note "Starting G2")
	 (run-state-change-hook 'start)
	 nil))

      (t (warn-upon-start-or-resume)))))


(defun system-reset ()
  (with-backtrace-for-internal-error 'system-reset
    (when (or system-has-paused system-is-running)
      ;; Complete any "field edits" in session.
      (cancel-all-field-edits-in-session)		; added. (MHD 10/6/92)
      ;; Complete any file operation in progress.
      (let ((system-has-paused nil)
	    (system-is-running nil))
	(complete-save-after-running-if-necessary))
      (let ((frame-serial-number-prior-to-reset (copy-frame-serial-number (current-frame-serial-number)))
	    (blocks-needing-representations-of-status-refreshed
	      (loop for block being each class-instance of 'block
		    when (and (frame-representations block)
			      (frame-status-and-notes-reflects-flags-of-frame-p block))
		      collect block using gensym-cons)))

	(atomic-exchange system-has-paused nil)
	(atomic-exchange system-is-running nil)
	(update-g2-run-state)
	(terminate-kb-save-or-backup-if-error-occurs)
	(setf (clock-get inhibit-non-real-time-clock-ticks?) nil)
	(clear-procedure-invocations)
	(kill-all-instances-of-all-g2gl-processes) ; for G2GL/BPEL (MHD 3/8/05)
	(disable-and-clear-system-profiling)
	(reclaim-all-indexed-attribute-hash-tables)
        (setf global-table-of-attributes-pane nil) ;; Added by SoftServe for Gensym-381
        (setf global-table-of-hidden-attributes-pane nil) ;; Added by SoftServe for Gensym-381
	(notify-sockets-of-g2-reset)
	(notify-http-servers-of-g2-reset)
	(let ((items-to-delete nil)
	      (delete-connections-without-leaving-stubs? t)
	      (connections-to-delete nil))
	  (loop for item being each class-instance of 'kb-workspace do
	    (if (and (transient-p item)
		     (null (parent-of-subworkspace? item)))
		(setq items-to-delete (gensym-cons item items-to-delete))))
	  (with-module-related-frame-note-updates-supressed
	    (loop with serial-number = (copy-frame-serial-number (current-frame-serial-number))
		  for item in items-to-delete
		  when (frame-has-not-been-reprocessed-p item serial-number)
		    do (delete-frame item)
		    finally (reclaim-frame-serial-number serial-number)))
	  (reclaim-gensym-list items-to-delete)
	  (setq items-to-delete nil)

	  (loop for block being each class-instance of 'block
		for superior? = (superior-frame block) do
	    (when (frame-of-class-p block 'item)
	      (if (and (transient-p block)
		       (or (null superior?)
			   (not (transient-p superior?))))
		  (setq items-to-delete (gensym-cons block items-to-delete)))
		  (remove-transient-relation-instances block t))
	    (when (not (eq (car items-to-delete) block))  
	      ;; When block isn't being deleted, check connections
	      (loop for connection being each output-connection of block do
		(when (and (transient-connection-p connection)
			   (symbolp (connection-frame-or-class connection)))
		  (setq connections-to-delete 
			(gensym-cons connection connections-to-delete))))))

	  (loop with serial-number = (copy-frame-serial-number (current-frame-serial-number))
		for item in items-to-delete
		do
	    (when (frame-has-not-been-reprocessed-p item serial-number)
	      (delete-item item))
		finally (reclaim-frame-serial-number serial-number))
	  (reclaim-gensym-list items-to-delete)
	  (loop with serial-number = (copy-frame-serial-number (current-frame-serial-number))
		for connection in connections-to-delete
		do
	    (when (connection-has-not-been-reprocessed-p connection serial-number)
	      (delete-connection-leaving-stubs-if-appropriate connection))
		finally (reclaim-frame-serial-number serial-number))
	  (reclaim-gensym-list connections-to-delete))
	(loop for g2-extension being each class-instance of 'g2-extension do
	  (unless (and (superblock? g2-extension)
		       (null (frame-status g2-extension)))
	    (funcall-method 'deactivate-and-propagate g2-extension nil)))
	(loop for block being class-instances of 'kb-workspace do
	  (when (and (null (superblock? block))
		     (null (parent-of-subworkspace? block)))
	    (funcall-method 'deactivate-and-propagate block nil)))
	(let ((message-board?
		(get-instance-with-name-if-any 'message-board 'message-board)))
	  (if message-board?
	      (funcall-method 'deactivate-and-propagate message-board? nil)))
	(finish-all-table-updates)	    ; clear out those scheduled updates,
;	(destroy-all-priority-queues)
	(suppressing-table-refresh-interval ;   if any & keep them out for now. (MHD 2/11/00)
	  (clear-g2-schedule)
	  (undo-kb-state-changes)
	  (clear-inform-messages)
	  (notify-data-server-of-start-or-reset nil)
	  (loop for server in list-of-all-data-servers
		for shut-down-function? = (function-to-shut-down-data-server? server) doing
	    (if shut-down-function? (funcall-symbol shut-down-function?)))
	  (cancel-data-server-accept-data-calls)
	  (loop for frame being each class-instance of 'system-frame doing
	    (funcall-method 'deactivate-and-propagate frame nil))
	  (loop for block in blocks-needing-representations-of-status-refreshed
		unless (frame-has-been-reprocessed-p
			 block frame-serial-number-prior-to-reset)
		  do (update-representations-of-slot-value
		       block 'frame-status-and-notes))
	  (reclaim-gensym-list blocks-needing-representations-of-status-refreshed)
	  (with-clock-sync
	  (setq gensym-time-at-start gensym-time)) ; do? just for hygiene.
					; (preset-gensym-time-for-initialization) ; this isn't really appropriate!
					; But it was performed here at least in 3.0 until Rev. 3.  (MHD 11/10/93)
	  (reclaim-frame-serial-number frame-serial-number-prior-to-reset)
	  ;; A G2 authorized as development or restricted-use may be made runtime
	  ;; only if runtime data saved from a runtime system was loaded into it.
	  ;; If this is the case, it gets reverted upon reset.
	  #+pre-g2-v5-licensing
	  (restore-authorization-if-temporary)
	  (run-state-change-hook 'reset))))))


(defun system-resume ()
  (cond
    ((ok-to-run-g2?)
     (setq debugging-reset nil)
     (atomic-exchange system-has-paused nil)
     (atomic-exchange system-has-aborted nil)
     (atomic-exchange system-is-running t)
     (requeue-deferred-running-tasks)
     (update-g2-run-state)
     (loop for server in list-of-all-data-servers
	   for resume-function? = (function-to-resume-data-server? server) doing
       (if resume-function? (funcall-symbol resume-function?)))
     (run-state-change-hook 'resume))
    
    (t (warn-upon-start-or-resume))))


(defun system-restart ()
  (cond
    ((ok-to-run-g2?)
     (system-reset)
     (system-start))
    
    (t (warn-upon-start-or-resume))))



;;;; System Procedures for Random Number Generation

;;;; - jpg 3/6/03

;;; The sysproc `g2-repeat-random-function' enables repeating the 
;;; sequence of random numbers without requiring a G2 reset.

(defun-for-system-procedure g2-repeat-random-function ()
  (reset-g2-random-state nil))


;;; The sysproc `g2-get-random-seed' returns the current seed,
;;; which is a non-negative fixnum, used to initialize the
;;; random number generator.

(defun-for-system-procedure g2-get-random-seed ()
  (make-evaluation-integer random-variation))


;;; The sysproc `g2-set-random-seed' enables the user to
;;; choose the seed, which can be any non-negative fixnum,
;;; used to initialize the random number generator.  When
;;; this system procedure is called, a new random state is
;;; created using this fixnum as its seed.

(defun-for-system-procedure g2-set-random-seed (seed)
  ;; The cap does type checking that SEED is a fixnum.
  (when (<f seed 0)
    (stack-error
      cached-top-of-stack
      "The argument ~a to g2-set-random-seed must be a non-negative integer."
      seed))
  (let ((user-random-seed? seed))
    (reset-g2-random-state t)))


;;; The sysproc `g2-generate-new-random-seed' returns a
;;; non-negative fixnum derived from the time-of-day clock
;;; which can be used to initialize the random number generator
;;; by calling `g2-set-random-seed' on this value.  This is the
;;; type of seed used by default by G2 when initializing the
;;; random number generator.

(defun-for-system-procedure g2-generate-new-random-seed ()
  (make-evaluation-integer (get-fixnum-time)))




;;;; Running the Scheduler



;;; The function `run-scheduler' is the main system function for running the
;;; scheduler, keeping clocks up to date, and idling the process when there is
;;; no work to be done.  This cycle can be run in several modes.  The first is
;;; real-time, where clock ticks are taken corresponding to real-time.  The
;;; second mode is simulated-time, where clock ticks will not be taken faster
;;; than one per second, but if there is more processing than can be performed
;;; within one second for a clock tick, then that processing will be completed
;;; before a tick is taken, and then only one tick will be taken, i.e. no
;;; attempt will be made to catch up to real time.  The third mode is fast-time
;;; (called "as fast as possible" to users), where clock ticks will be taken as
;;; soon as all processing for this tick has been completed.  Note that for KBs
;;; which extremely overload the CPU, fast-time will still run slower than
;;; real-time.  The last mode is nupec-catch-up mode.  It is expected that this
;;; mode will start out with a clock time which is behind real time.  The
;;; scheduler will run in fast-time until the clock has caught up with real
;;; time, and then it will switch to real-time mode.  This mode has been
;;; implemented as an enhancement to G2 under NUPEC consulting funds.

;;; The timing-parameters system-frame has been moved to workstation to allow a
;;; macro accessor.

(add-grammar-rules
  '((timing-scheduler-mode ('real 'time) real-time)
    (timing-scheduler-mode ('simulated 'time) simulated-time)
    (timing-scheduler-mode ('as 'fast 'as 'possible) fast-time)
;    #+nupec
;    (timing-scheduler-mode ('nupec 'catch 'up 'mode) nupec-catch-up)
    ))

(def-slot-value-writer timing-scheduler-mode (mode)
  (twrite-string
    (case mode
      (real-time "real time")
      (simulated-time "simulated time")
      (fast-time "as fast as possible")
      (nupec-catch-up "NUPEC catch up mode")
      (t "unknown"))))

(define-category-evaluator-interface (timing-scheduler-mode :access read-write)
    (member real-time simulated-time as-fast-as-possible)
  ((set-form (evaluation-value))
   (let ((mode (evaluation-symbol-symbol evaluation-value)))
     (if (eq mode 'as-fast-as-possible)
	 'fast-time
	 mode)))
  ((get-form (slot-value))
   (make-evaluation-symbol
     (if (eq slot-value 'fast-time) 'as-fast-as-possible slot-value))))

;; Note that the writer for nupec-catch-up mode is available in all software.
;; If a NUPEC knowledge base is loaded into a normal G2, then at least the
;; writer will print the mode correctly.



;;; The slot putter for `scheduler-mode' should ensure that the cached values
;;; for clock ticking are up to date if the scheduler mode has changed.

(def-slot-putter scheduler-mode (timing-parameters-instance new-mode)
  (setf (scheduler-mode timing-parameters-instance) new-mode)
  (when (system-table-installed-p timing-parameters-instance)
    (atomic-exchange force-clock-tick t)
    (update-g2-time-to-tick-after-scheduling-change))
  new-mode)




;;; The `install-system-table' and `deinstall-system-table' methods for
;;; timing-parameters maintain global-daylight-saving-time-adjustment, which is
;;; used to determine the real time by get-decoded-real-time.  See the function
;;; and this parameter's documentation for further details, module UTILITIES3.
;;;
;;; At the end of each, they both call
;;; update-g2-time-to-tick-after-scheduling-change, q.v.

(def-class-method install-system-table (timing-parameters)
  (setq global-daylight-saving-time-adjustment
	(clock-adjustment-in-minutes timing-parameters))
  (update-g2-time-to-tick-after-scheduling-change))

(def-class-method deinstall-system-table (timing-parameters)
  (setq global-daylight-saving-time-adjustment 0)
  (update-g2-time-to-tick-after-scheduling-change))

;; Methods on timing-parameters added for new system table constraints.  Putters
;; also modified to reflect the new constraints.  See System Frame section in
;; ENTITIES.  (MHD 10/8/91)





;;; The timing-parameters slot interface-mode controls whether or not
;;; service-workstations will respond to its time slice expiring, or whether it
;;; will always empty all workstation event queues before returning.

(add-grammar-rules
  `((interface-mode ('always 'service 'interface 'first)
		    always-service-interface-first)
    (interface-mode ('interruptible 'interface 'service)	; was misspelled as "interruptable" 
		    time-slice-dependant)))			;   until today. (MHD 6/16/92)

(def-slot-value-writer interface-mode (mode)
  (twrite
    (case mode
      (always-service-interface-first "always service interface first")
      (time-slice-dependant "interruptible interface service")	;   until today. (MHD 6/16/92)
      (t "unknown value"))))





;;;; Run Cycle Parameters





;;; The constant `scheduled-tasks-at-a-time' contains the number of tasks that
;;; should be run per pass through the body of the run-scheduler loop.  This is
;;; used to decrease the overhead of checking for input and icp buffer packets.

;(defparameter scheduled-tasks-at-a-time 2)


;;; The parameter `scheduled-tasks-time-limit' controls how long G2 will spend
;;; in run-one-scheduler-cycle processing scheduled tasks.  Each task has a 50
;;; millisecond time-slice size, so that should ideally allow about 4 tasks per
;;; pass through run-one-scheduler-cycle, but will delay receipt of network and
;;; UI events by at most a quarter second.


(defparameter scheduled-tasks-time-limit (fixnum-time-interval 200))       ;200 mS

;;; The parameters `icp-socket-processing-time-limit' and
;;; `workstation-servicing-time-limit' set the allowing time-slice size for ICP
;;; and service-workstation processing.

(defparameter icp-socket-processing-time-limit (fixnum-time-interval 50))


(declare-forward-reference initialize-check-memory function)     ;in CHECKMEMORY
#+development
(declare-forward-reference check-memory function)                ;in CHECKMEMORY

(def-system-variable countdown-for-checking CYCLES nil) ;devious name
(defmacro place-for-expiration-warning-task ()
  `countdown-for-checking)

(defparameter legacy-multisecond-heartbeat-adjustment-priority 1) ;devious name
(defmacro priority-for-expiration-warning-task ()
  `legacy-multisecond-heartbeat-adjustment-priority)

(defparameter legacy-multisecond-heartbeat-adjustment-interval 3600.0) ;devious name
(defmacro interval-for-expiration-warning-task ()
  `legacy-multisecond-heartbeat-adjustment-interval)

(defun-void do-legacy-multisecond-heartbeat-adjustments ;devious name
    ()
  (with-temporary-creation do-legacy-multisecond-heartbeat-adjustments
    (warn-of-license-expiration)))

(defun-void schedule-g2-legacy-heartbeat-tasks-if-necessary () ;devious name
  ;; The following call enforces Telewindows licensing just after the scheduler
  ;; starts running.
  (schedule-tw-modernization-tasks-if-necessary)
  ;; The following form sets up a hourly task that checks if the G2 license has
  ;; expired or is about to expire, and warns accordingly.
  (unless (schedule-task-in-place-p (place-for-expiration-warning-task))
    (with-current-scheduling ((place-for-expiration-warning-task)
			      (priority-for-expiration-warning-task)
			      (interval-for-expiration-warning-task)
			      nil
			      t)
      (do-legacy-multisecond-heartbeat-adjustments))))

(def-system-variable place-for-for-telewindows-modernization ;devious name
    CYCLES nil)
(defmacro place-for-telewindows-license-checking ()
  `place-for-for-telewindows-modernization)

(defparameter priority-for-telewindows-modernization 1)
(defmacro priority-for-telewindows-license-checking ()
  `priority-for-telewindows-modernization)

(def-system-variable interval-for-telewindows-modernization ;devious name
    CYCLES 
  (:funcall initialize-interval-for-telewindows-modernization))
(defun-simple initialize-interval-for-telewindows-modernization ()
  (+f 14 (random 5)))
(defmacro interval-for-telewindows-license-checking ()
  `interval-for-telewindows-modernization)

(defun-void do-legacy-subsecond-heartbeat-adjustments () ;devious name
  (kick-out-unauthorized-telewindows))

(defun-void schedule-tw-modernization-tasks-if-necessary () ;devious name
  (when (scheduler-enabled-p)
    (unless (schedule-task-in-place-p (place-for-telewindows-license-checking))
      (with-future-scheduling
	  ((place-for-telewindows-license-checking)
	   (priority-for-telewindows-license-checking)
	   (g2-future-interval (interval-for-telewindows-license-checking))
	   nil
	   nil
	   t)
	(do-legacy-subsecond-heartbeat-adjustments)))))

(def-system-variable multiplicative-counter-for-evaluation ;devious name
   EVAL 0)
(defmacro time-since-last-machine-id-check ()
  `multiplicative-counter-for-evaluation)

(defparameter modulus-counter-for-evaluation ;devious name
  #.(* 5 60 1000))
(defmacro interval-for-machine-id-check ()
  `modulus-counter-for-evaluation)

(def-system-variable previous-modulus-counter-for-evaluation ;devious name
    EVAL 0)
(defmacro local-fixnum-time-at-start-of-previous-clock-tick ()
  `previous-modulus-counter-for-evaluation)

(defmacro maybe-do-real-time-licensing-tasks (local-fixnum-time)
  `(let* ((fixnum-time-length-of-previous-tick
	    (fixnum-time-difference
	      ,local-fixnum-time
	      (local-fixnum-time-at-start-of-previous-clock-tick)))
	  (do-task-1-p
	    (>f (incff (time-since-last-kb-timestamp-insertion)
		       fixnum-time-length-of-previous-tick)
		(interval-for-kb-timestamp-insertion)))
	  (do-task-2-p
	    (>f (incff (time-since-last-machine-id-check)
		       fixnum-time-length-of-previous-tick)
		(interval-for-machine-id-check))))
     (when (or do-task-1-p do-task-2-p)
       (adjust-counters-for-evaluation do-task-1-p do-task-2-p))
     (setf (local-fixnum-time-at-start-of-previous-clock-tick)
	   ,local-fixnum-time)))

;;; SymScale notes: this function will be havily called by all threads, need to protect
;;; global variables accessed by them.

(defun-allowing-unwind adjust-counters-for-evaluation ;devious name
    (do-task-1-p do-task-2-p)
  (when do-task-1-p
    (insert-kb-timestamp)
    (setf (time-since-last-kb-timestamp-insertion) ;randomize it a bit
	  (modf (time-since-last-kb-timestamp-insertion) 1000)))
  (when do-task-2-p
    (have-a-nice-day)
    (setf (time-since-last-machine-id-check) ;randomize it a bit
	  (modf (time-since-last-machine-id-check) 10000))))

(defun-simple tick-the-clock (disable-caching-fixnum-time?)
  disable-caching-fixnum-time? ; used by get-fixnum-time, but not in development
  (let* ((local-fixnum-time (get-fixnum-time t disable-caching-fixnum-time?))
	 (time-at-start-of-previous-clock-tick fixnum-time-of-last-g2-tick)
	 (real-time-ticked?
	   (when (time-to-tick-real-time-p local-fixnum-time)
	     (maybe-do-real-time-licensing-tasks local-fixnum-time)
	     (tick-the-real-time-clock local-fixnum-time)))
	 (g2-time-ticked? nil))
    (case (scheduler-mode timing-parameters)
      ((real-time)
       (when (and system-is-running
		  (time-to-tick-g2-time-p local-fixnum-time)
		  (tick-the-g2-real-time-clock local-fixnum-time))
	 (take-actions-at-start-of-clock-tick
	   (fixnum-time-difference
	     local-fixnum-time
	     time-at-start-of-previous-clock-tick))
	 (setq g2-time-ticked? t)))
      ((fast-time)
       (when (and system-is-running
		  (not (tasks-enqueued-for-current-execution?))
		  (not (clock-get inhibit-non-real-time-clock-ticks?))
		  (tick-the-g2-fast-time-clock local-fixnum-time))
	 (take-actions-at-start-of-clock-tick
	   (fixnum-time-difference
	     local-fixnum-time
	     time-at-start-of-previous-clock-tick))
	 (setq g2-time-ticked? t)))
      ((simulated-time)
       (when (and system-is-running
		  (not (tasks-enqueued-for-current-execution?))
		  (not (clock-get inhibit-non-real-time-clock-ticks?))
		  (time-to-tick-g2-time-p local-fixnum-time)
		  (tick-the-g2-simulated-time-clock local-fixnum-time))
	 (take-actions-at-start-of-clock-tick
	   (fixnum-time-difference
	     local-fixnum-time
	     time-at-start-of-previous-clock-tick))
	 (setq g2-time-ticked? t)))

      ((nupec-catch-up)
       ;; If this is not a NUPEC version of G2 and the scheduler mode is 
       (cond ((nupec-authorized-p)
	      (when (and system-is-running
			 (if (clock-get nupec-catch-up-mode-caught-up?)
			     (time-to-tick-g2-time-p local-fixnum-time)
			     (and (not (tasks-enqueued-for-current-execution?))
				  (not (clock-get inhibit-non-real-time-clock-ticks?))))
			 (tick-the-nupec-catch-up-clock local-fixnum-time))
		(take-actions-at-start-of-clock-tick
		  (fixnum-time-difference
		    local-fixnum-time
		    time-at-start-of-previous-clock-tick))
		(setq g2-time-ticked? t)))
	     (t
	      (change-slot-value timing-parameters 'scheduler-mode 'real-time)
	      (warning-message 1
		  "This knowledge base was written within a NUPEC specialized ~
                  version of G2.  The scheduler mode was NUPEC catch up, but ~
                  since this is not  a NUPEC version of G2, it has been changed ~
                  to real time.")))))
    (with-temporary-creation run-one-scheduler-cycle
      (when (and real-time-ticked? (not g2-time-ticked?))
	(unpack-future-tasks-into-current-task-queues nil)))

    ;; The following function needs to be called within a scheduler that runs
    ;; all the time, not just after a G2 start!  For now we'll place a call to
    ;; it here, but this should eventually be replaced.  -jra & agh 8/4/89
    (with-backtrace-for-internal-error 'update-memory-limits
      (update-memory-limits local-fixnum-time))

    ;; record profiling information for the beginning of the clock tick
    (register-profiling-activity clock-tick)))

(defun-for-top-level run-one-scheduler-cycle ()
  (register-profiling-activity start)
  (check-memory-for-development 'run-one-scheduler-cycle_a)
  (tick-the-clock nil)
  (check-memory-for-development 'run-one-scheduler-cycle_b)
  (let ((time-slice-start-time 0))
    (with-backtrace-for-internal-error 'task-execution
      (loop with task-scheduling-start-time = (get-fixnum-time)
	    initially (setq time-slice-start-time task-scheduling-start-time)
	    for executed-task-function-name
		= (progn
		    (check-memory-for-development 'run-one-scheduler-cycle_c)
		    ;; GENSYMCID-1112: G2 aborts when loading a regular KB and
		    ;; when authorized by a specific g2.ok file.
		    ;; NOTE: here we removed `with-temporary-gensym-float-creation',
		    ;; because it caused most of time G2 is running in Local_area.
		    ;; -- Chun Tian (binghe), 2013/09
		    ;;
		    ;; GENSYMCID-1200: G2 performances slowdown between JAN 2014
		    ;; pre2 and final release
		    ;; The removed `with-temporary-gensym-float-creation' also
		    ;; prevented perf. degradation on proc. call. Nobody revert it!
		    ;; -- Chun Tian (binghe), 2014/02
		    (prog1 (dequeue-and-execute-next-task)
		      (check-memory-for-development 'run-one-scheduler-cycle_d)))
	    until (or (null executed-task-function-name)
		      (>=f (fixnum-time-difference
			     (setq time-slice-start-time (get-fixnum-time))
			     task-scheduling-start-time)
			   scheduled-tasks-time-limit))))
    (register-profiling-activity clock-tick)
    (check-memory-for-development 'run-one-scheduler-cycle_g)))


;;; The constant `g2-meters-scheduler-time-lag-variable-names-format' contains
;;; the format for intern'ing a symbol which will be used as a global variable
;;; to store the last gensym time for G2 meter servers.  Each priority level
;;; requires its own variable.  If there are n priority levels (n =
;;; how-many-priorities?), then there will be n variables required, and each of
;;; these variables will be used by one of the n servers to compute the various
;;; scheduler time lags for different priority levels.  These servers are
;;; defined at compile time by the macro `define-g2-meters-for-scheduler-time-
;;; lags' in the "g2-meters" module.  Because make-last-gensym-time-variable-
;;; name-for-g2-meters is only required at compile time, it can be defined using
;;; defun-for-macro instead of defun.  -pto 16aug88

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant g2-meters-scheduler-time-lag-variable-names-format
	       "PRIORITY-~a-LAST-GENSYM-TIME"))



;;; The macro `define-scheduler-functions-and-variables-for-g2-meters' is called
;;; at the top level just below here to define system variables for each
;;; priority and it also defines a global list of these variables.

;;; The variable PRIORITY-x-LAST-GENSYM-TIME gives the last time for which a
;;; task of priority level x was executed.


(defmacro define-scheduler-variables-for-g2-meters ()
  (let ((meter-variables
	  (loop for priority from 1 to how-many-priorities?
		collect (intern
			  (format
			    nil
			    g2-meters-scheduler-time-lag-variable-names-format
			    priority)))))
    `(progn
       ,@(loop for variable in meter-variables
	       collect
	       `(def-system-variable ,variable CYCLES 0))
       ,@(if (eval-feature :development)
	     (loop for variable in meter-variables
		   collect
		   `(pushnew ',variable *list-of-symbols-for-symbol-value*)))

       (defvar meter-lag-time-variables ',meter-variables))))

(define-scheduler-variables-for-g2-meters)




;;; The function `update-scheduler-time-lag' takes a symbol containing the data
;;; for scheduler lag at a given priority, and takes the gensym-time at which
;;; this task was scheduled for execution.  It merely sets the given time into
;;; the given variable.

(def-system-variable g2-meter-task-count cycles 0)

(defun update-scheduler-time-lag (lag-meter schedule-time)
  (decff g2-meter-task-count)
  (setf (symbol-value lag-meter) schedule-time))



;;; The function `reset-all-scheduler-lag-time-variables' sets all the variables
;;; priority-x-last-gensym-time's to the current gensym-time.  It is called by
;;; `reset-g2-meters' (defined in module G2-METERS).

(defun reset-all-scheduler-lag-time-variables ()
  (loop for variable in meter-lag-time-variables
	do
    (setf (symbol-value variable) gensym-time))
  (setq g2-meter-task-count 0))




;;; The function `schedule-tasks-for-updating-g2-meters-last-gensym-times' is
;;; called from take-actions-at-start-of-clock-tick.  It will schedule the tasks
;;; necessary to keep the scheduler lag meters up to date.

;;; Note that if the last task on the queue for a priority is the task for
;;; updating that we scheduled at the beginning of the last clock tick, then we
;;; may update the argument to that call.  This will prevent tasks from
;;; unendingly building up in priorities which are lagging far behind
;;; gensym-time.

;;; To prevent buildup of meter lag tasks in the scheduler, there is an absolute
;;; limit. G2-meter-task-limit is the limit and g2-meter-task-count is the count.
;;; It is incremented when the task is scheduled, and decremented when the task is
;;; executed. This task cannot be cancelled or rescheduled. But it is necessary to
;;; decrement the count also in clear-schedule.

(defconstant g2-meter-task-limit 100)

(defun schedule-tasks-for-updating-g2-meters-last-gensym-times ()
  )






;;; The function `take-actions-at-start-of-clock-tick' is called at the
;;; beginning of every clock tick, with the length of the previous tick fixnum
;;; time units as its only argument.  This function should take care of updating
;;; meters, calling data servers, and doing anything else that needs to be
;;; performed right at the start of a clock tick before anything else happens.

(defun-allowing-unwind take-actions-at-start-of-clock-tick
    (fixnum-time-length-of-previous-tick)
  #+development (update-pseudo-run-lights :take-actions-at-start-of-clock-tick)

  ;; Transfer all scheduled tasks that are due for execution into the
  ;; current queue.
  (with-backtrace-for-internal-error 'unload-scheduler-into-current-queue
    (unpack-future-tasks-into-current-task-queues t))

  ;; Here we spawn n tasks (n=how-many-priorities?) to update variables for
  ;; computing scheduler lag times for different priority tasks.  The following
  ;; function is defined by the macro define-scheduler-functions-and-
  ;; variables-for-g2-meters and MUST BE CALLED JUST AFTER unload-scheduler-
  ;; into-current-queue.  We can't spawn tasks for updating last gensym-time
  ;; variables before unload-scheduler-into-current-queue because the spawned
  ;; tasks with lower priorities than meter update priorities will will be
  ;; updated after the meters are read, and the lag values read by them will be
  ;; off by one.
  (when (g2-meter-data-service-on? data-server-parameters)
    (update-meter-values fixnum-time-length-of-previous-tick)
    (schedule-tasks-for-updating-g2-meters-last-gensym-times))

  ;; Reset the debugging parameters if they have been modified during the clock
  ;; tick.
  (reset-debugging-parameters)

  ;; The only way this could be left t is if an abort occurred within instantiate-variable,
  ;; or instantiate-object-in-attribute. It probably can't happen, but if it did, it would
  ;; leave G2 permanently unable to instantiate items as attributes of items. ML, 14 Sept. 89
  (setq recursive-attribute-nesting-has-occurred? nil))




;;; The system variable `data-server-accept-data-task' contains either NIL or a
;;; scheduled task which will call schedule-data-server-accept-data-calls when
;;; there are data servers that need accept data to be called.

(declare-special-global data-server-accept-data-task)
(def-system-variable data-server-accept-data-task cycles nil)




;;; The function `schedule-data-server-accept-data-calls' will schedule a task
;;; to occur at the next one second block tick boundary after it is called.
;;; This should only be called with G2 running or paused.  The function
;;; `cancel-data-server-accept-data-calls' cancels this task.

(defun-void schedule-data-server-accept-data-calls ()
  (when (or system-is-running system-has-paused)
    (when (or (not (schedule-task-in-place-p data-server-accept-data-task))
	      (schedule-task-currently-executing-p data-server-accept-data-task))
      (with-future-scheduling
	  (data-server-accept-data-task
	    (priority-of-data-service data-server-parameters)
	    (+e (ffloore-first (managed-float-value (clock-get current-g2-time))) 1.0))
	(call-data-server-accept-data-functions)))))

(defun-void schedule-immediate-data-server-accept-data-calls ()
  (when (or system-is-running system-has-paused)
    (with-current-scheduling (data-server-accept-data-task
			       (priority-of-data-service data-server-parameters))
      (call-data-server-accept-data-functions))))

(defun-void cancel-data-server-accept-data-calls ()
  (cancel-task data-server-accept-data-task))




;;; The function `call-data-server-accept-data-functions' iterates over all data
;;; servers, scheduling separate tasks to call accept data for each of these
;;; server, when accept data needs to be called.  If any data server needs
;;; accept data called, then reschedule the call to this function for the next
;;; second.

(defun call-data-server-accept-data-functions ()
  (with-backtrace-for-internal-error 'handle-all-data-servers
    (loop with continue-accept-data-calls? = nil
	  for data-server in list-of-all-data-servers
	  do
      (when (data-server-requests-accept-data-calls data-server)
	(setq continue-accept-data-calls? t)
	(when (server-is-in-use data-server)
	  (schedule-task-to-accept-data data-server)))
          finally
	    (when continue-accept-data-calls?
	      (schedule-data-server-accept-data-calls)))))

(defun schedule-task-to-accept-data (data-server)
  (when (server-is-in-use data-server)
    (unless (and (schedule-task-in-place-p
		   (task-to-accept-data data-server))
		 (not (schedule-task-currently-executing-p
			(task-to-accept-data data-server))))
      (with-current-scheduling
	  ((task-to-accept-data data-server)
	   (priority-of-data-service data-server-parameters))
	(accept-data-and-reschedule-if-necessary data-server)))))

(defun-simple accept-data-and-reschedule-if-necessary (data-server)
  (when (server-is-in-use data-server)
    (setq time-slice-start-time (get-fixnum-time))
    ;; Function-to-accept-data returns t if it finished all work.
    (unless (funcall-symbol (function-to-accept-data data-server))
      (schedule-task-to-accept-data data-server))))




;;; The function `continue-data-server-data-acceptance' is called with a data
;;; server and a gensym-time as its arguments.  If the current gensym-time is
;;; equal to the passed gensym time, then the data server's function to accept
;;; data should be funcalled.  If the passed time is not the current time, then
;;; a clock tick has occurred, this data server has already been given more
;;; time, and if anything still needs to be done for it, another continuation
;;; will already have been produced.  If the function to accept data returns T,
;;; then the data server is done and we should return.  If it returns NIL, then
;;; the data server is not yet finished, and we should schedule another
;;; continuation call to this function.

;; jh, 5/23/91.  Note that the function continue-data-server-data-acceptance is
;; not obsolete, since it is used in
;; end-simulation-procedure-or-external-simulation-cycle in SIMULATE2.  The main
;; scheduler, however, no longer works by continuing data acceptance; it always
;; schedules a task to accept data, even at first.  Perhaps AGH should review
;; end-simulation-procedure-or-external-simulation-cycle to see if the new data
;; acceptance machinery can be used there.  At any rate, changed the call to
;; priority-of-continued-data-service to priority-of-data-service in
;; continue-data-server-data-acceptance here.

(defun-void continue-data-server-data-acceptance (data-server continuation-time)
  ;; I have some qualms about this -rdf, 1/19/95
  (when (and (=e (managed-float-value continuation-time) (managed-float-value (clock-get current-g2-time)))
	     (server-is-in-use data-server))
    (when (not (funcall-symbol (function-to-accept-data data-server)))
      (with-current-scheduling
	  (nil (priority-of-data-service data-server-parameters))
	(continue-data-server-data-acceptance
	  data-server
	  continuation-time)))))

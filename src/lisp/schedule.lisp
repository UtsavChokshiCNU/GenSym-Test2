;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SCHEDULE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard



;; To NETEVENT

(declare-forward-reference ne-set-next-timer-event function)
(declare-forward-reference ne-enqueue-scheduler-event function)
(declare-forward-reference g2-event-ready-p function)
(declare-forward-reference get-pending-network-events function)


;; To WORKSTATION

(declare-forward-reference timing-parameters variable)
(declare-forward-reference scheduler-mode-function function)
(declare-forward-reference minimum-scheduling-interval-function function)
(declare-forward-reference name-and-class-for-computation-instance function)

;; To CLOCKS

(declare-forward-reference milliseconds-to-next-task function)
(declare-forward-reference current-g2-time variable)
(declare-forward-reference current-real-time variable)
(declare-forward-reference gensym-time variable)
(declare-forward-reference gensym-base-time-as-managed-float variable)
(declare-forward-reference tick-the-clock-for-tw-or-gsi function)

;; To SETS

(declare-forward-reference profiling-enabled? variable)
(declare-forward-reference posit-profiling-structure function)
(declare-forward-reference exit-current-profiling-context function)

;; To CYCLES

(declare-forward-reference tick-the-clock function)

;; To WINDOWS3

#+development
(declare-forward-reference update-pseudo-run-lights function)

;; To GSI

(declare-forward-reference loadable-bridges-enabled-p variable)

;; To STACK-KERN

(declare-forward-reference g2-event-loop function)
#+SymScale
(declare-forward-reference g2-worker-loop function)

#+SymScale
(declare-forward-references-to-module PARSE
  (current-grammar variable)
  (current-indicator-for-category-of-this-name variable)
  (current-indicator-for-category-of-symbol-token variable))

#+SymScale
(declare-forward-references-to-module PROC-UTILS
  (procedure-invocation? function)
  (current-procedure-is-running? function)
  (try-register-current-procedure function)
  (unregister-current-procedure function))

;;;; Scheduler



(def-concept scheduler)

;;; This module contains the scheduler for G2.  The majority of uses of this
;;; facility will be to schedule tasks using `with-future-scheduling',
;;; `with-current-scheduling', or `with-immediate-scheduling' or to cancel tasks
;;; with `cancel-task'.  Tasks are executed from run-scheduler-1 by calling
;;; `dequeue-and-execute-next-task'.  Other operations include reschedule-task,
;;; schedule-task-in-place-p, change-priority-of-task, and
;;; schedule-anonymous-single-task (previously schedule-current-task), and
;;; scheduler-time-lag.  See documentation near the definitions of these macros
;;; for details.

;; Examine what to do with the following: variable dequeuing-time, macro
;; schedule-time-of-scheduled-task, the function execute-task-out-of-order, the
;; function clear-schedule, the macro tasks-enqueued-for-current-execution,
;; variables system-is-running and system-is-paused.
;; -jra 2/17/94

;;; The code in this file replaces that of a older scheduler as of February,
;;; 1994.  Both of these schedulers have the following features.  They

;;;   execute tasks running them at given priorities,
;;;   can delay the start of tasks,
;;;   can run tasks cyclicly, i.e. repeating the task at a given frequency,
;;;   are robust in the face of non-local exits out of a task, and
;;;   can cancel tasks.

;;; The new scheduler also has the following additional features.  It

;;;   can delay or cycle tasks using subsecond (i.e. float) intervals,
;;;   runs tasks when G2 is reset,
;;;   can defer so-called "G2-is-running" tasks while G2 is paused, and
;;;   has a new immediate-task queue for enqueueing tasks to run immediately
;;;     after the current task.

;;; The design of this mechanism includes several sets of task-queues.  There
;;; should be one task queue, the immediate task queue, into which tasks of the
;;; highest priority are placed.  When a task is running, and it needs actions
;;; to occur immediately after that task, those actions should be implemented as
;;; tasks run through the immediate task queue.

;;; The current task queues, one queue per different priority, are for the tasks
;;; that are currently attempting to run.  There will be 12 priorities, with one
;;; task-queue for each.  Queues 1 through 10 will hold tasks at the user
;;; priorities, priority 0 is reserved for system tasks running at a priority
;;; higher than any user priority, and priority 11 is for system tasks running
;;; at a priority lower than any user priority.  All tasks currently eligible to
;;; run are in either the immediate task queue or the one of the current task
;;; queues.

;; There has been a suggestion to allow floating point priority values.  This
;; could be done if we allow the number of priority queues to vary, one per
;; floating point priority currently in use, just as we are about to have one
;; task queue per floating point time at which tasks are scheduled.  Not today.
;; -jra 2/17/94

;;; The deferred task queues, one queue per priority, are for tasks that should
;;; execute only when G2 is running.  Those tasks are placed into this queue
;;; when G2 is paused.  When G2 is resumed, these tasks will be moved back from
;;; the deferred queues into the current queues.

;;; There are two sets of future task queues.  The future real time task queues
;;; are for tasks scheduled to occur in the future at particular real-time clock
;;; times and priorities.  The future g2 time task queues are for g2-running
;;; tasks scheduled to occur in the future at particular gensym-time clock times
;;; and priorities.

;;; There is a total ordering of the task queues in each set of future queues,
;;; based primarily on the task time for the tasks in that queue and based
;;; secondarily on the priority of the tasks in that queue.  All tasks in the
;;; same queue will have the same task time and priority.  The number of task
;;; queues will vary, depending on the times and priorities of the currently
;;; existing scheduled tasks.  These task queues will be entered in a balanced
;;; binary tree to limit the amount of time needed to look up any individual
;;; queue.

;;; In G2 there are two notions of time, one being the current real time and the
;;; other being the G2 current time.  When G2 is running in simulated or
;;; fast-as-possible time, these two will vary considerably.  However, even when
;;; G2 is running in real-time they may vary, depending on the scheduler-quantum
;;; in the timing parameters and because of pausing and resetting KBs.  Because
;;; of these two notions of time, we are keeping two sets of event queues for
;;; future events, one for real time and one for G2 time.  In general, tasks in
;;; these two different queues should be considered ordered relative to each
;;; other, since at any moment a KB may be paused, reset, or have its
;;; scheduler-mode changed.  Lisp code should be written to not make ordering
;;; assumptions between the two queues.

;;; When it is time to tick the clock, tasks will be unpacked from the two sets
;;; of future queues into the current queues.  The function to unpack the future
;;; queues will be given the current real-time and the current G2 time.  For
;;; those task-queues in the future queue sets whose scheduling time is less
;;; than or equal to the current dequeuing time, the tasks in these queues will
;;; be placed onto the end of the current task-queues of the same priority.

;;; When G2 is not running, or when it is running but in a scheduler mode other
;;; than real-time, then the future real-time set of queues will always be
;;; unpacked into the current queues before the future G2 time set of queues.
;;; When G2 is running in real-time mode, then the relative ordering of tasks
;;; within the two queues will be maintained, with tasks from both the real time
;;; and G2 time queues ending up properly interleaved into the resulting current
;;; queues.  When there is a tie between the two, then the real-time queues will
;;; be unpacked first.

;;; Finally, note that none of the task queues in the future queue set will be
;;; allowed to be empty.  So if a future task queue exists with one task in it,
;;; and that task is cancelled, that queue will be deleted and removed from the
;;; balanced binary tree of queues.  This ensures that all memory for a task is
;;; reclaimed when that task is canceled.

;; Within the first implementation of this mechanism, the balanced binary tree
;; of future task-queues will instead be implemented with a list.  This will
;; give us an implementation which can be tuned with the addition of the faster
;; mechanism for finding, adding, and removing future task-queues.  -jra 2/17/94






;;;; Abstraction for priorities




;;; The following macros abstract some operations on priorities.  Priorities are
;;; currently fixnums from 0 through 11 the smaller the number, the higher the
;;; priority.

;;; The constant `how-many-priorities?' lists how many priorities there are from
;;; a user perspective.  The constant `highest-user-priority' holds the highest
;;; priority value available to user code.  The constants
;;; `highest-system-priority' and `lowest-system-priority' hold the inclusive
;;; bounds of the priority system as seen by the system.  The constants
;;; `higher-than-any-priority' and `lower-than-any-priority' hold fixnums that
;;; are above and below the range of priorities, used to reset values that would
;;; otherwise normally hold priorities.

(defconstant how-many-priorities? 10)

(defconstant highest-user-priority 1)

(defconstant highest-system-priority 0)

(defconstant lowest-system-priority 11)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant higher-than-any-priority -1)
  (defconstant lower-than-any-priority 12))

(defmacro highest-priority (&rest args)
  `(minf ,@args))

(defmacro lowest-priority (&rest args)
  `(maxf ,@args))

(defmacro lower-priority-p (&rest args)
  `(>f ,@args))

(defmacro lower-or-equal-priority (&rest args)
  `(>=f ,@args))

(defmacro higher-priority-p (&rest args)
  `(<f ,@args))

(defmacro higher-or-equal-priority (&rest args)
  `(<=f ,@args))

(defmacro equal-priority-p (&rest args)
  `(=f ,@args))

(def-substitution-macro priority-p (thing)
  (and (fixnump thing)
       (>f thing 0)
       (<=f thing how-many-priorities?)))

(def-substitution-macro system-priority-p (thing)
  (and (fixnump thing)
       (lower-or-equal-priority thing highest-system-priority)
       (higher-or-equal-priority thing lowest-system-priority)))






;;;; Scheduler Structures and Variables

#+(and SymScale (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :schedule-task-has-a-queue *features*))

;;; The structure `schedule-task' is used to store all information about a
;;; scheduled task.  Scheduled tasks can currently take up to 4 arguments.  More
;;; can be added as necessary, though it means increasing storage needs for all
;;; schedule tasks.

;;; Note that the floats for task-time, cycle-time, and initial-schedule-time 

(def-structure (schedule-task 
		(:creations-at-a-time 50)
		(:constructor make-schedule-task
		  (schedule-task-reclaimable-by-scheduler-p))
		(:slot-offset (schedule-task-arg-1 schedule-task-arg-offset))
		#+development
		(:print-function print-schedule-task))
  (schedule-task-simple-float-array (allocate-managed-simple-float-array 2)
				    :initialize-on-recycle nil)
  schedule-task-reclaimable-by-scheduler-p
  schedule-task-g2-running-p
  schedule-task-priority
  schedule-task-ensure-cycle-anniversaries-p
  schedule-task-queue-element
  schedule-task-function-name		; for profiling
  schedule-task-function
  ;; the following reclaimer function also reclaims slots arg-1 thru arg-4 
  ;; if necessary.
  (schedule-task-argument-reclaimers nil :reclaimer reclaim-schedule-task-args)
  #+SymScale schedule-task-thread
  #+mtg2 schedule-task-faction?
  #+schedule-task-has-a-queue schedule-task-queue
  schedule-task-argument-count
  schedule-task-arg-1			; argument slots must be contiguous!
  schedule-task-arg-2
  schedule-task-arg-3
  schedule-task-arg-4)

(defconstant schedule-task-arg-limit 4)

(defmacro schedule-task-arg (task n)
  ;; one must believe the compiler will fold the sum when both arguments are fixnums...
  `(svref ,task (+f ,n schedule-task-arg-offset)))

(defun reclaim-schedule-task-args (reclaimers)
  (when reclaimers
    (let (f)
      (loop for i below schedule-task-arg-limit do
	(setf f (gensym-pop reclaimers))
	(when f
	  (funcall f (schedule-task-arg structure-being-reclaimed i))
	  (setf (schedule-task-arg structure-being-reclaimed i) nil))))))

(defun-simple print-schedule-task (schedule-task stream depth)
  (declare (ignore depth))
  (current-system-case
    (gsi schedule-task stream)
    (t
      (printing-random-object (schedule-task stream)
	(format stream "TASK (")
	(format stream "~S" (schedule-task-function-name schedule-task))
	(loop for i below (schedule-task-argument-count schedule-task) do
	  (format stream " ~S" (schedule-task-arg schedule-task i)))
	(format stream ")"))))
  schedule-task)

;;; The macros `schedule-task-time' and `schedule-task-cycle-interval' access
;;; double floats within the simple float array for a schedule task.  They are
;;; setfable, and return a gensym-float.  The task-time is the unix-float time
;;; at which the task should begin execution, and the cycle interval is the
;;; frequency in seconds at which the task should be executed.

(defmacro schedule-task-time (schedule-task)
  `(float-vector-aref (schedule-task-simple-float-array ,schedule-task) 0))

(defmacro schedule-task-cycle-interval (schedule-task)
  `(float-vector-aref (schedule-task-simple-float-array ,schedule-task) 1))




;;; During development, we will hold symbols to represent functions within tasks
;;; so that tracing will work on scheduled tasks.  (Most Lisp implementations
;;; implement tracing by replacing the symbol-function cell of a symbol with a
;;; new function that emits trace info.)  During non-development, we will store
;;; compiled-function objects within the schedule-task structures so that
;;; runtime calls to symbol-function (which is suprisingly slow in Chestnut)
;;; will be eliminated.

;;; The macro `task-function-for-symbol' takes an unquoted, unevaluated symbol
;;; and expands to the form that will return the appropriate function object or
;;; symbol that can be stored within a task.  The macro
;;; `compiled-function-of-task-function' takes a task function and returns the
;;; compiled-function object for that task function.

(defmacro task-function-for-symbol (symbol)
  #+development
  `',symbol
  #-development
  `#',symbol)

(defmacro compiled-function-of-task-function (task-function)
  #+development
  `(symbol-function ,task-function)
  #-development
  task-function)


;;; The substitution macro `execute-schedule-task' takes a schedule task as its
;;; only argument.  This macro funcalls the schedule-task-function on the
;;; arguments.

#+development
(defvar trace-task-execution-p nil)

(def-substitution-macro execute-schedule-task (schedule-task)
  #+development
  (update-pseudo-run-lights :execute-task)
  #+development
  (when trace-task-execution-p
    (format t "~&Executing task ~S~%" schedule-task))
  (current-system-case
    (ab (when profiling-enabled?
	  (posit-profiling-structure schedule-task))))
  (let ((function (compiled-function-of-task-function
		    (schedule-task-function schedule-task))))
    (fixnum-case (schedule-task-argument-count schedule-task)
      ((0)
       (funcall-simple-compiled-function function))
      ((1)
       (funcall-simple-compiled-function
	 function
	 (schedule-task-arg-1 schedule-task)))
      ((2)
       (funcall-simple-compiled-function
	 function
	 (schedule-task-arg-1 schedule-task)
	 (schedule-task-arg-2 schedule-task)))
      ((3)
       (funcall-simple-compiled-function
	 function
	 (schedule-task-arg-1 schedule-task)
	 (schedule-task-arg-2 schedule-task)
	 (schedule-task-arg-3 schedule-task)))
      ((4)
       (funcall-simple-compiled-function
	 function
	 (schedule-task-arg-1 schedule-task)
	 (schedule-task-arg-2 schedule-task)
	 (schedule-task-arg-3 schedule-task)
	 (schedule-task-arg-4 schedule-task)))))
  (current-system-case
    (ab (when profiling-enabled?
	  (let ((current-time (allocate-managed-float (gensym-get-unix-time))))
	    (exit-current-profiling-context current-time)
	    (reclaim-managed-float current-time))))))

;; For tracing. Also, can trace cancel-and-reclaim-scheduled-queue-element-1
(defun-simple note-scheduling-task-1 (function-name task)
  (declare (ignore function-name task))
  nil)

(defmacro note-scheduling-task (function-name task)
  #-development (declare (ignore function-name task))
  #-development nil
  #+development `(note-scheduling-task-1 ,function-name ,task))

;;; The macro `schedule-task-store-function-and-args' takes a schedule-task and
;;; modifies it to hold the given function and arguments.

(defmacro schedule-task-store-function-and-args
    (schedule-task function-name function &rest args)
  (let ((task schedule-task)
	(bindings '(progn)))
    (when (not (symbolp schedule-task))
      (setq task (make-symbol "TASK"))
      (setq bindings `(let ((,task ,schedule-task)))))
    (append
      bindings
      `((setf (schedule-task-function-name ,task) ,function-name)
	(setf (schedule-task-function ,task) ,function)
	(setf (schedule-task-argument-count ,task) ,(length args))
	,@(loop for arg-number from 1
		for arg in args
		collect
		`(setf (,(intern (format nil "SCHEDULE-TASK-ARG-~a" arg-number))
			 ,task)
		       ,arg))
	(note-scheduling-task (schedule-task-function-name ,task) ,task)))))

#+SymScale
(declare-special-global immediate-task-queue
                        immediate-task-queue-vector
                        current-task-queue-vector
                        deferred-task-queue-vector
                        future-real-time-tasks
                        future-g2-time-tasks)

;;; The system variable `immediate-task-queue' holds a constant-queue which is
;;; filled with tasks which will be executed before the scheduler will return
;;; control to its caller.  Tasks which need to postpone actions until just
;;; after that task finishes

(def-system-variable immediate-task-queue schedule nil)

;;; In SymScale, `immediate-task-queue' is now a vector: each threads maintain
;;; their own task queues. Immediate tasks of procedure (code body invocation)
;;; will be put into immediate task queue which belongs to the current running
;;; thread, but most of other immediate tasks should go to main thread. Such a
;;; task queue can also be accessed by other threads, if necessary.  -- binghe

#+SymScale
(def-system-variable immediate-task-queue-vector schedule nil)

;;; The system variable `current-task-queue-vector' holds a simple vector
;;; holding constant-queues, one per priority.  These tasks are all currently
;;; attempting to be executed.

(def-system-variable current-task-queue-vector schedule nil)



;;; The system variable `deferred-task-queue-vector' holds a simple vector of
;;; constant-queues, one per priority.  These tasks were "g2-running-p" tasks
;;; that came up for execution while G2 was paused.

(def-system-variable deferred-task-queue-vector schedule nil)



;;; The system variable `future-real-time-tasks' holds a list of
;;; constant-queues, one for each combination of task time and priority of tasks
;;; scheduled to occur in real time.

;; Note that this is an interim implementation until I can get a balanced binary
;; tree in place.  -jra 2/19/94

;; Note that after 20 years, now we have implemented a O(log n) priority-queue
;; based on skip list.  -binghe, 11/16/2014

(def-system-variable future-real-time-tasks schedule nil)



;;; The system variable `future-g2-time-tasks' holds a list of constant-queues,
;;; one for each combination of task time and priority of tasks scheduled to
;;; occur in G2 time.

;; Note that this is an interim implementation until I can get a balanced binary
;; tree in place.  -jra 2/19/94

;; Note that after 20 years, now we have implemented a O(log n) priority-queue
;; based on skip list.  -binghe, 11/16/2014

(def-system-variable future-g2-time-tasks schedule nil)



;;; The structure `future-task-queue-holder' is used to make up elements of the
;;; future task queue.  It currently is arranged as a list, but will eventually
;;; be used to implement balanced binary trees of future task queues.

(def-structure (future-task-queue-holder
		 (:type vector)
		 (:creations-at-a-time 50)
		 (:constructor make-future-task-queue-holder-1 ())
		 (:reclaimer reclaim-future-task-queue-holder-1))
  future-task-queue-next-queue ; simple-vector in skip-list
  (future-task-queue-time
    (allocate-managed-float-box) :initialize-on-recycle nil)
  future-task-queue-priority
  future-task-queue-constant-queue
  #+skip-list
  future-task-queue-top-level)

#+skip-list
(defmacro future-task-queue-next-queue-0 (future-task-queue)
  `(atomic-reference-object
     (svref (future-task-queue-next-queue ,future-task-queue) 0)))

#+skip-list
(defmacro future-task-queue-next-queue-n (future-task-queue level)
  `(atomic-reference-object
     (svref (future-task-queue-next-queue ,future-task-queue) ,level)))

#+skip-list
(defconstant future-task-queue-max-level 15)

#+skip-list
(defun make-future-task-queue-holder-sentinel (task-time tail)
  (let ((node (make-future-task-queue-holder-1-macro))
        (next (allocate-managed-simple-vector-for-skip-list (1+f future-task-queue-max-level))))
    (mutate-managed-float-value
      (future-task-queue-time node) task-time)
    (setf (future-task-queue-priority node) 0)
    (loop for i from 0 to future-task-queue-max-level do
      (setf (svref next i) (make-atomic-reference tail)))
    (setf (future-task-queue-next-queue node) next)
    node))

#+skip-list
(defun make-future-task-priority-queue ()
  (let* ((tail (make-future-task-queue-holder-sentinel most-positive-double-float nil))
         (head (make-future-task-queue-holder-sentinel most-negative-double-float tail)))
    (lookup-cons-macro head tail)))

;;; The macro `make-future-task-queue-holder' takes a task-time and a priority
;;; and returns a newly created task-queue holder.

(defmacro make-future-task-queue-holder (task-time priority #+skip-list top-level)
  (let ((new-holder (make-symbol "NEW-HOLDER"))
	(new-queue (make-symbol "NEW-QUEUE")))
    `(let ((,new-holder (make-future-task-queue-holder-1-macro))
	   (,new-queue (make-empty-constant-queue)))
       (setf (queue-datum ,new-queue) future-task-queue-marker)
       (setf (future-task-queue-constant-queue ,new-holder) ,new-queue)
       (mutate-managed-float-value
	 (future-task-queue-time ,new-holder) ,task-time)
       (setf (future-task-queue-priority ,new-holder) ,priority)
       #-skip-list
       (setf (future-task-queue-next-queue ,new-holder) nil)
       #+skip-list
       (setf (future-task-queue-next-queue ,new-holder)
	     (allocate-managed-simple-vector-for-skip-list (1+f ,top-level)))
       #+skip-list
       (setf (future-task-queue-top-level ,new-holder) ,top-level)
       ,new-holder)))



#+(and development skip-list)
(defun describe-future-task-queue (future-task-queue)
  (let ((head (car future-task-queue))
        (tail (cdr future-task-queue))
        (level-list nil)
        (max-level 0)
        (element-list nil)
        (n-element 0))
    ;; get level 0 element first
    (loop for node = (future-task-queue-next-queue-0 head)
                then (future-task-queue-next-queue-0 node)
          until (eq node tail)
          maximize (future-task-queue-top-level node) into m
          finally (setq max-level m)
          do
      (push (future-task-queue-top-level node) level-list)
      (push (loop for e being each constant-queue-element of (future-task-queue-constant-queue node)
                  collect e)
            element-list)
      (incf n-element))
    (setq level-list (nreverse level-list))
    (setq element-list (nreverse element-list))
    ;; print the table
    (unless level-list
      (format t "Future task queue is empty.~%")
      (return-from describe-future-task-queue))
    (loop for i from max-level downto 0 do
      (format t "Level ~2D: " i)
      (loop with node = head
            for j in level-list
            for n = 1 then (1+ n)
            until (eq node tail)
            do
        (if (>= j i)
            (progn
              (setq node (future-task-queue-next-queue-n node i))
              (format t "#"
                      (future-task-queue-constant-queue node)))
          (format t " ")))
      (terpri))
    (terpri)
    element-list))

#+development
(defun describe-task-queue-vector (task-queue-vector)
  (loop with results = nil
        for priority from highest-system-priority to lowest-system-priority
        do
    (format t "Priority: ~d~%" priority)
    (push (cons priority
                (describe-constant-queue (svref task-queue-vector priority)))
          results)
    (terpri)
        finally
          (return (nreverse results))))




;;; The substitution macro `reclaim-future-task-queue-holder' takes a task-queue
;;; holder with an empty constant queue and reclaims it.

(defun reclaim-future-task-queue-holder
    (future-task-queue-holder)
  (reclaim-constant-queue
    (future-task-queue-constant-queue future-task-queue-holder))
  #+skip-list
  (progn
    (reclaim-managed-simple-vector-for-skip-list
      (future-task-queue-next-queue future-task-queue-holder))
    (setf (future-task-queue-next-queue future-task-queue-holder) nil))
  (reclaim-future-task-queue-holder-1-macro future-task-queue-holder))


;;; The iteration path `future-task-queue-holder' takes a set of future task
;;; queue holders such as is found in future-g2-time-tasks, and iterates over
;;; all of the future-task-queue-holders in it.  Note that tasks can be deleted
;;; from the currently served queue-holder, but deleting other tasks from other
;;; queues in this set has undefined effects.

(define-loop-path (future-task-queue-holder) future-task-queue-holders-of (of))

#+skip-list
(defun-for-macro future-task-queue-holders-of
    (path-name variable data-type prep-phrases inclusive?
	       allowed-preposistions data)
  (declare (ignore data-type data allowed-preposistions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S."
	   path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~s path of ~s ~
            (prep-phrase = ~s)"
	   path-name variable prep-phrases))
  (let* ((next-queue-holder (make-symbol "NEXT-QUEUE-HOLDER"))
	 (head (make-symbol "HEAD"))
	 (tail (make-symbol "TAIL"))
	 (init-bindings
	   `((,head (car ,(second (car prep-phrases))))
	     (,tail (cdr ,(second (car prep-phrases))))
	     (,next-queue-holder nil)
	     (,variable nil)))
	 (prologue-forms
	   `((setq ,next-queue-holder (future-task-queue-next-queue-0 ,head))))
	 (pre-step-tests `(eq ,next-queue-holder ,tail))
	 (steppings nil)
	 (post-step-tests nil)
	 (post-step-settings
	   `(,variable ,next-queue-holder
	     ,next-queue-holder
	     (future-task-queue-next-queue-0 ,next-queue-holder))))
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

#-skip-list
(defun-for-macro future-task-queue-holders-of
    (path-name variable data-type prep-phrases inclusive?
	       allowed-preposistions data)
  (declare (ignore data-type data allowed-preposistions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S."
	   path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~s path of ~s ~
            (prep-phrase = ~s)"
	   path-name variable prep-phrases))
  (let* ((next-queue-holder (make-symbol "NEXT-QUEUE-HOLDER"))
	 (init-bindings
	   `((,next-queue-holder (future-task-queue-next-queue
				   ,(second (car prep-phrases))))
	     (,variable nil)))
	 (prologue-forms nil)
	 (pre-step-tests `(null ,next-queue-holder))
	 (steppings nil)
	 (post-step-tests nil)
	 (post-step-settings
	   `(,variable ,next-queue-holder
	     ,next-queue-holder
	     (future-task-queue-next-queue ,next-queue-holder))))
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))




;;; The system variables `system-is-running' and `system-has-paused' are flags
;;; which store the running state of G2.  The following table lists the set of
;;; possible values for these variables.

;;;   System-is-running  System-has-paused  Meaning
;;;   -----------------  -----------------  -------
;;;   NIL                NIL                G2 is reset (or never started)
;;;   T                  NIL                G2 is running
;;;   NIL                T                  G2 has been paused
;;;   T                  T                  Never happens!

;;; Note that if G2 is paused and then resumed, G2 is then back to the running
;;; state.  These variables are set in functions in the file CYCLES for
;;; starting, pausing, and resetting G2.

(def-system-variable system-is-running schedule nil)

(def-system-variable system-has-paused schedule nil)

(def-concept reset)

(def-concept running)

(def-concept paused)

;;; GENSYMCID-1226: Create G2 abort flag that is publicly accessible.
(def-system-variable system-has-aborted schedule nil)

;;; `abort' is a special type of `paused', it only exists after internal errors.
(def-concept abort)

;;; The function `current-g2-run-state' returns one of the symbols reset,
;;; running, or paused based on the values of system-is-running and
;;; system-has-paused.

(defun current-g2-run-state ()
  (cond (system-has-aborted 'abort)
	(system-is-running 'running)
	(system-has-paused 'paused)
	(t 'reset)))


;;; SymScale notes: below three variables must be thread-specific and specially bound
;;; by each G2 scheduler worker.  -- Chun Tian (binghe), 2009/10/12

;;; The system variable `current-schedule-task' holds either NIL or the
;;; currently executing schedule-task structure.  This variable is used
;;; internally to the scheduler and should not be used outside this module.  The
;;; main use of the variable to be able to reclaim a task if a non-local exit
;;; kicks us out of the execution of the current task and to determine if a
;;; currently executing task was reclaimed.

(def-system-variable current-schedule-task schedule nil)




;;; The system variable `priority-of-current-task' holds the fixnum representing
;;; the priority of the task currently executing.  When we are not in the scope
;;; of a current task, this will hold -1, which is higher than any existing
;;; priority.

(def-system-variable priority-of-current-task CLOCKS -1)




;;; The system variable `priority-of-next-task' holds the fixnum representing
;;; the priority of the next task to be executed from the current task queues.
;;; Note that there may be immediate tasks will occur before this "next task",
;;; but immediate tasks are considered to be cleanup parts of the current task.

(def-system-variable priority-of-next-task CLOCKS most-positive-fixnum)







;;;; Future Task Queue Management Functions




;;; The following section implements functions that manage the set of future
;;; task queues.





;;; The variable `future-task-queue-marker' holds the value used to mark
;;; task-queues as being one of the queues of future tasks.

(defconstant future-task-queue-marker '(future-task-queue-marker))


;;; The function `get-or-create-future-task-queue-for-task' takes a schedule
;;; task and looks up the future task queue for this task and returns it.  If
;;; none exists, a new queue is made and returned.

(def-substitution-macro future-task-< (node task-time priority)
  (let ((node-time (managed-float-value (future-task-queue-time node)))
	(node-priority (future-task-queue-priority node)))
    (cond ((<e node-time task-time)
	   t)
	  ((=e node-time task-time)
	   (lower-priority-p node-priority priority))
	  (t
	   nil))))

(def-substitution-macro future-task-equal (node task-time priority)
  (let ((node-time (managed-float-value (future-task-queue-time node)))
	(node-priority (future-task-queue-priority node)))
    (and (=e node-time task-time)
	 (equal-priority-p node-priority priority))))

#+(and skip-list SymScale)
(defun future-task-queue-find (queue-holder task-time priority preds succs)
  (let ((bottom-level 0)
        marked snip
        pred curr succ)
    (tagbody retry
      (loop
        (setq pred queue-holder)
        (loop for level from future-task-queue-max-level downto bottom-level do
          (setq curr (future-task-queue-next-queue-n pred level))
          (loop
            (multiple-value-setq (succ marked)
              (get-atomic-reference (svref (future-task-queue-next-queue curr) level)))
            (loop while marked do
              (setq snip (compare-and-swap (svref (future-task-queue-next-queue pred) level)
                                           (make-atomic-reference curr)
                                           (make-atomic-reference succ)))
              (unless snip (go retry))
              (setq curr (future-task-queue-next-queue-n pred level))
              (multiple-value-setq (succ marked)
                (get-atomic-reference (svref (future-task-queue-next-queue curr) level))))
            (if (future-task-< curr task-time priority)
                (setq pred curr
                      curr succ)
              (return)))
          (setf (svref preds level) pred
                (svref succs level) curr))
        (return-from future-task-queue-find
          (when (future-task-equal curr task-time priority)
            curr)))))) ; return current node

#+(and skip-list (not SymScale))
(defun-simple future-task-queue-find (queue-holder task-time priority preds succs)
  (declare (type gensym-float task-time))
  (let ((bottom-level 0)
	(pred queue-holder)
	curr)
    (loop for level from future-task-queue-max-level downto bottom-level do
      (setq curr (future-task-queue-next-queue-n queue-holder level))
      (loop (if (future-task-< curr task-time priority)
		(setq pred curr
		      curr (future-task-queue-next-queue-n curr level))
	      (return)))
      (setf (svref preds level) pred
	    (svref succs level) curr))
    (when (future-task-equal curr task-time priority)
      curr)))

#+(and skip-list (not SymScale))
(defun-simple get-or-create-future-task-queue-for-task (schedule-task)
  (with-temporary-gensym-float-creation get-or-create-future-task-queue-for-task
    (let* ((priority (schedule-task-priority schedule-task))
	   (task-time (schedule-task-time schedule-task))
	   (g2-running-task? (schedule-task-g2-running-p schedule-task))
	   (future-holder (if g2-running-task?
			      future-g2-time-tasks
			   future-real-time-tasks))
	   (head (car-of-cons future-holder))
	   (preds skip-list-find-preds)
	   (succs skip-list-find-succs)
	   (bottom-level 0))
      (declare (type gensym-float task-time))
      (let ((queue-holder (future-task-queue-find head task-time priority preds succs)))
	(if queue-holder
	    (future-task-queue-constant-queue queue-holder)
	  (let* ((top-level (random-level future-task-queue-max-level))
		 (new-holder (make-future-task-queue-holder
			       task-time priority top-level)))
	    (loop for level from bottom-level to top-level do
	      (setf (svref (future-task-queue-next-queue new-holder) level)
		    (svref succs level)))
	    (loop for level from bottom-level to top-level
		  for pred = (svref preds level)
		  do
	      (setf (svref (future-task-queue-next-queue pred) level) new-holder))
	    (future-task-queue-constant-queue new-holder)))))))

#+(and skip-list SymScale)
(defun-simple get-or-create-future-task-queue-for-task (schedule-task)
  (with-temporary-gensym-float-creation get-or-create-future-task-queue-for-task
    (let* ((priority (schedule-task-priority schedule-task))
	   (task-time (schedule-task-time schedule-task))
	   (g2-running-task? (schedule-task-g2-running-p schedule-task))
	   (future-holder (if g2-running-task?
			      future-g2-time-tasks
			   future-real-time-tasks))
	   (head (car-of-cons future-holder))
	   (preds skip-list-find-preds)
	   (succs skip-list-find-succs)
	   (bottom-level 0))
      (declare (type gensym-float task-time))
      (loop as queue-holder = (future-task-queue-find head task-time priority preds succs)
	    do
	(if queue-holder
	    (return-from get-or-create-future-task-queue-for-task
	      (future-task-queue-constant-queue queue-holder))
	  (let* ((top-level (random-level future-task-queue-max-level))
		 (new-holder (make-future-task-queue-holder
			       task-time priority top-level)))
	    (loop for level from bottom-level to top-level do
	      (setf (svref (future-task-queue-next-queue new-holder) level)
		    (make-atomic-reference (svref succs level))))
	    (let ((pred (svref preds bottom-level))
		  (succ (svref succs bottom-level)))
	      (when (compare-and-swap (svref (future-task-queue-next-queue pred) bottom-level)
				      (make-atomic-reference succ)
				      (make-atomic-reference new-holder))
		(loop for level from (1+f bottom-level) to top-level do
		  (loop
		    (setq pred (svref preds level)
			  succ (svref succs level))
		    (when (compare-and-swap (svref (future-task-queue-next-queue pred) level)
					    (make-atomic-reference succ)
					    (make-atomic-reference new-holder))
		      (return nil))
		    (future-task-queue-find head task-time priority preds succs)))
		(return-from get-or-create-future-task-queue-for-task
		  (future-task-queue-constant-queue new-holder))))))))))

#-skip-list
(defun-simple get-or-create-future-task-queue-for-task (schedule-task)
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (with-temporary-gensym-float-creation get-or-create-future-task-queue-for-task
    (let ((priority (schedule-task-priority schedule-task))
	  (task-time (schedule-task-time schedule-task))
	  (g2-running-task? (schedule-task-g2-running-p schedule-task)))
      (declare (type gensym-float task-time))
      (loop for holder-trailer = (if g2-running-task?
				     future-g2-time-tasks
				     future-real-time-tasks)
			    then queue-holder
	    for queue-holder = (future-task-queue-next-queue holder-trailer)
			  then (future-task-queue-next-queue queue-holder)
	    do
	(if queue-holder
	    (let ((holder-task-time (managed-float-value
				      (future-task-queue-time queue-holder)))
		  (holder-priority (future-task-queue-priority queue-holder))
		  (insert-new? nil))
	      (declare (type gensym-float holder-task-time))
	      (unless (<e holder-task-time task-time)
		(if (=e task-time holder-task-time)
		    (cond ((equal-priority-p holder-priority priority)
			   (return (future-task-queue-constant-queue
				     queue-holder)))
			  ((lower-priority-p priority holder-priority)
			   (setq insert-new? t)))
		    (setq insert-new? t))
		(when insert-new?
		  (let ((new-holder (make-future-task-queue-holder
				      task-time priority)))
		    (setf (future-task-queue-next-queue new-holder) queue-holder)
		    (setf (future-task-queue-next-queue holder-trailer) new-holder)
		    (return (future-task-queue-constant-queue new-holder))))))
	    (let ((new-holder (make-future-task-queue-holder
				task-time priority)))
	      (setf (future-task-queue-next-queue new-holder) nil)
	      (setf (future-task-queue-next-queue holder-trailer) new-holder)
	      (return (future-task-queue-constant-queue new-holder)))))))))


;;; The function `delete-future-task-queue-for-task' takes a schedule task and
;;; deletes the future task queue that holds tasks with the same priority and
;;; task-time.  It is an error if no such task queue exists.

#+(and skip-list (not SymScale))
(defun-void delete-future-task-queue-for-task (schedule-task)
  (with-temporary-gensym-float-creation delete-future-task-queue-for-task
    (let* ((priority (schedule-task-priority schedule-task))
	   (task-time (schedule-task-time schedule-task))
	   (g2-running-task? (schedule-task-g2-running-p schedule-task))
	   (future-holder (if g2-running-task?
			      future-g2-time-tasks
			   future-real-time-tasks))
	   (head (car-of-cons future-holder))
	   (preds skip-list-find-preds)
	   (succs skip-list-find-succs)
	   (bottom-level 0))
      (declare (type gensym-float task-time))
      (let ((queue-holder (future-task-queue-find head task-time priority preds succs)))
	(when (null queue-holder)
	  #+development
	  (format t "~%No queue to be deleted, JRA help me (1)!")
	  (return-from delete-future-task-queue-for-task))
	(loop for level from (future-task-queue-top-level queue-holder)
		        downto bottom-level
	      for pred = (svref preds level)
	      do
	  (when (eq (future-task-queue-next-queue-n pred level) queue-holder)
	    (setf (svref (future-task-queue-next-queue pred) level)
		  (future-task-queue-next-queue-n queue-holder level))))
	(reclaim-future-task-queue-holder queue-holder)
	nil))))

#+(and skip-list SymScale)
(defun-void delete-future-task-queue-for-task (schedule-task)
  (with-temporary-gensym-float-creation delete-future-task-queue-for-task
    (let* ((priority (schedule-task-priority schedule-task))
	   (task-time (schedule-task-time schedule-task))
	   (g2-running-task? (schedule-task-g2-running-p schedule-task))
	   (future-holder (if g2-running-task?
			      future-g2-time-tasks
			    future-real-time-tasks)))
      (delete-future-task-queue-for-task-inner future-holder task-time priority))))

#+(and skip-list SymScale)
(defun-simple delete-future-task-queue-for-task-inner (future-holder task-time priority)
  (declare (type gensym-float task-time))
  (let* ((head (car-of-cons future-holder))
	 (preds skip-list-find-preds)
	 (succs skip-list-find-succs)
	 (bottom-level 0))
    (loop as queue-holder = (future-task-queue-find head task-time priority preds succs)
	  do
      (when (null queue-holder)
	(return-from delete-future-task-queue-for-task-inner nil))

      (let ((node-to-remove (svref succs bottom-level))
	    succ marked)
	(loop for level from (future-task-queue-top-level node-to-remove)
			downto (1+f bottom-level)
	      do
	  (multiple-value-setq (succ marked)
	    (get-atomic-reference (svref (future-task-queue-next-queue node-to-remove) level)))
	  (loop while (not marked) do
	    (compare-and-swap (svref (future-task-queue-next-queue node-to-remove) level)
			      (make-atomic-reference succ nil)
			      (make-atomic-reference succ t))
	    (multiple-value-setq (succ marked)
	      (get-atomic-reference
		(svref (future-task-queue-next-queue node-to-remove) level)))))
	(multiple-value-setq (succ marked)
	  (get-atomic-reference
	    (svref (future-task-queue-next-queue node-to-remove) bottom-level)))
	(loop as i-marked-it =
	      (compare-and-swap (svref (future-task-queue-next-queue node-to-remove) bottom-level)
				(make-atomic-reference succ nil)
				(make-atomic-reference succ t))
	      do
	   (multiple-value-setq (succ marked)
	     (get-atomic-reference (svref (future-task-queue-next-queue (svref succs bottom-level))
					  bottom-level)))
	   (cond (i-marked-it
		  (future-task-queue-find head task-time priority preds succs)
		  (return-from delete-future-task-queue-for-task-inner t))
		 (marked
		  ;; other threads has removed it first
		  (return-from delete-future-task-queue-for-task-inner nil))))))))

#-skip-list
(defun-void delete-future-task-queue-for-task (schedule-task)
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (with-temporary-gensym-float-creation delete-future-task-queue-for-task
    (let ((priority (schedule-task-priority schedule-task))
	  (task-time (schedule-task-time schedule-task))
	  (g2-running-task? (schedule-task-g2-running-p schedule-task)))
      (declare (type gensym-float task-time))
      (loop named find-queue
	    for holder-trailer = (if g2-running-task?
				     future-g2-time-tasks
				     future-real-time-tasks)
			    then queue-holder
	    for queue-holder = (future-task-queue-next-queue holder-trailer)
			  then (future-task-queue-next-queue queue-holder)
	    while queue-holder
	    do
	;; when both time & priority matched!
	(when (and (equal-priority-p priority (future-task-queue-priority queue-holder))
		   (=e task-time
		       (managed-float-value
			 (future-task-queue-time queue-holder))))
	  (setf (future-task-queue-next-queue holder-trailer)
		(future-task-queue-next-queue queue-holder))
	  (reclaim-future-task-queue-holder queue-holder)
	  (return-from find-queue nil))
	    #+development finally
	      #+development (format t "~%No queue to be deleted, JRA help me (3)!"))))))




;;; The macro `future-tasks-exist-p' takes a future-task-queue and is used to
;;; determine if there are any tasks scheduled to occur in that queue.

#-skip-list
(defmacro future-tasks-exist-p (future-task-queue-set)
  `(future-task-queue-next-queue ,future-task-queue-set))

#+skip-list
(defmacro future-tasks-exist-p (future-task-queue-set)
  (let ((next-queue (make-symbol "NEXT-QUEUE")))
    `(let ((,next-queue (future-task-queue-next-queue-0 (car ,future-task-queue-set))))
       (if (eq ,next-queue (cdr ,future-task-queue-set))
	   nil
	 ,next-queue))))
     



;;; The macro `unix-time-of-next-future-task' will return the gensym-float
;;; representing the unix-time of the next future task scheduled to run in the
;;; given future-task-queue set.  Note that this macro should only be called if
;;; there are future tasks, as verified by future-tasks-exist-p.

(defmacro unix-time-of-next-future-task (future-task-queue-set)
  `(managed-float-value (future-task-queue-time ,future-task-queue-set)))




;;; The modify macro `unpack-one-future-task-queue' takes a location containing
;;; a future task queue set that holds at least one task queue.  It will take
;;; the first queue from that set, merge it into the current task queues at the
;;; appropriate priority, and the store the modified future task queue set back
;;; into the given location.  This operation is internal to the scheduler.

#+(and skip-list (not SymScale))
(defmacro unpack-one-future-task-queue (future-queue)
  (let ((queue-holder (make-symbol "QUEUE-HOLDER"))
	(next-queue-holder (make-symbol "NEXT-QUEUE-HOLDER"))
	(priority (make-symbol "PRIORITY"))
	(head (make-symbol "HEAD")))
    `(let* ((,head (car-of-cons ,future-queue))
	    (,queue-holder (future-task-queue-next-queue-0 ,head))
	    (,next-queue-holder (future-task-queue-next-queue-0 ,queue-holder))
	    (,priority (future-task-queue-priority ,queue-holder)))
       (merge-constant-queues
	 (svref current-task-queue-vector ,priority)
	 (future-task-queue-constant-queue ,queue-holder))
       (when (higher-priority-p ,priority priority-of-next-task)
	 (setq priority-of-next-task ,priority))
       ;; delete first node in skip-list
       (loop for level from (future-task-queue-top-level ,queue-holder) downto 0
	     do
	 (setf (svref (future-task-queue-next-queue ,head) level)
	       (future-task-queue-next-queue-n ,queue-holder level)))
       (reclaim-future-task-queue-holder ,queue-holder)
       nil)))

;;; `merge-constant-queues' is only used for schedule-tasks, so it's moved here.

#+Lockfree-Deque
(defun merge-constant-queues (queue-to-fill queue-to-empty)
  (loop until (constant-queue-empty-p queue-to-empty)
        for element = (constant-queue-dequeue queue-to-empty)
        do
    #+schedule-task-has-a-queue
    (setf (schedule-task-queue element) queue-to-fill)
    (constant-queue-enqueue queue-to-fill element))
  nil)

#+(and skip-list SymScale)
(defun-simple unpack-one-future-task-queue (future-queue)
  (let* ((head (car-of-cons future-queue))
	 (tail (cdr-of-cons future-queue))
	 (marked nil)
	 (level 0)
	 (curr (future-task-queue-next-queue-n head level))
	 (succ nil))

    ;; Part 1: find the first unmarked node
    (multiple-value-setq (succ marked) ; NOTE: marked is the flag of `curr'
      (get-atomic-reference (svref (future-task-queue-next-queue curr) level)))
    (loop while marked do
      (setq curr (future-task-queue-next-queue-n curr level))
      (multiple-value-setq (succ marked)
	(get-atomic-reference (svref (future-task-queue-next-queue curr) level))))
    succ
    ;; Part 2: merge constant queues
    (let* ((queue-holder curr)
	   (priority (future-task-queue-priority queue-holder)))
      (when (eq queue-holder tail)
	(return-from unpack-one-future-task-queue))
      (merge-constant-queues
	(svref current-task-queue-vector priority)
	(future-task-queue-constant-queue queue-holder))
      (when (higher-priority-p priority priority-of-next-task)
	(setq priority-of-next-task priority))

      ;; Part 3: delete current node
      (let* ((task-time (managed-float-value (future-task-queue-time queue-holder))))
	(delete-future-task-queue-for-task-inner future-queue task-time priority))))
  nil)

#-skip-list
(defmacro unpack-one-future-task-queue (future-queue)
  (let ((queue-holder (make-symbol "QUEUE-HOLDER"))
	(next-queue-holder (make-symbol "NEXT-QUEUE-HOLDER"))
	(priority (make-symbol "PRIORITY")))
    `(#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
      (let* ((,queue-holder (future-task-queue-next-queue ,future-queue))
	     (,next-queue-holder
	       (and ,queue-holder
		    (future-task-queue-next-queue ,queue-holder)))
	     (,priority (future-task-queue-priority ,queue-holder)))
       (merge-constant-queues
	 (svref current-task-queue-vector ,priority)
	 (future-task-queue-constant-queue ,queue-holder))
       (reclaim-future-task-queue-holder ,queue-holder)
       (when (higher-priority-p ,priority priority-of-next-task)
	 (setq priority-of-next-task ,priority))
       (setf (future-task-queue-next-queue ,future-queue)
	     ,next-queue-holder)))))




;;; The modify macro `unpack-future-task-queues' takes a location holding a
;;; future task queue set, and it takes a gensym-float representing UNIX time
;;; stamp of the current dequeuing time, i.e. the latest time stamp for a task
;;; that is currently eligible to execute.  This macro will merge all task
;;; queues containing eligible tasks into the current task queues and then
;;; modify the given location with the remaining task queues from the given
;;; future task queue set.  This operation is internal to the scheduler.

#+development
(defun unpack-future-task-queues (future-task-queue-set unix-time-float)
  (let ((future-queue future-task-queue-set)
	(latest-dequeue-time unix-time-float))
    (declare (type gensym-float latest-dequeue-time))
    ;; future-tasks-exist-p may not be atomically, so after even it's true,
    ;; there're still additional checks in `unpack-one-future-task-queue`.
    (loop for next-future-task? = (future-tasks-exist-p future-queue)
	  while (and next-future-task?
		     (<=e (unix-time-of-next-future-task next-future-task?)
			  latest-dequeue-time))
	  do
      (unpack-one-future-task-queue future-queue))
    future-queue)) ; return value is not useful any more.

#-development
(defmacro unpack-future-task-queues (future-task-queue-set unix-time-float)
  (let ((future-queue (make-symbol "FUTURE-QUEUE"))
	(latest-dequeue-time (make-symbol "LATEST-DEQUEUE-TIME"))
	(next-future-task? (make-symbol "NEXT-FUTURE-TASK")))
    `(let ((,future-queue ,future-task-queue-set)
	   (,latest-dequeue-time ,unix-time-float))
       (declare (type ,(gensym-float-type) ,latest-dequeue-time))
       ;; future-tasks-exist-p may not be atomically, so after even it's true,
       ;; there're still additional checks in `unpack-one-future-task-queue`.
       (loop for ,next-future-task? = (future-tasks-exist-p ,future-queue)
	     while (and ,next-future-task?
			(<=e (unix-time-of-next-future-task ,next-future-task?)
			     ,latest-dequeue-time))
	     do
	 (unpack-one-future-task-queue ,future-queue))
       ,future-queue))) ; return value is not useful any more.

;; Lock the tasks queue arg when doing the unpack work

(defmacro determine-scheduler-mode-for-current-system ()
  `(current-system-case
    (ab
      (scheduler-mode-function timing-parameters))
    (t
      (quote real-time))))

(defmacro determine-minimum-scheduling-interval-for-current-system ()
  `(current-system-case
    (ab 
      (minimum-scheduling-interval-function timing-parameters))
    (t nil)))


;;; The function `unpack-future-tasks-into-current-task-queues' takes a
;;; managed-float and will move all tasks scheduled at or before that time into
;;; the current task queues.

(defun-void unpack-future-tasks-into-current-task-queues (g2-clock-ticked?)
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (with-temporary-gensym-float-creation unpack-future-tasks
    (let ((real-time (managed-float-value (clock-get current-real-time)))
	  (g2-time (managed-float-value (clock-get current-g2-time)))
	  (g2-running? system-is-running)
	  (scheduler-mode (determine-scheduler-mode-for-current-system)))
      (declare (type gensym-float real-time g2-time))
      (cond
	((or (not g2-running?)
	     (not g2-clock-ticked?))
	 (unpack-future-task-queues future-real-time-tasks real-time))
	((not (eq scheduler-mode 'real-time))
	 (unpack-future-task-queues future-real-time-tasks real-time)
	 (unpack-future-task-queues future-g2-time-tasks g2-time))
	;; Down here the clock has ticked, we are running, and the scheduler is
	;; in real-time mode.  In this mode, we will unpack the real-time and
	;; g2-time future queues keeping the relative ordering between them.
	(t ; real-time mode?
	 (let* ((future-real-time-tasks?
		  (future-tasks-exist-p future-real-time-tasks))
		(next-real-task-time
		  (if future-real-time-tasks?
		      (unix-time-of-next-future-task future-real-time-tasks?)
		      0d0))
		(future-g2-time-tasks?
		  (future-tasks-exist-p future-g2-time-tasks))
		(next-g2-task-time
		  (if future-g2-time-tasks?
		      (unix-time-of-next-future-task future-g2-time-tasks?)
		      0d0)))
	   (declare (type gensym-float next-real-task-time next-g2-task-time))
	   (loop while (and future-g2-time-tasks?
			    future-real-time-tasks?
			    (<=e next-g2-task-time g2-time)
			    (<=e next-real-task-time real-time))
		 do
	     (cond ((<e next-g2-task-time next-real-task-time)
		    (unpack-one-future-task-queue future-g2-time-tasks)
		    (setq future-g2-time-tasks?
			  (future-tasks-exist-p future-g2-time-tasks))
		    (when future-g2-time-tasks?
		      (setq next-g2-task-time
			    (unix-time-of-next-future-task future-g2-time-tasks?))))
		   (t
		    (unpack-one-future-task-queue future-real-time-tasks)
		    (setq future-real-time-tasks?
			  (future-tasks-exist-p future-real-time-tasks))
		    (when future-real-time-tasks?
		      (setq next-real-task-time
			    (unix-time-of-next-future-task future-real-time-tasks?))))))
	   (unpack-future-task-queues future-real-time-tasks real-time)
	   (unpack-future-task-queues future-g2-time-tasks g2-time))))))))






;;;; Deferred Task Queue Management Functions




;;; The function `defer-current-g2-running-tasks' should be called when G2 is
;;; being paused.  This function will defer tasks in the current task queues so
;;; that non-running tasks can continue to run.  When G2 is resumed, the
;;; function requeue-deferred-running-tasks should be called.

(defun-void defer-current-g2-running-tasks ()
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (loop for priority fixnum from highest-system-priority
		     to lowest-system-priority
	for current-task-queue = (svref current-task-queue-vector priority)
	for deferred-task-queue = (svref deferred-task-queue-vector priority)
	do
    (unless (constant-queue-empty-p current-task-queue)
      #-Lockfree-Deque
      (loop for schedule-task being each constant-queue-element of current-task-queue
	    do
	(when (schedule-task-g2-running-p schedule-task)
	  #+schedule-task-has-a-queue
	  (setf (schedule-task-queue schedule-task) deferred-task-queue)
	  (let ((queue-element (schedule-task-queue-element schedule-task)))
	    (requeue-queue-element deferred-task-queue queue-element))))
      ;; Here we cannot use LOOP path, because this is not a read-only situation:
      ;; the call of `requeue-queue-element' will remove elements from current-
      ;; task-queue, this broken the LOOP.
      #+Lockfree-Deque
      (loop with head = (constant-queue-head current-task-queue)
	    for queue-element = (constant-queue-next head current-task-queue)
	      then next-queue-element
	    until (null queue-element)
	    for next-queue-element = (constant-queue-next queue-element current-task-queue)
	    for schedule-task = (queue-datum queue-element)
	    do
	(when (schedule-task-g2-running-p schedule-task)
	  #+schedule-task-has-a-queue
	  (setf (schedule-task-queue schedule-task) deferred-task-queue)
	  #+development
	  (unless (eq (schedule-task-queue-element schedule-task)
		      queue-element)
	    (error "schedule-task-queue-element is different with holding queue?!"))
	  (requeue-queue-element deferred-task-queue
				 queue-element
				 current-task-queue)))))))




;;; The function `requeue-deferred-running-tasks' should be called when G2 is
;;; being resumed.  This function will remove tasks previously placed into the
;;; deferred queues by defer-current-g2-running-tasks, and place them onto the
;;; end of the current task queues.

(defun-void requeue-deferred-running-tasks ()
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (loop for priority fixnum from highest-system-priority
		     to lowest-system-priority
	for current-task-queue = (svref current-task-queue-vector priority)
	for deferred-task-queue = (svref deferred-task-queue-vector priority)
	do
    (unless (constant-queue-empty-p deferred-task-queue)
      (merge-constant-queues current-task-queue deferred-task-queue)
      (when (higher-priority-p priority priority-of-next-task)
	(setq priority-of-next-task priority))))))






;;;; Initializing and Clearing the Schedule

;;; The variable `scheduler-has-been-initialized-p' can be used to
;;; determine if initialize-scheduler has ever been called in this
;;; process.

(def-system-variable scheduler-has-been-initialized-p schedule nil)


;;; The functions in this section initialize and reset the scheduler.

;;; The function `initialize-scheduler' takes no arguments and is used to
;;; initialize the data structures for the scheduler.  It should be called once
;;; and only once when G2 is launched, and before any tasks have been scheduled.
;;; This function assumes that it is not within a temporary consing area.

(defun-void initialize-scheduler ()
  #-SymScale
  (setq immediate-task-queue (make-empty-constant-queue))
  #+SymScale
  (progn
    (setq immediate-task-queue-vector (make-thread-array nil))
    (loop for i from 0 below number-of-all-threads do
      (setf (svref immediate-task-queue-vector i) (make-empty-constant-queue)))
    ;; before deciding if we're in legacy mode, this must be set first as usual.
    (setq immediate-task-queue (svref immediate-task-queue-vector 0)))

  ;; This code assumes that the highest-system-priority is 0.
  (let ((number-of-priorities
	  (1+f (-f lowest-system-priority highest-system-priority))))
    (loop with new-vector = (make-array number-of-priorities)
	  for index from highest-system-priority to lowest-system-priority do
      (setf (svref new-vector index) (make-empty-constant-queue))
	  finally
	    (setq current-task-queue-vector new-vector))
    (setq priority-of-next-task lower-than-any-priority)
    (loop with new-vector = (make-array number-of-priorities)
	  for index from highest-system-priority to lowest-system-priority do
      (setf (svref new-vector index) (make-empty-constant-queue))
	  finally
	    (setq deferred-task-queue-vector new-vector))
    (setq future-real-time-tasks #+skip-list (make-future-task-priority-queue)
				 #-skip-list (make-future-task-queue-holder 0.0d0 -1))
    (setq future-g2-time-tasks   #+skip-list (make-future-task-priority-queue)
				 #-skip-list (make-future-task-queue-holder 0.0d0 -1))
    (atomic-exchange scheduler-has-been-initialized-p t)))




;;; The function `cancel-g2-running-tasks' will traverse the schedule
;;; task-queues and cancel all tasks that are tied to G2 running.  Note that in
;;; an ideal world, all such tasks would have already been canceled by the
;;; deactivation of items.

(defun-void cancel-g2-running-tasks ()
  (error "Cancel-g2-running-tasks not implementented yet.  -jra 2/20/94"))




;;; The substitution macro `cancel-schedule-task-possibly-reclaiming-queue'
;;; takes a schedule task and deletes the queue element of this task if any from
;;; its constant-queue.  If the remaining queue is one of the future task queues
;;; and is empty, then this macro will also delete that queue from the set of
;;; future queues.  Note that this is an internal operation of the scheduler
;;; which should be accessed through cancel-task or the task rescheduling
;;; operations.

(defun-substitution-macro cancel-schedule-task-possibly-reclaiming-queue
    (schedule-task)
  (when (schedule-task-queue-element schedule-task)
    (cancel-and-reclaim-scheduled-queue-element-1 schedule-task)))

;;; directly remove the task from its queue with knowing the queue.

(defun-void cancel-and-reclaim-scheduled-queue-element-1
    (schedule-task)
  (let ((queue-element (schedule-task-queue-element schedule-task))
	#+schedule-task-has-a-queue
	(queue (schedule-task-queue schedule-task)))
    (when queue-element
      #+(and development schedule-task-has-a-queue)
      (unless queue
        (error "queue-element is T but queue is NIL?!"))
      (setf (schedule-task-queue-element schedule-task) nil)
      #+schedule-task-has-a-queue
      (setf (schedule-task-queue schedule-task) nil)
      (let ((next-queue-element #-SymScale (queue-next-element queue-element)
				#+SymScale
				(queue-next-element-real queue-element))
	    #+SymScale
	    (previous-queue-element (queue-previous-element-real queue-element)))
	#+schedule-task-has-a-queue
	(constant-queue-delete queue-element queue)
	#-schedule-task-has-a-queue
	(delete-queue-element queue-element)
	(when #-SymScale
	      (and (eq (queue-datum next-queue-element)
		       future-task-queue-marker)
		   ;; if above EQ is true, then next-queue-element is a constant-queue
		   ;; head, then we check if there're other elements in the queue:
		   (null (constant-queue-peek next-queue-element)))
	      #+SymScale
	      (and (eq (queue-datum next-queue-element)
		       constant-queue-tail-marker)
		   (eq (queue-datum previous-queue-element)
		       constant-queue-head-marker))
	  (delete-future-task-queue-for-task schedule-task))))))


;;;; Computing Task Times




;;; The macro `next-tick-at-or-before-time' is used to compute an appropriate
;;; new clock value at or before a given UNIX time.  This macro takes a UNIX
;;; time, a minimum-scheduling-interval? as a fixnum of milliseconds or NIL, and
;;; a gensym-float which represents the minimum scheduling interval in seconds
;;; if the previous argument is non-NIL.  This macro returns a gensym-float of
;;; the appropriate value.  Similarly, the macro `next-tick-at-or-after-time' is
;;; used to compute an approprite new clock value at or after a given unix time.
;;; This macro is used when ticking the fast-time clocks.

(defmacro next-tick-at-or-before-time
    (unix-time minimum-scheduling-interval? float-scheduling-interval)
  (let* ((time (make-symbol "TIME"))
	 (minimum-in-milliseconds? (make-symbol "MINIMUM-IN-MILLISECONDS"))
	 (minimum-float (make-symbol "MINIMUM-FLOAT")))
    `(let ((,time ,unix-time)
	   (,minimum-in-milliseconds? ,minimum-scheduling-interval?)
	   (,minimum-float ,float-scheduling-interval))
       (declare (type gensym-float ,time ,minimum-float))
       (if ,minimum-in-milliseconds?
	   (if (<f ,minimum-in-milliseconds? 1000)
	       (let ((floored-tick-time (ffloore-first ,time)))
		 (declare (type gensym-float floored-tick-time))
		 (+e floored-tick-time
		     (*e (ffloore-first
			   (/e (+e (-e ,time floored-tick-time) 1.0e-6)
			       ,minimum-float))
			 ,minimum-float)))
	       (*e (ffloore-first (/e ,time ,minimum-float))
		   ,minimum-float))
	   ,time))))

(defmacro next-tick-at-or-after-time
    (unix-time minimum-scheduling-interval? float-scheduling-interval)
  (let ((time (make-symbol "TIME"))
	(minimum-in-milliseconds? (make-symbol "MINIMUM-IN-MILLISECONDS"))
	(minimum-float (make-symbol "MINIMUM-FLOAT")))
    `(let ((,time ,unix-time)
	   (,minimum-in-milliseconds? ,minimum-scheduling-interval?)
	   (,minimum-float ,float-scheduling-interval))
       (declare (type gensym-float ,time ,minimum-float))
       (if ,minimum-in-milliseconds?
	   (if (<f ,minimum-in-milliseconds? 1000)
	       (let ((floored-tick-time (ffloore-first ,time)))
		 (declare (type gensym-float floored-tick-time))
		 (+e floored-tick-time
		     (*e (fceilinge-first
			   (/e (-e (-e ,time floored-tick-time) 1.0e-6)
			       ,minimum-float))
			 ,minimum-float)))
	       (*e (fceilinge-first (/e ,time ,minimum-float))
		   ,minimum-float))
	   ,time))))






;;;; Scheduling Operations




;;; This section of code implements macros for scheduling tasks.  These
;;; operations vary as to whether they place task into the immediate queues, the
;;; current queues, or the future queues, whether the task is repeatedly
;;; executed or executed just once.  There are also specialized macros for
;;; pushing tasks onto the front of the immediate task queue, and for scheduling
;;; one task into a task queue directly after another task.

;;; All of these scheduling functions take a location? argument.  If the
;;; location is anything other than NIL, it is assumed to be a location into
;;; which the newly scheduled task can be placed.  The schedule-task structure
;;; placed in this location then can be used to cancel, reschedule, change the
;;; priority, or check if the task has already been executed.  Note that if you
;;; place a schedule-task into a location, then this structure must be reclaimed
;;; with a call to cancel-task, whether or not the task has executed.  If the
;;; location? argument to a scheduling function is NIL, then the schedule-task
;;; for this task is reclaimed at the time that the task is run.

;;; The modifying macro `with-immediate-scheduling' is used to schedule a task
;;; to occur as soon as the current task has completed.  Tasks scheduled in this
;;; way should be considered part of the currently executing task.  If you
;;; instead wish to reschedule a currently executing task, giving fair sharing
;;; of the CPU to other tasks running at the same priority, use
;;; schedule-current-task.  Note that there is no cyclic scheduling companion
;;; macro to this one.

;;; The location? argument can be NIL or a location to be SETFed with the
;;; schedule-task structure for the newly scheduled task.  The location should
;;; contain a schedule-task or NIL.  If the location currently has a
;;; schedule-task in it, that task will be cancelled and reclaimed before the
;;; next task is scheduled.

;;; The simple-or-void-function is an unevaluated symbol that should name a
;;; simple or void function.  In development this will go through the symbol in
;;; order to allow tracing.  In distribution this will compile into a reference
;;; to the compiled function object.  Please note that the name of this macro
;;; was chosen to get the right auto-fill behavior for our current Lisp editors.
;;; The arguments to the task are evaluated at the time the task is scheduled,
;;; and passed on to the named simple or void function when the task is
;;; executed.

;;; Examples:

;;;  (with-immediate-scheduling ((cleanup-task current-window))
;;;    (cleanup-dirty-windows current-window))

(defmacro with-immediate-scheduling ((&optional location? task-push? argument-reclaimers parallel?)
				     (simple-or-void-function &rest arguments))
  (note-scheduled-function-name simple-or-void-function)
  (let ((function-name `',simple-or-void-function)
	(function `(task-function-for-symbol ,simple-or-void-function))
	(arg `(gensym-list ,@argument-reclaimers)))
    (if location?
	`(immediate-task-schedule-modify ,location? nil
	   ,function-name ,function ,task-push? ,parallel? ,arg ,@arguments)
	`(immediate-task-schedule         nil       t
	   ,function-name ,function ,task-push? ,parallel? ,arg ,@arguments))))

(defmacro with-pushed-immediate-scheduling ((&optional location? argument-reclaimers parallel?)
					    (simple-or-void-function &rest arguments))
  `(with-immediate-scheduling (,location? t ,argument-reclaimers ,parallel?)
     (,simple-or-void-function ,@arguments)))

;;; The macro `immediate-scheduled-task-p' takes a scheduled task that is
;;; scheduled for execution and returns whether or not this task is an immediate
;;; task or a task scheduled at some priority.  By scheduled task I mean that it
;;; has not already been executed but is sitting in the task queues witing for
;;; execution, i.e. the predicate scheduled-task-in-place-p would return true.

(defmacro immediate-scheduled-task-p (scheduled-task)
  `(equal-priority-p (schedule-task-priority ,scheduled-task) higher-than-any-priority))

(define-modify-macro immediate-task-schedule-modify (&rest args)
  ;; in chestnut define-modify-macro is allowed to assume the following is a function.
  immediate-task-schedule)

(defmacro immediate-task-schedule (old-task scheduler-reclaims-p function-name function push-p
				   parallel? argument-reclaimers &rest function-arguments)
  #-SymScale (declare (ignore parallel?))
  (let ((new-task (make-symbol "NEW-TASK")))
    `(#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
       (cancel-task-internal ,old-task)
       (let ((,new-task (make-schedule-task-macro ,scheduler-reclaims-p)))
	 (setf (schedule-task-priority            ,new-task) higher-than-any-priority)
	 (setf (schedule-task-argument-reclaimers ,new-task) ,argument-reclaimers)
         #+SymScale
	 (setf (schedule-task-thread              ,new-task) ,parallel?)
	 (schedule-task-store-function-and-args ,new-task ,function-name ,function
						,@function-arguments)
	 #+schedule-task-has-a-queue
	 (setf (schedule-task-queue ,new-task)
	       (svref immediate-task-queue-vector
		      ,(if parallel? current-thread-index 0)))
	 (setf (schedule-task-queue-element ,new-task)
	       ,(if push-p
		    `(constant-queue-filo-enqueue
		       #-SymScale immediate-task-queue
		       #+SymScale
		       (svref immediate-task-queue-vector
			      ,(if parallel? 'current-thread-index 0)) ,new-task)
		    `(constant-queue-enqueue
		       #-SymScale immediate-task-queue
		       #+SymScale
		       (svref immediate-task-queue-vector
			      ,(if parallel? 'current-thread-index 0)) ,new-task)))
	 ,new-task))))

;;; The modifying macro `with-current-scheduling' enqueues tasks for execution
;;; in the current task queues.  It takes a location?, priority, a
;;; cycle-interval?, an ensure-cycle-anniversaries?, and a real-time-task? flag
;;; set of arguments to control the way a task is scheduled, and it takes in
;;; it's body a form that looks like a function call.  The unevaluated function
;;; symbol should name a simple or void function.  All arguments to the function
;;; form are evaluated at the time the task is scheduled and are stored in the
;;; scheduled task.  When the task is executed the named function will be called
;;; with these arguments.

;;; The priority should be a fixnum from 0 through 11.  The cycle-interval
;;; should be NIL or a gensym-float giving the interval at which this task
;;; should be repeated.  The ensure-cycle-aniversaries? flag controls whether or
;;; not the rescheduling of a cyclic task should occur at the cycle interval
;;; from when the actually ran or from the time that the task was originally
;;; scheduled to run.  The real-time-task? is a flag that says whether or not
;;; this task should be deferred if G2 is not currently running when the task
;;; attempts to execute.

;;; Note that there is a restriction on the location and cycle-interval?
;;; arguments.  If the location is given as any form but NIL, then it will be
;;; SETF'ed into with the schedule-task that represents this task.  If the
;;; cycle-interval? argument is given any form but NIL, then it must evaluate to
;;; a gensym-float giving the interval.  If the given interval is not a positive
;;; value, then this task will not cycle, but will be executed once.

;;; The macro `with-pushed-current-scheduling' is just like
;;; with-current-scheduling, except that the task is pushed onto the front of
;;; the task queue for this priority instead of being added to the end.


(defmacro with-current-scheduling ((location? priority
				    &optional cycle-interval?
					      ensure-cycle-anniversaries?
					      real-time-task?
					      argument-reclaimers
					      parallel?)
				   (simple-or-void-function &rest arguments))
  `(with-current-scheduling-1 (,location?
			       ,priority
			       ,cycle-interval?
			       ,ensure-cycle-anniversaries?
			       ,real-time-task?
			       nil  ; push-p
			       ,parallel?
			       ,argument-reclaimers)
     (,simple-or-void-function ,@arguments)))

(defmacro with-pushed-current-scheduling ((location? priority
					   &optional cycle-interval?
						     ensure-cycle-anniversaries?
						     real-time-task?
						     argument-reclaimers
						     parallel?)
					  (simple-or-void-function &rest arguments))
  `(with-current-scheduling-1 (,location? ,priority
			       ,cycle-interval?
			       ,ensure-cycle-anniversaries?
			       ,real-time-task?
			       t    ; push-p
			       ,parallel?
			       ,argument-reclaimers)
     (,simple-or-void-function ,@arguments)))

#+(and SymScale (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :task-schedule-modify-using-cas *features*))

(defmacro with-current-scheduling-1 ((location? priority
				      &optional interval
						recycle
						real-time
						push-p
						parallel-p
						argument-reclaimers)
				     (simple-or-void-function &rest arguments))
  (note-scheduled-function-name simple-or-void-function)
  (let* ((function-name `',simple-or-void-function)
	 (function   `(task-function-for-symbol ,simple-or-void-function))
	 (ar `(gensym-list ,@argument-reclaimers)))
    `(,(if location?
	   #+task-schedule-modify-using-cas
	   (if (and (consp location?)
		    ;; there's a special location which is not CAS doable. --binghe
		    (eq (car location?) 'gfi-output-scheduled-task))
	       'current-task-schedule-modify-1
	     'current-task-schedule-modify)
	   #-task-schedule-modify-using-cas
	   'current-task-schedule-modify
	   'current-task-schedule)
      ,(if location? location? nil) ; old-task
      ,(if location? nil t)         ; reclaim
      ,priority
      ,interval
      ,recycle
      ,real-time
      ,push-p
      ,function-name
      ,function
      ,parallel-p
      ,ar
      ,@arguments)))

(define-modify-macro #-task-schedule-modify-using-cas current-task-schedule-modify
		     #+task-schedule-modify-using-cas current-task-schedule-modify-1 (&rest args)
		     ;; in chestnut define-modify-macro is allowed to assume the following is a function.
		     current-task-schedule)

#+task-schedule-modify-using-cas
(defmacro current-task-schedule-modify (old-task reclaim-p priority interval cycle-p real-time
					push-p f-name f parallel-p reclaimers &rest args)
  (let* ((old (make-symbol "OLD"))
	 (new (make-symbol "NEW"))
	 (task (make-symbol "TASK"))
	 (g2-p (make-symbol "G2-P"))
	 (ctask (make-symbol "CTASK"))
	 (p (make-symbol "P"))
	 (v (make-symbol "V"))
	 (q (make-symbol "Q")))
    `(loop for ,old = ,old-task
	   for ,new = (let ((,task (make-schedule-task-macro ,reclaim-p)))
			(setf (schedule-task-cycle-interval               ,task) ,(or interval -1.0d0))
			(setf (schedule-task-priority                     ,task) ,priority)
			(setf (schedule-task-ensure-cycle-anniversaries-p ,task) ,cycle-p)
			(setf (schedule-task-argument-reclaimers          ,task) ,reclaimers)
			#+SymScale
			(setf (schedule-task-thread                       ,task) ,parallel-p)
			(let ((,g2-p (not ,real-time)))
			  (setf (schedule-task-g2-running-p ,task) ,g2-p)
			  (setf (schedule-task-time ,task)
				(managed-float-value
				  (if ,g2-p (clock-get current-g2-time) (clock-get current-real-time)))))
			(schedule-task-store-function-and-args ,task ,f-name ,f ,@args)
			,task)
	   doing
       (if (compare-and-swap ,old-task ,old ,new)
	   (let* ((,task ,new)
		  (,ctask (or (not (schedule-task-g2-running-p ,task)) system-is-running))
		  (,p (schedule-task-priority ,task))
		  (,v (if ,ctask current-task-queue-vector deferred-task-queue-vector))
		  (,q (svref ,v ,p)))
	     #+schedule-task-has-a-queue
	     (setf (schedule-task-queue ,task) ,q)
	     (setf (schedule-task-queue-element ,task)
		   (,(if push-p
			 'constant-queue-filo-enqueue
		         'constant-queue-enqueue)
		     ,q
		     ,task))
	     (when (and ,ctask (higher-priority-p ,p priority-of-next-task))
	       (setf priority-of-next-task ,p))
	     (return ,task))
	 (progn
	   #+development
	   (progn
	     (setf (schedule-task-time                         ,new) 0.0d0)
	     (setf (schedule-task-cycle-interval               ,new) 0.0d0)
	     (setf (schedule-task-g2-running-p		       ,new) nil)
	     (setf (schedule-task-priority		       ,new) nil)
	     (setf (schedule-task-ensure-cycle-anniversaries-p ,new) nil)
	     (setf (schedule-task-argument-reclaimers          ,new) nil)
	     (setf (schedule-task-thread                       ,new) nil)
	     (setf (schedule-task-function-name		       ,new) nil)
	     (setf (schedule-task-function		       ,new) nil)
	     (setf (schedule-task-argument-count	       ,new) nil)
	     (setf (schedule-task-arg-1			       ,new) nil)
	     (setf (schedule-task-arg-2			       ,new) nil)
	     (setf (schedule-task-arg-3			       ,new) nil)
	     (setf (schedule-task-arg-4			       ,new) nil))
	   (reclaim-schedule-task-macro ,new))))))

(defmacro current-task-schedule (old-task reclaim-p priority interval cycle-p real-time
				 push-p f-name f parallel-p reclaimers &rest args)
  #-(or SymScale mtg2) (declare (ignore parallel-p))
  (let* ((task  (make-symbol "TASK"))
	 (g2-p  (make-symbol "G2-P"))
	 (ctask (make-symbol "CTASK"))
	 ;; somewhat odd, but simpler than getting macrolet to work.
	 (p (make-symbol "P"))
	 (v (make-symbol "V"))
	 (q (make-symbol "Q")))
    `(#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
       (cancel-task-internal ,old-task)
       (let ((,task (make-schedule-task-macro ,reclaim-p)))
	 (setf (schedule-task-cycle-interval               ,task) ,(or interval -1.0d0))
	 (setf (schedule-task-priority                     ,task) ,priority)
	 (setf (schedule-task-ensure-cycle-anniversaries-p ,task) ,cycle-p)
	 (setf (schedule-task-argument-reclaimers          ,task) ,reclaimers)
	 #+SymScale
	 (setf (schedule-task-thread                       ,task) ,parallel-p)
	 #+mtg2
	 (setf (schedule-task-faction?                     ,task)
	       (if (or (eq ,parallel-p :main-faction)
		       (and (not (symbolp ,parallel-p)) (faction-p ,parallel-p)))
		       ,parallel-p))  ; PARALLEL-Phaction
	 (let ((,g2-p (not ,real-time)))
	   (setf (schedule-task-g2-running-p ,task) ,g2-p)
	   (setf (schedule-task-time ,task)
		 (managed-float-value
		   (if ,g2-p (clock-get current-g2-time) (clock-get current-real-time)))))
	 (schedule-task-store-function-and-args ,task ,f-name ,f ,@args)
	 (let* ((,ctask (or (not (schedule-task-g2-running-p ,task)) system-is-running))
		(,p (schedule-task-priority ,task))
		(,v (if ,ctask current-task-queue-vector deferred-task-queue-vector))
		(,q (svref ,v ,p)))
	   #+schedule-task-has-a-queue
	   (setf (schedule-task-queue ,task) ,q)
	   (setf (schedule-task-queue-element ,task)
		 (,(if push-p
		       'constant-queue-filo-enqueue
		       'constant-queue-enqueue)
		   ,q
		   ,task))
	   (when (and ,ctask (higher-priority-p ,p priority-of-next-task))
	     (setf priority-of-next-task ,p)))
	 ,task))))

;;; The modifying macro `with-future-scheduling' enqueues tasks for execution in
;;; the future task queues, or the current task queue if the given task time has
;;; already passed.  It takes a location?, priority, real-time-task?, a
;;; task-time, a cycle-interval? and an ensure-cycle-anniversaries? set of
;;; argumnts to control the way a task is scheduled, and it takes in it's body a
;;; form that looks like a function call.  The unevaluated function symbol
;;; should name a simple or void function.  All arguments to the function form
;;; are evaluated at the time the task is scheduled and are stored in the
;;; scheduled task.  When the task is executed the named function will be called
;;; with these arguments.

;;; The task-time argument should be a gensym-float representing a time in the
;;; unix-time format.  If the given unix-time isn't later than the
;;; current-g2-time or current-real-time (depending on whether it is a
;;; g2-running-task?), then the given task will be scheduled into the current
;;; task queues.  Task-times may be rounded to a scheduling quantum, given in
;;; hertz in the scheduling-quantum slot of the timing-parameters system-table.
;;; For some system tasks, this rounding may be overridden with the
;;; inhibit-scheduling-quantum? argument.

;;; Note that there is a restriction on the location and cycle-interval?
;;; arguments.  If the location is given as any form but NIL, then it will be
;;; SETF'ed into with the schedule-task that represents this task.  If the
;;; cycle-interval? argument is given any form but NIL, then it must evaluate to
;;; a gensym-float giving the interval.  If the given interval is not a positive
;;; value, then this task will not cycle, but will be executed once.

(defmacro with-future-scheduling
    ((location? priority task-time &optional cycle-interval? ensure-cycle-anniversaries?
      real-time-task? argument-reclaimers parallel?)
     (simple-or-void-function &rest arguments))
  (note-scheduled-function-name simple-or-void-function)
  `(,(if location?
	 #+task-schedule-modify-using-cas
	 (if (and (consp location?)
		  ;; there's a special location which is not CAS doable. --binghe
		  (eq (car location?) 'gfi-output-scheduled-task))
	     'future-task-schedule-modify-1
	   'future-task-schedule-modify)
	 #-task-schedule-modify-using-cas
	 'future-task-schedule-modify
	 'future-task-schedule)
     ,(if location? location? nil) ; old-task
     ,(if location? nil t)         ; reclaim
     ,priority
     ,task-time
     ,cycle-interval?
     ,ensure-cycle-anniversaries?
     ,real-time-task?
     ',simple-or-void-function
     (task-function-for-symbol ,simple-or-void-function)
     ,parallel?
     (gensym-list ,@argument-reclaimers)
     ,@arguments))

(define-modify-macro #-task-schedule-modify-using-cas future-task-schedule-modify
		     #+task-schedule-modify-using-cas future-task-schedule-modify-1 (&rest args)
		     ;; in chestnut define-modify-macro is allowed to assume
		     ;; the following is a function.
		     future-task-schedule)

#+task-schedule-modify-using-cas
(defmacro future-task-schedule-modify (old-task reclaim priority time interval anniversaries
				       real-time f-name f parallel-p reclaimers &rest args)
  (let ((old (make-symbol "OLD"))
	(new (make-symbol "NEW"))
	(task (make-symbol "TASK")))
    `(loop for ,old = ,old-task
	   for ,new = (let ((,task (make-schedule-task-macro ,reclaim)))
			(setf (schedule-task-time                         ,task) ,time)
			(setf (schedule-task-cycle-interval               ,task) ,(or interval -1.0d0))
			(setf (schedule-task-g2-running-p                 ,task) (not ,real-time))
			(setf (schedule-task-priority                     ,task) ,priority)
			(setf (schedule-task-ensure-cycle-anniversaries-p ,task) ,anniversaries)
			(setf (schedule-task-argument-reclaimers          ,task) ,reclaimers)
			(setf (schedule-task-thread                       ,task) ,parallel-p)
			(schedule-task-store-function-and-args ,task ,f-name ,f ,@args)
			,task)
	   doing
       (if (compare-and-swap ,old-task ,old ,new)
	   (progn
	     (cancel-task-internal ,old)
	     (future-task-schedule-2 ,new)
	     (return ,new))
	 (progn
	   #+development
	   (progn
	     (setf (schedule-task-time                         ,new) 0.0d0)
	     (setf (schedule-task-cycle-interval               ,new) 0.0d0)
	     (setf (schedule-task-g2-running-p		       ,new) nil)
	     (setf (schedule-task-priority		       ,new) nil)
	     (setf (schedule-task-ensure-cycle-anniversaries-p ,new) nil)
	     (setf (schedule-task-argument-reclaimers          ,new) nil)
	     (setf (schedule-task-thread                       ,new) nil)
	     (setf (schedule-task-function-name		       ,new) nil)
	     (setf (schedule-task-function		       ,new) nil)
	     (setf (schedule-task-argument-count	       ,new) nil)
	     (setf (schedule-task-arg-1			       ,new) nil)
	     (setf (schedule-task-arg-2			       ,new) nil)
	     (setf (schedule-task-arg-3			       ,new) nil)
	     (setf (schedule-task-arg-4			       ,new) nil))
	   (reclaim-schedule-task-macro ,new))))))

(defmacro future-task-schedule (old-task reclaim priority time interval anniversaries
				real-time f-name f parallel-p reclaimers &rest args)
  #-SymScale (declare (ignore parallel-p))
  (let ((task (make-symbol "TASK")))
    `(progn
       (cancel-task-internal ,old-task)
       (let ((,task (make-schedule-task-macro ,reclaim)))
	 (setf (schedule-task-time                         ,task) ,time)
	 (setf (schedule-task-cycle-interval               ,task) ,(or interval -1.0d0))
	 (setf (schedule-task-g2-running-p                 ,task) (not ,real-time))
	 (setf (schedule-task-priority                     ,task) ,priority)
	 (setf (schedule-task-ensure-cycle-anniversaries-p ,task) ,anniversaries)
	 (setf (schedule-task-argument-reclaimers          ,task) ,reclaimers)
	 #+SymScale
	 (setf (schedule-task-thread                       ,task) ,parallel-p)
	 (schedule-task-store-function-and-args ,task ,f-name ,f ,@args)
	 (future-task-schedule-2 ,task)
	 ,task))))

(defun-void future-task-schedule-2 (schedule-task)
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (with-temporary-gensym-float-creation future-task-schedule-2
    (let ((new-task-time (schedule-task-time schedule-task))
	  (g2-task? (schedule-task-g2-running-p schedule-task)))
      (declare (type gensym-float new-task-time))
      (when g2-task?
	(let ((millisecond-minimum-scheduling-interval? 
		(determine-minimum-scheduling-interval-for-current-system)))
	  (when millisecond-minimum-scheduling-interval?
	    (let ((float-minimum-scheduling-interval
		    (/e (coerce-fixnum-to-gensym-float
			  millisecond-minimum-scheduling-interval?)
			1000.0d0)))
	      (declare (type gensym-float float-minimum-scheduling-interval))
	      (setq new-task-time
		    (next-tick-at-or-after-time
		      new-task-time
		      millisecond-minimum-scheduling-interval?
		      float-minimum-scheduling-interval))
	      (setf (schedule-task-time schedule-task) new-task-time)))))
      (let* ((future-task?
	       (>e new-task-time
		   (managed-float-value
		     (if g2-task? (clock-get current-g2-time) (clock-get current-real-time)))))
	     (current-task? (and (not future-task?)
				 (or (not g2-task?) system-is-running)))
	     (priority (schedule-task-priority schedule-task))
	     (queue (if future-task?
			(get-or-create-future-task-queue-for-task schedule-task)
		      (svref (if current-task?
				 current-task-queue-vector
			       deferred-task-queue-vector)
			     priority))))
	#+schedule-task-has-a-queue
	(setf (schedule-task-queue schedule-task) queue)
	(setf (schedule-task-queue-element schedule-task)
	      (constant-queue-enqueue queue schedule-task))
	(when (and current-task?
		   (higher-priority-p priority priority-of-next-task))
	  (setq priority-of-next-task priority)))))))




;;; The macro `cancel-task' takes a location containing a schedule-task or NIL,
;;; cancels that the task if any, reclaims that task, then stores NIL back into
;;; the location.

#-SymScale
(define-modify-macro cancel-task () cancel-task-internal)

;;; The following atomic version can only work when `item-or-place' has no side
;;; effects. And all LOOKUP-SLOTs used by it has been converted into VECTOR-SLOT
;;; to work with `compare-and-swap'. -- Chun Tian (binghe), Mar 2015.

#+SymScale
(defmacro cancel-task (item-or-place)
  (let ((old-task (gensym)))
    `(loop for ,old-task = ,item-or-place do
       (when (compare-and-swap ,item-or-place ,old-task nil)
	 ;; this make sure the old task can only be reclaimed once.
	 (cancel-task-internal ,old-task)
	 (return t)))))

(defun-substitution-macro cancel-task-internal (schedule-task?)
  (when schedule-task?
    (when (eq schedule-task? current-schedule-task)
      (setq current-schedule-task nil))
    (cancel-schedule-task-possibly-reclaiming-queue schedule-task?)
    (reclaim-schedule-task-macro schedule-task?))
  nil)

(defvar-for-macro scheduled-function-name-list nil)

(defun-for-macro note-scheduled-function-name (name)
  (pushnew name scheduled-function-name-list)
  name)




;;;; Task Execution




;;; This section contains code for executing tasks from the schedule queues.

;;; The macro `dequeue-and-execute-all-immediate-tasks' will empty the immediate
;;; task queue of all enqueued tasks.  It takes one argument, the priority to
;;; simulate while executing these tasks.  Immediate tasks may be seen as a
;;; continuation of the current task queue task that enqueued them, so they
;;; should execute in apparently the same priority as their scheduling task.

(defun-substitution-macro dequeue-and-execute-all-immediate-tasks
    (priority-to-use)
  (let ((local-immediate-queue
	#-SymScale immediate-task-queue
	#+SymScale (svref immediate-task-queue-vector current-thread-index)))
    (loop for immediate-task? =
	 (constant-queue-dequeue local-immediate-queue)
	  while immediate-task? do
      (setf (schedule-task-queue-element immediate-task?) nil)
      #+schedule-task-has-a-queue
      (setf (schedule-task-queue immediate-task?) nil)
      (setq priority-of-current-task priority-to-use)
      #-mtg2
      (progn
	(setq current-schedule-task immediate-task?)
	(let ((reclaim-task?
	       (schedule-task-reclaimable-by-scheduler-p immediate-task?)))
	  (execute-schedule-task immediate-task?)
	  (when (and reclaim-task? (eq immediate-task? current-schedule-task))
	    (reclaim-schedule-task-macro immediate-task?))))
      #+mtg2
      (if (null (schedule-task-faction? immediate-task?))
	  (progn
	    (setq current-schedule-task immediate-task?)
	    (let ((reclaim-task?
		   (schedule-task-reclaimable-by-scheduler-p immediate-task?)))
	      (execute-schedule-task immediate-task?)
	      (when (and reclaim-task? (eq immediate-task? current-schedule-task))
		(reclaim-schedule-task-macro immediate-task?))))
	  (plan-immediate-task (gensym-list immediate-task?) priority-of-current-task)))
    (setq priority-of-current-task higher-than-any-priority)
    (setq current-schedule-task nil)))


;;; The simple function `dequeue-and-execute-next-task' finds and executes the
;;; next runnable task, returning true if a task was found and run, and
;;; returning NIL if no tasks were run.  This function is prepared for scheduled
;;; tasks to complete by performing a non-local exit through this function (such
;;; as a throw to a catch established by a caller), and then be reentered
;;; without leaking any scheduler structures.

;;; This function is implemented as follows.  First it checks if there are any
;;; data structures lying around from a previous scheduled task that still need
;;; to be cleaned up due to a non-local exit.  Next it will attempt to execute
;;; any immediate task queue tasks also left over from a previous non-local
;;; exit.

;;; Next it begins searching the current-task-queue-vector for a current task to
;;; execute.  This search starts at priority-of-next-task, then working towards
;;; the lower priorities.  If no tasks are found, priority-of-next-task is set
;;; to be lower than any priority, and this function returns NIL.  If a task is
;;; found, then it is executed.  After it returns (which it may not due to
;;; non-local exits) then the immediate task queue is checked again and drained
;;; of all tasks.  When done this function returns T.

;;; A note on the reclaimation of schedule-task structures.  When a task is
;;; scheduled, if no location is given for the schedule-task then the slot
;;; schedule-task-is-reclaimable-by-scheduler-p is set to true.  This flag
;;; controls whether or not this function may reclaim a schedule-task after it
;;; has been executed.  This flag must be cached into a local variable before
;;; execution of this function, since for tasks that aren't reclaimable by the
;;; scheduler, they may be cancelled or rescheduled during the execution of a
;;; task.  This may reset this flag on the schedule-task structure, causing this
;;; function to misbehave if the slot is read after the task executes.  So, this
;;; function should cache that value before running the task.

(defun-void dequeue-next-task ()
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
    (loop for priority from #-mtg2 priority-of-next-task
                            #+mtg2 highest-system-priority
                       to lowest-system-priority
          for current-task? = (constant-queue-dequeue
                                (svref current-task-queue-vector priority))
	when current-task?
	  return (progn
		   (setq priority-of-next-task priority)
		   (setq priority-of-current-task priority)
		   (setf (schedule-task-queue-element current-task?) nil)
		   #+schedule-task-has-a-queue
		   (setf (schedule-task-queue current-task?) nil)
		   (setq current-schedule-task current-task?))
	finally (setq priority-of-next-task lower-than-any-priority))))

(defmacro in-main-thread-p ()
  #-SymScale t
  #+SymScale
  `(=f current-thread-index 0))

#+SymScale
(progn
  ;; for communication between main and worker threads
  (defvar-of-special-global scheduler-task nil)
  (defvar-of-special-global scheduler-task-priority)
  (defvar-of-special-global scheduler-task-time 0)
  ;; other variables
  (defvar-of-special-global multicore-p nil)   ; flag set by #w"legacy"
  (defconstant scheduler-worker-loop-interval 1)
  ) ; progn (#+SymScale)

(defun-simple dequeue-and-execute-next-task ()
  ;; Clean up reclaimable schedule tasks that have been left in the
  ;; current-schedule-task variable due to non-local exits from this function.
  ;; In any case, reset current-schedule-task to NIL.
  (when current-schedule-task
    (when (schedule-task-reclaimable-by-scheduler-p current-schedule-task)
      (reclaim-schedule-task current-schedule-task))
    (setq current-schedule-task nil))
  
  ;; Drain the immediate queue of all immediate tasks left here due to a
  ;; non-local exit from this function.
  (dequeue-and-execute-all-immediate-tasks
    (if (system-priority-p priority-of-current-task)
	priority-of-current-task
	highest-system-priority))

  #+development
  (when (and (not system-has-paused)
	     (tasks-deferred-until-resumption?))
    (cerror "Oh, go on anyway"
	    "Deferred tasks exist while G2 is running!  Panic!"))
  
  (maybe-get-network-events)
  (when (eq current-system-name 'ab)
	(mqtt-poll-watcher))
  (dequeue-next-task)
  (when (and (not current-schedule-task)
	     (or (get-pending-network-events)
		 (current-system-case
		   (ab (tick-the-clock nil))
		   (t  (tick-the-clock-for-tw-or-gsi)))))
    (dequeue-next-task))

  (when current-schedule-task
    (let* ((current-task current-schedule-task)
	   (task-function-name (schedule-task-function-name current-task))
	   #+SymScale
	   (task-thread (schedule-task-thread current-task)))
      #-(or SymScale mtg2)
      (execute-task-and-reschedule current-task)
      #+mtg2 (plan-reschedule-task current-task)
      #+SymScale
      (if multicore-p
	  (case task-thread
	    (workstation
	     (execute-task-and-reschedule current-task))
	    ;; A Naive Synchronous Queue (Part I: enqueue), from Chapter 10.6.1 of the
	    ;; book `The Art of Multiprocessor Programming'. The `enqueuing' flag and
	    ;; related code are removed since there's only one enqueuer here.
	    ;;
	    ;; Also see Part II in `scheduler-worker-loop' (at the end of this file).
	    ((t)
	     (tx:with-lock-held (scheduler-event-lock)
	       (setq scheduler-task current-schedule-task)
	       (setq scheduler-task-priority priority-of-current-task)
	       (setq scheduler-task-time time-slice-start-time)
	       (tx:condition-variable-broadcast scheduler-event-ready)
	       (loop while scheduler-task do
	         (tx:condition-variable-wait-with-timeout scheduler-event-ready
							  scheduler-worker-loop-interval))
	       (tx:condition-variable-broadcast scheduler-event-ready)))
	    (t
	     (execute-task-and-reschedule current-task)))
	(execute-task-and-reschedule current-task))
      (setq current-schedule-task nil)

      ;; Next execute any immediate tasks enqueued by the execution of
      ;; the previous current task.
      (dequeue-and-execute-all-immediate-tasks priority-of-current-task)
      (setq priority-of-current-task higher-than-any-priority)

      task-function-name)))

;; This function was separated from above dequeue-and-execute-next-task
(defun-simple execute-task-and-reschedule (current-task)
  (let ((reclaim-task?
	 (schedule-task-reclaimable-by-scheduler-p current-task)))
    ;; time consuming
    (execute-schedule-task current-task)
    (when (eq current-schedule-task current-task)
      (let ((interval (schedule-task-cycle-interval current-task)))
	(declare (type gensym-float interval))
	(when (>e interval 0.0d0)
	  (let* ((g2-running?
		  (schedule-task-g2-running-p current-task))
		 (current-time
		  (if g2-running?
		      (managed-float-value (clock-get current-g2-time))
		      (managed-float-value (clock-get current-real-time))))
		 (old-task-time
		  (schedule-task-time current-task))
		 (new-time (+e interval current-time)))
	    (declare (type gensym-float current-time old-task-time
			   new-time))
	    (when (schedule-task-ensure-cycle-anniversaries-p current-task)
	      (setq new-time (+e old-task-time interval))
	      (when (not (>e new-time current-time))
		(setq new-time
		      (+e old-task-time
			  (*e interval
			      (fceilinge-first
			       (-e current-time old-task-time)
			       interval))))))
	    (setf (schedule-task-time current-task) new-time)
	    (future-task-schedule-2 current-task)
	    (setq current-schedule-task nil)))))
    (when (and reclaim-task?
	       (eq current-task current-schedule-task))
      (reclaim-schedule-task-macro current-task))))

;;; The function `tasks-enqueued-for-current-execution?' is an efficient peep at
;;; the scheduler to see if there are any tasks which it would perform if you
;;; called dequeue-and-execute-next-task.

(defun-simple tasks-enqueued-for-current-execution? ()
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (or #-SymScale (not (constant-queue-empty-p immediate-task-queue))
      #+SymScale
      (not (constant-queue-empty-p
	     (svref immediate-task-queue-vector current-thread-index)))

      (loop for priority from highest-system-priority to lowest-system-priority
	    thereis (not (constant-queue-empty-p
			   (svref current-task-queue-vector priority)))))))

(defun-simple tasks-deferred-until-resumption? ()
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (loop for priority from highest-system-priority to lowest-system-priority
	thereis (not (constant-queue-empty-p
		       (svref deferred-task-queue-vector priority))))))




;;; The macro `next-scheduled-task-for-function' takes an unquoted symbol naming
;;; a function that may have tasks scheduled for it and a priority.  This macro
;;; will search the currently scheduled tasks, and if the next task is one that
;;; would execute the given function, then that task is returned.  If the next
;;; task to execute would run some other function, then this operation returns
;;; NIL.  This function uses the given priority as a further filter.  If the
;;; task found executes at the given priority or is an immediate task, then it
;;; is returned.  If the found task is not immediate, or is for a priority other
;;; than the one given, then NIL is returned.

(defun-simple next-scheduled-task-for-function (function-name priority)
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (let ((immediate-task?
	 (constant-queue-peek
	   #-SymScale immediate-task-queue
	   #+SymScale (svref immediate-task-queue-vector current-thread-index))))
     (if immediate-task?
	 (if (eq (schedule-task-function-name immediate-task?) function-name)
	     immediate-task?
	     nil)
	 ;; Note that we have to loop since a cancelled task might have dropped
	 ;; the priority of the actual next task down below the value of the
	 ;; variable, priority-of-next-task.
	 #-SymScale
	 (loop for priority from priority-of-next-task to priority
	       for current-task? = (constant-queue-peek
				     (svref current-task-queue-vector priority))
	       do
	   (when current-task?
	     (return
	       (if (and (eq (schedule-task-function-name current-task?) function-name)
			(=f (schedule-task-priority current-task?) priority))
		   current-task?
		   nil))))))))


;;;; Task Utilities




;;; The following section implements other scheduling operations beyond basic
;;; scheduling, canceling, and executing.

;;; The macro `schedule-task-in-place-p' takes a schedule-task or NIL, and
;;; returns true when the argument is a schedule-task that is waiting to execute
;;; or is currently executing.  The macro `future-schedule-task-in-place-p' only
;;; returns true for tasks waiting to execute.  The macro
;;; `current-schedule-task-in-place-p' returns true for tasks in the
;;; current-queues of tasks waiting to execute.

(def-substitution-macro schedule-task-in-place-p (schedule-task?)
  (and schedule-task?
       (or (schedule-task-queue-element schedule-task?)
	   (eq schedule-task? current-schedule-task))))

(def-substitution-macro future-schedule-task-in-place-p (schedule-task?)
  (and schedule-task? (schedule-task-queue-element schedule-task?)))

(def-substitution-macro current-schedule-task-in-place-p (schedule-task?)
  (and schedule-task?
       (schedule-task-queue-element schedule-task?)
       (<=e (schedule-task-time schedule-task?)
	    (managed-float-value
	      (if (schedule-task-g2-running-p schedule-task?)
		  (clock-get current-g2-time)
		  (clock-get current-real-time))))))




;;; The macro `schedule-task-currently-executing-p' takes a schedule-task or NIL
;;; and returns true when the given argument is a schedule-task and is the task
;;; currently executing.

(def-substitution-macro schedule-task-currently-executing-p (schedule-task?)
  (and schedule-task?
       (eq schedule-task? current-schedule-task)))




;;; The modify macro `change-priority-of-task' takes a place holding a
;;; schedule-task or NIL and reschedules the task at the new priority if it
;;; exists.  Note that if the given priority is the same as this tasks existing
;;; priority, or if no task is in the location, then this operation is a noop.
;;; If the priority is different, then this task will be placed onto the end of
;;; the appropriate task-queue for its priority and task-time.

(define-modify-macro change-priority-of-task (new-priority)
		     change-priority-of-task-modify-macro)

(def-substitution-macro change-priority-of-task-modify-macro
    (schedule-task? priority)
  (cond
    ((schedule-task-in-place-p schedule-task?)
     (unless (equal-priority-p (schedule-task-priority schedule-task?) priority)
       (cancel-schedule-task-possibly-reclaiming-queue schedule-task?)
       (when (eq schedule-task? current-schedule-task)
	 (setq current-schedule-task nil))
       (setf (schedule-task-priority schedule-task?) priority)
       (future-task-schedule-2 schedule-task?))
     schedule-task?)
    (t
     (cancel-task-internal schedule-task?))))




;;; The modify macro `reschedule-task' takes a location with a schedule-task in
;;; it, and will reschedule that task before it has occurred or while it is
;;; occuring.  It also takes a fixnum seconds interval argument to delay the
;;; task.

(define-modify-macro reschedule-task (wait-interval) reschedule-task-1)

(defmacro reschedule-task-1 (schedule-task? wait-interval)
  (let ((task? (make-symbol "TASK")))
    `(let ((,task? ,schedule-task?))
       (cond
	 ((schedule-task-in-place-p ,task?)
	  (cancel-schedule-task-possibly-reclaiming-queue ,task?)
	  (when (eq ,task? current-schedule-task)
	    (setq current-schedule-task nil))
	  (when (immediate-scheduled-task-p ,task?)
	    (setf (schedule-task-priority ,task?)
		  highest-system-priority))
	  (setf (schedule-task-time ,task?)
		(+e (managed-float-value
		      (if (schedule-task-g2-running-p ,task?)
			  (clock-get current-g2-time)
			  (clock-get current-real-time)))
		    (coerce-fixnum-to-gensym-float ,wait-interval)))
	  (future-task-schedule-2 ,task?)
	  ,task?)
	 (t
	  (cancel-task-internal ,task?))))))
		   




;;; The modify macro `execute-task-out-of-order' takes a location holding a
;;; schedule-task or NIL and will execute and reclaim that schedule task, if
;;; any.  Note that if a non-local exit occurs out of these form, it will leak
;;; one schedule task.

(define-modify-macro execute-task-out-of-order ()
		     execute-task-out-of-order-1)

(defun-simple execute-task-out-of-order-1 (schedule-task)
  (when schedule-task
    (cancel-schedule-task-possibly-reclaiming-queue schedule-task)
    (when (eq schedule-task current-schedule-task)
      (setq current-schedule-task nil))
    (let ((priority-of-current-task
	    (lowest-priority
	      (schedule-task-priority schedule-task)
	      highest-system-priority))
	  (current-schedule-task schedule-task)
	  (reclaim-task?
	   (schedule-task-reclaimable-by-scheduler-p schedule-task)))
      #-mtg2
      (progn
	(execute-schedule-task schedule-task)
	(when reclaim-task?
	  (reclaim-schedule-task-macro schedule-task)))
      #+mtg2
      (if (null (schedule-task-faction? immediate-task?))
	  (progn
	    (execute-schedule-task schedule-task)
	    (when reclaim-task?
	      (reclaim-schedule-task-macro schedule-task)))
	  (plan-immediate-task (gensym-list schedule-task) priority-of-current-task))
      ;; Next execute any immediate tasks enqueued by the execution of
      ;; the previous current task.
      (dequeue-and-execute-all-immediate-tasks highest-system-priority)))
  nil)




;;; The function `clear-g2-schedule' is used when G2 is being reset.  This will
;;; cancel all currently scheduled g2-running tasks from all task-queues.

;; Note that the function below only works out because the iteration paths for
;; constant-queue-element and future-task-queue-holder always step past the
;; element being served before serving it, so that the currently served element
;; can always be deleted.  -jra 3/17/94

(defun-void clear-g2-schedule ()
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (with-backtrace-for-internal-error 'clear-g2-schedule
    ;; Start with the immediate tasks.
    #-SymScale
    (loop for schedule-task being each constant-queue-element of immediate-task-queue
	  do
      (when (schedule-task-g2-running-p schedule-task)
	(cancel-schedule-task-possibly-reclaiming-queue schedule-task)
	(when (schedule-task-reclaimable-by-scheduler-p schedule-task)
	  (reclaim-schedule-task-macro schedule-task))))
    #+SymScale
    (loop for i from 0 below number-of-all-threads
	  for queue = (svref immediate-task-queue-vector i)
	  do
      (loop for schedule-task being each constant-queue-element of queue
	    do
        (when (schedule-task-g2-running-p schedule-task)
	  (cancel-schedule-task-possibly-reclaiming-queue schedule-task)
	  (when (schedule-task-reclaimable-by-scheduler-p schedule-task)
	    (reclaim-schedule-task-macro schedule-task)))))
    ;; Next clear out the current task queues.
    (loop for priority from highest-system-priority to lowest-system-priority
	  for queue = (svref current-task-queue-vector priority)
	  do
      (loop for schedule-task being each constant-queue-element of queue
	    do
	(when (schedule-task-g2-running-p schedule-task)
	  (cancel-schedule-task-possibly-reclaiming-queue schedule-task)
	  (when (schedule-task-reclaimable-by-scheduler-p schedule-task)
	    (reclaim-schedule-task-macro schedule-task)))))
    ;; Next clear out the deferred task-queues.
    (loop for priority from highest-system-priority to lowest-system-priority
	  for queue = (svref deferred-task-queue-vector priority)
	  do
      (loop for schedule-task being each constant-queue-element of queue
	    do
	(cancel-schedule-task-possibly-reclaiming-queue schedule-task)
	(when (schedule-task-reclaimable-by-scheduler-p schedule-task)
	  (reclaim-schedule-task-macro schedule-task))))
    ;; Finally, clear out the future-g2-task-queues.
    (loop for queue-holder being each future-task-queue-holder
	  of future-g2-time-tasks
	  do
      (loop for schedule-task being each constant-queue-element of
			      (future-task-queue-constant-queue queue-holder)
	    do
	(cancel-schedule-task-possibly-reclaiming-queue schedule-task)
	(when (schedule-task-reclaimable-by-scheduler-p schedule-task)
	  (reclaim-schedule-task-macro schedule-task)))))))




;;; The function `adjust-task-times-after-clock-discontinuity' takes a
;;; managed-float and a future task queue.  This function iterates over the
;;; tasks in the queue and adjusts their task times by the amount given.

(defun-void adjust-task-times-after-clock-discontinuity
    (managed-float-offset future-task-queue-set)
  (with-temporary-gensym-float-creation adjust-task-times
    (loop with offset gensym-float = (managed-float-value managed-float-offset)
	  for task-queue-holder
	  being each future-task-queue-holder of future-task-queue-set
	  for holder-time = (future-task-queue-time task-queue-holder)
	  for queue = (future-task-queue-constant-queue task-queue-holder)
	  do
      (mutate-managed-float-value
	holder-time (+e (managed-float-value holder-time) offset))
      (loop for schedule-task being each constant-queue-element of queue
	    do
	(setf (schedule-task-time schedule-task)
	      (+e (schedule-task-time schedule-task) offset))))))






;;;; Time Slices




;;; A time slice is an interval during which an operation can continue to
;;; perform more work.  When a time slice is over, or expired, then the current
;;; process should pack its bags and return.  If it needs to schedule another
;;; task to continue its unfinished work, it should do so before returning.
;;; This section implements operations to control the length of a time slice, to
;;; enter a time slice, and to test if the current time slice is over.

(def-concept time-slice)




;;; The special variable `time-slice-start-time' is used to hold a start time
;;; during invocation of a scheduled task or data server accept function.  The
;;; system variable `maximum-time-slice-size' stores the maximum amount of time
;;; that any scheduled task should spend in one invocation, expressed in
;;; fixnum-time-units-per-second.  This is currently 50 milliseconds.  This
;;; value may specially bound around contexts where the allowable time slice
;;; size may differ, such as when servicing the user interface or network
;;; connections.  These values are used by the macro time-slice-expired-p.

(defvar time-slice-start-time 0)

(def-system-variable maximum-time-slice-size clocks
  (:funcall fixnum-time-interval 50))




;;; The function `time-slice-expired-p' is a macro which can be called to
;;; determine if some computation has overrun its allowable time slice.  It may
;;; be called by any routine in the system run within the dynamic scope of
;;; run-scheduler, which everything but the initial environment setup routines
;;; for G2.  Processes should make every reasonable effort to test this
;;; predicate and return as soon after their time slice expires as they are
;;; able.

(declare-side-effect-free-function time-slice-expired-p)

(defun-simple time-slice-expired-p ()
  (or (higher-priority-p priority-of-next-task priority-of-current-task)
      (let ((elapsed-time
	      (fixnum-time-difference (get-fixnum-time) time-slice-start-time)))
	(>=f elapsed-time maximum-time-slice-size))
      (and (/=f priority-of-next-task most-positive-fixnum)
	   (maybe-check-network-events))))

(declare-side-effect-free-function time-slice-expired-p-given-time)

(defun-simple time-slice-expired-p-given-time (given-fixnum-time)
  (or (higher-priority-p priority-of-next-task priority-of-current-task)
      (let ((elapsed-time
	      (fixnum-time-difference given-fixnum-time time-slice-start-time)))
	(>=f elapsed-time maximum-time-slice-size))))

(defmacro with-unlimited-time-slice (&body body)
  `(let ((maximum-time-slice-size most-positive-fixnum)
	 (priority-of-next-task most-positive-fixnum))
     ,@body))






;;;; Scheduler Lag Times




;;; There are G2 meters which the user can query to determine the "lag time" of
;;; tasks within a priority.  This section implements a function for determining
;;; the current lag time given a priority for the G2 running tasks.

;;; The function `scheduler-time-lag' takes a priority argument and a G2-tasks?
;;; flag and returns a gensym-float number of seconds that the tasks at that
;;; priority are behind.  This number is computed by comparing the task time of
;;; first G2 time task at that priority to the current-g2-time.

;;; Note that in 3.0 and earlier versions, these meters has somewhat different
;;; behaviors.  In 3.0 the reported scheduler lag for a priority would be the
;;; maximum of the lag at the next highest priority and the lag of the task at
;;; the head of the task queue at the given priority.  This meant that if there
;;; was a lag at a high priority, there would be equal or greater lags reported
;;; at every priority below that one, whether or not there were actaully tasks
;;; running at those lower priorities.  For example, if there were a 20 second
;;; lag at priority 6, and no tasks running at priorities 7 through 10,
;;; priorities 7 through 10 would still report a 20 second scheduler lag.

;;; In 4.0, the scheduler lag values will be accurate per priority.  So if there
;;; is a 20 second lag at priority 6, and no tasks running at priorities 7
;;; through 10, the the lag reported for priorities 7 through 10 will be 0.

(defun-simple scheduler-time-lag (priority)
  #+development
  (unless (priority-p priority)
    (error "Scheduler-lag-time given an argument that is not a priority: ~a"
	   priority))
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (loop for task being each constant-queue-element
		       of (svref current-task-queue-vector priority)
	when (schedule-task-g2-running-p task)
	  return (-e (managed-float-value (clock-get current-g2-time))
		     (schedule-task-time task))
	finally
	  (return 0.0d0))))




;;; This section is for functions to be used in helping to debug the scheduler.

(defun-void twrite-schedule-task-header ()
  (tformat "Time Cyclic G2-Running? Priority Function-and-Args"))


(defun-simple type-name-of-named-simple-vector (arg)
  (when (allocated-named-gensym-structure-p arg)
    (let ((type (g2-type-name-of-named-simple-vector arg)))
      (if (eql (symbol-package type) the-g2-defstruct-package)
	  (ab-name-of-unique-structure-type type)
	  type))))

(defun-void twrite-debug-object (arg)
  #-trace-invocations
  (declare (eliminate-for-gsi))
  (if (allocated-named-gensym-structure-p arg)
      (tformat " <~a>" (type-name-of-named-simple-vector arg))
      (tformat " ~a" arg)))

(defun-void twrite-debug-computation-instance-or-object (arg)
  #-trace-invocations
  (declare (eliminate-for-gsi))
  (multiple-value-bind (name? class?)
      (current-system-case
	(ab (name-and-class-for-computation-instance arg))
	(t nil))
    (cond ((null class?)
	   (twrite-debug-object arg))
	  ((null name?)
	   (tformat " [~a]" class?))
	  (t
	   (tformat " [~a ~a]" class? name?)))))

;;; The function `twrite-schedule-task' takes a schedule task and
;;; twrites a string describing that task.

(defun-void twrite-schedule-task (schedule-task)
  (declare (eliminate-for-gsi))
  (with-temporary-gensym-float-creation twrite-schedule-task
    (write-floating-point-number
      (-e (schedule-task-time schedule-task)
	  (+e (coerce-fixnum-to-gensym-float (clock-get gensym-time))
	      (universal-time-to-unix-time
		(managed-float-value (clock-get gensym-base-time-as-managed-float)))))
      9 3 0 nil nil nil nil 13 #\#)
    (twrite-char #\space)
    (let ((interval-string
	    (twith-output-to-text-string
	      (write-floating-point-number
		(schedule-task-cycle-interval schedule-task)
		4 3 0 t nil nil nil 8 #\#))))
      (twrite-string interval-string)
      (loop repeat (-f 8 (text-string-length interval-string)) do
	(twrite-char #\space))
      (reclaim-text-string interval-string))
    (twrite-string
      (if (schedule-task-g2-running-p schedule-task)
	  "T    "
	  "NIL  "))
    (tformat "~a~a   "
	     (schedule-task-priority schedule-task)
	     (if (<f (schedule-task-priority schedule-task) 10) " " ""))
    (let ((args (schedule-task-argument-count schedule-task)))
      (twrite-char #\()
      (let ((name (get-name-for-function (schedule-task-function-name schedule-task))))
	(twrite-string name)
	(reclaim-simple-gensym-string name))
      (when (>f args 0)
	(twrite-debug-computation-instance-or-object
	  (schedule-task-arg-1 schedule-task))
	(when (>f args 1)
	  (twrite-debug-computation-instance-or-object
	    (schedule-task-arg-2 schedule-task))
	  (when (>f args 2)
	    (twrite-debug-computation-instance-or-object
	      (schedule-task-arg-3 schedule-task))
	    (when (>f args 3)
	      (twrite-debug-computation-instance-or-object
		(schedule-task-arg-4 schedule-task))))))
      (twrite-char #\)))))




;;; The function `task-queue-descriptions' takes a constant-queue
;;; holding tasks and returns a gensym-cons list of text-strings describing that
;;; task-queue.  Note that this doesn't just twrite the whole thing since there
;;; are difficulties dealing with newlines in twritten text.

(defun-simple task-queue-descriptions (constant-queue)
  (declare (eliminate-for-gsi))
  (loop for schedule-task being each constant-queue-element of constant-queue
	collect (twith-output-to-text-string
		  (twrite-schedule-task schedule-task))
	  using gensym-cons))




;;; The function `print-schedule' prints to standard-output the
;;; current state of the clocks and scheduler queues.

(defun-simple print-schedule-to-string-list (current-only-p)
  (declare (eliminate-for-gsi))
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (with-temporary-gensym-float-creation print-schedule
    (nconc
      (gensym-list
	(twith-output-to-text-string
	  (tformat "System-is-running = ~a, System-has-paused = ~a"
		   system-is-running system-has-paused))
	(twith-output-to-text-string
	  (tformat "Scheduler-mode = ~a, Minimum-scheduling-interval = ~a"
		   (determine-scheduler-mode-for-current-system)
		   (determine-minimum-scheduling-interval-for-current-system)))
	(twith-output-to-text-string
	  (twrite-string "Actual real time  = ")
	  (write-floating-point-number
	    (gensym-get-unix-time)
	    9 3 0 nil nil nil nil 13 #\#))
	(twith-output-to-text-string
	  (tformat "Current-real-time = ")
	  (write-floating-point-number
	    (managed-float-value (clock-get current-real-time))
	    9 3 0 nil nil nil nil 13 #\#))
	(twith-output-to-text-string
	  (tformat "Current-g2-time   = ")
	  (write-floating-point-number
	    (managed-float-value (clock-get current-g2-time))
	    9 3 0 nil nil nil nil 13 #\#))
	(twith-output-to-text-string
	  (tformat "Gensym-time       = ")
	  (write-floating-point-number
	    (+e (coerce-fixnum-to-gensym-float gensym-time)
		(universal-time-to-unix-time
		  (managed-float-value (clock-get gensym-base-time-as-managed-float))))
	    9 3 0 nil nil nil nil 13 #\#))
	(twith-output-to-text-string
	  (tformat " (Gensym-time = ~a, gensym-base-time-as-managed-float = ~a)"
		   (clock-get gensym-time)
		   (managed-float-value (clock-get gensym-base-time-as-managed-float))))
	(twith-output-to-text-string
	  (tformat "Priority-of-next-task = ~a, current-tasks-enqueued? = ~a"
		   priority-of-next-task
		   (tasks-enqueued-for-current-execution?))))
      (unless (constant-queue-empty-p immediate-task-queue)
	(gensym-cons
	  (twith-output-to-text-string (tformat ""))
	  (gensym-cons
	    (twith-output-to-text-string (tformat "Immediate-task-queue"))
	    (gensym-cons
	      (twith-output-to-text-string (twrite-schedule-task-header))
	      (task-queue-descriptions immediate-task-queue)))))
      (when (tasks-enqueued-for-current-execution?)
	(gensym-cons
	  (twith-output-to-text-string (tformat ""))
	  (gensym-cons
	    (twith-output-to-text-string (tformat "Current-task-queue-vector"))
	    (gensym-cons
	      (twith-output-to-text-string (twrite-schedule-task-header))
	      (loop for priority from highest-system-priority to lowest-system-priority
		    nconc (task-queue-descriptions
			    (svref current-task-queue-vector priority)))))))
      (unless current-only-p
	(nconc
	  (when (tasks-deferred-until-resumption?)
	    (gensym-cons
	      (twith-output-to-text-string (tformat ""))
	      (gensym-cons
		(twith-output-to-text-string (tformat "Deferred-task-queue-vector"))
		(gensym-cons
		  (twith-output-to-text-string (twrite-schedule-task-header))
		  (loop for priority from highest-system-priority to lowest-system-priority
			nconc (task-queue-descriptions
				(svref deferred-task-queue-vector priority)))))))
	  (when (future-tasks-exist-p future-real-time-tasks)
	    (gensym-cons
	      (twith-output-to-text-string (tformat ""))
	      (gensym-cons
		(twith-output-to-text-string (tformat "Future-real-time-tasks"))
		(gensym-cons
		  (twith-output-to-text-string (twrite-schedule-task-header))
		  (loop for queue-holder
			    being each future-task-queue-holder of future-real-time-tasks
			nconc (task-queue-descriptions
				(future-task-queue-constant-queue queue-holder)))))))
	  (when (future-tasks-exist-p future-g2-time-tasks)
	    (gensym-cons
	      (twith-output-to-text-string (tformat ""))
	      (gensym-cons
		(twith-output-to-text-string (tformat "Future-g2-time-tasks"))
		(gensym-cons
		  (twith-output-to-text-string (twrite-schedule-task-header))
		  (loop for queue-holder
			    being each future-task-queue-holder of future-g2-time-tasks
			nconc (task-queue-descriptions
				(future-task-queue-constant-queue queue-holder)))))))))))))






;; gsi-maximum-idle-interval the maximum interval that a GSI process will sleep
;; (waiting for events), in milliseconds.  -ncc, 21 Apr 1997
;;  SEE ALSO gsi-set-pause-timeout for the user-visible setter for this
;; parameter.  
(defvar gsi-maximum-idle-interval 1000)


;;; The function `enqueue-scheduler-events-if-necessary' should be called after
;;; handling network and user interface events, and when run-one-scheduler-cycle
;;; is about to exit.  This function ensures that there is an appropriate
;;; continuing thread of execution back into run-one-scheduler-cycle by
;;; enqueuing events to be processed.

(defun-simple milliseconds-to-next-scheduler-event ()
  (if (or (tasks-enqueued-for-current-execution?)
	  (progn
	    (current-system-case
	      (ab (tick-the-clock t))
	      (t  (tick-the-clock-for-tw-or-gsi)))
	    (tasks-enqueued-for-current-execution?)))
      nil
      (let ((milliseconds-to-next-task (milliseconds-to-next-task)))
	(if (and milliseconds-to-next-task
		 (>=f 0 milliseconds-to-next-task))
	    nil
	    (minf (or milliseconds-to-next-task most-positive-fixnum)
		  ;; In this case we have no future tasks, no pending tasks, and no
		  ;; events in the queue.  We could decline to put any events into the
		  ;; queue and let the next network or UI event wake us up.  However,
		  ;; the fixnum time clocks have a range of 24 hours, so we must wake
		  ;; up within 24 hours in order to be able to measure how long we
		  ;; were asleep.  So, schedule a timer event for 1 hour into the
		  ;; future.  -jra 10/22/96
		  (current-system-case
		    (gsi
		      gsi-maximum-idle-interval)
		    (t 3600000)))))))

(defun-simple enqueue-scheduler-events-if-necessary (force-scheduler-event?)
  (let ((milliseconds-to-sleep?
	  (unless force-scheduler-event?
	    (milliseconds-to-next-scheduler-event))))
    (if milliseconds-to-sleep?
	(ne-set-next-timer-event milliseconds-to-sleep?)
	(ne-enqueue-scheduler-event))
    milliseconds-to-sleep?))

;;;
;;; SymScale(R): Multi-threaded G2 Server
;;;
;;; Lead developer: Chun Tian (binghe)
;;;
;;; Related CIDs:
#|

GENSYMCID-616: Update multi-threaded version of Chestnut translator (trans-mt-sbcl) Windows part
GENSYMCID-618: G2 Lisp source code translate to new directory "SymScale/c"
GENSYMCID-619: Add pthreads support for Windows (pthreads-w32)
GENSYMCID-621: Create Visual Studio project files for building SymScale G2
GENSYMCID-635: Create unit tests for multi-threaded Chestnut translator and RTL (Windows)
GENSYMCID-636: Create unit tests for multi-threaded Chestnut translator and RTL (Linux)
GENSYMCID-674: Two-threads SymScale G2 - Part I (scheduler)
GENSYMCID-675: Two-threads SymScale G2 - Part II (thread-safe DEFCONSER)
GENSYMCID-676: Two-threads SymScale G2 - Part III (thread-safe DEF-STRUCTURE, DEF-VECTOR-POOL and CONSTANT-QUEUE)
GENSYMCID-677: Two-threads SymScale G2 - Part IV (other fixes with atomic operations)
GENSYMCID-678: Fix linker errors when building SymScale G2 on Linux
GENSYMCID-695: Implement Gensym multithreading - UC12
GENSYMCID-738: Two-threads SymScale G2 consumes one full CPU
GENSYMCID-739: Implement atomic operators for Chestnut RTL: ATOMIC-INCF(&) and ATOMIC-DECF(&)
GENSYMCID-740: Three-threads SymScale G2: handle UI events when executing a long procedure
GENSYMCID-741: Three-threads SymScale G2: execute two procedures in parallel
GENSYMCID-775: Implement tx:compare-and-swap in Chestnut Lisp->C translator
GENSYMCID-1178: Complete G2 server multi threading
GENSYMCID-1233: Run WashingtonRiver (htwos) in multi-threading G2 
GENSYMCID-1331: Implement KB level atomic CONCLUDE for SymScale
GENSYMCID-1345: SymScale : Structure reclaimed is not of expected type BLOCK-CHANGE
GENSYMCID-1479: Multi-threading G2 (SymScale) cannot pass all regression tests
GENSYMCID-1496: Implement thread-safe, hash-based relation instances (former UC14)
GENSYMCID-1499: Create unit tests for G2's lock-free double-ended queue (constant-queue)

|#

;;; A recursive lock protecting scheduler globals
#+mtg2
(defvar scheduler-lock
  (tx:make-recursive-lock :name #.(symbol-name 'scheduler-lock)))

#+SymScale
(progn

(defvar-of-special-global number-of-scheduler-workers nil)
(defvar-of-special-global scheduler-worker-vector nil)
(defvar-of-special-global legacy-mode-p nil) ; flag set by #w"legacy"

(defvar-of-special-global scheduler-event-lock
  (tx:make-lock :name #.(symbol-name 'scheduler-event-lock)))
(defvar-of-special-global scheduler-event-ready
  (tx:make-condition-variable :lock scheduler-event-lock))
(defvar-of-special-global scheduler-event-done
  (tx:make-condition-variable :lock scheduler-event-lock))

(def-command-line-argument (legacy (:systams ab)) (:flag))
(def-command-line-argument (threads (:systems ab)) (:keyword))

(defun-simple get-workers-from-command-line ()
  (let ((n (get-command-line-keyword-argument-as-integer #w"threads")))
    ;; default value depend on current system
    (or n max-number-of-cores)))

(defun-simple legacy-mode-p ()
  (get-command-line-flag-argument #w"legacy"))

(defparameter g2-main-thread (tx:current-thread))

(defun-simple start-scheduler-workers ()
  ;; set current G2 running mode
  (setq legacy-mode-p (legacy-mode-p)
	multicore-p   (not legacy-mode-p))
  (when legacy-mode-p
    (return-from start-scheduler-workers))

  ;; set number of workers, with limitations
  (setq number-of-scheduler-workers
	(minf (get-workers-from-command-line) (1-f g2-max-threads)))

  ;; count all threads into a global variable
  (setq number-of-all-threads (1+f number-of-scheduler-workers))

  ;; starting scheduler workers
  (loop with new-vector = (make-thread-array nil)
	for index from 1 below number-of-all-threads do
    (setf (svref new-vector index)
	  (tx:spawn-thread (format nil "G2 scheduler worker ~D" index)
			   #'scheduler-worker-function index)) ; index = current-thread-index
	finally
	  (setf (svref new-vector 0) g2-main-thread)
	  (setq scheduler-worker-vector new-vector))

  ;; wait a while for above new created threads
  (tx:thread-yield))

(defun-void scheduler-worker-function (index)
  (let* ((current-thread-index index)
	 ;; scheduler variables
	 (current-schedule-task nil)
	 (priority-of-current-task higher-than-any-priority)
	 (time-slice-start-time 0)
	 ;; optimized-constant-vector
	 (optimized-constant-vector (make-array optimized-constant-vector-length))
	 (optimized-constant-vector-index 0)
	 (optimized-constant-pc 0)
	 (optimized-constant-op-codes nil)
	 ;; grammar (parse)
	 (current-transform-constituent-array nil)
	 (current-transform-constituent-count nil)
	 ;; always nil in worker thread (kb-save1)
	 (current-saving-context? nil)
	 ;; scope conses (utilities0)
	 (scope-conses (list (list nil)))
	 (vector-of-simple-vector-pools
	  (allocate-initial-managed-simple-vector-pool-array nil))
#|
	 (vector-of-simple-vector-pools-for-array
	  (allocate-initial-managed-simple-vector-pool-array nil))
	 (vector-of-simple-vector-pools-for-float-array
	  (allocate-initial-managed-simple-vector-pool-array nil))
	 (vector-of-simple-vector-pools-for-skip-list
	  (allocate-initial-managed-simple-vector-pool-array nil))
|#
	 (vector-of-oversized-simple-vector-pools
	  (allocate-initial-managed-simple-vector-pool-array nil))
	 (vector-of-simple-float-array-pools
	  (allocate-initial-vector-of-simple-float-array-pools))
	 (vector-of-oversized-simple-float-array-pools
	  (allocate-initial-vector-of-simple-float-array-pools))
	 ;; gensym-strings (utilities1)
	 (short-simple-gensym-strings (new-short-simple-gensym-string-vector nil))
	 (long-simple-gensym-strings (new-partial-buffer-gensym-string-vector nil))
	 (adjustable-gensym-strings (new-partial-buffer-gensym-string-vector nil))
	 (short-simple-gensym-string-counts (new-short-simple-gensym-string-vector 0))
	 (long-simple-gensym-string-counts (new-partial-buffer-gensym-string-vector 0))
	 (adjustable-gensym-string-counts (new-partial-buffer-gensym-string-vector 0))
	 ;; def-structure (utilities2)
	 (structure-being-reclaimed nil)
	 (skip-list-find-preds
	  (make-array skip-list-global-max-level))
	 (skip-list-find-succs
	  (make-array skip-list-global-max-level))
	 ;; intern symbols (utilities3)
	 (*package* *package*)
	 ;; float-string (unicode.lisp)
	 (string-for-returning-floats
	  (make-string size-of-string-for-returning-floats))
	 (partition-float-union (make-partition-float-or-long-union))
	 (partition-long-union  (make-partition-float-or-long-union))
	 (gensym-time-array
	  (make-gensym-time-array))
	 ;; dangerous global variables added by SoftServe (commands1)
	 (global-table-of-attributes-pane nil)
	 (global-table-of-hidden-attributes-pane nil)
	 (global-table-of-attributes-pane-pointer nil) 
	 (global-table-of-hidden-attributes-pane-pointer nil)
	 (global-nmsci-id-for-attributes-pane nil)
	 (global-nmsci-id-for-hidden-attributes-pane nil)
	 (global-nms-menu-choiced-item-id nil)
	 ;; workstation-contexts (mice)
	 (available-workstation-contexts nil) ; a per-thread pool
	 (specific-structure-for-current-workstation-context nil)
	 (next-continuation-function? nil)
	 (next-old-style-return-function? nil) 
	 (next-info nil)
	 (next-info-reclaimer? nil)
	 ;; solution for crash point in TWRITE-PORTION-OF-WIDE-STRING-UNPARSABLY-
	 ;; TO-CURRENT-WIDE-STRING (unicode)
	 (byte-vector-16-pools (make-byte-vector-16-pools nil))
	 (byte-vector-16-pool-counts (make-byte-vector-16-pools 0))
	 (byte-vector-16-pool-number-to-malloc -1)
	 ;; breakpoints (run)
	 (inside-breakpoint-p nil)
	 (return-from-breakpoint-task nil)
	 ;; per-threads duplicates check hash.
	 (duplicates-check-hash (make-duplicates-check-hash-table))
	 (things-that-affect-this-formula nil)
	 ;; icons
	 (current-icon-untransformed-width nil)
	 (current-icon-untransformed-height nil)
	 (current-icon-variables-plist nil)
	 (current-icon-variables-override-plist nil)
	 ;; frames5
	 (stack-of-slot-value-changes nil)
	 ;; new-rules
	 (list-of-generated-contexts nil)
	 (list-of-generated-contexts-tail nil))
    (let #-development ()
	 #+development
	 ((stack-of-current-named-dynamic-extents nil)
	  (pool-of-conses-for-stack-of-current-named-dynamic-extents nil)
	  (memory-comparison-alist nil)
	  (unreclaimed-class-descriptions nil)
	  (unreclaimed-slot-descriptions nil)
	  (unreclaimed-class-description-method-tables nil))
      (g2-worker-loop))))

;; macro user is function g2-worker-loop in stack-kern.lisp
(defmacro g2-worker-loop-macro ()
  `(loop do
     (catch-abort (1)
       (with-catch-handlers-for-stack-eval (t t)
         ;; worker initialization
         (loop do
           (scheduler-worker-loop)
           (tx:thread-yield))))))

;;; A Naive Synchronous Queue (Part II: dequeue), from Chapter 10.6.1 of the
;;; book `The Art of Multiprocessor Programming'. Simple but works correctly.
;;;
;;; Also see Part I in function `dequeue-and-execute-next-task'.
;;;
;;; TODO: upgrade the algorithm using paper `Scalable synchronous queues'.
;;; -- Chun Tian (binghe), April 1, 2015.

(defun-void scheduler-worker-loop ()
  (when current-schedule-task
    (when (schedule-task-reclaimable-by-scheduler-p current-schedule-task)
      (reclaim-schedule-task current-schedule-task))
    (setq current-schedule-task nil))

  (dequeue-and-execute-all-immediate-tasks
    (if (system-priority-p priority-of-current-task)
	priority-of-current-task
	highest-system-priority))

  (tx:with-lock-held (scheduler-event-lock)
    (loop while (null scheduler-task) do
      (tx:condition-variable-wait-with-timeout scheduler-event-ready
					       scheduler-worker-loop-interval))
    (shiftf current-schedule-task scheduler-task nil)
    (setq priority-of-current-task scheduler-task-priority)
    (setq time-slice-start-time scheduler-task-time)
    (tx:condition-variable-broadcast scheduler-event-ready))

  (execute-task-and-reschedule current-schedule-task)

  (dequeue-and-execute-all-immediate-tasks priority-of-current-task)
  (setq priority-of-current-task higher-than-any-priority))

) ; progn (SymScale)

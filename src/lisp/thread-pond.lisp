;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module THREAD-POND
; `thread-pool' name is already taken

;;; Copyright (c) 2017 Ignite 
;;; All Rights Reserved.

;;; Dmitri Hrapof

;;; A thread-pool implementation with a task queue

(def-structure (thread-pond
                 (:constructor make-thread-pond-internal)
                 (:reclaimer reclaim-thread-pond-internal))
  (thread-pond-active-count 0) ; number of running workers
  (thread-pond-lock nil) ; guards the pond
  (thread-pond-queue-cv nil) ; task queue condition variable
  (thread-pond-run-cv nil) ; running state condition variable
  (thread-pond-count-cv nil) ; running threads' count condition variable
  (thread-pond-run? nil) ; if true, workers are allowed to run
  (thread-pond-queue nil) ; task queue
  (thread-pond-threads nil) ; thread hash table
  (thread-pond-fun nil) ; function that processes tasks, one at a time
  (thread-pond-thunk nil) ; thread loop function
  (thread-pond-thread-name nil) ; thread name
  (thread-pond-payload nil) ; user data
  )

;;; Internal API

;;; Decreases running thread count
(defun-simple %thread-pond-decf-active-count (pond)
  (tx:with-lock-held ((thread-pond-lock pond))
    (decff (thread-pond-active-count pond))
    (tx:condition-variable-signal (thread-pond-count-cv pond))))

;;; Returns next enqueued task
;;; If there is none, waits until a task is enqueued and returns it
(defun-simple %get-next-pond-task (pond)
  (let ((q (thread-pond-queue pond)))
    (tx:with-lock-held ((thread-pond-lock pond))
      (loop
	 do
	   (cond
	     ((and (thread-pond-run? pond)
		   (not (constant-queue-empty-p q)))
	      (loop-finish))
	     ((not (constant-queue-empty-p q))
	      (tx:condition-variable-wait (thread-pond-run-cv pond)))
	     (t
	      (tx:condition-variable-wait (thread-pond-queue-cv pond)))))
      (when (eq-gethash (thread-pond-threads pond) (tx:current-thread) nil)
	;; we increment here because we're already under a lock,
	;; to avoid taking a lock again in the calling function
	(incff (thread-pond-active-count pond))
	(constant-queue-dequeue q)))))

;;; Does the thread removal
(defun-simple %remove-thread (pond thread kill?)
  (eq-remhash (thread-pond-threads pond) thread)
  (when kill? (tx:kill-thread thread)))

;;; Thread worker function
(defun-simple %thread-thunk (pond)
  (loop
     while
       (let ((task (%get-next-pond-task pond)))
	 (when task
	   (unwind-protect
		(funcall (thread-pond-fun pond) task)
	     (%thread-pond-decf-active-count pond))
	   t))))

;;; External API

;;; Starts threads
(defun-simple thread-pond-start (pond)
  (tx:with-lock-held ((thread-pond-lock pond))
    (setf (thread-pond-run? pond) t)
    (tx:condition-variable-broadcast (thread-pond-run-cv pond))))

;;; Stops threads
(defun-simple thread-pond-stop (pond wait-for-stop?)
  (tx:with-lock-held ((thread-pond-lock pond))
    (setf (thread-pond-run? pond) nil)
    (when wait-for-stop?
      (loop
	 while (pluspf (thread-pond-active-count pond))
	 do (tx:condition-variable-wait (thread-pond-count-cv pond))))))

;;; Puts a task into pool's queue
;;; If we need a priority queue, PRIORITY parameter should be added
(defun-simple thread-pond-enqueue (pond task)
  (tx:with-lock-held ((thread-pond-lock pond))
    (constant-queue-enqueue (thread-pond-queue pond) task)
    (tx:condition-variable-signal (thread-pond-queue-cv pond))))

;;; Adds a new thread to the pool
(defun-simple thread-pond-add-thread (pond)
  (#+chestnut-3 tx:with-dynamic-area #-chestnut-3 progn
   (tx:with-lock-held ((thread-pond-lock pond))
     (let ((thread
	    (tx:spawn-thread
	     (thread-pond-thread-name pond)
	     (thread-pond-thunk pond) pond)))
      (setf (eq-gethash (thread-pond-threads pond) thread) t)
      thread))))

;;; Removes a thread from the pool
;;; Returns T if successfully removed the thread
;;; Nil otherwise
(defun-simple thread-pond-remove-thread (pond thread kill?)
  (when (tx:threadp thread)
    (tx:with-lock-held ((thread-pond-lock pond))
      ;; eq-remhash always returns nil, unlike CL remhash :-(
      (when (eq-gethash (thread-pond-threads pond) thread nil)
	(%remove-thread pond thread kill?)
	t))))

;;; Creates a new thread-pool with SIZE threads, each taking tasks from
;;; pool's queue and running FUN function on these tasks
;;; SIZE is not a limit, more threads can be added later.
(defun make-thread-pond (size fun &optional (thunk #'%thread-thunk) (name "POND WORKER"))
  (let ((pond (make-thread-pond-internal)))
    (#+chestnut-3 tx:with-dynamic-area #-chestnut-3 progn
      (setf (thread-pond-lock pond) ; maybe we should make it a r/w lock
	      (tx:make-lock :name "THREAD POND LOCK"))
      (setf (thread-pond-queue-cv pond)
	    (tx:make-condition-variable :lock (thread-pond-lock pond)))
      (setf (thread-pond-run-cv pond)
	    (tx:make-condition-variable :lock (thread-pond-lock pond)))
      (setf (thread-pond-count-cv pond)
	    (tx:make-condition-variable :lock (thread-pond-lock pond))))
    ;; we use `make-eq-hash-table' instead of `def-hash-table' as
    ;; the latter is described as "User level hash table"
    (setf (thread-pond-threads pond) (make-eq-hash-table (maxf 1 size) nil nil))
    ;; we use `make-empty-constant-queue' instead of `priority-queue' as
    ;; the latter is described as "User level priority queue" and
    ;; the former has O(1) performance
    ;; it's liable to be replaced with Fibonacci heap priority queue
    ;; if we need it
    (setf (thread-pond-queue pond) (make-empty-constant-queue))
    (setf (thread-pond-fun pond) fun (thread-pond-thunk pond) thunk
	  (thread-pond-thread-name pond) name)
    (loop for i below size doing (thread-pond-add-thread pond))
    pond))

;;; (Partially) reclaims pool
(defun reclaim-thread-pond (pond)
  ;; if we are really going to reclaim the thread-pool, we'll have to
  ;; implement `reclaim-lock', `reclaim-thread' etc.
  (tx:with-lock-held ((thread-pond-lock pond))
    (let ((all-threads-list (eq-hash-table-keys (thread-pond-threads pond))))
      (loop for thread in all-threads-list
	 do (%remove-thread pond thread t))
      (reclaim-gensym-list all-threads-list))
    (reclaim-eq-hash-table (thread-pond-threads pond))
    (reclaim-constant-queue (thread-pond-queue pond)))
  (reclaim-thread-pond-internal pond))

;;; Some getters
(defun get-pond-lock (pond) (thread-pond-lock pond))
(defun get-pond-queue-cv (pond) (thread-pond-queue-cv pond))

;;; Thread-pool parameters

;;; -threads command-line argument
(def-command-line-argument (threads (:systems ab)) (:keyword))

;;; How many threads to create at start
(defun-simple get-initial-worker-number ()
  (max
   2
   (or (get-command-line-keyword-argument-as-integer
	#w"threads")
       (read-number-for-gensym-environment-variable
	#w"G2THREADS")
       0)))

;;; Variables need for interpreter
(defmacro with-symscale-worker-magic (&body body)
   `(let* (;; scheduler variables
	   (current-schedule-task nil)
	   (priority-of-current-task higher-than-any-priority)
	   (time-slice-start-time 0)
	   ;; optimized-constant-vector
	   (optimized-constant-vector
	    (make-array optimized-constant-vector-length))
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
	   (vector-of-oversized-simple-vector-pools
	    (allocate-initial-managed-simple-vector-pool-array nil))
	   (vector-of-simple-float-array-pools
	    (allocate-initial-vector-of-simple-float-array-pools))
	   (vector-of-oversized-simple-float-array-pools
	    (allocate-initial-vector-of-simple-float-array-pools))
	   ;; gensym-strings (utilities1)
	   (short-simple-gensym-strings
	    (new-short-simple-gensym-string-vector nil))
	   (long-simple-gensym-strings
	    (new-partial-buffer-gensym-string-vector nil))
	   (adjustable-gensym-strings
	    (new-partial-buffer-gensym-string-vector nil))
	   (short-simple-gensym-string-counts
	    (new-short-simple-gensym-string-vector 0))
	   (long-simple-gensym-string-counts
	    (new-partial-buffer-gensym-string-vector 0))
	   (adjustable-gensym-string-counts
	    (new-partial-buffer-gensym-string-vector 0))
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
	   ,@body)))

;;; Interpreter thread worker
(defun-simple %interpreter-thread-thunk (pond)
  (with-symscale-worker-magic
      (loop
	 while
	   (let ((task (%get-next-pond-task pond)))
	     (when task
	       (do-error-trapping
		   (with-safe-stack-eval-reentrancy
		       (catch-abort
			(1)
			(with-catch-handlers-for-stack-eval (t t)
			  (unwind-protect
			       (funcall (thread-pond-fun pond) task)
			    (%thread-pond-decf-active-count pond))))))
	       t)))))

;;; Faction thread pool worker
(defun faction-pond-worker (tuple)
    (let ((task (second tuple)))
      (case (first tuple)
	(:reschedule
	 (let ((priority-of-next-task highest-system-priority))
	   (setf current-schedule-task task
		 priority-of-current-task
		 (lowest-priority
		  (schedule-task-priority task)
		  highest-system-priority))
	   (execute-task-and-reschedule task)))
	(:immediate
	 (setf priority-of-current-task (third tuple))
	 (loop for batch-task in task do
	      (let ((reclaim-task?
		     (schedule-task-reclaimable-by-scheduler-p
		      batch-task)))
		(setf current-schedule-task batch-task)
		(execute-schedule-task batch-task)
		(when (and reclaim-task? (schedule-task-p batch-task))
		  (reclaim-schedule-task-macro batch-task)))))
	(reclaim-gensym-list task))
      (reclaim-gensym-list tuple)))


;;; Utilities for faction task creation
(defun make-immediate-faction-task (tasks priority)
  (gensym-list :immediate tasks priority))
(defun make-reschedule-faction-task (task)
  (gensym-list :reschedule task))
(defun make-interpreter-pond (size name)
  (make-thread-pond size #'faction-pond-worker #'%interpreter-thread-thunk name))


(defun task-faction (tuple)
  (let ((task (second tuple)))
    (case (first tuple)
      (:reschedule (schedule-task-faction? task))
      (:immediate (schedule-task-faction? (first task))))))

(defun task-suitable-p (running-factions element)
  (let ((fac (task-faction element)))
    (and (not (memq fac running-factions))
	 (or (null fac) (eq fac :main-faction)
	     (faction-running-p fac)))))

(defun constant-queue-dequeue-faction-wise (pond q)
  (let* ((running-factions (thread-pond-payload pond))
	 (task
	  (loop for element being each constant-queue-element of q
	     when (task-suitable-p running-factions element)
	     return element)))
    (when task
      (constant-queue-search-and-delete q task)
      (gensym-push (task-faction task) (thread-pond-payload pond))
      task)))

;;; Returns T if the queue is empty or there is no task such that it's faction
;;; is not currently running and isn't stopped
(defun constant-queue-empty-faction-wise-p (pond q)
  (if (constant-queue-empty-p q)
      t
      (let ((running-factions (thread-pond-payload pond))) 
	(loop for element being each constant-queue-element of q
	   when (task-suitable-p running-factions element)
	   do (return-from constant-queue-empty-faction-wise-p nil))
	t)))

;;; Returns next task such that it's faction is not currently running and
;;; isn't stopped
(defun-simple %get-next-faction-task (pond)
  (let ((q (thread-pond-queue pond)))
    (tx:with-lock-held ((thread-pond-lock pond))
      (loop
	 do
	   (let ((queue-empty? (constant-queue-empty-faction-wise-p pond q)))
	     (cond
	       ((and (thread-pond-run? pond)
		     (not queue-empty?))
		(loop-finish))
	       ((not queue-empty?)
		(tx:condition-variable-wait (thread-pond-run-cv pond)))
	       (t
		(tx:condition-variable-wait (thread-pond-queue-cv pond))))))
      (when (eq-gethash (thread-pond-threads pond) (tx:current-thread) nil)
	;; we increment here because we're already under a lock,
	;; to avoid taking a lock again in the calling function
	(incff (thread-pond-active-count pond))
	(constant-queue-dequeue-faction-wise pond q)))))

;;; Updates running factions list
(defun-simple %thread-pond-release-faction (factions pond)
  (tx:with-lock-held ((thread-pond-lock pond))
    (decff (thread-pond-active-count pond))
    (loop for faction in factions do
	 (setf (thread-pond-payload pond)
	       (delq faction (thread-pond-payload pond))))
    (reclaim-factions-list factions)
    (tx:condition-variable-signal (thread-pond-count-cv pond))
    (tx:condition-variable-broadcast (thread-pond-queue-cv pond))))

;;; Interpreter thread worker
(defun-simple %faction-thread-thunk (pond)
  (with-symscale-worker-magic
      (loop
	 while
	   (let ((task (%get-next-faction-task pond))
		 (current-faction-global))
	     (when task
	       (setf current-faction-global (factions-list (task-faction task)))
	       (do-error-trapping
		   (with-safe-stack-eval-reentrancy
		       (catch-abort
			(1)
			(with-catch-handlers-for-stack-eval (t t)
			  (unwind-protect
			       (funcall (thread-pond-fun pond) task)
			    (%thread-pond-release-faction
			     current-faction-global pond))))))
	       t)))))

;;; Adds the element to pond's payload
;;; If there is already such element, waits until it is removed
(defun add-unique-elem-to-payload (elem pond)
  (tx:with-lock-held ((thread-pond-lock pond))
    (loop
       do
	 (if (memq elem (thread-pond-payload pond))
	     (tx:condition-variable-wait (thread-pond-queue-cv pond))
	     (progn
	       (gensym-push elem (thread-pond-payload pond))
	       (loop-finish))))))

;;; Removes the element from pond's payload
(defun remove-unique-elem-from-payload (elem pond)
  (tx:with-lock-held ((thread-pond-lock pond))
    (setf (thread-pond-payload pond)
	  (delq elem (thread-pond-payload pond)))
    (tx:condition-variable-broadcast (thread-pond-queue-cv pond))))

;;; Creates a thread pool for factions
(defun make-faction-pond ()
  (make-thread-pond
   (get-initial-worker-number)
   #'faction-pond-worker #'%faction-thread-thunk "FACTION POOL"))

;;; Schedules immediate tasks
(defun plan-immediate-task (tasks priority)
  (when tasks
    (thread-pond-enqueue
     other-factions-thread-pool
     (make-immediate-faction-task tasks priority))))

;;; Schedules tasks with potential reschedule
(defun plan-reschedule-task (task)
  (if (or (null (schedule-task-faction? task))
	  (eq (task-function-for-symbol service-workstation)
	      (schedule-task-function task)))
      (execute-task-and-reschedule task)
      (thread-pond-enqueue
       other-factions-thread-pool
       (make-reschedule-faction-task task)))
  task)

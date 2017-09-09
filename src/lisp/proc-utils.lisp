;; -*- Mode:Lisp; Package: AB; Base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module PROC-UTILS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard



;;;; Forward References




;;; In PROC-COMP

(declare-forward-reference compile-procedure-definition function)


;;; In G2-RPC1

(declare-forward-reference remote-procedure-argument-description-function
			   function)
(declare-forward-reference abort-outgoing-remote-procedure-call function)
(declare-forward-reference remote-procedure-call-being-aborted function)

;;; In DISPLAYS

(declare-forward-reference clear-event-detectors function)

;;; In STACK-UTILS

(declare-forward-reference generate-standard-error-message function)
(declare-forward-reference execute-computation-instance function)

;;; In STACK-INST

(declare-forward-reference open-wake-up-collection-function function)

;;; In G2DS

(declare-forward-reference g2-to-g2-data-interface-p-function function)

;;; In G2-GSI

(declare-forward-reference gsi-interface-p-function function)

;;; In INSTALL

(declare-forward-reference analyze-compiled-items-for-consistency function)

;;; In G2-RPC2

(declare-forward-reference
  g2-rpc-object-handed-off-to-user-p-function function)

(declare-forward-reference get-item-from-local-handle function)

;;; In STACK-KERN

(declare-forward-reference
  registered-and-active-default-error-handler-p function)
(declare-forward-reference
  pass-loop-check-for-user-defined-default-error-handler-p function)
(declare-forward-reference
  pass-loop-check-to-write-error-to-logbook-p function)
(declare-forward-reference
  invoke-user-defined-default-error-handler function)
(declare-forward-reference
  set-dynamic-breakpoint-internal function)

;;; To JAVA3

#+java-export-facilities
(declare-forward-reference analyze-export-info-for-parsability function)

(declare-forward-reference
  code-body-invocation-exit-breakpoint-context-message function)

(declare-forward-reference block-can-be-inlined-p function)
(declare-forward-reference set-permanent-and-propagate function)
(declare-forward-reference make-transient-item function)
(declare-forward-reference explanation-related-features-enabled-func? function)

;; In QUERIES
(declare-forward-reference free-references-from-procedure function)
(declare-forward-reference extract-inlined-procedures-from-free-reference-vector
			   function)

;; In GRAMMAR2
(declare-forward-reference convert-class-qualified-list-to-keyword-symbol
			   function)

;; In G2-BPEL
(declare-forward-reference g2gl-call-invocation-p-function function)
(declare-forward-reference handle-g2gl-call-invocation-error function)

;; In COMMANDS2
(declare-forward-reference clone-of function)


;;;; Procedures Run Time Environment



;;; The PROC-UTILS module contains documentation and code for handling the
;;; run-time execution of procedures.  The kernel for procedures is structured
;;; as follows.

;;; When a procedure is compiled, its code is split up into several code bodies.
;;; When a procedure has the possibility of portions of it running in parallel,
;;; those portions are split out into separate code bodies.  These code bodies
;;; are numbered, there is always at least one, and this one (code body zero) is
;;; the starting point for the procedure invocation.  When a procedure is run,
;;; an instance of the class procedure-invocation is created to represent that
;;; invocation of the procedure.  (Procedure invocations are now gonna be
;;; structures.  Yee ha!  -jra 11/30/90) This procedure-invocation contains an
;;; instance of the structure code-body-invocation.  It is actually code body
;;; invocations which are executed, by execute-code-body-invocation.  They
;;; contain the environment of local name bindings, the program counter, and
;;; pointers to the calling and called code-body-invocations.  Note that there
;;; is no global "stack" data structure.  The stack is made up of linked code
;;; body invocations, and their individual environments.  Pointers are also kept
;;; between calling and called procedure invocations, but these are more for the
;;; kb developer's viewing pleasure than for the run-time use of the procedure
;;; kernel.  (A graphic stack debugger for procedures is in the works.) There is
;;; a system variable, top-level-procedure-invocations, which contains a list of
;;; the procedure invocations which have been started.  This is the list of the
;;; bases all procedure stacks.

;;; The allocation of CPU resources to procedures is handled as follows.  For
;;; each priority there is at most one current task (in the
;;; schedule-current-task sense).  It will be scheduled if there are any
;;; procedures which currently need processing at that priority.  Since
;;; code-body-invocations are the things which are actually executed at run
;;; time, scheduling is all done with code-body-invocations, not
;;; procedure-invocations.  There is one queue of code-body-invocations needing
;;; processing for each priority, and there is one further queue of
;;; code-body-invocations needing processing immediately.

;;; The queues for each priority are the queues of code-body-invocations which
;;; are scheduled to receive processing at that priority.  The second, immediate
;;; queue, is a queue of code-body-invocations which need processing before this
;;; task can return to the scheduler.  The immediate queue will have elements
;;; added to it by procedure activities which are guaranteed to execute without
;;; wait states.  For example, when one procedure calls another, it does so by
;;; adding the code-body-invocation of code-body zero of the called procedure to
;;; the immediate queue, and the calling procedure (actually, its
;;; code-body-invocation) exiting its execution without rescheduling itself for
;;; processing.  When the called code body invocation executes a return
;;; statement, this pushes values back into the environment of the caller,
;;; schedules the caller code-body-invocation for immediate execution, and then
;;; deletes itself.  This style of execution handling is done so that control
;;; may always be retained at the top level (i.e.  procedure calls do not
;;; recurse on the Lisp stack), and can be done since the procedures stack is a
;;; G2 data structure.  When a procedure wants to schedule itself for some time
;;; in the future (as a result of a "WAIT FOR 5 MINUTES" statement for example)
;;; it does schedule a true "scheduler" task for the given time.  The job of
;;; that task is to add the code body invocation to the queue of invocations
;;; needing processing at the appropriate priority.






;;;; Procedure Invocation Optimizations



;;; This section contains a discussion of optimizations of procedure invocations
;;; through machine compilation and "link-snapping" between compiled code bodies
;;; and called procedures.

;;; Because these facilities need to be capable of being interrupted at any
;;; level within the graph and wait for a condition, the stack must be a data
;;; structure within our system and may not usually use the Lisp stack.  This
;;; will make procedure invocation somewhat inefficient.  The Lisp stack may be
;;; used only in situations where it can be shown that the procedure invocations
;;; being called have no way of entering a wait state within their recursive
;;; depth.  This kind of an optimization will be important for our system if we
;;; are to compete performance-wise with C.  If it can be shown that no wait
;;; states are possible within a procedure's recursive descent and that the
;;; procedure has no identity features, then we also do not need to provide the
;;; data structure tracking necessary to create a display of the stack.  This is
;;; true since it will be impossible to stop the procedure from executing while
;;; within that invocation, and so nothing could possibly attempt to display the
;;; stack during that interval.  So, the stack should be structured as a
;;; directed graph in the typical case, but when it can be proven that a
;;; function will not wait, then it need have no explicit representation in our
;;; system.  This implies two types of procedure invocation functions in the
;;; system.

;;; The internal structure of a single procedure invocation is affected by the
;;; requirement that we run within a single stack without the possibility of
;;; using interrupts.  This means that a wait state may not be embedded within a
;;; block of code implementing a procedure body.  So, procedures bodies need to
;;; be split into sections of code which themselves will not have internal wait
;;; states.  A vector of code bodies then will represent the code for a
;;; procedure, and branches can be made between these bodies by them returning
;;; an integer naming the next code body to execute.  A wait state can be
;;; entered by a code body producing (via side effect) some structure or
;;; scheduled task which will "wake up" this procedure, and it returning a
;;; negative integer.  The absolute value of the returned integer is the next
;;; code body to execute upon reactivation, and the fact that it should not be
;;; executed immediately is represented by the number being negative.  This
;;; style of returned value interpretation is proposed so as to avoid the
;;; performance loss of multiple value returns.  Before returning a code body
;;; should set up some scheduled task or other facility which will eventually
;;; reactivate the procedure.  If it is a purely time-dependent wait state, a
;;; task should be scheduled.  If it is a COLLECT DATA or condition-based wait
;;; state, then some waiting mechanism should be invoked before returning, and
;;; this waiting mechanism may need to be given a pointer to the environment of
;;; this procedure.






;;;; Procedure Conses, or Proc-cons



;; The actual defconser was moved to RPC-COMMON1 for dependency reasons.
;; 8dec93 paf!, jh


;;; In procedure evaluation, alists are formed using proc conses and temporary
;;; constants.  The function `reclaim-proc-alist-head-and-temporary-constants'
;;; reclaims portions of those alists.  Note the the passed tail must be a cons
;;; which is some cdr of the given alist, or this function will loop forever.

(defun reclaim-proc-alist-head-and-temporary-constants (alist tail)
  (loop for trailer? = nil then alist-cons
	for alist-cons = alist then (cdr alist-cons)
	until (eq alist-cons tail)
	for value-cons = (car alist-cons)
	for temporary-constant? = (cdr value-cons)
	do
    (reclaim-if-temporary-constant temporary-constant?)
    (reclaim-proc-cons-macro value-cons)
	finally
	  (when trailer?
	    (reclaim-proc-list-given-tail alist trailer?))))




;;; The function `reclaim-proc-alist' takes an alist and reclaims all the
;;; procedure conses and temporary constants within it.

(defun reclaim-proc-alist (alist)
  (loop for trailer? = nil then alist-cons
	for alist-cons = alist then (cdr alist-cons)
	while alist-cons
	for value-cons = (car alist-cons)
	for temporary-constant? = (cdr value-cons)
	do
    (reclaim-if-temporary-constant temporary-constant?)
    (reclaim-proc-cons-macro value-cons)
	finally
	  (when trailer?
	    (reclaim-proc-list-given-tail alist trailer?))))




;;; The macro `delete-proc-element-macro' removes an element from a list,
;;; returning the resulting list.  This is exactly the same operation as
;;; delete-proc-element, but done inline.

(defmacro delete-proc-element-macro (item list)
  (let ((item-to-delete (gensym))
	(original-list (gensym)))
    `(let ((,item-to-delete ,item)
	   (,original-list ,list))
       (if ,original-list
	   (if (eq (car-of-cons ,original-list) ,item-to-delete)
	       (prog1 (cdr-of-cons ,original-list)
		 (reclaim-proc-cons-macro ,original-list))
	       (loop for trailer = ,original-list then cons
		     for cons on (cdr-of-cons ,original-list)
		     do
		 (when (eq (car-of-cons cons) ,item-to-delete)
		   (setf (cdr trailer) (cdr-of-cons cons))
		   (reclaim-proc-cons-macro cons)
		   (loop-finish))
		     finally (return ,original-list)))
	   nil))))





;;;; Procedure Evaluation




;;; The special variable `procedure-alist' is currently used to hold alists
;;; bound for arguments of called user defined functions.  This will eventually
;;; be removed when we implement function compilations which can reference
;;; vectorized environments.

;;; Note that it is legal for procedure evaluators to initiate non-local exits,
;;; and that conses and temporary constants bound on the alists should not
;;; become garbage when this occurs.  The handler of the non-local exits (i.e.
;;; the catch for :stack-error in stack-eval) is responsible for reclaiming
;;; anything bound on this list and that all evaluator users can only setq this
;;; variable, not bind it in a let.

(defvar procedure-alist nil) ; not used any more.








;;; The global property `procedure-evaluator' is used to associate procedure
;;; evaluation implementation functions with the symbol which names an
;;; evaluator.

(def-global-property-name procedure-evaluator)




;;; The special variable `evaluating-simulator-procedure?' will be bound to either
;;; T or a model definition (see invoke-simulation-procedure) if a simulation
;;; procedure is being evaluated, and to NIL otherwise.

(def-system-variable evaluating-simulator-procedure? proc-utils nil)




;;; The function `procedure-eval' is the top level function for the procedure
;;; evaluator.  It dispatches to the appropriate evaluator for the current
;;; procedure execution mode, stored in evaluating-simulator-procedure.
;;; Arithmetic errors are "caught" using the wrapper around procedure-evaluate
;;; and also is "caught" in procedure-sim-eval.

(defvar datum-type nil)






;;;; Procedure Code Bodies




;;; The structure `code-body' contains a p-code vector of instructions, and
;;; other data required to generate environments while producing a code body
;;; invocation.

;;; The surrounding-code-body-number?  slot is either NIL or contains the number
;;; of a code body which provides a surrounding environment for an invocation of
;;; this code body.  The function surrounding-code-body?  takes a code body, and
;;; returns the code body whose number is stored in this slot, if any.

;;; The environment-description slot contains
;;; a vector after compilation, and a list during compilation. During compilation,
;;; Each variable
;;; description is a phrase cons list whose car is the variable-name
;;; (possibly NULL for internally generated variable spots) and whose cdr is a
;;; property list of characteristics for this variable.  The current list of
;;; properties contain:   :type property giving a more specific type than
;;; ANY-TYPE for this variable, and a :return-value property specifying the
;;; that this var-spot receives returned values and giving the first, second,
;;; etc. returned value that this spot receives.
;;; At the end of compilation this is converted into a vector which is 2x the
;;; length of the list. The vector has the pattern NAME, INFORMATION
;;; NAME,INFORMATION... The information is assumed to be type information unless
;;; it is a list the car of which is :return-type. This was done as a space saving
;;; measure. Large kbs were using a large amount of space in this data structure

(def-class (code-body dependent-frame)
  (procedure-definition-of-code-body nil vector-slot system save)
  (surrounding-code-body-number? nil vector-slot system save)
  (return-value-position nil vector-slot system save)
  (maximum-received-value-count nil vector-slot system save)
  (environment-length nil vector-slot system save)
  (environment-description nil vector-slot system save)
  (code-body-byte-code-body nil vector-slot system save)
  (code-body-entry-points nil vector-slot system save)
  (code-body-error-handler-spec? nil vector-slot system save))

(def-slot-value-reclaimer code-body-entry-points (entry-point-array)
  (when entry-point-array (reclaim-managed-array entry-point-array)))

(defun-simple procedure-definition-of-code-body-function (code-body)
  (procedure-definition-of-code-body code-body))

(defun-simple code-body-byte-code-body-function (code-body)
  (code-body-byte-code-body code-body))

(defun-simple code-body-entry-points-function (code-body)
  (code-body-entry-points code-body))

;;; As part of the old-evaluators, the p-code-array slot of code bodies has
;;; beeen removed.  It was last used in 1992.  -jra 10/27/96

(def-absent-slot-putter p-code-array (code-body p-code-array)
  (declare (ignore code-body))
  (when p-code-array
    (loop for index from 0 below (managed-array-length p-code-array) do
      (reclaim-slot-value (managed-svref p-code-array index)))
    (reclaim-managed-array p-code-array)))

;;; Within procedures the actual objects which will be executed are `code body
;;; invocations'.  Each procedure may have several code bodies, and in the case
;;; of IN-PARALLEL forms, a single code body may have several invocations
;;; executing concurrently.  A code body invocation contains a pointer to its
;;; code body, a current program counter within that code body, an environment
;;; for this invocation, the procedure invocation containing this code body, a
;;; proc-cons list of calling code body invocations (if any), a proc-cons list
;;; of called code body invocations (if any), a code body invocation queue entry
;;; (if any), and a task for code body wake up (if any).

(def-structure (code-body-invocation (:include computation-instance)
				     (:predicate code-body-invocation-internal-p))
  code-body-of-invocation
  (code-body-invocation-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  code-body-invocation-priority
  procedure-invocation-of-code-body
  code-body-caller
  called-code-bodies
  things-this-code-body-invocation-is-interested-in
  code-body-invocation-postponed-clean-ups
  code-body-invocation-event-detectors
  ;; See NOTE1
  ri-completion-notification-collection-back-pointer
  (invocations-waiting-for-lock-held-by-this-invocation nil)
  (invocation-holding-lock-this-is-waiting-for nil)
  (reference-to-item-to-lock nil)
  ;; See NOTE2
  (code-body-invocation-thread nil))

;; NOTE1
;;
;; Since currently only procedure-invocations and branches of a "do in
;; parallel" that result in a code-body-invocation can wait for rule
;; invocations or focuses to complete, this slot lives here.  It will hold a
;; ri-completion-notification-collection? which is shared with the
;; rule-instances being waited upon..  See that slot on rule-instance for
;; details.  This is simply a back-pointer to support cleaning up
;; code-body-invocations that get aborted or (in the future) time out while
;; they are waiting for rules to complete.  Note that there can only ever be
;; one per code-body-invocation because either you have a procedure-invocation
;; that is doing multiple waits sequentially, in which case only one "ruleset"
;; will be waiting, or you have a do in parallel, that starts up a separate
;; code-body-invocation for each branch, and those will be the things that are
;; waiting.  -dkuznick, 8/15/05

;;; NOTE2
;;;
;;; Threads are used by the locking mechanism. A synchronized method is
;;; allowed to execute as long as the lock is held by an invocation in
;;; the same thread. This allows one synchronized method to call another
;;; method on the same item without self-deadlock. A thread is defined
;;; as a chain of code-body-invocations, each of which calls the previous
;;; one via call, dependent-call, or an on-error block. Start,
;;; and calls to "do in parallel" and "do in parallel until one completes"
;;; establish new threads. Rather than have explicit thread objects, which
;;; led to performance problems, we represent a thread by the first
;;; code-body-invocation in the thread that acquires a lock. This is safe,
;;; because when this invocation is closed, all other code bodies below it
;;; in the call chain will also be closed. Code body invocations above this
;;; one in the call chain will not have a value in the
;;; code-body-invocation-thread slot, but that's OK, because the slot is only
;;; used when testing to see if a lock needs to be acquired, to see if the
;;; lock is held by an invocation higher on the same call chain, so as long
;;; as the value is consistent for all invocations on a call chain that hold
;;; a lock, everything will be correct. -alatto, 3/29/07


(def-substitution-macro code-body-invocation-p (code-body)
  (when (simple-vector-p code-body)
    (let ((type-name (g2-type-name-of-named-simple-vector code-body)))
      (or (eq type-name (intern-unique-def-structure-symbol-name 'code-body-invocation))
	  (eq type-name (intern-unique-def-structure-symbol-name 'procedure-invocation))))))

;;; The macro `base-code-body-invocation-p' takes a code body invocation and
;;; returns whether or not this is the base code body invocation for its
;;; procedure invocation.

(defmacro base-code-body-invocation-p (code-body-invocation)
  ;; always true, unless it's a code-body-invocation
  `(not (code-body-invocation-internal-p ,code-body-invocation)))

(defmacro base-code-body-invocation (procedure-invocation)
  `,procedure-invocation)


;; AC 9-03-91. Added this for reference in SETS

(defun-simple procedure-invocation-of-code-body-function (code-body)
  (procedure-invocation-of-code-body code-body))

;; For reference in DEBUG
(defun-simple code-body-of-invocation-function (code-body)
  (code-body-of-invocation code-body))


;; rdf 2/3/94 need a function for use back in sets

(defun-simple code-body-invocation? (item)
  (code-body-invocation-p item))


;;; `need-to-wait-after-attempting-rule-scheduling' is an abstraction on top of the
;;; ri-completion-notification-collection-back-pointer slot.
;;;
;;; it must be a function (used by stack instruction)  --binghe, June 2016

(defun-simple need-to-wait-after-attempting-rule-scheduling
    (code-body-invocation)
  (ri-completion-notification-collection-back-pointer
    code-body-invocation))


(defun-substitution-macro scheduled-rule-instances-to-be-waited-on-p
    (completion-notification-collection)
  (car completion-notification-collection))


(defun-void remove-completion-notification-collection-if-empty
    (code-body-invocation)
  (let ((back-pointer (need-to-wait-after-attempting-rule-scheduling
			code-body-invocation)))
    (unless (scheduled-rule-instances-to-be-waited-on-p back-pointer)
      (reclaim-eval-list back-pointer)
      (setf (ri-completion-notification-collection-back-pointer
	      current-computation-instance)
	    nil))))

;;; `set-up-completion-notification-collection' is an abstraction for setting up
;;; the contents of the ri-completion-notification-collection-back-pointer
;;; slot.  It returns the new completion-notification-collection.

(defun-simple set-up-completion-notification-collection (code-body-invocation)
  (setf (ri-completion-notification-collection-back-pointer
	  code-body-invocation)
	(eval-list nil code-body-invocation)))



;;; The structure `remote-procedure-call' is used to store calls into or out of
;;; G2 across machine boundaries.  It includes all slots from code body
;;; invocations.

(def-structure (remote-procedure-call
		 (:constructor make-remote-procedure-call-internal
		  (remote-procedure-identifier-of-call
		    remote-procedure-declaration-of-call
		    remote-procedure-call-icp-socket
		    remote-procedure-call-icp-interface))
		 (:include code-body-invocation))
  remote-procedure-identifier-of-call
  remote-procedure-declaration-of-call
  remote-procedure-call-icp-socket
  remote-procedure-call-icp-interface
  (remote-procedure-call-start-index -1))

(defun-simple make-incoming-remote-procedure-call
    (remote-procedure-identifier-of-call
      remote-procedure-call-icp-socket)
  (let ((rpc (make-remote-procedure-call-internal
	       remote-procedure-identifier-of-call
	       nil
	       remote-procedure-call-icp-socket
	       nil)))
    (setf (code-body-of-invocation rpc) nil)
    (reclaim-frame-serial-number (code-body-invocation-frame-serial-number rpc))
    (setf (code-body-invocation-frame-serial-number rpc) nil)
    (setf (code-body-invocation-priority rpc) nil)
    (setf (procedure-invocation-of-code-body rpc) nil)
    (setf (code-body-caller rpc) nil)
    (setf (called-code-bodies rpc) nil)
    (setf (things-this-code-body-invocation-is-interested-in rpc) nil)
    (setf (code-body-invocation-postponed-clean-ups rpc) nil)
    (setf (code-body-invocation-event-detectors rpc) nil)
    rpc))

(defun-simple reclaim-incoming-remote-procedure-call (remote-procedure-call)
  #+trace-invocations
  (check-free-code-body-invocation remote-procedure-call)
  (when (remote-procedure-call-p remote-procedure-call)
    (reclaim-remote-procedure-call remote-procedure-call)))

(defun-simple make-outgoing-remote-procedure-call
    (remote-procedure-identifier-of-call
      remote-procedure-declaration-of-call
      remote-procedure-call-icp-socket
      remote-procedure-call-icp-interface)
  (let ((rpc (make-remote-procedure-call-internal
	       remote-procedure-identifier-of-call
	       remote-procedure-declaration-of-call
	       remote-procedure-call-icp-socket
	       remote-procedure-call-icp-interface)))
    (setf (code-body-of-invocation rpc) nil)
    (setf (things-this-code-body-invocation-is-interested-in rpc) nil)
    (setf (code-body-invocation-postponed-clean-ups rpc) nil)
    (setf (code-body-invocation-event-detectors rpc) nil)
    rpc))

(defun-simple reclaim-outgoing-remote-procedure-call (remote-procedure-call)
  #+trace-invocations
  (check-free-code-body-invocation remote-procedure-call)
  (reclaim-remote-procedure-call remote-procedure-call))

(def-structure (system-rpc
		 (:constructor
		   make-system-rpc
		   (system-rpc-lisp-function
		     system-rpc-argument-types
		     system-rpc-return-types))
		 #+development
		 (:print-function print-system-rpc))
  (system-rpc-lisp-function nil)
  (system-rpc-argument-types nil)
  (system-rpc-return-types nil))

#+development
(defun print-system-rpc (system-rpc stream depth)
  (declare (ignore depth))
  (printing-random-object (system-rpc stream)
    (format stream "SYSTEM-RPC ~S"
	    (system-rpc-lisp-function system-rpc))))

#-chestnut-trans
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :procedure-invocations-using-binary-tree *features*))

;;; NOTE: when using binary-tree to replace a plain list, the key and value of tree
;;; should be both the previous list elements, so that exist LOOP path can be used
;;; directly. -- Chun Tian (binghe), April 2015.

#+procedure-invocations-using-binary-tree
(defun-simple procedure-invocation-hash (invocation)
  (sxhash-lisp-object invocation))

#+procedure-invocations-using-binary-tree
(eval-when (:compile-toplevel :load-toplevel :execute)
  #+ignore
  (def-skip-list-or-binary-tree procedure-invocations
    :constructor make-procedure-invocations
    :hash-function procedure-invocation-hash
    :reclaimer reclaim-procedure-invocations
    :clearer clear-procedure-invocations-table ; never used
    :max-level 20)	
  (def-hash-table procedure-invocations
    :constructor make-procedure-invocations
    :hash-function-or-macro procedure-invocation-hash
    :reclaimer reclaim-procedure-invocations
    :clearer clear-procedure-invocations-table ; never used
    :max-skip-list-level 20))

;;; The class `procedure' is used to create procedure definitions.
;;;
;;; The `initialize method for procedure' changes the frame status to
;;; incomplete if the procedure-definition slot is either nil or contains
;;; no-value as its translation.

(def-class (procedure
	     (item entity)
	     (foundation-class procedure) define-predicate
	     (class-export-comment
	       "Procedures provide a means of encoding multi-threaded, ~
                structured programs."))
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?)
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have a date. ~
authors: ([ name: symbol, date: gensym-time ] * ), ~
editor-grammar: struct, defining-class: item, writable: true
"))
  ;; This slot is used to help snapshots know when a procedure has been recompiled.
  ;; This is used to tell if annotation information is stale.  May want to expose
  ;; this so that users who use the source position info in error objects will be
  ;; able to do the same kind of stale checking. -dkuznick, 4/6/99
  (n-compiles-this-session 0 system do-not-save do-not-put-in-attribute-tables)
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame
    nil system (type nil) save
    (attribute-export-comment "Alias as procedure-name?"))
  (tracing-and-breakpoints nil lookup-slot system user-overridable save
			   (type tracing-and-breakpoints))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      90 90 
      ((outline (0 0) (90 0) (90 90) (0 90))
       (outline (12 12) (48 12) (48 24) (12 24))
       (outline (12 48) (48 48) (48 60) (12 60))
       (outline (42 30) (78 30) (78 42) (42 42))
       (outline (42 66) (78 66) (78 78) (42 78)))
      nil
      ;; later, maybe redo the icon in order to be able to eliminate
      ;;   the magnification; the goal is to have this be the same size
      ;;   as most other system icons (e.g. variables), 60 X 60, but
      ;;   we decided to do this after the icon was already designed
      ;;   for 90 X 90. (MHD 8/4/89)
      #.(convert-to-magnification-at-compile-time 2/3)
      #.(convert-to-magnification-at-compile-time 2/3)))
  (class-of-procedure-invocation
    nil (type class-of-procedure-invocation?)
    vector-slot system user-overridable save
    (attribute-export-comment
      "The name of a subclass of procedure-invocation (or procedure-invocation ~
       itself).  Within this procedure, the expression \"this ~
       procedure-invocation\" will return a unique instance of this class for ~
       this execution of this procedure."))
  (default-procedure-priority
    #.default-procedure-evaluation-priority
    (type priority) vector-slot system user-overridable save)
  (uninterrupted-procedure-execution-limit?
    default (type execution-interval?-or-default) vector-slot
    user-overridable system save)
  (argument-count
    0 vector-slot system save
    (attribute-export-comment
      "Export: integer, writable = false"))
  (argument-list-description
    nil vector-slot system save
    (attribute-export-comment 
      "Export list of type descriptors, writable = false"))
  (returned-values-description
    nil vector-slot system save
    (attribute-export-comment 
      "Export list of type descriptors, writable = false"))
  (procedure-invocations
    nil vector-slot system do-not-save
    (attribute-export-comment
      "Export - debugging, process monitoring???"))
  (procedure-definition
    nil (type procedure-definition text procedure) vector-slot
    system save do-not-identify-in-attribute-tables select-changes
    (attribute-export-comment "Export as text."))
;  (code-bodies-3.0-alpha nil vector-slot system save do-not-clone)
  (procedure-code-bodies-3.0-beta nil vector-slot system save do-not-clone)
  ;; The procedure-flags is initially 1 because, by default, we assume that the
  ;; procedure needs validation.  This is flag is updated as the procedure is
  ;; compiled.  Note that the default is particularly needed for pre-4.0 KB's
  ;; that have not yet been recompiled.
  (procedure-flags
    1 vector-slot system save
    (attribute-export-comment "Add attribute-mimics for individual flags."))
  (parse-results? nil system save)
  (md5-identifier? nil system save)
  (dynamic-breakpoint-settings nil system save)
  (has-empty-code-body? nil system save))

(defun procedure-definition-function (procedure)
  (procedure-definition procedure))

(defun-simple has-empty-code-body-p (procedure)
  (has-empty-code-body? procedure))

;;; New interface for add/delete elements from procedure-invocations slot.
;;; NOTE: the macros here are too simple, cannot handle side-effects!

#+procedure-invocations-using-binary-tree
(defun-simple push-one-procedure-invocation (invocation procedure)
  (let ((old-tree? (procedure-invocations procedure)))
    ;; The slot `procedure-invocations' is a `do-not-save' slot, therefore most of the
    ;; cases (loading old KBs) it's a NIL slot, unless user creates a new procedure.
    (unless old-tree?
      (let ((new-tree (make-procedure-invocations)))
	#+SymScale
	(unless (compare-and-swap (procedure-invocations procedure) old-tree? new-tree)
	  ;; if other threads do the same thing first, reclaim our allocation.
	  (reclaim-procedure-invocations new-tree))
	#-SymScale
	(setf (procedure-invocations procedure) new-tree)))
    ;; set both key and value to the same thing: invocation
    (setf (get-procedure-invocations invocation (procedure-invocations procedure))
	  invocation)))

#-procedure-invocations-using-binary-tree
(defmacro push-one-procedure-invocation (invocation procedure)
  `(proc-push ,invocation (procedure-invocations ,procedure)))

#+procedure-invocations-using-binary-tree
(defun-simple delete-one-procedure-invocation (invocation procedure)
  (let ((invocations (procedure-invocations procedure)))
    #+(and development (not no-misterious-checks-in-dev))
    (unless (get-procedure-invocations invocation invocations)
      (error "no invocation to delete"))
    (delete-procedure-invocations invocation invocations)))

#-procedure-invocations-using-binary-tree
(defmacro delete-one-procedure-invocation (invocation procedure)
  `(setf (procedure-invocations ,procedure)
	 (delete-proc-element-macro ,invocation (procedure-invocations ,procedure))))

(def-virtual-attribute inlined-calls
    ((class procedure) (or (sequence symbol) (no-item)) nil)
  :event-updates nil
  :initial ((procedure) (declare (ignore procedure)) nil)
  :getter ((proc)
	   (let* ((free-references? (free-references-from-procedure proc))
		  (name-list?
		    (loop for ref in free-references?
			  nconcing
			  (let ((denotations?
				  (extract-inlined-procedures-from-free-reference-vector ref)))
			    (loop for d in denotations?
				  collect (if (consp d)
					      (prog1
						  (convert-class-qualified-list-to-keyword-symbol
						d)
						(reclaim-gensym-list d))
					      d)
				    using eval-cons
				  finally (reclaim-gensym-list denotations?))))))
	     (reclaim-gensym-list free-references?)
	     (allocate-evaluation-sequence name-list?))))


(defun-simple procedure? (block)
  (procedure-p block))

(eval-when (:compile-toplevel :load-toplevel :execute)

(define-loop-path procedure-invocation
;  #+(and procedure-invocations-using-binary-tree skip-list)
;  expand-skip-list-or-binary-tree-value-loop-iterator
;  #+(and procedure-invocations-using-binary-tree (not skip-list))
;  expand-binary-tree-value-loop-iterator
  #+procedure-invocations-using-binary-tree
  expand-hash-value-loop-iterator
  #-procedure-invocations-using-binary-tree
  expand-list-loop-iterator
  (of))

) ; eval-when

#+procedure-invocations-using-binary-tree
(def-slot-value-reclaimer procedure-invocations (invocations procedure)
  (atomic-exchange (procedure-invocations procedure) nil)
  (reclaim-procedure-invocations invocations))

(defun argument-list-description-function (procedure)
  (argument-list-description procedure))

(defun returned-values-description-function (procedure)
  (returned-values-description procedure))

(defun-simple n-compiles-this-session-function (procedure)
  (n-compiles-this-session procedure))

;; Moved the procedure initialize class-method to later in in this module.  It
;; needs to be after the definition of procedure-code-bodies-slot-name.
;; - cpm, 8/16/94


(define-slot-alias uninterrupted-procedure-execution-limit uninterrupted-procedure-execution-limit?
  procedure)


;;; The procedure-definition slot of a procedure is aliased as TEXT.  See
;;; also the slot box-translation-and-text of text boxes, which has a similar
;;; alias.

(define-slot-alias text procedure-definition procedure)

;; Added this alias 6/17/91.  Note that in 2.0, 2.1 there was no
;; "official" way to access the text, but I think you might have been
;; able to use procedure-definition, if you knew about it.  (MHD 6/17/91)



;;; The following are accessors and ways of setting procedure-flags.  The
;;; procedure flags are currently procedure-can-invalidate-environment,
;;; procedure-contains-wait-state, procedure-contains-indirect-procedure-
;;; call, and procedure-call-without-validated-environment.

;;; `Procedure-can-invalidate-environment-p' indicates if a procedure contains a
;;; statement, such as delete, transfer, or deactivate, that can invalidate a
;;; procedure environment.  The environment is invalidated, for example, when an
;;; item that is held in a local variable can no longer be referenced.

;;; `Procedure-contains-wait-state-p' indicates if a procedure contains a
;;; statement, such as wait (polled-wait and wait-for-interval),
;;; allow-other-processing, and collect-data, that allows wait states.  Note
;;; that this flag does not count the call statement, even though it does allow
;;; wait states.  Uses of the call statement are noted through the indirect-call
;;; flag and free-references.

;;; `Procedure-contains-indirect-procedure-call-p' indicates if a procedure
;;; contains a call to a procedure whose name cannot be determined at
;;; compile-time.  Note that direct uses of the call statement are not recorded
;;; here, but is recorded elsewhere using free-references.

;;; `Procedure-call-without-validated-environment-p' indicates if a procedure
;;; contains a call to another procedure (or system-procedure Lisp function)
;;; that cannot guarantee that its environment will remain valid.



(def-substitution-macro procedure-can-invalidate-environment-p (procedure)
  (/=f 0 (logandf (procedure-flags procedure)
		  procedure-can-invalidate-environment-mask)))

(def-substitution-macro procedure-contains-wait-state-p (procedure)
  (/=f 0 (logandf (procedure-flags procedure)
		  procedure-contains-wait-state-mask)))

(def-substitution-macro procedure-contains-indirect-procedure-call-p (procedure)
  (/=f 0 (logandf (procedure-flags procedure)
		  procedure-contains-indirect-procedure-call-mask)))

(def-substitution-macro procedure-call-without-validated-environment-p
			(procedure)
  (/=f 0 (logandf (procedure-flags procedure)
		  procedure-call-without-validated-environment-mask)))


(def-substitution-macro set-procedure-can-invalidate-environment (procedure)
  (setf (procedure-flags procedure)
	(logiorf (procedure-flags procedure)
		 procedure-can-invalidate-environment-mask)))

(def-substitution-macro set-procedure-contains-wait-state (procedure)
  (setf (procedure-flags procedure)
	(logiorf (procedure-flags procedure)
		 procedure-contains-wait-state-mask)))

(def-substitution-macro set-procedure-contains-indirect-procedure-call (procedure)
  (setf (procedure-flags procedure)
	(logiorf (procedure-flags procedure)
		 procedure-contains-indirect-procedure-call-mask)))

(def-substitution-macro set-procedure-call-without-validated-environment
			(procedure)
  (setf (procedure-flags procedure)
	(logiorf (procedure-flags procedure)
		 procedure-call-without-validated-environment-mask)))



;;; The function `procedure-environment-always-valid-p' checks the
;;; procedure-flags related to procedure environments and indicates if the
;;; environment is guaranteed to be valid.  If this predicate returns true, the
;;; procedure environment does not need to be validated during the procedure's
;;; execution.

(def-substitution-macro procedure-environment-always-valid-p (procedure)
  (=f (logandf procedure-invalidates-environment-union-mask
	       (procedure-flags procedure))
      0))



;;; The function `clear-procedure-compilation-frame-flags' clears those
;;; procedure-flags that relate to compilation and should be cleared at the
;;; start of the compilation.

;; Note that currently all procedure-flags relate to compilation.  - cpm,
;; 2/23/93.

(defun clear-procedure-compilation-frame-flags (procedure)
  (setf (procedure-flags procedure) (logandc2f (procedure-flags procedure) 1))
  (setf (procedure-flags procedure) (logandc2f (procedure-flags procedure) 2))
  (setf (procedure-flags procedure) (logandc2f (procedure-flags procedure) 4))
  (setf (procedure-flags procedure) (logandc2f (procedure-flags procedure) 8)))


;;; the following are sets of functions and macros to support conversion from
;;; list-type variable descriptions to vector type variable descriptions.
;;; the size  of the vector is 2x the number of variables that it describes.
;;; The vector elements are paired. elt[0] = name, elt[1] = desciption of elt[0] etc.
;;; if the description consists only of the type of the element (the overwhelimingly
;;; most common case) the element just consists of that type, otherwise it consists
;;; of a list the CAR of which is :general-description and the CDR of which is a
;;; p-list of descriptions.



(defmacro var-whole-type-description-from-index (description-vector index)
  `(managed-svref ,description-vector (+f (*f ,index 2) 1)))

(defmacro var-type-from-index (description-vector index)
  (let ((value (gensym)))
    `(let ((,value (var-whole-type-description-from-index ,description-vector ,index)))
       (when (and (consp ,value)
		  (eq (car ,value) ':general-description))
	 (setq ,value (getfq (cdr ,value) :type)))
       ,value)))

(defmacro set-var-type-from-index (description-vector index value)
  `(setf (var-whole-type-description-from-index ,description-vector ,index) ,value))


(defun var-type-from-index-function (description-vector index)
  (var-type-from-index description-vector index))


(defmacro var-name-from-index (description-vector index)
  `(managed-svref ,description-vector (*f ,index 2)))

(defmacro var-name-from-index? (description-vector index)
  (let ((description (gensym))
	(actual-index (gensym)))
    `(let ((,description ,description-vector)
	   (,actual-index (*f ,index 2)))
       (when (< ,actual-index (managed-array-length ,description))
	 (managed-svref ,description-vector ,actual-index)))))


(defun collect-types-into-list-using-phrase-conses (description-vector)
  (when description-vector
    (loop for index from 1 below (managed-array-length description-vector) by 2
	  for value = (managed-svref description-vector index)
	  for parsed-value = (if (and (consp value)
				      (eq (car value) ':general-description))
				 (getfq (cdr value) :type)
				 value)
	  collect parsed-value using phrase-cons)))

(defun collect-description-into-list-using-phrase-conses (description-vector)
  (when description-vector
    (let ((description-list nil))
      (loop with index = 0
	    while (< index (managed-array-length description-vector))
	    with name and description and copied-description
	    do
	(setq name (managed-svref description-vector index))
	(incff index)
	(setq description (managed-svref description-vector index))
	(incff index)
	(cond ((and (consp description)
		    (eq (car description) ':general-description))
	       (setq copied-description
		     (copy-tree-using-phrase-conses (cdr description)))
	       (phrase-push name copied-description))
	      ((consp description)
	       (setq copied-description
		     (copy-tree-using-phrase-conses description))
	       (phrase-push name copied-description))
	      (t
	       (setq  copied-description (phrase-list name description))))
	(cond (description-list
	       (nconc description-list (phrase-list copied-description)))
	      (t
	       (setq description-list (phrase-list copied-description)))))
      description-list)))

(defun collect-types-into-list-using-gensym-conses (description-vector)
  (when description-vector
    (loop for index from 1 below (managed-array-length description-vector) by 2
	  for value = (managed-svref description-vector index)
	  for parsed-value = (if (and (consp value)
				      (eq (car value) ':general-description))
				 (getfq (cdr value) :type)
				 value)
	  collect parsed-value using gensym-cons)))

(defmacro var-general-description-from-index (description-vector index)
  (let ((value (gensym)))
    `(let ((,value (managed-svref ,description-vector (+f (*f ,index 2) 1))))
       (when (and (consp ,value) (eq (car ,value) ':general-description))
	 (setq ,value (cdr ,value))
	 ,value))))


(defun-simple var-count (description-vector)
  #+development
  (unless (or (null description-vector)
	      (managed-array-p description-vector))
    (cerror "Continue" "~a should be a simple-vector" description-vector))
  (cond (description-vector
	 (floorf-positive (managed-array-length description-vector) 2))
	(t
	 0)))

  
  



;;; The macro `code-bodies' can be used to access the slot containing code
;;; bodies compiled for this version, but change-slot-value must be called with
;;; the correct slot name.  The parameter `procedure-code-bodies-slot-name'
;;; holds the symbol naming the slot.  It is used by the procedure compiler when
;;; installing compiled code bodies.

;; Changed today to update to the new stack evaluator compilations.  -jra
;; 8/25/91

(defmacro code-bodies (procedure)
  `(procedure-code-bodies-3.0-beta ,procedure))

(defun-simple code-bodies-function (procedure)
  (code-bodies procedure))

(defparameter procedure-code-bodies-slot-name 'procedure-code-bodies-3.0-beta)

(define-slot-alias disassembled-code procedure-code-bodies-3.0-beta)

(def-slot-putter procedure-code-bodies-3.0-beta
		 (procedure new-code-bodies initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p procedure))
	     loading-kb-p)
    (reclaim-slot-value new-code-bodies)
    (setq new-code-bodies nil)
    (note-frame-with-compilation-removed procedure))
  (setf (code-bodies procedure) new-code-bodies)
  new-code-bodies)

(def-absent-slot-putter code-bodies-3.0-alpha (procedure old-code-bodies)
  (declare (ignore procedure))
  (reclaim-slot-value old-code-bodies)
  nil)

(def-absent-slot-putter procedure-free-references (procedure old-references)
  (declare (ignore procedure))
  (reclaim-slot-value old-references)
  nil)


;;; GENSYMCID-1324: Remove "optimize-procedure-code?" (proc-opt) feature from G2 code base

(defvar list-of-previously-optimized-procedures nil)

(def-absent-slot-putter optimize-procedure-code? (procedure previously-optimized?)
  (when previously-optimized?
    (gensym-push procedure list-of-previously-optimized-procedures))
  nil)

(def-post-loading-function (recompile-previously-optimized-procedures :once-only t)
  (loop for procedure in list-of-previously-optimized-procedures do
    (recompile-item procedure))
  (reclaim-gensym-list list-of-previously-optimized-procedures)
  (setq list-of-previously-optimized-procedures nil))

(def-slot-putter parse-results? (procedure old-parse initializing?)
  (when (and initializing?
	     (or (not (compilations-up-to-date-p procedure))
		 (not (block-can-be-inlined-p procedure))
		 (not (cached-parses-up-to-date-p procedure)))
	     loading-kb-p)
    (reclaim-slot-value old-parse)
    (setq old-parse nil))
  (setf (parse-results? procedure) old-parse)
  old-parse)

(def-slot-putter md5-identifier? (procedure wide-string? initializing?)
  (when (and initializing?
	     (or (not (compilations-up-to-date-p procedure))
		 (not (block-can-be-inlined-p procedure))
		 (not (rewritten-procedure-inlining-p)))
	     loading-kb-p)
    (reclaim-slot-value wide-string?)
    (setq wide-string? nil))
  (setf (md5-identifier? procedure) wide-string?)
  wide-string?)




;;; The function `code-body-number-of-code-body' takes a code body and returns
;;; its "number" according to the procedure which owns it.

(defun code-body-number-of-code-body (code-body-to-check)
  (let* ((procedure? (procedure-definition-of-code-body code-body-to-check))
	 (code-bodies
	   (if procedure?
	       (code-bodies procedure?))))
    (loop for sibling-code-body in code-bodies
	  for count from 0
	  do
      (when (eq code-body-to-check sibling-code-body)
	(return count))
	  finally
	    #+development
	    (cerror
	      "Continue"
	      "Code body not registered in parent procedure's list.")
	    (return 0))))



(defun compress-annotation-info-for-saving (actual-lookup-structure?)
  (loop for info in actual-lookup-structure?
	collect (compress-annotation-list-for-saving info)
	  using phrase-cons))

(defun compress-annotation-list-for-saving (info)
  info)

;;; `get-annotation-for-address-if-any' is the main entry point to return line
;;; and position info given an address into a byte-code-vector (i.e. a PC), and
;;; a code-body.  This can return NIL, or the following five values:
;;;
;;;   (1) line-index, the line index of the formatted and presumably
;;;   word-wrapped text of the procedure (1-based);
;;;
;;;   (2) character-index, the character index in the line corresponding to
;;;   line-index (0-based);
;;;
;;;   (3) non-wrapped-line-index, the line index of the text of the procedure as
;;;   it would be if it were not word-wrapped, i.e., counting only the first
;;;   line and those that begin with a newline character (1-based);
;;;
;;;   (4) non-wrapped-character-index, the character index in the line
;;;   correspondign to non-word-wrapped-line-index (0-based); and
;;;
;;;   (5) non-wrapped-user-column-position, the 1-based character index past the
;;;   line separator character in the line corresponding to
;;;   non-word-wrapped-line-index
;;;
;;; Note that a line after a hard line break contains its linebreak character at
;;; the beginning. The column position is 1-based because that seems to be
;;; higher-level than zero-based, and because 1-based indexing is used in G2
;;; text operations, e.g., G2 system-defined function get-from-text.

(defun get-annotation-for-address-if-any (address code-body)
  (let ((actual-lookup-structure? (get-lookup-structure-if-any
				    (procedure-definition-of-code-body code-body))))
    (when actual-lookup-structure?
      (loop for ((start-address line-number character-number) (next-start-address))
	    on (nth (code-body-number-of-code-body code-body)
		    actual-lookup-structure?)
	    when (and (<= start-address address)
		      (or (null next-start-address)
			  (<f address next-start-address)))
	      return
	      (multiple-value-bind
		  (non-wrapped-line-index
		    non-wrapped-character-index
		    non-wrapped-character-index-past-linebreak)
		  (convert-to-non-word-wrapped-text-position
		    (cdr (procedure-definition
			   (procedure-definition-of-code-body code-body)))
		    line-number character-number)
		(values
		  line-number character-number
		  non-wrapped-line-index non-wrapped-character-index
		  (+f 1			; for 1-based column position
		      (-f non-wrapped-character-index
			  non-wrapped-character-index-past-linebreak))))))))




;;; `get-address-for-line-from-annotation-if-any' is sort of an inverse of
;;; get-annotation-for-address-if-any.  It takes a source-code line number and a
;;; procedure, and returns either NIL, or two values: the start-address of the
;;; byte code corresponding to the given source line (the line number according
;;; to the non-word-wrapped version of the procedure text), and the nth
;;; byte-code that the address is relative to.
(defun get-address-for-line-from-annotation-if-any (line procedure)
  (let ((actual-lookup-structure? (get-lookup-structure-if-any procedure)))
    (when actual-lookup-structure?
      (loop with start-address? = nil
	    with nth-code-body? = nil
	    with procedure-text = (cdr (procedure-definition procedure))
	    with non-word-wrapped-procedure-text ; reclaimed at end
	      = (convert-to-non-word-wrapped-text procedure-text)
	    for code-body-specific-annotations in actual-lookup-structure?
	    for nth-code-body from 0
	    until (loop for (start-address line-number char-index)
			    in code-body-specific-annotations
			;; Comparing line numbers is too simple.  It has the
			;; result that if you pass in a line number
			;; corresponding to a begin (say), it will return NIL.
			;; Deal with this later.  Multiple code-bodies is going
			;; to make this complicated to do correctly.  Probably
			;; have to find the lowest address associated with the
			;; line >= to the given line.
			as non-word-wrapped-line-index?
			   = (determine-corrected-text-position-if-necessary
			       line-number char-index
			       non-word-wrapped-procedure-text procedure-text 1)
			when (and non-word-wrapped-line-index?
				  ;; -- may be nil if line-/char-index invalid
				  (=f non-word-wrapped-line-index? line))
			  do (setq start-address? start-address)
			     (setq nth-code-body? nth-code-body)
			     (return t))
	    finally
	      (reclaim-text non-word-wrapped-procedure-text)
	      (return (values start-address? nth-code-body?))))))




;;; The function `procedure-code-body-given-number' takes a procedure and the
;;; number of a code body in that procedure.  This function returns the code
;;; body with that number, or NIL if none exists.

(defun procedure-code-body-given-number (procedure code-body-number)
  (car (nthcdr code-body-number (code-bodies procedure))))




;;; The function `surrounding-code-body?' takes a code body, and returns the
;;; surrounding code body of that code body, if there is any.

;; Note that this used to be held directly in a slot of code bodies.  When they
;; became dependent frames and started being saved in KBs, it was necessary to
;; not have multiple pointers to any code body, so its number is now held in
;; surrounded code bodies.

(defun surrounding-code-body? (code-body-to-check)
  (let ((surrounding-number? (surrounding-code-body-number? code-body-to-check)))
    (when surrounding-number?
      (procedure-code-body-given-number
	(procedure-definition-of-code-body code-body-to-check)
	surrounding-number?))))


#+unused
(def-frame-note-writer compile-procedure-note (particulars)
  (declare (ignore particulars))
  (tformat "this item needs to be recompiled for the optimize procedure code change to become effective"))

#+unused
(defun add-compile-procedure-note (procedure)
  (add-frame-note 'compile-procedure-note procedure nil))

;;; The slot value compiler for procedure-definitions aborts any ongoing
;;; invocations of this procedure and compiles the given definition.

(def-slot-value-compiler procedure-definition (parsed-definition procedure)
  ;; Shut down any currently running invocations.
  (let ((invocations (procedure-invocations procedure)))
    (when invocations
      ;; GENSYMCID-1927: G2 2016.7 Abort while editing running procedure
      ;;
      ;; Collect all procedure invocations into a list and only then
      ;; `signal-procedure-invocation-error` iterating that list, because
      ;; the hash table `invocations` will be changed during "signalling",
      ;; which would brake the loop iteration over the hash table.
      (loop for prin being each procedure-invocation of invocations
	    collect prin into prins-to-abort using gensym-cons
	    finally 
	      (loop for invocation in prins-to-abort do
		(signal-procedure-invocation-error
		  invocation
		  'error
		  1
		  (tformat-text-string
		    "Aborting procedure invocations of ~NF before compiling this procedure."
		    procedure)
		    nil))
	      (reclaim-gensym-list prins-to-abort))))
  ;; Compile the procedure.
  (compile-procedure-definition procedure parsed-definition)
  ;; Always return something to as the result of this compiler.  Note that any
  ;; compilation has already been cached in the procedure frame by the
  ;; compile-procedure-definition, and that this value is never looked at again.
  t)




;;; The slot putter for procedure-definition compiles procedures right now.
;;; This will have to be replaced when we understand how to save code bodies in
;;; files.

(def-slot-putter procedure-definition
		 (procedure procedure-definition initializing?)
  (when (and initializing?
	     (not (class-of-procedure-invocation-available-p))
	     loading-kb-p)
    (setf (class-of-procedure-invocation procedure)
	  'procedure-invocation))
  (when (and initializing?
	     (not (compilations-up-to-date-p procedure))
	     ;; Specific methods have procedure definitions.  Procedure methods
	     ;; do not.
	     (not (frame-of-class-p procedure 'method-declaration))
	     loading-kb-p)
    (reclaim-slot-value (car procedure-definition))
    (setf (car procedure-definition) no-value)
    (note-frame-with-compilation-removed procedure)
    (update-frame-status procedure 'incomplete t))
  #+java-export-facilities
  (analyze-export-info-for-parsability procedure procedure-definition)
  (when (eq (car procedure-definition) no-value)
    (change-slot-value procedure procedure-code-bodies-slot-name nil))
  (setf (procedure-definition procedure) procedure-definition)
  (when (and (not initializing?)
	     (frame-ok-p procedure))
    (adjust-dynamic-breakpoints
      procedure
      (loop for breakpoint
		in (dynamic-breakpoint-settings procedure)
	    collect (gensym-list
		      (dynamic-breakpoint-line-func breakpoint)
		      (dynamic-breakpoint-status-func breakpoint))
	      using gensym-cons)))
  procedure-definition)


(defconstant dynamic-breakpoint-enabled :enabled)
(defconstant dynamic-breakpoint-disabled :disabled)
(defconstant dynamic-breakpoint-valid :valid)
(defconstant dynamic-breakpoint-invalid :invalid)

;; Maybe this is silly and should be an evaluation-structure, and the slot
;; should hold an evaluation-sequence of the structures.  It would make it
;; trivial to expose then.
;;; NOTE: dynamic-breakpoints will have a -1 address and nth-code-body if the
;;; validity is :invalid.
(def-list-structure (dynamic-breakpoint (:consing-function slot-value-cons))
    (dynamic-breakpoint-address		;fixnum
      dynamic-breakpoint-line		;fixnum
      dynamic-breakpoint-nth-code-body	;fixnum
      dynamic-breakpoint-status		;symbol :ENABLED|:DISABLED
      dynamic-breakpoint-validity))	;symbol :VALID|:INVALID

(defun dynamic-breakpoint-line-func (dp)
  (dynamic-breakpoint-line dp))

(defun dynamic-breakpoint-status-func (dp)
  (dynamic-breakpoint-status dp))

(defun dynamic-breakpoint-validity-func (dp)
  (dynamic-breakpoint-validity dp))



(defun dynamic-breakpoint-enabled-p (dynamic-breakpoint)
  (eq (dynamic-breakpoint-status dynamic-breakpoint)
      dynamic-breakpoint-enabled))

(defun dynamic-breakpoint-valid-p (dynamic-breakpoint)
  (eq (dynamic-breakpoint-validity dynamic-breakpoint)
       dynamic-breakpoint-valid))

(defun get-dynamic-breakpoint-at-line? (procedure line)
  (loop for dynamic-breakpoint in (dynamic-breakpoint-settings procedure)
	for breakpoint-line = (dynamic-breakpoint-line dynamic-breakpoint)
	when (eql breakpoint-line line)
	  return dynamic-breakpoint))


(def-frame-note-writer invalid-dynamic-breakpoint (lines)
  ;; A lot of this style was taken from portions of twrite-type-mismatch
  ;; -dkuznick, 1/19/05 
  (tformat "there ~a invalid dynamic breakpoint~a on line~a"
	   (if (cdr lines)
	       "are"
	       "is an")
	   (if (cdr lines)
	       "s"
	       "")
	   (if (cdr lines)
	       "s"
	       ""))
  (loop for (line . rest) on lines
	do
    (tformat " ~a" line)
    while rest
	do
    (twrite-string
      (if (cdr rest)
	  ", "
	  " and "))))

(defun-void adjust-invalid-dynamic-breakpoint-frame-note (procedure)
  (delete-frame-note-if-any 'invalid-dynamic-breakpoint procedure)
  ;; The following is also O(n) on the number of
  ;; breakpoints and uses generic arithmetic.  But it's not likely the list
  ;; will ever get too long, plus it's only likely to be used during
  ;; debugging. -dkuznick, 1/19/05
  (let ((invalid-breakpoints?
	  (loop for dynamic-breakpoint in (dynamic-breakpoint-settings
					    procedure)
		unless (dynamic-breakpoint-valid-p dynamic-breakpoint)
		  collect (dynamic-breakpoint-line dynamic-breakpoint)
		    using slot-value-cons)))
    (when invalid-breakpoints?
      (add-frame-note
	'invalid-dynamic-breakpoint
	procedure
	(sort-list invalid-breakpoints? #'< nil)))))
  
;;; `add-dynamic-breakpoint' adds a new breakpoint to a procedure.  It returns
;;; non-nil when adding a legal breakpoint, or nil when adding an invalid
;;; one.  It also returns a second value of t if there were no other
;;; breakpoints, and nil if there were other breakpoints (valid or not).  If
;;; the caller will be making multiple calls to this at once, it should
;;; probably be wrapped in a with-updates-to-representations-supressed to avoid
;;; flashing. 

(defun add-dynamic-breakpoint (procedure address? line status nth-code-body?)
  (let ((dynamic-breakpoints? (dynamic-breakpoint-settings procedure)))
    (unless (get-dynamic-breakpoint-at-line? procedure line)
      (slot-value-push
	(make-dynamic-breakpoint (or address? -1)
				 line
				 (or nth-code-body? -1)
				 status
				 (if address?
				     dynamic-breakpoint-valid
				     ;; Can happen as the result of a
				     ;; recompile/edit -dkuznick, 3/11/05
				     dynamic-breakpoint-invalid))
	(dynamic-breakpoint-settings procedure))
      (adjust-invalid-dynamic-breakpoint-frame-note procedure))
    (values address? (not dynamic-breakpoints?))))

;;; `delete-all-dynamic-breakpoints' returns t if it deleted all breakpoints,
;;; and nil if there were no breakpoints to delete.
(defun delete-all-dynamic-breakpoints (procedure)
  (when (dynamic-breakpoint-settings procedure)
    (delete-frame-note-if-any 'invalid-dynamic-breakpoint procedure)
    (reclaim-slot-value-tree (dynamic-breakpoint-settings procedure))
    (setf (dynamic-breakpoint-settings procedure) nil)
    t))

;;; `delete-dynamic-breakpoint' deletes the dynamic breakpoint at the specified
;;; line.  Returns T if there was a breakpoint to remove, and if so, returns a
;;; second value if t if the last breakpoint was removed. 
(defun delete-dynamic-breakpoint (procedure line)
  (let ((breakpoint? (get-dynamic-breakpoint-at-line? procedure line)))
    (when breakpoint?
      (let ((new-breakpoints
	      (setf (dynamic-breakpoint-settings procedure)
		    (delete-gensym-element
		      breakpoint? (dynamic-breakpoint-settings procedure)))))
	(adjust-invalid-dynamic-breakpoint-frame-note procedure)
	(values t
		(not new-breakpoints))))))

;;; `turn-on-dynamic-breakpoint' turns on a dynamic breakpoint at a specified
;;; line.  It returns NIL if there was no breakpoint at that line or there is
;;; an invalid one at that line {in which case it is not set}, or non-NIL if
;;; there was.  Note that it is ok to turn on a breakpoint which is already
;;; turned on; non-NIL is returned in that case.
(defun turn-on-dynamic-breakpoint (procedure line)
  (let ((breakpoint? (get-dynamic-breakpoint-at-line? procedure line)))
    (when (and breakpoint?
	       (dynamic-breakpoint-valid-p breakpoint?))
      (setf (dynamic-breakpoint-status breakpoint?) dynamic-breakpoint-enabled))))


;;; `turn-off-dynamic-breakpoint' turns off a dynamic breakpoint at a specified
;;; line.  It returns NIL if there was no breakpoint at that line or there is
;;; an invalid one at that line, or non-NIL if there was.  Note that it is ok
;;; to turn off a breakpoint which is already turned off; non-NIL is returned
;;; in that case.
(defun turn-off-dynamic-breakpoint (procedure line)
  (let ((breakpoint? (get-dynamic-breakpoint-at-line? procedure line)))
    (when (and breakpoint?
	       (dynamic-breakpoint-valid-p breakpoint?))
      (setf (dynamic-breakpoint-status breakpoint?) dynamic-breakpoint-disabled))))


;;; `adjust-dynamic-breakpoints' is used to change over a procedure's current
;;; dynamic-breakpoint-settings to new values.  It takes the procedure and a
;;; gensym-tree of line and status info for the new breakpoints. The
;;; tree will be reclaimed.
(defun-void adjust-dynamic-breakpoints (procedure info)
  (with-updates-to-representations-supressed
      (procedure 'frame-status-and-notes)
    (delete-all-dynamic-breakpoints procedure)
    (loop for (line status) in (nreverse info) ;because setting is like a stack
	  do
      ;; The NIL is so we don't throw out breakpoints that become invalid.
      ;; Notice that if a valid breakpoint becomes invalid due to this adjust,
      ;; it retains its status -dkuznick, 3/11/05
      (set-dynamic-breakpoint-internal procedure line status nil)))
  (reclaim-gensym-tree info))


(def-virtual-attribute dynamic-breakpoints
    ((class procedure) (sequence
			 (structure
			   ((line-number integer)
			    (is-enabled truth-value)
			    ;; The following is a read-only value.  It is
			    ;; ignored in the setter. -dkuznick, 1/18/05
			    (is-valid truth-value))
			   (and line-number is-enabled)))
     nil)
  :event-updates nil
  :initial ((procedure) (declare (ignore procedure)) nil)
  :getter ((proc)
	   (loop for breakpoint in (dynamic-breakpoint-settings proc)
		 collect (allocate-evaluation-structure
			   (eval-list
			     'line-number
			     (dynamic-breakpoint-line breakpoint)
			     'is-enabled
			     (if (eq (dynamic-breakpoint-status breakpoint)
				     dynamic-breakpoint-enabled)
				 evaluation-true-value
				 evaluation-false-value)
			     'is-valid
			     (if (dynamic-breakpoint-valid-p breakpoint)
				 evaluation-true-value
				 evaluation-false-value)))
		 into eval-list using eval-cons
		 finally
		   (return (allocate-evaluation-sequence eval-list))))
  ;; The setter will need to notify the native UI.

  ;; Note the setter may need to override what gets passed in because it
  ;; ignores the is-valid value which gets set internally -dkuznick, 3/11/05
  :setter ((proc new-value)
	   (adjust-dynamic-breakpoints
	     proc
	     (loop for struct being each evaluation-sequence-element
		   of new-value
		   collect (gensym-list (evaluation-structure-slot
					  struct 'line-number)
					(if (evaluation-truth-value-is-true-p
					      (evaluation-structure-slot
						struct 'is-enabled))
					    dynamic-breakpoint-enabled
					    dynamic-breakpoint-disabled))
		   using gensym-cons))
	   nil))


(def-class-method initialize (procedure)
  (funcall-superior-method procedure)
  (when (or (null (procedure-definition procedure))
	    (null (get-slot-value procedure procedure-code-bodies-slot-name))
	    (no-value-p (car (procedure-definition procedure))))
    (update-frame-status procedure 'incomplete nil)))



;;; The deactivator for procedures causes all invocations of this procedure to
;;; be aborted before the procedure is itself deactivated.

(def-class-method deactivate-subclass-of-entity (procedure)
  (unless (runs-while-inactive-p procedure)
    (abort-procedure-invocations-of-procedure procedure)))

(defun-void abort-procedure-invocations-of-procedure (procedure)
  (let ((invocations (procedure-invocations procedure)))
    (when invocations
      (loop for invocation-to-abort being each procedure-invocation of invocations do
	(if (true-base-of-procedure-invocation-stack-p invocation-to-abort)
	    (abort-procedure-invocation invocation-to-abort)
	  (signal-procedure-invocation-error
	    invocation-to-abort
	    'error
	    1
	    (tformat-text-string
	      "Aborting procedure invocations of ~NF before deactivating this ~
               procedure."
	      procedure)
	    nil))))))



;;; The `cleanup' method for procedures should ensure that there are no running
;;; invocations of this procedure before it is deleted.  This is needed for
;;; running-while-inactive procedures.

(def-class-method cleanup (procedure)
  (abort-procedure-invocations-of-procedure procedure)
  (funcall-superior-method procedure))




;;; The `note-runs-while-inactive-change' method for procedures checks if the
;;; procedure is active, and if it is not active and we have just transitionsed
;;; to not running-while-inactive, then all current invocations of this
;;; procedure must be aborted.

(def-class-method note-runs-while-inactive-change (procedure)
  (funcall-superior-method procedure)
  (when (and (not (runs-while-inactive-p procedure))
	     (not (active-p procedure)))
    (abort-procedure-invocations-of-procedure procedure)))




;;; The `manually-disable' method for procedures checks if this is a running
;;; while inactive procedure, and if so it aborts all running
;;; procedure-invocations of this procedure.  If this is not a running while
;;; inactive procedure, then the deactivate method will take care of it.

(def-class-method manually-disable (procedure)
  (funcall-superior-method procedure)
  (when (runs-while-inactive-p procedure)
    (abort-procedure-invocations-of-procedure procedure)))




;;; The class `procedure-invocation' in a transient class representing an
;;; ongoing execution of a procedure.

;;; This has been changed to be an instance of a structure type, and a smaller
;;; class instance has been made.

(def-structure (procedure-invocation (:include code-body-invocation)
		 #+development
		 (:print-function print-procedure-invocation))
  tracing-and-breakpoints-of-procedure-invocation
  procedure-of-invocation
  procedure-invocation-top-level-array-index?
  simulation-procedure-invocation?
  procedure-invocation-completion-form?
  frame-of-procedure-invocation)

#+development
(defun print-procedure-invocation (procedure-invocation stream depth)
  (declare (ignore depth))
  (printing-random-object (procedure-invocation stream)
    (format stream "PROCEDURE-INVOCATION ~A"
	    (get-or-make-up-designation-for-block
	      (procedure-of-invocation procedure-invocation)))))

(defun-simple procedure-invocation? (thing)
  (procedure-invocation-p thing))

(defmacro calling-code-body-invocation (code-body-invocation)
  `(code-body-caller ,code-body-invocation))

(defun calling-procedure-invocation (code-body-invocation)
  (when code-body-invocation
    (loop do (setq code-body-invocation
		   (code-body-caller code-body-invocation))
	  when (null code-body-invocation)
	    return nil
	  when (procedure-invocation-p code-body-invocation)
	    return code-body-invocation)))

(defun find-procedure-invocation-in-module (procedure-invocation module)
  (loop for callee = procedure-invocation then caller?
	until (null callee)
	for caller? = (calling-procedure-invocation callee)
	for procedure = (procedure-of-invocation callee)
	when (eq module (get-module-block-is-in procedure))
	  return procedure))

(defun find-calling-procedure-invocation-in-module (procedure module)
  (and procedure
       (let ((invocations (procedure-invocations procedure)))
	 (when invocations
	   (loop
	     for invocation being each procedure-invocation of invocations
	     for procedure-deletion?
		 = (find-procedure-invocation-in-module invocation module)
	     when procedure-deletion?
	       return procedure-deletion?)))))

(def-class (procedure-invocation (item entity)
				 (foundation-class procedure-invocation)
				 not-normally-transient)
  (procedure-invocation-structure-of-procedure-invocation
    nil vector-slot system do-not-save))

(def-class-method cleanup (procedure-invocation)
  (let ((procedure-invocation-structure
	  (procedure-invocation-structure-of-procedure-invocation procedure-invocation)))
    (when procedure-invocation-structure
      (setf (procedure-invocation-structure-of-procedure-invocation procedure-invocation) nil)
      (setf (frame-of-procedure-invocation procedure-invocation-structure) nil)
      (abort-procedure-invocation procedure-invocation-structure)))
  (funcall-superior-method procedure-invocation))
  
(defun set-tracing-and-breakpoints-of-procedure-invocation
       (procedure-invocation new-tracing-and-breakpoints)
  (reclaim-slot-value
    (tracing-and-breakpoints-of-procedure-invocation
      procedure-invocation))
  (setf (tracing-and-breakpoints-of-procedure-invocation
	  procedure-invocation)
	new-tracing-and-breakpoints))

(defun-void set-tracing-and-breakpoints-of-procedure-invocations (block new-breakpoints)
  (let ((invocations (procedure-invocations block)))
    (when invocations
      (loop for invocation being each procedure-invocation of invocations do
	(set-tracing-and-breakpoints-of-procedure-invocation
	  invocation
	  (copy-for-slot-value new-breakpoints))))))

;;; The function `get-current-procedure-invocation-frame-if-any' is used to return
;;; the procedure-invocation frame associated with the current code-body
;;; invocation.  If the current-computation-instance is not a code-body invocation
;;; or if there is no procedure-invocation frame, nil is returned.  This function
;;; is need in the this-procedure-invocation role server.

(defun get-current-procedure-invocation-frame-if-any ()
  (let ((procedure-invocation?
	  (and (code-body-invocation-p current-computation-instance)
	       (procedure-invocation-of-code-body
		 current-computation-instance))))
    (and procedure-invocation?
	 (frame-of-procedure-invocation procedure-invocation?))))


(defun write-procedure-argument-list (args)
  (loop for arg in args
	for first-time? = t then nil
	do
    (unless first-time?
      (twrite-string ", "))
    (cond ((temporary-constant-p arg)
	   (print-constant (cached-constant-value arg) (constant-type arg)))
	  ((evaluation-value-p arg)
	   (write-evaluation-value arg))
	  ((framep arg)
	   (tformat "~NF" arg))
	  (t
	   (tformat "<error printing argument, ~a>" arg)))))



;;; `write-procedure-invocation-instance-from-slot' should be called
;;; twrite-procedure-invocation-instance-from-slot and should take only
;;; one argument.

(defvar within-writing-procedure-invocation-p nil)

(defun-void write-procedure-invocation-instance-from-slot (invocation ignored-frame)
  (declare (ignore ignored-frame))
  (let ((procedure-invocation-structure?
	  (cond
	    ((of-class-p invocation 'procedure-invocation)
	     (procedure-invocation-structure-of-procedure-invocation invocation))
	    ((procedure-invocation-p invocation)
	     invocation)
	    (t
	     nil))))
    (if (or (null procedure-invocation-structure?)
	    (memq invocation within-writing-procedure-invocation-p))
	(twrite-string #w"<a procedure invocation>")
	(let* ((within-writing-procedure-invocation-p
		 (gensym-cons invocation within-writing-procedure-invocation-p))
	       (base-code-body-invocation?
		 (base-code-body-invocation procedure-invocation-structure?))
	       (environment-vector?
		 (and base-code-body-invocation?
		      (invocation-local-var-vector base-code-body-invocation?)))
	       (frame-serial-number
		 (and base-code-body-invocation?
		      (code-body-invocation-frame-serial-number
			base-code-body-invocation?)))
	       (procedure (procedure-of-invocation procedure-invocation-structure?))
	       (argument-count (var-count (argument-list-description procedure))))
	  (denote-component-of-block t nil procedure)
	  (twrite-string "(")
	  (loop for index from 0 below argument-count
		for argument = (and environment-vector?
				    (svref environment-vector? index))
		do
	    (unless (=f index 0) (twrite-string ", "))
	    (if (or (deleted-frame-p argument)
		    (and (framep argument)
			 (frame-has-been-reprocessed-p argument frame-serial-number)))
		(write-stored-value nil)
		(write-stored-value argument)))
	  (twrite-string ")")
	  (gensym-pop within-writing-procedure-invocation-p)))))


;;;; Procedure Code Body Invocation Queues





;;; The function `enqueue-immediate-code-body-invocation' takes a code body
;;; invocation instance and enqueues it such that it will be executed before a
;;; procedure wait state is entered.  This function installs a backpointer from
;;; the code-body-invocation back to the queue entry, and ensures there are no
;;; double schedulings by clearing any queue entry already stored in this code
;;; body invocation.  This function returns NIL.

(defun-void enqueue-immediate-code-body-invocation (code-body-invocation)
  (with-immediate-scheduling ((invocation-schedule-task code-body-invocation)
			      nil () t) ; parallel?
    (execute-computation-instance code-body-invocation)))




;;; The function `filo-enqueue-immediate-code-body-invocation' performs the same
;;; operation, except that it enqueues for first in, last out execution.  In
;;; other words this enqueue butts into line ahead of everything else.

(defun-void filo-enqueue-immediate-code-body-invocation (code-body-invocation)
  (with-pushed-immediate-scheduling
      ((invocation-schedule-task code-body-invocation) () t) ; parallel?
    (execute-computation-instance code-body-invocation)))


;;; The function `computation-instance-faction' return the faction of the
;;; computation instance.
;;; If you want to run the main faction in parallel with the scheduler,
;;; pray to the gods, put your earthly affairs in order and uncomment
;;; :main-faction below.
;;; The most prominent issues now are:
;;; - "Uninterrupted procedure execution limit exceeded";
;;; - ... (?).
;;; In future :main-faction may have to be replaced with
;;; the (pseudo) faction singleton object.
#+mtg2
(defun-simple computation-instance-faction (computation-instance)
  (cond
    ((procedure-invocation-p computation-instance)
     (or
      (faction? (procedure-of-invocation computation-instance))
      ;:main-faction
      ))
    ((rule-instance-p computation-instance)
     (or
      (faction? (ri-rule computation-instance))
      ;:main-faction
      ))))

;;; The function `schedule-computation-instance-execution' takes a code body
;;; invocation and a priority, and enqueues the given invocation to be executed
;;; at the given priority.  This function also clears any other enqueuings of
;;; this code body invocation.  The given frame is checked to see if it runs
;;; while inactive, and that determines whether or not this is a g2-time task or
;;; a real-time task.  It returns NIL.  The `pushed-' version of this function
;;; does the same thing, except the task is pushed onto the front of the queue
;;; of tasks for this priority, not onto the end.

(defun-simple schedule-computation-instance-execution
    (computation-instance priority containing-frame)
  (let (#+SymScale
	(parallel? (code-body-invocation-p computation-instance))
	#+mtg2
	(parallel? (computation-instance-faction computation-instance)))
    (with-current-scheduling ((invocation-schedule-task computation-instance)
			      priority nil nil
			      (runs-while-inactive-p containing-frame)
			      () ; reclaimers
			      #+SymScale parallel?
			      #+mtg2 parallel?)
      (execute-computation-instance computation-instance))
    nil))

(defun-simple schedule-computation-instance-execution-for-breakpoint
    (computation-instance)
  (let (#+SymScale
	(parallel? (code-body-invocation-p computation-instance))
	#+mtg2
	(parallel? (computation-instance-faction computation-instance)))
    (with-current-scheduling ((invocation-schedule-task computation-instance)
			      priority-of-current-task
			      nil nil nil
			      () ; reclaimers
			      #+SymScale parallel?
			      #+mtg2 parallel?)
      (execute-computation-instance computation-instance))
    nil))

(defun-simple schedule-pushed-computation-instance-execution
    (computation-instance priority containing-frame)
  (let (#+SymScale
	(parallel? (code-body-invocation-p computation-instance))
	#+mtg2
	(parallel? (computation-instance-faction computation-instance)))
    (with-pushed-current-scheduling
	((invocation-schedule-task computation-instance)
	 priority nil nil
	 (runs-while-inactive-p containing-frame)
	 () ; reclaimers
	 #+SymScale parallel?
	 #+mtg2 parallel?)
      (execute-computation-instance computation-instance))
    nil))


;;; The macro `schedule-delayed-computation-instance-execution' takes a
;;; computation-instance, a priority, a containing frame, and a gensym-float
;;; holding the number of seconds to delay before executing the given
;;; invocation.

(defmacro schedule-delayed-computation-instance-execution
    (computation-instance priority containing-frame delay-interval)
  (let ((invocation (gensym))
	(priority-var (gensym))
	(runs-while-inactive (gensym))
	(task-time (gensym)))
    `(let* ((,invocation ,computation-instance)
	    (,priority-var ,priority)
	    (,runs-while-inactive
	       (runs-while-inactive-p ,containing-frame))
	    (,task-time
	       (+e (managed-float-value (if ,runs-while-inactive
					    (clock-get current-real-time)
					    (clock-get current-g2-time)))
		   ,delay-interval)))
       (declare (type gensym-float ,task-time))
       (if (code-body-invocation-p ,invocation)
	   (with-future-scheduling
	       ((invocation-schedule-task ,invocation)
		,priority-var ,task-time nil nil ,runs-while-inactive)
	     ; it boils down to `schedule-delayed-computation-instance-execution'
	     ; which takes care of factions
	     (wake-up-code-body-invocation ,invocation))
	   (with-future-scheduling
	       ((invocation-schedule-task ,invocation)
		,priority-var ,task-time nil nil ,runs-while-inactive)
	     (execute-computation-instance ,invocation)))
       nil)))




;;; The function `fetch-and-enter-next-current-computation-instance' takes a
;;; priority.  This function enters the computation-context for the next
;;; immediate computation instance to execute or the next scheduled computation
;;; instance at the given priority if the time slice has not expired.

;; Note that the procedure (local-variable) environment is always validated in
;; the following call.  This is necessary because the code-body-invocation is
;; either continuing execution or has been scheduled for execution (i.e., a
;; "start" action) and needs validation.  - cpm, 7/21/95

(defun-simple fetch-and-enter-next-current-computation-instance (priority)
  (setq current-computation-instance nil)
  (unless (maybe-check-network-events)
    (loop with time = (get-fixnum-time)
	  with time-slice-expired? = (time-slice-expired-p-given-time time)
	  with fixnum-time-limit? = nil
	  for schedule-task? = (next-scheduled-task-for-function
				 'execute-computation-instance
				 (if time-slice-expired?
				     higher-than-any-priority
				     priority))
	  while schedule-task?
	  do
      (let ((computation-instance (schedule-task-arg-1 schedule-task?))
	    (immediate-task? (immediate-scheduled-task-p schedule-task?)))
	(cancel-task (invocation-schedule-task computation-instance))
	(when (queue-invocation-for-lock-if-necessary computation-instance)
	  (when profiling-enabled? (posit-profiling-structure computation-instance))
	  (setq fixnum-time-limit? (enter-or-reclaim-computation-instance-context
				     computation-instance))
	  (when current-computation-instance
	    (unless immediate-task?
	      (setq cached-fixnum-start-time time))
	    (return fixnum-time-limit?)))))))




;;; The variable `forgive-long-procedure-instruction?' is normally NIL, but can
;;; be set to T by some instructions, such as NUPEC synchronize or tracing and
;;; breakpoints.  If this value is found to be T, then no warnings or error
;;; should be given for this long instruction, but the variable should then be
;;; reset to NIL to catch the next long one.

(def-system-variable forgive-long-procedure-instruction? proc-utils nil)





;;; The variable `code-body' will be bound to the code body that is currently
;;; being printed when executing a print-var-spot, and also is bound when
;;; executing a code body invocation.

;; This variable needs to be removed, but there may still be bogus references to
;; it.  -jra 2/7/92

;#+old-evaluators
(defvar code-body nil)




;;; Note that it is an error to execute the following instructions while
;;; executing a simulation procedure:
;;;
;;;  WAIT UNTIL
;;;  START
;;;  COLLECT DATA
;;;  CONCLUDE THAT
;;;  MOVE
;;;  SET-POSITION
;;;  ROTATE
;;;  SET-HEADING
;;;  CONCLUDE
;;;  FOCUS
;;;  INVOKE
;;;  CHANGE
;;;  SHOW
;;;  HIDE
;;;  ACTIVATE
;;;  DEACTIVATE
;;;  EDIT
;;;  INFORM
;;;  CREATE
;;;  DELETE

;;; The macro `error-if-simulation-procedure' takes a string naming the
;;; statement whose instruction the caller is within.  This macro will signal a
;;; procedure error if executed within a simulation procedure.

(defmacro error-if-simulation-procedure (instruction-name top-of-stack)
  `(when evaluating-simulator-procedure?
     (not-a-simulator-procedure-instruction ,instruction-name ,top-of-stack)))

(defun not-a-simulator-procedure-instruction
       (instruction-name-string top-of-stack)
  (stack-error
    top-of-stack
    "~a statements may not be executed within simulation procedures."
    instruction-name-string))




;;; The function `print-var-spot-for-stack' takes a variable spot and an
;;; environment description for the byte-code-body within which this variable
;;; spot is being evaluated.  It tprincs the variable name or a description of
;;; the variable.

;;; Modified to accept an optional argument that indicates if the var-spot is
;;; defined in the environment description.  This means that the nesting of the
;;; var-spot should not be used when locating the var-spot description in the
;;; environment.

;; This optional third argument was added to fix a bug in printing local-names
;; from a procedure error message.  If the local-name reference was within a
;; code-body that is not the defining code-body, then the message could not
;; determine the name of the local-variable.  The callers of print-var-spot-for-
;; stack can now pass in the definition environment-description.  See
;; signal-no-value-in-local-var-error.  - cpm, 10/13/93

;; Note that this printer function cannot currently print names and types for
;; var-spots of non-local code body variables, i.e.  variables from surrounding
;; code bodies.  -jra 4/8/91

(defun print-var-spot-for-stack
 (var-spot environment-description
	   &optional (var-spot-defined-in-environment-description? nil))
  #+development
  (when (or (not (consp var-spot)) (neq (car var-spot) 'var-spot))
    (error "Argument to print-var-spot , ~a, ~
            was not a valid var-spot."
	   var-spot))
  (let* ((var-spot-index (second var-spot))
	 (nesting (var-spot-index-nesting var-spot-index))
	 (local-index (var-spot-local-index var-spot-index))
	 (var-name? nil)
	 (var-description? nil))
    (when (and (or (=f nesting 0)
		 var-spot-defined-in-environment-description?)
	     environment-description)
      (setq var-name? (var-name-from-index environment-description local-index))
      (setq var-description? (var-general-description-from-index environment-description local-index))
      nil)
    (print-name-of-variable-and-description-1
      var-name?
      var-description?
      nesting
      local-index)
    nil))

(defun print-var-spot-for-stack-using-name-and-description
    (var-spot var-spot-name var-spot-description
	      &optional (var-spot-defined-in-environment-description? nil))
  #+development
  (when (or (not (consp var-spot)) (neq (car var-spot) 'var-spot))
    (error "Argument to print-var-spot , ~a, ~
            was not a valid var-spot."
	   var-spot))
  (let* ((var-spot-index (second var-spot))
	 (nesting (var-spot-index-nesting var-spot-index))
	 (local-index (var-spot-local-index var-spot-index))
	 (name? nil)
	 (description? nil))
    (when (or (=f nesting 0)
	      var-spot-defined-in-environment-description?)
      (setq name? var-spot-name)
      (setq description? var-spot-description))
    (print-name-of-variable-and-description-1
      name?
      description?
      nesting
      local-index)
    nil))


(defun named-var-spot-p (var-spot environment-description)
  (let* ((var-spot-index (second var-spot))
	 (nesting (var-spot-index-nesting var-spot-index))
	 (local-index (var-spot-local-index var-spot-index)))
    (and (=f nesting 0)
	 (not (null (var-name-from-index? environment-description local-index))))))

(defun print-var-spot-type-for-stack (var-spot environment-description)
  #+development
  (when (or (not (consp var-spot)) (neq (car var-spot) 'var-spot))
    (error "Argument to print-var-spot , ~a, ~
            was not a valid var-spot."
	   var-spot))
  (let* ((var-spot-index (second var-spot))
	 (nesting (var-spot-index-nesting var-spot-index))
	 (local-index (var-spot-local-index var-spot-index)))
    (print-type-of-variable-description
      (if (and (=f nesting 0) environment-description)
	  (var-general-description-from-index environment-description local-index)
	  nil)
      (if (and (=f nesting 0) environment-description)
	  (var-type-from-index environment-description local-index)
	  nil))
    nil))

(defun print-name-of-variable-description (variable-description)
  (print-name-of-variable-description-1 variable-description))

(defun print-name-of-variable-description-1
       (variable-description &optional nesting? index?)
  (let* ((name? (car variable-description))
	 (description-plist (cdr variable-description))
	 (name-was-found? t))
    (cond ((and name? (symbolp name?))
	   (twrite-symbol name? t))
	  ((and (consp name?) (eq (car name?) 'the))
	   (print-designation name?))
	  ((getfq description-plist :return-value)
	   (tformat "RETURN-VALUE-~a"
		    (getfq description-plist :return-value)))
	  (t
	   (setq name-was-found? nil)
	   (cond ((or (null nesting?) (null index?))
		  (twrite-string "<local>"))
		 ((=f nesting? 0)
		  (tformat "LOCAL-~a" index?))
		 (t
		  (tformat "LOCAL-~a-~a" nesting? index?)))))
    name-was-found?))

(defun print-name-of-variable-and-description (variable-name variable-description)
  (print-name-of-variable-and-description-1 variable-name variable-description))

(defun print-name-of-variable-and-description-1
       (name? variable-description &optional nesting? index?)
  (let* ((name-was-found? t))
    (cond ((and name? (symbolp name?))
	   (twrite-symbol name? t))
	  ((and (consp name?) (eq (car name?) 'the))
	   (print-designation name?))
	  ((eq (car variable-description) ':return-value)
	   (tformat "RETURN-VALUE-~a"
		    (cdr variable-description)))
	  (t
	   (setq name-was-found? nil)
	   (cond ((or (null nesting?) (null index?))
		  (twrite-string "<local>"))
		 ((=f nesting? 0)
		  (tformat "LOCAL-~a" index?))
		 (t
		  (tformat "LOCAL-~a-~a" nesting? index?)))))
    name-was-found?))

(defun print-type-of-variable-description (description? type?)
  (cond ((getfq description? :environment)
	 #+development
	 (error "Environment pointer found in new var spot environment.")
	 (twrite-string "<internal environment pointer>"))
	((getfq description? :return-value)
	 (tformat "~NT" 'item-or-datum))
	((valid-type-specification-p type?)
	 (write-type-specification type?))
	(t
	 (twrite-string "<untyped>"))))




;;; The function `write-code-body-environment' takes an environment description
;;; and an environment, and twrites the contents of that environment.

;;; Note that this function will not print data that it can't understand.  I was
;;; somewhat uncomfortable making this choice for all time, so I have put in a
;;; debugging global variable that can be set to allow the printing of internal data
;;; from procedure environments.  Hopefully we'll never have to use it, but there it
;;; is anyway.  -jra 3/29/90

(defvar allow-internal-procedure-environment-printing?
  #+development t
  #-development nil)

(defun write-code-body-environment (environment-description environment?)
  (let ((some-printed? nil))
    (cond ((null environment-description)
	   ;; Do nothing
	   nil)
	  ((null environment?)
	   ;; This disassemble only happens in development.
	   (loop with var-spot = (proc-list 'var-spot 0)
		 for index from 0
		 repeat (var-count environment-description)
		 do
	     (setf (second var-spot) index)
	     (when some-printed? (tformat ";~%"))
	     (setq some-printed? t)
	     (twrite-string "  ")
	     (print-var-spot-for-stack var-spot environment-description)
	     (twrite-string ": ")
	     (print-var-spot-type-for-stack var-spot environment-description)
		 finally (reclaim-proc-list var-spot)))
	  (t
	   (loop with var-spot = (proc-list 'var-spot 0)
		 for index from 0 below (length environment?)
		 repeat (length environment-description)
		 for value = (svref environment? index)
		 do
	     (setf (second var-spot) index)
	     (when (named-var-spot-p var-spot environment-description)
	       (when some-printed? (tformat ";~%"))
	       (setq some-printed? t)
	       (twrite-string "  ")
	       (print-var-spot-for-stack var-spot environment-description)
	       (twrite-string ": ")
	       (print-var-spot-type-for-stack var-spot environment-description)
	       (twrite-string " = ")
	       (write-stored-value value))
		 finally (reclaim-proc-list var-spot))))
    (unless some-printed?
      (twrite-string "  no local names available"))
    nil))




;;; The function `write-stack-contents' is used to print the contents of the
;;; stack into error messages.  Note that it will show at most 20 values within
;;; the stack.  This can be overridden via an optional argument.

(defun write-stack-contents (stack? top-of-stack? &optional (depth 20))
  (when stack?
    (tformat "~%Stack:")
    (cond ((<f top-of-stack? 0)
	   (tformat "~%No values on stack"))
	  ((>f top-of-stack? depth)
	   (tformat " (top ~a values not shown)" (-f top-of-stack? depth))
	   (loop for index from (-f top-of-stack? depth) to top-of-stack? do
	     (tformat "~%~a = " index)
	     (write-stored-value (svref stack? index))))
	  (t
	   (loop for index from 0 to top-of-stack? do
	     (tformat "~%~a = " index)
	     (write-stored-value (svref stack? index)))))))



;; I bumped this up from its original value of 200 because it was truncating
;; string references in even relatively short error messages (see print-
;; constant). We should monitor this value periodically as we get a better
;; sense of the overall range of messages we are showing the user. ddm 4/22/97



;;; The function `write-stored-value' takes a value stored in an environment or
;;; constant vector and tries to twrite a user recognizable form of that value.
;;; If it can't find an appropriate format, it prints "internal data".


(defun write-stored-value (value)
  (cond ((null value)
	 (twrite-string "no value"))
	((framep value)
	 (tformat "~NF" value))
	((evaluation-value-p value)
	 (let ((evaluation-value-writing-target-length?
		 maximum-length-for-writing-evaluation-values))
	   (write-evaluation-value value)))
	((temporary-constant-p value)
	 (let ((evaluation-value-writing-target-length?
		 maximum-length-for-writing-evaluation-values))
	   (print-constant (cached-constant-value value)
			   (constant-type value))))
	(t
	 (if allow-internal-procedure-environment-printing?
	     (tformat "<DEBUG DATA: ~a>" value)
	     (twrite-string "<internal data>")))))




;;; The function `wake-up-code-body-invocation' takes a code body invocation and
;;; schedules it for current execution.

(defun-simple wake-up-code-body-invocation (code-body-invocation)
  (clear-event-detectors code-body-invocation)
  (unless (current-schedule-task-in-place-p
	    (invocation-schedule-task code-body-invocation))
    (schedule-computation-instance-execution
      code-body-invocation
      (code-body-invocation-priority code-body-invocation)
      (procedure-of-invocation
	(procedure-invocation-of-code-body code-body-invocation))))
  nil)




;;; The function `wake-up-code-body-invocation-immediately' takes a code body
;;; invocation and places it on the immediate queue for execution.
;;; ajs (6/14/96)

(defun-simple wake-up-code-body-invocation-immediately (code-body-invocation)
  (clear-event-detectors code-body-invocation) 
  (filo-enqueue-immediate-code-body-invocation
    code-body-invocation))






;;;; Invocations of Procedures and Code Bodies




;;; When a procedure is invoked, a procedure-invocation is instantiated to
;;; represent the invocation.  This instance will persist during the execution
;;; of this invocation.  The invocation contains pointers to the caller and any
;;; called procedure-invocations, a list of all executing code body invocations
;;; for this procedure invocation, and the current status of this invocation.
;;; The environments for this invocation are actually stored in the code body
;;; invocations.

;;;






;;;; Environment Layout in Procedures




;;; The environments of code body invocations are laid out as follows:
;;;
;;;   [procedure arguments]
;;;   [surrounding environment]
;;;   [local variables]
;;;   [return value spots]


;;; When a procedure is invoked, the procedure invocation and base code body
;;; invocation are made.  The environment for the base code body invocation is
;;; modified to contain the passed argument.  If one code body invocation
;;; launches another, then the launched invocation will have a pointer back to
;;; the surrounding environment.

;;;






;;;; Procedure Call and Return




;;; The following documentation specifies the behavior of CALL and RETURN
;;; statements...

;;; When a procedure is invoked, it produces a procedure invocation.  That in
;;; turn produces a code body invocation for its base code body.  The
;;; environment of the base code body is given the arguments to the procedure as
;;; its zeroth through number of args minus one elements.  The execution of this
;;; code body will then produce any further code body invocations for this
;;; procedure invocation.  When a RETURN is executed from any of the code bodies
;;; for a procedure invocation, it evaluates its return expressions putting the
;;; values into the return values position of the environment of the calling
;;; code body invocation, CALL ABORTS any other executing code body invocations,
;;; then returns control to the code body invocation which initiated the CALL to
;;; this procedure invocation.  At the point at which control is returned to the
;;; calling invocation, the returning procedure invocation is deleted.

;;; Note that when a procedure is invoked, or when a procedure returns, the
;;; declared data types of the variable spots which are to receive values
;;; determine the kind of evaluation performed.  The functions
;;; prepare-inference-argument-list-for-procedure and prepare-procedure-
;;; argument-list-for-procedure take a list of expressions, and the definition
;;; of the procedure which is to be invoked.  It will return an eval-cons list
;;; whose car is the current-frame-serial-number and whose cdr is a list of
;;; frames and temporary constants which will be the argument list for the

;;; Note that both CALL and RETURN statements will cause an immediate invocation
;;; FILO enqueue of the code body invocation to which control is being
;;; transfered.  This makes the thread of execution of CALLs and RETURNs
;;; supercede the threads between concurrent statements in an IN-PARALLEL form.
;;; This is appropriate for the IN PARALLEL UNTIL ONE COMPLETES type of parallel
;;; launching, since the first statement that finishes should immediately
;;; transfer control back to the code body containing the IN PARALLEL UNTIL ONE
;;; COMPLETES.  This is also consistent with our assertion that CALL and RETURN
;;; (if not encumbered by parallel bodies) should execute without wait state.



;;; The function `prepare-inference-argument-list-for-procedure' takes a
;;; procedure definition frame and a list of argument expressions.  It returns
;;; an eval cons procedure argument list with the current frame serial number as
;;; the first element, and a flag saying whether the evaluation was successful.
;;; The flag can return the values T, NIL, or NO.  If the value is T, then all
;;; evaluations were successful.  If the value is NIL, then an expression
;;; returned UNKNOWN.  If the value is NO, then there was an error evaluating
;;; the arguments, and this argument list will not be able to be applied to the
;;; given procedure.  If the second returned value is NIL or NO (the
;;; evaluation was not successful) then the first value will also be NIL.


;;; The function `prepare-procedure-argument-list-for-stack-procedure' is used
;;; to make procedure argument lists inside of procedures executing in the stack
;;; interpreter.  It is similar to the function above, but gets its values right
;;; off of the stack.

;;; The arguments-known-to-be-correct-p?  argument is used to indicate whether
;;; the count and type of the arguments are already known to be correct.  In
;;; this case, no testing will be done and the arguments will be taken off the
;;; stack and returned from this function.

;;; Like the case when arguments are known to be valid, procedure method
;;; arguments (non-specific methods) are also not validated here.

;;; As a result of this, the frame-serial number which used to be cons'ed on to the
;;; returned list is never used, so I've deleted it -alatto, 3/12/99

(defun-simple signal-wrong-number-of-arguments-stack-error 
    (top-of-stack procedure arg-restp-index var-count arg-count)
  (raw-stack-error-named-error
    top-of-stack
    (make-wrong-number-of-arguments-error-text
      procedure arg-restp-index var-count arg-count)))

(defun-simple make-wrong-number-of-arguments-error-text
    (procedure arg-restp-index var-count arg-count)
  (tformat-stack-error-text-string
    "The wrong number of arguments were passed to ~NF from ~NF.  It needs~
     ~a~a argument~a but received ~a."
    procedure *current-computation-frame*
    (if arg-restp-index " at least " " ")
    var-count
    (if (=f var-count 1) "" "s")
    arg-count))

(defun prepare-procedure-argument-list-for-stack-procedure
    (procedure local-stack top-of-arguments-on-stack argument-count
	       arguments-known-to-be-correct-p?)
  (let* ((local-procedure? (frame-of-class-p procedure 'procedure))
	 (method-declaration?
	   (and local-procedure?
		(frame-of-class-p procedure 'method-declaration)))
	 (argument-descriptions
	   (if local-procedure?
	       (argument-list-description procedure)
	       (remote-procedure-argument-description-function procedure)))
	 (generated-argument-list nil)
	 (argument-restp-index nil)
	 value)
    (let ((i (1-f (var-count argument-descriptions))))
      (when (and (<=f 0 i)
		 (getf (var-general-description-from-index argument-descriptions i)
		       :all-remaining))
	(setq argument-restp-index i)))
    (when (and (not arguments-known-to-be-correct-p?)
	       (if argument-restp-index
		   (<f argument-count argument-restp-index)
		   (/=f argument-count (var-count argument-descriptions))))
      (signal-wrong-number-of-arguments-stack-error
	top-of-arguments-on-stack procedure argument-restp-index
	(or argument-restp-index (var-count argument-descriptions))
	argument-count))
    (loop for stack-index from (+f (-f top-of-arguments-on-stack argument-count)
				   1)
			  to top-of-arguments-on-stack
	  for arg-index = 0 then (if (and argument-restp-index (=f arg-index argument-restp-index))
				     arg-index
				     (1+f arg-index))
	  for description = (var-general-description-from-index argument-descriptions arg-index)
	  for stack-value = (svref local-stack stack-index)
	  for name = (var-name-from-index argument-descriptions arg-index)
	  for type = (var-type-from-index argument-descriptions arg-index)
	  do
      (cond
	((or arguments-known-to-be-correct-p? method-declaration?)
	 ;; Either valid or validated at runtime (for procedure methods).
	 (setq value stack-value)
	 (setq generated-argument-list
	       (eval-cons-macro value generated-argument-list)))	 
	((or (class-type-specification-p-macro type)
	     (eq type 'item-or-datum))
	 (setq value stack-value)
	 (cond
	   ((or (eq type 'item-or-datum)
		(of-class-p value (type-specification-class type)))
	    (setq generated-argument-list
		  (eval-cons-macro value generated-argument-list)))
	   ((and (eq 'handle (getfq description :kind))
		 (fixnump value))
	    (setq generated-argument-list
		  (eval-cons-macro value generated-argument-list)))
	   (t
	    (reclaim-eval-list generated-argument-list)
	    (procedure-argument-list-error
	      top-of-arguments-on-stack procedure name type value))))
	(t
	 ;; Note that if a value is fetched from a parameter, it will be stored
	 ;; into the parameter's location in the stack.  In the event that an
	 ;; error should occur, then this new evaluation value will be reclaimed
	 ;; from the stack.  -jra 4/10/91
	 (cond ((of-class-p stack-value 'parameter)
		(setq value (get-current-evaluation-value-of-parameter
			      stack-value))
		(setf (svref local-stack stack-index) value))
	       (t
		(setq value stack-value)))
	 (cond ((framep value)
		(reclaim-eval-list generated-argument-list)
		(procedure-argument-list-error
		  top-of-arguments-on-stack procedure name type value))
	       ((evaluation-value-of-type-p value type)
		(setq generated-argument-list
		      (eval-cons-macro value generated-argument-list)))
	       ((and (eq type 'float)
		     (evaluation-integer-p value))
		(setq generated-argument-list
		      (eval-cons-macro
			(make-evaluation-float
			  (coerce-fixnum-to-gensym-float
			    (evaluation-integer-value value)))
			generated-argument-list))
		(reclaim-evaluation-integer value))
	       (t
		(reclaim-eval-list generated-argument-list)
		(procedure-argument-list-error
		  top-of-arguments-on-stack procedure name type value))))))
    (nreverse generated-argument-list)))


;;; The function `prepare-procedure-argument-list-for-stack-procedure' returns
;;; an error-text if there is an error, or NIL otherwise.

;; This is quite similar to prepare-procedure-arguments-on-stack
(defun prepare-procedure-argument-list-in-place-for-stack-procedure
    (procedure local-stack top-of-arguments-on-stack argument-count
	       arguments-known-to-be-correct-p?)
  (unless (frame-of-class-p procedure 'procedure)
    (return-from prepare-procedure-argument-list-in-place-for-stack-procedure
      (tformat-stack-error-text-string
	"Internal G2 error: bad procedure ~a while preparing arguments."
	procedure)))
  (let* ((argument-descriptions (argument-list-description procedure))
	 (last-index (1-f (var-count argument-descriptions)))
	 (formal-arg-restp-index 
	   (when (and (<=f 0 last-index)
		      (getf (var-general-description-from-index argument-descriptions last-index)
			    :all-remaining))
	     last-index)))
    (when (and (not arguments-known-to-be-correct-p?)
	       (if formal-arg-restp-index
		   (<f argument-count formal-arg-restp-index)
		   (/=f argument-count (var-count argument-descriptions))))
      (return-from prepare-procedure-argument-list-in-place-for-stack-procedure
	(make-wrong-number-of-arguments-error-text
	  procedure formal-arg-restp-index
	  (or formal-arg-restp-index (var-count argument-descriptions))
	  argument-count)))
    (let ((switching-role-service-types?
	    (and (role-serve-inactive-objects?)
		 (null (may-refer-to-inactive-items-p procedure))))
	  (current-computation-flags current-computation-flags))
      (when switching-role-service-types?
	(setf (role-serve-inactive-objects?) nil))
      (let* ((bottom-of-arguments-on-stack
	       (1+f (-f top-of-arguments-on-stack argument-count)))
	     (inactive-item-index
	       (when switching-role-service-types?
		 (loop for stack-index from bottom-of-arguments-on-stack
				       to top-of-arguments-on-stack
		       for value = (svref local-stack stack-index)
		       when (and (framep value) (null (serve-item-p value)))
			 return (1+f (-f stack-index bottom-of-arguments-on-stack))))))
	(when inactive-item-index
	  (return-from
	    prepare-procedure-argument-list-in-place-for-stack-procedure
	    (tformat-stack-error-text-string
	      "Attempt to pass an inactive item as argument number ~A to ~
               the procedure ~NF which cannot refer to inactive items."
	      inactive-item-index
	      procedure)))
	(unless (or arguments-known-to-be-correct-p? (frame-of-class-p procedure 'method-declaration))
	  (loop for stack-index from bottom-of-arguments-on-stack
				to top-of-arguments-on-stack
		for value = (svref local-stack stack-index)
		for arg-index = 0 then (if (and formal-arg-restp-index
						(=f arg-index formal-arg-restp-index))
					   arg-index (1+f arg-index))
		for type = (var-type-from-index argument-descriptions arg-index)
		unless (cond
			 ((eq type 'item-or-datum) t)
			 ((class-type-specification-p-macro type)
			  (of-class-p value (type-specification-class type)))
			 (t
			  (when (of-class-p value 'parameter)
			    (setq value (get-current-evaluation-value-of-parameter value))
			    (setf (svref local-stack stack-index) value))
			  (cond ((framep value) nil)
				((evaluation-value-of-type-p value type) t)
				((and (eq type 'float)
				      (evaluation-integer-p value))
				 (setf (svref local-stack stack-index)
				       (make-evaluation-float
					 (coerce-fixnum-to-gensym-float
					   (evaluation-integer-value value))))
				 (reclaim-evaluation-integer value)
				 t)
				(t nil))))
		  do (let ((name (var-name-from-index argument-descriptions arg-index)))
		       (return-from
			 prepare-procedure-argument-list-in-place-for-stack-procedure
			 (make-procedure-argument-list-error-text
			   procedure name type value))))))))
  nil)


(defun procedure-argument-list-error
    (top-of-arguments-on-stack procedure name type value)
  (raw-stack-error-named-error
    top-of-arguments-on-stack
    (make-procedure-argument-list-error-text procedure name type value)))

(defun make-procedure-argument-list-error-text (procedure name type value)
  (twith-output-to-error-text
    (twrite-string "The ")
    (print-name-of-variable-and-description name type)
    (tformat
      " argument of ~NF is declared to take values of type ~
       ~NT, but instead it received "
      procedure
      type)
    (cond ((framep value)
	   (tformat "~NF, an instance of the class ~a."
		    value
		    (class value)))
	  (t
	   (write-stored-value value)
	   (twrite-character #.%\.)))
    (when (and (type-specification-subtype-p type 'datum)
	       (of-class-p value 'variable))
      (tformat
	"  Note that if you intended to pass the value of this variable, you ~
         must use a COLLECT DATA statement to fetch its value."))))




;;; The function `get-procedure-argument-list-error-if-any' takes a procedure
;;; and list of arguments for an invocation of that procedure.  This function
;;; should check the argument list, returning an error text string if there is a
;;; problem, and returning NIL if the argument list is OK.

;;; If an argument is a fixnum and the argument description specifies an item,
;;; then that fixnum may represent a previously registered `network handle'.  A
;;; `network handle' is an association between a local item and a fixnum that is
;;; registered using the system procedure register-on-network-lisp-side.  This
;;; association is useful when an object cannot be copied each time it is sent
;;; across a network, say, for efficiecy reasons or because it has system
;;; attributes that cannot be transmitted (as of 5/27/94, this is the case with
;;; all system attributes).

;;; If get-procedure-argument-list-error-if-any determines that the fixnum is a
;;; handle, and the handled object is of the appropriate class given the
;;; argument description, this function will side-effect the procedure argument
;;; list by replacing the fixnum with the handled object and return nil.
;;; The same functionality has just been added for UUIDs, both in their binary
;;; and text form. -dkuznick, 5/13/04
;;; Otherwise, as usual, this function will return an error text string
;;; describing the problem.

(defun get-procedure-argument-list-error-if-any
    (procedure argument-list icp-socket)
  (let* ((system-rpc-p (system-rpc-p procedure))
	 argument-descriptions arg-count procedure-or-procedure-name)
    (cond (system-rpc-p
	   (setf argument-descriptions (system-rpc-argument-types procedure))
	   (setf procedure-or-procedure-name
		 (system-rpc-lisp-function procedure)))
	  (t
	    (setf argument-descriptions (argument-list-description procedure))
	    (setf procedure-or-procedure-name procedure)))
    (setf arg-count (var-count argument-descriptions))
    (if (/=f arg-count (length argument-list))
	(tformat-text-string
	  "~NA requires ~a argument~a and received ~a."
	  procedure-or-procedure-name
	  (var-count argument-descriptions)
	  (if (=f (var-count argument-descriptions) 1) "" "s")
	  (length argument-list))
	(loop for index from 0 below arg-count
	      for arg-name = (var-name-from-index argument-descriptions index)
	      for type = (var-type-from-index argument-descriptions index)
	      for argument? in argument-list
	      for argument-cons on argument-list
	      do
	  (unless (or system-rpc-p argument?)
	    (return
	      (twith-output-to-text-string
		(twrite-string "The ")
		(print-name-of-variable-and-description arg-name type)
		(tformat
		  " argument of ~NA is declared to take values of type ~
                   ~a, but this procedure received a bad value instead."
		  procedure-or-procedure-name
		  type))))
	  (unless (receiving-resumable-object-p argument?)
	    (when (evaluation-unsigned-vector-16-p argument?)
	      (setq argument? (prog1 (evaluation-unsigned-vector-16-value argument?)
				(reclaim-eval-cons argument?)))
	      (setf (car argument-cons) argument?))
	    (cond
	      ((null argument?)		; only reached if system-rpc-p
	       (unless (type-specification-type-p argument? type)
		 (return
		   (twith-output-to-text-string
		     (twrite-string "The ")
		     (print-name-of-variable-and-description arg-name type)
		     (tformat
		       " argument of ~NA is declared to take values of type ~
                        ~NT, but it received NO-VALUE."
		       procedure-or-procedure-name
		       type)))))
	      ((if system-rpc-p ; system-rpc's can handle unsigend-vector-16's
		                ; which are not yet subtype of datum
		   (and (valid-type-specification-p type)
			(type-specification-subtype-in-kb-p
			  type '(or evaluation-value (no-item))))
		   (valid-datum-type-specification-p type))
	       (unless (evaluation-value-p argument?)
		 (return
		   (twith-output-to-text-string
		     (twrite-string "The ")
		     (print-name-of-variable-and-description arg-name type)
		     (tformat
		       " argument of ~NA is declared to take values of type ~
                        ~NT, but it received ~NF, ~
                        an instance of the class ~a."
		       procedure-or-procedure-name
		       type
		       argument?
		       (class argument?)))))
	       (unless (or
			 (value-type-compatible type (evaluation-value-type argument?))
			 (type-specification-subtype-p (evaluation-value-type argument?) type))
		 (return
		   (twith-output-to-text-string
		     (twrite-string "The ")
		     (print-name-of-variable-and-description arg-name type)
		     (tformat
		       " argument of ~NA is declared to take values ~
                        of type ~NT, but it received "
		       procedure-or-procedure-name
		       type)
		     (write-evaluation-value argument?)
		     (twrite-string ".")))))
	      ((eq type 'item-or-datum))
	      ((evaluation-value-p argument?)
	       (block transform-handled-object-if-possible
		 (when (class-type-specification-p type)
		   (let ((handled-object?
			   (cond ((evaluation-integer-p argument?)
				  (get-item-from-local-handle
				    (evaluation-integer-value argument?)
				    icp-socket))
				 ((evaluation-text-p argument?)
				  ;; We are checking the class below for both
				  ;; cases, so no need to specify it here
				  (the-item-having-uuid nil argument?))
				 (t nil))))
		     (when (and handled-object?
				(frame-of-class-p handled-object?
						  (type-specification-class
						    type)))
		       (reclaim-evaluation-value argument?)
		       (setf (car argument-cons) handled-object?)
		       (return-from transform-handled-object-if-possible))))
		 (return
		   (twith-output-to-text-string 
		     (twrite-string "The ")
		     (print-name-of-variable-and-description arg-name type)		     
		     (tformat
		       " argument of ~NA is declared to take instances  ~
                         of the class ~a, but it received the value "
		       procedure-or-procedure-name
		       (type-specification-class type))
		     (write-evaluation-value  argument?)
		     (twrite-string ".")))))
	      ((not (frame-of-class-p
		      argument?
		      (type-specification-class type)))
	       (return
		 (twith-output-to-text-string
		   (twrite-string "The ")
		   (print-name-of-variable-and-description arg-name type)
		   (tformat
		     " argument of ~NF is declared to take instances of the ~
                      class ~a, but it received ~NF, ~
                      an instance of the class ~a."
		     procedure
		     (type-specification-class type)
		     argument?
		     (class argument?)))))))))))



;;; The function `reclaim-lisp-call-argument-list' takes a lisp-function
;;; argument list and reclaims its eval-conses and any evaluation-values within
;;; it.

(defun reclaim-lisp-call-argument-list (argument-list)
  (when argument-list
    (loop for arg-trailer = nil then argument-cons
	  for argument-cons = argument-list then (cdr-of-cons argument-cons)
	  while argument-cons
	  for argument = (car-of-cons argument-cons)
	  do
      (reclaim-if-evaluation-value argument)
	  finally
	    (reclaim-eval-list-given-tail argument-list arg-trailer))))





;;;; P-Code Instruction Definitions




;;; This section contains definitions for procedures pseudo-code instructions.
;;; Note that they should be given here in numeric order, that if two
;;; instructions are defined for the same number, then the second one "wins",
;;; and that the number-of-procedure-p-code-instructions parameter above must
;;; contain an accurate count of the total number of instructions.

;;; Instruction 0, the `DATUM-ASSIGN p-code instruction' sets a variable value
;;; in this environment to the value of an evaluated expression.  Its first
;;; argument is the var-spot to put the result, and its second argument is the
;;; expression to evaluate.
;;;
;;;   (DATUM-ASSIGN var-spot expression)




;;; Instruction 1, the `ITEM-ASSIGN p-code instruction' sets a variable value in
;;; this environment to the item denoted by a designation.  Its first argument
;;; is the var-spot to put the result, and its second argument is the
;;; designation to evaluate.
;;;
;;;   (ITEM-ASSIGN var-spot designation)






;;; Instruction 2, the `ASSIGN-TYPE-AND-VALUE p-code instruction' is used to
;;; override and reclaim any existing value in the given var-spot and change
;;; that spot's type and value to the given type and the value of the given
;;; expression.  This is used by the returning mechanisms to set up return
;;; values from code body invocations other than the base.  The DATUM-ASSIGN and
;;; ITEM-ASSIGN instructions are preferred in the most situations.
;;;
;;;   (ASSIGN-TYPE-AND-VALUE var-spot type expression)






;;; Instruction 3, the `BRANCH p-code instruction' takes an instruction number
;;; and causes execution of the code body invocation to continue at that
;;; instruction.
;;;
;;;   (BRANCH instruction-index)




;;; Instruction 4, the `BRANCH-IF-TRUE p-code instruction' evaluates a logical
;;; expression, and if that expression is as true as or truer than the
;;; truth-threshold in the inference engine parameters, it then it executes a
;;; branch to the given instruction address.
;;;
;;;   (BRANCH-IF-TRUE logical-expression target-address)




;;; Instruction 5, the `BRANCH-IF-NOT-TRUE p-code instruction' evaluates a
;;; logical expression, and if the result is not as true as or truer than the
;;; truth-threshold of the inference engine parameters, it then branches to the
;;; given instruction.
;;;
;;;   (BRANCH-IF-NOT-TRUE logical-expression target-address)




;;; Instruction 6, the `JUMP p-code instruction' performs a branch statement
;;; between code-body-invocations.  This instruction pops the stack of code body
;;; callers as many levels as are specified in the first argument, and begins
;;; execution of that code body invocation at the instruction given in its
;;; second argument.  The target code body invocation is filo enqueued on the
;;; immediate stack so that this is a wait state free branch with no intervening
;;; executions of other code bodies.




;;; Instruction 7, the `CASE-DISPATCH p-code instruction' performs evaluates an
;;; expression returning an integer, and performs a branch to a corresponding
;;; instruction for the value of that expression, using a array to dispatch.  If
;;; the value of the expression is out of bounds of the table, then control is
;;; transfered to the else instruction.  If the else instruction is NIL, or if
;;; the value of the element of the dispatch table is NIL, then a level 1 error
;;; is signalled.
;;;
;;;   (CASE-DISPATCH expression table-base table-length
;;;                  instruction-table else-instruction)




;;; Instruction 8, the `RETURN-VALUES p-code instruction' returns a possibly
;;; empty set of values to the caller of this procedure, and file schedules
;;; immediate execution of the caller.  If there is no caller, then none of the
;;; expressions are evaluated.  After possibly returning values this code body
;;; invocation is closed (closing the procedure invocation as well) and the code
;;; body invocation interpreter is halted for this invocation.
;;;
;;;   (RETURN-VALUES (expression ...))




;;; Instruction 9, the `CALL p-code instruction' takes a procedure definition
;;; designation, a list of arguments, and a list of the types of the desired
;;; return values, and begins a call to the denoted procedure.  The
;;; RECEIVE-VALUES instruction must be used to accept the values returned by the
;;; called instruction.
;;;
;;;   (CALL designation (expressions ...) desired-value-types)




;;; Instruction 10, the `RECEIVE-VALUES p-code instruction' takes a set of
;;; var-spots, and will unpack returned values from a procedure call into the
;;; set of var-spots.  The length of the list of var-spots must agree with the
;;; length of the desired value types list given in the CALL instruction which
;;; should immediately preceed any call to this instruction.
;;;
;;;   (RECEIVE-VALUES (var-spot ...))




;;; Instruction 11, the `ALLOW-OTHER-PROCESSING p-code instruction' takes no
;;; arguments.  If the current time slice is expired, this statement causes a
;;; code body to enter a wait state, while scheduling itself for execution on
;;; the queue of code body invocations currently waiting for processing.  This
;;; will cause all other procedure instances waiting at this priority to get
;;; some processing time before this one gets another time slice.
;;;
;;;   (ALLOW-OTHER-PROCESSING)




;;; Instruction 12, the `OPEN-ITEM-ITERATION p-code instruction' takes a generic
;;; designation to be served, a var-spot to put the first value, a var-spot to
;;; put a continuation stack, and an instruction to branch to if there is no
;;; value to be served.
;;;
;;;   (OPEN-ITEM-ITERATION
;;;     simple-designation continuation-var-spot value-var-spot
;;;     no-value-branch)




;;; Instruction 13, the `OPEN-DATUM-ITERATION p-code instruction' takes a
;;; generic designation to be served which returns a datum, a var-spot to put
;;; the first value, a var-spot to put a continuation stack, and an instruction
;;; to branch to if there is no value to be served.
;;;
;;;   (OPEN-DATUM-ITERATION
;;;     simple-designation continuation-var-spot value-var-spot
;;;     no-value-branch)




;;; Instruction 14, the `SERVE-NEXT-ITEM-ITERATION p-code instruction' takes a
;;; var-spot containing a continuation stack or NIL, a var-spot to put the next
;;; value served from the continuation, and an instruction to branch to if there
;;; are no more values to be served.
;;;
;;;   (SERVE-NEXT-ITEM-ITERATION
;;;     continuation-var-spot value-var-spot no-value-branch-instruction)




;;; Instruction 15, the `SERVE-NEXT-DATUM-ITERATION p-code instruction' takes a
;;; var-spot containing a continuation stack or NIL, a var-spot to put the next
;;; value served from the continuation, and an instruction to branch to if there
;;; are no more values to be served.
;;;
;;;   (SERVE-NEXT-DATUM-ITERATION
;;;     continuation-var-spot value-var-spot no-value-branch-instruction)




;;; Instruction 16, the `CLOSE-ITERATION p-code instruction' takes a
;;; var-spot containing a continuation stack or NIL, and ensures that any
;;; continuations stored there have been closed.
;;;
;;;   (CLOSE-ITERATION continuation-var-spot)




;;; Instruction 17, the `POLLED-WAIT p-code instruction' takes an inferred
;;; logical expression and a procedure wait interval expression.  This
;;; instruction will test the inferred expression, and continue if it returns
;;; true, cancelling any tasks for wake up.  If not, the program counter is
;;; decremented so that this statement will be attempted again, and a task is
;;; scheduled to wake up this code body invocation at the time given in the wait
;;; interval expression.  Wake ups from an unsuccessful evaluation attempt may
;;; wake this code body invocation up again to receive a value.
;;;
;;; Note that this instruction should signal an error if executed within a
;;; simulation procedure.
;;;
;;;   (POLLED-WAIT inferred-logical-expression wait-interval-expression)




;;; Instruction 20, the `START p-code instruction' takes a designation, an
;;; argument list, an optional overriding priority expression, and an optional
;;; wait interval expression.  This statement will cause the designated
;;; procedure to be invoked on the given arguments after the wait interval and
;;; at the given priority or at its default priority.  This procedure does not
;;; relinquish the processor after executing this statement.

;;; Note that the START instruction should signal an error if executed within a
;;; simulation procedure.

;;;   (START designation argument-list priority? wait? across?)



;;; Instruction 21, the `WAIT-FOR p-code instruction' takes an expressions which
;;; returns a time interval, and causes this code body invocation to go to sleep
;;; for that interval of time.

;;; Note that the wait-for instruction has been renamed wait-for-interval.  -jra
;;; 5/6/91

;;;   (WAIT-FOR-INTERVAL interval-expression)




;;; Instruction 22, the `SIGNAL-ERROR p-code instruction' takes a symbol naming
;;; an error type, and executes the appropriate procedure-error code for that
;;; error.  In Release 2.1 this will have to be abstracted to fit into an error
;;; system we'll need for the ON ERROR stuff, but for now all code for error
;;; handling should just be inlined here.

;;; In anticipation of the new error handling system, this instruction
;;; has been rewritten to to take two expressions returning a symbol and
;;; a string.  These symbols and strings will be the name and textual
;;; description of the error.  -jra 4/10/91

;;;   (SIGNAL-ERROR error-name-symbol)




;;; Instruction 23, the `ABORT-CALLED-CODE-BODIES p-code instruction' is used to
;;; abort all called code body invocations from the executing code body
;;; invocation.
;;;
;;;   (ABORT-CALLED-CODE-BODIES)




;;; Instruction 24, the `CLOSE-CODE-BODY p-code instruction', closes
;;; the current code body invocation, and causes the caller of this invocation
;;; to be filo scheduled for immediate execution.  This instruction is used to
;;; finish parallel code bodies.
;;;
;;;   (CLOSE-CODE-BODY)




;;; Instruction 25, the `WAIT-FOR-CALLED-CODE-BODIES p-code instruction' is used
;;; to resynchronize execution in a code body which has launched parallel code
;;; bodies.  This instruction will wait until all called code bodies have
;;; returned.
;;;
;;;   (WAIT-FOR-CALLED-CODE-BODIES)




;;; Instruction 26, the `CALL-CODE-BODY p-code instruction' is used to launch a
;;; parallel, called code body invocation from the current code body invocation.
;;; The expressions are arguments to the code body invocation, and will be
;;; placed into the first N positions in the new environment.
;;;
;;;   (CALL-CODE-BODY code-body-number .  expressions)




;;; Instruction 27, the `PAUSE p-code instruction' is used to enter a wait state
;;; for this proceudre, waiting for something else to restart its processing.
;;; On restart, processing proceeds again at the next instruction.

;;;   (PAUSE)




;;; Instruction 28, the `COLLECT-DATA p-code instruction' is used to collect
;;; data, with timeouts and flags recording whether or not data was collected.
;;; The instruction takes four arguments: a list of pairs of var-spots and
;;; expressions, a nil or the var-spot containing the timestamp of the timeout
;;; time, an instruction address to branch to if all collections completed, and
;;; an instruction address to branch to if the collection timed out.

;;; If all datum-evaluates of the expressions succeed, values will be set into
;;; the var-spots given, all failed to receive a value flags for those var-spots
;;; will be set to 0, and control will be branched to the completion instruction
;;; address.  If any of the expressions returned unknown and there is no
;;; timeout, wake ups will be set from the variables that had no values to the
;;; currently executing code body invocation, the program counter will be set to
;;; resume at this instruction again, and the invocation will enter a wait
;;; state.  If any of the expressions returned unknown, there is a timeout
;;; given, and the timeout has not expired, a task will be scheduled for the
;;; timeout time to wake up this invocation, wake ups will be set from the
;;; variables that had no values, the program counter will be set to resume at
;;; this instruction, and a wait state will be entered.  If any of the
;;; expressions returned unknown, there is a timeout, and the timeout has
;;; expired, then those var-spots whose expressions returned values will be
;;; mutated, their failed to receive a value flags will be set to 0, the
;;; var-spots whose expressions had no values will not be mutated, but their
;;; failed flags will be set to 1, and finally the program counter will be
;;; resumed at the timeout instruction.  Note that if there is no timeout time
;;; given, no timeout instruction address need be given.
;;;
;;; Note that it is an error to execute this statement in a simulation
;;; procedure.

;;;   (COLLECT-DATA ((var-spot expression) ...)
;;;     evals-succeeded-spot timeout-varspot?
;;;     completed-instruction failed-instruction)




;;; Instruction 29, the `SYSTEM-CALL p-code instruction' takes a
;;; local-name-list, a lisp-function-name (a symbol), and a list of argument
;;; expressions.

;;; Note, that this was previously called lisp-call and was removed in case
;;; users can ever see the text of system procedures.  cpm, 6/30/91.

;;; This instruction evaluates the arguments in the procedure environment, calls
;;; the lisp-function named by the symbol, which is not evalled, and if there
;;; are any local-names, stores the return values of the Lisp call into the
;;; given local variables of the procedure.  When this instruction is executed,
;;; the calling procedure does not enter a "wait" state.  The lisp function is
;;; funcalled directly and is not scheduled.

;;; Any extra arguments returned by the Lisp function are ignored.  Any missing
;;; return values produce a level 1 procedure error.  The maximum number of
;;; arguments and return values are restricted by the constants
;;; maximum-number-of-lisp-call-arguments and
;;; maximum-number-of-lisp-call-return-values.  If the type of any return values
;;; is not compatible with the corresponding local name, a level 1 procedure
;;; error is signaled.

;;; Note that the arguments to the Lisp function are converted to
;;; evaluation-values.  The return values from the Lisp funcion must also be
;;; evaluation-values.

;;; This instruction can only be compiled in DEVELOPMENT, since they should only
;;; be used in system-procedures.  It can, of course, be executed in development
;;; and non-development.

;;; IMPORTANT NOTE:
;;; The funcalled lisp-function must be declared with declare-funcallable-symbol
;;; and must use the evaluation-value abstraction in SETS to handle arguments and
;;; return values.

;;;   (SYSTEM-CALL var-spot-list? symbol (expression ...))



;;; The function `execute-lisp-call-statement' does the work of the lisp-call
;;; instruction.  See that instruction for documentation.  

;;; The Lisp function is being passed evaluation-value or item args.  The
;;; evaluation-args should be reclaimed by the called Lisp function.  The return
;;; values from the Lisp function, like the args, must be evaluation-values, which
;;; will be reclaimed by the recipient, or items.  The Lisp function can delete an
;;; item argumnet passed to it, but that deleted item should not then be a return
;;; value.

;; In execute-lisp-call-statement, do we need to call
;; reclaim-code-body-environment-values (which reclaims temporary-constants and
;; closes role-value-servers) and set the procedure-environment-type of the
;; var-spot as in execute-call-statement??  cpm, 2/26/91.






;;;; Generating Code Body Invocations




;;; The system variable `top-level-procedure-invocations-array' contains a
;;; managed-array holding all of the procedure-invocations which have been
;;; independently started or called via an incoming remote-procedure-call
;;; message.  This is the root list of the tree of all currently executing
;;; procedure invocations.  Note that when procedure-invocations are closed, NIL
;;; is placed into the location in this array which had previously pointed to
;;; that procedure-invocation, so this array is sparse, in that the other
;;; invocations are not packed down.  This array and the minimum-index into it
;;; should only be modified by the functions register-top-level-procedure-
;;; invocation and deregister-top-level-procedure-invocation.

;;; The variable `minimum-available-procedure-invocation-index' holds a fixnum
;;; which is the lowest index into the top-level-procedure-invocations-array
;;; which could hold a NIL.  When there are no available NIL locations in the
;;; array, then this value will be equal to the length of the array.

(declare-special-global top-level-procedure-invocations-array)
(def-system-variable top-level-procedure-invocations-array proc-utils
  (:funcall allocate-managed-array 0))

; (def-system-variable top-level-procedure-invocations proc-utils nil)

(declare-special-global minimum-available-procedure-invocation-index)
(def-system-variable minimum-available-procedure-invocation-index proc-utils 0)

;;; the lock is to protect parallel access to above global array and variable, in the
;;; future we need to lockfree solution. -- Chun Tian (binghe), Apr 2015.

#+SymScale
(defvar-of-special-global procedure-invocations-lock
  (tx:make-recursive-lock :name "PROCEDURE-INVOCATION-LOCK"))


;;; The void function `register-top-level-procedure-invocation' takes a
;;; procedure-invocation structure and registers it as a top-level
;;; procedure-invocation.  This is done by placing it into the
;;; top-level-procedure-invocations-array at the first available NIL index, or
;;; by extending that array by one.

(defun-void #-SymScale register-top-level-procedure-invocation
	    #+SymScale register-top-level-procedure-invocation-1 (procedure-invocation)
  (let* ((top-array top-level-procedure-invocations-array)
	 (length (managed-array-length top-array))
	 (min-index minimum-available-procedure-invocation-index)
	 (index min-index))
    (declare (type fixnum length min-index index))
    (incff min-index)
    (cond ((=f length index)
	   (setq top-array (adjust-managed-array top-array min-index))
	   (setq top-level-procedure-invocations-array top-array))
	  (t
	   (loop while (and (<f min-index length)
			    (managed-svref top-array min-index))
		 do (incff min-index))))
    (setq minimum-available-procedure-invocation-index min-index)
    (setf (managed-svref top-array index) procedure-invocation)
    (setf (procedure-invocation-top-level-array-index? procedure-invocation)
	  index)))

#+SymScale
(defmacro register-top-level-procedure-invocation (procedure-invocation)
  `(tx:with-lock-held (procedure-invocations-lock)
     (register-top-level-procedure-invocation-1 ,procedure-invocation)))

;;; The void function `deregister-top-level-procedure-invocation' takes a
;;; procedure-invocation that is being closed, and removes it from the set of
;;; top-level procedure-invocations.

(defun-void #-SymScale deregister-top-level-procedure-invocation
	    #+SymScale deregister-top-level-procedure-invocation-1 (procedure-invocation)
  (let ((index (procedure-invocation-top-level-array-index? procedure-invocation)))
    (declare (type fixnum index))
    (when (<f index minimum-available-procedure-invocation-index)
      (setq minimum-available-procedure-invocation-index index))
    (setf (managed-svref top-level-procedure-invocations-array index) nil)))

#+SymScale
(defmacro deregister-top-level-procedure-invocation (procedure-invocation)
  `(tx:with-lock-held (procedure-invocations-lock)
     (deregister-top-level-procedure-invocation-1 ,procedure-invocation)))

#+ignore ;; SymScale
(progn

(defmacro procedure-hash (procedure)
  `(frame-serial-number-hash (frame-serial-number ,procedure)))

(def-hash-table top-level-procedures
  :constructor make-toplevel-procedures-table
  :hash-function-or-macro procedure-hash)

(declare-special-global top-level-procedures-table)
(def-system-variable top-level-procedures-table proc-utils
  (:funcall make-toplevel-procedures-table))

(defvar-of-special-global current-procedure-lock
  (tx:make-lock :name "CURRENT-PROCEDURE-LOCK"))

(defun-simple current-procedure-is-running? (procedure-invocation)
  (let ((procedure (procedure-of-invocation procedure-invocation)))
    (get-top-level-procedures procedure top-level-procedures-table)))

(defun-simple try-register-current-procedure (procedure-invocation)
  (let ((procedure (procedure-of-invocation procedure-invocation)))
    (tx:with-lock-held (current-procedure-lock)
      (if (get-top-level-procedures procedure top-level-procedures-table)
	  nil
	(progn
	  (setf (get-top-level-procedures procedure top-level-procedures-table) t)
	  procedure)))))

(defun-simple unregister-current-procedure (procedure)
  (tx:with-lock-held (current-procedure-lock)
    (if (get-top-level-procedures procedure top-level-procedures-table)
	(setf (get-top-level-procedures procedure top-level-procedures-table) nil)
      (error "procedure is already unregistered?!"))))

) ; progn #+SymScale
	

;;; The function `install-procedure-invocation-completion-form' takes a
;;; procedure-invocation structure and a completion form, and installs that
;;; completion form on the given procedure.  The effect of this installation is
;;; that the completion form will be executed when the procedure invocation
;;; exits, no matter if it exits by a normal return or because the procedure has
;;; been aborted (these are the only two ways for a procedure to exit).  In this
;;; respect, the completion form is like an unwind-protect around the body of
;;; the procedure invocation.  This form is currently used for simulation
;;; procedures, and is being considered for clean-up for field edit system
;;; procedures.

;;; The format of a completion form is a cons whose car is a funcallable symbol.
;;; The symbol-function of that symbol will be funcalled with the entire
;;; completion form as its only argument.  This function is responsible for
;;; reclaiming the completion form.

;;; The macro `install-code-body-invoation-completion-form' is the same
;;; operation, but instead it takes a code body invocation.  Note that the
;;; completion form is installed on the procedure invocation of this code body
;;; invocation, so users of "on error" or other code-body creating forms need to
;;; take care that they don't have a different scope for the code body
;;; invocation vs. the procedure invocation.

(def-substitution-macro install-procedure-invocation-completion-form
    (procedure-invocation completion-form)
  #+development
  (when (procedure-invocation-completion-form? procedure-invocation)
    (error "Overwriting existing completion form!"))
  (setf (procedure-invocation-completion-form? procedure-invocation)
	completion-form))

(defun install-procedure-invocation-completion-form-function
    (procedure-invocation completion-form)
  (install-procedure-invocation-completion-form procedure-invocation completion-form))

(defun install-code-body-invocation-completion-form
    (code-body-invocation completion-form)
  (install-procedure-invocation-completion-form
    (procedure-invocation-of-code-body code-body-invocation)
    completion-form))





;;; The function `generate-procedure-and-code-body-invocation' takes a procedure
;;; frame and a calling code body invocation, and generates a code body
;;; invocation to accept the requested call.  This function performs all
;;; necessary initializations for a new call to a procedure, including modifying
;;; the environment to accept the new argument values.  It does not enqueue the
;;; new invocation for execution, since the mode of enqueueing depends on the
;;; semantics of the caller.

;;; Also note that the calling-code-body? can be a remote-procedure-call.  In
;;; this case the calling-code-body? will not have a
;;; procedure-invocation-of-code-body.  Other than setting up the calling
;;; procedure invocation, this kind of object should be treated the same as any
;;; other code-body-invocation.

;;; This function never raises a stack error.  The way an error is handled
;;; depends on the top-of-stack? argument.  If it's :error-string, a text-string
;;; is returned.  If it's nil, a warning message is posted and nil is returned.
;;; Otherwise, an error-text is returned.

;; Note that there is a leak in this function when stack error is called, in
;; that the argument list and completion form are not being reclaimed.  Also
;; note that many callers of this function have an extra cons for a frame serial
;; in the generated argument list, and that this cons may not get reclaimed in
;; most circumstances either.  -jra 9/5/91

;; I think the above comment is referring to
;; generate-procedure-and-code-body-invocation-in-place and not
;; generate-procedure-invocation-error. -dkuznick, 7/16/04

(defun generate-procedure-invocation-error
    (top-of-stack? format-string &optional arg1 arg2 arg3)
  (cond ((eq top-of-stack? ':error-string)
	 (tformat-text-string format-string arg1 arg2 arg3))
	(top-of-stack?
	 (tformat-stack-error-text-string format-string arg1 arg2 arg3))
	(t
	 (warning-message* 1 format-string arg1 arg2 arg3)
	 nil)))

(defun generate-procedure-and-code-body-invocation-in-place
    (procedure calling-code-body? local-stack
	       top-of-arguments-on-stack incoming-argument-count 
	       simulation-procedure? completion-form? top-of-stack?
	       arguments-known-to-be-correct-p prepare-p thread?)
  (let (saved-procedure invocation-class argument-count)
    (when prepare-p
      (when (and (or (eq prepare-p 'start) (eq prepare-p 'call))
		 (frame-of-class-p procedure 'method-declaration)
		 (error-text-p
		   (setq procedure
			 (get-specific-method-for-stack
			   (setq saved-procedure procedure)
			   local-stack
			   (1+f (-f top-of-arguments-on-stack incoming-argument-count))
			   incoming-argument-count))))
	(return-from generate-procedure-and-code-body-invocation-in-place
	  (generate-procedure-invocation-error
	    top-of-stack?
	    "Cannot ~a method-declaration ~NF.  ~a"
	    (if (eq prepare-p 'start) "start" "call")
	    saved-procedure procedure)))
      (let ((error-text? 
	      (prepare-procedure-argument-list-in-place-for-stack-procedure
		procedure local-stack top-of-arguments-on-stack
		incoming-argument-count arguments-known-to-be-correct-p)))
	(when error-text?
	  (return-from generate-procedure-and-code-body-invocation-in-place
	    (prog1 (generate-procedure-invocation-error
		     top-of-stack? "~NW" error-text?)
	      (reclaim-error-text error-text?))))))
    (cond
      ((not (runnable-p procedure))
       (generate-procedure-invocation-error
	 top-of-stack?
	 "Cannot execute ~NF because it is ~a."
	 procedure (reason-not-runnable procedure)))
      ((and (setq invocation-class (class-of-procedure-invocation procedure))
	    (not (eq invocation-class 'procedure-invocaton))
	    (not (subclassp invocation-class 'procedure-invocation)))
       (generate-procedure-invocation-error
	 top-of-stack?
	 "The class of procedure invocation attribute of ~NF, ~a, was ~
          not procedure-invocation or a subclass of procedure-invocation."
	 procedure invocation-class))
      ((/=f incoming-argument-count
	    (setq argument-count (argument-count procedure)))
       (generate-procedure-invocation-error
	 top-of-stack?
	 "Call to ~NF has argument count mismatch."
	 procedure))
      (t
       (let ((invocation (make-procedure-invocation-macro))
	     (invocation-frame?
	       (when invocation-class
		 (make-procedure-invocation-frame
		   invocation-class (runs-while-inactive-p procedure)))))
	 (when invocation-frame?
	   (setf (procedure-invocation-structure-of-procedure-invocation invocation-frame?)
		 invocation))
	 (when profiling-enabled?
	   (increment-profiling-calls procedure))
	 ;; moved this one a little earlier.
	 (setf (code-body-invocation-frame-serial-number invocation)
	       (copy-frame-serial-number (current-frame-serial-number)))

	 ;; using new API to support both legacy and multi-threading G2.
	 (push-one-procedure-invocation invocation procedure)

	 (when calling-code-body?
	   (proc-push invocation (called-code-bodies calling-code-body?)))
	 (if (and calling-code-body?
		  (not (rule-instance-p calling-code-body?))
		  (procedure-invocation-of-code-body calling-code-body?))
	     (setf (procedure-invocation-top-level-array-index? invocation) nil)
	     (register-top-level-procedure-invocation invocation))
	 (setf (procedure-of-invocation invocation) procedure)
	 (setf (tracing-and-breakpoints-of-procedure-invocation invocation)
	       (let ((procedure-tracing? (tracing-and-breakpoints procedure)))
		 (if procedure-tracing?
		     (copy-for-slot-value procedure-tracing?))))
	 (setf (simulation-procedure-invocation? invocation) simulation-procedure?)
	 (install-procedure-invocation-completion-form invocation completion-form?)
	 (setf (frame-of-procedure-invocation invocation) invocation-frame?)
	 (setf (code-body-caller invocation) calling-code-body?)
	 (setf (invocation-stack-program-counter invocation) 0)
	 (setf (code-body-invocation-priority invocation)
	       (default-procedure-priority procedure))
	 (setf (procedure-invocation-of-code-body invocation) invocation)
	 (setf (called-code-bodies invocation) nil)
	 (let ((base-code-body (car-of-cons (code-bodies procedure))))
	   (setf (invocation-return-value-position invocation)
		 (return-value-position base-code-body))
	   (setf (invocation-return-value-count invocation)
		 (maximum-received-value-count base-code-body))
	   (setf (code-body-of-invocation invocation) base-code-body)
	   (let ((byte-code-body (code-body-byte-code-body base-code-body)))
	     (setf (invocation-byte-code-body invocation) byte-code-body)
	     (setf (invocation-constant-vector invocation)
		   (byte-code-body-constant-vector byte-code-body)))
	   (let* ((called-environment-array-length (environment-length base-code-body))
		  (called-environment
		    (if (=f called-environment-array-length 0)
			nil
			(allocate-environment-vector
			  called-environment-array-length t))))
	     (setf (invocation-local-var-vector invocation)
		   called-environment)
	     (unless (=f called-environment-array-length 0)
	       ;; Initialize all locations in the vector to the corresponding
	       ;; argument, or NIL.
	       (loop with initial-stack-index = (1+f (-f top-of-arguments-on-stack argument-count))
		     for stack-index from initial-stack-index to top-of-arguments-on-stack
		     for index from 0
		     do (setf (svref called-environment index)
			      (svref local-stack stack-index))
			(setf (svref local-stack stack-index) nil)) ;keep reclamation sane
	       (loop for non-argument-index
		     from argument-count below (length-of-simple-vector called-environment)
		     do (setf (svref called-environment non-argument-index) nil)))))
	 (when thread?
	   (setf (code-body-invocation-thread invocation) thread?))
	 (maybe-set-lock-for-invocation invocation procedure)
	 invocation)))))




;;; The function `make-procedure-invocation' takes a symbol naming a subclass of
;;; procedure invocation and a flag indicating if this is a running-while-inactive
;;; procedure.  This function creates and returns an instance of this class for
;;; a procedure being executed.  If this is not a runs-while-inactive procedure,
;;; a transient item is returned.  If this procedure is enabled for running
;;; while inactive, then a permanent, non-kb-savable, and activated
;;; procedure-invocation is returned.

(defun-simple make-procedure-invocation-frame (class runs-while-inactive?)
  (if runs-while-inactive?
      (let ((new-invocation (make-frame class)))
	(set-permanent-and-propagate new-invocation nil)
	(set-do-not-save-in-kb new-invocation)
	(funcall-method 'activate-if-possible-and-propagate new-invocation)
	new-invocation)
      (make-transient-item class)))




;;; The function `generate-code-body-invocation' takes a code body and a calling
;;; code body invocation, and generates a code body invocation to accept the
;;; requested call.  This function performs all necessary initializations for a
;;; new call to a code body, except modifying the environment to accept the new
;;; argument values and enqueuing the new invocation for execution.

(defun-simple generate-code-body-invocation
	      (code-body-to-call calling-code-body thread?)
  (let ((invocation (make-code-body-invocation)))
    (when thread?
      (setf (code-body-invocation-thread invocation) thread?))
    (proc-push invocation (called-code-bodies calling-code-body))
    (setf (code-body-caller invocation) calling-code-body)
    (setf (code-body-of-invocation invocation) code-body-to-call)
    (let ((byte-code-body (code-body-byte-code-body code-body-to-call)))
      (setf (invocation-byte-code-body invocation) byte-code-body)
      (setf (invocation-constant-vector invocation)
	    (or (byte-code-body-constant-vector byte-code-body)
		(byte-code-body-constant-vector
		  (code-body-byte-code-body
		    (car-of-cons
		      (code-bodies
			(procedure-definition-of-code-body
			  code-body-to-call))))))))
    (setf (invocation-stack-program-counter invocation) 0)
    (setf (code-body-invocation-frame-serial-number invocation)
	  (copy-frame-serial-number (current-frame-serial-number)))
    (setf (code-body-invocation-priority invocation)
	  (code-body-invocation-priority calling-code-body))
    (setf (procedure-invocation-of-code-body invocation)
	  (procedure-invocation-of-code-body calling-code-body))
    (setf (called-code-bodies invocation) nil)
    (setf (invocation-return-value-position invocation)
	  (return-value-position code-body-to-call))
    (setf (invocation-return-value-count invocation)
	  (maximum-received-value-count code-body-to-call))
    (let* ((environment-length (environment-length code-body-to-call))
	   (called-environment
	     (if (/=f environment-length 0)
		 (allocate-environment-vector environment-length)
		 nil)))
      (setf (invocation-local-var-vector invocation)
	    called-environment)
      (loop for index fixnum from 0 below environment-length
	    do (setf (svref called-environment index) nil)))
    invocation))




;;; The variable `closing-procedure-invocation' binds the procedure inovocation
;;; from which a completion-form? is called.  This allows the completion
;;; form to have access to useful information about the context in which
;;; the completion-form is called.

(defvar closing-procedure-invocation nil)




;;; The function `close-procedure-invocation' takes a procedure invocation which
;;; has already had all of its code body invocations removed, and should now be
;;; deleted.

(defun close-procedure-invocation (procedure-invocation-to-delete)
  (let ((procedure (procedure-of-invocation procedure-invocation-to-delete))
	(completion-form?
	  (procedure-invocation-completion-form? procedure-invocation-to-delete))
	(procedure-invocation-frame
	  (frame-of-procedure-invocation procedure-invocation-to-delete)))
    ;; using new API to support both legacy and multi-threading G2.
    (delete-one-procedure-invocation
      procedure-invocation-to-delete procedure)
    (when (procedure-invocation-top-level-array-index? procedure-invocation-to-delete)
      (deregister-top-level-procedure-invocation procedure-invocation-to-delete))
    (when completion-form?
      (let ((closing-procedure-invocation procedure-invocation-to-delete))
	(funcall-symbol (car completion-form?) completion-form?)
	(setf (procedure-invocation-completion-form? closing-procedure-invocation)
	      nil)))
    (when procedure-invocation-frame
      (setf (procedure-invocation-structure-of-procedure-invocation procedure-invocation-frame) nil)
      (setf (frame-of-procedure-invocation procedure-invocation-to-delete) nil)
      (delete-frame procedure-invocation-frame))
    (reclaim-procedure-invocation-macro procedure-invocation-to-delete)))




;;; The function `reclaim-code-body-environment-values' takes a procedure code
;;; body environment and reclaims all data structures in the slots of that
;;; environment.  The start and end arguments specify a section of the
;;; environment that should be cleaned.  The portion traversed starts at start
;;; and continues up to but not including end.  Start defaults to 0, and end
;;; defaults to the number of var-spots in the environment.

(defun reclaim-code-body-environment-values
       (code-body-environment-to-reclaim environment-description start? end?)
  (declare (ignore environment-description))
  (loop for index from (or start? 0)
		  below (or end?
			    (length-of-simple-vector
			      code-body-environment-to-reclaim))
	for value? = (svref code-body-environment-to-reclaim index)
	do
    (setf (svref code-body-environment-to-reclaim index) nil)
    (unless (or (fixnump value?) (symbolp value?))	; Optimization.
      (reclaim-if-evaluation-value value?))))




;;; The function `modify-code-body-environment-var-spot' takes a code body
;;; invocation, a var spot index (the second of a var-spot) denoting a location
;;; within its environment or an environment which surrounds it, and a new
;;; evaluation value for that location.  The function modifies the location and
;;; returns the value placed in the location.  Any old value in the location is
;;; reclaimed.

(defun modify-code-body-environment-var-spot
       (code-body-invocation var-spot-index value)
  (let ((nesting (var-spot-index-nesting var-spot-index))
	(local-index (var-spot-local-index var-spot-index)))
    (loop repeat nesting do
      (setq code-body-invocation
	    (code-body-caller code-body-invocation)))
    (let ((environment-vector
	    (invocation-local-var-vector code-body-invocation)))
      (reclaim-if-evaluation-value (svref environment-vector local-index))
        (setf (svref environment-vector local-index) value)
      value)))




;;; The function `close-code-body-invocation' is called to reclaim a code body
;;; invocation which has completed its execution.  If this is the last code body
;;; invocation of its procedure invocation, that procedure invocation will be
;;; closed as well.

;;; If the code body invocation is the currently executing one, set the
;;; current-computation-instance variable to NIL to inform the current
;;; instruction that it should exit.  This is checked by the delete, abort, and
;;; deactivate instructions.

(defun-simple close-code-body-invocation (code-body-invocation)
  (loop with code-bodies-to-close = (proc-list code-body-invocation)
	while code-bodies-to-close
	for code-body-invocation = (car code-bodies-to-close)
	for called-invocations? = (called-code-bodies code-body-invocation)
	do (if called-invocations?
	       ;; This only aborts the first called invocation, not all of
	       ;; them. Is this a bug? -alatto, 9/5/06
	       (let ((invocation (first called-invocations?)))
		 (if (remote-procedure-call-p invocation)
		     (abort-outgoing-remote-procedure-call invocation)
		     (proc-push invocation code-bodies-to-close)))
	       (close-code-body-invocation-1 (proc-pop code-bodies-to-close)))))

(defun-simple close-code-body-invocation-1 (code-body-invocation)
  (let* ((code-body-environment-vector
	   (invocation-local-var-vector code-body-invocation))
	 (calling-code-body-invocation?
	   (code-body-caller code-body-invocation)))
    (when (eq code-body-invocation current-computation-instance)
      (setq current-computation-instance nil))
    (when (memq code-body-invocation all-computation-instances-above-breakpoint)
      (setq all-computation-instances-above-breakpoint
	    (delete-gensym-element code-body-invocation
				   all-computation-instances-above-breakpoint))
      (setq may-return-from-breakpoint nil))
    (clear-event-detectors code-body-invocation)
    (clean-up-ri-completion-notification-collection-back-pointer
      code-body-invocation)
    ;; Note that we release the lock whenever there is a reference,
    ;; even if the reference doesn't point to anything any more.
    ;; If there used to be a lock, but it has been deleted, there are
    ;; still cleanups that release-lock needs to do.
    (when (reference-to-item-to-lock code-body-invocation)
      (release-lock code-body-invocation))
    (let ((lock-holder (invocation-holding-lock-this-is-waiting-for code-body-invocation)))
      (when lock-holder
	;; TODO: use skip-list instead
	(setf (invocations-waiting-for-lock-held-by-this-invocation lock-holder)
	      (delete-proc-element
		code-body-invocation
		(invocations-waiting-for-lock-held-by-this-invocation lock-holder)))
	(setf (invocation-holding-lock-this-is-waiting-for code-body-invocation)
	      nil)))
    (when code-body-environment-vector
      (reclaim-environment-vector code-body-environment-vector))
    (cancel-task (invocation-schedule-task code-body-invocation))
    (loop with wake-ups = (things-this-code-body-invocation-is-interested-in
			    code-body-invocation)
	  for variable in wake-ups
	  do (remove-request-for-variable-value variable code-body-invocation)
	  finally (reclaim-eval-list-macro wake-ups))
    (setf (things-this-code-body-invocation-is-interested-in code-body-invocation) nil)
    (when calling-code-body-invocation?
      ;; TODO: use skip-list instead
      (setf (called-code-bodies calling-code-body-invocation?)
	    (delete-proc-element-macro
	      code-body-invocation
	      (called-code-bodies calling-code-body-invocation?))))
    (let (#+trace-invocations
	  (type-name (type-name-of-named-simple-vector code-body-invocation)))
      (if (procedure-invocation-p code-body-invocation)
	  (close-procedure-invocation code-body-invocation)
	(reclaim-code-body-invocation-macro code-body-invocation))
      #+trace-invocations
      (check-free-code-body-invocation code-body-invocation type-name))))


;;; `clean-up-ri-completion-notification-collection-back-pointer' is a helper function to
;;; clean out the ri-completion-notification-collection-back-pointer on a
;;; code-body-invocation.  In the future if/when we implement the ability to
;;; cancel all outstanding rule-instances in this collection, this will be the
;;; place to do it (though more infrastructure will be needed).

(defun-void clean-up-ri-completion-notification-collection-back-pointer
    (code-body-invocation)
  (let ((ri-completion-notification-collection-back-pointer?
	  (ri-completion-notification-collection-back-pointer
	    code-body-invocation)))
    (when ri-completion-notification-collection-back-pointer?

      ;; Remove the code-body-invocation from the shared list so the
      ;; rule-instances don't try to wake it up.
      (setf (cadr ri-completion-notification-collection-back-pointer?) nil)

      ;; Clean out the slot on the code-body-invocation.  This is not a leak as
      ;; this list is owned by the rule-instances being waited on. 
      (setf (ri-completion-notification-collection-back-pointer
	      code-body-invocation)
	    nil))))




;;;; Procedure Environment Validation


#+trace-invocations
(progn
  
(defvar current-code-body-invocation-mark 0)
(defvar object-to-find nil)
(defvar objects-referencing-object nil)

(defun object-use-error (&optional type-name)
  (format t "~%An object of type ~S is still in use at it's reclaim"
	  (or type-name
	      (type-name-of-named-simple-vector object-to-find)))
  (format t "~%Types of references to this object:")
  (loop with icp-sockets = nil
	for ref in objects-referencing-object
	for type = (type-name-of-named-simple-vector ref)
	do (format t "~%   ~S" type)
	   (when (eq type 'icp-socket) (gensym-push ref icp-sockets))
	finally (when icp-sockets
		  (format t "~%ICP sockets:")
		  (loop for icp-socket in icp-sockets
			for text-string
			    = (twith-output-to-text-string
				(twrite-icp-socket-connection-name icp-socket))
			do (notify-user-at-console "~A~%" text-string)
			   (reclaim-text-string text-string))))
  (format t "~%")
  (inline-g2-print-backtrace)
  #+development
  (break)
  nil)

(defvar check-for-object-use-error
  (let ((string? (get-gensym-environment-variable #w"G2_DEBUG_OBJECT_USE")))
    (cond (string?
	   (reclaim-text-string string?)
	   t)
	  (t
	   nil))))

(defun check-free-code-body-invocation (invocation &optional type-name)
  (when check-for-object-use-error
    (let ((object-to-find invocation))
      (mark-all-cbis-and-rpis)
      (when (eql (invocation-mark invocation) current-code-body-invocation-mark)
	(object-use-error type-name)))))

(defun check-free-remote-procedure-identifier (rpid)
  (when check-for-object-use-error
    (let ((object-to-find rpid))
      (mark-all-cbis-and-rpis)
      (when (eql (remote-procedure-identifier-mark rpid) current-code-body-invocation-mark)
	(object-use-error)))))

(defun-void mark-all-cbis-and-rpis ()
  (if (=f current-code-body-invocation-mark most-positive-fixnum)
      (setf current-code-body-invocation-mark 0)
      (incff current-code-body-invocation-mark))
  (loop with top-array = top-level-procedure-invocations-array
	for index from 0 below (managed-array-length top-array)
	for invocation? = (managed-svref top-array index)
	do (mark-code-body-invocation invocation? nil))
  (loop for icp-socket in active-icp-sockets
	do (mark-all-remote-procedure-identifiers-for-port (icp-input-port icp-socket) 'input)
	   (mark-all-remote-procedure-identifiers-for-port (icp-output-port icp-socket) 'output)))

(defun-void mark-code-body-invocation (invocation parent)
  (when (and invocation
	     (not (eql (invocation-mark invocation) current-code-body-invocation-mark)))
    (setf (invocation-mark invocation) current-code-body-invocation-mark)
    (when (eq object-to-find invocation)
      (gensym-push parent objects-referencing-object))
    (when (remote-procedure-call-p invocation)
      (mark-remote-procedure-identifier (remote-procedure-identifier-of-call invocation) invocation))
    (mark-code-body-invocation (code-body-caller invocation) invocation)
    (loop for child in (called-code-bodies invocation)
	  do (mark-code-body-invocation child invocation))))

(defun-void mark-remote-procedure-identifier (rpid parent)
  (when (and rpid
	     (not (eql (remote-procedure-identifier-mark rpid) current-code-body-invocation-mark)))
    (setf (remote-procedure-identifier-mark rpid) current-code-body-invocation-mark)
    (when (eq object-to-find rpid)
      (gensym-push parent objects-referencing-object))
    (mark-code-body-invocation (remote-procedure-identifier-caller rpid) rpid)
    (mark-code-body-invocation (remote-procedure-identifier-callee rpid) rpid)))

(defun-void mark-all-remote-procedure-identifiers-for-port (port direction)
  (declare (ignore direction))
  (when port
    (let ((index-space (standard-icp-object-index-space port)))
      (when index-space
	(loop with icp-socket = (parent-icp-socket port)
	      with vector-of-index-subspace-vectors
		= (vector-of-index-subspace-vectors index-space)
	      as i from 0 below (length vector-of-index-subspace-vectors)
	      as index-subspace-vector? = (svref vector-of-index-subspace-vectors i)
	      while index-subspace-vector?
	      do (loop for j from 0 below #.(index-space-vector-length)
		       for object? = (svref index-subspace-vector? j)
		       when (remote-procedure-identifier-p object?)
			 do (mark-remote-procedure-identifier object? icp-socket)))))))

)

;;; When a code body invocation is about to be executed, the environment needs
;;; to be validated, in case any frames within the environment have been
;;; deleted.  The function `validate-code-body-invocation-environment' should
;;; search any accessible environments from this code body invocation, and if
;;; any of the frames in its environment have been recycled, it should set those
;;; environment bindings to NIL.  If a reference is made to that environment
;;; spot, it is left to the spot accessors to recognize that it is empty and
;;; signal an error.

;;; The frame serial number stored in the code body invocation is reset to the
;;; current frame serial number on creation of the code body invocation, and on
;;; exit from execute code body invocation.

;;; Modified validate-code-body-invocation-environment to optionally:
;;; 1. validate the class of items in the environment,
;;; 2. not validate the code-body-callers of the code-body-invocation.
;;; These changes were needed to validate procedure-invocations after there has
;;; been a runtime change to KB definitions.  In this case, the class of an item
;;; may have changed.  Also, procedure code-body-invocations are being validated
;;; one at a time, starting at the base code-body-invocation and not from
;;; code-bodies to their callers.  - cpm, 3/16/94

;;; Modified validate-item-or-evaluation-value and valid-item-or-evaluation-
;;; value-p to taken an argument that specifies an type-specfication or NIL.
;;; When this argument is non-NIL, this type-specification is used to validate
;;; the type of the item or evaluation-value.  An example where this
;;; type-specification validation is needed is when an item class may have
;;; changed because of a KB runtime modification.  Note that place-references
;;; and action-caches do not use the type-spec validation.  - cpm, 3/16/94


;;; Note: validate-item-or-evaluation-value has been moved to types.


(defun-simple valid-item-or-evaluation-value-p
	      (value frame-serial-number type-spec-for-validation?)
  (cond
    ((frame-or-deleted-frame-p value)
     (and (not (frame-has-been-reprocessed-p value frame-serial-number))
	  (serve-item-p value)
	  (or (null type-spec-for-validation?)
	      (and (or (eq type-spec-for-validation? 'item-or-datum)
		       (valid-class-type-specification-p
			 type-spec-for-validation?))
		   (type-specification-type-p
		     value type-spec-for-validation?)))))
    ((evaluation-item-reference-p value)
     (evaluation-item-reference-referenced-item value))
    ((evaluation-place-reference-p value)
     (evaluation-place-reference-valid-p value))
    ((evaluation-action-cache-p value)
     (validate-evaluation-action-cache value frame-serial-number))
    (type-spec-for-validation?
     (and (or (eq type-spec-for-validation? 'item-or-datum)
	      (valid-datum-type-specification-p type-spec-for-validation?))
	  (type-specification-type-p value type-spec-for-validation?)))
    (t
     value)))


(defun-simple validate-code-body-invocation-environment
    (invocation-to-validate validate-item-classes-also?
			    do-not-validate-code-body-callers?)
  (let* ((current-computation-flags current-computation-flags)
	 (procedure-invocation? (procedure-invocation-of-code-body
				  invocation-to-validate))
	 (procedure? (if procedure-invocation?
			 (procedure-of-invocation procedure-invocation?)
			 nil)))
    (when procedure?
      (setf (role-serve-inactive-objects?)
	    (may-refer-to-inactive-items-p procedure?)))  
    (if (null validate-item-classes-also?)
	(loop for code-body-invocation-to-examine
		  = invocation-to-validate
		  then (code-body-caller code-body-invocation-to-examine)
	      for code-body-to-examine
		  = (code-body-of-invocation code-body-invocation-to-examine)
	      for code-body-environment-to-examine
		  = (invocation-local-var-vector
		      code-body-invocation-to-examine)
	      for environment-length fixnum
				     = (environment-length code-body-to-examine)
	      for frame-serial-number
		  = (code-body-invocation-frame-serial-number
		      code-body-invocation-to-examine)
	      do
	  (loop for index fixnum from 0 below environment-length
		for value? = (svref code-body-environment-to-examine index)
		do
	    (when value?
	      (setf (svref code-body-environment-to-examine index)
		    (validate-item-or-evaluation-value
		      value? frame-serial-number nil))))

	      until (or do-not-validate-code-body-callers?
			(base-code-body-invocation-p
			  code-body-invocation-to-examine)))
	(loop for code-body-invocation-to-examine
		  = invocation-to-validate
		  then (code-body-caller code-body-invocation-to-examine)
	      for code-body-to-examine
		  = (code-body-of-invocation code-body-invocation-to-examine)
	      for code-body-environment-to-examine
		  = (invocation-local-var-vector code-body-invocation-to-examine)
	      for environment-length fixnum
				     = (environment-length code-body-to-examine)
	      for environment-description
		  = (environment-description code-body-to-examine)
	      for frame-serial-number
		  = (code-body-invocation-frame-serial-number
		      code-body-invocation-to-examine)
	      do
	  (loop for index fixnum from 0 below environment-length
		for value? = (svref code-body-environment-to-examine index)
;	      for description in environment-description
		for item-type? = (if (framep value?)
				     (var-type-from-index
				       environment-description index)
				     nil)
		do
	    (when value?
	      (setf (svref code-body-environment-to-examine index)
		    (validate-item-or-evaluation-value
		      value? frame-serial-number item-type?))))

	      until (or do-not-validate-code-body-callers?
			(base-code-body-invocation-p
			  code-body-invocation-to-examine))))
    nil))



;;; The function `validate-computation-instance-environment' is a
;;; more general version of validate-code-body-invocation-environment
;;; because it can handle rule-instances as well as code-body invocations.
;;; All users of validate-code-body-invocation-environment now use this
;;; function with a slight extra cost in terms of recoginizing a
;;; code-body invocation and an extra function call,
;;; this makes all the call sites more robust.

(defun-simple validate-computation-instance-environment 
    (computation-instance validate-item-classes-also?
			  do-not-validate-code-body-callers?)
  (cond ((code-body-invocation-p computation-instance)
	 (validate-code-body-invocation-environment
	   computation-instance
	   validate-item-classes-also?
	   do-not-validate-code-body-callers?))
	((rule-instance-p computation-instance)
	 (validate-rule-context-vector
	   (invocation-local-var-vector computation-instance)
	   (rule-environment-length
	     (ri-rule computation-instance))
	   (ri-frame-serial-number computation-instance)
	   (ri-rule computation-instance)
	   nil))))


;;; The function `validate-environment-for-code-body-invocation-tree' validates
;;; the environment of the given code-body and all the code-bodies that it
;;; calls.

;;; Note that validate-code-body-invocation-environment normally validates in
;;; the "other direction", going from a code-body to its callers, back to the
;;; base code-body.  But, this function does the opposite.

(defun-void validate-environment-for-code-body-invocation-tree
    (code-body-invocation)
  ;; Validate the code-body, check the class of any items, not validating
  ;; calling code-bodies.  Since, we are validating in the "other direction" in
  ;; the code body graph (breadth-first-search), the called code bodies are
  ;; validated after this, below.
  (validate-computation-instance-environment code-body-invocation t t)
  (loop for called-code-body-invocation
	    in (called-code-bodies code-body-invocation)
	do
    (when (code-body-invocation-p called-code-body-invocation)
      (validate-environment-for-code-body-invocation-tree
	called-code-body-invocation)))
  nil)



;;; The function `validate-all-procedure-invocations' checks that the
;;; environments of all procedure-invocations that have started executing are
;;; still valid.  Validating means removing deleted items from the environment
;;; and checking the class of any items in the environment.

;;; If the item has been deleted or if the item is now of the wrong class, then
;;; that environment location is cleared, but no error is signalled.  (This
;;; could cause a procedure error later, during execution, if the procedure
;;; references this location and expects there to be an item.)

;;; Note that it is necessary to check the class of item because the definition
;;; of the item (e.g, the class name or superior classes) may have changed.

(defun-void #-SymScale validate-all-procedure-invocations
	    #+SymScale validate-all-procedure-invocations-1 ()
  (loop with top-array = top-level-procedure-invocations-array
	for index from 0 below (managed-array-length top-array)
	for procedure-invocation? = (managed-svref top-array index)
	do
    (when procedure-invocation?
      (validate-environment-for-code-body-invocation-tree
	(base-code-body-invocation procedure-invocation?)))))

#+SymScale
(defmacro validate-all-procedure-invocations ()
  `(tx:with-lock-held (procedure-invocations-lock)
     (validate-all-procedure-invocations-1)))

;; Note that we were considering signaling an error if the class of the item is
;; not correct.  But, we then decided that it is better if the procedure can
;; continue running and to receive an error only if it references that invalid
;; item.  - cpm, 3/16/94




(defsetf code-body-invocation-local-name-value
    set-code-body-invocation-local-name-value)

(defun set-code-body-invocation-local-name-value
    (code-body-invocation local-name new-value)
  (loop with local-var-vector
	  = (invocation-local-var-vector code-body-invocation)
	with description = (environment-description
			     (code-body-of-invocation code-body-invocation))
	for description-index from 0
	    below (managed-array-length description) by 2
	for var-name = (managed-svref description description-index)
	do
    (when (eq local-name var-name)
      (let ((local-var-index (halff description-index)))
	(reclaim-if-evaluation-value (svref local-var-vector local-var-index))
	(setf (svref local-var-vector local-var-index) new-value)
	(return new-value)))))

;;; To handle the case where the value is a newly-created item, first validate
;;; all of the items already in existence, then set the new item, and then
;;; update the serial number in the code body invocation.  We assume that the
;;; caller has validated this item as not being e.g. a deleted frame.  Cribbed
;;; from return-stack-values-to-caller.
(defun set-local-name-value-validating-environment (invocation variable value)
  (unless (procedure-environment-always-valid-p (procedure-of-invocation invocation))
    (validate-computation-instance-environment invocation nil nil))
  (setf (code-body-invocation-local-name-value
	  invocation variable)
	value)
  (update-code-body-invocation-frame-serial-number invocation)
  value)
;; Note: DBK says that it would be better not to use a guard frame serial
;; number, but rather to use item-references.




;;;; Starting Procedure Invocations




;;; The function `start-procedure-invocation-in-place' takes a procedure
;;; definition, a list of arguments, an optional priority, and an optional wait
;;; interval before the start of execution, which will be reclaimed.  It returns
;;; the new code-body-invocation if there is no error.  If there is an error,
;;; the error handling depends on the top-of-stack? argument.  See the
;;; documentation for `generate-procedure-and-code-body-invocation-in-place'.

(defun start-procedure-invocation-in-place
    (procedure priority? wait?
	       local-stack top-of-arguments-on-stack argument-count
	       simulator-procedure? completion-form? top-of-stack?
	       validated-args-p prepare-p)
  (let ((new-invocation?
	  (generate-procedure-and-code-body-invocation-in-place
	    procedure nil
	    local-stack top-of-arguments-on-stack argument-count
	    simulator-procedure? completion-form? top-of-stack?
	    validated-args-p prepare-p nil)))
    (when (procedure-invocation-p new-invocation?)
      (let ((actual-priority
	      (if priority?
		  (setf (code-body-invocation-priority new-invocation?)
			priority?)
		  (code-body-invocation-priority new-invocation?))))
	(cond 
	  (wait?
	   (schedule-delayed-computation-instance-execution
	     new-invocation? actual-priority procedure
	     (prog1 (evaluation-quantity-value-as-float wait?)
	       (reclaim-evaluation-quantity wait?))))
	  (t
	   (schedule-computation-instance-execution
	     new-invocation? actual-priority procedure)))))
    new-invocation?))


;;; The function `start-procedure-invocation-in-place-immediately' will start a
;;; procedure immediately without going through the scheduler.  This is
;;; necessary for error handlers where the error should be handled as near as
;;; possibile to the time that it takes place.  The procedure-invocation will be
;;; placed at the start of the immediate task queue.

(defun start-procedure-invocation-in-place-immediately
    (procedure 
      local-stack top-of-arguments-on-stack argument-count
      simulator-procedure? completion-form? top-of-stack?)
  (let* ((new-invocation?
	   (generate-procedure-and-code-body-invocation-in-place
	     procedure nil
	     local-stack top-of-arguments-on-stack argument-count
	     simulator-procedure? completion-form? top-of-stack?
	     nil nil nil)))
    (when (procedure-invocation-p new-invocation?)
      (filo-enqueue-immediate-code-body-invocation new-invocation?))
    new-invocation?))

;;; `with-three-thousand-variables-bound' moved here from COMMANDS0

(defmacro with-three-thousand-variables-bound (&body body)
  `(let* ((current-computation-flags (make-computation-flags
				       :final-evaluation-attempt? t
				       :role-serve-inactive-objects? t))
	  (current-computation-activity 0)
	  (current-computation-component-particulars nil)
	  (*current-computation-frame* nil)
	  (current-computation-instance nil)
	  (current-computation-style nil)
	  (current-environment 'simulator)
	  (current-profile-structure? nil)

	  (evaluating-simulator-procedure? nil)
	  (explanation-variables nil)
	  (stack-expiration 'never)
	  (*variables-that-did-not-have-values* nil)

	  ;; For tracing and breakpoints facility.
	  saved-warning-level saved-tracing-level saved-breakpoint-level
	  saved-source-stepping-level

	  (cached-top-of-stack -1)
	  (cached-stack-program-counter 0))
     ,@body))



;;; The function `start-deferred-procedure-invocation' takes a
;;; code-body-invocation and an eval-cons-list of a frame serial number.  This
;;; function validates the argument list with the frame serial number, and if it
;;; is valid, it enters this code body invocation into the queue of current
;;; procedures.  If the argument list is no longer valid, then the
;;; code-body-invocation is closed.  In all cases the first cons of the argument
;;; list must be reclaimed by this function.

(defun-void start-deferred-procedure-invocation-in-place
    (code-body-invocation)
  (schedule-computation-instance-execution
    code-body-invocation
    (code-body-invocation-priority code-body-invocation)
    (procedure-of-invocation
      (procedure-invocation-of-code-body code-body-invocation))))




;;; The function `local-base-of-procedure-invocation-stack' takes a procedure
;;; and returns the stack base procedure invocation for the given invocation,
;;; within the local machine.  Note that there may be further procedure
;;; invocations within the true stack for this procedure invocation, but they
;;; exist on remote machines which have called this one through an RPC.

(defun-simple local-base-of-procedure-invocation-stack (procedure-invocation)
  (loop for callee = procedure-invocation then caller?
	for caller? = (calling-procedure-invocation callee)
	until (null caller?)
	finally (return callee)))




;;; The function `true-base-of-procedure-invocation-stack-p' takes a procedure
;;; invocation and returns whether or not it is the base of the stack, even if
;;; the stack proceeds across machine boundaries.  In other words, even if the
;;; given procedure invocation is the base of the stack within this machine, if
;;; an RPC has called it, this predicate returns NIL.

(defun-simple true-base-of-procedure-invocation-stack-p (procedure-invocation)
  (not (calling-code-body-invocation procedure-invocation)))




;;; The function `update-code-body-invocation-frame-serial-number' takes a
;;; code-body-invocation and updates the stored frame serial numbers for it and
;;; for the code body invocations whose enviroments it can access.  That set is
;;; exactly the code body callers of this invocation down to and including the
;;; base code body invocation for this procedure invocation.

(defun update-code-body-invocation-frame-serial-number
       (first-code-body-invocation)
  (loop for invocation-to-reset = first-code-body-invocation
				then (code-body-caller invocation-to-reset)
	do
    (frame-serial-number-setf (code-body-invocation-frame-serial-number invocation-to-reset)
			      (current-frame-serial-number))
	until (base-code-body-invocation-p invocation-to-reset))
  nil)




;;; The macro `update-code-body-invocation-frame-serial-number-ignoring-callers'
;;; is used to update a single code body invocations frame serial number, ala
;;; the function above, but without iterating up through the other code body
;;; invocations within the larger procedure.  This is needed when receiving
;;; items from RPC returns.

(defmacro update-code-body-invocation-frame-serial-number-ignoring-callers
    (code-body-invocation)
  `(frame-serial-number-setf (code-body-invocation-frame-serial-number ,code-body-invocation)
			     (current-frame-serial-number)))




;;; The function `abort-procedure-invocation' takes a procedure invocation and
;;; aborts its execution.  This means it first aborts any procedures which it
;;; has called, and then it aborts itself.  Aborting oneself means closing all
;;; code body invocations for this procedure.  When the last is closed, that
;;; will automatically close this procedure-invocation.

;;; Note that this function may also accept a procedure as the procedure
;;; invocation argument.  In that case, it will abort all invocations of the
;;; given procedure.

;;; This function must also send back errors to any remote-procedure-callers of
;;; an invocation being aborted.

;;; Note that this current implementation does not really address the issues of
;;; asynchronous aborting, and that it will have to be rewritten when we allow
;;; call abort.

(defun abort-procedure-invocation
       (procedure-invocation &optional suppress-error-signal-to-callers?)
  (cond
    ((procedure-invocation-p procedure-invocation)
     (cond ((or suppress-error-signal-to-callers?
		(true-base-of-procedure-invocation-stack-p procedure-invocation))
	    (close-code-body-invocation procedure-invocation))
	   (t
	    (signal-procedure-invocation-error
	      procedure-invocation 'error 1
	      (twith-output-to-text-string
		(twrite-string "Aborting ")
		(write-procedure-invocation-instance-from-slot
		  procedure-invocation nil)
		(twrite-string "."))
	      nil))))
    ((of-class-p procedure-invocation 'procedure)
     (let ((invocations (procedure-invocations procedure-invocation)))
       (when invocations
	 (loop for invocation? being each procedure-invocation of invocations do
	   (abort-procedure-invocation invocation? suppress-error-signal-to-callers?)))))
    ((of-class-p procedure-invocation 'procedure-invocation)
     (abort-procedure-invocation
       (procedure-invocation-structure-of-procedure-invocation
	 procedure-invocation)
       suppress-error-signal-to-callers?))))




;;; The function `abort-code-body-invocation' takes a code-body-invocation and
;;; aborts its execution.  It does so by first aborting any
;;; code-body-invocations which it has called, and then by closing itself.  Note
;;; that since the closing of the last code-body-invocation for a procedure
;;; closes the procedure, this automatically aborts all called procedure
;;; invocations of this code body invocation.  This will have to be rewritten
;;; when the ON ABORT facilities are implemented.

(defun-simple abort-code-body-invocation (invocation)
  (if (remote-procedure-call-p invocation)
      (abort-outgoing-remote-procedure-call invocation)
      (close-code-body-invocation invocation)))




;;; The function `clear-procedure-invocations' is called when the system is
;;; being reset.  It aborts or signals an error into every procedure-invocation
;;; that is not enabled for running while inactive.  This function can return
;;; only when no more running while running procedures still exist.

;;; When an error is signalled deep within a procedure invocation stack, we must
;;; restart the attempt to search that procedure-invocation tree from its root.
;;; The error may have aborted the entire tree or it may only have aborted a
;;; portion, leaving a running while running procedure-invocation remaining
;;; elsewhere in the tree.  We cannot move on to the next procedure-invocation
;;; tree until we have either aborted this one, or searched it entirely and
;;; found no running while running procedure invocations.  Since signalling an
;;; error into a procedure-invocation is always guaranteed to abort that one, we
;;; can prove that we are making progress through the tree and that this loop
;;; will eventually terminate.

(defun-void #-SymScale clear-procedure-invocations
	    #+SymScale clear-procedure-invocations-1 ()
  (loop with top-array = top-level-procedure-invocations-array
	for index from 0 below (managed-array-length top-array)
	do
    (loop for invocation? = (managed-svref top-array index)
	  while (and invocation?
		     (abort-running-while-running-procedure-invocations
		       invocation?)))))

#+SymScale
(defmacro clear-procedure-invocations ()
  `(tx:with-lock-held (procedure-invocations-lock)
     (clear-procedure-invocations-1)))

;;; The function `abort-running-while-running-procedure-invocations' takes a
;;; procedure-invocation and will make one pass at aborting it or any portion of
;;; it that is not enabled for running while inactive.  If any aborting happens,
;;; this function will return true (a.k.a I did it!), else if the given
;;; procedure-invocation is completely searched and proven to be all running
;;; while inactive enabled, then this function returns NIL (nothing to abort).

(defun-simple abort-running-while-running-procedure-invocations
    (procedure-invocation)
  (let ((invocation-to-abort
	  (find-running-while-running-procedure-invocation procedure-invocation)))
    (when invocation-to-abort
      (if (true-base-of-procedure-invocation-stack-p procedure-invocation)
	  (abort-procedure-invocation procedure-invocation)
	  (signal-error-to-running-while-running-invocation
	    procedure-invocation))
      t)))

(defun-simple find-running-while-running-procedure-invocation
    (invocation)
  (if (and (procedure-invocation-p invocation)
	   (not (runs-while-inactive-p (procedure-of-invocation invocation))))
      invocation
      (loop for sub-invocation in (called-code-bodies invocation)
	    for result = (find-running-while-running-procedure-invocation sub-invocation)
	    when result
	      return result
	    finally (return nil))))

(defun-void signal-error-to-running-while-running-invocation (invocation)
  (signal-procedure-invocation-error
    invocation
    'error
    1
    (tformat-text-string
      "Aborting procedure invocations while resetting G2.")
    nil))

;; Note that during the execution of this operation, we should be certain that
;; there are no new running while running procedures being started.  If this
;; operation is made resumable in a future methodized g2-reset, methodized
;; g2-abort, or "on exit" (i.e. unwind-protect for procedures) projects, then
;; things must be rewritten to enforce this restriction of no new running while
;; running procedures being started.  -jra 11/13/96







;;; The function `signal-procedure-invocation-error' is used to signal an error
;;; into an existing procedure invocation.  This is useful in situations where
;;; some situation external to the execution of the procedure invocation causes
;;; an error within it.

;;; Note that an error handling system will need to be defined for Release 2.1
;;; or thereabouts.  The error-name and error-arguments arguments to this
;;; function are in anticipation of that system, but are ignored now.  -jra
;;; 3/4/90

(defun signal-procedure-invocation-error
       (procedure-invocation error-name error-level
	error-text-string error-arguments)
  (declare (ignore error-name error-arguments))
  (signal-code-body-invocation-error
    procedure-invocation
    'error
    error-level
    error-text-string
    nil nil nil nil nil))

;;; The function `signal-code-body-invocation-error' is used to signal an error
;;; into an existing code-body-invocation.  The arguments are the
;;; code-body-invocation, the name of the error type, the level of the error,
;;; the error description string, the error argument list, the instruction which
;;; was being executed at the time of the error or NIL if the error is being
;;; signalled externally to the instruction executions, and finally any alist
;;; environment currently established.

;;; Note that an error handling system is planned for Release 2.1 which will
;;; need the error names and may make some use of argument lists for error
;;; types.  For now these arguments are ignored.  -jra 3/4/90

;; Here we are at release 3.0, about to do something trivail to handle errors.
;; -jra 8/30/91


(defun signal-code-body-invocation-error
    (code-body-invocation
      error error-level error-text byte-code-body? program-counter?
      stack? top-of-stack? suppress-debugging-info?
      &optional computation-frame? computation-component-particulars?)
  (let* ((error_text_local
	  (copy-wide-string (if (consp error-text) (first error-text) error-text)))
	 (code-body-invocation-error-handler?
	   (find-error-handler-for-code-body-invocation
	     error code-body-invocation))
	 (procedure-invocation
	   (procedure-invocation-of-code-body code-body-invocation))
	 (base-of-stack
	   (local-base-of-procedure-invocation-stack procedure-invocation))
	 (calling-code-body-invocation?
	   (calling-code-body-invocation base-of-stack))
	 (calling-remote-procedure-call?
	   (when (and (remote-procedure-call-p calling-code-body-invocation?)
		      (remote-procedure-identifier-of-call calling-code-body-invocation?))
	     calling-code-body-invocation?))
	 (calling-g2gl-call-invocation?
	   (when (g2gl-call-invocation-p-function calling-code-body-invocation?)
	     calling-code-body-invocation?))
	 (error-message
	   (if (and suppress-debugging-info?
		    code-body-invocation-error-handler?)
	       error-text
	       (prog1
		   (generate-standard-error-message
		     error error-text
		     (or computation-frame?
			 (procedure-of-invocation procedure-invocation))
		     (if computation-frame?
			 computation-component-particulars?
			 nil)
		     code-body-invocation byte-code-body?
		     (if (and byte-code-body?
			      (neq byte-code-body?
				   (invocation-byte-code-body code-body-invocation)))
			 (byte-code-body-constant-vector byte-code-body?)
			 (invocation-constant-vector code-body-invocation))
		     program-counter? stack? top-of-stack?
		     (invocation-local-var-vector code-body-invocation))
		 (reclaim-error-text error-text)))))
    (when (framep error)
      (setup-source-info-for-error-object error))
    (cond (code-body-invocation-error-handler?
	   (handle-error-in-code-body-invocation
	     code-body-invocation-error-handler? code-body-invocation
	     error error-message))
	  (t
	   (cond
	     ;; RPC error handler takes prority over default error handlers
	     (calling-remote-procedure-call?
	      (remote-procedure-call-being-aborted
		calling-remote-procedure-call? error-message error))
	     (calling-g2gl-call-invocation?
	      (handle-g2gl-call-invocation-error
		calling-g2gl-call-invocation? error-message error))
	     ;; Invoke default error handler if registered and active
	     ((and (registered-and-active-default-error-handler-p)
	           (pass-loop-check-for-user-defined-default-error-handler-p
		     code-body-invocation)
		   (invoke-user-defined-default-error-handler error error-message)))
	     (t   (write-warning-message error-level
		    (tformat "~NW" error-message)
		    (tformat "~%Aborting procedure stack from ")
		    (write-procedure-invocation-instance-from-slot
		      base-of-stack nil)
		    (tformat "."))			 
		  (reclaim-error-text error-message)
		  (if (and (framep error)
			   (transient-p error))
		      (delete-frame error))))
	   (abort-procedure-invocation base-of-stack t)))
    (reclaim-error-text error_text_local)))




;;; The function `propagate-error-to-code-body-invocation' is similar to
;;; signal-code-body-invocation-error, except that the error has already been
;;; written into its final form, and this is has been propagated here from some
;;; remote system.  This function should determine if the given code has its
;;; stack origin here in this machine, and if so should post the error message
;;; on the logbook and abort the stack.  If the given code body invocation has
;;; its stack origin in another machine, then the error should be propagated to
;;; that machine.

(defun propagate-error-to-code-body-invocation
    (code-body-invocation error error-level error-message)
  (signal-code-body-invocation-error
    code-body-invocation
    error error-level error-message nil
    nil nil nil nil))



;;; The function `find-error-handler-for-code-body-invocation' now searches
;;; the given code-body-invocation and any callers for an error-handler-spec
;;; which can handle the given error symbol or object.  Error-handler-specs
;;; can come in two forms:
;;; (i) A three element list, where the last element is an integer.  This
;;; corresponds to the two argument version of on-error where the arguments
;;; accepted are a symbol and a text;
;;; (ii) A three element list where the last element is a class specification.
;;; This corresponds to the one argument version of on-error where the argument
;;; accepted is an error object.
;;;
;;; This function reflects the following considerations to decide whether an
;;; error symbol or error object can be handled by an error-handler-spec:
;;; (i) An error object can always be handled by a symbol, text handler.
;;; (ii) A handler which accepts error objects can accept any error object
;;; which is a subclass of its class specification; 
;;; (ii) A symbol, text error can be converted to an error object of type
;;; given by the function `map-error-symbol-to-class-name'.

(defun find-error-handler-for-code-body-invocation
    (error-name-or-object code-body-invocation)
  (let ((class (if (framep error-name-or-object)
		   (class error-name-or-object)
		   (map-error-symbol-to-class-name
		     error-name-or-object))))
    (loop for caller? = code-body-invocation
		      then (code-body-caller caller?)
	  while (code-body-invocation-p caller?)
	  for code-body = (code-body-of-invocation caller?)
	  for code-body-error-handler-spec? =
	  (code-body-error-handler-spec? code-body)
	  do
      (when  (and code-body-error-handler-spec?
		  (if (consp (third code-body-error-handler-spec?)) 
		      (subclassp class (second
					 (third code-body-error-handler-spec?)))                        t)
		  (code-body-caller caller?)) 
	(return caller?)))))


;;; the function `handle-error-in-code-body-invocation' is used to dispatch to
;;; an error handling code body invocation.  The first argument is a code body
;;; invocation which was already discovered as the handler for an error which
;;; occurred in the code body invocation passed as the second argument.  The
;;; error name (a symbol) and a text string error message are given as the third
;;; and fourth arguments.

;;; This function should first begin the aborting of the code body invocations
;;; which are called from the handler.  The erroneous invocation is guaranteed
;;; to be within the set which will be aborted by this operation.  This abort
;;; has to be begun now so that none of the code body invocations below the
;;; handler will receive any more CPU cycles.  When we have an synchnronous
;;; abort, that should be used here.  For now, the asynchronous abort will
;;; have to do.

;;; The handler is then invoked by mimicing the action of the jump instruction
;;; to launch the handlers execution. 

(defun handle-error-in-code-body-invocation
    (protected-code-body-invocation erroneous-code-body-invocation
				   error-name-or-error-object error-message)
  (declare (ignore erroneous-code-body-invocation)) 
  (let* ((handling-code-body-invocation
	   (code-body-caller protected-code-body-invocation))
	 (called-code-bodies
	   (copy-list-using-proc-conses
	     (called-code-bodies handling-code-body-invocation)))
	 (handler-spec
	   (code-body-error-handler-spec?
	     (code-body-of-invocation protected-code-body-invocation)))
	 (new-style-error? (framep error-name-or-error-object))
	 (new-style-handler? (consp (third handler-spec)))
	 (old-style-handler? (not new-style-handler?))
	 )
    (multiple-value-bind (error-argument error-text-argument) 
	(map-between-error-styles error-name-or-error-object
				  error-message
				  new-style-error?
				  new-style-handler?)
      ;; Begin aborting called code bodies of the handler.
      (loop for called-code-body in called-code-bodies
	    do
	(abort-code-body-invocation called-code-body))
      (reclaim-proc-list called-code-bodies)
      ;; Modify the program counter, error name, and error text of the handler.
      (gensym-dstruct-bind ((handler-address
			     error-name-var-spot error-text-var-spot)
			   handler-spec)
	(setf (invocation-stack-program-counter handling-code-body-invocation)
	      (managed-svref (code-body-entry-points
			       (code-body-of-invocation handling-code-body-invocation))
			     handler-address))
	(cond ((symbolp error-argument)
	       (modify-code-body-environment-var-spot
		 handling-code-body-invocation error-name-var-spot
		 (make-evaluation-symbol error-argument)))
	      ;; In the case that an object is being added to the var-spot
	      ;; the frame serial number has to be updated
	      (t (modify-code-body-environment-var-spot
		  handling-code-body-invocation error-name-var-spot
		   error-argument)
		 (update-code-body-invocation-frame-serial-number
		   handling-code-body-invocation)))
	
	(cond (old-style-handler?
	       (modify-code-body-environment-var-spot
		 handling-code-body-invocation error-text-var-spot

		 ;; Unfortunately, we can only pass on the text string to the user.
		 (let ((text-string (error-text-string error-text-argument)))
		   (reclaim-error-text-but-not-string error-text-argument)
		   (make-evaluation-text-reclaiming-argument text-string)))
	       (when new-style-error?
		 (if (transient-p error-name-or-error-object)
		     (delete-frame error-name-or-error-object))))
	      (t (if new-style-error?
		     (reclaim-error-text error-message)
		     (reclaim-error-text-but-not-string error-message))))))

    ;; Schedule the handler for immediate execution.
    (wake-up-code-body-invocation-immediately handling-code-body-invocation)))

;;;; Computation Contexts




;;; A computation context is a set of bindings for several global variables
;;; which must be present before calling the stack evaluator.  The variables
;;; which need to be bound are those in the clear-computation-context-variables
;;; function below.  The other functions which currently need to be updated if
;;; anything is added to this list are: enter-computation-context-for-code-
;;; body-invocation, enter-or-reclaim-rule-instance-context, attempt-
;;; expression-cell-execution, enter-computation-context-for-variable-formula,
;;; and with-bindings-for-sim-eval-for-stack.

(def-bombout-clean-up-function 'clear-computation-context-variables)

(defun clear-computation-context-variables ()
  (setq current-computation-flags (make-computation-flags))
  (setq current-computation-activity 0)
  (setq current-computation-component-particulars nil)
  (setq *current-computation-frame* nil)
  (setq current-computation-instance nil)
  (setq current-computation-style nil)
  (setq current-environment nil)
  (setq evaluating-simulator-procedure? nil)
  (when explanation-variables
    (reclaim-explanation-variables))
  (setq stack-expiration 'never)
  (setq *variables-that-did-not-have-values* nil)
  nil)


;;; The function `enter-computation-context-for-invocation' takes an
;;; invocation(code body or rule instance), prepares the global variable
;;; contexts for an execution of the code body invocation, and returns the
;;; uninterrupted fixnum time execution limit for the given code body
;;; invocation.

(defun-simple enter-computation-context-for-invocation 
    (invocation dont-validate-environment?)
  (let* ((current-procedure-invocation
	   (procedure-invocation-of-code-body invocation))
	 (procedure?
	   (procedure-of-invocation current-procedure-invocation))
	 (default-time-limit?
	     (default-uninterrupted-procedure-execution-limit? timing-parameters))
	 (specific-time-limit?
	   (if procedure?
	       (uninterrupted-procedure-execution-limit? procedure?)))
	 (uninterrupted-procedure-time-error?
	   (if (eq specific-time-limit? 'default)
	       (if default-time-limit?
		   (fixnum-time-interval (*f 1000 default-time-limit?))
		   nil)
	       (if specific-time-limit?
		   (fixnum-time-interval (*f 1000 specific-time-limit?))
		   nil))))

    (setq current-computation-flags
	  (make-computation-flags
	    :role-serve-inactive-objects? (may-refer-to-inactive-items-p procedure?)
	    :default-dont-compute-new-variable-values t
	    :dont-compute-new-variable-values t
	    ))
    (setq current-computation-activity 0)
    (setq current-computation-component-particulars nil)
    (setq current-computation-style nil)
    (when explanation-variables
      (reclaim-explanation-variables))
    (setq stack-expiration 'never)
    (setq *variables-that-did-not-have-values* nil)
    
    (setq *current-computation-frame* procedure?)
    (setq current-computation-instance invocation)
    (setq evaluating-simulator-procedure?
	  (simulation-procedure-invocation? current-procedure-invocation))
    (setq current-environment (if evaluating-simulator-procedure?
				  'simulated-value
				  'procedure))

    (when profiling-enabled?
      (posit-profiling-structure procedure?))
    (unless dont-validate-environment?
      (validate-computation-instance-environment invocation nil nil))
    (enter-tracing-and-breakpoint-context
      *current-computation-frame*
      (enter-procedure-invocation-trace-message
	current-procedure-invocation invocation))
    uninterrupted-procedure-time-error?))




;;; The function `exit-computation-context-for-code-body-invocation' takes a
;;; code body invocation which is entering a wait state and the program counter
;;; that should be returned to when it wakes up.  This function prepares the
;;; invocation for sleep by storing the program counter and updated the stored
;;; frame serial number for any code body invocations whose enviroment may have
;;; been modified by the execution of the code body invocation being exited.
;;; Note that the global variables storing computation contexts are not
;;; modified, you must either enter a new context after calling this function,
;;; or call the function to clear the context.

(defun exit-computation-context-for-code-body-invocation
       (code-body-invocation program-counter suppress-exit-context?)
  (setf (invocation-stack-program-counter code-body-invocation) program-counter)
  (unless suppress-exit-context?
    (exit-tracing-and-breakpoint-context
      *current-computation-frame*
      (code-body-invocation-exit-breakpoint-context-message
	*current-computation-frame*)))
  (unless (rule-instance-p code-body-invocation) ;modified by SoftServe
    (update-code-body-invocation-frame-serial-number code-body-invocation))
)




;;; The system variable `check-for-circular-formula-paths?' is part of the
;;; computation context for formulas.  It reflects whether a circularity test
;;; should be done after a formula has failed to compute a value.

(def-system-variable check-for-circular-formula-paths? proc-utils nil)




;;; The function `enter-computation-context-for-variable-formula' is the
;;; inner context-switch for variable formulas.

;; Review this function for the case when the generic-formula is deleted or the
;; expression-cell is not computable, this was not finished.  -jra 5/13/92

(defun-simple enter-computation-context-for-variable-formula
    (formula-invocation)
  ;; Fetch values from the formula-invocation and variable needed by the
  ;; computation-context below.
  (let* ((variable (formula-invocation-variable formula-invocation))
	 (generic-formula?
	   (formula-invocation-generic-formula? formula-invocation))
	 (frame-serial-number
	   (formula-invocation-frame-serial-number? formula-invocation))
	 (expression-cell-parent
	   (if (and generic-formula?
		    (frame-has-not-been-reprocessed-p
		      generic-formula? frame-serial-number))
	       generic-formula?
	       variable))
	 (g2-cell-array (cell-array expression-cell-parent))
	 (expression-cell
	   (when g2-cell-array
	     (managed-svref (g2-cell-array-managed-array g2-cell-array) 0)))
	 (byte-code-body
	   (when expression-cell
	     (g2-expression-cell-byte-code-body expression-cell)))
	 (computation-style?
	   (when expression-cell
	     (g2-expression-cell-computation-style expression-cell)))
	 (backward-chaining-allowed?
	   (when computation-style?
	     (computation-style-may-request-data-seeking computation-style?)))
	 (network-access-attempt?
	   (when computation-style?
	     (computation-style-network-access-attempt computation-style?)))
	 (local-var-vector
	   (when byte-code-body
	     (allocate-environment-vector
	       
	       (var-count (byte-code-body-environment-description byte-code-body))))))

    ;; Check that the formula hasn't been deleted since the scheduling of this
    ;; formula invocation.
    (when (and generic-formula?
	       (frame-has-been-reprocessed-p
		 generic-formula?
		 frame-serial-number))
      (cancel-formula-for-backward-chaining variable)
      (return-from enter-computation-context-for-variable-formula nil))

    ;; Check that there is a good compilation in the expression-cell.
    (when (or (null expression-cell)
	      (not (expression-cell-able-to-compute-p expression-cell)))
      ;; Reclaim, but don't enter this formula.
      (cancel-formula-for-backward-chaining variable)
      (return-from enter-computation-context-for-variable-formula nil))

    ;; When the setting of minor variables in the inner context switch occurs,
    ;; it needs to fetch the byte-code-body and local-var-vector from the
    ;; formula-invocation.  Cache them in a slot of the invocation.
    (setf (invocation-byte-code-body formula-invocation)
	  byte-code-body)
    (setf (invocation-constant-vector formula-invocation)
	  (byte-code-body-constant-vector byte-code-body))
    ;; Set the slots of the environment vector when need to hold the parent
    ;; item of a variable in the generic formula case!!!
    (when (eq expression-cell-parent generic-formula?)
      (setf (svref local-var-vector 1) (parent-frame variable)))
    (setf (invocation-local-var-vector formula-invocation) local-var-vector)
    (setf (invocation-stack-program-counter formula-invocation) 0)

    (setq current-computation-flags
	  (make-computation-flags
	    :cache-explanation-variables? (and (cache-data-for-explanation-p variable)
					       (explanation-related-features-enabled-func?))
	    :role-serve-inactive-objects? (may-refer-to-inactive-items-p expression-cell-parent)
	    :attempting-network-read-access-p (eq network-access-attempt? 'read)
	    :attempting-network-write-access-p (eq network-access-attempt? 'write)
	    :default-dont-compute-new-variable-values (not backward-chaining-allowed?)
	    :dont-compute-new-variable-values (not backward-chaining-allowed?)
	    ))
    (setq current-computation-activity 0)
    (setq current-computation-component-particulars
	  (slot-value-list 'cell-array-element
			   (g2-expression-cell-index expression-cell)))
    (setf (formula-invocation-component-particulars formula-invocation)
	  current-computation-component-particulars)
    (setq *current-computation-frame* expression-cell-parent)
    (setq current-computation-instance formula-invocation)
    (setq current-computation-style computation-style?)
    (setq current-environment
	  (if (eq 'simulator
		  (computation-style-value-domain current-computation-style))
	      'simulated-value
	      'inference-engine))
    (setq evaluating-simulator-procedure? nil)
    (setq stack-expiration 'never)
    (setq *variables-that-did-not-have-values* nil)
    (when explanation-variables
      (reclaim-explanation-variables))
    
    ;; Variables specific to formula contexts.
    (setq check-for-circular-formula-paths?
	  (if (things-this-variable-is-interested-in variable) t nil))
    
    (enter-tracing-and-breakpoint-context
      expression-cell-parent
      (if generic-formula?
	  (tformat-text-string "Executing ~NF for ~NF."
			       generic-formula? variable)
	  (tformat-text-string "Executing formula for ~NF." variable)))
    
    ;; Open up wake up collection for the formula that is about to be executed.
    (open-wake-up-collection-function nil)
    nil))




;;; The function `exit-computation-context-for-variable-formula' is used
;;; to exit the context for variable formulas.

(defun exit-computation-context-for-variable-formula (formula-invocation)
  (let* ((generic-formula?
	   (formula-invocation-generic-formula? formula-invocation))
	 (variable (formula-invocation-variable formula-invocation))
	 (component-particulars
	   (formula-invocation-component-particulars formula-invocation)))
    (exit-tracing-and-breakpoint-context
      (or generic-formula? variable)
      (if generic-formula?
	  (tformat-text-string
	    "Returning from execution of ~NF for ~NF."
	    generic-formula? variable)
	  (tformat-text-string
	    "Returning from execution of the formula of ~NF."
	    variable)))
    (reclaim-slot-value-list-given-tail
      component-particulars (cdr-of-cons component-particulars))
    (reclaim-environment-vector
      (invocation-local-var-vector formula-invocation))

    (clear-computation-context-variables)
    (setf (formula-invocation? variable) nil)
    (reclaim-formula-invocation-macro formula-invocation)))




;;; The function `enter-or-reclaim-computation-instance-context' takes a
;;; comutation instance, modifies the global variables which contain the context
;;; for a computation, and returns the fixnum time limit for uninterrupted
;;; execution, if any.  If the computation instance was reclaimed instead of
;;; being entered, the current-computation-instance will be NIL on exit from
;;; this function.

;; Note that the procedure (local-variable) environment is always validated in
;; the following call.  This is necessary because the code-body-invocation is
;; either continuing execution or has been scheduled for execution (i.e., a
;; "start" action) and needs validation.  - cpm, 7/21/95

(defun-simple enter-or-reclaim-computation-instance-context
    (computation-instance)
  (cond ((rule-instance-p computation-instance)
	 (enter-or-reclaim-rule-instance-context computation-instance nil))
	((code-body-invocation-p computation-instance)
	 (enter-computation-context-for-invocation
	   computation-instance nil))
	((formula-invocation-p computation-instance)
	 (enter-computation-context-for-variable-formula computation-instance))
	(t
	 #+development
	 (cerror "Contiune" "Entering bad computation-instance ~a." computation-instance)
	 nil)))

(defun enter-procedure-invocation-trace-message
       (current-procedure-invocation code-body-invocation)
  (twith-output-to-text-string
    (setq forgive-long-procedure-instruction? t)
    (cond ((and (=f (invocation-stack-program-counter code-body-invocation) 0)
		(base-code-body-invocation-p code-body-invocation))
	   (twrite-string "Entering execution of ")
	   (write-procedure-invocation-instance-from-slot
	     current-procedure-invocation nil)
	   (let ((code-body-caller
		   (code-body-caller code-body-invocation)))
	     (cond ((null code-body-caller)
		    (twrite-string " as a top level procedure invocation"))
		   ((code-body-invocation-p code-body-caller)
		    (twrite-string ", called from ")
		    (write-procedure-invocation-instance-from-slot
		      (procedure-invocation-of-code-body code-body-caller)
		      nil))
		   ;; Else, it must be an RPC.  Note that this logic
		   ;; mirrors that in the return-values instruction.
		   (t
		    (twrite-string
		      ", in service of a remote procedure call")))))
	  (t
	   (twrite-string "Resuming execution of ")
	   (write-procedure-invocation-instance-from-slot
	     current-procedure-invocation nil)))
    (twrite-character #.%\.)))







;;;; Procedure Methods




;;; `Method-Declaration' is one of two method subclasses of procedure.  It is a
;;; generic method that is used to dispatch to a specific method based on its
;;; arguments.  The procedure method is only used to locate the specific method
;;; and is not executed.  The specific method is executed.
;;;
;;; The procedure-definition slot need not be filled in to make the frame status
;;; OK, unlike its superior class, procedure, and its sibling class,
;;; method.  However, the name-or-names-for-frame must be
;;; filled in [CPM - please review!].  Accordingly, the `initialize method for
;;; method-declaration' makes the frame-status of the frame be OK or INCOMPLETE
;;; depending only on whether the name-or-names-for-frame slot is non-nil or
;;; nil, respectively.

(def-class (method-declaration procedure
			       (foundation-class method-declaration)
			       define-predicate)
  ;; NOTES (frame status) can be complete without a procedure definition.
  ;; (There is no procedure definition in this case.)
					; Should the NOTES be incomplete when
					; there is no name??  - cpm, 2/1/94
  ;; (Inherits nil as the default initial value now. (MHD 7/18/94))
  ;; (frame-status-and-notes nil)

  ;; This method is named through this slot, not through a procedure-definition.
  ;; (There is no procedure definition.)  Make this slot visible and editable.
  (name-or-names-for-frame nil system (type name-or-names) save)

  ;; The tracing slot is not needed.  (Only a specific method can be traced.)
  ;; Make the slot invisible to the user because it cannot be disinheritted.
  (tracing-and-breakpoints nil lookup-slot system save (type nil))
  (requires-call-next-method?  nil lookup-slot system save (type yes-or-no))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      90 90 
      ((outline (0 0) (90 0) (90 90) (0 90))
       (solid-rectangle (12 12) (48 24))
       (outline (12 48) (48 48) (48 60) (12 60))
       (solid-rectangle (42 30) (78 42))
       (outline (42 66) (78 66) (78 78) (42 78)))
      nil
      ;; later, maybe redo the icon in order to be able to eliminate
      ;;   the magnification; the goal is to have this be the same size
      ;;   as most other system icons (e.g. variables), 60 X 60, but
      ;;   we decided to do this after the icon was already designed
      ;;   for 90 X 90. (MHD 8/4/89)
      #.(convert-to-magnification-at-compile-time 2/3)
      #.(convert-to-magnification-at-compile-time 2/3)))

  ;; The following "procedure" inherited slots are not needed.  Make the slots
  ;; invisible to the user because it cannot be disinheritted.
  (class-of-procedure-invocation nil (type nil) vector-slot system save)
  (default-procedure-priority #.default-procedure-evaluation-priority
    (type nil) vector-slot system save)
  (uninterrupted-procedure-execution-limit?
    default (type nil) vector-slot system save)
  (argument-count nil vector-slot system save)
  (argument-list-description nil vector-slot system save)
  (returned-values-description nil vector-slot system save)
  (procedure-invocations
    nil vector-slot system do-not-save)
  (procedure-definition
    nil (type nil) vector-slot system save
    do-not-identify-in-attribute-tables select-changes)
  (procedure-code-bodies-3.0-beta nil vector-slot system save do-not-clone)
  (procedure-flags 0 vector-slot system save))

;; There are some slots in the above class that are inherited from procedure,
;; but are not needed.  Because they cannot be disinherited, I've changed the
;; type to NIL, so that they are not visible to the user.  I would like to also
;; make them non-savable, but this is not yet possible.  In development,
;; report-slot-saving-problem checks for incompatibilities betwen slot
;; descriptions of classes and superiors.  It doesn't like that a superior class
;; saves the slot and the inferior does not.  This should be reviewed.  - cpm,
;; 2/3/94

(def-substitute-for-old-class procedure-method method-declaration
  kb-flag-when-specific-procedure-method-died)

(def-class-method initialize (method-declaration)
  (funcall-superior-method method-declaration)
  (update-frame-status
    method-declaration
    (if (name-or-names-for-frame method-declaration)
	'nil				; ok
	'incomplete)
    nil))




(def-class-method note-name-change (method-declaration old-names initializing-p)
  (update-frame-status
    method-declaration
    (if (name-or-names-for-frame method-declaration) ; any new names?
	'nil
	'incomplete)
    nil)
  (funcall-superior-method method-declaration old-names initializing-p))

;; Note: update the status before the following code triggers consistency-
;; analysis.  - cpm, 10/5/95



;;; `Method' is one of two subclasses of procedure.  It is the specific method
;;; that is dispatched to from the generic method call.  The dispatch is based
;;; on the arguments to the generic method.  The specific method can also be
;;; executed directly like a non-method procedure, without requiring the method
;;; dispatch.  (This requires use of the "class::method" expression to reference
;;; the specific method because the specific method is not named.)

(def-class (method procedure
		   (foundation-class method)
		   ; alias for procedure-method-name
		   define-predicate
		   (class-export-comment "Attributes exported currently:
<ul>
<li>class of procedure invocation,
<li>default procedure priority,
<li>uninterrupted procedure execution limit,
<li>text,
<li>qualified name (instead of names)<br></ul>"))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      90 90 
      ((outline (0 0) (90 0) (90 90) (0 90))
       (solid-rectangle (12 12) (48 24))
       (solid-rectangle (12 48) (48 60))
       (solid-rectangle (42 30) (78 42))
       (solid-rectangle (42 66) (78 78)))
      nil
      ;; later, maybe redo the icon in order to be able to eliminate
      ;;   the magnification; the goal is to have this be the same size
      ;;   as most other system icons (e.g. variables), 60 X 60, but
      ;;   we decided to do this after the icon was already designed
      ;;   for 90 X 90. (MHD 8/4/89)
					;Review MHD's comment with him!!  - cpm,
					;2/1/94
      #.(convert-to-magnification-at-compile-time 2/3)
      #.(convert-to-magnification-at-compile-time 2/3)))

  (procedure-method-name
    nil vector-slot system save not-user-editable (type procedure-method-name)
    namelike-slot ; new: replaces obsolete declare-namelike-slot declaration (MHD 5/14/00)
    (attribute-export-comment "export, writable = false, type string"))
  (procedure-method-class
    nil vector-slot system save
    namelike-slot ; new: replaces obsolete declare-namelike-slot declaration (MHD 5/14/00)
    (attribute-export-comment
      "export, writable = false, type class-name (symbol)"))
  (synchronized nil vector-slot system save user-overridable select-changes
		(type yes-or-no)))

(defun method-for-this-invocation (invocation)
  (let ((procedure
	  (when (procedure-invocation-p invocation)
	    (procedure-of-invocation invocation))))
    (when (and procedure (method-p procedure)) procedure)))

;;; The arguments are always first in the local var vector, and the
;;; instance of a method is always the first argument.
  
;;; If we allow other locks in the future, this will be a slot in the
;;; code-body-invocation instead.
(defun lock-for-this-method-invocation (invocation)
  (let ((locals (invocation-local-var-vector invocation)))
    (and locals (svref locals 0))))

(defun maybe-set-lock-for-invocation (invocation procedure)
  (cond ((and (method-p procedure) (synchronized procedure))
	 ;; if the procedure is a synchronized method, then the lock is set
	 ;; on the invocation, to the class object which this method is on.
	 (setf (reference-to-item-to-lock invocation)
	       (get-reference-to-item
		 (lock-for-this-method-invocation invocation))))
	(t
	 nil)))

;; FIXME: how to make this a real lock?
(defun release-lock (invocation)
  (let* ((lock-reference?
	   (reference-to-item-to-lock invocation))
	 (lock? (get-item-if-item-reference lock-reference?)))
    (when lock-reference?
      (reclaim-evaluation-item-reference lock-reference?)
      (setf (reference-to-item-to-lock invocation) nil))
    (when (and lock?
	       ;; Only release lock if it is held by this invocation
	       ;; not if it's held by a caller of this invocation.
	       (eq (invocation-locking-this-object lock?) invocation))
      (setf (invocation-locking-this-object lock?) nil)))
  (let ((invocations-list
	  (invocations-waiting-for-lock-held-by-this-invocation
	    invocation)))
    (loop for waiting-invocation in invocations-list do
      (setf (invocation-holding-lock-this-is-waiting-for waiting-invocation)
	    nil)
      (wake-up-code-body-invocation waiting-invocation))
    (reclaim-proc-list invocations-list)
    (setf (invocations-waiting-for-lock-held-by-this-invocation
	    invocation)
	  nil)))

;;; Given an invocation, if it wants to acquire a lock, and that lock
;;; is currently held, this procedure places the invocation on an
;;; appropriate queue and returns nil. If the invocation wants to acquire
;;; a lock, and the lock is not currently held, this acquires the lock.
;;; If no lock is required, this function does nothing.

;;; Returns nil if invocation has been queued, t if invocation has
;;; no associated lock (and is therefore ready to execute), and
;;; :lock-aquired if invocation has acquired a needed lock and is now
;;; ready to execute, and :lock-held-by-thread if the lock is already
;;; held by a method in the same thread, so that the method can
;;; immediately execute without obtaining the lock.

;;; make this a macro?

(defun queue-invocation-for-lock-if-necessary (invocation)
  (if (code-body-invocation-p invocation)
      (let ((lock? (get-item-if-item-reference
		     (reference-to-item-to-lock invocation))))
	(if lock?
	    (let ((locker? (invocation-locking-this-object lock?)))
	      (cond
		((null locker?)
		 (setf (invocation-locking-this-object lock?) invocation)
		 (unless (code-body-invocation-thread invocation)
		   (setf (code-body-invocation-thread invocation) invocation))
		 :lock-aquired)
		((eq (code-body-invocation-thread locker?)
		     (code-body-invocation-thread invocation))
		 :lock-held-by-thread)
		(t
		 (proc-push
		   invocation
		   (invocations-waiting-for-lock-held-by-this-invocation locker?))
		 (setf (invocation-holding-lock-this-is-waiting-for invocation)
		       locker?)
		 nil)))
	    t))
      t))


(def-substitute-for-old-class specific-procedure-method method
  kb-flag-when-specific-procedure-method-died)

(defun procedure-method-name-function (method)
  (procedure-method-name method))

(defun procedure-method-class-function (method)
  (procedure-method-class method))

(def-class-method initialize-after-reading (method)
  (funcall-superior-method method)
  (unless (remove-methodized-actions-p)
    (let ((name? (procedure-method-name method))
	  (class? (procedure-method-class method)))
      (when (and class? name?)
	(initialize-slot-value
	  method
	  'name-or-names-for-frame
	  (make-unique-slot-name-symbol class? name?))))))
	
      


;; The procedure-method-name is aliased to qualified-name because the writer for
;; this slot is used to write both the class and method name.

(define-slot-alias qualified-name procedure-method-name method)



;;; For method, procedure-method-name and
;;; procedure-method-class are declared to be namelike slots.  This is necessary
;;; because instances of this class are not named.  The method name and class
;;; are displayed in the table and notes instead of a name.

;;; Note that if both slots are being changed, then
;;; with-updates-to-representations-supressed should be used to wrap the calls
;;; to change-slot-value.  In this way, the class and name will be updated
;;; together in the display .
 
;; (declare-namelike-slot procedure-method-name)
;; (declare-namelike-slot procedure-method-class)
;;
;; -- Now done with a namelike-slot feature in the slot declaration. (MHD 5/14/00)


;;; The `cleanup method for method' cleans up method
;;; registration and consistency analysis.  It then does additional analysis
;;; based on the method name.

(def-class-method cleanup (method)
  (funcall-superior-method method)
  (let ((method-name? (procedure-method-name method))
        (method-class? (procedure-method-class method)))
    ;; Note that the method deregistration and retraction of analysis is done
    ;; before the additional analyze for consistency.  The analysis is done for
    ;; other methods that may have the same method name.  So, this method must
    ;; not be in the analysis.  (It has a free-reference to its own method
    ;; name.)
    (when (and method-name? method-class?)
      (unregister-method-declaration
	method-name? method method-class?))
;    (retract-consistency-analysis method)
    (when method-name?
      (analyze-compiled-items-for-consistency method-name?))))

;; Note that the method unregistration could have been done in a deactivation
;; method.  But, it seemed better to keep the method registered until it is
;; deleted.  Maybe, other features, such as INSPECT, will at some point need to
;; search over all methods, including deactivated ones.  - cpm, 2/5/94



;;; The slot-putters `procedure-method-name' and `procedure-method-class' are
;;; used to register the specific methods upon initialization.

;;; Note that registering is normally done in compile-procedure-definition when
;;; an edit is made to the method.  This ensures that both new method name and
;;; class are set before registration.

(def-slot-putter procedure-method-name
		 (method method-name initializing?)
  (let ((method-class? (procedure-method-class method)))
    (when initializing?
      (when (and method-name method-class?)
	(register-method-declaration
	  method-name method method-class?))))
  (setf (procedure-method-name method) method-name)
  method-name)

(def-slot-putter procedure-method-class
		 (method method-class initializing?)
  (when initializing?
    (let ((method-name? (procedure-method-name method)))
      (when (and method-class method-name?)
	(register-method-declaration
	  method-name? method method-class))))
  (setf (procedure-method-class method) method-class)
  method-class)



;;; The `slot-value-writer for procedure-method-name' writes the class-qualified
;;; method name, if possible, using the procedure-method-name and
;;; procedure-method-class slots of the specific method.

;;; Note that this writer is writing information for two slots, class and name.
;;; This is okay because both slots are updated when the method definition
;;; changes, with the method name being updated last.

(def-slot-value-writer procedure-method-name (value method)
  (let ((method-class? (procedure-method-class method)))
    (cond ((and value method-class?)
	   (tformat "~(~nq~)" value method-class?))
	  (t
	   (twrite-string "none")))))



;;; `Procedure-methods-of-class' is a kb-specific-property on class names.  The
;;; value consists of a gensym-list of procedure methods and method names.  This
;;; information is needed when searching for the specific method appropriate for
;;; the given class and arguments.

;;; The property is updated in the slot-putters for procedure-method-name and
;;; procedure-method-class and in compile-procedure-definition.

;;; The format of the property value is an association list:
;;;   ((method-name . methods) ...)

(def-kb-specific-property-name procedure-methods-of-class
    reclaim-gensym-tree-function)

(defun get-procedure-methods-of-class (class-name)
  (procedure-methods-of-class class-name))


;;; `Classes-of-procedure-method' is a kb-specific-property on method names.
;;; The value consists of a gensym-list of class names and a count of the
;;; methods defined for the named method and class.  This information is needed,
;;; for example, in the describe-frame method when searching for classes that
;;; define methods of the given name.

;;; The format of the property value is an association list:
;;;   ((class . integer) ...)

(def-kb-specific-property-name classes-of-procedure-method
    reclaim-gensym-tree-function)

;; To find the classes that define a named method, an alternative to the plist
;; would be to search at runtime all classes for the procedure-methods-of-class
;; property.  Besides this being less efficient, this approach would not find
;; methods defined for classes that do not yet have definitions.
;;
;; Also note that this method class information is kept on a property-list and
;; not kept on a procedure-definition frame because it should not be saved in
;; KB's.  The classes that define methods need to be updated as methods are
;; created or initialized (loaded or merged from KB's or modules).  - cpm,
;; 2/12/94



;;; The function `register-method-declaration' records the specific-method as
;;; being defined for the given class.  The frame is added to the association
;;; list if it is not already there.

;;; Also, if this is a new method for the class, the method count for the class
;;; is incremented.

(defun-simple register-method-declaration
    (specific-method-name specific-method-frame class)
  (let ((named-procedure-method-list?
	  (get-named-procedure-methods-for-class specific-method-name class)))
    (cond
      ((null named-procedure-method-list?)
       ;; Make a new alist entry for the named method.
       (let ((new-method-alist
	       (gensym-list
		 (gensym-list specific-method-name specific-method-frame)))
	     (procedure-methods? (procedure-methods-of-class class)))
	 (setf (procedure-methods-of-class class)
	       (if (null procedure-methods?)
		   new-method-alist
		   (nconc procedure-methods? new-method-alist)))
	 (increment-class-count-of-method specific-method-name class)))
      ((memq specific-method-frame named-procedure-method-list?)
       ;; Already in the list, do nothing.
       nil)
      (t
       ;; Add the method to the existing alist.
       (nconc
	 named-procedure-method-list? (gensym-list specific-method-frame))
       (increment-class-count-of-method specific-method-name class)))))



;;; The function `unregister-method-declaration' removes the registration of the
;;; given method frame and class.  Note that other methods with the same
;;; procedure method name may remain registered for the class.

;;; Also, the method count for this class is decremented.

(defun-simple unregister-method-declaration
    (specific-method-name specific-method-frame class)
  (let ((named-procedure-method-list?
	  (get-named-procedure-methods-for-class specific-method-name class))
	(procedure-methods? (procedure-methods-of-class class)))
    ;; The method is defined for the class, so deregister it.
    (when (and named-procedure-method-list?
	       (memq specific-method-frame named-procedure-method-list?))
      (setq named-procedure-method-list?
	    ;; This leaves at least one element, the method name.
	    (delete-gensym-element
	      specific-method-frame named-procedure-method-list?))
      (when (and named-procedure-method-list?
		 (null (cdr named-procedure-method-list?)))
	;; There are no remaining methods of the given name, so remove the alist
	;; entry.
	(cond
	  ((null (cdr procedure-methods?))
	   ;; This was the only named method for the class.
	   (reclaim-gensym-tree procedure-methods?)
	   (setf (procedure-methods-of-class class) nil))
	  (t
	   (setf (procedure-methods-of-class class)
		 (delete-gensym-element
		   named-procedure-method-list?
		   (procedure-methods-of-class class)))
	   (reclaim-gensym-list named-procedure-method-list?))))
      (decrement-class-count-of-method specific-method-name class))))



;;; The functions `increment-class-count-of-method' and
;;; `decrement-class-count-of-method' are used to record the fact that a class
;;; is defining the given method.  A count is kept of the number of times that
;;; the class defines the method.  This information is kept on a property of the
;;; method name.

;;; These functions should be called as appropriate, when a method frame is
;;; either being newly registered for a class (INCREMENT), or when the method is
;;; being deregistered (DECREMENT).  Note that the increment function should
;;; only be called if the method frame is being newly registered.

(defun-void increment-class-count-of-method (specific-method-name class)
  (let* ((class-count-list? (classes-of-procedure-method specific-method-name))
	 (class-count-cons?
	   (and class-count-list? (assq class class-count-list?))))
    (cond (class-count-cons?
	   (setf (cdr class-count-cons?)
		 (+f (cdr class-count-cons?) 1)))
	  ((null class-count-list?)
	   ;; No classes are on this list.
	   (setf (classes-of-procedure-method specific-method-name)
		 (gensym-list (gensym-cons class 1))))
	  (t
	   ;; This class is not yet in the list, so add it.
	   (nconc class-count-list?
		  (gensym-list (gensym-cons class 1))))))
  nil)

(defun-void decrement-class-count-of-method (specific-method-name class)
  (let* ((class-count-list? (classes-of-procedure-method specific-method-name))
	 (class-count-cons?
	   (and class-count-list? (assq class class-count-list?)))
	 (class-count? (and class-count-cons? (cdr class-count-cons?))))
    (when class-count-cons?
      (cond ((<=f class-count? 1)
	     (setf (classes-of-procedure-method specific-method-name)
		   (delete-gensym-element class-count-cons? class-count-list?))
	     (reclaim-gensym-cons class-count-cons?))
	    (t
	     (setf (cdr class-count-cons?)
		   (-f class-count? 1))))))
  nil)



;;; The function `get-named-procedure-methods-for-class' returns the list of
;;; specific procedure method frames that are defined for the given class.  Note
;;; that this list is maintained elsewhere and should not be reclaimed by the
;;; caller.  This function returns only the methods that are defined at the
;;; given class.  It does not return inherited methods from its superior
;;; classes.

;;; Note that the return list, if any, is of the form:
;;;   (method-name . <methods>)

(defun-simple get-named-procedure-methods-for-class (specific-method-name class)
  (let ((procedure-methods? (procedure-methods-of-class class)))
    (and procedure-methods?
	 (assq specific-method-name procedure-methods?))))



;;; The function `verify-method-dispatch' checks that the
;;; given specific method can be called for the given argument list.  It is
;;; called when trying to determine which of a class's methods should be
;;; dispatched to.  It assumes that the specific method is defined for a class
;;; in the inheritance hierarchy of the first argument, which must be an item.

;;; The method is correct if argument count of the method is equal to the number
;;; of arguments.  Note that this test is needed because there can be more than
;;; one method defined for the same class with different number of arguments.
;;; If the argument-count arg is NIL, this test is not done.

;;; Note that it does not test the type of any arguments.  As with non-method
;;; procedures, this is done at runtime.

(defun-simple verify-method-dispatch
    (specific-method argument-count? test-if-method-not-bad?
		     test-if-method-serve-item-p)
  (and (or (null argument-count?)
           (eq (argument-count specific-method) argument-count?))
       (or (null test-if-method-not-bad?) (frame-not-bad-p specific-method))
       (or (null test-if-method-serve-item-p) (serve-item-p specific-method))))



;;; The function `method-dispatch-error' is similar to the
;;; function verify-method-dispatch, in that it checks the
;;; method dispatch.  But, it returns an error string if the specific method
;;; dispatch is incorrect, or returns NIL if it is correct.

(defun-simple method-dispatch-error
    (specific-method argument-count? test-if-method-not-bad?
		     test-if-method-serve-item-p)
  (cond ((and argument-count?
	      (not (eq (argument-count specific-method) argument-count?)))
	 #w"The method has an incorrect number of arguments.")
	((and test-if-method-not-bad? (not (frame-not-bad-p specific-method)))
	 #w"The method is not okay.")
	((and test-if-method-serve-item-p (not (serve-item-p specific-method)))
	 #w"The method is not active or enabled.")
	(t nil)))



;;; The function duplicate-specific-methods-p checks if there are more than one
;;; method defined for the given class and number of arguments.  If so, this
;;; means that there is not a unique method dispatch.

(defun-simple duplicate-specific-methods-p
    (method-name method-class argument-count)
  (loop for specific-method
	in (cdr (get-named-procedure-methods-for-class
		    method-name method-class))
	with method-count fixnum = 0
	do
     (when (=f (argument-count specific-method) argument-count)
       (incff method-count))
	finally
     (return (>f method-count 1))))



;;; The function `get-specific-methods-for-class-or-superior-class' searches for
;;; one or more methods defined for the given class or a superior class.  Note
;;; that if the class is not yet defined, this function still searches for
;;; methods, but only those defined with the given class as the first argument.

;;; Note that this function returns either NIL or a list of 1 or more methods.
;;; The list should not be reclaimed by the caller!

;;; This function is used to find the set of methods that apply to the the given
;;; method name and class, not considering number of arguments to the method.
;;; (For a true method dispatch, see the remaining functions in this section.)

;;; Note that this function stops searching the class inheritance patch when it
;;; finds methods for the class or a superior.  It does *not* collect the
;;; methods for all superiors.

(defun-simple get-specific-methods-for-class-or-superior-class
    (method-declaration-name class)
  (let ((class-description? (class-description class))
	(method-name-and-method-list? nil)
	(method-list? nil))
    (cond
      (class-description?
       ;; Iterate over all inherited classes, most specific first.
       (loop for inherited-class in (class-inheritance-path class-description?)
	     do
	 (setq method-name-and-method-list?
	       (get-named-procedure-methods-for-class
		 method-declaration-name inherited-class))
	 (when method-name-and-method-list?
	   (setq method-list? (cdr-of-cons method-name-and-method-list?)))
	     until method-list?))
      (t
       (setq method-name-and-method-list?
	     (get-named-procedure-methods-for-class
	       method-declaration-name class))
       (when method-name-and-method-list?
	 (setq method-list?
	       (cdr-of-cons method-name-and-method-list?)))))
    method-list?))



;;; The function `get-specific-method-for-arg-list-given-name', similar to
;;; get-specific-method-for-stack-given-name, attempts to dispatch to a specific
;;; method based on the given arguments.  If a unique method is not found, a
;;; non-reclaimable error string is returned.

(defun-simple get-specific-method-for-arg-list-given-name
    (method-name argument-list icp-socket)
  (let* ((first-arg? (and argument-list (car-of-cons argument-list)))
	 (first-arg-from-handle
	   (if (evaluation-integer-p first-arg?)
	       (get-item-from-local-handle first-arg? icp-socket)
	       first-arg?))
	 (first-arg-class-description?
	   (and (of-class-p first-arg-from-handle 'item)
		(class-description-slot first-arg-from-handle)))
	 (argument-count (length argument-list))
	 (method-or-error
	   (if first-arg-class-description?
	       (get-specific-method
		 method-name first-arg-class-description? argument-count nil t t)
	       #w"The first argument to the procedure method is not an item.")))
    (cond ((text-string-p method-or-error)
	   (copy-text-string method-or-error))
	  (t
	   (when (evaluation-integer-p first-arg?)
	     (setf (car argument-list) first-arg-from-handle))
	   method-or-error))))


;;; The function `get-specific-method-for-stack-given-name' attempts to dispatch
;;; to a specific method based on the given stack arguments.  If a unique method
;;; is not found, a non-reclaimable error string is returned.

(defun-simple get-specific-method-for-stack-given-name
    (method-name stack first-argument-index argument-count)
  (let* ((first-arg? (svref stack first-argument-index))
	 (first-arg-class-description?
	   (and first-arg?
		(of-class-p first-arg? 'item)
		(class-description-slot first-arg?))))
    (if first-arg-class-description?
	(get-specific-method
	  method-name first-arg-class-description? argument-count nil t t)
	#w"The first argument to the procedure method is not an item.")))



;;; The function `get-specific-method-for-stack', similar to
;;; get-specific-method-for-stack-given-name, dispatches to a method based on
;;; it's arguments, but it is given a method-declaration argument.

;;; A non-reclaimable error string is returned if the method is not found.

(defun-simple get-specific-method-for-stack
    (method-declaration stack first-argument-index argument-count)
  (let* ((method-declaration-name-or-names?
	   (name-or-names-for-frame method-declaration))
	 (method-declaration-name?
	   (and method-declaration-name-or-names?
		(if (consp method-declaration-name-or-names?)
		    (car-of-cons method-declaration-name-or-names?)
		    method-declaration-name-or-names?))))
    (cond
      ((null method-declaration-name?)
       #w"The method-declaration is not named.")
      (t
       (get-specific-method-for-stack-given-name
	 method-declaration-name? stack first-argument-index argument-count)))))



;;; The function `get-next-specific-method-given-name', similar to
;;; get-specific-method-given-name, chooses the specific method for the given
;;; name, class, and argument list.  It differs in that it starts searching for
;;; the method in the superior classes of class.  It does not check class
;;; because it wants the next, more general, method above class.

;;; A non-reclaimable error string is returned if the next method is not found.

(defun-simple get-next-specific-method
    (method-name currently-executing-class argument-count
		 original-argument-class-description)
  (get-specific-method
    method-name original-argument-class-description argument-count
    currently-executing-class t t))




;;; The constant `action-methods-reference-class' controls the
;;; class upon which system implementations of all action methods are
;;; defined

(defconstant action-method-reference-class 'system-item)



;;; The function `get-specific-method' is used to dispatch to a specific method
;;; based on a given class description and argument pattern.  (Currently, this
;;; dispatch checks that the number of arguments of the method caller and the
;;; method are equal, but does not check the types.  The type checking is done,
;;; as usual, at runtime.)

;;; This function returns either one method or a non-reclaimable error string,
;;; if the method cannot be dispatched to.

;;; This function implements the abstraction for method dispatch and is used by
;;; several callers, for example get-specific-method-for-stack.  Any change to
;;; method dispatch should be made here.

;;; Note that if the argument-count? argument is NIL, there must be only one
;;; method of this name defined for the given class.  Otherwise, an error-string
;;; is returned.

;;; Note that if a specific method is defined for a class, but it is not of the
;;; correct argument pattern (i.e., number of arguments), then further superior
;;; classes are searched for the method.  This is not an error until all
;;; superior classes are searched and no correct method is found.

;;; The search-after-class? argument should be either NIL or a class name (a
;;; symbol).  If it is a class, then the method search begins after this value
;;; (i.e., search-after-class?) in the class-inheritance-path of the
;;; class-description argument.  (This argument is need when dispatching to the
;;; "next method".)  If this argument is NIL, the method search begins at the
;;; given class.

;;; Note that the test-if-method-not-bad? and test-if-method-serve-item-p?
;;; arguments should normally be non-NIL.  This is needed when dispatching to
;;; the method at runtime.  (This means that methods with a status of BAD will
;;; be ignored during the search for the method.  Incomplete methods are not
;;; ignored.)  In some non-runtime cases, such as consistency analysis, the
;;; test-if-method-serve-item-p? may be NIL.

;; (See also get-specific-methods-for-class-or-superior-class, which also
;; locates methods, but is not an actual method dispatcher.)

(defun-simple get-specific-method
    (method-declaration-name class-description argument-count?
			     search-after-class? test-if-method-not-bad?
			     test-if-method-serve-item-p?)
  ;; Iterate over all inherited classes, most specific first.
  (loop for inherited-class in (if search-after-class?
				   (cdr (memq search-after-class?
					      (class-inheritance-path
						class-description)))
				   (class-inheritance-path class-description))
	for method-list? =
	(get-named-procedure-methods-for-class
	  method-declaration-name inherited-class)
	for method-name? = (and method-list? (car-of-cons method-list?))
	with verified-specific-method? = nil
	with non-unique-method-error-p? = nil
	with specific-method-error-string? = nil
	with cached-dispatching-error-string? = nil
	do
    (when (eq method-name? method-declaration-name)
      (loop for specific-method in (cdr-of-cons method-list?)
	    for dispatch-error-string? =
	    (method-dispatch-error
	      specific-method argument-count? test-if-method-not-bad?
	      test-if-method-serve-item-p?)
	    do
	(cond
	  ((not dispatch-error-string?)
	   (cond (argument-count?
		  (setq verified-specific-method? specific-method)
		  (loop-finish))
		 ;; When argument-count is NIL, check that there is a unique
		 ;; method for this class.  So, keep searching.
		 (verified-specific-method?
		  ;; Found a second method of this name.
		  (setq non-unique-method-error-p? specific-method)
		  (loop-finish))
		 (t
		  (setq verified-specific-method? specific-method))))
	  ((not verified-specific-method?)
	   ;; Cache the dispatch error message in case the method is not
	   ;; found in any superiors.
	   (setq cached-dispatching-error-string? dispatch-error-string?)))))
    ;; Stop searching if either the correct method was found, if a second method
    ;; could be dispatched to (non-unique method error), or if the search has
    ;; reached the ITEM class.

    ;; Keep searching superior classes if no method has been found with the
    ;; correct argument pattern.
    ;; the new system actions are defined on the
    ;; `action-method-reference-class' so we need to search up that
    ;; far
	until (or verified-specific-method? non-unique-method-error-p?
		  (eq inherited-class 'system-item))
	finally
	  (setq specific-method-error-string?
		(cond
		  (non-unique-method-error-p?
		   #w"Method is defined more than once for the class.")
		  (verified-specific-method? nil) ; Okay, no error.
		  (cached-dispatching-error-string?
		   cached-dispatching-error-string?)
		  (t
		   #w"The method is not defined.")))
	  (return
	    (or specific-method-error-string?
		verified-specific-method?))))



;;; The function `check-for-matching-methods' checks if two specific procedure
;;; methods, p1 and p2, "match".  P1 and P2 must be instances of the class
;;; method.
;;;
;;; To match, they must be have the same name, be for the same class, and have
;;; the same count.  Note that if two specific procedure methods match, it is
;;; undefined which one will be active and in-use; therefore, this situation is
;;; undesireable.
;;;
;;; In the matching case, this returns three values:
;;;
;;;    (1) procedure-name (2) procedure-class (3) argument-count
;;;
;;; In the non-matching case, this returns nil.

(defun check-for-matching-methods
    (current-frame method-class-for-current-frame previous-frame)
  (if (and (eq (procedure-method-name current-frame)
	       (procedure-method-name previous-frame))
	   (eq method-class-for-current-frame
	       (procedure-method-class previous-frame))
	   (=f (argument-count current-frame) (argument-count previous-frame)))
      ;; don't have local variables, which slightly optimizes for the nonmatching
      ;; case, which should be more common
      (values
	(procedure-method-name current-frame)
	method-class-for-current-frame
	(argument-count current-frame))))

;; This is used only, at present, by the automerge facility, which uses it to
;; determine whether duplicate specific procedure methods shoudl be deleted.
;; (MHD 12/2/94)






;;;; Item Code Bodies


;;; The function `get-byte-code-body-if-any' returns the byte-code-body
;;; associated with the given item and computation-component-particulars, if
;;; any.

;;; Note that the component particulars argument is needed to choose the
;;; byte-code-body of a cell-array or of the initial-value of a generic-
;;; simulation-formula.  Also, note that the base byte-code-body of a procedure
;;; is returned, if present.

(defun get-byte-code-body-if-any (item computation-component-particulars?)
  (cond
    ((and (consp computation-component-particulars?)
	  (eq (car-of-cons computation-component-particulars?)
	      'cell-array-element))
     (g2-expression-cell-byte-code-body
       (managed-svref
	 (g2-cell-array-managed-array (cell-array item))
	 (second computation-component-particulars?))))
    ((and (consp computation-component-particulars?)
	  (eq (car-of-cons computation-component-particulars?)
	      'simulation-initial-value))
     (frame-class-case item
       (generic-simulation-formula
	 (generic-simulation-initial-value-byte-code-body item))
       (simulation-subtable
	 (simulation-subtable-initial-value-byte-code-body item))))
    (t
     (frame-class-case item
       (rule
	 (rule-byte-code-body item))
       (procedure
	 (let ((base-code-body?
		 (if (code-bodies item)
		     (car-of-cons (code-bodies item))
		     nil)))
	   (if base-code-body?
	       (code-body-byte-code-body base-code-body?)
	       nil)))
       (function-definition
	 (function-definition-byte-code-body item))
       (generic-simulation-formula
	 (generic-simulation-formula-byte-code-body item))
       (simulation-subtable
	 (simulation-subtable-byte-code-body item))
       (action-button
	 (let ((embedded-rule? (get-slot-value item 'embedded-rule?)))
	   (if embedded-rule?
	       (rule-byte-code-body embedded-rule?)
	       nil)))
       (user-menu-choice
	 (let ((embedded-rule?
		 (embedded-rule-in-user-menu-choice? item)))
	   (if embedded-rule?
	       (rule-byte-code-body embedded-rule?)
	       nil)))
       (t nil)))))

;;  The non-cell-array part of this code was borrowed from
;;  disassemble-item-if-appropriate in queries.  Use this abstraction
;;  in that function.  - cpm, 9/13/93


;;; The function `item-currently-contains-compiled-value' is used to test if the
;;; compiled-attribute of an item currently contains a compiled value.

(defun item-currently-contains-compiled-value (item)
  (not (null (or (get-byte-code-body-if-any item nil)
		 (let ((cell-array? (cell-array item)))
		   (and cell-array?
			(g2-cell-array-managed-array cell-array?)))))))

;; This function could be improved to check for the g2-expression-cell-byte-
;; code-body of any expression-cells in the g2-cell-array-managed-array.  This
;; is tricky because the byte-code-body location depends on the various
;; computation-component-particulars.  - cpm, 10/25/94






;;; Callback support

;; Moved here from controls.lisp -dkuznick, 6/8/04

;;; `check-procedure-arglist' is (now) an internal helper function.  It takes a
;;; procedure (frame) and an argument description which is either a list
;;; containing types (typically symbols or lists or symbols), or a vector of
;;; actual "things" which will be passed to a procedure invocation.  It returns
;;; multiple values: The first is either NIL if everything is ok, or a Lisp
;;; string (so don't try to reclaim it!) which is intended to be used as a
;;; format directive to tformat (though it's intended to be passed to something
;;; like stack-error), and either 3 or 4 values which will be uased as the
;;; arguments to the format directive {also to be passed along to something
;;; like stack-error}.
;;;
;;; If you want to use this, you should probably be calling
;;; check-procedure-arglist-and-maybe-notify below.
(defun check-procedure-arglist
    (procedure argument-types-or-arg-vector runtime-nil-ok)
  ;; screw case for method-declaration argument count
  (let ((arg-count (or (argument-count procedure) 0)))
    (if (=f arg-count (length argument-types-or-arg-vector))
	(let ((args (argument-list-description procedure))
	      (actual (vectorp argument-types-or-arg-vector)))
	  (loop for i below arg-count do
	    (let ((arg-type (var-type-from-index args i))
		  (x (elt argument-types-or-arg-vector i)))
	      (unless (if actual
			  (if (null x)
			      runtime-nil-ok
			      (type-specification-type-p x arg-type))
			  (type-specification-subtype-p x arg-type))
		(return
		  (values
		    (if actual
			"For procedure ~NF, arg ~S, = ~NA, expected to be of type ~NT"
			"For procedure ~NF, arg ~S expected to be of type ~NT, not ~NT")
		    procedure
		    (var-name-from-index args i)
		    x
		    (var-type-from-index args i)))))))
	(values
	  "Procedure ~NF expects to be called with ~S arguments, but is declared to take ~S"
	  procedure
	  (length argument-types-or-arg-vector)
	  arg-count))))


(defmacro check-procedure-arglist-and-maybe-notify-helper
    (procedure arg-description notification notification-extra-args
	       runtime-nil-ok)
  (let ((err-string? (gensym))
	(err-string-arg1 (gensym))
	(err-string-arg2 (gensym))
	(err-string-arg3 (gensym))
	(err-string-arg4 (gensym)))
    `(multiple-value-bind (,err-string? ,err-string-arg1 ,err-string-arg2
					,err-string-arg3 ,err-string-arg4)
	 (check-procedure-arglist ,procedure ,arg-description ,runtime-nil-ok)
       (when ,err-string?
	 (,notification ,@notification-extra-args ,err-string?
			,err-string-arg1 ,err-string-arg2
			,err-string-arg3 ,err-string-arg4))
       ,err-string?)))

;;; `check-procedure-arglist-and-maybe-notify' is a macro which is used to
;;; invoke CHECK-PROCEDURE-ARGUMENTS, takes a procedure and an arg-description
;;; to pass along to CHECK-PROCEDURE-ARGLIST, and if there is a problem, a
;;; supplied notification will be called (like stack-error or warning-message)
;;; with a descriptive message (generated by CHECK-PROCEDURE-ARGLIST).  If the
;;; notification to be used needs to pass extra arguments before the message
;;; (for example if you want to use warning-message, you need to be able to
;;; pass a level argument), the &rest argument will be spliced into the call
;;; between the call and the message.  It returns the first value from
;;; CHECK-PROCEDURE-ARGLIST (NIL if all is well, a Lisp string if there was a
;;; problem), so it's caller can take additional conditionalized action (but of
;;; course if your notification is stack-error, a problem will result in a
;;; throw).

(defmacro check-procedure-arglist-and-maybe-notify
    (procedure arg-description notification &rest notification-extra-args)
  `(check-procedure-arglist-and-maybe-notify-helper
     ,procedure ,arg-description ,notification ,notification-extra-args nil))

;;; `check-procedure-arglist-nil-ok-and-maybe-notify' is exactly like
;;; check-procedure-arglist-and-maybe-notify, except it tells
;;; check-procedure-arglist that a NIL argument seen at runtime is ok and
;;; should not trigger a type violation (the implementation of the
;;; publish/subscribe DELETE event relies on this).

(defmacro check-procedure-arglist-nil-ok-and-maybe-notify
    (procedure arg-description notification &rest notification-extra-args)
  `(check-procedure-arglist-and-maybe-notify-helper
     ,procedure ,arg-description ,notification ,notification-extra-args t))

;; Moved here from view-def.lisp (in rev 1.100 of view-def.lisp) -dkuznick,
;; 6/29/04

(defun-void start-local-representation-callback (representation argument-list)
  (let ((procedure (callback-representation-callback-procedure representation))
	(serial-number (callback-representation-callback-serial-number representation)))
    (cond
      ((symbolp procedure)
       (funcall procedure argument-list))
      ((frame-has-been-reprocessed-p procedure serial-number)
       (dwarn "start-local-representation-callback received a ~
               deleted procedure.  This is probably ok."))
      ((runnable-p-function procedure)
       (loop with arg-count = (length argument-list)
	     with arg-vector
	       = (allocate-managed-simple-vector arg-count)
	     for i from 0 below arg-count
	     for argument in argument-list
	     do
	 (setf (svref arg-vector i) argument)
	     finally
	       ;; First check the args are of the type the callback is
	       ;; expecting.  Note we don't check against
	       ;; subscription-callback-arg-types, because then a callback that
	       ;; a user wanted to use which specified a specific class instead
	       ;; of item would fail, and be confusing.  This way we just
	       ;; prevent aborts from runtime mismatches.
	       (let ((error? (check-procedure-arglist-nil-ok-and-maybe-notify
			       procedure
			       arg-vector
			       notify-user)))
		 (if error?
		     (loop for i below arg-count
			   ;; arg-vector reclaimed below
			   do (reclaim-if-evaluation-value
				;; reminder to doc aref -> svref here
				(svref arg-vector i)))
		     (start-procedure-invocation-in-place
		       procedure
		       nil		; priority?
		       nil		; wait?
		       arg-vector	; Local stack
		       (1-f arg-count)	; Top of arguments on stack
		       arg-count	; argument-count
		       nil		; simulator-procedure?
		       nil		; completion-form?
		       nil		; top-of-stack?
		       nil		; validated-args-p
		       nil)))		; prepare-p
	       (reclaim-managed-simple-vector arg-vector)
	       (reclaim-eval-list argument-list)))
      (t
       (dwarn "Procedure ~s passed to start-local-representation-callback ~
               is not runnable.  This is probably ok."
	      procedure)))))

;;;; Debug

#+development
(defun print-invocation-queue (queue)
  (terpri)
  (loop for task being each constant-queue-element of queue
        do
    (let* ((code-body-invocation task)
           (procedure-invocation (procedure-invocation-of-code-body
                                   code-body-invocation))
           (string (twith-output-to-text-string
                     (write-procedure-invocation-instance-from-slot
                       procedure-invocation nil))))
      (format t "  ~a~%" string)
      (reclaim-text-string string))))




;;;; Bogosity



(defun denote-component-of-block-1-for-procedure-invocation ()
  (cond
    ((and (boundp 'current-computation-instance)
	  (code-body-invocation-p current-computation-instance))
     (write-procedure-invocation-instance-from-slot
       (procedure-invocation-of-code-body current-computation-instance)
       nil))
    (t
     (twrite-string "an invocation")
     (denote-component-of-block-1 '*current-computation-frame* " of "))))

;; - To resolve forward reference problems. Ben 9/19/91



(defun get-frame-for-computation-instance (computation-instance)
  (cond ((null computation-instance) nil)
	((code-body-invocation-p computation-instance)
	 (let ((procedure-invocation
		 (procedure-invocation-of-code-body computation-instance)))
	   (when procedure-invocation
	     (procedure-of-invocation procedure-invocation))))
	((rule-instance-p computation-instance)
	 (ri-rule computation-instance))
	((formula-invocation-p computation-instance)
	 (formula-invocation-variable computation-instance))
	((inference-background-collection-p computation-instance)
	 (inference-background-collection-variable computation-instance))
	(t
	 computation-instance)))

(defun name-and-class-for-computation-instance (computation-instance)
  (let* ((frame? (get-frame-for-computation-instance computation-instance))
	 (class-description? (framep frame?))
	 (class? (when class-description?
		   (class-name-of-class-description class-description?)))
	 (name? (when (and class? (of-class-p frame? 'block))
		  (get-or-make-up-designation-for-block frame?))))
    (values name? class?)))




;;;; Re-entrant Stack Eval Hackery

(defmacro with-safe-stack-eval-reentrancy (&body body)
  `(let ((current-computation-flags (make-computation-flags))
	 (current-computation-activity 0)
	 (current-computation-component-particulars nil)
	 (*current-computation-frame* nil)
	 (current-computation-instance nil)
	 (current-computation-style nil)
	 (current-environment nil)
	 (evaluating-simulator-procedure? nil)
;	 (when nupec-explanation-variables
;	   (reclaim-eval-tree nupec-explanation-variables))
;        (setq nupec-explanation-variables nil)
	 (stack-expiration 'never)
	 (*variables-that-did-not-have-values* nil)
	 (cached-top-of-stack -1)
	 (cached-fixnum-start-time 0)
	 (cached-fixnum-time-limit? nil)	; CID-1178 added
	 (cached-fixnum-time? nil)		; CID-1178 added
	 (cached-stack-program-counter 0)
	 (cached-stack-frame-base 0)
	 (cached-byte-code-body nil)
;	 (detailed-tracing? nil)
;	 (major-tracing? nil)
	 (tracing-message-level 0)
	 (breakpoint-level 0)
	 (arithmetic-errors-are-stack-errors-p nil)
	 (procedure-start-time 0)		; CID-1178 added
	 (procedure-end-time 0)			; CID-1178 added
	 (procedure-current-time 0)		; CID-1178 added
	 (execution-time-stack nil)		; CID-1178 added
	 (forgive-long-procedure-instruction? nil) ; CID-1178 added
	 (global-stack (make-global-stack))
	 (free-global-stacks nil)		; CID-1233 added
	 (saved-local-var-vector nil)		; CID-1233 added
	 (last-source-line 0)			; CID-1233 added
	 (current-source-line 0))		; CID-1233 added
     ,@body
     ;; reclaim stuff and return nil
     (reclaim-managed-simple-vector global-stack)
     nil))




;;;; Procedure Kernel




;;; The module proc-kernel used to contain the code now in the module
;;; PROC-UTILS.  This is a more reasonable naming of the intent of the contents
;;; of these files.  This file is now almost entirely empty, and its contents
;;; should be moved to more reasonable places.

(defun write-procedure-time-warning (procedure-invocation elapsed-time)
  (write-warning-message* 1
    (write-procedure-invocation-instance-from-slot
      procedure-invocation nil)
    (tformat
      " has exceeded the warning limit for uninterrupted procedure execution!  ~
       This procedure has been executing for ~a seconds."
      (/e (coerce-fixnum-to-gensym-float elapsed-time)
	  (coerce-fixnum-to-gensym-float fixnum-time-units-per-second)))))

(defun signal-procedure-time-error (elapsed-time top-of-stack)
  (stack-error
    top-of-stack
    "Uninterrupted procedure execution time limit exceeded!  This procedure ~
     has executed for ~a seconds."
    (/e (coerce-fixnum-to-gensym-float elapsed-time)
	(coerce-fixnum-to-gensym-float fixnum-time-units-per-second))))

(defun code-body-invocation-exit-breakpoint-context-message (procedure)
  (when (procedure-p procedure)
    (tformat-text-string "Exiting execution of ~NF." procedure)))

;; The message above should be improved to allow printing the actual procedure
;; invocation being exitted.  The commented out portion had to be cut since the
;; variable procedure-invocation was being removed.  -jra 11/13/91


; #+development
;(defun print-history-of-variable (variable)
;  (let* ((history?
;          (variable-or-parameter-stored-histories? variable))
;         (ring? (first (cascaded-ring-buffers history?))))
;    (print-contents-of-history-buffer ring?)))

;; The above is obsolete.  See print-history-for-variable in HISTORIES.  - cpm,
;; 5/26/94


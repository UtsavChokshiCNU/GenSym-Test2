;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module G2-BPEL - BPEL (Business Process Execution Language) for G2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Lowell B. Hawkinson, Philippe Printz, Allan Scott,
;;; Doug Orleans




;;;; Forward References


(declare-forward-references
  (g2gl-standard-connection-class variable))





;;;; G2 BPEL Design Notes

;;; L. Hawkinson
;;; Apr. 27, 2005
;;; Plus patches from May 2, 2005 and May 10, 2005
;;; More patches through Nov. 18, 2005. -mhd


;;; See the latest version of the (MS Word) design document for design and
;;; specification, which is essential for understanding many parts of this
;;; source file, and which is now in the Paper Trail as:
;;; trail/0290-g2-bpel-design-notes.doc

;;; Previously, it was being sent around via email, primarily from lh to mhd,
;;; and was not online.  Later, when it further stabilizes, we may consider
;;; formatting it, or at least some parts of it, to be part of this file and/or
;;; possibly having other formats such as HTML, and/or breaking it up into
;;; multiple documents.





;;;; G2GL Compilation Versions and G2GL Activity Compilations



;;; A `g2gl-activity-compilation' is a kind of `g2gl-compilation-version'.
;;; Comments in the def-structure for for g2gl-compilation-version that follows
;;; point out the slots of a g2gl-activity-compilation.

(def-structure (g2gl-activity-compilation)
  (g2gl-body-element-position 0)
  (g2gl-body-element-index -1)                ; must get filled in w/non-neg. int.
  (g2gl-activity-class-code nil)
  (g2gl-activity-name nil)
  (g2gl-attribute-display-compilations nil)
  (activity-compilation-successors nil)
  (g2gl-expression-compilation nil)
  ;; the following slot is only used for a G2GL activity-with-body:
  (g2gl-body-compilation nil))

(def-structure (g2gl-compilation-version
                 (:include g2gl-activity-compilation))
  (source-g2gl-process nil)
  (current-execution-frames nil)
  (alist-of-g2gl-operation-names-for-instantiation nil)
  (compilation-version-number nil)
  (number-of-compilation-errors 0)
  (number-of-compilation-warnings 0)
  (next-variable-index-to-assign 0)
  (reassignable-temporary-variable-indices nil)
  (alist-of-g2gl-body-compilations nil)
  (compilations-of-outside-variables-used-in-compensation-handler nil)
  (flowchart-junctions-alist nil)
  ;; orbhained-strings contains string that should be destroyed in reclaimer
  (orphaned-strings nil))






;;;; G2GL Body Compilation Structures



(def-structure (g2gl-body-compilation)
  (g2gl-execution-display-title-position nil)
  (g2gl-variable-compilations nil)
  (g2gl-fault-handler-compilations nil)
  (g2gl-compensation-handler-compilations nil)
  (g2gl-event-handler-compilations nil)
  (g2gl-text-box-compilations nil)
  (flowchart-entry-activity-compilation nil)
  (out-connection-representation-stream nil)
  (next-body-element-index-to-assign 0)
  (number-of-body-compilation-errors-and-warnings 0)
  (execution-display-for-superimposed-tracings nil))


;;;; Structure is responing for correct saving and 
;;;; loading g2gl-activity-compilation
(def-structure (g2gl-activity-options
                  (:constructor make-g2gl-activity-options-1()))
  (activity-compilations-list nil :reclaimer reclaim-gensym-list)
  (activity-compilations-count 0))

(defun make-g2gl-activity-options (activity)
  (let* ((ret (make-g2gl-activity-options-1)))
    (gensym-push activity (activity-compilations-list ret))
    (incff (activity-compilations-count ret))
    ret))

;;;; G2GL Text Box Compilation Structures

(def-structure (g2gl-text-box-compilation)
  (g2gl-text-box-position 0)
  (class-of-g2gl-text-box 'borderless-free-text)
  (text-of-g2gl-text-box nil))                ; nil or a text


(def-structure (g2gl-attribute-display-compilation)
  (g2gl-attribute-display-position 0)
  (g2gl-attribute-display-table-header nil) ;nil or a text
  (g2gl-attribute-display-rows nil))        ;list of pairs of texts






;;;; G2GL Communication




;;; A `G2GL correlation' is a list consisting of a G2GL correlation variable
;;; name, possibly the symbol initiate-conversation, and (only for an invoke
;;; activity) one of the three "pattern specifier" symbols out, in, or out-in.
;;; (A G2GL correlation compilation is the same as a G2GL correlation except
;;; that it has a G2GL correlation variable compilation instead of the G2GL
;;; correlation variable name.)  When the symbol initiate-conversation is
;;; present in a correlation, a G2GL conversation (see below) should be
;;; initiated upon receipt or sending of a G2GL message m associated with the
;;; correlation in an activity, with the specified G2GL correlation variable
;;; "late-bound" to a value including the G2GL conversation key (see below)
;;; determined by m.  When the symbol initiate-conversation is not present, m
;;; must continue the G2GL conversation by including all the elements of the
;;; conversation key.  In the special case of an invoke activity that both sends
;;; a message and receives a response message, a pattern specifier must be
;;; present to indicate whether just the outbound, just the inbound, or both
;;; messages participate in the conversation and thus are subject to the
;;; correlation.

;;; A `G2GL conversation' is an arbitrarily extended two-way exchange of
;;; (operation-related) G2GL messages between linked partner processes.  Most
;;; G2GL messages exchanged between partner processes belong to one or more G2GL
;;; conversations that are "managed" by G2GL correlations and correlation
;;; variables.  In order for a G2GL message to be part of a conversation, it
;;; must include all the elements of the conversation key established for that
;;; conversation.  A G2GL conversation key is an alist of attribute name / value
;;; pairs that is used as the value of a G2GL correlation variable to identify
;;; the "subject" of a G2GL conversation.

(def-concept g2gl-correlation)
(def-concept g2gl-conversation)



;;; The structure type `g2gl-message-transmission' represents a transmission on
;;; a partner link.  The slots are:
;;;
;;;  message-transmission-operation-name, a G2GL operation name
;;;
;;;  message-transmission-source-or-fault-name, either the symbol invoke if mt
;;;  originated from an invoke activity compilation, the symbol reply if mt
;;;  originated from a non-fault-reporting reply activity compilation , or a
;;;  fault name (any symbol but invoke or reply) if mt originated from a
;;;  fault-reporting reply activity compilation
;;;
;;;  message-transmission-G2GL-message, a G2GL message m, or nil after m has
;;;  been extracted from mt so that m will not get deleted when mt is deleted

(def-structure (g2gl-message-transmission)
  (message-transmission-operation-name nil)
  (message-transmission-source-or-fault-name nil)
  (message-transmission-G2GL-message nil))





(def-structure (g2gl-service-port
                 (:reclaimer reclaim-g2gl-service-port-internal))
  (service-port-owner nil)
  (direct-connection-partner-link-variable-compilation nil)
  (partner-service-port nil)
  (received-message-transmissions-queue nil)
  (threads-located-at-receiving-activity-compilations nil)
  (continuations-waiting-for-reply nil))


;; See section ";;;; G2GL Communication (Cont.)" for a continuation of this
;; section.





;;;; G2GL Execution Faults


;;; The structure `g2gl-execution-fault' holds information for a G2GL execution
;;; fault: its name, data, and description text.  The fault data is a g2gl-value
;;; or or NIL, and can only be non-NIL for faults resulting from g2gl-throw or
;;; g2gl-invoke (where the partner replied with a fault).  The fault description
;;; is a text string used to describe the fault in breakpoint displays and G2
;;; stack errors.  Both of these slot values are owned by this structure.
;;;
;;; This fault structure is allocated by make-g2gl-[user|system]-fault, defined
;;; below.  It is never copied, but passed along (and sometimes saved in an
;;; execution-thread-state-parameter) as the fault propagates upward.  It is
;;; reclaimed by schedule-applicable-fault-handler-compilation (when caught by a
;;; fault handler), exit-g2gl-process-instance-with-fault (when the fault is
;;; unhandled at the top level and there is no invocation-thread),
;;; continue-scheduled-process-invocation (when the invocation-thread is a G2
;;; procedure or another G2GL process), and delete-g2gl-execution-thread (when a
;;; thread is deleted while on the schedule after returning from a procedure
;;; call, parked while doing implicit compensation, or parked in a breakpoint).

(def-structure (g2gl-execution-fault
                 (:constructor
                   make-g2gl-execution-fault
                   (g2gl-execution-fault-name
                     g2gl-execution-fault-data
                     g2gl-execution-fault-description)))
  (g2gl-execution-fault-name nil)
  (g2gl-execution-fault-activity-name nil)
  (g2gl-execution-fault-data nil :reclaimer remove-reference-to-g2gl-value)
  (g2gl-execution-fault-description nil :reclaimer reclaim-if-text-string))



(defun make-g2gl-user-fault (fault-name fault-data)
  (make-g2gl-execution-fault
    fault-name fault-data
    (when fault-data
      (twith-output-to-text-string
        (twrite-g2gl-value fault-data)))))

(defun signal-g2gl-user-fault (thread fault-name fault-data)
  (signal-g2gl-execution-fault
    thread (make-g2gl-user-fault fault-name fault-data)))



(defmacro make-g2gl-system-fault (fault-name &body desc-writers)
  `(make-g2gl-execution-fault
     ,fault-name
	 nil
     ,(when desc-writers
        `(twith-output-to-text-string
           ,@desc-writers))))

(defmacro make-g2gl-system-fault-with-activity-name (fault-name activity-name &body desc-writers)
  `(let ((execution-fault (make-g2gl-execution-fault
                            ,fault-name
							nil 
							,(when desc-writers
                              `(twith-output-to-text-string
                                ,@desc-writers)))))
    (setf (g2gl-execution-fault-activity-name execution-fault) ,activity-name)
	execution-fault))

(defmacro signal-g2gl-system-fault (thread fault-name &body desc-writers)
  `(signal-g2gl-execution-fault
     ,thread
     (make-g2gl-system-fault
       ,fault-name
       ,@desc-writers)))




;;;; G2GL Out-Connection Representations



;;; [From spec, p. 22:] An `out-connection representation' is a compilation (and
;;; highly compressed representation) of a connection between two activities in
;;; a G2GL activity flowchart that is used in the creation of execution
;;; displays.  Specifically, it is a series of non-negative integers, the first
;;; of which is the G2 input end position [plus 2^14 to indicate that the
;;; connection is straight and orthogonal and that no specification of the G2
;;; output end position is provided], the second of which [(if needed)] is the
;;; G2 output end position plus 2^14 to indicate that the connection is
;;; diagonal, and the rest of which (if the connection would require three or
;;; more deltas to specify the end-to-end path) are offset connection deltas for
;;; all but the two of those deltas that are nearest the output end.  A G2 input
;;; (or output) end position specifies a position on the perimeter of an icon as
;;; a non-negative integer that combines a 2-bit specification of the side with
;;; the position on that side as measured from either the left or top edge, as
;;; appropriate.  An offset connection delta is like a G2 connection delta but
;;; is offset by a constant, specifically 3x2^14 when this is in a vector of
;;; 16-bit integers or 3x2^26 otherwise.  A 16-bit unsigned integer vector can
;;; be used for an out-connection representation stream if every G2 connection
;;; delta represented in is between -2^14 and +2^14, which should almost always
;;; be the case, barring major re-engineering of the G2 representation of
;;; workspace distances.  (It can be assumed that every G2 input and output end
;;; position will be less that 2^14, again barring major re-engineering of the
;;; G2 representation of workspace distances.  Note that the G2 input and output
;;; end objects for an out-connection representation are always G2GL activities.
;;; [To save a stream element in the single-delta, i.e. straight-connection,
;;; case, offset the G2 input end position by 2^14 and omit the G2 output end
;;; position, deriving it from the input end position and the output end
;;; object.]

(def-concept out-connection-representation)





;;;; G2GL Execution Frames



(def-structure (g2gl-execution-frame
                 (:constructor make-g2gl-execution-frame-internal ()))
  (parent-compilation-version 0)
  (g2gl-variable-values-vector nil)
  (g2gl-execution-threads nil)
  (g2gl-process-instance-handle nil)
  (parked-process-invocation-thread nil)
  (process-instance-is-paused nil)
  (threads-ready-to-run-after-pause nil)
  (normal-completion-of-process-body-compilation nil))







;;;; G2GL Execution Threads



;;; A `G2GL execution thread' is a simple vector of slots that represents a
;;; thread of execution of a G2GL process instance.  Additional
;;; concurrently-executing threads are spawned upon execution of a G2GL
;;; flow-split or flow-signal compilation, upon execution of the body
;;; compilation of a G2GL activity-with-body compilation, upon execution of an
;;; event handler or compensation handler compilation, and sometimes upon
;;; execution of a fault handler compilation.  Multiple threads turn into a
;;; single continuing thread upon completion of execution of a flow-sync or
;;; flow-gate activity compilation, and any spawned thread will disappear after
;;; execution of an activity compilation that has no appropriate continuation
;;; successor.  Often but not always, suspensions and resumptions of the
;;; execution of a G2GL execution thread, whether at the G2GL body, activity, or
;;; expression level, are handled by the G2 scheduler, in much the same way that
;;; the suspensions and resumptions of a G2 procedure execution thread are
;;; handled.

;;; An execution thread is either active and running or inactive and `parked' in
;;; one (or more - see below) of the following places:
;;;  * the G2 schedule
;;;  * a flow-sync or flow-gate activity compilation - waiting for threads to
;;;    arrive from all predecessor activity compilations
;;;  * its own child threads that are currently working to execute the body
;;;    compilation of the activity compilation it, the parent, is now executing
;;;  * a compensation handler thread (or an ancestor of such) that was activated
;;;    non-locally from a thread that is executing a compensate activity
;;;    compilation and is waiting for compensation to finish
;;;  * a G2GL service port (see below) - waiting for receipt of a certain type
;;;    or types of G2GL message transmission (see below)
;;;  * a G2GL breakpoint button (see below) - waiting for it to be clicked on
;;;  * a G2GL procedure invocation structure (see below) - waiting for the
;;;    invoked procedure to finish executing
;;;  * the threads-ready-to-run-after-pause slot of its parent execution frame f
;;;    - waiting for the process-instance-is-paused of f to again become nil, at
;;;    which point all the threads parked here are scheduled to run, in list
;;;    order, as soon as possible
;;; An execution thread located at a pick activity compilation might be parked
;;; in one or more G2GL partner links as well as in the G2 schedule.  Whether
;;; running or parked, an execution thread is always included in the
;;; G2GL-execution-threads of its parent execution frame.  Also, it is always
;;; shown as an appropriately positioned thread token on each of its execution
;;; displays (each execution display depicting the body compilation it is
;;; working to execute), except very transiently while it is being created,
;;; moved, or deleted.

;;; A `sibling thread' of an execution thread thread is another (concurrent)
;;; thread with the same parent execution frame and parent thread as thread,
;;; where the `parent thread' of thread is either nil or the currently inactive
;;; and unscheduled execution thread that is waiting to finish executing the
;;; G2GL activity-with-body compilation one level up whose body compilation
;;; thread is being used to execute.  It is possible for an execution frame to
;;; have multiple concurrent executions of a particular body compilation b, and
;;; thus multiple sets of sibling threads for b, notably when b is for an event
;;; handler.

;;; An `abnormal thread' is an execution thread whose
;;; activity-compilation-to-execute (see below) is either: (a) a fault handler
;;; compilation; (b) a compensation handler compilation; or (c) a scope or event
;;; handler compilation whose body compilation has had a previous normally
;;; complete execution but is now being executed again (in the G2GL variable
;;; values environment as of the normal completion) solely because it encloses
;;; compensation handlers that are being executed (abnormally).  An
;;; abnormal thread whose activity-compilation-to-execute is a fault or
;;; compensation handler compilation gets scheduled for execution, whereas an
;;; abnormal thread for a scope activity compilation or a dispatched event
;;; handler compilation is only ever inactive and parked in its child threads or
;;; just re-activated and about to be deleted.  The
;;; activity-compilation-to-execute c of an abnormal thread, which is always a
;;; G2GL activity-with body compilation, is not permitted to have a normal
;;; completion of its body compilation.  Also, if c completes and has successors
;;; (which could only be the case if c is a scope activity compilation), those
;;; successors are ignored, since this abnormal execution of c did not arise
;;; from flowchart execution.  Note that an abnormal thread whose
;;; activity-compilation-to-execute is a fault or compensation handler
;;; compilation hc can have a non-nil normal-completions-of-nested-compilations
;;; (see below) and that the body compilation of hc can have fault handler
;;; compilations, to handle faults that might occur in the execution of hc, but
;;; not a compensation handler compilation (because there is no situation in
;;; which it could ever get executed).  [Consider using a special thread token
;;; icon for abnormal threads.]  The execution thread state (see below) of an
;;; abnormal thread is always the symbol abnormal.  A `normal thread' is a
;;; thread that is not abnormal.

;;; It is not possible for there to be concurrently executing combinations of
;;; normal and abnormal sibling threads, although abnormal threads might be
;;; created as siblings of normal threads (and scheduled for execution) just
;;; before the normal threads are killed.

;;; When execution of the flowchart of a body compilation b is complete, it will
;;; no longer have threads located at any of its activity compilations.  In this
;;; situation, any threads located at event-detecting event handler compilations
;;; in b will be immediately killed, through any threads located at "dispatched"
;;; event handler compilations will remain so that they can try to run to
;;; completion.

;;; A `thread token' is an iconic G2 object representing a thread on an
;;; execution display d.  It is located either at or on a connection approaching
;;; that G2GL activity on d whose compilation the thread is to execute or is
;;; currently executing.  The G2GL standard thread token has an eye-catching
;;; circular icon; other thread tokens should also have eye-catching,
;;; equal-height-and-width icons.  [A thread token might have an attribute
;;; display that shows, for an individual execution display, the execution
;;; thread state (with nil shown as the symbol running and with the symbol
;;; in-transit not shown at all) or, for a superimposed-tracings display, a
;;; label to identify the process instance (ideally based on a G2GL conversation
;;; key).  For the individual execution display case, all execution thread state
;;; changes must be reliably reflected in the thread token.]

;;; Execution threads are complex because they must support many dimensions of
;;; execution behavior: activity flowchart execution, concurrency of execution
;;; within a G2GL process instance, synchronization and merging of concurrently
;;; executing threads, execution of subordinate activity body compilations,
;;; scheduling, timeouts, suspension and resumption of execution, externally
;;; instigated pauses and resumptions of execution, states of execution of G2GL
;;; activity compilations, waiting for G2GL activity compilations to finish
;;; executing, parking in the G2 schedule while waiting to run, parking in a
;;; G2GL procedure invocation structure while waiting for the invoked procedure
;;; to finish executing, parking in a G2GL partner link while waiting for
;;; receipt of certain types of G2GL message transmissions, parking in a
;;; breakpoint button that is waiting to be clicked on, normal completions of
;;; executions of body compilations and invoke activity compilations, the
;;; execution when necessary of fault handler, compensation handler, and event
;;; handler compilations, abrupt terminations of execution, maintenance of
;;; execution displays, animations on execution displays using thread tokens,
;;; control of thread token properties, etc.

;;; A G2GL execution thread thread has the following slots:
;;;  * `parent-execution-frame', the G2GL execution frame that thread belongs to
;;;  * `parent-execution-thread', nil except when thread is used in the
;;;    execution of the body of a G2GL activity-with-body a one level up (this
;;;    could be a G2GL scope activity, a G2GL fault handler, a G2GL compensation
;;;    handler, or a G2GL event handler), in which case this parent thread is
;;;    the currently inactive and unscheduled thread that is waiting to finish
;;;    executing the compilation of a, with its activity-compilation-to-execute
;;;    slot thus set to a
;;;  * `activity-compilation-to-execute', the activity compilation thread is to
;;;    execute or is currently executing (though for a flow-sync or flow-gate
;;;    activity compilation, it may be a sibling thread of thread that actually
;;;    does the execution)
;;;  * `predecessor-activity-compilation', either nil or the activity
;;;    compilation that was executed by thread or a sibling of thread prior to
;;;    the arrival or creation of thread at the activity compilation it is to
;;;    execute or is currently executing (at present, this is used only in the
;;;    creation of execution displays, and then only rarely)
;;;  * `body-compilation-this-is-being-used-to-execute', the body compilation b
;;;    to which the activity-compilation-to-execute of thread belongs (this is
;;;    "redundant" in that, if the parent-execution-thread of thread is non-nil,
;;;    it is the G2GL-body-compilation of the activity-compilation-to-execute of
;;;    the parent-execution-thread of thread, or else it is the
;;;    G2GL-body-compilation of the parent-compilation-version of the
;;;    parent-execution-frame of thread)
;;;  * `execution-thread-state' (see below)
;;;  * `execution-thread-state-parameter' (see below)
;;;  * `location-of-execution-thread-in-G2-schedule', nil except when thread is
;;;    scheduled (or is just about to go onto or has just come off the
;;;    schedule), needed for abnormally terminating thread and/or for timeout
;;;  * `outside-variable-bindings-for-execution', normally nil but, when thread
;;;    is being used to execute a compensation handler compilation hc (at
;;;    however deep a level), either, if thread is now inactive, a list of
;;;    variable bindings to use when actively executing thread or, if thread is
;;;    now active, a list of variable bindings to restore when finished actively
;;;    executing thread, where the list structure is identical in the two cases
;;;    and also, except where thread is the root of the tree of threads that are
;;;    executing hc, identical to the list structure value of this same slot in
;;;    the parent thread
;;;  * `normal-completions-of-nested-compilations', a list of normal completions
;;;    of executions of G2GL activity-with-body body compilations or invoke
;;;    activity compilations that belong immediately to the
;;;    body-compilation-this-is-being-used-to-execute of thread, where each such
;;;    normal completion encompasses one or more compensation handler
;;;    compilations that might at least partially undo (reverse) actions taken
;;;    during the execution of what was normally completed, where all sibling
;;;    threads of thread must have identically the same value for this slot, and
;;;    where this slot is reclaimed and set to nil when the last thread of a set
;;;    of siblings is to be deleted, either in conjunction with the recording of
;;;    a normal deletion (which removes and puts elsewhere the appropriate piece
;;;    of the value of this slot) or in the absence of such a recording
;;;  * `thread-token-properties', an alist of pairs of thread token property
;;;    names (the symbols class, label, and color) and appropriate corresponding
;;;    values (a G2 class name, a symbol or string, and a G2 color name), set by
;;;    G2GL assign activities to override, for these properties, system default
;;;    values and values in the thread-token-properties-for-G2GL-process of the
;;;    parent G2GL process
;;;  * `G2GL-execution-displays', a list of one or two G2GL execution displays
;;;    depicting the execution or executions of the G2GL body compilation b that
;;;    thread is being used to execute, where: (a) the individual display, if
;;;    there is one, comes first; (b) the (shared) superimposed-tracings
;;;    display, if there is one, comes last; (c) the list is not shared
;;;    identically by the sibling execution threads for this execution of b; and
;;;    (d) corresponding execution display objects and connections on these
;;;    displays are at exactly the same coordinate locations
;;;  * `thread-tokens-for-execution-displays', a list of essentially identical
;;;    thread-specific iconic objects, one such iconic object of the same class
;;;    and content for each of the G2GL-execution-displays of thread, used for
;;;    showing the location of thread, per the activity-compilation-to-execute
;;;    of thread, in each display
;;; [Consider combining the G2GL-execution-displays and
;;; thread-tokens-for-execution-displays slots into a single alist slot.]


(def-structure (g2gl-execution-thread
                 (:constructor make-g2gl-execution-thread-internal ()))
  (parent-execution-frame nil)
  (parent-execution-thread nil)
  (activity-compilation-to-execute nil)
  (predecessor-activity-compilation nil)
  (body-compilation-this-is-being-used-to-execute nil)
  (timeout-for-execution-thread nil)
  (execution-thread-state nil)
  (execution-thread-state-parameter nil)
  (location-of-execution-thread-in-g2-schedule nil)
  (outside-variable-bindings-for-execution nil)
  (normal-completions-of-nested-compilations nil)
  (thread-token-properties nil)
  (g2gl-execution-displays nil)
  (thread-tokens-for-execution-displays nil)
  (g2gl-flow-scope-markers-in-this-thread nil :reclaimer reclaim-gensym-list))


;;; The `execution thread state' of thread, when located at or approaching a
;;; particular G2GL activity compilation c, can be any of the following symbols:
;;;
;;; nil - at any kind of activity compilation c, as the initial/normal state
;;;
;;;   thread may be: active (that is, executing c right now, but maybe about to
;;;   be scheduled due to a timeout or a delay at the end of tracing a
;;;   transition); scheduled (that is, parked in the G2 schedule or in the
;;;   threads-ready-to-run-after-pause slot of its parent execution frame); or
;;;   inactive (and parked at a flow-sync while waiting for threads to arrive
;;;   from all predecessor activity compilations or at a flow-gate not arrived
;;;   at from a flow-signal while waiting for threads to arrive from all
;;;   predecessor flow- signal activity compilations)
;;;
;;; in-partner-link - at a receive, invoke, pick, or message-event-handler
;;;                   activity compilation c
;;;
;;;   waiting for receipt of a G2GL message transmission with a particular G2GL
;;;   operation name (or, for a pick activity, one of several particular names)
;;;   as well as other appropriately matching information or possibly, for a
;;;   pick activity, until a specific time or the earliest of several specific
;;;   times
;;;
;;;   the execution-thread-state-parameter of thread must be either the directly
;;;   connected G2GL service port where thread is parked or, for a pick
;;;   activity, a list consisting of any number of such G2GL service ports where
;;;   thread is parked, but nils where the parking has yet to occur, and
;;;   specific times to wait until, possibly intermingled, with at least one
;;;   G2GL service port or nil
;;;
;;;   thread may be: inactive, unscheduled, and parked in one or more G2GL
;;;   service ports; inactive, scheduled, and also parked in one or more G2GL
;;;   service ports (after a G2GL message transmission of one of the types being
;;;   waited for becomes available in the service port or for any pick activity
;;;   that has specific times to wait until); or active and ready to try to
;;;   complete execution of c by again checking for receipt of a certain type or
;;;   types of G2GL message transmission and possibly by again checking the
;;;   clock (after coming off the schedule)
;;;
;;; positive - at a flow-gate activity compilation arrived at after execution of
;;;            a flow-signal activity compilation where the list status was
;;;            determined to be positive
;;;
;;;   the execution-thread-state-parameter of thread must be the appropriate
;;;   link name
;;;
;;;   thread, which was newly created upon execution of the flow-signal activity
;;;   compilation, is inactive, parked, and waiting for threads to arrive from
;;;   all predecessor activity compilations
;;;
;;; negative - at a flow-gate activity compilation arrived at after execution of
;;;            a flow-signal activity compilation where the list status was
;;;            determined to be negative
;;;
;;;   the execution-thread-state-parameter of thread must be the appropriate
;;;   link name
;;;
;;;   thread, which was newly created upon execution of the flow-signal activity
;;;   compilation, is inactive, parked, and waiting for threads to arrive from
;;;   all predecessor activity compilations
;;;
;;; waiting - at a wait or alarm-event-handler activity compilation
;;;
;;;   until a specific time
;;;
;;;   the execution-thread-state-parameter of thread must be the specific time
;;;   to wait until
;;;
;;;   thread may be: about to be scheduled, scheduled, or active (after coming
;;;   off the schedule) to again check the clock
;;;
;;; executing-body - at a G2GL activity-with-body compilation c
;;;
;;;   waiting for the body compilation b of c to finish executing
;;;
;;;   thread may be: inactive, unscheduled, and parked in every child thread of
;;;   thread that is currently working to execute b; or active just after
;;;   completion of the execution of b and therefore c
;;;
;;; in-procedure - at a call or invoke activity compilation c
;;;
;;;   waiting for an invoked G2 procedure or G2GL process to finish executing
;;;
;;;   the execution-thread-state-parameter of thread may be: a G2GL procedure
;;;   invocation structure (until the invoked procedure finishes executing); nil
;;;   (if the invoked procedure has completed successfully); or a
;;;   g2gl-execution-fault structure (if the invoked procedure has been abruptly
;;;   terminated due to an execution fault or due to some deliberate action that
;;;   is not a result of an abnormal deletion of thread)
;;;
;;;   thread, may be: inactive, unscheduled, and parked in a G2GL procedure
;;;   invocation structure; scheduled (just after the invoked procedure has
;;;   finished executing); or active and ready to proceed or signal a G2GL
;;;   execution fault, depending on the execution-thread-state-parameter of
;;;   thread (after coming off the schedule)
;;;
;;; abnormal - at a fault or compensation handler compilation c with body
;;;            compilation b or at a G2GL activity-with-body compilation c in
;;;            whose body compilation b a fault or compensation handler
;;;            compilation is being executed
;;;
;;;   waiting to start, finish, or clean up from regular or forced-termination
;;;   fault handling or explicit or implicit compensation handling in b, that
;;;   is, the undoing (reversal) of certain actions performed during an earlier
;;;   "normal" execution of c
;;;
;;;   when c is a fault handler compilation, the
;;;   execution-thread-state-parameter of thread must be either nil or, when
;;;   there is fault data and the execution of b has not yet started, a single
;;;   element list of the fault data
;;;
;;;   when c is a G2GL activity-with-body compilation or a local compensation
;;;   handler compilation, the execution-thread-state-parameter of thread must
;;;   be either: the thread that is parked at the compensate activity that
;;;   triggered the compensation, if any (which is to be resumed when thread is
;;;   deleted, and to which all unhandled faults in the compensation handler
;;;   should be propagated); a g2gl-execution-fault structure, if there was
;;;   no applicable fault handler (in which case the compensation is happening
;;;   as part of implicit fault handling and the fault should be re-thrown after
;;;   the last compensation); or the symbol implicit-compensation-handler, if
;;;   there was no compensation handler on the same body as c
;;;
;;;   when c is a non-local compensation handler compilation, the
;;;   execution-thread-state-parameter of thread must be nil
;;;
;;;   thread may be: scheduled and waiting to start executing b; active and
;;;   about to be parked to execute b; inactive, unscheduled, and parked in
;;;   every child thread of thread that is currently working to execute b; or
;;;   active just after completion of the execution of b, and therefore c, with
;;;   any successors of c to be ignored
;;;
;;; in-transit - approaching any kind of activity compilation
;;;
;;;   the execution-thread-state-parameter of thread must be a list consisting
;;;   of one or more (x, y) coordinate pairs for remaining tracing step
;;;   positions along the connection from a predecessor activity compilation pc
;;;   of c to c, followed, if pc is flow-signal activity compilation, by the
;;;   link status and the link name determined by the execution of pc
;;;
;;;   thread must have an individual execution display
;;;
;;;   thread may be: active and making a mini-step along the connection from pc
;;;   to c just before being scheduled or rescheduled, or else scheduled and
;;;   obligated to make at least one more mini-step
;;;
;;; at-breakpoint - at any kind of activity compilation c
;;;
;;;   waiting for a button to be clicked on
;;;
;;;   the execution-thread-state-parameter of thread must be a list consisting
;;;   of either the G2GL breakpoint button where thread is parked (see below) or
;;;   the symbol ready-to-proceed and, only for an execution fault breakpoint, a
;;;   g2gl-execution-fault structure
;;;
;;;   thread must have an individual execution display, except in the unusual
;;;   situation described below
;;;
;;;   thread may be: inactive, unscheduled, and parked in a G2GL breakpoint
;;;   button; active though already referred to in a G2GL breakpoint button
;;;   (just after an entry activity compilation breakpoint has been recognized);
;;;   scheduled and ready to proceed (after the G2GL breakpoint button is
;;;   clicked on); scheduled and ready to proceed without an individual
;;;   execution display (after the display has been abruptly deleted); or active
;;;   and about to proceed with or without an individual execution display
;;;   (after coming off the schedule)
;;;
;;; at-end - at any kind of activity compilation c that has no successors
;;;
;;;   waiting for the completion of non-event-handler sibling threads
;;;   (specifically, above a flow-discriminator or n-out-of-m-flow-join from
;;;   which this thread has "escaped")
;;;
;;;   A thread in this state does a "busy wait" until all non-event-handler
;;;   sibling threads have completed, i.e. it does the check and gets
;;;   immediately rescheduled.  When all non-event-handler sibling threads have
;;;   completed, the thread completes normally and its parent thread is
;;;   scheduled.  [TO DO: avoid this busy wait and make the other threads
;;;   responsible for doing the normal completion, i.e. "last one out turns off
;;;   the lights"]
;;;
;;; Of these states, nil may be regarded as "green" (proceeding as fast as
;;; possible), in-transit as "yellow" (moving along in mini-steps), and the
;;; others as "red" (blocked or possibly blocked from proceeding).  Note again,
;;; importantly, that an execution thread, whatever its state, is always
;;; represented, except very transiently, by a thread token on each execution
;;; display that exists for the G2GL body execution within which it is
;;; executing.



;;; A `normal completion' is a structure representing the residual data from
;;; executing a scope, invoke, or event handler activity compilation that
;;; completed "normally", i.e., without being prematurely terminated by a fault.
;;; This data is used by the activity's compensation handler when the activity's
;;; enclosing scope is prematurely terminated by a fault.  (This structure is
;;; roughly equivalent to what the BPEL spec refers to as an "installed
;;; compensation handler".)

(def-structure (normal-completion
                 (:constructor
                   make-normal-completion
                   (normally-completed-activity-compilation
                     outside-variable-bindings deeper-normal-completions)))
  ;; The activity compilation that completed, or nil if top-level.
  (normally-completed-activity-compilation nil)
  ;; A gensym alist of variable compilations and G2GL values.
  (outside-variable-bindings nil :reclaimer reclaim-outside-variable-bindings)
  ;; A gensym list of normal completions of nested compilations.
  (deeper-normal-completions nil :reclaimer reclaim-normal-completions))



;;;; G2GL Process Invocation Threads



;;; The structure `g2gl-process-invocation-thread' is used for invocation of a
;;; G2GL process as a procedure, i.e., doing a CALL.  This can be used either
;;; from a G2 procedure invocation, or from another G2GL process.

(def-structure (g2gl-process-invocation-thread)
  ;; process-invocation-context is a code-body-continuation if called from a
  ;; procedure or a g2gl-execution-thread if called from a process.
  (process-invocation-context nil)
  ;; process-invocation-frame is the frame that is executing the process
  (process-invocation-frame nil)
  ;; process-invocation-state is RETURN if the process ended with a g2gl-return
  ;; activity or DONE if it ended with a fault, a g2gl-exit activity, or the
  ;; final activity of the top-level process body.
  (process-invocation-state nil)
  ;; process-invocation-result is a list of values in the return case, a
  ;; g2gl-execution-fault structure in the fault case, or nil otherwise.
  (process-invocation-result nil)
  (location-of-process-invocation-thread-in-g2-schedule nil))





;;;; G2-BPEL Implementation: Icon Defining Utilities



(eval-when (:compile-toplevel :load-toplevel :execute)

(defun g2gl-label-icon-area (label)        ; -for-macro?
  (case label
    ((flow-gate flow-signal)
     (values 20 20))
    ((=)
     (values 20 20 'extra-large))
    ((flow-split
       flow-discriminator
       n-out-of-m-flow-join
       flow-terminator
       flow-sync pick-join switch-join pick
       event-handler alarm-event-handler message-event-handler)
     (values 200 25))
    ((fault-handler compensation-handler)
     (values 200 50))
    (t
     (values 100 50))))



(defun make-g2gl-activity-text-drawing-element ; -for-macro?
    (text-string width height font-size)
  (let* ((x (halfw width))
         (y (halfw height))
         (current-icon-variables-override-plist nil)
         (current-icon-variables-plist nil)
         (text-line-height
           (case font-size    ; hardwired, for now!
             (small 12)
             (large 15)
             (extra-large 20))))
    (multiple-value-bind (left top right bottom)
        (compute-edges-for-text-drawing-element
          `(text ,text-string (,x ,y) ,font-size))
      (decfw x (halfw (-w right left)))
      (decfw y (halfw (-w bottom top)))
      (incfw y text-line-height)
      `(text ,text-string (,x ,y) ,font-size))))



(defun generate-bpel-label-geometry        ; -for-macro?
    (string-or-symbol width height font-size)
  (make-g2gl-activity-text-drawing-element
    (if (symbolp string-or-symbol)
        (copy-text-string-with-case-conversion
          (symbol-name string-or-symbol)
          :first)
        (stringw string-or-symbol))
    width height font-size))


(defparameter g2gl-activity-labels        ; -for-macro?
  '(return
    breakpoint
    receive
    reply
    invoke
    assign
    call
    throw
    exit                                ; was: terminate
    wait
    empty
    do
                                        ; removed: sequence
    while
    scope
    compensate
    switch-fork
    pick

    pick-join
    switch-join
    flow-split
    flow-sync
    flow-discriminator
    n-out-of-m-flow-join
    flow-terminator

    fault-handler
    compensation-handler
    event-handler
    alarm-event-handler
    message-event-handler

    ;; listed "stacked" entry not handled; do by hand for now; maybe do later!
;   flow-signal                        ; flow- / signal
;   flow-gate                        ; flow- / gate

    =))                                ; for (local & arg) variables



;; The following text labels and positions were extracted by hand from the icons
;; designed by Philippe.  -dougo, 2/8/07

(defparameter g2gl-label-geometries '(
  (return (text #w"Return" (29 24) small))
  (breakpoint (text #w"Breakpoint" (16 24) small))
  (receive (text #w"Receive" (24 24) small))
  (reply (text #w"Reply" (33 24) small))
  (invoke (text #w"Invoke" (28 24) small))
  (assign (text #w"Assign" (27 24) small))
  (call (text #w"Call" (38 24) small))
  (throw (text #w"Throw" (31 24) small))
  (exit (text #w"Exit" (39 24) small))
  (wait (text #w"Wait" (35 24) small))
  (empty (text #w"Empty" (31 24) small))
  (do (text #w"Do" (41 24) small))
  (while (text #w"While" (32 24) small))
  (scope (text #w"Scope" (30 24) small))
  (compensate (text #w"Compensate" (10 24) small))
  (switch-fork (text #w"Switch Fork" (15 30) small))
  (pick (text #w"Pick" (87 18) small))
  (pick-join (text #w"Pick Join" (73 18) small))
  (switch-join (text #w"Switch Join" (66 18) small))
  (flow-split (text #w"Flow Split" (70 18) small))
  (flow-sync (text #w"Flow Sync" (68 18) small))
  (flow-discriminator (text #w"Flow Discriminator" (42 18) small))
  (n-out-of-m-flow-join (text #w"N-out-of-M Flow Join" (39 18) small))
  (flow-terminator (text #w"Flow Terminator" (51 18) small))
  (fault-handler (text #w"Fault Handler" (58 24) small))
  (compensation-handler (text #w"Compensation Handler" (28 24) small))
  (event-handler (text #w"Event Handler" (55 18) small))
  (alarm-event-handler (text #w"Alarm Event Handler" (34 18) small))
  (message-event-handler (text #w"Message Event Handler" (23 18) small))
  (= (text #w"=" (3 17) extra-large))
  ;; done by hand for now!
  (flow-signal
   (text #w"Flow" (6 17) small)
   (text #w"Signal" (1 30) small))
  (flow-gate
   (text #w"Flow" (6 17) small)
   (text #w"Gate" (6 34) small))
  ))



;;; `generate-bpel-label-geometries-code' is used in a development G2 to
;;; generate code (as text) to be pasted into the source module to define
;;; `G2gl-label-geometries'.  G2gl-label-geometries is mostly generated based on
;;; g2gl-activity-labels (further above) by generate-bpel-label-geometries-code.
;;; However, a couple of entries are done by hand (as indicated by comments
;;; below).

(defun generate-bpel-label-geometries-code () ; -for-macro?
  (let ((geometries
          (loop with width
                with height
                with font-size?
                for label in g2gl-activity-labels
                do (multiple-value-setq (width height font-size?)
                     (g2gl-label-icon-area label))
                collect `(,label
                            ,(generate-bpel-label-geometry
                               label width height
                               (or font-size? 'small))))))
    (format t "~%(defparameter-for-macro g2gl-label-geometries '(")
    (loop with *print-case* = ':downcase
          for x in geometries
          do (format t "~%  ~s" x))
    (format t "~%  ))")))


(defun g2gl-label-text (label)                ; -for-macro?
  `(text-region
     ,@(cdr (assq label g2gl-label-geometries))))



;;; The function `create-g2-bpel-activity-icon-description' is called at
;;; load-time to create an icon description for an activity class given its
;;; name.

(defun create-g2-bpel-activity-icon-description (activity-name)        ; -for-macro?
  (case activity-name
    ((flow-gate flow-signal)
     (create-g2-bpel-link-activity-icon-description activity-name))
    (t
     (create-default-g2-bpel-activity-icon-description activity-name))))


;;; The function `g2gl-activity-icon-symbol' returns a list of line drawing
;;; elements for the named activity's icon symbol, which generally appears below
;;; the text label.  The point coordinates are hard-coded, suitable for icon
;;; dimensions of 100x50 for normal activities and 200x50 for handler
;;; activities.  The function `g2gl-activity-icon-symbol-regions' returns a list
;;; of regions (for a polychrome header) for the named activity's icon symbol.
;;; Both of these are empty if the activity has no icon symbol.

;; TO DO: Ideally these should be their own standalone icon descriptions (with
;; their upper left corner at the origin) which could be composed (translated)
;; into the full activity icon description.  But that's more work than it's
;; worth at the moment.  -dougo, 2/8/07

(defconstant g2gl-activity-icon-symbols
  ;; icon symbols designed by Philippe:
  '((receive
     ;; envelope in circle
     (circle (40 39) (50 29) (60 39))
     (outline (45 35) (45 42) (55 42) (55 35))
     (lines (45 35) (50 39))
     (lines (50 39) (55 35)))
    (reply
     ;; envelope in double circle
     (circle (40 39) (50 29) (60 39))
     (circle (42 39) (50 31) (58 39))
     (outline (45 35) (45 42) (55 42) (55 35))
     (lines (45 35) (50 39))
     (lines (50 39) (55 35)))
    (invoke
     ;; envelope in thick circle
     (filled-circle (40 39) (50 29) (60 39))
     g2-icon-background
     (filled-circle (42 39) (50 31) (58 39))
     g2-icon-symbol
     (outline (45 35) (45 42) (55 42) (55 35))
     (lines (45 35) (50 39))
     (lines (50 39) (55 35)))
    (switch-fork
     ;; diamond around the label
     (outline (100 25) (50 50) (0 25) (50 0)))
    (while
      ;; closed circular arrow
      (circle (43 41) (50 34) (57 41))
      #.(create-filled-polygon-icon-description-element
          '((40 41) (49 40) (45 46))))
    (scope
     ;; square with plus sign
     (outline (43 33) (43 47) (57 47) (57 33))
     (text #w"+" (46 46) large))
    (fault-handler
     ;; lightning bolt
     #.(create-filled-polygon-icon-description-element
        '((91 49) (97 31) (102 38) (109 25) (102 46) (97 38))))
    (compensation-handler
     ;; rewind (two left-pointing filled triangles)
     #.(create-filled-polygon-icon-description-element
        '((100 32) (100 48) (90 40)))
     #.(create-filled-polygon-icon-description-element
        '((111 32) (111 48) (100 40))))
    (assign
     ;; equals sign
     (solid-rectangle (42 44) (58 46))
     (solid-rectangle (42 38) (58 40)))
    (throw
     ;; lightning bolt
     #.(create-filled-polygon-icon-description-element
         '((41 49) (47 31) (52 38) (59 25) (52 46) (47 38))))
    (wait
     ;; clock
     (circle (40 39) (50 29) (60 39))
     (lines (50 39) (50 31))
     (lines (50 39) (56 39)))
    (compensate
     ;; rewind
     #.(create-filled-polygon-icon-description-element
        '((50 32) (50 48) (40 40)))
     #.(create-filled-polygon-icon-description-element
        '((61 32) (61 48) (50 40))))
    (empty
     ;; square
     (outline (43 33) (43 47) (57 47) (57 33)))
    (do
      ;; generic item icon
      g2-icon-left-edge
      #.(create-filled-polygon-icon-description-element
          '((43 33) (50 40) (43 47)))
      g2-icon-top-edge
      #.(create-filled-polygon-icon-description-element
          '((50 40) (43 33) (57 33)))
      g2-icon-right-edge
      #.(create-filled-polygon-icon-description-element
          '((50 40) (57 33) (57 47)))
      g2-icon-bottom-edge
      #.(create-filled-polygon-icon-description-element
          '((43 47) (50 40) (57 47)))
      g2-icon-symbol
      (outline (43 33) (43 47) (57 47) (57 33))
      (lines (43 47) (57 33))
      (lines (43 33) (57 47)))
    (return
      ;; semicircular arrow
      #.(create-filled-polygon-icon-description-element
          '((49 37) (60 42) (51 46)))
      (lines (47 29) (arc (55 31)) (55 41)))
    (breakpoint
     ;; filled circle
     (filled-circle (43 41) (50 34) (57 41)))
    (exit
     ;; power symbol (circle with vertical line)
     (circle (43 41) (50 34) (57 41))
     (solid-rectangle (49 37) (50 44)))
    (call
     ;; square with horizontal lines (like a page of text?)
     (outline (43 34) (43 47) (57 47) (57 34))
     (lines (46 39) (54 39))
     (lines (46 43) (54 43)))
    ))

(defun g2gl-activity-icon-symbol (activity-name)
  (let ((icon-symbol (assq activity-name g2gl-activity-icon-symbols)))
    (when icon-symbol
      (cons 'g2-icon-symbol (cdr icon-symbol)))))

(defun g2gl-activity-icon-symbol-regions (activity-name)
  (cond ((eq activity-name 'do)
         '((g2-icon-symbol . black)
           (g2-icon-left-edge . extra-light-gray)
           (g2-icon-top-edge . light-gray)
           (g2-icon-right-edge . gray)
           (g2-icon-bottom-edge . gray)))
        ((g2gl-activity-icon-symbol activity-name)
         '((g2-icon-symbol . black)))))


;;; The parameters `g2gl-icon-rectangle-background' and
;;; `g2gl-icon-rectangle-outline' are drawing elements for the background and
;;; outline of a rectangular icon (with diagonally cut-off corners of size 5).
;;; The points in the drawing elements are relative to the width and height of
;;; the icon.

;; TO DO: rounded rectangles!

(defconstant g2gl-icon-rectangle-points
  '(;; lower left corner:
    (5 height) (0 (- height 5))
    ;; upper left corner:
    (0 5) (5 0)
    ;; upper right corner:
    ((- width 5) 0) (width 5)
    ;; lower right corner:
    (width (- height 5)) ((- width 5) height)))

(defconstant g2gl-icon-rectangle-background
  `(filled-polygon
     ,g2gl-icon-rectangle-points
     ;; triangles:
     ((5 height) (0 (- height 5)) (0 5))
     ((0 5) (5 0) ((- width 5) 0))
     (((- width 5) 0) (width 5) (width (- height 5)))
     ((width (- height 5)) ((- width 5) height) (5 height))
     ((5 height) (0 5) ((- width 5) 0))
     (((- width 5) 0) (width (- height 5)) (5 height))))

(defconstant g2gl-icon-rectangle-outline
  `(outline ,@g2gl-icon-rectangle-points))

(defconstant g2gl-icon-background-color 'rgb85a5ff) ;sort of a royal blue

(defun create-default-g2-bpel-activity-icon-description (activity-name)        ; -for-macro?
  (multiple-value-bind (width height) (g2gl-label-icon-area activity-name)
    (create-icon-description
      width height
      `((polychrome (g2-icon-outline . foreground)
                    (g2-icon-background . ,g2gl-icon-background-color)
                    (text-region . black)
                    ,@(g2gl-activity-icon-symbol-regions activity-name))
        g2-icon-background ,g2gl-icon-rectangle-background
        g2-icon-outline ,g2gl-icon-rectangle-outline
        ,@(g2gl-label-text activity-name)
        ,@(g2gl-activity-icon-symbol activity-name)))))


(defun create-g2-bpel-link-activity-icon-description (activity-name) ; -for-macro?
  (create-icon-description
    40 40
    `((polychrome (g2-icon-outline . foreground)
                  (g2-icon-background . ,g2gl-icon-background-color)
                  (text-region . black))
      g2-icon-background
      (filled-circle (0 20) (20 0) (40 20))
      g2-icon-outline
      (circle (0 20) (20 0) (40 20))
      ,@(g2gl-label-text activity-name))))


(defvar g2gl-standard-connection-line-pattern nil)
(defvar g2gl-standard-connection-arrows '((default triangle filled)))

(defun g2gl-standard-connection-stub (direction side position)
  `(nil g2gl-standard-connection ,direction ,side ,position nil
        ,g2gl-standard-connection-line-pattern
        ,g2gl-standard-connection-arrows))

(defvar g2gl-link-connection-line-pattern '(short-dash))
(defvar g2gl-link-connection-arrows '((default triangle)))

(defun g2gl-link-connection-stub (direction side position)
  `(nil g2gl-link-connection ,direction ,side ,position diagonal
        ,g2gl-link-connection-line-pattern
        ,g2gl-link-connection-arrows))


)  ; eval-when





;;;; G2GL Connection Utility Functions



;;; The function `g2gl-activity-has-no-standard-in-connections-p' returns true
;;; iff g2gl-activity has no standard G2GL input connections (i.e., of the class
;;; that is the value of g2gl-standard-connection-class).  If sides is nil, then
;;; connections on any side qualify.  If non-nil, sides may be a single side
;;; (i.e., left, top, right, or bottom) or else a list of sides, and a
;;; connection qualifies as a standard input connection only if it's on the
;;; specified side or sides.

(defun g2gl-activity-has-no-standard-in-connections-p
    (g2gl-activity &optional sides)
  (loop for c being each input-connection of g2gl-activity
        of-type g2gl-standard-connection-class
        never (or (null sides)
                  (let ((s (get-side-given-end-position
                             (output-end-position c))))
                    (if (atom sides) (eq s sides) (memq s sides))))))

(defun g2gl-activity-has-no-standard-out-connections-p (g2gl-activity)
  (loop for c being each output-connection of g2gl-activity
        of-type g2gl-standard-connection-class
        never t))


(defun list-g2-bpel-activity-output-connections (activity
                                                  &optional (side 'bottom))
  (loop for c being each output-connection of activity
        of-type g2gl-standard-connection-class
        on-side-or-sides side
        collect c using gensym-cons))

(defun list-g2-bpel-activity-input-connections (activity)
  (loop for c being each input-connection of activity
        of-type g2gl-standard-connection-class
        collect c using gensym-cons))


;;; Make a new standard G2GL connection and add it to an activity.  `direction?'
;;; can be nil, 'input, or 'output.  `side' is the side of the activity that
;;; will get the connection, one of 'top, 'bottom, 'left, or 'right.  The
;;; position of the connection is the midpoint of that side.  The new connection
;;; is returned.

(defun g2gl-activity-add-standard-connection (activity direction? side)
  (add-stub activity nil g2gl-standard-connection-class direction? side
            (midpoint-position-of-side-of-block side activity)
            nil nil g2gl-standard-connection-line-pattern
            g2gl-standard-connection-arrows))




(defun block-has-input-connections-p (block)
  (loop for c being each input-connection of block
        return t))

(defun block-has-output-connections-p (block)
  (loop for c being each output-connection of block
        return t))

(defun block-has-connections-p (block)
  (loop for c being each connection of block
        return t))

;; Only consider connected connections, i.e. ignore loose ends.
(defun block-has-connected-input-connections-p (block)
  (loop for c being each input-connection of block
        unless (loose-end-p (input-end-object c))
        return t))

;; Above four are general. Move to a CONNECT* module!



;;; The function `count-connected-block-connections-per-side' returns a count of
;;; each connected input and output connection of block as eight integer count
;;; values for the input and output sides as follows:
;;;
;;;   (1) left input; (2) top input; (3) right input; (4) bottom input; (5) left
;;;   output; (6) top output; (7) right output; and (8) bottom output

(defun count-connected-block-connections-per-side (block)
  (loop with lic fixnum = 0 with tic fixnum = 0        ; left-, etc., input count
        with ric fixnum = 0 with bic fixnum = 0
        with loc fixnum = 0 with toc fixnum = 0        ; left-, etc., output count
        with roc fixnum = 0 with boc fixnum = 0
        for x being each connection of block           ; a connection or port name
        unless (loose-end-p (get-block-at-other-end-of-connection x block))
          ;; a connected connection, not a port name
          do (cond
               ((eq (output-end-object x) block)
                (case (get-side-given-end-position (output-end-position x))
                  (left (incff lic))
                  (top (incff tic))
                  (right (incff ric))
                  (t (incff bic))))
               (t
                (case (get-side-given-end-position (input-end-position x))
                  (left (incff loc))
                  (top (incff toc))
                  (right (incff roc))
                  (t (incff boc)))))
        finally
          (return
            (values lic tic ric bic
                    loc toc roc boc))))

;; General. Move to a CONNECT* module!



;;; Update the delta-or-deltas of a connection, reclaiming the old slot value.

(defun change-delta-or-deltas (connection new-delta-or-deltas)
  (setf (delta-or-deltas connection)
        (prog1 new-delta-or-deltas
          (reclaim-slot-value (delta-or-deltas connection)))))

;; Move to a CONNECT* module!
;; Should this be part of the slot-value-setter?
;; Should it check for a singleton list and convert to atom?


;; general -- move elsewhere!
(defun opposite-side-of-side (side)
  (case side
    (bottom 'top)
    (right 'left)
    (top 'bottom)
    (left 'right)))

;; copied from shift-end-position-of-connection in connect2.lisp -- should move
;; there
(defun length-of-side-of-block (side block)
  (if (left-or-right-side? side)
      (height-of-block block)
      (width-of-block block)))

(defun midpoint-position-of-side-of-block (side block)
  (halfw (length-of-side-of-block side block)))


;;; Fix up the end and bend positions of a connection.

(defun clean-up-connection (connection
                             &optional
                             delta-or-deltas
                             (input-end-side 'bottom)
                             (output-end-side
                               (opposite-side-of-side input-end-side))
                             (input-end-position
                               (midpoint-position-of-side-of-block
                                 input-end-side
                                 (input-end-object connection)))
                             (output-end-position
                               (midpoint-position-of-side-of-block
                                 output-end-side
                                 (output-end-object connection))))
  (change-delta-or-deltas connection delta-or-deltas)
  (setf (input-end-position connection)
        (combine-side-and-position-on-side-for-end-position
          input-end-side input-end-position))
  (setf (output-end-position connection)
        (combine-side-and-position-on-side-for-end-position
          output-end-side output-end-position))
  connection)



(defun g2gl-activity-in-connection-count (g2gl-activity)
  (loop for c being each input-connection of g2gl-activity count t))





;;; Get-full-deltas-for-connection returns a newly created list (using
;;; gensym conses) of deltas for connection that go all the way from the input
;;; end position of connection to the output end position of connection.

;;; The implicit last two deltas are never omitted.  And zero or implicit deltas
;;; are not omitted.  In the case of diagonal connections, there are always an
;;; even and nonzero number of deltas.  The case of a diagonal connection with
;;; one element D in delta-or-deltas is a kind of degenerate case, which is
;;; generally results from an orthogonal connection with one delta being turned
;;; interactively into a diagonal connection. It gets interpreted as a final
;;; straight connection into the output end object.  This gets normalized into a
;;; fully diagonal connection with the final "straight" part treated as a
;;; diagonal connection that happens to be straight.  The resulting deltas list,
;;; therefore, is always even in length in the diagonal connection case.

;;; If maximum-of-deltas? may be supplied optionally. Its purpose is to limit
;;; the number of deltas to some "reasonable" limit.  It can be nil or a
;;; fixnum. If it's nil, then all deltas are put in the resulting list.
;;; Otherwise, it should be a fixnum integer 2 or greater specifying a limit on
;;; the number of deltas collected.
;;;
;;; If the limit is reached, a second value of t will be returned, indicating
;;; the list has been truncated.  Otherwise, the second value is nil.

(defun get-full-deltas-for-connection (connection &optional maximum-of-deltas?)
  (let* ((truncation-occurred? nil)
         (deltas
           (with-connection
               connection nil t nil
               ((delta-or-deltas (delta-or-deltas connection))
                ;; missing link deltas 1 and 2:
                d1 d2)
             (multiple-value-bind
                 (lastx lasty lasth)
                 (compute-last-delta-anchor-point connection)
               ;; Lastx/lasty give the x/y position of the last delta anchor.
               ;; lasth is true iff the last delta orientation is horizontal.
               (cond
                 ((null delta-or-deltas)
                  (if lasth
                      (setq d1 (-w output-end-x-position lastx)
                            d2 (-w output-end-y-position lasty))
                      (setq d1 (-w output-end-y-position lasty)
                            d2 (-w output-end-x-position lastx)))
                  (gensym-list d1 d2))
                 (t
                  (if lasth
                      (setq d1 (-w output-end-y-position lasty)
                            d2 (-w output-end-x-position lastx))
                      (setq d1 (-w output-end-x-position lastx)
                            d2 (-w output-end-y-position lasty)))
                  (nconc
                    (if (atom delta-or-deltas)
                        (if (connection-diagonal-p  connection)
                            (let ((deltas (gensym-list delta-or-deltas d1)))
                              (multiple-value-bind
                                  (lastx lasty lasth)
                                  (compute-last-delta-anchor-point connection deltas)
                                (if lasth
                                    (setq d1 (-w output-end-y-position lasty)
                                          d2 (-w output-end-x-position lastx))
                                    (setq d1 (-w output-end-x-position lastx)
                                          d2 (-w output-end-y-position lasty))))
                              deltas)
                            (gensym-list delta-or-deltas))
                        (if maximum-of-deltas?
                            (loop with i = 2 ; first two are d1/d2
                                  for d in delta-or-deltas
                                  when (>=f i maximum-of-deltas?)
                                    do (loop-finish)
                                  collect d into l using gensym-cons
                                  do (incff i)
                                  finally
                                    (when (>=f i maximum-of-deltas?)
                                      (setq truncation-occurred? t))
                                    (return l))
                            (copy-list-using-gensym-conses
                              delta-or-deltas)))
                    (gensym-list d1 d2))))))))
    (values deltas truncation-occurred?)))

;; This was adapted from add-missing-deltas-to-connection . (MHD 1/19/05)

;; At present the one user of this is compute-connection-tracing-step-positions.
;; It uses the maximum-of-deltas? feature to limit the number of potential
;; floating point operations so that it need not be concerned with temporary
;; area overflow. (MHD 1/19/05)





;;; Diagonal-connection-length-from-full-deltas computes the total length of a
;;; connection given its full list of deltas, which must be an even-length list
;;; of pairs of deltas (see get-full-deltas-for-connection, about obtaining such
;;; a list).
;;;
;;; This computes the length by computing the sum, for each two consecutive
;;; deltas in deltas, of the square roots of the sum of the squares of those
;;; consecutive deltas.
;;;
;;; This should be generally be called in temporary gensym-float creation
;;; context. This conses gensym floats and returns a gensym float.
;;;
;;; Note that in theory, a superlong list of deltas could result overfloat of of
;;; temporary areas. This function does not handle such a case.  However, this
;;; scenario seems exceedingly unlikely.  A partial workaround could probably be
;;; worked out by splitting such a superlong list into multiple lists, and
;;; performing multiple individually wrapped invocations of this.

(defun diagonal-connection-length-from-full-deltas (deltas)
  (loop with sum gensym-float = 0.0d0
        ;; the following 4 number inits are arbitrary:
        with d1 gensym-float = -1.0d0
        with d2 gensym-float = -1.0d0
        with squares-sum gensym-float = -1.0d0
        with sqrt gensym-float = -1.0d0
        for l on deltas by 'cddr-of-cons
        while (cdr-of-cons l)
        do (setq d1 (coerce-fixnum-to-gensym-float (first-of-cons l)))
           (setq d2 (coerce-fixnum-to-gensym-float (second-of-cons l)))
           (setq squares-sum
                 ;; expt contagion to gensym float assumed here:
                 (+e (expt d1 2) (expt d2 2)))
           (setq sqrt (sqrte squares-sum))
           (setq sum (+e sum sqrt))
        finally (return sum)))





;;;; Some constant URI strings for exporting to XML documents.

;;; The BPEL XML namespace URI is defined by the BPEL4WS spec, 5 May 2003.
;;; http://xml.coverpages.org/BPELv11-May052003Final.pdf
;;; http://xml.coverpages.org/bpel4ws.html

(defconstant bpel-xml-namespace-uri
  #w"http://schemas.xmlsoap.org/ws/2003/03/business-process/")

;;; The default expression and query language for BPEL is XPath.
(defconstant xpath-expression-language-uri
  #w"http://www.w3.org/TR/1999/REC-xpath-19991116")


;;; The partner link namespace is defined by the BPEL4WS spec (see above).

(defconstant plnk-xml-namespace-uri
  #w"http://schemas.xmlsoap.org/ws/2003/05/partner-link/")


;;; The XML Schema datatypes namespace URI is defined by XML Schema Part 2:
;;; Datatypes.  The BPEL4WS spec requires that variable types be XML Schema
;;; simple types.
;;; http://www.w3.org/TR/xmlschema-2/#namespaces

(defconstant xsd-datatypes-xml-namespace-uri
  #w"http://www.w3.org/2001/XMLSchema-datatypes")

(defvar xsd-datatypes-xml-namespace-prefix 'xsd)


;;; We define our own URIs for G2GL activities and expressions and G2 item or
;;; value types.

(defconstant g2gl-xml-namespace-uri
  #w"http://www.gensym.com/g2gl/")
(defconstant g2gl-expression-language-uri
  #w"http://www.gensym.com/g2gl/g2gl-expression")
(defconstant g2-datatypes-xml-namespace-uri
  #w"http://www.gensym.com/g2gl/g2-datatypes")

(defvar g2gl-xml-namespace-prefix 'g2gl)
(defvar g2-datatypes-xml-namespace-prefix 'g2)


;;;; G2-BPEL Implementation: Classes and Methods

;; impl. notes:
;;
;; (1) Later, change ALL slots that don't have an explicity lookup-slot slot
;; type feature to have a vector-slot slot type feature.  Leaving off for now,
;; since it's clutter, and makes changes just slightly harder.
;;
;; (2) To have the "body" be an instance of our special-purpose subclass of
;; KB-workspace, have a shadowed version of create-subworkspace, which is rigged
;; to create that class (or let the user choose a subclass of that class).



(def-class (g2gl-object object
                        not-user-instantiable))

(def-absent-slot-putter g2gl-namespace-map (g2gl-object value)
  ;; Slot was moved to g2gl-definition, discard the value if one was saved on a
  ;; non-definition object (it would have been ignored anyway). -dougo, 4/25/05
  (declare (ignore g2gl-object value))
  nil)



(def-class (g2gl-activity g2gl-object
             (stubs #.(g2gl-standard-connection-stub 'input 'top 20)
                    #.(g2gl-standard-connection-stub 'output 'bottom 20))
             ;; Abstract class: Also, note: subclassing, i.e., by users, is NOT
             ;; supported. Leaving out the feature (foundation-class
             ;; g2gl-activity) is to prevent subclassing. (MHD 11/29/04)
             not-user-instantiable do-not-put-in-menus
             ;; define g2gl-activity-p
             define-predicate)

  ;; Refine to suppress adding names to global name directory and to suppress
  ;; notes about multiple same-named instances! Refine to accept
  ;; g2gl-activity-name (grammar, local names directory; defined below) instead
  ;; of a general item name!
  (name-or-names-for-frame nil local-name-or-names)

  ;; the following is the named type of activity (a class-wide information
  ;; slot). It should never be changed on any instance.  Values are, e.g.,
  ;; SCOPE, WAIT, etc. default must be filled in on subclasses
  (g2-bpel-activity-name nil lookup-slot not-user-editable)

  ;; the following reflects the g2gl-activity feature connections-configuration,
  ;; which should never be changed on any instance; the default must be filled
  ;; on on each subclass (handled by def-g2gl-activity):
  (g2gl-connections-configuration-feature nil lookup-slot not-user-editable))




;;; A G2GL activity e is an entry activity "if e has no connected in-connections
;;; or, where the connections configuration type of the class of e is the symbol
;;; loop-anchor, has no connected in-connections except for one left-side or
;;; right-side in-connection".

(defun g2gl-activity-is-an-entry-activity-p (e)
  (or (not (block-has-connected-input-connections-p e))
      (let* ((feature (g2gl-connections-configuration-feature e))
             (connections-configuration-type
               (if feature (second feature))))
        (and (eq connections-configuration-type 'loop-anchor)
             ;; no in-connections except for one left-side or
             ;; right-side in-connection:
             (multiple-value-bind (lic tic ric bic)
                 (count-connected-block-connections-per-side e)
               (and (=f (+f lic ric) 1)
                    (=f (+f tic bic) 0)))))))



;;; The class `g2gl-activity-with-body', a subclass of g2gl-activity, is an
;;; abstract class (not user instantiable), and is used for activitities that
;;; must have a body, represented as a subworkspace.  Subclasses include, e.g.,
;;; G2GL-scope, which specifies.  The class `g2gl-handler' is a similarly
;;; abstract subclass, used for defining handlers (g2gl-fault-handler, et al).

(def-class (g2gl-activity-with-body g2gl-activity not-user-instantiable))

(def-class (g2gl-handler g2gl-activity-with-body not-user-instantiable))

(def-class (g2gl-event-handler g2gl-handler not-user-instantiable))


;;; The class `g2gl-flow-join', an abstract subclass of g2gl-activity, is used
;;; for flow-join activities, which bring together branches that stem from a
;;; g2gl-flow-split.  Currently, the subclasses defined are:
;;;
;;;   (a) g2gl-flow-sync - corresponds to the BPEL <flow> activity - a/k/a a
;;;   "synchronizing merge" (with a single subsequent execution path) -
;;;   synchronize many execution paths and then merge them all into one.
;;;
;;;   (b) g2gl-flow-discriminator - merge many execution paths without
;;;   synchronizing and execute the subsequent activity only once;
;;;
;;;   (c) g2gl-n-out-of-m-flow-join - merge many execution paths - perform
;;;   partial synchronization on N (where N is specified prior to run time)
;;;   paths, and execute the subsequent activity only once - a generalization of
;;;   a "discriminator";
;;;
;;;   (d) g2gl-flow-terminator - terminate all active incoming execution paths
;;;   once reached by any one of them, and execute the subsequent activity only
;;;   once.
;;;
;;; In G2GL a pair of a g2gl-flow-sync instance and an instance of any subclass
;;; of g2gl-flow-join in a well-formed flowchart, that is, with all activity
;;; branches stemming from the flow split rejoining in the corresponding flow
;;; join, must maintain a marker unique to the pair in any threads that travel
;;; along any paths from start to end (from the flow sync to the flow join). The
;;; activity subclasses of this class all are required to implement this
;;; protocol, either by deleting a thread containing a marker, or by removing a
;;; marker from a thread's list of markers. (See note below.)

(def-class (g2gl-flow-join g2gl-activity not-user-instantiable))

;; Note: this is primarily intended to support the G2GL-flow-terminator
;; activity.  At present, this adds some slight overhead, even if the feature is
;; not used at all in a given process. If we either decide to do away with the
;; g2gl-flow-terminator activity, we should get rid of it, or, if the compiler
;; has some global knowledge that the feature is not in use in a process,
;; perhaps the code with the overhead could be "compiled out". (MHD 10/14/05)

;; Note: g2gl-flow-join and all subclasses except for g2gl-flow-sync and their
;; functionality are not *yet* in the detailed spec, though they have been
;; discussed and agreed to with LH (who disclaims at this point formal
;; responsibility); they are to be added presently to the next revision of the
;; spac (presumably to be maintained by me). (MHD 10/14/05)



(def-class (g2gl-definition g2gl-object
                            not-user-instantiable
                            do-not-put-in-menus)
  (g2gl-target-namespace #w"" (type uri))
  (g2gl-namespace-map nil (type g2gl-namespace-map)))

(def-absent-slot-putter g2gl-xml-namespace (g2gl-definition value)
  ;; Slot was removed, discard the value if it was set on a saved definition.
  ;; In most cases it was just bpel-xml-namespace-uri, which was the old default
  ;; value, and this is now always exported as the default namespace.  If it was
  ;; set to some other namespace URI, the exported document wouldn't have been
  ;; valid BPEL anyway. -dougo, 4/25/05
  (declare (ignore g2gl-definition value))
  nil)


(def-class (g2gl-process g2gl-definition (foundation-class g2gl-process))
  ;; NOTE: new for G2 8.2r1: allow G2GL-process to be subclassed. (MHD 2/28/06)

  ;; NOTE: for a source G2GL process only: Note: in this case, we require
  ;; name-or-names-for-frame to have at least one name ("G2GL process name") ,
  ;; and we require there to be a subworkspace ("body").
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-outline . foreground)
                   (g2-icon-background . #.g2gl-icon-background-color)
                   (g2-icon-symbol . black))
       g2-icon-background #.g2gl-icon-rectangle-background
       g2-icon-outline #.g2gl-icon-rectangle-outline
       g2-icon-symbol
       (outline (20 6) (20 12) (30 12) (30 6))
       (outline (32 23) (25 28) (18 23) (25 18))
       (outline (9 35) (9 41) (19 41) (19 35))
       (outline (32 35) (32 41) (42 41) (42 35))
       (lines (25 12) (25 18))
       (lines (14 35) (14 23))
       (lines (14 23) (18 23))
       (lines (37 35) (37 23))
       (lines (32 23) (37 23)))))
  (g2gl-partner-link-groups nil (type g2gl-partner-link-groups))
  (names-of-g2gl-service-switches-for-instantiation
    nil (type g2gl-service-switch-names))
  (name-of-g2gl-service-switch-for-connection
    g2gl-standard-service-switch
    (type g2gl-service-switch-name))
  (callable-as-a-procedure t (type yes-or-no))
  (enable-instance-compensation nil (type yes-or-no))
  (this-is-an-abstract-process nil (type yes-or-no) vector-slot)
  ;; several read-only slots were moved from here down to the end so that
  ;; user-editable slots would appear uninterrupted, and higher up.  The
  ;; signature slot could get verbose, so it's at the bottom. (for G2 8.2r1)
  ;; (MHD 3/7/06)
  (break-on-execution-fault nil (type yes-or-no))
  (individual-execution-display-mode
    nil (type individual-execution-display-mode))
  (superimposed-tracings-execution-display-mode
    ;; Have custom category: superimposed-tracings-execution-display-mode
    nil (type superimposed-tracings-execution-display-mode))
  (thread-token-properties-for-g2gl-process nil)
  (thread-token-class nil (type class)) ; type "class?"
  (thread-token-color nil (type highlighting-object-color))
  (stack-of-compilation-versions nil vector-slot)        ; non-attribute
  
  ;; packed-compilation-version slot is used to save the latest compilation
  ;;  version. It is a list that contains all fields of g2gl-compilation-version.
  ;; The packed-compilation-version slot is iniailized before saving g2gl-process
  ;;  into KB and during loading g2gl-process from KB and reclaimed after saving
  ;;  and after g2gl-process is loaded
  (packed-compilation-version nil save)
  
  (latest-existing-compilation-version-was-disowned nil vector-slot) ; needs type!
  (latest-attempted-compilation-version-number ; 0 equivalent to none
    0 (type integer?) not-user-editable system save vector-slot)

  ;; All but 2nd and 3rd of the following 6 slots new in G2 8.2r1. (MHD 3/7/06)
  (latest-attempted-compilation-version-time ; new in 8.2r1
    nil (type frame-edit-timestamp?) not-user-editable system save)

  (number-of-errors-in-latest-attempted-compilation
    0 (type integer) not-user-editable system save)
  (number-of-warnings-in-latest-attempted-compilation
    0 (type integer) not-user-editable system save)

  (g2gl-process-compilation-version-number ; none (nil) if none; new in 8.2r1
    nil (type integer?) not-user-editable system do-not-save)
  (g2gl-process-compilation-version-time ; new in 8.2r1
    nil (type frame-edit-timestamp?) not-user-editable system do-not-save)
  (g2gl-process-procedure-signature        ; new in 8.2r1
    NO-SIGNATURE
    ;; ^-- this is the default value, which corresponds to an uncompiled
    ;; procedure, so, since compilations are not saved in KBs, this is what the
    ;; will be every time an instance is restored from a saved KB.  it prints as
    ;; "none"; () -- i.e., nil -- corresponds to zero args. (MHD 3/3/06)
    (type g2gl-process-procedure-signature?)
    not-user-editable system do-not-save))



(def-slot-value-writer frame-edit-timestamp? (value)
  (cond
    ((null value) (tformat "none"))
    (t (twrite-frame-edit-timestamp value))))



(def-slot-value-writer g2gl-process-procedure-signature? (value frame)
  (if (atom value)
      (tformat
        (case value
          (NO-SIGNATURE "none")
          (t
           ;; presumably NIL, i.e., no args
           "()")))
      (loop with optional-now-p = nil
            for ((name type default-value?) . more?)
                on value
            initially (tformat "(")
            when (and default-value?
                      (not optional-now-p)
                      (loop for (nil nil later-dv?) in more?
                            always later-dv?))
              do (setq optional-now-p t)
            do (twrite-symbol name) (tformat ": ")
               (write-g2gl-type-specifier?-from-slot type frame)
               (when default-value?
                 (tformat " (~adefault: "
                          (if optional-now-p "optional, " ""))
                 (twrite-g2gl-value default-value?)
                 (tformat ")"))
               (when more? (tformat ", "))
            finally
              (tformat ")"))))



(define-category-evaluator-interface (g2gl-process-procedure-signature?
                                       :access read)
    (or (member no-signature)
        (sequence
          (structure
            g2gl-process-procedure-signature-arg
            ((variable-name symbol)
             (variable-type
               (or (member general integer float truth-value
                           text symbol class)
                   (sequence symbol)))        ; 2 or 3
             (default-value
               (or (no-item)
                   integer float truth-value text symbol))))))
  ((get-form (slot-value))
   (if (listp slot-value)
       (allocate-evaluation-sequence
         (loop with optional-now-p = nil
               for i from 1
               as ((name type default-value?) . more?) on slot-value
               when (and default-value?
                         (not optional-now-p)
                         (loop for (nil nil later-dv?) in more?
                               always later-dv?))
                 do (setq optional-now-p t)
               collect (allocate-evaluation-structure
                         (eval-list
                           'variable-name name
                           'variable-type
                           (if (atom type)
                               type
                               (allocate-evaluation-sequence
                                 (loop for sym in type
                                       collect sym using eval-cons)))
                           'is-optional
                           (if optional-now-p
                               evaluation-true-value
                               evaluation-false-value)
                           'default-value default-value?))
                 using eval-cons))
       slot-value)))




;;; The following two slots used to be text-strings (type uri) to hold the
;;; query/expression language namespace URI.  They were removed since we only
;;; support one language (G2GL), and even if we do eventually support other
;;; languages (eg. XPath) this probably isn't the way to do it.  See HQ-5019191
;;; "G2GL: bpel-expression-language should not be editable".

(def-absent-slot-putter bpel-query-language (g2gl-process uri)
  (declare (ignore g2gl-process uri))
  nil)
(def-absent-slot-putter bpel-expression-language (g2gl-process uri)
  (declare (ignore g2gl-process uri))
  nil)





;;; The `initialize-after-reading method for g2gl-process' primarily does one
;;; service: it compiles the g2gl-process, unless it's an abstract process (its
;;; this-is-an-abstract-process attribute is true).
;;;
;;; The compiler for G2GL processes is generally quite well optimized for speed,
;;; and so it should be practically instantaneous to compile.  Therefore, we can
;;; avoid the need to save out compilations in the KB.  Not saving out
;;; compilations also gives us flexibility to change (improve and/or debug) the
;;; compilation output between releases without the need to ensure
;;; compatibility.
;;;
;;; Doing the compilation in this initialize-after-reading method as opposed to
;;; doing it in a post-loading function ensures that we will only attempt to
;;; compile those G2GL-process instances being restored from the saved KB being
;;; loaded.  If we did this in a post-loading function, we could skip the
;;; instances that are already compiled; however, we would not be able (without
;;; additional facilities and logic) to skip instances that are in the current
;;; KB but were not just loaded from the incoming KB.
;;;
;;; In order to work, the following key assumptions must be met: (a) that the
;;; instance has been sufficiently restored such that all its attributes, its
;;; subworkspace, and all attributes of all objects on its subworkspace to all
;;; levels have been restored; (b) that compilation of a G2GL process does not
;;; rely on the presence or state of any other G2GL process, or any other
;;; object, except possibly the G2GL-parameters system table; and (c) that the
;;; G2GL-parameters system table is either not needed, or is appropriately bound
;;; to the system table in force, or a suitable, reasonable facsimile thereof.

(def-class-method initialize-after-reading (g2gl-process)
  (funcall-superior-method g2gl-process)
  (restore-compilation-structure g2gl-process)
  (unless (this-is-an-abstract-process g2gl-process)
    (compile-g2gl-process-if-necessary-and-possible g2gl-process)))

(def-class-method prepare-to-saving-frame (g2gl-process)
  (funcall-superior-method g2gl-process)
  (create-compilation-structure g2gl-process))

(def-class-method on-frame-saved (g2gl-process)
  (funcall-superior-method g2gl-process)
  (delete-compilation-structure g2gl-process))

;; For review: the reliance on these attributes of G2GL-parameters in the
;; compiler: suppress-unspecified-partner-link-variable-type-faults and
;; compile-text-elements-in-source-for-execution-displays For now, they probably will not be
;; handled correctly (or if they are, it will be accidental).  Review whether it
;; might be better in both cases to handle them differently, without reliance on
;; the system table. (MHD 3/18/05)

;; We could decide later to save out compilations.  This could serve both as an
;; optimization to speed up loading, and also as a way to implement the feature
;; of allowing disembodied G2GL process instances to be saved and yet still be
;; be able to run -- an analog of the text-stripping feature we have for rules
;; and procedures. (MHD 3/18/05)



;;; The `cleanup method for g2gl-process' invokes reclaim-g2gl-process on itself
;;; after invoking its superior method.

(def-class-method cleanup (g2gl-process)
  (funcall-superior-method g2gl-process)
  (reclaim-g2gl-process g2gl-process))



(def-slot-value-reclaimer stack-of-compilation-versions (slot-value)
  ;; For now, just reclaim the top-level conses of the list stored in this
  ;; slot. Issue: what needs to or should be done with the
  ;; g2gl-compilation-version instances that are in this list?! (MHD 12/13/04)
  (reclaim-slot-value-list slot-value))




;;; The category `g2gl-service-switch-name' ...
;;; The category `g2gl-service-switch-names' ...

(def-grammar-list-category g2gl-service-switch-names (g2gl-service-switch-name)
  :separator \, :empty-list-symbol none)

(def-grammar-category g2gl-service-switch-name ()
  (unreserved-symbol)
  ('g2gl-standard-service-switch))

(def-grammar-category g2gl-service-switch-name? ()
  ('none nil)
  (g2gl-service-switch-name))

(def-registered-directory-of-names g2gl-service-switch-name)

(def-slot-value-compiler g2gl-service-switch-name? (parse-result)
  parse-result)

(def-slot-value-writer g2gl-service-switch-name (value)
  (twrite-symbol value))

(def-slot-value-compiler g2gl-service-switch-names (parse-result)
  (cond
    ((eq parse-result 'none)
     nil)
    (t
     (remove-noise-at-head-of-list-phrase parse-result))))

(def-slot-value-writer g2gl-service-switch-names (value)
  (cond
    ((null value)
     (twrite-string "none"))
    (t
     (tformat "~(~L,-~)" value))))


;;; The category `individual-execution-display-mode' is for the slot of the same
;;; name.  This is a category allowing a small set of symbol choices.

(def-grammar-category individual-execution-display-mode ()
  ('none nil)
  ('trace-top-level)
  ('trace-all-levels)
  ('break-on-entry)
  ('break-on-entry-at-all-levels))

(def-slot-value-writer individual-execution-display-mode (value)
  (twrite-symbol-or-none value))




;;; The category `g2gl-partner-link-groups', `g2gl-partner-link-group', and
;;; `g2gl-partner-link-variable-names' ...

(def-grammar-list-category g2gl-partner-link-groups (g2gl-partner-link-group)
  :separator \; :empty-list-symbol none)

(def-grammar-category g2gl-partner-link-group ()
  ((g2gl-partnership-name '\: g2gl-partner-link-variable-names)))

(def-grammar-list-category g2gl-partner-link-variable-names
    (g2gl-partner-link-variable-name)        ; category defined further below
  :separator \,)

(def-grammar-category g2gl-partnership-name ()
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-partnership-name)

(def-grammar-category g2gl-partner-link-variable-name? ()
  ('none nil)
  (unreserved-symbol))

(def-grammar-category g2gl-partner-link-variable-name ()
  (unreserved-symbol))

(def-slot-value-writer g2gl-partner-link-variable-name? (value)
  (twrite-symbol-or-none value))


;;; The compiler for g2gl-partner-link-groups expects either the symbol NONE or
;;; list structure like this
;;;
;;;   (|;| (foo |:| (|,| bar baz)) (abc |:| (|,| def hij)))
;;;
;;; and it returns nil for NONE and turns the list structure into something like
;;; this:
;;;
;;;   ((foo bar baz) (abc def hij))

(def-slot-value-compiler g2gl-partner-link-groups (parse-result)
  (cond
    ((eq parse-result 'none)
     nil)
    (t
     ;; get rid of noise in some parts of the list structure:
     (loop for l in (remove-noise-at-head-of-list-phrase parse-result)
           collect (phrase-cons
                     (car l)
                     ;; skip |:|
                     (remove-noise-at-head-of-list-phrase (caddr l)))
             using phrase-cons))))



(def-slot-value-writer g2gl-partner-link-groups (value)
  (cond
    ((null value)
     (twrite-string "none"))
    (t
     (loop for ((partnership-name . partner-link-variable-names) . more?)
           on value
           do (tformat "~(~a~): ~(~L,-~)~a"
                       partnership-name
                       partner-link-variable-names
                       (if more? "; " ""))))))


;;; The category `g2gl-operation-name' ...

(def-grammar-category g2gl-operation-name ()
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-operation-name)

(def-grammar-category g2gl-operation-name? ()
  ('none nil)
  (g2gl-operation-name))

(def-slot-value-writer g2gl-operation-name? (value)
  (twrite-symbol-or-none value))


;;; The category `g2gl-message-variable-name' ...

(def-grammar-category g2gl-message-variable-name ()
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-operation-name)

(def-grammar-category g2gl-message-variable-name? ()
  ('none nil)
  (g2gl-message-variable-name))

(def-slot-value-writer g2gl-message-variable-name? (value)
  (twrite-symbol-or-none value))



;;; The category `superimposed-tracings-execution-display-mode' ...

(def-grammar-category superimposed-tracings-execution-display-mode ()
  ('trace-top-level)
  ('trace-all-levels)
  ('normal nil))

(def-slot-value-writer superimposed-tracings-execution-display-mode (value)
  (tformat "~(~a~)" (or value 'normal)))




;;; The category `symbol-or-whole-string?' is to be used for labels.  To
;;; represent "no label", you use the symbol NONE.  Should you need the label
;;; to be literally "NONE", you must use the string "none" (i.e., written with
;;; ""'s).  In attribute tables and similar context labels that are symbols are
;;; generally written in lowercase, while labels that are strings are generally
;;; written as in the original string.

(def-grammar-category symbol-or-whole-string? ()
  ('none nil)
  (whole-string?)
  (symbol))

(def-slot-value-writer symbol-or-whole-string? (value)
  (twrite-symbol-or-string-or-none value))

;; Defined for highlighting-object-label only for now. Consider having this be
;; used for label attributes in readout tables and buttons!



;;; The category `object-name?' ...

(def-grammar-category object-name? ()
  ('none nil)
  (object-name))

(def-slot-value-writer object-name? (value)
  (twrite-symbol-or-none value))

;; General -- move elsewher.  Strangely, there was a grammar rule (object-name?
;; 'none nil) in MENUS, but it didn't seem connected to anything.  I commented
;; it out. (MHD 7/7/04)


(def-grammar-category highlighting-object-color ()
  ('none nil)
  (color-or-metacolor)
  ;; do this:  ?
;  (('region region-name 'color color-or-metacolor))
  )

(def-slot-value-writer highlighting-object-color (value)
  (twrite-symbol-or-none value))



;;; The category `g2gl-activity-name' ...

(def-grammar-category g2gl-activity-name? ()
  ('none nil)
  (g2gl-activity-name))

(def-grammar-category g2gl-activity-name ()
  (unreserved-symbol))

(def-slot-value-writer g2gl-activity-name? (value)
  (twrite-symbol-or-none value))

;;; get-g2gl-activity-name is a convenience accessor for the (primary) name of a
;;; G2GL activity.

(defun get-g2gl-activity-name (g2gl-activity)
  (get-primary-name-for-frame-if-any g2gl-activity))


;;; The category `g2gl-namespace-map'

(def-grammar-category g2gl-namespace-map-element ()
  (('default '\: uri)
   (nil 3))
  ((unreserved-symbol '\= uri)
   (1 3)))

(def-grammar-list-category g2gl-namespace-map (g2gl-namespace-map-element)
  :separator \; :empty-list-symbol none)

(def-slot-value-compiler g2gl-namespace-map (parse-result)
  (if (eq parse-result 'none)
      nil
      (remove-noise-at-head-of-list-phrase parse-result)))

(def-slot-value-writer g2gl-namespace-map (value)
  (cond
    ((null value)
     (twrite-string "none"))
    (t
     (loop for (prefix uri) in value
           as first-time? = t then nil
           do
       (unless first-time?
         (tformat ";~%"))
       (if prefix
           (progn (twrite-symbol prefix) (tformat " = "))
           (tformat "default: "))
       (tformat "\"")
       (tformat "~a" uri)
       (tformat "\"")))))


;;; Add an XML namespace prefix and uri to the namespace map of a G2GL
;;; definition, if they are not already included.  If they are already included,
;;; reclaim the uri string.

(defun add-xml-namespace-to-g2gl-definition (prefix? uri definition)
  (let ((binding (slot-value-list prefix? uri))
        (namespace-map (g2gl-namespace-map definition)))
    (if (member binding namespace-map :test #'equalw)
        (progn
          (reclaim-text-string uri)
          (reclaim-slot-value-list binding))
        (change-slot-value
          definition 'g2gl-namespace-map
          (nconc namespace-map (slot-value-list binding))))))

;; TO DO: this should disallow duplicate prefixes, or generate a new prefix or
;; something.  -dougo, 4/24/05



;;; The g2gl-definition object currently being imported.  This is set during
;;; convert-xml-wsdl-to-g2-wsdl and convert-xml-bpel-process-to-g2-bpel.

(defvar current-g2gl-definition)

(defun add-xml-namespace-to-current-g2gl-definition (prefix? uri)
  (add-xml-namespace-to-g2gl-definition prefix? uri current-g2gl-definition))





;;; The system table `g2gl-parameters' ... Note that for
;;; time-between-time-slices-for-execution-of-thread nil means "continuous",
;;; "asap", "epsilon time", "minimal".  Note that when this is non-nil, then
;;; rescheduling time granularity will be bound by the
;;; minimum-scheduling-interval of timing-parameters.  The value of that
;;; parameter cannot be lower than CONTINUOUS, or, if a number of seconds, .002
;;; (in 8.1, previously .05).  Therefore, it's important to set that to either
;;; continuous or the minimum, .002.

(def-system-frame g2gl-parameters g2-bpel

  ;; a URL string specific to (including the name of) the G2GL service switch
  ;; named G2GL-standard-service-switch
  (url-for-g2gl-standard-service-switch
    #w"g2gl://localhost/g2gl-standard-service-switch"
    (type nil))        ; later (type whole-string)! or "URL-string"?

  (alist-of-communication-attributes-for-g2gl-standard-service-switch
    ;; an alist that might include, for example, entries for attributes such as
    ;; internet-address, user-name, password, and anticipated-out-bandwidth
    nil)


  ;; same as maximum time slice: (.05 seconds, or 50 milliseconds). For now,
  ;; we're having this be noneditable and equivalent to maximum-time-slice-size
  ;; per reasons explained at continue-execution-of-thread, q.v.
  (time-slice-for-execution-of-thread
    .05 (type nil) ; fix grammar!
    vector-slot)

  (time-between-time-slices-for-execution-of-thread
    nil (type g2gl-short-interval?) vector-slot)

  (break-on-all-execution-faults nil (type yes-or-no) vector-slot)


  ;; normally true to suppress the posting of a compilation error and/or the
  ;; signaling of an execution fault when the type of a partner link variable is
  ;; not specified, but nil to permit such an error to be posted and such a
  ;; fault to be signaled
  (suppress-unspecified-partner-link-variable-type-faults t (type yes-or-no))


  ;; If no name (nil), the execution displays go on all active (logged-in)
  ;; windows. Windows are rarely named.  Consider borrowing the -window <name or
  ;; class> convention of designating a window by name-or-class.  You could have
  ;; a class of window used for debugging this way.  (MHD 12/7/04)
  (name-of-window-for-g2gl-execution-displays nil (type object-name?))

  (default-scale-for-execution-displays
      1.0
    ;; I'm disabling this slot from the user model for the final release of
    ;; 8.1r0.  The spec makes some use of it, but I'm not satisfied with it, and
    ;; it does not account for other divergences I've already made from the
    ;; spec, which are good, I feel.  E.g., different scales for superimposed
    ;; vs. non-superimposed case.  Also, there really should be positioning
    ;; ultimately.  So this is not ready for prime time at this time.  Taking
    ;; this out resolves HQ-5010307 "G2GL: Default-scale-for-execution-displays
    ;; doesn't seem to do anything" as well. (MHD 5/3/05)
    (type nil))                                ; was: (type workspace-scale-float) !!


  (compile-text-elements-in-source-for-execution-displays nil (type yes-or-no))
  (time-between-mini-tracing-steps .02 (type g2gl-short-interval)) ; 1/50 seconds
  (time-between-maxi-tracing-steps 0.5 (type g2gl-short-interval))
  (mini-tracing-step-size 10 (type mini-step-length-spec))
  (g2gl-activity-elbow-room 2 (type elbow-room-spec))
  ;; This accepts and can use any object subclass (an iconic entity). Consider
  ;; allowing and encouraging subclassing of thread-token for this purpose?
  (default-thread-token-class g2gl-standard-thread-token (type object-class))
  ;; The "color" is too simple; should probably be a color "spec", such that it
  ;; can include region patterns. (MHD 2/8/05)
  (default-thread-token-color coral (type color-or-metacolor))
  ;; Activity Object Icon Substitutions:
  (g2gl-object-icon-substitutions
    nil (type g2gl-object-icon-substitutions)))



;;; The `absent slot putter for g2gl-activity-icon-substitutions' exists because
;;; slot g2gl-activity-icon-substitutions on g2gl-parameters was renamed
;;; g2gl-object-icon-substitutions between 8.2a0 and 8.2r0, and expanded at this
;;; time to permit substitutions for any subclass of g2gl-object. (MHD 9/23/05)

(def-absent-slot-putter g2gl-activity-icon-substitutions (g2gl-object value)
  (setf (g2gl-object-icon-substitutions g2gl-object) value))



(def-grammar-list-category g2gl-object-icon-substitutions (g2gl-object-icon-substitution)
  :separator \; :conjunction nil :empty-list-symbol none)

(def-grammar-category g2gl-object-icon-substitution ()
  ((object-class                        ; later: g2gl-activity-class !!
     '\: object-class)
   (1 3)))

(def-slot-value-compiler g2gl-object-icon-substitutions (parse-result)
  (remove-noise-at-head-of-list-phrase parse-result))

(def-slot-value-writer g2gl-object-icon-substitutions (value)
  (if (null value)
      (tformat "none")
      (loop for (entry . more?) on value
            do (twrite-symbol (first entry))
               (tformat ": ")
               (twrite-symbol (second entry))
               (when more? (tformat "; ")))))

(def-slot-putter g2gl-object-icon-substitutions
    (g2gl-parameters-1 value initializing-p)
  (setf (g2gl-object-icon-substitutions g2gl-parameters-1) value)
  (unless initializing-p
    (when (system-table-installed-p g2gl-parameters-1)
      (reflect-g2gl-object-icon-substitutions)))
  value)


(def-class-method install-system-table (g2gl-parameters)
  (reflect-g2gl-object-icon-substitutions))

(def-class-method deinstall-system-table (g2gl-parameters)
  (revert-all-g2gl-object-icon-substitions))





;; Enforce acceptable values for these when they are edited!

(def-absent-slot-putter show-text-boxes-in-execution-displays (g value)
  (setf (compile-text-elements-in-source-for-execution-displays g) value))

(def-absent-slot-putter compile-texts-for-execution-displays (g value)
  (setf (compile-text-elements-in-source-for-execution-displays g) value))

;; The above slot name changes both happened post-8.1b0 (in the above order,
;; with several weeks in between), and apply to the g2gl-parameters system
;; table. (MHD 5/5/05)



(def-absent-slot-putter suppress-faults-on-missing-partner-link-variable-type
    (g2gl-params value)
  (setf (suppress-unspecified-partner-link-variable-type-faults g2gl-params) value))

;; This slot name change, done post 8.1b0, applies to the g2gl-parameters system
;; table. (MHD 4/12/05) -- originally put value in the slot named
;; suppress-faults-due-to-undetermined-port-type, but then that was renamed
;; again! -- see next form.... (MHD 5/5/05)


(def-absent-slot-putter suppress-faults-due-to-undetermined-port-type
    (g2gl-params value)
  (setf (suppress-unspecified-partner-link-variable-type-faults g2gl-params) value))

;; This change (again -- 2nd post-beta change to this slot/attribute name!),
;; done post 8.1b0, applies to the g2gl-parameters system table. (MHD 5/5/05)


;; Note: I'm changing the name of the system-table class from
;; g2-graphical-language-parameters to g2gl-parameters.  It's shorter, easier to
;; type, and sticks out less when you read it.  If you don't know what G2GL is,
;; it's less self-explanatory.  But G2GL is used all over, and we're trying to
;; brand G2GL further, so this approach fits in well.  A class substitution form
;; exists here for KBs saved in pre-beta versions created prior around
;; today. The substitution form can be removed just before or just after the
;; final release, or anytime in the future. (MHD 3/9/05)

;; For KBs saved pre-beta:

(def-substitute-for-old-class g2-graphical-language-parameters g2gl-parameters
  (+ g2-version-8-1-beta-0-kb-flags 1))



(def-grammar-category workspace-scale-float ()
  (float)
  (integer))                                ; 1, 2, 3, 4 only

(def-slot-value-compiler workspace-scale-float (parse-result)
  (when (integerp parse-result)
    (setq parse-result
          (make-phrase-float (coerce-to-gensym-float parse-result))))
  (cond
    ((not (phrase-float-p parse-result))
     (make-phrase-float 1.0))
    ((<e (phrase-float-value parse-result) .01)
     (make-phrase-float .01))
    ((>e (phrase-float-value parse-result) 4.0)
     (make-phrase-float 4.0))
    (t parse-result)))

(def-slot-value-writer workspace-scale-float (value)
  (tformat "~f" value))



;;; The grammar category `g2gl-short-interval' is for times that usually want
;;; range from a few 1000ths of a second to a few seconds.  The result is a
;;; single phrase float representing a number of seconds (likely to be
;;; fractional).  The category `g2gl-short-interval?' is similar, but supports
;;; NONE (internally nil) in addition to floats.

(def-grammar-category g2gl-short-interval ()
  ((float 'seconds) 1)
  ((positive-integer 'seconds) 1 coerce-phrase-number-to-float)
  ;; this case is really for the integer 1 only:
  ((positive-integer 'second) 1 coerce-phrase-number-to-float))

;; Note that in English you say "1.0 seconds" (plural), but "1 second", so we
;; don't have a grammar rule to permit "1.0 second", but "1 second": yes.

;; The compiler should probably enforce an acceptable-value limitation, both on
;; the max and the min!

(def-grammar-category g2gl-short-interval? ()
  ('none nil)
  (g2gl-short-interval))

(def-slot-value-writer g2gl-short-interval (value)
  (tformat "~f seconds" (slot-value-number-value value)))

(def-slot-value-writer g2gl-short-interval? (value frame)
  (if (null value)
      (tformat "none")
      (funcall
        (slot-value-writer 'g2gl-short-interval)
        value frame)))






(def-grammar-category mini-step-length-spec ()
  ;; Consdider using nothing, or "units", as in the "show action", meaning in
  ;; that case "window units".  Users might also want to specify window units, a
  ;; percentage, or even a blend. (MHD 12/8/04)
  ((positive-integer 'workspace 'units)))

(def-slot-value-compiler mini-step-length-spec (parse-result)
  (if (not (<f 0 (car parse-result) 10000)) ; arbitrarily high limit
      (values
        bad-phrase
        (copy-text-string
          "This must be a number of workspace units as a positive integer, less than 10000."))
      (car parse-result)))

(def-slot-value-writer mini-step-length-spec (value)
  (tformat "~d workspace units" value))


(def-grammar-category elbow-room-spec ()
  ((positive-integer 'workspace 'units)))

(def-slot-value-compiler elbow-room-spec (parse-result)
  (if (not (<=f 0 (car parse-result) 50))
      (values
        bad-phrase
        (copy-text-string
          "This must be a number of workspace units as a non-negative integer, 50 or less."))
      (car parse-result)))

(def-slot-value-writer elbow-room-spec (value)
  (tformat "~d workspace units" value))






;;; A `G2GL message' can either be a Web service message structure or
;;; (deprecated as of 8.3b0) an instance of g2gl-message.  In some cases
;;; (particularly in send-g2gl-message-transmission), NIL is also allowed, as
;;; the result of accessing an uninitialized message variable, which is
;;; considered equivalent to an empty message structure.

(def-concept g2gl-message)

(def-class (g2gl-message g2gl-object (foundation-class g2gl-message)
                         not-user-instantiable))


;;; The function `g2gl-message-attribute-value' returns the value of a named
;;; attribute in a G2GL message, or NIL if the message does not have that
;;; attribute.

(defun g2gl-message-attribute-value (m attr)
  (if (framep m)
      (when (attribute-of-class-p attr (class m))
        (get-slot-value m attr))
      (when m
        (evaluation-structure-slot m attr))))


;;; The function `clone-g2gl-message' creates a fresh copy of a G2GL message.
;;; The result is always either an evaluation structure or a transient and
;;; active frame.

(defun clone-g2gl-message (m)
  (cond ((framep m)
         (let ((clone (clone-frame m)))
           (set-transient-and-propagate clone nil)
           (funcall-method-macro 'activate-if-possible-and-propagate clone)
           clone))
        (m (copy-evaluation-structure m))
        (t (allocate-evaluation-structure nil))))

;; The code above is based on similar code in create-by-cloning-action-internal,
;; the G2 inference engine/procedure clone action function, q.v. Note:
;; previously, the (lone) caller just used to raw result of clone-frame,
;; resulting in bug HQ-5043296 "G2GL: g2gl-messages created by receive are
;; neither transient nor permanent". (MHD 6/24/05)



(def-class (g2gl-port-type-definition g2gl-object)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-outline . foreground)
                   (g2-icon-background . #.g2gl-icon-background-color)
                   (text-region . black))
       g2-icon-background #.g2gl-icon-rectangle-background
       g2-icon-outline #.g2gl-icon-rectangle-outline
       text-region
       (text #w"Port" (12 22) small)
       (text #w"Type" (10 40) small))))
  ;; a list of G2GL operation specs with distinct G2GL operation names:
  (port-type-api nil (type g2gl-operation-specs)))

;;; A G2GL operation spec, which specifies one of the operations of a G2GL port
;;; type, is a list consisting of a G2GL operation name, an input G2GL message
;;; type, possibly an output G2GL message type, and possibly a pair of a fault
;;; name and a fault G2GL message type.  The G2GL operation name is a symbol.
;;; The input G2GL message type is the type of G2GL message argument an invoke
;;; activity sends in an invocation of the operation.  An output G2GL message
;;; type, which is needed only for a two-way synchronous request/response
;;; invocation of the operation, is the type of G2GL message sent by a reply
;;; activity in response to an invocation of the operation.  The pair of a fault
;;; name and a fault G2GL message type is for use when a request/response
;;; invocation of the operation has an execution fault, and thus is useful only
;;; if there could be such request/response invocations.

(def-grammar-list-category g2gl-operation-specs (g2gl-operation-spec)
  :separator \; :conjunction nil :empty-list-symbol none)

(def-grammar-category g2gl-operation-spec ()
  ((g2gl-operation-name '\: 'input g2gl-message-class)
   (1 4))
  ((g2gl-operation-name '\: 'input g2gl-message-class '\,
                        'output g2gl-message-class)
   (1 4 7))
  ((g2gl-operation-name '\: 'input g2gl-message-class '\,
                        'output g2gl-message-class '\,
                        'fault g2gl-fault-name g2gl-message-class )
   (1 4 7 (10 . 11))))

(def-slot-value-compiler g2gl-operation-specs (parse-result)
  (remove-noise-at-head-of-list-phrase parse-result))

(def-slot-value-writer g2gl-operation-specs (value)
  (if (null value)
      (tformat "none")
      (loop for semi-p = nil then t
            for (op in-type out-type (fault-name . fault-type)) in value do
        (when semi-p (tformat "; "))
        (tformat "~(~a~): input ~a" op in-type)
        (when out-type
          (tformat ", output ~a" out-type)
          (when fault-name
            (tformat ", fault ~(~a~) ~a" fault-name fault-type))))))


(def-class (g2gl-partner-link-type-definition g2gl-object)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-outline . foreground)
                   (g2-icon-background . #.g2gl-icon-background-color)
                   (text-region . black))
       g2-icon-background #.g2gl-icon-rectangle-background
       g2-icon-outline #.g2gl-icon-rectangle-outline
       text-region
       (text #w"Partner" (2 22) small)
       (text #w"Link" (12 40) small))))
  ;; a list of one or two partnership port specs, where each partnership port
  ;; spec is either a G2GL port type (which in this case also serves as a role
  ;; name) or a pair of a role name (a symbol) and a G2GL port type, where order
  ;; is irrelevant in the case of two partnership port specs, and where separate
  ;; specification of a role name is necessary only in the unlikely situation
  ;; where the G2GL port type is the same for both partners.
  (partnership-port-specs nil (type g2gl-partnership-port-specs)))


(def-grammar-category g2gl-partnership-port-specs ()
  ('none nil)
  ;; otherwise, a list of 1 or 2 port specs:
  (g2gl-partnership-port-spec (1))
  ((g2gl-partnership-port-spec 'and g2gl-partnership-port-spec) (1 3)))


(def-grammar-category g2gl-partnership-port-spec ()
  (( 'port 'type g2gl-port-type '\, 'role 'name g2gl-role-name)
   (7 . 3))                                ; potential "SLOT-VALUE CDR PROBLEM!!!!"
  (('port 'type g2gl-port-type) 3))

(def-slot-value-compiler g2gl-partnership-port-specs (parse-result)
  parse-result)

(def-slot-value-writer g2gl-partnership-port-specs (value)
  (cond
    ((null value)
     (tformat "none"))
    ;; otherwise a list of 1 or 2 port specs
    (t
     (loop for (port-spec . more?) on value
           do (if (atom port-spec)
                  (tformat "port type ~a" port-spec)
                  (tformat "port type ~a, role name ~a"
                           (cdr port-spec) (car port-spec)))
              (when more?
                (tformat " and "))))))






;;;; Twriting Utilities


(defun twrite-symbol-or-none (symbol?)
  (twrite-symbol (or symbol? 'none)))

(defun twrite-symbol-or-string-or-none (symbol-or-string?)
  (if symbol-or-string?
      (let ((write-strings-parsably? t))
        (twrite-string symbol-or-string?))
      (twrite-symbol-or-none symbol-or-string?)))





;;;; Text Changing and Parsing Utilities



;;; The function `copy-g2gl-parse' copies parse, a parse tree, copying atoms
;;; that are wide strings or managed floats, and leaving other atoms alone, and
;;; copying list structure to all levels using gensym conses.

;;; The function `reclaim-g2gl-parse' reclaims parse, a parse tree, reclaiming
;;; wide strings and managed floats, and leaving any other atoms alone, and
;;; reclaiming list structure to all levels as gensym conses.

(defun copy-g2gl-parse (parse)
  (cond
    ((atom parse)
     (cond
       ((wide-string-p parse)
        (copy-wide-string parse))
       ((managed-float-p parse)
        (copy-managed-float parse))
       (t parse)))
    (t
     (gensym-cons
       (copy-g2gl-parse (car parse))
       (copy-g2gl-parse (cdr parse))))))


(defun reclaim-g2gl-parse (parse)
  (cond
    ((atom parse)
     (cond
       ((wide-string-p parse)
        (reclaim-wide-string parse))
       ((managed-float-p parse)
        (reclaim-managed-float parse))))
    (t
     (reclaim-g2gl-parse (car parse))
     (reclaim-g2gl-parse (cdr parse))
     (reclaim-gensym-cons parse))))





;;;; G2GL Time Primitives



;;; The macro `g2gl-get-current-time' gets the current time in unix time
;;; (floating point) format.  The result is a freshly consed gensym float.  This
;;; should be called in a temporary-gensym-float-creation context.

;;; The macro `g2gl-current-time->=' returns true if the current time is at or
;;; after the time supplied as an argument, which should be a gensym float.
;;; Otherwise, this returns nil. This should be called in a
;;; temporary-gensym-float-creation context.

;;; The macro `g2gl-current-time->=' returns true if the current time is before
;;; the time supplied as an argument, which should be a gensym float.
;;; Otherwise, this returns nil. This should be called in a
;;; temporary-gensym-float-creation context.

(defun-substitution-macro g2gl-get-current-time ()
  (gensym-get-unix-time))

(defun-substitution-macro g2gl-current-time->= (time)
  (>=e (g2gl-get-current-time) time))

(defun-substitution-macro g2gl-current-time-< (time)
  (<e (g2gl-get-current-time) time))





;;;; G2GL Execution Displays



;;; A `G2GL execution display' is a kind of temporary workspace used for tracing
;;; and breakpoint display during the execution of a G2GL process.  An activity
;;; flowchart, compiled from a a given source G2GL process, gets displayed here.
;;; A select set of menu choices and other UI features are also supplied.  This
;;; kind of workspace shows "proxy" blocks that are actually instances of item
;;; subclasses.  In the case of thread tokens, used to show the the progress of
;;; threads between activities on a flowchart, there may actually be instances
;;; of arbitrary user-defined subclasses of object.  There should be nothing the
;;; user can to disturb the layout or connectivity or existance of blocks on
;;; this workspace during its display.

;;; This class of workspace is very unusual in G2 in that it is a
;;; system-defined, non-item subclass that is always proprietary (with package
;;; PRIVATE), and with a built-in set of proprietary restrictions.  The
;;; proprietary restrictions restrict the set of commands to just those that can
;;; we want to feature and support, and not those that can disturb the smooth
;;; running of an execution display or impose undue burden on the implementation
;;; for extensive safety checking for things that have moved around or gone
;;; away.

(def-class (g2gl-execution-display temporary-workspace)

  ;; The object configuration slot restricts this as a proprietary workspace to
  ;; only allow a few select commands on G2GL activities, and just few on the
  ;; workspace itself.  In conjunction with this, we initialize
  ;; proprietary-package to PRIVATE below, making it a locked, proprietary
  ;; workspace.
  (object-configuration
    ((proprietary
       (workspace-menu
         (workspace) include
         move lift-to-top drop-to-bottom
         main-menu print-to-server print
         single-step do-not-single-step
         close-and-continue
         break-on-execution-faults
         do-not-break-on-execution-faults
         bring-up-source
         pause-process-instance resume-process-instance
         delete-process-instance
         process-display-attributes g2gl-system-attributes
         redo-layout-of-g2gl-body)
       (workspace-menu
         (item) include
         set-temporary-breakpoint remove-temporary-breakpoint)
       ;; remove the table menu for attribute displays:
       (table (item) nil include)
       ;; things prohibited:              gesture -> action
                                        ; -------    ------
       (pressing                        ; Return -> table
         #.(key-code 'return) nothing nil)
       (pressing                        ; Delete -> table
         #.(key-code 'delete) nothing nil)
       (clicking                        ; double-click -> table
         #.(logior
             double-bit
             (key-code 'mouse-select))
         nothing nil))))
  (proprietary-package private)

  (one-execution-thread-that-is-shown-hereon nil vector-slot)
  (execution-display-mode nil vector-slot)
  (temporary-breakpoints-for-execution-display nil vector-slot)
  (vector-of-g2gl-body-elements nil vector-slot))


;; Reclaimers are needed for the following slots that hold values that are not
;; normal slot values.  These are do-nothing reclaimers.  They avoid, in
;; development, a continuable error like "unknown thing ...".

(def-slot-value-reclaimer temporary-breakpoints-for-execution-display (value)
  (declare (ignore value)))

(def-slot-putter temporary-breakpoints-for-execution-display
    (g2gl-execution-display value initializing-p)
  (unless initializing-p
    (reclaim-slot-value-list
      (temporary-breakpoints-for-execution-display g2gl-execution-display)))
  (values
    (setf (temporary-breakpoints-for-execution-display g2gl-execution-display)
          value)
    t))                                        ; do not reclaim



(def-slot-value-reclaimer one-execution-thread-that-is-shown-hereon (value)
  (declare (ignore value)))

(def-slot-value-reclaimer vector-of-g2gl-body-elements (value)
  (declare (ignore value)))


(def-class-method cleanup (g2gl-execution-display)
  (funcall-superior-method g2gl-execution-display)
  (clean-up-for-deletion-of-execution-display g2gl-execution-display))




;;; The `slot-value-reclaimer for parent-execution-frames' on a
;;; g2gl-execution-display checks to see if this is serving as an execution
;;; display i.e., if the value argument, frames, in non-null.  If so, it calls
;;; remove-references-to-g2gl-execution-display, which, among other things,
;;; reclaims the top-level conses of frames.

(def-slot-value-reclaimer parent-execution-frames (frames g2gl-execution-display)
  (when frames
    (remove-references-to-g2gl-execution-display g2gl-execution-display)))


(defun remove-references-to-G2GL-execution-display (execution-display)
  execution-display
  ;; TBD!!
  )





;;; Delete-G2GL-execution-display (execution-display d):
;;;
;;; ... just delete d using G2's normal method for deleting a workspace (so that
;;; this procedure will be equivalent to a user's deleting d interactively
;;; through a GUI), which invokes
;;; clean-up-for-deletion-of-execution-display to perform use and reference
;;; "cleanup" as well as slot reclamation, prior to actually reclaiming d itself.

(defun delete-g2gl-execution-display (d)
  (delete-frame d))



;;; Clean-up-for-deletion-of-execution-display (execution-display d):

(defun clean-up-for-deletion-of-execution-display (d)
  (when (eq (execution-display-mode d) 'superimposed-tracings)
    (loop for execution-frame
              in (current-execution-frames
                   (parent-compilation-version
                     (parent-execution-frame
                       (one-execution-thread-that-is-shown-hereon d))))
          do (loop for related-thread
                       in (g2gl-execution-threads execution-frame)
                   when (memq d (g2gl-execution-displays related-thread))
                     ;; here, d should be the last element
                     do (setf (execution-display-for-superimposed-tracings
                                (body-compilation-this-is-being-used-to-execute
                                  related-thread))
                              nil)
                       ;; Note: this might be done multiple times
                        (remove-execution-display-from-thread related-thread d))))
  (when (not (eq (execution-display-mode d) 'superimposed-tracings))
    (loop for related-thread
              in (g2gl-execution-threads
                   (parent-execution-frame
                     (one-execution-thread-that-is-shown-hereon d)))
          when (memq d (g2gl-execution-displays related-thread))
            ;; here, d should be the first element
            do (remove-execution-display-from-thread related-thread d)
               (when (and (eq (execution-thread-state related-thread) 'at-breakpoint)
                          (not (eq (first (execution-thread-state-parameter
                                            related-thread))
                                   'ready-to-proceed))
                          ;; therefore, a breakpoint button on d
                          )
                 ;; this acts as if the user clicked on the button:
                 (handle-g2gl-breakpoint-button-click
                   (first (execution-thread-state-parameter related-thread))))))
  (progn
    (reclaim-slot-value-list
      (temporary-breakpoints-for-execution-display d))
    ;; not in spec, but to avoide double reclamation problems:
    (setf (temporary-breakpoints-for-execution-display d) nil))
  (reclaim-managed-array (vector-of-g2gl-body-elements d)))





;;;; G2GL Body Positions



;;; A `g2gl body position' is a representation of a position in a G2GL body or
;;; in an execution display. It may be either a small integer that encodes both
;;; the x and y coordinates or, where such a representation is not possible
;;; (because x or y has too great an absolute value), an x-y coordinate pair as
;;; a cons (allocated from the gensym-cons pool) of the form (x . y).

(def-concept g2gl-body-position)





;;;; G2GL Thread Tokens



;;; A `thread token' `g2gl-standard-thread-token' is used for animating
;;; execution threads.  The default thread-token class is
;;; `g2gl-standard-thread-token'.  A thread token's icon should be an
;;; equal-width/height, eye-catching, circular icon.  Subclasses should be
;;; equal-width/height as well, but in other colors and shapes.  In all cases,
;;; the item's size (width/height) should be fairly small.  At present, the
;;; default is a 24 width x 24 height filled circle in the color CORAL (a
;;; variant of orange), with a dark-gray outline.

;;; In addition, there should be a sizeable "simple" icon-color region, either
;;; named icon-color or with no name, such that changing the icon color (i.e.,
;;; changing the icon-color region) changes its main color.

;;; The class subclassable, with foundation class thread-token.  It is also
;;; instantiable. although instances should *generally* only be autocreated by
;;; the system for use on execution displays.  This generally should appear only
;;; on execution displays, in which case they are neither permanent nor
;;; transient, and don't appear to "exist" from the perspective of user code.
;;; (or, in the "hack" execution display case, not currently implemented, they
;;; would only be "transiently" (though in the neither-permanent-nor-transient
;;; state, not in the transient state) on a G2GL body subworkspace.)  We cannot
;;; really restrict users getting them by cloning and putting them elsewhere, so
;;; we don't need to use the class feature not-user-instantiable.

(def-concept thread-token)

(def-class (g2gl-standard-thread-token
             g2gl-object
             (foundation-class g2gl-standard-thread-token)
             do-not-put-in-menus)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      24 24
      ((polychrome
         (outer-circle . dark-gray)
         ;; The icon-color region is the inner circle. This is the region
         ;; controlled via the token color in G2GL-parameters:
         (icon-color . coral))
       (variables) (background-layer)
       outer-circle
       (filled-circle (0 12) (12 0) (24 12))
       icon-color                        ; inner circle
       (filled-circle (4 8) (8 4) (20 8)))
      nil nil nil nil nil nil)))

;; The spec also suggests perhaps having this blink.  If we ever have the
;; feature of icon/region blinking, consider using it here. (MHD 1/13/05)


(def-substitute-for-old-class thread-token g2gl-standard-thread-token
  (+ g2-version-8-1-beta-0-kb-flags 1))

;; The class thread-token was present in G2 8.1b0, and renamed
;; g2gl-standard-thread-token for 8.1r0.  The default init form for the
;; default-thread-token-class of g2gl-parameters was changed concurrently from
;; thread-token to g2gl-standard-thread-token. (MHD 4/19/05)





;;;; G2GL Breakpoint Buttons



;;; The class `g2gl-breakpoint-button' ... eye-catching...

(def-class (g2gl-breakpoint-button
             generic-action-button
             (attribute-displays
               ((breakpoint-button-text) at-standard-position)))
  (icon-description
    (:funcall-at-load-time
      create-action-button-description
      50 20 nil nil
      yellow black black))
  (breakpoint-button-execution-thread
    nil system vector-slot not-user-editable)
  (breakpoint-button-text                ; nil or a string
    "Breakpoint" (type whole-string? text)
    system vector-slot not-user-editable))

;; The spec also suggests perhaps having this blink.  If we ever have the
;; feature of icon/region blinking, consider using it here. (MHD 1/13/05)



;;; The reclaimer for the breakpoint-button-execution-thread of
;;; g2gl-breakpoint-button is custom.  The value can be a thread structure,
;;; which is a non-slot-value.  For now, this does nothing.

(def-slot-value-reclaimer breakpoint-button-execution-thread (value)
  (declare (ignore value)))

;; [To check: deal with reclamation elsewhere and/or later!  (MHD 1/21/05)]






;;;; G2GL Display Messages


;;; The class g2gl-display-message is a subclass of MESSAGE, used for displaying
;;; variable values next to variables on G2GL displays.

(def-class (g2gl-display-message
             message
             ;; internal class: instances should appear only on execution
             ;; displays, or, in the "hack" execution display case, only
             ;; transiently on a G2GL body subworkspace
             not-user-instantiable do-not-put-in-menus)
  (box-translation-and-text nil (type free text))
  (default-text-box-format-name
      borderless-free-text-format
      user-overridable))



;;;; G2GL Execution Display Titles

(def-class (g2gl-execution-display-title
             message
             ;; internal class: instances should appear only on execution
             ;; displays, or, in the "hack" execution display case, only
             ;; transiently on a G2GL body subworkspace
             not-user-instantiable do-not-put-in-menus)
  (box-translation-and-text nil (type free text))
  (default-text-box-format-name message-format user-overridable))





;;;; G2GL Process Instances



;;; A `process instance handle' is a unique cons.  Its car is the name of the
;;; process, if any, as of the time of the instantion of the process. The cdr
;;; may contain either nil or, if needed, a `process instance', an instance of
;;; the class g2gl-process-instance. The instance is a user-visible frame that
;;; maps directly to the G2GL execution frame corresponding to the process
;;; instance.
;;;
;;; To lower the overhead of maintaining process instance handles, the G2GL
;;; process instance data is not created until and unless it is needed (i.e.,
;;; implicitly requested) by the user.  This happens in one of the following
;;; situations:
;;;
;;;   (1) a call to system procedure g2-execute-g2gl-process;
;;;
;;;   (2) within a G2GL process, by evaluating the G2GL expression 'this process
;;;   instance'; or
;;;
;;;   (3) via a call to g2-collect-g2gl-process-instance-handles, which
;;;   allocates process instance data for every process instance.
;;;
;;; The class `g2gl-process-instance' has no attributes (user-visible slots).

(def-class (g2gl-process-instance
             g2gl-object
             ;; define g2gl-process-instance-p
             define-predicate
             not-user-instantiable do-not-put-in-menus)
  (g2gl-process-instance-execution-frame ; non-attribute
    nil vector-slot system do-not-save)
  (g2gl-process-instance-is-paused
    nil (type yes-or-no) system vector-slot))


(def-slot-putter g2gl-process-instance-is-paused (g2gl-process-instance value)
  (setf (g2gl-process-instance-is-paused g2gl-process-instance) value)
  (let ((f (g2gl-process-instance-execution-frame g2gl-process-instance)))
    (if value
        (pause-process-instance f)
        (resume-process-instance f)))
  value)



(def-class-method cleanup (g2gl-process-instance)
  (let ((f (g2gl-process-instance-execution-frame g2gl-process-instance)))
    (when f
      (setf (g2gl-process-instance-execution-frame g2gl-process-instance) nil)
      (when (g2gl-process-instance-handle f) ; nec.?
        (when (evaluation-item-reference-p
                (cdr (g2gl-process-instance-handle f)))
          (reclaim-evaluation-item-reference
            (cdr (g2gl-process-instance-handle f))))
        (reclaim-gensym-cons (g2gl-process-instance-handle f))
        (setf (g2gl-process-instance-handle f) nil))
      (exit-g2gl-process-instance f nil)))
  (funcall-superior-method g2gl-process-instance))





;;;; G2GL Variables



;;; A `G2GL variable' is an iconic object of class G2GL-variable in a G2GL body.
;;; The subclasses of a G2GL variable are: G2GL-arg-variable,
;;; G2GL-local-variable, G2GL-partner-link-variable, and
;;; G2GL-correlation-variable.  A G2GL variable has a G2GL variable name, a G2GL
;;; variable icon, a G2GL variable type, and possibly an initial constant value.
;;; The single required G2GL variable name of a G2GL variable is the value of
;;; its standard G2-object names attribute, which in this case is not included
;;; in any directory of names.

;;; G2GL variable type of a G2GL-arg-variable or a G2GL-local-variable may be
;;; the symbol general, integer, float, truth-value (meaning, in G2GL, true or
;;; false, but not any fuzzy truth value in between, such as ".8 true"), symbol,
;;; or text, a list of the form (class <class name>), or a G2GL message type.


;;; A `G2GL partner link variable' is a kind of G2GL variable that is specific
;;; to BPEL.  For G2GL per se, it is neither necessary nor recommended that the
;;; variable type be specified.  When it is specified, there are two options,
;;; represented as follows: (a) a list consisting of the symbol
;;; role-names-plus-partner-link-type, my role name or nil if none, the partner
;;; role name or nil if none, and a G2GL partner link type, or (b) a list
;;; consisting of the symbol port-types, the port type for this ("my") service
;;; endpoint or nil if none, and the port type for the partner service endpoint
;;; or nil if none.  The first option, the more complicated one, is based on the
;;; BPEL standard; note that the variable type in this case is not a G2GL
;;; partner link type, as one might suppose, but rather the combination of a
;;; G2GL partner link type and one or two role names that indicate which end of
;;; the partner link the variable value may represent.  Similarly, the value of
;;; a G2GL partner link variable is not a G2GL partner link, but rather nil
;;; until, if ever, it is set to a G2GL service port that represents the
;;; appropriate end of a G2GL partner link.  Once a G2GL partner link variable
;;; is set to a G2GL service port, it retains this value until it is unbound,
;;; which occurs when the body it is declared in terminates.  Note that G2GL
;;; partner link variables may be declared and thus bound in any G2GL body,
;;; though WS-BPEL allows it only in the top-level body of a process.


;;; A `G2GL correlation variable' is another kind of G2GL variable that is
;;; specific to BPEL.  The G2GL variable type for a G2GL correlation variable is
;;; a list consisting of the symbol conversation-key-attributes followed by the
;;; names of G2GL message attributes whose respective values must be the same in
;;; all messages belonging to a G2GL conversation (which therefore all contain
;;; the conversation key).  The value of a G2GL correlation variable is nil
;;; until, if ever, it is "late-bound" to a list consisting of a G2GL
;;; conversation key (which typically identifies the "subject" of the
;;; conversation) and possibly a series of G2GL operation names and G2GL
;;; messages that constitute a transcript of the conversation.  Note that a G2GL
;;; correlation variable is referred to in BPEL, rather confusingly, as a
;;; "correlation set"; a better term would be "correlation variable".

;;; The scope of a G2GL variable is the G2GL body (of a G2GL process or G2GL
;;; activity-with-body) in which it is located (declared) as well as all
;;; subordinate (enclosed) G2GL bodies thereof except where pre-empted by the
;;; declaration of another variable of the same name.




;;; The icons for the four instantiable classes of g2gl-variable have a distinct
;;; shape and background color, with a black equal sign (=) in the middle, and a
;;; black border.  They are all 20 by 20 rectangles, which makes them appear
;;; roughly 1.5 times the line height (of small text to be used alongside the
;;; icons).  The shapes and background colors each type of variable are as
;;; follows:
;;;
;;;   ARG:          square (light-steel-blue background)
;;;   LOCAL:        rounded-corner square (white background)
;;;   PARTNER-LINK: hexagon (light-pink background)
;;;   CORRELATION:  octagon (pale-green background)

;; The spec calls for this to be "the height of a line and a half of text".
;; This is slightly big given the height of "small" font (14 pt. helvetica), and
;; just about right for a line of "large" font (18 pt. helvetica), and slightly
;; small for a line of "extra large" font (24 pt. helvetica).  This is probably
;; OK.  Going smaller would probably make it hard to recognize the icon and
;; discern its shape as intended, especially at less than full size.  Review
;; with LH.  (MHD 10/28/04)

(def-class (g2gl-variable
             g2gl-object
             not-user-instantiable
             do-not-put-in-menus)
  ;; refine to suppress adding names to global name directory and to suppress
  ;; notes about multiple same-named instances:
  (name-or-names-for-frame nil (type name-or-names) local-name-or-names)
  (g2gl-variable-type general (type g2gl-type-specifier?))

  (default-value-for-g2gl-variable nil (type g2gl-variable-value?)))


(def-absent-slot-putter initial-value-for-g2gl-variable (v value)
  (setf (default-value-for-g2gl-variable v) value))

;; initial-value-for-g2gl-variable -> default-value-for-g2gl-variable for
;; g2gl-variable, post 8.1b0. (MHD 4/13/05)


(def-absent-slot-putter g2gl-partner-link-role-name-alist (v value)
  (declare (ignore v value))
  nil)

;; The g2gl-partner-link-role-name-alist slot on g2gl-variable was never used,
;; so I'm removing it.  -dougo, 7/11/07



(def-class (g2gl-arg-variable
             g2gl-variable)
  (icon-description                        ; square
    (:funcall-at-load-time
      create-icon-description
      20 20
      ((polychrome (light-steel-blue . light-steel-blue) (black . black))
       (variables)
       (background-layer)
       black
       (solid-rectangle (0 0) (20 20))
       light-steel-blue
       (solid-rectangle (3 3) (17 17))
       black
       (solid-rectangle (6 12) (14 14))
       (solid-rectangle (6 7) (14 9)))
      nil nil nil nil nil
      ((light-steel-blue 3 3 17 17) (black 0 0 20 20)))))

(def-class (g2gl-local-variable
             g2gl-variable)
  (icon-description                        ; rounded-corner square
    (:funcall-at-load-time
      create-icon-description
      20 20
      ((polychrome (white . white) (black . black))
       (variables)
       (background-layer)
       black
       (solid-rectangle (2 20) (18 17))
       (solid-rectangle (20 2) (16 18))
       (solid-rectangle (0 2) (4 18))
       (solid-rectangle (2 0) (18 4))
       (filled-circle (0 18) (2 16) (4 18))
       (filled-circle (16 18) (18 16) (20 18))
       (filled-circle (16 2) (18 0) (20 2))
       (filled-circle (0 2) (2 0) (4 2))
       white
       (filled-circle (3 16) (4 15) (5 16))
       (filled-circle (15 4) (16 3) (17 4))
       (filled-circle (15 16) (16 15) (17 16))
       (solid-rectangle (17 4) (15 16))
       (solid-rectangle (5 5) (15 17))
       (solid-rectangle (4 17) (16 16))
       (solid-rectangle (3 4) (5 16))
       (solid-rectangle (4 3) (16 5))
       (filled-circle (3 4) (4 3) (5 4))
       black
       (solid-rectangle (6 12) (14 14))
       (solid-rectangle (6 7) (14 9)))
      nil nil nil nil nil
      ((white 2 2 18 18) (black 0 0 20 20)))))




(def-class (g2gl-partner-link-variable
             g2gl-variable)
  (icon-description                        ; hexagonal shape
    (:funcall-at-load-time
      create-icon-description
      20 20
      ((polychrome (light-pink . light-pink) (black . black))
       (variables)
       (background-layer)
       black
       (filled-polygon
         ((20 6) (20 14) (10 20) (0 14) (0 6) (10 0))
         ((20 6) (20 14) (10 20))
         ((10 20) (0 14) (0 6))
         ((0 6) (10 0) (20 6))
         ((20 6) (10 20) (0 6)))
       light-pink
       (filled-polygon
         ((18 7) (18 13) (10 18) (2 13) (2 7) (10 2))
         ((18 7) (18 13) (10 18))
         ((10 18) (2 13) (2 7))
         ((2 7) (10 2) (18 7))
         ((18 7) (10 18) (2 7)))
       black
       (solid-rectangle (6 12) (14 14))
       (solid-rectangle (6 7) (14 9)))
      nil nil nil nil nil
      ((light-pink 2 2 18 18) (black 0 0 20 20))))
  ;; refinement of slot to default nil:
  (g2gl-variable-type nil (type g2gl-partner-link-variable-type?))
  ;; refinement to change the type:
  (default-value-for-g2gl-variable
      nil (type g2gl-partner-link-variable-default-value)))




;;; When the g2gl-variable-type of a partner link variable is specified, there
;;; are two options, represented as follows:
;;;
;;;   (a) a list consisting of the symbol role-names-plus-partner-link-type, my
;;;   role name or nil if none, the partner role name or nil if none, and a G2GL
;;;   partner link type, i.e.,:
;;;
;;;       (ROLE-NAMES-PLUS-PARTNER-LINK-TYPE
;;;           my-role-name? partner-role-name? partner-link-type)
;;;
;;;   or
;;;
;;;   (b) a list consisting of the symbol port-types, the port type for this
;;;   ("my") service endpoint or nil if none, and the port type for the partner
;;;   service endpoint or nil if none, i.e.:
;;;
;;;       (PORT-TYPES my-port-type? partner-port-type?)

(defun g2gl-partner-link-variable-type-p (proposed-type)
  (and (listp proposed-type)
       (memq (first proposed-type)
             '(role-names-plus-partner-link-type port-types))))

(def-grammar-category g2gl-partner-link-variable-type? ()
  ('unspecified nil)
  (g2gl-partner-link-variable-type))

(def-slot-value-compiler g2gl-partner-link-variable-type? (parse-result)
  parse-result)

(def-slot-value-writer g2gl-partner-link-variable-type? (value)
  (cond
    ((null value)
     (tformat "unspecified"))
    #+development
    ((not (g2gl-partner-link-variable-type-p value))
     (tformat
       "[invalid partner link variable type internal format: ~s]"
       value))
    ((eq (first value) 'role-names-plus-partner-link-type)
     ;; (ROLE-NAMES-PLUS-... my-rn? partner-rn? partner-lt)
     (tformat "~(partner link type = ~a with ~)" (fourth value))
     (when (second value)
       (tformat "~(my role = ~a~a~)"
                (second value)
                (if (third value) " and " "")))
     (when (third value)
        (tformat "~(partner role = ~a ~)" (third value))))
    (t
     ;; (PORT-TYPES my-port-type? partner-port-type?)
     (when (second value)
       (tformat "~(my port type = ~a~a~)"
                (second value)
                (if (third value) " and " "")))
     (when (third value)
       (tformat "~(partner port type = ~a~)" (third value))))))


(def-grammar-category g2gl-partner-link-variable-type ()
  (('partner 'link 'type '= g2gl-partner-link-type 'with 'my 'role '= g2gl-role-name)
   (role-names-plus-partner-link-type 10 nil 5))
  (('partner 'link 'type '= g2gl-partner-link-type 'with 'my 'role '= g2gl-role-name 'and 'partner 'role '= g2gl-role-name)
   (role-names-plus-partner-link-type 10 15 5))
  (('partner 'link 'type '= g2gl-partner-link-type 'with 'partner 'role '= g2gl-role-name)
   (role-names-plus-partner-link-type nil 10 5))

  (('my 'port 'type '= g2gl-port-type)
   (port-types 5 nil))
  (('my 'port 'type '= g2gl-port-type 'and 'partner 'port 'type '= g2gl-port-type)
   (port-types 5 11))
  (('partner 'port 'type '= g2gl-port-type)
   (port-types nil 5)))


(def-grammar-category g2gl-partner-link-type () (unreserved-symbol))
(def-registered-directory-of-names g2gl-partner-link-type)

(def-grammar-category g2gl-role-name () (unreserved-symbol))
(def-registered-directory-of-names g2gl-role-name)

(def-grammar-category g2gl-port-type () (unreserved-symbol))
(def-registered-directory-of-names g2gl-port-type)


;;; The slot type `g2gl-partner-link-variable-default-value' is either nil (for
;;; a non-remote partner link connection) or information needed to construct an
;;; endpoint reference.

(def-grammar-category g2gl-partner-link-variable-default-value ()
  ('local nil)
  (web-service-endpoint-reference))

(def-grammar-category web-service-endpoint-reference ()
  (('service-namespace '\: uri '\,
    'service-name '\: xml-ncname '\,
    'endpoint-name '\: xml-ncname)
   (3 7 11)))

(def-slot-value-writer g2gl-partner-link-variable-default-value (value)
  (if value
      (tformat "service-namespace: ~s, service-name: ~s, endpoint-name: ~s"
               (first value) (second value) (third value))
      (twrite "local")))




(def-class (g2gl-correlation-variable
             g2gl-variable)
  (icon-description                        ; octagonal shape
    (:funcall-at-load-time
      create-icon-description
      20 20
      ((polychrome (pale-green . pale-green) (black . black))
       (variables)
       (background-layer)
       black
       (filled-polygon
         ((14 0) (20 6) (20 14) (14 20) (6 20) (0 14) (0 6) (6 0))
         ((14 0) (20 6) (20 14))
         ((20 14) (14 20) (6 20))
         ((6 20) (0 14) (0 6))
         ((0 6) (6 0) (14 0))
         ((14 0) (20 14) (6 20))
         ((6 20) (0 6) (14 0)))
       pale-green
       (filled-polygon
         ((14 2) (18 6) (18 14) (14 18) (6 18) (2 14) (2 6) (6 2))
         ((14 2) (18 6) (18 14))
         ((18 14) (14 18) (6 18))
         ((6 18) (2 14) (2 6))
         ((2 6) (6 2) (14 2))
         ((14 2) (18 14) (6 18))
         ((6 18) (2 6) (14 2)))
       black
       (solid-rectangle (6 12) (14 14))
       (solid-rectangle (6 7) (14 9)))
      nil nil nil nil nil
      ((pale-green 2 2 18 18) (black 0 0 20 20))))
  ;; refinement of slot to default nil:
  (g2gl-variable-type nil (type g2gl-correlation-variable-type?))
  ;; refinement -- not available in table for this class:
  (default-value-for-g2gl-variable nil (type nil)))

;; Icons created in my (MHD's) private KB /home/mhd/kbs/bpel-icons.kb using G2
;; icon editor, then converted to Lisp using download-icons-from-current-kb in
;; development.  Consider maintaining the source KB, but probably it does not
;; have to be maintained.  If these want to edited, this can all be done anew,
;; or can be done by hand-editing the above sources. (MHD 10/30/04)



(def-substitute-for-old-class g2gl-conversation-variable g2gl-correlation-variable
  (+ g2-version-8-1-beta-0-kb-flags 1))

;; Note: class g2gl-conversation-variable => g2gl-correlation-variable today,
;; near end of 81b0 development.  Was in "Mar. 18 final, 2005" spec, but missed
;; until today. (MHD 3/31/05)




;;; The function `g2gl-correlation-variable-type-p' returns true iff
;;; `proposed-type' is a proper G2GL variable type for a correlation variable.

;;; "The G2GL variable type for a G2GL correlation variable is a list consisting
;;; of the symbol conversation-key-attributes followed by the names of G2GL
;;; message attributes..."

(defun g2gl-correlation-variable-type-p (proposed-type)
  (and (consp proposed-type)
       (eq (first proposed-type) 'conversation-key-attributes)))

(def-grammar-list-category g2gl-correlation-variable-type?
    (g2gl-message-attribute-name)
  :separator \, :conjunction nil :empty-list-symbol unspecified)

(def-slot-value-compiler g2gl-correlation-variable-type? (parse-result)
  (when parse-result
    (phrase-cons 'conversation-key-attributes
                 (remove-noise-at-head-of-list-phrase parse-result))))

(def-slot-value-writer g2gl-correlation-variable-type? (value)
  (tformat "~(~L,-~)" (or (if (consp value) (cdr value)) "unspecified")))

(def-grammar-category g2gl-message-attribute-name () (unreserved-symbol))
(def-registered-directory-of-names g2gl-message-attribute-name)




(eval-when (:compile-toplevel :load-toplevel :execute)
  ;; This eval-when hopefully enables using the operations at read time further
  ;; below. However, this may not work quite right in all Lisp implementations.

;;; `Map-g2gl-variable-class-to-code' maps from one of the built-in subclasses
;;; of g2gl-variable (including itself) to its "class code".
;;; `Map-g2gl-variable-code-to-class' maps from such a code to the corresponding
;;; build-in class.  Note that only valid and built-in classes are supported at
;;; this time. User-defined subclasses are not supported for these operations.

(defvar g2gl-variable 0)
(defvar g2gl-arg-variable 1)
(defvar g2gl-local-variable 2)
(defvar g2gl-partner-link-variable 3)
(defvar g2gl-correlation-variable 4)

(defun-substitution-macro map-g2gl-variable-class-to-code (class)
  (symbol-value class))

(defmacro quoted-g2gl-variable-class-code (quoted-g2gl-variable-subclass)
  (when (and (consp quoted-g2gl-variable-subclass)
             (eq (car quoted-g2gl-variable-subclass) 'quote))
    (cerror "continue anyway"
            "The arg  (~s) to quoted-g2gl-variable-class-code should NOT be quoted."
            quoted-g2gl-variable-subclass))
  `(map-g2gl-variable-class-to-code ',quoted-g2gl-variable-subclass))

(defun-substitution-macro map-g2gl-variable-code-to-class (code)
  (svref '#(g2gl-variable                ; 0
            g2gl-arg-variable                ; 1
            g2gl-local-variable                ; 2
            g2gl-partner-link-variable        ; 3
            g2gl-correlation-variable)        ; 4
         (the fixnum code)))
)  ; end (eval-when ....)




(def-class (g2gl-variable-compilation g2gl-object
                                      do-not-put-in-menus)
  (g2gl-var-body-element-position 0 save)
  (g2gl-var-body-element-index -1 (type integer)) ; must get filled in w/non-neg. int. or
                                        ;   nil for a proxy variable compilation
  (hack-reference-to-g2gl-variable nil save)     ; nil for a proxy variable compilation
  (g2gl-variable-class-code 0 (type integer) vector-slot)
  (c-g2gl-variable-name nil (type name-or-names) local-name-or-names vector-slot)
  (c-g2gl-variable-type nil save vector-slot)    ; atom or tree
  (c-default-value-for-g2gl-variable nil (type g2gl-variable-value?))
  (g2gl-variable-index nil (type integer) vector-slot))

(def-slot-value-reclaimer c-g2gl-variable-name (slot-value) slot-value)
(def-slot-value-reclaimer c-g2gl-variable-type (slot-value) slot-value)
(def-slot-value-reclaimer c-default-value-for-g2gl-variable (slot-value) slot-value)

(defun make-g2gl-variable-compilation ()
  (make-frame 'g2gl-variable-compilation))

(defun g2gl-variable-compilation-p (x)
  (of-class-p x 'g2gl-variable-compilation))

(defun reclaim-g2gl-variable-compilation (vc)
  ;; set all slots to nil
  (setf (g2gl-var-body-element-position vc) nil)
  (setf (g2gl-var-body-element-index vc) nil)
  (setf (hack-reference-to-g2gl-variable vc) nil)
  (setf (g2gl-variable-class-code vc) nil)
  (setf (c-g2gl-variable-name vc) nil)
  (setf (c-g2gl-variable-type vc) nil)
  (setf (c-default-value-for-g2gl-variable vc) nil)
  (setf (g2gl-variable-index vc) nil)
      
  ;; delete variable compilation
  (delete-frame vc))


;;;; Miscellany: g2gl-process, g2gl-standard-connection, and
;;;; g2gl-link-connection



; (def-class (ws-bpel-process g2gl-process))
(def-substitute-for-old-class ws-bpel-process g2gl-process
  (+ g2-version-8-1-beta-0-kb-flags 1))


;(def-class (g2gl-procedure g2gl-process))
(def-substitute-for-old-class g2gl-procedure g2gl-process
  (+ g2-version-8-1-beta-0-kb-flags 1))


(defparameter g2gl-standard-connection-class 'g2gl-standard-connection)

(def-class (g2gl-standard-connection connection do-not-put-in-menus)
  (cross-section-pattern ((black . 2)) system save))

(def-class (g2gl-link-connection connection do-not-put-in-menus)
  (cross-section-pattern ((black . 2)) system save))

(def-substitute-for-old-class bpel-process g2gl-process
  (+ g2-version-8-1-beta-0-kb-flags 1))

(def-substitute-for-old-class bpel-link-connection g2gl-link-connection
  (+ g2-version-8-1-beta-0-kb-flags 1))





;;;; Defining G2GL Activities



;;; The macro `def-g2gl-activity' is of the form
;;;
;;;   (DEF-G2GL-ACTIVITY (class-name superior-class activity-class-code . options)
;;;      icon-description
;;;      ( { g2gl-activity-slot-description } )
;;;      { implementation-piece } )
;;;
;;; where
;;;
;;;   class-name is one of the G2GL activity names (g2gl-invoke, g2gl-wait, etc.)
;;;
;;;   superior-class is an appropriate class (e.g., g2gl-activity or g2gl-scope)
;;;
;;;   activity-class-code - the small-integer code associated with the class
;;;     (see below)
;;;
;;;   options - any of the standard class features for def-class, but note:
;;;
;;;       standard stubs are added: STUBS here overrides them;
;;;
;;;     plus these special features:
;;;
;;;       additional-stubs - stubs to be added to standard set;
;;;
;;;       connections-configuration - ... (see spec!)
;;;
;;;   icon-description is a slot-init form that produces an icon description
;;;
;;;   g2gl-activity-slot-description is of the form
;;;
;;;     (slot-name proxy-name ( { activity-slot-option } ) { slot-feature })
;;;
;;;   where
;;;
;;;     slot-name is the name for the slot in the corresponding class
;;;     definition;
;;;
;;;      proxy-name is the name used to refer to the slot in the code of an
;;;      implementation piece (see below);
;;;
;;;      activity-slot-option is one of the following, with meanings as shown:
;;;
;;;      A-ONLY - define for the activity (class def.) only, no structure slot
;;;      defined
;;;
;;;      C-ONLY - for the compilation (structure) only, no "mangling" of the
;;;      name (see below)
;;;
;;;      LOOKUP-SLOT - declare slot a lookup slot in the class definition
;;;
;;;      CARRIED-OVER-TO-C - sets the corresponding slot in the activity
;;;      compilation to point to the same value as its corresponding slot in the
;;;      frame; note: doesn't really copy any allocated structure, just "copies"
;;;      the pointer.  (Normally used for fixnums, symbols, and other such
;;;      "immediates".)  NOTE: this happens upon creation of the compilation,
;;;      not upon compilation.
;;;
;;;      RECLAIMABLE - sufficient to reclaim the top-level conses, but OK to
;;;      reclaim any conses and any strings in the entire tree (i.e., reclaim
;;;      just the top-level conses)
;;;
;;;      RECLAIMABLE-AT-BOTH-LEVELS - sufficient to reclaim the top two levels
;;;      of conses, but OK to reclaim any conses and any strings in the entire
;;;      tree (i.e., reclaim top-level conses and also any cons that's the CAR
;;;      of any top-level cons cell)
;;;
;;;      INTEGER - type is fixnum (integer) (initialized to 0)
;;;
;;;      SYMBOL - type is symbol (initialized to nil)
;;;
;;;      FLAG - type is (member t nil) (i.e., boolean) (initialized to nil)
;;;           - assumed to be an attribute slot, and the slot type feature will
;;;             be (type yes-or-no)
;;;
;;;      (INITIAL-VALUE <initial slot value spec>) - as for slot definition
;;;
;;;
;;;      REQUIRED-NON-NIL-VALUE - for an attribute slot that is required to have
;;;      a non-nil value; code is generated to check for this and produce a
;;;      user-level complaint if this is not the case during compilation (note:
;;;      required-non-nil-value is sometimes called REQUIRED-FOR-COMPILATION in
;;;      the spec; they're meant to be the same thing)
;;;
;;;      SPECIAL-CONNECTIONS - ...
;;;
;;;    slot-feature is a slot feature as defined for a slot definition (of a
;;;    class definition)
;;;
;;;    implementation-piece is of the form
;;;
;;;      (code-type . code)
;;;
;;;    where
;;;
;;;      code-type is one of the following:
;;;
;;;        EXPRESSION-EXTRACTION-CODE - ...
;;;
;;;        ACTIVITY-EXPANSION-CODE - ...
;;;
;;;        ACTIVITY-EXECUTION-CODE - ...
;;;
;;;        ACTIVITY-COMPILATION-CODE - ...
;;;
;;;      code is a list of lisp expressions, which will ultimately be expanded
;;;      into code that needs the corresponding code type (using expansion
;;;      operations ... [to be defined later!] ).  The code is Lisp-like, except
;;;      that it may refer to proxy names and use certain special forms in
;;;      function positions, which are later expanded into other Lisp forms and
;;;      accessors.
;;;
;;;      Specifically, for each proxy-name defined, any reference to such a
;;;      name, except in the set-acs special form (see below) gets expanded into
;;;      an (accessor instance) reference in the code, where instance is a
;;;      frame, an instance of the class, and where accessor is the frame slot
;;;      accessor.
;;;
;;;      During compilation proxy names are predefined and may be used freely
;;;      throughout code.  They are:
;;;
;;;         a - the G2GL activity being compiled
;;;         b - the body compialtion for the g2gl body in which a is a body element
;;;         c - the corresponding and already partly-filled-in G2GL activity compilation
;;;         v - the compilation version parent of a
;;;
;;;      And also the following common activity compilation slots can be set,
;;;      i.e., using (setf (<slot name> c) ...), in code.
;;;
;;;
;;;        g2gl-activity-class-code
;;;        g2gl-activity-name
;;;        activity-compilation-successors
;;;        body-snapshot-index-for-G2GL-activity
;;;        g2gl-expression-compilation
;;;
;;;      During execution the predefined proxy names are:
;;;
;;;       c, the activity compilation to execute or try to execute
;;;
;;;       c-successors, the activity-compilation-successors of c
;;;
;;;       expression-value, the just-obtained-by-execution value of the
;;;       G2GL-expression-compilation of c, or nil if there is no such
;;;       expression compilation (that is, if the G2GL-expression-compilation of
;;;       c is nil)
;;;
;;;       thread, the currently active execution thread being used in the
;;;       execution of c
;;;
;;;       parent-thread, the parent-execution-thread of thread, which is nil if
;;;       thread is being used to execute the top-level body compilation of the
;;;       G2GL process
;;;
;;;       f, the parent-execution-frame of thread, that is, the G2GL execution
;;;       frame for the G2GL process instance being executed
;;;
;;;       execution-displays, the G2GL-execution-displays of thread, that is,
;;;       the G2GL execution displays for the
;;;       body-compilation-this-is-being-used-to-execute of thread, usually nil
;;;
;;; An important convention/assumption: slot names may be identical between
;;; disjoint g2gl activity subclasses as long as they are defined in same order
;;; following other vector slots.  I.e., it may be relied on that they will get
;;; assigned vector slot indexes and structure slot indexes strictly according
;;; to their order.  This happens to be the way frames and structures are
;;; defined, and we are relying upon this for for efficiency and ease of
;;; implementation.
;;;
;;; Slot name mangling: if a slot is defined for both the activity class and
;;; corresponding compilation, then the compilation slot will have the prefix
;;; "C-" prepended.  If a slot is A-ONLY, then no structure slot will be
;;; defined.  If a slot is C-ONLY, then the supplied slot name will be used as
;;; is.
;;;
;;; Note that we do NOT intend for the activity subclasses to be defined or
;;; refined, by users or by the system, and this implementation does not
;;; particularly lend itself to that.  (Besides the slot definition assumption
;;; just noted, the use of EQ and CASE to dispatch on classes, as opposed to,
;;; say, SUBCLASSP or CLASS-CASE, does not lend itself to extensibility.  Again,
;;; this approach is taken for efficiency combined with simplicity.
;;;
;;;      The special forms that may be used are:
;;;
;;;         (SET-ACS proxy-name value) - this expands into a setf of the
;;;         compilation structure slot accessor on the compilation structure,
;;;         setting its value.
;;;
;;; Activity class codes: to support fast numeric g2gl-activity-class-specific
;;; case statement dispatching in the activity execution engine, we assign codes
;;; to activity names, and have a very fast way to map from names to codes and
;;; back.  The name to code mapping is done using the value cell of the class
;;; name. That is, the class name is declared as a global variable, and its
;;; value is assigned to the code.  The reverse mapping is done via a small
;;; vector where the codes index into the vector, and the value of the element
;;; at that location is the symbol that's the name of the class.  Note that this
;;; approach results in the obvious limitation that the class names cannot be
;;; used for other purposes.

(eval-when (:compile-toplevel :load-toplevel :execute)

;;; The constant `max-activity-class-code' is currently 29 (it can grow upwards
;;; as new activities are defined via def-g2gl-activity).  The variable
;;; `activity-class-code-vector' holds a simple vector, of length
;;; max-activity-class-code + 1.  Each element except element 0 is set up to
;;; have a class corresponding to the code that is the index of that element.
;;; The code 0 is reserved.  Element 0 in the vector is set to the value of the
;;; constant `substitute-for-non-activity-class', which is defined as the symbol
;;; G2GL-EMPTY.  This code is used in the flowchart-activity compiler for the
;;; case of a non-activity (or unrecognized activity).  The constant
;;; `non-activity-class-code' is 0, and may be used to represent this case,
;;; i.e., for mapping from any non-g2gl-activity class to a code.

(defconstant substitute-for-non-activity-class 'g2gl-empty)
(defconstant non-activity-class-code 0)
(defconstant max-activity-class-code 30)

(defvar activity-class-code-vector
  (let ((a (make-array (+ max-activity-class-code 1))))
    ;; Element 0 must be initialized; others may be irrelevant/garbage at this
    ;; point, to be filled in via def-g2gl-activity calls.
    (setf (svref a 0) substitute-for-non-activity-class)
    a))

(defun check-def-g2gl-activity--vector-slot-conflicts (slots) ; -for-macro?
  slots)                                ; ignore for now!


(defmacro def-g2gl-activity ((class-name superior-class activity-class-code
                                         &rest options)
                             icon-description
                             g2gl-activity-slot-definitions
                             &rest implementation-pieces)
  (let* ((activity-compilation-structure-type
           (build-ab-symbol class-name 'activity-compilation))
         ;; note: we assume class-name is of the form G2GL-<activity name>
         (activity-name
           (build-ab-symbol
             (subseq (string class-name) (length "G2GL-"))))
         (remaining-options nil)
         (connections-configuration-feature
           (let ((config (assq 'connections-configuration options)))
             (if config
                 (prog1 config
                   (setq options (delq config options))))))
         (stubs nil)
         (slots
           (loop for (slot-name proxy-name options . slot-features)
                     in g2gl-activity-slot-definitions
                 as lookup-slot-p = (memq 'lookup-slot options)
                 as c-only-p = (memq 'c-only options)
                 as a-only-p = (memq 'a-only options)
                 collect ;; (proxy-name a-slot? c-slot? options . slot-features)
                 `(,proxy-name
                     ,(if (not c-only-p) slot-name)
                     ,(if (not a-only-p)
                          (if c-only-p
                              slot-name
                              (build-ab-symbol 'c slot-name)))
                     ,options
                     ,@slot-features)))
         (slot-definitions
           (loop for (proxy-name a-slot? c-slot? options . slot-features)
                     in slots
                 as lookup-slot-p = (memq 'lookup-slot options)
                 as initial-value-spec?
                    = (loop for x in options
                            when (and (consp x) (eq (car x) 'initial-value))
                              return x)
                 when a-slot?
                   collect `(,a-slot?
                               ,(if initial-value-spec?
                                    (second initial-value-spec?)
                                    nil)
                               ,(if lookup-slot-p 'lookup-slot 'vector-slot)
                               ,@(if (null (assq 'type slot-features))
                                     (cond
                                       ((memq 'flag options)
                                        '((type yes-or-no)))
                                       ;; other built-in type features?
                                       ))
                               ,@slot-features)))
         (activity-compilation-slots
           (loop for (proxy-name a-slot? c-slot? options . slot-features)
                     in slots
                 when c-slot?
                   collect `(,c-slot? nil))))
    ;; Test here for structure slot and vector slot conflicts: the idea to allow
    ;; under controlled conditions for vector slots in disjoint classes
    ;; subclasses g2gl-activity to have the same slot name and accessor
    ;; (setter/getter) macros, and similarly to allow corresponding structure
    ;; slots to have the same names.  The restriction is that for this to work,
    ;; the underlying vector index must be the same for each class or structure
    ;; type.  To test for that, we make sure all names that are duplicated
    ;; between definitions appear in the same order, and the same number of
    ;; positions from the beginning of the list of slot names. This test is only
    ;; done at macroexpansion time.
    (check-def-g2gl-activity--vector-slot-conflicts slots)
    `(progn
       (defvar ,class-name ,activity-class-code)
       (setf (svref activity-class-code-vector ,activity-class-code)
             ',class-name)
       (def-class (,class-name
                     ,superior-class
                     ,@(multiple-value-setq (stubs remaining-options)
                         (let* ((stubs (assq 'stubs options)) ; null CDR => no stubs
                                (additional-stubs
                                  (cdr (assq 'additional-stubs options)))
                                (horizontal-midline
                                  (halfw (g2gl-label-icon-area activity-name)))
                                (standard-stubs
                                  `(stubs
                                     ,(g2gl-standard-connection-stub
                                        'input 'top horizontal-midline)
                                     ,(g2gl-standard-connection-stub
                                        'output 'bottom horizontal-midline))))
                           ;; remove options we handle ourselves:
                           (loop for opt in '(stubs additional-stubs superior-class)
                                 do (setq options                ; changes arg
                                          (remove
                                            opt options
                                            :test #'(lambda (x y) (eq x (car y))))))
                           (values
                             (if (or stubs standard-stubs)
                                 (list
                                   (append
                                     (or stubs standard-stubs)
                                     additional-stubs)))
                             options)))
                     ,@remaining-options)
         (icon-description ,icon-description)
         (g2-bpel-activity-name ,activity-name)
         (g2gl-connections-configuration-feature ,connections-configuration-feature)
         ,@slot-definitions)
       (def-structure (,activity-compilation-structure-type
                         (:include g2gl-activity-compilation)
                         ;; no type needed except in development: later, to save a
                         ;; word per instance, add something like this:
                         ;; #-development (:unnamed t)
;                         (:reclaimer nil)
                         )
         ,@activity-compilation-slots)

       ;; convert structure to list
       (defun ,(build-ab-symbol activity-compilation-structure-type 'to-list)
            (activity-compilation-structure options)
          (gensym-list
             ;; class code
             (g2gl-activity-class-code activity-compilation-structure)
             ;; g2gl-activity-compilation fields
             (g2gl-activity-compilation-to-list activity-compilation-structure options)
             ;; g2gl-activity-compilation-structure fields
            ,@(loop for (slot-name nil) in activity-compilation-slots
               collect `(,slot-name activity-compilation-structure))))

       ;; load structure from list
       (defun ,(build-ab-symbol 'make activity-compilation-structure-type 'from-list)
            (fields options)
          (let* ((activity-compilation-structure
                    (,(build-ab-symbol 'make activity-compilation-structure-type)))
                 field ac)

                ; add to list
                (gensym-push activity-compilation-structure (activity-compilations-list options))
                (incff (activity-compilations-count options))

                (setf ac (make-g2gl-activity-compilation-from-list (second fields) options))
                (setf field (cddr fields))

            ;; copy g2gl-activity-compilation fields
             ,@(loop for ac-slot-name in '(g2gl-body-element-position
                                           g2gl-body-element-index
                                           g2gl-activity-class-code
                                           g2gl-activity-name
                                           g2gl-attribute-display-compilations
                                           activity-compilation-successors
                                           g2gl-expression-compilation
                                           g2gl-body-compilation)
                     collect `(progn
                                 (setf (,ac-slot-name activity-compilation-structure)
                                      (,ac-slot-name ac))
                                (setf (,ac-slot-name ac) nil)))

             ;; copy g2gl-activity-compilation-structure fields
            ,@(loop for (slot-name nil) in activity-compilation-slots
               collect `(progn
                          (setf (,slot-name activity-compilation-structure) (car field))
                          (setf field (cdr field))))
            
            (reclaim-g2gl-activity-compilation ac)
            
            activity-compilation-structure))

       ;; maintain dummy before/after functions for debugging in development;
       ;; see use in aggregate-g2gl-activity-execution-code.
       #+development
       (progn
         (defun ,(build-ab-symbol 'before class-name 'execution)
             (c c-successors expression-value thread parent-thread f execution-displays)
           c c-successors expression-value thread parent-thread f execution-displays)
         (defun ,(build-ab-symbol 'after class-name 'execution)
             (c c-successors expression-value thread parent-thread f execution-displays)
           c c-successors expression-value thread parent-thread f execution-displays))

       (let ((entry
               (or (assq ',class-name g2gl-activity-implementations-alist)
                   (let ((new (gensym-cons ',class-name nil)))
                     (push new g2gl-activity-implementations-alist)
                     new))))
         (setf (cdr entry) (list ',slots ',implementation-pieces)))
       ',class-name)))




(defun-for-macro get-g2gl-activity-slot-definitions (class-name g2gl-activity-slot-definitions)
  (loop for (slot-name proxy-name options . slot-features)
            in g2gl-activity-slot-definitions
        as lookup-slot-p = (memq 'lookup-slot options)
        as c-only-p = (memq 'c-only options)
        unless c-only-p
          collect `(,(build-ab-symbol class-name slot-name)
                     nil
                     ,(if lookup-slot-p 'lookup-slot 'vector-slot)
                     . ,slot-features)))

(defun-for-macro get-g2gl-activity-compilation-slots (class-name g2gl-activity-slot-definitions)
  (loop for (slot-name proxy-name options)
            in g2gl-activity-slot-definitions
        as a-only-p = (memq 'a-only options)
        unless a-only-p
          collect `(,(build-ab-symbol 'c class-name slot-name)
                     nil)))

(defvar g2gl-activity-implementations-alist nil)




;;; The macro `aggregate-g2gl-activity-compilation-code' emits custom
;;; compilation code defined for all G2GL activities.  Note that this does not
;;; exclude certain non-custom compilation steps, namely required-non-nil-value
;;; and carried-over-to-c, which are included in the creation code; see
;;; aggregate-g2gl-activity-compilation-creation-code.

(defmacro aggregate-g2gl-activity-compilation-code ()
  (when (null g2gl-activity-implementations-alist)
    (warn "**** g2gl-activity-implementations-alist is nil; something's wrong! ****"))
  `(case (class a)
     ,@(loop for (class-name slots implementation-pieces)
                 in g2gl-activity-implementations-alist
             as code = (subst-proxy-names-in-g2gl-activity
                         class-name
                         slots
                         (cdr (assq
                                'activity-compilation-code
                                implementation-pieces))
                         t)
             collect `((,class-name)
                       ,@code))))





(defmacro aggregate-g2gl-activity-execution-code ()
  `(fixnum-case (g2gl-activity-class-code c)
     ,@(loop for (class-name slots implementation-pieces)
                 in g2gl-activity-implementations-alist
             as code = (subst-proxy-names-in-g2gl-activity
                         class-name
                         slots
                         (cdr (assq
                                'activity-execution-code
                                implementation-pieces))
                         nil)
             collect `((,(map-g2gl-activity-class-to-code class-name)
                         ,@(if (eq class-name substitute-for-non-activity-class)
                               `(,non-activity-class-code)))
                       ;; have the name sitting around, handy for debugging
                       #+development ',class-name
                       ;; Call before and after dummy functions (defined in
                       ;; def-g2gl-activity) before and after the code, in
                       ;; development for debugging, so you can trace them or
                       ;; break on them to see the state of various things.
                       #+development
                       (,(build-ab-symbol 'before class-name 'execution)
                         c c-successors expression-value thread parent-thread
                         f execution-displays)
                       ,@code
                       #+development
                       (,(build-ab-symbol 'after class-name 'execution)
                         c c-successors expression-value thread parent-thread
                         f execution-displays)))))




;;; The function subst-proxy-names-in-g2gl-activity is invoked when code is
;;; aggregated for compilation or execution, i.e., by either
;;; aggregate-g2gl-activity-compilation-code or
;;; aggregate-g2gl-activity-execution-code.  This substitutes free references to
;;; proxy names with code of the form (<a-name> a), and substitutes forms of the
;;; form (set-acs proxy-name ...) with code of the form (setf (<c-name> c) ...).
;;;
;;; The a-name or c-name come from proxy-names-and-slots, which is of the form:
;;;
;;;   ( { (proxy-name a-slot? c-slot?) } )
;;;
;;; where a-slot? and c-slot? can be nil or an activity- or
;;; compilation-structure-slot, respectively.
;;;
;;; This checks for two kinds of problems with SET-ACS forms: (1) malformed
;;; (wrong number of elements in form, or wrong list structure) and (2) no
;;; c-slot corresponding to proxy name.  It can report these as, for example,
;;; in following respective error messages:
;;;
;;;    Warning: Activity G2GL-INVOKE: no C-Slot for proxy UNKNOWN used in this form:
;;;             (SET-ACS UNKNOWN FOO)
;;;
;;;    Warning: Activity G2GL-INVOKE: probable malformed SET-ACS form -- too many args:
;;;             (SET-ACS OPERATION-SPEC FOO BAR BAZ BLECH)


(defun subst-proxy-names-in-g2gl-activity ; -for-macro?
    (activity proxy-names-and-slots code compilation-case-p)
  ;; proxy-names-and-slots: ( { (proxy-name a-slot? c-slot?) } )
  (cond
    ((atom code)
     (let ((entry? (assq code proxy-names-and-slots)))
       (or (if compilation-case-p
               (if (second entry?) `(,(second entry?) a))
               (if (third entry?) `(,(third entry?) c)))
           code)))
    ((eq (first code) 'set-acs)
     (cond
       ((not compilation-case-p)
        (warn
          "Activity ~a: SET-ACS form in non-compilation code not allowed -- ignoring form:~% ~s"
          activity code))
       (t
        (if (and                                ; check for 3-long list
              (consp (cdr code))
              (consp (cddr code))
              (null (cdddr code)))
            (let ((entry? (assq (second code) proxy-names-and-slots)))
              (if (and entry? (third entry?))
                  `(setf (,(third entry?) c)
                         ,(subst-proxy-names-in-g2gl-activity
                            activity proxy-names-and-slots (third code)
                            compilation-case-p))
                  (progn
                    (warn
                      "Activity ~a: no C-Slot for proxy ~a used in this form:~%  ~s"
                      activity (second code) code)
                    nil)))
            (progn
              (warn
                "Activity ~a: probable malformed SET-ACS form -- too many args:~%  ~s"
                activity code)
              nil)))))
    (t
     (cons
       (subst-proxy-names-in-g2gl-activity
         activity proxy-names-and-slots (car code) compilation-case-p)
       (subst-proxy-names-in-g2gl-activity
         activity proxy-names-and-slots (cdr code) compilation-case-p)))))



;; Development-only function mexp-define-g2gl-activity-compiler pretty prints a
;; nice-looking macroexpansion of
;;
;;   (define-g2gl-activity-compiler)

#+development
(defun mexp-define-g2gl-activity-compiler ()
  (let* ((*print-length* 500)
         (*print-level* 50)
         (output-string
           (with-output-to-string (out-stream)
             (pprint
               (macroexpand '(define-g2gl-activity-compiler))
               out-stream))))
    (format t "~%~(~a~)" output-string)))





(defmacro aggregate-g2gl-activity-reclamation-code ()
  (when (null g2gl-activity-implementations-alist)
    (warn "**** g2gl-activity-implementations-alist is nil; something's wrong! ****"))
  `(if (null (g2gl-activity-class-code c))
       nil
       (fixnum-case (g2gl-activity-class-code c)
         ,@(loop for (class-name slots implementation-pieces)
                     in g2gl-activity-implementations-alist
                 as custom-reclamation-code
                    = (loop for (proxy-name a-slot? c-slot? options)
                                in slots
                            as listed-form?
                               = (if c-slot?
                                     (cond
                                       ((memq
                                          'reclaimable-at-both-levels
                                          options)
                                        `((setf (,c-slot? c)
                                                (prog1 nil
                                                  (loop for x in (,c-slot? c)
                                                        do (if (consp x)
                                                               (reclaim-gensym-cons x)))
                                                  (reclaim-gensym-list (,c-slot? c))))))
                                       ((memq
                                          'reclaimable
                                          options)
                                        `((setf (,c-slot? c)
                                                (prog1 nil
                                                  (reclaim-gensym-list
                                                    (,c-slot? c))))))))
                            append listed-form?)
                 as reclaimer-name
                 ;; this has to know how def-g2gl-activity builds structure the
                 ;; structure name, and how def-structure builds reclaimer name:
                    = (build-ab-symbol 'reclaim class-name 'activity-compilation)
                 collect `((,(map-g2gl-activity-class-to-code class-name)
                             ,@(if (eq class-name substitute-for-non-activity-class)
                                   `(,non-activity-class-code)))
                           #+development ',class-name ; to ease debugging
                           ,@custom-reclamation-code
                           (,reclaimer-name c))))))




;;; The macro `aggregate-g2gl-activity-compilation-creation-code' is used to
;;; expand into code to create the compilation structure corresponding to class,
;;; a particular proper subclass of g2gl-activity.  The result is a newly
;;; created activity compilation structure.
;;;
;;; Note that this handles certain non-custom compilation steps as follows:
;;;
;;;  (a) required-non-nil-value - a nil check is done on the value of a slot
;;;  with this feature in the activity instance, and, when nil, a compiler error
;;;  is issued; and
;;;
;;;  (b) carried-over-to-c - the value a slot with this feature is carried over
;;;  identically to the corresponding slot, whose Lisp accessor name is the same
;;;  but with "c-" prefixed to the beginning

(defmacro aggregate-g2gl-activity-compilation-creation-code (class-code)
  (when (null g2gl-activity-implementations-alist)
    (warn "**** g2gl-activity-implementations-alist is nil; something's wrong! ****"))
  `(fixnum-case ,class-code
     ,@(loop for (class-name slots)
                 in g2gl-activity-implementations-alist
             as code
                = `((,(build-ab-symbol 'make class-name 'activity-compilation)))
             collect `((,(map-g2gl-activity-class-to-code class-name)
                         ,@(if (eq class-name substitute-for-non-activity-class)
                               `(,non-activity-class-code)))
                       ,@(loop for (proxy-name a-slot? c-slot? options)
                                   in slots
                               when (memq 'required-non-nil-value options)
                                 collect `(unless (,a-slot? a)
                                            (let ((message-string
                                                    (tformat-text-string
                                                      "~(~a has no value~)"
                                                      (alias-slot-name-if-necessary
                                                        ',a-slot? a))))
                                              (post-g2gl-compilation-error
                                                message-string a b v)
                                              (reclaim-text-string message-string)))
                                   into init-forms
                               when (memq 'carried-over-to-c options)
                                 collect `(setf (,c-slot? c) (,a-slot? a))
                                   into init-forms
                               finally
                                 (return
                                   (if (null init-forms)
                                       `,code
                                       `((let ((c (progn . ,code)))
                                           ,@init-forms
                                           c)))))))))



(defun map-g2gl-activity-class-to-code (g2gl-activity-subclass)
  (symbol-value g2gl-activity-subclass))

(defun map-g2gl-activity-code-to-class (code)
  (svref activity-class-code-vector code))


(defmacro quoted-g2gl-activity-class-code (quoted-g2gl-activity-subclass)
  (when (and (consp quoted-g2gl-activity-subclass)
             (eq (car quoted-g2gl-activity-subclass) 'quote))
    (cerror "continue anyway"
            "The arg  (~s) to quoted-g2gl-activity-class-code should NOT be quoted."
            quoted-g2gl-activity-subclass))
  (map-g2gl-activity-class-to-code quoted-g2gl-activity-subclass))





;;;; g2gl-type-specifier slot



(defun g2gl-type-specifier-p (proposed-type)
  (or (memq proposed-type '(general integer float truth-value text symbol
                            sequence structure))
      (and (listp proposed-type)
           (memq (car proposed-type) '(class xml-type)))))

(def-grammar-category g2gl-type-specifier? ()
  ('none nil)
  (g2gl-type-specifier))

(def-slot-value-writer g2gl-type-specifier? (value)
  (if (null value)
      (twrite-string "none")                ; nec.? redundant?
      (g2gl-type-specifier-formatter value)))

(def-grammar-category g2gl-type-specifier ()
  ('general)
  ('integer)
  ('float)
  ('truth-value)
  ('text)
  ('symbol)
  ('sequence)
  ('structure)
  (('class unreserved-symbol)
   (class 2))
  (('xml-type unreserved-symbol)
   (xml-type 2))
  (('xml-type unreserved-symbol '\:
              unreserved-symbol)
   (xml-type 2 4)))


;;; Make a g2gl-type-specifier representing a reference to an external XML type,
;;; optionally recording the namespace prefix and URI in the namespace map of
;;; the current g2gl-definition (or reclaiming the URI if there's already a
;;; binding for that prefix and URI).

(defun make-g2gl-xml-type-specifier (prefix? type &optional ns-uri?)
  (when ns-uri?
    (add-xml-namespace-to-current-g2gl-definition prefix? ns-uri?))
  (if prefix?
      (slot-value-list 'xml-type prefix? type)
      (slot-value-list 'xml-type type)))

(defun g2gl-xml-type-specifier-type (type-spec)
  (or (third type-spec) (second type-spec)))

(defun g2gl-xml-type-specifier-prefix (type-spec)
  (and (third type-spec) (second type-spec)))


(defun g2gl-type-specifier-formatter (value)
  (cond
    ((null value)
     (tformat "none"))
    ((symbolp value)
     (twrite-symbol value))
    ((listp value)
     (let ((first (first value)))
       (case first
         (class
          (tformat "class ")
          (twrite-symbol (second value)))
         (xml-type
          (tformat "xml-type ")
          (twrite-symbol (second value))
          (when (= (length value) 3)
            (tformat ":")
            (twrite-symbol (third value)))))))))

(def-slot-value-writer g2gl-type-specifier (value)
  (g2gl-type-specifier-formatter value))


;;;; The category `g2gl-variable-value' ...

(def-grammar-category g2gl-variable-value? ()
  ('none nil)
  (g2gl-variable-value))

(def-grammar-category g2gl-variable-value ()
  (integer)
  (float)
  (truth-value)
  (whole-string)
  (symbol 1 reject-none-as-symbol)
  (g2gl-sequence)
  (g2gl-structure)
  (g2gl-evaluate-expression)
  ;; item names/references?
  ;; xml type??
  )
  
(def-grammar-category g2gl-evaluate-expression ()
  (('g2gl-evaluate-expression '\( g2gl-generic-expression '\, g2gl-generic-expression-default-value '\)) (3 5)))
  
(def-grammar-category g2gl-generic-expression ()
  (integer)
  (float)
  (truth-value)
  (whole-string)
  (symbol 1 reject-none-as-symbol)
  (g2gl-sequence)
  (g2gl-structure)
  )
    
(def-grammar-category g2gl-generic-expression-default-value ()
  (integer)
  (float)
  (truth-value)
  (whole-string)
  (symbol 1 reject-none-as-symbol)
  (g2gl-sequence)
  (g2gl-structure)
  )
  
(defun-simple reject-none-as-symbol (parse-result)
  (if (eq parse-result 'none)
      bad-phrase
      parse-result))

(def-slot-value-writer g2gl-variable-value? (slot-value)
  (write-attribute slot-value))                ; OK for now!



;; The function `g2gl-variable-type-p' returns true iff `type' is a proper G2GL
;; variable type for a variable of class `class'.

(defun g2gl-variable-type-p (type class)
  (case class
    (g2gl-partner-link-variable
     (g2gl-partner-link-variable-type-p type))
    (g2gl-correlation-variable
     (g2gl-correlation-variable-type-p type))
    (t
     (g2gl-type-specifier-p type))))



;;; Is a G2 type symbol a primitive type?

(defun g2gl-is-primitive-g2-type-symbol-p (type-symbol)
  (case type-symbol
    ((general truth-value integer symbol text float) t)))


;;; Is an xsd type symbol a primitive type?

(defun g2gl-is-primitive-xsd-type-symbol-p (type-symbol)
  (case type-symbol
    ((any-type boolean double float integer string) t)))



;;; xsd primitive type -> g2 primitive type
;;;
;;; Mapping from primitive types in XSD to G2 types
;;;

(defun convert-xsd-primitive-type-to-g2-primitive-type (xsd-type-symbol)
  (case xsd-type-symbol
    (any-type 'general)
    (boolean 'truth-value)
    (integer 'integer)
    ((double float) 'float)
    (t 'text)))

;;; g2 primitive type -> xsd primitive type
;;;
;;; Mapping from primitive types in G2 to XSD primitive types

(defun convert-g2-primitive-type-to-xsd-primitive-type (xsd-type-symbol)
  (case xsd-type-symbol
    (general 'any-type)
    (truth-value 'boolean)
    ((double float) 'double)
    (integer 'integer)
    (t 'string)))

;;; XML Name -> g2gl-type-specifier
;;;
;;; Takes a wide-string as an input.  The result is either a
;;; symbol (for a g2 primitive type) or it is a list for either
;;; g2 class types or XML defined class types.
;;;
;;; examples:
;;;
;;; "xsd:string" --> 'text
;;; "xsd:double" --> 'float
;;; "g2:integer" --> 'integer
;;; "g2:myTank" --> ('class 'my-tank)
;;; "lns:customerInfo" --> ('xml-type 'lns 'customer-info)
;;; "customerRecord" --> ('xml-type 'customer-record)
;;;
(defun convert-xml-name-to-g2gl-type-specifier (xml-name-widestring)
  (when (null xml-name-widestring)
    (return-from convert-xml-name-to-g2gl-type-specifier nil))
  (let* ((xml-name-parts
           (parse-text-line-into-list-of-text-strings
             xml-name-widestring #w":" #w" "))
         (result nil))
    (cond ((= (length xml-name-parts) 2)
           (let ((prefix-symbol
                   (convert-xml-name-to-symbol (first xml-name-parts)))
                 (type-name-symbol
                   (convert-xml-name-to-symbol (second xml-name-parts))))
             (case prefix-symbol
               (g2
                (cond ((g2gl-is-primitive-g2-type-symbol-p type-name-symbol)
                       (setq result type-name-symbol))

                      (t (setq result (slot-value-list 'class type-name-symbol)))))
               (xsd
                (setq result (convert-xsd-primitive-type-to-g2-primitive-type
                               type-name-symbol)))
               (t
                (setq result
                      (slot-value-list 'xml-type prefix-symbol type-name-symbol))))))
          ((= (length xml-name-parts) 1)
           (setq result (slot-value-list 'xml-type
                                         (convert-xml-name-to-symbol xml-name-widestring)))))
    (reclaim-gensym-tree-with-text-strings xml-name-parts)
    result))





;;;; G2GL Boolean Type


;;; The variables `g2gl-true' and `g2gl-false' represent truth-value (really
;;; boolean) values in G2GL.  These are implemented as unique conses, and in
;;; fact are the same as the evaluator's evaluation-true-value and
;;; evaluation-false-value, respectively.  In expressions, these are the only
;;; valid representation for boolean true and false values.

;;; The macro `g2gl-true-p' may be called with expression-value, the result of
;;; evaluating a G2GL expression, and is true if expression-value is g2gl-true.

;;; The macro `g2gl-false-p' is similar, but is true if expression-value is
;;; g2gl-false.

;;; The macro `g2gl-not' is similar, but is true if expression-value is not
;;; g2gl-true.

(defvar g2gl-true evaluation-true-value)
(defvar g2gl-false evaluation-false-value)

(defun-substitution-macro g2gl-true-p (expression-value)
  (eq expression-value g2gl-true))

(defun-substitution-macro g2gl-false-p (expression-value)
  (eq expression-value g2gl-false))

(defun-substitution-macro g2gl-not (expression-value)
  (if (eq expression-value g2gl-true) g2gl-false g2gl-true))





;;;; G2GL Call Invocation Structures


;;; ... used for the g2gl-call (non-standard BPEL) G2GL activity.

(def-structure (g2gl-call-invocation
                 (:constructor make-g2gl-call-invocation-internal ())
                 (:include code-body-invocation))
  (variables-to-receive-g2gl-call-values nil)
  (number-of-g2gl-call-return-values nil)
  (thread-parked-on-g2gl-call nil)
  (g2-procedure-invocation-for-g2gl-call nil)
  (completion-form-for-g2gl-call nil :reclaimer reclaim-gensym-list))

(defun-simple g2gl-call-invocation-p-function (thing)
  (g2gl-call-invocation-p thing))







;;;; Activity Definitions



(def-g2gl-activity (g2gl-receive
                     g2gl-activity 1
                     (attribute-displays
                       ((g2gl-operation-name) at-standard-position)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description receive)
  ((g2gl-partner-link-variable-name
     partner-link-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-partner-link-variable-name?))
   (g2gl-partner-link-variable partner-link-variable (c-only))
   (g2gl-port-type
     port-type
     (carried-over-to-c (initial-value nil))
     (type g2gl-port-type-name))
   (g2gl-operation-name
     operation-name
     (required-non-nil-value carried-over-to-c (initial-value nil))
     (type g2gl-operation-name?))
   (g2gl-correlations correlations (a-only) (type g2gl-correlations))
   (c-g2gl-correlations c-correlations (c-only reclaimable-at-both-levels))
   (g2gl-message-variable-name
     output-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-message-variable-name?))
   (g2gl-message-variable output-variable (c-only))
   (this-is-an-instantiation-trigger-for-receive
     trigger
     (carried-over-to-c flag)))
  (activity-compilation-code
    (when partner-link-variable-name
      (set-acs
        partner-link-variable
        (get-g2gl-variable-compilation
          partner-link-variable-name 'g2gl-partner-link-variable nil a b v)))
    (set-acs
      c-correlations
      (loop for correlation in correlations
            collect (compile-g2gl-correlation correlation a b v)
              using gensym-cons))
    (when output-variable-name
      (set-acs
        output-variable
        (get-g2gl-variable-compilation
          output-variable-name nil nil a b v))))
  (activity-execution-code
    (let ((result
            (look-for-g2gl-message-transmission
              thread partner-link-variable port-type operation-name
              c-correlations output-variable nil)))
      (when (null result)
        (when (null (execution-thread-state thread))
          (setf (execution-thread-state thread) 'in-partner-link)
          (setf (execution-thread-state-parameter thread)
                (get-value-of-g2gl-variable partner-link-variable f))
          ;; The position of the following exit statement diverges from the
          ;; spec!  The exit should go in the outer conditional, not just the
          ;; inner.  -dougo, 9/12/06
          ;; TO DO: determine if this difference is detectable.
          (exit-g2gl-process)))
      (when (eq (execution-thread-state thread) 'in-partner-link)
        (let ((sp (execution-thread-state-parameter thread)))
          (setf (threads-located-at-receiving-activity-compilations sp)
                (delete-gensym-element
                  thread (threads-located-at-receiving-activity-compilations sp)))
          (setf (execution-thread-state thread) nil)
          (setf (execution-thread-state-parameter thread) nil)))
      (when (not (eq result 'success))        ; -- if so, must be a fault
        (signal-g2gl-execution-fault thread result)
        (exit-g2gl-process)))))

(define-slot-alias this-is-an-instantiation-trigger
    this-is-an-instantiation-trigger-for-receive
  g2gl-receive)                                ; c.f., g2gl-pick


(def-absent-slot-putter output-g2gl-variable-name (a value)
  (setf (g2gl-message-variable-name a) value))

;; This slot name change, done post 8.1b0, applies to g2gl-receive, g2gl-invoke,
;; and g2gl-message-event-handler activities. (MHD 4/12/05)





(def-grammar-category g2gl-port-type-name ()
  ('unspecified nil)
  (unreserved-symbol))

(def-slot-value-writer g2gl-port-type-name (value)
  (cond
    ((null value)
     (twrite-string "unspecified"))
    (t
     (twrite-symbol value))))




(def-grammar-category g2gl-partner-link-variable-name ()
  (unreserved-symbol))

(def-grammar-category g2gl-port-type-specifier ()
  (unreserved-symbol)
  (('xml-type unreserved-symbol)
   (xml-type 2))
  (('xml-type unreserved-symbol '\: unreserved-symbol)
   (xml-type 2 4)))


;;; Xml Name -> g2gl-port-type-specifier
;;;
;;; Examples:

;;; "g2:foo" --> 'foo
;;; "foo" --> (xml-type foo)
;;; "foo:bar" --> (xml-type foo bar)

(defun convert-xml-name-to-g2gl-port-type-specifier (xml-name-widestring)
  (when (null xml-name-widestring)
    (return-from convert-xml-name-to-g2gl-port-type-specifier nil))
  (let* ((xml-name-parts
           (parse-text-line-into-list-of-text-strings
             xml-name-widestring #w":" #w" "))
         (result nil))
    (cond ((= (length xml-name-parts) 2)
           (let ((prefix-symbol
                   (convert-xml-name-to-symbol (first xml-name-parts)))
                 (g2-name
                   (convert-xml-name-to-symbol (second xml-name-parts))))
             (case prefix-symbol
               (g2
                (setq result g2-name))
               (t
                (setq result
                      (slot-value-list 'xml-type prefix-symbol g2-name))))))
          ((= (length xml-name-parts) 1)
           (setq result (slot-value-list 'xml-type
                                         (convert-xml-name-to-symbol xml-name-widestring)))))
    (reclaim-gensym-tree-with-text-strings xml-name-parts)
    result))

;;; g2gl-port-type-specifier -> Xml Name
;;;
;;; Examples:
;;; 'foo --> "g2:foo"
;;; (xml-type foo) --> "foo"
;;; (xml-type foo bar) --> "foo:bar"


(defun convert-g2gl-port-type-specifier-to-xml-name (g2gl-port-type-specifier)
  (let ((result nil))
    (cond ((symbolp g2gl-port-type-specifier)
           (setq result
                 (twith-output-to-text-string
                   (tformat "g2:")
                   (twrite-symbol g2gl-port-type-specifier))))
          ((= (length g2gl-port-type-specifier) 3)
           (let* ((prefix
                    (second g2gl-port-type-specifier))
                  (type-name
                    (third g2gl-port-type-specifier))
                  (prefix-xml-name
                    (convert-symbol-to-xml-name prefix))
                  (type-xml-name
                    (convert-symbol-to-xml-name type-name)))

             (setq result (twith-output-to-text-string
                            (tformat "~a:~a"
                                     prefix-xml-name
                                     type-xml-name)))

             (reclaim-wide-string prefix-xml-name)
             (reclaim-wide-string type-xml-name)))

          ((= (length g2gl-port-type-specifier) 2)

           (case (first g2gl-port-type-specifier)
             (class
              (let* ((type-name
                       (second g2gl-port-type-specifier))
                     (type-xml-name
                       (convert-symbol-to-xml-name type-name)))
              (setq result (twith-output-to-text-string
                            (tformat "g2:")
                            (twrite-symbol type-name)))
              (reclaim-wide-string type-xml-name)))
             (xml-type
              (let* ((type-name
                       (second g2gl-port-type-specifier))
                     (type-xml-name
                       (convert-symbol-to-xml-name type-name)))
                (setq result (twith-output-to-text-string
                               (tformat "~a" type-xml-name)))
                (reclaim-wide-string type-xml-name))))))
    result))

(def-grammar-category wsdl-operation-name ()
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-partner-link-variable-name)
(def-registered-directory-of-names wsdl-port-type)
(def-registered-directory-of-names wsdl-operation-name)

(defun format-g2gl-port-type-specifier (port-type)
  (cond ((symbolp port-type)
         (twrite-symbol port-type))
        ((= (length port-type) 2)
         (tformat "xml-type ")
         (twrite-symbol (second port-type)))
        ((= (length port-type) 3)
         (tformat "xml-type ")
         (twrite-symbol (second port-type))
         (tformat ":")
         (twrite-symbol (third port-type)))))


;; Slot type g2gl-correlations:

(def-grammar-list-category g2gl-correlations (g2gl-correlation)
  :separator \; :conjunction nil :empty-list-symbol none)

(def-grammar-category g2gl-correlation ()
  (g2gl-variable-name)
  ((g2gl-variable-name '\, 'initiate 'conversation)
   (1 initiate-conversation))

  ;; make the next two rules be for invoke-specific case only?!
  ((g2gl-variable-name '\, 'initiate 'conversation
                       '\, g2gl-correlation-pattern-specifier)
   (1 initiate-conversation 6))
  ((g2gl-variable-name '\, g2gl-correlation-pattern-specifier)
   (1 3)))

(def-grammar-category g2gl-correlation-pattern-specifier ()
  ('out)
  ('in)
  ('out-in))


(def-grammar-category g2gl-variable-name ()
  (unreserved-symbol))

(def-slot-value-writer g2gl-variable-name (value)
  (twrite-symbol-or-none value))

(def-registered-directory-of-names g2gl-variable-name)

;; NOTE: ideally, we'd like a *local* names directory, for prompting with these
;; names only within the local process scope!  A separate but worthwhile side
;; project! (MHD 11/29/04)


(def-slot-value-compiler g2gl-correlations (parse-result)
  (cond
    ((eq parse-result 'none)
     nil)
    (t
     ;; get rid of noise in some parts of the list structure:
     (loop for x in (remove-noise-at-head-of-list-phrase parse-result)
           ;; x is either <var-name/symbol>
           ;;   or (<var-name/symbol> <option> ...)
           collect (if (consp x) x (phrase-cons x nil))
             using phrase-cons))))

(def-slot-value-writer g2gl-correlations (value)
  (cond
    ((null value)
     (twrite "none"))
    (t
     (loop for (variable-name . options) in value
           as first-time? = t then nil
           do (unless first-time?
                (tformat "; "))
              (tformat "~(~a~)" variable-name)
              (loop for option in options do
                (case option
                  (initiate-conversation
                   (tformat ", initiate conversation"))
                  (t
                   (tformat ", ~(~a~)" option))))))))



;; Slot type g2gl-variable-name?:

(def-grammar-category g2gl-variable-name? ()
  ('none nil)
  (g2gl-variable-name))

(def-slot-value-writer g2gl-variable-name? (value)
    (twrite-symbol-or-none value))




(def-g2gl-activity (g2gl-reply
                     g2gl-activity 2
                     (attribute-displays
                       ((g2gl-operation-name) at-standard-position)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description reply)
  ((g2gl-partner-link-variable-name
     partner-link-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-partner-link-variable-name?)
     (no-accessor))
   (g2gl-partner-link-variable
     partner-link-variable
     (c-only)
     (no-accessor))
   (g2gl-port-type
     port-type
     (carried-over-to-c (initial-value nil))
     (type g2gl-port-type-name)
     (no-accessor))
   (g2gl-operation-name
     operation-name
     (required-non-nil-value carried-over-to-c (initial-value nil))
     (type g2gl-operation-name?)
     (no-accessor))
   (g2gl-correlations
     correlations
     (a-only)
     (type g2gl-correlations)
     (no-accessor))
   (c-g2gl-correlations
     c-correlations
     (c-only reclaimable-at-both-levels)
     (no-accessor))
   (g2gl-message-variable-name
     input-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-message-variable-name?)
     (no-accessor))
   (g2gl-message-variable
     input-variable
     (c-only)
     (no-accessor))
   (fault-name-for-reply
     fault-name (carried-over-to-c symbol) (type g2gl-fault-name?)))
  (activity-compilation-code
    (when partner-link-variable-name
      (set-acs
        partner-link-variable
        (get-g2gl-variable-compilation
          partner-link-variable-name 'g2gl-partner-link-variable nil a b v))
      (set-acs
        c-correlations
        (loop for correlation in correlations
              collect (compile-g2gl-correlation correlation a b v)
                using gensym-cons))
      (when input-variable-name
        (set-acs
          input-variable
          (get-g2gl-variable-compilation input-variable-name nil nil a b v)))))
  (activity-execution-code
    (let* ((source-or-fault-name (or fault-name 'reply))
           (result
             (send-g2gl-message-transmission thread source-or-fault-name)))
      (when (not (eq result 'success))        ; -- if so, must be a fault
        (signal-g2gl-execution-fault thread result)
        (exit-g2gl-process)))))


(def-absent-slot-putter input-g2gl-variable-name (a value)
  (setf (g2gl-message-variable-name a) value))

;; This slot name change, which was done post 8.1b0, applies only to g2gl-reply
;; and g2gl-invoke activities. (MHD 4/12/05)



;;; The G2GL-invoke activity permits a right-edge out connection optionally.
;;; One or more right-edge out connections go to fault handlers and at most one
;;; compensation handler specific to this activity.  A menu choice, therefore,
;;; ought to exist to "sprout" a right-edge output connection to either a fault
;;; handler or a compensation handler (if there's not one present).

(def-g2gl-activity (g2gl-invoke
                     g2gl-activity 3
                     (connections-configuration local-handlers-allowed)
                     (attribute-displays
                       ((g2gl-operation-name) at-standard-position)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description invoke)
  ((g2gl-partner-link-variable-name
     partner-link-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-partner-link-variable-name?)
     (no-accessor))
   (g2gl-partner-link-variable
     partner-link-variable
     (c-only)
     (no-accessor))
   (g2gl-port-type
     port-type
     (carried-over-to-c (initial-value nil))
     (type g2gl-port-type-name)
     (no-accessor))
   (g2gl-operation-name
     operation-name
     (required-non-nil-value carried-over-to-c (initial-value nil))
     (type g2gl-operation-name?)
     (no-accessor))
   (g2gl-correlations
     correlations
     (a-only)
     (type g2gl-correlations)
     (no-accessor))
   (c-g2gl-correlations
     c-correlations
     (c-only reclaimable-at-both-levels)
     (no-accessor))
   (g2gl-message-variable-name
     input-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-message-variable-name?)
     (no-accessor))
   (g2gl-message-variable
     input-variable
     (c-only)
     (no-accessor))
   (g2gl-response-variable-name
     output-variable-name
     (a-only (initial-value nil))
     (type g2gl-message-variable-name?))
   (g2gl-response-variable
     output-variable
     (c-only)))
  (activity-compilation-code
    (when partner-link-variable-name
      (set-acs
        partner-link-variable
        (get-g2gl-variable-compilation
          partner-link-variable-name 'G2GL-partner-link-variable nil a b v)))
    (set-acs
      c-correlations
      (loop for correlation in correlations
            collect (compile-g2gl-correlation correlation a b v)
              using gensym-cons))
    (when input-variable-name
      (set-acs
        input-variable
        (get-g2gl-variable-compilation input-variable-name nil nil a b v)))
    (when output-variable-name
      (set-acs
        output-variable
        (get-g2gl-variable-compilation output-variable-name nil nil a b v))))
  (activity-execution-code
    (let (result)
      (when (null (execution-thread-state thread))
        (setq result
              (send-g2gl-message-transmission thread 'invoke))
        (when (not (eq result 'success))
          (cond ((g2gl-call-invocation-p result)
                 (setf (execution-thread-state thread) 'in-procedure)
                 (setf (execution-thread-state-parameter thread) result)
                 (setf (thread-parked-on-g2gl-call result) thread))
                (t
                 (signal-g2gl-execution-fault thread result)))
          (exit-g2gl-process)))
      (cond
        ((eq (execution-thread-state thread) 'in-procedure)
         (setq result (execution-thread-state-parameter thread))
         (setf (execution-thread-state thread) nil)
         (setf (execution-thread-state-parameter thread) nil)
         (when result
           (signal-g2gl-execution-fault thread result)
           (exit-g2gl-process)))
        (output-variable
         (setq result
               (look-for-g2gl-message-transmission
                 thread partner-link-variable port-type operation-name
                 c-correlations output-variable t))
         (when (null result)
           (when (null (execution-thread-state thread))
             (setf (execution-thread-state thread) 'in-partner-link)
             (setf (execution-thread-state-parameter thread)
                   (get-value-of-g2gl-variable partner-link-variable f)))
           (exit-g2gl-process))
         (when (eq (execution-thread-state thread) 'in-partner-link)
           (let ((sp (execution-thread-state-parameter thread)))
             (setf (threads-located-at-receiving-activity-compilations sp)
                   (delete-gensym-element
                     thread
                     (threads-located-at-receiving-activity-compilations sp))))
           (setf (execution-thread-state thread) nil)
           (setf (execution-thread-state-parameter thread) nil))
         (when (not (eq result 'success))        ; -- if so, must be a fault
           (signal-g2gl-execution-fault thread result)
           (exit-g2gl-process))))
      (loop for hc in (cdr c-successors)
            when (=f (g2gl-activity-class-code hc)
                     (quoted-g2gl-activity-class-code
                       g2gl-compensation-handler))
              return (record-normal-completion-of-nested-compilation
                       thread c
                       (compilations-of-outside-variables-used-in-body hc)
                       nil f)))))


(def-absent-slot-putter response-output-g2gl-variable-name (a value)
  (setf (g2gl-response-variable-name a) value))

;; This slot name change, which was done post 8.1b0, applies only to g2gl-invoke
;; activities. (MHD 4/12/05)

;;; The macro `g2gl-eval-expression-error' is used to throw a fault within a
;;; catch-g2gl-eval-fault ...

(defmacro catch-g2gl-eval-fault ((fault-info-place) &body body)
  `(setf ,fault-info-place
         (catch g2gl-eval-error
           (progn . ,body)
           nil)))

(defvar g2gl-eval-error (list 'g2gl-eval-error))

#+development
(defparameter break-on-g2gl-eval-errors nil)

(defmacro g2gl-eval-expression-error (fault-name &body desc-writers)
  `(progn
     #+development
     (when break-on-g2gl-eval-errors
       (cerror "continue with G2GL error"
               "G2GL Eval Error: ~a: ~a"
               ,fault-name
               (twith-output-to-text-string
                 ,@desc-writers)))
     (throw g2gl-eval-error
       (make-g2gl-system-fault
         ,fault-name
         ,@desc-writers))))

(def-g2gl-activity (g2gl-pick
                     g2gl-activity 4
                     (connections-configuration split (g2gl-pick-join))
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 100)
                       #.(g2gl-standard-connection-stub 'output 'bottom 67)
                       #.(g2gl-standard-connection-stub 'output 'bottom 133)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description pick)
  ((this-is-an-instantiation-trigger-for-pick
     trigger
     (carried-over-to-c flag)))
  (activity-compilation-code
    (loop with message-branch-p
          for out being each output-connection of a
          as output-end-object = (output-end-object out)
          when (not (or (setq message-branch-p
                              (eq (class output-end-object) 'g2gl-receive))
                        (eq (class output-end-object) 'g2gl-wait)))
            do (post-g2gl-compilation-error
                 "at least one branch is not headed by a G2GL receive or wait activity"
                 a b v)
          count message-branch-p into n-message-branches
          finally
            ;; spec doesn't specify this check in detail, but says it's needed:
            (unless (>f n-message-branches 0)
              (post-g2gl-compilation-error
                "at least one branch must be headed by a G2GL receive activity"
                a b v))))
  (activity-execution-code
    (when (null (execution-thread-state thread))
      (setf (execution-thread-state thread) 'in-partner-link)
      (setf (execution-thread-state-parameter thread)
            (loop for c-successor in c-successors
                  if (=f (g2gl-activity-class-code c-successor)
                         (quoted-g2gl-activity-class-code g2gl-receive))
                    collect nil using gensym-cons
                  else
                    if (=f (g2gl-activity-class-code c-successor)
                           (quoted-g2gl-activity-class-code g2gl-wait))
                      collect
                      (let ((time
                              (evaluate-g2gl-expression
                                (g2gl-expression-compilation c-successor)
                                thread)))
                        (cond
                          ;; note: I think this is needed to prevent a possible
                          ;; abort; however, it doesn't clean up garbage, and
                          ;; this logic is not in spec; review! (MHD 4/12/05)
                          ((not (floatp time))
                           (signal-g2gl-system-fault
                             thread 'invalid-wait-duration-or-deadline
                             (twrite-g2gl-value time))
                           (exit-g2gl-process))
                          (t
                           (allocate-managed-float
                             (if (eq (c-type-of-g2gl-alarm-time-expression
                                       c-successor)
                                     'duration-expression)
                                 (+e time (g2gl-get-current-time))
                                 time)))))
                      using gensym-cons)))
    (let* ((earliest-alarm-time nil)
           (result nil)
           (remaining-c-successors c-successors)
           (remaining-possibility-values
             (execution-thread-state-parameter thread))
           (i 0)
           c-successor pv)
      (declare (type fixnum i))
      (loop while (and remaining-c-successors (null result))
            do (setq c-successor (first remaining-c-successors))
               (setq pv (first remaining-possibility-values))
               (when (and (=f (g2gl-activity-class-code c-successor)
                              (quoted-g2gl-activity-class-code g2gl-wait))
                          (or (null earliest-alarm-time)
                              (<e pv earliest-alarm-time)))
                 (if (not (>e pv (g2gl-get-current-time)))
                     (setq result 'success)
                     (setq earliest-alarm-time pv)))
               (when (=f (g2gl-activity-class-code c-successor)
                         (quoted-g2gl-activity-class-code g2gl-receive))
                 (setq result
                       (look-for-g2gl-message-transmission
                         thread
                         (g2gl-partner-link-variable c-successor)
                         (c-g2gl-port-type c-successor)
                         (c-g2gl-operation-name c-successor)
                         (c-g2gl-correlations c-successor)
                         (g2gl-message-variable c-successor)
                         nil))
                 (when (and (null result) (null pv))
                   (setf (first remaining-possibility-values)
                         (get-value-of-g2gl-variable
                           (g2gl-partner-link-variable c-successor)
                           f))))
               (pop remaining-c-successors)
               (pop remaining-possibility-values)
               (incff i))
      (when (null result)
        (when earliest-alarm-time
          (schedule-g2gl-execution-thread thread earliest-alarm-time))
        (exit-g2gl-process))
      (loop for pv in (execution-thread-state-parameter thread)
            when (and (not (null pv))
                      (not (managed-float-p pv))) ; not a G2 time
              do (setf (threads-located-at-receiving-activity-compilations pv)
                       (delete-gensym-element
                         thread
                         (threads-located-at-receiving-activity-compilations pv))))
      (reclaim-gensym-list (execution-thread-state-parameter thread))
      (setf (execution-thread-state thread) nil)
      (setf (execution-thread-state-parameter thread) nil)
      (when (not (eq result 'success))        ; -- if so, must be a fault
        (signal-g2gl-execution-fault thread result)
        (exit-g2gl-process))
      (loop repeat (-f i 1) do (pop c-successors))
      ;; now move over the G2GL receive or wait activity compilation on the
      ;; branch:
      (setq c (first c-successors))
      (setf (activity-compilation-to-execute thread) c) ; not really necessary!
      (setq c-successors (activity-compilation-successors c)))))

(define-slot-alias this-is-an-instantiation-trigger
    this-is-an-instantiation-trigger-for-pick
  g2gl-pick)                                ; c.f., g2gl-receive



(def-absent-slot-putter this-is-an-instantiation-trigger (a value)
  (frame-class-case a                        ; a g2gl-pick or g2gl-receive instance
    (g2gl-receive
      (setf (this-is-an-instantiation-trigger-for-receive a) value))
    (g2gl-pick
      (setf (this-is-an-instantiation-trigger-for-pick a) value))
    #+development
    (t
      (cerror "continue anyhow in production"
              "unknown class of object (~s) with this slot (value: ~s)!"
              a value))))

;; Done development of 8.1b0. (MHD 3/23/05)


(def-absent-slot-putter pick-possibilities (g2gl-pick value)
  (reclaim-slot-value value))                ; obsolete slot (MHD 4/14/05)










(def-g2gl-activity (g2gl-pick-join
                     g2gl-activity 5
                     (connections-configuration rejoin)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 67)
                       #.(g2gl-standard-connection-stub 'input 'top 133)
                       #.(g2gl-standard-connection-stub 'output 'bottom 100)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description pick-join)
  ())



(def-g2gl-activity (g2gl-switch-fork
                     g2gl-activity 6
                     (connections-configuration fork (g2gl-switch-join))
                     (additional-stubs
                       #.(g2gl-standard-connection-stub 'output 'right 25)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description switch-fork)
  ((switch-fork-condition
     e
     (a-only required-non-nil-value)
     (type g2gl-boolean-expression text)))
  (activity-compilation-code
    (when e
      (setf (g2gl-expression-compilation c)
            (compile-g2gl-expression
              (car e)                                ; parse tree
              'boolean-expression a b v))))
  (activity-execution-code
    (if (g2gl-false-p expression-value)
        (pop c-successors))))

(def-g2gl-activity (g2gl-switch-join
                     g2gl-activity 7
                     (connections-configuration rejoin)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 67)
                       #.(g2gl-standard-connection-stub 'input 'top 133)
                       #.(g2gl-standard-connection-stub 'output 'bottom 100)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description switch-join)
    ())



(def-g2gl-activity (g2gl-while
                     g2gl-activity 8
                     (connections-configuration loop-anchor (g2gl-while))
                     (additional-stubs
                       #.(g2gl-standard-connection-stub 'output 'right 17)
                       #.(g2gl-standard-connection-stub 'input 'right 33)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description while)
  ((while-iteration-condition
     e
     (a-only required-non-nil-value)
     (type g2gl-boolean-expression text)))
  (activity-compilation-code
    (when e
      (setf (g2gl-expression-compilation c)
            (compile-g2gl-expression
              (car e)                        ; parse tree
              'boolean-expression a b v))))
  (activity-execution-code
    (if (g2gl-true-p expression-value)
        (pop c-successors))))



(def-g2gl-activity (g2gl-flow-split
                     g2gl-activity 9
                     (connections-configuration
                       split
                       (g2gl-flow-sync
                         g2gl-flow-discriminator
                         g2gl-n-out-of-m-flow-join
                         g2gl-flow-terminator))
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 100)
                       #.(g2gl-standard-connection-stub 'output 'bottom 67)
                       #.(g2gl-standard-connection-stub 'output 'bottom 133)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description flow-split)
  ((g2gl-link-names link-names (a-only) (type g2gl-link-names))
   (g2gl-flow-scope-marker marker (c-only)))
  (activity-compilation-code
    (set-acs
      marker
      (get-g2gl-flow-scope-marker a nil)))
  (activity-execution-code
    ;; WHILE (LOOP) REENTRANCY PROBLEM HERE!!!
;    (gensym-assert
;      ;; showing no need for pushnew (assuming UUID's are unique;
;      ;; otherwise, "least of your problems")
;      (not (memq
;             marker
;             (g2gl-flow-scope-markers-in-this-thread thread))))
    (gensym-push
      marker (g2gl-flow-scope-markers-in-this-thread thread))
    (loop for cs in (cdr c-successors)
          as sibling-thread
             = (make-g2gl-execution-thread
                 cs c nil parent-thread thread
                 (body-compilation-this-is-being-used-to-execute thread)
                 f)
          do (schedule-g2gl-execution-thread sibling-thread nil))))

(def-absent-slot-putter bpel-link-names (g2gl-flow-split link-names)
  (setf (g2gl-link-names g2gl-flow-split) link-names))


;; Slot type g2gl-link-names:

(def-grammar-list-category g2gl-link-names (g2gl-link-name)
  :separator \, :conjunction nil :empty-list-symbol none)

(def-grammar-category g2gl-link-name ()
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-link-name)

(def-slot-value-compiler g2gl-link-names (parse-result)
  (if (eq parse-result 'none)
      nil
      (remove-noise-at-head-of-list-phrase parse-result)))

(def-slot-value-writer g2gl-link-names (value)
  (cond
    ((null value)
     (twrite-string "none"))
    (t
     (tformat "~(~L,-~)" value))))        ; print in lowercase as: a, b, ..., z


(def-slot-value-compiler g2gl-link-name (parse-result)
  (if (eq parse-result 'none) nil parse-result))

(def-slot-value-writer g2gl-link-name (value)
  (twrite-symbol-or-none value))






(def-g2gl-activity (g2gl-flow-sync
                     g2gl-flow-join 10
                     (connections-configuration rejoin)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 67)
                       #.(g2gl-standard-connection-stub 'input 'top 133)
                       #.(g2gl-standard-connection-stub 'output 'bottom 100)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description flow-sync)
  ((number-of-rejoining-branches n (c-only integer))
   (g2gl-flow-sync-scope-marker marker (c-only)))
  (activity-compilation-code
    (set-acs n (g2gl-activity-in-connection-count a))
    (set-acs
      marker (get-g2gl-flow-scope-marker a stack)))
  (activity-execution-code
    (let ((k (loop for some-thread in (g2gl-execution-threads f)
                   count
                   (and (eq c (activity-compilation-to-execute
                                some-thread))
                        (null (execution-thread-state
                                some-thread)))))) ; not IN-TRANSIT
      (cond
        ((not (=f k n))
         (exit-g2gl-process))
        (t
         (setf (g2gl-flow-scope-markers-in-this-thread thread)
               (delete-gensym-element
                 marker (g2gl-flow-scope-markers-in-this-thread thread)))
         (loop repeat (-f k 1)
               as related-thread
                  = (loop for some-thread in (g2gl-execution-threads f)
                          when
                            (and (not (eq some-thread thread))
                                 (eq c (activity-compilation-to-execute
                                         some-thread)))
                            return some-thread)
               do (delete-g2gl-execution-thread related-thread t t)))))))


(def-g2gl-activity (g2gl-flow-signal
                       g2gl-activity 11
                       (connections-configuration flow-signal)
                       (stubs
                         #.(g2gl-standard-connection-stub 'input 'top 20)
                         #.(g2gl-standard-connection-stub 'output 'bottom 20)
                         #.(g2gl-link-connection-stub 'output 'right 20)))
      (:funcall-at-load-time create-g2-bpel-activity-icon-description flow-signal)
    ((g2gl-link-name
       link-name
       (required-non-nil-value carried-over-to-c symbol)
       (type g2gl-link-name))
     (flow-signal-transition-condition        ; (translation . text) or nil
       e (a-only  (initial-value nil)) (type g2gl-boolean-expression? text)))
    (activity-compilation-code
      (when e
        (setf (g2gl-expression-compilation c)
              (compile-g2gl-expression
                (car e) ; translation is the "parse tree"
                'boolean-expression a b v))))
    (activity-execution-code
      (let* ((flow-gate-c (second c-successors))
             (sibling-thread
               (make-g2gl-execution-thread
                 flow-gate-c c nil parent-thread thread
                 (body-compilation-this-is-being-used-to-execute thread)
                 f))
             (link-status
               (if (g2gl-false-p expression-value)
                   ;; this covers the expression = "none" case:
                   'negative
                   'positive)))
        (when (null (execution-thread-state sibling-thread))
          (setf (execution-thread-state sibling-thread) link-status)
          (setf (execution-thread-state-parameter sibling-thread)
                link-name))
        (when (eq (execution-thread-state sibling-thread) 'in-transit)
          (setf (execution-thread-state-parameter sibling-thread)
                (nconc (execution-thread-state-parameter sibling-thread)
                       (gensym-list link-status link-name)))
          (schedule-g2gl-execution-thread sibling-thread nil)))))

;; g2gl-flow-signal was previously g2gl-link-signal (MHD 11/12/04)

(def-slot-putter flow-signal-transition-condition (g2gl-flow-signal value)
  (setf (flow-signal-transition-condition g2gl-flow-signal)
        (if (and (consp value) (null (car value)))
            ;; -- (nil . <text for none>) => nil
            nil
            value)))

(def-absent-slot-putter bpel-link-name (g2gl-flow-signal link-name)
  (setf (g2gl-link-name g2gl-flow-signal) link-name))


(def-g2gl-activity (g2gl-flow-gate
                     g2gl-activity 12
                     (connections-configuration flow-gate)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 20)
                       #.(g2gl-standard-connection-stub 'output 'bottom 20)
                       ;; one, two, or more input sync links; have one by
                       ;; default, but it can be more
                       #.(g2gl-link-connection-stub 'input 'left 20)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description flow-gate)
  ((number-of-flow-gate-in-connections n (c-only integer))
   (flow-gate-join-condition                ; (translation . text) or nil
     e (a-only (initial-value nil)) (type g2gl-boolean-expression? text))
   (c-flow-gate-join-condition ec (c-only))
   (suppress-join-failure suppress-join-failure (carried-over-to-c flag)))
  (activity-compilation-code
    (set-acs n (g2gl-activity-in-connection-count a))
    (when e
      (set-acs ec (compile-g2gl-expression (car e) 'join-condition a b v))))
  (activity-execution-code
    ;; Note: this never gets executed when arrived at from a flow-signal
    ;; activity compilation.
    (let ((k (loop for some-thread in (g2gl-execution-threads f)
                   count
                   (and (eq c (activity-compilation-to-execute
                                some-thread))
                        (case (execution-thread-state some-thread)
                          ((nil positive negative)
                           ;; not IN-TRANSIT
                           t)
                          (t nil)))))
          join-condition-result)
      (cond
        ((not (=f k n))
         (schedule-G2GL-execution-thread thread nil)
         (exit-g2gl-process))
        (t
         (setq join-condition-result
               (if (null ec)
                   (or (loop for th in (g2gl-execution-threads f)
                             if (and
                                  (eq c (activity-compilation-to-execute th))
                                  (eq (execution-thread-state th) 'positive))
                               return g2gl-true)
                       g2gl-false)
                   (evaluate-g2gl-expression ec thread)))
         (loop repeat (-f k 1)
               as related-thread
                  = (loop for th in (g2gl-execution-threads f)
                          if (and (not (eq th thread))
                                  (eq c (activity-compilation-to-execute th)))
                            return th)
               do (delete-g2gl-execution-thread related-thread t t))
         (when (and (g2gl-false-p join-condition-result)
                    (null suppress-join-failure))
           ;; the following was "commented out" in the spec of Apr. 12, 2005
           ;; (and even later versions), but LH said he'd undo that and that the
           ;; code continue to be present. But it needed the subsequent form to
           ;; exit after signalling to fix HQ-5018993 "G2GL:
           ;; flow-signal-transition-condition = false aborts G2" (MHD 4/27/05)
           (signal-g2gl-system-fault thread 'join-failure)
           (exit-g2gl-process)))))))

;; g2gl-flow-gate was previously g2gl-flow-gate (MHD 11/12/04)

(def-slot-putter flow-gate-join-condition (g2gl-flow-gate value)
  (setf (flow-gate-join-condition g2gl-flow-gate)
        (if (and (consp value) (null (car value)))
            ;; -- (nil . <text for none>) => nil
            nil
            value)))



(def-g2gl-activity (g2gl-scope g2gl-activity-with-body 13)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description scope)
  ((variable-access-serializable
     variable-access-serializable
     (carried-over-to-c flag (initial-value nil))
     (type yes-or-no)))
  (activity-execution-code
    (cond
      ((null (execution-thread-state thread))
       (setf (execution-thread-state thread) 'executing-body)
       (instantiate-g2gl-body-compilation-and-start-execution
         (g2gl-body-compilation c) nil thread f)
       ;; -- now exit (with thread now inactive, parked in a child thread, and
       ;; waiting to be reactivated after completion of the execution of the
       ;; body compilation of c)
       (exit-g2gl-process))
      (t
       (setf (execution-thread-state thread) nil)
       ;; -- presumably, prior to the above call, the slot's value was
       ;; EXECUTING-BODY, and we are now prepared to continue after completion
       ;; of the execution of the body compilation of c
       ))))


(def-g2gl-activity (g2gl-fault-handler
                     g2gl-handler 14
                     (connections-configuration local-handler)
                     (stubs))                ; no default stubs
    (:funcall-at-load-time create-g2-bpel-activity-icon-description fault-handler)
  ((g2gl-fault-name fault-name (carried-over-to-c) (type g2gl-fault-name-spec)))
  (activity-execution-code
    (let ((parameter (execution-thread-state-parameter thread)))
      (setf (execution-thread-state-parameter thread) nil)
      (instantiate-g2gl-body-compilation-and-start-execution
        (g2gl-body-compilation c) parameter thread f)
      ;; -- now exit (with thread, whose execution-thread-state is the symbol
      ;; abnormal, now inactive, parked in a child thread, and waiting to be
      ;; deleted after completion of the execution of the body compilation of c)
      (exit-g2gl-process))))





;;; The grammar category `g2gl-fault-name-spec' is used for the g2gl-fault-name
;;; of a g2gl-fault-handler instance.  The surface grammar is
;;;
;;;    none | catch all | <g2gl-fault-name/symbol>
;;;
;;; where <symbol> can be any symbol naming the fault to be handled.
;;; Internally, "none" case is represented as nil; the "catch all" case is
;;; represented as 0; the <symbol> case is simply represented as that symbol.

(def-grammar-category g2gl-fault-name-spec ()
  ('none nil)
  (('catch 'all) (1 2) transform-to-zero)
  (g2gl-fault-name))

(def-grammar-category g2gl-fault-name ()
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-fault-name)

(def-slot-value-writer g2gl-fault-name (value)
  (twrite value))

(def-grammar-category g2gl-fault-name? ()
  ('none nil)
  (g2gl-fault-name))

(defun transform-to-zero (template)
  (declare (ignore template))
  0)

(def-slot-value-writer g2gl-fault-name-spec (value)
  (cond
    ((null value)                        ; match based on variable type
     (tformat "none"))
    ((eql value 0)
     (tformat "catch all"))
    (t
     (tformat "~(~a~)" value))))


(def-slot-value-writer g2gl-fault-name? (value)
  (twrite-symbol-or-none value))





;; Note: 15 used below.





(def-g2gl-activity (g2gl-compensation-handler
                     g2gl-handler 16
                     (connections-configuration local-handler)
                     (stubs))                ; no default stubs
    (:funcall-at-load-time
      create-g2-bpel-activity-icon-description compensation-handler)
  ((compilations-of-outside-variables-used-in-body
     outside-variables (c-only reclaimable)))
  (activity-execution-code
    (instantiate-g2gl-body-compilation-and-start-execution
      (g2gl-body-compilation c) nil thread f)
    ;; -- now exit (with thread, whose execution-thread-state is the symbol
    ;; abnormal, now inactive, "pushed down", and waiting to be deleted after
    ;; completion of the execution of the body compilation of c)
    (exit-g2gl-process)))


(def-g2gl-activity (g2gl-alarm-event-handler
                     g2gl-event-handler 17
                     (connections-configuration alien)
                     (stubs))                ; no default stubs
    (:funcall-at-load-time
      create-g2-bpel-activity-icon-description alarm-event-handler)
  ((duration-or-deadline-expression
     e (a-only required-non-nil-value)
     (type g2gl-deadline-expression text))
   ;; type may be either DEADLINE-EXPRESSION or DURATION-EXPRESSION:
   (type-of-g2gl-alarm-time-expression
     type
     (required-non-nil-value
       carried-over-to-c
       symbol
       (initial-value duration-expression))
     (type g2gl-duration-type)))
  (activity-execution-code
    (when (null (execution-thread-state thread))
      (loop for related-thread
                in (g2gl-execution-threads f)
            when (and (eq (parent-execution-thread related-thread)
                          (parent-execution-thread thread))
                      (thread-is-in-instantiation-triggering-head-of-flowchart
                        related-thread
                        (flowchart-entry-activity-compilation
                          (body-compilation-this-is-being-used-to-execute
                            related-thread))))
              do (schedule-g2gl-execution-thread thread nil)
                ;; -- this prevents c from being executed before an
                ;; instantiation trigger receive or pick activity compilation
                ;; has been executed, as required in BPEL
                 (exit-g2gl-process))
      #+development
      (assert-for-development
        (memq type '(duration-expression deadline-expression)))
      (let* ((alarm-time
               (if (eq type 'duration-expression)
                   (+e (g2gl-get-current-time)
                       (coerce-to-gensym-float expression-value))
                   ;; else: must be DEADLINE-EXPRESSION
                   (coerce-to-gensym-float expression-value))))
        (setf (execution-thread-state-parameter thread)
              (allocate-managed-float alarm-time))
        (setf (execution-thread-state thread) 'waiting)))
    (cond
      ((and (eq (execution-thread-state thread) 'waiting)
            (g2gl-current-time-<
              (managed-float-value
                (execution-thread-state-parameter thread))))
       (schedule-g2gl-execution-thread
         thread
         (managed-float-value (execution-thread-state-parameter thread))))
      ((eq (execution-thread-state thread) 'waiting)
       (setf (execution-thread-state thread) 'executing-body)
       (reclaim-managed-float (execution-thread-state-parameter thread))
       (setf (execution-thread-state-parameter thread) nil)
       (instantiate-g2gl-body-compilation-and-start-execution
         (g2gl-body-compilation c) nil thread f))
      (t  ;state was EXECUTING-BODY, i.e. we're done
       (setf (execution-thread-state thread) nil)
       (delete-g2gl-execution-thread thread nil t)))
    (exit-g2gl-process)))



;; Slot name changed, for classes g2gl-wait and g2gl-alarm-event-handler, in
;; spec some time ago, but only today (post 8.1b0) in the implementation on the
;; main line. (MHD 4/12/05)

(def-absent-slot-putter type-of-g2gl-expression-in-wait-activity
    (wait-or-alarm-event-handler value)
  (setf (type-of-g2gl-alarm-time-expression wait-or-alarm-event-handler)
        value))





;;; The grammar category `g2gl-duration-type' has a surface grammar allowing
;;; either of the symbols DURATION-EXPRESSION or DEADLINE-EXPRESSION.
;;; Internally, those same symbols are stored as the value.

(def-grammar-category g2gl-duration-type ()
   ('duration-expression)
   ('deadline-expression))



(def-g2gl-activity (g2gl-message-event-handler
                     g2gl-event-handler 18
                     (connections-configuration alien)
                     (stubs)                ; no default stubs
                     (attribute-displays
                       ((g2gl-operation-name) at-standard-position)))
    (:funcall-at-load-time
      create-g2-bpel-activity-icon-description message-event-handler)
  ((g2gl-partner-link-variable-name
     partner-link-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-partner-link-variable-name?)
     (no-accessor))
   (g2gl-partner-link-variable
     partner-link-variable
     (c-only)
     (no-accessor))
   (g2gl-port-type
     port-type
     (carried-over-to-c (initial-value nil))
     (type g2gl-port-type-name)
     (no-accessor))
   (g2gl-operation-name
     operation-name
     (required-non-nil-value carried-over-to-c (initial-value nil))
     (type g2gl-operation-name?)
     (no-accessor))
   (g2gl-correlations
     correlations
     (a-only)
     (type g2gl-correlations)
     (no-accessor))
   (c-g2gl-correlations
     c-correlations
     (c-only reclaimable-at-both-levels)
     (no-accessor))
   (g2gl-message-variable-name
     output-variable-name
     (a-only required-non-nil-value (initial-value nil))
     (type g2gl-message-variable-name?)
     (no-accessor))
   (g2gl-message-variable
     output-variable
     (c-only)
     (no-accessor)))
  (activity-execution-code
    (let* (result sp sibling-thread)
      (when (not (eq (execution-thread-state thread) 'executing-body))
        (setq result
              (look-for-g2gl-message-transmission
                thread partner-link-variable port-type operation-name
                c-correlations output-variable nil))
        (when (null result)
          (when (null (execution-thread-state thread))
            (setf (execution-thread-state thread) 'in-partner-link)
            (setf (execution-thread-state-parameter thread)
                  (get-value-of-g2gl-variable partner-link-variable f)))
          (exit-g2gl-process))
        (when (eq (execution-thread-state thread) 'in-partner-link)
          (setq sp (execution-thread-state-parameter thread))
          (setf (threads-located-at-receiving-activity-compilations sp)
                (delete-gensym-element
                  thread
                  (threads-located-at-receiving-activity-compilations sp)))
          (setf (execution-thread-state thread) nil)
          (setf (execution-thread-state-parameter thread) nil))
        (when (not (eq result 'success))        ; -- if so, must be a fault
          (signal-g2gl-execution-fault thread result)
          (exit-g2gl-process))
        (setq sibling-thread
              (make-g2gl-execution-thread
                c nil nil parent-thread thread
                (body-compilation-this-is-being-used-to-execute thread)
                f))
        (setf (execution-thread-state sibling-thread) 'executing-body)
        ;; -- [the thread token for sibling-thread needs to be specially
        ;; positioned, since there already will be one at the standard position as
        ;; well as possibly others for threads like this at nearby non-standard
        ;; positions; worse, there must be separate G2GL variable binding
        ;; environments for each dispatched body execution of c, to be consistent
        ;; with WS-BPEL, or else a fault-handler-like invocation of the body
        ;; compilation of c together with constraints on the use of G2GL variables
        ;; bound outside the body!]
        (instantiate-g2gl-body-compilation-and-start-execution
          (g2gl-body-compilation c) nil sibling-thread f)
        (schedule-g2gl-execution-thread thread nil)
        (exit-g2gl-process)))))





(def-g2gl-activity (g2gl-assign g2gl-activity 19)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description assign)
  ((g2gl-assignments
     e (a-only required-non-nil-value) (type g2gl-assignment-expression text)))
  (activity-compilation-code
    (when e
      (setf (g2gl-expression-compilation c)
            (compile-g2gl-expression (car e) 'assignments a b v)))))


;;; The grammar category `g2gl-assignment-expression' ... used for the
;;; G2GL-ASSIGN activity's g2gl-assignments attribute.

(def-grammar-list-category g2gl-assignment-expression
    (single-g2gl-assignment-expression)
  :separator \; :empty-list-symbol none)

;; Note: at present this has a few minor bugs: (1) you start out with NIL as the
;; value, but it doesn't show what's supposed to be the corresponding text
;; "none"; (2) once you've entered an expression, you can't type in blank (and
;; have it be parsed) to get back to the original text and value; (3) you can
;; type in none to get the original value, i.e., nil, but when you click on
;; "none", it doesn't clear the text in the editor like most slots with none do
;; (a normal limitation of text type slots, I believe, but somewhat
;; disconcerting to users, I believe). (MHD 12/1/04)


;;; Single-g2gl-assignment-expression is for now closely patterned after G2
;;; procedure assignment statements.  In fact, the grammar used for the
;;; right-side expression is exactly that used in procedures, i.e.,
;;;
;;;   <proc-assignment-statement> ::=
;;;     <local-name> = <g2gl-untyped-expression>

(def-grammar-category single-g2gl-assignment-expression ()
  ((g2gl-place-reference-with-source-position
     =-with-source-position
     g2gl-untyped-expression-with-source-position)
   (assignment-statement 1 2 3)
   reduce-noting-source-position))        ; needed for saving LHS/RHS for export

(def-grammar-category g2gl-place-reference-with-source-position ()
  (g2gl-designation 1 reduce-noting-source-position))

(def-grammar-category =-with-source-position ()
  ('= 1 reduce-noting-source-position))

(def-grammar-category g2gl-untyped-expression-with-source-position ()
  (g2gl-untyped-expression 1 reduce-noting-source-position))

(def-grammar-category g2gl-untyped-expression ()
  (g2gl-new-message-expression)
  (g2gl-expression)
  (g2gl-logical-expression))

(def-grammar-category g2gl-new-message-expression ()
  (('new g2gl-message-class)))

(def-registered-directory-of-names g2gl-message-class)

(def-grammar-category g2gl-message-class ()
  (unreserved-symbol))

(def-grammar-category g2gl-expression ()
  (g2gl-sum)
  (g2gl-format-form))

(def-grammar-category g2gl-sum ()
  ((g2gl-term-or-signed-term '+ g2gl-sum-1) (+ 1 3) transpose-sum)
  ((g2gl-term-or-signed-term '- g2gl-sum-1) (- 1 3) transpose-sum)
  (g2gl-term-or-signed-term))

(def-grammar-category g2gl-term-or-signed-term ()
  (g2gl-term)
  (g2gl-signed-term))

(def-grammar-category g2gl-signed-term ()
  (('+ g2gl-term) 2)
  (('- g2gl-term) (- 2)))

(def-grammar-category g2gl-sum-1 ()
  ((g2gl-term '+ g2gl-sum-1) (|+plus+| 1 3))
  ((g2gl-term '- g2gl-sum-1) (|-minus-| 1 3))
  (g2gl-term))

(def-grammar-category g2gl-term ()
  ((g2gl-exponential '* g2gl-term-1) (* 1 3) transpose-term)
  ((g2gl-exponential '/ g2gl-term-1) (/ 1 3) transpose-term)
  (g2gl-exponential))

(def-grammar-category g2gl-term-1 ()
  (g2gl-exponential)
  ((g2gl-exponential '* g2gl-term-1) (|*times*| 1 3))
  ((g2gl-exponential '/ g2gl-term-1) (|/slash/| 1 3)))

(def-grammar-category g2gl-exponential ()
  ((g2gl-factor '^ g2gl-factor) (^ 1 3))
  (g2gl-factor))



;;; A `G2GL funcall' is G2GL's analog of the special functional form
;;; CALL-FUNCTION in G2.  The surface syntax is:
;;;
;;;   CALL-FUNCTION (arg-1 [, arg-2, ..., arg-n])
;;;
;;; where arg-1 is an expression that is evaluated (here, using the G2GL
;;; evaluator), and, to be valid, must result in a user-defined function, a G2
;;; item of class function-definition, tabular-function, or
;;; foreign-function-declaration, and where args-2 through arg-n are G2GL
;;; expressions to be evaluated and passed in as args 0 through (n - 2) of
;;; the function.
;;;
;;; Internally, this is parsed as a special form that will end up looking like
;;;
;;;   (G2GL-FUNCALL . args)
;;;
;;; be rather unspecially handled in the G2GL expression compiler (just like any
;;; other n-ary operator), and then specially dispatched to in the evaluator for
;;; the g2gl-funcall case.

;;; Note that CALL-FUNCTION has several internal uses, both in G2's function
;;; calling mechanism and grammar and in that of G2GL, so it's important to try
;;; to avoid confusing those uses with those of the g2gl-funcall mechanism.

(def-concept g2gl-funcall)

;; Support for g2gl-funcall ("CALL-FUNCTION") was first introduced in G2 8.2r1,
;; whereas support for function expressions generally was first introduced for
;; G2GL in G2 8.2r0. (MHD 3/10/06)

;; Note: several limitations, some of G2 and some of G2GL, combine to make it
;; rather difficult to actually use g2gl-funcall: (a) only for user-defined
;; functions -- not usable with built-in functions (G2); (b) only for actual
;; function instances of user-defined functions, not names thereof (G2); (c) you
;; cannot evaluate a user-defined function's name in an expression (G2GL, since
;; you cannot reference any item by its (global) name); (d) it's inconvenient to
;; get a function instance by name (G2GL -- to set a variable to be bound to a
;; function instance, you have to assign the variable in a special G2GL-CALL
;; activity by calling a procedure that returns the instance; there are other
;; means, but generally not much better; c.f., G2 expressions). (MHD 3/10/06)


(def-grammar-category g2gl-factor ()
  (('\( g2gl-conditional-expression '\)) 2)

  ((function-name '\( '\))
   (1)
   reject-if-g2gl-funcall               ; rejects CALL-FUNCTION(...)
   check-number-of-args                 ; rejects STRUCTURE(...)
   reject-if-sequence-constant          ; rejects SEQUENCE(...)
   to-g2gl-function-phrase)
  ((function-name '\( g2gl-function-arguments '\))
   (1 . 3)
   remove-noise-and-reject-if-g2gl-special-form
   reject-if-g2gl-funcall               ; rejects CALL-FUNCTION(...)
   check-number-of-args                 ; rejects STRUCTURE(...)
   reject-if-sequence-constant          ; rejects SEQUENCE(...)
   to-g2gl-function-phrase)

  (('call-function '\( g2gl-function-arguments '\))
   (1 . 3)
   remove-noise-and-reject-if-g2gl-special-form
   check-number-of-args-for-g2gl-funcall) ; => (G2GL-FUNCALL . 3)

  (('structure '\( g2gl-structure-argument-list '\))
   (evaluated-structure . 3)
   reject-if-structure-constant
   to-g2gl-function-phrase)

  (('the 'current 'time) (current-time))
  (('the 'current 'real 'time) (current-real-time))
  (('the 'current 'subsecond 'time) (current-subsecond-time))
  (('the 'current 'subsecond 'real 'time) (current-subsecond-real-time))
  (('the 'current 'system 'time) (current-system-time))
  (('the 'current 'system 'real 'time) (current-system-real-time))
  (('the 'current 'year) (call-function year (current-time)))
  (('the 'current 'month) (call-function month (current-time)))
  (('the 'current 'day 'of 'the 'month)
   (call-function day-of-the-month (current-time)))
  (('the 'current 'day 'of 'the 'week)
   (call-function day-of-the-week (current-time)))
  (('the 'current 'hour) (call-function hour (current-time)))
  (('the 'current 'minute) (call-function minute (current-time)))
  (('the 'current 'second) (call-function second (current-time)))

  ;; New - HQ-5093336 "G2GL: process thread management" (MHD 9/11/05)
  (('this 'process 'instance) (this-g2gl-process-instance))
  ;; New - extension - "this process" => (source) G2GL-process
  (('this 'process) (this-g2gl-process))

  (g2gl-designation)
  (g2gl-constant)

  ;; new for G2 8.2r0: xxx[i] - to refer to the ith element of xxx a G2GL
  ;; sequence:   (MHD 12/2/05)
  (g2gl-nth-element-designation))



(defun reject-if-g2gl-funcall (function-and-args)
  (if (eq (car-of-cons function-and-args) 'call-function)
      bad-phrase
      function-and-args))

(defun check-number-of-args-for-g2gl-funcall (function-form)
  (let* ((args (cdr function-form))
         (n-args (length args)))
    (cond
      ((<f n-args 1)
       (values bad-phrase 'too-few-arguments))
      (t
       (phrase-cons 'g2gl-funcall args)))))


(defun remove-noise-and-reject-if-g2gl-special-form (x)
  ;; FIX TO CHECK FOR SPECIAL FORMS!! (MHD 10/19/05)
  (phrase-cons (car x) (remove-noise-at-head-of-list-phrase (cdr x))))


(def-grammar-category g2gl-structure-argument-list ()
  ((symbol '\: g2gl-untyped-expression)
   ((quote 1) 3))
  ((symbol '\: g2gl-untyped-expression '\, g2gl-structure-argument-list)
   ((quote 1) 3 . 5)))


(def-grammar-list-category g2gl-function-arguments (g2gl-untyped-expression)
  :separator \,)


(def-grammar-category g2gl-conditional-expression ()
  (g2gl-expression)
  (g2gl-unique-conditional-expression))

(def-grammar-category g2gl-unique-conditional-expression ()
  (g2gl-unique-expression)
  (('if g2gl-logical-expression 'then g2gl-expression 'else g2gl-conditional-expression)
   (if-expression 2 4 6))
  (('if g2gl-logical-expression 'then g2gl-expression)
   (if-expression 2 4)))





(defun to-g2gl-function-phrase (g2-function-phrase)
  ;; (fn . , args) => (CALL-FUNCTION fn . args)
  (phrase-cons 'call-function g2-function-phrase))


(def-grammar-category g2gl-designation ()
  (('the attribute-name 'of g2gl-designation) (the 2 4))
  (('the class '|::| attribute-name 'of g2gl-designation)
   (the (class-qualified-name 2 4) 6))
  (g2gl-variable-name))

(def-grammar-category g2gl-nth-element-designation ()
  (('\( g2gl-nth-element-designation '\) g2gl-subscript-expression)
   (nth-element 2 4))
  (('\( g2gl-designation '\) g2gl-subscript-expression)
   (nth-element 2 4))
  ((g2gl-variable-name g2gl-subscript-expression)
   (nth-element 1 2)))

(def-grammar-category g2gl-subscript-expression ()
  (g2gl-bracketed-expression)
  ((g2gl-subscript-expression g2gl-bracketed-expression)
   (1 . 2)))

(def-grammar-category g2gl-bracketed-expression ()
  (('\[ g2gl-expression '\]) (1 2)))

(def-grammar-category g2gl-constant ()
  (number)
  (whole-string)
  ('true (1) transform-to-g2gl-true)
  ('false (1) transform-to-g2gl-false)
  (('the 'symbol symbol) (quote 3))
  (quantity-interval)
  (g2gl-sequence)
  (g2gl-structure))


;; For the 8.2a0 prerelease, good enough to define g2gl-sequence and
;; g2gl-structure just in terms of the general sequence and structure grammar
;; categories.  However, that could lead to non-g2gl-data types.  To remedy, we
;; must at a minimum trap and/or filter out such data. Alternatively, can
;; eliminate any and all discrepencies.  I think the major one after this will
;; just be fuzzy truth values.  Probably we should just support that data type
;; fully -- what harm does that do?! (MHD 9/12/05)

(def-grammar-category g2gl-sequence ()
  (sequence))

(def-grammar-category g2gl-structure ()
  (structure))


(def-grammar-category g2gl-logical-expression ()
  ((g2gl-unique-disjunct 'or g2gl-unique-logical-expression)
   (or 1 3)
   simplify-associative-operation)
  (g2gl-disjunct))

(def-grammar-category g2gl-unique-logical-expression ()
  ((g2gl-unique-disjunct 'or g2gl-unique-logical-expression)
   (or 1 3)
   simplify-associative-operation)
  (g2gl-unique-disjunct))

(def-grammar-category g2gl-disjunct ()
  ((g2gl-conjunct 'and g2gl-disjunct)
   (and 1 3)
   simplify-associative-operation)
  (g2gl-conjunct))

(def-grammar-category g2gl-conjunct ()
  (g2gl-unique-literal))

(def-grammar-category g2gl-unique-disjunct ()
  ((g2gl-unique-conjunct 'and g2gl-unique-disjunct)
   (and 1 3)
   simplify-associative-operation)
  (g2gl-unique-conjunct))

(def-grammar-category g2gl-unique-conjunct ()
  (g2gl-unique-literal))

(def-grammar-category g2gl-unique-literal ()
  ((g2gl-expression g2gl-comparator g2gl-expression)
   (2 1 3))
  (g2gl-designation)
  ((g2gl-expression 'has 'a 'value)
   (has-value-p 1))
  ((g2gl-expression 'has 'no 'value)
   (has-no-value-p 1))
  ('true (1) transform-to-g2gl-true)
  ('false (1) transform-to-g2gl-false)
  (('\( g2gl-logical-expression '\)) 2)
  (('\( 'if g2gl-unique-logical-expression
        'then g2gl-unique-logical-expression
        'else g2gl-unique-logical-expression '\))
   (if-expression 3 5 7))
  (('\( 'if g2gl-unique-logical-expression
        'then g2gl-unique-logical-expression '\))
   (if-expression 3 5))
  (('not '\( g2gl-unique-logical-expression '\))
   (not 3)))

(defun transform-to-g2gl-true (template)
  (declare (ignore template))
  (copy-for-phrase g2gl-true))

(defun transform-to-g2gl-false (template)
  (declare (ignore template))
  (copy-for-phrase g2gl-false))

(def-grammar-category g2gl-comparator ()
  ('=)
  ('/=)
  ('<)
  ('<=)
  ('>)
  ('>=))


;;; The grammar category `g2gl-format-form' handles the concatenation operator,
;;; i.e. brackets inside a string constant: the expression "foo [1+2] bar" is
;;; parsed as (format-form #w"foo " (+ 1 2) #w" bar").

(def-grammar-category g2gl-format-form ()
  ((left-string g2gl-open-format-expression)
   (format-form 1 2) simplify-associative-operation))

(def-grammar-category g2gl-open-format-expression ()
  ((g2gl-format-expression right-string)
   (format-form 1 2) simplify-associative-operation)
  ((g2gl-format-expression g2gl-format-expression-tail)
   (format-form 1 2) simplify-associative-operation))

(def-grammar-category g2gl-format-expression-tail ()
  ((middle-string g2gl-open-format-expression)
   (format-form 1 2) simplify-associative-operation))

(def-grammar-category g2gl-format-expression ()
  (g2gl-expression))




;;; The `slot-value compiler for g2gl-assignment-expression' gets a "noisy"
;;; parse result, and first of all applies remove-noise-at-head-of-list-phrase
;;; to it, resulting in new-parse-reseult, which then is of the form
;;;
;;;    ( { (SOURCE-POSITION
;;;          (ASSIGNMENT-STATEMENT
;;;            (SOURCE-POSITION <variable name> . <source position>))
;;;            (SOURCE-POSITION = . <source position>)
;;;            (SOURCE-POSITION <value expression> . <source position>)))
;;;      } )
;;;
;;; We want to change it to
;;;
;;;    ( { (ASSIGNMENT-STATEMENT <variable name> <value expression>
;;;         . <text string with value expression text> ) } )
;;;
;;; where <text string with value expression text> is a text string with the
;;; text of the right-hand-side value expression, starting immediately after the
;;; equal sign (=), and continuing until the semicolon (;) or the end of text.
;;;
;;; For example, the expression text
;;;
;;;   ok-status = the symbol yes;
;;;   is-freezing = {in fahrenheit: } temperature <= 32
;;;
;;; results in the following compilation result:
;;;
;;;   ((assignment-statement ok-status (quote yes) . #w" the symbol yes")
;;;    (assignment-statement
;;;      is-freezing (<= temperature 32)
;;;      . #w" {in fahrenheit: } temperature <= 32")))
;;;
;;; The purpose of all this is to make it easy to emit the text of the value
;;; expressions in G2GL syntax as the expression part of a BPEL XML <assign>
;;; activity.  E.g., the above example should get exported to something like:
;;;
;;;  <assign>
;;;   <copy><from expression=" the symbol yes"/><to variable="okStatus"/></copy>
;;;   <copy><from expression=" {in fahrenheit:} temperature &lt;= 32"/>
;;;    <to variable="isFreezing"/></copy>
;;;  </assign>

(def-slot-value-compiler g2gl-assignment-expression (parse-result)
  (let ((new-parse-result (remove-noise-at-head-of-list-phrase parse-result)))
    (loop for (nil (key
                     (nil variable-name . nil)
                     (nil nil . value-expression-start-position)
                     (nil value-expression . value-expression-end-position)))
              in new-parse-result
          collect (nconc
                    (phrase-list key variable-name)
                    (phrase-cons
                      value-expression
                      (text-string-from-current-source
                        value-expression-start-position
                        value-expression-end-position)))
            using phrase-cons)))

;;; Accessors for the parts of an assignment expression translation.

;;; Returns a symbol for a variable, or a list '(the x y) for the x attribute of
;;; variable y.
(defun g2gl-assignment-expression-designation (expression)
  (cadr expression))

;;; Returns a symbol.
(defun g2gl-assignment-expression-variable (expression)
  (let ((designation (g2gl-assignment-expression-designation expression)))
    (if (consp designation) (third designation) designation)))

;;; Returns a symbol or nil.
(defun g2gl-assignment-expression-part (expression)
  (let ((designation (g2gl-assignment-expression-designation expression)))
    (if (consp designation) (second designation) nil)))

;;; Returns a value expression parse tree.
(defun g2gl-assignment-expression-value-expression (expression)
  (caddr expression))

;;; Returns a text string.
(defun g2gl-assignment-expression-value-expression-text-string (expression)
  (cdddr expression))






(def-g2gl-activity (g2gl-throw g2gl-activity 20)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description throw)
  ((fault-name-for-throw
     fault-name
     ;; Note: required-non-nil-value is not in the detailed spec at this time,
     ;; but I believe it's consistent with BPEL and with the high-level spec
     ;; (which does not flag this as an extension), and seems most appropriate
     ;; to fix HQ-5027368 "G2GL: sample g2gl-process aborts G2 during
     ;; execution". (MHD 5/5/05)
     (carried-over-to-c symbol required-non-nil-value)
     (type g2gl-fault-name?))
   (fault-data-g2gl-variable-name
     fault-data-variable-name
     (a-only)
     (type g2gl-arg-or-non-arg-variable-name))
   (fault-data-g2gl-variable
     fault-data-variable
     (c-only)))
  (activity-compilation-code
    (when fault-data-variable-name
      (set-acs
        fault-data-variable
        (get-g2gl-variable-compilation
          fault-data-variable-name nil nil a b v))))
  (activity-execution-code
    (let ((fault-data
            (if fault-data-variable
                (add-reference-to-g2gl-value
                  (get-value-of-g2gl-variable fault-data-variable f)))))
      (signal-g2gl-user-fault thread fault-name fault-data)
      (exit-g2gl-process))))


(def-grammar-category g2gl-arg-or-non-arg-variable-name ()
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-arg-or-non-arg-variable-name)

(def-slot-value-compiler g2gl-arg-or-non-arg-variable-name (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-writer g2gl-arg-or-non-arg-variable-name (value)
  (twrite-symbol-or-none value))

(def-g2gl-activity (g2gl-wait g2gl-activity 21)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description wait)
  ((duration-or-deadline-expression
     e
     (a-only required-non-nil-value)
     (type g2gl-deadline-expression text))
   ;; type may be either DEADLINE-EXPRESSION or DURATION-EXPRESSION:
   (type-of-g2gl-alarm-time-expression
     type
     (required-non-nil-value
       carried-over-to-c
       symbol
       (initial-value duration-expression))
     (type g2gl-duration-type)))
  (activity-compilation-code
    (when e
      (setf (g2gl-expression-compilation c)
            (compile-g2gl-expression (car e) type a b v))))
  (activity-execution-code
    (with-temporary-gensym-float-creation g2gl-wait
        (when (null (execution-thread-state thread))
          (let* ((deadline-or-duration-as-gensym-float
                   (cond
                     ((gensym-float-p expression-value)
                      expression-value)
                     ((managed-float-p expression-value)
                      (prog1 (managed-float-value expression-value)
                        (remove-reference-to-g2gl-value expression-value)))
                     ((fixnump expression-value)
                      (coerce-fixnum-to-gensym-float expression-value))
                     (t
                      (g2gl-eval-expression-error
                        'non-numeric-value
                        (twrite-g2gl-value expression-value)))))
                 (alarm-time
                   (+e (if (eq type 'duration-expression)
                           (g2gl-get-current-time)
                           ;; else: type = DEADLINE-EXPRESSION
                           0.0)
                       deadline-or-duration-as-gensym-float)))
            (setf (execution-thread-state-parameter thread)
                  (allocate-managed-float alarm-time))
            (setf (execution-thread-state thread) 'waiting)))
      (cond
        ((and (eq (execution-thread-state thread) 'waiting)
              (g2gl-current-time-<
                (managed-float-value
                  (execution-thread-state-parameter thread))))
         (schedule-g2gl-execution-thread
           thread
           (managed-float-value
             (execution-thread-state-parameter thread)))
         (exit-g2gl-process))
        (t
         (reclaim-managed-float
           (execution-thread-state-parameter thread))
         ;; -- check w/LH -- not mentioned in spec!
         (setf (execution-thread-state thread) nil))))))



;; The grammar category `g2gl-deadline-expression' provides an expression that
;; should evaluate to a number (float or integer) in the duration case, and a
;; float, i.e., a valid unix time, in the case of a deadline.  The duration case
;; corresponds to a G2 "interval", while the deadline case corresponds to a G2
;; "time stamp".  At present, this is implemented as a general expression, but
;; it should ideally be improved to only be a numeric type of expression.  Also,
;; ideally, it should allow a time-stamp or interval expression to be directly
;; entered, e.g., <n> minutes <m> seconds.

(def-grammar-category g2gl-deadline-expression ()
  (g2gl-expression))


(def-grammar-category g2gl-duration-type ()
  ('deadline-expression)
  ('duration-expression))

(def-slot-value-writer g2gl-duration-type (value)
  (twrite-symbol value))





(def-g2gl-activity (g2gl-compensate g2gl-activity 22)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description compensate)
  ((scope-name-for-compensate-activity
     scope-name (carried-over-to-c symbol) (type g2gl-scope-name)))
  ;; TO DO: at compile time, check that the named scope exists
  (activity-execution-code
    (let ((thread-at-handler-compilation thread))
      (loop until (or (null thread-at-handler-compilation)
                      (=f (g2gl-activity-class-code
                            (activity-compilation-to-execute
                              thread-at-handler-compilation))
                          (quoted-g2gl-activity-class-code g2gl-fault-handler))
                      (=f (g2gl-activity-class-code
                            (activity-compilation-to-execute
                              thread-at-handler-compilation))
                          (quoted-g2gl-activity-class-code
                            g2gl-compensation-handler)))
            do (setq thread-at-handler-compilation
                     (parent-execution-thread thread-at-handler-compilation)))
      (when (null thread-at-handler-compilation)
        ;; TO DO: this should be a compile-time error!
        (signal-g2gl-system-fault thread 'compensate-activity-illegal-here)
        (exit-g2gl-process))                ; EXIT ADDED --MHD, 3/31/05
      (when (schedule-g2gl-compensation-if-necessary
              thread-at-handler-compilation scope-name thread nil f)
        ;; Thread is now parked in a thread at an activity being compensated,
        ;; which itself is parked in a scheduled compensation handler thread.
        (exit-g2gl-process)))))



(def-grammar-category g2gl-scope-name ()
  ('none nil)
  (unreserved-symbol))

(def-registered-directory-of-names g2gl-scope-name)

(def-slot-value-writer g2gl-scope-name (value)
  (twrite-symbol-or-none value))





(def-g2gl-activity (g2gl-empty g2gl-activity 23)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description empty)
  ()
  (activity-execution-code))



(def-g2gl-activity (g2gl-do g2gl-activity 24)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description do)
  ((g2gl-statements
     e
     (a-only required-non-nil-value)
     ;; We use g2gl-return-expression. It has the same syntax, and while the
     ;; values are ignored, I cannot see any real cost to reusing this. (MHD)
     (type g2gl-do-expression text)))
  (activity-compilation-code
    (when e
      (setf (g2gl-expression-compilation c)
            (compile-g2gl-expression (car e) 'do-expression a b v))))
  (activity-execution-code))




;;; The grammar category `g2gl-do-expression' ... used for the G2GL-DO
;;; activity's g2gl-values-expression attribute.
;;;
;;; Basically, the user types in a semicolon-separated list of statement
;;; expressions, e.g.,
;;;
;;;   foo = the foo of bar;
;;;   the xyz of abc = 123;
;;;   conclude that the foo of bar = baz
;;;
;;; At present, the only kinds of statements are assignment and conclude
;;; statements.

;; Future consideration: ultimately, there could be many more kinds of
;; statements, e.g., for all the G2 actions, e.g., post, show, create, etc., and
;; conditionals, e.g., if ..., unless ..., etc., and even loops, quantifiers,
;; etc.

(def-grammar-list-category g2gl-do-expression (g2gl-statement)
  :separator \; :empty-list-symbol none)

(def-grammar-category g2gl-statement ()
  (g2gl-assignment-statement)
  (g2gl-conclude-statement))

(def-grammar-category g2gl-assignment-statement ()
  ((g2gl-designation '= g2gl-untyped-expression)
   (assignment-statement 1 3)))

(def-grammar-category g2gl-conclude-statement ()
  (('conclude 'that g2gl-designation '= g2gl-untyped-expression)
   (conclude-statement 3 5)))


(def-slot-value-compiler g2gl-do-expression (parse-result)
  (remove-noise-at-head-of-list-phrase parse-result))



;; Note: 25 used below. (removed START)

;; Removed g2gl-start post 8.1b0, pre 8.1r0. (MHD 4/22/05)

(def-substitute-for-old-class g2gl-start g2gl-empty
  (+ g2-version-8-1-beta-0-kb-flags 1))





(def-g2gl-activity (g2gl-return
                     g2gl-activity 26
                     (connections-configuration end)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 50)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description return)
  ((g2gl-values-expression e (a-only) (type g2gl-return-expression text)))
  (activity-compilation-code
    (when e
      (setf (g2gl-expression-compilation c)
            (compile-g2gl-expression (car e) 'values-expression a b v))))
  (activity-execution-code
    (when expression-value
      (cond
        ((parked-process-invocation-thread f)
         (setf (process-invocation-result
                 (parked-process-invocation-thread f))
               expression-value))
        (t
         (reclaim-g2gl-values expression-value))))
    (exit-g2gl-process-instance f t)
    (exit-g2gl-process)))



;;; The grammar category `g2gl-return-expression' ... used for the G2GL-RETURN
;;; activity's g2gl-values-expression attribute.
;;;
;;; Basically, the user types in a comma-separated list of expressions, e.g.,
;;;
;;;   foo, a + b, a + b > 0
;;;
;;; "None" stands for "return no values".

(def-grammar-list-category g2gl-return-expression (g2gl-expression)
  :separator \, :empty-list-symbol none)

;; Note: at present this category has the same minor bugs essentially as for
;; g2gl-assignment-expression, q.v. (MHD 12/1/04)

(def-slot-value-compiler g2gl-return-expression (parse-result)
  (remove-noise-at-head-of-list-phrase parse-result))









(def-g2gl-activity (g2gl-break g2gl-activity 27)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description breakpoint)
  ()
  (activity-execution-code
    (cond
      ((null (execution-thread-state thread))
       (make-and-put-up-individual-execution-display-if-necessary thread)
       (effect-g2gl-breakpoint
         thread
         (copy-text-string "breakpoint at break activity")
         nil)
       (exit-g2gl-process))
      (t
       ;; Here the execution-thread-state of thread is the symbol at-breakpoint
       ;; and the execution-thread-state-parameter of thread is a list
       ;; consisting of just the symbol ready-to-proceed, since all other
       ;; possibilities will have been dealt with in the previous step and
       ;; earlier.
       #+development
       (unless (and (eq (execution-thread-state thread) 'at-breakpoint)
                    (listp (execution-thread-state-parameter thread))
                    (eq (car (execution-thread-state-parameter thread))
                        'ready-to-proceed))
         (cerror
           "continue anyhow"
           "in g2gl-break execution: execution thread state is wrong!"))
       (reclaim-gensym-list
         (execution-thread-state-parameter thread))
       (setf (execution-thread-state-parameter thread) nil) ; not strictly nec.
       (setf (execution-thread-state thread) nil)))))



(def-g2gl-activity (g2gl-exit
                     g2gl-activity 28
                     (connections-configuration end))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description exit)
  ()
  (activity-execution-code
    (exit-g2gl-process-instance f nil)
    (exit-g2gl-process)))                ; "exit"

(def-substitute-for-old-class g2gl-terminate g2gl-exit
  (+ g2-version-8-1-beta-0-kb-flags 1))

;; G2GL-terminate was renamed G2GL-exit today.  Note that terminate is the BPEL
;; 1.1 name, while exit is the 2.0 name for the same activity.  Although we
;; don't have the final draft of 2.0 at this time, it seems this renaming will
;; stick.  (MHD 3/12/05)



;; Note: 29 used below. (previously used for SEQUENCE, obsolete). (MHD 10/14/05)

;; actually, there's no explicit sequence activity in G2GL, removing:  (MHD 3/16/05)
;(def-g2gl-activity (g2gl-sequence g2gl-activity 29)
;    (:funcall-at-load-time create-g2-bpel-activity-icon-description sequence)
;  ())

(def-substitute-for-old-class g2gl-sequence g2gl-empty
  (+ g2-version-8-1-beta-0-kb-flags 1))



(def-g2gl-activity (g2gl-call g2gl-activity 30)
    (:funcall-at-load-time create-g2-bpel-activity-icon-description call)
  ((g2gl-procedure-call-statement
     e
     (a-only required-non-nil-value)
     (type g2gl-call-statement-expression text)))
  (activity-compilation-code
    (when e
      (setf (g2gl-expression-compilation c)
            (compile-g2gl-expression (car e) 'call a b v))))
  (activity-execution-code
    (cond
      ((null (execution-thread-state thread))
       ;; Expression-value is normally the result of g2gl-do-call, q.v.
       (let ((invoc expression-value))
         (setf (execution-thread-state thread) 'in-procedure)
         (setf (execution-thread-state-parameter thread) invoc)
         (setf (thread-parked-on-g2gl-call invoc) thread) ; used upon completion
         (exit-g2gl-process)))
      (t
       ;; if here, presumably, the state of thread is IN-PROCEDURE
       (setf (execution-thread-state thread) nil)
       (when (execution-thread-state-parameter thread)
         ;; may be fault case: parameter can be a g2gl-execution-fault structure
         (let ((fault-or-other (execution-thread-state-parameter thread)))
           (setf (execution-thread-state-parameter thread) nil)
           (when (g2gl-execution-fault-p fault-or-other)
             (signal-g2gl-execution-fault thread fault-or-other))
           (exit-g2gl-process)))))))






(def-g2gl-activity (g2gl-flow-discriminator
                     g2gl-flow-join 15
                     (connections-configuration rejoin)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 67)
                       #.(g2gl-standard-connection-stub 'input 'top 133)
                       #.(g2gl-standard-connection-stub 'output 'bottom 100)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description flow-discriminator)
  ((number-of-rejoining-branches n (c-only integer))
   (g2gl-flow-discriminator-scope-marker marker (c-only)))
  (activity-compilation-code
    (set-acs n (g2gl-activity-in-connection-count a))
    (set-acs
      marker
      (get-g2gl-flow-scope-marker a stack)))
  (activity-execution-code
    (if (eq (g2gl-flow-discriminator-body-function
              'exit c c-successors 1 n parent-thread f thread marker)
            'exit)
        (exit-g2gl-process))))


;;; The function `g2gl-flow-discriminator-body-function' is a subfunction of and
;;; used both by the g2gl-flow-discriminator activity and the
;;; g2gl-n-out-of-m-flow-join activity.  The only difference is that n-to-synch
;;; is 1 in the discriminator case, and "N" in the n-out-of-m case. (Here, n is
;;; the "M" in n-out-of-m; i.e., it's the number of branches.)  Exit-token is
;;; conventionally EXIT, but may be any value at all except for nil.  When this
;;; returns either exit-token or the symbol nil, if this returns any value other
;;; than exit-token (i.e., nil), the activity execution code should not exit,
;;; but should rather let execution proceed past itself ("fall through").

(defun g2gl-flow-discriminator-body-function
    (exit-token c c-successors n-to-sync n parent-thread f thread marker)
  (declare (type fixnum n n-to-sync))
  (macrolet ((exit-g2gl-process ()
               `(return-from g2gl-flow-discriminator-body-function
                  exit-token)))
    (cond
      ((null c-successors)
       ;; slightly degenerate case: handle as a flow-sync (code copied from
       ;; g2gl-flow-sync activity definition!)
       (let ((k (loop for some-thread in (g2gl-execution-threads f)
                      count
                      (and (eq c (activity-compilation-to-execute
                                   some-thread))
                           (null (execution-thread-state
                                   some-thread)))))) ; not IN-TRANSIT
         (cond
           ((not (=f k n))
            (exit-g2gl-process))
           (t
            (setf (g2gl-flow-scope-markers-in-this-thread thread)
                  (delete-gensym-element
                    marker (g2gl-flow-scope-markers-in-this-thread thread)))
            (loop repeat (-f k 1)
                  as related-thread
                     = (loop for some-thread in (g2gl-execution-threads f)
                             when
                               (and (not (eq some-thread thread))
                                    (eq c (activity-compilation-to-execute
                                            some-thread)))
                               return some-thread)
                  do (delete-g2gl-execution-thread related-thread t t))))))
      (t
       (let ((k (loop for th in (g2gl-execution-threads f)
                      count (and (eq c (activity-compilation-to-execute th))
                                 (null (execution-thread-state th))))))
         (when (=f k n-to-sync)
           ;; this the first time one thread has finished; schedule the
           ;; continuation. (Consider doing some graphical indication on the
           ;; thread token here, if any, and/or recording/displaying time stamps
           ;; on all the threads giving their arrival time.)
           (schedule-g2gl-execution-thread
             (make-g2gl-execution-thread
               (first c-successors) c nil parent-thread thread
               (body-compilation-this-is-being-used-to-execute thread)
               f)
             nil))
         (when (=f k n)
           ;; we've completed (joined) all threads, so now delete them all
           (loop while (loop for th in (g2gl-execution-threads f)
                             when (and (eq c (activity-compilation-to-execute th))
                                       (null (execution-thread-state th)))
                               do (delete-g2gl-execution-thread th t t)
                                  (return t))))
         (exit-g2gl-process))))))



(def-g2gl-activity (g2gl-n-out-of-m-flow-join
                     g2gl-flow-join 25
                     (connections-configuration rejoin)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 67)
                       #.(g2gl-standard-connection-stub 'input 'top 133)
                       #.(g2gl-standard-connection-stub 'output 'bottom 100)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description n-out-of-m-flow-join)
  ((number-of-rejoining-branches n (c-only integer))
   (g2gl-n-out-of-m-flow-join-scope-marker marker (c-only))
   (number-of-branches-to-synchronize
     n-to-sync
     (carried-over-to-c (initial-value 1))
     (type positive-integer)))
  (activity-compilation-code
    (let ((n-count (g2gl-activity-in-connection-count a))
          (n-to-sync-count (number-of-branches-to-synchronize a)))
      (when (>f n-to-sync-count                ; "N"
                n-count)                ; "M"
        (post-g2gl-compilation-warning
          "more branches (N) for synchronization than actual branches (M)"
          a b v)
        ;; if so, just have "N" = "M" (making this activity equivalent to
        ;; g2gl-flow-sync). (Note: n-to-sync-count cannot be 0 or negative due
        ;; to the the slot having category type feature for positive-integer.)
        (setq n-to-sync-count n-count))
      (set-acs n n-count)
      (set-acs n-to-sync n-to-sync-count)
      (set-acs marker (get-g2gl-flow-scope-marker a stack))))
  (activity-execution-code
    (if (eq (g2gl-flow-discriminator-body-function
              'exit c c-successors n-to-sync n parent-thread f thread marker)
            'exit)
        (exit-g2gl-process))))




;;; The function `get-g2gl-flow-scope-marker' assumes it's being called either
;;; from the compiler for g2gl-flow-split, in which case a should be that
;;; instance of g2gl-flow-split and stack? should be nil, or from the compiler
;;; for any subclass of g2gl-flow-join, in which case a should be that instance
;;; of g2gl-flow-join and stack? should be non-nil and have as its first element
;;; a list that's a triple whose third element is a and whose first element is
;;; the matching g2gl-flow-split instance whose branches meet at a.
;;;
;;; Whichever way the g2gl-flow-split instance is determined, its UUID string,
;;; copied as an all-upper-case string, is interned as a symbol that is returned
;;; as the marker.
;;;
;;; Notice that this is used in such a way by the flow-split/flow-join compilers
;;; such that an identical (EQ) and unique marker ends up stored both in the
;;; g2gl-flow-split and its matching g2gl-flow-join compilations (assuming all
;;; UUID's are unique).

(defun get-g2gl-flow-scope-marker (a stack?)
  (intern-text-string
    (nstring-upcasew
      (item-uuid-representation
        (cond
          (stack?
           (gensym-assert (eq (third (first stack?)) a))
           (gensym-assert (first (first stack?)))
           (gensym-assert
             (frame-of-class-p (first (first stack?)) 'g2gl-flow-split))
           (first (first stack?)))
          (t a))))))




;;; The function `do-g2gl-terminator-action' is called from the activity
;;; execution code for g2gl-flow-terminator with the terminator's marker, and f
;;; and thread, the activity's G2GL execution frame G2GL execution thread,
;;; respectively.  It returns after deleting all threads other than thread
;;; itself that have the same marker in their list of markers.

(defun do-g2gl-terminator-action (marker f thread)
  (setf (g2gl-flow-scope-markers-in-this-thread thread)
        (delete-gensym-element
          marker (g2gl-flow-scope-markers-in-this-thread thread)))
  (loop while (loop for th in (g2gl-execution-threads f)
                    when (and (not (eq th thread))
                              (memq marker
                                    (g2gl-flow-scope-markers-in-this-thread th)))
                      do (delete-g2gl-execution-thread th t t)
                         (return t))))

(def-g2gl-activity (g2gl-flow-terminator
                     g2gl-flow-join 29
                     (connections-configuration rejoin)
                     (stubs
                       #.(g2gl-standard-connection-stub 'input 'top 67)
                       #.(g2gl-standard-connection-stub 'input 'top 133)
                       #.(g2gl-standard-connection-stub 'output 'bottom 100)))
    (:funcall-at-load-time create-g2-bpel-activity-icon-description flow-terminator)
  ((g2gl-flow-terminator-scope-marker marker (c-only)))
  (activity-compilation-code
    (set-acs marker (get-g2gl-flow-scope-marker a stack)))
  (activity-execution-code
    (cond
      ((loop for th in (g2gl-execution-threads f)
             thereis (and (eq c (activity-compilation-to-execute th))
                          (null (execution-thread-state th))))
       (do-g2gl-terminator-action marker f thread))
      (t (exit-g2gl-process)))))

;; Note: the g2gl-flow-terminator does not correspond to one of the better-known
;; flow-join patterns, but it does implement more or less exactly the OR-join
;; <flow> activity variant semantics proposed/described in the WS-BPEL TC thread
;; at <http://lists.oasis-open.org/archives/wsbpel/200408/msg00181.html>.  Some
;; of the ramifications of forced thread termination are discussed in the thread
;; around this proposal there. (MHD 10/14/05)




)                                        ; (eval-when (:compile-toplevel :load-toplevel :execute) ..

;; The eval-when must surround definition of def-g2gl-activity as well as the
;; callers, since the aggregated code wants to be used in definitions that
;; follow.





;;;; (Prototype) Procedure Call Slot-Value Compiler & Grammar



;;; The grammar for `g2gl-call-statement-expression' is patterned after G2's
;;; proc-call-statement and proc-call-statement grammar.  The resulting parse is
;;; in practially the same format.  The main differences in the gramar are:
;;;
;;;   (a) each argument is g2gl-untyped-expression, as opposed to
;;;   procedure-untyped-expression
;;;
;;;   (b) each variable name (in the assignment statement case) is
;;;   g2gl-variable-name, as opposed to local-name
;;;
;;;   (c) we allow "G2GL designations" on the left side of the = sign, i.e., to
;;;   allow both variable names and message part names, e.g.,
;;;
;;;      foo, the bar of baz = call ...
;;;
;;;   (d) not supported: RPC calls (call ... across)
;;;
;;;   (e) not supported: method calling (call next method)

(def-slot-value-compiler g2gl-call-statement-expression (parse-result)
  (let* ((symbol-call-assignment-statement (first parse-result))
         (designation-list-with-noise (second parse-result))
         (procedure-name (third parse-result))
         (procedure-args-with-noise (fourth parse-result)))
    (phrase-list
      symbol-call-assignment-statement
      (remove-noise-at-head-of-list-phrase designation-list-with-noise)
      procedure-name
      (remove-noise-at-head-of-list-phrase procedure-args-with-noise))))

(def-grammar-category g2gl-call-statement-expression ()
  (g2gl-call-assignment-statement)
  (g2gl-call-statement))

(def-grammar-category g2gl-call-assignment-statement ()
  ((g2gl-designation-list
     '= 'call procedure-name '\( g2gl-procedure-arguments '\))
   (call-assignment-statement 1 4 6 nil))
  ((g2gl-designation-list '= 'call procedure-name '\( '\))
   (call-assignment-statement 1 4 nil nil)))

(def-grammar-category g2gl-call-statement ()
  (('call procedure-name '\( g2gl-procedure-arguments '\))
   (call-assignment-statement nil 2 4 nil))
  (('call procedure-name '\( '\))
   (call-assignment-statement nil 2 nil nil)))

;; The format of the transformation templates above is the same as for G2
;; procedures, where the nil is a place holder for an RPC interface, which
;; possibly we can some day support. (MHD 4/18/05)

(def-grammar-list-category g2gl-designation-list (g2gl-designation)
  :separator \,)

(def-grammar-list-category g2gl-procedure-arguments (g2gl-untyped-expression)
  :separator \,)










;;;; Boolean Expression Slot-Value Compiler & Grammar




(def-grammar-category g2gl-boolean-expression? ()
  ('none nil)
  (g2gl-boolean-expression))

(def-slot-value-compiler g2gl-boolean-expression? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-writer-as-existing-function g2gl-boolean-expression?
    write-expression-from-slot)



(add-grammar-rules '((g2gl-boolean-expression g2gl-logical-expression)))

(def-slot-value-compiler g2gl-boolean-expression (parse-result)
  parse-result)





;;;; Compiler for Top-level Processes



;;; Compile-G2GL-process-if-necessary-and-possible (G2GL-process s):
;;;
;;; This returns true if there is a current compilation version when it
;;; finishes, otherwise nil.

(defun compile-g2gl-process-if-necessary-and-possible (s)
  (when (or (null (stack-of-compilation-versions s))
            (latest-existing-compilation-version-was-disowned s))
    ;; -- there is no current compilation
    (compile-g2gl-process-if-possible s))
  (cond
    ((or (null (stack-of-compilation-versions s))
         (latest-existing-compilation-version-was-disowned s))
     ;; -- now due to compilation errors; return nil, indicating inability to
     ;; execute s due to compilation errors
     nil)
    (t t)))




;;; Compile-G2GL-process-if-possible ...
;;;
;;;   s - a g2gl-process instance; it should have a body: if not, this does
;;;   nothing, and returns nil.
;;;
;;; Note: if s fails to compile, the current compilation version, if any, is
;;; retained.

(defun compile-g2gl-process-if-possible (s)
  (when (null (subworkspaces s))
    (return-from compile-g2gl-process-if-possible nil))
  (let* ((v (make-g2gl-compilation-version))
         (body (first (subworkspaces s))))
    (setf (source-g2gl-process v) nil)
    (setf (current-execution-frames v) nil)
    (setf (alist-of-g2gl-operation-names-for-instantiation v) nil) ; temporarily
    (change-slot-value
      s 'latest-attempted-compilation-version-number
      (1+f (latest-attempted-compilation-version-number s)))
    (change-slot-value
      s 'latest-attempted-compilation-version-time
      (get-current-frame-edit-timestamp))
    (setf (compilation-version-number v)
          (latest-attempted-compilation-version-number s))
    (setf (number-of-compilation-errors v) 0)
    (setf (number-of-compilation-warnings v) 0)
    (setf (next-variable-index-to-assign v) 1)
    (setf (reassignable-temporary-variable-indices v) nil)
    (setf (alist-of-g2gl-body-compilations v) nil)
    (setf (compilations-of-outside-variables-used-in-compensation-handler v)
          nil)
    (setf (g2gl-body-compilation v)
          (compile-g2gl-body body nil v))
    (reclaim-gensym-list (reassignable-temporary-variable-indices v))
    (setf (reassignable-temporary-variable-indices v) nil)
    (change-slot-value
      s 'number-of-errors-in-latest-attempted-compilation
      (number-of-compilation-errors v))
    (change-slot-value
      s 'number-of-warnings-in-latest-attempted-compilation
      (number-of-compilation-warnings v))
    (setf (source-g2gl-process v) s)
    (when (not (=f (number-of-compilation-errors v) 0))
      (show-workspace body nil)
      (report-g2gl-compilation-completion-status v s)
      (delete-unowned-compilation-version-if-possible v)
      (return-from compile-g2gl-process-if-possible nil))
    (setf (alist-of-g2gl-operation-names-for-instantiation v)
          (derive-alist-of-g2gl-operation-names-for-instantiation
            (flowchart-entry-activity-compilation
              (g2gl-body-compilation v))
            body (g2gl-body-compilation v) v))
    (when (alist-of-g2gl-operation-names-for-instantiation v)
      (loop for switch-name?
                in (or (names-of-g2gl-service-switches-for-instantiation s)
                       '(nil))
            do (record-g2gl-process-for-instantiation
                 s
                 (or switch-name?
                     (name-of-g2gl-service-switch-for-connection s)))))
    (disown-current-compilation-version-if-any s)
    (setf (latest-existing-compilation-version-was-disowned s) nil)
    (slot-value-push v (stack-of-compilation-versions s))
    (change-slot-value
      s 'g2gl-process-compilation-version-number
      (copy-for-slot-value
        (latest-attempted-compilation-version-number s)))
    (change-slot-value
      s 'g2gl-process-compilation-version-time
      (copy-for-slot-value
        (latest-attempted-compilation-version-time s)))
    (change-slot-value
      s 'g2gl-process-procedure-signature
      (compute-g2gl-process-body-procedure-signature s))
    v))


(defun report-g2gl-compilation-completion-status
    (v &optional source-if-incomplete?)
  (notify-user
    "Compilation ~a for ~NF (version ~d): ~d error~a, ~d warning~a"
    (if (=f (number-of-compilation-errors v) 0) "complete" "INCOMPLETE")
    (or source-if-incomplete? (source-g2gl-process v))
    (compilation-version-number v)
    (number-of-compilation-errors v)
    (if (=f (number-of-compilation-errors v) 1) "" "s")
    (number-of-compilation-warnings v)
    (if (=f (number-of-compilation-warnings v) 1) "" "s")))



;;; Derive-alist-of-G2GL-operation-names-for-instantiation
;;; (flowchart-activity-compilation c, G2GL-body body, body-compilation b,
;;; compilation-version v)):
;;;
;;; This returns an alist of G2GL operation names that are specified by
;;; instantiation trigger receive and pick activities at the beginning of the
;;; activity subflowchart c paired with corresponding G2GL partner link variable
;;; compilations.

(defun derive-alist-of-g2gl-operation-names-for-instantiation (c body b v)
  (let ((trigger-msg
          "initial activity assumed to be instantiation trigger, though not so marked"))
    (cond
      ((=f (g2gl-activity-class-code c)
           (quoted-g2gl-activity-class-code g2gl-receive))
       (when (null (c-this-is-an-instantiation-trigger-for-receive c))
         ;; needs work -- a not passed in! (here, and below)
         (post-g2gl-compilation-warning trigger-msg body b v))
       (gensym-list
         (gensym-cons
           (c-g2gl-operation-name c)
           (g2gl-partner-link-variable c))))
      ((=f (g2gl-activity-class-code c)
           (quoted-g2gl-activity-class-code g2gl-pick))
       (when (null (c-this-is-an-instantiation-trigger-for-pick c))
         (post-g2gl-compilation-warning trigger-msg body b v))
       (loop for c-successor in (activity-compilation-successors c)
             when (=f (g2gl-activity-class-code c-successor)
                      (quoted-g2gl-activity-class-code g2gl-receive))
               collect (gensym-cons
                         (c-g2gl-operation-name c-successor)
                         (g2gl-partner-link-variable c-successor))
                 using gensym-cons))
      ((=f (g2gl-activity-class-code c)
           (quoted-g2gl-activity-class-code g2gl-flow-split))
       (loop for c-successor in (activity-compilation-successors c)
             nconc (derive-alist-of-g2gl-operation-names-for-instantiation
                     c-successor body b v)))
      (t nil))))





;;; Thread-is-in-instantiation-triggering-head-of-flowchart (execution-thread
;;; thread, flowchart-activity-compilation c):

(defun thread-is-in-instantiation-triggering-head-of-flowchart (thread c)
  (let ((class-code (g2gl-activity-class-code c)))
    (cond
      ((not
         (or (=f class-code
                 (quoted-g2gl-activity-class-code g2gl-receive))
             (=f class-code
                 (quoted-g2gl-activity-class-code g2gl-pick))
             (=f class-code
                 (quoted-g2gl-activity-class-code g2gl-flow-split))))
       nil)
      ((eq (activity-compilation-to-execute thread) c)
       t)
      ((and (=f class-code
                (quoted-g2gl-activity-class-code g2gl-flow-split))
            (loop for c-successor in (activity-compilation-successors c)
                  thereis
                  (thread-is-in-instantiation-triggering-head-of-flowchart
                    thread c-successor)))
       t)
      (t nil))))







;;;; Compiler for a G2GL-Body


;;; make-message-describing-g2gl-body ...
;;;
;;;  Args:
;;;
;;;   body - G2GL-body
;;;   v - compilation-version
;;;
;;; shows:
;;;
;;;    the description of a text box, located at the top left corner of body,
;;;    containing, say, "<purpose> of/for a scope <named ...> within the <the G2GL
;;;    process name of s> <the class of s>, version <the
;;;    latest-attempted-compilation-version-number of s>", e.g. "tracing of the
;;;    loan-approval BPEL-process, version 2"
;;;
;;; [what's purpose?! -mhd]


;;; The class `g2gl-identification-message' is used to label body workspaces, as
;;; created and added to workspaces by make-message-describing-g2gl-body.

(def-class (g2gl-identification-message message
                                        not-user-instantiable))

;; Note: new class, above, is not currently in the spec. (MHD 11/17/04)


(defun make-message-describing-g2gl-body (body v)
  (loop for subblock being each subblock of body
        when (frame-of-class-p subblock 'g2gl-identification-message)
          return (delete-frame subblock))
  (let* ((g2gl-process (parent-of-subworkspace? body))
         (message
           (make-message
             (tformat-text-string
               "The ~a ~a, version ~d."
               (or (get-primary-name-for-frame-if-any g2gl-process)
                   "(unnamed)")
               (class g2gl-process)
               (compilation-version-number v))
             'g2gl-identification-message))
         (height-for-message (height-of-block message))
         (top-edge-for-message
           (+w (top-edge-of-block body) (workspace-margin body)))
         (bottom-edge-for-message
           (+w top-edge-for-message height-for-message)))
    (add-to-workspace
      message body
      (+w (left-edge-of-block body) (workspace-margin body))
      ;; Logic borrowed from make-name-box.  Maybe abstract?
      (if (or (not (has-subblocks-p body))
              (loop for subblock being each subblock of body
                    never
                    (<w
                      (nth-value
                        1 (determine-extreme-edges-of-block subblock))
                      bottom-edge-for-message)))
          ;; Then:
          ;;    (Either no subblocks, or none above proposed bottom edge.)
          top-edge-for-message
          ;; Else:
          ;;    (Not sure if there's room, so just enlarge.)
          (-w (top-edge-of-block body) height-for-message))
      t t)
    message))



;;; Compile-G2GL-body
;;;   (G2GL-body body, class-of-G2GL-activity-with-this-body
;;;      class-above, compilation-version v)
;;;
;;; Body must be non-nil.  Class-above must be nil if body is a G2GL process
;;; body.


(defun compile-g2gl-body (body class-above v)
  (clear-g2gl-compilation-postings-on-body body)
  (let* ((b (make-g2gl-body-compilation))
         number-of-body-elements
         number-of-body-elements-without-body-indices
         g2gl-variables
         handlers
         entry-activities)
    (gensym-push
      (gensym-cons class-above b)
      (alist-of-g2gl-body-compilations v))
    (setf (g2gl-execution-display-title-position b)
          (make-g2gl-body-position
            (+w (left-edge-of-block body) (workspace-margin body))
            (+w (top-edge-of-block body) (workspace-margin body))))
    (setf (g2gl-variable-compilations b) nil)
    (setf (g2gl-fault-handler-compilations b) nil)
    (setf (g2gl-compensation-handler-compilations b) nil)
    (setf (g2gl-event-handler-compilations b) nil)
    (setf (flowchart-entry-activity-compilation b) nil)
    (setf (out-connection-representation-stream b) nil)
    (setf (next-body-element-index-to-assign b) 0)
    (setf (number-of-body-compilation-errors-and-warnings b) 0)
    (setq number-of-body-elements 0)
    (setq number-of-body-elements-without-body-indices 0)
    (setq g2gl-variables nil)
    (setq handlers nil)
    (setq entry-activities nil)

    (loop for e being each subblock of body
          do (incff number-of-body-elements)
             (cond
               ((frame-of-class-p e 'g2gl-variable)
                ;; if it has table frame representations and
                ;; (compile-text-elements-in-source-for-execution-displays g2gl-parameters),
                ;; compile them!  here and below! (MHD 3/26/05)
                (gensym-push e g2gl-variables))
               ((and (frame-of-class-p e 'g2gl-handler)
                     (not (block-has-connected-input-connections-p e)))
                (gensym-push e handlers))
               ((and (frame-of-class-p e 'text-box)
                     (not (block-has-connected-input-connections-p e)))
                (incff number-of-body-elements-without-body-indices)
                (when (compile-text-elements-in-source-for-execution-displays
                        g2gl-parameters)
                  (gensym-push
                    (compile-g2gl-text-box e)
                    (g2gl-text-box-compilations b))))
               ((not (frame-of-class-p e 'g2gl-activity))
                (incff number-of-body-elements-without-body-indices)
                (post-g2gl-compilation-warning
                  (if (frame-of-class-p e 'loose-end)
                      "illegal stub"
                      "illegal object")
                  e b v))
               ((g2gl-activity-is-an-entry-activity-p e)
                (gensym-push e entry-activities))))
    (setq g2gl-variables
          (sort-list g2gl-variables #'top-edge-of-block-lessp nil))
    (loop for g in g2gl-variables
          do (when (block-has-connections-p g)
               (post-g2gl-compilation-error
                 "a variable cannot have connections"
                 g b v))
             (when (and (eq (class g) 'g2gl-arg-variable) ; subclass?
                        (or class-above
                            (not (callable-as-a-procedure
                                   (parent-of-subworkspace? body))))
                        (or (not (eq class-above 'g2gl-fault-handler))
                            (loop for vc in (g2gl-variable-compilations b)
                                  thereis (=f (g2gl-variable-class-code vc)
                                              (quoted-g2gl-activity-class-code
                                                g2gl-arg-variable)))))
               (post-g2gl-compilation-warning
                 "arg variable not allowed here"
                 g b v))
             (when (and (eq (class g) 'g2gl-partner-link-variable)
                        class-above)
               (post-g2gl-compilation-warning
                 "in BPEL, partner link variable only allowed in top-level body"
                 g b v))                ; would be OK in G2GL
             (when (and (or (eq (class g) 'g2gl-correlation-variable)
                            (eq (class g) 'g2gl-local-variable))
                        class-above
                        (subclassp class-above 'g2gl-handler))
               (post-g2gl-compilation-warning
                 "in BPEL, variable not allowed in a handler"
                 g b v))                ; would be OK in G2GL
          collect (compile-g2gl-variable g b v)
            into variable-compilations using gensym-cons
          finally
            (setf (g2gl-variable-compilations b) variable-compilations)
            (reclaim-gensym-list g2gl-variables))
    (loop for e in handlers
          do (compile-non-local-g2gl-handler e class-above b v)
          finally (reclaim-gensym-list handlers))
    (let ((number-of-entry-activities (length entry-activities)))
      (cond
        ((=f number-of-entry-activities 0)
         (post-g2gl-compilation-error
           "no process flowchart entry activity" body b v))
        ((=f number-of-entry-activities 1)
         (let ((saved-flowchart-junctions-alist
                 (flowchart-junctions-alist v)))
           (setf (flowchart-junctions-alist v) nil)
           (setf (flowchart-entry-activity-compilation b)
                 (compile-g2gl-flowchart-activity
                   (first entry-activities) t nil b v))
           (let ((l (flowchart-junctions-alist v)))
             (setf (flowchart-junctions-alist v)
                   saved-flowchart-junctions-alist)
             (loop for x in l do (reclaim-gensym-cons x))
             (reclaim-gensym-list l))))
        (t                                ; number-of-entry-activities > 1
         (let ((message-string
                 (tformat-text-string
                   "one of ~d entry activities, none of which has been compiled"
                   number-of-entry-activities)))
           (loop for a in entry-activities doing
             (post-g2gl-compilation-error message-string a b v))
           (reclaim-text-string message-string))))
      (when (and (not (=f (next-body-element-index-to-assign b)
                          (-f number-of-body-elements
                              number-of-body-elements-without-body-indices)))
                 (=f number-of-entry-activities 1))
        (locate-lost-g2gl-activities-in-body
          body (first entry-activities) b v)))
    (reclaim-gensym-list entry-activities)
    (finalize-out-connection-representation-stream body b)
    (setf (execution-display-for-superimposed-tracings b) nil)
    (reclaim-gensym-cons
      (gensym-pop (alist-of-g2gl-body-compilations v)))
    b))





;;; Locate-lost-G2GL-activities-in-body
;;;   (G2GL-body body, flowchart-entry-activity flowchart-entry-activity,
;;;    body-compilation b, compilation-version v):
;;;
;;; This makes a special and potentially slow n-squared pass through the
;;; subblocks of body to locate and post error messages for G2GL activities in
;;; body that belong to cyclical entryless graphs or graphs with non-activity
;;; entry objects, but its efficiency is not important since it is used only
;;; when at least one error will be found.

(defun locate-lost-g2gl-activities-in-body (body flowchart-entry-activity b v)
  (let* ((flowchart-activities
           (collect-g2gl-flowchart-activities flowchart-entry-activity nil)))
    (loop for e being each subblock of body
          when (and (frame-of-class-p e 'g2gl-activity)
                    (not (and (frame-of-class-p e 'g2gl-handler)
                              (not (block-has-connected-input-connections-p e))))
                    (not (memq e flowchart-activities)))
            do (post-g2gl-compilation-error
                 "activity is in a graph with no proper entry activity"
                 e b v))))




;;; clear-g2gl-compilation-postings-on-body (G2GL-body body):

(defun clear-g2gl-compilation-postings-on-body (body)
  (loop with fsn
          = (copy-frame-serial-number (current-frame-serial-number))
        with postings-to-delete
          = (loop for p being subblock of body
                  when (frame-class-case p
                         ((g2gl-compilation-error g2gl-compilation-warning)
                          t))
                    collect p using gensym-cons)
        for p in postings-to-delete
        unless (frame-has-been-reprocessed-p p fsn)
          do (delete-frame p)
        finally
          (reclaim-frame-serial-number fsn)
          (reclaim-gensym-list postings-to-delete)))

;; Note: I cannot actually think of a scenario where the frame serial number
;; would be needed in practice to guard against a double deletion. Seems proper,
;; and doesn't hurt, to do the extra check, though. (MHD 12/15/04)


;;; There-are-g2gl-compilations-postings-on-body (G2GL-body body):

(defun there-are-g2gl-compilations-postings-on-body (body)
  (loop for p being subblock of body
        thereis (frame-class-case p
                  ((g2gl-compilation-error g2gl-compilation-warning)
                   t))))




;;; Compile-body-of-G2GL-activity
;;;   (G2GL-activity-with-body a, body-compilation b,
;;;    activity-compilation c, compilation-version v):

(defun compile-body-of-g2gl-activity (a b c v)
  (let ((body (first (subworkspaces a)))
        (class (class a))
        saved-outside-variables)
    (cond
      ((null body)
       (let ((message-string (tformat-text-string "~a has no body" class)))
         (post-g2gl-compilation-error message-string a b v)
         (reclaim-text-string message-string))
       (setf (g2gl-body-compilation c) nil)
       nil)
      (t
       (when (eq class 'g2gl-compensation-handler)
         (setq
           saved-outside-variables
           (compilations-of-outside-variables-used-in-compensation-handler v))
         (setf
           (compilations-of-outside-variables-used-in-compensation-handler v)
           nil))
       (setf (g2gl-body-compilation c) (compile-g2gl-body body (class a) v))
       (case class
         (g2gl-fault-handler
          (setf (c-g2gl-fault-name c) (g2gl-fault-name a)))
         (g2gl-compensation-handler
          (setf (compilations-of-outside-variables-used-in-body c)
                (compilations-of-outside-variables-used-in-compensation-handler v))
          (when (assq 'g2gl-compensation-handler
                      (alist-of-g2gl-body-compilations v))
            (loop for g
                      in (compilations-of-outside-variables-used-in-compensation-handler v)
                  when (not (memq g saved-outside-variables))
                    do (gensym-push g saved-outside-variables)))
          (setf (compilations-of-outside-variables-used-in-compensation-handler v)
                saved-outside-variables))
         (g2gl-message-event-handler
          (when (g2gl-partner-link-variable-name a)
            (setf (g2gl-partner-link-variable c)
                  (get-g2gl-variable-compilation
                    (g2gl-partner-link-variable-name a)
                    'g2gl-partner-link-variable nil a b v)))
          (setf (c-g2gl-operation-name c) (g2gl-operation-name a))
          (setf (c-g2gl-correlations c)
                (loop for correlation in (g2gl-correlations a)
                      collect (compile-g2gl-correlation correlation a b v)
                        using gensym-cons))
          (when (g2gl-message-variable-name a)
            (setf (g2gl-message-variable c)
                  (get-g2gl-variable-compilation
                    (g2gl-message-variable-name a) nil nil a b v))))
         (g2gl-alarm-event-handler
          (when (duration-or-deadline-expression a)
            (setf (g2gl-expression-compilation c)
                  (compile-g2gl-expression
                    (car (duration-or-deadline-expression a))
                    (type-of-g2gl-alarm-time-expression a)
                    a b v)))))
       c))))





;;; Compile-G2GL-text-box (text-box e):

(defun compile-g2gl-text-box (e)
  (let* ((c (make-g2gl-text-box-compilation)))
    (setf (g2gl-text-box-position c)
          (make-g2gl-body-position
            (left-edge-of-block e) (top-edge-of-block e)))
    (setf (class-of-g2gl-text-box c) (class e))
    (setf (text-of-g2gl-text-box c)
          (copy-text (cdr (box-translation-and-text e))))
    c))






;;;; ...



(defun top-edge-of-block-lessp (block-1 block-2)
  (<w (top-edge-of-block block-1)
      (top-edge-of-block block-2)))

;; for sorting blocks by top edge; quite general; move elsewhere?!

(defun left-edge-of-block-lessp (block-1 block-2)
  (<w (left-edge-of-block block-1)
      (left-edge-of-block block-2)))


;; In-connection-side-lessp is a utility function useful especially for sorting
;; input connections by position on side, left-to-right or top-to-bottom.

;; Out-connection-side-lessp is a utility function useful especially for sorting
;; output connections by position on side, left-to-right or top-to-bottom.

(defun in-connection-side-lessp (connection-1 connection-2)
  (<w
    (get-position-on-side-given-end-position
      (output-end-position connection-1))

    (get-position-on-side-given-end-position
      (output-end-position connection-2))))

(defun out-connection-side-lessp (connection-1 connection-2)
  (<w
    (get-position-on-side-given-end-position
      (input-end-position connection-1))

    (get-position-on-side-given-end-position
      (input-end-position connection-2))))


(defun sort-blocks-from-top-to-bottom (blocks)
  (sort-list blocks #'top-edge-of-block-lessp nil))

(defun sort-blocks-from-left-to-right (blocks)
  (sort-list blocks #'left-edge-of-block-lessp nil))

(defun sort-output-connections (connections)
  (sort-list connections #'out-connection-side-lessp nil))

(defun sort-input-connections (connections)
  (sort-list connections #'in-connection-side-lessp nil))


;;; Delete-g2gl-expression-compilation ... reclaims the compilation, either an
;;; entire expression compilation or a substructure of one,, reclaiming
;;; evaluation values as such, and otherwise reclaiming list structure as gensym
;;; conses.  Atoms not recognized as evaluation values are not allowed to appear
;;; in a compilation.


(defun delete-g2gl-expression-compilation (compilation)
  (cond
    ((atom compilation)
     (cond
       ((evaluation-value-p compilation)
        (reclaim-evaluation-value compilation))
       #+development
       ((null compilation) nil)                ; ignore nil
       ;; presumably a g2gl-variable-compilation, possibly recycled:
       #+development
       ((arrayp compilation) nil)
       #+development
       (t
        (cerror "continue anyway"
                "An unrecognized atomic datum in G2GL compilation: ~s"
                compilation))))
    ((evaluation-value-p compilation)
     (reclaim-evaluation-value compilation))
    (t
     (delete-g2gl-expression-compilation (car compilation))
     (delete-g2gl-expression-compilation (cdr compilation))
     (reclaim-gensym-cons compilation))))

;;; Delete-unowned-compilation-version-if-possible ...
;;;
;;; Arg: v - unowned-compilation-version

(defun delete-unowned-compilation-version-if-possible (v)
  (cond
    ((current-execution-frames v)
     ;; deletion of v can occur only if it has no current execution frames
     nil)
    (t
     (setf (stack-of-compilation-versions (source-g2gl-process v))
           (delete-slot-value-element
             v (stack-of-compilation-versions (source-g2gl-process v))))
     (delete-g2gl-body-compilation (g2gl-body-compilation v))
     
     (loop for str in (orphaned-strings v)
           do (reclaim-if-text-string str)
           finally (reclaim-gensym-list (orphaned-strings v)))
     
     ;; The reassignable-temporary-variable-indices of v should always be nil
     ;; here.
     (reclaim-g2gl-compilation-version v))))



;;; Delete-unowned-compilation-version-if-possible ...
;;;
;;; Arg: b - body-compilation

(defun delete-g2gl-body-compilation (b)
  (unless (fixnump (g2gl-execution-display-title-position b))
    ;; i.e., a cons
    (reclaim-gensym-cons (g2gl-execution-display-title-position b)))
  (let ((l (g2gl-variable-compilations b)))
    (when l
      (loop for c in l
            do (delete-g2gl-variable-compilation c))
      (reclaim-gensym-list l)))
  (loop for c in (g2gl-fault-handler-compilations b)
        do (delete-g2gl-activity-compilation c)
        finally (reclaim-gensym-list (g2gl-fault-handler-compilations b)))
  (loop for c in (g2gl-compensation-handler-compilations b)
        do (delete-g2gl-activity-compilation c)
        finally (reclaim-gensym-list (g2gl-compensation-handler-compilations b)))
  (loop for c in (g2gl-event-handler-compilations b)
        do (delete-g2gl-activity-compilation c)
        finally (reclaim-gensym-list (g2gl-event-handler-compilations b)))
  (loop for c in (g2gl-text-box-compilations b)
        do (delete-g2gl-text-box-compilation c)
        finally (reclaim-gensym-list (g2gl-text-box-compilations b)))
  (let ((entry-c (flowchart-entry-activity-compilation b)))
    (when entry-c
      (delete-activity-flowchart-compilation entry-c)))
  (cond
    ((wide-string-p (out-connection-representation-stream b))
     ;; case of a 16-bit unsigned-integer vector
     (reclaim-wide-string (out-connection-representation-stream b)))
    (t
     ;; case of a simple vector of small integers (fixnums)
     (reclaim-managed-array (out-connection-representation-stream b))))
  ;; The execution-display-for-superimposed-tracings of b should be nil at this
  ;; point, since execution displays for b should not exist except while b is
  ;; being executed and b cannot be deleted while it is being executed.
  (reclaim-g2gl-body-compilation b))




;;; Delete-activity-flowchart-compilation (entry-activity-compilation entry-c):

(defun delete-activity-flowchart-compilation (entry-c)
  (let ((flowchart-activity-compilations
          (collect-g2gl-activity-compilations entry-c nil)))
    (loop for c in flowchart-activity-compilations
          do (delete-g2gl-activity-compilation c))
    (reclaim-gensym-list flowchart-activity-compilations)))





;;;; Compiler for Variables



;;; Compile-g2gl-variable ...
;;;
;;; Args:
;;;   g - g2gl-variable
;;;   b - body-compilation
;;;   v - compilation-version
;;;
;;; For the case where g is a proxy G2GL variable, b should be nil, and g should
;;; be such as to not cause posting of compilation errors or warnings.

(defun compile-g2gl-variable (g b v)
  (let* ((class (class g))
         (c (make-g2gl-variable-compilation)) ; good for any variable class
         name-or-names)
    (setf (g2gl-var-body-element-position c)
          (make-g2gl-body-position-for-block g))
    (setf (g2gl-var-body-element-index c) nil) ; for the "proxy" var. case
    (when b
      ;; b can only be null in the case of a "proxy" G2GL variable
      (setf (g2gl-var-body-element-index c)
            (next-body-element-index-to-assign b))
      (incff (next-body-element-index-to-assign b)))
    (setf (g2gl-variable-class-code c)
          (map-g2gl-variable-class-to-code class))

    (setq name-or-names (name-or-names-for-frame g))
    (setf (c-g2gl-variable-name c) name-or-names)
    (cond
      ((null name-or-names)
       (post-g2gl-compilation-error "has no name" g b v))
      ((and (consp name-or-names) (cdr name-or-names))
       (setf (c-g2gl-variable-name c) (first name-or-names))
       (post-g2gl-compilation-warning "should have at most one name" g b v)))

    (setf (c-g2gl-variable-type c)        ; copy type as necessary; review!
          (copy-tree-using-gensym-conses (g2gl-variable-type g)))
    (cond
      ((null (g2gl-variable-type g))
       (case class
         ((g2gl-arg-variable g2gl-local-variable)
          (setf (c-g2gl-variable-type c) 'general)
          (post-g2gl-compilation-warning
            "type general assumed, but should specify a type" g b v))
         (g2gl-partner-link-variable
          (unless (suppress-unspecified-partner-link-variable-type-faults
                    g2gl-parameters)
            (post-g2gl-compilation-warning "should specify a type" g b v)))
         (g2gl-correlation-variable
          (post-g2gl-compilation-error "must specify a type" g b v))))
      ((not (g2gl-variable-type-p (g2gl-variable-type g) class))
       (post-g2gl-compilation-error "has a bad type" g b v)))
    (setf (c-default-value-for-g2gl-variable c)
          ;; copy initial value as necessary; review!
          (let ((val (default-value-for-g2gl-variable g)))
            (cond
              ((null val) nil)
              ((wide-string-p val) (copy-wide-string val))
              ((managed-float-p val) (copy-managed-float val))
              ((evaluation-sequence-p val) (copy-evaluation-sequence val))
              ((evaluation-structure-p val) (copy-evaluation-structure val))
              ((eq class 'g2gl-partner-link-variable)
               (copy-gensym-tree-with-text-strings val))

              ;; Default values of true and false are represented by the symbols
              ;; TRUE and FALSE in the default-value-for-g2gl-variable slot.  In
              ;; the case of a variable of type GENERAL, we have to specially
              ;; distinguish these from other symbols (see HQ-5061605 "G2GL:
              ;; true or false seen as symbols in default value of general type
              ;; variables").  This means there's no way to have a variable of
              ;; type GENERAL whose default value is the symbol TRUE or FALSE.
              ;; -dougo, 7/11/07

              ;; TO DO: To fix this, we could just store g2gl-true or g2gl-false
              ;; in this slot directly, but that would require updating old KBs.
              ;; Also, these would still display and parse as "true" or "false",
              ;; so there would need to be a category evaluator to allow the
              ;; user to conclude the symbol TRUE or FALSE.

              ((or (eq (c-g2gl-variable-type c) 'truth-value)
                   (and (eq (c-g2gl-variable-type c) 'general)
                        (memq val '(true false))))
               (if (eq val 'false) g2gl-false g2gl-true))

              (t val))))
    (setf (g2gl-variable-index c)
          (assign-index-for-variable v))
    c))





;;; Compile-non-local-G2GL-handler
;;;   (G2GL-handler a, class-of-G2GL-activity-one-level-up class-above,
;;;    body-compilation b, compilation-version v):

(defun compile-non-local-g2gl-handler (a class-above b v)
  (when (subclassp class-above 'g2gl-handler)
    (post-g2gl-compilation-warning        ; error instead?
      "handler not allowed in body of handler" a b v))
  (when (block-has-output-connections-p a)
    (post-g2gl-compilation-error "a handler cannot have out-connections" a b v))
  (when (name-or-names-for-frame a)
    (post-g2gl-compilation-warning "a handler should not have a name" a b v))
  (let* ((class (class a))
         (class-code (map-g2gl-activity-class-to-code class))
         (c (aggregate-g2gl-activity-compilation-creation-code class-code)))
    (setf (g2gl-body-element-position c)
          (make-g2gl-body-position
            (left-edge-of-block a) (top-edge-of-block a)))
    (setf (g2gl-body-element-index c) (next-body-element-index-to-assign b))
    (incff (next-body-element-index-to-assign b))
    (setf (g2gl-activity-class-code c) class-code)
    (setf (g2gl-activity-name c) (get-g2gl-activity-name a))
    (setf (activity-compilation-successors c) nil)
    (setf (g2gl-expression-compilation c) nil)
    (compile-body-of-g2gl-activity a b c v)
    (case class
      (g2gl-fault-handler
       (gensym-push c (g2gl-fault-handler-compilations b)))
      (g2gl-compensation-handler
       (when (g2gl-compensation-handler-compilations b)
         (post-g2gl-compilation-error
           "illegal extra compensation handler" a b v))
       (gensym-push c (g2gl-compensation-handler-compilations b))))
    (when (subclassp class 'g2gl-event-handler)
      (gensym-push c (g2gl-event-handler-compilations b)))))



;;; Assign-index-for-variable ...
;;;
;;; Args:
;;;   v - compilation-version

(defun assign-index-for-variable (v)
  (let ((i (next-variable-index-to-assign v)))
    (incff (next-variable-index-to-assign v))
    i))

;;; Arg: c - g2gl-variable-compilation

(defun delete-g2gl-variable-compilation (c)
  (when (consp (g2gl-var-body-element-position c))
    ;; a cons, not a small integer
    (reclaim-gensym-cons (g2gl-var-body-element-position c)))
  (reclaim-gensym-tree (c-g2gl-variable-type c))
  (let ((val (c-default-value-for-g2gl-variable c)))
    (cond
      ((wide-string-p val) (reclaim-wide-string val))
      ((managed-float-p val) (reclaim-managed-float val))
      ;; no conses to reclaim for now: if we do, make sure not to reclaim the
      ;; conses for g2gl-true or g2gl-false!
      ))
  (when (=f (g2gl-variable-class-code c)
            #.(map-g2gl-variable-class-to-code 'g2gl-partner-link-variable))
    (reclaim-gensym-tree-with-text-strings
      (c-default-value-for-g2gl-variable c)))
  (reclaim-g2gl-variable-compilation c))







;;;; Compiler for Activities



;;; Compile-g2gl-flowchart-activity always returns a G2GL activity compilation,
;;; even when a is some object other than a G2GL activity.
;;;
;;; a - a g2gl-activity instance (but "OK" if not: it's checked for)
;;; entry-case - entry-activity-case (true or nil)
;;; stack - a stack of unclosed branchpoint characterizations
;;; b - body compilation
;;; v - the compilation-version instance
;;;
;;; An unclosed branchpoint characterization is a list of a particular unclosed
;;; branchpoint activity, the branch-closing classes therefor (a list), and
;;; either nil or no-rejoin or the activity that already closed one of the
;;; branches from this branchpoint



;;;  `Local-handler-activity-p' is true iff block-on-activity-flowchart is a
;;;  g2gl-activity instance whose connection configuration feature is for
;;;  local-handler.

(defun-substitution-macro local-handler-activity-p
    (block-on-activity-flowchart)
  (and (frame-of-class-p block-on-activity-flowchart 'g2gl-activity)
       (eq (second
             (g2gl-connections-configuration-feature
               block-on-activity-flowchart)) ; may be nil
           'local-handler)))

;; Applicable class: G2GL-FAULT-HANDLER, G2GL-COMPENSATION-HANDLER.(MHD 4/18/05)


;;;  `local-handlers-allowed-activity-p' is true iff block-on-activity-flowchart
;;;  is a g2gl-activity instance whose connection configuration feature is for
;;;  local-handlers-allowed.

(defun-substitution-macro local-handlers-allowed-activity-p
    (block-on-activity-flowchart)
  (and
    (frame-of-class-p block-on-activity-flowchart 'g2gl-activity)
    (eq (second
          (g2gl-connections-configuration-feature
            block-on-activity-flowchart)) ; may be nil
        'local-handlers-allowed)))

;; Applicable class: G2GL-INVOKE.(MHD 4/18/05)




;;; The parameter `allow-g2gl-left-ins-from-while-p' says whether the G2GL
;;; activity flowchart compiler relaxes the specification, and allows left-in
;;; connections on activities if coming from a right-out connection of a while.
;;;
;;; This is planned to be be true at least through the first official public
;;; release of G2GL, in G2 8.1r0, because it was allowed through the beta, and
;;; even encouraged in that auto layout (the redo-layout command and import
;;; system procedures) connected a while's right output connection this way.

(defparameter allow-g2gl-left-ins-from-while-p t)

;; Done for compatibility when bug in compiler testing was discovered late in
;; the game.  The bug was fixed, and much related code reviews, as part of
;; fixing HQ-4996815 "G2GL: non-handler to the right of invoke should cause
;; error posting".  While this is set to true, we cannot resolve the
;; (low-priority) bug HQ-5012393 "G2GL: compiler for while allows left-input
;; activities, but should only allow top".  (MHD 4/18/05)


;;; The function `check-g2gl-activity-connections-for-compilation' implements
;;; the eight steps in the detailed spec for function
;;; compile-g2gl-flowchart-activity to check that connections of A are valid and
;;; post compilation errors if they are not.

(defun check-g2gl-activity-connections-for-compilation
    (a b v connections-configuration-type
       left-ins top-ins right-ins bottom-ins
       left-outs top-outs right-outs bottom-outs
       entry-case)
  (let (error-message-string?)
    ;; Top-ins:
    (when (setq error-message-string?
                (case connections-configuration-type
                  (rejoin
                   ;; require one or more connections:
                   (if (null top-ins)
                       "missing top-input connection"))
                  (fork
                   ;; require exactly one connection between top- and
                   ;; left-ins:
                   (case (+f (length top-ins) (length left-ins))
                     (0 (if entry-case
                            nil
                            "missing left- or top-input connection"))
                     (1) ; OK
                     (t
                      "extra or misplaced top- or left-input connections")))
                  ((local-handler alien start)
                   ;; require no connections:
                   (if top-ins "disallowed top-input connections"))
                  (t
                   ;; require at most one connection:
                   (if (cdr top-ins)
                       "too many top-input connections"))))
      (post-g2gl-compilation-error error-message-string? a b v))
    ;; Top-outs:
    (when (setq error-message-string?
                (if top-outs
                    "disallowed top-output connection(s)"))
      (post-g2gl-compilation-error error-message-string? a b v))
    ;; Left-ins:
    (when (setq error-message-string?
                (case connections-configuration-type
                  (fork
                   ;; left-ins check for fork case done already above
                   ;; with check for top-ins
                   )
                  (loop-anchor
                   ;; require exactly one connection between right-ins
                   ;; and left-ins:
                   (cond
                     ((and (null right-ins) (null left-ins))
                      "missing right- or left-input connection")
                     ((and right-ins left-ins)
                      "extra or misplaced right- or left-input connection(s)")))
                  (flow-gate
                   ;; require one or more flow-signal left-in connections
                   (loop with n-from-flow-signal = 0
                         with n-from-others = 0
                         for ins = right-ins then left-ins
                         repeat 2
                         do (loop for conn in ins
                                  as other
                                     = (get-block-at-other-end-of-connection
                                         conn a)
                                  do (if (frame-of-class-p
                                           other 'g2gl-flow-signal)
                                         (incff n-from-flow-signal)
                                         (incff n-from-others)))
                         finally
                           (return
                             (cond
                               ((and (=f n-from-flow-signal 0)
                                     (>f n-from-others 0))
                                "disallowed right- or left-input connections, none from a flow signal")
                               ((=f n-from-flow-signal 0)
                                "missing left- or right-input connection from a flow signal")
                               ((>f n-from-others 0)
                                "disallowed right- or left-input connections not from any flow signal")))))

                  ((local-handler)
                   ;; require exactly one local-handlers-allowed connection:
                   (loop for conn in left-ins
                         as other
                            = (get-block-at-other-end-of-connection
                                conn a)
                         count (local-handlers-allowed-activity-p other)
                           into n
                         finally
                           (unless (=f n 1)
                             (return
                               "missing or misplaced left-input connection(s)"))))
                  (t
                   ;; require no left-in connection:
                   (if (and left-ins
                            (or (not allow-g2gl-left-ins-from-while-p)
                                (not
                                  ;; OK to make an exception if (a) just
                                  ;; one left-in connection, and (b) it's
                                  ;; from a while's right output
                                  ;; connection:
                                  (and
                                    (null (cdr left-ins))
                                    (let ((in (first left-ins)))
                                      (eq (class
                                            (get-block-at-other-end-of-connection
                                              in a))
                                          'g2gl-while)
                                      (eq (get-side-given-end-position
                                            (input-end-position in))
                                          'right))))))
                       "no left-input connection allowed here"))))
      (post-g2gl-compilation-error error-message-string? a b v))
    ;; Left-outs:
    (when (setq error-message-string?
                (case connections-configuration-type
                  (flow-signal
                   ;; require exactly one flow-gate connection between
                   ;; left-outs and right-outs:
                   ;; require one or more flow-signal left-in connections
                   (loop with n-to-flow-gate = 0
                         with n-to-others = 0
                         for outs = right-outs then left-outs
                         repeat 2
                         do (loop for conn in outs
                                  as other
                                     = (get-block-at-other-end-of-connection
                                         conn a)
                                  do (if (frame-of-class-p
                                           other 'g2gl-flow-gate)
                                         (incff n-to-flow-gate)
                                         (incff n-to-others)))
                         finally
                           (return
                             (cond
                               ((and (=f n-to-flow-gate 0)
                                     (>f n-to-others 0))
                                "disallowed right- or left-output connections, none to a flow gate")
                               ((=f n-to-flow-gate 0)
                                "missing left- or right-output connection to a flow gate")
                               ((>f n-to-flow-gate 1)
                                "more than one left- or right-output connection to a flow gate")

                               ((>f n-to-others 0)
                                "disallowed right- or left-output connection(s) not to any flow gate")))))
                  (t
                   ;; require no left-out connections
                   (if left-outs "disallowed left-output connections"))))
      (post-g2gl-compilation-error error-message-string? a b v))
    ;; Right-ins:
    (when (setq error-message-string?
                (case connections-configuration-type
                  (loop-anchor
                   ;; right-ins check for loop-anchor case done already above
                   ;; with check for left-ins
                   )
                  (flow-gate
                   ;; right-ins check for flow-gate case done already above with
                   ;; check for left-ins
                   )
                  (t
                   (if right-ins "disallowed right-input connections"))))
      (post-g2gl-compilation-error error-message-string? a b v))
    ;; Right-outs:
    (when (setq error-message-string?
                (case connections-configuration-type
                  ((fork loop-anchor)
                   ;; require exactly one right-out connection:
                   (cond
                     ((null right-outs)
                      "missing right-output connection")
                     ((cdr right-outs)
                      "extra or misplaced right-output connections")))
                  (flow-signal
                   ;; right-outs check for flow-signal case done already above
                   ;; with check for left-outs
                   )
                  (local-handlers-allowed
                   ;; require only local-handler connections:
                   (if (loop for conn in right-outs
                             as other
                                = (get-block-at-other-end-of-connection
                                    conn a)
                             thereis (not (local-handler-activity-p
                                            other)))
                       "right-output connection is not to a local handler activity"))
                  (t
                   (if right-outs "disallowed right-output connections"))))
      (post-g2gl-compilation-error error-message-string? a b v))
    ;; Bottom-ins:
    (when (setq error-message-string?
                (if bottom-ins "disallowed bottom-input connections"))
      (post-g2gl-compilation-error error-message-string? a b v))
    ;; Bottom-outs:
    (when (setq error-message-string?
                (case connections-configuration-type
                  (split
                   ;; require one or more bottom-out connection:
                   (if (null bottom-outs)
                       "missing at least one bottom-output connection"))
                  (t
                   ;; require at most one bottom-out connection:
                   (if (cdr bottom-outs)
                       "extra or misplaced bottom-out connection(s)"))))
      (post-g2gl-compilation-error error-message-string? a b v))))




(defun compile-g2gl-flowchart-activity (a entry-case stack b v)
  (let* ((class (class a))
         (really-an-activity-p (subclassp class 'g2gl-activity))
         (class-code
           (if really-an-activity-p
               (map-g2gl-activity-class-to-code class)
               non-activity-class-code))
         (feature?
           (if really-an-activity-p
               (g2gl-connections-configuration-feature a)))
         (connections-configuration-type (if feature? (second feature?)))
         (new-branch-closing-classes (if feature? (third feature?)))
         (all-outs nil)
         (already-visited nil)
         c)
    (when (eq connections-configuration-type 'alien)
      (post-g2gl-compilation-error "illegal object in flowchart" a b v))
    (multiple-value-bind
        (left-ins top-ins right-ins bottom-ins
                  left-outs top-outs right-outs bottom-outs
                  number-of-predecessors)
        (get-g2gl-activity-ins-and-outs a)
      (loop for out being each output-connection of a
            as f-or-c = (connection-frame-or-class out)
            as class = (if (symbolp f-or-c) f-or-c (class f-or-c))
            when (not (or (subclassp class 'g2gl-standard-connection)
                          (subclassp class 'g2gl-link-connection)))
              do (post-g2gl-compilation-warning
                   "non-standard class of connection out of this activity"
                   a b v))
      (let ((previous-entry?
              (or (if (>f number-of-predecessors 1)
                      (assq a (flowchart-junctions-alist v)))
                  (if (and (flowchart-junctions-alist v)
                           (eq a (car (first (flowchart-junctions-alist v)))))
                      (first (flowchart-junctions-alist v))))))
        (cond
          (previous-entry?
           (setq already-visited t)
           (setq c (cdr previous-entry?)))
          (t
           ;; already-visited is nil:
           (setq c
                 (aggregate-g2gl-activity-compilation-creation-code class-code))
           (setf (g2gl-body-element-position c)
                 (make-g2gl-body-position
                   (left-edge-of-block a) (top-edge-of-block a)))
           (setf (g2gl-body-element-index c)
                 (next-body-element-index-to-assign b))
           (when really-an-activity-p
             ;; (when a is not a g2gl activity here, its assigned body element
             ;; index will not be unique, but that is ok, since a compilation
             ;; error will have already been posted so b will never be executed)
             (incff (next-body-element-index-to-assign b)))
           (setf (g2gl-attribute-display-compilations c)
                 (compile-g2gl-attribute-displays a))
           ;; Setting the class-code slot to nil in the following step is how we
           ;; recognize a half-processed flow-gate node, one that has ben
           ;; arrived at from one or more flow-gate nodes but not yet via a
           ;; normal branch, and thus one we have not yet gone through.
           (setf (g2gl-activity-class-code c) nil)
           (setf (g2gl-expression-compilation c) nil)
           (when (or (>f number-of-predecessors 1)
                     (and entry-case
                          (=f number-of-predecessors 1)))
             (setf (flowchart-junctions-alist v)
                   (nconc (flowchart-junctions-alist v)
                          (gensym-list (gensym-cons a c))))))))
      (let* ((existing-unclosed-branchpoint (first (first stack)))
             (existing-branch-closing-classes (second (first stack)))
             (subfork-case
               (and (eq connections-configuration-type 'fork)
                    (intersects-p
                      existing-branch-closing-classes
                      new-branch-closing-classes)
                    (=f number-of-predecessors 1) ; => one in-connection
                    (let ((sole-in-connection
                            (first (or left-ins top-ins right-ins bottom-ins))))
                      (and (eq (input-end-object sole-in-connection)
                               existing-unclosed-branchpoint)
                           (eq (get-side-given-end-position
                                 (input-end-position sole-in-connection))
                               'right)))))
             (stack-for-successors stack))
        (when (and new-branch-closing-classes
                   (not already-visited)
                   (not subfork-case))
          (gensym-push
            (gensym-list a new-branch-closing-classes nil)
            stack-for-successors))
        (when (eq connections-configuration-type 'rejoin)
          (cond
            ((not (memq class existing-branch-closing-classes))
             (post-g2gl-compilation-error "inappropriate rejoin" a b v))
            (t
             (let ((third (third (first stack-for-successors))))
               (unless (or (null third) (eq third a))
                 (post-g2gl-compilation-error
                   "other branches fail to rejoin here" a b v))
               (unless (eq third a)        ; check only one time per join
                 (frame-class-case a
                   ((g2gl-flow-discriminator g2gl-n-out-of-m-flow-join)
                    (loop for (branch-opener) in stack
                          when (frame-of-class-p branch-opener 'g2gl-while)
                            return (post-g2gl-compilation-error
                                     (if (frame-of-class-p a 'g2gl-flow-discriminator)
                                         "a FLOW-DISCRIMINATOR is illegal within a WHILE"
                                         "an N-OUT-OF-M-FLOW-JOIN is illegal within a WHILE")
                                     ;; note: could allow n-out-of-m with n = m,
                                     ;; but don't bother: it's a degenerate case
                                     a b v)))))
               (setf (third (first stack-for-successors)) a)
               (pop stack-for-successors)))))
        (when (and (eq connections-configuration-type 'loop-anchor)
                   already-visited
                   (not (eq existing-unclosed-branchpoint a)))
          (post-g2gl-compilation-error "improper loop" a b v))
        (let* ((continue-along-branch-through-already-visited-flow-gate
                 (and (eq connections-configuration-type 'flow-gate)
                      (not (memq 'g2gl-flow-gate existing-branch-closing-classes))
                      (null (g2gl-activity-class-code c))))) ; "half-processed"
          ;; "here we could check a flow-signal or flow-gate node ..."
          (when (or (and (eq connections-configuration-type 'flow-gate)
                         stack-for-successors
                         (memq 'g2gl-flow-gate existing-branch-closing-classes))
                    (and already-visited
                         (not continue-along-branch-through-already-visited-flow-gate)))
            ;; The following was added to fix leak bug HQ-5311834 "G2GL: Memory
            ;; leaks compiling diagrams - leak connection lists, e.g., for
            ;; WHILE". (MHD 6/22/06)
            (reclaim-g2gl-activity-ins-and-outs
              left-ins top-ins right-ins bottom-ins
              all-outs                        ; observe: nil here (setq/nconc below)
              left-outs top-outs right-outs bottom-outs)
            (return-from compile-g2gl-flowchart-activity c)))
        ;; The following function call implements the eight steps in the spec to
        ;; check that connections of A are valid and post compilation errors if
        ;; they are not.
        (check-g2gl-activity-connections-for-compilation
          a b v connections-configuration-type
          left-ins top-ins right-ins bottom-ins
          left-outs top-outs right-outs bottom-outs
          entry-case)
        (setf (g2gl-activity-class-code c) class-code)
        (cond
          (really-an-activity-p ; not true in error case
           (let ((name-or-names (name-or-names-for-frame a)))
             (setf (g2gl-activity-name c) name-or-names)
             (when (listp name-or-names)
               (setf (g2gl-activity-name c) (first name-or-names))
               (when (cdr name-or-names)
                 (post-g2gl-compilation-warning
                   "should have at most one name" a b v)))
             (when (and (subclassp class 'g2gl-handler)
                        name-or-names)
               (post-g2gl-compilation-warning
                 "a handler should not have a name" a b v))))
          (t
           (post-g2gl-compilation-error "not a G2GL activity" a b v)))
        (when (or (and (eq class 'g2gl-receive)
                       (this-is-an-instantiation-trigger-for-receive a))
                  (and (eq class 'g2gl-pick)
                       (this-is-an-instantiation-trigger-for-pick a)))
          (unless (not (block-has-connected-input-connections-p a))
            ;; "unless a has no connected in-connections ..."
            (post-g2gl-compilation-error
              "ineligible to have create-instance attribute" a b v)))
        (when (and (eq class 'g2gl-scope)
                   (variable-access-serializable a)
                   (loop for pair in (alist-of-g2gl-body-compilations v)
                         thereis (and (eq (car pair) 'g2gl-scope)
                                      ;; ... [the
                                      ;; c-variable-access-serializable of the
                                      ;; parent-G2GL-activity-compilation of
                                      ;; the body compilation component of
                                      ;; pair is true]
                                      )))
          (post-g2gl-compilation-error
            "serializable scopes cannot be nested"
            a b v))
        (when (subclassp class 'g2gl-activity-with-body)
          (compile-body-of-g2gl-activity a b c v))
        ;; huge macro expansion here:
        (AGGREGATE-G2GL-ACTIVITY-COMPILATION-CODE)
        ;; "later ..., if we are at a flow-sync node ..."!
        (let* ((stack-for-first-successor stack-for-successors)
               (stack-for-next-successor stack-for-first-successor)
               successors)
          (when (or (eq connections-configuration-type 'loop-anchor)
                    (eq connections-configuration-type 'flow-signal))
            (setq stack-for-first-successor stack)
            (when bottom-outs
              (setq stack-for-next-successor stack)))
          (setq all-outs (nconc bottom-outs right-outs left-outs top-outs))
          (setq successors nil)
          ;; The next step is the recursive step:
          (loop for out in all-outs
                as out-block = (get-block-at-other-end-of-connection out a)
                do (setq successors
                         (nconc
                           successors
                           (gensym-list
                             (compile-g2gl-flowchart-activity
                               out-block nil stack-for-next-successor b v))))
                   (produce-out-connection-representation-for-stream out b)
                   (setq stack-for-next-successor stack-for-successors))
          (when (and (null bottom-outs) all-outs)
            (gensym-push nil successors))
          (when (or (null successors)
                    (null (first successors)))
            (when stack-for-first-successor
              ;; we've arrived at a node with no successor, but have one or
              ;; more branchputs "unclosed"
              (post-g2gl-compilation-warning
                "branch fails to rejoin other branches" a b v))
            (loop for b                ; a branchpoint representation
                      in stack-for-first-successor
                  do (setf (third b) 'no-rejoin)))
          (when (and stack-for-successors
                     (eq (cdr stack-for-successors) stack))
            ;; we're at a branchpoint but have finished recursively all its
            ;; branches
            (reclaim-gensym-list (car stack-for-successors))
            (reclaim-gensym-cons stack-for-successors))
          (reclaim-g2gl-activity-ins-and-outs
            left-ins top-ins right-ins bottom-ins
            all-outs
            left-outs top-outs right-outs bottom-outs)
          (setf (activity-compilation-successors c) successors)
          c)))))



;;; Get-g2gl-activity-ins-and-outs (g2gl-activity a):
;;;
;;; This returns 9 values.  Values 1 through 4 are, respectively, lists of
;;; connected left, top, right, and bottom input connections; values 5 through 8
;;; are, respectively, lists of connected left, top, right, and bottom output
;;; connections; the 9th value is an integer giving the number of predecessors
;;; (i.e., the number of connected input connections into a).  Each resulting
;;; list is consed using fresh gensym conses, and the elements are sorted in
;;; left-to-right or top-to-bottom order.
;;;
;;; This is a subfunction of compile-g2gl-flowchart-activity.

(defun get-g2gl-activity-ins-and-outs (a)
  (loop with lc                                ; a listed connection, as needed
        ;; l(eft), t(op), etc. i(n) & o(out) lists:
        with li = nil with ti = nil with ri = nil with bi = nil
        with lo = nil with to = nil with ro = nil with bo = nil
        with number-of-predecessors fixnum = 0 ; counts input connections
        for x being each connection of a       ; a connection or port name
        unless (or (symbolp x)
                   (loose-end-p (get-block-at-other-end-of-connection x a)))
          ;; a connected connection, not a port name
          do
            ;; set lc to a new list of x, then set the appropriate in/out list
            ;; to it, after nconcing the old list onto the end of lc. Along the
            ;; way, count input connections into number-of-predecessors.
            (setq lc (gensym-cons-macro x nil))
            (setf (cdr lc)
                  (cond
                    ((eq (output-end-object x) a)
                     (incff number-of-predecessors)
                     (case (get-side-given-end-position (output-end-position x))
                       (left (prog1 li (setq li lc)))
                       (top (prog1 ti (setq ti lc)))
                       (right (prog1 ri (setq ri lc)))
                       (t (prog1 bi (setq bi lc)))))
                    (t
                     (case (get-side-given-end-position (input-end-position x))
                       (left (prog1 lo (setq lo lc)))
                       (top (prog1 to (setq to lc)))
                       (right (prog1 ro (setq ro lc)))
                       (t (prog1 bo (setq bo lc)))))))
        finally
          ;; Sort each in-* and out-* list that has > 1 element, then return:
          (unless (>f number-of-predecessors 1)        ; opt. (usually one in)
            (when (cdr li)
              (setq li (sort-list li 'in-connection-side-lessp nil)))
            (when (cdr ti)
              (setq ti (sort-list ti 'in-connection-side-lessp nil)))
            (when (cdr ri)
              (setq ri (sort-list ri 'in-connection-side-lessp nil)))
            (when (cdr bi)
              (setq bi (sort-list bi 'in-connection-side-lessp nil))))
          (when (cdr lo)
            (setq lo (sort-list lo 'out-connection-side-lessp nil)))
          (when (cdr to)
            (setq to (sort-list to 'out-connection-side-lessp nil)))
          (when (cdr ro)
            (setq ro (sort-list ro 'out-connection-side-lessp nil)))
          (when (cdr bo)
            (setq bo (sort-list bo 'out-connection-side-lessp nil)))
          (return (values li ti ri bi lo to ro bo number-of-predecessors))))



;;; The function `reclaim-g2gl-activity-ins-and-outs' reclaims the lists
;;; presumably resulting from an invocation of get-g2gl-activity-ins-and-outs.
;;; No useful values are returned.  If all-outs? is non-nil, then the out-
;;; lists, lo (left-outs), et al, are presumed to have been nconc'd already into
;;; that value, and are not separately reclaimed; otherwise, they are separately
;;; reclaimed.  In all cases, the in- lists, li (left-ins), et al, are presumed
;;; to require separate reclamation.
;;;
;;; This is a subfunction of compile-g2gl-flowchart-activity.

(defun-void reclaim-g2gl-activity-ins-and-outs
    (li ti ri bi all-outs? lo to ro bo)
  (reclaim-gensym-list-macro
    (if all-outs?
        (nconc li ti ri bi all-outs?)
        (nconc li ti ri bi lo to ro bo))))





;;; The function `compile-g2gl-attribute-displays' returns a gensym-list of
;;; g2gl-attribute-display-compilations corresponding to the attribute displays
;;; of g2gl-activity a.

(defun-simple compile-g2gl-attribute-displays (a)
  (loop for subblock being each subblock of a
        when (and (table-p subblock) (attribute-display-p subblock))
          collect (compile-g2gl-attribute-display subblock)
            using gensym-cons))

(defun-simple compile-g2gl-attribute-display (display)
  (let ((adc (make-g2gl-attribute-display-compilation)))
    (setf (g2gl-attribute-display-position adc)
          (make-g2gl-body-position
            (-w (left-edge-of-block display)
                (left-edge-of-block (superblock? display)))
            (-w (top-edge-of-block display)
                (top-edge-of-block (superblock? display)))))
    (setf (g2gl-attribute-display-rows adc)
          (loop for row in (table-rows display)
                for name-cell = (attribute-table-row-name-cell row)
                for value-cell = (attribute-table-row-value-cell row)
                when (attribute-table-cell-is-class-p value-cell)
                  do (setf (g2gl-attribute-display-table-header adc)
                           (copy-text (text? value-cell)))
                else
                  collect (gensym-cons
                            (when (cell-is-text-cell-p name-cell)
                              ;; TO DO: handle block cells?
                              (copy-text (text? name-cell)))
                            (when (cell-is-text-cell-p value-cell)
                              (copy-text (text? value-cell))))
                    using gensym-cons))
    adc))

(defun-void delete-g2gl-attribute-display-compilation (adc)
  (reclaim-g2gl-body-position (g2gl-attribute-display-position adc))
  (reclaim-text (g2gl-attribute-display-table-header adc))
  (loop for row in (g2gl-attribute-display-rows adc) do
    (reclaim-text (car row))
    (reclaim-text (cdr row))
    (reclaim-gensym-cons row))
  (reclaim-gensym-list (g2gl-attribute-display-rows adc))
  (reclaim-g2gl-attribute-display-compilation adc))




;;; `Compile-g2gl-expression' ..
;;;
;;; Args:
;;;
;;;  parse - G2GL-expression-parse-tree
;;;  type - type-of-G2GL-expression
;;;  a - g2gl-activity
;;;  b - body-compilation
;;;  v - compilation-version

(defun-allowing-unwind compile-g2gl-expression (parse type a b v)
  (catch 'bad-g2gl-expression
    (case type
      (do-expression
       (if (null parse)
           nil
           (gensym-cons
             'do-statements
             (loop for (type-of-statement . details) in parse
                   collect (case type-of-statement
                             (assignment-statement
                              (let ((place-expression (first details))
                                    (expression (second details)))
                                (gensym-list
                                  'assignment-statement
                                  (compile-g2gl-expression-1 place-expression a b v)
                                  (compile-g2gl-expression-1 expression a b v))))
                             (conclude-statement
                              (let ((place-expression (first details))
                                    (expression (second details)))
                                (gensym-list
                                  'conclude-statement
                                  (compile-g2gl-expression-1 place-expression a b v)
                                  (compile-g2gl-expression-1 expression a b v)))))
                     using gensym-cons))))
      (assignments
       (if (null parse)
           nil
           (gensym-cons
             'assignment-statements
             (loop for (assignment-statement place-expression expression)
                       in parse
                   collect (gensym-list
                             'assignment-statement
                             (compile-g2gl-expression-1 place-expression a b v)
                             (compile-g2gl-expression-1 expression a b v))
                     using gensym-cons))))
      (call
       (if (null parse)
           nil
           (gensym-list
             'call-assignment-statement
             (loop for variable-name in (second parse)
                   collect (compile-g2gl-expression-1 variable-name a b v)
                     using gensym-cons)
             (third parse)                ; procedure name
             (loop for expression in (fourth parse)
                   collect (compile-g2gl-expression-1 expression a b v)
                     using gensym-cons)
             ;; later, add in here/deal with "across ..."!!
             )))

      (values-expression
       (if (null parse)
           nil
           (gensym-cons
             'values
             (loop for expression in parse
                   collect (compile-g2gl-expression-1 expression a b v)
                     using gensym-cons))))
      ((join-condition
         duration-expression
         deadline-expression
         boolean-expression)
       (compile-g2gl-expression-1 parse a b v))
      (t
       (let ((message-string (tformat-text-string "bad ~a" type)))
         (post-G2GL-compilation-error message-string a b v)
         (reclaim-text-string message-string))))))





(defparameter break-on-g2gl-expression-compilation-errors nil)

(defvar g2gl-expression-compilation-error
  (list 'g2gl-expression-compilation-error))

(defun g2gl-expression-compilation-error
    (a b v general-type in-operation specific-type datum &optional extra-datum)
  #+development
  (when break-on-g2gl-expression-compilation-errors
    (cerror "continue with G2GL error"
            "G2GL Expression Compilation Error: ~a: ~a: ~a: ~a~a~a"
            general-type
            in-operation
            specific-type
            datum
            (if extra-datum " " "")
            (or extra-datum "")))
  (let ((message-text
          (twith-output-to-text-string
            (tformat
              "G2GL Expression Compilation Error: ~a: ~a~a~a~a~a~a~a"
              general-type
              (if in-operation ": " "")
              (or in-operation "")
              (if specific-type ": " "")
              (or specific-type "")
              datum
              (if extra-datum " " "")
              (or extra-datum "")))))
    (post-g2gl-compilation-error message-text a b v)
    (reclaim-text-string message-text))
  (throw 'bad-g2gl-expression nil))

(defun g2gl-expression-compilation-warning
    (a b v general-type in-operation specific-type datum &optional extra-datum)
  (g2gl-expression-compilation-error        ; same for now!
    a b v general-type in-operation specific-type datum extra-datum))




;;; compile-g2gl-expression-1 ... For now this operates very simply:
;;; only references to G2GL variables are allowed.  (Later, we should probably
;;; relax this to allow free references to arbitary G2 objects by name.)  If a
;;; G2GL variable name reference cannot be resolved, this throws to the catch in
;;; compile-g2gl-expression for BAD-G2GL-EXPRESSION.

;;; Args:
;;;  parse - g2gl expression parse tree
;;;  b - body-compilation

(defun compile-g2gl-expression-1 (parse a b v)
  (cond
    ((atom parse)
     (cond
       ((symbolp parse)
        (gensym-list
          'variable-compilation
          (get-g2gl-variable-compilation parse nil 'general a b v)))
       ((evaluation-value-p parse)
        (copy-evaluation-value parse))
       (t
        (g2gl-expression-compilation-error
          a b v 'unrecognized-atomic-datum 'nil 'nil parse))))
    (t
     (let* ((car (car-of-cons parse))
            (cdr (cdr-of-cons parse)))
       (cond
         ((and (eq cdr 'truth-value)
               (or (eql car 1000) (eql car -1000)))
          ;; copy a non-unique truth-value constant in expression code as the
          ;; unique true/false cons, so it's EQ comparable.  All copying or
          ;; reclaiming of this constant has to take care with this cons, as
          ;; does copy-evaluation-value and reclaim-evaluation-value.
          (if (=f car 1000) g2gl-true g2gl-false))
         ((evaluation-value-p parse)
          (copy-evaluation-value parse))
         ((and (eq cdr 'seconds)        ; duration (i.e., a G2 interval)
               (cond
                 ((fixnump car)
                  car)
                 ((managed-float-p car)
                  (copy-managed-float car))
                 (t nil))))
         (t
          (case car
            ((= /= < > <= >= + - * / ^ and or if-expression g2gl-funcall
                call-function format-form has-value-p has-no-value-p)
             (cond
               ((and
                  ;; optimize +1 and -1 cases, if ...
                  (memq car '(+ -))        ; plus or minus op
                  cdr (cdr cdr) (null (cddr cdr)) ; 2-long
                  (fixnump (second cdr)) ; second arg is fixnum constant 1
                  (= (second cdr) 1))
                (gensym-list
                  (case car (+ '1+) (- '1-))
                  (compile-g2gl-expression-1 (first cdr) a b v)))
               ((eq car 'call-function)
                (gensym-cons
                  car
                  (gensym-cons
                    (first cdr)
                    (loop for operand in (cdr cdr)
                          as arg-number from 0
                          collect (if (and (=f arg-number 0)
                                           (eq (first cdr) 'call-function))
                                      ;; non-system-defined (user-defined) case
                                      operand
                                      (compile-g2gl-expression-1 operand a b v))
                            using gensym-cons))))
               (t
                (gensym-cons
                  car
                  (loop for operand in cdr
                        collect (compile-g2gl-expression-1 operand a b v)
                          using gensym-cons)))))
            ((not)
             (gensym-list car (compile-g2gl-expression-1 (car cdr) a b v)))
            ((quote)
             ;; symbol, i.e., foo <= (quote foo) <= "the symbol foo"
             (second parse))

            ((current-time
               current-real-time
               current-subsecond-time
               current-subsecond-real-time
               current-system-time
               current-system-real-time
               this-g2gl-process-instance
               this-g2gl-process)
             (copy-list-using-gensym-conses parse))

            ((the)
             (gensym-cons
               car
               (gensym-list
                 (copy-tree-using-gensym-conses ; list iff qualified
                   (second parse))
                 (compile-g2gl-expression-1 (third parse) a b v))))

            ((nth-element)
             (compile-g2gl-nth-element-expression
               (second parse) (third parse) a b v))
            ((new)
             (gensym-list
               car
               ;; check second arg? It must be a symbol.  At runtime it must be
               ;; a subclass of g2gl-message, but we could warn here if it's not
               ;; yet known to be.  Review! (MHD 3/16/05)
               (second parse)))
            (t
             (g2gl-expression-compilation-error
               a b v 'unrecognized-operator 'nil 'nil car cdr)))))))))


;;; The function `compile-g2gl-nth-element-expression' compiles a parse result
;;; of the form (NTH-ELEMENT expr bracketed-expr) where bracketed-expr is either
;;; (\[ index-expr) or (bracketed-expr \[ index-expr).  The result is a tree of
;;; nested binary NTH-ELEMENT expression compilations.  For example,
;;; (NTH-ELEMENT expr ((\[ 1) \[ 2)) becomes
;;; (NTH-ELEMENT (NTH-ELEMENT comp 1) 2) where comp is the compilation of expr.

(defun compile-g2gl-nth-element-expression (expr bracketed-expr a b v)
  (gensym-list
    'nth-element
    (if (eq (car bracketed-expr) '\[)
        (compile-g2gl-expression-1 expr a b v)
        (compile-g2gl-nth-element-expression expr (car bracketed-expr) a b v))
    (compile-g2gl-expression-1 (car (last bracketed-expr)) a b v)))




;;; Compile-G2GL-correlation (G2GL-correlation correlation, G2GL-activity a,
;;; body-compilation b, compilation-version v):

(defun compile-g2gl-correlation (correlation a b v)
  (gensym-list
    (get-g2gl-variable-compilation
      (first correlation)
      'g2gl-correlation-variable
      (slot-value-list 'conversation-key-attributes)
      a b v)
    (copy-list-using-gensym-conses (cdr correlation))))




;;; `Get-g2gl-variable-compilation' ...
;;;
;;; Expected-class may be the symbol G2GL-partner-link-variable, the symbol
;;; g2gl-correlation-variable, or nil for "normal", that is, for a G2GL arg
;;; variable or a G2GL local variable; expected-type may be nil for "no specific
;;; expectation".
;;;
;;; This always returns a G2GL variable compilation, even if a declaration for
;;; name cannot be found or if the declaration found is of the wrong class or
;;; type; thus, for example, when a declaration cannot be found, a G2GL
;;; compilation warning is posted, and a "proxy" variable is created, the class
;;; of which is expected-class if non-nil or else the class G2GL-local-variable
;;; and the G2GL-variable-type of which is expected-type if non-nil or else the
;;; symbol general.
;;;
;;; Args:
;;;
;;;  G2GL-variable-name name,
;;;  expected-G2GL-variable-class expected-class,
;;;  expected-G2GL-variable-type expected-type,
;;;  G2GL-activity a,
;;;  body-compilation b,
;;;  compilation-version v

(defun get-g2gl-variable-compilation (name expected-class expected-type a b v)
  (let* ((c nil)
         (went-outside-compensation-handler nil)
         (alist (alist-of-g2gl-body-compilations v)))
    (loop with pair
          while alist
          do (setq pair (first alist))
             (loop for var-comp in (g2gl-variable-compilations (cdr pair))
                   when (eq (c-g2gl-variable-name var-comp) name)
                     do (setq c var-comp)
                        (setq alist nil)
                        (return)
                   finally
                     (when (eq (car pair) 'g2gl-compensation-handler)
                       (setq went-outside-compensation-handler t))
                     (pop alist)))
    (cond
      (c
       (when (not (g2gl-var-body-element-index c))
         ;; c is a "proxy" G2GL variable compilation, so post another warning.
         ;; See Suggestion HQ-5404745 "Always create compilation postings for
         ;; each reference to undeclared variables".  -dougo, 2/16/07
         (let ((message-string
                 (tformat-text-string
                   "~(~a not declared in any enclosing body~)" name)))
           (post-g2gl-compilation-warning message-string a b v)
           (reclaim-text-string message-string)))
       (let ((class (map-g2gl-variable-code-to-class (g2gl-variable-class-code c))))
         (when (or (and (null expected-class)
                        (not (memq class
                                   '(g2gl-arg-variable g2gl-local-variable))))
                   (and expected-class
                        (not (eq class expected-class))))
           (let ((message-string
                   (tformat-text-string
                     "~(the use of ~a is not appropriate for ~a~a variable~)"
                     name (supply-a-or-an class) class)))
             ;; NOTE: changed warning to error (approved by LH for next rev. of
             ;; spec, but not in the spec as of this time). This change also
             ;; resolves HQ-5040355 "G2GL: assigning a value to a partner link
             ;; variable aborts G2". (MHD 6/16/05)
             (post-g2gl-compilation-error message-string a b v)
             (reclaim-text-string message-string)))
         (when (and expected-type
                    (not (g2gl-type-compatible-p
                           (c-g2gl-variable-type c)
                           expected-type)))
           (let ((message-string
                   (tformat-text-string
                     "~(the use of ~a is not compatible with its declared type~)"
                     name)))
             (post-g2gl-compilation-warning message-string a b v)
             (reclaim-text-string message-string)))
         (when went-outside-compensation-handler
           (gensym-push
             c
             (compilations-of-outside-variables-used-in-compensation-handler v)))
         c))
      (t
       (let ((message-string
               (tformat-text-string
                 "~(~a not declared in any enclosing body~)" name)))
         (post-g2gl-compilation-warning message-string a b v)
         (reclaim-text-string message-string))
       (let ((e (make-frame (or expected-class 'g2gl-local-variable))))
         ;; use name-or-names-for-frame, not g2gl-variable-name as in spec!!
         (change-slot-value e 'name-or-names-for-frame name)
         (when expected-type
           (change-slot-value e 'g2gl-variable-type expected-type))
         ;; NOTE: we should have done all we can by this point to ensure the
         ;; proxy cannot get errors or warnings, which compile-g2gl-variable
         ;; cannot deal with (since it has a null body b).
         (setq c (compile-g2gl-variable e nil v))
         (setf (g2gl-variable-compilations b)
               (nconc (g2gl-variable-compilations b) (gensym-list c)))
         (delete-frame e)
         c)))))




(defun g2gl-type-compatible-p (type expected-type)
  type
  expected-type

  ;; dummy stub definition; fix later!!

  t)





;;; arg: c - activity-compilation

(defun delete-g2gl-activity-compilation (c)
  (when (consp (g2gl-body-element-position c))
    ;; a cons, not a small integer
    (reclaim-gensym-cons (g2gl-body-element-position c)))
  (loop for adc in (g2gl-attribute-display-compilations c) do
    (delete-g2gl-attribute-display-compilation adc))
  (reclaim-gensym-list (g2gl-attribute-display-compilations c))
  (reclaim-gensym-list (activity-compilation-successors c))
  (let ((ec (g2gl-expression-compilation c)))
    (when ec
      (delete-g2gl-expression-compilation ec)))
  (let ((code (g2gl-activity-class-code c))
        b)
    (when (and (and code
                    (or (=f code (quoted-g2gl-activity-class-code g2gl-scope))
                        (=f code (quoted-g2gl-activity-class-code g2gl-fault-handler))
                        (=f code (quoted-g2gl-activity-class-code g2gl-compensation-handler))
                        (=f code (quoted-g2gl-activity-class-code g2gl-alarm-event-handler))
                        (=f code (quoted-g2gl-activity-class-code g2gl-message-event-handler))))
               (setq b (g2gl-body-compilation c)))
      (delete-g2gl-body-compilation b)))
  ;; the following should delete structure c:
  (AGGREGATE-G2GL-ACTIVITY-RECLAMATION-CODE))





;;; Delete-G2GL-text-box-compilation (G2GL-text-box-compilation c):

(defun delete-g2gl-text-box-compilation (c)
  (when (consp (g2gl-body-element-position c))
    ;; a cons, not a small integer
    (reclaim-gensym-cons (g2gl-body-element-position c)))
  (reclaim-text (text-of-g2gl-text-box c))
  (reclaim-g2gl-text-box-compilation c))





;;; Find-activity-compilation-corresponding-to-surrogate-activity
;;;   (surrogate-activity a, execution-display d):

(defun find-activity-compilation-corresponding-to-surrogate-activity (a d)
  (loop with b
          = (body-compilation-this-is-being-used-to-execute
              (one-execution-thread-that-is-shown-hereon d))
        for c in (g2gl-fault-handler-compilations b)
        when (eq a (managed-svref
                     (vector-of-g2gl-body-elements d)
                     (g2gl-body-element-index c)))
          return c
        finally
          (return
            (or (loop for c in (g2gl-compensation-handler-compilations b)
                      when (eq a (managed-svref
                                   (vector-of-g2gl-body-elements d)
                                   (g2gl-body-element-index c)))
                        return c)
                (loop for c in (g2gl-event-handler-compilations b)
                      when (eq a (managed-svref
                                   (vector-of-g2gl-body-elements d)
                                   (g2gl-body-element-index c)))
                        return c)
                (loop with flowchart-activity-compilations
                        = (collect-g2gl-activity-compilations
                            (flowchart-entry-activity-compilation b)
                            nil)
                      for c in flowchart-activity-compilations
                      when (eq a (managed-svref
                                   (vector-of-g2gl-body-elements d)
                                   (g2gl-body-element-index c)))
                        do (reclaim-gensym-list flowchart-activity-compilations)
                           (return c)
                      finally
                        ;; we should practically never arrive here
                        (reclaim-gensym-list flowchart-activity-compilations)
                        (return nil))))))



;;; Collect-G2GL-activity-compilations
;;;  (G2GL-flowchart-activity-compilation c,
;;;   already-visited-activity-compilations l):

(defun collect-g2gl-activity-compilations (c l)
  (cond
    ((memq-p-macro c l) l)
    (t (let ((revised-l (gensym-cons c l)))
         (loop for c-successor? in (activity-compilation-successors c)
               when c-successor?
                 do (setq revised-l
                          (collect-g2gl-activity-compilations
                            c-successor?
                            revised-l)))
         revised-l))))






;;;; Posting Compilation Errors and Warnings





(def-class (g2gl-compilation-error message not-user-instantiable))
(def-class (g2gl-compilation-warning message not-user-instantiable))



;;; Args:
;;;
;;; message-string string,
;;; body-element-or-body e,
;;; body-compilation b,
;;; compilation-version v

(defun post-g2gl-compilation-error (string e b v)
  (incff (number-of-compilation-errors v))
  (post-g2gl-compilation-error-or-warning 'g2gl-compilation-error string e b v))

(defun post-g2gl-compilation-warning (string e b v)
  (incff (number-of-compilation-warnings v))
  (post-g2gl-compilation-error-or-warning 'G2GL-compilation-warning string e b v))


(defun post-g2gl-compilation-error-or-warning (class string e b v)
  v                                        ; not used for now!
  (incff (number-of-body-compilation-errors-and-warnings b))
  (let ((workspace? (get-workspace-if-any e)))
    (when workspace?
      (let ((message (make-message
                       (copy-text-string string)
                       class)))
        (change-color-of-text-box
          message nil
          (class-case class
            (g2gl-compilation-error 'red)
            (t 'yellow))
          'black
          (class-case class
            (g2gl-compilation-error 'white)
            (t 'black))
          'black)
        (cond
          ((frame-of-class-p e 'workspace)        ; body case
           (loop with left-edge-for-messages
                   = (-w (right-edge-of-block e)
                         (workspace-margin e)
                         (minimum-format-width-for-text-cell ; usual width
                           (text-box-format message)))
                 with spacing-between = 10
                 with lowest-edge-of-messages
                   = (+w (top-edge-of-block e) (workspace-margin e))
                 for b being each subblock of e
                 when (and (frame-of-class-p b 'message)
                           (=w (left-edge-of-block b) left-edge-for-messages))
                   do (setq lowest-edge-of-messages
                            (maxw lowest-edge-of-messages (bottom-edge-of-block b)))
                 finally
                   ;; worry about enlarging workspace!
                   (add-to-workspace
                     message e
                     left-edge-for-messages
                     (+w lowest-edge-of-messages spacing-between)
                     t)))
          (t
           ;; for now, plop these down, possibly overlapping, with their top-left
           ;; corner in the middle of the object they're for.  Improve later!
           (add-to-workspace
             message workspace?
             (midline-x-of-block e) (midline-y-of-block e) t)))))))

;; This should arrange to not overlap messages for any subblock! (MHD 4/5/05)





;;;; G2GL Body Positions and Representation Streams



;;; Make-G2GL-body-position (x-in-body x, y-in-body y):
;;;
;;; This encodes the g2gl body position as a small integer if both x and y have
;;; absolute values less than 2^13, which should almost always be the case if
;;; the body includes (0, 0), barring major re-engineering of the g2
;;; representation of workspace coordinates.  for the encoding, x and y are each
;;; offset by 2^13, and then the offset x effectively shifted 14 bits to the
;;; left is added to the offset y.

(defun make-g2gl-body-position (x y)
  (if (and (>f x #.(- (expt 2 13)))
           (<f x #.(+ (expt 2 13)))
           (>f y #.(- (expt 2 13)))
           (<f y #.(+ (expt 2 13))))
      (+f  (*f #.(expt 2 14) x)  #.(expt 2 27)  y  #.(expt 2 13))
      (gensym-cons x y)))

;; To to: make sure XML import lays out workspaces so that most items are
;; reasonably close, i.e., with (0, 0) around the center, so that the optimized
;; case works most of the time.  Consider having an "optimizing" version of a
;; "cleanup" command that not only does nice layout, but also fixes up workspace
;; coordinates to achieve a similar effect. (MHD 1/17/05)



;;; Reclaim-g2gl-body-position (g2gl-body-position p):

(defun reclaim-g2gl-body-position (p)
  (when (consp p)
    (reclaim-gensym-cons p))
  nil)



;;; Make-g2gl-body-position-for-block (block b):

(defun make-g2gl-body-position-for-block (b)
  (make-g2gl-body-position (left-edge-of-block b) (top-edge-of-block b)))



;;; Get-x-from-g2gl-body-position (g2gl-body-position p):

(defun get-x-from-g2gl-body-position (p)
  (cond
    ((fixnump p)                        ; an integer, not a cons
     ;; Alt: instead of dividing p by 2^14 to get a quotient, one could simply
     ;; extract the 14 bits of p that are displaced 14 bits from the right end
     ;; of p.
     (-f (floorf p #.(expt 2 14)) #.(expt 2 13)))
    (t
     (car p))))


;;; Get-y-from-g2gl-body-position (g2gl-body-position p):

(defun get-y-from-g2gl-body-position (p)
  (cond
    ((fixnump p)                        ; an integer, not a cons
     ;; Alt: instead of dividing p by 2^14 to get a remainder, one could simply
     ;; extract the rightmost 14 bits of p.
     (multiple-value-bind (quotient remainder)
         (floorf p #.(expt 2 14))
       (declare (ignore quotient))
       (-f remainder #.(expt 2 13))))
    (t (cdr p))))




;;; Move-to-G2GL-body-position (G2-object e, G2GL-body-position p):

(defun move-to-g2gl-body-position (e p)
  (shift-block-to
    e
    (get-x-from-g2gl-body-position p)
    (get-y-from-g2gl-body-position p)))



;;; Add-to-g2gl-body
;;;  (G2GL-object e, body-source-or-display d, g2gl-body-position p):

(defun add-to-g2gl-body (e d p)
  (add-to-workspace
    e d
    (get-x-from-g2gl-body-position p)
    (get-y-from-g2gl-body-position p)
    t))                                        ; updates images (if nec.)


;;; Add-to-g2gl-object
;;;  (G2GL-object e, G2GL-object o, g2gl-body-position p):
;;;
;;; This is just like add-to-g2gl-body, but the second argument can be block,
;;; not just a workspace.

(defun add-to-g2gl-object (e o p)
  (add-to-block
    e o
    (get-x-from-g2gl-body-position p)
    (get-y-from-g2gl-body-position p)
    t))



;;; Produce-out-connection-representation-for-stream
;;;   (out-connection out, body-compilation b):

(defun produce-out-connection-representation-for-stream (out b)
  (gensym-push
    (input-end-position out)
    (out-connection-representation-stream b))
  (gensym-push
    (+f (output-end-position out)
        ;; if connection is diagonal, signify by adding 2^14:
        (if (connection-diagonal-p out)
            #.(expt 2 14)
            0))
    (out-connection-representation-stream b))
  (cond
    ((fixnump (delta-or-deltas out))
     (gensym-push
       (+f #.(* 3 (expt 2 26)) (delta-or-deltas out))
       (out-connection-representation-stream b)))
    (t                                        ; must be a list
     (loop for delta in (delta-or-deltas out)
           do (gensym-push
                (+f #.(* 3 (expt 2 26)) delta)
                (out-connection-representation-stream b))))))



;;; finalize-out-connection-representation-stream
;;;   (g2gl-body body, body-compilation b):
;;;
;;; Note: this uses a wide string in to store an array of 16-bit unsigned
;;; integers with an associated active length field. Note that byte-vector-16
;;; arrays do not store the active length.

(defun finalize-out-connection-representation-stream (body b)
  (let* ((out-stream-list (out-connection-representation-stream b))
         (need-more-than-16-bits
           (or (and (or (>w (width-of-block body) #.(expt 2 14))
                        (>w (height-of-block body) #.(expt 2 14)))
                    (loop for element in out-stream-list
                          thereis
                          (and (not (<f element #.(expt 2 15)))
                               (not (<=f #.(- (* 3 (expt 2 26)) (expt 2 14))
                                         element
                                         #.(- (+ (* 3 (expt 2 26)) (expt 2 14)) 1))))))
               ;; check for signed (negative) elements:  See note! (MHD 7/7/06)
               (when (loop for element in out-stream-list
                           thereis (<f element 0))
                 ;; for #+development only!
                 #+development
                 (warn "MHD: negative elements in out-stream-list found: ~s"
                       out-stream-list)
                 t)))
         (i (length out-stream-list))
         vector)
    (declare (type fixnum i))
    (cond
      ((not need-more-than-16-bits)
       (setq vector (make-wide-string i))
       (loop for element in out-stream-list
             as u16 fixnum
                    = (if (<f element #.(expt 2 15))
                          element
                          (+f (-f element #.(* 3 (expt 2 26)))
                              #.(* 3 (expt 2 14))))
             do (decff i)
                #+development
                (when (or (<f u16 0) (>f u16 #.(- (expt 2 16) 1)))
                  (warn "bad u16 byte: ~d (~a) (from ~d)"
                        u16
                        (if (< u16 0) "negative" "doesn't fit in 16")
                        element))
                (setf (charw vector i)
                      (code-wide-character u16))))
      (t
       (setq vector (allocate-managed-array i))
       (loop for element in out-stream-list
             do (decff i)
                (setf (managed-svref vector i) element))))
    (reclaim-gensym-list out-stream-list)
    (setf (out-connection-representation-stream b) vector)))

;; We check for signed (negative) elements because, although it is unusual and
;; rare.  As far as I know, these can in fact only occur with the second-to-last
;; and last elements in out-stream-list, representing output-end-position and
;; input-end-position, respectively. There are checks in various places to
;; prevent/disallow negative end positions, but we have observed they can creep
;; in.  See bug HQ-5320612 "G2GL: G2 (development) abort compiling flowchart
;; with neg. offset connections". For how out-stream-list is constructed, see
;; produce-out-connection-representation-for-stream, above. (MHD 7/7/06)





;;;; G2gl-Object Icon Substitutions



;;; The variable `g2gl-object-icon-descriptions-info' is a static a-list
;;; (using general, non-reclaimable conses) of the form
;;;
;;;    ( {  (g2gl-subclass . corresponding-icon-description) } )
;;;
;;; with g2gl-subclass entries for each subclass of g2gl-object.  Since the
;;; class g2gl-object is sealed, we need not ever update this based on
;;; changes to any user-defined subclasses.

;;; This a-list is set up via a call to the the function
;;; `set-up-variable-g2gl-object-icon-descriptions-info', which sets it to the
;;; result of calling the function
;;; `get-all-g2gl-objects-icon-description-info'.  The call to set up the
;;; variable happens at load time -- see form below, at or near the end of this
;;; module.  Note: the setup function must use the UNOPTIMZED-SUBCLASSES loop
;;; path, since creation of structures supporting the implementation of the
;;; subclasses path happens only at process creation time.

(defvar g2gl-object-icon-descriptions-info)


(defun set-up-variable-g2gl-object-icon-descriptions-info ()
  (setq g2gl-object-icon-descriptions-info
        (get-all-g2gl-objects-icon-description-info)))




;;; The function and variable
;;; `args-for-g2gl-object-class-icon-description-override' and
;;; `override-g2gl-object-class-icon-description-with-generic' are used at load
;;; time only, in support of get-all-g2gl-objects-icon-description-info (see
;;; above).  They ensure that every subclass of G2GL-OBJECT does not use the
;;; same (EQ-identical) icon description as object.  (If one did, and
;;; subsitutions were done on it, all inheritors of OBJECT's icon description
;;; would then be changed.)  Note: icon-description inheriting/sharing is in
;;; general incompatible with the current icon substitution approach: we make
;;; the assumption that any other icon description in use in G2GL is unique,
;;; i.e., not inherited by any other system-defined subclass of G2GL-OBJECT.

(defvar args-for-g2gl-object-class-icon-description-override
  ;; lifted from SYSICONS - override for OBJECT: (MHD 9/27/05)
  '(50 50
    ((polychrome
      (g2-icon-left-edge . extra-light-gray)
      (g2-icon-top-edge . light-gray)
      (g2-icon-right-edge . gray)
      (g2-icon-bottom-edge . gray)
      (icon-color . foreground))
     (variables) (background-layer)
     g2-icon-left-edge (filled-polygon ((0 0) (25 25) (0 50)) ((0 0) (25 25) (0 50)))
     g2-icon-top-edge (filled-polygon ((25 25) (0 0) (50 0)) ((25 25) (0 0) (50 0)))
     g2-icon-right-edge (filled-polygon ((25 25) (50 0) (50 50)) ((25 25) (50 0) (50 50)))
     g2-icon-bottom-edge (filled-polygon ((0 50) (25 25) (50 50)) ((0 50) (25 25) (50 50)))
     icon-color (outline (0 0) (0 50) (50 50) (50 0))
     (lines (0 50) (50 0)) (lines (0 0) (50 50)))
    nil nil nil nil nil
    ((g2-icon-left-edge 0 0 25 50)
     (g2-icon-top-edge 0 0 50 25)
     (g2-icon-right-edge 25 0 50 50)
     (g2-icon-bottom-edge 0 25 50 50)
     (icon-color 0 0 50 50))))





(defun override-g2gl-object-class-icon-description-with-generic (g2gl-object-class)
  (override-icon-description-for-system-defined-class
    g2gl-object-class
    (apply
      'create-icon-description
      args-for-g2gl-object-class-icon-description-override)
    'nil))



(defun get-all-g2gl-objects-icon-description-info ()
  (loop for class being each unoptimized-subclass of 'g2gl-object
        if (eq (get-slot-description 'icon-description (slot-descriptions (class-description 'g2gl-object)))
               (get-slot-description 'icon-description (slot-descriptions (class-description class))))
          do                                ; see note! (MHD 9/27/05)
;            (warn "~a has an inherited icon-description slot description; a generic one is being created!"
;                  class)
            (override-g2gl-object-class-icon-description-with-generic class)
        collect (gensym-cons
                  class (get-slot-init-form class 'icon-description))))

;; The classes to which the above icon-description override applies as of now
;; are: G2GL-OBJECT, G2GL-ACTIVITY, G2GL-DEFINITION, G2GL-MESSAGE,
;; G2GL-PORT-TYPE-DEFINITION, G2GL-PARTNER-LINK-TYPE-DEFINITION,
;; G2GL-PROCESS-INSTANCE, G2GL-VARIABLE, G2GL-SERVICE-SWITCH,
;; G2GL-COMMUNICATION-PORT. (MHD 9/27/05)

;;; Instances of these classes should never have existed. We don't understand
;;; how instances of this class have been created, since they have always been
;;; not-user-instantiable, and there is no code that creates instances of them,
;;; but we have a kb containing instances of g2gl-communication-port (see bug
;;; HQ-550-5968 for details) So we are doing a def-substitute so that any other
;;; user kbs that also have instances of any of these classes can load
;;; successfully.

;;; The right thing to do would be to increment kb-flags, but this would
;;; rebuilding all the applications and utilities, and the freeze is hours
;;; away. So instead, we are just using the current value of kb-flags.  kb-flags
;;; was last incremented in January of 2007, and the classes were deleted in
;;; February of 2007, so it is possible that kbs exist that contain instances of
;;; g2-communication-port that were created in the window between these two
;;; events. Since we don't think there should be any kbs containing instances of
;;; this class, except that we have a single example of one, and any kbs created
;;; at that time were created with a beta, and therefore officially unsupported,
;;; we think this is an acceptable risk.  -alatto, 5/4/07

(def-substitute-for-old-class g2gl-communication-port object
  (1+f g2-version-8-3-alpha-0-kb-flags))


;;; The function `get-g2gl-object-icon-description' maps a g2gl-object
;;; subclass to its corresponding built-in icon description.

(defun get-g2gl-object-icon-description (g2gl-object-subclass)
  (cdr (assq g2gl-object-subclass g2gl-object-icon-descriptions-info)))







;;; G2GL allows a limited form of icon customization ("icon substitution") for
;;; subclasses of g2gl-object.  The form this takes at the user level is a
;;; system-table attribute in G2GL-parameters containing a list of associations,
;;; each containins a g2gl-object subclass and a corresponding (general
;;; object) subclass whose icon description is to be used in place of the
;;; built-in icon description for its g2gl-object subclass.


;; The following functions were referred consulted and were adapted to some
;; degree to produce the code below in this section.
;;
;;  flush-icon-caches-and-redraw-instances
;;  adjust-and-draw-images-governed-by-this-class

(defun reflect-g2gl-object-icon-substitutions ()
  (loop with cd
        for (class should-be-object-subclass)
            in (g2gl-object-icon-substitutions g2gl-parameters)
        as icon-description?
           = (and (setq cd (class-description should-be-object-subclass))
                  (class-description-class-case cd
                    ;; OK, we have a valid class - now, it has to be an object;
                    ;; if it's a g2gl-object, get the original, built-in icon
                    ;; description in a special way (i.e., we might have
                    ;; substituted the init form, so don't use that).
                    (g2gl-object
                      (get-g2gl-object-icon-description should-be-object-subclass))
                    (object
                      (get-slot-init-form should-be-object-subclass 'icon-description))))
        do (when (null icon-description?)
             (notify-user
               (if (subclassp should-be-object-subclass 'object)
                   "Has no icon description: ~a" ; should this ever happen?!
                   "Not a subclass of OBJECT: ~a")
               should-be-object-subclass))
        if (not (subclassp class 'g2gl-object))
          do (notify-user "Not a G2GL-Object subclass: ~a" class)
        else if (null (get-g2gl-object-icon-description class))
               ;; Arrange for the following never to happen, at least for
               ;; instantiable instances! each class must have its own unique
               ;; icon-description slot description:  (MHD 9/27/05)
               do (notify-user
                    "The G2GL-Object subclass ~a cannot have its icon substituted."
                    class)
          else collect (gensym-cons class icon-description?)
                 into batch using gensym-cons
        finally
          (reflect-g2gl-object-icon-substitutions-checked batch)
          (reclaim-gensym-tree batch)))

;; To do: improve this facility's error checking by maintaining notes for these
;; problems, rather than by notifying users on the logbook! (MHD 9/9/05)



;;; The function `reflect-g2gl-object-icon-substitutions-checked' is a
;;; subfunction of reflect-g2gl-object-icon-substitutions.  Its batch argument
;;; is an alist whose entries are of the form (class . icon-description?), where
;;; icon-description? is either nil or a valid replacement icon description for
;;; class, which is a subclass eligeable for icon substitiont, i.e., a subclass
;;; of g2gl-object.

;;; This loops over every g2gl-object subclass, checking if its current icon
;;; description, i.e., the icon description in its slot init form, corresponds
;;; to what it should be, either a replacement icon description if one is to be
;;; found in a corresponding class entry in batch, or the original, built-in
;;; icon description otherwise.  If necessary, this then effects any changes
;;; needed, i.e., changing the icon-description slot init form, and reflecting
;;; the changes graphically on instances as needed.

(defun reflect-g2gl-object-icon-substitutions-checked (batch)
  (loop for (class . original) in g2gl-object-icon-descriptions-info
        as initial-id = (get-slot-init-form class 'icon-description)
        as id-to-use-now
           = (or (cdr (assq class batch)) original)
        when (not (eq id-to-use-now initial-id))

          ;; id-to-use-now is either a valid new icon description or the
          ;; original (built-in) icon description for class; use it if
          ;; it's different from the init form.

          do (reflect-g2gl-object-icon-substitutions-1
               class id-to-use-now
               (-w (width-of-icon id-to-use-now)
                   (width-of-icon initial-id))
               (-w (height-of-icon id-to-use-now)
                   (height-of-icon initial-id)))))


(defun reflect-g2gl-object-icon-substitutions-1
    (g2gl-object-class icon-description delta-width delta-height)
  ;; erase each instance with its input connections:
  (loop for a being each class-instance of g2gl-object-class
        do (update-images-of-block a t nil)
           (update-input-connections-of-entity a t icon-description))

  ;; change the icon-description slot's init-form:
  (let ((slot-description
          (slot-description-from-class g2gl-object-class 'icon-description)))
    (setf (slot-init-form slot-description) icon-description))

  ;; set the icon description of each instance, and then draw it with its input
  ;; connections:
  (loop for a being each class-instance of g2gl-object-class
        do (setf (icon-description a) icon-description)
           (when (or (/=w delta-width 0) (/=w delta-height 0))
             (adjust-edges-of-instance a delta-width delta-height)
             (when (or (>w delta-width 0) (>w delta-height 0))
               (enlarge-workspace-for-block-rectangle-if-necessary a nil)))
           (cond ((entity-is-opaque-p a) ; nec?! (MHD)
                  (set-opaque-block a))
                 (t (clear-opaque-block a)))
           (update-images-of-block a nil nil)
           (update-input-connections-of-entity a nil icon-description)))

;; The above was patterned after adjust-and-draw-images-governed-by-this-class.

;; See: g2gl-object-icon-substitutions-may-be-in-use-p; we might want to add
;; logic to maintain that here, as an optimization. Review after Alpha (8.2a0)
;; release! (MHD 9/8/05)



(defun revert-all-g2gl-object-icon-substitions ()
  (loop for (class . original-id)
            in g2gl-object-icon-descriptions-info
        as id = (get-slot-init-form class 'icon-description)
        do (unless (eq id original-id)
             (revert-g2gl-object-icon-substitution
               class id original-id))))


(defun revert-if-g2gl-object-icon-substitution (icon-description)
  (loop for class being each subclass of 'g2gl-object
        as id = (get-slot-init-form class 'icon-description)
        when (eq id icon-description)
          do (revert-g2gl-object-icon-substitution class id)))


(defun revert-g2gl-object-icon-substitution
    (class id &optional original-icon-description-if-known?)
  (let ((original-icon-description?
          (or original-icon-description-if-known?
              (loop for c                ; first time through: c = class
                        in (class-inheritance-path (class-description class))
                    thereis (get-g2gl-object-icon-description class)
                    until (eq c 'g2gl-object))))) ; top of (G2GL-) hierarchy
    (when original-icon-description?
      ;; -- otherwise, class is just a subclass that happens to define its own
      ;; icon description, or happens to inherit an icon description from a
      ;; class that defines its own icon description.
      (let* ((delta-width
               (-w (width-of-icon original-icon-description?)
                   (width-of-icon id)))
             (delta-height
               (-w (height-of-icon original-icon-description?)
                   (height-of-icon id))))
        (reflect-g2gl-object-icon-substitutions-1
          class original-icon-description? delta-width delta-height)))))






;;;; Miscellaneous Functions



;;; Collect-G2GL-flowchart-activities
;;;   (flowchart-activity a, already-visited-activities l):

(defun collect-g2gl-flowchart-activities (a l)
  (cond
    ((memq a l)
     ;; alt: faster for very large flowcharts, if a is found in the
     ;; flowchart-junctions-alist of v, where compilation-version v is an added
     ;; argument.
     l)
    (t
     (let ((revised-l (gensym-cons a l)))
       (loop for out being each output-connection of a
             do (setq revised-l
                      (collect-g2gl-flowchart-activities
                        (output-end-object out)
                        revised-l)))
       revised-l))))





;;; Update-G2GL-variable-value-display
;;;   (G2GL-variable-compilation vc,
;;;    execution-thread-that-might-have-changed-the-value thread):
;;;
;;; Since variable values are displayed only on individual execution displays,
;;; this function needs to be called only if thread has an individual execution
;;; display, but it does not make such an assumption.
;;;
;;; Thread should be involved in executing a body compilation within the scope
;;; of vc.
;;;
;;; This does nothing if vc is a proxy variable, since proxy variables are not
;;; shown on execution displays; also, this does not update the value display of
;;; an outside variable of a compensation handler compilation currently being
;;; executed, because that could cause confusion and in any case would only
;;; persist for the fraction of a second during which thread remained active.
;;;
;;; This is to be called whenever the value of a G2GL variable is changed or
;;; when a new individual execution display is created.  [Note that variable
;;; values are displayed only on individual execution displays.  Note that it
;;; might be necessary to store the variable value as the value of an attribute
;;; of execution-display-object if the value-displaying block is implemented as
;;; a G2 attribute display.  Note that values of proxy variables are not
;;; displayed.]

(defun update-g2gl-variable-value-display (vc thread)
  (loop with thread-or-ancestor-thereof = thread
        with compilations
        with d
        with j fixnum = 0
        with i fixnum = 0
        with f
        with value
        with value-string
        with execution-display-object
        do (setq compilations
                 (g2gl-variable-compilations
                   (body-compilation-this-is-being-used-to-execute
                     thread-or-ancestor-thereof)))
        until (and compilations (memq-p-macro vc compilations))
        do (when (null (setq thread-or-ancestor-thereof
                             (parent-execution-thread
                               thread-or-ancestor-thereof)))
             (return))
        finally
          (when (and (g2gl-execution-displays thread-or-ancestor-thereof)
                     (not (eq (execution-display-mode
                                (setq d (first (g2gl-execution-displays
                                                 thread-or-ancestor-thereof))))
                              'superimposed-tracings))
                     (g2gl-var-body-element-index vc)        ; i.e., not a proxy var.
                     (eq (outside-variable-bindings-for-execution
                           thread-or-ancestor-thereof)
                         (outside-variable-bindings-for-execution thread))
                     ;; -- i.e., the variable is not an outside variable of a
                     ;; compensation handler compilation currently being
                     ;; executed
                     )
            (setq j (g2gl-var-body-element-index vc))
            (setq execution-display-object
                  (managed-svref (vector-of-g2gl-body-elements d) j))
            (setq i (g2gl-variable-index vc))
            (setq f (parent-execution-frame thread-or-ancestor-thereof))
            (with-temporary-gensym-float-creation
                update-g2gl-variable-value-display
              (setq value (managed-svref (g2gl-variable-values-vector f) i))
              (setq value-string
                    (let ((evaluation-value-writing-target-length?
                            ;; If the value is large, this will abbreviate it
                            ;; with ellipses.  C.F. write-stored-value in
                            ;; PROC-UTILS.
                            maximum-length-for-writing-evaluation-values))
                      (twith-output-to-text-string (twrite-g2gl-value value))))
              (loop for b being each subblock of execution-display-object
                    when (frame-of-class-p b 'g2gl-display-message)
                      return (change-text-of-message b value-string)
                    finally
                      (let* ((m (make-message value-string 'g2gl-display-message))
                             (p (make-g2gl-body-position
                                  (+w (right-edge-of-block
                                        execution-display-object)
                                      0) ; nudge/fine positioning; parameterize somewhere?
                                  (+w 2        ; ditto.
                                      (halfw (-w (+w (top-edge-of-block
                                                       execution-display-object)
                                                     (bottom-edge-of-block
                                                       execution-display-object))
                                                 (height-of-block m)))))))
                        (add-to-g2gl-object m execution-display-object p)
                        (reclaim-g2gl-body-position p)))))))





;;; Map-g2gl-execution-display-to-source-process-if-any ... returns a source
;;; G2GL process, if there is one, corresponding to g2gl-execution-display.
;;; There could be none in the case of a "disembodied" process.
;;;
;;; When this is called, the one-execution-thread-that-is-shown-hereon may
;;; either contain nil, in which case nil is returned [can this happen?!], or
;;; contain a valid, active G2GL execution thread.

(defun map-g2gl-execution-display-to-source-process-if-any (g2gl-execution-display)
  (if (one-execution-thread-that-is-shown-hereon g2gl-execution-display)
      (source-g2gl-process
        (parent-compilation-version
          (parent-execution-frame
            (one-execution-thread-that-is-shown-hereon
              g2gl-execution-display))))))


(defun map-g2gl-execution-display-to-source-body-if-any (g2gl-execution-display)
  (let ((g2gl-process?
          (map-g2gl-execution-display-to-source-process-if-any
            g2gl-execution-display)))
    (if g2gl-process?
        (first (subworkspaces g2gl-process?)))))

(defun map-g2gl-execution-display-to-execution-frame-if-any (g2gl-execution-display)
  (if (one-execution-thread-that-is-shown-hereon g2gl-execution-display)
      (parent-execution-frame
        (one-execution-thread-that-is-shown-hereon
          g2gl-execution-display))))







;;; Unset-temporary-breakpoint-for-surrogate-activity-p
;;;   (g2gl-activity a, g2gl-execution-display d)

(defun unset-temporary-breakpoint-for-surrogate-activity-p (a d)
  (let ((c (find-activity-compilation-corresponding-to-surrogate-activity a d)))
    (and c (not (memq c (temporary-breakpoints-for-execution-display d))))))





;;; Unremoved-temporary-breakpoint-for-surrogate-activity-p
;;;   (g2gl-activity a, g2gl-execution-display d)

(defun unremoved-temporary-breakpoint-for-surrogate-activity-p (a d)
  (let ((c (find-activity-compilation-corresponding-to-surrogate-activity a d)))
    (and c (memq c (temporary-breakpoints-for-execution-display d)))))






;;; Set-temporary-breakpoint-for-surrogate-activity
;;;   (g2gl-activity a, g2gl-execution-display d)

(defun set-temporary-breakpoint-for-surrogate-activity (a d)
  (slot-value-push
    (find-activity-compilation-corresponding-to-surrogate-activity a d)
    (temporary-breakpoints-for-execution-display d)))




;;; Remove-temporary-breakpoint-for-surrogate-activity
;;;   (g2gl-activity a, g2gl-execution-display d)

(defun remove-temporary-breakpoint-for-surrogate-activity (a d)
  (setf (temporary-breakpoints-for-execution-display d)
        (delete-slot-value-element
          (find-activity-compilation-corresponding-to-surrogate-activity a d)
          (temporary-breakpoints-for-execution-display d))))






;;; The function `pause-process-instance' pauses the process instance
;;; represented by f, an execution frame, which must be for a non-paused process
;;; instance.  This is primarily for use by the pause-process-inatance command
;;; (see COMMANDS2), and is not part of the detailed G2GL spec.

(defun pause-process-instance (f)
  (unless (process-instance-is-paused f)
    (setf (process-instance-is-paused f) t)
    (reflect-if-g2gl-execution-frame-is-paused f)))




(defun resume-process-instance (f)
  (when (process-instance-is-paused f)
    (resume-paused-process-instance f)
    (reflect-if-g2gl-execution-frame-is-paused f)))





(defun g2gl-execution-display-is-for-paused-process-p (g2gl-execution-display)
  (let ((execution-frame?
          (map-g2gl-execution-display-to-execution-frame-if-any
            g2gl-execution-display)))
    (and execution-frame?
         (process-instance-is-paused execution-frame?))))


(defun do-resume-process-instance-command (execution-display)
  (let ((execution-frame?
          (map-g2gl-execution-display-to-execution-frame-if-any
            execution-display)))
    (when execution-frame?
      (resume-process-instance execution-frame?))))


(defun do-pause-process-instance-command (execution-display)
  (let ((execution-frame?
          (map-g2gl-execution-display-to-execution-frame-if-any
            execution-display)))
    (when execution-frame?
      (pause-process-instance execution-frame?))))


(defun reflect-if-g2gl-execution-frame-is-paused (f)
  (let* ((handle-data? (cdr (g2gl-process-instance-handle f)))
         (g2gl-process-instance?
           (if (and handle-data?
                    (evaluation-item-reference-p handle-data?))
               (evaluation-item-reference-referenced-item handle-data?))))
    (when g2gl-process-instance?
      (unless (eq (process-instance-is-paused f)
                  (g2gl-process-instance-is-paused g2gl-process-instance?))
        ;; -- don't do this if state is already reflected in the
        ;; process-instance object, as when this is invoked via the slot putter.
        (change-slot-value
          g2gl-process-instance?
          'g2gl-process-instance-is-paused
          (process-instance-is-paused f)))))
  (loop for thread in (g2gl-execution-threads f)
        do
    (loop for d in (g2gl-execution-displays thread)
          unless (eq (execution-display-mode d) 'superimposed-tracings)
            do (reflect-if-paused-on-execution-display d f))))


(defun reflect-if-paused-on-execution-display (d f)
  (let ((new-value
          (if (and (process-instance-is-paused f)
                   (null (title-bar-text d)))
              (let ((title (workspace-title d)))
                (prog1 (tformat-text-string "~a - PAUSED" title)
                  (reclaim-text-string title)))
              nil)))
    (change-slot-value d 'title-bar-text new-value)))

;; Consider having additional or different indications of paused/non-paused
;; state besides putting PAUSED in the title bar (or not), and other means of
;; changing that state. Also consider having other changes indicated in the
;; title bar! (E.g., "<N> breakpoints" (if N > 0), "single-step mode" (if in
;; single-step mode), etc.)  For changing, consider tape-deck/VCR style buttons
;; in the title bar (or some floating control window?).  (MHD 8/22/05)





;;; The function `compute-g2gl-process-body-procedure-signature' computes the
;;; variables of the latest (installed/active) compilation version, if any.  If
;;; there are none, it returns the symbol NO-SIGNATURE.  Otherwise, it returns a
;;; freshly allocated slot value that is a list of the form
;;;
;;;   ( { (name type default-value?) } )

(defun compute-g2gl-process-body-procedure-signature (s)
  ;; => NO-SIGNATURE | ( { (name type default-value?) } )
  (if (null (stack-of-compilation-versions s))
      'no-signature
      (loop with v = (first (stack-of-compilation-versions s))
            for vc in (g2gl-variable-compilations (G2GL-body-compilation v))
            when (=f (g2gl-variable-class-code vc)
                     (quoted-g2gl-variable-class-code g2gl-arg-variable))
              collect (slot-value-list
                        (copy-for-slot-value (c-g2gl-variable-name vc))
                        (copy-for-slot-value (c-g2gl-variable-type vc))
                        (copy-for-slot-value (c-default-value-for-g2gl-variable vc)))
                using slot-value-cons)))





;;;; Mutable Data Management Policy

;; by MHD, 1/7/05

;;; A note on the current policy for managing mutable data in expressions and
;;; constants by the expression evaluator, compiler, and related utilities.
;;; Some data types that are mutable in Lisp are used to implement certain data
;;; types to support G2GL's data model: floats, text strings, and truth values
;;; (booleans).  Note that sequences and structure and other mutable data types
;;; are not supported at present in G2GL.  Also, general/fuzzy truth values, as
;;; in G2, are not supported: only the two truth values, absolutely true and
;;; absolutely false, are supported.  We want to avoid boxing/unboxing and
;;; copying so much at evaluation time.  Also, want to avoid entering temporary
;;; float consing contexts so much; once per overall expression evaluation
;;; should be more than enough -- previously it was once per arithmetic
;;; operation.  So, here are the handlings for strings, floats, and booleans
;;; (truth values):

;;; Here's a summary of the handling:
;;;                                      text string / float / truth value
;;; variable initial value               s             mf      TRUE or FALSE
;;; var. init. val. compilation          s'            mf'     unique t/f cons
;;; variable values vector               s'            mf''    unique t/f cons
;;; activity expression parse            s             mf      non-unique t/f cons
;;; activity expression compilation      s'            mf'     unique t/f cons
;;; g2gl-eval                            s'            gf      unique t/f cons
;;;
;;; where, s = string, s' = copy of s, s'' = copy of s', mf = managed float, mf'
;;; = copy of mf, mf'' = copy of mf', gf = gensym float.  T/f cons refers to a
;;; cons of (1000 . truth-value) for "true", (-1000 . truth-value) for false.
;;; The "unique" t/f cons is one or the two particular conses bound to g2gl-true
;;; and g2gl-false (q.v., below), shared and immutable unique conses.

;;; Notice that it follows from the above that managed floats and strings (s''
;;; and m'') in the variable values vector are NOT shared, and should be
;;; explicitly reclaimed.  In the case of the unique t/f conses, they're never
;;; reclaimed, since they're unique global constants.





;;;; G2GL Temporary Values


;;; In many cases, memory is statically allocated into the compilation
;;; structures of a G2Gl process, or it is dynamically created and then stored
;;; in a G2GL variable, or, in the case of floats, dynamically allocated, and
;;; then reclaimed via the mechanisms of the presumably surrounding
;;; with-temporary-gensym-float macro.  For other cases of dynamic allocation of
;;; values that may have to survive throughout an expression evaluation, we use a
;;; temporary G2GL-value facility, with the following interfaces.

;;; The macro `with-temporary-g2gl-values' should be wrapped around a body,
;;; presumably the body of the G2GL expression evaluation function, and it
;;; provides a context for noting newly created temporary G2GL values.  It is
;;; required for this to be wrapped around expression evaluation, and so it may
;;; be assumed that the following operation will be available for use by
;;; expression-evaluation routines.

;;; The function `note-temporary-g2gl-value' should be called to note a
;;; temporary G2GL value, newly created during expression evaluation, whose
;;; liftime ends at the end of this particular expression evaluation.

;;; The principal, and first, uses of the above function are in the functions
;;; g2gl-call-function and g2gl-funcall for calling G2 functions from G2GL; in
;;; general, the results of a function may be dynamically allocated, and a
;;; unique, unshared copy must be returned, effectively to the Lisp stack, as
;;; the result of G2GL-eval, and then later reclaimed (after completion of the
;;; entire expression evaluation).

(defvar current-temporary-g2gl-values)

(defmacro with-temporary-g2gl-values ((&rest options) &body body)
  (declare (ignore options))                ; reserved for future use!?
  `(let ((current-temporary-g2gl-values '()))
     (unwind-protect
          (progn . ,body)
       (when current-temporary-g2gl-values
         (reclaim-temporary-g2gl-values)))))

(defun reclaim-temporary-g2gl-values ()
  (loop for v in current-temporary-g2gl-values
        do (remove-reference-to-g2gl-value v)
        finally
          (reclaim-gensym-list current-temporary-g2gl-values)))

(defun note-temporary-g2gl-value (g2gl-value)
  (gensym-push g2gl-value current-temporary-g2gl-values)
  g2gl-value)

;; See if the overhead of this facility can be reduced, perhaps by wrapping it
;; at a higher level; c.f., with-temporary-gensym-float-creation.  Also, at
;; least tweak some of the above routines.  That should be done later, however,
;; as this is needed ASAP. (MHD 7/26/06)







;;;; G2GL Expression Evaluator

(defconstant g2gl-no-value '(g2gl . no-value))

;; note: see above for defvars for g2gl-true and g2gl-false


(defun-substitution-macro g2gl-eval-atomic-or-simple (expression)
  (cond
    ((or (fixnump expression)
         (symbolp expression)
         (or (eq expression g2gl-true)
             (eq expression g2gl-false))
         (wide-string-p expression))
     expression)
    ((managed-float-p expression)
     (managed-float-value expression))
    ((or (evaluation-sequence-p expression)
         (evaluation-structure-p expression))
     expression)
    ((atom expression)
     (g2gl-eval-expression-error
       'unknown-datum
       ;; This shouldn't happen, abort?
       (tformat "atomic expression of unknown type: ~a" expression)))
    ((evaluation-item-reference-p expression) ; impl: a cons w/a special cdr
     (evaluation-item-reference-referenced-item expression))
    (t nil)))


(defun-substitution-macro g2gl-eval (expression thread)
  (cond

    ((g2gl-variable-compilation-p expression)
     ;; note that the following cannot return nil, since it means "unbound", and
     ;; results in a Lisp throw to a catch that processes the G2GL error.
     (g2gl-eval-variable expression thread t))

    ;; The following returns a non-nil value or nil, meaning to fall
    ;; through. Note that nil cannot be a value.
    ((g2gl-eval-atomic-or-simple expression))

    ;; If here, we must have a cons, one not handled by
    ;; g2gl-eval-atomic-or-simple, which is to be handled by the following call.
    (t (g2gl-eval-non-atomic-or-simple expression thread t))))


;; This function should be combined with g2gl-eval, possibly making g2gl-eval
;; take a third argument specifying whether or not to allow no-value, but for
;; minimal diffs, I am using cut and paste in this thread.  -jv, 5/23/08

(defun-substitution-macro g2gl-eval-allowing-no-value (expression thread)
  (cond

    ((g2gl-variable-compilation-p expression)
     ;; note that the following cannot return nil, since it means "unbound", and
     ;; results in a Lisp throw to a catch that processes the G2GL error.
     (g2gl-eval-variable expression thread t))

    ;; The following returns a non-nil value or nil, meaning to fall
    ;; through. Note that nil cannot be a value.
    ((g2gl-eval-atomic-or-simple expression))

    ;; If here, we must have a cons, one not handled by
    ;; g2gl-eval-atomic-or-simple, which is to be handled by the following call.
    (t (g2gl-eval-non-atomic-or-simple expression thread t))))





;;; evaluate-g2gl-expression
;;;   (G2GL-expression-compilation ec, execution-thread thread):

(defun-allowing-unwind evaluate-g2gl-expression (ec thread)
  (with-temporary-g2gl-values ()
    (g2gl-eval ec thread)))



(defvar g2gl-failed-activity-name nil)


;;; The macro `catch-g2gl-eval-fault' is an environment macro, establishing a
;;; catch-g2gl-eval-fault lexical scope that must be wrapped around a body that
;;; may "throw a fault", meaning, in Lisp, exit nonlocally to the special catch
;;; tag, the value of special variable `g2gl-eval-error', whose value is a
;;; unique Lisp object.
;;;
;;; The fault-info-place arg should be a setf'able form, to be assigned the
;;; return value of the form.  This macro arranges for the value of the form to
;;; be nil unless a fault is thrown, in which case the value result of the throw
;;; is a g2gl-execution-fault structure.
;;;
;;; If fault-info-place is non-nil after this form is evaluated, the caller
;;; generally should call signal-g2gl-execution-fault, or some caller thereof,
;;; to effect a G2GL error.

(defmacro g2gl-eval-expression-error-with-activity-name (fault-name activity-name &body desc-writers)
  `(progn
     (setf g2gl-failed-activity-name ,activity-name)
     (throw g2gl-eval-error
       (make-g2gl-system-fault-with-activity-name
	     ,fault-name
		 ,activity-name
	     ,@desc-writers))))

(defun g2gl-eval-handle-non-numeric-arg (operation a &optional (b 0))
  (g2gl-eval-expression-error
    'arithmetic-error
    (tformat "operation ~a on non-numeric value" operation)
    (cond ((numberp a)
           (twrite " ") (twrite-g2gl-value b))
          ((numberp b)
           (twrite " ") (twrite-g2gl-value a))
          (t
           (twrite "s ") (twrite-g2gl-value a)
           (twrite " and ") (twrite-g2gl-value b)))))





(defun-substitution-macro g2gl-+ (a b)
  (or (cond
        ((and (fixnump a) (fixnump b))
         (+f a b))
        ((gensym-float-p a)
         (if (gensym-float-p b)
             (+e a b)
             (if (fixnump b) (+e a (coerce-fixnum-to-gensym-float b)))))
        ((gensym-float-p b)
         (if (fixnump a) (+e (coerce-fixnum-to-gensym-float a) b))))
          (if (eq a g2gl-no-value)
            g2gl-no-value
              (if (eq b g2gl-no-value)
                g2gl-no-value
                  (g2gl-eval-handle-non-numeric-arg '+ a b)))))

(defun-substitution-macro g2gl-1+ (a)
  (or (cond
        ((fixnump a)
         (1+f a))
        ((gensym-float-p a)
         (+e a 1.0)))
        (if (eq a g2gl-no-value)
          g2gl-no-value
          (g2gl-eval-handle-non-numeric-arg '1+ a))))

(defun-substitution-macro g2gl-- (a b)
  (or (cond
        ((and (fixnump a) (fixnump b))
         (-f a b))
        ((gensym-float-p a)
         (if (gensym-float-p b)
             (-e a b)
             (if (fixnump b) (-e a (coerce-fixnum-to-gensym-float b)))))
        ((gensym-float-p b)
         (if (fixnump a) (-e (coerce-fixnum-to-gensym-float a) b))))
          (if (eq a g2gl-no-value)
            g2gl-no-value
              (if (eq b g2gl-no-value)
                g2gl-no-value
                  (g2gl-eval-handle-non-numeric-arg '- a b)))))

(defun-substitution-macro g2gl-1- (a)
  (or (cond
        ((fixnump a)
         (1-f a))
        ((gensym-float-p a)
         (-e a 1.0)))
        (if (eq a g2gl-no-value)
          g2gl-no-value
	  (g2gl-eval-handle-non-numeric-arg '1- a))))



(defun-substitution-macro g2gl-unary-- (a)
  (or (cond
        ((fixnump a) (-f a))
        ((gensym-float-p a) (-e a)))
        (if (eq a g2gl-no-value)
          g2gl-no-value
	  (g2gl-eval-handle-non-numeric-arg '- a))))


(defun-substitution-macro g2gl-* (a b)
  (or (cond
        ((and (fixnump a) (fixnump b))
         (*f a b))
        ((gensym-float-p a)
         (if (gensym-float-p b)
             (*e a b)
             (if (fixnump b) (*e a (coerce-fixnum-to-gensym-float b)))))
        ((gensym-float-p b)
         (if (fixnump a) (*e (coerce-fixnum-to-gensym-float a) b))))
          (if (eq a g2gl-no-value)
            g2gl-no-value
              (if (eq b g2gl-no-value)
                g2gl-no-value
                  (g2gl-eval-handle-non-numeric-arg '* a b)))))

(defun-substitution-macro g2gl-/ (a b)
  (or (cond
        ((and (fixnump a) (fixnump b))
         (if (=f b 0)
             (g2gl-eval-expression-error
               'arithmetic-error (twrite 'divide-by-zero))
             (/e (coerce-fixnum-to-gensym-float a)
                 (coerce-fixnum-to-gensym-float b))))
        ((gensym-float-p a)
         (if (gensym-float-p b)
             (/e a
                 (if (=e b 0.0)
                     (g2gl-eval-expression-error
                       'arithmetic-error (twrite 'divide-by-zero))
                     b))
             (if (fixnump b)
                 (/e a
                     (if (=f b 0)
                         (g2gl-eval-expression-error
                           'arithmetic-error (twrite 'divide-by-zero))
                         (coerce-fixnum-to-gensym-float b))))))
        ((gensym-float-p b)
         (if (fixnump a)
             (/e (coerce-fixnum-to-gensym-float a)
                 (if (=e b 0.0)
                     (g2gl-eval-expression-error
                       'arithmetic-error (twrite 'divide-by-zero))
                     b)))))
          (if (eq a g2gl-no-value)
            g2gl-no-value
              (if (eq b g2gl-no-value)
                g2gl-no-value
                  (g2gl-eval-handle-non-numeric-arg '/ a b)))))


(defun g2gl-^ (a b)
  (let ((base 0.0)
        (power 0.0))
    (declare (type gensym-float base power))
    (cond
      ((fixnump a)
       (setq base (coerce-to-gensym-float a)))
      ((gensym-float-p a)
       (setq base a))
      ;; non-numeric arg - error cases follow
      ((or (gensym-float-p b) (fixnump b))
       (g2gl-eval-handle-non-numeric-arg '^ a))
      (t
       (g2gl-eval-handle-non-numeric-arg '^ a b)))
    (cond
      ((fixnump b)
       (setq power (coerce-to-gensym-float b)))
      ((gensym-float-p b)
       (setq power b))
      ;; non-numeric arg - error case follow
      (t
       (g2gl-eval-handle-non-numeric-arg '^ b)))
    (cond ((>e base 0.0)
           ;; Positive Base ok.  Don't need to test for a ratio result
           ;; since we have float arguments.
           (expte base power))
          ((=e base 0.0)
           ;; Base is 0.0
           (cond
             ((=e power 0.0)
              ;; (expt 0.0 0.0) would cause a Common Lisp error.
              1.0)
             ((>e power 0.0)
              ;; (expt 0.0 +power-float) is 0.0
              0.0)
             (t
              ;; (expt 0.0 -power-float) is undefined.
              (g2gl-eval-expression-error
                'arithmetic-error
                (tformat                ; based on g2-exponent-evaluation-float
                  "the arguments to the exponent operator (^) were a zero ~
                   base ~a and a negative power ~a.  These values produce ~
                   an undefined result."
                  base power)))))
          (t
           ;; Negative base.  (expt -base-float +power-float) produces a
           ;; complex numeric result which is not allowed in G2.
           (let ((truncated-power (truncate power)))
             (cond
               ;; Test for a power of the form n.0 and avoid a complex result.
               ((= power truncated-power)
                (expt base truncated-power))
               (t
                ;; result is a complex number, not a supported type in G2/G2GL
                (g2gl-eval-expression-error
                  'arithmetic-error
                  (tformat                ; based on g2-exponent-evaluation-float
                    "the arguments to the exponent operator (^) were a ~
                     negative base ~a and a floating point power ~a.  These ~
                     values produce a complex number, which is not supported ~
                     in G2GL."
                    base power)))))))))

;; The above implementation is based on the stack evaluator's
;; g2-exponent-evaluation-float function, q.v. (MHD 4/25/05)


(defun-substitution-macro g2gl-= (a b)
  (if (cond
        ((eq a b)
         ;; this case handles, at least, G2GL truth values and symbols
         t)
        ((and (fixnump a) (fixnump b))
         ;; (the above would really handle fixnums, but that's not guaranteed to
         ;; work in CL, so don't rely upon that.)
         (=f a b))
        ((and (wide-string-p a) (wide-string-p b))
         (string-equalw a b))
        ((gensym-float-p a)
         (if (gensym-float-p b)
             (=e a b)
             (if (fixnump b)
                 (=e a (coerce-fixnum-to-gensym-float b)))))
        ((gensym-float-p b)
         (if (fixnump a)
             (=e (coerce-fixnum-to-gensym-float a) b)))
        ((and (evaluation-sequence-p a) (evaluation-sequence-p b))
         (evaluation-sequence-eql a b))
        ((and (evaluation-structure-p a) (evaluation-structure-p b))
         (evaluation-structure-eql a b)))
      g2gl-true
      g2gl-false))

(defun-substitution-macro g2gl-/= (a b)
  (g2gl-not (g2gl-= a b)))

(defun-substitution-macro g2gl-< (a b)
  (if (cond
        ((and (fixnump a) (fixnump b))
         (<f a b))
        ((gensym-float-p a)
         (if (gensym-float-p b)
             (<e a b)
             (if (fixnump b)
                 (<e a (coerce-fixnum-to-gensym-float b))
                 (g2gl-eval-handle-non-numeric-arg '< a b))))
        ((gensym-float-p b)
         (if (fixnump a)
             (<e (coerce-fixnum-to-gensym-float a) b)
             (g2gl-eval-handle-non-numeric-arg '< a b)))
        (t
         (g2gl-eval-handle-non-numeric-arg '< a b)))
      g2gl-true
      g2gl-false))

(defun-substitution-macro g2gl-> (a b)
  (if (cond
        ((and (fixnump a) (fixnump b))
         (>f a b))
        ((gensym-float-p a)
         (if (gensym-float-p b)
             (>e a b)
             (if (fixnump b)
                 (>e a (coerce-fixnum-to-gensym-float b))
                 (g2gl-eval-handle-non-numeric-arg '> a b))))
        ((gensym-float-p b)
         (if (fixnump a)
             (>e (coerce-fixnum-to-gensym-float a) b)
             (g2gl-eval-handle-non-numeric-arg '> a b)))
        (t
         (g2gl-eval-handle-non-numeric-arg '> a b)))
      g2gl-true
      g2gl-false))

(defun-substitution-macro g2gl-<= (a b)
  (g2gl-not (g2gl-> a b)))

(defun-substitution-macro g2gl->= (a b)
  (g2gl-not (g2gl-< a b)))


(defun-substitution-macro g2gl-and (expressions thread)
  (if (loop for sub in expressions always (g2gl-true-p (g2gl-eval sub thread)))
      g2gl-true
      g2gl-false))

(defun-substitution-macro g2gl-or (expressions thread)
  (if (loop for sub in expressions thereis (g2gl-true-p (g2gl-eval sub thread)))
      g2gl-true
      g2gl-false))

(defun-substitution-macro g2gl-if (g2gl-if-args thread)
  (if (g2gl-true-p (g2gl-eval (first-of-cons g2gl-if-args) thread))
      (g2gl-eval (second-of-cons g2gl-if-args) thread)
      (g2gl-eval (or (third-of-cons g2gl-if-args) g2gl-false) thread)))



;;; The function `g2gl-call-function' .... Note: in the non-system-defined
;;; function case (i.e., presumably an intended user-defined function call),
;;; this expects that the function name will be CALL-FUNCTION (thanks to a
;;; grammar transformation), and that the first arg will be a symbol, the name
;;; supposedly of a user-defined function.  This will attempt a global G2 name
;;; reference.  If it does not yield an item of one of the classes
;;; function-definition, foreign-function-declaration, or tabular-function, this gets

(defun g2gl-call-function (g2gl-function-and-args thread)
  (let* ((g2gl-function (car g2gl-function-and-args))
         (g2gl-function-args (cdr g2gl-function-and-args))
         (user-fn?
           (if (eq g2gl-function 'call-function)
               (let ((fn?
                       (get-instance-with-name-if-any
                         nil (car g2gl-function-args))))
                 (or (if fn?
                         (frame-class-case fn?
                           ((function-definition
                              foreign-function-declaration
                              tabular-function)
                            fn?)
                           (t nil)))
                     (g2gl-eval-expression-error
                       'function-calling-error
                       (tformat "undefined function: ~a"
                                (car g2gl-function-args))))))))
    (g2gl-funcall-1 g2gl-function
                    (loop for arg in g2gl-function-args
                          as arg-number from 0
                          collect (if (and (=f arg-number 0) user-fn?)
                                      user-fn?
                                      (g2gl-eval arg thread))
                            using gensym-cons)
                    thread)))


(defun g2gl-funcall (g2gl-function-and-args thread)
  (let* ((g2gl-function (car g2gl-function-and-args))
         (g2gl-function-args (cdr g2gl-function-and-args))
         (user-fn
           (let ((fn? (g2gl-eval g2gl-function thread)))
             (if fn?
                 (if (framep fn?)
                     (frame-class-case fn?
                       ((function-definition
                          foreign-function-declaration
                          tabular-function)
                        fn?)
                       (t
                         (g2gl-eval-expression-error
                           'function-calling-error
                           (tformat "~a: ~NF is not a function"
                                    (car g2gl-function-args)
                                    fn?))))
                     (g2gl-eval-expression-error
                       'function-calling-error
                       (tformat "~a: ~NV is not a function"
                                (car g2gl-function-args)
                                fn?)))
                 (g2gl-eval-expression-error
                   'function-calling-error
                   'g2gl-funcall
                   (tformat "~a: no value for function expression"
                            (car g2gl-function-args)))))))
    (g2gl-funcall-1 'call-function
                    (gensym-cons
                      user-fn
                      (loop for arg in g2gl-function-args
                            collect (g2gl-eval arg thread)
                              using gensym-cons))
                    thread)))


(defun g2gl-funcall-1 (g2gl-function g2gl-evaluated-args thread)
  (let* ((item-or-evaluation-value-args
           (loop for arg in g2gl-evaluated-args collect 
              (progn
                (if (eq arg g2gl-no-value)
                    (return-from g2gl-funcall-1 g2gl-no-value))
                (copy-g2gl-value-as-item-or-evaluation-value arg))
              using gensym-cons))
         (frame-for-tracing-and-breakpoints
           ;; Use the G2GL process frame for this.  It would be nice to use the
           ;; particular activity that this function call expression comes from,
           ;; but I don't see any way to get to it.  In fact it might have been
           ;; discarded after compilation!  -dougo, 10/19/05
           (source-g2gl-process
             (parent-compilation-version
               (parent-execution-frame thread)))))
    (multiple-value-bind (value errors)
        (call-g2-function-for-g2gl
          g2gl-function item-or-evaluation-value-args
          frame-for-tracing-and-breakpoints)
      (cond
        (errors
         (g2gl-eval-expression-error
           'function-calling-error
           (loop for error in errors for first = t then nil do
             (unless first (tformat "~%"))
             (twrite error))
           (reclaim-gensym-list errors)))
        (t
         (reclaim-gensym-list g2gl-evaluated-args)
         (loop for arg in item-or-evaluation-value-args
               when (evaluation-value-p arg) do (reclaim-evaluation-value arg))
         (reclaim-gensym-list item-or-evaluation-value-args)
         (note-temporary-g2gl-value
           (convert-item-or-evaluation-value-to-g2gl-value value)))))))




;;; The macro `g2gl-format-form' evaluates a list of expressions and writes
;;; their values to a (temporary) evaluation text.  Text and symbols are written
;;; "beautifully", i.e. without double-quotes or @-escapes.  Cf. the
;;; `format-form' stack evaluator.

(defun-substitution-macro g2gl-format-form (expressions thread)
  (note-temporary-g2gl-value
    (twith-output-to-wide-string
      (loop for expr in expressions
            for val = (g2gl-eval expr thread) do
        (if (or (wide-string-p val) (symbolp val))
            (twrite val)
            (twrite-g2gl-value val))))))




;;; The function `g2gl-get-attribute-value' accesses the attribute of either a
;;; frame or structure, returning the result as newly referenced G2GL value
;;; (after possible coercion from the original evaluation value).  This makes no
;;; assumption as to whether frame-or-structure is actually of the appropriate
;;; data type, and checks for that may result in runtime error conditions.  This
;;; assumes attribute-name and class-qualifier? are symbols, but not necessarily
;;; that they are valid with respect to the frame or structure to which they're
;;; applied, possibly resulting in further runtime error conditions.

(defun g2gl-get-attribute-value (frame-or-structure attribute-name class-qualifier?)
  (let (slot-description value frame)
    (cond
      ((evaluation-structure-p frame-or-structure)
       (cond
         (class-qualifier?
          (g2gl-eval-expression-error
            'structure-attribute-fetch-error
            (tformat "~NV has no ~NQ attribute"
                     frame-or-structure attribute-name class-qualifier?)))
         (t (let* ((slot-not-found '#.(list nil))
                   (value
                     (evaluation-structure-slot
                       frame-or-structure attribute-name slot-not-found)))
              (cond
                ((eq value slot-not-found)
                 (g2gl-eval-expression-error
                   'structure-attribute-fetch-error
                   (tformat "~NV has no ~a attribute"
                            frame-or-structure attribute-name )))
                (t
                 (note-temporary-g2gl-value
                   (convert-item-or-evaluation-value-to-g2gl-value
                     (copy-if-evaluation-value value)))))))))
      ((not (framep (setq frame frame-or-structure)))
       (g2gl-eval-expression-error
         'attribute-fetch-error
         (twrite-g2gl-value frame)
         (twrite " is not an item or structure")))
      ((null (setq slot-description
                   (get-slot-description-of-frame
                     (unalias-slot-name-if-necessary attribute-name frame)
                     frame
                     class-qualifier?)))
       (g2gl-eval-expression-error
         'attribute-fetch-error
         (tformat "~NF has no ~NQ attribute"
                  frame attribute-name class-qualifier?)))
      ;; need to distinguish user data from non.  need to go through "attribute
      ;; export", especially on system defined slots! -- UPDATE: switch to
      ;; get-attribute-description-evaluation-value (below) may largely take
      ;; care of that. (MHD 10/3/05)

      ;; NOTE: TO DO: (!) Need to keep track of the newly consed item so that it
      ;; can be reclaimed later. (!) (MHD 10/3/05)

      ;; For a value that is an item, this just returns that item. For an
      ;; invalid or inaccessible value (including nil), this function returns
      ;; nil.
      ((setq value (get-attribute-description-evaluation-value
                     frame slot-description))
       (note-temporary-g2gl-value
         (convert-item-or-evaluation-value-to-g2gl-value value))))))



;;; The function `convert-item-or-evaluation-value-to-g2gl-value' takes an item
;;; (frame) or an unshared evaluation value and incorporates coerces it into a
;;; G2GL value if possible, reclaiming or incorporating the argument value into
;;; the result.  If a value cannot be coerced, nil is returned.
;;;
;;; Note that a managed float is converted to a gensym float, with the
;;; managed-float structure reclaimed.  This must be called in a temporary
;;; gensym-float creation context.
;;;
;;; The value can be used in a G2GL evaluation context.  It is not suitable for
;;; storing, however.  Convert-item-or-evaluation-value-to-g2gl-value can be
;;; used to create a G2GL value reference, suitable for storing in some data
;;; structure that survives the current evaluation context.
;;;
;;; Note: for "fuzzy" (non-exact) truth values, they're coerced using G2's
;;; default fuzzy truth rounding (function evaluation-truth-value-true-p) to
;;; G2GL's true or false value.

(defun convert-item-or-evaluation-value-to-g2gl-value (item-or-evaluation-value)
  (cond
    ((framep item-or-evaluation-value)
     item-or-evaluation-value)
    (t (let ((evaluation-value item-or-evaluation-value))
         (cond
           ((managed-float-p evaluation-value)
            (prog1 (managed-float-value evaluation-value)
              (reclaim-managed-float evaluation-value)))
           ((eq evaluation-value evaluation-true-value)
            g2gl-true)
           ((eq evaluation-value evaluation-false-value)
            g2gl-false)
           ((evaluation-truth-value-p evaluation-value)
            (prog1 (if (evaluation-truth-value-true-p evaluation-value)
                       g2gl-true
                       g2gl-false)
              (reclaim-evaluation-truth-value evaluation-value)))
           ;; Anything else is assumed to be an acceptable G2GL value and is
           ;; assumed to have already been sufficiently copied or had its
           ;; reference count incremented.
           (t evaluation-value))))))






;;; The substitution macro `convert-evaluation-value-to-slot-value-for-g2gl'
;;; efficiently determines the minimal conversion necessary for
;;; evaluation-value, which must can only be an evaluation that could possibly
;;; have been converted from a G2GL value, into a slot value, incorporating the
;;; argument evaluation-value into the result if possible.  That is, any
;;; reclamable structure in the argument must be fresh and unshared.  The result
;;; is an equivalent value suitable for storing as a slot value.

(defun-substitution-macro convert-evaluation-value-to-slot-value-for-g2gl
    (evaluation-value)
  ;; adapted from code in conclude-into-attribute-component
  (cond
    ((or (eq evaluation-value evaluation-true-value)
         (eq evaluation-value evaluation-false-value))
     (slot-value-list
       (evaluation-truth-value-value evaluation-value)
       'truth-value))
    (t
     ;; all set with all other known cases, esp. floats and text strings:
     evaluation-value)))



;;; The function `g2gl-set-attribute-value' is to be used to assign values
;;; directly into user-defined attributes, known in BPEL as "message parts", of
;;; G2GL-message instances (only).
;;;
;;; The assignment is done using the relatively high-performance setting
;;; primitive set-slot-description-value to assign the value.  This function's
;;; contract permits it to to cut a number of corners vs. conclude-style
;;; assignment, including not triggering forward chaining, not updating table
;;; representations, etc.
;;;
;;; If there are errors, this raises a fault, a non-local "throw" exit in Lisp,
;;; and never returns.  Otherwise, this does the assignment and returns no
;;; particular value.
;;;
;;; NB: the representation of "messages" in G2GL is expected to change in a
;;; relatively near-future relase. At that time, they will probably be
;;; represented some other datatype, and no longer be frame instances at all.
;;; (MHD 5/11/05)

(defun g2gl-set-attribute-value
    (frame attribute-name value class-qualifier?)
  (let (slot-description old-value converted-value)
    (cond
      ((or (not (framep frame))
           (not (frame-of-class-p frame 'g2gl-message)))
       (g2gl-eval-expression-error
         'attribute-set-error
         (twrite-g2gl-value frame)
         (tformat " is not a G2GL-message: cannot assign attribute ~NQ"
                  attribute-name class-qualifier?)))
      ((null (setq slot-description
                   (get-slot-description-of-frame
                     (unalias-slot-name-if-necessary attribute-name frame)
                     frame class-qualifier?)))
       (g2gl-eval-expression-error
         'attribute-set-error
         (tformat "~NF has no ~NQ attribute"
                  frame attribute-name class-qualifier?)))
      ((not (g2gl-value-acceptable-for-g2-attribute-p value))
       (g2gl-eval-expression-error
         'attribute-set-error
         (twrite-g2gl-value value)
         (twrite " is an invalid value for an attribute")))
      ((framep (setq old-value
                     (get-slot-description-value frame slot-description)))
       (g2gl-eval-expression-error
         'attribute-set-error
         (tformat "cannot assign a new value to a G2GL-message attribute ~
                   containing an item.  The ~NQ of ~NF contains an instance ~
                   of class ~A."
                  attribute-name class-qualifier? frame (class old-value))))
      (t
       (setq converted-value
             (if (and (fixnump value)
                      (eq (slot-type-specification slot-description) 'float))
                 ;; Allow an integer to be assigned to a float attribute by
                 ;; first converting it to a float.  See HQ-5113106 "G2GL: can't
                 ;; store an integer in a float variable or attribute".
                 ;; -dougo, 11/7/05
                 (make-evaluation-float (coerce-fixnum-to-gensym-float value))
                 (copy-g2gl-value-as-item-or-evaluation-value value)))
       (cond
         ((not (type-specification-type-p
                 converted-value
                 (slot-type-specification slot-description)))
          (reclaim-evaluation-value converted-value)
          (g2gl-eval-expression-error
            'attribute-set-error
            (twrite-g2gl-value value)
            (tformat
              " is not a valid type of value for the ~NQ attribute of ~NF"
              attribute-name class-qualifier? frame)))
         (t
          (setq converted-value
                (convert-evaluation-value-to-slot-value-for-g2gl
                  converted-value))
          (change-slot-description-value-without-updating-representations
            frame slot-description converted-value
            nil nil nil nil nil)))))))


(defun g2gl-conclude-attribute-value
    (frame attribute-name value class-qualifier?)
  (let (value-for-attribute)
    (cond
      ((not (framep frame))
       (g2gl-eval-expression-error
         'attribute-conclude-error
         (twrite-g2gl-value frame)
         (tformat " is not an item: cannot conclude attribute ~NQ"
                  attribute-name class-qualifier?)))
      ((not (g2gl-value-acceptable-for-g2-attribute-p value))
       (g2gl-eval-expression-error
         'attribute-conclude-error
         (twrite-g2gl-value value)
         (twrite " is an invalid value for an attribute")))
      (t
       (setq value-for-attribute
             (copy-g2gl-value-as-item-or-evaluation-value value))
       (let* ((*current-computation-frame* frame)
              (problem-string?
                (conclude-into-attribute-component
                  frame attribute-name class-qualifier?
                  value-for-attribute nil nil nil)))
         (cond
           (problem-string?
            (g2gl-eval-expression-error
              'attribute-conclude-error
              (twrite problem-string?)
              (reclaim-text-string problem-string?)))
           (t nil)))))))                ; success.




;;; The function `g2gl-set-structure-attribute-value' handles the expression
;;; "the <attribute> of <variable> = <value>" when the variable holds a
;;; structure or is uninitialized.  The variable is updated to hold a structure
;;; with the new attribute value.

(defun g2gl-set-structure-attribute-value (vc structure? attribute value thread)
  (let* ((attr-name
           ;; If the attribute is class-qualified, ignore the class qualifier,
           ;; which is what G2 currently does.  See HQ-5452386 "concluding a
           ;; class-qualified attribute name of a structure is allowed".
           ;; -dougo, 2/13/07
           (if (atom attribute) attribute (third attribute)))
         (new-value (copy-g2gl-value-as-item-or-evaluation-value value)))
    (cond (structure?
           ;; The following sequence will make sure that the structure is copied
           ;; if and only if we do not have the only reference to it.
           (setq structure? (add-reference-to-g2gl-value structure?))
           (set-value-of-g2gl-variable vc nil thread)
           (setq structure?
                 (obtain-mutable-evaluation-structure-copy structure?))
           (setf (evaluation-structure-slot structure? attr-name) new-value)
           (set-value-of-g2gl-variable vc structure? thread))
          (t
           (set-value-of-g2gl-variable
             vc
             (allocate-evaluation-structure-inline
               attr-name new-value)
             thread)))))





;;; The function `g2gl-value-p' is true if thing is a valid G2GL value.  This is
;;; true if thing is non-nil, and either identical to the value of either of the
;;; special variables g2gl-true or g2gl-false, an evaluation-item reference, an
;;; evaluation sequence or structure, or an integer (fixnum), symbol, managed
;;; float, gensym float, or a wide string.

;; This function is slightly optimized for speed, with the up-front checks for
;; nil and consp.  I would rather respect abstraction barriers a little better
;; and combine this with the acceptable-for-foo functions below to make a clear
;; type hierarchy, but for now I'm leaving this the way it was (but adding
;; sequences and structures).  -dougo, 11/14/06

(def-concept g2gl-value)

(defun g2gl-value-p (thing)
  (and thing
       (if (consp thing)
           (or (eq thing g2gl-true)
               (eq thing g2gl-false)
               (evaluation-item-reference-p thing)
               (evaluation-sequence-p thing)
               (evaluation-structure-p thing))
           (or (fixnump thing)
               (symbolp thing)
               (managed-float-p thing)
               (gensym-float-p thing)
               (wide-string-p thing)))))



(defun g2gl-value-acceptable-for-g2-attribute-p (value)
  (or (evaluation-sequence-p value)
      (evaluation-structure-p value)
      (g2gl-value-acceptable-for-g2-variable-p value)))

(defun g2gl-value-acceptable-for-g2-variable-p (value)
  (or (eq value g2gl-true)
      (eq value g2gl-false)
      (fixnump value)
      (symbolp value)
      (managed-float-p value)
      (gensym-float-p value)
      (wide-string-p value)))




(defun g2gl-conclude-g2-variable (variable-or-parameter value)
  (cond
    ((not (and (framep variable-or-parameter)
               (frame-of-class-p
                 variable-or-parameter 'variable-or-parameter)))
     (g2gl-eval-expression-error
       'conclude-error
       (twrite-g2gl-value variable-or-parameter)
       (twrite " is not a variable or parameter")))
    ((not (g2gl-value-acceptable-for-g2-variable-p value))
     (g2gl-eval-expression-error
       'conclude-error
       (twrite-g2gl-value value)
       (tformat " cannot be concluded into ~NF" variable-or-parameter)))
    (t
     (let* ((*current-computation-frame* variable-or-parameter)
            (problem-string?
              (put-current-evaluation-value
                variable-or-parameter
                (copy-g2gl-value-as-item-or-evaluation-value value)
                'never nil nil)))
       (cond
         (problem-string?
          (g2gl-eval-expression-error
            'conclude-error
            (twrite problem-string?)
            (reclaim-text-string problem-string?)))
         (t nil))))))


(defun-substitution-macro g2gl-do-conclude (place value-expression thread)
  (case (car place)
    (the
     (let ((attribute (second place)))
       ;; Note: (second place) may be an attribute-name symbol or a list of the
       ;; form: (CLASS-QUALIFIED-NAME class attribute-name)
       (g2gl-conclude-attribute-value
         (g2gl-eval (third place) thread)
         (if (atom attribute) attribute (third attribute))
         (g2gl-eval value-expression thread)
         (if (atom attribute) nil (second attribute)))))
    (t
     (g2gl-conclude-g2-variable
       (g2gl-eval place thread)                ; (VARIABLE-COMPILATION <vc>)
       (g2gl-eval value-expression thread)))))


(defun-substitution-macro g2gl-do-assignment (place value-expression thread)
  (case (car place)
    (the
     (let* ((attribute (second place))
            (msg-expression (third place))
            (value (g2gl-eval value-expression thread))
            (vc (cond ((g2gl-variable-compilation-p msg-expression)
                       msg-expression)
                      ((and (consp msg-expression)
                            (eq (first msg-expression) 'variable-compilation))
                       (second msg-expression))))
            (message (when vc (get-value-of-g2gl-variable
                                vc (parent-execution-frame thread)))))
       (if (and vc (or (not message) (evaluation-structure-p message)))
           ;; The expression is "the <attribute> of <variable> = <value>", where
           ;; the variable is either uninitialized or holds a structure.
           ;; TO DO: This could also handle more deeply nested places, although
           ;; that is not supported by BPEL's assign activity.
           (g2gl-set-structure-attribute-value
             vc message attribute value thread)
           (g2gl-set-attribute-value
             (g2gl-eval msg-expression thread)
             (if (atom attribute) attribute (third attribute))
             value
             (if (atom attribute) nil (second attribute))))))
    (t
     (set-value-of-g2gl-variable
       (second place)                        ; (VARIABLE-COMPILATION vc)
       (add-reference-to-g2gl-value
         (g2gl-eval value-expression thread))
       thread))))


(defun get-name-for-g2gl-variable (vc)
  (or
    (c-g2gl-variable-name vc)
    (intern-text-string                        ; ever nil?!
      (tformat-text-string "UNNAMED-VARIABLE-~d" (g2gl-variable-index vc)))))


(defun g2gl-eval-variable (vc thread allow-no-value-p)
  (let ((val (get-value-of-g2gl-variable vc (parent-execution-frame thread))))
    (cond
      ((null val)
       (if allow-no-value-p
           g2gl-no-value
       (g2gl-eval-expression-error
         'unbound-variable
             (tformat "variable ~a has no value" (get-name-for-g2gl-variable vc)))))
      ((managed-float-p val)
       (managed-float-value val))
      ((evaluation-item-reference-p val)
       (cond
         ((evaluation-item-reference-referenced-item val))
         (t
           (update-g2gl-variable-value-display vc thread)
           (g2gl-eval-expression-error
             'invalid-variable-binding
             (tformat "variable ~a has a deleted item as its value"
                      (get-name-for-g2gl-variable vc))))))
      (t val))))


;;; The function `g2gl-eval-non-atomic-or-simple' is a subfunction of
;;; g2gl-eval, q.v., above, which is intended to handle non-atomic and
;;; non-simple expressions, i.e., those not handled by
;;; g2gl-eval-atomic-or-simple.

;;; GENSYMCID-1289: G2GL use case of performance degradation from March 2014 to July 2014

(eval-when (:compile-toplevel :load-toplevel :execute)

  ;; All operators used in `g2gl-eval-non-atomic-or-simple' must be registered here.
  (defvar *all-g2gl-operators*
    '(VARIABLE-COMPILATION
      1+
      1-
      NOT
      -
      +
      =
      /=
      <
      >
      <=
      >=
      *
      /
      ^
      AND
      OR
      IF-EXPRESSION
      CALL-FUNCTION
      G2GL-FUNCALL
      FORMAT-FORM
      HAS-VALUE-P
      HAS-NO-VALUE-P
      THE
      NTH-ELEMENT
      NEW
      ASSIGNMENT-STATEMENTS
      DO-STATEMENTS
      VALUES
      CONCLUDE-STATEMENT
      ASSIGNMENT-STATEMENT
      CALL-ASSIGNMENT-STATEMENT
      CURRENT-TIME
      CURRENT-REAL-TIME
      CURRENT-SUBSECOND-TIME
      CURRENT-SUBSECOND-REAL-TIME
      CURRENT-SYSTEM-TIME
      CURRENT-SYSTEM-REAL-TIME
      THIS-G2GL-PROCESS-INSTANCE
      THIS-G2GL-PROCESS))

  (def-binary-tree g2gl-operators
		   :constructor make-g2gl-operators
		   :clearer clear-g2gl-operators
		   :accessor get-from-g2gl-operators
		   :hash-function sxhash-symbol)

  (defvar *g2gl-operators* (make-g2gl-operators))

  (defun fill-g2gl-operators ()
    (loop for op in *all-g2gl-operators*
          for i from 1 do
      (setf (get-from-g2gl-operators op *g2gl-operators*) i)))

  (fill-g2gl-operators)

  (defun-for-macro g2gl-symbol-to-index (key)
    (cond ((member key '(t otherwise)) key)
	  ((symbolp key)
	   (or (get-from-g2gl-operators key *g2gl-operators*)
	       (error "missing key in *g2gl-operators*")))
	  (t key)))

  (defmacro g2gl-symbol-case (symbol-keyform &body clauses)
    (let ((keyform (make-symbol "KEYFORM")))               
      `(let ((,keyform (or (get-from-g2gl-operators ,symbol-keyform *g2gl-operators*)
			   0))) ; just to make compiler happy
	 (declare (type fixnum ,keyform))
	 (fixnum-case ,keyform
	   ,@(loop for clause in clauses
		   for key = (car clause)
		   collect (if (consp key)
			       `(,(mapcar #'g2gl-symbol-to-index key) ,@(cdr clause))
			     `(,(g2gl-symbol-to-index key) ,@(cdr clause))))))))

) ; eval-when

(defun-allowing-unwind g2gl-eval-non-atomic-or-simple (expression thread allow-no-value-p)
  (macrolet ((expr-op (e) `(first-of-cons ,e))
             (expr-op-args (e) `(cdr-of-cons ,e))
             (expr-arg-1 (e) `(second-of-cons ,e))
             (expr-with-1-arg-has-2 (e) `(cddr-of-cons ,e))
             (expr-arg-2 (e) `(third-of-cons ,e))
             (expr-arg-3 (e) `(fourth-of-cons ,e))
             (expr-arg-4 (e) `(fifth-of-cons ,e)))
   (let ((continue-if-fail nil)
         (default-value    nil)
         evaluated-value
         fault-1)
    (catch-g2gl-eval-fault (fault-1)
      ;; note: indents are wrong below:
    (setq evaluated-value
      ;; for table based branch "switch", case -> g2gl-symbol-case
      (g2gl-symbol-case (expr-op expression) ; old: (CASE ...)
        ;; note: indents are wrong below:
      (variable-compilation
       (g2gl-eval-variable (expr-arg-1 expression) thread allow-no-value-p))
      (1+ (g2gl-1+ (g2gl-eval (expr-arg-1 expression) thread)))
      (1- (g2gl-1- (g2gl-eval (expr-arg-1 expression) thread)))
      (not (g2gl-not (g2gl-eval (expr-arg-1 expression) thread)))
      (-
       (if (expr-with-1-arg-has-2 expression)
           (g2gl-- (g2gl-eval (expr-arg-1 expression) thread)
                   (g2gl-eval (expr-arg-2 expression) thread))
           (g2gl-unary-- (g2gl-eval (expr-arg-1 expression) thread))))
      (+ (g2gl-+ (g2gl-eval (expr-arg-1 expression) thread)
                 (g2gl-eval (expr-arg-2 expression) thread)))
      (= (g2gl-= (g2gl-eval (expr-arg-1 expression) thread)
                 (g2gl-eval (expr-arg-2 expression) thread)))
      (/= (g2gl-/= (g2gl-eval (expr-arg-1 expression) thread)
                   (g2gl-eval (expr-arg-2 expression) thread)))
      (< (g2gl-< (g2gl-eval (expr-arg-1 expression) thread)
                 (g2gl-eval (expr-arg-2 expression) thread)))
      (> (g2gl-> (g2gl-eval (expr-arg-1 expression) thread)
                 (g2gl-eval (expr-arg-2 expression) thread)))
      (<= (g2gl-<= (g2gl-eval (expr-arg-1 expression) thread)
                   (g2gl-eval (expr-arg-2 expression) thread)))
      (>= (g2gl->= (g2gl-eval (expr-arg-1 expression) thread)
                   (g2gl-eval (expr-arg-2 expression) thread)))
      (* (g2gl-* (g2gl-eval (expr-arg-1 expression) thread)
                 (g2gl-eval (expr-arg-2 expression) thread)))
      (/ (g2gl-/ (g2gl-eval (expr-arg-1 expression) thread)
                 (g2gl-eval (expr-arg-2 expression) thread)))
      (^ (g2gl-^ (g2gl-eval (expr-arg-1 expression) thread)
                 (g2gl-eval (expr-arg-2 expression) thread)))
      (and (g2gl-and (expr-op-args expression) thread))
      (or (g2gl-or (expr-op-args expression) thread))
      (if-expression (g2gl-if (expr-op-args expression) thread))
      (call-function
        (if (and (eq (expr-arg-1 expression) 'call-function)
                 (eq (expr-arg-2 expression) 'g2gl-evaluate-expression) )
          (progn
            (setq continue-if-fail t)
            (setq default-value (g2gl-eval (expr-arg-4 expression) thread))
            (g2gl-eval (expr-arg-3 expression) thread))
          (g2gl-call-function (expr-op-args expression) thread)))
      (g2gl-funcall (g2gl-funcall (expr-op-args expression) thread))
      (format-form (g2gl-format-form (expr-op-args expression) thread))
      (has-value-p
       (let ((evaluation (g2gl-eval-allowing-no-value (expr-arg-1 expression) thread)))
         (if (eq evaluation g2gl-no-value)
             g2gl-false
             g2gl-true)))
      (has-no-value-p
       (let ((evaluation (g2gl-eval-allowing-no-value (expr-arg-1 expression) thread)))
         (if (eq evaluation g2gl-no-value)
             g2gl-true
             g2gl-false)))
      (the
       (g2gl-get-attribute-value
         (g2gl-eval (expr-arg-2 expression) thread)
         (if (atom (expr-arg-1 expression))
             (expr-arg-1 expression)
           (expr-arg-2 (expr-arg-1 expression)))
         (if (atom (expr-arg-1 expression))
             nil
           (expr-arg-1 (expr-arg-1 expression)))))
      (nth-element
       (let* ((sequence-expression (expr-arg-1 expression))
              (sequence (g2gl-eval sequence-expression thread))
              (index-expression (expr-arg-2 expression))
              (index (g2gl-eval index-expression thread)))
         (if (eq sequence g2gl-no-value)
             (return-from g2gl-eval-non-atomic-or-simple g2gl-no-value))
         (unless (evaluation-sequence-p sequence)
           (g2gl-eval-expression-error
             'invalid-bracketed-index-reference
             (twrite-g2gl-value sequence)
             (twrite " is not a sequence")))
         (unless (fixnump index)
           (g2gl-eval-expression-error
             'invalid-bracketed-index-reference
             (twrite-g2gl-value index)
             (twrite " is not an index")))
         (let ((value (evaluation-sequence-aref sequence index)))
           (if (null value)
               (if allow-no-value-p
                   g2gl-no-value
             (g2gl-eval-expression-error
               'bad-g2gl-sequence-reference
               (tformat "~NV has no value at index ~a" sequence index)))
           (note-temporary-g2gl-value
             (convert-item-or-evaluation-value-to-g2gl-value
                   (copy-if-evaluation-value value)))))))
      (new                                ; for message creation only
       (if (subclassp (expr-arg-1 expression) 'g2gl-message)
           (make-transient-item (expr-arg-1 expression))
           (g2gl-eval-expression-error
             'invalid-creation-type
             (twrite-g2gl-value (expr-arg-1 expression))
             (twrite " is not a G2GL message type"))))
      ((assignment-statements do-statements)
       (let (result)
         (loop for statement in (cdr expression)
               do (setq result (g2gl-eval statement thread)))
         result))
      (values
       (loop for expression in (cdr expression)
             as r = (g2gl-eval expression thread)
             collect (add-reference-to-g2gl-value r)
               using gensym-cons))
      (conclude-statement
       (g2gl-do-conclude (expr-arg-1 expression) (expr-arg-2 expression) thread))
      (assignment-statement
       (g2gl-do-assignment (expr-arg-1 expression) (expr-arg-2 expression) thread))
      (call-assignment-statement
       (g2gl-do-call
         (expr-arg-1 expression)                ; variables
         (expr-arg-2 expression)                ; procedure name
         (expr-arg-3 expression)                ; argument expressions
         thread))
      (current-time
       (-f (clock-get gensym-time) (clock-get gensym-time-at-start)))
      (current-real-time
       (-f (get-real-gensym-time) (clock-get gensym-time-at-start)))
      (current-subsecond-time
       (-e (managed-float-value (clock-get current-g2-time))
           (managed-float-value (clock-get g2-time-at-start))))
      (current-subsecond-real-time
       (-e (gensym-get-unix-time)
           (managed-float-value (clock-get g2-time-at-start))))
      (current-system-time
       (managed-float-value (clock-get current-g2-time)))
      (current-system-real-time
       (gensym-get-unix-time))
      (this-g2gl-process-instance
       (let* ((f (parent-execution-frame thread))
              (handle (g2gl-process-instance-handle f)))
         (unless (cdr handle)
           (instantiate-g2gl-process-instance f))
         (get-item-if-item-reference (cdr handle))))
      (this-g2gl-process
       (source-g2gl-process
         (parent-compilation-version (parent-execution-frame thread))))
      #+development
      ((1000 -1000)
       ;; in development, for now, check to make sure booleans are compiled
       ;; into the unique true/false values, as they should have been:
       (assert-for-development
         (or (not (eq (cdr expression) 'truth-value))
             (eq expression g2gl-true)
             (eq expression g2gl-false))
         "A non-unique truth value was found: ~a"
           expression))
      (t
       (g2gl-eval-expression-error
         'bad-subexpression
         ;; This shouldn't happen, abort?
         (tformat "unrecognized non-atomic subexpression: ~a" expression))))))
     (if fault-1
         (progn (if continue-if-fail default-value (throw g2gl-eval-error fault-1)))
       (values evaluated-value)))))



(defun g2gl-do-call (variables procedure-name arglist-expressions thread)
  (let* ((process-case? nil)
         procedure)
    (cond
      ((null
         (setq procedure
               ;; find a G2 procedure or a G2GL process to call,
               ;; giving precedence to the procedure if it has the
               ;; same name as a process:
               (or (get-instance-with-name-if-any
                     'procedure procedure-name)
                   (setq process-case?
                         (get-instance-with-name-if-any
                           'g2gl-process procedure-name)))))
       (g2gl-eval-expression-error
         'no-procedure
         (tformat "no procedure named ~a" procedure-name)))
      ((and process-case? (this-is-an-abstract-process procedure))
       (g2gl-eval-expression-error
         'process-cannot-be-executed
         (tformat "~a is an abstract G2GL process and cannot be executed"
                  procedure-name)))
      ((and process-case?
            (not (compile-g2gl-process-if-necessary-and-possible procedure)))
       (g2gl-eval-expression-error
         'process-cannot-be-compiled
         (tformat "~NF cannot be executed due to compilation errors."
                  procedure)))
      (t
       (loop for expression in arglist-expressions
	     as new-value = (g2gl-eval expression thread)
	     as arg
		= (if process-case?
		      (add-reference-to-g2gl-value new-value)
		      (copy-g2gl-value-as-item-or-evaluation-value new-value))
	     collect arg into args using gensym-cons
	     finally
	       (return
		 (if process-case?
		     (make-g2gl-to-g2gl-call-invocation
		       procedure args variables thread)
		     (let ((invoc-or-error (make-g2gl-to-g2-call-invocation
					     procedure args variables thread)))
		       (unless (g2gl-call-invocation-p invoc-or-error)
			     (g2gl-eval-expression-error-with-activity-name
			       'procedure-cannot-be-invoked
				   (symbol-name (g2gl-activity-name (activity-compilation-to-execute thread)))
			       (twrite invoc-or-error)
			       (reclaim-text-string invoc-or-error)))
		       invoc-or-error))))))))
			   



;;; The function `copy-g2gl-value-as-item-or-evaluation-value' returns either an
;;; evaluation-value equivalent copy of g2gl-value or an item reference.  If an
;;; item cannot be converted, nil is returned (should not happen).  If
;;; g2gl-value is a gensym float (an unboxed float), it is copied as an
;;; evaluation float (a managed, or boxed", float).
;;;
;;; This is primarily intended to be used for passing arguments to G2
;;; procedures. Such arguments can be either evaluation values or frames.  If
;;; g2gl-value is an item reference, it could be for a deleted frame. In this
;;; case, nil is returned upon dereferencing, with nil assumed to be detected
;;; and handled reasonably, i.e., as a "user" error.  Note that
;;; make-g2gl-to-g2-call-invocation handles the dereferencing of item
;;; references.

(defun copy-g2gl-value-as-item-or-evaluation-value (g2gl-value)
  (cond
    ((managed-float-p g2gl-value)
     (copy-evaluation-float g2gl-value))
    ((gensym-float-p g2gl-value)
     (make-evaluation-float g2gl-value))
    ((wide-string-p g2gl-value)
     (make-evaluation-text g2gl-value))
    ((g2gl-true-p g2gl-value)
     evaluation-true-value)
    ((g2gl-false-p g2gl-value)
     evaluation-false-value)
    ((fixnump g2gl-value)        ; g2gl-small-integer-p?
     (make-evaluation-integer g2gl-value))
    ((evaluation-sequence-p g2gl-value)
     (copy-evaluation-sequence g2gl-value))
    ((evaluation-structure-p g2gl-value)
     (copy-evaluation-structure g2gl-value))
    ((if (evaluation-item-reference-p g2gl-value)
         (evaluation-item-reference-referenced-item g2gl-value)))
    ;; bad item reference (i.e., deleted frame) or unhandled:
    (t g2gl-value)))





;;; The function `make-g2gl-to-g2-call-invocation' schedules a new
;;; procedure-invocation and returns a new g2gl-call-invocation structure, or
;;; returns an error text-string if the procedure-invocation cannot be made.
;;; Either way, the args list will be reclaimed.

(defun make-g2gl-to-g2-call-invocation (procedure args variables thread)
  (let ((nargs (length args))
        (arg-vector? nil)
        (process (source-g2gl-process
                   (parent-compilation-version
                     (parent-execution-frame thread))))
        invoc
        completion-form
        g2-invoc-or-error)
    (when (>f nargs 0)
      (setq arg-vector? (allocate-managed-simple-vector nargs))
      (loop for arg in args
            for i from 0
            do (setf (svref arg-vector? i) (get-item-if-item-reference arg))))
    (setq invoc (make-g2gl-call-invocation-internal))
    (setq completion-form (gensym-list 'finish-g2gl-call invoc))
    (setf (completion-form-for-g2gl-call invoc) completion-form)
    (setf (number-of-g2gl-call-return-values invoc)
          (let ((values-desc (returned-values-description procedure)))
            (if values-desc (halff (length values-desc)) 0)))
    (setf (variables-to-receive-g2gl-call-values invoc) variables)
    (setq g2-invoc-or-error
          ;; `start-procedure-invocation-in-place' checks OK-ness,
          ;; runnability, and argument count
          (with-three-thousand-variables-bound
              (let ((*current-computation-frame* process))
                (start-procedure-invocation-in-place
                  procedure        ; procedure
                  nil                ; priority?
                  nil                ; wait?
                  arg-vector?        ; Local stack
                  (1-f nargs)        ; Top of arguments on stack
                  nargs                ; argument-count
                  nil                ; simulator-procedure?
                  completion-form        ; completion-form?
                  ':error-string        ; top-of-stack?
                  nil                ; validated-args-p
                  'call))))        ; prepare-p
    (when arg-vector?
      (reclaim-managed-simple-vector arg-vector?))
    (reclaim-gensym-list args)
    (cond ((procedure-invocation-p g2-invoc-or-error)
           (setf (g2-procedure-invocation-for-g2gl-call invoc)
                 g2-invoc-or-error)
           (setf (calling-code-body-invocation g2-invoc-or-error) invoc)
           invoc)
          (t
           (reclaim-g2gl-call-invocation invoc)
           g2-invoc-or-error))))



(defun make-g2gl-to-g2gl-call-invocation (procedure args variables thread)
  (let ((invoc (make-g2gl-call-invocation-internal))
        completion-form
        invocation-thread)
    (setq completion-form (gensym-list 'finish-g2gl-call invoc))
    (setf (completion-form-for-g2gl-call invoc) completion-form)

    ;; The following slot gives the number of values _if known_ (G2-procedure
    ;; case), else nil (G2GL-process case):
    (setf (number-of-g2gl-call-return-values invoc) nil)

    (setf (variables-to-receive-g2gl-call-values invoc) variables)
    (setf (g2-procedure-invocation-for-g2gl-call invoc) nil)
    (setq invocation-thread (make-g2gl-process-invocation-thread))
    (setf (process-invocation-context invocation-thread) thread)
    (instantiate-g2gl-process-and-start-execution
      procedure args invocation-thread)
    invoc))



;;; The function `handle-g2gl-call-invocation-error' is called from the stack
;;; evaluator when an error reaches the top level.  This just converts the error
;;; into a g2gl-execution-fault structure and sets the thread state parameter,
;;; reclaiming the error message and error object (if needed).  The thread is
;;; not actually woken up until the invocation is completed and its
;;; completion-form is called (see finish-g2gl-call).

(defun-void handle-g2gl-call-invocation-error (invoc error-message error)
  (setf (execution-thread-state-parameter (thread-parked-on-g2gl-call invoc))
        (make-g2gl-system-fault
          'fault-during-g2-procedure-call
          (tformat "~NW" error-message)))
  (reclaim-error-text error-message)
  (when (and (framep error) (transient-p error))
    (delete-frame error)))


;;; The function `calling-process-of-g2gl-call-invocation' returns the
;;; g2gl-process instance that originated a g2gl-call.

(defun-simple calling-process-of-g2gl-call-invocation (invoc)
  (source-g2gl-process
    (parent-compilation-version
      (parent-execution-frame
        (thread-parked-on-g2gl-call invoc)))))



;;; The function `finish-g2gl-call' manages the completion of a procedure call
;;; via the g2gl-call activity.
;;;
;;; This the protocol for completion of a procedure call, from the spec:
;;;
;;; If and when the invoked procedure completes: (a) any values returned by the
;;; invoked procedure should be stored as the values of any specified G2GL
;;; variables, per invoc; (b) the G2GL execution thread parked in invoc should
;;; be scheduled for execution, with its execution-thread-state-parameter set to
;;; nil; and (c) invoc and the values of various of its slots should be
;;; reclaimed, as appropriate.  If the invoked procedure is abruptly terminated
;;; due to an execution fault or due to some deliberate action that is not a
;;; result of an abnormal deletion of thread: (a) the G2GL execution thread
;;; parked in invoc should be scheduled for execution, with its
;;; execution-thread-state-parameter set to a g2gl-execution-fault structure;
;;; and (b) invoc and the values of various of its slots should be reclaimed, as
;;; appropriate.  (If thread is abnormally deleted, be able to stop the invoked
;;; procedure if possible, reclaiming invoc and various of its slots as
;;; appropriate, or at least keep it from storing values in G2GL variables and
;;; scheduling a thread if and when it does finish.)

;;; IMPORTANT: Note: currently, g2gl-process procedures return through
;;; continue-scheduled-process-invocation, q.v. (MHD 7/27/06)

(defun-allowing-unwind finish-g2gl-call (completion-form)
  (let* ((invoc (second completion-form))
         (g2-invoc (g2-procedure-invocation-for-g2gl-call invoc))
         (thread (thread-parked-on-g2gl-call invoc))
         (variables (variables-to-receive-g2gl-call-values invoc))
         (n-values (number-of-g2gl-call-return-values invoc))
         fault-1)
    (declare (ignore g2-invoc))                ; not used yet!
    (when thread                        ; nec?
      ;; If there was an error in the procedure call, the parameter will have
      ;; already been set to a g2gl-execution-fault structure by
      ;; handle-g2gl-call-invocation-error.
      (unless (g2gl-execution-fault-p (execution-thread-state-parameter thread))
        ;; since this is not necessarily called from
        ;; continue-execution-of-thread, it must establish its own
        ;; catch-g2gl-eval-fault context to catch faults, which could occur as
        ;; a result of doing the variable assignments to the return values:
        (catch-g2gl-eval-fault (fault-1)
          ;; deal with getting values:
          (loop for i from 0 below n-values
                as new-value = (svref global-stack i)
                as place                ; variable or attribute
                   in variables        ;    (message-part) reference
                do (case (and (consp place) (car place))
                     (the
                      (let ((attribute (second place)))
                        (g2gl-set-attribute-value
                          (g2gl-eval (third place) thread)
                          (if (atom attribute) attribute (third attribute))
                          new-value        ; copied in the function as needed
                          (if (atom attribute) nil (second attribute)))))
                     (t
                      (set-value-of-g2gl-variable
                        (if (atom place)
                            ;; place is vc
                            place
                            ;; place is (VARIABLE-COMPILATION vc)
                            (second place))
                        (add-reference-to-g2gl-value new-value)
                        thread))))
          nil)
        (setf (execution-thread-state-parameter thread) fault-1))
      ;; schedule thread to resume:
      (schedule-g2gl-execution-thread thread nil)
      ;; reclaim other stuff, too!!
      (reclaim-g2gl-call-invocation invoc))))






;;;; Calling G2 built-in functions

;;; The code in this section supports calling a G2 built-in function, i.e.,
;;; a function whose name is present in the `*built-in-functions*' parameter
;;; (defined in the EVAL module).  Note that this also supports calling a
;;; user-defined function, using the `call-function' built-in function.  The
;;; entry point for G2GL is the function `call-g2-function-for-g2gl', which
;;; takes a function name, a list of arguments (items and/or evaluation values),
;;; and a frame (for tracing and breakpoints).
;;;
;;; Some built-in functions are actually special forms that do not evaluate all
;;; their arguments.  At present, there are only three: `structure',
;;; `change-attribute', and `remove-attribute'.  It is assumed that these have
;;; been converted to `evaluated-structure', `change-evaluated-attribute', and
;;; `remove-evaluated-attribute', respectively, at the parsing stage.
;;;
;;; It is also assumed that the number of arguments is correct for the given
;;; function.  A function call expression with a wrong number of arguments
;;; should have been rejected at the parsing stage.




;;; The function `item-or-value-type' returns a type description for an item or
;;; evaluation value.

(defun item-or-value-type (item-or-value)
  (if (framep item-or-value)
      (make-class-type-specification (class item-or-value))
      (evaluation-value-type item-or-value)))


;;; The function `express-items-or-values' takes a list of items and/or
;;; evaluation values and returns a corresponding phrase-list of expressions to
;;; represent them.

(defun express-items-or-values (items-or-values)
  (loop for item-or-value in items-or-values
        ;; Conveniently, var-spots are also expressions!
        collect (generate-new-variable-spot
                  (item-or-value-type item-or-value))
          using phrase-cons))


;;; The function `compile-function-call-into-nodes' takes the name of a
;;; built-in function, a list of arguments, and a return type description and
;;; returns a stack-node tree representing the function call.

(defun compile-function-call-into-nodes (name args return-type)
  (let ((arg-exprs
          (case name
            (call-function
             ;; The call-function special form converter requires the first
             ;; argument expression to be a designator, which a var-spot is not.
             ;; So instead of using the var-spot directly, give it a fixed name
             ;; and use the name as a variable.
             (generate-new-variable-spot
               (item-or-value-type (car args)) 'function)
             (phrase-cons 'function (express-items-or-values (cdr args))))
            (t
             (express-items-or-values args)))))
    (compile-stack-expression-into-nodes
      (phrase-cons name arg-exprs) return-type)))


;;; The function `compile-function-call-into-code-body-entry' takes the name of
;;; a built-in function, a list of arguments, and a return type description and
;;; returns a code-body-entry representing the function call.

(defun-allowing-unwind compile-function-call-into-code-body-entry
    (name args return-type)
  (enter-new-code-body nil
    (let ((result-var-spot (generate-new-variable-spot return-type)))
      (emit-instruction
        'assign-local-var result-var-spot
        (compile-function-call-into-nodes name args return-type))

      ;; TO DO: The complete-cell-expression pseudo-instruction seems to be the
      ;; simplest way to get stack-eval to exit, but it still copies the result
      ;; value back onto the stack and then immediately reclaims the copy, which
      ;; is kind of lame.  It might be better to make a new pseudo-instruction
      ;; (and corresponding stack instruction) that just does the exit and
      ;; nothing else.
      (emit-instruction 'complete-cell-expression result-var-spot)

      (current-compiler-code-body))))


;;; The macro `with-compiler-error-collecting' is an alternative to
;;; `with-compiler-error-reporting' that does not add compiler errors and
;;; warnings to frame notes.

(defmacro with-compiler-error-collecting (&body forms)
  `(let ((compiler-errors nil)
         (compiler-warnings nil))
     ,@forms))


;;; The macro `without-compiler-free-reference-collection' inhibits the
;;; recording of free references while executing its body.

(defmacro without-compiler-free-reference-collection (&body forms)
  `(let ((inhibit-free-reference-recording t))
     ,@forms))


;;; The macro `with-simple-compiler-environment-and-phrase-conses' is a simpler
;;; alternative to `with-compiler-environment-and-phrase-conses' for use in
;;; compiling function calls.  It doesn't add compiler errors to frame notes, it
;;; doesn't set up goto tags, and it doesn't record free references.

(defmacro with-simple-compiler-environment-and-phrase-conses (&body forms)
  `(with-phrase-conses
     (with-compiler-error-collecting
       (with-compiler-code-body-entries
         (with-compiler-stack-nodes
           (without-compiler-free-reference-collection
             ,@forms))))))


;;; The function `compile-function-call-for-stack' takes the name of a
;;; built-in function and a list of arguments and returns either a
;;; byte-code-body representing the function call or a gensym list of text
;;; strings if there are compilation errors.

(defun-allowing-unwind compile-function-call-for-stack (name args)
  (with-simple-compiler-environment-and-phrase-conses
    (let ((code-body-entry
            (compile-function-call-into-code-body-entry
              name args
              ;; TO DO: we might actually be able to figure out a stricter
              ;; required-type than this.
              'item-or-datum))
          byte-code-vector byte-codes-count byte-code-constants)
      (if compiler-errors
          ;; TO DO: return or reclaim compiler-warnings!
          (nreverse (copy-list-using-gensym-conses compiler-errors))
          (let ((byte-code-stream (make-byte-code-stream))
                (instructions (nreverse
                                (compiler-code-body-instructions-so-far
                                  (car code-body-entries-in-compilation)))))
            (let ((lexically-visible-code-bodies
                    (generate-list-of-lexically-visible-code-bodies
                      code-body-entry)))
              (emit-byte-code-vector-for-procedure
                byte-code-stream instructions))
            (multiple-value-setq (byte-code-vector byte-codes-count)
              (resolve-procedure-byte-code-addresses byte-code-stream))
            (setq byte-code-constants
                  (make-procedure-byte-code-constants byte-code-stream))
            (reclaim-byte-code-stream byte-code-stream)
            (make-byte-code-body
              byte-codes-count byte-code-vector byte-code-constants
              (convert-description-list-to-managed-array
                (compiler-code-body-environment-description
                  code-body-entry))
              nil))))))


;;; The structure `function-invocation' is a computation instance
;;; representing an invocation of a built-in function.

(def-structure (function-invocation
                 (:include computation-instance)
                 (:constructor make-function-invocation-1
                               (function-invocation-function-name
                                function-invocation-arguments))
                 (:reclaimer reclaim-function-invocation-1))
  function-invocation-function-name
  function-invocation-arguments
  )


;;; The function `make-function-invocation-from-byte-code-body' takes the name
;;; of a built-in function, a list of arguments, and a byte code body produced
;;; by `compile-function-call-for-stack' and returns a new function invocation.

(defun make-function-invocation-from-byte-code-body (name args byte-code-body)
  (let ((invocation (make-function-invocation-1 name args))
        (env (allocate-environment-vector
               (var-count (byte-code-body-environment-description
                            byte-code-body)))))
    ;; The local environment holds the argument values starting from index
    ;; 1.  (Index 0 will receive the return value.)
    (loop for arg in args for i from 1 do (setf (svref env i) arg))
    (setf (invocation-byte-code-body invocation) byte-code-body)
    (setf (invocation-local-var-vector invocation) env)
    (setf (invocation-stack-program-counter invocation) 0)
    (setf (invocation-constant-vector invocation)
          (byte-code-body-constant-vector byte-code-body))
    (setf (invocation-return-value-position invocation) 0)
    (setf (invocation-return-value-count invocation) 1)
    invocation))


;;; The function `reclaim-function-invocation' reclaims a function invocation
;;; along with its byte code body and environment vector.  The values in the
;;; environment vector are not reclaimed.

(defun reclaim-function-invocation (function-invocation)
  (let ((env (invocation-local-var-vector function-invocation)))
    ;; Clear out the environment so the arguments and return value don't get
    ;; reclaimed along with the environment vector.
    (setf (svref env 0) nil)
    (loop for arg in (function-invocation-arguments function-invocation)
          for i from 1 do (setf (svref env i) nil))
    (reclaim-environment-vector env)
    (reclaim-byte-code-body (invocation-byte-code-body function-invocation))
    (reclaim-function-invocation-1 function-invocation)))


;;; The function `make-function-invocation' takes the name of a built-in
;;; function and a list of arguments and creates a function invocation structure
;;; that, when executed, calls the function with the given arguments.  If there
;;; are any errors while compiling the function into byte code, a gensym-list of
;;; error message text strings will be returned instead of a function
;;; invocation.

(defun make-function-invocation (name args)
  (let ((compile-result (compile-function-call-for-stack name args)))
    (if (byte-code-body-p compile-result)
        (make-function-invocation-from-byte-code-body name args compile-result)
        compile-result)))


;;; The function `execute-function-invocation' takes a function invocation and a
;;; frame and executes the function invocation.  The frame is used by the stack
;;; evaluator for tracing and breakpoints.  The return value of the function
;;; invocation is returned.  An error during execution causes a stack error to
;;; be thrown.

(defun-allowing-unwind execute-function-invocation (function-invocation frame)
  (with-three-thousand-variables-bound
    (setq *current-computation-frame* frame)
    (setq current-computation-instance function-invocation)
    (setq current-environment 'procedure)

    ;; Call stack-eval-for-execute-computation-instance instead of plain
    ;; stack-eval because we want to pass stack errors to the caller.  If it
    ;; turns out that we'd rather use the catch handlers that plain stack-eval
    ;; uses, we'll have to modify the functions clean-up-wake-ups-state-if-any
    ;; and signal-error-to-computation-instance to handle function invocations.
    (stack-eval-for-execute-computation-instance
      (invocation-byte-code-body function-invocation)
      (invocation-constant-vector function-invocation)
      (invocation-local-var-vector function-invocation)
      (get-fixnum-time) nil 0)
    (svref (invocation-local-var-vector function-invocation)
           (invocation-return-value-position function-invocation))))


;;; The function `call-g2-function-for-g2gl' takes the name of a built-in
;;; function, a list of arguments, and a frame.  The function is invoked with
;;; the given arguments.  The frame is used by the stack evaluator for tracing
;;; and breakpoints.  Two values are returned: the result of the function call
;;; (an evaluation value) and a fresh gensym-list of error message text strings
;;; (if any).

(defun-allowing-unwind call-g2-function-for-g2gl (name args frame)
  (let ((invoc (make-function-invocation name args)))
    (if (not (function-invocation-p invoc))
        ;; There were compiler errors, so just return them.
        (values nil invoc)
        (with-catch-handlers
            (((:stack-error) (top-of-stack error error-msg
                                           suppress-debugging-info?)
              (declare (ignore top-of-stack error suppress-debugging-info?))
              (values nil (gensym-list (error-text-string error-msg)))))
          (unwind-protect (values (execute-function-invocation invoc frame) nil)
            (reclaim-function-invocation invoc))))))








;;;; Disowning Compilations Versions





;;; Disown-current-compilation-version-if-any (G2GL-process s):
;;;
;;; This can be invoked at any time.

(defun disown-current-compilation-version-if-any (s)
  (cond
    ((null (stack-of-compilation-versions s))
     nil)
    (t
     (setf (latest-existing-compilation-version-was-disowned s) t)
     (delete-unowned-compilation-version-if-possible
       (first (stack-of-compilation-versions s))))))





;;;; G2GL/BPEL Execution





;;; Instantiate-G2GL-process-and-start-execution (G2GL-process s, args args,
;;; G2GL-process-invocation-thread invocation-thread):
;;;
;;; This can be used to invoke s as a procedure; in this case, the
;;; callable-as-a-procedure attribute of s should be true, and invocation-thread
;;; should be non-nil.
;;;
;;; This assumes that there is a current compilation version of s.
;;;
;;; The individual args should already have been copied or had their reference
;;; counts incremented where appropriate; args and its elements are always
;;; reclaimed.
;;;
;;; Invocation-thread can be nil, e.g., as in the case of launching a top-level
;;; process from a menu command.  If invocation-thread is non-nil, it is parked
;;; in the new execution frame and will be scheduled for execution when the
;;; process instance terminates, however that happens.
;;;
;;; Unless an execution fault has been signaled, this starts and could possibly
;;; complete execution of the process instance and also, if invocation-thread is
;;; non-nil, parks invocation-thread in the new execution frame and will
;;; schedule it for execution when the process instance terminates, however that
;;; happens.
;;;
;;; Note that this should only be invoked as the last thing to be done before
;;; exiting back to the G2 scheduler.

;;; The variable `create-process-instance-for-current-process-p' is an implicit
;;; parameter .... bound to nil globally, bound to t by g2-execute-g2gl-process.

(defvar create-process-instance-for-current-process-p nil)
(defvar process-instance-created-for-current-process? nil)

(defun instantiate-g2gl-process-and-start-execution (s args invocation-thread)
  (let* ((thread-unless-fault
           (instantiate-g2gl-process s args invocation-thread)))
    (when thread-unless-fault
      (let ((f (parent-execution-frame thread-unless-fault)))
        (cond
          (create-process-instance-for-current-process-p
           (instantiate-g2gl-process-instance f)
           (setq process-instance-created-for-current-process?
                 (copy-evaluation-item-reference
                   (cdr (g2gl-process-instance-handle f))))
           ;; we schedule always in this case, since continue-... has a chance
           ;; to finish and kill the process before we've returned the instance.
           ;; (MHD 11/21/05)
           (schedule-g2gl-execution-thread thread-unless-fault nil))
          (t
           (continue-execution-of-thread thread-unless-fault)))))))


(defun instantiate-g2gl-process-instance (f)
  (let* ((handle (g2gl-process-instance-handle f))
         (instance (make-transient-item 'g2gl-process-instance)) ; c.f. make-procedure-invocation-frame
         (item-reference (get-reference-to-item instance)))
    (setf (g2gl-process-instance-execution-frame instance) f)
    (setf (cdr handle) item-reference)))



;;; Instantiate-G2GL-process (G2GL-process s, args args,
;;; G2GL-process-invocation-thread invocation-thread):
;;;
;;; This assumes that there is a current compilation version of s.
;;;
;;; This returns an execution thread located at the flowchart entry activity of
;;; the process body compilation for s, ready to start execution, unless an
;;; execution fault has been signaled, in which case it returns nil.
;;;
;;; The individual args should already have been copied or had their reference
;;; counts incremented where appropriate; args and its elements are always
;;; reclaimed.
;;;
;;; If invocation-thread is non-nil, it is parked in the new execution frame and
;;; will be scheduled for execution when the process instance terminates,
;;; however that happens.

;;; Note that this should only be invoked as the last thing to be done before
;;; exiting back to the G2 scheduler.

(defun instantiate-g2gl-process (s args invocation-thread)
  (let* ((v (first (stack-of-compilation-versions s)))
         (f (make-g2gl-execution-frame v)))
    (when invocation-thread
      (setf (parked-process-invocation-thread f) invocation-thread)
      (setf (process-invocation-frame invocation-thread) f))
    (instantiate-g2gl-body-compilation (G2GL-body-compilation v) args nil f)))



;;; Instantiate-G2GL-body-compilation-and-start-execution (body-compilation b,
;;; args args, parent-execution-thread parent-thread, execution-frame f):
;;;
;;; Args may be non-nil for a top-level body compilation or for a G2GL fault
;;; handler compilation.
;;;
;;; Unless an execution fault has been signaled, this starts and could possibly
;;; complete execution of the process instance.
;;;
;;; See other notes in the function instantiate-G2GL-process.

(defun instantiate-g2gl-body-compilation-and-start-execution
    (b args parent-thread f)
  (let ((thread-unless-fault
          (instantiate-g2gl-body-compilation b args parent-thread f)))
    (when thread-unless-fault
      (continue-execution-of-thread thread-unless-fault))))



;;; Instantiate-G2GL-body-compilation (body-compilation b, args args,
;;; parent-execution-thread parent-thread, execution-frame f):
;;;
;;; Args may be non-nil for a top-level body compilation or for a G2GL fault
;;; handler compilation.
;;;
;;; This returns an execution thread located at the flowchart entry activity of
;;; the body compilation of b, ready to start execution, unless an execution
;;; fault has been signaled, in which case it returns nil..
;;;
;;; See other notes in the function instantiate-G2GL-process.

(defun-allowing-unwind instantiate-g2gl-body-compilation (b args parent-thread f)
  (let* ((c (flowchart-entry-activity-compilation b)) ; should always exist
         (thread (make-g2gl-execution-thread c nil nil parent-thread nil b f))
         (event-handler-compilations (g2gl-event-handler-compilations b))
         fault-1 result)
    (loop for ehc in event-handler-compilations
          as sibling-thread
             = (make-g2gl-execution-thread
                 ehc nil nil parent-thread thread b f)
          do (schedule-g2gl-execution-thread sibling-thread nil))
    (catch-g2gl-eval-fault (fault-1)
       (setq
         result
         (loop with remaining-args = args
               with initial-value
               with process-name
               for vc in (g2gl-variable-compilations b)
               ;; Note: the following two-pass sweep over variable compilations
               ;; is intended to have errors pertaining to argument processing
               ;; have priority over errors pertaining to local-variable
               ;; processing. The steps are: (1) initialize argument variables,
               ;; either from the arglist or from the default-value slot; (2)
               ;; check for leftover, unused arguments (an error); (3)
               ;; initialize local variables per default-value slot. This is not
               ;; in synch with the spec, but will be, per LH, in the near
               ;; future. (MHD 6/16/05)
               when (=f (g2gl-variable-class-code vc)
                        (quoted-g2gl-variable-class-code g2gl-arg-variable))
                 do (cond
                      (remaining-args
                       (setq initial-value (pop remaining-args)))
                      ((setq initial-value (c-default-value-for-g2gl-variable vc))
                       (setq initial-value
                             (add-reference-to-g2gl-value initial-value)))
                      (t
                       (signal-g2gl-system-fault
                         thread 'missing-argument
                         (twrite (c-g2gl-variable-name vc)))
                       (return nil)))
                    (set-value-of-g2gl-variable vc initial-value thread)
               finally
                 (cond
                   ((and remaining-args
                         (or (null parent-thread)
                             (not (=f (g2gl-activity-class-code
                                        (activity-compilation-to-execute
                                          parent-thread))
                                      (quoted-g2gl-activity-class-code
                                        g2gl-fault-handler)))))
                    (setq process-name
                          (get-primary-name-for-frame-if-any
                            (source-g2gl-process (parent-compilation-version f))))
                    (signal-g2gl-system-fault
                      thread 'process-invoked-with-too-many-arguments
                      (twrite process-name))
                    (return nil))
                   (t
                    (loop for vc in (g2gl-variable-compilations b)
                          when (=f (g2gl-variable-class-code vc)
                                   (quoted-g2gl-variable-class-code
                                     g2gl-local-variable))
                            do (cond
                                 ((setq initial-value
                                        (c-default-value-for-g2gl-variable vc))
                                  (setq initial-value
                                        (add-reference-to-g2gl-value initial-value)))
                                 (t
                                  (setq initial-value nil)))
                               (set-value-of-g2gl-variable vc initial-value thread))
                    (return thread)))))
       nil)
    (reclaim-gensym-list args)
    (cond
      (fault-1
       (signal-g2gl-execution-fault thread fault-1)
       nil)
      (t result))))


(defparameter time-to-spend-executing-G2-BPEL-process-before-suspending
  50)                                        ; in milliseconds



;;; The function `continue-execution-of-thread' ...
;;;
;;; Arg:
;;;
;;;  thread, an execution-thread
;;;
;;; When this is invoked by the G2 scheduler, it is assumed that thread has
;;; already been removed from the G2 schedule.
;;;
;;; In the spec, where reference is made to the action "exit", it corresponds to
;;; an a exit from this continuation function, i.e., a return from this
;;; function, or, more precisely, from the main loop of this function with no
;;; values.  The macro `exit-g2gl-process' does this exit via its expansion to
;;;
;;;  (return-from continue-execution-of-thread (values))
;;;
;;; G2GL activities' execution code (see def-g2gl-activity) can use this the
;;; exit-thread-continuation macro.

(defmacro exit-g2gl-process ()
  `(return-from continue-execution-of-thread (values)))


;;; The constant `g2gl-execution-iterations-between-time-slice-checks' is used
;;; to limit the amount of time slice checking in continue-execution-of-thread.
;;; This is a tuning parameter, and it's fine to experiment with different
;;; values, but it's a constant for maximum inline efficiency.  The value is
;;; 1000.

(defconstant g2gl-execution-iterations-between-time-slice-checks 1000)


(defun-allowing-unwind continue-execution-of-thread (thread-to-continue)
  ;; NOTE: since G2's scheduler (as, I think, with most cooperative
  ;; schedulers) requires microtasks to yield to the scheduler when the
  ;; scheduler-determined time slice is expired, and cannot allow microtasks
  ;; to decide on their own how much time to take, it works best
  ;; practically, especially in terms of ease of integration with G2, to
  ;; deviate from the spec here and just use G2 scheduler's facilities for
  ;; determining time-slice timeouts, etc., i.e., to use
  ;; time-slice-expired-p.  LH agrees with this. (MHD 12/3/04)
 (with-temporary-gensym-float-creation
    continue-execution-of-thread
   (let* ((thread thread-to-continue)        ; see note! (MHD 3/2/05)
          coordinate-pairs
          parameter
          individual-display
          mode
          fault-1
          expression-value
          c-successors

          (timeout
            (+e (g2gl-get-current-time)
                (slot-value-number-value
                  (time-slice-for-execution-of-thread
                    g2gl-parameters))))
          (f (parent-execution-frame thread))
          (parent-thread
            (cond
              ((process-instance-is-paused f)
               (setf (threads-ready-to-run-after-pause f)
                     (nconc (threads-ready-to-run-after-pause f)
                            (gensym-list thread)))
               (exit-g2gl-process))
              (t
               (parent-execution-thread thread))))
          (execution-displays (g2gl-execution-displays thread))
          (c (activity-compilation-to-execute thread)))
    (when (eq (execution-thread-state thread) 'in-transit)
      ;; -- note that execution-displays must be non-nil in this case
      (remove-thread-tokens-from-execution-displays thread)
      (setq coordinate-pairs (execution-thread-state-parameter thread))
      (move-thread-tokens
        thread
        (car (first coordinate-pairs))
        (cdr (first coordinate-pairs)))
      (add-thread-tokens-to-execution-displays thread)
      (reclaim-gensym-cons
        ;; This call to reclaim the coordinate-pair cons is new - fixes leak -
        ;; BUG IN SPEC; REVISE SPEC! (MHD 10/17/05)
        (gensym-pop (execution-thread-state-parameter thread)))
      (setq parameter (execution-thread-state-parameter thread))
      (cond
        ((null parameter)
         (setf (execution-thread-state thread) nil)
         (schedule-g2gl-execution-thread thread nil)
         (exit-g2gl-process))
        ((not (symbolp (first parameter)))
         ;; -- i.e., there's at least one more coordinate pair remaining
         (schedule-g2gl-execution-thread thread nil)
         (exit-g2gl-process))
        (t
         (setf (execution-thread-state thread) (first parameter))
         ;; -- POSITIVE or NEGATIVE
         (setf (execution-thread-state-parameter thread) (second parameter))
         (reclaim-gensym-list parameter)
         (exit-g2gl-process))))


    (when (eq (execution-thread-state thread) 'at-end)
      ;; -- we're waiting for other threads to terminate (at the end of
      ;; executing a body) -- are there threads other than thread for this body?
      (loop for th in (g2gl-execution-threads f)
            when (and (not (eq th thread))
                      (eq (body-compilation-this-is-being-used-to-execute th)
                          (body-compilation-this-is-being-used-to-execute thread))
                      ;; Don't wait for idle event handlers.
                      (not (thread-is-idle-event-handler-p th)))
              do (schedule-g2gl-execution-thread thread nil)
                 (exit-g2gl-process)))

    ;; the following is the loop step:
    (catch-g2gl-eval-fault (fault-1)
       ;; -- nonstandard formatting here --
    (loop with count fixnum = 0 do
      (cond
        ((>f count g2gl-execution-iterations-between-time-slice-checks)
         (setq count 0)                        ; reset count
         (when (>=e (g2gl-get-current-time) timeout)
           (schedule-g2gl-execution-thread thread nil)
           (exit-g2gl-process)))
        (t (incff count)))                ; else increment count

      (when (and execution-displays
                 (not (eq (execution-display-mode (first execution-displays))
                          'superimposed-tracings)))
        (setq individual-display (first execution-displays))
        (setq mode (execution-display-mode individual-display))
        (when (and (or (null (execution-thread-state thread))
                       (eq (execution-thread-state thread) 'abnormal))
                   (or (eq mode 'single-step)
                       (memq c (temporary-breakpoints-for-execution-display
                                 individual-display)))
                   (not
                     ;; c has a body compilation?
                     (subclassp
                       (map-g2gl-activity-code-to-class
                         (g2gl-activity-class-code c))
                       'g2gl-activity-with-body)))
          (effect-g2gl-breakpoint
            thread
            (tformat-text-string
              (case mode
                (single-step "single-step breakpoint")
                (t "specifically set temporary breakpoint")))
            nil)
          (exit-g2gl-process)))
      (when (eq (execution-thread-state thread) 'at-breakpoint)
        (setq parameter (execution-thread-state-parameter thread))
        (cond
          ((not (eq (first parameter) 'ready-to-proceed))
           ;; -- and thus is a G2GL breakpoint button, which can only happen
           ;; when c is an entry activity compilation
           (exit-g2gl-process))
          ((cdr parameter)                ; parameter has more than one element
           ;; -- that is, we are ready to proceeed from an execution fault
           ;; breakpoint
           (let ((fault (second parameter)))
             (reclaim-gensym-list parameter)
             (setf (execution-thread-state-parameter thread) nil)
             (handle-g2gl-execution-fault-after-any-breakpoint thread fault)
             (exit-g2gl-process)))
          ((not (=f (g2gl-activity-class-code c)
                    (quoted-g2gl-activity-class-code g2gl-break)))
           (reclaim-gensym-list parameter)
           (setf (execution-thread-state-parameter thread) nil)
           (setf (execution-thread-state thread) nil))))
      (setq expression-value nil)
      (when (and (g2gl-expression-compilation c)
                 ;; The following test is needed to prevent an improper second
                 ;; evaluation for a final activity (with no successors) on a
                 ;; flow chart where the execution-thread-state of thread is
                 ;; AT-END, for a pick activity compilation where the
                 ;; execution-thread-state of thread is IN-PARTNER-LINK, for a
                 ;; wait activity compilation where the execution-thread-state
                 ;; of thread is WAITING, or for a call activity compilation
                 ;; where the execution-thread-state of thread is IN-PROCEDURE.
                 (null (execution-thread-state thread)))
        ;; note: spec doesn't handle the IN-EXPRESSION case yet!
        (setq expression-value
              (evaluate-g2gl-expression
                (g2gl-expression-compilation c) thread)))
      (setq c-successors (activity-compilation-successors c))
      (cond ((eq (execution-thread-state thread) 'at-end)
             (setf (execution-thread-state thread) nil))
            (t
             (AGGREGATE-G2GL-ACTIVITY-EXECUTION-CODE)))
      (cond
        ((or (null c-successors) (null (first c-successors)))
         (when (and (or (null (execution-thread-state thread))
                        (eq (execution-thread-state thread) 'at-end))
                    ;; are there threads other than thread for this body?
                    (loop for th in (g2gl-execution-threads f)
                          thereis
                          (and (not (eq th thread))
                               (eq (body-compilation-this-is-being-used-to-execute th)
                                   (body-compilation-this-is-being-used-to-execute thread))
                               ;; Don't wait for idle event handlers.
                               (not (thread-is-idle-event-handler-p th)))))
           ;; -- if there are still threads running "back there", presumably in
           ;; a scope we've just finished, then schedule this to run again, so
           ;; we keep waiting for those threads to finish. (MHD 11/2/05)
           (setf (execution-thread-state thread) 'at-end)
           (schedule-g2gl-execution-thread thread nil)
           (exit-g2gl-process))
         (loop for thread-state = (execution-thread-state thread)
               as has-surviving-sibling-thread
                  = (delete-g2gl-execution-thread thread nil t)
               when has-surviving-sibling-thread
                 do (exit-g2gl-process)
               when (null parent-thread)
                 do (when (or (null
                                (normal-completion-of-process-body-compilation
                                  f))
                              (eq thread-state 'abnormal))
                      (exit-g2gl-process-instance f nil))
                    (exit-g2gl-process)
               while (eq (execution-thread-state parent-thread) 'abnormal) do
           (setq thread parent-thread)
           (setq parent-thread (parent-execution-thread thread))
           (unless (=f (g2gl-activity-class-code
                         (activity-compilation-to-execute thread))
                       (quoted-g2gl-activity-class-code g2gl-fault-handler))
             ;; We just finished doing some compensation, but we might have
             ;; more work to do (indicated by the thread state parameter).
             (let ((parameter (execution-thread-state-parameter thread)))
               (cond
                 ((g2gl-execution-fault-p parameter)
                  ;; The thread was doing implicit fault handling, so continue
                  ;; that.
                  (setf (execution-thread-state-parameter thread) nil)
                  (unless (schedule-g2gl-compensation-if-necessary
                            thread nil nil parameter f)
                    ;; No more compensation to be done, so re-throw the original
                    ;; fault to the parent thread (or exit the process instance
                    ;; if we're at the top level).
                    (if parent-thread
                        (handle-g2gl-execution-fault-after-any-breakpoint
                          parent-thread parameter)
                        (exit-g2gl-process-instance-with-fault f parameter))
                    (exit-g2gl-process)))
                 ((eq parameter 'implicit-compensation-handler)
                  ;; The thread was doing implicit compensation handling, so
                  ;; continue that by compensating the next normal completion
                  ;; (if any).
                  (schedule-g2gl-compensation-if-necessary
                    thread nil nil nil f))
                 (parameter
                  ;; We got here from an explicit compensate activity, so wake
                  ;; up its thread so it can continue.
                  (schedule-g2gl-execution-thread parameter nil))
                 (t
                  ;; The thread was running an explicit compensation handler in
                  ;; a body, so just die and go to the parent thread (whose
                  ;; state parameter will be non-nil).
                  nil)))))
         (setq thread parent-thread)
         (setq parent-thread (parent-execution-thread thread))
         (setq execution-displays (g2gl-execution-displays thread))
         (setq c (activity-compilation-to-execute thread))
         (when t
           ;;  -- if [we are in danger of overflowing the function execution
           ;;  stack because we go one level recursively deeper in this function
           ;;  each time we execute a body compilation within a G2GL loop]
           ;;  [handle this situation more efficiently!], then exit after
           ;;  invoking schedule-G2GL-execution-thread with thread and nil, For
           ;;  now, we have the condition be true.  Later, we could optimize it,
           ;;  say by detecting if more than half the stack capacity has been
           ;;  used (where the lisp supports such a test) or by somehow
           ;;  detecting that we're executing in a while loop (or future variant
           ;;  thereof) or by having the nth test during a time slice be true.
           (schedule-g2gl-execution-thread thread nil)
           (exit-g2gl-process)))
        (t
         (when execution-displays
           (setf (predecessor-activity-compilation thread) c)
           (setf (activity-compilation-to-execute thread)
                 (first c-successors))
           (remove-thread-tokens-from-execution-displays thread)
           (set-up-transition-from-predecessor-activity-compilation
             thread c nil)
           (add-thread-tokens-to-execution-displays thread)
           (schedule-g2gl-execution-thread thread nil)
           (exit-g2gl-process))
         (setf (predecessor-activity-compilation thread) c)
         (setq c (first c-successors))
         (setf (activity-compilation-to-execute thread) c)))))
    ;; -- end nonstandard formatting from above --
    (when fault-1
      (signal-g2gl-execution-fault thread fault-1)))))

;; Previously, the arg was named thread, and it was subject to being setq'ed.
;; We've changed the arg to a different name, i.e., thread-to-continue, and we
;; no longer setq it. The reason is that this keeps the arg variable from being
;; declared volatile.  This works around a bug in Chestnut and/or the Alpha OSF
;; C compiler, such that the volatile variable, which doesn't completely agree
;; the generated C prototype, causes this compiler error:
;;
;; cc: Error: /bt/8build/g2/c/g2bpl.c, line 16776: In the definition of
;;       the function "continue_execution_of_thread", the promoted type of thread is
;;       incompatible with the type of the corresponding parameter in a prior
;;       declaration. (promotmatch);;
;;     volatile Object thread;

;;
;; (MHD 3/2/05)





;;; Resume-paused-process-instance (execution-frame f):

(defun resume-paused-process-instance (f)
  (loop for thread in (threads-ready-to-run-after-pause f)
        do (schedule-g2gl-execution-thread thread nil))
  (reclaim-gensym-list (threads-ready-to-run-after-pause f))
  (setf (threads-ready-to-run-after-pause f) nil)
  (setf (process-instance-is-paused f) nil))



;;; Get-value-of-G2GL-variable (G2GL-variable-compilation vc, execution-frame
;;; f):

(defun get-value-of-g2gl-variable (vc f)
  (managed-svref (g2gl-variable-values-vector f) (g2gl-variable-index vc)))

;; This needs to copy values of certain types and to increment the reference
;; counts of values of other types - so that values can be automatically
;; reclaimed at the proper time, if appropriate!]  [Consider implementing this
;; as a macro.







;;; The macro `stucturally-valid-g2gl-correlation-p' decides thing is a G2GL
;;; correlation if it is a list consisting of of one or more symbols, none of
;;; which are the symbol nil.

(defun-substitution-macro stucturally-valid-g2gl-correlation-p (thing)
  (and (consp thing)
       (loop with car
             for l = thing then (cdr-of-cons l)
             while l
             always (and (consp l)
                         (setq car (car-of-cons l))
                         (symbolp car)))))






;;; The macro `check-g2gl-variable-value-type-for-assignment' checks new-value,
;;; which must be either nil or a valid G2GL value, to see if it is of the type
;;; specified for vc, a G2GL variable compilation.  If new-value nil, this does
;;; nothing, since new-value is used in this case to initialize a variable or to
;;; make it be "unbound".  Otherwise, if the value type does not match the
;;; variable type, this calls g2gl-eval-expression-error, which throws to the
;;; innermost (Lisp) CATCH established by catch-g2gl-eval-fault, passing it
;;; relevant the fault name INVALID-VALUE-TYPE-FOR-VARIABLE-ASSIGNMENT and
;;; associated fault data.

(def-substitution-macro check-type-for-g2gl-variable-assignment (vc new-value)
  (when new-value
    (cond
      ((=f (g2gl-variable-class-code vc)
           (quoted-g2gl-variable-class-code g2gl-partner-link-variable))
       (unless (g2gl-service-port-p new-value)
         (g2gl-eval-expression-error
           'invalid-value-type-for-variable-assignment
           (twrite-g2gl-value new-value)
           (tformat " cannot be assigned to variable ~a"
                    (get-name-for-g2gl-variable vc)))))
      ((=f (g2gl-variable-class-code vc)
           (quoted-g2gl-variable-class-code g2gl-correlation-variable))
       (unless (stucturally-valid-g2gl-correlation-p new-value)
         (g2gl-eval-expression-error
           'invalid-value-type-for-variable-assignment
           (twrite-g2gl-value new-value)
           (tformat " cannot be assigned to variable ~a"
                    (get-name-for-g2gl-variable vc)))))
      (t                                       ; local- or arg-variable case
       (let* ((type (c-g2gl-variable-type vc)))
         (unless
             (case type
               (general t)
               (integer (fixnump new-value))
               (float (managed-float-p new-value))
               (truth-value
                (or (g2gl-true-p new-value) (g2gl-false-p new-value)))
               (text (wide-string-p new-value))
               (symbol (symbolp new-value))
               (sequence (evaluation-sequence-p new-value))
               (structure (evaluation-structure-p new-value))
               (t
                (cond
                  ((and (consp type) (eq (car-of-cons type) 'class))
                   (and (evaluation-item-reference-p new-value)
                        (let ((frame?
                                (evaluation-item-reference-referenced-item
                                  new-value)))
                          (and frame? (frame-of-class-p frame? (cadr type))))))
                  ((and (consp type) (eq (car-of-cons type) 'xml-type))
                   ;; to do: check XML-TYPE case better!
                   t)
                  #+development
                  (t
                   (cerror "continue anyhow"
                           "Unrecognized local- or arg-variable type: ~s"
                           type)
                   t))))
           (g2gl-eval-expression-error
             'invalid-value-type-for-variable-assignment
             (twrite-g2gl-value new-value)
             (tformat " cannot be assigned to variable ~a"
                      (get-name-for-g2gl-variable vc)))))))))




;;; Set-value-of-G2GL-variable (G2GL-variable-compilation vc, value value,
;;; execution-thread thread):
;;;
;;; Value should already have been copied or had its reference count
;;; incremented, as appropriate.
;;;
;;; This function must be called in a catch-g2gl-eval-fault environment, since
;;; it, or subfunctions it may use, may create faults and exit non-locally via
;;; g2gl-eval-expression-error.

(defun set-value-of-g2gl-variable (vc new-value thread)
  (when (and (fixnump new-value)
             (eq (c-g2gl-variable-type vc) 'float))
    ;; Allow an integer to be assigned to a float attribute by first converting
    ;; it to a float.  See HQ-5113106 "G2GL: can't store an integer in a float
    ;; variable or attribute".  -dougo, 11/7/05
    (setq new-value (allocate-managed-float
                      (coerce-fixnum-to-gensym-float new-value))))
  (check-type-for-g2gl-variable-assignment vc new-value)
  (let* ((vvv (g2gl-variable-values-vector (parent-execution-frame thread)))
         (i (g2gl-variable-index vc))
         (old-value (managed-svref vvv i)))
    (declare (type fixnum i))
    (setf (managed-svref vvv i) new-value)
    (when old-value
      (remove-reference-to-g2gl-value old-value))
    (unless (eq old-value new-value)        ; opt. - for symbols & fixnums
      (update-g2gl-variable-value-display vc thread))))



;;; The function `add-reference-to-g2gl-value' is to be called with a value that is
;;; about to be stored in a G2GL variable.  It copies and/or increments
;;; reference counts for value as appropriate, and returns the value that may be
;;; passed to set-value-of-g2gl-variable, suitable for storing in a variable.
;;; Such a call should generally be matched with a corresponding call to the
;;; function `remove-reference-to-g2gl-value', which reclaims and/or decrements
;;; reference counts for value as appropriate.

;;; How this handles frames: the add function turns a frame into either (a) a
;;; new item reference with its reference count = 1 or (b) an existing item
;;; reference, potentially shared with data structures used anywhere else in G2,
;;; with its reference count incremented by 1.  The remove function, when given
;;; an item reference, decrements its reference count, and, if it's decremented
;;; to zero, reclaims the item reference.

(defun add-reference-to-g2gl-value (value)
  (cond
    ((null value) nil)
    ((or (symbolp value) (fixnump value)) value)
    ((managed-float-p value) (copy-managed-float value))
    ((gensym-float-p value) (allocate-managed-float value))
    ((wide-string-p value) (copy-wide-string value))
    ((equal value evaluation-true-value) g2gl-true)
    ((equal value evaluation-false-value) g2gl-false)
    ((evaluation-sequence-p value)
     (copy-evaluation-sequence value))
    ((evaluation-structure-p value)
     (copy-evaluation-structure value))
    ((framep value)
     (get-reference-to-item value))
    ((evaluation-item-reference-p value)
     (copy-evaluation-item-reference value))
    ;; other cases go to nil
    (t nil)))

(defun remove-reference-to-g2gl-value (value)
  (cond
    ((managed-float-p value) (reclaim-managed-float value))
    ((wide-string-p value) (reclaim-wide-string value))
    ((evaluation-sequence-p value)
     (reclaim-evaluation-sequence value))
    ((evaluation-structure-p value)
     (reclaim-evaluation-structure value))
    ((evaluation-item-reference-p value)
     (reclaim-evaluation-item-reference value))))



;;; Reclaim-G2GL-variable-managed-value (G2GL-managed-value value,
;;; G2GL-variable-compilation vc):

(defun reclaim-g2gl-variable-managed-value (value vc)
  (cond
    ((=f (g2gl-variable-class-code vc)
         (quoted-g2gl-variable-class-code g2gl-partner-link-variable))
     ;; value is a g2gl-service-port structure
     (let* ((sp value)
            (partner-sp (partner-service-port sp)))
       (cond
         ((null (service-port-owner partner-sp))
          ;; -- i.e., if partner-sp is disconnected
          (reclaim-g2gl-service-port sp)
          (reclaim-g2gl-service-port partner-sp))
         ((direct-connection-partner-link-variable-compilation partner-sp)
          ;; i.e., if partner-sp is directly connected
          (setf (service-port-owner sp) nil)
          (setf (direct-connection-partner-link-variable-compilation sp) nil)
          ;; If threads are waiting at partner-sp, schedule them so they can
          ;; signal a partner-has-terminated fault.  This is not in the spec,
          ;; but is needed to fix HQ-5329754 "G2GL: second invocation of same
          ;; process from one requester process blocked".  See also the related
          ;; comment in look-for-g2gl-message-transmission below.
          ;; -dougo, 9/12/06
          (loop for partner-thread
                    in (threads-located-at-receiving-activity-compilations
                         partner-sp)
                do (schedule-G2GL-execution-thread partner-thread nil)))
         (t
          (loop for pair in (continuations-waiting-for-reply partner-sp)
                do (when (cdr pair)
                     (return-value-to-code-body-continuation
                       ;; TO DO: make an error object?
                       (allocate-evaluation-structure-inline
                         'error-text
                         (make-evaluation-text "Partner has terminated."))
                       (cdr pair)))
                   (reclaim-gensym-cons pair))
          (reclaim-gensym-list (continuations-waiting-for-reply partner-sp))
          ;; TO DO: remove partner-sp from its owner (a service switch)
          (reclaim-g2gl-service-port sp)
          (reclaim-g2gl-service-port partner-sp))
         )))
    (t
     (remove-reference-to-g2gl-value value))))

;; Partner links variables: once assigned, cannot be reassigned, except via
;; unbinding/unwinding.  Also, in G2GL, these are allowed to be at any level,
;; contra BPEL. We might want to think about removing warning.  For G2 8.1r0,
;; we've decided definitely to allow but have a warning.  But the warning is
;; kind of a pain, so we may want to even get rid of that.
;;
;; (MHD 5/2/05)






;;; Signal-G2GL-execution-fault
;;;   (execution-thread thread, g2gl-execution-fault fault):

(defun signal-g2gl-execution-fault (thread fault)
  (cond
    ((or (break-on-execution-fault
           (source-G2GL-process
             (parent-compilation-version
               (parent-execution-frame thread))))
         (break-on-all-execution-faults
           g2gl-parameters))
     (make-and-put-up-individual-execution-display-if-necessary thread)
     (effect-g2gl-breakpoint
       thread
       (twith-output-to-text-string
         (tformat "breakpoint on ~a execution fault"
                  (g2gl-execution-fault-name fault))
         (when (g2gl-execution-fault-description fault)
           (tformat ": ~a" (g2gl-execution-fault-description fault))))
       fault))
    (t
     (handle-g2gl-execution-fault-after-any-breakpoint thread fault))))



;;; The function `twrite-g2gl-value' can be used to (safely) twrite any G2GL
;;; value, including a g2gl-service-port, which can be the value of a partner
;;; link variable, and NIL, which can be the value of an uninitialized variable.

(defun twrite-g2gl-value (value)
  (if (evaluation-item-reference-p value)
      (let ((frame? (evaluation-item-reference-referenced-item value)))
        (tformat (if frame? "~NF" "(a deleted item)") frame?))
      (tformat
        (cond ((or (not value) (framep value) (evaluation-value-p value))
               "~NA")
              ((g2gl-service-port-p value)
               "(a partner link)") ; expand description; review!
              (t
               ;; Currently the only thing that could get here is a gensym
               ;; float, but we might as well be general.  -dougo, 2/9/07
               "~a"))
        value)))


;;; Handle-G2GL-execution-fault-after-any-breakpoint
;;;   (execution-thread thread, g2gl-execution-fault fault):
;;;
;;; This finds the proper fault handler (catch activity) compilation, if there
;;; is one, to start executing to handle the fault after it kills threads that
;;; should no longer exist.  First, when the G2GL-activity-class-code of the
;;; activity-compilation-to-execute of thread is a class code for an invoke
;;; activity, it looks for an applicable local fault handler compilation to
;;; execute.  Then it looks within the immediate body compilation (the
;;; G2GL-body-compilation of the activity-compilation-to-execute of the
;;; parent-execution-thread of thread) and up through successive enclosing body
;;; compilations, at each level appropriately killing all threads being used to
;;; execute that body compilation as well as all descendant threads of those
;;; threads but first, if it doesn't find applicable fault handler compilation
;;; at this level to execute, doing implicit fault and compensation handling as
;;; appropriate.  The job of a fault handler compilation is to clean up from
;;; (undo as appropriate) the unfinished work of the immediate body compilation,
;;; which might involve undoing (compensating) the finished work of subordinate
;;; body compilations by executing their compensation handler compilations.
;;;
;;; This reclaims the fault.

(defun handle-g2gl-execution-fault-after-any-breakpoint (thread fault)
  (cond
    ((and (=f (g2gl-activity-class-code
                (activity-compilation-to-execute thread))
              (quoted-g2gl-activity-class-code g2gl-invoke))
          (handle-g2gl-execution-fault-per-invoke-activity-compilation-if-possible
            thread fault))
     (delete-g2gl-execution-thread thread nil nil)
     ;; -- this step handles a fault occurring during the execution of an invoke
     ;; activity compilation
     )
    (t
     ;; this starts with the current body compilation and then goes up through
     ;; enclosing body compilations, looking for an applicable fault handler
     ;; compilation, executing it if found, doing [...]
     (loop for thread-or-ancestor-thereof = thread then parent-thread
           for parent-thread
               = (parent-execution-thread thread-or-ancestor-thereof)
           as f = (parent-execution-frame thread-or-ancestor-thereof)
           as c = (activity-compilation-to-execute thread-or-ancestor-thereof)
           do (cond
                ((eq (execution-thread-state thread-or-ancestor-thereof)
                     'abnormal)
                 ;; We're already handling a fault, keep going up.
                 (unless (=f (g2gl-activity-class-code
                               (activity-compilation-to-execute
                                 thread-or-ancestor-thereof))
                             (quoted-g2gl-activity-class-code
                               g2gl-fault-handler))
                   ;; ...But if we're not at a fault handler, i.e. we're doing
                   ;; compensation, "up" may actually be sideways, i.e. we go to
                   ;; the compensating thread, not the parent thread.  The
                   ;; compensating thread is stored in the state parameter in
                   ;; this case.
                   (let ((parameter (execution-thread-state-parameter
                                      thread-or-ancestor-thereof)))
                     (when (g2gl-execution-thread-p parameter)
                       (setq parent-thread parameter))))
                 (delete-g2gl-execution-thread
                   thread-or-ancestor-thereof nil nil))
                ((handle-G2GL-execution-fault-per-body-compilation-if-possible
                   parent-thread
                   (body-compilation-this-is-being-used-to-execute
                     thread-or-ancestor-thereof)
                   fault
                   f)
                 (return)))
           when (null parent-thread)
             ;; Unhandled fault at the top level, exit the process.
             do (exit-g2gl-process-instance-with-fault f fault)
                (return)))))



;;; Handle-G2GL-execution-fault-per-invoke-activity-compilation-if-possible
;;; (execution-thread-at-invoke-activity-compilation thread,
;;;  g2gl-execution-fault fault):
;;;
;;; This returns true or nil depending on whether it did or did not find an
;;; applicable local fault handler and schedule a newly created thread to
;;; execute it.
;;;
;;; This does not delete any threads.  This reclaims the fault if it is
;;; handled.

(defun handle-g2gl-execution-fault-per-invoke-activity-compilation-if-possible
    (thread fault)
  (let ((applicable-fault-handler-compilation
          (check-for-applicable-fault-handler-compilation
            (cdr
              (activity-compilation-successors ; may be nil
                (activity-compilation-to-execute thread)))
            fault)))
    (cond
      (applicable-fault-handler-compilation
       (schedule-applicable-fault-handler-compilation
         applicable-fault-handler-compilation
         fault
         (parent-execution-thread thread)
         (body-compilation-this-is-being-used-to-execute thread)
         (parent-execution-frame thread))
       t)
      (t nil))))





;;; The macro `class-code-for-g2gl-event-handler-activity-p' is true if code, a
;;; class code for a G2GL activity, the class code for an event handler
;;; activity, i.e., the corresponding to one of these classes:
;;;
;;;   g2gl-message-event-handler; or
;;;   g2gl-alarm-event-handler
;;;
;;; Note that these are the only two instantiable "event handler" classes, i.e.,
;;; the only two instantiable subclasses of g2gl-event-handler.

(defun-substitution-macro class-code-for-g2gl-event-handler-activity-p (code)
  (or (=f code (quoted-g2gl-activity-class-code g2gl-message-event-handler))
      (=f code (quoted-g2gl-activity-class-code g2gl-alarm-event-handler))))




;;; The function `thread-is-idle-event-handler-p' returns t iff thread is
;;; positioned at an event handler activity whose body is not currently being
;;; executed by a child thread.

(defun-simple thread-is-idle-event-handler-p (thread)
  (and (class-code-for-g2gl-event-handler-activity-p
         (g2gl-activity-class-code
           (activity-compilation-to-execute thread)))
       (not (eq (execution-thread-state thread) 'executing-body))))




;;; Handle-G2GL-execution-fault-per-body-compilation-if-possible
;;; (parent-execution-thread parent-thread, body-compilation b,
;;;  g2gl-execution-fault fault, execution-frame f):

;;; This returns true if it found an applicable fault handler compilation hc
;;; belonging to b (or a compensation handler compilation hc belonging to an
;;; activity compilation belonging to b) and scheduled a newly created thread to
;;; execute hc; otherwise, it returns nil.

;;; If parent-thread is non-nil, in which case its
;;; activity-compilation-to-execute must be a G2GL activity-with-body
;;; compilation, b will be the G2GL-body-compilation of the
;;; activity-compilation-to-execute of parent-thread; otherwise, b will be the
;;; G2GL-body-compilation of the appropriate compilation version.

;;; This deletes those threads in f whose parent-execution-thread is
;;; parent-thread and whose execution thread state is not the symbol abnormal,
;;; meaning that are not doing fault or compensation handling.  This reclaims
;;; the fault if it is handled.

(defun handle-g2gl-execution-fault-per-body-compilation-if-possible
    (parent-thread b fault f)
  (let* ((applicable-fault-handler-compilation
           (check-for-applicable-fault-handler-compilation
             (g2gl-fault-handler-compilations b)
             fault))
         scheduled-a-compensation-handler-thread-p)
    (cond
      (applicable-fault-handler-compilation
       (schedule-applicable-fault-handler-compilation
         applicable-fault-handler-compilation
         fault parent-thread b f)
       ;; -- note that this is done before potentially killing off any threads,
       ;; for one thing to preserve execution displays for b if they might be
       ;; needed to show execution of applicable-fault-handler-compilation
       )
      (t
       ;; applicable-fault-handler-compilation is nil, do implicit fault
       ;; handling if needed
       (let ((sibling-thread
               (loop for th in (g2gl-execution-threads f)
                     when (eq (parent-execution-thread th) parent-thread)
                       return th)))
         ;; There might be no sibling thread (i.e. no thread on b) in the case
         ;; of a forced-termination fault sent to an event handler whose body is
         ;; not currently running, e.g. an alarm-event-handler that hasn't
         ;; triggered yet.  (This is the only way a fault can be sent "downward"
         ;; from an enclosing scope, instead of "upward" from an activity on b.)
         ;; In this case, no compensation should be done at this point-- any
         ;; normal completions from previous incarnations of b will be
         ;; compensated when (if) the parent activity is compensated.
         (when sibling-thread
           (setq scheduled-a-compensation-handler-thread-p
                 (schedule-g2gl-compensation-if-necessary
                   sibling-thread nil nil fault f))))))
    ;; Terminate all normal sibling threads, giving them a chance to handle the
    ;; forced-termination fault first.
    (loop with related-thread
          with c
          with class-code
          while
          (setq related-thread
                (loop for th in (g2gl-execution-threads f)
                      when (and (eq (parent-execution-thread th) parent-thread)
                                (not (eq (execution-thread-state th) 'abnormal)))
                        return th))
          do (setq c (activity-compilation-to-execute related-thread))
             (setq class-code (g2gl-activity-class-code c))
          when (and
                 (=f class-code (quoted-g2gl-activity-class-code g2gl-invoke))
                 (eq (execution-thread-state related-thread) 'in-partner-link))
            ;; -- nonstandard formatting here --
      do (handle-g2gl-execution-fault-per-invoke-activity-compilation-if-possible
           related-thread (make-g2gl-system-fault 'forced-termination))
            ;; -- end nonstandard formatting --
          when (or
                 (=f class-code (quoted-g2gl-activity-class-code g2gl-scope))
                 (class-code-for-g2gl-event-handler-activity-p class-code))
            ;; -- nonstandard formatting here --
       do (handle-g2gl-execution-fault-per-body-compilation-if-possible
            related-thread (g2gl-body-compilation c)
            (make-g2gl-system-fault 'forced-termination) f)
            ;; -- end nonstandard formatting --
          do (delete-g2gl-execution-thread related-thread nil nil))
    (or applicable-fault-handler-compilation
        scheduled-a-compensation-handler-thread-p)))



;;; Check-for-applicable-fault-handler-compilation (handler-compilations
;;; handler-compilations, g2gl-execution-fault fault):

(defun check-for-applicable-fault-handler-compilation
    (handler-compilations fault)
  (let ((fault-name (g2gl-execution-fault-name fault))
        (fault-data (g2gl-execution-fault-data fault)))
    (or (cond
          ((null fault-data)
           (loop for hc in handler-compilations
                 when (and (=f (g2gl-activity-class-code hc)
                               (quoted-g2gl-activity-class-code
                                 g2gl-fault-handler))
                           (eq (c-g2gl-fault-name hc) fault-name)
                           ;; With no fault data, a handler only matches if it
                           ;; has no fault variable (i.e. no arg-variables on
                           ;; its body-compilation).  This is somewhat ambiguous
                           ;; in BPEL4WS, but is clarified in WS-BPEL.
                           ;; -dougo, 2/23/07
                           (loop for vc in (g2gl-variable-compilations
                                             (g2gl-body-compilation hc))
                                 never (=f (g2gl-variable-class-code vc)
                                           (quoted-g2gl-activity-class-code
                                             g2gl-arg-variable))))
                   return hc))
          (t                                ; fault data is non-nil
           (or
             (loop for hc in handler-compilations
                   when (and (=f (g2gl-activity-class-code hc)
                                 (quoted-g2gl-activity-class-code
                                   g2gl-fault-handler))
                             (eq (c-g2gl-fault-name hc) fault-name)
                             (has-matching-fault-variable hc fault-data))
                     return hc)
             (loop for hc in handler-compilations
                   when (and (=f (g2gl-activity-class-code hc)
                                 (quoted-g2gl-activity-class-code
                                   g2gl-fault-handler))
                             (null (c-g2gl-fault-name hc))
                             (has-matching-fault-variable hc fault-data))
                     return hc))))
        (loop for hc in handler-compilations
              when (and (=f (g2gl-activity-class-code hc)
                            (quoted-g2gl-activity-class-code
                              g2gl-fault-handler))
                        (eql (c-g2gl-fault-name hc) 0)) ; the catch-all case
                return hc)
        nil)))



;;; Has-matching-fault-variable (fault-handler-compilation hc, fault-data
;;; fault-data):

(defun has-matching-fault-variable (hc fault-data)
  (loop for vc in (g2gl-variable-compilations (g2gl-body-compilation hc))
        thereis (and (=f (g2gl-variable-class-code vc)
                         (quoted-g2gl-variable-class-code g2gl-arg-variable))
                     ;; such that fault-data is an inst. of var. type
                     (case (c-g2gl-variable-type vc)
                       (general t)
                       (float (managed-float-p fault-data))
                       (integer (fixnump fault-data))
                       (quantity (managed-number-p fault-data))
                       (symbol (symbolp fault-data))
                       (text (wide-string-p fault-data))
                       (sequence (evaluation-sequence-p fault-data))
                       (structure (evaluation-structure-p fault-data))
                       ;; handle others, e.g., class instances!
                       ;; abstract test!
                       ))))





;;; The function `schedule-g2gl-compensation-if-necessary' performs compensation
;;; during the process of fault handling.
;;;
;;; `sibling-thread' is any thread positioned on the body-compilation containing
;;; the activity to be compensated.  `specific-name' is a symbol (naming the
;;; specific activity to be compensated) or NIL (indicating the activity that
;;; most recently completed normally).  `compensating-thread' is a thread
;;; positioned at a compensate activity compilation that is being executed (or
;;; NIL if there is no explicit compensate activity).  `fault' is the fault
;;; currently being thrown.  (This is NIL if this is not called from an implicit
;;; fault handler, in which case the fault is already in the process of being
;;; handled and the fault data has already been stored in an argument variable
;;; of the fault handler.)  `f' is the process execution frame.
;;;
;;; This looks in sibling-thread for the most recent normal completion of a
;;; scope, invoke, or event handler activity (whose name is specific-name, if
;;; non-NIL).  If it finds one, it removes the normal completion from
;;; sibling-thread and schedules a new abnormal thread to execute it, parking
;;; compensating-thread (or storing fault) in this new thread (or one of its
;;; ancestors) and returning T; otherwise, NIL is returned.

(defun schedule-g2gl-compensation-if-necessary
    (sibling-thread specific-name compensating-thread fault f)
  (let* ((normal-completions (normal-completions-of-nested-compilations
                               sibling-thread))
         (normal-completion
           (if specific-name
               (loop for nc in normal-completions
                     when (eq (g2gl-activity-name
                                (normally-completed-activity-compilation nc))
                              specific-name)
                       return nc)
               (car normal-completions)))) ;nil is OK
    (unless normal-completion
      (return-from schedule-g2gl-compensation-if-necessary nil))
    (setf (normal-completions-of-nested-compilations sibling-thread)
          (delete-gensym-element normal-completion normal-completions))
    (multiple-value-bind (top-thread bottom-thread)
        (make-g2gl-compensation-threads
          normal-completion
          (parent-execution-thread sibling-thread)
          sibling-thread
          (body-compilation-this-is-being-used-to-execute sibling-thread)
          f)
      (setf (execution-thread-state-parameter top-thread)
            ;; If there is a compensating thread (i.e. there was an explicit
            ;; fault handler), park it in the top thread, so that the
            ;; compensating thread can be woken up again when compensation is
            ;; finished to do the next compensation (if any).  [TO DO: what if
            ;; compensating-thread gets interrupted and deleted?  This parameter
            ;; might become garbage!]
            (or compensating-thread
                ;; If there is a fault, continue with implicit fault handling.
                fault
                ;; Otherwise, continue with implicit compensation handling.
                'implicit-compensation-handler))
      (schedule-g2gl-execution-thread bottom-thread nil)))
  t)

;;; The function `make-g2gl-compensation-threads' descends a tree of normal
;;; completions until we find an activity that has a compensation handler (there
;;; is guaranteed to be one), creating abnormal threads along the way down.  Two
;;; values are returned, the top and bottom threads (which might be the same if
;;; the activity to compensate has a local compensation handler).  The top
;;; thread will have the given parent, sibling, body b, and frame f.  The bottom
;;; thread will be positioned at a compensation handler.

(defun make-g2gl-compensation-threads
    (normal-completion parent-thread sibling-thread b f)
  (let ((c (normally-completed-activity-compilation normal-completion))
        (outside-vars (outside-variable-bindings normal-completion))
        (deeper-ncs (deeper-normal-completions normal-completion)))
    (declare (ignore outside-vars))        ;TO DO: use this!
    (setf (deeper-normal-completions normal-completion) nil)
    (reclaim-normal-completion normal-completion)
    (when (=f (g2gl-activity-class-code c)
              (quoted-g2gl-variable-class-code g2gl-invoke))
      ;; An invoke activity is the only thing that can have a local handler.
      (let* ((hc (loop for hc in (cdr (activity-compilation-successors c))
                       when (=f (g2gl-activity-class-code hc)
                                (quoted-g2gl-activity-class-code
                                  g2gl-compensation-handler))
                         return hc))
             (thread (make-g2gl-execution-thread
                       hc nil t parent-thread sibling-thread b f)))
        (return-from make-g2gl-compensation-threads
          (values thread thread))))
    ;; Otherwise, we're at an activity-with-body, make a thread positioned at it
    ;; and look for a handler on its body.
    (setq parent-thread
          (make-g2gl-execution-thread c nil t parent-thread sibling-thread b f))
    (setq b (g2gl-body-compilation c))
    (let ((hcs (g2gl-compensation-handler-compilations b)))
      (when hcs
        (let ((thread (make-g2gl-execution-thread
                        (car hcs) nil t parent-thread nil b f)))
          (setf (normal-completions-of-nested-compilations thread)
                deeper-ncs) ;used by compensate activities in the handler
          (return-from make-g2gl-compensation-threads
            (values parent-thread thread)))))
    ;; Implicit compensation handler: compensate the most recent deeper normal
    ;; completion.
    (multiple-value-bind (top-thread bottom-thread)
        (make-g2gl-compensation-threads (car deeper-ncs) parent-thread nil b f)
      (setf (execution-thread-state-parameter top-thread)
            'implicit-compensation-handler)
      (setf (normal-completions-of-nested-compilations top-thread)
            (cdr deeper-ncs))
      (reclaim-gensym-cons deeper-ncs)
      (values parent-thread bottom-thread))))




;;; Schedule-applicable-fault-handler-compilation (fault-handler-compilation hc,
;;; g2gl-execution-fault fault, parent-execution-thread parent-thread,
;;; body-compilation b, execution-frame f):
;;;
;;; This reclaims the fault.

(defun schedule-applicable-fault-handler-compilation
    (hc fault parent-thread b f)
  (let* ((sibling-thread                ; related-thread, if any
           (loop for th in (g2gl-execution-threads f)
                 when (eq (parent-execution-thread th) parent-thread)
                   return th))
         (thread
           (make-g2gl-execution-thread
             hc nil t parent-thread sibling-thread b f))
         (fault-data (g2gl-execution-fault-data fault)))
    (when fault-data
      (setf (execution-thread-state-parameter thread)
            ;; single-element list of fault data:
            (gensym-list fault-data))
      (setf (g2gl-execution-fault-data fault) nil))
    (reclaim-g2gl-execution-fault fault)
    (schedule-g2gl-execution-thread thread nil)))





;;; Reclaim-g2gl-values (args args):

(defun reclaim-g2gl-values (args)
  (loop for arg in args
        do (remove-reference-to-g2gl-value arg))
  (reclaim-gensym-list args))




;;; `Make-g2gl-execution-frame' allocates a g2gl-execution-frame structure,
;;; initializes its slots appropriately, and returns the new structure.
;;;
;;; Args:
;;;
;;; v - compilation-version

(defun make-g2gl-execution-frame (v)
  (let* ((f (make-g2gl-execution-frame-internal))
         (s (source-g2gl-process v))
         (name-or-names (name-or-names-for-frame s))
         (name? (if (atom name-or-names) name-or-names (car name-or-names))))
    (setf (parent-compilation-version f) v)
    (setf (g2gl-variable-values-vector f)
          (allocate-managed-array
            (next-variable-index-to-assign v)
            ;; LH: it is probably not really necessary to set the elements of
            ;; the G2GL-variable-values-vector of f to nil -- MHD: therefore,
            ;; consider adding these args:  (for a bit of extra performance)
            ;;
            ;;   :dont-initialize nil
            ))
    (setf (g2gl-execution-threads f) nil)
    (setf (g2gl-process-instance-handle f)
          ;; cdr made nil initially, but may, at a later point, get filled in
          ;; with a process-instance (reference).
          (gensym-cons name? nil))
    (setf (normal-completion-of-process-body-compilation f) nil)
    (gensym-push f (current-execution-frames v))
    f))





;;; Reclaim-G2GL-process (G2GL-process s):
;;;
;;; Because a G2GL process s might be deleted as a G2 object interactively by a
;;; user, this special reclaimer is provided.  Reclaim-G2GL-process, before
;;; reclaiming attribute values of s appropriately, immediately terminates
;;; execution of all instances of all existing compilation versions of s, before
;;; then deleting those compilation versions.

(defun reclaim-g2gl-process (s)
  (disown-current-compilation-version-if-any s)
  (terminate-all-instances-of-g2gl-process s)
  (delete-compilation-structure s)
  ;; Do any specialized reclamation of attribute values in s if needed. [None
  ;; should be needed! See note! -mhd, 2/8/05]
  )

;; Note: I don't really see the point of the above.  What it does has to be done
;; whether interactively deleting or not.  The main difference between
;; interactive and non-interactive should just be that you're prompted to
;; confirm that you want to kill process instances in the interactive case.
;; That should be done with specialized messaging around the delete command. It
;; can use the following to prompt for confirmation of the process instances
;; about to be deleted. Meanwhile, the attribute values are reclaimed via
;; automatic means.  The cleanup method could invoke the kill-all-... call
;; directly, but, for now, I'll have it call the above. (MHD 2/8/05)


(defun count-instances-of-g2gl-process (s)
  (loop for v in (stack-of-compilation-versions s)
        sum (loop for f in (current-execution-frames v)
                  count t)))


;;; Terminate-all-instances-of-g2gl-process (G2GL-process s):

(defun terminate-all-instances-of-g2gl-process (s)

  ;; this loop deals with all but the first compilation version:
  (loop while (cdr (stack-of-compilation-versions s)) ; 2 or more in stack, 1 old
        do (exit-g2gl-process-instance
             (first (current-execution-frames
                      (second (stack-of-compilation-versions s))))
             nil))

  ;; now there are zero or one compilation versions

  ;; this loop gets rid of instances of the current compilation version, if any,
  ;; but not of any compilation versions:
  (loop with fs                                ; execution frames (f's)
        while (and (stack-of-compilation-versions s)
                   (setq fs
                         (current-execution-frames
                           (car (stack-of-compilation-versions s)))))
        do (exit-g2gl-process-instance (first fs) nil)))



;;; Terminate-all-instances-of-g2gl-process ():
;;;
;;; This is intended to be called from the system-reset function.

(defun kill-all-instances-of-all-g2gl-processes ()
  (loop for s being each class-instance of 'g2gl-process
        do (terminate-all-instances-of-g2gl-process s)))





;;; exit-g2gl-process-instance (execution-frame f, return-case return-case):

(defun exit-g2gl-process-instance (f return-case)
  (when (g2gl-process-instance-handle f) ; nec.?
    (let* ((handle-data? (cdr (g2gl-process-instance-handle f)))
           (g2gl-process-instance?
             (if (and handle-data?
                      (evaluation-item-reference-p handle-data?))
                 (evaluation-item-reference-referenced-item handle-data?))))
      (when g2gl-process-instance?
        (reclaim-evaluation-item-reference handle-data?)
        (setf (g2gl-process-instance-execution-frame g2gl-process-instance?) nil)
        (delete-frame g2gl-process-instance?)))
    (reclaim-gensym-cons
      ;; -- for HQ-5329578 "G2GL: leak executing G2GL process" (MHD 7/22/06)
      (g2gl-process-instance-handle f)))
  (loop while (g2gl-execution-threads f)
        ;; The following does all necessary cleanups, including removing
        ;; elements from (g2gl-execution-threads f).
        do (delete-g2gl-execution-thread
             (first (g2gl-execution-threads f)) nil nil))

  (when (normal-completion-of-process-body-compilation f)
    (reclaim-normal-completion
      (normal-completion-of-process-body-compilation f)))

  ;; To do: reclaim values in the variable values vector!!

  (when (parked-process-invocation-thread f)
    (let* ((invocation-thread (parked-process-invocation-thread f)))
      (setf (process-invocation-frame invocation-thread) nil)
      (setf (process-invocation-state invocation-thread)
            (if return-case 'return 'done))
      (schedule-process-invocation-thread invocation-thread nil)))

  (reclaim-managed-array (g2gl-variable-values-vector f))
  (setf (g2gl-variable-values-vector f) nil)

  (let ((v (parent-compilation-version f)))
    (setf (current-execution-frames v)
          (delete-gensym-element f (current-execution-frames v)))
    (reclaim-g2gl-execution-frame f)
    (let ((s (source-g2gl-process v)))
      (when (and (null (current-execution-frames v))
                 (or
                   (not (eq v (first (stack-of-compilation-versions s))))
                   (latest-existing-compilation-version-was-disowned s)))
        (delete-unowned-compilation-version-if-possible v)))))



;;; The function `exit-g2gl-process-instance-with-fault' abnormally exits the
;;; process instance for execution frame f with an unhandled fault at the top
;;; level.  This reclaims the fault.

(defun exit-g2gl-process-instance-with-fault (f fault)
  (let ((invocation-thread (parked-process-invocation-thread f)))
    (if invocation-thread
        (setf (process-invocation-result invocation-thread) fault)
        (reclaim-g2gl-execution-fault fault)))
  (exit-g2gl-process-instance f nil))




;;; Make-G2GL-execution-thread (activity-compilation c,
;;; predecessor-activity-compilation predecessor-c, thread-is-to-be-abnormal
;;; abnormal-case, parent-execution-thread parent-thread,
;;; sibling-execution-thread sibling-thread, body-compilation b, execution-frame
;;; f):
;;;
;;; When parent-thread is nil, the new thread is for the top-level body
;;; compilation of a G2GL process; otherwise, it is for the body compilation of
;;; a G2GL activity-with-body that parent-thread is being used to execute.
;;;
;;; When sibling-thread is nil, the new thread is for an entry activity
;;; compilation; otherwise, it is an additional thread for either a concurrently
;;; executing flow-split activity compilation branch, a flow-gate activity
;;; compilation arrived at via a BPEL link, a concurrently executing handler
;;; compilation, or a scope activity compilation to be executed abnormally on
;;; behalf of a concurrently executing fault or compensation handler
;;; compilation.
;;;
;;; The g2gl-flow-scope-markers-in-this-thread slot of the new thread is
;;; initialized with a copy of the list in the thread the new thread inherits
;;; from (namely, sibling-thread in case it's non-nil, and this abnormal-case is
;;; not true; otherwise, parent-thread), if any.
;;;
;;; This returns thread, appropriately initialized and shown as a thread
;;; location object on each of its execution displays, with its state
;;; reflecting, when appropriate, a breakpoint on entry or a tracing transition
;;; between activity compilations.

(defun make-g2gl-execution-thread
    (c predecessor-c abnormal-case parent-thread sibling-thread b f)
  (let* ((thread-to-inherit-from
           (if (and sibling-thread (not abnormal-case))
               sibling-thread
               parent-thread))
         (thread (make-g2gl-execution-thread-internal)))
    (setf (parent-execution-frame thread) f)
    (setf (parent-execution-thread thread)
          parent-thread)                ; could be nil
    (setf (activity-compilation-to-execute thread) c)
    (setf (predecessor-activity-compilation thread) predecessor-c)
    (setf (body-compilation-this-is-being-used-to-execute thread) b)
    (setf (execution-thread-state thread) (if abnormal-case 'abnormal))
    (setf (execution-thread-state-parameter thread) nil) ; not really nec.
    (setf (location-of-execution-thread-in-g2-schedule thread) nil)
    (setf (outside-variable-bindings-for-execution thread)
          (if parent-thread
              (outside-variable-bindings-for-execution parent-thread)))
    (setf (normal-completions-of-nested-compilations thread)
          (if sibling-thread
              (normal-completions-of-nested-compilations sibling-thread)))
    (setf (thread-token-properties thread) nil)
    (setf (g2gl-flow-scope-markers-in-this-thread thread)
          (if thread-to-inherit-from
              (copy-list-using-gensym-conses
                (g2gl-flow-scope-markers-in-this-thread
                  thread-to-inherit-from))))
    (when (and thread-to-inherit-from
               (thread-token-properties thread-to-inherit-from))
      (setf (thread-token-properties thread)
            (copy-gensym-tree-with-text-strings
              ;; (copying the alist structure and any value that is a string)
              (thread-token-properties thread-to-inherit-from))))
    (gensym-push thread (g2gl-execution-threads f))
    (cond
      (sibling-thread
       (let* ((execution-displays (g2gl-execution-displays sibling-thread)))
         (cond
           ((null execution-displays)
            thread)
           (t
            (setf  (g2gl-execution-displays thread)
                   (copy-list-using-gensym-conses execution-displays))
            (setf (thread-tokens-for-execution-displays thread)
                  (loop for l on (g2gl-execution-displays thread)
                        ;; make one location object per display
                        collect (make-g2gl-thread-token thread)
                          using gensym-cons))
            (cond
              (predecessor-c
               (set-up-transition-from-predecessor-activity-compilation
                 thread predecessor-c nil))
              (t
               (position-thread-tokens-above-activity-to-execute thread)))
            (add-thread-tokens-to-execution-displays thread)
            thread))))
      (t
       ;; Past here, sibling-thread is nil, that is, thread is for an entry
       ;; activity compilation and has no execution displays as yet.
       (let* ((s (source-g2gl-process (parent-compilation-version f)))
              (mode (individual-execution-display-mode s))
              d
              (breakpoint-at-entry-activity
                (or (eq mode 'break-on-entry-at-all-levels)
                    (and (eq mode 'break-on-entry)
                         (null parent-thread))
                    (and parent-thread
                         (g2gl-execution-displays parent-thread)
                         (not (eq (execution-display-mode
                                    (setq d (first (g2gl-execution-displays
                                                     parent-thread))))
                                  'superimposed-tracings))
                         (or (eq (execution-display-mode d) 'single-step)
                             (memq
                               (activity-compilation-to-execute parent-thread)
                               (temporary-breakpoints-for-execution-display d))))))
              (doing-superimposed
                (and (superimposed-tracings-execution-display-mode s)
                     (or (null parent-thread)
                         (eq (superimposed-tracings-execution-display-mode s)
                             'trace-all-levels)))))

         (when (or (eq mode 'trace-all-levels)
                   (and (eq mode 'trace-top-level)
                        (null parent-thread))
                   breakpoint-at-entry-activity)
           (make-and-put-up-execution-display thread nil doing-superimposed))
         (when (and breakpoint-at-entry-activity
                    ;; In the abnormal case, this is a parked thread doing
                    ;; compensation or handling a forced-termination fault
                    ;; (these are the only ways an abnormal thread can be
                    ;; created "from above", i.e. without being caused by a
                    ;; fault in a sibling thread).  Don't put the breakpoint
                    ;; here, wait until the handler body thread gets created.
                    (not abnormal-case))
           (effect-g2gl-breakpoint
             thread
             (tformat-text-string "breakpoint at entry activity")
             nil))
         (when doing-superimposed
           (cond
             ((setq d (execution-display-for-superimposed-tracings b))
              (show-thread-on-execution-display thread d))
             (t
              (make-and-put-up-execution-display
                thread 'superimposed-tracings))))
         thread)))))





;;; Effect-G2GL-breakpoint
;;;   (execution-thread-with-individual-execution-display thread,
;;;    breakpoint-button-text text-string,
;;;    g2gl-execution-fault fault):
;;;
;;; Text-string will become part of the G2GL breakpoint button this creates and
;;; will ultimately be reclaimed.  The fault will also be reclaimed.

(defun effect-g2gl-breakpoint (thread text-string fault)
  (let* ((d (first (g2gl-execution-displays thread)))
         (button (make-button 'g2gl-breakpoint-button nil nil t))
         (thread-token (first (thread-tokens-for-execution-displays thread)))
         p)
    (setf (breakpoint-button-execution-thread button) thread)

    ;; the text string goes into the breakpoint-button-text of button, to be
    ;; shown as an attribute display to the right of the button icon.  Use
    ;; change-slot-value for the side effect of changing the text on the
    ;; attribute display, which is defined to display this attribute (in the
    ;; class definition).
    (change-slot-value
      button 'breakpoint-button-text
      (convert-text-string-to-text text-string))

    ;; place button appropriately above (centered horizontally with respect to)
    ;; the thread token that is the first element of the
    ;; thread-tokens-for-execution-displays of thread:
    (setq p
          (make-g2gl-body-position
            (halfw
              (-w (+w (left-edge-of-block thread-token)
                      (right-edge-of-block thread-token))
                  (width-of-block button)))
            (-w (top-edge-of-block thread-token)
                ;; spacing parameter?
                5)))
    (add-to-g2gl-body button d p)
    (reclaim-g2gl-body-position p)

    (setf (execution-thread-state thread) 'at-breakpoint)

    (setf (execution-thread-state-parameter thread)
          (gensym-cons
            ;; NEED FRAME SERIAL NUMBER OR SIMILAR MECHANISM TO HANDLE CHECKING
            ;; FOR DELETION OF THE BUTTON FRAME!
            button
            (when fault (gensym-list fault))))))





(def-class-method click (g2gl-breakpoint-button x-in-workspace y-in-workspace)
  (highlight-or-unhighlight-button g2gl-breakpoint-button t)
  (cond
    ;; 1. Release isn't over the button at all.
    ((not (in-block-p g2gl-breakpoint-button x-in-workspace y-in-workspace))
     ;; do nothing
     nil)
    (t (handle-g2gl-breakpoint-button-click g2gl-breakpoint-button))))





;;; Handle-G2GL-breakpoint-button-click (G2GL-breakpoint-button button):
;;;
;;; This is ordinarily invoked by the part of G2 that handles clicks on objects
;;; on workspace displays, but it also might be invoked when the display with
;;; button on it is to be deleted, acting in that case as if the user had
;;; actually clicked on button.
;;;
;;; Besides handling an actual or simulated click on button, this also acts as
;;; if other breakpoint buttons on the same activity, say a flow-sync activity,
;;; had been clicked on.

(defun handle-g2gl-breakpoint-button-click (button)
  (loop with button-maybe
        with thread = (breakpoint-button-execution-thread button)
        for related-thread
            in (g2gl-execution-threads (parent-execution-frame thread))
        when (and (eq (activity-compilation-to-execute related-thread)
                      (activity-compilation-to-execute thread))
                  (eq (parent-execution-thread related-thread)
                      (parent-execution-thread thread))
                  (eq (execution-thread-state related-thread) 'at-breakpoint)
                  (not (eq (setq button-maybe
                                 (first
                                   (execution-thread-state-parameter
                                     related-thread)))
                           'ready-to-proceed)))
          ;; -- button-maybe is thus is one of perhaps several G2GL breakpoint
          ;; buttons located where thread is located
          do (delete-frame button-maybe)
            ;; -- thus removing it as a subblock of the individual execution
            ;; display it belongs to and erasing it from any exposing windows
             (setf (first (execution-thread-state-parameter related-thread))
                   'ready-to-proceed)
             (schedule-g2gl-execution-thread related-thread nil)))





;;; Schedule-G2GL-execution-thread
;;;   (execution-thread thread,
;;;    time-if-specific time):
;;;
;;; If time is non-nil, it should be a unix time as a gensym-float, i.e.,
;;; suitable as the time arg to with-future-scheduling.
;;;
;;; At present, this uses priority 2.  Later, this should probably be
;;; paramterized.

(defparameter priority-for-g2gl-thread-execution 2)

(defun schedule-g2gl-execution-thread (thread time)
  ;; insert execution-thread thread into the G2 schedule to resume execution at
  ;; time, updating (location-of-execution-thread-in-g2-schedule thread)
  ;; appropriately:
  (cond
    ((and (null time)
          (null (g2gl-execution-displays thread))
          (null (time-between-time-slices-for-execution-of-thread
                  g2gl-parameters)))
     ;; special mode - "continuous" running -- fastest possible
     ;; loops. Best/essential for benchmarking against G2 procedures until
     ;; our scheduler gets much more fine grained and can support
     ;; time-between times of less that 2 milliseconds! (MHD 1/10/05)
     (with-current-scheduling
         ((location-of-execution-thread-in-g2-schedule thread)
          priority-for-g2gl-thread-execution)
       (continue-execution-of-thread thread)))
    (t
     (with-temporary-gensym-float-creation
         schedule-g2gl-execution-thread
       (when (null time)
         (setq time
               (+e (g2gl-get-current-time)
                   (slot-value-number-value
                     (cond
                       ((null (g2gl-execution-displays thread))
                        (time-between-time-slices-for-execution-of-thread
                          g2gl-parameters))
                       ((eq (execution-thread-state thread) 'in-transit)
                        (time-between-mini-tracing-steps
                          g2gl-parameters))
                       (t
                        (time-between-maxi-tracing-steps
                          g2gl-parameters)))))))
       (with-future-scheduling
           ((location-of-execution-thread-in-g2-schedule thread)
            priority-for-g2gl-thread-execution
            time)
         (continue-execution-of-thread thread))))))

;; This does not follow the spec at all.  Needs review! (MHD 12/13/04)





;;; Unschedule-G2GL-execution-thread (execution-thread thread):

(defun unschedule-g2gl-execution-thread (thread)
  (cancel-task (location-of-execution-thread-in-g2-schedule thread)))









;;; Schedule-process-invocation-thread (process-invocation-thread
;;; invocation-thread, time-if-specific time):

(defun schedule-process-invocation-thread (invocation-thread time)
  (if (null time)
      (with-current-scheduling
          ((location-of-process-invocation-thread-in-G2-schedule
             invocation-thread)
           priority-for-g2gl-thread-execution)
        (continue-scheduled-process-invocation invocation-thread))
      (with-future-scheduling
          ((location-of-execution-thread-in-g2-schedule invocation-thread)
           priority-for-g2gl-thread-execution
           time)
        (continue-scheduled-process-invocation invocation-thread))))

;; Similar to schedule-g2gl-execution-thread, q.v. With some similar modest
;; divergence from spec -- (MHD 3/16/05)




(defun continue-scheduled-process-invocation (invocation-thread)
  (let ((context (process-invocation-context invocation-thread))
        (state (process-invocation-state invocation-thread))
        (result (process-invocation-result invocation-thread)))
    (cond
      ((code-body-continuation-p context)
       ;; The process was invoked by a procedure.  The invocation-thread and its
       ;; slots are reclaimed when the code-body-continuation completes, via
       ;; complete-process-invocation-thread (see below).
       (case state
         (return
           (return-value-to-code-body-continuation
             (allocate-evaluation-sequence
               ;; Convert G2GL values to G2 values:
               (loop for val in result
                     collect (copy-g2gl-value-as-item-or-evaluation-value val)
                       using eval-cons))
             context))
         (done
          (cond ((g2gl-execution-fault-p result)
                 (let ((fault (make-transient-item 'g2gl-fault))
                       (name (g2gl-execution-fault-name result))
                       (data (g2gl-execution-fault-data result))
                       (desc (g2gl-execution-fault-description result)))
                   (change-slot-value fault 'fault-name name)
                   (when data
                     (change-slot-value
                       fault 'fault-data
                       (copy-g2gl-value-as-item-or-evaluation-value data)))
                   (setq desc (twith-output-to-text-string
                                (twrite name)
                                (when desc (twrite ": ") (twrite desc))))
                   (change-slot-value fault 'error-description desc)
                   (signal-error-to-code-body-continuation
                     fault (copy-text-string desc) context)))
                (t
                 ;; either an abnormal, non-fault return (i.e., via exit
                 ;; activity), or a normal return with no values (i.e.,
                 ;; not via a return activity). For now: the abnormal case
                 ;; is not distinguished - review! (MHD 11/21/05)
                 (return-value-to-code-body-continuation
                   (allocate-evaluation-sequence nil) context))))))
      (t
       ;; else, must be for G2GL process; the process-invocation-context of
       ;; invocation-thread holds the calling thread, which we now continue:
       (let* ((execution-thread context)
              (invoc (execution-thread-state-parameter execution-thread))
              (variables (variables-to-receive-g2gl-call-values invoc))
              (fault-was-signaled-to-execution-thread nil))
         (setf (execution-thread-state-parameter execution-thread) nil)
         (cond
           ((eq state 'return)
            (loop for vars = variables then (cdr vars)
                  as vals = result then (cdr vals)
                  while (or vars vals)
                  do (cond
                       ((and vars vals)
                        (set-value-of-g2gl-variable
                          (second (car vars)) ; a variable compilation
                          (car vals)              ; a G2GL value
                          execution-thread))
                       ((null vals)
                        (setq fault-was-signaled-to-execution-thread t)
                        (signal-g2gl-system-fault
                          execution-thread
                          'g2gl-procedure-returned-too-few-values
                          (twrite 'g2gl-procedure) ; give name!!
                            )                           ; other data?!
                        (return))
                       ((null vars)
                        (remove-reference-to-g2gl-value (first vals)))))
            (reclaim-gensym-list result))
           ((eq state 'done)
            (cond
              (variables
               (setq fault-was-signaled-to-execution-thread t)
               (signal-g2gl-system-fault
                 execution-thread
                 'g2gl-procedure-terminated-without-return
                 (twrite 'g2gl-procedure) ; give name!!
                   ))
              (t
               ;; an error or just an (OK) non-returning process/procedure: OK?
               ;; handle error case some other way?!
               ))
            (when result (reclaim-g2gl-execution-fault result))))
         (reclaim-g2gl-call-invocation invoc)
         (unless fault-was-signaled-to-execution-thread
           ;; If a fault was signaled to execution-thread, then it does not need
           ;; to (and should not) be scheduled.  This check fixes HQ-5342482
           ;; "G2GL: g2 abort with no return block in process called as
           ;; procedure from process".  This fix is a little clunky (we have to
           ;; remember to set the boolean if any other faults get added) but I
           ;; think it's safer than trying to detect whether execution-thread
           ;; needs to be scheduled by inspecting its state (which might be
           ;; scheduled in a handler, at a breakpoint, dead because the fault
           ;; wasn't handled, or maybe other states I haven't thought of).
           ;; -dougo, 9/7/06
           (schedule-g2gl-execution-thread execution-thread nil))
         (reclaim-g2gl-process-invocation-thread invocation-thread))))))


;; Note: in the abort case, later, get the fault data, and pass it back for
;; error signalling! (MHD 3/30/05)



;;; The function `complete-process-invocation-thread' is called when the
;;; procedure that called a process completes, either normally or abnormally
;;; (e.g. by being aborted).  The process is aborted if it's still running, and
;;; the invocation-thread is unscheduled and reclaimed.

(defun-void complete-process-invocation-thread (completion-form)
  (let* ((invocation-thread (second completion-form))
         (frame (process-invocation-frame invocation-thread))
         (result (process-invocation-result invocation-thread)))
    (when frame
      (setf (parked-process-invocation-thread frame) nil)
      (exit-g2gl-process-instance frame nil))
    (unschedule-process-invocation-thread invocation-thread)
    (if (g2gl-execution-fault-p result)
        (reclaim-g2gl-execution-fault result)
        (reclaim-g2gl-values result))
    (reclaim-g2gl-process-invocation-thread invocation-thread))
  (reclaim-gensym-list completion-form))


;;; Unschedule-process-invocation-thread (process-invocation-thread
;;; invocation-thread):

(defun unschedule-process-invocation-thread (invocation-thread)
  (cancel-task (location-of-process-invocation-thread-in-g2-schedule
                 invocation-thread)))

;; Similar to unschedule-g2gl-execution-thread, q.v.





;;; `Record-normal-completion-of-nested-compilation'
;;; (execution-thread-unless-top-level thread,
;;; activity-with-body-or-invoke-activity-compilation-unless-top-level
;;; activity-compilation,
;;; compilations-of-outside-variables-used-in-immediate-compensation-handler
;;; outside-variables,
;;; normal-completions-of-one-level-more-deeply-nested-compilations
;;; deeper-normal-completions, execution-frame f):
;;;
;;; This is invoked on normal completion of a body compilation or an invoke
;;; activity compilation that has a local compensation handler compilation.
;;;
;;; This does not record a normal completion when thread is nil and the source
;;; G2GL process is not "instance-compensation-enabled"; instead, it
;;; appropriately reclaims deeper-normal-completions.
;;;
;;; This includes in a new normal-completion entry it records a "snapshot" of
;;; the current values of the G2GL variables specified by outside-variables,
;;; which is done even for the normal completion of a top-level body compilation
;;; provided the enable-instance-compensation of the source G2GL process is
;;; true, since it is needed when there are event handler compilations that
;;; could continue to execute and change the values of variables even after such
;;; a normal completion.

(defun record-normal-completion-of-nested-compilation
    (thread activity-compilation outside-variables deeper-normal-completions f)
  (cond
    ((and (null thread)
          (null (enable-instance-compensation
                  (source-g2gl-process
                    (parent-compilation-version f)))))
     (when deeper-normal-completions
       (reclaim-normal-completions deeper-normal-completions)))
    (t
     (let* ((outside-variable-bindings-for-compensation-handling
              (loop for c in outside-variables
                    collect (gensym-cons c (add-reference-to-g2gl-value
                                             (get-value-of-g2gl-variable c f)))
                      using gensym-cons))
            (normal-completion
              (make-normal-completion
                activity-compilation
                outside-variable-bindings-for-compensation-handling
                deeper-normal-completions)))
       (cond
         ((null thread)
          (setf (normal-completion-of-process-body-compilation f)
                normal-completion))
         ((normal-completions-of-nested-compilations thread)
          (setf (cdr (normal-completions-of-nested-compilations thread))
                (gensym-cons
                  (car (normal-completions-of-nested-compilations thread))
                  (cdr (normal-completions-of-nested-compilations thread))))
          (setf (car (normal-completions-of-nested-compilations thread))
                normal-completion))
         (t
          (loop with new-normal-completions-list
                  = (gensym-list normal-completion)
                for related-thread in (g2gl-execution-threads f)
                when (eq (parent-execution-thread related-thread)
                         (parent-execution-thread thread))
                  do (setf (normal-completions-of-nested-compilations
                             related-thread)
                           new-normal-completions-list))))))))







;;; Swap-values-of-outside-variable-bindings  (execution-thread thread):

(defun swap-values-of-outside-variable-bindings  (thread)
  (loop with f = (parent-execution-frame thread)
        with vvv = (g2gl-variable-values-vector f)
        for pair in (outside-variable-bindings-for-execution thread)
        as (vc . value-to-restore) = pair
        as i fixnum = (g2gl-variable-index vc)
        do (setf (cdr-of-cons pair) (managed-svref vvv i))
           (setf (managed-svref vvv i) value-to-restore)))


;;; Reclaim-normal-completions (normal-completions normal-completions):

(defun reclaim-normal-completions (normal-completions)
  (loop for l in normal-completions
        do (reclaim-normal-completion l))
  (reclaim-gensym-list normal-completions))



;;; Reclaim-outside-variable-bindings (outside-variable-bindings variable-bindings):

(defun reclaim-outside-variable-bindings (variable-bindings)
  (loop for pair in variable-bindings
        as value = (cdr pair)
        do (remove-reference-to-g2gl-value value)
           (reclaim-gensym-cons-macro pair))
  (reclaim-gensym-list variable-bindings))







;;; Delete-G2GL-execution-thread (execution-thread-with-no-children thread,
;;; known-to-have-normal-non-event-handler-sibling
;;; known-to-have-normal-non-event-handler-sibling, deletion-is-normal
;;; deletion-is-normal):
;;;
;;; If thread is normal but has no normal sibling threads, where "normal" means
;;; not being located at a handler, then, provided deletion-is-normal is true
;;; and the execution-thread-state of thread is not the symbol abnormal, the
;;; body compilation b being executed is now "normally complete", in which case
;;; this deletes those siblings of thread that are located at event-detecting
;;; event handlers and records a normal completion appropriately.
;;;
;;; If thread has execution displays, this deletes those of the execution
;;; displays that will no longer show any threads, once the thread token for
;;; thread is removed, and it also removes thread tokens for thread from those
;;; execution displays that are not deleted.
;;;
;;; This returns true if thread has one or more surviving siblings, where every
;;; surviving sibling must be either scheduled or managed by some other parked
;;; thread, or else nil, in which case values of G2GL variables bound by the
;;; body compilation now just fully completed will have been reclaimed as
;;; appropriate.

(defun delete-g2gl-execution-thread
    (thread known-to-have-normal-non-event-handler-sibling deletion-is-normal)
  (let* ((f (parent-execution-frame thread))
         (parent-thread (parent-execution-thread thread))
         (has-normal-non-event-handler-sibling
           known-to-have-normal-non-event-handler-sibling)
         (number-of-event-handler-siblings 0)
         (has-surviving-sibling nil)
         thread-state
         class-code
         parameter
         b
         immediate-compensation-handler-compilation-if-any
         outside-variables
         outside-variable-bindings)
    (when (not has-normal-non-event-handler-sibling)
      (loop for related-thread in (g2gl-execution-threads f)
            when (and (not (eq related-thread thread))
                      (eq (parent-execution-thread related-thread)
                          parent-thread))
              do (cond
                   ((class-code-for-g2gl-event-handler-activity-p
                      (g2gl-activity-class-code
                        (activity-compilation-to-execute related-thread)))
                    (incff number-of-event-handler-siblings))
                   ((eq (execution-thread-state related-thread) 'abnormal)
                    (setq has-surviving-sibling t))
                   (t
                    (setq has-normal-non-event-handler-sibling t)))))
    (when (and (not has-normal-non-event-handler-sibling)
               (>f number-of-event-handler-siblings 0)
               deletion-is-normal)        ; -- by implication, thread is normal
      (loop with related-thread
            while (setq related-thread
                        (loop for a-thread in (g2gl-execution-threads f)
                              when (and (eq (parent-execution-thread a-thread)
                                            parent-thread)
                                        (case (execution-thread-state a-thread)
                                          ((waiting in-partner-link)
                                           t)
                                          (t nil)))
                                return a-thread))
            do (delete-g2gl-execution-thread related-thread nil nil)
               (decff number-of-event-handler-siblings)))
    (when (or has-normal-non-event-handler-sibling
              (>f number-of-event-handler-siblings 0))
      (setq has-surviving-sibling t))
    (setq thread-state (execution-thread-state thread))
    (when (eq thread-state 'in-transit)
      (bypass-transition-to-activity-compilation thread)
      ;; -- this is just to reclaim the parameter list structure, including
      ;; any coordinate-pair elements
      )
    (when thread-state
      (setq class-code
            (g2gl-activity-class-code
              (activity-compilation-to-execute thread)))
      (setq parameter (execution-thread-state-parameter thread))
      (setf (execution-thread-state thread) nil)
      (setf (execution-thread-state-parameter thread) nil)
      (cond
        ((eq thread-state 'in-partner-link)
         (remove-thread-from-partner-links thread parameter))
        ((eq thread-state 'waiting)
         (reclaim-managed-float parameter)) ; a time
        ((and (eq thread-state 'in-procedure)
              (g2gl-call-invocation-p parameter))
         (let ((g2-invoc (g2-procedure-invocation-for-g2gl-call parameter)))
           (when g2-invoc
             (when (procedure-invocation-completion-form? g2-invoc)
               (setf (completion-form-for-g2gl-call parameter) nil)
               ;; -- completion form in parameter must be eq to that in g2-invoc
               (reclaim-gensym-list
                 (procedure-invocation-completion-form? g2-invoc))
               (setf (procedure-invocation-completion-form? g2-invoc) nil))
             (abort-procedure-invocation g2-invoc))
           (reclaim-g2gl-call-invocation parameter)))
        ((and (eq thread-state 'in-procedure)
              (g2gl-execution-fault-p parameter))
         (reclaim-g2gl-execution-fault parameter))
        ((and (eq thread-state 'abnormal)
              (=f class-code
                  (quoted-g2gl-activity-class-code
                    g2gl-fault-handler)))
         (reclaim-g2gl-values parameter))
        ((and (eq thread-state 'abnormal) (g2gl-execution-fault-p parameter))
         ;; compensating from an implicit fault handler
         (reclaim-g2gl-execution-fault parameter))
        ((eq thread-state 'at-breakpoint)
         (unless (symbolp (first parameter))
           ;; -- i.e., it's a button. so we delete it
           (delete-frame (first parameter)))
         (when (cdr parameter)
           (reclaim-g2gl-execution-fault (second parameter)))
         (reclaim-gensym-list parameter))))
    (unschedule-g2gl-execution-thread thread)
    (when (thread-token-properties thread)
      ;; reclaim the alist structure and any value that is a string:
      (reclaim-gensym-tree-with-text-strings
        (thread-token-properties thread)))
    (loop with d
          with related-thread
          while (g2gl-execution-displays thread)
          do (setq d (first (g2gl-execution-displays thread)))
             (cond
               ((not (eq (one-execution-thread-that-is-shown-hereon d) thread))
                (remove-execution-display-from-thread thread d))
               ((and
                  (or has-surviving-sibling
                      (eq (execution-display-mode d) 'superimposed-tracings))
                  (loop for execution-frame
                            in (current-execution-frames
                                 (parent-compilation-version f))
                        thereis
                        (loop for a-thread
                                  in (g2gl-execution-threads execution-frame)
                              when (and (not (eq a-thread thread))
                                        (memq d
                                              (g2gl-execution-displays
                                                a-thread)))
                                do (setq related-thread a-thread)
                                   (return t))))
                ;; if we're here, related-thread got a valid binding
                (setf (one-execution-thread-that-is-shown-hereon d)
                      related-thread)
                (remove-execution-display-from-thread thread d))
               (t
                (delete-g2gl-execution-display d))))
    (when (and (not (eq thread-state 'abnormal)) ; i.e., thread is normal
               (not has-surviving-sibling)
               deletion-is-normal)
      ;; -- i.e., this is the normal completion case, with the assumption that a
      ;; normal thread being abnormally deleted cannot have abnormal siblings
      (setq b (body-compilation-this-is-being-used-to-execute thread))
      (cond
        ((g2gl-compensation-handler-compilations b)
         (setq immediate-compensation-handler-compilation-if-any
               (first (g2gl-compensation-handler-compilations b))))
        (t
         (setq immediate-compensation-handler-compilation-if-any nil)))
      (cond
        (immediate-compensation-handler-compilation-if-any
         (setq outside-variables
               (compilations-of-outside-variables-used-in-body
                 immediate-compensation-handler-compilation-if-any)))
        (t
         (setq outside-variables nil)))
      (when (or immediate-compensation-handler-compilation-if-any
                (normal-completions-of-nested-compilations thread))
        (record-normal-completion-of-nested-compilation
          parent-thread
          (when parent-thread (activity-compilation-to-execute parent-thread))
          outside-variables
          (normal-completions-of-nested-compilations thread)
          f)
        (setf (normal-completions-of-nested-compilations thread) nil)))

    (when (not has-surviving-sibling)
      (reclaim-normal-completions
        (normal-completions-of-nested-compilations thread))
      (setq outside-variable-bindings
            (outside-variable-bindings-for-execution thread))
      (when (and outside-variable-bindings
                 (or (null parent-thread)
                     (not (eq (outside-variable-bindings-for-execution
                                parent-thread)
                              outside-variable-bindings))))
        (swap-values-of-outside-variable-bindings thread)
        (reclaim-outside-variable-bindings outside-variable-bindings)
        (when (and parent-thread
                   (outside-variable-bindings-for-execution parent-thread))
          (swap-values-of-outside-variable-bindings
            (outside-variable-bindings-for-execution parent-thread))))

      ;; this is the unbinding point:

      ;; iterate through vc's of body compilation used to execute of thread:

      ;; if a partner link vc:
      ;;   if the value nil, do nothing,
      ;;   else: it's a g2gl-service-port instance
      ;;     this end and the other end (they're interlinked) should be reclaimed
      ;;     set g2gl-partner-link-variable in the other process to nil
      ;;     no need to set this one to nil

      ;; for each variable bound by the body compilation that's being exited
      ;;  that might have a value that needs reclaiming, check for such a value
      ;;  (a "boxed number" or string, say) and reclaim as appropriate [perhaps
      ;;  to avoid having always to look through all the variables, there could
      ;;  be, as an optimization, a list of such variables kept in the sibling
      ;;  threads)
      (loop with vvv = (g2gl-variable-values-vector f)
            for vc in (g2gl-variable-compilations
                        (body-compilation-this-is-being-used-to-execute
                          thread))
            as i fixnum = (g2gl-variable-index vc)
            as old-value = (managed-svref vvv i)
            when old-value
              do (setf (managed-svref vvv i) nil) ; see note! (MHD 3/29/05)
                 (reclaim-g2gl-variable-managed-value old-value vc)))

    (setf (g2gl-execution-threads f)
          (delete-gensym-element thread (g2gl-execution-threads f)))
    (when (threads-ready-to-run-after-pause f)
      (setf (threads-ready-to-run-after-pause f)
            (delete-gensym-element
              thread (threads-ready-to-run-after-pause f))))
    (reclaim-g2gl-execution-thread thread)
    has-surviving-sibling))

;; Setting the vector entry to nil, although not in spec, is necessary because,
;; otherwise, subsequent calls to set-value-of-g2gl-variable might encounter the
;; value, and would reclaim it (again)!  The spec does say to reclaim old values
;; encountered at the old position, so there or here we've got to do
;; something. Review with LH! (MHD 3/29/05)




;;; Make-G2GL-thread-token (execution-thread thread):
;;;
;;; This determines the desired class, color, and label for a new thread token,
;;; using get-g2gl-thread-token-property-value.  The class and color are checked
;;; to ensure they are valid.  If they are not, appropriate substitutions are
;;; made.  The class must be a subclass of object, and be allowed to be
;;; transient.  The color must be a valid color or metacolor, as determined by
;;; color-or-metacolor-p.  If either color or class are inappropriate, a warning
;;; message of level 2 is given, and a substitution is made, using the default
;;; initial value for the color and class in the G2GL-parameters table.
;;; Otherwise, instance is created, using make-entity with the :no-stubs option,
;;; i.e., this is careful to create just the icon, and not any connection stubs.

(defun make-g2gl-thread-token (thread)
  (let* ((class (get-g2gl-thread-token-property-value thread 'class))
         (default-thread-token-class        ; have parameter or memoize this?
           (get-slot-init-form 'g2gl-parameters 'default-thread-token-class))
         (default-thread-token-color        ; ditto.
           (get-slot-init-form 'g2gl-parameters 'default-thread-token-color))
         (required-parent-class 'object)
         (label? (get-g2gl-thread-token-property-value thread 'label))
         (color (get-g2gl-thread-token-property-value thread 'color))
         (class-description? (class-description class))
         (class-frame? (get-instance-with-name-if-any 'class-definition class))
         (class-problem-string?
           ;; Much of the code for class checking borrowed from
           ;; create-action-internal -- abstract!!  Also, review whether all the
           ;; checks are appropriate for this application! (MHD 4/7/05)
           (cond
             ((null class-description?)
              (tformat-text-string "~a is not a defined class." class))
             ((not (class-can-be-transient-p class-description?))
              (if (subclassp class 'item)
                  (tformat-text-string
                    "Attempted to create an instance of ~a, but this class ~
                     is not allowed to be created transiently."
                    class)
                  (tformat-text-string "~a is not a defined class." class)))
             ((get-class-feature-in-class-description-if-any
                class-description? 'not-user-instantiable)
              (tformat-text-string
                "An instance of ~a cannot be created because it is either ~
          an abstract class or the instantiate attribute on its ~
          class-definition is set to `no'."
                ;; -- spelling of instantiate corrected here (for G2GL), not in
                ;; orig! (MHD 4/7/05)
                class))
             ((and class-frame? (transient-p class-frame?))
              (tformat-text-string
                "Cannot create an instance of ~a. This definition is transient."
                class))
             ((not (class-description-of-class-p
                     class-description? required-parent-class))
              (tformat-text-string
                "The class ~a is not a subclass of ~a."
                class required-parent-class))))
         (color-problem-string?
           (if (not (color-or-metacolor-p color))
               (tformat-text-string "~a is an illegal color" color)))
         entity)
    (when class-problem-string?
      (warn-of-invalid-g2gl-thread-token-class
        class-problem-string? class default-thread-token-class thread)
      (reclaim-text-string class-problem-string?)
      (setq class default-thread-token-class))
    ;; Now, entity can be assumed to be instantiable.
    (when color-problem-string?
      (warn-of-invalid-g2gl-thread-token-color
        color-problem-string? color default-thread-token-color thread)
      (reclaim-text-string color-problem-string?)
      (setq color default-thread-token-color))
    ;; Now, color can be assumed to be a legal color (or metacolor).
    (setq entity (make-entity class :no-stubs))
    (change-color-of-icon entity nil color)
    (when label?
      ;; if there's a label, display it to the left of the entity as if it were
      ;; the name of a G2GL variable:
      (let ((name-box (make-name-box entity)))
        (replace-text-with-text-string-in-text-box
          (if (symbolp label?)
              (symbol-name-text-string label?)
              label?)                        ; must be a text string
          name-box)
        (shift-block-to
          name-box
          (-w (left-edge-of-block entity) (width-of-block name-box))
          (halfw
            (-w (+w (top-edge-of-block entity) (bottom-edge-of-block entity))
                (height-of-block name-box))))))
    entity))

;; Note: this has at least one known bug: if the class is user defined, it could
;; be deleted, causing all instances to be automatically deleted out from under
;; G2GL, which doesn't currently handle it.  this might want to be changed to
;; create system-defined instances that just show a given class's icon
;; description, and thus be insulated from such an event. Fix!! (MHD 4/8/05)






;;; `Warn-of-invalid-g2gl-thread-token-class' ...

(defun warn-of-invalid-g2gl-thread-token-class
    (class-problem-string? class default-thread-token-class thread)
  (warning-message* 2
    "~a~%Substituting class ~a for ~a in execution display for ~NF."
    class-problem-string?
    default-thread-token-class
    class
    (source-g2gl-process
      (parent-compilation-version (parent-execution-frame thread)))))






;;; `Warn-of-invalid-g2gl-thread-token-color' ...

(defun warn-of-invalid-g2gl-thread-token-color
    (color-problem-string? color default-thread-token-color thread)
  (warning-message* 2
    "~a~%Substituting color ~a for ~a in execution display for ~NF."
    color-problem-string?
    default-thread-token-color
    color
    (source-g2gl-process
      (parent-compilation-version (parent-execution-frame thread)))))





;;; Get-G2GL-thread-token-property-value
;;;   (execution-thread thread,
;;;    thread-token-property-name property-name):

(defun get-g2gl-thread-token-property-value (thread property-name)
  ;; Note: even though this provides an operation involving "property names",
  ;; the storage is on alists.  This looks in more than one alist until it finds
  ;; one with an entry for the property.  If there's an entry that has nil as
  ;; its cdr ("value"), it's considered to have that property, and nil is
  ;; returned (as opposed to searching in the next alist).
  (let ((entry?
          (or (assq property-name
                    (thread-token-properties thread))
              (assq property-name
                    (thread-token-properties-for-g2gl-process
                      (source-g2gl-process
                        (parent-compilation-version
                          (parent-execution-frame thread))))))))
    (if entry?
        (cdr entry?)
        (case property-name
          (class (default-thread-token-class g2gl-parameters))
          (color (default-thread-token-color g2gl-parameters))))))






;;; Position-thread-tokens-above-activity-to-execute
;;;   (execution-thread-with-execution-display thread):

(defun position-thread-tokens-above-activity-to-execute (thread)
  (let* ((vector (vector-of-g2gl-body-elements
                   (first (g2gl-execution-displays thread))))
         (edo (managed-svref
                vector
                (g2gl-body-element-index
                  (activity-compilation-to-execute thread))))
         ;; logic for "hack" case missing here!
         x y)
    #+development
    (when (null edo)
      (cerror "continue anyhow" "EDO here should not be nil!"))
    (setq x (halfw (+w (left-edge-of-block edo) (right-edge-of-block edo))))
    (setq y
          (-w (-w (top-edge-of-block edo)
                  (g2gl-activity-elbow-room g2gl-parameters))
              (halfw (height-of-block
                       (first (thread-tokens-for-execution-displays thread))))))
    ;; -- (x, y) is now a thread token position directly above the center of edo
    ;; and separated from edo by the G2GL-activity-elbow-room of the G2GL system
    ;; table

    ;; -- now see if other threads are around there already, so we can shift new
    ;; ones over a bit:
    (multiple-value-setq (x y) (adjust-thread-token-x-y thread x y))

    (move-thread-tokens thread x y)))


;;; The function `adjust-thread-token-x-y' is a helper function of
;;; position-thread-tokens-above-activity-to-execute.  It tries to adjust the
;;; (x, y) position presumed to be the position for the next thread token
;;; centered over the next activity, and adjusts it heuristically (and not
;;; necessarily efficiently) to not overlap with others that already were to be
;;; placed at the same position, returning a suggested better (x, y) position as
;;; two values: new-x and new-y.

(defun adjust-thread-token-x-y (thread x y)
  (loop with d = (first (g2gl-execution-displays thread))
        with class = (get-g2gl-thread-token-property-value thread 'class)
        for b being each subblock of d
        when (and (frame-of-class-p b class)
                  (=w (midline-y-of-block b) y))
          collect b
            into others-for-same-position using gensym-cons
        finally
          (return
            (loop with x-try = x
                  while
                  (loop
                    for b in others-for-same-position
                    when (=w x-try (midline-x-of-block b))
                      do (incfw x-try (width-of-block b))
                         (return t))
                  finally
                    (reclaim-gensym-list others-for-same-position)
                    (return (values x-try y))))))

;; The above is not very efficient, but should practically not be any kind of
;; issue until rather huge activity flowcharts get built and used with tracing.
;; The above is not in the spec, but has been discussed and approved, and
;; probably this or similar will be a planned addition, pending a more
;; efficient, well-engineered solution. (MHD 3/20/05)










;;; Set-up-transition-from-predecessor-activity-compilation
;;;   (execution-thread-with-execution-display thread,
;;;    predecessor-activity-compilation predecessor-c
;;;    go-directly-to-final-position go-directly-to-final-position):
;;;
;;; Note: the G2GL-execution-displays of thread must be non-nil when this is
;;; invoked.

(defun set-up-transition-from-predecessor-activity-compilation
    (thread predecessor-c go-directly-to-final-position)
  #+development
  (when (null (g2gl-execution-displays thread))
    (cerror "continue anyway (crash)"
            "No execution displays in thread ~s~
             ~%  when calling set-up-transition-from-predecessor-activity-compilation.~
             ~%  This is an invalid condition, and the code cannot work in this case."
            thread))
  ;; -- MHD: there had been a bug in delete-g2gl-execution-thread leading to the
  ;; above, fixed now, but keep in guard in development for now. (MHD 1/26/05)
  (let* ((vector (vector-of-g2gl-body-elements
                   (first (g2gl-execution-displays thread))))
         ;; Note: I believe the next two have alternative code to get their
         ;; bindings in the "hack" display case. (MHD 1/20/05)
         (predecessor-edo
           (managed-svref vector (g2gl-body-element-index predecessor-c)))
         (edo
           (managed-svref
             vector
             (g2gl-body-element-index
               (activity-compilation-to-execute thread))))
         (connection
           ;; Get the out connection of predecessor-edo that's an in connection
           ;; of edo:  (presumably there's only one)
           (loop for oc being each output-connection of predecessor-edo
                 thereis (loop for ic being each input-connection of edo
                               when (eq ic oc)
                                 return ic)))
         (representative-thread-token
           (first (thread-tokens-for-execution-displays thread)))
         (step-positions
           (compute-connection-tracing-step-positions
             connection
             (halfw
               (maxw (width-of-block representative-thread-token)
                     (height-of-block representative-thread-token)))))
         x y)
    (when go-directly-to-final-position
      (loop while (cdr step-positions)
            do (gensym-pop step-positions)))
    (setq x (car (first step-positions)))
    (setq y (cdr (first step-positions)))
    (reclaim-gensym-cons (gensym-pop step-positions))
    (when step-positions
      (setf (execution-thread-state thread) 'in-transit)
      (setf (execution-thread-state-parameter thread) step-positions))
    (move-thread-tokens thread x y)))



;;; Compute-connection-tracing-step-positions
;;;   (connection connection, thread-token-radius thread-token-radius):
;;;
;;; This returns a list of coordinate-pair step positions along connection,
;;; where (a) the distance between successive step positions is the
;;; mini-tracing-step-size of the G2GL system table, (b) the first step position
;;; is no closer to the input end object than end-space, that is, the
;;; G2GL-activity-elbow-room of the G2GL system table plus thread-token-radius,
;;; and (c) the last step position is exactly end-space distant from the output
;;; end object, except that, if connection is not long enough for even one step
;;; position that satisfies these constraints, this returns a list of just one
;;; position halfway along connection.

;;; Note: in the diagonal connection case, this does mixed integer and floating
;;; point arithmetic, generating garbage floating point numbers that need to be
;;; reclaimed.  For efficiency, this wraps all its work in one big temporary
;;; float consing wrapper.  If too many floating point operations are done
;;; within such a context, this area could potentially overflow.  This amount is
;;; bound roughly by the number of connection deltas.  A "reasonable" number can
;;; clearly be handled by this function.  However, since there's no
;;; reasonablness checking elsewhere, for safety reasons, therefore, this
;;; handles only a "reasonable" number of connection deltas, as defined by the
;;; constant `maximum-number-of-deltas-for-tracing-step-positions', which is
;;; defined as 100.

(defconstant max-deltas-for-tracing-step-positions 100)

(defun compute-connection-tracing-step-positions (connection thread-token-radius)
  (with-temporary-gensym-float-creation
      compute-connection-tracing-step-positions
    (let* ((diagonal (connection-diagonal-p connection))
           (end-space
             (+w (g2gl-activity-elbow-room g2gl-parameters)
                 thread-token-radius))
           (step-size (mini-tracing-step-size g2gl-parameters))
           (deltas (get-full-deltas-for-connection ; all fixnums
                     connection max-deltas-for-tracing-step-positions))
           (length-of-connection        ; diagonal case: float, else fixnum
             (if (not diagonal)
                 (loop for delta fixnum in deltas sum (absf delta))
                 (diagonal-connection-length-from-full-deltas deltas)))
           (length-for-steps                ; diagonal case: float, else fixnum
             (- (- length-of-connection end-space) end-space))
           n                                ; fixnum after the following:
           (step-to-go                        ; diagonal case: float, else fixnum
             (cond
               ((>= length-for-steps 0)
                (setq n (floor length-for-steps step-size))
                (- (- length-of-connection end-space)
                   (*f n step-size)))
               (t
                (setq n 0)
                (if diagonal
                    (/e length-of-connection 2.0)
                    (halff length-of-connection)))))
           (in-object (input-end-object connection))
           (input-end-pos (input-end-position connection))
           (side (get-side-given-end-position input-end-pos))
           (position (get-position-on-side-given-end-position input-end-pos))
           (x (+w (left-edge-of-block in-object)
                  (or (case side (left 0) (right (width-of-block in-object)))
                      position)))
           (y (+w (top-edge-of-block in-object)
                  (or (case side (top 0) (bottom (height-of-block in-object)))
                      position)))
           (horizontal (case side ((left right) t) (t nil)))
           (remaining-deltas deltas)
           (leg-to-go 0)
           (step-positions-in-reverse-order nil))
      (cond
        ((not diagonal)
         (loop with hop
               while (>=f n 0)
               do (when (=w leg-to-go 0)
                    (setq leg-to-go (absw (first remaining-deltas))))
                  (setq hop (minw step-to-go leg-to-go))
                  (when (<w (first remaining-deltas) 0)
                    (setq hop (-w hop)))
                  (if horizontal
                      (setq x (+w x hop))
                      (setq y (+w y hop)))
                  (cond
                    ((>w leg-to-go step-to-go)
                     (setq leg-to-go (-w leg-to-go step-to-go))
                     (setq step-to-go step-size)
                     (setq step-positions-in-reverse-order
                           (gensym-cons-macro
                             (gensym-cons-macro x y)
                             step-positions-in-reverse-order))
                     (decff n))
                    (t
                     (setq step-to-go (-w step-to-go leg-to-go))
                     (pop remaining-deltas)
                     (setq leg-to-go 0)
                     (setq horizontal (not horizontal))))))
        (t                                ; diagonal is true
         (loop ;; the following initial values are type-matched but arbitrary
              with delta-x fixnum = 0
              with delta-y fixnum = 0
              with leg-length gensym-float = 0.0
              with leg-fraction-to-go gensym-float = 0.0
              with xs fixnum = 0
              with ys fixnum = 0
              while (>=f n 0)
              do (when (= leg-to-go 0)
                   (cond
                     (horizontal
                      (setq delta-x (first-of-cons remaining-deltas))
                      (setq delta-y (second-of-cons remaining-deltas)))
                     (t
                      (setq delta-y (first-of-cons remaining-deltas))
                      (setq delta-x (second-of-cons remaining-deltas))))
                   (setq remaining-deltas (cddr-of-cons remaining-deltas))
                   (setq x (+w x delta-x))
                   (setq y (+w y delta-y))
                   (setq leg-length
                         (sqrte
                           (+e (expt (coerce-fixnum-to-gensym-float delta-x) 2)
                               (expt (coerce-fixnum-to-gensym-float delta-y) 2))))
                   (setq leg-to-go leg-length))
                 (cond
                   ((> leg-to-go step-to-go)
                    (setq leg-to-go (- leg-to-go step-to-go))
                    (setq step-to-go step-size)
                    (setq leg-fraction-to-go
                          (/e (coerce-to-gensym-float leg-to-go)
                              leg-length))
                    (setq xs
                          (round
                            (-e (coerce-fixnum-to-gensym-float x)
                                (*e leg-fraction-to-go
                                    (coerce-fixnum-to-gensym-float delta-x)))))
                    (setq ys
                          (round
                            (-e (coerce-fixnum-to-gensym-float y)
                                (*e leg-fraction-to-go
                                    (coerce-fixnum-to-gensym-float delta-y)))))
                    (setq step-positions-in-reverse-order
                          (gensym-cons-macro
                            (gensym-cons-macro xs ys)
                            step-positions-in-reverse-order))
                    (decff n))
                   (t
                    (setq step-to-go (- step-to-go leg-to-go))
                    (setq leg-to-go 0))))))
      (reclaim-gensym-list-macro deltas)
      (nreverse step-positions-in-reverse-order))))

;; Find out what the real practical limit is for each implementation, i.e.,
;; currently, in Chestnut, and set max-deltas-for-tracing-step-positions
;; accordingly. Also, figure out other factors that can affect the amount of
;; float consing, especially step size, i.e., (mini-tracing-step-size
;; g2gl-parameters). (MHD 1/24/05)







;;; Move-thread-tokens
;;;   (execution-thread thread,
;;;    left-edge left-edge,
;;;    top-edge top-edge):
;;;
;;;
;;; It can be assumed here that thread tokens to be moved are not currently on a
;;; superblock and thus do not need to be erased or redrawn.

(defun move-thread-tokens (thread left-edge top-edge)
  (loop for h in (thread-tokens-for-execution-displays thread)
        do (shift-block
             h
             (-w left-edge (midline-x-of-block h))
             (-w top-edge (midline-y-of-block h)))))





;;; Add-thread-tokens-to-execution-displays (execution-thread thread):

(defun add-thread-tokens-to-execution-displays (thread)
  (loop for d in (g2gl-execution-displays thread)
        as h in (thread-tokens-for-execution-displays thread)
        do (add-to-workspace
             h d (left-edge-of-block h) (top-edge-of-block h) t)))





;;; Remove-thread-tokens-from-execution-displays (execution-thread thread):

(defun remove-thread-tokens-from-execution-displays (thread)
  (loop for d in (g2gl-execution-displays thread) ; corresponding lists
        as h in (thread-tokens-for-execution-displays thread)
        do (erase-images-of-block h nil)
           (remove-as-subblock-if-necessary h)))





;;; Remove-execution-display-from-thread
;;;   (execution-thread thread,
;;;    execution-display-for-this-thread d):
;;;
;;; Note that the thread token corresponding to d is deleted, and therefore
;;; removed from d, but that d is never herein deleted.

(defun remove-execution-display-from-thread (thread d)
  (let* ((i (position d (g2gl-execution-displays thread)))
         (thread-token-for-d
           (nth i (thread-tokens-for-execution-displays thread))))

    (delete-frame thread-token-for-d)

    ;; The following removes and reclaims the Ith cons of the lists in the
    ;; g2gl-execution-displays and
    ;; thread-tokens-for-execution-displays slots of thread:
    (cond
      ((>f i 0)
       (let* ((j (1-f i))
              (trailing-cons-1
                (nthcdr-macro j (g2gl-execution-displays thread)))
              (trailing-cons-2
                (nthcdr-macro
                  j (thread-tokens-for-execution-displays thread))))
         (reclaim-gensym-cons-macro
           (prog1 (cdr trailing-cons-1) (pop (cdr trailing-cons-1))))
         (reclaim-gensym-cons-macro
           (prog1 (cdr trailing-cons-2) (pop (cdr trailing-cons-2))))))
      (t
       (reclaim-gensym-cons-macro
         (prog1 (g2gl-execution-displays thread)
           (pop (g2gl-execution-displays thread))))
       (reclaim-gensym-cons-macro
         (prog1 (thread-tokens-for-execution-displays thread)
           (pop (thread-tokens-for-execution-displays thread))))))

    (when (and (null (g2gl-execution-displays thread))
               (eq (execution-thread-state thread) 'in-transit))
      (bypass-transition-to-activity-compilation thread))))





;;; Bypass-transition-to-activity-compilation (execution-thread-in-transit thread):
;;;
;;; This is called when (execution-thread-state-parameter thread) is a list of
;;; the form
;;;
;;;   ( { left-edge top-edge }+
;;;     [ link-status link-name ] )  ; if predecessor is a flow signal
;;;
(defun bypass-transition-to-activity-compilation (thread)
  (setf (execution-thread-state thread) nil)
  (let* ((parameter (execution-thread-state-parameter thread)))
    (setf (execution-thread-state-parameter thread) nil)
    (loop as (x y . tail) on parameter by 'cddr
          when (and tail (symbolp (car tail)))
            do (setf (execution-thread-state thread) (first tail))
               (setf (execution-thread-state-parameter thread) (second tail))
               (unschedule-g2gl-execution-thread thread)
               (return))
    (reclaim-gensym-list parameter)))





;;;; Display, Debugging, Tracing, and Animation Facilities



;;; Make-and-put-up-individual-execution-display-if-necessary
;;;   (execution-thread thread):

(defun make-and-put-up-individual-execution-display-if-necessary (thread)
  (when (or (null (g2gl-execution-displays thread))
            (eq (execution-display-mode
                  (first (g2gl-execution-displays thread)))
                'superimposed-tracings))
    (make-and-put-up-execution-display thread nil)))







;;; The parameter `prefer-buffered-drawing-for-g2gl-execution-displays?' is for
;;; now an internal parameter, controlling whether or not to make execution
;;; displays have their prefer-buffered-drawing slot set to true.  It's on by
;;; default, but it can be changed in development or may be changed some other
;;; ways in the future to allow experimentation.  Ultimately, this might want to
;;; be a user parameter, i.e., part of g2gl-parameters.

(defparameter prefer-buffered-drawing-for-g2gl-execution-displays? t)




;;; The function `make-entity-for-execution-display' makes an entity
;;; corresponding to an activity compilation c for the purpose of displaying on
;;; an execution display.

(defun-simple make-entity-for-execution-display (c)
  (let ((entity (make-entity (map-g2gl-activity-code-to-class
                               (g2gl-activity-class-code c))
                             :no-stubs)))
    (delete-all-attribute-displays entity)
    (loop for adc in (g2gl-attribute-display-compilations c) do
      (add-to-g2gl-object
        (make-fake-attribute-display-for-execution-display adc)
        entity (g2gl-attribute-display-position adc)))
    entity))


;;; The function `make-fake-attribute-display-for-execution-display' returns a
;;; new table containing text cells containing copies of the texts in the rows
;;; of g2gl-attribute-display-compilation adc.  The table is formatted to look
;;; like an attribute display, but it is not "live" and has no connections to
;;; any actual frame slot values.

(defun-simple make-fake-attribute-display-for-execution-display (adc)
  (make-or-reformat-table
    (nconc
      (when (g2gl-attribute-display-table-header adc)
        (slot-value-list
          (slot-value-list
            nil
            (make-text-cell
              (copy-text (g2gl-attribute-display-table-header adc))
              'attribute-display-class-format))))
      (loop for (text1 . text2) in (g2gl-attribute-display-rows adc)
            collect
            (slot-value-cons
              (when text1
                (make-text-cell
                  (copy-text text1) 'attribute-display-description-format))
              (when text2
                (slot-value-list
                  (make-text-cell
                    (copy-text text2) 'attribute-display-value-format))))
              using slot-value-cons))
    'attribute-display-table-format nil))




;;; Make-and-put-up-execution-display
;;;   (execution-thread thread,
;;;    execution-display-mode mode):
;;;
;;; Additional optional arg: miniatureize. If this this is true, the display is
;;; made small (1/4 scale) and stacked neatly in the upper left corner.

(defun make-and-put-up-execution-display (thread mode &optional miniatureize)
  (let* (d b g a e f parent-thread)
    (setq d (make-workspace 'g2gl-execution-display))
    (when prefer-buffered-drawing-for-g2gl-execution-displays?
      (setf (prefer-buffered-drawing d) t))
    (setq b (body-compilation-this-is-being-used-to-execute thread))
    (setf (one-execution-thread-that-is-shown-hereon d) thread)
    (setf (execution-display-mode d) mode)
    (setf (temporary-breakpoints-for-execution-display d) nil)
    ;; to hold references to G2GL variables and G2GL activities:
    (setf (vector-of-g2gl-body-elements d)
          (allocate-managed-array (next-body-element-index-to-assign b)))
    (add-title-to-execution-display
      thread mode
      (g2gl-execution-display-title-position b)
      d)
    (loop for c in (g2gl-variable-compilations b)
          when (g2gl-var-body-element-index c)
            ;; null test to make sure that it is not a proxy variable
            do (setq g (make-entity
                         (map-g2gl-variable-code-to-class
                           (g2gl-variable-class-code c))
                         :no-stubs))
              ;; Note: separately, g2gl-variable name-or-names-for-frame are
              ;; defined to display their names to their left, and to not
              ;; include their names in the global directory of names.  The
              ;; following call gets the name box set up correctly:
               (change-g2gl-variable-name g (c-g2gl-variable-name c))
               (add-to-g2gl-body g d (g2gl-var-body-element-position c))
               (setf (managed-svref
                       (vector-of-g2gl-body-elements d)
                       (g2gl-var-body-element-index c))
                     g))
    (loop for c in (g2gl-fault-handler-compilations b)
          do (setq a (make-entity-for-execution-display c))
             (add-to-g2gl-body a d (g2gl-body-element-position c))
             (setf (managed-svref
                     (vector-of-g2gl-body-elements d)
                     (g2gl-body-element-index c))
                   a))
    (loop for c in (g2gl-compensation-handler-compilations b)
          do (setq a (make-entity-for-execution-display c))
             (add-to-g2gl-body a d (g2gl-body-element-position c))
             (setf (managed-svref
                     (vector-of-g2gl-body-elements d)
                     (g2gl-body-element-index c))
                   a))
    (loop for c in (g2gl-event-handler-compilations b)
          do (setq a (make-entity-for-execution-display c))
             (add-to-g2gl-body a d (g2gl-body-element-position c))
             (setf (managed-svref
                     (vector-of-g2gl-body-elements d)
                     (g2gl-body-element-index c))
                   a))
    (loop for c in (g2gl-text-box-compilations b)
          do (setq e (make-text-box
                       (class-of-g2gl-text-box c)))
             (change-slot-value
               e 'box-translation-and-text
               (slot-value-cons
                 no-value
                 (copy-text (text-of-g2gl-text-box c))))
             (add-to-g2gl-body e d (g2gl-body-element-position c)))
    (add-flowchart-activities-to-execution-display
      (flowchart-entry-activity-compilation b)
      (out-connection-representation-stream b)
      0 d)
    (setq f (parent-execution-frame thread))
    (setq parent-thread (parent-execution-thread thread))
    (cond
      ((not (eq mode 'superimposed-tracings))
       (loop for related-thread in (g2gl-execution-threads f)
             when (eq parent-thread
                      (parent-execution-thread related-thread))
               do (show-thread-on-execution-display related-thread d))
       (loop for vc in (g2gl-variable-compilations b)
             do (update-g2gl-variable-value-display vc thread))
       (reflect-if-paused-on-execution-display d f))
      (t                                ; mode is SUPERIMPOSED-TRACINGS
       (loop for execution-frame
                 in (current-execution-frames (parent-compilation-version f))
             do (loop for related-thread
                          in (g2gl-execution-threads execution-frame)
                      when (eq parent-thread
                               (parent-execution-thread related-thread))
                        ;; change 3/19/05: the way to tell if two threads are
                        ;; siblings is to compare parents (not being on same
                        ;; body). (LH/MHD 3/15/05)
                        do (show-thread-on-execution-display
                             related-thread d)))
       ;; store frame serial number (or item reference)?!
       (setf (execution-display-for-superimposed-tracings b) d)))

    ;; Put up d on the window specified by
    ;; name-of-window-for-G2GL-execution-displays. If there's no name, put
    ;; workspace on all active (logged in) workstation windows.  Consider having
    ;; this parameter be "name-or-class", similar to the G2-window attribute and
    ;; the -window-name command line argument, but in this case, all matching
    ;; windows of the class or having the specified name, would get the
    ;; workspace. (MHD 1/19/05)
    (let* (name g2-window gensym-window pane workstation)
      (cond
        ((setq name (name-of-window-for-g2gl-execution-displays
                      g2gl-parameters))
         (cond
           ((and (setq g2-window
                       (get-instance-with-name-if-any 'g2-window name))
                 (setq gensym-window
                       (map-g2-window-to-gensym-window g2-window))
                 (setq workstation
                       (workstation-this-is-on gensym-window))
                 (logged-in-workstation-session-p workstation)
                 ;; if mapped, we assume it's logged in; other checks?!
                 (setq pane ; nec. to check?
                       (detail-pane gensym-window)))
            (for-workstation (workstation)
              (if miniatureize
                  (put-workspace-on-pane
                    d pane 'left 'top #.(round (normalized-scale) 4))
                  (put-workspace-on-pane d pane nil nil t))))
           (t
            (notify-user
              "No window with name ~a is available to show the execution ~
      display for ~NF.  Change the name-of-window-for-g2gl-execution-displays ~
      of g2gl-parameters to 'none' to show the display on all ~
      windows, or, if desired, disable execution displays for ~NF by ~
      changing its individual-execution-display-mode attribute to none."
              name
              (source-g2gl-process (parent-compilation-version f))
              (source-g2gl-process (parent-compilation-version f))))))
        (t
         (loop with gensym-window
               with pane
               for workstation in workstations-in-service
               when (logged-in-workstation-session-p workstation)
                 do (setq gensym-window (window-for-workstation workstation))
                    (when (setq pane    ; nec. to check?
                                (detail-pane gensym-window))
                      (for-workstation (workstation)
                        (if miniatureize
                            (put-workspace-on-pane
                              d pane 'left 'top #.(round (normalized-scale) 4))
                            (put-workspace-on-pane d pane nil nil t))))))))
    d))





;;; Add-title-to-execution-display
;;;   (execution-thread thread, execution-display-mode mode,
;;;    G2GL-body-position p, execution-display d):
;;;
;;; The title this produces might read something like "a scope named undo-commit
;;; within a fault handler within the loan-approval BPEL-process, version 2" or
;;; "superimposed tracings of the loan-approval BPEL-process, version 2".

(defun add-title-to-execution-display (thread mode p d)
  (let* (ancestor-of-thread
          c activity-class-code activity-class v s
          name-or-names
          title
          text)
    (setq
      text
      (twith-output-to-text
        ;; Variables current-wide-string and fill-pointer-for-current-wide-string
        ;; available in the following body:
        (when (eq mode 'superimposed-tracings)
          (twrite "superimposed tracings of "))
        (setq ancestor-of-thread (parent-execution-thread thread))
        (loop while ancestor-of-thread doing
          (setq c (activity-compilation-to-execute ancestor-of-thread))
          (setq activity-class-code (g2gl-activity-class-code c))
          (setq activity-class (map-g2gl-activity-code-to-class activity-class-code))
          (twrite
            (cond
              ((=f activity-class-code
                   (quoted-g2gl-activity-class-code g2gl-scope))
               "a scope")
              ((=f activity-class-code
                   (quoted-g2gl-activity-class-code g2gl-fault-handler))
               "a fault handler")
              ((=f activity-class-code
                   (quoted-g2gl-activity-class-code g2gl-compensation-handler))
               "a compensation handler")
              ((class-code-for-g2gl-event-handler-activity-p
                 activity-class-code)
               "an event handler")
              (t
               #+development
               (cerror "continue, using empty string"
                       "No string to match class/code ~a/~d"
                       activity-class activity-class-code)
               "")))
          (when (g2gl-activity-name c)
            (twrite " named ")
            (twrite (g2gl-activity-name c)))
          (twrite " within ")
          (setq ancestor-of-thread (parent-execution-thread ancestor-of-thread)))
        (setq v (parent-compilation-version (parent-execution-frame thread)))
        (setq s (source-g2gl-process v))
        (twrite "the ")
        (setq name-or-names (name-or-names-for-frame s))
        (when name-or-names
          (twrite (if (atom name-or-names) name-or-names (first name-or-names)))
          (twrite " "))
        (twrite (class s))
        (twrite ", version ")
        (twrite (compilation-version-number v))))
    (setq title (make-text-box 'g2gl-execution-display-title))
    (change-slot-value
      title 'box-translation-and-text (slot-value-cons no-value text))
    (let* (x y p2)
      (setq x (get-x-from-g2gl-body-position p))
      (setq y (get-y-from-g2gl-body-position p))
      ;; move title's bottom-left corner at (x, y):
      (incfw y (-w (height-of-block title)))
      (setq p2 (make-g2gl-body-position x y))
      (add-to-g2gl-body title d p2)
      (reclaim-g2gl-body-position p2))))



;;; Add-flowchart-activities-to-execution-display
;;;   (flowchart-activity-compilation c,
;;;    out-connection-representation-stream stream,
;;;    stream-index j0, execution-display d):

(defun add-flowchart-activities-to-execution-display (c stream j0 d)
  (let* ((a (make-entity-for-execution-display c))
         successors)
    (when (g2gl-activity-name c)
      ;; The name should (per the spec) appear to the left of the icon.
      ;; Currently, it's placed heuristically -- to the left if a connection is
      ;; in the way below and to the right, but normally below (or to the
      ;; right).  G2 needs a way to make such a specification easy.  Also, the
      ;; spec says the name should not be included in any directory of names --
      ;; that's done now via a slot feature declared in the class definition.
      (change-slot-value
        a 'name-or-names-for-frame
        (g2gl-activity-name c)))
    (add-to-g2gl-body
      a d (g2gl-body-element-position c))
    (setf (managed-svref
            (vector-of-g2gl-body-elements d)
            (g2gl-body-element-index c))
          a)
    (when (and (setq successors (activity-compilation-successors c))
               (null (first successors)))
      (pop successors))
    (loop with j = j0
          with a-successor
          for c-successor in successors
          as i = (g2gl-body-element-index c-successor)
          do (when (null (setq a-successor
                               (managed-svref
                                 (vector-of-g2gl-body-elements d)
                                 i)))
               (setq j
                     (add-flowchart-activities-to-execution-display
                       c-successor stream j d))
               (setq a-successor
                     (managed-svref
                       (vector-of-g2gl-body-elements d)
                       i)))
             (setq j
                   (connect-flowchart-activities-on-execution-display
                     a a-successor stream j))
          finally
            (shrink-wrap-workspace d)
            (return j))))




;;; Connect-flowchart-activities-on-execution-display
;;;   (input-end-activity input-end-activity,
;;;    output-end-activity output-end-activity,
;;;    out-connection-representation-stream stream,
;;;    stream-index j0):

(defun connect-flowchart-activities-on-execution-display
    (input-end-activity output-end-activity stream j0)
  (let* ((u16-stream-p (wide-string-p stream))
         (stream-length
           (if u16-stream-p
               (wide-string-length stream)
               (managed-array-length stream)))
         (delta-offset
           (if u16-stream-p
               #.(* 3 (expt 2 14))
               #.(* 3 (expt 2 26))))
         (j j0)
         (input-end-position
           ;; To do: does not yet handle the case where this element is offset
           ;; by 2^14 to indicate that the connection is straight and orthogonal
           ;; and that there is no specification of the G2 output end position!
           (prog1 (if u16-stream-p
                      (wide-character-code (charw stream j))
                      (managed-svref stream j))
             (incff j)))
         (output-end-position
           (prog1 (if u16-stream-p
                      (wide-character-code (charw stream j))
                      (managed-svref stream j))
             (incff j)))
         (diagonal
           (if (>=f output-end-position #.(expt 2 14))
               (progn
                 (decff output-end-position #.(expt 2 14))
                 t)))
         offset-delta
         (delta-or-deltas
           (loop while (and (<f j stream-length)
                            (>=f (setq offset-delta
                                       (if u16-stream-p
                                           (wide-character-code
                                             (charw stream j))
                                           (managed-svref stream j)))
                                 #.(expt 2 15)))
                 collect (-f offset-delta delta-offset)
                   into deltas
                   using slot-value-cons
                 ;; -- conses from the appropriate pool to be incorporated into
                 ;; the connection structure
                 do (incff j)
                 finally
                   (return
                     (if (and deltas (null (cdr deltas)))
                         ;; has exactly one element
                         (prog1 (first deltas)
                           (reclaim-slot-value-cons deltas))
                         deltas))))
         (connection-class
           (if (and (frame-of-class-p input-end-activity 'g2gl-flow-signal)
                    (frame-of-class-p output-end-activity 'g2gl-flow-gate))
               'g2gl-link-connection
               'g2gl-standard-connection))
         (connection (make-connection)))
    (setf (connection-frame-or-class connection) connection-class)
    (setf (input-end-object connection) input-end-activity)
    (setf (output-end-object connection) output-end-activity)
    (setf (input-end-position connection) input-end-position)
    (setf (output-end-position connection) output-end-position)
    (setf (delta-or-deltas connection) delta-or-deltas)
    (when diagonal
      (change-connection-attribute
        connection 'connection-style 'diagonal))

    ;; For now, assume all connections have arrows, not fins.  Users may change
    ;; this, e.g., by editing attributes of individual connections.  So, if we
    ;; want to respect that editing, we have to find a way to encode that info.
    ;; Review later! Similarly for line patterns, e.g., dashes. (MHD 1/28/05)
    (change-connection-attribute
      connection 'connection-arrows
      (copy-for-slot-value
        (if (eq connection-class g2gl-standard-connection-class)
            g2gl-standard-connection-arrows
            g2gl-link-connection-arrows)))
    (change-connection-attribute
      connection 'line-pattern
      (copy-for-slot-value
        (if (eq connection-class g2gl-standard-connection-class)
            g2gl-standard-connection-line-pattern
            g2gl-link-connection-line-pattern)))

    ;; later, if possible: if connection-class is the class
    ;; g2gl-link-connection, give connection the lowest possible G2 layer
    ;; position so that it will appear to run under most other objects and
    ;; connections in the flowchart!
    #-connections-v2
    (progn
      (slot-value-push connection (connections input-end-activity))
      (slot-value-push connection (connections output-end-activity)))
    #+connections-v2
    (let ((connection-item-1 (make-connection-item connection))
	  (connection-item-2 (make-connection-item connection))
	  (connection-itam-table-1
	   (or (connections input-end-activity)
	       (setf (connections input-end-activity)
		     (make-connection-item-table))))
	  (connection-itam-table-2
	   (or (connections output-end-activity)
	       (setf (connections output-end-activity)
		     (make-connection-item-table)))))	
      (setf (get-connection-item connection connection-itam-table-1)
	    connection-item-1)
      (setf (get-connection-item connection connection-itam-table-2)
	    connection-item-2))
    j))





;;; Show-thread-on-execution-display
;;;   (execution-thread thread, execution-display d):

(defun show-thread-on-execution-display (thread d)
  (let* ((established-h nil)
         h
         p)
    (when (thread-tokens-for-execution-displays thread)
      (setq established-h (first (thread-tokens-for-execution-displays thread))))
    (setq h (make-g2gl-thread-token thread))
    (cond
      ((not (eq (execution-display-mode d) 'superimposed-tracings))
       (gensym-push d (g2gl-execution-displays thread))
       (gensym-push h (thread-tokens-for-execution-displays thread)))
      (t
       ;; mode is SUPERIMPOSED-TRACINGS
       (setf (g2gl-execution-displays thread)
             (nconc (g2gl-execution-displays thread)
                    (gensym-list d)))
       (setf (thread-tokens-for-execution-displays thread)
             (nconc (thread-tokens-for-execution-displays thread)
                    (gensym-list h)))))
    (cond
      (established-h
       ;; we'll move h to the position (p) of established-h:
       (setq p (make-g2gl-body-position-for-block established-h)))
      (t
       ;; established-h is nil:
       (cond
         ((predecessor-activity-compilation thread)
          (set-up-transition-from-predecessor-activity-compilation
            thread (predecessor-activity-compilation thread) t))
         (t
          (position-thread-tokens-above-activity-to-execute thread)))
       ;; -- that should have moved h
       ;; -- now set position p to h's location:
       (setq p (make-g2gl-body-position-for-block h))))
    (add-to-g2gl-body h d p)
    (reclaim-g2gl-body-position p)))





;;;; G2GL/BPEL Miscellaneous System Procedures


;;; g2-execute-g2gl-process (g2gl-process g2gl-process):
;;;
;;; Note: this requires and expects its g2gl-process argument to be an item of
;;; class g2gl-process.  The system procedure cap must enforce this.

(defun-for-system-procedure g2-execute-g2gl-process ((g2gl-process item))
  (declare (values item))
  (cond
    ((this-is-an-abstract-process g2gl-process)
     (stack-error
       cached-top-of-stack
       "~NF cannot be executed because it is an abstract process."
       g2gl-process))
    ((compile-g2gl-process-if-necessary-and-possible g2gl-process)
     (let ((create-process-instance-for-current-process-p t)
           (process-instance-created-for-current-process? nil))
       (instantiate-g2gl-process-and-start-execution
         g2gl-process
         ;; no args for now; later, maybe have some way to enter/specify args
         nil
         nil)
       (if process-instance-created-for-current-process?
           (let ((ref process-instance-created-for-current-process?))
             (prog1 (evaluation-item-reference-referenced-item ref)
               (reclaim-evaluation-item-reference ref))))))
    (t
     (stack-error
       cached-top-of-stack
       "~NF cannot be executed due to compilation errors."
       g2gl-process))))



;;; g2-pause-g2gl-process-instance (g2gl-process-instance inst):
;;;
;;; Pauses the process instance and returns.
;;;
;;; Note: this requires and expects its inst argument to be an item of class
;;; g2gl-process-instance.  The system procedure cap must enforce this.

(defun-for-system-procedure g2-pause-g2gl-process-instance ((inst item))
  (let ((f (g2gl-process-instance-execution-frame inst)))
    (when (null f)
      (stack-error
        cached-top-of-stack
        "~NF cannot be used to pause a process -- it's not tied to any ~
         process. (In certain situations, this could suspected of being ~
         a possible Gensym internal error.)"
        inst))
    (pause-process-instance f)))

;; Note: at present, this does nothing special if the process is already
;; paused. Consider, if the process instance is already paused, having this
;; signal an error to complain.  It would be sad not to have a predicate
;; ("paused-p"? get-process-running-state?) if we did that!




;;; g2-kill-g2gl-process-instance (g2gl-process-instance inst):
;;;
;;; Note: this requires and expects its inst argument to be an item of class
;;; g2gl-process-instance.  The system procedure cap must enforce this.

(defun-for-system-procedure g2-kill-g2gl-process-instance ((inst item))
  (let ((f (g2gl-process-instance-execution-frame inst)))
    (when (null f)
      (stack-error
        cached-top-of-stack
        "~NF cannot be used to pause a process -- it's not tied to any ~
         process. (In certain situations, this could suspected of being ~
         a possible Gensym internal error.)"
        inst))
    (exit-g2gl-process-instance f nil)))




;;; g2-resume-g2gl-process-instance (g2gl-process-instance inst):
;;;
;;; Resumes the process instance and returns.
;;;
;;; Note: this requires and expects its inst argument to be an item of class
;;; g2gl-process-instance.  The system procedure cap must enforce this.

(defun-for-system-procedure g2-resume-g2gl-process-instance ((inst item))
  (let ((f (g2gl-process-instance-execution-frame inst)))
    (when (null f)
      (stack-error
        cached-top-of-stack
        "~NF cannot be used to resume a process -- it's not tied to any ~
         process. (In certain situations, this could suspected of being ~
         a possible Gensym internal error.)"
        inst))
    (resume-process-instance f)))



;;; g2-collect-all-g2gl-process-instances (g2gl-process s):
;;;
;;; Returns a sequence of all process instances of g2gl-process, possibly the
;;; empty sequence.
;;;
;;; Note: this requires and expects its inst argument to be an item of class
;;; g2gl-process.  The system procedure cap must enforce this.

(defun-for-system-procedure g2-collect-all-g2gl-process-instances ((s item))
  (declare (values sequence))
  (loop for v in (stack-of-compilation-versions s)
        nconc (loop with ref
                    with inst
                    for f in (current-execution-frames v)
                    as h = (g2gl-process-instance-handle f)
                    when (null (cdr h))
                      do (instantiate-g2gl-process-instance f)
                    do (setq ref (cdr h))
                       (setq inst
                             (evaluation-item-reference-referenced-item ref))
                    when inst
                      collect inst using gensym-cons)
          into list-of-insts
        finally
          (return
            (allocate-evaluation-sequence list-of-insts))))




;;; The class `g2gl-fault' is a system error class for propagating a G2GL
;;; execution fault to the stack evaluator.

(def-class (g2gl-fault g2-error
                       define-predicate
                       not-user-instantiable
                       do-not-put-in-menus)
  (fault-name nil (type g2gl-fault-name) system not-user-editable)
  (fault-data nil (type g2gl-fault-data) system not-user-editable))

(define-category-evaluator-interface (g2gl-fault-name :access read)
    symbol
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (g2gl-fault-data :access read)
    item-or-datum
  ((get-form (slot-value))
   slot-value))

(def-slot-value-writer g2gl-fault-data (value)
  (tformat "~NA" value))





;;; g2-call-g2gl-process-as-procedure(g2gl-process s, sequence args):
;;;
;;; Calls a process with arguments.  Returns a sequence of return values, or
;;; signals an error (an instance of g2gl-fault) if a fault is unhandled at the
;;; top level.

(defun-for-system-procedure g2-call-g2gl-process-as-procedure
    (g2gl-process sequence-with-arglist ret-var)
  (let (bad-arg)
    (cond
      ((this-is-an-abstract-process g2gl-process)
       (stack-error
         cached-top-of-stack
         "~NF cannot be executed because it is an abstract process."
         g2gl-process))
      ((not (compile-g2gl-process-if-necessary-and-possible g2gl-process))
       (stack-error
         cached-top-of-stack
         "~NF cannot be executed due to compilation errors."
         g2gl-process))
      ((setq bad-arg
             (loop for arg being each evaluation-sequence-element
                   of sequence-with-arglist
                   thereis (if (not (or (framep arg)
                                        (evaluation-text-p arg)
                                        (evaluation-float-p arg)
                                        (evaluation-truth-value-p arg)
                                        (evaluation-symbol-p arg)
                                        (evaluation-integer-p arg)
                                        (evaluation-sequence-p arg)
                                        (evaluation-structure-p arg)))
                               arg)))
       (stack-error
         cached-top-of-stack
         "~NA is not an acceptable G2GL argument value (calling ~NF as a procedure)."
         bad-arg g2gl-process))
      (t
       (let ((invocation-thread (make-g2gl-process-invocation-thread))
             (args
               (loop for arg being each evaluation-sequence-element
                     of sequence-with-arglist
                     collect (add-reference-to-g2gl-value arg)
                       using gensym-cons)))
         (setf (process-invocation-context invocation-thread)
               (make-code-body-continuation
                 'g2-call-g2gl-process-as-procedure ret-var
                 (gensym-list 'complete-process-invocation-thread
                              invocation-thread)))
         (instantiate-g2gl-process-and-start-execution
           g2gl-process args invocation-thread)
         ;; see continue-scheduled-process-invocation for continuation
         (reclaim-evaluation-sequence sequence-with-arglist))))))


(defun-for-system-procedure g2-compile-g2gl-process (g2gl-process)
  (when (this-is-an-abstract-process g2gl-process)
    (stack-error
      cached-top-of-stack
      "~NF cannot be compiled because it is an abstract process."
      g2gl-process))
  (if (compile-g2gl-process-if-possible g2gl-process)
      evaluation-true-value
      evaluation-false-value))


;;; g2-kill-all-g2gl-process-instances (g2gl-process p):

(defun-for-system-procedure g2-kill-all-g2gl-process-instances (p)
  (terminate-all-instances-of-g2gl-process p))





;;; g2-invoke-g2gl-operation (service-switch: item, operation-name: symbol,
;;;                           input-message: item-or-value)
;;;   = (output-message: item-or-value, reply-or-fault-name: symbol)
;;;
;;; The system procedure `g2-invoke-g2gl-operation' invokes an operation on one
;;; of the G2GL processes attached to the service switch.  The input-message may
;;; either be a Web service message structure or an instance of a subclass of
;;; g2gl-message.  Similarly, the returned output-message may either be a
;;; structure or an item.  If either message is an item, the caller is
;;; responsible for deleting the message afterward.  The procedure enters a wait
;;; state while waiting for the G2GL process to reply.  If the reply is a fault
;;; message, the second return value is the fault name, otherwise it is the
;;; symbol REPLY.


;;; The system procedure function `g2-invoke-g2gl-operation' schedules a G2GL
;;; thread and then returns.  The return value, an evaluation structure, will be
;;; stored in the ret-var variable at some later time.  If the process replies,
;;; the structure will have the following slots:
;;;   reply-or-fault-name: symbol (REPLY or a fault name)
;;;   output-message: item-or-value
;;; If the scope containing the partner link terminates without replying, the
;;; structure has the following slot:
;;;   error-text: text

(defun-for-system-procedure g2-invoke-g2gl-operation
    ((service-switch item) (operation-name symbol) (input-message item)
     (ret-var symbol))
  (declare (values))
  (unless (or (web-service-message-p input-message)
              (of-class-p input-message 'g2gl-message))
    (write-stack-error cached-top-of-stack
      (tformat "The input message is neither a Web service message structure ~
               nor an instance of a subclass of G2GL-MESSAGE:~%")
      (tformat (if (framep input-message) "~NF" "~NV") input-message)))
  ;; TO DO: look for an existing service port in service-switch
  (let ((instantiation-pair
          (look-for-g2gl-process-to-instantiate
            ;; TO DO: also use the message type?
            operation-name (get-primary-name-for-frame-if-any service-switch))))
    (unless instantiation-pair
      (stack-error
        cached-top-of-stack
        "Cannot find G2GL process to perform operation ~a."
        operation-name))
    (let ((partner-thread
            (instantiate-g2gl-process (car instantiation-pair) nil nil)))
       (unless partner-thread
         ;; TO DO: propagate the fault? (from initializing local vars)
         (stack-error
           cached-top-of-stack
           "Fault while instantiating G2GL process to perform operation ~a."
           operation-name))
       (let ((sp (make-raw-local-service-link
                   (cdr instantiation-pair) partner-thread))
             (mt (make-g2gl-message-transmission)))
         ;; TO DO: store sp in service-switch
         (setf (service-port-owner sp) service-switch)
         ;; TO DO: check the g2gl-port-type-definition to see if this operation
         ;; expects a return value.  If not, we don't need a continuation.
         (let ((pair (gensym-cons operation-name nil)))
           ;; TO DO: include conversation key
           ;; TO DO: allow multiple continuations per op-name
           (setf (cdr pair)
                 (make-code-body-continuation
                   'g2-invoke-g2gl-operation ret-var
                   (gensym-list 'complete-g2gl-operation-invocation pair)))
           (setf (continuations-waiting-for-reply sp) (gensym-list pair)))
         (setf (message-transmission-operation-name mt) operation-name)
         (setf (message-transmission-source-or-fault-name mt) 'invoke)
         (setf (message-transmission-g2gl-message mt)
               (clone-g2gl-message input-message))
         (enqueue-received-message-transmission mt (partner-service-port sp))
         (reclaim-gensym-cons instantiation-pair)
         (schedule-g2gl-execution-thread partner-thread nil)))))


(defun-void complete-g2gl-operation-invocation (completion-form)
  (setf (cdr (second completion-form)) nil)
  (reclaim-gensym-list completion-form))


;;; g2gl-get-failed-activity-name:
;;;
;;; Returns the failed activity name.

(defun-for-system-procedure g2gl-get-failed-activity-name ()
  (twith-output-to-text-string
    (twrite-string g2gl-failed-activity-name)))


;;;; G2GL Communication (Cont.)


;;; A `g2gl-service-switch' ...

(def-class (g2gl-service-switch g2gl-object)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-outline . foreground)
                   (g2-icon-background . #.g2gl-icon-background-color)
                   (text-region . black))
       g2-icon-background #.g2gl-icon-rectangle-background
       g2-icon-outline #.g2gl-icon-rectangle-outline
       text-region
       (text #w"Service" (1 22) small)
       (text #w"Switch" (5 40) small))))
  ;; note: spec says this should have a single name; we should either enforce
  ;; that (with warnings about, or by disallowing, multiple names, or make it
  ;; work in our implementation, which may be tricky.  For now, it will "be an
  ;; error", but there's no checking! (MHD 3/17/05)
  )


;;; The KB-specific variable `g2gl-standard-service-switch' holds the one
;;; standard G2GL service switch that every G2 KB must have.  It gets
;;; initialized when a new KB is created, via a call to the function
;;; `set-up-g2gl-standard-service-switch'.

(def-kb-specific-variable g2gl-standard-service-switch g2-bpel
  (:funcall set-up-g2gl-standard-service-switch))

(defun set-up-g2gl-standard-service-switch ()
  (let ((switch (make-entity 'g2gl-service-switch)))
    (change-primary-name-of-frame switch 'g2gl-standard-service-switch t)
    (set-transient-and-propagate switch nil)
    (funcall-method-macro 'activate-if-possible-and-propagate switch)
    switch))




;;; A `G2GL message transmissions queue' is either nil, for an empty queue, or a
;;; pair of pointers to the first and last cells of a list consisting of G2GL
;;; message transmissions in oldest-to-newest order.  In addition to message
;;; transmissions that represent exchanges between service endpoints, there are
;;; special kinds of message transmissions for making and breaking partner link
;;; connections.

(def-concept g2gl-message-transmissions-queue)



;;; `Look-for-G2GL-message-transmission'
;;; (execution-thread-at-a-receiving-activity-compilation thread,
;;; partner-link-variable-compilation partner-link-vc, G2GL-port-type-or-nil
;;; specified-port-type, G2GL-operation-name operation-name,
;;; compiled-G2GL-correlations correlations, g2gl-message-variable-compilation
;;; output-vc, reply-receipt-case reply-receipt-case):
;;;
;;; This returns either: the symbol success, when a G2GL message transmission
;;; already received from the partner service endpoint was found that is of the
;;; type being looked for, no faults or inconsistencies were detected, and
;;; output-vc was set to the found message; nil, when no G2GL message
;;; transmission of the type being looked for was found, no faults were
;;; detected, and thread was parked in the partner link that partner-link-vc is
;;; bound to; or an execution fault to be signaled.
;;;
;;; The fault names for the execution faults this might detect and signal, most
;;; of which reflect missing or inconsistent declarations rather than errors
;;; that could lead to crashes, are the symbols:
;;; no-binding-for-partner-link-variable, improper-message-source,
;;; partner-link-variable-type-unspecified,
;;; port-type-undetermined-by-partner-link-variable-type,
;;; port-type-description-not-found-for-operation,
;;; operation-not-described-as-two-way, wrong-type-of-message-received,
;;; wrong-type-of-output-variable, correlation-fault, and
;;; missing-part-to-initiate-conversation; note that this might also signal a
;;; fault reported by a reply activity compilation in a successfully found G2GL
;;; message transmission; and note that only one fault can be signaled when more
;;; than one fault condition exists.
;;;
;;; This never changes the execution-thread-state or the
;;; execution-thread-state-parameter of thread, and it never unparks thread from
;;; the partner link when it is parked there.
;;;
;;; Note that reply-receipt-case implies that the
;;; activity-compilation-to-execute of thread is an invoke activity compilation.

(defun look-for-g2gl-message-transmission
    (thread partner-link-vc specified-port-type operation-name correlations
            output-vc reply-receipt-case)
  (let* ((f (parent-execution-frame thread))
         (sp (get-value-of-g2gl-variable partner-link-vc f))
         ;; -- a non-nil result must be a directly-connected G2GL service port
         psp psp-owner queue mt source-or-fault-name m matched-correlation
         port-type correlation operation-spec
         conversation-key attribute-names
         new-key name-of-missing-attribute)
    (when (null sp)
      (return-from
        look-for-g2gl-message-transmission
        (package-up-g2gl-partnering-fault
          'no-binding-for-partner-link-variable
          (c-g2gl-variable-name partner-link-vc)
          nil)))
    (setq psp (partner-service-port sp))
    (setq psp-owner (service-port-owner psp))
    (setq queue (received-message-transmissions-queue sp))
    (cond
      ((and queue
            (loop for l on (car queue)
                  do (setq mt (car l))
                  thereis
                  (eq (message-transmission-operation-name mt)
                      operation-name)))
       (setq source-or-fault-name
             (message-transmission-source-or-fault-name mt))
       (setq m (message-transmission-G2GL-message mt))
       (setf (message-transmission-G2GL-message mt) nil)
       (setf (received-message-transmissions-queue sp)
             (delete-message-transmission-in-queue mt queue))
       (setq matched-correlation nil))
      ((null psp-owner)
       ;; This clause replaces the "handle disconnected partner case!!" comment
       ;; in the spec, and is needed to fix HQ-5329754 "G2GL: second invocation
       ;; of same process from one requester process blocked".  This fault is
       ;; also signaled in send-g2gl-message-transmission below.  See also the
       ;; related comment in reclaim-g2gl-variable-managed-value above.
       ;; -dougo, 9/12/06
       (return-from
         look-for-g2gl-message-transmission
         (package-up-g2gl-partnering-fault
           'partner-has-terminated
           operation-name m)))
      ((not (memq
              thread
              (threads-located-at-receiving-activity-compilations sp)))
       (gensym-push
         thread
         (threads-located-at-receiving-activity-compilations sp))
       ;; The position of the following return statement diverges from the spec!
       ;; It should always return if it gets to this condition, not just if the
       ;; thread is not already in the list of threads.  -dougo, 9/12/06
       ;; TO DO: determine if this difference is detectable.
       (return-from
         look-for-g2gl-message-transmission
         nil)))

    ;; NOTE: each of the following cond clauses either falls through or
    ;; returns its result as the value of this function. Therefore, there's
    ;; _mostly_ no need for explicit return-from's to exit this function.
    (cond
      ((not (memq source-or-fault-name '(invoke reply)))
       (make-g2gl-user-fault source-or-fault-name m))

      ;; the following steps just do consistency checking, with
      ;; appropriate faults signaled when inconsistencies are detected.
      ;; [consider having one or more special execution modes where
      ;; certain of these consistency checks are eliminated in order to
      ;; improve performance]
      ((or (and reply-receipt-case
                (eq source-or-fault-name 'invoke))
           (and (null reply-receipt-case)
                (eq source-or-fault-name 'reply)))
       (package-up-g2gl-partnering-fault
         'improper-message-source source-or-fault-name m))
      ((progn
         (cond ((not (c-g2gl-variable-type partner-link-vc))
                (unless (suppress-unspecified-partner-link-variable-type-faults
                          g2gl-parameters)
                  (return-from
                    look-for-g2gl-message-transmission
                    (package-up-g2gl-partnering-fault
                      'partner-link-variable-type-unspecified
                      (c-g2gl-variable-name partner-link-vc) m)))
                (setq port-type specified-port-type))
               (t
                (setq port-type
                      (look-for-g2gl-port-type
                        partner-link-vc
                        (eq source-or-fault-name 'reply)))
                (unless port-type
                  (return-from
                    look-for-g2gl-message-transmission
                    (package-up-g2gl-partnering-fault
                      'port-type-undetermined-by-partner-link-variable-type
                      (c-g2gl-variable-name partner-link-vc) m)))))
         (and specified-port-type
              (not (eq specified-port-type port-type))))
         ;; -- that is, if specified-port-type is inconsistent with the port
         ;;    type in the partner link variable type
       (package-up-g2gl-partnering-fault
         'specified-port-type-inconsistent specified-port-type m))
      ((and port-type
            (progn
              (setq operation-spec
                    (look-for-g2gl-operation-spec operation-name port-type))
              (cond
                ((null operation-spec)
                 (package-up-g2gl-partnering-fault
                   'description-not-found-for-operation operation-name m))
                ((<f (length operation-spec) 3)
                 (package-up-g2gl-partnering-fault
                   'operation-not-described-as-two-way operation-name m))
                ((and (framep m)
                      (not (frame-of-class-p m (third operation-spec))
                           ;; later, do this: !!  (MHD 4/12/05)
;                   (g2gl-value-is-of-type m (third operation-spec))
                   ))
                 (package-up-g2gl-partnering-fault
                   'wrong-type-of-message-received (class m) m))))))
      ((not (or (eq (c-g2gl-variable-type output-vc) 'general)
                ;; m should always be an instance of the type general
                (and (eq (c-g2gl-variable-type output-vc) 'structure)
                     (evaluation-structure-p m))
                ;; note: (MHD) abstract this testing!!
                (let ((type (c-g2gl-variable-type output-vc)))
                  (and (listp type)
                       (eq (first type) 'class)
                       (of-class-p m (second type)))))
            ;; later, do this:  !! (MHD 4/12/05)
;            (g2gl-value-is-of-type m (c-g2gl-variable-type output-vc))
            )
       (package-up-g2gl-partnering-fault
         'wrong-type-of-output-variable
         (c-g2gl-variable-type output-vc) m))
      ((and correlations
            (loop for cor in correlations
                  do (setq correlation cor)
                  thereis
                  (and (not (eq correlation matched-correlation))
                       (or (not reply-receipt-case)
                           (not (memq 'out cor)))
                       (setq conversation-key
                             (look-for-g2gl-conversation-key
                               correlation f))
                       (null
                         (match-G2GL-message-against-conversation-key
                           m conversation-key)))))
       (package-up-g2gl-partnering-fault
         'correlation-fault
         (c-g2gl-variable-name (first correlation))
         m))
      (t
       ;; -- result of this loop is the result of this function --
       (loop for cor in correlations
             do (setq correlation cor)
             when (and (or (not reply-receipt-case)
                           (not (memq 'out cor)))
                       (null
                         (look-for-g2gl-conversation-key
                           correlation f))
                       (memq 'initiate-conversation cor))
               do (setq attribute-names
                        (cdr (c-g2gl-variable-type (first cor))))
                 ;; -- car should've been CONVERSATION-KEY-ATTRIBUTES
                  (setq new-key nil)
                  (setq name-of-missing-attribute nil) ; nil cannot be a name
                  (loop for name in attribute-names
                        for value = (g2gl-message-attribute-value m name)
                        when value
                          do (gensym-push (gensym-cons name value) new-key)
                        else
                          do (setq name-of-missing-attribute name))
                  (when (null name-of-missing-attribute)
                    (loop for x in new-key
                          do (reclaim-gensym-cons x)
                          finally (reclaim-gensym-list new-key))
                    (return
                      (package-up-g2gl-partnering-fault
                        'missing-part-to-initiate-conversation
                        name-of-missing-attribute m)))
                  (set-value-of-g2gl-variable
                    (first correlation) new-key thread)
             finally
               (set-value-of-g2gl-variable
                 output-vc
                 (add-reference-to-g2gl-value m)
                 thread)
               (return 'success))))))



;;; `Look-for-G2GL-conversation-key' (compiled-G2GL-correlation correlation,
;;; execution-frame f):

(defun look-for-g2gl-conversation-key (correlation f)
  (let ((correlation-variable-binding
          (get-value-of-g2gl-variable (first correlation) f)))
    (first
      correlation-variable-binding)))        ; may be nil



;;; `Match-G2GL-message-against-conversation-key' (G2GL-message m,
;;; G2GL-conversation-key conversation-key):

(defun match-g2gl-message-against-conversation-key (m conversation-key)
  (loop with framep = (framep m)
        for (attribute . value) in conversation-key
        for m-value = (g2gl-message-attribute-value m attribute)
        always (if framep
                   (slot-value-equal-p value m-value)
                   (evaluation-value-equal-p value m-value))))






;;; `Send-G2GL-message-transmission'
;;; (execution-thread-at-a-reply-or-invoke-activity-compilation thread,
;;; source-or-fault-name source-or-fault-name):
;;;
;;; This returns either the symbol success, when a G2GL message transmission was
;;; successfully sent to a local process and no faults or inconsistencies were
;;; detected, or a g2gl-call-invocation structure, when a G2GL message is in the
;;; process of being sent to a remote Web service, or a g2gl-execution-fault
;;; structure to be signaled.
;;;
;;; The fault names for the execution faults this might detect and signal, most
;;; of which reflect missing or inconsistent declarations rather than errors
;;; that could lead to crashes, are the symbols:
;;; no-message-as-value-of-variable, partner-link-variable-type-unspecified,
;;; port-type-undetermined-by-partner-link-variable-type,
;;; port-type-description-not-found-for-operation,
;;; operation-not-described-as-two-way, wrong-type-of-message-to-send,
;;; correlation-fault, missing-part-to-initiate-conversation,
;;; cannot-find-process-to-perform-operation, and
;;; fault-while-instantiating-process-to-perform-operation; note that only one
;;; fault can be signaled when more than one fault condition exists.
;;;
;;; This never changes the execution-thread-state or the
;;; execution-thread-state-parameter of thread.

(defun send-g2gl-message-transmission (thread source-or-fault-name)
  (let* ((invoke-case (eq source-or-fault-name 'invoke))
         ;; -- true when the activity-compilation-to-execute of thread is an
         ;; invoke activity compilation
         (f (parent-execution-frame thread))
         (c (activity-compilation-to-execute thread))
         (input-vc (g2gl-message-variable c))
         (m (get-value-of-g2gl-variable input-vc f))
         partner-link-vc specified-port-type operation-name
         operation-spec port-type message-type-to-send
         conversation-key correlations correlation attribute-names
         new-key name-of-missing-attribute sp
         endpoint-reference? switch-name
         instantiation-pair partner-thread partner-sp partner-plvc pair mt)
    (unless (or (not m)
                (web-service-message-p m)
                (and (evaluation-item-reference-p m)
                     (setq m (evaluation-item-reference-referenced-item m))
                     ;; m just became frame for m, or nil (i.e., nil if deleted)
                     (of-class-p m 'g2gl-message)))
      (return-from
        send-g2gl-message-transmission
        (package-up-g2gl-partnering-fault
          'no-message-as-value-of-variable
          (c-g2gl-variable-name input-vc) nil)))
    (setq partner-link-vc (g2gl-partner-link-variable c))
    (setq specified-port-type (c-g2gl-port-type c))
    (setq operation-name (c-g2gl-operation-name c))
    (cond ((not (c-g2gl-variable-type partner-link-vc))
           (unless (suppress-unspecified-partner-link-variable-type-faults
                     g2gl-parameters)
             (return-from
               send-g2gl-message-transmission
               (package-up-g2gl-partnering-fault
                 'partner-link-variable-type-unspecified
                 (c-g2gl-variable-name partner-link-vc) m)))
           (setq port-type specified-port-type))
          (t
           (setq port-type
                 (look-for-g2gl-port-type partner-link-vc invoke-case))
           (unless port-type
             (return-from
               send-g2gl-message-transmission
               (package-up-g2gl-partnering-fault
                 'port-type-undetermined-by-partner-link-variable-type
                 (c-g2gl-variable-name partner-link-vc) m)))))
    (when (and specified-port-type
               (not (eq port-type specified-port-type)))
      ;; -- i.e., specified-port-type is inconsisten with port-type in the
      ;; partner link variable type
      (return-from
        send-g2gl-message-transmission
        (package-up-g2gl-partnering-fault
          'specified-port-type-inconsistent
          specified-port-type nil)))
    (when port-type
      (setq operation-spec
            (look-for-g2gl-operation-spec operation-name port-type))
      (when (null operation-spec)
        (return-from
          send-g2gl-message-transmission
          (package-up-g2gl-partnering-fault
            'description-not-found-for-operation
            operation-name nil)))
      (when (and (null invoke-case)
                 (<f (length operation-spec) 3))
        (return-from
          send-g2gl-message-transmission
          (package-up-g2gl-partnering-fault
            'operation-not-described-as-two-way
            operation-name nil)))
      (setq message-type-to-send
            (if invoke-case
                (second operation-spec)
                (third operation-spec)))
      (when (and (framep m)
                 (not (frame-of-class-p m message-type-to-send)))
        ;; not per latest spec, later, use:   (MHD 4/12/05)
;            (not (g2gl-value-is-of-type m message-type-to-send))
        (return-from
          send-g2gl-message-transmission
          (package-up-g2gl-partnering-fault
            'wrong-type-of-message-to-send
            (class m) nil))))
    (setq correlations (c-g2gl-correlations c))
    (when (and correlations
               (setq correlation
                     (loop for cor in correlations
                           when (or (not invoke-case) (not (memq 'in cor)))
                             return cor))
               (setq conversation-key
                     (look-for-g2gl-conversation-key correlation f))
               (null (match-g2gl-message-against-conversation-key
                       m conversation-key)))
      (return-from
        send-g2gl-message-transmission
        (package-up-g2gl-partnering-fault
          'correlation-fault
          (c-g2gl-variable-name (first correlation)) nil)))
    (when correlations
      (loop for correlation in correlations
            when (and (or (not invoke-case)
                          (not (memq 'in correlation)))
                      (null (look-for-g2gl-conversation-key correlation f))
                      (memq 'initiate-conversation correlation))
              do
                (setq attribute-names
                      (cdr (c-g2gl-variable-type (first correlation))))
                ;; -- car should've been CONVERSATION-KEY-ATTRIBUTES
                (setq new-key nil)
                (setq name-of-missing-attribute nil) ; nil cannot be a name
                (loop for name in attribute-names
                      for value = (g2gl-message-attribute-value m name)
                      when value
                        do (gensym-push (gensym-cons name value) new-key)
                      else
                        do (setq name-of-missing-attribute name))
                (when (null name-of-missing-attribute)
                  (loop for x in new-key
                        do (reclaim-gensym-cons x)
                        finally (reclaim-gensym-list new-key))
                  (return-from
                    send-g2gl-message-transmission
                    (package-up-g2gl-partnering-fault
                      'missing-part-to-initiate-conversation
                      name-of-missing-attribute nil)))
                (set-value-of-g2gl-variable (first correlation) new-key thread)))
    (setq sp (get-value-of-g2gl-variable partner-link-vc f))
    ;; -- a non-nil result must be a directly-connected G2GL service port
    (setq endpoint-reference?
          (c-default-value-for-g2gl-variable partner-link-vc))
    (cond
      ((and (not sp) (not invoke-case))
       (return-from send-g2gl-message-transmission
         (package-up-g2gl-partnering-fault 'invalid-reply operation-name nil)))
      ((and (not sp) (not endpoint-reference?))
       ;; [look at the G2GL-partner-link-groups or the source-G2GL-process of the
       ;; parent-compilation-version of f to see if there a partner link for this
       ;; process instance has already been established that should be
       ;; "paralleled here!]
       (setq switch-name
             (name-of-g2gl-service-switch-for-connection
               (source-g2gl-process
                 (parent-compilation-version f))))
       (setq instantiation-pair
             (look-for-g2gl-process-to-instantiate
               operation-name switch-name))
       (when (null instantiation-pair)
         (return-from
           send-g2gl-message-transmission
           (package-up-g2gl-partnering-fault
             'cannot-find-process-to-perform-operation
             operation-name nil)))
       (setq partner-thread
             (instantiate-g2gl-process (car instantiation-pair) nil nil))
       (when (null partner-thread)
         (return-from
           send-g2gl-message-transmission
           (package-up-g2gl-partnering-fault
             'fault-while-instantiating-process-to-perform-operation
             operation-name nil)))
       (setq partner-sp
             (make-raw-local-service-link partner-link-vc thread))
       (setf (service-port-owner partner-sp)
             (parent-execution-frame partner-thread))
       (setq partner-plvc (cdr instantiation-pair))
       (setf (direct-connection-partner-link-variable-compilation partner-sp)
             partner-plvc)
       (set-value-of-g2gl-variable partner-plvc partner-sp partner-thread)
       (reclaim-gensym-cons instantiation-pair)
       (schedule-g2gl-execution-thread partner-thread nil))
      ((and (not sp) endpoint-reference?)
       (let ((proc (get-instance-with-name-if-any
                     'procedure
                     ;; TO DO: don't hardcode the system procedure name-- put it
                     ;; in the g2gl-parameters system table, or each process, or
                     ;; each partner link variable?
                     'g2-invoke-web-service-operation)))
         (unless proc
           (return-from send-g2gl-message-transmission
             (package-up-g2gl-partnering-fault
               'g2web-kb-not-loaded operation-name nil)))
         (let* ((endpoint-reference-struct
                  (allocate-evaluation-structure-inline
                    'service-namespace
                    (make-evaluation-text (first endpoint-reference?))
                    'service-name
                    (make-evaluation-text (second endpoint-reference?))
                    'endpoint-name
                    (make-evaluation-text (third endpoint-reference?))))
                (operation-name-string
                  (convert-symbol-to-xml-name operation-name))
                (output-vc (g2gl-response-variable c))
                (invoc-or-error
                  (make-g2gl-to-g2-call-invocation
                    proc
                    (gensym-list
                      endpoint-reference-struct
                      operation-name-string
                      m)
                    (when output-vc (gensym-list output-vc))
                    thread)))
           (return-from send-g2gl-message-transmission
             (if (g2gl-call-invocation-p invoc-or-error)
                 invoc-or-error
                 (prog1 (package-up-g2gl-partnering-fault
                          'fault-while-invoking-web-service-procedure
                          invoc-or-error m)
                   (reclaim-if-text-string invoc-or-error)))))))
      ((direct-connection-partner-link-variable-compilation
         (setq partner-sp (partner-service-port sp)))
       ;; partner service port is directly connected
       (setq partner-thread
             (loop for th
                       in (threads-located-at-receiving-activity-compilations
                            partner-sp)
                   as c = (activity-compilation-to-execute th)
                   when (if (=f (g2gl-activity-class-code c)
                                (quoted-g2gl-activity-class-code g2gl-pick))
                            (loop for c-successor
                                      in (activity-compilation-successors c)
                                  thereis
                                  (eq operation-name
                                      (c-g2gl-operation-name c-successor)))
                            (eq operation-name (c-g2gl-operation-name c)))
                     return th))
       (when partner-thread
         (schedule-G2GL-execution-thread partner-thread nil)))
      ((not (service-port-owner partner-sp))
       ;; partner service port is disconnected
       ;; TO DO: instantiate a new process to receive the message!
       (return-from
         send-g2gl-message-transmission
         (package-up-g2gl-partnering-fault
           'partner-has-terminated
           operation-name m)))
      (invoke-case
       (return-from
         send-g2gl-message-transmission
         (package-up-g2gl-partnering-fault
           'indirect-invoke-not-implemented
           operation-name m)))
      ((setq pair (assq operation-name
                        (continuations-waiting-for-reply partner-sp)))
       ;; TO DO: match conversation key
       (when (cdr pair)
         (return-value-to-code-body-continuation
           (allocate-evaluation-structure-inline
             'reply-or-fault-name source-or-fault-name
             'output-message (clone-g2gl-message m))
           (cdr pair)))
       (setf (continuations-waiting-for-reply partner-sp)
             (delete-gensym-element
               pair (continuations-waiting-for-reply partner-sp)))
       (setf (service-port-owner partner-sp) nil)
       (return-from send-g2gl-message-transmission 'success))
      (t
       (return-from
         send-g2gl-message-transmission
         (package-up-g2gl-partnering-fault
           'invalid-reply
           operation-name m))))
    (setq mt (make-g2gl-message-transmission))
    (setf (message-transmission-operation-name mt) operation-name)
    (setf (message-transmission-source-or-fault-name mt) source-or-fault-name)
    (setf (message-transmission-g2gl-message mt) (clone-g2gl-message m))
    (enqueue-received-message-transmission mt partner-sp)
    (return-from send-g2gl-message-transmission 'success)))





;;; `package-up-g2gl-partnering-fault' (fault-name fault-name, fault-data
;;; fault-data, G2GL-message-to-reclaim m):

(defun package-up-g2gl-partnering-fault (fault-name fault-data m)
  (when (framep m)
    (delete-frame m))
  (make-g2gl-system-fault fault-name (twrite-g2gl-value fault-data)))







;;; Look-for-G2GL-port-type (partner-link-variable-compilation partner-link-vc,
;;; look-for-partner-port-type look-for-partner-port-type):

;;; This returns nil for any of the following faults:
;;; - there is no port type for this end of the partner link
;;; - the specified partner link type is undefined
;;; - a specified role name is absent from the definition of the specified
;;;   partner link type
;;; - the type of the partner link variable does not specify all the role names
;;;   in the partner link type

(defun look-for-g2gl-port-type (partner-link-vc look-for-partner-port-type)
  (let* ((partner-link-variable-type (c-g2gl-variable-type partner-link-vc))
         my-role-name
         partner-role-name
         partner-link-type-definition
         port-specs
         my-port-spec
         partner-port-spec
         number-of-role-names-in-variable-type
         chosen-port-spec)
    (cond
      ((eq (first partner-link-variable-type) 'port-types)
       (if (not look-for-partner-port-type)
           (return-from look-for-g2gl-port-type (second partner-link-variable-type))
           (return-from look-for-g2gl-port-type (third partner-link-variable-type))))
      (t
       ;; -- now the first element of partner-link-variable-type is
       ;;    ROLE-NAMES-PLUS-PARTNER-LINK-TYPE
       (setq my-role-name (second partner-link-variable-type))
       (setq partner-role-name (third partner-link-variable-type))
       (setq partner-link-type-definition
             (get-instance-with-name-if-any
               nil (fourth partner-link-variable-type)))
       (when (or (null partner-link-type-definition)
                 (not (frame-of-class-p
                        partner-link-type-definition
                        'G2GL-partner-link-type-definition)))
         (return-from look-for-g2gl-port-type nil)
         ;; -- in case the G2GL partner link type is not properly defined
         )
       (setq port-specs
             (partnership-port-specs partner-link-type-definition))
       (if (not my-role-name)
           (setq my-port-spec nil)
           (loop for spec in port-specs
                 when (or (eq spec my-role-name)
                          (and (consp spec)
                               (eq (car spec) my-role-name)))
                   return (setq my-port-spec spec)
                 finally (return-from look-for-g2gl-port-type nil)))
       (if (not partner-role-name)
           (setq partner-port-spec nil)
           (loop for spec in port-specs
                 when (or (eq spec partner-role-name)
                          (and (consp spec)
                               (eq (car spec) partner-role-name)))
                   return (setq partner-port-spec spec)
                 finally (return-from look-for-g2gl-port-type nil)))
       (setq number-of-role-names-in-variable-type
             (cond ((and (not my-role-name) (not partner-role-name)) 0)
                   ((and my-role-name partner-role-name) 2)
                   (t 1)))
       (unless (=f (length port-specs) number-of-role-names-in-variable-type)
         (return-from look-for-g2gl-port-type nil))
       (setq chosen-port-spec
             (if (null look-for-partner-port-type)
                 my-port-spec
                 partner-port-spec))
       (if (symbolp chosen-port-spec)
           (return-from look-for-g2gl-port-type chosen-port-spec)
           (return-from look-for-g2gl-port-type (cdr chosen-port-spec)))))))

;; [Try to avoid doing the fault checks redundantly each time a particular
;; activity compilation is executed, but make sure to do them after any relevant
;; edit.  (They are not done at compile or load time to avoid ordering
;; constraints.)]



;;; Look-for-G2GL-operation-spec (G2GL-operation-name operation-name,
;;; G2GL-port-type port-type):

(defun look-for-g2gl-operation-spec (operation-name port-type)
  (let* ((port-type-definition
           (get-instance-with-name-if-any nil port-type))) ; any class?!
    (cond
      ((or (null port-type-definition)
           (not (frame-of-class-p port-type-definition 'g2gl-port-type-definition)))
       ;; -- in case the G2GL port type is not properly defined
       nil)
      (t
       (loop for spec in (port-type-api port-type-definition)
             when (eq (first spec) operation-name)
               return spec
             finally
               (return nil))))))






;;; The `KB-specific property name names-of-g2gl-processes-for-instantiation' is
;;; used for recording process names.  The function that primarily manages this
;;; is record-g2gl-process-for-instantiation, q.v., below.

(def-kb-specific-property-name names-of-g2gl-processes-for-instantiation
    reclaim-gensym-list-function)




;;; Record-G2GL-process-for-instantiation (G2GL-process s,
;;; name-of-G2GL-service-switch switch-name):
;;;
;;; This adds the name of s to the list value of the
;;; names-of-G2GL-processes-for-instantiation property of each switch-name if it
;;; is not there already, creating the property if necessary.
;;;
;;; Note: the property list is a KB-specific property list.  The list that is
;;; the property value is cleared and automatically reclaimed when the KB is
;;; cleared.

(defun record-g2gl-process-for-instantiation (s switch-name)
  (let* ((s-name (get-primary-name-for-frame-if-any s))
         (process-names-for-instantiation
           (names-of-g2gl-processes-for-instantiation switch-name)))
    (when (not (memq s-name process-names-for-instantiation))
      (setf (names-of-g2gl-processes-for-instantiation switch-name)
            (nconc
              (names-of-g2gl-processes-for-instantiation switch-name)
              (gensym-list s-name))))))





;;; `Look-for-G2GL-process-to-instantiate' (G2GL-operation-name operation-name,
;;; G2GL-service-switch-name switch-name):

(defun look-for-g2gl-process-to-instantiate (operation-name switch-name)
  (loop with process-names-for-instantiation
          = (names-of-g2gl-processes-for-instantiation switch-name)
        with pair
        for process-name in process-names-for-instantiation
        as s = (get-instance-with-name-if-any 'g2gl-process process-name)
        when (and s
                  (stack-of-compilation-versions s)
                  (not (latest-existing-compilation-version-was-disowned s))
                  (setq pair
                        (assq
                          operation-name
                          (alist-of-g2gl-operation-names-for-instantiation
                            (first (stack-of-compilation-versions s))))))
          return (gensym-cons s (cdr pair))))





;;; `Make-raw-local-service-link'
;;; (direct-connection-partner-link-variable-compilation plvc, execution-thread
;;; thread):
;;;
;;; This returns the partner service port not yet attached to anything, though
;;; the directly connected service port has been fully interlinked with the G2GL
;;; process instance represented by plvc and f.

(defun make-raw-local-service-link (plvc thread)
  (let* ((dcsp (make-g2gl-service-port))
         (usp (make-g2gl-service-port)))
    (setf (service-port-owner dcsp) (parent-execution-frame thread))
    (setf (direct-connection-partner-link-variable-compilation dcsp) plvc)
    (setf (partner-service-port dcsp) usp)
    (setf (received-message-transmissions-queue dcsp) nil)
    (setf (threads-located-at-receiving-activity-compilations dcsp) nil)
    (setf (service-port-owner usp) nil)
    (setf (direct-connection-partner-link-variable-compilation usp) nil)
    (setf (partner-service-port usp) dcsp)
    (setf (received-message-transmissions-queue usp) nil)
    (setf (threads-located-at-receiving-activity-compilations usp) nil)
    (set-value-of-g2gl-variable plvc dcsp thread)
    usp))



;;; Reclaim-G2GL-service-port (G2GL-service-port sp):

(defun reclaim-g2gl-service-port (sp)
  (loop while (received-message-transmissions-queue sp)
        do (setf (received-message-transmissions-queue sp)
                 (delete-message-transmission-in-queue
                   (first (car (received-message-transmissions-queue sp)))
                   (received-message-transmissions-queue sp))))
  (reclaim-gensym-list
    (threads-located-at-receiving-activity-compilations sp))
  (reclaim-g2gl-service-port-internal sp))




;;; `Enqueue-received-message-transmission' (received-message-transmission mt,
;;; G2GL-service-port sp):

(defun enqueue-received-message-transmission (mt sp)
  (let* ((new-tail (gensym-list mt))
         (queue (received-message-transmissions-queue sp)))
    (cond
      ((null queue)
       (setf (received-message-transmissions-queue sp)
             (gensym-cons new-tail new-tail)))
      (t
       (setf (cdr (cdr queue)) new-tail)
       (setf (cdr queue) new-tail)))))



;;; `Delete-message-transmission-in-queue' (G2GL-message-transmission mt,
;;; G2GL-message-transmission-queue-that-includes-it queue):
;;;
;;; This returns queue minus mt; this could be nil.
;;;
;;; This reclaims mt and, in doing so, deletes and reclaims the
;;; message-transmission-G2GL-message of mt if it is a frame.

(defun delete-message-transmission-in-queue (mt queue)
  (loop with l = (car queue)
        with l-trailer = nil
        with l-follower
        until (eq (first l) mt)
        do (setq l-trailer l)
           (setq l (cdr l))
        finally
          (setq l-follower (cdr l))
          (reclaim-gensym-cons l)
          (when (framep (message-transmission-g2gl-message mt))
            ;; TO DO: should the message also be reclaimed if it's an evaluation
            ;; structure?  package-up-g2gl-partnering-fault does not, but that
            ;; might be a different case, or that might be a leak too.
            ;; -dougo, 7/27/07
            (delete-frame (message-transmission-g2gl-message mt)))
          (reclaim-g2gl-message-transmission mt)
          (cond
            ((and (null l-trailer) (null l-follower))
             (reclaim-gensym-cons queue)
             (return nil))
            ((null l-trailer)
             (setf (car queue) l-follower))
            ((null l-follower)
             (setf (cdr l-trailer) nil)
             (setf (cdr queue) l-trailer))
            (t
             (setf (cdr l-trailer) l-follower)))
          (return queue)))



(defun remove-thread-from-partner-links (thread parameter)
  (cond
    ((listp parameter)
     ;; -- true when the activity-compilation-to-execute of thread is a pick
     ;; activity compilation
     (loop for x in parameter
           if (managed-float-p x)                ; a time
             do (reclaim-managed-float x)
           else do
               ;; -- in this case, x is a G2GL-service-port
               (setf (threads-located-at-receiving-activity-compilations x)
                     (delete-gensym-element
                       thread
                       (threads-located-at-receiving-activity-compilations x))))
     (reclaim-gensym-list parameter))
    (t
     ;; -- in this case, parameter is a G2GL-service-port
     (setf (threads-located-at-receiving-activity-compilations parameter)
           (delete-gensym-element
             thread
             (threads-located-at-receiving-activity-compilations parameter)))))
  (setf (execution-thread-state-parameter thread) nil))





;;; Check a BPEL language URI for the given language type (a symbol such as
;;; EXPRESSION or QUERY).  If the URI corresponds to a supported language for
;;; that language type, return the corresponding language symbol, otherwise add
;;; a warning to the conversion state and return nil.

;; Currently the only supported language symbol is G2GL-EXPRESSION.
;; -dougo, 5/26/05

(defun check-bpel-language-uri (uri lang-type)
  (when (and uri (string=w uri g2gl-expression-language-uri))
    (return-from check-bpel-language-uri 'g2gl-expression))
  (add-g2gl-import-error
    (twith-output-to-text-string
      (twrite-string "Warning: ")
      (if (or (not uri) (string=w uri xpath-expression-language-uri))
          (tformat "XPath is an unsupported ~(~a~) language." lang-type)
          (tformat "Unknown ~(~a~) language ~s." lang-type uri))
      (tformat "  The only supported value for the ~(~aLanguage~) attribute is ~
                ~s.~%" lang-type g2gl-expression-language-uri)))
  nil)



;;;; G2GL diagram XML import and export
;;;; L. Hawkinson, A. Scott, M. David


;;; Importing BPEL Processes
;;;
;;; convert-xml-bpel-to-g2-bpel(xml-bpel-process)
;;;  -> (g2-bpel-process | errors )
;;;
;;; Converts by transforming, expanding and laying out.  It also validates
;;; syntactically and to some extent semantically the BPEL process input.
;;;
;;; Import will take plregisteredace directly from XML to a diagram.
;;;
;;; Import will perform the following high level tasks:
;;;
;;; i) XML parsing and validation against the BPEL and WSDL XML schemas;
;;;
;;; ii) Transforming and expanding BPEL XML into G2GL objects, workspaces and
;;; connections;
;;;
;;; iii) Performing layout of the G2GL process as it is being created.
;;;

;;; Layout Notes
;;;
;;; G2-BPEL-Process
;;;
;;; This is the root object for a process.
;;; The diagram itself is stored in the subworkspace of the process
;;;
;;; Process Workspace
;;;
;;; The process workspace will be broken into two parts:
;;;
;;; i) Top. Declaration of input and local variables used in the process.
;;; These will be objects that will be displayed in the form
;;; <var-name> = <var-value>, where = is an object and <var-name> and
;;; <var-value> are labels.
;;;
;;; ii) Bottom.  The process diagram itself will be displayed in a top to
;;; bottom manner with the direction of flow of the diagram proceeding down
;;; the way.
;;;
;;; Layout Rectangles
;;;
;;; Layout is broken up into rectangles, one rectangle for each activity
;;; that is being added to the diagram.
;;;
;;; Each rectangle has a width, a height, a location for the input connection
;;; to the rectangle and the location for the exit connection from
;;; the rectangle.
;;;
;;;
;;; Notes on laying out different types of Activities
;;;
;;;
;;; Activity
;;;
;;; An activity has an input connection on top and an output connection
;;; on the bottom
;;;
;;; Sequence
;;;
;;; Sequences are implicit in G2GL so they will not get separate nodes in the
;;; process diagram that is created.   So a sequence will be converted
;;; diagramatically into a sequence of connected nodes.
;;;
;;; Switch
;;;
;;; Switch branching is represented by multiple switch-fork objects each of
;;; which will be parallel to each other and connected.
;;;
;;; Below each switch fork a connection will connect to the activity on that
;;; switch branch.
;;;
;;; A switch-join bar will exist at the end of a switch to receive
;;; connections from each of the branches that imply continued execution.
;;; The switch-join bar must be parallel to the top and bottom of the
;;; workspace.
;;;
;;; While
;;;
;;; The body of the while loop is placed to the right of the while node. The
;;; first element in the body of the while loop is parallel with the while
;;; node itself.
;;;
;;; There will be a connection going from the top right of the while node to
;;; the first activity and a connection going from the bottom left of the last
;;; activity in the body going back to the bottom right of the while node
;;; loop is placed to the right of the while node. The first element in the
;;; body of the while loop is parallel with the while node itselfle loop is
;;; placed to the right of the while node. The first element in the body of
;;; the while loop is parallel with the while node itself.
;;;
;;; There will be a connection going from the top right of the while node to
;;; the first activity and a connection going from the bottom left of the
;;; last activity in the body going back to.
;;;
;;; There will be a connection going from the top right of the while node to
;;; the first activity and a connection going from the bottom left of the
;;; last activity in the body going back to the bottom left of the while node.
;;;
;;; In the special case where the while node does not have any body the
;;; connection from the top right of the while node will connect directly to
;;; the bottom right of the while node (making a loop with no activities in
;;; it.
;;;
;;; Flow
;;;
;;; At the beginning of a Flow a flow-split bar is placed.   It must be
;;; parallel with the bottom and top of the diagram workspace.  Multiple
;;; connections can come out of a flow-split bar for each of the activities
;;; in the flow.
;;;
;;; At the end of a Flow a flow-sync bar is placed.  It also must be parallel
;;; with the bottom and top of the diagram workspace.
;;;
;;; Pick
;;;
;;; Pick will be layed out in a similar manner to Switch, with multiple
;;; message-fork objects in parallel and with separate Pick branches that
;;; terminate with either a Terminate activity or a Pick-Join.
;;;
;;; Invoke
;;;
;;; The catch-handler for the invoke will be to the right and parallel to the
;;; invoke object. The catch-handler will return to the Invoke either by
;;; rejoining the lower right hand side of the Invoke object
;;;
;;; Scope
;;;
;;; A scope will be represented as an object with a subworkspace.  On the
;;; subworkspace a sub-diagram will be created which will follow the same
;;; structure as a top-level process diagram.
;;;
;;; Flow-Signal and Flow-Gate
;;;
;;; A Flow-Signal is a separate object that will be placed after an activity
;;; that is the source of the link.  It has one output.
;;;
;;; A Flow-Gate is a separate object that will be placed before an activity
;;; (it may have one or more intputs).
;;;
;;; A special kind of a connection is used to connect from a Flow-Signal to
;;; a Flow-Gate. For now these will just be connected directly, however,
;;; a better approach might make these connections not cross other objects
;;; directly.

;;; Layout algorithm
;;;
;;; convert-xml-bpel-activity-to-g2-bpel(xml-node, g2-bpel-process)
;;; = (width-of-layout, height-of-layout, input-offset, output-offset)
;;; begin
;;;  <to be determined>
;;; end


;;; Implementation Notes
;;;
;;; In the G2 directory there will be a schemas directory which will
;;; contain the XML schemas that can be used to validate BPEL, WSDL and
;;; XSD.
;;;
;;; A G2-BPEL-Process will be created with an associated subworkspace.
;;;
;;; A validating Document Object Model (DOM) parser will be created.
;;;
;;; An entity resolver will be registered with the DOM parser which is
;;; able to resolve to the location of the XML schema for BPEL, WSDL and
;;; XSD (XML schema definition) to the schemas directory that is on disk.
;;;
;;; The DOM parser will be run to produce an in-memory tree representation
;;; of the XML document.
;;;
;;; Any errors in parsing the XML document will be logged to the logbook
;;; and will be placed on the subworkspace of the G2-BPEL-Process object
;;;
;;; The first XML node of the Document object will be passed to a recursive
;;; function which will implement the layout algorithm that will be
;;; described above.


;;; A Note on code organization
;;;
;;; [xml/c/lispdom.c]
;;;
;;; Wraps DOM aspects of libxml2
;;;
;;; [lisp/dom.lisp]
;;;
;;; Lisp wrapper to DOM aspects of libxml2
;;;
;;; [lisp/g2-bpel.lisp]
;;;
;;; Among other things also implements the XML import and export
;;; functionality for G2-BPEL using the dom.lisp module.
;;;



;;; Notes on vertical vs. horizontal layout of BPEL workspaces:
;;;
;;; Advantages of horizontal:
;;;
;;;   corresponds with BPMN and UML prevailing practice
;;;
;;;
;;; Advantages of vertical:
;;;
;;;   used by some major players, at least Oracle BPEL Process Manager
;;;   (http://www.oracle.com/technology/products/ias/bpel/)
;;;
;;;   used in the famous "p. 15 example" (in the BPEL4WS spec)
;;;
;;;   printing or layout is usually more natural -- can show continuation on
;;;   following pages; with horizontal, you have to have a break -- "carriage
;;;   return" -- to view the continuation
;;;
;;;   viewing on screen is more natural -- can scroll up and down.  Scrolling up
;;;   and down is the easiest way to scroll because Page Up and Page Down keys
;;;   by default mean up/down scrolling.  This applies not just to default
;;;   viewing in G2 of workspaces, but also viewing in web browsers (e.g.,
;;;   screen shots, workspace images, or maybe some day vector graphics on web
;;;   pages).


;;; Functions for converting names in BPEL into symbols

(defun calculate-bpel-process-workspace-name (bpel-process-name)
  (when bpel-process-name
    (intern-text-string
      (tformat-text-string "~a-BODY" bpel-process-name))))


;;; Default width and height calculations for BPEL elements

(defconstant bpel-layout-border-size 40)
(defconstant bpel-variable-y-spacing-size 5)


;;; Set the partner link variable name, port type, and operation slots of a G2GL
;;; invoke, receive, reply, or message event handler from the corresponding
;;; attributes of a BPEL XML element.

(defun calculate-g2gl-operation-attributes (bpel-element activity)
  (change-slot-value
    activity 'g2gl-partner-link-variable-name
    (xml-element-get-attribute-symbol bpel-element "partnerLink"))

  (let ((port-type-qname
          (xml-element-get-attribute bpel-element "portType")))
    (when port-type-qname
      (multiple-value-bind (local-name prefix namespace)
          (xml-node-expand-qname-symbols bpel-element port-type-qname)
        (declare (ignore prefix))
        ;; Ignore the namespace and use the local-name as the name of the
        ;; g2gl-port-type-definition object.  Ideally this should use the
        ;; namespace URI to find a WSDL description containing the port type
        ;; definition.  -dougo, 5/23/05
        (declare (ignore namespace))
        (change-slot-value
          activity 'g2gl-port-type local-name))))

  (change-slot-value
    activity 'g2gl-operation-name
    (xml-element-get-attribute-symbol bpel-element "operation"))
)


;;; The function `calculate-partner-link-variable-type' figures out the variable
;;; type of a <partnerLink> element and returns it as a value suitable for the
;;; g2gl-partner-link-variable-type category.

(defun-simple calculate-partner-link-variable-type (element)
  (let ((partner-link-type
          (xml-element-get-attribute-symbol element "partnerLinkType"))
        (my-role
          (xml-element-get-attribute-symbol element "myRole"))
        (partner-role
          (xml-element-get-attribute-symbol element "partnerRole")))

    (if partner-link-type
        (slot-value-list 'role-names-plus-partner-link-type
                         my-role partner-role partner-link-type)
        ;; No partner-link-type specified, use the role names as port types.
        (slot-value-list 'port-types my-role partner-role))))


;;; The variable type of a local or arg variable according to the attributes of
;;; the corresponding XML element.

(defun calculate-g2gl-variable-type (element)
  (let ((type-qname
          (or (xml-element-get-attribute element "messageType")
              (xml-element-get-attribute element "type")
              (xml-element-get-attribute element "element"))))
    ;; We should maybe distinguish between types based on which attribute was
    ;; set, but generally it should be clear from the type name.

    (when type-qname
      (multiple-value-bind (type prefix? namespace?)
          (xml-node-expand-qname-symbols element type-qname)
        (if namespace?
            (let ((uri (xml-namespace-get-uri namespace?)))
              (cond ((string=w uri g2-datatypes-xml-namespace-uri)
                     ;; G2 type
                     (reclaim-text-string uri)
                     (if (g2gl-is-primitive-g2-type-symbol-p type)
                         type
                         (slot-value-list 'class type)))

                    ((and (string=w uri xsd-datatypes-xml-namespace-uri)
                          (g2gl-is-primitive-xsd-type-symbol-p type))
                     ;; XML Schema simple type
                     (reclaim-text-string uri)
                     (convert-xsd-primitive-type-to-g2-primitive-type type))

                    (t
                     ;; some other external type reference
                     (make-g2gl-xml-type-specifier prefix? type uri))))

            ;; No namespace found; this should probably be an error.
            (make-g2gl-xml-type-specifier prefix? type))))))


;;; Construct a text string containing the sequence of assignment expressions
;;; (in G2GL syntax) specified by a BPEL XML <assign> element.  The
;;; expression-language is the expression language symbol in effect for the
;;; element, and is used for determining the language of a <from> element with
;;; an expression attribute.  The query-language similarly determines the
;;; language of a <from> or <to> element with a query attribute.

;; It would probably be better to make a slot-value directly rather than making
;; a text string that gets parsed into a slot-value, but this way is guaranteed
;; not to put something bogus into the slot.  -dougo, 5/19/05

;; Currently an expression attribute is ignored (and the assignment is dropped)
;; if the expression-language is not G2GL-EXPRESSION.  -dougo, 5/19/05

;; Currently the attributes query, partnerLink, endpointReference, property, and
;; opaque are all ignored (and the assignment dropped).
;; See HQ-5020879 "G2GL: import ignores many forms of <assign>" -dougo, 5/19/05

(defun calculate-g2gl-assignment-expressions
    (element expression-language query-language)
  (twith-output-to-text-string
    (loop with wrote-any-p
          for child being each xml-element of (xml-node-child-nodes element) do
      (when (xml-node-name-symbol-equals-p
              child 'copy bpel-xml-namespace-uri)
        (let ((copy-children (xml-node-child-nodes child))
              (from-node nil)
              (to-node nil))
          (loop for copy-child being each xml-element of copy-children do
            (xml-node-name-symbol-case copy-child
              (bpel-xml-namespace-uri
                (from (setq from-node copy-child))
                (to   (setq to-node copy-child)))))
          (when (and from-node to-node)
            (let ((source (calculate-g2gl-assignment-source
                            from-node expression-language query-language))
                  (dest   (calculate-g2gl-assignment-destination
                            to-node query-language)))
              (when (and source dest)
                (if wrote-any-p
                    (twrite-string "; ")
                    (setq wrote-any-p t))
                (tformat "~a =~a" dest source))
              (when source (reclaim-text-string source))
              (when dest (reclaim-text-string dest))))))
          finally
            (unless wrote-any-p
              (twrite-string "none")))))


;;; Construct a text string containing the source (a G2GL expression)
;;; specified by a <from> element in a BPEL assignment activity, or nil if it
;;; can not be parsed (or is unsupported).

(defun calculate-g2gl-assignment-source
    (element expression-language query-language)
  (let ((variable
          (xml-element-get-attribute-symbol element "variable"))
        (part
          (xml-element-get-attribute-symbol element "part"))
        (query
          (xml-element-get-attribute element "query"))
        (partner-link
          (xml-element-get-attribute-symbol element "partnerLink"))
        (endpoint-reference
          (xml-element-get-attribute-symbol element "endpointReference"))
        (property
          (xml-element-get-attribute element "property"))
        (expression
          (xml-element-get-attribute element "expression"))
        (opaque
          (xml-element-get-attribute-symbol element "opaque")))
    (prog1
        (cond (variable
               (cond (property
                      ;; <from variable="ncname" property="qname"?/>
                      ;; TO DO
                      nil)
                     (part
                      (cond (query
                             ;; <from variable="ncname" part="ncname"
                             ;;       query="queryString"/>
                             ;; TO DO
                             (case query-language
                               (g2gl-expression
                                nil)
                               (t
                                nil)))
                            (t
                             ;; <from variable="ncname" part="ncname"/>
                             (twith-output-to-text-string
                               (twrite-string " the ")
                               (twrite-symbol part)
                               (twrite-string " of ")
                               (twrite-symbol variable)))))
                     (t
                      ;; <from variable="ncname"/>
                      (twith-output-to-text-string
                        (twrite-string " ")
                        (twrite-symbol variable)))))
              (partner-link
               (case endpoint-reference
                 ((my-role partner-role)
                  ;; <from partnerLink="ncname"
                  ;;       endpointReference="myRole|partnerRole"/>
                  ;; TO DO
                  nil)
                 (t
                  nil)))
              (expression
               ;; <from expression="general-expr"/>
               (case expression-language
                 (g2gl-expression
                  (copy-text-string expression))
                 (t
                  nil)))
              ((eq opaque 'yes)
               ;; <from opaque="yes"/>
               ;; TO DO
               nil)
              (t
               ;; <from> ... literal value ... </from>
               (convert-xml-literal-to-g2gl-constant element)))
      (when query
        (reclaim-text-string query))
      (when property
        (reclaim-text-string property))
      (when expression
        (reclaim-text-string expression))
      )))


;;; Construct a text string containing the destination (a G2GL designation)
;;; specified by a <to> element in a BPEL assignment activity, or nil if it can
;;; not be parsed (or is unsupported).

(defun calculate-g2gl-assignment-destination (element query-language)
  (let ((variable
          (xml-element-get-attribute-symbol element "variable"))
        (part
          (xml-element-get-attribute-symbol element "part"))
        (query
          (xml-element-get-attribute element "query"))
        (partner-link
          (xml-element-get-attribute-symbol element "partnerLink"))
        (property
          (xml-element-get-attribute element "property")))
    (prog1
        (cond (variable
               (cond (property
                      ;; <to variable="ncname" property="qname"/>
                      ;; TO DO
                      nil)
                     (part
                      (cond (query
                             ;; <to variable="ncname" part="ncname"
                             ;;     query="queryString"/>
                             ;; TO DO
                             (case query-language
                               (g2gl-expression
                                nil)
                               (t
                                nil)))
                            (t
                             ;; <to variable="ncname" part="ncname"/>
                             (twith-output-to-text-string
                               (twrite-string "the ")
                               (twrite-symbol part)
                               (twrite-string " of ")
                               (twrite-symbol variable)))))
                     (t
                      ;; <to variable="ncname"/>
                      (twith-output-to-text-string
                        (twrite-symbol variable)))))
              (partner-link
               ;; <to partnerLink="ncname"/>
               ;; TO DO
               nil)
              (t
               nil))
      (when query
        (reclaim-text-string query))
      (when property
        (reclaim-text-string property))
      )))


;;; Construct a text string containing a G2GL constant expression from an XML
;;; element containing a literal value, or nil if it can not be parsed (or is
;;; unsupported).

;; This should take a type specifier (and maybe check the xsi:type attribute if
;; present) to determine how to parse the literal value.  -dougo, 5/19/05

(defun convert-xml-literal-to-g2gl-constant (element)
  (let ((literal-value (xml-node-get-content element)))
    (when literal-value
      (cond ((or (string=w literal-value #w"true")
                 (string=w literal-value #w"false")
                 (syntactically-numeric-p literal-value))
             literal-value)
            (t
             ;; Assume it's a string, add double quotes.
             (twith-output-to-text-string
               (twrite-parsably literal-value)
               (reclaim-text-string literal-value)))))))


;;; The function `calculate-g2gl-correlations' returns a slot-value list
;;; (possibly empty) of G2GL correlations corresponding to the (well-formed)
;;; correlations of an XML element.

(defun calculate-g2gl-correlations (element)
  (let ((element (xml-node-get-child-by-name-symbol
                   element 'correlations bpel-xml-namespace-uri)))
    (when element
      (loop for child being each xml-element of (xml-node-child-nodes element)
            for correlation = (when (xml-node-name-symbol-equals-p
                                      child 'correlation bpel-xml-namespace-uri)
                                (calculate-g2gl-correlation child))
            when correlation
              collect correlation
                using slot-value-cons))))



;;; The function `calculate-g2gl-correlation' returns a G2GL correlation (a
;;; slot-value list) corresponding to a <correlation> XML element, or nil if the
;;; element is malformed.

(defun calculate-g2gl-correlation (element)
  (let ((name
          (xml-element-get-attribute-symbol element "set"))
        (initiate
          (xml-element-get-attribute-symbol element "initiate"))
        (pattern
          (xml-element-get-attribute-symbol element "pattern")))
    (unless name
      ;; TO DO: add a warning to the current conversion state ("set" attribute
      ;; is required)
      (return-from calculate-g2gl-correlation nil))
    (nconc
      (slot-value-list name)
      (when (eq initiate 'yes)
        (slot-value-list 'initiate-conversation))
      (case pattern
        ((in out) (slot-value-list pattern))
        ;; When the attribute string "out-in" is converted to a symbol, an extra
        ;; hyphen is inserted!
        (out--in (slot-value-list 'out-in))))))


;;; Initialize the alarm time slots of a G2GL object from an XML element.

(defun initialize-g2gl-alarm-time-from-xml-element
    (object element)
  (when (xml-element-has-attribute-p element "for")
    (initialize-g2gl-expression-slot-from-xml-attribute
      object 'duration-or-deadline-expression element "for")
    (change-slot-value object 'type-of-g2gl-alarm-time-expression
                       'DURATION-EXPRESSION))
  (when (xml-element-has-attribute-p element "until")
    (initialize-g2gl-expression-slot-from-xml-attribute
      object 'duration-or-deadline-expression element "until")
    (change-slot-value object 'type-of-g2gl-alarm-time-expression
                       'DEADLINE-EXPRESSION)))


;;; Find the default input or output connection of a g2gl-activity, or
;;; nil if it has none.

(defun g2gl-activity-default-input-connection (g2gl-activity)
  (loop for c being each input-connection of g2gl-activity
        of-type 'g2gl-standard-connection
        return c))

;;; The function `g2gl-activity-top-input-connection' returns the first standard
;;; input connection connected to the top of a g2gl-activity, or nil if it has
;;; none.

(defun g2gl-activity-top-input-connection (g2gl-activity)
  (loop for c being each input-connection of g2gl-activity
        of-type 'g2gl-standard-connection
        on-side-or-sides 'top
        return c))


(defun g2gl-activity-default-output-connection (g2gl-activity)
  (loop for c being each output-connection of g2gl-activity
        of-type 'g2gl-standard-connection
        return c))

;;; The function `g2gl-activity-default-output-stub' returns a g2gl-activity's
;;; first standard output connection that is connected to a loose end, or nil if
;;; it has none.

(defun g2gl-activity-default-output-stub (g2gl-activity)
  (loop for c being each output-connection of g2gl-activity
        of-type 'g2gl-standard-connection
        connected-to-a-block-of-type 'loose-end
        return c))


;;; Functions to find default input and output loose-ends
;;; of g2-bpel-activities

(defun bpel-activity-default-input-object (g2-bpel-activity)
  (loop for c being each input-connection of g2-bpel-activity
        as connection-frame-or-class = (connection-frame-or-class c)
        as class = (if (symbolp connection-frame-or-class)
                       connection-frame-or-class
                       (class connection-frame-or-class))
        when (subclassp class g2gl-standard-connection-class)
          return (input-end-object c)))

(defun bpel-activity-default-output-object (g2-bpel-activity)
  (loop for c being each output-connection of g2-bpel-activity
        as connection-frame-or-class = (connection-frame-or-class c)
        as class = (if (symbolp connection-frame-or-class)
                       connection-frame-or-class
                       (class connection-frame-or-class))
        when (subclassp class g2gl-standard-connection-class)
          return (output-end-object c)))

(defun bpel-activity-default-input-loose-end (g2-bpel-activity)
  (loop for c being each input-connection of g2-bpel-activity
        of-type 'g2gl-standard-connection
        connected-to-a-block-of-type 'loose-end
        return (input-end-object c)))

(defun bpel-activity-default-output-loose-end (g2-bpel-activity)
  (let ((c (g2gl-activity-default-output-stub g2-bpel-activity)))
    (when c (output-end-object c))))

(defun bpel-activity-immediately-connected-objects (g2-bpel-activity)
; (let ((result nil))
;   (loop for input-connection in
;         (list-g2-bpel-activity-input-connections g2-bpel-activity)
;         for input-end = (input-end-object-internal input-connection)
;        do (gensym-cons input-end result))
;   (loop for output-connection in
;         (list-g2-bpel-activity-output-connections g2-bpel-activity)
;         for output-end = (output-end-object-internal output-connection)
;        do (gensym-cons output-end result)))

  ;; Ths above is the old body of this function.  It creates a bunch of cons
  ;; cells for no good reason, and always returned nil.  I've replaced with the
  ;; new code below, to simply return nil, and will leave it up to Doug O. to
  ;; figure out what it really should do, or if callers should be modified not
  ;; to use this, and have this flushed!  (MHD 3/7/05)

  ;; New body:
  (declare (ignore g2-bpel-activity))
  nil)

;;; The function `bpel-activity-right-output-object' returns the first block it
;;; finds connected to g2-bpel-activity's right side via an output connection,
;;; if there is one; otherwise, it returns nil.

(defun bpel-activity-right-output-object (g2-bpel-activity)
  (loop for out being each output-connection of g2-bpel-activity
        on-side-or-sides 'right
        return (output-end-object out)))

(defun bpel-activity-right-output-connection (g2-bpel-activity)
  (loop for out being each output-connection of g2-bpel-activity
        on-side-or-sides 'right
        return out))


;;; The function `bpel-activity-right-input-object' returns the first block it
;;; finds connected to g2-bpel-activity's right side via an input connection,
;;; if there is one; otherwise, it returns nil.

(defun bpel-activity-right-input-object (g2-bpel-activity)
  (loop for in being each input-connection of g2-bpel-activity
        on-side-or-sides 'right
        return (input-end-object in)))


;;; The function `g2gl-activity-bottom-output-object' returns the first block it
;;; finds connected to g2gl-activity's bottom side via an output connection, if
;;; there is one; otherwise, it returns nil.

(defun g2gl-activity-bottom-output-object (g2gl-activity)
  (loop for out being each output-connection of g2gl-activity
        on-side-or-sides 'bottom
        return (output-end-object out)))

(defun g2gl-activity-bottom-output-connection (g2gl-activity)
  (loop for out being each output-connection of g2gl-activity
        on-side-or-sides 'bottom
        return out))


;;; Change the name of a G2GL object to a symbol, adding a name box if
;;; appropriate.

(defun change-g2gl-object-name (object name)
  (let ((allow-name-box-creation-without-workspace t))
    (change-slot-value object 'name-or-names-for-frame name)))


;;; The function `change-g2gl-variable-name' changes the appropriate slot of
;;; g2g2l-variable, an instance of any subclass of g2gl-variable, so it has the
;;; the name specified.  This also ensures the presence of a box, aligned to the
;;; left of the variable's icon, showing the name.  This is the way to change
;;; the name of any g2gl-variable when importing.  This returns the name.

(defun change-g2gl-variable-name (g2gl-variable name)
  (change-g2gl-object-name g2gl-variable name))


;;; Lowell's algorithm for laying out BPEL diagrams


;;; The special variable `g2gl-import-errors' holds a gensym list of error
;;; messages (text strings).  It only has a value during a G2GL import
;;; operation.

(defvar g2gl-import-errors)

;;; The special variable `g2gl-import-added-start-activity-p' is nil until
;;; the first activity has been added to the current G2GL body, after which it
;;; is t.  It only has a value during a G2GL import operation.

(defvar g2gl-import-added-start-activity-p)

;;; The special variable `g2gl-import-flow-link-p-list' holds a gensym
;;; p-list of flow-link names and objects.  It only has a value during a G2GL
;;; import operation.

(defvar g2gl-import-flow-link-p-list)

;;; The special variables `g2gl-expression-language-symbol' and
;;; `g2gl-query-language-symbol' each hold a symbol indicating the current
;;; expression language and query language, respectively.  Currently the only
;;; value this can hold is G2GL-EXPRESSION-LANGUAGE.  These variables only have
;;; a value during a G2GL import operation.

(defvar g2gl-expression-language-symbol)
(defvar g2gl-query-language-symbol)


;;; A bpel-layout is a list of the form
;;; (<width> <height> <entry-activity> <exit-activity> <blocks>)

;;; A bpel-layout represents a rectangle containing a set of activities and
;;; connections.  The rectangle is the smallest bounding box of its contents,
;;; i.e., some activity or connection abuts each of the four edges of the
;;; rectangle.  In particular, the top edge of the entry activity lies on the
;;; top edge of the rectangle.  The rectangle is initially positioned with its
;;; upper left corner at 0,0 on the current workspace, but it may later be moved
;;; to a different position (see `move-existing-layout-to-x-y' below).

;;; An empty bpel-layout is allowed, with <entry-activity>, <exit-activity>, and
;;; <blocks> all null.  The <width> and <height> may be non-zero to represent a
;;; region of padding.

(defmacro bpel-layout-width (layout)
  `(first ,layout))

(defmacro bpel-layout-height (layout)
  `(second ,layout))

(defmacro bpel-layout-entry-activity (layout)
  `(third ,layout))

(defmacro bpel-layout-exit-activity (layout)
  `(fourth ,layout))

(defmacro bpel-layout-blocks (layout)
  `(fifth ,layout))

(defun bpel-layout-empty-p (layout)
  (null (bpel-layout-blocks layout)))

(defun make-bpel-layout (width height entry-activity exit-activity blocks)
  (gensym-list width height entry-activity exit-activity blocks))

(defun make-empty-bpel-layout ()
  (make-bpel-layout 0 0 nil nil nil))

(defmacro bpel-layout-bind ((width height entry exit blocks) layout &body body)
  (avoiding-variable-capture (layout)
    `(prog1 (let ((,width (bpel-layout-width ,layout))
                  (,height (bpel-layout-height ,layout))
                  (,entry (bpel-layout-entry-activity ,layout))
                  (,exit (bpel-layout-exit-activity ,layout))
                  (,blocks (bpel-layout-blocks ,layout)))
              ,@body)
       (reclaim-bpel-layout ,layout))))

(defun reclaim-bpel-layout (layout)
  (reclaim-gensym-list layout))

(defun reclaim-bpel-layout-and-blocks (layout)
  (reclaim-gensym-tree layout))

;;; Reclaim a gensym list of bpel-layouts, along with the list itself.
(defun reclaim-bpel-layouts (layouts)
  (loop for layout in layouts do (reclaim-bpel-layout layout)
        finally (reclaim-gensym-list layouts)))

(defun add-g2gl-import-errors (errors)
  (setf g2gl-import-errors (nconc g2gl-import-errors errors)))

(defun add-g2gl-import-error (error-text)
  (add-g2gl-import-errors (gensym-list error-text)))


;;; The function `initialize-g2gl-expression-slot-from-xml-attribute'
;;; initializes an expression slot of a G2GL object from the value of an XML
;;; element attribute.  The `slot-name' argument is a symbol, while the
;;; `attr-name' and `ns-uri' arguments are strings (which are case-sensitive).
;;; If the expression is not parsable in the current expression language, an
;;; error is added to the current list of import errors and the slot is left
;;; uninitialized.

(defun initialize-g2gl-expression-slot-from-xml-attribute
    (object slot-name element attr-name &optional ns-uri)
  (let ((expr (xml-element-get-attribute element attr-name ns-uri)))
    (when expr
      (case g2gl-expression-language-symbol
        (g2gl-expression
         (unless (change-the-text-of object slot-name (copy-text-string expr))
           (let* ((attr-node (xml-element-get-attribute-node
                               element attr-name ns-uri))
                  (line (xml-node-get-line attr-node))
                  (qname (xml-node-qname element))
                  (attr-qname (xml-node-qname attr-node)))
             (add-g2gl-import-error
               (tformat-text-string
                 ;; TO DO: include filename, if any
                 "~%Line ~a: G2GL expression cannot be parsed: <~a ~a=~s>"
                 line qname attr-qname expr))
             (reclaim-text-string qname)
             (reclaim-text-string attr-qname))))
        (t
         ;; An unsupported expression language already resulted in an error, so
         ;; just ignore the expression in this case.
         ))
      (reclaim-text-string expr))))


;;; Functions to connect BPEL activities and loose-ends

(defun perform-connect-bpel-activities (exit-activity input-activity)
  (let ((output-loose-end
          (bpel-activity-default-output-loose-end exit-activity))
        (input-loose-end
          (bpel-activity-default-input-loose-end input-activity)))
    (cond ((and input-loose-end output-loose-end)
           ;; Find first connection (there must be one, and cannot be any more),
           ;; and then delete it.
           (loop for c being each connection of input-loose-end
                 return (delete-connection c))
           (connect-loose-end-to-block
             output-loose-end input-activity
             'top (halfw (width-of-block input-activity))))
          (input-loose-end
           (connect-loose-end-to-block
             input-loose-end exit-activity
             'bottom (halfw (width-of-block exit-activity))))
          (output-loose-end
           (connect-loose-end-to-block
             output-loose-end input-activity
             'top (halfw (width-of-block input-activity)))))))

;;; Position-of-ith-g2gl-connection .... 1 <= i <= n-connections

(defun position-of-ith-g2gl-connection (i block side n-connections)
  (roundw (*w i
              (case side
                ((left right) (height-of-block block))
                (t (width-of-block block))))
          (+ 1 n-connections)))


;;; Bend-distance-of-ith-g2gl-connection .... 1 <= i <= n-connections

;;; The distance between the bend and the destination end of the ith connection
;;; of a group of n parallel connections, as an increment of
;;; default-stub-length.  In order to avoid connection overlaps the bend
;;; distances should be short for the leftmost and rightmost connections and
;;; long for the ones in the middle.  For example, with n-connections = 5 the
;;; connections might look like this (with the destination ends at the top):

;;;    i = 1 2 3 4 5
;;;        | | | | |
;;; +------+ | | | +-----+
;;; |   +----+ | +---+   |
;;; |   |   +--+     |   |
;;; |   |   |        |   |

;;; Note that if the middle connection were straight, the others could be lower
;;; because they wouldn't overlap, but the user might move the connection around
;;; and it's convenient to have the bends in the right place already.

;;; If the side argument is 'right, the connections are connecting to the right
;;; side of a block, e.g. an invoke activity with local handlers.  In this case,
;;; the block is at the top of the layout rather than being centered, so all the
;;; connections bend in the same direction (down):

;;; 1 ----------
;;; 2 -------+
;;; 3 -----+ +--
;;; 4 ---+ |
;;; 5 -+ | +----
;;;    | |
;;;    | +------
;;;    |
;;;    +--------

;;; In this case, the bend distance is longest for the first two (the first one
;;; is just straight across, but we put the bend in anyway at the same distance
;;; as the second connection).

(defun bend-distance-of-ith-g2gl-connection (i n-connections
                                               &optional (side 'bottom))
  (*w default-stub-length
      (case side
        (right
         ;; n-i+1, but no more than n-1
         (minf (1+f (-f n-connections i)) (1-f n-connections)))
        (otherwise
         ;; i or n-i+1, whichever is smaller
         (minf i (1+f (-f n-connections i)))))))

;;; The amount of room required for a group of n parallel connections,
;;; properly bent to avoid overlap, in increments of default-stub-length.
;;; In other words, the total height/width of the above diagrams.

(defun room-for-g2gl-connections (n-connections &optional (side 'bottom))
  (*w default-stub-length
      (case side
        (right
         ;; n, but at least 2
         (maxf n-connections 2))
        (otherwise
         ;; half rounded up, plus 1
         (1+f (halff (1+f n-connections)))))))


;;; The function `delete-g2gl-output-connections' deletes all G2GL standard
;;; output connections from a G2GL activity.

(defun delete-g2gl-output-connections (activity &optional (side 'bottom))
  (let ((conns (list-g2-bpel-activity-output-connections activity side)))
    (loop for conn in conns do (delete-connection conn))
    (reclaim-gensym-list conns)))

;;; The function `delete-g2gl-input-connections' deletes all G2GL standard
;;; input connections from a G2GL activity.

(defun delete-g2gl-input-connections (activity)
  (let ((conns (list-g2-bpel-activity-input-connections activity)))
    (loop for conn in conns do (delete-connection conn))
    (reclaim-gensym-list conns)))


(defun perform-branching-connections (branch-activity branch-layouts
                                                      &optional (side 'bottom))
  (delete-g2gl-output-connections branch-activity side)
  (let ((n-connections (length branch-layouts))
        (input-side (opposite-side-of-side side)))
    (loop for layout in branch-layouts
          for entry-activity = (bpel-layout-entry-activity layout)
          for ic = (or (g2gl-activity-default-input-connection entry-activity)
                       ;; If there is no input connection stub, e.g. a local
                       ;; handler for invoke, then make one.
                       (g2gl-activity-add-standard-connection
                         entry-activity 'input input-side))
          for input-end = (input-end-object ic)
          as i from 1
          as position
             = (position-of-ith-g2gl-connection
                 i branch-activity side n-connections)
          as bend-distance
             = (bend-distance-of-ith-g2gl-connection
                 i n-connections side)
          do (connect-loose-end-to-block
               input-end branch-activity side position bend-distance))))


(defun perform-joining-connections (join-activity branch-layouts)
  (delete-g2gl-input-connections join-activity)
  (let ((n-connections (length branch-layouts))
        (side 'top) (output-side 'bottom))
    (loop for layout in branch-layouts
          for exit-activity = (bpel-layout-exit-activity layout)
          for stub = (or (g2gl-activity-default-output-stub exit-activity)
                         ;; If there is no output stub, e.g. a return or exit
                         ;; activity, then make one.
                         (g2gl-activity-add-standard-connection
                           exit-activity 'output output-side))
          for output-end = (output-end-object stub)
          as i from 1
          as position
             = (position-of-ith-g2gl-connection
                 i join-activity side n-connections)
          as bend-distance
             = (bend-distance-of-ith-g2gl-connection
                 i n-connections)
          when output-end
            do (connect-loose-end-to-block
                 output-end join-activity side position bend-distance))))

(defun collect-flow-links (link-block link-name)
  (let ((p-list-entry (getf g2gl-import-flow-link-p-list link-name)))
    (if p-list-entry
        (nconc p-list-entry (gensym-list link-block))
        (setf g2gl-import-flow-link-p-list
              (nconc g2gl-import-flow-link-p-list
                     (gensym-list link-name (gensym-list link-block)))))))

(defun get-g2gl-link-connection-input-loose-end (block)
  (loop for connection being each connection of block
        when (frame-of-class-p (input-end-object-internal connection) 'loose-end)
          do  (let ((class
                      (class-of-thing connection)))
                (when (subclassp class 'g2gl-link-connection)
                  (return (input-end-object-internal connection))))))

(defun get-g2gl-link-connection-output-loose-end (block)
  (loop for connection being each connection of block
        when (frame-of-class-p (output-end-object-internal connection) 'loose-end)
          do  (let ((class
                      (class-of-thing connection)))
                (when (subclassp class 'g2gl-link-connection)
                  (return (output-end-object-internal connection))))))

(defun perform-connect-flow-link (signal-block gate-block link-name)
  (unless (eq (get-workspace-if-any signal-block)
              (get-workspace-if-any gate-block))
    ;; A flow link is allowed to cross a scope boundary in BPEL, but G2GL does
    ;; not yet support it.  For now just leave the blocks disconnected and add a
    ;; warning.  See HQ-5155228 "G2GL: import of flow link crossing a scope
    ;; boundary leads to corruption".  -dougo, 11/16/05
    (add-g2gl-import-error
      (tformat-text-string
        "Warning: flow link ~a crosses a scope boundary, ~
         which G2GL does not support."
        link-name))
    (return-from perform-connect-flow-link nil))
  (let ((signal-loose-end
          (get-g2gl-link-connection-output-loose-end signal-block))
        (gate-loose-end
          (get-g2gl-link-connection-input-loose-end gate-block)))
    (when gate-loose-end
      (loop for x being each connection of gate-loose-end
            return (delete-connection x)))
    (when signal-loose-end
      (let ((side-of-gate-block-to-connect-to 'left))
        (when (left-edge-of-block-lessp gate-block signal-block)
          ;; The flow connection goes from right to left; connect the left side
          ;; of the signal to the right side of the gate.
          (let* ((flow-connection
                   (loop for c being each connection of signal-loose-end
                         return c))
                 (position-on-side
                   (get-position-on-side-given-end-position
                     (input-end-position flow-connection))))
            (setf (input-end-position flow-connection)
                  (combine-side-and-position-on-side-for-end-position
                    'left position-on-side)))
          (setq side-of-gate-block-to-connect-to 'right))
        (connect-loose-end-to-block signal-loose-end
                                    gate-block
                                    side-of-gate-block-to-connect-to
                                    20))
        ;; Put the signal block at the bottom of the workspace layering order,
        ;; so that its outgoing (diagonal) flow connection will cross underneath
        ;; the other blocks in the layout instead of over top.  Note that the
        ;; flow connection may still cross over other signal blocks (and their
        ;; outgoing connections), but there's no way to re-order the connections
        ;; in the workspace layering order separately from the blocks, so this
        ;; is the best we can do.
        (lower-block-to-bottom signal-block))))

(defun perform-connect-named-flow-links (link-name link-blocks)
  (let ((signal-blocks nil)
        (gate-blocks nil))
    (loop for block in link-blocks
          do
      (cond ((frame-of-class-p block 'g2gl-flow-gate)
             (setq gate-blocks (gensym-cons block gate-blocks)))
            (t  (setq signal-blocks (gensym-cons block signal-blocks)))))
    (loop for gate in gate-blocks
          do
      (loop for signal in signal-blocks
            do
        (perform-connect-flow-link signal gate link-name)))

    (reclaim-gensym-list signal-blocks)
    (reclaim-gensym-list gate-blocks)))

(defun perform-connect-flow-links ()
  (loop for (link-name link-blocks) on g2gl-import-flow-link-p-list by 'cddr do
    (perform-connect-named-flow-links link-name link-blocks)))

(defun perform-trim-last-activity-connections (layout)
  (unless (bpel-layout-empty-p layout)
    (let ((output-object
            (bpel-activity-default-output-loose-end
              (bpel-layout-exit-activity layout))))
      (when output-object
        (loop for c being each input-connection of output-object
              do
          (return (delete-connection c))))))
  layout)

(defun get-link-connection-of-flow-signal (flow-signal)
  (loop for c being each output-connection of flow-signal
        of-type 'g2gl-link-connection
        return c))

(defun collect-flow-signals-connected-to-flow-gate (flow-gate)
  (loop for c being each input-connection of flow-gate
        of-type 'g2gl-link-connection
        connected-to-a-block-of-type 'g2gl-flow-signal
        collect (input-end-object c) using gensym-cons))


;;; The special variable `g2gl-body-being-laid-out' holds the kb-workspace onto
;;; which G2GL objects are currently being laid out as part of import or
;;; redo-layout.  It only has a value during those operations.

(defvar g2gl-body-being-laid-out)


;;; Functions to move layouts

;;; Move the top left corner of an activity to a particular x and y location on
;;; the workspace, keeping the other activities and connections in the layout in
;;; the same relative positions.

(defun move-existing-layout-to-x-y (input-activity layout-blocks x y)
  (let* ((delta-x
           (- x (left-edge-of-block input-activity)))
         (delta-y
           (- y (top-edge-of-block input-activity))))
    (move-blocks-with-their-external-connections
      layout-blocks g2gl-body-being-laid-out delta-x delta-y)))


;;; Functions for different types of layouts

;;; Layout type 1
;;;
;;; Activity Layout
;;;
;;; Layout a single activity at 0,0 on the workspace
;;;
;;; Used for sequence, process, variables

(defun perform-activity-layout (activity)
  (unless (or (frame-of-class-p activity 'g2gl-variable)
              (frame-of-class-p activity 'g2gl-handler)
              g2gl-import-added-start-activity-p)
    ;; Remove the first stub in the activity.
    (let ((input-stub
            (bpel-activity-default-input-object activity)))
      (when input-stub
        (delete-connection (get-connection-for-loose-end input-stub)))
      (setf g2gl-import-added-start-activity-p t)))
  (let* ((width (width-of-block activity))
         (height (height-of-block activity))
         (blocks
           (gensym-cons activity (bpel-activity-immediately-connected-objects
                                   activity))))

    ;; The following function takes workspace coordinates in the user coordinate
    ;; system, so to get the upper left corner at 0,0 we have to use w/2,-h/2.
    (transfer-blocks-with-their-external-connections
      blocks
      g2gl-body-being-laid-out
      (halfw width)
      (-w (halfw height))
      nil)

    (make-bpel-layout width height activity activity blocks)))



;;; Arrange a list of layouts vertically from top to bottom into a single
;;; layout, with the given spacing in between (or bpel-layout-border-size if not
;;; provided).  The layouts are assumed to have their upper left corner at 0,0.
;;; Each layout will be centered in the return layout.  The returned entry
;;; activity and exit activity will be the entry activity of the first non-empty
;;; layout and the exit activity of the last non-empty layout, respectively.

(defun arrange-layouts-vertically
    (layouts &optional (spacing bpel-layout-border-size))
  (let ((max-width (loop for (width . nil) in layouts maximize width))
        (total-height 0)
        (first-entry-block nil)
        (last-exit-block nil)
        (all-blocks nil))
    (loop for (width height entry-block exit-block blocks) in layouts
          and y = 0 then (+w total-height spacing)
          do
      (setq total-height (+w y height))
      (when blocks
        (move-existing-layout-to-x-y
          entry-block
          blocks
          (+w (left-edge-of-block entry-block)
              (halfw (-w max-width width)))
          y)
        (when last-exit-block
          ;; Fix up the connection from the previous layout, if there is one, to
          ;; bend at the midpoint of the spacing, and move its endpoints to the
          ;; appropriate position and side.
          (let ((internal-connection
                  (g2gl-activity-bottom-output-connection last-exit-block)))
            (when (and internal-connection
                       (eq (output-end-object internal-connection) entry-block))
              (clean-up-connection
                internal-connection
                (-w (top-edge-of-block entry-block)
                    (bottom-edge-of-block last-exit-block)
                    (halfw spacing))))))
        (unless first-entry-block (setq first-entry-block entry-block))
        (setq last-exit-block exit-block)
        (setq all-blocks (nconc all-blocks blocks))))

    (make-bpel-layout
      max-width total-height first-entry-block last-exit-block all-blocks)))


;;; Arrange a list of layouts horizontally from left to right into a single
;;; layout, with the given spacing in between (or bpel-layout-border-size if not
;;; provided).  Each layout will be flush to top.  The layouts are assumed to
;;; have their upper left corner at 0,0.  The returned entry activity and exit
;;; activity will be the entry activity of the first non-empty layout and the
;;; exit activity of the last non-empty layout, respectively.

(defun arrange-layouts-horizontally
    (layouts &optional (spacing bpel-layout-border-size))
  (let ((total-width 0)
        (max-height 0)
        (first-entry-block nil)
        (last-exit-block nil)
        (all-blocks nil))
    (loop for (width height entry-block exit-block blocks) in layouts
          and x = 0 then (+w total-width spacing)
          do
      (setq total-width (+w x width))
      (setq max-height (maxw max-height height))
      (when blocks
        (move-existing-layout-to-x-y
          entry-block
          blocks
          (+w (left-edge-of-block entry-block) x)
          0)
        (unless first-entry-block (setq first-entry-block entry-block))
        (setq last-exit-block exit-block)
        (setq all-blocks (nconc all-blocks blocks))))

    (make-bpel-layout
      total-width max-height first-entry-block last-exit-block all-blocks)))



;;; Layout type 2
;;;
;;; Sequence Layout
;;;
;;; Lay out a sequence of layouts vertically

(defun perform-sequence-layout (child-nodes
                                 &optional (y-spacing bpel-layout-border-size))
  (let ((layouts
          (loop for node being each xml-element of child-nodes
                for layout = (convert-xml-bpel-activity-to-g2gl node)
                unless (bpel-layout-empty-p layout)
                  collect layout using gensym-cons
                else
                  do (reclaim-bpel-layout layout))))
    (prog1
        (arrange-layouts-vertically layouts y-spacing)

      (loop for last-exit-block = nil then exit-block
            for (nil nil entry-block exit-block nil) in layouts do
        (when last-exit-block
          (perform-connect-bpel-activities last-exit-block entry-block)))
      (reclaim-bpel-layouts layouts))))


;;; Layout type 3
;;;
;;; Parallel Layout
;;;
;;; Lay out child layouts in parallel branches with a split and join
;;; bar
;;;
;;; Used for:  flow, pick

(defun perform-parallel-layout (bpel-split-activity bpel-join-activity children)
  (let* ((split-layout
           (perform-activity-layout bpel-split-activity))
         (branch-layouts
           (loop for node being each xml-element of children
                 for layout = (convert-xml-bpel-activity-to-g2gl node)
                 unless (bpel-layout-empty-p layout)
                   collect layout using gensym-cons
                 else
                   do (reclaim-bpel-layout layout)))
         (branches-layout
           (arrange-layouts-horizontally branch-layouts))
         (join-layout
           (perform-activity-layout bpel-join-activity))
         (layouts
           (gensym-list split-layout branches-layout join-layout)))
    (prog1
        (arrange-layouts-vertically
          layouts
          (room-for-g2gl-connections (length branch-layouts)))

      (cond
        (branch-layouts
         (perform-branching-connections bpel-split-activity branch-layouts)
         (perform-joining-connections bpel-join-activity branch-layouts))
        (t
         ;; If there are no branches, connect the split bar directly to the join
         ;; bar, removing all the other loose ends first.
         (delete-g2gl-output-connections bpel-split-activity)
         (delete-g2gl-input-connections bpel-join-activity)
         (connect-loose-end-to-block
           (output-end-object
             (g2gl-activity-add-standard-connection
               bpel-split-activity 'output 'bottom))
           bpel-join-activity 'top
           (midpoint-position-of-side-of-block 'top bpel-join-activity))))

      (reclaim-bpel-layouts branch-layouts)
      (reclaim-bpel-layouts layouts))))


;;; Layout type 4
;;;
;;; Sub-activities layout
;;;
;;; Lay out child activities to the right of a main activity
;;;
;;; Used for:  while

(defun perform-sub-activities-layout (main-activity children)
  (let* ((while-object-layout
           (perform-activity-layout main-activity))
         (while-body-layout
           (perform-sequence-layout children))
         (while-body-entry-block
           (bpel-layout-entry-activity while-body-layout))
         (while-body-exit-block
           (bpel-layout-exit-activity while-body-layout))
         (while-body-output-connection-x
           (if while-body-exit-block
               (midline-x-of-block while-body-exit-block)
             0))
         (while-object-output-connection-y
           (roundw (height-of-block main-activity) 3))
         (while-body-y-offset
           (+w default-stub-length while-object-output-connection-y))
         (layouts
           (gensym-list while-object-layout while-body-layout)))

    ;; Put the while-body to the right of the while object.
    (bpel-layout-bind
        (width height entry-block exit-block blocks)
        (arrange-layouts-horizontally layouts)
      (declare (ignore entry-block exit-block))

      (unless (bpel-layout-empty-p while-body-layout)
        ;; If the while body is empty, skip everything below and leave the stubs
        ;; as a reminder that this is not valid BPEL.

        ;; Remove the input and output stubs from the while body.
        (delete-connection
          (g2gl-activity-default-input-connection while-body-entry-block))
        (delete-connection
          (g2gl-activity-default-output-connection while-body-exit-block))

        ;; Shift the while body down to make room for the input connection to
        ;; come in from the top.
        (move-existing-layout-to-x-y
          while-body-entry-block
          (bpel-layout-blocks while-body-layout)
          (left-edge-of-block while-body-entry-block)
          while-body-y-offset)

        ;; Adjust the total height for this downshift if needed.
        (setf height
              (maxw height (+w (bpel-layout-height while-body-layout)
                               while-body-y-offset)))

        ;; Connect the while object to the while body.
        (connect-loose-end-to-block
          (bpel-activity-right-output-object main-activity)
          while-body-entry-block 'top
          (halfw (width-of-block while-body-entry-block)))

        ;; Connect the while body to the while block.
        (let ((back-connection
                (connect-loose-end-to-block
                  (bpel-activity-right-input-object main-activity)
                  while-body-exit-block 'bottom
                  (halfw (width-of-block while-body-exit-block)))))
          (clean-up-connection
            back-connection
            (gensym-list
              ;; Go down to the bottom edge of the layout,
              default-stub-length
              ;; then over to the left edge of the layout.
              (-w (+w while-body-output-connection-x
                      (halfw bpel-layout-border-size))))
            'bottom 'right
            ;; Preserve the end positions.
            (get-position-on-side-given-end-position
              (input-end-position back-connection))
            (get-position-on-side-given-end-position
              (output-end-position back-connection))))

        ;; Add vertical room for the latter connection if needed.
        (setf height
              (maxw height
                    (+w (bottom-edge-of-block while-body-exit-block)
                        default-stub-length))))

      (reclaim-bpel-layouts layouts)

      (make-bpel-layout width height main-activity main-activity blocks))))


;;; Layout type 5
;;;
;;; Branch Layout
;;;
;;; Lay out child activities in branches without a branch bar
;;;
;;; Used for:  switch

(defun perform-branch-layout (xml-element branch-class join-class)
  (let* ((last-entry-block nil)
         (branch-layouts
           (loop for child being
                 each xml-element of (xml-node-child-nodes xml-element)
                 for layout = (convert-xml-bpel-activity-to-g2gl child)
                 unless (bpel-layout-empty-p layout)
                   collect layout using gensym-cons
                   and do (setq last-entry-block
                                (bpel-layout-entry-activity layout))
                 else
                   do (reclaim-bpel-layout layout)))
         (n-branches
           (length branch-layouts))
         (implicit-otherwise-p
           ;; If the rightmost branch entry block is a switch-fork, it's a
           ;; <case> element, which means there's an implicit empty <otherwise>
           ;; branch.
           (and last-entry-block
                (eq (class last-entry-block) branch-class)))
         (branches-layout
           ;; Put the branches side by side.
           (arrange-layouts-horizontally branch-layouts))
         (right-edge-of-last-entry-block
           ;; Save this position relative to branches-layout, for setting the
           ;; delta-or-deltas of the implicit-otherwise connection (see below).
           (if last-entry-block
               (right-edge-of-block last-entry-block)
             0))
         (join-bar (make-entity join-class))
         (join-bar-layout (perform-activity-layout join-bar))
         (layouts (gensym-list branches-layout join-bar-layout)))

    (when implicit-otherwise-p
      ;; Add room for the final else connection going down to the join bar.
      (incfw (bpel-layout-width branches-layout)
             (halfw bpel-layout-border-size))
      (incff n-branches))

    (prog1
        ;; Put the join bar at the bottom.
        (arrange-layouts-vertically
          layouts (room-for-g2gl-connections n-branches))

      ;; Connect the branch entry blocks from left to right.
      (loop for previous-entry-block = nil then entry-block
            for (nil nil entry-block nil nil) in branch-layouts do
        (when previous-entry-block
          ;; Delete the loose input connection from this entry block.
          (delete-connection
            (g2gl-activity-default-input-connection entry-block))
          ;; Connect the right output stub of the previous entry block to this
          ;; entry block.
          (connect-loose-end-to-block
            (bpel-activity-right-output-object previous-entry-block)
            entry-block 'left (midline-y-of-block entry-block))))

      (when implicit-otherwise-p
        (setq branch-layouts
              (nconc branch-layouts
                     (gensym-list
                       (make-bpel-layout 0 0 nil last-entry-block nil)))))

      ;; Connect all the exit blocks to the join bar.
      (perform-joining-connections join-bar branch-layouts)

      (when implicit-otherwise-p
        ;; Redirect the else connection of the last entry block around the last
        ;; layout.
        (clean-up-connection
          (bpel-activity-right-output-connection last-entry-block)
          (gensym-list
            (-w (bpel-layout-width branches-layout)
                right-edge-of-last-entry-block)
            (-w (top-edge-of-block join-bar)
                (midline-y-of-block last-entry-block)
                default-stub-length))
          'right 'top
          (halfw (height-of-block last-entry-block))
          (position-of-ith-g2gl-connection
            n-branches join-bar 'top n-branches)))

      (reclaim-bpel-layouts branch-layouts)
      (reclaim-bpel-layouts layouts))))

;;; Layout type 5
;;;
;;; Layout of flow-signal blocks
;;;

(defun perform-flow-signals-layout (children)
  (let ((layouts
          (loop for child being each xml-element of children
                when (xml-node-name-symbol-equals-p
                       child 'source bpel-xml-namespace-uri)
                  collect
                  (perform-activity-layout
                    (let ((link-block (make-entity 'g2gl-flow-signal))
                          (link-name
                            (xml-element-get-attribute-symbol
                              child "linkName")))
                      (change-slot-value
                        link-block 'g2gl-link-name link-name)
                      (initialize-g2gl-expression-slot-from-xml-attribute
                        link-block 'flow-signal-transition-condition
                        child "transitionCondition")
                      (collect-flow-links link-block link-name)
                      link-block))
                    using gensym-cons)))

    (prog1
        (arrange-layouts-vertically
          layouts (halfw bpel-layout-border-size))
      (loop for last-exit-block = nil then exit-block
            for (nil nil entry-block exit-block nil) in layouts do
        (when last-exit-block
          (perform-connect-bpel-activities last-exit-block entry-block)))
      (reclaim-bpel-layouts layouts))))


;;; Set the name of the entry-block from the "name" attribute of xml-element, if
;;; present, unless it already has one.  Add a flow gate above and flow signals
;;; below the layout for the BPEL activity represented by xml-element.  Set the
;;; flow gate's attributes from the "joinCondition" and "suppressJoinFailure"
;;; attributes of xml-element, if present (or inherited, in the latter case).
;;; The returned layout includes the original layout plus the flow blocks.

(defun add-standard-attributes-and-elements-to-g2gl-activity-layout
    (xml-element layout)
  (bpel-layout-bind (width height entry-block exit-block blocks) layout
    (let ((name (xml-element-get-attribute-symbol xml-element "name"))
          (children (xml-node-child-nodes xml-element))
          (spacing (halfw bpel-layout-border-size))
          (gate nil))

      (when name
        (unless (name-or-names-for-frame entry-block)
          (change-g2gl-object-name entry-block name)))

      (when children
        (loop for target being each xml-element of children
              when (xml-node-name-symbol-equals-p
                     target 'target bpel-xml-namespace-uri)
                do (unless gate (setq gate (make-entity 'g2gl-flow-gate)))
                   (collect-flow-links
                     gate
                     (xml-element-get-attribute-symbol target "linkName")))
        (when gate
          (initialize-g2gl-expression-slot-from-xml-attribute
            gate 'flow-gate-join-condition xml-element "joinCondition")
          (let ((suppress-join-failure
                  (xml-element-get-inherited-attribute
                    xml-element "suppressJoinFailure")))
            (when suppress-join-failure
              (change-the-text-of
                gate 'suppress-join-failure suppress-join-failure)))
          (bpel-layout-bind
            (gates-width gates-height first-gate last-gate gates)
            (perform-activity-layout gate)
            (declare (ignore gates-width)) ;assumed small enough to not matter
            ;; Put the gates centered above the entry-block.
            (move-existing-layout-to-x-y
              first-gate
              gates
              (-w (midline-x-of-block entry-block)
                  (midline-x-of-block first-gate))
              0)
            (move-existing-layout-to-x-y
              entry-block
              blocks
              (left-edge-of-block entry-block)
              (+w gates-height spacing))
            (perform-connect-bpel-activities last-gate entry-block)
            (setq height (+w gates-height spacing height))
            (setq entry-block first-gate)
            (setq blocks (nconc gates blocks))))

        (bpel-layout-bind
          (signals-width signals-height first-signal last-signal signals)
          (perform-flow-signals-layout children)
          (declare (ignore signals-width)) ;assumed small enough to not matter
          (declare (ignore signals-height))
          (when signals
            ;; Put the signals centered below the exit-block.
            (move-existing-layout-to-x-y
              first-signal
              signals
              (-w (midline-x-of-block exit-block)
                  (midline-x-of-block first-signal))
              (+w (bottom-edge-of-block exit-block) spacing))
            (perform-connect-bpel-activities exit-block first-signal)
            (setq height (maxw height (bottom-edge-of-block last-signal)))
            (setq exit-block last-signal)
            (setq blocks (nconc blocks signals)))))

      (make-bpel-layout width height entry-block exit-block blocks))))


;;; Layout an activity-with-body, with an optional arg variable at the top of
;;; the body subworkspace.

(defun perform-activity-with-body-layout
    (activity body-elements &optional arg-variable-name)
  (prog1 (perform-activity-layout activity)
    (let ((g2gl-body-being-laid-out (make-workspace 'kb-workspace))
          (g2gl-import-added-start-activity-p nil))
      (add-subworkspace g2gl-body-being-laid-out activity)
      (let ((layouts (gensym-list (perform-sequence-layout body-elements))))
        (when arg-variable-name
          (let ((var (make-entity 'g2gl-arg-variable)))
            (change-g2gl-variable-name var arg-variable-name)
            (gensym-push (perform-activity-layout var) layouts)))
        (let ((layout (arrange-layouts-vertically layouts)))
          (perform-trim-last-activity-connections layout)
          (reclaim-bpel-layouts layouts)
          (reclaim-bpel-layout-and-blocks layout)))
      (shrink-wrap-workspace g2gl-body-being-laid-out))))


;;; Convert <receive>, or <onMessage> inside <pick>, to g2gl-receive.

(defun convert-xml-bpel-receive-to-g2gl (xml-element)
  (let ((receive-activity
          (make-entity 'g2gl-receive))
        (create-instance
          (xml-element-get-attribute xml-element "createInstance")))
    (change-slot-value
      receive-activity 'g2gl-message-variable-name
      (xml-element-get-attribute-symbol xml-element "variable"))
    (when create-instance
      (change-the-text-of
        receive-activity 'this-is-an-instantiation-trigger-for-receive
        create-instance))
    (calculate-g2gl-operation-attributes xml-element receive-activity)
    (change-slot-value
      receive-activity 'g2gl-correlations
      (calculate-g2gl-correlations xml-element))
    (perform-activity-layout receive-activity)))


;;; Convert <wait>, or <onAlarm> inside <pick>, to g2gl-wait.

(defun convert-xml-bpel-wait-to-g2gl (xml-element)
  (let ((wait-activity (make-entity 'g2gl-wait)))
    (initialize-g2gl-alarm-time-from-xml-element wait-activity xml-element)
    (perform-activity-layout wait-activity)))


;;; Convert <onMessage> inside <eventHandlers> to g2gl-message-event-handler.

(defun convert-message-event-handler-to-g2gl (element)
  (let ((handler (make-entity 'g2gl-message-event-handler)))
    (calculate-g2gl-operation-attributes element handler)
    (change-slot-value
      handler 'g2gl-message-variable-name
      (xml-element-get-attribute-symbol element "variable"))
    (change-slot-value
      handler 'g2gl-correlations (calculate-g2gl-correlations element))
    (perform-activity-with-body-layout handler (xml-node-child-nodes element))))


;;; Convert <onAlarm> inside <eventHandlers> to g2gl-alarm-event-handler.

(defun convert-alarm-event-handler-to-g2gl (element)
  (let ((handler (make-entity 'g2gl-alarm-event-handler)))
    (initialize-g2gl-alarm-time-from-xml-element handler element)
    (perform-activity-with-body-layout handler (xml-node-child-nodes element))))


;;; Convert a child of <eventHandlers> to a g2gl-event-handler.

(defun convert-event-handler-to-g2gl (element)
  (xml-node-name-symbol-case element
    (bpel-xml-namespace-uri
      (on-message
        (convert-message-event-handler-to-g2gl element))
      (on-alarm
        (convert-alarm-event-handler-to-g2gl element)))))


;;; Convert <eventHandlers> to g2gl-event-handlers laid out vertically.

(defun convert-event-handlers-to-g2gl (element)
  (let ((layouts
          (loop for handler-element being
                each xml-element of (xml-node-child-nodes element)
                for layout = (convert-event-handler-to-g2gl handler-element)
                when (bpel-layout-empty-p layout)
                  do (reclaim-bpel-layout layout)
                else collect layout using gensym-cons)))
    (prog1 (arrange-layouts-vertically layouts)
      (reclaim-bpel-layouts layouts))))


;;; The function `convert-xml-bpel-flow-to-g2gl' converts an XML element
;;; representing a flow activity to the corresponding flowchart of
;;; G2GL activities on the current workspace.

(defun convert-xml-bpel-flow-to-g2gl (element)
  (let ((flow-split (make-entity 'g2gl-flow-split))
        (flow-join (make-entity
                     (xml-node-name-symbol-case element
                       (bpel-xml-namespace-uri
                         (flow 'g2gl-flow-sync))
                       (g2gl-xml-namespace-uri
                         (flow-discriminator 'g2gl-flow-discriminator)
                         (n-out-of-m-flow 'g2gl-n-out-of-m-flow-join)
                         (flow-terminator 'g2gl-flow-terminator)))))
        (links? (xml-node-get-child-by-name-symbol
                  element 'links bpel-xml-namespace-uri)))
    (when links?
      (change-slot-value
        flow-split 'g2gl-link-names
        (loop for child being each xml-element of (xml-node-child-nodes links?)
              when (xml-node-name-symbol-equals-p
                     child 'link bpel-xml-namespace-uri)
                collect (xml-element-get-attribute-symbol child "name")
                  using slot-value-cons)))
    (when (frame-of-class-p flow-join 'g2gl-n-out-of-m-flow-join)
      (let ((n-string? (xml-element-get-attribute element "n")))
        (when n-string?
          (change-the-text-of
            flow-join 'number-of-branches-to-synchronize n-string?))))
    (perform-parallel-layout
      flow-split flow-join (xml-node-child-nodes element))))



;;; The main recursive function for the layout algorithm
;;;
;;; convert-xml-bpel-activity-to-g2gl (xml-element)
;;;  = bpel-layout

(defun convert-xml-bpel-activity-to-g2gl-1 (xml-element)
  ;; Cases for different element types. Abstracting these out by
  ;; using a macro might be a good idea later -ajs 11/12/2004

  (xml-node-name-symbol-case xml-element
    (bpel-xml-namespace-uri
      (sequence
        (perform-sequence-layout (xml-node-child-nodes xml-element)))
      ((partner-links correlation-sets variables)
       (perform-sequence-layout (xml-node-child-nodes xml-element)
                                bpel-variable-y-spacing-size))
      (partner-link
        (let* ((g2gl-partner-link-variable
                 (make-entity 'g2gl-partner-link-variable)))
          (change-slot-value g2gl-partner-link-variable 'g2gl-variable-type
                             (calculate-partner-link-variable-type xml-element))
          (perform-activity-layout g2gl-partner-link-variable)))
      (partners
        (change-slot-value
          (parent-of-subworkspace? g2gl-body-being-laid-out)
          'g2gl-partner-link-groups
          (loop for partner being each xml-element of
                (xml-node-child-nodes xml-element)
                when (xml-node-name-symbol-equals-p
                       partner 'partner bpel-xml-namespace-uri)
                  collect
                  (slot-value-cons
                    (xml-element-get-attribute-symbol partner "name")
                    (loop for link being each xml-element of
                          (xml-node-child-nodes partner)
                          when (xml-node-name-symbol-equals-p
                                 link 'partner-link bpel-xml-namespace-uri)
                            collect
                            (xml-element-get-attribute-symbol link "name")
                              using slot-value-cons))
                    using slot-value-cons))
        (make-empty-bpel-layout))
      (variable
        (let* ((g2gl-variable
                 (make-entity 'g2gl-local-variable)))
          (change-slot-value g2gl-variable 'g2gl-variable-type
                             (calculate-g2gl-variable-type xml-element))
          (initialize-g2gl-expression-slot-from-xml-attribute
            g2gl-variable 'default-value-for-g2gl-variable
            xml-element "initialValue" g2gl-xml-namespace-uri)
          (perform-activity-layout g2gl-variable)))
      (correlation-set
        (let ((var (make-entity 'g2gl-correlation-variable))
              (properties
                (xml-element-get-attribute-symbols xml-element "properties")))
          (when properties
            (change-slot-value
              var 'g2gl-variable-type
              (slot-value-cons 'conversation-key-attributes properties)))
          (perform-activity-layout var)))
      (fault-handlers
        (perform-trim-last-activity-connections
          (perform-sequence-layout (xml-node-child-nodes xml-element))))
      ((catch catch-all)
       (let ((g2gl-fault-handler (make-entity 'g2gl-fault-handler)))
         (change-slot-value
           g2gl-fault-handler 'g2gl-fault-name
           (if (eq (xml-node-local-name-symbol xml-element) 'catch-all)
               0
               (xml-element-get-attribute-symbol xml-element "faultName")))
         (perform-activity-with-body-layout
           g2gl-fault-handler (xml-node-child-nodes xml-element)
           (xml-element-get-attribute-symbol xml-element "faultVariable"))))
      (compensation-handler
        (let ((handler (make-entity 'g2gl-compensation-handler)))
          (perform-activity-with-body-layout
            handler (xml-node-child-nodes xml-element))))
      (event-handlers
        (convert-event-handlers-to-g2gl xml-element))
      (assign
        (let ((assign-activity
                (make-entity 'g2gl-assign))
              (assignment-expressions
                (calculate-g2gl-assignment-expressions
                  xml-element
                  g2gl-expression-language-symbol
                  g2gl-query-language-symbol)))
          (unless (change-the-text-of
                    assign-activity 'g2gl-assignments
                    (copy-text-string assignment-expressions))
            ;; This should only happen if there was an error in an
            ;; "expression" attribute in a <from> element.
            ;; TO DO: report the actual attribute that's causing the error,
            ;; and keep the rest of the assignments.
            (add-g2gl-import-error
              (tformat-text-string
                ;; TO DO: file name if any
                "~%Line ~a: G2GL expression cannot be parsed: ~s"
                (xml-node-get-line xml-element)
                assignment-expressions)))
          (reclaim-text-string assignment-expressions)
          (perform-activity-layout assign-activity)))
      (invoke
        (let ((invoke-activity (make-entity 'g2gl-invoke)))
          (change-slot-value
            invoke-activity
            'g2gl-message-variable-name
            (xml-element-get-attribute-symbol xml-element "inputVariable"))
          (change-slot-value
            invoke-activity
            'g2gl-response-variable-name
            (xml-element-get-attribute-symbol xml-element "outputVariable"))
          (calculate-g2gl-operation-attributes xml-element invoke-activity)
          (change-slot-value
            invoke-activity 'g2gl-correlations
            (calculate-g2gl-correlations xml-element))

          (let* ((invoke-layout (perform-activity-layout invoke-activity))
                 (handler-layouts
                   ;; Collect the local handlers.
                   (loop for child being each xml-element
                         of (xml-node-child-nodes xml-element)
                         when (and (xml-node-namespace-uri-equals-p
                                     child bpel-xml-namespace-uri)
                                   (memq (xml-node-local-name-symbol child)
                                         '(catch catch-all
                                           compensation-handler)))
                           collect (convert-xml-bpel-activity-to-g2gl child)
                             using gensym-cons)))
            (if handler-layouts
                ;; Layout the local handlers vertically.
                (let* ((handlers-layout (arrange-layouts-vertically
                                          handler-layouts))
                       (layouts (gensym-list invoke-layout handlers-layout))
                       (layout
                         ;; Put them to the right of the invoke block.
                         (arrange-layouts-horizontally
                           layouts
                           (room-for-g2gl-connections
                             (length handler-layouts) 'right))))
                  (setf (bpel-layout-exit-activity layout) invoke-activity)
                  ;; Connect them to the right side of the invoke block.
                  (perform-branching-connections
                    invoke-activity handler-layouts 'right)
                  ;; Make the top connection go straight across instead of
                  ;; bending down to the middle of the left side of the
                  ;; handler.
                  (let ((top-conn (g2gl-activity-default-input-connection
                                    (bpel-layout-entry-activity
                                      handlers-layout))))
                    (setf (output-end-position top-conn)
                          (combine-side-and-position-on-side-for-end-position
                            'left (get-position-on-side-given-end-position
                                    (input-end-position top-conn)))))
                  (reclaim-bpel-layouts handler-layouts)
                  (reclaim-bpel-layouts layouts)
                  layout)
                ;; Else: no handlers, just the invoke.
                invoke-layout))))
      (receive
        (convert-xml-bpel-receive-to-g2gl xml-element))
      (reply
        (let ((reply-activity (make-entity 'g2gl-reply)))
          (change-slot-value
            reply-activity
            'g2gl-message-variable-name
            (xml-element-get-attribute-symbol xml-element "variable"))
          (calculate-g2gl-operation-attributes xml-element reply-activity)
          (change-slot-value
            reply-activity 'fault-name-for-reply
            (xml-element-get-attribute-symbol xml-element "faultName"))
          (change-slot-value
            reply-activity 'g2gl-correlations
            (calculate-g2gl-correlations xml-element))
          (perform-activity-layout reply-activity)))
      (throw
          (let ((activity (make-entity 'g2gl-throw)))
            (change-slot-value
              activity 'fault-name-for-throw
              (xml-element-get-attribute-symbol xml-element "faultName"))
            (change-slot-value
              activity 'fault-data-g2gl-variable-name
              (xml-element-get-attribute-symbol xml-element "faultVariable"))
            (perform-activity-layout activity)))
      (terminate
        (perform-activity-layout (make-entity 'g2gl-exit)))
      (wait
        (convert-xml-bpel-wait-to-g2gl xml-element))
      (empty
        (perform-activity-layout (make-entity 'g2gl-empty)))
      (scope
        (let ((scope-activity
                (make-entity 'g2gl-scope))
              (variable-access-serializable
                (xml-element-get-attribute
                  xml-element "variableAccessSerializable")))
          (when variable-access-serializable
            (change-the-text-of
              scope-activity 'variable-access-serializable
              variable-access-serializable))
          (perform-activity-with-body-layout
            scope-activity (xml-node-child-nodes xml-element))))
      (flow
        (convert-xml-bpel-flow-to-g2gl xml-element))
      (pick
        (let ((pick-activity
                (make-entity 'g2gl-pick))
              (pick-join
                (make-entity 'g2gl-pick-join))
              (create-instance
                (xml-element-get-attribute xml-element "createInstance")))
          (when create-instance
            (change-the-text-of
              pick-activity 'this-is-an-instantiation-trigger-for-pick
              create-instance))
          (perform-parallel-layout
            pick-activity pick-join
            (xml-node-child-nodes xml-element))))
      (switch
        (perform-branch-layout xml-element 'g2gl-switch-fork 'g2gl-switch-join))
      (case
          (let* ((fork
                   (make-entity 'g2gl-switch-fork))
                 (fork-layout
                   (perform-activity-layout fork))
                 (case-activity-layout
                   (perform-sequence-layout (xml-node-child-nodes xml-element)))
                 (layouts
                   (gensym-list fork-layout case-activity-layout)))
            (initialize-g2gl-expression-slot-from-xml-attribute
              fork 'switch-fork-condition xml-element "condition")
            (unless (bpel-layout-empty-p case-activity-layout)
              (perform-connect-bpel-activities
                fork (bpel-layout-entry-activity case-activity-layout)))
            (prog1 (arrange-layouts-vertically layouts)
              (reclaim-bpel-layouts layouts))))
      (while
          (let ((while-activity (make-entity 'g2gl-while)))
            (initialize-g2gl-expression-slot-from-xml-attribute
              while-activity 'while-iteration-condition xml-element "condition")
            (perform-sub-activities-layout
              while-activity (xml-node-child-nodes xml-element))))
      (compensate
        (let ((activity (make-entity 'g2gl-compensate)))
          (change-slot-value
            activity 'scope-name-for-compensate-activity
            (xml-element-get-attribute-symbol xml-element "scope"))
          (perform-activity-layout activity)))
      ((on-message on-alarm)
       (let ((handler-layout
               (case (xml-node-local-name-symbol xml-element)
                 (on-message
                  (convert-xml-bpel-receive-to-g2gl xml-element))
                 (on-alarm
                  (convert-xml-bpel-wait-to-g2gl xml-element))))
             (activity-layout
               (perform-sequence-layout
                 (xml-node-child-nodes xml-element))))
         (if (not (bpel-layout-empty-p activity-layout))
             (let ((layouts (gensym-list handler-layout activity-layout)))
               (perform-connect-bpel-activities
                 (bpel-layout-exit-activity handler-layout)
                 (bpel-layout-entry-activity activity-layout))
               (prog1 (arrange-layouts-vertically layouts)
                 (reclaim-bpel-layouts layouts)))
             (prog1 handler-layout
               (reclaim-bpel-layout activity-layout)))))
      ((otherwise)                        ;explicitly match the symbol OTHERWISE!
       (perform-sequence-layout (xml-node-child-nodes xml-element)))
      )
    (g2gl-xml-namespace-uri
      (start                                ; start removed in 8.1r0, post 8.1b0
        (perform-activity-layout (make-entity 'g2gl-empty)))
      (do
        (let ((activity (make-entity 'g2gl-do)))
          (initialize-g2gl-expression-slot-from-xml-attribute
            activity 'g2gl-statements xml-element "expression")
          (perform-activity-layout activity)))
      (call
        (let ((activity (make-entity 'g2gl-call)))
          (initialize-g2gl-expression-slot-from-xml-attribute
            activity 'g2gl-procedure-call-statement xml-element "expression")
          (perform-activity-layout activity)))
      (break
        (perform-activity-layout (make-entity 'g2gl-break)))
      ((flow-discriminator n-out-of-m-flow flow-terminator)
       (convert-xml-bpel-flow-to-g2gl xml-element))
      (return
        (let ((activity (make-entity 'g2gl-return)))
          (initialize-g2gl-expression-slot-from-xml-attribute
            activity 'g2gl-values-expression xml-element "expression")
          (perform-activity-layout activity)))
      (arg-variables
        (perform-sequence-layout (xml-node-child-nodes xml-element)
                                 bpel-variable-y-spacing-size))
      (arg-variable
        (let ((variable (make-entity 'g2gl-arg-variable)))
          (change-slot-value
            variable 'g2gl-variable-type
            (calculate-g2gl-variable-type xml-element))
          (initialize-g2gl-expression-slot-from-xml-attribute
            variable 'default-value-for-g2gl-variable
            xml-element "initialValue")
          (perform-activity-layout variable)))
      )))

(defun convert-xml-bpel-activity-to-g2gl (xml-element)
  (let ((layout (convert-xml-bpel-activity-to-g2gl-1 xml-element)))
    (if (bpel-layout-empty-p layout)
        layout
        (add-standard-attributes-and-elements-to-g2gl-activity-layout
          xml-element layout))))


;;; Entry function for the layout algorithm

;;; convert-xml-bpel-process-to-g2gl (xml-document)
;;;  = (g2-bpel-process)

(defun convert-xml-bpel-process-to-g2gl (xml-document)
  (let ((process-element
          (xml-node-get-child-by-name-symbol
            xml-document 'process bpel-xml-namespace-uri)))
    (unless process-element
      (add-g2gl-import-error
        (tformat-text-string "No process element found in XML namespace ~a"
                             bpel-xml-namespace-uri))
      (return-from convert-xml-bpel-process-to-g2gl nil))

    (let* ((process-name-symbol
             (xml-element-get-attribute-symbol process-element "name"))
           (bpel-process
             (make-entity 'g2gl-process))
           (current-g2gl-definition        ;special
             bpel-process)
           (g2gl-body-being-laid-out
             (make-workspace 'kb-workspace))
           (g2gl-target-namespace
             (xml-element-get-attribute
               process-element
               "targetNamespace"))
           (query-language-uri
             (xml-element-get-attribute
               process-element
               "queryLanguage"))
           (expression-language-uri
             (xml-element-get-attribute
               process-element
               "expressionLanguage"))
           (enable-instance-compensation
             (xml-element-get-attribute
               process-element
               "enableInstanceCompensation"))
           (this-is-an-abstract-process
             (xml-element-get-attribute
               process-element
               "abstractProcess"))
           (g2gl-expression-language-symbol
             (check-bpel-language-uri expression-language-uri 'expression))
           (g2gl-query-language-symbol
             (check-bpel-language-uri query-language-uri 'query)))

      (let ((allow-name-box-creation-without-workspace t))
        (change-slot-value
          bpel-process 'name-or-names-for-frame process-name-symbol))

      (when g2gl-target-namespace
        (change-slot-value bpel-process 'g2gl-target-namespace
                           g2gl-target-namespace))

      (when enable-instance-compensation
        (change-the-text-of bpel-process 'enable-instance-compensation
                            enable-instance-compensation))
      (when this-is-an-abstract-process
        (change-the-text-of bpel-process 'this-is-an-abstract-process
                            this-is-an-abstract-process))

      (add-subworkspace g2gl-body-being-laid-out bpel-process)

      (let ((layout (perform-sequence-layout
                      (xml-node-child-nodes process-element))))
        (perform-trim-last-activity-connections layout)
        (reclaim-bpel-layout-and-blocks layout))

      (perform-connect-flow-links)

      (shrink-wrap-workspace g2gl-body-being-laid-out)

      (change-slot-value g2gl-body-being-laid-out
                         'name-or-names-for-frame
                         (calculate-bpel-process-workspace-name
                           process-name-symbol))

      (when query-language-uri
        (reclaim-text-string query-language-uri))
      (when expression-language-uri
        (reclaim-text-string expression-language-uri))

      bpel-process)))


;;; Import a G2GL process from an XML document.
;;;
;;; If source-type is FILE, document-source is a text containing the path to a
;;; file containing the document.
;;;
;;; If source-type is TEXT, document-source is a text containing the document
;;; itself.
;;;
;;; A stack error is raised if the process can not be imported.
;;; Warnings (if any) are sent to the operator logbook.

(defun import-g2gl-process-from-xml (document-source source-type)
  (let ((source-string (evaluation-text-value document-source))
        (g2gl-import-errors nil)
        (g2gl-import-flow-link-p-list nil)
        (g2gl-import-added-start-activity-p nil)
        g2gl-process error-message)

    (reclaiming-xml-structures
      (let ((document
              (case source-type
                (file (xml-read-file source-string))
                (text (xml-read-string source-string)))))
        (add-g2gl-import-errors (xml-get-errors))
        (when document
          (setf g2gl-process (convert-xml-bpel-process-to-g2gl document)))))

    (when g2gl-import-errors
      (setf error-message
            (twith-output-to-text-string
              (tformat "While importing a G2GL process from ~s:~%"
                       (if (eq source-type 'file) source-string 'XML))
              (loop for error in g2gl-import-errors do (twrite-string error)))))

    (reclaim-gensym-tree-with-text-strings g2gl-import-errors)
    (reclaim-gensym-list g2gl-import-flow-link-p-list)

    (unless g2gl-process
      ;; Failed to create a G2GL process, raise a stack error.
      (write-stack-error cached-top-of-stack
        (when error-message
          (twrite-string error-message)
          (reclaim-text-string error-message))
        ;; OTHER CLEANUP HERE PROBABLY NECESSARY!!  E.g., deleting blocks
        ;; created, etc.!
        ))

    (when error-message
      ;; Success, but with warnings-- notify the user.
      (with-user-notification ()
        (twrite-string error-message)
        (reclaim-text-string error-message)))

    ;; The following two are in imitation of make-transient-item.  Added
    ;; the second of these to fix HQ-4998780 "G2GL: imported process not
    ;; on a workspace has inactive subworkspace".  (MHD 4/4/05)
    (set-transient-and-propagate g2gl-process nil)
    (funcall-method 'activate-if-possible-and-propagate g2gl-process)

    g2gl-process))


(defun-for-system-procedure g2-import-g2gl-process-from-xml (file-path)
  (import-g2gl-process-from-xml file-path 'file))

(defun-for-system-procedure g2-import-g2gl-process-from-xml-text (text-input)
  (import-g2gl-process-from-xml text-input 'text))



;;; Exporting BPEL Processes
;;;
;;; convert-g2-bpel-to-xml-bpel(g2-bpel-process) = (document)
;;;
;;; After conversion the document can be written to file using
;;; the xml-write-file(document, filepath) function.



;;; Collect the body elements of a G2GL body into separate gensym-lists, which
;;; are returned as multiple values:
;;;   arg variables
;;;   partner link variables
;;;   correlation variables
;;;   local variables
;;;   fault handlers
;;;   compensation handlers
;;;   event handlers
;;;   initial activities
;;; Each list is sorted by position in the body from top to bottom.  Default
;;; fault handlers (i.e. "catch all") are sorted to the end of the list of fault
;;; handlers.  Message event handlers are sorted before alarm event handlers.

(defun collect-g2gl-body-elements (body)
  (loop for block being each subblock of body
        for class-of-block = (class block)
        when (eq class-of-block 'g2gl-arg-variable)
          collect block into arg-variables using gensym-cons
        when (eq class-of-block 'g2gl-partner-link-variable)
          collect block into partner-link-variables using gensym-cons
        when (eq class-of-block 'g2gl-correlation-variable)
          collect block into correlation-variables using gensym-cons
        when (eq class-of-block 'g2gl-local-variable)
          collect block into local-variables using gensym-cons
        when (and (eq class-of-block 'g2gl-fault-handler)
                  (not (block-has-connected-input-connections-p block)))
          when (eql (g2gl-fault-name block) 0)
            collect block into default-fault-handlers using gensym-cons
          else
            collect block into non-default-fault-handlers using gensym-cons
        when (and (eq class-of-block 'g2gl-compensation-handler)
                  (not (block-has-connected-input-connections-p block)))
          collect block into compensation-handlers using gensym-cons
        when (eq class-of-block 'g2gl-message-event-handler)
          collect block into message-event-handlers using gensym-cons
        when (eq class-of-block 'g2gl-alarm-event-handler)
          collect block into alarm-event-handlers using gensym-cons
        when (and (frame-of-class-p block 'g2gl-activity)
                  (not (frame-of-class-p block 'g2gl-handler))
                  (g2gl-activity-is-an-entry-activity-p block))
          collect block into initial-activities using gensym-cons
        finally
          (return
            (values
              (sort-blocks-from-top-to-bottom arg-variables)
              (sort-blocks-from-top-to-bottom partner-link-variables)
              (sort-blocks-from-top-to-bottom correlation-variables)
              (sort-blocks-from-top-to-bottom local-variables)
              (nconc (sort-blocks-from-top-to-bottom non-default-fault-handlers)
                     (sort-blocks-from-top-to-bottom default-fault-handlers))
              (sort-blocks-from-top-to-bottom compensation-handlers)
              (nconc (sort-blocks-from-top-to-bottom message-event-handlers)
                     (sort-blocks-from-top-to-bottom alarm-event-handlers))
              (sort-blocks-from-top-to-bottom initial-activities)))))

(defun get-initial-activity-from-process-body (g2gl-process-body)
  (loop for block being each subblock of g2gl-process-body
        when (and (frame-of-class-p block 'g2gl-activity)
                  (not (frame-of-class-p block 'g2gl-handler))
                  (g2gl-activity-is-an-entry-activity-p block))
          return block))


;;; Collect the local handlers of a G2GL invoke activity into a gensym-list,
;;; sorted in the following order:
;;;   non-default fault handlers
;;;   default fault handlers
;;;   compensation handlers
;;; Each kind of handler is sorted by position in the body from top to bottom.
;;;
;;; Handlers connected to the left or right side of the activity are considered
;;; local, even though they're only actually legal on the right side.

(defun collect-g2gl-invoke-local-handlers (invoke)
  (loop for out-conn being each output-connection of invoke
        on-side-or-sides '(left right)
        for block = (output-end-object out-conn)
        for class-of-block = (class block)
        when (eq class-of-block 'g2gl-fault-handler)
          when (eql (g2gl-fault-name block) 0)
            collect block into default-fault-handlers using gensym-cons
          else
            collect block into non-default-fault-handlers using gensym-cons
        when (eq class-of-block 'g2gl-compensation-handler)
          collect block into compensation-handlers using gensym-cons
        finally
          (return
            (nconc
              (sort-blocks-from-top-to-bottom non-default-fault-handlers)
              (sort-blocks-from-top-to-bottom default-fault-handlers)
              (sort-blocks-from-top-to-bottom compensation-handlers)))))


;; The fault variable name of a fault handler is the name of the first (should
;; be only!) arg variable on its body workspace.
(defun g2gl-fault-variable-name (fault-handler)
  (let ((body (car (subworkspaces fault-handler))))
    (when body
      (loop for block being each subblock of body
            when (frame-of-class-p block 'g2gl-arg-variable)
              return (get-primary-name-for-frame-if-any block)))))


(defun get-next-g2gl-activity-from-g2gl-activity (g2gl-activity)
  (bpel-activity-default-output-object g2gl-activity))


(defun get-next-g2gl-activities-from-g2gl-activity (g2gl-activity)
  (let ((output-connections
          (list-g2-bpel-activity-output-connections g2gl-activity)))
    (when output-connections
      (sort-list
        (loop for connection in output-connections
              collect (output-end-object-internal connection)
                using gensym-cons)
        #'left-edge-of-block-lessp nil))))


;;; Set the partnerLink, portType, and operation attributes of a BPEL XML
;;; invoke, receive, reply, or message event handler element from the
;;; corresponding slots of a G2GL object.

(defun set-g2gl-operation-attributes-on-element
    (g2gl-activity xml-element)
  (xml-element-set-attribute-symbol
    xml-element "partnerLink" (g2gl-partner-link-variable-name g2gl-activity))

  (let ((port-type (g2gl-port-type g2gl-activity)))
    (when port-type
      ;; The port type is the name of a g2gl-port-type-definition.
      ;; Export it to the G2 datatypes namespace.  It should maybe be in a
      ;; special G2 port types namespace, or ideally it should be part of a WSDL
      ;; description and use the target namespace of that.  -dougo, 5/23/05
      (let* ((port-type-string
               (convert-symbol-to-xml-name port-type))
             (port-type-qname
               (twith-output-to-text-string
                 (twrite-symbol g2-datatypes-xml-namespace-prefix)
                 (twrite-string ":")
                 (twrite-string port-type-string))))
        (xml-element-set-attribute
          xml-element "portType" port-type-qname)
        (reclaim-wide-string port-type-string)
        (reclaim-wide-string port-type-qname))))

    (xml-element-set-attribute-symbol
      xml-element "operation" (g2gl-operation-name g2gl-activity)))


;;; Set the messageType, type, or element attribute on a variable element.

(defun set-g2gl-type-specifier-attribute-on-element (variable element)
  (let ((type-spec (g2gl-variable-type variable))
        attribute-name type prefix?)

    (if (and type-spec (symbolp type-spec))
        ;; G2 primitive type, convert to XML Schema built-in type.
        (progn
          (setq attribute-name "type")
          (setq type
                (convert-g2-primitive-type-to-xsd-primitive-type type-spec))
          (setq prefix? xsd-datatypes-xml-namespace-prefix))

        (case (first type-spec)
          (class
           ;; G2 class, which may be a message type or an element.
           (setq type (second type-spec))
           (setq attribute-name (if (subclassp type 'g2gl-message)
                                    "messageType" "element"))
           (setq prefix? g2-datatypes-xml-namespace-prefix))
          ;; TO DO: the name and namespace should refer to a WSDL or XML
          ;; Schema definition somewhere, instead of just using the G2 class
          ;; name directly. -dougo, 4/24/05

          (xml-type
           ;; Reference to an external XML type.  In general, we have no way
           ;; of knowing what kind of type it is, so just assume it's a
           ;; message type.
           (setq attribute-name "messageType")
           (setq type (g2gl-xml-type-specifier-type type-spec))
           (setq prefix? (g2gl-xml-type-specifier-prefix type-spec))

           ;; The namespace may give us a clue...
           (let ((namespace?
                   (xml-node-lookup-namespace-symbol element prefix?)))
             (when namespace?
               (let ((uri (xml-namespace-get-uri namespace?)))
                 (when (string=w uri xsd-datatypes-xml-namespace-uri)
                   ;; An XML Schema built-in datatype, hence simple.
                   (setq attribute-name "type"))
                 (reclaim-text-string uri)))))))

    (when attribute-name
      (let ((type-string (convert-symbol-to-xml-name type)))
        (when prefix?
          (let ((prefix-string (convert-symbol-to-xml-name prefix?)))
            (setq type-string
                  (prog1 (twith-output-to-text-string
                           (tformat "~a:~a" prefix-string type-string))
                    (reclaim-text-string prefix-string)
                    (reclaim-text-string type-string)))))
        (xml-element-set-attribute element attribute-name type-string)
        (reclaim-text-string type-string)))))


(defun set-g2gl-partner-link-attributes-on-element
    (partner-link-variable xml-element)
  (let ((variable-type (g2gl-variable-type partner-link-variable)))
    (when (listp variable-type)
      (let ((partner-link-type nil)
            (my-role nil)
            (partner-role nil))
        (case (first variable-type)
          (role-names-plus-partner-link-type
           (setq my-role (second variable-type))
           (setq partner-role (third variable-type))
           (setq partner-link-type (fourth variable-type)))
          (port-types
           ;; Use the port types as the role names.
           (setq my-role (second variable-type))
           (setq partner-role (third variable-type))))
        (when partner-link-type
          (xml-element-set-attribute
            xml-element "partnerLinkType"
            (convert-symbol-to-xml-name partner-link-type)))
        (when my-role
          (xml-element-set-attribute
            xml-element "myRole"
            (convert-symbol-to-xml-name my-role)))
        (when partner-role
          (xml-element-set-attribute
            xml-element "partnerRole"
            (convert-symbol-to-xml-name partner-role)))))))


;;; Set the alarm time attributes of an XML element from the corresponding slot
;;; values of a G2GL object.

(defun set-g2gl-alarm-time-attributes-on-element (object element)
  (let ((attr-name (case (type-of-g2gl-alarm-time-expression object)
                     (duration-expression "for")
                     (deadline-expression "until"))))
    (xml-element-set-attribute-from-text-slot-value
      element attr-name (duration-or-deadline-expression object))))



(defun collect-flow-gates-for-bpel-activity (bpel-activity)
  (loop as input-object = (bpel-activity-default-input-object bpel-activity)
                         then (bpel-activity-default-input-object input-object)
        while (and input-object
                   (frame-of-class-p input-object 'g2gl-flow-gate)
                   (not (memq input-object result)))
        collect input-object into result using gensym-cons
        finally (return result)))


(defun collect-flow-signals-for-bpel-activity (bpel-activity)
  (loop as output-object = (bpel-activity-default-output-object bpel-activity)
                         then (bpel-activity-default-output-object output-object)
        while (and output-object
                   (frame-of-class-p output-object 'g2gl-flow-signal)
                   (not (memq output-object result)))
        collect output-object into result using gensym-cons
        finally (return result)))


;;; The topmost flow gate connected to the top of a g2gl-activity object, or nil
;;; if there are none.

(defun topmost-flow-gate-for-g2gl-activity (g2gl-activity)
  (let ((flow-gates (collect-flow-gates-for-bpel-activity g2gl-activity)))
    (when flow-gates
      (prog1 (car (last flow-gates))
        (reclaim-gensym-list flow-gates)))))


;;; The bottommost flow signal connected to the bottom of a g2gl-activity
;;; object, or nil if there are none.

(defun bottommost-flow-signal-for-g2gl-activity (g2gl-activity)
  (let ((flow-signals (collect-flow-signals-for-bpel-activity g2gl-activity)))
    (when flow-signals
      (prog1 (car (last flow-signals))
        (reclaim-gensym-list flow-signals)))))


;;; The special variables `bpel-xml-namespace' and `g2gl-xml-namespace' hold the
;;; current xml-namespace structs while exporting a G2GL process as XML.  The
;;; BPEL namespace is used for elements and attributes that are part of the BPEL
;;; specification, while the G2GL namespace is used for elements and attributes
;;; corresponding to G2GL-specific extensions to the BPEL specification.

(defvar bpel-xml-namespace)
(defvar g2gl-xml-namespace)


;;; The functions `xml-node-new-bpel-child' and `xml-node-new-g2gl-child' are
;;; wrappers around `xml-node-new-child' to put the new element in the BPEL or
;;; G2GL namespace, respectively, using the current namespace structs while
;;; exporting a G2GL process to XML.  The namespace is explicitly specified in
;;; order to avoid inheriting the namespace of the parent element, which might
;;; be wrong, such as when a standard BPEL activity appears inside a
;;; G2GL-specific flow construct.

(defun xml-node-new-bpel-child (parent name &optional text-content)
  (xml-node-new-child parent name bpel-xml-namespace text-content))

(defun xml-node-new-g2gl-child (parent name &optional text-content)
  (xml-node-new-child parent name g2gl-xml-namespace text-content))


;;; The function `add-namespace-to-xml-element' adds a new namespace
;;; declaration to an XML element given a URI string and a prefix symbol.  If
;;; the prefix is not provided, a default namespace is created.  The new
;;; xml-namespace struct is returned.

(defun add-namespace-to-xml-element (xml-element uri &optional prefix)
  (xml-element-new-namespace
    xml-element uri (when prefix (convert-symbol-to-xml-name prefix))))


;;; The function `add-namespaces-to-xml-element' adds namespace declarations to
;;; an XML element for all of the namespaces specified in the
;;; `g2gl-namespace-map' slot of a G2GL object.

(defun add-namespaces-to-xml-element (xml-element bpel-activity)
  (let ((namespace-map
          (g2gl-namespace-map bpel-activity)))
    (loop for (prefix uri) in namespace-map
          do (add-namespace-to-xml-element xml-element uri prefix))))


;;; Add <target> elements to xml-element, one for each flow link coming into
;;; flow-gate.  Add "joinCondition" and "suppressJoinFailure" attributes to
;;; xml-element if the corresponding G2GL attributes are set on flow-gate.
;;; Return xml-element.

(defun add-flow-targets-to-xml-element (xml-element flow-gate)
  (let ((flow-signals (collect-flow-signals-connected-to-flow-gate flow-gate)))
    (loop for flow-signal in flow-signals do
      (let ((target-element (xml-node-new-bpel-child xml-element "target")))
        (xml-element-set-attribute
          target-element "linkName"
          (convert-symbol-to-xml-name (g2gl-link-name flow-signal)))))
    (reclaim-gensym-list flow-signals))
  (xml-element-set-attribute-from-text-slot-value
    xml-element "joinCondition" (flow-gate-join-condition flow-gate))
  (when (suppress-join-failure flow-gate)
    (xml-element-set-attribute
      xml-element "suppressJoinFailure" "yes"))
  xml-element
)


;;; Add "name", "joinCondition", and "suppressJoinFailure" attributes to
;;; xml-element, if needed.  Add <target> elements to xml-element corresponding
;;; to the flow gate attached to the top of entry-block and <source> elements
;;; corresponding to the flow signals attached to the bottom of exit-block (or
;;; entry-block if not provided).

(defun add-standard-attributes-and-elements-to-bpel-element
    (xml-element entry-block &optional exit-block)
  (let ((name
          (get-primary-name-for-frame-if-any entry-block))
        (flow-gate
          (bpel-activity-default-input-object entry-block))
        (flow-signals
          (collect-flow-signals-for-bpel-activity
            (or exit-block entry-block))))

    (when name
      (xml-element-set-attribute-symbol xml-element "name" name))

    (when (and flow-gate (eq (class flow-gate) 'g2gl-flow-gate))
      (add-flow-targets-to-xml-element xml-element flow-gate))

    (loop for flow-signal in flow-signals do
      (let ((source-element
              (xml-node-new-bpel-child xml-element "source"))
            (link-name
              (g2gl-link-name flow-signal))
            (transition-condition
              (flow-signal-transition-condition flow-signal)))
        (xml-element-set-attribute
          source-element
          "linkName"
          (convert-symbol-to-xml-name link-name))
        (when transition-condition
          (let ((transition-condition-string
                  (convert-text-to-text-string
                    (cdr transition-condition))))
            (xml-element-set-attribute
              source-element "transitionCondition"
              transition-condition-string)
            (reclaim-text-string transition-condition-string)))))

    (reclaim-gensym-list flow-signals)))


;;; Add a <correlations> child to an XML element if a G2GL activity has any
;;; correlations.

(defun add-correlations-to-bpel-element (element activity)
  (let ((correlations (g2gl-correlations activity)))
    (when correlations
      (let ((correlations-element
              (xml-node-new-bpel-child element "correlations")))
        (loop for (var-name . options) in correlations do
          (let ((correlation-element
                  (xml-node-new-bpel-child correlations-element "correlation")))
            (xml-element-set-attribute-symbol
              correlation-element "set" var-name)
            (loop for option in options do
              (case option
                (initiate-conversation
                 (xml-element-set-attribute
                   correlation-element "initiate" "yes"))
                ((in out)
                 (xml-element-set-attribute-symbol
                   correlation-element "pattern" option))
                (out-in
                 ;; Don't use xml-element-set-attribute-symbol here, because it
                 ;; will be converted to "outIn"!
                 (xml-element-set-attribute
                   correlation-element "pattern" "out-in"))))))))))


;;; Add <copy> children to an <assign> XML element for a list of assignment
;;; statements.

(defun add-assignments-to-bpel-element (element assignments)
  (loop for assignment in assignments do
    (let* ((copy-element
             (xml-node-new-bpel-child element "copy"))
           (from-element
             (xml-node-new-bpel-child copy-element "from"))
           (to-element
             (xml-node-new-bpel-child copy-element "to")))
      (xml-element-set-attribute
        from-element "expression"
        (g2gl-assignment-expression-value-expression-text-string assignment))
      (xml-element-set-attribute-symbol
        to-element "variable"
        (g2gl-assignment-expression-variable assignment))
      (xml-element-set-attribute-symbol
        to-element "part"
        (g2gl-assignment-expression-part assignment)))))


(defun convert-g2-bpel-activity-sequence-to-xml-bpel (bpel-activity
                                                       parent-element
                                                       &optional stop-activity)
  (loop for activity = bpel-activity then next-activity
        when (or (not activity)
                 (eq activity stop-activity)
                 (memq activity activities))
          do (reclaim-gensym-list activities)
             (return)
        collect activity into activities using gensym-cons
        for next-activity = (convert-g2-bpel-activity-to-xml-bpel
                              activity parent-element)))


(defun convert-g2-bpel-activity-to-xml-sequence-or-element
    (bpel-activity parent-element &optional stop-activity)
  (unless (eq bpel-activity stop-activity)
    (cond ((or (g2gl-activity-has-no-standard-out-connections-p bpel-activity)
               (let ((successor
                       (successor-of-activity
                         (get-activity-from-entry-object bpel-activity))))
                 (or (not successor)
                     (eq successor stop-activity))))
           (convert-g2-bpel-activity-sequence-to-xml-bpel
             bpel-activity
             parent-element
             stop-activity))
          (t
           (let ((sequence-element
                   (xml-node-new-bpel-child parent-element "sequence")))
             (convert-g2-bpel-activity-sequence-to-xml-bpel
               bpel-activity sequence-element stop-activity))))))


;;; Convert a g2gl-flow-gate and the activity below it into XML as a child of
;;; parent-element.  Return the next activity below that.

(defun convert-flow-gate-to-xml-bpel (flow-gate parent-element)
  (let* ((next-object (g2gl-activity-bottom-output-object flow-gate))
         (parent-of-next-element
           (if (and next-object (not (eq (class next-object) 'g2gl-flow-gate)))

               ;; If the next object is not a flow gate, just convert it as a
               ;; child of parent-element.  This flow gate will be converted to
               ;; <target> elements attached to the next element by
               ;; add-links-to-bpel-element.
               parent-element

               ;; Otherwise, there are two or more flow gates in succession;
               ;; convert this one into a <sequence> with <target> elements and
               ;; convert the next object as a child of the <sequence>.  If
               ;; there is no next object, this just becomes an empty sequence.
               ;; (Which is not legal BPEL, but neither is a dangling flow-gate.
               ;; Maybe eventually we could insert an <empty> element.  See
               ;; suggestion HQ-5004942 "G2GL: export should never produce
               ;; non-valid BPEL".)
               (add-flow-targets-to-xml-element
                 (xml-node-new-bpel-child parent-element "sequence")
                 flow-gate))))

    (convert-g2-bpel-activity-to-xml-bpel next-object parent-of-next-element)))


;;; Convert g2gl-receive to <receive>, or <onMessage> inside <pick>.

(defun convert-g2gl-receive-to-xml-bpel (bpel-activity parent-element name
                                                       &optional namespace)
  (let ((receive-element
          (xml-node-new-child parent-element name namespace))
        (output-variable-name
          (g2gl-message-variable-name bpel-activity)))
    (set-g2gl-operation-attributes-on-element bpel-activity receive-element)
    (when output-variable-name
      (xml-element-set-attribute
        receive-element "variable"
        (convert-symbol-to-xml-name output-variable-name)))
    (when (and (equal name "receive")
               (this-is-an-instantiation-trigger-for-receive bpel-activity))
      (xml-element-set-attribute receive-element "createInstance" "yes"))
    (add-standard-attributes-and-elements-to-bpel-element
      receive-element bpel-activity)
    (add-correlations-to-bpel-element receive-element bpel-activity)
    receive-element))


;;; Convert g2gl-wait to <wait>, or <onAlarm> inside <pick>.

(defun convert-g2gl-wait-to-xml-bpel (bpel-activity parent-element name
                                                    &optional namespace)
  (let ((wait-element (xml-node-new-child parent-element name namespace)))
    (set-g2gl-alarm-time-attributes-on-element bpel-activity wait-element)
    (add-standard-attributes-and-elements-to-bpel-element
      wait-element bpel-activity)
    wait-element))


;;; The function `get-join-from-branch-activity' searches downward from a G2GL
;;; branch activity (flow, switch, or pick) for the corresponding join bar
;;; object, if any.

;; TO DO: if the search runs into a dead end or loop, try other branches.
;; See also the similar code in exit-object-of-activity.

(defun get-join-from-branch-activity (branch-activity)
  (let ((entry-object-of-first-branch
          (g2gl-activity-bottom-output-object branch-activity)))
    (when entry-object-of-first-branch
      (loop for object = (get-activity-from-entry-object
                           entry-object-of-first-branch)
                       then (successor-of-activity object)
            while object
            until (memq object objects)
            collect object into objects using gensym-cons
            with join-classes = (join-classes-of-activity branch-activity)
            when (loop for class in join-classes
                       thereis (frame-of-class-p object class))
              return (prog1 object (reclaim-gensym-list objects))
            finally (reclaim-gensym-list objects)))))

(defun convert-g2-bpel-flow-activity-to-xml-bpel (flow-activity parent-element)
  (let* ((flow-join? (get-join-from-branch-activity flow-activity))
         (flow-element
           (if (or (not flow-join?)
                   (frame-of-class-p flow-join? 'g2gl-flow-sync))
               (xml-node-new-bpel-child parent-element "flow")
               (xml-node-new-g2gl-child
                 parent-element
                 (frame-class-case flow-join?
                   (g2gl-flow-discriminator "flowDiscriminator")
                   (g2gl-n-out-of-m-flow-join "nOutOfMFlow")
                   (g2gl-flow-terminator "flowTerminator")))))
         (link-names? (g2gl-link-names flow-activity))
         (next-activities
           (get-next-g2gl-activities-from-g2gl-activity flow-activity)))
    (add-standard-attributes-and-elements-to-bpel-element
      flow-element flow-activity flow-join?)
    (when (of-class-p flow-join? 'g2gl-n-out-of-m-flow-join)
      (let ((n-string (tformat-text-string
                        "~a" (number-of-branches-to-synchronize flow-join?))))
        (xml-element-set-attribute flow-element "n" n-string)
        (reclaim-text-string n-string)))
    (when link-names?
      (let ((links-element (xml-node-new-bpel-child flow-element "links")))
        (loop for link-name in (g2gl-link-names flow-activity) do
          (let ((link-element (xml-node-new-bpel-child links-element "link")))
            (xml-element-set-attribute
              link-element "name" (convert-symbol-to-xml-name link-name))))))
    (loop for flow-branch in next-activities do
      (convert-g2-bpel-activity-to-xml-sequence-or-element
        flow-branch flow-element flow-join?))
    flow-join?))

(defun convert-g2-bpel-switch-activity-to-xml-bpel (switch-activity parent-element)
  (let ((switch-element
          (xml-node-new-bpel-child parent-element "switch"))
        (switch-join
          (get-join-from-branch-activity switch-activity)))
    (add-standard-attributes-and-elements-to-bpel-element
      switch-element switch-activity switch-join)
    (loop for fork = switch-activity
                   then (bpel-activity-right-output-object fork)
          while fork
          until (memq fork forks)
          collect fork into forks using gensym-cons
          finally (reclaim-gensym-list forks)
          for otherwise-p = (not (eq (class fork) 'g2gl-switch-fork))
          for case-entry-object = (if otherwise-p
                                      fork
                                      (g2gl-activity-bottom-output-object
                                        fork))
          unless (eq (class fork) 'g2gl-switch-join)
            do (let ((case-element
                       (xml-node-new-bpel-child
                         switch-element
                         (if otherwise-p "otherwise" "case")))
                     (condition
                       (unless otherwise-p
                         (switch-fork-condition fork))))
                 (when condition
                   (xml-element-set-attribute
                     case-element "condition"
                     (convert-text-to-text-string (cdr condition))))
                 (convert-g2-bpel-activity-to-xml-sequence-or-element
                   case-entry-object case-element switch-join)))

    switch-join))


(defun convert-g2-bpel-pick-activity-to-xml-bpel (pick-activity parent-element)
  (let* ((pick-element
           (xml-node-new-bpel-child parent-element "pick"))
         (next-activities
           (get-next-g2gl-activities-from-g2gl-activity pick-activity))
         (pick-join
           (get-join-from-branch-activity pick-activity)))
    (when (this-is-an-instantiation-trigger-for-pick pick-activity)
      (xml-element-set-attribute pick-element "createInstance" "yes"))
    (add-standard-attributes-and-elements-to-bpel-element
      pick-element pick-activity pick-join)
    (loop for pick-branch in next-activities do
      (let* ((next-activity
               (get-next-g2gl-activity-from-g2gl-activity pick-branch))
             (handler-element
               (frame-class-case pick-branch
                 (g2gl-receive
                   (convert-g2gl-receive-to-xml-bpel
                     pick-branch pick-element "onMessage" bpel-xml-namespace))
                 (g2gl-wait
                   (convert-g2gl-wait-to-xml-bpel
                     pick-branch pick-element "onAlarm" bpel-xml-namespace))
                 (otherwise
                   ;; malformed pick, put the children on the <pick> itself.
                   (setq next-activity pick-branch)
                   pick-element))))
        (when next-activity
          (convert-g2-bpel-activity-to-xml-sequence-or-element
            next-activity handler-element pick-join))))
    pick-join))

(defun convert-g2-bpel-while-activity-to-xml-bpel (while-activity parent-element)
  (let ((while-element
          (xml-node-new-bpel-child parent-element "while"))
        (while-condition
          (while-iteration-condition while-activity))
        (while-body-activity
          (bpel-activity-right-output-object while-activity))
        (next-activity
          (g2gl-activity-bottom-output-object while-activity)))

    (when while-condition
      (xml-element-set-attribute while-element
                                 "condition"
                                 (convert-text-to-text-string
                                   (cdr while-condition))))
    (add-standard-attributes-and-elements-to-bpel-element
      while-element
      while-activity)
    (when while-body-activity
      (convert-g2-bpel-activity-to-xml-sequence-or-element
        while-body-activity while-element while-activity))
   (if (eq next-activity while-body-activity) nil next-activity)))


;;; Convert the body of a g2gl-handler to children of an XML element.

(defun convert-g2gl-handler-body-to-xml (handler element)
  (let ((body (car (subworkspaces handler))))
    (when body
      (let ((initial-activity (get-initial-activity-from-process-body body)))
        (when initial-activity
          (convert-g2-bpel-activity-to-xml-sequence-or-element
            initial-activity element))))))


(defvar activities-currently-being-converted-to-xml)

(defun convert-g2-bpel-activity-to-xml-bpel (bpel-activity parent-element)
  (let ((result nil))
    (when (and bpel-activity
               (not (memq bpel-activity
                          activities-currently-being-converted-to-xml)))
      (gensym-push bpel-activity activities-currently-being-converted-to-xml)
      (setq result
            (get-next-g2gl-activity-from-g2gl-activity bpel-activity))
      (class-case (class bpel-activity)
        (g2gl-flow-signal)
        (g2gl-flow-gate
          (setq result
                (convert-flow-gate-to-xml-bpel bpel-activity parent-element)))
        (kb-workspace                        ; previously "g2gl-process-body"
          (multiple-value-bind
              (arg-variables g2gl-partner-links correlation-variables
                             g2gl-variables g2gl-fault-handlers compensation-handlers
                             event-handlers initial-activities)
              (collect-g2gl-body-elements bpel-activity)

            (when arg-variables
              (let ((element (xml-node-new-g2gl-child
                               parent-element "argVariables")))
                (loop for cv in arg-variables do
                  (convert-g2-bpel-activity-to-xml-bpel cv element))))

            ;; Insert the partner link elements
            (when g2gl-partner-links
              (let ((partner-links-element
                      (xml-node-new-bpel-child parent-element "partnerLinks")))
                (loop for variable in g2gl-partner-links do
                  (convert-g2-bpel-activity-to-xml-bpel
                    variable partner-links-element))))

            (let ((parent? (parent-of-subworkspace? bpel-activity)))
              (when (and parent?
                         (frame-of-class-p parent? 'g2gl-process))
                (let ((partners (g2gl-partner-link-groups parent?)))
                  (when partners
                    (let ((partners-element
                            (xml-node-new-bpel-child
                              parent-element "partners")))
                      (loop for partner in partners do
                        (let ((partner-element
                                (xml-node-new-bpel-child
                                  partners-element "partner"))
                              (partner-name
                                (convert-symbol-to-xml-name
                                  (car partner))))
                          (xml-element-set-attribute
                            partner-element "name" partner-name)
                          (reclaim-text-string partner-name)
                          (loop for partner-link in (cdr partner) do
                            (let ((partner-link-element
                                    (xml-node-new-bpel-child
                                      partner-element "partnerLink"))
                                  (partner-link-name
                                    (convert-symbol-to-xml-name
                                      partner-link)))
                              (xml-element-set-attribute
                                partner-link-element "name"
                                partner-link-name)
                              (reclaim-text-string partner-link-name))))))))))

            (when correlation-variables
              (let ((element (xml-node-new-bpel-child
                               parent-element "correlationSets")))
                (loop for cv in correlation-variables do
                  (convert-g2-bpel-activity-to-xml-bpel cv element))))

            ;; Insert the variable elements
            (when g2gl-variables
              (let ((variables-element
                      (xml-node-new-bpel-child
                        parent-element "variables")))
                (loop for variable in g2gl-variables do
                  (convert-g2-bpel-activity-to-xml-bpel
                    variable variables-element))))

            ;; Insert the fault handlers
            (when g2gl-fault-handlers
              (let ((fault-handlers-element
                      (xml-node-new-bpel-child
                        parent-element "faultHandlers")))
                (loop for fault-handler in g2gl-fault-handlers do
                  (convert-g2-bpel-activity-to-xml-bpel
                    fault-handler fault-handlers-element))))

            (when compensation-handlers
              (loop for handler in compensation-handlers do
                (convert-g2-bpel-activity-to-xml-bpel
                  handler parent-element)))

            (when event-handlers
              (let ((element (xml-node-new-bpel-child
                               parent-element "eventHandlers")))
                (loop for handler in event-handlers do
                  (convert-g2-bpel-activity-to-xml-bpel handler element))))

            (loop for initial-activity in initial-activities do
              ;; If there is more than one activity then place it in a sequence
              ;; element
              (convert-g2-bpel-activity-to-xml-sequence-or-element
                initial-activity parent-element))

            (reclaim-gensym-list arg-variables)
            (reclaim-gensym-list correlation-variables)
            (reclaim-gensym-list compensation-handlers)
            (reclaim-gensym-list event-handlers)
            (reclaim-gensym-list initial-activities)
            (when g2gl-variables
              (reclaim-gensym-list g2gl-variables))
            (when g2gl-partner-links
              (reclaim-gensym-list g2gl-partner-links))
            (when g2gl-fault-handlers
              (reclaim-gensym-list g2gl-fault-handlers))))
        (g2gl-local-variable
          (let ((variable-element
                  (xml-node-new-bpel-child parent-element "variable"))
                (variable-name
                  (get-primary-name-for-frame-if-any bpel-activity))
                (initial-value
                  (default-value-for-g2gl-variable bpel-activity)))
            (when variable-name
              (xml-element-set-attribute variable-element
                                         "name"
                                         (convert-symbol-to-xml-name
                                           variable-name)))
            (set-g2gl-type-specifier-attribute-on-element
              bpel-activity variable-element)
            (when initial-value
              (let* ((write-floats-accurately-p t)
                     (initial-value-string
                       (make-text-string-representation-for-slot-value-itself
                         bpel-activity
                         initial-value
                         (get-type-of-slot
                           bpel-activity
                           'default-value-for-g2gl-variable
                           nil))))
                (xml-element-set-attribute
                  variable-element "initialValue"
                  initial-value-string
                  g2gl-xml-namespace)
                (reclaim-text-string initial-value-string)))))
        (g2gl-partner-link-variable
          (let ((variable-element
                  (xml-node-new-bpel-child parent-element "partnerLink"))
                (variable-name
                  (get-primary-name-for-frame-if-any bpel-activity)))
            (xml-element-set-attribute-symbol
              variable-element "name" variable-name)
            (set-g2gl-partner-link-attributes-on-element
              bpel-activity variable-element)))
        (g2gl-correlation-variable
          (let ((element (xml-node-new-bpel-child
                           parent-element "correlationSet"))
                (type (g2gl-variable-type bpel-activity)))
            (xml-element-set-attribute-symbol
              element "name" (get-primary-name-for-frame-if-any bpel-activity))
            (when (g2gl-correlation-variable-type-p type)
              (xml-element-set-attribute-symbols
                element "properties"
                ;; -- car should've been CONVERSATION-KEY-ATTRIBUTES
                (cdr type)))))
        (g2gl-fault-handler
          (let* ((fault-name (g2gl-fault-name bpel-activity))
                 (catch-all-p (eql fault-name 0))
                 (name (if catch-all-p "catchAll" "catch"))
                 (catch-element (xml-node-new-bpel-child parent-element name)))
            (unless catch-all-p
              (when fault-name
                (xml-element-set-attribute
                  catch-element "faultName"
                  (convert-symbol-to-xml-name fault-name)))
              (let ((var-name (g2gl-fault-variable-name bpel-activity)))
                (when var-name
                  (xml-element-set-attribute
                    catch-element "faultVariable"
                    (convert-symbol-to-xml-name var-name)))))
            (convert-g2gl-handler-body-to-xml bpel-activity catch-element)))
        (g2gl-compensation-handler
          (convert-g2gl-handler-body-to-xml
            bpel-activity
            (xml-node-new-bpel-child parent-element "compensationHandler")))
        (g2gl-message-event-handler
          (let ((element (xml-node-new-bpel-child parent-element "onMessage")))
            (set-g2gl-operation-attributes-on-element bpel-activity element)
            (xml-element-set-attribute-symbol
              element "variable" (g2gl-message-variable-name bpel-activity))
            (add-correlations-to-bpel-element element bpel-activity)
            (convert-g2gl-handler-body-to-xml bpel-activity element)))
        (g2gl-alarm-event-handler
          (let ((element (xml-node-new-bpel-child parent-element "onAlarm")))
            (set-g2gl-alarm-time-attributes-on-element bpel-activity element)
            (convert-g2gl-handler-body-to-xml bpel-activity element)))
        (g2gl-assign
          (let ((assign-element
                  (xml-node-new-bpel-child parent-element "assign")))
            (add-standard-attributes-and-elements-to-bpel-element
              assign-element bpel-activity)
            (when (g2gl-assignments bpel-activity)
              (add-assignments-to-bpel-element
                assign-element (car (g2gl-assignments bpel-activity))))))
        (g2gl-invoke
          (let ((invoke-element
                  (xml-node-new-bpel-child parent-element "invoke"))
                (input-variable-name
                  (g2gl-message-variable-name bpel-activity))
                (output-variable-name
                  (g2gl-response-variable-name bpel-activity)))
            (set-g2gl-operation-attributes-on-element
              bpel-activity invoke-element)
            (when input-variable-name
              (xml-element-set-attribute
                invoke-element
                "inputVariable"
                (convert-symbol-to-xml-name input-variable-name)))
            (when output-variable-name
              (xml-element-set-attribute
                invoke-element
                "outputVariable"
                (convert-symbol-to-xml-name output-variable-name)))
            (add-standard-attributes-and-elements-to-bpel-element
              invoke-element bpel-activity)
            (add-correlations-to-bpel-element invoke-element bpel-activity)
            (let ((local-handlers
                    (collect-g2gl-invoke-local-handlers bpel-activity)))
              (loop for handler in local-handlers do
                (convert-g2-bpel-activity-to-xml-bpel
                  handler invoke-element))
              (reclaim-gensym-list local-handlers)))
          (setq result (g2gl-activity-bottom-output-object
                         bpel-activity)))
        (g2gl-receive
          (convert-g2gl-receive-to-xml-bpel
            bpel-activity parent-element "receive" bpel-xml-namespace))
        (g2gl-reply
          (let ((reply-element
                  (xml-node-new-bpel-child parent-element "reply"))
                (input-variable-name
                  (g2gl-message-variable-name bpel-activity)))
            (set-g2gl-operation-attributes-on-element
              bpel-activity reply-element)
            (when input-variable-name
              (xml-element-set-attribute
                reply-element
                "variable"
                (convert-symbol-to-xml-name input-variable-name)))
            (xml-element-set-attribute-symbol
              reply-element "faultName" (fault-name-for-reply bpel-activity))
            (add-standard-attributes-and-elements-to-bpel-element
              reply-element bpel-activity)
            (add-correlations-to-bpel-element reply-element bpel-activity)))
        (g2gl-throw
          (let ((element
                  (xml-node-new-bpel-child parent-element "throw"))
                (fault-name
                  (fault-name-for-throw bpel-activity))
                (var-name
                  (fault-data-g2gl-variable-name bpel-activity)))
            (when fault-name
              (xml-element-set-attribute
                element "faultName"
                (convert-symbol-to-xml-name fault-name)))
            (when var-name
              (xml-element-set-attribute
                element "faultVariable"
                (convert-symbol-to-xml-name var-name)))
            (add-standard-attributes-and-elements-to-bpel-element
              element bpel-activity)))
        (g2gl-exit
          (add-standard-attributes-and-elements-to-bpel-element
            (xml-node-new-bpel-child parent-element "terminate")
            bpel-activity))
        (g2gl-wait
          (convert-g2gl-wait-to-xml-bpel
            bpel-activity parent-element "wait" bpel-xml-namespace))
        (g2gl-empty
          (add-standard-attributes-and-elements-to-bpel-element
            (xml-node-new-bpel-child parent-element "empty")
            bpel-activity))
        (g2gl-scope
          (let ((scope-element
                  (xml-node-new-bpel-child parent-element "scope")))
            (when (variable-access-serializable bpel-activity)
              (xml-element-set-attribute
                scope-element "variableAccessSerializable" "yes"))
            (convert-g2-bpel-activity-to-xml-bpel
              (car (subworkspaces bpel-activity)) scope-element)
            (add-standard-attributes-and-elements-to-bpel-element
              scope-element
              bpel-activity)))
        (g2gl-flow-split
          (setq result
                (convert-g2-bpel-flow-activity-to-xml-bpel
                  bpel-activity
                  parent-element)))
        (g2gl-pick
          (setq result
                (convert-g2-bpel-pick-activity-to-xml-bpel
                  bpel-activity
                  parent-element)))
        (g2gl-switch-fork
          (setq result
                (convert-g2-bpel-switch-activity-to-xml-bpel
                  bpel-activity
                  parent-element)))
        (g2gl-while
          (setq result
                (convert-g2-bpel-while-activity-to-xml-bpel
                  bpel-activity
                  parent-element)))
        (g2gl-do
          (let ((xml-element
                  (xml-node-new-g2gl-child parent-element "do"))
                (expression
                  (g2gl-statements bpel-activity)))
            (when expression
              (xml-element-set-attribute
                xml-element "expression"
                (convert-text-to-text-string (cdr expression))))
            (add-standard-attributes-and-elements-to-bpel-element
              xml-element
              bpel-activity)))
        (g2gl-call
          (let ((xml-element
                  (xml-node-new-g2gl-child parent-element "call"))
                (expression
                  (g2gl-procedure-call-statement bpel-activity)))
            (when expression
              (xml-element-set-attribute
                xml-element "expression"
                (convert-text-to-text-string (cdr expression))))
            (add-standard-attributes-and-elements-to-bpel-element
              xml-element
              bpel-activity)))
        (g2gl-break
          (add-standard-attributes-and-elements-to-bpel-element
            (xml-node-new-g2gl-child parent-element "break")
            bpel-activity))
        (g2gl-compensate
          (let ((xml-element
                  (xml-node-new-bpel-child parent-element "compensate"))
                (scope-name
                  (scope-name-for-compensate-activity bpel-activity)))
            (when scope-name
              (xml-element-set-attribute
                xml-element "scope"
                (convert-symbol-to-xml-name scope-name)))
            (add-standard-attributes-and-elements-to-bpel-element
              xml-element
              bpel-activity)))
        (g2gl-return
          (let ((xml-element
                  (xml-node-new-g2gl-child parent-element "return"))
                (expression
                  (g2gl-values-expression bpel-activity)))
            (when expression
              (xml-element-set-attribute
                xml-element "expression"
                (convert-text-to-text-string (cdr expression))))
            (add-standard-attributes-and-elements-to-bpel-element
              xml-element
              bpel-activity)))
        (g2gl-arg-variable
          (let ((xml-element
                  (xml-node-new-g2gl-child parent-element "argVariable"))
                (name (get-primary-name-for-frame-if-any bpel-activity))
                (initial-value
                  (default-value-for-g2gl-variable bpel-activity)))
            (when name
              (xml-element-set-attribute
                xml-element "name" (convert-symbol-to-xml-name name)))
            (set-g2gl-type-specifier-attribute-on-element
              bpel-activity xml-element)
            (when initial-value
              (let* ((write-floats-accurately-p t)
                     (initial-value-string
                       (make-text-string-representation-for-slot-value-itself
                         bpel-activity
                         initial-value
                         (get-type-of-slot
                           bpel-activity
                           'default-value-for-g2gl-variable
                           nil))))
                (xml-element-set-attribute
                  xml-element "initialValue" initial-value-string)
                (reclaim-text-string initial-value-string)))))
        ))
    (gensym-pop activities-currently-being-converted-to-xml)
    result))


(defun add-g2gl-comment-to-document (document process)
  (let ((comment-string
          (twith-output-to-text-string
            (tformat "~%  Automatically generated by G2GL.~%  ")

            ;; This generates copyright and trademark symbols, which would
            ;; require setting the encoding, and I don't feel like messing with
            ;; that right now.  -dougo, 5/5/05
;            (let* ((product (make-text-for-product-and-options))
;                   (product-string (convert-text-to-text-string product)))
;              (twrite-string product-string)
;              (reclaim-text product)
;              (reclaim-text-string product-string))
            (twrite-string "G2 ")

            (let* ((version (make-text-for-type-of-g2-license))
                   (version-string (convert-text-to-text-string version)))
              (twrite-string version-string)
              (reclaim-text version)
              (reclaim-text-string version-string))

            (let ((workspace (get-workspace-if-any process)))
              (when workspace
                (let ((module (module-this-is-part-of? workspace)))
                  (when module (tformat " Module: ~a~% " module))
                  (let* ((msp (get-saving-parameters module))
                         (sp saving-parameters)
                         (file (or (and msp (or (current-file-for-module msp)
                                                (filename-of-basis-kb msp)))
                                   (and sp (or (current-file-for-module sp)
                                               (filename-of-basis-kb sp))))))
                    (when file (tformat " File: ~a~% " file))))))

            )))
    (xml-node-add-comment document comment-string)
    (reclaim-text-string comment-string)
    document))


(defun convert-g2-bpel-to-xml-bpel (g2-bpel-process)
  (let* ((document
           (add-g2gl-comment-to-document
             (xml-create-document) g2-bpel-process))
         (process-element
           (xml-node-new-child document "process"))
         (process-name
           (get-primary-name-for-frame-if-any g2-bpel-process))
         (target-namespace
           (g2gl-target-namespace g2-bpel-process))
         (subworkspaces
           (subworkspaces g2-bpel-process)))

    (xml-element-set-attribute-symbol
      process-element "name" process-name)

    (when target-namespace
      (xml-element-set-attribute
        process-element
        "targetNamespace"
        target-namespace))

    (xml-element-set-attribute
      process-element "queryLanguage" g2gl-expression-language-uri)
    (xml-element-set-attribute
      process-element "expressionLanguage" g2gl-expression-language-uri)

    (when (enable-instance-compensation g2-bpel-process)
      (xml-element-set-attribute
        process-element "enableInstanceCompensation" "yes"))
    (when (this-is-an-abstract-process g2-bpel-process)
      (xml-element-set-attribute
        process-element "abstractProcess" "yes"))

    ;; Set some special variables:
    (let ((activities-currently-being-converted-to-xml nil) ;recursion guard

          (bpel-xml-namespace
            ;; The WS-BPEL XML namespace, as the default namespace.
            (add-namespace-to-xml-element
              process-element
              bpel-xml-namespace-uri))

          (g2gl-xml-namespace
            ;; The G2GL XML namespace, for non-BPEL elements and attributes.
            (add-namespace-to-xml-element
              process-element
              g2gl-xml-namespace-uri
              g2gl-xml-namespace-prefix)))

      ;; The G2 datatypes XML namespace, for G2 item and value types.
      (add-namespace-to-xml-element
        process-element
        g2-datatypes-xml-namespace-uri
        g2-datatypes-xml-namespace-prefix)

      ;; The XSD datatypes XML namespace, for XML Schema types.
      (add-namespace-to-xml-element
        process-element
        xsd-datatypes-xml-namespace-uri
        xsd-datatypes-xml-namespace-prefix)

      ;; TO DO: These should use different prefixes if the defaults would clash
      ;; with the user's prefixes. -dougo, 4/24/05

      ;; Add any other XML namespaces specified by the process object.
      (add-namespaces-to-xml-element process-element g2-bpel-process)

      ;; Set the namespace of the process element to the WS-BPEL XML namespace.
      (xml-node-set-namespace process-element bpel-xml-namespace)

      (when subworkspaces
        (convert-g2-bpel-activity-to-xml-bpel
          (car subworkspaces)
          process-element)))

    document))

;;; System procedure for exporting a G2GL process as an XML document to a file.

(defun-for-system-procedure g2-export-g2gl-process-as-xml (g2gl-process path)
  (reclaiming-xml-structures
    (xml-write-file (convert-g2-bpel-to-xml-bpel g2gl-process) path)))

;;; System procedure for exporting a G2GL process as an XML document to a text.

(defun-for-system-procedure g2-export-g2gl-process-as-xml-text (g2gl-process)
  (reclaiming-xml-structures
    (make-evaluation-text-reclaiming-argument
      (xml-write-text-string (convert-g2-bpel-to-xml-bpel g2gl-process)))))





;;;; Extracting structure information from a layout

;;; In the following functions, `activity' is meant in the BPEL sense; not every
;;; g2gl-activity object is an activity and vice versa.  An `activity
;;; representation' is a g2gl-activity object or gensym-list that stands in for
;;; an activity.
;;;
;;; A `basic activity' is an activity with no children, such as <empty>,
;;; <assign>, or <wait>.  It is represented by a single g2gl-activity object.
;;;
;;; A `structured activity' is an activity with one or more children:
;;;
;;;   A <sequence> activity is represented by a gensym-list of its children
;;;   activities.
;;;
;;;   A <while> activity is represented by its g2gl-while object.
;;;
;;;   A <switch> activity is represented by its leftmost g2gl-switch-fork
;;;   object.
;;;
;;;   A <pick> or <flow> activity is represented by its g2gl-pick or
;;;   g2gl-flow-split object, respectively.
;;;
;;;   An <invoke> activity is represented by its g2gl-invoke object.
;;;
;;; Note that flow links, join bars, and handlers are not activities.
;;;
;;; For most purposes, a <scope> is considered a basic activity (represented by
;;; a g2gl-scope object), since its children live on a different workspace.


;;; The `entry object' of an activity is the object that has the input
;;; connection for the activity:
;;;
;;;   The entry object of an activity with flow gates is the topmost flow gate.
;;;
;;;   The entry object of a <sequence> activity is the entry object of the first
;;;   activity in the sequence.
;;;
;;;   Otherwise, the entry object of an activity is the object that represents
;;;   the activity (see the definition of `activity representation' above).

(defun entry-object-of-activity (activity)
  (if (consp activity)
      (entry-object-of-activity (car activity))
      (or (topmost-flow-gate-for-g2gl-activity activity)
          activity)))

(defun get-activity-from-entry-object (entry-object)
  (loop for object = entry-object then next-object
        unless (eq (class object) 'g2gl-flow-gate)
          return (prog1 object (reclaim-gensym-list objects))
        collect object into objects using gensym-cons
        for next-object = (g2gl-activity-bottom-output-object object)
        when (or (not next-object) (memq next-object objects))
          return (prog1 object (reclaim-gensym-list objects))))


;;; The `exit object' of an activity is the object that has the output
;;; connection for the activity:
;;;
;;;   The exit object of an object with flow signals is the bottommost flow
;;;   signal.
;;;
;;;   The exit object of a basic activity is the activity object itself.
;;;
;;;   The exit object of a <sequence> activity is the exit object of the last
;;;   activity in the sequence.
;;;
;;;   The exit object of a <while> activity is the g2gl-while object.
;;;
;;;   The exit object of a <switch>, <pick>, or <flow> activity is the join bar
;;;   object at the bottom, if it exists.

(defun exit-object-of-activity (activity)
  (if (consp activity)
      (exit-object-of-activity (car (last activity)))
      (let* ((join-classes? (join-classes-of-activity activity))
             (object
               (if join-classes?
                   (loop for object = activity
                                    then (exit-object-of-activity
                                           (get-activity-from-entry-object
                                             next-object))
                         collect object into objects using gensym-cons
                         for next-object = (g2gl-activity-bottom-output-object
                                             object)
                         when (or (not next-object) (memq next-object objects))
                           ;; Dead end or loop!  TO DO: try other branches
                           return (prog1 object (reclaim-gensym-list objects))
                         when (loop for class in join-classes?
                                    thereis
                                    (frame-of-class-p next-object class))
                           return (prog1 next-object
                                    (reclaim-gensym-list objects)))
                   activity)))
        (or (bottommost-flow-signal-for-g2gl-activity object)
            object))))


;;; The `join class' of a <switch>, <pick>, or <flow> activity is the class of
;;; the join bar object at the bottom.

(defun join-classes-of-activity (activity)
  (frame-class-case activity
    (g2gl-switch-fork '(g2gl-switch-join))
    (g2gl-pick '(g2gl-pick-join))
    (g2gl-flow-split '(g2gl-flow-sync
                       g2gl-flow-discriminator
                       g2gl-n-out-of-m-flow-join
                       g2gl-flow-terminator))))


;;; The `successor' of an activity is the next activity connected to its exit
;;; object, or a join bar or nil if there is no next activity.

(defun successor-of-activity (activity)
  (let ((object (g2gl-activity-bottom-output-object
                  (exit-object-of-activity activity))))
    (if (and object (eq (class object) 'g2gl-flow-gate))
        (get-activity-from-entry-object object)
        object)))


;;; Collect a sequence of activities, starting from start-activity and
;;; working downward, into a gensym list.  Stop-object-or-class is either a
;;; specific G2GL object or a class of G2GL objects to stop at.  The stop object
;;; will not be included in the sequence.  If start-activity is the only element
;;; of the sequence, it will be returned instead of a singleton list.  If
;;; start-activity is the stop object, nil will be returned.

(defun collect-sequence-or-activity (start-activity
                                      &optional stop-object-or-class-or-classes)
  (let ((sequence
          (loop for activity = start-activity
                             then (successor-of-activity activity)
                while activity
                until (if (atom stop-object-or-class-or-classes)
                          (or (eq activity stop-object-or-class-or-classes)
                              (eq (class activity)
                                  stop-object-or-class-or-classes))
                          (memq (class activity)
                                stop-object-or-class-or-classes))
                until (memq activity sequence)
                collect activity into sequence using gensym-cons
                finally (return sequence))))
    (if (and sequence (null (cdr sequence)))
        (prog1 (car sequence) (reclaim-gensym-list sequence))
        sequence)))


;;; The function `upper-left-corner-of-g2gl-objects-in-body' returns the minimum
;;; x and y of the G2GL objects in the G2GL body currently being laid out.

(defun upper-left-corner-of-g2gl-objects-in-body ()
  (loop for block being each subblock of g2gl-body-being-laid-out
        when (frame-of-class-p block 'g2gl-object)
          minimize (left-edge-of-block block) into x
        and
          minimize (top-edge-of-block block) into y
        finally (return (values x y))))




;;;; Redoing the layout of existing G2GL objects and their connections.

;;; The function `redo-layout-of-g2gl-object' redoes the layout of a G2GL
;;; object.

(defun redo-layout-of-g2gl-object (object)
  (move-existing-layout-to-x-y object object 0 0)
  (make-bpel-layout (width-of-block object) (height-of-block object)
                    object object (gensym-list object)))


;;; The function `redo-layout-of-g2gl-objects' redoes the layout of a list of
;;; G2GL objects, from top to bottom, with the given vertical spacing, if
;;; provided.

(defun redo-layout-of-g2gl-objects
    (objects &optional (spacing bpel-layout-border-size))
  (let ((layouts (loop for object in objects
                       collect (redo-layout-of-g2gl-object object)
                         using gensym-cons)))
    (prog1 (arrange-layouts-vertically layouts spacing)
      (reclaim-bpel-layouts layouts))))


;;; The function `redo-layout-of-sequence-activity' redoes the layout of a
;;; G2GL <sequence> activity.

(defun redo-layout-of-sequence-activity
    (sequence &optional (spacing bpel-layout-border-size))
  (let ((layouts (loop for activity in sequence
                       collect (redo-layout-of-activity activity)
                         using gensym-cons)))
    (prog1 (arrange-layouts-vertically layouts spacing)
      (reclaim-bpel-layouts layouts))))


;;; The function `redo-layout-of-while-activity' redoes the layout of a G2GL
;;; <while> activity.

(defun redo-layout-of-while-activity (activity)
  (let ((while-body-object
          (bpel-activity-right-output-object activity)))
    (if while-body-object
        (let* ((while-body
                 (collect-sequence-or-activity
                   (get-activity-from-entry-object while-body-object)
                   activity))
               (while-body-layout
                 (redo-layout-of-activity while-body))
               (while-body-entry-block
                 (bpel-layout-entry-activity while-body-layout))
               (while-body-exit-block
                 (bpel-layout-exit-activity while-body-layout))
               (while-body-output-connection-x
                 (midline-x-of-block while-body-exit-block))
               (while-object-output-connection-y
                 (roundw (height-of-block activity) 3))
               (while-body-y-offset
                 (+w default-stub-length while-object-output-connection-y))
               (layouts
                 (gensym-list
                   (redo-layout-of-g2gl-object activity)
                   while-body-layout)))

          ;; Put the while-body to the right of the while object.
          (bpel-layout-bind
              (width height entry-block exit-block blocks)
              (arrange-layouts-horizontally layouts)
            (declare (ignore entry-block exit-block))

            ;; Shift the while body down to make room for the input connection
            ;; to come in from the top.
            (move-existing-layout-to-x-y
              while-body-entry-block
              (bpel-layout-blocks while-body-layout)
              (left-edge-of-block while-body-entry-block)
              while-body-y-offset)

            ;; Adjust the total height for this downshift if needed.
            (setf height
                  (maxw height (+w (bpel-layout-height while-body-layout)
                               while-body-y-offset)))

            ;; Move the connection from the while object to the top of the
            ;; while-body.
            (clean-up-connection
              (g2gl-activity-default-input-connection
                (bpel-layout-entry-activity while-body-layout))
              nil 'right 'top
              while-object-output-connection-y)

            ;; Bend the connection from the while-body back to the while
            ;; object.
            (let ((back-connection
                    (g2gl-activity-default-output-connection
                      (bpel-layout-exit-activity while-body-layout))))
              (when back-connection
                (clean-up-connection
                  back-connection
                  (gensym-list
                    default-stub-length
                    (-w (+w while-body-output-connection-x
                            (halfw bpel-layout-border-size))))
                  'bottom 'right
                  ;; Position the input end at the midpoint of the bottom of the
                  ;; while body exit block:
                  (halfw (width-of-block (bpel-layout-exit-activity
                                           while-body-layout)))
                  ;; Position the output end two-thirds down the right side of
                  ;; the while activity:
                  (roundw (twicew (height-of-block activity)) 3))))

            ;; Add vertical room for the latter connection if needed.
            (setf height
                  (maxw height
                        (+w (bottom-edge-of-block while-body-exit-block)
                            default-stub-length)))

            (when (consp while-body) (reclaim-gensym-list while-body))
            (reclaim-bpel-layouts layouts)
            (make-bpel-layout width height activity activity blocks)))

        ;; Otherwise, there's no body, just redo the while object itself.
        (redo-layout-of-g2gl-object activity))))

;;; The function `redo-layout-of-switch-activity' redoes the layout of a G2GL
;;; <switch> activity.

(defun redo-layout-of-switch-activity (activity)
  (let* ((else-connections nil)
         (implicit-otherwise-p nil)
         (last-fork nil)
         (branch-layouts
           (loop for fork = activity
                          then (bpel-activity-right-output-object fork)
                 while fork
                 until (memq fork forks)
                 for else-con = nil
                              then (g2gl-activity-default-input-connection fork)
                 when else-con do (gensym-push else-con else-connections)
                 collect fork into forks using gensym-cons
                 finally  (reclaim-gensym-list forks)
                 for otherwise-p = (not (eq (class fork) 'g2gl-switch-fork))
                 unless otherwise-p do (setq last-fork fork)
                 for case-entry-object = (if otherwise-p
                                             fork
                                             (g2gl-activity-bottom-output-object
                                               fork))
                 for case-activity = (when case-entry-object
                                       (collect-sequence-or-activity
                                         (get-activity-from-entry-object
                                           case-entry-object)
                                         'g2gl-switch-join))
                 for case-activity-layout = (when case-activity
                                              (redo-layout-of-activity
                                                case-activity))
                 when otherwise-p
                   when case-activity-layout
                     collect case-activity-layout using gensym-cons
                   else
                     do (setq implicit-otherwise-p t)
                 else
                   collect (let ((fork-layout
                                   (redo-layout-of-g2gl-object fork)))
                             (if case-activity-layout
                                 (let ((layouts
                                         (gensym-list
                                           fork-layout
                                           case-activity-layout)))
                                   ;; Put each switch-fork object above its
                                   ;; <case> activity.
                                   (prog1 (arrange-layouts-vertically layouts)
                                     (reclaim-bpel-layouts layouts)))
                                 fork-layout))
                   using gensym-cons
                 when (consp case-activity)
                   do (reclaim-gensym-list case-activity)
                 until otherwise-p))
         (n-branches (length branch-layouts))
         (branches-layout
           ;; Put the branches side by side.
           (arrange-layouts-horizontally branch-layouts))
         (right-edge-of-last-fork
           ;; Save this position relative to branches-layout, for setting the
           ;; delta-or-deltas of the implicit-otherwise connection (see below).
           (right-edge-of-block last-fork))
         (join-bar
           (g2gl-activity-bottom-output-object
             (bpel-layout-exit-activity branches-layout))))

    ;; Clean up the "else" connections between the branches.
    (loop for else-con in else-connections
          do (clean-up-connection else-con nil 'right))

    (let ((layouts
            (if (and join-bar (eq (class join-bar) 'g2gl-switch-join))
                (gensym-list
                  branches-layout
                  (redo-layout-of-g2gl-object join-bar))
                (gensym-list
                  branches-layout))))

      (when implicit-otherwise-p
        ;; Add room for the final else connection going down to the join bar.
        (incfw (bpel-layout-width branches-layout)
               (halfw bpel-layout-border-size))
        (incff n-branches))

      ;; Put the join bar at the bottom.
      (prog1
          (arrange-layouts-vertically
            layouts (room-for-g2gl-connections n-branches))
        ;; Fix up the join connections so their bends don't overlap.
        (loop for (nil nil nil exit-block nil) in branch-layouts
              for i from 1
              for join-connection = (g2gl-activity-bottom-output-connection
                                      exit-block)
              when join-connection
                do (let ((join-bar (output-end-object join-connection)))
                     (clean-up-connection
                       join-connection
                       (-w (top-edge-of-block join-bar)
                           (bottom-edge-of-block exit-block)
                           (bend-distance-of-ith-g2gl-connection
                             i n-branches))
                       'bottom 'top
                       (halfw (width-of-block exit-block))
                       (position-of-ith-g2gl-connection
                         i join-bar 'top n-branches))))

        (when implicit-otherwise-p
          (let* ((last-else-connection
                   (bpel-activity-right-output-connection last-fork))
                 (join-bar
                   (output-end-object last-else-connection)))
            ;; Redirect the else connection of the last fork down the right side
            ;; of the layout.
            (clean-up-connection
              last-else-connection
              (gensym-list
                (-w (bpel-layout-width branches-layout)
                    right-edge-of-last-fork)
                (-w (top-edge-of-block join-bar)
                    (midline-y-of-block last-fork)
                    default-stub-length))
              'right 'top
              (halfw (height-of-block last-fork))
              (position-of-ith-g2gl-connection
                n-branches join-bar 'top n-branches))))

        (reclaim-bpel-layouts branch-layouts)
        (reclaim-bpel-layouts layouts)
        (reclaim-gensym-list else-connections)))))


;;; The function `redo-layout-of-parallel-activity' redoes the layout of a G2GL
;;; <flow> or <pick> activity.

(defun redo-layout-of-parallel-activity (activity)
  (let* ((entry-objects
           (get-next-g2gl-activities-from-g2gl-activity activity))
         (n-branches (length entry-objects))
         (join-classes (join-classes-of-activity activity))
         (branch-layouts
           (loop for entry-object in entry-objects
                 for activity = (collect-sequence-or-activity
                                  (get-activity-from-entry-object entry-object)
                                  join-classes)
                 when activity
                   collect (redo-layout-of-activity activity)
                     using gensym-cons
                 when (consp activity)
                   do (reclaim-gensym-list activity)))
         (branches-layout
           (when branch-layouts
             ;; Put the branches side by side.
             (arrange-layouts-horizontally branch-layouts)))
         (join-bar
           (when branches-layout
             (g2gl-activity-bottom-output-object
               (bpel-layout-exit-activity branches-layout))))
         (layouts (gensym-list (redo-layout-of-g2gl-object activity))))

    (when branches-layout
      (gensym-push branches-layout layouts))
    (when (and join-bar (memq (class join-bar) join-classes))
      (gensym-push (redo-layout-of-g2gl-object join-bar) layouts))

    ;; Put the split bar at the top and the join bar at the bottom.
    (prog1 (arrange-layouts-vertically
             (nreverse layouts) (room-for-g2gl-connections n-branches))

      ;; Fix up the split and join connections so their bends don't overlap.
      (loop for (nil nil entry-block exit-block nil) in branch-layouts
            for i from 1
            for delta = (bend-distance-of-ith-g2gl-connection i n-branches)
            for split-connection = (g2gl-activity-top-input-connection
                                     entry-block)
            do (clean-up-connection
                 split-connection delta
                 'bottom 'top
                 (position-of-ith-g2gl-connection
                   i activity 'bottom n-branches))
            for join-connection = (g2gl-activity-default-output-connection
                                    exit-block)
            when join-connection
              do (let ((join-bar (output-end-object join-connection)))
                   (clean-up-connection
                     join-connection
                     (-w (top-edge-of-block join-bar)
                         (bottom-edge-of-block exit-block)
                         delta)
                     'bottom 'top
                     (halfw (width-of-block exit-block))
                     (position-of-ith-g2gl-connection
                       i join-bar 'top n-branches))))

      (reclaim-bpel-layouts branch-layouts)
      (reclaim-bpel-layouts layouts)
      (reclaim-gensym-list entry-objects))))


;;; The function `redo-layout-of-invoke-activity' redoes the layout of a G2GL
;;; <invoke> activity, putting its local handlers in a column to the right.

(defun redo-layout-of-invoke-activity (activity)
  (let* ((invoke-layout (redo-layout-of-g2gl-object activity))
         (local-handlers
           (collect-g2gl-invoke-local-handlers activity))
         (handler-layouts
           ;; Collect the local handler layouts.
           (loop for handler in local-handlers
                 collect (redo-layout-of-g2gl-object handler)
                   using gensym-cons
                 finally (reclaim-gensym-list local-handlers))))
    (if handler-layouts
        ;; Layout the local handlers vertically.
        (let* ((handlers-layout (arrange-layouts-vertically handler-layouts))
               (layouts (gensym-list invoke-layout handlers-layout)))
          ;; Put them to the right of the invoke block.
          (bpel-layout-bind (width height in out blocks)
              (arrange-layouts-horizontally
                layouts
                (room-for-g2gl-connections (length handler-layouts) 'right))
            (declare (ignore in out))
            ;; Fix up the handler connections so their bends don't overlap.
            (loop with n = (length handler-layouts)
                  for (nil nil handler nil nil) in handler-layouts
                  for i from 1
                  for delta = (bend-distance-of-ith-g2gl-connection i n 'right)
                  for in-conn = (g2gl-activity-default-input-connection handler)
                  for input-end-position = (position-of-ith-g2gl-connection
                                             i activity 'right n)
                  do (clean-up-connection
                       in-conn delta 'right 'left
                       input-end-position
                       (if (=f i 1)
                           ;; Make the top connection go straight across instead
                           ;; of bending down to the middle of the left side of
                           ;; the handler.
                           input-end-position
                           (halfw (height-of-block handler)))))
            (reclaim-bpel-layouts handler-layouts)
            (reclaim-bpel-layouts layouts)
            (make-bpel-layout width height activity activity blocks)))
        (gensym-dstruct-bind ((width height nil nil blocks) invoke-layout)
          (reclaim-bpel-layout invoke-layout)
          (make-bpel-layout width height activity activity blocks)))))


;;; The function `redo-layout-of-activity' redoes the layout of a G2GL activity,
;;; including its flow links.

(defvar activities-currently-being-laid-out)

(defun redo-layout-of-activity (activity)
  (if (consp activity)
      (redo-layout-of-sequence-activity activity)
      (bpel-layout-bind (width height entry-block exit-block blocks)
          (if (memq activity activities-currently-being-laid-out)
              (redo-layout-of-g2gl-object activity)
              (progn
                (gensym-push activity activities-currently-being-laid-out)
                (prog1
                    (frame-class-case activity
                      (g2gl-while
                        (redo-layout-of-while-activity activity))
                      (g2gl-switch-fork
                        (redo-layout-of-switch-activity activity))
                      ((g2gl-flow-split g2gl-pick)
                       (redo-layout-of-parallel-activity activity))
                      (g2gl-invoke
                        (redo-layout-of-invoke-activity activity))
                      (otherwise
                        (redo-layout-of-g2gl-object activity)))
                  (gensym-pop activities-currently-being-laid-out))))

        (let ((spacing (halfw bpel-layout-border-size))
              (flow-gates
                (nreverse
                  (collect-flow-gates-for-bpel-activity entry-block)))
              (flow-signals
                (collect-flow-signals-for-bpel-activity exit-block)))

          (when flow-gates
            ;; Put the gates centered above the entry-block.
            (bpel-layout-bind
                (gates-width gates-height first-gate last-gate gates)
                (redo-layout-of-g2gl-objects flow-gates spacing)
              (declare (ignore gates-width)) ;assumed small enough to not matter
              (declare (ignore last-gate))
              (move-existing-layout-to-x-y
                first-gate
                gates
                (-w (midline-x-of-block entry-block)
                    (midline-x-of-block first-gate))
                0)
              (move-existing-layout-to-x-y
                entry-block
                blocks
                (left-edge-of-block entry-block)
                (+w gates-height spacing))
              (setq height (+w gates-height spacing height))

              ;; Remove all bends from the gates connection.
              (clean-up-connection
                (g2gl-activity-default-input-connection entry-block))

              (setq entry-block first-gate)
              (setq blocks (nconc gates blocks))
              (reclaim-gensym-list flow-gates)))

          (when flow-signals
            ;; Put the signals centered below the exit-block.
            (bpel-layout-bind
                (signals-width signals-height first-signal last-signal signals)
                (redo-layout-of-g2gl-objects flow-signals spacing)
            (declare (ignore signals-width)) ;assumed small enough to not matter
            (declare (ignore signals-height))
            (move-existing-layout-to-x-y
              first-signal
              signals
              (-w (midline-x-of-block exit-block)
                  (midline-x-of-block first-signal))
              (+w (bottom-edge-of-block exit-block) spacing))
            (setq height (maxw height (bottom-edge-of-block last-signal)))

            ;; Remove all bends from the signals connection.
            (clean-up-connection
              (g2gl-activity-default-output-connection exit-block))

            (setq exit-block last-signal)
            (setq blocks (nconc blocks signals))
            (reclaim-gensym-list flow-signals)))

          (make-bpel-layout width height entry-block exit-block blocks)))))


;;; Fix up the end-position sides and bend distance of a g2gl-connection-link
;;; connection.

(defun redo-layout-of-flow-link-connection (connection)
  (let* ((signal (input-end-object connection))
         (gate (output-end-object connection))
         (left-to-right-p (left-edge-of-block-lessp signal gate)))
    (clean-up-connection
      connection
      (if left-to-right-p
          (-w (left-edge-of-block gate)
              (right-edge-of-block signal)
              default-stub-length)
          (-w (-w (left-edge-of-block signal)
                  (right-edge-of-block gate)
                  default-stub-length)))
      (if left-to-right-p 'right 'left))))


;;; The function `redo-layout-of-flow-link-connections' fixes up the
;;; g2gl-connection-link connections of the G2GL body currently being laid out.

(defun redo-layout-of-flow-link-connections ()
  (loop for block being each subblock of g2gl-body-being-laid-out
        when (eq (class block) 'g2gl-flow-signal)
          do (let ((c (get-link-connection-of-flow-signal block)))
               (when c (redo-layout-of-flow-link-connection c)))))



;;; The function `redo-layout-of-g2gl-body' redoes the layout of a G2GL body.

(defun redo-layout-of-g2gl-body (body)
  (let ((layouts nil)
        (g2gl-body-being-laid-out body)
        (activities-currently-being-laid-out
          nil))
    (multiple-value-bind
        (arg-variables partner-links correlation-variables variables
         fault-handlers compensation-handlers event-handlers
         entry-objects)
        (collect-g2gl-body-elements g2gl-body-being-laid-out)

      (multiple-value-bind (x y) (upper-left-corner-of-g2gl-objects-in-body)

        (when arg-variables
          (gensym-push (redo-layout-of-g2gl-objects
                         arg-variables
                         bpel-variable-y-spacing-size)
                       layouts)
          (reclaim-gensym-list arg-variables))

        (when partner-links
          (gensym-push (redo-layout-of-g2gl-objects
                         partner-links
                         bpel-variable-y-spacing-size)
                       layouts)
          (reclaim-gensym-list partner-links))

        (when correlation-variables
          (gensym-push (redo-layout-of-g2gl-objects
                         correlation-variables
                         bpel-variable-y-spacing-size)
                       layouts)
          (reclaim-gensym-list correlation-variables))

        (when variables
          (gensym-push (redo-layout-of-g2gl-objects
                         variables
                         bpel-variable-y-spacing-size)
                       layouts)
          (reclaim-gensym-list variables))

        (when fault-handlers
          (gensym-push (redo-layout-of-g2gl-objects fault-handlers)
                       layouts)
          (reclaim-gensym-list fault-handlers))

        (when compensation-handlers
          (gensym-push (redo-layout-of-g2gl-objects compensation-handlers)
                       layouts)
          (reclaim-gensym-list compensation-handlers))

        (when event-handlers
          (gensym-push (redo-layout-of-g2gl-objects event-handlers) layouts)
          (reclaim-gensym-list event-handlers))

        (loop for entry-object in entry-objects
              for activity = (collect-sequence-or-activity
                               (get-activity-from-entry-object entry-object))
              do (gensym-push (redo-layout-of-activity activity) layouts)
              when (consp activity) do (reclaim-gensym-list activity)
              finally (reclaim-gensym-list entry-objects))

        (setq layouts (nreverse layouts))

        (bpel-layout-bind (width height entry-block exit-block blocks)
            (arrange-layouts-vertically layouts)
          (when blocks
            (redo-layout-of-flow-link-connections)
            (move-existing-layout-to-x-y
              entry-block blocks (+w x (left-edge-of-block entry-block)) y)
            (shrink-wrap-workspace g2gl-body-being-laid-out)
            (reclaim-bpel-layouts layouts))
          (make-bpel-layout width height entry-block exit-block blocks))))))



;;;; Convert compilation structures to list routines

;; `class-to-from-list' creates copy of object list structure if obj is list
;; otherwise returns obj. list fields are not copied
(defun class-to-from-list (obj options)
  (declare (ignore options))
  (copy-tree-using-gensym-conses-no-value obj))

;; modified actual-copy-tree-using-x-conses with enhanced "atom" predicate
(defun-simple copy-tree-using-gensym-conses-no-value (tree?)
  (cond ((or (not (consp tree?))
             (no-value-p tree?)) ; no-value is an atom here
         tree?)
        ((evaluation-truth-value-p tree?)
         (if (evaluation-truth-value-true-p tree?)
           g2gl-true
           g2gl-false))
        (t
         (loop with new-list = (gensym-cons-macro
                                (copy-tree-using-gensym-conses-no-value (car tree?))
                                (cdr tree?))
               with last-new-cons = new-list
               with current-copy-position = (cdr tree?)
               until (atom current-copy-position)
               do (setf (cdr last-new-cons)
                          (gensym-cons-macro
                           (copy-tree-using-gensym-conses-no-value
                            (car current-copy-position))
                           (cdr current-copy-position)))
                  (setf last-new-cons (cdr last-new-cons))
                  (setf current-copy-position
                          (cdr current-copy-position))
               finally (return new-list)))))

;; `list-of-objects-to-list' creates list that contains results of 'func' function
;; calling for each objects from 'objects' parameter.
(defun list-of-objects-to-list (func objects options)
  (loop for obj = objects then (cdr obj)
			until (or (null obj)  (no-value-p obj))
	  collect (if (atom obj)  (return obj) (funcall func (car obj) options)) using gensym-cons))

;; routines that convert g2gl-text-box-compilation object to list
;; and vice versa

(defun g2gl-text-box-compilation-to-list (g2gl-text-box-compilation options)
  (when g2gl-text-box-compilation
    (gensym-list
      (class-to-from-list
        (g2gl-text-box-position g2gl-text-box-compilation) options)
      (class-of-g2gl-text-box g2gl-text-box-compilation)
      (text-of-g2gl-text-box g2gl-text-box-compilation))))

(defun make-g2gl-text-box-compilation-from-list (fields options)
  (when fields
    (let ((g2gl-text-box-compilation (make-g2gl-text-box-compilation)))

      (setf (g2gl-text-box-position g2gl-text-box-compilation)
          (class-to-from-list (first fields) options))
      (setf (class-of-g2gl-text-box g2gl-text-box-compilation) (second fields))
      (setf (text-of-g2gl-text-box g2gl-text-box-compilation) (third fields))
    
      g2gl-text-box-compilation)))
  

;; routines that convert g2gl-activity-compilation structure to list
;; and vice versa
(defmacro aggregate-g2gl-activity-compilation-to-list-code (g2gl-activity-compilation-structure 
                                                            options)
  (when (null g2gl-activity-implementations-alist)
    (warn "**** g2gl-activity-implementations-alist is nil; something's wrong! ****"))
  `(fixnum-case (g2gl-activity-class-code ,g2gl-activity-compilation-structure)
     ,@(loop for (class-name slots)
                 in g2gl-activity-implementations-alist
             collect `((,(map-g2gl-activity-class-to-code class-name)
                        ,@(if (eq class-name substitute-for-non-activity-class)
                               `(,non-activity-class-code)))
                (return (,(build-ab-symbol class-name 'activity-compilation 'to-list)
                          ,g2gl-activity-compilation-structure ,options))))))

(defmacro aggregate-g2gl-activity-compilation-from-list-code (fields options)
  (when (null g2gl-activity-implementations-alist)
    (warn "**** g2gl-activity-implementations-alist is nil; something's wrong! ****"))
  `(fixnum-case (car fields)
     ,@(loop for (class-name slots)
                 in g2gl-activity-implementations-alist
             collect `((,(map-g2gl-activity-class-to-code class-name)
                        ,@(if (eq class-name substitute-for-non-activity-class)
                               `(,non-activity-class-code)))
                (return (,(build-ab-symbol 'make class-name 'activity-compilation 'from-list)
                          ,fields ,options))))))

(defun g2gl-activity-compilation-structure-to-list (g2gl-activity-compilation-structure options)
  (let* ((index 
              (position g2gl-activity-compilation-structure (activity-compilations-list options))))
        ;; index it's position from the begin of the list
        ;; need to return the position from the end, 
        ;; becouse some elements can be added from the begin.
        (cond
          (index
           (-f (activity-compilations-count options) index))
          (g2gl-activity-compilation-structure
	   (gensym-push g2gl-activity-compilation-structure (activity-compilations-list options))
           (incff (activity-compilations-count options))
           (block nil
              (aggregate-g2gl-activity-compilation-to-list-code
                 g2gl-activity-compilation-structure
                 options))))))


(defun make-g2gl-activity-compilation-structure-from-list (fields options)
 (cond
  ((fixnump fields) ; it is an index
   (nth (-f (activity-compilations-count options) fields)
        (activity-compilations-list options)))
  (fields
   (block nil 
      (aggregate-g2gl-activity-compilation-from-list-code fields options)))))

;; routines that convert g2gl-attribute-display-compilation object to list
;; and vice versa

(defun g2gl-attribute-display-compilation-to-list (g2gl-attribute-display-compilation options)
  (when g2gl-attribute-display-compilation
    (gensym-list
      (class-to-from-list
        (g2gl-attribute-display-position g2gl-attribute-display-compilation) options)
      (g2gl-attribute-display-table-header g2gl-attribute-display-compilation)
      (class-to-from-list
        (g2gl-attribute-display-rows g2gl-attribute-display-compilation) options))))

(defun make-g2gl-attribute-display-compilation-from-list (fields options)
  (when fields
    (let* ((g2gl-attribute-display-compilation (make-g2gl-attribute-display-compilation)))
      
      (setf (g2gl-attribute-display-position g2gl-attribute-display-compilation)
          (class-to-from-list (first fields) options))
      (setf (g2gl-attribute-display-table-header g2gl-attribute-display-compilation)
          (second fields))
      (setf (g2gl-attribute-display-rows g2gl-attribute-display-compilation)
          (class-to-from-list (third fields) options))
    
      g2gl-attribute-display-compilation)))
    
;; routines that convert g2gl-body-compilation object to list
;; and vice versa
(defun g2gl-body-compilation-to-list (g2gl-body-compilation options)
  (when g2gl-body-compilation
    (gensym-list
      (class-to-from-list
        (g2gl-execution-display-title-position g2gl-body-compilation) options)
      (class-to-from-list
        (g2gl-variable-compilations g2gl-body-compilation) options)
      (list-of-objects-to-list #'g2gl-activity-compilation-structure-to-list
        (g2gl-fault-handler-compilations g2gl-body-compilation) options)
      (list-of-objects-to-list #'g2gl-activity-compilation-structure-to-list
        (g2gl-compensation-handler-compilations g2gl-body-compilation) options)
      (list-of-objects-to-list #'g2gl-activity-compilation-structure-to-list
        (g2gl-event-handler-compilations g2gl-body-compilation) options)
      (list-of-objects-to-list #'g2gl-text-box-compilation-to-list
        (g2gl-text-box-compilations g2gl-body-compilation) options)
      (g2gl-activity-compilation-structure-to-list
        (flowchart-entry-activity-compilation g2gl-body-compilation) options)
      (class-to-from-list
        (out-connection-representation-stream g2gl-body-compilation) options)
      (next-body-element-index-to-assign g2gl-body-compilation)
      (number-of-body-compilation-errors-and-warnings g2gl-body-compilation)
      (execution-display-for-superimposed-tracings g2gl-body-compilation))))

(defun make-g2gl-body-compilation-from-list (fields options)
  (when fields
    (let* ((g2gl-body-compilation (make-g2gl-body-compilation))
         (field fields))
    
      (setf (g2gl-execution-display-title-position g2gl-body-compilation)
          (class-to-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (g2gl-variable-compilations g2gl-body-compilation)
          (class-to-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (g2gl-fault-handler-compilations g2gl-body-compilation)
          (list-of-objects-to-list #'make-g2gl-activity-compilation-structure-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (g2gl-compensation-handler-compilations g2gl-body-compilation)
          (list-of-objects-to-list #'make-g2gl-activity-compilation-structure-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (g2gl-event-handler-compilations g2gl-body-compilation)
          (list-of-objects-to-list #'make-g2gl-activity-compilation-structure-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (g2gl-text-box-compilations g2gl-body-compilation)
          (list-of-objects-to-list #'make-g2gl-text-box-compilation-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (flowchart-entry-activity-compilation g2gl-body-compilation)
          (make-g2gl-activity-compilation-structure-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (out-connection-representation-stream g2gl-body-compilation)
          (class-to-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (next-body-element-index-to-assign g2gl-body-compilation) (car field))
      (setf field (cdr field))
    
      (setf (number-of-body-compilation-errors-and-warnings g2gl-body-compilation) (car field))
      (setf field (cdr field))
    
      (setf (execution-display-for-superimposed-tracings g2gl-body-compilation) (car field))

      g2gl-body-compilation)))
  
;; routines that convert g2gl-activity-compilation object to list
;; and vice versa

(defun g2gl-body-element-position-to-list (g2gl-body-element-position)
  (cond
   ((consp g2gl-body-element-position)
    (gensym-list (car g2gl-body-element-position) (cdr g2gl-body-element-position)))
   (t
    g2gl-body-element-position)))

(defun make-g2gl-body-element-position-from-list (fields)
  (cond
   ((consp fields)
    (make-g2gl-body-position (first fields) (second fields)))
   (t
    fields)))

(defun g2gl-activity-compilation-to-list (g2gl-activity-compilation options)
  (when g2gl-activity-compilation
    (gensym-list
      (g2gl-body-element-position-to-list 
        (g2gl-body-element-position g2gl-activity-compilation))
      (g2gl-body-element-index g2gl-activity-compilation)
      (g2gl-activity-class-code g2gl-activity-compilation)
      (g2gl-activity-name g2gl-activity-compilation)
      (list-of-objects-to-list #'g2gl-attribute-display-compilation-to-list
        (g2gl-attribute-display-compilations g2gl-activity-compilation) options)
      (list-of-objects-to-list #'g2gl-activity-compilation-structure-to-list
        (activity-compilation-successors g2gl-activity-compilation) options)
      (class-to-from-list
        (g2gl-expression-compilation g2gl-activity-compilation) options)
      (g2gl-body-compilation-to-list
        (g2gl-body-compilation g2gl-activity-compilation) options))))

(defun make-g2gl-activity-compilation-from-list (fields options)
  (when fields
    (let* ((g2gl-activity-compilation (make-g2gl-activity-compilation))
         (field fields))
    
      (setf (g2gl-body-element-position g2gl-activity-compilation)
          (make-g2gl-body-element-position-from-list (car field)))
      (setf field (cdr field))
    
      (setf (g2gl-body-element-index g2gl-activity-compilation) (car field))
      (setf field (cdr field))
    
      (setf (g2gl-activity-class-code g2gl-activity-compilation) (car field))
      (setf field (cdr field))
    
      (setf (g2gl-activity-name g2gl-activity-compilation) (car field))
      (setf field (cdr field))
    
      (setf (g2gl-attribute-display-compilations g2gl-activity-compilation)
          (list-of-objects-to-list #'make-g2gl-attribute-display-compilation-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (activity-compilation-successors g2gl-activity-compilation)
          (list-of-objects-to-list #'make-g2gl-activity-compilation-structure-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (g2gl-expression-compilation g2gl-activity-compilation)
          (class-to-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (g2gl-body-compilation g2gl-activity-compilation)
          (make-g2gl-body-compilation-from-list (car field) options))
    
      g2gl-activity-compilation)))
  
  
;; routines that convert g2gl-compilation-version object to list
;; and vice versa

(defun g2gl-compilation-version-to-list (g2gl-compilation-version)
  (when g2gl-compilation-version
     (let* ((options (make-g2gl-activity-options g2gl-compilation-version))
            (result
              (gensym-list
                (g2gl-activity-compilation-to-list
                    g2gl-compilation-version options)
                (source-g2gl-process g2gl-compilation-version)
                (class-to-from-list
                   (alist-of-g2gl-operation-names-for-instantiation
                       g2gl-compilation-version)
                   options)
                (compilation-version-number g2gl-compilation-version)
                (number-of-compilation-errors g2gl-compilation-version)
                (number-of-compilation-warnings g2gl-compilation-version)
                (next-variable-index-to-assign g2gl-compilation-version))))

       (reclaim-g2gl-activity-options options)
       result)))


(defmacro move-ac (src dst)
  `(progn
     ,@(loop for ac-slot-name in '(g2gl-body-element-position
                                   g2gl-body-element-index
                                   g2gl-activity-class-code
                                   g2gl-activity-name
                                   g2gl-attribute-display-compilations
                                   activity-compilation-successors
                                   g2gl-expression-compilation
                                   g2gl-body-compilation)
             collect `(progn
                        (setf (,ac-slot-name ,dst)
                              (,ac-slot-name ,src))
                        (setf (,ac-slot-name ,src) nil)))))

(defun make-g2gl-compilation-version-from-list (fields)
  (when fields
    (let* ((g2gl-compilation-version (make-g2gl-compilation-version))
           (options (make-g2gl-activity-options g2gl-compilation-version))
           (ac (make-g2gl-activity-compilation-from-list (first fields) options))
           (field (cdr fields)))
    
      (move-ac ac g2gl-compilation-version)
    
      (setf (source-g2gl-process g2gl-compilation-version) (car field))
      (setf field (cdr field))
    
      (setf (alist-of-g2gl-operation-names-for-instantiation g2gl-compilation-version)
          (class-to-from-list (car field) options))
      (setf field (cdr field))
    
      (setf (compilation-version-number g2gl-compilation-version) (car field))
      (setf field (cdr field))
    
      (setf (number-of-compilation-errors g2gl-compilation-version) (car field))
      (setf field (cdr field))
    
      (setf (number-of-compilation-warnings g2gl-compilation-version) (car field))
      (setf field (cdr field))
    
      (setf (next-variable-index-to-assign g2gl-compilation-version) (car field))
    
      (reclaim-g2gl-activity-compilation ac)
      (reclaim-g2gl-activity-options options)
      g2gl-compilation-version)))
  
  

;; Save compilation structure to and load that from KB routines
(defun create-compilation-structure (g2gl-process)
  (delete-compilation-structure g2gl-process)
  (when (stack-of-compilation-versions g2gl-process)
    (setf (packed-compilation-version g2gl-process)
      (g2gl-compilation-version-to-list
        (first (stack-of-compilation-versions g2gl-process))))))

(defun delete-compilation-structure (g2gl-process &optional v?)
  (when (packed-compilation-version g2gl-process)
    (let ((objects-to-delete
             (destroy-list-for-compilation-structure
               (packed-compilation-version g2gl-process) v?)))
      (when v?
        (setf (orphaned-strings v?) objects-to-delete)))
    (setf (packed-compilation-version g2gl-process) nil)))

(defun restore-compilation-structure (g2gl-process)
  (when (packed-compilation-version g2gl-process)
    (let* ((v (make-g2gl-compilation-version-from-list
                 (packed-compilation-version g2gl-process)))
             (body (first (subworkspaces g2gl-process))))
      (change-slot-value g2gl-process 'latest-attempted-compilation-version-number
                         (compilation-version-number v))
      (change-slot-value g2gl-process 'latest-attempted-compilation-version-time
                         (get-current-frame-edit-timestamp))
      (change-slot-value g2gl-process 'number-of-errors-in-latest-attempted-compilation
                         (number-of-compilation-errors v))
      (change-slot-value g2gl-process 'number-of-warnings-in-latest-attempted-compilation
                         (number-of-compilation-warnings v))
      (change-slot-value g2gl-process 'g2gl-process-compilation-version-number
                         (copy-for-slot-value (latest-attempted-compilation-version-number g2gl-process)))
      (change-slot-value g2gl-process 'g2gl-process-compilation-version-time
                         (copy-for-slot-value (latest-attempted-compilation-version-time g2gl-process)))
      (change-slot-value g2gl-process 'g2gl-process-procedure-signature
                         (compute-g2gl-process-body-procedure-signature g2gl-process))

      (setf (alist-of-g2gl-operation-names-for-instantiation v)
              (derive-alist-of-g2gl-operation-names-for-instantiation
                (flowchart-entry-activity-compilation (g2gl-body-compilation v))
                body
                (g2gl-body-compilation v) v))
      (when (alist-of-g2gl-operation-names-for-instantiation v)
        (loop for switch-name?
              in (or (names-of-g2gl-service-switches-for-instantiation g2gl-process)
                     '(nil))
              do (record-g2gl-process-for-instantiation
                   g2gl-process
                   (or switch-name? (name-of-g2gl-service-switch-for-connection g2gl-process)))))

      (slot-value-push v (stack-of-compilation-versions g2gl-process))
      (delete-compilation-structure g2gl-process v)
      v)))
  

;; Destroy compilation structure routines
(defun destroy-list-for-compilation-structure (cs-list &optional delete-objects?)
  (let (result)
    (loop for cs = cs-list then (cdr cs)
          for node = (car cs)
          for next-cs = (cdr cs)
          until (atom next-cs)
          do
       (cond
         ((evaluation-value-p-function node) nil)
         ;; GENSYMCID-861: G2GL-Process persistence problem managing sequence/structure
         ;; prevent NO-VALUE being reclaimed, see `copy-tree-using-gensym-conses-no-value'
         ((no-value-p node) nil)
         ((consp node)
          (let ((objects (destroy-list-for-compilation-structure node delete-objects?)))
            (setf result (nconc result objects))))
         ((and delete-objects? (text-string-p node))
           (gensym-push node result))
         (t nil)))
    
    (reclaim-gensym-list cs-list)
    
    result))

;;;; Recording Built-in G2GL-object-icon-descriptions



;; See documentation above, earlier in this module.

(set-up-variable-g2gl-object-icon-descriptions-info)


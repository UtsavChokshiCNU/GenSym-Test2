;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WORKSTATION

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David and Lowell B. Hawkinson





;;;; Forward References



(declare-forward-references
  (twrite-unix-time function)		; GRAMMAR0

  (extend-parsing-or-exit-editor-as-appropriate function edit1)

  (search-items-a-little   function queries)

  (find-workstation-context function new-menus)
  (run-event-handler function run)
  (find-event-interpretation function new-menus)
  (event-handler-refreshes-image-plane-p function new-menus)

  (do-g2-init-file?        variable kb-save2)
  (do-g2-init-file         function kb-save2)
  (clear-kb                function kb-save2)
  (do-g2-kb-load-at-launch function kb-save2)
  (reading-kb-p variable)
  (need-call-system-start  variable kb-merge)
  (system-start            function cycles)
  (loading-version-3-or-earlier-kb-p function)

  (initialize-for-asian-languages function kfep2)

  (notify-user-at-workstation function books)
  (enter-user-settings-editor function books)
  (hide-logbook-in-g2-window function books)
  (show-logbook-in-g2-window function books)

  #+development
  (update-telewindow-status-displays   function run)
  #+development
  (update-memory-allocation-displays   function run)
  #+development
  (key-name             function menus)
  
  (workstation-in-which-to-launch-recompilation? variable facilities)
  (launch-recompilation-for-this-kb              function facilities)

  (log-out-workstation                  function controls)
  (logged-in-workstation-session-p      function controls)
  (reclaim-dynamic-dialogs-call-dismissed function controls)

  #+development
  (check-memory                         function checkmemory)

  (completely-shut-down-g2              function commands1)
  (make-description-box                 function queries)
  (update-native-menu-bar               function) ; COMMANDS2
  (update-all-selection-highlights      function) ; COMMANDS0
  (call-twng-disconnect-callbacks       function) ; COMMANDS1
  (update-selection-highlights-on-workstation function) ; COMMANDS0
  (twrite-line-pattern-element function) ; GRAMMAR6A
  )

(declare-forward-reference kb-flags-of-software variable) ; kb-load1

(declare-forward-reference make-permanent-item function STACK-ACTS)







;;;; Mouse Spots


;;; `Push-more-detailed-spot' will thread a new spot onto the stack
;;; of spots for a mouse pointer.  It will do the record the item
;;; represented if the third argument is non-nil.  The frame serial
;;; number of the spot is setup per the rules outlined above.

(defun-void push-more-detailed-spot (mouse-pointer spot frame-represented?)
  (let ((stack-of-spots? (stack-of-spots mouse-pointer)))
    ;; Bind the represented item, and a first approximation to the
    ;; frame serial number.
    ;;   Since these spot slots are declared :initialize-on-recycle nil, they
    ;; may contain garbage at this point.  So, always set them here.
    ;; -fmw, 12/10/93

    ;; We saw a 2d-image-plane-state here once, which is a dependent frame, and
    ;; hance has no frame-serial-number.
    #+development
    (when (and frame-represented? (not (block-p frame-represented?)))
      (error "In push-more-detailed-spot, ~s is not a block!" frame-represented?))
    
    (setf (frame-represented? spot) frame-represented?)
    (frame-serial-number-setf (frame-serial-number-of-spot spot)
			      (when frame-represented?
				(frame-serial-number frame-represented?)))
    ;; Push onto the mouse-pointer
    (setf (mouse-pointer-of-spot spot) mouse-pointer)
    (setf (enclosing-spot? spot) stack-of-spots?)
    (setf (stack-of-spots mouse-pointer) spot)))



;;; `Push-last-spot' marks the spot given as not requiring further tracking, and
;;; invokes push-more-detailed-spot.

(defun-void push-last-spot (mouse-pointer spot frame-represented?)
  (setf (further-tracking-maybe-required? spot) nil)
  (push-more-detailed-spot mouse-pointer spot frame-represented?))







;;; `Validate-mouse-pointers' checks that every spot in every mouse pointer in
;;; the the workstation given is valid by checking it's frame serial number.
;;; Mouse pointers found to be invalid are handed off to
;;; invalidate-mouse-pointer.

(defun-void validate-mouse-pointers (workstation)
  (loop for mouse-pointers = (recent-mouse-pointers-1 workstation)
			   then (recent-mouse-pointers-2 workstation)
	for i from 1 to 2
	do
    (loop
      for mouse-pointer in mouse-pointers
      do
      (loop with deepest-invalid-spot? = nil
	    for spot? = (stack-of-spots mouse-pointer)
		      then (enclosing-spot? spot?)
	    while spot?
	    as frame-represented? = (frame-represented? spot?)
	    when (and frame-represented?
		      (frame-has-been-reprocessed-p
			frame-represented?
			(frame-serial-number-of-spot spot?)))
	      do (setf deepest-invalid-spot? spot?)
	    when (and
		   (let ((type-description-of-spot
			   (type-description-of-structure spot?)))
		     (or (eq type-description-of-spot
			     the-type-description-of-kb-workspace-image-plane-spot)
			 (eq type-description-of-spot
			     the-type-description-of-non-kb-workspace-image-plane-spot)
			 (eq type-description-of-spot
			     the-type-description-of-image-plane-spot)
			 #+development
			 (if (subtype-p-using-type-descriptions
			       (type-description-of spot?)
			       the-type-description-of-image-plane-spot)
			     (error "Assumptions of optimization broken.")
			     nil)))
		   (image-plane-has-been-reprocessed-p
		     (image-plane-of-spot spot?)
		     (reference-number-of-image-plane-of-spot spot?)))
	      do (setf deepest-invalid-spot? spot?)
	    finally
	      (when deepest-invalid-spot?
		(invalidate-mouse-pointer
		  mouse-pointer deepest-invalid-spot?))))))



;;; `Invalidate-mouse-pointer' marks the mouse-pointer as containing
;;; invalid spots.  It then pops spots off the spot stack until it
;;; finds a valid spot representing some item.  Finally it pushs
;;; an invalid-spot into the stack.

(defun-void invalidate-mouse-pointer (mouse-pointer deepest-invalid-spot)
  (setf (contains-invalid-spots mouse-pointer) t)
  ;; Pop off all the invalid spots, or those
  ;; that don't represent any item
  (loop for spot = (stack-of-spots mouse-pointer)
	do (setf (stack-of-spots mouse-pointer) (enclosing-spot? spot))
	   (setf (enclosing-spot? spot) nil)
	   (reclaim-structure spot)
	   (when (eq deepest-invalid-spot spot)
	     (return nil)))
  ;; Push in an on invalid spot.
  (push-more-detailed-spot
    mouse-pointer
    (make-invalid-spot)
    nil))


#+development
(defun show-recent-mouse-pointers (&optional
				    (workstation (car workstations-in-service)))
  (format t "~&latest: ~S" (mouse-pointer-of-latest-event  workstation))
  (format t "~&previous: ~S" (mouse-pointer-of-previous-event workstation))
  (format t "~&down?: ~S" (mouse-pointer-of-last-down workstation))
  (format t "~&interesting?: ~S" (mouse-pointer-of-last-interesting-event workstation))
  (loop for mouse-pointer in (recent-mouse-pointers-1 workstation)
	do (format t "~&~S" mouse-pointer))
  (loop for mouse-pointer in (recent-mouse-pointers-2 workstation)
	do (format t "~&~S" mouse-pointer)))




;;;; Workstation Events and Queue.


;;; A `workstation-event' is created by G2 in response to local events,
;;; telewindow events, or by the player.  They are created within a
;;; for-workstation, and they are a normalization of what ever that window's
;;; native event stream was providing. They exist only within G2.

;;; They contain a keycode, time-stamp, mouse location, window, pane, image-plane,
;;; and a frame serial number.  These are all read only, except keycode, which
;;; maybe rebound by the event stream lexical analysis.

;;; These events normally reside in a queue in the workstation where they maybe
;;; peeked at, read, and unread using the interface defined below.

(def-structure (workstation-event
		 (:reclaimer reclaim-workstation-event-1)
		 (:constructor make-workstation-event ())
		 #+development (:print-function print-workstation-event))
  workstation-event-code	   ; a key-code, aka a fixnum
  workstation-event-timestamp	   ; From the window system, 28bits of milliseconds.
  workstation-event-cursor-x	   ; gensym window coordinates
  workstation-event-cursor-y
  workstation-event-window?	   ; a gensym window;  nil => cursor not in one
  workstation-event-pane?	   ; nil => cursor not in a pane
  image-plane-for-workstation-event?
  (frame-reference-number-for-workstation-event? nil :reclaimer reclaim-frame-serial-number) ; the workspace's serial number
  ;; see shift-lexical-analysis-of-current-workstation? for note on pushed-back
  (workstation-event-was-pushed-back? nil)
  (workstation-event-detail nil))	; gensym-list of text-strings or other atoms.
					; Text strings are reclaimed when event reclaimed

;; workstation-event-detail is meant for event-specific data.
;; Currently only used by paste-events (lgibson 2/22/2000).

(defun reclaim-workstation-event (workstation-event)
  (let ((event-detail? (workstation-event-detail workstation-event)))
    (cond ((consp event-detail?)
	   (loop for element in event-detail? doing
	     (when (text-string-p element)
	       (reclaim-text-string element)))
	   (reclaim-gensym-list event-detail?))
	  ((text-string-p event-detail?)
	   (reclaim-text-string event-detail?))))
  (setf (workstation-event-detail workstation-event) nil)
  (reclaim-workstation-event-1 workstation-event))



#+development
(defun print-workstation-event (event stream depth)
  (declare (ignore depth))
  (printing-random-object (event stream)
     (format stream "~a ~a ~d,~d~@[ (pushedback)~]"
	     'workstation-event
	     (key-name (workstation-event-code event))
	     (workstation-event-cursor-x event)
	     (workstation-event-cursor-y event)
	     (workstation-event-was-pushed-back? event))
     (when (workstation-event-detail event)
       (format stream " ~s" (workstation-event-detail event)))))


;; Why can't def-structure do this for us?

(defun copy-workstation-event (event)
  (let ((new-event (make-workstation-event)))
    (setf (workstation-event-code new-event) (workstation-event-code event)
	  (workstation-event-cursor-x new-event) (workstation-event-cursor-x event)
	  (workstation-event-cursor-y new-event) (workstation-event-cursor-y event)
	  (workstation-event-timestamp new-event) (workstation-event-timestamp event)
	  (workstation-event-window? new-event) (workstation-event-window? event)
	  (workstation-event-pane? new-event) (workstation-event-pane? event)
	  (image-plane-for-workstation-event? new-event) (image-plane-for-workstation-event? event)
	  (frame-reference-number-for-workstation-event? new-event)
	    (copy-frame-serial-number (frame-reference-number-for-workstation-event? event))
	  (workstation-event-detail new-event)
	    (copy-event-plist (workstation-event-detail event)))
    new-event))






;;; Each `event' and `mouse-pointer' are given an `event-time' which is our
;;; best guess of then the user actually did the gesture that gave rise to the
;;; event.  These are encoded in a style analagous to that used for
;;; `fixnum-time' but they are consistently in units of `milliseconds' on all
;;; platforms.

;;; The origin is unknown, so all you can do is use these to measure the
;;; elapsed time between two events.  Care is taken to assure that events
;;; popped off the event Q will have equal or accending event times.

(def-concept event-time)

;; Historically the event time was useless, both because the value was bound
;; when the even was taken from the O/S (not when the user enqueued it) and
;; because differing processes had differing units and the G2 had no idea what
;; units the process as using.  This was fixed in relase 4.0.


;;; The term `timestamp' is sometimes used to refer to an `event-time'.  See
;;; event time for more details.  In milliseconds.

(def-concept timestamp)



;;; The function `event-time-difference' returns the non-negative difference of
;;; two event times, one which is known to be later than the other.

(defun event-time-difference (later-event-time earlier-event-time)
  (cond ((>=f later-event-time earlier-event-time)
	 (-f later-event-time earlier-event-time))
	(t
	 (setq later-event-time (-f later-event-time earlier-event-time))
	 (setq later-event-time (+f later-event-time event-time-mask 1))
	 (+f later-event-time 1))))



;;; `Reclaim-workstation-event-queue' is the reclaimer for the
;;; workstation-event-queue slot in workstation structures.

(defun reclaim-workstation-event-queue (workstation-event-queue)
  (loop for workstation-event being each queue-element of workstation-event-queue
	do (reclaim-workstation-event workstation-event))
  (reclaim-queue workstation-event-queue))



;;; `Enqueue-workstation-event' creates and fills out a new workstation-event
;;; and inserts at the tail of the workstation event queue. Event-detail? is
;;; either NIL or a gensym-list of symbols, fixnums, and strings, and is owned
;;; by this function.

;;  I believe event-detail? is always in the form of a plist these days.

(defun enqueue-workstation-event
    (workstation key-code cursor-x cursor-y timestamp window? pane? image-plane?
		 &optional event-detail?)
  (let ((workstation-event (make-workstation-event)))

    (setf (workstation-event-code workstation-event) key-code
	  (workstation-event-cursor-x workstation-event) cursor-x
	  (workstation-event-cursor-y workstation-event) cursor-y
	  (workstation-event-timestamp workstation-event) timestamp
	  (workstation-event-window? workstation-event) window?
	  (workstation-event-pane? workstation-event) pane?
	  (image-plane-for-workstation-event? workstation-event) image-plane?
	  (workstation-event-detail workstation-event) event-detail?)
    
    ;; Borrow the frame serial number of the workspace.
    (frame-serial-number-setf (frame-reference-number-for-workstation-event? workstation-event)
	  (when image-plane?
	    (let ((workspace? (workspace-on-image-plane? image-plane?)))
	      (when workspace?
		(frame-serial-number workspace?)))))

    (with-drawing-trace (event-q)
      (format t "Enqueue ~s in ~s" workstation-event (workstation-event-queue workstation)))
    
    (let ((queue (workstation-event-queue workstation)))
      (when (queue-empty-p queue)
	(maybe-schedule-service-workstation workstation t))
      (queue-insert queue workstation-event))
    workstation-event))



;;; `Servicing-workstation-event' is a dynamic extent established when we are
;;; doing the actual processing of a workstation event.  It is legal to unwind
;;; out of this extent, in particular the abort UI command throws out of this
;;; context.

(def-named-dynamic-extent servicing-workstation-event
  (module workstation)
  (unwind? t))


;;; `Current-workstation-event' is bound to the current workstation-event.
;;; when servicing-workstation-event.

(defvar-of-named-dynamic-extent current-workstation-event
    servicing-workstation-event)



;;; `Dequeue-workstation-event' pops the next event off the workstation
;;; event queue.

#+unused
(defun dequeue-workstation-event (workstation)
  (queue-pop (workstation-event-queue workstation)))


;;; The function `requeue-workstation-event' pushes a COPY of the given
;;; workstation event onto the HEAD of the queue; that is, it will be
;;; the next event read.

(defun requeue-workstation-event (workstation workstation-event)
  (let ((pushed-back-workstation-event
	  (copy-workstation-event workstation-event))
	(queue (workstation-event-queue workstation)))
    (setf (workstation-event-was-pushed-back? pushed-back-workstation-event) t)
    (when (queue-empty-p queue)
      (maybe-schedule-service-workstation workstation t))
    (queue-push queue pushed-back-workstation-event)))





;;; The function `flush-pending-mouse-motion-events' discards ALL pending
;;; mouse-motion events in the workstation event queue

(defun flush-pending-mouse-motion-events (workstation)
  (let ((queue (workstation-event-queue workstation)))
    (loop for event = (queue-peek queue)
	  while (and event
		     (mouse-motion-event-p
		       (workstation-event-code event)))
	  do (with-drawing-trace (event-q)
	       (format t "Discard ~s in ~s" event queue))
	  do (reclaim-workstation-event (queue-pop queue)))))

;; Note A: There are a lot of Qs here.  The O/S Queue, any Q's the xwindows.c or
;; equivalent might have, the ICP message Q, the G2 window's Q, etc.  It is very
;; hard to be sure we flush all these.  So there are also code guards in
;; shift-lexical-analysis-of-current-workstation?  and this is one reason
;; that routine can return nil.





;;;; Starting and Stopping Mouse Tracking



;;; `Start-tracking-mouse-in-current-workstation' is called in a
;;; for-workstation extent and it enables the generation of mouse motion
;;; events.

(defun-allowing-unwind start-tracking-mouse-in-current-workstation-context ()
  (setf (track-mouse-in-this-workstation-context?
	  current-workstation-context)
	t)
  (unless (tracking-mouse? current-workstation)
    (setf (tracking-mouse? current-workstation) t)
    (cond
      ((current-window-supports-v4-mouse-messages current-workstation-window)
       (case type-of-current-workstation-window
	 (icp
	  (with-icp-window (current-workstation-window)
	    (start-mouse-tracking-in-window current-workstation-window)))
	 (t
	  (start-mouse-tracking-in-window current-workstation-window)
	  (start-or-restart-native-window-heartbeat))))

      (t
       ;; The new ICP message function called above makes the following
       ;; obsolete.  The following is what is/was being done by 3.0 and 4.0
       ;; Beta Rev. 0 versions of G2.  (MHD 10/18/94)
       (case type-of-current-workstation-window
	 ((native x11-window)
	  (start-mouse-tracking current-workstation-native-window?))

	 (icp
	  (with-icp-window (current-workstation-window)
	    (send-icp-telewindows-start-mouse-tracking))))))))



;; The responsiblity for pushing back a mouse-motion event has been moved
;; to synchronize-selection-style, via push-back-mouse-motion-event, below.

;; Slamming the current mouse position seems ill concieved.  In the
;; native/x11-window case it results in the generated mouse motion event having
;; a delta of zero, which would trigger it's being ignored in most cases.  In
;; the icp case the random choice of 100/100 creates a bogus delta for the first
;; mouse motion.  Don't all platforms communicate the approprate mouse position
;; with every event, so isn't the last event's mouse position the right thing to
;; use? - ben 9/2/93



;;; `Stop-tracking-mouse-in-current-workstation' disables the generation of
;;; mouse motion events for current workstation and discards any mouse motion
;;; events hanging out in the workstation event queue.  This must be
;;; invoked inside a for-workstation extent, and that extent is updated
;;; appropriatly.

(defun-allowing-unwind stop-tracking-mouse-in-current-workstation-context ()
  (setf (track-mouse-in-this-workstation-context?
	  current-workstation-context)
	nil)
  (when (tracking-mouse? current-workstation)
    (setf (tracking-mouse? current-workstation) nil)
    (cond
      ((current-window-supports-v4-mouse-messages current-workstation-window)
       (case type-of-current-workstation-window
	 (icp
	  (with-icp-window (current-workstation-window)
	    (stop-mouse-tracking-in-window current-workstation-window)))
	 (t
	  (stop-mouse-tracking-in-window current-workstation-window)
	  (start-or-restart-native-window-heartbeat))))

      (t
       ;; The new ICP message function called above makes the following
       ;; obsolete.  The following is what is/was being done by 3.0 and 4.0
       ;; Beta Rev. 0 versions of G2.  (MHD 10/18/94)
       (case type-of-current-workstation-window
	 (x11-window
	  (stop-mouse-tracking-in-local-window current-workstation-window))

	 (icp
	  (with-icp-window (current-workstation-window)
	    (send-icp-telewindows-stop-mouse-tracking)))))))
  (flush-pending-mouse-motion-events current-workstation))



;;; The function `push-back-mouse-motion-event' pushes a mouse-motion
;;; event onto the event queue for the current workstation.  The x,y
;;; coordinates are taken from the most recent workstation x and y.

(defun push-back-mouse-motion-event ()
  (let* ((x (x-in-window-of-mouse? current-workstation))
	 (y (y-in-window-of-mouse? current-workstation))
	 (modifier-bits
	   (current-modifier-bits-for-workstation
	     current-workstation))
	 (timestamp (fixnum-time-of-mouse-pointer
		      (mouse-pointer-of-latest-event
			current-workstation))))
    (multiple-value-bind (pane? image-plane?)
	(decode-window-position current-workstation-window x y)

      (enqueue-workstation-event
	current-workstation
	(mouse-motion-key-code modifier-bits)
	x y
	timestamp					    ; (get-fixnum-time) Wrong!
	current-workstation-window
	pane?
	image-plane?))))


;; x,y, and timestamp will all be zero if this workstation has not yet seen a real
;; event.  Fortunately, push-back-mouse-motion-event is only called below event
;; handlers, so we can be sure that at least one event has occured.



;;;; Lexical Analysis of the Event Stream


;;; `advanced-button-state' takes in a key-code and a button-state.  It
;;; returns both normalizing the key-code, and updating the button-state.  All
;;; mouse up keycodes and all mouse down keycodes are converted to mouse up or
;;; down.  The bits in the button state are updated to indicate which mouse
;;; buttons are depressed.

;;; This is the heart of simulating a one button mouse.

(defun advanced-button-state (key-code before-mouse-button-state key-bits)
  (let ((after-mouse-button-state before-mouse-button-state))
    (macrolet ((adjust (op mask new-keycode)
		 `(progn
		    (setf after-mouse-button-state
			  (,op ,mask after-mouse-button-state))
		    (setf key-code (logiorf key-bits
					    (key-code ',new-keycode))))))
      (key-case (key-index key-code)
	(mouse-right-down   (adjust logiorf #b001 mouse-right-down))
	(mouse-middle-down  (adjust logiorf #b010 mouse-middle-down))
	(mouse-left-down    (adjust logiorf #b100 mouse-left-down))
	(mouse-down         (adjust logiorf #b100 mouse-down)) ; Treat like left-down.
	(mouse-right-up     (adjust logandf #b110 mouse-up))
	(mouse-middle-up    (adjust logandf #b101 mouse-up))
	(mouse-left-up      (adjust logandf #b011 mouse-up))
	(mouse-up           (adjust logandf #b011 mouse-up))) ; Treat like left-up
      )
    (values key-code after-mouse-button-state)))


;;; The function `mouse-down-p' returns T if any mouse buttons are
;;; currently down for the current workstation.  This is useful
;;; for setting up workstation contexts that should exit on the
;;; next mouse up/down transition.

(defun mouse-down-p ()
  (/=f 0 (mouse-button-model current-workstation)))



;;; The function `mouse-still-down-p' returns T the mouse-down-p is true and a
;;; look ahead in the local event Q indicates that it has not been released.
;;; This is useful for supressing autorepeat behavior as soon as possible.  Note
;;; that sadly this does not synchronize the local event queue with the OS event
;;; Q.

(defun mouse-still-down-p ()
  (and (mouse-down-p)
       (loop finally (return t)
	     with lookahead-mouse-button-state
	       = (mouse-button-model current-workstation)
	     for workstation-event being each queue-element
	     of (workstation-event-queue current-workstation)
	     as raw-key-code = (workstation-event-code workstation-event)
	     as canonical-key-code = (canonicalize-key-code raw-key-code)
	     as key-bits = (key-modifier-bits canonical-key-code)
	     when (/=f 0 lookahead-mouse-button-state) return nil
	     do
	   (multiple-value-bind
	       (normalized-key-code advanced-mouse-button-state)
	       (advanced-button-state canonical-key-code
				      lookahead-mouse-button-state
				      key-bits)
	     (declare (ignore normalized-key-code))
	     (setf lookahead-mouse-button-state
		   advanced-mouse-button-state)))))


(defun selection-style-mouse-tracking-p (selection-style)
  (cond ((show-selection-handles-p)	; Mouse tracking always on if using selection handles.
	 (neq selection-style 'unknown-is-selection-style))
	(t
	 (memq selection-style
	       '(top-level-with-mouse-tracking-is-selection-style
		 top-level-with-selection-focus-is-selection-style)))))

(defun selection-style-with-focus-p (selection-style)
  (memq selection-style
	'(top-level-with-selection-focus-is-selection-style
	  top-level-with-selection-focus-but-no-mouse-tracking-is-selection-style)))



;;; `remember-last-active-mouse-button' is used to keep track of the button that
;;; initiated mouse-activity on a window. It must be called with current-workstation
;;; bound.

(defun remember-last-active-mouse-button (key-code old-mouse-state &optional new-mouse-state)
  (declare (ignore new-mouse-state))
  (when (and (=f old-mouse-state 0) (key-code-is-mouse-down-p key-code))
    (setf (mouse-button-of-last-activity current-workstation)
	  (mouse-key-code-button-name-symbol (key-index key-code))))
  nil)


;;; `Synchronize-selection-style' bridges from the workstation context stack
;;; maintainance into the event handling lexical analysis.  It is invoked when
;;; entries are pushed or popped from the stack of workstation-contexts.  It
;;; brings the workstation (either ICP or XWindow) in synch.

(defun-void synchronize-selection-style
    (old-selection-style new-selection-style)

  ;;; Bring the workstation's selection-focus into synch.
  (setf (image-plane-with-selection-focus-of-workstation?
	  current-workstation) nil)
  (setf (block-with-selection-focus-of-workstation current-workstation)
	nil)
  (when (selection-style-with-focus-p new-selection-style)
    (setf (image-plane-with-selection-focus-of-workstation?
	    current-workstation)
	  (image-plane-with-selection-focus-of-workstation-context
	    specific-structure-for-current-workstation-context))
    (setf (block-with-selection-focus-of-workstation current-workstation)
	  (block-with-selection-focus-of-workstation-context
	    specific-structure-for-current-workstation-context)))

  ;; Bring mouse tracking into synch.
  (unless (dummy-workstation-p current-workstation)
    (let ((old-mouse-tracking-p
	    (selection-style-mouse-tracking-p old-selection-style))
	  (new-mouse-tracking-p
	    (selection-style-mouse-tracking-p new-selection-style)))
      old-mouse-tracking-p

      ;; Always push back a motion event, even if mouse tracking is already on.
      ;; Why?  Starting mouse tracking pushes one back on the TW side.
      ;; Not any more -fmw, 5/18/06
      (when (and new-mouse-tracking-p
		 (boundp 'current-workstation-window))
	(push-back-mouse-motion-event))
      
      (if new-mouse-tracking-p
	  (start-tracking-mouse-in-current-workstation-context)
	  (stop-tracking-mouse-in-current-workstation-context)))))



;;; The function `canonicalize-key-code' handles all of the key-code
;;; transformations on the G2 side.  TeleWindows does some of its own in order
;;; to converse with G2 3.0. See backtranslate-key-code.  For a new Unicode
;;; key-code with Unicode bit on, this does nothing but return key-code.

(defun canonicalize-key-code (key-code)
  (cond
    ((unicode-space-p key-code)		; Windows G2/TW sends Unicode spaces instead of SPACE.
     (key-code-for-space))
    ((unicode-bit-on-p key-code)	; Added. (MHD 8/24/99)
     key-code)
    (t
     ;; Cleanup ASCII control keys: their control-bit should be OFF.
     (when (special-control-key-p key-code)
       (setq key-code (logandf key-code (lognotf control-bit))))

     ;; Merge META or ALT into just ALT.
     (when (or (meta-bit-on-p key-code)
	       (alternate-bit-on-p key-code))
       (setq key-code (logiorf alternate-bit
			       (logandf key-code (lognotf meta-bit)
					(lognotf alternate-bit)))))

     ;; Moved to the TW side, since TW 4.0 now needs to talk to G2 3.0.  Foo.
     ;; Actually, this needs to live on both sides, although in the new spirit of
     ;; user empowerment, we should make the equation of keypad keys to numbers
     ;; controllable by the KB.
     (setq key-code (clobber-keypad-characters key-code))
     
     key-code)))





;;; `Shift-lexical-analysis-of-current-workstation?' updates the workstation's
;;; model of the event stream and returns the event at the head of the event
;;; queue or NIL.  This presumes the binding for current-workstation is
;;; current.  It assumes there is one or more events pending in the queue.
;;; Current-workstation-has-pending-events-p is one way to test that.

;;; Since the modifier keys information includes knowledge of the control
;;; keys we convert control keys to simpler keycodes.

;;; We merge any adjacent mouse motion events.  We eliminate mouse-motions
;;; entirely if tracking-mouse? is disabled.

;;; We simulate a one button mouse.  Only the first button down or last button
;;; up of the N buttons is passed on.  Flags are kept in the
;;; `mouse-button-model' of the workstation to indicate which buttons are
;;; currently down.  Button transitions, other than the first or last are
;;; discarded, unless there are no following events in which case an idle event
;;; is generated.  This can cause you to get two mouse-motion events in a row
;;; without any polling of the local server.

;;; This routine can return NIL even when events are pending because of the
;;; normalizing of mouse motion and the one button mouse simulator, even if the
;;; work

;;; A mouse pointer is generated and placed into `mouse-pointer-of-latest-event.'
;;; The previous value is moved over into `mouse-pointer-of-previous-event.'
;;; Whenever the first mouse button goes down `mouse-pointer-of-last-down' is
;;; rebound. Whenever an "interesting" event happens (not mouse motion or hover),
;;; `mouse-pointer-of-last-interesting-event' is rebound.

;;; The mouse pointer always tracked, at least, into the image-plane.  If the
;;; workstation is `tracking-mouse?' or the event is a mouse event then the
;;; tracking is iterated until done.

;;; This routine is the primary caller of the mouse tracking mechanisms, and
;;; hence establishes the dynamic extent for that.  Currently that consists of
;;; a binding for current-workstation, and the bindings established by
;;; with-raw-window-transform-and-draw-area.

(defun shift-lexical-analysis-of-current-workstation? ()
  (with-raw-window-transform-and-draw-area
      ((window-for-workstation current-workstation))
    (loop with queue = (workstation-event-queue current-workstation)
	  as workstation-event   ;; Reclaiming locally (3 places), or returned
	     = (queue-pop queue)
	  as following-event? = (queue-peek queue)
	  as key-code = (workstation-event-code workstation-event)
	  as key-bits = (key-modifier-bits key-code)
	  as before-mouse-button-state = (mouse-button-model current-workstation)
	  as after-mouse-button-state = before-mouse-button-state
	  do 
      (block :try-again

	;; Canonicalize the key code.
	(setq key-code (canonicalize-key-code key-code)
	      key-bits (key-modifier-bits key-code))
	(setf (workstation-event-code workstation-event) key-code)

	;; Discard multiple mouse motions.
	;; Discard info about the multiple mouse buttons info.
	(cond
	  ;; Mouse motion cleanup
	  ((mouse-motion-event-p key-code)
	   (cond
	     ;; Merge duplicates. (smoothing)
	     ((and following-event?
		   (mouse-motion-event-p 
		     (workstation-event-code following-event?)))
	      (return-from :try-again nil))
	     ;; Return NIL if the workstation is not tracking-mouse?
	     ;; See Note A on flush-pending-mouse-motion-events .
	     ((not (tracking-mouse? current-workstation)) 
	      (reclaim-workstation-event workstation-event)
	      (return nil))))
	  
	  ;; Convert left/middle/right-up/down to simply mouse-up/down,
	  ;; while preserving the modifier bits.
	  ((mouse-key-code-p key-code)
	   (multiple-value-bind (normalized-key-code new-mouse-button-state)
	       (advanced-button-state
		 key-code before-mouse-button-state key-bits)
	     (remember-last-active-mouse-button key-code before-mouse-button-state new-mouse-button-state)
	     (setf key-code normalized-key-code)
	     (setf after-mouse-button-state new-mouse-button-state)
	     (setf (workstation-event-code workstation-event)
		   key-code))))

	(let ((mouse-pointer
		(make-next-event-mouse-pointer
		  current-workstation
		  key-code ;; may still be rebound.
		  (workstation-event-timestamp workstation-event)
		  (workstation-event-cursor-x  workstation-event)
		  (workstation-event-cursor-y  workstation-event))))
	  
	  ;; Maintain mouse-pointer-of-latest-event and recent-mouse-pointers-*
	  (initialize-mouse-pointer-tracking-for-window
	    current-workstation
	    mouse-pointer
	    (workstation-event-pane? workstation-event)
	    (image-plane-for-workstation-event? workstation-event))

	  ;; Save "interesting" events for g2-last-input-event
	  (when (interesting-input-event-p key-code)
	    (release-mouse-pointer-if-any
	      (mouse-pointer-of-last-interesting-event current-workstation))
	    (setf (mouse-pointer-of-last-interesting-event current-workstation)
		  (reference-mouse-pointer mouse-pointer)))

	  ;; Did the status of the mouse buttons change? (Note A)
	  (unless (or (=f before-mouse-button-state after-mouse-button-state)
		      (workstation-event-was-pushed-back? workstation-event))
	    (setf (mouse-button-model current-workstation) after-mouse-button-state)
	    (cond
	      ;; First button of N going down, i.e. mouse down
	      ((=f 0 before-mouse-button-state)
	       (release-mouse-pointer-if-any
		 (mouse-pointer-of-last-down current-workstation))
	       (setf (mouse-pointer-of-last-down current-workstation)
		     (reference-mouse-pointer mouse-pointer)))
	      ;; Last button of N going up, i.e. mouse up.
	      ((=f 0 after-mouse-button-state)
	       ;; Nothing to do!
	       ;; (A generic mouse-up event is already in the queue, thanks to
	       ;; advanced-button-state)
	       )
	      ;; Otherwise, pretend this wasn't a button transition.
	      (T
	       (cond
		 ;; If tracking, convert this to mouse motion

		 ;; Intervening mouse button up/down events, other than the very
		 ;; first down and the very last up, get converted into
		 ;; mouse-motion's, if we are tracking, else are thrown away
		 ;; (unless we need it because we have no other event to
		 ;; return).

		 ((tracking-mouse? current-workstation)
		  (setf key-code (logiorf key-bits (key-code 'mouse-motion)))
		  (setf (workstation-event-code workstation-event) key-code)
		  (setf (key-code-of-mouse-pointer mouse-pointer) key-code))

		 ;; If other events in Q then discard this one.
		 (following-event?
		  (return-from :try-again nil))
		 ;; otherwise return nil.
		 (t
		  (reclaim-workstation-event workstation-event)
		  (return nil))))))

	  ;; Track till done, if "tracking", mouse event, or rebindable keystroke.
	  (when (or (tracking-mouse? current-workstation)
		    (mouse-key-code-p key-code)
		    ;; There could be a user-op bound to this key (bhyde 09-Dec-94)
		    ;; This now includes essentially all keys. -fmw, 2/18/05
		    (rebindable-key-code-p key-code))
	    (track-mouse-pointer-till-done mouse-pointer)))
	
	;; All done, I'm outta here.
	(return workstation-event))

      ;; We are trying again, throw this event away
      (reclaim-workstation-event workstation-event))))

;; Note A: Events which are pushed back are not allowed to update the
;; mouse model.  That model tries to reflect the hardware.  The normalizing
;; of, for example, mouse-middle-down to mouse-down coupled with pushing
;; back could create confusion.  The artificial mouse-events mouse-select
;; and mouse-drag are also prevented from updating the model, but by luck
;; the don't actually try.  - ben, 3/20/95

;; Note B: The stop mouse tracking routine makes some effort to discard
;; pending mouse motions, but since there are a lot of Q's it is hard.
;; This provides an absolute assurance that if the current workstation
;; context isn't interested in mouse motion it won't see any.


;;; The function `interesting-input-event-p' determines whether an event is
;;; interesting enough to the KB developer to save for g2-last-input-event.

(defun interesting-input-event-p (key-code)
  (key-case (key-index key-code)
    ((mouse-hover mouse-motion)
     nil)
    (paste-availability-request
      nil)
    (t
      t)))


;;; `Make-next-event-mouse-pointer' takes a gensym-window and a mouse-{x,y}.
;;; it returns a fresh mouse-pointer whose stack of spots contains only
;;; an entire-g2-window-spot.

;;; Record this mouse-pointer into the list of recent mouse pointers.

;;; Every N events triggers the reclaiming of a batch of N recent mouse
;;; pointers.  Care is taken to avoid reclaiming the current-mouse-down pointer.

(defun make-next-event-mouse-pointer
    (workstation key-code fixnum-time mouse-x mouse-y) ;; Note A

  ;; Make an initialize a new mouse pointer.
  (let ((latest-event-mouse-pointer
	 (make-mouse-pointer workstation key-code fixnum-time
			     mouse-x mouse-y)))

    ;; Compute compute coordinates relative to the selection-focus.
    (let (focus-image-plane)
      (when (setf focus-image-plane
		  (image-plane-with-selection-focus-of-workstation?
		    current-workstation))
	;; Currently ignoring the block, darn it.
	(with-image-plane-transform (focus-image-plane)
	  (setf (x-in-workspace-of-selection-focus? latest-event-mouse-pointer)
		(x-in-workspace mouse-x))
	  (setf (y-in-workspace-of-selection-focus? latest-event-mouse-pointer)
		(y-in-workspace mouse-y))
	  (setf (block-of-selection-focus? latest-event-mouse-pointer)
		(block-with-selection-focus-of-workstation current-workstation)))))

    ;; Record for memory management
    (gensym-push latest-event-mouse-pointer
		 (recent-mouse-pointers-1 workstation))

    ;; Shift in this new mouse pointer.
    (release-mouse-pointer-if-any
      (mouse-pointer-of-previous-event workstation))
    (setf (mouse-pointer-of-previous-event workstation)
	  (mouse-pointer-of-latest-event workstation))
    (setf (mouse-pointer-of-latest-event workstation)
	  latest-event-mouse-pointer)

    ;; Setup the spot stack.
    (push-more-detailed-spot
      latest-event-mouse-pointer
      (make-entire-g2-window-spot)
      (g2-window-for-this-workstation? workstation))

    ;; Reclaim some recent mouse pointers if approprate.
    (maybe-reclaim-some-mouse-pointers workstation)

    ;; Return the new mouse pointer
    latest-event-mouse-pointer))

(defun maybe-reclaim-some-mouse-pointers (workstation)
  (when (<f (decff (recent-mouse-pointer-countdown workstation)) 0)
    ;; Reset the counter, reclaim the mouse pointers in
    ;; recent-mouse-pointers-2 and shift those in recent-mouse-pointers-1 into
    ;; recent-mouse-pointers-2.  Take care not to reclaim the
    ;; mouse-down-pointer?
    (setf (recent-mouse-pointer-countdown workstation) 2)
    (let ((mouse-pointers-to-consider-reclaiming
	   (recent-mouse-pointers-2 workstation)))
      (setf (recent-mouse-pointers-2 workstation)
	    (recent-mouse-pointers-1 workstation))
      (setf (recent-mouse-pointers-1 workstation) nil)
      (loop for mouse-pointer in mouse-pointers-to-consider-reclaiming
	    do
	(cond
	  ((<=f (reference-count-of-mouse-pointer mouse-pointer) 0)
	   (reclaim-mouse-pointer mouse-pointer))
	  (T
	   (gensym-push mouse-pointer
			(recent-mouse-pointers-1 workstation)))))
      (reclaim-gensym-list mouse-pointers-to-consider-reclaiming))))

;; Note A: caller may rebind further normalize this key code.



;;; The function `x-in-workspace-coordinates' takes the image plane argument
;;; explicitly.  I don't know why x-in-workspace doesn't.

(defun x-in-workspace-coordinates (x-in-window image-plane)
  (with-image-plane-transform (image-plane)
    (x-in-workspace x-in-window)))

(defun y-in-workspace-coordinates (y-in-window image-plane)
  (with-image-plane-transform (image-plane)
    (y-in-workspace y-in-window)))



;;; The function `image-plane-of-workspace-on-workstation' returns the
;;; image-plane displaying the given workspace on the given workstation, if any,
;;; not including image-planes on printing windows.

(defun image-plane-of-workspace-on-workstation (workstation workspace)
  (loop for image-plane in (image-planes-this-is-on workspace)
	as window = (gensym-window-for-image-plane image-plane)
	when (and (not (printing-window-p window))
		  (eq workstation (workstation-this-is-on window)))
	  return image-plane))

(defun image-plane-of-workspace (workspace)
  (image-plane-of-workspace-on-workstation current-workstation workspace))


;;; The function `image-plane-of-workspace-on-window' returns the image-plane
;;; showing the workspace on the given gensym window, if any.

(defun image-plane-of-workspace-on-window (gensym-window workspace)
  (loop for pane in (panes-in-window gensym-window)
	thereis
	(loop for image-plane in (stack-of-image-planes pane)
	      when (eq (workspace-on-image-plane? image-plane)
		       workspace)
		return image-plane)))

(defun current-modifier-bits-for-workstation (workstation)
  (let ((mouse-pointer
	  (mouse-pointer-of-latest-event workstation)))
    (key-modifier-bits
      (key-code-of-mouse-pointer mouse-pointer))))

;; The most recent ones we can get.

;;; Moved here from DIALOGS, it is not used any more. --binghe, Sep 2, 2016.
(defun get-image-plane-by-frame (workstation frame)
  (loop for wc in (workstation-context-stack workstation)
	as edit-state? = (specific-structure-for-workstation-context wc)
	as frame? = (frame-being-edited? edit-state?) do
    (when (eq frame? frame)
      (let* ((edit-workspace (edit-workspace edit-state?))
	     (image-plane (image-plane-of-workspace edit-workspace)))
	(return-from get-image-plane-by-frame image-plane))))
  nil)



;;;; Workstation




;;; Workstations provide the abstraction thru which events are dispatched and
;;; drawing is rendered.  A G2 will have multiple workstations, one main one,
;;; and one for each Telewindow's connection, and finally a occational
;;; annonymous one.  Workstations maybe logged in or not.  Once logged in they
;;; have a user, and user-mode that is used to configure the user interface's
;;; behavor.  

;;; When the focus of G2 is on a given workstation a for-workstation extent is
;;; established.  Many subsystems work only within this context, for example the
;;; parser.  Occationally such extents are established just to enable the use of
;;; such subsystems.  In that case the user-mode not be the same as that of the
;;; workstation.

;;; Workstations persist over KB clear, but they have an associated frame to 
;;; KB, a G2-WINDOW, that provides the User's with some access to the them.

;;; The drawing is mediated by a hierarhcy of structures
;;;    gensym-workstation > gensym-window > pane(s) > image-planes
;;; panes orgainize the window into a set of tiles, image-planes are stacked
;;; in the pane, workspaces are viewed using an image-planes.

;;; Events are processed along a pipe line of stages.  `Poll-workstation'
;;; is regularly invoked to fill the workstation's `workstation-event-queue'
;;; with `workstation-event's.  Service-workstation is polled regularly to
;;; handle those events.

;;; Events dispatching is mediated by the workstations
;;; `workstation-context-stack'.  The `workstation-context's the top and
;;; bottom context found in that stack are searched when interpreting
;;; and event to find a handler for the event.

;;; Workstation-contexts provide the state to implement input/command
;;; micro tasks.  These command micro tasks implement modalities in for
;;; the user without starving other microtasks in G2.  Examples include
;;; include: top-level, editing, marking, dragging, and g2-login.
;;; Cycles are given to these micro-tasks only in the recursive extent
;;; of service-workstation and then only in response to events.

;;; The workstation also may have a single micro task used to avoid
;;; letting extensive inspect commands locking up G2.

;;; In addition to these input/command "micro tasks" output/drawing
;;; micro tasks exist.  Portions of it can be aborted by look ahead in the
;;; workstation event Q noticing pending events that will cause the
;;; current redraw to be redundent.







;;;; Event Interpretations


;;; An `event-interpretation' ia a trivial little abstraction to hack the
;;; internal event handler names vs. external user-menu-choices namespace
;;; problem.  We need to be able to allow the user to define a user-menu-choice
;;; named, eg, post-object-menu, and be able to distinguish that from the
;;; internal event handler of the same name.  We do that by appending the
;;; namespace to the name, via one of these here event-interpretations.

;;; They also allow for home-made closures of handlers and arguments.

;;; The namespace is either USER or INTERNAL.  In the simplest case, an
;;; internal event with no arguments, the interpretation is just the name
;;; symbol.

(defun make-event-interpretation (namespace name arguments)
  #+development (assert (memq namespace '(user internal)))
  (cond ((or arguments
	     (and namespace (neq namespace 'internal)))
	 (slot-value-list namespace name (copy-tree-using-slot-value-conses arguments)))
	(t
	 name)))

(def-substitution-macro event-interpretation-namespace (event-interpretation)
  (cond ((consp event-interpretation)
	 (first event-interpretation))
	(t
	 'internal)))

(def-substitution-macro event-interpretation-name (event-interpretation)
  (cond ((consp event-interpretation)
	 (second event-interpretation))
	(t
	 event-interpretation)))

(def-substitution-macro event-interpretation-arguments (event-interpretation)
  (cond ((consp event-interpretation)
	 (third event-interpretation))
	(t
	 nil)))

(defun reclaim-event-interpretation (event-interpretation)
  (when (consp event-interpretation)
    (reclaim-slot-value-tree event-interpretation)))



;;;; Workstation Context Validation


(def-concept valid-workstation-context)

;;; `Validate-workstation-context-p' is a structure method define on all
;;; subtypes of workstation-context-frame.  The harness uses this method to
;;; assure that no code in that implements the workstation context needs to
;;; worry about having the rug pulled out from under it.  See the notes below
;;; for a few exceptions to this.

;;; It returns a boolean indicating if the context is still valid.  You must AND
;;; your result together with the one from the superior method, call the
;;; superior method first.

;;; Invalid ones are aborted by the main event handling loop.  This helps to
;;; assure that all the other methods (except cleanup and continuation) and all
;;; the event handlers may know that the context is valid when they are called.

;;; Actions taken within the context's own code which might invalidate the
;;; context are it's own problem.  For example if new frames are added to it's
;;; state it will need to update the snapshots of frame references numbers this
;;; mechinism relies upon.

;;; The backbone provides some default mechinism.  One is provided to validate
;;; mouse pointers, and one to validate blocks.

;;; For mouse-pointers: As the context runs it may accumulate mouse pointer
;;; which must remain valid using
;;; `add-mouse-pointer-to-guardians-of-workstation-context' It is often useful
;;; to add the mouse pointer of the event that spawned the workstation context.

;;; For blocks the predicate `valid-block-in-workstation-context-p' will check
;;; against a snapshot of the frame reference number current when the context
;;; was made.  Note that contexts which are refined from
;;; `workstation-context-with-selection-focus' have a get a refined
;;; valid-workstation-context-p that checks the block they are focused on.

;;; Workstation contexts that create blocks after entry (for example the editor
;;; workspace) or allow blocks to come and go during thier operation (for
;;; example dragging), will need to refine this method.  Some contexts that have
;;; do not use (but probably could) workstation-context-with-selection-focus
;;; must refine it to monitor the block they are "focused on."

;;; We lack a good technique for checking if cached image-planes are still
;;; valid!  The crummy aproximation we currently use is `valid-image-plane-p'.

;;; The class system can change while a workstation context is running.  In
;;; particular user attributes can disappear. `Slot-exists-in-frame-p' is useful
;;; for validating attribute denotations.

;;; The cleanup method is called when a context becomes invalid and when it is
;;; still valid, but just returning.  Because of this the cleanup method must be
;;; very carefully crafted.

;;; Similarly, it is easy to neglect making the abort continuations sufficently
;;; paranoid.

;;; When coding an event handler you must be careful not to pull the rug out
;;; from under your own feet.  The most striking example of which is clearing
;;; the KB, which among other things resets the frame reference numbers and
;;; unwinds the context stack.

(def-generic-structure-method valid-workstation-context-p (workstation-context-frame))




;;; `Valid-workstation-context-p' is a method an after method with AND
;;; combination defined on all workstation contexts.  It's primary method
;;; asserts that all mouse pointer in the workstation context-frame are
;;; currently valid.

(def-structure-method valid-workstation-context-p (workstation-context-frame)
  (loop for mouse-pointer
	    in (mouse-pointers-of-workstation-context workstation-context-frame)
	never (contains-invalid-spots mouse-pointer)))


(def-structure-method valid-workstation-context-p
    (workstation-context-with-selection-focus)
  (and
    (funcall-superior-method workstation-context-with-selection-focus)
    (image-plane-has-not-been-reprocessed-p
      (image-plane-with-selection-focus-of-workstation-context
	workstation-context-with-selection-focus)
      (reference-number-of-image-plane
	workstation-context-with-selection-focus))
    (or (null (block-with-selection-focus-of-workstation-context
		workstation-context-with-selection-focus))
	(valid-block-in-workstation-context-p
	  (block-with-selection-focus-of-workstation-context
	    workstation-context-with-selection-focus)
	  workstation-context-with-selection-focus))))





;;;; Workstation Event Interpretation



;;; `Interpret-workstation-event' attempts to compute an indication of how this
;;; event will be handled, along with workstation context which handle it.  It
;;; returns two values.  The first is a event type or nil.  The second is a flag
;;; indicating if the event is handled by the latest workstation context,
;;; otherwise it will be handled by the top-level context.

;;; This returns an event-interpretation, which must be reclaimed.

;;; This establishes a servicing-workstation-event extent, and it must be
;;; invoked within an approprate for-workstation context.

;;; The returned workstation event type is a symbol is usually (always?)
;;; defined by def-workstation-event-type.

;;; This function maybe called multiple times on the same event.

;;; This is implemented as if by invoking the interpret-event method of the
;;; current and top-level workstation contexts.

(defun interpret-workstation-event (workstation-event workstation)
  (multiple-value-bind (event-interpretation? context-name?)
      (find-event-interpretation workstation-event workstation)
    (values event-interpretation?
	    (neq context-name? 'top-level))))

;; This function is deprecated.



;;; `Remove-image-plane-pointers-in-workstation-event-queue' goes through the
;;; queue of workstation events for workstation and sets the
;;; image-plane-for-workstation-event? slot to nil for all events for which
;;; that slot's value is eq to image-plane.  This function is designed to be
;;; used whenever an image plane is deleted, i.e.  by delete-image.

(defun remove-image-plane-pointers-in-workstation-event-queue
       (workstation image-plane)
  (loop for workstation-event being each queue-element of (workstation-event-queue workstation)
	as image-plane? = (image-plane-for-workstation-event? workstation-event)
	;; Fix up workstation event queues point to no longer contain valid image
	;;   planes. (This is a rather rare occurence.)
	when (eq image-plane? image-plane)
	  do (setf (image-plane-for-workstation-event? workstation-event) nil)
	     ;; Now search again for an image plane in that position.  (This
	     ;;   was added to fix the "burn-through" problem -- if you got
	     ;;   two clicked enqueued on a menu, the first would dismiss it, and
	     ;;   the second would bring up the system menu because the image plane
	     ;;   had been reset here to nil; thus, it appeared as though the second
	     ;;   click had burned through the workspace underneath the menu.
	     ;;   (MHD 11/30/89))
	     ;; And see note below.
	     (loop with x-in-window = (workstation-event-cursor-x workstation-event)
		   with y-in-window = (workstation-event-cursor-y workstation-event)
		   for image-plane
		       in (stack-of-image-planes
			    (pane-for-image-plane image-plane?))
		   when (and
			  ;; note: image-plane? is still in the stack, so go past
			  ;;   it:
			  (not (eq image-plane image-plane?))

			  ;; make sure it has an image (nec.?):
			  (workspace-on-image-plane? image-plane)

			  ;; within the image?:
			  (>=r x-in-window
			       (left-edge-of-image-in-window image-plane))
			  (>=r y-in-window
			       (top-edge-of-image-in-window image-plane))
			  (<r x-in-window
			      (right-edge-of-image-in-window image-plane))
			  (<r y-in-window
			      (bottom-edge-of-image-in-window image-plane)))
		     return
		       (progn
			 (setf (image-plane-for-workstation-event?
				 workstation-event)
			       image-plane)
			 (frame-serial-number-setf (frame-reference-number-for-workstation-event?
				 workstation-event)
			       (frame-serial-number
				 (workspace-on-image-plane? image-plane)))))))

;; Perhaps, the event should be discarded instead of having its image plane
;; and pane found again.  Perhaps, it should be discarded sometimes and
;; treated as it is above in other cases.  Perhaps, the frame serial
;; number should just be used by the higher level stuff instead of having
;; this function be used at all. (MHD 11/30/89)


(defun reclaim-non-kb-workspaces-for-this-workstation-only
    (list-of-non-kb-workspaces)
  (setf (non-kb-workspaces-for-this-workstation-only structure-being-reclaimed)
	nil)
  ;; Deleting workspaces has side effects on list-of- non-kb-workspaces; i.e.
  ;; the workspace backpointer reclaimer comes back and deletes the cons in
  ;; list-of-non-kb-workspaces holding this workspace
  (loop for non-kb-workspace in list-of-non-kb-workspaces
	do
    (delete-frame non-kb-workspace))
  (reclaim-gensym-list list-of-non-kb-workspaces))



;;; The function `close-telewindows-callback' is called whenever a TW
;;; connection is closed, either planned and unplanned.  A planned close calls
;;; close-telewindows-connection first, which flushes the workstation then
;;; calls us.  In that case, this function is a no-op.

;;; An unplanned close occurs when the TW process is killed asynchronously by
;;; ^C, for example.  In that case, we are called directly from
;;; transmit-icp-buffer, who will be the first guy to notice the unplanned
;;; close.

(defun close-telewindows-callback (icp-socket clean?)
  (declare (ignore clean?))		; indicates if shutdown was via shutdown or close.-ncc, 15 Apr 1996 
  (let ((workstation? (icp-socket-workstation icp-socket)))
    (when workstation?
      (maybe-schedule-service-workstation workstation? nil)
      (let ((gensym-window? (window-for-workstation workstation?)))
	(when gensym-window?
;	  (when (workstation-is-workspace-view-p workstation?)
;	    ;; Suppress connection loss notifications for workspace views,
;	    ;; whether in the ActiveX control or in the multiwindow UI: -- new
;	    ;; for 7.1 (MHD 9/3/03)
;	    (setf (suppress-connection-loss-notification-for-tw-p icp-socket) t))
	  ;; the next line will cause calls to workstation-dead-p to return t
	  
	  ;; Fix memory leak in dynamic dialog while telewindows shutdown unexpectly.
	  (reclaim-dynamic-dialogs-call-dismissed gensym-window?)

	  (setf (icp-output-port-for-window? gensym-window?) nil)))
      (setf (icp-socket-workstation icp-socket) nil))))




;;;; Drawing Parameters



(def-system-frame drawing-parameters workstation
  (allow-scheduled-drawing? t
			    (vector-slot) (system) (save)
			    (type yes-or-no))
  (drawing-in-paint-mode-p t (vector-slot) (system) (save)  ; User name is Paint Mode?
			   (type yes-or-no))
  (image-palette (:funcall-at-load-time default-value-for-image-palette)
		 (vector-slot) (system) (save)
		 (type image-palette))

  (show-selection-handles t (type yes-or-no))

  ;; Secondary selections were deemed confusing to users, so by default make them
  ;; indistinguishable from the primary selection.
  (default-primary-selection-color   green (vector-slot) (type color-or-metacolor))
  (default-secondary-selection-color green (vector-slot) (type color-or-metacolor))

  ;; Visible grid on KB workspaces
  (alignment-grid nil (type alignment-grid)))


(define-slot-alias primary-selection-color default-primary-selection-color drawing-parameters)
(define-slot-alias secondary-selection-color default-secondary-selection-color drawing-parameters)

;;; The `cleanup' method on drawing-parameters clears all slots which refer to
;;; names, which removes us as a user of those names.

(def-class-method cleanup (drawing-parameters)
  (funcall-superior-method drawing-parameters)
  (change-slot-value drawing-parameters 'image-palette nil))



;;; The absent-slot-putter `drawing-priority' handles early Beta and Alpha 4.0
;;; kbs which had a non-default value for this slot in drawing-parameters.

(def-absent-slot-putter drawing-priority (drawing-parameters value)
  value)


;;; The `initialize' and `initialize-after-reading' methods on
;;; drawing-parameters reset the default values for paint mode and scheduled
;;; drawing if this system table was created on behalf of a pre-4.0 KB.

(def-class-method initialize (drawing-parameters)
  (funcall-superior-method drawing-parameters)
  (reset-paint-mode-if-needed drawing-parameters))

(def-class-method initialize-after-reading (drawing-parameters)
  (funcall-superior-method drawing-parameters)
  (reset-paint-mode-if-needed drawing-parameters))

(defun reset-paint-mode-if-needed (drawing-parameters)
  (when (and reading-kb-p (loading-version-3-or-earlier-kb-p))
    (setf (drawing-in-paint-mode-p drawing-parameters) nil
	  (allow-scheduled-drawing? drawing-parameters) nil)))

;; Note that initialize-after-reading won't be called while reading a pre-4.0
;; KB, since such KBs do not contain any drawing-parameters to be read.  We
;; define one anyways for completeness, and to make this code parallel to the
;; code for menu-parameters.



(def-slot-putter allow-scheduled-drawing? (drawing-parameters value initializing?)
  (setf (allow-scheduled-drawing? drawing-parameters) value)
  (when (and value					    ; Scheduled implies painting.
	     (not (drawing-in-paint-mode-p drawing-parameters)))
    (change-slot-value drawing-parameters 'drawing-in-paint-mode-p t))

  (when (and (not initializing?)
  	     (system-table-installed-p drawing-parameters))
    (propagate-allow-scheduled-drawing value))
  
  value)



;; Show it to the user as "paint-mode?".
(define-slot-alias paint-mode? drawing-in-paint-mode-p drawing-parameters)



(def-slot-putter drawing-in-paint-mode-p (drawing-parameters painting initializing?)
  (setf (drawing-in-paint-mode-p drawing-parameters) painting)

  (when (and (not painting)				    ; not painting implies not scheduled.
	     (allow-scheduled-drawing? drawing-parameters))
    (change-slot-value drawing-parameters 'allow-scheduled-drawing? nil))

  ;; While loading a KB, at least at the time this slot-putter is called,
  ;; we do not know for certain whether this system table is installed
  ;; or not.  Kb-loading will later call our install-system-table method,
  ;; so defer the propagate until then.  -fmw, 8/31/94
  (when (and (not initializing?)
	     (system-table-installed-p drawing-parameters))
    (propagate-drawing-transfer-mode-to-all-gensym-windows painting))

  painting)




;;; `G2-global-paint-mode-p' is called from global-paint-mode-p, defined for
;;; both Telewindows and G2, only when running a G2 process.  It returns the
;;; value if the drawing-in-paint-mode-p slot of drawing-parameters, provided
;;; that variable is bound non-nil; otherwise, it just returns true.

(defun g2-global-paint-mode-p ()
  (cond ((and (boundp 'drawing-parameters) drawing-parameters)
	 (drawing-in-paint-mode-p drawing-parameters))
	(t
	 t)))

;; drawing-parameters is NIL during G2's initial startup.



;; This is an old name, present in some 4.0-alpha kbs.
;; The value is one of PAINT, PAINTING, or XOR.

(def-absent-slot-putter drawing-transfer-mode (drawing-parameters value)
  (change-slot-value drawing-parameters 'drawing-in-paint-mode-p
		     (if (memq value '(paint painting))
			 t
			 nil)))



;;; The class-method `install-system-table' propagates our slot values out
;;; to all affected windows, etc.

(def-class-method install-system-table (drawing-parameters)
  (propagate-allow-scheduled-drawing
    (allow-scheduled-drawing? drawing-parameters))
  (propagate-drawing-transfer-mode-to-all-gensym-windows
    (drawing-in-paint-mode-p drawing-parameters))
  (propagate-image-palette-to-all-gensym-windows
    (image-palette drawing-parameters))
  (propagate-show-selection-handles-to-all-gensym-windows
    (show-selection-handles drawing-parameters)))


(def-class-method deinstall-system-table (drawing-parameters))



;;; The function `propagate-allow-scheduled-drawing' copies the value from
;;; drawing parameters into the global variable which really controls the
;;; drawing, current-drawing-priority.  We avoid problems with local bindings of
;;; current-drawing-priority by doing the actual setq in an immediate task,
;;; which will be executed outside of any dynamic context set up by drawing.

(defun propagate-allow-scheduled-drawing (scheduled?)
  (with-immediate-scheduling ()
    (propagate-allow-scheduled-drawing-1 scheduled?)))

;;; The function `propagate-allow-scheduled-drawing-1' is to be called
;;; only as a top-level task, so that current-drawing-priority will not
;;; be lambda-bound.

(defun propagate-allow-scheduled-drawing-1 (scheduled?)
  (cond (scheduled?
	 (setq current-drawing-priority :draw-as-late-as-possible))
	(t
	 ;; Drain all of the drawing queues now?
	 (setq current-drawing-priority :draw-as-soon-as-possible))))



;;; The function `propagate-drawing-transfer-mode-to-all-gensym-windows' sets
;;; the drawing transfer mode for all currently open windows, and the default
;;; for new windows.

(defun propagate-drawing-transfer-mode-to-all-gensym-windows (painting-p)
  (let ((new-mode-name (if painting-p
			   :paint-infered-from-xor
			   :xor)))
    ;; I don't think this is needed.
    (when (boundp 'current-drawing-transfer-mode)
      (setq current-drawing-transfer-mode new-mode-name))
    (loop for workstation in workstations-in-service
	  as gensym-window = (window-for-workstation workstation)
	  doing
      (unless (eq (drawing-transfer-mode-of-gensym-window gensym-window)
		  new-mode-name)
	(setf (drawing-transfer-mode-of-gensym-window gensym-window) new-mode-name)
	(with-immediate-scheduling ()
	  ;; The macro wrapper we're using makes this refresh happen after
	  ;; coming up for air. This allows the code updating tables to complete
	  ;; in the face of a major drawing mode switch (which should not be
	  ;; expected to leave things displayed correctly), after which it will
	  ;; be possible to refresh all windows definitively. (MHD 4/14/97)
	  (refresh-window gensym-window))))))


#+development
(defun toggle-drawing-mode ()
  (let ((new-value
	  (case current-drawing-transfer-mode
	    (:xor t)
	    (t nil))))
    (change-slot-value drawing-parameters 'drawing-in-paint-mode-p new-value)
    (format t "Toggled system window, ~S, so it is now ~A~%"
	    current-drawing-transfer-mode
	    (if (eql :xor current-drawing-transfer-mode)
		"old and classic."
		"new and modern."))))


(def-slot-putter default-primary-selection-color (drawing-parameters value initializing?)
  (setf (default-primary-selection-color drawing-parameters) value)
  (unless initializing?
    (when (system-table-installed-p drawing-parameters)
      (update-all-selection-highlights 'color)))
  value)

(def-slot-putter default-secondary-selection-color (drawing-parameters value initializing?)
  (setf (default-secondary-selection-color drawing-parameters) value)
  (unless initializing?
    (when (system-table-installed-p drawing-parameters)
      (update-all-selection-highlights 'color)))
  value)

(def-slot-putter show-selection-handles (drawing-parameters value initializing?)
  (setf (show-selection-handles drawing-parameters) value)
  (when (system-table-installed-p drawing-parameters)
    (propagate-show-selection-handles-to-all-gensym-windows value initializing?))
  value)

(defun show-selection-handles-p (&optional gensym-window?)
  ;; drawing-parameters can be NIL during module deletion. Probably I should be
  ;; using show-selection-handles-of-gensym-window here, but I'm trying to
  ;; minimize changes for HQ-5448608. -fmw, 2/20/07
  (and (if drawing-parameters (show-selection-handles drawing-parameters))
       (if gensym-window? (selection-ui-p gensym-window?) t)))

(defun propagate-show-selection-handles-to-all-gensym-windows (on-p &optional initializing?)
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	doing
    (for-workstation (workstation)
      (unless (eq on-p (show-selection-handles-of-gensym-window gensym-window))
	(setf (show-selection-handles-of-gensym-window gensym-window) on-p)

	(unless initializing?
	  (update-selection-highlights-on-workstation workstation 'mode))

	(cond (on-p
	       (push-back-mouse-motion-event)
	       (start-tracking-mouse-in-current-workstation-context))
	      ((null specific-structure-for-current-workstation-context))
	      ((not (selection-style-mouse-tracking-p
		      (selection-style-of-workstation-context
			specific-structure-for-current-workstation-context)))
	       (stop-tracking-mouse-in-current-workstation-context)))))))



;;;; Alignment Grid

;; Grammar: <grid> [, line color: <color>] [, line pattern: <pattern>] [, snap to <grid>]

(defconstant alignment-grid-default-spacing '(50 . 50))
(defconstant alignment-grid-default-line-color 'foreground)
(defconstant alignment-grid-default-line-pattern 'coarse-dot)


(def-type-parameter stock-line-pattern-type
    (member solid dash dot long-dash short-dash coarse-dot fine-dot))

(def-grammar-category alignment-grid ()
  (alignment-grid-spacing (spacing 1))
  ((alignment-grid-spacing '\, alignment-grid-options) ((spacing . 1) . 3) transform-alist-into-plist))

(defun transform-alist-into-plist (alist)
  (loop for elem in alist
	when (consp elem)
	  collect (car elem) using phrase-cons and
	  collect (cdr elem) using phrase-cons))
	
(def-grammar-category alignment-grid-spacing ()
  (positive-integer (1 . 1))
  (('\( positive-integer '\, positive-integer '\)) (2 . 4)))

(def-grammar-list-category alignment-grid-options (alignment-grid-option))

(def-grammar-category alignment-grid-option ()
  (('line 'color '\: color-or-metacolor) (line-color . 4))
  (('line 'pattern '\: alignment-grid-line-pattern) (line-pattern . 4))
  (('snap 'to alignment-grid-spacing) (snap-to . 3)))

(def-grammar-category alignment-grid-line-pattern ()
  solid
  (connection-line-pattern-dot))

(def-slot-value-writer alignment-grid (value)
  (let* ((spacing (getf value 'spacing alignment-grid-default-spacing))
	 (line-color? (getf value 'line-color))
	 (line-pattern? (getf value 'line-pattern))
	 (snap-to? (getf value 'snap-to)))
    (twrite-alignment-grid-spacing spacing)
    (when line-color?
      (tformat ", line color: ~(~a~)" line-color?))
    (when line-pattern?
      (tformat ", line pattern: " line-pattern?)
      (twrite-line-pattern-element line-pattern?))
    (when snap-to?
      (tformat ", snap to ")
      (twrite-alignment-grid-spacing snap-to?))))

(def-slot-putter alignment-grid (drawing-parameters value initializing?)
  (setf (alignment-grid drawing-parameters) value)
  (unless initializing?
    (when (system-table-installed-p drawing-parameters)
      (refresh-alignment-grid-on-all-windows)))
  value)

(defun twrite-alignment-grid-spacing (spacing)
  (let ((dx (car spacing))
	(dy (cdr spacing)))
    (cond ((eql dx dy)
	   (tformat "~d" dx))
	  (t
	   (tformat "(~d,~d)" dx dy)))))

(defun alignment-grid-spacing-phrase (spacing-ev)
  (cond ((evaluation-integer-p spacing-ev)
	 (phrase-cons (evaluation-integer-value spacing-ev)
		      (evaluation-integer-value spacing-ev)))
	(t
	 (phrase-cons
	   (evaluation-sequence-ref spacing-ev 0)
	   (evaluation-sequence-ref spacing-ev 1)))))

;; Returns the fully defaulted values.
(defun unpack-alignment-grid-value (value)
  (let* ((spacing (getf value 'spacing alignment-grid-default-spacing))
	 (dx (car spacing))
	 (dy (cdr spacing))
	 (color (getf value 'line-color alignment-grid-default-line-color))
	 (pattern (getf value 'line-pattern alignment-grid-default-line-pattern))
	 (snap-to? (getf value 'snap-to))
	 (snap-dx? (car snap-to?))
	 (snap-dy? (cdr snap-to?)))
    (values dx dy color pattern snap-dx? snap-dy?)))

(define-category-evaluator-interface (alignment-grid :access read-write)
    (structure alignment-grid-spec
	       ((spacing (or integer (sequence integer 2 3)))
		(line-color symbol)
		(line-pattern #.stock-line-pattern-type)
		(snap-to (or integer (sequence integer 2 3)))))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value alignment-grid-spec)
     (nconc
       (when spacing
	 (phrase-list 'spacing (alignment-grid-spacing-phrase spacing)))
       (when line-color
	 (phrase-list 'line-color line-color))
       (when line-pattern
	 (phrase-list 'line-pattern line-pattern))
       (when snap-to
	 (phrase-list 'snap-to (alignment-grid-spacing-phrase snap-to))))))
  ((get-form (slot-value))
   (multiple-value-bind (dx dy line-color line-pattern snap-dx? snap-dy?)
       (unpack-alignment-grid-value slot-value)
     (allocate-evaluation-structure
       (nconc
	 (eval-list
	   'spacing (allocate-evaluation-sequence (eval-list dx dy))
	   'line-color line-color
	   'line-pattern line-pattern)
	 (when snap-dx?
	   (eval-list 'snap-to (allocate-evaluation-sequence (eval-list snap-dx? snap-dy?)))))))))

(defun get-global-snap-grid ()
  (multiple-value-bind (dx dy color pattern snap-dx? snap-dy?)
      (unpack-alignment-grid-value
	(alignment-grid drawing-parameters))
    (declare (ignore dx dy color pattern))
    (values snap-dx? snap-dy?)))

(defun visible-grid-permitted-p (image-plane)
  (and (workspace-on-image-plane? image-plane)
       (kb-workspace-p (workspace-on-image-plane? image-plane))))

(defun visible-grid-p (image-plane)
  (and (visible-grid-permitted-p image-plane)
       (get-view-preference (image-plane-view-preferences image-plane) 'visible-grid)))

(defun set-visible-grid-p (image-plane value)
  (when (visible-grid-permitted-p image-plane)
    (setf-view-preference (image-plane-view-preferences image-plane) 'visible-grid (if value t nil))
    value))

(defun refresh-alignment-grid (image-plane)
  (let ((current-draw-paper-p nil)) ; Skip the redundant sketch
    (invalidate-image-plane image-plane)))

(defun refresh-alignment-grid-on-all-windows ()
  (loop for workstation in workstations-in-service doing
    (loop for image-plane in (stack-of-image-planes (detail-pane-for-workstation workstation)) doing
      (when (visible-grid-p image-plane)
	(refresh-alignment-grid image-plane)))))

(defun toggle-visible-grid (image-plane)
  (when (visible-grid-permitted-p image-plane)
    (set-visible-grid-p image-plane (not (visible-grid-p image-plane)))
    (refresh-alignment-grid image-plane)))

;;; The function `draw-alignment-grid' draws a user-specified rectangular grid
;;; on the current image-plane, within the given region in window
;;; coordinates. It must be careful to preserve the phase of patterned lines.

(defun draw-alignment-grid (left top right bottom)
  (multiple-value-bind (dx dy line-color line-pattern)
      (unpack-alignment-grid-value
	(alignment-grid drawing-parameters))
    (let ((color-value (map-color-or-metacolor-to-color-value line-color))
	  (pattern-value (lookup-stock-line-pattern-element line-pattern))
	  (lcm least-common-multiple-of-stock-line-pattern-lengths)
	  (line-width 1))		; Need a geometric pen (zero width is cosmetic)

      ;; Vertical
      (loop with y-origin = (y-in-window 0)
	    with y0 = (+f y-origin (*f lcm (floorf (-f top y-origin) lcm)))
	    with y1 = bottom
	    for k from (floorf (x-in-workspace left) dx)
		  to (ceilingf (x-in-workspace right) dx)
	    as x = (x-in-window (*f k dx))
	    doing
	(draw-patterned-line x y0 x y1 color-value line-width pattern-value))

      ;; Horizontal
      (loop with x-origin = (x-in-window 0)
	    with x0 = (+f x-origin (*f lcm (floorf (-f left x-origin) lcm)))
	    with x1 = right
	    for k from (floorf (y-in-workspace top) dy)
		  to (ceilingf (y-in-workspace bottom) dy)
	    as y = (y-in-window (*f k dy))
	    doing
	(draw-patterned-line x0 y x1 y color-value line-width pattern-value)))))


;;;; The Image palette slot


(def-grammar-category image-palette ()
  (('black 'and 'white) black-and-white)		    ; Possibly dithered.
  (('standard 'colors) standard-colors)			    ; The current 63 color palette.
  (('standard 'grays) standard-grays)

  (('extended 'colors) extended-colors)			    ; Some new 100-odd color palette
  (('extended 'grays) extended-grays)

  (('custom 'colors 'from image-name) (custom-colors 4))    ; Exact colors from a given image.
  (('custom 'grays 'from image-name) (custom-grays 4)))


(def-substitution-macro image-palette-name (image-palette)
  (car-or-atom image-palette))


(def-substitution-macro image-palette-image-name (image-palette)
  (and (consp image-palette)
       (second image-palette)))


(def-slot-putter image-palette (drawing-parameters new-value)
  (let ((old-value (image-palette drawing-parameters)))
    (cond ((equal new-value old-value)
	   ;; If equal, do not do any updates, but still need to set the slot,
	   ;; since they may not be EQ.
	   (setf (image-palette drawing-parameters) new-value))
	  (t
	   ;; Update the slot, possibly noting us as a user of a name.
	   ;; Consistency analysis does all the updating of images, posting
	   ;; frame notes, etc.
	   (without-consistency-analysis (drawing-parameters)
	     (setf (image-palette drawing-parameters) new-value))))
    new-value))



(def-slot-value-writer image-palette (value)
  (let ((palette-name (image-palette-name value))
	(image-name? (image-palette-image-name value)))
    (case palette-name
      (black-and-white (twrite-string "black and white"))
      (standard-grays (twrite-string "standard grays"))
      (standard-colors (twrite-string "standard colors"))
      (extended-grays (twrite-string "extended grays"))
      (extended-colors (twrite-string "extended colors"))
      (custom-grays
       (tformat "custom grays from ~(~a~)" image-name?))
      (custom-colors
       (tformat "custom colors from ~(~a~)" image-name?))
      (t
       #+development (twrite value)))))


(defun image-palette-color-map? (image-palette)
  (let* ((image-name? (image-palette-image-name image-palette))
	 (image-definition? (and image-name?
				 (find-image-named image-name?)))
	 (image-data? (and image-definition?
			   (image-definition-data? image-definition?)))
	 (color-map? (and image-data?
			  (image-data-color-map image-data?))))
    color-map?))

			 
;; Old slot name.  Exists in some 4.0-alpha kbs.
(def-absent-slot-putter image-rendering-quality (drawing-params value)
  (let ((new-value
	  (case value
	    (standard-gray 'standard-grays)
	    (standard-color 'standard-colors)
	    (extended-gray 'extended-grays)
	    (extended-color 'extended-colors)
	    (custom-color
	     (slot-value-list 'custom-colors 'some-image-name))
	    (custom-gray
	     (slot-value-list 'custom-grays 'some-image-name))
	    (t
	     value))))
    (setf (image-palette drawing-params) new-value)))



;;; Maybe name consistency anal will take care of this for us?

(def-frame-note-writer drawing-parameters-image-incomplete (particulars)
  (gensym-dstruct-bind ((image-name) particulars)
    (tformat "the image ~(~a~) is incomplete" image-name)))


;;; The class-method `update-frame-status-and-notes' posts warnings about an
;;; incomplete image in a "custom colors/grays from <image>" clause.

(def-class-method update-frame-status-and-notes (drawing-parameters)
  (with-updates-to-representations-supressed
      (drawing-parameters 'frame-status-and-notes)
    (funcall-superior-method drawing-parameters)
    (let* ((frame-status? nil)				    ; aka OK
	   (image-palette (image-palette drawing-parameters))
	   (image-name? (image-palette-image-name image-palette))
	   (color-map? (image-palette-color-map? image-palette)))
      (delete-frame-note-if-any 'drawing-parameters-image-incomplete drawing-parameters)

      ;; Don't mention it if we are not installed (?)
      (when (system-table-installed-p drawing-parameters)
	(when (and image-name?
		   (find-image-named image-name?)
		   (null color-map?))
	  (add-frame-note 'drawing-parameters-image-incomplete drawing-parameters
			  (slot-value-list image-name?) t)))
      (update-frame-status drawing-parameters frame-status? nil))))




;;; The function `propagate-image-palette-to-all-gensym-windows' assures
;;; all connected gensym-windows use the given image-palette.  It does not
;;; check that the value has actually changed.

(defun propagate-image-palette-to-all-gensym-windows (image-palette)
  (let ((palette-name (image-palette-name image-palette))
	(color-map? (image-palette-color-map? image-palette)))
    ;; Set it for all existing windows.
    ;; This reclaims all existing renderings.
    (loop for workstation in workstations-in-service
	  as gensym-window = (window-for-workstation workstation)
	  doing
      (set-image-palette-of-gensym-window gensym-window palette-name color-map?))

    ;; This queues the workspace redraws for all the affected regions.
    (invalidate-all-image-renderings)))



;;; The function `set-image-palette-of-gensym-window' changes the image palette
;;; for a gensym-window. We set the slot locally, and if it is an ICP window,
;;; send an ICP message to change it on the far side.

(defun set-image-palette-of-gensym-window (gensym-window palette-name color-map?)
  (setf (image-palette-of-gensym-window gensym-window) palette-name)
  ;; If a local window, or, an ICP window of sufficient version, tell it to
  ;; change itself.
  (when (or (not (eq (type-of-gensym-window gensym-window) 'icp))
	    (current-window-supports-image-painting gensym-window))
    (update-window gensym-window
		   (left-edge-of-window gensym-window)
		   (top-edge-of-window gensym-window)
		   (right-edge-of-window gensym-window)
		   (bottom-edge-of-window gensym-window)
		   ;; This is an ICP message, in case you were wondering.
		   'change-image-palette-of-window
		   gensym-window
		   palette-name
		   color-map?)))


;;; The function `initialize-image-palette-of-new-gensym-window' is called
;;; from `obtain-max-window-protocol'.  It is a stub in telewindows.

(defun initialize-image-palette-of-new-gensym-window (gensym-window)
  (let* ((image-palette (image-palette drawing-parameters))
	 (palette-name (image-palette-name image-palette))
	 (color-map? (image-palette-color-map? image-palette)))
    (set-image-palette-of-gensym-window gensym-window palette-name color-map?)))



;;;; Timing Parameters (moved to TABLES, MHD, 2/4/00)





;;;; Servicing Workstations

;; workstations-in-service is now in TELESTUBS. (MHD 3/7/89)



;;; `Set-up-workstation' makes and initializes a workstation for gensym-window,
;;; fills in the workstation-this-is-on slot of gensym-window, and then adds the
;;; new workstation to the list in special variable workstations-in- service.
;;; The new workstation is returned.

(defun set-up-workstation (gensym-window)
  (let ((workstation (make-workstation
		       gensym-window)))
    (set-up-workstation-on-ab-side workstation gensym-window nil)))

;; This should be set-up-main-workstation.



;;; `Flush-workstation' completely shuts down a workstation by
;;; 
;;;    (1) logging out the user if we have one;
;;;    (2) unwinding all the workstation contexts;
;;;    (3) reclaiming the workstation structure, which
;;;        has side effects on these (conceptual) slots:
;;;             workstation-event-queue
;;;             local-event-queue
;;;             gensym-window
;;;        and
;;;    (4) removing workstation from workstations-in-service
;;;    
;;; Flush-workstation is called when a connection into G2 is closing.
;;; Note that connections may be closed intentionally or due to failure.

(defun flush-workstation (workstation)
  (with-backtrace-for-internal-error 'flush-workstation
    (for-workstation (workstation)
      ;; Call TWNG disconnect callback
      (when (and system-is-running (twng-window-p (window-for-workstation workstation)))
        (call-twng-disconnect-callbacks (window-for-workstation workstation)))
        (unless (workstation-flush-in-progress? workstation)
	  
      (setf (workstation-flush-in-progress? workstation) t)	  
      (log-out-workstation workstation)
      (unwind-all-workstation-contexts workstation)

      ;; Reclaim icp object map and workstation.  Note that it is not
      ;; necessary to send an ICP message to the remote process to
      ;; reclaim the corresponding workstation.  See also notes for
      ;; reclaim-window-for-workstation.
      (let ((delete-corresponding-object? nil))
        (reclaim-icp-object-map-for-workstation workstation))
      (reclaim-workstation workstation)))))

;; We don't want to allow log-out-workstation to do any drawing here.




;;; `Force-process-drawing' forces drawing on all the connected windows.  This
;;; is called in the midst of long operations that ought to be reschedulable,
;;; but we aren't clever enough yet, e.g.  KB load.  NO context (workstation,
;;; window, etc) is required.

;;; On occasion the drawing queues are "locked" and may not be drained because
;;; the KB is in some inconsistent, intermediate state.  In that case,
;;; we do nothing here but note that we happened.

(defun force-process-drawing ()
  (cond (drawing-is-locked?
	 (setq drawing-is-locked? 'force-process-drawing))
	(t
	 (do-some-icp-processing)
	 (loop for workstation in workstations-in-service
	       unless (and (eq workstation (workstation-this-is-on system-window))
			   (no-local-window-p))
	       do #-SymScale (force-workstation-drawing workstation)
		  #+SymScale (if (in-main-thread-p)
				 (force-workstation-drawing workstation)
			       (maybe-schedule-service-workstation workstation t)))
	 (flush-icp-output-ports))))


(defun-allowing-unwind do-some-icp-processing ()
  (with-scheduler-disabled
    (get-pending-network-events)))

;; Other forcing routines should obey the locking, too.


;;; The function `force-process-drawing-if-appropriate' drains all of the
;;; drawing queues for all workspaces if we are in ASAP mode.  It doesn't,
;;; however, poll for new events or call sync graphics.

(defun force-process-drawing-if-appropriate ()
;  (when (draw-as-soon-as-possible?)
  #+SymScale
  (unless (in-main-thread-p)
    (return-from force-process-drawing-if-appropriate))
  (unless (drawing-is-scheduled?)	; Note
    (loop for workstation in workstations-in-service
	  unless (and (eq workstation (workstation-this-is-on system-window))
		      (no-local-window-p))
	  doing
      (for-workstation-polling (workstation)
	(drain-current-workstation-drawing-queue)))
    (flush-icp-output-ports)))

;; Note: Only caller is TRANSFER-GROUPED-BLOCKS-WITH-THEIR-EXTERNAL-CONNECTIONS.
;; We always see the top-level binding of current-drawing-priority here, so we
;; must use drawing-is-scheduled? instead of draw-as-soon-as-possible?.  This is
;; a temporary fix-for-revision for the regression bug HQ-4094848, in order to
;; minimize changes and potential deleterious fanout.  The correct fix will
;; appear in the next release.  See discussion in change log for HQ-4094848.
;; -fmw, 12/10/01


;;; The function `force-workstation-drawing' forces drawing for the given
;;; workstation. Note this will establish a with-unlimited-time-slice.  This,
;;; surprisingly, calls poll-workstation, which forces reshape events into the
;;; drawing Queues.  NO context (workstation, window, etc) is required.

(defun force-workstation-drawing (workstation)
  (for-workstation-polling (workstation)

    ;; Get any pending reshape events.
    (poll-workstation)

    ;; Flush all drawing tasks out of the image-plane and pane queues.
    (drain-current-workstation-drawing-queue)

    ;; Do the force at the window system level.
    ;; This sends a message to flush ICP windows.
    (update-window
      current-workstation-window
      (left-edge-of-window current-workstation-window)
      (top-edge-of-window current-workstation-window)
      (right-edge-of-window current-workstation-window)
      (bottom-edge-of-window current-workstation-window)
      'sync-graphics-on-current-window)))





;;; The function `force-some-process-drawing' performs drawing tasks for the given
;;; workstation until the current time-slice expires.

(defun force-some-process-drawing ()
  (loop for workstation in workstations-in-service
	until (time-slice-expired-p)
	doing
    (for-workstation (workstation)
      (work-on-drawing-for-workstation workstation))))





;;; The substitution-macro `work-on-current-query-for-workstation' works a little
;;; on the current inspector search for the given workstation.  It returns t
;;; if any work was done.

(def-substitution-macro work-on-current-query-for-workstation (workstation)
  (when (search-states-in-this-workstation workstation)
    (with-backtrace-for-internal-error 'service-workstation-handle-search-states
      (loop for element in (search-states-in-this-workstation workstation)
	    as (kb-search-state . frame-serial-number) = element
	    if (frame-has-been-reprocessed-p
		 kb-search-state frame-serial-number)
	      collect element into elements-to-delete using gensym-cons
	    else do (let ((finished? nil))
		      (unwind-protect
			   (progn
			     (search-items-a-little
			       kb-search-state (current-frame-serial-number))
			     (setq finished? t))
			(unless finished?		    ; error happened?!
			  (delete-gensym-element	    ; flush search
			    element
			    (search-states-in-this-workstation
			      workstation))
			  (reclaim-frame-serial-number (cdr element))
			  (reclaim-gensym-cons element))))
		
	    finally
	      (when elements-to-delete
		(loop for element in elements-to-delete
		      do (setf 
			   (search-states-in-this-workstation
			     workstation)
			   (delete-gensym-element
			     element
			     (search-states-in-this-workstation
			       workstation)))
			 (reclaim-frame-serial-number (cdr element))
			 (reclaim-gensym-cons element)
		      finally
			(reclaim-gensym-list
			  elements-to-delete)))
	      (return t)))))

;; Maybe query states could be built upon background processes?




;;;; Event tracing


(defvar trace-workstation-events nil)

(defun trace-events ()
  (setq trace-workstation-events t
	trace-reshape-events t))

(defun untrace-events ()
  (setq trace-workstation-events nil
	trace-reshape-events nil))


;;; The function `trace-workstation-event' comes in two versions, one for
;;; development and one for the build.

(defun trace-workstation-event (mouse-pointer handler context-of-handler)
  #+development
  (if (eq trace-workstation-events 'simple)
      (simple-trace-workstation-event mouse-pointer handler context-of-handler)
      (fancy-trace-workstation-event mouse-pointer handler context-of-handler))
  #-development
  (simple-trace-workstation-event mouse-pointer handler context-of-handler))



#+development
(defun fancy-trace-workstation-event (mouse-pointer handler context-of-handler)
  (let* ((stack (workstation-context-stack current-workstation))
	 (top-of-stack (type-of-workstation-context (first stack))))
    (format t "~&~va~12a ~50s runs ~s"
	    (* 2 (- (length stack) 1)) ""
	    top-of-stack
	    mouse-pointer
	    handler)
    (unless (or (null handler)
		(eq top-of-stack context-of-handler))
      (format t " ~((~s)~)" context-of-handler))
    (terpri)
    (force-output)))


(defun simple-trace-workstation-event (mouse-pointer handler context-of-handler)
  (declare (ignore context-of-handler))
  (let* ((stack (workstation-context-stack current-workstation))
	 (top-of-stack (type-of-workstation-context (first stack)))
	 (spot? (stack-of-spots mouse-pointer))
	 (window-type
	   (type-of-gensym-window
	     (window-for-workstation current-workstation)))
	 (*print-case* :downcase))

    (format t "~2a ~9d ~4d ~4d ~12a ~a ~a -> ~a~%"
	    (case window-type (x11-window 'g2) (icp 'tw) (t window-type))
	    (fixnum-time-of-mouse-pointer mouse-pointer)
	    (x-of-mouse-pointer mouse-pointer)
	    (y-of-mouse-pointer mouse-pointer)
	    (symbol-from-key-code
	      (key-code-of-mouse-pointer mouse-pointer))
	    (if spot?
		(name-of-type-description
		  (type-description-of spot?))
		"")
	    top-of-stack
	    handler)))




;;;; Polling Workstations




;;; See also the subsection of the same name in TELESTUBS.



;;; The system-variable `round-robin-workstation-index' is the index into
;;; workstations-in-service at which service-workstations begins its work.  It
;;; may become out of range if a workstation is deleted, in which we simply
;;; reset it to zero.

#+perhaps
(def-system-variable round-robin-workstation-index workstation 0)



;;; `Current-workstation-has-pending-events-p' returns true if the current
;;; workstation has pending workstation events.  This is intended as a very
;;; inexpensive test and can be called by higher level functions to determine
;;; if they should stop in order for user input events to be serviced.  This
;;; must be used in a for- workstation context.

(defun-simple current-workstation-has-pending-events-p ()
  (or (not (queue-empty-p (workstation-event-queue current-workstation)))
      (poll-workstation)))




(def-system-variable task-to-run-service-workstations-final WORKSTATION nil)
(def-system-variable future-task-to-run-propagate-all-workspace-changes-to-image-planes WORKSTATION nil)
(def-system-variable current-task-to-run-propagate-all-workspace-changes-to-image-planes WORKSTATION nil)

(defparameter service-workstations-final-interval 1.000)
(defparameter service-workstation-interval  0.100)

(defun-void maybe-schedule-service-workstations (both-future-and-current-p)
  (loop for workstation in workstations-in-service
	do (maybe-schedule-service-workstation workstation both-future-and-current-p))
  (maybe-schedule-service-workstations-final))

(defun-void maybe-schedule-task-to-run-propagate-all-workspace-changes-to-image-planes ()
  (unless (future-schedule-task-in-place-p
	    future-task-to-run-propagate-all-workspace-changes-to-image-planes)
    (with-future-scheduling (future-task-to-run-propagate-all-workspace-changes-to-image-planes 0
                              (+e (managed-float-value (clock-get current-real-time))
				  service-workstation-interval)
			      nil nil t nil 'workstation)
      (propagate-all-workspace-changes-to-image-planes)))
  (unless (current-schedule-task-in-place-p
	    current-task-to-run-propagate-all-workspace-changes-to-image-planes)
    (with-current-scheduling (current-task-to-run-propagate-all-workspace-changes-to-image-planes 11
			       nil nil t nil 'workstation)
      (propagate-all-workspace-changes-to-image-planes))))

(defun-void maybe-schedule-service-workstations-final ()
  (when (or background-processes
	    #+development
	    (tables-exist-for-service-workstations-cruft-p))
    (unless (future-schedule-task-in-place-p task-to-run-service-workstations-final)
      (with-future-scheduling (task-to-run-service-workstations-final
				0
				(+e (managed-float-value (clock-get current-real-time)) 
				    service-workstations-final-interval)
				nil nil t nil 'workstation)
	(service-workstations-final)))))

(defun maybe-schedule-service-workstation (workstation? both-future-and-current-p)
  (when (and (null workstation?) system-window)
    (setq workstation? (workstation-this-is-on system-window)))
  (unless workstation?
    (maybe-schedule-service-workstations nil)
    (return-from maybe-schedule-service-workstation nil))
  (let ((workstation workstation?))
    (when (not (future-schedule-task-in-place-p
		 (future-task-to-run-service-workstation workstation)))
      (with-future-scheduling ((future-task-to-run-service-workstation workstation) 0
			       (+e (managed-float-value (clock-get current-real-time))
				   service-workstation-interval)
			       nil nil t nil 'workstation)
	(service-workstation workstation)))
    (when (and (not (current-schedule-task-in-place-p
		      (current-task-to-run-service-workstation workstation)))
	       (or both-future-and-current-p
		   (and (eq (type-of-gensym-window
			      (window-for-workstation workstation))
			    'x11-window)
			(queue-non-empty-p
			  (event-queue system-window))) ; player
		   (queue-non-empty-p (workstation-event-queue workstation))
		   (pending-drawing-for-workstation-p workstation)))
      (with-current-scheduling ((current-task-to-run-service-workstation workstation) 11
				nil nil t nil 'workstation)
	(service-workstation workstation)))))

(defun-void propagate-all-workspace-changes-to-image-planes ()
  (cancel-task future-task-to-run-propagate-all-workspace-changes-to-image-planes)
  (cancel-task current-task-to-run-propagate-all-workspace-changes-to-image-planes)

  (when (>f count-of-pending-workspace-drawing 0)
    (loop for workstation in workstations-in-service
          as gensym-window = (window-for-workstation workstation)
          do (check-for-pending-drawing-on-window gensym-window))

    ;; For now, keep this warning in production.  It should never occur. See bug
    ;; HQ-3742490. -fmw, 12/6/01
    (unless (~=f count-of-pending-workspace-drawing 0)
      (notify-user-at-console
	"[G2 internal warning] count-of-pending-workspace-drawing ended up non-zero after complete propagation! (= ~d)"
	count-of-pending-workspace-drawing))))

;need to use (eq (interface-mode timing-parameters) 'time-slice-dependant)
(defparameter normal-workstation-servicing-time-limit
  (fixnum-time-interval 50))
(defparameter prefer-interfaces-workstation-servicing-time-limit
  (fixnum-time-interval 200))

(defun service-workstations-final ()
  #+development (service-workstations-cruft)
  ;; Donate any extra time we have to printing.  Do not starve printing completely,
  ;; even if the time slice has expired.
  ;; -fmw, 2/22/94
  (service-background-processes)
  (maybe-schedule-service-workstations-final))

;; This can starve workstations that appear at the end of the list! - ben 9/2/93

;; In fact, it nearly always will.  For example, if the first workstation on
;; the list is a telewindow, then its graphics are so slow it will always
;; consume the entire time slice, until it is done drawing.  Only then will the
;; local X window will get any drawing cycles.  Probably, we should round-robin
;; the list workstations-in-service.  Then again, maybe it's better as it stands:
;; slow telewindows sit motionless for a long period then will refresh completely,
;; as opposed to refreshing in dribs and drabs.  I don't really know what is
;; preferable.


#+development
(defun tables-exist-for-service-workstations-cruft-p ()
  (or (loop for table being each class-instance of 'memory-management-table
	    thereis table)
      (loop for table being each class-instance of 'telewindows-status-table
	    thereis table)))

#+development
(defun service-workstations-cruft ()
  (when (tables-exist-for-service-workstations-cruft-p)
    (update-memory-allocation-displays)		    ; memory management table display hack
    (update-telewindow-status-displays)		    ; telewindows status table display hack
    (force-process-drawing)))



;;; The function `service-workstation' performs a chunk of work pending for a
;;; workstation, if any, and returns work-was-done?.  If an image plane needs
;;; refreshing, then that is given priority.  Else, if an event pending, we
;;; funcall its handler.  Consecutive mouse-motion events are compressed.
;;; Finally, we offer a time-slice to any drawing operations in progress and
;;; then to any search operations in progress.  There is some once-only code
;;; here to load G2 init files.  I dunno what the launch-recompilation stuff is.

;;; When there are multiple activities pending on a given workstation, they are
;;; performed strictly in the following order:
;;;
;;;    (1) if there has been no attempt to load the g2 init, that is done;
;;;
;;;    (2) if the workstation has not been logged into, entering a login
;;;      context;
;;;
;;;    (3) if the workstation event queue is empty, polling for such events;
;;;
;;;    (4) continuing to refresh an image plane on the workstation;
;;;
;;;    (5) handling enqueued workstation events, in order;
;;;
;;;    (6) continuing parsing, if it has been suspended and if the edit box has
;;;      no text regions.



;;; `Service-workstation' implements the micro task that manages a single workstation.
;;; It establishes a for-workstation context for all routines called within it.

;;; There are five main subtasks:
;;;   1. event handling,
;;;   2. drawing,
;;;   3. reschedulable inspect, and
;;;   4. editor parsing and prompts
;;;   5. idle events for the current workstation context
;;; commands.

;;; There are some minor one-of mechanisms:
;;;   1. logging in  (a workstation that has is not logged in, goes into a special mode).
;;;   2. loading the g2 ok file (triggered by not being authorized).
;;;   3. loading an initial KB (as triggerd by the command line).
;;;   3. launching a recompile all command (triggered by loading a KB needing this).

;;; An indication is returned if any work was actually done during this time slice.

;; `service-workstation-main' handles a one workstation event and is called by service-workstation

(defun-allowing-unwind service-workstation-main (workstation)
  #+development (update-pseudo-run-lights :service-workstation)
  (check-memory-for-development 'service-workstation_start)
  (cancel-task (current-task-to-run-service-workstation workstation))
  (cancel-task (future-task-to-run-service-workstation workstation))
  (when (null (window-for-workstation workstation))
    (notify-user-at-console "An incomplete workstation was encountered ~
      and ignored by G2.")
    (return-from service-workstation-main nil))
  (when (workstation-dead-p workstation)
    (flush-workstation workstation)
    (return-from service-workstation-main nil))
  (with-drawing-trace (service-workstation)
    (format t "==================== Service ~s ====================~%" 
 	    workstation))

  (let ((work-was-done? nil)
	(initial-time-slice-expired-p (time-slice-expired-p)))
    (with-icp-buffer-coelescing-scope
      (for-workstation (workstation)
	(validate-mouse-pointers workstation)
	(loop until (valid-workstation-context-p
		      specific-structure-for-current-workstation-context)
	      do (abort-current-workstation-context type-of-current-workstation-context))
	
	(when do-g2-init-file?
	  (setq do-g2-init-file? nil)
	  (when (g2-authorized-p)
	    (with-backtrace-for-internal-error 'service-workstation-g2-init
	      ;; Note: previously the command-line option "-kb" will be ignored if there's
	      ;; also an "-init" command-line option at the same time. Now we support them
	      ;; together: the KB file specified in "-kb" is treated as the first command
	      ;; in "-init" file, and all commands in the init file will be executed after
	      ;; the KB is loaded.  As a result, (do-g2-init-file) won't be called here any
	      ;; more, instead, (do-g2-kb-load-at-launch) will call (do-g2-init-file) after
	      ;; loading the KB.                       -- Chun Tian (binghe), 4 Sep 2016.
	      (unless nil ;; old: (do-g2-init-file)
		;; jh, 5/29/92.  Added the facility to load and possibly start a
		;; single KB at launch from the command line.
		(unless (do-g2-kb-load-at-launch)
		  (enable-scc-check))))))

	(let ((login-state (workstation-login-state workstation)))
	  (when (memq-p-macro login-state '(logged-out changing-kbs))
	    (setf (workstation-login-state workstation) 'logging-in)
	    (with-backtrace-for-internal-error 'service-workstation-enter-login
	      (enter-user-settings-editor
		(if (eq login-state 'changing-kbs) 'reloading 'starting)))))

	(when (and (eq workstation workstation-in-which-to-launch-recompilation?)
		   (logged-in-workstation-session-p workstation))
	  (with-backtrace-for-internal-error
	      'service-workstation-launch-recompilation
	    (launch-recompilation-for-this-kb)))
	
	(check-memory-for-development 'service-workstations_b)

	(when (or (not (queue-empty-p (workstation-event-queue current-workstation)))
		  (progn (when (poll-workstation)
			   (setq work-was-done? t)) ; Did work if saw refresh events.
			 (not (queue-empty-p (workstation-event-queue current-workstation)))))

	  (with-backtrace-for-internal-error 'service-workstation-event
	    (check-memory-for-development 'service-workstations_event-handling_start)

	    (let ((workstation-event? (shift-lexical-analysis-of-current-workstation?)))
	      (unless (or workstation-event?
			  (queue-empty-p (workstation-event-queue current-workstation)))
		(setq work-was-done? t))
	      (when workstation-event?
		(with-named-dynamic-extent* servicing-workstation-event
		    ((current-workstation-event workstation-event?))
		  (with-edit-warning-context ()
		    (multiple-value-bind (event-interpretation? context-of-handler?)
			(find-event-interpretation current-workstation-event workstation)

		      #+development (update-pseudo-run-lights :pending-events)

		      (when trace-workstation-events
			(trace-workstation-event
			  (mouse-pointer-of-latest-event current-workstation)
			  event-interpretation? context-of-handler?))

		      (cond
			;; Prefer to continue to refresh an image-plane over processing the event.
			((and (image-plane-to-continue-refreshing? workstation)
			      (not (and (event-handler-refreshes-image-plane-p event-interpretation?)
					(eq (image-plane-to-continue-refreshing? workstation)
					    (image-plane-for-workstation-event?
					      current-workstation-event)))))
			 (check-memory-for-development
			   'service-workstations_event-handling_continued-refresh)
			 (continue-refreshing-image-plane workstation)
			 (requeue-workstation-event current-workstation-event workstation)
			 (setq work-was-done? t))

			;; Handle the event.
			(event-interpretation?
			 (check-memory-for-development
			   'service-workstations_event-handling_run-event-handler)
			 (run-event-handler event-interpretation?
					    (mouse-pointer-of-latest-event current-workstation))
			 ;; Partial commands better not hang on to events!
			 (reclaim-workstation-event current-workstation-event)
			 (setq work-was-done? t))

			;; Maybe complain about unhandled events.
			(t ; enter-window and leave-window used to do OLE stuff, now do nothing
			 (check-memory-for-development 'service-workstations_event-handling_no_handler)
			 #+development
			 (when trace-workstation-events
			   (warn "Unhandled event in ~s context: ~s"
				 (type-of-workstation-context current-workstation-context)
				 current-workstation-event))
			 (reclaim-workstation-event current-workstation-event)
			 (setq work-was-done? t)))

		      (when event-interpretation?
			(reclaim-event-interpretation event-interpretation?)))))))
	    
	    (check-memory-for-development 'service-workstations_event-handling_end)))

	(when (and (not work-was-done?)
		   (image-plane-to-continue-refreshing? workstation))
	  (check-memory-for-development 'service-workstations_d)
	  #+development (update-pseudo-run-lights :continuing-refeshing)
	  (with-backtrace-for-internal-error
	      'service-workstation-keep-refreshing-image
	    (continue-refreshing-image-plane workstation))
	  (setq work-was-done? t))

	;; Feed "Idle Events" to the editor.
	(when (and (not work-was-done?)
		   (eq type-of-current-workstation-context 'editing)
		   (extend-parsing-or-exit-editor-as-appropriate))
	  (check-memory-for-development 'service-workstations_e)
	  (setq work-was-done? t))

	(when (work-on-drawing-window current-workstation-window t)
	  (setq work-was-done? t))

	(when (work-on-current-query-for-workstation workstation)
	  (setq work-was-done? t))

	(when (native-menu-bar-really-needs-updating-p workstation)
	  (update-native-menu-bar workstation)
	  (setq work-was-done? t))))

    (when work-was-done?
      (when (eq (workstation-login-state workstation) 'changing-kbs)
	(finish-changing-kb-for-workstations))
      (unless initial-time-slice-expired-p
	(setq last-workstation-serviced workstation)))

    (check-memory-for-development 'service-workstation_finish)
    (when work-was-done?
      (maybe-schedule-service-workstation workstation t))
    (when need-call-system-start
      (setq need-call-system-start nil)
      (system-start))

    work-was-done?))


;; `service-workstation' routine that handles all workstation events
;; it repeatly call `service-workstation-main' until queue-size becomes zero.

(defun-allowing-unwind service-workstation (workstation)
  (let* ((queue (workstation-event-queue workstation))
         (result (service-workstation-main workstation))
         (queue-size (queue-length queue)))
    (loop while (>f queue-size 0) do
      (setq result (service-workstation-main workstation))
      (decff queue-size))
    (return-from service-workstation result)))


;; Fix to be fairer!

;; Consider verifying that a workspace event handler is defined, here and in
;; workspace event execution functions.

;; Consider having parsing extension done for other editing contexts than the
;; current one for the workstation, although that would present implementation
;; problems and might prove confusing to the user if parsing failed or ended.

;; Consider having this handle more than one workstation event or image-
;; plane-refresh-quantum.



;;; `Finish-changing-kb-for-workstations' is responsible for
;;; attempting to (re)login all the workstations connected to this
;;; G2 a fresh KB appears on the scene.  We want this done as soon
;;; as possible since the show-workspace (as well as many other things)
;;; doesn't work until the workstations in question are in logged in.

(defun finish-changing-kb-for-workstations ()
  #+development
  (when servicing-workstation?
    (cerror "Continue?" "See finish-changing-kb-for-workstations."))

  (loop
    for workstation in workstations-in-service
    when (and
	   ;; don't do anything if workstation is "dead"; note: workspace-view
	   ;; workstations die when changing KBs: (MHD 7/24/03)
	   (not (workstation-dead-p workstation))
	   (eq (workstation-login-state workstation) 'changing-kbs))
      do
	(for-workstation (workstation)
	  (setf (workstation-login-state workstation) 'logging-in)
	  (with-backtrace-for-internal-error
	      'service-workstation-enter-login-2
	    (enter-user-settings-editor 'reloading)))))

;; This routine was introduced to fix a bug that loading a KB and starting it
;; from within service workstation would find it's self running the intially
;; rules in a KB with no logged in workstations.

;; Note that calling this from the code that created the fresh KB would be the
;; oovious thing to do, but that's hard since it is risky to recure
;; for-workstation.  So instead we call it in the epilog of service-workstation.

;; There is presumably a bug with autostart KB's loaded via a system procedure.




;;; The `track-mouse-into-spot' method defined on the abstract structure type
;;; spot is the method of last resort.  If frame represents a block it will call
;;; the generate-spot method on that block.  No matter what it
;;; futher-tracking-maybe-required will be nil after it is called.

(def-structure-method track-mouse-into-spot (spot)
  (when (further-tracking-maybe-required? spot)
    (let ((frame-represented? (frame-represented? spot)))
      (when (and frame-represented?
		 (block-p frame-represented?))
	(funcall-method 'generate-spot
			frame-represented?
			(mouse-pointer-of-spot spot))))
    (setf (further-tracking-maybe-required? spot) nil)))



;;; `Maybe-defer-refreshing-image-plane-1' is a subfunction of
;;; maybe-defer-refreshing-image-plane in DRAW.  Since that function may be
;;; called either in or out of a for-workstation context this assures a
;;; for-workstation is established calls maybe-defer-refreshing-image-plane-2.
;; - ben 2/23/93

(defun maybe-defer-refreshing-image-plane-1 (image-plane)
  (let ((workstation workstation-with-image-plane-being-refreshed))
    (unless (queue-empty-p (workstation-event-queue workstation))
      ;; do not poll -- in particular do not trigger a window reshape here;
      ;; also need CHEAP test
      (cond
	((and servicing-workstation?
	      (eq current-workstation workstation))
	 (maybe-defer-refreshing-image-plane-2 image-plane workstation))
	(t
	 (for-workstation (workstation)
	   (maybe-defer-refreshing-image-plane-2 image-plane workstation)))))))

;; Never used!!


;;; `Maybe-defer-refreshing-image-plane-2' looks ahead at the next event in the
;;; workstation's event Q and returns true if it's event-type is marked with
;;; `refreshes-image-plane-p' that in turn allows refreshing to be defered
;;; in preference to the presumably different refresh that event will trigger.
;; - ben 2/23/93

(defun maybe-defer-refreshing-image-plane-2 (image-plane workstation)
  (let* ((event (queue-peek (workstation-event-queue workstation)))
	 (event-interpretation?
	   (let ((current-workstation workstation))	; may be needed by the event interpreter.
	     (interpret-workstation-event event workstation)))
	 (refreshing?
	   (and event-interpretation?
		(event-handler-refreshes-image-plane-p event-interpretation?)
		(eq (image-plane-for-workstation-event? event)
		    image-plane))))
    (reclaim-event-interpretation event-interpretation?)
    (when refreshing?
      (setf (image-plane-to-continue-refreshing? workstation)
	    image-plane)
      t)))

;; Could better be done by event merging in the drawing queue?
;; Only caller of interpret-workstation-event!!



;;; `Continue-refreshing-image-plane' does the image-plane refresh that was put on
;;; hold by maybe-defer-refreshing-image-plane in DRAW.  It is called by
;;; service-workstation when the image-plane's refreshing can continue.
;; - ben 2/23/93

(defun continue-refreshing-image-plane (workstation)
  (invalidate-image-plane
    (shiftf (image-plane-to-continue-refreshing? workstation) nil)))







;;;; Workstation Primitives







;;; The grammar category `millisecond-sleep-interval' is used as the type for
;;; the slot milliseconds-to-sleep-when-idle.  This value can be NIL, which
;;; parses and prints as "use default", or it is an integer from 0 through 1000.

(add-grammar-rules
  `((millisecond-sleep-interval integer)
    (millisecond-sleep-interval ('use 'default) default)))

(def-slot-value-compiler millisecond-sleep-interval (parse-result)
  (cond ((eq parse-result 'default)
	 nil)
	((not (fixnump parse-result))
	 bad-phrase)
	((and (>=f parse-result 0)
	      (<=f parse-result 1000))
	 parse-result)
	(t
	 (values bad-phrase
		 (copy-text-string
		   "A millisecond sleep interval must be an integer from 0 through 1000.")))))

(def-slot-value-writer millisecond-sleep-interval (fixnum?)
  (if fixnum?
      (twrite fixnum?)
      (twrite-string "use default")))




;;; The grammar category `minimum-scheduling-interval?' is used as the type for
;;; a timing-parameters system-table value which controls the minimum interval
;;; between groups of scheduled tasks.  The printed representation is of a float
;;; number of seconds or the word continuous, but the internal representation is
;;; a fixnum number of milliseconds, or nil.  The value must be either evenly
;;; divide into 1000 milliseconds, or be a multiple of that.

(add-grammar-rules
  '((minimum-scheduling-interval? 'continuous)
    (minimum-scheduling-interval? positive-quantity-interval)))

(def-slot-value-writer minimum-scheduling-interval? (interval?)
  (cond ((null interval?)
	 (twrite-string "continuous"))
	((=f (modf-positive interval? 1000) 0)
	 (print-constant (floorf-positive interval? 1000) 'seconds))
	(t
	 (with-temporary-gensym-float-creation write-min-sched-interval
	   (print-constant
	     (/e (coerce-fixnum-to-gensym-float interval?) 1000.0)
	     'seconds)))))

(def-slot-value-compiler minimum-scheduling-interval? (parse-result)
  (cond 
    ((eq parse-result 'continuous)
     nil)
    ((and (consp parse-result)
	  (phrase-number-p (car-of-cons parse-result))
	  (eq (cdr-of-cons parse-result) 'seconds))
     (let ((interval (car-of-cons parse-result)))
       (cond
	 ((and (fixnump interval)
	       (<=f interval 0))
	  (values
	    bad-phrase
	    (copy-constant-wide-string #w"The interval must be greater than zero.")))
	 ((and (not (fixnump interval)) (not (phrase-float-p interval)))
	  bad-phrase)
	 (t
	  ; returns multiple-values.
	  (adjust-scheduling-interval interval)))))
    (t bad-phrase)))



;;; The function `adjust-scheduling-interval' takes an interval in fixnum or
;;; phrase float format and adjusts the interval to a fixnum count of
;;; milleseconds.  It returns either the adjusted interval or the multiple
;;; values bad-phrase and a copied text string.

;;; For subsecond intervals, the value is adjusted to a millisecond count
;;; equivalent to 1/n.  For values > 1, they are brought up to the next
;;; integer.

;;; This function is used grammar input for minimum scheduling intervals and
;;; minimum history intervals.

;; In the computation below we may be receiving values that have already been
;; through this rounding up to the nearest allowable limit.  Since our subsecond
;; interval rounding up can add up to 1 millisecond to the given value, subtract
;; off one millisecond from the given value before the computation.  This makes
;; this computation repeatable given a result from a previous execution, and it
;; is unlikely to severely affect users.  (Yes, I know that this is immoral, but
;; we're not storing the fixnum which is the fraction of a second to use, so we
;; have rounding troubles.  -jra 12/11/94)







(defun adjust-scheduling-interval (interval-in-seconds)
  (cond
    ((fixnump interval-in-seconds)
     (cond ((>f interval-in-seconds (ashf most-positive-fixnum -10))
	    (values
	      bad-phrase
	      (copy-text-string
		"The interval must be less than or equal to 6 days.")))
	   (t
	    (*f interval-in-seconds 1000))))
    (t
     (with-temporary-gensym-float-creation adjust-scheduling-interval
       (let ((given-value
	       (if (phrase-float-p interval-in-seconds)
		   (phrase-float-value interval-in-seconds)
		   (managed-float-value interval-in-seconds))))
	 (declare (type gensym-float given-value))
	 (cond ((>e given-value (coerce-fixnum-to-gensym-float
				  (ashf most-positive-fixnum -10)))
		(values
		  bad-phrase
		  (copy-text-string
		    "The interval must be less than or equal to 6 days.")))
	       ((>=e given-value 1.0)
		(*f (ceilinge-first given-value) 1000))
	       ((>e given-value 0.0)
		(cond ((<e given-value minimum-minimum-float-scheduling-interval)
		       ;; On signalling platforms the divide by 0 from (-e given-value
		       ;; 0.001), where given-value is 0.001, causes g2 to abort. This
		       ;; clause acts as a guard.
		       minimum-minimum-fixnum-scheduling-interval)
		      (t
		       (maxf minimum-minimum-fixnum-scheduling-interval
			     (ceilinge-first
			       (/e 1000.0
				   (ffloore-first
				     ;; assumed: minimum-minimum-... > 0.001
				     (/e 1.0 (-e given-value 0.001)))))))))
	       (t
		(values
		  bad-phrase
		  (copy-text-string
		    "The interval must be greater than 0.")))))))))

(defun-simple invert-adjusted-scheduling-interval (interval)
  (cond ((not (fixnump interval))
	 1)
	(t
	 (if (=f 0 (modf interval 1000))
	     (floorf interval 1000)
	     (allocate-managed-float
	       (*e 0.001 (coerce-fixnum-to-gensym-float interval)))))))



(defun-simple idle-time-when-polling ()
  (if  (milliseconds-to-sleep-when-idle timing-parameters)
       (milliseconds-to-sleep-when-idle timing-parameters)
       40))


;;;; Creating workstation events, G2 side.


;;; The function `absorb-local-event-ab-side' handles local-events orignating in
;;; G2.  Local-event remains owned by the caller.

(defun absorb-local-event-ab-side (event)
  (absorb-local-event-ab-side-1
    current-workstation
    (local-event-key-code event)
    (local-event-cursor-x event)
    (local-event-cursor-y event)
    (local-event-timestamp event)
    (copy-event-plist (local-event-plist event))))


;;; The function `absorb-local-event-ab-side-1', which runs only on the G2 side,
;;; handles local events from both TW and G2, converting them to workstation
;;; events. Note that it takes ownership of the event plist.

(defun absorb-local-event-ab-side-1 (workstation key-code x y timestamp plist)
  #+development
  (when trace-local-events
    (trace-local-event (pretty-type-of-gensym-window (window-for-workstation workstation))
		       key-code x y timestamp plist))
  (let* ((gensym-window (window-for-workstation workstation))
	 (window-handle? (getf plist 'window))
	 (native-window? (find-native-window gensym-window window-handle?))
	 (native-image-plane? (native-image-plane? native-window?))
	 (already-handled-p nil)
	 (pane? nil)
	 (image-plane? nil))
    (cond (native-window?
	   (when native-image-plane?
	     (setq image-plane? native-image-plane?
		   pane? (pane-for-image-plane native-image-plane?))
	     ;; This is a hack to keep the geometry of native TWAXL control windows
	     ;; in sync, since they don't get WM_MOVE events.  These properties
	     ;; are added by TW when running in TWAXL mode, by
	     ;; construct-local-event-plist -fmw, 1/20/04.

	     ;; Note that the window-refresh event, constructed in
	     ;; decode-native-control-event, uses properties x, y, width, height,
	     ;; so it doesn't fire here. -fmw, 7/12/04

	     (let ((left? (getf plist 'left))
		   (top? (getf plist 'top))
		   (width? (getf plist 'width))
		   (height? (getf plist 'height)))
	       (when (and left? top? width? height?)
		 (move-native-image-plane-to native-image-plane? left? top?)
		 (%set-native-window-size native-window? width? height?))))

	   ;; Convert from native-window client-area coordinates to G2 window
	   ;; coordinates, which is what all downstream processing expects.
	   (unless (control-event-uses-main-window-relative-coordinates-p
		     gensym-window key-code plist)
	     (incff x (native-window-left native-window?))
	     (incff y (native-window-top native-window?)))

	   ;; This was already done in poll-workstation or
	   ;; receive-telewindows-workstation-event-for-g2, but with the wrong
	   ;; values in this case.
	   (setf (x-in-window-of-mouse? workstation) x
		 (y-in-window-of-mouse? workstation) y)

	   ;; Handle some events now, instead of enqueuing them.
	   (when (handle-native-window-event native-window? key-code plist)
	     (setq already-handled-p t)))

	  (window-handle?
	   ;; Window handle but no native-window means event was on window background.
	   (setq pane? (detail-pane-for-workstation workstation)))

	  (t
	   (multiple-value-setq (pane? image-plane?)
	     (decode-window-position gensym-window x y))))
    (cond (already-handled-p
	   (reclaim-event-plist plist))
	  (t
	   (enqueue-workstation-event workstation key-code x y timestamp
				      gensym-window pane? image-plane?
				      plist)))))


;;; The function `control-event-uses-main-window-relative-coordinates-p' returns
;;; T if the x,y stored in an event from given telewindow with given key-code
;;; and plist are relative to the main G2 window, instead of the window
;;; specified in the plist.

(defun control-event-uses-main-window-relative-coordinates-p (gensym-window key-code plist)
  (declare (ignore gensym-window))
  (and (key-case key-code
	 ((tree-view html-view shortcut-bar logbook-view prop-grid)
	  t))
       (not (getf plist 'control-relative-coordinates))))

;; Normally, the x,y in an event is relative to the native window specified by
;; the WINDOW property in the plist, where a WINDOW of 0 or none means the main
;; G2-Window.

;; Unfortunately, almost all of the native controls violate this convention,
;; sending their events with main-window-relative coordinates, even though the
;; WINDOW property is present and specifies the control's window.  These are the
;; events sent via g2pvt_fire_control_event(), and those sent directly with
;; g2pvt_send_event, but with and hwnd of GHwndWnd.

;; To allow for fixing the coordinate system in the future, also check for a
;; random property in the event plist. -fmw, 3/16/06


;;;; Testing and Debugging WORKSTATION




;;; Describe-current-state ...

#+development
(defun describe-current-state (&optional (*print-length* nil))
  (let ((workstation
	  (cond
	    ((current-named-dynamic-extent-p 'for-workstation)
	     (format t "~&Context Stack of current-workstation: ")
	     current-workstation)
	    (t
	     (format t "~&Context Stack of system window's workstation: ")
	     (workstation-this-is-on system-window)))))
    (format t "~S" workstation)
    (loop for context in (workstation-context-stack workstation)
	as first-time? = t then nil
	do (if first-time?
	       (format t "~&    " )
	       (format t "~& <- "))
	   (format t "~(~a~)" (specific-structure-for-workstation-context context)))
    (values)))



;;;; Native Window Items

;; This stuff was never finished.

(def-class (g2-native-window (item entity) (foundation-class g2-native-window)
			     do-not-put-in-menus not-user-instantiable)
  ;; Internal slots.
  (native-window-structure nil vector-slot system)

  ;; User-visible slots.
  (native-window-left   0 (type read-only-integer) not-user-editable vector-slot no-accessor)
  (native-window-top    0 (type read-only-integer) not-user-editable vector-slot no-accessor)
  (native-window-width  0 (type read-only-positive-integer) not-user-editable vector-slot no-accessor)
  (native-window-height 0 (type read-only-positive-integer) not-user-editable vector-slot no-accessor)
  ;; TODO: x/y scroll position, range, enablement
  ;; TODO: icon, title, title-bar-buttons, system-menu
  ;; normal, minimized, maximized
  (native-window-state normal (type symbol) not-user-editable vector-slot no-accessor))

(def-class-method cleanup (g2-native-window)
  (funcall-superior-method g2-native-window)
  (let ((native-window? (native-window-structure g2-native-window)))
    (when native-window?
      (setf (native-window-structure g2-native-window) nil  ; Snap links
	    (native-window-item? native-window?) nil)
      ;; If native-window non-NIL, we know that we are not inside reclaiming the
      ;; native-window, so we need to propagate that here.
      (when (native-window-image-plane? native-window?)
	(delete-image-plane (native-window-image-plane? native-window?))))))

(defun delete-native-window-item (native-window)
  (let ((item? (native-window-item? native-window)))
    (when item?
      (setf (native-window-structure item?) nil	            ; Snap links
	    (native-window-item? native-window) nil)
      (unless (frame-being-deleted-p item?)
	(delete-frame item?)))))

(defun create-native-window-item (native-window)
  ;; Note these need to be permanent (like g2-window's) since they need to exist
  ;; even when G2 is stopped!
  (let ((item (make-permanent-item (native-window-item-class native-window))))
    (setf (native-window-structure item) native-window)
    item))

(defun ensure-native-window-item (native-window)
  (or (native-window-item? native-window)
      ;; FIXME: fsn?
      (prog1 (setf (native-window-item? native-window) (create-native-window-item native-window))
	(synchronize-native-window-item native-window))))

(defun native-window-item-class (native-window)
  (let ((class? (native-window-class native-window)))
    (or (and class? (classp class?) class?)
	'g2-native-window)))

;;; The function `synchronize-native-window-item' synchronizes the attributes of
;;; the KB-level item with the native-window. Always a copy from the
;;; native-window to the item (unidirectional). Representations of changed
;;; attributes will be updated.

(defun synchronize-native-window-item (native-window)
  (when (native-window-item? native-window)
    (let ((item? (native-window-item? native-window))
	  (do-not-note-permanent-changes-p t)) ; TODO: Not sure what this does. See
					; copy-gensym-window-attributes-into-g2-window
      (macrolet ((sync (item-slot structure-slot)
		   `(let ((value ,(if (symbolp structure-slot)
				      `(,structure-slot native-window)
				      structure-slot)))
		      (unless (eql (get-slot-value item? ',item-slot) value)
			(change-slot-value item? ',item-slot value)))))
	(sync native-window-left native-window-left)
	(sync native-window-top native-window-top)
	(sync native-window-width native-window-width)
	(sync native-window-height native-window-height)
	(sync native-window-state (or (native-window-state native-window) 'normal))))))

(defun g2-window-of-native-window-item? (native-window-item)
  (and (native-window-structure native-window-item)
       (native-window-gensym-window (native-window-structure native-window-item))
       (g2-window-for-gensym-window?
	 (native-window-gensym-window (native-window-structure native-window-item)))))

;; Nicer name than g2-window-of-g2-native-window
(def-virtual-attribute g2-window-of-view
    ((class g2-native-window)
     (or (no-item) (class g2-window))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-native-window)
	   ;; FIXME: serve-item-p ?
	   (g2-window-of-native-window-item? g2-native-window)))


;; Unused
(def-class (g2-native-view g2-native-window do-not-put-in-menus not-user-instantiable)
  ;; TODO: Attributes: document: item-or-value, etc.
  )

;; Unused
(def-class (g2-workspace-view g2-native-view (foundation-class g2-workspace-view)
			      do-not-put-in-menus not-user-instantiable)
  ;; TODO: Attributes: kb-workspace (= document). BUT: can't have item-valued
  ;; attributes.
  )

(defun image-plane-of-workspace-view? (g2-workspace-view)
  (and (workspace-view-p (native-window-structure g2-workspace-view))
       (native-window-image-plane? (native-window-structure g2-workspace-view))))

(defun workspace-of-workspace-view? (g2-workspace-view)
  (and (image-plane-of-workspace-view? g2-workspace-view)
       (workspace-on-image-plane? (image-plane-of-workspace-view? g2-workspace-view))))
  
(def-virtual-attribute workspace-of-view
    ((class g2-workspace-view)
     (or (no-item) (class kb-workspace))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-workspace-view)
	   ;; FIXME: serve-item-p ?
	   (workspace-of-workspace-view? g2-workspace-view)))

(def-virtual-attribute scale-of-view
    ((class g2-workspace-view)
     (or float (structure ((x-scale float)
			   (y-scale float))))
     nil)
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-workspace-view)
	   (let ((image-plane? (image-plane-of-workspace-view? g2-workspace-view)))
	     (cond ((null image-plane?)
		    (make-evaluation-float 1.0))
		   ((=f (image-x-scale image-plane?)
			(image-y-scale image-plane?))
		    (image-plane-x-scale-mf image-plane?))
		   (t
		    (allocate-evaluation-structure
		      (eval-list 'x-scale (image-plane-x-scale-mf image-plane?)
				 'y-scale (image-plane-y-scale-mf image-plane?))))))))


;;;; G2 Extensions

;; This section moved here from CONTROLS today. (MHD 8/8/94)
						

;;; A `G2 extension' is an object used to represent and control extension
;;; processes in G2.  The extension process can be designated in G2 in conclude
;;; actions to control opening and closing connections, and in show and hide
;;; actions to control where (which telewindow processes) things are displayed.

;;; The system defined subclasses of G2-extension are G2-window, GSI-extension,
;;; GFI-extension, GSPAN-extension, and G2-to-G2-extension.  Users can define
;;; subclasses of these but not of G2-extension itself.  Subclasses may be
;;; defined to add slots (which may hold display configuration information),
;;; to change the icon, or to change connection stubs.

(def-class (g2-extension object (foundation-class g2-extension)
			 define-predicate
			 not-user-instantiable
			 do-not-put-in-menus
			 not-solely-instantiable)
  (g2-user-name nil not-user-editable (type read-only-attribute) do-not-save) 
;  (g2-connection-request
;    (:funcall instantiate-variable g2-extension-parameter)
;    not-user-editable (type attribute))
  (g2-connection-status
    connection-closed not-user-editable (type read-only-attribute) do-not-save)
  (g2-routing-information
    nil not-user-editable (type read-only-attribute) do-not-save))

;; The slots of type attribute in g2-extension (such as g2-connection-status) have
;; similarities to both system and user slots and are a bit of a departure from
;; the strict dichotomy of system and user slots in the rest of the G2.  They are
;; similar to system slots in that they are not user editable and the slot values
;; are changed by g2 software only.  They are similar to user slots in that they
;; can be accessed by expressions in G2 (even though they can't be changed).
;; Currently, these slots must be lookup slots rather than vector slots because
;; the role servers for attributes only work with lookup slots.  Consider
;; improving this so that vector slots can also be served!  Also, currently, the
;; g2-connect-request slot must be saved.  The reason for this is that when the kb
;; is read, make-frame-without-computing-slot-initializations is called to make
;; the frame.  This only executes a :funcall initialization if the slot is a
;; vector slot.  Thus, the g2-extension-parameter is not instantiated.  For now,
;; the only solution is to save the slot.  This does not result in any functional
;; difference although it is a bit inefficient in that it saves something that
;; doesn't really need to be saved.  Consider improving
;; make-frame-without-computing-slot-initializations.

;; Note that it would be nice to make slots like g2-connection-status have more
;; specific names like connection-status-for-g2-extension?  and have an alias to
;; connection-status.  The problem with this is that datum-evaluate does not work
;; with aliases.  This is also a problem with system slots like scan-interval
;; which we want to allow rules to access.  The current proposal is to make new
;; role servers for these slots.  Making mappings from slot aliases to slots is
;; too inefficient at runtime and such mappings would not be unique in all cases.

;; G2-connection-request is an idea we are not pursuing now.  
;;
;; Note that the slot g2-connection-request has an absent slot putter.  And
;; note that the class g2-extension-parameter is obsolete.  The slot was
;; only present in some Beta copies of G2 2.0, so they may be considered
;; for reuse in 2.1 or later.  Note also that control-request-for-
;; g2-extension was an earlier name for this same slot, and that it also
;; has an absent slot putter. (MHD/AGH 3/22/90)
;;
;; Here is the slot's old documentation:
;; 
;; The control-request-for-g2-extension slot is a user slot initialized to
;; contain a g2-extension-parameter (a kind of symbolic-parameter).  The value of
;; the parameter can be changed by conclude actions in order to try to open and
;; close connections to extension processes.  Valid values include try-to-connect
;; and close connection.  If the parameter is set to an invalid value, a warning
;; is posted and the value is reset to the default 'none.  The
;; connection-status-for-g2-extension?  slot is a system slot that can have
;; values 'connected or 'connection-closed.  The slot
;; routing-information-for-g2-extension?  is also a system slot and contains
;; network protocol, host name, and process id.
;;
;;
;; The class g2-extension-parameter is also now obsolete, as noted above.  See
;; above note.
;; 
;; (def-class (g2-extension-parameter symbolic-parameter 
;;                                    define-predicate system-internal)
;;   (initial-value-of-variable-or-parameter none)
;;   )
;;
;;
;; ;; The system-internal class feature keeps this from being instantiable
;; ;; via the new-object menu option.  It does still show up with inspect
;; ;; and on the class hierarchy trees.  Several other system classes
;; ;; (arrow buttons for example) currently have this problem as well.

;; The following implements the phase-out of slots and classes, as described
;; above:

(def-absent-slot-putter control-request-for-g2-extension (frame value)
  (declare (ignore frame))
  (delete-frame value))				; a g2-extension-parameter

(def-absent-slot-putter g2-connection-request (frame value)
  (declare (ignore frame))
  (delete-frame value))				; a g2-extension-parameter


(def-substitute-for-old-class
  g2-extension-parameter symbolic-parameter)	; g2-extension-parameter had 
						;   no new slots


(def-slot-putter g2-connection-status 
    (g2-extension value initializing-p)
  (setf (g2-connection-status g2-extension) value)
  (unless initializing-p
    (update-subscriptions-from-virtual-attribute-change
      g2-extension (virtual-attribute 'ui-client-connection-status) nil))
  value)


;;; A g2-window ...

;;; The relations between g2-windows, workstations, and gensym-windows are
;;; shown in the diagram below.  The pointers are traversed when logging in
;;; and out in order to properly initialize all the structures.  See also
;;; documentation in TELEWINDOWS.

                                    
;;;                                 ----> g2-window ---
;;; g2-window-for-this-workstation? |                 |
;;;                                 |                 | workstation-for-g2-window?
;;;                                 ---               |
;;;                               ----> workstation <--
;;;                               |                 ---
;;;                               |                   |
;;;        workstation-this-is-on |                   | window-for-workstation
;;;                               |                   |
;;;                               --- gensym-window <--

;;; Note that the icp ports for the gensym-window are not shown in this diagram.
;;; These are kept in the slots icp-output-port-for-window? and
;;; icp-output-port-to-master-for-window? of the gensym-window structure.


(def-class (g2-window (g2-extension ui-client-item)
		      (foundation-class g2-window)
		      (stubs (nil network-wire nil bottom 30))
		      define-predicate)

  ;; Note that the following two slots are overridden in SYSICONS. (MHD 2/20/95)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 55 ((outline (5 0) (55 0) (55 40) (5 40))
	     (outline (40 5) (arc (47 8)) (50 15)
		      (50 25) (arc (47 32)) (40 35)
		      (20 35) (arc (13 32)) (10 25)
		      (10 15) (arc (13 8)) (20 5))
	     (outline (5 42) (55 42) (60 55) (0 55)))))

  (workstation-for-g2-window?			; not connected <=> not 
    nil vector-slot system)			;   logged in <=> nil
  (g2-user-mode					; had (type attribute) and
    nil (type g2-user-mode-for-login)		;   and not-user-editable until
    do-not-save)				;   today. (MHD/BAH 4/23/92)

  

  (g2-window-style			; nil (default), g2-5.x, standard, standard-large
    nil (type g2-window-style-override)
    do-not-save)			; do-not-save - like all the other slots here (?)

  (specific-language-for-this-g2-window? ; value comes from TW/G2 command 
					;   line or via login panel
    nil (type language?) do-not-save)

  
  (g2-window-management-type			; a symbolic variable: LOCAL or REMOTE
    nil not-user-editable (type read-only-attribute) do-not-save)

  ;; New slots in 7.1
  (g2-window-x 0 (type read-only-integer) not-user-editable)
  (g2-window-y 0 (type read-only-integer) not-user-editable)
  ;; New slots in 4.0
  (g2-window-width 0 (type read-only-positive-integer) not-user-editable)
  (g2-window-height 0 (type read-only-positive-integer) not-user-editable)

  (g2-window-x-resolution 75 (type read-only-positive-integer) not-user-editable) ; in DPI.
  (g2-window-y-resolution 75 (type read-only-positive-integer) not-user-editable)
  
  (g2-window-network-host-name?
    nil not-user-editable (type read-only-attribute) do-not-save)
  (g2-window-os-user-name?
    nil not-user-editable (type read-only-attribute) do-not-save)
  (g2-window-time-of-last-connection?
    nil not-user-editable (type unix-time?) do-not-save)
  (g2-window-initial-window-configuration-string?
    nil not-user-editable (type read-only-attribute) do-not-save)

  (g2-window-reroute-problem-report?
    nil not-user-editable (type read-only-attribute) do-not-save)

  (g2-window-os-type?
    nil not-user-editable (type read-only-attribute) do-not-save)
  (show-operator-logbook-in-this-window?
    t (type yes-or-no) lookup-slot system)

  (g2-window-user-is-valid
    #.falsity not-user-editable (type truth-value read-only-attribute) do-not-save)
  (g2-window-mode-is-valid
    #.falsity not-user-editable (type truth-value read-only-attribute) do-not-save))


;;; The substitute-for-old-class `workspace-view'. It is possible in 7.0 or 7.1
;;; to save KBs containing workspace-view instances, although it requires a
;;; deliberate effort on the user's part to do so. In any case, convert them to
;;; g2-windows. If in 8.0 we define a new workspace-view class that is saveable,
;;; then we will need to bump the save kb-flags to 275 so that this substitution
;;; does not apply to 8.0 KBs. -fmw, 11/7/03

(def-substitute-for-old-class workspace-view g2-window 275)

;; Since 275 is currently beyond the save kb-flags, the substitution will always
;; happen until we bump them.


(def-slot-value-compiler g2-window-style-override (parse-result)
  (if (eq parse-result 'default) nil parse-result))

(def-slot-value-writer g2-window-style-override (value)
  (twrite-symbol (or value 'default)))




(defun g2-window-user-is-valid-function (g2-window)  ; for forward reference
  (g2-window-user-is-valid g2-window))               ; in sequences2
(defun g2-window-mode-is-valid-function (g2-window)
  (g2-window-mode-is-valid g2-window))
(defun workstation-for-g2-window?-function (g2-window)
  (workstation-for-g2-window? g2-window))


(def-slot-putter g2-user-mode
    (g2-window value initializing-p)
  (setf (g2-user-mode g2-window) value)
  (unless initializing-p
    (update-subscriptions-from-virtual-attribute-change
      g2-window
      (virtual-attribute 'ui-client-user-mode)
      nil))
  value) 

;; A little facility for showing/hiding logbook:

;;; When a user changes the `show-operator-logbook-in-this-window?' slot of a
;;; G2 window, it should immediately show or hide the logbook in that window.
;;; This also puts the window in such a state that new pages are shown or not
;;; shown as per this parameter.

(def-slot-putter show-operator-logbook-in-this-window?
    (g2-window value initializing?)
  (let ((old-value (show-operator-logbook-in-this-window? g2-window)))
    (prog1 (setf (show-operator-logbook-in-this-window? g2-window) value)
      (unless initializing?		; not loading, cloning, creating, etc.
	(when (not (eq old-value value))
	  (cond
	    (value
	     (show-logbook-in-g2-window g2-window))
	    (t
	     (hide-logbook-in-g2-window g2-window))))))))
  
  
  

(def-slot-value-writer unix-time? (unix-time?)
  (if unix-time?
      (twrite-unix-time unix-time?)
      (tformat "none")))

(define-category-evaluator-interface (unix-time?
				       :access read)
    (or (no-item)
	(structure
	  unix-time
	  ((second number)
	   (minute number)
	   (hour number)
	   (date number)
	   (month number)
	   (year number))
	  (and hour minute second month date year)))
  ((get-form (slot-value))
   (if slot-value
       (with-temporary-gensym-float-creation twrite-unix-time
	 (let ((gensym-float-unix-time (managed-float-value slot-value)))
	   (cond ((or (<e gensym-float-unix-time -2.147483648e9) ; signed 32-bit long bounds
		      (>=e gensym-float-unix-time 2-to-31-plus-62-years))
		  (values bad-phrase
			  (twith-output-to-text-string
			    (twrite-string "<time stamp out of bounds>"))))
		 (t
		  (with-new-structure (unix-time)
		    (multiple-value-setf
		      (second minute hour date month year)
		      (gensym-decode-unix-time gensym-float-unix-time)))))))
       'none)))

; same alias as for g2-login
(define-slot-alias g2-window-specific-language specific-language-for-this-g2-window?
  g2-window)

(define-slot-alias g2-window-remote-host-name g2-window-network-host-name? g2-window)

(define-slot-alias g2-window-user-name-in-operating-system g2-window-os-user-name?
  g2-window)

(define-slot-alias g2-window-operating-system-type g2-window-os-type?
  g2-window)

(define-slot-alias g2-window-time-of-last-connection g2-window-time-of-last-connection?
  g2-window)

(define-slot-alias g2-window-initial-window-configuration-string g2-window-initial-window-configuration-string?
  g2-window)

(define-slot-alias g2-window-reroute-problem-report g2-window-reroute-problem-report?
  g2-window)



;;; The category `language?' is similar to the grammar current-language, but it
;;; is used for the slot in g2-window that overrides the (global) language
;;; setting in language-parameters.  Unlike current-language, the symbol NONE
;;; gets parsed as NIL, and the the symbol that is the same as default-language
;;; does not get parsed as nil.

(add-grammar-rules
  '((language? 'none)
    (language? language)))

(define-category-evaluator-interface (unreserved-symbol
				       :access read-write)
    symbol
  ((set-form (evaluation-value))
   (cond ((reserved-word-p evaluation-value)
	  (values bad-phrase
		  (twith-output-to-text-string
		    (tformat  " ~s is a reserved-symbol" evaluation-value))))
	 (t evaluation-value)))
  ((get-form (slot-value))
   slot-value))
       
(define-category-evaluator-interface (language?
				       :access read-write)
    (or (no-item)
	(named unreserved-symbol))
  ((set-form (evaluation-value))
   (call-category-setter 'unreserved-symbol evaluation-value nil nil nil))
  ((get-form (slot-value))
   slot-value))


(def-slot-value-compiler language? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-writer language? (language?)
  (twrite (or language? 'none)))

(def-slot-putter specific-language-for-this-g2-window? (g2-window language?
								  initializing-p)
  (add-or-delete-as-language-contributor
    g2-window (specific-language-for-this-g2-window? g2-window) t)
  (add-or-delete-as-language-contributor
    g2-window language? nil)
  (let ((changed (neq (specific-language-for-this-g2-window? g2-window) language?)))
    (setf (specific-language-for-this-g2-window? g2-window)
	  language?)
    (unless initializing-p
      (let ((workstation-for-g2-window? (workstation-for-g2-window? g2-window)))
	(when workstation-for-g2-window?
	  (setf (specific-language-for-this-workstation? workstation-for-g2-window?)
		language?)
	  (when changed
	    (decache-dynamic-menus 'language workstation-for-g2-window?))))
      (update-subscriptions-from-virtual-attribute-change
	g2-window
	(virtual-attribute 'ui-client-specific-language)
	nil)))
  language?)

(def-slot-putter g2-window-style (g2-window value initializing-p)
  (setf (g2-window-style g2-window) value)
  (unless initializing-p
    (let ((workstation-for-g2-window? (workstation-for-g2-window? g2-window)))
      (when workstation-for-g2-window?
	(setf (style-specifically-for-this-workstation? workstation-for-g2-window?)
	      value))))
  value)

  


(def-class (network-wire connection (foundation-class network-wire))
  (cross-section-pattern
    ((foreground . 3)) system save))





;; Add definitions for GSI, GSPAN, and remote G2 extension processes!






(defun get-i-am-alive-info-for-g2-window-if-any (g2-window)
  (let ((icp-socket? (get-icp-socket-for-g2-window g2-window)))
    (when icp-socket?
      (I-am-alive-info? icp-socket?))))



(defun get-icp-socket-for-g2-window (g2-window)
  (let* ((workstation? (workstation-for-g2-window? g2-window))
	 (icp-output-port?
	   (when workstation?
	     (icp-output-port-for-window?
	       (window-for-workstation workstation?)))))
    (when icp-output-port?
      (parent-icp-socket icp-output-port?))))



(defun get-gensym-window-for-g2-window (g2-window)
  (let* ((workstation? (workstation-for-g2-window? g2-window)))
    (when workstation?
      (window-for-workstation workstation?))))



(defun get-g2-window-given-icp-socket (icp-socket)
  (loop for g2-window being each class-instance of 'g2-window
	do (when (eq icp-socket
		     (get-icp-socket-for-g2-window g2-window))
	     (return g2-window))))



(defun-simple print-schedule-to-string (current-only-p)
  (twith-output-to-text-string
    (loop with lines = (print-schedule-to-string-list current-only-p)
	  for line in lines do
      (tformat "~A~%" line)
      (reclaim-text-string line)
	  finally (reclaim-gensym-list lines))))

(defun-simple print-schedule-to-file (file-name current-only-p)
  (let ((stream (g2-stream-open-for-output file-name)))
    (when stream
      (let ((lines (print-schedule-to-string-list current-only-p)))
	(loop for line in lines
	      while (write-text-string-to-stream line stream)
	      while (g2-stream-terpri stream))
	(loop for line in lines do (reclaim-text-string line))
	(reclaim-gensym-list lines))
      (g2-stream-close stream))))

(defun-simple print-schedule ()
  (let ((lines (print-schedule-to-string-list nil)))
    (loop for line in lines
	  do (notify-user-at-console "~A~%" line))
    (loop for line in lines do (reclaim-text-string line))
    (reclaim-gensym-list lines)))

(defun print-schedule-on-temporary-workspace (current-only-p)
  (let ((box (make-description-box (print-schedule-to-string current-only-p))))
    (put-workspace-on-pane
      (make-workspace 'temporary-workspace nil box 50 nil nil)
      current-workstation-detail-pane 'left 'top t)))

(defun-for-system-procedure g2-show-schedule
    (g2-window-or-file-name current-only-p)
  (cond ((evaluation-text-p g2-window-or-file-name)
	 (print-schedule-to-file (evaluation-text-value g2-window-or-file-name)
				 (evaluation-truth-value-is-true-p
				   current-only-p))
	 (reclaim-evaluation-text g2-window-or-file-name))
	((of-class-p g2-window-or-file-name 'g2-window)
	 (for-workstation ((workstation-for-g2-window? g2-window-or-file-name))
	   (print-schedule-on-temporary-workspace
	     (evaluation-truth-value-is-true-p current-only-p)))))
  (reclaim-evaluation-truth-value current-only-p))


;;;; Aborting

(defun-for-system-procedure g2-do-abort-workspace ()
  (internal-error-given-format-info
    gensym-error-format-string
    gensym-error-argument-list
    gensym-error-sure-of-format-info-p))


(defun-for-system-procedure g2-cause-synchronous-abort ()
  (error "Called the wrong system procedure"))

;;; The variable intentionally-bogus-vector-for-g2-cause-asynchronous-abort is
;;; initialize to nil, and never altered.  It's sole purpose is to be supplied
;;; as the arg to svref to cause an abort in the system procedure
;;; g2-cause-asynchronous-abort. We must supply such a variable instead of nil
;;; because some clever compilers will do constant folding, and thus abort at
;;; compile time, which is a bit too soon.

(defvar intentionally-bogus-vector-for-g2-cause-asynchronous-abort nil)

(defun-for-system-procedure g2-cause-asynchronous-abort ()
  (svref intentionally-bogus-vector-for-g2-cause-asynchronous-abort 14))

;; The Lucid compiler with optimize settings of speed 3, safety 0, compilation
;; speed 0, was found to have the constant folding problem alluded to
;; above. (MHD 5/31/01)




;;;; Telewindows 2

;;; ui-client-session is the Telewindows II equivalent
;;; of a g2-window

;;; represents an end-user session in Telewindows II
;;; These need to be made in very special ways, so do not call
;;; make-frame on this class. Instead, choose from the
;;; make-ui-client-session-* selection available below
(def-class (ui-client-session (object ui-client-item)
			      do-not-put-in-menus
			      not-user-instantiable
			      not-normally-transient
			      define-predicate)
  ;; use virtual attribute ui-client-user-mode to change this.
  ;; NEVER use change-slot-value on this slot directly on it
  ;; because of the complex constraints its legal values.
  (ui-client-session-user-mode nil (type g2-user-mode-for-login)
			       vector-slot system
			       do-not-save)
  (ui-client-session-user-name nil (type symbol)
			       not-user-editable
			       vector-slot system do-not-save)
  (ui-client-session-os-user-name? nil (type read-only-attribute)
				   not-user-editable
				   vector-slot system do-not-save)
  (ui-client-session-encoded-password nil (type user-password)
				      not-user-editable
				      do-not-put-in-attribute-tables
				      vector-slot do-not-save)
  (specific-language-for-this-ui-client-session? ; value comes from T2
    ;; This is not (yet) user-editable because a whole coordinating design
    ;; has to be worked out.
    nil not-user-editable (type language?) do-not-save)
  (ui-client-session-time-of-last-connection
     nil not-user-editable (type unix-time?) do-not-save)
  (ui-client-session-network-host-name? nil (type read-only-whole-string?)
			       not-user-editable
			       vector-slot do-not-save)
  (ui-client-session-os-type? nil (type symbol read-only-attribute)
			      not-user-editable
			      vector-slot do-not-save)
  (ui-client-session-parent-interface nil vector-slot system)
  (ui-client-session-workspaces nil vector-slot system)

  (ui-client-session-license-level?
    -2    ; i.e. unauthorized
    vector-slot system)

  ;; the following two slots are the same name as the equivalent slots
  ;; in g2-window.
  (ui-client-session-user-is-valid #.falsity not-user-editable
				   (type truth-value read-only-attribute)
				   do-not-save)
  (ui-client-session-mode-is-valid #.falsity not-user-editable
				   (type truth-value read-only-attribute)
				   do-not-save)
  (ui-client-session-status nil (type symbol)
			    not-user-editable
			    do-not-put-in-attribute-tables
			    vector-slot system do-not-save)
  (ui-client-session-nonce nil (type read-only-whole-string?)
			   not-user-editable
			   do-not-put-in-attribute-tables
			   vector-slot system do-not-save)
  (ui-client-session-field-edit nil 
				not-user-editable
				do-not-put-in-attribute-tables
				vector-slot system do-not-save))

(def-system-variable current-ui-client-session workstation nil)

(def-slot-putter ui-client-session-user-mode
    (ui-client-session value initializing-p)
  (setf (ui-client-session-user-mode ui-client-session) value)
  (unless initializing-p
    (update-subscriptions-from-virtual-attribute-change
      ui-client-session
      (virtual-attribute 'ui-client-user-mode)
      nil))
  value)

(def-slot-putter specific-language-for-this-ui-client-session?
    (ui-client-session value initializing-p)
  (setf (specific-language-for-this-ui-client-session? ui-client-session) value)
  (unless initializing-p
    (update-subscriptions-from-virtual-attribute-change
      ui-client-session
      (virtual-attribute 'ui-client-specific-language)
      nil)))

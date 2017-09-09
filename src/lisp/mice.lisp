;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module MICE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, and Ben Hyde





;;;; Introduction




;;; This module contains the frame system independent portions of the
;;; event handling.  This module is part of G2, but not Telewindows.

;;; It implements the native window heartbeat task.

;;; It contains mechinism to raise the semantic level of events by
;;; computing what the mouse is pointing at, these are known as mouse pointers.
;;; It contains mechnism for simple lexical analysis of the event stream.
;;; Finally event handling takes place inside of a dynamic extent that
;;; identifies the current workstation, this is known as a for workstation
;;; context and is implemented here.  It contains a complex mechinism for
;;; managing modes in the event handling, aka workstation contexts.







;;;; Forward References


(declare-forward-reference detail-pane                     function panes)
(declare-forward-reference push-last-spot                  function workstation)
(declare-forward-reference synchronize-selection-style     function workstation)
(declare-forward-reference set-session-info-in-workstation function)
(declare-forward-reference get-workstation-g2-window-style-in-force function)
(declare-forward-reference valid-workstation-context-p-function function)
(declare-forward-reference get-value-for-current-workstation-new-g2-classic-ui-p function)
(declare-forward-reference show-selection-handles-p function workstation)




;;;; Workstation Context Frames and Primary Methods



;;; `Workstation-context-frame' is the superior type of all
;;; workstation structures.  It's one slot
;;; `mouse-pointers-of-workstation-context' is used to hold the mouse pointers
;;; which guard the context, if any of these become invalid the context should
;;; be aborted.  See `register-mouse-pointer-in-workstation-context' for
;;; details.

;;; All workstation contexts have this method: clean-up-workstation-context.

(def-structure workstation-context-frame
  (mouse-pointers-of-workstation-context nil :reclaimer release-mouse-pointers)
  (frame-reference-number-of-workstation-context (copy-of-current-frame-serial-number-function)
						 :reclaimer reclaim-frame-serial-number))



;;; `Clean-up-workstation-context' is a structure method define on all subtypes
;;; of workstation-context-frame.  Is called when ever a workstation context is
;;; removed from the workstation context stack, either by aborting or by
;;; returning.  It must call it's superior method as it's last act.

(def-generic-structure-method clean-up-workstation-context (workstation-context-frame))



;;; See also valid-workstation-context-p in the module workstations.



;;; `Setup-workstation-context' is a structure method defined on
;;; workstation-context-frame.  It is invoked when the
;;; context is first placed upon the workstation context stack and
;;; provides an oportunity to fire up the thing.

(def-generic-structure-method setup-workstation-context (workstation-context-frame))



;;; `Suspend-workstation-context' is a structure method defined on
;;; workstation-context-frame.  It is invoked when
;;; ever another workstation context becomes current pushing this
;;; one deeper into the stack.  See WORKSTATIONS for more details.

(def-generic-structure-method suspend-workstation-context (workstation-context-frame))



;;; `Resume-workstation-context' is a structure method defined on
;;; workstation-context-frame. It is invoked when the current
;;; workstation context exits and this workstation context becomes current.

(def-generic-structure-method resume-workstation-context (workstation-context-frame))


;;; `valid-block-in-workstation-context-p' is used as a short hand for checking that
;;; a block has not been reprocessed since the time when the workstation context
;;; was created.  See valid-workstation-context for additional discussion.

(defmacro valid-block-in-workstation-context-p (block workstation-context-specifics)
  `(frame-has-not-been-reprocessed-p
     ,block
     (frame-reference-number-of-workstation-context ,workstation-context-specifics)))






;;;; Mouse Pointers

;;; Mouse pointers are used only within the user interface microtask
;;; implemented by service workstation.  Mouse pointers provide
;;; a rich description of locations on the user's window.
;;; Information about the location is computed by tracking down
;;; the mouse pointer.  The most interesting part of this is the
;;; `stack-of-spots.'

;;; Mouse pointers are usually the direct consequence of attempting to give
;;; workstation-events some semantic context.  Information from the original
;;; event is moved into the mouse pointer and it's substructure.
;;; `{x,y}-of-mouse-pointer' records the window position described by the
;;; mouse-pointer.  `Workstation-for-mouse-pointer' provides a backpointer to
;;; the workstation in question, and hence to the gensym-window, and g2-window.
;;; `Fixnum-time-of-mouse-pointer' is the fixnum time at the creation of the
;;; mouse-pointer, or the event from which the mouse pointer derived.
;;; `Key-code-of-mouse-pointer' is a key-code (see keyboards) taken from the
;;; original event, or defaulting to a Non-Event.

;;; `x-in-workspace-of-selection-focus?' and
;;; `y-in-workspace-of-selection-focus?' are bound when the selection-style has
;;; focused on a particular object.  See `x-in-workspace-of-selection-focus' for
;;; additional information.  `Block-of-selection-focus?' is bound analagously.

;;; A process known as `tracking a mouse-pointer' creates a stack of spots
;;; that record exactly what the mouse is pointing at. This is stored into
;;; the `stack-of-spots' slot.  This describes what elements of the user's
;;; document are represented under the mouse.  During the life cycle of a
;;; mouse pointer some of these elements can be deleted.  Mouse pointers
;;; are automaticly revalidated when ever a service workstation context
;;; is entered.  Frame serial numbers in the individual spots drive that
;;; validation.  An invalid mouse-pointer is marked as such in the
;;; `contains-invalid-spots' slot.  That in turn should trigger the aborting
;;; of UI processing that depends on that mouse pointer.

;;; Memory management is done with a reference count scheme.  The mouse-pointer
;;; of the current, latest, and last mouse down, are allow retained by the
;;; workstation.  UI processing that wants to retain additional pointers, (i.e.
;;; to recall the original position the user clicked prior to long interaction
;;; resulting a new object) should `reference', and `release' that pointer (see
;;; below).

(def-structure (mouse-pointer
		 (:constructor make-mouse-pointer
			       (workstation-for-mouse-pointer
				 key-code-of-mouse-pointer
				 fixnum-time-of-mouse-pointer
				 x-of-mouse-pointer y-of-mouse-pointer))
		 (:print-function print-mouse-pointer))
  workstation-for-mouse-pointer
  x-of-mouse-pointer
  y-of-mouse-pointer
  (reference-count-of-mouse-pointer 1)
  (stack-of-spots nil :reclaimer reclaim-structure)
  (contains-invalid-spots nil)
  fixnum-time-of-mouse-pointer
  key-code-of-mouse-pointer

  (x-in-workspace-of-selection-focus? nil)
  (y-in-workspace-of-selection-focus? nil)
  (block-of-selection-focus? nil)
  (kind-of-mouse-pointer nil))		; NIL, SYNTHETIC, or MULTI.


#+development
(defun print-mouse-pointer (mouse-pointer stream depth)
  (declare (ignore depth))
  (printing-random-object (mouse-pointer stream)
    (let ((stack-of-spots? (stack-of-spots mouse-pointer)))
      (format stream "MP~a ~a ~(~s~) ~d,~d"
	      (if (mouse-pointer-is-synthetic-p mouse-pointer) "*" "")
	      (key-name (key-code-of-mouse-pointer mouse-pointer))
	      (if stack-of-spots?
		  (name-of-type-description
		    (type-description-of
		      stack-of-spots?))
		  "empty")
	      (x-of-mouse-pointer mouse-pointer)
	      (y-of-mouse-pointer mouse-pointer)))))

;;; The function `mouse-pointer-is-multi-p' returns T iff the mouse-pointer
;;; "points" to multiple items (part of a multiple selection in the selection
;;; UI).

(defun mouse-pointer-is-multi-p (mouse-pointer)
  (eq (kind-of-mouse-pointer mouse-pointer) 'multi))

(defun mouse-pointer-is-synthetic-p (mouse-pointer)
  (not (null (kind-of-mouse-pointer mouse-pointer))))


;;; `Reference-mouse-pointer' increments the reference coutner
;;; of a mouse pointer.  The deamon that reclaims old mouse
;;; pointers will not reclaim any mouse pointer with a
;;; a non-zero reference count.

(defun-simple reference-mouse-pointer (mouse-pointer)
  #+development
  (unless (symbolp (svref mouse-pointer 0))
    (cerror "continue" "found reclaimed mouse-pointer"))
  (incff (reference-count-of-mouse-pointer mouse-pointer))
  mouse-pointer)


;;; `Release-mouse-pointer-if-any' will decrement the reference
;;; count of a mouse-pointer.  Note this maybe passed NIL, making
;;; it useful as the reclaimer for a slot.

(defun-void release-mouse-pointer-if-any (mouse-pointer?)
  (when mouse-pointer?
    #+development
    (unless (symbolp (svref mouse-pointer? 0))
      (cerror "continue" "found reclaimed mouse-pointer"))
    #+development
    (when (=f 0 (reference-count-of-mouse-pointer mouse-pointer?))
      (error "Attempt to release a mouse pointer that has a zero reference count."))
    (decff (reference-count-of-mouse-pointer mouse-pointer?))))

;;; `Release-mouse-pointers' takes a gensym list of mouse-pointers
;;; releases each of them and reclaims the list.

(defun-void release-mouse-pointers (mouse-pointers)
  (loop for mouse-pointer in mouse-pointers
	do (release-mouse-pointer-if-any mouse-pointer))
  (reclaim-gensym-list mouse-pointers))







;;;; Selection Style


;;; `Selection-style' enumerates the modes that lexical analysis of the
;;; event stream runs in.  Each worksation context has a selection-style.
;;; A workstation can be said to be in a selection-style of it's current
;;; workstation context.

;;; The term selection-style it taken from the term `secondary selection'
;;; a mode in a spread sheet where dragging over the worksheet enter's
;;; a range formula into the current dialog.  In G2 we do an analagous
;;; thing where dragging over text inserts into the current editor.

;;; Transitions to between various selection styles can turn mouse tracking on
;;; and off.  The spot generation process, i.e.what information is poured into
;;; the event's mouse pointers, is deeply effected by the selection-style.

;;; The selection style is a symbol of the form <name>-is-selection-style.
;;; These are discussed below.

;;; See `synchronize-selection-style' for details on how the selection style
;;; is kept synchronized.

(def-concept selection-style)


;;; `Selection-focus' is one behavior that a selection style, may or
;;; may not exhibit.   See `x-in-workspace-for-selection-focus' for
;;; additional details.

(def-concept selection-focus)



;;; `Workstation-context-with-selection-focus' is included in the
;;; workstation-context state of those who's selection-style
;;; include selection-focus behavior.

(def-structure (workstation-context-with-selection-focus
		 (:include workstation-context-frame))
  block-with-selection-focus-of-workstation-context
  image-plane-with-selection-focus-of-workstation-context
  reference-number-of-image-plane)


;;; `Unknown-is-selection-style' is the initial value for the selection style of
;;; a workspace, a fact that is implemented in the curious manner that the code
;;; that pushs the first workstation context arranges that.

(def-concept unknown-is-selection-style)


;;; `Top-level-is-selection-style' is used for most of the modeless workstation
;;; contexts.  In this state the mouse tracking is disabled, and the spots
;;; generated are those useful to the default modeless state.

(def-concept top-level-is-selection-style)



;;; `Editing-and-top-level-is-selection-style' causes spot generation
;;; to behave as if for top level, and in addition to do mouse tracking
;;; into text sufficent to allow the secondary selection of from the
;;; editor.

(def-concept editing-and-top-level-is-selection-style)




;;; `Mouse-tracking' is a boolean mode of the workstation indicating that
;;; mouse-motion events are desired.

;;; Sadly the term mouse-tracking is overloaded.  It is also used to name the
;;; process of giving a mouse-pointer a filled in spot-stack.  See
;;; `track-mouse-into-spot' for that meaning.

;;; It is recorded in the workstation's mouse-tracking? variable.  When the
;;; mouse-tracking is is enabled the event stream may contain mouse-motion
;;; events.

;;; Most of the cascade of Q's holding events (OS, Local Event Queue, ICP
;;; Message Q, Window Event Q) and the code that handles participate when this
;;; is toggled on and off.  And effort is made to clean all Mouse-motion events
;;; from the queues when tracking is off.

;;; Adjacent mouse-motion events are merged in all of the queues possible, the
;;; resulting smoothing would not be desirable in a painting program, but we
;;; aren't currently a painting program.

;;; Mouse motion events can occur where the mouse has not actually moved from
;;; the location reported in the previously event.

;;; Adjacent mouse motion events can occur with identical locations and
;;; event times.

;;; Poll-workstation, on the native window side, will generate a synthetic
;;; mouse-motion event if it is called and no events are pending AND it has been
;;; at least 100 milliseconds since the last synthetic mouse motion was
;;; generated.  This allows assures that auto repeat behaviors can be driven
;;; from and in synch with the user's event queue.

;;; The 100 millisecond delay in synthetic mouse motions are triggered by the
;;; boolean consider-synthetic-motion-event? in the workstation.  This is set by
;;; one mechinism in TW and another in G2.  In TW the idle process call sets it
;;; upon return (see idle-telewindows).  In G2 the native-window-heartbeat sets
;;; it.  The rate of these processes is set via native-window-idle-interval, and
;;; is shorted when the mouse-tracking is enabled.

(def-concept mouse-tracking)
(def-concept mouse-motion)


;;; `Top-level-with-mouse-tracking-is-selection-style' causes no
;;; variation in spot generation but it does cause cause mouse
;;; tracking to be done.

(def-concept top-level-with-mouse-tracking-is-selection-style)

;;; `top-level-with-selection-focus-is-selection-style' has
;;; mouse tracking behavior and selection focus behavior.

(def-concept top-level-with-selection-focus-is-selection-style)
(def-concept top-level-with-selection-focus-but-no-mouse-tracking-is-selection-style)


;;; `Def-selection-style-of-workstaton-context' is used at compile time to
;;; declare for each workstation context it's selection style.

(defmacro def-selection-style-of-workstaton-context
    (workstation-context-type selection-style)
  (unless (memq
	    selection-style
	    '(top-level-is-selection-style
	      editing-and-top-level-is-selection-style
	      top-level-with-mouse-tracking-is-selection-style
	      top-level-with-selection-focus-is-selection-style
	      top-level-with-selection-focus-but-no-mouse-tracking-is-selection-style))
    (warn "Unknown selection-style ~S." selection-style))
  `(setf (selection-style-of-workstation-context-type
	   ',workstation-context-type)
	 ',selection-style))

;;; `Selection-style-of-workstation-context-type' holds the declared
;;; selection style.  See selection-style-of-workstation-context.

(def-global-property-name selection-style-of-workstation-context-type)



;;; `Selection-style-of-workstation-context' is used at runtime to
;;; fetch the style.  This is used only by the code that maintains
;;; the workstations current selection style.

(defun selection-style-of-workstation-context (workstation-context)
  (let ((type-description (type-description-of workstation-context)))
    (or (selection-style-of-workstation-context-type
          (name-of-type-description type-description))
        'top-level-is-selection-style)))




;;;; Native Window Heartbeat



;;; The `native-window-heartbeat' exists to assure that the
;;; scheduler calls G2 at some minimum rate.  This rate
;;; is stored in native-window-polling-interval and is discussed
;;; there.  When that value is changed, this task is restarted.

;;; Currently this task has one other effect, it sets the flag
;;; that triggers the possiblity of a synthetic mouse motion
;;; being generated.  This is discussed in mouse-tracking.

(def-system-variable native-window-heartbeat-task WORKSTATION nil)

(defun start-or-restart-native-window-heartbeat ()
  (cancel-task native-window-heartbeat-task)
  (with-temporary-gensym-float-creation start-or-restart-native-window-heartbeat
    (let ((realtime-interval-of-heartbeat
	    (/e (coerce-fixnum-to-gensym-float native-window-polling-interval)
		1000.0)))
      (declare (type gensym-float realtime-interval-of-heartbeat))
      (with-future-scheduling
	  (native-window-heartbeat-task ;; place
	    ;; priority
	    0
	    ;; Delay prior to running.
	    (+e (gensym-get-unix-time) realtime-interval-of-heartbeat)
	    ;; Scan interval, 
	    realtime-interval-of-heartbeat
					;ensure anniversaries and real time!
	    nil t)
	(native-window-heartbeat system-window)))))

(defun native-window-heartbeat (native-gensym-window)
  #+development (update-pseudo-run-lights :native-window-heartbeat)
  (setf
    (consider-synthetic-motion-event?
      (workstation-this-is-on native-gensym-window))
    t))





;;;; Spots

;;; (See module MICE-COMMOM for related documentation on mouse-pointers)

;;; The `Spot' data type is introduced in at the top of this module.
;;; The thread runs thru the `enclosing-spot' slot implements a stack.
;;; The head of this stack is owned by a mouse-pointer.  A back pointer
;;; to that mouse pointer is available in `mouse-pointer-of-spot'

;;; Most spots on the screen can contain additional spots.  A slot
;;; `further-tracking-maybe-required?' is used to denote if the mouse
;;; tracking has finished finding the smallest spot available for the
;;; mouse pointer.  This slot defaults to T.

;;; Most spots represent some item in the the user's document, and this item is
;;; recorded in the spot by the `frame-represented?' slot.  This is guarded by
;;; `frame-serial-number-of-spot', this records the maximum of the represented
;;; item's serial number and that of the enclosing spot.  Spots are only used
;;; inside the service-worksation context, and they are validated when ever that
;;; context is entered.  If a spot is found to be invalid it is replaced
;;; with an invalid spot, and the mouse-pointer is marked.



;;; `Def-spot' is used to define all spot structure types.  It takes a number of
;;; keyword arguments.  The :slots argument should consist of the slots for
;;; def-structure, however with the exception [beginning with the sources
;;; pending release as of 10/8/99] that a slot description consisting of just a
;;; symbol becomes a def-structure slot description consisting of a list of that
;;; symbol and nil, i.e., a slot initialized to nil as opposed to "garbage".
;;; The :include, which defaults to spot, is passed thru to def-structure.

;;; The :print-function is passed thru to def-structure, but defaults to
;;; print-spot.

;;; The remaining options are stored in type-description's alist.  They
;;; maybe fetched using `get-spot-info'.  They default to the value
;;; specified for the included spot type.  See the def-spot for spot
;;; to see the top level defaults.

;;; The :type-of-enclosing spot declares what type the spot found on the
;;; enclosing-spot?.  The value NULL indicates that the spot can be
;;; the most enclosing entry in the stack, there is only one spot type.

;;; The :abstract-type-p is a boolean flag indicating if instances of this
;;; type are ever created.

;;; The :innermost-spot-p is a boolean flag indicating that instances of this
;;; type occur at the top of the stack after all tracking has finished.

;;;  The :type-of-frame-represented maybe used to declare just that, this
;;; defaults to null, indicating that frame-represented? will be nil.

(defmacro def-spot (spot-name &optional
			      &key
			      (slots nil)
			      (include 'spot)
			      (print-function 'print-spot)
			      (enclosing-spot-type
				(get-spot-info include 'enclosing-spot-type))
			      (innermost-spot-p
				(get-spot-info include 'innermost-spot-p))
			      (abstract-type
				(get-spot-info include 'abstract-type))
			      (type-of-frame-represented
				(get-spot-info include 'type-of-frame-represented)))
  #-development
  (declare (ignore print-function))
  `(progn
     (def-structure (,spot-name (:include ,include)
				#+development
				(:print-function ,print-function))
       ,@(ensure-def-structure-slot-descriptions-have-initializations slots))
     (eval-when (:compile-toplevel :load-toplevel :execute)
       (let ((type-description (type-description-of-type ',spot-name)))
	 (setf (alist-of-type-description type-description)
	       (list* (list 'innermost-spot-p ',innermost-spot-p)
		      (list 'enclosing-spot-type ',enclosing-spot-type)
		      (list 'abstract-type ',abstract-type)
		      (list 'type-of-frame-represented ',type-of-frame-represented)
		      (alist-of-type-description type-description)))))
     ',spot-name))



;;; The defun-for-macro
;;; `ensure-def-structure-slot-descriptions-have-initializations' expects a list
;;; of valid def-structure slot descriptions, and returns a list in which all
;;; slot descriptions contain initializations, i.e., in which there are no slot
;;; descriptions that are just symbols, and every slot description is a list
;;; containing at least two elements: the slot name and the initialization form.
;;; The argument tree is not mutated.  The resulting tree may contain new (free)
;;; conses, but may also share some, all, or no conses with the original.
;;;
;;; This is used by def-spot [as of the sources 10/8/99] to paper over the
;;; somewhat less-than-safe handling of slot descriptions with no
;;; initializations, i.e., those that are symbols, in which case it leaves them
;;; uninitialized, thus containing whatever value they held in their previous
;;; incarnation.  It was found that this behavior was the cause of bugs,
;;; previously undiscovered, and provided no beneficial functionality.  It was
;;; at best an unnecessary optimization.

(defun-for-macro ensure-def-structure-slot-descriptions-have-initializations
    (slots)
  (loop for slot-description in slots
	collect
	  (if (symbolp slot-description)
	      (list slot-description nil)
	      slot-description)))

;; An example of slots holding garbage was table-spot, which includes text-spot,
;; when applies to a spot on a non-text-cell (i.e., block) cell, rare but
;; possible, in which case the text-of-text-spot, format-frame-of-text-spot,
;; format-plist-of-text-spot at least held garbage.  I was suspicious of
;; numerous other non-initializing slots, including represented-frame?, common
;; to all spots.  (MHD 10/8/99)

(defun-for-macro get-spot-info (spot-type info-key)
  (second
    (assq
      info-key
      (alist-of-type-description
	(type-description-of-type spot-type)))))

(def-spot spot
    :slots (mouse-pointer-of-spot
	     (enclosing-spot? nil :reclaimer reclaim-structure-if-any)
	     (further-tracking-maybe-required? T)
	     frame-represented?
	     (frame-serial-number-of-spot nil))
    :include named-gensym-structure
    :enclosing-spot-type spot
    :innermost-spot-p nil
    :print-function print-spot
    :abstract-type t
    :type-of-frame-represented null)

#+development
(defun print-spot (spot stream depth)
  (declare (ignore depth))
  (printing-random-object (spot stream)
    (format stream "~S ~S"
	    (name-of-type-description
	      (type-description-of spot))
	    (frame-represented? spot))))


;;; An `entire-g2-window-spot' is found at the base of every
;;; stack-of-spots.  It is always possible to track further
;;; into it, the result of doing so will push either an
;;; image-plane-spot, or gensym-window-background-spot.

(def-spot entire-g2-window-spot
    :innermost-spot-p nil
    :enclosing-spot-type null
    :type-of-frame-represented g2-window)



;;; An `invalid-spot' is used to replace a spot that has been invalidated.
;;; Spots are invalidated when the service workstation task validates each spot,
;;; using the recorded frame serial numbers of each item.  These spots never
;;; reference an item.

(def-spot invalid-spot
    :innermost-spot-p t
    :enclosing-spot-type spot
    :type-of-frame-represented null)


;;; `Reclaim-mouse-pointers' reclaims a list of mouse pointers it is
;;; used to reclaim the slot in the workstation structure which
;;; manages all the mouse-pointers.

(defun-void reclaim-mouse-pointers (gensym-list-of-mouse-pointers)
  (loop for mouse-pointer in gensym-list-of-mouse-pointers
	do #+development
	   (unless (<=f 0 (reference-count-of-mouse-pointer mouse-pointer))
	     (cerror "continue" "reference count is negative"))
	   (reclaim-mouse-pointer mouse-pointer))
  (reclaim-gensym-list gensym-list-of-mouse-pointers))

#+development
(defun describe-mouse-pointer (mouse-pointer)
  (format t "~&~S " mouse-pointer)
  (when (further-tracking-maybe-required? (stack-of-spots mouse-pointer))
    (format t "~&  ...."))
  (loop for spot? = (stack-of-spots mouse-pointer)
	then (enclosing-spot? spot?)
	while spot?
	do (format t "~&  ~S" spot?))
  mouse-pointer)



;;;; Tracking Mouse Into Spots





;;; The `track-mouse-into-spot' should be defined for all spots that may
;;; exists with a non-NIL `further-tracking-maybe-required?' slot.  The default
;;; defined on the abstract structure type spot, will often do the right thing.

;;; This method must clear further-tracking-maybe-required?.  If if the spot in
;;; question contains a nested spot under the mouse one or more additional spots
;;; should be pushed into the mouse-pointer.  The last of these may require
;;; futher tracking.

;;; Each refinement of this method attempts should do nothing if
;;; `further-tracking-maybe-required' is nil.  It must call the
;;; superior method if it is unable to set further-tacking-maybe-required
;;; to nil.

;;; The dynamic extent provide to these methods is provided by their only common
;;; ancestor in the calling tree, shift-lexical-analysis-of-current-workstation.
;;; See also the default implementation on spot.

;;; See the concept `mouse-tracking' for another meaning of this term.

(def-generic-structure-method track-mouse-into-spot (spot))


#+development
(defparameter trace-mouse-tracking-p nil)



;;; `Track-mouse-pointer' takes a mouse-pointer and invokes the
;;; track-mouse-into-spot of the spot at the head of it's stack-of-spots.

(defun-void track-mouse-pointer (mouse-pointer)
  (track-mouse-into-spot (stack-of-spots mouse-pointer)))

;;; `Track-mouse-pointer-till-done' calls track-mouse-pointer until
;;; the innermost spot of the mouse pointer requires no futher tracking.

(defun-void track-mouse-pointer-till-done (mouse-pointer)
  #+development
  (when trace-mouse-tracking-p
    (format t "~&Track ~S" (stack-of-spots mouse-pointer)))
  (loop for most-detailed-spot = (stack-of-spots mouse-pointer)
	while (further-tracking-maybe-required? most-detailed-spot)
	do
    (track-mouse-into-spot most-detailed-spot)
    
	#+development
	(progn
	  (when (and (eq most-detailed-spot (stack-of-spots mouse-pointer))
		     (further-tracking-maybe-required? most-detailed-spot))
	    (error "Making no progress tracking the mouse pointer."))
	  (when trace-mouse-tracking-p
	    (format t "~&Track -> ~S" most-detailed-spot)))))



;;; `Make-an-initial-mouse-pointer' is used to create mouse pointers placed into
;;; slots prior to the event processing getting up a head of steam.  They allow
;;; the code to avoid a mess of nil checks.  The resulting mouse pointer is
;;; marked as containing invalid spots, and all they contain is one invalid spot
;;; in their spot stack most scary they don't even contain an
;;; entire-g2-window-spot.

(defun make-an-initial-mouse-pointer (workstation)
  (let ((mouse-pointer
	  (make-mouse-pointer
	    workstation
	    illegal-key-code ; key-code
	    0 ; fixnum-time
	    0 0 ; mouse-x mouse-y
	    )))
    (setf (contains-invalid-spots mouse-pointer) t)
    (push-last-spot mouse-pointer (make-invalid-spot) nil)
    mouse-pointer))



;;;; For Workstation a Named Dynamic Extent




;;; The dynamic extent `for-workstation' includes the union of the binding
;;; of for-workstation-polling and for-workstation-context.  It includes a few
;;; additional bindings of it's own.

;;; Current-workstation-native-window? is nil for a window of type ICP.

(def-named-dynamic-extent for-workstation 
  (module workstation)
  (unwind? t) 
  (includes for-workstation-polling for-workstation-context))



;;; `Servicing-workstation?' is a boolean flag indicating that a for-workstation
;;; dynamic extent is current.

(defvar-of-named-dynamic-extent servicing-workstation? for-workstation
  (global-binding nil))



;;; `current-workstation-detail-pane'

(defvar-of-named-dynamic-extent current-workstation-detail-pane for-workstation)



;;; `Current-workstation-g2-window?' is bound in a for-workstation context to
;;; the value of the g2-window-for-this-workstation? of current-workstation.
;;; Note: in G2 7.1 (the release pending as of 7/25/03), this value may be any
;;; instance of the class g2-window, e.g., including workspace-view.

(defvar-of-named-dynamic-extent current-g2-window-for-this-workstation?
    for-workstation)


;;; `current-g2-user-mode?'

(defvar-of-named-dynamic-extent current-g2-user-mode? for-workstation)


;;; New-g2-classic-ui-p controls whether a new UI style under development is in
;;; effect.  For now, the mode has to be turned on by choosing "New G2 Classic
;;; UI On" in the Main Menu Miscellany menu.  ("New G2 Classic UI Off" turns
;;; this off.)  It is off (nil) by default.

(def-system-variable new-g2-classic-ui-p mice nil)


;; `New-g2-classic-ui-standard-dialog-background-color' ...

(defparameter new-g2-classic-ui-standard-system-workspace-background-color 'smoke)

(defmacro new-standard-font-size ()
  `(case new-g2-classic-ui-p
     (standard-large 'large)
     (t 'small)))


;;; `Get-ui-parameter' ...

(defun get-ui-parameter (parameter-name &optional adjustment)
  (let ((font-for-editing (new-standard-font-size))
	(font-for-menus (new-standard-font-size))
	(font-for-title-bars (new-standard-font-size))
	(system-workspace-background-color
	  new-g2-classic-ui-standard-system-workspace-background-color))
    (case parameter-name
      (font-for-editing font-for-editing)
      (system-workspace-background-color system-workspace-background-color)
      (attributes-table-format 'new-attributes-table-format)
      (font-for-menus font-for-menus)
      ;; derived from FONT-FOR-MENUS:
      (menu-item-format
       (if (eq adjustment 'right)
	   (case font-for-menus
	     (small 'left-arrow-left-aligned-menu-item-format-new-small)
	     (t 'left-arrow-left-aligned-menu-item-format-new-large))
	   (case font-for-menus
	     (small 'left-aligned-menu-item-format-new-small)
	     (t 'left-aligned-menu-item-format-new-large))))
      (cascade-menu-item-format
       (if (eq adjustment 'right)
	   (case font-for-menus
	     (small 'left-arrow-left-aligned-cascade-menu-item-format-new-small)
	     (t 'left-arrow-left-aligned-cascade-menu-item-format-new-large))
	   (case font-for-menus
	     (small 'left-aligned-cascade-menu-item-format-new-small)
	     (t 'left-aligned-cascade-menu-item-format-new-large))))
      (close-box-x-offset (case font-for-menus (small 10) (t 11)))
      (close-box-y-offset (case font-for-menus (small 7) (t 16)))

      (font-for-title-bars font-for-title-bars)
      ;; derived from FONT-FOR-TITLE-BARS:
      (title-bar-format
       (case font-for-title-bars
	 (small 'left-aligned-menu-item-format-new-small)
	 (t 'left-aligned-menu-item-format-new-large)))
      (workspace-title-bar-frame-style
       (case font-for-title-bars
	 (small 'workspace-title-bar-frame-style-small)
	 (t 'workspace-title-bar-frame-style-large))))))

  ;; Note 1: offsets hand-tweaked a bit to land mouse in close box, just under and
;; at most a hair to the right of the center of the X, non-walking-menu case.
;; This is also used for putting up attribute tables. (MHD 10/6/99)




;;; The macro `For-workstation' establishes a for-workstation dynamic extent
;;; over it's body.

(defmacro for-workstation ((workstation) &body body)
  `(with-named-dynamic-extent* for-workstation
       (;; via for-workstation-polling
	(current-workstation ,workstation)
	(current-workstation-window
	  (window-for-workstation current-workstation))
	(current-g2-window-for-this-workstation?
	  (g2-window-for-this-workstation? current-workstation))
	(type-of-current-workstation-window
	  (type-of-gensym-window current-workstation-window))
	(current-workstation-native-window?
	  (native-window? current-workstation-window))
	;; via for-workstation-context 
	(current-workstation-context
	  (car (workstation-context-stack current-workstation)))
	(type-of-current-workstation-context
	  (type-of-workstation-context current-workstation-context))
	(specific-structure-for-current-workstation-context
	  (specific-structure-for-workstation-context
	    current-workstation-context))
	;; via for-workstation 
	(current-workstation-detail-pane
	  (detail-pane current-workstation-window))
	(current-g2-user-mode?
	  (g2-user-mode-for-this-workstation? current-workstation))
	(new-g2-classic-ui-p
	  (get-value-for-current-workstation-new-g2-classic-ui-p))
	(servicing-workstation? T))
     ,@body))








;;;; The Workstation Context Stack



;;; A `workstation context' implements a modality in the event
;;; processing of a workstation.  They assure that the processing
;;; associated with the mode does not starve out other G2 micro
;;; tasks.  

;;; For example when the mouse is depressed on a button we enter
;;; a context to track the mouse and manage the highlighting of
;;; the button.  Meanwhile other processing proceeds as usual.

;;; Each workstation has one or more workstation contexts organized in
;;; a stack that reflects the user entering and exiting particular modes.
;;; The oldest entry in the stack is known as the top-level context.
;;; Events are dispatched to the most recent context, and failing that
;;; they are dispatched to the top level context.

;;; Examples of workstation contexts include top-level, editing,
;;; dragging, marking, g2-login, breakpoint, subcommand, layout,
;;; icon-editor, selection.  Notice that workstation-context names are
;;; sometimes verbs, indicating what the user is doing in this mode, or
;;; nouns indicating what subsystem of G2 manages this modality.

;;; The `workstation-context-stack' is a tangle rooted a slot of workstations.
;;; the backbone of the stack are structures of type `workstation-context' and
;;; each of these points to structure that subtypes `workstation-context-frame'.
;;; (Do (outline-type-description 'workstation-context-frame) for a full
;;; enumeration.

;;; All this is a complex way to implement a threaded interpreter for handling
;;; event processing.  By analogy workstation-context-stack is then the execution
;;; stack of this thing.  The workstation-context structures are the call frames
;;; in the stack, while the workstation-context-frames are the local variables of
;;; the individual "subprograms".

;;; To implement a new workstation context you first define a structure that
;;; will hold the state vector of the context.  This structure is usually named
;;; <M>-state, as in dragging-state, top-level-state, etc.  This structure
;;; should include workstation-context-frame directly or
;;; indirectly.  You then implement a function to enter the state, three or more
;;; methods on the state to do the event handling, and a return function.

;;; The methods do the event handling while the context is active.  See the
;;; section  "Workstation Context Operations" below.

;;; A useful analogy views the context stack as the call stack for the process
;;; which manages a given workstation.  The <m>-state is the lexical variables
;;; of the call.  The entry function initializes these, and then
;;; enter-workstation-context places the new entry on the stack.  The return
;;; function's job is place the return values in to the prior context.

;;; The replace-current-context-first? flag to enter-workstation-context can be
;;; used to eliminate the frame ala tail recursion.

(def-concept workstation-context-stack)
(def-concept workstation-context)

(def-structure (workstation-context (:constructor make-workstation-context ())
				    #+development (:print-function print-workstation-context))

  type-of-workstation-context			; a symbol
  specific-structure-for-workstation-context	; a subtype of workstation-context-frame
  old-workstation-context-return-function?	; a symbol naming a function
  continuation-for-workstation-context?         ; a symbol naming a function
  workstation-context-return-information	; arbitrary lisp object
  workstation-context-return-information-reclaimer?	; a symbol naming a function
  track-mouse-in-this-workstation-context?	; boolean
  this-is-a-modal-context?			; when true, workstation has type-
						;   of-workstation-context in its
						;   type-of-modal-context? slot for
						;   this and all subcontexts
  )



#+development
(defun print-workstation-context (workstation-context stream depth)
  (declare (ignore depth))
  (printing-random-object (workstation-context stream)
     (format stream "~s ~s ~s"
	     'workstation-context
	     (type-of-workstation-context workstation-context)
	     (specific-structure-for-workstation-context workstation-context))))


;;; `trace-workstation-context-stack-p' ...

#+development
(defvar trace-workstation-context-stack-p nil)
;; (setf trace-workstation-context-stack-p t)
;; (setf trace-workstation-context-stack-p nil)

#+development
(defun trace-workstation-context-stack (&rest args)
  (unless trace-workstation-context-stack-p
    (error "Misplace trace call."))
  (format t "~&wk-stk: ~(~{~S ~}~)" args)
  (force-output *standard-output*))






;;; A `workstation context return function' provides control over the process
;;; of returning successfully from a workstation context.  It must pop the
;;; stack.  It straddles between the exiting context and it's caller.

;;; In order it should:
;;;    (1) extract any information it needs from its exiting workstation-context,
;;;        including that in the workstation-context-return-information.
;;;
;;;    (2) It may preempt the reclaiming of that information by nil-ing out
;;;        portions of it.
;;;
;;;    (3) do (exit-current-workstation-context-in-return-function '<returning-context>)
;;;        This has plenty of side effects, see unwind-one-workstation-context
;;;        below.
;;;
;;;    (4) Proceed in the superior context (i.e. at this point you have a
;;;        continuation.

(def-concept return-function)
(def-concept workstation-return-function)
(def-concept workstation-context-return-function)



;;; `Reclaim-workstation-context-stack' is the reclaimer for the the workstation-
;;; context-stack slot in workstation structures.

(defun reclaim-workstation-context-stack (workstation-context-stack)
  (loop for workstation-context in workstation-context-stack
	do (reclaim-workstation-context workstation-context))
  (reclaim-gensym-list workstation-context-stack))

;; Can this be right? - ben 3/17/94
















;;; `Establish-next-workstation-context-continuation' implements setting up a
;;; "call frame" in the workstation context stack.  It is used just prior to
;;; invoking a new workstation context.  The prefered interface to this is
;;; with-workstation-context-continuation.  It declares how the current context
;;; will proceed after a successful return from the subcontext.

;;; It takes four arguments.  The first argument implements the new prefered
;;; style.  The last four arguments implement the old style we are phasing
;;; out.

;;; The first argument is a continuation function.  This function will be
;;; invoked if the subcontext returns.  It is not invoked if the subcontext
;;; aborts (there is currently no way to establish an unwind protect to catch
;;; that eventuality).  This argument should be a symbol who's symbol-function
;;; takes one argument the workstation-context.

;;; Alternately the following three arguments can be given.  These entirely
;;; replace the return mechinisms of the workstation context stack interpreter.
;;; When the subcontext returns, the first arguement (aka the return function)
;;; is invoked.  The function MUST exit the subcontext.  The return function
;;; is a symbol, the symbol function of which should be a function of one
;;; argument.  It is invoked with the context-frame of the  SUB-context.

;;; The third argument, the return-information, is stored into the sub context's
;;; frame.  The fourth argument is invoked when the context is aborted, and
;;; provides a kind of unwind-protect that may reclaim the return information.

(def-substitution-macro store-next-workstation-context-continuation-information-1
    (continuation-function? old-style-return-function info info-reclaimer?)
  (setf next-continuation-function? continuation-function?)
  (setf next-old-style-return-function? old-style-return-function)
  (setf next-info info)
  (setf next-info-reclaimer? info-reclaimer?))

(defvar next-continuation-function? nil)
(defvar next-old-style-return-function? nil) 
(defvar next-info nil)
(defvar next-info-reclaimer? nil)

(defun establish-next-workstation-context-continuation
    (continuation-function? old-style-return-function? info info-reclaimer?)
  (store-next-workstation-context-continuation-information-1
    continuation-function? old-style-return-function? info info-reclaimer?))

(def-substitution-macro clear-next-workstation-context-continuation-information ()
    (store-next-workstation-context-continuation-information-1 nil nil nil nil))



;;; `With-workstation-context-continuation' is the prefered interface
;;; to establish-next-workstation-context-continuation.

(defmacro with-workstation-context-continuation ((continuation-function) &body body)
  `(with-workstation-context-continuation-1 (',continuation-function nil nil nil)
     ,@body))

(defmacro with-old-style-workstation-return-function
    ((return-function return-info reclaimer) &body body)
  `(with-workstation-context-continuation-1
       (nil ,return-function ,return-info ,reclaimer)
     ,@body))

(defmacro with-workstation-context-continuation-1
    ((continutation-function old-style-return-function info info-reclaimer?)
     &body body)
  `(progn
    (establish-next-workstation-context-continuation
      ,continutation-function ,old-style-return-function ,info ,info-reclaimer?)
    ,@body))




;;; `Available-workstation-contexts' is a free space pool for workstation
;;; contexts.

;; Does anybody know why we don't trust the structure pools to do this for us? - ben
;; Because we're trying to re-use the pool conses for maximum performances. - binghe

(def-system-variable available-workstation-contexts workstation nil)



;;; `Enter-context-in-current-workstation' pushes a new workstation context of
;;; type type-of-workstation-context onto the context stack for
;;; current-workstation.  I.e. it implements a the call semantics of this silly
;;; little event interpreter.

;;; Specific-structure-for-workstation-context is the call frame, and is
;;; a subtype of the structure workstation-context.

;;; If this-is-a-modal-context? is true, then this context is considered a
;;; `modal' context.  During this and non-modal contexts later pushed onto the
;;; stack (i.e. subcontexts), the type-of-modal-context? slot of workstations
;;; will have type-of-workstation-context as their value.

(defun enter-context-in-current-workstation
    (type-of-workstation-context
      specific-structure-for-workstation-context
      &optional
      (this-is-a-modal-context? nil))
  #+development
  (when trace-workstation-context-stack-p
    (trace-workstation-context-stack
      'enter type-of-workstation-context specific-structure-for-workstation-context))
  (let ((specific-structure-1 specific-structure-for-current-workstation-context))
    (when specific-structure-1
      (suspend-workstation-context specific-structure-1)))
  (unless available-workstation-contexts
    (gensym-push (make-workstation-context) available-workstation-contexts))
  (let* ((listed-new-workstation-context available-workstation-contexts)
	 (new-workstation-context (car listed-new-workstation-context))
	 (specific-structure-2 specific-structure-for-current-workstation-context))
    ;; pop one node from available-workstation-contexts into new-workstation-context,
    ;; while listed-new-workstation-context is holding the poped cons.
    (setq available-workstation-contexts (cdr available-workstation-contexts))
    ;; re-use the cdr of node's cons to hold a stack
    (setf (cdr listed-new-workstation-context)
	  (workstation-context-stack current-workstation))
    ;; then modify the poped node.
    (setf (type-of-workstation-context new-workstation-context)
	  type-of-workstation-context)
    (setf (specific-structure-for-workstation-context new-workstation-context)
	  specific-structure-for-workstation-context)
    (setf (old-workstation-context-return-function? new-workstation-context)
	  next-old-style-return-function?)
    (setf (continuation-for-workstation-context? new-workstation-context)
	  next-continuation-function?)
    (setf (workstation-context-return-information new-workstation-context)
	  next-info)
    (setf (workstation-context-return-information-reclaimer?
	    new-workstation-context)
      next-info-reclaimer?)
    (clear-next-workstation-context-continuation-information)
    ;; push the node into workstation-context-stack of current-workstation, using
    ;; the re-used cons.
    (setf (workstation-context-stack current-workstation)
	  listed-new-workstation-context)
    (when (setf (this-is-a-modal-context? new-workstation-context)
		this-is-a-modal-context?)
      (setf (type-of-modal-context? current-workstation)
	    type-of-workstation-context))
    ;; change 'current-workstation-context
    (setq current-workstation-context new-workstation-context)
    (setq type-of-current-workstation-context type-of-workstation-context)
    (let ((new-selection-style
	   (selection-style-of-workstation-context
	     specific-structure-for-workstation-context))
	  (old-selection-style
	   (if specific-structure-2
	       (selection-style-of-workstation-context specific-structure-2)
	       'unknown-is-selection-style)))
      (setq specific-structure-for-current-workstation-context
	    specific-structure-for-workstation-context)
      ;; synchronize-selection-style does this test itself.  We need to call it
      ;; in all cases.
      ;;      (unless (eq old-selection-style new-selection-style))
      (synchronize-selection-style old-selection-style new-selection-style))
    (setup-workstation-context
      specific-structure-for-current-workstation-context)))



;;; `Unwind-one-workstation-context' removes one context from the context stack
;;; of the current for-worksation context.

;;;   (1) invoke clean-up-workstation-context
;;;       -- note that the suspend is not called.
;;;   (2) invoke return-information-reclaimer?
;;;   (3) popping the context stack
;;;   (3a) [new convention for release pending (MHD 2/28/00):
;;;        The new top of the context is checked; if it is null,
;;;        or not valid-workstation-context-p, steps (4), (5), and
;;;        (6) are not done, but step (7) is always done.
;;;   (4) resynchronize assorted dynamic state.
;;;         for-workstation state, 
;;;         the modal context flag, and
;;;         selection-style -- call synchronize-selection-style
;;;   (5) invoke resume-workstation-context
;;;   (6) invoke the continuation?
;;;   (7) Reclaim-gensym-tree-with-text-strings is invoked on the (new-style) 
;;;       workstation context return values.

;;; This routine is rarely called directly, instead other routines provide
;;; slight more useful variations on the semantics:
;;;  1. return-from-current-workstation-context  -- for normal returns.
;;;  2. abort-current-workstation-context        -- for aborting
;;;  3. unwind-all-workstation-contexts          -- for workstation shutdown
;;;  4. exit-current-workstation-context-in-return-function
;;;                                              -- for inside return functions

(defun unwind-one-workstation-context ()
  (let ((continuation?
	  (continuation-for-workstation-context? current-workstation-context))
	(old-selection-style
	  (selection-style-of-workstation-context
	    specific-structure-for-current-workstation-context)))
    (let ((old-workstation-context-stack
	    (workstation-context-stack current-workstation)))

      ;; Clean up and reclaim the current context.
      (let* ((workstation-context-return-information-reclaimer?
	       (workstation-context-return-information-reclaimer?
		 current-workstation-context)))
	(clean-up-workstation-context
	  specific-structure-for-current-workstation-context)
	(setq specific-structure-for-current-workstation-context
	      'specific-structure-has-been-reclaimed)
	(when workstation-context-return-information-reclaimer?
	  (funcall-symbol
	    workstation-context-return-information-reclaimer?
	    (workstation-context-return-information
	      current-workstation-context))))
      
      ;; Remove the old context and put it on the
      ;;  available-workstion-context list, reusing
      ;;  the cons.
      #+development
      (test-assertion				; illegal for above calls
	(eq old-workstation-context-stack		; to have changed this!
	    (workstation-context-stack current-workstation)))
      ;; Pop the node
      (setf (workstation-context-stack current-workstation)
	    (cdr old-workstation-context-stack))
      (setf (workstation-context-return-information current-workstation-context)
	    nil)					; not really nec.
      ;; Push the node; Consider setting other of the slots to nil.
      (setf (cdr old-workstation-context-stack) available-workstation-contexts)
      (setq available-workstation-contexts old-workstation-context-stack)
      ;; Update current-workstation-context
      (setq current-workstation-context
	    (car (workstation-context-stack current-workstation))))

    ;; Now reenter the now current context, if we have one.
    (when current-workstation-context
      (setq type-of-current-workstation-context
	    (type-of-workstation-context current-workstation-context))
      (setq specific-structure-for-current-workstation-context
	    (specific-structure-for-workstation-context
	      current-workstation-context))
      ;; Simulate a dynamic binding for the flag that indicates
      ;;   we are in a modal context.
      (loop for workstation-context
		in (workstation-context-stack current-workstation)
	    when (this-is-a-modal-context? workstation-context)
	      return
	      (setf (type-of-modal-context? current-workstation)
		    (type-of-workstation-context workstation-context))
	    finally
	      (setf (type-of-modal-context? current-workstation) nil))
      (let ((new-selection-style
	      (selection-style-of-workstation-context
		specific-structure-for-current-workstation-context)))
	(synchronize-selection-style old-selection-style new-selection-style))
      (when (valid-workstation-context-p-function ; fwd. ref.
	      specific-structure-for-current-workstation-context)
	(resume-workstation-context
	  specific-structure-for-current-workstation-context)
	(when continuation?
	  #+development
	  (when trace-workstation-context-stack-p
	    (trace-workstation-context-stack 'continuation continuation?))
	  (funcall-symbol continuation? current-workstation-context))))
    ;; Reset (Reclaim and null out) values, if any.
    (reset-current-workstation-context-return-values)))	; see note A

;; Must we have our one free space manager in available-workstation-contexts?
;; - ben 11/28/93

;; Note A: contexts lower down, if any, will, it is assumed, be checked for
;; validity in next service workstation.  For this new storage convention, every
;; (new-style) return function and continuation function were visited to make
;; sure they comply with this new storage convention. (MHD 2/28/00)



;;; Reset-current-workstation-context-return-values is called at the tail end of
;;; unwind-one-workstation-context.  It reclaims the contents of the (new-style)
;;; return values in current-workstation, and sets those slots to nil.

(defun reset-current-workstation-context-return-values ()
  (setf (workstation-context-first-return-value current-workstation)
	(prog1 nil (reclaim-gensym-tree-with-text-strings
		     (workstation-context-first-return-value
		       current-workstation))))
  (setf (workstation-context-second-return-value current-workstation)
	(prog1 nil (reclaim-gensym-tree-with-text-strings
		     (workstation-context-second-return-value
		       current-workstation))))
  (setf (workstation-context-third-return-value current-workstation)
	(prog1 nil (reclaim-gensym-tree-with-text-strings
		     (workstation-context-third-return-value
		       current-workstation)))))



;;; `Unwind-one-workstation-context-safely' is internal to the context stack
;;; maintainance.  It invokes unwind-one-workstation-context, unless that
;;; would trigger the catastrophy of clearing off the last stack entry.

(defun unwind-one-workstation-context-safely ()
  (when (cdr (workstation-context-stack current-workstation))
    (unwind-one-workstation-context)))


;;; `Abort-current-workstation-context' is invoked in an event handler
;;; to abort the workstation context.  The context is unwound and the
;;; continuation is invoked with the return values of `:abort' and
;;; the latest mouse pointer.

;;; See unwind-one-workstation-context for additional actions taken.

(defun abort-current-workstation-context (context-name)
  #-development
  (declare (ignore context-name))
  #+development
  (when (and context-name
	     (not (eq context-name type-of-current-workstation-context)))
    (cerror "Go" "Exiting wrong context."))
  #+development
  (when trace-workstation-context-stack-p
    (trace-workstation-context-stack 
      'abort type-of-current-workstation-context
      specific-structure-for-current-workstation-context))
  (setf (workstation-context-first-return-value current-workstation)
	:abort)
  (setf (workstation-context-second-return-value current-workstation)
	(mouse-pointer-of-latest-event current-workstation))
  (unwind-one-workstation-context-safely))


;;; `Exit-current-workstation-context-in-return-function' must be
;;; called in the workstation context return function.  It unwinds
;;; one context from the stack.  It then invokes the continuation
;;; if any.

;;; See unwind-one-workstation-context for additional actions taken.

(defun exit-current-workstation-context-in-return-function (context-name)
  #-development
  (declare (ignore context-name))
  #+development
  (unless (eq context-name type-of-current-workstation-context)
    (cerror "Go" "Exiting wrong context."))
  #+development
  (when trace-workstation-context-stack-p
    (trace-workstation-context-stack 
      'exit type-of-current-workstation-context
      specific-structure-for-current-workstation-context))
  (unwind-one-workstation-context-safely))



;;; `Return-from-current-workstation-context' does just that.  It's first
;;; argument is the name of the context from which we are returning, and
;;; the remaining arguments, which are optional, are the values to return.

;;; This is the only way to "successfully" return from a workstation context
;;; and as such it will execute the `return-function.'

;;; See unwind-one-workstation-context for additional actions taken.

;;; [New return value storage conventions: (MHD 2/28/00)] Values v1, v2, and v3
;;; should be unshared gensym conses with text strings, and reclaimed
;;; accordingly.  Other atoms will be unreclaimed.  No other conses are allowed.
;;; Consumers, i.e., in continuation functions, should copy them out if they are
;;; to live on past their dynamic extent.  Note that the continuation function
;;; will not be called at all if the workstation context it is for is not valid
;;; (i.e., valid-workstation-context-p), a recent new convention which makes
;;; storage convention desirable.

(defun return-from-current-workstation-context (context-name &optional v1 v2 v3)
  #-development
  (declare (ignore context-name))
  #+development
  (unless (eq context-name type-of-current-workstation-context)
    (cerror "Go" "Exiting from wrong workstation context."))
  (setf (workstation-context-first-return-value current-workstation) v1)
  (setf (workstation-context-second-return-value current-workstation) v2)
  (setf (workstation-context-third-return-value current-workstation) v3)
  (let ((old-style-return-function?
	  (old-workstation-context-return-function? current-workstation-context)))
    #+development
    (when trace-workstation-context-stack-p
      (trace-workstation-context-stack 
	'return-from type-of-current-workstation-context
	specific-structure-for-current-workstation-context
	:return-function
	old-style-return-function?))
    (if old-style-return-function?
	(funcall-symbol old-style-return-function? current-workstation-context)
	(unwind-one-workstation-context-safely))))


;;; `With-workstation-context-return-values' is used in workstation context
;;; continuation functions to obtain the return values from the subcontext.

(defmacro with-workstation-context-return-values ((&optional v1 v2 v3) &body body)
  `(let (,@(loop for v in (list v1 v2 v3)
		 as a in '(workstation-context-first-return-value
			   workstation-context-second-return-value
			   workstation-context-third-return-value)
		 when v collect `(,v (,a current-workstation))))
     ,@body))
  


;;; `Unwind-all-workstation-contexts' unwinds ALL contexts on the context
;;; stack of workstation, including the bottommost context in the stack,
;;; leaving the workstation-context-stack slot of workstation nil.

(defun unwind-all-workstation-contexts (workstation)
  (with-backtrace-for-internal-error 'unwind-all-workstation-contexts
    (for-workstation (workstation)
      (loop while (workstation-context-stack current-workstation)
	    do
	(setf (workstation-context-first-return-value current-workstation)
	      :abort)
	(setf (workstation-context-second-return-value current-workstation)
	      (mouse-pointer-of-latest-event current-workstation))
	(unwind-one-workstation-context)))))


(defun unwind-current-workstation-back-to-top-level ()
  (with-backtrace-for-internal-error 'unwind-current-workstation-back-to-top-level
    (loop while (cdr (workstation-context-stack current-workstation))
	  do
      (abort-current-workstation-context type-of-current-workstation-context))))











;;;; Workstation Context Operations



;;; Three methods must be defined on each structure that refines
;;; workstation-context-frame.
;;;   clean-up-workstation-context

;;; These methods are all invoked with a for-workstation and servicing-event
;;; extent established approprately.  No drawing contexts are established.
;;; They must all guard agains recycled frames.




;;; The `clean-up-workstation-context' method is called when ever the context is
;;; removed from the stack, either by returning or by aborting.  It be
;;; implemented as a before method, calling it's superior method last.  It is
;;; analagous to an unwind protect's clean up.

;;; The primary method is defined on workstation-context-frame and
;;; will reclaim the state.  Note that the last thing the primary method does is
;;; to reclaim the structure, and that will call the slot value reclaimers.  The
;;; consequence of which is that you get two passes over the context as it is
;;; shut down.

;;; Note you must be extremely careful in these methods to bear in mind that
;;; we could be aborting the context because it was no longer valid and things
;;; that is points to have been reclaimed.

;;; This is invoked from unwind-one-workstation-context within a for-workstation
;;; context.

(def-structure-method clean-up-workstation-context (workstation-context-frame)
  (reclaim-structure workstation-context-frame))


;;; `Setup-workstation-context' is an after method defined on most the specific
;;; structures of most workstation contexts.  It is the open paren to
;;; clean-up-workstation-context's close paren.  It is called after the context
;;; has been made the current context.  It is hoped this can replace most of the
;;; enter-<context> functions.

;;; Refinements to this method should be implemented as after methods. The
;;; primary method on workstation-context-frame does nothing.

(def-structure-method setup-workstation-context (workstation-context-frame)
  (declare (ignore workstation-context-frame)))

;;; See PLATFORMS for the generic methods on a `workstation-context-frame'
;;; as well as the definition of the superior type of these structures.


;;; `Suspend-workstation-context' and `resume-workstation-context' are methods
;;; on workstation-context-frame that bracket the context's being suspended to
;;; enable a nested context to become current.  Refinements on resume should be
;;; after methods, while refinements on suspend should be before methods.  They
;;; are called while the frame is still current, and with no knowledge of what
;;; frame is becoming current.  The primary methods do nothing.

(def-structure-method resume-workstation-context (workstation-context-frame)
  (declare (ignore workstation-context-frame)))

(def-structure-method suspend-workstation-context (workstation-context-frame)
  (declare (ignore workstation-context-frame)))



(defun add-mouse-pointer-to-guardians-of-workstation-context
    (mouse-pointer workstation-context-frame)
  (gensym-pushnew
    (reference-mouse-pointer mouse-pointer)
    (mouse-pointers-of-workstation-context workstation-context-frame)))







;;;; Top Level State and Set Up Workstation Context Stack




(def-structure (top-level-state
		 (:include workstation-context-frame)))

(def-selection-style-of-workstaton-context top-level-state
    top-level-is-selection-style)

(defun put-gensym-window-in-v5-mode-internal (gensym-window)
  (setf (window-is-in-v5-mode-p gensym-window) t)
  (set-v5-mode-state t))

(defun set-up-workstation-on-ab-side
    (workstation gensym-window v5-mode-p)
  (let ((current-workstation workstation)
	(current-workstation-window gensym-window)
	(type-of-current-workstation-window (type-of-gensym-window gensym-window))
	;; The following are side-affected by enter-context-in-
	;;   current-workstation, and therefore need to be bound here.
	specific-structure-for-current-workstation-context
	type-of-current-workstation-context
	current-workstation-context)
    
    (when v5-mode-p
      (put-gensym-window-in-v5-mode-internal gensym-window))
    (setf (mouse-pointer-of-latest-event workstation)
	  (make-an-initial-mouse-pointer workstation))
    (setf (mouse-pointer-of-previous-event workstation)
	  (make-an-initial-mouse-pointer workstation))
    (setf (mouse-pointer-of-last-down workstation)
	  (make-an-initial-mouse-pointer workstation))
    (setf (mouse-pointer-of-last-interesting-event workstation)	; 8.3b0
	  (make-an-initial-mouse-pointer workstation))
    (gensym-push (mouse-pointer-of-latest-event workstation)
		 (recent-mouse-pointers-1 workstation))
    (gensym-push (mouse-pointer-of-previous-event workstation)
		 (recent-mouse-pointers-1 workstation))
    (gensym-push (mouse-pointer-of-last-down workstation)
		 (recent-mouse-pointers-1 workstation))
    (gensym-push (mouse-pointer-of-last-interesting-event workstation) ; 8.3b0
		 (recent-mouse-pointers-1 workstation))
    ;; link gensym-window and workstation together.
    (setf (workstation-this-is-on gensym-window) current-workstation)
    (enter-context-in-current-workstation
      'top-level
      (make-top-level-state))
    ;; push current-workstation into workstations-in-service
    (setq workstations-in-service		; put at end instead?
	  (gensym-cons current-workstation workstations-in-service))

    (set-session-info-in-workstation gensym-window workstation)
    (when (eq gensym-window system-window)
      (start-or-restart-native-window-heartbeat))

    (setf (show-selection-handles-of-gensym-window gensym-window)
	  (show-selection-handles-p gensym-window))

    current-workstation))


(def-system-variable current-system-dummy-workstation? mice nil)

(defun get-or-make-dummy-workstation ()
  (or current-system-dummy-workstation?
      (let ((workstation (make-workstation nil))
	    specific-structure-for-current-workstation-context)
	(setf current-system-dummy-workstation? workstation)
	(setf (window-for-workstation workstation)
	      (make-gensym-window nil)) ; see note! (MHD 8/21/03)
	(for-workstation-polling (workstation)
	  (enter-context-in-current-workstation
	    'top-level
	    (make-top-level-state)))
	workstation)))

;; Note: if we're calling the editor from programmatic Inspect the variable
;; current-workstation-window was previously being bound to nil, since the
;; window slot of the workstation was nil.  However, as its name implies (no '?'
;; at the end), it should never be nil.  To fix this, we now create a "dummy
;; window", which may not have every slot set up correctly, but should be
;; adequate for practical/all known uses, namely checking the plist, e.g., to
;; enable tests such as mdi-frame-p on this window.  All plist checks should be
;; able to cope with an empty plist.  However, at present, the main testing this
;; has undergone at this point is simply to get programmatic Inspect to work
;; (fixing bug HQ-4626157 "G2 abort using programmatic inspect"). But note that
;; G2 has been functioning without reported aborts when
;; current-workstation-window was being bound to nil, and this fixes the first
;; known case of code that could not tolerate that situation. It seems therefore
;; rather unlikely that there other cases in practice.  This facility should
;; probably be reviewed and cleaned up at some future point anyhow; it doesn't
;; seem very clean! (MHD 8/21/03)


(defun dummy-workstation-p (workstation)
  (or (eq workstation current-system-dummy-workstation?)
      (null (window-for-workstation workstation))
      (null (workstation-this-is-on (window-for-workstation workstation)))))


;;; `for-dummy-workstation' exists to allow use of editing facilities
;;; on a potentially "headless" G2.  Such facilities include inspect
;;; (queries.lisp) and parse-text-for-slot.  The dummy workstation is
;;; not entered into workstations-in-service nor does it have associated
;;; gensym-window's or G2-windows.  Cave canem.  Woof Woof!

(defmacro for-dummy-workstation (&body body)
  (let ((workstation (gensym)))
    `(let ((,workstation (get-or-make-dummy-workstation)))
       (with-named-dynamic-extent* for-workstation
	   (;; via for-workstation-polling
	    (current-workstation ,workstation)
	    (current-workstation-window
	      (window-for-workstation current-workstation))
	    (type-of-current-workstation-window nil)
	    (current-workstation-native-window? nil)
	    ;; via for-workstation-context 
	    (current-workstation-context
	      (car (workstation-context-stack current-workstation)))
	    (type-of-current-workstation-context
	      (type-of-workstation-context current-workstation-context))
	    (specific-structure-for-current-workstation-context
	      (specific-structure-for-workstation-context
		current-workstation-context))
	    ;; via for-workstation 
	    (current-workstation-detail-pane nil)
	    (current-g2-user-mode? 'administrator)
	    (servicing-workstation? T))
	 ,@body))))
       


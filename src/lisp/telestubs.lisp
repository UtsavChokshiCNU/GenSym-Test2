;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TELESTUBS -- Stubs to Support Telewindows

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Lowell B. Hawkinson, Brian Matthews, Fred White






;;;; Forward References


(declare-forward-references
  (check-shape-of-window-without-lookahead-for-g2
    function utilities4)
  (set-up-workstation-on-ab-side               function mice)
  (reclaim-panes-in-window                     function mice)
  (reclaim-mouse-pointers                      function mice)
  (reclaim-workstation-context-stack           function mice)
  (post-telewindows-connection-clogged         function debug)

  (handle-print-window-event                   function native-tw)
  (handle-about-box-event                      function dialogs)
  (nms-revert-to-unconnected-menu-bar          function native-tw)

  (get-g2-window-given-icp-socket              function workstation)
  (get-gensym-window-for-g2-window             function workstation)
  (g2-global-paint-mode-p                      function workstation)
  (absorb-local-event-ab-side                  function workstation)
  (absorb-local-event-ab-side-1                function workstation)
  (reclaim-workstation-event-queue             function workstation)
  (reclaim-non-kb-workspaces-for-this-workstation-only
    function workstation)

  (handle-paste-availability-event-in-g2       function edit2)
  (handle-paste-event-in-g2                    function edit2)

  (send-telewindows-workstation-event          function telewindows)
  (accept-telewindows-connection-license-level function telewindows)
  (accept-telewindows-connection-license-info  function telewindows)
  (accept-saved-user-settings-for-telewindows  function telewindows)
  (reroute-telewindows-connection              function telewindows)
  (paste-for-telewindows                       function telewindows)
  (reclaim-telewindows-workstation-function    function telewindows)
  (tw-handle-spawn-remote-command-line-process function telewindows)
  (tw-handle-spawn-remote-executable-process   function telewindows)
  (tw-handle-remote-process-exists-p           function telewindows)
  (tw-handle-kill-remote-process               function telewindows)
  (update-paste-availability-status-for-telewindows
    function telewindows)

  (g2-handle-spawn-remote-process-reply        function file-sysproc)
  (g2-handle-remote-process-exists-p-reply     function file-sysproc)
  (g2-handle-kill-remote-process-reply         function file-sysproc)

  (network-access-allowed-p                    function filters)

  (poll-player                                 function player)
  (player-state                                variable player))






;;;; Introduction


;;; This module is common to both Telewindows and G2.  Telestubs contains
;;; workstation event handling facilities that are in common to both Telewindows
;;; and G2, as well as a lot of other assorted stuff.

;; I have no idea why it is called telestubs.

;;; The substitution-macro `clobber-keypad-characters' converts keypad
;;; characters to their equivalents.  Since not all keyboard have
;;; distinguishable keypad chars, we don't want G2 to distinguish them
;;; for ANY keyboard.

(def-substitution-macro clobber-keypad-characters (key-code)
  (logiorf
    (key-modifier-bits key-code)
    (key-case (key-index key-code)
      (kp-space (key-code 'space))
      (kp-tab (key-code 'tab))
      (kp-enter (key-code 'enter))
      (kp-equal (key-code '=))
      (kp-multiply (key-code '*))
      (kp-add (key-code '+))
      (kp-subtract (key-code '-))
      (kp-decimal (key-code '\.))
      (kp-divide (key-code '/))
      (kp-separator (key-code '\,))
      (kp-0 (key-code '\0))
      (kp-1 (key-code '\1))
      (kp-2 (key-code '\2))
      (kp-3 (key-code '\3))
      (kp-4 (key-code '\4))
      (kp-5 (key-code '\5))
      (kp-6 (key-code '\6))
      (kp-7 (key-code '\7))
      (kp-8 (key-code '\8))
      (kp-9 (key-code '\9))
      (t key-code))))





;;; The function `backtranslate-key-code' transforms a modern key-code into one
;;; which a pre-4.0 G2 can understand.  Mostly, we collapse mouse buttons and
;;; add the control bit to the standard control chars.  Used only by a new
;;; telewindows.  An old telewindows talking to a new G2 can make itself
;;; understood without this kludgery.

(defun-simple backtranslate-key-code (key-code)
  ;; Change ALT to META, which is what G2 3.0 wants to see.
  (when (alternate-bit-on-p key-code)
    (setq key-code (logiorf meta-bit
			    (logandf key-code (lognotf alternate-bit)))))

  ;; Collapse numeric keypad keys to their regular equivalents.
  (setq key-code (clobber-keypad-characters key-code))

  (key-case key-code
    ;; First,  catch the control keys which we didn't change:
    ;; the few random keys in G2 3.0 which wanted the control-bit OFF:
    ;; c+m, c+h, c+i, and c+j.
    ((return control+m)
     (key-code '(control m)))

    ((backspace control+h)
     (key-code '(control h)))

    ((tab control+i)
     (key-code '(control i)))

    (<standard-newline-keys>
      (key-code '(control j)))

    (help						    ; A Gratuity
      (key-code '(control /)))
    (t
      (cond
	;; rather unlikely this code would be used (G2 3.0 w/TW 5.2), but I
	;; believe this would work well for Latin, and make incomprehensible,
	;; but harmless, codes up for most other scripts. (MHD 5/17/99)
	((unicode-bit-on-p key-code)
	 (key-unicode key-code))

	;; Otherwise, G2 3.0 expects its control characters
	;; to have the control bit set.  The pointless special cases of
	;; G2 3.0 was our motivation for changing key codes in 4.0
	((special-control-key-p key-code)
	 (logiorf key-code control-bit))

	;; Collapse all mouse buttons into one (including modified ones).
	((key-code-is-mouse-up-p key-code)
	 (key-code 'mouse-up))
	((key-code-is-mouse-down-p key-code)
	 (key-code 'mouse-down))
	((mouse-motion-event-p key-code)
	 (key-code 'mouse-motion))

	(t
	 key-code)))))



;;; The function `handle-event-in-telewindows-p' returns true if the event
;;; should be handled locally, by the telewindow process, rather than being sent
;;; to G2 as a telewindows-workstation-event.

(defun handle-event-in-telewindows-p (local-event)
  (or (=f (local-event-key-code local-event) (key-code 'print-window))
      (=f (local-event-key-code local-event) (key-code 'about-box))))


;;; The function `handle-event-in-telewindows' runs the TW-side event handler
;;; for given event.

(defun handle-event-in-telewindows (workstation key-code)
  (key-case key-code
    (print-window
      (handle-print-window-event workstation key-code))
    (about-box
      (handle-about-box-event workstation key-code))))

;; Telewindows does not have the usual G2 event handling mechanism, so we
;; dispatch these (few) events by hand.


;;; The icp-message-type `tw-command' allows G2 to execute TW-local commands.

(def-icp-message-type tw-command
    ((gensym-window gensym-window)
     (fixnum key-code))
  (handle-event-in-telewindows (workstation-this-is-on gensym-window) key-code))



;;;; Telewindows Copy and Paste Protocol

;; This section has some code that's for Telewindows only, some for G2 only, and
;; some for both.  It contains the definition of the "paste event queue", which
;; must preceed the definition of poll-workstation.

;;; Cut and Paste ICPs.
;;;
;;; The current TW has no knowledge of what is being clicked on, so there
;;; are a set of ICPs to handle cut, copy and paste between TW and G2.
;;; The ICP handlers on TW queue up paste events in a queue. These ICPs are
;;; outlined below. The quoted items below are cut/paste ICPs.
;;;
;;; ICP Handlers: are these called automatically? Seem to be according to
;;; icp-printing-message-handler-array in INT1.
;;;
;;;
;;; `request-paste-of-cut-buffer-text': from G2
;;;  ================================
;;; Sent by G2 when paste button (or menu option) pressed,
;;; TW handles by doing read-clipboard, then enqueueing into an event queue,
;;; (which triggers paste-from-telewindows-to-g2 on TW).
;;;
;;; G2:
;;; Sent in request-paste-for-editor in EDIT2 (no real logic: just call).
;;;
;;; request-paste-for-editor called by do-edit-subcommand, which looks like
;;; it may be called upon selecting an edit menu option.
;;;
;;; request-paste-for-editor also called by the ui-command paste (COMMANDS1),
;;; which I think is called when paste button pressed.
;;;
;;; TW:
;;; handler (TELESTUBS) does: (enqueue-local-paste-event (read-clipboard))
;;;
;;;
;;; `paste-from-telewindows-to-g2': from TW
;;;  ============================
;;; Sends the actual text from TW to G2.
;;; If TW sees something in paste event queue, send this IPC.
;;; G2 gets the text and enqueues a paste event.
;;;
;;; TW:
;;; poll-workstation (TELESTUBS):
;;; 	(if paste event queue non-empty
;;; 		handle-paste-event
;;; [paste event queue is non-empty only as a result of
;;;  request-paste-of-cut-buffer-text]
;;;
;;; handle-paste-event (TELESTUBS):
;;; 	 (if this-is-telewindows
;;; 	     (paste-for-telewindows gensym-window text-string request-id)
;;; 	     (handle-paste-event-in-g2 gensym-window text-string request-id timestamp))
;;; paste-for-telewindows (TELEWINDOWS):
;;; 	eventually calls send-icp-paste-from-telewindows-to-g2
;;;
;;; G2: handler (TELESTUBS) is
;;;     handle-paste-event-in-g2, which enqueues a workstation event
;;;	using the paste-request keycode. When workstation events are handled,
;;;	if an editor exists, then the private-editor-commands keymap
;;;	results in a call to paste-into-editor.
;;;
;;;
;;; NEW in 5.0r1:
;;; `request-paste-availability-status': from G2
;;;  =================================
;;; G2 sends to TW to request status of clipboard so it can decide
;;; whether to display paste button.
;;;
;;; G2 sends this ICP as soon as it knows a new editor is being
;;; displayed: in enter-editing-context (EDIT1):
;;; (if (window-supports-request-for-paste-availability
;;;       current-workstation-window)
;;; 	(request-paste-availability-for-editor))
;;;
;;; TW handler (TELESTUBS) similar to request-paste-of-cut-buffer-text
;;;
;;;
;;; `update-paste-availability-status': from TW
;;;  ================================
;;; Determines status of paste button.
;;; This is both an ICP message and a function.
;;;
;;; TW sends this ICP in poll-workstation (TELESTUBS)
;;; 	calls handle-paste-event;
;;; 	calls update-paste-availability-status fnc;
;;; 	      update-paste-availability-status-for-telewindows, etc.
;;;
;;; G2 handler (TELESTUBS) sets workstation-clipboard-has-text-p for this
;;;     window, then enqueues a workstation event using the
;;;	paste-availability-request keycode. When workstation events are handled,
;;;	if an editor exists, then the private-editor-commands keymap results
;;;	in a call to make-paste-menu-available.
;;;
;;;
;;; `copy-text-string-to-cut-buffer': from G2, presumably
;;;  ==============================
;;; When G2 gets a cut/copy motion (guessing), it sends this ICP with text.
;;; TW then writes text to clipboard.
;;;
;;; EDIT2
;;; G2: (guessing), if a cut/copy motion has just been done:
;;; 	if this window is an ICP type (that is, talking to TW)
;;; 	  then send this ICP message
;;; 	  else send ICP msg (to self? more magic).
;;;
;;; The handler for this takes its arg (a text-string) and writes it to the
;;; clipboard.
;;;
;;;
;;; `enable-or-disable-clipboard-polling': from G2 OBSELETE
;;;  ===================================
;;;
;;; TELESTUBS
;;;
;;; Used in start-or-stop-clipboard-polling. Start called in init
;;; (set-up-workstation-on-ab-side), stop never called. Could possibly use
;;; this to turn polling on and off.
;;;
;;; This is only called from G2 because set-up-workstation-on-ab-side is only
;;; defined by G2 (stubbed out by TW), and that is the only thing that
;;; calls start-clipboard-polling which is the only thing calling
;;; start-or-stop-clipboard-polling (except stop-clipboard-polling which has
;;; no callers).
;;;
;;; (LGibson 8/13/97)



(def-icp-message-type copy-text-string-to-cut-buffer
    (gensym-window text-string)
  (handle-copy-text-string-to-cut-buffer gensym-window text-string))

(defun handle-copy-text-string-to-cut-buffer (gensym-window text-string)
  (write-clipboard (native-window? gensym-window) text-string))

(defun copy-text-string-to-cut-buffer (gensym-window text-string)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-copy-text-string-to-cut-buffer
	 gensym-window text-string)))
    (t
     (handle-copy-text-string-to-cut-buffer
       gensym-window text-string))))



;;; `Request-paste-of-cut-buffer-text' and `request-paste-availability-status'
;;; Request-id should either be a positive integer that uniquely identifies a
;;; specific request, or zero, to indicate that there no specific request (or
;;; that no protocol for identifying requests exists in this case).

(def-icp-message-type request-paste-of-cut-buffer-text
    (gensym-window (integer request-id))
  (handle-request-paste-of-cut-buffer-text gensym-window request-id))

(defun handle-request-paste-of-cut-buffer-text (gensym-window request-id)
  (enqueue-local-paste-event
    (native-window? gensym-window)
    (read-clipboard (native-window? gensym-window))
    request-id))

(defun request-paste-of-cut-buffer-text (gensym-window request-id)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-request-paste-of-cut-buffer-text gensym-window request-id)))
    (t
     (handle-request-paste-of-cut-buffer-text gensym-window request-id))))


(defun enqueue-local-paste-event (native-window text-string request-id)
  (enqueue-window-paste-event
    native-window
    (key-code 'paste-request)
    (c-x11-last-event-time native-window)
    text-string request-id))


(def-icp-message-type request-paste-availability-status
    (gensym-window (integer request-id))
  (handle-request-paste-availability-status gensym-window request-id))

(defun handle-request-paste-availability-status (gensym-window request-id)
  (enqueue-local-paste-availability-event
    (native-window? gensym-window)
    (local-clipboard-has-text-p gensym-window)
    request-id))

(defun request-paste-availability-status (gensym-window request-id)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-request-paste-availability-status gensym-window request-id)))
    (t
     (handle-request-paste-availability-status gensym-window request-id))))



(defun enqueue-local-paste-availability-event (native-window paste-available-p request-id)
  (enqueue-window-paste-event
    native-window
    (key-code 'paste-availability-request)
    (c-x11-last-event-time native-window)
    paste-available-p request-id))


(def-system-variable local-paste-event-queue telestubs
  (:funcall make-queue))


(defmacro local-paste-event-queue (native-window?)
  `(or (get-paste-event-queue-of-native-window ,native-window?)
       local-paste-event-queue))


(defun enqueue-window-paste-event
    (native-window key-code timestamp text-string request-id)
  (let ((local-event (make-local-event)))
    (setf (local-event-key-code local-event) key-code
	  (local-event-timestamp local-event) timestamp
	  (local-event-cursor-x local-event) nil ; include later!
	  (local-event-cursor-y local-event) nil
	  (local-event-right local-event) nil ; not applicable
	  (local-event-bottom local-event) nil
	  (local-event-plist local-event)
	  (gensym-list
	    'text-string text-string ; might be clipboard text or paste status
	    'request-id request-id))
    (queue-insert (local-paste-event-queue native-window)
		  local-event)))


(defun handle-paste-event (gensym-window native-window)
  (declare (ignore native-window))	; no longer needed. (MHD 1/22/02)
  (let ((paste-event?			; always there, but not assumed
	  (queue-pop (paste-event-queue gensym-window)))
	(this-is-telewindows
	  (eq current-system-name 'telewindows)))
    (cond
      (paste-event?
       (let* ((event-code (local-event-key-code paste-event?))
	      (text-string-or-paste-p	   ; gets reclaimed with the event
		(getf (local-event-plist paste-event?) 'text-string))
	      (timestamp (local-event-timestamp paste-event?))
	      (request-id
		(getf (local-event-plist paste-event?) 'request-id)))
	 (cond ((eq event-code (key-code 'paste-availability-request))
		(when (notify-if-clipboard-has-text-p current-workstation)
		  (update-paste-availability-status
		    current-workstation-window text-string-or-paste-p timestamp)))
	       ((eq event-code (key-code 'paste-request))
		(if this-is-telewindows
		    (paste-for-telewindows gensym-window text-string-or-paste-p request-id)
		    (handle-paste-event-in-g2 gensym-window text-string-or-paste-p
					      request-id timestamp))))
	 (reclaim-local-event paste-event?))
       T)   ; T indicates we handled a paste event
      (t nil))))

;; TW used to cache the paste availability status that it sent to G2, but
;; this is no longer correct as G2 can decide that there is something in the
;; windows' clipboard when it does a cut/copy.

;;; `Paste-from-telewindows-to-g2'  This defines the function
;;; `handle-icp-paste-from-telewindows-to-g2', which manages the final
;;; conveyance of the text string from the network layer at the G2 side into the
;;; editor.  This also defines the function
;;; `send-icp-paste-from-telewindows-to-g2', which conveys the text from
;;; Telewindows to G2 via ICP.  Both functions do not reclaim their text-string
;;; argument.  The interface to the send function is via paste-for-telewindows,
;;; which is defined only for Telewindows; see the TELEWINDOWS module.

(def-icp-message-type paste-from-telewindows-to-g2
    (gensym-window text-string (integer request-id))
  (handle-paste-event-in-g2 gensym-window text-string request-id nil))


;;; `Local-clipboard-has-text-p' returns true for a gensym window whose type
;;; is X11 (native) window, and whose clipboard has text available to be
;;; pasted. Otherwise, it returns false (nil).  Unless the parameter
;;; `recheck-if-clipboard-has-text?' is true this will just return true if
;;; gensym-window was previously found to have clipboard text.  The Clipboard
;;; can be cleared (least on X) by terminating the Clipboard owner
;;; (e.g. Netscape).

(defparameter recheck-if-clipboard-has-text? t)

;; We are adding a new feature that the paste button will reflect the current
;; status of the clipboard, so changing this parameter to true.


(defun-simple local-clipboard-has-text-p (gensym-window)
  (or (unless recheck-if-clipboard-has-text?
	(workstation-clipboard-has-text-p
	  (workstation-this-is-on gensym-window)))
      (case (type-of-gensym-window gensym-window)
	(x11-window
	 (if (=f 0
		 (c-x11-clipboard-has-text
		   (native-window? gensym-window)))
	     nil
	     t)))))



(defun update-paste-availability-status (gensym-window status timestamp)
  (let ((this-is-telewindows
	  (eq current-system-name 'telewindows)))
    (cond
      (this-is-telewindows
       (update-paste-availability-status-for-telewindows
	 gensym-window status))
      (t
       (handle-paste-availability-event-in-g2
	 gensym-window status timestamp)))))


;;; Update-paste-availability-status ... Note that the handler is
;;; ONLY called on the G2 side.

(def-icp-message-type update-paste-availability-status
    (gensym-window (boolean status))
  (handle-paste-availability-event-in-g2 gensym-window status nil))


;; begin obselete section
;; clipboard polling is obselete and needs to be removed.

;;; `enable-or-disable-clipboard-polling' is called only
;;; from G2 (5.0, post Beta 0, or later).  It merely sets the flag in
;;; the workstation corresponding to gensym-window indicating an interest
;;; in updates when the availability of clipboard text changes.  The actual
;;; work of checking the availability, and then notifying G2, happens in
;;; poll-workstation.

(def-icp-message-type enable-or-disable-clipboard-polling
    (gensym-window (boolean enable-p))
  (enable-or-disable-clipboard-polling-in-gensym-window
    gensym-window enable-p))

(defun enable-or-disable-clipboard-polling-in-gensym-window
    (gensym-window enable-p)
  (let ((workstation (workstation-this-is-on gensym-window)))
    (setf (notify-if-clipboard-has-text-p workstation) enable-p)))


;;; `Start-clipboard-polling' and `stop-clipboard-polling' are called from
;;; workstation contexts, e.g., the editor, that need the clipboard to be
;;; polled.  These functions enable and disable, respectively, the service
;;; available (at least as of Telewindow 5.0) of notifying G2 when the clipboard
;;; has text available for pasting.  However, it may also be reasonable just to
;;; turn on clipboard polling unconditionally; this is now what is done; see
;;; set-up-workstation-on-ab-side.  Note, however, that this is only done by 5.0
;;; G2's; therefore, this will never be called if Telewindows 5.0 is talking to
;;; a G2 4.0.  Therefore, none of the paste notification messages will be
;;; (illegally) invoked given that configuration, which is a good thing.
;;;
;;; Note that this simply notifies G2 of the availability of clipboard text; it
;;; does not send any.  This is very low on information.

(defun start-clipboard-polling (gensym-window)
  (start-or-stop-clipboard-polling gensym-window t))

(defun stop-clipboard-polling (gensym-window)
  (start-or-stop-clipboard-polling gensym-window nil))

(defun start-or-stop-clipboard-polling (gensym-window start-p)
  (when (window-supports-native-cut-and-paste gensym-window)
    (case (type-of-gensym-window gensym-window)
      (icp
       (with-icp-window (gensym-window)
	 (send-icp-enable-or-disable-clipboard-polling
	   gensym-window start-p)))
      (t
       (enable-or-disable-clipboard-polling-in-gensym-window
	 gensym-window start-p)))))

;; end of obselete section



;;;; Polling Workstations


;;; `Poll-workstation' gets one or more external events and merges them into the
;;; workstation event queue for the current workstation.  It must be called in
;;; an for-workstation or for-workstation-polling context.  If it succeeds in
;;; enqueuing any events into the workstation it returns T.  If it queues a
;;; reshape event, but no ordinary events, it returns 'RESHAPE.  Otherwise, it
;;; returns nil.

;;; This returns immediately if the type-of-current-workstation-window
;;; is neither NATIVE, or X11-WINDOW (e.g. it is ICP).  In consequence this
;;; routine only does real work for the "local" window of the process.

;;; First it handles directly any window reshape events.

;;; It calls an OS routine to obtain any outstanding events.  For X11 windows,
;;; get-all-x11-events is called.

;;; A call, if approprate, is made to the player to let it enqueue a few events.

;;; Mouse motion events are discarded if we aren't tracking the mouse.
;;; Sequences of mouse motion events are collapsed, passing only the last of the
;;; sequence on.

;;; If no events are found, and the workstation is mouse-tracking then a
;;; synthetic mouse motion event is generated.

;;; In a Telewindows the events are sent up the ICP link, in a G2 they are
;;; enqueued into the workstation's event queue.

(defun poll-workstation ()
  (with-backtrace-for-internal-error 'poll-workstation
    #+development (update-pseudo-run-lights :poll-workstation)
    #+development
    (when (within-window-drawing-context-p)  ;; Note A
      (cerror "Proceed"
	      "Poll-workstation is risky to call when on-window-with-drawing."))
    (when (eq type-of-current-workstation-window 'x11-window)
      (let ((this-is-telewindows
	      (slave-gensym-window? current-workstation-window))
	    (talking-to-an-old-g2
	      (talking-to-a-pre-version-4-g2-p current-workstation-window))
	    (allow-mouse-hover-events-p
	      (window-supports-mouse-hover-events-p current-workstation-window))
	    (any-events? nil))				    ; return value

	;; Shift OS events into local event queue.
	(get-all-x11-events current-workstation-native-window?)

	;; Service the needs of the Cut&Paste protocol:   (New for 5.0.)
	;; Note: the availabilty of clipboard text should ideally be an
	;; event that triggers G2/TW's event-driven scheduling loop.
	;; However, for the C code to notice paste availability would be
	;; complex and cumbersome (would have to watch the X root window
	;; and look at all the events, picking out the setClipboardOwner
	;; events).
	;; New in 5.0 rev.1: instead of having TW constantly send paste
	;; availability to G2, have G2 request it. (lgibson 8/5/97)

	(when (queue-non-empty-p-macro
		(paste-event-queue current-workstation-window))
	  (when (handle-paste-event
		  current-workstation-window
		  current-workstation-native-window?)
	    (setq any-events? 'paste))) ; return value good enough if non-nil

	(when (queue-non-empty-p-macro
		(reshape-event-queue current-workstation-window))
	  (when (if this-is-telewindows
		    (check-shape-of-window-without-lookahead
		      current-workstation-window
		      current-workstation-native-window?)
		    (check-shape-of-window-without-lookahead-for-g2
		      current-workstation-window
		      current-workstation-native-window?))
	    (setq any-events? 'reshape)))

	;; Let the player slip in some events?
	(unless this-is-telewindows
	  (when (eq player-state 'running)
	    (poll-player)))

	;; Something to synch autorepeat, see mouse-tracking, and
	;; native-window-polling-interval.
	(unless talking-to-an-old-g2
	  (when (consider-synthetic-motion-event? current-workstation)
	    (setf (consider-synthetic-motion-event? current-workstation) nil)
	    (when (and (tracking-mouse? current-workstation)
		       (queue-empty-p
			 (event-queue current-workstation-window))
		       (if this-is-telewindows
			   (time-for-another-synthetic-motion-event?)
			   t))
	      ;; Getting the actual event-time and mouse location
	      ;; is was too hard in X?
	      #+development (update-pseudo-run-lights :synthetic-mouse-motion)
	      (enqueue-local-event
		current-workstation-native-window?
		(mouse-motion-key-code (c-x11-last-event-bits current-workstation-native-window?))
		(c-x11-last-mouse-x-position current-workstation-native-window?)
		(c-x11-last-mouse-y-position current-workstation-native-window?)
		(c-x11-last-event-time current-workstation-native-window?)))))
	
	
	;; Shift local event queue into workstation event queue or ICP stream.
	(loop for event? = (dequeue-local-event-if-any current-workstation-native-window?)
	      while event?
	      as key-code = (local-event-key-code event?)
	      doing

	  ;; Merge or discard mouse motions.
	  (when (mouse-motion-event-p key-code)
	    (setq event?
		  (cond ((tracking-mouse? current-workstation)
			 (requeue-local-event current-workstation-native-window? event?)
			 (get-last-local-mouse-motion-event
			   current-workstation-native-window?))
			(t
			 (reclaim-local-event event?)
			 nil))))

	  ;; Discard mouse hover events if the G2 doesn't support them.
	  (when (and (mouse-hover-event-p key-code)
		     (not allow-mouse-hover-events-p))
	    (setq event? nil))

	  (when event?
	    (setf (x-in-window-of-mouse? current-workstation) (local-event-cursor-x event?))
	    (setf (y-in-window-of-mouse? current-workstation) (local-event-cursor-y event?))
	    (setq any-events? t)
	    (cond
	      (this-is-telewindows
	       #+development
	       (when trace-local-events
		 (trace-local-event (pretty-type-of-gensym-window
				      current-workstation-window)
		       (local-event-key-code event?)
		       (local-event-cursor-x event?)
		       (local-event-cursor-y event?)
		       (local-event-timestamp event?)
		       (local-event-plist event?)))

	       (when talking-to-an-old-g2
		 (let ((new-key-code (backtranslate-key-code key-code)))
		   #+development
		   (when (and trace-local-events
			      (not (equal key-code new-key-code)))
		     (format t "    Backtranslated key-code to ~a~%"
			     (symbol-from-key-code new-key-code)))
		   (setf key-code new-key-code
			 (local-event-key-code event?) key-code)))

	       (cond
		 #+development
		 ((or (key-code-equal key-code 'pause) ; Pause/Break key
		      (key-code-equal key-code 'break) ; LispM only?!
		      (key-code-equal key-code '(control |~~|))) ; Ctrl+tilde
		  (run-break-loop current-workstation-window))
		 ((handle-event-in-telewindows-p event?)
		  (handle-event-in-telewindows current-workstation
					       (local-event-key-code event?)))
		 (t
		  (send-telewindows-workstation-event current-workstation event?))))

	      (t						    ; G2 case:
	       (absorb-local-event-ab-side event?)))
	    (reclaim-local-event event?)))

	any-events?))))


;;; poll-native-window-workstation is used by netevent.lisp to handle incoming
;;; display events without calling the G2 scheduler.  Calling the scheduler also
;;; accomplishes this work; but it has higher overhead and cannot be called in
;;; nested event loops (ala Foreign Functions) where the thread may already be
;;; inside the G2 stack evaluator.  This function cannot invoke the stack
;;; evaluator.  -ncc, 11 Aug 1997
(defun-void poll-native-window-workstation ()
  (loop for workstation in workstations-in-service
	when (native-window? (window-for-workstation workstation))
	  do (for-workstation-polling (workstation)
	       (poll-workstation))))

;; Fixed not to use system-window, which should generally not be used.  If we
;; ever want multiple native windows to work for G2 or Telewindows, having the
;; system use system-window is generally bad.  Note: this potentially could have
;; an avoidable performance problem if there are very large numbers of
;; workstations in service but few are local native windows (in a G2 server);
;; consider having a more efficient means to access the locals, e.g., a separate
;; list or local native windows in service. (MHD 3/1/01)

;; Historical notes: This routine once had huge variations for multiple
;; platforms.  It once had a way to turn VT100 arrow key escapes into cursor
;; key-codes.  It once had a way to make meta keys by prefixing them with
;; escape.  It is unclear how much of this stuff worked reliably.  - ben 11/25/93

;; Note A: The reshape can Q drawing work, something you may not do when already
;; drawing.


;;; `time-for-another-synthetic-motion-event?' is used only under Telewindows,
;;; it acts to assure we don't generate synthetic-motion-events faster than
;;; about one every third of a second.

(defvar time-of-last-synthetic-motion-event? nil)

(defun time-for-another-synthetic-motion-event? ()
  (with-temporary-gensym-float-creation time-for-another-synthetic-motion-event?
    (let ((now (gensym-get-unix-time)))
      (declare (type gensym-float now))
      (cond
	((null time-of-last-synthetic-motion-event?)
	 (setf time-of-last-synthetic-motion-event?
	       (allocate-managed-float now))
	 t)
	((<=e (+e (managed-float-value time-of-last-synthetic-motion-event?)
		  .3)
	      now)
	 (setf (managed-float-value time-of-last-synthetic-motion-event?)
	       now)
	 t)
	(t
	 nil)))))

;; Non-unix platforms still poll, so even if we license idle-process to sleep
;; long enough we need this to throttle back. - ben Jul 13, 95





;;;; Telewindows Interface to Workstations






;;; This transcript illustrates a TW connecting into an AB.
;;; It is not the only possible transcript since when each
;;; side of the wire gets cycles can make things vary.

;;; 1. A TW introduces himself.
;;;   TW define-telewindows-workstation -S>
;;;   TW define-gensym-window           -S>
;;;   TW initialize-telewindows-workstation -S>
;;;   TW message-group-id            -S>
;;; 2. G2 Notices that input.
;;;   AB                             -R> define-telewindows-workstation
;;;   AB                             -R> define-gensym-window
;;;   AB                             -R> initialize-telewindows-workstation
;;; 3. G2 responds by creating the window and painting the initial screen.
;;;   AB                             <S- define-gensym-window
;;;   AB                             <S- set-window-protocol-version (G2 4.0 only)
;;;   AB                             <S- begin-window-update
;;;   AB                             <S- paint-solid-rectangle-in-current-window
;;;   AB                             <S- paint-solid-rectangle-in-current-window
;;;   AB                             <S- paint-solid-rectangle-in-current-window
;;;   AB                             <S- paint-solid-rectangle-in-current-window
;;;   AB                             <S- begin-window-update
;;;   AB                             <S- begin-window-update
;;;   AB                             <S- make-tiling-pattern
;;;   AB                             <S- copy-from-tiling-pattern-to-current-window
;;; 4. Finally G2 notices the end of the intial mssage group.
;;;   AB                             -R> message-group-id
;;; 5. The TW recieves, and presumably draws the initial window.
;;;   TW define-gensym-window        <R-
;;;   TW begin-window-update         <R-
;;;   TW paint-solid-rectangle-in-current-window <R-
;;;   TW paint-solid-rectangle-in-current-window <R-
;;;   TW paint-solid-rectangle-in-current-window <R-
;;;   TW paint-solid-rectangle-in-current-window <R-
;;;   TW begin-window-update         <R-
;;;   TW begin-window-update         <R-
;;;   TW make-tiling-pattern         <R-
;;;   TW copy-from-tiling-pattern-to-current-window   <R-



;;; We will need to define the workstation as a telewindows corresponding object.
;;; User event polling will occur at the remote node. The remote node will send
;;; the user events to the proper workstation.


(def-icp-object-type workstation
  (standard-icp-object-index-space
   (corresponding-icp-object-map-for-workstation workstation))
  (send-icp-define-telewindows-workstation corresponding-icp-object-index))



(def-icp-message-type define-telewindows-workstation
                      (corresponding-icp-object-index)
  (receive-initial-message 'g2 'telewindows)
  (store-corresponding-icp-object
    corresponding-icp-object-index
    (make-workstation nil)))



(def-icp-value-type-equivalence icp-window-protocol-version unsigned-integer)

;;; `Set-window-protocol-version' is passed from G2 to Telewindows when G2
;;; has determined the maximum protocol level the Telewindows may utilize.
;;; See obtain-max-window-protocol.

(def-icp-message-type set-window-protocol-version
    (gensym-window icp-window-protocol-version)
  (setf (icp-window-protocol-version gensym-window)
	icp-window-protocol-version)
  (when (current-window-supports-this-icp-window-protocol-p
	  icp-window-protocol-supports-transparent-copy
	  gensym-window)
    (setf (drawing-transfer-mode-of-gensym-window gensym-window)
	  :paint-infered-from-xor))
  ;; Call this early in the connection process. This calls
  ;; initialize-gensym-window-after-connection if the version of the remote G2
  ;; is acceptable. Also called from ICP make-tiling-pattern, but that ICP
  ;; message isn't always sent.
  (telewindows-check-version-of-remote-g2 gensym-window))




(def-icp-value-type-equivalence icp-drawing-transfer-mode unsigned-integer)

;;; `Set-transfer-mode' is used by G2 to notify a Telewindow's to rebind
;;; current-drawing-transfer-mode.  It maybe used only if the protocol
;;; level is at least "icp-window-protocol-supports-transparent-copy."

(def-icp-message-type set-transfer-mode (icp-drawing-transfer-mode)
  (setf current-drawing-transfer-mode
	(case (logandf icp-drawing-transfer-mode 1)	    ; Low bit is mode.
	  (0 :xor)
	  (1 :paint-infered-from-xor))))



;;; `Set-background-color-value' is used by G2 to notify a Telewindows's to
;;; rebind current-background-color-vlaue.  It maybe used only if the protocol
;;; level is at least "icp-window-protocol-supports-transparent-copy."

(def-icp-message-type set-background-color-value (color-value)
  (setf current-background-color-value color-value))






;;; `Set-window-license-level' sets up the license level for gensym-window.
;;; `License-level' is an integer with values as follows:
;;;
;;;    -2 (unauthorized)
;;;    -1 (floating)
;;;    0 (embedded)
;;;    1 (runtime)
;;;    2 (restricted-use)
;;;    3 (development)

(def-icp-value-type-equivalence license-level integer)

(def-icp-message-type set-window-license-level
    (gensym-window license-level)
  (accept-telewindows-connection-license-level gensym-window license-level))



;;; `Set-telewindows-connection-license-info' ... is the successor to
;;; set-window-license-level, which is now obsolete, but is harmless and still
;;; may be used.

(def-icp-message-type set-telewindows-connection-license-info
    (gensym-window
      (list telewindows-connection-license-info))
  (accept-telewindows-connection-license-info
    gensym-window
    telewindows-connection-license-info))





;;; The function `offer-g2-user-settings-back-to-telewindows' sets the
;;; properties given in plist (a gensym-list of symbols and fixnums), plus other
;;; useful properties, in the remote Telewindow.

(defun offer-g2-user-settings-back-to-telewindows (workstation plist)
  (when (icp-window-protocol-supports-saving-user-settings-p
	  (window-for-workstation workstation))
    (let* ((gensym-window (window-for-workstation workstation))
	   (augmented-plist
	     (nconc (gensym-list 'session-id (gensym-window-session-id gensym-window))
		    (copy-list-using-gensym-conses plist))))
      (with-icp-window (gensym-window)
	(send-icp-save-user-settings-for-telewindows gensym-window augmented-plist))
      (reclaim-gensym-list augmented-plist))))

(def-icp-message-type save-user-settings-for-telewindows
    (gensym-window (list user-settings-plist))
  (accept-saved-user-settings-for-telewindows ; Is user-settings-plist ever reclaimed?
    gensym-window
    user-settings-plist))


;;;; Servicing Workstations



;;; `Initialize-telewindows-workstation' creates the corresponding workstation on
;;; the G2 side and initializes it to be processed in the G2 scheduler loop.
;;; The window slot of the workstation is initialized with a window of type ICP.
;;; Note that the window-parameters-plist for the telewindows window is
;;; transmitted over from the remote telewindows window.

(defun initialize-workstation (workstation gensym-window v5-mode-p)
  (cond
    ((permit-connection-from-telewindows-p gensym-window)
     (lay-out-window gensym-window)
     (refresh-window gensym-window)
     (setf (window-for-workstation workstation) gensym-window)
     (set-up-workstation-on-ab-side workstation gensym-window v5-mode-p)
     (let* ((icp-port?
	      (icp-output-port-for-window? gensym-window))
	    (icp-socket?
	      (and icp-port? (parent-icp-socket icp-port?))))
       (when icp-socket?				    ; Should always be the case.
	 (register-icp-callback 'icp-connection-loss
	   'close-telewindows-callback icp-socket?)
	 (setf (icp-socket-listener-client? icp-socket?) 'telewindows)
	 (setf (icp-socket-workstation icp-socket?) workstation)
	 (register-icp-callback 'icp-write 'telewindows-write-state-change icp-socket?)
	 (initialize-g2-process-telewindows-icp-socket icp-socket?))))
    ((network-access-allowed-p 'telewindows 'connect)
     (reject-telewindows-connection gensym-window))
    (t (disallow-new-icp-listener-connection current-icp-socket))))

(def-icp-message-type initialize-telewindows-workstation
		      (workstation gensym-window)
  ;; Always sent from TELEWINDOWS and handled in G2:
  ;; The TW version has already been negotiated at this point.
  (initialize-workstation workstation gensym-window nil))

(def-icp-message-type initialize-ntw-workstation
    (workstation gensym-window)
  (initialize-workstation workstation gensym-window t))

(defun telewindows-write-state-change (icp-socket writable-p)
  (current-system-case
    (ab
      (when writable-p
	(let ((workstation (icp-socket-workstation icp-socket)))
	  (when workstation
	    (maybe-schedule-service-workstation workstation t)))))
    (t icp-socket writable-p nil)))

(defun-void reclaim-workstation-tasks (workstation)
  (cancel-task (current-task-to-run-service-workstation workstation))
  (cancel-task (future-task-to-run-service-workstation workstation))
  (cancel-task (selection-callbacks-task workstation)))


;;; The function `permit-connection-from-telewindows-p' determines whether to
;;; allow a connection from a telewindows on the given gensym-window.  We
;;; disallow connections from telewindows earlier than 4.0 by checking that it
;;; supports scrolling.

;;; We also disallow certain prerelease versions, to promote stability and avoid
;;; the need to test with such "mutant" versions.  Currently, the only
;;; prerelease version we ban is the 7.0 prerelease: 7.0 alpha, beta, and r0
;;; candidates.  We also ban 7.0 telewindows that use the -ui multiwindow
;;; command line option (including alpha and candidate versions of 7.1r0, which
;;; had supported this option).

(defun permit-connection-from-telewindows-p (gensym-window)
  (and (eq current-system-name 'ab)
       (network-access-allowed-p 'telewindows 'connect)
       (null (reason-to-reject-telewindows-connection gensym-window))))

;; Current-system-name is checked here to prevent connecting a Telewindows to
;; another Telewindows.

(defun reason-to-reject-telewindows-connection (gensym-window)
  (cond ((not (current-window-supports-this-icp-window-protocol-p
		icp-window-protocol-supports-scrolling
		gensym-window))
	 "pre-4.0 version")
	((current-window-icp-window-protocol-70-prerelease-p gensym-window)
	 "7.0 prerelease version")
	((old-style-mdi-frame-p gensym-window)
	 "7.0 with the '-ui multiwindow' command line option")
	((twng-p gensym-window)
	 (unless (window-supports-chart-views-in-panes gensym-window)
	   "pre-8.3r0 TWNG"))
	((multiwindow-option-p gensym-window)
	 "TW in multiwindow mode")))

;; There should be a way to give a reason for the rejection at the TW side!
(defun reject-telewindows-connection (gensym-window)
  (notify-user-at-console-and-on-logbook
    "G2 rejected a connection from an unsupported Telewindows: ~a."
    (reason-to-reject-telewindows-connection gensym-window))
  (close-telewindows-connection-internal gensym-window))


;;; The function `talking-to-a-pre-version-4-g2-p' returns T if we are talking
;;; to a pre-4.0 G2, or, if we are so early in the connection process that the
;;; window protocol has not yet been determined.  The window protocol is
;;; reliable after G2 has sent the set-window-protocol message.

(defun talking-to-a-pre-version-4-g2-p (gensym-window)
  (<=f (icp-window-protocol-version gensym-window)
       icp-window-protocol-supports-scrolling))


(defun window-supports-mouse-hover-events-p (gensym-window)
  (window-supports-views-in-listbars gensym-window)) ; 8.3b0


(def-icp-value-type-equivalence event-code integer)	; needs 24 bits




;;; The icp-message-type `telewindows-workstation-event' is sent by telewindows
;;; to G2 for every mouse or keyboard event.

(def-icp-message-type telewindows-workstation-event
    (workstation event-code
		 (coordinate x) (coordinate y)
		 (unsigned-integer timestamp))
  (receive-telewindows-workstation-event-for-g2
    workstation event-code x y timestamp))

;; Note: When a 3.0 telewindows tries to connect to a 4.0 G2, we shut down the
;; connection inside of initialize-telewindows-workstation, which sets the
;; workstation's window back to NIL, and kills the ICP connection.
;; Unfortunately, this doesn't flush the queue of incoming messages entirely.
;; There may be some workstation events still in the queue, which will be
;; processed as usual.  Hopefully, the only possible queued up event is
;; telewindows-workstation-event, so that the one test for NIL here will
;; suffice.

;; Since we're about to refuse the connection from 3.0 anyways, just ignore
;; this event. However, since the remote telewindows never gets a chance
;; to send us close-telewindows-connection, I believe that we leak a
;; workstation object in this case.  -fmw, 11/18/9



;;; `Extended-telewindows-workstation-event' ... event-plist is an ICP list, and
;;; its elements may only be symbols, text strings, or integers.

(def-icp-message-type extended-telewindows-workstation-event
    (workstation event-code
		 (coordinate x) (coordinate y)
		 (unsigned-integer timestamp)
		 (list event-plist))
  (receive-telewindows-workstation-event-for-g2
    workstation event-code x y timestamp event-plist))



;;; `Receive-telewindows-workstation-event-for-g2' ... This function takes
;;; ownership of the event-plist (it is not copied).

(defun receive-telewindows-workstation-event-for-g2
    (workstation event-code x y timestamp &optional event-plist)
  (setf (x-in-window-of-mouse? workstation) x)  ; do only when tracking?
  (setf (y-in-window-of-mouse? workstation) y)
  (when (window-for-workstation workstation)
    (absorb-local-event-ab-side-1 workstation event-code x y timestamp event-plist)))



;;; The following icp message types,
;;;
;;;   `start-mouse-tracking-in-window',
;;;   `stop-mouse-tracking-in-window',
;;;   `set-position-of-mouse-in-window', and
;;;   `shift-position-of-mouse-in-window'
;;;
;;; are new ICP message types in G2/TW 4.0 Beta Rev. > 0.
;;;
;;; They replace, respectively, the following icp message types:
;;;
;;;    `telewindows-start-mouse-tracking',
;;;    `telewindows-stop-mouse-tracking',
;;;    `set-position-of-mouse', and
;;;    `shift-position-of-mouse'
;;;
;;; which can only now be sent by G2/TW 4.0 Beta Rev. 0 or earlier.

(def-icp-message-type telewindows-start-mouse-tracking ()
  (start-mouse-tracking-in-window current-workstation-window))

(def-icp-message-type start-mouse-tracking-in-window (gensym-window)
  (handle-start-mouse-tracking-in-window gensym-window))

(defun handle-start-mouse-tracking-in-window (gensym-window)
  (setf (tracking-mouse? (workstation-this-is-on gensym-window)) t)
  (start-mouse-tracking (native-window? gensym-window))
  ;; G2 3.0 requires that a mouse-motion event is sent back.
  (when (talking-to-a-pre-version-4-g2-p gensym-window)
    (push-back-telewindows-mouse-motion-event gensym-window)))

(defun start-mouse-tracking-in-window (gensym-window)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window-if-needed (gensym-window)
       (send-icp-start-mouse-tracking-in-window gensym-window)))
    (t
     (handle-start-mouse-tracking-in-window gensym-window))))


(defun push-back-telewindows-mouse-motion-event (gensym-window)
  (let* ((native-window (native-window? gensym-window))
	 (mouse-x (c-x11-get-mouse-x-position native-window))
	 (mouse-y (c-x11-last-mouse-y-position native-window)) ; see note 2
	 (bits (c-x11-last-event-bits native-window)))

    (setf (x-in-window-of-mouse? (workstation-this-is-on gensym-window))
	  mouse-x)
    (setf (y-in-window-of-mouse? (workstation-this-is-on gensym-window))
	  mouse-y)
    (enqueue-local-event				    ; Was merge-local-event
      native-window
      (mouse-motion-key-code bits)
      mouse-x mouse-y
      (c-x11-last-event-time native-window))
    (current-system-case
      (ab (maybe-schedule-service-workstation nil t)))))

;; Note 1: I added the modifier bits for mouse-motion. -fmw, 4/13/95

;; Note 2: per protocol defined by c-x11-get-mouse-x-position, you get get the
;; mouse-y position by getting the last mouse y after a ...-get-mouse-x-....



(def-icp-message-type telewindows-stop-mouse-tracking ()
  (stop-mouse-tracking-in-window current-workstation-window))

(def-icp-message-type stop-mouse-tracking-in-window (gensym-window)
  (handle-stop-mouse-tracking-in-window gensym-window))

(defun handle-stop-mouse-tracking-in-window (gensym-window)
  (setf (tracking-mouse? (workstation-this-is-on gensym-window)) nil)
  (stop-mouse-tracking-in-local-window gensym-window))

(defun stop-mouse-tracking-in-window (gensym-window)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-stop-mouse-tracking-in-window gensym-window)))
    (t
     (handle-stop-mouse-tracking-in-window gensym-window))))




;;; The function `stop-mouse-tracking-in-native-window' turns off local mouse
;;; tracking and cleanses the local event queue of any remaining motion events.

(defun stop-mouse-tracking-in-local-window (gensym-window)
  (stop-mouse-tracking (native-window? gensym-window))
  (let ((event?
	  (get-last-local-mouse-motion-event
	    (native-window? gensym-window))))
    (when event?
      (reclaim-local-event event?))))




(def-icp-message-type set-position-of-mouse ((coordinate x) (coordinate y))
  (set-position-of-mouse x y))

(def-icp-message-type set-position-of-mouse-in-window
    (gensym-window (coordinate x) (coordinate y))
  (handle-set-position-of-mouse-in-window gensym-window x y))

(defun handle-set-position-of-mouse-in-window (gensym-window x y)
  ;; Note it locally:
  (setf (x-in-window-of-mouse? (workstation-this-is-on gensym-window)) x
	(y-in-window-of-mouse? (workstation-this-is-on gensym-window)) y)
  (c-x11-move-pointer (native-window? gensym-window) x y)
  nil)

(defun set-position-of-mouse-in-window (gensym-window x y)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-set-position-of-mouse-in-window gensym-window x y)))
    (t
     (handle-set-position-of-mouse-in-window gensym-window x y))))



;;; The function `set-position-of-mouse' warps the mouse for the current
;;; workstation window to x, y, and also updates the local current workstation
;;; structure's model of where the mouse is.  This must be called in a
;;; for-workstation context.

(defun set-position-of-mouse (x y)
  ;; Note it locally.
  (setf (x-in-window-of-mouse? current-workstation) x
	(y-in-window-of-mouse? current-workstation) y)
  (case (type-of-gensym-window current-workstation-window)
    (icp
     (with-icp-window (current-workstation-window)
       (set-position-of-mouse-in-window current-workstation-window x y)))
    (t
     (set-position-of-mouse-in-window current-workstation-window x y))))




(def-icp-message-type shift-position-of-mouse
		      ((integer delta-x) (integer delta-y))
  (shift-position-of-mouse delta-x delta-y))

(def-icp-message-type shift-position-of-mouse-in-window
    (gensym-window (coordinate delta-x) (coordinate delta-y))
  (handle-shift-position-of-mouse-in-window gensym-window delta-x delta-y))

(defun handle-shift-position-of-mouse-in-window (gensym-window delta-x delta-y)
  (let* ((native-window (native-window? gensym-window))
	 (new-mouse-x (+r (c-x11-get-mouse-x-position native-window) delta-x))
	 (new-mouse-y (+r (c-x11-last-mouse-y-position native-window) delta-y)))
    (c-x11-move-pointer native-window new-mouse-x new-mouse-y)
    nil))

(defun shift-position-of-mouse-in-window (gensym-window delta-x delta-y)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-shift-position-of-mouse-in-window gensym-window delta-x delta-y)))
    (t
     (handle-shift-position-of-mouse-in-window gensym-window delta-x delta-y))))



;;; `Shift-position-of-mouse' shifts the mouse in the current workstation, and
;;; also updates the local current workstation structure's model of where the
;;; mouse is.

(defun-allowing-unwind shift-position-of-mouse (delta-x delta-y)
  ;; Note it locally.
  (incfr (x-in-window-of-mouse? current-workstation) delta-x)
  (incfr (y-in-window-of-mouse? current-workstation) delta-y)
  (shift-position-of-mouse-in-window
    current-workstation-window delta-x delta-y))





;;; `Shift-cursor-position' and `set-cursor-position' may be called by the higher
;;; level routines.  All coordinates (or deltas) are with respect to the window.

;;; Shift-cursor-position moves the cursor from its current x and y positions
;;; by x-amount and y-amount in current-workstation.

(defun shift-cursor-position (x-amount y-amount)
  (shift-position-of-mouse-in-window
    current-workstation-window
    x-amount y-amount))

;; Called only by some unused UI commands.


;;; `Set-cursor-position' sets the absolute position of the cursor in
;;; current-workstation.

(defun set-cursor-position (new-x-position new-y-position)
  (set-position-of-mouse new-x-position new-y-position))

;; What's the difference between this and set-position-of-mouse?! Why have
;; both?! (MHD 8/18/02)

;; Consider allowing either of the positions to be nil in order to be able to
;; change the mouse position in only x or y without having to know both.





;;;; For-Each-Workstation: Macro for Operating on All Workstations



;;; `For-Each-Workstation' is a macro that simply evaluates body in a
;;; for-workstation-polling environment for each workstation in
;;; workstations-in-service.
;;;
;;; This establishes a block is established that may be returned from.

(defmacro for-each-workstation (&body body)
  (avoiding-variable-capture (&aux workstation)
    `(loop for ,workstation in workstations-in-service
	   do (for-workstation-polling (,workstation)
		. ,body))))





;;;; Support for Beeps



;;; Beep-at-user beeps in the current workstation window if possible.  This
;;; may only be called in a for-workstation context.

;;; Note that it may be impossible because (a) G2 does not know how to do
;;; that (true in a few implementations, at present -- see code in PLATFORMS
;;; for details) ; (b) the implementation does not permit that to be done; or
;;; (c) beeping has been disabled by the user in some hardware way (by turning
;;; a knob on the monitor, e.g.) or in some software way (through the the control
;;; panel, say, on the Mac, e.g.).

(defun beep-at-user ()
  (beep-in-window current-workstation-window))


;;; Beep-in-window ...

(def-icp-message-type beep-in-window (gensym-window)
  (beep-in-window gensym-window))


(defun-allowing-unwind beep-in-window (gensym-window)
  (case (type-of-gensym-window gensym-window)
    (icp
     (with-icp-window (gensym-window)
       (send-icp-beep-in-window gensym-window)))
    (t
     (beep-in-window-1 gensym-window))))

;; There was a bug here in telewindows.  The following form was:
;; (icp-output-port-for-window? current-workstation-window) until 2/6/92 in 3.0
;; development; could be bugs 3.0 alpha or early beta images of Telewindows
;; from around or before this time.  (This function is the beep system
;; procedure in sys-proc.) (MHD 2/6/92)







;;;; Global Paint Mode: T or (in G2 Only) NIL



;;; `Global-paint-mode-p' is true if we're either running in Telewindows,
;;; or if (g2-global-paint-mode-p), q.v., defined for G2 only, is true.

(defun global-paint-mode-p ()
  (if (memq current-system-name '(telewindows))
      t
      (g2-global-paint-mode-p)))




;;;; The Break Loop

;; moved here from RUN. (MHD 4/20/89)



#+(and lucid (not translator))			; it's a bug, sort of, in lucid that
(defvar * nil)					;   this need be done for the first
#+(and lucid (not translator))			;   three.
(defvar ** nil)
#+(and lucid (not translator))
(defvar *** nil)

#-translator
(defvar **** nil)

#-translator
(defvar ***** nil)

#-translator
(defvar ****** nil)

#-translator
(defvar ******* nil)

#-translator
(defvar ******** nil)

#-translator
(defvar ********* nil)

#-translator
(defvar ********** nil)



;;; Make-new-value-for-*-if-appropriate, if "appropriate", sets the value * to value, sets
;;; the value of ** to the previous value of *, and so on, for up to 10 *'s. At present,
;;; it is considered "appropriate" if and only if its the #+development environment.  In
;;; any case, this will always return value.

(defun make-new-value-for-*-if-appropriate (value)
  #+development
  (setq ********** *********
	********* ********
	******** *******
	******* ******
	****** *****
	***** ****
	**** ***
	*** **
	** *
	* value)
  #-development
  (setq	*** **
	** *
	* value)
  value)

;; Consider making this non-development, in the interest of field support.



;;; `show-*-history' Prints the current *, **, ***, etc. which is nice
;;; because they are a recent history of selection, etc.
;;; when in development
#+development
(defun show-*-history ()
  (let ((*print-level* 3)
	(*print-length* 4))
    (format t "~@{~&~S ~S~}"
	    '**  *
	    '***  **
	    '****  ***
	    '*****  ****
	    '******  *****
	    '*******  ******
	    '********  *******
	    '*********  ********
	    '**********  *********))
  (values))

;; Most of the above cloned from DEVICES, which is for Lisp machines only!





#+(or development porting)
(defparameter allow-run-break-loop t)

#+(or development porting)
(defun run-break-loop (gensym-window &optional interesting-frame?)
  (declare (ignore gensym-window))
  (when allow-run-break-loop
    (break ";;; ~a break~@[ on ~s~]."
	   (system-alias current-system-name) ; i.e., G2, TW, or GSI
	   interesting-frame?)))




;;;; Closing a Telewindows Connection




(def-icp-message-type request-to-close-telewindows-connection (gensym-window)
  (close-telewindows-connection gensym-window))



;;; `Close-telewindows-connection' is called for the case of a planned shutdown.
;;; Close-telewindows-callback is the connection loss callback function If the
;;; shutdown is unplanned, it calls flush-workstation.  If the shutdown is
;;; planned, it is a no-op since flush-workstation is called
;;; in close-telewindows-connection.

(defun-allowing-unwind close-telewindows-connection (gensym-window)
  (case (type-of-gensym-window gensym-window)
    (icp
     (close-telewindows-connection-internal gensym-window)
     (current-system-case
       (ab
	 (maybe-schedule-service-workstation (workstation-this-is-on gensym-window) nil))))
    (t
     (when (native-menu-bar-p gensym-window)
       (nms-revert-to-unconnected-menu-bar gensym-window)) ; A no-op on unix platforms.
     (notify-user-if-possible
       "Telewindows shutdown as requested.~%")
     (shutdown-icp-socket-connection
       (parent-icp-socket
	 (icp-output-port-to-master-for-window? gensym-window))
       'requested)
     (reclaim-telewindows-workstation-function
       (workstation-this-is-on gensym-window)))))

;; In the case of a planned shutdown,
;; get-telewindows-workstation-given-icp-socket will return nil (because the
;; workstation has already been taken out of service in
;; close-telewindows-connection).  Close-telewindows-callback is thus a no-op
;; in this case.


(defun-allowing-unwind close-telewindows-connection-internal (gensym-window)
  (with-icp-window (gensym-window)
    (send-icp-request-to-close-telewindows-connection gensym-window))

  (let ((output-port (icp-output-port-for-window? gensym-window)))
    (when output-port
      (let ((icp-socket (parent-icp-socket output-port)))
	(setf (icp-socket-workstation icp-socket) nil)
	(setf (icp-output-port-for-window? gensym-window) nil)
	(flush-and-shutdown-icp-socket icp-socket)))))





;;;; System-specific Slot Reclaimers



;;; This section has various reclaimers that need to be called from either
;;; Telewindows or G2, but are noops except in G2.  These are primarily for the
;;; workstation and gensym-window structure.  In previous versions of
;;; Telewindows, these structures were never reclaimed on the Telewindows side,
;;; since the process was shut down concurrently.  But in the New UI/TW Pro,
;;; these structures may come and go, so they need to be disposed of cleanly.

;; NOTE: some of these reclaimers, or some subset of their code, should really
;; be run in TW, but they never were, and it never mattered, since the sins were
;; covered by process shutdowns.  This issue must be reviewed soon! (MHD 4/2/02)




;;; `Reclaim-panes-in-window-if-g2', `reclaim-workstation-event-queue-if-g2',
;;; `reclaim-mouse-pointers-if-g2', `reclaim-workstation-context-stack-if-g2',
;;; `reclaim-non-kb-workspaces-for-this-workstation-only-if-g2', and
;;; `reclaim-icon-rendering-and-remove-from-icon-description-if-g2' simply
;;; dispatch to the functions whose names are the same except for the -if-g2
;;; suffix iff this is G2.  On other systems (i.e., Telewindow), they do nothing
;;; but simply ignore their arguments are return no useful value.

(defun reclaim-panes-in-window-if-g2 (panes-in-window)
  panes-in-window
  (current-system-case
    (ab
      (reclaim-panes-in-window panes-in-window))))

(defun reclaim-workstation-event-queue-if-g2 (workstation-event-queue)
  workstation-event-queue
  (current-system-case
    (ab
      (reclaim-workstation-event-queue workstation-event-queue))))

(defun-void reclaim-mouse-pointers-if-g2 (gensym-list-of-mouse-pointers)
  gensym-list-of-mouse-pointers
  (current-system-case
    (ab
      (reclaim-mouse-pointers gensym-list-of-mouse-pointers))))

(defun reclaim-workstation-context-stack-if-g2 (workstation-context-stack)
  workstation-context-stack
  (current-system-case
    (ab
      (reclaim-workstation-context-stack workstation-context-stack))))

(defun reclaim-non-kb-workspaces-for-this-workstation-only-if-g2
    (list-of-non-kb-workspaces)
  list-of-non-kb-workspaces
  (current-system-case
    (ab
      (reclaim-non-kb-workspaces-for-this-workstation-only list-of-non-kb-workspaces))))

(defun reclaim-icon-rendering-and-remove-from-icon-description-if-g2 (icon-rendering)
  icon-rendering
  (current-system-case
    (ab
      (reclaim-icon-rendering-and-remove-from-icon-description icon-rendering))))





;;;; Rerouting a Telewindows Connection



;;; The function `reroute-telewindow' reroutes given ICP window to another
;;; G2. Must be called in a with-icp-window context.

(defun reroute-telewindow (gensym-window protocol host port init-string)
  (when (icp-window-p gensym-window)
    (with-backtrace-for-internal-error 'reroute-telewindow
      (send-icp-reroute-telewindow gensym-window protocol host port init-string))))

(def-icp-message-type reroute-telewindow
  ((gensym-window gensym-window)
    (text-string protocol)
    (text-string host)
    (text-string port)
    (text-string init-string))
    
  ;; Gensym-129 fix
  (reclaim-cached-structures-for-window gensym-window)
  
  (reroute-telewindows-connection gensym-window
    (copy-text-string protocol)
    (copy-text-string host)
    (copy-text-string port)
    (copy-text-string init-string)))


;;;; Obsolete ICP Messages


;;; These obsolete messages can only be sent from a 7.x G2 to a TW in 7.x-style
;;; multiwindow mode, which means G2 7.0 and TW 7.0. So, they could be removed
;;; entirely, but I'm leaving stubs out of paranoia.

(def-icp-message-type launch-peer-window (gensym-window (list overriding-plist))
  (declare (ignore gensym-window overriding-plist))
  (dwarn "Unexpected ICP message launch-peer-window"))

(def-icp-message-type set-window-show-status (gensym-window (symbol show-state))
  (declare (ignore gensym-window show-state))
  (dwarn "Unexpected ICP message set-window-show-status"))

(def-icp-message-type show-window-with-geometry
    (gensym-window (coordinate x) (coordinate y) (coordinate width) (coordinate height)
 		   (list options-plist))
  (declare (ignore gensym-window x y width height options-plist))
  (dwarn "Unexpected ICP message show-window-with-geometry"))

(def-icp-message-type set-scroll-info
    ((gensym-window gensym-window)
     (fixnum xmin) (fixnum xmax) (fixnum xpos)
     (fixnum ymin) (fixnum ymax) (fixnum ypos))
  (declare (ignore gensym-window xmin xmax xpos ymin ymax ypos))
  (dwarn "Unexpected ICP message set-scroll-info"))



;;;; I-am-alive Mechanism for Telewindows

;;; Flow control is needed in Telewindows for situations where the Telewindows process
;;; cannot keep up with the G2 process.  This can happen if the network is slow or if
;;; the Telewindows process is slow (possibly because there are other processes
;;; running on the processor), especially if the G2 knowledge base is doing things
;;; like showing and hiding complicated workspaces every second.  In such cases, ICP
;;; buffers can build up (typically in the G2 process) and in the long run, the
;;; process could run out of memory.  Thus, flow control is needed to prevent this
;;; from happening.

;;; Initialize-I-am-alive-info is called in the same places where connection-loss
;;; callback functions for Telewindows are registered; in run-telewindows (for the
;;; Telewindows process), and in the handler for initialize-telewindows-workstation
;;; (for the G2 process).  Function-to-decide-whether-to-send-I-am-alive,
;;; function-to-determine-if-remote-process-alive?, and
;;; function-to-determine-if-icp-connection-clogged?  are implemented as described in
;;; the above described examples.  The parameters in the I-am-alive-info structures
;;; are initialized based on global parameters.

;;; The function-to-determine-if-icp-connection-clogged?  is implemented with some
;;; hysteresis so that it does not decide too quickly that the connection is
;;; unclogged.  This is done to prevent limit cycle thrashing where the connection
;;; becomes clogged again very soon after it is found to be unclogged.

;;; Also, the decision that the connection is clogged is not made
;;; immediately upon detection of more than the maximum limit of bytes;
;;; Telewindows is given some time to unclog.  This is accomplished by
;;; using the time-when-first-suspected-clogging?  slot of an
;;; I-am-alive-info structure.  This slot is set to (get-fixnum-time)
;;; upon detecting excess of the maximum limit of ICP bytes, but the
;;; connection is not considered clogged until the excess has gone on
;;; unabated for some period of time.  This feature is very important
;;; since workspace refreshes, and particularly, complete refreshes of
;;; graphs, can put a large number of icp bytes into the buffers before
;;; ICP has a chance to process them.  It is not fair in this case to
;;; consider the connection clogged immediately; Telewindows should be
;;; given a chance to overcome the (hopefully) transient overload.

;;; The difficulty with flow control for Telewindows is not in determining that the
;;; connection is clogged, but rather, in doing something about it.  Once the
;;; icp-connection-clogged-p slot is set, writing-icp-message-group will not write
;;; messages until the slot is reset.  Thus, draw messages will simply be dropped.  In
;;; general, this means that a full refresh (using refresh-window) will be necessary
;;; when the connection becomes unclogged.

;;; The fact that messages are being dropped and that a full refresh is necessary is
;;; flagged by on-window which checks the icp-connection-clogged-slot and adds the
;;; window to a list in a special variable.  The
;;; function-to-determine-if-icp-connection-clogged?  could check this flag when it
;;; determines that the icp connection is unclogged and take care of executing the
;;; full refresh.

;;; Doing a full refresh is a brute force approach and could be very inefficient in
;;; certain cases.  Optimizations are possible.  For example, if a draw for any
;;; display is missed, all that is required is that the draw method for the display be
;;; invoked when the icp connection becomes unclogged.  Refreshes could also be
;;; workspace specific, or even to things on the workspace if track is kept of what
;;; was dropped.



(defparameter telewindows-I-am-alive-send-interval 30)

(defparameter telewindows-max-number-of-message-groups-before-clogged 50)

(defparameter telewindows-min-number-of-message-groups-before-unclogged 20)

(defparameter telewindows-max-number-of-icp-bytes-before-clogged 20000)

(defparameter telewindows-min-number-of-icp-bytes-before-unclogged 500)

(defparameter telewindows-seconds-to-wait-before-judging-clogged 10)

;; The closer that telewindows-max-number-of-icp-bytes-before-clogged and
;; telewindows-max-number-of-icp-bytes-before-unclogged are, the less will be the
;; hysteresis; the less will be the frequency of the clogged-unclogged limit cycle
;; for an overloaded system.  Actually,
;; telewindows-min-number-of-icp-bytes-before-unclogged should be close to 0
;; so that when the connection becomes unclogged, response will be good.

(defvar use-telewindows-clogging-mechanism-p t)

(defun initialize-g2-process-telewindows-icp-socket (icp-socket)
  (initialize-I-am-alive-info
    icp-socket
    (when use-telewindows-clogging-mechanism-p
      'telewindows-connection-clogged-for-g2?)))


(defun initialize-telewindows-process-telewindows-icp-socket (icp-socket)
  (initialize-I-am-alive-info
    icp-socket
    'telewindows-connection-clogged?))






;;; Telewindows-connection-clogged-for-g2?  is like
;;; telewindows-connection-clogged?  except that it posts messages when a
;;; connection becomes clogged or unclogged.

(defun telewindows-connection-clogged-for-g2? (icp-socket I-am-alive-info)
  (if (not (icp-connection-clogged-p I-am-alive-info))
      (cond
	;; GENSYMCID-1215: twng locking up
	;;
	;; here, the following three conditions are previously connected with AND,
	;; this doesn't look correct, because if any of them happens, that's one
	;; limitation reached, and telewindows connection should be considered as
	;; "clogged". -- Chun Tian (binghe), Feb 2015.
	((or  (>f (number-of-outstanding-message-groups I-am-alive-info)
		  telewindows-max-number-of-message-groups-before-clogged)
	      (>f (number-of-outstanding-icp-bytes I-am-alive-info)
		  telewindows-max-number-of-icp-bytes-before-clogged)
	      (>f (number-of-outstanding-output-icp-bytes icp-socket)
		  telewindows-max-number-of-icp-bytes-before-clogged))
	 (cond
	   ((null (time-when-first-suspected-clogging? I-am-alive-info))
	    ;; First suspecting that clogged.
	    (setf (time-when-first-suspected-clogging? I-am-alive-info)
		  (get-fixnum-time))
	    nil)
	   ((<f (convert-fixnum-time-difference-to-seconds
		  (fixnum-time-difference
		    (get-fixnum-time)
		    (time-when-first-suspected-clogging? I-am-alive-info)))
		telewindows-seconds-to-wait-before-judging-clogged)
	    ;; Still suspect, but give it some more time.
	    nil)
	   ((not (drawing-is-scheduled?))
	    ;; Really is clogged.
	    (let* ((g2-window? (get-g2-window-given-icp-socket icp-socket))
		   (things-to-update-when-unclogged?
		     (things-to-update-when-unclogged? I-am-alive-info)))

	      (post-telewindows-connection-clogged g2-window? t)

	      (when (not (memq icp-socket things-to-update-when-unclogged?))
		(setf (things-to-update-when-unclogged? I-am-alive-info)
		      (gensym-cons
			icp-socket
			things-to-update-when-unclogged?))))
	    t)))
	(t
	 (setf (time-when-first-suspected-clogging? I-am-alive-info) nil)
	 nil))

      (cond
	((not
	   ;; Invece, only when three conditions are all matched, telewindows is
	   ;; "unclogged". So here we must use AND. --binghe
	   (and (<f (number-of-outstanding-message-groups I-am-alive-info)
		    telewindows-min-number-of-message-groups-before-unclogged)
		(<f (number-of-outstanding-icp-bytes I-am-alive-info)
		    telewindows-min-number-of-icp-bytes-before-unclogged)
		(<f (number-of-outstanding-output-icp-bytes icp-socket)
		    telewindows-min-number-of-icp-bytes-before-unclogged)))
	 t)
	(t
	 (let ((g2-window? (get-g2-window-given-icp-socket icp-socket)))
	   (when g2-window?
	     (post-telewindows-connection-clogged g2-window? nil)))
	 nil))))

;; Fix post-telewindows-connection-clogged to work (see below)!



(defun number-of-outstanding-output-icp-bytes (icp-socket)
  (if (not (all-icp-buffers-transmitted? (icp-output-port icp-socket)))
      (loop for icp-buffer = (icp-buffer-queue-head (icp-output-port icp-socket))
			   then next-buffer
	    for next-buffer = (icp-buffer-next icp-buffer)
	    while next-buffer
	    sum (number-of-icp-bytes-in-buffer next-buffer))
      0))

;; This is feasible because process-icp-sockets handles a message group as soon as
;; it is received.  Thus, there is no possibility of message groups piling up on
;; the remote side and a good estimate of the number of outstanding icp bytes can
;; be optained just by looking at the local output buffers.  Consider getting rid
;; of the other mechanism for computing number of outstanding icp bytes.  Still
;; need to send I-am-alive messages though.  The clogging predicate should be more
;; a function of time than number of outstanding icp bytes.




;; Parameters for I-am-alive-info are defaulted from global parameters.



(defun handle-unclogged-connection-if-necessary (I-am-alive-info)
  (let ((things-to-update-when-unclogged?
	  (things-to-update-when-unclogged? I-am-alive-info)))
    (cond
      ((and things-to-update-when-unclogged?
	    (not (icp-connection-clogged-p I-am-alive-info)))
       (loop for thing in things-to-update-when-unclogged?
	     do
	 (cond
	   ((icp-socket-p thing)
	    (let* ((g2-window? (get-g2-window-given-icp-socket thing))
		   (gensym-window?
		     (when g2-window?
		       (get-gensym-window-for-g2-window g2-window?))))
	      (when gensym-window?
		(refresh-window gensym-window?))))))
       (reclaim-things-to-update-when-unclogged?
	 things-to-update-when-unclogged?)
       (setf (things-to-update-when-unclogged? I-am-alive-info) nil))
      (t
       ;; We don't expect to get into this case very often because
       ;; the task that calls this function is only called upon
       ;; the transition clogged->unclogged.  The following clause
       ;; exists for reasons of paranoia.
       (with-temporary-gensym-float-creation schedule-unclog-hanlder
	 (with-future-scheduling
	     ((unclogged-cleanup-task I-am-alive-info)
	      0 ; priority - why not?
	      (+e (managed-float-value (clock-get current-real-time))
		  5.0) ; wild guess
	      nil ; cycle time
	      nil ; ensure-cycle
	      t   ; real time p
	      )
	   (handle-unclogged-connection-if-necessary
	     I-am-alive-info)))))))

;; This will become more sophisticated.  Yeah.

;; This is in TELESTUBS rather than INT due to the reference to gensym-window-p.







;;;; Spawning Processes from Telewindows

;; jh, 12/28/95.

(def-icp-message-type spawn-remote-process
    ((fixnum index-of-result-parameter) (text-string command-line))
  ;; Don't forget that command-line is reclaimed by the automatic
  ;; icp-value-reclaimer!
  (tw-handle-spawn-remote-command-line-process
    index-of-result-parameter
    command-line))

(def-icp-message-type spawn-remote-executable
    ((fixnum index-of-result-parameter) (text-string command-line))
  ;; Don't forget that command-line is reclaimed by the automatic
  ;; icp-value-reclaimer!
  (tw-handle-spawn-remote-executable-process
    index-of-result-parameter
    command-line))

(def-icp-message-type remote-process-exists-p
    ((fixnum index-of-result-parameter) (managed-double-float process-id))
  (tw-handle-remote-process-exists-p index-of-result-parameter process-id))

(def-icp-message-type kill-remote-process
    ((fixnum index-of-result-parameter) (managed-double-float process-id))
  (tw-handle-kill-remote-process index-of-result-parameter process-id))

(def-icp-message-type spawn-remote-process-reply
    ((fixnum index-of-result-parameter) (managed-double-float process-id))
  (g2-handle-spawn-remote-process-reply index-of-result-parameter process-id))

(def-icp-message-type remote-process-exists-p-reply
    ((fixnum index-of-result-parameter) (fixnum result-code))
  (g2-handle-remote-process-exists-p-reply
    index-of-result-parameter
    result-code))

(def-icp-message-type kill-remote-process-reply
    ((fixnum index-of-result-parameter) (fixnum result-code))
  (g2-handle-kill-remote-process-reply index-of-result-parameter result-code))

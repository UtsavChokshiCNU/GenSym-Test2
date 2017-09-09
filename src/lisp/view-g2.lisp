;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module VIEW-G2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Joe Devlin, Paul B. Konigsberg

;;; This file defines the message interface within G2 for communication with
;;; telewindows. It contains both, the functions that handle incoming messages from
;;; G2, and the functions that notify telewindows about any new information that
;;; telewindows needs to know about. The functions that correspond to these G2 message
;;; functions are defined in Module VIEW-TW. For example, in view-tw.lisp the function
;;; `register-interest-in-ws' is defined.  This functions sends a `represent-ws'
;;; message from TW -> G2 that is handled by `represent-ws-view-message-handler'.
;;; Likewise, view-g2.lisp defines the function `send-representations-item-moved'
;;; that sends a `represent-ws-move-notification' message from G2 -> TW. This
;;; message is handled by `represent-ws-move-notification-view-message-handler'.
;;; As a side note, some handlers also serve directly as senders such as the
;;; function `represent-ws-view-message-handler' described above.

;;; If you haven't noticed the conventions used for defining message-handlers,
;;; all message handlers have the following form:
;;;   ` <message-type>-message-handler ' where message-type is one of the
;;; view-messages defined in Module VIEW-MSG. Message-types are defined using the
;;; def-view-message macro that is found in view-msg.lisp.  The macro declares a knew
;;; message-type-code using def-icp-message-type-code.  Handlers  are also defined 
;;; in this file using def-icp-message-type.

;;;EVENTS-G2
(declare-forward-reference get-attribute-from-class function) 
(declare-forward-reference get-text-of-attribute function)
(declare-forward-reference make-media-bin-for-g2-java-bean function)

(declare-forward-reference item-has-remote-representation-p function)


;;; WS-PROTOCOL as refined by Open-Display
;;; Author(s):  Paul B. Konigsberg
;;; Gensym Co. 10/23/95

;;; NOT UP TO DATE!!!!!
;;; `G2->TW  Message-Senders Interface:'
;;;
;;;    send-representations-item-resized (item new-left new-top new-right new-bottom)
;;;       - represent-ws-resize-notification
;;;            (gensym-window
;;;             integer view-handle
;;;             integer item-handle
;;;             integer new-left
;;;             integer new-top
;;;             integer new-right
;;;             integer new-bottom)
;;;
;;;    send-ws-representations-item-moved (item delta-x delta-y)
;;;       - represent-ws-move-notification
;;;            (gensym-window
;;;             integer view-handle
;;;              integer item-handle
;;;              integer delta-x
;;;              integer delta-y)
;;;  
;;;    send-representations-item-insert-as-subblock
;;;         (item superblock position-or-next-lower-item)
;;;       - represent-ws-item-insert-as-subblock-notification
;;;            (gensym-window
;;;             integer view-handle
;;;             integer item-handle 
;;;             integer master-handle?
;;;             integer next-lower-item-handle)  ; bottom has no next-lower-item so use 0 ??
;;;
;;;    send-representations-item-remove-as-subblock  (item superblock)
;;;       - represent-ws-item-remove-as-subblock-notification
;;;            (gensym-window
;;;             integer view-handle
;;;             integer item-handle
;;;             integer master-handle?)
;;;
;;;    send-all-telewindows-new-kb-workspace-existence-notification (kb-ws)
;;;       - kb-workspace-existence-notification
;;;            ((list workspace-info))
;;;
;;;    send-ws-representations-change-icon-description (??? icon-changes)
;;;       - represent-ws-change-icon-description
;;;         (gensym-window
;;;          color(s)?
;;;          bounds?
;;;          rotate-item?
;;;          other?)
;;;
;;;    send-ws-representations-icon-class-change (icon-class ???)
;;;       - represent-ws-change-icon-class-change-notification
;;;         (gensym-window
;;;          integer view-handle
;;;          ?????)
;;;
;;;    send-ws-representations-icon-instance-change(icon-instance)
;;;       - represent-ws-icon-instance-change-notification
;;;         (gensym-window
;;;          integer view-handle
;;;          integer item-handle
;;;          ????)
;;;
;;;    send-ws-representations-readout-table-update (readout-table)
;;;       - represent-ws-item-readout-table-update-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type??  new-value)
;;;
;;;    send-ws-representations-readout-table-format-change(readout-table)
;;;       - represent-ws-item-readout-table-format-change-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type??  readout-table-format)
;;;
;;;    send-ws-representations-text-box-highlight(text-box)
;;;       - represent-ws-item-text-box-highlight-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           boolean new-value)
;;;
;;;    send-ws-representations-chart-layout-change(chart)
;;;       - represent-ws-item-chart-layout-change-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? chart-layout)
;;;
;;;    send-ws-representations-chart-data-burst(chart)
;;;       - represent-ws-item-chart-data-burst-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? new-value)
;;;
;;;    send-ws-representations-trend-chart-layout-change(trend-chart)
;;;       - represent-ws-item-trend-chart-layout-change-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? trend-chart-layout)
;;;
;;;    send-ws-representations-trend-chart-data-burst(trend-chart)
;;;       - represent-ws-item-trend-chart-data-burst-notifcation
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? new-value)
;;;
;;;    send-ws-representations-connection-kink-introduce(connection)
;;;       - represent-ws-item-connection-kink-introduce-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           ????)
;;;
;;;    send-ws-representations-connection-class-change(????)
;;;       - ?????
;;;

;;; `G2<-TW Message-Handlers Interface'
;;;
;;;    put-gensym-window-in-v5-mode (gensym-window)
;;;         - spew-workspace-info-at-telewindows (gensym-window)
;;;
;;;    represent-ws (gensym-window ws-handle view-handle test-p)
;;;         - represent-ws-reply
;;;         - represent-ws-initial-state-data
;;; 
;;;    move-ws-item (item-handle xpos ypos)
;;;
;;;    change-ws-item-layer (item-handle next-lower-item-or-position)
;;;
;;;    transfer-ws-item (item-handle new-ws-handle xpos ypos)
;;;
;;;    clone-ws-item (item-handle new-ws-handle xpos ypos)
;;;
;;;    delete-ws-item (item-handle)
;;;
;;;    change-ws-item-change-color-layer (item-handle new-color? layer?)
;;;
;;;    change-item-bounds (item-handle new-bounds)
;;;    
;;; `TW->G2 Message-Senders Interface'
;;;
;;;    register-interest-in-ws (gensym-window ws-handle view-handle)
;;;       - represent-ws
;;;            (gensym-window
;;;             integer ws-handle
;;;             integer view-handle
;;;             boolean test-p
;;;     
;;;    enter-v5-mode (gensym-window)
;;;       -  put-gensym-window-in-v5-mode
;;;             (gensym-window)
;;;
;;;    request-ws-item-move (item-handle xpos ypos)
;;;       - move-ws-item
;;;
;;;    request-ws-item-change-bounds (item-handle new-bounds)
;;;       -  change-item-bounds
;;;          (item-handle new-bounds)
;;;
;;;    request-ws-item-change-layer (item-handle next-lower-item-or-position)
;;;       - change-ws-item-layer
;;;
;;;    request-ws-item-transfer (item-handle new-ws-handle xpos ypos)
;;;       - transfer-ws-item
;;;
;;;    request-ws-item-clone (item-handle new-ws-handle xpos ypos)
;;;       - clone-ws-item
;;;
;;;    request-ws-item-delete (item-handle)
;;;       - delete-ws-item
;;;
;;;    request-ws-item-change-color-layer (item-handle new-color? layer?)
;;;       - change-ws-item-change-color-layer
;;;

;;;
;;; `TW<-G2 Message-Handlers Interface'
;;;
;;;    kb-workspace-existence-notification (ws-info-list)
;;; 
;;;    represent-ws-reply
;;;       (gensym-window view-handle allow-p number-of-data-segments)
;;;
;;;    represent-ws-initial-state-data
;;;       (gensym-window view-handle initial-state-info)
;;;
;;;    represent-ws-move-notification
;;;       (gensym-window view-handle item-handle delta-x delta-y)
;;;
;;;    represent-ws-resize-notification
;;;       (gensym-window view-handle item-handle
;;;        new-left new-top new-right new-bottom)
;;;
;;;    represent-ws-item-insert-as-subblock-notification
;;;       (gensym-window view-handle item-handle
;;;        master-handle? next-lower-item-handle)
;;;
;;;    represent-ws-item-remove-as-subblock-notification
;;;       (gensym-window view-handle item-handle master-handle?)
;;;
;;;    represent-ws-change-icon-description
;;;         (gensym-window
;;;          color(s)?
;;;          bounds?
;;;          rotate-item?
;;;          other?)
;;;
;;;    represent-ws-change-icon-class-change-notification
;;;         (gensym-window
;;;          integer view-handle
;;;          ?????)
;;;
;;;    represent-ws-icon-instance-change-notification
;;;         (gensym-window
;;;          integer view-handle
;;;          integer item-handle
;;;          ????)
;;;
;;;    represent-ws-item-readout-table-update-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type??  new-value)
;;;
;;;    represent-ws-item-readout-table-format-change-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type??  readout-table-format)
;;;
;;;    represent-ws-item-text-box-highlight-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           boolean new-value)
;;;
;;;    represent-ws-item-chart-layout-change-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? chart-layout)
;;;
;;;    represent-ws-item-chart-data-burst-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? new-value)
;;;
;;;    represent-ws-item-trend-chart-layout-change-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? trend-chart-layout)
;;;
;;;    represent-ws-item-trend-chart-data-burst-notifcation
;;;          (gensym-window
;;;           integer view-handle
;;;           integer item-handle
;;;           type?? new-value)
;;;
;;;    represent-ws-item-connection-kink-introduce-notification
;;;          (gensym-window
;;;           integer view-handle
;;;           ????)
;;;
;;;    represent-ws-representations-connection-class-change(????)
;;;       - ?????
;;;
;;;  

;;;  `WORKSPACE-REPRESENTATION:'
;;;  -view-handle
;;;
;;;  -list of CONTAINED-ITEMS
;;;       all items in a workspace-representation will be at the same containment
;;;       level so that the containment of one item within a second, non-workspace
;;;       item, will not be indicated.  However, the visual implications of this
;;;       hierarchical containment will be preserved through the use of a
;;;       'dragging-slave-list' for each item.  The dragging-slave-list
;;;       for an item is a list of all other items (within that workspace) that are
;;;       subblocks of the given item (referred to as the `master item')
;;;
;;;    subblocks: (these will be items in an open-display)
;;;       od-items with specialized attributes and behavior
;;;          -layer and position determined relative to its master
;;;       examples:
;;;        nameboxes and attribute-displays
;;;        (stored as a subblocks but managed as representations)
;;;        -Adding a namebox  adds an od-item to the od-workspace at the master
;;;         item's x-y location on top of the topmost subblock of the master item.
;;;         It also  adds the namebox to the dragging-slave-list of
;;;           the master-item for the namebox.
;;;       revision: only v5-tw-item-like-p subblocks will be items
;;;  -WIDTH, HEIGHT 
;;;
;;;  
;;;  `ITEM-REPRESENTATION' within a workspace-representation:
;;;  -`item-handle'
;;;   unique identifier for an item instance (is the handle to the item in g2)
;;;
;;;  -`dragging-slave-list' see above
;;;
;;;  -`item-type/class'
;;;    for specifying icon-description 
;;;    for specifying class-specific tracking
;;;        -callback(s) for posting item dialogues/tables 
;;;  -`item-bounds' (location,width,height)
;;;    -updates the x,y-positions of all the items in its slave-list.
;;;  -`item-layer'
;;;    specifies the item's z-position within its workspace.
;;;    updates the  z-positions of all the items in its slave-list.
;;;  -`item-other-attributes' (changable AND user visible attributes):
;;;    item-color, layout, etc....???
;;;    



;;;   CHANGES NEEDED IN G2

;; fixed..problem with how to just send (all) the text of 'box-translation-and-text
;;     need a function to extract just the text from the slot since tw doesn't need the
;;     translation.  Structure of whats stored in the slot varies from instance to instance
;;     and from class to class.  Also note that, my temporary solution to just send the
;;     entire slot won't work because the slot usually contains dotted lists and there
;;     isn't presently any icp value-type that can handle nested dotted lists. Hmmm

;; ok..need to resolve dealing with attribute displays. Would like to deal with them as just
;;    text boxes and not with their specific slot names, so that we would only have to
;;    let through 'box-translation and text.  Also what about transfering tables to workspaces??
;;    Are they just a collection of  displays since attribute displays are just tiny tables??
;;    How will the update for this work???? (ok...just one big attribute-display)
;;    semi-cleaned-up-->
;;    presently hooking into updates in update-representations-in-table by sending an item-change
;;    message for table-rows, with an index of slot-name, and stripping the text of the text-cell
;;    being updated for the new-value. C'EST TRES, TRES MAL

;;  for tables changes we want to notify workspace-representations unless
;;    (classic-attribute-table-p table) is true

;; fixed...need to deal with subblock insertion all being placed directly on top of 'the-master
;;       also, other blocks don't know about subblocks

;; done: need a hook for buttons in  change-on/off-switch to send the new-value of
;;    toggle-buttons, radio-buttons

;; ok--issue ---> sliders---> need to decide what and when we are going to send.
;;             ie just the slider-display or the value or both....???

;; issue---> hook for on/off-switches signals more than once  for the button you press

;;*** issue --> present method for sifting out slot-value changes that are relevant to workspaces
;;        is kind of hacky.  <see  slot-is-relevant-to-workspace-representation-p in frames5.lisp>

;; fixed readout-tables...updated as a table not through change slot value (stupid!@##)
;;   fixed...bug---> updates for readout tables send nil as new-value because its not actually stored anywhere
;;         except in the cell itself!!!!

;; *** 2do--->need to get trend-chart data-bursts working

;; issue---> meters only move meter-marker subblock as data-bursts !

;; *** 2do --->cloning a workspace -> signal new-workspace
;; *** 2do --->create a subworkspace -> signal new-workspace

;; fixed:deleting a kb-workspace ---> signal deletion in v5-tws of the workspace-representations
;;   partially fixed---> signals deletion of instances of classes  on other workspaces 
;;                       if the deleted workspace contained a class def.
;; fixed:      but not getting signal that the workspace itself was deleted

;; ok..issue:::--->dials move many items
;;      we really don't want to keep treating it this way do we??????
;; this part is fixed---> also not inserting the other subblocks
;;      same problems with displays for lifting and dropping, etc....

;; issue--->add-subblock used by tables

;; note ---> moving does move loose-connections but doesn't lift or drop

;; reserve 0 for the handle to the bottom

;; fixed ;; bug:::--->deletion of class-def. doesn't notify deletion of subblocks
;;           ie nameboxes, etc..

;; fixed ;; bug:::--->lift to top isn't lifting subblocks to top for attribute displays of
;;           a block or for nameboxes, etc...

;; fixed ;; bug:::--->tranfer doesn't remove and delete subblocks

;; fixed ;; bug:::--->insertion doesn't know about subblocks when inserting on top of an item
;;           ie. that it should take into account that the item on top of which it is
;;            being placed might have subblocks that were (artificially) inserted
;;            on top of their master.

;; done...need to send icon-description info with initial info
;; need to send icon-description changes any time the icon-description changes
;;    ie through the change-color-of-item

;; ok..redesigned..bug/issue---> button-label's are also subblocks but aren't updated as representations
;;  change-slot-value sends message to the master not the label item itself
;;
;; fixed...bug:::--->initial-data doesn't send  subblocks of items

;; *** 2do connections, default-junctions, network-wire
;; *** getter-problems:  initial button-states, trend-chart-complex-structures

;; ok...issues menus, dialogues(text-editors, icon-editors, inspect, logbooks)
;; ok...issues non-od-item items


;;; changes needed in:
;;;   update-representations-of-slot-value
;;;   remove-representations-of-slot-component-group
;;;   update-representations-in-tables
;;;   highlight-or-unhighlight-attribute
;;;   update-attribute-tables
;;;   update-attribute-table-rows (might not be a problem --
;;;                                entry will be guarded by outer func)
;;;   write-slot-for-kb







;;;;  Creation of ws-representations.

;;;  Automatically controls the sending and deletion of
;;;  `object-definition-representations' as needed by the workspace
;;;  that a particuliar telewindow has requested to represent.
;;;  The function `represent-ws' sends an object-definition-representation
;;;  (ie icon-description) only if it is not already being represented by
;;;  that particuliar telewindows.

;;;  Each object-definition-representation maintains a reference-count
;;;  that enables unreferenced object-definition-representations
;;;  to be deleted from the object-definition's frame-representations.
;;;  The reference-count is the number of instances of that class in the window.

;;;  Removing subblocks implicitly changes the reference count.  If there are
;;;  no more instances of that object-definition remaining on that window, 
;;;  the representation for that telewindow is deleted.

;;;  Adding a subblock to a workspace calls represent-object-definition for all
;;;  telewindows representing that workspace while  also incrementing the reference-count
;;;  for each window.





;;;; Mapping gensym-windows to ICP-Sockets



;;; These two equal and opposite routines are part of the work
;;; to wean the view/representation system away from its original
;;; assumption that clients were always instances of NTW.

;;; There are some open issues regarding this change.
;;;
;;; 1. Workstations own user mode, not icp-sockets
;;;    (cf. send-window-new-mode)
;;; 2. v5-mode is associated with gensym-windows and governs the generation
;;;    of various notifications for the client
;;;    (cf. put-gensym-window-in-v5-mode and friends)
;;; 2a We need a way to say that a socket wants to be involved in this
;;;    whole representation business and to what extent.  And how
;;;    about a loop-path iterator for clients too.
;;;    (cf.  get-list-of-v5-mode-clients)
;;; 3. The definition of many of the view-messages unnecessarily include
;;;    gensym-window in their argument-lists.  These could be removed
;;;    and fewer references to gensym-windows would be needed in this file.
;;;    This is relatively simple drudgery.

(defmacro remote-gensym-window-icp-socket (gensym-window)
  (avoiding-variable-capture (gensym-window)
    `(progn
       #+development
       (unless (eq (type-of-gensym-window ,gensym-window) 'icp)
	 (error "~s is not a remote gensym-window" ,gensym-window))
       (parent-icp-socket
	 (icp-output-port-for-window? gensym-window)))))

;;; apparently defunct
(defun-simple icp-socket-remote-gensym-window (icp-socket)
  (loop with icp-output-port = (icp-output-port icp-socket)
        for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	when (eq icp-output-port
		 (icp-output-port-for-window? gensym-window))
	  return gensym-window
	finally
	  #+development
	  (error
	    "icp-socket ~s is not associated with a remote gensym-window"
	    icp-socket)
	  (return nil)))
		 
	  

;;;  `represent-object-definition' is in charge of first checking to see if the
;;;  telewindow is already representing that object-definition.  If this is not so,
;;;  a new object-definition-representation will be sent to that telewindow.



;;; `user-defined-class-names-on-workspace'
;;; Returns the list of class-names of every user-defined-class for which there
;;; is at least one instance on the workspace.

;;; Places reclaimation of its return value on its caller

(defun user-defined-class-names-on-workspace (ws)
  (loop with result = 'nil
	for item being each subblock of ws
	as class-name = (class item)
	do
    (when (user-defined-class-p class-name)
      (gensym-pushnew class-name result))
	finally
	  (return result)))


;;; `class-count-on-workspace'
;;; Returns  the number of instances of the user defined class
;;; given by class-name that are on the workspace.

(defun class-count-on-workspace (ws class-name)
  (loop with result = 0
	for item being subblock of ws
	as item-class-name = (class item)
	do
    (when (eq item-class-name class-name)
      (incff result))
	finally
	  (return result)))

(defun-simple representation-address-valid-p (representation)
  (let* ((address (representation-address representation))
	(icp-socket (getfq address 'socket))
	(session-id? (getfq address 'session-id)))
    (or (null session-id?)
	(=f session-id?
	    (icp-socket-session-id icp-socket)))))

;;; `get-object-definition-representation'
;;; Returns the object-definition-representation for icp-socket
;;; in the frame-representations of the definition, if one exists,
;;; otherwise returns nil.

(defun-simple get-object-definition-representation (definition icp-socket)
  (loop with frame-representations = (frame-representations definition)
	for representation in frame-representations
	do
    (when (frame-of-class-p representation 'ws-representation)
      (let* ((address (representation-address representation))
	     (representation-icp-socket (getf address 'socket)))
	(when (eq representation-icp-socket icp-socket)
	  representation)))))


;;;  `note-disuse-of-object-definition-representation'
;;;  Decreases the reference-count of the object-definition-representation
;;;  for the particuliar window.  Will trigger deletion of the representation
;;;  if the count reaches zero.

(defun note-disuse-of-object-definition-representation
    (object-definition icp-socket decrement)
  (when-let (representation
	     (get-object-definition-representation object-definition icp-socket))
    (when (=f (decff (object-definition-representation-reference-count
		       representation)
		     decrement)
	      0)
      ;;(send-client-delete-object-definition-info
      ;;	icp-socket
      ;;(name-or-names-for-frame object-definition))
      (delete-representation representation))))


;;;  `note-use-of-object-definition-representation'
;;;  Increases the reference-count of the object-definition-representation
;;;  for the particuliar window.

(defun note-use-of-object-definition-representation
    (object-definition icp-socket increment)
  (when-let (representation
	     (get-object-definition-representation object-definition icp-socket))
    (incff (object-definition-representation-reference-count representation)
	   increment)))

(defun represent-class (class-name icp-socket)
  (when (and (class-definition class-name)
	     (not (system-defined-class-p class-name)))
    (let ((new-representation
	    (make-representation icp-socket
				 (class-definition class-name)
				 'object-definition-representation)))
      (setf (representation-address new-representation)
	    (slot-value-list 'socket icp-socket
			     'session-id (icp-socket-session-id icp-socket)))
      (setf (object-definition-representation-reference-count
	      new-representation)
	    0)))
  ;;(send-client-object-definition-info
  ;;  icp-socket class-name)
  )


;;; `represent-ws'
;;; Creates a workspace representation of ws for the icp-socket.
;;; Ensures that all needed object-definitions are represented by the
;;; icp-socket (ie if the workspace contains instances of some definition).
;;; Notes use of any such definitions and passes in the instance-counts of 
;;; each definition as increments.

(defun represent-ws (ws icp-socket callback)
  (let* ((workspace-was-showing-p
	   (workspace-showing-p ws nil))
	 (representation
	  (make-representation
	    (or icp-socket local-pseudo-socket)
	    ws
	    'ws-representation)))
    (store-callback-representation representation)
    (setf (representation-address representation)
	  (slot-value-list 'socket icp-socket
			   'session-id (icp-socket-session-id icp-socket)))
    (setf (callback-representation-callback-procedure representation)
	  (demand-representation-callback-remote-procedure-name callback))
    (when (framep callback)
      (frame-serial-number-setf (callback-representation-callback-serial-number representation)
				(frame-serial-number callback)))
    (unless workspace-was-showing-p
      (event-update-status-of-block-showing ws nil t))
    
    representation))


;; based on represent-ws
;;; representation-class-name is a quoted symbol
;;; callback is also a quoted symbol.

(defun represent-trend-chart (item icp-socket callback)
  (let* ((representation
	 (make-representation
	   (or icp-socket local-pseudo-socket)
	   item
	   'tc-representation)))
    (store-callback-representation representation)
  ;;(format t "in represent-trend-chart: ~S ~S ~S ~S~%" item icp-socket
  ;;	  representation-class-name callback)
  (setf (representation-address representation)
	(slot-value-list 'socket icp-socket
			 'session-id (icp-socket-session-id icp-socket)))
  ;; fix this: shouldn't hardcode this slot name
  (setf (callback-representation-callback-procedure representation)
	(demand-representation-callback-remote-procedure-name callback))
  (when (framep callback)
    ;; why does this slot work when the representation class lacks the slot,
    ;; e.g., in tc-representation and ws-representation?
    (frame-serial-number-setf (callback-representation-callback-serial-number representation)
			      (frame-serial-number callback)))
  representation))

;;; ABMH - AB(G2) Message-Handlers
;;; This section defines the handlers of messages that are
;;; received by G2 from Telewindows.





;;; `request-allowed-with-possible-reply' sends a request-denied message to
;;;  telewindows, if the request is denied.  If the request is allowed and this
;;;  was a test request, it sends a request-granted message. Its return value is
;;;  nil if denied and true otherwise. This function will reclaim the gensym-list
;;;  other-info?, if need be.





;;;; AB(G2) Message-Senders

;;; This section defines the functions used by G2 to send messages
;;; to Telewindows.



;;;; Workspace represenation Property Getters



;;; Connections

(defun connection-property-getter (connection-structure)
  (let* ((connection-class (class-of-thing connection-structure))
	 (style (get-attribute-from-class connection-class 'connection-style))
	 (stub-length
	   (get-attribute-from-class connection-class 'stub-length))
	 (cross-section-pattern
	   (get-attribute-from-class connection-class 'cross-section-pattern)))
        
    (allocate-evaluation-structure-inline
      'style style
      'stub-length stub-length
      'cross-section-pattern cross-section-pattern)))


;; Text-boxes

(defun text-box-format-property-getter (text-box-format)
  (when text-box-format
    (allocate-evaluation-structure-inline
      'name (name-or-names-for-frame text-box-format)
      'font (or (car (text-cell-font-map text-box-format)) 'HM14)
      'text-line-color (or (text-cell-line-color? text-box-format) 'foreground)
      'text-background-color (or (text-cell-background-color? text-box-format) 'transparent)
      'left-margin (or (text-cell-left-margin text-box-format) 12)
      'top-margin (or (text-cell-top-margin text-box-format) 9)
      'right-margin (or (text-cell-right-margin text-box-format) 12)
      'bottom-margin (or (text-cell-bottom-margin text-box-format) 8)
      'indentation-margin (or (text-cell-turnover-line-indentation text-box-format) 24)
      'text-line-height (or (text-cell-line-height text-box-format) 15)
      'text-line-spacing (or (text-cell-line-spacing text-box-format) 5)
      'border-width (or (text-box-left-border-width text-box-format) 0)
					; are widths ever not the same
      'border-color (or (text-box-border-color? text-box-format) 'foreground)
      ;'x-magnification (text-cell-x-magnification? text-box-format)
      )))
      

(defun convert-text-to-text-sequence (text)
  (allocate-evaluation-sequence
    (loop with text-lines = nil
	  for elt in text
	  do
      (when (text-string-p elt)
	(eval-push
	  (copy-text-string elt)
	  text-lines))
	  finally
	    (return (nreverse text-lines)))))

(defun export-text-box-overrides (text-box)
  (allocate-evaluation-structure
    (copy-tree-including-leaves-using-eval-conses
      (text-cell-plist-for-text-box text-box))))

(defun text-box-property-getter (text-box)
  (let* ((text (get-slot-value text-box 'box-translation-and-text))
	 (text-box-format (text-box-format text-box))
	 (text-box-overrides (export-text-box-overrides text-box))
	 (text-box-format-properties
	   (text-box-format-property-getter text-box-format)))
    (allocate-evaluation-structure-inline
      'text-lines (if text
		     (convert-text-to-text-sequence text)
		     'empty)
      'item-overrides text-box-overrides
      'text-box-format text-box-format-properties)))

;;; Displays

(defun dial-property-getter (dial)
  (let* ((low-value (low-value-for-dial-ruling dial))
	 (high-value (high-value-for-dial-ruling dial))
	 (increment (increment-per-dial-ruling dial))
	 (low-value-number (cond ((numberp low-value)
				  0);low-value)
				 ((managed-float-p increment)
				  0);(aref increment 0))
				 (t 1)))
	 (high-value-number (cond ((numberp high-value)
				   0);high-value)
				  ((managed-float-p increment)
				   0);(aref increment 0))
				  (t 1)))
	 (increment-number (cond ((numberp increment)
				  0);increment)
				 ((managed-float-p increment)
				  0);(aref increment 0))
				 (t 1))))
    (allocate-evaluation-structure-inline
      'low-value low-value-number
      'high-value high-value-number
      'increment increment-number)))

;; NOTE: icp lists don't allow floats

(defun meter-property-getter (meter)
  (let* ((low-value (low-value-for-meter-ruling meter))
	 (high-value (high-value-for-meter-ruling meter))
	 (increment (increment-per-meter-ruling meter))
	  (low-value-number (cond ((numberp low-value)
				   0) ;low-value)
				 ((managed-float-p increment)
				  0) ;(aref increment 0))
				 (t 1)))
	 (high-value-number (cond ((numberp high-value)
				   10);high-value)
				  ((managed-float-p increment)
				   0);(aref increment 0))
				  (t 1)))
	 (increment-number (cond ((numberp increment)
				  0);increment)
				 ((managed-float-p increment)
				  1);(aref increment 0))
				 (t 1))))
    (allocate-evaluation-structure-inline
      'low-value low-value-number
      'high-value high-value-number
      'increment increment-number)))
   
;; current value =~ ( / (marker-position  (meter-marker)) 300) 
;; NOTE: icp lists don't allow floats

;;; NOTE: this function is used to get the initial-download
;;; information in g2-represent-trend-chart, and produces
;;; data specific to those needs.

(defun trend-chart-property-getter (trend-chart)
  (let* ((label-to-display (trend-chart-label-to-display trend-chart))
	 (title (if label-to-display
		    (convert-text-to-text-string label-to-display)
		    nil))
	 (time-axis (call-category-getter 'trend-chart-time-axis-grammar-spec
					  (trend-chart-time-axis trend-chart)
					  trend-chart nil))
	 (value-axes (call-category-getter 'trend-chart-value-axes-grammar-spec
		       (trend-chart-value-axes trend-chart)
		       trend-chart nil))
	 (point-formats (call-category-getter
			  'trend-chart-point-formats-grammar-spec
			  (trend-chart-point-formats trend-chart)
			  trend-chart nil))
	 (connector-formats (call-category-getter
			      'trend-chart-connector-formats-grammar-spec
			      (trend-chart-connector-formats trend-chart)
			      trend-chart nil))
	 (trend-chart-format (call-category-getter
			       'trend-chart-format-grammar-spec
			       (trend-chart-format trend-chart)
			       trend-chart nil))
	 (trend-chart-plots (call-category-getter
			      'trend-chart-plots-grammar-spec
			      (trend-chart-plots trend-chart)
			      trend-chart nil))
	 (not-already-represented-p (not (item-has-remote-representation-p
					   trend-chart 'tc-representation)))
	 (active-p (trend-chart-active-p trend-chart))
	 (initial-info (allocate-evaluation-structure-inline
			 'trend-chart-active
			 (make-evaluation-boolean-value active-p)
			 'title title
			 'plots trend-chart-plots
			 'value-axes value-axes
			 'time-axis time-axis
			 'point-formats point-formats
			 'connector-formats connector-formats
			 'trend-chart-format trend-chart-format
			 'current-g2-time (copy-managed-float (clock-get current-g2-time)))))
    (when active-p
      (when (or (null (trend-chart-end-time trend-chart))
		(and not-already-represented-p
		     (not (showing-p trend-chart t))))
	(update-active-trend-chart trend-chart t nil))
      (setf (evaluation-structure-slot initial-info 'timespan)
	    (collect-time-bounds trend-chart t not-already-represented-p))
      (setf (evaluation-structure-slot initial-info 'value-axis-extrema)
	    (collect-value-axis-extrema trend-chart t not-already-represented-p))
      (setf (evaluation-structure-slot initial-info 'initial-plot-data)
	    (get-current-plot-data trend-chart t not-already-represented-p)))
    initial-info))

;; NOTE that trend-chart-property-getter returns nested dotted lists
;; also need to reduce complex structures
    
(defun chart-property-getter (chart)
  (declare (ignore chart)))

;; are we keeping old charts???
  
(defun action-button-property-getter (action-button)
  (let ((label? (label-for-button action-button)))
    (allocate-evaluation-structure-inline
      'label (if label? (copy-evaluation-value label?))
      ;;'status (button-status action-button)
      )))
     
(defun radio-button-property-getter (radio-button)
  (allocate-evaluation-structure-inline
    'label (label-for-button radio-button)
    'status (button-status radio-button)))
     
(defun check-box-property-getter (check-box)
  (allocate-evaluation-structure-inline
    'label (label-for-button check-box)
    'status (button-status check-box)))

(defun slider-property-getter (slider)
  (loop with additional-properties
	  = (gensym-list (minimum-value-for-slider slider)
			 (maximum-value-for-slider slider))
	for subblock being each subblock of slider
	until (frame-of-class-p subblock 'slider-readout)
	finally
	(cond
	  ((frame-of-class-p subblock 'slider-readout)
	   (gensym-push (text-box-property-getter subblock)
			additional-properties))
	  (t
	   (gensym-push (allocate-evaluation-structure-inline) additional-properties)))
	(gensym-push (label-for-button slider) additional-properties)
	(return (allocate-evaluation-structure-inline
		  'label (nth 0 additional-properties)
		  'slider-readout-properties (nth 1 additional-properties)
		  'minimum-value (nth 2 additional-properties)
		  'maximum-value (nth 3 additional-properties)))))
	    
(defun type-in-box-property-getter (type-in-box)
  (allocate-evaluation-structure-inline
    'label (label-for-button type-in-box)
    'last-value-displayed (last-value-displayed-in-type-in-box? type-in-box)))

;; type-of-last-value-displayed-in-type-in-box
;; format-for-type-in-box
;; blank-for-type-in?
;; have-edit-option-buttons-for-type-in


;; Tables
    
;;; `table-property-getter'
;;; Does NOT reclaim its return value
(defun table-property-getter (table)
  (allocate-evaluation-structure-inline
    'table-rows (export-table-rows table)))

(defun export-table-rows (table)
  (loop with result = 'nil
	with table-rows
	  = (copy-list-using-gensym-conses
	      (table-rows table))
	with reverse-table-rows = (nreverse table-rows)
	;;If there is only one cell, it *probably* is an attribute display value
	;;(vs. the name), and you would ordinarily think of the name as the left
	;;and the value as the right, so the below is a little funky.
	;;delete-attribute-name-from-attribute-display explicitly collapses the
	;;rows down to one element if it can, though a newly minted attribute
	;;display gives an explicit NIL for the name (thus "left cell" is nil,
	;;as you would expect).  But we didn't want to spend time looking into
	;;the fanout to change that function.  So the naming convention remains
	;;a bit funky here.
	for (left-cell right-cell) in  reverse-table-rows
	as left-text = (exported-cell-text left-cell)
	as left-line-color? = (when left-text
				(compute-text-cell-line-color
				  (text-cell-plist left-cell)
				  (text-cell-format left-cell)
				  table))
	as right-text = (exported-cell-text right-cell)
	as right-line-color? = (when right-text
				(compute-text-cell-line-color
				  (text-cell-plist right-cell)
				  (text-cell-format right-cell)
				  table))
	do
    (eval-push
      (cond ((and left-text right-text)
	      (allocate-evaluation-structure-inline
		'left-text left-text
		'left-text-line-color left-line-color?
		'right-text right-text
		'right-text-line-color right-line-color?))
	     (right-text
	      (allocate-evaluation-structure-inline
		  'right-text right-text
		  'right-text-line-color right-line-color?))
	     (left-text
	      (allocate-evaluation-structure-inline
		  'left-text left-text
		  'left-text-line-color left-line-color?)))
      result)
	finally
	  (reclaim-gensym-list reverse-table-rows)
	  (return (allocate-evaluation-sequence result))))
;reclaimer??


(def-virtual-attribute table-rows 
    ((class table) (or (sequence) (no-item)) ())
  ;;subscription?
  :event-updates nil
  :initial ((class) (declare (ignore class)) (allocate-evaluation-structure nil))
					       
  :getter  ((table)
	    (export-table-rows table)))

(def-virtual-attribute table-font-size
    ((class table-item) symbol ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((table-item)
	    (car (text-cell-font-map
		   (text-cell-format
		     (get-a-text-cell table-item))))))

(def-virtual-attribute represented-item
    ((or (class table-item) (class name-box))(or datum (no-item)) ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) (allocate-evaluation-structure nil))
  :getter  ((item)
	    (cond ((frame-of-class-p item 'table-item)
		   (multiple-value-bind
		       (frame slot-name defining-class?)
		       (get-slot-represented-by-text-cell-if-any
			 (get-a-text-cell item))
		     (declare (ignore slot-name defining-class?))
		     frame))
		  ((frame-of-class-p item 'name-box)
		   (superblock? item)))))
  
(def-virtual-attribute table-layout
    ((class table-item) (or (structure) (no-item)) ())
  ;;subscription
  :event-updates nil
  :initial ((class) (declare (ignore class)) (allocate-evaluation-structure nil))
  :getter  ((table-item)
	    (export-table-layout table-item)))

(def-virtual-attribute text-x-magnification
    ((class text-box) number ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((text-box)
	    (with-temporary-gensym-float-creation
		text-x-magnification
	      (make-evaluation-float
		(get-x-magnification-of-text-box-for-system-procedure text-box)))))

(def-virtual-attribute text-y-magnification
    ((class text-box) number ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((text-box)
	    (with-temporary-gensym-float-creation
		text-y-magnification
	      (make-evaluation-float
		(get-y-magnification-of-text-box-for-system-procedure text-box)))))
  
(def-virtual-attribute format-type
    ((or (class text-box)(class table)) symbol ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((item)
	    (let ((format-frame
		    (frame-class-case item
		      (table
			(table-format item))
		      (text-box
			(text-box-format item)))))
	      ;; pbk eventually make a type-in-box case here
;		      (type-in-box
;			(format-for-type-in-box item)))))
	      (when format-frame
		(or (name-or-names-for-frame format-frame)
		    (format-change? format-frame))))))

(def-virtual-attribute value-to-display
    ((or (class meter)
	 (class dial))
     number ())
  :event-updates nil 
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((display-or-button)
	    (export-value-to-display display-or-button)))

(defun export-display-value (display &optional min-value max-value)
  (let* ((g2-cell-array (cell-array display))
	 (cell-array-value? (and g2-cell-array
				(get-expression-cell-cache g2-cell-array 0)))
	 (value
	   (and cell-array-value?
		(extract-number-or-value
		  (if (evaluation-obsolete-datum-p cell-array-value?)
		      (evaluation-obsolete-datum-value cell-array-value?)
		      cell-array-value?)))))
    (cond ((null value)
	   nil)
	  ((evaluation-truth-value-p value)
	   value)
	  ((and min-value max-value (numberp value))
	   (make-evaluation-value-based-on-type
	     (max min-value (min max-value value))))
	  ((evaluation-value-p value)
	   (copy-evaluation-value value))
	  (t
	   (make-evaluation-value-based-on-type value)))))

(defun export-value-to-display (display)
  (frame-class-case display
    (meter
      (let* ((min-value (extract-number-or-value
			  (low-value-for-meter-ruling display)))
	     (max-value (extract-number-or-value
			  (high-value-for-meter-ruling display))))
	(export-display-value display min-value max-value)))
    (dial
      (let* ((min-value (extract-number-or-value
			  (low-value-for-dial-ruling display)))
	     (max-value (extract-number-or-value
			  (high-value-for-dial-ruling display))))
	(export-display-value display min-value max-value)))))

(def-virtual-attribute button-status
    ((or (class check-box)(class radio-button))
     (or (no-item) (member on off)) ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :setter ((button new-value)
	   (set-button-status-internal button new-value)
	   nil)
  :getter ((button)
	   (button-status button)))

(defun-allowing-unwind button-status (button)
  (with-current-value-for-button-if-any ((value expiration? type variable) button)
    (frame-class-case button
      (check-box	
	(cond
	  ((or (not (active-p button)) (manually-disabled-p button)
	       (null (on-value-for-check-box button)))
	   nil)
	  ((constant-attribute-value-equals-datum-p
	       (on-value-for-check-box button) value type)
	   'on)
	  ((constant-attribute-value-equals-datum-p
	     (off-value-for-check-box button) value type)
	   'off)
	  (t nil)))
      (radio-button
	(make-evaluation-value-based-on-type
	  (cond ((or (not (active-p button))(manually-disabled-p button)
		     (null (value-for-radio-button button)))
		 'off)
		((constant-attribute-value-equals-datum-p
		   (value-for-radio-button button) value type)
		 'on)
		(t 'off)))))))

(defun-allowing-unwind set-button-status-internal (button new-value)
  (let ((current-value (button-status button)))    
    (frame-class-case button
      (check-box
	(unless (or (null new-value)
		    (eq new-value current-value))
	  (funcall-method 'click button
			  (left-edge-of-block button)
			  (top-edge-of-block button))))
      (radio-button
	(when (and (eq current-value 'off)
		   (eq new-value 'on))
	  (funcall-method 'click button
			  (left-edge-of-block button)
			  (top-edge-of-block button)))))))

(def-virtual-attribute slider-value
    ((class slider) number ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :setter ((slider new-value)
	   (set-slider-value-internal slider new-value))
  :getter ((slider)
	   (get-slider-value-internal slider)))

(defun-allowing-unwind get-slider-value-internal (slider)
  (and (runnable-p slider)
       (with-current-value-for-button-if-any
	   ((value expiration? type variable) slider)
	 (make-evaluation-value-based-on-type value))))

(defun-allowing-unwind set-slider-value-internal (slider new-managed-float-value)
  (let ((variable? nil)					    ; variable? => (null frame?)
	(frame? nil)					    ; frame? => (null variable?)
	(slot-name nil)
	(minimum-value-for-slider (minimum-value-for-slider slider))
	(maximum-value-for-slider (maximum-value-for-slider slider))
	new-value)
    (when (or (runnable-p slider)
	      (button-in-use-by-system-p slider))
     (when (and (or (and (setq frame?
			      (associated-frame-for-button? slider))
			(setq slot-name
			      (associated-slot-name-for-button?
				slider))
			(frame-has-not-been-reprocessed-p
			  frame?
			  (associated-frame-serial-number-for-button? slider)))
		   (and (runnable-p slider)
			(setq variable?
			      (get-variable-for-button-if-any slider)))))
      (when (and minimum-value-for-slider
		 maximum-value-for-slider)
	(with-temporary-gensym-float-creation
	    set-slider-value-internal
	  (setq new-value
		(min (max (extract-number-or-value new-managed-float-value)
			  (extract-number-or-value minimum-value-for-slider))
		     (extract-number-or-value maximum-value-for-slider)))
	  (if frame?
	      (change-slot-value
		frame? slot-name
		(read-or-write-slider slider new-value))
	      (let ((*current-computation-frame* slider))
		(put-current-value
		  variable?
		  (read-or-write-slider slider new-value)
		  'number 'never nil))))))
    nil)))

(defun-allowing-unwind type-in-box-value (type-in-box)
  (and (runnable-p type-in-box)
       (with-current-value-for-button-if-any ((value expiration? type variable)
					      type-in-box)
	 (cond ((null value)
		nil)
	       ((make-evaluation-value value type))))))

(def-virtual-attribute type-in-box-value
    ((class type-in-box) (or symbol text number truth-value) ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :setter ((type-in-box new-value)
	   (change-slot-value type-in-box
	  		      'type-in-box-input-value
			      (if (evaluation-truth-value-p new-value)
				  (make-slot-constant (car new-value) (cdr new-value) nil)
				  (copy-evaluation-value new-value)))
	   nil)
  :getter ((type-in-box)
	   (type-in-box-value type-in-box)))

(defmacro bad-color-p (new-color-pattern-or-error)
  `(symbolp (car ,new-color-pattern-or-error)))

(defvar item-color-pattern-returns-overrides-only-p nil)

(def-virtual-attribute item-color-pattern
    ((or (class connection) ;(class kb-workspace)
	 (class text-box)
	 (class entity))
     (structure) ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :setter  ((item new-color-pattern-structure)
	    (let* ((note-as-kb-state-change? t)
		   (new-color-pattern-or-error
		     (and new-color-pattern-structure
			  (import-color-pattern new-color-pattern-structure)))
		   (color-change-error?
		     (if (bad-color-p new-color-pattern-or-error)
			 new-color-pattern-or-error
			 (change-color-of-item
			   item note-as-kb-state-change?
			   nil new-color-pattern-or-error))))
	      (cond ((null color-change-error?)
		     (reclaim-slot-value-tree new-color-pattern-or-error))
		    (t
		     (let ((type-of-error (car-of-cons color-change-error?))
			   (error-args (cdr-of-cons color-change-error?)))
		       (reclaim-gensym-cons color-change-error?)
		       (cond ((eq type-of-error 'missing-color-region)
			      (missing-color-region-error
				item error-args))
			     ((eq type-of-error 'unnamed-color-region)
			      (unnamed-color-region-error
				item error-args))
			     ((eq type-of-error 'illegal-colors)
			      (illegal-colors-error error-args))
			(t nil)))))))
  :getter  ((item)
	    (cond ((or (frame-of-class-p item 'type-in-box)
		       ;;in case loose-ends become items
		       (frame-of-class-p item 'loose-end))
		   (allocate-evaluation-structure nil))
		  (t
		   (let* ((color-pattern
			    (get-color-pattern-of-item
			      item nil nil nil item-color-pattern-returns-overrides-only-p))
			  ;;export-text-box-overrides 
			  ;;bug in get-text-box-color-pattern when nil
			  (exported-color-pattern
			    (export-color-pattern color-pattern)))
		     ;; this seems scary, since if it really is a tree
		     ;; then it could share conses with exported-color-pattern
		     (reclaim-slot-value-tree color-pattern)
		     exported-color-pattern)))))

(defun missing-color-region-error (entity region)
  (tformat-text-string
    "Cannot change the ~a region of ~NF.  The class definition for ~a ~
     does not have a region named ~a."
    region entity (class entity) region))

(defun unnamed-color-region-error (entity region)
  (tformat-text-string
    "Cannot change an unnamed color region in ~NF using its color name ~
       (~a).  Unnamed color regions cannot be changed."
    entity region))

(defun illegal-colors-error (illegal-colors)
  (twith-output-to-text-string
    (loop for remaining-colors on illegal-colors
	  when (loop for previous-illegal-colors on illegal-colors
		     until (eq previous-illegal-colors remaining-colors)
		     never (eq (car previous-illegal-colors)
			       (car remaining-colors)))
	    collect (car remaining-colors)
	      into remaining-colors-without-duplicates  using gensym-cons
	  finally
	    (loop for sublist on remaining-colors-without-duplicates doing
	      (write-evaluation-value (car sublist))
	      (cond ((null (cdr sublist)))
		    ((null (cddr sublist))
		     (twrite-string " and "))
		    (t
		     (twrite-string ", "))))
	    (twrite-string
	      (if (cdr remaining-colors-without-duplicates)
		  " are illegal colors"
		  " is an illegal color"))
	    (reclaim-gensym-list
	      remaining-colors-without-duplicates)
	    (reclaim-gensym-list illegal-colors))))

(def-virtual-attribute layer-position
    ((class block) integer ())
  :event-updates nil 
  :initial ((class) (declare (ignore class)) nil)
  ;; :setter					       
  :getter  ((block)
	    ;; bug (pbk) connections
	    (g2-get-item-layer-position block)))

(def-virtual-attribute name-box-item
    ((class entity) (or datum (no-item)) ())
  :event-updates nil 
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((entity)
	    (get-name-box-if-any? entity)))

(def-virtual-attribute attribute-display-items
    ((class entity) (or (sequence) (no-item)) ())
  :event-updates nil 
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((entity)	    
	    (loop for subblock being each subblock of entity
		  when (and (table-p subblock)
			    (attribute-display-p subblock)
			    (serve-item-p subblock))
		    collect subblock
		      into subblocks using eval-cons
		    finally
		    (when subblocks
		      (return (allocate-evaluation-sequence subblocks))))))

(def-virtual-attribute representation-type
    ((class item) symbol ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((item)
	   (representation-type-of-thing item)))

(def-virtual-attribute connection-is-directed
    ((class connection) truth-value ())
  :event-updates nil 
  :initial ((class) (declare (ignore class)) nil)
  :getter ((connection)
	   (make-evaluation-truth-value
	     (if (connection-directed?
		   (connection-for-this-connection-frame connection))
		 truth
		 falsity))))
			
(def-virtual-attribute connection-position-sequence
    ((class connection) (sequence) ())
  :event-updates nil 
  :initial ((class) (declare (ignore class)) nil)
  ;; :setter
  :getter ((connection)
	   (export-connection-position-sequence
	     (connection-for-this-connection-frame connection))))

(def-virtual-attribute text
    ((class name-box) text ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((item)
	   (let ((text-or-error
		   (get-text-of-attribute item 'text (class item))))
	     (cond ((symbolp text-or-error)
		    nil)
		   (t text-or-error)))))

(def-virtual-attribute type-in-box-variable-or-parameter
    ((class type-in-box) (or datum (no-item)) ()) 
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((tib)
	   (let ((slot-value (associated-variable-designation? tib))
		 (*current-computation-frame* tib))
	     (evaluate-designation slot-value nil))))

(def-virtual-attribute strip-text-mark
    ((class item) truth-value ())
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) nil)
  :getter ((item)
	   (if (strip-text-p item) evaluation-true-value evaluation-false-value))
  :setter
  ((item new-state)
   (cond ((evaluation-truth-value-is-true-p new-state)
	  (set-stripping-flags-as-specified item 1 0))
	 (t
	  (set-stripping-flags-as-specified item 0 0)))
   nil))

(def-virtual-attribute do-not-strip-text-mark
    ((class item) truth-value ())
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) nil)
  :getter ((item)
	   (if (do-not-strip-text-p item) evaluation-true-value evaluation-false-value))
  :setter
  ((item new-state)
   (cond ((evaluation-truth-value-is-true-p new-state)
	  (set-stripping-flags-as-specified item 0 1))
	 (t
	  (set-stripping-flags-as-specified item 0 0)))
   nil))

(def-generic-method get-workspace-representation-type (frame))

(def-class-method get-workspace-representation-type (system-item)
  (declare (ignore system-item))
  nil)


;; `accepts-connections-p'
;; auxiliary function for get-workspace-representation-type for entities

(defun accepts-connections-p (entity)
  ;; some user-defined-classes
  ;; (no-manual-connection-p object?) ; only a temporary thing??
  ;;  '(table text-box dial meter button
  ;;  definition chart freeform-table trend-chart))

  (let ((inheritance-path	; UGLY!! (optimization)
	  (class-inheritance-path
	    (class-description-slot entity))))
    (not (loop for class
		   in classes-that-do-not-normally-connect
	       thereis
	       (inheritance-path-memq
		 class inheritance-path)))))
  
;; The check for classes of objects not to consider could be speeded up
;; by obtaining a list of  classes in the inheritance path outside the main
;; loop, adapting the test to do a memq, and, if necessary, recycling the list of
;; classes at the end.  However, at present the classes-of-objects-not-to-consider
;; feature is lightly used, and this would be a very minor speed-up.



;; Entities

(def-class-method get-workspace-representation-type (entity)
  ;; decide whether has connections
  (cond
    ((accepts-connections-p entity)
     'icon-with-connections)
    (t
     'icon-without-connections)))

;; Loose-ends

(def-class-method get-workspace-representation-type (loose-end)
  (declare (ignore loose-end))
  'loose-end)

(def-class-method get-workspace-representation-type (connection)
  (declare (ignore connection))
  'connection)


;; Text-boxes

(def-class-method get-workspace-representation-type (text-box)
  (declare (ignore text-box))
  'text-box)


;; Tables 

(def-class-method get-workspace-representation-type (table)
  (cond
    ((attribute-display-p table)
     'attribute-display)
    ((short-representation-p table)
     'short-representation)
    ((classic-attribute-table-p table)
     'classic-attribute-table)
    ((attribute-table-with-header-p table)
     'attribute-table-with-header) ; includes class table-of-values
    ((attribute-table-p table)
     'attribute-table)))
;readout-table-p
;digital-clock-p
;attribute-table-like-p
;kind-of-attribute-table-if-any
;table-of-values
;menus
;explanation-table
;development-tabular-display
;graph

    
;; Displays
    
(def-class-method get-workspace-representation-type (readout-table)
  (declare (ignore readout-table))
  'attribute-table)

(def-class-method get-workspace-representation-type (dial)
  (declare (ignore dial))
  'dial)

(def-class-method get-workspace-representation-type (meter)
  (declare (ignore meter))
  'meter)

(def-class-method get-workspace-representation-type (trend-chart)
  (declare (ignore trend-chart))
  'trend-chart)

(def-class-method get-workspace-representation-type (graph)
  (declare (ignore graph))
  'graph)

(def-class-method get-workspace-representation-type (chart)
  (declare (ignore chart))
  'chart)

(def-class-method get-workspace-representation-type (freeform-table)
  (declare (ignore freeform-table))
  'freeform-table)


;; Buttons

(def-class-method get-workspace-representation-type (action-button)
  (declare (ignore action-button))
  'action-button)

(def-class-method get-workspace-representation-type (radio-button)
  (declare (ignore radio-button))
  'radio-button)

(def-class-method get-workspace-representation-type (check-box)
  (declare (ignore check-box))
  'check-box)

(def-class-method get-workspace-representation-type (slider)
  (declare (ignore slider))
  'slider)

(def-class-method get-workspace-representation-type (type-in-box)
  (declare (ignore type-in-box))
  'type-in-box)

(def-class-method get-workspace-representation-type (kb-workspace)
  (declare (ignore kb-workspace))
  'kb-workspace)



;; List of NON items that behave as items:
;; tables(transfered attribute tables and attribute-displays)
;; name-boxes    (??label-boxes)



;;; `get-item-specific-info'
;;; Does NOT reclaim its return value

(defun get-thing-specific-info (thing representation-type-name)
  (let* ((ws-representation-type
	   (ws-representation-type representation-type-name))
	 (property-getter
	   (and ws-representation-type
		(ws-representation-type-property-getter ws-representation-type)))
	 (additional-properties
	   (if property-getter
	       (funcall property-getter thing)
	       (allocate-evaluation-structure-inline))))
    additional-properties))

(defun get-item-specific-info (item)
  (let ((representation-type-name
	  (funcall-method 'get-workspace-representation-type item)))
    (get-thing-specific-info item representation-type-name)))


(defun get-bounds-of-thing (thing)
  (cond ((framep thing)
	 (get-item-bounds thing))
	((connectionp thing)
	 nil)
	(t
	 nil)))

(defun get-item-bounds (item)
  (make-structure-from-dimensions
    (left-edge-of-block item)
    (-f (top-edge-of-block  item))
    (right-edge-of-block item)
    (-f (bottom-edge-of-block item))))

(defun get-position-of-thing (thing)
  (cond ((framep thing)
	 (get-item-position thing))
	((connectionp thing)
	 (export-connection-position-sequence thing))
	(t nil)))

(defun export-connection-position-sequence (connection)
  (let ((connection-vertices-in-workspace
	  (connection-vertices-in-workspace connection)))
    (loop with tmplist = nil
	  with result = nil
	  for ((x . y)) on connection-vertices-in-workspace 
	  do
      (eval-push x tmplist)
      (eval-push (-f y) tmplist)
	  finally
	    (setf result
		  (allocate-evaluation-sequence
		    (nreverse tmplist)))
	    (reclaim-gensym-tree connection-vertices-in-workspace)
	    (return result))))
	    
(defun get-item-position (item)
  (allocate-evaluation-structure-inline
    'xpos (item-x-position item)
    'ypos (item-y-position item)))


#+old
(defun convert-list-of-children-to-child-handles
    (list-of-children)
  (loop with result = nil
	for child in list-of-children
	do
    (when (v5-tw-item-like-p child)
      (gensym-push (demand-item-handle child) result))
	finally
	  (return result)))

(defun-simple export-color-pattern (color-pattern)
  (loop with color-pattern-list = nil
	for (region . color) in color-pattern
	do
    (when color
      (eval-push region color-pattern-list)
      (eval-push color color-pattern-list))
	finally
	  (return
	    (allocate-evaluation-structure
	      (nreverse color-pattern-list)))))

(defun-simple import-color-pattern (color-pattern-structure)
  (loop with color-pattern = nil
	with bad-colors? = nil
	for (region . color)
	    being each evaluation-structure-pair of color-pattern-structure
	do
    (cond ((and (symbolp color)(gensym-color-p color))
	   (slot-value-push (slot-value-cons region color) color-pattern))
	  (t
	   (gensym-push color bad-colors?)))

	finally
	  (cond (bad-colors?
		 (reclaim-slot-value color-pattern)
		 (gensym-push 'illegal-colors bad-colors?)
		 (return bad-colors?))
		(t
		 (return (nreverse color-pattern))))))

(defun export-attributes-plist (attributes-plist)
  (let ((orientation (getfq attributes-plist 'REFLECTION-AND-ROTATION))
	(variable-overrides
	  (allocate-evaluation-structure
	    (copy-tree-including-leaves-using-eval-conses
	      (getfq attributes-plist 'VARIABLES))))
	(region-overrides
	  (export-color-pattern
	    (getfq attributes-plist 'ICON-COLOR-PATTERN))))
    (allocate-evaluation-structure-inline
      'orientation orientation
      'variable-overrides variable-overrides
      'region-overrides region-overrides)))


       




;;; Auxialiary function for `send-all-telewindows-new-kb-workspace-existence'

;;; `get-list-of-v5-mode-clients' whips up a list of v5 UI clients of g2
;;; as icp-sockets.  Currently it cheats and uses workstations in service
;;; as a basis set.  The caller of this function should reclaim-gensym-list
;;; on returned list.

;;; apparently defunct
(defun get-list-of-v5-mode-clients ()
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	when (and (window-is-in-v5-mode-p gensym-window )
		  (eq (type-of-gensym-window gensym-window) 'icp))
	  collect (remote-gensym-window-icp-socket gensym-window)
	    using gensym-cons))




(defun-void maybe-reclaim-update-info (cons-containing-reference-count update-info)
  (decff (car cons-containing-reference-count))
  (when (=f 0 (car-of-cons cons-containing-reference-count))
    (reclaim-gensym-tree update-info)
    (reclaim-gensym-cons cons-containing-reference-count)))



(defmacro class-overrides-slot-p (class-name slot-name)
  `(and (class-description ,class-name)
	(or (memq ,slot-name
		  (slots-local-to-class (class-description ,class-name)))
	    ;; try using class-has-override-on-slot-p
	    (memq ,slot-name
		  (inherited-slots-this-class-overrides
		    (class-description ,class-name))))))


;;; more generic interface that will work for sys class as well

(defun get-slot-init-form-defined-by-class (class-name slot-name)
  (when (class-overrides-slot-p class-name slot-name)
    (let* ((class-description
	     (class-description class-name))
	   (slot-description
	     ;; (slot-description-from-class class 'icon-description)
	     (and class-description
		(get-slot-description-of-class-description
		  slot-name class-description)))
	   (slot-init-form (and slot-description
				(slot-init-form slot-description))))
      slot-init-form)))

(defun get-drawing-description-slot-name-for-class (class-name)
   (cond ((class-description-of-class-p
		    (class-description class-name) 'connection)
	  'cross-section-pattern)
	 (t
	  'icon-description)))


;;; `slot-init-form-drawing-description'
;;; Returns a new list that must be reclaimed by the caller.

(defun slot-init-form-drawing-description (slot-init-form slot-name)
  (when slot-init-form
    (case slot-name
      (icon-description
       (let ((line-drawing-description
	       (copy-tree-using-gensym-conses
		 (icon-line-drawing-description slot-init-form))))
	 (setf line-drawing-description
	       (gensym-push
		 (height-of-icon slot-init-form)
		 line-drawing-description))
	 (gensym-push (width-of-icon slot-init-form)
		      line-drawing-description)))
      (cross-section-pattern
       (copy-tree-using-gensym-conses slot-init-form))
      (t nil))))

(defun get-drawing-description-defined-by-class (class-name)
  (let* ((slot-name
	   (get-drawing-description-slot-name-for-class class-name))
	 (slot-init-form
	   (get-slot-init-form-defined-by-class class-name slot-name))
	 (drawing-description
	   (slot-init-form-drawing-description slot-init-form slot-name)))
    drawing-description))






;;;; UI Client Interface and UI Client Session


;class-info-attributes
; class-name
; is-system-defined
; direct-superior-classes
; class-inheritance-path
; class-attributes get-static-attribute-descriptions-of-class
; instance-attributes get-instance-attribute-descriptions-of-class
(def-class (ui-client-interface (gsi-interface)
				not-user-instantiable
				define-predicate)
  (identifying-attributes
    ((item #|(frame-serial-number . nil)|# (class .  nil) (name . nil))
     #|(unique-identification uuid)|#
     )
    (system) user-overridable
    (type attributes-which-identify-a-network-item-reference)
    (save))
  (creation-attributes
    ((item (class-description . nil))
     #|(unique-identification uuid)|#
     )
    (system) user-overridable
    (type attributes-which-identify-a-network-item-reference)
    (save))
  (disable-interleaving-of-large-messages
    t (system) user-overridable do-not-put-in-attribute-tables
    (type yes-or-no) (save))
  
  (ui-client-interface-user-mode
    administrator vector-slot system)
  ;; the following two slots are for the callback that are
  ;; issued for the creation and deletion of modules
  (ui-client-interface-callback? nil vector-slot system) ; remote-procedure
  (ui-client-interface-callback-data nil vector-slot system) ;evaluation-value
  ;; the following two slots are for the g2-subscribe-to-item
  ;; subscriptions that are automatically placed on every module-information
  (ui-client-interface-module-information-callback?
    nil vector-slot system) ; remote-procedure
  (ui-client-interface-module-information-callback-data
    nil vector-slot system) ; evaluation-value
  (ui-client-interface-module-representations nil vector-slot system)
  (ui-client-interface-sessions nil vector-slot system)
  ;; for file progress updates
  (ui-client-interface-progress-callback? nil vector-slot system) ; remote-procedure
  (ui-client-interface-progress-callback-data nil vector-slot system) ;evaluation-value
  ;; for dialogs that aren't directly from ui (breakpoints, source code control)
  (ui-client-interface-dialog-callback? nil vector-slot system) ; remote-procedure
  (ui-client-interface-dialog-callback-data nil vector-slot system) ;evaluation-value
  (ui-client-interface-dialog-list nil vector-slot system))

(defun ui-client-interface-p-function (interface)
  (ui-client-interface-p interface))

(def-slot-value-reclaimer ui-client-interface-sessions (sessions interface)
  (declare (ignore interface))
  (loop for session in sessions
	do
    (loop with representations-list = (copy-list-using-gensym-conses
					(frame-representations session))
	  for representation in representations-list
	  when (frame-of-class-p representation 'callback-representation)
	    do
	      (delete-representation representation)
	  finally
	    (reclaim-gensym-list representations-list))
    (g2-release-ui-client-session session))
  (reclaim-slot-value-list sessions))

(def-slot-value-reclaimer ui-client-session-workspaces (workspaces session)
  (declare (ignore session))
  (reclaim-slot-value-list workspaces))

(defun-simple cleanup-parent-interface (interface client-session)
  (unless (frame-being-deleted-p interface)
    (setf (ui-client-interface-sessions interface)
	  (delete-slot-value-element
	    client-session
	    (ui-client-interface-sessions interface)))))

(def-slot-value-reclaimer ui-client-session-parent-interface
    (interface client-session)
  (cleanup-parent-interface interface client-session))

;;; Currently, if anyone deletes a ui-client-session, its
;;; nonce data will be left lying around, creating a leak
;;; Since they shouldn't be doing this we won't worry about it
;;; We take advantage of this supposed "leak" currently in that
;;; the nonce data is left lying around across a clear-kb.
;;;


;; Robert: these are alternatives to using g2-release-ui-client-session
;; that we stubbed some time ago. I'd go with the 'release' routine,
;; but is this route more guarenteed to get all cases?
;(defun-simple cleanup-ui-client-session-nonce (ui-client-session)
;  (declare (ignore ui-client-session))
;  ;some abstracted function based on note-that-session-has-logged-out 
;  )

;(def-slot-value-reclaimer ui-client-session-nonce (nonce ui-client-session)
;  (declare (ignore nonce))
;  (cleanup-ui-client-session-nonce ui-client-session))


;;; `Already-is-a-named-ui-session-from-this-client' is used to enforce a
;;; policy that self-authorizing, ok-based, 'named' tw2 clients can only
;;; use their codes if the connection is from a second-tier client rather
;;; than a third tier. [[ RP: is this said right ? ]] This is used in
;;; check-self-authorizing-tw2 to prohibit ok-based login-attempts
;;; when there is already a ui-client-session logged in through this
;;; ui-client-interface that uses anything other than a floating license
;;; for its authorization. 

(defun already-is-a-named-ui-session-from-this-client
    (gsi-interface machine-id)
  (let ((sessions (ui-client-interface-sessions gsi-interface)))
    (when sessions  ; cheap efficiency
      (loop
	for session in sessions
	thereis (when (ui-client-session-is-self-authorized-p session)
		  (string-equalw
		    (machine-id-of-ui-client-session session)
		    machine-id))))))


(defparameter ui-client-session-slots-to-save-for-clear-kb
  '(name-or-names-for-frame
    ui-client-session-user-mode
    ui-client-session-user-name
    ui-client-session-encoded-password
    specific-language-for-this-ui-client-session?
    ui-client-session-time-of-last-connection
    ui-client-session-network-host-name?
    ui-client-session-os-type?
    ui-client-session-license-level?
    ui-client-session-user-is-valid
    ui-client-session-mode-is-valid
    ui-client-session-status
    ui-client-session-nonce
    ui-client-session-os-user-name?))

(defparameter item-representation-slots-to-save-for-clear-kb
  '(item-representation-denotation
    item-representation-user-data-value
    representation-address
    callback-representation-callback-procedure
    callback-representation-callback-serial-number
    callback-representation-callback-subscription-handle))

(defparameter callback-representation-slots-to-save-for-clear-kb
  '(representation-address
    callback-representation-callback-procedure
    callback-representation-callback-serial-number
    callback-representation-callback-subscription-handle
    callback-representation-callback-subscription-handle))

(defparameter showing-representation-slots-to-save-for-clear-kb
  '(showing-representation-user-data-value
    representation-address
    callback-representation-callback-procedure
    callback-representation-callback-serial-number
    callback-representation-callback-subscription-handle))

(defun-simple get-slots-to-save-in-clear-kb-for-representation (representation)
  (frame-class-case representation
    (item-representation item-representation-slots-to-save-for-clear-kb)
    (showing-representation showing-representation-slots-to-save-for-clear-kb)
    (callback-representation callback-representation-slots-to-save-for-clear-kb)
    (t #+development
       (cerror "Continue"
	       "should have only been called on item/showing/callback-representation"))))

(define-slot-alias ui-client-specific-language specific-language-for-this-ui-client-session?
  ui-client-session)

(define-slot-alias ui-client-session-network-host-name ui-client-session-network-host-name?
  ui-client-session)

(define-slot-alias ui-client-session-operating-system-type ui-client-session-os-type?
  ui-client-session)

(define-slot-alias ui-client-session-user-name-in-operating-system ui-client-session-os-user-name?
  ui-client-session)


;;; The next nine forms are for the sole benefit of forward references

(defun ui-client-interface-sessions-function (interface)
  (ui-client-interface-sessions interface))

(defun ui-client-session-parent-interface-function (session)
  (ui-client-session-parent-interface session))

(defun ui-client-session-license-level?-function (session)
  (ui-client-session-license-level? session))

(defun set-ui-client-session-license-level (session level)
  (setf (ui-client-session-license-level? session) level))

(defun set-ui-client-session-user-is-valid (session boolean)
  (setf (ui-client-session-user-is-valid session) boolean))

(defun set-ui-client-session-mode-is-valid (session boolean)
  (setf (ui-client-session-mode-is-valid session) boolean))

(defun ui-client-session-status-function (session)
  (ui-client-session-status session))


;;; Call this function, not the setf to change the status

(defun set-ui-client-session-status (session symbol)
  (setf (ui-client-session-status session) symbol)
  (update-subscriptions-from-virtual-attribute-change
    session (virtual-attribute 'ui-client-connection-status) nil))

(defun ui-client-session-nonce-function (session)
  (ui-client-session-nonce session))


(define-system-rpc-access (g2-allocate-session-id (text) ui-client-interface)
    ()
  (let ((nonce (allocate-new-nonce)))
    (make-evaluation-text (t2-nonce-string nonce))))




;;; The next form is for the benefit of forward reference from
;;; controls.lisp

(defun-simple ui-client-session-workspaces-function (session)
  (ui-client-session-workspaces session))



;;; This is the entry point from tw2 when it is trying to self-authorize itself
;;; using an ok file. We pass in all the information in the file for the machine
;;; that the tw2 is running on, and do all the checking on this side of the
;;; fence.  If the codes are good, return true. Otherwise return the error
;;; symbol.

(defun-system-rpc (g2-validate-named-tw2 (datum)) ; boolean or symbol
    ((rpc-instance system-rpc-instance)
     (nonce text)
     (machine-id text)
     (code1 integer)
     (code2 integer)
     (code3 integer)
     (code4 integer)
     (code5 integer)
     (start-date (or (no-item) datum))  ; either nil or a sequence
     (end-date (or (no-item) datum))    ; ditto
     (desired-license-level symbol))
  
  (let* ((current-system-rpc-icp-socket?
	   (system-rpc-instance-icp-socket rpc-instance))
	 (gsi-interface?
	   (and current-system-rpc-icp-socket?
		(enclosing-interface-frame? current-system-rpc-icp-socket?))))
    
    (multiple-value-bind (authorized? error-symbol?)
	(check-self-authorizing-tw2
	  gsi-interface? nonce
	  machine-id
	  code1 code2 code3 code4 code5
	  start-date end-date
	  desired-license-level)
      
      (return-from-system-defined-rpc
	rpc-instance
	(eval-list
	  (if authorized?
	      evaluation-true-value
	      error-symbol?))))))




;;; change to defun-for-system-rpc
;;; never intended to be used in a KB

(defun-for-system-procedure g2-make-ui-client-session
    (ui-client-interface nonce user-mode user-name encoded-password
     user-name-in-os? language host-name os-type time-of-connection
     workspace-showing-callback?)
  (multiple-value-bind (session? error-symbol?)
      (make-ui-client-session-fully-featured
 	ui-client-interface nonce
	user-mode user-name encoded-password
 	user-name-in-os? language host-name os-type time-of-connection)
    (cond (error-symbol?
 	   (values session? error-symbol?))
 	  (t
	   (values
	     session?
	     nil
	     (if (null workspace-showing-callback?)
		 nil
		 (g2-subscribe-to-workspaces-showing
		   session?
		   workspace-showing-callback?
		   1)))))))

(define-system-rpc-access  (g2-make-ui-client-session (datum) ;(structure)
						      ui-client-interface)
    ((nonce text) ; i.e. a wide-string
     (user-mode (or (no-item) symbol))
     (user-name (or (no-item) symbol))
     (encoded-password (or (no-item) text))
     (user-name-in-os? (or (no-item) text))
     (language symbol)
     (host-name text)
     (os-type symbol)
     (workspace-showing-callback? (or (no-item) symbol)))
  (let ((gsi-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    (multiple-value-bind (session error-symbol? showing-handle)
 	(g2-make-ui-client-session
 	  gsi-interface nonce user-mode user-name encoded-password
 	  user-name-in-os? language host-name os-type (clock-get current-real-time)
	  workspace-showing-callback?)
      (allocate-evaluation-structure-inline
 	'session-item session
 	'error-symbol error-symbol?
	'workspace-showing-handle showing-handle))))


;;; only use this one if you really know what you are doing
(defun-simple make-ui-client-session-internal ()
  (let ((session (make-frame 'ui-client-session)))
    (set-do-not-save-in-kb session)
    (set-permanent-and-propagate session nil)
    (funcall-method 'activate-if-possible-and-propagate session)
    session))


#+obsolete
(defun report-failed-login (error-symbol)
  (declare (ignore error-symbol))
  ;(break "Got to the login failure reporter")
  (when (and nil
	     login-failure-handler?
	     (not (frame-has-been-reprocessed-p
		    login-failure-handler?
		    login-failure-handler-frame-serial-number?)))
    (start-procedure-invocation-in-place
      login-failure-handler?  ; procedure
      nil  ; priority?
      0    ; wait?
      0    ; local-stack
      nil  ; top-of-arguments-on-stack
      nil  ; argument-count
      nil  ; simulator-procedure?
      nil  ; completion-form?
      nil  ; top-of-stack?
      nil  ; validated-args-p
      nil  ; prepare-p
      )))


;;; The preferred way to make a ui-client-session: it creates the
;;; interconnections with the ui-client-interface, and the unique-identifiers,
;;; that result in this ui-client-session actually being useable.

(defun make-ui-client-session-fully-featured
    (client-interface nonce
     user-mode user-name nonce-encoded-password
     user-name-in-os? language host-name os-type time-of-connection)

  (let* ((session-from-previous-attempt?
	   (ui-client-session-for-nonce nonce))
	 (session (or session-from-previous-attempt?
		      (make-ui-client-session-internal)))
	 (error-symbol? nil)
	 (no-room-at-the-inn? nil)
	 (nonce-data nil))
    
    (unless error-symbol?
      (multiple-value-setq (nonce-data error-symbol?)
	;; is this a known nonce (session id) and is
	;; it in a state that would permit us to continue,
	;; e.g. we haven't tried to log in too many times.
	(data-for-valid-nonce nonce)))

    (unless error-symbol?
      (setf (ui-client-session-nonce session) nonce)
      (setf (ui-client-session-parent-interface session)
	    client-interface)
      (slot-value-pushnew
	session (ui-client-interface-sessions client-interface)))

    (unless (or error-symbol?
		(ui-client-session-is-self-authorized-p session))
      (setq no-room-at-the-inn?
	    ;; Determine whether this G2 will (still) let us in.
	    ;; Even if there was room in the T2 pool at the
	    ;; time we started to log in, if we didn't successfully
	    ;; complete on the first attempt (e.g. the password
	    ;; was wrong) then there is the possibility that
	    ;; some other ui-client session completed while
	    ;; we were retrying and it grabbed the last
	    ;; available license.
	    ;;   Should we refine the error message if we get
	    ;; this situation?
	    (not (some-floating-tw2-available-p)))
      (cond
	(no-room-at-the-inn?
	 (setq error-symbol? 'no-available-floating-licenses))
	(t (set-ui-client-session-license-level
	     session #.floating-lic-level))))

    
    (unless error-symbol?
      ;; populate the item. If we got here then we're going
      ;; to be returning it even if there is a later problem.
      (change-slot-value
	session 'ui-client-session-user-mode user-mode)
      (setf (ui-client-session-user-name session) user-name)
      (setf (ui-client-session-encoded-password session)
	    nonce-encoded-password)
      (setf (ui-client-session-os-user-name? session) user-name-in-os?)
      (change-slot-value
	session 'specific-language-for-this-ui-client-session? language)
      (setf (ui-client-session-network-host-name? session) host-name)
      (setf (ui-client-session-os-type? session) os-type)
      (setf (ui-client-session-time-of-last-connection session)
	    (copy-managed-float time-of-connection)))

    (unless error-symbol?
      (unless session-from-previous-attempt?
	(setf (t2-nonce-session-frame nonce-data) session)))
    
    (unless error-symbol?
      (setq error-symbol?
	    ;; vet these arguments (name, password, mode) for
	    ;; validity in a secure G2. If we pass this we're
	    ;; golden. 
	    (log-in-ui-client
	      nonce-data session user-name
	      nonce-encoded-password user-mode))
      ;; log-in-ui-client now invokes the user handler for
      ;; either success or failure, so there's no reason to
      ;; invoke it again in the failure case.  Besides which,
      ;; report-failed-login is no longer defined.  - jv, 11/20/98
      ;; (when error-symbol? (report-failed-login error-symbol?))
      )


    (when error-symbol?
      (set-ui-client-session-status session error-symbol?))
    
    (cond ((or no-room-at-the-inn?
	       (eq error-symbol? 'too-many-login-attempts))
	   (g2-release-ui-client-session session)
	   (values nil error-symbol?))
	  (error-symbol?
	   (values session error-symbol?))
	  (t (values session nil)))))



;;; Never to be used in a KB
(defun-for-system-procedure g2-release-ui-client-session (client-session)
  (unless deleting-ui-client-interfaces-for-clear-kb
    (log-out-ui-client client-session))
  (delete-frame client-session)
  nil)

(define-system-rpc-access (g2-release-ui-client-session () ui-client-interface)
  ((client-session (class ui-client-session)))
  (g2-release-ui-client-session client-session))

(defun-simple ui-client-session-valid-p (session)
  (session-has-successfully-logged-in-p session))



;;; throws a stack-error when the session is not the correct one
;;; for the interface. Must be called from within an rpc call
;;; in order to be any use, as it expects current-system-rpc-icp-socket?
;;; to be bound

(defun-void check-ui-client-session-for-rpc-access (session)
  (when (ui-client-session-doesnt-match-current-interface-p session)
    (stack-error cached-top-of-stack "session and interface do not match"))
  (unless (ui-client-session-valid-p session)
    (stack-error cached-top-of-stack "session not logged in")))

(defun-simple rpc-interface-class-ok? (rpc-instance
				    procedure-name
				    interface-class-name)
  (let* ((socket? (system-rpc-instance-icp-socket rpc-instance))
	 (interface (and socket? ; paranoid
			 (enclosing-interface-frame? socket?))))
    (cond ((or (null interface)
	       (not (frame-of-class-p interface
				      interface-class-name)))
	   (system-rpc-error
	     rpc-instance
	     'invalid-interface-class-for-rpc-call
	     (tformat-text-string "rpc call ~A not available to interface ~NF"
				  procedure-name
				  interface))
	   nil)
	  (t t))))

(defun-simple ui-client-session-ok-for-defun-system-rpc? (session rpc-instance call-sym)
  (cond ((not (rpc-interface-class-ok? rpc-instance call-sym 'ui-client-interface))
	 nil)
	((ui-client-session-doesnt-match-current-interface-p session)
	 (system-rpc-error
	   rpc-instance
	   'session-interface-mismatch
	   (tformat-text-string "~S" "session and interface do not match"))
	 nil)
	((not (ui-client-session-valid-p session))
	 (system-rpc-error
	   rpc-instance
	   'session-not-logged-in
	   (tformat-text-string "~S" "session not logged in"))
	 nil)
	(t t)))

(defun-simple ui-client-session-doesnt-match-current-interface-p (session)
  (and current-system-rpc-icp-socket?
       (not (eq (enclosing-interface-frame? current-system-rpc-icp-socket?)
		(ui-client-session-parent-interface session)))))

(defun-simple find-frame-representation-for-this-session (session frame representation-class)
  (loop with interface = (ui-client-session-parent-interface session)
	for representation in (frame-representations frame)
	when (and (frame-of-class-p representation representation-class)
		  (eq interface (get-interface-from-representation representation)))
	  return representation))

(defun-simple any-session-ws-associations-remaining-p (workspace interface)
  (loop for session in (ui-client-interface-sessions interface)
	thereis (loop for ws in (ui-client-session-workspaces session)
		      thereis (eq ws workspace))))

;;; returns nil if workspace already associated with session

(defun-simple associate-workspace-with-ui-session
    (ui-client-session workspace)
  (let ((already-there? (find workspace (ui-client-session-workspaces ui-client-session))))
    (unless already-there?
      (slot-value-push workspace (ui-client-session-workspaces ui-client-session)))
    (not already-there?)))

;;; returns t if the session was associated with the workspace,
;;; nil otherwise

(defun-for-system-procedure disassociate-workspace-from-ui-session
    (ui-client-session workspace)
  (cond ((find workspace (ui-client-session-workspaces ui-client-session))
	 (setf (ui-client-session-workspaces ui-client-session)
	       (delete-slot-value-element
		 workspace (ui-client-session-workspaces ui-client-session)))
	 t)
	(t nil)))




(def-virtual-attribute ui-client-user-mode
    ((class ui-client-item)
     (or (no-item) symbol)
     ())
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (make-evaluation-symbol
	 (get-slot-value client-item 'ui-client-session-user-mode)))
     (g2-window
       (make-evaluation-symbol
	 (get-slot-value client-item 'g2-user-mode)))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item))))
  :setter
  ((block new-mode)
   (multiple-value-bind (result error-string?)
       (check-and-install-new-g2-user-mode-for-login new-mode block)
    (declare (ignore result))
    ;; nil signifies success. A freshly cons'd string is returned
    ;; when there's been some kind of problem.
    error-string? )))


(def-virtual-attribute ui-client-user-name
    ((class ui-client-item)
     (or (no-item) symbol)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (make-evaluation-symbol
	 (get-slot-value client-item 'ui-client-session-user-name)))
     (g2-window
       (make-evaluation-symbol
	 (get-slot-value client-item 'g2-user-name)))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))

(def-virtual-attribute ui-client-remote-host-name
    ((class ui-client-item)
     (or (no-item) text)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (let ((host-text
	   (frame-class-case client-item
	     (ui-client-session
	       (get-slot-value client-item 'ui-client-session-network-host-name?))
	     (g2-window
	       (get-slot-value client-item 'g2-window-network-host-name?))
	     (t
	       #+development
	       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))
     (and host-text
	  (make-evaluation-text host-text)))))

(def-virtual-attribute ui-client-operating-system-type
    ((class ui-client-item)
     (or (no-item) symbol)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (make-evaluation-symbol
	 (get-slot-value client-item 'ui-client-session-os-type?)))
     (g2-window
       (make-evaluation-symbol
	 (get-slot-value client-item 'g2-window-os-type?)))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))

(def-virtual-attribute ui-client-time-of-last-connection
    ((class ui-client-item)
     (or (no-item) (structure))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (call-category-getter
	 'unix-time?
	 (get-slot-value client-item 'ui-client-session-time-of-last-connection)
	 client-item nil))
     (g2-window
       (call-category-getter
	 'unix-time?
	 (get-slot-value client-item 'g2-window-time-of-last-connection?)
	 client-item nil))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))
    
(def-virtual-attribute ui-client-user-name-in-operating-system
    ((class ui-client-item)
     (or (no-item) text)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (call-category-getter
	 'whole-string?
	 (get-slot-value client-item 'ui-client-session-os-user-name?)
	 client-item nil))
     (g2-window
       (call-category-getter
	 'whole-string?
	 (get-slot-value client-item 'g2-window-os-user-name?)
	 client-item nil))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))

(def-virtual-attribute ui-client-specific-language
    ((class ui-client-item)
     (or (no-item) symbol)
     ())
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (call-category-getter 'language?
	 (get-slot-value
	   client-item 'specific-language-for-this-ui-client-session?)
	 client-item nil))
     (g2-window
       (call-category-getter 'language?
	 (get-slot-value client-item 'specific-language-for-this-g2-window?)
	 client-item nil))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))

(def-virtual-attribute ui-client-connection-status
    ((class ui-client-item)
     (or (no-item) symbol)
     ())
  :event-updates  :within-putter
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (if (ui-client-session-valid-p client-item)
	   (make-evaluation-symbol 'connected)
	   (make-evaluation-symbol 'not-connected)))
     (g2-window
       (make-evaluation-symbol
	 (get-slot-value client-item 'g2-connection-status)))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))

(def-virtual-attribute ui-client-user-is-valid
    ((class ui-client-item)
     (or (no-item) truth-value)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (make-evaluation-truth-value
	 (get-slot-value client-item 'ui-client-session-user-is-valid)))
     (g2-window
       (make-evaluation-truth-value
	 (get-slot-value client-item 'g2-window-user-is-valid)))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))

(def-virtual-attribute ui-client-mode-is-valid
    ((class ui-client-item)
     (or (no-item) truth-value)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (make-evaluation-truth-value
	 (get-slot-value client-item 'ui-client-session-mode-is-valid)))
     (g2-window
       (make-evaluation-truth-value
	 (get-slot-value client-item 'g2-window-mode-is-valid)))
     (t
       #+development
       (cerror "Continue" "how come we got called on a ui-client-item that wasn't a g2-window or a ui-client-session: ~S" client-item)))))


(def-virtual-attribute ui-client-interface
    ((class ui-client-session)
     (or datum (no-item))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-session)
   (ui-client-session-parent-interface client-session)))


(def-virtual-attribute uses-floating-license
    ((class ui-client-item)
     (or (no-item) truth-value)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter
  ((client-item)
   (frame-class-case client-item
     (ui-client-session
       (make-evaluation-boolean-value
	 (=f #.floating-lic-level
	     (ui-client-session-license-level?-function client-item))))
     (g2-window
      (make-evaluation-boolean-value
       (let ((gensym-window? (map-g2-window-to-gensym-window client-item)))
	 (and gensym-window?
	      (=f #.floating-lic-level
		  (telewindows-license-level-of-gensym-window gensym-window?))))))
     (t #+development
	(cerror "Called on a ui-client-item that wasn't a g2-window or a ui-client-session" client-item)))))




(defvar local-ui-client-test-mode-p nil)



(def-class (showing-representation
	     callback-representation define-predicate)
  (showing-representation-user-data-value t vector-slot))

(defun-simple workspace-showing-on-ui-client-p (workspace)
  (loop for representation in (frame-representations workspace)
	thereis (frame-of-class-p representation 'ws-representation)))

(defun update-ui-client-for-hide
    (client-session workspace)
  (when local-ui-client-test-mode-p
    #+development
    (format t "Hiding ~s from ~s~%" workspace client-session)
    (return-from update-ui-client-for-hide))
  (loop with current-frame-serial-number-on-entry = (copy-frame-serial-number (current-frame-serial-number))
	with representations = (collect-frames-of-class (frame-representations client-session)
							'showing-representation)
	for representation in representations
       	do
    (when (and (not (frame-has-been-reprocessed-p representation
						  current-frame-serial-number-on-entry))
	       (representation-address-valid-p representation))
      (let* ((argument-list
	       (eval-list
		 (make-evaluation-symbol 'hide)        ; type of update
		 workspace
		 (allocate-evaluation-structure nil) ; no particulars for HIDE
		 (showing-representation-user-data-value representation)
		 (callback-representation-callback-subscription-handle representation))) ; the "subscription handle"
	     (address (representation-address representation))
	     (socket (getfq address 'socket)))
	(callback-representation-fire-callback
	  representation socket argument-list)))
	finally (reclaim-frame-serial-number current-frame-serial-number-on-entry)
		(reclaim-gensym-list representations)))

(defun update-ui-client-for-show
    (block workspace client-session go-to-block?
	   require-visibility? 
	   symbolic-x-scale? symbolic-y-scale?
	   symbolic-x-in-workspace? symbolic-y-in-workspace?
	   symbolic-x-in-window? symbolic-y-in-window?
	   x-offset-units? symbolic-x-offset-direction?
	   y-offset-units? symbolic-y-offset-direction?
	   x-magnification? y-magnification?
	   x-in-workspace? y-in-workspace?
	   x-in-window? y-in-window?
	   &optional ; make nonoptional? 
	   above-or-below-or-t-for-same?
	   specific-workspace-or-t-for-group?)
  (declare (ignore require-visibility? above-or-below-or-t-for-same?
		   specific-workspace-or-t-for-group?))
  (when local-ui-client-test-mode-p
    #+development
    (format t "Showing ~S on ~s~%" workspace client-session)
    (return-from update-ui-client-for-show))
  (loop with current-frame-serial-number-on-entry = (copy-frame-serial-number (current-frame-serial-number))
	with representations = (collect-frames-of-class (frame-representations client-session)
							'showing-representation)
	for representation in representations
       	do
    (when (and (not (frame-has-been-reprocessed-p representation
						  current-frame-serial-number-on-entry))
	       (representation-address-valid-p representation))
      (let* ((argument-list
	       (eval-list
		 (make-evaluation-symbol 'show)        ; type of update
		 workspace
		 (let ((structure (allocate-evaluation-structure-inline
				    'item (or block 'nil)
				    'go-to-item (or go-to-block? nil))))
		   (macrolet ((add-slot-if-needed (name value)
				;; assume value is a symbol
				`(when ,value
				   (setf (evaluation-structure-slot
					   structure ,name)
					 (make-evaluation-value-based-on-type
					   ,value)))))
		     (add-slot-if-needed 'symbolic-x-scale symbolic-x-scale?)
		     (add-slot-if-needed 'symbolic-y-scale symbolic-y-scale?)
		     (add-slot-if-needed 'symbolic-x-in-workspace
					 symbolic-x-in-workspace?)
		     (add-slot-if-needed 'symbolic-y-in-workspace
					 symbolic-y-in-workspace?)
		     (add-slot-if-needed 'symbolic-x-in-window
					 symbolic-x-in-window?)
		     (add-slot-if-needed 'symbolic-y-in-window
					 symbolic-y-in-window?)
		     (add-slot-if-needed 'x-offset-units x-offset-units?)
		     (add-slot-if-needed 'y-offset-units y-offset-units?)
		     (add-slot-if-needed 'symbolic-x-offset-direction
					 symbolic-x-offset-direction?)
		     (add-slot-if-needed 'symbolic-y-offset-direction
					 symbolic-y-offset-direction?)
		     (add-slot-if-needed 'x-magnification x-magnification?)
		     (add-slot-if-needed 'y-magnification y-magnification?)
		     (add-slot-if-needed 'x-in-workspace x-in-workspace?)
		     (add-slot-if-needed 'y-in-workspace y-in-workspace?)
		     (add-slot-if-needed 'x-in-window x-in-window?)
		     (add-slot-if-needed 'y-in-window y-in-window?)
		     structure))
		 (showing-representation-user-data-value representation)
		 (callback-representation-callback-subscription-handle representation))) ; the "subscription handle"
	     (address (representation-address representation))
	     (socket (getfq address 'socket)))
	(callback-representation-fire-callback
	  representation socket argument-list)))
	finally (reclaim-frame-serial-number current-frame-serial-number-on-entry)
		(reclaim-gensym-list representations)))



(defun-for-system-procedure g2-subscribe-to-workspaces-showing
    (client-session callback user-data)
  (let* ((representation
	   (cond
	     (current-system-rpc-icp-socket?
	      (make-representation
		current-system-rpc-icp-socket?
		client-session
		'showing-representation))
	     (t
	      (let ((g2-window?
		      (loop for w being class-instances of 'g2-window
			    when (eq 'local (g2-window-management-type w))
			      do (return w))))
		(unless g2-window?
		  (stack-error cached-top-of-stack "No local window for G2"))
		(make-representation
		  local-pseudo-socket
		  g2-window?
		  'showing-representation))))))
    (setf (callback-representation-callback-procedure representation)
	  (demand-representation-callback-remote-procedure-name callback))
    (cond
      (current-system-rpc-icp-socket?
       (setf (representation-address representation)
	     (slot-value-list 'socket current-system-rpc-icp-socket?
			      'session-id (icp-socket-session-id
					    current-system-rpc-icp-socket?))))
      (t
       (setf (representation-address representation)
	     (slot-value-list 'socket local-pseudo-socket))
       (frame-serial-number-setf (callback-representation-callback-serial-number representation)
				 (frame-serial-number callback))))
    (setf (showing-representation-user-data-value representation)
	  (copy-evaluation-value user-data))
    (store-callback-representation representation)))

(define-system-rpc-access (g2-subscribe-to-workspaces-showing (integer)
							      ui-client-interface)
    ((client-item (class ui-client-item))
     (callback symbol)
     (user-data datum))
  (g2-subscribe-to-workspaces-showing client-item callback user-data))

(defun-for-system-procedure g2-unsubscribe-to-workspaces-showing (subscription-index)
  (let ((representation? (representation-handle-gethash
			   (evaluation-integer-value subscription-index))))
    (when representation?
      (delete-representation representation?))
    evaluation-true-value))

(define-system-rpc-access (g2-unsubscribe-to-workspaces-showing
			    (truth-value) ui-client-interface)
    ((subscription-handle integer))
  (g2-unsubscribe-to-workspaces-showing subscription-handle))




;;; `Field Edit Subscriptions'
;;;
;;;
(defun-for-system-procedure g2-subscribe-to-field-edit-actions
    (client-session callback user-data)
  (let* ((representation
	   (cond
	     (current-system-rpc-icp-socket?
	      (make-representation
		current-system-rpc-icp-socket?
		client-session
		'field-edit-representation))
	     (t
	      (let ((g2-window?
		      (loop for w being class-instances of 'g2-window
			    when (eq 'local (g2-window-management-type w))
			      do (return w))))
		(unless g2-window?
		  (stack-error cached-top-of-stack "No local window for G2"))
		(make-representation
		  local-pseudo-socket
		  g2-window?
		  'field-edit-representation))))))
    (setf (callback-representation-callback-procedure representation)
	  (demand-representation-callback-remote-procedure-name callback))
    (cond
      (current-system-rpc-icp-socket?
       (setf (representation-address representation)
	     (slot-value-list 'socket current-system-rpc-icp-socket?
			      'session-id (icp-socket-session-id
					    current-system-rpc-icp-socket?))))
      (t
       (setf (representation-address representation)
	     (slot-value-list 'socket local-pseudo-socket))
       (frame-serial-number-setf (callback-representation-callback-serial-number representation)
				 (frame-serial-number callback))))
    (setf (field-edit-representation-user-data-value representation)
	  (copy-evaluation-value user-data))
    (store-callback-representation representation)))

(define-system-rpc-access (g2-subscribe-to-field-edit-actions (integer)
							      ui-client-interface)
    ((client-item (class ui-client-session))
     (callback symbol)
     (user-data datum))
  (g2-subscribe-to-field-edit-actions client-item callback user-data))

(defun-for-system-procedure g2-unsubscribe-to-field-edit-actions (subscription-index)
  (let ((representation? (representation-handle-gethash
			   (evaluation-integer-value subscription-index))))
    (when representation?
      (delete-representation representation?))
    evaluation-true-value))

(define-system-rpc-access (g2-unsubscribe-to-field-edit-actions
			    (truth-value) ui-client-interface)
    ((subscription-handle integer))
  (g2-unsubscribe-to-field-edit-actions subscription-handle))





(defun-for-system-procedure g2-subscribe-to-modules
    (ui-client-interface
      kb-callback kb-callback-data
      module-information-callback module-information-callback-data)
  (setf (ui-client-interface-callback? ui-client-interface)
	(demand-representation-callback-remote-procedure-name kb-callback))
  (setf (ui-client-interface-callback-data ui-client-interface)
	kb-callback-data)
  (setf (ui-client-interface-module-information-callback? ui-client-interface)
	(demand-representation-callback-remote-procedure-name
	  module-information-callback))
  (setf (ui-client-interface-module-information-callback-data ui-client-interface)
	module-information-callback-data)
  (let ((result
	  (allocate-evaluation-structure-inline
	    'modules
	    (allocate-evaluation-sequence
	      (loop for module-info being each class-instance of 'module-information
		    collect
		    (make-new-module-info-structure
		      module-info ui-client-interface) using eval-cons))
	    'logbook
	    (get-current-logbook-sequence)
	    'message-board
	    (get-current-message-board-sequence))))
    result))

(define-system-rpc-access (g2-subscribe-to-modules ((structure))
						   ui-client-interface)
    (;(session (class ui-client-session))
     (module-callback symbol)
     (module-callback-data datum)
     (module-information-callback symbol)
     (module-information-callback-data datum))
  (let ((gsi-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    ;(check-ui-client-session-for-rpc-access session)
    (g2-subscribe-to-modules
      gsi-interface module-callback module-callback-data
      module-information-callback module-information-callback-data)))

(defun-simple make-evaluation-sequence-of-top-level-modules (module-name)
  (and module-name
       (loop for workspace 
		 being class-instances of 'kb-workspace
	     ;; Only top level workspaces.
	     when (and (null (parent-of-subworkspace? workspace))
		       (eq module-name (module-this-is-part-of? workspace)))
	       collect workspace into lst using eval-cons
	       finally
	       (when lst
		 (return (allocate-evaluation-sequence lst))))))


(defun make-new-module-info-structure (module-info ui-client-interface)
    (let* ((name-denotation-sequence
	     (allocate-evaluation-sequence
		 (eval-list
		   (allocate-evaluation-structure-inline
		     'type 'attribute
		     'name 'top-level-module))))
	   (required-modules-denotation-sequence
	     (allocate-evaluation-sequence
		 (eval-list
		   (allocate-evaluation-structure-inline
		     'type 'attribute
		     'name 'directly-required-modules))))
	   (current-system-rpc-icp-socket?
	     (gsi-interface-icp-socket ui-client-interface))
	   (name-subscription-result
	     ;; structure containing 'initial-value and 'subscription-handle
	     (g2-subscribe-to-item
	       module-info
	       name-denotation-sequence
	       (ui-client-interface-module-information-callback?
		 ui-client-interface)
	       (copy-if-evaluation-value
		 (ui-client-interface-module-information-callback-data
		   ui-client-interface))
	       evaluation-false-value))
	   (required-modules-subscription-result
	     ;; structure containing 'initial-value and 'subscription-handle
	     (g2-subscribe-to-item
	       module-info
	       required-modules-denotation-sequence
	       (ui-client-interface-module-information-callback?
		 ui-client-interface)
	       (copy-if-evaluation-value
		 (ui-client-interface-module-information-callback-data
		   ui-client-interface))
	       evaluation-false-value))
	   (name-subscription-handle
	     (evaluation-structure-slot name-subscription-result 'subscription-handle))
	   (required-modules-subscription-handle
	     (evaluation-structure-slot required-modules-subscription-result 'subscription-handle))
	   (module-structure
	     (allocate-evaluation-structure-inline
	       'module-information
	       module-info
	       'is-top-level
	       (make-evaluation-boolean-value
		 (eq module-info (get-system-table-currently-in-force 'module-information)))
	       'subscription-handles
	       (allocate-evaluation-sequence
		 (eval-list name-subscription-handle required-modules-subscription-handle))
	       'other-system-tables
	       (allocate-evaluation-sequence
		 (loop for table-name in (compute-system-table-choices t)
		       unless (eq table-name 'module-information)
		       collect (symbol-value table-name) using eval-cons))
	       'subscription-initial-value
	       (allocate-evaluation-structure-inline
		 'top-level-module
		 (copy-if-evaluation-value
		   (evaluation-structure-slot name-subscription-result 'initial-value))
		 'directly-required-modules
		 (copy-if-evaluation-value
		   (evaluation-structure-slot required-modules-subscription-result 'initial-value))
		 'top-level-kb-workspaces
		 (make-evaluation-sequence-of-top-level-modules
		   (and module-info
			(top-level-kb-module? module-info))))))
	   (name-representation
	     (representation-handle-gethash name-subscription-handle))
	   (required-modules-representation
	     (representation-handle-gethash required-modules-subscription-handle)))
      #+development
      (unless (and name-representation required-modules-representation)
	(cerror "go on, but not with my blessing" "uh-oh"))
      (slot-value-pushnew
	name-representation
	(ui-client-interface-module-representations ui-client-interface))
      (slot-value-pushnew
	required-modules-representation
	(ui-client-interface-module-representations ui-client-interface))
      (reclaim-evaluation-structure name-subscription-result)
      (reclaim-evaluation-structure required-modules-subscription-result)
      module-structure))

(defun-for-system-procedure g2-unsubscribe-to-modules
    (ui-client-interface)
  (setf (ui-client-interface-callback? ui-client-interface) nil)
  (reclaim-if-evaluation-value
    (ui-client-interface-callback-data ui-client-interface))
  (setf (ui-client-interface-callback-data ui-client-interface) nil)
  (reclaim-if-evaluation-value
    (ui-client-interface-callback-data ui-client-interface))
  (setf (ui-client-interface-callback-data ui-client-interface) nil)
  (loop for representation
	    in (ui-client-interface-module-representations ui-client-interface)
	do
    (delete-representation representation))
  (reclaim-slot-value-list
    (ui-client-interface-module-representations ui-client-interface))
  (setf
    (ui-client-interface-module-representations ui-client-interface)
    nil))

(define-system-rpc-access (g2-unsubscribe-to-modules () ui-client-interface)
    ()
  (let ((gsi-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    (g2-unsubscribe-to-modules gsi-interface)))

(defun inform-ui-client-interfaces-of-module-creation (module-info)
  (loop for ui-client-interface being each class-instance of 'ui-client-interface
	for icp-socket? = (get-slot-value ui-client-interface 'gsi-interface-icp-socket)
	when (and icp-socket?
		  (/=f (icp-connection-state icp-socket?) icp-connection-closed))
	  do
	    (inform-ui-client-interface-of-module-creation module-info ui-client-interface)))

(defun inform-ui-client-interface-of-module-creation (module-info ui-client-interface)
  (let ((callback? (ui-client-interface-callback? ui-client-interface)))
    (when (and callback?
	       (gsi-interface-icp-socket ui-client-interface))
      (let ((arg-list
	      (eval-list
		'create
		(make-new-module-info-structure
		  module-info ui-client-interface))))
	(start-remote-representation-callback
	  (gsi-interface-icp-socket ui-client-interface) callback? arg-list)))))

(defun inform-ui-client-interfaces-of-module-deletion (module-info)
  (loop for ui-client-interface being each class-instance of 'ui-client-interface
	as callback? = (ui-client-interface-callback? ui-client-interface)
	for icp-socket? = (get-slot-value ui-client-interface 'gsi-interface-icp-socket)
	when (and icp-socket?
		  (/=f (icp-connection-state icp-socket?) icp-connection-closed))
	  do
    (loop with representations
	    = (ui-client-interface-module-representations ui-client-interface)
	  with representations-to-delete = ()
	  for representation in representations
	  when (eq module-info (represented-frame representation))
	    do
	      (gensym-push representation representations-to-delete)
	  finally
	    (loop for representation in representations-to-delete
		  do
	      (setf (ui-client-interface-module-representations ui-client-interface)
		    (delete-slot-value-element
		      representation
		      (ui-client-interface-module-representations ui-client-interface))))
	    (reclaim-gensym-list representations-to-delete))
    (when (and callback?
	       (gsi-interface-icp-socket ui-client-interface))
      (let ((arg-list
	      (eval-list
		'delete module-info)))
	(start-remote-representation-callback
	  (gsi-interface-icp-socket ui-client-interface) callback? arg-list)))))

(defun inform-ui-client-interfaces-of-clear-kb ()
  (loop for ui-client-interface being each class-instance of 'ui-client-interface
	as callback? = (ui-client-interface-callback? ui-client-interface)
	as icp-socket? = (gsi-interface-icp-socket ui-client-interface)
	do
    (reclaim-slot-value-list
      (ui-client-interface-module-representations ui-client-interface))
    (setf (ui-client-interface-module-representations ui-client-interface) nil)
    (when (and callback?
	       icp-socket?
	       (/=f (icp-connection-state icp-socket?) icp-connection-closed))
      (let ((arg-list
	      (eval-list
		'clear-kb nil)))
	(start-remote-representation-callback icp-socket? callback? arg-list)))))



(defun-void inform-ui-client-interfaces-of-top-level-workspace-assignment-change
    (kb-workspace newly-becoming-top-level-workspace? module-name)
  (loop for ui-client-interface being each class-instance of 'ui-client-interface
	for icp-socket? = (get-slot-value ui-client-interface 'gsi-interface-icp-socket)
	when (and icp-socket?
		  (/=f (icp-connection-state icp-socket?) icp-connection-closed))
	  do
	    (inform-ui-client-interface-of-top-level-workspace-assignment-change
	      kb-workspace newly-becoming-top-level-workspace? module-name ui-client-interface)))

(defun-void inform-ui-client-interface-of-top-level-workspace-assignment-change
    (kb-workspace newly-becoming-top-level-workspace? module-name ui-client-interface)
  (let ((callback? (ui-client-interface-callback? ui-client-interface))
	(icp-socket? (gsi-interface-icp-socket ui-client-interface)))
    (when (and callback?
	       icp-socket?
	       (/=f (icp-connection-state icp-socket?) icp-connection-closed))
      (let* ((particulars
	       (allocate-evaluation-structure-inline
		 'kb-workspace
		 kb-workspace
		 'module-name
		 module-name))
	     (modfn-code
	       (if newly-becoming-top-level-workspace?
		   'add-as-top-level-workspace
		   'remove-as-top-level-workspace))
	     (arg-list
	       (eval-list
		 modfn-code
		 particulars)))
	(start-remote-representation-callback icp-socket? callback? arg-list)))))

(defun inform-ui-client-interfaces-of-general-update (update-type data)
  (loop for ui-client-interface being each class-instance of 'ui-client-interface
	as callback? = (ui-client-interface-callback? ui-client-interface)
	as icp-socket? = (gsi-interface-icp-socket ui-client-interface)
	do
    (when (and callback?
	       icp-socket?
	       (/=f (icp-connection-state icp-socket?) icp-connection-closed))
      (let ((arg-list
	      (eval-list update-type data)))
	(start-remote-representation-callback icp-socket? callback? arg-list)))))


(defun-simple file-progress-as-structure (progress-frame)
  (allocate-evaluation-structure
    (loop for slot-description in (slot-descriptions (class-description (class progress-frame)))
	  when (memq (defining-class slot-description) '(file-progress module-load-request))
	    nconc (eval-list (pretty-slot-name slot-description)
			     (copy-if-evaluation-value
			       (get-slot-description-value progress-frame slot-description))))))


;;; The function `note-file-progress' updates native progress bars for a file
;;; operation, on all workstations which support them.

(defun note-file-progress (progress-frame delete-p)
  (let* ((filename? (namestring-of-file-in-progress? progress-frame))
	 (direction? (direction-of-file-progress? progress-frame))
	 (bytes? (number-of-kb-characters-so-far? progress-frame))
	 (lines? (progress-through-file progress-frame))
	 (total? (length-of-file-in-characters? progress-frame))
	 (status? (status-of-file-progress? progress-frame)))
    (cond (delete-p
	   (note-progress))		; Remove the progress bar.
	  ((and (null direction?) (null total?)) ; Don't know what to display yet.
	   (note-progress #w"" 0))
	  ((or bytes? lines? status?)
	   ;; Note: total? is null during module-loading-schedule creation or
	   ;; save-kb. Direction? is frequently null.
	   (let* ((numerator (or bytes? total? (if (eql lines? 0) 0) 100))
		  (denominator (or total? 100))
		  (note (twith-output-to-text-string
			  (tformat "~a~a"
				   ;; Terminology assumes it is a KB.
				   (cond ((eq direction? 'output)
					  "Saving ")
					 ((or (eq direction? 'input) total?)
					  "Loading ")
					 (t ""))
				   filename?)
			  (if (and lines? (eq direction? 'output))
			      (tformat "  ~d lines " lines?)
			      (tformat "  ~d%" (compute-percentage numerator denominator)))
			  (when status?
			    (tformat "  [~a]" (if (and (eq direction? 'output)
						       (eq status? 'open))
						  'writing
						  status?))))))
	     (note-progress note numerator denominator)
	     (reclaim-text-string note)))
	  (t
	   (dwarn "Ignoring call to note-file-progress")))))


;;; The function `note-update-to-file-progress' updates progress notes for a
;;; file operation for T2 and native TW clients.

(defun note-update-to-file-progress (progress-frame &optional change)
  (note-file-progress progress-frame (eq change 'delete)) ; native progress bars
  (loop with info? = nil
	for ui-client-interface being each class-instance of 'ui-client-interface
	for callback? = (ui-client-interface-progress-callback? ui-client-interface)
	for icp-socket? = (get-slot-value ui-client-interface 'gsi-interface-icp-socket)
	when (and callback? icp-socket?
		  (/=f (icp-connection-state icp-socket?) icp-connection-closed))
	  do 
	     (start-remote-representation-callback
	       icp-socket?
	       callback?
	       (eval-list
		 (copy-evaluation-value
		   (or info? (setq info? (file-progress-as-structure progress-frame))))
		 (make-evaluation-boolean-value (eq change 'delete))))
	finally (reclaim-if-evaluation-value info?)))

(define-system-rpc-access (g2-subscribe-to-file-progress-changes ()
								 ui-client-interface)
    ((progress-callback symbol)
     (progress-callback-data datum))
  (let ((ui-client-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    (setf (ui-client-interface-progress-callback? ui-client-interface)
	  (demand-representation-callback-remote-procedure-name progress-callback))
    (setf (ui-client-interface-progress-callback-data ui-client-interface) progress-callback-data))
  nil)

(define-system-rpc-access (g2-unsubscribe-to-file-progress-changes ()
								   ui-client-interface)
    ()
  (let ((ui-client-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    (setf (ui-client-interface-progress-callback? ui-client-interface) nil)
    (reclaim-if-evaluation-value (ui-client-interface-progress-callback-data ui-client-interface))
    (setf (ui-client-interface-progress-callback-data ui-client-interface) nil))
  nil)


(defvar current-t2-dialog-sequence-number 0)
(defun-simple get-next-sequence-number-for-dialog-for-t2 ()
  (if (=f current-t2-dialog-sequence-number most-positive-fixnum)
      0
      (incff current-t2-dialog-sequence-number)))

(defvar t2-dialog-result-alist nil)

;enter-dialog-for-pause-for-internal-error-or-debug
;maybe-put-up-scc-timeout-dialog-for-workstation
;ask-user-about-checking-pathname-out-for-editing
;warn-about-editing-item
(defun enter-dialog-for-t2 (dialog-name dialog-as-eval-list continuation ui-client-interface? client-item?
					&optional sequence-number)
  (let ((info (allocate-evaluation-sequence
		(loop for entry in dialog-as-eval-list
		      for (type text name value) = entry
		      collect (if (eq type 'item)
				  (allocate-evaluation-structure-inline ; type is item
				    'type type 'item text 'name name)
				  (allocate-evaluation-structure-inline ; type is text, button, or check-box
				    'type type 'text text 'name name 'value value))
			using eval-cons)))
	(current-dialog-sequence-number (or sequence-number
					    (get-next-sequence-number-for-dialog-for-t2))))
    (reclaim-eval-list dialog-as-eval-list)
    (if ui-client-interface?
	(enter-dialog-for-ui-client-interface
	  dialog-name info continuation ui-client-interface? client-item? current-dialog-sequence-number)
	(loop for ui-client-interface being each class-instance of 'ui-client-interface
	      do (enter-dialog-for-ui-client-interface
		   dialog-name info continuation ui-client-interface client-item? current-dialog-sequence-number)))
    (when (consp continuation)
      (reclaim-slot-value-list continuation))
    (reclaim-evaluation-value info)
    current-dialog-sequence-number))

(defun some-dialog-for-t2-has-returned-p (sequence-number)
  (assoc sequence-number t2-dialog-result-alist))

(defun leave-dialog-for-t2 (sequence-number)
  (loop for ui-client-interface being each class-instance of 'ui-client-interface
	do (leave-dialog-for-ui-client-interface ui-client-interface nil sequence-number))
  (values (get-values-for-t2-dialog sequence-number)))

(defun get-values-for-t2-dialog (sequence-number)
  (let ((a (assoc sequence-number t2-dialog-result-alist)))
    (when a
      (setq t2-dialog-result-alist (delete-gensym-element a t2-dialog-result-alist))
      (loop with button = nil
	    for e being each evaluation-sequence-element of (cdr a)
	    for type = (evaluation-structure-slot e 'type)
	    for name = (evaluation-structure-slot e 'name)
	    for value = (evaluation-structure-slot e 'value)
	    when (eq type 'button)
	      do (setq button name)
	    when (eq type 'check-box)
	      collect (slot-value-cons name (evaluation-boolean-is-true-p value))
		into check-box-values
		using slot-value-cons
	    finally (reclaim-evaluation-value (cdr a))		   
		    (reclaim-gensym-cons a)
		    (return (values button check-box-values))))))

(defun enter-dialog-for-ui-client-interface
    (dialog-name info continuation ui-client-interface client-item? sequence-number)
  (let ((callback? (ui-client-interface-dialog-callback? ui-client-interface)))
    (when callback?
      (let ((icp-socket? (get-slot-value ui-client-interface 'gsi-interface-icp-socket)))
	(when (and icp-socket?
		   (/=f (icp-connection-state icp-socket?) icp-connection-closed))
	  (slot-value-push (slot-value-list sequence-number
					    dialog-name
					    (if (consp continuation)
						(copy-list-using-slot-value-conses
						  continuation)
						continuation))
			   (ui-client-interface-dialog-list ui-client-interface))
	  (start-remote-representation-callback
	    icp-socket?
	    callback?
	    (eval-list
	      sequence-number
	      client-item?
	      dialog-name
	      'enter
	      (copy-evaluation-value info))))))))

;;SEE NOTE BY start-inspect-session-internal when changing this function	     
(defun-void notify-t2-for-local-recompile (new-info-list)
  (update-dialog-for-t2 'recompile new-info-list 'status-update))

(defun-void update-dialog-for-t2 (dialog-name new-info-list update-type)
  (loop for ui-client-interface being each class-instance of 'ui-client-interface
	do (update-dialog-for-ui-client-interface ui-client-interface nil dialog-name new-info-list update-type)))

(defun-simple get-dialog-info (dialog-name ui-client-interface)
  (loop for info in (ui-client-interface-dialog-list ui-client-interface)
			       when (eq dialog-name (cadr info))
				 return info))

(defun-void update-dialog-for-ui-client-interface (ui-client-interface client-item? dialog-name new-info-list update-type)
  (let ((callback? (ui-client-interface-dialog-callback? ui-client-interface)))
    (when callback?
      (let ((dialog-info (get-dialog-info dialog-name ui-client-interface)))
	(when dialog-info
	  (let ((icp-socket? (get-slot-value ui-client-interface 'gsi-interface-icp-socket))
		(sequence-number (car dialog-info)))
	    (when (and icp-socket?
		       (/=f (icp-connection-state icp-socket?) icp-connection-closed))
	      (start-remote-representation-callback
		icp-socket?
		callback?
		(eval-list
		  sequence-number
		  client-item?
		  dialog-name
		  'update
		  (allocate-evaluation-sequence
		    (eval-list
		      (allocate-evaluation-structure-inline
			'update-type
			update-type
			'update-info
			(allocate-evaluation-sequence (copy-list-using-eval-conses new-info-list))))))))))))))

(defun leave-dialog-for-ui-client-interface (ui-client-interface client-item? sequence-number)
  (let ((callback? (ui-client-interface-dialog-callback? ui-client-interface)))
    (when callback?
      (let ((a (assoc sequence-number
		      (ui-client-interface-dialog-list ui-client-interface))))
	(when a
	  (setf (ui-client-interface-dialog-list ui-client-interface)
		(delete-slot-value-element
		  a
		  (ui-client-interface-dialog-list ui-client-interface)))
	  (let ((dialog-name (cadr a))
		(continuation (caddr a)))
	    (when (consp continuation)
	      (reclaim-slot-value-list continuation))
	    (reclaim-slot-value-list a)
	    (let ((icp-socket? (get-slot-value ui-client-interface 'gsi-interface-icp-socket)))
	      (when (and icp-socket?
			 (/=f (icp-connection-state icp-socket?) icp-connection-closed))
		(start-remote-representation-callback
		  icp-socket?
		  callback?
		  (eval-list
		    sequence-number
		    client-item?
		    dialog-name
		    'leave
		    nil))))))))))

(defun-simple remove-dialog-info-from-ui-client-interface-dialog-list (dialog-sequence-number ui-client-interface)
  (let* ((dialog-info (assoc dialog-sequence-number
			     (ui-client-interface-dialog-list ui-client-interface)))
	 (continuation
	   (caddr dialog-info)))
    (setf (ui-client-interface-dialog-list ui-client-interface)
	  (delete-slot-value-element
	    dialog-info
	    (ui-client-interface-dialog-list ui-client-interface)))
    (reclaim-slot-value-list dialog-info)
    (when (consp continuation)
      (reclaim-slot-value-list continuation))))
  
(define-system-rpc-access (g2-return-values-to-unsolicited-dialog () ui-client-interface)
    ((dialog-sequence-number integer)
     (dialog-values (sequence))
     (client-item (class ui-client-session)))
  (let ((ui-client-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    (let ((a (assoc dialog-sequence-number
		    (ui-client-interface-dialog-list ui-client-interface))))
      (when a
	(unless (assoc dialog-sequence-number t2-dialog-result-alist)
	  (gensym-push (gensym-cons dialog-sequence-number
				    (copy-evaluation-value dialog-values))
		       t2-dialog-result-alist))
	(let ((continuation (caddr a)))
	  (cond ((null continuation)
		 (remove-dialog-info-from-ui-client-interface-dialog-list dialog-sequence-number ui-client-interface))
		((consp continuation)
		 (apply (car continuation) dialog-sequence-number client-item (cdr continuation)))		 
		(t
		 (funcall continuation dialog-sequence-number client-item)))))))
  nil)

(define-system-rpc-access (g2-subscribe-to-unsolicited-dialogs ()
							       ui-client-interface)
    ((dialog-callback symbol)
     (dialog-callback-data datum))
  (let ((ui-client-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    (setf (ui-client-interface-dialog-callback? ui-client-interface)
	  (demand-representation-callback-remote-procedure-name 
	    dialog-callback))
    (setf (ui-client-interface-dialog-callback-data ui-client-interface) dialog-callback-data))
  nil)

(define-system-rpc-access (g2-unsubscribe-to-unsolicited-dialogs ()
								 ui-client-interface)
    ()
  (let ((ui-client-interface
	  (enclosing-interface-frame? current-system-rpc-icp-socket?)))
    (setf (ui-client-interface-dialog-callback? ui-client-interface) nil)
    (reclaim-if-evaluation-value (ui-client-interface-dialog-callback-data ui-client-interface))
    (setf (ui-client-interface-dialog-callback-data ui-client-interface) nil))
  nil)


;; represent and unrepresent-workspace should change showing status
;;    (and workspace?
;;        ( image-planes-this-is-on workspace?))
;; becomes
;;    (and workspace?
;;        (or ( image-planes-this-is-on workspace?)
;;            (has-at-least-one-workspace-representation *))
;;   represent and unrepresent should also trigger status changes.
;;
;; add api for subscribe to umc's
;; add code for firing embedded rules correctly (binding this window)
;; 
;; more api code multiple subscribe




;;;; SYS-PROCs in file-sysproc.lisp

(define-system-rpc-access (g2-files-in-directory
 			    ((class text-list)))
    ((directory-string text))
  (multiple-value-bind (file-names-list-frame error-message)
      (files-in-directory-lisp-side directory-string)
    (cond ((string=w error-message #w"")
	   file-names-list-frame)
	  (t
	   (delete-frame file-names-list-frame)
	   (stack-error cached-top-of-stack
			"G2-FILES-IN-DIRECTORY() failed ~a"
			error-message)))))

(define-system-rpc-access (g2-subdirectories-in-directory
 			    ((class text-list)))
    ((directory-string text))
  (multiple-value-bind (directory-names-list-frame error-message)
      (subdirectories-in-directory-lisp-side directory-string)
    (cond ((string=w error-message #w"")
	   directory-names-list-frame)
	  (t
	   (delete-frame directory-names-list-frame)
	   (stack-error cached-top-of-stack
			(tformat-text-string
			  "G2-SUBDIRECTORIES-IN-DIRECTORY() failed ~a"
			  error-message))))))

(define-system-rpc-access (g2-get-host-name (text))
    ()
  (let ((host-name?
	  (get-host-name-lisp-side)))
    (if (text-string= host-name? #w"")
	(stack-error cached-top-of-stack
		     "GET-HOST-NAME() failed.")
	host-name?)))

(define-system-rpc-access (g2-get-port-number-or-name (text))
    ()
  (let ((port-name?
	  (get-port-number-or-name-lisp-side)))
    (if (text-string= port-name? #w"")
	(stack-error cached-top-of-stack
		     "GET-PORT-NUMBER-OR-NAME() failed.")
	port-name?)))

(define-system-rpc-access (g2-get-port-number-or-name-given-index
			    (text))
    ((index integer))
    (let ((port-name?
	    (get-port-number-or-name-given-index-lisp-side index)))
      (if (text-string= port-name? #w"")
	  (stack-error cached-top-of-stack
		       "GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX(~s) failed."
			   index)
	  port-name?)))

(define-system-rpc-access (g2-get-structured-version ((structure)))
    ()
  (let ((software-version? (system-version-information-as-structure)))
    (if (null software-version?)
	(stack-error cached-top-of-stack
		     "G2-GET-VERSION() failed.")
	software-version?)))

(define-system-rpc-access (g2-get-software-version
 			    (text))
    ()
  (let ((software-version? (get-software-version-lisp-side)))
    (if (text-string= software-version? #w"")
	(stack-error cached-top-of-stack
		     "GET-SOFTWARE-VERSION() failed.")
	software-version?)))

(define-system-rpc-access (g2-get-build-version
 			    (text))
    ()
  (let ((software-version? (g2-get-build-version)))
    (if (text-string= software-version? #w"")
	(stack-error cached-top-of-stack
		     "G2-GET-BUILD-VERSION() failed.")
	software-version?)))

(define-system-rpc-access (g2-unix-time (float))
    ()
  (unix-time-lisp-side))

(define-system-rpc-access (g2-unix-time-at-start (float))
    ()
  (unix-time-at-start-lisp-side))

#+development
(define-system-rpc-access (g2-get-command-line-argument-from-launch (text))
    ((index integer))
  (let ((command-line-argument
	  (get-command-line-argument-from-launch-lisp-side index)))
    (if (text-string= command-line-argument #w"")
	(stack-error cached-top-of-stack
		      "GET-COMMAND-LINE-ARGUMENT-FROM-LAUNCH(~s) failed."
		      index)
	command-line-argument)))

(define-system-rpc-access (g2-kill-process (truth-value))
    ((process-id float))
  (kill-process-lisp-side process-id))

(define-system-rpc-access (g2-process-exists ())
    ((process-id integer))
  (let ((command-status
	  (process-exists-lisp-side process-id)))
    (case command-status
      (1 (copy-evaluation-truth-value
	   evaluation-true-value))
      (0 (copy-evaluation-truth-value
	   evaluation-false-value))
      (t
        (stack-error cached-top-of-stack
		     "PROCESS-EXISTS([~s]) failed."
		     process-id)))))

(define-system-rpc-access (g2-spawn-process-with-arguments
			    (float))
    ((command text))
  (let ((new-process-id
	  (spawn-process-with-arguments-lisp-side command)))
    (if (= (managed-float-value new-process-id) -1.0)
	(stack-error cached-top-of-stack
		     "SPAWN-PROCESS-WITH_ARGUMENTS(~a) failed."
		     command)
	new-process-id)))

(define-system-rpc-access (g2-spawn-process-to-run-command-line
			    (float))
    ((command text))
  (let ((new-process-id
	  (spawn-process-to-run-command-line-lisp-side command)))
    (if (= (managed-float-value new-process-id) -1.0)
	(stack-error cached-top-of-stack
		     "SPAWN-PROCESS-TO-RUN-COMMAND-LINE(~a) failed."
		     command)
	new-process-id)))

(define-system-rpc-access (g2-devices-on-machine ((class text-list)))
    ()
   (devices-on-machine-lisp-side))

(define-system-rpc-access (g2-disk-space-available-in-directory (integer))
    ((directory-string text))
    (multiple-value-bind (available-space error-message)
	(disk-space-available-in-directory-lisp-side directory-string)
      (if (=f available-space -1)
	  (stack-error cached-top-of-stack
		       "DISK-SPACE-AVAILABLE-IN-DIRECTORY(~a) failed.:~a"
		       directory-string error-message)
	  available-space)))
		     
(define-system-rpc-access (g2-change-default-directory ())
    ((new-default text))
  (multiple-value-bind (status error-message)
      (change-default-directory-lisp-side new-default)
    (unless (evaluation-truth-value-is-true-p status)
      (stack-error
	cached-top-of-stack
	"CHANGE-DEFAULT-DIRECTORY(~a) failed: ~a."
	new-default error-message))))

(define-system-rpc-access (g2-default-directory (text))
    ()
  (multiple-value-bind (current-default error-message)
      (default-directory-lisp-side)
    (if (text-string= current-default #w"")
	(stack-error
	  cached-top-of-stack
	  "DEFAULT-DIRECTORY() failed: ~A"
	  error-message)
	current-default)))

(define-system-rpc-access (g2-directory-exists (truth-value))
    ((directory-string text))
  (directory-exists-lisp-side directory-string))

(define-system-rpc-access (g2-latest-date-file-attributes-were-changed (float))
    ((file-string text))
  (multiple-value-bind (change-data error-message)
      (latest-date-file-attributes-were-changed-lisp-side file-string)
    (if (= (managed-float-value change-data) -1.0)
	(stack-error cached-top-of-stack
		     "LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED(~a): ~a"
		     file-string error-message)
	change-data)))

(define-system-rpc-access (g2-latest-date-file-was-accessed (float))
    ((file-string text))
  (multiple-value-bind (access-date error-message)
      (latest-date-file-was-accessed-lisp-side file-string)
    (if (= (managed-float-value access-date) -1.0)
	(stack-error cached-top-of-stack
		     "LATEST-DATE-FILE-WAS-ACCESSED(~a): ~a"
		     file-string error-message)
	access-date)))

(define-system-rpc-access (g2-latest-date-file-was-modified (float))
    ((file-string text))
  (multiple-value-bind (modification-date error-message)
      (latest-date-file-was-modified-lisp-side file-string)
    (if (= (managed-float-value modification-date) -1.0)
	(stack-error cached-top-of-stack
		     "LATEST-DATE-FILE-WAS-ACCESSED(~a): ~a"
		     file-string error-message)
	modification-date)))

(define-system-rpc-access (g2-length-of-file (integer))
    ((file-stream (class g2-stream)))
  (multiple-value-bind (file-length-or-signal error-message)
      (length-of-file-lisp-side file-stream)
    (if (=f file-length-or-signal -1)
	(stack-error cached-top-of-stack
		     "LENGTH-OF-FILE(~a) failed: ~a"
		     (name-of-file file-stream)
		     error-message)
	file-length-or-signal)))

(define-system-rpc-access (g2-file-names-are-identical (truth-value))
    ((filestring1 text)
     (filestring2 text))
  (file-names-are-identical-lisp-side filestring1 filestring2))

(define-system-rpc-access (g2-file-exists (truth-value))
    ((filestring text))
  (file-exists-lisp-side filestring))

(define-system-rpc-access (g2-type-of-file-system (symbol))
    ()
  (type-of-file-system-lisp-side))

(define-system-rpc-access (g2-partition-filestring
			    (text text text text text text))
    ;host,device,directory,base-name,extension,version
    ((filestring text))
  (partition-filestring-lisp-side filestring))

(define-system-rpc-access (g2-collect-into-filestring (text))
    ((host text)
     (device text)
     (directory text)
     (root-name text)
     (extension text)
     (version text))
  (collect-into-filestring-lisp-side
    host device directory root-name extension version))

(define-system-rpc-access (g2-file-version-string (text))
    ((filestring text))
  (file-version-string-lisp-side filestring))

(define-system-rpc-access (g2-file-extension-string (text))
    ((filestring text))
  (file-extension-string-lisp-side filestring))

(define-system-rpc-access (g2-file-base-name-string (text))
    ((filestring text))
  (file-base-name-string-lisp-side filestring))

(define-system-rpc-access (g2-file-directory-list-to-string (text))
    ((directory-list (class text-list)))
  (file-directory-list-to-string-lisp-side directory-list))

(define-system-rpc-access (g2-file-directory-string-to-list
			    ((class text-list)))
    ((filestring text))
  (file-directory-string-to-list-lisp-side filestring))

(define-system-rpc-access (g2-file-directory-string (text))
    ((filestring text))
  (file-directory-string-lisp-side filestring))

(define-system-rpc-access (g2-file-device-string (text))
    ((filestring text))
  (file-device-string-lisp-side filestring))

(define-system-rpc-access (g2-file-host-string (text))
    ((filestring text))
  (file-host-string-lisp-side filestring))

(define-system-rpc-access (g2-delete-file ())
    ((filestring text))
  (multiple-value-bind (status-of-operation error-message )
      (delete-file-lisp-side filestring)
    (unless (evaluation-truth-value-is-true-p status-of-operation)
      (stack-error cached-top-of-stack
		   (tformat-text-string
		     "DELETE-FILE(~s) failed: ~s"
		     filestring error-message)))))

(define-system-rpc-access (g2-rename-file ())
    ((old-filestring text)
     (new-filestring text))
  (multiple-value-bind (status-of-operation error-message)
      (rename-file-lisp-side old-filestring new-filestring)
    (unless (evaluation-truth-value-is-true-p status-of-operation)
      (stack-error cached-top-of-stack
		   "RENAME-FILE(~a,~a) failed: ~a"
		   old-filestring new-filestring
		   error-message))))

(define-system-rpc-access (g2-copy-file ())
    ((old-filestring text)
     (new-filestring text))
  (multiple-value-bind (status-of-operation error-message)
      (copy-file-lisp-side old-filestring new-filestring)
    (unless (evaluation-truth-value-is-true-p status-of-operation)
      (stack-error cached-top-of-stack
		   "COPY-FILE(~a,~a) failed: ~a"
		   old-filestring new-filestring
		   error-message))))


;;;; Sys-procs in proc-comp.lisp

(define-system-rpc-access (g2-enable-inlining ())
    ()
    (g2-enable-inlining))

(define-system-rpc-access (g2-disable-inlining ())
    ()
    (g2-disable-inlining))


;;;; SYS-PROCs in filters.lisp

(define-system-rpc-access (g2-item-is-editable (truth-value (or text (no-item))))
    ((item (class item)))
  (g2-item-is-editable item))

(define-system-rpc-access (g2-set-item-explicitly-editable ())
    ((item (class item)))
  (g2-set-item-explicitly-editable item))

(define-system-rpc-access (g2-set-item-and-all-its-subblocks-explicitly-editable ())
    ((item (class item)))
  (g2-set-item-and-all-its-subblocks-explicitly-editable item))

(define-system-rpc-access (g2-set-all-items-in-module-explicitly-editable ())
    ((item (class item)))
  (g2-set-all-items-in-module-explicitly-editable item))

;;;; SYS-PROCs in sets.lisp

(define-system-rpc-access (g2-modules-with-unsaved-changes (sequence))
    ()
  (g2-modules-with-unsaved-changes))

(define-system-rpc-access (g2-start-save-module (symbol text))
    ((pathname text)
     (file-progress-display truth-value)
     (window-or-not item-or-datum)
     (module symbol)
     (include-required-modules truth-value))
  (g2-save-module pathname
 		  file-progress-display 
 		  window-or-not 
 		  module 
 		  include-required-modules))

(define-system-rpc-access (g2-start-save-module-1 (symbol text))
    ((pathname text)
     (file-progress-display truth-value)
     (window-or-not item-or-datum)
     (module symbol)
     (include-required-modules truth-value)
     (using-clear-text truth-value)
     (emitting-c-code truth-value)
     (log-message-for-commit-after-saving (or (no-item) text)))
  (let ((options (allocate-evaluation-structure-inline
		  'file-progress-display (copy-evaluation-value file-progress-display)
		  'include-required-modules (copy-evaluation-value include-required-modules)
		  'using-clear-text (copy-evaluation-value using-clear-text)
		  'emitting-c-code (copy-evaluation-value emitting-c-code)
		  'log-message-for-commit-after-saving
		  (copy-if-evaluation-value log-message-for-commit-after-saving))))
    (multiple-value-bind (status-symbol error-text?)
	(g2-save-module-extended pathname module window-or-not options)
      (reclaim-evaluation-value options)
      (values status-symbol error-text?))))

(define-system-rpc-access (g2-start-save-kb (symbol text))
    ((pathname text)
     (type-of-file symbol)
     (file-progress-display truth-value)
     (window item-or-datum))
  (g2-save-kb pathname
 	      type-of-file
	      file-progress-display 
 	      window))

(define-system-rpc-access (g2-continue-save-kb (symbol text))
     ((file-progress-display truth-value))
  (g2-continue-save-kb file-progress-display))

(define-system-rpc-access (g2-finish-save-kb (symbol text))
    ((file-progress-display truth-value))
  (multiple-value-prog1
      (g2-finish-save-kb file-progress-display)
    (terminate-kb-save-or-backup-if-error-occurs)))

(defun-for-system-procedure g2-abort-save-in-progress ()
  (terminate-kb-save-or-backup-if-error-occurs))

(define-system-rpc-access (g2-abort-save-in-progress ())
    ()
  (g2-abort-save-in-progress))

(define-system-rpc-access (g2-delete-module ())
    ((module symbol)
     (also-delete-associated-workspaces truth-value))
  (g2-delete-module module
 		    also-delete-associated-workspaces))

(define-system-rpc-access (g2-create-module ())
    ((module symbol))
  (g2-create-module module))

(define-system-rpc-access (g2-load-kb-1 (truth-value))
    ((path-name text)
     (resolve-conflicts-automatically truth-value)
     (bring-formats-up-to-date truth-value)
     (update-before-loading truth-value))
  (let ((options (allocate-evaluation-structure-inline
		  'resolve-conflicts-automatically (copy-evaluation-value resolve-conflicts-automatically)
		  'bring-formats-up-to-date (copy-evaluation-value bring-formats-up-to-date)
		  'merge-kb (make-evaluation-boolean-value nil)
		  'install-system-tables (make-evaluation-boolean-value t)
		  'update-before-loading (copy-evaluation-value update-before-loading))))
    (prog1 (g2-load-kb-extended path-name options)
      (reclaim-evaluation-value options))))

(define-system-rpc-access (g2-load-kb (truth-value))
    ((path-name text)
     (resolve-conflicts-automatically truth-value)
     (bring-formats-up-to-date truth-value))
  (g2-load-kb path-name
 	      resolve-conflicts-automatically
 	      bring-formats-up-to-date))

(define-system-rpc-access (g2-merge-kb-1 (truth-value))
    ((path-name-string text)
     (resolve-conflicts-automatically truth-value)
     (bring-formats-up-to-date truth-value)
     (install-system-table truth-value)
     (update-before-loading truth-value))
  (let ((options (allocate-evaluation-structure-inline
		  'resolve-conflicts-automatically (copy-evaluation-value resolve-conflicts-automatically)
		  'bring-formats-up-to-date (copy-evaluation-value bring-formats-up-to-date)
		  'merge-kb (make-evaluation-boolean-value t)
		  'install-system-tables (copy-evaluation-value install-system-table)
		  'update-before-loading (copy-evaluation-value update-before-loading))))
    (prog1 (g2-merge-kb-extended path-name-string options)
      (reclaim-evaluation-value options))))

(define-system-rpc-access (g2-merge-kb (truth-value))
    ((path-name-string text)
     (resolve-conflicts-automatically truth-value)
     (bring-formats-up-to-date truth-value)
     (install-system-table truth-value))
  (g2-merge-kb path-name-string
	       resolve-conflicts-automatically
	       bring-formats-up-to-date
	       (make-evaluation-truth-value falsity)
	       install-system-table))

(define-system-rpc-access (g2-warmboot-kb (truth-value))
    ((path-name-string text)
     (run-from-snapshot-time-as-fast-as-possible truth-value))
  (g2-warmboot-kb path-name-string
		   run-from-snapshot-time-as-fast-as-possible))

(define-system-rpc-access (g2-load-runtime-data (truth-value)) ; GENSYMCID-1258 (BCDR)
    ((path-name-string text)
     (option structure))
  (g2-load-runtime-data path-name-string option))

(defun g2-source-code-control-operation (function pathname &optional log-message-for-commit?)
  (let* ((operation (case function
		      (g2-source-code-control-update 'scc-update)
		      (g2-source-code-control-edit 'scc-edit)
		      (g2-source-code-control-unedit 'scc-unedit)
		      (g2-source-code-control-revert 'scc-revert)
		      (g2-source-code-control-commit 'scc-commit)))
	 (error-message? (do-scc-command-1 operation pathname log-message-for-commit?)))
    (when error-message?
      (stack-error cached-top-of-stack "Error in ~A: ~A" function error-message?))
    nil))

(defun-for-system-procedure g2-source-code-control-update (pathname)
  (g2-source-code-control-operation 'g2-source-code-control-update pathname))

(defun-for-system-procedure g2-source-code-control-edit (pathname)
  (g2-source-code-control-operation 'g2-source-code-control-edit pathname))

(defun-for-system-procedure g2-source-code-control-unedit (pathname)
  (g2-source-code-control-operation 'g2-source-code-control-unedit pathname))

(defun-for-system-procedure g2-source-code-control-revert (pathname)
  (g2-source-code-control-operation 'g2-source-code-control-revert pathname))

(defun-for-system-procedure g2-source-code-control-commit (pathname log-message)
  (g2-source-code-control-operation 'g2-source-code-control-commit pathname log-message))

(define-system-rpc-access (g2-source-code-control-update ())
    ((path-name text))
  (g2-source-code-control-update path-name))

(define-system-rpc-access (g2-source-code-control-edit ())
    ((path-name text))
  (g2-source-code-control-edit path-name))

(define-system-rpc-access (g2-source-code-control-unedit ())
    ((path-name text))
  (g2-source-code-control-unedit path-name))

(define-system-rpc-access (g2-source-code-control-revert ())
    ((path-name text))
  (g2-source-code-control-revert path-name))

(define-system-rpc-access (g2-source-code-control-commit ())
    ((path-name text)
     (log-message text))
  (g2-source-code-control-commit path-name log-message))


(defun-for-system-procedure g2-post-message (sequence-of-values
					      duration-or-other-ev)
  (let ((message
	  (twith-output-to-text-string
	    (loop for x being each evaluation-sequence-element
		  of sequence-of-values
		  do
	      (write-block-or-evaluation-value x t))))
	(duration? (and (evaluation-integer-p duration-or-other-ev)
			(evaluation-integer-value duration-or-other-ev))))
    (reclaim-evaluation-value sequence-of-values)
    (reclaim-evaluation-value duration-or-other-ev)
    (post-on-message-board
      message nil duration? nil nil)))

(define-system-rpc-access (g2-post-message () ui-client-interface)
    ((sequence-of-values (sequence))
     (duration-or-false value))
  (g2-post-message sequence-of-values duration-or-false))

;;; non optimized!! Except it assumes ordered tree
;;; with non-distinct elements adjacent

(defun-simple eval-flatten-symbol-tree-for-user-modes (symbol-tree)
  (loop with flattened-tree = nil
	with old-leaf = nil
	for branch in symbol-tree
	do
    (cond ((symbolp branch)
	   (unless (eq branch old-leaf)
	     (setf old-leaf branch)
	     (eval-push branch flattened-tree)))
	  ((listp branch)
	   (let ((new-list (eval-flatten-symbol-tree-for-user-modes branch)))
	     (when new-list
	       (setf flattened-tree (nconc flattened-tree new-list)))))
	  (t
	   #+development
	   (cerror "go on" "Unexpected format of user-mode-directory")))
    finally
	  (return flattened-tree)))

(defun-for-system-procedure g2-get-known-user-modes ()
  (let ((directory-of-modes (get-directory-contents 'non-built-in-g2-user-mode)))
    (if (and (symbolp directory-of-modes) directory-of-modes)
	(allocate-evaluation-sequence (eval-list 'administrator directory-of-modes))
	(allocate-evaluation-sequence
	  (eval-flatten-symbol-tree-for-user-modes directory-of-modes)))))


(define-system-rpc-access (g2-get-known-user-modes ((sequence)))
    ()
  (g2-get-known-user-modes))

;;;; Beans on Workspaces


(def-class (g2-foreign-object object
			      (foundation-class g2-foreign-object)
			      not-solely-instantiable
			      not-user-instantiable
			      define-predicate)
  (active-stubs nil
		system do-not-clone do-not-save))

(def-virtual-attribute active-stubs
    ((class g2-foreign-object)
     (sequence)
     ())
  ;;subscription?
  :event-updates nil
  :initial  ((class) (declare (ignore class)) nil)
  :getter  ((g2-foreign-object)
	    (unless (active-stubs g2-foreign-object)
	      (setf (active-stubs g2-foreign-object)
		    (allocate-evaluation-sequence nil)))
	    (copy-evaluation-sequence (active-stubs g2-foreign-object)))
  :setter ((g2-foreign-object new-value)
	   (let ((old-value (active-stubs g2-foreign-object)))
	     (setf (active-stubs g2-foreign-object)
		   (copy-evaluation-sequence new-value))
	     (reclaim-if-evaluation-value old-value))))
	   

(def-class (g2-java-bean g2-foreign-object
			 (foundation-class g2-java-bean)
			 do-not-put-in-menus
			 define-predicate)
  (g2-java-bean-media-bin nil system save)
  (latent-listeners nil
		    system save do-not-clone))

(def-virtual-attribute latent-listeners
    ((class g2-java-bean)
     (or (no-item) (structure))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)))
  :getter ((g2-java-bean)
	   (and (latent-listeners g2-java-bean)
		(copy-evaluation-structure (latent-listeners g2-java-bean))))
  :setter ((g2-java-bean new-value)
	   (let ((old-value (latent-listeners g2-java-bean)))
	     (setf (latent-listeners g2-java-bean)
		   (and new-value
			(copy-evaluation-structure new-value)))
	     (when old-value
	       (reclaim-evaluation-structure old-value)))))


(def-slot-value-reclaimer g2-java-bean-media-bin (media-bin)
  (when media-bin
    (delete-frame media-bin)))


(def-virtual-attribute internal-media-bin
    ((class g2-java-bean)
     (or (no-item) (class media-bin))
     ())
  ;;subscription?
  :event-updates nil
  :initial  ((class) (declare (ignore class)) nil)
  :getter  ((g2-java-bean)
	    (g2-java-bean-media-bin g2-java-bean)))


(def-class (g2-foreign-savable item
			       (foundation-class item)
			       do-not-put-in-menus
			       not-solely-instantiable
			       not-user-instantiable)
  )


(def-class (g2-foreign-serializable g2-foreign-savable
				    (foundation-class item)
				    do-not-put-in-menus
				    not-solely-instantiable
				    not-user-instantiable)
  )



(def-class-method initialize (g2-java-bean)
  (funcall-superior-method g2-java-bean)
  (when (frame-of-class-p g2-java-bean 'g2-foreign-serializable)
    (let ((media-bin (g2-java-bean-media-bin g2-java-bean)))
      (unless media-bin
	(make-media-bin-for-g2-java-bean g2-java-bean)))))

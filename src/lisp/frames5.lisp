; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FRAMES5: Frames for Knowledge Bases

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.







;;;; Forward References




(declare-forward-references-to-module
  comp-utils
  (current-computation-component-particulars variable)
  (*current-computation-frame* variable))

(declare-forward-references-to-module
  kb-load1
  (kb-flags variable))

(declare-forward-references-to-module
  kb-load2
  (blocks-with-relation-instances-from-kb-read variable))

(declare-forward-references-to-module
  draw
  remove-as-subblock-if-necessary)

(declare-forward-references-to-module
  kb-save2
  (releasing-kb? variable))

(declare-forward-references-to-module
  kb-save3
  note-deletion-of-block-2)

(declare-forward-references-to-module
  tables
  update-frame-name-references
  get-cached-debugging-name
  (pseudo-class-slot-description variable)
  update-all-representations-of-slot
  do-deferred-updates-to-representations-in-tables
  get-slot-component-value
  set-slot-component-value
  get-slot-component-putter-if-any
  detach-table-from-frames-it-represents)

(declare-forward-references-to-module
  panes
  delete-image-planes-workspace-is-on
  update-images-of-block)

(declare-forward-references-to-module
  install
  analyze-compiled-items-for-consistency
  put-attribute-description-value)

(declare-forward-references-to-module
  activate
  superior-frame)

(declare-forward-references-to-module
  definitions
  add-or-delete-class-or-name-for-frame
  (classes-and-directory-categories-for-classes variable))

(declare-forward-references-to-module
  kb-merge
  get-module-block-is-in
  add-or-delete-as-workspace-belonging-to-module
  update-module-related-frame-notes-for-all-workspaces)

(declare-forward-references-to-module
  connect1
  frame-serial-number-for-connection-function)

(declare-forward-references-to-module
  relations
  remove-transient-relation-instances
  reclaim-relation-instances)

(declare-forward-references-to-module
  lists
  remove-element-from-all-g2-lists)

(declare-forward-references-to-module
  sequences2
  maintain-authorized-user)

(declare-forward-references-to-module
  simulate5
  install-item-in-model-if-models-used)

(declare-forward-references-to-module
  controls
  embedded-frame-parent-status)

(declare-forward-references-to-module
  moves
  remove-as-block-being-dragged)

(declare-forward-references-to-module
  g2ds
  update-g2ds-variable-to-interface-connections)

(declare-forward-references-to-module
  places
  write-status-of-component-particulars
  denote-component-of-block)

(declare-forward-references-to-module
  g2-gsi
  handle-update-to-located-sensor-attribute)

(declare-forward-references-to-module
  filters
  get-property-value-in-object-configuration)

(declare-forward-reference reading-kb-p variable)	; in KB-*
;; in view-g2
(declare-forward-reference inform-ui-client-interfaces-of-top-level-workspace-assignment-change function)

(declare-forward-references-to-module
  view-def
  delete-representation
  send-representation-deletion-notification
  update-subscriptions-from-virtual-attribute-change)

;(declare-forward-references-to-module
;  events-g2
;  update-tw-method-declaration-for-name-putter)

(declare-forward-references-to-module stack-acts
  conclude-into-attribute-component)

(declare-forward-reference convert-text-string-to-text function)

(declare-forward-reference note-modification-of-module-for-clear-text function)

(declare-forward-reference suppress-use-of-stack-of-slot-value-changes-p variable)

(declare-forward-reference note-permanent-change function)

(declare-forward-reference note-permanent-change-to-component function)

(declare-forward-reference note-deletion-of-block-for-selection function)

(declare-forward-reference remove-block-from-native-views function)

#+mtg2
(declare-forward-reference check-faction function)


;;;; Frame Representations



;;; A `representation frame' of a frame f is a frame r that represents one or
;;; more slots of f.  (At present, representation frames are always tables.)

;;; Each class of representation frame must have an
;;; update-representation-of-slot-value method that takes the following 5
;;; arguments: the representation frame, erase-case?  (non-nil to erase), the
;;; slot name, the new value for the slot, and the old value or nil (nil meaning
;;; that the old value should be ignored).  In the erase case, the old
;;; representation should simply be erased, maybe only partially if part of the
;;; old representation can be used in the new one.  In the non-erase case, the
;;; new representation should be drawn, at least the part not in common with the
;;; old one.  When the new representation is part of a larger structure, e.g. a
;;; table, that larger structure may need to be reformatted.

;; This sounds nice but there is no occcurrence of any
;; update-representation-of-slot-value method in G2. -pga, 3/25/96

;;; A representation frame is not saved unless it is a subblock of a KB workspace.

;; Not saving representation frames which are not on KB workspaces only started
;; today.  Before that, such frames were saved and then deleted upon loading in
;; by the post-loading function clean-up-orphan-frame-representations.
;; (MHD/ML 7/26/90)



;;; Add-frame-representation-if-necessary adds representation-frame (e.g., an
;;; attribute table), which at least in part represents one or more slots of
;;; frame, to the frame representations of frame, unless it is already so
;;; recorded there.

(defun add-frame-representation-if-necessary (representation-frame frame)
  (if (not (memq representation-frame (frame-representations frame)))
      (progn
	(setf (frame-representations frame)
	      (slot-value-cons representation-frame
			       (frame-representations frame))))))



;;; Remove-from-frame-representations-if-present removes representation-frame (a
;;; table, graph, dial, etc.), which at least in part represents one or more
;;; slots of frame, from the frame representations of frame, if it is so
;;; recorded there.  It does nothing more than this.

(defun remove-from-frame-representations-if-present (representation-frame frame)
  (setf (frame-representations frame)
	(delete-slot-value-element		; not necessarily there
	  representation-frame (frame-representations frame))))



;;; The slot reclaimer for frame-representations does the following, in order:
;;;
;;;   (1) sets the slot to nil
;;;   (2) for each representation frame r in frames-representations,
;;;         if r is being deleted, it does nothing; otherwise
;;;         if r is an explanation table, it calls
;;;           (detach-table-from-frames-it-represents r); otherwise
;;;         it calls (delete-frame r)
;;;   (3) reclaims the top level conses in frames-representations as
;;;         slot value conses

(def-slot-value-reclaimer frame-representations (frame-representations frame)
  (setf (frame-representations frame) nil)
  (loop for representation-frame in frame-representations
	unless (frame-being-deleted-p representation-frame)
	  do (frame-class-case representation-frame
	       (explanation-table   ; review new logic w/LH! (MHD 1/24/90)
		 (detach-table-from-frames-it-represents representation-frame))
	       (representation
		 (let ((serial-number (copy-frame-serial-number (frame-serial-number representation-frame))))
		   ;; GENSYMCID-1406: Item deleted event
		   ;; ignore send deletion notification while frame is being deleted
		   (when (not (frame-being-deleted-p frame))
		     (send-representation-deletion-notification representation-frame))
		   ;; if the above code has noticed that the socket
		   ;; has closed in the meantime, then it will
		   ;; have already called delete-representation.
		   (if (not (frame-has-been-reprocessed-p representation-frame
							  serial-number))
		       (delete-representation representation-frame)
		       #+development
		       (format t "avoided multiple reclaim of frame-representation~%"))
		   (reclaim-frame-serial-number serial-number)))
	       (t
		 (delete-frame representation-frame))))
  (reclaim-slot-value-list frame-representations))

;; At present, this deletes a representation frame if it represents one or more
;; slots in a frame being deleted (unless it is an explanation table (MHD), even
;; if it also represents slots in other frames.  Consider changing this behavior.

;; Documentation supplied and new logic added for explanation-table case.  Review
;; later.  Also see and review explanation tables in TABLES. (MHD 1/24/90)






;;;; Namelike Slots


;;; A `namelike slot' is a slot in a frame that in some sense names a frame.
;;; Usually, this is just name-or-names-for-frame.  However, in some cases
;;; it is necessary for this to be some other slot defined for a class.  For
;;; example, the slot giving the name of a method for procedures.
;;;
;;; When a namelike slot in a given frame is updated, it triggers the function
;;; update-frame-name-references, on that frame and the appropriate subframes,
;;; to all appropriate levels.
;;;
;;; In the case of the name-or-names-for-frame slot (only), this updates the
;;; name-box and top-bar-of-image-plane if appropriate.
;;;
;;; For all slots, it updates table representations of the related class-header
;;; slot on tables for all subframes that might include the namelike slot's
;;; former value.

(def-global-property-name namelike-slot-p)

(defmacro declare-namelike-slot (pretty-slot-name)
  `(progn (setf (namelike-slot-p ',pretty-slot-name) t)
	  ',pretty-slot-name))

;; Note: use of namelike-slot-p global-property-name is obsolete.  The macro
;; namelike-slot-p will go away, as will declare-namelike-slot-p.  The users of
;; this facility will be converted to use slot-description-for-namelike-slot-p,
;; which will be a slot of a slot description, as the predicate for the
;; namelike-slot slot feature.  This documentation will be shifted to
;; global-slot-features, q.v.  Flush this soon!  (MHD 5/14/00)




;;;; Updating Representations


;;; `Stack-of-slot-value-changes' is dynamically bound by change-slot-value and
;;; utilized to allow the reformatting of a table to be deferred by out of the
;;; recursive decent of change-slot-value, and into the epilog of change slot
;;; value.
;;;
;;; This stack has a surprising format.  The front of the list consists of cons
;;; cells managed by change-slot-value.  They record what slots, or components
;;; thereof, it is currently working on.  The end of the list consists of a list
;;; of tables, nconc'd onto the end by update-text-cell when it decides to defer
;;; reformatting a given table.  One more special thing: when it defers
;;; reformatting, it first erases them completely.  Processed them later then
;;; means (re)formatting them from scratch and then drawing them.
;;;
;;; 
;;; Thus, the variable is dynamically bound to a list of the form
;;;
;;;     ( { slot-representation }+ {table}* )
;;;
;;; where slot-representation is either
;;;
;;;     (frame . slot-name)
;;;
;;; or
;;;
;;;     (frame slot-name
;;;      defining-class? slot-component-name
;;;      . slot-component-indicator?)
;;;
;;; (This representation is optimized for the very common case of a simple frame
;;; and slot name pair, and is less so when the other components are present.) 
;;;
;;; When change-slot-value sees that its looking at the end of the list, i.e.,
;;; just a list of tables, it runs through the whole list, reformats each table
;;; completely, and reclaims the list.

;;; The general rule here is that cells in tables are redrawn immediately unless
;;; they would force the reformatting of the table.  In that case the entire
;;; table's reformatting is deferred until the outermost call to change-slot-
;;; value finishes executing.
;;; 
;;;
;;; Some functions in tables care about stack-of-slot-value-changes, and may
;;; even manipulate it:
;;;
;;; Highlight-or-unhighlight-attribute: ...

;;; Update-attribute-table-rows: when a table that is an element of the list is
;;; deleted in the course of updating its rows (by update-attribute-table-rows),
;;; the table element is removed from this list.
;;;
;;; This means that the tables at the end of list may be deleted.  That's ok.  Note
;;; that the head of the list is never altered, and that where the tail contains
;;; tables, the head always contains slot representations.

;; - ben (12/19/90), and Mark (2/5/94)

(def-system-variable stack-of-slot-value-changes frames5 nil nil nil reclaim-slot-value-tree-function )	; slot value conses

;;; `Just-update-representations-of-slot-value' contains a unique value, which when
;;; passed to change-slot-value as the new value for a slot modifies the behavior of
;;; that routine to just update the representations.  The routine
;;; update-representations-of-slot-value is a better interface to this facility.

;; - ben (12/19/90)

(defvar just-update-representations-of-slot-value
	(list 'just-update-representations-of-slot-value))


;;; `Suppress-updating-of-slot-value-representations?' is a special variable
;;; bound by callers to change-slot-value to suppress the updating of
;;; representations for this slot.  The responsiblity for seeing that such
;;; slots are finally updated falls to whoever bound suppress-updating-of-
;;; slot-value-representations?.

;; ben (12/17/90)

(defvar suppress-updating-of-slot-value-representations? nil)


(defconser stack-change)

;;; `With-updates-to-representations' ... After body, this updates
;;; representations of the slot, and updates any table or name box
;;; representations there may be for the slot.  Only one value may be returned
;;; from body.  It is an error to unwind out of this form.

(defmacro with-updates-to-representations
    ((frame slot-description &optional
	    slot-component-name? slot-component-indicator?)
     &body body)
  (avoiding-variable-capture
      (frame slot-description slot-component-name? slot-component-indicator?)
    `(let* ((stack-of-slot-value-changes
	      (stack-change-cons-macro
		(if ,slot-component-name?
		    (nconc
		      (stack-change-list ,frame ,slot-description)
		      (stack-change-cons
			,slot-component-name?
			,slot-component-indicator?))
		    (stack-change-cons-macro ,frame ,slot-description))
		stack-of-slot-value-changes)))
       (prog1 (progn . ,body)
	 (unless (or suppress-updating-of-slot-value-representations?
		     (slot-representation-changing-p
		       ,frame ,slot-description
		       ,slot-component-name? ,slot-component-indicator?))
	   (update-all-representations-of-slot
	     ,frame ,slot-description
	     ,slot-component-name? ,slot-component-indicator?))
	 (when (slot-description-for-namelike-slot-p ,slot-description)
	   (update-frame-name-references ,frame)) ; good or evil??!
	 (reclaim-stack-change-tree
	   (stack-change-pop stack-of-slot-value-changes))

	 (do-deferred-updates-to-representations-in-tables-if-appropriate)))))




;;; `With-updates-to-representations-supressed' establishes a dynamic extent
;;; within which changes to the given slot do not update their representations.
;;; Upon exiting this extent those representations are updated.  This can be
;;; used to supress flashing during a series of changes to a slot (i.e.  frame
;;; notes).

;;; This form one value and only one value.  It is an error to unwind out of
;;; this form.

(defmacro with-updates-to-representations-supressed
    ((frame slot-name &optional defining-class?) &body body)
  (avoiding-variable-capture (frame slot-name defining-class?)
    `(with-updates-to-representations
	 (,frame (get-slot-description-of-frame
		   ,slot-name ,frame ,defining-class?))
       . ,body)))



;;; `Slot-representation-changing-p' called within change-slot-value after frame
;;; and slot-name have been pushed on the top of the change stack,
;;; stack-of-slot-value-changes, says whether the pair are also present further
;;; down.  If this is true, we can avoid updating their representation for now,
;;; since the changes further below will bring about their updates.
;;;
;;; Let's go over what happens:
;;;
;;;    (1) You enter change-slot-value and bind stack-of-slot-value-changes
;;;    to ((frame . slot-description) . stack-of-slot-value-changes) -- let's assume
;;;    that stack-of-slot-value-changes does not contain (frame . slot-name)
;;;    before we entered it.
;;;
;;;    (2) you call the slot putter;
;;;
;;;    (3) the slot putter calls some know-it-all function that calls
;;;    change slot value on (frame . slot-name) again
;;;
;;;    (4) you bind stack-of-slot-value-changes to
;;;
;;;        ((frame . slot-description) (frame . slot-description)
;;;         . stack-of-slot-value-changes)
;;;
;;;    (5) You call this function, it sees that (frame . slot-name) is in the
;;;    cdr of stack-of-slot-value-changes, telling you not to update its
;;;    representation, because you're not the last guy that's going to do
;;;    it;
;;;
;;;    (6) You leave the recursive call to change slot value, and the putter,
;;;    and stack-of-slot-value-changes gets wound back to
;;;    
;;;       ((frame . slot-description) . stack-of-slot-value-changes)
;;;
;;;    (7) You've just called the putter, so now you call this function, and
;;;    it returns nil; so you know that you're the last guy to change this
;;;    this slot, which means you should update the representations, which
;;;    you should now do.
;;;
;;; That's it.  

(defun-substitution-macro slot-representation-changing-p
    (frame slot-description
	   slot-component-name? slot-component-indicator?)
  (if (cdr-of-cons stack-of-slot-value-changes)	; opt.
      (loop for frame-and-slot-or-atom in (cdr-of-cons stack-of-slot-value-changes)
	    until (atom frame-and-slot-or-atom)	; hit a table
	    thereis
	      (and (or (eq slot-description
			   (cdr-of-cons frame-and-slot-or-atom))
		       (if (consp (cdr-of-cons frame-and-slot-or-atom))
			   (and (eq slot-description
				    (second frame-and-slot-or-atom))
				(eq slot-component-name?
				    (third frame-and-slot-or-atom))
				(eq slot-component-indicator?
				    (cdddr frame-and-slot-or-atom)))))
		   (eq frame (car-of-cons frame-and-slot-or-atom))))))

;; This wants to be pretty efficient.

;; Does this need to take slot-component-name? and slot-component-indicator? args?!




;;; `Do-deferred-updates-to-representations-in-tables-if-appropriate', called
;;; within a with-updates-to-representations context, checks if
;;; stack-of-slot-value-changes consists of just tables to reformat, in which
;;; case it's appropriate to reformat them all.
;;;
;;; This actually just checks if the stack is in a state where it's time to
;;; reformat.  If so, the reformatting is handled by a subfunction in the module
;;; TABLES, do-deferred-updates-to-representations-in-tables.  That handles
;;; reformatting, and, in addition, reclaims the entire list
;;; stack-of-slot-value-changes.
;;;
;;; This operates in cooperation with the function
;;; update-representations-in-tables.  (Both functions are in TABLES).  They're
;;; both coordinated by with-updates-to-representations, above.

(defun-substitution-macro do-deferred-updates-to-representations-in-tables-if-appropriate
    ()
  (when (and stack-of-slot-value-changes
	     (atom (car-of-cons stack-of-slot-value-changes))
	     (not suppress-use-of-stack-of-slot-value-changes-p))
    (do-deferred-updates-to-representations-in-tables)))




;;; The macro `update-representations-of-slot-value-macro' performs an update
;;; without the check of whether this frame has frame representations.

(defmacro update-representations-of-slot-value-macro
    (frame slot-name defining-class?)
  (avoiding-variable-capture (frame slot-name defining-class?)
    `(change-slot-description-value
       ,frame
       (or (get-slot-description-of-frame ,slot-name ,frame ,defining-class?)
	   ;; Added to access the slot-description during class inheritance
	   ;; changes when slot-description hash-table information is
	   ;; incomplete.  (ghw 3/31/97)
	   (get-slot-description
	     ,slot-name (slot-descriptions (class-description (class ,frame)))
	     ,defining-class?))
       just-update-representations-of-slot-value)))

;; These definition belong naturally in the "Changing Slot Values and/or Updating
;; their Representations" section, but they get used earlier in the file!
;; BAH, please review!  (MHD 6/3/91)




;;; The macro `Activatable-subworkspace-p' checks a property of objects that
;;; makes it possible to use the activate and deactivate actions to activate and
;;; deactivate the subworkspaces of the object.

(defmacro activatable-subworkspace-p (object)
  `(get-property-value-in-object-configuration
     ,object 'activatable-subworkspace nil))








;;;; Frame Status and Frame Notes



;;; The frame-status-and-notes slot of a frame specifies the `installation
;;; status' of the frame and may include any number of notes regarding the
;;; status, the installation, or the actual use of the frame.  Formally, a
;;; frame-status-and-notes value is either the particular frame status nil or a
;;; frame note list of the form (frame-status . frame-note-plist).  See below
;;; for a full description of a frame status and frame notes.



;;; A `frame status' must be one of the following.
;;;
;;;    nil means the frame is `ok' and, if installable, either has just 
;;;    been created or has been installed
;;;
;;;    INCOMPLETE means the frame is incompletely filled in and is not installed
;;;
;;;    BAD means the frame is unusable and is not installed

;;; The status of a frame should not depend on whether or not names it refers to
;;; are defined.

;;; `Frame notes' may be error messages, or merely informative notes.  A frame
;;; note consists of a `type of note' (a symbol) and `particulars'.  Frame notes
;;; are organized as a `frame note plist', where types of notes serve as
;;; property names and particulars as values.  A frame note plist consists of
;;; unshared frame note conses.  Also, any tree used as the particulars of a
;;; frame note consists of unshared frame note conses and no atoms that need
;;; reclaiming.

;;; For each type of frame note, a `frame note writer' must be defined; see
;;; below.

;;; Clarification of the frame status and frame notes on saved kbs. (ML 21 Dec.
;;; 87) Status and frame-notes will now be saved in kbs.  It is expected that
;;; most frames will be OK and have no notes, which is represented by NIL.
;;; Either a slot value compiler or a slot putter may introduce or remove frame
;;; notes or change the status.  In some cases, slot-putters will introduce or
;;; remove slots on other frames, as, for example the name reference system.
;;; Since order dependency cannot be relied on, care must be taken with frame
;;; status and notes in any case where more than one slot is responsible.  For
;;; example, a rule is made bad by the slot value compiler for its
;;; box-translation-and-text slot type, which is rule.  Nothing but this same
;;; compiler should alter this bad status; therefore, frame updating from other
;;; sources must be careful of this.



(def-slot-value-reclaimer frame-status-and-notes (frame-status-and-notes frame)
  (setf (frame-status-and-notes frame) nil)	; necessary -- see note
  (reclaim-slot-value frame-status-and-notes))

;; Note: the setf'ing of the frame-status-and-notes is "necessary" as a royal
;; kludge that makes referals/changes to this slot before it's been initialized
;; work out -- fix all slot putters that are guilty of this! (MHD 7/20/94)


;;; Frame-status gets the frame status of frame.

(defmacro frame-status (frame)
  `(car (frame-status-and-notes ,frame)))


#+unused
(defun-simple frame-status-function (frame)
  (car (frame-status-and-notes frame)))




;;; `Frame-ok-p' is true if the frame status of frame is nil, which means "OK".

(defmacro frame-ok-p (frame)
  `(null (car (frame-status-and-notes ,frame))))

;;; `Frame-not-bad-p' is used as an argument to
;;; get-instance-with-name-that-satisfies-predicate-if-any in file FUNCTIONS.

(defun frame-not-bad-p (frame)
  (not (eq (car (frame-status-and-notes frame)) 'bad)))

(defun frame-incomplete-p (frame)
  (eq (frame-status frame) 'incomplete))

(def-virtual-attribute item-status
    ((class block) (member ok incomplete bad) ())
  :event-updates :within-putter
  :initial ((class)
	    (declare (ignore class))
	    'ok)
  :getter ((block) (or (frame-status block) 'ok)))

(def-virtual-attribute item-active
    ((class block) truth-value ())
  :event-updates :within-putter
  :initial ((class)
	    (declare (ignore class))
	    (make-evaluation-truth-value falsity))
  :getter ((block) (if (active-p block)
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity))))

(def-virtual-attribute containing-module
    ((class block) symbol ())
  :event-updates nil
  :initial ((class)
	    (declare (ignore class))
	    nil)
  :getter ((block)
	   (make-evaluation-symbol (get-module-block-is-in block))))




;;; `Frame-has-note-p' is true if frame has type-of-note on its frame note plist.

;;; Note that (getf (cdr (frame-status-and-notes frame)) type-of-note) provides
;;; an ambiguous result when it returns nil: it could mean that it does not have
;;; type-of-note, or that it has type-of-note, but that its particulars happen
;;; to be nil.

(defun-simple frame-has-note-p (frame type-of-note)
  (if (frame-status-and-notes frame)
      (let ((frame-note-plist (cdr (frame-status-and-notes frame))))
	(if frame-note-plist
	    (loop for type-of-note-1 in frame-note-plist by #'cddr
		  thereis (eq type-of-note-1 type-of-note))))))





;;; The macro `frame-has-frame-notes-p' takes a frame (ok, actually a block) and
;;; returns whether or not it has any frame notes of any kind.

(defmacro frame-has-frame-notes-p (frame)
  `(cdr (frame-status-and-notes ,frame)))


;;; `frame-status-union' is a binary combinator for frame statuses
;;; for use when setting a status of the frame of a class that depends
;;; on the status of multiple slots.

(defun-simple frame-status-union (status-1 status-2)
  (cond ((eq status-1 'bad) 'bad)
	((eq status-2 'bad) 'bad)
	((eq status-1 'incomplete) 'incomplete)
	((eq status-2 'incomplete) 'incomplete)
	(t nil)))


;;; `Update-frame-status' updates the frame status of frame to be
;;; new-frame-status.  The frame notes, if any, are left unchanged.  If
;;; do-not-update-representations? is non-nil, any representions of the frame
;;; status and notes for frame will not be updated; this is an appropriate
;;; option to exercise if another update of the frame-status-and-notes slot will
;;; happen immediately or if frame is being deleted.  Frame is returned.

;;; Update-frame-status is also part of the activation logic which is
;;; extensively documented in file ACTIVATE. Specifically, if a frame becomes
;;; other than ok, it must be deactivated, and all inferiors must be deactivated
;;; and marked ancestor-not-activatable. Upon becoming ok, a frame may be
;;; activated, and in any case, the status of ancestor-not-activatable of its
;;; subordinates may need updating.



(defun update-frame-status
    (frame new-frame-status do-not-update-representations?)
  (let* ((old-frame-status-and-notes
	   (frame-status-and-notes frame))
	 (old-frame-status
	   (car old-frame-status-and-notes))
	 (reclaim-old-frame-status-and-notes? nil))
    (if (null old-frame-status-and-notes)
        (unless (null new-frame-status)
	  (setf (frame-status-and-notes frame)
		(slot-value-cons new-frame-status nil)))
        (if (and (null new-frame-status)
                 (null (cdr old-frame-status-and-notes)))
	    (progn
	      (setf (frame-status-and-notes frame) nil)
	      (setq reclaim-old-frame-status-and-notes? t))
	    (setf (frame-status-and-notes frame) ; needed at least if noting 
		  (progn		         ;    changes (MHD 7/18/94)
		    (setf (car old-frame-status-and-notes) new-frame-status)
		    old-frame-status-and-notes))))

    ;; Updates to the activation status are made after the frame status has been
    ;; modified, because these will look at the new frame status.

    (if (eq new-frame-status 'bad)
	(funcall-method 'deactivate-and-propagate frame
			(ancestor-not-activatable-p frame)))

    (when (and old-frame-status (null new-frame-status))
      ;; The frame was previously not ok, but is now becoming ok.
      (gensym-assert (not (frame-being-deleted-p frame)))
      (if (let ((superior-frame (superior-frame frame)))
	    (if superior-frame
		(and (active-p superior-frame)
		     (or (not (activatable-subworkspace-p frame))
			 (active-p frame))) ; See note below.  - cpm, 3/24/95
		(and (block-p frame)
		     (transient-p frame))))
	  (funcall-method 'activate-if-possible-and-propagate frame)
	  (funcall-method 'deactivate-and-propagate frame
			  (ancestor-not-activatable-p frame))))
    (when reclaim-old-frame-status-and-notes?
      (reclaim-slot-value old-frame-status-and-notes)))
  (unless do-not-update-representations?
    (update-representations-of-slot-value frame 'frame-status-and-notes))

  (update-subscriptions-from-virtual-attribute-change
    frame (virtual-attribute 'item-status) nil)

  (check-for-frame-being-embedded frame)	; new. (MHD 7/2/91)
  
  frame)

;; Added an active-p test in the case where the frame has an activatable-
;; subworkspace.  (See my comment above.)  This keeps the (already active) frame
;; from being deactivated, in the ELSE case!  Also, note that in this case,
;; because the item is already active, the activation is not further propagated
;; to inferior frames.  This is correct because the items inferior to the
;; activatable-subworkspace may not have been activated.  - cpm, 3/24/95


(defun-void update-representations-of-frame-notes (frame)
  (update-representations-of-slot-value frame 'frame-status-and-notes)
  (update-subscriptions-from-virtual-attribute-change
    frame (virtual-attribute 'item-notes) nil))



;;; `Get-particulars-of-frame-note-if-any' looks for a frame note on frame of
;;; type type-of-note, and if there is such a note, returns its particulars.

(def-substitution-macro get-particulars-of-frame-note-if-any
			(type-of-note frame)
  (if current-computation-component-particulars
      (get-particulars-of-frame-note-from-component-particulars
	type-of-note frame current-computation-component-particulars)
      (getfq (cdr (frame-status-and-notes frame)) type-of-note)))

(defun get-particulars-of-frame-note-from-component-particulars
       (type-of-note frame component-particulars)
  (getfq (cdr (second (get-entry-for-component-particulars
			component-particulars frame)))
	 type-of-note))

(defun get-particulars-of-frame-notes-for-component-particulars (frame)
  (getfq (cdr (frame-status-and-notes frame))
	 'frame-notes-for-component-particulars))


;;; The function `frame-note-of-type-for-component-particular-p' checks if the
;;; frame note of the given type is found for any component particulars for the
;;; given frame.

(defun frame-note-of-type-for-component-particular-p (type-of-note frame)
  (loop for particulars-of-frame-notes in
	    (get-particulars-of-frame-notes-for-component-particulars frame)
	for component-particular = (first particulars-of-frame-notes)
	thereis
	  (get-particulars-of-frame-note-from-component-particulars
	    type-of-note frame component-particular)))



;;; An `embedded frame' is a frame having a parent-frame, and having a
;;; parent-attribute-name which is in the list-of-embedding-slots. Whenever the
;;; status of the frame notes of an embedded frame is modified, the
;;; frame-status-and-notes of the parent-frame must be checked and updated if
;;; necessary so that the note embedded-rule-has-frame-notes is present or
;;; absent accordingly. Representations of The frame-notes of the superior-frame
;;; must also be updated. This is done by add-frame-note and
;;; delete-frame-note-if-any.

;;; `List-of-embedding-slots' is a list of lists of the form
;;;
;;;    (parent-slot-name parent-slot-name-defining-class?
;;;     embedded-frame-slot-name? embedded-frame-defining-class?)  
;;;
;;; The slot names are generally not the same.

(defparameter list-of-embedding-slots
  '((translation-and-text-of-embedded-rule nil embedded-rule? nil) 
    (action-for-user-menu-choice? nil embedded-rule-in-user-menu-choice? nil)))

;; Note that this is only used at present for system-defined classes, for which
;; we're not specifying defining classes at present (for 3.0). (MHD 2/22/94)

;;; `Update-frame-status-of-parent-of-embedded-frame' is called by
;;; add-frame-note and delete-frame-note-if-any whenever the frame being
;;; operated on is embedded. The second argument is t if the embedded frame has
;;; frame notes after the modification. (It does not reflect the particular
;;; frame note alone.)

(defun update-frame-status-of-parent-of-embedded-frame
       (parent-frame embedded-frame-has-notes
	name-of-slot-holding-embedded-frame
	defining-class-for-slot?)
  (declare (ignore defining-class-for-slot?)) ; FIX TO USE!! (MHD 2/22/94)

  ;; New: (MHD 7/2/91)
  (let* ((embedded-frame
	   (get-slot-value
	     parent-frame name-of-slot-holding-embedded-frame))
	 (new-parent-status
	   (embedded-frame-parent-status parent-frame embedded-frame)))
	
    (update-frame-status
      parent-frame
      new-parent-status
      nil))
  
  (cond
    ;; Embedded frame had no notes, and now does.
    ((and embedded-frame-has-notes
	  (null (get-particulars-of-frame-note-if-any
		  'embedded-rule-has-frame-notes parent-frame)))
     (add-frame-note 'embedded-rule-has-frame-notes parent-frame
		     name-of-slot-holding-embedded-frame
		     nil nil))
    ;; Embedded frame had notes and still does.
    (embedded-frame-has-notes
     (update-representations-of-frame-notes parent-frame))
    ;; Embedded frame had notes and no longer does.
    ((get-particulars-of-frame-note-if-any
       'embedded-rule-has-frame-notes parent-frame)
     (delete-frame-note-if-any 'embedded-rule-has-frame-notes parent-frame))))




;;; `Check-for-frame-being-embedded' ... Note that this need not be called
;;; if the parent-frame of frame is nil.

(defun check-for-frame-being-embedded (frame)
  (when (block-p frame)
    (multiple-value-bind
	(parent-frame? parent-slot-name? parent-slot-name-defining-class?)
	(get-kb-parent-information frame)
      (when parent-frame?
	(loop for (embedding-slot-name embedding-slot-name-defining-class?
		   parent-embedding-slot-name parent-embedding-defining-class?)
		  in list-of-embedding-slots
	      when (and (eq embedding-slot-name parent-slot-name?)
			(eq embedding-slot-name-defining-class?
			    parent-slot-name-defining-class?))
			
		return
		  (update-frame-status-of-parent-of-embedded-frame
		    parent-frame?
		    (cdr (frame-status-and-notes frame))
		    parent-embedding-slot-name
		    parent-embedding-defining-class?))))))

;; This facility, around list-of-embedding-slots, is probably obsolete.  It has
;; only been used, so far, with system-defined slots (on action buttons and user
;; menu choices).  It has not been partially converted to deal with the need for
;; class qualifiers on slot names, but they're not yet needed for system
;; defined slots.  (MHD 2/19/94)

;; Consider making this a def-substitution-macro; was one until today.  Note
;; that it is called from earlier in this file. (MHD 7/3/91)



;;; The frame note writer for embedded-rule-has-frame-notes type notes
;;; writes the frame notes of the embedded frame into the frame notes of the
;;; superior frame. The method by which it maintains consecutive numbering
;;; is discussed in frames5. Note that it will write inappropriate stuff if
;;; there are no frame notes for the inferior-frame.

;; Code for frame note writer for embedded-rule-has-frame-notes
;; appears later due to macro ordering.





;;; `Add-frame-note' adds onto frame a note of type type-of-note with the
;;; specified particulars.  The frame status is left unchanged.  If there is an
;;; existing note of type type-of-note, it is discarded, and its particulars are
;;; recycled unless recycle-old-particulars-list-if-any?  is nil.  (The only
;;; reason not to recycle the old particulars is if the new particulars
;;; incorporate conses from the old particulars).  If
;;; do-not-update-representations?  is non-nil, any representions of the frame
;;; status and notes for frame will not be updated; this is an appropriate
;;; option to exercise if another update of the frame-status-and-notes slot will
;;; happen immediately or if frame is being deleted.  Frame is returned.

;;; Add-frame-note is sensitive to the binding of
;;; current-computation-component-particulars.  If this is non-nil,
;;; add-frame-note will call add-frame-note-to-component-particulars which adds
;;; the frame note for the component particular rather than the entire frame
;;; (see also add-frame-note-to-component-particulars).

(defun add-frame-note 
       (type-of-note frame
	&optional particulars recycle-old-particulars-list-if-any?
	do-not-update-representations?)
  (if current-computation-component-particulars
      (add-frame-note-to-component-particulars
	type-of-note frame
	current-computation-component-particulars
	particulars
	recycle-old-particulars-list-if-any? do-not-update-representations?)
      (add-frame-note-1
	type-of-note frame particulars
	recycle-old-particulars-list-if-any? do-not-update-representations?)))

(defun add-frame-note-1
       (type-of-note frame particulars recycle-old-particulars-list-if-any?
	do-not-update-representations?)
  (let* ((frame-status-and-notes
	   (frame-status-and-notes frame))
	 (old-particulars-or-no-value
	   (getfq (cdr frame-status-and-notes) type-of-note no-value)))
    (cond
      ((eq old-particulars-or-no-value no-value)
       (setf (frame-status-and-notes frame) ; needed at least if noting
					    ;    changes (MHD 7/18/94)
	     (nconc (or frame-status-and-notes
			(slot-value-cons nil nil))
		    (slot-value-cons
		      type-of-note
		      (slot-value-cons particulars nil)))))
      (t (setf (frame-status-and-notes frame) ; ditto.
	       (progn
		 (setf (getf (cdr frame-status-and-notes) type-of-note)
		       particulars)
		 (frame-status-and-notes frame)))		 
	 (when (and recycle-old-particulars-list-if-any?
		    (not (atom old-particulars-or-no-value)))
	   (reclaim-slot-value old-particulars-or-no-value))))

    (unless do-not-update-representations?
      (update-representations-of-frame-notes frame))

    (check-for-frame-being-embedded frame)

    frame))





;;; `Delete-frame-note-if-any' looks for a frame note on frame of type
;;; type-of-note, and if there is such a note, deletes it, recycles it, and
;;; updates any representions of the frame status and notes for frame.
;;; Type-of-note is returned if a note is actually deleted; otherwise, nil is
;;; returned.

;;; Delete-frame-note-if-any is sensitive to the binding of
;;; current-computation-component-particulars.  If this is non-nil, it will call
;;; delete-frame-note-from-component-particulars which adds the frame note for
;;; the component particular rather than the entire frame (see also
;;; delete-frame-note-from-component-particulars).

;;; `Delete-multiple-frame-notes-if-any' is just like delete-frame-note-if-any
;;; except that it takes a list, types-of-notes, instead of a single
;;; type-of-note.

(defun delete-frame-note-if-any (type-of-note frame)
  (if current-computation-component-particulars
      (delete-frame-note-from-component-particulars
	type-of-note frame current-computation-component-particulars)
      (delete-frame-note-if-any-1 type-of-note frame)))

(defun delete-frame-note-if-any-1 (type-of-note frame)
  (let ((frame-status-and-notes
	  (frame-status-and-notes frame)))
    (prog1
	(unless (atom frame-status-and-notes)
	  (loop as l = frame-status-and-notes
		     then (cdr-of-cons plist-tail)
		as plist-tail = (cdr-of-cons l)
		while plist-tail
		when (eq (car-of-cons plist-tail) type-of-note)
		  do (note-change-to-block frame 'frame-status-and-notes)
		     (setf (cdr l) (cddr plist-tail))
		     (setf (cddr plist-tail) nil)
		     (reclaim-slot-value plist-tail)
		     (cond
		       ((and (null (car frame-status-and-notes))
			     (null (cdr frame-status-and-notes)))
			(setf (frame-status-and-notes frame) nil)
			(reclaim-slot-value-cons-macro frame-status-and-notes)))
		     (update-representations-of-frame-notes frame)
		     (return type-of-note)))
      (when (parent-frame frame)
	(check-for-frame-being-embedded frame)))))


(defun delete-multiple-frame-notes-if-any (types-of-notes frame)
  (when (frame-status-and-notes frame)
    (loop for type-of-note in types-of-notes
	  do (delete-frame-note-if-any type-of-note frame))))





;;; `Add-to-frame-note-particulars-list-if-necessary' adds item at the end of
;;; the particulars list of the type-of-note note on frame, if there is such a
;;; note and item is not yet among its particulars.  If there is no type-of-note
;;; note, one is added with just item in its particulars list.  Representations
;;; of the frame status and notes for frame are updated, if necessary and
;;; possible.

;;; It always calls add-frame-note unless no change is needed. 

;;; Add-to-frame-note-particulars-list-if-necessary is sensitive to the binding
;;; of current-computation-component-particulars.  If this is non-nil, it will
;;; call add-frame-note-particular-to-component-particulars, which adds the
;;; frame note for the component particular rather than the entire frame. (See
;;; also add-frame-note-particular-to-component-particulars.)

(defun add-to-frame-note-particulars-list-if-necessary
       (item type-of-note frame)
  (if current-computation-component-particulars
      (add-frame-note-particular-to-component-particulars
	item type-of-note frame
	current-computation-component-particulars)
      (add-to-frame-note-particulars-list-if-necessary-1
	item type-of-note frame)))

(defun add-to-frame-note-particulars-list-if-necessary-1
       (item type-of-note frame)
  (let ((existing-particulars
	  (get-particulars-of-frame-note-if-any type-of-note frame)))
    (if (not (member item existing-particulars :test #'equal))
	(add-frame-note-1
	  type-of-note frame
	  (nconc existing-particulars (slot-value-cons item nil))
	  nil nil))))


;;; `Component-particulars-with-frame-notes' collects from the
;;; *current-computation-frame* the set of those component particulars which have
;;; frame notes.  A fresh list of slot value conses is returned to the caller.

;;; Note that the elements of this list are owned by the frame status and
;;; notes.  If you delete notes these elements may be deleted.

(defun component-particulars-with-frame-notes ()
  (loop for (component-particulars . nil) 
	    in (get-particulars-of-frame-notes-for-component-particulars
		 *current-computation-frame*)
	collect component-particulars using slot-value-cons))





;;; `Delete-from-frame-note-particulars-list' deletes item, if present (using eq
;;; as the test), from the particulars list of the type-of-note note on frame.
;;; Item should occur at most once in that list.  The abandoned cons and item,
;;; if any, is recycled.  If item was the only element in the particulars list,
;;; the note itself is deleted.  Representations of the frame status and notes
;;; for frame are updated, if necessary and possible.

;;; It always calls add-frame-note or delete-frame-note unless no change is needed.

;;; Delete-from-frame-note-particulars-list is sensitive to the binding of
;;; current-computation-component-particulars.  If this is non-nil, it will call
;;; delete-frame-note-particular-from-component-particulars, which adds the frame
;;; note for the component particular rather than the entire frame. (See also
;;; delete-frame-note-particular-from-component-particulars.)

(defun delete-from-frame-note-particulars-list
       (key-for-item type-of-note frame)	
  (if current-computation-component-particulars
      (delete-frame-note-particular-from-component-particulars
	key-for-item type-of-note frame
	current-computation-component-particulars)
      (delete-from-frame-note-particulars-list-2
	key-for-item type-of-note frame)))

(defun delete-from-frame-note-particulars-list-2
       (key-for-item type-of-note frame)	
  (let ((particulars
	  (get-particulars-of-frame-note-if-any type-of-note frame)))
    (when (memq key-for-item particulars)
      (if (null (cdr particulars))
	  (delete-frame-note-if-any-1 type-of-note frame)
	  (add-frame-note-1
	    type-of-note frame
	    (delete-from-frame-note-particulars-list-1
	      key-for-item particulars)
	    nil nil)))))

(defun delete-from-frame-note-particulars-list-1
       (key-for-item particulars)
  (loop as l-trailer? = nil then l
	as l = particulars then (cdr l)
	until (eq key-for-item (car l))		       ; loop terminates only
						       ; if item present
	finally
	  (if l-trailer?
	      (setf (cdr l-trailer?) (cdr l))
	      (setq particulars (cdr l)))
	  (setf (cdr l) nil)
	  (reclaim-slot-value l)
	  (return particulars)))



;;; Def-frame-note-writer defines a `frame note writer', a function that writes,
;;; as a sentence, a frame note of type type-of-note.  Body, which will be the
;;; function's body, may refer to the particulars of the note via
;;; particulars-var, and, if listed-frame-var is specified, body may refer to
;;; the frame via the listed variable.

;;; Frame note writers are invoked, when there are notes, by the slot value
;;; writer for the frame-status-and-notes slot.  What's written by a frame note
;;; writer must be grammatically an English sentence without initial
;;; capitalization, final punctuation, or internal semicolons. (See exception
;;; below.)  See def-slot-value-writer for how frame note writers should do
;;;  their writing.

;;; A frame note writer may have a superior type-of-note specified. This may be
;;; used to group the notes for the purpose of searching for them. There is no
;;; check on circularity, which ought not to occur.  (Never has been used!!!)

;;; It is permitted to write a frame note that has the appearance of several
;;; frame notes.  To do this, use the format "(i) ... ; (i+1)" ... .
;;; Specifically, do the following:
;;; 
;;;    For the first note, unless frame-note-index-has-been-written?
;;;    or you are only writing one note, write "(i) ", where i is
;;;    the value of frame-note-index.
;;;    
;;;    For each subsequent note except for the last, write "; (i)",
;;;    numbering them consecutively. (This is an exception to the rule
;;;    that no internal semicolons should appear within a note.)
;;;    
;;;    After writing the complete note, increment frame-note-index-skip by
;;;    n-1, where n subnotes have been written.
;;;
;;; The main purpose of this feature is to permit a frame to include frame
;;; notes of inferior frames which are not displayed.  See write-frame-notes-
;;; of-inferior-frames.  Another purpose is to allow a single note that deals
;;; with a number of types problems or with a number of instances of a
;;; particular type of problem to appear as a number of subnotes instead of as
;;; one long note.
;;; The macro do-frame-notes iterates over the notes portions of
;;; frame-status-and-notes.

(def-global-property-name frame-note-writer-1)

(def-global-property-name superior-frame-note-type)

(def-global-property-name inferior-frame-note-types)

(defmacro frame-note-writer (symbol)
  (let ((writer? (gensym)))
    `(let ((,writer? (frame-note-writer-1 ,symbol)))
       (if ,writer?
	   (compiled-function-in-place ,writer?)
	   nil))))

(defmacro def-frame-note-writer
	  (type-of-note (particulars-var . listed-frame-var-and-superior-type)
	   &body body)
  (let ((name (intern (format nil "WRITE-~A-NOTE" type-of-note)))
	(frame-var (if listed-frame-var-and-superior-type
		       (car listed-frame-var-and-superior-type) (gensym)))
	(superior-type (if (cdr listed-frame-var-and-superior-type)
			   (second listed-frame-var-and-superior-type) (gensym))))
    `(progn
       ,@(when (cdr listed-frame-var-and-superior-type)
	   `((setf (superior-frame-note-type ',type-of-note) ',superior-type)
	     (pushnew ',type-of-note
		      (inferior-frame-note-types ',superior-type))))
       (defun-simple-into-place (,name (frame-note-writer-1 ',type-of-note))
	   (,particulars-var ,frame-var)
	 ,@(if (null listed-frame-var-and-superior-type)
	       `((declare (ignore ,frame-var))))
	 . ,body)
       ',name)))


;;; `Def-abstract-frame-note-type' is used to define a frame note type that will
;;; have no instances, but is a node on the frame note hierarchy for the purpose
;;; of grouping them in a tree. All frame notes should be placed in a single
;;; tree whose root is 'frame-notes.

(defmacro def-abstract-frame-note-type (frame-note-type superior-type)
  `(progn (setf (superior-frame-note-type ',frame-note-type) ',superior-type)
	  (pushnew ',frame-note-type
		   (inferior-frame-note-types ',superior-type))))


;;; `Frame-note-subtype-or-eq-p' is t if the first frame-note-type is below the
;;; second one in the hierarchy, or is the same as the second one. Frame note
;;; types are symbols.

(defun frame-note-subtype-p (frame-note-type possible-superior-type)
  (loop for type = frame-note-type then (superior-frame-note-type type)
	until (null type)
	if (eq type possible-superior-type) do (return t)))



;; The following documented toward front of file. Placed here because
;; it must follow def-frame-note-writer.

(def-frame-note-writer
  embedded-rule-has-frame-notes (particulars frame-with-embedded-rule)
  ;; particulars is a slot name, the name of the embedded rule slot
  (when (get-slot-value frame-with-embedded-rule particulars)	; added cond. (MHD 7/5/90)
    (write-frame-notes-of-inferior-frame 
      (get-slot-value frame-with-embedded-rule particulars))))


;; Note that 'embedded-rule-has-frame-notes exists in saved kbs.



;;; The verbosely named function `frame-status-and-notes-reflects-flags-
;;; of-frame-p' is a predicate which returns whether or not the slot value
;;; writer for frame-status-and-notes will be writing any notifications of data
;;; stored in the frame-flags.  This is used in the slot value writer for
;;; frame-status-and-notes and in the inference engine evaluator with-status,
;;; which is used by Inspect to determine the "status" of a frame.  See
;;; module QUERIES.

(defun frame-status-and-notes-reflects-flags-of-frame-p (frame)
  (or (manually-disabled-p frame)
      (ancestor-not-activatable-p frame)
      (and (or system-is-running system-has-paused)
	   (not (frame-of-class-p frame 'simulation-subtable))
	   (not (active-p frame)))))

;; Consider changing the way frame note writers are named.



(defvar frame-note-index-skip)
(defvar frame-note-index)
(defvar frame-note-index-has-been-written?)
(defvar frame-note-count)



;;; `do-frame-notes'
;;; This macro iterates over the notes portion of a frame's
;;; frame-status-and-notes, and for each note, binds note-iteration-variable
;;; to a newly allocated wide-string.
;;; Unless the caller sets the note-iteration-variable to nil within the body,
;;; the string will be immediately reclaimed.
;;; The variables frame-note-index-skip, frame-note-index, frame-note-count,
;;; and frame-note-index-has-been-written? are all global variables that
;;; will be bound within the context of do-frame-notes.

(defmacro do-frame-notes (((note-iteration-variable) frame) &body body)
  (avoiding-variable-capture
      (frame &aux frame-status-and-notes index rest-of-plist
	     frame-note-writer? type-of-note particulars)
    `(let ((,frame-status-and-notes
	      (frame-status-and-notes ,frame)))
       (when (cdr ,frame-status-and-notes)
	 (loop with frame-note-index-skip = 0
	       with frame-note-count = (halff (length (cdr ,frame-status-and-notes)))
	       as ,index from 1
	       as frame-note-index = (+f ,index frame-note-index-skip)
	       as frame-note-index-has-been-written? 
		  = (or ,rest-of-plist (>f frame-note-index 1))
	       as (,type-of-note ,particulars . ,rest-of-plist)
		  = (cdr ,frame-status-and-notes)
		  then ,rest-of-plist
	       as ,frame-note-writer?
		  = (frame-note-writer ,type-of-note)
	       as ,note-iteration-variable
		  = (twith-output-to-text-string
		      (cond
			(,frame-note-writer?
			 (funcall-simple-compiled-function
			   ,frame-note-writer? ,particulars ,frame))
			(t
			 (tformat "~S [frame note writer missing for type of note ~A]"
				  ,particulars ,type-of-note))))
	       do (progn ,@body)
		  (when ,note-iteration-variable
		    (reclaim-wide-string ,note-iteration-variable))
	       until (null ,rest-of-plist))))))


;;; The virtual attribute `item-notes' is used to extract the text of the frame
;;; notes of the given frame.  We do not yet expose the symbols that name types of
;;; frame names, just the sequence of strings.

(def-virtual-attribute item-notes ((class block) (or (sequence text) (no-item)) nil)
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) nil)
  :getter ((frame)
	   (let ((notes nil))
	     (do-frame-notes ((note) frame)
	       (eval-push note notes)
	       (setq note nil))
	     (when notes
	       (allocate-evaluation-sequence (nreverse notes))))))


(def-slot-value-writer frame-status-and-notes (frame-status-and-notes frame)
  (if (and (frame-of-class-p frame 'block)
	   (name-for-debugging frame)
	   ;; Modified by ML, 3/13/90 to not print the name for debugging
	   ;; in the frame notes if the frame has at least one name.
	   ;; Undone by Ben 9/10/91, debugging names are now generated
	   ;; in some senarios even when you have a primary name, for
	   ;; example when you lack a unique name.
	   ; (null (name-or-names-for-frame frame))
	   )
      (tformat "~A: " (get-cached-debugging-name frame)))
  (twrite-symbol (or (car frame-status-and-notes) 'ok) t)

  
 
  ;; The message "not active" appears in the frame notes when (1) the frame is
  ;; not active, and (2) the system is running or paused, and (3) none of the
  ;; conditions above this comment apply, and (4) the frame is not a
  ;; simulation-subtable.  System frames now get activated and deactivated by
  ;; system-start and system-reset respectively.  If there are other types of
  ;; frames which are represented to the user by tables, but are not activated
  ;; and deactivated, they should be added to the code below to prevent the
  ;; message from appearing.  -ML-, 1 July, 88.
  
  (when (frame-status-and-notes-reflects-flags-of-frame-p frame)
    (tformat
      ", ~a ~a~a"
      (if (car frame-status-and-notes)  "and" "but")
      (cond
	((and (manually-disabled-p frame) (ancestor-not-activatable-p frame))
	 "DISABLED, and some superior item is either DISABLED or not OK")	; "DISABLED, BAD, or INCOMPLETE"?
	((manually-disabled-p frame)
	 "DISABLED")
	((ancestor-not-activatable-p frame)
	 "some superior item is either DISABLED or not OK")
	((and (frame-of-class-p frame 'rule) (initial-rule-p frame))
	 "this INITIALLY rule is no longer active, having completed or timed out")
	(t "not active"))
      (if (cdr frame-status-and-notes) "" ".")))

  (when (cdr frame-status-and-notes)
    (twrite-string ", and note that ")
    (twrite-frame-notes frame nil)))

(defvar abbreviate-frame-notes-p nil)

(defun-void twrite-frame-notes (frame abbreviate-frame-notes-p)
  (do-frame-notes ((note) frame)
    (when frame-note-index-has-been-written?
      (tformat "~%(~D) " frame-note-index))
    (twrite-string note)
    (unless (>=f frame-note-index frame-note-count)
      (twrite-string "; "))))

;; Consider changing ", and note that " to " -- and note that" or ".  Note
;; that".

;; Eventually assume that all types of notes have frame note writers, and get
;; rid of the test and default writer-cum-error-message!





;;; `Write-frame-notes-of-inferior-frame' writes all the frame notes of the 
;;; specified frame. It must be called only within a frame-note-writer 
;;; (otherwise its variables will be unbound), and writes as a single note
;;; what looks like a series of notes with appropriate numbering as per the
;;; frame note writer. See discussion under def-frame-note-writer.

;;; It should be called only when inferior-frame has one or more frame notes.

(defun write-frame-notes-of-inferior-frame (inferior-frame)
  (loop for (type-of-note particulars . rest-of-plist) =
	    (cdr (frame-status-and-notes inferior-frame)) then rest-of-plist
	for frame-note-writer?
	    = (frame-note-writer type-of-note)
	for index from frame-note-index doing 

    (unless (and (or frame-note-index-has-been-written?
		     (null rest-of-plist))
		 (=f index frame-note-index))
      (tformat "(~d) " index)) 

    (if frame-note-writer?
	(funcall-simple-compiled-function
	  frame-note-writer? particulars inferior-frame)
	(tformat "~S [frame note writer missing for type of note ~A]"
		 particulars type-of-note))

    (unless (null rest-of-plist) (twrite-string "; "))

	until (null rest-of-plist)

	finally

	  (setq frame-note-index-skip
		(+f frame-note-index-skip (-f index frame-note-index)))))



;;; Frame Notes for Component Particulars

;;; The frame note type frame-notes-for-component-particulars should be used for
;;; noting frame notes of component particulars of a frame on the frame itself.
;;; This is useful for tables for example, where there are many cells in the
;;; table, but the frame notes for problems related to the cells are noted on the
;;; table.

;;; The particulars of frame-notes-for-component-particulars are of the form
;;; (component-particulars status . frame-notes), where component-particulars is a
;;; slot value of the appropriate form for the type of frame, status indicates the
;;; status of the component particular, and frame-notes are any other type of
;;; frame note.  The frame note writer for frame-notes-for-component-particulars
;;; uses the denote-component-of-block to write the component particulars, writes
;;; the status, and then calls the appropriate frame note writers for the
;;; frame-notes.  Note that this frame note should only be used for frames of
;;; class block.

;;; As with the non component particular situation, status is typically not set by
;;; the mechanism which puts up the frame notes.  For example, the rule compiler
;;; puts up frame notes but does not change status of frames or component
;;; particulars.  However, things that call the rule compiler can determine status
;;; based on frame notes by using the function bad-status-compiler-frame-notes?.

;;; The usual frame note primitives (add-frame-note,
;;; add-to-frame-note-particulars-list-if-necessary, delete-frame-note-if-any, and
;;; delete-from-frame-note-particulars-list, etc.) all work for
;;; frame-notes-for-component-particulars.  However, some additional primitives
;;; are provided to simplify use of this type of frame note.  These primitives
;;; should be used to ensure robustness.

;;; Add-frame-note-to-component-particulars is like add-frame-note except that it
;;; takes a component particular as an additional argument and adds the frame note
;;; to the component particular, creating an entry for the component particular if
;;; none exists.  Add-frame-note-particular-to-component-particulars is like
;;; add-to-frame-note-particulars-list-if-necessary except that it takes a
;;; component particular as an argument and adds the particular to the appropriate
;;; frame note for that component particular.  Similarly,
;;; delete-frame-note-from-component-particulars and
;;; delete-frame-note-particular-from-component-particulars are like
;;; delete-frame-note-if-any and delete-from-frame-note-particulars-list, except
;;; that they are specific to component particulars.

;; See "ma:>agh>array-compiles" for test cases.

; start using component particulars special var in compiler.



(def-frame-note-writer frame-notes-for-component-particulars
		       (frame-notes-for-component-particulars frame)
  (loop for (component-particulars (status . frame-notes))
	    in frame-notes-for-component-particulars
	do
    (tformat "~%for ")	
    (denote-component-of-block nil component-particulars frame)
    (write-status-of-component-particulars
      component-particulars status)
    (when frame-notes
      (loop initially
;	      (twrite-string ", and note that ")
	      (twrite-string ", ")
	    with frame-note-index-skip = 0
	    as (type-of-note particulars . rest-of-plist)
	       = frame-notes
			     then rest-of-plist
	    as frame-note-writer?
	       = (frame-note-writer type-of-note)
	    as index from 1
	    as frame-note-index = (+f index frame-note-index-skip)
	    as frame-note-index-has-been-written? =
	       (or rest-of-plist (> frame-note-index 1))
	    do (if frame-note-index-has-been-written?
		   (tformat "~%(~D) " frame-note-index))
	       ;; Change the funcall below to funcall-simple-compiled-function
	       ;; after the next recompile.  -jra 5/17/91
	       (if frame-note-writer?
		   (funcall-simple-compiled-function
		     frame-note-writer? particulars frame)
		   (tformat "~S [frame note writer missing for type of note ~A]"
			    particulars type-of-note))
	       (if (null rest-of-plist)
		   (return nil))		       ; arbitrary value
	       (twrite-string "; ")))))



(defun add-frame-note-to-component-particulars
       (type-of-note frame component-particulars particulars
	recycle-old-particulars-list-if-any? do-not-update-representations?)
  (add-frame-note-1
    'frame-notes-for-component-particulars
    frame 
    (add-frame-note-to-component-particulars-1
      type-of-note frame component-particulars particulars
      recycle-old-particulars-list-if-any?)
    nil do-not-update-representations?))

(defun add-frame-note-to-component-particulars-1
       (type-of-note frame component-particulars particulars
	recycle-old-particulars-list-if-any?)
  (note-change-to-block frame 'frame-status-and-notes)
  (let (component-particulars-entry frame-status-and-notes
	old-particulars-or-no-value
	particulars-of-frame-notes-for-component-particulars)
    (multiple-value-setq
      (component-particulars-entry 
       particulars-of-frame-notes-for-component-particulars)
      (get-or-make-entry-for-component-particulars
	component-particulars frame))
    (setq frame-status-and-notes (second component-particulars-entry)
	  old-particulars-or-no-value
	  (getfq (cdr frame-status-and-notes) type-of-note no-value))
    (cond
      ((eq old-particulars-or-no-value no-value)
       (setf (second component-particulars-entry)
	     (nconc (or frame-status-and-notes
			(slot-value-cons nil nil))
		    (slot-value-cons 
		      type-of-note (slot-value-cons particulars nil)))))
      (t
       (setf (getf (cdr frame-status-and-notes) type-of-note)
	     particulars)
       (when (and recycle-old-particulars-list-if-any?
		  (not (atom old-particulars-or-no-value)))
	 (reclaim-slot-value old-particulars-or-no-value))))
    particulars-of-frame-notes-for-component-particulars))

(defun get-or-make-entry-for-component-particulars (component-particulars frame)
  (let* ((particulars-of-frame-notes-for-component-particulars
	   (get-particulars-of-frame-notes-for-component-particulars
	     frame))
	 (component-particulars-entry?
	   (assoc component-particulars 
		  particulars-of-frame-notes-for-component-particulars
		  :test #'equal)))
    (cond 
      (component-particulars-entry?
       (values component-particulars-entry?
	       particulars-of-frame-notes-for-component-particulars))
      (t
       (let ((new-component-particulars-entry?
	       (slot-value-list (copy-for-slot-value component-particulars) nil)))
	 (values new-component-particulars-entry?
		 (nconc particulars-of-frame-notes-for-component-particulars
			(slot-value-list new-component-particulars-entry?))))))))

(defun get-entry-for-component-particulars (component-particulars frame)
  (let ((current-computation-component-particulars nil))
    (assoc component-particulars 
	   (get-particulars-of-frame-note-if-any
	     'frame-notes-for-component-particulars frame)
	   :test #'equal)))

(defun add-frame-note-particular-to-component-particulars
       (particular type-of-note frame component-particulars)
  (let* ((existing-particulars?
	   (get-particulars-of-frame-note-from-component-particulars
	     type-of-note frame component-particulars)))
    (when (not (memq particular existing-particulars?))
      (add-frame-note-to-component-particulars
	type-of-note frame component-particulars 
	(nconc existing-particulars? (slot-value-cons particular nil))
	nil nil))))

(defun delete-frame-note-from-component-particulars 
       (type-of-note frame component-particulars)
  (let ((component-particulars-entry?
	  (get-entry-for-component-particulars
	    component-particulars frame)))
    (delete-frame-note-from-component-particulars-1
      type-of-note frame component-particulars-entry? 
      (second component-particulars-entry?))))

(defun delete-frame-note-from-component-particulars-1
       (type-of-note? frame component-particulars-entry? frame-status-and-notes)
  (unless (atom frame-status-and-notes)
    (loop as l = frame-status-and-notes
	       then (cdr plist-tail)
	  as plist-tail = (cdr l)
	  while plist-tail
	  when (or (null type-of-note?)
		   (eq (car plist-tail) type-of-note?))
	    do (note-change-to-block frame 'frame-status-and-notes)
	       (setf (cdr l) (cddr plist-tail))
	       (setf (cddr plist-tail) nil)
	       (reclaim-slot-value plist-tail)
	       (when (and (null (car frame-status-and-notes))
			  (null (cdr frame-status-and-notes)))
		 (setf (second component-particulars-entry?) nil)
		 (reclaim-slot-value-cons-macro frame-status-and-notes)
		 (with-updates-to-representations-supressed
		   (frame 'frame-status-and-notes)
		   (let ((current-computation-component-particulars nil))
		     (delete-from-frame-note-particulars-list-2
		       component-particulars-entry? 
		       'frame-notes-for-component-particulars frame))))
	       (update-representations-of-frame-notes frame)
	       (return type-of-note?))))



(defun delete-all-frame-notes-for-component-particular
       (component-particulars frame)
  (let ((component-particulars-entry?
	  (get-entry-for-component-particulars
	    component-particulars frame)))
    (delete-frame-note-from-component-particulars-1
      nil frame component-particulars-entry? 
      (second component-particulars-entry?))))



(defun delete-frame-note-particular-from-component-particulars
       (key-for-item type-of-note frame component-particulars)
  (let* ((particulars
	   (get-particulars-of-frame-note-from-component-particulars
	     type-of-note frame component-particulars)))
    (when (memq key-for-item particulars)
      (if (null (cdr particulars))
	  (delete-frame-note-from-component-particulars
	    type-of-note frame component-particulars)
	  (add-frame-note-to-component-particulars
	    type-of-note frame component-particulars
	    (delete-from-frame-note-particulars-list-1
	      key-for-item particulars)
	    nil nil)))))



;;; Delete-frame-note-from-all-component-particulars-of-frame is useful for
;;; getting rid of frame notes that are within the component particulars entries
;;; of 'frame-notes-for-component-particulars notes.

(defun delete-frame-note-from-all-component-particulars-of-frame
       (type-of-note frame)
  (loop with component-particulars-entries
	  = (get-particulars-of-frame-notes-for-component-particulars frame)
	for component-particulars-entry in component-particulars-entries
	do (delete-frame-note-from-component-particulars-1
	     type-of-note frame component-particulars-entry
	     (second component-particulars-entry))))

;; Consider writing 
;; delete-frame-note-particular-from-all-component-particulars-of-frame.



;;; Delete-frame-notes-of-types-in-list is provided for convenience since it is
;;; often necessary to delete a whole set of frame notes.

(defun-void delete-frame-notes-of-types-in-list 
    (frame frame-note-type-list delete-only-from-component-particulars?)
  (when (frame-has-frame-notes-p frame)
    (with-updates-to-representations-supressed
	(frame 'frame-status-and-notes)
      (loop for frame-note-type in frame-note-type-list
	    do
	(if delete-only-from-component-particulars?
	    (delete-frame-note-from-all-component-particulars-of-frame
	      frame-note-type frame)
	    (delete-frame-note-if-any frame-note-type frame))))))

;; Consider writing delete-frame-note-particulars-from-types-in-list.




;;; The development-only function `check-frame-notes' will iterate over frames
;;; checking integrity of frame note data structures.  It takes an optional
;;; argument, which should either be a symbol naming a class of items to iterate
;;; across, or should take an individual frame.  The argument defaults to block,
;;; where the slot frame-status-and-notes is defined.  If there are any
;;; problems, a description of is written to standard output.

#+development
(defun check-frame-notes (&optional (class-or-frame 'block))
  (cond ((of-class-p class-or-frame 'block)
	 (check-frame-notes-of-frame class-or-frame)
	 1)
	((and (symbolp class-or-frame)
	      (subclassp class-or-frame 'block))
	 (loop for frame being each class-instance of class-or-frame
	       count t
	       do
	   (check-frame-notes-of-frame frame)))
	(t
	 (error
	   "~A wasn't a symbol naming a subclass of block or an instance of ~
            block."
	   class-or-frame))))

#+development
(defun check-frame-notes-of-frame (frame)
  (let ((status-and-notes (frame-status-and-notes frame)))
    (unless (null status-and-notes)	; NIL is OK.
      (let* ((status (car status-and-notes))
	     (notes (cdr status-and-notes)))
	(unless (memq status '(nil incomplete bad))
	  (format
	    t "Status of ~a was not one of nil, incomplete, or bad, it was ~A~%"
	    frame status))
	(loop until (null notes) do
	  (cond ((and (consp notes)
		      (consp (cdr notes))
		      (symbolp (car notes))
		      (frame-note-writer (car notes)))
		 (setq notes (cddr notes)))
		(t
		 (format
		   t "Notes of ~a were bad: ~s~%" frame notes)
		 (loop-finish))))))))





;;;; Directories of Names

;; Consider moving this to module MENUS.

;; In "delivery" versions of G2, do not maintain directories of names!



;;; A `directory of names' is a data-abstracted structure that records all
;;; symbol and/or string instances of a specific grammar category in such a way
;;; that all such instances that begin with a particular sequence of characters
;;; can be efficiently found.  The operations on directories of names are:
;;; add-to-directory-of-names, delete-from-directory-of-names, make-menu-of-
;;; names-from-directory, and in-directory-of-names-p.

;;; A directory of names for a grammar category is kept as the directory-of-names
;;; property (a kb-specific property) of the category symbol. Note that since
;;; the property is kb-specific, directories cannot be created or populated
;;; before the initial call to run-ab, i.e. not while G2 loads. All of the
;;; directories that are populated by names that are defined before any
;;; user actions (e.g. the names of the foundation classes) are set up by
;;; a call to initialize-kb-name-directories (which is called as part of
;;; run-ab or clear-kb). Many of the routines in that function are table-
;;; driven, see, e.g., classes-and-directory-categories-for-frame-names.

;;; Directories are created automatically as a side-effect of the first call
;;; to add-to-directory-of-names that mentions a given category. The property
;;; remains on the category symbol thereafter even if all of the names have
;;; been removed by calls to delete-from-category-of-names. 

;;; A directory of names may be:
;;;
;;;    (a) nil, representing an empty directory;
;;;
;;;    (b) a string or a symbol other than nil, with nil represented by an
;;;    uninterned nil kept as the value of special variable directory-nil;
;;;
;;;    (c) a grammar list of the form (d1 d2 ... dn), where
;;;
;;;        (1) n > 1,
;;;
;;;        (2) each di is a non-empty directory of names,
;;;
;;;        (3) for some m, all the names in all of the di have the same
;;;        (char-equal) first m characters,
;;;
;;;        (4) for every j and k such that j < k <= n, either dj is a name with
;;;        exactly  m characters or all the names in dj and in dk have at
;;;        least m + 1 characters and the (m + 1)st character of each name
;;;        in dj is < (i.e., char-lessp) the  (m + 1)st character of each
;;;        name in dk, and
;;;
;;;        (5) for each di that is a grammar list, all the names in di have at
;;;        least the same (char-equal) first (m + 1) characters.

;;; A directory of names can contain duplicate names.

;; Note: changed the definitions of "same" from char= to char-equal today.
;; Rationale explained further below.  (MHD 4/18/94)

;; Note that (c5) is somewhat redundant with (c3) and could be stated as a
;; variant of (c4).

;; Consider having format (c) be (d1 d2 ... dn-1 . dn).  This would save some
;; space, but would be slower and more complicated to iterate over.

;; The operation in-directory-of-names-p was added today.  I needed it because
;; I wanted to avoid duplicate names, and there was no way to do that without
;; maintaining alternate data structures or changing the spec to disallow them.
;; This function had already been defined, but had not been documented or used
;; anywhere until now.  Someone should review (and then document) why allowing
;; duplicate names is desirable in the spec!  (MHD 5/29/90)

;; Duplicate names appear to provide a poor man's reference count.  
;; If 5 user restrictions statements reference a given mode then
;; it will appear five times. (BAH 7/1/90)

(defvar directory-nil (make-symbol "nil"))	; use copy-symbol?

;; What is directory-nil for, you ask?  Recall that nil is the empty directory.
;; But, you can put nil in a directory!  So when you do the abstractions converts
;; your nil into directory nil for use internally. (BAH 7/1/90 -- I think this is
;; right)


(defun reclaim-grammar-tree-function (tree)
  (reclaim-grammar-tree tree))

; (def-kb-specific-property-name directory-of-names reclaim-grammar-tree-function) ; now in PARSE




;;; String-for-directory-name returns a string, either symbol-or-string itself
;;; or (symbol-name-text-string symbol-or-string).

(def-substitution-macro string-for-directory-name (symbol-or-string)
  (if (text-string-p symbol-or-string)
      symbol-or-string
      (symbol-name-text-string symbol-or-string)))



;;; String-for-first-name-in-directory ...

(defmacro string-for-first-name-in-directory (directory-of-names)
  `(loop for directory = ,directory-of-names
		       then (first directory)
	 when (atom directory)
	   return (string-for-directory-name directory)))



;;; Strings-have-same-ith-character-p ... assumes that string-2 is at least as
;;; long as string-1.

(def-substitution-macro strings-have-same-ith-character-p
			(string-1 string-2 i)
  (if (>f (text-string-length string-1) i)
      (char-equalw			; not case sensitive
	(charw string-1 i)
	(charw string-2 i))))

;; Change to comparison using char-equal vs. char=.
;; 
;; Changed these to be case insensitive.  They weren't before, but it didn't
;; matter (you couldn't tell) because were always (or almost always) dealing
;; with symbols, normalized to uppercase.  Now, we sometimes have strings, i.e.,
;; for file names in the KB Load File dialog.  Just implement this for now by
;; using the Common Lisp case-insensitive character comparison functions.
;; Specifically, EQL => CHAR-EQUAL, and CHAR>= => CHAR-NOT-LESSP. [However, we
;; forgot to include CHAR-NOT-LESSP in our set of imported CL functions, so I'm
;; just going to user (NOT (CHAR-LESSP x)) for now.]
;;
;; Review this again, and all the others, and at the same time review with
;; respect to gensym charcters.
;;
;; See if more efficient comparitors, possibly case-senstive, can be used
;; for some parts of this facility, as long as it would look the same to the
;; user.
;;
;; See if case sensitivity could be made an option.  It's not needed at
;; present, but it could be later.  (MHD 4/18/94)

;; Review this and following macros with respect to gensym characters!



;;; String-has-same-ith-character-as-simple-string-p ... assumes that
;;; simple-string has an ith character.

(def-substitution-macro string-has-same-ith-character-as-simple-string-p
    (string simple-string i)
  (if (>f (text-string-length string) i)
      (char-equalw			; not case sensitive
	(charw string i)
	(scharw simple-string i))))



;;; String-has-char>=-ith-character-as-simple-string-p ... assumes that
;;; simple-string has an ith character.

(def-substitution-macro string-has-char>=-ith-character-as-simple-string-p
    (string simple-string i)
  (if (>f (text-string-length string) i)
      (not (char-lesspw
	     (charw string i)			;verify that this does not cons!
	     (scharw simple-string i)))))



;;; get-directory-contents

;;;  returns a tree of the current contents of the directory.
;;;  This must not be modified or reclaimed.

(defun-simple get-directory-contents (category-symbol)
  (directory-of-names category-symbol))

;;; In-directory-of-names-p ...

(defun in-directory-of-names-p (symbol-or-string category-symbol)
  (if (null symbol-or-string) (setq symbol-or-string directory-nil))  ; changes arg
  (let ((directory-of-names (directory-of-names category-symbol)))
    (if directory-of-names
	(let ((simple-string
		(copy-text-string
		  (string-for-directory-name symbol-or-string))))
	  (prog1
	    (in-directory-of-names-1
	      directory-of-names
	      (string-for-first-name-in-directory directory-of-names)
	      (if (not (atom directory-of-names))
		  (string-for-first-name-in-directory
		    (second directory-of-names)))
	      0 symbol-or-string simple-string (text-string-length simple-string))
	    (reclaim-text-string simple-string))))))

(defun in-directory-of-names-1
       (non-empty-directory-of-names
	string-for-first-name-in-directory
	string-for-second-name-in-directory?
	m symbol-or-string simple-string length-of-simple-string)
  (let ((length-of-first-name-in-directory
	  (text-string-length string-for-first-name-in-directory)))
    (if (=f m length-of-simple-string)
	(=f length-of-first-name-in-directory length-of-simple-string)
	(let ((character (scharw simple-string m))
	      (character-1?
		(if (>f length-of-first-name-in-directory m)
		    (charw string-for-first-name-in-directory m))))
	  (if (or (null string-for-second-name-in-directory?)
		  (and character-1?
		       (char-equalw
			 character-1?	; char=?
			 (charw string-for-second-name-in-directory? m))))
	      (if (and character-1?
		       (char-equalw character-1? character))	; char=?
		  (in-directory-of-names-1	; could iterate instead
		    non-empty-directory-of-names
		    string-for-first-name-in-directory
		    string-for-second-name-in-directory? (+f m 1)
		    symbol-or-string simple-string length-of-simple-string))
	      (loop as l on non-empty-directory-of-names
		    as subdirectory = (car l)
		    as string-for-first-name-in-subdirectory
		       = string-for-first-name-in-directory
		       then (string-for-first-name-in-directory subdirectory)
		    as character?		; could be a bit more efficient
		       = character-1?
		       then (if (or character?
				    (>f
				      (text-string-length
					string-for-first-name-in-subdirectory)
				      m))
				(charw string-for-first-name-in-subdirectory m))
		    when (and character?
			      (not (char-lesspw character? character)))	; char>= ok?
		      return
			(if (char-equalw character? character)	; char=?
			    (in-directory-of-names-1
			      subdirectory
			      string-for-first-name-in-subdirectory
			      (if (not (atom subdirectory))
				  (string-for-first-name-in-directory
				    (second subdirectory)))
			      (+f m 1)
			      symbol-or-string
			      simple-string length-of-simple-string))))))))

;; This could have a trivial definition if it were restricted to the case of
;; relatively small directories of symbols.

;; Consider having this return the number of occurrences.

;; Consider having, as an argument, length-of-first-name-in-directory.

;; Consider having this do a binary search in the loop.



;;; Add-to-directory-of-names ...  A string used as the name is not copied and
;;; will not be reclaimed by this facility.  Such a string should be reclaimed
;;; elsewhere, but only after it has been deleted from the directory or after
;;; the directory has been used for the last time.

(defun add-to-directory-of-names (symbol-or-string category-symbol)
  (when (null symbol-or-string) (setq symbol-or-string directory-nil))  ;changes arg
  (setf (directory-of-names category-symbol)
	(let ((directory-of-names (directory-of-names category-symbol)))
	  (if (null directory-of-names)
	      symbol-or-string
	      (let ((simple-string
		      (copy-text-string (string-for-directory-name symbol-or-string))))
		(prog1 (add-to-directory-of-names-1
			 directory-of-names
			 (string-for-first-name-in-directory directory-of-names)
			 (if (not (atom directory-of-names))
			     (string-for-first-name-in-directory
			       (second directory-of-names)))
			 0 symbol-or-string simple-string (text-string-length simple-string))
		  (reclaim-text-string simple-string))))))
  nil)

(defun add-to-directory-of-names-1
       (non-empty-directory-of-names
	string-for-first-name-in-directory
	string-for-second-name-in-directory?
	m symbol-or-string simple-string length-of-simple-string)
  (if (=f m length-of-simple-string)
      (if (or (null string-for-second-name-in-directory?)
	      (strings-have-same-ith-character-p
		string-for-first-name-in-directory
		string-for-second-name-in-directory? m))
	  (grammar-list symbol-or-string non-empty-directory-of-names)
	  (grammar-cons symbol-or-string non-empty-directory-of-names))
      (let ((character (scharw simple-string m))
	    (character-1?
	      (if (>f (text-string-length string-for-first-name-in-directory) m)
		  (charw string-for-first-name-in-directory m))))
	(if (or (null string-for-second-name-in-directory?)
		(and character-1?
		     (char-equalw
		       character-1?
		       (charw string-for-second-name-in-directory? m))))
	    (if (and character-1?
		     (not (char-lesspw character-1? character)))
		(if (char-equalw character-1? character)
		    (add-to-directory-of-names-1
		      non-empty-directory-of-names
		      string-for-first-name-in-directory
		      string-for-second-name-in-directory? (+f m 1)
		      symbol-or-string simple-string length-of-simple-string)
		    (grammar-list symbol-or-string
				  non-empty-directory-of-names))
		(grammar-list non-empty-directory-of-names symbol-or-string))
	    (loop as l-trailer? = nil then l
		  as l on non-empty-directory-of-names
		  as subdirectory = (car l)
		  as string-for-first-name-in-subdirectory
		     = string-for-first-name-in-directory
		     then (string-for-first-name-in-directory subdirectory)
		  as character?
		     = character-1?
		     then (if (or character?
				  (>f
				    (text-string-length
				      string-for-first-name-in-subdirectory)
				    m))
			      (charw string-for-first-name-in-subdirectory m))
		  when (and character?
			    (not (char-lesspw character? character)))
		    do (if (char-equalw character? character)
			   (setf (car l)
				 (add-to-directory-of-names-1
				   subdirectory
				   string-for-first-name-in-subdirectory
				   (if (not (atom subdirectory))
				       (string-for-first-name-in-directory
					 (second subdirectory)))
				   (+f m 1)
				   symbol-or-string
				   simple-string length-of-simple-string))
			   (if l-trailer?
			       (setf (cdr l-trailer?)
				     (grammar-cons symbol-or-string l))
			       (return (grammar-cons symbol-or-string l))))
		       (return non-empty-directory-of-names)
		  finally
		    (setf (cdr l-trailer?) (grammar-list symbol-or-string))
 		    (return non-empty-directory-of-names))))))

;; Consider having, as an argument,length-of-first-name-in-directory.

;; Consider having this do a binary search in the loop.

;; Consider using grammar-cons-macro herein, for a bit more speed.



;;; Delete-from-directory-of-names assumes that symbol-or-string is in the
;;; directory of names for category-symbol.  If symbol-or-string is a string, it
;;; must be eq (not just equal) the string that was added to the directory.

(defun delete-from-directory-of-names (symbol-or-string category-symbol)
  (cond
    ((not releasing-kb?)			; see module FILES
     (if (null symbol-or-string)
	 (setq symbol-or-string directory-nil))	;changes arg
     (setf (directory-of-names category-symbol)
	   (let ((directory-of-names (directory-of-names category-symbol)))
	     (if directory-of-names		; this test should not be needed
		 (let ((simple-string
			 (copy-text-string
			   (string-for-directory-name symbol-or-string))))
		   (prog1
		     (delete-from-directory-of-names-1
		       directory-of-names
		       (string-for-first-name-in-directory directory-of-names)
		       0 symbol-or-string simple-string (text-string-length simple-string))
		     (reclaim-text-string simple-string)))))))))

(defun delete-from-directory-of-names-1
       (non-empty-directory-of-names string-for-first-name-in-directory m
	symbol-or-string simple-string length-of-simple-string)
  (cond
    ((atom non-empty-directory-of-names)
     (if (not (eq non-empty-directory-of-names symbol-or-string))	 
	 non-empty-directory-of-names))	; this case should never happen
    ((=f m length-of-simple-string)
     (if (eq (first non-empty-directory-of-names) symbol-or-string)
	 (if (cddr non-empty-directory-of-names)
	     (prog1
	       (cdr non-empty-directory-of-names)
	       (reclaim-grammar-cons non-empty-directory-of-names))
	     (prog1
	       (second non-empty-directory-of-names)
	       (reclaim-grammar-list non-empty-directory-of-names)))
	 non-empty-directory-of-names))	; this case should never happen
    ((and (string-has-same-ith-character-as-simple-string-p
	    string-for-first-name-in-directory simple-string m)
	  (string-has-same-ith-character-as-simple-string-p
	    (string-for-first-name-in-directory
	      (second non-empty-directory-of-names))
	    simple-string m))
     (delete-from-directory-of-names-1
       non-empty-directory-of-names string-for-first-name-in-directory (+f m 1)
       symbol-or-string simple-string length-of-simple-string))
    (t (loop as l-trailer? = nil then l
	     as l on non-empty-directory-of-names
	     as subdirectory = (car l)
	     as string-for-first-name-in-subdirectory
		= string-for-first-name-in-directory
		then (string-for-first-name-in-directory subdirectory)
	     when (string-has-same-ith-character-as-simple-string-p
		    string-for-first-name-in-subdirectory simple-string m)
	       do (let ((modified-subdirectory
			  (delete-from-directory-of-names-1
			    subdirectory string-for-first-name-in-subdirectory
			    (+f m 1)
			    symbol-or-string simple-string
			    length-of-simple-string)))
		    (if modified-subdirectory
			(setf (car l) modified-subdirectory)
			(progn
			  (if l-trailer?
			      (setf (cdr l-trailer?) (cdr l))
			      (setq non-empty-directory-of-names (cdr l)))
			  (reclaim-grammar-cons l))))
		  (loop-finish))
       (if (cdr non-empty-directory-of-names)
	   non-empty-directory-of-names
	   (prog1
	     (first non-empty-directory-of-names)
	     (reclaim-grammar-cons non-empty-directory-of-names))))))

;; Consider using reclaim-grammar-cons-macro herein, for a bit more speed.

;; This is not coded for maximum speed.



;;; `make-menu-tree-of-names-from-directory' - returns a tree of all
;;; the names in the given directory whose first length-of-prefix
;;; characters matches the prefix-simple-string.  There's no guarantee
;;; as to the organization of this tree.

(defun-simple make-menu-tree-of-names-from-directory
    (non-empty-directory-of-names string-for-first-name-in-directory
				  m prefix-simple-string length-of-prefix)
  (cond
    ((=f m length-of-prefix)
     non-empty-directory-of-names)
    ((atom non-empty-directory-of-names)
     (if (string-has-same-ith-character-as-simple-string-p
	   string-for-first-name-in-directory prefix-simple-string m)
	 (make-menu-tree-of-names-from-directory	; could iterate instead
	   non-empty-directory-of-names
	   string-for-first-name-in-directory
	   (+f m 1)
	   prefix-simple-string length-of-prefix)
	 nil))
    ((and (string-has-same-ith-character-as-simple-string-p
	    string-for-first-name-in-directory
	    prefix-simple-string
	    m)
	  (string-has-same-ith-character-as-simple-string-p
	    (string-for-first-name-in-directory (second non-empty-directory-of-names))
	    prefix-simple-string
	    m))
     (make-menu-tree-of-names-from-directory
       non-empty-directory-of-names
       string-for-first-name-in-directory
       (+f m 1)
       prefix-simple-string
       length-of-prefix))
    (t
     (loop for subdirectory in non-empty-directory-of-names
	   as string-for-first-name-in-subdirectory
	      = string-for-first-name-in-directory
	      then (string-for-first-name-in-directory subdirectory)
	   when (string-has-same-ith-character-as-simple-string-p
		  string-for-first-name-in-subdirectory prefix-simple-string m)
	     return
	     (make-menu-tree-of-names-from-directory
	       subdirectory string-for-first-name-in-subdirectory (+f m 1)
	       prefix-simple-string length-of-prefix)))))


;; Note that when make-menu-tree-of-names-from-directory is entered, all
;; names in non-empty-directory-of-names have the same first m characters as
;; prefix-simple-string.

;; The string-has-same-ith-character-as-simple-string-p tests in
;; make-menu-tree-of-names-from-directory (and in add-to-directory-of-names-1 and
;; delete-from-directory-of-names-1) include name length tests which are, in
;; many cases, unnecessary.  Also, at least the first of these tests in the
;; loops is redundant.  Consider revising code to take advantage of this
;; information.




;;; `flatten-first-n-distinct-elements-of-menu-tree'

(defvar flattened-menu-reverse nil)
(defvar flattened-menu-maximum-remaining-elements 0)

(defun-simple flatten-first-n-distinct-elements-of-menu-tree (directory-of-names)
  (if (listp directory-of-names)
      (loop for dir in directory-of-names
            always (flatten-first-n-distinct-elements-of-menu-tree dir))
      (or (memq directory-of-names flattened-menu-reverse)
          (when (<=f 0 (decff flattened-menu-maximum-remaining-elements))
            (grammar-push directory-of-names flattened-menu-reverse)
            t))))



;;; `make-menu-of-names-unless-too-many?' - obtains the directory of names for a
;;; category symbol, and flattens it, returning (a) the whole list if it's
;;; length is less than maximum-length- of-menu; (b) the "first"
;;; maximum-length-of-menu members of the list if the list is too long but
;;; return-list-if-too-long-p is t; (c) or the constant value
;;; menu-too-many-instances if return-list-if-too-long-p is nil.
;;;    We used to use some heuristics to tell which categories to look up.
;;; We are no longer doing that, and now look up every category every time
;;; we reprompt.

(defun-simple make-menu-of-names-unless-too-many?
    (category-symbol prefix-simple-string?
		     maximum-length-of-menu
		     return-partial-list-p)
  (let* ((directory-of-names (directory-of-names category-symbol))
	 (directory-tree-of-names
	   (if (and directory-of-names prefix-simple-string?)
	       (make-menu-tree-of-names-from-directory
		 directory-of-names
		 (string-for-first-name-in-directory directory-of-names)
		 0 prefix-simple-string?
		 (text-string-length prefix-simple-string?))
	       directory-of-names))
	 (flattened-menu-maximum-remaining-elements maximum-length-of-menu)
	 (flattened-menu-reverse nil)
	 (few-enough-choices-p 
	   (flatten-first-n-distinct-elements-of-menu-tree
	     directory-tree-of-names)))
    (cond
      ((or few-enough-choices-p return-partial-list-p)
       flattened-menu-reverse)
      (t
       (reclaim-grammar-list flattened-menu-reverse)
       menu-too-many-instances))))



;;; `make-menu-of-names-from-directory-if-few-enough'

(defun-simple make-menu-of-names-from-directory-if-few-enough
       (category-symbol prefix-simple-string? maximum-length-of-menu)
  (cond
    ((>=f 0 maximum-length-of-menu)
     menu-too-many-instances)
    (t
     (make-menu-of-names-unless-too-many?
       category-symbol prefix-simple-string? maximum-length-of-menu nil))))



;;; `Make-menu-of-names-from-directory' returns a token menu consisting of
;;; names from the directory of names for category-symbol, restricted to
;;; begin with the sequence of characters in prefix-simple-string? (according
;;; to char=) when prefix-simple-string? is specified.  If category-symbol has
;;; no directory of names, nil will be returned.

;;; A returned token menu will be a menu content structure, will be in
;;; alphabetical order, will contain qualifying names up to a maximum of
;;; maximum-length-of-menu, and will not contain duplicates (except possibly
;;; for strings that are equal but not eq).  (See also make-menu-content-
;;; structure-for-token-position in module PARSE.)  Also returned in this
;;; case, as a second value, is either the length of the token menu or nil
;;; to indicate that the token menu had to be truncated to the first maximum-
;;; length-of-menu names.



(defun-simple make-menu-of-names-from-directory (category-symbol
						  prefix-simple-string?)
  (nreverse
    (make-menu-of-names-unless-too-many?
      category-symbol prefix-simple-string? maximum-length-of-menu-of-names t)))

;; Make-menu-of-names-from-directory is not coded for maximum speed.  Consider
;; revising it a la add-to-directory-of-names for greater speed.

;; "Make-menu-of-names-from-directory" should have had an "-if-any" suffix.





;;;; Names for Frames



;;; A `name' is a symbol other than nil.  (The name whose print name is NIL can
;;; be expressed as :NIL, i.e., the symbol whose print name is "NIL" interned in
;;; the keyword package.)  A `namable-frame' (a block, at present) may have any
;;; number of names.  A `defined name' is a name that is the name of some
;;; namable frame.

;;; The `frame-or-frames-with-this-name' property of a name specifies the
;;; frames, if any, that have this name.  When there is only one such frame, the
;;; value of this property is just the frame.  When there are more than one, the
;;; value is a gensym list of them.  A defined name has a non-nil value for this
;;; property.  This property is kb-specific, and since its value is determined
;;; entirely by the slot putter for name-or-names-for-frame, it need not be
;;; represented explicitly in a saved kb.

(def-kb-specific-property-name frame-or-frames-with-this-name
    reclaim-gensym-list-if-list)



;;; The macro `do-name-or-names' iterates over a name-or-names-for-frame slot
;;; value, executing body once with name bound to each of the names in the
;;; NAME-OR-NAMES argument.  Recall that name-or-names can either be a name
;;; symbol, i.e., a non-nil symbol, or a possibly empty list of name symbols.

;;; The macro `do-frame-or-frames' iterates over a
;;; frame-or-frames-with-this-name property value, executing body once with
;;; frame bound to each of the frames in the FRAME-OR-FRAMES argument.  Recall
;;; that frame-or-frames can either be a frame or a possibly empty list of
;;; frames.

(defmacro do-name-or-names ((name-var name-or-names) &body body)
  `(do-atom-or-list-of-atoms (,name-var ,name-or-names) . ,body))

(defmacro do-frame-or-frames ((frame-var frame-or-frames) &body body)
  `(do-atom-or-list-of-atoms (,frame-var ,frame-or-frames) . ,body))



;;; The function `name-or-names-same-p' compares its args, set-a and set-b,
;;; which are possible values for the name-or-names-for-frame slot, as sets and
;;; returns true (non-nil) if they are the same when each is regarded as a set.
;;; This is the recommended way to compare two values for the
;;; name-or-names-for-frame slot (= NAMES attribute) for being "the same".
;;;
;;; Names-1 and names-2 should be a possible value for the
;;; name-or-names-for-frame slot, i.e., an atomic name symbol or a list of
;;; symbols, and the symbol NIL is regarded as an empty list, not as the name
;;; NIL.  (The actual name NIL can be expressed as :NIL, i.e., the symbol whose
;;; print name is "NIL" interned in the keyword package.)
;;;
;;; Note that the arguments NEED NOT be normalized in any way, e.g., to have any
;;; particular ordering, duplicates eliminated, singleton lists converted to
;;; atoms.
;;;
;;; Examples:
;;;  (name-or-names-same-p nil nil) => true
;;;  (name-or-names-same-p 'frank nil) => nil
;;;  (name-or-names-same-p 'frank 'frank) => true
;;;  (name-or-names-same-p 'frank '(frank)) => true
;;;  (name-or-names-same-p 'frank 'bob) => nil
;;;  (name-or-names-same-p 'frank '(tim frank jim)) => nil
;;;  (name-or-names-same-p 'frank '(frank frank frank)) => true
;;;  (name-or-names-same-p '(frank jim) '(jim frank)) => true
;;;  (name-or-names-same-p '(frank jim) '(jim frank bob)) => nil

(defun name-or-names-same-p (set-a set-b)
  (cond
    ((and set-a (atom set-a))
     (cond
       ((and set-b (atom set-b))
	(eq set-a set-b))
       (t (and set-b (loop for name-b in set-b always (eq name-b set-a))))))
    ((and set-b (atom set-b))
     (and set-a (loop for name-a in set-a always (eq name-a set-b))))
    (t (and (loop for name-a in set-a always (memq name-a set-b))
	    (loop for name-b in set-b always (memq name-b set-a))))))

;;; The function `name-or-names-like-p' use `thereis' instead of `always' as in
;;; `name-or-names-same-p', in this ways, if there's anything common between
;;; to name-or-names, the result will be true. It's specially useful for
;;; connection-posts.

(defun name-or-names-like-p (set-a set-b)
  (cond
    ((and set-a (atom set-a))
     (cond
       ((and set-b (atom set-b))
	(eq set-a set-b))
       (t (and set-b (loop for name-b in set-b thereis (eq name-b set-a))))))
    ((and set-b (atom set-b))
     (and set-a (loop for name-a in set-a thereis (eq name-a set-b))))
    ;; there's no need to have the other loop: they're symmetry.
    (t
     (loop for name-a in set-a thereis (memq name-a set-b)))))

;; Note that this is efficient enough for small lists, but would not be for
;; large lists.  The sets of names are almost always singletons.  A good-sized
;; list of names -- in the 100's or 1000's -- is practically inconceivable,
;; though G2 does not actually place any restrictions on the number of names.





;;; Get-primary-name-for-frame-if-any returns the `primary name' for namable
;;; frame (the first one of its names), if any, or else nil.

(defun get-primary-name-for-frame-if-any (namable-frame)
  (let ((name-or-names-for-frame (name-or-names-for-frame namable-frame)))
    (if (atom name-or-names-for-frame)
	name-or-names-for-frame
	(car name-or-names-for-frame))))



;;; Get-secondary-name-for-frame-if-any returns the `secondary name' for
;;; namable-frame (the second one of its names), if any, or else nil.

(defun get-secondary-name-for-frame-if-any (namable-frame)
  (let ((name-or-names-for-frame (name-or-names-for-frame namable-frame)))
    (if (consp name-or-names-for-frame) (second name-or-names-for-frame))))


;;; Get-unique-name-for-frame-if-any returns for the namable-frame the first
;;; name in its list of names which names this and only this frame.

(defun get-unique-name-for-frame-if-any (namable-frame)
  (do-name-or-names (name (name-or-names-for-frame namable-frame))
    (let ((frame-or-frames-with-this-name (frame-or-frames-with-this-name-macro name)))
      (when (or (not (consp frame-or-frames-with-this-name))
		(null (cdr frame-or-frames-with-this-name)))
	(return name)))))



;;; Get-instance-with-name-if-any returns the first frame of class class to have
;;; been given the name name.

;;; Get-instance-with-name-that-satisfies-predicate-if-any returns the first
;;; frame of class class to have been given the name name that satisfies
;;; one-arg-predicate.

(defun get-instance-with-name-if-any (class? name)
  (let ((frame-or-frames-with-this-name
	  (frame-or-frames-with-this-name-macro name)))
    (if frame-or-frames-with-this-name
	(if (atom frame-or-frames-with-this-name)
	    (when (or (null class?)
		      (if (eq class? 'item)
			  (frame-of-class-p frame-or-frames-with-this-name 'item)
			  (frame-of-class-p frame-or-frames-with-this-name class?)))
	      frame-or-frames-with-this-name)
	    (loop for frame in frame-or-frames-with-this-name
		  when (or (null class?)
			   (if (eq class? 'item)
			       (frame-of-class-p frame 'item)
			       (frame-of-class-p frame class?)))
		    return frame)))))


;;; Same as `get-instance-with-name-if-any' but with runtime faction check
;;; `get-instance-with-name-that-satisfies-predicate-if-any' seems to be
;;; commented out in '89
#+mtg2
(defun get-faction-instance-with-name-if-any (faction class? name)
  (let ((frame-or-frames-with-this-name
	  (frame-or-frames-with-this-name-macro name)))
    (if frame-or-frames-with-this-name
	(if (atom frame-or-frames-with-this-name)
	    (when (and
		   (or (null class?)
		       (if (eq class? 'item)
			   (frame-of-class-p
			    frame-or-frames-with-this-name 'item)
			   (frame-of-class-p
			    frame-or-frames-with-this-name class?)))
		   (check-faction faction frame-or-frames-with-this-name))
	      frame-or-frames-with-this-name)
	    (loop for frame in frame-or-frames-with-this-name
	       when (and
		     (or (null class?)
			 (if (eq class? 'item)
			     (frame-of-class-p frame 'item)
			     (frame-of-class-p frame class?)))
		     (check-faction faction frame))
	       return frame)))))



;; In addition to these, other functions that map from a name into a frame or frames
;; should be defined where they are used, since there are various use-dependent ways of
;; verifying assumptions and dealing with ambiguities.

;; Macro versions of thes functions would be sizable, especially since the expansions of
;; of-class-p are sizable.



(def-slot-putter name-or-names-for-frame
    (namable-frame name-or-names-for-frame initializing?)
  (unless (atom name-or-names-for-frame) ; see Note 1 (MHD/ML 5/23/91)
    (if (null (cdr name-or-names-for-frame))
	(let ((car-name (first name-or-names-for-frame)))
	  (reclaim-slot-value-list name-or-names-for-frame)
	  (setq name-or-names-for-frame car-name))
	(setq name-or-names-for-frame
	      (delete-duplicates-from-list
		name-or-names-for-frame
		'reclaim-slot-value-cons-function))))  
  (let ((old-names
	  (if initializing?
	      '()
	      (name-or-names-for-frame namable-frame))))    
    (setf (name-or-names-for-frame namable-frame) name-or-names-for-frame)    
    (when (not (name-or-names-same-p old-names name-or-names-for-frame))
      (funcall-method 'note-name-change namable-frame old-names initializing?))
    name-or-names-for-frame))

;; Note 1: there are KBs saved in 2.0 or 2.1, that have a list of a single name.
;; This argument modifying code reduces that to a symbol.  It also removes
;; duplicates, which it has always done, since the slot compiler does not remove
;; duplicates.  (MHD/ML 5/23/91)




;;; `Note-name-change' is a class method defined for all blocks and may be
;;; further refined for subclasses.  It is called with the instance and two
;;; additional arguments: old-names, a list of the names previously set as the
;;; value of the slot, or nil in the case of initializing the slot, and
;;; initializing-p, same as the the slot putter for name-or-names-for-frame's
;;; initialization-case variable, which per def-slot-putter's documentation, may
;;; make certain initializations inappropriate.
;;;
;;; The method is called from the slot putter for name-or-names-for-frame AFTER
;;; the new set of names has been set into the slot, and only when the set of
;;; names is changing.  I.e., the if the old list of names is A, B, and the new
;;; list of names is B, A, this method will NOT be called.

;;; The method defined for class BLOCK supplies essential behavior: it will
;;; add/remove frame from its various registrations with respect to the old and
;;; new set of names.  This includes, in particular, updating the
;;; frame-or-frames-with-this-name KB property of each name symbol, and also
;;; updating frame notes about multiple instances with the same name and similar
;;; types of conflicts.

;;; Other classes may define their own special behavior, but should always call
;;; the superior method to get the basic block behavior.  I.e., implementations
;;; for a given class X are required to do (funcall-superior-method X old-names
;;; initializing-p) in addition to their own name change handling. Normally the
;;; call to the superior method is done first, at the beginning of the body,
;;; unless the method has a special need to do some things earlier, i.e., based
;;; on knowledge of what some superior, especially BLOCK, does in its method.

;;; The list structure of the argument old-names belongs to the caller, and
;;; should never be incorporated into any nontransient data structures or in any
;;; way mutated or reclaimed by the method.

(def-generic-method note-name-change (block old-names initializing-p))

(def-class-method note-name-change (block old-names initializing-p)
  (declare (ignore initializing-p))
  (update-as-frame-with-name
    block old-names (name-or-names-for-frame block)))





;;; Update-as-frame-with-name performs the task of updating the
;;; frame-or-frames-with-this-name KB property of each name symbol, and also
;;; updating the frame notes about multiple instances with the same name and
;;; similar types of conflicts.  It is to be invoked by the
;;; note-name-change method of the class BLOCK.
;;;
;;; This does not reclaim, incorporate, or mutate the lists passed in.

(defun update-as-frame-with-name (namable-frame old-names new-names)  
  (cond
    ((if old-names (atom old-names))
     (cond
       ((if new-names (atom new-names))
	(unless (eq old-names new-names)
	  (delete-as-frame-with-name namable-frame old-names)
	  (add-as-frame-with-name namable-frame new-names)))
       (t (unless (memq old-names new-names)
	    (delete-as-frame-with-name namable-frame old-names))
	  (loop for name in new-names
		unless (eq name old-names)
		  do (add-as-frame-with-name namable-frame name)))))
    ((if new-names (atom new-names))
     (loop for old-name in old-names
	   unless (eq old-name new-names)
	     do (delete-as-frame-with-name namable-frame old-name))
     (unless (memq new-names old-names)
       (add-as-frame-with-name namable-frame new-names)))
    (t (loop for old-name in old-names
	     unless (memq old-name new-names)
	       do (delete-as-frame-with-name namable-frame old-name))
       (loop for name in new-names
	     unless (memq name old-names)
	       do (add-as-frame-with-name namable-frame name)))))



;;; The function `change-primary-name-of-frame' changes the first name of the
;;; frame to its argument without altering the remaining names.  The argument
;;; becomes the primary name.  It may be used to remove a primary name by giving
;;; it a null argument, but this will do nothing if there is a secondary name.

(defun change-primary-name-of-frame (namable-frame new-name initializing?)
  (let ((names (name-or-names-for-frame namable-frame))
	new-value)
    (cond
      ((null new-name)
       (if (symbolp names)
	   (if initializing?
	       (put-name-or-names-for-frame namable-frame (car names) initializing?)
	       (change-slot-value
		 namable-frame
		 'name-or-names-for-frame
		 nil))))
      
      ;; If already a name, do nothing.
      ((if (consp names) (memq new-name names) (eq new-name names))
       names)

      (t
       (setq new-value
	     (if (atom names)
		 new-name
		 (slot-value-cons
		   new-name
		   (copy-list-using-slot-value-conses (cdr names)))))
       (if initializing?
	   (put-name-or-names-for-frame namable-frame new-value initializing?)

	   (change-slot-value
	     namable-frame
	     'name-or-names-for-frame
	     new-value))))))



;;; (change-secondary-name-of-frame (namable-frame new-name)
;;; changes the second name of the frame to its argument without
;;; altering the remaining names. If there is not at least one name
;;; already, it does nothing. If new-name is nil, all but the primary
;;; name of the frame are removed.

(defun change-secondary-name-of-frame (namable-frame new-name initializing?)
  (let ((names (name-or-names-for-frame namable-frame))
	new-value)
    (cond
      ((null names) nil)

      ;; If already a name, do nothing.
      ((if (consp names) (memq new-name names) (eq new-name names)))

      ((null new-name)
       (if (consp names)
	   (if initializing?
	       (put-name-or-names-for-frame namable-frame (car names) initializing?)
	       (change-slot-value
		 namable-frame
		 'name-or-names-for-frame
		 (car names)))))

      (t
       (setq new-value
	     (if (atom names)
		 (slot-value-list names new-name)
		 (slot-value-cons
		   (car names)
		   (slot-value-cons
		     new-name
		     (cddr names)))))
       (if initializing?
	   (put-name-or-names-for-frame namable-frame new-value initializing?)
	   (change-slot-value
	     namable-frame
	     'name-or-names-for-frame
	     new-value))))))

;; If the class or some superclass of namable-frame has a class-specific-
;; definition-property-name property, then properties should be maintained on
;; each of the name-or-names-for-frame, with that property name and
;; namable-frame as the value!

;; Reclaim conses in old values of name-or-names-for-frame!

;; Consider reflecting a subworkspace name change in its parent.  (At present,
;; an entity name change is reflected in its subworkspace, if there is a
;; subworkspace and either it has the same primary name as its parent or neither
;; has a name).

;; Note that this could be invoked during the loading of module TABLES, if
;; global default format frames with names are created there.



;;; Make-new-name-for-frame returns a symbol not currently used as a name for a
;;; frame or class and not formerly used as a name of a built-in class.  This
;;; symbol will be either the concatenation of part-1, part-2, and part-3, if
;;; available, OR part-1, part-2, and part-3 suffixed by -1, -2, or the like,
;;; the first such symbol that is available.  Part-1, part-2, and part-3 may be
;;; symbols and/or strings, where part-2 and part-3 are optional.

(defun make-new-name-for-frame (part-1 &optional (part-2 "") (part-3 ""))
  (loop as i from 0
	as name = (intern-text-string
		    (if (=f i 0)
			(tformat-text-string "~A~A~A" part-1 part-2 part-3)
			(tformat-text-string "~A~A~A-~D" part-1 part-2 part-3 i)))
	when (and (null (frame-or-frames-with-this-name name))
		  (null (class-description name))
		  (null (substitute-class name)))
	  return name))



;;; Subworkspace-is-named-like-its-parent-p is true if subworkspace has a parent such
;;; that both have no name or both have the same primary name.

(defun subworkspace-is-named-like-its-parent-p (subworkspace)
  (and (parent-of-subworkspace? subworkspace)
       (eq (get-primary-name-for-frame-if-any (parent-of-subworkspace? subworkspace))
	   (get-primary-name-for-frame-if-any subworkspace))))




;;; `Add-as-frame-with-name' is invoked when name is added to
;;; (name-or-names-for-frame namable-frame).  Namable-frame must not yet be
;;; included in (frame-or-frames-with-this-name name).

(defun add-as-frame-with-name (namable-frame name)
  ;; Retract note, if any; this is needed for the initializing?
  ;; (i.e., kb-loading) case (MHD 2/14/92)
  (delete-from-frame-note-particulars-list
    name 'non-unique-names namable-frame)

  (let* ((old-frame-or-frames-with-this-name	
	   (frame-or-frames-with-this-name name))
	 ;; I added a test to check whether the namable-frame is already in the
	 ;; old value because the initializing code for the relation-name and
	 ;; inverse-of-relation slot putters for relations was placing
	 ;; duplicate frames on the list causing erroneous frame notes, and,
	 ;; after frame deletions, allowing recycled frames in the list which
	 ;; resulted in crashes especially during kb clearing.  (5/17/95 GHW)
	 (new-frame-or-frames-with-this-name
	   (cond ((null old-frame-or-frames-with-this-name)
		  namable-frame)
		 ((atom old-frame-or-frames-with-this-name)
		  (if (eq namable-frame old-frame-or-frames-with-this-name)
		      old-frame-or-frames-with-this-name
		      (gensym-list
			old-frame-or-frames-with-this-name namable-frame)))
		 (t
		  (if (memq namable-frame old-frame-or-frames-with-this-name)
		      old-frame-or-frames-with-this-name
		      (nconc old-frame-or-frames-with-this-name
			     (gensym-list namable-frame))))))) 

    (add-or-delete-class-or-name-for-frame namable-frame name nil)

    (if (frame-of-class-p namable-frame 'authorized-user)
	(maintain-authorized-user namable-frame))

    (setf (frame-or-frames-with-this-name name)
	  new-frame-or-frames-with-this-name)
    
    (when (and (consp new-frame-or-frames-with-this-name)
	       (cdr new-frame-or-frames-with-this-name))
      (loop for frame in new-frame-or-frames-with-this-name
	    ;; Delete and add are used here because the message specifies
	    ;; the number of duplicates that exist, which keeps changing.
	    do
	(delete-from-frame-note-particulars-list
	  name 'non-unique-names frame)
	;; Do not add this note to connection-post or system-table
	;; instances. Non-unique names are considered proper.
	(unless (or (frame-of-class-p frame 'connection-post)
		    (frame-of-class-p frame 'system-table)
		    (frame-of-class-p frame 'method)
		    (get-slot-feature-if-any
		      (class frame)
		      'name-or-names-for-frame
		      'local-name-or-names))
	  (add-to-frame-note-particulars-list-if-necessary
	    name 'non-unique-names frame))))

    (analyze-compiled-items-for-consistency name)
    (install-item-in-model-if-models-used namable-frame)))

;; Note that the posting of non-unique-names notes must be done after the change
;; to (frame-or-frames-with-this-name name), for the frame note writer to work
;; right.



;;; `Delete-as-frame-with-name' is invoked when NAME is deleted from
;;; (name-or-names-for-frame namable-frame).  Namable-frame is assumed to be
;;; included in (frame-or-frames-with-this-name name).

(defun delete-as-frame-with-name (namable-frame name)
  (let ((frame-or-frames-with-this-name (frame-or-frames-with-this-name name)))

    (add-or-delete-class-or-name-for-frame namable-frame name t)

    (cond
      ((eq frame-or-frames-with-this-name namable-frame)
       (setq frame-or-frames-with-this-name nil))
      ((and (not (atom frame-or-frames-with-this-name))	 ; should always succeed
	    (memq namable-frame frame-or-frames-with-this-name))
       (loop for frame in frame-or-frames-with-this-name
	     do (delete-from-frame-note-particulars-list
		  name 'non-unique-names frame))
       (cond
	 ((null (cddr frame-or-frames-with-this-name))
	  (setq frame-or-frames-with-this-name
		(prog1
		  (if (eq (first frame-or-frames-with-this-name)
			  namable-frame)
		      (second frame-or-frames-with-this-name)
		      (first frame-or-frames-with-this-name))
		  (reclaim-gensym-list frame-or-frames-with-this-name))))
	 (t (setq frame-or-frames-with-this-name
		  (delete-gensym-element
		    namable-frame frame-or-frames-with-this-name))
	    (if (cdr frame-or-frames-with-this-name)
		(loop for frame in frame-or-frames-with-this-name
		      unless (or (frame-of-class-p frame 'connection-post)
				 (frame-of-class-p frame 'system-table)
				 (frame-of-class-p frame 'method))
		      do (add-to-frame-note-particulars-list-if-necessary
			   name 'non-unique-names frame)))))))
    (setf (frame-or-frames-with-this-name name)
	  frame-or-frames-with-this-name)

    (analyze-compiled-items-for-consistency name)
    (install-item-in-model-if-models-used namable-frame)))




;;; `ensure-named-frame-is-first-fetched' makes namable-frame be at the front
;;; of (frame-or-frames-with-this-name name), where name is each name in
;;; (name-or-names-for-frame namable-frame).

(defun ensure-named-frame-is-first-fetched (namable-frame)
  (do-name-or-names (name (name-or-names-for-frame namable-frame))
    (let ((frame-or-frames-with-this-name
	    (frame-or-frames-with-this-name name)))
      (unless (or (atom frame-or-frames-with-this-name)
		  (eq (car frame-or-frames-with-this-name) namable-frame))
	(loop for l-trailer = frame-or-frames-with-this-name then l
	      as l on (cdr frame-or-frames-with-this-name)	; end test for safety
	      when (eq (car l) namable-frame)
		do (setf (cdr l-trailer) (cdr l))
		   (setf (cdr l) frame-or-frames-with-this-name)
		   (setf (frame-or-frames-with-this-name name)
			 l)
		   (return nil))))))

;; This is used only for installing system tables at present.  (MHD 6/10/92)




(def-slot-value-reclaimer name-or-names-for-frame (name-or-names frame)
  (declare (ignore name-or-names))
;;  GENSYMCID-1162: Inspect command doesn't suggest names for some items
;;
;;  Next two lines are commented to avoid twice remove names from
;;  names directory. change-slot-value will finally call slot putter for
;;  name-or-names-for-frame -> note-name-change -> update-as-frame-with-name
;;  -> delete-as-frame-with-name. So next deletion is redundant. --Fei Liu
#|
  (do-name-or-names (name name-or-names)
    (delete-as-frame-with-name frame name))
|#
  (change-slot-value frame 'name-or-names-for-frame nil))

;; Unless the slot value reclaimer for frame-representations is invoked before
;; this one, this one might do unnecessary work, e.g., it might update an
;; about-to-be-deleted attributes table.  Actually, it would suffice here to
;; just invoke the slot putter for name-or-names-for-frame with nil and then
;; call reclaim-slot-value on the value, if the value is a list!



;;; `Non-unique-names' is a type of note, the particulars of which is a list of
;;; one or more symbols.  When there is more than one frame with the same name,
;;; excluding any subworkspace whose primary name is the same as that of its
;;; parent, that name appears in the particulars list of a non-unique-names note
;;; on each such frame.

(def-frame-note-writer non-unique-names (non-unique-names)
  (twrite-string "this is one of ")
  (loop as (non-unique-name . rest-of-names)
	   = non-unique-names
	   then rest-of-names
	do (cond
	     ((atom (frame-or-frames-with-this-name non-unique-name))
	      (twrite-string "a number of renamed items")) ; BUG COVER-UP; REMOVE LATER!
	     (t (twrite (length
			 (frame-or-frames-with-this-name non-unique-name)))
		(twrite-string " distinct items named ")
		(twrite non-unique-name)))	; use format t here?
	   (if (null rest-of-names)
	       (return nil))			; arbitrary value
	   (twrite-string " and ")))

;; Consider refining the text of this note to distinguish ambiguities from cases
;; where a single object is represented by more than one frame with the same
;; name.

;; Consider writing the names in upper case.



;; ;;; The slot named `name-or-names-for-frame' is the quintessential namelike slot.
;; ;;; It is therefore declared namelike-slot-p.
;; 
;; (declare-namelike-slot name-or-names-for-frame)
;;
;; -- Now done with a namelike-slot feature in the slot declaration. (MHD 5/14/00)






;;;; Changing Slot Values and/or Updating their Representations



;;; `Change-slot-value' changes the value of the slot-name slot of frame, or the
;;; component thereof designated by slot-component-name? and
;;; slot-component-indicator?, if specified, to new-value.  (There is an
;;; exception mentioned below.)  If there is a slot putter it is allowed to
;;; update the slot value.  Change-slot-value signals an error if the frame has
;;; no slot-name slot.  The stored value is returned.

;;; Representations of the frame are updated, e.g. table, name-box, or top-
;;; bar-of-image-plane.  Only a slot named name-or-names-for-frame may have a
;;; name box and/or top-bar-of-image-plane representation.  In addition, slots
;;; with a namelike-slot feature trigger update-frame-name-references on
;;; frame and the appropriate subframes, to all appropriate levels.

;;; The old value of the slot is reclaimed, using reclaim-slot-value, unless
;;; 
;;;  1. the old value is the same as the new value,
;;;  2. the old value is the same as the slot's default value,
;;;  3. the slot putter indicates that it reclaimed the value, or
;;;  4. the slot value is a number, or nil, or
;;;  5. the slot putter being used is PUT-ATTRIBUTE-VALUE, used
;;;     for user-defined attributes (and maybe other slots)
;;;     
;;; The slot putter indicates that it reclaimed the old value by returning
;;; a second value which is non-nil.

;;; Most people are surprised to discover that change-slot-value does not call
;;; the slot value reclaimer.  Really.  This is because the reclaim is done
;;; after the slot putter has already installed the new value and the reclaimer
;;; is likely to "clean up" the entire slot.  Any slot that is made with conses
;;; other than slot-value-conses must have its slot putter reclaim the old
;;; value.

;;; The exception to this usual behavior happens when the new-value is the value
;;; of special variable just-update-representations-of-slot-value.  In this case
;;; change-slot-value just updates any table, name-box, or top-bar-of-image-plane 
;;; representations to reflect the current value of the slot.  In this case, of
;;; course, the slot is not updated.  Update-representations-of-slot-value is
;;; the usual way to invoke this service.  The return value is undefined in 
;;; this case.

;;; Changing a slot value is somewhat expensive, but must be used when the new
;;; value might affect the installation of the frame, when there might be
;;; representions of the slot value, or when the frame timestamp and authors
;;; should be updated for the change.
					   
;;; The macro `change-slot-description-value-without-updating-representations'
;;; is the one interface that all of the calls to change-slot-value and friends
;;; end up funnelling through in the case where the value is really to be
;;; changed. (It's not called in the just-updating-frame-representations case.)
;;; It is called with both a slot description and the
;;; pretty-slot-name/defining-class pair, all args non-optional.  This in fact
;;; does not handle the updating of representations; some of the the callers do
;;; that via their use of the macro with-updates-to-representations.

(defun-substitution-macro change-slot-description-value-without-updating-representations
    (frame slot-description new-value
	   pretty-slot-name defining-class
	   slot-component-name? slot-component-indicator? do-not-reclaim-old-value-override?)
  (let* (old-value (do-not-reclaim-old-value? nil))
    (prog1
	(cond
	  ((or slot-component-name? slot-component-indicator?)
	   (multiple-value-setq (old-value do-not-reclaim-old-value?)
	     (get-slot-component-value
	       frame pretty-slot-name defining-class
	       slot-component-name? slot-component-indicator?))
	   (unless (or do-not-note-permanent-changes-p
		       (slot-value-equal-p old-value new-value))
	     (note-permanent-change-to-component
	       frame slot-description
	       slot-component-name? slot-component-indicator?))
	   (let ((slot-component-putter?
		   (get-slot-component-putter-if-any
		     frame pretty-slot-name defining-class
		     slot-component-name? slot-component-indicator?)))
	     (cond
	       (slot-component-putter?
		(multiple-value-bind (value dont-reclaim?)
		    (funcall-simple-multi-valued-compiled-function 
		      slot-component-putter? frame
		      pretty-slot-name defining-class
		      slot-component-indicator? new-value nil)
		  (when dont-reclaim? (setq do-not-reclaim-old-value? t))
		  value))
	       (t	    
		(set-slot-component-value
		  frame pretty-slot-name defining-class
		  slot-component-name? slot-component-indicator?
		  new-value)))))
	  (t
	   (let ((slot-putter? (get-slot-description-putter-if-any slot-description)))
	     (cond
	       ((eq slot-putter? 'put-attribute-value)
		;; Put-attribute-value reclaims slot values, so we always
		;; set do-not-reclaim-old-value? to true, and we don't need
		;; to set old-value, since it won't be looked at.
		(setq do-not-reclaim-old-value? t)
		(put-attribute-description-value
		  frame slot-description new-value do-not-reclaim-old-value-override?))
	       (t
		(setq old-value
		      (get-slot-description-value-macro frame slot-description))
		(unless (or do-not-note-permanent-changes-p
			    (slot-value-equal-p old-value new-value))
		  (note-permanent-change frame slot-description))
		(cond
		  (slot-putter?
		   
		   (multiple-value-setq-some (nil do-not-reclaim-old-value?)
		       (funcall-simple-multi-valued-compiled-function 
			 slot-putter? frame new-value nil)))
		  (t
		   (set-slot-description-value
		     frame slot-description new-value))))))))
      (when (and (not do-not-reclaim-old-value?)
		 (not do-not-reclaim-old-value-override?)
		 old-value
		 (not (eq new-value old-value))
		 (not (fixnump old-value))
		 (or slot-component-name?
		     (not (eq old-value
			      (slot-init-form slot-description)))))
	(reclaim-slot-value old-value)))))




(defun change-slot-value
    (frame slot-name new-value &optional class-if-specific?
	   slot-component-name? slot-component-indicator?)
  (change-slot-description-value-function
    frame
    (or (get-slot-description-of-frame slot-name frame class-if-specific?)
	#+development
	(cerror "Continue with bad slot description (nil) as in production."
		"There's no ~a~a~a slot for ~s."
		(or class-if-specific? "")
		(if class-if-specific? "::" "")
		slot-name
		frame))
    new-value
    slot-component-name? slot-component-indicator?))




;;; The macro `change-slot-description-value' and its related function are the
;;; equivalent of change-slot-value above, but instead of taking a
;;; pretty-slot-name and a class-if-specific? qualifier as arguments, it takes a
;;; slot description.

(defmacro change-slot-description-value
    (frame slot-description new-value
	   &optional slot-component-name? slot-component-indicator?)
  `(change-slot-description-value-function
     ,frame ,slot-description ,new-value
     ,slot-component-name? ,slot-component-indicator?))

(defun-simple change-slot-description-value-function
    (frame slot-description new-value
	   slot-component-name? slot-component-indicator?)
  (with-updates-to-representations
      (frame slot-description slot-component-name? slot-component-indicator?)
    
    (unless (eq new-value just-update-representations-of-slot-value)
      (change-slot-description-value-without-updating-representations
	frame slot-description new-value
	(pretty-slot-name slot-description)
	(defining-class slot-description)
	slot-component-name? slot-component-indicator? nil))))
  


;;; `Update-representations-of-slot-value' updates any table or name box representations
;;; there may be of the value of the slot-name slot of frame, to reflect the current value.

(defun update-representations-of-slot-value
    (frame slot-name
	   &optional defining-class?
	   slot-component-name? slot-component-indicator?)
  (when (or (frame-representations frame)
	    (eq slot-name 'name-or-names-for-frame))
    (change-slot-description-value
      frame
      (if (eq slot-name 'class)
	  pseudo-class-slot-description
	  (get-slot-description-of-frame slot-name frame defining-class?))
      just-update-representations-of-slot-value
      slot-component-name? slot-component-indicator?)))





;;; `Set-slot-value-and-update-representations' sets the slot-name slot of frame to
;;; new-value (without invoking any slot putter therefor or reclaiming the old value),
;;; and then updates any table or name box representations there may be for the slot.
;;; New-value is returned.

;; This function is currently called for system-defined slots only, so there
;; there is no need to add a defining class argument.  (ghw 10/14/93)

(defun set-slot-value-and-update-representations 
    (frame slot-name new-value
	   &optional defining-class?
	   slot-component-name? slot-component-indicator?)
  (with-updates-to-representations
      (frame (get-slot-description-of-frame slot-name frame defining-class?)
	     slot-component-name? slot-component-indicator?)
    (set-slot-value frame slot-name new-value defining-class?)))

;; Switched to use of the new macro, and the extra args for slot components.
;; (MHD 2/5/94)










;;;; Removing Blocks from Dragging Contexts



;;; Remove-block-being-deleted-as-block-being-dragged is to be called
;;; from delete-frame just before deleting a block.  It backs the
;;; block out of the data structures that handle dragging.  For the
;;; sake of speed, this macro does a fast, inline check to see if
;;; anything might have to be done with block at all (rather rare)
;;; before calling out to a subfunction that does most of the work.

(def-substitution-macro remove-block-being-deleted-as-block-being-dragged (block)
  (when (and (block-is-currently-being-dragged-p block)
	     (not (frame-of-class-p block 'workspace)))
    (remove-as-block-being-dragged block)))








;;;; Deleting Blocks 

;;; This section was introduced to disentangle frame deletion
;;; in the general case from G2 specific semantics which is pretty
;;; much wrapped up with the class BLOCK.






(def-system-variable items-deleted-since-load-or-save frames5 nil)
(def-system-variable items-deleted-since-load-or-save-tail frames5 nil)

(defun add-deleted-item-to-list (item frame?)
  (let ((frame-serial-number
	  (copy-frame-serial-number
	    (if frame?
	      (frame-serial-number item)
	      (frame-serial-number-for-connection-function item)))))
    (cond
      (items-deleted-since-load-or-save
       (setq items-deleted-since-load-or-save-tail
	     (setf (cdr items-deleted-since-load-or-save-tail)
		   (journal-list frame-serial-number))))
      (t (setq items-deleted-since-load-or-save
	       (setq items-deleted-since-load-or-save-tail
		     (journal-list frame-serial-number)))))))

(defun reclaim-items-deleted-since-load-or-save ()
  (loop for frame-serial-number in items-deleted-since-load-or-save-tail
	do (reclaim-frame-serial-number frame-serial-number))
  (reclaim-journal-list items-deleted-since-load-or-save)
  (setq items-deleted-since-load-or-save nil)
  (setq items-deleted-since-load-or-save-tail nil))







;;; `Note-deletion-of-block' must be called before deleting any permanent block.
;;; It is not an error to call it for other blocks.

;;; Permanent blocks: The block must be written within the recursive extent, and
;;; its inferiors added to the traversal state under the conditions noted for
;;; note-change-to-block.  Furthermore, the frame-serial-number must be put on a
;;; list of deleted blocks.  (This is needed for backups).

(defmacro note-deletion-of-block (block)
  `(when noting-changes-to-kb-p (note-deletion-of-block-1 ,block)))

(defun-void note-deletion-of-block-1 (block)
  (note-deletion-of-block-2 block))

;;; `do-block-specific-deletion-stuff' is a the piece of an earlier
;;; version of delete-frame that implements a large part of the
;;; g2-specific deletion semantics.

(defun do-block-specific-deletion-stuff (frame)

  #+mtg2
  (when (faction? frame) (unpropagate-faction-recursively frame))
  
  (remove-block-being-deleted-as-block-being-dragged frame)
  (remove-block-from-native-views frame)            ; TODO: Could use a frame-flag.
  (note-deletion-of-block-for-selection frame)
  (note-deletion-of-block frame)
  (cond
    ((superblock? frame)			    ; this case could be speeded up a bit
     (update-images-of-block frame 'delete nil)
     (remove-as-subblock-if-necessary frame))
    
    ((frame-of-class-p frame 'connection)	    ; connection-frames still need stuff done.
     (remove-as-subblock-if-necessary frame))
    
    ((frame-of-class-p frame 'workspace)
     (delete-image-planes-workspace-is-on frame)))
  
  (when (list-elements-for-item frame)
    ;; Remove the block from all g2-lists that it is a member of.
    (remove-element-from-all-g2-lists frame nil))
  
  (funcall-simple-method-if-any-macro 'deactivate-and-propagate frame nil) ; maybe always redundant
  
  (when (and (frame-of-class-p frame 'item)
	     (relation-instances frame))
    (cond (releasing-kb?
	   #+SymScale
	   (let ((old-tree (atomic-exchange (relation-instances frame) nil)))
	     (reclaim-relation-instances old-tree))
	   #-SymScale
	   (reclaim-relation-instances (relation-instances frame))
	   #-SymScale
	   (setf (relation-instances frame) nil))
	  (t
	   ;; Remove the item from all relations it takes part in.
	   (remove-transient-relation-instances frame nil)
	   (when reading-kb-p
	     (setq blocks-with-relation-instances-from-kb-read
		   (delete-gensym-element
		     frame
		     blocks-with-relation-instances-from-kb-read))))))

  (retract-consistency-analysis-if-allowed frame)
  (with-immutable-consistency-analysis (frame)
    (funcall-simple-method-if-any-macro 'cleanup frame)))



;;;; KB-workspaces



;;; A `kb-workspace' is graphically a block on which one can place
;;; various statements, entities, blocks, etc. A kb-workspace is
;;; either active or inactive at any time. If a kb-workspace is
;;; inactive, none of the things placed on it can behave in an active
;;; way. Rules cannot be invoked, variables cannot supply values, etc.

;;; Kb-workspaces are a sub-class of workspaces. 

 
;;; A `top level' kb-workspace is one that has not parent, i.e., whose
;;; parent-of-subworkspace?  slot is NIL.  it is at the top of the "workspace
;;; hierarchy".  Otherwise a kb-workspace is a `subworkspace'.  

;;; A top-level kb-workspace is activated when the G2 is started. Subworkspaces
;;; are activated when their parent-of-subworkspace? is activated, except for
;;; procedure bodies where explicit and perhaps instance specific activation is used.




(def-class (kb-workspace (item workspace)
			 (foundation-class kb-workspace) define-predicate)
  ;; Bogus name. Part of tamper mechanism.
  (display-stack-priority	; intentionally misleading name -- for authorization
    nil vector-slot system save (attribute-export-comment "Bogus name. Part of tamper mechanism. Internal."))
  (initial-rule-count nil vector-slot system)
  (module-this-is-part-of?
    nil lookup-slot system user-overridable (type module-name?)
    (attribute-export-comment "Currently aliased to module-assignment. Change alias to just module ?"))
  (kb-workspace-initial-width
   700 lookup-slot system save (type positive-integer)
   user-overridable do-not-put-in-attribute-tables
   (attribute-export-comment "export as initial-workspace-width, (type positive-integer), writable = false"))
  (kb-workspace-initial-height 500 lookup-slot system save user-overridable
                                (type positive-integer)
				do-not-put-in-attribute-tables
   (attribute-export-comment "export as initial-workspace-height, (type positive-integer), writable = false"))
  (workspace-background-color?
    white system vector-slot user-overridable save (type extant-color-or-metacolor) 
    (attribute-export-comment "Export as background-color, with type (or none color-symbol)"))  
  (workspace-foreground-color?			   
    black system user-overridable vector-slot save (type extant-color-or-metacolor)
    (attribute-export-comment "Export as foreground-color, with type (or none color-symbol)"))  
  (workspace-margin
    30 system vector-slot user-overridable
    (type non-negative-integer)
    (attribute-export-comment "Export as is"))
  (background-images
    nil (type background-images)
    (attribute-export-comment "Type becomes ( image-definition *) <==> ~
				(or (seq (image-definition)) none)."))
  (frame-style
    nil user-overridable (type frame-style-name?)
    (attribute-export-comment
      "Export: Should type become frame-style-definition (an embedded struct), or ~
 	a symbol as it currently is (frame-style-name)?"))
  (title-bar-text
    nil system user-overridable (type workspace-title-bar-text))
  ;; Bogus name. Part of tamper mechanism.
  (display-index-point
    nil vector-slot system save
    (attribute-export-comment "Bogus name. Part of tamper mechanism. Internal."))
  (layering-information-for-clear-text
    nil lookup-slot system))


(define-slot-alias initial-height kb-workspace-initial-height kb-workspace)

(define-slot-alias initial-width kb-workspace-initial-width kb-workspace)


(add-grammar-rules
  '((module-name unreserved-symbol)
    (module-name? module-name)
    (module-name? 'unspecified)))

(reserve-words '(unspecified))			; move to the appropriate grammar module!

(define-slot-alias foreground-color workspace-foreground-color? kb-workspace)
(define-slot-alias background-color workspace-background-color? kb-workspace)

(def-slot-value-compiler module-name? (parse-result)
  (if (eq parse-result 'unspecified)
      nil
      parse-result))

(define-category-evaluator-interface (module-name?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(def-slot-value-writer module-name? (module-name?)
  (cond
    ((null module-name?)
     (twrite-string "unspecified"))
    (t
     (twrite-symbol module-name?))))



;;; The slot putter for `module-this-is-part-of?'

;;; Added hooks to send out notification about the change in assignment
;;; of module of a top-level kb-workspace in the putter for this slot.
;;; The notification is only sent if
;;; 1) The kb-workspace is actually changing modules and
;;; 2) The frame is not being deleted.
;;; We suppress the former to avoid unnecessary callbacks. The latter
;;; is handled in the cleanup method of kb-workspace. The callback
;;; notification needs to be sent before the icp-object-map for the
;;; registered item is reclaimed, which happens in the cleanup
;;; method for system-item. -vkp, 3/17/98

(def-slot-putter module-this-is-part-of? (kb-workspace value initializing?)
  (if (and (eq value no-value) initializing?)	; for very KBs saved with very early 
      (setq value nil))				;   versions of KB Modularity
  (let ((old-module?				;   software -- remove after 3.0 (MHD 2/19/92)
	  (unless initializing?
	    (module-this-is-part-of? kb-workspace))))
    (setf (module-this-is-part-of? kb-workspace) value)
    (unless initializing?
      (note-modification-of-module-for-clear-text value old-module?))
    (if old-module?
	(add-or-delete-as-workspace-belonging-to-module
	  kb-workspace old-module? t))
    (if value
	(add-or-delete-as-workspace-belonging-to-module
	  kb-workspace value nil))
    ;notify UI-INTERFACE-CLIENTs of top-level workspace changes
    (unless (or (eq old-module? value) (frame-being-deleted-p kb-workspace))
      (when old-module?
	(inform-ui-client-interfaces-of-top-level-workspace-assignment-change
	  kb-workspace nil old-module?))
      (when value
	(inform-ui-client-interfaces-of-top-level-workspace-assignment-change
	  kb-workspace t value)))
    (unless initializing?  ; called from elsewhere if initializing
      (update-module-related-frame-notes-for-all-workspaces
	kb-workspace old-module?))
    value))


(def-class-method initialize (kb-workspace)
  (funcall-superior-method kb-workspace)
  ;; Do not call this here; it's too expensive, since it
  ;; is not known if we will be making a subworkspace or
  ;; not; instead, we rely on the top-level workspace
  ;; maker being the only way one creates a new
  ;; top level workspace, and on it calling this:
  ;; (update-module-related-frame-notes-for-all-workspaces)
  ;; Removed. (MHD 8/16/96)
  )



(define-slot-alias module-assignment module-this-is-part-of?)




;(def-slot-value-writer kb-name (value)
;  (twrite (or value 'none)))

;(def-slot-value-compiler kb-name (parse)
;  (if (eq parse 'none) nil parse))


;;; The kb-specific-variable `dynamic-menus-modification-tick' is incremented
;;; whenever something changes that could affect the contents of a menu in the
;;; developer menu bar.

;;; It is a stop-gap for 7.0 alpha, pending a more general solution for all
;;; kinds of dynamic menus (eg, KB-level dynamic NMS menus).  In particular, we
;;; have to worry about fixnum wrapping.  It might simply be replaced by a
;;; post-menu callback which recomputes dynamic menus every time they are used,
;;; rather than caching and decaching with this modification tick.

(def-kb-specific-variable dynamic-menus-modification-tick frames5 0)
    
(defmacro increment-modification-tick (place)
  `(setf ,place (logandf (1+f ,place) #xFFFFFF)))	; 24 bits

(defmacro decrement-modification-tick (place)
  `(setf ,place (logandf (1-f ,place) #xFFFFFF)))	; 24 bits


;;; The function `decache-dynamic-menus' is called on changes which may
;;; invalidate the developer menu bar.  If workstation is NIL, then all
;;; workstations are affected.

(defun decache-dynamic-menus (type &optional workstation?)
  (cond ((or (eq type 'language) (eq type 'user-mode))
	 ;; A change in language means we have push the change out immediately
	 ;; (well, at the next call to service-workstation), because it changes
	 ;; the top-level items in the menu bar, which are visible at all times.

	 ;; Same is true for user mode, if some top-level items are restricted.
	 (if workstation?
	     (setf (nms-dynamic-menu-modification-tick (window-for-workstation workstation?)) -1)
	     (loop for workstation in workstations-in-service doing
	       (when (and (eq (workstation-login-state workstation) 'logged-in)
			  (null (specific-language-for-this-workstation? workstation))
			  (native-menu-bar-p (window-for-workstation workstation)))
		 (setf (nms-dynamic-menu-modification-tick (window-for-workstation workstation)) -1)))))
	(workstation?
	 ;; Cause just given workstation to be out of date by decrementing
	 ;; its tick into the past. (hack)
	 (decrement-modification-tick
	   (nms-dynamic-menu-modification-tick (window-for-workstation workstation?))))
	(t
	 (increment-modification-tick dynamic-menus-modification-tick))))

;; TODO: When type is kb-configuration, we could optimize and only decache
;; workstations which are not in administrator mode.


;;; The function `native-menu-bar-really-needs-updating-p' returns T if the menu
;;; bar for workstation is out of date, and we wish to "push" the new menu bar
;;; out to the TW on given the workstation at the next round through
;;; service-workstation, as opposed to waiting until the user clicks on the menu
;;; bar in TW and "pulls" the menu update. We currently use this push model only
;;; for changes in the current language, which affects the top-level, visible
;;; menu bar items

(defun native-menu-bar-really-needs-updating-p (workstation)
  (if workstation    ;;Suzsoft add for Gensym-407
  (let ((gensym-window (window-for-workstation workstation)))
    (when (native-menu-bar-p gensym-window)
      (=f (nms-dynamic-menu-modification-tick gensym-window) -1)))))

(def-class-method note-name-change (kb-workspace old-names initializing-p)
  (funcall-superior-method kb-workspace old-names initializing-p)
  (decache-dynamic-menus 'named-workspaces))


;;; The absent slot putter for kb-name is a temporary thing to fix up g2.ok over
;;; this weekend.  It seems that the file got saved out with kb-name slot
;;; values, and now we can't find any old versions of the file.  Grrrrrrr.  Also
;;; note that the class miscellaneous-parameters does have a slot with this
;;; name.  So, if we get a miscellaneous-parameters through this function, we
;;; should attempt to put the value.-jra 3/3/91

(def-absent-slot-putter kb-name (frame name)
  (declare (ignore frame name)))

(def-absent-slot-putter kb-name-for-workspace (frame name)
  (declare (ignore frame name)))




(def-substitute-for-old-class concurrent-block kb-workspace)

(def-absent-slot-putter initialization-interval (kb-workspace value)
  (declare (ignore kb-workspace value)))



;;; Item-workspace-p is true of a workspace that is both a workspace and an item.
;;; Logbook-pages and message-boards are the prototypical examples.
;;; The set of items that reside upon such workspaces is the domain over
;;; which inspect scans.  Workspaces that are not kb-workspaces, but are
;;; item-workspace-p, are never enabled, that prevents items appearing in
;;; the domain of the interpreters.

(defun item-workspace-p (frame)
  (and (frame-of-class-p frame 'workspace)
       (frame-of-class-p frame 'item)))





(defun get-reference-to-item-no-copy (item)
  (uuid item))

(defmacro ensure-uuid-for-item (item)
  `(ensure-uuid-for-item-reference (uuid ,item)))

(defun get-reference-to-item (item)
  (copy-evaluation-item-reference (uuid item)))

(def-slot-value-compiler uuid (parse-result item)
  (cond
    ((not (text-string-p parse-result))	; See note
     (values bad-phrase (copy-constant-wide-string #w"a UUID must be entered as a string")))
    (t
     (multiple-value-bind (uuid? problem-report?)
	 (convert-uuid-representation-to-internal parse-result)
       (cond ((null uuid?)
	      (values bad-phrase problem-report?))
	     (t
	      (let* ((uuid uuid?)
		     (existing-item (get-item-or-item-list-for-uuid uuid)))
		(cond ((and existing-item item (not (eq item existing-item)))
		       (if nil
			   nil ; add to frame notes
			   (reclaim-text-string uuid))
		       (values bad-phrase (copy-constant-wide-string #w"There already is an item with this UUID")))
		      (t
		       (when current-edit-state
			 (note-use-of-text-string-in-phrase uuid))
		       uuid)))))))))

(def-slot-value-writer uuid (uuid)
  (twrite-uuid-printed-representation-as-string uuid))

(def-slot-value-reclaimer uuid (unique-reference frame)
  (declare (ignore unique-reference))
  (put-uuid frame nil nil))

(defun-simple item-uuid (system-item)
  (let ((item-reference? (uuid system-item)))
    (when item-reference?
      (evaluation-item-reference-uuid item-reference?))))

(defun-void put-new-uuid (frame)
  (let ((new-item-reference (get-item-reference-for-new-uuid)))
    (setf (uuid frame) new-item-reference)
    (setf (evaluation-item-reference-referenced-item new-item-reference) frame)))

(def-slot-putter uuid (frame uuid? initializing?)
  (declare (ignore initializing?))
  (let* ((old-item-reference (uuid frame))
	 (new-item-reference
	   (when uuid?
	     (when (valid-uuid-p uuid?)
	       (mark-wide-string-as-binary uuid?))
	     (get-item-reference-for-uuid uuid? t t))))
    (cond
      ((eq old-item-reference new-item-reference))
      ((and new-item-reference
	    (evaluation-item-reference-referenced-item new-item-reference))
       ;; skip it.  This case shouldn't be reached.  The slot-value-compiler should have checked.
       (reclaim-evaluation-item-reference new-item-reference))
      (t
       (when old-item-reference
	 (setf (evaluation-item-reference-referenced-item old-item-reference) nil)
	 (reclaim-evaluation-item-reference old-item-reference))
       (setf (uuid frame) new-item-reference)
       (when new-item-reference
	 (setf (evaluation-item-reference-referenced-item new-item-reference) frame))))
    (when uuid?
      (reclaim-text-string uuid?))
    (values new-item-reference t)))




;;;; Uniform types



;; These are designed for convenience, not speed.  -fmw, 1/12/94

(def-substitution-macro ab-type-of (thing)
  (cond ((framep thing)
	 (class-description (class thing)))
	(t
	 (or (type-description-of-1 thing)
	     (type-description-of-type t)))))


(def-substitution-macro ab-find-type (name)
  (or (type-description-of-type name)
      (class-description name)))



(defun ab-subtypep-1 (class-1 class-2)
  (cond ((and (type-description-p class-1) (type-description-p class-2))
	 (subtype-p-using-type-descriptions class-1 class-2))
	((and (class-description-p class-1) (class-description-p class-2))
	 (inheritance-path-memq (class-name-of-class-description class-2)
				(class-inheritance-path class-1)))))


(defun ab-subtypep (type-1 type-2)
  (cond ((eq type-2 t)
	 t)
	((eq type-1 t)
	 nil)
	(t
	 (let ((class-1 (ab-find-type type-1))
	       (class-2 (ab-find-type type-2)))
	   (ab-subtypep-1 class-1 class-2)))))



;;; The macro `ab-typep-function' is typep over G2 structures and frames.

(defun ab-typep-function (thing ab-type)
  (ab-subtypep-1 (ab-type-of thing) (ab-find-type ab-type)))


(defmacro ab-typep (thing ab-type)
  (if (constantp ab-type)
      (let ((type (eval ab-type)))
	(cond ((class-description type)
	       `(and (framep ,thing)
		     (frame-of-class-p ,thing ',type)))
	      (t
	       `(ab-typep-function ,thing ,ab-type))))
      `(ab-typep-function ,thing ,ab-type)))

;; Ben would prefer this to take a type-description as the second arg, rather than a symbol.



(defmacro ab-typecase (expr &body cases)
  (let ((var (make-symbol "EXPR")))
    `(let ((,var ,expr))
       (cond ,@(loop for (type . body) in cases
		     collect
		     (cond ((null type))
			   ((eq type t)
			    `(,t ,@body))
			   ((atom type)
			    `((ab-typep ,var ',type)
			      ,@body))
			   ((singleton? type)
			    `((ab-typep ,var ',(first type))
			      ,@body))
			   (t
			    `((or ,@(loop for type-name in type
					  collect `(ab-typep ,var ',type-name)))
			      ,@body))))))))



;;;; "Attribute Descriptions"

(def-concept attribute-description)

;;; Attribute Descriptions are a union of slot-descriptions and virtual-attributes.
;;; They are being invented so I do not have to write approximately 10^6
;;; functions whose names contain the phrase "slot-description-or-virtual-attribute"
;;; jed -  10/1/96

(defun-simple get-attribute-description-from-class-description
    (class-description attribute-name class-qualifier?)
  (let ((slot-description?
	  (get-slot-description-of-class-description
	    attribute-name class-description class-qualifier?)))
    (cond
      ((and slot-description?
	    (user-defined-slot-description-p slot-description?))
       slot-description?)
      (t
       (or (let ((va (virtual-attribute attribute-name)))
	     (when (and va
			(virtual-attribute-defined-for-class?
			  va
			  (class-name-of-class-description class-description)))
	       va))
	   (let ((aliased-slot-name
		   (get-slot-name-for-alias-if-any
		     attribute-name (class-name-of-class-description
				      class-description))))
	     (if aliased-slot-name
		 (get-slot-description-of-class-description
		   aliased-slot-name class-description class-qualifier?)
		 slot-description?)))))))

(defmacro get-attribute-description-of-frame
    (frame attribute-name class-qualifier?)
  `(get-attribute-description-from-class-description
     (class-description-slot ,frame) ,attribute-name ,class-qualifier?))

(defmacro attribute-description-type-specification (attribute-description-exp)
  (let ((attribute-description (gensym)))
    `(let ((,attribute-description ,attribute-description-exp))
       (if (slot-description-p ,attribute-description)
	   (slot-type-specification ,attribute-description)
	   (virtual-attribute-arg-type ,attribute-description)))))


;;; Evaluator-Info Caching on Slot Descriptions

;;; This exists to allow much faster cached access to whether a system-defined
;;; slot has a evaluation-interface getter or setter.  This information is
;;; decached if virtual-attribute or category-evaluator interfaces are changed.

(def-substitution-macro get-slot-description-evaluator-info (slot-description)
  (or (slot-description-evaluator-info? slot-description)
      (cache-evaluator-slot-info slot-description)))

(defun-simple cache-evaluator-slot-info (slot-description)
  (let* ((slot-info (make-evaluator-slot-info))
	 (slot-type?
	   (feature-assq 'type (slot-features slot-description)))
	 (category?
	   (if slot-type?
	       (category-symbol-given-slot-type slot-type?)))
	 (text-slot?
	   (if slot-type? (text-slot-type-p slot-type?) nil))
	 (category-setter
	   (and category?
		(evaluation-value-to-category-function category?)))
	 (category-getter
	   (and category?
		(slot-value-to-evaluation-value-function category?)))
	 (category-committer
	   (or (category-committer-function category?)
	       #'default-category-slot-access-committer))
	 (category-extracter
	   (or (category-extracter-function category?)
	       #'default-category-slot-access-extracter))
	 (virtual-attribute
	   (virtual-attribute (pretty-slot-name slot-description))))
    (setf any-cached-evaluator-slot-info-p t)
    (setf (slot-description-evaluator-info? slot-description) slot-info)
    (setf (evaluator-slot-info-category slot-info)
	  category?)
    (setf (evaluator-slot-info-category-setter slot-info)
	  category-setter)
    (setf (evaluator-slot-info-category-getter slot-info)
	  category-getter)
    (setf (evaluator-slot-info-category-committer slot-info)
	  category-committer)
    (setf (evaluator-slot-info-category-extracter slot-info)
	  category-extracter)
    (setf (evaluator-slot-info-text-slot-p slot-info)
	  text-slot?)
    (setf (evaluator-slot-info-virtual-attribute slot-info)
	  virtual-attribute)
    slot-info))
    


(defun-simple get-attribute-description-evaluation-value (frame attribute-description)
  (cond
    ((eq (g2-type-name-of-named-simple-vector attribute-description)
	 (intern-unique-def-structure-symbol-name 'slot-description))
     (cond
       ((user-defined-slot-description-p attribute-description)
	(let ((value (get-user-slot-description-value
		       frame attribute-description)))
	  (cond
	    ((slot-constantp value)
	     (cast-slot-constant-into-evaluation-value value))
	    ((framep value)
	     (if (serve-item-p value) value nil))
	    ;; note:  frame-or-evaluation-value-user-attribute-value
	    ;; uses (copy-evaluation-non-logical-datum-macro value)
	    (value (copy-evaluation-value value))
	    (t nil))))
       (t
	(let* ((evaluator-info
		 (get-slot-description-evaluator-info attribute-description))
	       (category-getter?
		 (evaluator-slot-info-category-getter evaluator-info)))
	  (cond
	    (category-getter?
	     (multiple-value-bind (extracted-value reclaim-p)
		 (funcall-simple-multi-valued-compiled-function
		   (evaluator-slot-info-category-extracter evaluator-info)
		   (get-slot-description-value frame attribute-description)
		   evaluator-info)
	       (prog1 (call-category-getter-fn
			category-getter?
			extracted-value
			frame
			attribute-description)
		 (when reclaim-p
		   (reclaim-slot-value extracted-value)))))
	    (t
	     nil))))))
    (t
     ;; Virtual-attribute case (must be system-defined).
     (if (type-specification-type-p
	   frame
	   (virtual-attribute-arg-type attribute-description))
	 (let ((value 
		 (get-virtual-attribute frame attribute-description)))
	   (if (eq value no-component-value)
	       nil
	       value))
	 nil))))
  
(defun-simple change-attribute-description-evaluation-value
              (frame attribute-description new-value)
  (if (slot-description-p attribute-description)
      (let ((pretty-name (pretty-slot-name attribute-description))
	    (unique-name (unique-slot-name attribute-description)))
	(conclude-into-attribute-component
	  frame
	  (alias-slot-name-if-necessary
	    (pretty-slot-name attribute-description)
	    frame)
	  (cond ((eq pretty-name unique-name) ; doesn't need qual optimization
		 nil)
		;; the following test isn't so cheap -- 
		;; would like to memo-ize its results
		((slot-name-needs-qualification-p
		   attribute-description (class-description-slot frame))
		 (defining-class attribute-description))
		(t
		 nil))
	  new-value
	  nil
	  nil
	  attribute-description))
      (conclude-into-attribute-component
	frame
	(virtual-attribute-name attribute-description)
	nil
	new-value
	nil
	nil
	attribute-description)))



(defun default-category-slot-access-committer (compiled-parse-result evaluation-value evaluator-info)
  (declare (ignore evaluation-value))
  (if (evaluator-slot-info-text-slot-p evaluator-info)
      (slot-value-cons
	compiled-parse-result
	(convert-text-string-to-text
	  (twith-output-to-text-string
	    (funcall-compiled-function
	      (slot-value-writer
		(evaluator-slot-info-category evaluator-info))
	      compiled-parse-result
	      compiled-parse-result))))
      compiled-parse-result))

(defun default-category-slot-access-extracter (slot-value evaluator-info)
  (if (evaluator-slot-info-text-slot-p evaluator-info)
      (values (car slot-value) nil)
      (values slot-value nil)))

(defun text-category-slot-access-committer (compiled-parse-result evaluation-value evaluator-info)
  (if (evaluator-slot-info-text-slot-p evaluator-info)
      (when evaluation-value
	(slot-value-cons
	  compiled-parse-result
	  (convert-text-string-to-text
	    (copy-text-string evaluation-value))))
      compiled-parse-result))

(defun text-category-slot-access-extracter (slot-value evaluator-info)
  (if (evaluator-slot-info-text-slot-p evaluator-info)
      (values (cdr slot-value) nil)
      (values
	(convert-text-string-to-text
	  (twith-output-to-text-string
	    (funcall-compiled-function
	      (slot-value-writer
		(evaluator-slot-info-category evaluator-info))
	      slot-value
	      slot-value)))
	t)))



#+maybe
(defun-for-system-procedure g2-test-change-attribute
    (item slot-name class-qualifier-if-symbol new-value)
  (let ((slot-description?
	  (get-slot-description-of-frame
	    slot-name item (if (symbolp class-qualifier-if-symbol)
			       class-qualifier-if-symbol
			       nil))))
    (cond (slot-description?
	   (let ((error?
		   (change-attribute-description-evaluation-value
		     item slot-description? new-value)))
	     (when error?
	       (stack-error cached-top-of-stack
			    error?))))
	  (t
	   (stack-error cached-top-of-stack
			"bad slot reference ~NQ"
			slot-name
			(if (symbolp class-qualifier-if-symbol)
			    class-qualifier-if-symbol
			    nil))))))
	    



;;;; General Accessors




(defun user-attribute-slot-description-or-virtual-attribute
    (item-or-class-description attribute class-specific-attribute-class? direction)
  (let* ((class-description-p (class-description-p item-or-class-description))
	 (class-description (if class-description-p
				item-or-class-description
				(class-description-slot item-or-class-description)))
	 (slot-description?
	   (get-slot-description-of-class-description
	     attribute class-description class-specific-attribute-class?))
	unaliased-name? type? virtual-attribute?
	arg-type?
	category-interface?)
    (cond
	((and slot-description?
	      (user-defined-slot-description-p slot-description?))
	 (values slot-description? nil))
	((and (if (setq unaliased-name?
			(get-slot-name-for-alias-if-any attribute item-or-class-description))
		  (setq slot-description?
			(get-slot-description-of-class-description
			  unaliased-name? class-description class-specific-attribute-class?))
		  slot-description?)
	      (setq type? (feature-assq 'type (slot-features slot-description?)))
	      (setq category-interface? (category-evaluator-interface-from-slot-type type?))
	      (case direction
		(get (interface-slot-value-to-evaluation-value-function
		       category-interface?))
		(set (interface-evaluation-value-to-category-function
		       category-interface?))
		(both (and (interface-slot-value-to-evaluation-value-function
			     category-interface?)
			   (interface-evaluation-value-to-category-function
			     category-interface?)))))
	 (values slot-description? category-interface?))
	((and (setq virtual-attribute? (virtual-attribute attribute))
	      (setq arg-type? (virtual-attribute-arg-type virtual-attribute?))
	      (or class-description-p
		  (type-specification-type-p item-or-class-description arg-type?))
	      (case direction
		(get (virtual-attribute-getter? virtual-attribute?))
		(set (virtual-attribute-setter? virtual-attribute?))
		(both (and (virtual-attribute-getter? virtual-attribute?)
			   (virtual-attribute-setter? virtual-attribute?)))))
	 (values nil virtual-attribute?)))))

(defmacro coerce-user-slot-value-to-evaluation-value (value)
  `(let ((value ,value))
     (cond ((slot-constantp value)
	    (cast-slot-constant-into-evaluation-value value))
	   ((framep value)
	    (if (serve-item-p value) value nil))
	   ;; note:  frame-or-evaluation-value-user-attribute-value
	   ;; uses (copy-evaluation-non-logical-datum-macro value)
	   (t value))))

;used in uses of with-slot-evaluation-value-from-user-attribute-if-present, below
(defun-simple get-slot-evaluation-value-1 (item slot-description? category-interface-or-virtual-attribute?)
  (cond ((null slot-description?)
	 (call-get-virtual-attribute-fn
	   (virtual-attribute-getter? category-interface-or-virtual-attribute?)
	   item))
	((null category-interface-or-virtual-attribute?)
	 (coerce-user-slot-value-to-evaluation-value
	   (get-slot-description-value item slot-description?)))
	(t
	 (let ((evaluator-info
		 (get-slot-description-evaluator-info slot-description?)))
	   (multiple-value-bind (extracted-value reclaim-p)
	       (funcall-simple-multi-valued-compiled-function
		 (evaluator-slot-info-category-extracter evaluator-info)
		 (get-slot-description-value item slot-description?)
		 evaluator-info)
	     (prog1 (call-category-getter-fn
		      (evaluator-slot-info-category-getter evaluator-info)
		      extracted-value	   
		      item slot-description?)
	       (when reclaim-p
		 (reclaim-slot-value extracted-value))))))))


;used in rpc-common3: item-matches-identifying-attributes-p select-attributes-from-item
(defmacro with-slot-evaluation-value-from-user-attribute-if-present
    ((variable item-form attribute-form attribute-class?-form &optional if-not-present-form)
     &body forms)
  (let ((item (make-symbol "ITEM"))
	(slot-description? (make-symbol "SLOT-DESCRIPTION?"))
	(category-interface-or-virtual-attribute?
	  (make-symbol "CATEGORY-INTERFACE-OR-VIRTUAL-ATTRIBUTE?")))
    `(let ((,item ,item-form))
       (multiple-value-bind (,slot-description? ,category-interface-or-virtual-attribute?)
	   (user-attribute-slot-description-or-virtual-attribute
	     ,item ,attribute-form ,attribute-class?-form 'get)
	 (if (or ,slot-description? ,category-interface-or-virtual-attribute?)
	     (let ((,variable (get-slot-evaluation-value-1 ,item ,slot-description?
							   ,category-interface-or-virtual-attribute?)))
	       ,@forms)
	     ,if-not-present-form)))))

;;; GENSYMCID-1167: Verify in the source code the difference between ...

;;; Here the function `find-similar-slot-name' and `find-similar-class-name' are trying
;;; to fix those corrupted KBs which contains reclaimed symbols (&...&).  If string1
;;; and string2 are the same except the first and last character (&), we say they're
;;; `similar', and for those broken KBs, we replace broken symbols into their similar
;;; symbols by searching into all valid slots and classes.
;;;
;;; And the root cause of the issue should be in `read-attribute-name-from-text-string-1'
;;; (EDIT1) in which token-values as symbol names may get reclaimed in rare cases.
;;;
;;; -- Chun Tian (binghe), 27/12/2013

;; see RECLAIM-WIDE-STRING
(defun-simple malformed-symbol-name-p (symbol)
  (let* ((symbol-string (symbol-name-text-string symbol))
	 (symbol-length (text-string-length symbol-string))
	 (stamp #.%\&))
    (and (char=w (charw symbol-string 0) stamp)
	 (char=w (charw symbol-string (1-f symbol-length)) stamp))))

(defun-simple find-similar-slot-name (slot-name class)
  (let* ((slot-name-string (symbol-name-text-string slot-name))
	 (slot-name-length (text-string-length slot-name-string)))
    (when (>=f slot-name-length 5) ; long enough?
      (loop with sub1 = (text-string-substring slot-name-string 1 (1-f slot-name-length))
	    for current-class in (class-inheritance-path (class-description class))
	    thereis
	(loop for candidate-slot-name in (slots-local-to-class
					   (class-description current-class))
	      for candidate-slot-name-string = (symbol-name-text-string candidate-slot-name)
	      for candidate-slot-name-length = (text-string-length candidate-slot-name-string)
	      when (and (=f slot-name-length candidate-slot-name-length)
			(let ((sub2 (text-string-substring candidate-slot-name-string 1
							   (1-f candidate-slot-name-length))))
			  (prog1 (text-string= sub1 sub2)
			    (reclaim-text-string sub2))))
	      do (progn
		   (notify-user "Fixed corrupted attribute name ~A with ~S, ~
                                 please save your KB and notify Gensym Customer Support."
			      slot-name candidate-slot-name)
		   (setq slot-name candidate-slot-name)
		   (return t))
	      finally
		(return nil))
	    finally
	      (reclaim-text-string sub1)))
    slot-name))

(defun-simple find-similar-class-name (class)
  (let* ((class-name-string (symbol-name-text-string class))
	 (class-name-length (text-string-length class-name-string)))
    (when (>=f class-name-length 5) ; long enough?
      (loop with sub1 = (text-string-substring class-name-string 1 (1-f class-name-length))
	    for candidate-class-name being each subclass of 'block
	    for candidate-class-name-string = (symbol-name-text-string candidate-class-name)
	    for candidate-class-name-length = (text-string-length candidate-class-name-string)
	    when (and (=f class-name-length candidate-class-name-length)
		      (let ((sub2 (text-string-substring candidate-class-name-string 1
							 (1-f candidate-class-name-length))))
			(prog1 (text-string= sub1 sub2)
			  (reclaim-text-string sub2))))
	    do (progn
		 (notify-user "Fixed corrupted class name ~A with ~S, ~
                               please save your KB and notify Gensym Customer Support."
			      class candidate-class-name)
		 (setq class candidate-class-name)
		 (loop-finish))
	    finally
	      (reclaim-text-string sub1)))
    class))

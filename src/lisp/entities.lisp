;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ENTITIES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Ong, Peng Tsin,
;;; Stephen R. DeVoy, Andreas Hofmann, and Lowell B. Hawkinson






;;;; Forward References in ENTITIES


(declare-forward-reference write-drawing-element function)

;; To KB-MERGE

(declare-forward-reference module-information variable)
(declare-forward-reference
  inhibit-updating-module-related-frame-notes-for-all-workspaces?
  variable)
(declare-forward-reference system-version-from-kb-being-read variable)

;; To PRINTING

(declare-forward-reference printing-icon-current-region-index? variable)


;; To DEBUG

(declare-forward-reference warn-of-missing-color-region function)
(declare-forward-reference warn-of-unnamed-color-region function)
(declare-forward-reference warn-of-illegal-colors function)
(declare-forward-reference warn-of-invalid-color-attribute function)


;; To CONNECT1

(declare-forward-reference get-connection-color function)
(declare-forward-reference get-cross-section-regions-function function)


;; To CONNECT2

(declare-forward-reference make-stubs function)
(declare-forward-reference magnify-connections-on-block-in-workspace function)
(declare-forward-reference
  reflect-and-rotate-loose-ends-of-block-in-workspace function)
(declare-forward-reference
  reflect-and-rotate-connections-on-block-in-workspace function)
(declare-forward-reference change-color-of-connection function)
(declare-forward-reference change-color-pattern-of-connection function)
(declare-forward-reference magnify-icon function)
(declare-forward-reference rotate-and-reflect-icon function)


;; To CONNECT3A
(declare-forward-reference local-edges-of-block-or-connection function)


;; To CONNECT4

(declare-forward-reference determine-subworkspace-connection-posts
			   function)
(declare-forward-reference flush-all-subworkspace-connection-posts-for-object
			   function)

;; To Definitions
(declare-forward-reference update-slot-description-for-system-defined-class function)
(declare-forward-reference mark-background-image-coordinates-as-needing-update function)

;; To TABLES

(declare-forward-reference change-color-of-text-box function)


;; To MOVES

(declare-forward-reference move-blocks-with-their-external-connections function)
(declare-forward-reference transfer-blocks-with-their-external-connections function)
(declare-forward-reference redraw-transfer-representations-of-block function)
(declare-forward-reference determine-extreme-edges-for-item-being-moved function)


;; To FILES

(declare-forward-reference notify-engineer function)
(declare-forward-reference note-kb-state-change function)
(declare-forward-reference current-kb-pathname? variable)
;; TRAVERSALS
(declare-forward-reference add-as-inferior-block function)
(declare-forward-reference remove-as-inferior-block function)


;; To INSTALL

(declare-forward-reference update-runtime-structures-according-to-edit function)


;; To Facilities

(declare-forward-reference make-attribute-displays-per-specs function)

;; To CHECK-MEMORY

#+development
(declare-forward-reference check-memory function)


;; To DEFINITIONS
(declare-forward-reference workspace-background-images-are-centered-p function)


;; To stack-acts
(declare-forward-reference executing-change-item-color-instruction-p variable)

;; To EVENTS-G2
(declare-forward-reference send-ws-representations-item-color-pattern-change function)

(declare-forward-reference get-property-value-in-object-configuration function)
(declare-forward-reference find-image-data function) ;definitions.lisp

(declare-forward-reference get-ruling-for-meter function)

(declare-forward-reference get-module-block-is-in function)
(declare-forward-reference bounding-region-of-block-or-connection function)

(declare-forward-reference move-selection-highlights function)

;; To View-Def
(declare-forward-reference update-subscriptions-for-color-change function)

;; To G2-BPEL

(declare-forward-reference g2gl-parameters variable)
(declare-forward-reference get-g2gl-object-icon-description function)

;; To FACTIONS
#+mtg2
(declare-forward-reference propagate-faction-recursively function)
#+mtg2
(declare-forward-reference add-faction-member function)
#+mtg2
(declare-forward-reference remove-as-faction-member function)

;; To Do


;; The following by MHD, 9/9/87:

;; Fix variable names in many functions to give some clue as to what coordinate
;; system is in use, and especially to make conspicuous variables whose values
;; may not fit in at all (such as floats in the circle drawing stuff.)



;;;; Entities



;;; An `entity' is a block that typically represents (non-uniquely) an object.  When
;;; an entity has a location, it is graphically represented by an icon.

;;; An `icon' is a line drawing in a rectangle....

;;; A `polychrome icon' is an icon which has a polychrome line drawing description,
;;; as defined below.

;;; The icon description for an entity is normally just the default value for the
;;; icon-description slot.  However, instances of certain system-internal entity
;;; classes may have entity-specific icon descriptions.  It is assumed that such
;;; an entity will never be saved in a saved kb; if it were to be saved, its
;;; entity-specific icon description would not be saved, and thus, if the saved
;;; kb were reloaded, the entity would have the icon description from the class and
;;; might be drawn incorrectly (maybe with turding).  Changing the icon description
;;; of an entity may be done using setf; if the entity is currently drawn, the same
;;; logic as would be used to change the icon size must be used as well.

;;; Subworkspaces values are not explicitly saved in a saved kb, but instead are
;;; reconstructed from saved parent-of-subworkspace? values.

;;; NOTE: the number of vector slots of class `entity' should be the same with
;;; class `table' (defined in tables.lisp). -- Chun Tian (binghe), Apr 2, 2015.

(def-class (entity block define-predicate
		   (class-export-comment
		      "Icon-description defined on ENTITY, but is ~
	specialized on individual classes and shows up directly on those ~
	classes without appearing in their def-class. This is a hack to ~
	initialize each class with it's own icon description. Export as ~
	( regions-and-drawing-commands * ) | icon, writable = true.
	icon-attributes-plist, exported as icon-attributes will show up on any ~
	class that has icon-description, but it is inherited normally from ~
	ENTITY."))

  (icon-description			      ; not normally set or saved; see above
    nil system vector-slot user-overridable   ; See note A
    (attribute-export-comment "See comment on ENTITY class definition"))
  (icon-attributes-plist
    nil system vector-slot save
    (attribute-export-comment "Export as Icon-attributes part"))

  (attribute-displays-for-class
    nil lookup-slot system class-slot do-not-save user-overridable
    not-user-editable no-accessor do-not-put-in-attribute-tables)
  (stubs-for-class
    nil lookup-slot system class-slot do-not-save user-overridable
    not-user-editable no-accessor do-not-put-in-attribute-tables)

  (subworkspaces nil system vector-slot save) ; at most one element

  (runtime-structures-affected-by-this-entity nil system vector-slot)

  ;; The next three slots are moved here from the former capability, external-
  ;; simulation.
  (external-simulation-object-structure
     nil (lookup-slot) (system)
     (do-not-put-in-attribute-tables) (do-not-save))
  (external-simulation-definition-for-entity
     nil (lookup-slot) (system)
     (do-not-put-in-attribute-tables) (do-not-save))
  (external-set-pointers?
     nil (lookup-slot) (system)
     (do-not-put-in-attribute-tables) (do-not-save)))


;; Change the name of the subworkspace slot to subworkspace? (and its value
;; accordingly) in recognition of the fact that an entity will never be allowed to
;; have more than one subworkspace.

;; Runtime-structures-affected-by-this-entity is used to uncache runtime
;; structures when the entity is edited (see INSTALL, SIMULATE).  This slot is
;; not saved.

;; Note A: The initialization of icon-description for class entity is fixed up later in
;; this module, after create-icon-description is usable, so that all will be as
;; if the initialization had been of the form
;;  (:FUNCALL-AT-LOAD-TIME create-icon-description ...)

;; Consider having icon-description be a vector slot, to speed up icon rendering
;; a bit, even though this slot is never set.
;; Since this slot is almost-always non-NIL, we save space and time by making
;; it a vector slot. -fmw, 1/9/95


;; If user-defined classes were ever to have entity-specific icon descriptions,
;; module DEFINITIONS would need to be revised to do the right thing on class
;; redefinitions.

;; See fix-up-icon-description-for-entity-if-necessary below.

;; Consider having icon-attributes-plist have a type so it can be examined and
;; edited.  In that case, maybe in any case, it should have a slot putter to
;; redraw the entity.

;; Consider having icon-attributes-plist be a lookup slot, if only a low
;; percentage of entities in large kbs make use of it and icon rendering speed
;; is not a key factor.

;; Consider having the parent information slots be vector slots.

;; Consider having the subworkspaces slot be a vector slot, if necessary for
;; fast G2 procedure calls.

;; List-of-procedure-instances-for-entity used to be a slot containing a list of
;; all procedure instances of which this entity is the focal-entity.  If the
;; entity or the procedure-instance where not IN-USE, then both references to
;; the instance were to have been deleted and the instance re-used.





;;; The slot value reclaimer for icon-description reclaims its value if it is
;;; not EQ to the default value for the slot; see definitions for entity and
;;; icon-description for more information.

(def-slot-value-reclaimer icon-description (icon-description entity)
  (let ((default-slot-value
	    (get-slot-init-form (class entity) 'icon-description))
	(substitute-icon-description?
	  (if (frame-of-class-p entity 'g2gl-activity) ; see note! (MHD 7/13/06)
	      ;; special-case handling for G2GL activities:
	      (let ((substitute-class?
		      (if g2gl-parameters ; nec.?
			  (cadr (assq (class entity)
				      (get-slot-value 
					g2gl-parameters
					'g2gl-object-icon-substitutions))))))
		(if substitute-class?
		    (class-case substitute-class?
		      (g2gl-object
			(get-g2gl-object-icon-description substitute-class?))
		      (object
			(get-slot-init-form substitute-class? 'icon-description))))))))
    (if (and icon-description
	     (not (eq icon-description default-slot-value))
	     (null substitute-icon-description?))
	;; must be entity-specific => reclaim it
	(reclaim-icon-description icon-description))))

;; Note: in some unusual cases involving switching KBs (clearing, system table
;; installation, etc.), the slot init form doesn't match the G2GL icon
;; substitutions, so this check is therefore necessary. See bug HQ-5264337 "G2
;; abort clearing a G2GL bug example kb". (MHD 7/13/06)

;; Get-slot-init-form is now defined in FRAMES2. (MHD 6/18/90)


(def-slot-value-reclaimer runtime-structures-affected-by-this-entity
			  (value frame)
  value
  (update-runtime-structures-according-to-edit frame))


(def-absent-slot-putter debugging-specification (entity value)	; eliminate in mid-1988!
  (declare (ignore value entity)))


(def-class-method generate-spot (entity mouse-pointer)
  (generate-simple-item-spot entity mouse-pointer))


(defun icon-description-function (entity)
  (icon-description entity))




;;;; Subworkspaces



;;; An entity may have only one `subworkspace'.



;;; Some entities do not get their subworkspaces activated when they themselves
;;; become active. This includes entities having the capability ACTIVATABLE-SUBWORKSPACE,
;;; and it will also apply to procedures later.

;;; The macro `subworkspacep' will return NIL if the workspace is a top-level workspace,
;;; otherwise it will return a non-NIL value.

(defmacro subworkspacep (workspace)
  `(parent-of-subworkspace? ,workspace))

;;; Add-subworkspace makes workspace a subworkspace of entity, and returns
;;; workspace.  If the superblock of entity is active, workspace will be
;;; activated.

;;; If workspace is of class kb-workspace, and (top-level-kb-module?
;;; module-information) is non-nil, the module-this-is-part-of? slot of
;;; the workspace is changed to nil, using change-slot-value, in order
;;; to meet with constraints for that slot when it is no longer a top-level
;;; workspace, and also to cause its frame notes, and those of module-
;;; information, to be reconsidered.

(defun add-subworkspace (workspace entity)
  (let ((previously-top-level-workspace-of-module-p
	  (if (and (frame-of-class-p workspace 'kb-workspace)
		   (null (parent-of-subworkspace? workspace)))
	      (module-this-is-part-of? workspace))))
    #+mtg2
    (let ((faction?
	   (cond
	     ((eq 'faction (class entity)) entity)
	     ((faction? entity) (faction? entity)))))
      (when faction?
	(add-faction-member workspace faction?)
	(propagate-faction-recursively workspace)))
    ;; setting may be redundant in the initialize(-after-reading) case:
    (setf (parent-of-subworkspace? workspace) entity)
    ;; Memq can only be true in the loading case for 3.0 and > KBs.
    (unless (memq workspace (subworkspaces entity))
      #+SymScale
      (slot-value-push-atomic workspace (subworkspaces entity))
      #-SymScale
      (setf (subworkspaces entity)
	    (slot-value-cons workspace (subworkspaces entity)))
      (cond
	((and (active-p entity)
	      (not (activatable-subworkspace-p entity)))
	 (funcall-method-if-any 'activate-if-possible-and-propagate workspace))
	((or (manually-disabled-p entity)
	     (ancestor-not-activatable-p entity)
	     (frame-status entity))
	 (funcall-method 'deactivate-and-propagate workspace t))))
    (determine-subworkspace-connection-posts entity)
    (add-as-inferior-block workspace entity)	       ;added cpm, 8/9/91.

    (when (and previously-top-level-workspace-of-module-p
	       (get-slot-value			; fwd. ref.
		 module-information 'top-level-kb-module?))
      (change-slot-value				; new. (MHD 11/22/91)
	workspace 'module-this-is-part-of? nil))

    workspace))

;; Consider adding workspace at the end of the subworkspaces list.



;;; Remove-as-subworkspace-if-necessary makes workspace not be a subworkspace,
;;; if it is one.  That is to say, workspace becomes a top-level workspace.
;;; Workspace is returned.

;;; If workspace is of class kb-workspace, (top-level-kb-module?
;;; module-information) is non-nil, the module-this-is-part-of?  slot of the
;;; workspace is changed to the value of (top-level-kb-module?
;;; module-information), using change-slot-value, which is what would have
;;; happened to that slot in a newly created top-level kb workspace.  It is also
;;; needed in order to cause its frame notes, and those of module-information,
;;; to be reconsidered.

(defun remove-as-subworkspace-if-necessary
    (workspace &optional (deactivate-workspace? t))
  (let ((parent-of-subworkspace? (parent-of-subworkspace? workspace)))
    (cond
      (parent-of-subworkspace?

       #+mtg2
       (when (faction? workspace)
	 (remove-as-faction-member workspace)
	 (when (eq 'faction (class parent-of-subworkspace?))
	   (reclaim-constant-queue
	    (get-slot-value parent-of-subworkspace? 'faction-members))
	   (set-slot-value parent-of-subworkspace? 'faction-members nil)))
       
       (remove-as-inferior-block workspace parent-of-subworkspace?) ; (MHD 2/5/94)
       (setf (parent-of-subworkspace? workspace) nil)
       ;; TODO: not thread-safe.
       (setf (subworkspaces parent-of-subworkspace?)
	     (delete-slot-value-element		; not necessarily there
	      workspace (subworkspaces parent-of-subworkspace?)))

       (when deactivate-workspace?
	 (funcall-method-if-any 'deactivate-and-propagate workspace nil))
       (flush-all-subworkspace-connection-posts-for-object
	 parent-of-subworkspace? nil)))

    ;; Do not run this code if this is being deleted; it only
    ;; needs to run if we're making it a top-level KB workspace.
    ;; Setting the module slot triggers a lot of frame note checking,
    ;; which can be costly. (MHD 8/20/96)

    (when (and (not (frame-being-deleted-p workspace))
	       (null parent-of-subworkspace?))
      (let ((top-level-kb-module?
	      (get-slot-value			; fwd. ref.
		module-information 'top-level-kb-module?)))
	(if (and (frame-of-class-p workspace 'kb-workspace)
		 top-level-kb-module?)
	    (change-slot-value			; new. (MHD 11/22/91)
	      workspace 'module-this-is-part-of?
	      top-level-kb-module?))))

    workspace))

  ;; Modified to optionally not deactivate the workspace that is being removed.
;; cpm, 8/14/91.  This change is need in the make-subworkspace action.




;;; Transfer-subworkspace-if-any transfers the subworkspace from entity, if it has one,
;;; to entity-without-subworkspace (which must not have a subworkspace).

(defun transfer-subworkspace-if-any (entity entity-without-subworkspace)
  (if (subworkspaces entity)
      (let* ((inhibit-updating-module-related-frame-notes-for-all-workspaces?
	       t))			; transferring a subworkspace cannot have
					;  any impact on modularity; suppress
					;  all frame notes activity around
					;  the incremental steps
	(add-subworkspace
	  (remove-as-subworkspace-if-necessary
	    (first (subworkspaces entity)))
	  entity-without-subworkspace))))



;;; Replace-subworkspace-if-any adds a subworkspace to a new parent.  This
;;; subworkspace is first removed from any existing parent.  Any previous
;;; subworkspace of the new parent is removed but not deleted.

;;; When the new subworkspace is added to the new parent and this parent is
;;; already active, this new subworkspace is activated.  If the parent is not
;;; active, the new subworkspace is deactivated.  If the subworkspace already
;;; has the new parent as its existing parent, there is no change (i.e., no
;;; activation or deactivation).

;;; Note that any existing subworkspace of the new parent is removed and not
;;; deactivated.  Also, if the new subworkspace is already a subworkspace of
;;; another object, it is not deactivated when it is removed from this parent
;;; object and before being added to the new parent.

;; Written for the make-subworkspace action in 3.0.  cpm, 8/14/91.

;; Modified the remove-subworkspace function to optionally not deactivate the
;; subworkspace.

(defun replace-subworkspace-if-any (kb-workspace entity)
  (let ((kb-workspace-already-subworkspace? nil))
    (when (subworkspaces entity)
      ;; Remove existing subworkspaces of the new parent, before adding the
      ;; subworkspace.
      (loop with subworkspace-list =
	    (copy-list-using-gensym-conses (subworkspaces entity))
	    ;; The subworkspace list is copied and later reclaimed, since
	    ;; removing workspaces from the parent modifies the original
	    ;; list.
	    for subworkspace in subworkspace-list
	    do
	(if (eq subworkspace kb-workspace)
	    (setq kb-workspace-already-subworkspace? t)
	    (remove-as-subworkspace-if-necessary subworkspace nil))
	    finally
	      (reclaim-gensym-list subworkspace-list)))
    (unless kb-workspace-already-subworkspace?
      (let* ((inhibit-updating-module-related-frame-notes-for-all-workspaces?
	       (and (null (parent-of-subworkspace? kb-workspace)) ; => top-level-p
		    ;; This condition added as part of a fix for HQ-2273578:
		    ;; "unrecoverably inconsistent modularization".  When
		    ;; making a unmodularized top-level workspace a subworkspace,
		    ;; update-module-related-frame-notes-for-all-workspaces will
		    ;; not update frame notes unless inhibit-updating-module-
		    ;; related-frame-notes-for-all-workspaces? is true.  (ghw 11/20/98)
		    (null (frame-has-note-p
			    kb-workspace 'workspace-does-not-belong-to-any-module)))))
					; transferring a subworkspace cannot have
					;  any impact on modularity; unless it's
					;  a top-level workspace, suppress
					;  all frame notes activity around
					;  the incremental steps
	;; Remove the subworkspace's old parent and add the new.
	(remove-as-subworkspace-if-necessary kb-workspace nil)
	(add-subworkspace kb-workspace entity)))))



;;; `Subworkspace-currently-being-deleted?' is normally bound to nil.  However,
;;; in the recursive descent of delete-frame called by the reclaimer for
;;; subworkspaces, it is bound to the subworkspace being deleted.  The intended use for this
;;; is so that module frame note checking can be skipped in this case.

(defvar subworkspace-currently-being-deleted? nil)

(def-slot-value-reclaimer subworkspaces (subworkspaces entity)
  (setf (subworkspaces entity) nil)
  (loop with reference-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	for subworkspace in subworkspaces
	when (frame-has-not-been-reprocessed-p subworkspace reference-serial-number)
	  do (setf (parent-of-subworkspace? subworkspace) nil)
	     (let ((subworkspace-currently-being-deleted? subworkspace))
	       (delete-frame subworkspace))
	finally (reclaim-frame-serial-number reference-serial-number))
  (reclaim-slot-value-list subworkspaces))


;; Seeing that the parent-of-subworkspace? slot putter had finally been reduced
;; to the equivalent of a noop, apart from some development bug checking code,
;; I've flushed the definition.  The development code was not providing much
;; value really.  The thing it used to do, call add-subworkspace when entity?
;; was non-nil and when loading from a KB, is now done by the
;; initialize-after-reading method for workspaces.  That had to be done because
;; doing it in the slot putter was first of all evil -- it set slots before the
;; frame was all read in -- and second of all causing a real bug, namely that
;; transient subworkspaces saved in snapshots would always be made permanent
;; when read back in. (MHD 8/29/94)

;; (def-slot-putter parent-of-subworkspace?
;;                  (workspace entity? initializing?)
;;   #+development
;;   (test-assertion (if entity? initializing?))   ; See note below.
;;   (setf (parent-of-subworkspace? workspace) entity?))
;;
;; ;; Note: It is assumed that this will be invoked only while initializing
;; ;; workspace, and then, only in the KB loading case, not in the clone or
;; ;; creation cases.  Note that parent-of-subworkspace? has the do-not-clone
;; ;; feature, and is not specially handled by clone-frame.  The subworkspaces slot
;; ;; (on entities), on the other hand, is specially handled, namely by calling
;; ;; add-subworkspace.
;;
;; ;; This was fixed up to set the slot propertly, to return its value, and
;; ;; to assert that it can only be called with a non-nil ENTITY? arg when
;; ;; loading a KB.  We think that could only happen when reading an old
;; ;; KB created before 3.0 -- in 3.0 saved KBs, this fixing up isn't really
;; ;; necessary.  (MHD/ML 3/27/91)


(def-slot-value-reclaimer parent-of-subworkspace?
			  (parent-of-subworkspace? subworkspace)
  (if (framep parent-of-subworkspace?)			; this test is redundant
      (remove-as-subworkspace-if-necessary subworkspace)))

;; The parent-of-subworkspace? slot of a workspace is defined in module KB-FRAMES.



;;; `disallow-connection-subworkspaces'
;;; Connections were once entities and could,
;;; through configurations, have obtained
;;; a subworkspace.  This function will
;;; convert such a subworkspace to a top-level
;;; workspace that is contained within the same
;;; module as the connection.

(defun disallow-connection-subworkspaces (workspace connection-frame)
  (setf (module-this-is-part-of? workspace)
	(get-module-block-is-in connection-frame))
  (setf (parent-of-subworkspace? workspace) nil)
  ;;inform the operator of the change and lift to top
  )

;;; The `initialize-after-reading method for kb-workspace' handles the side
;;; effects that must accompany the setting of the parent-of-subworkspace? slot
;;; to a non-nil value a frame being restored from a KB, i.e., the adding of a
;;; subworkspace.  This is where the call to add-subworkspace happens when restoring
;;; an workspace that's a subworkspace from a KB.
;;;
;;; When an instance of a workspace becomes a subworkspace during cloning, the
;;; function clone-frame calls add-subworkspace.
;;;
;;; When an existing instance of a workspace is added as a subworkspace of
;;; an existing instance of an entity, i.e., at runtime, it is done by calling
;;; add-subworkspace directly.

(def-class-method initialize-after-reading (workspace)
  (funcall-superior-method workspace)

  (compute-workspace-caches-after-reading workspace)

  (let ((parent (parent-of-subworkspace? workspace)))
    (when (framep parent)
      (frame-class-case parent
	(entity
	  (add-subworkspace workspace parent))
	(connection
	  (disallow-connection-subworkspaces workspace parent)))))
  (unless (workspace-background-images-are-centered-p)
    (mark-background-image-coordinates-as-needing-update workspace)))





;;;; Icon Attributes



;;; The `icon attributes plist' may have the following properties
;;;
;;;        reflection-and-rotation   ; nil for normal
;;;
;;;        x-magnification           ; magnifies current-image-x(y)-scale;
;;;        y-magnification           ;   overrides icon-x(y)-magnification?
;;;
;;;        line-color
;;;
;;;        highlight-color           ; takes precedence over background color, and results
;;;				     ;   in false color for icon lines and fill
;;;
;;;	   icon-color-pattern        ; an alist of (color-region . color)
;;;                                  ;   using slot-value conses -- overrides
;;;                                  ;   icon-color-pattern? slot
;;;
;;;        width                     ; override width(height)-of-icon slots
;;;        height                    ;   of icon-description
;;;
;;;
;;;        selection-actions         ; ????  user-input-action-bindings?
;;;
;;; The icon attributes plist should only be changed using change-icon-attribute,
;;; defined below.  All strings and conses (to all levels) contained in an icon
;;; attributes plist must be unshared.  They are reclaimed upon deletion or upon
;;; a change via change-icon-attribute.



;;; The actual line color for a line drawing element is determined
;;; by (in order of priority):
;;;
;;;    (1) a color explicitly specified in the element (via the icon-color-
;;;        pattern);
;;;
;;;    (2) a line-color property in the icon attributes plist, if any;
;;;
;;;    (3) the icon-line-color? slot in the icon description, if specified; or
;;;
;;;    (4) the value of special variable current-default-line-color.





;;; `Change-icon-attribute' makes the icon attributes plist of entity have the property
;;; specified by indicator and value? or, if value? is nil, not have a property under
;;; indicator.  Strings and conses making up the structure are recycled as necessary.
;;; Slot value consing is done as necessary.  Value? is returned after being stored.
;;; Value? is NOT copied.

(defun change-icon-attribute (entity indicator value?)
  (note-change-to-block entity 'icon-attributes-plist)
  (loop with icon-attributes-plist
	  =  (icon-attributes-plist entity)
	as l-trailer? = nil then (cdr l)
	as l = icon-attributes-plist
	     then (cdr l-trailer?)
	while l
	when (eq (car-of-cons l) indicator)
	  do (cond
	       (value?
		(reclaim-slot-value (second-of-cons l))
		(setf (second-of-cons l) value?))
	       (t (if l-trailer?
		      (setf (cdr-of-cons l-trailer?) (cdr (cdr-of-cons l)))
		      (setf (icon-attributes-plist entity) (cddr l)))
		  (setf (cddr l) nil)
		  (reclaim-slot-value l)))
	     (return value?)
	finally
	  (if value?
	      (setf (icon-attributes-plist entity)
		    (slot-value-cons
		      indicator
		      (slot-value-cons
			value?
			icon-attributes-plist))))
	  (return value?)))


#+development
(defun check-for-icon-attributes-plist-slot-init-form ()
  ;; code to be written and put in g2-final
  ;; took this code out of change-icon-attribute for efficiency reasons
  ;;(let ((class-description (class-description-slot entity))
  ;;	(slot-description
  ;;	  (get-slot-description-of-class-description
  ;;	    'icon-attributes-plist class-description))
  ;;	(slot-init-form
  ;;	  (slot-init-form slot-description)))
  ;;   (if (and icon-attributes-plist
  ;;	     (eq slot-init-form icon-attributes-plist))
  ;;	(setf (icon-attributes-plist entity)
  ;;	      (setq icon-attributes-plist	; used again below
  ;;		    (copy-for-slot-value
  ;;		      icon-attributes-plist)))
  ;; Above logic added today.  Identical logic added to
  ;;   change-text-box-property, also. (MHD 9/11/89)
  ;; consider abstracting this as
  ;;   (copy-slot-value-if-defaulted
  ;;     entity 'icon-attributes-plist)
  )




;;;; Line Drawing Description Accessor (relative to entities)


(defmacro default-color-pattern-of-entity (entity)
  `(or (icon-color-pattern? (icon-description ,entity))
       '((foreground . foreground))))

(defun-simple current-color-pattern-of-entity (entity)
  (or (getfq (icon-attributes-plist entity) 'icon-color-pattern)
      (default-color-pattern-of-entity entity)))


(defmacro get-workspace-foreground-color-for-entity-if-any (entity)
  `(let ((workspace? (get-workspace-if-any ,entity)))
     (if workspace? (workspace-foreground-color? workspace?))))

(defun-simple current-line-color-of-entity (entity)
  (or (getfq (icon-attributes-plist entity) 'line-color)
      (or (icon-line-color? (icon-description entity))
	  (get-workspace-foreground-color-for-entity-if-any entity)
	  current-default-line-color)))

(defun-simple get-polychrome-header-from-entity-if-any (entity)
  (let ((icon-description? (icon-description entity)))
    (if icon-description?
	(get-polychrome-header-if-any
	  (icon-line-drawing-description icon-description?)))))



;;; `Polychrome-icon-p' is true if the given entity is a polychrome icon.  (This
;;; is also documented above.)

(defun-simple polychrome-icon-p (entity)
  (get-polychrome-header-from-entity-if-any entity))



;;; The function `monochrome-icon-p' is true if the given entity is entirely of
;;; one color.  Either it has no regions, or all of its region have the same
;;; color, FOREGROUND.

(defun-simple monochrome-icon-p (entity)
  (let ((header? (get-polychrome-header-from-entity-if-any entity)))
    (or (null header?)
	(loop for (region . color) in (cdr header?)
	      always (and (eq region 'foreground)
			  (eq color 'foreground))))))


;;; The function `multichrome-icon-p' is true if the given entity's icon
;;; description is polychrome and has a region named ICON-COLOR.  Persumably,
;;; in 4.0 all icon descriptions are polychrome, so this predicate is true for
;;; those magic icons which have a specific region which represents "the color
;;; of the item".

(defun-simple multichrome-icon-p (entity)
  (let ((header? (get-polychrome-header-from-entity-if-any entity)))
    (when header?
      (loop for (region . color) in (cdr header?)
	    thereis (eq region 'icon-color)))))


(defun-simple single-color-entity-p (entity)
  (null (cdr (cdr (get-polychrome-header-from-entity-if-any entity)))))







;;;; Making Entities




;;; `External-simulation-p' is a property of entities that allows them to
;;; receive values from GSPAN and other data sources.


(defmacro external-simulation-p (entity)
  `(get-property-value-in-object-configuration ,entity 'external-simulation nil))




;;; The initialize method for entity calls install-externally-simulated-entity
;;; if the entity is simulated externally.  As with the slot putter for
;;; output-vector-from-external-simulator, this is a forward installation from
;;; the standpoint of the variables affected.

;(def-class-method initialize (entity)
;  (funcall-superior-method entity)
;  (when (external-simulation-p entity)
;    (install-externally-simulated-entity entity)))

;; The external-simulation-p check is actually not necessary but does
;; improve efficiency.

;; Removing GSPAN from the product entirely improves efficiency even more.
;; Removing the initialize method for entity improves make-frame speed by 25%,
;; because of the slowness of the external-simulation-p check. -jra 5/10/95




;;; The `initialize-after-reading method for entity' ensures that the block
;;; edges of each entity are consistent with its icon description, which may
;;; have changed since the KB was saved.
;;;
;;; Changes in user-defined classes would normally be handled without this
;;; method, but this handles system-defined classes, and is harmless for
;;; user-defined classes, or classes that have no inconsistencies.
;;;
;;; [Also, there were bugs in earlier versions (prior to 8/4/89) that prevented
;;; edges of user-defined class instances to be properly updated when changes
;;; were made. (MHD 8/8/89)]
;;;
;;; This method also moves the line-color of entities with the new sysicons
;;; into the color of the icon-color region.  Previously, the line-color was
;;; kept around, and kludgey defaults in drawing endeavored to make it be the
;;; default color for the icon-color region. Unfortunately, since many 4.0 KBs
;;; have been saved out with the line colors sotred in the wrong place, we
;;; have to update in all cases. -fmw, 1/29/95

(def-class-method initialize-after-reading (entity)
  (funcall-superior-method entity)	; per convention
  (bring-block-edges-in-synch-with-icon-description entity))

(defun transformed-edges-of-entity (entity use-managed-floats-p)
  (let ((icon-description? (icon-description entity)))
    (when icon-description?
      (let* ((icon-attributes-plist (icon-attributes-plist entity))
	     (width-of-icon
	       (or (when icon-attributes-plist
		     (getf icon-attributes-plist 'width))
		   (width-of-icon icon-description?)))
	     (height-of-icon
	       (or (when icon-attributes-plist
		     (getf icon-attributes-plist 'height))
		   (height-of-icon icon-description?)))
	     (x-magnification?
	       (or (when icon-attributes-plist
		     (getf icon-attributes-plist 'x-magnification))
		   (icon-x-magnification? icon-description?)))
	     (y-magnification?
	       (or (when icon-attributes-plist
		     (getf icon-attributes-plist 'y-magnification))
		   (icon-y-magnification? icon-description?)))
	     (width-of-icon-after-magnification
	       (if x-magnification?
		   (if use-managed-floats-p
		       (magnify-as-number width-of-icon x-magnification?)
		       (magnify width-of-icon x-magnification?))
		   width-of-icon))
	     (height-of-icon-after-magnification
	       (if y-magnification?
		   (if use-managed-floats-p
		       (magnify-as-number height-of-icon y-magnification?)
		       (magnify height-of-icon y-magnification?))
		   height-of-icon))
	     (rotated-by-90-p
	       (and icon-attributes-plist
		    (rotated-by-90-p
		      (getf icon-attributes-plist 'reflection-and-rotation)))))
	(if rotated-by-90-p
	    (values height-of-icon-after-magnification width-of-icon-after-magnification)
	    (values width-of-icon-after-magnification height-of-icon-after-magnification))))))

(defun bring-block-edges-in-synch-with-icon-description (entity)
  (let ((icon-description? (icon-description entity)))
    (when icon-description?
      (multiple-value-bind (width-of-icon-after-transformations height-of-icon-after-transformations)
	  (transformed-edges-of-entity entity nil)
	(let* ((icon-attributes-plist (icon-attributes-plist entity))
	       (width-of-block (width-of-block entity))
	       (height-of-block (height-of-block entity)))
	  (when (or (not (=w width-of-icon-after-transformations
			     width-of-block))
		    (not (=w height-of-icon-after-transformations
			     height-of-block)))
	    (magnify-icon
	      entity
	      (or (getf icon-attributes-plist 'x-magnification)
		  (icon-x-magnification? icon-description?))
	      (or (getf icon-attributes-plist 'y-magnification)
		  (icon-y-magnification? icon-description?))
	      nil nil nil))


	  ;; A bug in fix-icon-description-for-class-slot sometimes introduced
	  ;; icon color patterns which look like ((nil) (icon-color blue)) into
	  ;; KB's which were saved in G2 before 2/10/95.  Remove the NIL's
	  ;; here. -fmw, 2/10/95
	  (let ((instance-color-pattern?
		  (and icon-attributes-plist
		       (getfq icon-attributes-plist 'icon-color-pattern))))
	    (when (loop for pair? in instance-color-pattern?
			thereis (null pair?))
	      (let ((new-color-pattern
		      (loop for pair? in instance-color-pattern?
			    when pair?
			      collect (copy-tree-using-slot-value-conses ; Paranoia.
					pair?)
				using slot-value-cons)))
		(change-icon-attribute entity 'icon-color-pattern new-color-pattern)
		(setq instance-color-pattern? new-color-pattern)))

	    ;; Icon description can change between releases.  If this is a
	    ;; different revision (including a different release), then check
	    ;; patterns that don't work for the new icon description (that's in
	    ;; the image).  We can restrict our dealings to 4.0 entities, which
	    ;; always are polychrome. If we find that a pattern is not in synch
	    ;; with the definition, we change it. (MHD 8/18/95)
	    (when (and instance-color-pattern?
		       (system-defined-class-p (class entity))
		       (system-revision-greater-p
			 system-version-of-current-gensym-product-line
			 system-version-from-kb-being-read))
	      (let ((default-color-pattern
			(get-color-pattern-of-item entity 'default nil t)))
		(unless (and (loop for (region) in default-color-pattern
				   always (assq region instance-color-pattern?))
			     (loop for (region) in instance-color-pattern?
				   always (assq region default-color-pattern)))
		  (loop for (region . default-color) in default-color-pattern
			collect (slot-value-cons
				  region
				  (or (cdr (assq region instance-color-pattern?))
				      default-color))
			  into new-instance-color-pattern using slot-value-cons
			finally
			  (change-icon-attribute
			    entity 'icon-color-pattern
			    new-instance-color-pattern)
			  (setf instance-color-pattern?
				new-instance-color-pattern)))
		(reclaim-slot-value default-color-pattern))))


	  ;; Move the line-color of sysicons to the icon-color region.  This is
	  ;; the fix for HQ-176736 "Icon color change lost after moving".  We
	  ;; have to correct in all cases, since many 4.0 Kbs have been saved
	  ;; with the color of the icon-color region stored in the line-color
	  ;; property. -fmw, 1/29/95
	  (when (and ; (loading-version-3-or-earlier-kb-p)
		  (multichrome-icon-p entity)		    ; Has an icon-color region.
		  icon-attributes-plist
		  (getfq icon-attributes-plist 'line-color))

	    (let* ((line-color
		     (getfq icon-attributes-plist 'line-color))
		   (class-color-pattern?
		     (icon-color-pattern? icon-description?))
		   (instance-color-pattern?
		     (getfq icon-attributes-plist 'icon-color-pattern)))

	      (cond (instance-color-pattern?
		     ;; If it has an instance color pattern, that takes precedence.
		     ;; However, I don't think this case can happen while loading
		     ;; a 3.0 KB.
		     )
		    (t
		     ;; If has no instance color pattern, make one, and put the
		     ;; line-color in as the color of region ICON-COLOR.
		     ;;
		     ;; Then, too, do special handling for "invisible" icons as
		     ;; follows: if the line color was TRANSPARENT, then assume
		     ;; the icon was meant to be invisible, and preserve that
		     ;; property by moving TRANSPARENT in as the metacolor for
		     ;; every (new) named region. Note that this heuristic was not
		     ;; applied until 4.0 Rev. 1. Note that all icon descriptions
		     ;; for built-in icons were changed for Rev. 1 to have all
		     ;; named regions, to achieve this desired effect, although
		     ;; the code below doesn't absolutely assume that. [AKA the
		     ;; "Storm Integration Fix" for Rev. 1] (MHD 8/16/95)
		     (let ((new-instance-color-pattern
			     (loop for (region . color) in class-color-pattern?
				   as new-color = (if (or (and (not (eq line-color region))
							       (eq line-color 'transparent))
							  (eq region 'icon-color))
						      line-color
						      color)
				   collect (slot-value-cons region new-color)
				     using slot-value-cons)))

		       (set-icon-colors
			 entity nil new-instance-color-pattern nil))))

;            ;; Discard the line-color if not used, namely, if there is no
;            ;; region named FOREGROUND.
;            (unless (icon-has-region-p entity 'foreground)
;              (change-icon-attribute entity 'line-color nil))

	      ;; Instead, discard the line color if it's been moved to the
	      ;; color pattern.  It's to remain otherwise, since it has semantic
	      ;; information, not just visual information. (See definitions
	      ;; elsewhere.)  Note that class definition changes result in
	      ;; icon-color being reinitialized.
	      (when (icon-has-region-p entity 'icon-color)
		(change-icon-attribute entity 'line-color nil))))
	  )))))



;;; `Make-entity' is a specialization of make-frame which is used to make
;;; entities. Unlike make-frame, make-entity calls `set-up-icon-for-entity' to
;;; set up block edges, create connection stubs, create attribute displays, etc.
;;; If maybe-defer-slot-group?, no stubs or block edges are set up, and the case
;;; of special-stubs-handling? = :NO-STUBS is ignored.  Otherwise,
;;; special-stubs-handling? does apply, i.e., for the :TRANSIENT case, with
;;; effects as documented for set-up-icon-for-entity, q.v.

(defun make-entity (subclass-of-entity
		     &optional special-stubs-handling? maybe-defer-slot-group?)
  (make-entity-of-class-description
    (class-description subclass-of-entity)
    special-stubs-handling? maybe-defer-slot-group?))

(defun-simple make-entity-of-class-description
    (class-description special-stubs-handling? maybe-defer-slot-group?)
  (let ((entity (make-frame-of-class-description class-description)))
    (unless (and maybe-defer-slot-group?
		 (slot-group-may-be-deferred-for-entity entity))
      (set-up-icon-for-entity entity special-stubs-handling?))
    entity))




;;; In some cases, we will want to defer any creation of a slot group, for
;;; example when an entity is being created as a transient item or as an
;;; attribute.  However, if attribute displays or stubs are called for by the
;;; class definition, then this initialization should not be deferred.  The
;;; function `slot-group-may-be-deferred-for-entity' is used to detect these
;;; cases.  In general, it may be deferred when the only function of the slot
;;; group is to store the magnitudes of the edges, magnifications, and
;;; rotations.  Currently, attributes never have the slot group set up (which is
;;; potentially a bug due to the lack of stubs), and transient items always have
;;; it set up.  This function is being added to help us eliminate slot groups
;;; from some transient items.  -jra 1/26/95

(defun-simple slot-group-may-be-deferred-for-entity (entity)
  (let* ((class-description (class-description-slot entity))
	 (attribute-displays-class-feature?
	   (get-class-feature-in-class-description-if-any
	     class-description 'attribute-displays))
	 (stubs-class-feature?
	   (get-class-feature-in-class-description-if-any
	     class-description 'stubs)))
    (and (or (null stubs-class-feature?)
	     (eq (cdr stubs-class-feature?) 'none))
	 (or (null attribute-displays-class-feature?)
	     (eq (cdr attribute-displays-class-feature?) 'none))
	 (null (let ((icon-attributes-plist? (icon-attributes-plist entity)))
		 (when icon-attributes-plist?
		   (getf icon-attributes-plist? 'reflection-and-rotation)))))))




;;; The function `perform-any-deferred-icon-set-up' takes items and sets up the
;;; icon-slot-group if the given item is an entity and has had its
;;; set-up-icon-for-entity call deferred.

(defun-void perform-any-deferred-icon-set-up (item)
  (when (and (entity-p item)
	     (null (slot-group-for-block? item)))
    (set-up-icon-for-entity item)))

(defun line-drawing-description-is-opaque-p
    (line-drawing-description default-variables computed-values-plist icon-width icon-height)
  (declare (ignore #-development line-drawing-description
		   default-variables computed-values-plist icon-width icon-height))
  ;(evaluating-icon-elements (icon-width icon-height default-variables computed-values-plist)
  nil)

(defun image-covers-icon (image-drawing-element entity)
  (let* ((icon-description (icon-description entity))
	 (icon-width (width-of-icon icon-description))
	 (icon-height (height-of-icon icon-description))
	 (image-data
	   (find-image-data
	     (image-drawing-element-image-name image-drawing-element))))
    (and image-data
         (let* ((image-width (image-data-width image-data))
                (image-height (image-data-height image-data))
                (image-coordinates
                 (third image-drawing-element))
                (image-x-shift
                 (or (car image-coordinates) 0))
                (image-y-shift
                 (or (second image-coordinates) 0)))
           ;; doesn't take into account power-points
           (and (=f (image-data-transparent-color-index image-data) -1)
                (<f image-x-shift 1)
                (<f image-y-shift 1)
                (>f (+f image-width image-x-shift) icon-width)
                (>f (+f image-height image-y-shift) icon-height))))))

(defun background-layer-covers-icon (background-layer? entity)
  (or (not (image-drawing-element-p background-layer?))
      (image-covers-icon background-layer? entity)))

(defun valid-background-layer-p (background-layer? regions)
  (or (and (image-drawing-element-p background-layer?)
	   (find-image-data (second background-layer?)))
      (valid-region-or-color-p background-layer? regions)))

(defun valid-region-or-color-p (region-or-color? regions)
  (and (symbolp region-or-color?)
       (or (gensym-color-p region-or-color?)
	   (gensym-color-p
	     (cdr (assq region-or-color? regions))))))

(defun entity-is-opaque-p (entity)
  (let* ((icon-description (icon-description entity))
	 (line-drawing-description
	   (icon-line-drawing-description icon-description))
	 (icon-attributes-plist
	   (icon-attributes-plist entity))
	 (computed-values-plist
	   (get-computed-values-plist icon-attributes-plist))
	 (default-variables (cdr (get-variable-specification-if-any
				   line-drawing-description)))
	 (icon-color-pattern?
	   (icon-color-pattern? icon-description))
	 (regions
	   (if icon-color-pattern?
	       (or (if icon-attributes-plist
		       (getfq icon-attributes-plist 'icon-color-pattern))
		   icon-color-pattern?)))
	 (background-layer
	   (icon-description-background-image icon-description))
	 (result
	   (or (and (valid-background-layer-p background-layer regions)
		    (background-layer-covers-icon background-layer entity))
	       (line-drawing-description-is-opaque-p
		 line-drawing-description
		 default-variables
		 computed-values-plist
		 (width-of-icon icon-description)
		 (height-of-icon icon-description)))))
    result))


;;; `Set-up-icon-for-entity' sets up entity, if necessary, to have its
;;; right-edge-of-block and bottom-edge-of-block slots to the width and height
;;; of the icon respectively, taking into account rotation, reflection, and
;;; magnification, as well as to create connections and attribute displays.
;;;
;;; If special-stubs-handling? is nil, then stubs are created normally.  If it's
;;; :TRANSIENT, they're made transient.  If it's :NO-STUBS, then no stubs are
;;; created.

;;; If (slot-group-for-block? entity) is null, this does the work; otherwise,
;;; the work is assumed to have been done already, so this does nothing.

(defun set-up-icon-for-entity (entity &optional special-stubs-handling?)
  ;; Check for old calling sequence in development. The second arg used to be
  ;; make-stubs-transient?  (t/nil). (MHD 1/21/05).
  #+development
  (when (and special-stubs-handling?
	     (not (memq special-stubs-handling?
			'(:transient :no-stubs))))
    (cerror "continue anyway"
	    "Unrecognized value for second arg special-stubs-handling?: ~s~
            ~%  It should be nil, :NO-STUBS, or :TRANSIENT.~
            ~%  (Note: argument was changed Jan. '05.)"
	    special-stubs-handling?))
  (when (null (slot-group-for-block? entity))
    (let ((icon-description? (icon-description entity))
	  (icon-attributes-plist? (icon-attributes-plist entity)))
      (when icon-description?
	(when (entity-is-opaque-p entity)
	  (set-opaque-block entity))
	(let ((class-description (class-description-slot entity)))
	  (when (not (frame-of-class-p entity 'connection))
	    ;; set right & bottom edges (all edges assumed to be zero initially)
	    ;; It is these non-default values which cause EVERY entity to allocate
	    ;; a slot-group-for-block.  A pity.
	    (let* ((width
		     (or (if icon-attributes-plist?
			     (getf icon-attributes-plist? 'width))
			 (width-of-icon icon-description?)))
		   (height
		     (or (if icon-attributes-plist?
			     (getf icon-attributes-plist? 'height))
			 (height-of-icon icon-description?))))
	      ;; This assumes that left & top are 0 now.
	      (change-edges-of-block entity nil nil width height)))

	  ;; Make stubs, unless special-stubs-handling? is :NO-STUBS, and have
	  ;; them be transient if special-stubs-handling? is :TRANSIENT.
	  (unless (eq special-stubs-handling? ':no-stubs)
	    (let ((stub-specs?
		    (cdr (get-class-feature-in-class-description-if-any
			   class-description 'stubs))))
	      (when (and stub-specs?
			 (not (eq stub-specs? 'none))
			 (null (parent-frame entity))
			 (null (parent-attribute-name entity)))
		(make-stubs
		  entity stub-specs?
		  (eq special-stubs-handling? ':transient)))))

	  ;; Magnify if needed.
	  (let ((x-magnification?
		  (or (if icon-attributes-plist?
			  (getf icon-attributes-plist? 'x-magnification))
		      (icon-x-magnification? icon-description?)))
		(y-magnification?
		  (or (if icon-attributes-plist?
			  (getf icon-attributes-plist? 'y-magnification))
		      (icon-y-magnification? icon-description?))))
	    (when (or x-magnification? y-magnification?)
	      (change-edges-of-block
		entity
		nil nil
		(if x-magnification?
		    (magnify (width-of-block entity) x-magnification?))
		(if y-magnification?
		    (magnify (height-of-block entity) y-magnification?)))
	      ;; ... left & top edges (still) assumed to be 0.
	      (when (connections entity)		; optimization
		(magnify-connections-on-block-in-workspace
		  entity x-magnification? y-magnification? nil nil 0 0 0 0))))

	  ;; reflect/rotate
	  (let ((reflection-and-rotation?
		  (if icon-attributes-plist?
		      (getf icon-attributes-plist? 'reflection-and-rotation))))
	    (when reflection-and-rotation?
	      (let ((x-center-of-entity (halfw (width-of-block entity)))
		    (y-center-of-entity (halfw (height-of-block entity))))
		(change-icon-attribute entity 'reflection-and-rotation nil)
		(reflect-and-rotate-loose-ends-of-block-in-workspace
		  entity reflection-and-rotation?
		  x-center-of-entity y-center-of-entity)
		(reflect-and-rotate-block-in-workspace
		  entity reflection-and-rotation?
		  x-center-of-entity y-center-of-entity))))

	  ;; make attribute displays   -- new. (MHD 6/11/91)
	  (let ((attribute-display-specs?
		  (cdr (get-class-feature-in-class-description-if-any
			 class-description 'attribute-displays))))
	    (when attribute-display-specs?
	      (unless (or (eq attribute-display-specs? 'none)
			  called-within-clear-text-loading)
		(make-attribute-displays-per-specs
		  entity attribute-display-specs?)))))))))

;; This is usually only called from make-entity, where it used to be inline.
;; It is now also called from handle-choice-for-block-menu when handling the
;; transfer-original menu choice.  It was newly abstracted today.  (MHD 7/18/92)

;; Note that to make transient entities usually save space occupied by slot-
;; group-for-block, we should (1) make the defaults when READ be correct and
;; (2) have make-icon-slot-group call this to initialize slots.  (I think that
;; will do it, but it needs more review.)  (MHD 7/13/92)

;; Adding

;; To be able to do this with an initialize method, we have to deal with the
;; :TRANSIENT case of special-stubs-handling?  arg used above.  In practice,
;; this is only called that way when called from make-transient-item (one
;; place).  You could get rid of the arg by having an extra arg to make-frame,
;; transient?.  That bit of information could then be passed on to the
;; initialize method, either by a required extra arg or by setting the transient
;; flag in the frame before calling the initialize method.  AND you have to deal
;; with the fact that some callers just want to create these things without any
;; graphic junk in them, e.g. instantiate-variable and
;; instantiate-object-in-attribute!  (MHD 4/3/91)

;; HAVE MAKE-FRAME DO ALL THIS FOR THE ENTITY CASE!!!

;; Have to magnify before rotating rather than after
;; (makes a difference if x and y scales are different)



;;; `Make-entity-with-specific-icon-description' makes an entity of class
;;; subclass-of-entity with an entity-specific icon description based on the
;;; other arguments.  The icon line color, x and y magnifications, and x and y
;;; offsets for fine positioning are all defaulted to nil; of these, only line-
;;; color? may currently be supplied.

;;; It is assumed that the entity has no icon attributes or stub specifications.
;;; Subclass-of-entity should not be a user-defined class.  Icon-line-drawing-description
;;; must be a slot value (with unshared conses).

;;; An entity with an entity-specific icon description must never be saved in
;;; a saved kb.  See also the definition of entity and icon description.

(defun make-entity-with-specific-icon-description
       (subclass-of-entity
	icon-line-drawing-description width-of-icon height-of-icon
	&optional icon-color? icon-background-image?)
  #+development
  (check-memory-for-development 'make-entity-with-specific-icon-description_1)
  (let ((icon-description
	  (create-icon-description
	    width-of-icon height-of-icon icon-line-drawing-description))
	entity)
    (setf (icon-description-background-image icon-description)
	  icon-background-image?)
    (setf entity (make-entity subclass-of-entity))
    (setf (icon-description entity) icon-description)

    (set-edges-of-block entity 0 0 width-of-icon height-of-icon)

    (when icon-color?
      (setf (icon-line-color? icon-description) icon-color?))

    #+development
    (check-memory-for-development 'make-entity-with-specific-icon-description_2)
    entity))







;;;; Rubber Stamp Widgets



;;; Rubber-stamp-widgets are graphics, described using icons, that can be
;;; drawn onto the screen without creating a block for each instance.  Instead
;;; a single iconic-entity-with-specific-icon-description is created for each
;;; KB, and that one is transformed and stamped out as needed.  These are used,
;;; for example to create the walking menu indicators, and scroll bar components.

;;; Rubber stamps are stored in KB specific varaibles *-rubber-stamp-widget.
;;; They are created when the KB starts up, and reclaimed when it is cleared.

;; TBD
;; Users can redefine the graphics for some of these by creating classes with
;; particular names, the icon description of those classes will then override
;; the built in graphic.


;;; `Make-iconic-entity-with-specific-icon-description' is used to create
;;; assorted rubber stamps that in turn are used to draw decorations in menus,
;;; and frames.  The orientation argument should be one of: nil, clockwise-90,
;;; clockwise-180, or clockwise-270 If rotated-p is true, then create four
;;; icons, one for each orientation.

(defun make-iconic-entity-with-specific-icon-description
    (icon-description width height rotated-p)
  (loop for orientation in   (if rotated-p
				 '(nil clockwise-90 clockwise-180 clockwise-270)
				 '(nil))
	as iconic-entity = (make-entity-with-specific-icon-description
			     'iconic-entity
			     (copy-for-slot-value icon-description)
			     width height)
	when orientation
	  do (change-icon-attribute
	       iconic-entity
	       'reflection-and-rotation
	       orientation)

	nconc (graphics-list orientation iconic-entity)))

;; I'm too paranoid to use the "normal" orientation rather than nil. - ben 2/1/94



;;; `Reclaim-rubber-stamp-widgets' just reclaims the backbone, the frames
;;; will have already been reclaimed by the frame system.

(defun reclaim-rubber-stamp-widgets (plist-of-rubber-stamp-widgets)
  (reclaim-graphics-list plist-of-rubber-stamp-widgets))



;;; `Resize-box-rubber-stamp-widget' is used as the default graphic
;;; for a frame's resize box.

(def-kb-specific-variable resize-box-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((lines (2 2) (2 14) (14 14) (14 2) (2 2))
     (lines (4 4) (4 10) (11 10) (11 4) (4 4)))
    16 16 nil)
  nil
  reclaim-rubber-stamp-widgets)





(defun make-title-bar-widget-icon-description
    (icon-description pending-icon-description? na-icon-description? width height)
  (loop for situation in '(normal pending na)
	as iconic-entity = (make-entity-with-specific-icon-description
			     'iconic-entity
			     (copy-for-slot-value
			       (case situation
				 (normal icon-description)
				 (pending (or pending-icon-description? icon-description))
				 (na (or na-icon-description? icon-description))))
			     width height)
	nconc (graphics-list situation iconic-entity)))





;;; `Close-box-rubber-stamp-widget' is used as the default graphic
;;; for a frame's close box.

(def-kb-specific-variable close-box-rubber-stamp-widget draw
  (:funcall
    make-title-bar-widget-icon-description
    ;; Normal:
    ((polychrome (black . black) (dark-gray . dark-gray) (smoke . smoke)
		 (light-gray . light-gray))
     (variables) (background-layer)
     light-gray (filled-polygon ((15 0) (15 15) (0 15) (0 0))
				((15 0) (15 15) (0 15)) ((0 15) (0 0) (15 0)))
     smoke (filled-polygon
	     ((0 0) (16 0) (14 2) (2 2) (2 14) (0 16)) ((0 0) (16 0) (14 2))
	     ((2 2) (2 14) (0 16)) ((0 0) (14 2) (2 2)) ((2 2) (0 16) (0 0)))
     dark-gray (filled-polygon
		 ((16 16) (0 16) (2 14) (14 14) (14 2) (16 0))
		 ((16 16) (0 16) (2 14)) ((14 14) (14 2) (16 0))
		 ((16 16) (2 14) (14 14)) ((14 14) (16 0) (16 16)))
     black
     (filled-polygon
       ((13 5) (5 13) (3 11) (11 3)) ((13 5) (5 13) (3 11))
       ((3 11) (11 3) (13 5)))
     (filled-polygon
       ((13 11) (11 13) (3 5) (5 3)) ((13 11) (11 13) (3 5))
       ((3 5) (5 3) (13 11))))
    ;; Pending:
    ((polychrome (black . black) (dark-gray . dark-gray) (smoke . smoke)
		 (light-gray . light-gray))
     (variables) (background-layer)
     LIGHT-GRAY (FILLED-POLYGON ((15 0) (15 15) (0 15) (0 0))
				((15 0) (15 15) (0 15)) ((0 15) (0 0) (15 0)))
     DARK-GRAY
           (FILLED-POLYGON
	     ((0 0) (16 0) (14 2) (2 2) (2 14) (0 16)) ((0 0) (16 0) (14 2))
	     ((2 2) (2 14) (0 16)) ((0 0) (14 2) (2 2)) ((2 2) (0 16) (0 0)))
     SMOKE     (FILLED-POLYGON
		 ((16 16) (0 16) (2 14) (14 14) (14 2) (16 0))
		 ((16 16) (0 16) (2 14)) ((14 14) (14 2) (16 0))
		 ((16 16) (2 14) (14 14)) ((14 14) (16 0) (16 16)))
     BLACK
     (FILLED-POLYGON ((14 6) (6 14) (4 12) (12 4)) ((14 6) (6 14) (4 12)) ((4 12) (12 4) (14 6)))
     (FILLED-POLYGON ((14 12) (12 14) (4 6) (6 4)) ((14 12) (12 14) (4 6)) ((4 6) (6 4) (14 12))))
    ;; NA: (not specified for now)
    nil
    16 16)
  nil
  reclaim-rubber-stamp-widgets)


;;; `Left-scroll-arrow-rubber-stamp-widget' is used as the default graphic
;;; for the arrows in scroll boxes.  There are also three others for
;;; other orientations.

(def-kb-specific-variable left-scroll-arrow-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((polychrome (dark-color . dark-gray)
		 (face-color . light-gray)
		 (light-color . white)
		 (border . black)
		 (arrow-color . black))
     dark-color (lines (1 19) (19 19) (19 1))
     face-color (solid-rectangle (2 2) (18 18))
     light-color  (lines (1 19) (1 1) (19 1))
     border  (outline (0 0) (0 20) (20 20) (20 0))
     arrow-color (filled-polygon ((7 10) (13 4) (13 16)) ((7 10) (13 4) (13 16))))
    21 21 nil)
  nil
  reclaim-rubber-stamp-widgets)

(def-kb-specific-variable top-scroll-arrow-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((polychrome (dark-color . dark-gray)
		 (face-color . light-gray) (light-color . white)
		 (border . black) (arrow-color . black))
     dark-color (lines (1 19) (19 19) (19 1))
     face-color (solid-rectangle (2 2) (18 18))
     light-color (lines (1 19) (1 1) (19 1))
     border (outline (0 0) (0 20) (20 20) (20 0))
     arrow-color (filled-polygon ((5 14) (11 8) (17 14)) ((5 14) (11 8) (17 14))) )
    21 21 nil)
  nil
  reclaim-rubber-stamp-widgets)

(def-kb-specific-variable right-scroll-arrow-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((polychrome (dark-color . dark-gray)
		 (face-color . light-gray)
		 (light-color . white)
		 (border . black)
		 (arrow-color . black))
     dark-color (lines (1 19) (19 19) (19 1))
     face-color (solid-rectangle (2 2) (18 18))
     light-color (lines (1 19) (1 1) (19 1))
     border (outline (0 0) (0 20) (20 20) (20 0))
     arrow-color (filled-polygon ((8 16) (8 4) (14 10)) ((8 16) (8 4) (14 10))))
    21 21 nil)
  nil
  reclaim-rubber-stamp-widgets)

(def-kb-specific-variable bottom-scroll-arrow-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((polychrome (dark-color . dark-gray)
		 (face-color . light-gray) (light-color . white)
		 (border . black) (arrow-color . black))
     dark-color (lines (1 19) (19 19) (19 1))
     face-color (solid-rectangle (2 2) (18 18))
     light-color (lines (1 19) (1 1) (19 1))
     border (outline (0 0) (0 20) (20 20) (20 0))
     arrow-color (filled-polygon ((5 8) (17 8) (11 14)) ((5 8) (17 8) (11 14))))
    21 21 nil)
  nil
  reclaim-rubber-stamp-widgets)

(def-kb-specific-variable scroll-bar-elevator-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((polychrome (face-color . light-gray) (light-color . white)
		 (dark-color . dark-gray) (border . black))
     face-color (solid-rectangle (2 2) (17 17))
     light-color (lines (1 17) (1 1) (17 1))
     dark-color (lines (1 17) (17 17) (17 1))
     border (outline (0 0) (0 18) (18 18) (18 0)))
    18 18 nil)
  nil
  reclaim-rubber-stamp-widgets)



;;; `Marker-for-cascading-menu-rubber-stamp-widget' is used to do just
;;; that.

(def-kb-specific-variable right-marker-for-cascading-menu-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((filled-polygon ((0 0) (10 5) (0 10)) ((0 0) (10 5) (0 10))))
    10 10 nil)
  nil
  reclaim-rubber-stamp-widgets)

(def-kb-specific-variable left-marker-for-cascading-menu-rubber-stamp-widget draw
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((filled-polygon ((10 0) (0 5) (10 10)) ((10 0) (0 5) (10 10))))
    10 10 nil)
  nil
  reclaim-rubber-stamp-widgets)



;;; `Rebind-rubber-stamps-to-user-icons' is called when ever the
;;; an icon description is put into a class named one of the
;;; names that users are told can be used to override a built in
;;; icon.  It reclaims all current rubber stamps and makes new ones.

;;; The chaining that fires this off on user edits has been disabled.
;;; This mechinism was not released to users.

#+not-released
(defun-void rebind-rubber-stamps-to-user-icons ()
  ;; resize-box
  (setf resize-box-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  resize-box-rubber-stamp-widget
	  'overriding-icon-for-resize-box
	  '((LINES (2 2) (2 14) (14 14) (14 2) (2 2))
	    (LINES (4 4) (4 10) (11 10) (11 4) (4 4)))
	  16 16 nil))
  ;; close-box
  (setf close-box-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  close-box-rubber-stamp-widget
	  'overriding-icon-for-close-box
	  '((LINES (2 2) (2 14) (14 14) (14 2) (2 2))
	    (LINES (4 4) (4 10) (11 10) (11 4) (4 4)))
	  16 16 nil))

  ;; scroll-arrow
  (setf left-scroll-arrow-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  left-scroll-arrow-rubber-stamp-widget
	  'overriding-icon-for-scroll-arrows
	  '((polychrome (dark-color . dark-gray)
	     (face-color . light-gray)
	     (light-color . white)
	     (border . black)
	     (arrow-color . black))
	    dark-color (lines (1 19) (19 19) (19 1))
	    face-color (solid-rectangle (2 2) (18 18))
	    light-color  (lines (1 19) (1 1) (19 1))
	    border  (outline (0 0) (0 20) (20 20) (20 0))
	    arrow-color (filled-polygon ((7 10) (13 4) (13 16)) ((7 10) (13 4) (13 16))))
	  21 21 nil))
  (setf top-scroll-arrow-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  top-scroll-arrow-rubber-stamp-widget
	  'overriding-icon-for-scroll-arrows
	  '((polychrome (dark-color . dark-gray)
	     (face-color . light-gray) (light-color . white)
	     (border . black) (arrow-color . black))
	    dark-color (lines (1 19) (19 19) (19 1))
	    face-color (solid-rectangle (2 2) (18 18))
	    light-color (lines (1 19) (1 1) (19 1))
	    border (outline (0 0) (0 20) (20 20) (20 0))
	    arrow-color (filled-polygon ((5 14) (11 8) (17 14)) ((5 14) (11 8) (17 14))))
	  21 21 nil))
  (setf right-scroll-arrow-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  right-scroll-arrow-rubber-stamp-widget
	  'overriding-icon-for-scroll-arrows
	  '((polychrome (dark-color . dark-gray)
	     (face-color . light-gray)
	     (light-color . white)
	     (border . black)
	     (arrow-color . black))
	    dark-color (lines (1 19) (19 19) (19 1))
	    face-color (solid-rectangle (2 2) (18 18))
	    light-color (lines (1 19) (1 1) (19 1))
	    border (outline (0 0) (0 20) (20 20) (20 0))
	    arrow-color (filled-polygon ((8 16) (8 4) (14 10)) ((8 16) (8 4) (14 10))))
	  21 21 nil))
  (setf bottom-scroll-arrow-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  bottom-scroll-arrow-rubber-stamp-widget
	  'overriding-icon-for-scroll-arrows
	  '((polychrome (dark-color . dark-gray)
	     (face-color . light-gray) (light-color . white)
	     (border . black) (arrow-color . black))
	    dark-color (lines (1 19) (19 19) (19 1))
	    face-color (solid-rectangle (2 2) (18 18))
	    light-color (lines (1 19) (1 1) (19 1))
	    border (outline (0 0) (0 20) (20 20) (20 0))
	    arrow-color (filled-polygon ((5 8) (17 8) (11 14)) ((5 8) (17 8) (11 14))))
	  21 21 nil))

  ;; Elevator
  (setf scroll-bar-elevator-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  scroll-bar-elevator-rubber-stamp-widget
	  'overriding-icon-for-scroll-arrows
	  '((polychrome (face-color . light-gray) (light-color . white)
	     (dark-color . dark-gray) (border . black))
	    face-color (solid-rectangle (2 2) (17 17))
	    light-color (lines (1 17) (1 1) (17 1))
	    dark-color (lines (1 17) (17 17) (17 1))
	    border (outline (0 0) (0 18) (18 18) (18 0)))
	  18 18 nil))

  ;; Cascading Menu marker
  (setf right-marker-for-cascading-menu-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	  right-marker-for-cascading-menu-rubber-stamp-widget
	  :may-not-be-overridden
	  '((filled-polygon ((0 0) (10 5) (0 10)) ((0 0) (10 5) (0 10))))
	  10 10 nil))
  (setf left-marker-for-cascading-menu-rubber-stamp-widget
	(rebind-one-rubber-stamp-to-user-icons
	 left-marker-for-cascading-menu-rubber-stamp-widget
	 :may-not-be-overridden
	 '((filled-polygon ((10 0) (0 5) (10 10)) ((10 0) (0 5) (10 10))))
	 10 10 nil)))


#+not-released
(defun rebind-one-rubber-stamp-to-user-icons (old-rubber-stamps
					       user-class-name
					       default-icon-description
					       default-width default-height
					       rotated-p)
  (declare (ignore user-class-name))
  (loop for (key iconic-entity) on old-rubber-stamps by #'cddr
	do (delete-frame iconic-entity)
	finally (reclaim-graphics-list old-rubber-stamps))
  (let ((icon-description default-icon-description)
	(width default-width)
	(height default-height))
    (let ((user-override? (get-instance-with-name-if-any
			    'class-definition
			    user-class-name))
	  icon-description-for-class?)
      (when (and user-override?
		 (frame-ok-p user-override?)
		 (setf icon-description-for-class?
		       (get-slot-value user-override? 'icon-description-for-class?)))
	(setf icon-description (cddr icon-description-for-class?))
	(setf width (first icon-description-for-class?))
	(setf height (second icon-description-for-class?))))
    (make-iconic-entity-with-specific-icon-description
      icon-description width height rotated-p)))





;;; `Draw-rubber-stamp-widget' draws the rubber stamp of the given
;;; name scaled and offset to fill the rectangle given.

(defun-void draw-rubber-stamp-widget (frame-widget-name
				       left-edge-in-workspace top-edge-in-workspace
				       right-edge-in-workspace bottom-edge-in-workspace)
  (let*
      ;; Map: name -> stamps/orientation -> entity
      ((orientation nil)
       (iconic-entity-of-widget
	 (or
	   (getf (lookup-rubber-stamp-set-of-frame-widget frame-widget-name) orientation)
	   (second resize-box-rubber-stamp-widget))))

    ;; Scale and offset the widget into this rectangle.
    (with-rectangle-scaling ((left-edge-of-block iconic-entity-of-widget)
			     (top-edge-of-block iconic-entity-of-widget)
			     (right-edge-of-block iconic-entity-of-widget)
			     (bottom-edge-of-block iconic-entity-of-widget)
			     left-edge-in-workspace
			     top-edge-in-workspace
			     right-edge-in-workspace
			     bottom-edge-in-workspace)
      (draw-icon-for-entity iconic-entity-of-widget))
    nil))

(defun lookup-rubber-stamp-set-of-frame-widget (frame-widget-name)
  (case frame-widget-name
    (right-marker-for-cascading-menu
     right-marker-for-cascading-menu-rubber-stamp-widget)
    (left-marker-for-cascading-menu
     left-marker-for-cascading-menu-rubber-stamp-widget)
    (gensym-left-scroll-arrow-frame-component
     left-scroll-arrow-rubber-stamp-widget)
    (gensym-up-scroll-arrow-frame-component
     top-scroll-arrow-rubber-stamp-widget)
    (gensym-right-scroll-arrow-frame-component
     right-scroll-arrow-rubber-stamp-widget)
    (gensym-down-scroll-arrow-frame-component
     bottom-scroll-arrow-rubber-stamp-widget)
    (gensym-resize-box-frame-component
     resize-box-rubber-stamp-widget)
    (gensym-close-box-frame-component
     close-box-rubber-stamp-widget)
    (gensym-scroll-bar-elevator-frame-component
     scroll-bar-elevator-rubber-stamp-widget)
    (t
     #+development
     (cerror "Go" "Unknown rubberstamp.")
     resize-box-rubber-stamp-widget)))


(defun change-color-in-rubber-stamp (workspace rubber-stamp-entity
				      left-edge top-edge right-edge bottom-edge
				      region-to-change old-color new-color)
  (loop
    with icon-description = (icon-description rubber-stamp-entity)
;    with line-drawing-description = (icon-line-drawing-description icon-description)
;    with polychrome-header = (car line-drawing-description)
    with icon-color-pattern = (icon-color-pattern? icon-description)
    for (region) in icon-color-pattern
    collect (if (eq region region-to-change) old-color 'black)
      into current-color-list using gensym-cons-macro
    collect (if (eq region region-to-change) new-color 'black)
      into new-color-list using gensym-cons-macro
    finally
      (let ((current-drawing-transfer-mode :xor))
	(update-images nil
		       rubber-stamp-entity workspace
		       left-edge top-edge right-edge bottom-edge
		       nil
		       'revise-icon-rendering-of-rubber-stamp
		       rubber-stamp-entity
		       left-edge top-edge right-edge bottom-edge
		       current-color-list new-color-list)
	(reclaim-gensym-list-macro current-color-list)
	(reclaim-gensym-list-macro new-color-list))))

(defun revise-icon-rendering-of-rubber-stamp
    (rubber-stamp-entity
      left-edge top-edge right-edge bottom-edge
      current-color-list new-color-list)
  (with-rectangle-scaling ((left-edge-of-block rubber-stamp-entity)
			   (top-edge-of-block rubber-stamp-entity)
			   (right-edge-of-block rubber-stamp-entity)
			   (bottom-edge-of-block rubber-stamp-entity)
			   left-edge
			   top-edge
			   right-edge
			   bottom-edge)
    (revise-icon-rendering
      rubber-stamp-entity current-color-list new-color-list nil)))







;;;; Entity Drawing





;;; `Draw-icon' looks up the icon rendering for this icon and stamps it out in the
;;; current drawing context.

;;; The first two parameters; {left, top}-edge-for-icon-in-workspace specify
;;; where to stamp it out.

;;; The next three parameters, icon-description and icon-attributes-plist,
;;; control width, height, rotation, magnification, and reflection.

;;; Finally two parameters control the color of the icon, i.e.
;;; foreground-color-difference-or-differences and
;;; background-color-value-or-values.  The background color values are passed
;;; to allow true colors to be infered given the color differences.  The
;;; routine is used both to draw icons from scratch, in which case the
;;; background color with be the same for all layers, or to change the colors
;;; of individual layers, in which case the background color is a list of the
;;; old colors for each layer.

;;; The foreground-color-difference-or-differences argument is either a list or
;;; an atom.  Each element is either an real color difference, or is the
;;; distinguished value color-meaning-transparent.

;;; The type of the color values arguments maybe either a list or a single fixnum
;;; color difference.  If the backgound color value is a list the color differences
;;; must be also be a list.

;;; We call `draw-icon-rendering' to actually stamp out the icons.  It has to
;;; be called once for each different value of the background color.

;; This is called only by DRAW-ICON-FOR-ENTITY and REVISE-ICON-RENDERING.

(defun-void draw-icon
    (left-edge-for-icon-in-workspace
      top-edge-for-icon-in-workspace
      icon-description icon-attributes-plist
      foreground-color-difference-or-differences	    ; Generalized color differences.
      background-color-value-or-values)
  (let* ((icon-rendering
	   (get-or-make-icon-rendering icon-description icon-attributes-plist))
	 (left-edge-in-window
	   (x-in-window left-edge-for-icon-in-workspace))
	 (top-edge-in-window
	   (y-in-window top-edge-for-icon-in-workspace))
	 (right-edge-in-window
	   (+r left-edge-in-window (width-of-rendering-structure icon-rendering)))
	 (bottom-edge-in-window
	   (+r top-edge-in-window (height-of-rendering-structure icon-rendering)))
	 (atomic-background-color-value?
	   (if (atom background-color-value-or-values)
	       background-color-value-or-values))
	 (color-meaning-transparent
	   (color-meaning-no-change)))
    (with-background-color-value
	(or atomic-background-color-value?
	    (first background-color-value-or-values))
      (cond
	;; If all background colors are identical, we can draw all the layers
	;; with just one call to draw-icon-rendering.
	((or atomic-background-color-value?
	     (loop for color-value in (cdr background-color-value-or-values)
		   always (=f (first background-color-value-or-values)
			      color-value)))
	 (draw-icon-rendering
	   left-edge-in-window top-edge-in-window
	   right-edge-in-window bottom-edge-in-window
	   foreground-color-difference-or-differences
	   icon-rendering))
	(T
	 ;; Otherwise, we have lists of colors values and differences.
	 ;; Call draw-icon-rendering once for each layer that changed.
	 (loop with working-color-difference-list
		 = (loop for p on foreground-color-difference-or-differences
			 collect color-meaning-transparent using slot-value-cons)
	       finally
		 (reclaim-slot-value-list working-color-difference-list)
	       for p on working-color-difference-list
	       for color-difference
		   in foreground-color-difference-or-differences
	       as remaining-background-color-values?
	          = (cdr background-color-value-or-values)
	          then (cdr remaining-background-color-values?)
	       doing
	   (unless (color-difference-is-transparent-p color-difference)
	     (setf (car p) color-difference)
	     (draw-icon-rendering
	       left-edge-in-window top-edge-in-window
	       right-edge-in-window bottom-edge-in-window
	       working-color-difference-list
	       icon-rendering)
	     (setf (car p) color-meaning-transparent))
	   (when remaining-background-color-values?
	     (set-current-background-color-value
	       (first remaining-background-color-values?)))))))))

;; This is only used in the two following functions.  Consider making it a macro to
;; gain a bit of speed.

(defmacro solid-color-background-layer-p (background-layer)
  `(and ,background-layer
	(symbolp ,background-layer)))

(defun-substitution-macro draw-background-color-for-entity
    (background-layer? line-color-or-colors?
		       left top right bottom)
  (let ((color?
	  (or (and (gensym-color-p background-layer?)
		   background-layer?)
	      (cdr (assq background-layer?
			 line-color-or-colors?)))))
    (when color?
      (draw-solid-rectangle
	left top right bottom
	(metacolor-difference color? 'background)))))


(defun draw-background-image-for-entity
    (image-data left-offset-in-workspace top-offset-in-workspace
		rotated-width-in-workspace rotated-height-in-workspace
		x-scale y-scale reflection-and-rotation
		left top right bottom
		block-is-currently-being-dragged-p)
  (let* (;(time-expired? nil)
	 (support-icon-image-painting?
	   (and (window-supports-icon-image-painting current-window)
		(window-supports-painting-this-image-data current-window image-data)))
	 (foreground-color-value
	   (if (boundp 'current-image-plane)
	       (compute-workspace-foreground-color-value current-image-plane)
	       current-foreground-color-value))
	 (clipped-left (maxr left-edge-of-draw-area left))
	 (clipped-top (maxr top-edge-of-draw-area top))
	 (clipped-right (minr right-edge-of-draw-area right))
	 (clipped-bottom (minr bottom-edge-of-draw-area bottom))
	 (x-bleed-width 1)
	 (y-bleed-width 1))
    (when (and (icp-window-p current-window)
	       (current-window-supports-image-painting)
	       support-icon-image-painting?)
      (unless (finished-transmitting-image-data-p image-data)
	;; we need to know if it was already sent ???
	(when (icp-connection-open-p current-icp-socket)
	  (send-all-image-data image-data))))
    (cond ((or block-is-currently-being-dragged-p
	       (null support-icon-image-painting?)
	       (and (icp-window-p current-window)
		    (or (not (icp-connection-open-p current-icp-socket))
			(not (finished-transmitting-image-data-p image-data)))))
	   (draw-solid-rectangle
	     left top (-f right 1) (-f bottom 1)
	     (map-to-color-value-macro 'light-grey))
	   (draw-rectangle-outline-in-window
	     (+f left 1) (+f top 1)(-f right 1) (-f bottom 1)
	     (map-to-color-value-macro 'dim-grey)
	     1 1))
	  (t
	   (unless (>=f x-scale (normalized-scale))
	     (setq x-bleed-width 2))
	   (unless (>=f y-scale (normalized-scale))
	     (setq y-bleed-width 2))
	   (draw-icon-background-image
	     image-data
	     left top
	     left-offset-in-workspace
	     top-offset-in-workspace
	     (+f rotated-width-in-workspace x-bleed-width)
	     (+f rotated-height-in-workspace y-bleed-width)
	     clipped-left clipped-top clipped-right clipped-bottom
	     x-scale y-scale
	     reflection-and-rotation
	     nil
	     foreground-color-value
	     current-background-color-value)))))



;;; The function `draw-icon-for-entity' does the drawing of the icon for entity,
;;; if any, as described in its icon-description slot.
;;;
;;; This is a draw function.  This is essentially a subfunction of the draw
;;; method for entity, and does precisely the same thing as that method except
;;; for drawing connections and subblocks of the entity.  It may be used by
;;; other draw methods that wish to do just the icon-drawing subset of what the
;;; draw method for entity does.

(defun-void draw-icon-for-entity (entity)
  (let ((icon-description? (icon-description entity)))
    (when icon-description?
      (draw-icon-from-description
	icon-description? (icon-attributes-plist entity)
	(left-edge-of-block entity)
	(top-edge-of-block entity)
	(right-edge-of-block entity)
	(bottom-edge-of-block entity)
	(block-is-currently-being-dragged-p entity)))))


;;; The function `draw-icon-from-description' draws an icon given only the icon
;;; description, attributes, and position. No actual entity instance is
;;; required.

;;; This function must be called in an on-window-with-drawing context.
;;; Normally, it should also be called in an on-image-plane context; however, it
;;; only requires the coordinate transformation from the special variables
;;; current-x-origin-of-drawing, etc, and not necessarily an actual image-plane

(defun-void draw-icon-from-description
    (icon-description icon-attributes-plist
		      block-left block-top block-right block-bottom
		      block-is-currently-being-dragged-p)
  (let* ((background-layer
	   (icon-description-background-image icon-description))
	 (background-image-spec
	   (if (and (consp background-layer) (consp (second background-layer))
		    (eq (caadr background-layer) 'editor-scaling))
	       (car background-layer)
	       background-layer))
	 (editor-scaling (unless (eq background-image-spec background-layer)
			   (cdadr background-layer)))
	 (background-image-name
	   (when (image-drawing-element-p background-image-spec)
	     (cadr background-image-spec)))
	 (background-image-x-y
	   (when (image-drawing-element-p background-image-spec)
	     (caddr background-image-spec)))
	 (background-image (find-image-data background-image-name))
	 (computed-values-plist
	   (get-computed-values-plist icon-attributes-plist))
	 (line-drawing-description
	   (icon-line-drawing-description icon-description))
	 (default-variables
	     (cdr (get-variable-specification-if-any
		    line-drawing-description)))
	 (reflection-and-rotation
	   (getfq icon-attributes-plist 'reflection-and-rotation))
	 (rotated-by-90-p
	   (rotated-by-90-p reflection-and-rotation))
	 (x-magnification? (getfq icon-attributes-plist 'x-magnification))
	 (y-magnification? (getfq icon-attributes-plist 'y-magnification))
	 (rotated-x-magnification?
	   (if rotated-by-90-p y-magnification? x-magnification?))
	 (rotated-y-magnification?
	   (if rotated-by-90-p x-magnification? y-magnification?))
	 (icon-color-pattern?			    ; Note A.
	   (icon-color-pattern? icon-description))
	 (line-color-from-plist?
	   (if icon-attributes-plist
	       (getfq icon-attributes-plist 'line-color)))
	 (icon-foreground-color?
	   (or line-color-from-plist?
	       (icon-line-color? icon-description)))
	 (line-color-or-colors?
	   ;; If the icon description was changed at run time,
	   ;; after a change-color-pattern action has been executed,
	   ;; the icon-attributes-plist might contain an obsolete
	   ;; alist, hence line-color-or-colors? might be outdated.
	   (if icon-color-pattern?
	       (or (if icon-attributes-plist
		       (getfq icon-attributes-plist 'icon-color-pattern))
		   icon-color-pattern?)
	       icon-foreground-color?))
	 (generalized-color-differences
	   (cond ((atom line-color-or-colors?)
		  (metacolor-difference
		    ;; Should this be icon-foreground-color?
		    ;; No.  We want our parent's fg color here.
		    (or line-color-or-colors? 'FOREGROUND)
		    'background))
		 (t
		  (loop for (region-name . color) in line-color-or-colors?
			as real-color = (or (if (eq color 'foreground)
						icon-foreground-color?)
					    color)
			collect (metacolor-difference real-color 'background)
			  using gensym-cons-macro))))
	 (left (x-in-window block-left))
	 (top (y-in-window block-top))
	 (right (x-in-window block-right))
	 (bottom (y-in-window block-bottom)))

    ;; When called from send-native-icon-1, current-image-plane is unbound.
    (when (boundp 'current-image-plane)
      (let ((bleeding-hack :bleeding-on-all-sides))
	(with-workspace-to-window-transform (bleeding-hack)
	  (multiple-value-bind (left-in-window top-in-window
					       right-in-window bottom-in-window)
	      (transform block-left block-top (+f 1 block-right) (+f 1 block-bottom))
	    (declare (ignore left-in-window top-in-window))
	    (setq right right-in-window
		  bottom bottom-in-window)))))
    
    (cond
      (background-image
       (evaluating-icon-elements
	 (nil nil default-variables computed-values-plist)
	 (let ((left-offset-in-workspace
		 (or (point-x background-image-x-y) 0))
	       (top-offset-in-workspace
		 (or (point-y background-image-x-y) 0))
	       (editor-x-scale (car editor-scaling))
	       (editor-y-scale (second editor-scaling))
	       (current-x-scale current-image-x-scale)
	       (current-y-scale current-image-y-scale)
	       (rotated-width-in-workspace
		 (if rotated-x-magnification?
		     (inverse-magnify (-w block-right block-left)
				      rotated-x-magnification?)
		     (-w block-right block-left)))
	       (rotated-height-in-workspace
		 (if rotated-y-magnification?
		     (inverse-magnify (-w block-bottom block-top)
				      rotated-y-magnification?)
		     (-w block-bottom block-top))))
	   (when editor-scaling
	     (setf current-x-scale
		   (scalef current-image-x-scale editor-x-scale)
		   current-y-scale
		   (scalef current-image-y-scale editor-y-scale)))
	   (setf current-x-scale
		 (if rotated-x-magnification?
		     (magnify current-x-scale
			      rotated-x-magnification?)
		     current-x-scale)
		 current-y-scale
		 (if rotated-y-magnification?
		     (magnify current-y-scale rotated-y-magnification?)
		     current-y-scale))
	   (draw-background-image-for-entity
	     background-image
	     left-offset-in-workspace top-offset-in-workspace
	     rotated-width-in-workspace rotated-height-in-workspace
	     current-x-scale current-y-scale reflection-and-rotation
	     left top right bottom
	     block-is-currently-being-dragged-p))))
      ((solid-color-background-layer-p background-layer)
       (with-background-color-value
	   current-background-color-value
	 (draw-background-color-for-entity
	   background-layer
	   line-color-or-colors?
	   left top right bottom))))
    (draw-icon
      block-left block-top
      icon-description icon-attributes-plist
      generalized-color-differences
      current-background-color-value)
    (when icon-color-pattern?
      (reclaim-gensym-list
	generalized-color-differences))))

;; A "generalized-color-difference" is either a true color difference or the
;; transparent-color-value.

;; Note A: I think that it is now true that EVERY icon-description has a
;; non-null color-pattern.  Monochrome icons, which used to not have a color
;; pattern, now have a color-pattern of ((foreground . foreground)).  The
;; result is that we always pass a list-of-color-differences to draw-icon,
;; instead of a single value.  This change broke printing.  -fmw, 11/8/94


;;; The function `draw-selected-regions-of-icon' draws from scratch only the
;;; named regions of the entity.

(defun draw-selected-regions-of-icon (entity changed-regions)
  (let ((icon-description? (icon-description entity)))
    (when icon-description?
      (let* ((icon-attributes-plist
	       (icon-attributes-plist entity))
	     (color-pattern
	       (current-color-pattern-of-entity entity))
	     (multichrome?
	       (multichrome-icon-p entity))
	     (foreground-color-difference-or-differences
	       (cond ((and (monochrome-icon-p entity)
			   (equal changed-regions '(icon-color)))
		      (metacolor-difference
			(current-line-color-of-entity entity)
			'background))
		     (t
		      (loop for (region-name . color) in color-pattern
			    as real-color = (or (if (eq color 'foreground)
						    (current-line-color-of-entity entity))
						color)
			    as region-changed? = (or (memq-macro region-name changed-regions)
						     (and (eq region-name 'foreground)
							  (not multichrome?)
							  (memq-macro 'icon-color changed-regions)))
			    as color-difference
			       = (if region-changed?
				     (metacolor-difference real-color 'background)
				     transparent-color-value)
			    collect color-difference using gensym-cons)))))
	(draw-icon
	  (left-edge-of-block entity) (top-edge-of-block entity)
	  icon-description? icon-attributes-plist
	  foreground-color-difference-or-differences
	  current-background-color-value)
	(when (consp foreground-color-difference-or-differences)
	  (reclaim-gensym-list-macro foreground-color-difference-or-differences))))))





;;; The `draw method on an entity' draws the entity on the current image plane,
;;; making icon renderings as necessary.  The icon render is stamped onto the
;;; image plane in the approprate color differences.  Any subblocks or
;;; connections are drawn after the icon.

;;; Raster size is obtained from width, height, x-scale, and y-scale.  If there
;;; is a rotation of 90 or 270, then the raster width and height are swapped as
;;; are the scalings for renderings.  The x and y magnifications from the icon
;;; attributes plist are for the non-rotated icon.  I.e. Magnifications don't
;;; have to be swapped whenever the icon is rotated.

(def-class-method draw (entity)
  (draw-icon-for-entity entity))





;;; `Revise-icon-rendering' draws revised colors for an icon, converting the
;;; icon from old-foreground-color-or-colors to new-foreground-color-or-colors
;;; and new-line-color?.  If new-line-color? is NIL, then the line-color of the
;;; entity is not chanaged

;;; It uses draw-icon to stamp out the changed layers in the icon.  The type of
;;; the two color arguments should be the same, they are either: a single
;;; color, a single meta-color, or a list of same.

;;; This function maps those color names to color differences.  It must also
;;; compute the current color values of the icon being changed.  To enable
;;; draw-icon to appropriately bind current-background-color-value (which
;;; enables true colors to be infered) it must also compute the current color
;;; values of the icon layers.

(defun revise-icon-rendering
    (entity
      old-foreground-color-or-colors
      new-foreground-color-or-colors
      new-line-color?)
  (let ((icon-description? (icon-description entity)))
    (when icon-description?
      (let* ((icon-attributes-plist (icon-attributes-plist entity))
	     (old-color-value-or-values nil)
	     (foreground-color-difference-or-color-differences nil)

	     ;; The old meaning of foreground w/in this entity. -fmw, 1/27/95
	     (old-line-color
	       (current-line-color-of-entity entity))
	     (new-line-color
	       (or new-line-color? old-line-color))
	     (current-foreground-color-value
	       (map-color-or-metacolor-to-color-value
		 old-line-color)))

	(cond
	  ((atom old-foreground-color-or-colors)
	   (let ((old-foreground-color-value
		   (map-color-or-metacolor-to-color-value
		     old-foreground-color-or-colors))
		 (new-foreground-color
		   (if (eq new-foreground-color-or-colors 'foreground)
		       new-line-color
		       new-foreground-color-or-colors)))

	     (setf foreground-color-difference-or-color-differences
		   (metacolor-difference new-foreground-color
					 old-foreground-color-or-colors))
	     (setf old-color-value-or-values old-foreground-color-value)))

	  (t
	   (loop for old-foreground-color in old-foreground-color-or-colors
		 for new-foreground-color in new-foreground-color-or-colors
		 as old-foreground-color-value
		    = (map-color-or-metacolor-to-color-value
			old-foreground-color)
		 as new-foreground-color-1
		    = (if (eq new-foreground-color 'foreground)
			  new-line-color
			  new-foreground-color)
		 as color-difference
		    = (metacolor-difference new-foreground-color-1 old-foreground-color)
		 collect color-difference
		   into foreground-color-differences
		   using gensym-cons-macro
		 collect old-foreground-color-value
		   into old-color-values
		   using gensym-cons-macro
		 finally
		   (setf foreground-color-difference-or-color-differences
			 foreground-color-differences)
		   (setf old-color-value-or-values
			 old-color-values))))

	(draw-icon
	  (left-edge-of-block entity) (top-edge-of-block entity)
	  icon-description? icon-attributes-plist
	  foreground-color-difference-or-color-differences
	  old-color-value-or-values)

	(unless (atom old-foreground-color-or-colors)
	  (reclaim-gensym-list-macro foreground-color-difference-or-color-differences)
	  (reclaim-gensym-list-macro old-color-value-or-values))))))

;; Note: This function is not called for opaque -> transparent in paint mode.
;; That is handled via a region invalidation.  See do-icon-color-revision.







(defun reflect-and-rotate-block-in-workspace
    (block reflection-and-rotation center-x center-y)
  (let ((new-reflection-and-rotation
	  (multiply-reflection-and-rotation
	    (getfq (icon-attributes-plist block) 'reflection-and-rotation)
	    reflection-and-rotation)))
    (if (memq new-reflection-and-rotation '(nil normal))
	(change-icon-attribute
	  block 'reflection-and-rotation nil)
	(change-icon-attribute
	  block 'reflection-and-rotation
	  (multiply-reflection-and-rotation
	    (getfq (icon-attributes-plist block) 'reflection-and-rotation)
	    reflection-and-rotation))))
  (reflect-and-rotate-connections-on-block-in-workspace
    block reflection-and-rotation)
  (multiple-value-bind (new-left-top-x new-left-top-y)
      (reflect-and-rotate-point-in-workspace
	(left-edge-of-block block) (top-edge-of-block block)
	reflection-and-rotation center-x center-y)
    (multiple-value-bind (new-right-bottom-x new-right-bottom-y)
	(reflect-and-rotate-point-in-workspace
	  (right-edge-of-block block) (bottom-edge-of-block block)
	  reflection-and-rotation center-x center-y)

      (change-edges-of-block block
			     (minw new-left-top-x new-right-bottom-x)
			     (minw new-left-top-y new-right-bottom-y)
			     (maxw new-left-top-x new-right-bottom-x)
			     (maxw new-left-top-y new-right-bottom-y)))))

;; This should be renamed `reflect-and-rotate-entity-in-workspace', since it
;; only applies to entities at present, and would not handle a general block!


(defun reflect-and-rotate-point-in-workspace
       (x y reflection-and-rotation center-x center-y)
  (multiple-value-bind (delta-x delta-y)
      (rotate-point-in-line-drawing-description	; do explicitly!
	reflection-and-rotation 0 0 (-w x center-x) (-w y center-y))
    (values (+w delta-x center-x) (+w delta-y center-y))))

;; This has to be called for all blocks in the workspace including loose
;; ends.  Thus, the x - y position of the loose ends as well as the end-
;; position of the loose end connections will be automatically updated
;; correctly.

;; This could be more efficient if it had to be.




;;; `Create-icon-description-if-valid' is called by user-class definition code
;;; (module DEFINITIONS) to create an icon-description for a subclass of object.
;;; If a valid description is specified, this returns a corresponding icon
;;; description structure.  Otherwise, it provides a default icon description
;;; (which is a rectangle for the given size).
;;;
;;; If there is a problem, the user is notified via notify-engineer as to the
;;; nature of the problem.
;;;
;;; The problem with this approach is that a user mistake looses the whole icon
;;; description. A better approach would be to delete only the affected piece or
;;; to restore what was.



(defun create-icon-description-if-valid
    (icon-width icon-height line-drawing-description line-color-of-icon
		icon-background-layer)
  (multiple-value-bind (ok? information-if-not-ok-or-extrema-if-ok?)
      (valid-line-drawing-description-p
	icon-width icon-height line-drawing-description nil)
    (cond
      (ok?
       (let ((new-icon-description
	       (create-icon-description
		 icon-width icon-height line-drawing-description line-color-of-icon
		 nil nil nil nil information-if-not-ok-or-extrema-if-ok?)))

	 ;; Replace information-if-not-ok-or-extrema-if-ok? with nil
	 ;; to disable region extrema optimization of icon rasters.  - AGH, 3/9/90
	 (setf (icon-description-background-image new-icon-description)
	       icon-background-layer)
	 new-icon-description))

      (t
       (cond
	 ((and (consp information-if-not-ok-or-extrema-if-ok?)
	       (symbolp (car information-if-not-ok-or-extrema-if-ok?)))
	  ;; Invalid description element encountered -- the first description
	  ;;   element encountered that was bad got returned.
	  (let ((temporary-text-string
		  (twith-output-to-text-string
		    (write-drawing-element information-if-not-ok-or-extrema-if-ok?))))
	    (notify-engineer
	      "Invalid icon description element:~%  ~a" temporary-text-string)
	    (reclaim-text-string temporary-text-string)))
	 (t
	  ;; A problem with something other than a particular description
	  ;;   element.
	  (notify-engineer
	    "This icon description is not valid for this height and width.")))
       (create-default-entity-icon-description icon-width icon-height)))))

;; Losing the whole icon description is a VERY POOR way to handle this kind of
;; problem!  Fortunately, it doesn't arise often, if at all, in practice.  (MHD
;; 4/28/94)

;; I fixed this function, which used to be in DEFINITIONS, not to leak free
;; conses when a default icon was needed by abstracting the call to the function
;; below, which I added, and which uses slot value conses, as is proper.  Then,
;; I moved this here from DEFINITIONS today, just for a bit of improved
;; modularity.  (MHD 4/28/94)



;;; `Create-default-entity-icon-description' creates a default icon description,
;;; of the given width and height, to be used as the default icon description in
;;; case of some problem with an icon description supplied by a user, or, possibly,
;;; due a G2 developer's programming error.
;;;
;;; This is derived from `default-entity-line-drawing-description-template', by
;;; substituting appropriately for :width and :height therein.  Currently, this
;;; defines the outline of a simple rectangular box, of the given width and
;;; height dimensions.
;;;
;;; The conses that make up the resulting line drawing description are
;;; slot-value conses.  Note that this function may only be used at runtime,
;;; within when there is a current KB; i.e., it cannot be used at load time when
;;; defining built-in (system-defined) classes.

(defvar default-entity-line-drawing-description-template
  '((outline (0 0) (:width 0) (:width :height) (0 :height))))

(defun create-default-entity-icon-description
    (icon-width icon-height)
  (create-icon-description
    icon-width icon-height
    (slot-value-list
      (nsubst
	icon-width :width
	(nsubst
	  icon-height :height
	  (copy-tree-using-slot-value-conses
	    default-entity-line-drawing-description-template))))))




;;;; Downloading KB-Level Icon Definitions

;;; This is a new facility for "downloading" icons created in a KB to G2 Lisp
;;; sources.  Dave Riddell (DWR) is using this to redefine the icons for the
;;; built-in classes.

;;; This facility is run in a KB with object subclasses defined with icon
;;; definitions desired for system classes.  You call the function
;;; `generate-system-icons-lisp-module', defined below, with pairs of the
;;; the system class and the corresponding class in the KB with the desired
;;; icon description.  And you specify a pathname.
;;;
;;; The resulting file is a Lisp module intended to be loaded/compiled as a
;;; normal G2 Lisp source file.  It must come after all of the def-classes
;;; in the load order.

;;;; Primary/Example Use:
;;;
;;; Load KB "/home/mhd/new-defs.kb"

;;; Now, you should see the new icons on object-definition.

;; Ideas:
;;
;; Have a system procedure to kick this off?
;;
;; Have a "save kb" or inspect command to do this?
;;
;; ---
;;
;; Show icons in menus along the left column?  Option?  (Per class? Could get
;; old for some complex icons for classes you don't care about....Proprietary...)
;;


#+development
(defun convert-class-or-frame-to-icon-description-creation-form (class-or-frame)
  (let ((icon-description?
	  (get-slot-init-form
	    (if (symbolp class-or-frame)
		class-or-frame
		(class class-or-frame))
	    'icon-description)))
    (if icon-description?
	(convert-icon-description-to-creation-form icon-description?))))


#+development
(defun convert-class-or-frame-to-stubs-creation-form (class-or-frame)
  (get-slot-init-form
    (if (symbolp class-or-frame)
	class-or-frame
	(class class-or-frame))
    'stubs-for-class))


#+development				; class icon description
(defun cid (class)
  (get-slot-init-form class 'icon-description))



#+development
(defun convert-icon-description-to-creation-form (icon-description)
  `(create-icon-description
     ',(width-of-icon icon-description)
     ',(height-of-icon icon-description)
     ',(icon-line-drawing-description icon-description)
     ',(icon-line-color? icon-description)
     nil nil nil nil
     ',(icon-region-extrema? icon-description)))



;;; `Download-icons-from-current-kb' searches the current KB and finds all
;;; object-definition instances that specify an attribute (a class-specific
;;; attribute) named `class-for-icon', along with a default value, which should
;;; be a symbol that names a built-in class.  For each such object definition,
;;; the default value of class-for-icon is used as the built-in class whose icon
;;; should be redefined.  (Note that the class must be defined, i.e., the object
;;; definition must be OK and installed.)
;;;
;;; What this does is:
;;;
;;;    (1) Create a Lisp source file named <name-of-kb>.lisp;
;;;    (2) Compile the created lisp source file;
;;;    (3) Loads the resulting compiled file.
;;;
;;; The effect of this is that the system-defined classes will now exhibit
;;; the new icons.  Note that the change will be "permanent" for the rest
;;; of the "session", i.e., after the KB is cleared, but not after the system
;;; is shut down.  To make the change continue (into the release, say), the
;;; Lisp module must be installed into the system at the end of the list of
;;; included Lisp modules.
;;;
;;;
;;; Use at Gensym as of now (November, 1994) involves these steps:
;;;
;;;    (1) Icon developmer edits icons in kbs/sysicons.kl, and updates
;;;        the repository (commits) this file.
;;;    (2) Developer: update to the latest sysicons:
;;;         bt kbs; update sysicons.kl
;;;    (3) Developer: Load KB "...kbs/sysicons.kl"
;;;    (4) Developer: Break into lisp, and evaluate
;;;         (download-icons-from-current-kb)
;;;        That creates lisp/sysicons.lisp
;;;    (5) Developer: hand-edit the sysicons.lisp file to get back the
;;;        computed width/height for action buttons -- this is hand-written
;;;        code, and not part of the icons description.  Get this from the
;;;        previous version.  [I would like to automate this, but haven't
;;;        had time. -mhd]
;;;    (5) Developer: commit lisp/sysicons.lisp
;;;
;;;

#+development
(defun download-icons-from-current-kb ()
  (loop for object-definition being each class-instance of 'object-definition
	  as kb-defined-class?
	    = (get-slot-value object-definition 'name-of-defined-class)
	  as system-defined-class?
	    = (if (and kb-defined-class?
		       (has-slot-p kb-defined-class? 'class-for-icon))
		  (get-slot-init-form kb-defined-class? 'class-for-icon))
	  when (and kb-defined-class? system-defined-class?
		    (classp system-defined-class?))
	    collect kb-defined-class? into kb-defined-classes
	    and collect system-defined-class? into system-defined-classes
	  finally
	     (cond
	       ((null kb-defined-classes)
		(return
		  (values
		    nil "Nothing Found.")))
	       ((null current-kb-pathname?)
		(return
		  (values
		    nil "There's no current KB -- Don't know where to save.")))
	       (t
		(let ((file-name
			(gensym-namestring
			  (gensym-make-pathname
			    :type #w"lisp"
			    :defaults
			      (gensym-namestring current-kb-pathname?)))))
		  (format t "
About to download ~s as follows:"
			  file-name)
		  (loop for c1 in kb-defined-classes
			as c2 in system-defined-classes
			do (format t "~%  Class for ~a icon is ~a ..."
				   c1 c2))
		  (let ((pathname
			  (generate-system-icons-lisp-module
			    file-name system-defined-classes kb-defined-classes)))
		  (load
		    (compile-file		; assumed to return the output pathname
		      pathname))
		  (return (list kb-defined-classes system-defined-classes pathname))))))))




;; Summary of Hand Edits:

;; ;; ACTION-BUTTON, from NEW-ACTION-BUTTON-DEF
;; ;;
;; ;; **** NOTE: This has been hand-edited as follows:
;; ;;
;; ;;  X - system-defined-class ACTION-BUTTON => GENERIC-ACTION-BUTTON
;; ;;  X: this is now done in sysicons.kb; no hand-edit needed
;; ;;  - in the line drawing description, substitions as follows:
;; ;;     . 100 => width
;; ;;     . 97 => (- width 3)
;; ;;     . 40 => height
;; ;;     . 37 => (- height 3)
;; ;;    (This makes it a computed icon description, G2's very first, in fact.)
;; ;;
;; ;;  - last arg, region-extrema?, => nil (this is an optional argument
;; ;;    that is used to limit the area of a raster for a given region,
;; ;;    but since all of our regions have computed parts, we can't supply
;; ;;    a region-extrema? argument, or at least we don't know how to
;; ;;    at present; it is safe to leave it nil.)
;; ;;
;; ;;  - Lightened the color one "notch" - changed the pending-indicator color
;; ;;    from light-gray => extra-light-gray, and changed the south-east
;; ;;    shadow's color from extra-light-gray => smoke.  This should improve
;; ;;    the contrast of the usually black foreground-color text that appears
;; ;;    in the label.
;; ;;
;; ;;  - just for readability:
;; ;;     . Forms like (quote x) => 'x (everywhere)
;; ;;     . reformatted lisp code into several lines
;; ;;
;; ;; (MHD 5/27/94)
;;
;; ;; NOTE: This was the original source description based on Dave's edits to
;; ;; sysicons.kl.  However, I'm only going to take the new region names, and
;; ;; lighter colors, and disregard the size change.  A size change at this time
;; ;; would be too risky, and was probably not actually intended. (MHD 8/14/95)
;;
;; ;; DEFAULT-ACTION-BUTTON, from NEW-DEFAULT-ACTION-BUTTON-DEF
;;
;; ;; MHD:  HAND-EDIT
;; ;;
;; ;;  105 => width
;; ;;  102 => (- width 3)
;; ;;  99 => (- width 6)
;; ;;  98 => (- width 7)
;; ;;  96 => (- width 9)
;; ;;  42 => height
;; ;;  39 => (- height 3)
;; ;;  36 => (- height 6)
;; ;;  33 => (- height 9)
;; ;;
;;
;; ;; MHD: hand-edited again 8/16/95, just to get the regions names, and the colors
;; ;; changed slightly per the above from DWR. (MHD 8/16/95)

#+development
(defparameter hand-edits-to-icon-description-override
  '((generic-action-button
     . (create-icon-description
	'90 '35
	'((polychrome
	   (pending-indicator . light-gray)
	   (g2-icon-light-shading . extra-light-gray)
	   (g2-icon-dark-shading . dark-gray))
	  pending-indicator
	  (solid-rectangle (2 2) ((- width 2) (- height 2)))
	  g2-icon-light-shading
	  (filled-polygon
	   ((0 0) (width 0) ((- width 3) 3) (3 3) (3 (- height 3)) (0 height))
	   ((0 0) (width 0) ((- width 3) 3))
	   ((3 3) (3 (- height 3)) (0 height))
	   ((0 0) ((- width 3) 3) (3 3))
	   ((3 3) (0 height) (0 0)))
	  g2-icon-dark-shading
	  ;; "mystery polygon:"  not sure what this is -- my guess is its an
	  ;; artifact! Talk to Dave! (MHD)
;      (filled-polygon
;       ((100 0) (100 40) (97 40) (97 3))
;       ((100 0) (100 40) (97 40))
;       ((97 40) (97 3) (100 0)))
	  (filled-polygon
	   ((3 (- height 3)) ((- width 3) (- height 3)) ((- width 3) 3) (width 0) (width height) (0 height))
	   (((- width 3) (- height 3)) ((- width 3) 3) (width 0))
	   ((width height) (3 (- height 3)) ((- width 3) (- height 3)))
	   (((- width 3) (- height 3)) (width 0) (width height))
	   ((width height) (0 height) (3 (- height 3)))))
	'nil
	nil nil nil nil
	nil))
    (default-action-button
	. (create-icon-description
	   '105 '42
	   '((polychrome
	      (pending-indicator . light-gray)
	      (g2-icon-light-shading . extra-light-gray)
	      (g2-icon-dark-shading . dark-gray))
	     pending-indicator
	     (solid-rectangle (6 6) ((- width 7) (- height 6)))
	     g2-icon-light-shading
	     (filled-polygon
	      ((3 (- height 3)) ((- width 3) (- height 3)) ((- width 3) 3) (width 0) (width height) (0 height))
	      (((- width 3) (- height 3)) ((- width 3) 3) (width 0))
	      ((width height) (3 (- height 3)) ((- width 3) (- height 3)))
	      (((- width 3) (- height 3)) (width 0) (width height))
	      ((width height) (0 height) (3 (- height 3))))
	     (filled-polygon
	      ((6 (- height 6)) (6 6) ((- width 6) 6) ((- width 9) 9) (10 9) (9 9) (9 (- height 9)))
	      ((6 6) ((- width 6) 6) ((- width 9) 9))
	      (((- width 9) 9) (10 9) (9 9))
	      ((9 9) (6 (- height 6)) (6 6))
	      ((6 6) ((- width 9) 9) (9 9))
	      ((9 9) (9 (- height 9)) (6 (- height 6))))
	     g2-icon-dark-shading
	     (filled-polygon
	      ((0 0) (width 0) ((- width 3) 3) (3 3) (3 (- height 3)) (0 height))
	      ((0 0) (width 0) ((- width 3) 3))
	      ((3 3) (3 (- height 3)) (0 height))
	      ((0 0) ((- width 3)  3) (3 3))
	      ((3 3) (0 height) (0 0)))
	     (filled-polygon
	      ((9 (- height 9)) ((- width 9) (- height 9)) ((- width 9) 9)
	       ((- width 6) 6) ((- width 6) (- height 6)) (6 (- height 6)))
	      (((- width 9) (- height 9)) ((- width 9) 9) ((- width 6) 6))
	      (((- width 6) (- height 6)) (9 (- height 9)) ((- width 9) (- height 9)))
	      (((- width 9) (- height 9)) ((- width 6) 6) ((- width 6) (- height 6)))
	      (((- width 6) (- height 6)) (6 (- height 6)) (9 (- height 9)))))
	   'nil
	   nil nil nil nil
	   nil))))


;;; Supply-hand-edit-to-icon-description-override-if-necessary usually returns
;;; its second argument; however, if the first argument is a system defined
;;; class with an entry in the hand-edits-to-icon-description-override, then the
;;; cdr of that entry is returned.  This is used to "override the override" with
;;; a hand edit.  Currently, there are two hand edits, and their comments with
;;; rationale is given above.  If necessary, see MHD for details and lore.

#+development
(defun supply-hand-edit-to-icon-description-override-if-necessary
    (system-defined-class given-icon-description)
  (or (cdr (assq system-defined-class
		 hand-edits-to-icon-description-override))
      given-icon-description))



#+development
(defun generate-system-icons-lisp-module
    (file-name system-defined-classes kb-defined-classes)
  (unless (= (length system-defined-classes)
	     (length kb-defined-classes))
    (cerror "Continue anyway (works if you repair the lists)"
	    "The two parallel lists don't match up in length!"))
  (with-open-file (output-stream (wide-string-to-string file-name) :direction :output)
    (format output-stream
	    ";; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*- ~
             ~%(in-package \"AB\")~%~
             ~%;;;; Module SYSICONS~%~
             ~%;;; Copyright (c) 1986 - 2017 Gensym Corporation.~
             ~%;;; All Rights Reserved.~%~
             ~%;;; THIS IS A MACHINE-GENERATED FILE. DO NOT EDIT BY HAND.~
             ~%;;; TO GENERATE THIS, EVALUATE (download-icons-from-current-kb).~%~%")
    (loop with *print-pretty* = nil
	  with *print-level* = nil
	  with *print-length* = nil
	  with *print-case* = :downcase
	  ;; Changes here for text in icons: Previously, we downcased the entire
	  ;; Lisp form we emitted.  Now we only downcase symbols just to make
	  ;; them look nicer, but we have to leave text (i.e., text in icons)
	  ;; alone.  Also, we now ensure that text strings are printed readable,
	  ;; which they are in Gensym's Lisp development environment (thanks to
	  ;; Lucid-specific hacks).  (MHD 12/30/96)
	  for system-defined-class
	      in system-defined-classes
	  as kb-defined-class
	     in kb-defined-classes
	  do (format output-stream
		     "~%~%~%;; ~a, from ~a~
                      ~%~%(override-icon-description-for-system-defined-class~
                      ~%  '~s~
                      ~%  ~s~
                      ~%  '~s)~%~%"
		     system-defined-class
		     kb-defined-class
		     system-defined-class
		     (supply-hand-edit-to-icon-description-override-if-necessary
		       system-defined-class
		       (convert-class-or-frame-to-icon-description-creation-form
			 kb-defined-class))
		     (convert-class-or-frame-to-stubs-creation-form
		       kb-defined-class)))
    (truename output-stream)		; This is needed to tell where the file was
					;   written to, but it causes warnings
    ))					;   because it's not a gensym pathname
					;   function - fix this hassle!

;; Currently, the ab-lemacs editor can't c-m-b back up from here, even though
;; all brackets match, and the reader/compiler like this.  Don't know why this
;; is -- but it must be bug in ab-lemacs somewhere. (MHD 2/15/94)




;;; `Override-icon-description-for-system-defined-class' is intended to be used
;;; at load time in a machine generated Lisp source file to override system
;;; defined slots.  The Lisp source file is generated by an system procedure
;;; that's an internal tool designed for this purpose.  This tool can be run by
;;; Icon designers to redefine system-defined icons.
;;;
;;; Stub-feature?, if specfied, should be a slot feature for the stub feature,
;;; which goes on the slot-group-for-block? slot.  It should looks something
;;; like this example, which is for a g2-window:
;;;
;;;    (stubs (nil network-wire nil bottom 30))



(defun override-icon-description-for-system-defined-class-ab
    (system-defined-class icon-description &optional stub-feature?)
  (update-slot-description-for-system-defined-class
    system-defined-class
    'icon-description
    icon-description)
  (when stub-feature?
    (let ((present-stubs-class-feature?
	    (get-class-feature-if-any system-defined-class 'stubs)))
      (unless (equal present-stubs-class-feature? stub-feature?)
	(let* ((class-description (class-description system-defined-class))
	       (class-features (class-features class-description))
	       (cons-holding-relevant-class-feature?
		 (member 'stubs class-features :test 'car-eq)))
	  (cond (cons-holding-relevant-class-feature?
		 (setf (car cons-holding-relevant-class-feature?)
		       stub-feature?))
		(t (setf (class-features class-description)
			 (cons stub-feature? class-features)))))))
    (update-slot-description-for-system-defined-class
      system-defined-class
      'slot-group-for-block?
      nil
      (list stub-feature?))))





;;;; Iconic Entities



;;; An `iconic entity' is an entity which exists solely for the purpose of
;;; providing a graphic entity with a custom icon description without having
;;; to create custom class with a class-wide icon description.

;;; The class iconic-entity is a subclass of entity.  Its primary use is
;;; as the subclass-of-entity argument to make-entity-with-specific-icon-
;;; description.

;; Suggested name: entity-with-specific-icon-description

(def-class (iconic-entity entity))





;;; `Fix-up-icon-description-for-entity-if-necessary' fixes up the
;;; slot-init-form and initialization for slot icon-description of entity.  It
;;; requires that create-icon- description be invocable by this point in the
;;; load sequence.

(defun fix-up-icon-description-for-entity-if-necessary ()
  (let ((slot-description
	  (get-slot-description-of-class-description
	    'icon-description (class-description 'entity)))
	(slot-definition
	  (assq 'icon-description (cddr (class-definition 'entity))))
	(slot-init-form
	  '(:funcall-at-load-time
	    create-icon-description
	    50 50
	    ((outline (0 0) (50 0) (50 50) (0 50))
	     (lines (0 0) (50 50))
	     (lines (50 0) (0 50))))))
    (unless (slot-init-form-given-slot-definition slot-definition)
      (setf (slot-init-form-given-slot-definition slot-definition)
	    slot-init-form))
    (unless (slot-init-form slot-description)
      (setf (slot-init-form slot-description)
	    (apply (cadr slot-init-form) (cddr slot-init-form))))))

(fix-up-icon-description-for-entity-if-necessary)	; invocation





;;;; Activation of Entities




;;; Has been moved to file RULES.

;;; Any subclass of entity which requires specific activation and/or
;;; deactivation shoud have an activate-subclass-of-entity and/or a
;;; deactivate-subclass-of-entity method.





;;; Given an item and a method, `propagate-method-to-attributes' applys the
;;; method to all attributes of the item which are themselves entities.

;;; Note that propagate-method-to-attributes evaluates the forms in args-if-any
;;; once per attribute, and so is a NON-STANDARD MACRO!  It will refuse to
;;; compile any calls to it that might have problems.  -jra 12/28/92

(defmacro propagate-method-to-attributes (item method &rest args-if-any)

  (loop for arg in args-if-any do
    (when (and (not (symbolp arg)) (not (constantp arg)))
      (error "Propagate-method-to-attributes does not deal with multiple ~
              evaluation of its extra args. Fix this!!")))

  (let ((item-evaluated (gensym))
	(slot-description (gensym))
	(slot-value (gensym)))
    `(let* ((,item-evaluated ,item))
       (loop for ,slot-description
		 in (slot-descriptions
		      (class-description-slot ,item-evaluated))
	     do
	 (when (user-defined-slot-description-p ,slot-description)
	   (let ((,slot-value
		    (get-slot-description-value
		      ,item-evaluated ,slot-description)))
	     (when (of-class-p ,slot-value 'item)
	       (funcall-method
		 ,method ,slot-value ,@args-if-any))))))))

(defmacro propagate-simple-method-to-attributes (item method &rest args-if-any)

  (loop for arg in args-if-any do
    (when (and (not (symbolp arg)) (not (constantp arg)))
      (error "Propagate-method-to-attributes does not deal with multiple ~
              evaluation of its extra args. Fix this!!")))

  (let ((item-evaluated (gensym))
	(slot-description (gensym))
	(slot-value (gensym)))
    `(let* ((,item-evaluated ,item))
       (loop for ,slot-description in
		 (slot-descriptions (class-description-slot ,item-evaluated))
	     do
	 (when (user-defined-slot-description-p ,slot-description)
	     (let ((,slot-value
		    (get-slot-description-value
		      ,item-evaluated ,slot-description)))
	       (when (of-class-p ,slot-value 'item)
		 (funcall-simple-method-macro
		   ,method ,slot-value ,@args-if-any))))))))




;;; The macro `funcall-simple-function-on-attributes' funcalls the given
;;; simple-function to each attribute of the given item which is itself an item.
;;; The argument simple-function is evaluated.  It must be a compiled function
;;; that was defined with defun-simple.

(defmacro funcall-simple-compiled-function-on-attributes
	  (item simple-function &rest args)
  (let* ((needs-rebinding?
	   (not (and (symbolp item)
		     (loop for arg in args
			   always (or (symbolp arg) (constantp arg))))))
	 (item-binding (if needs-rebinding? (gensym) item))
	 (arg-bindings
	   (if needs-rebinding?
	       (loop repeat (length args) collect (gensym))
	       args))
	 (let-list?
	   (if needs-rebinding?
	       (cons (list item-binding item)
		     (loop for binding in arg-bindings
			   for arg in args
			   collect (list binding arg)))))
	 (body
	   `(loop for slot-description in
		      (slot-descriptions (class-description-slot ,item-binding))
		  do
	      (when (user-defined-slot-description-p slot-description)
		(let ((slot-value (get-slot-description-value-macro
				    ,item-binding slot-description)))
		  (when (of-class-p slot-value 'item)
		    (funcall-simple-compiled-function
		      ,simple-function slot-value ,@arg-bindings)))))))

    (if needs-rebinding?  `(let ,let-list? ,body) body)))



(defmacro def-pseudo-attribute-class (name list-of-pseudo-attributes)
  (let ((rules
	  (loop for attribute in list-of-pseudo-attributes
		for rule
		    = `(,name
			  ,@(cond ((atom attribute)
				   (list `',attribute))
				  (t
				   (error "Pseudo-attributes must be symbols"))))
		collect rule))
	(predicate-name (intern (format nil "~s-P" name))))
    `(progn
       (add-grammar-rules ',rules)
       (def-substitution-macro ,predicate-name (attribute)
	 (memq-p-macro attribute ',list-of-pseudo-attributes))
       ',name)))



(def-pseudo-attribute-class color-attribute
    (icon-color stripe-color background-color foreground-color
		border-color text-color))


(def-pseudo-attribute-class graphic-attribute
    (icon-x-position icon-y-position icon-heading icon-width icon-height
		     item-x-position item-y-position
		     item-width item-height
		     text-alignment))	; added for 5.0 Rev. 3 (MHD 3/10/98)


;; (def-pseudo-attribute-class workspace-attribute
;;    (workspace subworkspace))




;;;; Icon Position, Size, Orientation, and Movement

;; This is being converted and extended to work with "items" now instead of just
;; icons. (MHD 9/1/89)


;;; These icon position and movement primitives take arguments and yield values with
;;; respect to `user workspace coordinate', which differ from ordinary workspace
;;; coordinates only in that y coordinates are reversed in sign.  In a user workspace
;;; coordinate system, x values increase to the right and y values increase in the
;;; upwards direction -- as is canonical for Cartesian coordinate systems.






;;; Item-x-position ...

;;; Item-y-position ...

;;; Item-width ...

;;; Item-height ...


(defun-simple item-x-position (item)
  (let ((width-of-block (width-of-block item)))
    (+f (left-edge-of-block item)
	(if (or (not (entity-p item))
		(memq (getf (icon-attributes-plist item) 'reflection-and-rotation)
		      '(nil normal clockwise-270
			reflected-clockwise-180 reflected-clockwise-270)))
	    (halfw width-of-block)
	    (-f width-of-block (halfw width-of-block))))))

(defun-simple item-y-position (item)
  (let ((height-of-block (height-of-block item)))
    (-w					; flip sign for user coordinate system
      (+f (top-edge-of-block item)
	  (if (or (not (entity-p item))
		  (memq (getf (icon-attributes-plist item) 'reflection-and-rotation)
			'(nil normal clockwise-90
			  reflected reflected-clockwise-270)))
	      (halfw height-of-block)
	      (-f height-of-block (halfw height-of-block)))))))

(defun-simple item-width (item)
  (cond ((slot-group-for-block? item)
	 (-w (right-edge-of-block item) (left-edge-of-block item)))
	((and (not (frame-of-class-p item 'connection))
	      (frame-of-class-p item 'entity)
	      (icon-description item))
	 (let* ((icon-description (icon-description item))
		(icon-attributes-plist? (icon-attributes-plist item)))
	   (or (if icon-attributes-plist?
		   (getf icon-attributes-plist? 'width))
	       (width-of-icon icon-description))))
	(t 0)))

(defun-simple item-height (item)
  (cond ((slot-group-for-block? item)
	 (-w (bottom-edge-of-block item) (top-edge-of-block item)))
	((and (not (frame-of-class-p item 'connection))
	      (frame-of-class-p item 'entity)
	      (icon-description item))
	 (let ((icon-description (icon-description item))
	       (icon-attributes-plist? (icon-attributes-plist item)))
	   (or (if icon-attributes-plist?
		   (getf icon-attributes-plist? 'height))
	       (height-of-icon icon-description))))
	(t 0)))




;;; Icon-heading ...

(defun icon-heading (entity)
  (case (getfq (icon-attributes-plist entity) 'reflection-and-rotation)
    ((nil normal reflected) 0)
    ((clockwise-90 reflected-clockwise-90) 90)
    ((clockwise-180 reflected-clockwise-180) 180)
    ((clockwise-270 reflected-clockwise-270) 270)))

(defun reflectedp (entity) ;left-right
  (case (getfq (icon-attributes-plist entity) 'reflection-and-rotation)
    ((nil normal clockwise-90 clockwise-180 clockwise-270) nil)
    (t ;(reflected reflected-clockwise-90 reflected-clockwise-180 reflected-clockwise-270)
     t)))



;;; `graphic-attributes' - new virtual attributes for graphic-attributes

(def-virtual-attribute item-x-position
    ((class item)
     integer
     ())
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-x-position item)))



(def-virtual-attribute icon-x-position
    ((class item)
     integer
     (deprecated (item)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-x-position item)))



(def-virtual-attribute item-y-position
    ((class item)
     integer
     ())
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-y-position item)))



(def-virtual-attribute icon-y-position
    ((class item)
     integer
     (deprecated (item)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-y-position item)))


(def-virtual-attribute icon-heading
    ((class entity)
     integer
     ())
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (icon-heading item))
  :setter
  ((entity new-heading)
   (rotate-and-reflect-icon entity
			    (-f new-heading (icon-heading entity))
			    nil nil nil t)))

(def-virtual-attribute icon-reflection
    ((class entity)
     (or symbol (no-item))
     ())
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   'left-right)
  :getter
  ((item)
   (if (reflectedp item)
       'left-right
       nil))
  :setter
  ((entity new-value)
   (let ((reflectp (cond ((eq new-value nil)
			  (reflectedp entity))
			 ((eq new-value 'left-right)
			  (not (reflectedp entity)))
			 (t
			  'bad))))
   (if (eq reflectp 'bad)
       (copy-constant-wide-string #w"bad value for item-reflection")
       (when reflectp
	 (rotate-and-reflect-icon entity 0 t nil nil t))))))

(def-virtual-attribute item-height
    ((class item)
     integer
     ())
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-height item)))


(def-virtual-attribute icon-height
    ((class item)
     integer
     (deprecated (item)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-height item)))


(def-virtual-attribute item-width
    ((class item)
     integer
     ())
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-width item)))


(def-virtual-attribute icon-width
    ((class item)
     integer
     (deprecated (item)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-integer 0))
  :getter
  ((item)
   (item-width item)))





;;; The `icon-color' of an entity has an involved definition due the two
;;; possible interpretations:
;;;   1. "the color of the region named icon-color"
;;;   2. "the line-color (default foreground color) of the entity"

;;; In 4.0 this problem has become much worse since all of the new system icons
;;; have a region named icon-color.  The conflict is resolved as follows:
;;;  1. If there is a region named icon-color, then that is the icon-color.
;;;  2. Otherwise, the icon-color is the line-color.
;;; There is much code in change-color/pattern-of-icon to maintain these properties.

;;; For example, suppose an entity has regions named FOREGROUND and FOO.  Then,
;;; changing the color pattern of the entity such that (foreground=red,
;;; foo=green) has to stuff RED into the LINE-COLOR, GREEN into the FOO region,
;;; and leave the foreground regions in the icon pattern alone.
;;;
;;; Note that when the icon-color of an entity is changed, the change must
;;; always be done, regardless of its visibility.  This is so that the
;;; fetching the icon color will fetch the value stored there.

(def-concept icon-color)


;;; The function `icon-color' returns the "icon-color" of the given entity.  In
;;; 4.0, the icon-color of an entity is defined to be the color of the region
;;; named ICON-COLOR, if there is one, else the line-color of the entity.
;;;
;;; The line-color defaults to nil, but can be changed by the user only if there
;;; is no icon-color region, i.e., by changing the icon-color of the entity in
;;; such a case.  When non-nil, the line-color of an entity determines the
;;; default foreground color while drawing the entity; that is, any region whose
;;; color is foreground will get the entity's line-color, if any.  If there is
;;; no line-color, foreground regions are drawn in the workspaces's foreground
;;; color.

(defun icon-color (entity)
  (or
    ;; The color of the region named icon-color, if any.
    (cdr (assq 'icon-color (icon-color-pattern entity)))

    ;; The line color, if any.
    (getf (icon-attributes-plist entity) 'line-color)
    (let ((icon-description? (icon-description entity)))
      (if icon-description?
	  (icon-line-color? icon-description?)))

    ;; The color of the region named foreground, if any.
    ;; I think that this will always be FOREGROUND or nil.
    (cdr (assq 'foreground (icon-color-pattern entity)))

    ;; else BLACK (usually).
    current-default-line-color))

;; This function must be kept in sync with it corresponding setter,
;; change-icon-color.

;; Notice that even though one cannot change the icon-color of any item in 3.0,
;; you can always get the icon color.  It defaults to black.



;;; The function `get-color-of-icon-region' returns the color of the given
;;; region in the entity's icon desciption.  A region named ICON-COLOR is
;;; equivalent to the icon-color of the entity, defined above.

(defun get-color-of-icon-region (entity region)
  (if (eq region 'icon-color)
      (icon-color entity)
      (cdr (assq region (icon-color-pattern entity)))))




;;; The function `icon-color-pattern' ...

(defun icon-color-pattern (entity)
  (or (getf (icon-attributes-plist entity) 'icon-color-pattern)
      (let ((icon-description? (icon-description entity)))
	(if icon-description?
	    (icon-color-pattern? icon-description?)))))




;;; Item-color ...

(defun item-color (item region?)
  (frame-class-case item
    (connection
      (get-connection-color item (or region? 'stripe-color)))
    (text-box
      (let* ((text-cell-plist
	       (get-slot-value item 'text-cell-plist-for-text-box))
	     (text-box-format
	       (get-slot-value item 'text-box-format)))
	(case region?
	  (background-color
	   (or (getf text-cell-plist 'background-color)
	       (get-slot-value text-box-format 'text-cell-background-color?)
	       'transparent))
	  (text-color
	   (or (getf text-cell-plist 'line-color)
	       (get-slot-value text-box-format 'text-cell-line-color?)
	       current-default-line-color))
	  (border-color
	   (or (getf text-cell-plist 'border-color)
	       (get-slot-value text-box-format 'text-box-border-color?)
	       current-default-line-color)))))
    (entity
      (if region?
	  (get-color-of-icon-region item region?)
	  (icon-color item)))
    (workspace
      (case region?
	(background-color
	 (or (workspace-background-color? item) 'white))
	(foreground-color
	 (or (workspace-foreground-color? item) 'black))))))

;; The use of calls to get-slot-value, rather than inline accessor macros, is
;; necessitated by the load ordering problem, i.e., the accessors would be
;; illegal forward references. (MHD)

;; These handle fallthrough cases inconsistently, and maybe wrongly.  In the
;; case of entities, a region not found can fall through to nil.  For the null
;; region? case, icon-color falls through to current-default-line-color, which
;; will be BLACK.  The background-color of a text box falls through to
;; TRANSPARENT.  For a workspace, it falls through to WHITE.  It seems like a
;; mess, and it's all pretty delicate!  (MHD 11/2/90 and 6/7/94).
;;
;; "This is not set! This needs more work!!" (MHD 8/2/89)


;;;; Color Attributes


;;; Color-attributes are defined somewhat sporadically.  The following
;;; classes always have the listed color-attributes, and never have
;;; the ones which are not listed for them:
;;;
;;;  connection - stripe-color
;;;  text-box - background-color, text-color, border-color
;;;  (kb-)workspace - background-color, foreground-color (see note)
;;;
;;; The `icon-color' of an entity has an involved definition due the two
;;; possible interpretations:
;;;   1. "the color of the region named icon-color"
;;;   2. "the line-color (default foreground color) of the entity"

;;; In 4.0 this problem has become much worse since all of the new system icons
;;; have a region named icon-color.  The conflict is resolved as follows:
;;;  1. If there is a region named icon-color, then that is the icon-color.
;;;  2. Otherwise, the icon-color is the line-color.
;;; There is much code in change-color/pattern-of-icon to maintain these properties.

;;; For example, suppose an entity has regions named FOREGROUND and FOO.  Then,
;;; changing the color pattern of the entity such that (foreground=red,
;;; foo=green) has to stuff RED into the LINE-COLOR, GREEN into the FOO region,
;;; and leave the foreground regions in the icon pattern alone.
;;;
;;; Note that when the icon-color of an entity is changed, the change must
;;; always be done, regardless of its visibility.  This is so that the
;;; fetching the icon color will fetch the value stored there.

;;; The line-color defaults to nil, but can be changed by the user only if there
;;; is no icon-color region, i.e., by changing the icon-color of the entity in
;;; such a case.  When non-nil, the line-color of an entity determines the
;;; default foreground color while drawing the entity; that is, any region whose
;;; color is foreground will get the entity's line-color, if any.  If there is
;;; no line-color, foreground regions are drawn in the workspaces's foreground
;;; color.

;;; Entities should always have something which is returned
;;; when icon-color is requested.  In addition, if an entity happens
;;; to have a region which shares a name with a color-attribute,
;;; then the color-attribute becomes valid for that class.

;;; Example: class foobar has the following regions and colors:
;;;     icon-color: red
;;;     top-region: green
;;;     bot-region: blue
;;; Assuming an instance of foobar called steve, in this case,
;;; the icon-color of steve => red, and attempting to access the
;;; background-color of steve produces an error.

;;; Now, let's say we rename the region called "icon-color" so
;;; that it's now named "red-region".  Accessing the icon-region
;;; of steve then yields, bafflingly, black.  When there is no
;;; region named icon-color, it defaults to the default line-color.

;;; Finally, say we rename "top-region" to "background-color".  Now,
;;; the background-color of steve => green.  It is really unnecessary
;;; and confusing to assign virtual attributes seemingly dynamically,
;;; but that's what's always been done.  Of course, you could always
;;; get a generic named region using the "region icon-color" syntax,
;;; as in "the bot-region icon-color of steve".  However, note that
;;; in G2v4, the syntax "the background-color icon-color of steve"
;;; was ambiguous.  This will be fixed for 5.0, and really is the
;;; preferable way to access a named region in an arbitrary class.

;; Workspace note: the code for workspace is not called.  Background-color
;; and foreground-color are slots in kb-workspace, which are defined to be of
;; type extant-color-or-metacolor.  Therefore, the category-evaluator interface
;; for extant-color-or-metacolor handles those cases.  Nevertheless, the code
;; should work if get-background-color were ever called with a workspace.


;;; `background-color'

(def-virtual-attribute background-color
    ((or (class text-box) (class entity))
     symbol
     (deprecated (entity)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-symbol 'black))
  :getter
  ((item)
   (frame-class-case item
     (text-box
       (let* ((text-cell-plist
		(get-slot-value item 'text-cell-plist-for-text-box))
	      (text-box-format
		(get-slot-value item 'text-box-format)))
	 (or (getf text-cell-plist 'background-color)
	     (get-slot-value text-box-format 'text-cell-background-color?)
	     'transparent)))
     (workspace				;; see note above
       (or (workspace-background-color? item) 'white))
     (entity
       (get-color-of-icon-region item 'background-color))
     (t nil)))
  :setter
  ((item new-background-color)
   (if (gensym-color-p new-background-color)
       (frame-class-case item
	 (text-box
	   (change-color-of-text-box
	     item t new-background-color :no-change :no-change)
	   nil)
	 (workspace
	   (change-color-of-workspace
	     item t new-background-color :no-change)
	   nil)
	 (t
	   (tformat-text-string
	     "The attribute BACKGROUND-COLOR does not exist in ~NF."
	     item)))
       (tformat-text-string
	 "The argument given, ~a, was not a valid color."
	 new-background-color))))


;;; `foreground-color'

(def-virtual-attribute foreground-color
    ((or (class entity))
     symbol
     (deprecated (entity)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-symbol 'black))
  :getter
  ((item)
   (frame-class-case item
     (workspace				;; see note above
       (or (workspace-foreground-color? item) 'white))
     (entity
       (get-color-of-icon-region item 'foreground-color))
     (t nil)))
  :setter
  ((item new-foreground-color)
   (if (gensym-color-p new-foreground-color)
       (frame-class-case item
	 (workspace
	   (change-color-of-workspace
	     item t :no-change new-foreground-color)
	   nil)
	 (t
	   (tformat-text-string
	     "The attribute FOREGROUND-COLOR does not exist in ~NF."
	     item)))
       (tformat-text-string
	 "The argument given, ~a, was not a valid color."
	 new-foreground-color))))



;;; `text-color'

(def-virtual-attribute text-color
    ((or (class text-box) (class entity))
     symbol
     (deprecated (entity)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-symbol 'black))
  :getter
  ((item)
   (frame-class-case item
     (text-box
       (let* ((text-cell-plist
		(get-slot-value item 'text-cell-plist-for-text-box))
	      (text-box-format
		(get-slot-value item 'text-box-format)))
	 (or (getf text-cell-plist 'line-color)
	     (get-slot-value text-box-format 'text-cell-line-color?)
	     current-default-line-color)))
     (entity
       (get-color-of-icon-region item 'text-color))
     (t nil)))
  :setter
  ((item new-text-color)
   (if (gensym-color-p new-text-color)
       (frame-class-case item
	 (text-box
	   (change-color-of-text-box
	     item t :no-change :no-change new-text-color)
	   nil)
	 (t
	   (tformat-text-string
	     "The attribute TEXT-COLOR does not exist in ~NF."
	     item)))
       (tformat-text-string
	 "The argument given, ~a, was not a valid color."
	 new-text-color))))



;;; `border-color'

(def-virtual-attribute border-color
    ((or (class text-box) (class entity))
     symbol
     (deprecated (entity)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-symbol 'black))
  :getter
  ((item)
   (frame-class-case item
     (text-box
       (let* ((text-cell-plist
		(get-slot-value item 'text-cell-plist-for-text-box))
	      (text-box-format
		(get-slot-value item 'text-box-format)))
	 (or (getf text-cell-plist 'border-color)
	     (get-slot-value text-box-format 'text-box-border-color?)
	     current-default-line-color)))
     (entity
       (get-color-of-icon-region item 'border-color))
     (t nil)))
  :setter
  ((item new-border-color)
   (if (gensym-color-p new-border-color)
       (frame-class-case item
	 (text-box
	   (change-color-of-text-box
	     item t :no-change new-border-color :no-change)
	   nil)
	 (t
	   (tformat-text-string
	     "The attribute BORDER-COLOR does not exist is ~NF." item)))
       (tformat-text-string
	 "The argument given, ~a, was not a valid color."
	 new-border-color))))


;;; `stripe-color'

(def-virtual-attribute stripe-color
    ((or (class connection) (class entity))
     symbol
     (deprecated (entity)))
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-symbol 'black))
  :getter
  ((item)
   (frame-class-case item
     (connection
       (get-connection-color item 'stripe-color))
     (entity
       (get-color-of-icon-region item 'stripe-color))
     (t nil)))
  :setter
  ((item new-stripe-color)
   (if (gensym-color-p new-stripe-color)
       (frame-class-case item
	 (connection
	   (change-color-of-connection item t new-stripe-color)
	   nil)
	 (t
	   (tformat-text-string
	     "The attribute STRIPE-COLOR does not exist in ~s."
	     item)))
       (tformat-text-string
	 "The argument given, ~a, was not a valid color."
	 new-stripe-color))))


;;; `icon-color'

(def-virtual-attribute icon-color
    ((class entity) ;; arg-type-spec
     symbol				;; value-type-spec
     ())				;; features
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   (make-evaluation-symbol 'black))
  :getter
  ((item)
   (icon-color item))
  :setter
  ((item new-icon-color)
   (if (gensym-color-p new-icon-color)
       (progn
	 (change-color-of-item item t 'icon-color new-icon-color)
	 nil)
       (twith-output-to-text-string
	 (tformat "The argument given, ~a, was not a valid color."
		  new-icon-color)))))








;;; Move-item ...

(defun move-icon (entity new-x new-y)
  (move-item entity new-x new-y))

;; Move-icon is obsolete -- don't use them in new code.



;;; The substitution-macro `round-macro' is an experiment in speeding up
;;; mill.kb, which spends most of its time moving items around by fixnum
;;; amounts.

(def-substitution-macro round-macro (number)
  (if (fixnump number) number (round number)))



;;; The function `move-item' is called by the evaluator's SET-POSITION
;;; instruction.

(defun move-item (item new-x new-y &optional (note-as-kb-state-change? t))
  (setq new-x (round-macro new-x))			    ; these change args
  (setq new-y (round-macro new-y))
  (move-item-by
    item (-w new-x (item-x-position item)) (-w new-y (item-y-position item))
    note-as-kb-state-change?))


;;; 1 pixel of icon will be left over when moving item on a workspace
;;; when moving item, the item rectangle will be enlarged by 1 pixel

(defmacro icon-fix-when-moving-item () `1)

;;; The function `move-item-by' is called by the evaluator's MOVE instruction.
;;; The delta's here may be floats or integers.

(defun move-item-by (item delta-x delta-y &optional (note-as-kb-state-change? t))
  (let ((workspace? (get-workspace-if-any item))
	(do-not-note-permanent-changes-p note-as-kb-state-change?))
    (when workspace?
      (let ((delta-x-in-workspace (round-macro delta-x))
	    (delta-y-in-workspace (-w (round-macro delta-y))))

	(unless (=w delta-x-in-workspace delta-y-in-workspace 0)

	  (when note-as-kb-state-change?
	    (note-kb-state-change item 'item-position))	; make faster!?
	  ;; Note that before 2.0, noting was done even if the deltas were
	  ;;   both zero. (MHD 3/31/89)

	  (multiple-value-bind
	      (extreme-left-edge extreme-top-edge extreme-right-edge
				 extreme-bottom-edge)
	      (determine-extreme-edges-for-item-being-moved item)

	    (let ((margin (workspace-margin workspace?)))

	      ;; Restrict the deltas such the extreme edges of the item after the
	      ;; move will still lie within the workspace margins.
	      (setq delta-x-in-workspace
		    (maxw
		      (minw
			delta-x-in-workspace
			(-w (-w (right-edge-of-block workspace?) margin)
			    extreme-right-edge))
		      (-w (+w (left-edge-of-block workspace?) margin)
			  extreme-left-edge)))
	      (setq delta-y-in-workspace
		    (maxw
		      (minw
			delta-y-in-workspace
			(-w (-w (bottom-edge-of-block workspace?) margin)
			    extreme-bottom-edge))
		      (-w (+w (top-edge-of-block workspace?) margin)
			  extreme-top-edge))))

	    (cond
	      ((=w delta-x-in-workspace delta-y-in-workspace 0))

	      ((connections item)
	       (move-blocks-with-their-external-connections
		 item workspace?
		 delta-x-in-workspace delta-y-in-workspace))

	      ;; The separate cases for entity and block are not needed, I think.
	      ((or (entity-p item)
		   (opaque-block-p item))
	       (cond ((and (paint-mode-p)
			   (not (render-frame-in-xor-overlay-p item)))

		      ;; Slightly optimized case, temporarily here to test
		      ;; the speed improvement, if any. -fmw, 1/3/95

		      (let ((region (make-region-from-rectangle
				      (-w extreme-left-edge (icon-fix-when-moving-item))
				      (-w extreme-top-edge (icon-fix-when-moving-item))
				      (+w extreme-right-edge (icon-fix-when-moving-item))
				      ;; Gensym-59 fix: bottom area is not updated completely -
				      ;; it needs to increase extreme-bottom-edge
				      (+w 5 extreme-bottom-edge))))
			(setq region (add-rectangle-to-region
				       (+w extreme-left-edge delta-x-in-workspace)
				       (+w extreme-top-edge delta-y-in-workspace)
				       (+w extreme-right-edge delta-x-in-workspace)
				       (+w extreme-bottom-edge delta-y-in-workspace)
				       region))
			(let ((do-not-update-selection-highlights t)) ; We do it later.
			  (shift-block item delta-x-in-workspace delta-y-in-workspace))
			(move-selection-highlights
			  item workspace? delta-x-in-workspace delta-y-in-workspace)
			(invalidate-region-of-workspace workspace? region)
			(reclaim-region region)))

		     (t
		      (let ((region-invalidation-is-preferred
			      (opaque-block-p item)))
			(update-images-of-rectangle-of-block
			  item t
			  extreme-left-edge extreme-top-edge
			  extreme-right-edge extreme-bottom-edge)
			(let ((do-not-update-selection-highlights t)) ; We do it later.
			  (shift-block item delta-x-in-workspace delta-y-in-workspace))
			(move-selection-highlights
			  item workspace? delta-x-in-workspace delta-y-in-workspace)
			(update-images-of-rectangle-of-block
			  item nil
			  (+w extreme-left-edge delta-x-in-workspace)
			  (+w extreme-top-edge delta-y-in-workspace)
			  (+w extreme-right-edge delta-x-in-workspace)
			  (+w extreme-bottom-edge delta-y-in-workspace))))))
	      (t
	       ;; I guess this case is for items whose new bounding rectangle
	       ;; after shift-block is unpredictable?  Borderless-free-text's
	       ;; arrive here.  So do trend-charts and graphs.
	       (update-images-of-block item t nil)
	       (let ((do-not-update-selection-highlights t)) ; We do it later.
		 (shift-block item delta-x-in-workspace delta-y-in-workspace))
	       (move-selection-highlights
		 item workspace? delta-x-in-workspace delta-y-in-workspace)
	       (update-images-of-block item nil nil)))))))))

;; Note-as-kb-state-change? should be nil by default; fix callers and change!

;; Consider calling warning-message when entity is not on a workspace, instead of just
;; moving it "abstractly".

;; CHECK THAT ARGUMENTS ARE WITHIN FIXNUM BOUNDS!

;; Consider having move-icon used for icon dragging.

;; Note that an entity may have a subblock outside its block rectangle, e.g., a name box.






;;; `Transfer-item' is used for runtime transferring of items (i.e., via calls
;;; from the inference engine).  It only works for transfers of items for which
;;; all of the following are true:
;;;
;;;   (1) item must be transient;
;;;
;;;   (2) item must be a block;
;;;
;;;   (3) item must be an immediate subblock of a workspace or not a subblock;
;;;
;;;   (4) item may have connections, but the transfer will be rejected
;;;   if there are connections that are other than stubs;
;;;
;;; (Later, this will hopefully be extended to handle groups of blocks, possibly
;;; interconnected).

;;; New-X? and new-y? are in user workspace coordinates.  Note that either one
;;; or both may be null.  When one is null, its current position stays the same.
;;; Note that newly created objects start off (with their top, left corner (!))
;;; at (0, 0) and that newly created workspaces have their origin in their
;;; center, i.e., half way between their left and right edges and half way
;;; between their top and bottom edges.

;;; Workspace? may be nil or any KB workspace or a message board.  If workspace?
;;; is nil, then the item is transferred into "limbo" or "nowhere", which is
;;; just like being transferred to an active workspace, as far as activating is
;;; concerned.  When workspace? is non-nil, the item's activation is not done if
;;; item is already on workspace?.  When item is being moved to a new
;;; workspace?, it gets activated in the usual way; see add-subblock.

;;; Note that this does not test its arguments to ensure that they conform with
;;; any of the constraints mentioned above.

(defun transfer-item
    (item workspace? new-x? new-y? &optional note-as-kb-state-change?)
  (transfer-blocks-with-their-external-connections
    item workspace? new-x? new-y? note-as-kb-state-change?))

;; Added event-update-status-of-block-showing logic. - ben 10/25/91 -- That's
;; been moved to transfer-blocks-with-their-external-connections.  (MHD 2/3/94)
;; NOTE: In 3.0, transferring by hand probably failed to do the
;; event-update-status-of-block-showing logic, which would have been a bug.
;; (We're pretty sure, but just haven't tested this.)  (MHD/BAH 2/3/94)

;; Unfortunately, note-as-kb-state-change? defaults to NIL here but defaults
;; to t for move-item.  Clean up some day! (MHD 9/27/91)

;; Note that transfer-blocks-with-their-external-connections also handles
;; transferring groups of blocks, but there is nothing in the language now
;; to interface to such functionality. (MHD 4/3/91)




;;; `Add-item-to-workspace' is similar to transfer-item, but it can be used for
;;; non-transient items, including neither-permanent-nor-transient items, and
;;; requires a workspace argument.  This is generally intended to be used for
;;; newly created items, which are neither-permanent-nor-transient.

(defun add-item-to-workspace
    (item workspace new-x? new-y?  &optional note-as-kb-state-change?)
  (transfer-blocks-with-their-external-connections
    item workspace new-x? new-y? note-as-kb-state-change?))

;; This should also be useful for supporting user-created "palettes", though
;; that needs design! (MHD 5/1/03)
  





;;; `Change-color-of-icon' is now entirely equivalent to changing the color of
;;; the ICON-COLOR region of an entity.  It has the additional feature that
;;; when new-color? is nil, the default color is restored.  The default color
;;; is the color when there is no line-color property in the icon attributes
;;; plist.

(defun change-color-of-icon (entity note-as-kb-state-change? new-color?)
  (when (icon-description entity)
    (let* ((default-color
	       (or (icon-line-color? (icon-description entity))
		   (get-workspace-foreground-color-for-entity-if-any entity)
		   current-default-line-color))
	   (new-color
	     (or new-color? default-color)))

      (unless (eq new-color (icon-color entity))
	(let* ((color-change-pattern
		(slot-value-list
		  (slot-value-cons 'icon-color new-color)))
	       (stack-error-or-nil?
		 (change-color-pattern-of-icon
		   entity note-as-kb-state-change? color-change-pattern)))
	  (reclaim-slot-value-tree color-change-pattern)
	  stack-error-or-nil?)))))

;; This used to refuse to change the color of polychrome icons, calling the
;; function warn-of-polychrome-icon.  Now it goes ahead and does it, but
;; updates the screen incorrectly. -fmw, 10/7/94





;;; The function `set-icon-colors' sets the icon color pattern and line-color
;;; to the given values.  New-color-pattern must be a slot-value list (or nil)
;;; and is CONSUMED by this routine.  If new-line-color?, then it is not
;;; changed.

(defun set-icon-colors (entity note-as-kb-state-change? new-color-pattern new-line-color?)
  (let* ((do-not-note-permanent-changes-p note-as-kb-state-change?)
	 (default-color-pattern?
	     (icon-color-pattern? (icon-description entity)))
	 (default-line-color
	     (or (icon-line-color? (icon-description entity))
		 'foreground))
	 (color-pattern-is-default?
	   (loop for (region . color) in new-color-pattern
		 always (eq color (cdr (assq region default-color-pattern?)))))
	 (line-color-is-default?
	   (eq new-line-color? default-line-color)))

    (when note-as-kb-state-change?
      (note-kb-state-change entity 'icon-color)
      (note-kb-state-change entity 'icon-color-pattern))

    ;; If new-line-color is NIL, then we erase the property always.
    (cond ((null new-line-color?))
	  (line-color-is-default?
	   (change-icon-attribute entity 'line-color nil))
	  (t
	   (change-icon-attribute entity 'line-color new-line-color?)))

    (cond (color-pattern-is-default?
	   (reclaim-slot-value-tree new-color-pattern)
	   (change-icon-attribute entity 'icon-color-pattern nil))
	  (t
	   (change-icon-attribute entity 'icon-color-pattern new-color-pattern)))))



;;; The function `change-color-pattern-of-icon' changes the color pattern of the
;;; entity according to the color-change-pattern, which must be an alist of
;;; (region . color).
;;;
;;; A region named ICON-COLOR is special in that all icons/entities have this
;;; region, in the user model: sometimes it's color is stored into the
;;; line-color proeprty of the entity, rather than into the entity's color
;;; pattern.  In all cases, this region's value must be saved if only in order
;;; to be given back to the user next time it is requested.
;;;
;;; For other regions, if they do not explicitly exist, it is an error to change
;;; their region, and a warning or abort is signalled as is appropriate.

(defun change-color-pattern-of-icon
    (entity note-as-kb-state-change? color-change-pattern)
  (when (icon-description entity)
    (let* ((current-color-pattern
	     (current-color-pattern-of-entity entity))
	   (new-color-pattern
	     (copy-tree-using-slot-value-conses current-color-pattern))
	   (new-line-color?				    ; Set from icon-color sometimes.
	     nil)
	   (any-changes?
	     nil)
	   (error?
	     nil)
	   (becoming-transparent?
	     (loop for (nil . new-color) in color-change-pattern
		   thereis (transparent-color-p new-color)))
	   (stack-error-or-nil? nil))

      ;; Stuff color changes into the new-color-pattern and into new-line-color?
      (loop as (region . color) in color-change-pattern
	    as new-region-and-color? = (assq region new-color-pattern)
	    doing
	(cond
	  ((and (eq region 'icon-color)	; all icons have icon-color
		(null new-region-and-color?))
	   (setq new-line-color? color)
	   (setq any-changes? t))

	  ;; The instructions change-item-color and change-item-color-pattern
	  ;; bind executing-change-item-color-instruction-p.  When a missing
	  ;; or unnamed color region error is detected in this function, an
	  ;; error is returned to the instructions; otherwise the return
	  ;; value is nil.
	  ((null new-region-and-color?)
	   (cond (executing-change-item-color-instruction-p
		  (setq stack-error-or-nil?
			(gensym-cons 'missing-color-region region))
		  (setq error? t)
		  (loop-finish))
		 (t (warn-of-missing-color-region entity region)
		    (setq error? t))))

	  ((eq (car new-region-and-color?)		    ; (color . color),
	       (cdr new-region-and-color?))		    ;  i.e., unlabeled
	   (cond (executing-change-item-color-instruction-p
		  (setq stack-error-or-nil?
			(gensym-cons 'unnamed-color-region region))
		  (setq error? t)
		  (loop-finish))
		 (t (warn-of-unnamed-color-region entity region)
		    (setq error? t))))
	  (t
	   (unless (eq color (cdr new-region-and-color?))
	     (setq any-changes? t)
	     (setf (cdr new-region-and-color?) color)))))

      (cond
	((or error? (null any-changes?))
	 (reclaim-slot-value-tree new-color-pattern))

	;; If we are scheduled painting, invalidate the changed icon regions.
	((appropriate-to-invalidate-color-of-block? entity becoming-transparent?)
	 (let ((workspace? (get-workspace-if-any-macro entity)))

	   ;; set-icon-colors consumes the new-color-pattern argument.
	   (set-icon-colors entity note-as-kb-state-change?
			    new-color-pattern new-line-color?)

	   ;; Note that color-change-pattern holds just the changed regions and
	   ;; colors, while new-color-pattern held the exhaustive list of all
	   ;; new colors.
	   (when workspace?
	     (let ((changed-regions
		     (loop for (region . color) in color-change-pattern
			   collect region using gensym-cons)))
	       (invalidate-color-of-block workspace? entity changed-regions)
	       (reclaim-gensym-list changed-regions)))
	   ;; Update native item views, No workspace required.
	   (update-item-views entity)))

	(t
	 (loop as (current-region . current-color) in current-color-pattern
	       as (new-region . new-color) in new-color-pattern
	       collect current-color
		 into current-color-list using gensym-cons-macro
	       collect new-color
		 into new-color-list using gensym-cons-macro
	       finally
		 ;; Ignores new-line-color !!
		 (do-color-revision (entity becoming-transparent?)
		     (revise-icon-rendering entity current-color-list
					    new-color-list new-line-color?)
		   (reclaim-gensym-list-macro current-color-list)
		   (reclaim-gensym-list-macro new-color-list)
		   (set-icon-colors
		     entity note-as-kb-state-change?
		     new-color-pattern new-line-color?)))
	 ;; Update native item views, No workspace required.
	 (update-item-views entity)))

      stack-error-or-nil?)))

;; In 2.0 Beta, prior to 6/29/89, icon color change patterns are of
;; the form
;;
;;   ( { (<color region> <color>) } )
;;
;; which was generated by the compiler for the actions like "change the
;; color pattern of foo to bar = green".
;;
;;
;; On the other hand, icon color patterns are of the form
;;
;;   ( { (<color region> . <color>) | (<color> . <color>) } )
;;
;; which is generated by the compiler for icon descriptions.  There was
;; no particular advantage of one over the other; rather, they were done by
;; different people, and no one worried about it until there were KBs with
;; both forms in them.  This icon color change pattern is also more wasteful
;; of space.
;;
;; This was fixed up 6/29/89 by making icon color change patterns be like
;; icon color patterns.  For compatibility of 2.0 Beta KBs, however, icon
;; color change patterns will be hand-checked to see if they are in their
;; old form, so that they will work without even needing to be recompiled.
;; After 2.0, old 2.0 Beta KBs will need to be recompiled in order to work
;; (and not to bomb out). (MHD/AGH 6/29/89)




;; Implement "whenever the color of <designation> is changed ..."!

;; Fix this comment in light of changes change-color-of-icon and change-color-pattern-of-
;; icon. (MHD 4/27/89)
;; ;; Do this by drawing the color difference, for greater efficiency!  This could be done
;; ;; by binding special variable workspace-area-background-color? to (icon-color entity)
;; ;; and having on-image-plane use a non-nil value of this in lieu of the
;; ;; workspace area background color of the image plane.  Alternatively, it could be
;; ;; done a la highlight-or-unhighlight-icon!


(defun icon-has-region-p (entity region)
  (let ((icon-description? (icon-description entity)))
    (if icon-description?
	(assq region (icon-color-pattern? icon-description?)))))



;;; The function `change-color-of-item' is called from the evaluator for
;;; GPL expressions of the form "change the [region] icon-color of <item>".

;;; If specific-region? is nil, icon-color, or stripe-color, then color-or-
;;; pattern can be a `color change pattern', a list of the form
;;;
;;;        ( { (region . color) } )
;;;
;;; It must be so specified whenever specific-region? is nil.

;;; Whenever specific-region? is non-nil, color-change-pattern can just be a
;;; color or metacolor.   In that case, specific-region? can either be
;;;
;;;   (a) One of
;;;        icon-color, stripe-color, text-color, background-color,
;;;        foreground-color, or border-color;
;;;
;;;   (b) the name of a stripe region, if item is a connection; or
;;;
;;;   (c) the name of an icon color region, if item is an entity with
;;;        a polychrome icon definition

;;; This function does not assume that its args will be consistent and valid;
;;; it tries to give level 1 warning messages when invalid color changes
;;; are attempted.

(defun change-color-of-item
    (item note-as-kb-state-change? specific-region? color-or-pattern)
  (perform-any-deferred-icon-set-up item)
  (let ((specific-region-ok?
	  (cond
	    ((null specific-region?)
	     (not (null color-or-pattern)))	; ok for now, but still need
							    ;   to check if elements specify
							    ;   valid regions
	    ((color-attribute-p specific-region?)	    ; a color attribute?
	     (cond
	       ((frame-class-case item		; ok if color attributes jibes
		  (connection			;   with class of item
		    (eq specific-region? 'stripe-color))
		  (entity
		    (eq specific-region? 'icon-color))
		  (text-box
		    (memq-p-macro specific-region?
				  '(background-color border-color text-color)))
		  (workspace
		    (memq-p-macro specific-region?
				  '(background-color foreground-color))))
		t)
	       (t
		(warn-of-invalid-color-attribute
		  item specific-region?)
		nil)))
	    (t
	     ;; Here, the color attribute is assumed to be either
	     ;;   icon-color or stripe-color, and item should be
	     ;;   an entity or a connection; however, the source language
	     ;;   allows either icon-color or stripe-color, and unfortunately
	     ;;   we cannot tell here whether they used the correct one in
	     ;;   the source; we always just choose the correct one based
	     ;;   on the class of item.
	     (frame-class-case item
	       ((connection entity) t)
	       (t
		 (warn-of-invalid-color-attribute
		   item specific-region?)
		 nil))))))
    (when specific-region-ok?
      (let* ((color-change-pattern?		; to be reclaimed at end
	       (if (consp color-or-pattern)	;   if not eq to color-or-pattern
		   color-or-pattern
		   (unless (and (color-attribute-p specific-region?)
				(neq specific-region? 'icon-color))
		     (gensym-list
		       (gensym-cons
			 specific-region? color-or-pattern)))))
	     (illegal-colors?
	       (cond (color-change-pattern?
		      (loop for (nil . color) in color-change-pattern?
			    unless (gensym-color-p color)
			      collect color using gensym-cons))
		     ((not (gensym-color-p color-or-pattern))
		      (gensym-list color-or-pattern))))
	     (stack-error-or-nil? nil))

	(cond
	  (illegal-colors?
	   (cond (executing-change-item-color-instruction-p
		  (setq stack-error-or-nil?
			(gensym-cons 'illegal-colors illegal-colors?)))
		 (t (warn-of-illegal-colors illegal-colors?)
		    (reclaim-gensym-list illegal-colors?))))
	  (t
	   (frame-class-case item
	     (connection
	       (if color-change-pattern?
		   (change-color-pattern-of-connection
		     item note-as-kb-state-change? color-change-pattern?)
		   (change-color-of-connection
		     item note-as-kb-state-change? color-or-pattern)))
	     (entity
	       ;; For calls from the instructions change-item-color and change-
	       ;; item-color-pattern, the return value will be error
	       ;; information when a missing or unnamed color region is detected;
	       ;; otherwise the return value will be nil.  (ghw 6/5/95)
	       (setq stack-error-or-nil?
		     (if color-change-pattern?
			 (change-color-pattern-of-icon
			   item note-as-kb-state-change? color-change-pattern?)
			 (change-color-of-icon
			   item note-as-kb-state-change? color-or-pattern))))
	     (text-box
	       (if color-change-pattern?
		   (change-color-of-text-box
		     item note-as-kb-state-change?
		     (or (cdr (assq 'background-color color-change-pattern?))
			 :no-change)
		     (or (cdr (assq 'border-color color-change-pattern?))
			 :no-change)
		     (or (cdr (assq 'text-color color-change-pattern?))
			 :no-change))
		   ;; else, specific-region? should be one of background-color,
		   ;;   border-color, or text-color, AND color-
		   ;;   or-pattern should be a color (or metacolor)
		   (change-color-of-text-box
		     item note-as-kb-state-change?
		     (if (eq specific-region? 'background-color)
			 color-or-pattern
			 :no-change)
		     (if (eq specific-region? 'border-color)
			 color-or-pattern
			 :no-change)
		     (if (eq specific-region? 'text-color)
			 color-or-pattern
			 :no-change))))
	     (workspace
	       (if color-change-pattern?
		   (change-color-of-workspace
		     item note-as-kb-state-change?
		     (or (cdr (assq 'background-color color-change-pattern?))
			 :no-change)
		     (or (cdr (assq 'foreground-color color-change-pattern?))
			 :no-change))
		   ;; else, specific-region? should be one of background-color or
		   ;;   foreground-color, AND color-or-pattern should
		   ;;   be a color (or metacolor)
		   (change-color-of-workspace
		     item note-as-kb-state-change?
		     (if (eq specific-region? 'background-color)
			 color-or-pattern
			 :no-change)
		     (if (eq specific-region? 'foreground-color)
			 color-or-pattern
			 :no-change)))))
	   (when g2-has-v5-mode-windows-p
	     (unless (or stack-error-or-nil?
			 (workspace-p item))
	       (send-ws-representations-item-color-pattern-change
		 item
		 specific-region?
		 color-or-pattern)))
	   ;; Notify subscribers of color-change (separate from TW2
	   ;; ws-representation stuff above
	   (update-subscriptions-for-color-change
	     item color-or-pattern specific-region?)))
	(unless (eq color-change-pattern? color-or-pattern)
	  (reclaim-gensym-tree color-change-pattern?))
	stack-error-or-nil?))))

;; Unfortunately, information which could tell whether specific-region? was supplied
;; as a region (e.g., as is FOO in "change the FOO stripe-color of ...") or as a color
;; attribute (e.g. as is FOO in "change the FOO of ...") is discarded by this point!
;; That's why we have to warn that specific-region? is an invalid color attribute
;; or region, whereas we really could know which one were we to preserve that
;; information!
;;
;; In other words, as things now stand, if FOO is an entity which has a BAR region,
;; the system lets you change the color of the BAR region by saying "change the BAR
;; stripe-color of FOO to ...", and, similarly, if FOO is a connection which has a
;; BAR stripe region, the system lets you change the BAR stripe color by saying
;; "change the BAR icon-color of FOO to ...".
;;
;; This is a bug we have to live with for 2.0!!  (MHD 3/27/90)

;; Another way to do this would be to have change-color-pattern methods for
;; the various classes.




;;; The function `adjust-icon-rendering-usage-counts' increments or decrements
;;; the usage counts for each icon rendering of the given entity.

(defun adjust-icon-rendering-usage-counts (block image-plane? now-showing?)
  (when (and (entity-p block)
	     (icon-description block))
    (let ((window? (and image-plane?
			(gensym-window-for-pane (pane-for-image-plane image-plane?)))))
      (loop for icon-rendering in (icon-renderings (icon-description block)) doing
	(when (or (null window?)
		  (eq window? (window-for-icon-rendering icon-rendering)))
	  (setf (number-of-times-used-in-cache? icon-rendering)
		(if now-showing?
		    (1+f (number-of-times-used-in-cache? icon-rendering))
		    (maxf 0 (1-f (number-of-times-used-in-cache? icon-rendering))))))))))

;; Called from event-update-status-of-block-showing (PANES).  It is here in
;; order to pick the entity-p and other macros.
;; This is really a place-holder implementation, pending stress tests. -fmw, 1/10/94






;;; The function `get-color-pattern-of-item' returns an `icon color change
;;; pattern', which is an a-list similar to an icon color pattern, except that
;;; the car of each element is always a region, not a color.  There is one
;;; a-list entry for each of the named regions of item.  The a-list is composed
;;; of slot value conses and symbols.  It is of the form
;;;
;;;    ( { (region . color-or-metacolor) } )
;;;
;;; The functions `get-connection-color-pattern', `get-color-pattern-of-icon',
;;; `get-workspace-color-pattern', and `get-text-box-color-pattern' return the
;;; color pattern for a connection, entity, workspace, and text box,
;;; respectively.  Note that for any other class, nil is returned as the color
;;; pattern by get-color-pattern-of-item.
;;;
;;; State? can be either nil, CURRENT, PERMANENT, or DEFAULT.  Nil or CURRENT
;;; gets the current pattern.  PERMANENT gets the pattern saved away in the
;;; original KB state plist.  And DEFAULT gets the pattern defined for instances
;;; of the particular class if item, either by the user or system as
;;; appropriate.
;;;
;;; Explicit? can be either true (non-nil) or false (nil).  If true, then all
;;; colors in the pattern are explicit colors or metacolors, and nil never
;;; appears.  If false, nil may appear.  The false case should only be used
;;; therefore for geting internally visible color patterns.  Note that in some
;;; cases, this distinction is not necessary; i.e., nil sometimes never appears
;;; for certain classes of item, e.g., entity and connection.
;;;
;;; If include-unnamed? is true, entries for unnamed regions, i.e., of the form
;;; (color-or-metacolor . color-or-metacolor), are included in the pattern.
;;; Note that this actually makes it a "proper" color pattern, as opposed to a
;;; "color change pattern".  This is used by the initialize-after-reading method
;;; for entity, which must ensure that the complete color pattern stored on the
;;; plist of system-defined icons is correct.  (Note that connections only
;;; differ in that they only have a color change pattern stored on their plist.
;;; Also, unfortunately we've not implemented a means of fixing up changes to
;;; their patterns at KB load time, and perhaps not even at redefinition time;
;;; a bug I've inherited most likely! (MHD 8/21/95))

;; Fix for next release: make this a method!!  See also
;; colorable-regions-of-frame, with which there is considerable overlap!
;;
;; Note that colorable-regions-of-frame (used for color menus) does not
;; give border-color for borderless text boxes.  This does. Not sure which
;; is right.
;;
;; (MHD 8/17/95)

;; Notes:
;;
;;   (1) connections and icons never have explicit colors
;;
;;   (2) workspaces and text boxes never have unnamed regions


(defun get-color-pattern-of-item (item &optional state? explicit? include-unnamed? override-only?)
  (frame-class-case item
    (connection (get-connection-color-pattern item state? explicit? include-unnamed? override-only?))
    (entity (get-icon-color-pattern item state? explicit? include-unnamed? override-only?))
    (workspace (get-workspace-color-pattern item state? explicit? include-unnamed? override-only?))
    (text-box (get-text-box-color-pattern item state? explicit? include-unnamed? override-only?))
    (t '())))

(defun get-connection-color-pattern
    (connection &optional state? explicit? include-unnamed? override-only?)
  (let* ((base-color-pattern
	   (loop for (color-or-region . color)
		     in (get-cross-section-regions-function
			  (get-slot-init-form
			    (class connection) 'cross-section-pattern))
		 when (or include-unnamed? (not (eq color-or-region color)))
		   nconc
		   (slot-value-list (slot-value-cons color-or-region color))))
	 (override-pattern		; shared list structure
	   (case state?
	     ((nil current permanent)
	      (or (if (eq state? 'permanent)
		      (getf (original-kb-state-plist connection)
			    'connection-color-pattern))
		  (get-cross-section-regions-function
		    (get-slot-value connection 'cross-section-pattern)))))))
    (if override-only?
	(progn
	  (reclaim-slot-value base-color-pattern)
	  (normalize-color-pattern override-pattern))
	(merge-color-patterns
	  override-pattern base-color-pattern
	  (not explicit?)))))


(defun get-icon-color-pattern
    (entity &optional state? explicit? include-unnamed? override-only?)
  (let* ((base-color-pattern
	   (loop for (color-or-region . color)
		     in (icon-color-pattern? (icon-description entity))
		 when (or include-unnamed? (not (eq color-or-region color)))
		   nconc
		   (slot-value-list (slot-value-cons color-or-region color))))
	 (override-pattern		; shared list structure
	   (case state?
	     ((nil current permanent)
	      (or (if (eq state? 'permanent)
		      (getf (original-kb-state-plist entity)
			    'icon-color-pattern))
		  (getf
		    (icon-attributes-plist entity)
		    'icon-color-pattern))))))
    (if override-only?
	(progn
	  (reclaim-slot-value base-color-pattern)
	  (normalize-color-pattern override-pattern))
	(merge-color-patterns
	  override-pattern base-color-pattern
	  (not explicit?)))))


(defun get-workspace-color-pattern
    (workspace &optional state? explicit? include-unnamed? override-only?)
  (declare (ignore include-unnamed?))
  (let ((base-color-pattern
	  (nsubst
	    (or (get-slot-init-form
		  (class workspace)
		  'workspace-background-color?)
		(if explicit? 'white))
	    ':bg
	    (nsubst
	      (or (get-slot-init-form
		    (class workspace)
		    'workspace-foreground-color?)
		  (if explicit? 'black))
	      ':fg
	      (copy-for-slot-value
		'((background-color . :bg)
		  (foreground-color . :fg))))))
	(override-pattern		; copied list structure
	  (case state?
	    ((nil current permanent)
	     (or (if (eq state? 'permanent)
		     (copy-for-slot-value
		       (getf (original-kb-state-plist workspace)
			     'workspace-color-pattern)))
		 (nsubst
		   (workspace-background-color? workspace)
		   ':bg
		   (nsubst
		     (workspace-foreground-color? workspace)
		     ':fg
		     (copy-for-slot-value
		       '((background-color . :bg)
			 (foreground-color . :fg))))))))))
    (if override-only?
	(progn
	  (reclaim-slot-value base-color-pattern)
	  override-pattern)
	(prog1 (merge-color-patterns
		 override-pattern base-color-pattern
		 (not explicit?))
	  (reclaim-slot-value override-pattern)))))


(defun get-text-box-color-pattern (text-box &optional state? explicit? include-unnamed? override-only?)
  (declare (ignore include-unnamed?))
  (let* ((text-cell-plist
	   (get-slot-value text-box 'text-cell-plist-for-text-box))
	 (text-box-format
	   (get-slot-value text-box 'text-box-format))
	 (base-color-pattern
	   (nsubst
	     (or (get-slot-value text-box-format 'text-cell-background-color?)
		 (if explicit? 'transparent))
	     ':bg
	     (nsubst
	       (or (get-slot-value text-box-format 'text-box-border-color?)
		   (if explicit? current-default-line-color)) ; note 1
	       ':border
	       (nsubst
		 (or (get-slot-value text-box-format 'text-cell-line-color?)
		     (if explicit? current-default-line-color))
		 ':text
		 (copy-for-slot-value
		   '((background-color . :bg)
		     (border-color . :border)
		     (text-color . :text)))))))
	 (override-pattern		; copied list structure
	   (case state?
	     ((nil current permanent)
	      (or (if (eq state? 'permanent)
		      (copy-for-slot-value
			(getf (original-kb-state-plist text-box)
			      'text-box-color-pattern)))
		  (nsubst
		    (getf text-cell-plist 'background-color)
		    ':bg
		    (nsubst
		      (getf text-cell-plist 'border-color)
		      ':border
		      (nsubst
			(getf text-cell-plist 'line-color)
			':text
			(copy-for-slot-value
			  '((background-color . :bg)
			    (border-color . :border)
			    (text-color . :text))))))))
	     (default
	       (let ((text-cell-plist-for-class
		       (slot-init-form
			 (slot-description-from-class
			   (class text-box) 'text-cell-plist-for-text-box))))
		 (nsubst
		   (getf text-cell-plist-for-class 'background-color)
		   ':bg
		   (nsubst
		     (getf text-cell-plist-for-class 'border-color)
		     ':border
		     (nsubst
		       (getf text-cell-plist-for-class 'line-color)
		       ':text
		       (copy-for-slot-value
			 '((background-color . :bg)
			   (border-color . :border)
			   (text-color . :text)))))))))))
    (if override-only?
	(progn
	  (reclaim-slot-value base-color-pattern)
	  override-pattern)
	(prog1 (merge-color-patterns
		 override-pattern base-color-pattern
		 (not explicit?))
	  (reclaim-slot-value override-pattern)))))

;; Note 1: it seems that we should not use current-default-line-color, but
;; instead TRANSPARENT.  However, that would not be consistent with what
;; item-color does in this case.  Now, changing item-color might be a good
;; idea, but it is too incompatible and risky a change to attempt at this
;; time. Review later!  (MHD 8/22/95)



;;; `Merge-color-patterns' destructively alters the cdrs of the a-list entries
;;; in base-color-pattern with overrides from the corresponding entries in
;;; override-pattern.  However, unless null-colors-can-override? is true, nil
;;; will not be used to replace a color in the base color pattern.
;;;
;;; Override-pattern is not consumed in any way by this function.
;;;
;;; This returns base-color-pattern a-list after it has been altered.  This
;;; function is a subfunction of the "methods" for getting color patterns,
;;; above.

(defun merge-color-patterns
    (override-pattern base-color-pattern null-colors-can-override?)
  (loop for (color-or-region . color?) in override-pattern
	as entry-in-base
	   = (assq color-or-region base-color-pattern)
	when (and (not (eq color-or-region color?))
		  entry-in-base
		  (or color?
		      null-colors-can-override?))
	  do (setf (cdr entry-in-base) color?))
  base-color-pattern)

(defun normalize-color-pattern (override-pattern)
  (loop for (color-or-region . color?) in override-pattern
	unless (eq color-or-region color?)
	  collect (slot-value-cons color-or-region color?)
	  using slot-value-cons))






;;;; Highlighting Icons



;;; Highlight-or-unhighlight-icon ... returns nil only in two cases: (1) the highlight
;;; case when the highlight color of icon is already new-highlight-color, and (2) the
;;; unhighlight case when there is no highlight color.

;(defun highlight-or-unhighlight-icon (entity new-highlight-color unhighlight-case?)
;  (let ((old-highlight-color?
;	  (getf (icon-attributes-plist entity) 'highlight-color)))
;    (cond
;      ((if unhighlight-case?
;	   old-highlight-color?
;	   (not (eq old-highlight-color? new-highlight-color)))
;       (if unhighlight-case?
;	   (change-icon-attribute entity 'highlight-color nil))
;       (update-images
;	 unhighlight-case? (superblock? entity)
;	 (left-edge-of-block entity) (top-edge-of-block entity)
;	 (right-edge-of-block entity) (bottom-edge-of-block entity)
;	 t 'highlight-icon entity new-highlight-color)
;       (if (not unhighlight-case?)
;	   (change-icon-attribute
;	     entity 'highlight-color new-highlight-color))))))

;; Maybe needs work in nested case.

;; Was part of scrolling arrows, but is currently unused. - ben 4/08/93


;;; `Highlight-icon' is an unused draw function.

#+unused
(defun highlight-icon (entity highlight-color)
  (let* ((left-edge-of-icon-in-window
	   (x-in-window (left-edge-of-block entity)))
	 (top-edge-of-icon-in-window
	   (y-in-window (top-edge-of-block entity)))
	 (right-edge-of-icon-in-window
	   (+r (x-in-window (right-edge-of-block entity)) 1))
	 (bottom-edge-of-icon-in-window
	   (+r (y-in-window (bottom-edge-of-block entity)) 1))
	 (old-background-color-value
	   (let ((old-highlight-color?
		   (getf (icon-attributes-plist entity) 'highlight-color)))
	     (if old-highlight-color?
		 (map-color-or-metacolor-to-color-value
		   old-highlight-color?)
		 current-background-color-value)))
	 (new-background-color-value
	   (map-color-or-metacolor-to-color-value
	     highlight-color)))
    (cond
      ((not (=f new-background-color-value	;=color ??
		old-background-color-value))
       (if (not (=f old-background-color-value	;=color ??
		    current-background-color-value))
	   (let ((erase-instead? (not erase-instead?)))
	     (draw-solid-rectangle
	       left-edge-of-icon-in-window top-edge-of-icon-in-window
	       right-edge-of-icon-in-window bottom-edge-of-icon-in-window
	       (color-difference
		 old-background-color-value current-background-color-value))))
       (if (not (=f new-background-color-value	;=color ??
		    current-background-color-value))
	   (draw-solid-rectangle
	     left-edge-of-icon-in-window top-edge-of-icon-in-window
	     right-edge-of-icon-in-window bottom-edge-of-icon-in-window
	     (color-difference
	       new-background-color-value current-background-color-value)))))))

;; Fix entity draw method for efficiency -- and draw highlight rectangle if
;; it has a highlight color!  Eliminate "fine positioning"?

;; Consider abstracting portions of this that are common to the draw method.


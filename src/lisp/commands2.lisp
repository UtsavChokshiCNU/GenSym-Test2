;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module COMMANDS2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;;;; Forward References



(declare-forward-references
  (enter-icon-editor function icons5)

  ;; in G2-BPEL:
  (compile-g2gl-process-if-possible function)
  (compile-g2gl-process-if-necessary-and-possible function)
  (instantiate-g2gl-process-and-start-execution function)
  (report-g2gl-compilation-completion-status function)
  (there-are-g2gl-compilations-postings-on-body function)
  (clear-g2gl-compilation-postings-on-body function)
  (map-g2gl-execution-display-to-source-process-if-any function)
  (map-g2gl-execution-display-to-source-body-if-any function)
  (map-g2gl-execution-display-to-execution-frame-if-any function)
  (g2gl-execution-display-is-for-paused-process-p function)
  (do-pause-process-instance-command function)
  (do-resume-process-instance-command function)
  (unset-temporary-breakpoint-for-surrogate-activity-p function)
  (set-temporary-breakpoint-for-surrogate-activity function)
  (unremoved-temporary-breakpoint-for-surrogate-activity-p function)
  (remove-temporary-breakpoint-for-surrogate-activity function)
  (g2gl-activity-has-no-standard-in-connections-p function)
  (g2gl-standard-connection-class variable)
  (g2gl-standard-connection-line-pattern variable)
  (g2gl-standard-connection-arrows variable)
  (delete-g2gl-execution-display function)
  (redo-layout-of-g2gl-body function)
  (g2gl-parameters variable)
  ;; In FRAMES2A
  (frame-hash-function function))




;;;; UI commands, part 2.



(define-ui-command new-object ((class (class-name 'object))
                               workspace image-plane original-x-in-window original-y-in-window)
  "Create a new object of a chosen class upon this workspace."
  (when (object-creation-on-workspace-allowed-p workspace)
    (when (classp class)
      (make-instance-interactively
        class image-plane original-x-in-window original-y-in-window))))


;; also meter, graph, readout-table, control-panel!

(define-ui-command new-display ((class (class-name '(readout-table dial meter trend-chart
                                                     graph chart freeform-table)))
                                workspace
                                image-plane original-x-in-window original-y-in-window)
  "Create a new display upon this workspace."
  (when (restricted-object-creation-on-workspace-allowed-p workspace)
    (make-instance-interactively class image-plane original-x-in-window original-y-in-window)))



;; free-text suffices?
;; move to top level "New Message" ??

(define-ui-command new-free-text ((class (class-name '(free-text borderless-free-text text-inserter message)))
                                  workspace
                                  image-plane original-x-in-window original-y-in-window)
  "Create a new text object."
  (when (object-creation-on-workspace-allowed-p workspace)
    (make-instance-interactively class image-plane original-x-in-window original-y-in-window)))




(define-ui-command new-button ((class (class-name '(action-button radio-button check-box slider type-in-box)))
                               workspace
                               image-plane original-x-in-window original-y-in-window)
  "Create a new button."
  (when (restricted-object-creation-on-workspace-allowed-p workspace)
    (make-instance-interactively class image-plane original-x-in-window original-y-in-window)))




(define-ui-command new-rule ((class class-of-rule)
                             workspace image-plane original-x-in-window original-y-in-window)
  "Create a new rule and place it on a workspace"
  (when (restricted-object-creation-on-workspace-allowed-p workspace)
    ;; This is the  def-class-choice-action text-box  in facilities.
    ;; It works because rules are text-boxes!!
    ;; The editor gets the grammar from  (get-slot-feature-if-any 'rule 'box-translation-and-text 'type).
    (act-on-choice-of-a-text-box class
                                 image-plane
                                 original-x-in-window original-y-in-window)))




;; restricted use license now allowed to create new definition, but
;; only real definition subclass instances, not "definitional items"
;; like procedure, etc.  That filtering happens in the handler.
;; 5/14/92   -ML-

;; This filtering is now supposed to happen in the class-of-definition presentation-type,
;; but is not yet implemented! -fmw, 11/30/93

(define-ui-command new-definition ((class class-of-definition) workspace
                                   image-plane original-x-in-window original-y-in-window)
  "Create a new type of definitional item: class definition, message definition, procedure, etc."
  (when (object-creation-on-workspace-allowed-p workspace)
    (make-instance-interactively class image-plane original-x-in-window original-y-in-window)))





;; "Item" is the user's name for "frame".

;; Enable and disable for items and workspaces are separated for the benefit of
;; the item-submenu.

(define-ui-command enable ((frame frame-or-subframe))
  "Enable this item."
  (when (and (manually-disabled-p frame)
             (frame-may-be-enabled-or-disabled-p frame t))
    (funcall-method 'manually-enable frame)))

(define-ui-command (enable-item :name enable) ((frame frame-or-subframe))
  "Enable this item."
  (when (and (not (workspace-p frame))
             (manually-disabled-p frame)
             (frame-may-be-enabled-or-disabled-p frame t))
    (funcall-method 'manually-enable frame)))

(define-ui-command (enable-workspace :name enable) (workspace)
  "Enable this workspace."
  (when (and (manually-disabled-p workspace)
             (frame-may-be-enabled-or-disabled-p workspace t))
    (funcall-method 'manually-enable workspace)))


(define-ui-command disable ((frame frame-or-subframe))
  "Disable this item.  Disabled items are visible only to inspect commands."
  (when (and (not (manually-disabled-p frame))
             (frame-may-be-enabled-or-disabled-p frame t))
    (funcall-method 'manually-disable frame)))

(define-ui-command (disable-item :name disable) ((frame frame-or-subframe))
  "Disable this item.  Disabled items are visible only to inspect commands."
  (when (and (not (workspace-p frame))
             (not (manually-disabled-p frame))
             (frame-may-be-enabled-or-disabled-p frame t))
    (funcall-method 'manually-disable frame)))

(define-ui-command (disable-workspace :name disable) (workspace)
  "Disable this workspace.  Disabled items are visible only to inspect commands."
  (when (and (not (manually-disabled-p workspace))
             (frame-may-be-enabled-or-disabled-p workspace t))
    (funcall-method 'manually-disable workspace)))



(define-ui-command (name-workspace :name name) (workspace)
  "Give this workspace a name, or edit the existing name."
  (when (and (or (user-workspace-p workspace)
                 (frame-of-class-p                            ; see the def-class in module EDIT
                   workspace 'category-instance-menu-workspace)
                 (frame-of-class-p workspace 'message-board) ; continue to allow
                 (frame-of-class-p workspace 'scrapbook))   ;   these to be named
                                                            ;   for now (MHD 8/29/88)
             (type-of-slot-if-editable (class workspace) 'name-or-names-for-frame)
             (item-is-either-not-permanent-or-from-an-editable-module-p workspace))
    (enter-editing-context                                    ; NOTE: similar code in block case
      workspace 'name-or-names-for-frame                    ; will be part of current context
      (make-text-representation-for-slot-value
        workspace 'name-or-names-for-frame)
      ;; specify text-box-format, width-for-cell?, width-for-initial-text?!
      )))


(define-ui-command (move-workspace :name move)
    (image-plane original-x-in-window original-y-in-window)
  "Move this workspace"
  (set-cursor-position original-x-in-window original-y-in-window)
  (enter-image-plane-dragging-context
    image-plane
    (-r original-x-in-window (left-edge-of-image-in-window image-plane))
    (-r original-y-in-window (top-edge-of-image-in-window image-plane))))


(define-ui-command (color-workspace :name color)
    ((region ((member '(foreground-color background-color)) :title 'choose-a-region))
     (color ((color) :title region))
     (workspace workspace))
  "Change the foreground or background color of this workspace."
  (when (and (user-workspace-p workspace)
             (transient-or-permanent-p workspace)
             (item-is-either-not-permanent-or-from-an-editable-module-p workspace))
    (change-color-of-item workspace nil region color)))


(define-ui-command clone-workspace (workspace image-plane)
  "Create a copy of this workspace, which differs only in its name"
  (when (and (frame-of-class-p workspace 'kb-workspace)
             (not (proprietary-p workspace))
             #+pre-g2-v5-licensing (not (runtime-option-authorized-p))
             #+pre-g2-v5-licensing (not (embedded-option-authorized-p)))
    (let ((new-workspace
            (clone-frame workspace)))

      ;; after cloning a workspace, set its transient bit apropriately and propagate.  This is
      ;; necessary because frame-flags-2 is not being cloned by clone-frame, and
      ;; probably shouldn't.   -dkuznick, 5/17/99
      (when (transient-p workspace)
        (set-transient-and-propagate new-workspace nil))

      (when (and (permanent-block-p new-workspace)
                 (null (parent-of-subworkspace? new-workspace))
                 (reason-permanent-items-module-is-not-editable new-workspace))
        (setf (module-this-is-part-of? new-workspace) nil))

      ;; after cloning a workspace, activate it if appropriate: (MHD 10/25/91)
      (when (and (or system-is-running system-has-paused)
                 (not (active-p new-workspace)))
        (funcall-method 'activate-if-possible-and-propagate new-workspace))
      (put-workspace-on-pane
        new-workspace current-workstation-detail-pane
        'center 'center
        (maxf (image-x-scale image-plane)
              (image-y-scale image-plane))))))

;; Why doesn't this enter workspace dragging context, since that is
;; what cloning an entity does?



(defun allow-color-menu-choice (frame)
  (cond ((text-box-p frame)
         (transient-or-permanent-p frame))
        ((entity-p frame)
         (or (not (polychrome-icon-p frame))
             (null (regions-and-colors-of-entity frame))
             (loop for (region . color) in (regions-and-colors-of-entity frame)
                   thereis (or (not (eq region color))
                               (eq region 'foreground)))))
        (t t)))



(define-ui-command color ((frame most-interesting-frame)
                          (region (colorable-regions-of-frame frame))
                          (color ((metacolor) :title region)))
  "Change the color of a selected region of this item"
  (when (and (allow-color-menu-choice frame)
             (item-is-either-not-permanent-or-from-an-editable-module-p frame))
    (change-color-of-item frame nil region color)))

;; If there is exactly one colorable region (icon-color), then the
;; COLORABLE-REGIONS-OF-FRAME pres type returns an immediate value, hence the
;; region submenu is skipped.

;; The COLOR command used to operate on the magic argument BLOCK, which caused
;; it to run on the item-represented by tables, instead of on the table itself.
;; This issue does not arise normally because COLOR is not even in the menu
;; for attribute tables.  It only obtains when the user has effectively added
;; COLOR to that menu by binding some keystroke to the command.
;; As you might guess, this is still a pretty fuzzy design.



(define-ui-command describe-configuration ((item frame-or-subframe))
  "Describe the item configurations which apply to this item"
  (when (transient-or-permanent-p item)
    ;; Was: (pane-for-image-plane image-plane)
    (describe-restrictions-on-temporary-workspace item current-workstation-detail-pane)))

(define-ui-command (describe-configuration-of-item :name describe-configuration)
    ((item frame-or-subframe))
  "Describe the item configurations which apply to this item"
  (when (and (not (workspace-p item))
             (transient-or-permanent-p item))
    ;; Was: (pane-for-image-plane image-plane)
    (describe-restrictions-on-temporary-workspace item current-workstation-detail-pane)))

(define-ui-command (describe-configuration-of-workspace :name describe-configuration)
    (workspace)
  "Describe the item configurations which apply to this item"
  (when (transient-or-permanent-p workspace)
    ;; Was: (pane-for-image-plane image-plane)
    (describe-restrictions-on-temporary-workspace workspace current-workstation-detail-pane)))

;; Old KBS which refer to describe-restrictions in some "selecting any implies ..." clause
;; are automatically updated to refer to describe-configuration, instead.  So, it should
;; be safe to remove the describe-restrictions command completely.


(define-ui-command describe ((item frame-or-subframe))
  "Describe this item"
  (when (transient-or-permanent-p item)                    ; Text-box test.
    (describe-item-on-temporary-workspace item)))

(define-ui-command (describe-item :name describe) ((item frame-or-subframe))
  "Describe this item"
  (when (and (not (workspace-p item))
             (transient-or-permanent-p item))                    ; Text-box test.
    (describe-item-on-temporary-workspace item)))

(define-ui-command (describe-workspace :name describe) (workspace)
  "Describe this workspace"
  (when (transient-or-permanent-p workspace)                    ; Text-box test.
    (describe-item-on-temporary-workspace workspace)))

(define-ui-command operate-on-area (workspace image-plane
                                              original-x-in-window original-y-in-window)
  (when (and (not (selection-enabled-p))
             (user-workspace-p workspace)
             (item-is-either-not-permanent-or-from-an-editable-module-p workspace))
    (operate-on-area-of-workspace
      workspace image-plane original-x-in-window original-y-in-window)))



(define-ui-command print-to-server (workspace)
  "Print workspace to a PostScript(TM) file on the G2 server."
  (when (and (frame-system-operation-is-allowed-p 'show-workspace workspace)
             (item-menu-command-permitted-p 'print workspace))
    (print-workspace workspace)))

(define-ui-command go-to-superior (workspace)
  (when (let ((parent? (parent-of-subworkspace? workspace)))
          (and parent?
               (workspaces-can-be-shown-at-this-kb-level-p
                 parent? current-workstation)))
    (goto-frame-instance (parent-of-subworkspace? workspace))))

(define-ui-command hide-workspace (workspace image-plane)
  "Hide this workspace"
  (when (workspace-can-be-hidden? workspace)
    (delete-image-plane image-plane)))


(define-ui-command delete-workspace (workspace)
  "Delete this workspace"
  (when (and (not (computation-frame-at-breakpoint-depends-on-block-p workspace))
             (item-is-either-not-permanent-or-from-an-editable-module-p workspace))
    (let ((x (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
          (y (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))
      ;; GENSYMCID-1015: Inconsistent modularization deleting a workspace.
      (delete-workspace-for-user workspace x y))))

;; This guy normally asks for confirmation, which is the only reason it wants x
;; and y.  We want the latest x,y, so we must bind them in the body of the
;; command, rather than in its arglist.




;;; The command `align-text command' gives the user the option to select
;;; alignment, LEFT, CENTER, or RIGHT -- some day, JUSTIFIED may be handled in
;;; addition, on any permanent or transient text box.  (Items that are not
;;; permanent or transient are typically not part part of the permanent or
;;; transient part of the KB, but are used as system-controlled, items, e.g.,
;;; logbook messages.)  The `text-alignment presentation type' just defines the
;;; valid submenu choices to select the alignment: left, center, right, or
;;; justified.

(define-presentation-type text-alignment ()
  :menu-options (:title align-text)
  :choices '(left center right
             ;; justified ; some day!
             ))


(define-ui-command align-text
    ((text-box text-box)
     (text-alignment text-alignment))
  (when (transient-or-permanent-p text-box)  ; "user-item-p"?!
    (update-text-box-alignment-override text-box text-alignment)))


(define-presentation-type font ()
  :menu-options (:title font)
  :choices '(small large extra-large))        ; Hardcoded all over the place.

(define-ui-command font
    ((font font)
     (text-box text-box))
  (when (transient-or-permanent-p text-box)
    ;; This change is not really via a system procedure.
    (let ((note-kb-state-changes-via-system-procedures? nil))
      (g2-set-font-of-text-box-1 text-box font nil nil))))


#+development
(define-ui-command disassemble (procedure)
  "Disassemble this procedure."
  (unless (text-slots-in-frame-have-been-stripped-p procedure)
    (disassemble-procedure-on-temporary-workspace procedure)))


;;;; Explanation-related commands



(define-ui-command dynamic-rule-invocation-display (rule)
  (when (explanation-related-features-enabled? miscellaneous-parameters)
    (make-dynamic-rule-invocation-display rule)))    ; can't be subframe

(define-ui-command dynamic-backward-chaining (variable)
  (when (explanation-related-features-enabled? miscellaneous-parameters)
    (make-backward-chaining-display variable)))

(define-ui-command describe-chaining (variable)
  (when (explanation-related-features-enabled? miscellaneous-parameters)
    (make-static-chaining-display variable)))

(define-ui-command dynamic-generic-rule-display (object)
  (when (explanation-related-features-enabled? miscellaneous-parameters)
    (make-dynamic-generic-rule-display object)))



;;;; EDIT commands


(def-substitution-macro licensing-restricts-edit
    (block slot-name)
  (or
    (and
      (or (eq slot-name 'box-translation-and-text)
          (eq slot-name 'procedure-definition))
      #+runtime-functionality-without-a-license
      t
      #-runtime-functionality-without-a-license
      (g2-limited-to-this-license-level-or-more restricted-use)
      (or (frame-of-class-p block 'procedure)
          (frame-of-class-p block 'rule)))
    (and
      (eq slot-name 'icon-description-for-class?)
      (frame-of-class-p block 'class-definition)
      #+runtime-functionality-without-a-license
      t
      #-runtime-functionality-without-a-license
      (g2-limited-to-this-license-level-or-more runtime)
      )))

;; jh, 8/16/96. Devious name, just in case.

(defun-simple update-editor-possibility-cache (block slot-name)
  (licensing-restricts-edit block slot-name))


;;; The function `permit-edit-text-slot-p' returns T if given text-valued slot
;;; of item can be and may be edited by the user.

(defun permit-edit-text-slot-p (item text-slot-name)
  (and (type-of-slot-if-editable (class item) text-slot-name)
       (not (text-slots-in-frame-have-been-stripped-p item))
       #+runtime-functionality-without-a-license
       nil
       #-runtime-functionallity-without-a-license
       (not (g2-limited-to-this-license-level-or-more restricted-use))
       (item-is-either-not-permanent-or-from-an-editable-module-p item)))

(defun edit-procedure-ok-for-ui-command-p (procedure)
  (permit-edit-text-slot-p procedure 'procedure-definition))

(define-ui-command (edit-procedure :name edit) (procedure)
  (when (edit-procedure-ok-for-ui-command-p procedure)
    (enter-editing-context procedure 'procedure-definition)))

(define-ui-command (edit-action-button :name edit) (action-button)
  (when (permit-edit-text-slot-p action-button 'translation-and-text-of-embedded-rule)
    (enter-editing-context action-button 'translation-and-text-of-embedded-rule)))

(define-ui-command (edit-name-box :name edit) (name-box)
  (when (and (type-of-slot-if-editable (class (superblock? name-box)) 'name-or-names-for-frame)
             (item-is-either-not-permanent-or-from-an-editable-module-p name-box))
    (enter-editing-context (superblock? name-box) 'name-or-names-for-frame)))

;; Note that editing of name boxes for non-kb-workspaces is generally allowed
;; -- in particular, it has documented functionality for
;; category-instance-menu-workspace instances, and it would seem useful for
;; Inspect workspace.  Message boards may also be renamed, or given a new
;; "first name", perhaps using a different language or terminology.  (MHD
;; 10/29/91)


(define-ui-command (edit-text-box :name edit)
    (text-box block-being-represented
              image-plane original-x-in-window original-y-in-window)
  (when (and (editable-text-box-p text-box)
             (not (licensing-restricts-edit
                    block-being-represented 'box-translation-and-text)))
    (frame-class-case text-box
      ((or inspect-command inspect-history) (handle-inspect-command text-box))
      (t
        (enter-editing-context-on-text-box
          text-box image-plane
          original-x-in-window original-y-in-window)))))


(define-ui-command edit-icon (class-definition)
  "Edit the icon associated this object definition"
  (when (and (class-definition-defines-user-editable-icon-class-p
               class-definition)
             #+runtime-functionality-without-a-license
             nil
             #-runtime-functionality-without-a-license
             (not (g2-limited-to-this-license-level-or-more runtime))
             (item-is-either-not-permanent-or-from-an-editable-module-p class-definition))
    (enter-icon-editor class-definition)))

;; This used to look first at frame then at block.


;;; The ui-command `edit-icon-from-table' is active over the
;;; icon-description slot of the table of an object-definition.

(define-ui-command (edit-icon-from-table :name edit-icon)
    (slot-name class-definition)
  (when (and (eq slot-name 'icon-description-for-class?)
             (class-definition-defines-user-editable-icon-class-p
               class-definition)
             #+runtime-functionality-without-a-license
             nil
             #-runtime-functionality-without-a-license
             (not (g2-limited-to-this-license-level-or-more runtime))
             (item-is-either-not-permanent-or-from-an-editable-module-p class-definition))
    (enter-icon-editor class-definition)))



;;; The variable `tightness-of-text-spot-for-click-to-edit' is rebound sometimes
;;; by the selection UI to a looser value (100).

(defvar tightness-of-text-spot-for-click-to-edit 50)

;; See fill-out-text-spot for the meaning of the various magic numbers.



;;; `Click-to-edit' is invoked by post-object-menu.  Because it is invoked
;;; directly it must check restrictions, which editable-text-spot-p does
;;; for it.

(define-ui-command click-to-edit
    (editable-text-spot-p ;; Note B.
      block-being-represented
      block-showing-representation
      image-plane
      slot-name
      x-in-window
      y-in-window
      &optional
      defining-class)
  (when (and (or (<= (tightness-of-text-spot editable-text-spot-p)
                     tightness-of-text-spot-for-click-to-edit)
                 (null defining-class)
                 (feature-assq ;; Once only in G2.
                   'edit-only
                   (slot-features
                     (get-slot-description-if-editable-attribute
                       block-being-represented
                       (alias-slot-name-if-necessary slot-name block-being-represented)
                       defining-class))))
             (non-menu-choice-permitted-p
               'click-to-edit block-being-represented)
             (not (frame-of-class-p block-showing-representation 'name-box))
             (enclosing-item-of-text-spot-visible-p editable-text-spot-p)
             (not (frame-of-class-p block-showing-representation 'scrap))
             (not (message-on-logbook-p block-showing-representation))
             (not (licensing-restricts-edit
                    block-being-represented slot-name))
             (not (and
                    #+runtime-functionality-without-a-license
                    t
                    #-runtime-functionality-without-a-license
                    (g2-limited-to-this-license-level-or-more runtime)
                    (eq slot-name 'icon-description)))
             (if (ab-typep editable-text-spot-p 'table-spot)
                 (editable-text-cell-p
                   block-showing-representation
                   (table-cell-of-spot? editable-text-spot-p))
                 (editable-text-box-p block-showing-representation)))
    (frame-class-case block-showing-representation
      (table
        (enter-text-editor-on-text-cell
          block-showing-representation
          (table-cell-of-spot? editable-text-spot-p)
          image-plane x-in-window y-in-window
          (line-index-of-text-spot editable-text-spot-p)
          (character-index-of-text-spot editable-text-spot-p)))
      ((or inspect-history inspect-command)
        (handle-inspect-command
          block-being-represented
          (line-index-of-text-spot editable-text-spot-p)
          (character-index-of-text-spot editable-text-spot-p)))
      (text-box
        (enter-editing-context-on-text-box
          block-being-represented
          image-plane
          nil nil
          (line-index-of-text-spot editable-text-spot-p)
          (character-index-of-text-spot editable-text-spot-p))))))

;; Note A:
;;  (a) Does the tightness constant varies ought to vary from spot to spot?
;;  (b) does fail to get expressions-to-display of a readout table right?
;;  (c) editable-text-spot-p tests configuration, visiblity, editable slot
;;      feature, etc.

;; Note B: Referencing a spot is evil.



;;;; This is Another Section



(define-ui-command go-to-subworkspace (entity)
  (when (let ((subworkspaces? (subworkspaces entity)))
          (and subworkspaces?
               (workspaces-can-be-shown-at-this-kb-level-p
                 (car subworkspaces?) current-workstation)))
    (go-to-maybe-newly-created-subworkspace entity nil)))


(define-ui-command create-instance
    (frame workspace original-x-in-window original-y-in-window image-plane)
  (when (and (frame-of-class-p frame 'class-definition)
             (let* ((class-name? (name-of-defined-class frame))
                    (class-description? (class-description class-name?))
                    (class-features?
                      (and class-description?
                           (class-features class-description?))))
               (and class-description?
                    (not (feature-assq-macro
                           'not-user-instantiable class-features?))
                    (not (feature-assq-macro
                           'do-not-put-in-menus class-features?))
                    (not (direct-superiors-preclude-instantiability-p
                             (direct-superiors-of-defined-class frame)))
                    (not (subclassp class-name? 'loose-end)) ; lgibson 10/5/97
                    (not (subclassp class-name? 'connection))
                    (not (subclassp class-name? 'procedure-invocation))
                    (not (subclassp class-name? 'simulation-subtable))
                    #+pre-g2-v5-licensing (not (runtime-option-authorized-p))
                    #+pre-g2-v5-licensing (not (embedded-option-authorized-p)))))
    (let ((class (name-of-defined-class frame)))
      (cond ((subclassp class 'kb-workspace)
             (put-workspace-on-pane
               (if (eq class 'kb-workspace)
                   (make-new-top-level-kb-workspace 'kb-workspace)
                   (make-new-top-level-kb-workspace
                     class nil nil nil
                     (class-slot-description-value 'kb-workspace-initial-width class)
                     (class-slot-description-value 'kb-workspace-initial-height class)
                     (slot-init-form (slot-description-from-class
                                       class 'module-this-is-part-of?))))
               current-workstation-detail-pane 'center 'center nil))
            ((or (subclassp class 'free-text)
                 (subclassp class 'borderless-free-text)
                 (subclassp class 'text-inserter)
                 (subclassp class 'statement)
                 (subclassp class 'external-simulation-definition))
             (when (object-creation-on-workspace-allowed-p workspace)
               (make-instance-interactively
                 class image-plane (+f original-x-in-window 30) original-y-in-window)))
            ((or (subclassp class 'readout-table)
                 (subclassp class 'dial)
                 (subclassp class 'meter)
                 (subclassp class 'trend-chart)
                 (subclassp class 'graph)
                 (subclassp class 'chart)
                 (subclassp class 'freeform-table))
             (when (restricted-object-creation-on-workspace-allowed-p workspace)
               (make-instance-interactively
                 class image-plane (+f original-x-in-window 30) original-y-in-window)))
            (t
             (handle-block-motion-command
               frame 'create-instance
               original-x-in-window original-y-in-window
               image-plane nil))))))


(define-ui-command table-of-values
    (tabular-function original-x-in-window original-y-in-window)
  (put-up-table-of-values
    tabular-function original-x-in-window original-y-in-window))


;; get move or transfer, one or the other, for anything but a command frame

(defun-simple block-transferable-via-ui-command-p (block)
  (and (block-transferable-p block)
       (not (proprietary-p block))
       (not (frame-of-class-p block 'command))      ;(MHD 6/18/90)
       (not (frame-of-class-p block 'loose-end))    ;lgibson 10/5/97
       (not (frame-of-class-p block 'connection))   ;lgibson 9/26/97
       (not (frame-of-class-p block 'name-box))     ;jh, 7/1/97.
       (not (frame-of-class-p block 'system-frame)) ;jh, 11/4/97.
       (not (frame-acts-like-arrow-button-p block))    ;fmw, 4/8/05
       (item-is-either-not-permanent-or-from-an-editable-module-p block)))

(define-ui-command transfer (block original-x-in-window original-y-in-window image-plane)
  (when (block-transferable-via-ui-command-p block)
    (handle-block-motion-command
      block 'transfer original-x-in-window original-y-in-window image-plane nil)))

(define-ui-command move (block original-x-in-window original-y-in-window image-plane)
  (when (and (not (workspace-p block))                            ; Prefer move-workspace for this.
             ;; The not-transferable condition was here only to prevent both
             ;; Move and Transfer from appearing in a popup menu simultaneously
             ;; It wasn't meant to imply that the block was not moveable,
             ;; because if it is tranferable, it is moveable. So if we are in a
             ;; start-via-an-event context (start-generic), as opposed to
             ;; deciding-whether-to-put-in-menu context, enable the
             ;; command. Same stuff in move-attribute-display.
             ;; This somewhat kludgey code restores 3.0 (!)  behavior and fixes
             ;; HQ-839554. -fmw, 2/24/04
             (or (if (inconsistent-behavior-of-move-in-configurations-p)
                     nil
                     (ui-command-start-generic-context-p))
                 (not (block-transferable-p block))
                 (proprietary-p block))
             (not (block-of-edit-workspace-p block))
             (item-is-either-not-permanent-or-from-an-editable-module-p block))
    (handle-block-motion-command
      block 'move original-x-in-window original-y-in-window image-plane nil)))

(defun-simple block-clonable-via-ui-command-p (block)
  (and (not (frame-of-class-p block 'external-simulation-definition))
       (not (frame-of-class-p block 'command))
       (not (frame-of-class-p block 'loose-end)) ; lgibson 10/5/97
       (not (frame-of-class-p block 'connection)) ; lgibson 9/26/97
       (not (frame-of-class-p block 'procedure-invocation))
       (not (workspace-p block))   ;Prefer clone-workspace for this.
       (not (proprietary-p block)) ;Until problems are fixed - agh, 7/15/90
       #+pre-g2-v5-licensing (not (runtime-option-authorized-p))
       #+pre-g2-v5-licensing (not (embedded-option-authorized-p))
       (not (block-of-edit-workspace-p block))
       (not (frame-of-class-p block 'name-box)) ;jh, 7/1/97.
       (not (frame-of-class-p block 'table-item)) ; HQ-4404993 -fmw, 10/30/02
       (not (frame-acts-like-arrow-button-p block)))); HQ-5003929 -fmw, 4/8/05

(define-ui-command clone (block original-x-in-window original-y-in-window image-plane)
  (when (block-clonable-via-ui-command-p block)
    (handle-block-motion-command
      block 'clone original-x-in-window original-y-in-window image-plane nil)))


(define-ui-command clone-as-trend-chart
    (block original-x-in-window original-y-in-window image-plane)
  (when (frame-of-class-p block 'graph)
    (handle-block-motion-command
      block 'clone-as-trend-chart
      original-x-in-window original-y-in-window image-plane nil)))


(define-ui-command rotate-reflect
    ((rotation rotation)
     (entity entity))
  (when (frame-may-be-rotated-or-reflected-p entity t)
    (rotate-and-reflect-icon
     entity
     (case rotation
       (90-clockwise 90)
       (90-counterclockwise 270)
       (|180| 180)
       (left-right-reflection 0)
       (up-down-reflection 180))
     (case rotation
       (90-clockwise nil)
       (90-counterclockwise nil)
       (|180| nil)
       (left-right-reflection t)
       (up-down-reflection t))
     nil nil                      ; for rotation/reflection about center
     nil)
    (invoke-rules-for-movement-chaining entity 'is-moved-by-the-user)))


(defun change-size-permitted-p (block)
  (and (entity-like-p block)
       (icon-description block)            ; GENSYMCID-865
       (not (loose-end-p block))           ; HQ-4262899
       (block-is-upon-kb-workspace? block) ; HQ-4262899
       (item-is-either-not-permanent-or-from-an-editable-module-p block)))

(define-ui-command change-size
    (block image-plane original-x-in-window original-y-in-window window)
  "Change the size of this item"
  (when (and (change-size-permitted-p block)
             (not (show-selection-handles-p window)))
    (enter-sizing-dialog
      (if (frame-of-class-p block 'type-in-box)
          (get-type-in-text-box block)
          block)
      image-plane                                        ; Was image-plane-showing-block
      original-x-in-window original-y-in-window)))

(define-ui-command restore-to-normal-size (block window)
  "Restore this item to its normal size"
  (when (and (change-size-permitted-p block)
             (show-selection-handles-p window) ; Maybe remove this condition?
             (not (item-at-normal-size-p block)))
    (restore-item-to-normal-size block)
    (invoke-rules-for-resizement-chaining block 'is-resized-by-the-user)))

(defun item-at-normal-size-p (block)
  (frame-class-case block
    (entity
      (and (null (getf (icon-attributes-plist block) 'x-magnification))
           (null (getf (icon-attributes-plist block) 'y-magnification))))
    (graph
      (and (=f (width-of-block block) (minimum-graph-width (graph-format block)))
           (=f (height-of-block block) (minimum-graph-height (graph-format block)))))
    (trend-chart
      (and (=f (width-of-block block) default-trend-chart-width)
           (=f (height-of-block block) default-trend-chart-height)))
    (chart
      (and (=f (width-of-block block) default-chart-width)
           (=f (height-of-block block) default-chart-height)))
    (text-box
      (and (=f (minimum-width-of-text-box block) 0)
           (=f (minimum-height-of-text-box block) 0)))
    (t t)))


;; Needs x,y just for the confirmation dialog.

(defun item-may-be-deleted-by-user (block)
  (not (or (frame-of-class-p block 'inspect-command)        ; (MHD 1/9/91)
           (frame-acts-like-arrow-button-p block)       ;  HQ-5003929 -fmw, 4/8/05
           (block-of-edit-workspace-p block)
           (frame-of-class-p block 'system-table)
           (computation-frame-at-breakpoint-depends-on-block-p block)
           (not (item-is-either-not-permanent-or-from-an-editable-module-p block)))))

(define-ui-command delete (block)
  ;; This command covers delete, hide-table, hide, hide-name and delete-message
  ;; from facilties.
  (when (item-may-be-deleted-by-user block)
    (let ((x (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
          (y (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))
      (delete-block-for-user block x y))))



;; This should really test on the subworkspace, not the entity, but that
;;   isn't created yet! at least this way it will pick up higher
;;   classes (i.e. item). (MHD 11/6/88)
(defun item-may-be-given-subworkspace-by-user (entity)
  (and (transient-or-permanent-p entity)                    ; Not for short-reps
       (null (subworkspaces entity))
       (not (proprietary-p entity))
       #+pre-g2-v5-licensing (not (runtime-option-authorized-p))
       #+pre-g2-v5-licensing (not (embedded-option-authorized-p))
       (workspaces-can-be-shown-at-this-kb-level-p entity current-workstation)
       (item-is-either-not-permanent-or-from-an-editable-module-p entity)))

(define-ui-command create-subworkspace ((class class-of-workspace) (entity frame-for-selection))
  (when (and (entity-p entity)
             (not (connection-frame-p entity)) ; See make-subworkspace-action-internal
             (item-may-be-given-subworkspace-by-user entity))
    (go-to-maybe-newly-created-subworkspace entity class)))

;; Just using a magic arg of entity here gets us the item-represented for
;; tables, which is not what we want.


(defun change-min-size-permitted-p (item)
  (and (transient-or-permanent-p item)
       (or (frame-of-class-p item 'text-box)
           (frame-of-class-p item 'type-in-box))
       (item-is-either-not-permanent-or-from-an-editable-module-p item)))

;; fix this to work(!): change-size
;; are action buttons desirec?

(define-ui-command change-min-size
    (item image-plane original-x-in-window original-y-in-window window)
  (when (and (change-min-size-permitted-p item)
             (not (show-selection-handles-p window)))
    (enter-min-sizing-dialog
      (if (frame-of-class-p item 'type-in-box)
          (get-type-in-text-box item)
          item)
      image-plane original-x-in-window original-y-in-window)))



(define-ui-command go-to-message-origin (text-box)
  (when (get-origin-of-message-if-appropriate text-box)
    (goto-frame-instance (get-origin-of-message-if-appropriate text-box))))

;; Too bad we have to repeat the call to get-origin-of-message-if-appropriate.



(defun allow-go-to-referenced-item-p (item)
  (or (allow-go-to-frame-instance-p item)
      (of-class-p item 'system-table)))


;;; The presentation-type `referenced-item-of-message' returns a list of names
;;; and items for those items references by the message which are non-deleted,
;;; non-properietary, and which have workspaces.

(define-presentation-type referenced-item-of-message (message)
  :menu-options (:title referenced-items :strip-hyphens nil)
  :choices (let ((snapshots (snapshots-of-valid-blocks-related-to-message message)))
             ;; Menus will reclaim this as a slot-value.
             (loop for snapshot in snapshots
                   as block = (block-of-snapshot snapshot)
                   when (allow-go-to-referenced-item-p block)
                     collect (let* ((name (get-or-make-up-designation-for-block block))
                                    (copy-of-name (if (text-string-p name)
                                                      (copy-text-string name)
                                                      name)))
                               (slot-value-list 'choice
                                                copy-of-name
                                                snapshot))
                       using slot-value-cons))

  ;; We must store snapshots in the choice list, and then transform them into
  ;; blocks after one has been chosen, provided the block still exists.  The
  ;; tester ensures that the UI command will not run if block is deleted (and
  ;; our choice function returns nil).
  :tester ((x) x)
  :choice-transformer ((choice)
                       (when (and (snapshot-of-block-p choice)
                                  (snapshot-of-block-valid-p choice))
                         (block-of-snapshot choice)))

  ;; The immediate-value is not passed thru the choice transformer, so must be
  ;; a block.  The partial-command mechanism snapshots it for us.
  :immediate-value ((message)
                    (let* ((list (snapshots-of-valid-blocks-related-to-message message))
                           (first (loop for snapshot in list
                                        as block = (block-of-snapshot snapshot)
                                        if (allow-go-to-referenced-item-p block)
                                          return block)))
                      (when (=f 1 (loop for snapshot in list
                                        count (allow-go-to-referenced-item-p
                                                (block-of-snapshot snapshot))))
                        first)))

  :available-p ((message)
                (let ((list (snapshots-of-valid-blocks-related-to-message message)))
                  (loop for snapshot in list
                        thereis (allow-go-to-referenced-item-p (block-of-snapshot snapshot))))))



(define-ui-command go-to-referenced-item (message (item (referenced-item-of-message message)))
  ;; Hacked to show system tables also.  Drawing-parameters can now generate
  ;; logbook messages at kb-load time.
  (cond ((of-class-p item 'system-table)
         (let ((x-in-window
                 (halfr (-r (right-edge-of-window current-workstation-window)
                            (left-edge-of-window current-workstation-window))))
               (y-in-window
                 (halfr (-r (bottom-edge-of-window current-workstation-window)
                            (top-edge-of-window current-workstation-window)))))
           (put-up-attributes-table item x-in-window y-in-window)))
        (t
         (goto-frame-instance item))))

;; Ought to have a meta-type which given a list of choices, defines the
;; availabilty and immediate-value functions for you, as above.

(defun-simple referenced-source-code-choice-ok-p (snapshot)
  ;; Note that the invocation could be stale (i.e. the procedure may have been
  ;; recompiled, but we'll catch that in the UI command so we can inform the user).
  (and (invocation-info-of-snapshot snapshot)
       (allow-go-to-referenced-item-p (block-of-snapshot snapshot))))

(defun-simple make-choice-for-referenced-invocation-info-of-message (snapshot)
  (let ((name (get-or-make-up-designation-for-block (block-of-snapshot snapshot)))
        (line? (referenced-source-code-position-of-snapshot snapshot)))
    (slot-value-list 'choice
                     (if line?
                         (tformat-text-string "~A  (line ~D)" name line?)
                         (tformat-text-string "~A" name))
                     snapshot)))

(defun key-for-sorted-caller-snapshot-choices (choice)
  (snapshot-invocation-info-code-body-index
    (invocation-info-of-snapshot
      (third choice))))

(defun-simple choices-for-referenced-invocation-info-of-message (snapshots)
  (let ((error-snapshot (loop for snapshot in snapshots
                              when (and (referenced-source-code-choice-ok-p snapshot)
                                        (=f 0 (snapshot-invocation-info-code-body-index
                                                (invocation-info-of-snapshot snapshot))))
                                return snapshot))
        (caller-snapshots (sort-list
                            (loop for snapshot in snapshots
                                  when (and (referenced-source-code-choice-ok-p snapshot)
                                            (<f 0 (snapshot-invocation-info-code-body-index
                                                    (invocation-info-of-snapshot snapshot))))
                                    collect (make-choice-for-referenced-invocation-info-of-message snapshot)
                                      using slot-value-cons)
                            #'<
                            #'key-for-sorted-caller-snapshot-choices)))
    (nconc (when error-snapshot
             (slot-value-list (make-choice-for-referenced-invocation-info-of-message error-snapshot)))
           (when caller-snapshots
             (slot-value-cons
               '-
               (slot-value-cons
                 (slot-value-list 'choice
                                  (if error-snapshot
                                      (tformat-text-string "   Callers of ~A   "
                                                           (get-or-make-up-designation-for-block
                                                             (block-of-snapshot error-snapshot)))
                                      (tformat-text-string "   Callers   ")))
                 caller-snapshots))))))

(define-presentation-type referenced-invocation-info-of-message (message)
  :menu-options (:title referenced-source-code)
  :choices (let ((snapshots (snapshots-of-valid-blocks-related-to-message message)))
             (choices-for-referenced-invocation-info-of-message snapshots))
  ;; We must store snapshots in the choice list, and return it  provided the
  ;; block still exists.  The tester ensures that the UI command will not run if block is deleted (and
  ;; our choice function returns nil).
  :tester ((x) x)
  :choice-transformer ((choice)
                       (when (and (snapshot-of-block-p choice)
                                  (snapshot-of-block-valid-p choice))
                         (invocation-info-of-snapshot choice)))
  ;; The immediate-value is not passed thru the choice transformer, so must be
  ;; a block.  The partial-command mechanism snapshots it for us.
  :immediate-value ((message)
                    (loop for snapshot in (snapshots-of-valid-blocks-related-to-message
                                            message)
                          with first-invocation-info = nil
                          if (referenced-source-code-choice-ok-p snapshot)
                            do
                              (if first-invocation-info
                                  (return nil)
                                  (setq first-invocation-info
                                        (invocation-info-of-snapshot snapshot)))
                          finally
                            (return first-invocation-info)))
  :available-p ((message)
                (let ((list (snapshots-of-valid-blocks-related-to-message message)))
                  (loop for snapshot in list
                        thereis (and (referenced-source-code-choice-ok-p snapshot)
                                     (invocation-info-of-snapshot snapshot))))))

(defun referenced-source-code-position-of-snapshot (snapshot)
  (let ((invocation-info? (invocation-info-of-snapshot snapshot)))
    (when (and invocation-info?
               (allow-go-to-referenced-item-p (block-of-snapshot snapshot)))
      (let ((procedure (snapshot-invocation-info-procedure invocation-info?)))
        (and (edit-procedure-ok-for-ui-command-p procedure)
             (not (snapshot-invocation-info-stale-p invocation-info?))
             (get-annotation-for-address-if-any
               (snapshot-invocation-info-program-counter invocation-info?)
               (snapshot-invocation-info-code-body invocation-info?)))))))

;; For going from a stack-error message to a piece of source code. -dkuznick, 1/28/99
(define-ui-command go-to-source-code
    (message
      (invocation-info (referenced-invocation-info-of-message message)))
  (let ((procedure (snapshot-invocation-info-procedure invocation-info)))
    (cond ((not (edit-procedure-ok-for-ui-command-p procedure))
           (notify-user "Can't edit the procedure."))
          ((snapshot-invocation-info-stale-p invocation-info)
           (notify-user "This message is no longer valid because the procedure has been recompiled."))
          (t
           (multiple-value-bind (line-number character-number)
               (get-annotation-for-address-if-any
                 (snapshot-invocation-info-program-counter invocation-info)
                 (snapshot-invocation-info-code-body invocation-info))
             (cond ((null line-number)
                    (notify-user "Couldn't find source code mapping information."))
                   (t
                    (enter-editing-context procedure 'procedure-definition
                                           nil nil nil nil
                                           line-number character-number))))))))


;;;; Enumerated Values


;;; This section implements a new UI command, `change-to', for quickly changing
;;; the value of attributes with an "enumerated type".  For now, enumerated
;;; types include only:

;;;  (1) Symbol, with the "possible values" modifier
;;;  (2) Truth-value

;;; We could also include the yes/no system type, subsuming the change-to-yes
;;; and change-to-no commands, but we need those commands explicitly for item
;;; restrictions to continue to work.

;;; Note that the enumerations are not strict: the attribute still can hold
;;; other values. For this reason, the Edit command choice remains available.


;;; The function `slot-description-possible-values' returns a list of symbols
;;; representing possible values for the given slot, or NIL if there is no
;;; finite list. The list is a CONSTANT, and should not be reclaimed.

(defun slot-description-possible-values (slot-description)
  (cond ((value-set-given-attribute-and-class
           (pretty-slot-name slot-description)
           (defining-class slot-description)))
;        ((get-type-feature-if-boolean (slot-features slot-description))
;         '(yes no))
        ((and (user-defined-slot-description-p slot-description)
              (eq (slot-type-specification slot-description) 'truth-value))
         '(true false))))

(defun slot-description-current-value-as-symbol (frame slot-description)
  (let ((slot-value (get-slot-description-value frame slot-description)))
    (case (slot-type-specification slot-description)
      (symbol
       slot-value)
      (truth-value
       (when (and (user-defined-slot-description-p slot-description) ; Needed?
                  (slot-constantp slot-value))                       ; Always true?
         (let ((number (get-slot-value-number-or-string-from-slot-constant slot-value)))
           (cond ((eql number truth)
                  'true)
                 ((eql number falsity)
                  'false)))))
      (t
;       (if (get-type-feature-if-boolean (slot-features slot-description))
;           (if slot-value 'yes 'no))
       nil))))

(defun possible-new-values-of-slot (frame slot-name defining-class)
  (let ((slot-description?
          (slot-description-from-class (class frame) slot-name defining-class)))
    (when slot-description?
      (let ((possible-values
              (slot-description-possible-values slot-description?))
            (current-value
              (slot-description-current-value-as-symbol frame slot-description?)))
        (loop for value in possible-values
              unless (eql value current-value)
                collect value using slot-value-cons)))))

(define-presentation-type possible-new-value-of-slot (frame slot-name defining-class)
  :menu-options (:title new-value)
  :choices (possible-new-values-of-slot frame slot-name defining-class)
  :immediate-value ((frame slot-name defining-class)
                    (let ((choices (possible-new-values-of-slot frame slot-name defining-class)))
                      (prog1 (and (singleton? choices)
                                  (first choices))
                        (reclaim-slot-value-list choices)))))

;;; The ui-command `change-to' changes the value of an enumerated attribute via
;;; a menu of the other possible values, or if there is only one, immediately.

(define-ui-command (change-to :labeler ("~a \"~(~a~)\"" pretty-name new-value))
    ((text-cell text-cell-of-table)
     (frame frame-represented-by-table)
     (slot-name slot-name)
     (defining-class defining-class)
     (new-value (possible-new-value-of-slot frame slot-name defining-class)))
  (when (and (item-is-either-not-permanent-or-from-an-editable-module-p frame)
             (possible-new-values-of-slot frame slot-name defining-class))
    (change-value-of-attribute-in-text-cell-via-parser text-cell new-value)))


;;; The ui-command `change-to-yes' appears for some boolean-valued attributes.

(define-ui-command (change-to-yes :pretty-name "change to \"yes\"")
    ((text-cell text-cell-of-table)
     (frame frame-represented-by-table))
  (when (and (include-yes-no-menu-choice-p text-cell)
             (multiple-value-bind (boolean-p logical-value)
                 (text-cell-represents-boolean-attribute-p text-cell)
               (and boolean-p (not logical-value)))
             (item-is-either-not-permanent-or-from-an-editable-module-p frame))
    (change-value-of-attribute-in-text-cell-via-parser text-cell 'yes)))

(define-ui-command (change-to-no :pretty-name "change to \"no\"")
    ((text-cell text-cell-of-table)
     (frame frame-represented-by-table))
  (when (and (include-yes-no-menu-choice-p text-cell)
             (multiple-value-bind (boolean-p logical-value)
                 (text-cell-represents-boolean-attribute-p text-cell)
               (and boolean-p logical-value))
             (item-is-either-not-permanent-or-from-an-editable-module-p frame))
    (change-value-of-attribute-in-text-cell-via-parser text-cell 'no)))



(defun enable-choose-existing-class (table frame slot-name defining-class?)
  (let ((type-of-slot? (get-type-of-slot frame slot-name defining-class?)))
    (and type-of-slot?
         (null (get-subframe frame slot-name defining-class?))
         (not (memq (cadr type-of-slot?) grammar-categories-getting-yes-no-feature))
         (memq (cadr type-of-slot?)
               grammar-categories-getting-choose-existing-class-feature)
         (not (frame-of-class-p table 'explanation-table))   ; cannot edit cells
                                                            ;   of explanation tables
         (transient-or-permanent-p frame))))



(defun put-barrier-on-destabilization-via-menu-selection
    (frame slot-description class x-in-window y-in-window)
  (enter-dialog
    (tformat-text-string
      "Really change the superior class(es)?  (This class definition is in ~
             a part of the KB ~
             declared as stable. This edit could cause dependent ~
             parts of the KB to become incomplete, and to ~
             require recompilation.)")
    nil nil
    'allow-continuation-of-class-selection-upon-confirmation
    (slot-value-list
      frame slot-description class (copy-frame-serial-number (current-frame-serial-number)))
    'exit-menu-selection-upon-denial-of-confirmation nil
    x-in-window y-in-window))

(defun allow-continuation-of-class-selection-upon-confirmation
    (frame slot-description class serial-number)
  (unless (frame-has-been-reprocessed-p frame serial-number)
    (recording-items-made-incomplete
      ('choose-existing-class)
      (change-slot-description-value frame slot-description class)
      (offer-to-recompile-items-made-incomplete-if-appropriate))))


(defun exit-menu-selection-upon-denial-of-confirmation ()
  nil)

(define-ui-command choose-existing-class ((table attribute-table)
                                          (frame frame-represented-by-table)
                                          (slot-name slot-name)
                                          (defining-class defining-class)
                                               ; not required
                                          (class (superior-class frame))
                                               ; FRAME must be a definition.
                                          image-plane
                                          original-x-in-window
                                          original-y-in-window)
  (when (enable-choose-existing-class table frame slot-name defining-class)
    (let ((slot-description
            (slot-description-from-class (class frame) slot-name)))
      (cond
        ((restrict-destabilization-p frame slot-description)
         (put-barrier-on-destabilization-via-menu-selection
           frame slot-description
           class (-w original-x-in-window 10) (-w original-y-in-window 10)))
        (t
         (change-slot-value frame slot-name class defining-class))))))


(defun allow-subtable-command-p (frame slot-name defining-class)
  (or (get-type-of-slot frame slot-name defining-class)
      (get-slot-feature-if-any
        (class frame) slot-name 'class-of-optional-subframe
        defining-class)))

(define-ui-command subtable
    ((table attribute-table)
     (slot-name slot-name)
     (defining-class defining-class) ; not required
     (frame frame-represented-by-table)
     (subframe subframe)
     original-x-in-window original-y-in-window)
  "Display the table of the item which is the value of this attribute"
  (when (and (allow-subtable-command-p frame slot-name defining-class)
             (eq frame (parent-frame subframe)))
    ;; If frame is not the parent-frame of subframe then the subtable
    ;; is no longer viable.  E.g. when the transfer off of an attribute
    ;; occurs yet the previous subtable is available to be selected.
    ;; See Bug HQ-3614622 for an example. - jpg for mhd 8/30/00
    (put-up-attributes-table (get-slot-value frame slot-name defining-class)
                             original-x-in-window original-y-in-window)))

(define-ui-command subtable-of-hidden-attributes
    ((table attribute-table)
     (slot-name slot-name)
     (defining-class defining-class) ; not required
     (frame frame-represented-by-table)
     (subframe subframe)
     original-x-in-window original-y-in-window)
  "Display the table of the item which is the value of this attribute"
  (when (allow-subtable-command-p frame slot-name defining-class)
    (put-up-virtual-attributes-table (get-slot-value frame slot-name defining-class)
                                     original-x-in-window original-y-in-window)))

(define-ui-command (show-subtable-of-unsaved-attributes :name show-unsaved-attributes)
    ((table attribute-table)
     (slot-name slot-name)
     (defining-class defining-class) ; not required
     (frame frame-represented-by-table)
     (subframe subframe)
     original-x-in-window original-y-in-window)
  "Shows the attributes that have changed since the last save of this attribute."
  (when (and (allow-subtable-command-p frame slot-name defining-class)
             (item-has-unsaved-changes-visible-in-tables-p
               (get-slot-value frame slot-name defining-class)))
    (let ((block (get-slot-value frame slot-name defining-class)))
      (put-up-attributes-table block original-x-in-window original-y-in-window
                               nil nil nil
                               (if (item-was-created-by-load-p block)
                                   (attributes-permamently-changed block)
                                   t)))))


;;; The macro, `value-is-constrained-by-declared-type-p', returns a non-null
;;; value when the slot value is a subobject, the attribute is constrained to be
;;; an instance of a class, and the slot-value class is the only interactively
;;; instantiable applicable class.  When that is the case, there will be no
;;; delete-subtable menu choice on the attribute subtable.

(defmacro value-is-constrained-by-declared-type-p
    (frame slot-name defining-class subframe)
  `(let* ((slot-description
           (slot-description-from-class
             (class ,frame) ,slot-name ,defining-class))
          (slot-type-specification
            (slot-type-specification slot-description))
          (class-of-type-specification?
            (and (class-type-specification-p slot-type-specification)
                 (second slot-type-specification)))
          (class-of-subframe (class ,subframe)))
     (and class-of-type-specification?
          (loop for subclass being each subclass of class-of-type-specification?
                for class-features = (class-features
                                       (class-description subclass))
                do
            (unless (or (eq subclass class-of-subframe)
                        (feature-assq-macro 'not-user-instantiable class-features)
                        (feature-assq-macro 'do-not-put-in-menus class-features))
              (return nil))
                finally (return t)))))




(define-ui-command delete-subtable ((table attribute-table)
                                    (slot-name slot-name)
                                    (defining-class defining-class)
                                    (frame frame-represented-by-table)
                                    (subframe subframe))
  (unless (value-is-constrained-by-declared-type-p
            frame slot-name defining-class subframe)
    (when (if (get-type-of-slot frame slot-name defining-class)
                 (and (frame-system-operation-is-allowed-p
                        'change-set-of-inferiors frame)
                      (frame-system-operation-is-allowed-p
                        'change-superior subframe))
                 (get-slot-feature-if-any
                   (class frame) slot-name 'class-of-optional-subframe
                   defining-class))
          (let ((x (x-of-mouse-pointer
                     (mouse-pointer-of-latest-event current-workstation)))
                (y (y-of-mouse-pointer
                     (mouse-pointer-of-latest-event current-workstation))))
            (delete-block-for-user subframe x y)))))



(define-ui-command add-optional-subtable
    ((table attribute-table)
     (slot-name slot-name)
     (defining-class defining-class) ; not required
     (frame frame-represented-by-table)
     (class (subframe-class frame slot-name defining-class))
     image-plane original-x-in-window original-y-in-window)
  (when (allow-subtable-p table frame slot-name defining-class)
    (do-addition-of-optional-subtable-from-menu
        class image-plane original-x-in-window original-y-in-window
        frame slot-name defining-class)))



(define-ui-command show-attribute-display
    ((table attribute-table)
     (slot-name slot-name)
     (defining-class defining-class) ; not required
     (frame frame-represented-by-table))
  ;; only make this available on real attribute
  ;; tables, i.e., not on short representations
  (when (and (attribute-table-p table)
             ;; doesn't work with tables at all
             (not (table-p frame))
             ;; doesn't work with opaque blocks
             (not (opaque-block-p frame))
             ;; not a "subtable"
             (null (get-kb-parent-information frame))
             ;; on a workspace? (if didn't check
             ;;   for this, you would get this choice
             (get-workspace-if-any frame)
             ;;for system tables
             (transient-or-permanent-p frame)
             (item-is-either-not-permanent-or-from-an-editable-module-p frame))
    (add-slot-representation-as-attribute-display frame slot-name defining-class)))


(define-ui-command (edit-attribute-value :name edit)
    ((table attribute-table)
     (name-or-value-text-cell                ; i.e., cell in either the rh or lh
       text-cell-of-table)                ;    column of an attribute table
                                        ; later, should be a presentation type!
     image-plane
     block-being-represented
     slot-name
     original-x-in-window original-y-in-window)
  (when (and (or (and (attribute-table-p table)
                      (editable-text-cell-p
                        table
                        (get-attribute-value-text-cell
                          table name-or-value-text-cell)))
                 (and (frame-of-class-p table 'graph)
                      (item-is-either-not-permanent-or-from-an-editable-module-p
                       block-being-represented)))
             (not (licensing-restricts-edit
                    block-being-represented slot-name)))
    (let* ((attribute-value-text-cell
             (get-attribute-value-text-cell
               table name-or-value-text-cell)))
      (enter-text-editor-on-text-cell
        table attribute-value-text-cell
        image-plane original-x-in-window original-y-in-window))))


(define-ui-command hide-table (table workspace)
  (when (and (not (short-representation-p table))
             (not (attribute-display-p table))
             (not (frame-of-class-p workspace 'edit-workspace))) ; See Note

    ;; We can't put x,y-in-window into our lambda list because those get bound
    ;; at the time the menu is put up!  Need a more magical argument type.

    (let ((x (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
          (y (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))
      (delete-block-for-user table x y))))

;; Note: This prevents a menu from popping up over the little table of the
;; directory and "(contents unknown)" which appears below the edit-box in the
;; load-kb dialog.  However, a similar output-only table in the inspector
;; window gets through, in 3.0, too.  Do we care?  -fmw, 3/17/95

;; Note that this command can glom onto a readout-table, eg, by virtue of the
;; fact that the magic arg is TABLE rather than ATTRIBUTE-TABLE.  But, we don't
;; put hide-table into the simple-item menu, so we are OK. -- UPDATE: this used
;; to actually cause a problem with the tabular displays in Inspect.  Clicking
;; on the row or column of a table representing a readout table would get
;; hide-table on the menu, and choosing hide-table would delete the
;; readout-table, not the tabular Inspect display, as it should.  Using the new
;; magic argument table-but-not-kb-item addresses this problem. -mhd, 1/17/01



(define-ui-command (hide-attribute-table :name hide-table)
    ((table attribute-table)&optional (frame? frame-represented-by-table))
  (when (and (not (short-representation-p table))
             (not (attribute-display-p table))
             (not (and frame? (frame-of-class-p frame? 'g2-login)))) ; Note.

    (let ((x (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
          (y (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))
      (delete-block-for-user table x y))))

;; Note: added while preventing the transfer/hide-table menu items from
;; appearing for the table used in login-panels. -fmw, 3/30/95

;;;;Gensym-178-HQ-5673853-SUCI-Add menu-choice on table of item go-to-item
(define-ui-command go-to-item
    ((table attribute-table) (frame frame-represented-by-table))
  (when (and (attribute-table-p table)
             (not (table-p frame))
             (get-workspace-if-any frame))
    (goto-frame-instance frame)))        



;;;; Attribute Display commands



;;; The ui-command `edit-attribute-display' is a slight variation on edit-attribute-value,
;;; used just for attribute displays.

(define-ui-command (edit-attribute-display :name edit)
    ((table attribute-display)
     (name-or-value-text-cell text-cell-of-table)
     block-being-represented slot-name
     image-plane original-x-in-window original-y-in-window)
  (when (and
          (editable-text-cell-p
            table (get-attribute-value-text-cell table name-or-value-text-cell))
          (not (licensing-restricts-edit block-being-represented slot-name)))
    (let ((attribute-value-text-cell
            (get-attribute-value-text-cell table name-or-value-text-cell)))
      (enter-text-editor-on-text-cell
        table attribute-value-text-cell
        image-plane original-x-in-window original-y-in-window))))



;; Same as the block commands, just a different argument.  Too bad.
;; If we defined the block commands on "thing", we could use them here.

(define-ui-command (move-attribute-display :name move)
    (attribute-display original-x-in-window original-y-in-window image-plane)
  (when (or (if (inconsistent-behavior-of-move-in-configurations-p)
                nil
                (ui-command-start-generic-context-p))     ; See MOVE cmd for info.
            (not (block-transferable-p attribute-display))
            (proprietary-p attribute-display))
    (handle-block-motion-command attribute-display 'move
                                 original-x-in-window original-y-in-window image-plane nil)))

(define-ui-command (transfer-attribute-display :name transfer)
    (attribute-display original-x-in-window original-y-in-window image-plane)
  (when (and (block-transferable-p attribute-display)
             (not (proprietary-p attribute-display)))
    (handle-block-motion-command attribute-display 'transfer
                                 original-x-in-window original-y-in-window image-plane nil)))


(define-ui-command add-another-attribute ((table attribute-display)
                                          (frame frame-represented-by-table)
                                          (slot-designation
                                            (attributes-missing-from-table table frame)))
  (when (and (attributes-can-be-added-to-attribute-display-p table frame)
             (item-is-either-not-permanent-or-from-an-editable-module-p table))
    ;; May have been deleted.  Someday the ptype will handle this test
    ;; correctly.
    (when (or (eq slot-designation 'class)
              (slot-exists-in-frame-p slot-designation frame))
      (add-another-attribute-to-attribute-display
        table frame
        (unqualified-name slot-designation)
        (class-qualifier slot-designation)))))



(define-ui-command delete-attribute ((table attribute-display)
                                     (frame frame-represented-by-table)
                                     (text-cell attribute-display-text-cell)
                                     (slot-name slot-name)
                                     (defining-class defining-class)) ; not required
  (when (and (attributes-can-be-deleted-from-attribute-display-p table frame)
             (item-is-either-not-permanent-or-from-an-editable-module-p table))
    (delete-attribute-from-attribute-display
      table frame slot-name defining-class text-cell)))


(define-ui-command add-name-of-attribute ((table attribute-display)
                                          (text-cell attribute-display-text-cell))
  (when (and (attribute-name-can-be-added-to-attribute-display-p table text-cell)
             (item-is-either-not-permanent-or-from-an-editable-module-p table))
    (add-attribute-name-to-attribute-display table text-cell)))


(define-ui-command delete-name-of-attribute ((table attribute-display)
                                             (text-cell attribute-display-text-cell))
  (when (and (attribute-name-shown-in-attribute-display-p table text-cell)
             (item-is-either-not-permanent-or-from-an-editable-module-p table))
    (delete-attribute-name-from-attribute-display table text-cell)))


(define-ui-command hide-attribute-display (attribute-display)
  (when (item-is-either-not-permanent-or-from-an-editable-module-p attribute-display)
    (delete-frame attribute-display)))



;;; The function `prohibit-transfer-of-table-p' returns T for various random
;;; tables whose transfer is not allowed (via menus, at least).

(defun prohibit-transfer-of-table-p (table frame-represented?)
  (or
    ;; We are holding off of allowing transfer of "query tables" because there
    ;; are some issues with them:
    (multiframe-table-p table)                    ; "query-table-p"?

    ;; For 3.0: disallow transfer option on newly created title blocks -- but
    ;; grandfather existing title blocks to have the option.  (They will become
    ;; rare and valuable this way, sort of collectible.) (MHD 7/23/91)
    (and (title-block-table-p table)
         (superblock? table)
         (title-block-workspace-p (superblock? table)))

    (search-results-table-p table)
    (file-progress-table-p table)

    (and frame-represented? (or (frame-of-class-p frame-represented? 'g2-login)
                                (frame-of-class-p frame-represented?
                                                  'server-parameters)))))




;;; The ui-command `transfer-table' has a more complex predicate than the
;;; simple TRANSFER command.  Also, it transfers the attribute-table under the
;;; mouse, NOT any possible table object which the attribute table represents
;;; (eg, readout-tables).

(define-ui-command (transfer-table :name transfer)
    ((table attribute-table)
     original-x-in-window original-y-in-window image-plane
     &optional (frame? frame-represented-by-table))

  (when (and (not (prohibit-transfer-of-table-p table frame?))
             (block-transferable-p table)
             (not (proprietary-p table)))

    (handle-block-motion-command table 'transfer
                                 original-x-in-window original-y-in-window image-plane nil)))



;;;; Commands on short representations



(define-ui-command (table-for-short-representation :name table)
    ((frame frame-represented-by-table)
     original-x-in-window original-y-in-window)
  "Put up the attributes table for an arbitrary G2 item."
  (put-up-attributes-table frame original-x-in-window original-y-in-window))

(define-ui-command (table-of-hidden-attributes-for-short-representation :name table-of-hidden-attributes)
    ((frame frame-represented-by-table)
     original-x-in-window original-y-in-window)
  "Put up the virtual attributes table for an arbitrary G2 item."
  (put-up-virtual-attributes-table frame original-x-in-window original-y-in-window))


(define-ui-command (show-unsaved-attributes-for-short-representation :name show-unsaved-attributes)
    ((frame frame-represented-by-table)
     original-x-in-window original-y-in-window)
  "Shows the attributes that have changed since the last save of an permanent G2 item."
  (when (item-has-unsaved-changes-visible-in-tables-p frame)
    (put-up-attributes-table frame original-x-in-window original-y-in-window
                             nil nil nil
                             (if (item-was-created-by-load-p frame)
                                 (attributes-permamently-changed frame)
                                 t))))



(define-ui-command (describe-table-item :name describe)
    ((frame frame-represented-by-table))
  "Describe this item"
  (when frame
    (describe-item-on-temporary-workspace frame)))

;; I'm not sure the condition is correct here. See FACILITIES.


(define-ui-command (transfer-short-representation :name transfer)
    ((table short-representation-table)
     image-plane original-x-in-window original-y-in-window
     &optional (frame? frame-represented-by-table))
  (when (and (block-transferable-p table)
             (not (proprietary-p table))
             ;; More server-parameters hackery
             (if frame?
                 (not (frame-of-class-p frame? 'server-parameters))
                 t))
    (handle-block-motion-command table 'transfer
                                 original-x-in-window original-y-in-window image-plane nil)))


(define-ui-command go-to-original ((table short-representation-table)
                                   (frame frame-represented-by-table))
  (when (and (or (short-representation-p table)
                 (multiframe-table-p table))
             (multiple-value-bind (block-on-workspace? workspace?)
                 (get-block-on-workspace-for-frame frame)
               (and block-on-workspace?
                    (or (frame-of-class-p workspace? 'non-kb-workspace)
                        (workspaces-can-be-shown-at-this-kb-level-p
                          workspace? current-workstation)))))

    (frame-class-case table
      (explanation-table                ; Only NUPEC gets these now. (MHD 2/6/94)
        (let ((frame? (get-explanation-table-original table))) ; why not "frame"?!
          (when frame?
            (goto-frame-instance frame?))))
      (t
        (goto-frame-instance frame)))))


;; Hmm.
(define-ui-command delete-original ((table short-representation-table)
                                    (frame frame-represented-by-table))
  (when (and (or (short-representation-p table)
                 (multiframe-table-p table))
             (problem-item-in-limbo-p frame))
    (let ((x (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
          (y (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))
      (delete-block-for-user frame x y))))


;; Hmm. This never appears in a menu??
(define-ui-command transfer-original ((table short-representation-table)
                                      (frame frame-represented-by-table)
                                      image-plane original-x-in-window original-y-in-window)
  (when (and (or (short-representation-p table)
                 (multiframe-table-p table))
             frame
             (not (connection-p frame))                            ; can't transfer connections yet
             (problem-item-in-limbo-p frame))
    (handle-block-motion-command table 'transfer-original
                                 original-x-in-window original-y-in-window image-plane frame)))



(define-ui-command (hide-short-representation-table :name hide)
    ((table short-representation-table))
  (when (or (short-representation-p table)
            (multiframe-table-p table))
    (let ((x (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
          (y (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))
      (delete-block-for-user table x y))))




;;;; Freeform Table commands



;; The mouse-over-cell-in-new-table-p predicate may not be needed: these
;; commands are only enabled in the freeform-table menu.  Also, the particular
;; cell of the table probably ought to be a magic argument..

(define-ui-command edit-cell-expression (new-table image-plane original-x-in-window original-y-in-window)
  (when (change-in-freeform-table-is-meaningful-p
          new-table 0 0 image-plane original-x-in-window original-y-in-window)
    (do-new-table-edit new-table 'edit-cell-expression
                       image-plane original-x-in-window original-y-in-window)))


(define-ui-command edit-cell-format (new-table image-plane original-x-in-window original-y-in-window)
  (when (change-in-freeform-table-is-meaningful-p
          new-table 0 0 image-plane original-x-in-window original-y-in-window)
    (do-new-table-edit new-table 'edit-cell-format
                       image-plane original-x-in-window original-y-in-window)))


(define-ui-command add-row (new-table image-plane original-x-in-window original-y-in-window)
  (when
      (change-in-freeform-table-is-meaningful-p
        new-table 1 0 image-plane original-x-in-window original-y-in-window)
;(change-in-freeform-table-dimensions-is-ok-p new-table 1 0)
    (do-new-table-edit new-table 'add-row image-plane original-x-in-window original-y-in-window)))


(define-ui-command add-column (new-table image-plane original-x-in-window original-y-in-window)
  (when
      (change-in-freeform-table-is-meaningful-p
        new-table 0 1 image-plane original-x-in-window original-y-in-window)
;      (change-in-freeform-table-dimensions-is-ok-p new-table 0 1)
    (do-new-table-edit new-table 'add-column image-plane original-x-in-window original-y-in-window)))


(define-ui-command delete-row (new-table image-plane original-x-in-window original-y-in-window)
  (when
      (change-in-freeform-table-is-meaningful-p
        new-table -1 0 image-plane original-x-in-window original-y-in-window)
;      (change-in-freeform-table-dimensions-is-ok-p new-table -1 0)
    (do-new-table-edit
        new-table 'delete-row image-plane original-x-in-window original-y-in-window)))


(define-ui-command delete-column (new-table image-plane original-x-in-window original-y-in-window)
  (when
      (change-in-freeform-table-is-meaningful-p
        new-table 0 -1 image-plane original-x-in-window original-y-in-window)
;      (change-in-freeform-table-dimensions-is-ok-p new-table 0 -1)
    (do-new-table-edit
        new-table 'delete-column image-plane original-x-in-window original-y-in-window)))



;;;; Connection Commands


(define-ui-command (delete-connection :name delete) (connection)
  (when (item-is-either-not-permanent-or-from-an-editable-module-p connection)
    (let ((connection-structure (connection-for-this-connection-frame connection)))
      (if (ok-to-delete-connection-p connection-structure)
          (delete-connection-to-stub connection-structure)
          (notify-user "Deleting this connection would cause directionality problems")))))

;; Consider using delete-connection here, instead of delete-connection-to-stub.
;; Consider, if user does nothing with the frame's table, getting rid of it.

;; (subworkspace                ; consider supporting this, here & in RUN
;; (go-to-maybe-newly-created-subworkspace connection))



(define-ui-command (color-connection :name color)
    ((block connection)
     (region (colorable-regions-of-frame block))
     (color ((color) :title region)))
  (when (and (transient-or-permanent-p block)
             (colorable-regions-of-frame block)
             (item-is-either-not-permanent-or-from-an-editable-module-p block))
    (change-color-of-item block nil region color)))





;;;; Commands for Slot Components Represented in Tables



(defun get-compound-slot-descriptor-from-cell-if-any (text-cell)
  (multiple-value-bind (frame? slot-name? defining-class? slot-component-name?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (declare (ignore frame? defining-class?))
    (and slot-name?
         (null slot-component-name?)
         (compound-slot-descriptor slot-name?))))

(defun represents-single-component-value-p (text-cell)
  (let ((descriptor? (get-compound-slot-descriptor-from-cell-if-any text-cell)))
    (and descriptor? (not (compound-slot-multiple-p descriptor?)))))

(defun represents-multiple-component-value-p (text-cell)
  (let ((descriptor? (get-compound-slot-descriptor-from-cell-if-any text-cell)))
    (and descriptor? (compound-slot-multiple-p descriptor?))))

;;; The ui-command `show-slot-component-subtable'

(define-ui-command (show-slot-component-subtable :name subtable)
    ((text-cell text-cell-of-table) x-in-window y-in-window)
  (when (represents-single-component-value-p text-cell)
    (multiple-value-bind (frame slot-name defining-class?)
        (get-slot-represented-by-text-cell-if-any text-cell)
      (declare (ignore defining-class?))
      (put-up-attributes-table
        frame x-in-window y-in-window nil slot-name))))


(define-presentation-type slot-component-groups (a-mouse-pointer)
  ;; Note: variable name MOUSE-POINTER not legal
  :available-p ((mp) (slot-component-groups-exist-p mp))
  :choices
    (map-mouse-pointer-to-menu-choices-for-slot-component-groups
      a-mouse-pointer t)
  :choice-transformer get-table-for-slot-component-group
  :menu-options (:title subtables)
  :tester ((x) (declare (ignore x)) t))

(define-presentation-type non-default-slot-component-groups (a-mouse-pointer)
  :available-p ((mp) (slot-component-groups-exist-p mp))
  :choices
    (map-mouse-pointer-to-menu-choices-for-slot-component-groups
      a-mouse-pointer nil)
  :choice-transformer get-table-for-slot-component-group
  :menu-options (:title subtables)
  :tester ((x) (declare (ignore x)) t))

(define-presentation-type non-default-referred-slot-component-groups (a-mouse-pointer)
  :available-p ((mp) (referred-slot-component-groups-exist-p mp))
  :choices
    (map-mouse-pointer-to-menu-choices-for-referred-slot-component-groups
      a-mouse-pointer nil)
  :choice-transformer get-table-for-slot-component-group
  :menu-options (:title referable-subtables)
  :tester ((x) (declare (ignore x)) t))

(defun slot-component-groups-exist-p (mouse-pointer)
  (with-mouse-pointer-bindings (&optional (text-cell text-cell-of-table)) ; optional?
      mouse-pointer
    (and text-cell                        ; can be nil?
         (represents-multiple-component-value-p text-cell)
         (multiple-value-bind (frame? slot-name? defining-class?)
             (get-slot-represented-by-text-cell-if-any text-cell)
           (and frame?
                (component-groups-for-compound-slot-value
                  (get-slot-value frame? slot-name? defining-class?)))))))

(defun referred-slot-component-groups-exist-p (mouse-pointer)
  (with-mouse-pointer-bindings (&optional (text-cell text-cell-of-table))
      mouse-pointer
    (and text-cell
         (represents-reference-slot-component-value-p text-cell)
         (multiple-value-bind (frame? slot-name? defining-class? slot-component-name?)
             (get-slot-represented-by-text-cell-if-any text-cell)
           (and frame? slot-name? slot-component-name?
                (let ((referred-slot-name
                        (get-referred-slot-name slot-name? slot-component-name?)))
                  (component-groups-for-compound-slot-value
                    (get-slot-value frame? referred-slot-name defining-class?))))))))

(defun map-mouse-pointer-to-menu-choices-for-slot-component-groups
    (mouse-pointer allow-default-p)
  (with-mouse-pointer-bindings ((frame frame-represented-by-table)
                                (slot-name slot-name))
      mouse-pointer
    (compute-menu-choices-for-slot-component-group-indicators
      frame slot-name allow-default-p)))

(defun map-mouse-pointer-to-menu-choices-for-referred-slot-component-groups
    (mouse-pointer allow-default-p)
  (with-mouse-pointer-bindings ((frame frame-represented-by-table)
                                (slot-name slot-name)
                                (slot-component-name slot-component-name?))
      mouse-pointer
    (let ((referred-slot-name
            (get-referred-slot-name slot-name slot-component-name)))
      (compute-menu-choices-for-slot-component-group-indicators
        frame referred-slot-name allow-default-p))))

(defun compute-menu-choices-for-slot-component-group-indicators (frame slot-name
                                                                  allow-default-p)
  (loop with slot-component-type-name
        = (compound-slot-compound-type
            (compound-slot-descriptor slot-name))
        with count = 0
        for slot-component-group
            in (component-groups-for-compound-slot-value
                 (get-slot-value frame slot-name))
        as slot-component-indicator
          = (slot-component-group-indicator slot-component-group)
        as name-or-names?
          = (slot-component-group-name-or-names
              slot-component-group slot-component-type-name)
        as slot-component-name?
          = (if name-or-names?
                (if (consp name-or-names?)
                    (car name-or-names?)
                    name-or-names?))
        as choice-string
          = (cond
              ((default-slot-component-group-p
                   slot-component-group)
               (when allow-default-p
                 (tformat-text-string "~a Defaults"
                                      slot-component-type-name)))
              (slot-component-name?
               (incff count)
               (tformat-text-string
                 "~a #~d ~a"
                 slot-component-type-name count slot-component-name?))
              (t
               (incff count)
               (tformat-text-string
                 "~a #~d"
                 slot-component-type-name count)))
        collect (slot-value-list 'choice choice-string slot-component-indicator)
          using slot-value-cons))


(defun get-first-slot-component-group-indicator-if-only-one (frame slot-name allow-defaults-p)
  (let* ((slot-value (get-slot-value frame slot-name))
         (groups
           (if allow-defaults-p
               (multiple-compound-slot-value-instances slot-value)
               (multiple-compound-slot-value-real-instances slot-value))))
;          (component-groups-for-compound-slot-value
;            (get-slot-value frame slot-name))))
    (if (and groups
             (null (cdr groups)))
        (slot-component-group-indicator (car groups)))))


(defun represents-slot-component-value-p (text-cell)
  (multiple-value-bind (frame? slot-name? defining-class? slot-component-name?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (declare (ignore frame? defining-class?))
    (and slot-name?
         slot-component-name?
         (compound-slot-descriptor slot-name?))))

(defun represents-reference-slot-component-value-p (text-cell)
  (multiple-value-bind (frame? slot-name? defining-class? slot-component-name?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (declare (ignore frame?))
    (and slot-name?
         slot-component-name?
         (compound-slot-descriptor slot-name?)
         (let ((slot-component-features
                 (get-slot-component-features
                   slot-name? defining-class? slot-component-name?)))
           (eq (cadr (feature-assq 'subtype slot-component-features))
               'reference)))))

(define-ui-command (show-referred-slot-component-subtable :name referenced-subtable)
    ((text-cell text-cell-of-table) x-in-window y-in-window)
  (when (represents-reference-slot-component-value-p text-cell)
    (multiple-value-bind (frame slot-name defining-class?
                                slot-component-name? slot-component-indicator?)
        (get-slot-represented-by-text-cell-if-any text-cell)
      (declare (ignore defining-class?))
      (let ((component-group
              (get-slot-component-group-by-reference
                frame
                (get-slot-component-group frame slot-name
                                          slot-component-indicator?)
                slot-component-name?)))
        (put-up-attributes-table
          frame x-in-window y-in-window nil
          (slot-component-group-master-slot-name component-group)
          (slot-component-group-indicator component-group))))))

(defun represents-non-default-value-of-non-default-component-group-p (text-cell)
  (multiple-value-bind (frame? slot-name? defining-class? slot-component-name?
                               slot-component-indicator?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (and (not (eq slot-component-indicator? 'default))
         (multiple-value-bind (ignore defaulted-p)
             (get-slot-component-value frame? slot-name? defining-class?
                                       slot-component-name?
                                       slot-component-indicator?)
           (declare (ignore ignore))
           (not defaulted-p))
         (let ((slot-component-features
                 (get-slot-component-features
                   slot-name? defining-class? slot-component-name?)))
           (not (feature-assq 'not-editable-in-default slot-component-features))))))


;;; The UI comands `show-text' and `show-summary-of-text' appear at present only
;;; on compound slots.  They allow the (full) text of such a slot to be shown or
;;; replaced with a (short) summary, respectively.  Note that a summarized text
;;; should not be have the EDIT menu choice.  Thus, the choices
;;; SHOW-SUMMARY-OF-TEXT and EDIT alternate with the choice SHOW-TEXT.  When
;;; attribute tables are put up interactively, the text is put into summary form
;;; by default.  The choice the user then sees most of the time is show-text.
;;; The text remains in summary form until the user chooses show-text.  Note that
;;; the choice whether to show text, or just show a summary, is only made on each
;;; individual cell of a table.  It does not affect how other tables display the
;;; same slot.

(define-ui-command (show-text)
    (attribute-table text-cell-of-table slot-name frame)
  (when (and (compound-slot-descriptor slot-name) ; for trend charts
             (let ((value-text-cell (get-attribute-value-text-cell
                                      attribute-table text-cell-of-table)))
               (and
                 (null (getf (text-cell-plist value-text-cell) 'slot-component-name))
                 (or (getf (text-cell-plist value-text-cell) 'text-summarized?)
                     (getf (text-cell-plist value-text-cell) 'exported-format)))))
    (show-attribute-as 'text attribute-table text-cell-of-table)))

(define-ui-command (show-attribute-as-text)
    (attribute-table text-cell-of-table slot-name frame)
  (when (and
          ;; show-text is used for trend charts, for compatibility, since it's
          ;; been that way since 4.0:
          (null (compound-slot-descriptor slot-name))

          (let ((value-text-cell (get-attribute-value-text-cell
                                   attribute-table text-cell-of-table)))
            (and
              (null (getf (text-cell-plist value-text-cell) 'slot-component-name))
              (or (getf (text-cell-plist value-text-cell) 'text-summarized?)
                  (getf (text-cell-plist value-text-cell) 'exported-format)))))
    (show-attribute-as 'text attribute-table text-cell-of-table)))

(define-ui-command (show-summary-of-text)
    (attribute-table text-cell-of-table slot-name)
  (when (and (compound-slot-descriptor slot-name)
             (let ((value-text-cell (get-attribute-value-text-cell
                                      attribute-table text-cell-of-table)))
               (and
                 (null (getf (text-cell-plist value-text-cell) 'slot-component-name))
                 (or (null (getf (text-cell-plist value-text-cell) 'text-summarized?))
                     (getf (text-cell-plist value-text-cell) 'exported-format)))))
    (show-attribute-as
      'summary-of-text
      attribute-table text-cell-of-table)))



(defun show-attribute-as (what attribute-table text-cell-of-table)
  (let* ((value-text-cell
           (get-attribute-value-text-cell
             attribute-table text-cell-of-table))
         text-summarized?
         (exported-format
           (case what
             (summary-of-text
              (setq text-summarized? t)
              nil)
             (text
              (setq text-summarized? nil)
              nil)
             (value
              (setq text-summarized? nil)
              t)
             (t
              #+development
              (cerror "continue anyway"
                      "~a is an unknown spec for show-value-as" what)))))
    (change-text-cell-property
      value-text-cell 'text-summarized? text-summarized?)
    (change-text-cell-property
      value-text-cell 'exported-format exported-format)
    (update-text-cell-for-slot-in-table attribute-table value-text-cell)))



(defun permit-view-slot-in-exported-format-p (text-cell)
  (multiple-value-bind (frame slot-name defining-class?
                              slot-component-name? slot-component-indicator?
                              virtual-attribute?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (declare (ignore slot-component-indicator?))
    (unless (or virtual-attribute? slot-component-name? (null frame))
      (let ((slot-description? (slot-description-from-class
                                 (class frame) slot-name defining-class?)))
        (when slot-description?
          (if (system-defined-slot-description-p slot-description?)
              (let ((type? (feature-assq 'type (slot-features slot-description?))))
                (and type?
                     (not (text-slot-type-p type?))
                     (let ((category? (category-symbol-given-slot-type type?)))
                       (and category?
                            (slot-value-to-evaluation-value-function category?)
                            (not (text-category-evaluator-interface-p category?))))))
              (let ((value (get-slot-description-value frame slot-description?)))
                (or (evaluation-sequence-p value)
                    (evaluation-structure-p value)))))))))

(define-ui-command (show-attribute-as-value)
    (attribute-table text-cell-of-table slot-name frame)
  (when (let ((value-text-cell (get-attribute-value-text-cell
                                 attribute-table text-cell-of-table)))
          (and (permit-view-slot-in-exported-format-p value-text-cell)
               (null (getf (text-cell-plist value-text-cell) 'exported-format))))
    (show-attribute-as
      'value attribute-table text-cell-of-table)))

;; Note: show-attribute-as-value is the reverse of show-attribute-as-text.

(defun editable-yes-or-no-slot-p (text-cell)
  (multiple-value-bind (frame slot-name defining-class? slot-component-name?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (let* ((features (get-attribute-features
                       (class frame) slot-name defining-class?
                       slot-component-name?))
           (type-of-slot?
             (type-slot-feature-assq-if-editable features))
           (category-symbol?
             (if type-of-slot?
                 (category-symbol-given-slot-type type-of-slot?))))
      (and (memq category-symbol? grammar-categories-getting-yes-no-feature)
           (item-is-either-not-permanent-or-from-an-editable-module-p frame)))))


(define-ui-command (revert-slot-component-value :name link-to-default)
    ((table attribute-table)
     (text-cell
       text-cell-of-table)
     image-plane original-x-in-window original-y-in-window)
  (when (and (attribute-table-p table)
             (represents-slot-component-value-p text-cell)
             (let ((value-text-cell
                      (get-attribute-value-text-cell
                        table text-cell)))
               (or (editable-text-cell-p table value-text-cell)
                   (editable-yes-or-no-slot-p value-text-cell)))
             (represents-non-default-value-of-non-default-component-group-p
               text-cell))
    ;; should have same predicate as edit-attribute-value
    ;; AND be filled with a non-default value
    ;; AND not be a component of default slot component group
    (multiple-value-bind (frame slot-name defining-class?
                                slot-component-name? slot-component-indicator?)
        (get-slot-represented-by-text-cell-if-any text-cell)
      (revert-slot-component-value
        frame slot-name defining-class?
        slot-component-name? slot-component-indicator?))))

(define-ui-command (choose-table-for-reference :name change-reference)
    ((frame frame-represented-by-table)
     (mouse-pointer mouse-pointer)        ; to make arg for slot-component-groups presentation type
     (slot-component-indicator-for-referred
       (non-default-referred-slot-component-groups mouse-pointer))
     (slot-name slot-name)
     (defining-class defining-class)
     (text-cell text-cell-of-table)
     (slot-component-name slot-component-name?)
     (slot-component-indicator? slot-component-indicator?))
  (when (represents-reference-slot-component-value-p text-cell)
    (let* ((referred-slot-name
             (get-referred-slot-name slot-name slot-component-name))
           (slot-component-group
             (get-slot-component-group frame referred-slot-name
                                       slot-component-indicator-for-referred))
           (name-or-names?
             (slot-component-group-name-or-names
               slot-component-group
               (component-type slot-component-group)))
           (slot-component-group-name?
             (if name-or-names?
                 (if (consp name-or-names?)
                     (car name-or-names?)
                     name-or-names?))))
      (change-slot-value
        frame slot-name
        (or slot-component-group-name?
            (get-current-place-of-component-group
              frame referred-slot-name slot-component-indicator-for-referred))
        defining-class
        slot-component-name
        slot-component-indicator?))))


(define-ui-command (add-slot-component-group :name add-subtable)
    ((text-cell text-cell-of-table) x-in-window y-in-window)
  (when (represents-multiple-component-value-p text-cell)
    (multiple-value-bind (frame slot-name defining-class?)
        (get-slot-represented-by-text-cell-if-any text-cell)
      (declare (ignore defining-class?))
      (let* ((new-component-group
               (add-instance-to-multiple-compound-slot-value
                 frame
                 slot-name                ; defining-class? later!
                 nil nil nil))
             (slot-component-indicator
               (compound-type-instance-indicator? new-component-group)))
        (put-up-attributes-table
          frame x-in-window y-in-window nil
          slot-name                        ; defining-class? later!
          slot-component-indicator)))))

(define-ui-command (delete-slot-component-group :name delete-subtable)
    ((frame frame-represented-by-table)
     (mouse-pointer mouse-pointer)        ; to make arg for slot-component-groups presentation type
     (slot-component-indicator-for-group
       (non-default-slot-component-groups mouse-pointer))
     (slot-name slot-name)
     (defining-class defining-class)
     (text-cell text-cell-of-table)
      x-in-window y-in-window)
   (when (and (represents-multiple-component-value-p text-cell)
             (multiple-component-value-has-deleteable-group
               frame slot-name defining-class))
     (confirm-and-remove-slot-component-group
      frame slot-name nil slot-component-indicator-for-group
      x-in-window y-in-window)))

(defun confirm-and-remove-slot-component-group
    (frame slot-name defining-class slot-component-indicator-for-group
           x-in-window y-in-window)
  (enter-dialog
    ;; dialog-message-text-string
    (tformat-text-string "Delete this ~(~a~)?"
                         (compound-slot-compound-type
                             (compound-slot-descriptor slot-name)))
    ;; ok-text-string? cancel-text-string?
    nil nil
    ;; ok-function? ok-function-arglist?
    'remove-instance-from-multiple-compound-slot-value
    (slot-value-list frame slot-name
                     defining-class
                     slot-component-indicator-for-group)
      ;; cancel-function? cancel-function-arglist?
    nil nil
    x-in-window y-in-window))


(defun multiple-component-value-has-deleteable-group
    (frame slot-name defining-class)
  (or (null (compound-slot-has-at-least-one-instance-p
              (compound-slot-descriptor slot-name)))
      (>f (slot-component-group-count
            frame slot-name defining-class)
          1)))


(define-ui-command (get-table-for-slot-component-group :name subtables)
    ((mouse-pointer mouse-pointer)        ; to make arg for slot-component-groups presentation type
     (slot-component-indicator-for-group (slot-component-groups mouse-pointer))
     (frame frame-represented-by-table)
     (slot-name slot-name)
     (text-cell text-cell-of-table)
     x-in-window
     y-in-window)
  (when (represents-multiple-component-value-p text-cell)
    (put-up-attributes-table
      frame x-in-window y-in-window nil
      slot-name slot-component-indicator-for-group)))

(defun get-table-for-slot-component-group (slot-component-indicator-for-group)
  slot-component-indicator-for-group)




;;;; Commands for Slot Components, Directly on Frames


;;; The presentation type `slot-component-group' supports getting a
;;; slot-component group indicator in a given compound slot that's a
;;; multiple-component type of compound slot.
;;;
;;; It either returns immediately the one component-group indicator, if there is
;;; just one, or gives a submenu of the available groups, resulting in the
;;; indicator chosen by the user from the menu.

(define-presentation-type slot-component-group-indicator
    (a-mouse-pointer block compound-slot-name)
  :available-p
    ((mp block csn)
     (slot-component-groups-exist-for-mouse-pointer-p
       mp block csn))
  :choices
    (map-mouse-pointer-to-menu-choices-for-slot-component-group-indicators
      a-mouse-pointer block compound-slot-name  t)
  :choice-transformer get-table-for-slot-component-group
  :menu-options (:title "subtable")        ; needs to be computed! ("plots", "value axes", etc.)
  :immediate-value
    ((mp block csn)
     (map-mouse-pointer-to-slot-component-group-if-only-one
       mp block csn t)))

(defun map-mouse-pointer-to-slot-component-group-if-only-one
    (mouse-pointer block compound-slot-name allow-defaults-p)
  (declare (ignore mouse-pointer))
  (get-first-slot-component-group-indicator-if-only-one
    block compound-slot-name allow-defaults-p))

(defun slot-component-groups-exist-for-mouse-pointer-p
    (mouse-pointer block compound-slot-name)
  (declare (ignore mouse-pointer))
  (component-groups-for-compound-slot-value
    (get-slot-value block compound-slot-name)))

(defun map-mouse-pointer-to-menu-choices-for-slot-component-group-indicators
    (mouse-pointer block compound-slot-name allow-default-p)
  (declare (ignore mouse-pointer))
  (compute-menu-choices-for-slot-component-group-indicators
    block compound-slot-name allow-default-p))





;;;; Commands for Trend-Charts



;;; The `generate-spot method for trend-chart' generates a
;;; `trend-chart spot'.  Note that trend-chart spots can be generated only for
;;; instances of the class trend-chart.


(def-spot trend-chart-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented trend-chart)

;; This must preceed use of make-trend-chart-spot in the load order.


(def-class-method generate-spot (trend-chart mouse-pointer)
  (push-last-spot mouse-pointer (make-trend-chart-spot) trend-chart))

(defmenu (trend-chart-menu :class-name-or-names-for-export trend-chart
                           :restriction-type item-menu) (trend-chart-spot)
  table
  operate-on-plot-subtable
  operate-on-value-axis-subtable
  get-table-for-time-axis-of-trend-chart
  operate-on-point-format-subtable
  operate-on-connector-format-subtable
  get-table-for-trend-chart-format-of-trend-chart
  transfer move name clone                ; by inclusion?
  change-size-of-trend-chart

  delete
  (include entity-lifting-menu)
  enable disable describe table-of-hidden-attributes describe-configuration ; inclusion?

  (include stripping-and-marking-menu)
  (include user-menu-choices))



(define-presentation-type slot-component-group-indicator-for-operation
    (a-mouse-pointer block compound-slot-name operation)
;  :available-p
;    ((mp block csn)
;     (slot-component-groups-exist-for-mouse-pointer-p
;       mp block csn))
  :choices
    (compute-indicators-for-slot-component-operation
      a-mouse-pointer block compound-slot-name operation)
  :choice-transformer get-table-for-slot-component-group
  :menu-options (:title "subtable")
  :immediate-value
    ((mp block csn operation)
     (get-indicator-for-slot-component-operation-if-only-one-exsts
       mp block csn operation)))

(defun slot-component-groups-exist-for-operation-p
    (mouse-pointer block compound-slot-name operation)
  (case operation
    ((subtable  delete-subtable)
     (slot-component-groups-exist-for-mouse-pointer-p
       mouse-pointer block compound-slot-name))
    (add-subtable nil)
    (defaults-subtable t)))

(defun get-indicator-for-slot-component-operation-if-only-one-exsts
    (mouse-pointer block compound-slot-name operation)
  (case operation
    (subtable
     (map-mouse-pointer-to-slot-component-group-if-only-one
       mouse-pointer block compound-slot-name nil))
    (delete-subtable
     nil)
    (add-subtable
     t)
    (defaults-subtable
        'default)))

(defun compute-indicators-for-slot-component-operation
    (mouse-pointer block compound-slot-name operation)
  (case operation
    ((subtable delete-subtable)
     (map-mouse-pointer-to-menu-choices-for-slot-component-group-indicators
       mouse-pointer block compound-slot-name nil))
    ((add-subtable defaults-subtable)
     (slot-value-list
       (slot-value-list 'choice
                        (tformat-text-string "bug -- shouldn't need this menu")
                        'default)))))


(define-presentation-type slot-component-group-operation
    (a-mouse-pointer block compound-slot-name)
  :choices (compute-slot-component-operations
             a-mouse-pointer block compound-slot-name)
  )

(defun compute-slot-component-operations (mouse-pointer block compound-slot-name)
  (declare (ignore mouse-pointer))
  (cond
    ((multiple-component-value-has-deleteable-group
       block compound-slot-name nil) ; last arg should be defining class
     (slot-value-list 'subtable 'add-subtable 'delete-subtable 'defaults-subtable))
    (t
     (slot-value-list 'subtable 'add-subtable 'defaults-subtable))))

(defun ok-plot-operation ()

  t)

(defmacro define-slot-component-group-operations-command
    (command-name command-pretty-name slot-name operation-menu-title)
  `(define-ui-command (,command-name :name ,command-pretty-name)
       ((mouse-pointer mouse-pointer)
        (block block)
        (subtable-operation
          ((slot-component-group-operation
             mouse-pointer block ',slot-name) :title ',operation-menu-title))
        (slot-component-group-indicator
          (slot-component-group-indicator-for-operation
            mouse-pointer block ',slot-name subtable-operation))
        original-x-in-window original-y-in-window)
     (when t
       (case subtable-operation
         ((subtable defaults-subtable)
          (put-up-attributes-table
            block original-x-in-window original-y-in-window nil
            ',slot-name slot-component-group-indicator))
         (add-subtable
          (let* ((new-component-group
                   (add-instance-to-multiple-compound-slot-value
                     block
                     ',slot-name
                     nil nil nil))
                 (slot-component-indicator
                   (compound-type-instance-indicator? new-component-group)))
            (put-up-attributes-table
              block original-x-in-window original-y-in-window nil
              ',slot-name
              slot-component-indicator)))
         (delete-subtable
          (when slot-component-group-indicator
            (confirm-and-remove-slot-component-group
              block ',slot-name nil slot-component-group-indicator
              original-x-in-window original-y-in-window)))))))

;            (remove-instance-from-multiple-compound-slot-value
;              block ',slot-name
;             nil ; defining-class
;              slot-component-group-indicator)))))))

(define-slot-component-group-operations-command operate-on-plot-subtable
    plots trend-chart-plots plots)
(define-slot-component-group-operations-command operate-on-value-axis-subtable
    value-axes trend-chart-value-axes value-axes)
(define-slot-component-group-operations-command operate-on-point-format-subtable
    point-formats trend-chart-point-formats point-formats)
(define-slot-component-group-operations-command operate-on-connector-format-subtable
    connector-formats trend-chart-connector-formats connector-formats)


;;; The UI command `get-table-for-plot-of-trend-chart' appears on the menu you get
;;; when you click on a trend-chart as the choice `plots'.  If there are more plots
;;; than one, the user initially sees a submenu listing the choices
;;; corresponding to each plot, e.g., something like
;;;
;;;   PLOT #1
;;;   PLOT #2 TEMPERATURE-PLOT
;;;   PLOT #3 PRESSURE-PLOT
;;;
;;; Selecting one of these choice brings up the table showing the corresponding
;;; value axis.  If there is only one plot, it brings up the table for it right
;;; away without an intervening submenu.
;;;
;;; Note that, apart from the title, this appears as the same menu you get when
;;; you click on the plots attribute (internally the trend-chart-plots slot) in a
;;; table for a trend-chart.

(define-ui-command (get-table-for-plot-of-trend-chart :name plot-subtable)
    ((mouse-pointer mouse-pointer)
     (block block)
     (slot-component-group-indicator
       (slot-component-group-indicator mouse-pointer block 'trend-chart-plots))
     trend-chart
     original-x-in-window original-y-in-window)
  (when (component-groups-for-compound-slot-value
          (get-slot-value trend-chart 'trend-chart-plots))
    (put-up-attributes-table
      trend-chart original-x-in-window original-y-in-window nil
      'trend-chart-plots slot-component-group-indicator)))




;;; The UI command `get-table-for-value-axis-of-trend-chart' appears on the menu you
;;; get when you click on a trend-chart as the choice `value axes'.  If there are more
;;; than one, the user initially sees a submenu listing the choices
;;; corresponding to each plot, e.g., something like
;;;
;;;   VALUE-AXIS #1
;;;   VALUE-AXIS #2 AXIS-FOR-TEMPERATURE-PLOT
;;;   VALUE-AXIS #3 AXIS-FOR-PRESSURE-PLOT
;;;   VALUE-AXIS #4
;;;   VALUE-AXIS #5 AXIS-FOR-MISCELLANEOUS-PLOTS
;;;
;;; Selecting one of these choice brings up the table showing the corresponding
;;; value axis.  If there is only one value axis, it brings up the table for it
;;; right away without an intervening submenu.
;;;
;;; Note that, apart from the title, this appears as the same menu you get when
;;; you click on the value-axes attribute (internally the trend-chart-value-axes slot)
;;; in a table for a trend-chart.

(define-ui-command (get-table-for-value-axis-of-trend-chart :name value-axis-subtable)
    ((mouse-pointer mouse-pointer)
     (block block)
     (slot-component-group-indicator
       (slot-component-group-indicator mouse-pointer block 'trend-chart-value-axes))
     trend-chart
     original-x-in-window original-y-in-window)
  (when (component-groups-for-compound-slot-value
          (get-slot-value trend-chart 'trend-chart-value-axes))
    (put-up-attributes-table
      trend-chart original-x-in-window original-y-in-window nil
      'trend-chart-value-axes slot-component-group-indicator)))



;;; The UI command `get-table-for-time-axis-of-trend-chart' appears on the menu you
;;; get when you click on a trend-chart as the choice `time axis'.
;;;
;;; Selecting this choice brings up the table showing the trend-chart's time axis.
;;;
;;; Note that, apart from the title, this appears as the same menu you get when
;;; you click on the time-axis attribute (internally the trend-chart-time-axis slot)
;;; in a table for a trend-chart.

(define-ui-command (get-table-for-time-axis-of-trend-chart :name time-axis-subtable)
    ((mouse-pointer mouse-pointer)
     trend-chart
     original-x-in-window original-y-in-window)
  (put-up-attributes-table
    trend-chart original-x-in-window original-y-in-window nil
    'trend-chart-time-axis nil))



;;; The UI command `get-table-for-connector-format-of-trend-chart' ...

(define-ui-command (get-table-for-connector-format-of-trend-chart :name connector-format-subtable)
    ((mouse-pointer mouse-pointer)
     (block block)
     (slot-component-group-indicator
       (slot-component-group-indicator mouse-pointer block 'trend-chart-connector-formats))
     (trend-chart frame)
     original-x-in-window original-y-in-window)
  (when (component-groups-for-compound-slot-value
          (get-slot-value trend-chart 'trend-chart-connector-formats))
    (put-up-attributes-table
      trend-chart original-x-in-window original-y-in-window nil
      'trend-chart-connector-formats slot-component-group-indicator)))


;;; The UI command `get-table-for-point-format-of-trend-chart' ...

(define-ui-command (get-table-for-point-format-of-trend-chart :name point-format-subtable)
    ((mouse-pointer mouse-pointer)
     (block block)
     (slot-component-group-indicator
       (slot-component-group-indicator mouse-pointer block 'trend-chart-point-formats))
     (trend-chart frame)
     original-x-in-window original-y-in-window)
  (when (component-groups-for-compound-slot-value
          (get-slot-value trend-chart 'trend-chart-point-formats))
    (put-up-attributes-table
      trend-chart original-x-in-window original-y-in-window nil
      'trend-chart-point-formats slot-component-group-indicator)))



;;; The UI command `get-table-for-format-of-trend-chart' ...

(define-ui-command (get-table-for-trend-chart-format-of-trend-chart
                     :name trend-chart-format-subtable)
    ((mouse-pointer mouse-pointer)
     trend-chart
     original-x-in-window original-y-in-window)
  (put-up-attributes-table
    trend-chart original-x-in-window original-y-in-window nil
    'trend-chart-format nil))




;;; The UI command `change-size-of-trend-chart' appears on the menu you get when
;;; you click on a trend-chart as the choice `change size'.  This behaves just
;;; the same as the other commands with the same appearance.

(define-ui-command (change-size-of-trend-chart :name change-size)
    (trend-chart image-plane original-x-in-window original-y-in-window)
  (enter-sizing-dialog
    trend-chart image-plane original-x-in-window original-y-in-window))

;; Make a generic version of this, and eliminate this and the other 3 or 4
;; separate ui commands! (MHD 2/8/94)



;;;; Native UI Commands


(defun get-check-box-value-from-plist (plist property)
  (getf plist property))


;; Cf load-or-merge-kb-from-file-command
(defun load-or-merge-kb-from-native-file-dialog (pathname event-plist)
  (multiple-value-bind
      (bring-formats-up-to-date? warmboot-case? auto-merge-case?
                                 install-system-tables-if-merge-case?
                                 what-to-do-after-loading-kb? merge-kb?
                                 update-before-loading?)
      (get-button-settings-for-file-command #'get-check-box-value-from-plist event-plist)
    (load-or-merge-kb-if-ok
      (gensym-pathname pathname)
      (if merge-kb?                        ; load-case?
          nil
          (if (empty-kb-p) t 'replace))
      bring-formats-up-to-date?
      warmboot-case?
      auto-merge-case?
      install-system-tables-if-merge-case?
      what-to-do-after-loading-kb?
      update-before-loading?)))


;;; The event-handler `handle-file-dialog-message' processes all choices made
;;; from native file dialogs. We check directly here for KB load/merge/save
;;; operations, and will later handle others uses of the dialog, such as
;;; KB-level system procedures.

(define-event-handler handle-file-dialog-message ((gensym-window window) event-plist)
  (let* ((operation (getf event-plist 'operation))
         (pathname? (getf event-plist 'pathname))
         (handle (getf event-plist 'dialog-handle))
         (current-default-pathname? (make-default-pathname
                                      (symbolic-file-type-for-file-command? operation))))
    (when (and (eq operation 'save-module)
               (getf event-plist 'save-all-to-one-file))
      (setq operation 'save-kb))
    (case operation
      (sysproc                        ; Call from KB-level procedure.
       (handle-dialog-response 'file handle (copy-if-text-string pathname?)))
      (t
       (when pathname?
         (case operation
           ((load-kb merge-kb)
            (when (load-kb-permitted-p)
              (load-or-merge-kb-from-native-file-dialog pathname? event-plist)))
           (save-kb
            (when (save-kb-permitted-p)
              (finish-executing-file-command
                'kb-save nil nil nil
                pathname? nil
                nil nil 'default nil nil nil nil
                current-default-pathname?
                pathname?
                nil nil nil 'default nil)))
           (save-module
            (when (save-kb-permitted-p)
              (finish-executing-file-command
                'save-module
                (or (getf event-plist 'module)
                    (get-slot-value module-information 'top-level-kb-module?))
                (getf event-plist 'including-all-required-modules)
                nil
                pathname?
                nil nil nil 'default nil nil nil nil
                current-default-pathname?
                pathname?
                nil nil 'default nil
                (getf event-plist 'save-only-changed-modules))))
           (load-attribute-file
            (when (not system-is-running)
              (let ((gp (gensym-pathname pathname?)))
                ;; Load-custom-software-file-if-ok REQUIRES a gensym-pathname
                ;; structure, and then owns it.
                (load-custom-software-file-if-ok gp 'attribute))))
           (connect-to-foreign-image
            ;; Not used yet.
            (when (not system-is-running)
              (connect-to-foreign-image (copy-if-text-string pathname?))))
           (disconnect-from-foreign-image
            ;; Not used yet.
            (when (not system-is-running)
              (disconnect-from-foreign-image (copy-if-text-string pathname?))))
           (write-g2-stats
            (write-g2-stats (copy-if-text-string pathname?)))
           (t
            (dwarn "Unhandled operation in handle-file-dialog-message: ~s" operation))))))))

;; See file-dialog-1 for the available event-plist properties.
;; Cf finish-executing-file-command and post-native-file-dialog

;; These conditions should not be needed since the operation can not be
;; initiated otherwise.
;;  (main-menu-command-permitted-p 'load-kb)
;;  (main-menu-command-permitted-p 'save-kb)


;;;; Operations on Current Selection


;; We may want to nicer alignment operations.  For now, we duplicate the
;; existing set of operate-on-area buttons.

;; This menu replaces the usual item menu if the item is a member of a
;; multi-element selection.
(defmenu (selection-menu :title selection :restriction-type item-menu) ()
  move-selection
  clone-selection
  transfer-selection
  align-selection
  distribute-selection
  delete-selection)

;; FIXME: These commands actually want to operate on the selected image-plane
;; only when they are bound to keystrokes.  If they are bound to mouse clicks,
;; then they want to operate on the image-plane under the mouse.

;; mouse-left-select on workspace background
(define-event-handler select-workspace-or-deselect-all (image-plane &optional selected-image-plane g2-window selected-workspace)
  (cond ((eq image-plane selected-image-plane)
         (raise-image-plane-to-top image-plane)
         (deselect-all-things selected-image-plane)
         (update-att-tables selected-workspace g2-window))
        ((selectable-image-plane-p image-plane)
         (select-and-raise-image-plane image-plane))))

;; mouse-left-select on item on workspace or g2-window background. Item and
;; image-plane were already selected on mouse-left-down, so we only need to
;; raise the image-plane.
(define-event-handler raise-image-plane (&optional (image-plane? image-plane))
  (when image-plane?
    (raise-image-plane-to-top image-plane?)))

;; escape
(define-ui-command deselect-all (selected-image-plane)
  (deselect-all-things selected-image-plane))

;; Alternate binding for escape
;; TODO: Permit classic G2 pop-up menus to be selected workspaces, so that
;; escape will deexpose them, too.
(define-ui-command deselect-all-or-dismiss (selected-image-plane)
  (let* ((selection? (image-plane-current-selection selected-image-plane)))
    (cond ((and selection? (>f (count-selection selection?) 0))
           (deselect-all-things selected-image-plane))
          ((temporary-workspace-p (workspace-on-image-plane? selected-image-plane))
           (delete-image-plane selected-image-plane)))))

(define-event-handler toggle-selection-of-item (thing-to-select image-plane)
  (when (thing-selectable-via-ui-p thing-to-select)
    (cond ((thing-selected-p thing-to-select image-plane)
           (deselect-thing thing-to-select image-plane))
          (t
           (select-image-plane image-plane)
           (select-thing thing-to-select image-plane)))))

;; Shift+mouse-left/right-down
(define-event-handler toggle-selection-of-item-then-search-for-mouse-drag (mouse-pointer)
  (toggle-selection-of-item mouse-pointer)
  (search-for-mouse-drag mouse-pointer))


;; Selects just this item, unless it was already selected.
(define-event-handler select-this-item (thing-to-select image-plane g2-window) ;; Added by SoftServe for Gensym-381 
  (when (thing-selectable-via-ui-p thing-to-select)
    (select-image-plane image-plane)
    (unless (thing-selected-p thing-to-select image-plane)
      (set-selection thing-to-select image-plane g2-window)))) ;; Added by SoftServe for Gensym-381

;; mouse-left/right-down or Control+mouse-left/right-down
(define-event-handler select-then-search-for-mouse-drag (mouse-pointer)
  (select-this-item mouse-pointer)
  (search-for-mouse-drag mouse-pointer))

;; mouse-left-select on a table value cell
(define-event-handler select-then-raise-image-plane (mouse-pointer image-plane)
  (select-this-item mouse-pointer)
  (raise-image-plane-to-top image-plane))

;; mouse-left-down on a text-cell. Select unless parent table is already selected.
(define-event-handler maybe-select-part-then-search-for-mouse-drag
    (thing-to-select image-plane mouse-pointer)
  (unless (thing-or-parent-selected-p thing-to-select image-plane)
    (select-this-item mouse-pointer))
  (search-for-mouse-drag mouse-pointer))


(defvar connected-subnet ())

(defun compute-connected-subnet-1 (node)
  (unless (memq node connected-subnet)
    (dragging-push node connected-subnet)
    (cond ((connection-p node)
           (compute-connected-subnet-1 (input-end-object node))
           (compute-connected-subnet-1 (output-end-object node)))
          ((framep node)
           (loop for connection being the connections of node
                 doing (compute-connected-subnet-1 connection))))))

;;; The function `compute-connected-subnet' returns a new dragging list of the
;;; transitive closure over connectedness from root.

(defun compute-connected-subnet (root)
  (let ((connected-subnet ()))
    (when (or (connection-p root) (framep root)) ; Disallow text cells
      (compute-connected-subnet-1 root))
    (nreverse connected-subnet)))

(defun select-network (thing image-plane)
  (select-image-plane image-plane)
  (let ((things (compute-connected-subnet thing)))
    (loop for thing in things doing
      (when (thing-selectable-via-ui-p thing)
        (select-thing thing image-plane)))
    (reclaim-dragging-list things)))

(defun toggle-select-network (thing image-plane)
  (select-image-plane image-plane)
  (let ((things (compute-connected-subnet thing)))
    (cond ((loop for thing in things
                 always (thing-selected-p thing image-plane))
           (deselect-things things image-plane))
          (t
           (loop for thing in things doing
             (when (thing-selectable-via-ui-p thing)
               (select-thing thing image-plane)))))
    (reclaim-dragging-list things)))

;; Alt+mouse-left/right-down selects connected network of items and connections.
(define-event-handler select-network-then-search-for-mouse-drag
    (thing-to-select image-plane mouse-pointer)
  (deselect-all-things image-plane)
  (select-network thing-to-select image-plane)
  (search-for-mouse-drag mouse-pointer))

;; Shift+Alt+mouse-left/right-down toggles connected network's membership in selection.
(define-event-handler toggle-select-network-then-search-for-mouse-drag
    (thing-to-select image-plane mouse-pointer)
  (toggle-select-network thing-to-select image-plane)
  (search-for-mouse-drag mouse-pointer))


;;; The ui-command `select-all' selects all selectable top-level blocks and
;;; connections on workspace.  It does not select subblocks or text-cells.

(define-ui-command select-all (selected-workspace selected-image-plane)
  (let ((things (compute-workspace-selectables selected-workspace t)))
    (select-things things selected-image-plane)
    (reclaim-gensym-list things)))


;; Alt+return
(define-ui-command (selection-properties :name table :pretty-name "Table")
    (original-x-in-window original-y-in-window)
  "Put up the attributes table for current selection."
  (when (and (primary-selection-as-block)
             (allow-table-command-p (primary-selection-as-block)))
    (put-up-attributes-table (primary-selection-as-block)
                             original-x-in-window original-y-in-window)))
;; TODO: fancy composite table when selection has more than one item.


;; This is bound only to right-click on the workspace background, so we know
;; that really-post-object-menu will post the workspace menu.
(define-event-handler select-then-post-workspace-menu (image-plane mouse-pointer &optional g2-window selected-workspace)
  (deselect-all-things image-plane)
  (select-image-plane image-plane)
  (update-att-tables selected-workspace g2-window)
  (really-post-object-menu mouse-pointer))

;; Posts the menu as if user right-clicked on the primary selection.
(define-ui-command (post-menu-for-selection :pretty-name "Menu")
    (workstation)
  (when (eq (workstation-login-state workstation) 'logged-in) ; HQ-4714353
    (let ((thing? (get-selection workstation)))
      (when thing?
        (let ((mouse-pointer (synthesize-mouse-pointer workstation thing?
                                                       (key-code 'non-event))))
          (really-post-object-menu mouse-pointer)
          (release-mouse-pointer-if-any mouse-pointer))))))


;;; The function `click-button' simulates clicking on the center of the given
;;; action button on workstation.

(defun click-button (button workstation)
  (let* ((workspace? (get-workspace-if-any button))
         (current-image-plane-for-button
           (and workspace? (image-plane-for-workspace workspace? workstation))))
    (when current-image-plane-for-button
      (highlight-or-unhighlight-button button nil) ; The click method unhighlights it.
      (multiple-value-bind (x-in-workspace y-in-workspace)
          (center-of-thing button)
        (funcall-method 'click button x-in-workspace y-in-workspace)))))


;;; The ui-command `perform-default-action' is bound to double-click and operates
;;; on the item clicked on, as opposed to the current selection. Of course, since
;;; the first click selected, it amounts to operating on the selection.

(define-ui-command (perform-default-action :name default-action)
    (mouse-pointer &optional short-representation-table)
  (let ((tightness-of-text-spot-for-click-to-edit 100))
    (cond
      ;; These may be available when click-to-edit is not.
      ((command-available-p 'edit-name-box mouse-pointer)
       (start-ui-command 'edit-name-box mouse-pointer))
      ((command-available-p 'change-to-yes mouse-pointer)
       (start-ui-command 'change-to-yes mouse-pointer))
      ((command-available-p 'change-to-no mouse-pointer)
       (start-ui-command 'change-to-no mouse-pointer))
      ((command-available-p 'change-to mouse-pointer)
       (start-ui-command 'change-to mouse-pointer))

      ((command-available-p 'click-to-edit mouse-pointer) ; Checks restrictions.
       (start-ui-command 'click-to-edit mouse-pointer))

      (short-representation-table
       ;; This operates on the item represented.
       (start-ui-command 'table-for-short-representation mouse-pointer))
      (t
       ;; This operates on the table itself, if any.
       (start-ui-command 'table mouse-pointer)))))

;; This tries to enter the editor even for cases where click-to-edit fails
;; simply due to the tightness-of-text-spot being greater than 50. This case
;; obtains, eg, for double-click on an empty table cell. In classic G2 that case
;; pops up a menu which includes Edit.



;;; The function `run-ui-command-on-selection' runs the given command on a
;;; mouse-pointer corresponding to the current selection.

(defun run-ui-command-on-selection (command-name workstation)
  (let ((mouse-pointer (selection-mouse-pointer workstation)))
    (start-ui-command command-name mouse-pointer)
    (release-mouse-pointer-if-any mouse-pointer)))



;;; The ui-command `perform-default-action-on-selection-if-any' does something
;;; only if the selection is not just the selected workspace; that is, there are
;;; some items selected on the selected workspace.

(define-ui-command (perform-default-action-on-selection-if-any :name default-action)
    (workstation mouse-pointer)
  (when (primary-selection workstation)
    (start-ui-command 'perform-default-action-on-selection mouse-pointer)))

;;; The ui-command `perform-default-action-on-selection' is bound to return and
;;; space and generally does the same thing as double-click on the selection,
;;; with a couple of exceptions.

(define-ui-command (perform-default-action-on-selection :name default-action)
    (workstation workstation-context mouse-pointer)
  (let ((thing (get-selection workstation)))
    (cond ((secondary-selection workstation)
           (default-action-on-multi-selection workstation))

          ((and (text-cell-p thing)
                (eq (type-of-workstation-context workstation-context) 'g2-login))
           ;; FIXME: Kludge for g2-login, probably others need it too.
           (let ((mouse-pointer (synthesize-mouse-pointer workstation thing (key-code 'mouse-down))))
             (mouse-down-on-attribute-value-in-g2-login-state mouse-pointer)
             (release-mouse-pointer-if-any mouse-pointer)))

          ((and (and (framep thing) (button-p thing) (perform-button-action? thing)))
           (click-button thing workstation))

          (t
           (run-ui-command-on-selection 'perform-default-action workstation)))))


;;; The function `default-action-on-multi-selection' pops-up tables for each
;;; item in the selection. An experiment on users for 7.0 alpha.

(defparameter maximum-number-of-tables-to-pop-up 25)

(defun default-action-on-multi-selection (workstation)
  (let ((count 0))
    (block loop
      (do-selection-things (thing (current-selection workstation))
        (when (or (framep thing)
                  (connection-p thing))
          (let ((mouse-pointer (synthesize-mouse-pointer workstation thing)))
            (start-ui-command 'table mouse-pointer)
            (release-mouse-pointer-if-any mouse-pointer))
          (incff count)
          (when (>f count maximum-number-of-tables-to-pop-up)
            (notify-user "Limiting command to first ~d selected items"
                         maximum-number-of-tables-to-pop-up)
            (return-from loop)))))))

;; Without a cap, this would need to be schedulable!
;; TODO: Other loops over the current selection may need caps, also.

(defun center-of-thing-on-window (thing image-plane?)
  (cond ((and (framep thing)
              (workspace-p thing)
              (native-image-plane-p image-plane?))
         (native-window-center (image-plane-native-window? image-plane?)))
        (t
         (multiple-value-bind (x-in-workspace y-in-workspace)
             (center-of-thing thing)
           (values (if image-plane?
                       (x-in-window-for-image-plane x-in-workspace image-plane?)
                       0)
                   (if image-plane?
                       (y-in-window-for-image-plane y-in-workspace image-plane?)
                       0))))))


;;; The function `synthesize-mouse-pointer' attempts to create the mouse-pointer
;;; which would have be created by a click on thing.

(defun synthesize-mouse-pointer (workstation thing? &optional key-code? x-in-window? y-in-window?)
  (let* ((gensym-window (window-for-workstation workstation))
         (workspace? (get-workspace-of-thing-if-any thing?))
         (pane? (detail-pane gensym-window))
         (image-plane? (and workspace?
                            (image-plane-of-workspace-on-workstation
                              workstation workspace?)))
         (time (if (boundp 'current-workstation-event)
                   (workstation-event-timestamp current-workstation-event)
                   0))
         (key-code (or key-code? (key-code 'non-event)))
         (mouse-pointer nil))

    (multiple-value-bind (x-in-window y-in-window)
        (center-of-thing-on-window thing? image-plane?)
      (setq x-in-window (or x-in-window? x-in-window)
            y-in-window (or y-in-window? y-in-window))
      (setq mouse-pointer (make-mouse-pointer workstation key-code time
                                              x-in-window y-in-window)))
    (setf (kind-of-mouse-pointer mouse-pointer) 'synthetic)
    ;; Record for memory management
    (gensym-push mouse-pointer (recent-mouse-pointers-1 workstation))
    ;; This call gets us to window.
    (push-more-detailed-spot mouse-pointer (make-entire-g2-window-spot)
                             (g2-window-for-this-workstation? workstation))
    (cond ((null thing?)
           (push-more-detailed-spot mouse-pointer (make-named-pane-spot pane?) nil)
           (push-last-spot mouse-pointer (make-pane-background-spot) nil))
          ((and (framep thing?) (workspace-p thing?) image-plane?)
           (push-more-detailed-spot mouse-pointer (make-named-pane-spot pane?) nil)
           (push-workspace-background-spots mouse-pointer image-plane?))
          (t
           (with-raw-window-transform-and-draw-area (gensym-window)
             (initialize-mouse-pointer-tracking-for-window
               workstation mouse-pointer pane? image-plane?)
             (cond ((connection-p thing?)
                    (funcall-method 'generate-spot (connection-frame thing?) mouse-pointer))
                   ((text-cell-p thing?)
                    (funcall-method 'generate-spot (get-table-for-cell thing?) mouse-pointer))
                   ((and (table-p thing?)
                         (or (attribute-table-p thing?) (multiframe-table-p thing?)))
                    (generate-spot-for-pure-input-table
                      thing? mouse-pointer (make-attribute-table-spot))
                    (push-last-spot mouse-pointer (make-table-background-spot) nil))
                   ((framep thing?)
                    (funcall-method 'generate-spot thing? mouse-pointer))
                   (t
                    ;; This case should never occur.
                    (dwarn "synthesize-mouse-pointer using default method for ~s" thing?)
                    (track-mouse-pointer-till-done mouse-pointer))))))
    ;; If there is a text-spot, clear the line and character positions,
    ;; causing the editor to use a default cursor position (at the beginning
    ;; of the text for a scrolling editor, and at the end otherwise). It is OK
    ;; for these slots to be NIL, even though they don't have "?" in their
    ;; names. See fill-out-text-spot.
    (let ((text-spot? (find-spot-of-type mouse-pointer 'text-spot)))
      (when text-spot?
        (setf (line-index-of-text-spot text-spot?) nil
              (character-index-of-text-spot text-spot?) nil)))
    mouse-pointer))


(defun push-workspace-background-spots (mouse-pointer image-plane)
  (let* ((workspace (workspace-on-image-plane? image-plane))
         (spot (make-workspace-spot workspace image-plane
                                    (x-of-mouse-pointer mouse-pointer)
                                    (y-of-mouse-pointer mouse-pointer))))
    (push-more-detailed-spot mouse-pointer spot workspace)
    (push-last-spot mouse-pointer (make-workspace-background-spot-function) nil)))



;;; The function `get-selection' returns the current primary selected
;;; object. This is either the primary selection, if there is a selection, or
;;; else the current selected workspace. It is the single object on which menu
;;; bar commands normally operate.

(defun get-selection (workstation)
  (or (primary-selection workstation)
      (selected-workspace workstation)))


;;; The function `selection-mouse-pointer' returns a newly-consed mouse-pointer
;;; which attempts to "point" at the currently *primary* selection, if any, or
;;; else the selected workspace. A flag in the mouse-pointer notes whether there
;;; was actually more than one item selected.

(defun selection-mouse-pointer (workstation)
  (let ((mouse-pointer (synthesize-mouse-pointer workstation (get-selection workstation))))
    (when (secondary-selection workstation)
      (setf (kind-of-mouse-pointer mouse-pointer) 'multi))
    mouse-pointer))


;;; The function `prepare-for-selection-moving' does stuff common to move and
;;; transfer selections.  It returns only those blocks for which dragging is
;;; permitted. It warps the mouse cursor to the mouse-pointer's position, so
;;; that we start with a zero offset.

(defun prepare-for-selection-moving (mouse-pointer blocks)
  (set-cursor-position (x-of-mouse-pointer mouse-pointer) (y-of-mouse-pointer mouse-pointer))
  (with-mouse-pointer-bindings (x-in-window y-in-window image-plane frame-for-selection
                                      &optional original-x-in-window original-y-in-window)
      mouse-pointer
    (let* ((block (first blocks))
           (x (or original-x-in-window x-in-window))
           (y (or original-y-in-window y-in-window))
           x-offset-from-dragger
           y-offset-from-dragger)
      (when blocks
        ;; Push back a mouse-motion to get the dragging started.
        (requeue-mouse-motion-event mouse-pointer)

        ;; Dragging context drags relative to the first block in the list,
        ;; so make block be that.
        (when (and (memq frame-for-selection blocks)
                   (neq frame-for-selection block))
          (setq blocks (delete-dragging-element frame-for-selection blocks))
          (setq blocks (dragging-cons frame-for-selection blocks))
          (setq block frame-for-selection))

        (with-image-plane-transform (image-plane)
          (setq x-offset-from-dragger (-w (x-in-workspace x) (left-edge-of-block block)))
          (setq y-offset-from-dragger (-w (y-in-workspace y) (top-edge-of-block block))))
        (values blocks image-plane x-offset-from-dragger y-offset-from-dragger)))))

;; TODO: check restrictions.


(define-ui-command (move-selection :name move) (workspace image-plane mouse-pointer)
  (when (image-plane-selection-non-empty-p image-plane)
    (cond ((non-kb-workspace-p workspace)
           (start-ui-command 'move-workspace mouse-pointer))
          (t
           (multiple-value-bind (blocks image-plane dx dy)
               (prepare-for-selection-moving mouse-pointer
                                             (compute-blocks-to-move-from-selection
                                               (image-plane-current-selection image-plane)))
             (when blocks
               (enter-move-dragging-context blocks dx dy image-plane)))))))

(defun selection-transferable-p (selection)
  (let ((blocks (compute-blocks-from-selection selection)))
    (prog1 (blocks-transferable-p blocks)
      (reclaim-dragging-list blocks))))

;; Called only from a popup menu on a selected item.
(define-ui-command (transfer-selection :name transfer) (image-plane mouse-pointer)
  (when (and (image-plane-selection-non-empty-p image-plane)
             (selection-transferable-p (image-plane-current-selection image-plane)))
    (let ((blocks (compute-blocks-from-selection
                    (image-plane-current-selection image-plane))))
      (multiple-value-bind (blocks image-plane dx dy)
          (prepare-for-selection-moving mouse-pointer blocks)
        (when blocks
          (enter-transfer-dragging-context blocks dx dy image-plane (mouse-down-p) nil))))))


(defun selection-cloneable-p (selection)
  (let ((blocks (compute-blocks-to-clone-from-selection selection)))
    (prog1 (not (null blocks))
      (reclaim-dragging-list blocks))))

(define-ui-command (clone-selection :name clone) (image-plane mouse-pointer)
  (when (and (image-plane-selection-non-empty-p image-plane)
             (selection-cloneable-p (image-plane-current-selection image-plane)))
    (multiple-value-bind (blocks image-plane dx dy)
        (prepare-for-selection-moving mouse-pointer
                                      (compute-blocks-to-clone-from-selection
                                        (image-plane-current-selection image-plane)))
      (when blocks
        ;; clone-blocks clones the internal connections amongst the blocks, too,
        ;; although it returns us just the blocks.
        (let ((clones (clone-blocks blocks)))
          ;; The -2 offset is to ensure clones appear immediately, rather than
          ;; XORing over their originals.  See warp-cursor-for-bounding-state-button
          ;; and clone-case of handle-block-motion-command-1.
          (enter-transfer-dragging-context clones (-w dx 2) (-w dy 2) image-plane)
          (reclaim-dragging-list blocks))))))





;;; The constant `align-selection-command-operations' is a list of the names
;;; (symbols) of selection operations. These are TOP, BOTTOM, TOP/BOTTOM-CENTER,
;;; LEFT, RIGHT, LEFT/RIGHT-CENTER for top, bottom, vertical center, left,
;;; right, and horizontal center alignment, respectively.  These are accepted as
;;; the OPERATION argument to the align-selection UI command, and they are also
;;; accepted as the operation arg by the align-blocks function (q.v., in
;;; FACILITIES).

(defvar align-selection-command-operations
  '(left left/right-center right top top/bottom-center bottom))



(define-ui-command (align-selection :name align :pretty-name "Align")
    ((operation (member align-selection-command-operations))
     image-plane)
  (when (selection-has-multiple-blocks-p image-plane)
    (let ((blocks (compute-selection-blocks (image-plane-current-selection image-plane))))
      (when blocks                        ; Paranoia
        (align-blocks blocks operation)
        (reclaim-dragging-list blocks)))))

;; TODO: Align on the primary selection.
;; TODO: Probably can use an alist in the member presentation type.
;; TODO: This one *really* wants to be undoable.


(define-ui-command (distribute-selection :name distribute :pretty-name "Distribute")
    ((operation (member distribute-selection-command-operations)) ; Tough to add accel chars!
     image-plane)
  (when (selection-has-at-least-n-blocks-p image-plane 3)
    (let ((blocks (compute-selection-blocks (image-plane-current-selection image-plane))))
      (when blocks                        ; Paranoia
        (distribute-blocks blocks operation)
        (reclaim-dragging-list blocks)))))


;;; The function `selectable-subblock-p' determines whether a subblock of a
;;; top-level block on a workspace is selected in the TAB ordering.  Somewhat
;;; arbitrarily, we allow only table-items (attribute displays).

(defun selectable-subblock-p (subblock)
  (frame-of-class-p subblock 'table-item))

;;; The function `compute-workspace-selectables' returns a newly consed
;;; gensym-list of the UI selectable, mostly-top-level objects on workspace, in
;;; order.

(defun compute-workspace-selectables (workspace forward)
  (let ((list ()))
    (loop for block being each subblock of workspace doing
      (when (thing-selectable-via-ui-p block)
        (gensym-push block list)
        (when (connections block)
          (loop for connection being the output-connections of block doing
            (when (thing-selectable-via-ui-p connection)
              (gensym-push connection list))))
        (when (has-subblocks-p block)
          (loop for subblock being each subblock of block doing
            (when (and (selectable-subblock-p subblock)
                       (thing-selectable-via-ui-p subblock))
              (gensym-push subblock list))))))
    (if forward (nreverse list) list)))

;; TODO: A stateful pointer to make these more efficient.
;; TODO: Configurable order and subset.


(defun next-selectable-block-on-workspace (workspace current)
  (let ((list (compute-workspace-selectables workspace t)))
    (prog1 (next-selectable-in-list current list)
      (reclaim-gensym-list list))))

(defun previous-selectable-block-on-workspace (workspace current)
  (let ((reversed (compute-workspace-selectables workspace nil)))
    (prog1 (next-selectable-in-list current reversed)
    (reclaim-gensym-list reversed))))


(defmacro do-selectable-cells-of-table ((cell table) &body body)
  (avoiding-variable-capture (table &aux row)
    `(dolist (,row (table-rows ,table))
       (dolist (,cell ,row)
         (when (selectable-table-cell-p ,table ,cell)
           ,@body)))))

(defun first-selectable-cell-of-table? (table)
  (block search
    (do-selectable-cells-of-table (cell table)
      (return-from search cell))))

(defun last-selectable-cell-of-table? (table)
  (let (last?)
    (do-selectable-cells-of-table (cell table)
      (setq last? cell))
    last?))


;; TODO: if next thing is a table and the table contains only one selectable
;; cell (eg, an attribute display with one entry without name), then skip the
;; table and select the cell.
(defun number-of-selectable-cells-in-table (table)
  (let ((count 0))
    (do-selectable-cells-of-table (cell table)
      (incff count))
    count))

(defun next-selectable-cell-of-table (current-cell table)
  (block search
    (let (prev)
      (do-selectable-cells-of-table (cell table)
        (when (eq prev current-cell)
          (prepare-table-cell cell table)
          (return-from search cell))
        (setq prev cell)))))

(defun previous-selectable-cell-of-table (current-cell table)
  (block search
    (let (prev)
      (do-selectable-cells-of-table (cell table)
        (when (eq cell current-cell)
          (prepare-table-cell prev table)
          (return-from search prev))
        (setq prev cell)))))


;;; The function `normal-sort-of-table-p' excludes graphs, so that TAB does not
;;; try to descend to the graph-grid. It is intended to include only tables
;;; which consist of an array of text-cells or icon-cells, and may need some
;;; further work.

(defun normal-sort-of-table-p (thing)
  (and (framep thing)
       (table-p thing)
       (not (graph-p thing))))

;;; The function `one-element-table-p' is true if table contains exactly one
;;; selectable cell.

(defun one-element-table-p (table)
  (let ((count 0))
    (block search
      (do-selectable-cells-of-table (cell table)
        (incff count)
        (when (>=f count 2)
          (return-from search))))
    (=f count 1)))

(defun next-selectable-thing-on-workspace (workspace current?)
  ;; TODO: Generics on workspace: first/last/next/prev-selectable
  (cond ((and (null current?)                ; Special case for attribute tables workspaces:
                                        ; skip the table itself.
              (attribute-table-workspace-p workspace))
         (let* ((table (first-subblock workspace))
                (cell? (first-selectable-cell-of-table? table)))
           (prepare-table-cell cell? table)))

        ((normal-sort-of-table-p current?) ; From "normal" table, descend into its cells.
         (cond ((one-element-table-p current?) ; Don't descend into one-element tables.
                (next-selectable-block-on-workspace workspace current?))
               (t
                (let ((cell? (first-selectable-cell-of-table? current?)))
                  (cond (cell?
                         (prepare-table-cell cell? current?))
                        (t
                         (next-selectable-block-on-workspace workspace current?)))))))
        ((cell-of-table-p current?)        ; From a cell, next cell or next block
         (or (next-selectable-cell-of-table current? (get-table-for-cell current?))
             (next-selectable-block-on-workspace workspace (get-table-for-cell current?))))
        (t                                ; Otherwise, next block
         (next-selectable-block-on-workspace workspace current?))))

(defun previous-selectable-thing-on-workspace (workspace current?)
  (cond ((cell-of-table-p current?)
         (let ((table (get-table-for-cell current?)))
           (or (previous-selectable-cell-of-table current? table)
               table)))
        (t
         (let ((block (previous-selectable-block-on-workspace workspace current?)))
           (cond ((not (normal-sort-of-table-p block))
                  block)
                 ((one-element-table-p block)
                  block)
                 (t
                  (let ((cell? (last-selectable-cell-of-table? block)))
                    (cond (cell?
                           (prepare-table-cell cell? block))
                          (t
                           block)))))))))

(define-ui-command select-next-item (selected-image-plane g2-window)
  (let* ((current? (primary-selection-on-image-plane selected-image-plane))
         (selected-item? (next-selectable-thing-on-workspace
                          (workspace-on-image-plane? selected-image-plane)
                          current?)))
    (deselect-all-things selected-image-plane)
    (select-thing selected-item? selected-image-plane)
    (update-att-tables selected-item? g2-window)))

(define-ui-command select-previous-item (selected-image-plane g2-window)
  (let* ((current? (primary-selection-on-image-plane selected-image-plane))
         (selected-item? (previous-selectable-thing-on-workspace
                          (workspace-on-image-plane? selected-image-plane)
                          current?)))
    (deselect-all-things selected-image-plane)
    (select-thing selected-item? selected-image-plane)
    (update-att-tables selected-item? g2-window)))

(defun next-selectable-in-list (current? list)
  (or (and current?
           (loop for next in (cdr (memq current? list))
                 when (selectable-thing-p next)
                   return next))
      (loop for next in list
            when (selectable-thing-p next)
              return next)))


(defun ok-to-delete-thing-p (thing)
  (cond ((framep thing)
         (item-may-be-deleted-by-user thing))
        ((connection-p thing)
         (ok-to-delete-connection-p thing))))


;;; The function `delete-selection' asks for confirmation first.  It will need
;;; to ignore things which are selectable but not deletable (namely, text cells).

(define-ui-command (delete-selection :name delete) ((image-plane selected-image-plane))
  (when (image-plane-selection-non-empty-p image-plane)
    (let (blocks-and-connections)
      (do-selection-things (thing (image-plane-current-selection image-plane))
        (when (ok-to-delete-thing-p thing)
          (dragging-push thing blocks-and-connections)))
      (when blocks-and-connections
        (let* ((n (length blocks-and-connections))
               (block-or-connection (car blocks-and-connections))
               (caption
                 (cond ((=f n 2)
                        (tformat-wide-string "Delete both selected items?"))
                       ((>f n 2)
                        (tformat-wide-string "Delete all ~d selected items?" n))
                       ((framep block-or-connection)
                        (dialog-message-string-for-delete-block block-or-connection))
                       ((connection-frame-of-connection? block-or-connection)
                        (dialog-message-string-for-delete-block
                          (connection-frame-of-connection? block-or-connection)))
                       (t
                        (tformat-wide-string "Delete this ~a?"
                                             (connection-frame-or-class block-or-connection))))))
          ;; enter-dialog owns the caption string.
          (enter-dialog
            caption nil nil
            'delete-selection-upon-confirmation
            (slot-value-list blocks-and-connections
                             (copy-frame-serial-number (current-frame-serial-number)))
            'reclaim-dragging-list-function
            (slot-value-list blocks-and-connections)))))))
;; TODO: Maybe delete selected workspace


(defun delete-selection-upon-confirmation (blocks-and-connections reference-serial-number)
  (loop with junction-blocks-not-to-be-deleted = blocks-and-connections        ; Special variable
        with workspace? = (and (car blocks-and-connections)
                               (get-workspace-of-thing-if-any (car blocks-and-connections)))
        for block-or-connection in blocks-and-connections
        doing
    (cond ((framep block-or-connection)
           (delete-frame-after-checking-serial-number block-or-connection reference-serial-number))
          ((connection-p block-or-connection)
           (unless (thing-has-been-reprocessed-p block-or-connection reference-serial-number)
             (delete-connection-to-stub block-or-connection))))
        finally
          (when workspace?
            (invoke-workspace-invalidation-handler-if-any
              workspace? 'delete))
          (reclaim-frame-serial-number reference-serial-number))
  (reclaim-dragging-list-function blocks-and-connections))

(def-hash-table blocks-hash
    :hash-function-or-macro frame-hash-function)

(defun make-blocks-hash-table ()
  (make-blocks-hash))
  
(defun reclaim-blocks-hash-table (table)
  (reclaim-blocks-hash table))
    
(defun get-block-from-table (block table)
  (get-blocks-hash block table))

(defun push-block-to-table (block table)
  (setf (get-blocks-hash block table) block))

(defun add-unique-to-dragging-list (item list-of-items hash-for-list)
  (if (not (get-block-from-table item hash-for-list))
    (progn
      (push-block-to-table item hash-for-list)
      (dragging-cons item list-of-items))
    list-of-items))

;;; The function `compute-filtered-blocks-from-selection' returns a newly consed
;;; dragging list of those things in the selection which satisfy filter on
;;; blocks. A connection or text cell satifies the filter if its ends or table
;;; does. Finally, if both a block and one of its subblocks would be in the
;;; list, we remove the subblocks, and use the parent.

(defun compute-filtered-blocks-from-selection (selection filter)
  (let ((blocks ())
        (selection-hash-table (make-blocks-hash-table))
        (blocks-hash-table (make-blocks-hash-table)))
    (when selection
      (loop for item in (%secondary-selection selection) do
        (when (is-block-p item)
          (push-block-to-table item selection-hash-table)))
      (do-selection-things (thing selection)
        (when (text-cell-p thing)
          (setq thing (get-table-for-cell thing)))
        (cond ((framep thing)
               (when (block-p thing)
                 (let* ((superblock? (superblock? thing))
                        (block
                         (cond ((null superblock?)
                                thing)
                               ((or (eq superblock? (%primary-selection selection))
                                    (get-block-from-table superblock? selection-hash-table))
                                superblock?)
                               (t
                                thing))))
                   (when (funcall filter block)
                     (setq blocks (add-unique-to-dragging-list block blocks blocks-hash-table))))))
              ((connection-p thing)
               (when (and (input-end-object thing)
                          (funcall filter (input-end-object thing))
                          (output-end-object thing)
                          (funcall filter (output-end-object thing)))
                 (setq blocks (add-unique-to-dragging-list (input-end-object thing) blocks blocks-hash-table))
                 (setq blocks (add-unique-to-dragging-list (output-end-object thing) blocks blocks-hash-table)))))))
    (reclaim-blocks-hash-table selection-hash-table)
    (reclaim-blocks-hash-table blocks-hash-table)
    blocks))

(defun compute-blocks-from-selection (selection)
  (compute-filtered-blocks-from-selection selection #'identity))

(defun compute-blocks-to-move-from-selection (selection)
  (compute-filtered-blocks-from-selection selection #'drag-block-permitted-p))

(defun compute-blocks-to-clone-from-selection (selection)
  (compute-filtered-blocks-from-selection selection #'block-clonable-via-ui-command-p))

(defun compute-blocks-to-transfer-from-selection (selection)
  (compute-filtered-blocks-from-selection selection #'block-transferable-via-ui-command-p))


;;; The function `move-current-selection' moves blocks and connections in
;;; current selection by dx,dy in workspace coordinates, subject to movement
;;; contraints imposed by item configurations.  Non-block non-connection
;;; selected things are ignored.  Returns non-NIL if it did anything.

(defun move-current-selection (dx dy)
  (let ((blocks (compute-blocks-to-move-from-selection (current-selection)))
        (did-something nil))
    (when blocks
      (let ((workspace? (get-workspace-if-any (car blocks))))
        (when workspace?
          (multiple-value-bind
              (outline-for-blocks-to-drag external-connections)
              (make-outline-for-blocks-to-drag blocks nil)
            (multiple-value-bind (ddx ddy)
                (compute-restricted-motion-for-blocks
                  workspace? blocks outline-for-blocks-to-drag external-connections dx dy)
              (when (or (/=f ddx 0) (/=f ddy 0))
                (shift-blocks-with-their-external-connections
                  outline-for-blocks-to-drag external-connections
                  nil workspace? ddx ddy nil t)
                (setq did-something t))))))
      (when did-something
        (trigger-user-icon-movement-rules-for-blocks blocks))
      (reclaim-dragging-list blocks)
      did-something)))

;;; The function `compute-restricted-motion-for-blocks' computes a new dx, dy
;;; which satisfy restrictions.

(defun compute-restricted-motion-for-blocks
    (workspace blocks outline external-connections? dx dy)
  (multiple-value-bind (x-step? y-step? left? top? right? bottom?)
      (compute-movement-contraints workspace blocks outline external-connections?)
    ;; If a grid is active, always move by one grid square.  This makes arrow
    ;; and control-arrow equivalent, which is too bad.
    (when (and x-step? (/=f dx 0))
      (setq dx (if (> dx 0) (absf x-step?) (-f (absf x-step?)))))
    (when (and y-step? (/=f dy 0))
      (setq dy (if (> dy 0) (absf y-step?) (-f (absf y-step?)))))
    (let* ((first-block (first blocks))
           (proposed-x (+f dx (left-edge-of-block first-block)))
           (proposed-y (+f dy (top-edge-of-block first-block)))
           (delta-x-in-workspace
             (-w (restrict-coordinate-value proposed-x x-step? left? right?)
                 (left-edge-of-block first-block)))
           (delta-y-in-workspace
             (-w (restrict-coordinate-value proposed-y y-step? top? bottom?)
                 (top-edge-of-block first-block))))
      (values delta-x-in-workspace delta-y-in-workspace))))

;;; The function `move-selection-permitted-p' was added to prevent moving
;;; logbook messages.  Probably fixes other stuff.  I think that do want
;;; messages to be selectable, but if not, this predicate may no longer be
;;; needed.

(defun move-selection-permitted-p ()
  (let ((workspace? (selected-workspace)))
    (and workspace? (kb-workspace-p workspace?))))

;
(defun selection-is-text-cell-p ()
  (and (text-cell-p (primary-selection current-workstation))
       (null (secondary-selection current-workstation))))

(define-ui-command move-selection-up (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-y-scrollbar-p selected-image-plane)
             (line-up mouse-pointer)
             (start-ui-command 'shift-up-ten-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection 0 -10))))

(define-ui-command move-selection-down (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-y-scrollbar-p selected-image-plane)
             (line-down mouse-pointer)
             (start-ui-command 'shift-down-ten-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection 0 +10))))

(define-ui-command move-selection-left (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-x-scrollbar-p selected-image-plane)
             (line-left mouse-pointer)
             (start-ui-command 'shift-left-ten-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection -10 0))))

(define-ui-command move-selection-right (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-x-scrollbar-p selected-image-plane)
             (line-right mouse-pointer)
             (start-ui-command 'shift-right-ten-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection +10 0))))

;; TODO: Remove this hard-wired static inheritance of event handlers.

(define-ui-command nudge-selection-up (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-y-scrollbar-p selected-image-plane)
             (raster-up mouse-pointer)
             (start-ui-command 'shift-up-one-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection 0 -1))))

(define-ui-command nudge-selection-down (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-y-scrollbar-p selected-image-plane)
             (raster-down mouse-pointer)
             (start-ui-command 'shift-down-one-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection 0 +1))))

(define-ui-command nudge-selection-left (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-x-scrollbar-p selected-image-plane)
             (raster-left mouse-pointer)
             (start-ui-command 'shift-left-one-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection -1 0))))

(define-ui-command nudge-selection-right (mouse-pointer selected-image-plane)
  (cond ((null (current-selection))
         (if (image-plane-has-x-scrollbar-p selected-image-plane)
             (raster-right mouse-pointer)
             (start-ui-command 'shift-right-one-percent mouse-pointer)))
        ((move-selection-permitted-p)
         (move-current-selection +1 0))))

;; When these are called from the menu bar the mouse-pointer is already correct:
;; it is the selection mouse pointer. However, when we are called from the
;; keyboard it's the current mouse position mouse pointer. Since we want the
;; selection mouse pointer in all cases, we have to resynthesize ourselves.
;; This is something to clean up for 7.0 beta.


;;; The function `run-focus-or-selection-image-plane-command' runs an
;;; image-plane scaling command which acts on either a single-workspace-view
;;; image-plane or the selected image-plane, depending on the mode we are in.
;;; Single-workspace-view scaling always happens around the center of the
;;; window, while selected workspace scaling happens around the center of the
;;; selected item on the workspace, if any, or else the center of the workspace.

(defun run-focus-or-selection-image-plane-command
    (command-name workstation focus-image-plane? selected-image-plane?)
  (cond (focus-image-plane?
         (handle-image-plane-event command-name
                                   focus-image-plane?
                                   (midline-x-of-pane focus-image-plane?)
                                   (midline-y-of-pane focus-image-plane?)))
        (selected-image-plane?
         (run-ui-command-on-selection command-name workstation))))

(define-ui-command zoom-in (workstation &optional selected-image-plane)
  (when selected-image-plane
    (run-focus-or-selection-image-plane-command
      'twenty-percent-bigger workstation nil selected-image-plane)))

(define-ui-command zoom-out (workstation &optional selected-image-plane)
  (when selected-image-plane
    (run-focus-or-selection-image-plane-command
      'twenty-percent-smaller workstation nil selected-image-plane)))

(define-ui-command (selection-full-scale :name full-scale)
    (workstation &optional selected-image-plane)
  (when selected-image-plane
    (run-focus-or-selection-image-plane-command
      'full-scale workstation nil selected-image-plane)))


;; Note that when running in multiwindow mode on Windows, Control+TAB, etc move
;; between MDI children, and we never see those keystrokes.

(define-ui-command select-next-workspace (selected-image-plane)
  (let ((image-plane? (next-selectable-image-plane selected-image-plane)))
    (when image-plane?
      (lower-image-plane-to-bottom selected-image-plane)
      (select-and-raise-image-plane image-plane?))))

(define-ui-command select-previous-workspace (selected-image-plane)
  (let ((image-plane? (previous-selectable-image-plane selected-image-plane)))
    (when image-plane?
      (select-and-raise-image-plane image-plane?))))


(define-ui-command hide-selected-workspace (selected-image-plane)
  (delete-image-plane selected-image-plane))

;; We don't check workspace-can-be-hidden? here because that prohibits hiding
;; unnamed temporary workspaces (except logbook pages), which is what we most
;; want to hide!


;;;; NMS Helper Functions


;;; These are intermediate level functions for use by G2 internally to manage
;;; the default G2 menu-bar.  They do not signal stack errors or mess with
;;; evaluation values.  Also, they will create the NMS data structures even if
;;; NMS is not supported on a given window.  This is mainly for testing on the
;;; local window.

;;; Note that we assume that supported => ICP.


(defparameter nms-allowed-menu-types '(popup pop-up menubar menu-bar parameter toolbar))


;;; The kb-specific-variable `nms-reclaim-hook' exists just so that we can
;;; notice a clear-kb happening and reset all NMS menus.

(def-kb-specific-variable nms-reclaim-hook commands2 nil nil nms-global-reset-hook)

;;; The function `nms-global-reset-hook' is called upon Clear KB via
;;; reclaim-values-of-kb-specific-variables.

(defun nms-global-reset-hook (value)
  (declare (ignore value))
  (nms-reset-globally t))                ; Hard reset


;;; The function `nms-reset-globally' does a NMS reset on all connected
;;; workstations.

;;; A hard-reset deletes all menus and items. A soft reset deletes only menus
;;; and items created by the user at KB level (via the NMS system procedures).

(defun nms-reset-globally (hard-reset-p)
  (loop for workstation in workstations-in-service doing
    (nms-reset-1 (window-for-workstation workstation) hard-reset-p)))


(defparameter nms-empty-string #w"")

(defun nms-copy-string (string?)
  (when string?
    (copy-as-wide-string string?)))

(defun nms-key-valid-p (menu-item)
  (let ((key? (nms-menu-item-key menu-item))
        (fsn? (nms-menu-item-fsn menu-item)))
    (or (null fsn?)                        ; Means key was not a frame at all.
        (frame-has-not-been-reprocessed-p key? fsn?))))


;;; The function `nms-create-menu-1' creates an NMS menu on window and returns
;;; the handle, or NIL in case of error.

(defun nms-create-menu-1 (gensym-window type &optional label? callback?)
  (assert-for-development (memq type nms-allowed-menu-types))
  (let ((nms-menu? (nms-allocate-menu gensym-window type)))
    (when nms-menu?
      (setf (nms-menu-label nms-menu?) (nms-copy-string label?)
            (nms-menu-callback nms-menu?) callback?)
      (when (nms-supported-on-gensym-window-p gensym-window)
        ;; TODO: Assuming that supported => ICP
        (with-icp-window (gensym-window)
          (send-icp-nms-create-menu gensym-window
                                    (nms-menu-handle nms-menu?)
                                    (nms-menu-type nms-menu?)
                                    (nms-menu-flags nms-menu?))))
      nms-menu?)))


(defun nms-delete-menu-1 (gensym-window menu recursive-p)
  (let ((menu-handle (nms-menu-handle menu)))
    (nms-delete-menu-locally gensym-window menu recursive-p)
    (when (nms-supported-on-gensym-window-p gensym-window)
      (with-icp-window (gensym-window)
        (send-icp-nms-delete-menu gensym-window menu-handle (if recursive-p 1 0))))))


;;; The function `nms-delete-menu-contents-1' deletes all of menu's items, and
;;; their submenus, recursively, leaving menu alive but an empty husk with no
;;; items.

(defun nms-delete-menu-contents-1 (gensym-window menu)
  (let ((menu-handle (nms-menu-handle menu)))
    (nms-delete-menu-locally gensym-window menu t t) ; recurse-p, keep-toplevel-menu-p
    (when (nms-supported-on-gensym-window-p gensym-window)
      (with-icp-window (gensym-window)
        ;; options==3 => keep-toplevel-menu-p, recurse-p
        (send-icp-nms-delete-menu gensym-window menu-handle 3)))))

(defun nms-dismiss-1 (gensym-window)
  (when (nms-supported-on-gensym-window-p gensym-window)
    (with-icp-window (gensym-window)
      (send-icp-nms-dismiss gensym-window))))

;;; The function 'nms-set-iconsize-1' changes the icon size of NMS menu bar and tool bar

(defun nms-set-iconsize-1 (gensym-window iconsize)
  (with-icp-window (gensym-window)
    (send-icp-nms-set-iconsize iconsize)))

;;; The function `nms-reset-1' deletes NMS menus and menu items on given window.
;;; A hard-reset deletes all menus and items. A soft reset deletes only menus
;;; and items created by the user at KB level (via the NMS system procedures).

(defun nms-reset-1 (gensym-window hard-reset-p)
  ;; We used to reclaim native-icons here, from when they were used only by
  ;; native menus. But now that they are used by other things, we can't,
  ;; because, for example, this function is called from the sysproc
  ;; g2-nms-reset, which specifically resets only native menus.

  ;; Moreover, since this is called during clear KB from
  ;; reclaim-values-of-kb-specific-variables, and the native-icon tables include
  ;; item-references, we would stumble across the same problem encountered by
  ;; `ui-callbacks', that all item-references get rudely reclaimed during clear
  ;; KB. See the comments near ui-callbacks.

  (nms-reset-locally gensym-window hard-reset-p)
  (when (nms-supported-on-gensym-window-p gensym-window)
    (with-icp-window (gensym-window)
      (send-icp-nms-reset gensym-window (if hard-reset-p 1 0)))))


(defun nms-virtual-item-p (label)
  (memq label '(break break-with-bar right-justify)))


;;; The function `nms-create-menu-item-1' creates an NMS menu item.  Label is a
;;; string, or, one of the symbols BREAK, BREAK-WITH-BAR, SEPARATOR,
;;; RIGHT-JUSTIFY.  It returns NIL in the case of allocation failure, or, for
;;; "virtual" items like break and right-justify, which just set flags in the
;;; following item.

(defun nms-create-menu-item-1 (gensym-window menu label key help flags command)
  (cond ((nms-virtual-item-p label)
         ;; These influence the next item added to menu.  So save the flags in
         ;; the menu's flags slot.
         (nms-set-bit menu
                      (case label
                        (break mf-menubreak)
                        (break-with-bar mf-menubarbreak)
                        (right-justify mf-rightjustify)
                        (t 0))
                      t)
         nil)
        (t
         (let ((item (nms-allocate-menu-item gensym-window)))
           (when item
             (let* ((label-string? (if (text-string-p label) label nil))
                    (new-flags (logiorf (nms-menu-item-flags item)
                                        flags
                                        (case label
                                          (separator mf-separator)
                                          (break mf-menubreak)
                                          (break-with-bar mf-menubarbreak)
                                          (right-justify mf-rightjustify)
                                          (t 0)))))
               (setf (nms-menu-item-label item) (nms-copy-string label-string?)
                     (nms-menu-item-help item) (nms-copy-string help)
                     (nms-menu-item-flags item) new-flags
                     (nms-menu-item-key item) (copy-if-text-string key)
                     (nms-menu-item-fsn item) (if (framep key)
                                                  (copy-frame-serial-number
                                                    (frame-serial-number key)))
                     (nms-menu-item-command item) command)
               item))))))


;;; The function `nms-append-locally' takes care of propagating the influence
;;; bits from menu to item, and creating the parent/child links.

(defun nms-append-locally (gensym-window menu item)
  (declare (ignore gensym-window))
  (let* ((influence-bits (logiorf mf-menubreak mf-menubarbreak mf-rightjustify))
         (menu-flags (logandf influence-bits (nms-menu-flags menu))))

    (nms-set-bit item menu-flags t)
    (nms-set-bit menu influence-bits nil)

    (setf (nms-menu-item-parent item) (nms-menu-handle menu)
          (nms-menu-item-position item) (nms-menu-item-count menu))
    (gensym-push item (nms-menu-items menu))
    (incff (nms-menu-item-count menu))
    item))

;; command can be a symbol (names a UI command), an fixnum (stock command ID),
;; T, (means item is value for a parameter), or NIL.  The ICP routine, however,
;; only takes an unsigned-integer or nil for the ID.

(defun nms-append-item-1 (gensym-window menu label &optional key help command (flags 0))
  (let ((item (nms-create-menu-item-1 gensym-window menu label key help flags command)))
    (when item
      (nms-append-locally gensym-window menu item)
      (when (nms-supported-on-gensym-window-p gensym-window)
        ;; If menu-item is a stock command, we need to send over it's ID as well
        ;; as its handle (they are not related as usual).
        (with-icp-window (gensym-window)
          (send-icp-nms-append-menu-item gensym-window
                                         (nms-menu-handle menu)
                                         (nms-menu-item-handle item)
                                         (or (nms-menu-item-label item) nms-empty-string)
                                         (or (nms-menu-item-help item) nms-empty-string)
                                         (nms-menu-item-flags item)
                                         (nms-menu-item-command-id item))))
      item)))


;;; The function `nms-append-special-1' appends an owner-drawn menu item, with
;;; custom fg and bg colors, possibly later a custom icon.

(defun nms-append-special-1 (gensym-window menu label key help flags command fg bg)
  (let ((item (nms-create-menu-item-1 gensym-window menu label key help flags command)))
    (when item
      (nms-append-locally gensym-window menu item)
      (when (nms-supported-on-gensym-window-p gensym-window)
        (with-icp-window (gensym-window)
          (on-window-without-drawing (gensym-window) ; Just for map-to-color-value
            (send-icp-nms-append-special gensym-window
                                         (nms-menu-handle menu)
                                         (nms-menu-item-handle item)
                                         (or (nms-menu-item-label item) nms-empty-string)
                                         (or (nms-menu-item-help item) nms-empty-string)
                                         (logiorf (nms-menu-item-flags item)
                                                  mf-ownerdraw)
                                         (nms-menu-item-command-id item)
                                         (map-to-color-value fg)
                                         (map-to-color-value bg)))))
      item)))


(defun nms-append-submenu-1 (gensym-window menu label submenu &optional help? (flags 0))
  (setf-text (nms-menu-label submenu) (nms-copy-string label))
  (setf-text (nms-menu-help submenu) (nms-copy-string help?))
  (nms-append-locally gensym-window menu submenu)
  (setf (nms-menu-flags submenu) (logiorf mf-popup flags (nms-menu-flags submenu)))
  (when (nms-supported-on-gensym-window-p gensym-window)
    (with-icp-window (gensym-window)
      (send-icp-nms-append-menu-item gensym-window
                                     (nms-menu-handle menu)
                                     (nms-menu-handle submenu)
                                     (or (nms-menu-label submenu) nms-empty-string)
                                     (or (nms-menu-help submenu) nms-empty-string)
                                     (nms-menu-flags submenu)
                                nil))
    submenu))


(defun nms-set-key-1 (gensym-window item new-key)
  (declare (ignore gensym-window))
  (nms-reclaim-key item)
  (setf (nms-menu-item-key item) (copy-if-text-string new-key)
        (nms-menu-item-fsn item) (copy-frame-serial-number
                                   (cond ((framep new-key)
                                          (frame-serial-number new-key))
                                         ((or (evaluation-structure-p new-key)
                                              (evaluation-sequence-p new-key))
                                          (current-frame-serial-number))))))


;;; The function `nms-set-text-1' can set either the label text or the help text
;;; for a menu item.  The old text is reclaimed.  We must know the menu in order
;;; to set the label text.  The menu is not strictly needed to set the help
;;; text.

(defun nms-set-text-1 (gensym-window menu item which new-text)
  (case which
    (label
     (setf-text (nms-menu-item-label item) new-text))
    (help
     (setf-text (nms-menu-item-help item) new-text)))
  (when (nms-supported-on-gensym-window-p gensym-window)
    (let ((plist (icp-list which new-text)))
      (with-icp-window (gensym-window)
        (send-icp-nms-modify-menu-item gensym-window
                                       (nms-menu-handle menu)
                                       (nms-menu-item-handle item)
                                       plist))
      (reclaim-icp-list plist))))


;;; The function `nms-set-icon-1' uses the native icons facility to create an
;;; icon on the remote TW, if possible, and add it to the given NMS menu item.

(defun nms-set-icon-1 (gensym-window menu submenu-or-item icon-designation?)
  (unless (eql icon-designation? (nms-menu-item-icon submenu-or-item))
    (setf (nms-menu-item-icon submenu-or-item) icon-designation?)
    (when (native-icons-p gensym-window)
      (with-icp-window (gensym-window)        ; TODO: Assuming ICP window
        (let ((handle? (send-native-icon gensym-window icon-designation?)))
          (when handle?
            (let ((plist (icp-list 'icon handle?)))
              (send-icp-nms-modify-menu-item gensym-window
                                             (nms-menu-handle menu)
                                             (nms-menu-item-handle submenu-or-item)
                                             plist)
              (reclaim-icp-list plist))))))))


;;; The function `nms-set-colors-1' sets the fg and bg colors of item.  NIL
;;; means the default color.

(defun nms-set-colors-1 (gensym-window menu item fg? bg?)
  (unless (and (eq fg? (nms-menu-item-fg item))
               (eq bg? (nms-menu-item-bg item)))
    (setf (nms-menu-item-fg item) fg?
          (nms-menu-item-bg item) bg?)
    (when (nms-supported-on-gensym-window-p gensym-window)
      (on-window-without-drawing (gensym-window) ; Just for map-to-color-value
        (with-icp-window (gensym-window)
          (let ((plist (icp-list 'foreground (if fg? (map-to-color-value fg?) -1)
                                 'background (if bg? (map-to-color-value bg?) -1))))
            (send-icp-nms-modify-menu-item gensym-window
                                           (nms-menu-handle menu)
                                           (nms-menu-item-handle item)
                                           plist)
            (reclaim-icp-list plist)))))))

;;; The function `nms-set-menu-bar-1' sets the menu bar on window to handle.  A
;;; handle of -1 means to hide the current menu bar. A handle of 0 means to
;;; change to the "unconnected" or "not logged in" TW menu bar.

(defun nms-set-menu-bar-1 (gensym-window handle)
  ;; Maintain our notion of the current menu-bar, unless we are just hiding it.
  (unless (=f handle -1)
    (setf (nms-current-menu-bar? gensym-window) handle))
  (when (nms-menu-bars-supported-p gensym-window)
    (with-icp-window (gensym-window)
      (send-icp-nms-set-menu-bar gensym-window handle))))

(defmacro do-nms-windows ((window) &body body)
  `(loop for workstation in workstations-in-service
         as ,window = (window-for-workstation workstation)
         doing
     (when (and (nms-supported-on-gensym-window-p ,window)
                (eq (workstation-login-state workstation) 'logged-in))
       ;; If we are not in a for-workstation context
       ;; (servicing-workstation? is nil), or not in the right one,
       ;; set one up for the workstation we're visiting.  Some
       ;; function involved here, e.g., selection-not-enabled-p,
       ;; may be called and expect to be able to fetch
       ;; (current-window) based on the for-workstation
       ;; bindings. (MHD 7/29/03)
       (if (and servicing-workstation?
                (eq current-workstation workstation))
           (progn ,@body)
           (for-workstation (workstation)
             ,@body)))))


;;;; Icon Designations


;;; An `icon-designation' is either a symbol, an item, or an item-reference, and
;;; designates the icon for the named class, if a symbol, else the icon of the
;;; item.

(def-concept icon-designation)

(defun icon-designation-p (thing)
  (or (symbolp thing)
      (evaluation-item-reference-p thing)
      (framep thing)))

(defun copy-icon-designation (icon-designation)
  (cond ((framep icon-designation)
         (get-reference-to-item-if-item icon-designation))
        ((evaluation-item-reference-p icon-designation)
         (copy-evaluation-item-reference icon-designation))
        (t
         icon-designation)))

(defun reclaim-icon-designation (icon-designation)
  (reclaim-if-evaluation-item-reference icon-designation))

(defun hash-icon-designation (icon-designation-or-hash)
  (cond ((fixnump icon-designation-or-hash)
         icon-designation-or-hash)
        ((symbolp icon-designation-or-hash)
         (sxhash-symbol icon-designation-or-hash))
        ((evaluation-item-reference-p icon-designation-or-hash)
         (hash-item-reference icon-designation-or-hash))
        ((framep icon-designation-or-hash)
         (hash-item-reference (uuid icon-designation-or-hash)))
        (t
         #+development
         (cerror "Return 0" "Invalid key in icon-designation-hash: ~s" icon-designation-or-hash)
         0)))

(defun valid-icon-designation-p (icon-designation)
  (cond ((null icon-designation)
         nil)
        ((symbolp icon-designation)
         (or (eq icon-designation 'none)
             (get-stock-native-icon-handle icon-designation)
             (iconic-class-name-p icon-designation)))
        ((evaluation-item-reference-p icon-designation)
         (let ((item? (evaluation-item-reference-referenced-item icon-designation)))
           (and item? (iconic-class-name-p (class item?)))))
        ((framep icon-designation)
         (iconic-class-name-p (class icon-designation)))))

;; cf class-definition-defines-user-editable-icon-class-p
(defun iconic-class-name-p (name)
  (let* ((class-description? (class-description name))
         (path (and class-description?
                    (class-inheritance-path class-description?))))
    (and class-description?
         (memq 'entity path)
         (icon-description-for-class-name? name) ; NOTE: This test alone may suffice.
         (not (memq 'connection path))
         (not (memq 'meter path)))))

(defun icon-description-for-class-name? (class-name)
  (let ((slotd? (slot-description-from-class class-name 'icon-description)))
    (and slotd? (slot-init-form slotd?))))


;;;; Stock Icons


(defconstant temp-icon-flag #.(ashf 1 21))        ; Keep in sync with ext/c/twpro.c
(defconstant stock-native-icon-flag #.(ashf 1 20))

(def-concept stock-icons)

;;; The parameter `stock-native-icons' is the ordered list of built-in icons we
;;; provide for use in native menus, toolbars, treeviews, etc. The order *MUST*
;;; match tw/c/toolbar.bmp.

(defparameter stock-native-icons
  '(gms-cut-icon                        ; See MSDN doc for TBADDBITMAP
    gms-copy-icon                        ; Names chosen to match gmsdemo.kb
    gms-paste-icon
    gms-undo-icon
    gms-redo-icon
    gms-delete-icon
    gms-file-icon                        ; file-new
    gms-folder-icon                        ; file-open (folder with little "opening" arrow)
    gms-save-icon                        ; file-save
    gms-print-preview-icon
    gms-properties-icon
    gms-help-icon
    gms-find-icon
    gms-replace-icon
    gms-print-icon
    ;; Icons we've added beyond the standard Windows set.
    gms-gensym-icon                        ; Called gmsd-demo-logo in gmsdemo
    gms-binoculars-icon
    gms-save-all-icon

    gms-closed-folder-icon                ; Default treeview icons (8.1b0) -fmw, 3/9/05
    gms-open-folder-icon
    gms-drop-document-icon                ; Document icon with little "dropping" arrow.
    gms-document-icon

    gms-funnel-icon                        ; Added -fmw, 3/17/05
    gms-toolbox-icon

    gms-small-up-triangle                ; Added -fmw, 8/16/06
    gms-small-down-triangle
    gms-small-3d-up-triangle
    gms-small-3d-down-triangle))

(defun get-stock-native-icon-handle (name)
  (let ((index? (position name stock-native-icons)))
    (if index?
        (logiorf index? stock-native-icon-flag))))


;;;; Native Icons

(def-concept native-icons)                ; Also in TELESTUBS


(defparameter next-temp-icon-handle 1000)        ; Separate handle space for temp icons

;;; The hash-table `native-icon-handle' maps an icon-designation (a stock icon
;;; name, iconic class name, or item-reference) to its handle. We keep one of
;;; these on each gensym-window.
;;; Really `native-icon-handle` contains hashes of icon-designation that are mapped
;;;  to icon-designation handle. It is because it needs to delete already reclaimed
;;;  icon-designations. To avoid re-setting data in collision of key hashes case
;;;  there are used '(hash key)' list as hash table key.

(defun make-icon-hash-key (icon-designation-or-key)
  (let* ((icon-designation-p? (icon-designation-p icon-designation-or-key))
         (key (copy-icon-designation
                (if icon-designation-p?
                    icon-designation-or-key
                    (second icon-designation-or-key))))
         (key-hash (if icon-designation-p?
                       (hash-icon-designation key)
                       (first icon-designation-or-key))))
    (gensym-list key-hash key)))

(defun reclaim-icon-hash-key (icon-hash-key)
  (when icon-hash-key
    (reclaim-icon-designation (second icon-hash-key))
    (reclaim-gensym-list icon-hash-key)))

(defun hash-icon-hash-key (icon-hash-key)
  (first icon-hash-key))

(defun eq-hash-icon-hash-key (icon-hash-key-1 icon-hash-key-2)
  (eq (second icon-hash-key-1) (second icon-hash-key-2)))

(def-hash-table native-icon-handle
    :accessor get-native-icon-handle-1
    :hash-function-or-macro hash-icon-hash-key
    :key-comparitor eq-hash-icon-hash-key
    :key-reclaimer reclaim-icon-hash-key
    :key-deleter delete-native-icon-handle-1)

(defun get-native-icon-handle (icon-designation-or-hash hash-table)
  (let ((key (make-icon-hash-key icon-designation-or-hash)))
    (prog1 (get-native-icon-handle-1 key hash-table)
      (reclaim-icon-hash-key key))))

(defun delete-native-icon-handle (icon-designation-or-hash hash-table)
  (let ((key (make-icon-hash-key icon-designation-or-hash)))
    (prog1 (delete-native-icon-handle-1 key hash-table)
      (reclaim-icon-hash-key key))))

(defun set-native-icon-handle (icon-designation hash-table value)
  (let ((key (make-icon-hash-key icon-designation)))
    (setf (get-native-icon-handle-1 key hash-table) value)))

(defun maximum-number-of-native-icons (gensym-window)
  (or (getf (window-parameters-plist gensym-window) 'native-icons-limit)
      (if (win32-window-p gensym-window) 4000)
      0))

;; Flag bits we cram into the hash table, set if the icon of given size has been
;; sent. These bits are seen only by G2, so they can be freely changed.
(defun-substitution-macro native-icon-size-flag (size)
  (case size
    (small #.(ashf 1 25))
    (large #.(ashf 1 26))
    (t 0)))

(defun native-icon-handle (icon-designation gensym-window)
  (and (native-icons-table? gensym-window)
       (get-native-icon-handle icon-designation (native-icons-table? gensym-window))))

;;; The function `find-native-icon' returns the icon handle if the given icon
;;; has been sent over to the given window. Second value is true if small icon
;;; sent, third value if large icon sent.

(defun find-native-icon (gensym-window icon-designation)
  (let ((handle? (native-icon-handle icon-designation gensym-window)))
    (when handle?
      (values
        (logandf handle? #xFFFFF)
        (/=f (logandf handle? (native-icon-size-flag 'small)) 0)
        (/=f (logandf handle? (native-icon-size-flag 'large)) 0)))))

;;; The function `update-native-icon' redraws the icon on window in the sizes
;;; that are already present. If none, does nothing.

(defun update-native-icon-on-window (gensym-window icon-designation)
  (multiple-value-bind (handle? small-p large-p)
      (find-native-icon gensym-window icon-designation)
    (when handle?
      (draw-native-icon gensym-window icon-designation handle? small-p large-p t))))

(defun note-native-icon-sent (gensym-window icon-designation size)
  (let ((handle? (native-icon-handle icon-designation gensym-window)))
    (when handle?
      (let ((new-handle (logiorf handle? (native-icon-size-flag size))))
        (unless (=f handle? new-handle)
          (set-native-icon-handle icon-designation
                                  (native-icons-table? gensym-window)
                                  new-handle))))
    (when (framep icon-designation)
      (setf (item-has-icon-views-p icon-designation) t))))


;;; The function `allocate-native-icon-handle' returns a new integer handle for
;;; a user-defined native icon, or NIL on failure. Stock icons do not call this.

(defun allocate-native-icon-handle (gensym-window icon-designation)
  (let* ((hash-table (or (native-icons-table? gensym-window)
                         (setf (native-icons-table? gensym-window)
                               (make-native-icon-handle))))
         (handle (or (gensym-pop (free-icon-handles gensym-window))
                     (prog1 (next-icon-handle gensym-window)
                       (incff (next-icon-handle gensym-window))))))
    (cond ((>=f handle (maximum-number-of-native-icons gensym-window))
           ;; TODO: "native icons" may not be in the user vocabulary.
           (notify-user
             "Exceeded maximum of ~D native icons on ~NF. Not adding ~NF."
             (maximum-number-of-native-icons gensym-window)
             (or (g2-window-for-gensym-window? gensym-window) "(no window)")
             icon-designation)
           nil)
          (t
           (set-native-icon-handle icon-designation hash-table handle)))))

(defun reclaim-native-icons-table (table?)
  (when table?
    (clear-native-icon-handle table?)
    (reclaim-native-icon-handle table?)))

(defun free-all-native-icon-handles-on-window (gensym-window)
  (let ((hash-table? (native-icons-table? gensym-window))
        (free-list? (free-icon-handles gensym-window)))
    (reclaim-native-icons-table hash-table?)
    (setf (native-icons-table? gensym-window) nil)
    (reclaim-gensym-list free-list?)
    (setf (free-icon-handles gensym-window) nil)
    (setf (next-icon-handle gensym-window) 0)))

(defun icon-description-for-class (class-name)
  ;; TODO: inheritance?
  (slot-init-form (slot-description-from-class class-name 'icon-description)))


;;; The function `send-native-icon' ensures that given TW has the named icon, of
;;; the given size, if possible, and returns the icon handle or NIL. Sizes can
;;; include SMALL or LARGE.

(defun send-native-icon (gensym-window icon-designation? &optional (sizes '(small)))
  (cond ((not (native-icons-p gensym-window))
         nil)
        ((or (null icon-designation?) (eq icon-designation? 'none))
         -1)
        ((not (valid-icon-designation-p icon-designation?))
         nil)
        ((get-stock-native-icon-handle icon-designation?))
        (t
         (multiple-value-bind (handle? small-present large-present)
             (find-native-icon gensym-window icon-designation?)
           (let ((need-small (and (not small-present) (memq 'small sizes)))
                 (need-large (and (not large-present) (memq 'large sizes))))
             (when (or need-small need-large)
               (unless handle?
                 (setq handle? (allocate-native-icon-handle gensym-window icon-designation?)))
               (when handle?
                 (draw-native-icon gensym-window icon-designation? handle? need-small need-large nil)))
             handle?)))))

;;; The function `send-native-bitmap' draws an arb size temp bitmap on the
;;; remote TW and returns the handle and resulting width, and height in pixels,
;;; or NIL for an invalid icon.

(defun send-native-bitmap (gensym-window icon-designation &optional width? height?)
  (cond ((not (native-icons-p gensym-window))
         nil)
        ((or (null icon-designation) (eq icon-designation 'none))
         -1)
        ((not (valid-icon-designation-p icon-designation))
         nil)
        ((get-stock-native-icon-handle icon-designation)
         (values (get-stock-native-icon-handle icon-designation) 16 16))
        (t
         (let* ((icon-description (if (framep icon-designation)
                                      (icon-description icon-designation)
                                      (icon-description-for-class icon-designation)))
                (width (or width?
                           (if (framep icon-designation)
                               (item-width icon-designation)
                               (1+f (width-of-icon icon-description)))))
                (height (or height?
                            (if (framep icon-description)
                                (item-height icon-designation)
                                (1+f (height-of-icon icon-description)))))
                (handle (prog1 (logiorf temp-icon-flag next-temp-icon-handle)
                          (incff next-temp-icon-handle))))
           (with-raw-window-transform-and-draw-area (gensym-window)
             (on-window-without-drawing (gensym-window)
               (setq current-drawing-transfer-mode :paint-infered-from-xor)
               (on-window-with-drawing (gensym-window)
                 (draw-native-icon-1 icon-designation handle width height 'fill))))
           (values handle width height)))))

;;; The function `draw-native-icon' unconditionally draws the given native icon
;;; on window, in the selected sizes. Optionally refreshes all users of the icon
;;; on the window.

(defun draw-native-icon (gensym-window icon-designation handle small-p large-p refresh-p)
  (with-raw-window-transform-and-draw-area (gensym-window)
    (on-window-without-drawing (gensym-window)
      ;; Force paint mode.
      (setq current-drawing-transfer-mode :paint-infered-from-xor)
      (on-window-with-drawing (gensym-window)
        (when small-p
          (draw-native-icon-1 icon-designation handle small-native-icon-size small-native-icon-size)
          (note-native-icon-sent gensym-window icon-designation 'small))
        (when large-p
          (draw-native-icon-1 icon-designation handle large-native-icon-size large-native-icon-size)
          (note-native-icon-sent gensym-window icon-designation 'large))
        (when refresh-p
          (refresh-native-icon gensym-window handle #xFF)))))

  ;; Thanks to rh, messages to reclaim ICP objects are queued and processed
  ;; later in a scheduler task. In particular, any reclaim-icon-renderings
  ;; induced by the above call.
  (flush-queued-reclaim-index-space-messages gensym-window))


;;; The function `draw-native-icon-1' is the guts of where we draw an icon to a
;;; Win32 ImageList on the current TW. We draw it twice, once to a color bitmap
;;; for the icon itself, and again to a monochrome bitmap for the mask. We do
;;; this needing neither an entity instance nor an image-plane.

(defun-allowing-unwind draw-native-icon-1 (icon-designation handle target-width target-height
                                                            &optional fill-p)
  (let* ((framep (framep icon-designation))
         (icon-description (if framep
                               (icon-description icon-designation)
                               (icon-description-for-class icon-designation)))
         (plist (if framep (icon-attributes-plist icon-designation)))
         ;; G2 lies about icon sizes.
         (icon-width (if framep (item-width icon-designation)
                         (width-of-icon icon-description)))
         (icon-height (if framep (item-height icon-designation)
                          (height-of-icon icon-description)))
         (src-left 0)
         (src-top 0)
         (src-right icon-width)
         (src-bottom icon-height)
         (dst-left 0)
         (dst-top 0)
         (dst-right target-width) 
         (dst-bottom target-height)
         (w target-width)         
         (h target-height)
         (white (color-difference (color-value-for-white) current-background-color-value)))

    ;; If icon is smaller than target, center it. Otherwise, scale to fit.
    (unless fill-p
      (when (<f icon-width target-width)
        (setq dst-left (halff (-f target-width icon-width))
              dst-right (+f dst-left icon-width)))

      (when (<f icon-height target-height)
        (setq dst-top (halff (-f target-height icon-height))
              dst-bottom (+f dst-top icon-height))))

    (when (or (=f src-left src-right)        ; This should never happen now.
              (=f src-top src-bottom))
      #+development (cerror "Ignore it" "Icon for ~s has size ~dx~d !"
                            icon-designation icon-width icon-height)
      (return-from draw-native-icon-1))

    (unwind-protect
         (with-rectangle-scaling (src-left src-top src-right src-bottom
                                           dst-left dst-top dst-right dst-bottom)
           ;; Draw icon to buffer in full color.
           (begin-drawing-to-icon-buffer current-window target-width target-height)
           (draw-solid-rectangle 0 0 w h white)
           (draw-icon-from-description icon-description plist 0 0 icon-width icon-height nil)
           (end-drawing-to-icon current-window)

           ;; Draw icon to mask in black&white.
           (begin-drawing-to-icon-mask current-window target-width target-height)
           (draw-solid-rectangle 0 0 w h white)
           (let* ((monochrome-color-description-plist
                    (make-monochrome-color-description-plist
                      (color-value-for-black)
                      (color-value-for-black)))
                  (current-color-map
                   (make-color-map (window-screen-depth current-window)
                                   monochrome-color-description-plist)))
             (draw-icon-from-description icon-description plist 0 0 icon-width icon-height nil)
             (reclaim-gensym-tree monochrome-color-description-plist)
             (reclaim-color-map current-color-map))
           (end-drawing-to-icon current-window)

           ;; Save icon to imagelist on TW.

           ;; TODO: This is where we are restricted to either 16x16 or 32x32
           ;; icons, unless we're drawing a temp icon (denoted by special bit
           ;; set in handle), which can be of any size.
           (save-native-icon current-window handle target-width target-height))

      ;; Ensure we are drawing to the real window again.
      (end-drawing-to-icon current-window))))

(defun valid-icon-designation-or-stack-error (icon-designation)
  (or (valid-icon-designation-p icon-designation)
      (ui-stack-error "~NF is an invalid icon designation. ~
                       It must be a stock icon name, G2 class name, or an item."
                      icon-designation)))

;;; The function `note-kb-reset-for-native-icons' clears out all native icons
;;; upon a KB reset.

;;; FIXME: Note that native icons in non-transient views (workspace views and
;;; the native logbook) will be left hanging. This is a bug to be fixed.

(defun note-kb-reset-for-native-icons ()
  (loop for workstation in workstations-in-service
        as gensym-window = (window-for-workstation workstation)
        doing
    (reset-native-icons-1 gensym-window)))

;;; The function `reset-native-icons-1' destroys all user-defined native icons
;;; on the given window. Since they may be in use by menus, call this only from
;;; nms-reset. Built-in (stock) native icons are not affected.

(defun reset-native-icons-1 (gensym-window)
  (free-all-native-icon-handles-on-window gensym-window) ; Clear hash table, etc.
  (when (native-icons-p gensym-window)
    (with-icp-window (gensym-window)
      (destroy-native-icons gensym-window))))


;;; The function `update-icon-views' updates all views on all windows of the
;;; given icon, which may be either a symbol naming a class which has changed,
;;; or an item whose icon has changed colors or orientation.

(defun update-icon-views (icon-designation)
  (loop for workstation in workstations-in-service
        as gensym-window = (window-for-workstation workstation)
        when (native-icons-p gensym-window)
          do (update-native-icon-on-window gensym-window icon-designation)))

;;; The window to use when making bitmaps for GSI
(defvar window-for-bitmap-for-gsi nil)

;;; Gets the "root" window. Currently it really makes sense only on Windows.
(def-gensym-c-function c-get-root-window
                       (:pointer "g2ext_get_root_window")
  ())

;;; Gets the window to use for making icon bitmaps for GSI.
;;; Because the "main" window (`system-window`) may be smaller than the icon,
;;; here we shall look for the "root" window, but only on Windows, because
;;; currently there is no "root" window on X11.
(defun get-window-for-bitmap-for-gsi ()
  (when (null window-for-bitmap-for-gsi)
    (setq window-for-bitmap-for-gsi 
          (if (windows-platform-p)
            (make-or-revise-window-per-native-window nil (c-get-root-window))
            system-window)))
  window-for-bitmap-for-gsi)

;;;; Get Icon Bitmap


;;; The function `g2-get-icon-bitmap-for-gsi' returns a bitmap for the icon of
;;; item, in the form of a G2 text string. Transparent areas of the icon are filled
;;; with the given background color, which is a 24-bit packed BGR integer.

;;; The returned text string is in a packed binary format not meant to be
;;; accessed directly by users, only by GSI.  Returned values are the string,
;;; width in pixels, height in pixels, and a format indicator, which is 0 for
;;; little-endian, 1 for big-endian.

;; We really want to use an unsigned-byte-vector type, so that we don't have to
;; worry about endianness, but GSI doesn't have one.

(defun-for-system-procedure g2-get-icon-bitmap-for-gsi ((item item) (background integer))
  (declare (values text integer integer integer))

  (unless (and (of-class-p item 'entity)
               (icon-description item))
    (ui-stack-error "~NF must be an item with an icon." item))

  (let* ((gensym-window (get-window-for-bitmap-for-gsi))
         (width (1+f (width-of-block item)))
         (height (1+f (height-of-block item)))
         (depth 24)                            ; The bitmap we return is always 24 bpp.
         (stride (bytes-per-line width depth))
         (nwords (*f height (ashf stride -1))))

    (when (>=f nwords maximum-length-for-user-text-strings)
      (ui-stack-error "The icon for ~NF is ~dx~d, which is too large." item width height))

    (when (or (=f width 0) (=f height 0))
      (ui-stack-error "The icon for ~NF has zero size." item))

    (let ((pixmap? (create-truecolor-pixmap gensym-window width height)))
      (unless pixmap?
        (ui-stack-error "Unable to create ~dx~dx~d bitmap." width height depth))
      (draw-item-on-pixmap gensym-window item pixmap? background)

      (let* ((string (make-wide-string nwords :initial-element #u0000))
             (status (c-x11-get-pixmap-bits (pixmap-pointer pixmap?)
                                            (pixmap-width pixmap?)
                                            (pixmap-height pixmap?)
                                            stride string))
             (big-endian-p (=f status 1)))  ; Sparc/Solaris, AIX, etc.
        (reclaim-pixmap pixmap?)
        (mark-wide-string-as-binary string) ; Makes GSI use gsi-unsigned-short-vector-type-tag
        (values string width height (if big-endian-p 1 0))))))

(defun draw-item-on-pixmap (gensym-window item pixmap background)
  (let (bg)
    (with-raw-window-transform-and-draw-area (gensym-window)
      (on-window-without-drawing (gensym-window)
        (setq current-drawing-transfer-mode :paint-infered-from-xor) ; Force paint mode.
        (on-window-with-drawing (gensym-window)
          (setq bg (if (symbolp background)
                       (map-to-color-value background)
                       background))        ; TODO: Convert BGR to window's pixel format.
          (draw-item-on-pixmap-1 item pixmap bg))))
    bg))

(defun-allowing-unwind draw-item-on-pixmap-1 (item pixmap bg)
  (unwind-protect
       (with-cached-transform (nil (normalized-scale)
                                   (normalized-scale)
                                   (-f (left-edge-of-block item))
                                   (-f (top-edge-of-block item)))
         (c-x11-draw-offscreen current-native-window? (pixmap-pointer pixmap) 1)
         (draw-solid-rectangle 0 0 (pixmap-width pixmap) (pixmap-height pixmap)
                               (color-difference bg current-background-color-value))
         (draw-icon-for-entity item))
    (c-x11-draw-offscreen current-native-window? 0 0)))

(defun create-truecolor-pixmap (gensym-window width height)
  (let* ((depth 24)                        ; TODO: Permit other truecolor visuals.
         (raster (c-x11-create-bigmap (native-window? gensym-window) width height depth)))
    (when (>=f raster 0)
      (make-pixmap width height depth raster))))

;; Bytes in a DWORD aligned DIB scanline.
(defun bytes-per-line (width depth)
  (ashf (ashf (+f (*f width depth) 31) -5) 2))

;;; The gensym-c-function `c-x11-get-pixmap-bits' copies the pixels in pixmap
;;; into buffer. Returns 1 if they were stored in big-endian order, 0 if
;;; little-endian, and -1 on error.

(def-gensym-c-function c-x11-get-pixmap-bits
    (:fixnum-int "g2ext_get_pixmap_bits")
  ((:pointer pixmap)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int stride)
   (:wide-string buffer)))


;; The following functions are mainly for testing, and are not documented for
;; users, as of 6/2/04.

#+development
(defun-for-system-procedure g2-get-pixel (string x y width)
  (prog1 (c-get-truecolor-pixel string x y (bytes-per-line width 24))
    ;; Ugh. Entire string (== entire bitmap) is copied on each call.
    (reclaim-evaluation-value string)))

#+development
(defun-for-system-procedure g2-get-standard-color (bgr)
  (car (find-nearest-color standard-gensym-color-alist
                           (logandf bgr #xFF)                 ; Red
                           (logandf (ashf bgr -8) #xFF)         ; Green
                           (logandf (ashf bgr -16) #xFF) ; Blue
                           nil)))

#+development
(def-gensym-c-function c-get-truecolor-pixel
    (:fixnum-int "g2ext_get_truecolor_pixel")
  ((:wide-string string)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int stride)))



;;;; NMS System Procedures



;; 0.9: First released version (G2 7.0r0)
;; 1.0: Dynamic menus (G2 7.1)
;; 1.1: Native icons  (G2 7.1)
;; 1.2: Native toolbars  (G2 8.0a1)
;; 1.3: Modify control, etc  (G2 8.0r1)
;; 1.4: DrawMenuBar added, etc (G2 8.1a0)
;; 1.5: Unposting callback added (G2 8.1b0)
;; 1.6: Tooltips and button-styles (G2 8.1r1)
;; 1.7: Popup menus in workspace views (G2 8.3r0)
(defparameter nms-version 1.7)

(defun nms-menu-bars-or-stack-error (gensym-window)
  (unless (nms-menu-bars-supported-p gensym-window)
    (ui-stack-error "NMS menu bars are not supported on embedded windows ~NF"
                    (g2-window-for-gensym-window? gensym-window))))

(defun nms-signal-allocation-error ()
  (ui-stack-error "Attempt to create more than ~D NMS menus and/or items."
                  nms-maximum-permitted-handle)
  nil)

(defun nms-supported-or-stack-error (gensym-window)
  (if (nms-supported-on-gensym-window-p gensym-window)
      t
      (ui-stack-error "NMS is not supported on window ~NF."
                      (g2-window-for-gensym-window? gensym-window))))

(defun nms-lookup-designation (gensym-window designation &optional type)
  (cond ((fixnump designation)
         (nms-lookup-handle gensym-window designation))
        ((wide-string-p designation)
         (nms-lookup-label gensym-window designation type))))

(defun nms-lookup-label (gensym-window label &optional type)
  (do-nms-items (mot gensym-window)
    (when (and (or (null type)
                   (eq type (nms-menu-type mot)))
               (and (nms-menu-label mot)
                    (string-equalw (nms-menu-label mot) label))) ; Case-indep
      (return-from nms-lookup-label mot))))

(defun nms-menu-or-stack-error (gensym-window designation)
  (let ((menu? (nms-lookup-designation gensym-window designation)))
    (if (and menu? (nms-menu-p menu?))
        menu?
        (ui-stack-error "The designation ~S does not refer to an NMS menu on window ~NF."
                        designation
                        (g2-window-for-gensym-window? gensym-window)))))

(defun nms-menu-item-or-stack-error (gensym-window designation)
  (let ((item? (nms-lookup-designation gensym-window designation)))
    (if (and item? (nms-menu-item-p item?))
        item?
        (ui-stack-error "The designation ~S does not refer to an NMS menu item on window ~NF."
                        designation
                        (g2-window-for-gensym-window? gensym-window)))))

(defun nms-menu-or-item-or-stack-error (gensym-window designation)
  (let ((menu-or-item? (nms-lookup-designation gensym-window designation)))
    (or menu-or-item?
        (ui-stack-error "The designation ~S does not refer to an NMS menu or item on window ~NF."
                        designation
                        (g2-window-for-gensym-window? gensym-window)))))

(defun nms-menu-item-parent-or-stack-error (gensym-window menu-or-item)
  (let ((parent? (nms-menu-item-parent menu-or-item)))
    (cond ((null parent?)
           (ui-stack-error
             "The NMS choice ~S must first be added to a menu before changing its attributes."
             (or (nms-menu-label menu-or-item)
                 (nms-menu-handle menu-or-item))))
          (t
           (nms-menu-or-stack-error gensym-window parent?)))))

(defun nms-permitted-key-or-stack-error (key)
  (unless (or (null key) (fixnump key) (symbolp key) (wide-string-p key)
              (evaluation-boolean-p key) ; EQ to truth or falsity (no need to reclaim)
              (framep key))
    (ui-stack-error
      "The key for a menu item must be an integer, a symbol, a string, false, true, or an item")))

(defun nms-callback-name-or-stack-error (callback)
  (cond ((null callback) nil)
        ((eq callback 'inherited) nil)
        ((eq callback 'none) nil)
        ((symbolp callback) callback)
        ((and (framep callback)
              (procedure-p callback))
         (get-primary-name-for-frame-if-any callback))
        (t
         (ui-stack-error "The callback argument ~NF must be either a symbol or a procedure."
                         callback))))


;;; The macro `with-nms-wrapper' wraps around the body of every NMS system
;;; procedure.  It checks that the supplied window exists and supports NMS,
;;; takes care of converting the return value to an evaluation-value, and
;;; reclaims selected arguments as evaluation-values.

(defmacro with-nms-wrapper ((g2-window &rest args-to-reclaim) &body body)
  `(let ((gensym-window (map-to-gensym-window-or-stack-error ,g2-window)))
     (when (nms-supported-or-stack-error gensym-window)
       (make-evaluation-value-from-lisp-value
         (prog1 (progn ,@body)
           ,@(loop for arg in args-to-reclaim
                   collect `(when ,arg (reclaim-evaluation-value ,arg))))))))


;;; The macro `with-nms-window' is a simpler version for functions which have a
;;; more complicated reclamation pattern than the former can handle.

(defmacro with-nms-window ((g2-window) &body body)
  `(let ((gensym-window (map-to-gensym-window-or-stack-error ,g2-window)))
     (when (nms-supported-or-stack-error gensym-window)
       ,@body)))


;;; The sysproc `nms-version' returns the current version of the compiled-in
;;; sysprocs (as opposed to the KB-level sysprocs provided by nms.kb, which
;;; necessarily have their own version number).

(defun-for-system-procedure nms-version ()
  (make-evaluation-value-from-lisp-value nms-version))


;;; The sysproc `nms-supported-p' returns two boolean values. The first is true
;;; if NMS menu bars are supported and the second if NMS popup menus are
;;; supported, on the given window.

(defun-for-system-procedure nms-supported-p (g2-window)
  (let* ((gensym-window?
           (map-g2-window-to-gensym-window g2-window))
         (menu-bars
           (make-evaluation-boolean-value (if gensym-window? (nms-menu-bars-supported-p gensym-window?))))
         (popup-menus
           (make-evaluation-boolean-value (if gensym-window? (nms-popup-menus-supported-p gensym-window?)))))
    (values menu-bars popup-menus)))


;;; The sysproc `nms-create-menu' create a native menu on the given window, and
;;; returns a handle, which is a small positive integer.  Signals error if menu
;;; cannot be created. Type is either menu-bar or popup.

(defun-for-system-procedure nms-create-menu (g2-window type label callback)
  (with-nms-wrapper (g2-window label)
    (unless (memq type nms-allowed-menu-types)
      (ui-stack-error "The menu type ~NF must be one of ~A." type nms-allowed-menu-types))

    (when (nms-menu-bar-menu-type type)
      (nms-menu-bars-or-stack-error gensym-window))

    (let* ((callback-name? (nms-callback-name-or-stack-error callback))
           (menu? (nms-create-menu-1 gensym-window type label callback-name?)))
      (cond (menu?
             (nms-menu-handle menu?))
            (t
             (nms-signal-allocation-error))))))


;;; The function `internal-name-of-built-in-menu?' both determines which
;;; built-in menus we export to users, and how the external name maps to the
;;; internal name.

(defun internal-name-of-built-in-menu? (menu-name)
  (cdr (assq menu-name '((file . file-submenu)
                         (edit . edit-submenu)
                         (system-tables . system-table-menu)
                         (view . view-submenu)
                         (toolbars . toolbars)
;                         (workspace . workspace-submenu)
;                         (entity-submenu . item)
                         (run . run-submenu)
                         (run-options . run-options)
                         (tools . tools-submenu)
                         (package-preparation . package-preparation-menu)
                         (window . window-submenu)
                         (help . help-submenu)))))

;;; The function `nms-get-built-in-menu' returns a copy of the named built-in
;;; menu. The menu functions just like the "real" one, including graying and
;;; ungraying.

(defun-for-system-procedure nms-get-built-in-menu (g2-window menu-name)
  (with-nms-wrapper (g2-window)
    (for-workstation ((workstation-this-is-on gensym-window))
      (let* ((internal-name
               (or (internal-name-of-built-in-menu? menu-name)
                   (ui-stack-error "There is no built-in menu named ~A." menu-name)))
             (mouse-pointer
               (selection-mouse-pointer current-workstation))
             (cached-restrictions-alist
               (compute-all-restrictions current-g2-user-mode?))
             (menu?
               (nms-create-command-menu gensym-window internal-name 'popup mouse-pointer)))
        (reclaim-filter-tree-function cached-restrictions-alist)
        (unless menu?                        ; Eg, the window menu when running in SDI mode.
          (ui-stack-error "The built-in menu ~A is not available in the current context." menu-name))
        (nms-menu-handle menu?)))))


;;; The function `nms-delete-menu' deletes the given menu, its items, and
;;; optionally all of its submenus, recursively.  Returns 1 on success, 0 on
;;; error.

(defun-for-system-procedure nms-delete-menu (g2-window menu-handle recursive-p)
  (with-nms-wrapper (g2-window)
    (let ((menu (nms-menu-or-stack-error gensym-window menu-handle)))
      (when (and (nms-menu-p menu)
                 (nms-built-in-menu-p menu))
        (ui-stack-error "The menu handle ~A represents built-in menu and may not be deleted."
                        menu-handle))
      (nms-delete-menu-1 gensym-window menu recursive-p)
      1)))

;;; The function `nms-reset' deletes all user-created NMS menus and items for
;;; given window.  If the current menu-bar was an NMS menu, then it reverts to
;;; the default menu-bar.  All other per-window state reverts to the default:
;;; the callback name, etc.

(defun-for-system-procedure nms-reset (g2-window)
  (with-nms-wrapper (g2-window)
    (nms-reset-1 gensym-window nil)        ; A soft reset
    1))


;;; The function `nms-dismiss' deexposes any popup or pulldown menus on window
;;; and exits any modal menu event loop.

(defun-for-system-procedure nms-dismiss (g2-window)
  (with-nms-wrapper (g2-window)
    (nms-dismiss-1 gensym-window)
    1))

;;; The function 'nms-set-iconsize' changes the icon size of NMS menu bar and tool bar if the window support NMS.
;;; Currently, the maximum size of the icon size is 96x96

(defun-for-system-procedure nms-set-iconsize (iconsize g2-window)
  (when (>f iconsize 96)
    (ui-stack-error "The maximum icon size is 96x96."))
  (when (>f 16 iconsize)
    (ui-stack-error "The minimum icon size is 16x16."))
  (with-nms-wrapper (g2-window)
    (nms-set-iconsize-1 gensym-window iconsize)
      1))

;; Should this stack-error on unsupported, or just return false?
(defun-for-system-procedure nms-is-menu-p (g2-window handle)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (torf (nms-menu-p (nms-lookup-handle gensym-window handle))))
    (copy-evaluation-truth-value
      (if torf evaluation-true-value evaluation-false-value))))

(defun-for-system-procedure nms-is-pop-up-menu-p (g2-window handle)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (menu (nms-lookup-handle gensym-window handle))
         (torf (nms-pop-up-menu-p menu)))
    (copy-evaluation-truth-value
      (if torf evaluation-true-value evaluation-false-value))))

(defun-for-system-procedure nms-is-menu-bar-p (g2-window handle)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (menu (nms-lookup-handle gensym-window handle))
         (torf (nms-menu-bar-menu-p menu))) ; For NMS 1.2, fix the return value.
    (copy-evaluation-truth-value
      (if torf evaluation-true-value evaluation-false-value))))

(defun-for-system-procedure nms-is-menu-item-p (g2-window handle)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (torf (nms-menu-item-p (nms-lookup-handle gensym-window handle))))
    (copy-evaluation-truth-value
      (if torf evaluation-true-value evaluation-false-value))))


;;; The function `nms-get-menus' returns a sequence of all the valid menu
;;; handles on window.

(defun-for-system-procedure nms-get-menus (g2-window)
  (with-nms-wrapper (g2-window)
    (let ((menus ()))
      (do-nms-items (mot gensym-window)
        (when (nms-menu-p mot)
          (gensym-push (nms-menu-handle mot) menus)))
      (allocate-evaluation-sequence (nreverse menus)))))

;;; The function `nms-get-items' returns a sequence of all the choice handles in
;;; menu on window.

(defun-for-system-procedure nms-get-items (g2-window menu-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu (nms-menu-or-stack-error gensym-window menu-handle)))
      (allocate-evaluation-sequence
        (nreverse                        ; They are stored in reverse order.
          (loop for item in (nms-menu-items menu)
                collect (nms-menu-item-handle item) using eval-cons))))))


;;; The function `nms-get-item-with-key' returns the handle of the menu item
;;; within menu or one of its submenus, recursively, with given key. If none,
;;; return 0. If more than one, returns one arbitrarily.

(defun-for-system-procedure nms-get-item-with-key (g2-window menu-handle key)
  (with-nms-wrapper (g2-window)
    (let* ((menu (nms-menu-or-stack-error gensym-window menu-handle))
           (item? (nms-get-item-with-key-1 menu key)))
      (if item? (nms-menu-item-handle item?) 0))))

(defun nms-get-item-with-key-1 (menu key)
  (loop for menu-or-item in (nms-menu-items menu)
        as item? = (cond ((nms-menu-item-p menu-or-item)
                          (when (and (nms-key-valid-p menu-or-item)
                                     ;; Do we need a better comparison here?
                                     ;; Certainly if we allow structures for keys.
                                     ;; Changed from EQL to EQUAL, to handle strings. -fmw, 7/16/03
                                     ;; Changed to EQUALW, to handle strings! -fmw, 11/19/05
                                     (equalw key (nms-menu-item-key menu-or-item)))
                            menu-or-item))
                         (t
                          (nms-get-item-with-key-1 menu-or-item key)))
        when item? return it))

(defun nms-get-user-visible-key (menu-or-item)
  (let ((key (nms-menu-item-key menu-or-item)))
    (cond ((not (nms-key-valid-p menu-or-item))
           nil)
          ((ui-command-p key)                ; Used by internal menus.
           (ui-command-menu-name key))
          (t
           key))))

;;; The function `nms-append-item' appends an ordinary menu item to the end of
;;; given menu and returns the item-handle.  The label is a string or one of the
;;; symbols SEPARATOR or BREAK.  Signals on any error.

(defun-for-system-procedure nms-append-item (g2-window menu-handle label key)
  (with-nms-wrapper (g2-window label)
    (nms-permitted-key-or-stack-error key)
    (let* ((menu (nms-menu-or-stack-error gensym-window menu-handle))
           (item? (nms-append-item-1 gensym-window menu label key)))
      (cond (item?
             (nms-menu-item-handle item?))
            ((nms-virtual-item-p label)        ; Not an error for item? to be NIL here.
             0)
            (t
             (nms-signal-allocation-error))))))

(defun nms-pretty-name (menu)
  (or (nms-menu-label menu)
      #w"no name"))

;;; The function `nms-append-submenu' appends a (precreated) submenu to the end
;;; of the given menu and returns the submenu-handle (serves as the item handle).

(defun-for-system-procedure nms-append-submenu (g2-window menu-handle label submenu-handle)
  (with-nms-wrapper (g2-window label)
    (let* ((menu (nms-menu-or-stack-error gensym-window menu-handle))
           (submenu (nms-menu-or-stack-error gensym-window submenu-handle))
           (existing-parent-menu?
             (nms-lookup-handle gensym-window (nms-menu-parent submenu))))
      (when existing-parent-menu?
        (ui-stack-error
          "The submenu ~S cannot be added to menu ~S because it is already in menu ~S."
          label
          (nms-pretty-name menu)
          (nms-pretty-name submenu)))
      (nms-append-submenu-1 gensym-window menu label submenu)
      (nms-menu-handle submenu))))

(defun-for-system-procedure nms-check-menu-item (g2-window item-handle torf)
  (with-nms-wrapper (g2-window)
    (let* ((item (nms-menu-item-or-stack-error gensym-window item-handle))
           (menu (nms-menu-item-parent-or-stack-error gensym-window item))
           (bitp (evaluation-truth-value-is-true-p torf))
           (was-checked (nms-has-property-p g2-window item-handle 'checked)))
      (nms-set-bit item mf-checked bitp)
      (with-icp-window (gensym-window)
        (send-icp-nms-check-menu-item
          gensym-window (nms-menu-handle menu) (nms-menu-item-id item)
          (if bitp mf-checked 0)))
      was-checked)))

(defun-for-system-procedure nms-enable-menu-item (g2-window item-handle torf)
  (with-nms-wrapper (g2-window)
    (let* ((item (nms-menu-or-item-or-stack-error gensym-window item-handle))
           (menu (nms-menu-item-parent-or-stack-error gensym-window item))
           (bitp (evaluation-truth-value-is-true-p torf))
           (was-enabled (nms-has-property-p g2-window item-handle 'enabled))
           ;; For Win32 menus only, set the gray bit by position, instead of by
           ;; command ID, because by command ID does not work if the item is
           ;; actually a menu. We could set it by position always, but
           ;; by-position is very iff with TWNG. See HQ-4620867 and HQ-5397646.
           (by-position (not (twng-window-p gensym-window))))
      (nms-set-bit item mf-grayed (not bitp))
      (with-icp-window (gensym-window)
        (send-icp-nms-enable-menu-item
          gensym-window (nms-menu-handle menu)
          (if by-position
              (nms-menu-item-position item)
              (nms-menu-item-id item))
          (logiorf (if bitp 0 mf-grayed)
                   (if by-position mf-byposition 0))))
      was-enabled)))

(defun-for-system-procedure nms-check-radio-item (g2-window first-handle last-handle check-handle)
  (with-nms-wrapper (g2-window)
    (let ((first (nms-menu-item-or-stack-error gensym-window first-handle))
          (last (nms-menu-item-or-stack-error gensym-window last-handle))
          (check (nms-menu-item-or-stack-error gensym-window check-handle)))
      (unless (and (eql (nms-menu-item-parent first) (nms-menu-item-parent last))
                   (eql (nms-menu-item-parent last)  (nms-menu-item-parent check)))
        (ui-stack-error "All radio items must be in the same menu."))
      (let ((menu (nms-menu-item-parent-or-stack-error gensym-window first)))
        ;; FIXME: Set flag bits locally. Need to loop from first to last.
;                  (nms-set-bit check mf-checked bitp)
        (with-icp-window (gensym-window)
          (send-icp-nms-check-radio-item
            gensym-window (nms-menu-handle menu)
            (nms-menu-item-id first)
            (nms-menu-item-id last)
            (nms-menu-item-id check)
            0))
        check-handle))))

(defun-for-system-procedure nms-has-property-p (g2-window handle property)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (menu-or-item (nms-menu-or-item-or-stack-error gensym-window handle))
         (flags (nms-menu-item-flags menu-or-item))
         (torf (case property
                 (checked (/=f 0 (logandf flags mf-checked)))
                 (enabled (=f 0 (logandf flags mf-grayed))))))
    (copy-evaluation-truth-value
      (if torf evaluation-true-value evaluation-false-value))))

(defun-for-system-procedure nms-set-label (g2-window menu-or-item-handle new-label)
  (with-nms-window (g2-window)
    (let* ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle))
           (menu (nms-menu-item-parent-or-stack-error gensym-window menu-or-item))
           (old-label-ev (make-evaluation-text
                           (or (nms-menu-label menu-or-item) #w""))))
      (nms-set-text-1 gensym-window menu menu-or-item
                      'label (nms-copy-string (evaluation-text-value new-label)))
      (reclaim-evaluation-text new-label)
      old-label-ev)))

(defun-for-system-procedure nms-get-label (g2-window menu-or-item-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle)))
      (or (nms-menu-label menu-or-item) #w""))))


(defun-for-system-procedure nms-set-help (g2-window menu-or-item-handle new-help)
  (with-nms-window (g2-window)
    (let* ((item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle))
           (menu (nms-menu-item-parent-or-stack-error gensym-window item))
           (old-help-ev (make-evaluation-text
                          (or (nms-menu-help menu) #w""))))
      (nms-set-text-1 gensym-window menu item
                      'help (nms-copy-string (evaluation-text-value new-help)))
      (reclaim-evaluation-text new-help)
      old-help-ev)))

(defun-for-system-procedure nms-get-help (g2-window menu-or-item-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle)))
      (or (nms-menu-help menu-or-item) #w""))))


;; Returns the old key (if valid).
(defun-for-system-procedure nms-set-key (g2-window menu-or-item-handle new-key)
  (with-nms-window (g2-window)
    (nms-permitted-key-or-stack-error new-key)
    (let* ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle))
           (old-key-ev (make-evaluation-value-from-lisp-value
                         (nms-get-user-visible-key menu-or-item))))
      (nms-set-key-1 gensym-window menu-or-item new-key)
      (reclaim-evaluation-value new-key)
      old-key-ev)))

(defun-for-system-procedure nms-get-key (g2-window menu-or-item-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle)))
      (nms-get-user-visible-key menu-or-item))))


;; Returns the old callback set for this item (as opposed to the one actually
;; called for this item, which is found by a search).
(defun-for-system-procedure nms-set-callback (g2-window menu-or-item-handle new-callback)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle))
          (new-callback-name? (nms-callback-name-or-stack-error new-callback)))
      (prog1 (nms-menu-callback menu-or-item)
        (setf (nms-menu-callback menu-or-item) new-callback-name?)))))

;; Always returns a symbol.
(defun-for-system-procedure nms-get-callback (g2-window menu-or-item-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle)))
      (nms-menu-callback menu-or-item))))


;;; The function `nms-set-event-callback' sets either the posting or unposting
;;; callback.

(defun nms-set-event-callback (type g2-window menu-handle new-callback)
  (with-nms-wrapper (g2-window)
    (let* ((menu (nms-menu-or-stack-error gensym-window menu-handle))
           (new-callback-name? (nms-callback-name-or-stack-error new-callback))
           (old-callback-name? (case type
                                 (posting (nms-menu-posting-callback menu))
                                 (unposting (nms-menu-unposting-callback menu))))
           (flag (case type
                   (posting mf-dynamic)
                   (unposting mf-unpost)
                   (t 0)))
           (supported? (case type
                         (posting (window-supports-nms-posting-callbacks gensym-window))
                         (unposting (window-supports-nms-unposting-callbacks gensym-window)))))
      (unless supported?
        (ui-stack-error "NMS ~a callbacks are not supported on window ~NF." type g2-window))
      (when (nms-menu-bar-menu-p menu)
        (ui-stack-error "~a callbacks are not allowed on the menu bar itself, handle ~D."
                        type menu-handle))

      (unless (eq new-callback-name? old-callback-name?)
        (case type
          (posting (setf (nms-menu-posting-callback menu) new-callback-name?))
          (unposting (setf (nms-menu-unposting-callback menu) new-callback-name?)))

        (nms-set-bit menu flag (not (null new-callback-name?)))

        ;; Tell TW to inform us on WM_INITMENUPOPUP for this menu.
        (with-icp-window (gensym-window)
          (send-icp-nms-set-menu-flags
            gensym-window (nms-menu-handle menu)
            (if new-callback-name? flag 0)
            flag)))
      (or old-callback-name? 'none))))

(defun-for-system-procedure nms-set-posting-callback (g2-window menu-handle new-callback)
  (nms-set-event-callback 'posting g2-window menu-handle new-callback))

(defun-for-system-procedure nms-set-unposting-callback (g2-window menu-handle new-callback)
  (nms-set-event-callback 'unposting g2-window menu-handle new-callback))

;; Always returns a symbol.
(defun-for-system-procedure nms-get-posting-callback (g2-window menu-or-item-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle)))
      (or (nms-menu-posting-callback menu-or-item)
          'none))))

(defun-for-system-procedure nms-get-unposting-callback (g2-window menu-or-item-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle)))
      (or (nms-menu-unposting-callback menu-or-item)
          'none))))


;; Selection callbacks

(defun-for-system-procedure nms-set-selection-callback
    (g2-window menu-handle new-callback)
  (with-nms-wrapper (g2-window)
    (let* ((menu (nms-menu-or-stack-error gensym-window menu-handle))
           (new-callback-name? (nms-callback-name-or-stack-error new-callback))
           (old-callback-name? (nms-menu-selection-callback menu)))
      (unless (window-supports-nms-selection-callbacks gensym-window)
        (ui-stack-error "NMS selection callbacks are not supported on window ~NF."
                        g2-window))
      (unless (eq new-callback-name? old-callback-name?)
        (setf (nms-menu-selection-callback menu) new-callback-name?)

        (nms-set-bit menu mf-menuselect (not (null new-callback-name?)))

        (with-icp-window (gensym-window)
          (send-icp-nms-set-menu-flags
            gensym-window (nms-menu-handle menu)
            (if new-callback-name? mf-menuselect 0)
            mf-menuselect)))
      (or old-callback-name? 'none))))

(defun-for-system-procedure nms-get-selection-callback (g2-window menu-or-item-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu-or-item (nms-menu-or-item-or-stack-error gensym-window menu-or-item-handle)))
      (or (nms-menu-selection-callback menu-or-item)
          'none))))


(defun-for-system-procedure nms-delete-all-menu-choices (g2-window menu-handle)
  (with-nms-wrapper (g2-window)
    (let ((menu (nms-menu-or-stack-error gensym-window menu-handle)))
      (nms-delete-menu-contents-1 gensym-window menu))))


(defun-for-system-procedure nms-set-colors (g2-window item-handle foreground background)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (when (nms-supported-or-stack-error gensym-window)
      (let* ((item (nms-menu-or-item-or-stack-error gensym-window item-handle))
             (menu (nms-menu-item-parent-or-stack-error gensym-window item))
             (old-fg (or (nms-menu-item-fg item) 'default))
             (old-bg (or (nms-menu-item-bg item) 'default)))
        (nms-set-colors-1 gensym-window menu item
                          (if (memq foreground '(default none)) nil foreground)
                          (if (memq background '(default none)) nil background))
        (values old-fg old-bg)))))

(defun-for-system-procedure nms-get-colors (g2-window item-handle)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (when (nms-supported-or-stack-error gensym-window)
      (let ((item (nms-menu-or-item-or-stack-error gensym-window item-handle)))
        (values (or (nms-menu-item-fg item) 'default)
                (or (nms-menu-item-bg item) 'default))))))


(defun-for-system-procedure nms-set-icon (g2-window submenu-or-item-handle icon-designation)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (when (nms-supported-or-stack-error gensym-window)
      (valid-icon-designation-or-stack-error icon-designation)
      ;; We make it just a warning for icons to be unsupported, which I think
      ;; will be a convenience to users.
      (cond ((not (native-icons-p gensym-window))
             (notify-user "Warning: NMS icons are not supported on window ~NF."
                          g2-window)
             'none)
            (t
             ;; Note: item is actually submenu-or-item here.
             (let* ((item (nms-menu-or-item-or-stack-error
                            gensym-window submenu-or-item-handle))
                    (menu (nms-menu-item-parent-or-stack-error gensym-window item))
                    (old-icon-designation? (nms-menu-item-icon item))
                    (icon-designation? (if (neq icon-designation 'none) icon-designation)))
               (unless (eq old-icon-designation? icon-designation?)
                 (nms-set-icon-1 gensym-window menu item icon-designation?))
               (or old-icon-designation? 'none)))))))

(defun-for-system-procedure nms-get-icon (g2-window submenu-or-item-handle)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (when (nms-supported-or-stack-error gensym-window)
      (let ((item (nms-menu-or-item-or-stack-error gensym-window submenu-or-item-handle)))
        (or (nms-menu-item-icon item) 'none)))))


;;; The function `nms-set-menu-bar' sets the menu-bar of g2-window to the given
;;; menu. A menu-handle of 0 or otherwise invalid means to revert to the
;;; developer menu-bar.  A menu-handle of -1 means to hide the current menu-bar,
;;; -2 means unhide.

(defun-for-system-procedure nms-set-menu-bar (g2-window menu-handle)
  (with-nms-wrapper (g2-window)
    (nms-menu-bars-or-stack-error gensym-window)
    (let* ((menu? (nms-lookup-handle gensym-window menu-handle))
           (old-menu-bar (or (nms-current-menu-bar? gensym-window) 0))
           (handle (cond ((=f menu-handle 0)
                          (for-workstation ((workstation-this-is-on gensym-window))
                            (ensure-developer-menu-bar gensym-window)))
                         ((=f menu-handle -1) -1)
                         ((=f menu-handle -2) old-menu-bar)
                         (menu? (nms-menu-handle menu?))
                         (t 0))))
      (when (and menu? (neq (nms-menu-type menu?) 'menu-bar))
        (ui-stack-error "The given menu is not a menu-bar menu."))
      (nms-set-menu-bar-1 gensym-window handle)
      old-menu-bar)))


(defun-for-system-procedure nms-get-menu-bar (g2-window)
  (with-nms-wrapper (g2-window)
    (nms-menu-bars-or-stack-error gensym-window)
    (or (nms-current-menu-bar? gensym-window) 0)))


;;; The function `nms-pop-up-menu' exposes the given menu as a popup menu at x,y
;;; in USER window coordinates.

(defun-for-system-procedure nms-pop-up-menu (g2-window menu-handle user-x-in-window user-y-in-window)
  (with-nms-wrapper (g2-window)
    (let ((menu (nms-menu-or-stack-error gensym-window menu-handle))
          (x-in-window (user-x-in-window-to-internal-x-in-window user-x-in-window gensym-window))
          (y-in-window (user-y-in-window-to-internal-y-in-window user-y-in-window gensym-window)))
      (unless (nms-pop-up-menu-p menu)
        (ui-stack-error "The given menu is not a pop-up menu."))
      (with-icp-window (gensym-window)
        (send-icp-nms-pop-up-menu gensym-window (nms-menu-handle menu) x-in-window y-in-window))
      menu-handle)))

;; TODO: Add original-item argument.


;;; The function `nms-start-callback' starts a KB-level NMS callback procedure of
;;; the given type, with lambda-list matching one of:
;;;    (g2-window, handle, choice, path:sequence)           -- 7.x NMS callback
;;;    (g2-window, handle, choice, properties:structure)    -- 8.x NMS callback
;;;    (g2-window, handle, choice, path: sequence, status:truth-value) -- 8.0r1 Selection callback
;;; where properties is a structure with PATH as one of its slots. We allow
;;; either procedure type, supplying the correct arguments in either case.

;;; Returns non-NIL iff procedure started.

(defun nms-start-callback (procedure-name type g2-window handle choice activation-path value?)
  (let* ((pretty-type (case type
                        (activation "NMS activation callback")
                        (control "NMS control callback")
                        (posting "NMS posting callback")
                        (unposting "NMS unposting callback")
                        (selection "NMS selection callback")
                        (t "NMS callback")))
         (procedure?
           (get-callback-procedure procedure-name
                                   pretty-type
                                   nil        ; No arglist checking (we dispatch later)
                                   t))        ; must-be-runnable
         (lambda-list (and procedure? (argument-list-description procedure?)))
         (arguments (gensym-list g2-window handle choice)))
    (cond ((null procedure?))

          ((argument-list-description-matches-template-p
             lambda-list '((class g2-window) integer integer (sequence)))
           (setq arguments (nconc arguments (gensym-list activation-path))))

          ((argument-list-description-matches-template-p
             lambda-list '((class g2-window) integer integer (sequence) truth-value))
           (setq arguments (nconc arguments
                                  (gensym-list activation-path
                                               (if value?
                                                   evaluation-true-value
                                                   evaluation-false-value)))))

          ((argument-list-description-matches-template-p
             lambda-list '((class g2-window) integer integer (structure)))
           (let ((plist
                    (nconc (eval-list 'path activation-path)
                          (eval-list 'type type)
                          (case type
                            (control
                             (if value? (eval-list 'string (copy-if-text-string value?))))
                            ((selection posting unposting)
                             (eval-list 'status (if value?
                                                    evaluation-true-value
                                                    evaluation-false-value)))))))
             (setq arguments (nconc arguments
                                    (gensym-list (allocate-evaluation-structure plist))))))
          (t
           (warning-message* 1 "The ~A procedure ~NF's signature is not one of ~
                                  (g2-window, integer, integer, sequence), or ~
                                  (g2-window, integer, integer, structure), or ~
                                  (g2-window, integer, integer, sequence, truth-value)"
             pretty-type procedure?)
           (setq procedure? nil)))
    (when procedure?
      (let ((kb-procedure-completion-form?
              (if (eq type 'posting)
                  (slot-value-list
                    'nms-procedure-exit-hook g2-window
                    (copy-frame-serial-number (frame-serial-number g2-window))))))
        (apply-kb-procedure procedure? arguments)))))


;;; The function `nms-procedure-exit-hook' called when a posting callback
;;; procedure exits by any means (normal return or abort).

(defun nms-procedure-exit-hook (form)
  (let ((g2-window (second form))
        (fsn (third form)))
    ;; closing-procedure-invocation is bound to the invocation object here.
    ;; The procedure return value can be found in (svref global-stack 0).
    ;; See return-values-body
    (unless (frame-has-been-reprocessed-p g2-window fsn)
      (let ((gensym-window? (map-g2-window-to-gensym-window g2-window)))
        (when (and gensym-window?
                   (icp-window-p gensym-window?)
                   (window-supports-nms-posting-callbacks gensym-window?))
          ;; Hmm... should this be checking for ICP connection still open?
          (with-icp-window (gensym-window?)
            (send-icp-nms-enable-items gensym-window? nil)))))
    (reclaim-frame-serial-number fsn)
    (reclaim-slot-value-list form)))



;;; The event-handler `nms-execute-menu-choice' runs when a choice is made from
;;; an NMS menu on window, or a menu is dismissed without a choice. CHOICE is
;;; the unique item id or nms-no-choice for no choice.

(define-event-handler nms-execute-menu-choice (workstation (gensym-window window) event-plist)
  (setf global-nms-menu-choiced-item-id (getf event-plist 'choice))    ; Top-level popup Menu handle or -1
  (let* ((menu-handle (getf event-plist 'menu)) ; Win32 command ID.
         (item-handle (nms-menu-id-to-handle gensym-window global-nms-menu-choiced-item-id))
         (item? (nms-lookup-handle gensym-window item-handle)) ; Chosen item, if any.
         (parent-menu? (and item? (nms-lookup-handle gensym-window (nms-menu-item-parent item?))))
         (menu? (or (nms-lookup-handle gensym-window menu-handle)
                    parent-menu?))
         (cmd? (and item? (nms-menu-item-command item?))))
    (cond ((null cmd?)                        ; A KB-level NMS menu item.
           (nms-execute-kb-level-callback gensym-window 'activation menu? item?))

          ((consp cmd?)                        ; User menu choice
           (when (framep (get-selection workstation))
             (execute-user-menu-choice-if-possible (second cmd?)
                                                   (get-selection workstation))))

          ((eq cmd? t)                        ; A parameter for UI command
           (assert-for-development (and parent-menu? item?))
           (nms-execute-parameter-menu-choice workstation parent-menu? item?))

          ((partial-command-p cmd?)        ; A partial command.
           (nms-pursue-partial-command workstation cmd?))

          ((symbolp cmd?)                ; A bare UI command.
           (nms-execute-ui-command workstation cmd?))
          (t
           (dwarn "Junk in nms-execute-menu-choice: ~s" cmd?)))))

;; Note: decode-native-control-event defines the contents of event-plist.


;;; The function `nms-execute-kb-level-callback' tries to start the KB-level
;;; procedure associated with the choice of item within menu, or the posting of
;;; a menu. If no item was chosen, the procedure associated with menu. Returns
;;; non-NIL iff procedure is actually started. ITEM? here is either NIL, an
;;; nms-menu-item structure, or a fixnum. PLIST is a plist of additional
;;; arguments to pass to the callback, as a structure. The caller is responsible
;;; for reclaiming it.

(defun nms-execute-kb-level-callback (gensym-window type menu? item? &optional value?)
  (let* ((g2-window? (g2-window-for-gensym-window? gensym-window))
         (menu-or-item? (if (nms-menu-item-p item?) item? menu?))
         (callback? (nms-lookup-callback gensym-window type menu-or-item?)))
    (cond ((null g2-window?)
           (dwarn "No g2-window associated with ~s!" gensym-window)
           nil)
          ((null menu-or-item?)
           (dwarn "No menu or item found for handles ~d and ~d on ~s!"
                  menu? item? gensym-window)
           nil)
          ((null callback?)
           (warning-message* 1
               "There is no NMS ~(~A~) callback procedure defined for menu or choice \"~A\" with handle ~D."
             type
             (nms-pretty-name menu-or-item?)
             (nms-menu-handle menu-or-item?))
           nil)
          (t
           (nms-start-callback
             callback?
             type
             g2-window?
             (if menu? (nms-menu-handle menu?) 0)
             (if (nms-menu-item-p item?) (nms-menu-item-handle item?) (or item? 0))
             (nms-compute-activation-path gensym-window menu-or-item?)
             value?)))))


;;; The function `nms-execute-ui-command' runs when an NMS menu item with an
;;; attached UI command is chosen.  These are the items that G2 created
;;; internally, as opposed to items created by the KB developer with the NMS
;;; sysprocs.

(defun nms-execute-ui-command (workstation command-name)
  (run-ui-command-on-selection command-name workstation))


;;; The function `nms-compute-activation-path' returns a sequence of the handles
;;; of each menu in the path from the toplevel menu to the given leaf item.

(defun nms-compute-activation-path (gensym-window menu-or-item?)
  (allocate-evaluation-sequence
    (nreverse
      (loop for mot? = menu-or-item? then (nms-lookup-handle gensym-window (nms-menu-parent mot?))
            while mot?
            collect (make-evaluation-integer (nms-menu-handle mot?)) using eval-cons))))

;; TODO: We can compute this from the leaf only because menus are not currently
;; shared.  But we need to have shared menus (for caching large menus like the
;; class menu and the 2nd level color menu), so the activation path will have to
;; be computed in the C code on TW and passed back (by hooking WM_SELECTMENU).


;;; The function `nms-lookup-callback' returns the name of the given type of
;;; callback procedure for the given NMS menu or item. TYPE should be ACTIVATION
;;; or POSTING.

(defun nms-lookup-callback (gensym-window type menu-or-item?)
  (loop for mot? = menu-or-item? then (nms-lookup-handle gensym-window (nms-menu-parent mot?))
        while mot?
        as callback? = (case type
                         ((activation control) (nms-menu-callback mot?))
                         (posting (if (nms-menu-p mot?)
                                      (nms-menu-posting-callback mot?)))
                         (unposting (if (nms-menu-p mot?)
                                        (nms-menu-unposting-callback mot?)))
                         (selection (if (nms-menu-p mot?)
                                        (nms-menu-selection-callback mot?)))
                         (t (dwarn "Unknown NMS callback type: ~a" type)))
        when callback?
          do (return callback?)))


;;;; NMS Parameter Menus


;;; NMS parameter menus are used for the arguments to UI commands. Each item in
;;; a parameter menu has a nms-menu-command slot of T, to mark it is a parameter
;;; value. The actual value is in the key (not fsn-protected). The number of the
;;; argument to which it applies is in nms-menu-argument slot.  The item's
;;; containing menu holds the partial commmand in its command slot.


;;; The function `nms-execute-parameter-menu-choice' executes a choice from a
;;; parameter menu. Such a choice is "executed" by filling-in the appropriate
;;; argument of the menu's partial command, and pursuing it.

(defun nms-execute-parameter-menu-choice (workstation menu item)
  (let* ((partial-command (nms-menu-command menu))
         (which-argument  (nms-menu-argument menu))
         (key (nms-menu-item-key item))
         (mouse-pointer (selection-mouse-pointer workstation))
         (menu-description (find-menu-description (nms-menu-callback menu)))
         (value (transform-menu-item-after-choice menu-description key)))
    (parameter-menu-choice-function-1
      (copy-partial-command partial-command)
      nil which-argument value mouse-pointer)
    (release-mouse-pointer-if-any mouse-pointer)))



;;; The function `nms-pursue-partial-command' is called when partial-commands in
;;; command menus, as opposed to parameter menus, are chosen. These
;;; partial-commands don't get an argument filled-in from the menu, we simply
;;; pursue them, being careful to first copy, so as to not disturb the menu item
;;; itself.

(defun nms-pursue-partial-command (workstation partial-command)
  (let ((mouse-pointer (selection-mouse-pointer workstation)))
    (pursue-partial-command
      (copy-partial-command partial-command)
      mouse-pointer
      'menu)
    (release-mouse-pointer-if-any mouse-pointer)))


;;;; NMS Controls


;;; An `NMS Control' is a native control managed by NMS. It currently can be a
;;; toolbar, an edit-box, or a combo-box. Toolbars are like menu bars, except
;;; that you can have any number of them, they have names, and they can be
;;; docked to any edge of a frame or left floating.

(def-concept nms-control)
(def-concept toolbar)


;;; The event-handler `handle-nms-control-message' handles a message from an NMS
;;; control. The only possible message now is "made a choice".

(define-event-handler handle-nms-control-message ((gensym-window window) event-plist)
  (let* ((control-id? (getf event-plist 'control-id))
         (selection? (getf event-plist 'selection))
         (value? (getf event-plist 'value))
         (control? (and control-id?
                        (nms-lookup-handle
                          gensym-window (nms-menu-id-to-handle gensym-window control-id?))))
         (parent? (and control?
                       (nms-lookup-handle gensym-window (nms-menu-item-parent control?)))))
    selection?
    (when control?
      ;; TODO: Pass a plist to the callback, including selection.
      (nms-execute-kb-level-callback gensym-window 'control parent? control? value?))))

(defun nms-controls-supported-or-stack-error (gensym-window)
  (unless (nms-controls-p gensym-window)
    (ui-stack-error "NMS controls are not supported on ~NF"
                    (g2-window-for-gensym-window? gensym-window))))

(defun nms-toolbars-supported-or-stack-error (gensym-window)
  (unless (nms-toolbars-p gensym-window)
    (ui-stack-error "NMS toolbars are not supported on ~NF"
                    (g2-window-for-gensym-window? gensym-window))))

(defun nms-controls-check-type-or-stack-error (type options)
  (let ((stype? (case type
                  (toolbar
                   '(structure
                     ((callback symbol)
                      (key datum)
                      (dock symbol)
                      (neighbor integer)
                      (enable-tooltips truth-value)
                      (visible truth-value) ; Default is True for all of them.
                      (button-style (member automatic caption-only icon-only
                                            icon-and-caption default)))))
                  (edit-box
                   '(structure
                     ((callback symbol)
                      (key datum)
                      (width integer)
                      (visible truth-value)
                      (initial text))))
                  (combo-box
                   '(structure
                     ((callback symbol)
                      (key datum)
                      (width integer)
                      (initial text)
                      (choices (sequence text))
                      (drop-down-width integer)
                      (visible truth-value)
                      (allow-any truth-value)))))))
    (unless stype?
      (ui-stack-error "~S is not a known type of NMS control." type))
    (check-type-or-stack-error options stype?)))

;; Users don't call this sysproc directly. There is a separate cap for each
;; control type.

(defun-for-system-procedure nms-create-control (type label options g2-window)
  (with-nms-wrapper (g2-window label)
    (nms-controls-check-type-or-stack-error type options)
    (case type
      (toolbar (nms-toolbars-supported-or-stack-error gensym-window))
      (t       (nms-controls-supported-or-stack-error gensym-window)))
    (let ((callback? (evaluation-structure-slot options 'callback))
          (key? (evaluation-structure-slot options 'key))
          (dock? (evaluation-structure-slot options 'dock))
          (neighbor? (evaluation-structure-slot options 'neighbor))
          (control? nil))

      (when (and neighbor? (not (nms-toolbar-p (nms-lookup-handle gensym-window neighbor?))))
        (reclaim-if-evaluation-value options)
        (ui-stack-error "The neighbor option, ~D, is not a toolbar handle." neighbor?))

      (unless (setq control? (nms-allocate-control gensym-window nil type label))
        (reclaim-if-evaluation-value options)
        (nms-signal-allocation-error))

      (setf (nms-menu-callback control?) callback?)
      (nms-set-key-1 gensym-window control? key?)
      (when (nms-toolbar-p control?)
        (setf (nms-menu-docking-position control?) dock?))

      (let ((plist (unbox-evaluation-value options)))

        (when (and (not (getf plist 'visible t))
                   (not (window-supports-hide-toolbar gensym-window)))
          (ui-stack-error "Initially hidden toolbars are not supported on ~NF" g2-window))

        ;; If the window doesn't support docking against a neighbor, then just
        ;; dock to the same docking station as the neighbor. This is the best we
        ;; can do, and I think is preferable to signalling an error. -fmw,
        ;; 6/2/05

        (when (and neighbor? (not (window-supports-toolbar-docking gensym-window)))
          (let* ((neighbor (nms-lookup-handle gensym-window neighbor?))
                 (dock (or (nms-menu-docking-position neighbor) 'top)))
            (warning-message 3
                "Warning: The window ~NF does not support docking against a neighbor. ~
                 Docking at ~A instead." g2-window dock)
            (setq plist (mutate-gensym-plist plist 'dock dock))))

        (with-icp-window (gensym-window)
          (send-icp-nms-create-control gensym-window
                                       (nms-menu-item-handle control?)
                                       type label plist))
        (reclaim-unboxed-evaluation-value plist))

      ;; FIXME: We are leaking the options here, but we need to be careful about
      ;; shared data in KEY, which was saved into data structure.

      ;; (reclaim-if-evaluation-value options)
      (setf (nms-menu-options control?) options)
      (nms-menu-item-handle control?))))

;;; The function `nms-append-control' adds an NMS control to a menu (or
;;; toolbar). The control-handle is returned.

(defun-for-system-procedure nms-append-control (menu-handle control-handle g2-window)
  (with-nms-wrapper (g2-window)
    (nms-controls-supported-or-stack-error gensym-window)
    (let* ((menu (nms-menu-or-stack-error gensym-window menu-handle))
           (control (nms-menu-item-or-stack-error gensym-window control-handle))
           ;; FIXME: Check control type.
           (existing-parent-menu?
             (nms-lookup-handle gensym-window (nms-menu-parent control))))
      (when existing-parent-menu?
        (ui-stack-error
          "The control ~S cannot be added to menu ~S because it is already in menu ~S."
          (nms-pretty-name control)
          (nms-pretty-name menu)
          (nms-pretty-name existing-parent-menu?)))

      (nms-append-locally gensym-window menu control)
      (with-icp-window (gensym-window)
        (if (window-supports-append-control-ex gensym-window)
            (send-icp-nms-append-control-ex gensym-window
                                            (nms-menu-handle menu)
                                            (nms-menu-handle control)
                                            (nms-menu-item-flags control)
                                            nil)
            (send-icp-nms-append-control gensym-window
                                         (nms-menu-handle menu)
                                         (nms-menu-handle control))))
      (nms-menu-handle control))))

;;; The function `nms-modify-control' modifies an NMS control in a variety of
;;; ways. Added for HQ-4847689 in 8.0r1. CONTROL-HANDLE can be an integer or a
;;; string. ARGUMENT can be an integer, symbol, structure, or sequence.

(defun-for-system-procedure nms-modify-control (control-handle action argument g2-window)
  (with-nms-wrapper (g2-window)
    (nms-controls-supported-or-stack-error gensym-window)
    (unless (current-window-supports-nms-modify-control gensym-window)
      (ui-stack-error "Modifying NMS controls is not supported on ~NF" g2-window))

    ;; Supported actions: SET-TEXT, SET-CHOICE, SHOW, HIDE, 
    ;; actions supported added in Gensym-267: ADD-TEXT, DELETE-TEXT
    (when (memq action '(show hide))
      (unless (window-supports-hide-toolbar gensym-window)
        (ui-stack-error "Show/hide toolbar is not supported on ~NF" g2-window)))

    (let* ((control (nms-menu-or-item-or-stack-error gensym-window control-handle))
           (tree (unbox-evaluation-value argument)))

      ;; TODO: Validate control type, action, and arguments.
      (with-icp-window (gensym-window)
        (send-icp-nms-modify-control gensym-window (nms-menu-handle control) action tree))

      (reclaim-unboxed-evaluation-value tree)
      (reclaim-if-evaluation-value control-handle)
      (reclaim-if-evaluation-value argument)
      (nms-menu-item-handle control))))

(defun-for-system-procedure nms-delete-control (control-handle g2-window)
  (with-nms-wrapper (g2-window)
    (nms-controls-supported-or-stack-error gensym-window)
    (let* ((control (nms-menu-or-item-or-stack-error gensym-window control-handle))
           (menu? (nms-lookup-handle gensym-window (nms-menu-parent control))))
      (with-icp-window (gensym-window)
        (send-icp-nms-delete-control gensym-window
                                     (if menu? (nms-menu-handle menu?) -1)
                                     (nms-menu-handle control)))

      ;; destroy control
      ;; Note: if control is a menu make sure that it does not have sub-items
      (let* ((handle (nms-menu-item-handle control)))
        (when menu? (nms-delete-item menu? control))
        (nms-deallocate-handle gensym-window handle)
        (nms-reclaim-menu-or-item control)
        handle))))

;; The title of the overall G2-Window, that is.
(defun-for-system-procedure g2-ui-set-window-title (title g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (current-window-supports-set-window-title gensym-window)
      (ui-stack-error "Setting the window title is not supported on ~NF" g2-window))
    (set-window-title gensym-window title)
    title))


;;;; NMS Debugging


#+development
(defun nms-dump (&optional tree)
  (loop for wks in workstations-in-service
        as gensym-window = (window-for-workstation wks)
        as array? = (nms-menu-table-slot gensym-window)
        doing
    (when array?
      (format t "~s ~s~%" wks array?)
      (loop for i from 1 to (nms-fill-pointer array?)
            as thing? = (managed-svref array? i)
            as parent? = (and thing? (nms-menu-parent thing?))
            doing
        (cond ((null thing?))
              ((null tree)
               (format t "[~2d] ~s~%" i thing?))
              ((null parent?)
               (nms-tree thing?))))))
  (values))

#+development
(defun nms-tree (menu &optional (indent 0))
  (when menu
    (loop repeat indent doing (princ "  "))
    (format t "~s~%" menu)
    (when (nms-menu-p menu)
      (loop for item in (reverse (nms-menu-items menu)) doing
        (nms-tree item (1+ indent))))
    menu))

#+development
(defun nms-clear ()
  (loop for wks in workstations-in-service
        as win = (window-for-workstation wks)
        doing (setf (nms-menu-table-slot win) nil)))


;;;; UI Themes


(def-type-parameter ui-theme-type (member 2000 2001 2002 2003))

(defun ui-themes-p (gensym-window)
 (and (twng-window-p gensym-window)
      (current-window-supports-nms-set-theme gensym-window)))

(defun default-ui-theme (gensym-window)
  (cond ((twng-window-p gensym-window) 2001)
        (t 'gensym)))

(defun-for-system-procedure g2-ui-set-theme (theme g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (old-theme (or (get-ui-property gensym-window 'theme)
                        (default-ui-theme gensym-window))))
    (check-type-or-stack-error theme ui-theme-type)
    (unless (ui-themes-p gensym-window)
      (ui-stack-error "Settable UI themes are not supported on ~NF" g2-window))
    (nms-set-theme-1 gensym-window theme)
    (set-ui-property gensym-window 'theme theme)
    old-theme))

(defun-for-system-procedure g2-ui-get-theme (g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (or (get-ui-property gensym-window 'theme)
        (default-ui-theme gensym-window))))


;;;; Views API: Properties


(defun readable-view-property-or-stack-error (property)
  (or (view-property-p property)
      (ui-stack-error "~S is not a known view attribute." property)))

(defun views-in-dialogs-p (gensym-window)
  (and (twng-window-p gensym-window)        ; TODO: Lift this restriction.
       (window-supports-views-in-dialogs gensym-window)))

;;; The function `preprocess-view-options' munges an init-plist in any way
;;; needed before sending to TW. CAN STACK-ERROR.

(defun preprocess-view-options (view options)
  (let ((gensym-window (native-window-gensym-window view)))
    (setq options (preprocess-icon-options gensym-window options))
    (setq options (preprocess-container-options gensym-window options (native-window-class view))))
  options)

(defun preprocess-icon-options (gensym-window options)
  (let ((icon? (getf options 'icon)))
    (when icon?
      (valid-icon-designation-or-stack-error icon?)
      (setf (getf options 'icon) (send-native-icon gensym-window icon?))))
  options)

(defun preprocess-container-options (gensym-window options view-class)
  (let ((container? (getf options 'container))
        (dock? (getf options 'dock))
        (neighbor? (getf options 'neighbor)))
    (multiple-value-bind (container neighbor)
        (preprocess-container-options-1 gensym-window container? dock? neighbor? view-class)
      (when container?
        (setf (getf options 'container) container))
      (when neighbor?
        (setf (getf options 'neighbor) neighbor)))
    options))

;; FIXME: Unfortunately, this routine sometimes gets evaluation-values and
;; sometimes gets lisp values for its arguments. It's OK for now, except that we
;; have to print errors with a plain ~A instead of ~NV, meaning users might see
;; LISP data in error messages.
(defun preprocess-container-options-1 (gensym-window container? dock? neighbor? view-class)
  (let ((container -1)
        (neighbor 0))
    (cond ((container-name-p container?) ; Eg, NIL, PANE, MDI-CHILD, ...
           (setq container container?)
           (cond ((null neighbor?))
                 ((eql neighbor? 0)        ; Special case: don't error if neighbor?==0
                  (warning-message* 3 "Ignoring neighbor option of ~D." neighbor?))
                 (t
                  (setq neighbor (lookup-view-handle gensym-window neighbor?)))))
          ((view-designation-p container?)
           (when (and dock? (neq dock? 'within))
             (ui-stack-error "Only docking WITHIN is allowed for container ~A" container?))
           (let ((view (find-native-view-or-stack-error gensym-window container?)))
             (multiple-value-setq (container neighbor)
               (case (native-window-class view)
                 (g2-dialog-view
                  (preprocess-dialog-container gensym-window container? neighbor? view-class))
                 (g2-shortcut-bar
                  (preprocess-shortcut-bar-container view neighbor?))
                 (t
                  (ui-stack-error "Cannot place view in ~A containers."
                                  (pretty-name-of-view-class (native-window-class view))))))))
          (t
           (ui-stack-error "Invalid container ~A" container?)))
    (values container neighbor)))

;; For dialog containers, neighbor is the ID of a control within a dialog.
(defun preprocess-dialog-container (gensym-window container neighbor? view-class)
  (unless (views-in-dialogs-p gensym-window)
    (ui-stack-error "The window ~NF does not support placing views in custom dialogs."
                    (g2-window-for-gensym-window? gensym-window)))
  (let* ((dialog? (lookup-dialog-given-handle
                    gensym-window
                    (lookup-view-handle gensym-window container)))
         (component? (and dialog? neighbor?
                          (lookup-component-given-component-kb-id neighbor? dialog?)))
         (type? (and component?
                     (map-control-type-fixnum-to-symbol (dialog-component-type component?)))))
    (unless component?
      (ui-stack-error "Dialog component ~A was not found in dialog ~A" neighbor? container))
    (unless (eq type? 'label)
      (ui-stack-error "Unable to place ~A into dialog: neighbor must specify a LABEL control, not a ~A."
                      (pretty-name-of-view-class view-class)
                      type?))
    (values (dynamic-dialog-handle dialog?)
            (dialog-component-internal-id component?))))


;;; The function `native-window-info' returns an eval-list of information about
;;; the given window. We use this in lieu of KB-level view items, as well as for
;;; "closed" callbacks, where the actual native-window no longer exists by the
;;; time the callback is called.

(defun native-window-info (native-window)
  (with-temporary-gensym-float-creation native-window-info
    (loop for property in all-view-properties
          as value? = (get-view-property native-window property)
          when (and (not (inapplicable-view-property native-window property))
                    (or value? (include-null-window-property-p native-window property)))
            collect property using eval-cons and
            collect (make-evaluation-value-from-lisp-value value?) using eval-cons)))

(defun inapplicable-view-property (native-window property)
  (case property
    ((x-scale y-scale)
     (not (workspace-view-p native-window)))
    ((dock neighbor draggable close-action)
     (or (mdi-child-p native-window)
         (top-level-window-p native-window)))
    ((minimizeable maximizeable)
     (native-pane-p native-window))))

(defun include-null-window-property-p (native-window property)
  (cond ((mdi-child-p native-window)
         (memq property '(minimizeable maximizeable)))
        ((native-pane-p native-window)
         (memq property '(closeable floatable autohideable draggable)))))

(defun inapplicable-view-property-error (native-window property)
  (ui-stack-error "The ~A property cannot be set for ~A views."
                  property (native-window-container-type native-window)))


;;;; Views API: System Procedures

;; Settable properties. Cf all-view-properties.
(def-type-parameter workspace-view-properties-type
    (structure #.(append (cadr view-properties-type)
                         '((x-scale float)
                           (y-scale float)))))


(defun dock-native-window (native-window dock? neighbor?)
  (let ((plist (nconc (if dock? (gensym-list 'dock dock?))
                      (if neighbor? (gensym-list 'neighbor neighbor?)))))
    (setf (native-window-state native-window) 'docked)
    (when dock?
      (setf (native-window-dock native-window) dock?))
    (when neighbor?
      (setf (native-window-neighbor? native-window) neighbor?))
    (manage-pane-1 native-window 'dock plist)
    (reclaim-gensym-list plist)
    native-window))

(def-type-parameter pane-action-type
    (member select dock float show hide autohide toggle-docking destroy))

(defun pane-management-p (gensym-window)
  (and (twng-window-p gensym-window)
       (window-supports-manage-pane gensym-window))) ; TODO: Permit TW 8.1 ops?

;; TODO: Rename to g2-ui-manage-view g2-ui-manage-window ?
(defun-for-system-procedure g2-ui-manage-pane (action handle ev-arg g2-window)
  (check-type-or-stack-error action pane-action-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))

    (unless (pane-management-p gensym-window)
      (ui-stack-error "Management of docking panes is not supported on ~NF"
                      (g2-window-for-gensym-window? gensym-window)))

    (let* ((native-window (find-native-view-or-stack-error gensym-window handle nil))
           (arg (unbox-evaluation-value ev-arg)))
      (when (native-pane-p native-window)
        (case action
          (select
           (manage-pane-1 native-window arg nil))

          (dock
           (cond ((symbolp arg)                ; This is crazy.
                  (dock-native-window native-window arg nil))
                 ((fixnump arg)
                  (dock-native-window native-window nil arg))))

          (float
           (%set-native-window-state native-window 'floating))

          (show
           (%set-native-window-state native-window 'normal))

          (hide
           (%set-native-window-state native-window 'hidden))

          (autohide
           (%set-native-window-state native-window 'autohidden))

          (toggle-docking
           (manage-pane-1 native-window action nil))

          (destroy
           (manage-pane-1 native-window action nil)
           (reclaim-native-window native-window))))
      (reclaim-unboxed-evaluation-value arg)
      (reclaim-if-evaluation-value ev-arg)
      (reclaim-if-evaluation-value handle)
      action)))

;; Not exposed to users.
(defun-for-system-procedure g2-ui-get-view-property (handle property g2-window)
  (readable-view-property-or-stack-error property)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (native-window (find-native-window-or-stack-error gensym-window handle))
         (value? (get-view-property native-window property)))
      (reclaim-if-evaluation-value handle)
      ;; TODO: Distinguish NIL for doesn't apply from NIL for false.
    (make-evaluation-value-from-lisp-value value?)))

(defun-for-system-procedure g2-ui-modify-view (handle properties g2-window)
  (check-type-or-stack-error properties workspace-view-properties-type)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (native-window (find-native-window-or-stack-error gensym-window handle))
         (original-style nil)
         (style nil)
         (x-scroll? nil)
         (y-scroll? nil)
         (x-scale? nil)
         (y-scale? nil)
         (dock? nil)
         (neighbor? nil)
         (left? nil)
         (top? nil)
         (width? nil)
         (height? nil))

    ;; First process geometry changes, since they may affect style bits.
    (loop for (property . value) being each evaluation-structure-pair of properties
          doing (case property
                  (left (setq left? value))
                  (top (setq top? value))
                  (width (setq width? value))
                  (height (setq height? value))
                  (x-scale
                   (xy-scale-property-allowed-or-stack-error native-window)
                   (setq x-scale? value))
                  (y-scale
                   (xy-scale-property-allowed-or-stack-error native-window)
                   (setq y-scale? value))))

    (when (and native-window ; make compiler happy
               (native-image-plane? native-window)
               (or x-scale? y-scale?))
      (with-temporary-gensym-float-creation g2-ui-modify-view
        (show-workspace
          (workspace-on-image-plane? (native-image-plane? native-window))
          (g2-window-for-gensym-window? gensym-window)
          nil nil nil nil nil nil nil nil nil nil nil
          (if x-scale? (managed-float-value x-scale?))
          (if y-scale? (managed-float-value y-scale?)))))

    (when (or left? top? width? height?)
      (let ((left (or left? (native-window-left native-window)))
            (top (or top? (native-window-top native-window)))
            (width (or width? (native-window-width native-window)))
            (height (or height? (native-window-height native-window))))
        (reshape-native-window native-window left top (+f left width) (+f top height))
        (when (native-image-plane? native-window)
          ;; We need this rigamarole in case scroll bars were added or removed
          ;; as a result of the reshape.  TODO: Write code to do this in one
          ;; step.
          (canonicalize-scroll-position (native-image-plane? native-window))
          (reshape-native-window native-window left top (+f left width) (+f top height))
          (canonicalize-scroll-position (native-image-plane? native-window)))))

    ;; Sample the current style.
    (setq original-style (native-window-style native-window)
          style original-style)

    ;; Process all of the other properties.
    (loop for (property . value) being each evaluation-structure-pair of properties
          as torf = (and (evaluation-boolean-p value)
                         (evaluation-boolean-is-true-p value))
          doing
      (case property
        (callback
         (when (native-view-p native-window)
           (when (symbolp value)
             (set-view-property native-window 'callback value))))
        (title
         (%set-native-window-title native-window value))
        (visible-caption
         (cond ((native-pane-p native-window)
                )                        ; TODO: Needs Codejock feature in XTP 9.70
               (t
                (setf-bits style ws-caption torf))))
        (icon
         (valid-icon-designation-or-stack-error value)
         (%set-native-window-icon native-window value))

        (state
         (%set-native-window-state native-window value))
        (dock
         (if (native-pane-p native-window)
             (setq dock? value)
             (inapplicable-view-property-error native-window property)))
        (neighbor
         (cond ((native-pane-p native-window)
                (let ((native-window (find-native-window-or-stack-error gensym-window value)))
                  (setq neighbor? (native-window-handle native-window))))
               (t
                (inapplicable-view-property-error native-window property))))
        (floatable
         (or (%set-native-window-floatable native-window torf)
             (inapplicable-view-property-error native-window property)))

        (autohideable
         (or (%set-native-window-autohideable native-window torf)
             (inapplicable-view-property-error native-window property)))

        (draggable
         (or (%set-native-window-draggable native-window torf)
             (inapplicable-view-property-error native-window property)))

        (closeable
         (%set-native-window-closeable native-window torf))

        (minimizeable
         (if (or (mdi-child-p native-window)
                 (top-level-window-p native-window))
             (setf-bits style ws-minimizebox torf)
             (inapplicable-view-property-error native-window property)))
        (maximizeable
         (if (or (mdi-child-p native-window)
                 (top-level-window-p native-window))
             (setf-bits style ws-maximizebox torf)
             (inapplicable-view-property-error native-window property)))
        (resizeable
         (if (or (mdi-child-p native-window)
                 (top-level-window-p native-window))
             (setf-bits style ws-thickframe torf)
             (inapplicable-view-property-error native-window property)))

        (close-action
         (or (%set-native-window-close-action native-window (if (eq value 'hide) 'hide 'destroy))
             (inapplicable-view-property-error native-window property)))

        (x-scroll-bar)                        ; Must set flags on image-plane, else they'll come back.
        (y-scroll-bar)                        ; NEVER, ALWAYS, AUTOMATIC
        (x-scroll-position
         (setq x-scroll? value))
        (y-scroll-position
         (setq y-scroll? value))))

    (reclaim-evaluation-structure properties)
    (reclaim-if-evaluation-value handle)

    (when (or dock? neighbor?)
      (let ((plist (nconc (if dock? (gensym-list 'dock dock?))
                          (if neighbor? (gensym-list 'neighbor neighbor?)))))
        (when dock?
          (setf (native-window-dock native-window) dock?))
        (when neighbor?
          (setf (native-window-neighbor? native-window) neighbor?))
        (manage-pane-1 native-window 'dock plist)
        (reclaim-gensym-list plist)))

    (when (or x-scroll? y-scroll?)
      (cond ((native-image-plane? native-window)
             (scroll-image-plane-to (native-image-plane? native-window)
                                    (or x-scroll? (native-window-x-scroll? native-window) 0)
                                    (or y-scroll? (native-window-y-scroll? native-window) 0)))
            (t
             ;; TODO: Scroll tree-views, html-views, etc.
             )))

    (when (/=f style original-style)
      (%set-native-window-style native-window style))))


(defun xy-scale-property-allowed-or-stack-error (native-window)
  (unless (native-image-plane? native-window)
    (ui-stack-error "The X-SCALE and Y-SCALE properties apply only to workspace views, not ~As."
                    (pretty-name-of-view-class (native-window-class native-window)))))


;;;; Views API: Support


;; FIXME: hack, until we unify these. Only used for DESTROY and PRINT at the moment.
(defun manage-view (view action arg)
  (case (native-window-class view)
    (g2-workspace-view (manage-workspace-view view action arg))
    (g2-tree-view (manage-tree-view view action arg))
    (g2-html-view (manage-html-view view action arg))
    (g2-shortcut-bar (manage-shortcut-bar view action arg))
    (g2-chart-view (manage-chart-view view action arg))
    (g2-dialog-view nil)                ; FIXME: Implement this.
    (g2-output-view (manage-logbook-view view action arg))
    (g2-property-grid (manage-property-grid view action arg))
    (g2-tabular-view (manage-tabular-view view action arg))
    (t #+development
       (cerror "Go on" "Unknown class of view ~s" (native-window-class view)))))

;; FIXME: hack. Needs to operate on the image-plane, too.
(defun manage-workspace-view (view action arg)
  (case action
    (show (show-native-window view))
    (select (show-native-window view)) ; Same as show
    (hide (show-native-window view sw-hide))        ; Does this do anything?
    (minimize (show-native-window view sw-minimize))
    (maximize (show-native-window view sw-maximize))
    (restore (show-native-window view sw-shownormal))
    (raise (raise-native-window view)) ; Do nothing for docked panes.
    (lower (lower-native-window view))
    (caption (caption-native-window view arg))
    (destroy (destroy-native-window view))))

;;; The function `native-window-is-transient-p' returns true for views which
;;; should be destroyed on reset.  For no really good reason, all native views
;;; are transient, *except* for workspace views (native image-planes), and the
;;; logbook.

(defun native-window-is-transient-p (native-window)
  (and (not (workspace-view-p native-window))
       (not (native-logbook-p native-window))))

;;; The function `note-kb-reset-for-native-views' destroys all transient views
;;; on reset.  For no really good reason, all native views are transient,
;;; *except* for workspace views and the native logbook.

(defun note-kb-reset-for-native-views ()
  (loop for workstation in workstations-in-service
        as gensym-window = (window-for-workstation workstation)
        doing
    (when (and (eq (workstation-login-state workstation) 'logged-in)
               (or (nms-controls-p gensym-window)
                   (chart-views-p gensym-window)) ; Charts allowed in multiwindow tw.
               (window-supports-tree-views gensym-window))
      (for-workstation (workstation)
        (do-native-windows (native-window gensym-window)
          (when (or (native-window-is-transient-p native-window)
                    (and in-clear-kb-p (native-logbook-p native-window)))
            (manage-view native-window 'destroy nil)
            (reclaim-native-window native-window)))))))

;;; The function `note-native-window-event' is called from some of the generic
;;; native-window event handlers down in PANES.

(defun note-native-window-event (event native-window)
  (when (native-view-callback? native-window)
    (invoke-view-callback native-window event 'none
                          (native-window-info native-window)
                          'none)))


;;;; Workspace Views


(def-type-parameter workspace-view-options-type
    (structure
      #.(append
          (cadr view-properties-type)
          '((x-scale float)
            (y-scale float)
            (handle integer)                ; Not settable, for convenience only.
            (class symbol)))))

;;; The function `g2-ui-create-workspace-view' is just "show workspace" with
;;; more options available, in particular scroll bar positions and window size.

(defun-for-system-procedure g2-ui-create-workspace-view (workspace options g2-window)
  (check-type-or-stack-error options workspace-view-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (mdi-frame-p gensym-window)
      (ui-stack-error "Workspace views are not supported on ~NF" g2-window))
    (unless (workspaces-can-be-shown-at-this-kb-level-p
              workspace (workstation-this-is-on gensym-window))
      (ui-stack-error "Showing workspace ~NF is restricted." workspace))
    (unless (eq (evaluation-structure-slot options 'container 'mdi-child)
                'mdi-child)
      (ui-stack-error "Unsupported container for workspace views: ~NV."
                      (evaluation-structure-slot options 'container)))
    (with-temporary-gensym-float-creation g2-ui-create-workspace-view
      (let* ((image-plane (image-plane-of-workspace-on-window gensym-window workspace))
             (workstation (workstation-this-is-on gensym-window))
             (options* (unbox-evaluation-value options))
             (icon? (getf options* 'icon))
             (state? (getf options* 'state))
             (x-scale? (getf options* 'x-scale))
             (y-scale? (getf options* 'y-scale))
             (x-scale (if x-scale?
                          (round (* (managed-float-value x-scale?) (normalized-scale)))
                          (normalized-scale)))
             (y-scale (if y-scale?
                          (round (* (managed-float-value y-scale?) (normalized-scale)))
                          (normalized-scale)))
             (native-window nil))
        (when icon?
          (valid-icon-designation-or-stack-error icon?))

        (for-workstation (workstation)
          (when image-plane                        ; We permit at most one workspace view/window.
            (delete-image-plane image-plane))
          (setq image-plane (get-available-image-plane
                              (detail-pane gensym-window)
                              (lookup-frame-description-reference-of-block? workspace)
                              nil))
          (let ((native-image-plane-options options*))
            (put-image-on-image-plane image-plane workspace x-scale y-scale
                                      nil nil nil nil nil nil)
            (canonicalize-scroll-position image-plane))
          (setq native-window (image-plane-native-window? image-plane))
          (when icon?
            (%set-native-window-icon native-window icon?))

          (scroll-image-plane-to image-plane
                                 (getf options* 'x-scroll-position 0)
                                 (getf options* 'y-scroll-position 0))
          (when state?
            (%set-native-window-state native-window state?)))

        (reclaim-unboxed-evaluation-value options*)
        (native-window-handle native-window)))))


;;;; Tree Views


(def-type-parameter tree-view-options-type
    (structure
      #.(append                                        ; Yuck: why doesn't #, seem to work?
          (cadr view-properties-type)
          '((infer-icon-from-node-name truth-value)
            (right-click-selects-node truth-value) ; Default is true
            (tree item-or-datum)                ; Initial contents (item-or-value)
            (default-icon item-or-datum)
            (default-leaf-icon item-or-datum)
            (default-folder-icon item-or-datum)))))

(def-type-parameter tree-view-modify-node-type
    (structure
      ((label text)
       (tooltip text)
       (icon item-or-datum)
       (selected-icon item-or-datum)
       (bold truth-value)
       (expand truth-value))))

(def-type-parameter tree-view-insert-node-options-type
    (structure
      ((position (member first after last)))))

(defparameter tree-view-ex-operations        ; Supported in TW 82r0
  '(insert set-indent set-item-height set-background-color set-foreground-color set-insert-mark-color
    select-node delete-node edit-node expand-node collapse-node))

(defparameter tree-view-82r1-operations '(modify-node))

(def-structure (tree-view
                 (:include native-view)
                 (:constructor make-tree-view-1)
                 (:reclaimer reclaim-tree-view-1)
                 #+development (:print-function print-native-window))
  (tree-view-default-leaf-icon? nil)
  (tree-view-default-folder-icon? nil)
  (tree-view-infer-icon-from-name-p nil) ; Get class/stock icon name from node name.
  (tree-view-options nil)
  (tree-view-handle-base 1)              ; Doesn't change any more (free handles are reclaimed)
  (tree-view-handle-next 1)                ; Reserve 0 handle to indicate none.
  (tree-view-nodes nil)                        ; Flat array of nodes, indexed by handle - base
  (tree-view-hash nil)
  (tree-view-free-handles nil  ; List of free handles 
                          :reclaimer reclaim-gensym-list))


(def-structure (tree-view-node
                 (:constructor make-tree-view-node-1)
                 (:reclaimer reclaim-tree-view-node-1)
                 #+development (:print-function print-tree-view-node))
  (tree-view-node-handle 0)
  (tree-view-node-ev-node nil)
  (tree-view-node-evalue nil)                ; The user node: an evaluation-value. Supplied to callback.
  (tree-view-node-label nil)                ; Usually shared with evalue, or, a symbol's pname
  (tree-view-node-flags 0)
  (tree-view-node-parent nil)
  (tree-view-node-children nil)
  (tree-view-node-icon nil :reclaimer reclaim-icon-hash-key)
  (tree-view-node-selected-icon nil :reclaimer reclaim-icon-hash-key))

#+development
(defun print-tree-view-node (node stream depth)
  (declare (ignore depth))
  (printing-random-object (node stream)
    (format stream "TREE-VIEW-NODE ~a [~d]" (tree-view-node-label node) (tree-view-node-handle node))))

(def-class (g2-tree-view g2-native-view (foundation-class g2-tree-view)
                         do-not-put-in-menus not-user-instantiable)
  (%tree-view-structure nil vector-slot system)
  (g2-tree-structure nil (type structure) not-user-editable vector-slot no-accessor))

(defun make-tree-view (gensym-window callback container options)
  (let ((tv (make-tree-view-1)))
    (initialize-native-view tv gensym-window 'g2-tree-view container options callback)
    (let ((default-icon? (getf options 'default-icon)))
      (setf (tree-view-default-leaf-icon? tv) (getf options 'default-leaf-icon default-icon?)
            (tree-view-default-folder-icon? tv) (getf options 'default-folder-icon default-icon?)
            (tree-view-infer-icon-from-name-p tv) (getf options 'infer-icon-from-node-name)))
    tv))

(def-structure-method clean-up-structure (tree-view)
  (tree-view-clear tree-view)
  (funcall-superior-method tree-view))

(defun reclaim-tree-view (tv)
  (reclaim-native-window tv))

(defmacro flag-set-p (value mask)
  `(/=f 0 (logandf ,value ,mask)))

;; Label is copied.
(defun set-tree-view-node-label (node label?)
  (when (flag-set-p (tree-view-node-flags node) tvf-reclaim-label) ; Ick.
    (reclaim-if-text-string (tree-view-node-label node)))
  (setf (tree-view-node-label node) (copy-if-text-string label?))
  (setf-bits (tree-view-node-flags node) tvf-reclaim-label (wide-string-p label?))
  label?)

(defun reclaim-tree-view-node (tree-view node)
  ;; Remove from hash table
  (when (tree-view-hash tree-view)
    (item-or-name-hash-remove (tree-view-node-item-or-name node)
                              (tree-view-node-handle node)
                              (tree-view-hash tree-view)))
  ;; Remove from array
  (let* ((handle? (tree-view-node-handle node))
        (index (-f handle?
                   (tree-view-handle-base tree-view))))
    (gensym-push handle? (tree-view-free-handles tree-view))
    (setf (managed-svref (tree-view-nodes tree-view) index) nil))
  ;; Remove from parent's list
  (let ((parent? (and (tree-view-node-parent node)
                      (tree-view-ref tree-view (tree-view-node-parent node)))))
    (when parent?
      (setf (tree-view-node-children parent?)
            (delete-gensym-element (tree-view-node-handle node)
                                   (tree-view-node-children parent?)))))
  
  (reclaim-gensym-list (tree-view-node-children node))
  
  (set-tree-view-node-label node nil)
  
  (reclaim-if-evaluation-value (tree-view-node-ev-node node))
  (setf (tree-view-node-ev-node node) nil)
  
  (reclaim-if-evaluation-item-reference (tree-view-node-evalue node))
  (setf (tree-view-node-evalue node) nil)
  
  (setf (tree-view-node-label node) nil
        (tree-view-node-parent node) nil
        (tree-view-node-children node) nil)
  (reclaim-tree-view-node-1 node))

(defmacro do-tree-view-nodes ((node tree-view) &body body)
  (avoiding-variable-capture (tree-view &aux nodes i)
    `(let ((,nodes (tree-view-nodes ,tree-view)))
       (when ,nodes
         (loop for ,i from 0 below (-f (tree-view-handle-next ,tree-view)
                                       (tree-view-handle-base ,tree-view))
               as ,node = (managed-svref ,nodes ,i)
               doing
           (when (tree-view-node-p ,node)
             ,@body))))))

;;; The function `tree-view-allocate-node' allocates a unique integer handle for
;;; given user-node.  The user-node (evalue) becomes owned by the
;;; tree-view. Handles are reused within a tree-view instance.

(defun tree-view-allocate-node (tree-view evalue label flags children)
  (let* ((handle (or (gensym-pop (tree-view-free-handles tree-view))
                     (prog1 (tree-view-handle-next tree-view)
                       (incff (tree-view-handle-next tree-view)))))
         (index (-f handle (tree-view-handle-base tree-view)))
         (node (make-tree-view-node-1)))
    (cond ((null (tree-view-nodes tree-view))
           (setf (tree-view-nodes tree-view)
                 ;; GENSYMCID-856: g2-ui-clear-tree-view causes G2 abort.
                 ;; If (tree-view-nodes tree-view) is null but index >= 256, just
                 ;; allocate a 256 sized array is NOT enough, more spaces needed!
                 (allocate-managed-array (maxf 256 (ashf 1 (1+f (g-logf index)))))))
          ((>=f index (managed-array-length (tree-view-nodes tree-view)))
           (setf (tree-view-nodes tree-view)
                 (adjust-managed-array (tree-view-nodes tree-view)
                                       (ashf 1 (1+f (g-logf index)))))))
    (setf (tree-view-node-handle node) handle
          (tree-view-node-evalue node) (get-reference-to-item-if-item evalue) ; User's structure for node.
          (tree-view-node-label node) (if (symbolp label) (symbol-namew label) label)
          (tree-view-node-flags node) flags
          (tree-view-node-children node) (loop for (nil child-handle) in children
                                               collect child-handle using gensym-cons))
    ;; Set parent links
    (loop for child-handle in (tree-view-node-children node)
          as child? = (tree-view-ref tree-view child-handle)
          when child?
            do (setf (tree-view-node-parent child?) handle))

    ;; Add to array
    (setf (managed-svref (tree-view-nodes tree-view) index) node)
    ;; Add to hash table
    (unless (tree-view-hash tree-view)
      (setf (tree-view-hash tree-view) (make-item-or-name-hash)))
    (item-or-name-hash-put (tree-view-node-item-or-name node)
                           (tree-view-node-handle node)
                           (tree-view-hash tree-view))
    node))

(defun tree-view-ref (tree-view handle)
  (let* ((array? (tree-view-nodes tree-view))
         (index (-f handle (tree-view-handle-base tree-view))))
    (when (and array?
               (<=f 0 index (1-f (managed-array-length array?))))
      (managed-svref array? index))))

;; Maintains parent/child links.
(defun tree-view-insert-node-locally (tree-view reference-handle node-handle position?)
  (let ((reference? (tree-view-ref tree-view reference-handle))
        (node? (tree-view-ref tree-view node-handle))
        (parent? nil))
    (cond ((null reference?))
          ((null node?))
          ((memq position? '(nil first last)) ; reference is parent node
           (setq parent? reference?))
          (t                                ; reference is sibling node
           (setq parent? (and (tree-view-node-parent reference?)
                              (tree-view-ref tree-view (tree-view-node-parent reference?))))))
    (when parent?
      (setf (tree-view-node-parent node?) (tree-view-node-handle parent?))
      (case position?
        ((nil last)
         (setf (tree-view-node-children parent?)
               (nconc (tree-view-node-children parent?) (gensym-list node-handle))))
        (first
         (setf (tree-view-node-children parent?)
               (gensym-cons node-handle (tree-view-node-children parent?))))
        (after
         (let ((new-children
                 (loop for child-handle in (tree-view-node-children parent?)
                       collect child-handle using gensym-cons
                       if (eql reference-handle child-handle)
                         collect node-handle using gensym-cons)))
           (reclaim-gensym-list (tree-view-node-children parent?))
           (setf (tree-view-node-children parent?) new-children)))))
    node?))

(defun free-tree-view-node-icon (gensym-window? icon-designation?)
 (when (and icon-designation? gensym-window? (native-icons-table? gensym-window?))
  (multiple-value-bind (handle? small-p large-p)
      (find-native-icon gensym-window? icon-designation?)
    (declare (ignore small-p large-p))
    (when handle?
      (gensym-push handle? (free-icon-handles gensym-window?)))
    (delete-native-icon-handle icon-designation? (native-icons-table? gensym-window?)))))

(defun free-tree-view-node-icons (tree-view node)
  (let* ((gensym-window (native-window-gensym-window tree-view)))
    (free-tree-view-node-icon gensym-window (tree-view-node-selected-icon node))
    (free-tree-view-node-icon gensym-window (tree-view-node-icon node)))) 

(defun tree-view-delete-node-locally (tree-view node-handle)
  (let ((node? (tree-view-ref tree-view node-handle)))
    (when node?
      (loop for child in (tree-view-node-children node?) doing
        (tree-view-delete-node-locally tree-view child))
      (free-tree-view-node-icons tree-view node?)
      (reclaim-tree-view-node tree-view node?))))

(defun tree-view-node-item-or-name (node)
  (let ((ev (tree-view-node-evalue node)))
    (cond ((evaluation-item-reference-p ev)
           ev)
          ((evaluation-symbol-p ev)
           (evaluation-symbol-symbol ev))
          ((evaluation-text-p ev)
           (evaluation-text-value ev))
          ((evaluation-structure-p ev)
           (evaluation-structure-slot ev 'item-or-name)))))

(defun tree-view-node-getprop (node property)
  (let ((ev (tree-view-node-evalue node)))
    (case property
      (label (tree-view-node-label node))
      (flags (tree-view-node-flags node))
      ((item-or-name item)
       (cond ((evaluation-item-reference-p ev)
              (evaluation-item-reference-referenced-item ev))
             ((evaluation-structure-p ev)
              (evaluation-structure-slot ev property))))
      (t
       (when (evaluation-structure-p ev)
         (evaluation-structure-slot ev property))))))

;; Set a node property in the G2-side cache.
(defun tree-view-node-setprop (node property value)
  (case property
    (label (set-tree-view-node-label node value))
;   (tooltip)
;   (icon)
;   (selected-icon)
    (bold (setf-bits (tree-view-node-flags node) tvf-bold value))
    (expand (setf-bits (tree-view-node-flags node) tvf-expand value))))

;; Modify node in G2 and TW.
(defun tree-view-modify-node (tree-view node-handle plist)
  (let ((node? (tree-view-ref tree-view node-handle)))
    (when node?
      (loop for (property value) on plist by #'cddr do
        (tree-view-node-setprop node? property value))
      (let ((plist* (gensym-cons 'node (gensym-cons node-handle plist))))
        (manage-tree-view tree-view 'modify-node plist*)
        (reclaim-gensym-cons (cdr plist*))
        (reclaim-gensym-cons plist*)))))

(defun tree-view-find-node-by-label (tree-view label)
  (do-tree-view-nodes (node tree-view)        ; TODO: hash table for this, too.
    (when (equalw label (tree-view-node-label node))
      (return (tree-view-node-handle node)))))

(defun tree-view-find-node-by-name (tree-view item-or-name)
  (when (tree-view-hash tree-view)
    (car-or-atom (item-or-name-hash-get item-or-name (tree-view-hash tree-view)))))

;;; The function `tree-view-find-node' returns the node handle for a node
;;; designation, or NIL if none. Use `tree-view-ref' to get the node from the
;;; handle.

(defun tree-view-find-node (tree-view ev-node-designation)
  (cond ((or (evaluation-boolean-p ev-node-designation)
             (eq ev-node-designation 'root))
         0)
        ((evaluation-integer-p ev-node-designation)
         (if (tree-view-ref tree-view (evaluation-integer-value ev-node-designation))
             (evaluation-integer-value ev-node-designation)))
        ((evaluation-text-p ev-node-designation)
         (tree-view-find-node-by-label tree-view (evaluation-text-value ev-node-designation)))
        ((or (framep ev-node-designation)
             (symbolp ev-node-designation))
         (tree-view-find-node-by-name tree-view ev-node-designation))))

(defun tree-view-find-node-or-stack-error (tree-view ev-node-designation)
  (or (tree-view-find-node tree-view ev-node-designation)
      (ui-stack-error "The node ~NA was not found in tree-view ~D."
                      ev-node-designation
                      (native-window-handle tree-view))))

(defun tree-view-clear (tree-view)
  (let ((nodes (tree-view-nodes tree-view)))
    (when nodes
      (loop for i from 0 below (-f (tree-view-handle-next tree-view)
                                   (tree-view-handle-base tree-view))
            as node? = (managed-svref nodes i)
            when (tree-view-node-p node?)
              do (reclaim-tree-view-node tree-view node?))
      (reclaim-managed-array nodes)
      (setf (tree-view-nodes tree-view) nil)))

  (when (tree-view-hash tree-view)
    (clear-item-or-name-hash (tree-view-hash tree-view))
    (reclaim-item-or-name-hash (tree-view-hash tree-view))
    (setf (tree-view-hash tree-view) nil))

  ;; Reclaim all of the evaluation values handed to us by the user.
  (reclaim-if-evaluation-value (tree-view-options tree-view))
  (setf (tree-view-options tree-view) nil)

  tree-view)

(defun tree-views-p (gensym-window)
 (and (nms-controls-p gensym-window) ; TWNG
      (window-supports-tree-views gensym-window)))

(defun check-tree-view-version-or-stack-error (gensym-window &optional operation)
  (let ((g2-window (g2-window-for-gensym-window? gensym-window)))
    (unless (tree-views-p gensym-window)
      (ui-stack-error "Tree views are not supported on ~NF" g2-window))
    (when (or (and (memq operation tree-view-ex-operations)
                   (not (window-supports-tree-views-ex gensym-window)))
              (and (memq operation tree-view-82r1-operations)
                   (not (window-supports-modify-node gensym-window))))
      (ui-stack-error "Tree views on ~NF do not support the ~A operation."
                      g2-window operation))))

(defmacro with-tree-view ((tv handle g2-window &optional operation) &body body)
  `(let ((gensym-window (map-to-gensym-window-or-stack-error ,g2-window))
         (,tv nil))
     (check-tree-view-version-or-stack-error gensym-window ,operation)
     (setq ,tv (find-native-view-or-stack-error gensym-window ,handle 'g2-tree-view))
     ,@body))

(defmacro with-tree-view-sysproc ((tv node ev-handle ev-node g2-window) &body body)
  `(let* ((gensym-window (map-to-gensym-window-or-stack-error ,g2-window))
          (,tv (find-native-view-or-stack-error gensym-window handle 'g2-tree-view))
          (,node (tree-view-ref ,tv (tree-view-find-node-or-stack-error tv ev-node))))
     (prog1 (progn ,@body)
       (reclaim-if-evaluation-value ,ev-handle)
       (reclaim-if-evaluation-value ,ev-node))))

;;; The function `tree-view-node-returned-evalue' determines the evaluation
;;; value we return to the user for a node, as used by the various inquiry
;;; system procedures and the callback.  It is unfortunate that this value is
;;; fixed and is not updated as child nodes are added and removed, but that has
;;; been our convention.

(defun tree-view-node-returned-evalue (node?)
  (cond ((null node?)
         evaluation-false-value)
        ((evaluation-item-reference-p (tree-view-node-evalue node?))
         (evaluation-item-reference-referenced-item (tree-view-node-evalue node?)))
        (t
         (copy-if-evaluation-value (tree-view-node-evalue node?)))))

(defun manage-tree-view (tv action arg)
  (let ((gensym-window (native-window-gensym-window tv))
        (handle (native-window-handle tv)))
    (when (tree-views-p gensym-window)
      (when (icp-window-p gensym-window)
        (with-icp-window (gensym-window)
          (send-icp-manage-tree-view gensym-window action handle arg))))))

;; TODO: begin-drag, dropped?
(defun tree-view-event-name (event-code keycode)
  (case event-code
    (1 'select)                                ; Keep in sync with twng/c/TreeView.h
    (2 (mouse-click-event-name 'right-click keycode))
    (3 'key-pressed)
;    (4 'closed)                        ; Handled as a generic view event
    (5 'node-expanded)
    (6 'node-collapsed)
    (7 'edited)
    (8 (mouse-click-event-name 'left-click keycode))
    (9 (mouse-click-event-name 'middle-click keycode))))

(define-event-handler handle-tree-view-message ((gensym-window window) event-plist x-in-window y-in-window)
  (let* ((handle (getf event-plist 'handle 0))
         (tv? (find-native-window gensym-window handle 'g2-tree-view))
         (node-handle (getf event-plist 'item 0))
         (node? (if tv? (tree-view-ref tv? node-handle)))
         (label? (getf event-plist 'value))
         (keycode (getf event-plist 'key 0))
         (event-code? (getf event-plist 'event))
         (event? (tree-view-event-name event-code? keycode)))
    (when (and tv? event?)
      (multiple-value-bind (user-window-x user-window-y)
          (gensym-window-point-to-user-window-point gensym-window x-in-window y-in-window)
        (let ((keysym? (if (and (>f keycode 0)
                                (eq event? 'key-pressed))
                           (parseable-symbol-from-key-code (canonicalize-key-code keycode)))))
          (invoke-view-callback tv? event?
                                label?
                                (nconc
                                  (eval-list 'x user-window-x 'y user-window-y)
                                  (if keysym? (eval-list 'key keysym?)))
                                ;; TODO: Use tree-view-node-returned-evalue
                                (if node? (tree-view-node-evalue node?))))))))

;;; Gensym-121 fix
(defun update-icon-views-property (icon?)
  (when (and icon? (framep icon?))
    (setf (item-has-icon-views-p icon?) t)))
  
;;; The function `create-tree-from-structure-hierarchy' creates a gensym-tree
;;; from a hierarchy of evaluation structures, allocating node handles within
;;; the tree-view instance to save node information locally (in G2).
;;;
;;; The resulting gensym-tree is sent over ICP and ultimately interpreted by
;;; `populate-tree-view' in NATIVE-TW.
;;;
;;; The input tree is as returned by g2-get-workspace-hierarchy and friends:
;;;
;;;    structure(item-or-name, children, &allow-other-keys)
;;;
;;; with these keys recognized, and other keys ignored:
;;;
;;;    item-or-name  - Symbol, string, or G2 item
;;;    children      - Sequence of child nodes
;;;    icon          - Symbol or instance designating icon for node
;;;    selected-icon - Icon for selected node (eg, an open folder icon)
;;;    expand        - Initially show the children of node.
;;;    bold          - Show node label in bold face
;;;    label         - Label for node, instead of deriving from item-or-name
;;;    tooltip       - Tooltip for node, instead of using label
;;;
;;; The constructed gensym-tree, sent over ICP:
;;;
;;;    tree  = (label handle (tree ... tree) icons flags tooltip ...)
;;;    label = symbol | string
;;;
;;; The strings, if any, are SHARED with the structure. The tree-view object is
;;; used to record handles for each node in the tree.

  
;; Can STACK-ERROR
(defun create-tree-from-structure-hierarchy (tree-view structure-node)
  (multiple-value-bind (label? children? icon? selected-icon? flags? tooltip?)
      (tree-view-parse-structure-node tree-view structure-node)
    (when label?
       ;; Gensym-121 fix
      (update-icon-views-property icon?)
      (let* ((gensym-window
               (native-window-gensym-window tree-view))
             (icon-handle? (if icon? (send-native-icon gensym-window icon?)))
             (selected-icon-handle? (if selected-icon?
                                        (send-native-icon gensym-window selected-icon?)))
             (icons (gensym-cons-or-atom icon-handle? selected-icon-handle?))
             (children
               (when (evaluation-sequence-p children?)
                 (loop for child being each evaluation-sequence-element of children?
                       as subtree? = (create-tree-from-structure-hierarchy tree-view child)
                       when subtree?
                         collect it using gensym-cons)))
             (node (tree-view-allocate-node
                     tree-view structure-node label? (or flags? 0) children))
             (handle (tree-view-node-handle node)))
        
        ;; initialize node
        (when icon?
          (setf (tree-view-node-icon node) (make-icon-hash-key icon?)))
        (when selected-icon?
          (setf (tree-view-node-selected-icon node) (make-icon-hash-key selected-icon?)))

        ;; Optimize the list a little bit.
        (cond ((null (or children icons flags? tooltip?))
               (gensym-list label? handle))
              ((null (or icons flags? tooltip?))
               (gensym-list label? handle children))
              ((null (or flags? tooltip?))
               (gensym-list label? handle children icons))
              ((null tooltip?)
               (gensym-list label? handle children icons flags?))
              (t
               (gensym-list label? handle children icons flags? tooltip?)))))))

;; Can STACK-ERROR
;; (values label children icon selected-icon expand? tooltip?)
(defun tree-view-parse-structure-node (tree-view node)
  (multiple-value-bind (item-or-name? children? icon? selected-icon? label? flags? tooltip?)
      (if (evaluation-structure-p node)
          (values (evaluation-structure-slot node 'item-or-name)
                  (evaluation-structure-slot node 'children)
                  (tree-view-get-icon-or-stack-error node 'icon)
                  (tree-view-get-icon-or-stack-error node 'selected-icon)
                  (evaluation-structure-slot node 'label)
                  (tree-view-compute-node-flags node)
                  (evaluation-structure-slot node 'tooltip))
          (values node nil nil nil nil nil nil))
    ;; FIXME: Type-check more stuff.
    (when item-or-name?
      (values (or label? (tree-view-compute-node-label item-or-name?))
              children?
              (or icon? (tree-view-default-icon tree-view item-or-name? children?))
              selected-icon?
              flags?
              tooltip?))))

(defun estructure-slot-true-p (estructure slot)
  (let ((value (evaluation-structure-slot estructure slot)))
    (and (evaluation-boolean-p value)
         (evaluation-boolean-is-true-p value))))

(defun tree-view-compute-node-flags (node)
  (let ((flags
          (logiorf
            (if (evaluation-structure-slot node 'children) tvf-children 0)
            (if (estructure-slot-true-p node 'bold)     tvf-bold 0)
            (if (estructure-slot-true-p node 'expand)   tvf-expand 0)
            (if (estructure-slot-true-p node 'check)    tvf-check 0))))
    (when (/=f flags 0)
      flags)))

;; Can STACK-ERROR
(defun tree-view-get-icon-or-stack-error (node attribute-name)
  (let ((icon? (evaluation-structure-slot node attribute-name)))
    (cond ((null icon?)
           nil)
          ((valid-icon-designation-p icon?)
           icon?)
          (t
           (ui-stack-error "The ~A attribute in ~NA is invalid: ~A."
                           attribute-name node
                           (explanation-for-type-error?
                             icon? '(or symbol text datum (no-item))))))))

(defun tree-view-default-icon (tree-view item-or-name? children?)
  (let ((icon-designation?
          (cond ((tree-view-infer-icon-from-name-p tree-view)
                 (cond ((null item-or-name?)
                        nil)
                       ((symbolp item-or-name?)
                        item-or-name?)
                       ((stringpw item-or-name?)
                        (intern-wide-string-no-reclaim item-or-name?))
                       ((of-class-p-function item-or-name? 'class-definition)
                        (name-of-defined-class item-or-name?))
                       ((framep item-or-name?)
                        item-or-name?)))
                ((framep item-or-name?)                ; If not inferring icon from node name, then
                 item-or-name?))))                ; only do so if item-or-name is an item.
    (cond ((valid-icon-designation-p icon-designation?)
           icon-designation?)
          ((and (evaluation-sequence-p children?)
                (not (evaluation-sequence-empty-p children?)))
           (tree-view-default-folder-icon? tree-view))
          (t
           (tree-view-default-leaf-icon? tree-view)))))

(defun tree-view-compute-node-label (item-or-name?)
  (cond ((null item-or-name?)
         nil)
        ((or (stringpw item-or-name?)
             (symbolp item-or-name?))
         item-or-name?)
        ((of-class-p item-or-name? 'block)
         ;; Inspect uses the table-header, I think.
         (get-or-make-up-designation-for-block item-or-name?))))


(defun add-nodes-to-tree (tv nodes)
  (let ((tree (gensym-list nil -1 nodes))) ;; (label handle children)
    (manage-tree-view tv 'populate tree)
    (reclaim-gensym-tree tree)))

(defun add-root-evalues-to-tree (tv evalues part-size)
  (let* ((count 0)
         (handle nil)
         (children nil)
         (children-end nil))

    (loop for ev-root being each evaluation-sequence-element of evalues do
      (incff count)
      (let ((node (create-tree-from-structure-hierarchy tv ev-root)))
        (when node
        ;; add node to list
        ;; (setf children (nconc children (gensym-list node))) - too slow
        (cond ((not children)
                (setq children (gensym-list node))
                (setq children-end children))
              (t
                (nconc children-end (gensym-list node))
                (setq children-end (cdr children-end))))
        
        ;; get handle of 1st node to return it
        (unless handle
          (setq handle (second node)))
        
        ;; add nodes to tree
        (when (>=f count part-size)
          (setf count 0)
          (add-nodes-to-tree tv children)
          (setq children nil)))))
    
    ;; add rest of nodes
    (when children
      (add-nodes-to-tree tv children))

    handle))

(defun populate-tree-from-evalue (tv evalue)
  (cond ((evaluation-sequence-p evalue)
          (add-root-evalues-to-tree tv evalue 1000))
        (t
         (add-root-evalue-to-tree tv evalue))))

(defun add-root-evalue-to-tree (tv ev-root)
  (let* ((tree (create-tree-from-structure-hierarchy tv ev-root))
        (node-handle (when tree (second tree))))
    (when node-handle
      (manage-tree-view tv 'populate tree)
      (reclaim-gensym-tree tree))
    node-handle))

#+development
(defun check-tree-view (tv)
  (let ((count1 0)
        (count2 0)
        (count3 0))

    (format t "Array~%")
    (do-tree-view-nodes (node tv)
      (let ((other (tree-view-find-node-by-name tv (tree-view-node-item-or-name node))))
        (format t "[~d] ~40s ~s ~:s~%" count1 node other (tree-view-node-children node))
        (incff count1)))

    (format t "Hash~%")
    (loop for entry being each hash-value of (tree-view-hash tv)
          do (format t "[~d] ~s~%" count2 entry)
          do (incff count2 (cond ((null entry) 0)
                                 ((atom entry) 1)
                                 (t (length entry)))))

    (labels ((print-subtree (tv root &optional (indent 0))
               (format t "~v@t~s~%" indent root)
               (when root
                 (incff count3)
                 (loop for child-handle in (tree-view-node-children root)
                       as child? = (tree-view-ref tv child-handle)
                       doing (print-subtree tv child? (+ indent 2))))))
      (format t "Tree~%")
      (do-tree-view-nodes (node tv)
        (when (null (tree-view-node-parent node))
          (print-subtree tv node))))

    (format t "~d == ~d == ~d~%" count1 count2 count3)
    tv))


;;;; Tree View System Procedures


;;; The sysproc `g2-ui-create-tree-view' creates a new tree-view on given
;;; window and returns its handle.

(defun-for-system-procedure g2-ui-create-tree-view (title callback options g2-window)
  (check-type-or-stack-error options tree-view-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (check-tree-view-version-or-stack-error gensym-window)

    (let* ((ev-tree? (evaluation-structure-slot options 'tree))
           (options* (unbox-evaluation-value options '(tree)))
           (container (getf options* 'container 'pane)))
      (setq options* (mutate-gensym-plist options* 'label title))
      (let ((tv (make-tree-view gensym-window callback container options*)))
        (preprocess-view-options tv options*)
        (set-view-property tv 'title (copy-wide-string title)) ; Because tree-views use LABEL in options.
        (manage-tree-view tv 'create options*)
        (reclaim-unboxed-evaluation-value options*)
        (setf (tree-view-options tv) options)
        (when ev-tree?
          (populate-tree-from-evalue tv ev-tree?))
        (native-window-handle tv)))))

(defun native-window-class-if-any (handle g2-window)
  (let ((gensym-window? (map-g2-window-to-gensym-window g2-window)))
    (when gensym-window?
      (let ((native-window? (find-native-window gensym-window? handle)))
        (when native-window?
          (native-window-class native-window?))))))

;; This sysproc is generic on the view class, and has an unfortunate name. Used
;; generically for actions SELECT-NODE EXPAND-NODE COLLAPSE-NODE DELETE-NODE
(defun-for-system-procedure g2-ui-manage-tree-view (action handle ev-arg g2-window)
  (case (native-window-class-if-any handle g2-window)
    (g2-property-grid
     (g2-ui-manage-property-grid action handle ev-arg g2-window))
    (t
     (g2-ui-manage-tree-view-internal action handle ev-arg g2-window))))

(defun g2-ui-manage-tree-view-internal (action handle ev-arg g2-window)
  (with-tree-view (tv handle g2-window action)
    (let ((keep-ev-arg nil))
      (case action
        (populate                        ; TODO: Merge w/insert
         (let* ((node-handle (populate-tree-from-evalue tv ev-arg))
               (node (when node-handle (tree-view-ref tv node-handle))))
	    (when node
	      (setf (tree-view-node-ev-node node) ev-arg)
              (setq keep-ev-arg t))))

        (clear
		(manage-tree-view tv action nil)
		(tree-view-clear tv)

        ;; Project ID: 40432
        ;; Gensym-3039-TAM4-CM-BF-JIRA-47202
        ;; Color of toolbar buttons on TWNG cannot be changed after g2-ui-clear-tree-view is called.
        ;; Reason:
        ;;   This two line will delete the toolbar button's icon, so we comment it.
        ;; 24/3/2010
		; (let* ((gensym-window? (map-to-gensym-window-or-stack-error g2-window)))
		; (free-all-native-icon-handles-on-window gensym-window?))
        )

        ((close destroy)                ; Pane operations
         (manage-tree-view tv action nil)
         (reclaim-tree-view tv))

        ((hide select)                        ; Pane operations.
         (manage-tree-view tv action nil))

        (t
         (let ((arg (unbox-evaluation-value ev-arg)))
           (case action
             ;; TODO: Update local state.
             (select-item
              (manage-tree-view tv action arg))

             ((select-node edit-node expand-node collapse-node expand-all collapse-all)
              (let ((node-handle (tree-view-find-node-or-stack-error tv ev-arg)))
                (manage-tree-view tv action node-handle)))

             (delete-node
              (let ((node-handle (tree-view-find-node-or-stack-error tv ev-arg)))
                (tree-view-delete-node-locally tv node-handle)
                (manage-tree-view tv action node-handle)))

             ((set-background-color set-foreground-color set-insert-mark-color)
              (manage-tree-view tv action (rgb-value-of-gensym-color arg)))

             ((set-indent set-item-height
                          right-click-selects-node set-right-click-selects-node)
              (when (fixnump arg)
                (manage-tree-view tv action arg)))

             (t
              (dwarn "Unknown action in g2-ui-manage-tree-view: ~s" action)))
           (reclaim-unboxed-evaluation-value arg))))
      (unless keep-ev-arg
        (reclaim-if-evaluation-value ev-arg))
      (reclaim-if-evaluation-value handle))))

;;; The sysproc `g2-ui-insert-node' inserts a node (or an entire subtree) as a
;;; child or sibling, according to options, of the given reference node. It is
;;; generic on the view class.

(defun-for-system-procedure g2-ui-insert-node (handle ev-node reference options g2-window)
  (case (native-window-class-if-any handle g2-window)
    (g2-property-grid
     (g2-ui-insert-property-grid-node handle ev-node reference options g2-window))
    (t
     (g2-ui-insert-tree-view-node handle ev-node reference options g2-window))))

(defun g2-ui-insert-tree-view-node (handle ev-node parent options g2-window)
  (check-type-or-stack-error options tree-view-insert-node-options-type)
  (with-tree-view (tv handle g2-window 'insert)
    (let* ((parent-handle (tree-view-find-node-or-stack-error tv parent))
           (position? (evaluation-structure-slot options 'position))
           (tree (create-tree-from-structure-hierarchy tv ev-node))
           (node-handle (second tree))
           (node (tree-view-ref tv node-handle)))
      (let ((arg (nconc (gensym-list 'tree tree
                                     'parent parent-handle)
                        (if position? (gensym-list 'position position?)))))
        (tree-view-insert-node-locally tv parent-handle node-handle position?)
        (manage-tree-view tv 'insert arg)
        (setf (tree-view-node-ev-node node) ev-node)
        (reclaim-gensym-tree arg)
        (reclaim-if-evaluation-value handle)
        (reclaim-if-evaluation-value parent)
        (reclaim-evaluation-structure options)
        node-handle))))

;;; The function `g2-ui-modify-node' modifies selected properties of a node:
;;; label, tooltip, icon, selected-icon, bold, or expand.

(defun-for-system-procedure g2-ui-modify-node (handle ev-node changes g2-window)
  (case (native-window-class-if-any handle g2-window)
    (g2-property-grid
     (g2-ui-modify-property-grid-node handle ev-node changes g2-window))
    (t
     (g2-ui-modify-tree-view-node handle ev-node changes g2-window))))

(defun g2-ui-modify-tree-view-node (handle ev-node changes g2-window)
  (check-type-or-stack-error changes tree-view-modify-node-type)
  (with-tree-view (tv handle g2-window 'modify-node)
    (let* ((node-handle (tree-view-find-node-or-stack-error tv ev-node))
           (plist (unbox-evaluation-value changes)))
      (loop for sublist on plist by #'cddr      ; Preprocess icons in plist.
            as (property value) = sublist
            when (memq property '(icon selected-icon))
              do (setf (cadr sublist) (send-native-icon
                                        gensym-window
                                        (tree-view-get-icon-or-stack-error changes property))))
      (tree-view-modify-node tv node-handle plist)
      (reclaim-unboxed-evaluation-value plist)
      (reclaim-if-evaluation-value handle)
      (reclaim-if-evaluation-value ev-node)
      (reclaim-evaluation-structure changes)
      node-handle)))


;;;; Node Inquiry System Procedures


(defun-for-system-procedure g2-ui-node-exists (handle ev-node g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (tv (find-native-view-or-stack-error gensym-window handle 'g2-tree-view)))
    (prog1 (make-evaluation-boolean-value (tree-view-find-node tv ev-node))
      (reclaim-if-evaluation-value handle)
      (reclaim-if-evaluation-value ev-node))))

(defun-for-system-procedure g2-ui-get-child-nodes (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (allocate-evaluation-sequence
      (loop for child-handle in (tree-view-node-children node)
            as child? = (tree-view-ref tv child-handle)
            when child?
              collect (tree-view-node-returned-evalue child?)
                using gensym-cons))))

(defun-for-system-procedure g2-ui-get-parent-node (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (let ((parent? (and (tree-view-node-parent node)
                        (tree-view-ref tv (tree-view-node-parent node)))))
      (tree-view-node-returned-evalue parent?))))

(defun-for-system-procedure g2-ui-get-first-child-node (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (let ((child? (and (tree-view-node-children node)
                       (tree-view-ref tv (car (tree-view-node-children node))))))
      (tree-view-node-returned-evalue child?))))

(defun-for-system-procedure g2-ui-get-last-child-node (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (let ((child? (and (tree-view-node-children node)
                       (tree-view-ref tv (car (last (tree-view-node-children node)))))))
      (tree-view-node-returned-evalue child?))))

(defun-for-system-procedure g2-ui-get-next-child-node (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (let* ((parent? (and (tree-view-node-parent node)
                         (tree-view-ref tv (tree-view-node-parent node))))
           (next-handle? (and parent?
                              (cadr (member (tree-view-node-handle node)
                                            (tree-view-node-children parent?)))))
           (next? (and next-handle? (tree-view-ref tv next-handle?))))
      (tree-view-node-returned-evalue next?))))

(defun-for-system-procedure g2-ui-get-previous-child-node (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (let* ((parent? (and (tree-view-node-parent node)
                         (tree-view-ref tv (tree-view-node-parent node))))
           (prev-handle?
             (when parent?
               (loop for (child next?) on (tree-view-node-children parent?)
                     when (eql (tree-view-node-handle node) next?)
                       return child)))
           (prev? (and prev-handle? (tree-view-ref tv prev-handle?))))
      (tree-view-node-returned-evalue prev?))))

(defun-for-system-procedure g2-ui-count-child-nodes (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (make-evaluation-integer (length (tree-view-node-children node)))))

(defun-for-system-procedure g2-ui-delete-child-nodes (handle ev-node g2-window)
  (with-tree-view-sysproc (tv node handle ev-node g2-window)
    (let ((has-children-p (not (null (tree-view-node-children node)))))
      (loop for child-handle in (tree-view-node-children node)
            as child? = (tree-view-ref tv child-handle)
            when child?
              do (tree-view-delete-node-locally tv child-handle)
                 (manage-tree-view tv 'delete-node child-handle))
      (make-evaluation-boolean-value has-children-p))))


;;;; Fast Hierarchy Routines


;; Not yet exposed to users -fmw, 12/8/04
(defun-for-system-procedure g2-get-class-hierarchy-fast (class-name)
  (when (class-description class-name)
    (get-class-hierarchy-1 (class-description class-name))))

(defun get-class-hierarchy-1 (class-description)
  (let ((children (inferior-classes (class-name-of-class-description class-description))))
    (allocate-evaluation-structure
      (nconc
        (eval-list 'item-or-name
                   (class-name-of-class-description class-description))
        (when children
          (eval-list 'children
                     (allocate-evaluation-sequence
                       (loop for child in children
                             collect (get-class-hierarchy-1
                                       (class-description child)) using eval-cons))))))))

;; This is 300 times faster, with 30 times fewer bytes consed, than
;; g2-get-class-hierarchy, using symbols to name the class instead of strings.
;; It's still 100X faster if using strings.


;;;; Time/Date Conversions


;;; The function `gensym-time-to-vb-date' returns a fixnum representing just the
;;; date part, as days since 1899.

(defun gensym-time-to-vb-date (gensym-time-offset)
  (with-temporary-gensym-float-creation gensym-time-to-vb-date
    (let ((utc-offset (compute-utc-offset))
          (unix-time (convert-gensym-time-to-unix-time (+f gensym-time-offset
                                                           (clock-get gensym-time-at-start)))))
      (+f (floore-first (+e (coerce-to-gensym-float unix-time)
                            (coerce-to-gensym-float utc-offset))
                        86400.0)
          25569))))

(defun vb-date-to-gensym-time (vb-date)
  (with-temporary-gensym-float-creation vb-date-to-gensym-time
    (let* ((utc-offset (compute-utc-offset))
           (unix-time (-e (*e 86400.0 (coerce-to-gensym-float (-f vb-date 25569)))
                          (coerce-to-gensym-float utc-offset))))
      (-f (convert-unix-time-to-gensym-time unix-time)
          (clock-get gensym-time-at-start)))))

(defun compute-utc-offset ()
  (compute-unix-time-offset)
  (with-temporary-gensym-float-creation compute-utc-offset
    (-f (floore-first (managed-float-value unix-time-offset-for-encoding)))))


;;;; Property Grid


(def-type-parameter property-grid-verbs-type
    (sequence (or text symbol (structure ((name symbol)
                                          (label text)
                                          (user-data item-or-datum))))))

(def-type-parameter property-grid-options-type
    (structure
      #.(append
          (cadr view-properties-type)
          '((contents datum)
            (foreground-color symbol)
            (background-color symbol)
            (line-color symbol)
            (help-foreground-color symbol)
            (help-background-color symbol)
            (category-foreground-color symbol)
            (readonly-foreground-color symbol)
            (sort #.prop-grid-sort-type)
            (show-toolbar truth-value)
            (show-help truth-value)
            (help-height integer)
            (verbs #.property-grid-verbs-type)
            (verbs-height integer)
            (view-divider float)
            (font text)                        ; TODO
            (user-data datum)))))

(def-type-parameter property-grid-node-options-type
    (structure
      ((property (or symbol text))
       (category (or symbol text))
       (type #.prop-grid-node-type)
       (label text)
       (description text)
       (current-value datum)
       (icon item-or-datum)                ; For TEXT type only
       (possible-values (sequence item-or-datum))
       (value-format (or (member dd.ddd short-date long-date) symbol))
       (readonly truth-value)
       (ellipsis truth-value)
       (edit-in-place truth-value)
       (expand truth-value)
       (select truth-value)
       (user-data datum))))

(defun prop-grid-make-lisp-value (evalue &optional keys-to-omit)
  (unbox-evaluation-value evalue keys-to-omit))

(defun preprocess-property-grid-option (pg option arg)
  (case option
    ((foreground-color background-color line-color ; Yuck.
                       help-foreground-color help-background-color
                       category-foreground-color readonly-foreground-color)
     (if (symbolp arg) (rgb-value-of-gensym-color arg)))
    (sort
     (prop-grid-sort-code arg))
    (icon
     (when (valid-icon-designation-p arg)
       (send-native-icon (native-window-gensym-window pg) arg '(small large))))
    (value-format                        ; Returns a C-style format string.
     (case arg
       (short-date
        (copy-wide-string #w"%x"))
       (long-date
        (copy-wide-string #w"%#x"))
       (t
        (multiple-value-bind (left right)
            (decode-format arg)
          (when left
            (twith-output-to-wide-string
              (tformat "%.~dg" (+f left right)))))))) ; FIXME: Not quite right
    (t
     arg)))

;; This is for NODE options.
(defun preprocess-property-grid-options (pg plist)
  (loop for place on plist by #'cddr
        as (p v) = place
        as vnew = (preprocess-property-grid-option pg p v)
        do (setf (cadr place) vnew)))

;; This is for VIEW options.
(defun preprocess-property-grid-view-options (pg plist)
  (preprocess-view-options pg plist)
  (loop for place on plist by #'cddr
        as (p v) = place
        unless (eq p 'icon)
          do (setf (cadr place) (preprocess-property-grid-option pg p v))))

(def-structure (property-grid
                 (:include native-view)
                 (:constructor make-property-grid-1)
                 (:reclaimer reclaim-property-grid-1)
                 #+development (:print-function print-native-window))
  (prop-grid-handle-base 1)
  (prop-grid-handle-next 1)                ; Zero handle not allowed
  (prop-grid-nodes nil)                        ; Flat array of nodes, indexed by handle - base
  (prop-grid-user-data nil)                ; An evaluation-value
  (prop-grid-verbs nil)
  (prop-grid-user-func nil)
  )                ; List of prop-grid-verb structures

(def-structure-method clean-up-structure (property-grid)
  (prop-grid-clear property-grid)
  (reclaim-if-evaluation-value (prop-grid-user-data property-grid))
  (setf (prop-grid-user-data property-grid) nil)
  (setf (prop-grid-user-func property-grid) nil)
  (funcall-superior-method property-grid))

(defun make-property-grid (gensym-window callback container user-data options &optional (user-func? nil))
  (let ((pg (make-property-grid-1)))
    (initialize-native-view pg gensym-window 'g2-property-grid container options callback)
    (setf (prop-grid-user-data pg) (copy-if-evaluation-value user-data))
    (setf (prop-grid-user-func pg) (copy-if-evaluation-value user-func?))
    pg))

(defun reclaim-property-grid (pg)
  (reclaim-native-window pg))


(def-structure (prop-grid-verb
                 (:constructor make-prop-grid-verb (prop-grid-verb-name
                                                     prop-grid-verb-label
                                                     prop-grid-verb-user-data))
                 (:reclaimer reclaim-prop-grid-verb)
                 #+development (:print-function print-prop-grid-verb))
  (prop-grid-verb-name nil :reclaimer reclaim-if-text-string)
  (prop-grid-verb-label nil :reclaimer reclaim-if-text-string)
  (prop-grid-verb-user-data nil :reclaimer reclaim-if-evaluation-value))

#+development
(defun print-prop-grid-verb (verb stream depth)
  (declare (ignore depth))
  (printing-random-object (verb stream)
    (format stream "PROPERTY-GRID-VERB ~s" (prop-grid-verb-name verb))))

(defun prop-grid-clear-verbs (prop-grid)
  (when (prop-grid-verbs prop-grid)
    (loop for verb in (prop-grid-verbs prop-grid)
          do (reclaim-prop-grid-verb verb))
    (reclaim-gensym-list (prop-grid-verbs prop-grid))
    (setf (prop-grid-verbs prop-grid) nil)))

(defun preprocess-prop-grid-verbs (pg evalue?)
  (prop-grid-clear-verbs pg)
  (when evalue?
    (setf (prop-grid-verbs pg)
          (loop for verb being each evaluation-sequence-element of evalue?
                as label? = (cond ((evaluation-text-p verb)
                                   (copy-wide-string (evaluation-text-value verb)))
                                  ((evaluation-symbol-p verb)
                                   (translated-string-for-symbol (evaluation-symbol-symbol verb) t t))
                                  ((evaluation-structure-p verb)
                                   (if (evaluation-structure-slot verb 'label)
                                       (copy-wide-string (evaluation-structure-slot verb 'label)))))
                as user-data = (when (evaluation-structure-p verb)
                                 (get-reference-to-item-if-item
                                   (copy-if-evaluation-value
                                     (evaluation-structure-slot verb 'user-data))))
                as name? = (cond ((evaluation-symbol-p verb)
                                  (evaluation-symbol-symbol verb))
                                 ((and (evaluation-structure-p verb)
                                       (evaluation-structure-slot verb 'name)))
                                 (t
                                  (copy-wide-string label?)))
                when label?
                  collect (make-prop-grid-verb name? label? user-data))))
  (loop for verb in (prop-grid-verbs pg)
        collect (copy-wide-string (prop-grid-verb-label verb))
          using gensym-cons))


(def-structure (property-grid-node
                 (:constructor make-prop-grid-node-1)
                 (:reclaimer reclaim-prop-grid-node-1))
  (prop-grid-node-handle 0)
  (prop-grid-node-name nil)
  (prop-grid-node-type nil)
  (prop-grid-node-evaluation-type nil)        ; User's preferred ev-type for values, if any.
  (prop-grid-node-label nil)
  (prop-grid-node-user-data nil))        ; An evaluation-value

(defun reclaim-prop-grid-node (prop-grid node)
  (let ((index (-f (prop-grid-node-handle node) (prop-grid-handle-base prop-grid))))
    (when (prop-grid-nodes prop-grid)
      (setf (managed-svref (prop-grid-nodes prop-grid) index) nil)))
  (reclaim-if-text-string (prop-grid-node-name node))
  (reclaim-if-text-string (prop-grid-node-label node))
  (reclaim-if-evaluation-value (prop-grid-node-user-data node))
  (setf (prop-grid-node-user-data node) nil)
  (reclaim-prop-grid-node-1 node))

;; TODO: Combine with tree-view version.
(defun prop-grid-allocate-node (prop-grid name type caption user-data etype)
  (let* ((handle (prop-grid-handle-next prop-grid))
         (index (-f handle (prop-grid-handle-base prop-grid)))
         (node (make-prop-grid-node-1)))
    (incff (prop-grid-handle-next prop-grid))
    ;; Same stretegy as in `tree-view-allocate-node' -- binghe, 2013/02/05
    (cond ((null (prop-grid-nodes prop-grid))
           (setf (prop-grid-nodes prop-grid)
                 (allocate-managed-array (maxf 256 (ashf 1 (1+f (g-logf index)))))))
          ((>=f index (managed-array-length (prop-grid-nodes prop-grid)))
           (setf (prop-grid-nodes prop-grid)
                 (adjust-managed-array (prop-grid-nodes prop-grid)
                                       (ashf 1 (1+f (g-logf index)))))))
    (setf (prop-grid-node-handle node) handle
          (prop-grid-node-name node) (copy-if-text-string name)
          (prop-grid-node-type node) type
          (prop-grid-node-evaluation-type node) etype
          (prop-grid-node-label node) (copy-if-text-string caption)
          (prop-grid-node-user-data node) (copy-if-evaluation-value user-data))
    (setf (managed-svref (prop-grid-nodes prop-grid) index) node)
    node))

(defun prop-grid-ref (prop-grid handle)
  (let ((array? (prop-grid-nodes prop-grid))
        (index (-f handle (prop-grid-handle-base prop-grid))))
    (when (and array? (<=f 0 index (1-f (managed-array-length array?))))
      (managed-svref array? index))))

(defmacro do-prop-grid-nodes ((node prop-grid) &body body)
  `(when (prop-grid-nodes ,prop-grid)
     (loop for i from 0 below (-f (prop-grid-handle-next ,prop-grid)
                                  (prop-grid-handle-base ,prop-grid))
           as ,node = (managed-svref (prop-grid-nodes ,prop-grid) i)
           doing
       (when (property-grid-node-p ,node)
         ,@body))))

(defun prop-grid-clear (prop-grid)
  (prop-grid-clear-verbs prop-grid)
  (do-prop-grid-nodes (node prop-grid)
    (reclaim-prop-grid-node prop-grid node))
  (when (prop-grid-nodes prop-grid)
    (reclaim-managed-array (prop-grid-nodes prop-grid))
    (setf (prop-grid-nodes prop-grid) nil))
  ;; Reset base.
  (setf (prop-grid-handle-base prop-grid) (prop-grid-handle-next prop-grid)))

(defun prop-grid-find-node (prop-grid ev-node-designation)
  (cond        ((evaluation-integer-p ev-node-designation)
         (prop-grid-ref prop-grid (evaluation-integer-value ev-node-designation)))

        ((evaluation-text-p ev-node-designation)
         (let ((wide-string (evaluation-text-value ev-node-designation)))
           (do-prop-grid-nodes (node prop-grid)
             (when (or (equalw wide-string (prop-grid-node-name node))
                       (equalw wide-string (prop-grid-node-label node)))
               (return-from prop-grid-find-node node)))))

        ((evaluation-symbol-p ev-node-designation)
         (let ((value (evaluation-symbol-symbol ev-node-designation)))
           (do-prop-grid-nodes (node prop-grid)
             (when (eq value (prop-grid-node-name node))
               (return-from prop-grid-find-node node)))))))

(defun prop-grid-find-category (prop-grid category-name-ev)
  (let ((node? (prop-grid-find-node prop-grid category-name-ev)))
    (when (and node? (eq (prop-grid-node-type node?) 'category))
      node?)))

(defun property-grid-find-node-or-stack-error (prop-grid ev-node-designation)
  (or (prop-grid-find-node prop-grid ev-node-designation)
      (ui-stack-error "The node ~NA was not found in property grid ~D."
                      ev-node-designation
                      (native-window-handle prop-grid))))

;; Cf twrite-string-that-identifies-attribute
(defun prop-grid-compute-label (name)
  (cond ((wide-string-p name)
         (copy-wide-string name))
        ((symbolp name)
         (with-localization-domain 'table
           (with-localization-purpose 'attribute
             (let ((localized-string? (translation-for-symbol? name)))
               (twith-output-to-wide-string
                 (twrite-string-as-attribute-name
                   (or localized-string? (symbol-namew name))
                   :first t nil known-gensym-acronyms))))))))


;;; The function `prop-grid-compute-contents' returns a gensym-list of node
;;; specs, each created by prop-grid-create-node-spec.

(defvar prop-grid-contents)

(defun prop-grid-compute-contents (pg evalue parent?)
  (let ((prop-grid-contents nil))
    (prop-grid-compute-contents-1 pg evalue parent?)
    (nreverse prop-grid-contents)))

(defun prop-grid-compute-contents-1 (pg evalue parent?)
  (cond ((null evalue))
        ((evaluation-sequence-p evalue)
         (loop for ev being each evaluation-sequence-element of evalue
               do (prop-grid-compute-contents-1 pg ev parent?)))
        (t
         (multiple-value-bind (name type caption value-ev category-ev
                                    children-ev user-data-ev options)
             (prop-grid-parse-node-evalue evalue)
           (when (and (eq type 'category) (or parent? category-ev))
             (ui-stack-error "Attempted to create nested categories: ~S within ~NV."
                             caption (if parent? (prop-grid-node-label parent?) category-ev)))
           (preprocess-property-grid-options pg options)
           (let* ((parent? (or parent?
                               (unless (eq type 'category)
                                 ;; For leaf nodes, auto-create their category.
                                 (prop-grid-ensure-category pg (or category-ev 'misc)))))
                  (node (prop-grid-create-node
                          pg name type caption parent? value-ev user-data-ev options)))
             (when children-ev
               (prop-grid-compute-contents-1 pg children-ev node)))))))

(defun prop-grid-create-node (pg name type caption parent? value-ev user-data-ev options)
  (let* ((etype (if (evaluation-value-p value-ev)
                     (car-or-atom (evaluation-value-type value-ev))
                     type))
         (value? (prop-grid-evalue-to-native? type value-ev))
         (node (prop-grid-allocate-node pg name type caption user-data-ev etype))
         (node-spec (prop-grid-create-node-spec caption
                                                (prop-grid-node-handle node)
                                                (if (neq type 'category) type)
                                                (if parent? (prop-grid-node-handle parent?))
                                                value?
                                                options)))
    (gensym-push node-spec prop-grid-contents)
    node))

(defun prop-grid-ensure-category (pg category-name-ev)
  (or (prop-grid-find-category pg category-name-ev)
      (let* ((name (prop-grid-make-lisp-value category-name-ev))
             (caption (prop-grid-compute-label name)))
        (prop-grid-create-node pg name 'category caption nil nil nil nil))))

;; Return values are newly consed, except for the evaluation-values
;; (values name type caption value-ev category-ev children-ev user-data-ev options)
(defun prop-grid-parse-node-evalue (evalue)
  (cond ((evaluation-symbol-p evalue)
         (values (evaluation-symbol-symbol evalue)
                 'text
                 (prop-grid-compute-label (evaluation-symbol-symbol evalue))))
        ((evaluation-text-p evalue)
         (values (copy-text-string (evaluation-text-value evalue))
                 'text
                 (copy-text-string (evaluation-text-value evalue))))
        (t
         (check-type-or-stack-error evalue property-grid-node-options-type)
         (let* ((property (evaluation-structure-slot evalue 'property))
                (category (evaluation-structure-slot evalue 'category))
                (name (copy-if-text-string (or property category 'name-missing))) ; HACK
                (label? (evaluation-structure-slot evalue 'label))
                (caption (cond (label?
                                (copy-text-string (evaluation-text-value label?)))
                               (t
                                (prop-grid-compute-label name))))
                (value-ev (evaluation-structure-slot evalue 'current-value))
                (type (cond ((and category (null property)) 'category)
                            ((evaluation-structure-slot evalue 'type))
                            ((evaluation-integer-p value-ev) 'integer) ; Infer type from value.
                            ((evaluation-float-p value-ev) 'float)
                            ((evaluation-boolean-p value-ev) 'boolean)
                            ((evaluation-truth-value-p value-ev) 'truth-value)
                            ((and (evaluation-symbol-p value-ev)              ; Heuristic
                                  (gensym-color-p (evaluation-symbol-symbol value-ev))) 'color)
                            (t 'text)))
                (children-ev (evaluation-structure-slot evalue 'children))
                (user-data-ev (evaluation-structure-slot evalue 'user-data))
                (options (prop-grid-make-lisp-value
                           evalue '(property category label type children user-data current-value))))
           (values name type caption value-ev category children-ev user-data-ev options)))))

;;; The function `prop-grid-evalue-to-native?' converts the user-supplied
;;; current-value for a property grid node into the lisp value we send to TW.

(defun prop-grid-evalue-to-native? (type evalue)
  (with-temporary-gensym-float-creation prop-grid-evalue-to-native?
    (case type
      (color
       (when (evaluation-symbol-p evalue)
         (rgb-value-of-gensym-color (evaluation-symbol-symbol evalue))))
      (float                                ; We can send over a managed-float...
       (when (evaluation-float-p evalue)
         (allocate-managed-float (evaluation-float-value evalue))))
      (date
       (cond ((evaluation-integer-p evalue)   ; "the current real time"
              (gensym-time-to-vb-date (evaluation-integer-value evalue)))
             ((evaluation-float-p evalue)     ; "the current subsecond real time"
              (gensym-time-to-vb-date (rounde-first (evaluation-float-value evalue))))
             ((evaluation-structure-p evalue)
              (gensym-time-to-vb-date
                (multiple-value-bind (second minute hour date month year)
                    (decode-gensym-time gensym-time)
                  (declare (ignore second minute hour))
                  (encode-gensym-time
                    0 0 0
                    (evaluation-structure-slot evalue 'date date)
                    (evaluation-structure-slot evalue 'month month)
                    (evaluation-structure-slot evalue 'year year)))))))
      (t
       (prop-grid-make-lisp-value evalue)))))

(defun prop-grid-native-to-evalue (node string-value integer-value?)
  (with-temporary-gensym-float-creation prop-grid-native-to-evalue
    (case (prop-grid-node-type node)
      (boolean
       (make-evaluation-boolean-value (eql integer-value? 1)))
      (integer
       (make-evaluation-integer (or integer-value? 0)))
      (float                                ; ...but getting one back requires parsing the string
       (make-evaluation-float
         (coerce-to-gensym-float
           (read-float-from-string string-value 0 (text-string-length string-value)))))
      (date
       (let ((time (vb-date-to-gensym-time (or integer-value? 0))))
         (case (prop-grid-node-evaluation-type node)
           (integer
            (make-evaluation-integer time))
           (float
            (make-evaluation-float (coerce-to-gensym-float time)))
           (structure
            (multiple-value-bind (second minute hour date month year)
                (decode-gensym-time time)
              (declare (ignore second minute hour))
              (allocate-evaluation-structure-inline 'month month 'date date 'year year))))))
      (color
       (make-evaluation-symbol
         (intern-text-string
           (nstring-upcasew
             (twith-output-to-wide-string
               (tformat "RGB~A" string-value))))))
      (t
       (make-evaluation-text string-value)))))

(defun property-grids-p (gensym-window)
  (and (twng-window-p gensym-window)
       (window-supports-property-grid gensym-window)))

(defun manage-property-grid (pg action &optional (arg nil) (node 0))
  (let ((gensym-window (native-window-gensym-window pg))
        (handle (native-window-handle pg)))
    (cond ((not (property-grids-p gensym-window)))
          ((icp-window-p gensym-window)
           (with-icp-window (gensym-window)
             (send-icp-manage-property-grid gensym-window action handle node arg)))
          (t
           (manage-property-grid-1 gensym-window action handle node arg)))))

(defun-for-system-procedure g2-ui-create-property-grid (title callback options g2-window &optional user-func?)
  (check-type-or-stack-error options property-grid-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (property-grids-p gensym-window)
      (ui-stack-error "Property grids are not supported on ~NF" g2-window))
    (let* ((options* (prop-grid-make-lisp-value options '(contents verbs user-data)))
           (contents (evaluation-structure-slot options 'contents))
           (verbs (evaluation-structure-slot options 'verbs))
           (user-data (evaluation-structure-slot options 'user-data))
           (container (getf options* 'container 'pane)))
      (setq options* (mutate-gensym-plist options* 'title title))
      (let* ((pg (make-property-grid gensym-window callback container user-data options* user-func?))
             (contents* (prop-grid-compute-contents pg contents nil))
             (verbs* (preprocess-prop-grid-verbs pg verbs)))
        (preprocess-property-grid-view-options pg options*)
        (when contents*
          (setq options* (mutate-gensym-plist options* 'contents contents*)))
        (when verbs*
          (setq options* (mutate-gensym-plist options* 'verbs verbs*)))
        (manage-property-grid pg 'create options*)
        (reclaim-unboxed-evaluation-value options*) ; Reclaims title
        (reclaim-evaluation-value options)
        (native-window-handle pg)))))

(defun-for-system-procedure g2-ui-manage-property-grid (action handle ev-arg g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (pg (find-native-view-or-stack-error gensym-window handle 'g2-property-grid)))
    (case action
      ((close destroy)
       (manage-property-grid pg 'destroy)
       (reclaim-property-grid pg))

; FIXME
;      ((select dock float show hide autohide toggle-docking)
;       (manage-pane-1 native-window arg nil))

      (clear
       (manage-property-grid pg action)
       (prop-grid-clear pg))

      ((contents populate)
       ;; TODO: We have to clear it before computing contents. So any syntax
       ;; error in the contents will leave the prop grid cleared. Not ideal, but
       ;; no worse that if the user first cleared it then populated.
       (manage-property-grid pg 'clear)
       (prop-grid-clear pg)
       (let ((contents (prop-grid-compute-contents pg ev-arg nil)))
         (manage-property-grid pg action contents)
         (reclaim-unboxed-evaluation-value contents)))

      (modify
       (let ((plist (prop-grid-make-lisp-value ev-arg)))
         (when (plistp plist)
           (preprocess-property-grid-view-options pg plist)
           (manage-property-grid pg action plist))
         (reclaim-unboxed-evaluation-value plist)))

      ((select-node expand-node collapse-node)
       (let ((node (property-grid-find-node-or-stack-error pg ev-arg)))
         (manage-property-grid pg action nil (prop-grid-node-handle node))))

      ((expand-all collapse-all)
       (let ((node-handle (if (evaluation-boolean-p ev-arg)
                              0
                             (prop-grid-node-handle
                               (property-grid-find-node-or-stack-error pg ev-arg)))))
         (manage-property-grid pg action nil node-handle)))

      (delete-node
       (let ((node (property-grid-find-node-or-stack-error pg ev-arg)))
         (manage-property-grid pg action nil (prop-grid-node-handle node))
         (reclaim-prop-grid-node pg node)))

      (verbs
       (check-type-or-stack-error ev-arg property-grid-verbs-type)
       (let ((verbs* (preprocess-prop-grid-verbs pg ev-arg)))
         (manage-property-grid pg 'verbs verbs*)
         (reclaim-unboxed-evaluation-value verbs*)))

      (t
       (cond ((and (prop-grid-opcode action)
                   (not (prop-grid-node-opcode action)))
              (let* ((arg (prop-grid-make-lisp-value ev-arg))
                     (v (preprocess-property-grid-option gensym-window action arg)))
                (manage-property-grid pg action v)
                (reclaim-unboxed-evaluation-value arg)))
             (t
              (ui-stack-error "Unknown property-grid action ~S" action))))))
  (reclaim-if-evaluation-value ev-arg)
  (reclaim-if-evaluation-value handle))

(defun g2-ui-insert-property-grid-node (handle ev-node ev-parent options g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (pg (find-native-view-or-stack-error gensym-window handle 'g2-property-grid))
         (parent (property-grid-find-node-or-stack-error pg ev-parent))
         (contents (prop-grid-compute-contents pg ev-node parent))
         (node-handle (gensym-dstruct-bind ((caption id) (car contents)) caption id)))
    (manage-property-grid pg 'contents contents (prop-grid-node-handle parent))
    (reclaim-if-evaluation-value handle)
    (reclaim-if-evaluation-value ev-node)
    (reclaim-if-evaluation-value ev-parent)
    (reclaim-evaluation-structure options)
    node-handle))

(defun g2-ui-modify-property-grid-node (handle ev-node changes g2-window)
  (check-type-or-stack-error changes property-grid-node-options-type)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (pg (find-native-view-or-stack-error gensym-window handle 'g2-property-grid))
         (node (property-grid-find-node-or-stack-error pg ev-node))
         (value? (evaluation-structure-slot changes 'current-value))
         (icon? (evaluation-structure-slot changes 'icon))
         (user-data? (evaluation-structure-slot changes 'user-data))
         (plist (prop-grid-make-lisp-value changes '(current-value icon user-data))))
    (setq plist (nconc                        ; Preprocess node plist
                  (when value?
                    (gensym-list 'current-value
                                 (prop-grid-evalue-to-native? (prop-grid-node-type node) value?)))
                  (when icon?
                    (gensym-list 'icon
                                 (preprocess-property-grid-option pg 'icon icon?)))
                  plist))
    (when user-data?
      (reclaim-if-evaluation-value (prop-grid-node-user-data node))
      (setf (prop-grid-node-user-data node) (copy-if-evaluation-value user-data?)))
    (when plist
      (manage-property-grid pg 'modify-node plist (prop-grid-node-handle node)))
    (reclaim-unboxed-evaluation-value plist)
    (reclaim-if-evaluation-value handle)
    (reclaim-if-evaluation-value ev-node)
    (reclaim-evaluation-structure changes)
    (prop-grid-node-handle node)))

(define-event-handler handle-property-grid-message ((gensym-window window) event-plist
                                                    x-in-window y-in-window)
  (let* ((pg? (find-native-window gensym-window (getf event-plist 'window) 'g2-property-grid))
         (event? (prop-grid-event-name (getf event-plist 'event)))
         (node? (if pg? (prop-grid-ref pg? (getf event-plist 'item -1))))
         (string-value? (getf event-plist 'value))
         (integer-value? (getf event-plist 'ivalue))
;	 (user-data-grid? (prop-grid-user-data pg?))
	 (user-func? (prop-grid-user-func pg?))
;	 (user-data-node? (if node? (prop-grid-node-user-data node?)))
;	 (frame? (if user-data-node? (evaluation-structure-slot user-data-node? 'frame)))
;	 (slot-name? (if user-data-node? (evaluation-structure-slot user-data-node? 'slot-name)))
;	 (command? (if user-data-node? (evaluation-structure-slot user-data-node? 'command)))
	 )
    (when (and pg? event?)
      (prop-grid-invoke-callback pg? event? node? string-value? integer-value?
                                 x-in-window y-in-window))

    (when (and user-func? node?)
      (funcall user-func? pg? node? event?))))

(defun prop-grid-invoke-callback (pg event node? string-value? integer-value?
                                  x-in-window y-in-window)
  (let ((gensym-window (native-window-gensym-window pg))
        (verb? (when (and (eq event 'verb)
                          integer-value?
                          (>=f integer-value? 0))
                 (nth integer-value? (prop-grid-verbs pg)))))
    (multiple-value-bind (x y)
        (gensym-window-point-to-user-window-point gensym-window x-in-window y-in-window)
      (invoke-view-callback
        pg event
        (copy-if-text-string
          (cond (verb? (prop-grid-verb-name verb?))
                (node? (prop-grid-node-name node?))
                (t evaluation-false-value)))
        (nconc
          (case event
            (sorted
             (if integer-value? (eval-list 'sort (prop-grid-sort-symbol integer-value?))))
            (verb
             (if verb? (prop-grid-verb-event-info verb?)))
            (t
             (prop-grid-default-event-info node? string-value? integer-value?)))
          (eval-list 'x x 'y y))
        (prop-grid-user-data pg)))))        ; Invoke-view-callback copies it

(defun prop-grid-verb-event-info (verb)
  (nconc (eval-list 'name (copy-if-text-string (prop-grid-verb-name verb)))
         (eval-list 'label (copy-wide-string (prop-grid-verb-label verb)))
         (if (prop-grid-verb-user-data verb)
             (eval-list 'user-data (get-item-if-item-reference
                                     (copy-if-evaluation-value
                                       (prop-grid-verb-user-data verb)))))))

(defun prop-grid-default-event-info (node? string-value? integer-value?)
  (nconc
    (if node?
        (eval-list 'node (prop-grid-node-handle node?)
                   'type (prop-grid-node-type node?)
                   'name (copy-if-text-string (prop-grid-node-name node?))
                   'label (copy-if-text-string (prop-grid-node-label node?))))
    (if (and node? string-value?)
        (eval-list 'current-value
                   (prop-grid-native-to-evalue node? string-value? integer-value?)))
    (if string-value? (eval-list 'text-value (copy-if-text-string string-value?)))
    (if integer-value? (eval-list 'integer-value integer-value?))
    (if (and node? (prop-grid-node-user-data node?))
        (eval-list 'user-data
                   (copy-if-evaluation-value
                     (prop-grid-node-user-data node?))))))

(defun property-user-callback-func (pg node event)
  (let* ((user-data-node? (if node (prop-grid-node-user-data node)))
	 (frame? (if user-data-node? (evaluation-structure-slot user-data-node? 'frame)))
	 (slot-name? (if user-data-node? (evaluation-structure-slot user-data-node? 'slot-name)))
         #+ignore ; not used
	 (command? (if user-data-node? (evaluation-structure-slot user-data-node? 'command)))
	 (virtual? (if user-data-node? (evaluation-structure-slot user-data-node? 'virtual)))
         #+ignore ; not used
	 (editable? (if user-data-node? (evaluation-structure-slot user-data-node? 'editable))))
    (when (and frame? slot-name?)
      (case event
	((double-click node-expanded node-collapsed)
	 (update-property-grid-user-data pg frame?)
	 (enter-editing-context frame? slot-name? nil nil nil
				nil nil
				nil nil nil nil nil nil nil nil nil nil nil nil
				nil nil
				nil virtual? nil))))))

(defun update-property-grid-user-data (prop-grid frame)
  (when prop-grid
    (let* ((user-data-grid? (prop-grid-user-data prop-grid))
	   (frame? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'frame)))
	   (window? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'window)))
	   (func? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'func)))
	   ;; TODO: should be `frame' or `frame?' --binghe
	   (user-data-update? (package-internal-data-property frame window? func? T)))
      (declare (ignore frame?))
      (setf (prop-grid-user-data prop-grid) user-data-update?))))

(defun update-property-grid-user-data-reset-flag (prop-grid frame)
  (when prop-grid
    (let* ((user-data-grid? (prop-grid-user-data prop-grid))
	   (frame? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'frame)))
	   (window? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'window)))
	   (func? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'func)))
	   ;; TODO: should be `frame' or `frame?' --binghe
	   (user-data-update? (package-internal-data-property frame window? func? nil)))
      (declare (ignore frame?))
      (setf (prop-grid-user-data prop-grid) user-data-update?))))

(defun update-property-pane-after-edit (prop-grid)
  (when (not (eq prop-grid nil))
    (let* ((user-data-grid? (prop-grid-user-data prop-grid))
	   (frame? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'frame)))
	   (window? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'window)))
	   (func? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'func)))
	   (flag? (if user-data-grid? (evaluation-structure-slot user-data-grid? 'flag))))
      (declare (ignore flag?))
      (when (and frame? window?)
	(if func? (funcall func? frame? window?))
	(update-property-grid-user-data-reset-flag prop-grid frame?)))))

;;;; Grid Views

;; NOTE: Grid-views aren't really views yet, just components in dialogs

(defun grid-view-event-name (event-code)
  (case event-code
    (1 'selection-changed)
    (t nil)))

;; Really this is a dialog-view message, caused by a grid-view.  Events: new
;; control has focus (tabbed to), etc.
(define-event-handler handle-grid-view-message ((gensym-window window) (plist event-plist))
  (let* ((handle (getf plist 'window 0))
         (dialog-view? (find-native-window gensym-window handle 'g2-dialog-view))
         (event-name? (grid-view-event-name (getf plist 'event)))
         (control-id (getf plist 'control-id))
         (row (getf plist 'row -1))
         (column (getf plist 'column -1))
         (selection? (getf plist 'value)) ; As a packed string
         (custom-dialog? (and dialog-view? (dialog-view-custom-dialog? dialog-view?)))
         (component? (and control-id custom-dialog?
                          (lookup-component-given-component-internal-id
                            control-id custom-dialog?)))
         (grid-view? (and component?
                          (dialog-component-g2-representation? component?))))
    (when (and event-name? component?)
      (let ((selection-ev?
              (if (and (lisp-grid-view-p grid-view?) selection?)
                  (unpack-grid-view-selection grid-view? selection?))))
        (invoke-view-callback dialog-view?
                              event-name?
                              (dialog-component-kb-id component?)                 ; Item
                              (nconc
                                (if (and (>=f row 0) (>=f column 0))     ; row/column of focus cell
                                    (eval-list 'row row 'column column))
                                (if selection-ev?
                                    (eval-list 'selection selection-ev?)))
                              (copy-evaluation-value (dynamic-dialog-user-data custom-dialog?)))))))


;;; The function `unpack-grid-view-selection' unpacks the current grid-view
;;; selection, updating our local cache and returning an evaluation-value to
;;; pass to the user callback.

(defun unpack-grid-view-selection (gv wide-string)
  (grid-view-clear-selection gv)
  (allocate-evaluation-sequence
    (loop for i below (wide-string-length wide-string) by 4
          as minrow = (1-f (byte-vector-16-aref wide-string (+f i 0)))
          as mincol = (1-f (byte-vector-16-aref wide-string (+f i 1)))
          as maxrow = (1-f (byte-vector-16-aref wide-string (+f i 2)))
          as maxcol = (1-f (byte-vector-16-aref wide-string (+f i 3)))
          collect (allocate-evaluation-structure-inline
                    'minrow minrow 'maxrow maxrow 'mincol mincol 'maxcol maxcol)
            using eval-cons
          doing
      (loop for row from minrow to maxrow do
        (loop for column from mincol to maxcol do
          (grid-view-select-cell gv row column))))))



;;;; HTML Views


(def-type-parameter html-view-options-type
    #.view-properties-type)

(def-structure (html-view
                 (:include native-view)
                 (:constructor make-html-view-1)
                 (:reclaimer reclaim-html-view-1)
                 #+development (:print-function print-native-window))
  (html-view-url? nil))

(def-class (g2-html-view g2-native-view (foundation-class g2-html-view)
                         do-not-put-in-menus not-user-instantiable)
  (url-of-view nil (type whole-string?) vector-slot))

(def-class-method cleanup (g2-html-view)
  (let ((hv? (native-window-structure g2-html-view)))
    (when hv?
      (close-html-view hv?)                ; Destroys the TW-side window.
      (reclaim-html-view hv?)))
  ;; Now let superior snap links.
  (funcall-superior-method g2-html-view))

(def-slot-putter url-of-view (g2-html-view new-url? initializing?)
  (setf (url-of-view g2-html-view) new-url?)
  (let ((hv? (native-window-structure g2-html-view)))
    (when hv?
      (setf (html-view-url? hv?) (copy-if-text-string new-url?))
      (unless initializing?
        (manage-html-view hv? 'goto (or new-url? #w"")))))
  new-url?)

(defun make-html-view (gensym-window callback container options url)
  (let ((hv (make-html-view-1)))
    (initialize-native-view hv gensym-window 'g2-html-view container options callback)
    (setf (html-view-url? hv) (copy-if-text-string url))
    hv))

(def-structure-method clean-up-structure (html-view)
  (reclaim-if-text-string (html-view-url? html-view))
  (setf (html-view-url? html-view) nil)
  (funcall-superior-method html-view))

(defun reclaim-html-view (hv)
  (reclaim-native-window hv))

(defun html-views-p (gensym-window)
  (and (nms-controls-p gensym-window) ; TWNG
       (window-supports-html-views gensym-window)))

(defun-for-system-procedure g2-ui-create-html-view (url callback options g2-window)
  (check-type-or-stack-error options html-view-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (html-views-p gensym-window)
      (ui-stack-error "HTML views are not supported on ~NF" g2-window))

    (let* ((options* (mutate-gensym-plist
                       (unbox-evaluation-value options)
                       'url url))
           (container (getf options* 'container 'mdi-child))
           (hv (make-html-view gensym-window callback container options* url)))
      (setq options* (preprocess-view-options hv options*))
      (manage-html-view hv 'create options*)
      (reclaim-unboxed-evaluation-value options*)
      (reclaim-if-evaluation-value options)
      (native-window-handle hv))))

(defun-for-system-procedure g2-ui-manage-html-view (action handle ev-arg g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (html-views-p gensym-window)
      (ui-stack-error "HTML views are not supported on ~NF" g2-window))
    (let ((hv (find-native-view-or-stack-error gensym-window handle 'g2-html-view)))
      (case action
        (destroy
         (manage-html-view hv action nil)
         (reclaim-html-view hv))
        (t
         (let ((arg (unbox-evaluation-value ev-arg)))
           (manage-html-view hv action arg)
           (reclaim-unboxed-evaluation-value arg))))
      (reclaim-if-evaluation-value ev-arg)
      (reclaim-if-evaluation-value handle))))

(defun manage-html-view (hv action arg)
  (let ((gensym-window (native-window-gensym-window hv))
        (handle (native-window-handle hv)))
    (with-icp-window (gensym-window)
      (send-icp-manage-html-view gensym-window action handle arg))))


;; TODO: Merge with native-window API.
(defun close-html-view (hv)
  (manage-html-view hv 'destroy nil))

(defun html-view-event-name (event-code)
  (case event-code
    (t nil)))

(define-event-handler handle-html-view-message ((gensym-window window) event-plist)
  (let* ((handle (or (getf event-plist 'handle)        ; FIXME: Remove before 8.1 beta
                     (getf event-plist 'window)))
         (hv? (find-native-window gensym-window handle 'g2-html-view))
         (event? (html-view-event-name (getf event-plist 'event))))
    (when (and hv? event?)
      ;; TODO: events for done-loading, switched-url, etc.
      (invoke-view-callback hv? event? 'label nil 'none))))


;;;; CHART Views


(def-type-parameter chart-view-properties-type
    (or (structure) (sequence (structure))))

(def-type-parameter chart-view-action-type
    (member update destroy print copy export partial-update set))

(def-structure (chart-view
                 (:include native-view)
                 (:constructor make-chart-view-1)
                 (:reclaimer reclaim-chart-view-1)
                 #+development (:print-function print-native-window))
  ;; Zillion properties go here.
  (chart-view-graph-type nil))

(def-class (g2-chart-view g2-native-view (foundation-class g2-chart-view)
                          do-not-put-in-menus not-user-instantiable)
  ;; Zillion properties go here.
  )

(def-class-method cleanup (g2-chart-view)
  (let ((cv? (native-window-structure g2-chart-view)))
    (when cv?
      (manage-chart-view cv? 'destroy nil) ; Destroys the TW-side window.
      (reclaim-chart-view cv?)))
  ;; Now let superior snap links.
  (funcall-superior-method g2-chart-view))

(defun make-chart-view (gensym-window callback container options)
  (let ((cv (make-chart-view-1)))
    (initialize-native-view cv gensym-window 'g2-chart-view container options callback)
    cv))

(def-structure-method clean-up-structure (chart-view)
  (funcall-superior-method chart-view))

(defun reclaim-chart-view (cv)
  (reclaim-native-window cv))

(defun chart-views-p (gensym-window)
  (and (mdi-frame-p gensym-window)
       (window-supports-chart-views gensym-window)
       (or (get-gensym-window-parameter gensym-window 'charting-library-version?)
	       (eq 'jfreechart (charting-library miscellaneous-parameters)))))

(defun get-chart-view-or-stack-error (handle g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (chart-views-p gensym-window)
      (ui-stack-error "Chart views are not supported on ~NF" g2-window))
    (let ((cv? (find-native-window gensym-window handle 'g2-chart-view)))
      (unless cv?
        (ui-stack-error "No Chart view found for handle ~d" handle))
      cv?)))

(defun valid-chart-property-p (name)
  (or (writeable-view-property-p name)
      (memq name '(type update))
      (chart-property-p name)))

(defun valid-chart-symbol-p (symbol)
  (or (pechart-enum-value symbol)
      (gensym-color-p symbol)
      (rgb-color-p symbol)
      (pechart-type-code symbol nil)))

;; Returns the unknown symbol as second value.
(defun valid-chart-property-value-p (property value)
  (cond ((writeable-view-property-p property)
         t)
        ((symbolp value)
         (values (valid-chart-symbol-p value)
                 value))
        ((and (evaluation-structure-p value)
              (evaluation-structure-slot value 'v)
              (symbolp (evaluation-structure-slot value 'v)))
         (values (valid-chart-symbol-p (evaluation-structure-slot value 'v))
                 (evaluation-structure-slot value 'v)))
        (t
         (values t nil))))

;; TODO: Probably should be a warning, not a stack error.
(defun check-chart-properties-or-stack-error (evalue)
  (check-type-or-stack-error evalue chart-view-properties-type)
  (macrolet ((check-properties (structure)
               `(loop for (name . value) being each evaluation-structure-pair of ,structure doing
                  (unless (valid-chart-property-p name)
                    (gensym-push name unknown-properties))
                  (multiple-value-bind (value-ok-p symbol)
                      (valid-chart-property-value-p name value)
                    (unless value-ok-p
                      (gensym-push symbol unknown-enums))))))
    (let ((unknown-properties ())
          (unknown-enums ()))

      (cond ((evaluation-sequence-p evalue)
             (loop for element being each evaluation-sequence-element of evalue doing
               (when (evaluation-structure-p element)
                 (check-properties element))))
            ((evaluation-structure-p evalue)
             (check-properties evalue)))

      (when (or unknown-properties unknown-enums)
        (write-stack-error
            cached-top-of-stack
          (when unknown-properties
            (tformat "The following chart-view properties are unknown: ");
            (write-symbol-list unknown-properties)
            (tformat ". ")
            (reclaim-gensym-list unknown-properties))
          (when unknown-enums
            (tformat "The following chart-view enumeration values are unknown: ");
            (twrite-list unknown-enums :conjoiner " and ")
            (tformat ". ")
            (reclaim-gensym-list unknown-enums)))))))

;;; The function `unbox-chart-view-properties' is identical to
;;; unbox-evaluation-value, except elements of a sequence at top-level are
;;; simply nconc'ed instead of collected.

(defun unbox-chart-view-properties (evalue)
  (cond ((evaluation-sequence-p evalue)
         (loop for element being each evaluation-sequence-element of evalue
               when (evaluation-structure-p element)
                 nconc (unbox-evaluation-value element)))
        (t
         (unbox-evaluation-value evalue))))

(defun manage-chart-view-for-eval (cv action ev-arg)
  (check-type-or-stack-error action chart-view-action-type)
  (let ((arg (case action
               (set (unbox-chart-view-properties ev-arg))
               (t (unbox-evaluation-value ev-arg))))
        (handle (native-window-handle cv)))
    (manage-chart-view cv action arg)
    (reclaim-unboxed-evaluation-value arg)
    (reclaim-if-evaluation-value ev-arg)
    (when (eq action 'destroy)
      (reclaim-chart-view cv))
    handle))

(defun manage-chart-view (cv action arg)
  (let ((gensym-window (native-window-gensym-window cv))
        (handle (native-window-handle cv)))
    (cond ((icp-window-p gensym-window)
           (with-icp-window (gensym-window)
             (send-icp-manage-chart-view gensym-window action handle arg nil)))
          (t
           (manage-chart-view-1 gensym-window action handle arg nil)))))

(defun chart-view-event-name (event-code)
  (case event-code
    (1 'closed)                                ; Keep in sync with CV_EVENT_CLOSED
    (2 'click)
    (3 'menu-choice)
    (t nil)))

(define-event-handler handle-chart-view-message ((gensym-window window) event-plist)
  (let* ((handle (getf event-plist 'window -1))
         (cv? (find-native-window gensym-window handle 'g2-chart-view))
         (event? (chart-view-event-name (getf event-plist 'event)))
         (string? (getf event-plist 'value))
         (x (getf event-plist 'x 0))
         (y (getf event-plist 'y 0)))
    (when (and cv? event?)
      (multiple-value-bind (item info)
          (case event?
            (click
             (let ((xyz (when (stringpw string?)
                          (read-chart-point-from-string string?))))
               (values (if xyz (allocate-evaluation-structure xyz) 'none)
                       (eval-list 'subset x 'point y))))
            (menu-choice
             (values 'none                ; This will be the item's string, someday.
                     (nconc
                       (eval-list 'menu-choice x)
                       (if (>f y 0) (eval-list 'submenu-choice y))))))

        (invoke-view-callback cv? event? item info 'no-user-data))
      (when (eq event? 'closed)
        (reclaim-chart-view cv?)))))

(defun read-chart-point-from-string (string)
  ;; "x=%lf, y=%lf, z=%lf"
  (with-temporary-gensym-float-creation handle-chart-view-message
    (loop with start = 0
          for axis in '(x y z)
          for pos = (position-in-text-string-tail #.%\= string start)
          while pos
          as value = (allocate-managed-float
                       (read-float-from-string string (1+f pos) (length string)))
          collect axis using eval-cons
          collect value using eval-cons
          do (setq start (1+f pos)))))



;;;; Chart Views System Procedures


(defun-for-system-procedure g2-ui-create-chart-view (title callback options g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))

    (check-chart-properties-or-stack-error options)

    (unless (chart-views-p gensym-window)
      (ui-stack-error "Chart views are not supported on ~NF" g2-window))

    (unless (or (and (twng-window-p gensym-window)
                     (window-supports-chart-views-in-panes gensym-window))
                (eq (evaluation-structure-slot options 'container 'mdi-child)
                    'mdi-child))
      (ui-stack-error "The container ~NV is not supported for chart views on ~NF."
                      (evaluation-structure-slot options 'container)
                      g2-window))

    (let* ((options* (mutate-gensym-plist
                       (unbox-chart-view-properties options)
                       'title title))
           (container (getf options* 'container 'mdi-child))
           (cv (make-chart-view gensym-window callback container options*)))
      (setq options* (preprocess-view-options cv options*))

      ;; If data present and no "points" property, add one.
      (when (null (getf options* 'points))
        (let* ((data? (or (getf options* 'ydata)        ; ydata is first priority.
                          (getf options* 'xdata)))
               (points (if (consp data?) (length data?) 0)))
          (when (>f points 0)
            (setq options* (mutate-gensym-plist options* 'points points)))))

      ;; GENSYMCID-1054: Gigasoft Charts Issue causes TWNG to crash and exit without warning when using TWNG 2011 with 8.3r1
      ;; Now we put `charting-library-to-use' into options* for ICP compability with G2 8.3r1
      (setq options* (mutate-gensym-plist options*
                                          'charting-library-to-use
                                          (charting-library miscellaneous-parameters)))

      (manage-chart-view cv 'create options*)

      (reclaim-unboxed-evaluation-value options*)
      (reclaim-if-evaluation-value options)
      (native-window-handle cv))))

;; Actions: destroy, print, update, partial-update, copy, set, ...
(defun-for-system-procedure g2-ui-manage-chart-view (action handle ev-arg g2-window)
  (let ((cv (get-chart-view-or-stack-error handle g2-window)))
    (reclaim-if-evaluation-value handle)
    (manage-chart-view-for-eval cv action ev-arg)))

;; This is a shortcut for the SET action.
(defun-for-system-procedure g2-ui-modify-chart-view (handle properties g2-window)
  (let ((cv (get-chart-view-or-stack-error handle g2-window)))
    (reclaim-if-evaluation-value handle)
    (check-chart-properties-or-stack-error properties)
    (manage-chart-view-for-eval cv 'set properties)))


;;; The sysproc `g2-ui-chart-set-data' tries to be a fast way to set data.

;;; TODO: We probably need to do some buffering, and define a new ICP message
;;; that takes an entire float array, to really help.

(defun-for-system-procedure g2-ui-chart-set-data (handle prop i j v g2-window)
  (check-type-or-stack-error v '(or number symbol text))
  (let ((cv (get-chart-view-or-stack-error handle g2-window))
        (plist (gensym-list 'update nil
                            prop (gensym-list 'i i 'j j 'v v)))) ; FIXME: Yuck.
    (reclaim-if-evaluation-value handle)
    (manage-chart-view cv 'set plist)
    (reclaim-unboxed-evaluation-value plist)
    (native-window-handle cv)))


;;;; Shortcut Bars


(def-type-parameter shortcut-bar-options-type
    (structure
      #.(append
          (cadr view-properties-type)
          '((style (member default listbar))        ; What to call the Outlook 2003 style?
            (allow-drag-item truth-value)        ; Default: false
            (allow-rename-item truth-value)        ; Default: false
            (background-color symbol)
            (foreground-color symbol)))))

(def-type-parameter shortcut-bar-folders-type
    (sequence                                ; A sequence of folders
      (structure
        ((label text)                        ; Each folder, a label and a sequence of items.
         (items (sequence
                  (structure ((icon item-or-datum) ; Each item a structure.
                              (label text)
                              (tooltip text))
                             (and icon label))))))
      1))                                ; XTP can't handle empty shortcut bars? Only for default style?

;; Documented actions: small-icons large-icons disable-folder enable-folder clear destroy
(def-type-parameter shortcut-bar-actions-type
    (member destroy hide show select close
            populate add-folder add-item
            clear small-icons large-icons background-color foreground-color
            select-folder enable-folder disable-folder select-item
            enable-item disable-item))

(def-structure (shortcut-bar
                 (:include native-view)
                 (:constructor make-shortcut-bar-1)
                 (:reclaimer reclaim-shortcut-bar-1)
                 #+development (:print-function print-native-window))
  (shortcut-bar-style nil)        ; NIL, DEFAULT, or LISTBAR
  (shortcut-bar-folders nil))        ; An evaluation-sequence.

(def-class (g2-shortcut-bar g2-native-view (foundation-class g2-shortcut-bar)
                         do-not-put-in-menus not-user-instantiable)
  ;; TODO: Save the tree structure here.
  )

(def-class-method cleanup (g2-shortcut-bar)
  (let ((shb? (native-window-structure g2-shortcut-bar)))
    (when shb?
      (manage-shortcut-bar shb? 'destroy nil)
      (reclaim-shortcut-bar shb?)))
  ;; Now let superior snap links.
  (funcall-superior-method g2-shortcut-bar))

(defun make-shortcut-bar (gensym-window callback container options)
  (let ((shb (make-shortcut-bar-1)))
    (initialize-native-view shb gensym-window 'g2-shortcut-bar container options callback)
    shb))

(def-structure-method clean-up-structure (shortcut-bar)
  (clear-shortcut-bar shortcut-bar)
  (funcall-superior-method shortcut-bar))

(defun clear-shortcut-bar (shb)
  (reclaim-if-evaluation-value (shortcut-bar-folders shb))
  (setf (shortcut-bar-folders shb) nil)
  shb)

(defun reclaim-shortcut-bar (shb)
  (reclaim-native-window shb))

(defun shortcut-bars-p (gensym-window)
  (and (nms-controls-p gensym-window) ; TWNG
       (window-supports-shortcut-bars gensym-window)))

(defun shortcut-bar-style-code (style)
  (case style
    (listbar shortcut-bar-style-outlook-2003)
    (t shortcut-bar-style-outlook)))


(defun-for-system-procedure g2-ui-create-shortcut-bar (folders callback options g2-window)
  (check-type-or-stack-error options shortcut-bar-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (shortcut-bars-p gensym-window)
      (ui-stack-error "Shortcut Bars are not supported on ~NF" g2-window))
    (when folders
      (check-type-or-stack-error folders shortcut-bar-folders-type t)) ; FIXME: Why t?
    (let* ((options* (unbox-evaluation-value options))
           (container (getf options* 'container 'pane))
           (style? (getf options* 'style))
           (bg? (getf options* 'background-color))
           (fg? (getf options* 'foreground-color))
           (shb (make-shortcut-bar gensym-window callback container options*)))
      (setq options* (preprocess-view-options shb options*))
      (when style?
        (setf (shortcut-bar-style shb) style?)
        (setf (getf options* 'style) (shortcut-bar-style-code style?)))
      (when bg?
        (setf (getf options* 'background-color) (rgb-value-of-gensym-color bg?)))
      (when fg?
        (setf (getf options* 'foreground-color) (rgb-value-of-gensym-color fg?)))
      (manage-shortcut-bar shb 'create options*)
      (reclaim-unboxed-evaluation-value options*)
      (when folders                        ; We take ownership of this ev.
        (populate-shortcut-bar shb folders))
      (reclaim-if-evaluation-value options)
      (native-window-handle shb))))

(defun-for-system-procedure g2-ui-manage-shortcut-bar (action handle ev-arg g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (shortcut-bars-p gensym-window)
      (ui-stack-error "Shortcut bars are not supported on ~NF" g2-window))

    (check-type-or-stack-error action shortcut-bar-actions-type)

    (let ((shb (find-native-view-or-stack-error
                 gensym-window handle 'g2-shortcut-bar))
	  (do-not-reclaim-ev-arg nil))
      (case action
        (populate
         (check-type-or-stack-error ev-arg shortcut-bar-folders-type t) ; FIXME: Why t?
	 (setf do-not-reclaim-ev-arg t)
         (populate-shortcut-bar shb ev-arg))

        (clear
         (manage-shortcut-bar shb action nil)
         (clear-shortcut-bar shb))

        (destroy
         (manage-shortcut-bar shb action nil)
         (reclaim-shortcut-bar shb))

        ((set-background-color background-color)
         (when (evaluation-symbol-p ev-arg)
           (manage-shortcut-bar
             shb 'background-color (rgb-value-of-gensym-color (evaluation-symbol-symbol ev-arg)))))

        ((set-foreground-color foreground-color)
         (when (evaluation-symbol-p ev-arg)
           (manage-shortcut-bar
             shb 'foreground-color (rgb-value-of-gensym-color (evaluation-symbol-symbol ev-arg)))))

        (t
         (let ((arg (unbox-evaluation-value ev-arg)))
           (manage-shortcut-bar shb action arg)
           (reclaim-unboxed-evaluation-value arg))))

      (when (not do-not-reclaim-ev-arg)
	(reclaim-if-evaluation-value ev-arg))
      (reclaim-if-evaluation-value handle))))


;;; The function `populate-shortcut-bar' fills the shortcut bar with the given
;;; folders (an evaluation value), and takes ownership of that value.

(defun populate-shortcut-bar (shb ev-folders)
  (when (evaluation-sequence-p ev-folders)
    (let ((folders (unbox-evaluation-value ev-folders))
          (gensym-window (native-window-gensym-window shb)))

      (clear-shortcut-bar shb)        ; Clear out old folders.
      (setf (shortcut-bar-folders shb) ev-folders) ; Hang on to new ones.

      ;; Send all the icons first, both 16x16 and 32x32. Note that we
      ;; destructively change icon names in the list structure to their handles.
      (dolist (folder folders)
        (when (plistp folder)
          (let ((folder-icon? (getf folder 'icon))
                (folder-items (getf folder 'items)))
            (when folder-icon?
              (setf (getf folder 'icon)
                    (send-native-icon gensym-window folder-icon? '(small large))))
            (dolist (item folder-items)
              (when (plistp item)
                (let ((icon? (getf item 'icon)))
                  (when icon?
                    (setf (getf item 'icon)
                          (send-native-icon gensym-window icon? '(small large))))))))))

      ;; Now send the folders.
      (manage-shortcut-bar shb 'populate folders)
      (reclaim-unboxed-evaluation-value folders))))

;; For shortcut-bar containers, neighbor is a folder number, defaulting to 0.
(defun preprocess-shortcut-bar-container (shortcut-bar neighbor?)
  (unless (window-supports-views-in-listbars (native-window-gensym-window shortcut-bar))
    (ui-stack-error "The window ~NF does not support placing views in listbars."
                    (g2-window-for-gensym-window? (native-window-gensym-window shortcut-bar))))
  (unless (eq (shortcut-bar-style shortcut-bar) 'listbar)
    (ui-stack-error "Only listbar-style shortcut-bars may be used as containers."))
  (when neighbor?
    ;; TODO: Allow folder names as well as numbers.
    (unless (and (fixnump neighbor?)
                 (get-shortcut-bar-folder shortcut-bar neighbor?))
      (ui-stack-error "The neighbor option ~A must be the number of an existing folder."
                      neighbor?)))
  (values (native-window-handle shortcut-bar)
          (or neighbor? 0)))

;;; The function `get-shortcut-bar-item' returns the folder or the item, from
;;; the saved evaluation value, according to whether item-number? is specified.

(defun get-shortcut-bar-item (shb folder-number &optional item-number?)
  (let ((folders? (shortcut-bar-folders shb)))
    (when folders?
      (let* ((folder? (evaluation-sequence-aref folders? folder-number))
             (items? (and folder? (evaluation-structure-slot folder? 'items)))
             (item? (and items? item-number? (evaluation-sequence-aref items? item-number?))))
        (or item? folder?)))))

(defun get-shortcut-bar-folder (shb folder-number)
  (let ((folders? (shortcut-bar-folders shb)))
    (when folders?
      (evaluation-sequence-aref folders? folder-number))))


(defun manage-shortcut-bar (shb action arg)
  (let ((gensym-window (native-window-gensym-window shb))
        (handle (native-window-handle shb)))
    (when (shortcut-bars-p gensym-window)
      (with-icp-window (gensym-window)
        (send-icp-manage-shortcut-bar gensym-window action handle arg)))))

; Sync with xtp/include/Controls/Common.Include/XTNotify.h
(defun shortcut-bar-event-name (event-code)
  (case event-code
    (1 'item-selected)                ; Item was selected.
    (2 'item-renamed)                ; Item label edit completed.
    (3 'folder-renamed)                ; Folder label edit completed.
    (4 'drag-item)                ; Item drag operation in process.
    (5 'folder-selected)        ; Folder selection changed.
    (6 'hover)                        ; [unused] Mouse is hovering over item (more like enter/leave)
    (7 'item-deleted)                ; [unused] Item deleted.
    (8 'folder-deleted)                ; [unused] Folder deleted.
    (9 'begin-drag)                ; Item drag operation begun.
    (10 'right-click)))                ; Right click on item or background.

(define-event-handler handle-shortcut-bar-message ((gensym-window window) event-plist)
  (let* ((handle? (getf event-plist 'window))
         (event? (getf event-plist 'event))
         (folder-number? (getf event-plist 'folder))
         (item-number? (getf event-plist 'item))
         (label? (getf event-plist 'value))
         (shb? (find-native-window gensym-window handle? 'g2-shortcut-bar))
         (event-name (shortcut-bar-event-name event?)))
    (when shb?
      (invoke-view-callback shb? event-name label?
                            (eval-list 'folder (or folder-number? -1)
                                       'item (or item-number? -1))
                            (get-shortcut-bar-item shb? folder-number? item-number?)))))


;;;; Breakpoint Support


(defun breakpoint-state-to-opcode (state)
  (cond ((eql state dynamic-breakpoint-disabled)
         editor-disable-breakpoint)
        ((eql state dynamic-breakpoint-enabled)
         editor-set-breakpoint)
        ((eql state 'clear-all)
         editor-clear-breakpoints)
        (t
         editor-clear-breakpoint)))

(defun opcode-to-breakpoint-state (opcode)
  (case opcode
    (#.editor-disable-breakpoint
     dynamic-breakpoint-disabled)
    (#.editor-set-breakpoint
     dynamic-breakpoint-enabled)
    (#.editor-clear-breakpoint
     nil)
    (#.editor-clear-breakpoints
     'clear-all)))

;;; The function `set-breakpoint-and-notify' tries to set or clear a breakpoint
;;; on the given line in a frame (procedure or rule) and updates all views of
;;; the breakpoint. Gensym-window is the window on which the operation was
;;; attempted. We beep in that window on failure.

(defun set-breakpoint-and-notify (gensym-window frame line state)
  (cond ((not (procedure-p frame))        ; Breakpoints supported only in procedures.
         (beep-in-window gensym-window))
        ((not (cond ((null state)
                     (delete-dynamic-breakpoint frame line))
                    ((eq state 'clear-all)
                     (delete-all-dynamic-breakpoints frame)
                     t)
                    (t
                     (set-dynamic-breakpoint-internal frame line state))))
         #+development (dwarn "set-breakpoint ~s line ~d state ~a failed" frame line state)
         (beep-in-window gensym-window))
        (t
         (update-breakpoint-views frame line state))))

;;; The function `editor-set-breakpoints' completely resets the breakpoints
;;; on procedure from a list of breakpoints, in the form of a line number
;;; logiorf'd with debugger-disabled-breakpoint-flag if disabled. All views are
;;; updated.

(defun editor-set-breakpoints (procedure breakpoints)
  (delete-all-dynamic-breakpoints procedure)
  (update-breakpoint-views procedure 0 'clear-all)
  (loop for breakpoint in breakpoints
        as disabled-p = (/= 0 (logandf breakpoint editor-disabled-breakpoint-flag))
        as line = (logandf #xFFFFF breakpoint)
        as state = (if disabled-p dynamic-breakpoint-disabled dynamic-breakpoint-enabled)
        do
    (when (set-dynamic-breakpoint-internal procedure line state)
      (update-breakpoint-views procedure line state))))

(defun editor-clear-breakpoints (procedure)
  (editor-set-breakpoints procedure nil))

(defun update-breakpoint-views (procedure line state)
  ;; Update debugger views.
  (when (and computation-frame-at-breakpoint
             (eq procedure computation-frame-at-breakpoint))
    (loop for workstation in workstations-in-service
          as gensym-window = (window-for-workstation workstation)
          doing
      (when (native-debugger-dialog-p gensym-window)
        (debugger-send-breakpoint gensym-window line state))))

  ;; Update editor views.
  ;; We can only update editors which have the latest compile tick, and which
  ;; are unmodified. The unmodifiedness is checked on the TW side in editor.c.
  (loop for workstation in workstations-in-service doing
    (loop for wc in (workstation-context-stack workstation)
          as edit-state? = (if (eq (type-of-workstation-context wc) 'editing)
                               (specific-structure-for-workstation-context wc))
          doing
      (when (and edit-state?
                 (eq (frame-being-edited? edit-state?) procedure)
                 (eq (name-of-slot-being-edited edit-state?) 'procedure-definition)
                 (eql (editor-compile-tick edit-state?)
                      (n-compiles-this-session-function procedure)))
        (loop for image-plane in (image-planes-this-is-on (edit-workspace edit-state?))
              as native-window? = (image-plane-native-window? image-plane)
              doing
          (when native-window?
            (editor-send-breakpoint native-window? line state)))))))


;;;; Native Editor


(def-concept native-editor)

;; Category or type-specification-simple-expansion
(defparameter categories-using-single-line-native-editor
  '(name-or-names name? module-name? symbol integer integer? number?))

(defconstant category-menu-icon-delimiter #.\%page)
(defparameter editor-completions-separator (code-wide-character 1)) ; Control+A

(defvar native-editor-already-updated nil)

;;; The function `set-up-native-editor' is eventually called from PANES (in the
;;; function create-native-window-for-image-plane) the native-editor is enabled.

(defun set-up-native-editor (gensym-window native-window edit-state
                                           ;; Added by SoftServe
                                           &optional modal)
  (let* ((string (convert-text-to-text-string (text-being-edited edit-state)))
         (cursor-line-index? (initial-cursor-line-index? edit-state))
         (cursor-character-index? (initial-cursor-character-index? edit-state))
         (caret (if cursor-line-index?
                    (compute-caret-from-line-and-char
                      (text-being-edited edit-state)
                      cursor-line-index? (or cursor-character-index? 0))
                    ;; Default cursor position is at the END of the text. See
                    ;; enter-editing-context-1
                    (wide-string-length string)))
         (frame? (frame-being-edited? edit-state))
         (breakpoints (and (edit-state-does-breakpoints-p edit-state)
                           (debugger-get-breakpoints frame?))))

    ;; Keep track of which compile this editor corresponds to.
    (when (procedure-p frame?)
      (setf (editor-compile-tick edit-state)
            (n-compiles-this-session-function frame?)))

    ;; Default grammar is free text.
    (unless (free-text-slot-being-edited? edit-state)
      (manage-native-editor native-window editor-set-grammar #w""
                            editor-grammar-procedure/rule)) ; TODO: More grammars

    (let ((options (logiorf editor-options-single-line-comments
                            (if (use-single-line-editor-p edit-state)
                                editor-options-single-line-editor
                                0)
                            (if (native-editor-query-on-close-p edit-state)
                                editor-options-query-on-close
                                0))))
      (when (window-supports-manage-dialog gensym-window) ; TW 8.2+
        (manage-native-editor native-window #.editor-set-options #w"" options)))

    ;; Set tab spacing (only for 8.3r0+ editors).
    (manage-native-editor native-window editor-set-tabs #w""
                          (number-of-spaces-to-insert-on-a-tab editor-parameters))

    ;; Select incremental updates (ditto)
    (when (window-supports-incremental-editor-updates gensym-window)
      (manage-native-editor native-window editor-incremental-updates #w"" 1))

    (manage-native-editor native-window editor-set-text string caret)
    (reclaim-text-string string)

    (manage-native-editor native-window editor-set-breakpoints #w"" 0 breakpoints)

    ;; Don't show the editor window until here.
    (manage-native-editor native-window #.editor-show)
    
    ;; Added by SoftServe
    (when modal
    (manage-native-editor native-window editor-modal))
    ;; End of SoftServe changes

    (reclaim-eval-list breakpoints)))

(defun edit-state-does-breakpoints-p (edit-state)
  (and (frame-being-edited? edit-state)
       (procedure-p (frame-being-edited? edit-state))
       (eq (name-of-slot-being-edited edit-state) 'procedure-definition)))

(defun use-single-line-editor-p (edit-state)
  (let* ((category (category-symbol-given-slot-type (type-of-slot-being-edited edit-state)))
         (base-category (type-specification-simple-expansion category)))
    (or (memq category categories-using-single-line-native-editor)
        (memq base-category categories-using-single-line-native-editor))))

(defun native-editor-query-on-close-p (edit-state)
  (not (and (frame-being-edited? edit-state)
            (frame-of-class-p (frame-being-edited? edit-state) 'command))))

(define-event-handler handle-editor-message ((gensym-window window) workstation
                                             event-plist &optional native-image-plane)
  (let* ((opcode (getf event-plist 'opcode 0))
         (caret (getf event-plist 'caret 0))
         (g2-window? (g2-window-for-this-workstation? workstation))
         (end? (getf event-plist 'end))
         (string? (getf event-plist 'text))
         (native-window? (and native-image-plane
                              (image-plane-native-window? native-image-plane)))
         (workspace? (and native-image-plane
                          (workspace-on-image-plane? native-image-plane)))
         (edit-state? (and workspace? (find-edit-state workstation workspace?))))
    (when edit-state?
      (case opcode
        (#.editor-cursor-moved
         (editor-move-cursor edit-state? caret)
         (editor-reply-if-error native-window? edit-state?))

        (#.editor-text-inserted
         (editor-insert-text edit-state? string? caret)
         (editor-reply-if-error native-window? edit-state?))

        (#.editor-text-deleted
         (editor-delete-text edit-state? caret end?)
         (editor-reply-if-error native-window? edit-state?))

        (#.editor-completions-new
         (cond ((editor-parse edit-state? nil)
                (editor-send-syntax-error native-window? edit-state?))
               (t
                (editor-show-completions-popup native-window? edit-state?))))

        ((#.editor-apply-new #.editor-exit-new)
         (editor-try-to-commit-changes
           native-window? edit-state? nil caret
           (if (eql opcode editor-exit-new) 'end 'update) g2-window?))

        (#.editor-hotspot-clicked
         (when (and string? end?)
           (native-editor-hotspot-click
             edit-state? string? (case end? (1 'category) (2 'completion)))))

        (#.editor-completions                ; Update text and return completions or error.
         ;; This is an obsolete message.
         ;; Since we display a scrolling list of completions, allow a bunch.
         (let ((old-value (maximum-number-of-names-for-a-menu-override? edit-state?)))
           (unwind-protect-for-development handle-editor-message
               (progn
                 (setf (maximum-number-of-names-for-a-menu-override? edit-state?) 2000)
                 (editor-set-text edit-state? string? caret))
             (setf (maximum-number-of-names-for-a-menu-override? edit-state?) old-value)))

         (cond ((editor-parse edit-state? nil)
                (editor-send-syntax-error native-window? edit-state?))
               (t
                (editor-show-completions-popup native-window? edit-state?))))

        (#.editor-arglist                ; Return arglist for procedure, method, or function.
         (editor-send-arglist native-window? string?))

        (#.editor-goto-item                ; Go to item given name
         (editor-goto-item native-window? string?))

        ((#.editor-set-breakpoint #.editor-clear-breakpoint #.editor-disable-breakpoint
                                  #.editor-clear-breakpoints)
         ;; caret is really the line number here.
         (if (edit-state-does-breakpoints-p edit-state?)
             (set-breakpoint-and-notify gensym-window (frame-being-edited? edit-state?)
                                        caret (opcode-to-breakpoint-state opcode))
             (beep-in-window gensym-window)))

        (#.editor-set-breakpoints        ; Breakpoints for upcoming apply/exit.
         (when string?
           (setf-text (editor-pending-breakpoints edit-state?) (copy-if-text-string string?))))

        ;; Added by SoftServe
        (#.editor-custom-toolbar
         (let* ((procedure? (get-callback-procedure editor-toolbar-user-callback 
                                                   "callback-for-custom-toolbar-in-editor")))
        (when procedure?
          (call-kb-procedure procedure? caret))))
        ;; End of SoftServe changes
        (#.editor-undo
         ;; GENSYMCID-844
         ;;   when twng do a 'undo' action, it will send message `editor-undo' to G2,
         ;;   with `caret' holds the current cache of `maximum-number-of-undos-to-remember'.
         ;;   if the cache has expired, G2 will send a new value to twng to update it.
         (let ((native-window? (native-editor-window edit-state?)))
           (when (and native-window?
                      (/=f caret (maximum-number-of-undos-to-remember editor-parameters)))
             (manage-native-editor native-window? #.editor-maximum-number-of-undos-to-remember
                                   nil (maximum-number-of-undos-to-remember editor-parameters)))))
        ((#.editor-apply #.editor-exit) ; Update text, compile, and maybe exit.
         (editor-try-to-commit-changes
           native-window? edit-state? string? caret
           (if (eql opcode editor-exit) 'end 'update) g2-window?))))))

;;; The function `editor-try-to-commit-changes' updates the text of the frame
;;; being edited and attempts to parse. If parsing fails, we send a parse error
;;; back and we're done. If it succeeds, then we update the set of breakpoints
;;; for the frame, and send back an acknowledgement, with frame notes, unless
;;; we're exiting the editor. Mode is either UPDATE or END.

(defun editor-try-to-commit-changes (native-window edit-state text? caret? mode &optional g2-window)
  (cond ((current-edit-state-p edit-state)
         (editor-try-to-commit-changes-1 native-window edit-state text? caret? mode g2-window))
        (t
         (beep-in-window (native-window-gensym-window native-window)))))

(defun editor-try-to-commit-changes-1 (native-window edit-state text? caret? mode &optional g2-window)
  (let* ((frame (frame-being-edited? edit-state))
         (fsn (copy-frame-serial-number (frame-serial-number frame)))
         (pending-breakpoints-p
           (not (null (editor-pending-breakpoints edit-state))))
         (breakpoints
           (prog1
               (word-vector-to-fixnum-list (editor-pending-breakpoints edit-state))
             (setf-text (editor-pending-breakpoints edit-state) nil))))

    (when (and text? caret?)
      (editor-set-text edit-state text? caret?))

    ;; If we are ending editing, the editor's workstation context is actually
    ;; unwound within the call to editor-parse. So we have to set up the exit
    ;; code here, in anticipation of a normal exit.  If the editor decides to do
    ;; an abortive exit (probably only happens if the frame is reclaimed), then
    ;; the exit status will be changed there to cancel-exit. -fmw, 1/30/07
    (when (eq mode 'end)
      (setf (type-of-exit-from-edit-context? edit-state) 'end-exit))

    (cond ((editor-parse edit-state mode)
           ;; If the text can not be parsed, notify user the current editor can not be close.
           (if (being-autoclose-with-system-procedure? edit-state)
               (notify-user "Current editor open can not be close using g2-ui-close-current-editor because the applying changes can not be parsed."))
           (editor-send-syntax-error native-window edit-state))
          ((frame-has-been-reprocessed-p frame fsn))
          (t
           ;; Successful commit
           (update-att-tables frame g2-window)
           (when (procedure-p frame)
             (setf (editor-compile-tick edit-state)
                   (n-compiles-this-session-function frame)))
           (when pending-breakpoints-p
             (when (procedure-p frame)
               (editor-set-breakpoints frame breakpoints)))
           (when (eq mode 'update)
             (editor-send-frame-notes native-window edit-state))))
    (setf (being-autoclose-with-system-procedure? edit-state) nil)
    (reclaim-gensym-list breakpoints)
    (reclaim-frame-serial-number fsn)))

(defun editor-reply-if-error (native-window edit-state)
  (cond ((problem-string-of-first-reason-for-bad-parse? edit-state)
         (editor-send-syntax-error native-window edit-state))
        (t
         (editor-send-syntax-repair native-window edit-state))))

(defun current-edit-state-p (edit-state)
  (eq edit-state (specific-structure-for-workstation-context
                    current-workstation-context)))

;; I believe this routine is obsolete now.
(defun editor-set-text (edit-state string caret)
  (let ((native-editor-already-updated t))
    (in-editing-context (edit-state)
      (replace-entire-edit-box-text string)
      (multiple-value-bind (line-index character-index)
          (compute-line-and-character-from-caret (text-being-edited edit-state) caret)
        (change-edit-box-cursor-position line-index character-index)))))

(defun editor-move-cursor (edit-state caret)
  (let ((native-editor-already-updated t))
    (in-editing-context (edit-state)
      (multiple-value-bind (line-index character-index)
          (compute-line-and-character-from-caret (text-being-edited edit-state) caret)
        (change-edit-box-cursor-position
          line-index character-index
          nil)))))                        ; no-parsing-or-ellipsis-deletion?

(defun editor-insert-text (edit-state string caret)
  (let ((native-editor-already-updated t))
    (in-editing-context (edit-state)
      (multiple-value-bind (line-index character-index)
          (compute-line-and-character-from-caret (text-being-edited edit-state) caret)
        (insert-text-string-in-text-being-edited
          string nil nil line-index character-index
          (find-text-tail-for-line (text-being-edited edit-state) line-index)
          nil nil
          nil)))))                        ; no-parsing-or-ellipsis-deletion?

(defun editor-delete-text (edit-state start-caret end-caret)
  (let ((native-editor-already-updated t))
    (in-editing-context (edit-state)
      (multiple-value-bind (start-line-index start-character-index)
          (compute-line-and-character-from-caret (text-being-edited edit-state) start-caret)
        (multiple-value-bind (end-line-index end-character-index)
            (compute-line-and-character-from-caret (text-being-edited edit-state) end-caret)
          (change-edit-box
            (text-being-edited current-edit-state)
            start-line-index start-character-index end-line-index end-character-index
            nil nil nil
            ;; FIXME: Want parsing but not ellipsis deletion.
            nil nil nil nil T))))))                        ; no-parsing-or-ellipsis-deletion?

(defun editor-clear-error (edit-state)
  ;; Clear out any previous reason for a bad parse. This is due to the
  ;; "unless" in handle-parsing-or-compilation-problem added by JED 8/10/94.
  (when (problem-string-of-first-reason-for-bad-parse? edit-state)
    (reclaim-most-recent-reason-for-bad-parse?
      (most-recent-reason-for-bad-parse? edit-state))
    (setf (most-recent-reason-for-bad-parse? edit-state) nil)))

;; cf: finish-parsing-insofar-as-possible
(defun editor-parse (edit-state mode)
  (let* ((edit-workspace (edit-workspace edit-state))
         (fsn (copy-frame-serial-number (frame-serial-number edit-workspace))))

    (in-editing-context (edit-state)
      (editor-clear-error edit-state)

      ;; This binding fakes out EDIT-CONTEXT-REMAINS-VALID-P, so that the editor
      ;; will agree to cough up completions.
      (let ((specific-structure-for-current-workstation-context edit-state))
        (case mode
          (update (extend-parsing-as-appropriate 'end t t))
          (end (extend-parsing-as-appropriate 'end t))
          (t (extend-parsing-as-appropriate 'no-autocompletion t t)))))

    (cond ((frame-has-been-reprocessed-p edit-workspace fsn)
           (reclaim-frame-serial-number fsn)
           nil)
          (t
           (reclaim-frame-serial-number fsn)
		   (setf (line-index-of-repair-for-bad-parse? edit-state) nil)
	       (setf (character-index-of-repair-for-bad-parse? edit-state) nil)
           (problem-string-of-first-reason-for-bad-parse? edit-state)))))

;; Actually, replace-or-insert-text. Cf insert-text-string-at-cursor-from-outside
(defun native-editor-replace-text (edit-state string start-line start-char end-line? end-char?)
  (let ((native-window? (native-editor-window edit-state)))
    (when native-window?
      (let ((start (compute-caret-from-line-and-char
                     (text-being-edited edit-state)
                     start-line start-char)))
        (cond ((and end-line? end-char?)
               (let ((end (compute-caret-from-line-and-char
                            (text-being-edited edit-state)
                            end-line? end-char?)))
                 (manage-native-editor native-window? #.editor-replace-text string start end)))
              (t
               (manage-native-editor native-window? #.editor-insert-text string start)))))))

(defun editor-show-completions-popup (native-window edit-state)
  (let ((completions (get-editor-completions edit-state)))
    (when completions
      (let ((string
              (twith-output-to-wide-string
                (loop for str in completions
                      as first = t then nil
                      doing
                  (unless first (twrite-char editor-completions-separator))
                  (tformat "~a" str)))))
        (manage-native-editor native-window editor-completions string)
        (reclaim-wide-string string)
        (reclaim-gensym-tree-with-text-strings completions)))))

(defun editor-send-syntax-error (native-window edit-state)
  (when (problem-string-of-first-reason-for-bad-parse? edit-state)
    (manage-native-editor
      native-window editor-syntax
      (problem-string-of-first-reason-for-bad-parse? edit-state)
      (compute-caret-from-line-and-char
        (text-being-edited edit-state)
        (or (line-index-of-first-reason-for-bad-parse? edit-state) 1)
        (or (character-index-of-first-reason-for-bad-parse? edit-state) 0)))
    ;; Now discard the error.
	(setf (line-index-of-repair-for-bad-parse? edit-state) nil)
	(setf (character-index-of-repair-for-bad-parse? edit-state) nil)
    (editor-clear-error edit-state)))
(defun editor-send-syntax-repair (native-window edit-state)
  (when (and (line-index-of-repair-for-bad-parse? edit-state)
             (character-index-of-repair-for-bad-parse? edit-state))
    (manage-native-editor 
      native-window editor-syntax-repair #w"" 
      (compute-caret-from-line-and-char
        (text-being-edited edit-state)
        (or (line-index-of-repair-for-bad-parse? edit-state) 1)
        (or (character-index-of-repair-for-bad-parse? edit-state) 0)))
    (setf (line-index-of-repair-for-bad-parse? edit-state) nil)
	(setf (character-index-of-repair-for-bad-parse? edit-state) nil)))

;; TODO: Send parsed frame notes, so that we can underline mispellings, and
;; otherwise highlight or goto the line containing an error.
(defun editor-send-frame-notes (native-window edit-state)
  (let ((frame? (frame-being-edited? edit-state)))
    (when frame?
      (let ((string (twith-output-to-text-string
                      (write-slot-value
                        'frame-status-and-notes
                        (frame-status-and-notes frame?)
                        frame?))))
        ;; Acknowledge successful save and send notes.
        (manage-native-editor native-window #.editor-text-saved string)
        (reclaim-wide-string string)))))

(defun editor-send-arglist (native-window string)
  (let* ((token?
           (editor-get-definition-name? string))
         (arglists
           ;; FIXME: The call-p argument, if true, prevents searching any of the
           ;; built-in functions. We set it to NIL to search all, so we may
           ;; return the wrong answer for "call" statements. But then, so does
           ;; the classic editor in some cases!
           (if token?
               (parameters-for-token-if-any token? nil)))
         (calltip
           (twith-output-to-text-string
             (loop for arglist in arglists
                   as first = t then nil
                   doing
               (unless first (twrite-line-separator))
               (twrite-signature token? arglist)))))
    (manage-native-editor native-window editor-arglist calltip)
    (reclaim-gensym-tree arglists)
    (reclaim-wide-string calltip)))

(defun editor-get-definition-name? (string)
  (multiple-value-bind (name? end-index class-qualifier?)
      (read-attribute-name-from-text-string string)
    (declare (ignore end-index))
    (cond ((null name?)
           nil)
          (class-qualifier?
           (make-unique-slot-name-symbol class-qualifier? name?))
          (t
           name?))))

(defun editor-goto-item (native-window string)
  (let* ((symbol?
           (editor-get-definition-name? string))
         (frame?
           (and symbol?
                (car-or-atom (frame-or-frames-with-this-name symbol?))))
         (permitted?
           ;; TODO: Maybe check get-workspace instead if frame is a workspace?
           (and (inspect-permitted-p)
                (main-menu-command-permitted-p 'inspect)))
         (note
           (twith-output-to-text-string
             (cond ((not permitted?)
                    (tformat "This command has been restricted."))
                   ((null symbol?)
                    (tformat "Problem parsing string \"~a\"." string))
                   ((null frame?)
                    (tformat "No G2 item found with name \"~(~A~)\"." symbol?))
                   (t
                    (tformat "Go to ~(~A~)." symbol?))))))
    (manage-native-editor native-window editor-notes note)
    (if (and frame? permitted?)
        (goto-frame-instance frame?)
        (manage-native-editor native-window editor-beep))
    (reclaim-wide-string note)))

(defun suspend-native-editor (edit-state)
  (native-editor-send-command edit-state editor-disable))

(defun resume-native-editor (edit-state)
  (native-editor-send-command edit-state editor-enable))

(defun native-editor-window (edit-state)
  (loop for image-plane in (image-planes-this-is-on (edit-workspace edit-state))
        thereis (image-plane-native-window? image-plane)))

(defun native-editor-send-command (edit-state opcode &optional string? caret? arg?)
  (let ((native-window? (native-editor-window edit-state)))
    (when native-window?
      (manage-native-editor native-window? opcode string? caret? arg?))))

(defun editor-send-breakpoint (native-window line state)
  (manage-native-editor native-window
                        (breakpoint-state-to-opcode state)
                        #w"" line))

(defun find-edit-state (workstation workspace)
  (loop for ws in (workstation-context-stack workstation)
        as state = (specific-structure-for-workstation-context ws)
        when (and (edit-state-p state)
                  (eq workspace (edit-workspace state)))
          return state))


(defun native-editor-clear-output (native-window)
  (manage-native-editor native-window #.editor-clear-output))

(defun native-editor-print (native-window string &optional type)
  (manage-native-editor native-window #.editor-append-output
                        string
                        (case type
                          (category #.editor-style-category)
                          (completion #.editor-style-completion)
                          (t #.editor-style-normal))))

(defun native-editor-terpri (native-window)
  (native-editor-print native-window #w"\u2028"))

(defun native-editor-tab (native-window)
  (native-editor-print native-window #w"\u0009"))

;;; The function `canonicalize-category-menu' does a partial job of merging
;;; redundant categories into their super-category, and renaming some odd ones
;;; (eg, left-string -> quoted-message).  Abstracted from
;;; make-category-menu-table, which ought to use this.

(defun canonicalize-category-menu (category-menu)
  ;; float, integer < number
  ;; string < quoted-message, end-of-message
  (loop with most-general-number-type?
        with most-general-string-type?
        with unit-of-measure?
        with list
        for category-symbol in category-menu
        doing
    (case category-symbol
      (number
       (setq most-general-number-type? 'number))
      ((integer non-negative-integer)
       (cond ((null most-general-number-type?)
              (setq most-general-number-type? 'integer))
             ((eq most-general-number-type? 'float)
              (setq most-general-number-type? 'number))))
      (float
       (cond ((null most-general-number-type?)
              (setq most-general-number-type? 'float))
             ((eq most-general-number-type? 'integer)
              (setq most-general-number-type? 'number))))
      (left-string
       (setq most-general-string-type? 'quoted-message))
      ((middle-string right-string)
       (setq most-general-string-type? 'end-of-message))
      (whole-string
       (unless most-general-string-type?
         (setq most-general-string-type? 'string)))
      ((neutral-unit-of-measure singular-unit-of-measure plural-unit-of-measure)
       (setq unit-of-measure? 'unit-of-measure))
      ((bad-java-character-literal proc-logical-type))
      (t
       (gensym-push category-symbol list)))
        finally
          (return (nreverse (nconc (if most-general-number-type?
                                       (gensym-list most-general-number-type?))
                                   (if most-general-string-type?
                                       (gensym-list most-general-string-type?))
                                   (if unit-of-measure?
                                       (gensym-list unit-of-measure?))
                                   list)))))

;;; The function `regroup-completion-menus' reduces the number of columns of
;;; completions we need to display by merging consecutive one-element columns
;;; into a single column.  Abstracted from put-up-menus-1

(defun regroup-completion-menus (menus)
  (loop with l = menus
        as menu = (car l)
        as menu* = (cond ((and (null (cdr menu)) ; two onesies in a row
                               (if (cdr l) (null (cdr (car (cdr l))))))
                          (loop collect (copy-tree-using-gensym-conses (car (pop l)))
                                  using gensym-cons
                                until (or (null l) (cdr (car l)))))
                         (t
                          (pop l)
                          (copy-tree-using-gensym-conses
                            (if (eq (car menu) :upcase)
                                (cdr menu)
                                menu))))
        collect menu* using gensym-cons
        while l))

;;; The function `native-editor-show-completions' takes a raw
;;; menu-content-structure, directly from the classic editor's put-up-menus-1
;;; routine, massages it, and sends it over to the native editor as a tree of
;;; strings.

(defun native-editor-show-completions (edit-state menu-content-structure)
  (let ((native-window? (native-editor-window edit-state)))
    (when native-window?
      (let* ((categories (canonicalize-category-menu
                           (car menu-content-structure)))
             (menus (regroup-completion-menus (cdr menu-content-structure)))
             (strings
               (gensym-cons
                 (loop for category in categories
                       collect (copy-symbol-name category nil) using gensym-cons)
                 (loop for menu in menus
                       collect (loop for entry in menu
                                     collect (token-menu-string-to-display-for-entry entry)
                                       using gensym-cons)
                         using gensym-cons))))
        (manage-native-editor native-window? #.editor-show-completions #w"" 0 strings)
        (reclaim-gensym-tree-with-text-strings strings)
        (reclaim-gensym-tree menus)
        (reclaim-gensym-tree categories)))))

(defun native-editor-hotspot-click (edit-state string type)
  (case type
    (category
     (let ((category (intern-text-string
                       (nstring-upcasew (copy-wide-string string))
                       ab-package-1)))
       (native-editor-category-click edit-state category)))
    (completion
     (in-editing-context (edit-state)
       (insert-text-string-at-cursor string t t)))))

(defun native-editor-category-click (edit-state category)
  (let ((names (choices-for-category-menu edit-state category)))
    (cond (names
           (native-editor-show-menu-of-names edit-state names))
          (t
           (native-editor-show-help-for-category edit-state category)))
    (reclaim-grammar-list names)))

(defun native-editor-show-menu-of-names (edit-state names)
  (let ((native-window? (native-editor-window edit-state)))
    (when native-window?
      (let ((strings
              (gensym-cons nil
                           (loop for name in names
                                 collect (gensym-list
                                           (copy-symbol-name name nil))
                                   using gensym-cons))))
        (manage-native-editor native-window? #.editor-show-completions #w"" 0 strings)
        (reclaim-gensym-tree-with-text-strings strings)))))

(defun native-editor-show-help-for-category (edit-state category)
  (let ((native-window? (native-editor-window edit-state)))
    (when native-window?
      (let ((string (copy-symbol-name category nil)))
        (setf (temporary-information-on-edit-workspace? edit-state) 'editor-notification)
        (native-editor-clear-output native-window?)
        (native-editor-print native-window? #w"Enter any ")
        (native-editor-print native-window? string 'category)
        (reclaim-text-string string)))))

(defun native-editor-display-notification (edit-state string)
  (native-editor-send-command edit-state #.editor-notes string))


;; Abstracted from handle-mouse-down-event-in-edit-context
(defun choices-for-category-menu (edit-state category &optional omit)
  (unless (or (null category)
              (eq category omit))
    (let ((token
            (in-editing-context (edit-state)
              (get-next-token-if-available
                (cursor-line-index current-edit-state)
                (cursor-character-index current-edit-state)))))
      (prog1
          (make-menu-of-names-from-directory
            category (if (text-string-p token) token))
        (when (text-string-p token)
          (reclaim-text-string token))))))

(defun completion-equal (wide-string-1 wide-string-2)
  (let ((length-1 (or (position-in-text-string category-menu-icon-delimiter wide-string-1)
                      (wide-string-length wide-string-1)))
        (length-2 (or (position-in-text-string category-menu-icon-delimiter wide-string-2)
                      (wide-string-length wide-string-2))))
    (and (=f length-1 length-2)
         (=f 0 (compare-byte-vector-16-portion wide-string-1 0
                                               wide-string-2 0
                                               length-1 t)))))

;;; The function `remove-duplicate-strings' returns a new gensym-list of the
;;; unique strings in given list. Duplicate strings are reclaimed, as is the
;;; entire input list.

(defun remove-duplicate-strings (sorted-list-of-strings)
  (loop with last = nil
        for string in sorted-list-of-strings
        if (and last (completion-equal last string))
          do (reclaim-wide-string string)
        else
          collect string using gensym-cons and
          do (setq last string)
        finally
          (reclaim-gensym-list sorted-list-of-strings)))


;;; The function `get-editor-completions' returns a gensym-list of strings, all
;;; newly consed.

(defun get-editor-completions (edit-state)
  (let ((completions ()))
    (when (null current-edit-state)
      (setq current-edit-state edit-state))
    (loop for block being each subblock of (edit-workspace edit-state) do
      (frame-class-case block
        (token-menu
          (dolist (row (table-rows block))
            (dolist (cell row)
              ;; Copied from `insert-token-menu-text-cell-text-at-cursor'
              (let* ((choice? (getf (text-cell-plist cell) 'choice))
                     (text-string
                       (or (if choice? (copy-text-string choice?))
                           (convert-text-to-text-string (text? cell) nil nil nil nil nil t))))
                (unless (exclude-editor-prompt-p text-string)                
                  (gensym-push text-string completions))))))

        (category-menu                        ; Eg, "any procedure", etc.
          ;; Since we're putting this all into one list, we ought to choose just
          ;; the most general category. Would also like to mark types for names
          ;; with a little icon. Finally, we probably will need to cache this on
          ;; the client.
          (dolist (row (table-rows block))
            (dolist (text-cell row)
              (let* ((category (getfq (text-cell-plist text-cell) 'choice))
                     (names (choices-for-category-menu edit-state category 'item-name)))
                (loop for name in names doing                  
                  (unless (exclude-editor-prompt-p name)
                   (gensym-push (twith-output-to-wide-string
                                 (twrite-symbol name)
                                 (case category            ; TODO: Icons for other categories
                                   (class
                                    (twrite-character category-menu-icon-delimiter)
                                    (twrite "1"))
                                   (procedure-name
                                    (twrite-character category-menu-icon-delimiter)
                                    (twrite "2"))
                                   (variable-name   ; FIXME: No such category.
                                    (twrite-character category-menu-icon-delimiter)
                                    (twrite "3"))))
                               completions)))
                (reclaim-grammar-list names)))))

        (editor-notification
          (gensym-push (convert-text-to-text-string
                         (box-translation-and-text block) nil nil nil nil nil t)
                       completions))))
      (setq current-edit-state nil)
      (remove-duplicate-strings
        (sort-list completions #'string-lesspw nil))))

;;; The function `compute-line-and-character-from-caret' computes the line and
;;; character indexes for the *formatted text* in given editor, which is what
;;; the G2 editor wants, for given offset. The G2 editor counts lines from 1,
;;; and characters in a line from 1, except that for line 1 the first char is 0.
;; cf: find-end-of-text

(defun compute-line-and-character-from-caret (text caret)
  (loop with text-tail = text
        with text-line
        with line-length
        with lost-space-at-end-of-line
        for line from 1
        as bol = 0 then eol
        do (multiple-value-setq
               (text-line line-length lost-space-at-end-of-line text-tail)
             (get-next-text-line text-tail))
        as space = (get-length-of-space-at-end-of-line lost-space-at-end-of-line)
        as len = (+f line-length space)
        as eol = (+f bol len)
        until (<=f caret eol)
        while text-tail
        finally
          (return (values line (-f (minf caret eol) bol)))))

(defun compute-caret-from-line-and-char (text line-index character-index)
  (loop with text-tail = text
        with caret = 0
        with text-line
        with line-length
        with lost-space-at-end-of-line
        for line from 1
        do (multiple-value-setq
               (text-line line-length lost-space-at-end-of-line text-tail)
             (get-next-text-line text-tail))
        while text-line
        when (=f line line-index)
          return (+f caret character-index)
        as space = (get-length-of-space-at-end-of-line lost-space-at-end-of-line)
        do (incff caret (+f line-length space))
        finally (return caret)))


;;;; Debugger Dialog


(define-event-handler handle-debugger-dialog-message ((gensym-window window) event-plist)
  (let ((opcode (getf event-plist 'opcode 0))
        (line? (getf event-plist 'line))
        (button? (getf event-plist 'button))
        (source-stepping-p (getf event-plist 'source-stepping 'unknown))
        (frame computation-frame-at-breakpoint))
    (case opcode
      ((#.editor-set-breakpoint #.editor-disable-breakpoint #.editor-clear-breakpoint
                                #.editor-clear-breakpoints)
       (set-breakpoint-and-notify gensym-window frame line? (opcode-to-breakpoint-state opcode)))
      (t
       ;; Update source stepping from the debugger's checkbox, if it had one.
       (unless (eq source-stepping-p 'unknown)
         (debugger-set-source-stepping-p source-stepping-p))
       (when button?
         (execute-breakpoint-button button?))))))

;; TODO: We should verify that the debugger is displaying the procedure we think
;; it is.  For now this is always true since the debugger dialog is modal.

(defun debugger-send-breakpoint (gensym-window line state)
  (when (native-debugger-dialog-p gensym-window)
    (manage-debugger-dialog gensym-window (breakpoint-state-to-opcode state) line)))


;;;; Server File Browsing


;;; Telewindows sends the `list-directory' to G2 to request various types of
;;; directory listings. The native file dialog requests full listings, which are
;;; send back via list-directory-response. The native directory dialog requests
;;; concise listings, or other operations, which are sent back via
;;; send-choose-directory.



(define-event-handler handle-list-directory-message ((gensym-window window) event-plist)
  (let* ((handle? (getf event-plist 'handle))
         (opcode (getf event-plist 'opcode 0))
         (root? (getf event-plist 'root))
         (directory? (getf event-plist 'directory)))
    (when (and handle? directory? (current-window-supports-list-directory gensym-window))
      (case opcode
        (#.ld-request-full-listing
         (let ((listing (list-directory directory?)))
           (with-icp-window (gensym-window)
             (send-icp-list-directory-response handle? listing))
           (reclaim-directory-listing listing)))

        (#.ld-request-children
         (handle-list-directory-request-children gensym-window handle? root? directory?))

        (#.ld-request-refresh
         (handle-list-directory-refresh gensym-window handle? root? directory?))))))

(def-gensym-c-function c-get-system-drives-list
    (:fixnum-int "g2ext_get_sys_drives_list_as_string")
  ((:wide-string buffer)
   (:fixnum-int buflen)))

(def-gensym-c-function c-get-system-special-folders
    (:fixnum-int "g2ext_get_system_special_folders")
  ((:wide-string buffer)
   (:fixnum-int buflen)))
  		 
;;; Telewindows sends the `list-sys-drives-message' to G2 ...

(define-event-handler handle-list-sys-drives-message ((gensym-window window) event-plist)
  (let ((buffer (obtain-simple-gensym-string 300)))
    (with-icp-window (gensym-window)
      (c-get-system-drives-list buffer 300)
      (send-icp-list-sys-drives-response (copy-null-terminated-string-as-text-string buffer)))))





;;;; Native Dialog API


;;; The procedure caps for these routines have to do a little work. They create
;;; a "semaphore" G2 parameter, system call the internal procedure, and then
;;; wait until the parameter receives a value, which will be the choice from the
;;; dialog. This is how we handle KB-level modal dialogs.

;;; The variable `pending-native-dialogs' is a gensym list of native-dialog
;;; structures awaiting responses. `native-dialog-handle-parity' is flipped on
;;; each KB reset, so that we can detect stale handles.

(def-system-variable      native-dialog-handle-parity commands2 0)
(def-kb-specific-variable pending-native-dialogs commands2 () nil reclaim-native-dialog-handles)
(def-kb-specific-variable next-native=dialog-handle commands2 1)

(def-structure native-dialog
  (native-dialog-type nil)                ; Type as supplied by the user
  (native-dialog-handle 0)
  (native-dialog-item-reference? nil :reclaimer reclaim-if-evaluation-item-reference))

(defconstant most-positive-fixnum-ashf-minus-1 (ashf most-positive-fixnum -1))

(defun allocate-native-dialog-handle (type parameter)
  (let* ((handle (prog1 (logiorf (ashf next-native=dialog-handle 1)
                                 native-dialog-handle-parity)
                   (if (>=f next-native=dialog-handle most-positive-fixnum-ashf-minus-1)
                       (setq next-native=dialog-handle 0)
		     (incff next-native=dialog-handle))))
         (native-dialog (make-native-dialog)))
    (setf (native-dialog-type native-dialog) type
          (native-dialog-handle native-dialog) handle
          (native-dialog-item-reference? native-dialog) (get-reference-to-item-if-item parameter))
    (gensym-push native-dialog pending-native-dialogs)
    handle))

(defun find-native-dialog (handle)
  (loop for entry in pending-native-dialogs
        when (eql handle (native-dialog-handle entry))
          return entry))

(defun stale-native-dialog-handle-p (handle)
  (/=f (logandf handle 1) native-dialog-handle-parity))

(defun flip-native-dialog-handle-parity ()
  (setq native-dialog-handle-parity
        (logxorf native-dialog-handle-parity 1)))

(defun reclaim-native-dialog-handle (handle)
  (let ((native-dialog? (find-native-dialog handle)))
    (when native-dialog?
      (setq pending-native-dialogs
            (delete-gensym-element native-dialog? pending-native-dialogs))
      (reclaim-native-dialog native-dialog?))))

(defun reclaim-native-dialog-handles (&optional ignored-list)
  (declare (ignore ignored-list))        ; Provided by RECLAIM-VALUES-OF-KB-SPECIFIC-VARIABLES
  (loop for entry in pending-native-dialogs doing
    (reclaim-native-dialog entry))
  (reclaim-gensym-list pending-native-dialogs)
  (setq pending-native-dialogs nil))


(defun note-kb-reset-for-native-dialogs ()
  ;; Cancel all posted dialogs, and discard any pending ones.
  (do-nms-windows (gensym-window)
    (reset-native-controls gensym-window))
  ;; Flip a bit so we can detect the stale handle which will come back from
  ;; dialogs we cancelled. If somebody does two or more restarts before we
  ;; receive all the cancel messages, then we won't notice the handles are
  ;; stale. This does not cause an error, but does post logbook messages.
  ;; TODO: A better solution would be to assume that handles never wrap around,
  ;; and keep a high-water mark.
  (flip-native-dialog-handle-parity)
  ;; Reclaim all of the handles.
  (reclaim-native-dialog-handles))


;;; The function `g2-ui-dialog-is-supported' returns true if the given type of
;;; native dialog (basic, file, etc), is available on given window.  A user may
;;; prefer UIL dialogs if native ones are not available.

(defun-for-system-procedure g2-ui-dialog-is-supported (type g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (make-evaluation-boolean-value
      (case type
        ((basic message confirmation yes-no yes-no-cancel retry-cancel query
                query2)        ; Query with 2 return values: (text, button-symbol)
         (native-basic-dialogs-p gensym-window))
        (choose-file
         (native-file-dialog-without-custom-buttons-p gensym-window))
        (choose-file-custom-buttons
         (native-basic-dialogs-p gensym-window))
        (print-workspace
         (native-printing-supported-p gensym-window))
        ((custom dynamic)
         (native-custom-dialogs-p gensym-window))
        ((notification delay-notification)
         (native-animation-control-p gensym-window))))))

(defun-for-system-procedure g2-ui-post-basic-dialog (parameter message options g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (native-basic-dialogs-p gensym-window)
      (ui-stack-error "Native dialogs are not supported on ~NF." g2-window))
    (check-type-or-stack-error options
                               '(structure ((type symbol) (caption text) (icon symbol))))
    (let* ((type (evaluation-structure-slot options 'type 'message))
           ;; Dialog-type determines what sort of dialog we display, whereas
           ;; Type determines how we process the results.
           ;; Currently they can differ only for query dialogs.
           (dialog-type (if (eq type 'query2) 'query type))
           (icon    (evaluation-structure-slot options 'icon 'question))
           (caption? (evaluation-structure-slot options 'caption)))

      (unless (memq dialog-type known-basic-dialog-types)
        (ui-stack-error "~A is not a known type of basic dialog." dialog-type))
      (unless (memq icon known-basic-dialog-icons)
        (ui-stack-error "~A is not a known basic dialog icon." icon))

      (let* ((filled-string (fill-text-for-native-dialog message))
             (handle (allocate-native-dialog-handle type parameter)))
        (post-basic-dialog gensym-window handle dialog-type filled-string caption? icon)
        (reclaim-evaluation-value filled-string)
        (reclaim-evaluation-structure options)
        handle))))

(define-event-handler handle-basic-dialog-message ((gensym-window window) event-plist)
  (let* ((handle (getf event-plist 'handle))
         (type (getf event-plist 'type))
         (choice? (getf event-plist 'choice))
         (response? (unless (eq choice? 'cancel)
                      (copy-if-text-string (getf event-plist 'response)))))
    (handle-dialog-response type handle (or response? choice? 'cancel) choice?)))

(defun handle-dialog-response (dialog-type handle value &optional button?)
  (let* ((native-dialog? (find-native-dialog handle))
         (item-reference? (and native-dialog?
                               (native-dialog-item-reference? native-dialog?)))
         (parameter? nil))
    (cond ((stale-native-dialog-handle-p handle)) ; This is normal after reset-KB.
          ((null item-reference?)
           (notify-user "Warning: No receiver for ~a dialog with handle ~d."
                        dialog-type handle))
          ((null (setq parameter? (get-item-if-item-reference item-reference?)))
           (notify-user "Semaphore parameter for ~a dialog was deleted!" dialog-type))
          ((eq (native-dialog-type native-dialog?) 'query2)
           (let ((packed-value
                   ;; Pack button and value into text parm. We can be sure the
                   ;; cap will unpack it since only that cap asks for a QUERY2
                   ;; dialog.
                   (twith-output-to-wide-string
                     (twrite-symbol (or button? 'none) t)
                     (twrite-char #\/)
                     (unless (eq button? 'cancel)
                       (twrite value)))))
             (if value
                 (reclaim-evaluation-value value))
             (set-parameter-and-reclaim parameter? packed-value)))
          (t
           (set-parameter-and-reclaim parameter? value)))
    (reclaim-native-dialog-handle handle)))

;;; The function `set-parameter-and-reclaim' sets parameter to value, if
;;; possible, and reclaims value.

(defun set-parameter-and-reclaim (parameter value)
  (let ((*current-computation-frame* parameter))
    (cond ((frame-of-class-p parameter 'symbolic-parameter)
           (put-current-value parameter
                              (if (symbolp value) value 'none)
                              'symbol nil nil))
          ((frame-of-class-p parameter 'text-parameter)
           (put-current-value parameter
                              (if (wide-string-p value) value #w"")
                              'text nil nil))
          (t
           (dwarn "Invalid parameter class: ~s" parameter))))
  (when value
    (reclaim-evaluation-value value)))


;;; The function `g2-ui-cancel-dialogs' cancels any native dialogs posted on
;;; window, and discards any queued ones. We will get a message back from
;;; cancelled modal dialogs, so we don't want to clear the handle table here.

;; TODO: Handle entries for queued dialogs on window will leak until KB is
;; reset.

(defun-for-system-procedure g2-ui-cancel-dialogs (g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (cond ((native-basic-dialogs-p gensym-window)
           (reset-native-controls gensym-window))
          (t
           (cancel-classic-menus-and-dialogs gensym-window)))))

;;; The function `cancel-classic-menus-and-dialogs' cancels all classic menus
;;; and the current classic dialog, if any, on given gensym-window.

(defun cancel-classic-menus-and-dialogs (gensym-window)
  (for-workstation ((workstation-this-is-on gensym-window))
    (when (eq type-of-current-workstation-context 'dialog)
      (abort-current-workstation-context 'dialog))
    (loop for image-plane in (stack-of-image-planes (detail-pane gensym-window))
          as workspace? = (workspace-on-image-plane? image-plane)
          when (of-class-p workspace? 'menu-workspace)
            do (delete-menu workspace?))))


;;;; Choose File


(def-type-parameter choose-file-options-type
    (structure ((caption text)
                (save-file truth-value)
                (extension text)
                (ok-button-label text)
                (client-side truth-value)
                (cancel-button-label text)
                (filter (sequence (sequence text 2 3)))
                (shortcuts (sequence text)))))

;; Note: We don't insist on same filesystem. The user can choose a client-side
;; file if he wants, by specifying the CLIENT-SIDE option.

(defun-for-system-procedure g2-ui-choose-file (text-parameter pathname options g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (client-side-p (evaluation-boolean-is-true-p
                          (evaluation-structure-slot options 'client-side)))
         (use-built-in-dialog-p (or client-side-p
                                    (server-and-client-share-file-system-p gensym-window))))
    (unless (native-file-dialog-without-custom-buttons-p gensym-window)
      (ui-stack-error "Native file dialogs are not supported on ~NF." g2-window))
    (check-type-or-stack-error options choose-file-options-type)
    (unless (or use-built-in-dialog-p (native-file-dialog-p gensym-window))
      (ui-stack-error "Native server-side file dialogs are not supported on ~NF." g2-window))
    (let* ((handle (allocate-native-dialog-handle 'file text-parameter))
           (save-file-p (evaluation-boolean-is-true-p
                          (evaluation-structure-slot options 'save-file)))
           (pathname-os (if client-side-p
                            (gensym-window-os-type gensym-window)
                            g2-operating-system))
           ;; Cf post-native-file-dialog
           (flags (logiorf (if save-file-p 1 0)        ; Bit0:Save/Open, Bit1:Server/client, Bits2-4:encoded os
                           (if use-built-in-dialog-p 0 2)
                           (ashf (encode-pathname-os pathname-os) 2)))

           ;; Ensure that the default pathname has a directory part by merging
           ;; it with the current working directory (of the server), UNLESS
           ;; we're choosing a client-side file.
           (canonical-pathname
             (cond (client-side-p        ; If client-side, then for us pathname is an opaque string.
                    (copy-text-string pathname))
                   (t
                    (let* ((default-directory (g2-stream-get-default-directory))
                           (gp (gensym-merge-pathnames pathname default-directory)))
                      (prog1 (gensym-namestring gp)
                        (reclaim-text-string default-directory)
                        (reclaim-gensym-pathname gp))))))

           (caption (evaluation-structure-slot options 'caption #w"Open File"))
           (filter (compute-file-filter-from-evalue (evaluation-structure-slot options 'filter)))
           (extension (evaluation-structure-slot options 'extension #w""))
           (ok-label? (evaluation-structure-slot options 'ok-button-label))
           (cancel-label? (evaluation-structure-slot options 'cancel-button-label))
           (buttons
             (nconc
               (if ok-label?
                   (gensym-list (gensym-list 'ok 'ok (copy-if-text-string ok-label?))))
               (if cancel-label?
                   (gensym-list (gensym-list 'cancel 'cancel (copy-if-text-string cancel-label?))))))
           (places
             (when (evaluation-structure-slot options 'shortcuts)
               (loop for string being each evaluation-sequence-element of
                       (evaluation-structure-slot options 'shortcuts)
                     collect string using gensym-cons))))

      (post-file-dialog gensym-window handle 'sysproc flags
                        caption canonical-pathname extension filter buttons places)

      (reclaim-text-string canonical-pathname)
      (reclaim-gensym-tree filter)        ; Just the conses, the strings are in options.
      (reclaim-gensym-tree places)        ; Ditto
      (reclaim-gensym-tree-with-text-strings buttons)))
  (reclaim-evaluation-value pathname)
  (reclaim-evaluation-value options))

(defun compute-file-filter-from-evalue (evalue?)
  (cond ((null evalue?)
         (copy-tree-using-gensym-conses '((#w"All Files (*.*)" #w"*.*"))))
        (t
         (loop for seq being each evaluation-sequence-element of evalue?
               collect (loop for string being each evaluation-sequence-element of seq
                             collect string using gensym-cons)
                 using gensym-cons))))


;;;; Choose Directory


(def-type-parameter choose-directory-options-type
    (structure ((caption text)
                (ok-button-label text)
                (cancel-button-label text)
                (root text)
                (client-side truth-value))))

(defun choose-directory-p (gensym-window)
  (and (native-pop-up-menus-p gensym-window)
       (window-supports-choose-directory gensym-window)))

(defun-for-system-procedure g2-ui-choose-directory (text-parameter ev-pathname ev-options g2-window)
  (check-type-or-stack-error ev-options choose-directory-options-type)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (client-side-p (evaluation-boolean-is-true-p
                          (evaluation-structure-slot ev-options 'client-side)))
         (client-dialog-p (or client-side-p
                              (server-and-client-share-file-system-p gensym-window))))

    (unless (choose-directory-p gensym-window)
      (ui-stack-error "The choose-directory dialog is not supported on ~NF." g2-window))

    (cond (client-dialog-p
           (choose-directory-on-client text-parameter ev-pathname ev-options gensym-window))
          (t
           (choose-directory-on-server text-parameter ev-pathname ev-options gensym-window)))

    (reclaim-evaluation-value ev-pathname)
    (reclaim-evaluation-value ev-options)))

(defun choose-directory-on-client (text-parameter ev-pathname ev-options gensym-window)
  (let* ((handle (allocate-native-dialog-handle 'file text-parameter))
         (plist (unbox-evaluation-value ev-options '(client-side)))
         (pathname (evaluation-text-value ev-pathname)))
    (send-choose-directory gensym-window handle cd-post-client-dialog pathname plist)
    (reclaim-unboxed-evaluation-value plist)))

(defun choose-directory-on-server (text-parameter ev-pathname ev-options gensym-window)
  (unless (window-supports-choose-directory-on-server gensym-window)
    (ui-stack-error "Server-side file browsing is not supported on ~NF."
                    (g2-window-for-gensym-window? gensym-window)))

  (unless (directory-pathname-p (evaluation-text-value ev-pathname))
    (ui-stack-error "The default pathname ~NF is not a directory." ev-pathname))

  (let ((ev-root? (evaluation-structure-slot ev-options 'root)))
    (when ev-root?
      (unless (directory-pathname-p (evaluation-text-value ev-root?))
        (ui-stack-error "The specified root pathname ~NF is not a directory." ev-root?))))

  ;; TODO: Check that pathname is under root.

  (let* ((handle (allocate-native-dialog-handle 'file text-parameter))
         (plist (unbox-evaluation-value ev-options '(root client-side)))
         (gensym-pathname (canonical-directory-pathname (evaluation-text-value ev-pathname)))
         (pathname (gensym-namestring gensym-pathname))
         (default-root (default-root-directory))
         (root-gensym-pathname (canonical-directory-pathname
                                 (evaluation-structure-slot ev-options 'root default-root)))
         (root (gensym-namestring root-gensym-pathname))
         (tree (list-directories-upwards pathname root t))
         (separator (pathname-separator-as-string)))

    ;; Additional setup for server-side dialog: compute initial tree contents,
    ;; add canonicalized root directory, add separator.
    (setq plist (mutate-gensym-plist plist 'tree tree))
    (setq plist (mutate-gensym-plist plist 'root root))
    (setq plist (mutate-gensym-plist plist 'separator (copy-wide-string separator)))

    (send-choose-directory gensym-window handle cd-post-server-dialog pathname plist)

    (reclaim-text-string default-root)
    (reclaim-unboxed-evaluation-value plist)
    (reclaim-gensym-pathname root-gensym-pathname)
    (reclaim-gensym-pathname gensym-pathname)
    (reclaim-text-string pathname)))

(defun send-choose-directory (gensym-window handle opcode pathname plist)
  (with-icp-window (gensym-window)
    (send-icp-choose-directory gensym-window handle 'sysproc opcode pathname plist)))

(defun handle-list-directory-request-children (gensym-window handle root directory)
  (let* ((path-to-node (list-directories-upwards directory root))
         (subdirectories (list-subdirectories directory))
         (listing (gensym-list path-to-node subdirectories))
         (plist (gensym-list 'tree listing)))
    (send-choose-directory gensym-window handle cd-add-children directory plist)
    (reclaim-gensym-tree-with-text-strings plist)))

(defun handle-list-directory-refresh (gensym-window handle root directory)
  (let* ((listing (list-directories-upwards directory root t))
         (plist (gensym-list 'tree listing)))
    (send-choose-directory gensym-window handle cd-refresh directory plist)
    (reclaim-gensym-tree-with-text-strings plist)))


;;; The curious function `list-directories-upwards' returns a gensym-list of
;;; directories or directory listings, one for each directory from leaf upwards
;;; to root, inclusive. Each element is either a directory name, or a
;;; gensym-list (dir-name subdir-name ... subdir-name). All strings a newly
;;; consed.

(defun list-directories-upwards (leaf-pathname root-pathname &optional listings-p)
  (let* ((leaf (canonical-directory-pathname leaf-pathname))
         (root (canonical-directory-pathname root-pathname))
         (list
           (loop with gensym-pathname = leaf
                 as dirname = (if (or (gensym-pathname-name gensym-pathname)
                                      (gensym-pathname-type gensym-pathname))
                                  (gensym-name-and-type-namestring gensym-pathname)
                                  (gensym-namestring gensym-pathname))
                 as element = (if listings-p
                                  (gensym-cons dirname (list-subdirectories gensym-pathname))
                                  dirname)
                 collect element using gensym-cons
                 until (gensym-pathnames-equal-p gensym-pathname root)
                 do (setq gensym-pathname (prog1 (parent-directory-pathname gensym-pathname)
                                            (reclaim-gensym-pathname gensym-pathname)))
                 while gensym-pathname
                 finally (if gensym-pathname (reclaim-gensym-pathname gensym-pathname)))))
    (reclaim-gensym-pathname root)
    (nreverse list)))

;;; The function `list-subdirectories' returns a new, sorted gensym-list of the
;;; names of the "non-system" subdirectories of the given directory. This
;;; excludes, for example, "." and ".."  on Unix.

(defun list-subdirectories (directory)
  (let ((subdirs (sort-list (all-subdirectories-in-directory directory)
                            #'gensym-pathname-lessp nil)))
    (prog1 (loop for subdir in subdirs
                 when (or (gensym-pathname-name subdir)
                          (gensym-pathname-type subdir))
                   collect (gensym-name-and-type-namestring subdir)
                     using gensym-cons)
      (reclaim-path-list-of-gensym-pathnames subdirs))))

(defun directory-pathname-p (pathname)
  (let* ((directory (canonical-directory-pathname pathname))
         (namestring (gensym-namestring directory)))
    (prog1 (g2-stream-directory-p namestring)
      (reclaim-gensym-pathname directory)
      (reclaim-wide-string namestring))))


;;;; Printing

(def-type-parameter print-workspace-options-type
    (structure ((format (member native postscript jpeg))
                (fmt (member native postscript jpeg)) ; Since FORMAT is a reserved word.
                (pathname text)
                (quality integer)
                (use-default-printer truth-value))))

;;; The function `g2-ui-print-workspace' prints a workspace in the specified
;;; format, which defaults to Native. For native printing, it first posts the
;;; print dialog, unless the option use-default-printer:true is given, in which
;;; case it prints immediately without posting the dialog.

(defun-for-system-procedure g2-ui-print-workspace (workspace options g2-window)
  (check-type-or-stack-error options print-workspace-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
        (format (or (evaluation-structure-slot options 'format)
                    (evaluation-structure-slot options 'fmt)
                    'default))
        (quality (evaluation-structure-slot options 'quality -1)) ; JPEG quality
        (pathname? (evaluation-structure-slot options 'pathname))
        (options* (unbox-evaluation-value options)))
    (case format
      (postscript
       (print-workspace workspace))        ; TODO: use pathname? here.

      (jpeg
       ;; GENSYMCID-1170: Printing needs a workstation when initializing frame border width.
       (for-workstation ((workstation-this-is-on gensym-window))
         (print-workspace-as-image workspace pathname? format quality)))

      ((default native)                        ; Default means native-if-possible.
       (unless (native-printing-supported-p gensym-window)
         (ui-stack-error "Native print-workspace is not supported on ~NF" g2-window))

       (when (getf options* 'use-default-printer)
         (unless (window-supports-native-printing-ex gensym-window)
           (ui-stack-error "The use-default-printer option is not supported for ~NF"
                           g2-window)))

       (print-workspace-on-window workspace gensym-window options*))
      (t
       (ui-stack-error "~a is not a supported printing format." format)))
    (reclaim-unboxed-evaluation-value options*)
    (reclaim-evaluation-structure options)))

;; TODO: Notify user of completion.



;;; Notification

(defun-for-system-procedure g2-ui-post-notification (message options g2-window)
  (check-type-or-stack-error options '(structure ((caption text)
                                                  (icon symbol)
                                                  (font-size integer))))
  (g2-ui-notification-1 g2-window 'post
                        message
                        (evaluation-structure-slot options 'caption)
                        (evaluation-structure-slot options 'icon 'information)
                        (evaluation-structure-slot options 'font-size))
  (reclaim-evaluation-structure options))

(defun-for-system-procedure g2-ui-remove-notification (g2-window)
  (g2-ui-notification-1 g2-window 'remove))

(defun-for-system-procedure g2-ui-update-notification (message options g2-window)
  (reclaim-evaluation-structure options) ; Unused.
  (g2-ui-notification-1 g2-window 'update message))

(defun g2-ui-notification-1 (g2-window operation &optional message caption icon font-size)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (native-animation-control-p gensym-window) ; Suffices
      (ui-stack-error "Native notification dialogs are not supported on ~NF" g2-window))
    (when message
      (setq message (fill-text-for-native-dialog message)))
    (manage-notification gensym-window operation caption message icon font-size)
    (when message
      (reclaim-wide-string message))))


;;; Animation Control

(defun-for-system-procedure g2-ui-post-delay-notification (message options g2-window)
  (check-type-or-stack-error options '(structure ((caption text)
                                                  (animation text)
                                                  (font-size integer))))
  (when message
    (setq message (fill-text-for-native-dialog message)))
  (g2-ui-animate-1 g2-window 'post
                   message
                   (evaluation-structure-slot options 'caption)
                   (evaluation-structure-slot options 'animation)
                   (evaluation-structure-slot options 'font-size))
  (reclaim-evaluation-structure options))

(defun-for-system-procedure g2-ui-remove-delay-notification (g2-window)
  (g2-ui-animate-1 g2-window 'remove))

(defun-for-system-procedure g2-ui-update-delay-notification (message options g2-window)
  (reclaim-evaluation-structure options) ; Unused.
  (g2-ui-animate-1 g2-window 'update message))

(defun-for-system-procedure g2-ui-command-delay-notification (command g2-window)
  (unless (memq command '(stop start step))
    (ui-stack-error "~A is not a known delay-notification command." command))
  (g2-ui-animate-1 g2-window command))

(defun g2-ui-animate-1 (g2-window operation &optional message caption media arg)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (native-animation-control-p gensym-window)
      (ui-stack-error "Native delay notifications are not supported on ~NF" g2-window))
    ;; operation = post, remove, update, stop, start, seek, step
    (manage-animation gensym-window operation caption message media arg)
    (when message
      (reclaim-wide-string message))))

(defun pause-native-animations (gensym-window)
  (when (native-animation-control-p gensym-window)
    (manage-animation gensym-window 'stop)))

(defun resume-native-animations (gensym-window)
  (when (native-animation-control-p gensym-window)
    (manage-animation gensym-window 'start)))


;;;; Selection API: Procedures


;;; The `selection-api' is a set of system procedures and virtual attributes for
;;; manipulating the selection on a window, which is an otherwise hidden data
;;; structure.

(def-concept selection-api)

(defun selection-ui-enabled-or-stack-error (gensym-window)
  (or (selection-enabled-p gensym-window)
      (ui-stack-error "The selection UI is not enabled on ~NF."
                      (or (g2-window-for-gensym-window? gensym-window)
                          "(no window)"))))


;;; The function `get-image-plane-or-stack-error' returns the image-plane
;;; showing thing on given window. In multiwindow mode, we get an error because
;;; nothing is ever showing in the common frame window, which is what
;;; gensym-window corresponds to here.

(defun get-image-plane-or-stack-error (thing gensym-window)
  (let* ((workspace? (get-workspace-of-thing-if-any thing))
         (image-plane? (and workspace?
                            (image-plane-of-workspace-on-workstation
                              (workstation-this-is-on gensym-window)
                              workspace?))))
    (or image-plane?
        (ui-stack-error "~NF is not showing on ~NF"
                        thing
                        (or (g2-window-for-gensym-window? gensym-window) "(no window)")))))

(defun ui-select-deselect-body (ws-fun atom-fun list-fun thing-or-things g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (selection-ui-enabled-or-stack-error gensym-window)
    (cond ((of-class-p thing-or-things 'workspace)
           (funcall-compiled-function ws-fun thing-or-things
                                      (workstation-this-is-on gensym-window)))
          (t
           (let* ((things (import-selectable-things thing-or-things g2-window))
                  (workspace? (common-workspace-of-things? things)))
             ;; If there is a common workspace, we can batch the update.
             (cond (workspace?
                    (funcall-compiled-function
                      list-fun
                      things
                      (get-image-plane-or-stack-error workspace? gensym-window)))
                   (t
                    (dolist (thing things)
                      (funcall-compiled-function
                        atom-fun
                        thing
                        (get-image-plane-or-stack-error thing gensym-window)))))
             (reclaim-eval-list things))))
    (unless (framep thing-or-things)
      (reclaim-evaluation-value thing-or-things))))

(defun-for-system-procedure g2-ui-select (thing-or-things g2-window)
  (ui-select-deselect-body #'select-workspace #'select-thing #'select-things
                           thing-or-things g2-window))

(defun-for-system-procedure g2-ui-deselect (thing-or-things g2-window)
  (ui-select-deselect-body #'deselect-workspace #'deselect-thing #'deselect-things
                           thing-or-things g2-window))

(defun-for-system-procedure g2-ui-deselect-all (workspace g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    ;; We deliberately don't check for the selection UI enabled here, so that
    ;; this procedure can be used to work around bugs.
    (deselect-all-things (get-image-plane-or-stack-error workspace gensym-window))))

;;; The function `g2-ui-get-selection' returns an evaluation sequence of the
;;; items, connection frames and text-cells selected in given window. The first
;;; entry is guarenteed to be the "primary" selection.

(defun-for-system-procedure g2-ui-get-selection (workspace? g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (image-plane? (and workspace?
                            (get-image-plane-or-stack-error workspace? gensym-window))))
  (allocate-evaluation-sequence
    (export-list-elements (get-selection-as-eval-list image-plane?)))))

;;; The function `g2-ui-set-selection' makes the current selection on window be
;;; items, in order. Every item must be upon the same workspace, and the
;;; workspace must be showing on the given g2-window.

(defun-for-system-procedure g2-ui-set-selection (items g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (workstation (workstation-this-is-on gensym-window))
         (count (evaluation-sequence-length items))
         (things (import-selectable-things items g2-window))
         (workspace? (common-workspace-of-things? things)))
    (selection-ui-enabled-or-stack-error gensym-window)
    (cond ((=f count 0)                        ; If user originally supplied 0 items
           (when (selected-image-plane workstation)
             (deselect-all-things (selected-image-plane workstation))))
          ((null things)                ; All were filtered out.
           (ui-stack-error "None of the items in ~NV are selectable." items))
          ((null workspace?)
           (ui-stack-error "All items must be selectable and upon the same workspace."))
          (t
           (let ((image-plane
                   (get-image-plane-or-stack-error workspace? gensym-window)))
             (select-workspace workspace? workstation)
             (set-selection things image-plane)
             (reclaim-eval-list things))))))

(defun-for-system-procedure g2-ui-is-selected (thing g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (if (cond ((workspace-p thing)
               (workspace-selected-p thing (workstation-this-is-on gensym-window)))
              (t
               (thing-selected-p thing
                                 (get-image-plane-or-stack-error thing gensym-window))))
        evaluation-true-value
        evaluation-false-value)))

(defun-simple ui-get-selected-workspace (g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (workstation (workstation-this-is-on gensym-window))
         (workspace? (selected-workspace workstation)))
    (when (and workspace? (item-p workspace?)       ; serve-item-p?
               ;; GENSYMCID-1404: Always on top
               (frame-of-class-p workspace? 'kb-workspace))
      workspace?)))

(defun-for-system-procedure g2-ui-get-selected-workspace (g2-window)
  (or (ui-get-selected-workspace g2-window)
      (ui-stack-error "~NF does not have a selected kb workspace" g2-window)))

(defun-for-system-procedure g2-ui-select-workspace (workspace g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (selection-ui-enabled-or-stack-error gensym-window)
    (when (and (framep workspace)
               (workspace-p workspace))
      (let ((image-plane? (image-plane-of-workspace-on-window gensym-window workspace)))
        (when (and image-plane?
                   (selectable-image-plane-p image-plane?))
          (select-image-plane image-plane?))))))

(defun-for-system-procedure g2-ui-register-selection-callback
    (event procedure user-data g2-window) ; (symbol procedure item-or-value g2-window) : int
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (selection-ui-enabled-or-stack-error gensym-window)
    ;; Also want to index on window, though that can wait for later.
    (g2-ui-register-callback event procedure user-data g2-window nil)))

(defun-for-system-procedure g2-ui-register-workspace-callback
    (event procedure user-data workspace) ; (symbol procedure item-or-value workspace) : int
  (g2-ui-register-callback event procedure user-data workspace nil))


;;;; Views API: Procedures


;;; The function `views-api-p' is true as of 8.2a0 TW's. Although there aren't
;;; any new ICP messages, the existing messages to manage views, manage-window,
;;; manage-pane, manage-tree-view, etc, have been much enhanced.
;; TODO: *Some* of the Views API operations vould work in older TW's.

(defun views-api-p (gensym-window)
  (and (current-window-supports-views-api gensym-window)
       (native-windows-p gensym-window)))

(defun views-api-or-stack-error (gensym-window)
  (or (views-api-p gensym-window)
      (ui-stack-error "Advanced Views API features are not supported on ~NF."
                      (g2-window-for-gensym-window? gensym-window))))

(defun find-native-window-or-stack-error (gensym-window handle)
  (or (find-native-window gensym-window handle)
      (ui-stack-error "No window or view found for handle ~A." handle)))

(defun lookup-view-handle (gensym-window view-designation &optional no-stack-error)
  (let ((native-window?
          (if no-stack-error
              (find-native-window gensym-window view-designation)
              (find-native-window-or-stack-error gensym-window view-designation))))
    (if native-window?
        (native-window-handle native-window?))))

(defun-for-system-procedure g2-ui-get-selected-window-handle (g2-window)  
 (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))) 
   (cond 
     ((icp-window-p gensym-window) 
       (selected-native-window-handle gensym-window))     
     (t
       (ui-stack-error "This operation can not be performed on g2 local window ~NF" g2-window)))))

(defun-for-system-procedure g2-ui-get-window-handles (g2-window)
  (sequence-of-native-window-handles
    (map-to-gensym-window-or-stack-error g2-window)))


(defun-for-system-procedure g2-ui-is-valid-window-handle (handle g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (native-window? (find-native-window gensym-window handle)))
    (reclaim-if-evaluation-value handle)
    (if native-window?
        evaluation-true-value
        evaluation-false-value)))

(defun-for-system-procedure g2-ui-lookup-window-handle (designation g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (native-window? (find-native-window gensym-window designation)))
    (reclaim-if-evaluation-value designation)
    (cond (native-window?
           (values (allocate-evaluation-structure
                     (native-window-info native-window?))
                   evaluation-true-value))
          (t
           (values (allocate-evaluation-structure nil)
                   evaluation-false-value)))))

;;; The function `g2-ui-show-workspace' is supposed be a sysproc version of the
;;; SHOW action (actually named SHOW-NEW), except with more options. For now, it
;;; has fewer options, and exists only to provide a way to ensure that a
;;; workspace is visible.

;;; Options beyond those handled by SHOW-NEW to be added someday: class of view
;;; to create, whether to allow multiple views of the same workspace on one
;;; window, etc.

(defun-for-system-procedure g2-ui-show-workspace (workspace options g2-window)
  (check-type-or-stack-error options '(structure ((ensure-visible truth-value))))
  (let ((require-visibility? (evaluation-boolean-is-true-p
                               (evaluation-structure-slot options 'ensure-visible))))
    (reclaim-evaluation-structure options)
    (map-to-gensym-window-or-stack-error g2-window)
    (unless (frame-system-operation-is-allowed-p 'show-workspace workspace)
      (ui-stack-error
        "Cannot show ~NF.  The show action has been restricted for this item."
        workspace))
    (show-workspace workspace g2-window
                    nil nil nil nil nil nil nil nil nil nil
                    nil nil nil nil nil nil nil nil nil
                    require-visibility?)))

(defun selected-native-window-handle (gensym-window?)
  (when gensym-window?
    (let ((native-window? (selected-native-window?
                            (workstation-this-is-on gensym-window?))))
      (when native-window?
        ;; TODO: Maybe return 0, for the entire g2-window, if nothing selected
        ;; but the workstation supports native windows, simply to avoid dealing
        ;; with no-item's.
        (native-window-handle native-window?)))))

;; TODO: In stacking order, with selected window first.
(defun sequence-of-native-window-handles (gensym-window?)
  (when gensym-window?
    (let ((handles ()))
      (do-native-windows (native-window gensym-window?)
        (eval-push (native-window-handle native-window) handles))
      (allocate-evaluation-sequence handles))))


;;;; Selection API: Virtual Attributes


;;; The virtual-attribute `selected-workspace' returns the selected workspace on
;;; given window, or no-item if the selected workspace does not exist or is not
;;; an item (eg, a non-kb-workspace). The setter accepts a singleton sequence
;;; containing the workspace, in order to work around G2 grammar/compiler
;;; problems.

(def-virtual-attribute selected-workspace
    ((class g2-window)
     (or (no-item) (class kb-workspace) (sequence (class kb-workspace) 1 2))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-window)
           (when (map-g2-window-to-gensym-window g2-window)
             (ui-get-selected-workspace g2-window)))
  :setter ((g2-window workspace)
           (when (evaluation-sequence-p workspace) ; Workaround hack
             (setq workspace (evaluation-sequence-aref workspace 0)))
           (funcall-catching-stack-errors g2-ui-select-workspace workspace g2-window)))


;;; The virtual-attribute `selected-items' returns the selected items of the
;;; selected workspace of given window as a sequence. You can't get at the
;;; selection of a non-selected workspace, via an attribute, until we reify
;;; image-planes.

;;; This attribute has the property that if concluding a sequence into it does
;;; not get an error, then getting its value will return the same sequence, in
;;; the same order.

(def-virtual-attribute selected-items
    ((class g2-window)
     (or (no-item) (sequence #.type-specification-of-thing))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-window)
           (let* ((gensym-window? (map-g2-window-to-gensym-window g2-window))
                  (workspace? 
                   (and gensym-window?
                        (selected-workspace 
                         (workstation-this-is-on gensym-window?)))))
             (cond ((null workspace?)
                    nil)
                   (*current-computation-frame*
                    (g2-ui-get-selection workspace? g2-window))
                   (t
                    (let ((current-computation-flags current-computation-flags))
                      (setf (role-serve-inactive-objects?) t)
                      (g2-ui-get-selection workspace? g2-window))))))
  :setter ((g2-window items)
           (funcall-catching-stack-errors g2-ui-set-selection items g2-window)))

;; Maybe we want to let g2-windows have evaluation-attributes. Seems like any
;; item with virtual attributes needs them. The only time we don't inherit flags
;; from a parent frame is when showing the window's hidden attributes table.


;;; The virtual-attribute `g2-window-ui-style' returns the UI style of the
;;; window as a symbol, or no-item if the window is not in use.

(def-virtual-attribute g2-window-ui-style
    ((class g2-window)
     (or (no-item) (member classic standard multiwindow))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  ;; Someday this may have a setter.
  :getter ((g2-window)
           (gensym-window-ui (map-g2-window-to-gensym-window g2-window))))


;;; The virtual-attribute `g2-window-client-version' returns version info
;;; for the client connected to the g2-window, in the form of a structure.
;;; Cf g2-get-version and g2-version-of-kb-file.

(def-virtual-attribute g2-window-client-version
    ((class g2-window)
     (structure)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-window)
           (let ((icp-socket? (get-icp-socket-for-g2-window g2-window)))
             (cond ((null (get-gensym-window-for-g2-window g2-window))
                    (allocate-evaluation-structure nil))
                   (icp-socket?
                    (allocate-evaluation-structure
                      (nconc
                        (eval-list
                          'program (if (twng-window-p (get-gensym-window-for-g2-window g2-window))
                                       'twng 'tw)
                          'major-version-number (remote-icp-major-version icp-socket?)
                          'minor-version-number (canonicalize-minor-version-number
                                                  (remote-icp-minor-version icp-socket?))
                          'revision (remote-icp-revision-number icp-socket?))
                        (if (remote-icp-build-identification-string? icp-socket?)
                            (eval-list 'build-identification-string
                                       (copy-as-wide-string
                                         (remote-icp-build-identification-string? icp-socket?)))))))
                   (t
                    (allocate-evaluation-structure-inline
                      'program 'g2
                      'major-version-number major-version-number-of-current-gensym-product-line
                      'minor-version-number (canonicalize-minor-version-number
                                              minor-version-number-of-current-gensym-product-line)
                      'revision revision-number-of-current-gensym-product-line
                      'build-identification-string (copy-as-wide-string
                                                       build-identification-string)))))))

(defun canonicalize-minor-version-number (minor-version)
  (multiple-value-bind (floor rem)
      (floorf minor-version 10)
    (if (=f rem 0) floor minor-version)))


;;;; Views API: Virtual Attributes


;;; The virtual-attribute `selected-window-handle' represents the handle of the
;;; selected NATIVE window on the given g2-window, or no-item if nothing
;;; selected or the g2-window doesn't support native-windows.

(def-virtual-attribute selected-window-handle ; handle-of-selected-native-window-if-any
    ((class g2-window)
     (or (no-item) integer)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-window)
           (selected-native-window-handle
             (get-gensym-window-for-g2-window g2-window)))

  :setter ((g2-window handle)
           (let* ((gensym-window? (get-gensym-window-for-g2-window g2-window))
                  (native-window? (find-native-window gensym-window? handle)))
             (when native-window?
               (select-native-window native-window?)))))


(def-virtual-attribute window-handles
    ((class g2-window)
     (or (no-item) (sequence integer))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-window)
           (sequence-of-native-window-handles
             (get-gensym-window-for-g2-window g2-window))))



;;;; Features Procedures


;;; We need a better way for users to determine what features a particular
;;; Telewindow has, without using the kludge of calling an API function while
;;; catching errors. This was partially done for dialogs
;;; (g2-ui-dialog-is-supported), but we need a general facility.

(defun g2-ui-has-feature (feature g2-window)
  feature g2-window)

(defun g2-ui-get-feature-info (feature g2-window)
  ;; (values version structure(stock-icons-list...))
  feature g2-window)

(defun-for-system-procedure g2-ui-get-features (g2-window)
  ;; sequence of all feature names
  ;; or, structure of all possible features, with true/false?
  g2-window)



;;;; NMS Menus of UI Commands


;;; This section contains code to create NMS menus from built-in
;;; menu-descriptions, which in turn contain built-in UI commands as their
;;; choices.  As such, we have to support executing UI commands from NMS menu
;;; choices, and automatically graying choices as the UI commands become
;;; unavailable.

;;; First, we have to create the menu bar from a built-in menu-description,
;;; using NMS procedures.  Since some UI commands have submenus for their
;;; arguments, which may include items from the current selection, we
;;; theoretically have to recompute the menubar from scratch whenever the
;;; selection changes. We avoid that for now by including a fixed set of menu
;;; items.


;;; The recursive function `nms-create-command-menu' creates an NMS menu of UI
;;; commands, from a G2 menu root.  Items are enabled/disabled according to
;;; given mouse-pointer, which should represent the current selection.

;;; This function and the following require that current-g2-user-mode? and
;;; cached-kb-restrictions be bound.

(defun nms-create-command-menu (gensym-window root type mouse-pointer)
  (let ((desc (find-menu-description root)))
    (when (and desc (menu-available-p desc mouse-pointer))
      (let ((menu (nms-create-menu-1 gensym-window type nil)))
        (nms-populate-command-menu gensym-window root mouse-pointer menu)))))


;;; The function `nms-menu-item-string' is the same as menu-item-string, except
;;; that it defaults capitalize and strip-hyphens from the menu-description.

(defun nms-menu-item-string (menu-description menu-item)
  (menu-item-string menu-description menu-item
                    (menu-description-capitalize? menu-description)
                    (menu-description-strip-hyphens? menu-description)
                    ;; parameters
                    nil))


;;; The function `nms-populate-command-menu' populates an existing native menu
;;; with UI commands from G2 menu root.

(defun nms-populate-command-menu (gensym-window root mouse-pointer menu)
  (let ((desc (find-menu-description root)))
    (when (and desc (menu-available-p desc mouse-pointer))
      (setf (nms-menu-g2-menu menu) root) ; Remember the G2 menu.
      (let ((choices (get-menu-choice-list desc))) ; Handles included menus.
        (with-localization-domain 'menu
          (loop for choice in choices doing
            ;; We get a submenu either explicitly (submenu name ...) or implicitly
            ;; via a UI command that wants more arguments than can be had from a
            ;; mouse-pointer.
            (cond ((menu-item-is-spacer-p choice)
                   (nms-append-item-1 gensym-window menu 'separator))

                  ((or (atom choice)                ; UI command
                       (eq (car choice) 'command)) ; (command label command-name)
                   (let* ((command-name (if (atom choice) choice (third choice)))
                          (cmd? (find-ui-command command-name)))
                     (or cmd? (dwarn "Missing cmd ~s" choice))
                     (when cmd?
                       (nms-create-menu-tree-for-command
                         gensym-window
                         desc
                         menu
                         choice
                         cmd? mouse-pointer))))

                  ((eq (car choice) 'submenu)
                   ;; An explicit (command) submenu, as opposed to a parameter submenu.
                   ;; Create a submenu if we know how to get the choices.
                   ;; Otherwise, create a command item with "..." to say
                   ;; that it pops up another menu.
                   (let* ((submenu-name (second choice))
                          (submenu-desc? (find-menu-description submenu-name))
                          (submenu-label (and submenu-desc?
                                              (nms-menu-item-string submenu-desc? choice)))
                          (submenu? (nms-create-command-menu gensym-window submenu-name
                                                             'popup mouse-pointer)))
                     (when submenu?
                       (nms-append-submenu-1 gensym-window menu submenu-label submenu? nil))
                     (reclaim-text-string submenu-label)))

                  ((eq (car choice) 'user-menu-choice) ; (user-menu-choice choice-symbol)
                   (nms-add-menu-item-for-user-menu-choice
                     gensym-window menu (second choice)
                     (compute-frame-for-selection mouse-pointer)))

                  ((eq (car choice) 'include)) ; Handled by get-menu-choice-list

                  (t
                   ;; Eg, (ROW ...),
                   (dwarn "In nms-populate-command-menu, NYI choice: ~s for ~s" choice root)))))
        (reclaim-menu-items choices)
        menu))))


(defun compute-menu-item-label-with-shortcut (label key-code)
  (prog1 (twith-output-to-text-string
           (twrite-string label)
           (twrite-char #\tab)
           (twrite-shortcut-key key-code))
    (reclaim-text-string label)))


;;; The function `nms-create-menu-tree-for-command' creates menus and submenus
;;; for the given command.  Submenus are used to collect additional command
;;; arguments.  However, the primary argument (whatever that means) comes from
;;; the selection, so we leave it empty here, to be filled-in when the command
;;; is chosen from the menu.

(defun nms-create-menu-tree-for-command (gensym-window menu-description
                                                       menu menu-item cmd mouse-pointer)
  (let* ((partial-command (make-empty-partial-command cmd))
         (label-string (nms-menu-item-string
                         menu-description (if (symbolp menu-item) cmd menu-item)))
         ;; This call should really be command-enabled-p, but we don't have the
         ;; correct restrictions in hand at the moment. That's OK because
         ;; whenever we create the menu bar we also send the gray/ungray
         ;; messages which sets the enabledment for each item correctly.
         (flags (if (command-available-p cmd mouse-pointer) 0 mf-grayed))
         (key-code?
           (lookup-command-in-context (find-workstation-context 'top-level)
                                      (ui-command-name cmd))))
    (fill-in-immediate-arguments partial-command)
    (multiple-value-bind (choices place menu-description)
        (submenu-choices-for-next-partial-command-argument partial-command mouse-pointer)

      ;; Add shortcut, if any.  Does this work OK when command requires arguments?
      (when key-code?
        (setq label-string (compute-menu-item-label-with-shortcut label-string key-code?)))

      (cond ((null choices)
             (nms-append-item-1 gensym-window menu
                                label-string
                                cmd                ; key. No need for pc here.
                                (ui-command-documentation cmd)
                                (or (ui-command-id cmd)        ; If non-NIL, a stock command
                                    (ui-command-name cmd))
                                flags)
             (reclaim-partial-command partial-command))
            (t
             (let ((submenu
                     (nms-create-parameter-menu gensym-window partial-command menu-description
                                                choices place
                                                mouse-pointer)))
               (reclaim-menu-items choices)
               (nms-append-submenu-1 gensym-window menu label-string submenu nil flags))))
      (reclaim-text-string label-string))))


(defun lookup-command-in-item-configuration (choice-symbol frame?)
  (unless (eq current-g2-user-mode? 'administrator) ; Optimization
    (let* ((buckets (key-bindings-due-to-object-configurations frame?))
           (key-code?
             (loop for bucket in buckets
                   as key-pattern = (keymap-bucket-key-pattern bucket)
                   as handlers = (keymap-bucket-handlers bucket)
                   when (and (key-code-p key-pattern)
                             (loop for (class handler . options) in handlers
                                   thereis (eq handler choice-symbol)))
                     return key-pattern)))
      (reclaim-filter-tree buckets)
    key-code?)))


(defun nms-add-menu-item-for-user-menu-choice (gensym-window menu user-menu-choice-symbol frame?)
  (let ((label-string (translated-string-for-symbol user-menu-choice-symbol t t))
        (key-code?
          (lookup-command-in-item-configuration user-menu-choice-symbol frame?)))
    (when key-code?
      (setq label-string (compute-menu-item-label-with-shortcut label-string key-code?)))
    (nms-append-item-1 gensym-window menu
                       label-string
                       nil                ; key
                       nil                ; TODO: doc string for umc
                       (gensym-list 'user-menu-choice user-menu-choice-symbol) ; cmd
                       0)))                ; flags



;;; The function `nms-add-parameter-menu-choice' adds a choice to a parameter
;;; menu for the value of the place-th argument to partial-command

(defun nms-add-parameter-menu-choice (gensym-window partial-command menu-description
                                                    menu choice place mouse-pointer)
  (let* ((label-string (nms-menu-item-string menu-description choice))
         (pc (copy-partial-command partial-command))
         (value (transform-menu-item-after-choice menu-description choice)))
    (bind-partial-command-argument pc place value)
    (multiple-value-bind (subchoices subplace submenu-description)
        (submenu-choices-for-next-partial-command-argument pc mouse-pointer)
      (cond (subchoices
             (let ((submenu
                     (nms-create-parameter-menu gensym-window
                                                pc submenu-description
                                                subchoices subplace mouse-pointer)))
               (reclaim-menu-items subchoices)
               (nms-append-submenu-1 gensym-window menu label-string submenu nil)))

            ((eq (menu-description-make-text-cell menu-description) ; FIXME
                 'make-text-cell-for-color)
             (reclaim-partial-command pc)
             (unless (eq value 'more)
               (nms-append-special-1 gensym-window menu label-string
                                     choice ; key = value to fill-in
                                     nil    ; doc
                                     0
                                     t            ; T means value for parameter.
                                     (case (map-to-black-or-white value)
                                       (white 'black)
                                       (black 'white))
                                     value)))
            (t
             (reclaim-partial-command pc)
             (nms-append-item-1 gensym-window menu label-string
                                ;; choice will be reclaimed, so store the value in the key.
                                (menu-item-value choice) ; key = value to fill-in
                                nil            ; doc
                                t)))            ; T means value for parameter.
      (reclaim-text-string label-string))))


;;; The function `nms-create-parameter-menu' creates a tree of parameter menus
;;; for command.  Normally there is just one menu for a parm.  Some parms, like
;;; class-name, create an entire tree of menus.

(defun nms-create-parameter-menu (gensym-window partial-command menu-description
                                                choices place mouse-pointer)
  (let ((menu (nms-create-menu-1 gensym-window 'parameter nil)))
    ;; Used to find the menu-description after a choice.
    (setf (nms-menu-callback menu) (menu-description-name menu-description)
          (nms-menu-command menu) partial-command
          (nms-menu-argument menu) place)
    ;; Each choice is a value for the PLACE-th argument of command,
    ;; or else a submenu.
    (loop for choice in choices
          as first = t then nil
          doing
      (cond ((or (menu-item-is-spacer-p choice)
                 (and (consp choice)
                      (menu-item-is-spacer-p (second choice))))
             (nms-append-item-1 gensym-window menu 'separator))

            ((or (atom choice)                    ; value
                 (eq (car choice) 'choice)  ; (choice label value)
                 (eq (car choice) 'dialog)) ; (dialog label function)
             (nms-add-parameter-menu-choice gensym-window partial-command menu-description
                                            menu choice place mouse-pointer))

            ((eq (car choice) 'submenu)
             ;; Further menus for the SAME argument place.
             (let* ((subchoice (second choice))
                    (submenu-label (nms-menu-item-string menu-description choice))
                    (subchoices-function? (menu-description-submenu-choices menu-description))
                    (subchoices (when subchoices-function?
                                  (funcall-ui subchoices-function?
                                              menu-description
                                              subchoice
                                              mouse-pointer)))
                    (submenu? (nms-create-parameter-menu gensym-window
                                                         partial-command
                                                         menu-description
                                                         subchoices place
                                                         mouse-pointer)))
               (when submenu?
                 (nms-append-submenu-1 gensym-window menu submenu-label submenu? nil))
               (reclaim-menu-items subchoices)
               (reclaim-text-string submenu-label)))

            ((eq (car choice) 'row)        ; (ROW choice ... choice)
             ;; This is not right, of course: we're creating a column for each
             ;; row, so the menu is transpose of what it is supposed to be. To
             ;; fix that, we need to look at the entire choices list before
             ;; starting to add items.
;             (unless first
;               (nms-append-item-1 gensym-window menu 'break))
             (loop for row-choice? in (cdr choice) doing
               (when row-choice?
                 (nms-add-parameter-menu-choice gensym-window partial-command menu-description
                                                menu row-choice? place mouse-pointer))))
            (t
             (dwarn "In nms-create-parameter-menu, NYI menu choice: ~s" choice))))
    menu))


;;; The function `submenu-choices-for-next-partial-command-argument' returns a newly
;;; consed list of menu-items, which should be reclaimed with reclaim-menu-items.

(defun submenu-choices-for-next-partial-command-argument (partial-command mouse-pointer)
  (unless (partial-command-is-complete-p partial-command) ; Optimization
    (let* ((command (partial-command-command partial-command))
           (pursuer (ui-command-pursuer command)))
      (multiple-value-bind (argument-name argument-type argument-place)
          (funcall-ui pursuer partial-command)
        (declare (ignore argument-name))
        (multiple-value-bind (ptype? parameters options)
            (parse-presentation-type argument-type)
          (declare (ignore options))        ; Eg, :title
          (when ptype?
            (let* ((menu-name? (presentation-type-menu ptype?))
                   (menu-description? (and menu-name? (menu-description-named menu-name?)))
                   (choices (and menu-description?
                                 (compute-menu-items menu-description? mouse-pointer parameters))))
              (reclaim-presentation-type argument-type)
              (values choices argument-place menu-description?))))))))



;;;; Menubar Updating


;;; The event `handle-menu-bar-message' is sent by TW when the user clicks on
;;; the menu bar but before TW enters the modal menu loop.  G2 MUST respond with
;;; an ICP nms-enable-items message which grays, ungrays, adds, deletes items as
;;; needed to match the current KB state, especially the current selection.  TW
;;; will spin in a modal loop until the nms-enable-items message is received.

(define-event-handler handle-menu-bar-message (workstation)
  (let* ((gensym-window (window-for-workstation workstation))
         (menu-handle (or (nms-current-menu-bar? gensym-window) 0))
         (menu? (nms-lookup-handle gensym-window menu-handle)))
     ;; Added by SoftServe for Gensym-381
  (when (and global-nmsci-id-for-attributes-pane
             (twng-window-p gensym-window))
   (cond((eq global-table-of-attributes-pane nil)
	 (nms-check-menu-item (g2-window-for-gensym-window? gensym-window) 
               (nms-menu-id-to-handle gensym-window global-nmsci-id-for-attributes-pane)
               (make-evaluation-truth-value falsity)))
	((not (eq global-table-of-attributes-pane nil))
	 (nms-check-menu-item (g2-window-for-gensym-window? gensym-window) 
               (nms-menu-id-to-handle gensym-window global-nmsci-id-for-attributes-pane)
               (make-evaluation-truth-value truth)))))
  (when (and global-nmsci-id-for-hidden-attributes-pane
             (twng-window-p gensym-window))
   (cond((eq global-table-of-hidden-attributes-pane nil)
	 (nms-check-menu-item (g2-window-for-gensym-window? gensym-window) 
               (nms-menu-id-to-handle gensym-window global-nmsci-id-for-hidden-attributes-pane)
               (make-evaluation-truth-value falsity)))
	((not (eq global-table-of-hidden-attributes-pane nil))
	 (nms-check-menu-item (g2-window-for-gensym-window? gensym-window) 
               (nms-menu-id-to-handle gensym-window global-nmsci-id-for-hidden-attributes-pane)
               (make-evaluation-truth-value truth)))))
	;; End of SoftServe changes
    (update-native-menu workstation menu?)))

;; Note that we get this message even for user-level NMS menu bars, which
;; do NOT have automatice graying/ungraying.

;; TODO: event-plist ought to contain the handle of the menu to be updated.

;; Or, we could adopt a push model and update TW whenever certain things change
;; in the KB. This avoids the initial delay posting a dropdown menu from the
;; menubar, and also avoids any concerns with modal event loops, at the expense
;; of slowing down G2, especially if there are lots of idle TW's with menubars.


(defvar update-menu-values ())

;;; The function `update-native-menu' updates given menu and all its submenus to
;;; reflect the current selection on workstation. For now, we just update
;;; gray/ungray status for items which are UI commands. Later, add/remove items,
;;; etc.

(defun update-native-menu (workstation menu?)
  (for-workstation-polling (workstation)
    (let ((gensym-window current-workstation-window))
      (when (native-menu-bar-p gensym-window)
        ;; We MUST send the ICP message in all cases, even if menu is NIL since TW
        ;; is in a modal loop (with a timeout, but a long timeout), waiting for a
        ;; response.
        (cond ((null menu?)
               (with-icp-window (gensym-window)
                 (send-icp-nms-enable-items gensym-window nil)))
              (t
               ;; First check whether we need to repopulate the menu bar
               (when (and (/=f (nms-dynamic-menu-modification-tick gensym-window)
                               dynamic-menus-modification-tick)
                          (eql (nms-current-menu-bar? gensym-window)
                               (nms-developer-menu-bar? gensym-window)))
                 (update-developer-menu-bar gensym-window))

               ;; Now send the gray/ungray message.
               (let ((mouse-pointer (selection-mouse-pointer current-workstation)))
                 (with-mouse-pointer-bindings (&optional (frame? frame)) mouse-pointer
                   (let ((cached-restrictions-alist (compute-all-restrictions
                                                      (g2-user-mode-for-this-workstation?
                                                        (workstation-this-is-on gensym-window))
                                                      frame?))
                         (update-menu-values ()))
                     (update-native-menu-1 gensym-window menu? mouse-pointer)
                     (with-icp-window (gensym-window)
                       (send-icp-nms-enable-items gensym-window update-menu-values))
                     (reclaim-gensym-list update-menu-values)
                     (reclaim-filter-tree cached-restrictions-alist)
                     (release-mouse-pointer-if-any mouse-pointer))))))))))

;;; The recursive function `update-native-menu-1' recursively computes
;;; update-menu-values for the tree of menus rooted at MENU.  Each element is a
;;; packed 16-bit fixnum with the low bit the new value for the mf-grayed flag,
;;; and the high 15 bits the item handle.  This packing ensures that most values
;;; will fit into a single icp-byte.  We also update our local cache of the
;;; mf-grayed bit for each item.

(defun update-native-menu-1 (gensym-window menu mouse-pointer)
  (loop with g2-menu? = (find-menu-description (nms-menu-g2-menu menu))
        with default-restriction-type? = (and g2-menu? (menu-description-restriction-type g2-menu?))
        for item in (nms-menu-items menu)
        as cmd? = (nms-menu-item-command item)
        as restriction-type? = (restriction-type-for-command cmd? default-restriction-type?)
        as (permitted? . restrictions) = (cdr (assq restriction-type? cached-restrictions-alist))
        doing
    (cond ((nms-parameter-menu-p item)
           (assert-for-development (partial-command-p cmd?))
           (update-native-menu-item item
                                    (command-enabled-p (ui-command-named (partial-command-name cmd?))
                                                       mouse-pointer
                                                       restrictions permitted?)))
          ((nms-menu-p item)
           (update-native-menu-1 gensym-window item mouse-pointer))
          ((and cmd? (neq cmd? t) (symbolp cmd?))
           (update-native-menu-item item
                                    (command-enabled-p (ui-command-named cmd?)
                                                       mouse-pointer
                                                       restrictions permitted?)))
          ((partial-command-p cmd?)
           (update-native-menu-item item
                                    (command-enabled-p (ui-command-named (partial-command-name cmd?))
                                                       mouse-pointer
                                                       restrictions permitted?)))
          ((fixnump cmd?)                ; cmd=integer (stock commands)
           (when (ui-command-p (nms-menu-item-key item))
             (update-native-menu-item item
                                      (command-enabled-p (nms-menu-item-key item)
                                                         mouse-pointer
                                                         restrictions permitted?))))
          (t
           ;; Other cases: cmd?=NIL (separators, etc)
           (when cmd?
             (dwarn "Unknown case: cmd=~s, item=~s" cmd? item))))))

;; TODO: Disable menus, as well as items?


;;; The function `command-enabled-p' returns true if given command should be
;;; ungrayed in the menu bar. COMMAND must be either a UI command instance
;;; (structure) or a list of (user-menu-choice choice-symbol).

(defun command-enabled-p (command mouse-pointer restrictions permitted?)
  (and (command-available-p command mouse-pointer)
       (let ((name (cond ((ui-command-p command)
                          (ui-command-menu-name command))
                         ((consp command)
                          (second command))
                         (t
                          (dwarn "Junk in command: ~s" command)))))
         (if (memq name restrictions) permitted? (not permitted?)))))


;;; The function `update-native-menu-item' grays or ungrays given NMS menu item
;;; by pushing onto update-menu-values list.

(defun update-native-menu-item (item ungray-p)
  (let* ((handle (nms-menu-item-handle item))
         (old-flags (logandf (nms-menu-item-flags item) mf-grayed))
         (new-flags (if ungray-p
                        (logandf old-flags (lognotf mf-grayed))
                        (logiorf old-flags mf-grayed))))
    ;; Remember that 0 means enabled, 1 means grayed.
    (unless (=f new-flags old-flags)
      (setf (nms-menu-item-flags item) new-flags)
      #+development (if (>f handle 32767)
                        (cerror "Go on" "NMS menu handle ~d is out of range!" handle))
      ;; Packed handle[15] flag[1] into 16 bits
      (gensym-push (logiorf (ashf (logandf handle 32767) 1)
                            (if ungray-p 0 1))
                   update-menu-values))))


;;; The event-handler `handle-post-menu-message' is triggered whenever a dynamic
;;; menu is posted on the remote TW. It starts a KB-level procedure which can
;;; arbitrarily change the menu (except delete it!) before it is displayed.

(define-event-handler handle-post-menu-message ((gensym-window window) event-plist)
  (let* ((menu-handle (getf event-plist 'nms-menu-handle))
         (position (getf event-plist 'item))
         (nms-menu? (nms-lookup-handle gensym-window menu-handle)))
    (or
      (nms-execute-kb-level-callback gensym-window 'posting nms-menu? position t)
      ;; Mandatory response to TW. Do this IFF procedure not started. If
      ;; procedure was started, then we are assured that nms-procedure-exit-hook
      ;; will eventually be called, which takes care of sending the message.
      (with-icp-window (gensym-window)
        (send-icp-nms-enable-items gensym-window nil)))))

;; Simply a notification, no reply message required. Added for 8.1b0.
(define-event-handler handle-unpost-menu-message ((gensym-window window) event-plist)
  (let* ((menu-handle (getf event-plist 'nms-menu-handle))
         (nms-menu? (nms-lookup-handle gensym-window menu-handle)))
    (nms-execute-kb-level-callback gensym-window 'unposting nms-menu? -1 nil)))


;;; The event-handler `handle-menu-item-selected-message' is triggered whenever
;;; a native menu item is selected or unselected, where here selection means
;;; highlighted via the mouse or keyboard navigation, assuming that the feature
;;; has been enabled via nms-set-selection-callback. The usual case of an
;;; unselect immediately followed by a select is bundled into one event.

(define-event-handler handle-menu-item-selected-message ((gensym-window window) event-plist)
  (let* ((menu-handle (getf event-plist 'nms-menu-handle))
         (item-id (getf event-plist 'item))
         (previous-menu-handle (getf event-plist 'previous-nms-menu-handle))
         (previous-item-id (getf event-plist 'previous-item))

         (menu? (nms-lookup-handle gensym-window menu-handle))
         (item? (nms-lookup-id gensym-window item-id))
         (previous-menu? (nms-lookup-handle gensym-window previous-menu-handle))
         (previous-item? (nms-lookup-id gensym-window previous-item-id))

         (callback? (nms-lookup-callback gensym-window 'selection (or menu? item?)))
         (previous-callback? (nms-lookup-callback gensym-window 'selection (or previous-menu?
                                                                               previous-item?)))
         (g2-window? (g2-window-for-gensym-window? gensym-window)))
    (when g2-window?
      (when (and previous-callback? previous-menu?) ; This choice was unselected.
        (nms-start-callback previous-callback? 'selection g2-window?
                            (nms-menu-handle previous-menu?)
                            (if previous-item? (nms-menu-item-handle previous-item?) 0)
                            (nms-compute-activation-path gensym-window previous-menu?)
                            nil))
      (when (and callback? menu?)                    ; This choice was selected.
        (nms-start-callback callback? 'selection g2-window?
                            (nms-menu-handle menu?)
                            (if item? (nms-menu-item-handle item?) 0)
                            (nms-compute-activation-path gensym-window menu?)
                            t)))))


;;;; Developer Menu Bar Support


;;; The function `create-developer-menu-bar' creates a developer menu bar from
;;; scratch, or populates an existing menu, based on the given mouse pointer,
;;; which defaults to the selection mouse pointer.  The menu handle is returned.

(defun create-developer-menu-bar (gensym-window &optional mouse-pointer? existing-menu?)
  (let* ((workstation (workstation-this-is-on gensym-window))
         (mouse-pointer (or mouse-pointer? (selection-mouse-pointer workstation)))
         (nms-constructing-built-in-menus-p t)
         (cached-restrictions-alist (compute-all-restrictions
                                      (g2-user-mode-for-this-workstation? workstation)))
         (menu? (cond (existing-menu?
                       (nms-populate-command-menu gensym-window 'developer-menu-bar
                                                  mouse-pointer existing-menu?))
                      (t
                       (nms-create-command-menu gensym-window 'developer-menu-bar
                                                'menu-bar mouse-pointer)))))
    (setf (nms-dynamic-menu-modification-tick gensym-window) dynamic-menus-modification-tick)
    (reclaim-filter-tree-function cached-restrictions-alist)
    (unless mouse-pointer?
      (release-mouse-pointer-if-any mouse-pointer))
    (when menu?
      (nms-menu-handle menu?))))


;;; The function `ensure-developer-menu-bar' returns the possibly cached handle
;;; of the G2 developer menu bar for given window.

(defun ensure-developer-menu-bar (gensym-window)
  (or (nms-developer-menu-bar? gensym-window)
      (setf (nms-developer-menu-bar? gensym-window)
            (create-developer-menu-bar gensym-window))))

(defun install-developer-menu-bar (gensym-window)
  (when (nms-menu-bars-supported-p gensym-window)
    (let ((menu-bar? (ensure-developer-menu-bar gensym-window)))
      (when menu-bar?
        (nms-set-menu-bar-1 gensym-window menu-bar?)))))

(defun install-unconnected-menu-bar (gensym-window)
  (when (nms-menu-bars-supported-p gensym-window)
    (let* ((menu-bar-handle? (nms-current-menu-bar? gensym-window))
      (menu-bar?
        (if menu-bar-handle? (nms-lookup-handle gensym-window menu-bar-handle?))))
      (if menu-bar?
        (nms-delete-menu-1 gensym-window menu-bar? 1)
        (nms-set-menu-bar-1 gensym-window 0)))))

(defun hide-menu-bar (gensym-window)
  (when (nms-menu-bars-supported-p gensym-window)
    (nms-set-menu-bar-1 gensym-window -1)))

;;; The function `update-native-menu-bar' recreates the current menu bar. We
;;; only know how to do that for the developer menu bar. GMS probably takes care
;;; of this itself, so only menu bars built with the NMS API might want
;;; something done here. (Maybe we should permit symbols for menu strings => automatic
;;; translation with needing GFR?).

(defun update-native-menu-bar (workstation)
  (let ((gensym-window (window-for-workstation workstation)))
    (when (and (native-menu-bar-p gensym-window)
               (eql (nms-current-menu-bar? gensym-window)
                    (nms-developer-menu-bar? gensym-window)))
      (recreate-developer-menu-bar gensym-window))
    ;; We must declare ourselves done in all cases.
    (setf (nms-dynamic-menu-modification-tick gensym-window) dynamic-menus-modification-tick)))



;;; The function `update-developer-menu-bar' updates the developer menu bar
;;; in-place, without creating a new top-level menu. This is needed by the
;;; WM_INITMENU handler deep down in ext/c/msmain.c, for when the menu bar has
;;; changed in ways other than the graying of items.

(defun update-developer-menu-bar (gensym-window)
  (when (nms-menu-bars-supported-p gensym-window)
    (let ((developer-menu-bar?
            (nms-lookup-handle gensym-window (nms-developer-menu-bar? gensym-window))))
      (when developer-menu-bar?
        (nms-delete-menu-contents-1 gensym-window developer-menu-bar?)
        (create-developer-menu-bar gensym-window nil developer-menu-bar?)
        ;; We now set the menu bar to itself, just to get hViewMenu and
        ;; hWindowMenu, down in the C code, recomputed.
        (nms-set-menu-bar-1 gensym-window (nms-developer-menu-bar? gensym-window))))))

;;; The function `recreate-developer-menu-bar' computes a new developer menu bar
;;; from scratch and deletes the old one, if any. It is also installed if was
;;; currently displayed.

(defun recreate-developer-menu-bar (gensym-window)
  (when (nms-menu-bars-supported-p gensym-window)
    (let ((old-developer-menu-bar? (nms-developer-menu-bar? gensym-window)))
      (setf (nms-developer-menu-bar? gensym-window) nil)
      (when (eql (nms-current-menu-bar? gensym-window) old-developer-menu-bar?)
        (install-developer-menu-bar gensym-window))
      (when (nms-lookup-handle gensym-window old-developer-menu-bar?)
        (nms-delete-menu-1 gensym-window
                           (nms-lookup-handle gensym-window old-developer-menu-bar?)
                           t)))))


;;; The function `install-default-menu-bar' is called when a new TW connects,
;;; from restore-current-workstation-detail-pane

(defun install-default-menu-bar (gensym-window)
  (install-developer-menu-bar gensym-window))

;; TODO: NMS users may not want this to happen if they've defined their own menu
;; bar. There will be a lot of menu bar flashing.


;;; The function `note-gensym-window-initalized' is called after a gensym-window
;;; is initialized with a new set of image-planes. This happens upon kb-load and
;;; upon new TW connections.

(defun note-gensym-window-initialized (gensym-window)
  (when (selection-enabled-p)                ; -fmw, 8/22/02
    (select-default-workspace (workstation-this-is-on gensym-window))
    (initialize-ui-options gensym-window)
    (cond ((show-developer-menu-bar-p gensym-window 'connect)
           (install-default-menu-bar gensym-window))
          (t
           (hide-menu-bar gensym-window)))))


;;; The function `run-state-change-hook' is called after G2's run state changes
;;; with the operation used to change it.  Operation is either start, pause,
;;; resume, or reset. At present, it does just NMS-related stuff.

(defun run-state-change-hook (operation)
  (update-system-tray-icon)
  (case operation
    (start)                                ; Nothing to do here.
    (pause
     (do-nms-windows (gensym-window)
       (setf (nms-saved-menu-bar? gensym-window) nil)
       (when (show-developer-menu-bar-p gensym-window 'pause)
         (setf (nms-saved-menu-bar? gensym-window) (nms-current-menu-bar? gensym-window))
         (install-default-menu-bar gensym-window))
       (when (native-animation-control-p gensym-window)
         (pause-native-animations gensym-window))))
    (resume
     (do-nms-windows (gensym-window)
       (when (nms-saved-menu-bar? gensym-window)
         (nms-set-menu-bar-1 gensym-window (nms-saved-menu-bar? gensym-window)))
       (when (native-animation-control-p gensym-window)
         (resume-native-animations gensym-window))))
    ((reset clear-kb)
     (unless in-clear-kb-p                ; Optimization: a hard reset will follow shortly,
       (do-nms-windows (gensym-window)  ; via reclaim-values-of-kb-specific-variables
         (nms-reset-1 gensym-window nil)        ; Soft NMS reset
         (when (show-developer-menu-bar-p gensym-window 'reset)
           (install-default-menu-bar gensym-window))))
     (when in-clear-kb-p
       (reclaim-all-ui-callbacks))
     (note-kb-reset-for-native-dialogs)
     (note-kb-reset-for-native-views)
     (note-kb-reset-for-native-status-bars)
     (note-kb-reset-for-native-icons)
     (reset-all-ui-properties))
    (t
     (dwarn "Unknown operation in run-state-change-hook: ~s" operation))))


;;;; Native Printing


;;; The ui-command `print-to-client' requests the client to post a native print
;;; dialog. For workspaces, we don't do anything else until we get the response,
;;; which is handled in `handle-print-dialog-message'.

(define-ui-command (print-to-client :name print :dialog t :pretty-name "&Print")
    ((gensym-window window)
     &optional (workspace? workspace) (native-window? selected-native-window))
  "Print workspace or native view on client-side printer."
  (when (and (native-printing-supported-p gensym-window)
             (printable-thing-p (or workspace? native-window?))
             (if workspace?
                 (frame-system-operation-is-allowed-p 'show-workspace workspace?)
                 t))
    (cond (workspace?
           (print-workspace-on-window workspace? gensym-window))
          (native-window?
           (manage-view native-window? 'print nil)))))

;; Printable natively on the client, that is.
(defun printable-thing-p (thing)
  (or (and (framep thing) (workspace-p thing))
      (html-view-p thing)
      (chart-view-p thing)))

(defun print-workspace-on-window (workspace gensym-window &optional options)
  (cond ((native-printing-supported-p gensym-window)
         (print-workspace-natively workspace gensym-window options))
        (t
         (print-workspace workspace))))

;;; The function `print-workspace-natively' actually just tells the given
;;; window, which must be an ICP window, to post a native printer dialog.  Only
;;; when that dialog sends us back the results do we actually begin printing, in
;;; handle-print-dialog-message.

(defun print-workspace-natively (workspace gensym-window &optional options)
  (let* ((jobname (twith-output-to-wide-string
                    (tformat "~NF" workspace)))
         (uuid (item-uuid workspace))
         (uuid-string (twith-output-to-wide-string
                        (twrite-uuid-printed-representation uuid))))
    (with-icp-window (gensym-window)
      (cond ((window-supports-native-printing-ex gensym-window)
             (send-icp-native-printing-ex gensym-window uuid-string jobname options))
            (t
             #+development (when options (dwarn "Ignoring options ~s" options))
             (send-icp-native-printing-dialog gensym-window uuid-string jobname))))
    (reclaim-wide-string uuid-string)
    (reclaim-wide-string uuid)
    (reclaim-wide-string jobname)))

;;; The event-handler `handle-print-dialog-message' handles an incoming choice
;;; from the native print dialog.

(define-event-handler handle-print-dialog-message ((gensym-window window) event-plist)
  (let* ((workspace-uuid? (getf event-plist 'uuid))
         (workspace-name? (getf event-plist 'jobname))
         (workspace? (get-instance-with-uuid-if-any 'workspace workspace-uuid?)))
    (cond (workspace?
           (print-workspace workspace? gensym-window event-plist))
          (t
           (notify-user "Workspace to print, ~a, no longer exists."
                        (or workspace-name? "None"))
           (with-icp-window (gensym-window)
             (native-printing-abort-printing gensym-window))))))

(defun native-printing-supported-p (gensym-window)
  (and (icp-window-p gensym-window) ; TODO: permit local window
       (win32-window-p gensym-window)
       (window-supports-native-printing gensym-window)))

(defun get-instance-with-uuid-if-any (class uuid?)
  ;; See set-up-workspace-view-post-login
  (when uuid?
    (let ((instance? (get-instance-from-uuid-representation uuid?)))
      (when (and (framep instance?) (frame-of-class-p instance? class))
        instance?))))

(defun get-instance-with-debugging-name-if-any (class name-as-string)
  ;; See role named-by-debugging-name
  (loop for frame in all-frames-with-simple-debugging-names
        when (and (frame-of-class-p frame class)
                  (string-equalw name-as-string (get-cached-debugging-name frame)))
          do (return frame)))


;;;; Keyboard Scrolling Commands


;; These bindings are patterned after Visio zooming keyboard
;; shortcuts. (Specifically Visio Professional 10.0.525, for Windows.)  home ->
;; move to upper left, end -> move to lower left, control+home -> move to upper
;; right, control+end -> move to lower right

(define-event-handler page-left (selected-image-plane)
  (when (image-plane-has-x-scrollbar-p selected-image-plane)
    (hscroll-image-plane selected-image-plane 'pageup)))

(define-event-handler page-right (selected-image-plane)
  (when (image-plane-has-x-scrollbar-p selected-image-plane)
    (hscroll-image-plane selected-image-plane 'pagedown)))

(define-event-handler page-up (selected-image-plane)
  (when (image-plane-has-y-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'pageup)))

(define-event-handler page-down (selected-image-plane)
  (when (image-plane-has-y-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'pagedown)))

(define-event-handler line-left (selected-image-plane)
  (when (image-plane-has-x-scrollbar-p selected-image-plane)
    (hscroll-image-plane selected-image-plane 'lineup 1)))

(define-event-handler line-right (selected-image-plane)
  (when (image-plane-has-x-scrollbar-p selected-image-plane)
    (hscroll-image-plane selected-image-plane 'linedown 1)))

(define-event-handler line-up (selected-image-plane)
  (when (image-plane-has-y-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'lineup 1)))

(define-event-handler line-down (selected-image-plane)
  (when (image-plane-has-y-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'linedown 1)))

(define-event-handler raster-left (selected-image-plane)
  (when (image-plane-has-x-scrollbar-p selected-image-plane)
    (hscroll-image-plane selected-image-plane 'rasterup 1)))

(define-event-handler raster-right (selected-image-plane)
  (when (image-plane-has-x-scrollbar-p selected-image-plane)
    (hscroll-image-plane selected-image-plane 'rasterdown 1)))

(define-event-handler raster-up (selected-image-plane)
  (when (image-plane-has-y-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'rasterup 1)))

(define-event-handler raster-down (selected-image-plane)
  (when (image-plane-has-y-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'rasterdown 1)))

(defun image-plane-has-scrollbar-p (image-plane)
  (or (image-plane-has-x-scrollbar-p image-plane)
      (image-plane-has-y-scrollbar-p image-plane)))

(define-event-handler home (selected-image-plane)
  (when (image-plane-has-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'home)
    (hscroll-image-plane selected-image-plane 'home)))

(define-event-handler end (selected-image-plane)
  (when (image-plane-has-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'end)
    (hscroll-image-plane selected-image-plane 'home)))

(define-event-handler home-right (selected-image-plane)
  (when (image-plane-has-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'home)
    (hscroll-image-plane selected-image-plane 'end)))

(define-event-handler end-right (selected-image-plane)
  (when (image-plane-has-scrollbar-p selected-image-plane)
    (vscroll-image-plane selected-image-plane 'end)
    (hscroll-image-plane selected-image-plane 'end)))


;;; Microsoft-style wheel scrolling: vscroll if vscroll bar present, else
;;; hscroll if hscroll bar present, else move. Always applies to the selected
;;; image-plane, not the image-plane under the mouse.

(defparameter mouse-wheel-lines 3)        ; FIXME: Get from TW's msh_MouseWheelLines.

(define-event-handler mouse-wheel-scroll-forward (mouse-pointer selected-image-plane
                                                                x-in-window y-in-window)
  (cond ((image-plane-has-y-scrollbar-p selected-image-plane)
         (vscroll-image-plane selected-image-plane 'lineup mouse-wheel-lines))
        ((image-plane-has-x-scrollbar-p selected-image-plane)
         (hscroll-image-plane selected-image-plane 'lineup mouse-wheel-lines))
        (t
         (handle-image-plane-event 'shift-down-ten-percent selected-image-plane
                                   x-in-window y-in-window))))

(define-event-handler mouse-wheel-scroll-backward (mouse-pointer selected-image-plane
                                                                 x-in-window y-in-window)
  (cond ((image-plane-has-y-scrollbar-p selected-image-plane)
         (vscroll-image-plane selected-image-plane 'linedown mouse-wheel-lines))
        ((image-plane-has-x-scrollbar-p selected-image-plane)
         (hscroll-image-plane selected-image-plane 'linedown mouse-wheel-lines))
        (t
         (handle-image-plane-event 'shift-up-ten-percent selected-image-plane
                                   x-in-window y-in-window))))


;;;; Native Image Plane Handlers


;;; These are all notification events, sent *after* the action has already been
;;; performed by Windows. For that reason, we have to be careful to not send the
;;; corresponding message back to TW, lest we get into an infinite message loop.
;;; The `native-image-plane-updated-by-client' special variable prevents this.

;;; The &optional in these is to avoid a warning when we get messages with stale
;;; handles, somthing that is perfectly normal.

(define-event-handler handle-window-activated ((gensym-window window) &optional native-window event-plist)
  (when native-window
    (handle-window-selected native-window event-plist)))

(define-event-handler handle-window-refresh ((gensym-window window) &optional native-window event-plist)
  (when native-window
    (handle-window-refresh-1 native-window event-plist)))

(define-event-handler handle-window-moved ((gensym-window window) &optional native-window event-plist)
  (when native-window
    (handle-window-moved-1 native-window event-plist)))

(define-event-handler handle-window-sized ((gensym-window window) &optional native-window event-plist)
  (when native-window
    (handle-window-sized-1 native-window event-plist)
    (call-dialog-resize-callback-if-any gensym-window event-plist)))

(define-event-handler handle-window-closed ((gensym-window window) &optional native-window event-plist)
  (when native-window
    (handle-window-closed-1 native-window event-plist)))

(define-event-handler handle-window-hscroll ((gensym-window window)
                                             &optional native-image-plane event-plist)
  (when native-image-plane
    ;; Actually, in this case the native-window *hasn't* been updated on the client.
    (let* ((current-workspace (workspace-on-image-plane? native-image-plane))
	   (current-pane (pane-for-image-plane native-image-plane))
	   (current-gensym-window (gensym-window-for-pane current-pane)))
      (when current-workspace
	(note-scrollbar-changed current-workspace current-gensym-window)))
    (let ((native-image-plane-updated-by-client native-image-plane)
          (native-window-client-operation 'scroll)
          (scrollbar-code (getf event-plist 'code))
          (thumb-position (getf event-plist 'thumb)))
      (hscroll-image-plane native-image-plane scrollbar-code 1 thumb-position))))

(define-event-handler handle-window-vscroll ((gensym-window window)
                                             &optional native-image-plane event-plist)
  (when native-image-plane
    (let* ((current-workspace (workspace-on-image-plane? native-image-plane))
	   (current-pane (pane-for-image-plane native-image-plane))
	   (current-gensym-window (gensym-window-for-pane current-pane)))
      (when current-workspace
	(note-scrollbar-changed current-workspace current-gensym-window)))
    (let ((native-image-plane-updated-by-client native-image-plane)
          (native-window-client-operation 'scroll)
          (scrollbar-code (getf event-plist 'code))
          (thumb-position (getf event-plist 'thumb)))
      (vscroll-image-plane native-image-plane scrollbar-code 1 thumb-position))))



;;;; G2GL/G2-BPEL Commands




(define-ui-command (compile-g2gl-process-workspace
                     :name compile-g2gl-process :pretty-name "Com&pile Process")
    (workspace)
  "Compile this G2GL process"
  (when (get-g2gl-process-parent-of-workspace-if-any workspace t)
    (run-compile-g2gl-process-command
      (get-g2gl-process-parent-of-workspace-if-any workspace t))))


;;; The function `get-g2gl-process-parent-of-workspace-if-any' gets the
;;; G2GL-process instance that is the ancestor of this workspace in G2GL-process
;;; workspace hierarchy.
;;;
;;; If optional argument require-to-be-non-abstract-p is specified and true,
;;; this requires such an instance, if found, to have its
;;; this-is-an-abstract-process attribute be nil. (Such processes should not be
;;; compiled or executed.)
;;;
;;; This works by searching the parent workspace, and its parent, to all levels,
;;; and returns a parent it finds that is a G2GL-process instance, stopping and
;;; returning nil when either when there's no parent, or when the parent is not
;;; a g2gl-activity-with-body instance.

(defun get-g2gl-process-parent-of-workspace-if-any
    (workspace &optional require-to-be-non-abstract-p)
  (loop with child-workspace = workspace
        with parent
        while (setq parent (parent-of-subworkspace? child-workspace))
        when (frame-of-class-p parent 'g2gl-process)
          return (if (or (not require-to-be-non-abstract-p)
                         (not (get-slot-value
                                parent 'this-is-an-abstract-process)))
                     parent)
        while (and
                (frame-of-class-p parent 'g2gl-activity-with-body)
                (setq child-workspace (superblock? parent)))))


(define-ui-command (compile-g2gl-process :pretty-name "Com&pile Process")
    (entity)
  "Compile this G2GL process"
  (when (and (frame-of-class-p entity 'g2gl-process)
             (subworkspaces entity)
             (not (get-slot-value entity 'this-is-an-abstract-process)))
    (run-compile-g2gl-process-command entity)))


(defun run-compile-g2gl-process-command (g2gl-process)
  (let ((v (compile-g2gl-process-if-possible g2gl-process)))
    (when v
      (report-g2gl-compilation-completion-status v))))




(define-ui-command (clean-up-g2gl-compilation-postings-on-body
                     :name clean-up-g2gl-process-compilation-postings
                     :pretty-name "C&lear Compilation Postings")
    (workspace)
  "Clear error or warning messages posted during compilation of this G2GL process"
  (when (and (get-g2gl-process-parent-of-workspace-if-any workspace)
             (there-are-g2gl-compilations-postings-on-body workspace))
    (clear-g2gl-compilation-postings-on-body workspace)))


(define-ui-command (clean-up-g2gl-compilation-postings-on-process
                     :name clean-up-g2gl-process-compilation-postings
                     :pretty-name "C&lear Compilation Postings")
    (entity)
  "Clear error or warning messages posted during compilation of this G2GL process"
  (when (and (frame-of-class-p entity 'g2gl-process)
             (subworkspaces entity)
             (there-are-g2gl-compilations-postings-on-body
               (first (subworkspaces entity))))
    (clear-g2gl-compilation-postings-on-body
      (parent-of-subworkspace? (first (subworkspaces entity))))))




;;; The command named `execute-g2gl-process' is available for g2gl-process
;;; instances or subworkspaces thereof that are subworkspaces of flowchart
;;; activities to any level, with the following restrictions: (a) the system
;;; must be running (i.e., started, and not paused); (b) the G2GL-process
;;; instance at the top of the hierarchy must be active; (c) the process must
;;; either (i) be compiled (have a usable, non-disowned compilation) or (ii) be
;;; potentially compilable, meaning that it has a subworkspace.
;;;
;;; Notice that the g2gl-process instance has to be active to be executable, but
;;; its subworkspace does not.  Since we allow the process to be executed when
;;; there isn't even a subworkspace, as long as there's a usable compilation, so
;;; an inactive subworkspace should not be an issue.
;;;
;;; If the process has a usable compilation, this executes with that
;;; compilation.  Otherwise, this attempts compilation.  If the compilation is
;;; successful, i.e., no errors are reported, this executes with the resulting
;;; compilation, and otherwise does nothing further.

(define-ui-command (execute-g2gl-process-workspace
                     :name execute-g2gl-process
                     :pretty-name "E&xecute Process")
    (workspace)
  "Execute this G2GL process"
  (when (and system-is-running
             (let ((process?
                     (get-g2gl-process-parent-of-workspace-if-any
                       workspace t)))
               (and process?
                    (active-p process?))))
    (run-execute-g2gl-process-command
      (get-g2gl-process-parent-of-workspace-if-any workspace t))))

(define-ui-command (execute-g2gl-process
                     :pretty-name "E&xecute Process")
    (entity)
  "Execute this G2GL process"
  (when (and system-is-running
             (frame-of-class-p entity 'g2gl-process)
             (active-p entity)
             (or (subworkspaces entity)        ; can be compiled?
                 (and
                   (get-slot-value entity 'stack-of-compilation-versions)
                   (not (get-slot-value
                          entity
                          'latest-existing-compilation-version-was-disowned))))
             (not (get-slot-value entity 'this-is-an-abstract-process)))
    (run-execute-g2gl-process-command entity)))

(defun run-execute-g2gl-process-command (g2gl-process)
  (when (compile-g2gl-process-if-necessary-and-possible g2gl-process)
    (instantiate-g2gl-process-and-start-execution
      g2gl-process
      ;; no args for now; later, maybe have some way to enter/specify args
      nil
      nil)))





(define-ui-command (single-step :pretty-name "Single-Step") (workspace)
  "Treat every activity as a breakpoint"
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             (null (get-slot-value workspace 'execution-display-mode)))
    (change-slot-value workspace 'execution-display-mode 'single-step)))

(define-ui-command (do-not-single-step :pretty-name "Do Not Single-Step") (workspace)
  "Do not treat every activity as a breakpoint"
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             (eq (get-slot-value workspace 'execution-display-mode)
                 'single-step))
    (change-slot-value workspace 'execution-display-mode nil)))

(define-ui-command (close-and-continue :pretty-name "Close and Continue") (workspace)
  (when (frame-of-class-p workspace 'g2gl-execution-display)
    (delete-g2gl-execution-display workspace)))

(define-ui-command (break-on-execution-faults
                     :pretty-name "Break on Execution Faults")
    (workspace)
  (when (and nil                        ; NOT YET IMPLEMENTED!
             (frame-of-class-p workspace 'g2gl-execution-display))))

(define-ui-command (do-not-break-on-execution-faults
                       :pretty-name "Do Not Break on Execution Faults")
    (workspace)
  (when (and nil                        ; NOT YET IMPLEMENTED!
             (frame-of-class-p workspace 'g2gl-execution-display))))

(define-ui-command (remove-all-temporary-breakpoints
                     :pretty-name "Remove All Temporary Breakpoints")
    (workspace)
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             (get-slot-value
               workspace 'temporary-breakpoints-for-execution-display))
    (change-slot-value
      workspace 'temporary-breakpoints-for-execution-display nil)))

(define-ui-command (bring-up-source :pretty-name "Bring Up Source") (workspace)
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             (map-g2gl-execution-display-to-source-body-if-any workspace)
             (workspaces-can-be-shown-at-this-kb-level-p
               (map-g2gl-execution-display-to-source-body-if-any workspace)
               current-workstation))
    (goto-frame-instance
      (map-g2gl-execution-display-to-source-body-if-any workspace))))

(define-ui-command (pause-process-instance
                     :pretty-name "Pause Process Instance")
    (workspace)
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             ;; - not for superimposed-tracings displays: -
             (not (eq (get-slot-value workspace 'execution-display-mode)
                      'superimposed-tracings))
             (not (g2gl-execution-display-is-for-paused-process-p workspace)))
    (do-pause-process-instance-command workspace)))

(define-ui-command (resume-process-instance
                     :pretty-name "Resume Process Instance")
    (workspace)
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             ;; - not for superimposed-tracings displays: -
             (not (eq (get-slot-value workspace 'execution-display-mode)
                      'superimposed-tracings))
             (g2gl-execution-display-is-for-paused-process-p workspace))
    (do-resume-process-instance-command workspace)))


(define-ui-command (delete-process-instance
                     :pretty-name "Delete Process Instance")
    (workspace)
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             ;; - not for superimposed-tracings displays: -
             (not (eq (get-slot-value workspace 'execution-display-mode)
                      'superimposed-tracings))
             (map-g2gl-execution-display-to-execution-frame-if-any
               workspace))
    (confirm-or-cancel
      (copy-text-string "Delete this process instance?")
      'exit-g2gl-process-instance
      (slot-value-list
        (map-g2gl-execution-display-to-execution-frame-if-any workspace)
        nil))))



(define-ui-command (process-display-attributes
                     :pretty-name "Process Display Attributes")
    (workspace original-x-in-window original-y-in-window)
  (when (and (frame-of-class-p workspace 'g2gl-execution-display)
             (map-g2gl-execution-display-to-source-process-if-any workspace))
    (put-up-attributes-table
      (map-g2gl-execution-display-to-source-process-if-any workspace)
      original-x-in-window original-y-in-window
      '(individual-execution-display-mode
        superimposed-tracings-execution-display-mode))))

(define-ui-command (g2gl-system-attributes
                     :pretty-name "G2GL System Attributes")
    (workspace original-x-in-window original-y-in-window)
  (when (frame-of-class-p workspace 'g2gl-execution-display)
    (put-up-attributes-table
      g2gl-parameters
      original-x-in-window original-y-in-window)))

;; Note: this does yet -- per the spec -- arrange for the table to come down
;; with the execution display.  Do that!  Possibly that can be done through the
;; menus-for-this mechanism!  (MHD 1/26/05)


(define-ui-command (set-temporary-breakpoint) (entity workspace)
  (when (and (frame-of-class-p entity 'g2gl-activity)
             (frame-of-class-p workspace 'g2gl-execution-display)
             (unset-temporary-breakpoint-for-surrogate-activity-p
               entity workspace))
    (set-temporary-breakpoint-for-surrogate-activity
      entity workspace)))

(define-ui-command (remove-temporary-breakpoint) (entity workspace)
  (when (and (frame-of-class-p entity 'g2gl-activity)
             (frame-of-class-p workspace 'g2gl-execution-display)
             (unremoved-temporary-breakpoint-for-surrogate-activity-p
               entity workspace))
    (remove-temporary-breakpoint-for-surrogate-activity
      entity workspace)))




(define-ui-command (add-stub-for-local-handler) (entity)
  (when (and (or (frame-of-class-p entity 'g2gl-fault-handler)
                 (frame-of-class-p entity 'g2gl-compensation-handler))
             (g2gl-activity-has-no-standard-in-connections-p entity 'left))
    (let ((new-stub?
            (add-stub
              entity nil g2gl-standard-connection-class 'input 'left
              (halfw (height-of-block entity)) nil nil
              g2gl-standard-connection-line-pattern
              g2gl-standard-connection-arrows)))
      (when new-stub?
        (update-connection-images nil (superblock? entity) new-stub?)))))



(define-ui-command (redo-layout-of-g2gl-body :pretty-name "Redo Layout")
    (workspace)
  (when (get-g2gl-process-parent-of-workspace-if-any workspace)
    (redo-layout-of-g2gl-body workspace)))





;;;; Embedded Telewindows Support (TWAXL)



;;; The system procedures `twaxl-show-workspace-with-name/uuid' shows the
;;; workspace denoted by UUID or by NAME on the given Win32 HWND, within the TW
;;; process (or g2-window) designated by the session ID.

;;; Any existing view on the HWND is first removed. Then, if the workspace is
;;; already showing somewhere else on the TW, then that view is removed.

;;; Finally, if the workspace exists a view of it is placed onto the HWND.  To
;;; simply remove the view on HWND, specify "" for the NAME or the UUID. (Which
;;; means you can't display a workspace whose name is the symbol ||).

;;; If hwnd-hi and lo both 0, the HWND defaults to the windowhandle given on
;;; TW's command line.

(defun-for-system-procedure twaxl-show-workspace-with-name ((session integer)
                                                            (hwnd-hi integer)
                                                            (hwnd-lo integer)
                                                            (workspace-name text))
  (let* ((name? (and (>f (lengthw workspace-name) 0)
                     ;; This handles case and @-escapes, but is a huge macro.
                     (alphabet-symbol-from-portion-of-text workspace-name)))
         (workspace? (and name? (get-instance-with-name-if-any 'workspace name?))))
    (show-workspace-on-hwnd session hwnd-hi hwnd-lo workspace?)))


(defun-for-system-procedure twaxl-show-workspace-with-uuid ((session integer)
                                                            (hwnd-hi integer)
                                                            (hwnd-lo integer)
                                                            (workspace-uuid text))
  (show-workspace-on-hwnd session hwnd-hi hwnd-lo
                          (and (>f (lengthw workspace-uuid) 0)
                               (the-item-having-uuid 'workspace workspace-uuid))))


;;; The function `g2-ui-get-associated-gsi-interface' returns the GSI-INTERFACE
;;; for a G2-WINDOW, assuming this is a single TW/AXL control using both. If
;;; not, it signals a stack-error.

(defun-for-system-procedure g2-ui-get-associated-gsi-interface ((g2-window item))
  (declare (values item))
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (or (find-gsi-interface-with-session-id
          (gensym-window-session-id gensym-window))
        (ui-stack-error "There is no gsi-interface associated with ~NF." g2-window))))


;;; The function `g2-ui-get-associated-g2-window' returns the G2-WINDOW for a
;;; GSI-INTERFACE, assuming there is a single TW/AXL control using both. If not,
;;; it signals a stack-error.

(defun-for-system-procedure g2-ui-get-associated-g2-window ((gsi-interface item))
  (declare (values item))
  (let ((gensym-window? (find-gensym-window-with-session-id
                          (gsi-interface-session-id gsi-interface))))
    (cond (gensym-window?
           (g2-window-for-gensym-window? gensym-window?))
          (t
           (ui-stack-error "There is no g2-window associated with ~NF."
                           gsi-interface)))))


;;; The virtual-attribute `g2-window-is-embedded' is true for g2-windows
;;; representing a TW client running embedded, i.e., without its own top-level
;;; window. This is true for twplug, twaxl, etc.

(def-virtual-attribute g2-window-is-embedded
    ((class g2-window)
     truth-value
     ())
  :event-updates nil
  :initial ((win) (declare (ignore win)) nil) ;?
  :getter ((g2-window)
           (make-evaluation-boolean-value
             (let ((gensym-window? (and (of-class-p g2-window 'g2-window)
                                        (map-g2-window-to-gensym-window g2-window))))
               (and gensym-window? (embedded-window-p gensym-window?))))))


;;; The function `find-gsi-interface-with-session-id' returns the connected GSI
;;; interface for session ID, or nil.

(defun find-gsi-interface-with-session-id (session-id)
  (loop for gsi-interface being class-instances of 'gsi-interface
        when (and (gsi-icp-socket-connected-p gsi-interface) ; CHECKME: Is this the test we want?
                  (gsi-interface-session-id gsi-interface)
                  (eql session-id (gsi-interface-session-id gsi-interface)))
          return gsi-interface))

;; Must be called in a stack-eval context.
(defun record-session-id-for-current-gsi-interface (session-id)
  (let* ((rpc? (and current-computation-instance ; can be nil for system-rpc
                    (find-remote-procedure-call-for-code-body-invocation
                      current-computation-instance)))
         (gsi-interface?
           (and rpc? (get-icp-interface-for-remote-procedure-call rpc? 'no-error))))
    (when (and gsi-interface? (of-class-p gsi-interface? 'gsi-interface))
      ;; This will occur when one or more workspace views connects to a AxL gateway,
      ;; then all of them are shut down, without shutting down the gateway.  In theory,
      ;; this does not necessitate a new session, but the code which mediates the TW
      ;; connection is kept in the Workspace View, not in ActiveX Link; and so, the WSV
      ;; control always shuts down TW when all of the views are gone.  We don't want to
      ;; push that responsibility out into ActiveX Link, so we have this sub-optimal
      ;; situation instead.  -jv, 7/13/04
      (setf (gsi-interface-session-id gsi-interface?) session-id))))

;; Must be called in a stack-eval context.
(defun show-workspace-on-hwnd (session-id hwnd-hi hwnd-lo workspace?)
  (let* ((gensym-window? (find-gensym-window-with-session-id session-id))
         (g2-window? (and gensym-window?
                          (g2-window-for-gensym-window? gensym-window?)))
         (parent? (if (=f hwnd-hi hwnd-lo 0)
                      (and gensym-window? (get-hwnd-from-command-line gensym-window?))
                      (make-32bit-integer hwnd-hi hwnd-lo))))

    (unless g2-window?
      ;; FIXME: Users don't know about session IDs.
      (ui-stack-error "There is no G2-WINDOW for session ID ~D." session-id))

    (unless (native-windows-p gensym-window?)
      (ui-stack-error "Workspace Views are not supported on ~NF" g2-window?))

    (unless parent?
      (ui-stack-error "Invalid default HWND from command line ~s, for ~NF."
                      (get-gensym-window-parameter gensym-window? 'windowhandle)
                      g2-window?))

    ;; This is the only place where we find out the session-id for a
    ;; GSI-INTERFACE, unless we define a new ICP message.
    (record-session-id-for-current-gsi-interface session-id)

    (let* ((image-plane-showing-workspace?
             (get-image-plane-if-any workspace? (detail-pane gensym-window?)))
           (image-plane-within-parent?
             (find-native-image-plane-with-parent gensym-window? parent?)))

      ;; Remove existing image on view, if any.
      (when image-plane-within-parent?
        (delete-image-plane image-plane-within-parent?)) ; FIXME: Allow multiple views.

      ;; Remove other view of workspace, if any.
      (when (and image-plane-showing-workspace?
                 (neq image-plane-showing-workspace? image-plane-within-parent?))
        (delete-image-plane image-plane-showing-workspace?))

      (when workspace?
        (let ((desired-parent-of-native-window? parent?))
          ;; TODO: All the various options to show-workspace.
          (show-workspace workspace? g2-window?)))

      (reclaim-32bit-integer parent?))))

(defun get-hwnd-from-command-line (gensym-window)
  (let ((hex-string? (get-gensym-window-parameter gensym-window 'windowhandle)))
    (when (wide-string-p hex-string?)
      (read-32bit-integer-from-hex-string hex-string?))))

;; The string may have a leading "0x"
(defun read-32bit-integer-from-hex-string (string)
  (with-temporary-bignum-creation
    (let ((value 0))
      (loop for i below (lengthw string)
            as weight? = (digit-char-pw (charw string i) 16)
            if weight?
              do (setq value (+ (* value 16) weight?)))
      (make-32bit-integer (logand (ash value -16) #xFFFF)
                          (logand value #xFFFF)))))



;;;; Dynamic Dialog Event Handlers


(defun get-dialog-update-callback (dialog)
  (cond ((dynamic-dialog-update-callback? dialog)
         (get-callback-procedure (dynamic-dialog-update-callback? dialog)
                                 "dialog-update-callback"
                                 '((class g2-window) integer datum symbol (structure) datum (sequence))
                                 t nil t))
        ((dynamic-dialog-generic-callback? dialog)
         (values (get-view-callback (dynamic-dialog-generic-callback? dialog)
                                    "dialog-generic-callback")
                 'generic))))

(defun get-dialog-dismissed-callback (dialog)
  (cond ((dynamic-dialog-dismissed-callback? dialog)
         (get-callback-procedure (dynamic-dialog-dismissed-callback? dialog)
                                 "dialog-dismissed-callback"
                                 '((class g2-window) integer truth-value datum (sequence))
                                 t nil t))
        ((dynamic-dialog-generic-callback? dialog)
         (values (get-view-callback (dynamic-dialog-generic-callback? dialog)
                                    "dialog-generic-callback")
                 'generic))))

(defun get-dialog-resize-callback (dialog)
  (when (dynamic-dialog-resize-callback? dialog)
   (get-callback-procedure (dynamic-dialog-resize-callback? dialog)
                           "dialog-resize-callback"
                           '((class g2-window) integer integer integer)
                           t nil t)))


;;; `call-dialog-update-callback'

(defun call-dialog-update-callback (callback type dialog component gensym-window)
  (let* ((control-kb-id (dialog-component-kb-id component))
         (all-control-value-data?
           (if (=f dialog-response-send-all-data
                   (logandf dialog-response-send-all-data
                            (dialog-component-response-action component)))
               (obtain-values-for-all-controls dialog)))
         (user-data
           (dynamic-dialog-user-data dialog))
         ;; We call g2-window-for-gensym-window? inline here.  It's
         ;; probably impossible for it to be NIL, but if it is, the
         ;; user proc will get a g2-window that doesn't exist, which
         ;; is probably what you'd expect.
         (g2-window
           (g2-window-for-gensym-window? gensym-window)))
    (case type
      (generic
       (let ((reason-for-callback 'user-edit)
             (info (allocate-evaluation-structure
                     (nconc
                       (eval-list 'control-id control-kb-id)
                       (eval-list 'control-value (compose-up-to-date-control-value component))
                       (if all-control-value-data?
                           (eval-list 'all-control-values all-control-value-data?))))))
         (call-kb-procedure callback
                            reason-for-callback
                            g2-window
                            (dynamic-dialog-handle dialog)
                            control-kb-id
                            info
                            (copy-if-evaluation-value user-data))))
      (focus-changed
       (let ((reason-for-callback 'focus-changed)
             (new-value
               (allocate-evaluation-structure
                 (eval-list 'control-id control-kb-id
                            'control-value (compose-up-to-date-control-value component)))))
         (call-kb-procedure callback
                            g2-window
                            (dynamic-dialog-handle dialog)
                            control-kb-id
                            reason-for-callback
                            new-value
                            (copy-if-evaluation-value user-data)
                            (or all-control-value-data? (allocate-evaluation-sequence nil)))))
      (t
       (let ((reason-for-callback 'user-edit)
             (new-value
               (allocate-evaluation-structure
                 (eval-list 'control-id control-kb-id
                            'control-value (compose-up-to-date-control-value component)))))
         (call-kb-procedure callback
                            g2-window
                            (dynamic-dialog-handle dialog)
                            control-kb-id
                            reason-for-callback
                            new-value
                            (copy-if-evaluation-value user-data)
                            (or all-control-value-data? (allocate-evaluation-sequence nil))))))))


(defun call-dialog-update-callback-if-any (component gensym-window)
  (let ((dialog (dialog-component-parent-dialog component)))
    (multiple-value-bind (callback? type)
        (get-dialog-update-callback dialog)
      (when callback?
        (call-dialog-update-callback callback? type dialog component gensym-window)))))


(defun call-dialog-dismissed-callback (callback type dialog respcode gensym-window)
  (let* ((user-data (dynamic-dialog-user-data dialog))
         (dialog-ok-p (response-code-says-accept-changes-p respcode))
         (dialog-ok-truth-value
           (make-evaluation-truth-value
             (if dialog-ok-p truth falsity)))
         (all-control-value-data?
           (if dialog-ok-p
               (obtain-values-for-all-controls dialog)))
         (g2-window
           (g2-window-for-gensym-window? gensym-window)))
    (case type
      (generic
       (let ((info (allocate-evaluation-structure
                     (nconc (eval-list 'dialog-ok dialog-ok-truth-value)
                            (if all-control-value-data?
                                (eval-list 'all-control-values all-control-value-data?))))))
         (call-kb-procedure callback
                            'dismissed
                            g2-window
                            (dynamic-dialog-handle dialog)
                            dialog-ok-truth-value
                            info
                            (copy-if-evaluation-value user-data))))
      (t
       (call-kb-procedure callback
                          g2-window
                          (dynamic-dialog-handle dialog)
                          dialog-ok-truth-value
                          (copy-if-evaluation-value user-data)
                          (or all-control-value-data? (allocate-evaluation-sequence nil)))))))

(defun call-dialog-resize-callback (callback dialog width height gensym-window)
  (let ((g2-window
         (g2-window-for-gensym-window? gensym-window)))
    (call-kb-procedure callback
                       g2-window
                       (dynamic-dialog-handle dialog)
                       width
                       height)))

(defun call-dialog-gesture-callback-if-any (component keycode row column x-in-window y-in-window)
  (let* ((dialog (dialog-component-parent-dialog component))
         (dialog-view? (dynamic-dialog-view? dialog)))
    (when dialog-view?
      (invoke-view-callback dialog-view?
                            (view-callback-event-name-for-keycode keycode)
                            (dialog-component-kb-id component)
                            (make-info-for-dialog-gesture row column x-in-window y-in-window
                                                          component keycode
                                                          (native-window-gensym-window dialog-view?))
                            (dynamic-dialog-user-data dialog)))))

(defun grid-view-dialog-component-p (component)
  (eq (map-control-type-fixnum-to-symbol (dialog-component-type component))
      'grid-view))

(defun update-semaphore-parameter (dialog)
  (let* ((dialog-semaphore (dynamic-dialog-semaphore-parameter dialog))
         (serial (dynamic-dialog-semaphore-serial-number dialog)))
    (cond ((and (framep dialog-semaphore)
                (quantitative-parameter-p dialog-semaphore)
                (frame-serial-number-p serial)
                (not (frame-has-been-reprocessed-p dialog-semaphore serial)))
           (let ((*current-computation-frame* dialog-semaphore))
             (put-current-value
               dialog-semaphore
               314159 'integer nil nil)))
          (t
           ;; This could be a serious error.  We should, at least try to do
           ;; something to allow the query system procedure to contine, because
           ;; if we are here, it is likely that it is waiting to receive a
           ;; value.  We also should get this error visible to the user so they
           ;; can call customer support.  For now, though, we will do nothing
           ;; outside of development.  We need to review all instances of
           ;; dialogs-dwarn, though probably not for 8.0r0.  -jv, 5/29/04
           (dialogs-dwarn "incorrect or empty semaphore in dialog ~s" dialog)
           nil))))

;;; `handle-dialog-update'

(define-event-handler handle-dialog-update ((gensym-window window) event-plist)
  (let* ((initiator (getf event-plist 'initiator))
         (dialog-id (getf event-plist 'dialog-id))
         (control-id (getf event-plist 'control-id))
         (new-value (getf event-plist 'new-value))
         (dialog (and (fixnump dialog-id) (lookup-dialog-given-handle gensym-window dialog-id)))
         (component? (and dialog (lookup-component-given-component-internal-id
                                   control-id dialog))))
    (cond
      ((null dialog)
       (dialogs-stack-error nil "received dialog update callback for nonexistent dialog!"))
      (t
       (unless (eql control-id id-for-no-component)
         (set-new-value-of-component-or-components
           dialog control-id new-value))
       (case initiator
         (#.tw-initiated-update
          (cond ((null component?)
                 (dialogs-stack-error dialog "received update for nonexistent dialog component"))
                ((response-code-says-no-callback-p (dialog-component-response-action component?))
                 ;; Even if no user-level callback is requested, we still need
                 ;; to do some processing for grid views to apply incremental
                 ;; updates. -fmw, 2/21/07
                 (when (grid-view-dialog-component-p component?)
                   (grid-view-apply-updates (dialog-component-g2-representation? component?)
                                            (dialog-component-incoming-value? component?))))
                (t
                 (multiple-value-bind (callback? type)
                     (get-dialog-update-callback dialog)
                   (when callback?        ; If no callback specified -- this is perfectly fine.  Do nothing.
                     (call-dialog-update-callback callback? type dialog component? gensym-window))))))

         (#.tw-multi-update-begin
          (setf (dynamic-dialog-initiating-control dialog) control-id))

         (#.g2-multi-update-begin
          (setf (dynamic-dialog-initiating-control dialog) control-id))

         ((#.tw-multi-update-continue #.g2-multi-update-continue
                                      #.tw-multi-update-finish)
          ;; nothing to do here?  good to send this event anyway?
          )
         (#.focus-changed-update
          (cond ((null component?)
                 (dialogs-stack-error dialog "received update for nonexistent dialog component"))
                ((response-code-says-no-callback-p (dialog-component-response-action component?))
                 ;; Even if no user-level callback is requested, we still need
                 ;; to do some processing for grid views to apply incremental
                 ;; updates. -fmw, 2/21/07
                 (when (grid-view-dialog-component-p component?)
                   (grid-view-apply-updates (dialog-component-g2-representation? component?)
                                            (dialog-component-incoming-value? component?))))
                (t
                 (multiple-value-bind (callback? type)
                     (get-dialog-update-callback dialog)
                   (when callback?        ; If no callback specified -- this is perfectly fine.  Do nothing.
                     (call-dialog-update-callback callback? 'focus-changed dialog component? gensym-window))))))

         (#.g2-multi-update-finish
          (update-semaphore-parameter dialog))
         (t
          ;; G2 case not yet implemented, but we still need to set the semaphore 
          (update-semaphore-parameter dialog)
          (dialogs-dwarn "unsupported initiator in handle-dialog-update: ~s"
                         initiator)))))))

;;; `handle-dialog-dismissed'

(define-event-handler handle-dialog-dismissed ((gensym-window window) event-plist)
  (let* ((dialog-id (getf event-plist 'dialog-id))
         (respcode (getf event-plist 'dialog-response-code))
         (dialog (and (fixnump dialog-id) (lookup-dialog-given-handle gensym-window dialog-id))))
    (cond
      ((or (null dialog) (=f dialog-id handle-for-no-dialog))
       (dialogs-dwarn "error: got a callback for invalid dialog (~s)~%" event-plist))
      ((response-code-indicates-client-side-problem-p respcode)
       (dialogs-stack-error dialog "dialog ~d has failed due to an unknown problem in Telewindows"
                            dialog-id))
      (t
       (multiple-value-bind (callback? type)
           (get-dialog-dismissed-callback dialog)
         (cond ((null callback?)
                (dialogs-dwarn "no dismissed callback found for dialog ~s (~d)~%" dialog dialog-id))
               (t
                (call-dialog-dismissed-callback callback? type dialog respcode gensym-window))))))
    ;; we get here from any of the cases above which do not result in
    ;; stack-errors, including the ones (like not having any callback) which
    ;; result in development warnings.  -jv, 9/5/06
    ;; Right.  Including the one where we have no dialog.  So we can't just
    ;; go ahead and reclaim.  Do a check first.  -jv, 9/7/06
    (when (dynamic-dialog-p dialog)
      (reclaim-dynamic-dialog dialog))))

(defun call-dialog-resize-callback-if-any (gensym-window event-plist)
  (let* ((dialog-id (getf event-plist 'window))
         (dialog (and (fixnump dialog-id) (lookup-dialog-given-handle gensym-window dialog-id)))
         (width (getf event-plist 'width))
         (height (getf event-plist 'height)))
    (when dialog
      (let ((callback? (get-dialog-resize-callback dialog)))
        (when callback?
          (call-dialog-resize-callback callback? dialog width height gensym-window))))))


;;; `handle-miscellaneous-dialog'

(define-event-handler handle-miscellaneous-dialog ((gensym-window window) event-plist)
  (let* ((dialog-id (getf event-plist 'dialog-id))
         (control-id (getf event-plist 'control-id))
         (message-type (getf event-plist 'message-type))
         (info-string (getf event-plist 'info))
         (dialog (lookup-dialog-given-handle gensym-window dialog-id))
         (the-control (and control-id dialog
                           (lookup-component-given-component-internal-id
                             control-id dialog))))
    ;; currently we only handle one message-type, but we verify anyway.  -jv, 7/25/06
    (case message-type
      (#.g2-send-wsv-address
       ;; We already did error checking to make sure the workspace existed, when we
       ;; created the component.  This is only happening a split second later.  But,
       ;; who knows?  The workspace might have gone away since then.  Always check.
       (let* ((workspace? (and (dialog-component-p the-control)
                               (workspace-dialog-component-requested-workspace?
                                 (dialog-component-original-value? the-control))))
              (serial-number (gensym-window-serial-number gensym-window))
              (hwnd-components (and info-string (read-32bit-integer-from-hex-string info-string))))
         (when (of-class-p workspace? 'workspace)
           (show-workspace-on-hwnd serial-number (car hwnd-components) (cdr hwnd-components)
                                   workspace?)
           (reclaim-32bit-integer hwnd-components))))
      (t
       #+development
       (cerror "Continue"
               "Unrecognized message-type for dialog 'miscellaneous' event.")))))

(defun view-callback-event-name-for-keycode (keycode?)
  (cond ((null keycode?)
         nil)
        ((mouse-key-code-p keycode?)
         (mouse-click-event-name
           (case (key-code-mouse-button-name keycode?)
             (left 'left-click)
             (middle 'middle-click)
             (right 'right-click))
           (key-modifier-bits keycode?)))
        (t
         'key-press)))

(defun make-info-for-dialog-gesture (row column x-in-window y-in-window
                                         component? keysym gensym-window)
  (multiple-value-bind (user-window-x user-window-y)
      (gensym-window-point-to-user-window-point gensym-window x-in-window y-in-window)
    (let ((parseable-canonical-keycode
            (parseable-symbol-from-key-code (canonicalize-key-code keysym)))
          (tabular-view-p (eq (map-control-type-fixnum-to-symbol (dialog-component-type component?))
                              'tabular-view))
          (grid-view-p (eq (map-control-type-fixnum-to-symbol (dialog-component-type component?))
                           'grid-view)))
      (nconc
        (eval-list 'x user-window-x)
        (eval-list 'y user-window-y)
        (eval-list 'key parseable-canonical-keycode)
        (if tabular-view-p
            (eval-list
              'selected-rows
              (tabular-view-currently-selected-rows component?)))
        (if grid-view-p
            (eval-list
              'selected-cells
              (grid-view-currently-selected-cells component?)))
        (unless (eql row -1)
          (eval-list (if tabular-view-p 'logical-id 'row)
                     (copy-if-evaluation-value row)))
        (unless (eql column -1)
          (eval-list 'column (copy-if-evaluation-value column)))))))

(define-event-handler handle-dialog-gesture ((gensym-window window) event-plist
                                             x-in-window y-in-window)
  (let* ((handle? (getf event-plist 'window))
         (dialog-view? (find-native-window gensym-window handle? 'g2-dialog-view))
         (dialog? (and dialog-view? (dialog-view-custom-dialog? dialog-view?)))
         (control-id? (getf event-plist 'control-id))
         (component? (and control-id? dialog?
                          (lookup-component-given-component-internal-id
                            control-id? dialog?)))
         (keycode? (getf event-plist 'key))
         (row (getf event-plist 'row -1))
         (column (getf event-plist 'column -1)))
    (cond ((null dialog-view?))
          ((null keycode?))
          ((null component?)
           (dialogs-stack-error nil "Received gesture for nonexistent dialog component."))
          (t
           (call-dialog-gesture-callback-if-any component? keycode? row column x-in-window y-in-window)))))


;;;; Modal UI Timeout


;;; The function `g2-set-move-resize-time-limit' specifies the *maximum* time
;;; that G2 will spend, frozen, in a modal loop to move or resize its main
;;; window, or no time limit if 0. It implements the suggestion HQ-5065576
;;; "Timeout for modal move/resize operations on Windows", which is in turn just
;;; a workaround for the real bug, HQ-3499839 "G2 freezes while moving main
;;; window". For that reason, this will remain undocumented and exposed only to
;;; selected users (eg, CTC).

;;; Note that once the real bug is fixed, then this procedure can become a
;;; no-op, since G2 will always spend 0 seconds frozen, satisfying any maximum.

(defun-for-system-procedure g2-set-move-resize-time-limit ((seconds integer))
  (declare (values integer))
  (c-set-move-resize-time-limit seconds))

(def-gensym-c-function c-set-move-resize-time-limit
    (:fixnum-int "g2ext_set_move_resize_time_limit")
  ((:fixnum-int seconds)))




(def-type-parameter html-help-command-type
    (member display-topic display-contents display-index display-popup destroy))

(def-type-parameter html-help-options-type
    (structure ((help-file-directory text) ; Default: exe directory
                (help-file-name text)           ; Default: "Master.chm"
                (topic (or text integer))  ; Default: ""
;                (x integer)                   ; Position for popup help. Default: mousepos
;                (y integer)
                )))

(defun html-help-p (gensym-window)
  (and (telewindows-window-p gensym-window) ; Notice we permit the classic UI here
       (win32-window-p gensym-window)
       (window-supports-html-help-ex gensym-window)))

(defun-for-system-procedure g2-ui-html-help (command options g2-window)
  (check-type-or-stack-error command html-help-command-type)
  (check-type-or-stack-error options html-help-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (html-help-p gensym-window)
      (ui-stack-error "HTML Help is not supported on ~NF" g2-window))
    (let* ((options* (unbox-evaluation-value options))
           (topic? (getf options* 'topic))
           (cmd (case command
                  (display-topic (if (fixnump topic?) hh-help-context hh-display-topic))
                  (display-contents hh-display-toc)
                  (display-index hh-display-index)
                  (display-popup hh-display-text-popup)
                  (destroy hh-close-all))))
      (cond ((icp-window-p gensym-window)
             (with-icp-window (gensym-window)
               (send-icp-html-help-ex cmd options*)))
            (t
             (html-help-ex cmd options*)))
      (reclaim-unboxed-evaluation-value options*))))


;;;; Mouse Cursors


(def-type-parameter mouse-cursors-type        ; Order must agree with g2pvt_set_mouse_cursor
    (member default arrow cross hand help i-beam circle-slash
            size-all size-ne-sw size-ns size-nw-se size-we up-arrow wait))

(defparameter mouse-cursors (cdr mouse-cursors-type))

(defun mouse-cursor-id (cursor)
  (or (position cursor mouse-cursors) 0))

(def-virtual-attribute mouse-cursor
    ((class g2-window)
     #.mouse-cursors-type
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((g2-window)
           (retrieve-ui-property g2-window 'mouse-cursor))
  :setter ((g2-window cursor)
           (modify-ui-property g2-window 'mouse-cursor cursor)))


;;;; UI Properties

(defparameter random-lisp-enums '(nil t left top right bottom        ; Sync with LK_LEFT, etc.
                                  automatic size-to-fit fixed compressed))

(defun lisp-enum-value (symbol)
  (or (position symbol random-lisp-enums) -1))

(defun eval-lisp-enums (list)
  (loop for sublist on list
        as element = (car sublist)
        when (symbolp element)
          do (setf (car sublist) (lisp-enum-value element)))
  list)

;; Just one more of these, and I'll make a facility.
;; Sync order with UIPROP_CURSOR, etc.
(defparameter all-ui-properties '(mouse-cursor theme enabled no-raise))

(defun ui-property-id (property)
  (or (position property all-ui-properties) -1))

(defun ui-property-default-value (gensym-window property)
  (case property
    (mouse-cursor 'default)
    (theme (default-ui-theme gensym-window))
    (enabled t)
    (no-raise nil)))

(defun ui-property-icp-value (property value)
 (case property
   (mouse-cursor (mouse-cursor-id value))
   (theme value)
   (enabled (if value 1 0))
   (no-raise (if value 1 0))))

(defun ui-property-permanent-p (property) ; i.e., survives reset.
  (or (eq property 'no-raise)
      (and do-not-allow-user-interactions-during-kb-load?
           (or (eq property 'enabled)
               (eq property 'mouse-cursor)))))

(defun retrieve-ui-property (g2-window property)
  (let ((gensym-window? (get-gensym-window-for-g2-window g2-window)))
    (when gensym-window?
      (get-ui-property gensym-window? property
                       (ui-property-default-value gensym-window? property)))))

(defun modify-ui-property (g2-window property value)
  (let ((gensym-window? (get-gensym-window-for-g2-window g2-window)))
    (when gensym-window?
      (change-ui-property gensym-window? property value))
    nil))

(defun change-ui-property (gensym-window property value)
  (let* ((property-id (ui-property-id property))
         (default-value (ui-property-default-value gensym-window property))
         (old-value (get-ui-property gensym-window property default-value))
         (icp-value (ui-property-icp-value property value)))
    (unless (eql value old-value)
      (if (eql value default-value)
          (remove-ui-property gensym-window property)
          (set-ui-property gensym-window property value))
      (when (window-supports-manage-ui-properties gensym-window)
        (manage-ui-properties-1 gensym-window property-id icp-value)))
    old-value))

(defun reset-all-ui-properties ()
  (loop for workstation in workstations-in-service
        as gensym-window = (window-for-workstation workstation)
        doing
    (for-workstation (workstation)
      (loop for property in all-ui-properties doing
        (unless (ui-property-permanent-p property)
          (change-ui-property gensym-window property
                              (ui-property-default-value gensym-window property)))))))

;;; The function `enable-ui-on-all-workstations' disables user input, and
;;; changes the mouse cursor to an hour glass, on all workstations for which
;;; that is possible, or undoes that.

(defun enable-ui-on-all-workstations (enable)
  (loop for workstation in workstations-in-service
        as gensym-window = (window-for-workstation workstation)
        doing
    (for-workstation (workstation)
      (change-ui-property gensym-window 'mouse-cursor (if enable 'default 'wait))
      (change-ui-property gensym-window 'enabled enable))))


;;; The function `initialize-ui-options' is called in a for-workstation context.
;;; It's job is to initialize "permanent" UI options on the given window, upon
;;; KB-load or a new TW connection.

(defun initialize-ui-options (gensym-window)
;  (change-ui-property gensym-window 'no-raise (not (right-click-lifts-to-top-in-native-ui-p)))
  gensym-window)


(defun initialize-ui-options-on-all-workstations ()
  (loop for workstation in workstations-in-service
        as gensym-window = (window-for-workstation workstation)
        doing
    (for-workstation (workstation)
      (initialize-ui-options gensym-window))))




(def-type-parameter tabbed-mdi-options-type
    (structure (;(grouped truth-value)
                (tab-position (member left top right bottom))
                (tab-layout (member automatic size-to-fit fixed compressed))
                (show-icons truth-value))))

(defun tabbed-mdi-supported-p (gensym-window)
  (and (twng-window-p gensym-window)
       (current-window-supports-tabbed-mdi-mode gensym-window)))

(defun save-mdi-children (gensym-window)
  (do-native-windows (native-window gensym-window)
    (when (mdi-child-p native-window)
      (save-native-window-geometry native-window)
      (when (or (native-window-maximized-p native-window)
                (native-window-minimized-p native-window))
        (show-native-window native-window sw-restore)))))

(defun restore-mdi-children (gensym-window)
  (do-native-windows (native-window gensym-window)
    (when (mdi-child-p native-window)
      (gensym-dstruct-bind ((left top right bottom state style exstyle)
                           (native-window-saved-geom native-window))
        (let ((image-plane? (native-image-plane? native-window)))
          (cond (left
                 (when (and state (neq state 'normal))
                   (%set-native-window-state native-window state))
                 (reshape-native-window-and-update-scroll-bars native-window left top right bottom)
                 ;; Restore style after shape has been restored.
                 (%set-native-window-style native-window style exstyle)
                 (when image-plane?
                   (canonicalize-scroll-position image-plane?)))
                (t
                 ;; Windows created while in tabbed mode: best we can do.
                 (%set-native-window-style native-window default-mdi-child-style 0)
                 (when image-plane?
                   (synchronize-shape-of-native-image-plane image-plane?)))))))))

;; Yeech.
(defun tabbed-mdi-encode-options (options)
  (loop for sublist on options by #'cddr
        as (property value) = sublist
        as opcode = (case property
                      (show-icons #.mdi-show-icons)
                      (tab-position #.mdi-tab-position)
                      (tab-layout #.mdi-tab-layout))
        as val = (lisp-enum-value value)
        doing
    (setf (car sublist) opcode
          (cadr sublist) val))
  options)

(defun-for-system-procedure g2-ui-tabbed-mdi-mode (tabbed-ev options g2-window)
  (check-type-or-stack-error options tabbed-mdi-options-type)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (tabbed-mdi-supported-p gensym-window)
      (ui-stack-error "Tabbed MDI mode is not supported on ~NF" g2-window))
    (let* ((was-tabbed (tabbed-mdi-p gensym-window))
           (tabbed (evaluation-truth-value-is-true-p tabbed-ev))
           (options* (tabbed-mdi-encode-options
                       (unbox-evaluation-value options)))
           (opcode (if tabbed #.mdi-grouped-mode #.mdi-normal-mode)))
      (when (and (not was-tabbed) tabbed)
        (save-mdi-children gensym-window))
      (tabbed-mdi-mode-1 gensym-window opcode options*)
      (when (and was-tabbed (not tabbed))
        (restore-mdi-children gensym-window))
      (set-ui-property gensym-window 'tabbed-mdi tabbed)
      (reclaim-unboxed-evaluation-value options*)))
  (reclaim-evaluation-truth-value tabbed-ev)
  (reclaim-evaluation-value options))


;;; The sysproc `g2-get-long-amount' returns amount of long variables in G2 Server 

(defun-for-system-procedure g2-get-long-amount ()
  0) ; obsoleted by GENSYMCID-1365

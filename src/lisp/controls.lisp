;; -*- Mode: Lisp; Package:AB; Base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module CONTROLS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Mark H. David, John Valente, Paul Konigsberg, Allan Scott, Andreas Hofmann





;; In TRAVERSALS

(declare-forward-reference add-as-inferior-block function)

#+maybe
(declare-forward-reference send-window-new-mode function) ; VIEW-G2

;; EVENTS-G2
(declare-forward-reference send-ws-representations-item-icon-variables-change function)
(declare-forward-reference send-ws-representations-item-rotated function)
(declare-forward-reference send-ws-representations-item-virtual-attribute-change function)

;; VIEW-G2
(declare-forward-reference update-ui-client-for-show function)
(declare-forward-reference update-ui-client-for-hide function)
(declare-forward-reference set-ui-client-session-user-is-valid function)
(declare-forward-reference set-ui-client-session-mode-is-valid function)
(declare-forward-reference ui-client-session-workspaces-function function)
(declare-forward-reference representation-address-valid-p function)
(declare-forward-reference select-workspace function)
(declare-forward-reference note-gensym-window-initialized function)

;; COMMANDS0
(declare-forward-reference uncolumnified-list-of-colors-for-level function)

;; COMMANDS1
(declare-forward-reference set-simulate-proprietary-mode function)

;; COMMANDS2
(declare-forward-reference install-unconnected-menu-bar function)
(declare-forward-reference send-native-icon function)
(declare-forward-reference send-native-bitmap function)
(declare-forward-reference valid-icon-designation-p function)
(declare-forward-reference copy-icon-designation function)
(declare-forward-reference reclaim-icon-designation function)
(declare-forward-reference preprocess-container-options-1 function)
(declare-forward-reference get-dialog-dismissed-callback function)
(declare-forward-reference call-dialog-dismissed-callback function)


;;;; Buttons



;;; A `button' is an entity associated with actions in response to mouse action
;;; by the user. A button (or subclass thereof) may contain subblocks, and
;;; these may fall outside of the button's own block rectangle.

;;; Typical subblocks include: a text box containing the `label' for the button
;;; and temporary subblocks used to highlight portions of the button.  e.g. an
;;; X inside of a check box (to show it is checked), a black circle inside of a
;;; radio button (to show it is on), or an inner ring inside of a radio button
;;; (to show that the mouse down inside of it and it will be turned on if the
;;; mouse is released at this time).

;;; Since a button usually displays a label, it does not show its name in a name
;;; box; nor does it have a NAME menu choice on its menu.  It can however [as of
;;; 3.0, starting 7/3/91] be given a name, e.g., through its NAMES (alias for
;;; name-or-names-for-frame) attribute in its table.


;;; Icons for Buttons
;;;
;;; Icon descriptions for several of the buttons are stylized in such a way that
;;; the system can manage to display their various states.  To design action,
;;; radio buttons, check boxes, and type-in boxes, you just have to know the
;;; names of the regions involved in the button tracking, and how they function:
;;;
;;; All of these classes have a region named
;;;
;;;    pending-indicator
;;;
;;; The color of this region should be TRANSPARENT in the definition.  When your
;;; mouse is tracking over the button, i.e., when the action that will occur
;;; upon your release is "pending", this region gets changed to the color
;;; FOREGROUND.  When you move the mouse out of this region, the color reverts
;;; to background.
;;;
;;; That's the only region currently of interest for action buttons and type-in
;;; boxes.
;;;
;;; Radio buttons and check boxes have one more important named region:
;;;
;;;    on-indicator
;;;
;;; In the definition, this is colored TRANSPARENT.  When a radio button or
;;; check box is "on", it changes to FOREGROUND.
;;;
;;; It is important to realize that, at present, the actual color of these
;;; buttons determines the state (on or off) of the buttons.  There's no
;;; (redundant) backing store of this information.  (So, if you changed
;;; the colors to blue for "on" and yellow for "off", the code wouldn't
;;; work any more.)
;;;
;;;
;;; A couple of footnotes:
;;;
;;; (1) The question-mark indicator that appears in a check box that is in an
;;; "unknown" state is actually a subblock, not an icon.  That could be
;;; remedied.  We could have a region, unknown-state-indicator, say, that goes
;;; to FOREGROUND when in the unknown state. I just didn't have the patience to
;;; "draw" this.
;;;
;;; (2) Sliders are completely different.  Their arrows are subblocks, and they
;;; have no pending indicator as such.  They're really different....
;;;
;;; MHD, 1/23/96: Changed the drawing/placement of slider needles somewhat:
;;; previously, slider needles were placed with their top edge aligned with the
;;; top edge of the slider; now the bottom edge is placed at the top of the
;;; slider.  This became obviously needed when the new, enlarged, improved
;;; version of the needle was created by Dave Riddell. Note: for existing
;;; sliders, this may not be redrawn/replaced until the slider is reset, or some
;;; dragging is done it.  (MHD 1/23/96)

(def-class (button entity define-predicate)
;  (name-or-names-for-frame nil (type nil))     ; commented out -- allow user
                                                ;  access.  (MHD 7/3/91)
  (label-for-button nil (type whole-string?) vector-slot system save)

  (button-is-being-used-by-system-p nil lookup-slot))

;; Note that buttons will probably be made into objects someday (instead of
;; entities) in order to allow users to define their own classes.

;; The rounding of the action button could use some improvement, especially
;; under magnification!  Consider also abstracting the code that produces it as
;; a function named something like make-rounded-box.actions



;; The current hierarchy is
;;
;;   Button
;;     Generic Action Button
;;       Arrow Button
;;         Left Arrow Button
;;         Right Arrow Button
;;         Up Arrow Button
;;         Down Arrow Button
;;       Default Action Button
;;       Action Button
;;     Non-Action Button
;;       On/off Switch
;;         Radio Button
;;         Check Box
;;       Slider
;;       Type-in Box
;;
;;
;; Consider changing this to
;;
;;   Control
;;     Generic Action Button
;;       .
;;       .
;;       .
;;     On/off Switch
;;       Radio Button
;;       Check Box
;;     Slider
;;     Type-in Box



(def-absent-slot-putter
  initialize-variable-per-current-button-value-on-startup? (button value?)
  button value?)

;; old slot description:
;;   (t (type nil) vector-slot system save) -- in 1.1 (invisible to users)
;;   (t (type yes-or-no) lookup-slot system save) -- in 1.0 patch

;; Perhaps this could be removed! Before or after 2.0 is released. Note that
;; it is not present in any standard KB on AB as of this date. (MHD 6/29/89)


(def-spot button-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type t
    :type-of-frame-represented button)

(def-class-method generate-spot (button mouse-pointer)
  (push-last-spot mouse-pointer (make-button-spot) button))




;;; The name of the slot label-for-button is aliased as label.  Note also that
;;; the name-or-names-for-frame slot is not presently visible or available to
;;; the user.  That slot is, however, sometimes used in buttons managed by the
;;; system in system dialog boxes.

(define-slot-alias label label-for-button button)

;; Note that buttons do sometimes take on "temporary names" (e.g.
;; "button-xxx-12"), but such names are typically visible to the user
;; through the frame-notes slot and are not actually stored in the name-or-
;; names-for-frame slot.




;;; The slot putter for the label-for-button updates the label according to
;;; whole-string?, which may either be a string or nil.  If initializing? is
;;; non-nil, this slot putter calls update-button-label to update the button
;;; label subblock of button.  This returns the value of whole-string?.

(def-slot-putter label-for-button (button whole-string? initializing?)
  (unless initializing?
    (update-button-label
      button (if whole-string? (copy-text-string whole-string?))))
  (setf (label-for-button button) whole-string?))




;;;; Button Labels



;;; A `button label' is a text box used for labelling buttons.

(def-class (button-label text-box)
  (default-text-box-format-name button-label-format))


(def-dialog-box-format button-label-format
  text-cell-font-map (hm18)

  ;; new -- height was wrong in 3.0 & 4.0 Beta Rev. 0, leading to turding on
  ;; update.  Now these should all be right -- they're the same as for type-in
  ;; boxes. (MHD 11/15/94)
  text-cell-line-height 20
  text-cell-baseline-position 15
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 6)
  minimum-word-spacing #.(convert-to-text-width 3)
  maximum-word-spacing #.(convert-to-text-width 14)

  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0

  ;; Labels in KBs created prior to 6/16/89 (2.0) had 12, 9, 12,
  ;;   and 8 (the default for a dialog box format) for the
  ;;   following four items, respectively.  These exactly center
  ;;   the baseline and ascender height with respect to the bottom
  ;;   and top block edges, which looks right.  (MHD 6/16/89)
  ;; Tried 12, 11, 12, 6
  ;; Now trying 9, 6, 6, 2 (MHD 6/29/89)
  text-cell-left-margin 9
  text-cell-top-margin 6
  text-cell-right-margin 6
  text-cell-bottom-margin 2)

;; PROBLEM: Old buttons will still not look right even after bringing formats
;; up-to-date, since the label still needs to be centered (by the label updater),
;; which is only accomplished by reparsing the label.  Consider doing this as a
;; post-loading function. (MHD 6/29/89)

(def-class-method generate-spot (button-label mouse-pointer)
  (generate-spot-for-aggregate
    button-label mouse-pointer))


#+obsolete
(declare-unselectable-class-of-subblock button-label)


(defun make-button-label (text-line text-box-format-name? &optional class? do-not-reformat?)
  (make-free-text-box
    text-line
    (or class? 'button-label)
    text-box-format-name?
    nil nil do-not-reformat?))

;; Consider deabstracting this!






;;; The function `update-button-label' draws a new label for a button.  If
;;; non-nil, text-string? becomes the text of a new button label to be made a
;;; subblock of button, and it becomes incorporated or reclaimed as a result.
;;; If text-string? is nil, this serves to just remove the button label.
;;; Whether or not text-string? is nil, the old button label subblock, if any,
;;; gets deleted.

;;; Generally, but with exceptions given below, a button label is positioned so
;;; that (a) its left edge is aligned with the right edge of the button and (b)
;;; its center is aligned vertically with the center of the button.

;;; An action button label differs in that it gets centered both horizontally
;;; and vertically with respect to the button.  Also note that an action
;;; button's icon is stretched or shrunk (no more than its "normal" size) so
;;; that it surrounds the label, keeping the label centered within the button.

;;; A sliders label differs in that (a) its right edge is aligned with the
;;; line 50 units to the left of the left edge of the slider or 5 units to the
;;; left of the left edge of the minimum value label for the slider, whichever
;;; is less, and (b) its bottom edge is aligned with the bottom edge of the
;;; button.

;;; A type-in box label differs in that its right edge is aligned with the
;;; left edge of the type-in box.

(defun update-button-label (button text-string? &optional text-box-format-name? do-not-reformat?)
  (delete-subblocks-of-class button 'button-label)
  (if text-string?
      (let* ((label (make-button-label text-string? text-box-format-name? nil do-not-reformat?))
             (width-of-label (width-of-block label))
             (height-of-label (height-of-block label))
             (left-edge-for-label                ; to align left edge of label
               (right-edge-of-block button))        ;   with right edge of button
             (top-edge-for-label                ; to center label vertically
               (halfw (-w (+w (top-edge-of-block button)
                              (bottom-edge-of-block button))
                          height-of-label))))
        (frame-class-case button
          (generic-action-button
            (fit-entity-around-text-box                ; button acts as a rounded border
              button label)
            (setq left-edge-for-label                ; to center label horizontally
                  (halfw (-w (+w (left-edge-of-block button)
                                 (right-edge-of-block button))
                             width-of-label)))
            (setq top-edge-for-label                ; to center label vertically
                  (halfw (-w (+w (top-edge-of-block button)
                                 (bottom-edge-of-block button))
                             height-of-label))))
          (slider
            (setq left-edge-for-label                ; to align right edge of label
                  (-w (left-edge-of-block        ;   with the line 50 units to
                        button)                        ;   left of slider
                      width-of-label
                      50))
            (loop for subblock                        ; but also no further to the right
                      being each subblock of button        ;   than 5 units to the left of the
                  when (frame-of-class-p        ;   min value label (if present)
                         subblock 'slider-minimum-value-label)
                    return
                      (setq left-edge-for-label
                            (minw left-edge-for-label
                                  (-w (left-edge-of-block subblock)
                                      (width-of-block label)
                                      5))))
            (setq top-edge-for-label                ; to align bottom of label with
                  (-w (bottom-edge-of-block        ;   bottom of slider
                        button)
                      height-of-label)))
          (type-in-box
            (setq left-edge-for-label                ; to align right edge of label
                  (-w (left-edge-of-block        ;   with left edge of type-in box
                        button)
                      width-of-label))))
        (add-to-block
          label button left-edge-for-label top-edge-for-label t t))))

;; Note: in 2.0 Beta and earlier releases of G2, the default for top-edge-for-
;; label was (top-edge-of-block button). (MHD 6/16/89)


;;; Fit-entity-around-text-box ...

(defun fit-entity-around-text-box (entity text-box)
  (fit-entity-around-text-box-or-bounding-rectangle
    entity text-box nil nil nil nil))

(defun fit-entity-around-text-box-or-bounding-rectangle
    (entity text-box? left-edge? top-edge? right-edge? bottom-edge?)
  (let* ((minimum-width-for-generic-action-button?
           ;; a kludge for the sake of getting a few of our built-in dialogs'
           ;; buttons to be same-sized; needs more generality!
           ;; -- previously, this just tested for a strict instance of
           ;; GENERIC-ACTION-BUTTON, which I think was unintentional.
           ;; (MHD 9/23/99)
           (and (frame-of-class-p entity 'generic-action-button)
                (minimum-width-of-generic-action-button?-function
                  entity)))
         (minimum-width
           (or minimum-width-for-generic-action-button?
               (width-of-icon (icon-description entity))))
         (ideal-right-edge
           (+w (left-edge-of-block entity) minimum-width))
         (minimum-right-edge
           (+w (left-edge-of-block entity)
               (maxw (if text-box?
                         (width-of-block text-box?)
                         0)
                     (if left-edge?
                         (-w right-edge? left-edge?)
                         0))))
         (fix-width?
           (or minimum-width-for-generic-action-button?
               (<w (right-edge-of-block entity) minimum-right-edge)
               (and (>w minimum-right-edge ideal-right-edge)
                    (>w (right-edge-of-block entity) ideal-right-edge))))
         (ideal-bottom-edge
           (+w (top-edge-of-block entity)
               (height-of-icon (icon-description entity))))
         (minimum-bottom-edge
           (+w (top-edge-of-block entity)
               (maxw
                 (if text-box?
                     (height-of-block text-box?)
                     0)
                 (if top-edge?
                     (-w bottom-edge? top-edge?)
                     0))))
         (fix-height?
           (or (<w (bottom-edge-of-block entity) minimum-bottom-edge)
               (and (>w minimum-bottom-edge ideal-bottom-edge)
                    (>w (bottom-edge-of-block entity) ideal-bottom-edge))))
         (fix-text-box?
           (when text-box?
               (not (and (=w (+w (halfw (-w (width-of-block entity)
                                        (width-of-block text-box?)))
                             (left-edge-of-block entity))
                         (left-edge-of-block text-box?))
                     (=w (+w (halfw (-w (height-of-block entity)
                                        (height-of-block text-box?)))
                             (top-edge-of-block entity))
                         (top-edge-of-block text-box?)))))))
    (when (or fix-width? fix-height? fix-text-box?
              (or (<w minimum-width
                      (width-of-block entity))
                  (<w (height-of-icon (icon-description entity))
                      (height-of-block entity))))
      (update-images-of-block entity t t)
      (cond
        (fix-width?
         (cond (minimum-width-for-generic-action-button?
                (change-edges-of-block entity nil nil ideal-right-edge nil)
                (change-icon-attribute
                  entity 'width minimum-width-for-generic-action-button?))
               (t
                (change-edges-of-block entity nil nil minimum-right-edge nil)
                (change-icon-attribute entity 'width (width-of-block entity)))))
        ((<w minimum-width (width-of-block entity))
         (change-icon-attribute entity 'width nil)
         (change-edges-of-block entity nil nil ideal-right-edge nil)))
      (cond
        (fix-height?
         (change-edges-of-block entity nil nil nil minimum-bottom-edge)
         (change-icon-attribute entity 'height (height-of-block entity)))
        ((<w (height-of-icon (icon-description entity))
             (height-of-block entity))
         (change-icon-attribute entity 'height nil)
         (change-edges-of-block entity nil nil nil ideal-bottom-edge)))
      (when text-box?
        (shift-block
          text-box?
          (-w (+w (halfw (-w (width-of-block entity) (width-of-block text-box?)))
                  (left-edge-of-block entity))
              (left-edge-of-block text-box?))
          (-w (+w (halfw (-w (height-of-block entity) (height-of-block text-box?)))
                  (top-edge-of-block entity))
              (top-edge-of-block text-box?))))
      (let ((workspace? (get-workspace-if-any entity)))
        (when workspace?
          ;; note: not necessary in the shrinking case, but ok:
          (enlarge-workspace-for-block-and-subblocks-as-necessary
            entity workspace?))) ; do this before it's drawn
      (update-images-of-block entity nil t))))





;;;; Non Action Buttons



;;; The class `non-action-button' is for buttons without embedded action rules.
;;; These do take action, but always in the form of concluding the value of the
;;; associated-variable-designation? slot.

(def-class (non-action-button button)

; for polling:   (never was or would be saved. removed. -mhd, 9/27/91)
;  (button-update-task? nil vector-slot system)        ; for scheduling updates (ala displays)

  (value-on-activation?                                ; seldom used, hence a lookup slot
    nil (type attribute) lookup-slot system        ; if other buttons have the same
    user-overridable save)                        ;   value, should give a frame note!!

  (associated-variable-designation?
    nil (type constant-variable-designation?)   ; replaces variable-for-check-box,
    vector-slot                                        ;   variable-for-radio-button, and
    system user-overridable save)                ;   variable-for-slider, and
                                                ;   variable-for-type-in-box.
                                                ;   (MHD 6/30/89)


  (associated-frame-for-button?                        ; for use by system; can't have this
    nil (type nil)                                ;   slot be non-nil wo/the next two.
    system save                                        ; Three new slots. (MHD 9/19/89)
    (attribute-export-comment "???"))
  (associated-slot-name-for-button?                ; NOTE: THESE NEED WORK AND WERE NEVER USED!!
    nil (type nil)                                ;   Saving of these would never work!!
    system save                                        ;   These have never had non-default values
    (attribute-export-comment "non-functioning???"))
  (associated-frame-serial-number-for-button?        ;   in running G2 2.0 systems, which I think
    nil (type nil)                                ;   means they could be gotten rid of wo/needing
    system save (attribute-export-comment "internal")))                        ;   obsolete slot putters.  These could also
                                                ;   be made do-not-save at any time (although
                                                ;   it does not really matter now in practice).
                                                ;   See use in set-variable-per-button-if-appropriate.
                                                ;   (MHD 10/3/90)

;; Consider making non-action buttons be frame representations and integrating
;; this more with that facility! (MHD 9/19/89)

;; Consider making the three associated-frame slots be vector slots.
;; (MHD 9/19/89)

(define-slot-alias value-on-activation value-on-activation?
  non-action-button)

(define-slot-alias variable-or-parameter associated-variable-designation?
  non-action-button)

(def-class-method cleanup (non-action-button)
  (funcall-superior-method non-action-button))

;; jh, 9/30/91.  Needed for forward reference in INSTALL.
(defun associated-variable-designation-function? (frame)
  (associated-variable-designation? frame))

;;; The slot putter for associated-variable-designation? ...

;; Should trigger an update to the display when active.  -jra & mhd 9/26/91

(def-slot-putter associated-variable-designation?
    (non-action-button designation? initializing?)
  (unless initializing?
    (add-or-delete-button-frame-note
      non-action-button 'button-missing-variable designation?)
    (install-true-value-update
      'handle-update-to-variable-for-button non-action-button nil
      (if (not initializing?)
          (associated-variable-designation? non-action-button)
          nil)
      designation?))
  (with-new-consistency-analysis-as-appropriate
      (non-action-button)
    (setf (associated-variable-designation? non-action-button) designation?))
  (when g2-has-v5-mode-windows-p
    (frame-class-case non-action-button
      ((radio-button check-box)
       (send-ws-representations-item-virtual-attribute-change
         non-action-button (virtual-attribute 'button-status) nil))
      (slider
        (send-ws-representations-item-virtual-attribute-change
          non-action-button (virtual-attribute 'slider-value) nil))
      (type-in-box
        (send-ws-representations-item-virtual-attribute-change
          non-action-button (virtual-attribute 'type-in-box-variable-or-parameter) nil)
        (send-ws-representations-item-virtual-attribute-change
          non-action-button (virtual-attribute 'type-in-box-value) nil))))
  (update-button non-action-button)
  designation?)

;; This now does nothing at initialization time -- that which is used to do
;; then is now done in the (new) initialize method.  It was (wrongly) playing
;; with the (MHD 7/8/94)



;;; The slot value reclaimer for associated-variable-designation? ...

(def-slot-value-reclaimer associated-variable-designation?
                          (designation? non-action-button)
  (install-true-value-update                      ; actually deinstalling now
    'handle-update-to-variable-for-button
    non-action-button
    nil
    designation?
    nil)
  (reclaim-slot-value designation?))


(def-class-method initialize (non-action-button)
  (funcall-superior-method non-action-button)
  (initialize-non-action-button non-action-button))

(def-class-method initialize-after-reading (non-action-button)
  (funcall-superior-method non-action-button)
  (initialize-non-action-button non-action-button))

(defun initialize-non-action-button (non-action-button)
  (add-or-delete-button-frame-note
    non-action-button 'button-missing-variable
    (associated-variable-designation? non-action-button))
  (when (associated-variable-designation? non-action-button)
    (install-true-value-update
      'handle-update-to-variable-for-button non-action-button nil
      nil
      (associated-variable-designation? non-action-button))))








;;;; Action Buttons



;;; An `action button' is a button which has one subblock: a text box containing
;;; the label for the button.  Clicking on an action button generally causes
;;; some action to take place.  In some cases, holding down on the button may
;;; cause the action to continually take place.

;;; Action buttons have a label that very briefly summarizes its action (in a
;;; short word or two) and a surrounding border.

;;; Basic Operation: When the user presses the mouse down on this button, it is
;;; highlighted and remains so highlighted while the mouse is down and the mouse
;;; is inside of the button.  If the mouse is released inside of the button, the
;;; highlighting is removed, and the action associated with the button should
;;; take place.

;;; These are typically used, for example, as the OK and Cancel buttons in a
;;; dialog box.

;;; Other names: "button", "pushbutton"

;;; A `default action button' is a subclass of an action button.  When a button
;;; can be invoked by typing the Enter key, that button should be a default
;;; action button.  There should never be more than one default action button
;;; presented to the user at a given time.  The default action button will
;;; appear differently by having a bolder border around its label.
;;;
;;; The `initialize method for generic-action-button' and the
;;; `initialize-after-reading method for generic-action-button' both call
;;; `initialize-action-button-action', which does setup work.
;;;
;;; To be OK and usable, an action button must have an "action", either as the
;;; value for its embedded-rule? slot, which holds the "action" rule for
;;; user-defined buttons, or as the value for its button-action? slot, which
;;; holds a function for system-defined buttons.
;;;
;;; The initialization will leave the frame-status-and-notes slot set up as
;;; appropriate.  The frame status should always be INCOMPLETE when there's
;;; no action, and OK (nil) otherwise.
;;;
;;; When there's no action, the frame note
;;; user-menu-choice-or-action-button-missing-action is also present.  Note that
;;; the action can only be present during initialization after creating a clone
;;; or reading in a frame from a KB.  Putters that set the action therefore must
;;; also adjust the frame-status-and-notes appropriately.

(def-class (generic-action-button button)
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (translation-and-text-of-embedded-rule ; the "action" slot for users
    nil (type embedded-rule text) vector-slot system select-changes)

  (embedded-rule? nil vector-slot system save)

  (button-action? nil lookup-slot system)                        ; these three now only used
  (button-action-data? nil lookup-slot system)                        ;   by G2 internally, not for
  (minimum-width-of-generic-action-button? nil lookup-slot system)        ;   user action buttons

  (action-button-priority 2 (type priority) lookup-slot system save)

  (icon-description
    (:funcall-at-load-time create-action-button-description 100 40)))

(def-slot-value-reclaimer button-action? (button-action?)
  button-action?)                        ; unnecessary value

(def-slot-value-reclaimer button-action-data? (button-action-data? action-button)
  (if button-action-data?
      (let ((arglist?
              (frame-class-case action-button
                (arrow-button nil)                ; has t or nil there
                (t (second button-action-data?)))))
        (when arglist?
          (reclaim-button-action-arglist arglist?
                                         (button-action? action-button)))
        (reclaim-slot-value-list button-action-data?))))

(defun reclaim-button-action-arglist (arglist function)
  (case function
    (delete-frame-after-checking-serial-number
     (reclaim-frame-serial-number (second arglist)))
    (allow-continuation-of-class-selection-upon-confirmation
     (reclaim-frame-serial-number (fourth arglist)))
    (update-virtual-attributes-table
     (reclaim-frame-serial-number (first arglist))
     (reclaim-frame-serial-number (third arglist))))
  (reclaim-slot-value-list arglist))


(defun-simple translation-and-text-of-embedded-rule-function
    (generic-action-button)
  (translation-and-text-of-embedded-rule generic-action-button))

(defun action-button-priority-function (button)
  (action-button-priority button))

(defun minimum-width-of-generic-action-button?-function (button)
  (minimum-width-of-generic-action-button? button))

(defun embedded-rule?-function (generic-action-button)
  (embedded-rule? generic-action-button))




;;; Action-button ...
;;;
;;; Action-button is the only subclass of generic-action-button that can be
;;; created by the user.  The system never manages the creation or deletion
;;; of instances of action-button or any of its subclasses; action-button is
;;; the only class in the generic-action-button hierarchy which is also a subclass
;;; of item.  At present, it has no subclasses, but if it did, they would also be
;;; subclasses of item.  This state of affairs evolved somewhat painfully, as
;;; detailed in the historical note below.
;;;
;;; Historical Note.  On 3/12/90, MHD made the following changes to the button
;;; hierarchy, in order, as follows:
;;;
;;;    (1) The name of the class action-button was changed to generic-action-
;;;        button, in this module, ICONS2, and RUN, including all references to
;;;        the symbol ACTION-BUTTON where that specifically meant the class.
;;;
;;;        This meant, in particular, that arrow buttons, icon editor buttons,
;;;        and default action buttons changed to inherit from generic-action-
;;;        button instead of action-button, and also that, temporarily, the
;;;        class action-button ceased to exist.  Also, note that the class of
;;;        button used for system-created "dialog boxes" changed from action-
;;;        button to generic-action-button.
;;;
;;;        As an exception, the reference to action-button in recompile-key-
;;;        slots-of-class-instances was not changed.
;;;
;;;        As an exception, the reference to action-button handle-choice-for-
;;;        workspace-menu was not changed, leaving action-button as the only
;;;        user-instantiable subclass of generic-action-button.
;;;
;;;        As an exception, the references to action-button in QUERIES was
;;;        not changed, leaving action-button as the only "inspectable" subclass
;;;        of generic-action-button.
;;;
;;;        Note, however, that the PURPOSE argument to invoke-old-or-new-rule
;;;        remained ACTION-BUTTON.
;;;
;;;    (2) A new class, ACTION-BUTTON, was created with superior class generic-
;;;        action-button.  This meant that the class action-button was left with
;;;        all of its former attributes, but without any subclasses inheriting
;;;        from it.

(def-class (action-button (item generic-action-button)
                          (foundation-class action-button) define-predicate)
  (action-button-priority 2 (type priority) lookup-slot system
                          user-overridable save))

(def-class-method initialize-after-reading (action-button)
  (funcall-superior-method action-button) ; per convention
  (when t          ; later, use KB flag to limit this fixup to only old KBs!
                  ;   (MHD 5/26/94)
    (loop for subblock being the subblocks of action-button
          when (frame-of-class-p subblock 'button-label)
            do (when t                        ; Some bogus format frames in 3.0; frame
                                        ;    flag for KBs of the vintage with
                                        ;    this problem?  (MHD 5/18/95)
                 (when (not (eq (name-or-names-for-frame action-button)
                                (default-text-box-format-name subblock)))
                   (setf (text-box-format subblock)
                         (get-or-make-format-frame
                           (default-text-box-format-name subblock)))))
               (change-icon-attribute action-button 'x-magnification nil)
               (fit-entity-around-text-box action-button subblock)
               (return))))

;;; The user-menu-choice methods for `note-runs-while-inactive-change' and
;;; `note-may-refer-to-inactive-items-change' should call the next method, then
;;; it should propagate the settings into the embedded rule.

(def-class-method note-runs-while-inactive-change (action-button)
  (funcall-superior-method action-button)
  (let ((rule? (embedded-rule? action-button)))
    (when rule?
      (change-slot-value
        rule? 'frame-flags
        (if (runs-while-inactive-p action-button)
            (logiorf (frame-flags rule?) runs-while-inactive-flag)
            (logandc2 (frame-flags rule?) runs-while-inactive-flag))))))

(def-class-method note-may-refer-to-inactive-items-change (action-button)
  (funcall-superior-method action-button)
  (let ((rule? (embedded-rule? action-button)))
    (when rule?
      (change-slot-value
        rule? 'frame-flags
        (if (may-refer-to-inactive-items-p action-button)
            (logiorf (frame-flags rule?) may-refer-to-inactive-items-flag)
            (logandc2 (frame-flags rule?) may-refer-to-inactive-items-flag))))))




;;; The `manually-enable' and `manually-disable' methods for action-buttons
;;; propagate the setting of the enabled frame flag down into the embedded rule.
;;; It used to be that all enable/disable did was toggle whether or not
;;; something was activated.  However, for running-while-inactive rules, it now
;;; also stops their execution, regardless of activation state.  These methods
;;; propagate that value down into the embedded rule.

(def-class-method manually-enable (action-button)
  (funcall-superior-method action-button)
  (let ((embedded-rule? (embedded-rule? action-button)))
    (when embedded-rule?
      (funcall-method 'manually-enable embedded-rule?))))

(def-class-method manually-disable (action-button)
  (funcall-superior-method action-button)
  (let ((embedded-rule? (embedded-rule? action-button)))
    (when embedded-rule?
      (funcall-method 'manually-disable embedded-rule?))))



(defun background-color-of-generic-action-button
    (generic-action-button)
  (get-color-of-icon-region
    generic-action-button 'pending-indicator))




;;; The `draw method for generic-action-button' is a customized draw method
;;; for drawing action buttons.
;;;
;;; It is needed to assure that the text box containing the label for the action
;;; button is drawn against the background color of the action button, which
;;; guards against a "false color" problem in the case where xor drawing is in
;;; effect.  The general method for drawing entities assumes that either the
;;; name boxes or other subblocks being drawn do not overlap the icon, or that
;;; the user is not concerned with the false color problem, and so doesn't deal
;;; with it.  Action buttons, however, are assumed to have text in their middle,
;;; over a uniform background color, or metacolor, and typically framed by a
;;; bordering design built into the icon description.
;;;
;;; This makes the following assumptions:
;;;
;;;   (1) the background color or metacolor is the color or metacolor for
;;;   the region named PENDING-INDICATOR;
;;;
;;;   (2) the subblocks, if any, are all to be drawn against this color;
;;;
;;;   (3) there are never connections to draw

(def-class-method draw (generic-action-button)
  (draw-icon-for-entity generic-action-button)
;  (draw-subblocks generic-action-button)
  )

;; Note: the code which was here to bind the background color for button-label
;; subblocks has been moved to `compute-background-color-value-for-block',
;; which is used by draw-or-change-color-in-text-cell-for-block.  This was
;; necessary in order to bind the bg color correctly for both complete redraws
;; (the path here), and for incremental updates. -fmw, 6/17/94

;; Note that this might not be needed in a world in which XOR drawing could
;; never take place.  Note that it might be reasonable to consider drawing the
;; label directly in the draw method, and not even holding a text box subblock,
;; although that would require other work in other places.

;; This is being done for 4.0, where we are considering a new icon description
;; for action buttons that has light-gray as the default PENDING-INDICATOR
;; color.  In previous releases, this was the metacolor TRANSPARENT, which made
;; the overlapping of the label on top of the icon always "work".  (MHD 5/27/94)

;; Note A: Unfortunately, assumption (2) is false: attribute displays associated with
;;  an action button are subblocks which are drawn against the workspace
;;  background. So we change the bg color only for button-label subblocks.
;;  -fmw, 6/13/94




(def-class (default-action-button generic-action-button))

;; Do the icon description!!




(define-slot-alias action-priority action-button-priority
  generic-action-button)

(define-slot-alias action translation-and-text-of-embedded-rule
  generic-action-button)





(def-class-method activate-subclass-of-entity (generic-action-button)
  (let ((embedded-rule? (embedded-rule? generic-action-button)))
    (if embedded-rule?
        (funcall-method 'activate-if-possible-and-propagate embedded-rule?))))

(def-class-method deactivate-subclass-of-entity (generic-action-button)
  (let ((embedded-rule? (embedded-rule? generic-action-button)))
    (if embedded-rule?
        (funcall-method 'deactivate-and-propagate embedded-rule? nil))))






;;; Small-editor-subcommand-button ... here to support text editing, used in EDIT2.

(def-class (editor-subcommand-button generic-action-button)
  (icon-description
    (:funcall-at-load-time create-action-button-description 46 22))
  (editor-subcommand-name nil vector-slot system) ; a symbol
  (editor-subcommand-disabled-p nil vector-slot system)
  (subcommand-button-radio-button-status nil vector-slot system))

(defun-simple editor-subcommand-name-function (generic-action-button)
  (editor-subcommand-name generic-action-button))

(def-class-method draw (editor-subcommand-button)
  (unless (editor-subcommand-disabled-p editor-subcommand-button)
    (funcall-superior-method editor-subcommand-button)))

(defun-void enable-or-disable-editor-subcommand-button
    (editor-subcommand-button disable-p)
  (when (if disable-p
            (not (editor-subcommand-disabled-p editor-subcommand-button))
            (editor-subcommand-disabled-p editor-subcommand-button))
    ;; Because button labels are subblocks, and our enabled-p flag doesn't
    ;; control subblock drawing (because the draw method is no longer recursive
    ;; on subblocks), we have to actually remove/add the label to disable/enable
    ;; it.
    (update-button-label
      editor-subcommand-button
      (if disable-p
          nil
          (copy-if-text-string (label-for-button editor-subcommand-button)))
      'editor-subcommand-label-format)
    (erase-images-of-block editor-subcommand-button t)
    (setf (editor-subcommand-disabled-p editor-subcommand-button) disable-p)
    (draw-images-of-block editor-subcommand-button t)))


(defparameter highlight-color-pattern-for-enabled-pending-subcommands
  '((pending-indicator . dark-gray)))
(defparameter highlight-color-pattern-for-enabled-non-pending-subcommands
  'default)
(defparameter highlight-color-pattern-for-non-pending-off-radio-button-subcommands
  '((pending-indicator . light-gray)))
(defparameter highlight-color-pattern-for-pending-off-radio-button-subcommands
  highlight-color-pattern-for-enabled-pending-subcommands)
(defparameter highlight-color-pattern-for-non-pending-on-radio-button-subcommands
  '((pending-indicator . smoke)))
(defparameter highlight-color-pattern-for-pending-on-radio-button-subcommands
  highlight-color-pattern-for-enabled-pending-subcommands)

(defun-void indicate-editor-subcommand-button-pending-state
    (editor-subcommand-button pending? just-remove-indicator?)
  (let* ((color-pattern
           (case (subcommand-button-radio-button-status editor-subcommand-button)
             ((nil)
              (if pending?
                  highlight-color-pattern-for-enabled-pending-subcommands
                  highlight-color-pattern-for-enabled-non-pending-subcommands))
             (off
              (if pending?
                  highlight-color-pattern-for-pending-off-radio-button-subcommands
                  highlight-color-pattern-for-non-pending-off-radio-button-subcommands))
             (on
              (if
                pending?
                highlight-color-pattern-for-pending-on-radio-button-subcommands
                highlight-color-pattern-for-non-pending-on-radio-button-subcommands
                )))))
    (change-color-pattern-of-icon
      editor-subcommand-button nil
      (if (or (eq color-pattern 'default) just-remove-indicator?)
          (default-color-pattern-of-entity editor-subcommand-button)
          color-pattern))))


(def-dialog-box-format editor-subcommand-label-format
  text-cell-font-map (hm14)
  text-cell-line-quadding? nil
  text-cell-line-height 14
  text-cell-baseline-position 12
  text-cell-line-spacing 1
  default-word-spacing #.(convert-to-text-width 4)
  minimum-word-spacing #.(convert-to-text-width 2)
  maximum-word-spacing #.(convert-to-text-width 7)

  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0

  text-cell-left-margin 4
  text-cell-top-margin 7
  text-cell-right-margin 4
  text-cell-bottom-margin 6)

(defun get-overall-minimum-width-for-subcommand-menu-column (strings)
  (let* ((text-box-format-name 'editor-subcommand-label-format)
         (text-box-format (get-or-make-format-frame text-box-format-name))
         (quantized-sizes '(80  160 360)))
    (loop for string in strings
          as line-width
             = (+w (compute-width-of-text-line
                     string nil nil
                     (text-cell-font-map text-box-format)
                     (default-word-spacing text-box-format))
                   6)                        ; extra for button border/shadow junk
          as minimum-width
             = (loop for size in quantized-sizes
                     when (>=w size line-width)
                       return size
                     finally
                       (return line-width))
          maximize minimum-width)))


(defun make-editor-subcommand-button
    (label-text-string editor-subcommand-name &optional minimum-width?)
  (let* ((text-box-format-name 'editor-subcommand-label-format)
         (button
          (make-button
            'editor-subcommand-button
            label-text-string nil t
            (maxw (or minimum-width? 80) 80)
            text-box-format-name)))
    (setf (editor-subcommand-name button) editor-subcommand-name)
    ;; for compatibility, start off disabled:
    (enable-or-disable-editor-subcommand-button button t)
    button))




;;;; Embedded Rules (for Action Buttons and User Menu Choices)

(def-slot-putter translation-and-text-of-embedded-rule
                 (generic-action-button action-text initializing?)
  ;; When loading a KB saved before 3.0, clear its compile and parse, note that
  ;; it is pre-3.0, and make it incomplete.  -jra 6/5/91  -- UPDATE: the
  ;; changes to the notes slot have to be done in the initialize method,
  ;; i.e., after the frame is fully formed. (MHD 7/12/94)
  (when (and initializing?
             (not (compilations-up-to-date-p generic-action-button))
             loading-kb-p)
    (reclaim-slot-value (car action-text))
    (setf (car action-text) no-value))
  (setf (translation-and-text-of-embedded-rule generic-action-button)
        action-text))


(defun check-for-and-fix-up-cloned-embedded-rule (embedded-rule)
  (when (not (eq (car (box-translation-and-text embedded-rule)) no-value))

    ;; This was created by cloning.  At this point, the newly created rule in
    ;; the slot embedded-rule?  (or embedded-rule-in-user-menu-choice?) contains
    ;; a car which is not (no-value). ...

    (assert-consistency-analysis-if-allowed embedded-rule)

    ;; Activate it if necessary
    (if (active-p (parent-frame embedded-rule))
        (funcall-method 'activate-if-possible-and-propagate embedded-rule))))


(defun initialize-action-button-action (generic-action-button)
  (let ((embedded-rule? (embedded-rule? generic-action-button)))
    (when embedded-rule?
      (set-parent-information
        embedded-rule? generic-action-button
        'translation-and-text-of-embedded-rule nil)
      (unless reading-kb-p
        (add-as-inferior-block
          embedded-rule?
          generic-action-button))
      (when (priority-p (action-button-priority generic-action-button))
        (change-slot-value
          embedded-rule?
          'rule-priority
          (action-button-priority generic-action-button)))
      (propagate-runnable-item-options-to-embedded-rule
        embedded-rule? generic-action-button)
      (check-for-and-fix-up-cloned-embedded-rule
        embedded-rule?))

    ;; part of loading a KB saved before 3.0 -- make it incomplete -- see also the
    ;; putter for translation-and-text-of-embedded-rule (MHD 7/12/94)
    (when (and (not (compilations-up-to-date-p generic-action-button))
               (translation-and-text-of-embedded-rule generic-action-button)
               loading-kb-p)
      (add-or-delete-button-frame-note
        generic-action-button
        'button-or-user-menu-choice-not-compiled-up-to-date
        nil)
      (update-frame-status generic-action-button 'incomplete t)
      (note-frame-with-compilation-removed generic-action-button))
    (add-or-delete-button-frame-note
      generic-action-button
      'user-menu-choice-or-action-button-missing-action
      embedded-rule?)))


(def-class-method initialize (generic-action-button)
  (funcall-superior-method generic-action-button)
  (initialize-action-button-action generic-action-button))

(def-class-method initialize-after-reading (generic-action-button)
  (funcall-superior-method generic-action-button)
  (initialize-action-button-action generic-action-button))

(def-slot-putter embedded-rule? (generic-action-button embedded-rule? initializing?)
  (prog1
      (setf (embedded-rule? generic-action-button) embedded-rule?)
    (unless initializing?
      (initialize-action-button-action generic-action-button))))

(def-slot-putter action-button-priority (generic-action-button value initializing?)
  (prog1 (setf (action-button-priority generic-action-button) value)
    (unless initializing?
      (initialize-action-button-action generic-action-button))))

(def-slot-value-reclaimer embedded-rule? (embedded-rule?)
  (if embedded-rule?
      (delete-frame embedded-rule?)))



;;; An `embedded rule' is either
;;;
;;;   (1) a rule with a list of actions;
;;;   (2) an unconditional rule;
;;;   (3) a when rule; or
;;;   (4) a rule with FOR clauses followed by WHEN or UNCONDITIONALLY
;;;
;;; In case (1), it is necessary for the embedded rule compiler to apply the
;;; fix-action-list transform which was not applied initially.

;;; A `rule embedder' is a frame which has or can have an embedded rule in one
;;; of its slots.

;;; At present, only action buttons and user menu choices (see MENUS) are rule
;;; embedders.  An action button keeps its embedded rule in the slot named
;;; embedded-rule?.  A user menu choice keeps its embedded rule in the slot
;;; named embedded-rule-in-user-menu-choice?.  Unfortunately, the compiler for
;;; embedded-rule must apply special knowledge about these two cases as well as
;;; various details about normal rule compiler; thus, to add other cases, it
;;; is necessary to modify its code.

;;; `rule-is-embedded-p' is true if a rule is embedded.  This has been split out
;;; from the definition of embedded-rule-p so it can be called as an efficiency
;;; hack in collect-instances-of-class-for-role-service.

(defun-simple rule-is-embedded-p (rule)
  (parent-frame rule))                        ; it is assumed now that only
                                        ;   embedded rules have non-nil
                                        ;   here. (MHD 6/26/90)

;;; `Embedded-rule-p' is true if frame is a rule that is embedded.

(defun-simple embedded-rule-p (frame)
  (and (frame-of-class-p frame 'rule)
       (rule-is-embedded-p frame)))

;; This should maybe be a macro, but it is a function at least for now because
;; it has to be forward-referenced from QUERIES.  (MHD 6/26/90)



(def-slot-value-compiler embedded-rule (parse-result rule-embedder slot-name)
  (let ((modification-while-executing?
          (modification-while-executing? rule-embedder slot-name)))
    (when modification-while-executing?
      (return-from compile-embedded-rule-for-slot
        (values
          bad-phrase
          modification-while-executing?))))
  (let (value error?)
    (with-updates-to-representations-supressed (rule-embedder 'frame-status-and-notes)
      (add-or-delete-button-frame-note
        rule-embedder
        'button-or-user-menu-choice-not-compiled-up-to-date
        t)
      (multiple-value-setq (value error?)
        (let* ((class-of-rule-embedder (class rule-embedder))
               (user-menu-choice-case?
                 (subclassp class-of-rule-embedder 'user-menu-choice))
               (slot-name-for-embedded-rule
                  (get-slot-name-for-embedded-rule class-of-rule-embedder))
               (rule
                 (let ((embedded-rule?
                         (get-slot-value
                           rule-embedder slot-name-for-embedded-rule)))
                   (cond
                     (embedded-rule?
                      (let ((do-not-note-permanent-changes-p t))
                        (delete-frame embedded-rule?))
                          (set-slot-value rule-embedder slot-name-for-embedded-rule nil)))
                   (let ((new-rule (make-frame 'rule)))
                     (setf (text-box-format new-rule)        ; required for all boxes --
                                        ;   but wasn't done till now!
                           (get-or-make-format-frame        ;   So fix needed to be put
                                        ;   into FILES. (MHD 10/17/89)
                             (default-text-box-format-name new-rule)))
                     (clear-invocable-via-backward-chaining new-rule)
                     (clear-invocable-via-forward-chaining new-rule)
                     (change-slot-value
                       rule-embedder slot-name-for-embedded-rule new-rule)
                     new-rule))))
          (when user-menu-choice-case?
            ;; Make this rule invokable via item as a focal class.
            (change-slot-value rule 'focal-classes (slot-value-list 'item)))
          (put-box-translation-and-text
            rule
            (slot-value-cons
              (copy-for-slot-value
                (compile-rule-for-slot
                  (let ((translation
                          (if (memq (car parse-result) '(when for unconditionally))
                              parse-result
                              (fix-action-list (phrase-list 'when 'true parse-result)))))
                    (if user-menu-choice-case?
                        (phrase-list
                          'for (phrase-list 'any 'item)
                          translation)
                        translation))
                  rule nil))
              (slot-value-list
                (tformat-text-string                ; e.g. "See action-button."
                  "See ~(~A~)." class-of-rule-embedder)))
            nil)

;    (update-frame-notes-for-rule-superior rule rule-embedder)
          (if (active-p rule-embedder)
              (funcall-method 'activate-if-possible-and-propagate rule))
          T)))
    (values value error?)))                        ; a real translation not needed

;; Consider using "superior-frame" where "rule-embedder" is now used above!

;; Document user-menu-choice-case!!

;; This is left in because it is used in the compiler above. It assumes that
;; the embedding slot is a function of the class of the embedded frame.
;; Please note list-of-mmbedding-slots in frames4. ML 11/2/89.

(defun get-slot-name-for-embedded-rule (class-of-rule-embedder)
  (class-case class-of-rule-embedder
    (generic-action-button
      'embedded-rule?)
    (user-menu-choice                                ; abstract better!!
      'embedded-rule-in-user-menu-choice?)
    ;; no other cases handled at present
    ))

;(defun update-frame-notes-for-rule-superior
;       (rule superior-frame)
;  (if (frame-status-and-notes rule)
;      (add-frame-note
;        'embedded-rule-has-frame-notes superior-frame
;        (get-slot-name-for-embedded-rule (class superior-frame)) nil nil)
;      (delete-frame-note-if-any
;        'embedded-rule-has-frame-notes superior-frame)))













;;;; On/off Switches





;;; A `on/off switch' has two states: on and off.

;;; Basic Operation: When the user presses the mouse down on an on/off switch, its
;;; `pending indicator' region illuminated to show that a change in its state is
;;; pending.  The pending indicator remains illuminated while the mouse is
;;; down and the mouse is inside of the button.  If the mouse is released inside
;;; of the button, the pending indicator is made invisible, the on/off switch is turned
;;; on.  When a radio button is on, its `on-indicator' region, is illuminated.

;;; At present, an on/off switch is an abstract class; it should not normally be
;;; instantiated.

(def-class (on/off-switch non-action-button))         ; abstract class

;; (def-substitute-for-old-class switch on/off-switch)        ; remove after 2.0 Alpha Release
;; This was put in in development, but was found to clash with KBs being
;; developed.  Unfortunately, the def-substitute itself would send user defined classes
;; into limbo.  Commented out after 2.0 Alpha, 9/21/89. (MHD 9/21/89)



;;; Change-on/off-switch ... Mode may be one of the symbols: TOGGLE, to toggle
;;; between "on" and "off", T to indicate "on", NIL to indicate "off",
;;; or the value of the special variable no-value to indicate an "undefined"
;;; reading, represented by making a question-mark-box its subblock.

;;; As an exception, if the mode is toggle but the switch was in the "undefined"
;;; state (showing a "?"), the mode is always made nil.  That is, toggling while
;;; in the undefined state can only go to the off state.

;; Changing the state of the button updates all of its images.

(defun change-on/off-switch (on/off-switch mode)
  (let* ((color-of-checked-region
           (get-color-of-icon-region on/off-switch 'on-indicator))
         (question-mark-box?
           (loop for subblock being each subblock of on/off-switch
                 if (frame-of-class-p subblock 'question-mark-box)
                   return subblock)))
    (cond
      ((and question-mark-box?
            (not (eq mode no-value)))
       (delete-frame question-mark-box?)
       (if (eq mode 'toggle)
           (setq mode nil))))                        ; changes arg!
    (case mode
      ((t)
       (if (not (eq color-of-checked-region 'foreground))
           (change-color-pattern-of-icon
             on/off-switch nil '((on-indicator . foreground)))))
      ((nil)
       (if (not (eq color-of-checked-region 'transparent))
           (change-color-pattern-of-icon
             on/off-switch nil '((on-indicator . transparent)))))
      ((toggle)
       (case color-of-checked-region
         ((foreground)
          (change-color-pattern-of-icon
            on/off-switch nil '((on-indicator . transparent))))
         (otherwise
          (change-color-pattern-of-icon
            on/off-switch nil '((on-indicator .  foreground))))))
      (otherwise                                        ; => (eq mode no-value)
       ;; use a region? or something else?
       (change-color-pattern-of-icon
         on/off-switch nil '((on-indicator . transparent)))
       (if (null question-mark-box?)
           (let ((question-mark-box (make-question-mark-box)))
             (add-to-block
               question-mark-box on/off-switch
               (+w (left-edge-of-block on/off-switch)
                   (-w (halfw (width-of-block on/off-switch))
                       (halfw (width-of-block question-mark-box))))
               (+w (top-edge-of-block on/off-switch)
                   (-w (halfw (height-of-block on/off-switch))
                       (halfw (height-of-block question-mark-box))))
               t t)))))))

;; Consider returning true if the check box was left in the on state and nil
;; otherwise.

;; Note that in the case statement above, Lucid 4 gave a warning when T was used
;; as a value (it was enclosed in parens) and it was used as the default tag
;; (the T was not enclosed in parens).  This is a Lucid bug, which is worked
;; around by using otherwise in the case statements above.  -jra 5/3/91






;;; Get-on/off-switch-status ... returns either T, NIL, or no-value.

;; Changing the state of the button updates all of its images.

(defun get-on/off-switch-status (on/off-switch)
  (let* ((color-of-checked-region
           (get-color-of-icon-region on/off-switch 'on-indicator))
         (question-mark-box?
           (loop for subblock being each subblock of on/off-switch
                 if (frame-of-class-p subblock 'question-mark-box)
                   return subblock)))
    (cond
      (question-mark-box? no-value)
      ((eq color-of-checked-region 'foreground)
       t)
      (t
       ;; (eq color-of-checked-region 'foreground)
       nil))))


(defun on/off-switch-on-p (on/off-switch)
  (eq (get-on/off-switch-status on/off-switch) 't))

(defun on/off-switch-off-p (on/off-switch)
  (eq (get-on/off-switch-status on/off-switch) 'nil))

(defun on/off-switch-undefined-p (on/off-switch)
  (eq (get-on/off-switch-status on/off-switch) no-value))







;;;; Check Boxes




;;; A `check box' may have one subblock which is its label.  The label is a
;;; text box of class button-label.  A check box has two main states:  checked and
;;; unchecked.  Clicking on a check box toggles between these two states.

;;; A group of check boxes will often appear in a `check box cluster'.  In this
;;; case, even though all of the boxes are independent of each other, they are
;;; related by their meaning to the application and appear together
;;; geographically.  Often, the effect of changing them may all be keyed off of
;;; a common OK button in a dialog box.

;;; Basic Operation: When the user presses the mouse down on this button, a
;;; `pending box' is added to the box to show that a change in its state is
;;; pending.  The pending box remains there while the mouse is down and the
;;; mouse is inside of the button.  If the mouse is released inside of the
;;; button, the pending box is removed, a `check' (which actually looks like
;;; an "X") is placed in the check box, and the box's state is toggled.  Clicking
;;; again makes it go back to being unchecked.

;;; Other names: "switch", "on/off switch", "toggle switch"

(def-class (check-box (item on/off-switch) (foundation-class check-box))
  (on-value-for-check-box nil (type attribute) vector-slot system
                          user-overridable save)
  (off-value-for-check-box nil (type attribute) vector-slot system
                           user-overridable save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      20 20
      ((polychrome
         (on-indicator . transparent)
         (pending-indicator . transparent)
         (foreground . foreground))

       on-indicator                                ; transparent/foreground
;       (lines (3 4) (15 16))
;       (lines (15 4) (3 16))
;       (lines (4 4) (16 16))
;       (lines (16 4) (4 16))
;       (lines (5 4) (17 16))
;       (lines (17 4) (5 16))

       ;; Converting system icons to polygons/solid-rectangles JED 8/11/93

        #.(create-filled-polygon-icon-description-element
            '((3 4) (5 4) (10 9) (15 4) (17 4) (11 10) (17 16)
              (15 16) (10 11) (5 16) (3 16) (9 10)))

       pending-indicator                        ; transparent/foreground
;       (outline (2 2) (18 2) (18 18) (2 18))        ; note: slightly overlaps check
;       (outline (3 3) (17 3) (17 17) (3 17))
         (solid-rectangle (2 2) (18 3))
         (solid-rectangle (2 3) (3 17))
         (solid-rectangle (17 3) (18 17))
         (solid-rectangle (2 17) (18 18))

       foreground                                ; the box itself: always foreground
;       (outline (0 0) (20 0) (20 20) (0 20))
;       (outline (1 1) (19 1) (19 19) (1 19))
        (solid-rectangle (0 0) (20 1))
        (solid-rectangle (0 1) (1 19))
        (solid-rectangle (19 1) (20 19))
        (solid-rectangle (0 19) (20 20))
       ))))

;; Consider having an off-indicator region and having another appearance for
;; neither one -- rather than reimplementing the "?" idea!

;; Note that, for now, turning check boxes or radio buttons off means turning
;; the on-indicator region "off" (i.e. making it transparent).

;; Use filled polygons for instead of double and triple lines; or have lines
;; of parameterized thickness!  When you scale this, the double and triple
;; thick lines spread out, which looks wrong! (MHD 8/7/89)



(def-absent-slot-putter variable-for-check-box (check-box value)
  (put-associated-variable-designation?                ; defer to master slot putter
    check-box value t))

;; old slot description:
;;    (variable-for-check-box
;;       nil (type constant-variable-designation?) vector-slot system save)

;; old "slot alias":
;;    (def-slot-alias variable-for-check-box variable check-box)

;; old slot putter:
;;    (def-slot-putter variable-for-check-box (check-box designation? initializing?)
;;      (add-or-delete-button-frame-note
;;        check-box 'button-missing-variable designation?)
;;      (install-true-value-update
;;        'handle-update-to-variable-for-button check-box nil
;;        (if (not initializing?)
;;            (variable-for-check-box check-box)
;;            nil)
;;        designation?)
;;      (setf (variable-for-check-box check-box) designation?))

;; old reclaimer:
;;     (def-slot-value-reclaimer variable-for-check-box (designation? check-box)
;;       (install-true-value-update                ; Actually deinstalling now.
;;         'handle-update-to-variable-for-button
;;         check-box
;;         nil
;;         designation?
;;         nil)
;;       (reclaim-slot-value designation?))




(define-slot-alias on-value on-value-for-check-box check-box)
(define-slot-alias off-value off-value-for-check-box check-box)



(def-slot-putter on-value-for-check-box (check-box attribute initializing?)
  (prog1 (setf (on-value-for-check-box check-box) attribute)
         (unless initializing?
           (add-or-delete-button-frame-note
             check-box 'button-missing-on-value attribute)
           (when g2-has-v5-mode-windows-p
             (send-ws-representations-item-virtual-attribute-change
               check-box (virtual-attribute 'button-status) nil))
           (update-button check-box))))



(def-slot-putter off-value-for-check-box (check-box attribute initializing?)
  (prog1 (setf (off-value-for-check-box check-box) attribute)
         (unless initializing?
           (add-or-delete-button-frame-note
             check-box 'button-missing-off-value attribute)
           (when g2-has-v5-mode-windows-p
             (send-ws-representations-item-virtual-attribute-change
               check-box (virtual-attribute 'button-status) nil))
           (update-button check-box))))


(def-class-method initialize (check-box)
  (funcall-superior-method check-box)
  (add-or-delete-button-frame-note
    check-box 'button-missing-on-value
    (on-value-for-check-box check-box))
  (add-or-delete-button-frame-note
    check-box 'button-missing-off-value
    (off-value-for-check-box check-box))
  (update-button check-box))




;; old pending indicator :
;;
;;       (def-class (check-box-pending-box entity system-internal)
;;         (icon-description
;;           (:funcall-at-load-time
;;             create-icon-description
;;             20 20
;;             ((outline (2 2) (18 2) (18 18) (2 18))
;;              (outline (3 3) (17 3) (17 17) (3 17))))))

(def-class (substitute-for-check-box-pending-box entity))
(def-substitute-for-old-class
  check-box-pending-box substitute-for-check-box-pending-box)

(def-class-method
    fix-frame-with-substitute-class (substitute-for-check-box-pending-box)
  ;; Should never really be here, since it should not have been saved
  ;;   out in this state -- unlikely that any KBs ever were.
  (delete-frame substitute-for-check-box-pending-box))

;; (MHD 8/7/89)


;; old checked indicator:
;;
;;       (def-class (check-box-check entity system-internal)
;;         (icon-description
;;           (:funcall-at-load-time
;;             create-icon-description
;;             20 20
;;             ((lines (3 4) (15 16))
;;              (lines (15 4) (3 16))
;;              (lines (4 4) (16 16))
;;              (lines (16 4) (4 16))
;;              (lines (5 4) (17 16))
;;              (lines (17 4) (5 16))))))

(def-class (substitute-for-check-box-check entity))

(def-substitute-for-old-class
  check-box-check substitute-for-check-box-check)

(def-class-method
    fix-frame-with-substitute-class (substitute-for-check-box-check)
  ;; presence implies it was checked
  (change-on/off-switch                                ; ok? (Maybe just leave out, since
    (superblock? substitute-for-check-box-check) t)        ; we're not running!) (MHD)
  (delete-frame substitute-for-check-box-check))

;; (MHD 8/7/89)



(def-class (question-mark-box text-box)
  (default-text-box-format-name question-mark-box-format))

(def-text-box-format question-mark-box-format
  text-cell-font-map (hm14)

  text-cell-paragraph-indentation 0

  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 0
  text-cell-bottom-margin 0

  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)


(defun make-question-mark-box ()
  (make-free-text-box
    (copy-constant-wide-string #w"?") 'question-mark-box))

;; Get rid of this, too!!

(def-class-method generate-spot (question-mark-box mouse-pointer)
  (generate-spot-for-aggregate
    question-mark-box mouse-pointer))


(def-class-method initialize-after-reading (check-box)
  (funcall-superior-method check-box)
  (change-on/off-switch check-box no-value))












;;;; Radio Buttons




;;; A `radio button' ... is a type of on/off-switch ...

;;; A `radio button cluster' is the set of radio buttons which have the
;;; same associated variable.  All radio buttons in such a cluster
;;; should have unique value-for-radio-button slot values, and each such
;;; value should conceptually be mutually exclusive.
;;; Clicking on a radio turns it on and all of the others in the cluster off.

;;; When a radio button is turned in a cluster is turned on, the radio button
;;; (or buttons) that were previously on are turned off.

;;; Other names: "multiple, mutually exclusive choice buttons", "car radio
;;; buttons"

(def-class (radio-button (item on/off-switch) (foundation-class radio-button))
  (value-for-radio-button nil (type attribute) vector-slot system
                          user-overridable save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      20 20
      ((polychrome
         (on-indicator . transparent)
         (pending-indicator . transparent)
         (foreground . foreground))

       pending-indicator
       (filled-circle (10 2) (18 10) (10 18))
       transparent                                ; the transparent region is
       (filled-circle (10 7) (13 10) (10 13))        ;   really a part the pending-
                                                ;   indicator region; it hollows
                                                ;   out the filled circle, making
                                                ;   into a ring
       on-indicator
       (filled-circle (10 7) (13 10) (10 13))        ; note that this has to come after
                                                ;   the pending indicator the up the
                                                ;   transparent part of the ring
       foreground
       (circle (10 0) (20 10) (10 20))
       (circle (10 1) (19 10) (10 19))))))


(def-absent-slot-putter variable-for-radio-button (radio-button value)
  (put-associated-variable-designation?                ; defer to master slot putter
    radio-button value t))

;; old slot description:
;;  (variable-for-radio-button
;;    nil (type constant-variable-designation?) vector-slot system save)

;; old "slot alias":
;;  (def-slot-alias variable-for-radio-button variable radio-button)

;; old slot putter:
;;  (def-slot-putter variable-for-radio-button
;;                   (radio-button designation? initializing?)
;;    (add-or-delete-button-frame-note
;;      radio-button 'button-missing-variable designation?)
;;    (install-true-value-update
;;      'handle-update-to-variable-for-button radio-button nil
;;      (if (not initializing?)
;;          (variable-for-radio-button radio-button)
;;          nil)
;;      designation?)
;;    (setf (variable-for-radio-button radio-button) designation?))

;; old reclaimer:
;;  (def-slot-value-reclaimer variable-for-radio-button (designation? radio-button)
;;    (install-true-value-update                        ; Actually deinstalling now.
;;      'handle-update-to-variable-for-button
;;      radio-button
;;      nil
;;      designation?
;;      nil)
;;    (reclaim-slot-value designation?))



(define-slot-alias on-value value-for-radio-button radio-button)

;; Change the alias above from VALUE to ON-VALUE today (10/30/91 in the 3.0
;; pre-alpha version) because VALUE is a reserved word (i.e., used in "the value
;; of <variable>" expressions), so you were prevented from accessing the slot
;; from actions.  As it turns out, ON-VALUE might be preferable anyway, since it
;; is consistent with the ON-VALUE slot of a check-box. (MHD 10/30/91)





(def-slot-putter value-for-radio-button (radio-button attribute initializing?)
  (prog1 (setf (value-for-radio-button radio-button) attribute)
         (unless initializing?
           (add-or-delete-button-frame-note
             radio-button 'button-missing-value attribute)
           (when g2-has-v5-mode-windows-p
             (send-ws-representations-item-virtual-attribute-change
               radio-button (virtual-attribute 'button-status) nil))
           (update-button radio-button))))

(def-class-method initialize (radio-button)
  (funcall-superior-method radio-button)
  (add-or-delete-button-frame-note
    radio-button 'button-missing-value
    (value-for-radio-button radio-button))
  (update-button radio-button))



;; old pending indicator:
;;
;; (def-class (radio-button-pending-ring entity system-internal)
;;   (icon-description
;;     (:funcall-at-load-time
;;       create-icon-description
;;       20 20
;;       ((filled-circle (10 2) (18 10) (10 18))
;;        transparent
;;        (filled-circle (10 7) (13 10) (10 13)))
;;       ;; before 8/4/89:
;;;       ((circle (10 2) (18 10) (10 18))
;;;        (circle (10 3) (17 10) (10 17)))
;;       )))


(def-class (substitute-for-radio-button-pending-ring entity))

(def-substitute-for-old-class
  radio-button-pending-ring substitute-for-radio-button-pending-ring)

(def-class-method
    fix-frame-with-substitute-class (substitute-for-radio-button-pending-ring)
  ;; Should never really be here, since it should not have been saved
  ;;   out in this state -- unlikely that any KBs ever were.
  (delete-frame substitute-for-radio-button-pending-ring))

;; (MHD 8/7/89)



;; old checked indicator:
;;
;;  (def-class (radio-button-dot entity system-internal)
;;    (icon-description
;;      (:funcall-at-load-time
;;        create-icon-description
;;        20 20
;;        ((filled-circle (10 7) (13 10) (10 13)))
;;        ;; before 8/4/89:
;;  ;      ((circle (10 9) (11 10) (10 11))
;;  ;       (circle (10 8) (12 10) (10 12))
;;  ;       (circle (10 7) (13 10) (10 13)))
;;        )))


(def-class (substitute-for-radio-button-dot entity))

(def-substitute-for-old-class
  radio-button-dot substitute-for-radio-button-dot)

(def-class-method
    fix-frame-with-substitute-class (substitute-for-radio-button-dot)
  ;; presence implies it was checked
  (change-on/off-switch                                ; ok? (Maybe just leave out, since
    (superblock? substitute-for-radio-button-dot) t)        ; we're not running!) (MHD)
  (delete-frame substitute-for-radio-button-dot))

;; (MHD 8/7/89)






(def-class-method initialize-after-reading (radio-button)
  (funcall-superior-method radio-button)
  (change-on/off-switch radio-button nil))












;;;; Sliders



;;; A `slider' is an analog-like device for selecting a number by moving a
;;; `needle' to a position along a guide.  A slider has at least two subblocks:
;;; a needle and a guide.  It may also have a button label as an additional
;;; subblock.  A slider resembles the slider on standard home or car radio
;;; receivers.

;;; Basic Operation: When the user presses the mouse down on this button, the
;;; needle goes to where the mouse is and stays with the mouse until it is
;;; released.  If the user releases without the mouse being inside of the guide,
;;; the change is aborted, and the needle is restored to its original position.

;;; Other names: dial,

(def-class (slider (item non-action-button) (foundation-class slider))
  (minimum-value-for-slider nil (type number?) vector-slot system
                            user-overridable save)
  (maximum-value-for-slider nil (type number?) vector-slot system
                            user-overridable save)

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      200 8
       ;; Converting system icons to polygons/solid-rectangles JED 8/11/93
;      ((lines (0 7) (200 7))
;       (lines (0 8) (200 8)))))
      ((solid-rectangle (0 7) (200 8)))))
  (needle-tracking-data nil vector-slot system)        ; info. used at runtime

  (set-value-while-sliding? nil (type yes-or-no) vector-slot system
                            user-overridable save)
  ;; otherwise, set value whenever the slider value changes

  (when-to-show-value nil (type when-to-show-value) vector-slot system
                      user-overridable save)


  ;; new slot/attribute in 4.0:  (MHD 11/11/94)
  (format-for-slider-readout            ; format used when showing value in
    nil system lookup-slot              ;   the slider's own readout
    (type nil) ; Not yet for user's eyes -- switch to (type type-in-box-format?)
               ;   when ready to expose to users. (MHD 11/15/94)
    ))




(def-absent-slot-putter variable-for-slider (slider value)
  (put-associated-variable-designation?                ; defer to master slot putter
    slider value t))

;; old slot description:
;;  (variable-for-slider
;;    nil (type constant-variable-designation?) vector-slot system save)

;; old "slot alias":
;;  (def-slot-alias variable-for-slider variable slider)

;; old slot putter:
;;  (def-slot-putter variable-for-slider (slider designation? initializing?)
;;    (add-or-delete-button-frame-note
;;      slider 'button-missing-variable designation?)
;;    (install-true-value-update
;;      'handle-update-to-variable-for-button slider nil
;;      (if (not initializing?)
;;          (variable-for-slider slider)
;;          nil)
;;      designation?)
;;    (setf (variable-for-slider slider) designation?))

;; old reclaimer:
;;  (def-slot-value-reclaimer variable-for-slider (designation? slider)
;;    (install-true-value-update                        ; Actually deinstalling now.
;;      'handle-update-to-variable-for-button
;;      slider
;;      nil
;;      designation?
;;      nil)
;;    (reclaim-slot-value designation?))

(add-grammar-rules
  '((when-to-show-value ('only 'while 'sliding) while-sliding)
    (when-to-show-value 'never)
    (when-to-show-value 'always)))

(def-slot-putter when-to-show-value (slider value initializing?)
  (prog1 (setf (when-to-show-value slider) value)
         (when (not initializing?)
           (update-slider-readout slider nil)        ; redundant with the following?!
           (update-button slider))))

;; This compiler is for the benefit of attribute export only.  The grammar is
;; all that is needed for setting the slot otherwise.

(def-slot-value-compiler when-to-show-value (parse-result)
  (case parse-result
    (while-sliding 'while-sliding)
    (never 'never)
    (always 'always)
    (t
     (values
       bad-phrase
       (tformat-text-string
         "acceptable values are: only-while-sliding, never, and always.")))))




(def-slot-value-writer when-to-show-value (value)
  (twrite-string
    (case value
      (while-sliding "only while sliding")
      (never "never")
      (t                                        ; always
       "always"))))



;;; Update-slider-readout ... this does not assume that the slider minimum
;;; or maximum values have been set up.

(defun update-slider-readout (slider sliding? &optional exact-value-if-known?)
  (let ((slider-readout?
          (loop for subblock being each subblock of slider        ;   while sliding!
                when (frame-of-class-p subblock 'slider-readout)
                  do (return subblock))))
    (if (let ((when-to-show-value (when-to-show-value slider)))
          (or (eq when-to-show-value 'never)
              (and (eq when-to-show-value 'while-sliding)
                   (not sliding?))))
        (if slider-readout?
            (delete-frame slider-readout?))
        (let* ((minimum-value?
                 (minimum-value-for-slider slider))
               (maximum-value?
                 (maximum-value-for-slider slider)))
          (cond
            ((and minimum-value? maximum-value?)
             (let* ((readout-text-string
                      (with-temporary-gensym-float-creation update-slider-readout
                        (make-text-string-for-constant-attribute-value-if-any
                          (or exact-value-if-known?
                              (read-or-write-slider slider nil))
                          'number
                          (format-for-slider-readout slider)))
                      ;; Old way (before the format slot was added in 4.0):
                      ;;   (MHD 11/5/94)
                      ;;
                      ;; (twith-output-to-text-string
                      ;;   (tprin (read-or-write-slider slider nil) nil))
                      ))
               (if (null slider-readout?)
                   (let ((label
                           (make-button-label
                             (copy-text-string readout-text-string)
                             nil 'slider-readout)))
                     (add-to-block
                       label slider
                       (halfw (-w (+w (left-edge-of-block slider)
                                      (right-edge-of-block slider))
                                  (width-of-block label)))
                       (bottom-edge-of-block slider)
                       t t))
                   (replace-text-with-text-string-in-text-box
                     readout-text-string slider-readout?))
               (reclaim-text-string readout-text-string))))))))


(def-class (slider-needle entity)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      10 40
       ;; Converting system icons to polygons/solid-rectangles JED 8/11/93
       ((filled-polygon ( (1 1) (9 1) (5 5) ) ( (1 1) (9 1) (5 5) ))))))
;      ((lines (1 1) (1 1))
;       (lines (9 1) (9 1))
;
;       (lines (2 1) (2 2))
;       (lines (8 1) (8 2))
;
;       (lines (3 1) (3 3))
;       (lines (7 1) (7 3))
;
;       (lines (4 1) (4 4))
;       (lines (6 1) (6 4))
;
;       (lines (5 1) (5 5))))))


(def-spot slider-spot
    :slots nil
    :include spot                                            ; Shouldn't this inherit from button-spot?
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented slider)

(def-class-method generate-spot (slider mouse-pointer)
  (push-last-spot mouse-pointer (make-slider-spot) slider))


(define-slot-alias minimum-value minimum-value-for-slider slider)
(define-slot-alias maximum-value maximum-value-for-slider slider)


(def-class (slider-minimum-value-label text-box)
  (default-text-box-format-name button-label-format))        ; CANNOT be subclass of button-label now!

(def-class (slider-maximum-value-label text-box)
  (default-text-box-format-name button-label-format))

(def-class (slider-readout text-box)
  (default-text-box-format-name button-label-format))

;; These methods cause all of these subblocks to generate instead a
;; spot for their parent, the slider.
(def-class-method generate-spot (slider-minimum-value-label mouse-pointer)
  (generate-spot-for-aggregate slider-minimum-value-label mouse-pointer))

(def-class-method generate-spot (slider-maximum-value-label mouse-pointer)
  (generate-spot-for-aggregate slider-maximum-value-label mouse-pointer))

(def-class-method generate-spot (slider-readout mouse-pointer)
  (generate-spot-for-aggregate slider-readout mouse-pointer))

(def-class-method generate-spot (slider-needle mouse-pointer)
  (generate-spot-for-aggregate slider-needle mouse-pointer))



(def-slot-putter minimum-value-for-slider (slider variable-value? initializing?)
  (put-slot-value-for-minimum-or-maximum-value-for-slider
    slider variable-value? initializing? t))


(def-slot-putter maximum-value-for-slider (slider variable-value? initializing?)
  (put-slot-value-for-minimum-or-maximum-value-for-slider
    slider variable-value? initializing? nil))


;;; `put-slot-value-for-minimum-or-maximum-value-for-slider' ... expects
;;; variable-value? to be a slot value number, i.e. a slot value float or a
;;; regular number.

(defun put-slot-value-for-minimum-or-maximum-value-for-slider
       (slider variable-value? initializing? minimum-case?)
  (add-or-delete-button-frame-note
    slider
    (if minimum-case?
        'button-missing-minimum-value
        'button-missing-maximum-value)
    variable-value?)
  (cond
    ((not initializing?)
     (delete-subblocks-of-class
       slider
       (if minimum-case?
           'slider-minimum-value-label
           'slider-maximum-value-label))
     (cond
       (variable-value?
        (let ((label
                (make-button-label
                  (twith-output-to-text-string
                    (if (slot-value-float-p variable-value?)
                        (tprin (slot-value-float-value variable-value?) nil)
                        (tprin variable-value? nil)))
                  nil
                  (if minimum-case?
                      'slider-minimum-value-label
                      'slider-maximum-value-label))))
          (add-to-block
            label slider
            (if minimum-case?
                (-w (left-edge-of-block slider)
                    (width-of-block label))
                (right-edge-of-block slider))
            (-w (bottom-edge-of-block slider)
                (height-of-block label))
            t t))))))

  ;; Fix up slider button label so that it doesn't run into the
  ;;   minimum value label if necessary.  Done in accord with
  ;;   constraints described under update-button-label.
  (if (and minimum-case? (not initializing?))
      (loop for label-subblock-maybe being each subblock of slider
            when (frame-of-class-p label-subblock-maybe 'button-label)
              return
                (loop with ideal-left-edge
                        = (-w (left-edge-of-block slider)
                              (width-of-block label-subblock-maybe)
                              50)
                      for min-value-label-subblock-maybe
                          being each subblock of slider
                      when (frame-of-class-p
                             min-value-label-subblock-maybe
                             'slider-minimum-value-label)
                        do (setq ideal-left-edge
                                 (minw ideal-left-edge
                                       (-w (left-edge-of-block
                                             min-value-label-subblock-maybe)
                                           (width-of-block label-subblock-maybe)
                                           5)))
                           (loop-finish)
                      finally
                        (cond
                          ((not (=w (left-edge-of-block label-subblock-maybe)
                                    ideal-left-edge))
                           (erase-images-of-block label-subblock-maybe t)
                           (shift-block
                             label-subblock-maybe
                             (-w ideal-left-edge
                                 (left-edge-of-block label-subblock-maybe))
                             0)
                           (draw-images-of-block label-subblock-maybe t))))))
  (prog1
    (if minimum-case?
        (setf (minimum-value-for-slider slider) variable-value?)
        (setf (maximum-value-for-slider slider) variable-value?))
    (when (and (not initializing?)
               ;; sliders must have a minimum-value-for-slider and
               ;; maximum-value-for-slider for this to be done; also
               ;; must be active-p -- I think active-p won't happen if
               ;; the above names slots are not filled in, but I don't
               ;; want to assume that here in this code.  The following
               ;; 3 checks were not done in 3.0 Beta Revs 0-1.  This was
               ;; causing an abort.  Fixed today.  By the way this code
               ;; was put in during 3.0 development in order to get
               ;; sliders to update after an edit that makes them able
               ;; to display a value while running.  (MHD 4/4/92)
               ;; --- UPDATE: activation was changed to propagate to
               ;; incomplete things.  Things that used to check active-p
               ;; may now have to check frame-ok-p as well.  Active-p
               ;; always checked active-p, and now it has been updated
               ;; to check frame-ok-p, too.  For now, I'll just leave
               ;; this code as is.  (MHD 3/19/93)
               ;; Sliders must now be just runnable-p, not active-p to work.
               ;; -jra 11/6/96
               (minimum-value-for-slider slider)
               (maximum-value-for-slider slider)
               (runnable-p slider))
      (update-slider-readout slider nil)        ; redundant with the following?!
      (when g2-has-v5-mode-windows-p
        (send-ws-representations-item-virtual-attribute-change
          slider (virtual-attribute 'slider-value) nil))
      (update-button slider))))






;;; `Change-slider' moves the needle to (x-in-workspace, y-in-workspace) if that
;;; is "in" the slider.  If not, it returns the slider to its original position,
;;; as given by the needle tracking data slot.

(defun change-slider (slider x-in-workspace y-in-workspace)
  (when (or (runnable-p slider)
            (button-in-use-by-system-p slider))
    (unless (in-extreme-edges-of-block-p slider x-in-workspace y-in-workspace)
      (let ((position-from-data (cddr (needle-tracking-data slider))))
        (setq x-in-workspace (pop position-from-data))        ; Changes args!
        (setq y-in-workspace (pop position-from-data))))
    (let ((needle nil)
          (slider-readout? nil))
      (loop for subblock being each subblock of slider
            do (frame-class-case subblock
                 (slider-needle
                   (setq needle subblock)
                   (if slider-readout? (return nil)))
                 (slider-readout
                   (setq slider-readout? subblock)
                   (if needle (return nil)))))
      (let* ((half-width-of-mouse
               (halfw (width-of-block needle)))
             (x-shift-for-needle
               (-w
                 (maxw
                   (left-edge-of-block slider)
                   (minw (right-edge-of-block slider)
                         (+w x-in-workspace
                             (let* ((tracking-data (needle-tracking-data slider))
                                    (original-left-edge-in-workspace
                                      (pop tracking-data))
                                    (original-mouse-x-in-workspace
                                      (progn (pop tracking-data) (pop tracking-data))))
                               (-w (+w original-left-edge-in-workspace
                                       half-width-of-mouse)
                                   original-mouse-x-in-workspace)))))
                 (+w (left-edge-of-block needle)
                     half-width-of-mouse)))
             (y-shift-for-needle
               ;; Move the bottom edge of the slider needle to rest on the top
               ;; edge of the slider.  Almost always a zero shift, but not
               ;; there's a resize of the slider or needle icon.
               (-w (-w (top-edge-of-block slider)
                       (height-of-block needle))
                   (top-edge-of-block needle))))
        (when (or (not (and (=w 0 x-shift-for-needle)
                            (=w 0 y-shift-for-needle)))
                  (null slider-readout?))                    ; => just have to get readout drawn
          (update-images-of-block needle t nil)
          (shift-block needle x-shift-for-needle y-shift-for-needle)
          (when (set-value-while-sliding? slider)
            (set-variable-per-button-if-appropriate slider nil))
          (update-slider-readout slider t)
          (update-images-of-block needle nil nil))))))

;; Consider filling in the left side by having a subblock, needle-fill, that
;; draws itself as a dark rectangle from zero up to the needle.




;;; Reset-slider ... resets slider to its "inactive" position, i.e. that assumed
;;; on a KB reset or when the slider gets deactivated.

(defun reset-slider (slider)
  (let* ((slider-needle
           (loop for subblock being each subblock of slider
                 when (frame-of-class-p subblock 'slider-needle)
                   return subblock))
         (slider-readout?
           (loop for subblock being each subblock of slider
                 when (frame-of-class-p subblock 'slider-readout)
                   return subblock))
         (left-edge-for-needle
           (-w (left-edge-of-block slider)
               (halfw (width-of-block slider-needle))))
         (top-edge-for-needle
           (-w (top-edge-of-block slider)
               (height-of-block slider-needle))))
    (unless (and (=w left-edge-for-needle
                     (left-edge-of-block slider-needle))
                 (=w top-edge-for-needle        ; unnec.
                     (top-edge-of-block slider-needle)))

      (update-images-of-block slider-needle t nil)
      (shift-block
        slider-needle
        (-w left-edge-for-needle
            (left-edge-of-block slider-needle))
        (-w top-edge-for-needle
            (top-edge-of-block slider-needle)))
      (update-images-of-block slider-needle nil nil)
      (if slider-readout?
          (update-slider-readout slider t)))))

;; Improve sliders so that their display is not ambiguous -- as things now stand,
;; the "reset" display looks the same as it would if the value of the associated
;; variable or parameter was equal to the slider's value!!

;; This is essentially the deactivate-subclass-of-entity method; consider just
;; defining it that way.





;;; Read-or-write-slider ... may only be used if there is a minimum and maximum
;;; value for the slider.  The needle is set if new-value? is not nil; in this
;;; case, new-value? is expected to be an acceptable value (in the range of the
;;; slider).  New-value? should be a gensym float.

;;; This returns as its single value the final value for the slider.  It should
;;; always be called within a with-temporary-gensym-float-creation context,
;;; since it potentially does arithmetic that conses.  The value returned is a
;;; number, possibly a gensym float.

(defun read-or-write-slider (slider new-value?)
  (let* ((minimum-value (minimum-value-for-slider slider))
         (maximum-value (maximum-value-for-slider slider))
         (minimum-value-position (left-edge-of-block slider))
         (maximum-value-position (right-edge-of-block slider))
         (needle
           (loop for subblock being each subblock of slider
                 when (frame-of-class-p subblock 'slider-needle)
                   return subblock))
         (needle-x-position
           (maxw
             minimum-value-position
             (minw
               maximum-value-position
               (+w (left-edge-of-block needle)
                   (halfw (width-of-block needle))))))
         (coerced-minimum-value
           (cond ((slot-value-float-p minimum-value)
                  (slot-value-float-value minimum-value))
                 ((slot-value-long-p minimum-value)
                  (coerce-to-gensym-float (slot-value-long-value minimum-value)))
                 (t
                  (coerce-to-gensym-float minimum-value))))
         (coerced-maximum-value
           (cond ((slot-value-float-p maximum-value)
                  (slot-value-float-value maximum-value))
                 ((slot-value-long-p maximum-value)
                  (coerce-to-gensym-float (slot-value-long-value maximum-value)))
                 (t
                  (coerce-to-gensym-float maximum-value))))
         (coerced-span-value
           (-e coerced-maximum-value coerced-minimum-value))
         (coerced-width-of-range
           (coerce-to-gensym-float
             (-w maximum-value-position minimum-value-position)))
         (trivial-case-p (=e 0.0 coerced-width-of-range))
         (percentage
           (if trivial-case-p
               0.0
               (/e (coerce-to-gensym-float
                     (-w needle-x-position minimum-value-position))
                   coerced-width-of-range)))
         (unrounded-value
           (if trivial-case-p
               coerced-minimum-value
               (+e coerced-minimum-value
                   (*e coerced-span-value percentage))))
         (value
           (if (or (not (typep minimum-value 'fixnum))
                   (not (typep maximum-value 'fixnum)))
               unrounded-value
               (round unrounded-value)))
         computed-value-position)
    (cond
      (new-value?
       (setq computed-value-position
             (if (=e 0.0 coerced-span-value)
                 needle-x-position
                 (*e
                   (/e
                     (-e (coerce-to-gensym-float new-value?) coerced-minimum-value)
                     coerced-span-value)
                   coerced-width-of-range)))
       (cond
         ((or (nanp new-value?)
              (exceptional-float-p new-value?)
              (not (= new-value? value)))
          (let* ((new-needle-x-position
                   (if (or (nanp new-value?)
                           (exceptional-float-p new-value?)
                           (=e coerced-width-of-range 0.0)
                           (exceptional-float-p computed-value-position))
                       minimum-value-position
                       (maxw
                         minimum-value-position
                         (minw
                           maximum-value-position
                           (+w minimum-value-position
                               (round computed-value-position))))))
                 (final-x-shift
                   (-w new-needle-x-position needle-x-position)))
            (cond
              ((not (=w final-x-shift 0))
               (erase-images-of-block needle t)
               (shift-block
                 needle (-w new-needle-x-position needle-x-position) 0)
               (draw-images-of-block needle t))))))
       (update-slider-readout slider nil new-value?)
       new-value?)
      (t value))))







;;; The `initialize method for slider', in addition to calling its superior's
;;; method, sets up the frame notes based on whether the required
;;; minimum/maximum value parameters have been established.  Also, when called
;;; in the clone case, it resets the slider; in the make-frame case, it can't be
;;; done here because the required subblocks, including the slider needle, are
;;; not yet present, so the equivalent gets done by make-button.

(def-class-method initialize (slider)
  (funcall-superior-method slider)
  (add-or-delete-button-frame-note
    slider 'button-missing-minimum-value
    (minimum-value-for-slider slider))
  (add-or-delete-button-frame-note
    slider 'button-missing-maximum-value
    (maximum-value-for-slider slider))
  (let ((clone-case?
          (loop for subblock being each subblock of slider
                thereis (frame-of-class-p subblock 'slider-needle))))
    (when clone-case?
      (reset-slider slider))))


;;; The `initialize-after-reading method for slider', in addition to calling its
;;; superior method, resets the slider.

(def-class-method initialize-after-reading (slider)
  (funcall-superior-method slider)

  ;; Bring slider needle edges in sync with icon description, in case
  ;; it has gotten an new one since it was saved.  This will be done
  ;; by the initialize-after-reading method on the needle, if it hasn't
  ;; already, but we don't know the order of the calling of that method
  ;; on the different blocks involved; and we have to assure it's done
  ;; now, so that reset-slider can fix its position.
  (loop for subblock being each subblock of slider
        when (frame-of-class-p subblock 'slider-needle)
          return (bring-block-edges-in-synch-with-icon-description subblock))
  (reset-slider slider))





;;; The function `mouse-down-on-slider' enters button-down context if the mouse
;;; was clicked on the slider needle.  Otherwise, it does nothing.

(defun mouse-down-on-slider (slider image-plane x-in-window y-in-window)
  (let (x-in-workspace y-in-workspace)
    (with-image-plane-transform (image-plane)
      (setf x-in-workspace (x-in-workspace x-in-window))
      (setf y-in-workspace (y-in-workspace y-in-window)))

    ;; Mouse on the needle?
    (let ((slider-needle?
            (loop for subblock being each subblock of slider
                  when (and (frame-of-class-p subblock 'slider-needle)
                            (in-block-p subblock x-in-workspace y-in-workspace))
                    return subblock)))

      (when slider-needle?
        (change-slot-value slider 'needle-tracking-data
                           (slot-value-list
                             (left-edge-of-block slider-needle?)
                             (top-edge-of-block slider-needle?)
                             x-in-workspace y-in-workspace))

        (enter-button-down-context slider image-plane)))))




;;;; Type-in Boxes


;;; A `type-in box' ...

;;; A type-in box has no icon description.  It has its own trivial draw method,
;;; which simply draws its subblocks.  Its graphic appearance is completely
;;; determined its subblocks. These consist of its bounding box, used to draw
;;; the rectangular box around it; its label, used for arbitrary free associated
;;; text; and its type-in text box, which can display the current value, or be
;;; edited to set the current value, of any G2 variable.

;;; The width and height of a type-in box are always maintained as the width and
;;; height, respectively, of its bounding box.

(def-class (type-in-box (item non-action-button) (foundation-class type-in-box))
  (format-for-type-in-box
    nil system user-overridable lookup-slot
    (type type-in-box-format?)
    (attribute-export-comment "The name of a text format."))
  (icon-description nil)
  (type-in-box-input-value
    nil (type read-only-attribute) vector-slot system
    do-not-put-in-attribute-tables do-not-save)
  (last-value-displayed-in-type-in-box?
    nil do-not-save vector-slot system)
  (type-of-last-value-displayed-in-type-in-box?
    nil do-not-save vector-slot system)
  (blank-for-type-in?                                ; "clear-on-edit?"? "blank-the-edit-box?"
    t (type yes-or-no) lookup-slot system user-overridable save
    (attribute-export-comment "boolean"))
  (have-edit-option-buttons-for-type-in?        ; New for 2.0. (MHD 9/19/89)
    nil (type yes-or-no) lookup-slot system user-overridable save
    (attribute-export-comment "boolean"))
  (show-prompts-for-type-in?                ; New for 8.0. (MHD 5/26/04)
    nil (type yes-or-no) lookup-slot system user-overridable save
    (attribute-export-comment "boolean")))


(define-slot-alias show-prompts-for-type-in show-prompts-for-type-in? type-in-box)




(def-absent-slot-putter typed-in-type-in-box-value (type-in-box value)
  ;; was a SAVE slot until 11/8/89 -- now obsolete, replaced somewhat
  ;;   by type-in-box-input-value; just let old value, if any, be
  ;;   garbage. (MHD 4/4/90)
  type-in-box value                                ; ignored
  )

(def-absent-slot-putter variable-for-type-in-box (type-in-box value)
  (put-associated-variable-designation?                ; defer to master slot putter
    type-in-box value t))

;; old slot description:
;;  (variable-for-type-in-box
;;    nil (type constant-variable-designation?) vector-slot system save)

;; old "slot alias":
;;  (def-slot-alias variable-for-type-in-box variable type-in-box)

;; old slot putter:
;;  (def-slot-putter variable-for-type-in-box
;;                   (type-in-box designation? initializing?)
;;    (add-or-delete-button-frame-note
;;      type-in-box 'button-missing-variable designation?)
;;    (install-true-value-update
;;      'handle-update-to-variable-for-button type-in-box nil
;;      (if (not  initializing?)
;;          (variable-for-type-in-box type-in-box)
;;          nil)
;;      designation?)
;;    (setf (variable-for-type-in-box type-in-box) designation?))        ; clear display!?

;; old reclaimer:
;;  (def-slot-value-reclaimer variable-for-type-in-box (designation? type-in-box)
;;    (install-true-value-update                        ; Actually deinstalling now.
;;      'handle-update-to-variable-for-button
;;      type-in-box
;;      nil
;;      designation?
;;      nil)
;;    (reclaim-slot-value designation?))

(def-class-method draw (type-in-box)
;  (draw-subblocks type-in-box)
  type-in-box)


(def-spot type-in-box-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented type-in-box)

(def-class-method generate-spot (type-in-box mouse-pointer)
  (push-last-spot mouse-pointer
                  (make-type-in-box-spot)
                  type-in-box))


(defun mouse-select-on-type-in-box (type-in-box image-plane x-in-workspace y-in-workspace)
  (when (runnable-p type-in-box)
    (highlight-or-unhighlight-button type-in-box t)
    (when (in-block-p type-in-box x-in-workspace y-in-workspace)
      (let ((variable?
              (get-variable-for-button-if-any type-in-box)))
        (when variable?
          (let ((text-box (get-type-in-text-box type-in-box)))
            (multiple-value-bind (line-index? character-index?)
                (if (not
                      (or (blank-for-type-in? type-in-box)
                          (null (last-value-displayed-in-type-in-box?
                                  type-in-box))))
                    (find-position-in-text
                      text-box nil nil nil
                      t                        ; t?
                      x-in-workspace
                      y-in-workspace
                      nil nil nil nil))
              (enter-editing-context
                type-in-box 'type-in-box-input-value
                (if line-index?
                    (copy-text (cdr (box-translation-and-text text-box)))
                    (make-empty-text))
                nil
                (text-box-format text-box)
                nil
                line-index? character-index?
                image-plane
                text-box
                nil nil nil nil
                (get-type-of-slot-if-any-for-type-in-box type-in-box variable?)
                nil nil
                (not (have-edit-option-buttons-for-type-in? type-in-box))
                (not (show-prompts-for-type-in? type-in-box))))))))))



;;; `Get-type-of-slot-if-any-for-type-in-box' returns the type slot feature to
;;; be used for editing and parsing input for a type-in box.  This function
;;; helps to implement in a new feature in G2 8.0 (as of May, 2004): if type is
;;; free-text, and variable is a text variable, edit as free text, i.e.,
;;; returning the type feature (TYPE FREE TEXT) from this function.  In this
;;; case, type-in-box-input-value putter will postprocess the result.

(defun get-type-of-slot-if-any-for-type-in-box (type-in-box variable)
  (let* ((type-of-slot?
           (get-type-of-slot-if-any-for-variable variable))
         (category?
           (if type-of-slot?
               (category-symbol-given-slot-type type-of-slot?)))
         (quantitative-p
           (or (quantitative-variable-p variable)
               (quantitative-parameter-p variable)))
         (format (format-for-type-in-box type-in-box)))
    (cond
      ((and (eq format 'free-text)
            (eq category? 'whole-string))
       '(type free text))
      ((and quantitative-p (eq format 'time-stamp))
       (frame-class-case variable
         ((integer-variable integer-parameter)
          '(type time-stamp))
         (t
          '(type time-stamp-optionally-with-subseconds))))
      ((and quantitative-p (eq format 'seconds))
       '(type interval))
      (t type-of-slot?))))






;;; A `type-in-text-box' is the operative subblock of a type-in-box.  When
;;; selected, they defer to the type-in-box.

(def-class (type-in-text-box text-box)
  (box-translation-and-text nil (type free text))
  (default-text-box-format-name default-type-in-box-format)

  (minimum-width-of-text-box 0)                ; experiment w/these
  (minimum-height-of-text-box 0))

(def-format-class (type-in-box-format text-box-format)
  (text-cell-font-map (hm18))
  (text-box-left-border-width 1)
  (text-box-top-border-width 1)
  (text-box-right-border-width 1)
  (text-box-bottom-border-width 1)
  (text-cell-lines-justified? nil)
  (text-cell-paragraph-indentation 0)
  (text-cell-turnover-line-indentation 14)
  (text-cell-line-spacing 3)
  (text-cell-left-margin 6)
  (text-cell-top-margin 5)
  (text-cell-right-margin 6)
  (text-cell-bottom-margin 6)
  (text-cell-line-quadding? nil)
  (minimum-format-width-for-text-cell 340)
  (text-cell-line-height 20)
  (text-cell-baseline-position 15)
  (text-cell-line-spacing 3)
  (default-word-spacing
    #.(convert-to-text-width 6))
  (minimum-word-spacing
    #.(convert-to-text-width 3))
  (maximum-word-spacing
    #.(convert-to-text-width 14)))



;;; The class-method `generate-spot' for type-in-text-box defers to its
;;; superblock, a type-in-box.

(def-class-method generate-spot (type-in-text-box mouse-pointer)
  (when (superblock? type-in-text-box)
    (funcall-method 'generate-spot
                    (superblock? type-in-text-box)
                    mouse-pointer)))




(defun get-type-in-text-box (type-in-box)
  (loop for subblock being each subblock of type-in-box
        thereis
          (if (frame-of-class-p subblock 'type-in-text-box)
              subblock)))                        ; make this a macro?



;;; `Type-in-box-free-text-p' is true if value, a slot value, is of
;;; the form taken by a free text slot value, namely a cons of the form
;;;
;;;   ( no-value . text)
;;;
;;; where no-value is the value of special variable no-value, and text is a text
;;; (as defined in BOXES).

(defun free-text-slot-value-p (value)
  (and (consp value) (eq (car value) no-value)))




;;; The `slot-putter for type-in-box-input-value' ...

;;; Handling of values that are in free text format:
;;;
;;; When you click on a type-in box that has format FREE-TEXT, the editor is
;;; entered to edit with the type of slot = (type free text), which means that
;;; the value be a box-translation-and-text type of value that evaluates to true
;;; by the predicate free-text-slot-value-p.  This slot putter is then called
;;; after that editor is exited.
;;;
;;; A lot may have changed by virtue of arbitrary KB edits since we entered the
;;; editor, which this code has to be mindful of in order to avoid an abort.
;;;
;;; The first form below (in the non-initializing case) may set new-value or
;;; leave it the same as value based on value, variable?, and the type-in
;;; box. If it sets it nil, it means there's a problem with value.
;;;
;;; This deals with the postprocessing necessary with free-text format. The
;;; editor was told in this case to not parse anything, but to deliver free
;;; text. Note that argument value may have be changed to nil by this.
;;;
;;; If null, something bad happened -- variable was deleted, was renamed, a
;;; variable of a different (non-text) type got the name we're currently using
;;; OR the format was changed, resulting in a mismatch between format and type.
;;; These are very obscure cases, unlikely to really happen in a deployment
;;; environment, and we need not give a very detailed explanation, or do much
;;; more than give a simple error message and then punt out.

(def-slot-putter type-in-box-input-value (type-in-box value initializing?)
  (unless initializing?
    (let* ((variable? (get-variable-for-button-if-any type-in-box)))
      (when (free-text-slot-value-p value)
        (let ((replacement-string?
                (if (and variable?
                         (eq (format-for-type-in-box type-in-box) 'free-text))
                    (let* ((type-of-slot?
                             (get-type-of-slot-if-any-for-variable variable?)))
                      (if (eq (if type-of-slot?
                                  (category-symbol-given-slot-type type-of-slot?))
                              'whole-string)
                          (convert-text-to-text-string (cdr value)))))))
          (when (null replacement-string?)
            (notify-user
              "Cannot set value from type-in-box ~NF due to a change in the KB during type-in."
              type-in-box))
          (setq value replacement-string?)))
      (cond
        ((or (null variable?) (null value))
         (store-managed-number-or-value
           (last-value-displayed-in-type-in-box? type-in-box)
           nil)
         (setf (type-of-last-value-displayed-in-type-in-box? type-in-box)
               nil)
         (update-display-of-type-in-box type-in-box nil nil))
        (t
         (with-temporary-gensym-float-creation type-in-box-putter
           (multiple-value-bind (cached-value expiration type)
               (convert-constant-attribute-value-to-cached-value value)
             expiration                                ; not used
             (store-managed-number-or-value
               (last-value-displayed-in-type-in-box? type-in-box)
               cached-value)
             (setf (type-of-last-value-displayed-in-type-in-box? type-in-box)
                   type)
             (update-display-of-type-in-box type-in-box cached-value type)))))))
  (setf (type-in-box-input-value type-in-box) value)
  (unless initializing?
    (set-variable-per-button-if-appropriate type-in-box nil))
  value)




(defun update-display-of-type-in-box
    (type-in-box
      constant-attribute-value-or-cached-value? type-if-a-cached-value?)
  (let ((type-in-text-box?
          (get-type-in-text-box type-in-box))
        replacement-text-string)
    ;; MHD, please review!  I added the following WHEN form to test
    ;; type-in-text-box.  This function was crashing when called from the
    ;; initialize method for the type-in-box.  - cpm, 7/25/94
    (when type-in-text-box?
      (setq replacement-text-string
            (make-text-string-for-constant-attribute-value-if-any
              constant-attribute-value-or-cached-value?
              type-if-a-cached-value?
              (format-for-type-in-box type-in-box)))
      (replace-text-with-text-string-in-text-box
        replacement-text-string type-in-text-box?)
      (reclaim-text-string replacement-text-string)
      (change-edges-of-block
        type-in-box nil nil
        (right-edge-of-block type-in-text-box?)
        (bottom-edge-of-block type-in-text-box?)))))



;;; `Make-text-string-for-constant-attribute-value-if-any' ... Type-if-cached?
;;; may be NUMBER, as long as value? is known to be a number.  If it is not one
;;; of the known numeric subtypes (number, float, etc.), number-format will be
;;; ignored.

(defun make-text-string-for-constant-attribute-value-if-any
    (value? type-if-cached? format)
  (if (null value?)
      (copy-constant-wide-string #w"****")
      (twith-output-to-text-string
        (let ((write-symbols-in-lower-case? t))
          (cond
            ((and (number-subtype-p type-if-cached?)
                  (consp format))        ; dd.ddd type format
             (twrite-number-per-format value? format))
            (type-if-cached?
             (print-constant
               value?
               (if (number-subtype-p type-if-cached?)
                   (case format
                     (time-stamp 'time-stamp)
                     (seconds 'seconds)
                     (t type-if-cached?))
                   type-if-cached?)
               (eq format 'free-text)))
            ((eq format 'free-text)
             (write-evaluation-value value? t))
            (t (write-attribute-from-slot value? nil)))))))


;;; `Twrite-number-per-format' writes a number according to
;;; number-format. Number-format can be one of the following:
;;;
;;;   TIME-STAMP;
;;;   SECONDS; or
;;;   a cons of the form (integral-size . fraction-size)  (only for floats)

(defun twrite-number-per-format (value number-format)
  (case number-format
    (time-stamp (print-constant value 'time-stamp))
    (seconds (print-constant value 'seconds))
    (t
     (typecase value
       (float
        (cond
          ((consp number-format)
           (let ((integral-size (car number-format))
                 (fraction-size (cdr number-format)))
             (write-floating-point-number
               value integral-size fraction-size 6 nil nil nil)))
          (t
           (twrite-float value))))
       (integer
        (tformat "~d" value))))))




(defun change-type-in-box (type-in-box cached-value? type?)
  (store-managed-number-or-value
    (last-value-displayed-in-type-in-box? type-in-box)
    cached-value?)

  ;; Type-in-box-input-value should never be NIL, since then the editor
  ;; would supress the written value.  Since this slot is brought into
  ;; synch with the actual value only around the edit, and by the writer,
  ;; the value prior to writing isn't relevant. (MHD 7/1/92)  KLUDGE?
  (setf (type-in-box-input-value type-in-box) T)

  (setf (type-of-last-value-displayed-in-type-in-box? type-in-box) type?)
  (update-display-of-type-in-box type-in-box cached-value? type?))

;; It would probably be preferable to slam the type-in-box-input-value to
;; a non-nil value in the def-class. (MHD 7/1/92)


(def-class-method initialize-after-reading (type-in-box)
  (funcall-superior-method type-in-box)
  (change-type-in-box type-in-box nil nil))


(def-class-method initialize (type-in-box)
  (funcall-superior-method type-in-box)
  (change-type-in-box type-in-box nil nil))










;;;; Arrow Buttons




(def-class (arrow-button generic-action-button)
  (frame-status-and-notes nil)                        ; override inherited default
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      13 13 ((outline (0 0) (13 0) (13 13) (0 13))))))






(def-class (left-arrow-button arrow-button)
  (icon-description
    (:funcall-at-load-time create-arrow-description left 13)))

(def-class (up-arrow-button arrow-button)
  (icon-description
    (:funcall-at-load-time create-arrow-description up 13)))

(def-class (right-arrow-button arrow-button)
  (icon-description
    (:funcall-at-load-time create-arrow-description right 13)))

(def-class (down-arrow-button arrow-button)
  (icon-description
    (:funcall-at-load-time create-arrow-description down 13)))

















;;;; Buttons As Displays



;;; The activate-subclass-of-entity method for non-action-button schedules a task
;;; at priority 1 to call verify-and-set-variable-per-non-action-button.  This
;;; assures that the initialization of the button can really happen after
;;; everything else in the KB has been activated.

(def-class-method activate-subclass-of-entity (non-action-button)
  (with-current-scheduling (nil 1 nil nil nil (nil 'reclaim-frame-serial-number))
    (verify-and-set-variable-per-non-action-button
      non-action-button (copy-frame-serial-number
                          (current-frame-serial-number)))))

;; This method and the corresponding deactivate method should do something to show
;; that the type-in box is inactive!


(defun-void verify-and-set-variable-per-non-action-button
    (non-action-button reference-serial-number)
  (unless
      (frame-has-been-reprocessed-p non-action-button reference-serial-number)
    (if (value-on-activation? non-action-button)
        (set-variable-per-button-if-appropriate non-action-button t))
; for polling:
;     (schedule-cyclic-task
;       (button-update-task? non-action-button) 1 1 2
;       'update-button non-action-button)
     ))


(def-class-method deactivate-subclass-of-entity (non-action-button)
  ;; the following should logic should be paralleled in kb loading for
  ;;   buttons that were saved while the system was paused. (MHD 11/8/89)
  (frame-class-case non-action-button
    (type-in-box

      ;; New logic -- abort edits upon deactivation:  (MHD 5/15/92)
      (loop with type-in-text-box
              = (get-type-in-text-box non-action-button)
            while
              (loop for menu-or-edit-workspace
                        in (menus-for-this non-action-button)
                    when (frame-of-class-p menu-or-edit-workspace 'edit-workspace)
                      do (highlight-or-unhighlight-for-slot
                           type-in-text-box 'box-translation-and-text
                           nil nil t)
                         (delete-frame menu-or-edit-workspace)
                         (return t)))

      (change-type-in-box non-action-button nil nil))
    ;; This was not being done for the two following item until today!
    ;;   (MHD 11/8/89)
    (check-box
      (change-on/off-switch non-action-button no-value))
    (radio-button
      (change-on/off-switch non-action-button nil))
    (slider (reset-slider non-action-button)))
; for polling:
;  (cancel-task (button-update-task? non-action-button))
  )

(def-class-method deactivate-and-propagate (non-action-button ancestor-not-ok?)
  (funcall-superior-method non-action-button ancestor-not-ok?)
  (when g2-has-v5-mode-windows-p
    (frame-class-case non-action-button
      ((check-box radio-button)
       (send-ws-representations-item-virtual-attribute-change
         non-action-button (virtual-attribute 'button-status) nil))
      (slider
        (send-ws-representations-item-virtual-attribute-change
          non-action-button (virtual-attribute 'slider-value) nil))
      (type-in-box
        (send-ws-representations-item-virtual-attribute-change
          non-action-button (virtual-attribute 'type-in-box-value) nil)))))




;;; With-current-value-for-button-if-any ... variables are bound during the call
;;; and the call takes place in a context in which all floating point numbers are
;;; temporary.  ONLY ONE VALUE may be returned from the body of this macro.

;;; As with get-current-value, all variables are valid if and only if the expiration?
;;; is non-nil.

;;; If the value is of type TEXT, it will be reclaimed upon exiting the body.

(defmacro with-current-value-for-button-if-any
          (((value-variable expiration?-variable type-variable
                            &optional (variable-variable? nil))
            button)
           &body body)
  (let ((variable-variable?
          (or variable-variable? '#:variable))
        (button-variable '#:button)
        (text-value-variable? (gensym)))
    `(with-temporary-gensym-float-creation button
       (let* ((current-computation-flags current-computation-flags)
              ;; the above binding inhibits backward chaining, data service, etc.
              (,button-variable ,button)
              (,variable-variable?
               (get-variable-for-button-if-any ,button-variable))
              ,value-variable ,expiration?-variable ,type-variable
              (,text-value-variable? nil))        ; non-nil at end of body only if value is
                                                ;   a string
         (setf (dont-compute-new-variable-values) t)
         (with-wake-up-management
           (none (,value-variable ,expiration?-variable ,type-variable) nil)
           (if ,variable-variable?
               (let ((*current-computation-frame* ,button-variable))        ; bind higher up?
                 (get-current-value ,variable-variable? nil))
               (values nil nil nil)))
         (prog1
           (progn
             (cond
               ((and ,expiration?-variable
                     (eq ,type-variable 'text))
                (setq ,text-value-variable? ,value-variable)))
             . ,body)
           (if ,text-value-variable?
               (reclaim-text-string ,text-value-variable?)))))))





;;; `buttons-in-button-down-state' is a system variable bound to a list of all buttons
;;; that are currently in the button down state.  Enter-button-down-context adds its
;;; button to this list and the clean-up method for the button-down context removes
;;; it. Functions that change buttons asynchronously (i.e. from the scheduler) should
;;; consult this list and not do so if the button is a member of this list.

(def-system-variable buttons-in-button-down-state controls nil)

;; Consider putting this into the workstation structure, making it a KB specific
;; variable, or doing something else with it.

;; Note that, at present, this is consulted only in the update-button function,
;; above.





;;; The function `handle-update-to-variable-for-button' is called whenever the
;;; value of a variable which is being monitored by a button changes.  If the
;;; last argument is non-null, it means that a constant valued attribute of the
;;; passed frame has changed, and this function should ignore that update.
;;; Also, if the passed button is inactive, this function should ignore the
;;; update.

(defun handle-update-to-variable-for-button
       (button ignored-extra-argument ignored-variable attribute-name? old-value
               class-if-specific?)
  (declare (ignore ignored-extra-argument ignored-variable old-value class-if-specific?))
  (when (and (null attribute-name?)
             (runnable-p button))
    (when g2-has-v5-mode-windows-p
      (frame-class-case button
        ((radio-button check-box)
         (send-ws-representations-item-virtual-attribute-change
           button (virtual-attribute 'button-status) nil))
        (slider
          (send-ws-representations-item-virtual-attribute-change
            button (virtual-attribute 'slider-value) nil))
        (type-in-box
          (send-ws-representations-item-virtual-attribute-change
            button (virtual-attribute 'type-in-box-value) nil))))
    (update-button button)))

;; Note that update-button checks active-p on the button as well, and that it
;; may not be needed here.  -jra & mhd 2/10/89





(defvar disable-update-button nil)

;;; `update-button' is the function used to reflect on a button the value of its
;;; associated variable.  This checks if button is active-p and frame-ok-p.  It
;;; won't do anything unless those are true.  It also checks that button is not
;;; in the button-down state, by checking that button is not an element of
;;; buttons-in-button-down-state.  It does nothing if the button is in the
;;; button-down state.

(defun-allowing-unwind update-button (button)
  (when (and (not disable-update-button)
             (runnable-p button)
             (not (memq button buttons-in-button-down-state)))
    (with-current-value-for-button-if-any ((value expiration? type variable) button)
      (frame-class-case button
        (check-box
          (cond
            ((null expiration?)
             (change-on/off-switch button no-value))        ; expired -- show "?"
            (t
             (change-on/off-switch
               button
               (cond
                 ((constant-attribute-value-equals-datum-p
                    (on-value-for-check-box button) value type)
                  t)
                 ((constant-attribute-value-equals-datum-p
                    (off-value-for-check-box button) value type)
                  nil)
                 (t no-value))))))
        (radio-button
          (cond
            ((null expiration?)
             (change-on/off-switch button nil))        ; expired -- leave off
            (t
             (change-on/off-switch
               button
               (constant-attribute-value-equals-datum-p
                 (value-for-radio-button button) value type)))))
        (slider
          (if (and expiration? (numberp value))        ; - value here is a raw (temporary) float
                                        ;     or an integer
              (read-or-write-slider                ; - we ignore no value or out-of-range(!)
                button value)))
        (type-in-box
          (cond
            ((null expiration?)                        ; no value
             (if (last-value-displayed-in-type-in-box? button)
                 ;; change only if now displaying (as an optimization):
                 (change-type-in-box button nil nil)))
            (t
             (let* ((managed-value-displayed?
                      (last-value-displayed-in-type-in-box? button))
                    (type-of-last-value-displayed
                      (type-of-last-value-displayed-in-type-in-box? button))
                    (cached-value-displayed?
                      (if managed-value-displayed?        ; optimization?!
                          (extract-cached-number-or-value
                            managed-value-displayed?))))
               (cond
                 ((null cached-value-displayed?)        ; no previous value
                  (change-type-in-box button value type))
                 ((not
                    (datum-equal
                      value type
                      cached-value-displayed? type-of-last-value-displayed))
                  (change-type-in-box button value type)))))))))))





(defun constant-attribute-value-equals-datum-p
       (constant-attribute-value datum datum-type)
  (multiple-value-bind (value expiration type)
      (convert-constant-attribute-value-to-cached-value constant-attribute-value)
    expiration  ; not used
    (datum-equal value type datum datum-type)))







;;;; Frame Notes for Buttons


;; Note: this is in transition -- this has been somewhat abstracted to support
;; frame notes at least for user menu choices in addition to buttons.  The names
;; and documentation still need to be changed to reflect that, but enough has
;; been done to allow using this for initial user menu choice frame notes right
;; now.  Needs finishing! (MHD 7/5/90)


;;; Make-list-of-button-status-and-types-of-notes is a function that takes a frame
;;; note status (the symbol nil, bad, or incomplete) and any number (less than the
;;; arbitrary limit of 12) of types of notes for buttons.

(defmacro make-list-of-button-status-and-types-of-notes-1
          (frame-note-status . types-of-notes)
  `(slot-value-list
     ,frame-note-status
     . ,(loop for type-of-note in types-of-notes
              collect type-of-note
              collect nil)))

(defun make-list-of-button-status-and-types-of-notes
       (frame-note-status
        &optional                                ; pseudo rest args
        (arg1 no-arg) (arg2 no-arg) (arg3 no-arg) (arg4 no-arg)
        (arg5 no-arg) (arg6 no-arg) (arg7 no-arg) (arg8 no-arg)
        (arg9 no-arg) (arg10 no-arg) (arg11 no-arg) (arg12 no-arg))
  (call-per-number-of-actual-args
    make-list-of-button-status-and-types-of-notes-1 1 frame-note-status
    arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10 arg11 arg12))





;;; Add-or-delete-button-frame-note is used for all frame notes for buttons.
;;; The allowed types of frame notes for buttons are: button-missing-variable,
;;; button-missing-minimum-value, button-missing-maximum-value, button-missing-
;;; value, button-missing-on-value, and button-missing-off-value.  These symbols
;;; are in the global variable all-types-of-frame-notes-for-buttons.

;;; This also checks and updates frame status appropriately.

(defparameter all-types-of-frame-notes-for-buttons
              '(button-missing-variable button-missing-minimum-value
                button-missing-maximum-value button-missing-value
                button-missing-on-value button-missing-off-value

                ;; new:   (MHD 7/5/90)
                user-menu-choice-or-action-button-missing-action
                user-menu-choice-missing-applicable-class
                user-menu-choice-missing-label

                ;; New.  -jra 10/12/91
                button-or-user-menu-choice-not-compiled-up-to-date

                ;; New.  -mhd 8/3/94
                user-menu-choice-condition-not-compiled-up-to-date
                ))

(defun button-frame-status (button)
  (let* ((embedded-rule-status
           (let ((embedded-rule?
                   (frame-class-case button
                     (generic-action-button
                       (embedded-rule? button))
                     (user-menu-choice
                       (embedded-rule-in-user-menu-choice? button)))))
             (and embedded-rule? (frame-status embedded-rule?))))
         (cell-array? (cell-array button))
         (cell-array-status
           (and cell-array?
                (loop with cells = (g2-cell-array-managed-array cell-array?)
                      for i from 0 below (managed-array-length cells)
                      when (not (expression-cell-able-to-compute-p
                                  (managed-svref cells i)))
                        return 'incomplete)))
         (button-status
           (if (loop for type-of-note in (cdr (frame-status-and-notes button)) by #'cddr
                     thereis (memq type-of-note all-types-of-frame-notes-for-buttons))
               'incomplete
               nil)))
    (frame-status-union
      cell-array-status
      (frame-status-union embedded-rule-status button-status))))

(defun add-or-delete-button-frame-note (button type-of-note delete-case?)
  (if delete-case?
      (delete-frame-note-if-any type-of-note button)
      (add-frame-note type-of-note button nil t nil))
  (update-frame-status
    button
    (button-frame-status button)
    nil))

(defun embedded-frame-parent-status (parent-frame embedded-frame)
  (or (and (or (frame-of-class-p parent-frame 'action-button)
               (frame-of-class-p parent-frame 'user-menu-choice))
           (button-frame-status parent-frame))
      (if (atom (frame-status-and-notes embedded-frame))
          (frame-status-and-notes embedded-frame)
          (car (frame-status-and-notes embedded-frame)))))

(def-frame-note-writer button-missing-variable (particulars)
  particulars
  (twrite-string
    "this is missing a variable"))

(def-frame-note-writer button-missing-minimum-value (particulars)
  particulars
  (twrite-string
    "this is missing a minimum value"))

(def-frame-note-writer button-missing-maximum-value (particulars)
  particulars
  (twrite-string
    "this is missing a maximum value"))

;;; The frame-note writer for button-missing-value ... for radio buttons.

(def-frame-note-writer button-missing-value (particulars)
  particulars
  (twrite-string
    "this is missing an on-value"))                ; slot name's alias was changed
                                                ;   from VALUE to ON-VALUE
                                                ;   for 3.0. (MHD 12/12/91)


(def-frame-note-writer button-missing-on-value (particulars)
  particulars
  (twrite-string
    "this is missing an on-value"))

(def-frame-note-writer button-missing-off-value (particulars)
  particulars
  (twrite-string
    "this is missing an off-value"))

(def-frame-note-writer user-menu-choice-or-action-button-missing-action
                       (particulars)
  particulars
  (twrite-string
    "this is missing an action"))

(def-frame-note-writer user-menu-choice-missing-applicable-class (particulars)
  particulars
  (twrite-string
    "this is missing an applicable class"))        ; alt: "does not specify
                                                ;   an applicable class"?

(def-frame-note-writer user-menu-choice-missing-label (particulars)
  particulars
  (twrite-string
    "this is missing a label"))

(def-frame-note-writer button-or-user-menu-choice-not-compiled-up-to-date
    (particulars)
  (declare (ignore particulars))
  (twrite-string "the action needs to be compiled"))

(def-frame-note-writer user-menu-choice-condition-not-compiled-up-to-date
    (particulars)
  (declare (ignore particulars))
  (twrite-string "the condition needs to be compiled"))

;;;







;;;; Dialogs




(define-workstation-context dialog ()
  :constructor (make-dialog-state (dialog-workspace dialog-image-plane))
  :state-variables (dialog-workspace
                     dialog-image-plane)
  ;; Maybe we should absorb modified mouse-up/down events here too?  -fmw,
  ;; 2/11/94
  :keymap (((<mouse-down> button-spot)
            mouse-down-on-button-in-dialog-state)
           ((<mouse-down> workspace-background-spot)
            mouse-down-on-workspace-in-dialog-state)
           ((<mouse-down> close-box-spot)
            mouse-down-on-close-box-widget-in-dialog-state)
           (<mouse-down>
             mouse-down-on-other-in-dialog-state)
           (<mouse-up>
             do-nothing-event-handler)
           (<standard-enter-keys>
             wrap-up-in-dialog-state)
           (<standard-abort-keys>
             cancel-in-dialog-state)
           (escape                        ; Only when selection UI enabled?
             cancel-in-dialog-state)))


(def-structure-method valid-workstation-context-p (dialog-state)
  (and (funcall-superior-method dialog-state)
       (valid-block-in-workstation-context-p
         (dialog-workspace dialog-state)
         dialog-state)))

(def-structure-method clean-up-workstation-context (dialog-state)
  (let ((dialog-workspace (dialog-workspace dialog-state)))
    (when (valid-block-in-workstation-context-p dialog-workspace dialog-state)
      (delete-frame dialog-workspace)))
  (funcall-superior-method dialog-state))

;;; The functions `wrapped-action-function' and
;;; `cancel-button-action-in-dialog-state' is used below in enter-dialog, as is
;;; `exit-current-workstation-context-function'.  Their jobs are to return from
;;; the current DIALOG context, and, in the case of wrapped-action-function,
;;; apply the user-supplied function to arglist.  They

(defun wrapped-action-function (function arglist)
  (let ((copy-of-arglist (copy-list-using-slot-value-conses arglist)))
    (case function
      (delete-frame-after-checking-serial-number
       (setf (second copy-of-arglist)
             (copy-frame-serial-number (second copy-of-arglist))))
      (allow-continuation-of-class-selection-upon-confirmation
       (setf (fourth copy-of-arglist)
             (copy-frame-serial-number (fourth copy-of-arglist)))))
    (return-from-current-workstation-context 'dialog)
    (apply function copy-of-arglist)
    (reclaim-button-action-arglist copy-of-arglist function)))

;; Deleting the workspace is no longer handled here, as it is redundant with the
;; cleanup function.  (MHD 3/20/94)

(defun cancel-button-action-in-dialog-state ()
  (abort-current-workstation-context 'dialog))



;;; The workstation context `native-simple-dialog' implements a simple dialog
;;; (as would be invoked by enter-dialog) that is "native", i.e., uses native
;;; Win32 dialog facilities, not G2 workspaces, buttons, etc. ...

(def-system-variable current-native-simple-dialog-handle controls 0)

(defun allocate-native-simple-dialog-handle ()
  (when (=f current-native-simple-dialog-handle most-positive-fixnum)
    (setq current-native-simple-dialog-handle 0))
  (incff current-native-simple-dialog-handle))

(define-workstation-context native-simple-dialog ()
  :parent nil                        ; Since the native dialog itself is modal, declare this modal,
  :modal t                        ; although we'll only see any events if the user typed ahead.
  :constructor (make-native-simple-dialog-state
                 (dialog-handle
                   dialog-message-text-string
                   ok-text-string?
                   ok-function? ok-function-arglist?
                   cancel-text-string? cancel-function? cancel-function-arglist?
                   additional-button-text-string? additional-button-function?
                   additional-button-arglist?
                   which-to-make-default-button?))
  :state-variables (dialog-handle
                     dialog-message-text-string
                     ok-text-string?
                     ok-function? ok-function-arglist?
                     cancel-text-string? cancel-function? cancel-function-arglist?
                     additional-button-text-string? additional-button-function?
                     additional-button-arglist?
                     which-to-make-default-button?)
  :keymap ((simple-dialog-ok ok-in-simple-dialog-state)
           (simple-dialog-cancel cancel-in-simple-dialog-state)
           (simple-dialog-additional additional-in-simple-dialog-state)
           (<standard-abort-keys> abort-workstation-context)))


(defun text-string-per-button-string-spec (spec label-type?)
  (if (and (null spec) label-type?)
      (get-dialog-label-text-string label-type?)
      (copy-text-string
	(or (if (eq spec 'none) #w"" spec)
	    #w""))))

;; The above should be documented & made generally usable: it's not just for
;; native dialogs.


;;; The function `fill-text-for-native-dialog' returns a new string with lines
;;; wrapped for a native dialog in exactly the same places G2 does for a classic
;;; dialog. Lines are separated with CRLF's. The input string is reclaimed.

(defun fill-text-for-native-dialog (string)
  (let* ((text (convert-text-string-to-text string))
         (formatted-text (reformat-text text (get-or-make-format-frame 'button-label-format)))
         (filled-text
           (remove-unicode-line-breaks
             (convert-text-to-string-with-native-line-breaks formatted-text))))
    (reclaim-text text)                        ; Incorporates string.
    (reclaim-text formatted-text)
    filled-text))

;; This ignores lost spaces.
(defun convert-text-to-string-with-native-line-breaks (text)
  (twith-output-to-text-string
    (loop with text-tail = text
          with text-line
          with line-length
          with lost-space-at-end-of-line
          as first = t then nil
          do (multiple-value-setq
                 (text-line line-length lost-space-at-end-of-line text-tail)
               (get-next-text-line text-tail))
             (when text-line
               (unless first
                 (twrite-char #.%return) ; CRLF
                 (twrite-char #.%linefeed))
               (twrite-string text-line))
          while text-line)))


;;; `Copy-text-string-for-native-word-wrap' copies text-string with unicode line
;;; breaks turned into CRLF's.  The word wrapper used for dialogs in Microsoft
;;; Windows will make these be hard linebreaks, whereas it cannot deal with the
;;; Unicode linebreak characters unfortunately.

(defun copy-text-string-for-native-word-wrap (text-string)
  (twith-output-to-text-string
    (loop for i from 0 below (lengthw text-string)
          as char = (charw text-string i)
          if (member char '(#.%line-separator #.%paragraph-separator))
            do (twrite-char #.%return)
               (twrite-char #.%linefeed)
          else do (twrite-char char))))

(defun-allowing-unwind put-up-native-simple-dialog (native-simple-dialog-state)
  (protected-let*
      ((ok-string
	 (text-string-per-button-string-spec
	   (ok-text-string? native-simple-dialog-state)
	   'ok)
	 (reclaim-text-string ok-string))
       (cancel-string
	 (text-string-per-button-string-spec
	   (cancel-text-string? native-simple-dialog-state)
	   'cancel)
	 (reclaim-text-string cancel-string))
       (additional-string
	 (text-string-per-button-string-spec
	   (additional-button-text-string? native-simple-dialog-state)
	   nil)
	 (reclaim-text-string additional-string))
       (message-string
	 (copy-text-string-for-native-word-wrap
	   (dialog-message-text-string native-simple-dialog-state))
	 (reclaim-text-string message-string)))
    (post-simple-dialog current-workstation-window
			(dialog-handle native-simple-dialog-state)
			message-string
			ok-string cancel-string additional-string
			(which-to-make-default-button? native-simple-dialog-state))))

;; The above (and lower-level functions) must be fixed to deal with null OK and
;; null Cancel case!



(defun check-dialog-handle-in-current-event (native-simple-dialog-state workstation-event)
  (let* ((current-dialog-handle (dialog-handle native-simple-dialog-state))
         (event-detail (workstation-event-detail workstation-event))
         (handle-from-event (getf event-detail 'dialog-handle)))

    (cond
      ((not (eql current-dialog-handle handle-from-event))
       (dwarn "~%The current dialog's handle (~d) doesn't correspond to the handle (~d) in this event.~%"
              current-dialog-handle
              handle-from-event)
       nil)
      (t t))))


(define-event-handler ok-in-simple-dialog-state
    (mouse-pointer
      (native-simple-dialog-state workstation-context-specifics))
  (when (check-dialog-handle-in-current-event
          native-simple-dialog-state current-workstation-event)
    (return-from-current-workstation-context 'native-simple-dialog)
    (when (ok-function? native-simple-dialog-state)
      (apply (ok-function? native-simple-dialog-state)
             (ok-function-arglist? native-simple-dialog-state)))))

(define-event-handler cancel-in-simple-dialog-state
    (mouse-pointer
      (native-simple-dialog-state workstation-context-specifics))
  (when (check-dialog-handle-in-current-event
          native-simple-dialog-state current-workstation-event)
  (return-from-current-workstation-context 'native-simple-dialog)
  (when (cancel-function? native-simple-dialog-state)
    (apply (cancel-function? native-simple-dialog-state)
           (cancel-function-arglist? native-simple-dialog-state)))))

(define-event-handler additional-in-simple-dialog-state
    (mouse-pointer
      (native-simple-dialog-state workstation-context-specifics))
  (when (check-dialog-handle-in-current-event
          native-simple-dialog-state current-workstation-event)
    (return-from-current-workstation-context 'native-simple-dialog)
    (when (additional-button-function? native-simple-dialog-state)
      (apply (additional-button-function? native-simple-dialog-state)
             (additional-button-arglist? native-simple-dialog-state)))))

(def-structure-method valid-workstation-context-p (native-simple-dialog-state)
  (and (funcall-superior-method native-simple-dialog-state)
       ;; anything to check?
       ))

(def-structure-method clean-up-workstation-context (native-simple-dialog-state)
  ;; There might be more to clean up.  Look at other
  ;; state-variables. -dkuznick,  1/19/06 
  (reclaim-text-string (dialog-message-text-string native-simple-dialog-state))
  (funcall-superior-method native-simple-dialog-state))


;;; `Enter-dialog' starts a simple dialog in one of two ways:
;;;
;;;  (1) as a native (Win32) dialog, or
;;;
;;;  (2) as G2 dialog box (using a G2 workspace, G2 buttons, etc.)
;;;
;;; If the window this is for is capable of handling this dialog natively, and
;;; desires to do so, and additional-block-to-display-below-message? is null,
;;; then we have case (1), i.e., a native dialog. In this case, x-in-window?,
;;; y-in-window?, make-strictly-modal?, and
;;; additional-block-to-display-below-message? are ignored.  Otherwise, case (2)
;;; applies.
;;;
;;; In case (1) this launches a native simple dialog and runs a
;;; native-simple-dialog workstation context.
;;;
;;; In case (2) this puts up a dialog box at the center of the pane, and runs a
;;; dialog workstation context. (It does not move the mouse.)  This puts the
;;; dialog workspace on a newly created image plane in the current workstation's
;;; detail pane.  Then it enters a dialog in the current workstation.  This
;;; expects to be executed in a for-workstation context.

;;; If ok-text-string? is nil, the string "OK" (or a localized replacement) will
;;; be used.  If ok-text-string? is the symbol NONE, then no OK button will
;;; appear.  Otherwise, ok-text-string? should be a text string to be used as
;;; the label of the OK button.

;;; If cancel-text-string? is nil, the string "Cancel" (or a localized
;;; replacement) will be used.  If cancel-text-string? is the symbol NONE, then
;;; no CANCEL button will appear.  Otherwise, cancel-text-string? should be a
;;; text string to be used as the label of the CANCEL button.

;;; If x-in-window? is specified, the y-in-window? must also be specified.
;;; These are presumed to be the location of the mouse.  If they are
;;; unspecified, the dialog workspace is placed at the center of the pane.  Even
;;; if they are specified, the placement of the dialog workspace is constrained
;;; so that it always fits within the pane and, in so much as that constraint
;;; permits, so that the mouse is positioned at the center of the ok button.

;;; All string arguments (i.e., the message and labels) become the property of
;;; this function and are subject to eventual reclamation.

;;; Additional-button-text-string?, additional-button-function?,
;;; additional-button-arglist? can be used to add a third button for the
;;; occasions where that is necessary.  For example, this could be used for
;;; the common yes/no/cancel variety of dialog.
;;;
;;; These args are used in just the same way as ok-text-string?, ok-function?,
;;; and ok-function-arglist?, respectively, with the exception that the first of
;;; these args, the text string arg, must be specified non-nil if ok-function?
;;; is non-nil, since this function has no particular guess as to what the
;;; default should be.  Also, a null value for Additional-button-text-string?,
;;; as well as the value NONE, indicates that no such button should appear.
;;;
;;; When there are only two buttons, the OK choice is to the right of the CANCEL
;;; choice.  When there is an additional button, it sits in-between the OK and
;;; CANCEL choices.
;;;
;;; Which-to-make-default-button? may be OK, nil (the default, meaning OK),
;;; CANCEL, ADDITIONAL, or NONE.  If NONE, all of the buttons will be generic
;;; action buttons; otherwise, the corresponding button will use the class
;;; default-action-button, and will be the button chosen when the user types
;;; Enter or Return.  In 4.0 Beta Phase 2 we will have a distinctive icon for
;;; default action buttons.  Note that prior to this version, the OK button was
;;; always made to be the default action button.
;;;
;;; Center-ok-button-over-mouse?, if true, makes the dialog appear under the
;;; mouse, such that the mouse is right in the center of the OK button, except
;;; to the extent that it shifts away in order to fit the dialog completely in
;;; the pane at full scale.  This is considered not-great anymore.  Now that we
;;; have distinctive icons for the default button (which needn't be the OK
;;; button anymore either), we want to do a more standard thing and put the
;;; dialog in the center of the screen at normalized scale.  [Should we scale
;;; the dialog to fit in the pane like we do with menus?]  It does this if
;;; center-ok-button-over-mouse? is false, the default.
;;;
;;; Regardless of the placement, the image plane showing the dialog workspace
;;; has a custom "dialog frame style".  It appears to have a nicer border than
;;; our traditional image plane frame style, and much resembles the Mac in this
;;; regard.

;;; The argument make-strictly-modal? should be specified true if this dialog is
;;; to be strictly modal.  Note that when this is true, new contexts not
;;; launched from this context are not to be entered.  [However, this is to some
;;; extent voluntary at this point; at least the change-mode command is disabled
;;; by such voluntarism. (MHD 3/28/97)]

;;; The argument additional-block-to-display-below-message? is a block to add to
;;; the workspace below the main message text box.  This will be centered below
;;; the main message text box.  When the dialog workspace is deleted, it will
;;; also be deleted.

;;; Internationalization:  Any text strings that are passed in to this function
;;; must have been localized by the caller (i.e. dialog-message-text-string,
;;; ok-text-string?, cancel-text-string?, or additional-button-text-string?).
;;; The default labels are localized here by the subroutine make-dialog-action-button.

;;; Note that the arglists are copied and reclaimed using
;;; copy-slot-value-list and reclaim-slot-value-list. If this
;;; is not sufficient (for example, if the arguments include frame
;;; serial numbers), the copying and reclamation must be special-cased
;;; in reclaim-button-action-arglist and in wrap-action-function, as
;;; has been done for delete-frame-after-checking-serial-number
;;; and allow-continuation-of-class-selection-upon-confirmation
;;; -alatto, 4/13/99

(defun enter-dialog
    (dialog-message-text-string
      ok-text-string? cancel-text-string?
      ok-function? ok-function-arglist?
      cancel-function? cancel-function-arglist?
      &optional x-in-window? y-in-window?
      additional-button-text-string? additional-button-function?
      additional-button-arglist?
      which-to-make-default-button? center-ok-button-over-mouse?
      make-strictly-modal?
      additional-block-to-display-below-message?)
  (if (and (null additional-block-to-display-below-message?)
	   (native-simple-dialogs-p current-workstation-window))
      (let* ((dialog-handle (allocate-native-simple-dialog-handle))
             (native-simple-dialog-state
               (make-native-simple-dialog-state
                 dialog-handle
                 (if simple-dialog-fill-text-p
		     (fill-text-for-native-dialog dialog-message-text-string)
		     dialog-message-text-string)
                 ok-text-string?
                 ok-function? ok-function-arglist?
                 cancel-text-string? cancel-function? cancel-function-arglist?
                 additional-button-text-string? additional-button-function?
                 additional-button-arglist?
                 which-to-make-default-button?)))
        (put-up-native-simple-dialog native-simple-dialog-state)
        (enter-context-in-current-workstation
          'native-simple-dialog
          native-simple-dialog-state
          make-strictly-modal?))
      (let* ((buttons
               (make-buttons-for-dialog
                 ok-text-string?
                 ok-function? ok-function-arglist?
                 cancel-text-string? cancel-function? cancel-function-arglist?
                 additional-button-text-string? additional-button-function?
                 additional-button-arglist?
                 which-to-make-default-button?))
             (dialog-message                ; "make-dialog-message"?
               (make-button-label dialog-message-text-string nil))
             (workspace
               (make-workspace 'temporary-workspace nil dialog-message 10)))
        (when additional-block-to-display-below-message?
          (add-to-workspace
            additional-block-to-display-below-message? workspace
            ;; left edge position changed today; see note! (MHD 2/1/05)
            (halfw
              (-w (+w (left-edge-of-block dialog-message)
                      (right-edge-of-block dialog-message))
                  (width-of-block additional-block-to-display-below-message?)))
            (+w (bottom-edge-of-block dialog-message) 10)))
        (arrange-dialog-workspace
          workspace
          (or additional-block-to-display-below-message?
              dialog-message)
          buttons)
        (let* ((image-plane
                 (put-up-dialog-image-plane
                   workspace x-in-window? y-in-window?
                   (if center-ok-button-over-mouse?
                       (loop for button in buttons
                             when (eq (get-primary-name-for-frame-if-any button)
                                      'ok)
                               return button))))
               (dialog-state (make-dialog-state workspace image-plane)))
          (reclaim-gensym-list buttons)
          (enter-context-in-current-workstation
            'dialog dialog-state make-strictly-modal?)))))

;; Note: the "additional block" was previously specified to be left-aligned
;; under the message.  But that was ugly in the debugger dialog, since the
;; buttons would then typically be centered under it.  So you'd end up with
;; unused whitespace on the left side, over the row of buttons on the bottom
;; centered under this block.  Since the debugger dialog was the only caller, I
;; changed the spec to have this be centered instead. (MHD 2/1/05)



(defun make-buttons-for-dialog
    (ok-text-string?
      ok-function? ok-function-arglist?
      cancel-text-string? cancel-function? cancel-function-arglist?
      additional-button-text-string? additional-button-function?
      additional-button-function-arglist?
      which-to-make-default-button?)
  (loop with default-type = (or which-to-make-default-button? 'ok)
        for type in '(ok additional cancel) ; Note: this is the partial
                                            ;   ordering we desire
        as required? = (case type
                         (additional
                          (and additional-button-text-string?
                               (not (eq additional-button-text-string?
                                        'none))))
                         (ok
                          (if ok-text-string?
                              (not (eq ok-text-string?
                                       'none))
                              t))
                         (cancel
                          (if cancel-text-string?
                              (not (eq cancel-text-string?
                                       'none))
                              t)))
        as default-case? = (eq type default-type)
        as string?
          = (case type
              (ok ok-text-string?)
              (cancel cancel-text-string?)
              (t (or additional-button-text-string? nil)))
        as function?
          = (case type
              (ok ok-function?)                ; can't really be nil!
              (cancel
               (or cancel-function?
                   (symbol-function 'cancel-button-action-in-dialog-state)))
              (t additional-button-function?))
        as arglist?
          = (case type
              (ok ok-function-arglist?)
              (cancel cancel-function-arglist?)
              (t additional-button-function-arglist?))
        as button?
           = (if required?
                 (make-dialog-action-button
                   type default-case?
                   string? function? arglist?
                   (and (eq type 'cancel) ; kludge!
                        (null cancel-function?))))
        when button?
          collect button? using gensym-cons))


(def-global-property-name standard-dialog-button-label-string)

(loop for (label string)
      in '((ok "OK") (cancel "Cancel") (apply "Apply")
           (reset "Reset") (yes "Yes") (no "No")
           ;; etc.!
           )
      do (register-button-label-for-internationalization label)
         (setf (standard-dialog-button-label-string label) string))



(defun get-dialog-label-text-string (label-type)
  (or (let ((string?
              (with-localization-purpose 'button-label
                (with-localization-domain 'default
                  ;; n.b. the domain should be set in the appropriate caller
                  ;; of this function where it knows what kind of thing
                  ;; this button is going to be part of.  There is no default
                  ;; domain now (1/98) and this usage just makes the use
                  ;; of the translation code safe for use with callers
                  ;; that aren't internationalized.
                  (or (translation-for-symbol? label-type)
                      (standard-dialog-button-label-string label-type))))))
        (if string? (copy-text-string string?)))
      (copy-text-string-with-case-conversion
        (symbol-name-text-string label-type)
        :first)))




(defun make-dialog-action-button
    (type default-case? string? function? arglist? &optional dont-wrap-function?)
  (let ((wrapped-action-function (symbol-function 'wrapped-action-function))
        (button
          (make-button
            (if default-case? 'default-action-button 'generic-action-button)
            (or string? (get-dialog-label-text-string type))
            type
            t)))
    (setf (button-action? button)
          (if dont-wrap-function?
              function?
              wrapped-action-function))
    (setf (button-action-data? button)
          (if dont-wrap-function?
              arglist?
              (slot-value-list function? arglist?)))
    (set-active button)  ; see note (MHD 1/26/95)
    button))

;; The set-active had been put here with the comment "just to get highlighting
;; to work!! (MHD 11/10/88)" -- It would seem to not be needed now that we pass
;; in "for-use-by-system?"  = true, which is new.  But not ready to chance that
;; -- there could be random tests for active-p that would need to be dealt with
;; first.  (MHD 1/26/95)



(defun make-button-to-update-virtual-attributes-table (table block timestamp)
  (let ((button (make-button
                  'generic-action-button
                  (tformat-text-string "Update this table")
                  nil
                  t)))
    (setf (button-action? button) 'update-virtual-attributes-table)
    (setf (button-action-data? button)
          (slot-value-list table
                           (slot-value-list (copy-frame-serial-number
                                              (frame-serial-number table))
                                            block
                                            (copy-frame-serial-number
                                              (frame-serial-number block))
                                            timestamp button)))
    (set-active button)  ; see note (MHD 1/26/95)
    button))


;;; `Put-up-dialog-image-plane' ... returns the resulting image plane.

(defun put-up-dialog-image-plane
    (workspace x-in-window? y-in-window? button-to-center-over?)
  (let* ((frame-description-reference
           (lookup-frame-description-reference-of-frame-style
             'dialog-workspace-frame-style
             'default-workspace-frame-style))
         (image-plane
           (cond
             (button-to-center-over?
              (let* ((image-plane
                       (get-available-image-plane
                         current-workstation-detail-pane
                         frame-description-reference
                         nil))
                     (center-x
                       (halfw
                         (+w (left-edge-of-block button-to-center-over?)
                             (right-edge-of-block button-to-center-over?))))
                     (center-y
                       (halfw
                         (+w (top-edge-of-block button-to-center-over?)
                             (bottom-edge-of-block button-to-center-over?))))
                     (x-in-window
                       (or x-in-window?
                           (halfr
                             (+r (left-edge-of-pane-in-window image-plane)
                                 (right-edge-of-pane-in-window image-plane)))))
                     (y-in-window
                       (or y-in-window?
                           (halfr
                             (+r (top-edge-of-pane-in-window image-plane)
                                 (bottom-edge-of-pane-in-window image-plane)))))
                     (default-x-scale (get-default-image-x-scale image-plane))
                     (default-y-scale (get-default-image-y-scale image-plane)))
                (put-image-on-image-plane
                  image-plane
                  workspace
                  default-x-scale default-y-scale
                  nil nil
                  center-x center-y
                  (maxr (+r (left-edge-of-pane-in-window image-plane)
                            (delta-x-in-window
                              (-w center-x (left-edge-of-block workspace))
                              default-x-scale))
                        (minr (-r (right-edge-of-pane-in-window image-plane)
                                  (delta-x-in-window
                                    (-w (right-edge-of-block workspace) center-x)
                                    default-x-scale))
                              x-in-window))
                  (maxr (+r (top-edge-of-pane-in-window image-plane)
                            (delta-y-in-window
                              (-w center-y (top-edge-of-block workspace))
                              default-y-scale))
                        (minr (-r (bottom-edge-of-pane-in-window image-plane)
                                  (delta-y-in-window
                                    (-w (bottom-edge-of-block workspace) center-y)
                                    default-y-scale))
                              y-in-window)))
                image-plane))
             (t
              ;; puts up an image plane at normalized full scale at the center
              ;; of the pane, and returns the image plane:
              (put-workspace-on-pane
                workspace current-workstation-detail-pane
                nil nil nil
                :frame-description-reference frame-description-reference)))))
    ;; (change-color-of-workspace workspace nil 'extra-light-gray nil) ; ??
    image-plane
    ))


(defparameter vertical-fine-positioning-for-default-action-button -3)


;;; `Arrange-dialog-workspace' ... called after dialog message has been added to
;;; workspace, with workspace "shrink-wrapped" around it.  This expects buttons
;;; to be in their appropriate order (e.g., OK before Cancel button in the list).

(defun arrange-dialog-workspace
    (workspace block-above-buttons buttons-in-order)
  ;; right-justified arrangement:   (similar to Mac)
  (loop with layout-policy = 'motif ; programmer's choice: MOTIF or MAC
        with minimum-interbutton-spacing = 10
        with right-edge-of-message = (right-edge-of-block block-above-buttons)
        ; with left-edge-of-message = (right-edge-of-block block-above-buttons)
        with number = (length buttons-in-order)
        with button-total-width
          = (loop for b in buttons-in-order sum (width-of-block b))
        with buttons-in-reverse-order
          = (nreverse (copy-list-using-gensym-conses buttons-in-order))
        as previous-button? = nil then button
        for button in buttons-in-reverse-order
        as i from 0
        as left-edge
           first (case layout-policy
                   (mac
                    (-w right-edge-of-message (width-of-block button)))
                   (motif
                    (-w (maxw (+w (vertical-midline-of-block block-above-buttons)
                                  (halfw button-total-width)
                                  (*w (halfw number) minimum-interbutton-spacing))
                              right-edge-of-message)
                        (width-of-block button))))
           then (-w left-edge
                    (maxw minimum-interbutton-spacing
                          (case layout-policy
                            (mac 0)
                            (motif
                             ;; WRONG -- fix later!
                             0)))
                    (width-of-block button))
        as top-edge
           = (+w (+w (bottom-edge-of-block block-above-buttons)
                     minimum-interbutton-spacing)
                 (if (frame-of-class-p button 'default-action-button)
                     vertical-fine-positioning-for-default-action-button
                     0))
        do (add-to-workspace button workspace left-edge top-edge)
        finally (reclaim-gensym-list buttons-in-reverse-order)))

;; Note: to move this towards a Motif look and feel, center the buttons, and
;; equally distribute them along the bottom.



;;; `Dialog-button-arranges-earlier-p' can be used as a sort-lessp predicate in
;;; order to arrange dialog buttons in a standard ordering.
;;;
;;; It uses the (primary) name of each button in order to determine its "type".
;;;
;;; Currently, it only knows to put OK type buttons before CANCEL type buttons.
;;; If it doesn't know about a pair of buttons' types, or if either lacks a
;;; type, it returns true, i.e., it leaves their order unchanged when used as a
;;; sort predicate.

(defun dialog-button-arranges-earlier-p (button-1 button-2)
  (let* ((ordering '(ok cancel))                ; needs to be expanded!
         (position-1?
           (position
             (get-primary-name-for-frame-if-any button-1)
             ordering))
         (position-2?
           (position
             (get-primary-name-for-frame-if-any button-2)
             ordering)))
    (if (or (null position-2?)
            (null position-1?))
        t
        (<f position-1? position-2?))))

;; Not written for speed!


;; To do: solve problem of click-ahead, and maybe type-ahead, by either flushing
;; queue of events here, or recording the current time, and not responding to
;; clicks (and maybe keystrokes) that were typed before the current time in the
;; event handler!  See if this can be generalize -- FMW? (MHD 1/22/95)
;;
;; I'm now pretty sure you can't easily solve this without putting the test into
;; the dialog.  In particular, just flushing the event queue can't work because
;; the queue could be sitting on the local event queue, and that doesn't get
;; up-to-date until we poll, or it could be sitting on the Telewindows side, which
;; we really can't do much about getting.
;;
;; Comparing times of events is difficult because there's no defined origin for
;; event times.  You can only compare two of them, and you can get an absolete
;; time difference between time (granularity of milliseconds).
;;
;; Here is an approach which should work provided that there is an event that
;; coincides exactly with entering the dialog context:
;;
;; call T(E) the event time of some event E.  Record the event that started the
;; dialog E1.  Do work that takes time TIMESPAN amount of time, as an event time
;; interval, to put up the dialog.  Record E1 and TIMESPAN as state variables.
;; Now, event handlers can reject any event E2 such that
;;
;;    event-time-differenct(T(E2), T(E1)) < TIMESPAN
;;
;; This will just work for dialogs.  If it wanted to be generalized for other
;; kinds of workstation event handline, especially kinds that aren't explicitly
;; started by pushing a workstation context, it would have to be supported at
;; the workstation level.  That should be considered in due time.  (MHD 1/23/95)


(define-event-handler mouse-down-on-button-in-dialog-state
    (mouse-pointer
      (dialog-state workstation-context-specifics)
      image-plane
      button)
  (if (eq image-plane (dialog-image-plane dialog-state))
      (enter-button-down-context button image-plane)
      (mouse-down-on-other-in-dialog-state mouse-pointer)))

(define-event-handler mouse-down-on-workspace-in-dialog-state
    (mouse-pointer
      (dialog-state workstation-context-specifics)
      x-in-window
      y-in-window
      image-plane
      workspace)
  (if (eq workspace (dialog-workspace dialog-state))
      (enter-image-plane-dragging-context
              image-plane
              (-w x-in-window (left-edge-of-image-in-window image-plane))
              (-w y-in-window (top-edge-of-image-in-window image-plane))
              t)
      (mouse-down-on-other-in-dialog-state mouse-pointer)))

(define-event-handler mouse-down-on-close-box-widget-in-dialog-state
    (mouse-pointer
      (dialog-state workstation-context-specifics)
      x-in-window
      y-in-window
      image-plane
      workspace)
  (if (eq workspace (dialog-workspace dialog-state))
      (enter-close-box-widget-pending-context workspace image-plane)
      (mouse-down-on-other-in-dialog-state mouse-pointer)))


(define-workstation-context widget-pending
    (workstation-context-with-selection-focus)
  :selection-style top-level-with-selection-focus-is-selection-style
  :parent nil
  :modal t
  :constructor (make-widget-pending-state
                 (block-with-selection-focus-of-workstation-context
                   image-plane-with-selection-focus-of-workstation-context
                   reference-number-of-image-plane))
  :state-variables (specific-image-plane-for-widget-pending ;   serial-number-..."?
                     (widget-pending-in-pending-state? t))
  :keymap ((<mouse-up> mouse-up-in-close-box-widget-pending-state)
           (<mouse-motion> mouse-motion-in-close-box-widget-pending-state)
           (<standard-abort-keys> abort-workstation-context)))

(defun enter-close-box-widget-pending-context (workspace specific-image-plane)
  (let ((workstation-context-specifics
          (make-widget-pending-state
            workspace specific-image-plane
            (serial-number-of-image-plane specific-image-plane))))
    (enter-context-in-current-workstation
      'widget-pending workstation-context-specifics)
    (add-mouse-pointer-to-guardians-of-workstation-context
      (mouse-pointer-of-latest-event current-workstation)
      workstation-context-specifics)
    (change-close-box-situation specific-image-plane 'pending)))



;;; `Change-close-box-situation' updates the state variable in image-plane
;;; to situation, one of the symbols NORMAL, PENDING, or NA, and then repaints the
;;; close box.

(defun change-close-box-situation (image-plane situation)
  #+development
  (test-assertion (member situation '(normal pending na)))
  (unless (eq (image-plane-close-box-situation image-plane)
              (setf (image-plane-close-box-situation image-plane) situation))
    (with-raw-window-transform-and-draw-area
        ((gensym-window-for-image-plane image-plane))
      (on-image-plane (image-plane)
        (project-frame
          'drawing-close-box
          (frame-description-of-frame-description-reference
            (frame-description-reference-of-image-plane image-plane))
          (left-edge-of-image-in-window image-plane)
          (top-edge-of-image-in-window image-plane)
          (right-edge-of-image-in-window image-plane)
          (top-edge-of-workspace-area-in-window image-plane)
          nil)))))


(define-event-handler mouse-down-on-other-in-dialog-state
    ((dialog-state workstation-context-specifics))
  (let ((dialog-image-plane (dialog-image-plane dialog-state)))
    (with-image-plane-transform (dialog-image-plane)
      (let* ((message-text?
              (loop for subblock being each subblock
                    of (dialog-workspace dialog-state)
                    when (frame-of-class-p subblock 'text-box)
                      return subblock))
             ;; Center the mouse at the bottom of the dialogs' message text.
             (x-offset (halfr
                         (-r (right-edge-of-image-in-window
                               dialog-image-plane)
                             (left-edge-of-image-in-window
                               dialog-image-plane))))
             (y-offset (if message-text?
                           (-r (y-in-window (bottom-edge-of-block message-text?))
                               (top-edge-of-image-in-window dialog-image-plane))
                         0)))
        (raise-image-plane-to-top dialog-image-plane)
        (enter-image-plane-dragging-context
          dialog-image-plane x-offset y-offset t)))))


(define-event-handler mouse-down-in-dialog-state
    (mouse-pointer
      x-in-window
      y-in-window
      (dialog-state workstation-context-specifics)
      &optional
      (image-plane? image-plane nil))
  (let ((dialog-image-plane (dialog-image-plane dialog-state)))
    (cond

      ;; Mouse-down on the dialog: select a dialog button or drag.
      ((eq image-plane? dialog-image-plane)
       (with-mouse-pointer-bindings
           (x-in-workspace
             y-in-workspace
             &optional (button? button nil)) mouse-pointer
         (cond

           (button?
            (enter-button-down-context button? image-plane?))

           ;; If not over a button, just drag the image plane.
           (t
            (enter-image-plane-dragging-context
              image-plane?
              (-w x-in-window (left-edge-of-image-in-window image-plane?))
              (-w y-in-window (top-edge-of-image-in-window image-plane?))
              t)))))

      ;; Mouse-down elsewhere: warp the dialog to the mouse and drag.
      (t
       (with-image-plane-transform (dialog-image-plane)
         (let* ((message-text?
                 (loop for subblock being each subblock
                       of (dialog-workspace dialog-state)
                       when (frame-of-class-p subblock 'text-box)
                         return subblock))
                ;; Center the mouse at the bottom of the dialogs' message text.
                (x-offset (halfr
                            (-r (right-edge-of-image-in-window
                                  dialog-image-plane)
                                (left-edge-of-image-in-window
                                  dialog-image-plane))))
                (y-offset (if message-text?
                              (-r (y-in-window (bottom-edge-of-block message-text?))
                                  (top-edge-of-image-in-window dialog-image-plane))
                            0)))
           (raise-image-plane-to-top dialog-image-plane)
           (enter-image-plane-dragging-context
             dialog-image-plane x-offset y-offset t)))))))


(defun find-button-in-dialog (workspace kind-of-button)
  (loop for subblock being each subblock of workspace
        when (if (memq kind-of-button '(nil default))
                 (frame-of-class-p subblock 'default-action-button)
                 (and (frame-of-class-p subblock 'generic-action-button)
                      (eq (name-or-names-for-frame subblock) kind-of-button)))
          return subblock))

(defun execute-dialog-button (dialog-state kind-of-button)
  (when (valid-block-in-workstation-context-p
          (dialog-workspace dialog-state)
          dialog-state)
    (let ((action-button? (find-button-in-dialog (dialog-workspace dialog-state) kind-of-button)))
      (when action-button?
        (highlight-or-unhighlight-button action-button? nil)
        (funcall-method 'click action-button?
                        (left-edge-of-block action-button?)
                        (top-edge-of-block action-button?))))))


(define-event-handler wrap-up-in-dialog-state
    ((dialog-state workstation-context-specifics))
  (execute-dialog-button dialog-state 'default))

(define-event-handler cancel-in-dialog-state
    ((dialog-state workstation-context-specifics))
  (execute-dialog-button dialog-state 'cancel))



;;;; Button Down State



;;; The variable `current-image-plane-for-button' is bound when handle-event,
;;; click, and drag methods for buttons are invoked.

(defvar current-image-plane-for-button)


(define-workstation-context button-down
    (workstation-context-with-selection-focus)
  :selection-style top-level-with-selection-focus-is-selection-style
  :parent nil
  :modal t
  :constructor (make-button-down-state
                 (block-with-selection-focus-of-workstation-context
                   image-plane-with-selection-focus-of-workstation-context
                   reference-number-of-image-plane))
  :state-variables (specific-image-plane                    ;   serial-number-..."?
                     (button-pending-in-button-down-state? t))
  :keymap ((<mouse-up> mouse-up-in-button-down-state)
           (<mouse-motion> mouse-motion-in-button-down-state)
           (<standard-abort-keys> abort-workstation-context)))


(defun enter-button-down-context (button specific-image-plane)
  (let ((workstation-context-specifics
         (make-button-down-state
           button specific-image-plane (serial-number-of-image-plane
                                         specific-image-plane))))
    (enter-context-in-current-workstation
      'button-down workstation-context-specifics)
    (add-mouse-pointer-to-guardians-of-workstation-context
      (mouse-pointer-of-latest-event current-workstation)
      workstation-context-specifics)
    (gensym-push button buttons-in-button-down-state)))

(def-structure-method clean-up-workstation-context (button-down-state)
  (setq buttons-in-button-down-state
        (delete-gensym-element
          (block-with-selection-focus-of-workstation-context button-down-state)
          buttons-in-button-down-state))
  (funcall-superior-method button-down-state))


(define-event-handler mouse-motion-in-button-down-state
    ((button block-of-selection-focus)
     (image-plane image-plane-of-selection-focus)
     (x x-in-workspace-of-selection-focus)
     (y y-in-workspace-of-selection-focus))
  (let ((current-image-plane-for-button image-plane))
    (frame-class-case button
      (slider
        (change-slider button x y))
      (button
        (when (or (runnable-p button)
                  (button-in-use-by-system-p button))
          (highlight-or-unhighlight-button
            button (not (in-block-p button x y))))))))

(define-event-handler mouse-motion-in-close-box-widget-pending-state
    (mouse-pointer
      (workspace block-of-selection-focus)
      (image-plane image-plane-of-selection-focus))
  (cond
    ((let ((spot? (find-spot-of-type mouse-pointer 'close-box-spot)))
       (and spot? (eq (frame-represented? spot?) workspace)))
     (change-close-box-situation image-plane 'pending))
    (t
     (change-close-box-situation image-plane 'normal))))


(define-event-handler mouse-up-in-button-down-state
    (mouse-pointer
      (button-down-state workstation-context-specifics)
      (button block-of-selection-focus)
      (image-plane image-plane-of-selection-focus)
      (x x-in-workspace-of-selection-focus)
      (y y-in-workspace-of-selection-focus))
  ;; Bring the button into synch.
  (mouse-motion-in-button-down-state mouse-pointer)
  (let ((button-name (get-primary-name-for-frame-if-any button))
        ;; Careful now, the return might eliminate the button!
        (frame-serial-number
          (copy-frame-serial-number (frame-reference-number-of-workstation-context button-down-state))))
    (if (in-block-p button x y)
        (return-from-current-workstation-context 'button-down :ok button-name)
        (abort-current-workstation-context 'button-down))
    (let ((current-image-plane-for-button image-plane))
      (unless (frame-has-been-reprocessed-p button frame-serial-number)
        (funcall-method 'click button x y)))
    (reclaim-frame-serial-number frame-serial-number)))

;; That funcall-method 'click should be in the continuation!
;; The click method is a no-op on some buttons, go figure.


;; Consider having a global unwind-protect that takes all buttons out of the
;; list buttons-in-button-down-state.  Also, consider having that done if
;; necessary in delete-frame or by a cleanup method!  Also, note the similarity
;; buttons-in-button-down-state.


(define-event-handler mouse-up-in-close-box-widget-pending-state
    (mouse-pointer
      (workspace block-of-selection-focus)
      (image-plane image-plane-of-selection-focus))
  (let* ((spot? (find-spot-of-type mouse-pointer 'close-box-spot))
         (delete-p (and spot? (eq (frame-represented? spot?) workspace))))
    (return-from-current-workstation-context 'widget-pending)
    (cond
      (delete-p (delete-image-plane image-plane))
      (t (change-close-box-situation image-plane 'normal)))))







;;;; Button Methods for Handling Events




;;; The `click' method for a button (or a type-in-box!) is invoked when the
;;; user releases the mouse "near" the button.  "Near" means the action button
;;; was found by find-object- near-mouse (see RUN) when the system was running
;;; and not paused.

;;; Currently the click method is invoked in dialog state (in response to a return),
;;; in button-down state.

;;; These can be called when the button is inactive or not "frame-ok-p".

(def-generic-method click (block x-in-workspace y-in-workspace))

;; I don't think that the highlighting or the mouse targeting should be
;; in this method.  - ben 9/30/94

;; To do: unfortunately, the button doesn't highlight when you hit return.  This
;; seems to be a bug, as code at the click handler does something with the
;; highlight: turns it off.  Needs an investigation!  This is sad, for example,
;; if you hit return and it takes a long time to do it, say to delete a huge
;; workspace hierarchy, since you don't get to see that the button you chose is
;; operating.  Compare with clicking on that button.  See if this can be done
;; when the click methods are better folded in with Ben's design.  (MHD 1/26/95)

;; Note: the frame-ok-p check was missing in 3.0, which apparently did not bomb
;; out.  It meant that you could click the check box on and off even when it was
;; incomplete, which should be considered a bug.  It behaved the way it does now
;; in 2.1.  The change that made active-p not be the same as frame-ok-p came
;; just in time for 3.0.  (MHD 3/19/93)

;;; The following `click' method returns whether an integer count of
;;; rules scheduled as a result of this click, or nil indicating none.

(def-class-method click (generic-action-button x-in-workspace y-in-workspace)
  (highlight-or-unhighlight-button generic-action-button t)
  (cond
    ;; 1. Release isn't over the button at all.
    ((not (in-block-p generic-action-button x-in-workspace y-in-workspace))
     ;; do nothing
     nil)

    ;; 2. The button is built in, and using this mechinism.
    ((button-action? generic-action-button)
     (apply (button-action? generic-action-button)
            (button-action-data? generic-action-button))
     nil)

    ;; 3. The button is using an embedded rule.
    ((embedded-rule? generic-action-button)
     (fire-action-button generic-action-button current-workstation-window))
    ;; 4. Otherwise it was:
    ;;  a) a dysfunctional embedded rule  (became so while the mouse was down?).
    ;;  b) none of the above
    ;; both cases happen in practice.  In case b the button-down-state
    ;; may be invoked with a continuation, that state returns enough state
    ;; to do useful things.
    (t
     ;; Do nothing.
     nil)))


(defun-simple fire-action-button (generic-action-button instigating-client)
  (let ((embedded-rule? (embedded-rule? generic-action-button))
        (window-instigating-this-rule-instance? instigating-client))
    (cond
      ((and embedded-rule?
            (or (runnable-p generic-action-button)
                (button-in-use-by-system-p generic-action-button)))
       (invoke-old-or-new-rule embedded-rule? nil nil nil 'action-button))
      (t
       nil))))

;; Should *current-computation-frame* be bound around invoke-old-or-new-rule?


(def-class-method click (check-box x-in-workspace y-in-workspace)
  (when (or (runnable-p check-box)
            (button-in-use-by-system-p check-box))
    (highlight-or-unhighlight-button check-box t)
    (when (in-block-p check-box x-in-workspace y-in-workspace)
      (change-on/off-switch check-box 'toggle)
      (set-variable-per-button-if-appropriate check-box nil))))



(def-class-method click (radio-button x-in-workspace y-in-workspace)
  (when (runnable-p radio-button)
    (highlight-or-unhighlight-button radio-button t)
    (when (in-block-p radio-button x-in-workspace y-in-workspace)
      (change-on/off-switch radio-button t)
      (loop with variable-designation?
            = (associated-variable-designation? radio-button)
            for x being each class-instance of 'radio-button
            when (and (not (eq x radio-button))
                      (equal (associated-variable-designation? x)
                             variable-designation?)        ; DESIGNATION-EQUAL!!!
                      ;; if there subclasses, consider requiring
                      ;;    classes to be strictly the same?
                      )
              do (change-on/off-switch x nil))
      (set-variable-per-button-if-appropriate radio-button nil))))

;; Abstract the operation to test equality of designations (and/or constant
;; designations) and put that into COMPILE1.



(def-class-method click (type-in-box x-in-workspace y-in-workspace)
  (mouse-select-on-type-in-box type-in-box
                               current-image-plane-for-button ; Retch.
                               x-in-workspace y-in-workspace))




;;; `Get-type-of-slot-if-any-for-variable' ...  I have no idea what the original
;;; intent was (see jra 10/91 comment below), but this is now called from only
;;; one place: mouse-select-on-type-in-box, where it is an abstraction used in
;;; the call to enter-editing-context. The value that this returns controls two
;;; things: the grammar that is used for parsing the value as it is typed in
;;; and the choice of slot compiler.
;;;
;;; Note that for a type-in box it is never the case that a slot-compiler is
;;; going to be called since a check inside get-slot-value-compiler-for-
;;; current-edit-state-if-any forces that routine to return nil (rather than a
;;; slot-compiler) if the type-of-slot-being-edited (which this function sets)
;;; is different from the actual type on the slot being edited, which for
;;; type-in-box is the slot type-in-box-input-value which is of type read-
;;; only-attribute. That is of relatively little consequence here since only
;;; minimal processing is needed for these values and that can be handled by
;;; transformations associated with the rules for these categories.


(defun get-type-of-slot-if-any-for-variable (variable)
  (case (data-type-of-variable-or-parameter variable)
    (time-stamp                                ; (MHD 5/26/04)
     (frame-class-case variable
       ((integer-variable integer-parameter)
        '(type time-stamp))
       (t
         '(type time-stamp-optionally-with-subseconds))))
    (interval '(type interval))                ; (MHD 5/26/04)
    (truth-value '(type truth-value-constant))  ; ddm/mhd 5/27/97
    (symbol '(type symbol))
    (text
      ;; Later! '(type free text))      ; NEEDS WORK!
      '(type whole-string))                ; requires enclosing ""'s
;    (pure-number '(type pure-number))        ;  ML TO WRITE!
    (number '(type number))
    (integer '(type integer))
    (float '(type float))
;    (neutral-unit-of-measure '(type neutral-unit-of-measure))
;    (plural-unit-of-measure '(type plural-unit-of-measure))
    (t '(type read-only-attribute))))

;; Later, make these use the specific grammar!  Note that the processing
;; done by the slot compiler for attribute (in GRAMMAR2) is relied on for
;; getting the values expected by put-slot-value for the data types which
;; use attribute above.  For example, TRUE becomes
;;    (make-slot-constant-using-phrase-conses 1000 'truth-value)

;; Note that this was never finished!!!  If you want to use only true data
;; types, then the function type-specification-of-variable-or-parameter-value
;; fetches it.  If you want to allow so-called types like interval and
;; time-stamp to be passed through and affect the allowable grammar, then you
;; should go ahead and continue to use the slot directly, as above, but put in
;; handlers for these types.  -jra 10/9/91




(def-class-method click (slider x-in-workspace y-in-workspace)
  (when (runnable-p slider)
    (change-slider slider x-in-workspace y-in-workspace)
    (set-variable-per-button-if-appropriate slider nil)
    (update-slider-readout slider nil)))






;;; The function `Button-in-use-by-system-p' is true if the button is in use by
;;; the system.  If that is so, then things normally not done because the
;;; button is not active can be done anyway.

(defun button-in-use-by-system-p (button)
  (or (button-is-being-used-by-system-p button)
      (and (frame-of-class-p button 'generic-action-button) ; in by the system!
           (or (frame-of-class-p button 'icon-editor-button)
               (button-action? button)
;;               (name-or-names-for-frame button)
               ))))

;; Will have to change when buttons can have names!!
;; Buttons do have names now, so I took this clause out. -fmw, 1/10/94


;; Only used by the function below at present.  Clean up the reasons for this
;; in various system dialogs like operate-on-area, ok-cancel, etc.! (MHD 8/13/89)






;;;; Menu (Selection) Methods for Buttons



;;; The function `perform-button-action?' returns T if the button is active,
;;; which means that it should performs its action upon a mouse click, rather
;;; than the usual behavior of moving or posting its menu.

(defun perform-button-action? (button)
  (or system-is-running
      (or (runs-while-inactive-p button)
          (button-in-use-by-system-p button)
                                                            ; make just the first test be needed!
          (frame-of-class-p button 'arrow-button))))



;;;; Interfacing Buttons and Variables




;;; `Set-variable-per-button-if-appropriate' ... If activation-case? is
;;; non-nil, the value concluded is that of the value-on-activation? slot of
;;; the button, rather than that given by the "setting" of the button.

(defun set-variable-per-button-if-appropriate
    (non-action-button activation-case?)
  (let ((variable? nil)                                            ; variable? => (null frame?)
        (frame? nil)                                            ; frame? => (null variable?)
        (constant-attribute-value nil)
        (slot-name nil))
    (when (and (or (and (setq frame?
                              (associated-frame-for-button? non-action-button))
                        (setq slot-name
                              (associated-slot-name-for-button?
                                non-action-button))
                        (frame-has-not-been-reprocessed-p
                          frame?
                          (associated-frame-serial-number-for-button? frame?)))
                   (and (runnable-p non-action-button)
                        (setq variable?
                              (get-variable-for-button-if-any non-action-button))))
               (if activation-case?
                   (setq constant-attribute-value                        ; may get nil
                         (value-on-activation? non-action-button))
                   (frame-class-case non-action-button
                     (radio-button
                       (if (and (setq constant-attribute-value        ; has a value?
                                      (value-for-radio-button non-action-button))
                                (eq                ; on?
                                  (get-color-of-icon-region
                                    non-action-button 'on-indicator)
                                  'foreground))
                           t))
                     (check-box
                       (if (let ((on-value?
                                   (on-value-for-check-box non-action-button)))
                             (if on-value?
                                 (setq constant-attribute-value
                                       (if (eq        ; on?
                                             (get-color-of-icon-region
                                               non-action-button 'on-indicator)
                                             'foreground)
                                           on-value?
                                           (off-value-for-check-box non-action-button)))))
                           t))
                     (slider
                       (if (and
                             (minimum-value-for-slider non-action-button)
                             (maximum-value-for-slider non-action-button))
                           (with-temporary-gensym-float-creation
                               set-from-slider                ; required around
                                                            ;   put-current-value
                                                            ;   and read-or-write-
                                                            ;   slider
                             (if frame?
                                 (change-slot-value
                                   frame? slot-name
                                   (read-or-write-slider non-action-button nil))
                                 (let ((*current-computation-frame* non-action-button))
                                   (put-current-value
                                     variable?
                                     (read-or-write-slider non-action-button nil)
                                     'number 'never nil)))))
                       nil)
                     (type-in-box
                       (setq constant-attribute-value                        ; may get nil
                             (type-in-box-input-value non-action-button))))))

      (with-temporary-gensym-float-creation set-variable-per-button-if-appropriate
        (multiple-value-bind (cached-value expiration type)
            (convert-constant-attribute-value-to-cached-value
              constant-attribute-value)
          (if frame?                                ; I belive this case is not in use
              (change-slot-value                ;   yet. (MHD 2/28/91)
                frame? slot-name
                ;; maybe call this box-slot-value-if-necessary? review?
                ;; (MHD 2/28/91)
                (if (gensym-float-p cached-value)
                    (make-slot-value-float cached-value)
                    cached-value))
              (let ((*current-computation-frame* non-action-button))
                (put-current-value
                  variable? cached-value type expiration nil)

                ;; Now schedule a task to update the button according
                ;;   to the value of the variable in one second -- the
                ;;   value might have been the wrong type, e.g., or been
                ;;   rounded, e.g.    (This logic not in until today.
                ;;   (MHD 1/19/90))
                (with-current-scheduling (nil 2)
                  (scheduled-update-button non-action-button)))))))))

;; Review the use of the "cached" if and when the concept of a "cached value" goes
;; away and/or after the conversion to slot value floats as managed floats has been
;; completed.  (MHD 2/28/91)

(defun-void scheduled-update-button (button)
  (update-button button))

;; Scheduled-update-button is needed since update-button is not a
;; simple-function.  -jra 3/18/94




(defun get-variable-for-button-if-any (non-action-button)
  (let* ((constant-designation?
           (associated-variable-designation? non-action-button))
         (entity-evaluation?
           (if constant-designation?
               (let ((*current-computation-frame* non-action-button))
                 (evaluate-designation constant-designation? nil)))))
    (cond
      ;; could have nil, a temporary constant, or a frame
      ((null entity-evaluation?)
       nil)
      ((temporary-constant-p entity-evaluation?)
       (reclaim-temporary-constant entity-evaluation?)
       (write-warning-message
           1
         (tformat "~ND in ~NF does not designate a variable or a parameter."
                  constant-designation?
                  non-action-button))
       nil)
      ((variable-or-parameter-p entity-evaluation?)
       entity-evaluation?))))

;; Review warning message wording! (MHD 9/10/88)







;; This has been temporarily moved here just to make it compile!! (MHD 3/23/89)


;;; `Evaluate-user-menu-choice-condition' returns true if either user-menu-choice
;;; has no condition or if its condition evaluates true, that is to a truth
;;; value greater than the current default thruth threshold (as given by
;;; inference-engine-paramters).  Note that if the condition fails to return
;;; a value for any reason (e.g. needing the value of a variable in its
;;; expression), it is just the same as being false.  Note that the evaluation
;;; of the condition should not perturb the system; namely, it should not
;;; cause backward chaining.

;;; Entity is the selected object, i.e. what the user clicked on.  Soon, this
;;; argument will be changed to ITEM.  [A more precise discussion of this argument
;;; will be deferred until we better define selection, the notion of "the
;;; selected object", and what an "item" is.]

(defun evaluate-user-menu-choice-condition (user-menu-choice entity)
  (let ((expression-to-evaluate?
          (car (condition-for-using-user-menu-choice? user-menu-choice))))
    (when (null expression-to-evaluate?)
      (return-from evaluate-user-menu-choice-condition t))
    (let* ((cell-array? (cell-array user-menu-choice))
           (expression-cell?
             (when cell-array?
               (managed-svref (g2-cell-array-managed-array cell-array?) 0)))
           (argument-list (eval-list entity))
           (result? nil))
      (when expression-cell?
        (attempt-expression-cell-execution
          expression-cell? argument-list
          (may-refer-to-inactive-items-p user-menu-choice))
        (setq result? (get-expression-cell-cache cell-array? 0))
        (setq result? (and (evaluation-truth-value-p result?)
                           (evaluation-truth-value-is-true-p result?))))
      (reclaim-eval-cons argument-list)
      result?)))

(def-class-method expression-cell-updated
                  (user-menu-choice cell-array index old-cache? new-cache?)
  (declare (ignore user-menu-choice cell-array index old-cache? new-cache?))
  nil)

;; Consider adding tracing and breakpoints support both here and in action
;; buttons.  Right now the interface to that facility appears rather messy,
;; at first glance at least. For example, in order to use it get-new-value-
;; for-display must bind three special variables (saved-warning-level, saved-
;; tracing-level, and saved-breakpoint-level) and one local variable
;; (tracing-and-breakpoints) (!).









;;;; Highlighting Buttons




;;; ... There are several known names of regions in button icons that are
;;; handled specially for purposes of highlighting. ... The region `pending-
;;; indicator' is changed to background in the unhighlight case and to
;;; foreground when highlighting.  The region `details' is optionally present.
;;; If it is present, it is changed to foreground in the unhighlight case and
;;; to background when highlighting.

;; Note that `details' is only used for some icon editor button at present.
;; It was important to flip that region's colors in the case of those buttons
;; because the graphics were being erased when highlighting.  Note that there
;; is still a similar problem with action buttons with textual interior which
;; is bad in certain implementations: since the color of the text is not drawn
;; against a background of the pending indicator region, it appears in a false
;; color when that region is other than background.  In some implementations,
;; this false color is actually invisible.  In others, it is hard to read.  In
;; others, it is fine.  This should be fix!!! (MHD 10/31/89)


;;; Highlight-or-unhighlight-button ...

(defun highlight-or-unhighlight-button (button unhighlight-case?)
  ;; Ensure that the highlight/unhighlight pair is not merged together.
  (let ((flush-graphics-immediately? t))

    (frame-class-case button
      (slider
        nil)
      (type-in-box
        (highlight-or-unhighlight-text-box
          (get-type-in-text-box button) nil unhighlight-case?))
      ((generic-action-button on/off-switch)
       (let ((current-pending-indicator-color
               (get-color-of-icon-region
                 button 'pending-indicator)))
         (unless (eq current-pending-indicator-color
                     (if unhighlight-case?
                         'transparent
                         'foreground))
           (let ((current-drawing-transfer-mode :xor)
                 (pattern-in-unhighlight-case?
                   (if unhighlight-case?
                       (gensym-list
                         (or
                           (icon-has-region-p button 'pending-indicator) ; fix name!
                           '(pending-indicator .  transparent))))))
             (change-color-pattern-of-icon
               button nil
               (if unhighlight-case?
                   (if (icon-has-region-p button 'details)
                       (gensym-cons
                         '(details . foreground)
                     ;   '((pending-indicator . transparent) pbk
                         pattern-in-unhighlight-case?)
                       pattern-in-unhighlight-case?)
                   (if (icon-has-region-p button 'details)
                       '((pending-indicator . foreground)
                         (details . background))
                       '((pending-indicator . foreground)))))
             (when pattern-in-unhighlight-case?
               (reclaim-gensym-list pattern-in-unhighlight-case?)))))))))

;; Consider just highlighting using the default entity highlight method.

;; Consider implementing a new metacolor "background-opposite" to use as the
;; highlight color.






;;;; Creating Buttons





(defun make-button (class &optional label-text-string? name? for-use-by-system?
                          minimum-width-for-button? text-box-format-name?
                          do-not-reformat?)
  (let ((button (make-entity class)))
    (when for-use-by-system?
      (setf (button-is-being-used-by-system-p button) t))
    (when minimum-width-for-button?
      (change-slot-value
        button 'minimum-width-of-generic-action-button?
        minimum-width-for-button?))
    (when label-text-string?
      (setf (label-for-button button) (copy-text-string label-text-string?))
      (update-button-label button label-text-string? text-box-format-name? do-not-reformat?))
    (cond ((subclassp class 'slider)
           (let ((slider-needle (make-entity 'slider-needle)))
             (add-to-block
               slider-needle button
               ;; keep the slider needle's bottom aligned with the top edge of
               ;; the of the slider; the center of the slider needle starts out
               ;; aligned with the left edge of the slider:
               (-w (left-edge-of-block button) ; 0 here
                   (halfw (width-of-block slider-needle)))
               (-w (top-edge-of-block button)
                   (height-of-block slider-needle)))))
          ((subclassp class 'type-in-box)
           (let ((type-in-text-box
                   (make-free-text-box
                     (copy-constant-wide-string #w"****")        ; abstract away from ****!
                     'type-in-text-box)))
             (add-to-block type-in-text-box button 0 0)
             (set-edges-of-block button 0 0
                                 (right-edge-of-block type-in-text-box)
                                 (bottom-edge-of-block type-in-text-box))))
          (t nil))
    (when name?
      (change-slot-value
        button 'name-or-names-for-frame
        (slot-value-cons name? (name-or-names-for-frame button))))
    button))



;;;; Adding Buttons to Workspaces



;;; Set-up-bounding-dialog-ws creates rows of button according as specified
;;; rows-of-button-specs and adds them to workspace using add-to-workspace
;;; without updating their images.

;;; Rows-of-button-specs should be a gensym list of rows.  Each row should be a
;;; gensym list of button specs.  Each button spec should be either a symbol or
;;; a list whose first element is a symbol, whose second element is a either a
;;; string, if that string is to be its label instead of using the symbol name
;;; of the symbol, or nil, and, whose third element is optional and non-nil if
;;; it is to be the "default" button.  When the symbol name is used as the
;;; button's label, it is initially capitalized and all hyphens are removed;
;;; e.g. sample-name becomes "Sample name".

;;; The symbol provided by the button spec is always used as the button's name.
;;; Buttons are spaced out with 10 units between each one.  The conses in
;;; rows-of-button-specs are not altered or reclaimed by this function; they
;;; may therefore be constant list structure, or the caller may reclaim them
;;; after this function returns.  The analogous convention is true of any
;;; strings in any of the button specs.

(defun set-up-bounding-dialog-ws
    (rows-of-button-specs workspace left-edge top-edge
                          &optional minimum-width-of-button?)
  (loop as row in rows-of-button-specs
        as top-edge-for-this-row = top-edge then top-edge-for-next-row
        as top-edge-for-next-row
           = (+w (loop for button-spec in row
                       as previous-button? = nil then button
                       as class-of-button
                          = (if (or (atom button-spec)
                                    (null (fourth button-spec)))
                                'generic-action-button
                                'default-action-button)
                       as button
                          = (make-button
                              class-of-button
                              (copy-text-string
                                (if (atom button-spec)
                                    (symbol-name-text-string button-spec)
                                    (or (second button-spec)
                                        (symbol-name-text-string
                                          (car button-spec)))))
                              (if (atom button-spec) button-spec (car button-spec))
                              t
                              minimum-width-of-button?)
                       do (add-to-workspace
                            button workspace
                            (if previous-button?
                                (+w (right-edge-of-block previous-button?) 10)
                                left-edge)
                            (+w top-edge-for-this-row
                                (if (subclassp class-of-button 'default-action-button)
                                    vertical-fine-positioning-for-default-action-button
                                    0)))
                          (setf (button-action? button) (third button-spec))
                       maximize
                         (bottom-edge-of-block button) using maxf)
                 10)))




(defun add-check-boxes-to-current-dialog (label? list)
  (let* ((workspace (dialog-workspace
                     (specific-structure-for-workstation-context
                       current-workstation-context)))
        (left-edge (+w 20 (left-edge-of-block workspace)))
        (top-edge (loop for block being each subblock of workspace
                        when (frame-of-class-p block 'generic-action-button)
                          return (bottom-edge-of-block block))))
    (when label?
      (let ((label (make-button-label label? nil)))
        (add-to-workspace label workspace left-edge (+w 20 top-edge) t nil)
        (setq top-edge (+w 5 (bottom-edge-of-block label)))))
    (loop for top-edge = (+w 5 top-edge)
                       then (+w 5 (bottom-edge-of-block check-box))
          for (label name) in list
          as check-box = (make-button 'check-box (copy-text-string label) name t)
          do (add-to-workspace check-box workspace left-edge top-edge t nil)
      (loop for block being each subblock of workspace
            when (and (frame-of-class-p block 'generic-action-button)
                      (eq (button-action? block)
                          (symbol-function 'wrapped-action-function)))
              do (setf (button-action? block)
                       (symbol-function 'wrapped-action-function-with-checkbox-list))))))

(defun wrapped-action-function-with-checkbox-list (function arglist)
  (let ((copy-of-arglist (copy-list-using-slot-value-conses arglist)))
    (case function
      (delete-frame-after-checking-serial-number
       (setf (second copy-of-arglist)
             (copy-frame-serial-number (second copy-of-arglist))))
      (allow-continuation-of-class-selection-upon-confirmation
       (setf (fourth copy-of-arglist)
             (copy-frame-serial-number (fourth copy-of-arglist)))))
    (let ((alist (loop with workspace = (dialog-workspace
                                          (specific-structure-for-workstation-context
                                            current-workstation-context))
                       for block being each subblock of workspace
                       when (frame-of-class-p block 'check-box)
                         collect (slot-value-cons (get-primary-name-for-frame-if-any block)
                                                  (on/off-switch-on-p block))
                           using slot-value-cons)))
      (setq copy-of-arglist (nconc copy-of-arglist
                                   (slot-value-list alist))))
    (return-from-current-workstation-context 'dialog)
    (apply function copy-of-arglist)
    (reclaim-button-action-arglist copy-of-arglist function)))


;; Definition for class g2-window, among others, moved to module WORKSTATION.
;; They were being forward referenced and seemed way to primitive to belong
;; here.  (MHD 8/8/94)





;;;; G2 Window/Workstation Connection Maintenence




;;; `Connect-workstation-to-g2-window' sets up the pointers between g2-window
;;; and workstation, updates the connection status slots of g2-window, and fills
;;; in user settings from workstation.

(defun connect-workstation-to-g2-window (workstation g2-window)

  ;; Set up pointers between workstation and g2-window
  (change-slot-value g2-window 'workstation-for-g2-window? workstation)
  (setf (g2-window-for-this-workstation? workstation) g2-window)

  ;; Update the g2-window-management-type slot in g2-window
  (cond
    ((eq 'icp (type-of-gensym-window (window-for-workstation workstation)))
     (change-slot-value g2-window 'g2-window-management-type 'remote))
    (t (change-slot-value g2-window 'g2-window-management-type 'local)
       (when (workstation-os-user-name? workstation)
         (reclaim-text-string (workstation-os-user-name? workstation)))
       (setf (workstation-os-user-name? workstation)
             (foreign-get-user-name))
       (setf (workstation-os-type? workstation) g2-operating-system))))



;;; `Disconnect-workstation-from-g2-window' ... G2-window is deleted if it
;;; is not to be saved in the kb and is not now already in the process of
;;; being deleted.

;;; Also, in all cases, all workstation contexts are aborted.  Also, in all
;;; cases, all images of workspaces in the window are deleted.

(defun disconnect-workstation-from-g2-window (workstation g2-window)
  ;; Cut the pointer from the workstation to the g2 window.
  (setf (g2-window-for-this-workstation? workstation) nil)

  ;; Either delete g2-window, if appropriate, or put it into a cleared state
  (cond
    ((frame-being-deleted-p g2-window)
     ;; nothing to do -- frame is being deleted
     )
    ((do-not-save-in-kb-p g2-window)
     ;; not to be saved -- this was automatically created, so it
     ;;   now needs to be automatically deleted
     (funcall-method                                ; deactivate this thing
       'deactivate-and-propagate g2-window nil)        ; (Really necessary if about
     (delete-frame g2-window))                        ;   to delete?!)
    (t

     ;; Reinitialize the slots so that this can be reused:

     ;; Cut the pointer from the window to the workstation
     (change-slot-value g2-window 'workstation-for-g2-window? nil)

     ;; Update the connection status in g2-window
     (change-slot-value g2-window 'g2-connection-status 'connection-closed)

     ;; Update the g2-window-management-type slot in g2-window
     (change-slot-value g2-window 'g2-window-management-type nil)

     ;; Fill in user settings in g2-window
     (change-slot-value g2-window 'g2-user-name nil)
     (change-slot-value g2-window 'g2-user-mode nil)

     ;; Using setf to avoid triggering actions. Setting them back to
     ;; their initial (before login) values.
     (setf (g2-window-user-is-valid g2-window) falsity)
     (setf (g2-window-mode-is-valid g2-window) falsity)))


  ;; Abort any existing workstation contexts.
  (for-workstation (workstation) (unwind-current-workstation-back-to-top-level))

  ;; (Consider having an option to suppress this when rerouting.  Deleting the
  ;; window should do all of this anyway, this is just more needless drawing.
  ;; Cannot just remove this now because the workspaces have to be cleared when
  ;; just logging out. (MHD 11/8/94) (MHD 3/7/95)
  ;;
  ;; Clear the window of any images of workspaces
  (loop for pane in (panes-in-window (window-for-workstation workstation))
        do (loop for image-plane?
                     = (loop for image-plane
                                 in (stack-of-image-planes pane)
                             as workspace?
                                = (workspace-on-image-plane? image-plane)
                             when workspace? return image-plane)
                 while image-plane?
                 do (delete-image-plane image-plane?))))



;;; `Copy-gensym-window-attributes-into-g2-window' copies information about an
;;; actual gensym window into its g2-window (frame) representation.  This uses
;;; change-slot-value on the relevant slots, resulting in the immediate updating
;;; of the g2-window's table(s), if any.
;;;
;;; The current attributes affected are:
;;;
;;;   g2-window-x
;;;   g2-window-y
;;;   g2-window-width
;;;   g2-window-height
;;;   g2-window-x-resolution
;;;   g2-window-y-resolution
;;;
;;; This is called from a number of different places in the software that can
;;; influence either the attributes in question, either by changing the
;;; g2-window, or by changing the values underlying these attributes in the
;;; gensym-window.
;;;
;;; Note that these attributes are at present read-only; no mechanism is
;;; provided in either the UI or the API for changing these values through the
;;; g2-window; i.e., they're only displays of underlying gensym-window values.

(defun copy-gensym-window-attributes-into-g2-window (gensym-window)
  (let* ((workstation? (workstation-this-is-on gensym-window))
         (g2-window?
           (if workstation?
               (g2-window-for-this-workstation? workstation?))))
    (when g2-window?
      ;; Propagate the current window size.
      (let* ((do-not-note-permanent-changes-p t)
             (width-in-pixels (-f (right-edge-of-window gensym-window)
                                  (left-edge-of-window gensym-window)))
             (height-in-pixels (-f (bottom-edge-of-window gensym-window)
                                   (top-edge-of-window gensym-window)))
             (x-scale (get-gensym-window-parameter gensym-window 'default-x-scale))
             (y-scale (get-gensym-window-parameter gensym-window 'default-y-scale))
             (width (scale-scale width-in-pixels (normalized-scale) x-scale))
             (height (scale-scale height-in-pixels (normalized-scale) y-scale))
             (x-resolution (scale-scale x-scale 75 (normalized-scale)))
             (y-resolution (scale-scale y-scale 75 (normalized-scale))))
        ;; Set to workspace units, which is pixels * 4096/scale.
        ;; DPI = 75 * scale/4096.
        (macrolet ((s (g2-window-slot value)
                     `(unless (eql        ; don't change if not changing
                                (,g2-window-slot g2-window?)
                                ,value)
                        (change-slot-value
                          g2-window? ',g2-window-slot ,value))))
;          (s g2-window-x (window-x-in-parent gensym-window))
;          (s g2-window-y (window-y-in-parent gensym-window))
          (s g2-window-width width)
          (s g2-window-height height)
          (s g2-window-x-resolution x-resolution)
          (s g2-window-y-resolution y-resolution))))))

;; Might we ever be on-window here?






;;;; Role Service for G2 Windows


;;; Serve-this-window, a role server function, has been moved here from ROLES due
;;; to the reference to the slot ri-window-for-rule? , which is not defined when
;;; ROLES is loaded.

(defun serve-this-window (role domain)
  (declare (ignore domain))
  (let* ((role-class (type-of-role role))
         (gensym-window-for-rule?
           (if (and (boundp 'current-computation-instance)
                    (rule-instance-p current-computation-instance))
               (ri-window-for-rule?
                 current-computation-instance)))
         (current-session? (and (boundp 'current-ui-client-session)
                                current-ui-client-session))
         (resulting-item?
           (cond
             ;; new 5.0r1 (Nevada) case
             ((and gensym-window-for-rule?
                   (of-class-p gensym-window-for-rule?
                               'ui-client-session))
              gensym-window-for-rule?)
             ;; if no rule window, maybe current-ui-client-session
             ;; is bound, in which case we can use that.
             (current-session? current-session?)
             ;; traditional technique for serving g2-windows
             (t
              (let ((workstation-for-window?
                      (if gensym-window-for-rule?
                          (workstation-this-is-on gensym-window-for-rule?)
                          (if servicing-workstation?
                              current-workstation))))
                (and workstation-for-window?
                     (g2-window-for-this-workstation?
                       workstation-for-window?)))))))
    (and resulting-item?
         (frame-of-class-p resulting-item? role-class)
         resulting-item?)))

;; Consider flagging the error of using "this window" in other than an
;; embedded rule in the compiler and/or frame notes.






;;;; Support for G2 Window-related Evaluators



;;; `Transform-user-coordinate' either transforms an x or y user window
;;; coordinate a user workspace coordinate, or transforms an x or y user
;;; workspace coordinate into a user window coordinate.
;;;
;;; The origin of the user window coordinate system is defined to be the center
;;; of the detail pane of the G2 window.  This differs a bit from the internal
;;; window system, where the origin is generally the upper, left corner of the
;;; window (a few pixels away from the upper left corner of the pane due to the
;;; pane border).
;;;
;;; A y user window coordinate grows upward in the positive direction.  This is
;;; the opposite from the internal window system, where positive y grows
;;; downward.  (There is no difference between the two systems in this regard
;;; for the x dimension.)
;;;
;;; This maps a user window coordinate into a user workspace coordinate by (1)
;;; if a y coordinate, taking its opposite, otherwise its identity; (2) adding
;;; to it the offset from the internal origin to the center of the pane; (3)
;;; mapping this via x/y-in-workspace to the (internal) workspace coordinate;
;;; and (4) if it's a y coordinate, returning its opposite, otherwise returning
;;; its identity.
;;;
;;; Mapping from workspace to window coordinates is basically the reverse of
;;; this process.
;;;
;;; This maps a user workspace coordinate into a user window coordinate by (1)
;;; if a y coordinate, taking its opposite, otherwise its identity; (2) mapping
;;; this via x/y-in-window to the (internal) window coordinate; (3) subtracting
;;; the offset from the internal origin to the center of the pane from the
;;; result; and (4) if a y coordinate, returning its opposite, otherwise
;;; returning its identity.
;;;
;;; The result of this function is an evaluation integer.
;;;
;;; If g2-window is not a mapped gensym window, or if workspace is not on an
;;; image plane in the mapped gensym window, then this signals a stack error.

(defun transform-user-coordinate
    (transformation-type workspace g2-window coordinate)
  (make-evaluation-integer
    (let* ((image-plane (map-to-image-plane-or-stack-error workspace g2-window))
           (x-center-of-pane
             (halfr (+r (left-edge-of-pane-in-window image-plane)
                        (right-edge-of-pane-in-window image-plane))))
           (y-center-of-pane
             (halfr (+r (top-edge-of-pane-in-window image-plane)
                        (bottom-edge-of-pane-in-window image-plane)))))
      (with-image-plane-transform (image-plane)
        (case transformation-type
          (x-in-window
           (-r (x-in-window coordinate) x-center-of-pane))
          (y-in-window
           (-r (-r (y-in-window (-r coordinate)) y-center-of-pane)))
          (x-in-workspace
           (x-in-workspace (+r coordinate x-center-of-pane)))
          (y-in-workspace
           (-r (y-in-workspace (+r (-r coordinate) y-center-of-pane)))))))))





;;; The function `user-x-in-window-to-internal-x-in-window' converts the user's
;;; idea of an x-in-window coordinate to G2's internal value.

(defun user-x-in-window-to-internal-x-in-window (user-x-in-window gensym-window)
  (let* ((pane (detail-pane gensym-window))
         (image-plane (car (stack-of-image-planes pane)))
         (x-center-of-pane
           (halfr (+r (left-edge-of-pane-in-window image-plane)
                      (right-edge-of-pane-in-window image-plane)))))
    (+r user-x-in-window x-center-of-pane)))

(defun user-y-in-window-to-internal-y-in-window (user-y-in-window gensym-window)
  (let* ((pane (detail-pane gensym-window))
         (image-plane (car (stack-of-image-planes pane)))
         (y-center-of-pane
           (halfr (+r (top-edge-of-pane-in-window image-plane)
                      (bottom-edge-of-pane-in-window image-plane)))))
    (-r y-center-of-pane user-y-in-window)))



;;; `Map-g2-window-to-gensym-window' returns the gensym window for g2-window
;;; if there is one; otherwise, nil.  This can be called in any context; it
;;; does not signal stack errors.

(defun-simple map-g2-window-to-gensym-window (g2-window)
  (if (workstation-for-g2-window? g2-window)
      (window-for-workstation (workstation-for-g2-window? g2-window))))



;;; `Map-to-image-plane' maps the pair (workspace, g2-window) to a valid image
;;; plane if possible; otherwise, nil.  This can be called in any context; it
;;; does not signal stack errors. `Map-to-image-plane-in-gensym-window' is its
;;; subfunction and does almost the same thing, but takes a gensym-window
;;; argument instead.  The gensym-window argument should have already been
;;; mapped from a g2-window, and should be connected.

(defun-simple map-to-image-plane (workspace g2-window)
  (let ((gensym-window? (map-g2-window-to-gensym-window g2-window)))
    (if gensym-window?
        (map-to-image-plane-in-gensym-window workspace gensym-window?))))

(defun-simple map-to-image-plane-in-gensym-window (workspace gensym-window)
  (get-image-if-any
    workspace
    (detail-pane gensym-window)))

;; Note that, somewhat inconsistently, the get-pane-if-any, given DETAIL-PANE,
;; is assumed never to return nil, despite the "-if-any" suffix, whereas these
;; mapping functions, without any such suffix, may return nil.  The detail pane
;; is guaranteed to be there in a valid gensym-window. Still, it seems
;; inconsistent, and would be nice to fix up! (MHD 4/2/04)





;;; `Map-to-image-plane-or-stack-error' maps the pair (workspace, g2-window) to
;;; a valid image plane if possible.  If it can't get a gensym window, or can't
;;; get an image plane in that window, it signals an appropriate stack error.
;;;
;;; `Map-to-gensym-window-or-stack-error' ... maps g2-window to a valid gensym
;;; window if possible.  If it can't get a gensym window, it signals an
;;; appropriate stack error.
;;;
;;; Both of these functions may only be called within a stack evaluation
;;; context.

(defun map-to-image-plane-or-stack-error (workspace g2-window)
  (or (map-to-image-plane-in-gensym-window
        workspace
        (map-to-gensym-window-or-stack-error g2-window))
      (stack-error
        cached-top-of-stack
        "~NF is not showing in ~NF" workspace g2-window)))

(defun map-to-gensym-window-or-stack-error (g2-window)
  (or (map-g2-window-to-gensym-window g2-window)
      (stack-error
        cached-top-of-stack
        "~NF is not in use as a window" g2-window)))


;;; `Get-user-image-plane-scale' gets the floating point user image plane scale
;;; in either x or y for the image plane designated by the supplied
;;; workspace/g2-window pair.  If the image plane cannot be gotten, an
;;; appropriate stack error may be signalled.
;;;
;;; This may only be used in a stack evaluation context.  This returns an
;;; evaluation float as its single return value.

(defun get-user-image-plane-scale (x-or-y-scale workspace g2-window)
  (assert-that-within-temporary-float-scope)
  (make-evaluation-float
    (compute-user-image-plane-scale
      x-or-y-scale
      (map-to-image-plane-or-stack-error workspace g2-window))))








;;;; Window System System Procedures



;;; Summary:
;;;
;;; g2-x-in-window (x-in-workspace, workspace, g2-window) => x-in-window
;;; g2-y-in-window (y-in-workspace, workspace, g2-window) => y-in-window
;;;
;;; g2-x-in-workspace (x-in-window, workspace, g2-window) => x-in-workspace
;;; g2-y-in-workspace (y-in-window, workspace, g2-window) => y-in-workspace
;;;
;;; g2-x-scale-of-workspace-in-window (workspace, g2-window) => x-scale
;;; g2-y-scale-of-workspace-in-window (workspace, g2-window) => y-scale
;;;
;;; The coordinate arguments must be integers.  The coordinate transformation
;;; functions return integers.
;;;
;;; Each scaling function returns a float F, where 0.0 > F >= 4.0, where 1.0 is
;;; full scale.

(defun-for-system-procedure g2-x-in-window (x-in-workspace workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (prog1 (transform-user-coordinate 'x-in-window workspace g2-window x-in-workspace)
    (reclaim-evaluation-integer x-in-workspace)))

(defun-for-system-procedure g2-y-in-window (y-in-workspace workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (prog1 (transform-user-coordinate 'y-in-window workspace g2-window y-in-workspace)
    (reclaim-evaluation-integer y-in-workspace)))

(defun-for-system-procedure g2-x-in-workspace (x-in-window workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (prog1 (transform-user-coordinate 'x-in-workspace workspace g2-window x-in-window)
    (reclaim-evaluation-integer x-in-window)))

(defun-for-system-procedure g2-y-in-workspace (y-in-window workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (prog1 (transform-user-coordinate 'y-in-workspace workspace g2-window y-in-window)
    (reclaim-evaluation-integer y-in-window)))


;;; `G2-x-scale-of-workspace-in-window' and `G2-y-scale-of-workspace-in-window'
;;; return floats (i.e., evaluation floats).

(defun-for-system-procedure g2-x-scale-of-workspace-in-window (workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (get-user-image-plane-scale 'x-scale workspace g2-window))

(defun-for-system-procedure g2-y-scale-of-workspace-in-window (workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (get-user-image-plane-scale 'y-scale workspace g2-window))



;;; All of the following return the value "n".  This is always the current layer
;;; position of workspace in g2-window as of the end of the procedure.  N is a
;;; non-negative integer.  N = 0 for the frontmost workspace (i.e., the image
;;; plane therefor).
;;;
;;; Note that is possible for a request to set a layer position not to be
;;; granted, e.g., if it impossible (negative integer, or larger than the
;;; current stack size), or if a "riding image plane" ("superplane") is
;;; currently "glued" to an image plane at that position, and so cannot tolerate
;;; an intervening image plane.

;;; g2-get-workspace-layer-position (workspace, g2-window) => n
;;; g2-lift-workspace-to-top (workspace, g2-window) => n
;;; g2-drop-workspace-to-bottom (workspace, g2-window) => n
;;; g2-lift-workspace-in-front-of (workspace, g2-window) => n
;;; g2-drop-workspace-behind (workspace, g2-window) => n
;;; g2-get-workspace-layer-position (workspace, g2-window) => n
;;; g2-set-workspace-layer-position (workspace, g2-window) => n

(defun-simple get-position-of-image-plane-in-its-stack (image-plane)
  (loop for image-plane-in-stack
            in (stack-of-image-planes (pane-for-image-plane image-plane))
        as position from 0
        when (eq image-plane-in-stack image-plane)
          return position))


(defun-for-system-procedure g2-get-workspace-layer-position (workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (get-position-of-image-plane-in-its-stack
    (map-to-image-plane-or-stack-error workspace g2-window)))

(defun-for-system-procedure g2-lift-workspace-to-top (workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (raise-image-plane-to-top
    (map-to-image-plane-or-stack-error workspace g2-window)))

(defun-for-system-procedure g2-drop-workspace-to-bottom (workspace g2-window)
  (declare (keeps-g2-local-variables-valid t))
  (lower-image-plane-to-bottom
    (map-to-image-plane-or-stack-error workspace g2-window)))

(defun-for-system-procedure g2-lift-workspace-in-front-of
    (workspace-1 workspace-2 g2-window)        ; really means "put in front of",
  (declare (keeps-g2-local-variables-valid t))
  (g2-set-workspace-layer-position        ;   which might involve dropping
    workspace-1
    g2-window
    (-f (g2-get-workspace-layer-position workspace-2 g2-window) 1)))

(defun-for-system-procedure g2-drop-workspace-behind ; really means "put behind",
    (workspace-1 workspace-2 g2-window)                     ;   which might involve lifting
  (declare (keeps-g2-local-variables-valid t))
  (g2-set-workspace-layer-position
    workspace-1
    g2-window
    (+f (g2-get-workspace-layer-position workspace-2 g2-window) 1)))

(defun-for-system-procedure g2-set-workspace-layer-position
    (workspace g2-window position)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((image-plane (map-to-image-plane-or-stack-error workspace g2-window))
         (current-pane (pane-for-image-plane image-plane))
         (present-position
           (get-position-of-image-plane-in-its-stack image-plane))
         (delta-position-index?
           (if (=f present-position position)
               nil
               (-f position present-position))))
    (if delta-position-index?
        (progn
          (revise-pane current-pane image-plane delta-position-index? nil)
          (get-position-of-image-plane-in-its-stack image-plane))
        present-position)))

;; Still can't: get the position of the bottom workspace; get every workspace
;; shown in a window; get the workspace shown at a given position (if any).
;; These are mostly item problems (non-kb-workspaces are not items).

;; Consider adding  "show" system procedure, like this:
;; (defun-for-system-procedure g2-show-workspace-in-window
;;    (workspace g2-window
;;     x-in-workspace y-in-workspace
;;     x-in-window y-in-window
;;     x-scale y-scale
;;     layer-position)
;;   ...)




;;; G2-item-is-showing-in-window ... This expects the caller to ensure that the
;;; second arg is actually an instance of the class UI-CLIENT-ITEM, and,
;;; in the case of a G2-WINDOW, that is it connected.

(defun-for-system-procedure g2-item-is-showing-in-window
    ((item item) (ui-client-item item))        ; rely on caller for fine-grained checking
  (declare (values truth-value)
           (keeps-g2-local-variables-valid t))
  (let ((workspace? (get-workspace-if-any item)))
    (if (and workspace?
             (workspace-is-showing-in-ui-client-item workspace? ui-client-item))
        truth
        falsity)))

;; To tell if a window is showing, you have to, for now, check the
;; g2-connected-status of a g2-window object to see that is is CONNECTED.  This
;; can only be done via the expression
;;
;;   the text of the g2-connected-status of my-window = "connected"
;;
;; at present.  But later, we'll enable component part access enough to give
;; users direct access to the symbol that is the value. (MHD 8/11/94)

(defun-simple workspace-is-showing-in-ui-client-item
    (workspace ui-client-item)
  (frame-class-case ui-client-item
    ((ui-client-session)
     (find workspace (ui-client-session-workspaces-function ui-client-item)))
    ((g2-window)
     (let ((gensym-window? (map-g2-window-to-gensym-window  ui-client-item)))
       (and gensym-window?
            (loop for image-plane in (image-planes-this-is-on workspace)
                  thereis (eq (gensym-window-for-pane
                                (pane-for-image-plane image-plane))
                              gensym-window?)))))))







;;;; System Procedures for KB State Changes

(defvar note-kb-state-changes-via-system-procedures? t)

;; Changed from (conceptually) nil to t between Rev. 0 and Rev. 1
;; of G2 4.0. (MHD 8/17/95)



;;;; Icon Rotation/Reflection System Procedures


;;; g2-get-reflection-and-rotation (item) => reflection-and-rotation, a symbol in
;;;   { normal                  ; normal (no rotation or reflection)
;;;     clockwise-90            ; rotated by 90 degrees
;;;     clockwise-180           ; rotated by 180 degrees
;;;     clockwise-270           ; rotated by 270 degrees
;;;     reflected               ; flipped left to right
;;;     reflected-clockwise-90  ; flipped left to right, and then rotated by 90 degrees
;;;     reflected-clockwise-180 ; flipped left to right, and then rotated by 180 degrees
;;;                             ;   (note: equivalent to "flipped upside down")
;;;     reflected-clockwise-270 ; flipped left to right, and then rotated by 270 degrees
;;;   }   ; note: these are all of the configurations currently possible in G2
;;;
;;; g2-combine-reflection-and-rotation (reflection-and-rotation-1,
;;;     reflection-and-rotation-2)
;;;   => reflection-and-rotation
;;;
;;;
;;; g2-set-reflection-and-rotation (item reflection-and-rotation)
;;;   => reflection-and-rotation ; i.e., the resulting reflection-and-rotation
;;; g2-reflect-item-horizontally (item) => reflection-and-rotation
;;; g2-reflect-item-vertically (item) => reflection-and-rotation
;;;
;;; For entities that cannot be rotated (buttons, dials, and meters) and for
;;; things that don't normally have a reflection-and-rotation, e.g., workspaces,
;;; text boxes, system tables, etc., NORMAL is returned in the get case, and a
;;; stack error is signalled in the set cases.  Otherwise, the actual rotation
;;; is returned in both the get and set cases.

(defun-for-system-procedure g2-get-reflection-and-rotation ((item item))
  (declare (values symbol)                        ; nil <=> NORMAL
           (keeps-g2-local-variables-valid t))
  (g2-get-reflection-and-rotation-internal item))

(define-system-rpc-access (g2-get-reflection-and-rotation (symbol))
    ((item (class item)))
  (g2-get-reflection-and-rotation item))

(defun-for-system-procedure g2-set-reflection-and-rotation
    ((item item) (reflection-and-rotation symbol))
  (declare (values symbol)
           (keeps-g2-local-variables-valid t))
  (g2-set-reflection-and-rotation-internal item reflection-and-rotation))

(define-system-rpc-access (g2-set-reflection-and-rotation (symbol))
    ((item (class item))
     (reflection-and-rotation symbol))
  (g2-set-reflection-and-rotation item reflection-and-rotation))

(defun-for-system-procedure g2-combine-reflection-and-rotation
    ((reflection-and-rotation-1 symbol) (reflection-and-rotation-2 symbol))
  (declare (values symbol)
           (keeps-g2-local-variables-valid t))
  (require-legal-reflection-and-rotation-symbol
    reflection-and-rotation-1)
  (require-legal-reflection-and-rotation-symbol
    reflection-and-rotation-2)
  (multiply-reflection-and-rotation
    reflection-and-rotation-1 reflection-and-rotation-2))                        ; nil <=> NORMAL

(defun-for-system-procedure g2-reflect-item-horizontally ((item item))
  (declare (values symbol)
           (keeps-g2-local-variables-valid t))
  (g2-set-reflection-and-rotation-internal
    item
    (multiply-reflection-and-rotation
      (g2-get-reflection-and-rotation-internal item)
      'reflected)))

(define-system-rpc-access (g2-reflect-item-horizontally (symbol))
    ((item (class item)))
  (g2-reflect-item-horizontally item))

(defun-for-system-procedure g2-reflect-item-vertically ((item item))
  (declare (values symbol)
           (keeps-g2-local-variables-valid t))
  (g2-set-reflection-and-rotation-internal
    item
    (multiply-reflection-and-rotation
      (g2-get-reflection-and-rotation-internal item)
      'reflected-clockwise-180)))

(define-system-rpc-access (g2-reflect-item-vertically (symbol))
    ((item (class item)))
  (g2-reflect-item-vertically item))


;;; `G2-get-reflection-and-rotation-internal' ...

(defun g2-get-reflection-and-rotation-internal (item)
  (or (if (entity-p item)
          (getfq (icon-attributes-plist item)
                 'reflection-and-rotation))
      'normal))


;;; `G2-set-reflection-and-rotation-internal' is the Lisp-internal version
;;; of g2-set-reflection-and-rotation.  This is also called internally by
;;; the g2-reflect-item-horizontally and g2-reflect-item-vertically system
;;; procedures.  This does all checking and potentially signals a stack error.
;;; It also returns the appropriate value, a symbol giving the final
;;; reflection-and-rotation.

(defun g2-set-reflection-and-rotation-internal (item reflection-and-rotation)
  (require-legal-reflection-and-rotation-symbol reflection-and-rotation) ; may throw
  (require-rotatable-and-reflectable-item item cached-top-of-stack) ; may throw
  (let* ((current-reflection-and-rotation
           (or (getfq (icon-attributes-plist item) 'reflection-and-rotation)
               'normal))
         (inverse
           (invert-reflection-and-rotation current-reflection-and-rotation))
         (delta-reflection-and-rotation
           (multiply-reflection-and-rotation inverse reflection-and-rotation)))
    (rotate-and-reflect-icon-symbolically
      item delta-reflection-and-rotation nil nil
      note-kb-state-changes-via-system-procedures?)
    (when g2-has-v5-mode-windows-p
      (send-ws-representations-item-rotated
        item
        (or (getfq (icon-attributes-plist item) 'reflection-and-rotation)
            'normal)))
    (or (getfq (icon-attributes-plist item) 'reflection-and-rotation)
        'normal)))



;;; `Require-legal-reflection-and-rotation-symbol'
;;; signals a stack error if text-box is not a subclass of text box.

(defun require-legal-reflection-and-rotation-symbol
    (candidate-symbol)
  (when (not (legal-reflection-and-rotation-symbol-p candidate-symbol))
    (stack-error
      cached-top-of-stack
      "~a is not a legal reflection-and-rotation. (Legal values are ~
       normal, clockwise-90, clockwise-180, ~
       clockwise-270, reflected, reflected-clockwise-90, ~
       reflected-clockwise-180, or reflected-clockwise-270.)"
      candidate-symbol)))





;;;; System Procedures for Accessing Icon Colors



;;; `G2-Get-Item-Color-Pattern' and `g2-set-item-color-pattern' get and
;;; set, respectively, an item's color pattern.
;;;
;;; `G2-Get-Default-Item-Color-Pattern' returns the default color pattern of
;;; an item, i.e., either that defined by the user or the system as appropriate.
;;;
;;; `G2-Get-Permanent-Item-Color-Pattern' returns the color pattern as it
;;; would be if the KB were reset, or as it would be if this KB were saved
;;; and then reloaded.
;;;
;;; Technically, the get functions return a "color change pattern" as opposed
;;; to a color pattern.  See ENTITIES for definitions and discussion of the
;;; distinction.
;;;
;;; These are the Lisp-side function of system procedures with the same name.
;;; These system procedures were newly added to G2 as of 4.0 Rev. 1.
;;;
;;; [One of the main reasons was to allow procedures to change all of the
;;; (named) regions of built-in system-defined icons without having to know any
;;; of their region names at compile time.  This then allows both system-defined
;;; and user-defined icons to change all (named) regions to TRANSPARENT,
;;; effectively making an item invisible.  (MHD 8/17/95)]
;;;
;;; [Maybe there should be reset-kb-state-change-for-color-pattern, but there
;;; _really_ should be a general mechanism for this for all kb state changes,
;;; e.g., position, rotation, etc.! (MHD 8/17/95)]
;;;
;;; The arg to the get function can be any item.  The result is always a
;;; new transient item of class symbol-array with an even number of elements.
;;; The array is if the form
;;;
;;;    ( { region color-or-metacolor } )
;;;
;;; where region and color-or-metacolor are symbols.  This array is in fact
;;; guaranteed to be a valid set of actual color regions and their actual
;;; "bindings" in the item.  (Further information about what kinds of color
;;; patterns and regions various items can have is beyond the scope of this
;;; doc.  But see ENTITIES.)
;;;
;;; The args to the set function are an item to set and color change pattern in
;;; the form of an item that should be a symbol array containing a valid
;;; specification for a color change pattern, i.e., a symbol-array instance of
;;; the form described above, but possibly with different color-or-metacolor
;;; entries.
;;;
;;; The symbol-array item is checked for validity in various stages, first by
;;; extract-color-pattern-from-alleged-color-pattern-symbol-array and then by
;;; change-item-color-pattern-from-evaluation-stack and any of its subfunctions.
;;;
;;; In general, it either gets a valid specification for an item and its
;;; color change pattern, and does the change, or it signals a stack error.

(defun-for-system-procedure g2-get-item-color-pattern ((item item))
  (declare (values item))
  (convert-color-pattern-to-transient-symbol-array
    (get-color-pattern-of-item item nil t)))

(defun-for-system-procedure g2-get-default-item-color-pattern ((item item))
  (declare (values item))
  (convert-color-pattern-to-transient-symbol-array
    (get-color-pattern-of-item item 'default t)))

(defun-for-system-procedure g2-get-permanent-item-color-pattern ((item item))
  (declare (values item))
  (convert-color-pattern-to-transient-symbol-array
    (get-color-pattern-of-item item 'permanent t)))

(defun-for-system-procedure g2-set-item-color-pattern
    ((item item) (color-pattern-symbol-array item))
  (let ((color-pattern
          (extract-color-pattern-from-alleged-color-pattern-symbol-array
            color-pattern-symbol-array)))
    (change-item-color-pattern-from-evaluation-stack
      cached-top-of-stack
      item
      color-pattern
      note-kb-state-changes-via-system-procedures?)
    (reclaim-proc-tree color-pattern)))



;;; `G2-get-item-color', `g2-get-default-item-color', and
;;; `g2-get-permanent-item-color' each take an item and return
;;; the color for the designated region in the designated "state",
;;; where the region is designated by the argument region, and the
;;; state (current, default, or permanent) is implied by the
;;; respective procedure name.

(defun-for-system-procedure g2-get-item-color
    ((item item) (region symbol))
  (declare (values symbol))
  (or (let ((color-pattern (get-color-pattern-of-item item nil t)))
        (prog1 (cdr (assq region color-pattern))
          (reclaim-slot-value-tree color-pattern)))
      (stack-error-for-unknown-region item region)))

(define-system-rpc-access (g2-get-item-color (symbol))
    ((item (class item))
     (region symbol))
  (g2-get-item-color item region))

(defun-for-system-procedure g2-get-default-item-color
    ((item item) (region symbol))
  (declare (values symbol))
  (or (let ((color-pattern (get-color-pattern-of-item item 'default t)))
        (prog1 (cdr (assq region color-pattern))
          (reclaim-slot-value-tree color-pattern)))
      (stack-error-for-unknown-region item region)))

(define-system-rpc-access (g2-get-default-item-color (symbol))
    ((item (class item))
     (region symbol))
  (g2-get-default-item-color item region))

(defun-for-system-procedure g2-get-permanent-item-color
    ((item item) (region symbol))
  (declare (values symbol))
  (or (let ((color-pattern (get-color-pattern-of-item item 'permanent t)))
        (prog1 (cdr (assq region color-pattern))
          (reclaim-slot-value-tree color-pattern)))
      (stack-error-for-unknown-region item region)))

(define-system-rpc-access (g2-get-permanent-item-color (symbol))
    ((item (class item))
     (region symbol))
  (g2-get-permanent-item-color item region))

;; These should later be implemented not to have to cons at all. That can be
;; done with some extra work, but we simply lack the time to get that right
;; right now.  Consing up the full pattern, extracting the region we want, and
;; reclaiming the pattern is correct and OK in the short run.  Eventually,
;; considing adding the optional "state?" and "external?" arg to item-color, and
;; then change these to use them. (MHD 8/18/95)


;;; `G2-set-item-color' sets just the designated region's color to be
;;; color-or-metacolor.  If there is anything wrong with region or
;;; color-or-metacolor, or item cannot be changed, this signals a stack
;;; error.
;;;
;;; This returns no useful values.

(defun-for-system-procedure g2-set-item-color
    ((item item) (region symbol) (color-or-metacolor symbol))
  (let ((color-change-pattern-for-stack-evaluator
          (proc-list (proc-cons region color-or-metacolor))))
    (change-item-color-pattern-from-evaluation-stack
      cached-top-of-stack
      item
      color-change-pattern-for-stack-evaluator
      note-kb-state-changes-via-system-procedures?)
    (reclaim-proc-tree color-change-pattern-for-stack-evaluator)))

(define-system-rpc-access (g2-set-item-color ())
    ((item (class item))
     (region symbol)
     (color-or-metacolor symbol))
  (g2-set-item-color item region color-or-metacolor))

;;; `G2-get-item-color-regions' returns a symbol array containing all of the
;;; named regions of item.  Note that this is list is guaranteed to be in the
;;; same order as the list of region/color-or-metacolor pairs in a color-pattern
;;; represented as a symbol-array as emitted by the g2-get-item-color-pattern
;;; system procedure and friends.

(defun-for-system-procedure g2-get-item-color-regions ((item item))
  (declare (values item))
  (let* ((symbol-array (make-transient-item 'symbol-array))
         (color-pattern (get-color-pattern-of-item item nil t))
         (length (length color-pattern)))
    (change-slot-value symbol-array 'g2-array-length length)
    (loop for (region) in color-pattern
          as i from 0
          do (setf (g2-array-aref symbol-array i) region))
    (reclaim-slot-value-tree color-pattern)
    symbol-array))



;;; `Convert-color-pattern-to-transient-symbol-array' returns a transient symbol
;;; list based on color-pattern.  Color-pattern is reclaimed by this function
;;; as a slot value tree.
;;;
;;; Color-pattern must be a valid color pattern; this does not checking.

(defun convert-color-pattern-to-transient-symbol-array (color-pattern)
  (let* ((symbol-array (make-transient-item 'symbol-array))
         (length (twicef (length color-pattern))))
    (change-slot-value symbol-array 'g2-array-length length)
    (loop for (region . color-or-metacolor) in color-pattern
          as i from 0 by 2
          do (setf (g2-array-aref symbol-array i) region)
             (setf (g2-array-aref symbol-array (+f i 1)) color-or-metacolor))
    (reclaim-slot-value-tree color-pattern)
    symbol-array))




;;; `Extract-color-pattern-from-alleged-color-pattern-symbol-array' takes takes
;;; an item, and verifies that it is a symbol list.  If not, it signals a stack
;;; error.  Then it verifies the length of the list is even, and signals a stack
;;; error if it is not.  Then it returns the color change pattern corresponding
;;; to the symbol-array, assuming that the list is of the form
;;;
;;;    ( { region color } )
;;;
;;; Note, however, that the a-list is made up of proc conses, which happen to be
;;; needed as the arg to the function used to execute a color pattern change.
;;;
;;; Note that symbol-array is expected to be an item (i.e., via the actual system
;;; procedure's arg type declaration), but it's not and cannot be assumed that
;;; it's of class symbol-array.

(defun extract-color-pattern-from-alleged-color-pattern-symbol-array
    (symbol-array)
  (when (not (frame-of-class-p symbol-array 'symbol-array))
    (stack-error
      cached-top-of-stack
      "~NA is not an item of class symbol-array."
      symbol-array))
  (when (oddp (g2-array-length symbol-array))
    (stack-error
      cached-top-of-stack
      "~NA is not an even-length array of symbols. It should be an ~
       array of alternating region name and color name symbols, starting with ~
       the first region name."
      symbol-array))
  (let ((color-pattern-so-far nil)
        (i 0))
    (do-g2-array-elements (symbol symbol-array nil)
      (cond
        ((evenp i)                        ; need oddpf and evenpf!
         (proc-push
           (proc-cons symbol nil)
           color-pattern-so-far))
        (t
         (setf (cdr (first color-pattern-so-far)) symbol)))
      (incff i))
    (nreverse-canonically color-pattern-so-far)))



(defun stack-error-for-unknown-region (item region)
  (stack-error cached-top-of-stack "~NA has no ~a region." item region))












;;;; Power Icons Support Functions:
;;;; (should be moved to stack-acts when
;;;;  conclude or change action is added) pbk 4/9/96








;;;; Primary set functions for compute-values-plist in Power Icons:

;;; `set-icon-variables-internal'
;;; Does NOT modify, or reclaim new-variables-plist.
;;; Copies all variable values before setting.
;;; Returned value is an error OR the new variables attribute
;;; PBK POTENTIAL BUG -- NEED TO REMOVE WIDTH/HEIGHT from
;;; THE LIST WE TRY TO SET!!!!!!

(defun set-icon-variables-internal
    (entity note-as-kb-state-change? new-variables-plist delete-non-changing-variables-p)
  ;;  (cond ((entity-is-opaque-p entity)
  ;;                 (set-opaque-block entity))
  ;;                (t (clear-opaque-block entity)))
  ;; is the opacity changing ???
  (loop        with result = nil
        with icon-description = (icon-description entity)
        with line-drawing-description = (icon-line-drawing-description icon-description)
        with default-variables-plist
          = (cdr (get-variable-specification-if-any line-drawing-description))
        for (variable-name variable-value) on default-variables-plist by 'cddr
        as new-value?
           = (getfq new-variables-plist variable-name)
        as default-case-p
           = (variable-value-equal new-value? variable-value)
        do
    (when (and new-value? (not default-case-p))
      (slot-value-push variable-name result)
      (slot-value-push (copy-for-slot-value new-value?) result))
        finally
          (let ((do-not-note-permanent-changes-p note-as-kb-state-change?))
            (when note-as-kb-state-change?
              (note-kb-state-change entity 'variables))
            (change-icon-variables entity (nreverse result)
                                   delete-non-changing-variables-p))))

(defun-void reclaim-icon-variables-plist (plist)
  (loop for (name value) on plist by 'cddr
        do
    (when (text-string-p-macro value)
      (reclaim-text-string value))
        finally
          (reclaim-slot-value-list plist)))

(defun change-icon-variables (entity value? &optional (delete-non-changing-values-p t))
  (note-change-to-block entity 'icon-attributes-plist)
  (loop with icon-attributes-plist
          =  (icon-attributes-plist entity)
        as l-trailer? = nil then (cdr l)
        as l = icon-attributes-plist
             then (cdr l-trailer?)
        while l
        when (eq (car-of-cons l) 'variables)
          do (cond
               (value?
                (cond (delete-non-changing-values-p
                       (reclaim-icon-variables-plist (second-of-cons l))
                       (setf (second-of-cons l) value?))
                      (t
                       (let ((old-variables (second-of-cons l)))
                         (loop for (variable-name variable-value) on old-variables by 'cddr
                               as new-value-exists-p = (getf value? variable-name)
                               do
                           (unless new-value-exists-p
                             (slot-value-push (copy-for-slot-value variable-value) value?)
                             (slot-value-push variable-name value?)))
                         (reclaim-icon-variables-plist old-variables))
                       (setf (second-of-cons l) value?))))
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
                      'variables
                      (slot-value-cons
                        value?
                        icon-attributes-plist))))
          (return value?)))








;;;; Functions for computing minimal redraw of Power Icons:


(defmacro set-extrema-for-line-drawing-element
    (extrema-for-line-drawing-element new-value-exp access-function compare-function)
  (let ((new-value (gensym)))
    (unless (symbolp extrema-for-line-drawing-element)
      (error "set-extrema-for-line-drawing-element only accepts variables as place forms"))
    (unless (symbolp access-function)
      (error "access function must be a symbol naming a function"))
    (unless (symbolp compare-function)
      (error "compare function must be a symbol naming a function"))
    `(let ((,new-value ,new-value-exp))
       (cond ((null ,new-value)
              nil)
             ((null (,access-function ,extrema-for-line-drawing-element))
              (setf (,access-function ,extrema-for-line-drawing-element)
                    ,new-value))
             (t (setf (,access-function ,extrema-for-line-drawing-element)
                      (,compare-function ,new-value
                                         (,access-function ,extrema-for-line-drawing-element))))))))

(defun set-left-extrema-for-line-drawing-element
    (extrema-for-line-drawing-element new-value)
  (set-extrema-for-line-drawing-element
    extrema-for-line-drawing-element new-value car minf))

(defun set-top-extrema-for-line-drawing-element
    (extrema-for-line-drawing-element new-value)
  (set-extrema-for-line-drawing-element
    extrema-for-line-drawing-element new-value second minf))

(defun set-right-extrema-for-line-drawing-element
    (extrema-for-line-drawing-element new-value)
  (set-extrema-for-line-drawing-element
    extrema-for-line-drawing-element new-value third maxf))

(defun set-bottom-extrema-for-line-drawing-element
    (extrema-for-line-drawing-element new-value)
  (set-extrema-for-line-drawing-element
    extrema-for-line-drawing-element new-value fourth  maxf))

(defun update-extrema-for-line-drawing-element
    (extrema-for-line-drawing-element new-x new-y)
  (set-left-extrema-for-line-drawing-element
    extrema-for-line-drawing-element
    new-x)
  (set-top-extrema-for-line-drawing-element
    extrema-for-line-drawing-element
    new-y)
  (set-right-extrema-for-line-drawing-element
    extrema-for-line-drawing-element
    new-x)
  (set-bottom-extrema-for-line-drawing-element
    extrema-for-line-drawing-element
    new-y))

(defun compute-extrema-for-text-drawing-element
    (line-drawing-element extrema-for-line-drawing-element)
  (let* ((point (third line-drawing-element))
         (text-reflection-and-rotation
           #+text-element-reflection-rotation
           (when (symbolp (fifth line-drawing-element))
             (fifth line-drawing-element))
           #-text-element-reflection-rotation
           nil
           )
         (scale? (if text-reflection-and-rotation
                     (sixth line-drawing-element)
                     (fifth line-drawing-element)))
         (width-of-icon  (simple-eval-for-icon 'width))
         (height-of-icon (simple-eval-for-icon 'height))
         (magnified-width-of-icon
           (if scale? (magnify width-of-icon (car scale?))
               width-of-icon))
         (magnified-height-of-icon
           (if scale? (magnify height-of-icon (second scale?))
               height-of-icon)))
    (multiple-value-bind (left top right bottom)
        (compute-edges-for-text-drawing-element line-drawing-element)
      (setq left (pin-in-range 0 (point-x point) magnified-width-of-icon))
      (setq right (pin-in-range 0 right magnified-width-of-icon))
      (setq top (pin-in-range 0 top magnified-height-of-icon))
      (setq bottom (pin-in-range 0 bottom magnified-height-of-icon))
      (update-extrema-for-line-drawing-element
        extrema-for-line-drawing-element
        left top)
      (update-extrema-for-line-drawing-element
        extrema-for-line-drawing-element
        right bottom)
      extrema-for-line-drawing-element)))

(defun compute-extrema-for-image-drawing-element
    (image-drawing-element extrema-for-line-drawing-element)
   (let* ((image-name (simple-eval-for-icon (second image-drawing-element)))
          (point? (third image-drawing-element))
          (x0 (if point? (point-x point?) 0))
          (y0 (if point? (point-y point?) 0))
          (image-data? (find-image-data image-name))
          (width-of-image (if image-data? (image-data-width image-data?) 0))
          (height-of-image (if image-data? (image-data-height image-data?) 0))
          (width-of-icon (simple-eval-for-icon 'width))
          (height-of-icon (simple-eval-for-icon 'height))
          ;(scale? (fourth image-drawing-element))
          (max-x
            (pin-in-range 0 (+f x0 width-of-image) width-of-icon))
          (max-y (pin-in-range 0 (+f y0 height-of-image) height-of-icon))
          (min-x (pin-in-range 0 x0 width-of-icon))
          (min-y (pin-in-range 0 y0 height-of-icon)))
     (update-extrema-for-line-drawing-element
       extrema-for-line-drawing-element
       min-x min-y)
     (update-extrema-for-line-drawing-element
       extrema-for-line-drawing-element
       max-x max-y)
     extrema-for-line-drawing-element))

(defun compute-extrema-for-circle-drawing-element
    (line-drawing-element extrema-for-line-drawing-element)
  (let* ((points (cdr line-drawing-element))
         (width-of-icon (simple-eval-for-icon 'width))
         (height-of-icon (simple-eval-for-icon 'height))
         (p1 (first points))
         (p2 (second points))
         (p3 (third points)))
    (when
        (and (=f (length points) 3)
             t ) ;(point-p p1) (point-p p2) (point-p p3))
      (multiple-value-bind
          (min-x min-y max-x max-y)
          (compute-circle-bounding-box
            (point-x p1) (point-y p1)
            (point-x p2) (point-y p2)
            (point-x p3) (point-y p3))
        (update-extrema-for-line-drawing-element
          extrema-for-line-drawing-element
          (pin-in-range 0 min-x width-of-icon)
          (pin-in-range 0 min-y height-of-icon))
        (update-extrema-for-line-drawing-element
          extrema-for-line-drawing-element
          (pin-in-range 0 max-x width-of-icon)
          (pin-in-range 0 max-y height-of-icon))))
    extrema-for-line-drawing-element))

(defmacro circle-drawing-element-p (line-drawing-element)
  `(or (eq (car ,line-drawing-element) 'circle)
       (eq (car ,line-drawing-element) 'filled-circle)))


;;; `extrema-for-line-drawing-element'
;;; Modifies the extrema-for-line-drawing-element,
;;; which should initially be set to (slot-value-list nil nil nil nil)
;;; Should be called from within a evaluating-icon-elements context.

(defun extrema-for-line-drawing-element
    (line-drawing-element extrema-for-line-drawing-element)
  (cond ((text-drawing-element-p line-drawing-element)
         (compute-extrema-for-text-drawing-element
           line-drawing-element extrema-for-line-drawing-element))
        ((image-drawing-element-p line-drawing-element)
         (compute-extrema-for-image-drawing-element
           line-drawing-element extrema-for-line-drawing-element))
        ((circle-drawing-element-p line-drawing-element)
         (compute-extrema-for-circle-drawing-element
           line-drawing-element extrema-for-line-drawing-element))
        (t
         (loop with width-of-icon
               = (simple-eval-for-icon 'width)
               with height-of-icon
               = (simple-eval-for-icon 'height)
               for elt in line-drawing-element
               do
           (cond ((arc-point-p elt)
                  (update-extrema-for-line-drawing-element
                    extrema-for-line-drawing-element
                    (pin-in-range 0 (point-x (second-of-cons elt)) width-of-icon)
                    (pin-in-range 0 (point-y (second-of-cons elt)) height-of-icon)))
                 ((or (power-point-p elt)(constant-point-p elt))
                      (update-extrema-for-line-drawing-element
                        extrema-for-line-drawing-element
                        (pin-in-range 0 (point-x elt) width-of-icon)
                        (pin-in-range 0 (point-y elt) height-of-icon)))
                 ((consp elt)
                  (extrema-for-line-drawing-element
                    elt extrema-for-line-drawing-element)))
               finally
                 (return extrema-for-line-drawing-element)))))




(defmacro compute-bleed-width-for-element (element)
  `(case (car ,element)
     (text 1)
     (lines 1)
     (t 1)))

;;; `extrema-region-for-changing-variables'
;;; Returns a NEW region that must be reclaimed by the caller.


(defun extrema-region-for-changing-variables (element-list
                                               default-variables-list
                                               override-variable-list
                                               normalized-width
                                               normalized-height
                                               changing-variables
                                               old-override-variable-list
                                               delete-non-changing-variables-p)
  (loop with bleed-width = 0
        with clip-width = 1
        with result = nil
        with extrema-list = nil
        with extrema-region = nil
        for element in element-list
        when (and (consp element)
                  (or (and delete-non-changing-variables-p
                           (element-contains-variables-p element old-override-variable-list))
                      (element-contains-variables-p element changing-variables)))
          ;; We need to update variables that are in old-override-variable-list
          ;; but which are not in changing-variables since they will we be
          ;; reverting to default-values, and therefore changing

          do
            (setq extrema-list
                  (evaluating-icon-elements
                    (normalized-width normalized-height default-variables-list override-variable-list)
                    ;;need to check for ordering of override-list ???
                    (extrema-for-line-drawing-element
                      element (slot-value-list nil nil nil nil))))
            (setq bleed-width (compute-bleed-width-for-element element))
            (setq extrema-region
                  (make-region-from-rectangle
                    (pin-in-range 0 (-f (car-of-cons extrema-list) bleed-width)
                                  (-f normalized-width clip-width))
                    (pin-in-range 0 (-f (cadr-of-cons extrema-list) bleed-width)
                                  (-f normalized-height clip-width))
                    (pin-in-range 0 (+f (third extrema-list) bleed-width)
                                  (-f normalized-width clip-width))
                    (pin-in-range 0 (+f (fourth extrema-list) bleed-width)
                                  (-f normalized-height clip-width))))
            (setq bleed-width 0)
            (reclaim-slot-value-list extrema-list)
            (setq result
                  (cond (result
                         (prog1
                             (union-region ;-and-simplify
                               extrema-region
                               result)
                           (reclaim-region extrema-region)
                           (reclaim-region result)))
                        (t extrema-region)))
        finally
          (return result)))

(defun element-contains-variables-p (element variables-plist)
  (cond ((null element)
         nil)
        ((getfq variables-plist element)) ;hmmm pbk
        ((consp element)
         (let ((car-element (car-of-cons element)))
           (unless (eq car-element 'variables)
             (or (element-contains-variables-p car-element variables-plist)
                 (element-contains-variables-p (cdr-of-cons element) variables-plist)))))))






;;; `shift-interval-w'
;;; Destructively modifies the given interval.

(defun shift-interval-w
    (interval delta)
  (setf (interval-left interval)
        (+w (interval-left interval) delta))
  (setf (interval-right interval)
        (+w (interval-right interval) delta)))


;;; `shift-region-w'
;;; Destructively modifies the given region.

(defun shift-region-w
    (region delta-x delta-y)
  (declare (eliminate-for-gsi))
  (dolist (strip (region-strips region))
    (setf (region-strip-top strip)
          (+w (region-strip-top strip) delta-y))
    (unless (=f 0 delta-x)
      (dolist (interval (region-strip-intervals strip))
        (shift-interval-w interval delta-x))))
  (let ((box (region-bounding-box region)))
    (shift-interval-w
      (region-bounding-box-x-interval box) delta-x)
    (shift-interval-w
      (region-bounding-box-y-interval box) delta-y))
  region)

;;; `expand-interval-w'
;;; Destructively modifies the given interval.

(defun expand-interval-r
    (interval delta-left delta-right)
  (setf (interval-left interval)
        (-r (interval-left interval) delta-left))
  (setf (interval-right interval)
        (+r (interval-right interval) delta-right)))


;;; `expand-region-r'
;;; Destructively modifies the given region.

(defun expand-region-r
    (region delta-left delta-top delta-right delta-bottom)
  (declare (eliminate-for-gsi))
  (let ((count 0))
  (dolist (strip (region-strips region))
    (incff count)
    (setf (region-strip-top strip)
          (-r (region-strip-top strip) (if (oddp count) delta-top
                                           (-f delta-bottom))))
    (unless (=f 0 delta-right delta-left)
      (dolist (interval (region-strip-intervals strip))
        (expand-interval-r interval delta-left delta-right)))))
  (let ((box (region-bounding-box region)))
    (expand-interval-r
      (region-bounding-box-x-interval box) delta-left delta-right)
    (expand-interval-r
      (region-bounding-box-y-interval box) delta-top delta-bottom))
  region)



;;; `magnify-interval-w'
;;; Destructively modifies the given interval.

(defun magnify-interval-w
    (interval magnification?)
  (when magnification?
    (setf (interval-left interval)
          (magnify
            (interval-left interval)
            magnification?))
    (setf (interval-right interval)
          (magnify
            (interval-right interval)
            magnification?))))

;;; `magnify-region'
;;; Destructively modifies the given region.

(defun magnify-region
    (region x-magnification? y-magnification?)
  (declare (eliminate-for-gsi))
  (dolist (strip (region-strips region))
    (when y-magnification?
      (setf (region-strip-top strip)
            (magnify
              (region-strip-top strip)
              y-magnification?)))
    (when  x-magnification?
      (dolist (interval (region-strip-intervals strip))
        (magnify-interval-w interval x-magnification?))))
  (let ((box (region-bounding-box region)))
    (magnify-interval-w
      (region-bounding-box-x-interval box)  x-magnification?)
    (magnify-interval-w
      (region-bounding-box-y-interval box)  y-magnification?))
  region)


;;; `orient-region'
;;; Creates a NEW region from the given region.
;;; Does NOT modify or reclaim the given region.

(defun orient-region
    (region orientation width-at-normalized-scale height-at-normalized-scale)
  (multiple-value-bind (left top right bottom)
      (region-bounding-rectangle region)
    (orient-points-for-icon
        orientation
        width-at-normalized-scale
        height-at-normalized-scale
      left top right bottom)
    (psetf left (minw left right)
           top (minw top bottom)
           right (maxw left right)
           bottom (maxw top bottom))
    (make-region-from-rectangle left top right bottom)))


(defmacro icon-is-rotated-p (orientation)
  `(and ,orientation (not (eq ,orientation 'normal))))

;;; `magnify-orient-and-shift-region'
;;; Creates a list of NEW regions that must be reclaimed
;;; by the caller. Consumes old-region.

(defun magnify-orient-and-shift-region
    (old-region delta-x delta-y x-mag? y-mag?
                orientation
                width-at-normalized-scale
                height-at-normalized-scale)
  (when old-region
   (let* ((rotated-p (icon-is-rotated-p orientation))
          (new-region old-region)
          (magnified-region
            (magnify-region new-region x-mag? y-mag?))
          (oriented-region
            (cond (rotated-p
                   (orient-region new-region
                                  orientation
                                  width-at-normalized-scale
                                  height-at-normalized-scale))
                  (t magnified-region)))
          (shifted-region
            (shift-region-w oriented-region delta-x delta-y)))
     (when rotated-p
       (reclaim-region magnified-region))
     shifted-region)))




;;; `compute-extrema-region-for-item'
;;; Used to compute the bounds of elements whose bounds are
;;; changing according to the changing-variable-specs.
;;; Returns a region that must be reclaimed by the caller.
;;; Does NOT consume or reclaim changing-variable-spec.

(defun compute-extrema-region-for-item
    (item changing-variables-plist compute-new-state-p delete-non-changing-variables-p)
  (let* ((icon-description
           (icon-description item))
         (icon-line-drawing-description
           (icon-line-drawing-description icon-description))
         (region-specification?
           (get-polychrome-header-if-any icon-line-drawing-description))
         (variable-specification?
           (get-variable-specification-if-any icon-line-drawing-description))
         (background-specification?
           (get-icon-background-layer-if-any icon-line-drawing-description))
         (stipple?
           (get-icon-stipple-if-any icon-line-drawing-description))
         (default-variables (cdr variable-specification?))
         (icon-attributes-plist (icon-attributes-plist item))
         (x-magnification (getfq icon-attributes-plist 'x-magnification))
         (y-magnification (getfq icon-attributes-plist 'y-magnification))
         (reflection-and-rotation (getfq icon-attributes-plist 'reflection-and-rotation))
         (width  (width-of-block item)) ; use (width-of-icon icon-description) and
         (height (height-of-block item));     height-of-icon instead !
         (orientation-code (get-orientation-code reflection-and-rotation))
         (normalized-width (if x-magnification
                             (inverse-magnify
                               (oriented-x-value width height orientation-code)
                                x-magnification)
                              (oriented-x-value width height orientation-code)))
         (normalized-height (if y-magnification
                              (inverse-magnify
                                (oriented-y-value width height orientation-code)
                                y-magnification)
                              (oriented-y-value width height orientation-code)))
         (computed-values-plist
           (get-computed-values-plist icon-attributes-plist))
         (element-list
           (get-element-list
             icon-line-drawing-description
             region-specification?
             variable-specification?
             background-specification?
             stipple?))
         (region-to-update
           (extrema-region-for-changing-variables
             element-list
             default-variables
             (cond (compute-new-state-p
                    changing-variables-plist)
                   (t computed-values-plist))
             normalized-width normalized-height
             changing-variables-plist
             computed-values-plist
             delete-non-changing-variables-p)))
    region-to-update))




(defun region-has-positive-area-p (region)
  (multiple-value-bind (left top right bottom)
      (region-bounding-rectangle region)
    (let ((width (-r right left))
          (height (-r bottom top)))
      (and (>r width 0) (>r height 0)))))
;; see also empty-region-p


(defun update-images-of-region-of-block-old
    (item erase-p region bleed-width)
  (when (or (block-is-currently-being-dragged-p item)
            (region-has-positive-area-p region))
    (multiple-value-bind (left top right bottom)
        (region-bounding-rectangle region)
      (update-images-of-rectangle-of-block
        item erase-p
        (-r left bleed-width) (-r top bleed-width)
        (+r right bleed-width) (+r bottom bleed-width)))))

#+development
(defparameter update-images-call-count 0)
#+development
(defparameter update-images-backtrace-log nil)
#+development
(defun reset-update-images-count-and-backtrace ()
  (setf update-images-call-count 0)
  (setf update-images-backtrace-log nil))


;;; `update-images-of-region-of-block'
;;;  Paint mode only please!!!
;;;  Only call this from power icons please!!!
;;;  not checking if showing here, or checking if dragging here
;;;   or if the workspac exist, because we already checked that
;;;   the item is showing-p
;;;  Created for optimization.

(defun update-images-of-region-of-block
    (block erase-p region bleed-width)
  (declare (ignore bleed-width)) ; need to deal with this pbk
  ;;(incf update-images-call-count)
  ;;(push (backtrace) update-images-backtrace-log)
  (when (region-has-positive-area-p region)
    (let ((workspace? (get-workspace-if-any-macro block))
          (current-drawing-priority
            (if erase-p :draw-as-late-as-possible current-drawing-priority)))
      (when (and workspace? (workspace-showing-p workspace? t))
        (merge-change-to-block workspace? block 'region region)))))

(defparameter update-images-of-regions-of-block-tracing nil)


(defun update-images-of-block-for-region
    (item erase-p region)
  (when region
    (let ((region-invalidation-is-preferred
            (block-is-currently-being-dragged-p item)))
      (cond ((or (render-frame-in-xor-overlay-p item) (xor-mode-p))
             (update-images-of-region-of-block-old
               item erase-p region 3))
            (t
             (update-images-of-region-of-block
               item erase-p region 3))))))


(defun undefined-icon-variable-value-error-message
    (variable-spec default-variables)
  (invalid-icon-variable-value-error-message
    (car variable-spec)
    (cadr variable-spec)
    (twith-output-to-text-string
      (tformat "~s is an undefined icon variable.~%  Variables declaration--> "
               (car variable-spec))
      (if default-variables
          (write-variable-specification-list default-variables)
          (tformat "NOT DEFINED")))))

(defun invalid-icon-variable-value-error-message (variable-name variable-value reason)
  (tformat-text-string
    #w"ERROR: Can not change the value of ~a to ~a. ~% REASON: ~a. ~% "
    variable-name variable-value reason))



;;; `change-item-variable-value'
;;;  Does NOT modify or reclaim variable-specs.

(defun change-item-variable-value
    (item variables-plist note-as-kb-state-change?
          delete-non-changing-variables-p)
  (let ((showing-p (showing-p item nil))
        icon-attributes-plist reflection-and-rotation orientation-code
        width height oriented-width oriented-height
        x-scale y-scale
        region-to-draw old-region region-to-erase
        region-to-erase-w region-to-draw-w
        left-edge-of-block top-edge-of-block
        variable-change-error?
        error-text?)
    (when showing-p
      (setq icon-attributes-plist
            (icon-attributes-plist item))
      (setq reflection-and-rotation
            (getfq icon-attributes-plist 'reflection-and-rotation))
      (setq orientation-code (get-orientation-code  reflection-and-rotation))
      (setq width (width-of-block item))
      (setq height (height-of-block item))
      (setq oriented-width (oriented-x-value width height orientation-code))
      (setq oriented-height (oriented-y-value width height orientation-code))
      (setq x-scale
            (getfq  icon-attributes-plist 'x-magnification))
      (setq y-scale
            (getfq icon-attributes-plist 'y-magnification))
      (setq region-to-draw
            (compute-extrema-region-for-item item variables-plist t
                                             delete-non-changing-variables-p))
      (setq old-region
            (compute-extrema-region-for-item item variables-plist nil
                                             delete-non-changing-variables-p))
      (setq region-to-erase
            old-region)
      (setq left-edge-of-block (left-edge-of-block item))
      (setq top-edge-of-block (top-edge-of-block item))
      (setq region-to-erase-w
            (magnify-orient-and-shift-region
              region-to-erase
              left-edge-of-block
              top-edge-of-block
              x-scale y-scale
              reflection-and-rotation
              oriented-width oriented-height))
      (setq region-to-draw-w
            (magnify-orient-and-shift-region
              region-to-draw
              left-edge-of-block
              top-edge-of-block
              x-scale y-scale
              reflection-and-rotation
              oriented-width oriented-height))
      (when nil ;(and region-to-draw-w region-to-erase-w)
        (setq region-to-erase-w
              (prog1
                  (subtract-region region-to-erase-w region-to-draw-w)
                (reclaim-region region-to-erase-w))))
      (when nil ;(and region-to-draw-w region-to-erase-w)
        (setq region-to-draw-w
              (prog1
                  (subtract-region region-to-draw-w region-to-erase-w)
                (reclaim-region region-to-draw-w)))))

    (with-updates-to-transfer-representations (item)
      (when showing-p
        (update-images-of-block-for-region item t region-to-erase-w))
      ;; should erase-p be 'delete ????
      (setf variable-change-error?
            (set-icon-variables-internal
              item note-as-kb-state-change?
              variables-plist
              delete-non-changing-variables-p))
      (cond ((eq (car variable-change-error?) 'error)
             ;;  outer function should have handled this.
             (setf error-text?
                   (undefined-icon-variable-value-error-message
                     (second variable-change-error?)
                     (third variable-change-error?))))
            (t
             (when showing-p
               (update-images-of-block-for-region item nil region-to-draw-w)))))

    ;; Update native item views, Showing-p not required.
    (update-item-views item)

    (when showing-p
      (reclaim-region region-to-erase-w)
      (reclaim-region region-to-draw-w))
    error-text?))

(defun-simple bad-value-for-variable? (item variable-name new-value)
  (loop  with icon-description
         = (icon-description item)
         with line-drawing-description
           = (icon-line-drawing-description icon-description)
         with polychrome-header?
           = (let ((header? (car line-drawing-description)))
               (if (and (consp header?)
                        (eq (car-of-cons header?) 'polychrome))
                   header?))
         with variable-header?
           = (get-variable-specification-if-any line-drawing-description)
         with background-header?
           = (get-icon-background-layer-if-any line-drawing-description)
         with stipple?
           = (get-icon-stipple-if-any line-drawing-description)
         with variables-plist
           = (and variable-header? (cdr-of-cons variable-header?))
         with old-value?
           = (getfq variables-plist variable-name)
         initially
           (when old-value?
             (setf (getf variables-plist variable-name) new-value))
         with element-list
           = (get-element-list
               line-drawing-description
               polychrome-header?
               variable-header?
               background-header?
               stipple?)
         for element in element-list
         as bad-variable?
            = (element-contains-bad-variable?
                element
                variables-plist)
         thereis
         (when bad-variable?
           (when old-value?
             (setf (getf variables-plist variable-name) old-value?))
           (gensym-push new-value bad-variable?)
           (gensym-push variable-name bad-variable?)
           (gensym-push element bad-variable?))
         finally
           (when old-value?
             (setf (getf variables-plist variable-name) old-value?))))


(defun undefined-variable? (variable-specs default-variables)
  (loop for (variable-name variable-value) on variable-specs by 'cddr
        unless (or (getfq default-variables variable-name)
                   (memq variable-name '(width height)))
          return
          (slot-value-list variable-name variable-value)))



(defun change-variables-of-item
    (item variables-plist delete-non-changing-variables-p)
  (let* ((bad-variable?
           ;; make more efficient later by checking all at once.
           (loop for (variable-name  variable-value) on variables-plist by 'cddr
                 thereis
                 (bad-value-for-variable? item variable-name variable-value)))
         (bad-variable-name (cadr bad-variable?))
         (bad-variable-value (third bad-variable?))
         (bad-variable-reason? (fourth bad-variable?))
         (icon-description (icon-description item))
         (icon-line-drawing-description
           (icon-line-drawing-description icon-description))
         (variable-specification?
           (get-variable-specification-if-any icon-line-drawing-description))
         (default-variables (cdr variable-specification?))
         (undefined-variable?
           (undefined-variable? variables-plist default-variables))
         error-string?)
    (cond (bad-variable?
           (setq error-string?
                 (invalid-icon-variable-value-error-message
                   bad-variable-name
                   bad-variable-value
                   bad-variable-reason?))
           (reclaim-gensym-list bad-variable?)
           error-string?)
          (undefined-variable?
           (setq error-string?
                 (undefined-icon-variable-value-error-message
                   undefined-variable? default-variables))
           (reclaim-slot-value-list undefined-variable?)
           error-string?)
          (t
           (change-item-variable-value
             item
             variables-plist
             t  ;note-kb-state-changes-via-system-procedures?
             delete-non-changing-variables-p)))))



;;; `g2-set-icon-variable-value'
;;; Power Icons system procedure.

(defun-for-system-procedure g2-set-icon-variable-value
    ((item item) (variable-name symbol) (variable-value datum))
   (let* ((variable-spec-for-stack-evaluator
            (proc-list variable-name variable-value))
          (error-text?
            (change-variables-of-item
              item
              variable-spec-for-stack-evaluator
              nil)))
     (reclaim-proc-list variable-spec-for-stack-evaluator)
     (when error-text?
       (stack-error cached-top-of-stack error-text?))))


(def-copy-tree-including-leaves-using-x-conses eval)


;;; `icon variable conclude action'
;;;

(def-virtual-attribute icon-variables
    ((class entity) (or (structure) (no-item)) ())
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) (allocate-evaluation-structure nil))

  :getter  ((block)
            (let ((icon-description (icon-description block)))
              (and icon-description
                   (let* ((icon-line-drawing-description
                            (icon-line-drawing-description icon-description))
                          (default-values-plist
                              (cdr (get-variable-specification-if-any
                                     icon-line-drawing-description)))
                          (icon-attributes-plist (icon-attributes-plist block))
                          (default-width  (width-of-icon icon-description))
                          (default-height (height-of-icon icon-description))
                          (current-width (or (getfq icon-attributes-plist 'width)
                                             default-width))
                          (current-height (or (getfq icon-attributes-plist 'height)
                                              default-height))
                          (computed-values-plist
                            (get-computed-values-plist icon-attributes-plist))
                          (merged-variable-plist-without-width-height
                            (merge-variable-plists computed-values-plist
                                                   default-values-plist))
                          (merged-variable-plist
                            (progn
                              (eval-push current-height merged-variable-plist-without-width-height)
                              (eval-push 'height merged-variable-plist-without-width-height)
                              (eval-push current-width merged-variable-plist-without-width-height)
                              (eval-push 'width merged-variable-plist-without-width-height)
                              merged-variable-plist-without-width-height))
                          (result
                            (cond ((null merged-variable-plist)
                                   nil)
                                  ((consp merged-variable-plist)
                                   (allocate-evaluation-structure
                                     merged-variable-plist))
                                  (t  ; The symbol case.
                                   #+development
                                   (cerror "go on"
                                           "icon-variable failure - call PBK")
                                   merged-variable-plist))))
                     result))))
  :setter ((block new-icon-variables)
           (let ((icon-description (icon-description block)))
             (cond
               (icon-description
                (let* ((default-width  (width-of-icon icon-description))
                       (default-height (height-of-icon icon-description))
                       (icon-attributes-plist (icon-attributes-plist block))
                       (current-width (or (getfq icon-attributes-plist 'width)
                                          default-width))
                       (current-height (or (getfq icon-attributes-plist 'height)
                                           default-height)))
                  (cond ((evaluation-structure-p new-icon-variables)
                         (let* ((new-variables-plist
                                  (convert-structure-to-plist new-icon-variables))
                                (new-width
                                  (or (getfq new-variables-plist 'width)
                                      default-width))
                                (new-height
                                  (or (getfq new-variables-plist 'height)
                                      default-height))
                                error-text?)
                           (cond ((not (fixnump new-width))
                                  (setq error-text?
                                        (invalid-icon-variable-value-error-message
                                          'width new-width
                                          (twith-output-to-text-string
                                            (tformat "~s is not an integer" new-width)))))

                                 ((not (fixnump new-height))
                                  (setq error-text?
                                        (invalid-icon-variable-value-error-message
                                          'height new-height
                                          (twith-output-to-text-string
                                            (tformat "~s is not an integer" new-height)))))
                                 ((setq error-text? (check-icon-size new-width new-height))
                                  (setq error-text?
                                        (prog1 (tformat-text-string "ERROR: ~a" error-text?)
                                          (reclaim-text-string error-text?))))
                                 (t
                                  (when (not (=f new-width current-width))
                                    (change-block-width block new-width
                                                        current-width
                                                        (=f new-width default-width)))
                                  (when (not (=f new-height current-height))
                                    (change-block-height block new-height
                                                         current-height
                                                         (=f new-height default-height)))
                                  (setq error-text?
                                        (change-variables-of-item block new-variables-plist t))
                                  (when (null error-text?)
                                    (when g2-has-v5-mode-windows-p
                                      (send-ws-representations-item-icon-variables-change
                                        block
                                        new-icon-variables))
                                    (update-subscriptions-from-virtual-attribute-change
                                      block (virtual-attribute 'icon-variables) nil))))
                           (reclaim-slot-value-list new-variables-plist)
                           error-text?))
                        ((null new-icon-variables)
                         (let ((computed-values-alist
                                 (and icon-attributes-plist
                                      (get-computed-values-plist icon-attributes-plist))))
                           (when (not (=f current-width default-width))
                             (change-block-width block default-width current-width t))
                           (when (not (=f current-height default-height))
                             (change-block-height block default-height current-height t))
                           (when computed-values-alist
                             (change-icon-variables block nil)
                             (remove-kb-state-variable-record block 'variables)
                             (update-images-of-block block nil t)))
                         (when g2-has-v5-mode-windows-p
                           (send-ws-representations-item-icon-variables-change
                             block
                             nil))
                         (update-subscriptions-from-virtual-attribute-change
                           block (virtual-attribute 'icon-variables) nil)
                         nil)
                        (t
                         (tformat-text-string
                           "Icon-variables must be a structure, so ~NE ~
                            cannot be put into ~NF."
                           new-icon-variables block)))))
               (new-icon-variables
                (tformat-text-string
                  "Cannot conclude icon-variables for ~NF" block))))))

;;; `g2-set-icon-decaching-parameters'
;;; This system procedure is used to control how icon-renderings
;;; are decached, on a class by class basis.  Users can specify
;;; the maximum number of icon-renderings that will be stored in
;;; the icon-description structure for this class.  The number
;;; of renderings to decache, when that limit is reached, can also
;;; be specified.  The defaults/minimum values are given by the
;;; constants `default-number-of-renderings-for-bulk-delete'
;;; and `default-maximum-renderings-for-class', which are the
;;; the values used for all system defined classes.  These values
;;; must be integers.  The maximum number of renderings must be atleast
;;; ten greater than the number of icons to decache, and inappropriate
;;; values will be politely coerced.

(defun-for-system-procedure g2-set-icon-decaching-parameters
    (class-definition maximum-renderings-for-class
                      number-of-renderings-to-decache-at-a-time)
  (cond ((not (and (fixnump maximum-renderings-for-class)
                   (fixnump number-of-renderings-to-decache-at-a-time)))
         (stack-error
           cached-top-of-stack
           "maximum-renderings-for-class and number-of-renderings-to-decache-at-a-time must be integers in call to g2-set-decaching-parameters"
           class-definition))
        ((not (and (framep class-definition)
                   (frame-of-class-p class-definition 'class-definition)))
         (stack-error
           cached-top-of-stack
           "~NF is not a class-definition in call to g2-set-decaching-parameters"
           class-definition))
        ((<=f maximum-renderings-for-class
              number-of-renderings-to-decache-at-a-time)
         (stack-error cached-top-of-stack
                      "maximum-renderings-for-class, ~s, must be greater than ~
                       number-of-renderings-to-decache-at-a-time, ~s"
                      maximum-renderings-for-class
                      number-of-renderings-to-decache-at-a-time))
        (t
          (let* ((number-to-decache
                   (maxf #.default-number-of-renderings-for-bulk-delete
                         number-of-renderings-to-decache-at-a-time))
                 (maximum-renderings
                   (maxf maximum-renderings-for-class
                         (+f number-to-decache 10))))
            (setf (maximum-renderings-for-class class-definition)
                  maximum-renderings)
            (setf (number-of-renderings-for-bulk-delete class-definition)
                  number-to-decache)))))


;;; The `g2-set-icon-bitmap-decaching-parameters' system procedure is used to
;;; control how bitmaps used for icons are cached and decached.  This function
;;; is similar to G2-SET-ICON-DECACHING-PARAMETERS.

(defun-for-system-procedure g2-set-icon-bitmap-decaching-parameters
    (maximum-icon-bitmaps maximum-icon-bitmap-memory)
  (unless (and (fixnump maximum-icon-bitmaps)
               (fixnump maximum-icon-bitmap-memory))
    (stack-error cached-top-of-stack
                 "maximum-icon-bitmaps and maximum-icon-bitmap-memory must be ~
                  positive integers in call to g2-set-icon-bitmap-decaching-parameters"))
  (unless (and (pluspf maximum-icon-bitmaps)
               (pluspf maximum-icon-bitmap-memory))
    (stack-error cached-top-of-stack
                 "maximum-icon-bitmaps, ~s, and maximum-icon-bitmap-memory, ~s, ~
                  must be positive integers in call to g2-set-icon-bitmap-decaching-parameters"
                 maximum-icon-bitmaps
                 maximum-icon-bitmap-memory))
  (unless (<f maximum-icon-bitmaps maximum-icon-bitmap-memory)
    (stack-error cached-top-of-stack
                 "maximum-icon-bitmaps, ~s,  must be less than maximum-icon-bitmap-memory, ~
                  ~s, in call to g2-set-icon-bitmap-decaching-parameters"
                 maximum-icon-bitmaps
                 maximum-icon-bitmap-memory))
  ;; Now that the fatal problems are out of the way, warn about silly values.
  (unless (<=f 100 maximum-icon-bitmaps 5000)
    (warning-message* 3 "maximum-icon-bitmaps, ~s, should be between 100 and 5000 ~
                         in call to g2-set-icon-bitmap-decaching-parameters, "
                 maximum-icon-bitmaps))
  (unless (>=f maximum-icon-bitmap-memory 1024)
    (warning-message* 3 "maximum-icon-bitmap-memory, ~s, should be at least 1024 ~
                         in call to g2-set-icon-bitmap-decaching-parameters."
                 maximum-icon-bitmap-memory))

  (setq default-maximum-icon-bitmaps maximum-icon-bitmaps
        default-maximum-icon-bitmap-memory maximum-icon-bitmap-memory))


;;; Note that this does NOT copy the leaves of the structure when
;;; placing them into the plist.
(defun convert-structure-to-plist (structure)
  (loop with result = nil
        for (variable . value) being each evaluation-structure-pair of structure
        do
    (slot-value-push
      variable
      result)
    (slot-value-push
      value
      result)
        finally
          (return (nreverse result))))


(defun merge-variable-plists (override-plist default-plist)
  (loop with new-list = nil
        for (name default-value) on default-plist by 'cddr
        as overridden-value? = (getfq override-plist name)
        do
    (eval-push name new-list)
    (cond (overridden-value?
           (eval-push (copy-evaluation-value overridden-value?) new-list))
          (t
           (eval-push (copy-evaluation-value default-value)
                      new-list)))
        finally
          (return (nreverse new-list))))



;;; g2-make-item-opaque and g2-clear-item-opaque are temporary
;;;  system-procedures for dwr to use at GUS-96. Do NOT become
;;;  dependent upon them and use cautiously.(pbk 6/6/96)

(defun-for-system-procedure g2-make-item-opaque
    ((item item))
  (set-opaque-block item))

(defun-for-system-procedure g2-clear-item-opaque
    ((item item))
  (clear-opaque-block item))

;;; g2-make-item-opaque and g2-clear-item-opaque are temporary
;;;  system-procedures for dwr to use at GUS-96. Do NOT become
;;;  dependent upon them and use cautiously.(pbk 6/6/96)


(defun change-block-width (entity new-width old-width default-value-p)
  (let ((delta-width (-w new-width old-width))
        (showing-p (showing-p entity t)))
    (with-updates-to-transfer-representations (entity)
      (when showing-p
        (update-images-of-block entity t t))
      (change-icon-attribute entity 'width
                             (if default-value-p nil new-width))
      (when (slot-group-for-block? entity)
        (adjust-edges-of-instance entity delta-width 0))
      (when showing-p
        (update-images-of-block entity nil t)))
    (update-item-views entity)))

(defun change-block-height (entity new-height old-height default-value-p)
  (let ((delta-height (-f new-height old-height))
        (showing-p (showing-p entity t)))
    (with-updates-to-transfer-representations (entity)
      (when showing-p
        (update-images-of-block entity t t))
      (change-icon-attribute entity 'height
                             (if default-value-p nil new-height))
      (when (slot-group-for-block? entity)
        (adjust-edges-of-instance entity 0 delta-height))
      (when showing-p
        (update-images-of-block entity nil t)))
    (update-item-views entity)))


;;;; System Procedures for Changing Text Boxes





;;; `With-changes-to-text-box' ...

(defmacro with-changes-to-text-box ((text-box) &body body)
  (avoiding-variable-capture (text-box)
    `(progn
       (erase-images-of-block ,text-box t)
       (prog1 (progn . ,body)
         (reformat-text-box-in-place ,text-box)
         ;; may need to be called after drawing; I don't remember/we're not
         ;; sure!
         (enlarge-workspace-for-block-rectangle-if-necessary ,text-box nil)
         (draw-images-of-block ,text-box t)))))



;;; The functions `make-original-value-for-text-box-font-kb-state-change' and
;;; `restore-original-value-for-text-box-font-kb-state-change' implement the
;;; "methods" to save and restore the "font" of a text box prior to its being
;;; changed by user code, namely by G2-set-font-size-of-text-box, the system
;;; procedure for changing the font size and/or magnification of a text box.
;;; These are called by note-kb-state-change and undo-kb-state-change,
;;; respectively.
;;;
;;; This pair of functions saves and restores the text box's text-box-format,
;;; and x/y modifications, if any, in the text box's text-cell plist.
;;;
;;; The x/y magnifications stored are copied as slot values for storage in the
;;; kb-state-change-plist of the frame.  And they are copied again for storage
;;; back into the text-cell plist.  This works out because both plists are
;;; unshared and subject to reclamation as slot values.

(defun make-original-value-for-text-box-font-kb-state-change (text-box)
  (let ((text-box-format (text-box-format text-box))
        (plist (text-cell-plist-for-text-box text-box)))
    (slot-value-list
      text-box-format
      (copy-for-slot-value (getf plist 'x-magnification?))
      (copy-for-slot-value (getf plist 'y-magnification?)))))


(defun restore-original-value-for-text-box-font-kb-state-change
    (text-box original-value)
  (let* ((text-box-format (first original-value)) ; see code in KB-SAVE2,
         (x-magnification? (second original-value)) ; fn: note-kb-state-change
         (y-magnification? (third original-value))
         (plist (text-cell-plist-for-text-box text-box))
         (x-mag-same-p (eql (getfq-macro plist 'x-magnification?)
                            x-magnification?))
         (y-mag-same-p (eql (getfq-macro plist 'y-magnification?)
                            y-magnification?))
         (format-same-p (eq (text-box-format text-box) text-box-format)))
    (unless (and format-same-p x-mag-same-p y-mag-same-p)
      (with-changes-to-text-box (text-box)
        (setf (text-box-format text-box) text-box-format)
        (change-text-box-property
          text-box 'x-magnification
          (copy-for-slot-value x-magnification?))
        (change-text-box-property
          text-box 'y-magnification
          (copy-for-slot-value y-magnification?)))
      (when g2-has-v5-mode-windows-p
        (unless format-same-p
          (send-ws-representations-item-virtual-attribute-change
            text-box (virtual-attribute 'format-type) nil))
        (unless x-mag-same-p
          (send-ws-representations-item-virtual-attribute-change
            text-box (virtual-attribute 'text-x-magnification) nil))
        (unless y-mag-same-p
          (send-ws-representations-item-virtual-attribute-change
            text-box (virtual-attribute 'text-y-magnification) nil))))))



;;; `Require-text-box-arg-to-system-procedure' signals a stack error if text-box
;;; is not a subclass of text box.

(defun require-text-box-arg-to-system-procedure (text-box)
  (when (not (frame-of-class-p text-box 'text-box))
    (stack-error
      cached-top-of-stack
      "~NF is not a text box." text-box)))


;;; `Require-text-box-subclass-arg-to-system-procedure' signals a stack error if
;;; text-box is not a subclass of text box.

(defun require-text-box-subclass-arg-to-system-procedure
    (text-box-subclass-candidate)
  (when (not (subclassp text-box-subclass-candidate 'text-box))
    (stack-error
      cached-top-of-stack
      "~NF is not a text-box class."
      text-box-subclass-candidate)))


;;; `Minimum-magnification-imposable-by-sysprocs-on-text-boxes' and
;;; `maximum-magnification-imposable-by-sysprocs-on-text-boxes' are constant,
;;; unshared gensym floats that set the range of legal user magnifications,
;;; currently [.125 .. 4.0].
;;;
;;; Note that changes that narrow this range can potentially break user code,
;;; and should also, in general, never be needed.  Any changes here should
;;; at least be dated.  The current values went into effect with the first
;;; release of system procedure for changing magnification: 12/19/94.
;;;
;;; `Restrict-font-magnification-to-legal-range' restricts factor, as supplied
;;; by the user of the font changing system procedure, to the legal range.  The
;;; factor arg must be a number (i.e., including fixnums).  The result is always
;;; a float, coerced if necessary.
;;;
;;; `Convert-to-font-magnification-in-legal-range' does the same, except that it
;;; returns its result as a gensym magnification.

(defparameter minimum-magnification-imposable-by-sysprocs-on-text-boxes
  minimum-magnification-for-text-boxes)
(defparameter maximum-magnification-imposable-by-sysprocs-on-text-boxes
  maximum-magnification-for-text-boxes)

(defun restrict-font-magnification-factor-to-legal-range (factor)
  (maxe minimum-magnification-imposable-by-sysprocs-on-text-boxes
        (mine maximum-magnification-imposable-by-sysprocs-on-text-boxes
              (coerce-to-gensym-float
                (if (slot-value-number-p factor)
                    (slot-value-number-value factor)
                    factor)))))


(defun convert-to-font-magnification-in-legal-range (factor)
  (convert-to-magnification
    (restrict-font-magnification-factor-to-legal-range factor)))







;;;; System Procedure for Changing the "Font" of a Text Box



;;; `G2-set-font-size-of-text-box' is the lisp side of the system procedure of the
;;; same name.
;;;
;;; It takes a text box and a symbol naming a legal font (aka, font size) plus
;;; an x and y magnification factor to be applied to the font size (i.e., 1 = no
;;; magnification).
;;;
;;; X-magnification and y-magnification should be be a legal font magnification
;;; factor, which is an integer or float in the range [0.125 .. 4.0].
;;;
;;; If font-size, x-magnification, and y-magnification already correspond to the
;;; current font, or the font-size is not a legal font size, this does not
;;; perform any action whatsoever.  X-magnification and y-magnification are
;;; pinned to the legal range shown above.
;;;
;;; Otherwise, this changes to specified font size, reformatting the text and
;;; updating all graphics accordingly.
;;;
;;; In either case, this returns as its three values the final font-size,
;;; x-magnification, and y-magnification of the text box.
;;;
;;; Currently defined legal values for font-size are:
;;;
;;;    SMALL, LARGE, EXTRA-LARGE
;;;
;;;
;;; If text-box is not an instance of the class text-box, this signals a stack
;;; error with a fitting message.  Note that text-box is unfortunately not a
;;; user class.  For purposes of describing the input, the user class is either
;;; STATEMENT or MESSAGE or FREE-TEXT or BORDERLESS-FREE-TEXT of TEXT-INSERTER
;;; ... [Did I miss any?  Sad!]
;;;
;;; `G2-get-font-of-text-box' is the lisp side of the system procedure of the
;;; same name.
;;;
;;; Both of these functions return the following three values:
;;;
;;;    (1) the font size of text-box;
;;;    (2) the x-magnification of text-box; and
;;;    (3) the y-magnfication of text-box
;;;
;;; These system procedures are being instituted for 4.0 Beta [Phase 2] in the
;;; sources as of 12/19/94.

(defun-void g2-set-font-of-text-box-1 (text-box font-size x-magnification? y-magnification?)
  (with-temporary-gensym-float-creation g2-set-font-of-text-box-1
    (let* ((x-magnification (cond ((null x-magnification?)
                                   1.0)
                                  ((evaluation-float-p x-magnification?)
                                   (evaluation-float-value x-magnification?))
                                  (t
                                   x-magnification?)))
           (y-magnification (cond ((null y-magnification?)
                                   1.0)
                                  ((evaluation-float-p y-magnification?)
                                   (evaluation-float-value y-magnification?))
                                  (t
                                   y-magnification?)))
           (text-box-format-name (frame-class-case text-box
                                   (message 'large-message-format)
                                   (text-inserter 'scrap-format)
                                   (t (default-text-box-format-name text-box))))
           (new-format-frame?
             (if (memq font-size '(small large extra-large))
                 (get-or-make-format-frame
                   (choose-font-format-per-font-size
                     text-box-format-name ; NOTE A
                     font-size)))))
      (when new-format-frame?
        (unless (font-spec-equal-for-system-procedure
                  text-box new-format-frame?
                  x-magnification y-magnification)
          (let ((do-not-note-permanent-changes-p
                   note-kb-state-changes-via-system-procedures?))
            (when note-kb-state-changes-via-system-procedures?
              (note-kb-state-change text-box 'text-box-font))
            (with-changes-to-text-box (text-box)
              (setf (text-box-format text-box) new-format-frame?)
              (when g2-has-v5-mode-windows-p
                (send-ws-representations-item-virtual-attribute-change
                  text-box (virtual-attribute 'format-type) nil))
              (set-font-magnification-of-text-box-for-system-procedure
                text-box x-magnification y-magnification))))))))

(defun-for-system-procedure g2-set-font-of-text-box
    ((text-box item) (font-size symbol)
     (x-magnification number) (y-magnification number))
  (declare (values symbol number number)
           (keeps-g2-local-variables-valid t))
  (require-text-box-arg-to-system-procedure text-box)
  (g2-set-font-of-text-box-1 text-box font-size x-magnification y-magnification)
  (get-font-of-text-box-for-system-procedure text-box))

(define-system-rpc-access (g2-set-font-of-text-box (symbol ;the font
                                                     number ;the x-magnification factor
                                                     number)) ;the y-magnification factor
    ((text-box (class item))
     (font-size symbol)
     (x-mag number)
     (y-mag number))
  (g2-set-font-of-text-box text-box font-size x-mag y-mag))

;; NOTE A: (pbk 2/6/96) Changed text-box-format-name from  'large-message-format
;; to a class specific format.
;; Also fixed a bug in 'set-font-magnification-of-text-box-for-system-procedure.


(defun-for-system-procedure g2-get-font-of-text-box ((text-box item))
  (declare (values symbol number number)
           (keeps-g2-local-variables-valid t))
  (require-text-box-arg-to-system-procedure text-box)
  (get-font-of-text-box-for-system-procedure text-box))

(define-system-rpc-access (g2-get-font-of-text-box (symbol ;the font
                                                     number ;the x-magnification factor
                                                     number)) ;the y-magnification factor
    ((text-box (class item)));can we do more type checking?
  (g2-get-font-of-text-box text-box))

;; Issues/Bugs
;;
;; We don't signal for a bugus font size.  Neither do the rotate sysproc's
;; above.  The main reason is that we will probably some day expand or change
;; the set of legal choices, and having a signalling policy limit the reasonable
;; way for us to do so.  It's also true that signalling is kind a big pain at
;; times for users to deal with.

;; Consider upgrading the user myth of BIG being a "font" by saying that
;; BIGx1.5x1.7 can also be a "font", with x and y magnifcation being 1.5 and
;; 1.7, respectively. (MHD 12/19/94)
;;
;; We currently don't directly support the concept of "null magnification",
;; i.e., unspecified magnification falling through to the magnification in the
;; format.  If there's no magnification on the plist, then we give the
;; magnification on the text box format (always nil now in practice), and if
;; there's still none, we give 1.0.  Now, if they change away from the default
;; and then back, we currently keep the equivalent of 1.0 on the plist as the
;; magnification.  What else should we do?  We could replace it with nil (and
;; then, remove the property) if that property is equivalent to the default.
;; That would lose if/when we supported changing the format and/or supported
;; real overrides in the sense we have have internally.  This is analagous to
;; slot values vs. non-default values, in the semantic issues area.  This is
;; particularly analagous to lookup slots in the space utilization issues area.
;; For now, we shall restore the default and reclaim the space.  I think the
;; space savings may be too important to ignore for some future, unspecified
;; incompatibility; subject to review/revision at some future date. This is done
;; in set-font-magnification-of-text-box-for-system-procedure. (MHD 12/19/94)
;;
;; Reformatting is not leaving full margins in the right-hand side!
;;
;; We currently don't observe any user restrictions.
;;
;; We currently don't save/restore KB state changes based on this change.





;;; `Font-spec-equal-for-system-procedure' .... Is true if new-format-frame?  is
;;; the same as the current format frame of text box, and x- and y-magnification
;;; are the current font magnifications for text-box.  X-magnification and
;;; y-magnification are either integers or gensym floats.  If not true, the result
;;; is nil (false).
;;;
;;; This is for internal use by the system procedure for changing the font of a
;;; text box.

(defun-simple font-spec-equal-for-system-procedure
    (text-box new-format-frame? x-magnification y-magnification)
  (and (eq (text-box-format text-box) new-format-frame?)
       (with-temporary-gensym-float-creation
           font-spec-equal-for-system-procedure
         (and
           (=e (get-x-magnification-of-text-box-for-system-procedure text-box)
               (restrict-font-magnification-factor-to-legal-range x-magnification))
           (=e (get-y-magnification-of-text-box-for-system-procedure text-box)
               (restrict-font-magnification-factor-to-legal-range y-magnification))))))


;;; `Get-font-of-text-box-for-system-procedure' returns three values:
;;;
;;;    (1) the font of text-box (a symbol);
;;;    (2) the x-magnification factor (a gensym-float); and
;;;    (3) the y-magnification factor (a gensym-float)

(defun get-font-of-text-box-for-system-procedure (text-box)
  (values
    (determine-font-size-per-format
      (text-box-format text-box)
      (frame-class-case text-box
        (message 'large-message-format) ; JED 12/28/95 msgs seem to be "special"
        (text-inserter 'scrap-format)
        (t (default-text-box-format-name text-box))))
    (get-x-magnification-of-text-box-for-system-procedure text-box)
    (get-y-magnification-of-text-box-for-system-procedure text-box)))


(defmacro get-default-x-magnification-of-text-box-format (text-box-format)
  `(or (text-cell-x-magnification? ,text-box-format)
       1.0))

(defmacro get-default-y-magnification-of-text-box-format (text-box-format)
  `(or (text-cell-y-magnification? ,text-box-format)
       1.0))


(defun-void set-font-magnification-of-text-box-for-system-procedure
    (text-box x-magnification-factor y-magnification-factor)
  (let* ((valid-x-magnification-factor
           (restrict-font-magnification-factor-to-legal-range
             x-magnification-factor))
         (valid-y-magnification-factor
           (restrict-font-magnification-factor-to-legal-range
             y-magnification-factor))
         (new-x-value-p (not (=e valid-x-magnification-factor
                                 (get-x-magnification-of-text-box-for-system-procedure text-box))))
         (new-y-value-p (not (=e valid-y-magnification-factor
                                 (get-y-magnification-of-text-box-for-system-procedure text-box))))
         (text-box-format (text-box-format text-box))
         (default-x-magnification-factor
             (get-default-x-magnification-of-text-box-format text-box-format))
         (default-y-magnification-factor
             (get-default-y-magnification-of-text-box-format text-box-format)))
    (when new-x-value-p
      (change-text-box-property
        text-box 'x-magnification
        (if (=e valid-x-magnification-factor default-x-magnification-factor)
            nil                        ; restore "default"
                                ; see "issues"  note above (MHD 12/19/94)
          (convert-to-magnification valid-x-magnification-factor)))
      (when g2-has-v5-mode-windows-p
        (send-ws-representations-item-virtual-attribute-change
          text-box (virtual-attribute 'text-x-magnification) nil)))
    (when new-y-value-p
      (change-text-box-property
        text-box 'y-magnification
        (if (=e valid-y-magnification-factor default-y-magnification-factor)
            nil                        ; restore "default"
                                ; see "issues"  note above (MHD 12/19/94)
            (convert-to-magnification valid-y-magnification-factor)))
      (when g2-has-v5-mode-windows-p
        (send-ws-representations-item-virtual-attribute-change
          text-box (virtual-attribute 'text-y-magnification) nil)))))

;; (pbk 12/29/95) Fixed bug in setting magnification.  Previously (in 40r1) we were setting to
;; the default (ie clearing the plist) if the new value was the same as the old value. This is
;; clearly the wrong behavior in the case when the magnifaction is NOT the default value.  The
;; correct behavior is to NOT set at all if the value hasn't changed and to clear the plist ONLY
;; if we are setting the magnification to the default value.



(defmacro get-x-or-y-magnification-of-text-box-for-system-procedure (text-box x-or-y)
  (test-assertion                        ; not evaluated -- remember: don't quote!
    (member x-or-y '(x y)))
  (avoiding-variable-capture (text-box)
    `(let ((magnification?
             (or (getf (text-cell-plist-for-text-box ,text-box)
                       ',(if (eq x-or-y 'x) 'x-magnification 'y-magnification))
                 (,(if (eq x-or-y 'x)
                       'text-cell-x-magnification?
                       'text-cell-y-magnification?)
                   (text-box-format ,text-box)))))
       (if magnification?
           (convert-magnification-to-factor magnification?)
           1.0))))

(defmacro get-x-or-y-magnification-of-text-box-from-format (text-box-format x-or-y)
  (test-assertion                        ; not evaluated -- remember: don't quote!
    (member x-or-y '(x y)))
  (avoiding-variable-capture (text-box-format)
    `(let ((magnification?
             (,(if (eq x-or-y 'x)
                   'text-cell-x-magnification?
                   'text-cell-y-magnification?)
               ,text-box-format)))
       (if magnification?
           (convert-magnification-to-factor magnification?)
           1.0))))


;;; `Get-x-magnification-of-text-box-for-system-procedure' and
;;; `get-y-magnification-of-text-box-for-system-procedure' both return
;;; a font magnification factor.

(defun-simple get-x-magnification-of-text-box-for-system-procedure (text-box)
  (get-x-or-y-magnification-of-text-box-for-system-procedure text-box x))

(defun-simple get-y-magnification-of-text-box-for-system-procedure (text-box)
  (get-x-or-y-magnification-of-text-box-for-system-procedure text-box y))

(def-virtual-attribute text-font
    ((class text-box)
     (structure ((font-size (member small large extra-large))
                 (x-magnification float)
                 (y-magnification float))
                (and font-size))
     nil)
  :event-updates :within-putter
  :initial
  ((text-box-subclass)
   (declare (ignore text-box-subclass))
   (allocate-evaluation-structure
     (eval-list 'font-size 'large)))
  :getter
  ((text-box)
   (let ((font-size
           (determine-font-size-per-format
             (text-box-format text-box)
             (frame-class-case text-box
               (message 'large-message-format) ; JED 12/28/95 msgs seem to be "special"
               (text-inserter 'scrap-format)
               (t (default-text-box-format-name text-box)))))
         (x-magnification
           (get-x-or-y-magnification-of-text-box-for-system-procedure text-box x))
         (y-magnification
           (get-x-or-y-magnification-of-text-box-for-system-procedure text-box y)))
     (allocate-evaluation-structure
       (nconc (eval-list 'font-size font-size)
              (unless (=e 1.0 x-magnification)
                (eval-list 'x-magnification (make-evaluation-float x-magnification)))
              (unless (=e 1.0 y-magnification)
                (eval-list 'y-magnification (make-evaluation-float y-magnification)))))))
  :setter
  ((text-box new-value)
   (let ((font-size (evaluation-structure-slot new-value 'font-size))
         (x-magnification? (evaluation-structure-slot new-value 'x-magnification))
         (y-magnification? (evaluation-structure-slot new-value 'y-magnification)))
     (g2-set-font-of-text-box-1 text-box font-size x-magnification? y-magnification?)
     nil)))




;; Not used yet: (MHD 12/19/94)

;;; text box is an instance of class text-box width-or-none is either a width or
;;; the symbol DEFAULT; when default, the width defaults to the built-in
;;; setting.  If width-or-default is anything other than a number coercible to
;;; an integer, DEFAULT is assumed.  The value cannot be less than 0 or greater
;;; than 65,000.

(defun-for-system-procedure g2-set-minimum-width-of-text-box (text-box width)
  (require-text-box-arg-to-system-procedure text-box)
  (let* ((old (minimum-width-of-text-box text-box))
         (new (if (and (numberp width) (not (exceptional-float-p width)))
                  (min 65000 (max (round width) 0)) nil)))
    (unless (eql old new)
      (with-changes-to-text-box (text-box)
        (setf (minimum-width-of-text-box text-box) new)))))

(defun-for-system-procedure g2-get-minimum-width-of-text-box (text-box)
  (require-text-box-arg-to-system-procedure text-box)
  (minimum-width-of-text-box text-box))

(defun-for-system-procedure g2-set-maximum-width-of-text-box (text-box width-or-default)
  (require-text-box-arg-to-system-procedure text-box)
  (let* ((old (text-cell-desired-maximum-line-measure-for-text-box? text-box))
         (new (if (and (numberp width-or-default)
                       (not (exceptional-float-p width-or-default)))
                  (min 65000 (max (round width-or-default) 0)) nil)))
    (unless (eql old new)
      (with-changes-to-text-box (text-box)
        (setf (text-cell-desired-maximum-line-measure-for-text-box? text-box) ; name is wierd, huh
              new)))))

(defun-for-system-procedure g2-get-maximum-width-of-text-box (text-box)
  (require-text-box-arg-to-system-procedure text-box)
  (text-cell-desired-maximum-line-measure-for-text-box? text-box))

;;; `G2-get-text-extent' takes a G2 text (a text string) and a symbol naming a
;;; message subclass, and returns a structure with the following information
;;; about the extent of the text box's width and height after formatting:
;;;
;;;    (1) width: width in x of the bounding box of the text;
;;;    (2) height: height in y of the bounding box of the text;
;;;    (3) left-margin-width: the width of the left margin;
;;;    (4) top-margin-width: the width of the top margin;
;;;    (5) right-margin-width: the width of the right margin;
;;;    (6) bottom-margin-width: the width of the bottom margin;
;;;    (7) left-border-width: the width of the left border;
;;;    (8) top-border-width: the width of the top border;
;;;    (9) right-border-width: the width of the right border;
;;;    (10) bottom-border-width: the width of the bottom border
;;;
;;; Note that the width and height are the only items that can vary from call to
;;; call given the same text-box-subclass argument and a possibly different text
;;; text-string.
;;;
;;; Note: it may have be more modular to break these out separately, the user
;;; has no other access to these values, and this is not intended to be a very
;;; final abstraction project, just an interim solution to various Guide
;;; formatting needs.

(defun-for-system-procedure g2-get-text-extent
    ((text-string text) (text-box-subclass symbol))
  (declare (values structure)
           (keeps-g2-local-variables-valid t))
  (require-text-box-subclass-arg-to-system-procedure text-box-subclass)
  (let* ((text-box-format
           (get-or-make-format-frame
             (or (get-slot-init-form
                   text-box-subclass
                   'default-text-box-format-name)
                 'message-format)))
         (text-cell-plist
           (get-slot-init-form
             text-box-subclass 'text-cell-plist-for-text-box))
         (format-width-override?
           (get-slot-init-form
             text-box-subclass
             'minimum-width-of-text-box)))
    (G2-get-text-extent-1
      text-string text-box-format text-cell-plist
      format-width-override?)))

(define-system-rpc-access (G2-get-text-extent ((structure)))
    ((text-string text)
     (text-box-subclass symbol))
  (G2-get-text-extent
    text-string
    text-box-subclass))


;;; G2-get-text-extent-1 ... does not reclaim its text-string argument.

(defun G2-get-text-extent-1
    (text-string text-box-format text-cell-plist
                 &optional format-width-override?)
  (multiple-value-bind (width height)
      (get-extent-of-text-string-after-formatting
        text-string text-box-format text-cell-plist
        format-width-override?)
    (allocate-evaluation-structure
      (eval-list
        'width width
        'height height
        'left-margin (text-cell-left-margin text-box-format)
        'top-margin (text-cell-top-margin text-box-format)
        'right-margin (text-cell-right-margin text-box-format)
        'bottom-margin (text-cell-bottom-margin text-box-format)
        'left-border-width (text-box-left-border-width text-box-format)
        'top-border-width (text-box-top-border-width text-box-format)
        'right-border-width (text-box-right-border-width text-box-format)
        'bottom-border-width (text-box-bottom-border-width text-box-format)))))





;;;; System Procedures for Bounding-Box Operations




;;; `g2-change-size-of-item-per-area' ...
;;;
;;; See the documentation for the change-size-per-bounding-rectangle method for
;;; the set of defined/conventional modes.  In practice, mode is generally
;;; ignored for now, except in the case of text boxes, where it can be the
;;; symbol SCALE.  However, it is not quite ready for prime time, so it is
;;; not ever supported.

(defun-for-system-procedure g2-change-size-of-item-per-area
    (item left-edge top-edge right-edge bottom-edge mode)
  (declare (keeps-g2-local-variables-valid t))
  ;; flip two y values in user coordinate system:
  (let ((internal-left-edge left-edge)
        (internal-top-edge (-w top-edge))
        (internal-right-edge right-edge)
        (internal-bottom-edge (-w bottom-edge)))

    ;; Require area greater than zero.  This error frequently occurs when the user
    ;; has switched the left/top and right/bottom coordinates.  In 4.0 Beta Phase
    ;; 2, we just switched them so they made sense, but this was considered
    ;; harmful to programmers trying to get their arguments correct.  We now
    ;; signal an error (for 4.0 final, etc.) (MHD 3/13/95)
    (check-item-is-resizable item)
    (cond
      ((not (and (<w internal-top-edge internal-bottom-edge)
                 (<w internal-left-edge internal-right-edge)))
       (stack-error cached-top-of-stack "Area must be greater than zero in size."))
      (t
       (change-size-per-bounding-rectangle
         item
         internal-left-edge internal-top-edge
         internal-right-edge internal-bottom-edge
	 mode)))))

(define-system-rpc-access (g2-change-size-of-item-per-area ())
    ((item (class item))
     (left-edge integer)
     (top-edge integer)
     (right-edge integer)
     (bottom-edge integer)
     (mode symbol))
  (g2-change-size-of-item-per-area
    item
    left-edge
    top-edge
    right-edge
    bottom-edge
    mode))



;;; `item-is-resizable'
;;;
;;; An attempt to abstract the reluctance of some classes to be resized
;;; item-is-resizable-p is a predicate that determines if a block is
;;; resizable.

(defun-simple item-is-resizable-p (frame)
  #+development
  (unless
      (and (framep frame) (frame-of-class-p frame 'block))
    (cerror "go on anyway" "Illegal item passed to change size procedure"))
  (not
    (or (frame-of-class-p frame 'meter)
        (frame-of-class-p frame 'dial)
        (frame-of-class-p frame 'freeform-table)
        (frame-of-class-p frame 'readout-table)
        (frame-of-class-p frame 'type-in-box))))



;;; `check-item-is-resizable'
;;; can be used to throw a stack-error if passed an item that
;;; does not satisfy the item-is-resizable-p predicate.

(defun-void check-item-is-resizable (frame)
  (unless (item-is-resizable-p frame)
    (stack-error cached-top-of-stack
                 "Items of class ~A are not resizable." (class frame))))




;; Allowing SCALE would be the first time we let user scale boxes.  They can't
;; even do it through the user interface now.  It does happen in one, and only
;; one place, in G2 now in fact: in the labels for dials and meters.  Oh,
;; brother!  Until now .... (MHD 8/15/94)

;; Make sure this does the right thing for areas that are too big (clamps to
;; "maximum magnification") and for things that should be change-sized! (MHD
;; 8/15/94)

;; Trend charts want to support two modes, I think.  Talk to JED about this
;; again!  (MHD 8/15/94)



;;; ` g2-restore-item-to-normal-size'
;;;
;;; Programmatic interface for the restore-to-normal-size button
;;; in the change-size dialog.  See sizing-restore().

(defun-for-system-procedure g2-restore-item-to-normal-size (item)
  (check-item-is-resizable item)
  (restore-item-to-normal-size item))

(define-system-rpc-access (g2-restore-item-to-normal-size ())
    ((item (class item)))
  (g2-restore-item-to-normal-size item))

#+maybe-later
(defun-for-system-procedure g2-set-magnification-of-item
    (item x-magnification y-magnification)
  ;; need to ensure that this is an entity
  (let ((x-mag
          (with-temporary-gensym-float-creation convert-ratio-to-magnification
            (convert-to-magnification
              (if (evaluation-float-p x-magnification)
                  (evaluation-float-value x-magnification)
                  x-magnification))))
        (y-mag
          (with-temporary-gensym-float-creation convert-ratio-to-magnification
            (convert-to-magnification
              (if (evaluation-float-p y-magnification)
                  (evaluation-float-value y-magnification)
                  y-magnification))))
        (left (left-edge-of-block item))
        (top (top-edge-of-block item)))

    (check-item-is-resizable item)
    (cond
      (nil ;(or (=f x-magnification 0) (=f y-magnification 0))
       (stack-error cached-top-of-stack "Magnfications must be greater than zero."))
      (t
       (magnify-icon item x-mag y-mag left top nil)))))



;;; `G2-move-from-area-of-workspace' ...
;;;
;;; This does just what would be done if a user were using MOVE via
;;; operate-on-area on the specified rectangle in administrator mode.  In other
;;; words, this ignores user restrictions, if any, bearing on the movability of
;;; items or the expandability of workspaces.  It also ignores the convention
;;; that the move _action_ cannot expand a workspace, whereas a user-interface
;;; gesture can.  It also does not note the move as a KB state changes -- upon
;;; reset, the items will remain permanently where they are, and the workspace
;;; will remain at whatever size it was at while running, unless, of course,
;;; they change due to other KB state change resets.
;;;
;;; Workspace must be a KB workspace.
;;;
;;; The y-coordinate and y-delta args are with respect to the user workspace
;;; coordinate system, wherein positive y grows upwards.  All of these args must
;;; be fixnum integers.
;;;
;;; This returns no useful value.

(defun-for-system-procedure g2-move-from-area-of-workspace
    (workspace left-edge top-edge right-edge bottom-edge
               delta-x delta-y)
  (declare (keeps-g2-local-variables-valid nil)) ; NIL because of potential item
                                            ; transfers.  - cpm, 5/27/95

  ;; flip three y values in user coordinate system:
  (setq top-edge (-w top-edge))
  (setq bottom-edge (-w bottom-edge))
  (setq delta-y (-w delta-y))

  (let ((dragging-list-of-blocks-in-area
          (prepare-blocks-for-operation-on-area
            workspace left-edge top-edge right-edge bottom-edge)))
    (when dragging-list-of-blocks-in-area
      (multiple-value-bind
          (outline-for-blocks-to-drag external-connections)
          (make-outline-for-blocks-to-drag
            dragging-list-of-blocks-in-area nil)
        (shift-blocks-with-their-external-connections
          outline-for-blocks-to-drag external-connections
          nil workspace delta-x delta-y)))))

;; Rename most of the the args with "user-workspace-" as a prefix!

;; This is originally primarily intended for the GDA group in their attempts to
;; implement scrolling-like (trend-chart-like) capabilities for use in their
;; Gant charts.  The contact is Andreas Hofmann to see if this is working out.
;; Introduced for 4.0.  (MHD 8/15/94)

;; For testing, create a new workspace and put a few blocks around the
;; middle.  The following will show you something:
;;
;;   (progn
;;     (g2-move-from-area-of-workspace (ci 'kb-workspace) -300 300 300 -300 30 30)
;;     (force-workspace-drawing (ci 'kb-workspace)))





;;;; System Procedure for Rerouting a Telewindows Connection



;;; The system procedure `G2-reroute-window' ...
;;;
;;; Init-string-spec can be a string, possibly the empty string ("").

(defun-allowing-unwind-for-system-procedure g2-reroute-window
    ((g2-window item) (protocol text) (host text) (port text) (init-string text))
  (declare (keeps-g2-local-variables-valid nil))
  (when (not (of-class-p g2-window 'g2-window))
    (stack-error cached-top-of-stack
                 "g2-reroute-window not yet implemented for the item ~NF" g2-window))
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (case (type-of-gensym-window gensym-window)
      (icp
       (reroute-gensym-window
         gensym-window protocol host port init-string))
      (t
       (stack-error cached-top-of-stack
                    "Attempt to reroute ~NA failed: rerouting of the locally connected ~
          window is not allowed."
                    g2-window)))))

;; plist-of-corresponding-icp-object-maps-for-font-maps ??


(defun reroute-gensym-window (gensym-window protocol host port init-string)
  (case (type-of-gensym-window gensym-window)
    (icp
     (progn ; temporary-progn (2 20 95 "MHD -- deal w/ICP font object map for font maps!")
       ;; review another time! (MHD 2/20/95)
       (setq plist-of-corresponding-icp-object-maps-for-font-maps nil)) ; leak! FIX!
     (log-out-workstation (workstation-this-is-on gensym-window))

     (with-icp-window (gensym-window)
       (reroute-telewindow gensym-window protocol host port init-string)))
    (t
     #+development
     (cerror "continue, doing nothing" "rerouting the local window is not implemented at present")
     nil)))






;;;; System Procedures for Packaging and Releasing



;;; Package Preparation Mode

(defun-for-system-procedure g2-enter-package-preparation-mode ()
  (declare (keeps-g2-local-variables-valid t))
  (enter-package-preparation-mode))

(defun-for-system-procedure g2-leave-package-preparation-mode ()
  (declare (keeps-g2-local-variables-valid t))
  (leave-package-preparation-mode))

(defun-for-system-procedure g2-is-in-package-preparation-mode ()
  (declare (values truth-value)
           (keeps-g2-local-variables-valid t))
  (if package-preparation-mode truth falsity))



;;; Simulate-proprietary Mode

(defun-for-system-procedure g2-enter-simulate-proprietary-mode ()
  (declare (keeps-g2-local-variables-valid t))
  (when (not simulate-proprietary?)
    (set-simulate-proprietary-mode t)))

(defun-for-system-procedure g2-leave-simulate-proprietary-mode ()
  (declare (keeps-g2-local-variables-valid t))
  (when simulate-proprietary?
    (set-simulate-proprietary-mode nil)))

(defun-for-system-procedure g2-is-in-simulate-proprietary-mode ()
  (declare (values truth-value)
           (keeps-g2-local-variables-valid t))
  (if simulate-proprietary? truth falsity))



;;; Making Workspaces Proprietary

(defun-for-system-procedure g2-make-workspaces-proprietary-now ()
  (declare (keeps-g2-local-variables-valid t))
  (let ((system-is-running nil))        ; suppresses check in subfn.
    (make-proprietary-now)))



;;; Stripping Texts

(defun-for-system-procedure g2-strip-texts-now ()
  (declare (keeps-g2-local-variables-valid t))
  (let ((system-is-running nil))        ; ditto.
    (strip-all-texts)))



;;; Do-not-strip-text and Strip-text Marks on Items

(defun-for-system-procedure g2-set-strip-text-mark (item new-state)
  (declare (keeps-g2-local-variables-valid t))
  (cond ((evaluation-truth-value-is-true-p new-state)
         (set-stripping-flags-as-specified item 1 0))
        (t
         (set-stripping-flags-as-specified item 0 0)))
  (reclaim-evaluation-truth-value new-state))

(defun-for-system-procedure g2-item-has-strip-text-mark (item)
  (declare (keeps-g2-local-variables-valid t))
  (if (strip-text-p item)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(defun-for-system-procedure g2-set-do-not-strip-text-mark (item new-state)
  (declare (keeps-g2-local-variables-valid t))
  (cond ((evaluation-truth-value-is-true-p new-state)
         (set-stripping-flags-as-specified item 0 1))
        (t
         (set-stripping-flags-as-specified item 0 0)))
  (reclaim-evaluation-truth-value new-state))

(defun-for-system-procedure g2-item-has-do-not-strip-text-mark (item)
  (declare (keeps-g2-local-variables-valid t))
  (if (do-not-strip-text-p item)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))






;;;; G2 Window Cleanup



;;; When a g2 window is deleted, the user is logged out by calling log-out-
;;; workstation with the workstation associated with g2-window, if any.

(def-class-method cleanup (g2-window)
  (funcall-superior-method g2-window)
  (let* ((workstation? (workstation-for-g2-window? g2-window)))
    (when workstation?
      (log-out-workstation workstation?))))






;;;; Workstation Login and Logout



;;; `Log-out-workstation' ...

;;; This routine transitions workstation-login-state into either the LOGGED-OUT state
;;; or the CHANGING-KBS state.  It clears our model of the user from
;;; the g2-window-for-this-workstation?, LOGIN-WORKSTATION sets up that model.

;;; If we are going to LOGGED-OUT, then it also clears the user information from
;;; the workstation.

;;; If there is a g2 window for workstation, it is disconnected from it by
;;; calling disconnect-workstation-from-g2-window.

;;; This routine can be called from inside of a for-workstation context, in
;;; which case it must also clear the current-workstation specials.

(defun log-out-workstation (workstation)

  (with-backtrace-for-internal-error 'log-out-workstation

    (let* ((goal-state (if releasing-kb? 'changing-kbs 'logged-out))
           (clear-user-model (clear-model-of-user-when-logging-out-p goal-state))
           (preserve-login-information?
             (when (g2-secure-p)
               (login-information-specified-on-command-line-p workstation))))

      ;; Wipe the window's model of the user.
      (disconnect-workstation-from-g2-window-if-any workstation)

      ;; Maybe wipe the workstation's model of the user.  (Initialize workstation
      ;;   "user slots" the same way as declared in the def-structure.)
      (unless (or clear-user-model
                  preserve-login-information?)
        (setf (g2-user-mode-for-this-workstation? workstation) nil)
        (setf (g2-user-in-this-workstation-has-backdoor-privileges? workstation)
              nil)
        (setf (g2-user-name-for-this-workstation? workstation) nil)
        (setf (g2-user-password-for-this-workstation? workstation) nil)
        (setf (g2-window-name-or-class-for-this-workstation workstation) 'g2-window)
        ;; If we are inside of a for-workstation then clear its model
        (when servicing-workstation?
          (setq current-g2-user-mode? nil)))

      (when (and preserve-login-information?
                 (not clear-user-model))
        (setf (g2-user-password-for-this-workstation? workstation) nil)
        (let ((original-mode-from-command-line?
                (second (memq 'user-mode
                              (window-parameters-plist
                                (window-for-workstation workstation))))))
          (when original-mode-from-command-line?
            (setf (g2-user-mode-for-this-workstation? workstation)
                  (intern-text-string
                    (string-upcasew original-mode-from-command-line?))))))

      (setf (workstation-login-state workstation) goal-state)
      (setf (g2-window-for-this-workstation? workstation) nil)
      (unless (workstation-dead-p workstation)
        (install-unconnected-menu-bar (window-for-workstation workstation))))))



;;; `Login-information-specified-on-command-line-p' is relevant only to
;;; secure G2s, where a logout is going to be followed by putting up the
;;; login dialog for the benefit of the next user who uses that Telewindows
;;; connection. It notes whether any login data was given on the command
;;; line. If there was, we avoid clearing anything other than the password
;;; from the workstation so that when the login dialog comes up it will
;;; offer the original values as defaults.

(defun login-information-specified-on-command-line-p (workstation)
  (let ((gensym-window? (window-for-workstation workstation)))
    (when gensym-window?
      (let ((plist (window-parameters-plist gensym-window?)))
        (or (memq-p-macro 'user-name plist) ;; password is irrelevant
            (memq-p-macro 'user-mode plist))))))



;;; `Disconnect-workstation-from-g2-window-if-any' wipes out the window's model
;;; of the user.

(defun disconnect-workstation-from-g2-window-if-any (workstation)
  (let ((g2-window? (g2-window-for-this-workstation? workstation)))
    (when g2-window?
      (disconnect-workstation-from-g2-window workstation g2-window?))))


(defun clear-model-of-user-when-logging-out-p (goal-state)
  (or (eq goal-state 'changing-kbs)
      (and (eq goal-state 'loading-kbs)
           (not (g2-secure-p)))))








;;;; login user handler

(def-kb-specific-variable login-handler controls nil nil nil)
(def-kb-specific-variable login-handler-fsn controls nil nil reclaim-frame-serial-number)

(defun-for-system-procedure g2-register-login-handler (procedure)
  (if (of-class-p procedure 'procedure)
      (progn
        (check-procedure-arglist-and-maybe-notify
          procedure '((structure)) stack-error cached-top-of-stack)
        (setf login-handler procedure)
        (frame-serial-number-setf login-handler-fsn (frame-serial-number procedure))
        (make-evaluation-truth-value-function truth))
      (progn
        ;; This leaks a fsn.  Fix later.  -dkuznick, 6/29/04
        (setf login-handler nil)
        (make-evaluation-truth-value-function falsity))))

(defmacro invoke-user-handler (procedure frame-serial-number &rest args)
  "macro to stack allocate arguments and start call, args are checked against procedure arglist at runtime"
  (let ((arg-vector (gensym))
        (f   (gensym))
        (sn  (gensym))
        (msg (gensym)))
    `(let ((,f  ,procedure)
           (,sn ,frame-serial-number))
       (when (of-class-p ,f 'procedure)
         (unless (frame-has-been-reprocessed-p ,f ,sn)
           ;; managed vectors can't have 0 length!
           (let ((,arg-vector (allocate-managed-simple-vector ,(max 1 (length args)))))
             ,@(loop for i below (length args) collect `(setf (svref ,arg-vector ,i) ,(elt args i)))
             (let ((,msg (check-procedure-arglist-and-maybe-notify
                           ,f ,arg-vector notify-user)))
               (if ,msg
                   (progn
                     .,(loop for i below (length args) collect `(reclaim-if-evaluation-value (aref ,arg-vector ,i))))
                   (with-three-thousand-variables-bound
                       (start-procedure-invocation-in-place ,f
                                                            nil
                                                            nil
                                                            ,arg-vector
                                                            ,(1- (length args))
                                                            ,(length args)
                                                            nil
                                                            nil
                                                            nil
                                                            nil
                                                            nil))))
             (reclaim-managed-simple-vector ,arg-vector)))))))

(defun network-info (x)
  ;; useful info for login handler
  (cond ((workstation-p x)
         (let (port)
           (setf port (icp-output-port-for-window? (window-for-workstation x)))
           (when port
             (icp-connection-name (parent-icp-socket port)))))
        ((and (framep x)
              (frame-of-class-p x 'ui-client-session))
         (icp-connection-name (gsi-interface-icp-socket (ui-client-session-parent-interface x))))
        ;; always give the guy a string
        (t #w"")))







;;;; `Log-in-workstation'

;;; Attempt to transition the workstation-login-state to LOGGED-IN, but
;;; we may fail.  Return values are a boolean indicating our success,
;;; and upon failure a symbol that indicates why we failed.

;;; First we validate the user name and password, then the mode, finally
;;; the window.  Only once we have validated all this should we start
;;; doing things that have side effects.

;;; Backdoor and G2 being secure effect the handling of name, password,
;;; and mode validation.  We allow him into any mode if we are not secure.
;;; We also allow no user name or password to be specified if we are not
;;; secure.  We let him in under any user name if he knows the backdoor
;;; password and is on the local workstation.

;;; ...

;;; A G2 window is created or selected based on the following rules and
;;; on what is specified by the user-window-description? argument.
;;;
;;;    (0) If a G2-window instance is provided, that instance is assigned.
;;;        This case case is only allowed for code that knows it is passing
;;;        in a g2-window instance with a non-nil workstation-for-g2-window?.
;;;        [This capability is new for 3.0, rev. 3, in development as of 4/23/92.]
;;;
;;;    (1) If a window name is specified  and an instance with that name
;;;        exists which is not already assigned and which is not a transient
;;;        item, then that instance is assigned.
;;;
;;;    (2) If a window class is specified, an instance of that class
;;;        (but not of a subclass) is assigned if it is available and
;;;        is not a transient item.
;;;
;;;    (3) If a window class is specified and there are no available
;;;        instances, then one is automatically created provided that
;;;        the class is defined.

;;; When a window is automatically created, it will not be saved  out in
;;; the current KB.  But it will be deleted when it is logged out. Note that
;;; such an automatically created window is not a transient item; it will not
;;; be deleted upon a system reset.

;;; When a g2 window is assigned, the g2-window-management-type slot of that
;;; window is set to LOCAL, if this window is managed by the local system
;;; process (i.e. by G2), and to REMOTE if this window is managed by some
;;; remote process (i.e. Telewindows).

;;; Finally, if restore-detail-pane? is true, the current workstation (if
;;; any) has its detail pane restored.  Note that this should only be specified
;;; when the caller knows that the current workstation detail pane is empty,
;;; i.e. when changing kbs or logging in over telewindows on a secure G2.
;;; (Otherwise, it may result in multiple image planes showing the same
;;; workspace, which is not usually desired.)

(defun log-in-workstation
    (workstation user-name? encoded-user-password?
                 user-mode? user-window-description?
                 &optional restore-detail-pane? language? g2-window-style?)
  (let* ((allowable-window-class 'g2-window) ; does not include workspace-view
         (reason-we-failed? nil)
         (valid-g2-window-name? nil)
         (valid-named-window-instance? nil) ; only if valid-g2-window-name?
         (gensym-window (window-for-workstation workstation))
         (window-uuid-representation?
           (getf (window-parameters-plist gensym-window) 'window-uuid))
         (window-for-uuid?
           (let ((instance?
                   (if window-uuid-representation?
                       (get-instance-from-uuid-representation
                         window-uuid-representation?))))
             (if (and instance?
                      (frame-of-class-p instance? allowable-window-class))
                 instance?)))
         (frame-reference (current-frame-serial-number))
         (valid-g2-window-class? nil))
    ;; Validate the user name and password
    (setq reason-we-failed?
          (validate-user-and-password user-name? encoded-user-password?))
    ;; Validate the user mode
    (unless reason-we-failed?
      (unless user-mode?   ; You have to have a mode.
        (setq reason-we-failed? 'user-mode-required)))
    ;; it has to be one you're allowed to be in
    (unless reason-we-failed?
      (setq reason-we-failed?
            (validate-user-mode-for-user user-name? user-mode?)))
  
    (when (is-in-ldap-mode-p) 
      (setq reason-we-failed? (authentificate-user-ldap user-name? user-mode?)))
 
    ;; Validate the window
    (unless reason-we-failed?
      (cond
        ((null user-window-description?)
         (setq reason-we-failed? 'window-required))
        ((not (symbolp user-window-description?)) ; it's a g2-window
         (setq valid-named-window-instance?
               user-window-description?))
        (t                                        ; may be a name (1st choice)
         (cond                                        ;   or a class
           ((setq valid-named-window-instance?
                  (or window-for-uuid?
                      (get-instance-with-name-if-any
                        allowable-window-class user-window-description?)))
            ;; it's a name
            (cond
              ((workstation-for-g2-window? valid-named-window-instance?)
               (if (eq workstation                ; ok, because in use by us now
                       (workstation-for-g2-window? valid-named-window-instance?))
                   (setq valid-g2-window-name? user-window-description?)
                   (if (workstation-for-g2-window? valid-named-window-instance?)
                       (setq reason-we-failed? 'named-window-already-in-use))))))
           ((subclassp                                ; try interpreting it as a class name
              user-window-description?
              allowable-window-class)
            ;; it's a class
            (setq valid-g2-window-class? user-window-description?))
           (t
            (setq reason-we-failed? 'no-windows-with-this-name-or-of-this-class))))))
    (unless reason-we-failed?
      ;; We are in; now changing state can begin.
      ;; Change window if we need to and get the user model in synch.
      (let ((g2-window-for-this-workstation?
              (g2-window-for-this-workstation? workstation)))
        ;; Three steps:
        ;; 1. Discard existing window, if it doesn't match window-description.
        #+development
        (test-assertion         ; this just checks for programmer errors (MHD 4/23/92)
          (or (not (eq user-window-description?
                       valid-named-window-instance?))
              (and (not (symbolp user-window-description?))
                   (g2-window-p user-window-description?)
                   (eq user-window-description?
                       g2-window-for-this-workstation?))))
        (when (and g2-window-for-this-workstation?
                   (not (eq user-window-description?
                            valid-named-window-instance?)))
          (when (if valid-g2-window-name?
                    (not                        ; this window has the name?
                      (eq valid-named-window-instance?
                          g2-window-for-this-workstation?))
                    ;; else:   (now valid-g2-window-class? can't be null)
                    (not
                      (frame-of-class-p                ; this window has the class?
                        g2-window-for-this-workstation?
                        valid-g2-window-class?)))
            (disconnect-workstation-from-g2-window
              workstation g2-window-for-this-workstation?)
            (setf g2-window-for-this-workstation? nil)))
        (cond
          ((or (and valid-named-window-instance?
                    (frame-has-been-reprocessed-p
                      valid-named-window-instance? frame-reference))
               (and valid-g2-window-class? ; see "-- update" further down!
                    (or (not (classp valid-g2-window-class?))
                        (not (subclassp valid-g2-window-class? allowable-window-class)))))
           ;; Uh oh.  Odd case!  Disconnecting the workstation from the window
           ;; must have caused the instance to be deleted, most likely either
           ;; because it in the workspace heirarchy of the g2 window that got
           ;; deleted, or because its class definition was in that heirarchy and
           ;; got deleted.  We'll have to leave them in the logged out state.
           ;; Fixes bug HQ-2729457. (MHD 6/4/99)
           ;; -- UPDATE: Odd case II! Fixes bug HQ-3508782. (MHD 6/5/00)
           (setq reason-we-failed? 'window-required) ; make more specific/accurate?
           (setq valid-named-window-instance? nil)
           (setq valid-g2-window-class? nil)
           (log-out-workstation workstation)
           (when (and user-window-description?
                      (symbolp user-window-description?))
             ;; While rare, this usually/always happens because the user
             ;; specified a window name or class.  The way we handle it puts the
             ;; user in a totally unexpected state: the window they were on is
             ;; gone, and the window they're going to is gone, and they'll be
             ;; put back at top level in G2 (unless they're secure.  So we think
             ;; a logbook message is in order.
             (notify-user
               "Failed attempting to change to the G2 window whose name or ~
              class is ~A.  The specified G2 window got deleted in ~
              the process of making the change."
               user-window-description?)
             nil))
          ;; (otherwise, proceed past the odd case to step 2...)
          (t
           ;; 2. Copy the user name, password, and mode into the window, workstation,
           ;; current-workstation specials.
           ;; Synch up the workstation's user model
           (setf (g2-user-name-for-this-workstation? workstation) user-name?)
           (setf (g2-user-password-for-this-workstation? workstation)
                 (copy-for-slot-value encoded-user-password?))
           (if (symbolp user-window-description?)        ; HMMM... (MHD 4/23/92)
               (setf (g2-window-name-or-class-for-this-workstation workstation)
                     user-window-description?))
           (setf (specific-language-for-this-workstation? workstation) language?)
           (setf (style-specifically-for-this-workstation? workstation)
                 g2-window-style?)
           ;; 2a. Now make sure we have a window
           (unless g2-window-for-this-workstation?
             (setf g2-window-for-this-workstation?
                   (or valid-named-window-instance?
                       (loop for g2-window
                                 being each strict-class-instance
                             of valid-g2-window-class?
                             when
                               (and (null (name-or-names-for-frame g2-window))
                                    (null (workstation-for-g2-window? g2-window))
                                    (not (transient-p g2-window)))
                               return g2-window        ; found one existing, available
                             finally
                               (return                ; have to autocreate one
                                 (autocreate-g2-window valid-g2-window-class?)))))
             (connect-workstation-to-g2-window
               workstation g2-window-for-this-workstation?))
           ;; 3. Now synch the window's user model from the workstation's model.
           (set-session-info-in-g2-window workstation g2-window-for-this-workstation?)
           ;; a couple of new slots on g2-windows that need to be initialized
           (setf (g2-window-user-is-valid g2-window-for-this-workstation?) truth)
           (setf (g2-window-mode-is-valid g2-window-for-this-workstation?) truth)
           ;; user-mode
           (update-AB-side-TW-user-mode
             user-mode? g2-window-for-this-workstation? workstation)
           ;; Put workstation in LOGGED-IN state.
           (setf (workstation-login-state workstation) 'logged-in)
           ;; Do things for current workstation if necessary.  This is called
           ;; after setting the state to logged-in so that the code that follows
           ;; can tell it's OK to put stuff up & do things with the workstation.
           (when servicing-workstation?
;        ;; Synch for-workstation context
;        (setf current-g2-user-mode? user-mode?)
             ;; If changing the KB, restore the saved detail pane description
             ;; on the current workstation.
             (when restore-detail-pane?
               (restore-current-workstation-detail-pane nil t)
               (note-gensym-window-initialized gensym-window)))))))
    (invoke-user-handler
      login-handler
      login-handler-fsn
      (allocate-evaluation-structure-inline
        'success (make-evaluation-value-based-on-type (null reason-we-failed?))
        'system (make-evaluation-value-based-on-type 'tw)
        'status (make-evaluation-value-based-on-type reason-we-failed?)
        'user-name user-name?
        'user-mode user-mode?
        'network-info (make-evaluation-value-based-on-type
                        (network-info workstation))))
    (values (if reason-we-failed? nil t) reason-we-failed?)))

(defun notice-tw-disconnect (workstation user-name user-mode)
  ;; for symmetry between tw and t2
  ;; workstation disappears after this call !
  (invoke-user-handler login-handler
                       login-handler-fsn
                       (allocate-evaluation-structure-inline
                         'success (make-evaluation-value-based-on-type nil)
                         'system (make-evaluation-value-based-on-type 'tw)
                         'status (make-evaluation-value-based-on-type 'too-many-login-attempts)
                         'user-name user-name
                         'user-mode user-mode
                         'network-info (make-evaluation-value-based-on-type (network-info workstation)))))

;; Probably, ultimately, the caller of this in FILTERS should go through the
;; same interface as everything else, probably enter-user-settings-editor with
;; some extra args. (MHD 11/22/94)


;; Note that this does not assume it is being called in a for-workstation
;; context; now it seems it would probably have been better to, but we
;; defer review of that decision for now. (MHD/BAH 4/16/90)







;;;; `Log-in-ui-client'

;;; A user coming in via Telewindows Two does not have a workstation
;;; or a g2-window. The information that would have been on a
;;; g2-window appears instead on a ui-client-session. They are however
;;; subject to the same constraints when G2 is secure. These have been
;;; abstracted into subroutines that are accessed here and in
;;; log-in-workstation.

(defun log-in-ui-client (nonce-data session user-name nonce-encoded-password user-mode)
  (let ((reason-we-failed? nil))
    (when (too-many-login-attempts-from-this-source nonce-data)
      (setq reason-we-failed? 'too-many-login-attempts)
      (setf (t2-nonce-state nonce-data) 'too-many-login-attempts))
    ;; If we're secure, does this password go with this user?
    (unless reason-we-failed?
      (setq reason-we-failed?
            (validate-user-and-password user-name nonce-encoded-password (t2-nonce-string nonce-data))))
    ;; Is the mode something that can be a user-mode? (In classic g2 this
    ;; check is done by the parser.)
    (unless reason-we-failed?
      (setq reason-we-failed?
            (validate-as-possible-user-mode user-mode)))
    ;; If we're secure, is this a mode we're allowed to be in?
    (unless reason-we-failed?
      (setq reason-we-failed?
            (validate-user-mode-for-user user-name user-mode)))
    (unless reason-we-failed?
      ;; This is just a validator, we leave it to the caller to set
      ;; the values into the frame in the appropriate places for
      ;; user-name and such.
      ;; The one exception is two values that are exclusively managed
      ;; on the g2 side in response to updates to secure ok files.
      (set-ui-client-session-user-is-valid session truth)
      (set-ui-client-session-mode-is-valid session truth)
      ;; And also we record the fact that we were successful
      (note-that-session-has-been-successfully-logged-in session))
    (invoke-user-handler login-handler
                         login-handler-fsn
                         (allocate-evaluation-structure-inline
                           'success (make-evaluation-value-based-on-type (null reason-we-failed?))
                           'system (make-evaluation-value-based-on-type 't2)
                           'status (make-evaluation-value-based-on-type reason-we-failed?)
                           'user-name user-name
                           'user-mode user-mode
                           'network-info (make-evaluation-value-based-on-type (network-info session))))
    reason-we-failed?))

(defun log-out-ui-client (ui-client-session)
  (note-that-session-has-logged-out ui-client-session))





;;;; Log-in Failure Errors

;;; There should be a structure, analogous to `access-error' that
;;; encapsulates the information about just what aspect of the login is in
;;; error. It would replace the simple use of symbols that
;;; log-in-workstation presently uses. Of course a substantial number of
;;; callers would have to be revised. But that's probably a good thing; its
;;; just waiting for a good reason to touch them all. In lieu of taking the
;;; time to do that, the define-internationalized-symbol facility in
;;; LANGUAGE that is at least a start on something better.


;;; The symbols used in log-in-workstation as possible values for the
;;; reason-we-failed?.  This list is maintained by hand (sigh).
;;;
;;; The use of `define-internationalized-symbol' sets these up as simple
;;; conditions that can be referenced in language translation statements in
;;; a kb.

(def-concept login-errors)

(loop for symbol
      in '(user-name-required
           password-required
           unknown-user-or-bad-password
           user-mode-required
           unauthorized-mode
           unknown-user-mode-in-current-kb
           window-required
           named-window-already-in-use
           no-windows-with-this-name-or-of-this-class
           (password-has-expired
            . #w"This password has expired")

           ;; used by `disallow-ui-client-session'
           (no-available-floating-licenses
            . #w"All available floating license are in use.")


           (too-many-login-attempts .
            #w"There have been too many attempts to login from this source")

           ;; cases for problems with user-modes
           (user-mode-is-not-a-symbol . #w"user modes must be symbols")
           (user-mode-may-not-be-nil . #w"Nil is not a possible user mode")
           (user-mode-may-not-be-an-empty-string .
            #w"\"\" is not a valid user mode")
           (cannot-enter-proprietary-mode .
            #w"You cannot enter PROPRIETARY mode.")

           ;; for the specialized kind of "login failures" unique to doing a
           ;; password change:
           new-password-required
           duplicate-new-password-required
           new-password-must-be-at-least-4-characters-long
           new-password-too-long
           new-password-has-invalid-characters
           new-passwords-do-not-match
           new-passwords-do-not-match
            cannot-write-to-g2-ok-file        ; probably obsolete!
           can-not-write-tmp-file
            cannot-find-g2-ok-file
           g2passwd-executable-cannot-be-found
           (initializing-the-password-of-user-with-existing-password .
            #w"The user already has a password.")
            problem-saving-password-in-g2-ok-file)

      do (define-internationalized-symbol symbol))


;;; These are the possible states that a nonce can be in.
;;; The nonce structure and functions are in SEQUENCES1, but
;;; these are here because LANGUAGE is later in the module
;;; load order; sigh.

(loop for symbol
      in '(no-entry-for-this-nonce
           nonce-is-not-a-string
           ;too-many-login-attempts -- entry provided just above
           logged-in
           logged-out
           )
      do (define-internationalized-symbol symbol))






;;;; Rendering Decaching Test Functions

;;; The following functions can be used to check consistency of renderings
;;; between G2 and any number of TELEWINDOWS processes.  These are defined
;;; for development only.


#+development
(defvar list-of-rendering-icp-indices nil)



;;; Get-icp-indices-for-renderings-given-telewindow should be called from
;;; a G2 process to put the icp indices for the telewindow of all
;;; icon-renderings used in the telewindow into the global variable
;;; list-of-rendering-icp-indices.

;;; Check-telewindows-lru-queue should be called in telewindows process
;;; after get-icp-indices-for-renderings-given-telewindow has been called
;;; in the G2 process.


#+development
(defun get-icp-indices-for-renderings-given-telewindow
       (telewindow-name lru-queue)
  (setq list-of-rendering-icp-indices nil)
  (let* ((telewindow
           (get-instance-with-name-if-any 'entity telewindow-name))
         (workstation?
           (workstation-for-g2-window? telewindow))
         (icp-output-port?
           (when workstation?
             (icp-output-port-for-window?
               (window-for-workstation workstation?)))))
    (when icp-output-port?
      (loop as rendering
               = (least-recently-used-lru-element lru-queue)
               then (lru-element-next-element rendering)
            until (eq rendering lru-queue)
            as index
               = (if (eq lru-queue icon-rendering-lru-queue)
                     (get-icp-object-index-for-icon-rendering
                       rendering icp-output-port?)
                     (get-icp-object-index-for-graph-rendering
                       rendering icp-output-port?))
            do (when index
                 (setq list-of-rendering-icp-indices
                       (cons index list-of-rendering-icp-indices))))))
  list-of-rendering-icp-indices)



#+development
(defun check-telewindows-lru-queue (lru-queue)
  (let* ((list-of-renderings-from-queue
           (loop as rendering
                    = (least-recently-used-lru-element lru-queue)
                    then (lru-element-next-element rendering)
                 until (eq rendering lru-queue)
                 collect rendering))
         (icp-socket?
           (car active-icp-sockets))
         (icp-input-port?
           (when icp-socket? (icp-input-port icp-socket?)))
         (list-of-renderings-from-icp-indices
           (when icp-input-port?
             (loop for index in list-of-rendering-icp-indices
                   as corresponding-icp-object
                      = (get-object-from-index-space
                          (standard-icp-object-index-space icp-input-port?)
                          index)
                   collect corresponding-icp-object))))
    (loop for rendering in list-of-renderings-from-queue
          do (when (not (memq rendering list-of-renderings-from-icp-indices))
               (cerror "" "rendering in TELEWINDOWS not in G2")))
    (loop for rendering in list-of-renderings-from-icp-indices
          do (when (not (memq rendering list-of-renderings-from-queue))
               (cerror "" "rendering in G2 not in TELEWINDOWS")))
    ))








;;;; Showing and Hiding





;;; Show-or-hide ... If show-case? is true, it shows the workspace for block if
;;; there is one; otherwise, it hides the workspace for block if there is one.
;;; If show-details? is non-nil, they are used to specify positioning and scaling
;;; details.  If g2-window? is non-nil, it is taken to be a in instance of a frame
;;; of class g2-window and, if there is a workstation associated with it, the show
;;; or hide action takes place inside of it.  If g2-window? is nil, and servicing-
;;; workstation? (a special variable) is non-nil, the show or hide action takes
;;; place in the detail pane of current-workstation-window.  Finally, if g2-window?
;;; is nil, and servicing-workstation? is nil, then the show or hide action takes
;;; place in every logged-in workstation window.

;;; If go-to-block? is true, then the workspace is shown at full scale and such
;;; that block is at the center of the pane, and, where the platform supports it,
;;; the mouse is also warped to the center.  This only makes sense to specify if
;;; show-case? is true, and this overrides show-details? completely.

;;; After showing the workspace, if servicing-workstations? is true, its image plane
;;; is required to be visible by calling require-that-image-plane-be-visible.

(defun show-or-hide (block show-case? show-details? g2-window-or-client-session?
                     &optional go-to-block?)
  (if (and g2-window-or-client-session?          ; temporary! fix callers to
           (not (and (framep g2-window-or-client-session?) ;   conform, then remove!
                     (or (frame-of-class-p g2-window-or-client-session?
                                           'g2-window)
                         (frame-of-class-p g2-window-or-client-session?
                                           'ui-client-session)))))
      (return-from show-or-hide nil))
  (cond
    ((and g2-window-or-client-session?
          (frame-of-class-p g2-window-or-client-session?
                            'g2-window))
     (if (workstation-for-g2-window? g2-window-or-client-session?)
         (show-or-hide-1
           block show-case? show-details?
           (window-for-workstation
             (workstation-for-g2-window? g2-window-or-client-session?))
           nil go-to-block?)))
    (servicing-workstation?
     (show-or-hide-1
       block show-case? show-details? current-workstation-window t
       go-to-block?))
    ((and g2-window-or-client-session?
          (frame-of-class-p g2-window-or-client-session?
                            'ui-client-session))
     (cond (show-case?
            #+development
            (cerror "go on" "funny show case - see JED")
            nil)
           (t
            (let ((workspace? (get-workspace-if-any block)))
              (when workspace?
                (update-ui-client-for-hide
                  g2-window-or-client-session? workspace?))))))
    (t
     (loop for workstation in workstations-in-service
           when (eq (workstation-login-state workstation) 'logged-in)
             do (show-or-hide-1
                  block show-case? show-details?
                  (window-for-workstation workstation)
                  nil go-to-block?))
     (cond (show-case?
            #+development
            (cerror "go on" "funny show case - see JED")
            nil)
           (t
            (loop for client-session being each class-instance
                  of 'ui-client-session
                  do
              (let ((workspace? (get-workspace-if-any block)))
                (when workspace?
                  (update-ui-client-for-hide
                    client-session workspace?)))))))))


(defun show-or-hide-1
    (block show-case? show-details? gensym-window
           require-visibility? go-to-block?)
  (let* ((pane (detail-pane gensym-window))
         (workstation (workstation-this-is-on gensym-window))
         (workspace? (get-workspace-if-any block))
         (image-plane? (if workspace? (get-image-if-any workspace? pane)))
         (workspace-was-hidden? (null image-plane?)))
    (when (workspace-show-or-hide-hook workspace? gensym-window show-case?)
      (return-from show-or-hide-1 nil))

    (cond
      ((not show-case?)                                ; => hide case
       ;; delete the image; note that delete-image-plane updates selection,
       ;; native scroll bars, & native title bars:
       (if image-plane? (delete-image-plane image-plane?)))

      ;; otherwise, show case
      ((and workspace?                                ; => there is a workspace to show
            (workspaces-can-be-shown-at-this-kb-level-p
              workspace? workstation))        ; => showing this workspace
                                        ;   not restricted

       ;; if workspace is not on an image plane, get an image plane
       (unless image-plane?
         (setf image-plane?
               (get-available-image-plane
                 pane
                 (lookup-frame-description-reference-of-block? workspace?)
                 nil)))

       (cond
         (go-to-block?
          (transform-image                        ; show at full scale, centered
            image-plane? workspace?                ;   on block, at the front
            (get-default-image-x-scale image-plane?)
            (get-default-image-y-scale image-plane?)
            nil block
            nil nil nil nil
            nil nil nil nil t)
          (warp-mouse-to-center-of-workstation-window workstation))
         (t
          (multiple-value-bind (scale? x-in-workspace? y-in-workspace?
                                       x-in-window? y-in-window?)
              (decode-show-action-description show-details? block image-plane?)

            ;; Transform image plane to show workspace according to show-details?,
            ;;   where applicable, and according to the position and scale remembered
            ;;   from when the workspace was last hidden, where show-details? leaves
            ;;   things unspecified.
            (let ((remembered-window-position-and-scale?
                    (if workspace-was-hidden?
                        (getf
                          (plist-of-remembered-window-positions-and-scales workspace?)
                          (pane-name pane)))))
              (transform-image
                image-plane? workspace?
                (or scale?
                    (if remembered-window-position-and-scale?
                        (scale-scale
                          (third remembered-window-position-and-scale?)
                          (get-default-image-x-scale image-plane?)
                          (normalized-scale))))
                (or scale?
                    (if remembered-window-position-and-scale?
                        (scale-scale
                          (fourth remembered-window-position-and-scale?)
                          (get-default-image-y-scale image-plane?)
                          (normalized-scale))))
                nil nil
                (or x-in-workspace?
                    (if remembered-window-position-and-scale?
                        0))
                (or y-in-workspace?
                    (if remembered-window-position-and-scale?
                        0))
                (or x-in-window?
                    (if remembered-window-position-and-scale?
                        (delta-x-in-window
                          (first remembered-window-position-and-scale?)
                          (scale-scale
                            (normalized-scale)
                            (get-default-image-x-scale image-plane?)
                            (normalized-scale)))))
                (or y-in-window?
                    (if remembered-window-position-and-scale?
                        (delta-x-in-window
                          (second remembered-window-position-and-scale?)
                          (scale-scale
                            (normalized-scale)
                            (get-default-image-y-scale image-plane?)
                            (normalized-scale)))))
                nil nil nil nil
                t)
              (if require-visibility?
                  (require-that-image-plane-be-visible image-plane?))))))

       ;; Any time we "show" a workspace, it must be selected, whether going to
       ;; a block, lifting to the top, or showing something that was previously
       ;; hidden.
       (when (selection-enabled-p (window-for-workstation workstation))
         (select-workspace workspace? workstation))
       (update-native-title-bar image-plane?)))))

;; The go-to-block? arg is for goto-frame-instance.

;; Warping the mouse should be eliminated!  Instead, it should highlight or
;; blink the block that is of interest.  Going to the center could also be
;; eliminated, possibly.



;;; Decode-show-action-description returns the scale, x-in-workspace,
;;; y-in-workspace, x-in-window, y-in-window for the given action-description,
;;; block, workspace, and image plane.
;;;
;;; Show-details is a list of the form
;;;
;;;    ( {detail} )
;;;
;;; Where detail is one of
;;;
;;;    (SCALE ...)
;;;    (WORKSPACE-POSITION ...)
;;;    (SCREEN-POSITION ...)
;;;
;;; with possible expansions as shown below::
;;;
;;; scale:
;;;
;;;   (SCALE nil)
;;;   (SCALE ONE-QUARTER)
;;;   (SCALE HALF)
;;;   (SCALE THREE-QUARTER)
;;;   (SCALE FULL)
;;;
;;; new/proposed:
;;;
;;;   (SCALE positive-slot-value-float)
;;;   (SCALE negative-slot-value-float)
;;;   (SCALE TO-FIT [x] [y])
;;;
;;; where positive|negative-slot-value-float is a number greater or less than 0.
;;; When greater than 0, it is an absolute scale, that is, relative to full
;;; scale.  When less than 0 it is a scale relative to the current scale.  Note
;;; that the ultimate scale of the image plane is subject to internal limits.
;;;
;;; In the TO-FIT case, if both x and y are omitted, a scale is chosen at the
;;; maximum size, or full scale, whichever is smaller, at which the image fits
;;; in the pane.  If just x is specified, a scale is chosen at the maximum size,
;;; or full scale, whichever is smaller, at which the image is no wider than X.
;;; Y is the same but for the Y dimension.  If X and Y are both specified, the
;;; smaller of the dimensions is used to constrain the scale.
;;;
;;;
;;;
;;; workspace-position:
;;;
;;;   (WORKSPACE-POSITION CENTER)
;;;   (WORKSPACE-POSITION ( LEFT|TOP|RIGHT|BOTTOM  CENTER|LEFT|RIGHT ))
;;;   (WORKSPACE-POSITION ( <x-expr>  <y-expr> ))  ; new for 4.0
;;;
;;; Note that "workspace position" refers the workspace coordinate of the block
;;; argument, which need not itself be a workspace: it may be a block on a
;;; workspace.
;;;
;;;
;;; screen-position:
;;;
;;;   (SCREEN-POSITION AT|direction-and-units-spec CENTER)
;;;   (SCREEN-POSITION AT|direction-and-units-spec
;;;      ( LEFT|TOP|RIGHT|BOTTOM  CENTER|LEFT|RIGHT ))
;;;   (SCREEN-POSITION AT|direction-and-units-spec ; new for 4.0
;;;      ( <x-expr>  <y-expr> ))
;;;
;;; direction-and-units-spec:
;;;
;;;   (direction units [direction units])
;;;
;;; direction: ABOVE BELOW LEFT RIGHT
;;;
;;; where units is a delta in window system units, to be added in the BELOW and
;;; RIGHT cases, and substracted in the ABOVE and LEFT cases.

;;; NOTE: This version of the implementation of the SHOW action is obsolete.  It
;;; is still supported for old code, or, strictly speaking, the old compiles of
;;; old code, however.  See the section "New Show", below.  (MHD 3/1/94)
;;;
;;; NOTE: Old compiles do not fully handle the interpretation of "full scale"
;;; properly.  They happen to do the right thing as long as default-x-scale =
;;; default-y-scale, which is probably always true. (MHD 3/1/94)

(defun decode-show-action-description (show-details block image-plane)
  (let ((scaling-details nil)
        (workspace-position-details nil)
        (screen-position-details nil)
        (default-scale             ; imperfect, but ok -- only for old compiles
            (get-default-image-x-scale image-plane))
        (scale? nil)
        (x-in-workspace? nil) (y-in-workspace? nil)
        (x-in-window? nil) (y-in-window? nil))
    (loop for details in show-details
          do (case (car details)
               (scale
                (setq scaling-details details))
               (workspace-position
                (setq workspace-position-details details))
               (screen-position
                (setq screen-position-details details))))
    (setq scale?
          (case (cadr scaling-details)                ; can be nil
            ((nil) nil)
            (t
             (magnify default-scale
                      (case (cadr scaling-details)
                        (one-quarter #.(convert-to-magnification-at-compile-time .25))
                        (half #.(convert-to-magnification-at-compile-time .5))
                        (three-quarter #.(convert-to-magnification-at-compile-time
                                           .75))
                        (t                        ; full
                         #.(convert-to-magnification-at-compile-time 1)))))))
    (let* ((left-edge (left-edge-of-pane-in-window image-plane))
           (top-edge (top-edge-of-pane-in-window image-plane))
           (right-edge (right-edge-of-pane-in-window image-plane))
           (bottom-edge (bottom-edge-of-pane-in-window image-plane))
           (x-center (halfr (+r left-edge right-edge)))
           (y-center (halfr (+r top-edge bottom-edge))))
      (cond
        ((null screen-position-details))        ; unspecified
                                                ; NOTE: in 1.11B and earlier
                                                ;   this was the same as the
                                                ;   following case (center)
        ((atom (caddr screen-position-details))        ; => center
         (setq x-in-window? x-center)
         (setq y-in-window? y-center))
        (t
         (case (car (caddr screen-position-details))
           (left (setq x-in-window? left-edge))
           (top (setq y-in-window? top-edge))
           (right (setq x-in-window? right-edge))
           (bottom (setq y-in-window? bottom-edge)))
         (case (cadr (caddr screen-position-details))
           (center
            (if (memq (car (caddr screen-position-details)) '(top bottom))
                (setq x-in-window? x-center)
                (setq y-in-window? y-center)))
           (left (setq x-in-window? left-edge))
           (right (setq x-in-window? right-edge)))
         ;; NOTE: in 1.11A, there was a bug causing offsets from the center of
         ;;   the screen to be ignored because the following cond was at this
         ;;   level (and so was ignored in the Center case). (MHD 4/6/89)
         ))
      (cond
        ((not (atom (cadr screen-position-details)))        ; == (not (eq (cadr ...) 'AT))
         (multiple-value-setq (x-in-window? y-in-window?)
           (update-per-direction-and-units-spec
             (cadr screen-position-details) x-in-window? y-in-window?))
         (if (cddr (cadr screen-position-details))
             (multiple-value-setq (x-in-window? y-in-window?)
               (update-per-direction-and-units-spec
                 (cddr (cadr screen-position-details)) x-in-window? y-in-window?))))))
    (let* ((left-edge (left-edge-of-block block))
           (top-edge (top-edge-of-block block))
           (right-edge (right-edge-of-block block))
           (bottom-edge (bottom-edge-of-block block)))
      (cond
        ((and (null screen-position-details)        ; unspecified
              (null workspace-position-details)))        ; NOTE: in 1.11B and earlier
                                                ;   this was the same as the
                                                ;   following case (center)
        ((atom (if workspace-position-details        ; center
                   (cadr workspace-position-details)
                   (caddr screen-position-details)))
         (setq x-in-workspace? (halfw (+w left-edge right-edge)))
         (setq y-in-workspace? (halfw (+w top-edge bottom-edge))))
        (t
         (case (if workspace-position-details
                   (car (cadr workspace-position-details))
                   (car (caddr screen-position-details)))
           (left (setq x-in-workspace? left-edge))
           (top (setq y-in-workspace? top-edge))
           (right (setq x-in-workspace? right-edge))
           (bottom (setq y-in-workspace? bottom-edge)))
         (case (if workspace-position-details
                   (cadr (cadr workspace-position-details))
                   (cadr (caddr screen-position-details)))
           (center
            (if (memq (if workspace-position-details
                          (car (cadr workspace-position-details))
                          (car (caddr screen-position-details)))
                      '(top bottom))
                (setq x-in-workspace? (halfw (+w left-edge right-edge)))
                (setq y-in-workspace? (halfw (+w top-edge bottom-edge)))))
           (left (setq x-in-workspace? left-edge))
           (right (setq x-in-workspace? right-edge))))))
    (values scale? x-in-workspace? y-in-workspace? x-in-window? y-in-window?)))




;;; Update-per-direction-and-units-spec is pretty trivial ...

(defun update-per-direction-and-units-spec
       (direction-and-units-spec x-in-window y-in-window)        ; args may be changed!
  (let* ((direction (car direction-and-units-spec))
         (units (cadr direction-and-units-spec)))
    (case direction
      (above (decfr y-in-window units))
      (below (incfr y-in-window units))
      (left (decfr x-in-window units))
      (t                                        ; right
       (incfr x-in-window units)))
    (values x-in-window y-in-window)))








;;;; New Show




;;; The above show-or-hide is no longer used for showing from inference engine
;;; instructions compiled in 4.0 or higher.  It is still used for old SHOW
;;; instructions.  And it is used for the HIDE instruction.  The new functions
;;; in this section are for compiling and executing the new show instruction,
;;; SHOW-NEW.  (MHD 11/9/93)


;;; Show-workspace ... If this is called when servicing workstations, visibility
;;; is required of all workspaces shown.
;;;
;;; ... Pane-name? is new for 6.0, but it is not currently being exposed to users
;;; through any interfaces.  It is possible it will be used in future versions of
;;; the product.  [MHD 11/10/99]

;;; The g2-window-or-client-session? is actually an g2-window or
;;; client-session, i.e., in the "g2-window" case it may be either a proper
;;; g2-window instance or a workspace-view instance.  In either case, it is
;;; checked for belonging to a Telewindows session that is logged in. If it is
;;; not logged in, the request to show a workspace is silently ignored.

;; IMPLEMENT:
;;
;; Above-or-below-or-t-for-same? controls stacking of the image planes within a
;; pane.  If this is nil, the default, then the image plane is always shown at
;; the top of the stack of image planes.  If it is T, the image plane is shown
;; at its current position, if any, or at the top, if none.  Otherwise, this
;; should be either ABOVE or BELOW, and its interpretation depends on
;; specific-workspace-or-t-for-group?, as follows.
;;
;; If specific-workspace-or-t-for-group? is a workspace, then this is put above,
;; or below if above-or-below-or-t-for-same? is BELOW, that workspace, if it is
;; found in the pane.  If it is not found, then it's put at the top of the image
;; plane stack.  Note that the value can be the same as the workspace for the
;; argument block-or-workspace.  This then can be used to implement a 1+ ("1
;; closer to front") or 1- ("1 further back") feature.
;;
;; If specific-workspace-or-t-for-group? is T, then the image plane is put no
;; higher, or lower if above-or-below-or-t-for-same? is BELOW, than it needs to
;; be to be just above, or below, those image planes whose rectangles intersect
;; this image plane's.
;;
;; Otherwise, specific-workspace-or-t-for-group? should be nil, and the image
;; plane is simply put above, or, if above-or-below-or-t-for-same? is BELOW,
;; below, all other image planes in the pane.

(defun show-workspace
    (block-or-workspace
      g2-window-or-client-session?
      &optional
      go-to-block?
      symbolic-x-scale? symbolic-y-scale?
      symbolic-x-in-workspace? symbolic-y-in-workspace?
      symbolic-x-in-window? symbolic-y-in-window?
      x-offset-units? symbolic-x-offset-direction?
      y-offset-units? symbolic-y-offset-direction?
      x-magnification? y-magnification?
      x-in-workspace? y-in-workspace?
      x-in-window? y-in-window?
      above-or-below-or-t-for-same?
      specific-workspace-or-t-for-group?
      (require-visibility? servicing-workstation?))
  (let* ((workspace? (or (get-workspace-if-any block-or-workspace)
                         (return-from show-workspace nil)))
         (g2-window-p
           (and g2-window-or-client-session?
                (frame-of-class-p g2-window-or-client-session? 'g2-window)))
         (workstation?
           (or (if g2-window-p
                   (workstation-for-g2-window? g2-window-or-client-session?))
               (if servicing-workstation?
                   current-workstation))))
    (macrolet ((call-subfunction-passing-args (function-name target-var)
                 `(,function-name block-or-workspace workspace?
                                  ,target-var
                                  go-to-block? require-visibility?
                                  symbolic-x-scale? symbolic-y-scale?
                                  symbolic-x-in-workspace? symbolic-y-in-workspace?
                                  symbolic-x-in-window? symbolic-y-in-window?
                                  x-offset-units? symbolic-x-offset-direction?
                                  y-offset-units? symbolic-y-offset-direction?
                                  x-magnification? y-magnification?
                                  x-in-workspace? y-in-workspace?
                                  x-in-window? y-in-window?
                                  above-or-below-or-t-for-same?
                                  specific-workspace-or-t-for-group?)))
      (cond (workstation?
             (let ((g2-window? (g2-window-for-this-workstation? workstation?)))
               (when (and g2-window?
                          (logged-in-workstation-session-p workstation?))
                 (call-subfunction-passing-args
                   show-workspace-1 (window-for-workstation workstation?)))))
            ((and g2-window-or-client-session?
                  (frame-of-class-p g2-window-or-client-session?
                                    'ui-client-session))
             (call-subfunction-passing-args
               update-ui-client-for-show
               g2-window-or-client-session?))
            ((and (not g2-window-p)
                  g2-window-or-client-session?) ; if not one of our favorite class
             nil)                           ; just ignore - shouldn't happen
            (t                              ; tell the whole world
             (loop for workstation in workstations-in-service
                   when (eq (workstation-login-state workstation) 'logged-in)
                     do
                       (call-subfunction-passing-args
                         show-workspace-1
                         (window-for-workstation workstation)))
             (loop for session being each class-instance
                   of 'ui-client-session
                   do
               (call-subfunction-passing-args
                 update-ui-client-for-show session)))))))


;;; `Show-workspace-1' is usually called from the inference engine to show block
;;; on workspace in gensym-window per various parameters.  All of the parameters
;;; after are evaluation values.  It is also used for various other purposes,
;;; such as "go-to" commands in the user interface (e.g., get-workspace,
;;; go-to-original).
;;;
;;; This is a subfunction of show-workspace.
;;;
;;; In the go-to-block? case, all of the parameters following go-to-block?  are
;;; actually ignored.  In this case, the image is transformed so that the block
;;; is centered in the pane, and, as well, the mouse is "warped" to the center
;;; of the block.
;;;
;;; In the case where go-to-block? is nil, we transform the image to show
;;; workspace according to the parameters following go-to-block?, where
;;; applicable, and according to the position and scale remembered from when the
;;; workspace was last hidden.
;;;
;;; If require-visibility? is true, move the image plane, if necessary, to be
;;; minimally visible.

(defun show-workspace-1 (block workspace gensym-window go-to-block?
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
  (declare (ignore                        ; later!
             specific-workspace-or-t-for-group?))

  (when (workspace-show-or-hide-hook workspace gensym-window 'show)
    (return-from show-workspace-1 nil))

  (let* ((pane
           (or (detail-pane gensym-window)
               (RETURN-FROM show-workspace-1 nil))) ; bail out if no pane
         (workstation (workstation-this-is-on gensym-window))
         (image-plane? (get-image-if-any workspace pane))
         (workspace-was-hidden? (null image-plane?))
         (remembered-position-and-scale
           (if workspace-was-hidden?
               (getf
                 (plist-of-remembered-window-positions-and-scales workspace)
                 (pane-name pane)))))
    (when (workspaces-can-be-shown-at-this-kb-level-p workspace workstation)
      ;; => showing this workspace not restricted

      ;; if workspace is not on an image plane, get an image plane
      (unless image-plane?
        (setf image-plane?
              (get-available-image-plane
                pane
                (lookup-frame-description-reference-of-block-in-pane? workspace pane)
                nil)))
      (following-lead-image-plane-in-stack-of-coupled-image-planes (image-plane?)
        (cond
          (go-to-block?
           (transform-image                        ; show at full scale, centered
             image-plane? workspace                ;   on block, at the front
             (get-default-image-x-scale image-plane?)
             (get-default-image-y-scale image-plane?)
             nil block nil nil nil nil nil nil nil nil t)
           (warp-mouse-to-center-of-workstation-window workstation))
          (t
           (multiple-value-bind
               (x-scale? y-scale?
                         x-in-workspace? y-in-workspace?
                         x-in-window? y-in-window?)
               (decode-evaluation-show-parameters
                 block image-plane? remembered-position-and-scale
                 symbolic-x-scale? symbolic-y-scale?
                 symbolic-x-in-workspace? symbolic-y-in-workspace?
                 symbolic-x-in-window? symbolic-y-in-window?
                 x-offset-units? symbolic-x-offset-direction?
                 y-offset-units? symbolic-y-offset-direction?
                 x-magnification? y-magnification?
                 x-in-workspace? y-in-workspace?
                 x-in-window? y-in-window?)
             (transform-image
               image-plane? workspace x-scale? y-scale? nil nil
               x-in-workspace? y-in-workspace? x-in-window? y-in-window?
               nil nil nil nil
               ;; This will be the value of the raise-image-plane-to-top?
               ;; argument to transform-image.  (ghw 5/11/98)
               (not above-or-below-or-t-for-same?))
             (when require-visibility?
               (require-that-image-plane-be-visible image-plane?))))))

      ;; put-image-on-image-plane was supposed to be the only interface for
      ;; exposing new workspaces, but it's not.
      (when (and workspace-was-hidden? (selection-enabled-p gensym-window))
        ;; GENSYMCID-1668: Using TWNG with our application (gms native menus in twng,
        ;;                 popup menus appear behind the workspace initiating the popup)
        (select-workspace workspace workstation)))))



;;; `Lookup-frame-description-reference-of-block-in-pane?' is like
;;; lookup-frame-description-reference-of-block (in module DRAW), but it prefers
;;; the default frame style for the block in the pane, i.e., taking into account
;;; the window-specific UI preference, ahead of the DEFAULT default frame style.

(defun-simple lookup-frame-description-reference-of-block-in-pane? (block pane)
  (let* ((workstation-for-pane (workstation-this-is-on (gensym-window-for-pane pane))))
    (for-workstation (workstation-for-pane)
      (lookup-frame-description-reference-of-block? block))))






;;; Structure of type `show-parameters-decoder' hold information used for
;;; decoding show parameters. ...

(def-structure (show-parameters-decoder
                 (:constructor make-show-parameters-decoder))

  ;; Show area:
  ;;   usually from window parameters plist:
  (minimum-scale-for-show-area nil)
  (default-x-scale-for-show-area nil)
  (default-y-scale-for-show-area nil)
  ;;   usually from image plane:
  (image-x-scale-for-show-area nil)
  (image-y-scale-for-show-area nil)
  (left-edge-for-show-area nil)
  (top-edge-for-show-area nil)
  (right-edge-for-show-area nil)
  (bottom-edge-for-show-area nil))





;;; The function `decode-evaluation-show-parameters' is called at runtime to
;;; decode the (mostly) symbolic show parameters, which are actually evaluation
;;; values.
;;;
;;; This is a subfunction of show-workspace-1.
;;;
;;; Remembered-position-and-scale? is the remembered position and scale, which
;;; should be supplied non-nil only if the workspace was previously hidden (i.e.,
;;; this is a newly initialized image plane).
;;;
;;; Symbolic-x/y-scale? may be one of the following:
;;;
;;;   ONE-QUARTER, HALF, THREE-QUARTER, FULL, CURRENT
;;;
;;; X/y-magnification? may be an integer or float that is used to magnify the
;;; symbolic scale, which defaults (ultimately) to the current scale, if there
;;; is one, or else simple "full scale" (default-x-scale/default-y-scale).
;;; (Note: in practice, this parameter is always paired with either FULL or
;;; CURRENT; see the grammar in GRAMMAR3.)
;;;
;;; The following may be integers or floats:
;;;
;;;   x-offset-units? y-offset-units?
;;;   x-in-workspace? y-in-workspace?
;;;   x-in-window? y-in-window?

(defun decode-evaluation-show-parameters
    (block image-plane remembered-position-and-scale?
           symbolic-x-scale? symbolic-y-scale?
           symbolic-x-in-workspace? symbolic-y-in-workspace?
           symbolic-x-in-window? symbolic-y-in-window?
           x-offset-units? symbolic-x-offset-direction?
           y-offset-units? symbolic-y-offset-direction?
           x-magnification? y-magnification?
           x-in-workspace? y-in-workspace?
           x-in-window? y-in-window?)
  (let* ((gensym-window
           (gensym-window-for-pane
             (pane-for-image-plane image-plane)))
         (decoder (make-show-parameters-decoder)))
    (setf (minimum-scale-for-show-area decoder)                        ; assumed > 1
          (get-gensym-window-parameter gensym-window 'minimum-scale))
    (setf (default-x-scale-for-show-area decoder)
          (get-gensym-window-parameter gensym-window 'default-x-scale))
    (setf (default-y-scale-for-show-area decoder)
          (get-gensym-window-parameter gensym-window 'default-y-scale))
    (setf (image-x-scale-for-show-area decoder) (image-x-scale image-plane))
    (setf (image-y-scale-for-show-area decoder) (image-y-scale image-plane))
    (setf (left-edge-for-show-area decoder)
          (left-edge-of-pane-in-window image-plane))
    (setf (top-edge-for-show-area decoder)
          (top-edge-of-pane-in-window image-plane))
    (setf (right-edge-for-show-area decoder)
          (right-edge-of-pane-in-window image-plane))
    (setf (bottom-edge-for-show-area decoder)
          (bottom-edge-of-pane-in-window image-plane))
    (decode-show-parameters-for-show-area
      block decoder
      remembered-position-and-scale?
      symbolic-x-scale? symbolic-y-scale?
      symbolic-x-in-workspace? symbolic-y-in-workspace?
      symbolic-x-in-window? symbolic-y-in-window?
      x-offset-units? symbolic-x-offset-direction?
      y-offset-units? symbolic-y-offset-direction?
      x-magnification? y-magnification?
      x-in-workspace? y-in-workspace?
      x-in-window? y-in-window?)))

(defun decode-show-parameters-for-show-area
    (block decoder
      remembered-position-and-scale?
      symbolic-or-numeric-x-scale? symbolic-or-numeric-y-scale?
      symbolic-x-in-workspace? symbolic-y-in-workspace?
      symbolic-x-in-window? symbolic-y-in-window?
      x-offset-units? symbolic-x-offset-direction?
      y-offset-units? symbolic-y-offset-direction?
      x-magnification? y-magnification?
      x-in-workspace? y-in-workspace?
      x-in-window? y-in-window?
      &optional do-not-reclaim-decoder-p)
  (let* ((x-scale?
           (if (or x-magnification?
                   symbolic-or-numeric-x-scale?
                   remembered-position-and-scale?)
               (with-temporary-gensym-float-creation show-x-scaling
                 (maxf (minimum-scale-for-show-area decoder)
                       (round-for-show
                         (* (or x-magnification? 1)
                            (cond
                              ((not (symbolp symbolic-or-numeric-x-scale?))
                               symbolic-or-numeric-x-scale?) ; numeric case
                              (symbolic-or-numeric-x-scale?
                               (if (eq symbolic-or-numeric-x-scale? 'current)
                                   (image-x-scale-for-show-area decoder)
                                   (scale-scale
                                     (default-x-scale-for-show-area decoder)
                                     (case symbolic-or-numeric-x-scale?
                                       (one-quarter 1)
                                       (half 2)
                                       (three-quarter 3)
                                       (full 4))
                                     4)))
                              (remembered-position-and-scale?
                               (scale-scale
                                 (third remembered-position-and-scale?)
                                 (default-x-scale-for-show-area decoder)
                                 (normalized-scale)))
                              (t
                               (image-x-scale-for-show-area decoder)))))))))
         (y-scale?
             (if (or y-magnification?
                     symbolic-or-numeric-y-scale?
                     remembered-position-and-scale?)
                 (with-temporary-gensym-float-creation show-y-scaling
                   (maxf (minimum-scale-for-show-area decoder)
                         (round-for-show
                           (* (or y-magnification? 1)
                              (cond
                                ((not (symbolp symbolic-or-numeric-y-scale?))
                                 symbolic-or-numeric-y-scale?) ; numeric case
                                (symbolic-or-numeric-y-scale?
                                 (if (eq symbolic-or-numeric-y-scale? 'current)
                                     (image-y-scale-for-show-area decoder)
                                     (scale-scale
                                       (default-y-scale-for-show-area decoder)
                                       (case symbolic-or-numeric-y-scale?
                                         (one-quarter 1)
                                         (half 2)
                                         (three-quarter 3)
                                         (full 4))
                                       4)))
                                (remembered-position-and-scale?
                                 (scale-scale
                                   (fourth remembered-position-and-scale?)
                                   (default-y-scale-for-show-area decoder)
                                   (normalized-scale)))
                                (t
                                 (image-y-scale-for-show-area decoder)))))))))
         (x-in-window?
           (or (if x-in-window?
                   (+r (halfr (+r (left-edge-for-show-area decoder)
                                  (right-edge-for-show-area decoder)))
                       (round-for-show x-in-window?)))
               (case symbolic-x-in-window?
                 (center
                  (halfr (+r (left-edge-for-show-area decoder)
                             (right-edge-for-show-area decoder))))
                 (left (left-edge-for-show-area decoder))
                 (right (right-edge-for-show-area decoder)))
               (if remembered-position-and-scale?
                   (delta-x-in-window
                     (first remembered-position-and-scale?)
                     (scale-scale
                       (normalized-scale)
                       (default-x-scale-for-show-area decoder)
                       (normalized-scale))))))
         (y-in-window?
           (or (if y-in-window?
                   (+r (halfr (+r (top-edge-for-show-area decoder)
                                  (bottom-edge-for-show-area decoder)))
                       (-r (round-for-show y-in-window?))))
               (case symbolic-y-in-window?
                 (center
                  (halfr (+r (top-edge-for-show-area decoder)
                             (bottom-edge-for-show-area decoder))))
                 (top (top-edge-for-show-area decoder))
                 (bottom (bottom-edge-for-show-area decoder)))
               (if remembered-position-and-scale?
                   (delta-y-in-window
                     (second remembered-position-and-scale?)
                     (scale-scale
                       (normalized-scale)
                       (default-y-scale-for-show-area decoder)
                       (normalized-scale))))))
         (x-in-workspace?
           (or (if x-in-workspace? (round-for-show x-in-workspace?))
               (case symbolic-x-in-workspace?
                 (center
                  (halfr (+r (left-edge-of-block block)
                             (right-edge-of-block block))))
                 (left (left-edge-of-block block))
                 (right (right-edge-of-block block)))))
         (y-in-workspace?
           (or (if y-in-workspace? (-w (round-for-show y-in-workspace?)))
               (case symbolic-y-in-workspace?
                 (center
                  (halfr (+r (top-edge-of-block block)
                             (bottom-edge-of-block block))))
                 (top (top-edge-of-block block))
                 (bottom (bottom-edge-of-block block)))))
         (x-offset-units-in-raster-units?
           (when x-offset-units?
             (let ((rounded-x-offset-units (round-for-show x-offset-units?)))
               (if t ; (>=r most-negative-raster-coordinate  ; implement this later!
                                        ;      rounded-x-offset-units
                                        ;      most-positive-raster-coordinate)
                   rounded-x-offset-units))))
         (y-offset-units-in-raster-units?
           (when y-offset-units?
             (let ((rounded-y-offset-units (round-for-show y-offset-units?)))
               (if t ; (>=r most-negative-raster-coordinate  ; implement this later!
                                        ;      rounded-y-offset-units
                                        ;      most-positive-raster-coordinate)
                   rounded-y-offset-units)))))
    (when (and x-in-window? x-offset-units-in-raster-units? symbolic-x-offset-direction?)
      (case symbolic-x-offset-direction?
        (right (incfr x-in-window? x-offset-units-in-raster-units?))
        (left (decfr x-in-window? x-offset-units-in-raster-units?))))
    (when (and y-in-window? y-offset-units-in-raster-units? symbolic-y-offset-direction?)
      (case symbolic-y-offset-direction?
        (above (decfr y-in-window? y-offset-units-in-raster-units?))
        (below (incfr y-in-window? y-offset-units-in-raster-units?))))
    (unless do-not-reclaim-decoder-p
      (reclaim-show-parameters-decoder decoder))
    (values x-scale? y-scale?
            (or x-in-workspace?
                (if x-in-window? 0))
            (or y-in-workspace?
                (if y-in-window? 0))
            x-in-window? y-in-window?)))




;;; The function `decode-show-details-as-phrase-list' is to be called in a
;;; phrase compiling context, i.e., in an edit context, from the compiler.  It
;;; returns a phrase-cons list of 16 elements:
;;;
;;; note: names of elements ending with ? indicate they are nil, or as named.
;;; note: names of elements that have include the word "symbolic" will be
;;; quoted (i.e., inclosed in a (QUOTE x) form as x), unless they are nil.
;;;
;;;      (1) symbolic-x-scale?        (2) symbolic-y-scale?
;;;      (3) symbolic-x-in-workspace? (4) symbolic-y-in-workspace?
;;;      (5) symbolic-x-in-window?    (6) symbolic-y-in-window?
;;;      (7) x-offset-units?          (8) symbolic-x-offset-direction?
;;;      (9) y-offset-units?          (10) symbolic-y-offset-direction?
;;;      (11) x-magnification?        (12) y-magnification?
;;;      (13) x-in-workspace?         (14) y-in-workspace?
;;;      (15) x-in-window?            (16) y-in-window?

(defun decode-show-details-as-phrase-list (show-details)
  (let* ((scaling-details (assoc 'scale show-details))
         (workspace-position-details (assoc 'workspace-position show-details))
         (screen-position-details (assoc 'screen-position show-details))

         (scaling-subdetails (cadr scaling-details))

         (symbolic-x-scale? nil)
         (symbolic-y-scale? nil)
         (x-magnification? nil)
         (y-magnification? nil)

         (symbolic-x-in-workspace? nil) (symbolic-y-in-workspace? nil)

         (symbolic-x-in-window? nil) (symbolic-y-in-window? nil)

         (symbolic-x-offset-direction? nil) (x-offset-units? nil)
         (symbolic-y-offset-direction? nil) (y-offset-units? nil)

         (x-in-workspace? nil) (y-in-workspace? nil)
         (x-in-window? nil) (y-in-window? nil))

    (cond
      ((null scaling-subdetails))
      ((atom scaling-subdetails)
       (setq symbolic-y-scale?
             (setq symbolic-x-scale? scaling-subdetails)))
      (t
       (setq symbolic-y-scale?
             (setq symbolic-x-scale? (first scaling-subdetails)))
       (setq x-magnification? (second scaling-subdetails))
       (setq y-magnification? (or (third scaling-subdetails) x-magnification?))))
    (cond
      ((null screen-position-details))        ; unspecified
      ((and (caddr screen-position-details)        ; => center
            (atom (caddr screen-position-details)))
       (setq symbolic-x-in-window? 'center)
       (setq symbolic-y-in-window? 'center))
      ((and (consp (second screen-position-details))
            (eq (first (second screen-position-details)) 'at))
       (setq x-in-window? (second (second screen-position-details)))
       (setq y-in-window? (third (second screen-position-details))))
      (t
       (case (car (caddr screen-position-details))
         (left (setq symbolic-x-in-window? 'left))
         (top (setq symbolic-y-in-window? 'top))
         (right (setq symbolic-x-in-window? 'right))
         (bottom (setq symbolic-y-in-window? 'bottom)))
       (case (cadr (caddr screen-position-details))
         (center
          (if (memq (car (caddr screen-position-details)) '(top bottom))
              (setq symbolic-x-in-window? 'center)
              (setq symbolic-y-in-window? 'center)))
         (left (setq symbolic-x-in-window? 'left))
         (right (setq symbolic-x-in-window? 'right)))))
    (when (and (not (atom (cadr screen-position-details)))
               (not (eq (first (second screen-position-details)) 'AT)))
      (loop for (direction units) on (cadr screen-position-details)
                                  by 'cddr        ; only 1 or 2 iterations possible
            do (case direction
                 ((above below)
                  (setq symbolic-y-offset-direction? direction)
                  (setq y-offset-units? units))
                 (t                        ; (right left)
                  (setq symbolic-x-offset-direction? direction)
                  (setq x-offset-units? units)))))

    (cond
      ((and (null screen-position-details)        ; unspecified
            (null workspace-position-details)))
      ((and (if workspace-position-details        ; center
                (cadr workspace-position-details)
                (caddr screen-position-details))
            (atom (if workspace-position-details        ; center
                      (cadr workspace-position-details)
                      (caddr screen-position-details))))
       (setq symbolic-x-in-workspace? 'center)
       (setq symbolic-y-in-workspace? 'center))
      (t
       (case (if workspace-position-details
                 (car (cadr workspace-position-details))
                 (car (caddr screen-position-details)))
         (left (setq symbolic-x-in-workspace? 'left))
         (top (setq symbolic-y-in-workspace? 'top))
         (right (setq symbolic-x-in-workspace? 'right))
         (bottom (setq symbolic-y-in-workspace? 'bottom))
         (t (setq x-in-workspace?
                  (if workspace-position-details
                      (car (cadr workspace-position-details))
                      (car (caddr screen-position-details))))))
       (case (if workspace-position-details
                 (cadr (cadr workspace-position-details))
                 (cadr (caddr screen-position-details)))
         (center
          (if (memq (if workspace-position-details
                        (car (cadr workspace-position-details))
                        (car (caddr screen-position-details)))
                    '(top bottom))
              (setq symbolic-x-in-workspace? 'center)
              (setq symbolic-y-in-workspace? 'center)))
         (left (setq symbolic-x-in-workspace? 'left))
         (right (setq symbolic-x-in-workspace? 'right))
         (t (setq y-in-workspace?
                  (if workspace-position-details
                      (cadr (cadr workspace-position-details))
                      (cadr (caddr screen-position-details))))))))

    (phrase-list
      (phrase-quote-if-non-nil symbolic-x-scale?)
      (phrase-quote-if-non-nil symbolic-y-scale?)
      (phrase-quote-if-non-nil symbolic-x-in-workspace?)
      (phrase-quote-if-non-nil symbolic-y-in-workspace?)
      (phrase-quote-if-non-nil symbolic-x-in-window?)
      (phrase-quote-if-non-nil symbolic-y-in-window?)
      x-offset-units? (phrase-quote-if-non-nil symbolic-x-offset-direction?)
      y-offset-units? (phrase-quote-if-non-nil symbolic-y-offset-direction?)
      x-magnification? y-magnification?
      x-in-workspace? y-in-workspace?
      x-in-window? y-in-window?)))

;; Note: this was converted to a list-returning function, from a values returning
;; function, in order to work around a low limit on the maximum number of values
;; in Chestnut's Lisp-to-C translator.   If the limit is upped in Chestnut, consider
;; converting this back, along with fixing its caller in PROC-INST.  (MHD 1/4/93)


(defun phrase-quote-position-spec-if-not-symbolic (position-spec)
  (if (member position-spec
              '(left top right bottom center nil))
      (phrase-quote-if-non-nil position-spec)
      position-spec))

(defun phrase-quote-if-non-nil (value)        ; move to somewhere else?!
  (if value (phrase-list 'quote value)))





;;; `Warp-mouse-to-center-of-workstation-window' warps the mouse the center
;;; of the window associated with workstation, if possible.

(defun warp-mouse-to-center-of-workstation-window (workstation)
  (for-workstation (workstation)        ; center mouse
    (set-cursor-position
      (halfr (-r (right-edge-of-window current-workstation-window)
                 (left-edge-of-window current-workstation-window)))
      (halfr (-r (bottom-edge-of-window current-workstation-window)
                 (top-edge-of-window current-workstation-window))))))



;;; Round-for-show is used by show-workspace to round evaluation values that
;;; must be turned into fixnums (coordinates or scales) prior to interfacing to
;;; the low-level G2 window management functions.
;;;
;;; It assumes that its argument is either a fixnum, evaluation float, or gensym
;;; float.
;;;
;;; Rounding is different from CLtL, but the same as done in the evaluator, with
;;; one additional feature: the result number is guaranteed to be a fixnum,
;;; adding or subtracting from the argument number if necessary.

(defun-simple round-for-show (evaluation-number-or-gensym-float)
  (if (evaluation-integer-p evaluation-number-or-gensym-float)
      evaluation-number-or-gensym-float
      (with-temporary-gensym-float-creation show-workspace
        (let* ((float-value
                 (if (evaluation-float-p evaluation-number-or-gensym-float)
                     (evaluation-float-value evaluation-number-or-gensym-float)
                     evaluation-number-or-gensym-float))
               (truncatable-float-value
                 (if (>e float-value 0.0)
                     (mine (+e float-value 0.5) most-positive-fixnum-as-float)
                     (maxe (-e float-value 0.5) most-negative-fixnum-as-float))))
          (declare (type gensym-float truncatable-float-value))
          (truncate truncatable-float-value)))))

;; restrict to some other range, e.g., legal coordinates??!





;;; Get-image-if-any returns an image plane that workspace is on in pane.
;;; This is intended to be used under the constraint that at most one
;;; image plane per workspace is ever present.

(defun get-image-if-any (workspace pane)
  ;; two-pronged attack strategy:
  (loop for remaining-image-planes-this-is-on
          = (image-planes-this-is-on workspace)
          then (cdr remaining-image-planes-this-is-on)
        for remaining-image-planes-in-pane
          = (stack-of-image-planes pane)
          then (cdr remaining-image-planes-in-pane)
        while (or remaining-image-planes-this-is-on
                  remaining-image-planes-in-pane)
        when (and remaining-image-planes-this-is-on
                  (eq (pane-for-image-plane (car remaining-image-planes-this-is-on))
                      pane))
          return (car remaining-image-planes-this-is-on)
        when (and remaining-image-planes-in-pane
                  (eq (workspace-on-image-plane?
                        (car remaining-image-planes-in-pane))
                      workspace))
          return (car remaining-image-planes-in-pane)))


;;; `Autocreate-g2-window' creates an instance of g2-window-subclass, which must
;;; be a subclass of g2-window, in the proper way for autocreated G2 windows.
;;; This means that it can be treated as an item by user code, but it will not
;;; be saved in the KB.  Nor will it interfere with saving a KB, including in
;;; modules.  Nor will it be deleted upon reset.

(defun autocreate-g2-window (g2-window-subclass)
  (let ((g2-window (make-frame g2-window-subclass)))
    (set-permanent-block g2-window)
    ;; Set this bit to keep from saving and enable autodeletion:
    (set-do-not-save-in-kb g2-window)
    ;; activate this thing:
    (funcall-method 'activate-if-possible-and-propagate g2-window)
    g2-window))

;; Misc. utility routines:


;;; The function `logged-in-workstation-session-p' can be called with any
;;; workstation, whether for a multiwindow UI or not, and returns true if the
;;; session is logged in; otherwise false (nil).  This abstracts the details of
;;; fetching parent workstations in the multiwindow case in order to test the
;;; workstation-login-state slot of that workstation.  Note that, if iterating
;;; over workstations-in-service in order to operate on logged-in parent
;;; workstations only, it's recommended to test the workstation-login-state slot
;;; directly on each workstation, since only the parent workstation has that
;;; slot set when the session is logged in.

(defun logged-in-workstation-session-p (workstation)
  (eq (workstation-login-state workstation) 'logged-in))



;;;; Beeping



;;; Beep-in-g2-window is to be called from a "system procedure" -- it must be
;;; passed a g2 window (frame) associated with a logged in gensym window/
;;; workstation to work.  But it expects anything and exhaustively checks its
;;; argument.  It returns the evaluation value false if it is certain that no
;;; beep occurred, and the evaluation value true otherwise.

;; Following declaration is necessary for calling this function from G2 via the
;; "system call" action.  jh, 8/23/91.
;; Updated to use system-procedure declaration.  - cpm, 8/3/93.
(declare-system-procedure-function beep-in-g2-window t)

;;; should support any ui-client-item at some point

(defun beep-in-g2-window (potential-g2-window)
  (if (and (framep potential-g2-window)
           (frame-of-class-p potential-g2-window 'g2-window))
      (let ((workstation? (workstation-for-g2-window?-function
                            potential-g2-window)))
        (if (and workstation?
                 (logged-in-workstation-session-p workstation?))
            (let ((gensym-window? (window-for-workstation workstation?)))
              (cond (gensym-window?
                     (beep-in-window gensym-window?)
                     (copy-evaluation-truth-value-function evaluation-true-value))
                    (t (copy-evaluation-truth-value-function evaluation-false-value))))
            (copy-evaluation-truth-value-function evaluation-false-value)))
      (copy-evaluation-truth-value-function evaluation-false-value)))

;; Consider notifying the user what the problem is if the above cannot be done.
;; jh, 8/2/91.  For the moment, we will simply return false if we know we couldn't
;; beep, and true otherwise.  Made these changes today.






;;;; Going to Frames



;;; Goto-frame-instance can show frame on its workspace, if it is on a workspace.  If
;;; frame is not on a workspace but has a ancestral frame on a workspace, it can show
;;; the closest ancestor on its workspace.  If neither frame nor any of frame's
;;; ancestors is on a workpace, it can notify the user that it cannot show frame
;;; because it is not on a workspace.

;;; If frame can be shown, it is unless showing that workspace is prohibited due to
;;; user restrictions.

;;; If the block that ends up being shown is a workspace, then it is shown at its last
;;; remembered position and scale; otherwise, the workspace the block to be shown is
;;; on is positioned such that the block is in the center of the detail pane of
;;; current-workstation-window, and the mouse is also warped to that position.

;;; Goto-frame-instance must be called in a for-workstation context.

(defun goto-frame-instance (frame)
  (let ((block-on-workspace? (get-block-on-workspace-for-frame frame)))
    (cond
      ((null block-on-workspace?)
       (notify-user                                ; BUG!?
         "Sorry, G2 cannot show this object because it is not on any workspace!"))
      (t
       (show-or-hide
         block-on-workspace? t nil nil
         (not (workspace-p frame)))))))

;; This should warn of an ambiguity and allow the user to choose!!

;; Consider NOT being able to do this for everything (e.g. formats)!!



;;; The function `allow-go-to-frame-instance-p' is supposed to be T for those
;;; blocks for which goto-frame-instance does something.

(defun allow-go-to-frame-instance-p (item)
  (and (get-block-on-workspace-for-frame item)
       (not (proprietary-p item))))





;;; Get-block-on-workspace-for-frame ... returns either nil or two values: a block
;;; on a workspace and that workspace.  The block returned will in some way be
;;; "for" frame.

;;; If frame is a connection, the output end object of the connection and its
;;; workspace are returned.

(defun get-block-on-workspace-for-frame (frame)
  (let ((workspace? nil))
    (cond
      ((and (block-p frame)
            (setq workspace? (get-workspace-if-any frame)))
       (values frame workspace?))
      ((frame-of-class-p frame 'connection)
       ;; What this does isn't very satisfying, esp. in "go to original" in
       ;;   inspect because it just puts you on the block that is the output end
       ;;   of the connection; this is OK when that is a loose end, but poor in
       ;;   most other cases. Fix!! (Added by MHD 9/16/88)
       (let ((output-end-object
               (output-end-object (connection-for-this-connection-frame frame))))
         (if (setq workspace?  (get-workspace-if-any output-end-object))
             (values output-end-object workspace?))))
      (t
       (loop with parent-frame? = frame
             do (setq parent-frame?
                      (if (frame-of-class-p
                            parent-frame?
                            'simulation-subtable)        ; subclass of block now. (MHD 7/10/91)
                          (get-slot-value
                            parent-frame? 'parent-variable)
                          (if (block-p parent-frame?)
                              (get-kb-parent-information parent-frame?))))
                (if parent-frame?
                    (if (block-p parent-frame?)
                        (if (setq workspace?
                                  (get-workspace-if-any parent-frame?))
                            (return (values parent-frame? workspace?))))
                    (return nil)))))))







;;;; Concluding Symbolic Parameters from a Field Edit



;;; Conclude-symbolic-parameter-for-field-edit does a "conclude" action on
;;; symbolic-parameter, concluding symbol as its value.  This function is
;;; intended for use the the field edit facility of the editor.

(defun conclude-symbolic-parameter-for-field-edit (symbolic-parameter symbol)
  ;; The following should be able to work while paused.  FIND ME, JRA!  -jra
  ;; 11/16/96
  (if (and system-is-running (not system-has-paused))
      (with-temporary-gensym-float-creation
        conclude-symbolic-parameter-for-field-edit
        (multiple-value-bind (cached-value expiration type)
            (convert-constant-attribute-value-to-cached-value symbol)
          (let ((*current-computation-frame* symbolic-parameter))
            (put-current-value
              symbolic-parameter
              cached-value type expiration nil))))))





;;;; Field Edits

;; Section moved here wholesale from EDIT2 -- edit2 is too early for this all to
;; live because of the need to access macros defined for the evaluation system.
;;
;; To do: abstract pure-editor functionality and ship it back.  Merge the above
;; section with this one.  Reduce the tentative nature of the comments.  Define
;; system procedures using modern defining forms, handling type format
;; conversion declaratively.  !!! (MHD 1/10/95)


;; To compile this facility from AB 3.1 sources in a 3.0 (Lispm) environment:
;;
;;   (1) compile the defstructure for edit-state in PARSE;
;;   (2) compile the function enter-editing-context-on-text-box in FACILITIES;
;;   (3) Compile the entire buffer (file) EDIT;
;;   (4) compile the section "Concluding Symbolic Parameters from a Field Edit"
;;       in CONTROLS;
;;   (5) compile the function system-reset in CYCLES
;;
;; NOTE: this will ruin all existing G2 processes (due to the redefinition of
;; the edit state structure).  You must create new G2 processes after following
;; these steps.


;; To do:
;;
;; (1) DONE: Cancel/End Current Field Edit
;; (2) Parse for a Grammar Category
;; (3) Edit a Slot
;; (4) Make up several categories that can be parsed.
;;
;; TO DO: (!!!!)  Handle cleanup in abort case -- i.e., aborting the procedure.
;; This must be done prior to releasing 4.0.  See if this can just be done in
;; the procedure itself.

;; Issues:
;;
;; How to abort a context if it's not the top-level one?  Ans: That's not
;; a problem, just delete the edit workspace.  The problem is completing it.)
;;
;; How to End if not on top?  Ans: pull it to the top using a new feature
;; and disciplin of workstation contexts that allows this.
;;
;; What if the window is secure, and not logged into?  What if it gets logged
;; out of?


;;; The `field edit' facility defines four functions to be funcalled by system
;;; procedures:
;;;
;;;    edit-message-as-field-for-user
;;;    cancel-current-field-edit-if-any
;;;    update-current-field-edit-if-any
;;;    cancel-current-field-edit-if-any
;;;
;;; ...






;;; Edit-message-as-field-for-user ... This is called from a system procedure,
;;; and so may rely on its arguments being as expected.

;;; A `field edit' is a little different from a normal edit.  The tab key, which
;;; normally adds horizontal whitespace to the text being edited, serves to end
;;; the editing session for a field edit.  And the UPDATE function (a subcommand
;;; button) is disabled for a field edit, whereas it serves normally to allow
;;; you to update the original text being edited without exiting the current
;;; edit context.

;;; ... There are three sets of possible final return values.  The first is the
;;; "cannot-enter" variety:
;;;
;;;    cannot-enter-for-some-unknown-reason
;;;    cannot-enter-because-field-edit-in-progress
;;;    cannot-enter-because-restricted
;;;    cannot-enter-because-not-showing
;;;
;;; The second is the "exit" variety:
;;;
;;;    cancel-exit   (caused by
;;;    tab-exit
;;;    end-exit
;;;
;;; The third is the "action" variety:
;;;
;;;    cancel-action
;;;    end-action

;;; This function returns either ENTERED-EDITOR or one of the "cannot-enter" variety
;;; of final return values shown above.  If this returns nil, then the editor was
;;; entered, and the user can begin entering text into the editor; in this case, the
;;; system-procedure caller must wait until edit-status-symbolic-parameter
;;; receives a value.  At that time, the value it receives should be one of the
;;; possible final return values above.  If this returns non-nil, then it did
;;; not enter the editor or any other workstation context, and the value returned
;;; will be one of the "cannot-enter" variety of return values shown above.

;;; Only one field edit is allowed per window.  If there is a field edit already
;;; in progress in g2-window, this returns cannot-enter-because-edit-in-progress.

;;; This function can deal with edit-status-symbolic-parameter being deleted after
;;; the editor has been exited.  It is presumably the case, however, that the calling
;;; system procedure will abort automatically if that happened, since it is presumably
;;; monitoring that object waiting for its value to change.
;;;
;;; In 3.0, edit-message-as-field-for-user is always called with edit-style? =
;;; nil.  In 4.0, it may be called without this arg, effectively with it as nil,
;;; or with an instance of the class edit-style, a user-defined class that's
;;; defined by the Gensym-proprietary UIL KL.  This class defines several
;;; attributes that are effectively parameters to the field edit procedure, and
;;; allow fine-grained control over numerous editing parameters.


;;; `get-type-of-slot-for-user-edit'

(defun-simple get-type-of-slot-for-user-edit (class? attribute? defining-class?)
  (and class?
       (let* ((slot-name (unalias-slot-name-if-necessary attribute? class?))
              (class-description? (class-description class?))
              (slot-description?
                (and class-description?
                     (get-slot-description-of-class-description
                       slot-name class-description? defining-class?))))
         (and slot-description?
              (feature-assq
                'type
                (slot-features slot-description?))))))


;;; The macro `with-editor-return-value' sets up a context such that the given
;;; symbolic parameter will receive a value when the edit context invoked in the
;;; body exits or aborts.

(defmacro with-editor-return-value ((symbolic-parameter) &body body)
  `(with-old-style-workstation-return-function
       ('return-from-field-edit
	  (slot-value-list
	    ,symbolic-parameter
	    (copy-frame-serial-number
	      (frame-serial-number
		,symbolic-parameter)))
	  'reclaim-list-and-record-abort-in-edit-status-parameter)
     ,@body))


;;; `edit-message-as-field-for-g2-window'

(defun-void edit-message-as-field-for-g2-window
    (message edit-status-symbolic-parameter
             workstation image-plane type-of-slot?
             edit-style?)
  (for-workstation (workstation)
    ;; GENSYMCID-1466: Re: Signal 11 Abort
    (loop until (valid-workstation-context-p
                  specific-structure-for-current-workstation-context)
          do (abort-current-workstation-context type-of-current-workstation-context))
    (with-editor-return-value (edit-status-symbolic-parameter)
      (enter-field-editing-context
        message image-plane edit-style? type-of-slot?))))



;;; `edit-message-as-field-for-t2-toolkit'

(defun-void edit-message-as-field-for-t2-toolkit
    (message ui-client-item edit-status-symbolic-parameter
             type-of-slot? edit-style? class? attribute? defining-class?)
  (let ((field-edit-info
          (make-ui-client-session-field-edit
            message
            ui-client-item
            edit-status-symbolic-parameter
            attribute?
            class?
            defining-class?
            type-of-slot?
            edit-style?)))
    (setf (ui-client-session-field-edit ui-client-item)
          field-edit-info)
    (notify-ui-client-session-of-field-edit-action-if-any
      ui-client-item 'CREATE
      (copy-evaluation-structure field-edit-info))))


;;; `edit-message-as-field-for-user'

(declare-system-procedure-function edit-message-as-field-for-user nil
                                   (message ui-client-item edit-status
                                            &optional edit-style? class? attribute? defining-class?))

(defun edit-message-as-field-for-user
    (message ui-client-item edit-status
             &optional edit-style? class? attribute? defining-class?)
  ;; ADD "USER-FRIENDLY" TYPE CHECKING HERE!  (Aborting in the G2 system
  ;; procedure sense is fine.)
  (unless (and class?
               attribute?
               defining-class?
               (symbolp class?)
               (symbolp attribute?)
               (symbolp defining-class?))
    (setq class? nil)
    (setq attribute? nil)
    (setq defining-class? nil))
  (multiple-value-bind (exit-status? workstation image-plane)
      (prepare-to-edit-message-as-field message ui-client-item)
    (or exit-status?
        (let ((type-of-slot? (get-type-of-slot-for-user-edit
                               class? attribute? defining-class?)))
          (cond
            ((and class? (null type-of-slot?))
             'CANNOT-ENTER-BECAUSE-ATTRIBUTE-UNKNOWN)
            ((frame-of-class-p ui-client-item 'g2-window)
             (edit-message-as-field-for-g2-window
               message edit-status
               workstation image-plane type-of-slot?
               edit-style?)
             'ENTERED-EDITOR)
            (t
             (edit-message-as-field-for-t2-toolkit
               message ui-client-item edit-status
               type-of-slot? edit-style?
               class? attribute? defining-class?)
             'ENTERED-EDITOR))))))


;; What to do about the UPDATE function?  How to handle that?  If you return, then
;; the calling function has to either loop on such a value -- a much more complicated
;; protocol -- or possibly not stay on top of what the end-user is really editing and
;; changing.  Our current solution is to define the field editor's behavior as
;; suppressing the update function as inconsistent with field editing, just as the
;; TAB function is redefined here to exit instead of insert whitespace.  -- mhd, 8/31/92

;; Note, however, there is nothing to protect against some inference engine activity
;; from putting in some illegal value or some fake legal value.  Deal with this
;; deficiency later! -- mhd, 8/31/92

;; How to deal with the inference engine getting paused or reset in the middle of
;; the edit session this launches.  If paused, we can set up a task to run when
;; resumed that puts the final-exit value.  If reset, we should probably abort the
;; editor.  If we ever do confirmations of aborts, would those presumably have to
;; be done in order for the reset to complete?  Hmmm. -- MHD, 8/31/92




;;; `Prepare-to-edit-message-as-field' returns the following three values:
;;;
;;;    (1) exit-status? -- nil if the field can be edited, or else a
;;;           symbol that is to go back to the user as the reason for
;;;           failure;
;;;
;;;    (2) workstation? -- nil iff exit-status? is non-nil; otherwise,
;;;           the workstation in which to edit, which was derived from
;;;           g2-window;
;;;
;;;    (3) image-plane? -- nil iff exit-status? is non-nil; otherwise,
;;;           the image plane upon which to edit in place
;;;
;;; This can be thought of, then, as returning one of two possible sets of
;;; values: (1) the single value of an exit status, and (2) nil followed
;;; by the workstation and image-plane on which to edit.

(defun prepare-to-edit-message-as-field (message ui-client-item)
  (let (workstation? image-plane? workspace? editing-disallowed-in-ui-client-item?)
    (setq editing-disallowed-in-ui-client-item?
          (cond ((frame-of-class-p ui-client-item 'g2-window)
                 (setq workstation? (workstation-for-g2-window?-function ui-client-item))
                 (cond
                   ((not (and workstation?
                              (logged-in-workstation-session-p workstation?)
                              (null (type-of-modal-context? workstation?))))
                    'CANNOT-ENTER-FOR-SOME-UNKNOWN-REASON) ; later - better reason!!
                   ((get-field-edit-workspace-if-any ui-client-item)
                    'CANNOT-ENTER-BECAUSE-FIELD-EDIT-IN-PROGRESS)
                   (t
                    (for-workstation (workstation?)
                      (setq workspace? (get-workspace-if-any message))
                      (setq image-plane?
                            (if workspace?
                                (get-image-if-any
                                  workspace? current-workstation-detail-pane)))
                      (when (null image-plane?)
                        'CANNOT-ENTER-BECAUSE-NOT-SHOWING)))))
                ((frame-of-class-p ui-client-item 'ui-client-session)
                 (setq workspace? (get-workspace-if-any message))
                 (cond (nil ;((not (and workspace?
                               ; (workspace-is-showing-in-ui-client-item
                            ;  workspace? ui-client-item)))
                        'CANNOT-ENTER-BECAUSE-NOT-SHOWING)
                       ((ui-client-session-field-edit ui-client-item)
                        'CANNOT-ENTER-BECAUSE-FIELD-EDIT-IN-PROGRESS)))
                (t
                 'UNKNOWN-CLASS-OF-WINDOW-FOR-FIELD-EDIT)))
    (cond (editing-disallowed-in-ui-client-item?)
          (t
           (let* ((slot-name 'box-translation-and-text)
                  (type-of-slot?
                    (type-of-slot-if-editable (class message) slot-name))
                  (defining-class
                      (defining-class
                          (get-slot-description-of-frame slot-name message))))
             (cond
               ((not (and type-of-slot?
                          (or (transient-p message)
                              (permanent-block-p message))
                          ;; if a text slot, not stripped:
                          (or (not (text-slot-type-p type-of-slot?))
                              (not (stripped-text-p
                                     (cdr (get-slot-value message slot-name))))
                              (frame-of-class-p message 'message)))); for when this is generalized
                'CANNOT-ENTER-FOR-SOME-UNKNOWN-REASON)        ; later - better reason!!
               ((not (edit-attribute-allowed-p message slot-name defining-class))
                'CANNOT-ENTER-BECAUSE-RESTRICTED)
               (t
                (values nil workstation? image-plane?))))))))



;;; `Reclaim-list-and-record-abort-in-edit-status-parameter' may be called as a return
;;; function from the editor for the edit-message-as-field function.  This expects
;;; list to have in it (<frame-or-recycled-frame> <frame-serial-number>).  However,
;;; the "normal" return function arranges for this function only to be called in the
;;; case of an abort exit.  (In the case of a normal, non-abort exit, the pointer to
;;; this reclaimer is to be set to nil, causing it not to be invoked.)  Thus, when
;;; this is called, it knowns we are aborting, and so, it sets the value of the
;;; symbolic parameter to CANCEL-EXIT, provided that it has not been deleted since
;;; the editor was invoked, which is determined using <frame-serial-number>.  Conses
;;; are returned to the slot-value cons pool.

(defun reclaim-list-and-record-abort-in-edit-status-parameter (list)
  (if (not (frame-has-been-reprocessed-p (first list) (second list)))
      (conclude-symbolic-parameter-for-field-edit
        (first list) 'cancel-exit))
  (reclaim-frame-serial-number (second list))
  (reclaim-slot-value-list list))



;;; `Return-from-field-edit' returns from the edit workstation context from an
;;; edit launched by edit-message-as-field-for-user.  This expects to find a
;;; list of a symbolic parameter, used to record edit status, along with its
;;; frame serial number.  Provided that the symbolic parameter has not been
;;; deleted, this puts into it the value of the edit-status slot type-of-exit?
;;; which corresponds to one of the exiting values documented for edit-message-
;;; as-field-for-user.

(defun return-from-field-edit (workstation-context)
  (let* ((edit-status-and-sn (workstation-context-return-information workstation-context))
         (edit-status (first edit-status-and-sn))
         (frame-serial-number (second edit-status-and-sn)))
    (in-editing-context (specific-structure-for-current-workstation-context)
      (if (not (frame-has-been-reprocessed-p edit-status frame-serial-number))
          (conclude-symbolic-parameter-for-field-edit
            edit-status
            (type-of-exit-from-edit-context? current-edit-state))))
    (reclaim-slot-value-list edit-status-and-sn)
    (setf (workstation-context-return-information-reclaimer? workstation-context)
          nil) ; our reclaimer function only to be called in abort case
    (reclaim-frame-serial-number frame-serial-number)
    (exit-current-workstation-context-in-return-function 'editing)))






#+development
(defun system-g2-window ()
  (g2-window-for-this-workstation? (workstation-this-is-on system-window)))



;;; `Get-field-edit-workspace-if-any' returns the edit workspace for the current,
;;; the only, field edit workspace in the workstation for g2-window, provided
;;; there is a valid one.  It also returns several additional values.  The entire
;;; set of values is as follows:
;;;
;;;    (1) the edit workspace;
;;;    (2) the edit-status symbolic parameter;
;;;    (3) the workstation context for the edit state;
;;;    (4) the frame being edited;
;;;    (5) the name of the slot being edited;
;;;    (6) the class qualifier for the slot being edited, if any
;;;    (7) the type of the slot being edited; and
;;;    (8) the edit box

(defun get-field-edit-workspace-if-any (g2-window)
  (let ((workstation? (workstation-for-g2-window?-function g2-window)))
    (if workstation?
        (loop with edit-status-symbolic-parameter?
              with edit-status-frame-serial-number?
              for workstation-context
                  in (workstation-context-stack workstation?)
              as edit-state?
                 = (if (eq (type-of-workstation-context workstation-context) 'editing)
                       (specific-structure-for-workstation-context workstation-context))
              when (and edit-state?
                        (eq (old-workstation-context-return-function?
                              workstation-context)
                            'return-from-field-edit)
                        (and (setq edit-status-symbolic-parameter?
                                   (first
                                     (workstation-context-return-information
                                       workstation-context)))
                             (setq edit-status-frame-serial-number?
                                   (second
                                     (workstation-context-return-information
                                       workstation-context)))
                             (not (frame-has-been-reprocessed-p
                                    edit-status-symbolic-parameter?
                                    edit-status-frame-serial-number?)))
                        (valid-block-in-workstation-context-p
                          (edit-workspace edit-state?)
                          edit-state?)
                        (and (frame-being-edited? edit-state?)
                             (not (frame-has-been-reprocessed-p
                                    (frame-being-edited? edit-state?)
                                    (serial-number-of-frame-being-edited?
                                      edit-state?)))))
                return
                  (values
                    (edit-workspace edit-state?)
                    edit-status-symbolic-parameter?
                    workstation-context
                    (frame-being-edited? edit-state?)
                    (name-of-slot-being-edited edit-state?)
                    (defining-class-for-slot-being-edited? edit-state?)
                    (type-of-slot-being-edited edit-state?)
                    (edit-box edit-state?))))))






;;; `Cancel-current-field-edit-if-any' ... This is to be funcalled by a system
;;; procedure.

(declare-system-procedure-function cancel-current-field-edit-if-any nil (ui-client-item))

(defun cancel-current-field-edit-if-any (ui-client-item)
  (cond ((frame-of-class-p ui-client-item 'g2-window)
         (multiple-value-bind (edit-workspace? edit-status-symbolic-parameter
                                               edit-workstation-context)
             (get-field-edit-workspace-if-any ui-client-item)
           (when edit-workspace?
             (delete-frame edit-workspace?)
             (finish-field-edit-and-record-status
               edit-status-symbolic-parameter 'cancel-action
               edit-workstation-context))))
        ((frame-of-class-p ui-client-item 'ui-client-session)
         (notify-ui-client-session-of-field-edit-action-if-any
           ui-client-item 'CANCEL nil))))


;;; `End-current-field-edit-if-any' ... This is to be funcalled by a system
;;; procedure.

(declare-system-procedure-function end-current-field-edit-if-any nil (ui-client-item))

(defun end-current-field-edit-if-any (ui-client-item)
  (cond ((frame-of-class-p ui-client-item 'g2-window)
         (multiple-value-bind (edit-workspace? edit-status-symbolic-parameter
                                               edit-workstation-context
                                               frame-being-edited slot-name defining-class?
                                               type-of-slot edit-box)
             (get-field-edit-workspace-if-any ui-client-item)
           (when edit-workspace?
             (let ((copy-of-text-being-edited
                     (copy-text (cdr (box-translation-and-text edit-box)))))
               (if (parse-text-for-slot
                     copy-of-text-being-edited
                     frame-being-edited
                     (get-slot-description-of-frame
                       slot-name frame-being-edited defining-class?)
                     t type-of-slot)
                   (finish-field-edit-and-record-status
                     edit-status-symbolic-parameter 'end-action
                     edit-workstation-context)))
             (delete-frame edit-workspace?))))
        ((frame-of-class-p ui-client-item 'ui-client-session)
         (notify-ui-client-session-of-field-edit-action-if-any
           ui-client-item 'END nil))))



;;; `Update-current-field-edit-if-any' ... This is to be funcalled by a system
;;; procedure.

(declare-system-procedure-function update-current-field-edit-if-any nil (ui-client-item))

(defun update-current-field-edit-if-any (ui-client-item)
  (cond ((frame-of-class-p ui-client-item 'g2-window)
         (multiple-value-bind (edit-workspace? edit-status-symbolic-parameter
                                               edit-workstation-context
                                               frame-being-edited slot-name defining-class?
                                               type-of-slot edit-box)
             (get-field-edit-workspace-if-any ui-client-item)
           (declare (ignore edit-status-symbolic-parameter edit-workstation-context))
           (or (if edit-workspace?
                   (let ((copy-of-text-being-edited
                           (copy-text (cdr (box-translation-and-text edit-box)))))
                     (if (parse-text-for-slot
                           copy-of-text-being-edited
                           frame-being-edited
                           (get-slot-description-of-frame
                             slot-name frame-being-edited defining-class?)
                           t type-of-slot)
                         (copy-evaluation-truth-value-function
                           evaluation-true-value))))
               (copy-evaluation-truth-value-function
                 evaluation-false-value))))
        ((frame-of-class-p ui-client-item 'ui-client-session)
         (notify-ui-client-session-of-field-edit-action-if-any
           ui-client-item 'UPDATE nil))))

;; Bug in 3.0: the version of the above function in 3.0 returns NIL if
;; edit-workspace? is nil; it should have returned the falsity truth value.
;; That bug has now been corrected in 4.0. (MHD 8/13/94)


(defun-system-rpc (g2-finish-field-edit-and-record-status (truth-value))
    ((rpc-instance system-rpc-instance)
     (session (class ui-client-session))
     (status symbol))
  (return-from-system-defined-rpc
      rpc-instance
      (eval-list
        (if (finish-ui-client-session-field-edit-and-record-status session status)
            evaluation-true-value
            evaluation-false-value))))

(defun finish-ui-client-session-field-edit-and-record-status (session status)
  (let ((field-edit? (ui-client-session-field-edit session))
        parameter?)
    (when field-edit?
      (setq parameter? (evaluation-structure-slot
                         field-edit?
                         'edit-status-symbolic-parameter))
      (conclude-symbolic-parameter-for-field-edit parameter? status)
      (change-slot-value session 'ui-client-session-field-edit nil)
      t)))

(defun finish-field-edit-and-record-status
       (edit-status-symbolic-parameter status edit-workstation-context)
  (conclude-symbolic-parameter-for-field-edit edit-status-symbolic-parameter status)
  (reclaim-slot-value-list
    (workstation-context-return-information edit-workstation-context))
  (setf (workstation-context-return-information edit-workstation-context)
        nil)
  (setf (workstation-context-return-information-reclaimer? edit-workstation-context)
        nil))

(defun-system-rpc (g2-update-ui-client-session-field-edit (truth-value))
    ((rpc-instance system-rpc-instance)
     (session (class ui-client-session))
     (new-text text))
  (return-from-system-defined-rpc
      rpc-instance
      (eval-list
        (if (update-ui-client-session-field-edit session new-text)
            evaluation-true-value
            evaluation-false-value))))

(defun update-ui-client-session-field-edit (session new-text)
  (let ((field-edit? (ui-client-session-field-edit session))
        frame-being-edited
        slot-name
        defining-class?
        type-of-slot)
    (when field-edit?
      (setq frame-being-edited (evaluation-structure-slot field-edit? 'message))
      (setq slot-name (evaluation-structure-slot field-edit? 'slot-name))
      (setq defining-class? (evaluation-structure-slot field-edit? 'defining-class))
      (setq type-of-slot (evaluation-structure-slot field-edit? 'type-of-slot))
      (parse-text-for-slot
        (convert-text-string-to-text (copy-text-string new-text));copy???
        frame-being-edited
        (get-slot-description-of-frame
          slot-name frame-being-edited defining-class?)
        t type-of-slot))))




;;; Cancel-all-field-edits-in-session ... This is to be called by system-reset
;;; to cancel all field edits in session.

(defun cancel-all-field-edits-in-session ()
  (loop for ui-client-item being each class-instance of 'ui-client-item
        do (cancel-current-field-edit-if-any ui-client-item)))


;; When a field edit is in session before a pause, it stays in session until
;; a resume.  If ended while paused, ....[SPECIFY?!] (MHD 10/6/92)





;;; `Refresh-field-edit-from-message' and `refresh-field-edit-with-text' change
;;; the text of the specified field edit edit box to a given text, specified as
;;; either a message or an actual text.
;;;
;;; They both return a truth-value: truth if successful, falsity otherwise.
;;;
;;; The intended use of these functions is to adjust the content of the edit box
;;; before the user has begun editing it.  It can also be used to reset the text
;;; to a legal value after an attempt has been made to commit ("update") it with
;;; a bogus one.
;;;
;;; These are the lisp-side functions used by system procedures.  The system
;;; procedures have the responsibility of doing the class type checking on the
;;; message and g2-window arguments; the lisp function only declares them to be
;;; of type "item".

(defun-for-system-procedure refresh-field-edit-from-message
    ((message item) (ui-client-item item))
  (declare (values truth-value))
  (let ((text-string
          (convert-text-to-text-string
            (cdr (box-translation-and-text message)))))
    (prog1
        (refresh-field-edit-with-text-1 message ui-client-item text-string)
      (reclaim-text-string text-string))))

(defun-for-system-procedure refresh-field-edit-with-text
    ((message item) (ui-client-item item) (text-string text))
  (declare (values truth-value))
  (refresh-field-edit-with-text-1 message ui-client-item text-string))


;;; `Refresh-field-edit-with-text-1' ... text-string is not reclaimed.
;;; (workstation-for-g2-window? ui-client-item) shouldn't be nil

(defun refresh-field-edit-with-text-1 (message ui-client-item text-string)
  (cond ((frame-of-class-p ui-client-item 'g2-window)
         (multiple-value-bind
             (edit-workspace? edit-status-symbolic-parameter
                              workstation-context frame-being-edited)
             (get-field-edit-workspace-if-any ui-client-item)
           (declare (ignore edit-status-symbolic-parameter))
           (or (when (and edit-workspace?
                          (eq frame-being-edited message)
                          (workstation-for-g2-window? ui-client-item))
                 ;; error otherwise?!
                 (for-workstation ((workstation-for-g2-window? ui-client-item))
                   (in-editing-context
                       ((specific-structure-for-workstation-context workstation-context))
                     (replace-entire-edit-box-text text-string)))
                 truth)
               falsity)))
        ((frame-of-class-p ui-client-item 'ui-client-session)
         (notify-ui-client-session-of-field-edit-action-if-any
           ui-client-item 'REFRESH
           (allocate-evaluation-structure-inline
             'new-value
             (copy-text-string text-string))))))

;; The above is prepared to bind the editing context even if it is not the top
;; level one.  There are no known problems with the above, but a constraint
;; should be established that allows this, the code should be examined to ensure
;; compliance.  Also, the doc. for in-editing-context should be changed to allow
;; for this case; the code is fine for this as is (now that it takes the edit
;; state as a parameter, rather than using the top of the workstation context
;; stack).  Ideally, the editor could be pumped through any number of
;; transformations directly through the edit-state, rather than ever needing
;; a workstation context!  (MHD 1/9/94)






;;;; Entering an Editing Context via Field Edit

(def-class (field-edit-representation
             callback-representation define-predicate)
  (field-edit-representation-user-data-value t vector-slot))

;;; NOTE: This macro binds many variables.  This is not meant for general usage,
;;; but rather for abstracting old field edit code for usage with remote cliens.

(defmacro with-edit-style-attributes ((edit-style-arg text-box-arg) &body body)
  `(let* ((edit-style? ,edit-style-arg)
          (text-box ,text-box-arg)
          (editor-scroll-decision-override?
            (case (get-edit-style-attribute edit-style? 'multiline-mode)
              (default nil)
              ((nil) 'never)
              (t 'always)))
          ;; DO TYPE ERROR CHECKING HERE LATER!! (Here, require all symbols.)
          (editor-specific-natural-language-override?
            (get-edit-style-attribute edit-style? 'language-specific-editor nil))
          (editor-frame-style-override?
            (get-edit-style-attribute edit-style? 'frame-style nil))
          (editor-background-color-override?
            (get-edit-style-attribute edit-style? 'background-color nil))
          (editor-text-color-override?
            (get-edit-style-attribute edit-style? 'text-color nil))
          (editor-font-size-override?        ; note that this precludes use of the text-box's
                                        ;   own format -- rather sad! (MHD 1/7/95)
            (get-edit-style-attribute edit-style? 'font-size nil))
          (editor-block-font-override?
            (get-edit-style-attribute edit-style? 'use-block-font nil))
          (editor-initial-editor-height-override?
            (get-edit-style-attribute edit-style? 'initial-editor-height nil))
          (full-editor?
            (non-menu-choice-permitted-p 'full-editor text-box))
          (in-place-editing?
            (get-edit-style-attribute
              edit-style? 'in-place-editing (not full-editor?)))
          (buttons-visible?
            (get-edit-style-attribute
              edit-style? 'buttons-visible
              (or full-editor?
                  (non-menu-choice-permitted-p
                    'option-buttons-for-edit-in-place text-box))))
          (menus-visible?
            (get-edit-style-attribute
              edit-style? 'menus-visible
              (or full-editor?
                  (non-menu-choice-permitted-p
                    'menus-for-edit-in-place text-box))))
          (clear-before-edit?
            (get-edit-style-attribute
             edit-style?
             'clear-before-edit
             (and (not full-editor?)
                  (not (non-menu-choice-permitted-p
                         'do-not-clear-text-for-edit-in-place text-box)))))
          (initial-text-or-edit-box?
            (if clear-before-edit?
                (make-empty-text))))
     . ,body))

(def-slot-value-reclaimer ui-client-session-field-edit (field-edit ui-client-session)
  (declare (ignore ui-client-session))
  (reclaim-evaluation-structure field-edit))

(defun make-ui-client-session-field-edit
    (message
      ui-client-session
      edit-status-symbolic-parameter
      attribute
      class?
      defining-class
      type-of-slot
      edit-style?)
  (let ((CURRENT-G2-USER-MODE?
          (or (ui-client-session-user-mode ui-client-session)
              'ADMINISTRATOR))
        (structure (allocate-evaluation-structure-inline)))
    (macrolet ((add-slot-if-needed (name value)
                 ;; assume value is a symbol
                 `(when ,value
                    (setf (evaluation-structure-slot
                            structure ,name)
                          ,value))))
      (setf type-of-slot (and type-of-slot (coerce-to-free-text-type-of-slot type-of-slot)))
      (with-edit-style-attributes (edit-style? message)
        (add-slot-if-needed 'message message)
        (add-slot-if-needed 'edit-status-symbolic-parameter edit-status-symbolic-parameter)
        (add-slot-if-needed 'attribute attribute)
        (add-slot-if-needed 'class class?)
        (add-slot-if-needed 'defining-class defining-class)
        (add-slot-if-needed 'type-of-slot
                            type-of-slot)
        (add-slot-if-needed 'slot-name 'BOX-TRANSLATION-AND-TEXT)
        (add-slot-if-needed 'editor-scroll-decision-override
                              editor-scroll-decision-override?) ;nil never always
        (add-slot-if-needed 'editor-specific-natural-language-override
                            editor-specific-natural-language-override?)
        (add-slot-if-needed 'editor-frame-style-override editor-frame-style-override?)
        (add-slot-if-needed 'editor-background-color-override editor-background-color-override?)
        (add-slot-if-needed 'editor-text-color-override editor-text-color-override?)
        (add-slot-if-needed 'editor-font-size-override editor-font-size-override?)
        (add-slot-if-needed 'editor-block-font-override editor-block-font-override?)
        (add-slot-if-needed 'editor-initial-editor-height-override
                            editor-initial-editor-height-override?)
        (add-slot-if-needed 'full-editor' full-editor?)
        (add-slot-if-needed 'in-place-editing in-place-editing?)
        (add-slot-if-needed 'buttons-visible buttons-visible?)
        (add-slot-if-needed 'menus-visible menus-visible?)
        (add-slot-if-needed 'clear-before-edit clear-before-edit?)
        (add-slot-if-needed 'initial-text-or-edit-box initial-text-or-edit-box?)))
    structure))

(defun notify-ui-client-session-of-field-edit-action-if-any
    (ui-client-session action-symbol extra-info)
  (let ((field-edit? (ui-client-session-field-edit ui-client-session)))
    (cond (field-edit?
           (loop with current-frame-serial-number-on-entry = (copy-frame-serial-number (current-frame-serial-number))
                 with representations = (collect-frames-of-class (frame-representations ui-client-session)
                                                                'field-edit-representation)
                 for representation in representations
                 do
             (when (and (not (frame-has-been-reprocessed-p representation
                                                           current-frame-serial-number-on-entry))
                        (representation-address-valid-p representation))
               (let* ((address (representation-address representation))
                      (socket (getf address 'socket))
                      (message (evaluation-structure-slot field-edit? 'message))
                      (workspace (and message (get-workspace-if-any message)))
                      (argument-list
                        (eval-list
                          (make-evaluation-symbol action-symbol)
                          workspace
                          (or extra-info (allocate-evaluation-structure nil));bug
                          (field-edit-representation-user-data-value representation)
                          (callback-representation-callback-subscription-handle representation)))) ; the "subscription handle"
                 (callback-representation-fire-callback
                   representation socket argument-list)))
                 finally (reclaim-frame-serial-number current-frame-serial-number-on-entry)
                         (reclaim-gensym-list representations))
           truth)
          (t
           falsity))))

;;; If type-of-slot? is specified, it is used to specify the grammar, overriding
;;; the usual grammar/parsing that would be done (or, in the case of free text,
;;; not done) for the given block/slot-name/defining-class combination.

(defun enter-field-editing-context
    (text-box image-plane edit-style? type-of-slot?)
  (with-edit-style-attributes (edit-style? text-box)
    (enter-editing-context
      text-box
      'box-translation-and-text                ; ignore defining-class issue for now!
      initial-text-or-edit-box?
      nil ;; edit-workspace-hidden?
      (if editor-block-font-override?
          (create-blob-edit-box-format)
          (when (and (text-box-p text-box)
                     ; see "precludes" note above! (MHD  1/7/95)
                     (null editor-font-size-override?))
            (text-box-format text-box)))
      nil ;; width-for-cell?
      nil ;; cursor-line-index?
      nil ;; cursor-character-index?
      (if in-place-editing? image-plane)
      (if in-place-editing? text-box)
      ;; {left,top,right,bottom}-edge-of-cell-in-table-on-which-to-edit-in-place?
      nil nil nil nil
      (if type-of-slot?
          (coerce-to-free-text-type-of-slot type-of-slot?))
      nil ;; special-entry-context?
      nil ;; function-to-call-on-changed-edit-box-text?
      (not buttons-visible?) ;; do-not-have-edit-option-buttons?
      (not menus-visible?))  ;; do-not-have-edit-menus?
    (let ((edit-state specific-structure-for-current-workstation-context))
      (setf (editing-field? edit-state) t)
      (setf (do-not-allow-secondary-selection? edit-state)
            (not (get-edit-style-attribute
                   edit-style?
                   'allow-outside-text-selection
                   t)))
      (setf (never-confirm-cancelled-edit? edit-state)
            (not (get-edit-style-attribute
                   edit-style?
                   'confirm-cancelled-edit
                   t))))))

;;; `Coerce-to-text-type-of-slot' returns either type-of-slot, if that is a text
;;; type slot; if not, it returns a version of type-of-slot that is a text-type
;;; slot, either by obtaining a cached copy or by creating (and caching) a copy.
;;;
;;; This is to be used to implement the feature needed by field edit that a type
;;; of slot can be passed in with a text type value.

(def-global-property-name saved-free-text-version-of-type-of-slot)

(defun coerce-to-free-text-type-of-slot (type-of-slot)
  (if (text-slot-type-p type-of-slot)
      type-of-slot
      (or (saved-free-text-version-of-type-of-slot
            (second type-of-slot))
          (setf (saved-free-text-version-of-type-of-slot
                  (second type-of-slot))
                (with-dynamic-creation
                    (nconc (copy-list type-of-slot)
                           (list 'text)))))))

;; Introduced in 4.0 Beta. (MHD 12/23/94)




(def-global-property-name uil-edit-style-name-for-attribute)
(def-global-property-name uil-edit-style-filter-function-for-attribute)

(defmacro define-uil-edit-style-names-for-attributes (tag &rest names-and-filters)
  (declare (ignore tag))
  `(progn
     . ,(loop for (name filter-function) in names-and-filters
              collect
              `(setf (uil-edit-style-name-for-attribute ',name)
                     ',(intern (format nil "UIL-FIELD-EDIT-~a" name)))
              collect
              `(setf (uil-edit-style-filter-function-for-attribute ',name)
                     ',filter-function))))

(define-uil-edit-style-names-for-attributes edit-style
  (multiline-mode filter-edit-style-boolean-for-field-edit)
  (in-place-editing filter-edit-style-boolean-for-field-edit)
  (buttons-visible filter-edit-style-boolean-for-field-edit)
  (menus-visible filter-edit-style-boolean-for-field-edit)

  ;; This attribute refers to the swiping of text to insert that text into the
  ;; editor.  It so happens that Guide edit-styles do not declare an attribute
  ;; of this name, which means that it can't be controlled from Guide.

  ;; Adding to the confusion, there is another attribute which Guide does
  ;; define in its field-edit styles, uil-field-edit-allow-secondary-selection,
  ;; which, in the user-model, was supposed to control pending-delete (ie,
  ;; typing characters when there was an active text-region would delete the
  ;; text in the region and then insert the characters).  Nobody on the G2 side
  ;; implements that feature, however.  -fmw, 8/21/95
  (allow-outside-text-selection filter-edit-style-boolean-for-field-edit)

  (select-before-edit                        ; not yet implemented
    filter-edit-style-boolean-for-field-edit)
  (clear-before-edit filter-edit-style-boolean-for-field-edit)
  (confirm-cancelled-edit
    filter-edit-style-boolean-for-field-edit)
  (post-edit-operations-menu                ; not yet implemented
    filter-edit-style-boolean-for-field-edit)

  (language-specific-editor
    filter-edit-style-symbol-for-field-edit)
  (frame-style
    filter-edit-style-symbol-for-field-edit)
  (background-color
    filter-edit-style-color-for-field-edit)
  (text-color
    filter-edit-style-color-for-field-edit)
  (font-size
    filter-edit-style-font-size-for-field-edit)
  (use-block-font
    filter-edit-style-boolean-for-field-edit)
  (initial-editor-height
    filter-edit-style-positive-integer-for-field-edit))


(defun filter-edit-style-positive-integer-for-field-edit (x default)
  (if (fixnump x)
      x
      default))

(defun filter-edit-style-font-size-for-field-edit (x default)
  (if (memq x '(small large extra-large))
      x
      default))

(defun filter-edit-style-color-for-field-edit (x default)
  (if (and (symbolp x) (color-or-metacolor-p x))
      x
      default))

(defun filter-edit-style-symbol-for-field-edit (x default)
  (if (symbolp x)
      x
      default))


;;; Filter-edit-style-boolean-for-field-edit ... wants x to be an evaluation
;;; truth value.  It returns T, NIL, or DEFAULT.

(defun filter-edit-style-boolean-for-field-edit (x default)
  (if (and (evaluation-value-p x)
           (evaluation-truth-value-p x))
      (if (evaluation-truth-value-is-true-p x)
          't
          'nil)
      default))








;;; Get-edit-style-attribute safely accesses the slot named attribute-name, if
;;; present, in the frame edit-style?, if non-nil, which should be of class
;;; edit-style, a UIL-defined "user-defined" class.  If the attribute does not
;;; exist, is "none", i.e., nil, or has as its value DEFAULT, this returns the
;;; value of default, which defaults to DEFAULT.  If its value is "false", i.e.,
;;; the false truth value, this returns nil.  Otherwise, this returns its value.

(defun get-edit-style-attribute
    (edit-style? attribute-name &optional (default 'DEFAULT))
  (let* ((slot-value
           (if edit-style?
               (get-slot-value-if-any
                 edit-style?
                 (uil-edit-style-name-for-attribute attribute-name))))
         (evaluation-value
           (cond
             ((slot-constantp slot-value)
              (cast-slot-constant-into-evaluation-value slot-value))
             ((evaluation-value-p slot-value)
              slot-value)
             (t default)))                ; tough luck otherwise!
         (filter-function?
           (uil-edit-style-filter-function-for-attribute
             attribute-name)))
    (if filter-function?
        (funcall filter-function? evaluation-value default)
        evaluation-value)))


;; This needs either to have the newer options passed in as args to
;; enter-editing-context (sad, and already done for the multiline-mode option --
;; never say never) or for the structure, or one similar, to be passed in.  (MHD
;; 8/15/94)

;; This needs more working out of the user-selectable portion with DWR, since
;; the passing in of the mouse position were not considered/dealt with.






;;;; GDA-Private UI Procedures



(defun-for-system-procedure g2-hide-name-box (block)
  (loop for subblock being each subblock of block
        do
    (when (frame-of-class-p subblock 'name-box)
      (delete-block-for-user subblock 0 0)
      (return))))

(defun-for-system-procedure g2-hide-attribute-displays (block)
  (loop for subblock being each subblock of block
        do
    (when (frame-of-class-p subblock 'table)
      (delete-block-for-user subblock 0 0))))





;;;; System Procedure Stubs for G2 as CORBA Client



;;; `corba-preprocess-idl' stub

;;; NOTE: it was recently discovered this system procedure is called from a
;;; regression test procedure, specifically the procedure corba-preprocess-idl
;;; in tests/itempass.kb.  It is NOT called from sys-mod.kb, so it is NOT
;;; officially supported.  But we want to keep it here to keep the regression
;;; test working. (MHD 7/16/02)

(defun-for-system-procedure corba-preprocess-idl
    (g2-filestring)
  (declare (keeps-g2-local-variables-valid t))
  (notify-user "The G2 System Procedure CORBA-PREPROCESS-IDL is no longer ~
                supported.  Please contact Gensym Customer Support")
  (let ((g2-array? (make-transient-item 'g2-array)))
    g2-filestring
    (change-slot-value g2-array? 'g2-array-length 0)
    g2-array?))

;; This subsection was moved here from the decomissioned module JAVA2
;; today. (MHD 7/16/02)




;;;; System Procedures to Launch Telewindows


(def-gensym-c-function c-run-telewindows
    (:fixnum-int "g2ext_run_telewindows_here")
  ())

(defun-for-system-procedure g2-launch-telewindows-here ()
  (c-run-telewindows))




;;;; Dialog Views


;;; The structure `dialog-view' brings native custom dialogs into the fold of
;;; the native windows, native image-planes, tree views, etc, facility. This is
;;; important, both to get dialogs into the same handle space, and to make a MDI
;;; child dialog view able to be the selected window.

(def-structure (dialog-view
                 (:include native-view)
                 (:constructor make-dialog-view-1)
                 (:reclaimer reclaim-dialog-view-1)
                 #+development (:print-function print-native-window))
  (dialog-view-custom-dialog? nil))

;; TODO: all we're doing here is reserving the name for 8.1a0.
(def-class (g2-dialog-view g2-native-view (foundation-class g2-dialog-view)
                           do-not-put-in-menus not-user-instantiable))

(defun make-dialog-view (gensym-window custom-dialog %title container options &optional callback?)
  (let ((dv (make-dialog-view-1)))
    (initialize-native-view dv gensym-window 'g2-dialog-view container options callback?)
    (setf (native-window-title? dv) %title     ; Take ownership of string.
	  (dialog-view-custom-dialog? dv) custom-dialog)
    dv))

(def-structure-method clean-up-structure (dialog-view)
  (setf (dialog-view-custom-dialog? dialog-view) nil) ; TODO: Reclaim or not?
  (funcall-superior-method dialog-view))

(defun dialog-panes-p (gensym-window)
  (and (twng-window-p gensym-window)
       (window-supports-dialog-panes gensym-window)))



;;;; Custom (Dynamic) Dialogs -- G2 Side


;;; `custom-dialog' cons pool

(defconser custom-dialog CONTROLS)


;;; `reclaim-custom-dialog-list-function'

(defun reclaim-custom-dialog-list-function (list)
  (reclaim-custom-dialog-list list))


;;; `reclaim-custom-dialog-list-with-text-strings'

(defun-void reclaim-custom-dialog-list-with-text-strings (list?)
  (when list?
    (loop for text in list?
          do
      (reclaim-text-string text))
    (reclaim-custom-dialog-list list?)))


;;; `copy-custom-dialog-list-with-text-strings'

(defun copy-custom-dialog-list-with-text-strings (list)
  (loop for text in list
        collect (copy-text-string text) using custom-dialog-cons))


;;; 32bit constants - 32bit numbers are represented as a dotted pair of 16 bit
;;; high and low bits (high . low)

(defvar 32bit-constants nil)

(defmacro def-32bit-constant (constant-name 32bit-value)
  `(setf 32bit-constants
         (gensym-push (gensym-cons ',constant-name ,32bit-value)
                      32bit-constants)))

(defmacro 32bit-constant-p (constant-symbol)
  `(cdr (assoc ,constant-symbol 32bit-constants)))

(defmacro 32bit-constant-value (constant-symbol)
  `(cdr (assoc ,constant-symbol 32bit-constants)))

;; Note that many of these are duplicates of those already in windows4.lisp

;;; BEGIN:  Autogenerated section
;;; Warning:  Do not edit this section!
;;; This section is generated by winuser_constants.exe
(def-32bit-constant ws-overlapped          '(     0 .     0))
(def-32bit-constant ws-popup               '( 32768 .     0))
(def-32bit-constant ws-child               '( 16384 .     0))
(def-32bit-constant ws-minimize            '(  8192 .     0))
(def-32bit-constant ws-visible             '(  4096 .     0))
(def-32bit-constant ws-disabled            '(  2048 .     0))
(def-32bit-constant ws-clipsiblings        '(  1024 .     0))
(def-32bit-constant ws-clipchildren        '(   512 .     0))
(def-32bit-constant ws-maximize            '(   256 .     0))
(def-32bit-constant ws-caption             '(   192 .     0))
(def-32bit-constant ws-border              '(   128 .     0))
(def-32bit-constant ws-dlgframe            '(    64 .     0))
(def-32bit-constant ws-vscroll             '(    32 .     0))
(def-32bit-constant ws-hscroll             '(    16 .     0))
(def-32bit-constant ws-sysmenu             '(     8 .     0))
(def-32bit-constant ws-thickframe          '(     4 .     0))
(def-32bit-constant ws-group               '(     2 .     0))
(def-32bit-constant ws-tabstop             '(     1 .     0))
(def-32bit-constant ws-minimizebox         '(     2 .     0))
(def-32bit-constant ws-maximizebox         '(     1 .     0))
(def-32bit-constant ws-ex-mdichild         '(     0 .    64))
(def-32bit-constant ws-ex-toolwindow       '(     0 .   128))
(def-32bit-constant ws-ex-windowedge       '(     0 .   256))
(def-32bit-constant ws-ex-clientedge       '(     0 .   512))
(def-32bit-constant ws-ex-contexthelp      '(     0 .  1024))
(def-32bit-constant ws-ex-right            '(     0 .  4096))
(def-32bit-constant ws-ex-left             '(     0 .     0))
(def-32bit-constant ws-ex-rtlreading       '(     0 .  8192))
(def-32bit-constant ws-ex-ltrreading       '(     0 .     0))
(def-32bit-constant ws-ex-leftscrollbar    '(     0 . 16384))
(def-32bit-constant ws-ex-rightscrollbar   '(     0 .     0))
(def-32bit-constant ws-ex-controlparent    '(     1 .     0))
(def-32bit-constant ws-ex-staticedge       '(     2 .     0))
(def-32bit-constant ws-ex-appwindow        '(     4 .     0))
(def-32bit-constant ws-ex-overlappedwindow '(     0 .   768))
(def-32bit-constant ws-ex-pallettewindow   '(     0 .   392))
(def-32bit-constant bs-pushbutton          '(     0 .     0))
(def-32bit-constant bs-defpushbutton       '(     0 .     1))
(def-32bit-constant bs-checkbox            '(     0 .     2))
(def-32bit-constant bs-autocheckbox        '(     0 .     3))
(def-32bit-constant bs-radiobutton         '(     0 .     4))
(def-32bit-constant bs-3state              '(     0 .     5))
(def-32bit-constant bs-auto3state          '(     0 .     6))
(def-32bit-constant bs-groupbox            '(     0 .     7))
(def-32bit-constant bs-userbutton          '(     0 .     8))
(def-32bit-constant bs-autoradiobutton     '(     0 .     9))
(def-32bit-constant bs-ownerdraw           '(     0 .    11))
(def-32bit-constant bs-lefttext            '(     0 .    32))
(def-32bit-constant bs-text                '(     0 .     0))
(def-32bit-constant bs-icon                '(     0 .    64))
(def-32bit-constant bs-bitmap              '(     0 .   128))
(def-32bit-constant bs-left                '(     0 .   256))
(def-32bit-constant bs-right               '(     0 .   512))
(def-32bit-constant bs-center              '(     0 .   768))
(def-32bit-constant bs-top                 '(     0 .  1024))
(def-32bit-constant bs-bottom              '(     0 .  2048))
(def-32bit-constant bs-vcenter             '(     0 .  3072))
(def-32bit-constant bs-pushlike            '(     0 .  4096))
(def-32bit-constant bs-multiline           '(     0 .  8192))
(def-32bit-constant bs-notify              '(     0 . 16384))
(def-32bit-constant bs-flat                '(     0 . 32768))
(def-32bit-constant bs-rightbutton         '(     0 .    32))
(def-32bit-constant es-left                '(     0 .     0))
(def-32bit-constant es-center              '(     0 .     1))
(def-32bit-constant es-right               '(     0 .     2))
(def-32bit-constant es-multiline           '(     0 .     4))
(def-32bit-constant es-uppercase           '(     0 .     8))
(def-32bit-constant es-lowercase           '(     0 .    16))
(def-32bit-constant es-password            '(     0 .    32))
(def-32bit-constant es-autovscroll         '(     0 .    64))
(def-32bit-constant es-autohscroll         '(     0 .   128))
(def-32bit-constant es-nohidesel           '(     0 .   256))
(def-32bit-constant es-oemconvert          '(     0 .  1024))
(def-32bit-constant es-readonly            '(     0 .  2048))
(def-32bit-constant es-wantreturn          '(     0 .  4096))
(def-32bit-constant es-number              '(     0 .  8192))
(def-32bit-constant ss-left                '(     0 .     0))
(def-32bit-constant ss-center              '(     0 .     1))
(def-32bit-constant ss-right               '(     0 .     2))
(def-32bit-constant ss-icon                '(     0 .     3))
(def-32bit-constant ss-blackrect           '(     0 .     4))
(def-32bit-constant ss-grayrect            '(     0 .     5))
(def-32bit-constant ss-whiterect           '(     0 .     6))
(def-32bit-constant ss-blackframe          '(     0 .     7))
(def-32bit-constant ss-grayframe           '(     0 .     8))
(def-32bit-constant ss-whiteframe          '(     0 .     9))
(def-32bit-constant ss-useritem            '(     0 .    10))
(def-32bit-constant ss-simple              '(     0 .    11))
(def-32bit-constant ss-leftnowordwrap      '(     0 .    12))
(def-32bit-constant ss-ownerdraw           '(     0 .    13))
(def-32bit-constant ss-bitmap              '(     0 .    14))
(def-32bit-constant ss-enhmetafile         '(     0 .    15))
(def-32bit-constant ss-etchedhorz          '(     0 .    16))
(def-32bit-constant ss-etchedvert          '(     0 .    17))
(def-32bit-constant ss-etchedframe         '(     0 .    18))
(def-32bit-constant ss-typemask            '(     0 .    31))
(def-32bit-constant ss-noprefix            '(     0 .   128))
(def-32bit-constant ss-notify              '(     0 .   256))
(def-32bit-constant ss-centerimage         '(     0 .   512))
(def-32bit-constant ss-rightjust           '(     0 .  1024))
(def-32bit-constant ss-realsizeimage       '(     0 .  2048))
(def-32bit-constant ss-sunken              '(     0 .  4096))
(def-32bit-constant ss-endellipsis         '(     0 . 16384))
(def-32bit-constant ss-pathellipsis        '(     0 . 32768))
(def-32bit-constant ss-wordellipsis        '(     0 . 49152))
(def-32bit-constant ss-ellipsismask        '(     0 . 49152))
(def-32bit-constant pbs-smooth             '(     0 .     1))
(def-32bit-constant pbs-vertical           '(     0 .     4))
(def-32bit-constant tbs-autoticks          '(     0 .     1))
(def-32bit-constant tbs-vert               '(     0 .     2))
(def-32bit-constant tbs-horz               '(     0 .     0))
(def-32bit-constant tbs-top                '(     0 .     4))
(def-32bit-constant tbs-bottom             '(     0 .     0))
(def-32bit-constant tbs-left               '(     0 .     4))
(def-32bit-constant tbs-right              '(     0 .     0))
(def-32bit-constant tbs-both               '(     0 .     8))
(def-32bit-constant tbs-noticks            '(     0 .    16))
(def-32bit-constant tbs-enableselrange     '(     0 .    32))
(def-32bit-constant tbs-fixedlength        '(     0 .    64))
(def-32bit-constant tbs-nothumb            '(     0 .   128))
(def-32bit-constant tbs-tooltips           '(     0 .   256))
(def-32bit-constant dts-updown             '(     0 .     1))
(def-32bit-constant dts-shownone           '(     0 .     2))
(def-32bit-constant dts-shortdateformat    '(     0 .     0))
(def-32bit-constant dts-longdateformat     '(     0 .     4))
(def-32bit-constant dts-timeformat         '(     0 .     9))
(def-32bit-constant dts-appcanparse        '(     0 .    16))
(def-32bit-constant dts-rightalign         '(     0 .    32))
(def-32bit-constant uds-wrap               '(     0 .     1))
(def-32bit-constant uds-alignright         '(     0 .     4))
(def-32bit-constant uds-alignleft          '(     0 .     8))
(def-32bit-constant uds-autobuddy          '(     0 .    16))
(def-32bit-constant uds-arrowkeys          '(     0 .    32))
(def-32bit-constant uds-horz               '(     0 .    64))
(def-32bit-constant uds-nothousands        '(     0 .   128))
(def-32bit-constant uds-hottrack           '(     0 .   256))
(def-32bit-constant lbs-notify             '(     0 .     1))
(def-32bit-constant lbs-sort               '(     0 .     2))
(def-32bit-constant lbs-noredraw           '(     0 .     4))
(def-32bit-constant lbs-multiplesel        '(     0 .     8))
(def-32bit-constant lbs-ownerdrawfixed     '(     0 .    16))
(def-32bit-constant lbs-ownerdrawvariable  '(     0 .    32))
(def-32bit-constant lbs-hasstrings         '(     0 .    64))
(def-32bit-constant lbs-usetabstops        '(     0 .   128))
(def-32bit-constant lbs-nointegralheight   '(     0 .   256))
(def-32bit-constant lbs-multicolumn        '(     0 .   512))
(def-32bit-constant lbs-wantkeyboardinput  '(     0 .  1024))
(def-32bit-constant lbs-extendedsel        '(     0 .  2048))
(def-32bit-constant lbs-disablenoscroll    '(     0 .  4096))
(def-32bit-constant lbs-nodata             '(     0 .  8192))
(def-32bit-constant lbs-nosel              '(     0 . 16384))
(def-32bit-constant cbs-simple             '(     0 .     1))
(def-32bit-constant cbs-dropdown           '(     0 .     2))
(def-32bit-constant cbs-dropdownlist       '(     0 .     3))
(def-32bit-constant cbs-ownerdrawfixed     '(     0 .    16))
(def-32bit-constant cbs-ownerdrawvariable  '(     0 .    32))
(def-32bit-constant cbs-autohscroll        '(     0 .    64))
(def-32bit-constant cbs-oemconver          '(     0 .   128))
(def-32bit-constant cbs-sort               '(     0 .   256))
(def-32bit-constant cbs-hasstrings         '(     0 .   512))
(def-32bit-constant cbs-nointegralheight   '(     0 .  1024))
(def-32bit-constant cbs-disablenoscroll    '(     0 .  2048))
(def-32bit-constant cbs-uppercase          '(     0 .  8192))
(def-32bit-constant cbs-lowercase          '(     0 . 16384))
(def-32bit-constant lvs-icon               '(     0 .     0))
(def-32bit-constant lvs-report             '(     0 .     1))
(def-32bit-constant lvs-smallicon          '(     0 .     2))
(def-32bit-constant lvs-list               '(     0 .     3))
(def-32bit-constant lvs-typemask           '(     0 .     3))
(def-32bit-constant lvs-singlesel          '(     0 .     4))
(def-32bit-constant lvs-showselalways      '(     0 .     8))
(def-32bit-constant lvs-sortascending      '(     0 .    16))
(def-32bit-constant lvs-sortdescending     '(     0 .    32))
(def-32bit-constant lvs-shareimagelists    '(     0 .    64))
(def-32bit-constant lvs-nolabelwrap        '(     0 .   128))
(def-32bit-constant lvs-autoarrange        '(     0 .   256))
(def-32bit-constant lvs-editlabels         '(     0 .   512))
(def-32bit-constant lvs-ownerdata          '(     0 .  4096))
(def-32bit-constant lvs-noscroll           '(     0 .  8192))
(def-32bit-constant lvs-typestylemask      '(     0 . 64512))
(def-32bit-constant lvs-aligntop           '(     0 .     0))
(def-32bit-constant lvs-alignleft          '(     0 .  2048))
(def-32bit-constant lvs-alignmask          '(     0 .  3072))
(def-32bit-constant lvs-ownerdrawfixed     '(     0 .  1024))
(def-32bit-constant lvs-nocolumnheader     '(     0 . 16384))
(def-32bit-constant lvs-nosortheader       '(     0 . 32768))
;;; END:  Autogenerated section



;;; `type-of-dialog'

(def-grammar-category type-of-dialog ()
  modal modeless mdi-child)

(def-slot-value-writer type-of-dialog (slot-value)
  (twrite slot-value))

(define-category-evaluator-interface (type-of-dialog :access read-write)
    symbol
  ((set-form (evaluation-value))
   ;; NONE should not be allowed!!!  Fix soon.
   (if (eq evaluation-value 'none)
       nil
       evaluation-value))
  ((get-form (slot-value))
   (or slot-value 'none)))


;;; `x-position'

;; x-position and y-position are supposed to also support any positive integer!!
;; Implement that soon.  -jv, 2/1/05

(def-grammar-category x-position ()
  center
  left
  right
  desktop-center
  desktop-left
  desktop-right
  working-area-center
  working-area-left
  working-area-right
  near-desktop-left
  near-desktop-right
  near-left
  near-right
  near-working-area-left
  near-working-area-right)

(def-slot-value-writer x-position (slot-value)
  (twrite slot-value))

(define-category-evaluator-interface (x-position :access read-write)
    symbol
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       nil
       evaluation-value))
  ((get-form (slot-value))
   (or slot-value 'none)))


;;; `y-position'

(def-grammar-category y-position ()
  center
  bottom
  top
  desktop-bottom
  desktop-top
  near-bottom
  near-top
  near-desktop-bottom
  near-desktop-top
  near-working-area-bottom
  near-working-area-top
  working-area-bottom
  working-area-top)

(def-slot-value-writer y-position (slot-value)
  (twrite slot-value))

(define-category-evaluator-interface (y-position :access read-write)
    symbol
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       nil
       evaluation-value))
  ((get-form (slot-value))
   (or slot-value 'none)))



;;; `dialog-definition' class

(def-class (dialog-definition
             (item entity)
             (foundation-class dialog-definition)
             define-predicate
             (class-export-comment
               "Native dialogs"))
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame
    nil system save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-left-edge . light-gray)
                   (g2-icon-top-edge . gray)
                   (g2-icon-right-edge . gray)
                   (g2-icon-bottom-edge . extra-light-gray)
                   (icon-color . foreground))
       (variables)
       (background-layer)
       g2-icon-left-edge (filled-polygon ((0 0) (25 25) (0 50)) ((0 0) (25 25) (0 50)))
       g2-icon-top-edge (filled-polygon ((25 25) (0 0) (50 0)) ((25 25) (0 0) (50 0)))
       g2-icon-right-edge (filled-polygon ((25 25) (50 0) (50 50)) ((25 25) (50 0) (50 50)))
       g2-icon-bottom-edge (filled-polygon ((0 50) (25 25) (50 50)) ((0 50) (25 25) (50 50)))
       icon-color (outline (0 0) (0 50) (50 50) (50 0)) (lines (0 50) (50 0))
       (lines (0 0) (50 50)))))
  (dialog-title nil (type whole-string?) vector-slot system save)
  (dialog-width 100 (type integer) vector-slot system save)
  (dialog-height 100 (type integer) vector-slot system save)
  (dialog-x-position center (type x-position) vector-slot system save)
  (dialog-y-position center (type y-position) vector-slot system save)
  (dialog-type modeless (type type-of-dialog) vector-slot system save)
  (dialog-background-color nil (type color) vector-slot system save)
  (update-callback nil (type symbol) vector-slot system save)
  (dismissed-callback nil (type symbol) vector-slot system save)
  (resize-callback nil (type symbol) vector-slot system save)
  )


;;; Dialog error handling uses the dynamically scoped variable
;;; current-dialog-errors-structure in a dynamic extent to buffer
;;; dialog errors
;;;
;;; A scope to collect errors is established using the
;;; with-collect-dialog-errors macro and passing it a
;;; dialog-errors-structure
;;;
;;; Errors are buffered by calling add-dialog-error.
;;;
;;; Determining if there are any errors can be achieved by
;;; calling dialog-has-errors-p on a dialog-errors-structure
;;;
;;; Formatting an error string that contains all the errors
;;; can be done by calling format-dialog-errors.

(def-structure dialog-errors-structure
  (dialog-errors nil :reclaimer reclaim-custom-dialog-list-with-text-strings))

(def-named-dynamic-extent dialogs-error-handling
  (module controls)
  (unwind? nil))

(defvar-of-named-dynamic-extent current-dialog-errors-structure dialogs-error-handling)

(defmacro with-collect-dialog-errors (dialog-errors-structure &body forms)
  `(with-named-dynamic-extent dialogs-error-handling
       ((current-dialog-errors-structure ,dialog-errors-structure))
     (with-catch-handlers		; TODO: Abstract this stack-error catching.
	 (((:stack-error) (top-of-stack error error-msg suppress-debugging-info?)
	   (declare (ignore top-of-stack error suppress-debugging-info?))
	   (when (text-string-p error-msg) ; Paranoia
	     (add-dialog-error error-msg)
	     (reclaim-text-string error-msg))))
       ,@forms)))

(defmacro add-dialog-error (error &rest args)
  `(add-dialog-error-1 (tformat-text-string ,error ,@args)))

(defun add-dialog-error-1 (text-string)
  (setf (dialog-errors current-dialog-errors-structure)
	(nconc (dialog-errors current-dialog-errors-structure)
 	       (custom-dialog-list text-string)))
  nil)

(defmacro throw-dialog-error (error &rest args)
  `(dialogs-stack-error nil ,error ,@args))

;;; `format-dialog-errors' is used to tformat the errors in the
;;; dialog-errors-structure.  It is only intended to be called inside
;;; write-dialogs-stack-error or some other place where tformat is valid.
(defun format-dialog-errors (prefix dialog-errors-structure)
  (tformat "~A:" prefix)
  (loop for error-text in (dialog-errors dialog-errors-structure)
        do
    (tformat "~% ~A" error-text)))

(defun dialog-has-errors-p (dialog-errors-structure)
  (cond ((dialog-errors dialog-errors-structure)
         t)))


;;; `default-styles-for-dialog-control' - most styles are "off" by default.
;;; The ones in this list are "on" by default.

(defconstant default-styles-for-dialog-control
  '(ws-visible ws-child ws-tabstop))



;;; `handle-for-no-dialog'

(defconstant handle-for-no-dialog -1)


(defconstant id-for-no-component -1)
(defconstant id-for-entire-dialog -1)


(defconstant text-for-ellipsis (make-evaluation-text #w"..."))
(defconstant toggle-button-selected-token #w"True")
(defconstant toggle-button-not-selected-token #w"False")

(defconstant maximum-number-of-tab-frames 20)


;;; `tree-view-...-separator' constants

(defconstant tree-view-hierarchy-separator #.%\/ ) ;; forward slash
(defconstant tree-view-item-separator #.%\| ) ;; vertical bar

(defconstant duration-field-separator #.%\: ) ;; colon

(defconstant tab-frame-field-separator #.%\\ ) ;; backslash

(defconstant general-dialog-element-separator #.(coerce-to-wide-character 001))
(defconstant general-dialog-secondary-element-separator #.(coerce-to-wide-character 002))

(defmacro twrite-dialogs-element-separator ()
  `(twrite-char 1))

(defmacro twrite-dialogs-secondary-element-separator ()
  `(twrite-char 2))



;;; `G2 Styles' -- Gensym specific style constants; must be kept in synch with
;;; those in ext/c/dyndlg.h.  Since these get sent to Telewindows, they must
;;; not be changed after they have shipped, or else we would break compatibility
;;; between versions.

(defconstant g2-style-none 0)

;(defconstant g2-lvs-gridlines 1)
;(defconstant g2-lvs-allow-sort-rows 2)

(defconstant g2-bs-initially-selected 4)

(defconstant g2-ctv-select-only-leaves 8)

(defconstant g2-uds-integers-only 1)

(defconstant g2-dts-show-time    1)
(defconstant g2-dts-show-date    2)
(defconstant g2-dts-24-hour-time 4)

(defconstant g2-dts-us-format    #x0001)
(defconstant g2-dts-eu-format    #x0010)
(defconstant g2-dts-gov-format   #x0020)

(defconstant cbs-simple          #x0001)     ; Win32 style bits for combo boxes
(defconstant cbs-dropdown        #x0002)
(defconstant cbs-dropdownlist    #x0003)

(defconstant g2-cbs-color-picker #x10000)    ; Indicates a combo box being used as a color picker 

(defconstant g2-anchor-top    #x0010)        ; NOTE: These bit assignments agree with WinForms
(defconstant g2-anchor-bottom #x0020)        ; (shifted left 4 bits), and must not be changed.
(defconstant g2-anchor-left   #x0040)
(defconstant g2-anchor-right  #x0080)
(defconstant g2-anchor-p      #x0100)        ; Set if any anchor was specified


;; `Dialog default values'

;; Absolutely and completely arbitrary!!!  An alternate approach would be to
;; figure out the rightmost and bottommost controls on the dialog, and
;; automatically shrink-wrap it, if the user did not specify a height or width.

(defconstant default-width-for-custom-dialog 500)
(defconstant default-height-for-custom-dialog 250)


(defconstant spinner-default-current-value 50)
(defconstant spinner-default-low-value      0)
(defconstant spinner-default-high-value   100)
(defconstant spinner-default-increment      1)
(defconstant spinner-minimum-increment  .0001)



;; `Dialog Position'

;;; `dialog-symbol-to-code-map' -- must be kept in synch with GPD_ constants
;;; in ext/c/dyndlgs.h

(defconstant dialog-symbol-to-code-map
  '((center . -10000)                   ; center of the parent window
    (desktop-center . -10001)           ; center of the desktop
    (left . -10002)                     ; left edge of the parent window
    (top . -10003)                      ; top edge of the parent window
    (right . -10004)                    ; right edge of the parent window
    (bottom . -10005)                   ; bottom edge of the parent window
    (near-left . -10006)                ; near the left edge of the parent window
    (near-top . -10007)                 ; near the top edge of the parent window
    (near-right . -10008)               ; near the right edge of the parent window
    (near-bottom . -10009)              ; near the bottom edge of the parent window
    (desktop-left . -10010)             ; left edge of the desktop
    (desktop-top . -10011)              ; top edge of the desktop
    (desktop-right . -10012)            ; right edge of the desktop
    (desktop-bottom . -10013)           ; bottom edge of the desktop
    (near-desktop-left . -10014)        ; near the left edge of the desktop
    (near-desktop-top . -10015)         ; near the top edge of the desktop
    (near-desktop-right . -10016)       ; near the right edge of the desktop
    (near-desktop-bottom . -10017)      ; near the bottom edge of the desktop

    (working-area-center . -10018)      ; center of the working area
    (working-area-left . -10019)        ; left edge of the working area
    (working-area-top . -10020)         ; top edge of the working area
    (working-area-right . -10021)       ; right edge of the working area
    (working-area-bottom . -10022)      ; bottom edge of the working area
    (near-working-area-left . -10023)   ; near the left edge of the working area
    (near-working-area-top . -10024)    ; near the top edge of the working area
    (near-working-area-right . -10025)  ; near the right edge of the working area
    (near-working-area-bottom . -10026) ; near the bottom edge of the working area
    ))

;; The constants in the above a-list must be kept in synch with ext/c/dyndlgs.h.

(defconstant default-x-position-for-custom-dialog 'center)
(defconstant default-y-position-for-custom-dialog 'center)


;;; `valid-dialog-position-symbols'

(defconstant valid-dialog-position-symbols
  (loop for (symbol) in dialog-symbol-to-code-map
        collect symbol))



;;; `control-value structures'

;; "cv" == "control value" or "cell value"


;;; `list-box-cv'

;; Note, I'm considering a combo box to be a type of list-box.  Maybe there's a
;; generic term which encapsulates both.  If someone tells me what it is, I'll
;; change this to use it.  -jv, 4/28/05

(def-structure list-box-cv
  (list-box-cv-list
    '() :reclaimer reclaim-custom-dialog-list-with-text-strings)
  (list-box-cv-selected
    '() :reclaimer reclaim-custom-dialog-list-with-text-strings)
  (list-box-cv-text-selection?
    '() :reclaimer reclaim-custom-dialog-list-function)
  (list-box-cv-style? nil))		; A symbol or NIL


;;; `checkable-list-box-cv'

(def-structure (checkable-list-box-cv (:include list-box-cv))
  (checkable-list-box-cv-checked
    '() :reclaimer  reclaim-custom-dialog-list-with-text-strings))


;;; `text-box-cv'

;; should this also include position of the cursor?
(def-structure text-box-cv
  (text-box-cv-text? nil :reclaimer reclaim-if-text-string))


;;; `integer-cv'

(def-structure integer-cv
  (integer-cv-value 0))


;;; `quantity-cv'

(def-structure quantity-cv
  (quantity-cv-value 0 :reclaimer reclaim-evaluation-quantity))


;;; `spinner-cv'

(def-structure spinner-cv
  (spinner-cv-current-value spinner-default-current-value
                            :reclaimer reclaim-evaluation-quantity)
  (spinner-cv-low-value     spinner-default-low-value
                            :reclaimer reclaim-evaluation-quantity)
  (spinner-cv-high-value    spinner-default-high-value
                            :reclaimer reclaim-evaluation-quantity)
  (spinner-cv-increment     spinner-default-increment
                            :reclaimer reclaim-evaluation-quantity)
  (spinner-cv-type 'quantity)
  (spinner-cv-integral-size? nil)
  (spinner-cv-fraction-size? nil))


;;; No slot reclaimers for the next few because we are not treating them as
;;; evaluation-values.  This whole inconsistency involving evaluation-values in
;;; the dialog structures needs to be dealt with.  -dkuznick, 12/1/05

;;; `duration-cv'

(def-structure duration-cv
  (duration-cv-weeks   0)
  (duration-cv-days    0)
  (duration-cv-hours   0)
  (duration-cv-minutes 0)
  (duration-cv-seconds 0))
  
(def-structure short-duration-cv
  (short-duration-cv-hours   0)
  (short-duration-cv-minutes 0)
  (short-duration-cv-seconds 0))


;;; `calendar-cv'

(def-structure calendar-cv
  (calendar-cv-year  -1)
  (calendar-cv-month -1)
  (calendar-cv-date  -1)
  (calendar-cv-format g2-dts-us-format))


;;; `time-of-day-cv'

(def-structure time-of-day-cv
  (time-of-day-cv-year   -1)
  (time-of-day-cv-month  -1)
  (time-of-day-cv-date   -1)
  (time-of-day-cv-hour   -1)
  (time-of-day-cv-minute -1)
  (time-of-day-cv-second -1))


;;; `check-box-cv'

(def-structure check-box-cv
  (check-box-cv-label?    nil :reclaimer reclaim-if-text-string)
  (check-box-cv-checked-p nil))


;;; `push-button-cv' -- applies to the "regular" push-button as well as the
;;; toggle-button

(def-structure push-button-cv
  (push-button-cv-label?             nil :reclaimer reclaim-if-text-string)
  (push-button-cv-icon-handle?       nil)
  (push-button-cv-icon-designation?  nil :reclaimer reclaim-icon-designation)
  (push-button-cv-checked-p          nil))


;; `image-cv'

(def-structure image-cv
  (image-cv-icon nil)
  (image-cv-icon-designation nil :reclaimer reclaim-icon-designation))



;;; `dialog-component'

(defconstant unspecified-component-type -1)

(def-structure dialog-component
  (dialog-component-type unspecified-component-type)
  (dialog-component-kb-id nil)
  (dialog-component-internal-id id-for-no-component)
  (dialog-component-value? nil :reclaimer reclaim-if-text-string-function)
  (dialog-component-left? nil)
  (dialog-component-top? nil)
  (dialog-component-height? nil)
  (dialog-component-width? nil)
  (dialog-component-text-font? nil)
  (dialog-component-text-font-size? nil) ;;;'font and font-sizes initialisation' 
  (dialog-component-text-font-color? nil :reclaimer reclaim-if-text-string-function) ;;;'font color initialisation'
  (dialog-component-control-background-color? nil :reclaimer reclaim-if-text-string-function)
  ;;; This is either NIL or border-width of control
  (dialog-component-border-width? nil)
  ;;; This is either NIL or border-color of control
  (dialog-component-border-color? nil :reclaimer reclaim-if-text-string-function)
  (dialog-component-style nil :reclaimer reclaim-gensym-cons)
  (dialog-component-parent-kb-id? nil)
  (dialog-component-parent-text? nil :reclaimer reclaim-if-evaluation-value)
  (dialog-component-response-action dialog-response-unspecified)
  (dialog-component-parent-dialog nil)
  (dialog-component-parent-id id-for-entire-dialog)
  (dialog-component-evaluation-structure nil :reclaimer reclaim-if-evaluation-value)
  (dialog-component-original-value? nil :reclaimer reclaim-if-evaluation-value)
  (dialog-component-incoming-value? nil :reclaimer reclaim-if-text-string)
  (dialog-component-g2-style 0)
  (dialog-component-tabstop-index? nil)
  ;; This is either NIL, one of the xxx-cv structures, or the fixnum handle of a
  ;; native-view (only for tabular-views at the moment).
  (dialog-component-g2-representation? nil :reclaimer reclaim-if-structure)
  ;; Additional text-based style for GENSYMCID-210
  (dialog-component-additional-style? nil :reclaimer reclaim-if-text-string)
  ;; Adding dialog-component-is-default to indicate a default push-button
  (dialog-component-is-default nil))

#+development
(def-development-printer print-dialog-component (component stream)
  (when (dialog-component-p component)
    (printing-random-object (component stream)
      (format stream "DIALOG-COMPONENT ~A" (dialog-component-kb-id component)))
    component))


;;; `dynamic-dialog' def-structure

(defconstant dialog-first-component-number 16)

(def-structure dynamic-dialog
  (dynamic-dialog-handle handle-for-no-dialog)
  (dynamic-dialog-view? nil :reclaimer reclaim-native-window) ;nil ok for recl
  (dynamic-dialog-components '() :reclaimer reclaim-dynamic-dialog-components)
  (dynamic-dialog-next-component-number dialog-first-component-number)
  (dynamic-dialog-generic-callback? nil)
  (dynamic-dialog-user-data nil :reclaimer reclaim-if-evaluation-value)
  (dynamic-dialog-semaphore-parameter nil) ;needs reclaiming or dealing with
  (dynamic-dialog-semaphore-serial-number nil) ;ditto
  (dynamic-dialog-initiating-control nil)
  (dynamic-dialog-errors nil :reclaimer reclaim-dialog-errors-structure)
  (dynamic-dialog-count-components 0)
  (dynamic-dialog-dismissed-callback? nil)
  (dynamic-dialog-update-callback? nil)
  (dynamic-dialog-resize-callback? nil)
  (dynamic-dialog-default-push-button? nil))


;;; `gensym-window-of-dialog-component'

(defun gensym-window-of-dialog-component (dc)
  ;; Assuming view can't be NIL, which it shouldn't be in the contexts this is
  ;; being used in.  -dkuznick, 8/30/05
  (let ((view (dynamic-dialog-view? (dialog-component-parent-dialog dc))))
    (assert-for-development view)
    (native-window-gensym-window view)))


;;; `list-of-dynamic-dialogs'

#+development
(defun list-of-dynamic-dialogs (&optional gensym-window?)
  (loop for workstation in workstations-in-service
        as window = (window-for-workstation workstation)
        when (or (null gensym-window?)
                 (eq gensym-window? window))
          appending
          (loop for native-window in (native-windows-on-gensym-window window)
                when (and (dialog-view-p native-window)
                          (dialog-view-custom-dialog? native-window))
                  collect (dialog-view-custom-dialog? native-window))))


;;; `reclaim-dynamic-dialog-components'

(defun-void reclaim-dynamic-dialog-components (components)
  (loop for component in components
        do (reclaim-dialog-component component)
        finally (reclaim-gensym-list components)))

;;; Moved from inside close-telewindows-callback (workstation.lisp)
(defun-void reclaim-dynamic-dialogs-call-dismissed (gensym-window)
  (let ((native-window-list (native-windows-on-gensym-window gensym-window)))
    (loop for native-window in native-window-list do
          (when (dialog-view-p native-window)
            (let ((dialog (dialog-view-custom-dialog? native-window)))
              (when (dynamic-dialog-p dialog)
                (multiple-value-bind (callback? type)
                    (get-dialog-dismissed-callback dialog)
                  (when callback?
                    (call-dialog-dismissed-callback callback? type dialog 1 gensym-window)))
                (reclaim-dynamic-dialog dialog)))))))

;;; `32bit-nlogior' calculates the logical or of two 32bit numbers
;;;
;;; Note that this operation is destructive to the first argument (val1) and if
;;; expressed in C this would be the equivalent of (val1 |= val2)

(defun 32bit-nlogior (val1 val2)
  (setf (car val1)  (logiorf (car val1) (car val2)))
  (setf (cdr val1)  (logiorf (cdr val1) (cdr val2))))


;;; `add-style-to-lisp-struct'

(defun add-style-to-lisp-struct (lisp-struct style-constant)
  (let ((val1 (dialog-component-style lisp-struct))
        (val2 (32bit-constant-value style-constant)))
    (setf (car val1) (logior (car val1) (car val2)))
    (setf (cdr val1) (logior (cdr val1) (cdr val2)))))


;;; `delete-style-from-lisp-struct'

(defun delete-style-from-lisp-struct (lisp-struct style-constant)
  (let ((val1 (dialog-component-style lisp-struct))
        (val2 (32bit-constant-value style-constant)))
    (setf (car val1) (logandc2 (car val1) (car val2)))
    (setf (cdr val1) (logandc2 (cdr val1) (cdr val2)))))


;;; `test-style-in-lisp-struct' returns true of the style is on in this
;;; dialog-component structure's dialog-component-style slot.

(defun test-style-in-lisp-struct (lisp-struct style-constant)
  (let ((val1 (dialog-component-style lisp-struct))
        (val2 (32bit-constant-value style-constant)))
    (or
      (logtest (car val1) (car val2))
      (logtest (cdr val1) (cdr val2)))))


;;; `add-g2-style-to-lisp-struct'

(defun add-g2-style-to-lisp-struct (lisp-struct style-value)
  (setf (dialog-component-g2-style lisp-struct)
        (logiorf (dialog-component-g2-style lisp-struct) style-value)))


;;; `delete-g2-style-from-lisp-struct'

(defun delete-g2-style-from-lisp-struct (lisp-struct style-value)
  (setf (dialog-component-g2-style lisp-struct)
        (logandc2 (dialog-component-g2-style lisp-struct) style-value)))


;;; `create-dialog-component'

(defun create-dialog-component (evaluation-struct)
  (let ((the-struct (make-dialog-component)))
    (setf (dialog-component-style the-struct) (gensym-cons 0 0))
    (setf (dialog-component-evaluation-structure the-struct)
          (deep-copy-evaluation-value evaluation-struct))
    the-struct))


;;; `dialogs-dwarn'

#+development
(defvar print-dialog-warnings-p t)

(defmacro dialogs-dwarn (format &rest args)
  #+development `(when print-dialog-warnings-p (warn ,format ,@args))
  #-development (declare (ignore format args)))

(defmacro dialogs-warn (format &rest args)
  `(warning-message* 3 ,format ,@args))

;;; `dialogs-stack-error' exists for three reasons:
;;;  1. to avoid having to type that annoying "cached-top-of-stack" thing
;;;  2. to provide an easily greppable form so that we can find all the
;;;     myriad stack errors involving dialogs
;;;  3. to take the opportunity to clean up whatever internal data structures
;;;     might have already been allocated to the dialog
;;;
;;; If it were just (3), then we would expect the first argument to always
;;; be a dynamic-dialog structure.  But we have some errors where there is no
;;; dialog involved, or no reason to clean up the dialog yet: for example,
;;; errors that come up before we even allocate the dialog structure, or errors
;;; in trying to dynamically modify the dialog, which should definitely not
;;; cause the dialog to be reclaimed.  So, it is perfectly valid to pass nil
;;; as the first argument.  -jv, 5/21/04

(defmacro dialogs-stack-error (dialog? message &rest args)
  (avoiding-variable-capture (dialog? message &rest args)
    `(progn
       (when ,dialog?
         (reclaim-dynamic-dialog ,dialog?))
       (stack-error cached-top-of-stack ,message ,@args))))


;;; `write-dialogs-stack-error' is like dialogs-stack-error except it uses
;;; write-stack-error instead.  This is to enable cleanups to happen before the
;;; stack-error is thrown.
;; Note we are purposely not using avoiding-variable-capture here for a subtle
;; reason.  We'd like to say:
;; (avoiding-variable-capture (dialog? &rest body) ...), but there's a problem
;; with doing that in this case.  BODY is meant to be forms that do tformats,
;; and need to be wrapped inside the WRITE-STACK-ERROR.
;; avoiding-variable-capture will actually evaluate them outside the
;; write-stack-error in the interest of macro safety, and then stick the result
;; into the call to WRITE-STACK-ERROR.  That's not what we want, so we have to
;; do the hygienification by hand. -dkuznick, 2/2/05

(defmacro write-dialogs-stack-error (dialog? &body body)
  (let ((dialog-var? (gensym)))
    `(let ((,dialog-var? ,dialog?))
       (write-stack-error cached-top-of-stack
         ,@body
         (when ,dialog-var?
           (reclaim-dynamic-dialog ,dialog-var?))))))





;;;; Attributes of Dialog Components (Controls)


;;; The property `dialog-handler' stores dialog-handler functions on
;;; attribute-name symbols defined by def-dialog-component-attribute.

(def-global-property-name dialog-handler)


(defmacro dialog-attribute-is-null-error (attribute-name)
  `(add-dialog-error "Attribute ~s missing in dialog control structure."
                     ',attribute-name))

(defmacro dialog-attribute-must-be-integer-error (attribute-name)
  `(add-dialog-error "Attribute ~s in dialog control structure must be an integer."
                     ',attribute-name))


(defmacro dialog-attribute-must-be-symbol-error (attribute-name)
  `(add-dialog-error "Attribute ~s in dialog control structure must be a symbol."
                     ',attribute-name))


(defmacro dialog-attribute-must-be-text-error (attribute-name)
  `(add-dialog-error "Attribute ~s in dialog control structure must be a text."
                     ',attribute-name))


(defmacro dialog-attribute-must-be-truth-value-error (attribute-name)
  `(add-dialog-error "Attribute ~s in dialog control structure must be a truth-value."
                     ',attribute-name))


(defmacro dialog-attribute-must-be-sequence-error (attribute-name)
  `(add-dialog-error
     "Attribute ~s in dialog control structure must be a sequence."
     ',attribute-name))


(defmacro dialog-attribute-must-be-structure-error (attribute-name)
  `(add-dialog-error
     "Attribute ~s in dialog control structure must be a structure."
     ',attribute-name))


(defmacro dialog-attribute-must-be-value-error (attribute-name)
  `(add-dialog-error
     "Attribute ~s in dialog control structure must be a value."
     ',attribute-name))


(defmacro dialog-attribute-must-be-structure-containing-text-error (attribute-name)
  `(add-dialog-error
     "Attribute ~s in dialog control structure must be ~
      a structure containing a TEXT-VALUE attribute."
     ',attribute-name))


(defmacro dialog-attribute-must-be-structure-containing-tree-layout-error (attribute-name)
  `(add-dialog-error
     "Attribute ~s in dialog control structure must be ~
      a structure containing a TREE-LAYOUT attribute."
     ',attribute-name))


(defmacro dialog-attribute-must-be-int-symbol-or-false-error (attribute-name)
  `(add-dialog-error
     "Attribute ~s in dialog control structure must be ~
      either an integer, a symbol, or FALSE."
     ',attribute-name))


(defmacro dialog-attribute-must-be-integer-or-symbol-error (attribute-name)
  `(add-dialog-error
     "Attribute ~s in dialog control structure must be ~
      either an integer or a symbol"
     ',attribute-name))


;;; `def-dialog-component-attribute'

(defmacro def-dialog-component-attribute (attribute-name
                                           (new-value lisp-struct
                                                      &key (type nil)
                                                      (null-allowed-p nil))
                                           &body body)
  (let ((attribute-handler
          (intern (format nil "DIALOG-EVALUATION-STRUCTURE-~a-HANDLER"
                          attribute-name)))
        (null-error-handler
          (unless null-allowed-p
            `((unless ,new-value
                (dialog-attribute-is-null-error ,attribute-name)))))
        (control-type-checker
          ;; This should "never happen", and perhaps should be a #+development
          ;; cerror, instead of a stack-error, but for the early stages, let's
          ;; assume some highly unexpected things might happen, and try to
          ;; handle them gracefully.  -jv, 5/10/04
          `(unless (dialog-component-type lisp-struct)
             (if (dialog-component-kb-id lisp-struct)
                 (add-dialog-error "Dialog component ~s must have ~
                                       CONTROL-TYPE specified."
                                   (dialog-component-kb-id lisp-struct))
                 (add-dialog-error "All controls in the dialog specification ~
                                       must have CONTROL-TYPE specified."))))
        (error-check-protected-body
          (case type
            (integer
             `((when ,new-value
                 (cond ((not (evaluation-integer-p new-value))
                        (dialog-attribute-must-be-integer-error ,attribute-name))
                       (t ,@body)))))
            (text
             `((when ,new-value
                 (cond ((not (evaluation-text-p new-value))
                        (dialog-attribute-must-be-text-error ,attribute-name))
                       (t ,@body)))))
            (symbol
             `((when ,new-value
                 (cond ((not (evaluation-symbol-p new-value))
                        (dialog-attribute-must-be-symbol-error ,attribute-name))
                       (t ,@body)))))
            (truth-value
             `((when ,new-value
                 (cond ((not (evaluation-truth-value-p new-value))
                        (dialog-attribute-must-be-truth-value-error ,attribute-name))
                       (t ,@body)))))
            (sequence
             `((when ,new-value
                 (cond ((not (evaluation-sequence-p new-value))
                        (dialog-attribute-must-be-sequence-error ,attribute-name))
                       (t ,@body)))))
            (structure
             `((when ,new-value
                 (cond ((not (evaluation-structure-p new-value))
                        (dialog-attribute-must-be-structure-error ,attribute-name))
                       (t ,@body)))))
            (value
             `((when ,new-value
                 (cond ((not (evaluation-value-p new-value))
                        (dialog-attribute-must-be-value-error ,attribute-name))
                       (t ,@body)))))
            (integer-or-symbol-or-false
             `((when ,new-value
                 (cond ((not (or (evaluation-integer-p new-value)
                                 (evaluation-symbol-p new-value)
                                 (evaluation-truth-value-p new-value)))
                        (dialog-attribute-must-be-int-symbol-or-false-error
                          ,attribute-name))
                       (t ,@body)))))
            (integer-or-symbol
             `((when ,new-value
                 (cond ((not (or (evaluation-integer-p new-value)
                                 (evaluation-symbol-p new-value)))
                        (dialog-attribute-must-be-integer-or-symbol-error
                          ,attribute-name))
                       (t ,@body)))))
            (t
             (cond (type
                    (unless (valid-type-specification-p type)
                      (warn "Invalid type specification in ~A ~A: ~S"
                            'def-dialog-component-attribute attribute-name type))
                    `((when ,new-value
                        (let ((error-message?
                                (check-type-error-message ,new-value ',type)))
                          (cond (error-message?
                                 (add-dialog-error
                                   "Attribute ~s in dialog control structure is invalid: ~A"
                                   ',attribute-name error-message?)
                                 (reclaim-text-string error-message?))
                                (t ,@body))))))
                   (t
                    body))))))
    `(progn
       (defun ,attribute-handler (,new-value ,lisp-struct)
         ,control-type-checker
         ,@null-error-handler
         ,@error-check-protected-body)
       (setf (dialog-handler ',attribute-name) #',attribute-handler)
       ',attribute-name)))


;;; `accept-only-leaves': truth-value.

(def-dialog-component-attribute accept-only-leaves (new-value
                                                     lisp-struct
                                                     :type truth-value)
  (if (eq (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct))
          'tree-view-combo-box)
      (if (evaluation-truth-value-is-true-p new-value)
          (add-g2-style-to-lisp-struct lisp-struct g2-ctv-select-only-leaves)
          (delete-g2-style-from-lisp-struct lisp-struct g2-ctv-select-only-leaves))
      (add-dialog-error "The ACCEPT-ONLY-LEAVES attribute is only applicable to ~
                         tree-view-combo-boxes.")))


;;; `accepts-return': truth-value.  First, note that this has no effect if the
;;; IS-MULTILINE attribute is.  Otherwise, if this is true, then a return key
;;; results in a return (line break) being entered.  When false, a return key's
;;; only function is to activate the default push button, if any.  When the
;;; return key is not accepted, but multiline is enabled, a return can still be
;;; typed be entered by typing CTRL+RETURN (and also, it seems, CTRL+J or
;;; CTRL+M).  This corresponds exactly to the Windows ES_WANTRETURN flag.  Note
;;; that the accepts-return name is inspired by the very similar property on the
;;; TextBox class in .NET; the name sounds better, and that's probably why it's
;;; the new name in the newer controls API of .NET.

(def-dialog-component-attribute accepts-return (new-value
                                                 lisp-struct
                                                 :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-wantreturn)
          (delete-style-from-lisp-struct lisp-struct 'es-wantreturn))
      (add-dialog-error
        "The ACCEPTS-RETURN attribute is only applicable ~
                            to text-boxes.")))


;;; `alignment'

(def-dialog-component-attribute alignment
    (new-value lisp-struct :type symbol)
  (let* ((type-symbol
           (map-control-type-fixnum-to-symbol
             (dialog-component-type lisp-struct)))
         (requested-alignment
           (evaluation-symbol-symbol new-value)))
    (case type-symbol
      (spinner
       (case requested-alignment
         (left
          (delete-style-from-lisp-struct lisp-struct 'uds-alignright)
          (add-style-to-lisp-struct lisp-struct 'uds-alignleft))
         (right
          (delete-style-from-lisp-struct lisp-struct 'uds-alignleft)
          (add-style-to-lisp-struct lisp-struct 'uds-alignright))
         (t
          (add-dialog-error
            "The value of the ALIGNMENT attribute, ~A, is not valid. It ~
             must be one of the symbols LEFT or RIGHT."
            requested-alignment))))
      (label
       (case requested-alignment
         (left
          (add-style-to-lisp-struct lisp-struct 'ss-left))
         (center
          (add-style-to-lisp-struct lisp-struct 'ss-center))
         (right
          (add-style-to-lisp-struct lisp-struct 'ss-right))
         (t
          (add-dialog-error
            "The value of the ALIGNMENT attribute, ~A, is not valid. It ~
             must be one of the symbols LEFT, CENTER or RIGHT."
            requested-alignment))))
      (t
       (add-dialog-error
         "The ALIGNMENT attribute is only applicable to ~
          labels and spinners.")))))


;;; The dialog-component-attribute `anchor' folds into five new G2 style
;;; bits. The bits are arranged to agree with the "anchorStyles" enumeration in
;;; Winforms, so that users can specify them with a fixnum if they want, for
;;; conciseness.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant anchor-symbol-type '(member none top left bottom right
                                  top-left bottom-right top-left-bottom-right)))

(defun anchor-bit (symbol)
  (case symbol
    (top g2-anchor-top)
    (bottom g2-anchor-bottom)
    (left g2-anchor-left)
    (right g2-anchor-right)
    (top-left (logiorf g2-anchor-top g2-anchor-left))
    (bottom-right (logiorf g2-anchor-bottom g2-anchor-right))
    (top-left-bottom-right (logiorf g2-anchor-top g2-anchor-bottom g2-anchor-left g2-anchor-right))
    (t 0)))

(def-dialog-component-attribute anchor (new-value lisp-struct
                                                  :type (or integer
                                                            #.anchor-symbol-type
                                                            (sequence #.anchor-symbol-type)))
  (add-g2-style-to-lisp-struct
    lisp-struct
    (logiorf g2-anchor-p
             (cond ((fixnump new-value) (ashf (logandf new-value #xF) 4))
                   ((symbolp new-value) (anchor-bit new-value))
                   ((evaluation-sequence-p new-value)
                    (loop with result = 0
                          for symbol being each evaluation-sequence-element of new-value
                          do (setq result (logiorf (anchor-bit symbol) result))
                          finally (return result)))
                   (t 0)))))


;;; `arrow-keys':

(def-dialog-component-attribute arrow-keys
    (new-value lisp-struct :type truth-value)
  (if (eq 'spinner
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'uds-arrowkeys)
          (delete-style-from-lisp-struct lisp-struct 'uds-arrowkeys))
      (add-dialog-error
        "The ARROW-KEYS attribute is only applicable to spinners.")))


;;; `background-color' - place-marker.  For now this is only used by the tabular
;;; view

(def-dialog-component-attribute background-color
    (new-value lisp-struct :type symbol))


;;; `border': truth-value.

(def-dialog-component-attribute border (new-value
                                         lisp-struct
                                         :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-border)
      (delete-style-from-lisp-struct lisp-struct 'ws-border)))


;;; `control-id'

(def-dialog-component-attribute control-id (new-value
                                             lisp-struct
                                             :type integer-or-symbol)
  (let ((dialog (dialog-component-parent-dialog lisp-struct)))
    (loop for existing-component in (dynamic-dialog-components dialog)
          when (eql new-value (dialog-component-kb-id existing-component)) do
              (add-dialog-error "The given dialog specification uses the ~
               control-id ~NV more than once.  Each control in a dialog specification ~
               must have a unique control-id." new-value))
    (setf (dialog-component-internal-id lisp-struct)
          (dynamic-dialog-next-component-number dialog))
    (setf (dialog-component-kb-id lisp-struct) new-value)))


;;; `dialog-control-type'

(defun dialog-control-type (requested-value)
  (cond
    ((symbolp requested-value)
     (map-control-type-symbol-to-fixnum requested-value))
    (t
     nil)))


;;; `control-type' dialog-component-attribute is a special case, because we
;;; obtain the control-type at the very beginning of add-component-to-custom-
;;; dialog; we need to know the type in order to properly evaluate anything
;;; else with the control.  So, it would seem this could be a no-op, but what
;;; if someone specified control-type *twice*, with two different types, in
;;; the same control?  We can catch that error here.  For now, at least, it's
;;; also a good place to check our work and have #+development errors if it
;;; doesn't check out.  -jv, 5/8/04

(def-dialog-component-attribute control-type (new-value lisp-struct)
  (let* ((this-control-type (dialog-control-type new-value))
         (already-found-type (dialog-component-type lisp-struct)))
    (cond
      ((eql this-control-type already-found-type)
       ;; OK, they're the same.  Presumably, we are just using the attribute in
       ;; the structure which we already used; or perhaps, the user specified
       ;; the control-type twice, but specified it the same both times.  We
       ;; won't consider that an error (at least, not for now).

       ;; Do some type-specific initialization here.
       (case new-value
         (tab-frame
          (add-style-to-lisp-struct lisp-struct 'ws-clipsiblings))
         (progress-bar)
         (track-bar
          (add-style-to-lisp-struct lisp-struct 'tbs-enableselrange)
          (add-style-to-lisp-struct lisp-struct 'tbs-autoticks))
         (slider
          (add-style-to-lisp-struct lisp-struct 'tbs-enableselrange))
         (tree-view-combo-box)
         (combo-box
          (add-style-to-lisp-struct lisp-struct 'ws-vscroll))
         ((list-box checkable-list-box)
          (add-style-to-lisp-struct lisp-struct 'ws-vscroll)
          (add-style-to-lisp-struct lisp-struct 'lbs-notify))
         (color-picker
          (add-style-to-lisp-struct lisp-struct 'ws-vscroll)
          (add-style-to-lisp-struct lisp-struct 'cbs-dropdownlist))
         ((text-box masked-edit label))
         (spinner
          (add-style-to-lisp-struct lisp-struct 'uds-autobuddy)

	  ;; Other bits which used to be forced true in the C++ code, and hence
	  ;; were not overrideable by G2. Now they are.
          (add-style-to-lisp-struct lisp-struct 'uds-arrowkeys)
          (add-style-to-lisp-struct lisp-struct 'uds-nothousands)

          ;; alignment has to default to right-aligned.  It's overrideable
          ;; via the alignment attribute.  But it can't default to the spin
          ;; control's default, since that assumes there's no buddy, and we
          ;; are creating spinners, which always have a text-box buddy.
          (add-style-to-lisp-struct lisp-struct 'uds-alignright))
         ((duration workspace))
         (short-duration 
         	(add-style-to-lisp-struct lisp-struct 'dts-updown)
          (add-style-to-lisp-struct lisp-struct 'dts-timeformat))
         (calendar
          (delete-style-from-lisp-struct lisp-struct 'dts-updown))
         (time-of-day
          (add-style-to-lisp-struct lisp-struct 'dts-updown)
          (add-style-to-lisp-struct lisp-struct 'dts-timeformat)
          (add-g2-style-to-lisp-struct lisp-struct g2-dts-show-time))
         (group
          (add-style-to-lisp-struct lisp-struct 'bs-groupbox))
         (radio-button
          (add-style-to-lisp-struct lisp-struct 'bs-autoradiobutton))
         (check-box
          (add-style-to-lisp-struct lisp-struct 'bs-autocheckbox))
         (push-button)
         (toggle-button
          (add-style-to-lisp-struct lisp-struct 'bs-autocheckbox)
          (add-style-to-lisp-struct lisp-struct 'bs-pushlike))
         (tabular-view
          ;; Default styles now handled by the tabular-view itself.
	  )
         (grid-view
          ;; are there default styles we want to add here?  -jv, 3/24/05
          ))
       t)
      ((fixnump this-control-type)
       (cond
         ((or (not (fixnump already-found-type))
              (=f already-found-type unspecified-component-type))
          ;; To get here would be quite bizarre, because if the component-type
          ;; was not specified, we should have aborted the add-component
          ;; function in the first place, and never gotten here.  Seems very
          ;; bad, but if it somehow ever happened, we'd just accept it in
          ;; distribution.
          #+development
          (cerror "Continue, using new type"
                  "original type of structure ~s was unspecified; now specifying ~s"
                  lisp-struct new-value)
          (setf (dialog-component-type lisp-struct) this-control-type))
         (t
          ;; This is user error.  The user has specified control-type twice, with
          ;; two different values, in the same control.  For now, we'll ignore the
          ;; second value in distribution; the correct action would be to notify
          ;; the user of the problem, although I'm not sure if we should consider
          ;; it a fatal error or not.
          #+development
          (cerror "Continue, not changing type"
                  "conflict in types: control already had type ~s, type ~s requested"
                  (map-control-type-fixnum-to-symbol already-found-type)
                  new-value))))
      ((null this-control-type)
       ;; What can cause this case would be if the user had first specified a
       ;; valid control-type, and then specified an unrecognized one.
       #+development
       (cerror "Go ahead"
               "ignoring ~s control type; control already has type ~s"
               new-value (map-control-type-fixnum-to-symbol already-found-type)))
      (t
       ;; Nothing could possibly cause this case
       #+development
       (error "How did dialog-control-type return something not a fixnum and not nil? (~s)"
              this-control-type)))))


;;; `dropdown-height' -- just for backwards compatibility.  Use DROPPED-HEIGHT, instead.

(def-dialog-component-attribute dropdown-height
    (new-value lisp-struct :type integer)
  (unless (memq (map-control-type-fixnum-to-symbol
                  (dialog-component-type lisp-struct))
                '(tree-view-combo-box))
    new-value ;; ignore this; we'll pick it up later
    (add-dialog-error
      "The DROPDOWN-HEIGHT attribute is only applicable to tree-view-combo-boxes.")))


;;; `dropdown-width' -- just for backwards compatibility.  Use DROPPED-WIDTH, instead.

(def-dialog-component-attribute dropdown-width
    (new-value lisp-struct :type integer)
  (unless (memq (map-control-type-fixnum-to-symbol
                  (dialog-component-type lisp-struct))
                '(combo-box color-picker tree-view-combo-box))
    new-value ;; ignore this; we'll pick it up later
    (add-dialog-error
      "The DROPDOWN-WIDTH attribute is only applicable to combo-boxes.")))


;;; `dropped-height': integer

(def-dialog-component-attribute dropped-height
    (new-value lisp-struct :type integer)
  (unless (memq (map-control-type-fixnum-to-symbol
                  (dialog-component-type lisp-struct))
                '(tree-view-combo-box))
    new-value ;; ignore this; we'll pick it up later
    (add-dialog-error
      "The DROPPED-HEIGHT attribute is only applicable to tree-view-combo-boxes.")))


;;; `dropped-width': integer

(def-dialog-component-attribute dropped-width
    (new-value lisp-struct :type integer)
  (unless (memq (map-control-type-fixnum-to-symbol
                  (dialog-component-type lisp-struct))
                '(combo-box color-picker tree-view-combo-box))
    new-value ;; ignore this; we'll pick it up later
    (add-dialog-error
      "The DROPPED-WIDTH attribute is only applicable to combo-boxes.")))


;;; `extended-selection': truth-value.

(def-dialog-component-attribute extended-selection
    (new-value lisp-struct :type truth-value)
  (let ((control-type
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct))))
    (case control-type
      (tabular-view
       (if (evaluation-truth-value-is-true-p new-value)
           (delete-style-from-lisp-struct lisp-struct 'lvs-singlesel)
           (add-style-to-lisp-struct lisp-struct 'lvs-singlesel)))
      ((list-box checkable-list-box)
       (if (evaluation-truth-value-is-true-p new-value)
           (progn
             (delete-style-from-lisp-struct lisp-struct 'lbs-multiplesel)
             (add-style-to-lisp-struct lisp-struct 'lbs-extendedsel))
           (delete-style-from-lisp-struct lisp-struct 'lbs-extendedsel)))
      (t
       (add-dialog-error "The EXTENDED-SELECTION attribute is only applicable to ~
                          tabular-views, list-boxes and checkable-list-boxes.")))))


;;; `height'

(def-dialog-component-attribute height (new-value
                                         lisp-struct
                                         :type integer)
  (setf (dialog-component-height? lisp-struct) new-value))

;;; font (GENSYMCID-1190: Font feature request)

(def-dialog-component-attribute text-font (new-value
                                            lisp-struct
                                            :type text)
  (setf (dialog-component-text-font? lisp-struct) new-value))

;;; font size

(def-dialog-component-attribute text-font-size (new-value
                                                 lisp-struct
                                                 :type integer)
  (setf (dialog-component-text-font-size? lisp-struct) new-value))

;;; font color

(def-dialog-component-attribute text-font-color (new-value
                                                  lisp-struct
                                                  :type text)
  (reclaim-if-text-string (dialog-component-text-font-color? lisp-struct))
  (setf (dialog-component-text-font-color? lisp-struct)
        (copy-wide-string new-value)))

;;; control background color

(def-dialog-component-attribute control-background-color (new-value
                                                           lisp-struct
                                                           :type text)
  (reclaim-if-text-string (dialog-component-control-background-color? lisp-struct))
  (setf (dialog-component-control-background-color? lisp-struct)
        (copy-wide-string new-value)))

;;; border color

(def-dialog-component-attribute border-color (new-value
                                               lisp-struct
                                               :type text)
  (reclaim-if-text-string (dialog-component-border-color? lisp-struct))
  (setf (dialog-component-border-color? lisp-struct)
        (copy-wide-string new-value)))

;;; border width

(def-dialog-component-attribute border-width (new-value
                                               lisp-struct
                                               :type integer)
  (setf (dialog-component-border-width? lisp-struct) new-value))


;;; `horizontal-scrollbar': truth-value.

(def-dialog-component-attribute horizontal-scrollbar (new-value
                                                       lisp-struct
                                                       :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-hscroll)
      (delete-style-from-lisp-struct lisp-struct 'ws-hscroll)))


;;; `is-autohscroll': truth-value.

(def-dialog-component-attribute is-autohscroll (new-value
                                                 lisp-struct
                                                 :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-autohscroll)
          (delete-style-from-lisp-struct lisp-struct 'es-autohscroll))
      (add-dialog-error
        "The IS-AUTOHSCROLL attribute is only applicable ~
                            to text-boxes.")))


;;; `is-autovscroll': truth-value.

(def-dialog-component-attribute is-autovscroll (new-value
                                                 lisp-struct
                                                 :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-autovscroll)
          (delete-style-from-lisp-struct lisp-struct 'es-autovscroll))
      (add-dialog-error
        "The IS-AUTOVSCROLL attribute is only applicable ~
                            to text-boxes.")))


;;; `is-child': truth-value

(def-dialog-component-attribute is-child (new-value
                                           lisp-struct
                                           :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-child)
      (delete-style-from-lisp-struct lisp-struct 'ws-child)))


;;; `is-default': truth-value

(def-dialog-component-attribute is-default
    (new-value lisp-struct :type truth-value)
  (if (eq 'push-button
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (prog1
            (add-style-to-lisp-struct lisp-struct 'bs-defpushbutton)
            (setf (dialog-component-is-default lisp-struct) t))
          (delete-style-from-lisp-struct lisp-struct 'bs-defpushbutton))
      (add-dialog-error "The IS-DEFAULT attribute is only applicable to push-buttons.")))


;;; `is-disabled': truth-value

(def-dialog-component-attribute is-disabled (new-value
                                              lisp-struct
                                              :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-disabled)
      (delete-style-from-lisp-struct lisp-struct 'ws-disabled)))


;;; `is-enabled': truth-value

(def-dialog-component-attribute is-enabled (new-value
                                             lisp-struct
                                             :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (delete-style-from-lisp-struct lisp-struct 'ws-disabled)
      (add-style-to-lisp-struct lisp-struct 'ws-disabled)))


;;; `is-integer':

(def-dialog-component-attribute is-integer
    (new-value lisp-struct :type truth-value)
  (if (eq 'spinner
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-g2-style-to-lisp-struct lisp-struct g2-uds-integers-only)
          (delete-g2-style-from-lisp-struct lisp-struct g2-uds-integers-only))
      (add-dialog-error
        "The IS-INTEGER attribute is only applicable to spinners.")))


;;; `is-lowercase': truth-value.

(def-dialog-component-attribute is-lowercase (new-value
                                               lisp-struct
                                               :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-lowercase)
          (delete-style-from-lisp-struct lisp-struct 'es-lowercase))
      (add-dialog-error
        "The IS-LOWERCASE attribute is only applicable ~
                            to text-boxes.")))


;;; `is-multiline': truth-value.

(def-dialog-component-attribute is-multiline (new-value
                                               lisp-struct
                                               :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-multiline)
          (delete-style-from-lisp-struct lisp-struct 'es-multiline))
      (add-dialog-error
        "The IS-MULTILINE attribute is only applicable ~
                            to text-boxes.")))


;;; `is-password': truth-value.  Note, ES_PASSWORD is only valid only for
;;; single-line edit controls.  For 8.1a0, probably won't be able to check
;;; for that.  -jv, 1/21/05

(def-dialog-component-attribute is-password (new-value
                                              lisp-struct
                                              :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-password)
          (delete-style-from-lisp-struct lisp-struct 'es-password))
      (add-dialog-error
        "The IS-PASSWORD attribute is only applicable ~
                            to text-boxes.")))


;;; `is-readonly': truth-value.

(def-dialog-component-attribute is-readonly (new-value
                                              lisp-struct
                                              :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-readonly)
          (delete-style-from-lisp-struct lisp-struct 'es-readonly))
      (add-dialog-error
        "The IS-READONLY attribute is only applicable ~
                            to text-boxes.")))


;;; `is-smooth': truth-value.

(def-dialog-component-attribute is-smooth (new-value
                                            lisp-struct
                                            :type truth-value)
  (if (eq (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct))
          'progress-bar)
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'pbs-smooth)
          (delete-style-from-lisp-struct lisp-struct 'pbs-smooth))
      (add-dialog-error "The IS-SMOOTH attribute is only applicable to progress-bars.")))


;;; `is-uppercase': truth-value.

(def-dialog-component-attribute is-uppercase (new-value
                                               lisp-struct
                                               :type truth-value)
  (if (eq 'text-box (map-control-type-fixnum-to-symbol
                      (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'es-uppercase)
          (delete-style-from-lisp-struct lisp-struct 'es-uppercase))
      (add-dialog-error
        "The IS-UPPERCASE attribute is only applicable ~
                            to text-boxes.")))


;;; `is-vertical': truth-value.

(def-dialog-component-attribute is-vertical (new-value
                                              lisp-struct
                                              :type truth-value)
  (if (eq (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct))
          'progress-bar)
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'pbs-vertical)
          (delete-style-from-lisp-struct lisp-struct 'pbs-vertical))
      (add-dialog-error "The IS-VERTICAL attribute is only applicable to progress-bars.")))


;;; `is-visible': truth-value

(def-dialog-component-attribute is-visible (new-value
                                             lisp-struct
                                             :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-visible)
      (delete-style-from-lisp-struct lisp-struct 'ws-visible)))


;;; `left'

(def-dialog-component-attribute left (new-value
                                       lisp-struct
                                       :type integer)
  (setf (dialog-component-left? lisp-struct) new-value))


;;; `list-box-style': symbol, one of SIMPLE, DROPDOWN, or DROPDOWNLIST.

(def-dialog-component-attribute list-box-style
    (new-value lisp-struct :type symbol)
  (if (eq 'combo-box
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (let* ((symbol (evaluation-symbol-symbol new-value))
             (style? (case symbol
                       (simple 'cbs-simple)
                       (dropdown 'cbs-dropdown)
                       (dropdownlist 'cbs-dropdownlist))))
        (if style?
            (add-style-to-lisp-struct lisp-struct style?)
            (add-dialog-error
              "The value of the LIST-BOX-STYLE attribute, ~A, is not valid. It ~
               must be one of the symbols SIMPLE, DROPDOWN, or DROPDOWNLIST."
              symbol)))
      (add-dialog-error
        "The LIST-BOX-STYLE attribute is only applicable to combo-boxes.")))

;;; GENSYMCID-210: International format for native date/time controls
;;; `data-format' : text

(def-dialog-component-attribute date-format
    (new-value lisp-struct :type text)
  (let ((control-type (map-control-type-fixnum-to-symbol
                       (dialog-component-type lisp-struct))))
    (case control-type
      ((calendar time-of-day)
       (setf (dialog-component-additional-style? lisp-struct)
             (when new-value
               (copy-evaluation-text new-value))))
      (t
       (add-dialog-error "The DATE-FORMAT atribute is only applicable to ~
                         calendar and time-of-day.")))))

;;; `long-date-format':

(def-dialog-component-attribute long-date-format
    (new-value lisp-struct :type truth-value)
  (if (eq 'calendar
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (cond
        ((evaluation-truth-value-is-true-p new-value)
         (delete-style-from-lisp-struct lisp-struct 'dts-shortdateformat)
         (add-style-to-lisp-struct lisp-struct 'dts-longdateformat))
        (t
         (delete-style-from-lisp-struct lisp-struct 'dts-longdateformat)
         (add-style-to-lisp-struct lisp-struct 'dts-shortdateformat)))
      (add-dialog-error
        "The LONG-DATE-FORMAT attribute is only applicable to calendar controls.")))


;;; `multiple-selection': truth-value.

(def-dialog-component-attribute multiple-selection
    (new-value lisp-struct :type truth-value)
  (let ((control-type
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct))))
    (case control-type
      ((list-box checkable-list-box)
       (delete-style-from-lisp-struct lisp-struct 'lbs-extendedsel)
       (if (evaluation-truth-value-is-true-p new-value)
           (add-style-to-lisp-struct lisp-struct 'lbs-multiplesel)
           (delete-style-from-lisp-struct lisp-struct 'lbs-multiplesel)))
      (t
       (add-dialog-error "The MULTIPLE-SELECTION attribute is only applicable to ~
                         list-boxes and checkable-list-boxes.")))))


;;; `orientation'

(def-dialog-component-attribute orientation
    (new-value lisp-struct :type symbol)
  (let* ((type-symbol
           (map-control-type-fixnum-to-symbol
             (dialog-component-type lisp-struct)))
         (requested-orientation
           (evaluation-symbol-symbol new-value)))
    (case type-symbol
      (spinner
       (case requested-orientation
         (vertical
          (delete-style-from-lisp-struct lisp-struct 'uds-horz))
         (horizontal
          (add-style-to-lisp-struct lisp-struct 'uds-horz))
         (t
          (add-dialog-error
            "The value of the ORIENTATION attribute, ~A, is not valid. It ~
             must be one of the symbols VERTICAL or HORIZONTAL."
            requested-orientation))))
      (t
       ;; We use a case statement because orientation could be applicable to
       ;; other controls besides spinners; for this first commit, however,
       ;; that's all we have.  -jv/mhd, 5/19/04
       (add-dialog-error
         "The ORIENTATION attribute is only applicable to spinners.")))))


;;; `parent-control-id'

(def-dialog-component-attribute parent-control-id (new-value
                                                    lisp-struct
                                                    :type integer-or-symbol-or-false)
  (setf (dialog-component-parent-kb-id? lisp-struct) new-value))


;;; `parent-control-text'

(def-dialog-component-attribute parent-control-text (new-value
                                                      lisp-struct
                                                      :type text)
  (setf (dialog-component-parent-text? lisp-struct)
        (when new-value
          (copy-evaluation-text new-value))))


;;; `response-action'

(def-dialog-component-attribute response-action (new-value lisp-struct :type symbol)
  (let* ((control-type
           (map-control-type-fixnum-to-symbol
             (dialog-component-type lisp-struct)))
         (integer-code
           (case new-value
             (ignore
              dialog-response-no-action)
             ((ok accept)
              dialog-response-respond-all-and-ok)
             (cancel
              dialog-response-cancel)
             (respond
              dialog-response-just-respond)
             (respond-with-all-data
              dialog-response-respond-all)
             (ok-with-just-my-data
              dialog-response-respond-and-ok)
             (ok-without-data
              dialog-response-ok)
             (t
              ;; We do not get here unless the supplied new-value was a symbol,
              ;; so we can feel safe using ~s.  The list of acceptable symbols
              ;; is in the order shown in the G2 8.0r1 doc.  -jv, 4/7/05
              (dialogs-stack-error
                nil
                "Attribute RESPONSE-ACTION in dialog control structure must be ~
                one of the following symbols: IGNORE, OK, ACCEPT, CANCEL, ~
                RESPOND, RESPOND-WITH-ALL-DATA, OK-WITH-JUST-MY-DATA, or ~
                OK-WITHOUT-DATA.  The action ~s is not recognized."
                new-value)))))
    (when (and (response-code-says-dismiss-p integer-code)
               (neq control-type 'push-button))
      (dialogs-stack-error
        nil
        "Only dialog controls of type PUSH-BUTTON can have a RESPONSE-ACTION ~
         which dismisses a dialog.  Action ~s is not supported on controls of ~
         type ~s." new-value control-type))
    (setf (dialog-component-response-action lisp-struct) integer-code)))


;;; `show-date':

(def-dialog-component-attribute show-date
    (new-value lisp-struct :type truth-value)
  (if (eq 'time-of-day
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-g2-style-to-lisp-struct lisp-struct g2-dts-show-date)
          (delete-g2-style-from-lisp-struct lisp-struct g2-dts-show-date))
      (add-dialog-error
        "The SHOW-DATE attribute is only applicable to time-of-day controls.")))


;;; `show-time':

(def-dialog-component-attribute show-time
    (new-value lisp-struct :type truth-value)
  (if (eq 'time-of-day
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-g2-style-to-lisp-struct lisp-struct g2-dts-show-time)
          (delete-g2-style-from-lisp-struct lisp-struct g2-dts-show-time))
      (add-dialog-error
        "The SHOW-TIME attribute is only applicable to time-of-day controls.")))


;;; `single-selection': truth-value.

(def-dialog-component-attribute single-selection
    (new-value lisp-struct :type truth-value)
  (let ((control-type
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct))))
    (case control-type
      (tabular-view
       (if (evaluation-truth-value-is-true-p new-value)
           (add-style-to-lisp-struct lisp-struct 'lvs-singlesel)
           (delete-style-from-lisp-struct lisp-struct 'lvs-singlesel)))
      ((list-box checkable-list-box)
       ;; Somewhat arbitrarily, say that non-single-selection is extended
       ;; selection.  I think that's the more normal case.  -jv, 2/18/05
       (delete-style-from-lisp-struct lisp-struct 'lbs-multiplesel)
       (if (evaluation-truth-value-is-true-p new-value)
           (delete-style-from-lisp-struct lisp-struct 'lbs-extendedsel)
           (add-style-to-lisp-struct lisp-struct 'lbs-extendedsel)))
      (t
       (add-dialog-error "The SINGLE-SELECTION attribute is only applicable to ~
                          tabular-views, list-boxes and checkable-list-boxes.")))))


;;; `sort-list': truth-value.

(def-dialog-component-attribute sort-list
    (new-value lisp-struct :type truth-value)
  (let ((control-type
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct))))
    (case control-type
      (combo-box
       (if (evaluation-truth-value-is-true-p new-value)
           (add-style-to-lisp-struct lisp-struct 'cbs-sort)
           (delete-style-from-lisp-struct lisp-struct 'cbs-sort)))
      ((list-box checkable-list-box)
       (if (evaluation-truth-value-is-true-p new-value)
           (add-style-to-lisp-struct lisp-struct 'lbs-sort)
           (delete-style-from-lisp-struct lisp-struct 'lbs-sort)))
      (t
       (add-dialog-error "The SORT-LIST attribute is only applicable to ~
                          combo-boxes, list-boxes and checkable-list-boxes.")))))


;;; `starts-new-group': truth-value.  Only applies to radio buttons?

(def-dialog-component-attribute starts-new-group (new-value
                                              lisp-struct
                                              :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-group)
      (delete-style-from-lisp-struct lisp-struct 'ws-group)))


;;; `top'

(def-dialog-component-attribute top (new-value
                                      lisp-struct
                                      :type integer)
  (setf (dialog-component-top? lisp-struct) new-value))


;;; `use-24-hour-time':

(def-dialog-component-attribute use-24-hour-time
    (new-value lisp-struct :type truth-value)
  (if (eq 'time-of-day
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-g2-style-to-lisp-struct lisp-struct g2-dts-24-hour-time)
          (delete-g2-style-from-lisp-struct lisp-struct g2-dts-24-hour-time))
      (add-dialog-error
        "The USE-24-HOUR-TIME attribute is only applicable to time-of-day controls.")))


;;; `vertical-scrollbar': truth-value.

(def-dialog-component-attribute vertical-scrollbar (new-value
                                                     lisp-struct
                                                     :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-vscroll)
      (delete-style-from-lisp-struct lisp-struct 'ws-vscroll)))


;;; `width'

(def-dialog-component-attribute width (new-value
                                        lisp-struct
                                        :type integer)
  (setf (dialog-component-width? lisp-struct) new-value))


;;; `wrap': if true, the value set by pressing the spin control wraps to the
;;; lower limit after it reaches the upper limit, and vice versa.

(def-dialog-component-attribute wrap
    (new-value lisp-struct :type truth-value)
  (if (eq 'spinner
          (map-control-type-fixnum-to-symbol
            (dialog-component-type lisp-struct)))
      (if (evaluation-truth-value-is-true-p new-value)
          (add-style-to-lisp-struct lisp-struct 'uds-wrap)
          (delete-style-from-lisp-struct lisp-struct 'uds-wrap))
      (add-dialog-error
        "The WRAP attribute is only applicable to spinners.")))

;; Currently this doesn't work.  We think some coding is needed at the C/C++
;; level to support it.  It should be supported! (MHD 5/19/04)


;;; `win32-styles': evaluation-sequence of constant symbols

(def-dialog-component-attribute win32-styles (new-value
                                               lisp-struct
                                               :type sequence)
  (loop for style-constant being each evaluation-sequence-element of new-value
        do
    (when (symbolp style-constant)
      (let ((style-value (32bit-constant-value style-constant)))
        (when style-value
          (32bit-nlogior (dialog-component-style lisp-struct)
                         style-value)
          (dialog-component-style lisp-struct)
          style-constant style-value)))))




;;;; Dialog Tabstops


;;; Tabstop handling.  In G2 dynamic dialogs, practically every control is, by
;;; default, a `tabstop', i.e., a control that has input focus in a dialog by
;;; typing the TAB or SHIFT+TAB keystroke.

;;; The constant list `non-natural-tabstop-dialog-component-type-symbols'
;;; contains a list of component type symbols for controls that are exceptions
;;; to this rule.  At present only label (static text) is in this list.  Thus
;;; all other supported controls are by default tab stops.  Any control,
;;; including labels, can explicitly be made to be or not be a tabstop,
;;; overriding any default behavior.  This is done using the IS-TABSTOP dialog
;;; component attribute.

;;; When there are multiple tabstops, there is an order, from first to last,
;;; called a `tabstop order', in which each control is selected for focus when a
;;; tab (or shift+tab) is typed in.  The control that is first is initially
;;; given the focus.  When a tab is typed, the next control in the order is
;;; given the focus, and so on until the last control in the order is reached,
;;; at which point we go back to the first control in the order.  When a
;;; shift+tab is typed, we go backwards, going from first to last if the first
;;; control in the order has focus.

;;; By default the first control in the tabstop order is the first control in the
;;; sequence of controls specified that is a tabstop (see above).  The second
;;; control in this sequence is second in order, and so on.  If any control that
;;; is a tabstop specifies a tabstop-index attribute, an integer, that control
;;; is made higher in the order than any controls for which no such attribute is
;;; specified.  In choosing the order between multiple controls that all have a
;;; tabstop-index specified, the ones that are lower come first; if two are the
;;; same, then the one that appears earlier in the list comes first.

;;; For example, consider the following sequence of controls A through G,
;;; sequenced in the following order in the dynamic dialog's sequence of
;;; components, with the values for tabstop-index as shown:
;;;
;;;   A   B   C            D   E   F            G
;;;   3,  4,  <no value>,  2,  3,  <no value>,  2
;;;
;;; The resulting tabstop order in this case would be:
;;;
;;;   <D, G, A, E, B, C, F>.

(def-concept tabstop-order)


;;; The constant list `non-natural-tabstop-dialog-component-type-symbols'
;;; contains a list of component type symbols for controls that are exceptions
;;; to this rule.

(defconstant non-natural-tabstop-dialog-component-type-symbols '(label group))


;;; `tabstop-in-dialog-p'

(defun tabstop-in-dialog-p (dialog-component)
  (test-style-in-lisp-struct dialog-component 'ws-tabstop))


;;; The function `tabstop-lessp-for-dialog-component' implements a
;;; "tabstop-lessp" check for two components A and B as follows:
;;;
;;;    if both have an index, then (A's index < B's index); else
;;;    if both are tab stops, then false;
;;;    else true
;;;
;;; When used with a stable sorting routine applied to a user-ordered list of
;;; components, this implements the desired tabstop order, with these
;;; properties:
;;;
;;;    tabstop controls with lower indexes < those with higher indexes;
;;;    tabstop controls with indexes < those with no indexes;
;;;    tabstop controls < nontabstop controls; and
;;;    in case of any tie, the user-specified order is maintained

(defun tabstop-lessp-for-dialog-component (component-1 component-2)
  (let* ((component-1-tabstop-p (tabstop-in-dialog-p component-1))
         (component-2-tabstop-p (tabstop-in-dialog-p component-2))
         index-1? index-2?)
    (if (and component-1-tabstop-p component-2-tabstop-p)
        (if (and (setq index-1? (dialog-component-tabstop-index? component-1))
                 (setq index-2? (dialog-component-tabstop-index? component-2)))
            (<f index-1? index-2?)
            index-1?)
        component-1-tabstop-p)))


;;; The function `tab-order-reversed-dialog-components' gets a list of dialog
;;; components (lisp structures of type dialog-component), which is in the
;;; reverse of the original order in the user's g2 structure.  This returns the
;;; list sorted to be in the proper tab order.  The top-level conses of the
;;; original are destructively altered by this function; i.e., no conses are
;;; lost, and any pointers to the original list must be replaced with the result
;;; of calling this function, since they are made invalid by this call.

(defun tab-order-reversed-dialog-components (dialog-components)
  (setq dialog-components                ; change arg, here and below
        (nreverse-canonically dialog-components))
  (setq dialog-components
        ;; This assumes and requires sort-list to be a stable, non-consing,
        ;; efficient (n log n speed) sort, which it is.
        (sort-list dialog-components #'tabstop-lessp-for-dialog-component nil))
  dialog-components)


;;; `is-tabstop': truth-value. Note see
;;; non-natural-tabstop-dialog-component-type-symbols, and related
;;; documentation, for info on tabstop handling.

(def-dialog-component-attribute is-tabstop (new-value
                                             lisp-struct
                                             :type truth-value)
  (if (evaluation-truth-value-is-true-p new-value)
      (add-style-to-lisp-struct lisp-struct 'ws-tabstop)
      (delete-style-from-lisp-struct lisp-struct 'ws-tabstop)))


;;; `tabstop-index': integer

(def-dialog-component-attribute tabstop-index (new-value
                                                lisp-struct
                                                :type integer)
  (setf (dialog-component-tabstop-index? lisp-struct) new-value))





;;;; Control-Value

;;; Code in this section produces a string from the structure specified by the
;;; user as a dialog-control's CONTROL-VALUE.


;;; `specified-or-inherited-structure-slot' - is sort of a general thing, which
;;; maybe could go in types.lisp, rather than here.  Note that default-struct?
;;; need not be supplied (i.e., can be nil, and technically could be anything,
;;; but it's intended that it will be either a structure or nil), and that we
;;; don't evaluate default-struct? unless the slot is not specified in the
;;; specified-struct.  -jv, 10/25/05

(defun-substitution-macro specified-or-inherited-structure-slot
    (specified-struct slot-name default-struct? default-value?)
  (or (evaluation-structure-slot specified-struct slot-name)
      (and (evaluation-structure-p default-struct?)
           (evaluation-structure-slot default-struct? slot-name))
      default-value?))


;;; `make-custom-dialog-list-of-text-strings'

(defun make-custom-dialog-list-of-text-strings (sequence)
  (loop for elt being each evaluation-sequence-element of sequence
        collect (copy-text-string (evaluation-text-value elt))
          using custom-dialog-cons))


;;; `validate-dialog-control-value-sequence'

(defun validate-dialog-control-value-sequence (sequence)
  (unless (evaluation-sequence-p sequence)
    (throw-dialog-error "Not a sequence: ~NA" sequence)))


;;; `validate-dialog-control-value-structure'

(defun validate-dialog-control-value-structure (structure)
  (unless (evaluation-structure-p structure)
    (throw-dialog-error "Not a structure: ~NA" structure)))


;;; `verify-control-value-textual-value-is-a-text'

(defun-void verify-control-value-textual-value-is-a-text
    (control-value control-type attribute-name required-p)
  (let ((text? (evaluation-structure-slot control-value attribute-name nil)))
    (cond ((null text?)
           (when required-p
             (add-dialog-error
               "Attribute CONTROL-VALUE in ~a control structure must contain ~
                a ~a attribute."
               control-type
               attribute-name)))
          (t
           (unless (evaluation-text-p text?)
             (add-dialog-error
               "Attribute CONTROL-VALUE in ~a control structure~a must contain ~
                a ~a attribute that is a text."
               control-type
               (if (not required-p)
                   ", if present,"
                   "")
               attribute-name))))))


;;; `verify-control-value-textual-sequence-is-a-sequence-of-texts'

(defun-void verify-control-value-textual-sequence-is-a-sequence-of-texts
    (control-value control-type attribute-name required-p)
  (let ((sequence? (evaluation-structure-slot control-value attribute-name nil)))
    (cond ((null sequence?)
           (when required-p
             (dialogs-stack-error
               nil
               "Attribute CONTROL-VALUE in ~a control structure must contain ~
                a ~a attribute."
               control-type
               attribute-name)))
          (t
           (unless (evaluation-sequence-p sequence?)
             (dialogs-stack-error
               nil
               "Attribute CONTROL-VALUE in ~a control structure~a must contain ~
                a ~a attribute that is a sequence."
               control-type
               (if (not required-p)
                   ", if present,"
                   "")
               attribute-name))
           (let ((bad-element?
                   (loop for elt being each evaluation-sequence-element
                         of sequence?
                         unless (evaluation-text-p elt)
                           do (return elt))))
             (when bad-element?
               (dialogs-stack-error
                 nil
                 "Attribute CONTROL-VALUE in ~a control structure must be ~
                  a structure with a ~a attribute~a that is a sequence of ~
                  texts, but at least one of the elements of the sequence, ~
                  ~NA, is not a text."
                 control-type
                 attribute-name
                 (if (not required-p)
                   ", if present,"
                   "")
                 bad-element?)))))))


;;; `tab-frame-labels-not-sequence-stack-error'

(defun tab-frame-labels-not-sequence-stack-error (supposed-sequence?)
  (throw-dialog-error
     "Attribute CONTROL-VALUE in dialog control structure must be a ~
         structure, with subattribute TAB-LABELS, which must be a sequence.~A"
    (if supposed-sequence?
        (tformat-text-string "  ~NA is not a sequence." supposed-sequence?)
        "")))


;;; `tab-frame-selected-not-text-stack-error'

(defun tab-frame-selected-not-text-stack-error (selected-tab?)
  (throw-dialog-error
     "Subattribute SELECTED-TAB of attribute CONTROL-VALUE of a TAB-FRAME ~
         must be a text.  ~NA is not a text." selected-tab?))


;;; `tab-frame-label-not-text-stack-error'

(defun tab-frame-label-not-text-stack-error (label)
  (throw-dialog-error
     "Attribute CONTROL-VALUE in dialog control structure must be ~
         a structure, with subattribute TAB-LABELS, which must be a sequence ~
         of texts.  ~NA is not a text." label))


;;; `tab-frame-duplicate-labels-stack-error'

(defun tab-frame-duplicate-labels-stack-error (label)
  (throw-dialog-error
     "All members of the TAB-LABELS of the CONTROL-VALUE of a TAB-FRAME ~
         dialog control must be unique.  ~NA was found more than once."
    label))


;;; `tab-frame-selected-not-found-stack-error'

(defun tab-frame-selected-not-found-stack-error (selected-tab?)
  (throw-dialog-error
     "Subattribute SELECTED-TAB of attribute CONTROL-VALUE of a TAB-FRAME ~
         must be a text which is specified in the TAB-LABELS.  ~NA was not ~
         found." selected-tab?))


;;; `bar-dialogs-stack-error'

(defun bar-dialogs-stack-error ()
  (throw-dialog-error
         "Attribute CONTROL-VALUE in dialog control structure must be ~
          a structure, in which the value of keys CURRENT-VALUE, ~
          LOW-VALUE, HIGH-VALUE, and INCREMENT all must be integer ~
          between 0 and 65,535 if present, with LOW-VALUE <= CURRENT-VALUE <= ~
          HIGH-VALUE and INCREMENT must be less than the difference between ~
          LOW-VALUE and HIGH-VALUE."))

;;; `slider-dialogs-stack-error'

(defun slider-dialogs-stack-error ()
  (throw-dialog-error
         "Attribute CONTROL-VALUE in dialog control structure must be ~
          a structure, in which the value of keys CURRENT-VALUE, ~
          LOW-VALUE, HIGH-VALUE, and INCREMENT all must be quantity, ~
          with LOW-VALUE <= CURRENT-VALUE <= HIGH-VALUE, INCREMENT ~
          must be not less than 1e-10 and less than the difference between ~
          LOW-VALUE and HIGH-VALUE and (HIGH-VALUE - LOW-VALUE) / INCREMENT ~
          must be less than 536870911."))


;;; `selected-color-value-invalid-stack-error'

(defun selected-color-value-invalid-stack-error (value control-type valid-format-text)
  (throw-dialog-error
    "The attribute SELECTED of the CONTROL-VALUE of a ~s control must be ~a.  ~
     The given value, ~NA, is not valid."
    control-type
    valid-format-text
    value))


;;; `color-picker-colors-not-sequence-stack-error'

(defun color-picker-colors-not-sequence-stack-error (requested-colors)
  (stack-error cached-top-of-stack
    "The attribute COLORS of the CONTROL-VALUE of a COLOR-PICKER control ~
     must be a sequence, if supplied.  ~NA is not a valid specification."
    requested-colors))


;;; `color-picker-invalid-colors-stack-error' -- receives the list of ALL colors
;;; which were not valid, but just refers to either "some colors" or "a color".
;;; Maybe change to print the list of invalid colors.

(defun color-picker-invalid-colors-stack-error (list-of-invalid-colors)
  (let ((multiple-invalid-colors-p (>f (length list-of-invalid-colors) 1)))
    (write-dialogs-stack-error nil
      (tformat
        "~A specified in a COLOR-PICKER control ~A invalid.  Colors must be ~
         symbols which name built-in colors in G2.  ~L,& ~A."
        (if multiple-invalid-colors-p "Some colors" "A color")
        (if multiple-invalid-colors-p "were" "was")
        list-of-invalid-colors
        (if multiple-invalid-colors-p
            "do not name known colors"
            "does not name a known color"))
      (reclaim-slot-value-list list-of-invalid-colors))))


;;;  `dialog-image-control-value-error'

(defun dialog-image-control-value-error (attribute specifics)
  (throw-dialog-error
     "Attribute ~a of an IMAGE ~a must be a structure ~
      containing an ICON attribute, whose value must be a symbol naming a ~
      class with an icon, stock icon name, or an item which has an icon."
     attribute
     specifics))


;;; Text-box stack errors.  Still need work.  They should whip up messages
;;; to show exactly what the error was.  But, that usually leaks.  Leaving
;;; for help from dbk.  Also, wording likely could still be improved.

(defun text-box-selection-length-error ()
  (throw-dialog-error
     "The SELECTION attribute of the control-value of a TEXT-BOX dialog ~
         control must be either an integer or a sequence of two integers.  ~
         The supplied specification provided a sequence of the wrong length."))

(defun text-box-selection-sequence-not-integer-error (elt)
  (declare (ignore elt))
  (throw-dialog-error
     "The SELECTION attribute of the control-value of a TEXT-BOX dialog ~
         control must be either an integer or a sequence of two integers.  ~
         The supplied specification provided a sequence in which at least one ~
         of the elements was not an integer."))

(defun text-box-selection-error ()
  (throw-dialog-error
     "The SELECTION attribute of the control-value of a TEXT-BOX dialog ~
         control must be either an integer or a sequence of two integers.  ~
         The supplied specification specified a SELECTION which was ~
         unrecognized."))

(defun text-box-color-must-be-symbol-error (which)
  (declare (ignore which))
  (throw-dialog-error
    "The color attributes of the control-value of a TEXT-BOX dialog ~
         control must be symbols which name colors.  One of the values ~
         supplied was not a symbol."))

(defun text-box-color-must-be-gensym-color-error (which)
  (declare (ignore which))
  (throw-dialog-error
     "The color attributes of the control-value of a TEXT-BOX dialog ~
         control must be symbols which name colors.  One of the symbols ~
         supplied was not recognized as a color."))

(defun text-box-color-may-not-be-metacolor-error (which)
  (declare (ignore which))
  (throw-dialog-error
     "The color attributes of the control-value of a TEXT-BOX dialog ~
         control must be symbols which name colors.  Metacolors cannot ~
         be supported."))


;;; `masked-edit-dialogs-stack-error'

(defun masked-edit-dialogs-stack-error ()
  (throw-dialog-error
         "Attribute CONTROL-VALUE in dialog control structure must be ~
          a structure with at least one of the following attributes: ~
          MASK, LITERAL, or CURRENT-VALUE."))


;;; `spinner-value-stack-error' - we already ran these "checks" and found at
;;; least one of them to be problematic.  But we've lost that information, for
;;; the sake of code simplicity.  Do the checks again, to figure out exactly
;;; which error we need to complain about.  Note, we only complain about the
;;; "first" problem we encounter.  -jv, 9/8/06

(defun spinner-value-stack-error (current-value? low-value? high-value? increment?)
  (unless (evaluation-quantity-p current-value?)
    (throw-dialog-error
      "The CURRENT-VALUE of the CONTROL-VALUE of a SPINNER dialog control ~
           must be a quantity."))
  (unless (evaluation-quantity-p low-value?)
    (throw-dialog-error
      "The LOW-VALUE of the CONTROL-VALUE of a SPINNER dialog control ~
           must be a quantity."))
  (unless (evaluation-quantity-p high-value?)
    (throw-dialog-error
      "The HIGH-VALUE of the CONTROL-VALUE of a SPINNER dialog control ~
           must be a quantity."))
  (unless (evaluation-quantity-p increment?)
    (throw-dialog-error
      "The INCREMENT of the CONTROL-VALUE of a SPINNER dialog control ~
           must be a quantity."))
  (unless (spinner-increment-is-ok
            (evaluation-quantity-value increment?))
    ;; need to format spinner-minimum-increment here, instead of hard-coding it.
    (throw-dialog-error
      "The INCREMENT of the CONTROL-VALUE of a SPINNER dialog control ~
           must have an absolute value greater than 0.0001."))
  (unless (<= (evaluation-quantity-value low-value?)
              (evaluation-quantity-value current-value?))
    (throw-dialog-error
      "Attribute CONTROL-VALUE in dialog control structure must be ~
           a structure, in which LOW-VALUE <= CURRENT-VALUE."))
  (unless (<= (evaluation-quantity-value current-value?)
              (evaluation-quantity-value high-value?))
    (throw-dialog-error
      "Attribute CONTROL-VALUE in dialog control structure must be ~
           a structure, in which CURRENT-VALUE <= HIGH-VALUE."))
  ;; WTF?  We didn't find any specific problem above.  How did we get here?  Throw
  ;; a generic error.
  (throw-dialog-error
     "Attribute CONTROL-VALUE in dialog control structure must be ~
         a structure, in which the value of keys CURRENT-VALUE, ~
         LOW-VALUE, HIGH-VALUE, and INCREMENT all must be ~
         quantities if present, with LOW-VALUE <= CURRENT-VALUE <= HIGH-VALUE."))


;;; `spinner-format-unparsable-error'

(defun spinner-format-unparsable-error ()
  (throw-dialog-error
     "Attribute PRECISION of a SPINNER control could not be parsed."))


;;; `spinner-format-must-be-symbol-error'

(defun spinner-format-must-be-symbol-error ()
  (throw-dialog-error
     "Attribute PRECISION of a SPINNER control must be a symbol."))


;;; `duration-not-an-integer-stack-error'

(defun duration-not-an-integer-stack-error (field value)
  (throw-dialog-error
    "The attribute ~s of the CONTROL-VALUE of a DURATION control must be an ~
     integer.  The given value, ~NA, is not valid." field value))


;;; `duration-value-too-large-stack-error'

(defun duration-value-too-large-stack-error (value)
  (throw-dialog-error
    "The maximum duration of the DURATION control is one second less than ~
     1000 weeks.  The given value would require ~d weeks, and therefore ~
     is not valid." value))


;;; `dialog-workspace-control-value-error'

(defun dialog-workspace-control-value-error (specifics)
  (throw-dialog-error
     "Attribute CONTROL-VALUE of a WORKSPACE dialog control must be a structure ~
      containing either a WORKSPACE-NAME or WORKSPACE-UUID attribute; ~
      WORKSPACE-NAME must be a text or a symbol, and WORKSPACE-UUID must be a ~
      text, if present.~a" specifics))


;;; `dialog-workspace-unknown-uuid-error'

(defun dialog-workspace-unknown-uuid-error ()
  (dialog-workspace-control-value-error
    #w"  No workspace with the given WORKSPACE-UUID exists."))


;;; `dialog-workspace-unknown-name-error'

(defun dialog-workspace-unknown-name-error ()
  (dialog-workspace-control-value-error
    #w"  No workspace with the given WORKSPACE-NAME exists."))


;;; `dialog-workspace-name-not-symbol-or-text-error'

(defun dialog-workspace-name-not-symbol-or-text-error ()
  (dialog-workspace-control-value-error
    #w"  The given WORKSPACE-NAME was not a symbol or a text."))


;;; `dialog-workspace-control-value-not-structure-error'

(defun dialog-workspace-control-value-not-structure-error ()
  (dialog-workspace-control-value-error
    #w"  The given control-value was not a structure."))


;;; `bad-text-value-specification-for-push-button-error'

(defun bad-text-value-specification-for-push-button-error (spec)
  (throw-dialog-error
    "Subattribute TEXT-VALUE of the CONTROL-VALUE of a PUSH-BUTTON or ~
     TOGGLE-BUTTON dialog control must a text.  ~NA is not a valid value."
    spec))


;;; `bad-icon-specification-for-push-button-error' -- see also
;;; valid-icon-designation-or-stack-error

(defun bad-icon-specification-for-push-button-error (spec)
  (throw-dialog-error
    "Subattribute ICON of the CONTROL-VALUE of a PUSH-BUTTON or TOGGLE-BUTTON ~
     dialog control must be a valid icon designation: a stock icon name, G2 ~
     class name, or an item.  ~NA is not a valid value."
    spec))


;;; `bad-icon-name-specification-for-push-button-error'

(defun bad-icon-name-specification-for-push-button-error (spec)
  (throw-dialog-error
    "The attribute ICON-NAME in the control-value of a PUSH-BUTTON control is ~
     deprecated; please specify ICON instead.  The attribute must be a valid ~
     icon designation: a stock icon name, G2 class name, or an item.  ~NA is ~
     not a valid value."
    spec))


;;; `push-button-using-icon-name-warning'

(defun push-button-using-icon-name-warning ()
  (dialogs-warn "The attribute ICON-NAME in the control-value of a PUSH-BUTTON ~
                 control is deprecated; please specify ICON instead."))


;;; `push-button-using-both-icon-name-and-icon-warning'

(defun push-button-using-both-icon-name-and-icon-warning ()
  (dialogs-warn "The attribute ICON-NAME in the control-value of a PUSH-BUTTON ~
                 control is superseded by ICON; a single control should not ~
                 specify both.  The ICON attribute will be used, and the ~
                 ICON-NAME attribute will be ignored."))


;;; `validate-tab-labels-and-selected' - Note before we get here, we've already
;;; validated that labels-seq is a non-empty evaluation-sequnce, and that
;;; selected-tab is an evaluation text.  So we've validated the types.  Now we
;;; validate that the actual values make sense.

(defun validate-tab-labels-and-selected (labels-seq selected-tab?)
  (unless (evaluation-sequence-p labels-seq)
    (tab-frame-labels-not-sequence-stack-error labels-seq))
  (when (and selected-tab? (not (evaluation-text-p selected-tab?)))
    (tab-frame-selected-not-text-stack-error selected-tab?))
  (loop with found-selected-p = (null selected-tab?)
        with accepted-labels = '()
        for label being each evaluation-sequence-element of labels-seq
        as label-val = (evaluation-text-value label) do
    (unless (evaluation-text-p label)
      (tab-frame-label-not-text-stack-error label-val))
    (when (member label-val accepted-labels :test #'string-equalw)
      (reclaim-custom-dialog-list accepted-labels)
      (tab-frame-duplicate-labels-stack-error label-val))
    (custom-dialog-push label-val accepted-labels)
    (when (and (not found-selected-p)
               (string-equalw label-val
                              (evaluation-text-value selected-tab?)))
      (setq found-selected-p t))
        finally
          (reclaim-custom-dialog-list accepted-labels)
          (unless found-selected-p
            (tab-frame-selected-not-found-stack-error selected-tab?))))


;;; `tab-frame-extract-text-for-control-value' - this will break if any of the labels
;;; has a backslash embedded in its name.
;;; Format: Label-1\Label-2\...\Label-n\001SelectedTab\001Icon-1\Icon-2\...Icon-n\001position

(defun tab-frame-extract-text-for-control-value (value lisp-struct)
  (let ((gensym-window (gensym-window-of-dialog-component lisp-struct))
        (labels-seq (evaluation-structure-slot value 'tab-labels))
        (selected-tab? (evaluation-structure-slot value 'selected-tab))
        (icons-seq (evaluation-structure-slot value 'tab-icons))
        (position? (evaluation-structure-slot value 'tab-position)))
    (validate-tab-labels-and-selected labels-seq selected-tab?)
    ;; This string is leaked.  -jv, 5/11/04
    ;; It's now not leaked when used in the modify-control-structure.  It is
    ;; still leaked when it goes into the dialog-component
    ;; structure. {see the def-dialog-component-attribute for
    ;; control-value}. -dkuznick, 8/24/04
    (twith-output-to-text-string
      (loop for first-time-p = t then nil
            for ws being each evaluation-sequence-element of labels-seq do
        (unless first-time-p
          (twrite-char tab-frame-field-separator))
        (twrite-string ws))

      (twrite-char general-dialog-element-separator)
      (when selected-tab?
        (twrite-string (evaluation-text-value selected-tab?)))

      (when (or (evaluation-sequence-p icons-seq) position?)
        (twrite-char general-dialog-element-separator))

      (when (evaluation-sequence-p icons-seq)
        (loop for icon being each evaluation-sequence-element of icons-seq
              as icon-handle? = (and (valid-icon-designation-p icon)
                                     (send-native-icon gensym-window icon))
              as first = t then nil
              doing
          (unless first
            (twrite-char tab-frame-field-separator))
          (tformat "~d" (or icon-handle? -1))))
      (when position?
        (twrite-char general-dialog-element-separator)
        (tformat "~d" (case position?
                        (top 0)
                        (left 1)
                        (bottom 2)
                        (right 3)
                        (t 0)))))))


;;; `bar-extract-text-for-control-value'

(defun bar-extract-text-for-control-value (value)
  ;; by using default values, we allow the slots to be unspecified.
  (let* ((low-value (evaluation-structure-slot value 'low-value 0))
         (high-value (evaluation-structure-slot value 'high-value 100))
         (current-value (evaluation-structure-slot value 'current-value 50))
         (increment (evaluation-structure-slot value 'increment 1)))
    (cond
      ((and (evaluation-integer-p current-value)
            (evaluation-integer-p low-value)
            (evaluation-integer-p high-value)
            (evaluation-integer-p increment)
            (<= (evaluation-integer-value low-value)
                (evaluation-integer-value current-value)
                (evaluation-integer-value high-value))
            (<=f 0 (evaluation-integer-value low-value) 65535)
            (<=f 0 (evaluation-integer-value high-value) 65535)
            (<= (evaluation-integer-value increment)
                (-f (evaluation-integer-value high-value)
                    (evaluation-integer-value low-value))))
       ;; Note, the generated string is leaked!  -jv, 3/6/05
       ;; It's now not leaked when used in the modify-control-structure.  It is
       ;; still leaked when it goes into the dialog-component
       ;; structure. {see the def-dialog-component-attribute for
       ;; control-value}. -dkuznick, 8/24/04
       (tformat-text-string "~s|~s|~s|~s"
                            current-value low-value high-value increment))
      (t
       (bar-dialogs-stack-error)))))

;;; `slider-extract-text-for-control-value`

(defun slider-compute-current-value (eval-low-value eval-high-value eval-increment new-value)
  (let* ((low-value (evaluation-quantity-value eval-low-value))
         (high-value (evaluation-quantity-value eval-high-value))
         (increment (evaluation-quantity-value eval-increment)))
    (make-evaluation-quantity (min high-value (+ low-value (* increment new-value))))))

(defun slider-extract-text-for-control-value (value)
  (let* ((eval-low-value (evaluation-structure-slot value 'low-value 0.0))
         (eval-high-value (evaluation-structure-slot value 'high-value 100.0))
         (eval-current-value (evaluation-structure-slot value 'current-value 50.0))
         (eval-increment (evaluation-structure-slot value 'increment 1.0)))
    (cond
      ((and (evaluation-quantity-p eval-current-value)
            (evaluation-quantity-p eval-low-value)
            (evaluation-quantity-p eval-high-value)
            (evaluation-quantity-p eval-increment))
       (let* ((low-value (evaluation-quantity-value eval-low-value))
              (high-value (evaluation-quantity-value eval-high-value))
              (current-value (evaluation-quantity-value eval-current-value))
              (increment (evaluation-quantity-value eval-increment)))
         (cond
           ((and (<= 0 low-value current-value high-value)
                 (<= 1e-10 increment (- high-value low-value)))
            (let ((new-high-value (/ (- high-value low-value) increment))
                  (new-current-value (/ (- current-value low-value) increment)))
              (if (<= 0 new-current-value new-high-value 536870911)
                (tformat-text-string "~s|~s|~s|~s"
                                     (ceiling new-current-value) 0 (ceiling new-high-value) 1)
                (slider-dialogs-stack-error))))
           (t
            (slider-dialogs-stack-error)))))
      (t
       (slider-dialogs-stack-error)))))


;;; Tree view control-value validation.  These functions all raise a stack
;;; error if they encounter an invalid value.

;; TO DO: better error messages!  -dougo, 5/4/05


;;; `validate-tree-view-item-or-name' - An item-or-name is a text, a symbol, or
;;; an item.

(defun validate-tree-view-item-or-name (item-or-name)
  (unless (or (evaluation-text-p item-or-name)
              (evaluation-symbol-p item-or-name)
              (of-class-p item-or-name 'block))
    (throw-dialog-error
      "Every attribute specified as ITEM-OR-NAME in a tree-view-combo-box ~
       must be a text, symbol, or item.  The following value is not valid: ~NA"
      item-or-name)))


;;; `validate-tree-view-tree' - A tree is a structure with an ITEM-OR-NAME and
;;; an optional sequence of CHILDREN.

(defun validate-tree-view-tree (tree)
  (validate-dialog-control-value-structure tree)
  (let ((item-or-name
          (evaluation-structure-slot tree 'item-or-name))
        (children
          (evaluation-structure-slot tree 'children)))
    (validate-tree-view-item-or-name item-or-name)
    (when children
      (validate-tree-view-forest children))))


;;; `validate-tree-view-forest' - A forest is a sequence of trees.
;; Consider allowing a single tree.  -dougo, 5/4/05

(defun validate-tree-view-forest (tree-layout)
  (validate-dialog-control-value-sequence tree-layout)
  (loop for tree being each evaluation-sequence-element of tree-layout
        do (validate-tree-view-tree tree)))


;;; `validate-tree-view-node-pattern' - A node pattern is any structure.
;; Should ITEM-OR-NAME be required?  -dougo, 5/4/05

(defun validate-tree-view-node-pattern (node-pattern)
  (validate-dialog-control-value-structure node-pattern))


;; `label-for-item-or-name'

(defun label-for-item-or-name (item-or-name)
  (cond
    ((evaluation-text-p item-or-name)
     (copy-text-string (evaluation-text-value item-or-name)))
    ((evaluation-symbol-p item-or-name)
     (twith-output-to-text-string
       (twrite-symbol
         (evaluation-symbol-symbol item-or-name))))
    ((of-class-p item-or-name 'block)
     (twith-output-to-text-string
       (twrite ;; is this guaranteed to be a symbol?
         (get-or-make-up-designation-for-block item-or-name))))))


;;; `write-rest-of-tree-view-value'

(defun write-rest-of-tree-view-value (parent-pathname rest-of-structure)
  (let* ((item-or-name (evaluation-structure-slot rest-of-structure 'item-or-name))
         (item-string (label-for-item-or-name item-or-name))
         (new-parent
           (twith-output-to-text-string
             (when (and parent-pathname
                        (wide-string-p parent-pathname)
                        (>f (text-string-length parent-pathname) 0))
               (twrite-string parent-pathname)
               (twrite-char tree-view-hierarchy-separator))
             (twrite-string item-string))))
    (twrite-string new-parent)
    (twrite-char tree-view-item-separator)
    (let ((children? (evaluation-structure-slot rest-of-structure 'children)))
      (when children?
        (loop for child being each evaluation-sequence-element of children? do
          (write-rest-of-tree-view-value new-parent child))))
    (reclaim-wide-string new-parent)
    (reclaim-wide-string item-string)))


;;; `tree-node-matches-node-pattern-p' returns true iff all of the slots of the
;;; node-pattern are present in the node and their values are all eql.

(defun tree-node-matches-node-pattern-p (node node-pattern)
  (loop for (slot . val1) being each evaluation-structure-pair of node-pattern
        for val2 = (evaluation-structure-slot node slot)
        always (evaluation-value-eql val1 val2)))


;;; `path-to-node-in-tree' returns a gensym-list of the ancestor nodes of
;;; a node in a tree matching a node pattern, or nil if no nodes match.  The
;;; node pattern is an evaluation structure with one or more slots, each of
;;; which must be present in the target node having the same (eql) value.  The
;;; tree is an evaluation sequence of nodes, where each node is an evaluation
;;; structure whose CHILDREN slot is a tree or nil.  Each node in the returned
;;; list is a child of the previous node, and the final node in the list is the
;;; node in the tree that matches the node pattern.

(defun path-to-node-in-tree (node-pattern tree)
  (loop for node being each evaluation-sequence-element of tree
        when (tree-node-matches-node-pattern-p node node-pattern)
          return (gensym-list node)
        for subtree = (evaluation-structure-slot node 'children)
        for path = (and subtree (path-to-node-in-tree node-pattern subtree))
        when path return (gensym-cons node path)))


;;; `path-string-to-node-in-tree' returns a text-string containing the
;;; ITEM-OR-NAME slots of the ancestor nodes of a node in a tree matching a
;;; node pattern, separated by a separator wide-character, or nil if no nodes
;;; match.

(defun path-string-to-node-in-tree (node-pattern tree separator)
  (let ((path (path-to-node-in-tree node-pattern tree)))
    (when path
      (twith-output-to-text-string
        (loop for node in path
              for item-or-name = (evaluation-structure-slot node 'item-or-name)
              for label = (label-for-item-or-name item-or-name)
              for sep = nil then separator
              when sep do (twrite-char sep)
              do (twrite-string label)
                 (reclaim-text-string label))
        (reclaim-gensym-list path)))))


;;; `node-with-label-in-sequence' returns the node in a sequence whose
;;; ITEM-OR-NAME slot has a given label, or nil if there is no such node.

(defun node-with-label-in-sequence (target-label sequence)
  (loop for node being each evaluation-sequence-element of sequence
        for item-or-name = (evaluation-structure-slot node 'item-or-name)
        for label = (label-for-item-or-name item-or-name)
        for match-p = (string=w label target-label)
        do (reclaim-text-string label)
        when match-p return node))


;;; `follow-path-string-to-node-in-tree' returns the node in a tree that can be
;;; reached by following a path string with the given separator wide-character,
;;; or nil if there is no such node.  This is essentially the inverse of
;;; `path-string-to-node-in-tree'.

(defun follow-path-string-to-node-in-tree (path-string tree separator)
  (loop for subtree = tree then (evaluation-structure-slot node 'children)
        for start = 0 then (1+f sep-pos?)
        for sep-pos? = (position-in-text-string-tail
                        separator path-string start)
        for label = (text-string-substring path-string start sep-pos?)
        for node = (node-with-label-in-sequence label subtree)
        do (reclaim-text-string label)
        unless sep-pos? return node
        while node))


;;; `tree-view-extract-text-for-control-value'

(defun tree-view-extract-text-for-control-value (value)
  (let ((tree-layout
          (evaluation-structure-slot value 'tree-layout))
        (initially-selected
          (evaluation-structure-slot value 'selected)))
    (cond
      ((evaluation-sequence-p tree-layout)
       (validate-tree-view-forest tree-layout)
       (when initially-selected
         (validate-tree-view-node-pattern initially-selected))
       (twith-output-to-text-string
         (let ((initially-selected-as-string
                 (or (when initially-selected
                       (path-string-to-node-in-tree
                         initially-selected tree-layout
                         tree-view-hierarchy-separator))
                     ;; Use the label of the first root node if the initially
                     ;; selected node is not provided or does not exist.
                     (unless (evaluation-sequence-empty-p tree-layout)
                       (label-for-item-or-name
                         (evaluation-structure-slot
                           (evaluation-sequence-aref tree-layout 0)
                           'item-or-name))))))
           (when initially-selected-as-string
             (twrite-string initially-selected-as-string)
             (reclaim-text-string initially-selected-as-string)
             (twrite-char tree-view-item-separator)))
         (loop for child being each evaluation-sequence-element of tree-layout
               do (write-rest-of-tree-view-value #w"" child))))
      (t
       (dialog-attribute-must-be-structure-containing-tree-layout-error control-value)
       nil))))


;;; `replace-list-box-cv-list'

(defun-void replace-list-box-cv-list (lisp-list-box new-value)
  (reclaim-custom-dialog-list-with-text-strings
    (list-box-cv-list lisp-list-box))
  (setf (list-box-cv-list lisp-list-box) new-value))


;;; `replace-list-box-cv-selected'

(defun-void replace-list-box-cv-selected (lisp-list-box new-value)
  (reclaim-custom-dialog-list-with-text-strings
    (list-box-cv-selected lisp-list-box))
  (setf (list-box-cv-selected lisp-list-box) new-value))


;;; `replace-list-box-cv-text-selection'

(defun-void replace-list-box-cv-text-selection (lisp-list-box new-value)
  (reclaim-custom-dialog-list (list-box-cv-text-selection? lisp-list-box))
  (multiple-value-bind (selection-begin? selection-end?)
      (parse-text-box-selection new-value)
    (setf (list-box-cv-text-selection? lisp-list-box)
          (custom-dialog-list selection-begin? selection-end?))))


;;; `replace-checkable-list-box-cv-checked'

(defun-void replace-checkable-list-box-cv-checked (lisp-checkable-list-box new-value)
  (reclaim-custom-dialog-list-with-text-strings
    (checkable-list-box-cv-checked lisp-checkable-list-box))
  (setf (checkable-list-box-cv-checked lisp-checkable-list-box) new-value))


;;; `ensure-list-box-control-value-structure'

(defun ensure-list-box-control-value-structure
    (dialog-component &optional (type 'list-box))
  (or (dialog-component-g2-representation? dialog-component)
      (setf (dialog-component-g2-representation? dialog-component)
            (if (eq type 'checkable-list-box)
                (make-checkable-list-box-cv)
                (make-list-box-cv)))))


;;; `build-list-box-text-sequence-data'

(defun build-list-box-text-sequence-data
    (lisp-struct control-value lisp-list-box action not-combox? &optional (type 'list-box))
  (let* ((gensym-window (gensym-window-of-dialog-component lisp-struct))
         (supports-update-color? (remote-side-supports-update-color-in-list-box-p
                                   (icp-socket-for-gensym-window? gensym-window)))
         (background-color? (evaluation-structure-slot control-value 'control-background-color))
         (font-color? (evaluation-structure-slot control-value 'text-font-color))
         (text-sequence (evaluation-structure-slot control-value 'text-sequence))
         (text-selection? (evaluation-structure-slot control-value 'text-selection))
         (list-of-strings
           (make-custom-dialog-list-of-text-strings text-sequence)))
    (case action
      (add
       (setf (list-box-cv-list lisp-list-box)
             (nconc (list-box-cv-list lisp-list-box) list-of-strings))
       ;; Note that the format when doing an add is identical to that when doing
       ;; a replace.  In fact, TWNG probably runs the exact same code to parse
       ;; and handle the list; the only difference is that in the case of a
       ;; replace, TWNG will first empty out the box before adding the new
       ;; entries.  But there's another difference, apparently by design, though
       ;; I'm not sure we have a great reason for it: when doing an ADD, we do
       ;; not allow the user to specify/change either the SELECTED or (in the
       ;; case of a checkable-list-box) the CHECKED entries.  So instead of
       ;; looking at those values in the control-value, we just write the
       ;; separator character.  This code could surely be improved. -jv, 5/9/07
       (twith-output-to-text-string
         (when (eq type 'checkable-list-box)
           ;; the "list" -- always empty -- of items to be checked
           (twrite-dialogs-secondary-element-separator))
         ;; the "list" -- always empty -- of items to be selected
         (twrite-dialogs-secondary-element-separator)
         (loop for element in list-of-strings
               do
           (twrite-string element)
           (twrite-dialogs-element-separator))
         (twrite-dialogs-secondary-element-separator)))
      (t
       #+development
       (unless (eq 'replace action)
         (cerror "Do a replace"
                 "Unrecognized action for build-list-box-text-sequence-data: ~s"
                 action))
       (when (and not-combox? (eq type 'list-box) supports-update-color?)
         (when background-color?
           (funcall (dialog-handler 'control-background-color) background-color? lisp-struct))
         (when font-color?
           (funcall (dialog-handler 'text-font-color) font-color? lisp-struct)))
       (replace-list-box-cv-list lisp-list-box list-of-strings)
       (replace-list-box-cv-text-selection lisp-list-box text-selection?)
       (twith-output-to-text-string
         (when (eq type 'checkable-list-box)
           (let ((text-list? (checkable-list-box-cv-checked lisp-list-box)))
             (when text-list?
               (loop for element in text-list?
                     do
                 (twrite-string element)
                 (twrite-dialogs-element-separator))))
           (twrite-dialogs-secondary-element-separator))
         (loop for element in (list-box-cv-selected lisp-list-box)
               do
           (twrite-string element)
           (twrite-dialogs-element-separator))
         (twrite-dialogs-secondary-element-separator)
         (loop for element in (list-box-cv-list lisp-list-box)
               do
           (twrite-string element)
           (twrite-dialogs-element-separator))
         (when (and not-combox? (eq type 'list-box) supports-update-color?)
           (twrite-dialogs-secondary-element-separator)
           (when (dialog-component-control-background-color? lisp-struct)
             (twrite-string (dialog-component-control-background-color? lisp-struct)))
           (twrite-dialogs-element-separator)
           (when (dialog-component-text-font-color? lisp-struct)
              (twrite-string (dialog-component-text-font-color? lisp-struct))))
         (let ((text-selection? (list-box-cv-text-selection? lisp-list-box)))
           (twrite-character general-dialog-secondary-element-separator)
           (when (and text-selection?
                      (fixnump (car text-selection?))
                      (fixnump (cadr text-selection?)))
             (twrite-fixnum (car text-selection?))
             (twrite-character general-dialog-element-separator)
             (twrite-fixnum (cadr text-selection?)))))))))


;;; `combo-box-extract-text-for-control-value' - the difference between this function
;;; and list-box-extract-text-for-control-value is that for a list-box, the SELECTED
;;; attribute must be a sequence, whereas for a combo-box, it must be a text.
;;; The TEXT-SEQUENCE attribute is handled in exactly the same way.

(defun combo-box-extract-text-for-control-value (value dialog-component action)
  (verify-control-value-textual-sequence-is-a-sequence-of-texts
    value 'combo-box 'text-sequence t)
  (verify-control-value-textual-value-is-a-text
    value 'combo-box 'selected nil)
  (let* ((lisp-list-box (ensure-list-box-control-value-structure dialog-component))
         (selected? (evaluation-structure-slot value 'selected))
;         (foreground-color? (evaluation-structure-slot
;                              value 'text-color))
;         (background-color? (evaluation-structure-slot
;                              value 'background-color))
         (text-selection? (evaluation-structure-slot
                            value 'text-selection)))

    (replace-list-box-cv-selected lisp-list-box
                                  (if (evaluation-text-p selected?)
                                      (custom-dialog-list
                                        (copy-text-string
                                          (evaluation-text-value selected?)))
                                      nil))
    (replace-list-box-cv-text-selection lisp-list-box text-selection?)

    (build-list-box-text-sequence-data dialog-component value lisp-list-box action nil)))


;;; `list-box-extract-text-for-control-value'

(defun list-box-extract-text-for-control-value (value dialog-component action
                                                &optional (type 'list-box))
  (verify-control-value-textual-sequence-is-a-sequence-of-texts
    value 'list-box 'text-sequence t)
  (verify-control-value-textual-sequence-is-a-sequence-of-texts
    value 'list-box 'selected nil)
  (when (eq type 'checkable-list-box)
    (verify-control-value-textual-sequence-is-a-sequence-of-texts
      value type 'checked nil))
  (let ((lisp-list-box (ensure-list-box-control-value-structure dialog-component type))
        (selected? (evaluation-structure-slot value 'selected))
        (checked? (and (eq type 'checkable-list-box)
                       (evaluation-structure-slot value 'checked))))
    (when selected?
      (replace-list-box-cv-selected lisp-list-box
                                    (make-custom-dialog-list-of-text-strings
                                      selected?)))
    (when checked?
      (replace-checkable-list-box-cv-checked
        lisp-list-box (make-custom-dialog-list-of-text-strings checked?)))

    (build-list-box-text-sequence-data dialog-component value lisp-list-box action t type)))


;;; `list-of-invalid-colors'

(defun list-of-invalid-colors (requested-colors)
  (loop for sym being each evaluation-sequence-element of requested-colors
        unless (and (symbolp sym)
                    ;; we don't want to allow RGB colors here, so we don't use
                    ;; gensym-color-p.  -jv, 12/2/05
                    (or (color-value-vector-index-and-intensity sym)
                        (gensym-metacolor-p sym)))
          collect sym using slot-value-cons))


;;; `determine-list-of-colors-for-color-picker'

(defun determine-list-of-colors-for-color-picker (requested-colors?)
  (cond
    (requested-colors?
     (unless (evaluation-sequence-p requested-colors?)
       (color-picker-colors-not-sequence-stack-error requested-colors?))
     (let ((invalid-colors? (list-of-invalid-colors requested-colors?)))
       (if invalid-colors?
           (color-picker-invalid-colors-stack-error invalid-colors?)
           (loop for sym being each evaluation-sequence-element of requested-colors?
                 collect sym using slot-value-cons))))
    (t
     (uncolumnified-list-of-colors-for-level 2))))


;;; `copy-color-symbol-name'

(defun copy-color-symbol-name (color-symbol)
  (copy-symbol-name color-symbol nil t))


;;; `color-picker-extract-text-for-control-value'

(defun color-picker-extract-text-for-control-value (value)
  (let* ((requested-colors? (evaluation-structure-slot value 'colors))
         (selected-color?
           (evaluation-structure-slot value 'selected))
         (list-of-colors (determine-list-of-colors-for-color-picker
			   requested-colors?)))
    (cond ((and selected-color? (not (symbolp selected-color?)))
	   (reclaim-slot-value-list list-of-colors)
	   (selected-color-value-invalid-stack-error ; Not actually a stack-error
	     selected-color? 'color-picker #w"a symbol")
	   nil)
	  ((and selected-color? (not (memq selected-color? list-of-colors)))
	   (reclaim-slot-value-list list-of-colors)
	   (selected-color-value-invalid-stack-error ; Not actually a stack-error
	     selected-color? 'color-picker #w"a member of the list of colors")
	   nil)
	  (t
	   (prog1
	       (twith-output-to-text-string
		 (when selected-color?
		   (let ((color-name (copy-color-symbol-name selected-color?)))
		     (twrite-string color-name)
		     (reclaim-wide-string color-name)))
		 (loop for color in list-of-colors
		       as color-name = (copy-color-symbol-name color)
		       do
		   (twrite-dialogs-element-separator)
		   (twrite-string color-name)
		   (reclaim-wide-string color-name)))
	     (reclaim-slot-value-list list-of-colors))))))



;;; `full-color-picker-extract-text-for-control-value'

(defun full-color-picker-extract-text-for-control-value (value)
  (let* ((requested-colors? (evaluation-structure-slot value 'colors))
         (selected-color? (evaluation-structure-slot value 'selected))
         (list-of-colors (determine-list-of-colors-for-color-picker
                          requested-colors?)))
    (if selected-color?
        ;; Maybe the following should be abstracted in the rgb-color facility
        ;; to lose the RGB off the front -dkuznick, 9/21/05 
        ;;suzsoft change it for Gensym-2060,   11/12/09 
        ;;if the selected-color is a name of color, we will change it to form 'GRBrrggbb' first     
        (cond ((memq selected-color? list-of-colors) 
               (reclaim-slot-value-list list-of-colors)
               ;; Strip off the leading "RGB"
               (text-string-substring (symbol-name (rgb-symbol-from-color selected-color?)) 3 nil))
              ((rgb-color-p selected-color?)
               (reclaim-slot-value-list list-of-colors)
                ;; Strip off the leading "RGB"
               (text-string-substring (symbol-name selected-color?) 3 nil))
             (t 
               (reclaim-slot-value-list list-of-colors)
               (selected-color-value-invalid-stack-error
                  selected-color?
                  'full-color-picker
                  #w"an RGB symbol of the form RGBrrggbb.")))
        ;;Suzsoft
        (copy-text-string #w""))))

;;suzsoft add the function for Gensym-2060, 11/12/09
;;; The `rgb-symbol-from-color' takes the color name as an argument , 
;;; returns a symbol of the form RGBrrggbb,
;;; a valid color name, where rr, gg, bb, are the 8-bit hex
;;; values for red, green, and blue.

;;; Examples:
;;; blue:  rgb-symbol-from-color(blue) = RGB0000FF
;;; brown:  rgb-symbol-from-color(brown) = RGBA52A2A
(defun rgb-symbol-from-color (color)
  (multiple-value-bind (red? green? blue?)
    (rgb-from-color color)
  (let ((red-value-value (evaluation-integer-value red?))
	(green-value-value (evaluation-integer-value green?))
	(blue-value-value (evaluation-integer-value blue?))
	hex-char-list)    

    (multiple-value-bind (hex-char-1 hex-char-2)
	(hex-color-values blue-value-value)
      (setq hex-char-list
	    (gensym-cons hex-char-1
			 (gensym-cons hex-char-2
				      hex-char-list))))
    (multiple-value-bind (hex-char-1 hex-char-2)
	(hex-color-values green-value-value)
      (setq hex-char-list
	    (gensym-cons hex-char-1
			 (gensym-cons hex-char-2
				      hex-char-list))))
    (multiple-value-bind (hex-char-1 hex-char-2)
	(hex-color-values red-value-value)
      (setq hex-char-list
	    (gensym-cons hex-char-1
			 (gensym-cons hex-char-2
				      hex-char-list))))    
    (prog1 
	(intern-text-string
	  (apply #'tformat-text-string "RGB~c~c~c~c~c~c"
		 hex-char-list))
      (reclaim-gensym-list hex-char-list)))))
;;suzsoft

;;; `parse-text-box-selection'

(defun parse-text-box-selection (selection?)
  (cond
    ((evaluation-sequence-p selection?)
     (cond
       ((/=f 2 (evaluation-sequence-length selection?))
        (text-box-selection-length-error))
       ((not (evaluation-integer-p (evaluation-sequence-aref selection? 0)))
        (text-box-selection-sequence-not-integer-error 0))
       ((not (evaluation-integer-p (evaluation-sequence-aref selection? 1)))
        (text-box-selection-sequence-not-integer-error 1))
       (t
        (values
          (evaluation-integer-value (evaluation-sequence-aref selection? 0))
          (evaluation-integer-value (evaluation-sequence-aref selection? 1))))))
    ((evaluation-integer-p selection?)
     (values (evaluation-integer-value selection?)
             (evaluation-integer-value selection?)))
    ((null selection?)
     (values nil nil))
    (t
     (text-box-selection-error))))


;;; `create-string-for-text-box-control-value'

(defun create-string-for-text-box-control-value (the-text?
                                                  selection-begin? selection-end?
                                                  foreground-color? background-color?)
  (multiple-value-bind (fg-r fg-g fg-b)
      (rgb-from-color foreground-color?)
    (multiple-value-bind (bg-r bg-g bg-b)
        (rgb-from-color background-color?)
      (twith-output-to-wide-string
        (when (wide-string-p the-text?)
          (twrite-string the-text?)
          (reclaim-wide-string the-text?))

        (twrite-character general-dialog-element-separator)
        (when (fixnump selection-begin?)
          (twrite-fixnum selection-begin?))
        (twrite-character general-dialog-secondary-element-separator)
        (when (fixnump selection-begin?)
          (twrite-fixnum selection-end?))

        (twrite-character general-dialog-element-separator)
        (when foreground-color?
          (twrite-rgb-as-padded-hex fg-r fg-g fg-b))

        (twrite-character general-dialog-element-separator)
        (when background-color?
          (twrite-rgb-as-padded-hex bg-r bg-g bg-b))))))


;;; `text-box-extract-text-for-control-value'

(defun text-box-extract-text-for-control-value (lisp-struct control-value)
  (declare (ignore lisp-struct))
  (let* ((the-text
           (generic-extract-text-for-control-value control-value))
         (selection? (evaluation-structure-slot
                       control-value 'selection))
         (foreground-color? (evaluation-structure-slot
                              control-value 'text-color))
         (background-color? (evaluation-structure-slot
                              control-value 'background-color)))

    (cond
      ((not (symbolp foreground-color?))
       (reclaim-wide-string the-text)
       (text-box-color-must-be-symbol-error 'foreground))
      ((not (symbolp background-color?))
       (reclaim-wide-string the-text)
       (text-box-color-must-be-symbol-error 'background))
      ((and foreground-color? (not (gensym-color-p foreground-color?)))
       (reclaim-wide-string the-text)
       (text-box-color-must-be-gensym-color-error 'foreground))
      ((and background-color? (not (gensym-color-p background-color?)))
       (reclaim-wide-string the-text)
       (text-box-color-must-be-gensym-color-error 'background))
      ((gensym-metacolor-p foreground-color?)
       (reclaim-wide-string the-text)
       (text-box-color-may-not-be-metacolor-error 'foreground))
      ((gensym-metacolor-p background-color?)
       (reclaim-wide-string the-text)
       (text-box-color-may-not-be-metacolor-error 'background))

      (t
       (multiple-value-bind (selection-begin? selection-end?)
           (parse-text-box-selection selection?)
         (create-string-for-text-box-control-value
           the-text selection-begin? selection-end?
           foreground-color? background-color?))))))


;;; `masked-edit-extract-text-for-control-value'

(defun masked-edit-extract-text-for-control-value (value)
  (macrolet ((length* (thing)
	       `(if (text-string-p ,thing) (lengthw ,thing) 0)))
    ;; We allow the slots to be unspecified.
    (let* ((mask-value (evaluation-structure-slot value 'mask nil))
	   (mask-length (length* mask-value))
	   (literal-value (evaluation-structure-slot value 'literal nil))
	   (literal-length (length* literal-value))
	   (current-value (evaluation-structure-slot value 'current-value nil))
	   (current-length (length* current-value))
	   (selection? (evaluation-structure-slot value 'selection nil))
	   (foreground-color? (evaluation-structure-slot
				value 'text-color))
	   (background-color? (evaluation-structure-slot
				value 'background-color))
	   (string-for-masks nil)
	   (length-to-use (maxf 0 mask-length literal-length current-length)))
      (cond
	((and (>f length-to-use 0)
 	      (or (null mask-value) (text-string-p mask-value))
 	      (or (null literal-value) (text-string-p literal-value))
 	      (or (null current-value) (text-string-p current-value)))
	 (setq string-for-masks
	       (twith-output-to-text-string
		 (if mask-value (twrite-string mask-value))
		 (loop for i from mask-length below length-to-use
		       with filler-char = (if mask-value
					      (charw mask-value (1-f mask-length))
					      #.%\> )
		       do
		   (twrite-char filler-char))
		 (twrite-char #.%\| )
		 (if literal-value (twrite-string literal-value))
		 (loop for i from literal-length below length-to-use
		       with filler-char = (if literal-value
					      (charw literal-value (1-f literal-length))
					      #.%\_ )
		       do
		   (twrite-char filler-char))
		 (twrite-char #.%\| )
		 (if current-value (twrite-string current-value))
		 (loop for i from current-length below length-to-use
		       with filler-char = (if current-value
					      (charw current-value (1-f current-length))
					      #.%\Z )
		       do
		   (twrite-char filler-char))))
	 ;; now that we've created "string-for-masks", we send it to
	 ;; create-string-for-text-box-control-value, which will reclaim it and
	 ;; tack the extra info onto the end.  -jv, 7/7/06
	 (multiple-value-bind (selection-begin? selection-end?)
	     (parse-text-box-selection selection?)
	   (create-string-for-text-box-control-value
	     string-for-masks selection-begin? selection-end?
	     foreground-color? background-color?)))
	(t
	 (masked-edit-dialogs-stack-error))))))


;;; `generic-extract-text-for-control-value' returns either a fresh text or NIL.

(defun generic-extract-text-for-control-value (value)
  (let ((text-value
          (evaluation-structure-slot value 'text-value)))
    (cond
      ((evaluation-text-p text-value)
       (copy-evaluation-text text-value))
      (t
       (dialog-attribute-must-be-structure-containing-text-error control-value)
       nil))))


;;; `decode-format-for-spinner'

(defun decode-format-for-spinner (format?)
  (cond
    ((null format?)
     (values nil nil))
    ((not (symbolp format?))
     (spinner-format-must-be-symbol-error)
     (values nil nil))
    (t
     (multiple-value-bind (left-count right-count)
         (decode-format format?)
       (unless (and left-count right-count)
         (spinner-format-unparsable-error))
       (values left-count right-count)))))


;;; `spinner-increment-is-ok'

(defun spinner-increment-is-ok (increment)
  (typecase increment
    (float
     (>= (abs increment) spinner-minimum-increment))
    (t t)))


;;; `build-spinner-grid-view-cell-value'

;; need more error checking?  Do later.  -jv, 5/11/04
;; MISNAMED.  No longer just for grid-view spinners.  FINDME.

(defun build-spinner-grid-view-cell-value (cell-value default-cell-value?)
  ;; by using default values, we allow the slots to be unspecified.
  (let ((current-value? (specified-or-inherited-structure-slot
                          cell-value 'current-value default-cell-value?
                          spinner-default-current-value))
        (low-value? (specified-or-inherited-structure-slot
                      cell-value 'low-value default-cell-value?
                      spinner-default-low-value))
        (high-value? (specified-or-inherited-structure-slot
                       cell-value 'high-value default-cell-value?
                       spinner-default-high-value))
        (increment? (specified-or-inherited-structure-slot
                      cell-value 'increment default-cell-value?
                      spinner-default-increment))
        (format? (specified-or-inherited-structure-slot
                      cell-value 'precision default-cell-value?
                      nil))
        (integral-size? nil)
        (fraction-size? nil))
    (multiple-value-setq (integral-size? fraction-size?)
      (decode-format-for-spinner format?))
    (if (and (evaluation-quantity-p current-value?)
             (evaluation-quantity-p low-value?)
             (evaluation-quantity-p high-value?)
             (evaluation-quantity-p increment?)
             (spinner-increment-is-ok
               (evaluation-quantity-value increment?))
             (<= (evaluation-quantity-value low-value?)
                 (evaluation-quantity-value current-value?)
                 (evaluation-quantity-value high-value?)))
        (let ((new-cell-value (make-spinner-cv)))
          (setf (spinner-cv-integral-size? new-cell-value) integral-size?)
          (setf (spinner-cv-fraction-size? new-cell-value) fraction-size?)
          (setf (spinner-cv-current-value new-cell-value)
                (copy-evaluation-quantity current-value?))
          (setf (spinner-cv-low-value new-cell-value)
                (copy-evaluation-quantity low-value?))
          (setf (spinner-cv-high-value new-cell-value)
                (copy-evaluation-quantity high-value?))
          (setf (spinner-cv-increment new-cell-value)
                (copy-evaluation-quantity increment?))
          new-cell-value)
        (spinner-value-stack-error
          current-value? low-value? high-value? increment?))))


;;; `twrite-spinner-value-as-string'

(defun twrite-spinner-value-as-string (spinner-value)
  (let ((write-floats-accurately-p t))
    (twrite (spinner-cv-current-value spinner-value))
    (twrite-char tree-view-item-separator)
    (twrite (spinner-cv-low-value spinner-value))
    (twrite-char tree-view-item-separator)
    (twrite (spinner-cv-high-value spinner-value))
    (twrite-char tree-view-item-separator)
    (twrite (spinner-cv-increment spinner-value))
    (when (and (spinner-cv-integral-size? spinner-value)
               (spinner-cv-fraction-size? spinner-value))
      (twrite-char tree-view-item-separator)
      (twrite (spinner-cv-integral-size? spinner-value))
      (twrite-char tree-view-item-separator)
      (twrite (spinner-cv-fraction-size? spinner-value)))))


;;; `spinner-extract-text-for-control-value'

(defun spinner-extract-text-for-control-value (value dialog-component)
  (let ((spinner-control-value
	  ;; NIL is passed for the default-value here because this is a REPLACE
	  ;; action, If we ever implement MODIFY actions, we could pass
	  ;; (dialog-component-original-value? dialog-component), or preferably,
	  ;; the computed current value as a structure -fmw, 4/27/07
          (build-spinner-grid-view-cell-value value nil)))
    ;; Note: the generated string is leaked!  -jv, 5/11/04
    ;; It's now not leaked when used in the modify-control-structure.  It is
    ;; still leaked when it goes into the dialog-component
    ;; structure. {see the def-dialog-component-attribute for
    ;; control-value}. -dkuznick, 8/24/04
    (when (spinner-cv-p (dialog-component-g2-representation? dialog-component))
      (reclaim-spinner-cv (dialog-component-g2-representation? dialog-component)))
    (setf (dialog-component-g2-representation? dialog-component)
          spinner-control-value)
    (twith-output-to-text-string
      (twrite-spinner-value-as-string spinner-control-value))))


;;; The function `send-dialog-bitmap' draws a bitmap with dimemsions given in
;;; pixels or dialog units, for the default GUI font on given window.

(defun send-dialog-bitmap (gensym-window icon-designation width? height? units)
  (send-native-bitmap gensym-window icon-designation
                      (case units
                        (dialog-units
                         (if width? (dialog-units-to-pixels gensym-window width? 'x)))
                        (t
                         width?))
                      (case units
                        (dialog-units
                         (if height? (dialog-units-to-pixels gensym-window height? 'y)))
                        (t
                         height?))))


;;; `image-extract-icon-handle-for-control-value?' returns two values: a fixnum handle
;;; for the icon specified in the ICON attribute of the given structure, or NIL
;;; if one couldn't be found, and the icon-designation it used to get the handle.

(defun image-extract-icon-handle-for-control-value? (value default-value? gensym-window
                                                           &optional width? height? (units 'pixels))
  (let ((icon-designation? (specified-or-inherited-structure-slot
                             value 'icon default-value? nil)))
    (when (valid-icon-designation-p icon-designation?)
      (values
        (send-dialog-bitmap gensym-window
                            icon-designation?
                            width? height? units)
        icon-designation?))))


;;; `image-extract-text-for-control-value'

(defun image-extract-text-for-control-value (value lisp-struct)
  (let* ((gensym-window (gensym-window-of-dialog-component
                          lisp-struct))
         (icon-handle? (image-extract-icon-handle-for-control-value?
                         value nil gensym-window
                         (dialog-component-width? lisp-struct)
                         (dialog-component-height? lisp-struct)
                         'dialog-units)))
    (if icon-handle?
        (twith-output-to-text-string
          (twrite-fixnum icon-handle?))
        (dialog-image-control-value-error "CONTROL-VALUE"
                                          "control in a dialog"))))


;;; `duration-string-from-canonical-values' -- takes the values and whips them
;;; up into a text string

(defun duration-string-from-canonical-values (weeks days hours minutes seconds)
  (twith-output-to-text-string
    (twrite-fixnum weeks)
    (twrite-char duration-field-separator)
    (twrite-fixnum days)
    (twrite-char duration-field-separator)
    (twrite-fixnum hours)
    (twrite-char duration-field-separator)
    (twrite-fixnum minutes)
    (twrite-char duration-field-separator)
    (twrite-fixnum seconds)))
    
(defun short-duration-string-from-canonical-values (hours minutes seconds)
  (twith-output-to-text-string
    (twrite-fixnum hours)
    (twrite-char duration-field-separator)
    (twrite-fixnum minutes)
    (twrite-char duration-field-separator)
    (twrite-fixnum seconds)))


;;; `get-fixnum-values-from-control-value' is meant to be used for either a
;;; standalone duration control or a duration control in a grid-view.

(defun get-fixnum-values-from-control-value (control-value default-value?)
  (macrolet ((duration-fixnum-value-of-structure-slot (structure default-struct? field)
               `(let ((derived-value (specified-or-inherited-structure-slot
                                       ,structure ,field ,default-struct? nil)))
                  (cond
                    ((null derived-value)
                     0)
                    ((evaluation-integer-p derived-value)
                     (evaluation-integer-value derived-value))
                    ((not (evaluation-integer-p derived-value))
                     (duration-not-an-integer-stack-error ,field derived-value))))))
    (values (duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-weeks)
            (duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-days)
            (duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-hours)
            (duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-minutes)
            (duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-seconds))))
            
(defun get-fixnum-values-from-new-control-value (control-value default-value?)
  (macrolet ((short-duration-fixnum-value-of-structure-slot (structure default-struct? field)
               `(let ((derived-value (specified-or-inherited-structure-slot
                                       ,structure ,field ,default-struct? nil)))
                  (cond
                    ((null derived-value)
                     0)
                    ((evaluation-integer-p derived-value)
                     (evaluation-integer-value derived-value))
                    ((not (evaluation-integer-p derived-value))
                     (duration-not-an-integer-stack-error ,field derived-value))))))
    (values (short-duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-hours)
            (short-duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-minutes)
            (short-duration-fixnum-value-of-structure-slot control-value default-value? 'number-of-seconds))))


;;; `make-duration-values-canonical' -- Things used to sort-of work without this
;;; function.  If your spec specified 3601 seconds, that would get turned into
;;; 1 hour, 1 second automatically by the CTime class in C++.  But as usual, the
;;; "normal" thing doesn't work with weeks and days.  We could send the data as
;;; specified to C, and do the work over there, but I think it's better to do it
;;; in Lisp.  Of course, the distinction is not just Lisp vs. C, it's also G2
;;; vs. TW.  I am electing to fix it in G2.  If we had released this feature
;;; (the duration control) in a commercial release, my choice might be to fix it
;;; on BOTH sides, so that it would work as long as EITHER your G2 or your TWNG
;;; were up to date; but since we've only released it as a Beta, I'm not worried
;;; about it, and I'm just fixing it in G2.  -jv, 4/22/05

(defun make-duration-values-canonical (weeks-value days-value hours-value
                                                   minutes-value seconds-value)
  (macrolet ((duration-overflow (this-field max-value upper-field)
               `(when (>=f ,this-field ,max-value)
                  (multiple-value-bind (quotient remainder)
                      (floorf ,this-field ,max-value)
                    (incff ,upper-field quotient)
                    (setq ,this-field remainder)))))

    (duration-overflow seconds-value 60 minutes-value)
    (duration-overflow minutes-value 60   hours-value)
    (duration-overflow   hours-value 24    days-value)
    (duration-overflow    days-value  7   weeks-value)

    (when (>f weeks-value 999)
      (duration-value-too-large-stack-error weeks-value))

    (values weeks-value days-value hours-value minutes-value seconds-value)))
    
(defun make-short-duration-values-canonical (hours-value minutes-value seconds-value)
  (macrolet ((short-duration-overflow (this-field max-value upper-field)
               `(when (>=f ,this-field ,max-value)
                  (multiple-value-bind (quotient remainder)
                      (floorf ,this-field ,max-value)
                    (incff ,upper-field quotient)
                    (setq ,this-field remainder)))))

    (short-duration-overflow seconds-value 60 minutes-value)
    (short-duration-overflow minutes-value 60   hours-value)

    (values hours-value minutes-value seconds-value)))


;;; `duration-extract-text-for-control-value'

(defun duration-extract-text-for-control-value (control-value)
  (multiple-value-bind (weeks-value days-value hours-value minutes-value seconds-value)
      (get-fixnum-values-from-control-value control-value nil)
    (multiple-value-bind (weeks days hours minutes seconds)
        (make-duration-values-canonical
          weeks-value days-value hours-value minutes-value seconds-value)
      (duration-string-from-canonical-values weeks days hours minutes seconds))))
      
(defun short-duration-extract-text-for-control-value (control-value)
  (multiple-value-bind (hours-value minutes-value seconds-value)
      (get-fixnum-values-from-new-control-value control-value nil)
    (multiple-value-bind (hours minutes seconds)
        (make-short-duration-values-canonical
          hours-value minutes-value seconds-value)
      (short-duration-string-from-canonical-values hours minutes seconds))))


;;; `calendar-extract-text-for-control-value'

(defun calendar-extract-text-for-control-value (value component)
  ;; These defaults of 0 are bogus, leading to a warning in TWNG's log:
  ;; error: failed to set calendar to 0:0:0
  (let* ((year-value (evaluation-structure-slot value 'selected-year 0))
         (month-value (evaluation-structure-slot value 'selected-month 0))
         (date-value (evaluation-structure-slot value 'selected-date 0))
         (date-format (dialog-component-additional-style? component)))
    (twith-output-to-text-string
      (twrite-fixnum year-value)
      (twrite-char #.%\: )
      (twrite-fixnum month-value)
      (twrite-char #.%\: )
      (twrite-fixnum date-value)
      ;; GENSYMCID-210: International format for native date/time controls
      (when date-format
        (twrite-char #.%\| )
        (twrite-string date-format)))))

;;; `time-of-day-extract-text-for-control-value'

(defun time-of-day-extract-text-for-control-value (value component)
  ;; Ditto error: failed to set time-of-day to 0:0:0:0:0:0
  (let* ((year-value (evaluation-structure-slot value 'selected-year 0))
         (month-value (evaluation-structure-slot value 'selected-month 0))
         (date-value (evaluation-structure-slot value 'selected-date 0))
         (hours-value (evaluation-structure-slot value 'selected-hour 0))
         (minutes-value (evaluation-structure-slot value 'selected-minute 0))
         (seconds-value (evaluation-structure-slot value 'selected-second 0))
         (date-format (dialog-component-additional-style? component)))
    (twith-output-to-text-string
      (twrite-fixnum year-value)
      (twrite-char #.%\: )
      (twrite-fixnum month-value)
      (twrite-char #.%\: )
      (twrite-fixnum date-value)
      (twrite-char #.%\: )
      (twrite-fixnum hours-value)
      (twrite-char #.%\: )
      (twrite-fixnum minutes-value)
      (twrite-char #.%\: )
      (twrite-fixnum seconds-value)
      ;; GENSYMCID-210: International format for native date/time controls
      (when date-format
        (twrite-char #.%\| )
        (twrite-string date-format)))))

;;; `workspace-by-uuid'

(defun workspace-by-uuid (uuid-value?)
  (let ((workspace?
          (and uuid-value? (the-item-having-uuid 'workspace uuid-value?))))
    (unless (of-class-p workspace? 'workspace)
      (dialog-workspace-unknown-uuid-error))
    workspace?))


;;; `workspace-by-name-symbol'

(defun workspace-by-name-symbol (ws-name-symbol)
  (let ((workspace?
          (get-instance-with-name-if-any 'workspace ws-name-symbol)))
    (unless (of-class-p workspace? 'workspace)
      (dialog-workspace-control-value-error
        (dialog-workspace-unknown-name-error)))
    workspace?))


;;; `workspace-dialog-component-prefers-uuid-p'

(defun workspace-dialog-component-prefers-uuid-p (dialog-control-value)
  (let* ((name-value?
           (evaluation-structure-slot dialog-control-value 'workspace-name))
         (uuid-value?
           (evaluation-structure-slot dialog-control-value 'workspace-uuid))
         (prefer-uuid? (evaluation-structure-slot dialog-control-value 'use-uuid)))
    (if (evaluation-truth-value-p prefer-uuid?)
        (evaluation-truth-value-is-true-p prefer-uuid?)
        (if (evaluation-text-p uuid-value?)
            (null name-value?)
            nil))))


;;; `workspace-dialog-component-name-symbol'

(defun workspace-dialog-component-name-symbol (name-value?)
  (cond
    ;; note, NIL is not an evaluation-symbol
    ((evaluation-symbol-p name-value?)
     (evaluation-symbol-symbol name-value?))
    ((and (evaluation-text-p name-value?)
          (>f (lengthw name-value?) 0))
     ;; This handles case and @-escapes, but is a huge macro.
     (alphabet-symbol-from-portion-of-text
       (evaluation-text-value name-value?)))
    (t
     (dialog-workspace-control-value-error
       (dialog-workspace-name-not-symbol-or-text-error)))))


;;; `workspace-dialog-component-requested-workspace?'

(defun workspace-dialog-component-requested-workspace? (dialog-control-value)
  (if (evaluation-structure-p dialog-control-value)
      (if (workspace-dialog-component-prefers-uuid-p dialog-control-value)
          (workspace-by-uuid (evaluation-structure-slot dialog-control-value 'workspace-uuid))
          (workspace-by-name-symbol
            (workspace-dialog-component-name-symbol
              (evaluation-structure-slot dialog-control-value 'workspace-name))))
      (dialog-workspace-control-value-not-structure-error)))


;;; `workspace-extract-text-for-control-value' -- we do an error check here, but
;;; if all is ok, we send the string "N/A".  C doesn't ever need to know which
;;; workspace we're showing.  That's all handled on the G2 side.  C just needs
;;; to create an HWND and tell us what it is.

(defun workspace-extract-text-for-control-value (value)
  (let ((ws-or-error-text (workspace-dialog-component-requested-workspace? value)))
    (when (text-string-p ws-or-error-text)
      (dialog-workspace-control-value-error ws-or-error-text))
    (copy-evaluation-text #w"N/A")))



;;; `derive-icon-designation-for-push-button'

(defun derive-icon-designation-for-push-button
    (correct-icon-specification?
      deprecated-icon-specification?)
  (cond
    ;; later, support taking the icon-name as a string
    ((valid-icon-designation-p correct-icon-specification?)
     (when (valid-icon-designation-p deprecated-icon-specification?)
       (push-button-using-both-icon-name-and-icon-warning))
     correct-icon-specification?)

    ((valid-icon-designation-p deprecated-icon-specification?)
     (push-button-using-icon-name-warning)
     deprecated-icon-specification?)

    (t
     nil)))


;;; `push-button-parse-control-value-text' - helper function, sets up the
;;; internal data structure.  The calling function creates the actual string.

(defun push-button-parse-control-value-text (value lisp-struct)
  (let* ((gensym-window (gensym-window-of-dialog-component lisp-struct))
         (g2-rep (dialog-component-g2-representation? lisp-struct))
         (text-value?
           (evaluation-structure-slot value 'text-value))
         (value-of-selected
           (evaluation-structure-slot value 'selected))
         (correct-icon-specification?
           (evaluation-structure-slot value 'icon))
         (deprecated-icon-specification?
           (evaluation-structure-slot value 'icon-name))
         (icon-designation?
           (derive-icon-designation-for-push-button
             correct-icon-specification?
             deprecated-icon-specification?))
         (icon-handle?
           (and icon-designation?
                (send-dialog-bitmap gensym-window
                                    icon-designation?
                                    nil nil 'pixels))))

    (unless g2-rep
      (setq g2-rep (make-push-button-cv))
      (setf (dialog-component-g2-representation? lisp-struct) g2-rep))

    ;; undocumented feature
    (when (and (evaluation-symbol-p text-value?)
               (eq (evaluation-symbol-symbol text-value?) 'ellipsis))
      (setq text-value? text-for-ellipsis))

    (cond
      ((evaluation-text-p text-value?)
       (setf (push-button-cv-label? g2-rep)
             (copy-text-string (evaluation-text-value text-value?))))
      (t
       (setf (push-button-cv-label? g2-rep) nil)
       (when text-value?
         (bad-text-value-specification-for-push-button-error text-value?))))

    (setf (push-button-cv-checked-p g2-rep)
          (and (evaluation-truth-value-p value-of-selected)
               (evaluation-truth-value-is-true-p value-of-selected)))

    (cond
      ((fixnump icon-handle?)
       (setf (push-button-cv-icon-designation? g2-rep) icon-designation?)
       (setf (push-button-cv-icon-handle? g2-rep) icon-handle?)
       (add-style-to-lisp-struct lisp-struct 'bs-icon))
      (t
       (when correct-icon-specification?
         (bad-icon-specification-for-push-button-error
           correct-icon-specification?))

       (when deprecated-icon-specification?
         (bad-icon-name-specification-for-push-button-error
           deprecated-icon-specification?))

       (setf (push-button-cv-icon-designation? g2-rep) nil)
       (setf (push-button-cv-icon-handle? g2-rep) nil)
       (delete-style-from-lisp-struct lisp-struct 'bs-icon)))))



;;; `push-button-extract-text-for-control-value' returns either a fresh text or NIL.

(defun push-button-extract-text-for-control-value (value lisp-struct)
  (push-button-parse-control-value-text value lisp-struct)
  (let* ((g2-rep (dialog-component-g2-representation? lisp-struct))
         (gensym-window (gensym-window-of-dialog-component lisp-struct))
         (support-update-color? (remote-side-supports-update-color-in-push-button-p
                                  (icp-socket-for-gensym-window? gensym-window)))
         (background-color? (evaluation-structure-slot value 'control-background-color))
         (font-color? (evaluation-structure-slot value 'text-font-color)))

    (unless (push-button-cv-p g2-rep)
      ;; panic
      (setq g2-rep (make-push-button-cv))
      (setf (dialog-component-g2-representation? lisp-struct) g2-rep))

    (when (and support-update-color? background-color?)
      (funcall (dialog-handler 'control-background-color) background-color? lisp-struct))

    (when (and support-update-color? font-color?)
      (funcall (dialog-handler 'text-font-color) font-color? lisp-struct))

    ;; This is an error, but we assume that we have already added a specific
    ;; error higher up, so we don't signal a generic error here.
    ;; (unless (or (text-string-p (push-button-cv-label? g2-rep))
    ;;             (fixnump (push-button-cv-icon-handle? g2-rep)))
    ;; ...

    (if support-update-color?
      ;;; if update color supported in twng, format is next
      ;;;  text-value <seperator> icon-handle <seperator> background-color <seperator> font-color
      (twith-output-to-text-string
        (when (text-string-p (push-button-cv-label? g2-rep))
          (twrite-string (push-button-cv-label? g2-rep)))
        (twrite-dialogs-element-separator)
        (when (fixnump (push-button-cv-icon-handle? g2-rep))
          (twrite-fixnum (push-button-cv-icon-handle? g2-rep)))
        (twrite-dialogs-element-separator)
        (when (dialog-component-control-background-color? lisp-struct)
          (twrite-string (dialog-component-control-background-color? lisp-struct)))
        (twrite-dialogs-element-separator)
        (when (dialog-component-text-font-color? lisp-struct)
          (twrite-string (dialog-component-text-font-color? lisp-struct))))
      ;;; if update color not supported in twng, format is next
      ;;;   text-value <seperator> icon-handle
      (twith-output-to-text-string
        (when (text-string-p (push-button-cv-label? g2-rep))
          (twrite-string (push-button-cv-label? g2-rep)))
        (when (fixnump (push-button-cv-icon-handle? g2-rep))
          (twrite-dialogs-element-separator)
          (twrite-fixnum (push-button-cv-icon-handle? g2-rep)))))))


;;; `toggle-button-extract-text-for-control-value'

(defun toggle-button-extract-text-for-control-value (value lisp-struct)
  (push-button-parse-control-value-text value lisp-struct)
 (let* ((g2-rep (dialog-component-g2-representation? lisp-struct))
         (gensym-window (gensym-window-of-dialog-component lisp-struct))
         (support-color-settings? (remote-side-supports-color-settings-in-toggle-button-p
				    (icp-socket-for-gensym-window? gensym-window)))
         (background-color? (evaluation-structure-slot value 'control-background-color))
         (font-color? (evaluation-structure-slot value 'text-font-color)))

    (unless (push-button-cv-p g2-rep)
      ;; panic
      (setq g2-rep (make-push-button-cv))
      (setf (dialog-component-g2-representation? lisp-struct) g2-rep))

    (when (and support-color-settings? background-color?)
      (funcall (dialog-handler 'control-background-color) background-color? lisp-struct))

    (when (and support-color-settings? font-color?)
      (funcall (dialog-handler 'text-font-color) font-color? lisp-struct))

    (twith-output-to-text-string
      (when (text-string-p (push-button-cv-label? g2-rep))
        (twrite-string (push-button-cv-label? g2-rep)))
      (twrite-dialogs-element-separator)
      (when (fixnump (push-button-cv-icon-handle? g2-rep))
        (twrite-fixnum (push-button-cv-icon-handle? g2-rep)))
      (when support-color-settings?
        (twrite-dialogs-element-separator)
        (when (dialog-component-control-background-color? lisp-struct)
          (twrite-string (dialog-component-control-background-color? lisp-struct)))
        (twrite-dialogs-element-separator)
        (when (dialog-component-text-font-color? lisp-struct)
          (twrite-string (dialog-component-text-font-color? lisp-struct))))
      (twrite-dialogs-secondary-element-separator)
      (if (push-button-cv-checked-p g2-rep)
          (twrite-string toggle-button-selected-token)
          (twrite-string toggle-button-not-selected-token)))))

(defun label-extract-text-for-control-value (value lisp-struct)
  (let* ((text-value? (evaluation-structure-slot value 'text-value))
         (gensym-window (gensym-window-of-dialog-component lisp-struct))
         (remote-support-border-settings (remote-side-supports-border-settings-in-label-p
                                           (icp-socket-for-gensym-window? gensym-window)))
         (border-color? (evaluation-structure-slot value 'border-color))
         (border-width? (evaluation-structure-slot value 'border-width))
	 (remote-support-background-settings (remote-side-supports-update-color-in-label-p
	                                        (icp-socket-for-gensym-window? gensym-window)))
	 (background-color? (evaluation-structure-slot value 'control-background-color)))
    (when remote-support-border-settings
      (if border-color?
        (funcall (dialog-handler 'border-color) border-color? lisp-struct)
        (setq border-color? (dialog-component-border-color? lisp-struct)))
      (if border-width?
        (funcall (dialog-handler 'border-width) border-width? lisp-struct)
        (setq border-width? (dialog-component-border-width? lisp-struct))))
    (when (and remote-support-background-settings background-color?)
      (funcall (dialog-handler 'control-background-color) background-color? lisp-struct))
    (twith-output-to-text-string
      (when (text-string-p text-value?)
        (twrite-string text-value?))
      (when remote-support-border-settings
        (twrite-dialogs-element-separator)
        (when (and border-color? (text-string-p border-color?))
          (twrite-string border-color?))
        (twrite-dialogs-element-separator)
        (when (and border-width? (fixnump border-width?))
          (twrite-fixnum border-width?)))
      (when remote-support-background-settings
        (twrite-dialogs-secondary-element-separator)
        (when (dialog-component-control-background-color? lisp-struct)
          (twrite-string (dialog-component-control-background-color? lisp-struct)))))))

;;; `evaluate-control-value-per-control-type' always returns a fresh text string
;;; to its callers or NIL.

(defun evaluate-control-value-per-control-type (lisp-struct control-type-symbol new-value)
  (case control-type-symbol
    (tab-frame
     (tab-frame-extract-text-for-control-value new-value lisp-struct))
    ((progress-bar track-bar)
     (bar-extract-text-for-control-value new-value))
    (slider
     (slider-extract-text-for-control-value new-value))
    (tree-view-combo-box
     (tree-view-extract-text-for-control-value new-value))
    (combo-box
     (combo-box-extract-text-for-control-value new-value lisp-struct 'replace))
    ((list-box checkable-list-box)
     (list-box-extract-text-for-control-value new-value lisp-struct 'replace
                                      control-type-symbol))
    (color-picker
     (color-picker-extract-text-for-control-value new-value))
    (full-color-picker
     (full-color-picker-extract-text-for-control-value new-value))
    (text-box
     (text-box-extract-text-for-control-value lisp-struct new-value))
    (masked-edit
     (masked-edit-extract-text-for-control-value new-value))
    (label
     (label-extract-text-for-control-value new-value lisp-struct))
    ((group radio-button check-box)
     (generic-extract-text-for-control-value new-value))
    (spinner
     (spinner-extract-text-for-control-value new-value lisp-struct))
    (image
     (image-extract-text-for-control-value new-value lisp-struct))
    (duration
     (duration-extract-text-for-control-value new-value))
    (short-duration
     (short-duration-extract-text-for-control-value new-value))
    (calendar
     (calendar-extract-text-for-control-value new-value lisp-struct))
    (time-of-day
     (time-of-day-extract-text-for-control-value new-value lisp-struct))
    (workspace
     (workspace-extract-text-for-control-value new-value))
    (push-button
     (push-button-extract-text-for-control-value new-value lisp-struct))
    (toggle-button
     (toggle-button-extract-text-for-control-value new-value lisp-struct))
    (tabular-view
     ;; Tabular-views are now initialized via their own API, instead of via
     ;; packed strings.
     (copy-wide-string #w""))
    (grid-view
     (grid-view-evaluate-control-value new-value lisp-struct))
    (t
     (generic-extract-text-for-control-value new-value))))


;;; `control-value-structure-to-g2-styles' -- looks at the given control-value,
;;; extracts out any data that needs to be transformed into g2-styles.

;; here we "know" that this is the only g2-style which can be applied to
;; check-boxes and radio-buttons, so we just set the value instead of using
;; logiorf. -jv, 8/12/04

(defun control-value-structure-to-g2-styles (control-type-symbol value)
  (let ((styles-to-add g2-style-none))
    (case control-type-symbol
      ((check-box radio-button)
       (let ((selected-or-not-value
               (evaluation-structure-slot value 'selected)))
         (if (and (evaluation-truth-value-p selected-or-not-value)
                  (evaluation-truth-value-is-true-p
                    selected-or-not-value))
             (setq styles-to-add g2-bs-initially-selected)))))
    styles-to-add))


;;; `control-value' dialog-component-attribute

(def-dialog-component-attribute control-value (new-value
                                                lisp-struct
                                                :type structure)
  (let ((control-type-symbol (map-control-type-fixnum-to-symbol
                               (dialog-component-type lisp-struct))))
    (setf (dialog-component-original-value? lisp-struct)
          (deep-copy-evaluation-value new-value))
    (setf (dialog-component-value? lisp-struct)
          (evaluate-control-value-per-control-type
            lisp-struct control-type-symbol new-value))
    (add-g2-style-to-lisp-struct
      lisp-struct
      (control-value-structure-to-g2-styles
        control-type-symbol new-value))))




;;;; Dialog Updates from TWNG



;;; `find-pos-of-char' -- a similar function probably exists in unicode or
;;; utilities1, but I don't have time to find it.  -jv, 3/29/05

(defun find-pos-of-char (string-to-search char-to-find start end)
  (loop with i = start
        while (and (not (char=w (charw string-to-search i) char-to-find))
                   (<f i end))
        do
    (setq i (1+f i))
        finally
          (return i)))


;;; `copy-of-evaluation-quantity-or-default' - a generic function, but only used
;;; by the function below (so far), so it lives here.

(defun-simple copy-of-evaluation-quantity-or-default (thing default)
  (copy-evaluation-quantity
    (if (evaluation-quantity-p thing)
        thing
        default)))


;;; `color-name-symbol-from-text-string' - this is actually a fairly generic
;;; function.  It takes a wide-string, and returns a symbol.  The symbol which
;;; is returned is the result of interning the string, with the following
;;; modifications: all letters (in the English alphabet, anyway) get
;;; upper-cased, and spaces are turned into hyphens.  Again, this is not
;;; terribly specific to color names, and could be used to turn any wide-string
;;; into a symbol, but who knows if making spaces into hyphens is always the
;;; right thing to do?  So for now, anyway, this function retains a very
;;; specific name.

(defun color-name-symbol-from-text-string (wide-string)
  (let* ((case-delta #.(-f (char-code #\A) (char-code #\a)))
         (length (lengthw wide-string))
         (new-gensym-string
           (obtain-simple-gensym-string length)))
    (loop for i from 0 below length
          as char = (charw wide-string i)
          as substitute-char = (cond
                                 ((char<=w #.%\a char #.%\z)
                                  (char+w char case-delta))
                                 ;; substitute hyphens for spaces
                                 ((char=w char #.%space)
                                  #.%\-)
                                 (t
                                  char))
          do
      (setf (schar new-gensym-string i)
            (ascii-code-char (wide-character-code substitute-char))))
    (intern-gensym-string new-gensym-string nil)))


;;; `tab-frame-updated-control-value'

(defun tab-frame-updated-control-value (component)
  (let* ((incoming-value
           (or (dialog-component-incoming-value? component)
               #w""))
         (currently-selected?
           (if (>f (text-string-length incoming-value) 0)
               (make-evaluation-text incoming-value)))
         (original-value
           (dialog-component-original-value? component))
         (labels? (evaluation-structure-slot original-value 'tab-labels))
         (icons? (evaluation-structure-slot original-value 'tab-icons))
         (position? (evaluation-structure-slot original-value 'tab-position)))
    ;; structure(tab-labels: sequence(<text>+),
    ;;           tab-icons: sequence(<text>+),
    ;;           tab-position: <symbol>),
    ;;           selected-tab: <text>)
    (allocate-evaluation-structure
      (nconc
        (if (evaluation-sequence-p labels?)
            (eval-list 'tab-labels (copy-evaluation-sequence labels?)))
        (if (evaluation-sequence-p icons?)
            (eval-list 'tab-icons (copy-evaluation-sequence icons?)))
        (if (evaluation-symbol-p position?)
            (eval-list 'tab-position (copy-evaluation-symbol position?)))
        (if currently-selected?
            (eval-list 'selected-tab currently-selected?))))))


;;; `bar-updated-control-value'

(defun bar-updated-control-value (component)
  (let ((new-value (or (dialog-component-incoming-value? component)
                       #w""))
        (slider-bar-p? (eq 'slider (map-control-type-fixnum-to-symbol
                                     (dialog-component-type component)))))
    ;; structure(current-value: <integer>,
    ;;           low-value: <integer>
    ;;           high-value: <integer>,
    ;;           increment: <integer>)
    (let* ((original-values
             (dialog-component-original-value? component))
           (low-value
             (deep-copy-evaluation-value
               (evaluation-structure-slot
                 original-values 'low-value 0)))
           (high-value
             (deep-copy-evaluation-value
               (evaluation-structure-slot
                 original-values 'high-value 1)))
           (increment
             (deep-copy-evaluation-value
               (evaluation-structure-slot
                 original-values 'increment 1)))
           (currently-selected-value
             (with-temporary-gensym-float-creation
                 bar-updated-control-value
               (multiple-value-bind
                   (newly-read-value new-value-type)
                   (read-number-from-text-string new-value)
                 (case new-value-type
                   (float
                    (if slider-bar-p?
                      (slider-compute-current-value low-value high-value
                                                    increment (floor newly-read-value))
                      (make-evaluation-integer (floor newly-read-value))))
                   (fixnum
                    (if slider-bar-p?
                      (slider-compute-current-value low-value high-value
                                                    increment newly-read-value)
                      (make-evaluation-integer newly-read-value)))
                   (t
                    (deep-copy-evaluation-value
                      (evaluation-structure-slot
                        original-values 'current-value 1))))))))
      (allocate-evaluation-structure
        (eval-list 'current-value
                   currently-selected-value
                   'low-value
                   low-value
                   'high-value
                   high-value
                   'increment
                   increment)))))


;;; `tree-view-updated-control-value'

(defun tree-view-updated-control-value (component)
  (let* ((tree-layout
          (deep-copy-evaluation-value
            (evaluation-structure-slot
              (dialog-component-original-value? component)
              'tree-layout)))
         (selected-node?
           (follow-path-string-to-node-in-tree
             (or (dialog-component-incoming-value? component)
                 #w"")
             tree-layout tree-view-hierarchy-separator)))
    ;; structure(tree-layout: sequence(<structure>*),
    ;;           [selected: <structure>])
    (allocate-evaluation-structure
      (nconc (eval-list 'tree-layout tree-layout)
             (and selected-node? (eval-list 'selected selected-node?))))))


;;; `break-up-list-box-string-into-list'

(defun break-up-list-box-string-into-list (new-value? start-pos end-character?)
  (and (text-string-p new-value?)
       (loop with len = (lengthw new-value?)
             with separator = general-dialog-element-separator
             with start = start-pos
             as i from start-pos
             as next-char = (charw new-value? i)
             while (<f i len)
             if (eqlw separator next-char)
               collect (copy-portion-of-wide-string new-value? start i) using eval-cons
               and do (setq start (+ i 1))
             else when (eqlw end-character? next-char)
                    do (loop-finish))))


;;; `find-end-of-regular-text'

(defun find-end-of-regular-text? (string separator-char end-char)
  (loop for i from 0 below end-char
        when (char=w (charw string i) separator-char)
          return i))


;;; `list-box-updated-control-value'

    ;; list-box
    ;; structure(text-sequence: sequence(<text>+),
    ;; selected: sequence(<text>+))
    ;;
    ;; combox-box
    ;; structure(text-sequence: sequence(<text>+),
    ;; selected: <text>)
    ;;
    ;; checkable-list-box
    ;; structure(text-sequence: sequence(<text>+),
    ;; checked: sequence(<text>+))

(defun list-box-updated-control-value (component type)
  (let* ((new-value? (dialog-component-incoming-value? component))
         (length? (and (text-string-p new-value?)
                       (text-string-length new-value?)))
         (lisp-list-box (dialog-component-g2-representation? component))
         (end-of-regular-text
           (or (find-end-of-regular-text?
                 new-value? general-dialog-secondary-element-separator length?)
               length?))
         (list-of-selected-values
           (break-up-list-box-string-into-list
             new-value?
             0
             general-dialog-secondary-element-separator))
         (combo-box-selection nil)
         (list-of-checked-values? '())
         (text-selection? nil))
    (replace-list-box-cv-selected
      lisp-list-box
      (and new-value?
           (copy-custom-dialog-list-with-text-strings
             list-of-selected-values)))
    (when (eq type 'checkable-list-box)
      (setq list-of-checked-values?
            (break-up-list-box-string-into-list
              new-value?
              (1+f end-of-regular-text)
              general-dialog-secondary-element-separator))
      (replace-checkable-list-box-cv-checked
        lisp-list-box
        (copy-custom-dialog-list-with-text-strings
          list-of-checked-values?)))
    (when (eq type 'combo-box)
      (setq combo-box-selection
            (if (wide-string-p new-value?)
                (copy-portion-of-wide-string new-value? 0 end-of-regular-text)
                (copy-wide-string #w"")))
      (when (/=f end-of-regular-text length?)
        (multiple-value-bind (selection-begin selection-end)
            (extract-selection-boundaries-for-text-box
              new-value?
              (+f end-of-regular-text 2)
              length?)
          (setq text-selection? (eval-list selection-begin selection-end)))))
    (allocate-evaluation-structure
      (nconc
        (eval-list
          'text-sequence
          (allocate-evaluation-sequence
            (loop for text in (list-box-cv-list lisp-list-box)
                  collect (make-evaluation-text text) using eval-cons)))
        (case type
          (combo-box
           (eval-list 'selected combo-box-selection))
          ((list-box checkable-list-box)
           (eval-list
             'selected
             (allocate-evaluation-sequence list-of-selected-values))))
        (and (eq type 'combo-box)
             text-selection?
             (eval-list 'text-selection
                        (allocate-evaluation-sequence
                          text-selection?)))
        (and (eq type 'checkable-list-box)
             (eval-list 'checked
                        (allocate-evaluation-sequence
                          list-of-checked-values?)))))))


;;; `color-picker-updated-control-value'

(defun color-picker-updated-control-value (component)
  ;; structure(selected: <text>[, colors: <sequence>])
  (let* ((selected-value?
           (if (and (dialog-component-incoming-value? component)
                    (> (lengthw (dialog-component-incoming-value? component)) 0))
               (color-name-symbol-from-text-string
                 (dialog-component-incoming-value? component))))
         (list-for-selected?
           (and selected-value?
                (eval-list 'selected selected-value?)))
         (sequence-of-colors?
           (and (evaluation-structure-p
                  (dialog-component-original-value? component))
                (evaluation-structure-slot
                  (dialog-component-original-value? component) 'colors)))
         (list-for-colors?
           (and (evaluation-sequence-p sequence-of-colors?)
                ;; manually make a copy of the sequence
                (eval-list 'colors
                           (allocate-evaluation-sequence
                             (loop for color-sym being each evaluation-sequence-element
                                   of sequence-of-colors?
                                   collect color-sym using eval-cons)))))
         (list-for-structure
           (if list-for-selected?
               (if list-for-colors?
                   (nconc list-for-selected? list-for-colors?)
                   list-for-selected?)
               list-for-colors?)))
    (allocate-evaluation-structure list-for-structure)))


;;; `full-color-picker-updated-control-value'

(defun full-color-picker-updated-control-value (component)
  (allocate-evaluation-structure
    (eval-list
      'selected
      (intern-text-string
        (tformat-text-string
          "RGB~a" (or (dialog-component-incoming-value? component)
                      ;; When we support having an initial color
                      ;; selected, will we need to use it here?  Can we ever
                      ;; get no incoming value? -dkuznick, 9/19/05
                      #w"000000"))))))


;;; `extract-selection-boundaries-for-text-box' - incomprehensibly complicated
;;; for such a simple function.  Should be improved/simplified.  -jv, 3/1/06

(defun extract-selection-boundaries-for-text-box (string begin end)
  (let* ((text-to-parse
           (copy-portion-of-wide-string string begin end))
         (separator (find-pos-of-char
                      text-to-parse
                      general-dialog-secondary-element-separator
                      0 (-f end begin)))
         (start-string (copy-portion-of-wide-string text-to-parse 0 separator))
         (end-string (copy-portion-of-wide-string text-to-parse
                                                  (1+f separator)
                                                  (-f end begin))))
    (multiple-value-bind
        (start-index start-index-type)
        (read-number-from-text-string start-string)
      (when (neq start-index-type 'fixnum)
        #+development
        (cerror "Continue"
                "extract-selection-boundaries-for-text-box got non-fixnum for start-index")
        (setq start-index 0))
      (multiple-value-bind
          (end-index end-index-type)
          (read-number-from-text-string end-string)
        (when (neq end-index-type 'fixnum)
          #+development
          (cerror "Continue"
                  "extract-selection-boundaries-for-text-box got non-fixnum for end-index")
          (setq end-index begin))
        (reclaim-wide-string text-to-parse)
        (reclaim-wide-string start-string)
        (reclaim-wide-string end-string)
        (values start-index end-index)))))


;;; `extract-color-for-text-box'

(defun extract-color-for-text-box (string begin end)
  (if (=f begin end)
      nil
      (let* ((text-to-parse
               (copy-portion-of-wide-string string begin end))
             (return-symbol
               (intern-wide-string (tformat-text-string "RGB~A" text-to-parse))))
        (reclaim-wide-string text-to-parse)
        (canonical-color-name return-symbol))))


;;; `text-updated-control-value-ex' - new-value will be reclaimed/owned by this
;;; function.

(defun text-updated-control-value-ex (new-value len end-of-text)
  (let* ((up-to-date-text
           (copy-portion-of-wide-string new-value 0 end-of-text))
         (end-of-selection (find-pos-of-char
                             new-value
                             general-dialog-element-separator
                             (1+f end-of-text) len))
         (end-of-fg-text (find-pos-of-char
                           new-value
                           general-dialog-element-separator
                           (1+f end-of-selection) len))
         (end-of-bg-text (find-pos-of-char
                           new-value
                           general-dialog-element-separator
                           (1+f end-of-fg-text) len))
         (foreground-color? (extract-color-for-text-box
                              new-value (1+f end-of-selection) end-of-fg-text))
         (background-color? (extract-color-for-text-box
                              new-value (1+f end-of-fg-text) end-of-bg-text)))
    (multiple-value-bind (selection-begin
                           selection-end)
        (extract-selection-boundaries-for-text-box
          new-value (1+f end-of-text) end-of-selection)

      (let* ((selection-value
               (if (=f selection-begin selection-end)
                   (make-evaluation-integer selection-begin)
                   (allocate-evaluation-sequence
                     (eval-list selection-begin selection-end))))
             (updated-control-value
               (eval-list 'text-value up-to-date-text
                          'selection selection-value)))
        (when foreground-color?
          (setq updated-control-value
                (nconc updated-control-value
                       (eval-list 'text-color foreground-color?))))
        (when background-color?
          (setq updated-control-value
                (nconc updated-control-value
                       (eval-list 'background-color background-color?))))
        (reclaim-text-string new-value)
        (allocate-evaluation-structure
          updated-control-value)))))


;;; `text-updated-control-value' - TW 8.2r1 will send extra data serialized into
;;; the string, representing the selection and colors of the text-box.  But
;;; instead of confidently bifurcating by the version of the window, we will
;;; just be prepared to handle either the simple or the complicated data, in
;;; either case.  -jv, 3/1/06

(defun text-updated-control-value (component)
  (let* ((new-value
           (copy-wide-string
             (or (dialog-component-incoming-value? component)
                 #w"")))
         (length-of-text (lengthw new-value))
         (end-of-text (find-pos-of-char
                        new-value
                        general-dialog-element-separator
                        0 length-of-text)))
    (cond 
      ((=f end-of-text length-of-text)
       (allocate-evaluation-structure
         (eval-list 'text-value new-value)))
      ((eq 'label (map-control-type-fixnum-to-symbol
                    (dialog-component-type component)))
       (prog1
         (allocate-evaluation-structure
           (eval-list 'text-value (copy-portion-of-wide-string new-value 0 end-of-text)))
         (reclaim-text-string new-value)))
      (t
        (text-updated-control-value-ex
          new-value length-of-text end-of-text)))))


;;; `spinner-parse-string'

(defun spinner-parse-string (value-string spin-cv)
  (let* ((len (text-string-length value-string))
         (tmp-string nil)
         (begin-search 0)
         (separator-pos 0))

    (reclaim-evaluation-quantity (spinner-cv-current-value spin-cv))
    (reclaim-evaluation-quantity (spinner-cv-low-value spin-cv))
    (reclaim-evaluation-quantity (spinner-cv-high-value spin-cv))
    (reclaim-evaluation-quantity (spinner-cv-increment spin-cv))

    (setq separator-pos
          (find-pos-of-char value-string #.%\| begin-search len))
    (setq tmp-string
          (wide-string-substring value-string begin-search separator-pos))
    (setf (spinner-cv-current-value spin-cv)
          (read-evaluation-quantity-from-text-string tmp-string))
    (reclaim-wide-string tmp-string)
    (setq begin-search (1+f separator-pos))

    (setq separator-pos
          (find-pos-of-char value-string #.%\| begin-search len))
    (setq tmp-string
          (wide-string-substring value-string begin-search separator-pos))
    (setf (spinner-cv-low-value spin-cv)
          (read-evaluation-quantity-from-text-string tmp-string))
    (reclaim-wide-string tmp-string)
    (setq begin-search (1+f separator-pos))

    (setq separator-pos
          (find-pos-of-char value-string #.%\| begin-search len))
    (setq tmp-string
          (wide-string-substring value-string begin-search separator-pos))
    (setf (spinner-cv-high-value spin-cv)
          (read-evaluation-quantity-from-text-string tmp-string))
    (reclaim-wide-string tmp-string)
    (setq begin-search (1+f separator-pos))

    (setq separator-pos
          (find-pos-of-char value-string #.%\| begin-search len))
    (setq tmp-string
          (wide-string-substring value-string begin-search separator-pos))
    (setf (spinner-cv-increment spin-cv)
          (read-evaluation-quantity-from-text-string tmp-string))
    (reclaim-wide-string tmp-string)

    (allocate-evaluation-structure
      (eval-list 'current-value
                 (copy-evaluation-quantity (spinner-cv-current-value spin-cv))
                 'low-value
                 (copy-evaluation-quantity (spinner-cv-low-value spin-cv))
                 'high-value
                 (copy-evaluation-quantity (spinner-cv-high-value spin-cv))
                 'increment
                 (copy-evaluation-quantity (spinner-cv-increment spin-cv))))))


;;; `ensure-spinner-control-value-structure'

(defun ensure-spinner-control-value-structure (dialog-component)
  (or (dialog-component-g2-representation? dialog-component)
      (setf (dialog-component-g2-representation? dialog-component)
            (make-spinner-cv))))


;;; `spinner-updated-control-value'

(defun spinner-updated-control-value (component)
    ;; structure(current-value: <quantity>,
    ;;           low-value: <quantity>
    ;;           high-value: <quantity>,
    ;;           increment: <quantity>)
    (let ((spinner-cv (ensure-spinner-control-value-structure component)))
      (cond
        ((and (text-string-p (dialog-component-incoming-value? component))
              (/=f 0 (text-string-length (dialog-component-incoming-value? component))))
         (spinner-parse-string (dialog-component-incoming-value? component)
                               spinner-cv))
        ((evaluation-structure-p (dialog-component-original-value? component))
         (deep-copy-evaluation-value
           (dialog-component-original-value? component)))
        (t
         #+development
         (cerror "Go on, using default values"
                 "spinner-updated-control-value: unable to find value")
         (allocate-evaluation-structure
           (eval-list 'current-value
                      spinner-default-current-value
                      'low-value
                      spinner-default-low-value
                      'high-value
                      spinner-default-high-value
                      'increment
                      spinner-default-increment))))))


;;; `parse-duration-string-into-eval-list' -- what a pedantic hack.  To be improved.
;;; -jv, 2/20/05

(defun parse-duration-string-into-eval-list (duration-string)
  (let* ((len (text-string-length duration-string))
         (weeks 0) (days 0) (hours 0) (minutes 0) (seconds 0)
         (i 0))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq weeks (+f (-f (charw duration-string i) #.%\0)
                      (*f weeks 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw duration-string i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq days (+f (-f (charw duration-string i) #.%\0)
                     (*f days 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw duration-string i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq hours (+f (-f (charw duration-string i) #.%\0)
                      (*f hours 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw duration-string i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq minutes (+f (-f (charw duration-string i) #.%\0)
                        (*f minutes 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw duration-string i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq seconds (+f (-f (charw duration-string i) #.%\0)
                        (*f seconds 10)))
      (setq i (1+f i)))
    (eval-list 'number-of-weeks weeks
               'number-of-days days
               'number-of-hours hours
               'number-of-minutes minutes
               'number-of-seconds seconds)))
               
(defun parse-short-duration-string-into-eval-list (duration-string)
  (let* ((len (text-string-length duration-string))
         (hours 0) (minutes 0) (seconds 0)
         (i 0))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq hours (+f (-f (charw duration-string i) #.%\0)
                      (*f hours 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw duration-string i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq minutes (+f (-f (charw duration-string i) #.%\0)
                        (*f minutes 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw duration-string i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw duration-string i))) do
      (setq seconds (+f (-f (charw duration-string i) #.%\0)
                        (*f seconds 10)))
      (setq i (1+f i)))
    (eval-list 'number-of-hours hours
               'number-of-minutes minutes
               'number-of-seconds seconds)))


;;; `duration-updated-control-value'

(defun duration-updated-control-value (component)
  (let* ((new-value (or (dialog-component-incoming-value? component)
                        #w""))
         (parsed-eval-list
           (parse-duration-string-into-eval-list new-value)))
    ;; structure(number-of-weeks: <integer>,
    ;;           number-of-days: <integer>
    ;;           number-of-hours: <integer>
    ;;           number-of-minutes: <integer>
    ;;           number-of-seconds: <integer>)
    (allocate-evaluation-structure parsed-eval-list)))
    
(defun short-duration-updated-control-value (component)
  (let* ((new-value (or (dialog-component-incoming-value? component)
                        #w""))
         (parsed-eval-list
           (parse-short-duration-string-into-eval-list new-value)))
    ;; structure(number-of-hours: <integer>
    ;;           number-of-minutes: <integer>
    ;;           number-of-seconds: <integer>)
    (allocate-evaluation-structure parsed-eval-list)))


;;; `calendar-updated-control-value'

(defun calendar-updated-control-value (component)
  (let* ((new-value (or (dialog-component-incoming-value? component)
                        #w""))
         (len (text-string-length new-value))
         (year 0) (month 0) (day 0)
         (i 0))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq year (+f (-f (charw new-value i) #.%\0)
                     (*f year 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw new-value i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq month (+f (-f (charw new-value i) #.%\0)
                      (*f month 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw new-value i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq day (+f (-f (charw new-value i) #.%\0)
                    (*f day 10)))
      (setq i (1+f i)))
    ;; structure(selected-year:   <integer between 1601 and 30827>
    ;;           selected-month:  <integer between 1 and 12>
    ;;           selected-date:   <integer between 1 and 31>
    (allocate-evaluation-structure
      (eval-list 'selected-year year
                 'selected-month month
                 'selected-date day))))


;;; `time-of-day-updated-control-value'

(defun time-of-day-updated-control-value (component)
  (let* ((new-value (or (dialog-component-incoming-value? component)
                        #w""))
         (len (text-string-length new-value))
         (year 0) (month 0) (day 0) (hour 0) (minute 0) (second 0)
         (i 0))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq year (+f (-f (charw new-value i) #.%\0)
                     (*f year 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw new-value i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq month (+f (-f (charw new-value i) #.%\0)
                      (*f month 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw new-value i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq day (+f (-f (charw new-value i) #.%\0)
                    (*f day 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw new-value i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq hour (+f (-f (charw new-value i) #.%\0)
                     (*f hour 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw new-value i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq minute (+f (-f (charw new-value i) #.%\0)
                       (*f minute 10)))
      (setq i (1+f i)))
    (loop while (and (<f i len) (not (digit-char-pw (charw new-value i)))) do
      (setq i (1+f i)))
    (loop while (and (<f i len) (digit-char-pw (charw new-value i))) do
      (setq second (+f (-f (charw new-value i) #.%\0)
                       (*f second 10)))
      (setq i (1+f i)))
    ;; structure(selected-year:   <integer between 1601 and 30827>
    ;;           selected-month:  <integer between 1 and 12>
    ;;           selected-date:   <integer between 1 and 31>
    ;;           selected-hour:   <integer between 0 and 23>
    ;;           selected-minute: <integer between 0 and 59>
    ;;           selected-second: <integer between 0 and 50>
    (allocate-evaluation-structure
      (eval-list 'selected-year year
                 'selected-month month
                 'selected-date day
                 'selected-hour hour
                 'selected-minute minute
                 'selected-second second))))


;;; `workspace-updated-control-value'

(defun workspace-updated-control-value (component)
  (let* ((orig-control-value
           (dialog-component-original-value? component))
         (prefer-uuid-p
           (and (evaluation-structure-p orig-control-value)
                (workspace-dialog-component-prefers-uuid-p orig-control-value))))
    (if prefer-uuid-p
        (allocate-evaluation-structure
          (eval-list
            'workspace-uuid
            (copy-text-string
              (evaluation-structure-slot orig-control-value 'workspace-uuid))))
        (allocate-evaluation-structure
          (eval-list
            'workspace-name
            (if (evaluation-structure-p orig-control-value)
                (workspace-dialog-component-name-symbol
                  (evaluation-structure-slot orig-control-value 'workspace-name))
                (copy-wide-string
                  (or (dialog-component-incoming-value? component)
                      #w""))))))))


;;; `button-updated-control-value'

(defun button-updated-control-value (component)
  (let ((new-value (or (dialog-component-incoming-value? component)
                       #w"")))
    ;; structure(text-value: <text>
    ;;           selected: <truth-value>)
    (allocate-evaluation-structure
      (eval-list 'text-value
                 (copy-wide-string
                   (dialog-component-value? component))
                 'selected
                 (make-evaluation-truth-value
                   (if (text-string= new-value #w"True")
                       truth
                       falsity))))))


;;; `push-button-updated-control-value'

(defun push-button-updated-control-value (component)
  ;; structure(text-value: <text>
  ;;           icon: <icon-designation>)
  (let* ((g2-rep (dialog-component-g2-representation? component))
         (utd-label (dialog-component-incoming-value? component)))

    (when (and (wide-string-p utd-label)
               (/=f 0 (wide-string-length utd-label)))
      (when (wide-string-p (push-button-cv-label? g2-rep))
        (reclaim-wide-string (push-button-cv-label? g2-rep)))
      (setf (push-button-cv-label? g2-rep) (copy-wide-string utd-label)))

    (allocate-evaluation-structure
      (nconc
        (if (wide-string-p (push-button-cv-label? g2-rep))
            (eval-list 'text-value
                       (make-evaluation-text (push-button-cv-label? g2-rep))))
        (if (valid-icon-designation-p (push-button-cv-icon-designation? g2-rep))
            (eval-list 'icon (push-button-cv-icon-designation? g2-rep)))))))


;;; `toggle-button-updated-control-value'

(defun toggle-button-updated-control-value (component)
  ;; structure(text-value: <text>
  ;;           icon: <icon-designation>,
  ;;           selected: <truth-value>)
  (let* ((g2-rep (dialog-component-g2-representation? component))
         (new-value (or (dialog-component-incoming-value? component)
                        #w""))
         (len (text-string-length new-value))
         (delimiter (find-pos-of-char
                      new-value
                      general-dialog-secondary-element-separator
                      0 len))
         (label (copy-portion-of-wide-string new-value 0 delimiter))
         (status (copy-portion-of-wide-string new-value (1+f delimiter) len))
         (selected-p (text-string= status toggle-button-selected-token)))
    (reclaim-wide-string status)

    (when (and (wide-string-p label)
               (/=f 0 (wide-string-length label)))
      (when (wide-string-p (push-button-cv-label? g2-rep))
        (reclaim-wide-string (push-button-cv-label? g2-rep)))
      (setf (push-button-cv-label? g2-rep) (copy-wide-string label)))


    (allocate-evaluation-structure
      (nconc
        (if (wide-string-p (push-button-cv-label? g2-rep))
            (eval-list 'text-value
                       (make-evaluation-text (push-button-cv-label? g2-rep))))
        (if (valid-icon-designation-p (push-button-cv-icon-designation? g2-rep))
            (eval-list 'icon (push-button-cv-icon-designation? g2-rep)))
        (eval-list 'selected
                   (make-evaluation-truth-value
                     (if selected-p truth falsity)))))))


;;; `compose-up-to-date-control-value' -- We receive "current value" back from C
;;; as a string, and here is where we will turn it back into a structure, to
;;; send it to the callback or the query.

(defun compose-up-to-date-control-value (component)
  (let ((control-symbol (map-control-type-fixnum-to-symbol
			  (dialog-component-type component))))
    (if (and (neq control-symbol 'tabular-view)
	     (null (dialog-component-incoming-value? component))
	     (dialog-component-original-value? component))
	(deep-copy-evaluation-value
	  (dialog-component-original-value? component))
        (case control-symbol
          (tab-frame
           (tab-frame-updated-control-value component))
          ((progress-bar track-bar slider)
           (bar-updated-control-value component))
          (tree-view-combo-box
           (tree-view-updated-control-value component))
          ((combo-box list-box checkable-list-box)
           (list-box-updated-control-value component control-symbol))
          (image
           #+development
           (cerror "Do nothing"
                   "updating not supported on IMAGE controls"))
          (color-picker
           (color-picker-updated-control-value component))
          (full-color-picker
           (full-color-picker-updated-control-value component))
          ((text-box masked-edit label group)
           (text-updated-control-value component))
          (spinner
           (spinner-updated-control-value component))
          (duration
           (duration-updated-control-value component))
          (short-duration
           (short-duration-updated-control-value component))
          (calendar
           (calendar-updated-control-value component))
          (time-of-day
           (time-of-day-updated-control-value component))
          (workspace
           (workspace-updated-control-value component))
          ((radio-button check-box)
           (button-updated-control-value component))
          (push-button
           (push-button-updated-control-value component))
          (toggle-button
           (toggle-button-updated-control-value component))
          (tabular-view
           (tabular-view-updated-control-value component))
          (grid-view
           (grid-view-updated-control-value component))
          (t
           (copy-wide-string #w"unsupported control type"))))))


;;; `lookup-component-given-component-internal-id'

(defun lookup-component-given-component-internal-id (component-id dialog)
  (loop for component in (dynamic-dialog-components dialog)
        when (eql component-id (dialog-component-internal-id component))
          return component))


;;; `map-control-id-to-kb-id'

(defun map-control-id-to-kb-id (control-id dialog)
  (let ((component
          (lookup-component-given-component-internal-id
            control-id dialog)))
    (and component
         (dialog-component-kb-id component))))


;;; `set-new-value-of-component-or-components'

(defun set-new-value-of-component-or-components (dialog control-id new-value)
  (let ((kb-id (map-control-id-to-kb-id control-id dialog)))
    (loop for component in (dynamic-dialog-components dialog)
          when (eql kb-id (dialog-component-kb-id component))
            do
              (let ((old-value? (dialog-component-incoming-value? component)))
                (when old-value?
                  (reclaim-wide-string old-value?)))
              #+echo-dialog-send
              (dbg-output-dialog-update component new-value)
              (setf (dialog-component-incoming-value? component)
                    (copy-wide-string new-value)))))




;;;; Grid-Views

;;; Example strings: (replace control characters to make these work)
;;;               #w"{3/4}]"
;;;               #w"(0,0)T^A header 0,0^A]"
;;;               #w"(2,1)C260ET^ACheck Box^A]"
;;;               #w"(1,2)EC133T^Aone-two-celltext^AF^Aaquamarine^A]"
;;;               #w"(1,3)EC67B^Ablue^AT^Aitem1^Bitem2^Bitem3^A]"
;;;               #w"(_,2)H23]"
;;;               #w"(1,2)S^Ayellow^A]"



(def-concept grid-views)


;;; The parameter `grid-view-column-properties' is an alist of all attributes of
;;; a column-spec, in the form of (external-name . internal-name).

(defparameter grid-view-column-properties
  '((text-value . text)                        ; Column header text
    (default-cell-type . cell-type)
    (default-cell-value . cell-value)
    (text-color . text-color)
    (background-color . background-color)
    (read-only . read-only)
	(is-multiline . is-multiline) ; added by SoftServe
    (width . width)
    (alignment . alignment)
    (bold . bold)
    (ellipsis-button . ellipsis-button)))

;;; The parameter `default-grid-view-alignment-bits' contains Windows text
;;; format bits which are applied (for now at least) to all cells.

(defparameter default-grid-view-alignment-bits (logiorf dt-vcenter dt-singleline dt-end-ellipsis))

;;; The parameter `grid-view-column-properties-returned-to-user' is the subset
;;; of the above properties which are returned to the user in a callback.  As
;;; far as I can tell, the only reason we leave some out is because they are
;;; hard to translate back into evaluation values: eg, default-cell-value.

(defparameter grid-view-column-properties-returned-to-user
  '((text-value . text)
    (read-only . read-only)
    (alignment . alignment)
    (bold . bold)
    (ellipsis-button . ellipsis-button)))


;;; The type `grid-view-cell-structure-type' is an approximation of the type of
;;; a grid-cell as supplied to a system procedure. It isn't exact since the
;;; cell-value and selected types depend on the cell-type, but it is useful, and
;;; is a strict superset.

;; NOTE: This type is only used for modify/replace, not for initial creation!
(def-type-parameter grid-view-cell-structure-type
    (structure ((cell-type (member text-box integer quantity check-box combo-box color-picker
                                   calendar time-of-day duration short-duration image spinner))
                (cell-value (structure ((text-value text)
                                        (current-value datum)
                                        (text-sequence (sequence text))
                                        (colors (sequence symbol))
                                        (selected-year integer)
                                        (selected-month integer)
                                        (selected-date integer)
                                        (selected-hour integer)
                                        (selected-minute integer)
                                        (selected-second integer)
                                        (low-value number)
                                        (high-value number)
                                        (increment  number)
                                        (precision symbol)
                                        (icon item-or-datum) ; icon-designation-p
					(list-box-style (member dropdown dropdownlist))
                                        (selected (or truth-value symbol text)))))
                (text-color symbol)
                (background-color symbol)
                (alignment (member left center right))
		(bold truth-value)
                (read-only truth-value)
				(is-multiline truth-value) ; added by SoftServe
                (selected truth-value)
                (ellipsis-button truth-value))))


;;; `lisp-grid-view'

(def-structure lisp-grid-view
  (lisp-grid-view-row-count 0)
  (lisp-grid-view-column-count 0)
  (lisp-grid-view-row-header-p t)
  ;; No reclaimer on lisp-grid-view-row-information because it's currently
  ;; handled via the reclaimer on lisp-grid-view-rows
  (lisp-grid-view-row-information '())
  (lisp-grid-view-column-header-p t)
  ;; NOTE: column-information is a mixture of lisp and evaluation values!
  (lisp-grid-view-column-information '() :reclaimer reclaim-grid-view-column-information)
  (lisp-grid-view-rows '() :reclaimer reclaim-lisp-grid-view-rows)
  (lisp-grid-view-selected-cells '() :reclaimer reclaim-custom-dialog-tree)
  (lisp-grid-view-notification? nil)
  ;; Not ...-sorting-p because this may get extended in the future to have a
  ;; meaningful non-NIL value, and having "?" at the end of "tag" names
  ;; confuses emacs -dkuznick, 9/2/05
  (lisp-grid-view-sorting nil)
  (lisp-grid-view-row-strings '() :reclaimer reclaim-custom-dialog-list-with-text-strings)
  (lisp-grid-view-use-row-header t)
  (lisp-grid-view-use-column-header t)
  (lisp-grid-view-end-data-delimiter #.%\])
  (lisp-grid-view-background-color? nil)
  (lisp-grid-view-support-font? nil))


;;; `reclaim-grid-view-column-information'

(defun-void reclaim-grid-view-column-information (col-info)
  (loop for elt in col-info
        do (reclaim-grid-view-column-information-element elt)
        finally (reclaim-custom-dialog-list col-info)))

(defun-void reclaim-grid-view-column-information-element (column-info-element)
  (loop for (key value) on column-info-element by 'cddr
        do (reclaim-if-evaluation-value value)
        finally (reclaim-custom-dialog-list column-info-element)))


;;; `reclaim-lisp-grid-view-rows'

(defun-void reclaim-lisp-grid-view-rows (rows)
  (declare (ignore rows))
  (loop for i from 0 below (lisp-grid-view-row-count structure-being-reclaimed)
        do
    ;; Always delete the 0th row.  Each time through the loop this will be the
    ;; next row.
    (grid-view-delete-row-locally structure-being-reclaimed 0)))


(defmacro grid-view-row-info (lisp-grid-view row)
  `(nth ,row (lisp-grid-view-row-information ,lisp-grid-view)))

(defmacro grid-view-column-info (lisp-grid-view col)
  `(nth ,col (lisp-grid-view-column-information ,lisp-grid-view)))


;;; `grid-view-cell'

(defparameter grid-view-cell-properties
  '(cell-type cell-value text-color background-color read-only is-multiline selected alignment bold ellipsis-button))

(def-structure grid-view-cell
  (grid-view-cell-text-color? nil)
  (grid-view-cell-bg-color? nil)
  (grid-view-cell-type? nil)
  (grid-view-cell-value? nil :reclaimer reclaim-structure-if-any)
  (grid-view-cell-read-only? nil)	 ; An evaluation-boolean or NIL, meaning unspecified.
  (grid-view-cell-is-multiline? nil)	 ; SoftServe
  (grid-view-cell-alignment? nil)
  (grid-view-cell-bold? nil)		 ; Ditto
  (grid-view-cell-ellipsis-button? nil)
  (grid-view-cell-text-font? nil)
  (grid-view-cell-text-font-size? nil)) ; Ditto


;;; The macro `grid-view-ref' references the grid-view-cell at row, col.

(defmacro grid-view-ref (lisp-grid-view row col)
  `(managed-svref (nth ,row (lisp-grid-view-rows ,lisp-grid-view)) ,col))

(defun coerce-to-evaluation-boolean (evalue?)
  (when evalue?
    (make-evaluation-boolean-value
      (evaluation-value-is-true-p evalue?))))

(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar list-of-grid-tokens '())

(defvar list-of-grid-attributes '())

(defmacro def-grid-token (description letter)
  (let ((constant-name
          (intern (format nil "GRID-TOKEN-~:@(~A~)" description))))
    `(progn
       (push ,letter list-of-grid-tokens)
       (defconstant ,constant-name ,letter))))


(defmacro def-grid-attribute-type (description letter)
  (let ((constant-name
          (intern (format nil "GRID-TOKEN-~:@(~A~)" description))))
    `(progn
       (push ,letter list-of-grid-tokens)
       (push ,letter list-of-grid-attributes)
       (defconstant ,constant-name ,letter))))


(def-grid-token start-dim  #.%\{ )
(def-grid-token slash      #.%\/ )
(def-grid-token end-dim    #.%\} )
(def-grid-token start-cell #.%\( )
(def-grid-token comma      #.%\, )
(def-grid-token end-cell   #.%\) )

; (def-grid-token end-data   #.%\] )
(defun grid-token-end-data (gensym-window)
  (if (window-supports-grid-view-delimiter-fix gensym-window)
      (code-charw 3)
      #.%\]))

(def-grid-token sort-p     #.%\$ )
(def-grid-token visible-cell        #.%\V )
(def-grid-token title-row-height    #.%\H )
(def-grid-token title-column-width  #.%\W )
(def-grid-token frozen-row-count    #.%\A )
(def-grid-token frozen-column-count #.%\C )

(def-grid-attribute-type alignment  #.%\A )


;; `grid-token-per-row-or-col' - This was not exactly the original design.  The
;; underscore was intended to mean "data for the entire row/column".  That still
;; applies, in the case of things like row-height and column-width, which only
;; apply on a per-row or per-column basis.  But for text, what it was originally
;; supposed to mean was "put this text into every cell in the row (or column?)".
;; That functionality was never necessary, as we implemented that feature at the
;; G2 level.  What we needed TWNG to provide was a way to set the text of the
;; header cell, and I (jv) blithely changed TWNG so that the interpretation was
;; as such.  That's the agreed-upon meaning of '_', as of this date.  This works
;; with all versions of TWNG at the present time.  I have tested 8.1r0,
;; 8.1r1. 8.2r0, and the up-to-date sandbox builds of 8.2r1 and 8.3r0, and this
;; always sets the header text, and never sets text for the entire row.  So,
;; that has always been its de facto meaning.  Note, however, that this is only
;; supported by TWNG when the header is visible.  If not, you cannot refer to
;; the header, if not.  (That's essentially because we don't think of it as
;; "visible" or not, we think of it as "present" or not.)  So, the way to refer
;; to a header cell is with '_', but, again, only if it's present/visible/
;; shown/whatever.  -jv, 2/6/06
(def-grid-token per-row-or-col      #.%\_ )

(def-grid-attribute-type bg-color   #.%\B )
(def-grid-attribute-type cell-type  #.%\C )
(def-grid-attribute-type bold       #.%\D )
(def-grid-attribute-type editable   #.%\E )
(def-grid-attribute-type fg-color   #.%\F )
(def-grid-attribute-type is-multiline   #.%\G ) ; added by SoftServe
(def-grid-attribute-type row-height #.%\H )
(def-grid-attribute-type image      #.%\I )
(def-grid-attribute-type clicked    #.%\K )
(def-grid-attribute-type selection  #.%\L )
(def-grid-attribute-type style      #.%\S )
(def-grid-attribute-type cell-text  #.%\T )
(def-grid-attribute-type value      #.%\V )
(def-grid-attribute-type col-width  #.%\W )
(def-grid-attribute-type use-header #.%\X )
(def-grid-attribute-type text-font  #.%\Y )
(def-grid-attribute-type text-font-size #.%\J)

(defconstant grid-view-close-dimensions-char #.%\} )
(defconstant grid-view-open-cell-char #.%\( )
(defconstant grid-view-close-cell-char #.%\) )

); eval-when

;;; `grid-view-set-header-text'

(defun grid-view-set-header-text (gv row column new-text)
  ;; not implemented; users cannot change the text of the header
  ;; programmatically, so it should not actually come up.  -jv, 4/29/05
  (declare (ignore gv row column new-text)))


;;; `set-grid-view-integer-value'

(defun-void set-grid-view-integer-value (cell-value new-text)
  (let ((type-of-number (and (evaluation-text-p new-text)
                             (syntactically-numeric-p
                               (evaluation-text-value new-text)))))
    (cond
      ((eq type-of-number 'INTEGER)
       (multiple-value-bind
           (newly-read-value new-value-type)
           (with-temporary-gensym-float-creation
               set-grid-view-integer-value
             (read-number-from-text-string
               (evaluation-text-value new-text)))
         (unless (eq new-value-type 'FIXNUM)
           #+development
           (cerror "Continue, using zero"
                   "For INTEGER cell, got value back from TWNG, and found it to ~
                    be syntactically an integer, but read-number-from-text-string ~
                    apparently could not make it into a fixnum.")
           (setq newly-read-value 0))
         (setf (integer-cv-value cell-value) newly-read-value)))
      (t
       #+development
       (cerror "Continue, using zero"
               "For INTEGER cell, got value back from TWNG, and found it not ~
                to be syntactically an integer")
       (setf (integer-cv-value cell-value) 0)))))


;;; `set-grid-view-quantity-value'

(defun-void set-grid-view-quantity-value (cell-value new-text)
  (let* ((type-of-number (and (evaluation-text-p new-text)
                              (syntactically-numeric-p
                                (evaluation-text-value new-text)))))
    (cond
      ((memq type-of-number '(INTEGER FLOAT))
       (let ((newly-read-value
               (with-temporary-gensym-float-creation
                   set-grid-view-quantity-value
                 (make-evaluation-quantity
                   (read-number-from-text-string
                     (evaluation-text-value new-text))))))
         (setf (quantity-cv-value cell-value) newly-read-value)))
      (t
       #+development
       (cerror "Continue, using zero"
               "For QUANTITY cell, got value back from TWNG, and found it not ~
                to be syntactically numeric")
       (setf (quantity-cv-value cell-value) 0)))))


;;; `set-grid-view-calendar-value'

(defun set-grid-view-calendar-value (cell-value calendar-string)
  ;; expects a string like mm/dd/yy(yy)
  ;; we need to determine what calendar-format the cell is using to know how
  ;; to parse it -jv, 9/5/06
  (let* ((len (text-string-length calendar-string))
         (field1 0) (field2 0) (field3 0)
         (year 0) (month 0) (date 0) (i 0))

    ;; parse field1
    (loop while (and (< i len) (digit-char-pw (charw calendar-string i))) do
      (setq field1 (+f (-f (charw calendar-string i) #.%\0)
                      (*f field1 10)))
      (setq i (1+f i)))

    ;; skip slash or other junk
    (loop while (and (< i len) (not (digit-char-pw (charw calendar-string i)))) do
      (setq i (1+f i)))

    ;; parse field2
    (loop while (and (< i len) (digit-char-pw (charw calendar-string i))) do
      (setq field2 (+f (-f (charw calendar-string i) #.%\0)
                     (*f field2 10)))
      (setq i (1+f i)))

    ;; skip slash or other junk
    (loop while (and (< i len) (not (digit-char-pw (charw calendar-string i)))) do
      (setq i (1+f i)))

    ;; parse field3
    (loop while (and (< i len) (digit-char-pw (charw calendar-string i))) do
      (setq field3 (+f (-f (charw calendar-string i) #.%\0)
                     (*f field3 10)))
      (setq i (1+f i)))

    ;; Ignore any extra junk at the end.  Now set and sanity check args.

    (cond
      ((eql (calendar-cv-format cell-value) g2-dts-gov-format)
       (setq year field1)
       (setq month field2)
       (setq date field3))
      ((eql (calendar-cv-format cell-value) g2-dts-eu-format)
       (setq date field1)
       (setq month field2)
       (setq year field3))
      (t
       (setq month field1)
       (setq date field2)
       (setq year field3)))

    (when (or (< month 1)
              (> month 12))
      (setq month 1))
    (when (or (< date 1)
              (> date 31))
      ;; bah, allow 31 for any month, in this first attempt
      (setq date 1))
    ;; first, a sanity-check on the year
    (when (or (< year 1601)
              (> year 30827))
      #+development
      (cerror "Continue, substituting the current year."
              "Invalid year supplied to set-grid-view-calendar-value")
      (setq year (get-current-year)))

    (setf (calendar-cv-year cell-value) year)
    (setf (calendar-cv-month cell-value) month)
    (setf (calendar-cv-date cell-value) date)))


;;; `set-grid-view-time-of-day-value'

(defun set-grid-view-time-of-day-value (cell-value time-string)
  ;; expects a string like hh:mm:ss
  (let* ((len (text-string-length time-string))
         (hour 0) (minute 0) (second 0) (i 0))

    ;; parse hour
    (loop while (and (< i len) (digit-char-pw (charw time-string i))) do
      (setq hour (+f (-f (charw time-string i) #.%\0)
                     (*f hour 10)))
      (setq i (1+f i)))

    ;; skip colon or other junk
    (loop while (and (< i len) (not (digit-char-pw (charw time-string i)))) do
      (setq i (1+f i)))

    ;; parse minute
    (loop while (and (< i len) (digit-char-pw (charw time-string i))) do
      (setq minute (+f (-f (charw time-string i) #.%\0)
                       (*f minute 10)))
      (setq i (1+f i)))

    ;; skip colon or other junk
    (loop while (and (< i len) (not (digit-char-pw (charw time-string i)))) do
      (setq i (1+f i)))

    ;; parse second
    (loop while (and (< i len) (digit-char-pw (charw time-string i))) do
      (setq second (+f (-f (charw time-string i) #.%\0)
                       (*f second 10)))
      (setq i (1+f i)))

    ;; Ignore any extra junk at the end.  Now sanity check args.

    (when (or (< hour 0)
              (> hour 23))
      (setq hour 0))
    (when (or (< minute 0)
              (> minute 59))
      (setq minute 0))
    (when (or (< second 0)
              (> second 59))
      (setq second 0))

    (setf (time-of-day-cv-hour cell-value) hour)
    (setf (time-of-day-cv-minute cell-value) minute)
    (setf (time-of-day-cv-second cell-value) second)))


;;; `set-grid-view-duration-value'

(defun set-grid-view-duration-value (cell-value new-text)
  (let* ((parsed-list (parse-duration-string-into-eval-list new-text))
         (nweeks? (or (cadr (memq 'number-of-weeks parsed-list)) 0))
         (ndays? (or (cadr (memq 'number-of-days parsed-list)) 0))
         (nhours? (or (cadr (memq 'number-of-hours parsed-list)) 0))
         (nminutes? (or (cadr (memq 'number-of-minutes parsed-list)) 0))
         (nseconds? (or (cadr (memq 'number-of-seconds parsed-list)) 0)))
    (setf (duration-cv-weeks cell-value) nweeks?)
    (setf (duration-cv-days cell-value) ndays?)
    (setf (duration-cv-hours cell-value) nhours?)
    (setf (duration-cv-minutes cell-value) nminutes?)
    (setf (duration-cv-seconds cell-value) nseconds?)))
    
(defun set-grid-view-short-duration-value (cell-value new-text)
  (let* ((parsed-list (parse-short-duration-string-into-eval-list new-text))
         (nhours? (or (cadr (memq 'number-of-hours parsed-list)) 0))
         (nminutes? (or (cadr (memq 'number-of-minutes parsed-list)) 0))
         (nseconds? (or (cadr (memq 'number-of-seconds parsed-list)) 0)))
    (setf (short-duration-cv-hours cell-value) nhours?)
    (setf (short-duration-cv-minutes cell-value) nminutes?)
    (setf (short-duration-cv-seconds cell-value) nseconds?)))


(defun set-grid-view-image-value (cell-value new-text)
  ;; Right now we are getting an empty string back.  So just use what's there
  ;; already.
  (declare (ignore cell-value new-text))
  nil)


;;; `set-grid-view-spinner-value'

(defun set-grid-view-spinner-value (cell-value new-text)
  (let* ((type-of-number (and (evaluation-text-p new-text)
                              (syntactically-numeric-p
                                (evaluation-text-value new-text)))))
    (cond
      ((memq type-of-number '(INTEGER FLOAT))
       (let ((newly-read-value
               (with-temporary-gensym-float-creation
                   set-grid-view-spinner-value
                 (make-evaluation-quantity
                   (read-number-from-text-string
                     (evaluation-text-value new-text))))))
         (setf (spinner-cv-current-value cell-value) newly-read-value)))
      (t
       #+development
       (cerror "Continue, using zero"
               "For SPINNER cell, got value back from TWNG, and found it not ~
                to be syntactically numeric")
       (setf (quantity-cv-value cell-value) 0)))))


;;; `grid-view-set-cell-text'

(defun-void grid-view-set-cell-text (gv row column new-text)
  (cond
    ((or (<f row 0) (<f column 0))
     (grid-view-set-header-text gv row column new-text))
    (t
     (let* ((rows? (lisp-grid-view-rows gv))
            (row-spec? (nth row rows?))
            (cell-structure? (and row-spec? (managed-svref row-spec? column)))
            (cell-type? (and cell-structure? (grid-view-cell-type? cell-structure?)))
            (cell-value (and cell-structure? (grid-view-cell-value? cell-structure?))))
       #+development
       (unless cell-type?
         (cerror "Continue" "No cell-type supplied"))
       (when cell-type?
         (case cell-type?
           (text-box
            (reclaim-if-evaluation-value (text-box-cv-text? cell-value))
            (setf (text-box-cv-text? cell-value)
                  (make-evaluation-text new-text)))
           (integer
            (set-grid-view-integer-value cell-value new-text))
           (quantity
            (set-grid-view-quantity-value cell-value new-text))
           (check-box
            (reclaim-if-evaluation-value (check-box-cv-label? cell-value))
            (setf (check-box-cv-label? cell-value)
                  (make-evaluation-text new-text)))
           ((combo-box color-picker)
            (reclaim-custom-dialog-list-with-text-strings
              (list-box-cv-selected cell-value))
            (setf (list-box-cv-selected cell-value)
                  (custom-dialog-list (make-evaluation-text new-text))))
           (calendar
            (set-grid-view-calendar-value cell-value new-text))
           (time-of-day
            (set-grid-view-time-of-day-value cell-value new-text))
           (duration
            (set-grid-view-duration-value cell-value new-text))
           (short-duration
            (set-grid-view-short-duration-value cell-value new-text))
           (image
            (set-grid-view-image-value cell-value new-text))
           (spinner
            (set-grid-view-spinner-value cell-value new-text))
           (t
            #+development
            (cerror "Continue" "Unknown grid-view cell-type: ~s" cell-type?))))))))


;;; `grid-view-set-cell-additional-value'

(defun-void grid-view-set-cell-additional-value (gv row column new-text)
  (cond
    ((or (<f row 0) (<f column 0))
     ;; I don't know what this would mean
     #+development
     (cerror "Continue"
             "Cannot set the value of a header cell"))
    (t
     (let* ((rows? (lisp-grid-view-rows gv))
            (row-spec? (nth row rows?))
            (cell-structure? (and row-spec? (managed-svref row-spec? column)))
            (cell-type? (and cell-structure? (grid-view-cell-type? cell-structure?))))
       #+development
       (unless cell-type?
         (cerror "Continue" "No cell-type supplied"))
       (when cell-type?
         (case cell-type?
           (check-box
            (cond
              ((text-string= new-text #w"1")
               (setf (check-box-cv-checked-p
                       (grid-view-cell-value? cell-structure?)) t))
              ((text-string= new-text #w"0")
               (setf (check-box-cv-checked-p
                       (grid-view-cell-value? cell-structure?)) nil))
              (t
               #+development
               (cerror "Continue, taking no action"
                       "Invalid 'value' for grid-view check-box: ~s"
                       new-text))))
           (t
            #+development
            (cerror "Continue" "Unknown supported grid-view cell-type for 'value': ~s"
                    cell-type?))))))))


(defun grid-view-clear-selection (gv)
  (reclaim-custom-dialog-tree (lisp-grid-view-selected-cells gv))
  (setf (lisp-grid-view-selected-cells gv) nil))

(defun %grid-view-cell-selected-p (gv row column)
  (loop for cell in (lisp-grid-view-selected-cells gv)
	when (and (=f row (car cell))
		  (=f column (cdr cell)))
	  return cell))

(defun grid-view-cell-selected-p (gv row column)
  (not (null (%grid-view-cell-selected-p gv row column))))
  
(defun grid-view-set-cell-selected (gv row column selected-p)
  (when (and (<f -1 row (length (lisp-grid-view-rows gv)))
	     (<f -1 column (length (lisp-grid-view-column-information gv))))
    (let ((cell? (%grid-view-cell-selected-p gv row column)))
      (cond (selected-p
	     (unless cell?
	       (custom-dialog-push
		 (custom-dialog-cons row column)
		 (lisp-grid-view-selected-cells gv))))
	    (t
	     (when cell?
	       (setf (lisp-grid-view-selected-cells gv)
		     (delete-custom-dialog-element cell? (lisp-grid-view-selected-cells gv)))))))))

(def-substitution-macro grid-view-select-cell (gv row column)
  (grid-view-set-cell-selected gv row column t))


;;; `grid-view-set-notification'

(defun grid-view-set-notification (gv row column)
  (setf (lisp-grid-view-notification? gv)
        (custom-dialog-cons row column)))


;;; `parse-pair-into-row-and-column'

(defun parse-pair-into-row-and-column (token)
  (let* ((len (text-string-length token))
         (row 0) (column 0) (i 0))

    ;; get past the open paren
    (loop while (and (< i len) (not (digit-char-pw (charw token i)))) do
      (setq i (1+f i)))

    ;; read row
    (loop while (and (< i len) (digit-char-pw (charw token i))) do
      (setq row (+f (-f (charw token i) #.%\0)
                    (*f row 10)))
      (setq i (1+f i)))

    ;; get past the comma
    (loop while (and (< i len) (not (digit-char-pw (charw token i)))) do
      (setq i (1+f i)))

    ;; read column
    (loop while (and (< i len) (digit-char-pw (charw token i))) do
      (setq column (+f (-f (charw token i) #.%\0)
                       (*f column 10)))
      (setq i (1+f i)))

    (values row column)))


;;; `grid-view-apply-updates' -- when we get a string from TWNG C, we receive it
;;; here and apply the changes to the internal data structures.
;;; In the original implementation, we expected this string to be the current
;;; value of all cells.  Now we only expect to receive the size of the grid, and
;;; the value of the most recently edited cell, if any.  -jv, 7/26/06

(defun-void grid-view-apply-updates (gv incoming-string)
  (when (lisp-grid-view-notification? gv)
    (reclaim-custom-dialog-cons (lisp-grid-view-notification? gv))
    (setf (lisp-grid-view-notification? gv) nil))

  (loop with len = (lengthw incoming-string)
        with start = 0
        with i = 0
        with row = -1
        with column = -1
        as whole-token = nil
        as next-token = (charw incoming-string i)
        while (< i len)
        do
    (case next-token
      (#.grid-token-start-dim
       (setq i (find-pos-of-char incoming-string grid-view-close-dimensions-char
                                 i len))
       ;; I don't think we care about this, although we could compare values as
       ;; a sanity check.  -jv, 3/29/05
       ;; (lisp-grid-view-row-count gv) (lisp-grid-view-column-count gv)
       ;; (setq whole-token (copy-portion-of-wide-string incoming-string start (1+f i)))
       )
      (#.grid-token-start-cell
       (setq i (find-pos-of-char incoming-string grid-view-close-cell-char
                                 i len))
       (setq whole-token (copy-portion-of-wide-string incoming-string start (1+f i)))
       (multiple-value-setq (row column)
         (parse-pair-into-row-and-column whole-token))
       (reclaim-text-string whole-token))
      ((#.grid-token-cell-text #.grid-token-cell-type
                               #.grid-token-bg-color #.grid-token-fg-color
                               #.grid-token-col-width #.grid-token-row-height)
       (setq i (find-pos-of-char incoming-string general-dialog-element-separator
                                 i len))
       (setq whole-token (copy-portion-of-wide-string incoming-string (1+f start) i))
       (when (eql next-token #.grid-token-cell-text)
         (grid-view-set-cell-text gv row column whole-token))
       (reclaim-text-string whole-token))
      (#.grid-token-value
       (setq i (1+f i))
       (setq whole-token (copy-portion-of-wide-string incoming-string (1+f start) (1+f i)))
       (grid-view-set-cell-additional-value gv row column whole-token)
       (reclaim-text-string whole-token))

      ;; As of 8.3r0, TWNG no longer sends this opcode. Selection changes are
      ;; sent independently. Since previous TWNG's are not allowed to connect,
      ;; we don't need to support it any longer.
      (#.grid-token-selection
       (dwarn "Obsolete grid-view token: ~s" next-token))

      (#.grid-token-clicked
       ;; right now, (ellipsis-button) "clicked" is the only "notification" we report
       (setq i (1+f i))
       (setq whole-token (copy-portion-of-wide-string incoming-string (1+f start) (1+f i)))
       ;; whole-token better equal #w"1"; we assume it does
       (grid-view-set-notification gv row column)
       (reclaim-text-string whole-token))
      (t
       #+development
       (cerror "Continue" "Unknown grid-view token: ~s" next-token)))
    ;; The following should be handled in the loop control clauses
    (setq i (1+f i))
    (setq start i)
    ;; What's this for if the "as" clause is there in the loop?
    (setq whole-token nil)))


;;; `grid-view-unknown-cell-type-error'

(defun grid-view-unknown-cell-type-error (cell-type)
  (dialogs-stack-error nil
                       "Unknown CELL-TYPE for a GRID-VIEW dialog control: ~s"
                       cell-type))


;;; `rows-not-a-sequence-error'

(defun rows-not-a-sequence-error (rows?)
  (dialogs-stack-error nil
                       "The control-value of a GRID-VIEW control must be a ~
                        structure, with attribute ROWS, which must be a ~
                        sequence.~

   The given dialog specification is incorrectly formed.  The attribute ROWS ~
   is not a sequence:

 ~NA" rows?))


;;; `columns-not-a-sequence-error'

(defun columns-not-a-sequence-error (columns?)
  (dialogs-stack-error nil
                       "The control-value of a GRID-VIEW control must be a ~
                        structure, with attribute COLUMNS, which must be a ~
                        sequence.~

   The given dialog specification is incorrectly formed.  The attribute COLUMNS ~
   is not a sequence:

 ~NA" columns?))


;;; `at-least-one-column-required-error'

(defun at-least-one-column-required-error ()
  (dialogs-stack-error nil
                       "The control-value of a GRID-VIEW control must be a ~
                        structure, with attribute COLUMNS, which must contain ~
                        at least one column.  ~

   The given dialog specification is incorrectly formed.  The attribute COLUMNS ~
   is an empty sequence."))


(defun row-or-column-not-a-structure-error (bad-value type)
  (dialogs-stack-error nil
                       "The control-value of a GRID-VIEW control must be a ~
  structure, with attribute ~a, which must be a sequence of structures. ~
  The given dialog specification is incorrectly formed.  The following ~
  element of the sequence is not a structure:
  ~NA"
                       type
                       bad-value))


(defun cell-settings-not-a-sequence-error (row-number cell-settings?)
  (dialogs-stack-error nil
                       "The control-value of a GRID-VIEW control must be a ~
                        structure, with attribute ROWS, which must be a ~
                        sequence of structures, where each structure in the ~
                        sequence must have an attribute CELL-SETTINGS, which ~
                        must be a sequence of structures.~
~
    The given dialog specification is incorrectly formed.  In row #~d, the ~
    CELL-SETTINGS attribute is not a sequence:

~NA" row-number cell-settings?))


(defun cell-not-a-structure-error (row-number cell?)
  (dialogs-stack-error nil
                       "The control-value of a GRID-VIEW control must be a ~
                        structure, with attribute ROWS, which must be a ~
                        sequence of structures, where each structure in the ~
                        sequence must have an attribute CELL-SETTINGS, which ~
                        must be a sequence of structures.~
~
    The given dialog specification is incorrectly formed.  In row #~d, the ~
    CELL-SETTINGS contains an element which is not a structure:

~NA"
                       row-number cell?))


(defun not-all-columns-the-same-length-error (row-number)
  (dialogs-stack-error nil
                       "The control-value of a GRID-VIEW control must be a ~
                        structure, with attribute ROWS, which must be a ~
                        sequence of structures, where each structure in the ~
                        sequence must have an attribute CELL-SETTINGS, which ~
                        must be a sequence of structures.  Each row must have ~
                        the same number of elements in its CELL-SETTINGS.
~
    The given dialog specification is incorrectly formed.  Row #~d has ~
    a different number of columns from the COLUMNS specification."
                       row-number))


(defun no-dialog-grid-view-operation-error (dialog-id)
  (dialogs-stack-error
    nil "The dialog-id ~NA does not identify an existing dialog."
    dialog-id))

(defun control-not-a-grid-view-operation-error (kb-control-id)
  (dialogs-stack-error
    nil "The control-id ~NA does not identify a grid-view."
    kb-control-id))

(defun new-column-not-the-same-length-error (new-row-count existing-row-count)
  (dialogs-stack-error
    nil "Can't add new row to grid-view because it has ~NV columns, ~
         which is not the same number as the existing rows have: ~NV."
    new-row-count existing-row-count))

(defun invalid-row-insertion-point-grid-view-insert-error (bad-row max-row)
  (dialogs-stack-error
    nil "Trying to insert a new row in grid-view at position ~NF. The ~
         position must be between 0 and the current number of rows (~NV), ~
         inclusive."
    bad-row max-row))

(defun unrecognized-attribute-grid-view-insert-error (attribute-name)
  (dialogs-stack-error
    nil "The attribute ~NA is not recognized as an attribute of a ~
        grid-view row." attribute-name))


(defun invalid-cell-replace-point-grid-view-error (bad-row max-row bad-col max-col)
  (dialogs-stack-error
    nil "Trying to replace a cell in grid-view at position (~NF, ~NF). Each ~
         position must be at least 0 and less than the current number of ~
         rows (~NV) and columns (~NV), respectively."
    bad-row bad-col max-row max-col))


(defun sys-proc-not-supported-grid-view-error (sys-proc g2-window)
  (dialogs-stack-error
    nil "System procedure ~s not supported on window ~NF"
    sys-proc g2-window))

(defun selected-cells-not-formatted-properly-error ()
  (dialogs-stack-error nil
                       "The SELECTED-CELLS attribute of the control-value of ~
                        a GRID-VIEW control, if present, must be a sequence of ~
                        structures, with each structure having attribute ROW ~
                        and COLUMN, which each must be integers."))


(defun sorting-not-formatted-properly-error ()
  (dialogs-stack-error nil
                       "The SORTING attribute of the control-value of a ~
                        GRID-VIEW control, if present, must be a ~
                        truth-value."))

(defun background-color-not-formatted-properly-error ()
  (dialogs-stack-error nil
                       "The BACKGROUND-COLOR attribute of the control-value of a ~
                        GRID-VIEW control, if present, must be a symbol naming a color."))


(defun use-row-col-header-not-formatted-properly-error (attribute)
  (dialogs-stack-error nil
                       "The ~a attribute of the control-value ~
                        of a GRID-VIEW control, if present, must be a ~
                        truth-value."
                       attribute))


(defun invalid-color-selected-for-grid-view-color-picker-error (requested-symbol)
  (dialogs-stack-error nil
                       "The SELECTED attribute of a cell with type COLOR-PICKER in a GRID-VIEW ~
     control must be a symbol which names a color available in the color-picker.  The ~
     symbol ~s does not name such a color." requested-symbol))

(defun non-color-selected-for-grid-view-color-picker-error (requested)
  (dialogs-stack-error nil
                       "The SELECTED attribute of a cell with type COLOR-PICKER in a GRID-VIEW ~
     control must be a symbol which names a color available in the 2nd level color menu.  The ~
     value ~NA is not a symbol." requested))

(defun grid-view-row-height-not-an-integer-error ()
  (dialogs-stack-error nil
                       "Attribute HEIGHT in GRID-VIEW must be an integer."))

(defun grid-view-column-width-not-an-integer-error ()
  (dialogs-stack-error nil
                       "Attribute WIDTH in GRID-VIEW must be an integer."))

(defun grid-view-alignment-invalid-format-error ()
  (dialogs-stack-error nil
                       "Attribute ALIGNMENT in GRID-VIEW must be the symbol ~
                        LEFT, CENTER or RIGHT."))

(defun grid-view-text-not-a-text-error ()
  (dialogs-stack-error nil
                       "Attribute TEXT-VALUE in GRID-VIEW must be a text."))

(defun grid-view-color-not-a-symbol-error ()
  (dialogs-stack-error nil
                       "Colors in GRID-VIEW controls must be symbols."))

(defun grid-view-cell-value-not-a-structure-error ()
  (dialogs-stack-error nil
                       "Attribute CELL-VALUE in cell within GRID-VIEW ~
                        control must be a structure."))

(defun grid-view-combo-box-element-not-text-error (element)
  (dialogs-stack-error nil
                       "Attribute CELL-VALUE in dialog control structure must be ~
                        a structure with a TEXT-SEQUENCE attribute that is a ~
                        sequence of texts, but at least one of the elements of ~
                        the sequence, ~NA, is not a text." element))

(defun grid-view-combo-box-selected-error (selected sequence)
  (dialogs-stack-error nil
                       "The SELECTED attribute of a combo-box in a grid-view ~
                        must specify a text which is present in the ~
                        TEXT-SEQUENCE; ~NA was not found in ~NA"
                       selected sequence))

(defun grid-view-combo-box-style-error (style)
  (dialogs-stack-error nil
                       "The LIST-BOX-STYLE attribute of a combo-box in a grid-view ~
                        must be either the symbol DROPDOWN or DROPDOWNLIST, not ~NA"
		       style))
  
(defun grid-view-invalid-integer-error ()
  (dialogs-stack-error
    nil "The value of attribute CURRENT-VALUE ~
         in the cell-value of an INTEGER cell of ~
         a GRID-VIEW dialog control, must be an integer, if present."))

(defun grid-view-invalid-quantity-error ()
  (dialogs-stack-error
    nil "The value of attribute CURRENT-VALUE ~
         in the cell-value of a QUANTITY cell of ~
         a GRID-VIEW dialog control, must be a quantity, if present."))

(defun grid-view-calendar-non-integer-error ()
  (dialogs-stack-error
    nil "The values of attributes SELECTED-YEAR, SELECTED-MONTH, and ~
         SELECTED-DATE, in the cell-value of a CALENDAR cell of ~
         a GRID-VIEW dialog control, must be integers, if present."))

(defun grid-view-calendar-invalid-year-error ()
  (dialogs-stack-error
    nil "The value of attributes SELECTED-YEAR in the cell-value of a ~
         CALENDAR cell of a GRID-VIEW dialog control must be an integer ~
         between 1970 and 3000, inclusive."))

(defun grid-view-calendar-invalid-month-error ()
  (dialogs-stack-error
    nil "The value of attributes SELECTED-MONTH in the cell-value of a ~
         CALENDAR cell of a GRID-VIEW dialog control must be an integer ~
         between 1 and 12, inclusive."))

(defun grid-view-calendar-invalid-date-error ()
  (dialogs-stack-error
    nil "The value of attributes SELECTED-DATE in the cell-value of a ~
         CALENDAR cell of a GRID-VIEW dialog control must be a date ~
         which exists in the specified month and year."))

(defun grid-view-time-of-day-non-integer-error ()
  (dialogs-stack-error
    nil "The values of attributes SELECTED-HOUR, SELECTED-MINUTE, and ~
         SELECTED-SECOND, in the cell-value of a CALENDAR cell of ~
         a GRID-VIEW dialog control, must be integers, if present."))

(defun grid-view-time-of-day-invalid-hour-error ()
  (dialogs-stack-error
    nil "The value of attributes SELECTED-HOUR in the cell-value of a ~
         CALENDAR cell of a GRID-VIEW dialog control must be an integer ~
         between 0 and 23, inclusive."))

(defun grid-view-time-of-day-invalid-minute-error ()
  (dialogs-stack-error
    nil "The value of attributes SELECTED-MINUTE in the cell-value of a ~
         CALENDAR cell of a GRID-VIEW dialog control must be an integer ~
         between 0 and 59, inclusive."))

(defun grid-view-time-of-day-invalid-second-error ()
  (dialogs-stack-error
    nil "The value of attributes SELECTED-HOUR in the cell-value of a ~
         CALENDAR cell of a GRID-VIEW dialog control must be an integer ~
         between 0 and 59, inclusive."))



(defun verify-rows-is-a-sequence (control-value)
  (let ((rows? (evaluation-structure-slot control-value 'rows)))
    (unless (evaluation-sequence-p rows?)
      (rows-not-a-sequence-error rows?))))


(defun verify-each-row-or-column-is-a-structure (control-value attribute)
  (loop for row-or-col being each evaluation-sequence-element
        of (evaluation-structure-slot control-value attribute)
        unless  (evaluation-structure-p row-or-col)
          do
            (row-or-column-not-a-structure-error row-or-col attribute)))


(defun verify-each-row-is-a-structure (control-value)
  (verify-each-row-or-column-is-a-structure control-value 'rows))


(defun verify-every-CELL-SETTINGS-attribute-is-a-sequence (control-value)
  (loop for row being each evaluation-sequence-element
        of (evaluation-structure-slot control-value 'rows)
        as i = 0 then (1+f i)
        as cell-settings = (evaluation-structure-slot row 'cell-settings)
        unless (evaluation-sequence-p cell-settings)
          do
            (cell-settings-not-a-sequence-error 0 cell-settings)))


(defun verify-every-cell-is-a-structure (control-value)
  (loop for row being each evaluation-sequence-element
        of (evaluation-structure-slot control-value 'rows)
        as i = 0 then (1+f i)
        as cell-settings = (evaluation-structure-slot row 'cell-settings)
        do
    (loop for cell being each evaluation-sequence-element of cell-settings
          unless (evaluation-structure-p cell) do
              (cell-not-a-structure-error i cell))))


(defun verify-same-number-of-columns (control-value)
  (let ((columns? (evaluation-structure-slot control-value 'columns)))
    (if (evaluation-sequence-p columns?)
        (if (evaluation-sequence-empty-p columns?)
            (at-least-one-column-required-error)
            (loop with rows? = (evaluation-structure-slot control-value 'rows)
                  with number-of-columns = (evaluation-sequence-length columns?)
                  for row being each evaluation-sequence-element of rows?
                  as i from 0
                  as cell-settings = (evaluation-structure-slot row 'cell-settings)
                  as row-length = (evaluation-sequence-length cell-settings)
                  do
              (unless (=f number-of-columns row-length)
                (not-all-columns-the-same-length-error i))))
        (columns-not-a-sequence-error columns?))))


(defun verify-each-column-is-a-structure (control-value)
  (verify-each-row-or-column-is-a-structure control-value 'columns))

(defun verify-format-of-selected-cells (control-value)
  (let ((selected-cells? (evaluation-structure-slot control-value 'selected-cells)))
    (if selected-cells?
        (unless (and (evaluation-sequence-p selected-cells?)
                     (loop for selected-cell being each
                           evaluation-sequence-element of selected-cells?
                           always (and (evaluation-structure-p selected-cell)
                                       (evaluation-integer-p
                                         (evaluation-structure-slot selected-cell 'column))
                                       (evaluation-integer-p
                                         (evaluation-structure-slot selected-cell 'row)))))
          (selected-cells-not-formatted-properly-error)))))


(defun verify-format-of-sorting (control-value)
  (let ((sorting? (evaluation-structure-slot control-value 'sorting)))
    (when sorting?
      ;; This will likely be extended in the future to be a structure
      ;; containing information about the sort -dkuznick, 9/2/05
      (unless (evaluation-truth-value-p sorting?)
        (sorting-not-formatted-properly-error)))))

(defun verify-format-of-background-color (control-value)
  (let ((background-color? (evaluation-structure-slot control-value 'background-color)))
    (when background-color?
      (unless (and (symbolp background-color?)
		   (gensym-color-p background-color?))
        (background-color-not-formatted-properly-error)))))


(defun verify-format-of-use-row-column-header (control-value)
  (let ((use-row-header? (evaluation-structure-slot control-value
                                                    'use-row-header))
        (use-column-header? (evaluation-structure-slot control-value
                                                       'use-column-header)))
    (when use-row-header?
      (unless (evaluation-truth-value-p use-row-header?)
        (use-row-col-header-not-formatted-properly-error 'use-row-header)))
    (when use-column-header?
      (unless (evaluation-truth-value-p use-column-header?)
        (use-row-col-header-not-formatted-properly-error 'use-column-header)))))


(defun validate-grid-control-value-is-properly-formed (control-value)
  (verify-rows-is-a-sequence control-value)
  (verify-each-row-is-a-structure control-value)
  (verify-every-CELL-SETTINGS-attribute-is-a-sequence control-value)
  (verify-every-cell-is-a-structure control-value)
  (verify-same-number-of-columns control-value)
  (verify-each-column-is-a-structure control-value)
  (verify-format-of-selected-cells control-value)
  (verify-format-of-sorting control-value)
  (verify-format-of-background-color control-value)
  (verify-format-of-use-row-column-header control-value))




(defun write-grid-view-dimensions (rows cols)
  (tformat "{~d/~d}" rows cols))

(defun write-grid-view-use-row-col-header (row-p col-p)
  ;; row-p true means we want a row-header, which itself is a column to the
  ;; left of all the data
  ;; col-p true means we want a column-header, which itself is a row above all
  ;; the data
  (tformat "~c~a"
           grid-token-use-header
           (cond ((and row-p col-p) 0)
                 ((and col-p (not row-p)) 1)
                 ((and row-p (not col-p)) 2)
                 ;; want no headers
                 (t 3))))

(defun write-grid-view-sorting (sort-p)
  (tformat "~c~d" grid-token-sort-p (if sort-p 1 0)))

(defun write-grid-view-visible-cell (row column)
  (tformat "~c~d~c~d" grid-token-visible-cell row grid-token-visible-cell column))

(defun write-grid-view-title-row-height (height)
  (tformat "~c~d" grid-token-title-row-height height))

(defun write-grid-view-title-column-width (width)
  (tformat "~c~d" grid-token-title-column-width width))

(defun write-grid-view-frozen-row-count (count)
  (tformat "~c~d" grid-token-frozen-row-count count))

(defun write-grid-view-frozen-column-count (count)
  (tformat "~c~d" grid-token-frozen-column-count count))

(defun write-grid-view-background-color (color)
  (tformat "~c~d" grid-token-bg-color (rgb-value-of-gensym-color color)))

(defun write-grid-view-terminator (gv)
  (twrite-char (lisp-grid-view-end-data-delimiter gv)))

(defun write-grid-view-global-info (lisp-grid-view component)
  (let ((row-count (lisp-grid-view-row-count lisp-grid-view))
        (column-count (lisp-grid-view-column-count lisp-grid-view))
        (use-row-header-p (lisp-grid-view-use-row-header lisp-grid-view))
        (use-column-header-p (lisp-grid-view-use-column-header lisp-grid-view))
        (sort-p (lisp-grid-view-sorting lisp-grid-view))
        (background-color? (lisp-grid-view-background-color? lisp-grid-view))
        (visible-cell?
         (evaluation-structure-slot
           (dialog-component-original-value? component) 'visible-cell))
        (title-row-height
         (evaluation-structure-slot
           (dialog-component-original-value? component) 'title-row-height))
        (title-column-width
         (evaluation-structure-slot
           (dialog-component-original-value? component) 'title-column-width))
        (frozen-row-count
         (evaluation-structure-slot
           (dialog-component-original-value? component) 'frozen-row-count))
        (frozen-column-count
         (evaluation-structure-slot
           (dialog-component-original-value? component) 'frozen-column-count)))
    (write-grid-view-dimensions
      ;; We need to increment each of these to account for the row and column
      ;; headers, if present.  Note that a column-header is itself a row, and
      ;; vice-versa, hence what looks like a logic error.  -dkuznick, 9/28/05
      (if use-column-header-p
          (1+f row-count)
          row-count)
      (if use-row-header-p
          (1+f column-count)
          column-count))

    (when (or (not use-row-header-p) (not use-column-header-p))
      (write-grid-view-use-row-col-header use-row-header-p
                                          use-column-header-p))
    (when sort-p
      (write-grid-view-sorting sort-p))

    (when (and visible-cell?
               (fixnump (evaluation-structure-slot visible-cell? 'row))
               (fixnump (evaluation-structure-slot visible-cell? 'column)))
      (write-grid-view-visible-cell (evaluation-structure-slot visible-cell? 'row)
                                    (evaluation-structure-slot visible-cell? 'column)))

    (when (and title-row-height (fixnump title-row-height) (>=f title-row-height 0))
      (write-grid-view-title-row-height title-row-height))
    (when (and title-column-width (fixnump title-column-width) (>=f title-column-width 0))
      (write-grid-view-title-column-width title-column-width))

    (when (and frozen-row-count (fixnump frozen-row-count) (>f frozen-row-count 0))
      (write-grid-view-frozen-row-count frozen-row-count))
    (when (and frozen-column-count (fixnump frozen-column-count) (>f frozen-column-count 0))
      (write-grid-view-frozen-column-count frozen-column-count))

    (when background-color?
      (write-grid-view-background-color background-color?))

    ;; Separates the header-ish info from the rest.
    (write-grid-view-terminator lisp-grid-view)))


(defun write-grid-view-row-designation (row-num)
  (tformat "(~d,~c)" row-num grid-token-per-row-or-col))

(defun write-grid-view-column-designation (col-num)
  (tformat "(~c,~d)" grid-token-per-row-or-col col-num))

(defun write-grid-view-cell-designation (row-num col-num)
  (tformat "(~d,~d)" row-num col-num))

(defun write-grid-view-selected (selected-p)
  (when selected-p
    (tformat "~c1" grid-token-selection)))

(defun grid-view-encode-alignment (alignment?)
  (let ((value? (encode-text-alignment alignment?)))
    (if value?
	(logiorf default-grid-view-alignment-bits value?))))

(defun write-grid-view-alignment (alignment?)
  (when alignment?
    (tformat "~c~d"
             grid-token-alignment
	     (or (grid-view-encode-alignment alignment?)
		 (grid-view-alignment-invalid-format-error)))))

(defun write-grid-view-bold (bold?)
  (when bold?
    (tformat "~c~d" grid-token-bold (if (evaluation-value-is-true-p bold?) 1 0))))

(defun write-grid-view-read-only (read-only?)
  (tformat "~c~d"
           grid-token-editable
           (if (evaluation-value-is-true-p read-only?)
               0
               1)))
			   
(defun write-grid-view-cell-is-multiline (is-multiline?)
  (when is-multiline?
    (tformat "~c~d" grid-token-is-multiline (if (evaluation-value-is-true-p is-multiline?) 1 0))))
			   
(defun write-grid-view-row-height (height?)
  (cond
    ((null height?)
     t)
    ((evaluation-integer-p height?)
     (tformat "~c~d" grid-token-row-height (evaluation-integer-value height?)))
    (t
     (grid-view-row-height-not-an-integer-error))))

(defun write-grid-view-column-width (width?)
  (cond
    ((null width?)
     t)
    ((evaluation-integer-p width?)
     (tformat "~c~d" grid-token-col-width (evaluation-integer-value width?)))
    (t
     (grid-view-column-width-not-an-integer-error))))


(defun map-grid-view-cell-type-to-dialogs-fixnum (cell-type? ellipsis-button?)
  (let ((ellipsis-button-p (evaluation-value-is-true-p ellipsis-button?)))
    (cond
      ((or (null cell-type?) (not (symbolp cell-type?)))
       (map-control-type-symbol-to-fixnum 'text-box ellipsis-button-p))
      ((eq cell-type? 'color-picker)
       ;; in this first implementation, at least, a color-picker is a regular
       ;; old combo-box on the C side; we handle it specially here in Lisp.
       (map-control-type-symbol-to-fixnum 'combo-box ellipsis-button-p))
      (t
       (map-control-type-symbol-to-fixnum cell-type? ellipsis-button-p)))))


(defun write-grid-view-cell-type (cell-type? ellipsis-button?)
  (when cell-type?
    (tformat "~c~d"
             grid-token-cell-type
             (map-grid-view-cell-type-to-dialogs-fixnum cell-type?
                                                        ellipsis-button?))))


(defun write-general-grid-view-text-value (text?)
  (when (and (evaluation-text-p text?)
             (>f (text-string-length (evaluation-text-value text?)) 0))
    (twrite-char grid-token-cell-text)
    (tformat "~a" text?)
    (twrite-dialogs-element-separator)))


;;; `write-grid-view-row-header-text' and `write-grid-view-column-header-text'
;;; It's important not to call these when the row-header or column header,
;;; respectively, is not visible/present.  -jv, 2/1/06

(defun write-grid-view-row-header-text (gv row-num row-header-text)
  (tformat "(~d,~c)" row-num grid-token-per-row-or-col)
  (write-general-grid-view-text-value row-header-text)
  (write-grid-view-terminator gv))

(defun write-grid-view-column-header-text (gv column-num column-header-text)
  (tformat "(~c,~d)" grid-token-per-row-or-col column-num)
  (write-general-grid-view-text-value column-header-text)
  (write-grid-view-terminator gv))


(defun write-grid-view-color (requested-color)
  (unless (evaluation-symbol-p requested-color)
    (grid-view-color-not-a-symbol-error))
  (let ((color-name (copy-color-symbol-name requested-color)))
    (twrite-string color-name)
    (twrite-dialogs-element-separator)
    (reclaim-text-string color-name)))

(defun write-grid-view-colors (text-color? bg-color?)
  (when text-color?
    (twrite-char grid-token-fg-color)
    (write-grid-view-color text-color?))
  (when bg-color?
    (twrite-char grid-token-bg-color)
    (write-grid-view-color bg-color?)))

(defun write-grid-view-text-font (text-font?)
  (when text-font?
    (tformat "~c~d" grid-token-text-font text-font?)
    (twrite-dialogs-element-separator)))

(defun write-grid-view-text-font-size (text-font-size?)
  (when text-font-size?
    (tformat "~c~d" grid-token-text-font-size text-font-size?)))

;;; `write-text-box-grid-view-cell-value'

(defun write-text-box-grid-view-cell-value (cell-value)
  (let ((text-value? (text-box-cv-text? cell-value)))
    (when text-value?
      (write-general-grid-view-text-value text-value?))))


;;; `write-integer-grid-view-cell-value'

(defun write-integer-grid-view-cell-value (cell-value)
  (let ((text-string
          (twith-output-to-text-string
            (twrite-fixnum (integer-cv-value cell-value)))))
    (write-general-grid-view-text-value text-string)
    (reclaim-text-string text-string)))


;;; `write-quantity-grid-view-cell-value'

(defun write-quantity-grid-view-cell-value (cell-value)
  (let* ((write-floats-accurately-p t)
         (text-string
          (twith-output-to-text-string
            (twrite (quantity-cv-value cell-value)))))
    (write-general-grid-view-text-value text-string)
    (reclaim-text-string text-string)))


;;; `write-check-box-grid-view-cell-value'

(defun write-check-box-grid-view-cell-value (cell-value)
  (let* ((selected-p (check-box-cv-checked-p cell-value))
         (text-value? (check-box-cv-label? cell-value)))
    ;; The C code doesn't like empty text values.  Not supplying a "T" at all
    ;; works fine, though.  -jv, 4/30/05
    (when (and (text-string-p text-value?)
               (>f (text-string-length text-value?) 0))
      (write-general-grid-view-text-value text-value?))
    (when selected-p
      ;; Hack!  We should be able to write "V0" here for not selected.  That
      ;; doesn't work, but omitting the value entirely does.  -jv, 3/25/05
      (twrite-char grid-token-value)
      (twrite-char #.%\1))))


;;; `write-combo-box-grid-view-cell-value'

(defun write-combo-box-grid-view-cell-value (cell-value)
  (let* ((sequence? (list-box-cv-list cell-value))
         (selected? (car (list-box-cv-selected cell-value)))
         (style? (list-box-cv-style? cell-value))
         (problem-with-selected-p (text-string-p selected?)))
    (cond
      ((and sequence? (listp sequence?))
       (twrite-char grid-token-cell-text)
       (if (text-string-p selected?)
           (twrite-string selected?)
           (if (>f (length sequence?) 0)
               (twrite-string (car sequence?))))
       (loop for element in sequence?
             do
         (unless (text-string-p element)
           ;; This should never happen.  If the user supplied a non-text, we
           ;; should have caught it while building the string.  -jv, 4/29/05
           (grid-view-combo-box-element-not-text-error element))
         (when (and problem-with-selected-p (text-string= element selected?))
           (setq problem-with-selected-p nil))
         (twrite-dialogs-secondary-element-separator)
         (twrite-string (evaluation-text-value element)))
       (when problem-with-selected-p
         (grid-view-combo-box-selected-error selected? sequence?))
       (twrite-dialogs-element-separator)
       (case style?
	 (dropdown
	  (tformat "~c~d" grid-token-style cbs-dropdown))
	 (dropdownlist
	  (tformat "~c~d" grid-token-style cbs-dropdownlist))
	 (color-picker			; Not a list-box-style the user can specify.
	  (tformat "~c~d" grid-token-style (logiorf cbs-dropdownlist g2-cbs-color-picker))))))))


;;; `write-calendar-grid-view-cell-value'

(defun write-calendar-grid-view-cell-value (cell-value)
  (let* ((year-value (calendar-cv-year cell-value))
         (month-value (calendar-cv-month cell-value))
         (date-value (calendar-cv-date cell-value)))
    (twrite-char grid-token-style)
    (twrite-fixnum (calendar-cv-format cell-value))
    ;; If the year is -1, that means the user did not supply any value, and
    ;; therefore wants the default.  To get that, don't write anything out.
    (unless (=f -1 year-value)
      (twrite-char grid-token-cell-text)
      (twrite-fixnum year-value)
      (twrite-char #.%\: )
      (twrite-fixnum month-value)
      (twrite-char #.%\: )
      (twrite-fixnum date-value)
      ;; C expects an hour, minute, and second; they're probably not necessary,
      ;; but for uniformity, supply them.
      (twrite-string ":0:0:0")
      (twrite-dialogs-element-separator))))


;;; `write-time-of-day-grid-view-cell-value'

(defun write-time-of-day-grid-view-cell-value (cell-value)
  (let* ((hour-value (time-of-day-cv-hour cell-value))
         (minute-value (time-of-day-cv-minute cell-value))
         (second-value (time-of-day-cv-second cell-value)))
    ;; If the hour is -1, that means the user did not supply any value, and
    ;; therefore wants the default.  To get that, don't write anything out.
    (unless (=f -1 hour-value)
      (twrite-char grid-token-cell-text)
      ;; C expects a year, month, and date, even though they will not really be
      ;; used; get them out of the way, to get on to the time.
      ;; 1970 triggers DST issue when timezone adjustment yields negative time.
      ;; So, pass 1971 as a default, it is ignored in the control anyway.
      ;; TODO: Maybe it is better to pass the month 2, or day 2, but leave 1970?
      ;; But it is ignored anyway, so no issues here.
      (twrite-string "1971:1:1:")
      (twrite-fixnum hour-value)
      (twrite-char #.%\: )
      (twrite-fixnum minute-value)
      (twrite-char #.%\: )
      (twrite-fixnum second-value)
      (twrite-dialogs-element-separator))))


;;; `write-duration-grid-view-cell-value'

(defun write-duration-grid-view-cell-value (cell-value)
  (let* ((weeks-value (duration-cv-weeks cell-value))
         (days-value (duration-cv-days cell-value))
         (hours-value (duration-cv-hours cell-value))
         (minutes-value (duration-cv-minutes cell-value))
         (seconds-value(duration-cv-seconds cell-value)))
    (twrite-char grid-token-cell-text)

    (when (<f weeks-value 100)
      (twrite "0"))
    (when (<f weeks-value 10)
      (twrite "0"))
    (twrite-fixnum weeks-value)
    (twrite-char #.%\: )

    (when (<f days-value 100)
      (twrite "0"))
    (when (<f days-value 10)
      (twrite "0"))
    (twrite-fixnum days-value)
    (twrite-char #.%\: )

    (when (<f hours-value 10)
      (twrite "0"))
    (twrite-fixnum hours-value)
    (twrite-char #.%\: )

    (when (<f minutes-value 10)
      (twrite "0"))
    (twrite-fixnum minutes-value)
    (twrite-char #.%\: )

    (when (<f seconds-value 10)
      (twrite "0"))
    (twrite-fixnum seconds-value)
    (twrite-dialogs-element-separator)))
    
(defun write-short-duration-grid-view-cell-value (cell-value)
  (let* ((hours-value (short-duration-cv-hours cell-value))
         (minutes-value (short-duration-cv-minutes cell-value))
         (seconds-value(short-duration-cv-seconds cell-value)))
    (twrite-char grid-token-cell-text)

    (when (<f hours-value 10)
      (twrite "0"))
    (twrite-fixnum hours-value)
    (twrite-char #.%\: )

    (when (<f minutes-value 10)
      (twrite "0"))
    (twrite-fixnum minutes-value)
    (twrite-char #.%\: )

    (when (<f seconds-value 10)
      (twrite "0"))
    (twrite-fixnum seconds-value)
    (twrite-dialogs-element-separator)))


;;; `write-image-grid-view-cell-value'

(defun write-image-grid-view-cell-value (cell-value)
  (twrite-char grid-token-image)
  (twrite-fixnum (image-cv-icon cell-value)))


;;; `write-spinner-grid-view-cell-value'

(defun write-spinner-grid-view-cell-value (cell-value)
  (tformat "~c" grid-token-cell-text)
  (twrite-spinner-value-as-string cell-value)
  (twrite-dialogs-element-separator))


;;; `write-fallback-grid-view-cell-value'

(defun-void write-fallback-grid-view-value (value)
  (let ((text (twith-output-to-text-string
                (tformat "~NF" (get-item-if-item-reference value)))))
    (write-general-grid-view-text-value text)
    (reclaim-text-string text)))


;;; `write-grid-view-cell-value' is sort of like evaluate-control-value-per-control-type.

(defun-void write-grid-view-cell-value (cell-value cell-type component)
  (declare (ignore component))
  (case cell-type
    (text-box
     (write-text-box-grid-view-cell-value cell-value))
    (integer
     (write-integer-grid-view-cell-value cell-value))
    (quantity
     (write-quantity-grid-view-cell-value cell-value))
    (check-box
     (write-check-box-grid-view-cell-value cell-value))
    ((combo-box color-picker)
     (write-combo-box-grid-view-cell-value cell-value))
    (calendar
     (write-calendar-grid-view-cell-value cell-value))
    (time-of-day
     (write-time-of-day-grid-view-cell-value cell-value))
    (duration
     (write-duration-grid-view-cell-value cell-value))
    (short-duration
     (write-short-duration-grid-view-cell-value cell-value))
    (image
     (write-image-grid-view-cell-value cell-value))
    (spinner
     (write-spinner-grid-view-cell-value cell-value))
    (t
     ;; If the user DID supply a cell-type, it has to be one of the supported
     ;; symbols.
     (grid-view-unknown-cell-type-error cell-type))))




;;; `write-grid-view-cell-data'

(defun write-grid-view-cell-data (gv row-num component)
  (loop with row = (nth row-num (lisp-grid-view-rows gv))
        for column-num from 0 below (lisp-grid-view-column-count gv)
        as cell = (managed-svref row column-num)
        as cell-selected-p = (grid-view-cell-selected-p gv row-num column-num)
        as cell-type? = (grid-view-cell-type? cell)
        as cell-value? = (grid-view-cell-value? cell)
        as read-only? = (grid-view-cell-read-only? cell)
        as is-multiline? = (grid-view-cell-is-multiline? cell)
        as text-color = (grid-view-cell-text-color? cell)
        as bg-color = (grid-view-cell-bg-color? cell)
        as alignment? = (grid-view-cell-alignment? cell)
        as bold? = (grid-view-cell-bold? cell)
        as ellipsis-button? = (grid-view-cell-ellipsis-button? cell)
        as text-font? = (grid-view-cell-text-font? cell)
        as text-font-size? = (grid-view-cell-text-font-size? cell)
        do
    (write-grid-view-cell-designation row-num column-num)
    (write-grid-view-colors text-color bg-color)
    ;; If we have an ellipsis-button, we need to switch types.
    (write-grid-view-cell-type cell-type? ellipsis-button?)
    (write-grid-view-cell-value cell-value? cell-type? component)
    (write-grid-view-read-only read-only?)
    (write-grid-view-cell-is-multiline is-multiline?)
    (write-grid-view-selected cell-selected-p)
    (write-grid-view-alignment alignment?)
    (write-grid-view-bold bold?)
    (write-grid-view-text-font text-font?)
    (write-grid-view-text-font-size text-font-size?)
    (write-grid-view-terminator gv)))


;;; `write-grid-view-column-data'

(defun write-grid-view-column-data (gv component)
  (declare (ignore component))
  (loop for elt in (lisp-grid-view-column-information gv)
        as column-num from 0
        as width? = (getf elt 'width)
        as column-header-text? = (getf elt 'text)
        as read-only? = (getf elt 'read-only)
        as is-multiline? = (getf elt 'is-multiline)
        as alignment? = (getf elt 'alignment)
        as bold? = (getf elt 'bold)
        as text-color? = (getf elt 'text-color)
        as bg-color? = (getf elt 'background-color)
        do
    (when (and (evaluation-text-p column-header-text?)
               (lisp-grid-view-use-column-header gv))
      (write-grid-view-column-header-text gv column-num column-header-text?))
    (when (or (evaluation-integer-p width?)
              (evaluation-truth-value-p read-only?)
              (evaluation-symbol-p alignment?))
      (write-grid-view-column-designation column-num)
      (write-grid-view-colors text-color? bg-color?)
      (write-grid-view-column-width width?)
      (write-grid-view-read-only read-only?)
      (write-grid-view-cell-is-multiline is-multiline?)
      (write-grid-view-alignment alignment?)
      (write-grid-view-bold bold?)
      (write-grid-view-terminator gv))))


;;; `create-lisp-grid-view'

(defun create-lisp-grid-view (row-count column-count sorting? use-row-header? use-column-header? support-font? end-data-delimiter)
  (let ((new-lisp-grid-view (make-lisp-grid-view)))
    (setf (lisp-grid-view-row-count new-lisp-grid-view) row-count)
    (setf (lisp-grid-view-column-count new-lisp-grid-view) column-count)
    (setf (lisp-grid-view-sorting new-lisp-grid-view)
          (and sorting? (evaluation-truth-value-is-true-p sorting?)))
    (setf (lisp-grid-view-use-row-header new-lisp-grid-view)
          (and use-row-header?
               (evaluation-truth-value-is-true-p use-row-header?)))
    (setf (lisp-grid-view-use-column-header new-lisp-grid-view)
          (and use-column-header?
               (evaluation-truth-value-is-true-p use-column-header?)))
    (setf (lisp-grid-view-support-font? new-lisp-grid-view) support-font?)
    (setf (lisp-grid-view-end-data-delimiter new-lisp-grid-view) end-data-delimiter)
    (loop for i from 0 below row-count
          as new-row = (allocate-managed-array column-count)
          do
      (loop for j from 0 below column-count do
        (setf (managed-svref new-row j) nil))
      ;; technically we're doing this out of order, but we're just adding
      ;; placeholders, so it couldn't matter less.
      (custom-dialog-push new-row (lisp-grid-view-rows new-lisp-grid-view)))
    new-lisp-grid-view))


;;; `verify-grid-view-g2-representation'

#+development
(defun verify-grid-view-g2-representation (dialog-component)
  (unless (lisp-grid-view-p (dialog-component-g2-representation? dialog-component))
    (cerror "Add one"
            "GRID-VIEW component has no (or incorrect) G2 representation")
    (setf (dialog-component-g2-representation? dialog-component)
          (make-lisp-grid-view))))


;;; `create-grid-view-cell'

(defun get-color-symbol-name-if-any (color?)
  (if (and color? (text-string-p color?))
      (color-name-symbol-from-text-string color?)
    color?))

(defun create-grid-view-cell (text-color? bg-color? cell-type? cell-value?
                              read-only? 
                              is-multiline? alignment? bold? ellipsis-button?
                              text-font text-font-size)
  (let ((new-cell (make-grid-view-cell)))
    (setf (grid-view-cell-text-color? new-cell) text-color?)
    (setf (grid-view-cell-bg-color? new-cell) bg-color?)
    (setf (grid-view-cell-type? new-cell) cell-type?)
    (setf (grid-view-cell-value? new-cell) cell-value?)
    (setf (grid-view-cell-read-only? new-cell) (coerce-to-evaluation-boolean read-only?))
    (setf (grid-view-cell-is-multiline? new-cell) (coerce-to-evaluation-boolean is-multiline?)) ; added by SoftServe
    (setf (grid-view-cell-alignment? new-cell) alignment?)
    (setf (grid-view-cell-bold? new-cell) (coerce-to-evaluation-boolean bold?))
    (setf (grid-view-cell-ellipsis-button? new-cell) (coerce-to-evaluation-boolean ellipsis-button?))
    (setf (grid-view-cell-text-font? new-cell) text-font)
    (setf (grid-view-cell-text-font-size? new-cell) text-font-size)
    new-cell))


(defun grid-view-replace-cell (lisp-grid-view row col new-cell)
  (let ((old-cell? (grid-view-ref lisp-grid-view row col)))
    (when old-cell?
      (reclaim-grid-view-cell old-cell?))
    (setf (grid-view-ref lisp-grid-view row col) new-cell)))

(defun row-column-in-evaluation-sequence-p (row cell evaluation-sequence?)
  (and evaluation-sequence?
       (loop for selected-cell being each evaluation-sequence-element of evaluation-sequence?
             as row-of-selected-cell = (evaluation-structure-slot selected-cell 'row)
             as column-of-selected-cell = (evaluation-structure-slot selected-cell 'column)
             when (and (=f row row-of-selected-cell)
                       (=f cell column-of-selected-cell))
               return t)))

;;; `build-text-box-grid-view-cell-value'

(defun build-text-box-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-text-box-cv))
         (text-value? (specified-or-inherited-structure-slot
                        cell-value 'text-value default-cell-value? nil)))
    (when (evaluation-text-p text-value?)
      (setf (text-box-cv-text? new-cell-value)
            (copy-text-string (evaluation-text-value text-value?))))
    new-cell-value))


;;; `build-integer-grid-view-cell-value'

(defun build-integer-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-integer-cv))
         (integer-value? (specified-or-inherited-structure-slot
                           cell-value 'current-value default-cell-value? 0)))
    (cond
      ((evaluation-integer-p integer-value?)
       (setf (integer-cv-value new-cell-value)
             (evaluation-integer-value integer-value?)))
      (t
       (grid-view-invalid-integer-error)))
    new-cell-value))


;;; `build-quantity-grid-view-cell-value'

(defun build-quantity-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-quantity-cv))
         (quantity-value? (specified-or-inherited-structure-slot
                            cell-value 'current-value default-cell-value? 0)))
    (cond
      ((evaluation-quantity-p quantity-value?)
       (setf (quantity-cv-value new-cell-value)
             (copy-evaluation-quantity quantity-value?)))
      (t
       ;; This is leaking the new quantity-cv structure. -dkuznick, 9/6/05
       (grid-view-invalid-quantity-error)))
    new-cell-value))


;;; `build-check-box-grid-view-cell-value'

(defun build-check-box-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-check-box-cv))
         (selected-p (specified-or-inherited-structure-slot cell-value 'selected
                                                            default-cell-value? nil))
         (text-value? (specified-or-inherited-structure-slot cell-value 'text-value
                                                             default-cell-value? nil)))
    (when (evaluation-text-p text-value?)
      (setf (check-box-cv-label? new-cell-value)
            (copy-text-string (evaluation-text-value text-value?))))
    (setf (check-box-cv-checked-p new-cell-value)
          (and (evaluation-truth-value-p selected-p)
               (evaluation-truth-value-is-true-p selected-p)))
    new-cell-value))


;;; `build-combo-box-grid-view-cell-value'

(defun build-combo-box-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-list-box-cv))
         (sequence? (specified-or-inherited-structure-slot cell-value
                                                           'text-sequence
                                                           default-cell-value? nil))
         (selected? (specified-or-inherited-structure-slot cell-value 'selected
                                                           default-cell-value? nil))
         (style? (specified-or-inherited-structure-slot cell-value 'list-box-style
							default-cell-value? nil))
         (problem-with-selected-p (evaluation-text-p selected?)))
    (cond
      ((evaluation-sequence-p sequence?)
       (setf (list-box-cv-list new-cell-value)
             (loop for element being each evaluation-sequence-element of sequence?
                   unless (evaluation-text-p element) do
                       (grid-view-combo-box-element-not-text-error element)
                   when (and problem-with-selected-p
                             (text-string= (evaluation-text-value selected?)
                                           element))
                             do
                       (setq problem-with-selected-p nil)
                   collect (copy-text-string (evaluation-text-value element))
                     using custom-dialog-cons))
       (when problem-with-selected-p
         (grid-view-combo-box-selected-error selected? sequence?))
       (setf (list-box-cv-selected new-cell-value)
             (and (not (evaluation-sequence-empty-p sequence?))
                  (custom-dialog-list
                    (copy-text-string
                      (evaluation-text-value
                        (if (evaluation-text-p selected?)
                            selected?
                            (evaluation-sequence-aref sequence? 0)))))))
       (when style?
	 (cond ((and (evaluation-symbol-p style?)
		     (memq (evaluation-symbol-symbol style?) '(dropdown dropdownlist)))
		(setf (list-box-cv-style? new-cell-value) (evaluation-symbol-symbol style?)))
	       (t
		(grid-view-combo-box-style-error style?))))))
    new-cell-value))


;;; `build-color-picker-grid-view-cell-value'

(defun build-color-picker-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-list-box-cv))
         (list-of-colors (determine-list-of-colors-for-color-picker
                           (specified-or-inherited-structure-slot
                             cell-value 'colors
                             default-cell-value? nil)))
         (selected-color?
           (specified-or-inherited-structure-slot cell-value 'selected default-cell-value? nil)))
    (setf (list-box-cv-selected new-cell-value)
            (cond
              ((null selected-color?)
               ;; perfectly acceptable; user does not need to specify an initially
               ;; selected value
               (if (car list-of-colors)
                   (custom-dialog-list
                     (copy-color-symbol-name (car list-of-colors)))))
              ((evaluation-symbol-p selected-color?)
               (if (memq selected-color? list-of-colors)
                   (custom-dialog-list
                     (copy-color-symbol-name selected-color?))
                   (invalid-color-selected-for-grid-view-color-picker-error
                     selected-color?)))
              (t
               (non-color-selected-for-grid-view-color-picker-error
                 selected-color?))))
    (setf (list-box-cv-list new-cell-value)
          (loop for color in list-of-colors
                as color-name = (copy-color-symbol-name color)
                collect color-name using custom-dialog-cons))

    ;; A special style of combo-box.
    (setf (list-box-cv-style? new-cell-value) 'color-picker)

    (reclaim-slot-value-list list-of-colors)
    new-cell-value))




;;; `build-calendar-grid-view-cell-value'

(defun build-calendar-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-calendar-cv))
         (year-value (specified-or-inherited-structure-slot
                       cell-value 'selected-year default-cell-value? -1))
         (month-value (specified-or-inherited-structure-slot
                        cell-value 'selected-month default-cell-value? -1))
         (date-value (specified-or-inherited-structure-slot
                       cell-value 'selected-date default-cell-value? -1))
         (requested-format? (specified-or-inherited-structure-slot
                              cell-value 'calendar-format default-cell-value? nil)))
    (unless (and (evaluation-integer-p year-value)
                 (evaluation-integer-p month-value)
                 (evaluation-integer-p date-value))
      (grid-view-calendar-non-integer-error))
    ;; If the user failed to supply any of them, that is fine.  We will supply
    ;; default values: the current date.
    (when (and (=f -1 (evaluation-integer-value year-value))
               (=f -1 (evaluation-integer-value month-value))
               (=f -1 (evaluation-integer-value date-value)))
      (multiple-value-bind (second minute hour date month year)
          (get-decoded-real-time)
        (declare (ignore second minute hour))
        (setq year-value (make-evaluation-integer year))
        (setq month-value (make-evaluation-integer month))
        (setq date-value (make-evaluation-integer date))))
    ;; if any one of them is provided, however, all of them must be provided,
    ;; and all of them must be valid
    (when (or (<f year-value 1970) (>f year-value 3000))
      (grid-view-calendar-invalid-year-error))
    (when (or (<f month-value 1) (>f month-value 12))
      (grid-view-calendar-invalid-month-error))
    (when (not (valid-date-for-month-p date-value month-value year-value))
      (grid-view-calendar-invalid-date-error))
    (setf (calendar-cv-year new-cell-value) year-value)
    (setf (calendar-cv-month new-cell-value) month-value)
    (setf (calendar-cv-date new-cell-value) date-value)
    (setf (calendar-cv-format new-cell-value)
          (case requested-format?
            (dd-mm-yyyy g2-dts-eu-format)
            (yyyy-mm-dd g2-dts-gov-format)
            (t g2-dts-us-format)))
    new-cell-value))


;;; `build-time-of-day-grid-view-cell-value'

(defun build-time-of-day-grid-view-cell-value (cell-value default-cell-value?)
  (let* ((new-cell-value (make-time-of-day-cv))
         (hour-value (specified-or-inherited-structure-slot
                       cell-value 'selected-hour default-cell-value? -1))
         (minute-value (specified-or-inherited-structure-slot
                         cell-value 'selected-minute default-cell-value? -1))
         (second-value (specified-or-inherited-structure-slot
                         cell-value 'selected-second default-cell-value? -1)))
    (unless (and (evaluation-integer-p hour-value)
                 (evaluation-integer-p minute-value)
                 (evaluation-integer-p second-value))
      (grid-view-time-of-day-non-integer-error))

    ;; If the user failed to supply any of them, that is fine.  We will supply
    ;; default values: the current time. We can't use the TWNG-side defaults
    ;; since TWNG does not send those to G2 unless the cell is edited.
    (when (and (=f -1 (evaluation-integer-value hour-value))
	       (=f -1 (evaluation-integer-value minute-value))
	       (=f -1 (evaluation-integer-value second-value)))
      (multiple-value-bind (second minute hour)
          (get-decoded-real-time)
        (setq hour-value (make-evaluation-integer hour))
        (setq minute-value (make-evaluation-integer minute))
        (setq second-value (make-evaluation-integer second))))

    ;; if any one of them is provided, however, all of them must be provided,
    ;; and all of them must be valid
    (when (or (<f hour-value 0) (>f hour-value 23))
      (grid-view-time-of-day-invalid-hour-error))
    (when (or (<f minute-value 0) (>f minute-value 59))
      (grid-view-time-of-day-invalid-minute-error))
    (when (or (<f second-value 0) (>f second-value 59))
      (grid-view-time-of-day-invalid-second-error))
    (setf (time-of-day-cv-hour new-cell-value) hour-value)
    (setf (time-of-day-cv-minute new-cell-value) minute-value)
    (setf (time-of-day-cv-second new-cell-value) second-value)
    new-cell-value))


;;; `build-duration-grid-view-cell-value'

(defun build-duration-grid-view-cell-value (cell-value default-cell-value?)
  ;; This is treating how to specify value a little differently from an
  ;; embedded calendar and time-of-day, which disallows "none"s, and forces you
  ;; to specify either none of the values or all of them.  Here, we will do
  ;; exactly what the standalone duration control does.  -dkuznick, 5/19/05

  (multiple-value-bind (weeks-value days-value hours-value minutes-value seconds-value)
      (get-fixnum-values-from-control-value cell-value default-cell-value?)
    (multiple-value-bind (weeks days hours minutes seconds)
        (make-duration-values-canonical
          weeks-value days-value hours-value minutes-value seconds-value)
      (let ((new-cell-value (make-duration-cv)))
        (setf (duration-cv-weeks new-cell-value) weeks)
        (setf (duration-cv-days new-cell-value) days)
        (setf (duration-cv-hours new-cell-value) hours)
        (setf (duration-cv-minutes new-cell-value) minutes)
        (setf (duration-cv-seconds new-cell-value) seconds)
        new-cell-value))))
        
(defun build-short-duration-grid-view-cell-value (cell-value default-cell-value?)
  (multiple-value-bind (hours-value minutes-value seconds-value)
      (get-fixnum-values-from-new-control-value cell-value default-cell-value?)
    (multiple-value-bind (hours minutes seconds)
        (make-short-duration-values-canonical
          hours-value minutes-value seconds-value)
      (let ((new-cell-value (make-short-duration-cv)))
        (setf (short-duration-cv-hours new-cell-value) hours)
        (setf (short-duration-cv-minutes new-cell-value) minutes)
        (setf (short-duration-cv-seconds new-cell-value) seconds)
        new-cell-value))))


;;; The function `send-native-icon-for-grid-view-cell' sends a native icon to be
;;; used in a cell of a grid-view. We send both 16x16 and 32x32 icons.

(defun send-native-icon-for-grid-view-cell (cell-value default-cell-value? gensym-window)
  (let ((icon-designation? (specified-or-inherited-structure-slot
                             cell-value 'icon default-cell-value? nil)))
    (when (valid-icon-designation-p icon-designation?)
      (values (send-native-icon gensym-window icon-designation? '(small large))
	      icon-designation?))))

(defun build-image-grid-view-cell-value (cell-value default-cell-value? gensym-window)
  (multiple-value-bind (icon? icon-designation)
      (send-native-icon-for-grid-view-cell
        cell-value default-cell-value? gensym-window)
    (if icon?
        (let ((new-cell-value (make-image-cv)))        ; Is this ever reclaimed?
          (setf (image-cv-icon new-cell-value) icon?)
          ;; We need to keep track of the icon-designation because when we get
          ;; the icon handle back from a callback, we have no way to map it to
          ;; the icon-designation. -dkuznick, 8/31/05
          (setf (image-cv-icon-designation new-cell-value) (copy-icon-designation icon-designation))
          new-cell-value)
        ;; We need to throw an error
        (dialog-image-control-value-error "CELL-VALUE" "in a grid-view"))))


;;; `build-grid-view-cell-value-1' is sort of like evaluate-control-value-per-control-type.
;;; Cell-value and default-cell-value? are both evaluation values here.

(defun build-grid-view-cell-value-1 (cell-type cell-value default-cell-value? gensym-window) ; May stack-error
  (case cell-type
    (text-box
     (build-text-box-grid-view-cell-value cell-value default-cell-value?))
    (integer
     (build-integer-grid-view-cell-value cell-value default-cell-value?))
    (quantity
     (build-quantity-grid-view-cell-value cell-value default-cell-value?))
    (check-box
     (build-check-box-grid-view-cell-value cell-value default-cell-value?))
    (duration
     (build-duration-grid-view-cell-value cell-value default-cell-value?))
    (short-duration
     (build-short-duration-grid-view-cell-value cell-value default-cell-value?))
    (calendar
     (build-calendar-grid-view-cell-value cell-value default-cell-value?))
    (time-of-day
     (build-time-of-day-grid-view-cell-value cell-value default-cell-value?))
    (combo-box
     (build-combo-box-grid-view-cell-value cell-value default-cell-value?))
    (color-picker
     (build-color-picker-grid-view-cell-value cell-value default-cell-value?))
    (image
     (build-image-grid-view-cell-value cell-value default-cell-value? gensym-window))
    (spinner
     (build-spinner-grid-view-cell-value cell-value default-cell-value?))
    (t
     ;; We don't get here just because the cell-type was omitted.  We checked
     ;; for that earlier on, and supplied TEXT-BOX if the user didn't supply a
     ;; type explicitly.  We only get here if something explicit was provided
     ;; which we don't recognize.  -jv, 4/28/05
     (grid-view-unknown-cell-type-error cell-type))))


;;; `build-grid-view-cell-value'

(defun build-grid-view-cell-value (cell cell-type default-cell-value? gensym-window) ; May stack-error
  (let ((found-cell-value?
          (evaluation-structure-slot cell 'cell-value default-cell-value?)))
    ;; Why is default-cell-value? being used both above and below here?
    (cond
      ((null found-cell-value?)
       (let* ((temp-cell-value
                (allocate-evaluation-structure nil))
              (rval (build-grid-view-cell-value-1 cell-type
                                                  temp-cell-value
                                                  default-cell-value?
                                                  gensym-window)))
         (reclaim-evaluation-structure temp-cell-value)
         rval))
      ((evaluation-structure-p found-cell-value?)
       (build-grid-view-cell-value-1 cell-type
                                     found-cell-value?
                                     default-cell-value?
                                     gensym-window))
      (t
       ;; If the user DID supply a cell-value, it has to be a structure.  If not,
       ;; we throw an error.
       (grid-view-cell-value-not-a-structure-error)))))


;;; The function `build-grid-view-cell-data' is used when initially creating the
;;; grid-view. It is not used when making updates.

;; TODO: use build-grid-view-cell for much of this
;; cf: add-or-replace-cell-in-internal-grid-view-with-defaulting
(defun build-grid-view-cell-data (component row-num cells columns selected-cells?)
  (let* ((gv (dialog-component-g2-representation? component))
         (support-font? (lisp-grid-view-support-font? gv)))
    #+development
    (unless (lisp-grid-view-p gv)
      (cerror "Add one"
              "GRID-VIEW component has no (or incorrect) G2 representation")
      (setf (dialog-component-g2-representation? component)
            (make-lisp-grid-view))
      (setq gv (dialog-component-g2-representation? component)))
    (loop for cell being each evaluation-sequence-element of cells
          with gensym-window = (gensym-window-of-dialog-component component)
          as column-num from 0
          as this-column = (evaluation-sequence-aref columns column-num)
          as default-cell-type? = (evaluation-structure-slot this-column 'default-cell-type 'text-box)
          as default-cell-value? = (evaluation-structure-slot this-column 'default-cell-value)
          as default-read-only? = (evaluation-structure-slot this-column 'read-only)
          as default-is-multiline? = (evaluation-structure-slot this-column 'is-multiline) ; added by SoftServe
          as default-text-color? = (evaluation-structure-slot this-column 'text-color)
          as default-bg-color? = (evaluation-structure-slot this-column 'background-color)
          as default-alignment? = (evaluation-structure-slot this-column 'alignment)
          as default-bold? = (evaluation-structure-slot this-column 'bold)
          as default-ellipsis-button? = (evaluation-structure-slot this-column 'ellipsis-button)
          as read-only? = (evaluation-structure-slot cell 'read-only default-read-only?)
          as is-multiline? = (evaluation-structure-slot cell 'is-multiline default-is-multiline?) ; added by SoftServe
          as alignment? = (evaluation-structure-slot cell 'alignment default-alignment?)
          as bold? = (evaluation-structure-slot cell 'bold default-bold?)
          as cell-type = (evaluation-structure-slot cell 'cell-type default-cell-type?)
          as ellipsis-button? = (and (eq cell-type 'text-box)
                                     (evaluation-structure-slot cell
                                       'ellipsis-button
                                       default-ellipsis-button?))
          as text-font? = (when support-font?
                            (evaluation-structure-slot cell 'text-font nil))
          as text-font-size? = (when support-font?
                                 (evaluation-structure-slot cell 'text-font-size nil))
          as new-cell-value = (build-grid-view-cell-value cell cell-type default-cell-value? gensym-window)
          as new-cell = (create-grid-view-cell
                          (or (evaluation-structure-slot cell 'text-color nil)
                              (get-color-symbol-name-if-any (evaluation-structure-slot cell 'text-font-color nil))
                              default-text-color?)
                          (or (evaluation-structure-slot cell 'background-color nil)
                              (get-color-symbol-name-if-any (evaluation-structure-slot cell 'control-background-color))
                              default-bg-color?)
                          cell-type new-cell-value
                          ;; the default for read-only is supposed to
                          ;; be false, but it seems to be true in the
                          ;; C code, so if the user didn't specify, on
                          ;; either a column or cell level, then we
                          ;; will explicitly specify false.
                          read-only?
                          is-multiline? ; added by SoftServe
                          alignment?
                          bold?
                          ellipsis-button?
                          text-font?
                          text-font-size?)
        do
      (grid-view-replace-cell gv row-num column-num new-cell)
      (when (row-column-in-evaluation-sequence-p row-num column-num selected-cells?)
        (grid-view-select-cell gv row-num column-num)))))


;; evaluation value -> internal value
(defun build-grid-view-cell (gv row column cell-structure?) ; May stack-error
  (let ((cell (make-grid-view-cell)))
    (when cell-structure?
      (loop for (property . evalue) being each evaluation-structure-pair of cell-structure? doing
        (set-grid-view-cell-property gv cell row column property evalue)))
    cell))


;;; `dialog-component-too-large-stack-error'

(defun dialog-component-too-large-stack-error (lisp-struct)
  (let* ((dialog (dialog-component-parent-dialog lisp-struct))
         (component-type (map-control-type-fixnum-to-symbol
                           (dialog-component-type lisp-struct)))
         (grid-view-p (eq 'grid-view component-type)))

    ;; We shouldn't have to, and probably don't have to, reclaim the string
    ;; here.  But it does no harm, and it's a particularly large value that
    ;; we should take no chances of leaking.  -jv, 10/21/05
    (reclaim-text-string (dialog-component-value? lisp-struct))
    (setf (dialog-component-value? lisp-struct) nil)

    (write-dialogs-stack-error
      dialog
      (tformat "The ~NA component ~NA of the dialog specification was too ~
                large.  Please make a smaller ~A."
               component-type
               (dialog-component-kb-id lisp-struct)
               (if grid-view-p
                 "initial specification, possibly augmenting the grid-view via g2-ui-grid-view-insert-row after the grid-view has posted."
                 "specification.")))))


;;; `build-grid-view-row-data'

(defun build-grid-view-row-data (component rows columns selected-cells?)
  (loop with gv = (dialog-component-g2-representation? component)
        for elt being each evaluation-sequence-element of rows
        as row-num from 0
        as height? = (evaluation-structure-slot elt 'height)
        as row-header-text? = (evaluation-structure-slot elt 'text-value)
        as text-color? = (evaluation-structure-slot elt 'text-color)
        as bg-color? = (evaluation-structure-slot elt 'background-color)
        as cells = (evaluation-structure-slot elt 'cell-settings)
        as this-row-info = (custom-dialog-list
                             'text (copy-if-evaluation-value row-header-text?)
                             'height height?
                             'text-color text-color?
                             'background-color bg-color?)
        do
    ;; Need type check on cells? -dkuznick, 3/24/05
    (build-grid-view-cell-data component row-num cells columns selected-cells?)
        as this-row-string = (twith-output-to-text-string
                               (when (and (evaluation-text-p row-header-text?)
                                          (lisp-grid-view-use-row-header gv))
                                 (write-grid-view-row-header-text gv row-num row-header-text?))
                               (when (or (evaluation-integer-p height?) text-color? bg-color?)
                                 (write-grid-view-row-designation row-num)
                                 (write-grid-view-colors text-color? bg-color?)
                                 (write-grid-view-row-height height?)
                                 (write-grid-view-terminator gv))
                               (write-grid-view-cell-data gv row-num component))
        when (>f (text-string-length this-row-string)
                 maximum-length-for-user-text-strings) do
            (dialog-component-too-large-stack-error component)
        collect this-row-info into row-information using custom-dialog-cons
        collect this-row-string into row-strings using custom-dialog-cons
        finally
          (setf (lisp-grid-view-row-information gv) row-information)
          (setf (lisp-grid-view-row-strings gv) row-strings)))


;;; `add-grid-view-to-dialog' - used for TWNGs 8.2r0 and newer.  Immediately
;;; after we've added the component, this function gets called, which sends
;;; over the row data as strings, one string (and one foreign function call)
;;; per row.  Note, we do not check the size of the strings here, because we
;;; already did that when building up lisp-grid-view-row-strings.

(defun add-grid-view-to-dialog (component dialog)
  (loop with dialog-handle = (dynamic-dialog-handle dialog)
        with control-id = (dialog-component-internal-id component)
        with gv = (dialog-component-g2-representation? component)
        for row-string in (lisp-grid-view-row-strings gv)
        do
    #+echo-dialog-send
    (dbg-output-grid-view-cells dialog-handle control-id row-string)
    (send-icp-specify-grid-view-cells dialog-handle control-id row-string)))



;;; The function `build-grid-view-column-data' computes
;;; lisp-grid-view-column-information from given columns structure, an
;;; evaluation value. Columns is an evaluation-value here.

;;; NOTE: The internal value is a mixture of lisp and evaluation values! It is a
;;; list of plists, some of whose property values are ordinary lisp values (eg,
;;; alignment) and some of which are evaluation values (eg, cell-value).

(defun build-grid-view-column-data (component columns)
  (let ((gv (dialog-component-g2-representation? component)))
    (setf (lisp-grid-view-column-information gv)
          (loop for elt being each evaluation-sequence-element of columns
                collect (build-grid-view-column-data-1 elt)
                  using custom-dialog-cons))))

;; evaluation value -> internal value (see above)
(defun build-grid-view-column-data-1 (column-structure)
  (loop for (attribute . property) in grid-view-column-properties
        as evalue? = (evaluation-structure-slot column-structure attribute)
        when evalue?
          collect property using custom-dialog-cons and
          collect (build-grid-view-column-data-2 property evalue?) using custom-dialog-cons))

;; evaluation value -> internal value (see above)
(defun build-grid-view-column-data-2 (property evalue)
  ;; Technically, we should be copying all values before putting them into
  ;; this-column-info.  This is relying on knowledge of which evaluation-values
  ;; are boxed. -dkuznick, 12/9/05
  (case property
    ((text cell-value)
     (copy-if-evaluation-value evalue))
    ((read-only is-multiline ellipsis-button bold)
     (copy-if-evaluation-value evalue))
    (t
     ;; Presumably, the evalue at this point does not actually need unboxing.
     (unbox-evaluation-value evalue))))


;;; `grid-view-evaluate-control-value' is the workhorse for building up our
;;; internal data structure, from the user-supplied spec, and the strings we
;;; will send to C.  The top-level and per-column data is stored in a string
;;; as the component-value (the initial value sent to C), and the row data is
;;; stored separately, in lisp-grid-view-row-strings, to be sent separately.

(defun grid-view-evaluate-control-value (value dialog-component)
  (validate-grid-control-value-is-properly-formed value)
  ;; After this validation, we make a lot of assumptions.
  (let* ((gensym-window (gensym-window-of-dialog-component dialog-component))
         (support-font? (remote-side-supports-font-in-grid-view-p
                          (icp-socket-for-gensym-window? gensym-window)))
         (rows (evaluation-structure-slot value 'rows))
         (columns (evaluation-structure-slot value 'columns))
         (row-count (evaluation-sequence-length rows))
         (column-count (evaluation-sequence-length columns))
         (selected-cells? (evaluation-structure-slot value 'selected-cells))
         (sorting? (evaluation-structure-slot value 'sorting))
         (background-color? (evaluation-structure-slot value 'background-color))
         ;; These next two default to true.
         (use-row-header? (evaluation-structure-slot value 'use-row-header evaluation-true-value))
         (use-column-header? (evaluation-structure-slot value 'use-column-header evaluation-true-value))
         (new-lisp-grid-view
           (create-lisp-grid-view row-count column-count sorting? use-row-header? use-column-header?
                                  support-font? (grid-token-end-data gensym-window))))

    (setf (lisp-grid-view-background-color? new-lisp-grid-view) background-color?)

    (setf (dialog-component-g2-representation? dialog-component) new-lisp-grid-view)
    (build-grid-view-column-data dialog-component columns)
    (build-grid-view-row-data dialog-component rows columns selected-cells?)

    (twith-output-to-text-string
      (write-grid-view-global-info new-lisp-grid-view dialog-component)
      (write-grid-view-column-data new-lisp-grid-view dialog-component))))


;;; `make-text-box-cell-value-eval-list'

(defun make-text-box-cell-value-eval-list (cell-value?)
  (let ((text-value? (text-box-cv-text? cell-value?)))
    (eval-list 'text-value
	       (make-evaluation-text
		 (if (text-string-p text-value?)
		     text-value?
		     #w"")))))


;;; `make-integer-cell-value-eval-list'

(defun make-integer-cell-value-eval-list (cell-value?)
  (let ((integer-value? (integer-cv-value cell-value?)))
    (if (fixnump integer-value?)
        (eval-list 'current-value
                   (make-evaluation-integer integer-value?))
        (eval-list))))


;;; `make-quantity-cell-value-eval-list'

(defun make-quantity-cell-value-eval-list (cell-value?)
  (eval-list 'current-value
             (copy-evaluation-quantity (quantity-cv-value cell-value?))))


;;; `make-check-box-cell-value-eval-list'

(defun make-check-box-cell-value-eval-list (cell-value?)
  (let* ((text-value? (check-box-cv-label? cell-value?))
         (checked-p (check-box-cv-checked-p cell-value?))
         (rval
           (eval-list 'selected (make-evaluation-truth-value
                                  (if checked-p
                                      truth falsity)))))
    (when (text-string-p text-value?)
      (setq rval
            (nconc
              (eval-list
                'text-value
                (make-evaluation-text text-value?))
              rval)))
    rval))


;;; `make-combo-box-cell-value-eval-list'

(defun make-combo-box-cell-value-eval-list (cell-value?)
  (let ((text-sequence? (list-box-cv-list cell-value?))
        (selected-value? (car (list-box-cv-selected cell-value?)))
	(style? (list-box-cv-style? cell-value?)))
    (nconc
      (eval-list
	'text-sequence
	(allocate-evaluation-sequence
	  (loop for element in text-sequence?
		collect (make-evaluation-text element) using eval-cons)))
      (if style?
	  (eval-list 'list-box-style (make-evaluation-symbol style?)))
      (if (text-string-p selected-value?)
	  (eval-list 'selected (make-evaluation-text selected-value?))))))


;;; `make-color-picker-cell-value-eval-list'

(defun make-color-picker-cell-value-eval-list (cell-value?)
  (let ((selected-value? (car (list-box-cv-selected cell-value?))))
    (if (text-string-p selected-value?)
        (eval-list 'selected
                   (color-name-symbol-from-text-string selected-value?))
        (eval-list))))


;;; `make-calendar-cell-value-eval-list'

(defun make-calendar-cell-value-eval-list (cell-value?)
  (let ((cv-year (calendar-cv-year cell-value?))
        (cv-month (calendar-cv-month cell-value?))
        (cv-date (calendar-cv-date cell-value?))
        (cv-format (calendar-cv-format cell-value?)))
    (eval-list 'selected-year cv-year
               'selected-month cv-month
               'selected-date cv-date
               'calendar-format
               (if (eql cv-format g2-dts-eu-format)
                   'dd-mm-yyyy
                   (if (eql cv-format g2-dts-gov-format)
                       'yyyy-mm-dd
                       'mm-dd-yyyy)))))


;;; `make-time-of-day-cell-value-eval-list'

(defun make-time-of-day-cell-value-eval-list (cell-value?)
  (let ((cv-hour (time-of-day-cv-hour cell-value?))
        (cv-minute (time-of-day-cv-minute cell-value?))
        (cv-second (time-of-day-cv-second cell-value?)))
    (eval-list 'selected-hour cv-hour
               'selected-minute cv-minute
               'selected-second cv-second)))


;;; `make-duration-cell-value-eval-list'

(defun make-duration-cell-value-eval-list (cell-value?)
  (let ((cv-weeks (duration-cv-weeks cell-value?))
        (cv-days (duration-cv-days cell-value?))
        (cv-hours (duration-cv-hours cell-value?))
        (cv-minutes (duration-cv-minutes cell-value?))
        (cv-seconds (duration-cv-seconds cell-value?)))
  (eval-list 'number-of-weeks cv-weeks
             'number-of-days cv-days
             'number-of-hours cv-hours
             'number-of-minutes cv-minutes
             'number-of-seconds cv-seconds)))
             
(defun make-short-duration-cell-value-eval-list (cell-value?)
  (let ((cv-hours (short-duration-cv-hours cell-value?))
        (cv-minutes (short-duration-cv-minutes cell-value?))
        (cv-seconds (short-duration-cv-seconds cell-value?)))
  (eval-list 'number-of-hours cv-hours
             'number-of-minutes cv-minutes
             'number-of-seconds cv-seconds)))


;;; `make-image-cell-value-eval-list'

(defun make-image-cell-value-eval-list (cell-value?)
  ;; We have no way to take the handle and get back the symbol.
  (eval-list 'icon (make-evaluation-value-from-lisp-value (image-cv-icon-designation cell-value?))))


;;; `make-spinner-cell-value-eval-list'

(defun make-spinner-cell-value-eval-list (cell-value)
  (eval-list 'current-value
             (copy-evaluation-value (spinner-cv-current-value cell-value))
             'low-value
             (copy-evaluation-value (spinner-cv-low-value cell-value))
             'high-value
             (copy-evaluation-value (spinner-cv-high-value cell-value))
             'increment
             (copy-evaluation-value (spinner-cv-increment cell-value))))


;;; `make-cell-value-eval-list'

(defun make-cell-value-eval-list (cell-type cell-value?)
  (case cell-type
    (text-box
     (make-text-box-cell-value-eval-list cell-value?))
    (integer
     (make-integer-cell-value-eval-list cell-value?))
    (quantity
     (make-quantity-cell-value-eval-list cell-value?))
    (check-box
     (make-check-box-cell-value-eval-list cell-value?))
    (combo-box
     (make-combo-box-cell-value-eval-list cell-value?))
    (color-picker
     (make-color-picker-cell-value-eval-list cell-value?))
    (calendar
     (make-calendar-cell-value-eval-list cell-value?))
    (time-of-day
     (make-time-of-day-cell-value-eval-list cell-value?))
    (duration
     (make-duration-cell-value-eval-list cell-value?))
    (short-duration
     (make-short-duration-cell-value-eval-list cell-value?))
    (image
     (make-image-cell-value-eval-list cell-value?))
    (spinner
     (make-spinner-cell-value-eval-list cell-value?))
    (t
     (grid-view-unknown-cell-type-error cell-type))))


;;; `make-cell-value-struct'

(defun make-cell-value-struct (cell-type? cell-value?)
  (allocate-evaluation-structure
    (and cell-type?
         (make-cell-value-eval-list cell-type? cell-value?))))

(defun make-evaluation-value-for-cell-property (property cell-type cell-value)
  (case property
    (cell-value
     (make-cell-value-struct cell-type cell-value))
    (t
     (make-evaluation-value-from-lisp-value cell-value))))

;;; `make-cell-setting'

;; internal value -> evaluation value
(defun make-cell-setting (gv cell row column column-info)
  (allocate-evaluation-structure
    (loop with cell-type = (get-grid-view-cell-property gv cell row column 'cell-type column-info t)
          for property in grid-view-cell-properties
          as value? = (get-grid-view-cell-property gv cell row column property column-info)
          when value?
            collect property using eval-cons and
            collect (make-evaluation-value-for-cell-property property cell-type value?)
              using eval-cons)))


;;; `make-cell-settings'

;; internal value -> evaluation value
(defun make-cell-settings (gv row-num row)
  (allocate-evaluation-sequence
    (loop with cell-count = (managed-array-length row)
          for i from 0 below cell-count
          for column-info in (lisp-grid-view-column-information gv)
          collect (make-cell-setting gv (managed-svref row i) row-num i column-info)
            using eval-cons)))


;;; `grid-view-row-eval-list'

(defun grid-view-row-eval-list (gv row-num row-info row)
  (let* ((row-header (getf row-info 'text))
         (cell-settings (make-cell-settings gv row-num row))
         (row-list '()))
    (setq row-list
          (eval-list 'cell-settings cell-settings))
    (when (text-string-p row-header)
      (setq row-list (eval-cons 'text-value
                                (eval-cons (make-evaluation-text row-header) row-list))))
    row-list))


;;; `build-grid-view-rows'

(defun build-grid-view-rows (gv)
  (allocate-evaluation-sequence
    (loop for row-info in (lisp-grid-view-row-information gv)
          as row-num from 0
          as row = (nth row-num (lisp-grid-view-rows gv))
          as row-list = (grid-view-row-eval-list gv row-num row-info row)
          collect
          (allocate-evaluation-structure row-list)
            using eval-cons)))


;;; `build-grid-view-selected-cells'

(defun build-grid-view-selected-cells (gv)
  (allocate-evaluation-sequence
    (loop for (row . col) in (lisp-grid-view-selected-cells gv)
          collect (allocate-evaluation-structure-inline
                    'row row 'column col)
            using eval-cons)))


;;; `grid-view-currently-selected-cells'

(defun grid-view-currently-selected-cells (lisp-struct)
  (build-grid-view-selected-cells
    (dialog-component-g2-representation? lisp-struct)))


;;; `build-grid-view-notification'

(defun build-grid-view-notification (gv)
  (if (lisp-grid-view-notification? gv)
      (allocate-evaluation-structure-inline
        'row
        (car (lisp-grid-view-notification? gv))
        'column
        (cdr (lisp-grid-view-notification? gv))
        'reason 'ellipsis-button)))

;; internal value -> evaluation value
(defun build-grid-view-column (column)
  (allocate-evaluation-structure
    (loop for (attribute . property) in grid-view-column-properties-returned-to-user
          as value? = (getf column property)
          when value?
            collect attribute using eval-cons and
	    ;; NOTE: This call only just happens to work. Column property values
	    ;; are actually evaluation values, not lisp values. But the only
	    ;; type used for which there is any difference is truth-value, which
	    ;; make-evaluation-value-from-lisp-value handles. Actually, that
	    ;; function is very poorly named. -fmw, 7/10/07
            collect (make-evaluation-value-from-lisp-value value?) using eval-cons)))

;; internal value -> evaluation value
(defun build-grid-view-columns (gv)
  (allocate-evaluation-sequence
    (loop for column in (lisp-grid-view-column-information gv)
          collect (build-grid-view-column column)
            using eval-cons)))


;;; `build-evaluation-structure-for-grid-view-callback'

(defun build-evaluation-structure-for-grid-view-callback (gv)
  (let ((columns (build-grid-view-columns gv))
        (rows (build-grid-view-rows gv))
        (selected-cells (build-grid-view-selected-cells gv))
        (notification? (build-grid-view-notification gv)))
    (allocate-evaluation-structure
      (if notification?
          (eval-list 'columns columns
                     'rows rows
                     'selected-cells selected-cells
                     'notification notification?)
          (eval-list 'columns columns
                     'rows rows
                     'selected-cells selected-cells)))))


;;; `grid-view-updated-control-value'

(defun grid-view-updated-control-value (component)
  (let ((incoming-string (dialog-component-incoming-value? component)))
    (grid-view-apply-updates
      (dialog-component-g2-representation? component)
      incoming-string)
    (build-evaluation-structure-for-grid-view-callback
      (dialog-component-g2-representation? component))))




;;; `manage-grid-view'

(defun manage-grid-view (gensym-window dialog-id control-id actions)
  (cond ((icp-window-p gensym-window)
         (with-icp-window (gensym-window)
           (send-icp-manage-grid-view dialog-id control-id actions)))
        (t
         (manage-grid-view-1 dialog-id control-id actions))))

;;; `manage-grid-view-get-value-request'

(defun manage-grid-view-get-value-request (gensym-window dialog-id control-id var actions)
  (cond ((icp-window-p gensym-window)
         (with-icp-window (gensym-window)
           (send-icp-manage-grid-view-get-value dialog-id control-id actions
                                                (name-or-names-for-frame var))))
        (t
         (put-evaluation-value var
                               (manage-grid-view-1 dialog-id control-id actions)
                               'never nil nil))))

;;; `lookup-dialog-given-handle'

(defun lookup-dialog-given-handle (gensym-window handle)
  (let ((dialog-view? (find-native-window gensym-window handle 'g2-dialog-view)))
    (when dialog-view?
      (dialog-view-custom-dialog? dialog-view?))))


;;; `lookup-component-given-component-kb-id'

(defun lookup-component-given-component-kb-id (component-id dialog)
  (loop for component in (dynamic-dialog-components dialog)
        when (eql component-id (dialog-component-kb-id component))
          return component))


;;; `%manage-grid-view' - purely a helper function for the system procedures.
;;; Action-or-actions must be something that reclaim-unboxed-evaluation-value
;;; can reclaim.

(defun %manage-grid-view (gensym-window dialog-id kb-control-id action-or-actions)
  (let* ((dialog (lookup-dialog-given-handle gensym-window dialog-id))
         (control (lookup-component-given-component-kb-id kb-control-id dialog))
         (control-id (dialog-component-internal-id control))
         (actions (if (consp (car action-or-actions))
                      action-or-actions
                      (gensym-list action-or-actions))))
    (manage-grid-view gensym-window dialog-id control-id actions)
    (reclaim-unboxed-evaluation-value actions)
    control-id))

(defun %manage-grid-view-get-value-request
    (gensym-window dialog-id kb-control-id scrollbar-position-var action-or-actions)
  (let* ((dialog (lookup-dialog-given-handle gensym-window dialog-id))
         (control (lookup-component-given-component-kb-id kb-control-id dialog))
         (control-id (dialog-component-internal-id control))
         (actions (if (consp (car action-or-actions))
                      action-or-actions
                      (gensym-list action-or-actions))))
    (manage-grid-view-get-value-request gensym-window dialog-id control-id scrollbar-position-var actions)
    (reclaim-unboxed-evaluation-value actions)
    control-id))

;;; `insert-grid-view-row-at-position'

(defun insert-grid-view-row-at-position (gv row-number row-structure)
  (let* ((column-count (lisp-grid-view-column-count gv))
         (new-row-label? (evaluation-structure-slot row-structure 'text-value))
         (new-row-height? (evaluation-structure-slot row-structure 'height))
         (new-row-integer-label? (evaluation-structure-slot row-structure 'integer))
         (new-row-text-color? (evaluation-structure-slot row-structure 'text-color))
         (new-row-bg-color? (evaluation-structure-slot row-structure 'background-color))
         ;; Should be abstracted.
         (new-row-info (custom-dialog-list 'text (copy-if-evaluation-value
                                                   new-row-label?)
                                           'height new-row-height?
                                           'integer-label new-row-integer-label?
                                           'text-color new-row-text-color?
                                           'background-color new-row-bg-color?))
         (new-row (allocate-managed-array column-count)))
    (cond
      ((=f 0 row-number)
       (custom-dialog-push new-row-info (lisp-grid-view-row-information gv))
       (custom-dialog-push new-row (lisp-grid-view-rows gv)))
      (t
       (loop for index from 0
             as row-information-trailer = nil then rest-row-information
             ;; can't use "on" as that could exit the loop early if we are
             ;; trying to stick a row on the end. -dkuznick, 5/2/05
             as rest-row-information = (lisp-grid-view-row-information gv)
                                     then (cdr rest-row-information)
             as rest-rows-trailer = nil then rest-rows
             as rest-rows = (lisp-grid-view-rows gv) then (cdr rest-rows)
             when (=f index row-number)
               do
                 (setf (cdr row-information-trailer)
                       (custom-dialog-cons new-row-info rest-row-information))
                 (setf (cdr rest-rows-trailer)
                       (custom-dialog-cons new-row rest-rows))
                 (return))))))


;; cf: build-grid-view-cell-data
(defun create-grid-view-cell-with-defaulting (cell-ev column-info support-font?) ; May stack-error
  (let* ((default-cell-type (or (getf column-info 'cell-type) 'text-box))
         (default-cell-value? (getf column-info 'cell-value))
         (default-read-only? (getf column-info 'read-only))
         (default-is-multiline? (getf column-info 'is-multiline)) ; added by SoftServe
         (default-text-color? (getf column-info 'text-color))
         (default-bg-color? (getf column-info 'background-color))
         (default-alignment? (getf column-info 'alignment))
         (default-bold? (getf column-info 'bold))
         (default-ellipsis-button? (getf column-info 'ellipsis-button))
         ;; This is suspect as I believe default-read-only? is t/nil.  So if
         ;; it's t, it will not get interpreted correctly as it's expected to
         ;; be an evaluation-truth-value or NIL below.  -dkuznick, 12/15/05
         (new-cell-read-only?
           (evaluation-structure-slot cell-ev 'read-only default-read-only?))
         ;; added by SoftServe
         (new-cell-is-multiline?
           (evaluation-structure-slot cell-ev 'is-multiline default-is-multiline?))
         ;; end of SoftServe changes
         (new-cell-type (evaluation-structure-slot cell-ev 'cell-type default-cell-type))
         (new-cell-text-color
           (or (evaluation-structure-slot cell-ev 'text-color nil)
               (get-color-symbol-name-if-any (evaluation-structure-slot cell-ev 'text-font-color nil))
               default-text-color?))
         (new-cell-background-color
           (or (evaluation-structure-slot cell-ev 'background-color nil)
               (get-color-symbol-name-if-any (evaluation-structure-slot cell-ev 'control-background-color nil))
               default-bg-color?))
         (new-cell-alignment?
           (evaluation-structure-slot cell-ev 'alignment default-alignment?))
         (new-cell-bold?
         (evaluation-structure-slot cell-ev 'bold default-bold?))
         ;; Same problem as read-only? above.  -dkuznick, 12/15/05
         (new-cell-ellipsis-button?
           (evaluation-structure-slot cell-ev 'ellipsis-button default-ellipsis-button?))
         (new-cell-text-font?
           (when support-font?
             (evaluation-structure-slot cell-ev 'text-font nil)))
         (new-cell-text-font-size?
           (when support-font?
             (evaluation-structure-slot cell-ev 'text-font-size nil)))
         (new-cell-value
           (build-grid-view-cell-value cell-ev              ; May stack-error
                                       new-cell-type
                                       default-cell-value?
                                       current-window)))
    (create-grid-view-cell new-cell-text-color new-cell-background-color
                           new-cell-type new-cell-value new-cell-read-only?
                           new-cell-is-multiline? new-cell-alignment? new-cell-bold? new-cell-ellipsis-button?
                           new-cell-text-font? new-cell-text-font-size?)))


(defun grid-view-insert-row-locally (gv row-number row-structure) ; May stack-error
  ;; First create all of the cells, without side-effecting the grid.
  (let ((cells
	  (loop with cell-settings = (evaluation-structure-slot row-structure 'cell-settings)
		for cell-ev being each evaluation-sequence-element of cell-settings
		as column-number from 0
		as column-info = (grid-view-column-info gv column-number)
		collect (create-grid-view-cell-with-defaulting cell-ev column-info
			  (lisp-grid-view-support-font? gv))
		  using gensym-cons)))

    ;; Now we know we won't stack-error, mutate the grid.
    (insert-grid-view-row-at-position gv row-number row-structure)
    (incff (lisp-grid-view-row-count gv))
    (loop for cell in cells
	  as col-number from 0
	  do (grid-view-replace-cell gv row-number col-number cell))
    (reclaim-gensym-list cells)))


;;; The function `get-grid-view-cell-property' returns the value for the given
;;; property of cell, inheriting from column-info as needed.

(defun get-grid-view-cell-property (gv cell row column property &optional column-info fully-defaulted)
  (case property
    (cell-type
     (or (grid-view-cell-type? cell)
         (getf column-info 'cell-type)
         (and fully-defaulted 'text-box)))
    (cell-value
     (or (grid-view-cell-value? cell)
         (getf column-info 'cell-value))) ; TODO: default cell-value depends on cell-type.
    (text-color
     (or (grid-view-cell-text-color? cell)
         (getf column-info 'text-color)
         (and fully-defaulted 'black)))
    (background-color
     (or (grid-view-cell-bg-color? cell)
         (getf column-info 'background-color)
         (and fully-defaulted 'white)))
    (read-only
     (or (grid-view-cell-read-only? cell)
	 (getf column-info 'read-only)))
	 ;; added by SoftServe
	(is-multiline
     (or (grid-view-cell-is-multiline? cell)
	 (getf column-info 'is-multiline)))
	 ;; end of SoftServe changes
    (selected
     (or (grid-view-cell-selected-p gv row column)
         (getf column-info 'selected)))         
    (alignment
     (or (grid-view-cell-alignment? cell)
         (getf column-info 'alignment)
         (and fully-defaulted 'left)))
    (bold
     (or (grid-view-cell-bold? cell)
	 (getf column-info 'bold)))
    (ellipsis-button
     (or (grid-view-cell-ellipsis-button? cell)
         (getf column-info 'ellipsis-button)))         
    (t
     (dwarn "Unknown grid-view-cell property ~s" property))))


;;; The function `set-grid-view-cell-property' sets the given property locally,
;;; in the lisp data structure, given an evaluation value. Uses current-window.
;;; It can throw a stack-error because of the call to build-grid-view-cell-value-1.

(defun set-grid-view-cell-property (gv cell row column property evalue) ; May stack-error
  (case property
    (cell-type                                ; NOTE: If changing, must be set first!
     (setf (grid-view-cell-type? cell) (evaluation-symbol-symbol evalue)))
    (cell-value
     (when (grid-view-cell-value? cell)
       (reclaim-structure-if-any (grid-view-cell-value? cell)))
     (setf (grid-view-cell-value? cell)
           (build-grid-view-cell-value-1 (grid-view-cell-type? cell) evalue nil current-window)))
    (text-color
     (setf (grid-view-cell-text-color? cell) (evaluation-symbol-symbol evalue)))
    (background-color
     (setf (grid-view-cell-bg-color? cell) (evaluation-symbol-symbol evalue)))
    (read-only
;     ;; HQ-5029051 "grid-view: combo-box doesn't work when set read-only"
;     (unless (memq (grid-view-cell-type? cell) '(combo-box color-picker))
     (setf (grid-view-cell-read-only? cell) (coerce-to-evaluation-boolean evalue)))
	 ;; added by SoftServe
	(is-multiline
     (setf (grid-view-cell-is-multiline? cell) (coerce-to-evaluation-boolean evalue)))
	 ;; end of SoftServe changes
    (selected
     (grid-view-set-cell-selected gv row column (evaluation-truth-value-is-true-p evalue)))
    (alignment
     (setf (grid-view-cell-alignment? cell) (evaluation-symbol-symbol evalue)))
    (bold
     (setf (grid-view-cell-bold? cell) (coerce-to-evaluation-boolean evalue)))
    (ellipsis-button
     (setf (grid-view-cell-ellipsis-button? cell) (coerce-to-evaluation-boolean evalue)))
    (t
     (dwarn "Unknown grid-view-cell property ~s" property))))


;;; The function `encode-grid-view-cell-property' returns the encoded value to
;;; send over ICP for the given cell property, or NIL if the default value will
;;; do. If fully-defaulted is true, then return a value even if it is the
;;; default. Newly consed. Uses current-window.

(defun encode-grid-view-cell-property (gv cell row column property component column-info
					  &optional fully-defaulted?)
  (let ((value? (get-grid-view-cell-property gv cell row column property column-info fully-defaulted?)))
    (when (or value? fully-defaulted?)
      (case property
        (cell-type
         (map-grid-view-cell-type-to-dialogs-fixnum
           value? (get-grid-view-cell-property gv cell row column 'ellipsis-button column-info t)))
        (cell-value
         (twith-output-to-text-string
           (when value?
             (write-grid-view-cell-value
               value?
               (get-grid-view-cell-property gv cell row column 'cell-type column-info t)
               component))))
        ((text-color background-color)
         (map-to-color-value value?))
;;; modifed by SoftServe 31/10/08
;;; old version  "((read-only ellipsis-button selected bold)"
        ((read-only is-multiline ellipsis-button bold)
	 (if (evaluation-value-is-true-p value?) 1 0))
;;; added by SoftServe 31/10/08
		((selected)
	 (if value? 1 0))
;;; end of SoftServe changes
        (alignment
	 (grid-view-encode-alignment (or value? (if fully-defaulted? 'left))))))))

(defun encode-grid-view-cell-properties (gv cell row column component column-info)
  (loop for property in grid-view-cell-properties
        as encoded-value? = (encode-grid-view-cell-property
                              gv cell row column property component column-info)
        when encoded-value?
          collect property using gensym-cons and
          collect encoded-value? using gensym-cons))


;;; The function `grid-view-insert-row-action' computes an "insert-row action",
;;; in the form of a newly consed gensym-tree of symbols and strings, to send
;;; over ICP via manage-grid-view.

(defun grid-view-insert-row-action (gv row-number component)
  (let* ((row-info (grid-view-row-info gv row-number))
         (row-height? (getf row-info 'height))
         (header-text? (getf row-info 'text))
         (header-integer? (getf row-info 'integer-label))
         (cell-settings
           (loop for col-number from 0 below (lisp-grid-view-column-count gv)
                 as column-info = (grid-view-column-info gv col-number)
                 as cell = (grid-view-ref gv row-number col-number)
                 collect (encode-grid-view-cell-properties gv cell row-number col-number component column-info)
                   using gensym-cons)))
    (nconc
      (gensym-list 'insert-row)
      (gensym-list 'row row-number)
      (if (fixnump row-height?)
          (gensym-list 'height row-height?))
      (if (text-string-p header-text?)
          (gensym-list 'text-value (copy-text-string header-text?)))
      (if (fixnump header-integer?)
          (gensym-list 'integer-label header-integer?))
      (gensym-list 'cell-settings cell-settings))))

(defun grid-view-insert-column-action (gv col-number component)
  (let* ((column-info (grid-view-column-info gv col-number))
         (column-width? (getf column-info 'width))
         (header-text? (getf column-info 'text))
         (cell-settings
           (loop for row-number from 0 below (lisp-grid-view-row-count gv)
                 as cell = (grid-view-ref gv row-number col-number)
                 collect (encode-grid-view-cell-properties gv cell row-number col-number component column-info)
                   using gensym-cons)))
    (nconc
      (gensym-list 'insert-column)
      (gensym-list 'col col-number)
      (if (fixnump column-width?)
          (gensym-list 'width column-width?))
      (if (text-string-p header-text?)
          (gensym-list 'text-value (copy-text-string header-text?)))
      (gensym-list 'cell-settings cell-settings))))


;;; The macro `with-lisp-grid-view' is a helper macro for the grid-view system
;;; procedures which binds variables for the various objects found by id, and
;;; stack-errors if they don't exist.

(defmacro with-lisp-grid-view (((lisp-grid-view &optional (gensym-window 'gensym-window)
                                                (component 'component) (dialog 'dialog))
                                (dialog-id kb-control-id g2-window))
                               &body body)
  `(let* ((,gensym-window (map-to-gensym-window-or-stack-error ,g2-window))
          (,dialog (lookup-dialog-given-handle ,gensym-window ,dialog-id))
          (,component (and ,dialog
                           (lookup-component-given-component-kb-id ,kb-control-id ,dialog)))
          (,lisp-grid-view (and ,component
                                (eq 'grid-view (map-control-type-fixnum-to-symbol
                                                 (dialog-component-type ,component)))
                                (dialog-component-g2-representation? ,component))))
     (unless ,dialog
       (no-dialog-grid-view-operation-error ,dialog-id))
     (unless ,lisp-grid-view
       (control-not-a-grid-view-operation-error ,kb-control-id))
     ,@body))


;;; `reclaim-lisp-grid-view-row'

(defun-void reclaim-lisp-grid-view-row (removed-row)
  (loop for i from 0 below (managed-array-length removed-row)
        as the-cell = (managed-svref removed-row i)
        do
    (if (grid-view-cell-p the-cell)
        (reclaim-grid-view-cell the-cell)
        #+development
        (cerror "Ignore it"
                "Non-grid-view-cell found in grid-view-row!"))
        finally (reclaim-managed-array removed-row)))


;;; `reclaim-lisp-grid-view-row-information-entry'

(defun-void reclaim-lisp-grid-view-row-information-entry (entry?)
  (when entry?
    (reclaim-if-evaluation-value (getf entry? 'text)) ; should be abstracted
    (reclaim-custom-dialog-list entry?)))


;;; `grid-view-delete-row-locally'

(defun grid-view-delete-row-locally (gv row-number) ; May stack-error
  (let* ((removed-row-info? (grid-view-row-info gv row-number))
         (removed-row? (nth row-number (lisp-grid-view-rows gv))))
    (cond
      ((and removed-row? removed-row-info?)
       (setf (lisp-grid-view-row-information gv)
             (delete-custom-dialog-element removed-row-info?
                                           (lisp-grid-view-row-information gv)))
       (setf (lisp-grid-view-rows gv)
             (delete-custom-dialog-element removed-row? (lisp-grid-view-rows gv)))
       (reclaim-lisp-grid-view-row-information-entry removed-row-info?)
       (reclaim-lisp-grid-view-row removed-row?)
       (decff (lisp-grid-view-row-count gv)))
      (t
       (dialogs-stack-error nil "Attempt to delete row #~d from grid-view ~
                                 dialog control, but no such row exists."
                            row-number)))
    nil))

;;; The function `grid-view-insert-column-locally' inserts a column into the
;;; local grid-view structure at position col-number. The column-info and new
;;; cells are initialized from column-structure.  Note that we don't require the
;;; user to specify contents for all of the new cells; unspecified cells are
;;; simply initialized as empty.  This differs from the insert-row functions.

(defun grid-view-insert-column-locally (gv col-number column-structure) ; May stack-error
  (let* ((cell-settings?
           (evaluation-structure-slot column-structure 'cell-settings))
	 (cells
	   (loop for row-number below (lisp-grid-view-row-count gv)
		 as cell-ev? = (if (and cell-settings?
					(<f row-number (evaluation-sequence-length cell-settings?)))
				   (evaluation-sequence-ref cell-settings? row-number))
		 as cell = (build-grid-view-cell gv row-number col-number cell-ev?)
		 collect cell using gensym-cons))
	 (column-info
	   (build-grid-view-column-data-1 column-structure)))

    ;; Now it's safe to mutate the grid.

    (cond ((=f col-number 0)                ; setf-nthcdr is not CL.
           (custom-dialog-push column-info (lisp-grid-view-column-information gv)))
          (t
           (custom-dialog-push column-info (cdr (nthcdr (1-f col-number)
							(lisp-grid-view-column-information gv))))))
    (loop for cell in cells
	  as sublist on (lisp-grid-view-rows gv)
	  as row-array = (car sublist)
	  do (setf (car sublist) (insert-into-managed-array row-array col-number cell)))
    (reclaim-gensym-list cells)
    (incff (lisp-grid-view-column-count gv))))

(defun grid-view-delete-column-locally (gv col-number)
  (let ((info (grid-view-column-info gv col-number)))
    (when info
      (setf (lisp-grid-view-column-information gv)
            (delete-custom-dialog-element info (lisp-grid-view-column-information gv)))
      (reclaim-grid-view-column-information-element info))

    (loop for sublist on (lisp-grid-view-rows gv)
          as row-array = (car sublist)
          as row-number from 0
          as cell = (grid-view-ref gv row-number col-number)
          doing
      (setf (car sublist) (delete-managed-array-element row-array col-number))
      (reclaim-structure-if-any cell))

    (decff (lisp-grid-view-column-count gv))))


(defun grid-view-modify-cell-locally (gv row-number col-number cell-structure) ; May stack-error
  (let ((cell (grid-view-ref gv row-number col-number)))
    (loop for (property . evalue) being each evaluation-structure-pair of cell-structure doing
      (set-grid-view-cell-property gv cell row-number col-number property evalue))))

(defun grid-view-modify-cell-remotely (gv row-number col-number properties dialog-id component)
  (let* ((column-info
           (grid-view-column-info gv col-number))
         (cell
           (grid-view-ref gv row-number col-number))
         (action
           (nconc
             (gensym-list 'modify-cell 'row row-number 'col col-number)
             (loop for property in properties
                   as encoded-value? = (encode-grid-view-cell-property
                                         gv cell row-number col-number property component column-info t)
                   when encoded-value?
                     collect property using gensym-cons and
                     collect encoded-value? using gensym-cons))))
    (%manage-grid-view current-window dialog-id (dialog-component-kb-id component) action)))

(defun grid-view-replace-cell-locally (gv row-number col-number cell-structure)	; May stack-error
  (let* ((column-info (grid-view-column-info gv col-number))
         (cell (create-grid-view-cell-with-defaulting cell-structure column-info
                 (lisp-grid-view-support-font? gv))))
    (grid-view-replace-cell gv row-number col-number cell)))


(defun grid-view-replace-cell-remotely (gv row-number col-number dialog-id component)
  (grid-view-modify-cell-remotely gv row-number col-number grid-view-cell-properties dialog-id component))


(defun grid-view-get-cell-or-stack-error (gv row-number col-number)
  ;; Check indices validity
  (unless (and (<f -1 row-number (lisp-grid-view-row-count gv))
               (<f -1 col-number (lisp-grid-view-column-count gv)))
    (invalid-cell-replace-point-grid-view-error
      (evaluation-integer-value row-number)
      (lisp-grid-view-row-count gv)
      (evaluation-integer-value col-number)
      (lisp-grid-view-column-count gv)))
  (grid-view-ref gv row-number col-number))

(defun check-for-valid-cell-structure (cell-structure)
  (let ((error-text?
          (check-type-error-message cell-structure grid-view-cell-structure-type)))
    (when error-text?
      (write-dialogs-stack-error nil
        (tformat "The CELLSPEC argument is invalid - ~A" error-text?)
        (reclaim-text-string error-text?)
        (reclaim-evaluation-structure cell-structure)))))


;;;; Grid View System Procedures


;;; `g2-ui-grid-view-insert-row' is a system procedure which places a new row
;;; into row number ROW, moving all following rows downwards. In other words, it
;;; inserts *before* the given row, which is allowed to be one beyond the end.
;;; Row number 0 is the first row of user data.

(defun-for-system-procedure g2-ui-grid-view-insert-row
    (dialog-id kb-control-id row-number row-structure g2-window)
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))
    (let* ((cell-settings?
             (evaluation-structure-slot row-structure 'cell-settings))
           (column-count-of-new-row
             (if (evaluation-sequence-p cell-settings?)
                 (evaluation-sequence-length cell-settings?)
                 0)))

      (unless (=f column-count-of-new-row (lisp-grid-view-column-count gv))
        (new-column-not-the-same-length-error
          column-count-of-new-row (lisp-grid-view-column-count gv)))

      (unless (<=f -1 (evaluation-integer-value row-number) (lisp-grid-view-row-count gv))
        (invalid-row-insertion-point-grid-view-insert-error
          (evaluation-integer-value row-number)
          (lisp-grid-view-row-count gv)))

      (when (=f row-number -1)                ; A convenience
        (setq row-number (lisp-grid-view-row-count gv)))

      (on-window-without-drawing (gensym-window)
	(grid-view-insert-row-locally gv row-number row-structure)
	(let ((action (grid-view-insert-row-action gv row-number component)))
	  (%manage-grid-view gensym-window dialog-id kb-control-id action)))

      ;; Still leaked in error cases above.  -dkuznick, 1/26/06
      (reclaim-evaluation-structure row-structure))))

;;; `g2-ui-grid-view-insert-rows'

(defun-for-system-procedure g2-ui-grid-view-insert-rows
    (dialog-id kb-control-id rows-ev g2-window) ;row-number row-structure
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))
    (when (evaluation-sequence-p rows-ev)
      (let ((gv-row-count (lisp-grid-view-row-count gv))
            column-count-of-new-row
            cell-settings?)
        (loop for row-struct-item being each evaluation-sequence-element of rows-ev 
              do
              (when row-struct-item
                (when (not (evaluation-structure-p row-struct-item))
                  (stack-error cached-top-of-stack
                               "Input sequence elements must be structures."))
                (let* ((row-number (evaluation-structure-slot row-struct-item 'row-num))
                       (row-structure (evaluation-structure-slot row-struct-item 'row-struct)))

                  (when (null row-structure)
                    (stack-error cached-top-of-stack
                                 "row-structure is invalid."))
                  (setq cell-settings? (evaluation-structure-slot row-structure 'cell-settings))

                  (when (null cell-settings?)
                    (stack-error cached-top-of-stack
                                 "cell-settings is invalid."))
                  (setq column-count-of-new-row
                        (if (evaluation-sequence-p cell-settings?)
                            (evaluation-sequence-length cell-settings?)
                          0))

                  (unless (=f column-count-of-new-row (lisp-grid-view-column-count gv))
                    (new-column-not-the-same-length-error
                     column-count-of-new-row (lisp-grid-view-column-count gv)))

                  (unless (<=f -1 (evaluation-integer-value row-number) gv-row-count)
                    (invalid-row-insertion-point-grid-view-insert-error
                     (evaluation-integer-value row-number)
                     (lisp-grid-view-row-count gv)))

                  (setq gv-row-count (+f gv-row-count 1))))))
      (on-window-without-drawing (gensym-window)
         (let ((actions nil))
            (loop for row-struct-item being each evaluation-sequence-element of rows-ev
                  do
                  (when row-struct-item
                    (let* ((row-number (evaluation-structure-slot row-struct-item 'row-num))
                           (row-structure (evaluation-structure-slot row-struct-item 'row-struct)))
                      (when (=f row-number -1)                ; A convenience
                        (setq row-number (lisp-grid-view-row-count gv)))
                      (grid-view-insert-row-locally gv row-number row-structure)
                      (setq actions (gensym-cons (grid-view-insert-row-action gv row-number component) actions)))))
            (setq actions (nreverse actions))
            (%manage-grid-view gensym-window dialog-id kb-control-id actions))))))


;;; `g2-ui-grid-view-update-rows'

(defun-for-system-procedure g2-ui-grid-view-update-rows
    (dialog-id kb-control-id rows-ev g2-window) ;row-number row-structure
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))
    (when (evaluation-sequence-p rows-ev)
      (let ((gv-row-count (lisp-grid-view-row-count gv))
            column-count-of-new-row
            cell-settings?)
        (loop for row-struct-item being each evaluation-sequence-element of rows-ev
              do
              (when row-struct-item
                (when (not (evaluation-structure-p row-struct-item))
                  (stack-error
                   cached-top-of-stack
                   "Input sequence elements must be structures."))
                (let* ((row-number (evaluation-structure-slot row-struct-item 'row-num))
                       (row-structure (evaluation-structure-slot row-struct-item 'row-struct)))

                    (when (null row-structure)
                      (stack-error cached-top-of-stack
                                   "row-structure is invalid."))
                    (setq cell-settings?
                          (evaluation-structure-slot row-structure 'cell-settings))

                    (when (null cell-settings?)
                      (stack-error cached-top-of-stack
                                   "cell-settings is invalid."))
                    (setq column-count-of-new-row
                          (if (evaluation-sequence-p cell-settings?)
                              (evaluation-sequence-length cell-settings?)
                            0))

                  (unless (=f column-count-of-new-row (lisp-grid-view-column-count gv))
                    (new-column-not-the-same-length-error
                      column-count-of-new-row (lisp-grid-view-column-count gv)))

                  (unless (<=f -1 (evaluation-integer-value row-number) gv-row-count)
                    (invalid-row-insertion-point-grid-view-insert-error
                     (evaluation-integer-value row-number)
                     (lisp-grid-view-row-count gv)))))))

      (on-window-without-drawing (gensym-window)
         (let ((actions nil))
            (loop for row-struct-item being each evaluation-sequence-element of rows-ev
                do
                  (when row-struct-item
                    (let* ((row-number (evaluation-structure-slot row-struct-item 'row-num))
                           (row-structure (evaluation-structure-slot row-struct-item 'row-struct)))
                      (when (=f row-number -1)                ; A convenience
                        (setq row-number (lisp-grid-view-row-count gv)))
                      (grid-view-delete-row-locally gv row-number)
                      (grid-view-insert-row-locally gv row-number row-structure)
                      (setq actions (gensym-cons (gensym-list 'delete-row 'row row-number) actions))
                      (setq actions (gensym-cons (grid-view-insert-row-action gv row-number component) actions)))))
            (setq actions (nreverse actions))
            (%manage-grid-view gensym-window dialog-id kb-control-id actions))))))


;;; `g2-ui-grid-view-delete-row' is a system procedure which deletes the
;;; designated row, if present, from the grid-view control and from our local
;;; copy. Row number 0 is the first row of user data.

(defun-for-system-procedure g2-ui-grid-view-delete-row
    (dialog-id kb-control-id row-number g2-window)
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))

    (unless (<=f -1 row-number (1-f (lisp-grid-view-row-count gv)))
      (dialogs-stack-error
        nil "Trying to delete a nonexistent row in grid-view at position ~NF. The ~
         position must be between 0 and the current number of rows minus one (~NV), ~
         inclusive, or -1."
        row-number (1-f (lisp-grid-view-row-count gv))))

    (when (=f row-number -1)                ; A convenience
      (setq row-number (1-f (lisp-grid-view-row-count gv))))

    (grid-view-delete-row-locally gv row-number)
    (%manage-grid-view gensym-window dialog-id kb-control-id
                       (gensym-list 'delete-row 'row row-number))))

(defun-for-system-procedure g2-ui-grid-view-insert-column
    (dialog-id kb-control-id col-number column-structure g2-window)
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))
    (let* ((cell-settings?
             (evaluation-structure-slot column-structure 'cell-settings))
           (row-count-of-new-column
             (if (evaluation-sequence-p cell-settings?)
                 (evaluation-sequence-length cell-settings?)
                 0)))

      (when (>f row-count-of-new-column (lisp-grid-view-row-count gv))
	(dialogs-warn "Ignoring ~D extraneous rows specified in cell-settings."
		      (-f row-count-of-new-column (lisp-grid-view-row-count gv))))

      (unless (<=f -1 col-number (lisp-grid-view-column-count gv))
	(dialogs-stack-error
	  nil "Trying to insert a new column in grid-view at position ~NF. The ~
         position must be between 0 and the current number of columns (~NV), ~
         inclusive, or -1."
	  col-number (lisp-grid-view-column-count gv)))

      (when (=f col-number -1)                ; A convenience
	(setq col-number (lisp-grid-view-column-count gv)))

      (on-window-without-drawing (gensym-window)
	(grid-view-insert-column-locally gv col-number column-structure)
	(let ((action (grid-view-insert-column-action gv col-number component)))
	  (%manage-grid-view gensym-window dialog-id kb-control-id action)))

      (reclaim-evaluation-structure column-structure))))

(defun-for-system-procedure g2-ui-grid-view-delete-column
    (dialog-id kb-control-id col-number g2-window)
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))

    (unless (<=f -1 col-number (1-f (lisp-grid-view-column-count gv)))
      (dialogs-stack-error
        nil "Trying to delete a nonexistent column in grid-view at position ~NF. The ~
         position must be between 0 and the current number of columns minus one (~NV), ~
         inclusive, or -1."
        col-number (1-f (lisp-grid-view-column-count gv))))

    (when (=f col-number -1)                ; A convenience
      (setq col-number (1-f (lisp-grid-view-column-count gv))))

    (grid-view-delete-column-locally gv col-number)
    (%manage-grid-view gensym-window dialog-id kb-control-id
                       (gensym-list 'delete-column 'col col-number))))


;; Note we are leaking cell-structure in the stack-errors below, I think I'm
;; going to wait to fix that more generally in the future -dkuznick, 1/26/06


;;; The function `g2-ui-grid-view-replace-cell' updates *all* of the attributes
;;; of the specified cell, taking values from the supplied structure if present,
;;; otherwise from column defaults.

(defun-for-system-procedure g2-ui-grid-view-replace-cell (dialog-id kb-control-id
                                                                    row-number col-number
                                                                    cell-structure g2-window)
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))
    (check-for-valid-cell-structure cell-structure)
    (grid-view-get-cell-or-stack-error gv row-number col-number) ; Simply for error check.

    ;; Do the update, locally and remotely.
    (on-window-without-drawing (gensym-window)
      (grid-view-replace-cell-locally gv row-number col-number cell-structure)
      (grid-view-replace-cell-remotely gv row-number col-number dialog-id component))

    (reclaim-evaluation-structure cell-structure)))


;;; The function `g2-ui-grid-view-modify-cell' modifies the given attributes of
;;; the specified cell. Other attributes of the cell are left unchanged.

(defun-for-system-procedure g2-ui-grid-view-modify-cell (dialog-id kb-control-id
                                                                   row-number col-number
                                                                   cell-structure g2-window)
  (with-lisp-grid-view ((gv) (dialog-id kb-control-id g2-window))
    (check-for-valid-cell-structure cell-structure)
    (grid-view-get-cell-or-stack-error gv row-number col-number) ; Simply for error check.
    
    ;; Do the update, locally and remotely. The on-window is needed for
    ;; computing color values and sending native icons.
    (let ((changed-properties
            (loop for (property . evalue ) being each evaluation-structure-pair of cell-structure
                  collect property using gensym-cons)))
      (on-window-without-drawing (gensym-window)
        (grid-view-modify-cell-locally gv row-number col-number cell-structure)
        (grid-view-modify-cell-remotely gv row-number col-number
                                        changed-properties dialog-id component))
      (reclaim-gensym-list changed-properties))

    (reclaim-evaluation-structure cell-structure)))


;;; `g2-ui-grid-view-row-count' is a system procedure which tells you how many
;;; rows are in the given grid-view.

(defun-for-system-procedure g2-ui-grid-view-row-count (dialog-id kb-control-id g2-window)
  (with-lisp-grid-view ((lisp-grid-view) (dialog-id kb-control-id g2-window))
    (lisp-grid-view-row-count lisp-grid-view)))

(defun-for-system-procedure g2-ui-grid-view-get-hscroll-position-request
    (dialog-id kb-control-id scrollbar-position-var g2-window)
  (with-lisp-grid-view ((lisp-grid-view) (dialog-id kb-control-id g2-window))
    (when (remote-side-supoorts-get-and-set-scroll-position-in-grid-view-p
           (icp-socket-for-gensym-window? gensym-window))
      (%manage-grid-view-get-value-request gensym-window dialog-id kb-control-id scrollbar-position-var
                                           (gensym-list 'get-hscroll-position)))))

(defun-for-system-procedure g2-ui-grid-view-set-hscroll-position (dialog-id kb-control-id scrollbar-position g2-window)
  (with-lisp-grid-view ((lisp-grid-view) (dialog-id kb-control-id g2-window))
    (when (remote-side-supoorts-get-and-set-scroll-position-in-grid-view-p
           (icp-socket-for-gensym-window? gensym-window))
      (%manage-grid-view gensym-window dialog-id kb-control-id
                         (gensym-list 'set-hscroll-position 'param scrollbar-position)))))

(defun-for-system-procedure g2-ui-grid-view-get-vscroll-position-request
    (dialog-id kb-control-id scrollbar-position-var g2-window)
  (with-lisp-grid-view ((lisp-grid-view) (dialog-id kb-control-id g2-window))
    (when (remote-side-supoorts-get-and-set-scroll-position-in-grid-view-p
           (icp-socket-for-gensym-window? gensym-window))
      (%manage-grid-view-get-value-request gensym-window dialog-id kb-control-id scrollbar-position-var
                                           (gensym-list 'get-vscroll-position)))))

(defun-for-system-procedure g2-ui-grid-view-set-vscroll-position (dialog-id kb-control-id scrollbar-position g2-window)
  (with-lisp-grid-view ((lisp-grid-view) (dialog-id kb-control-id g2-window))
    (when (remote-side-supoorts-get-and-set-scroll-position-in-grid-view-p
           (icp-socket-for-gensym-window? gensym-window))
      (%manage-grid-view gensym-window dialog-id kb-control-id
                         (gensym-list 'set-vscroll-position 'param scrollbar-position)))))


;; end of grid-view section






;;;; Posting Custom Dialogs


;;; `echo-dialog-spec-p'

(defvar echo-dialog-spec-p
  #-echo-dialog-send nil
  #+echo-dialog-send t)

(defun-for-system-procedure g2-ui-echo-dialog-spec (echo-p)
  (if (and (evaluation-truth-value-p echo-p)
           (evaluation-truth-value-is-true-p echo-p))
      (setq echo-dialog-spec-p t)
      (setq echo-dialog-spec-p nil)))



;;; `required-dialog-component-attribute-missing-p'

(defun required-dialog-component-attribute-missing-p (lisp-struct)
  (cond
    ((null (dialog-component-kb-id lisp-struct))
     (add-dialog-error "No control-id specified for dialog component!")
     t)
    ((null (dialog-component-value? lisp-struct))
     (add-dialog-error "No control-value specified for component ~s"
                       (dialog-component-kb-id lisp-struct))
     t)
    ((null (dialog-component-height? lisp-struct))
     (add-dialog-error "No height specified for component ~s"
                       (dialog-component-kb-id lisp-struct))
     t)
    ((null (dialog-component-width? lisp-struct))
     (add-dialog-error "No width specified for component ~s"
                       (dialog-component-kb-id lisp-struct))
     t)
    ((null (dialog-component-left? lisp-struct))
     (add-dialog-error "No left specified for component ~s"
                       (dialog-component-kb-id lisp-struct))
     t)
    ((null (dialog-component-top? lisp-struct))
     (add-dialog-error "No top specified for component ~s"
                       (dialog-component-kb-id lisp-struct))
     t)
    ((null (dialog-component-style lisp-struct))
     (add-dialog-error "No style specified for component ~s"
                       (dialog-component-kb-id lisp-struct))
     t)
    (t
     nil)))


;;; `map-parent-id-to-internal-id'

(defun map-parent-id-to-internal-id (lisp-struct)
  (loop with parent-id = (dialog-component-parent-kb-id? lisp-struct)
        for component in (dynamic-dialog-components
                           (dialog-component-parent-dialog lisp-struct))
        when (eql parent-id (dialog-component-kb-id component))
          return (dialog-component-internal-id component)))

;;; 'set font parameters if null'

(defun set-font-parameters (lisp-struct)
  (cond 
    ((null (dialog-component-text-font-size? lisp-struct))
     (setf (dialog-component-text-font-size? lisp-struct) 0)))
  (cond
    ((null (dialog-component-text-font? lisp-struct))
     (setf (dialog-component-text-font? lisp-struct) #w"")))
  (cond
    ((null (dialog-component-text-font-color? lisp-struct))
     (setf (dialog-component-text-font-color? lisp-struct) (copy-wide-string #w""))))
  (cond
    ((null (dialog-component-control-background-color? lisp-struct))
     (setf (dialog-component-control-background-color? lisp-struct) (copy-wide-string #w"")))))

;;; `add-component-lisp-struct'

#| adding a magic bit in response-action if component-type is push-button to
 | indicate the push-button is default push-button or not. response-action only
 | support 1, 3, 4, 7, 12, 15, 17, 32 value. so, use a high bit like the 10th
 | bit to store is-default field is a better choice than modify a sequence of
 | functions
 |#

;;; 1024 = 2^10
(defconstant bit-of-push-button-is-default 1024)

(defun add-component-lisp-struct (lisp-struct dialog gensym-window)
  (setf (dialog-component-parent-id lisp-struct)
        (or (map-parent-id-to-internal-id lisp-struct)
            id-for-entire-dialog))
  ;; if the response-action was not specified, use the default, which depends
  ;; on what type of control it is.
  (when (=f (dialog-component-response-action lisp-struct)
            dialog-response-unspecified)
    (setf (dialog-component-response-action lisp-struct)
          (case (map-control-type-fixnum-to-symbol
                  (dialog-component-type lisp-struct))
            ((tree-view-combo-box combo-box list-box checkable-list-box color-picker
                                  full-color-picker text-box
                                  masked-edit spinner duration short-duration calendar
                                  time-of-day radio-button check-box toggle-button)
             dialog-response-just-respond)
            (push-button
             dialog-response-respond-all-and-ok)
            ((tab-frame progress-bar track-bar slider label workspace
                        group tabular-view grid-view image)
             dialog-response-no-action)
            (t
             (dialogs-dwarn "add-component-lisp-struct: unrecognized: ~d in ~s"
                            (dialog-component-type lisp-struct) lisp-struct)
             dialog-response-no-action))))

  (let* ((component-type-symbol (map-control-type-fixnum-to-symbol
                                  (dialog-component-type lisp-struct))))
    (set-font-parameters lisp-struct) ;;; To assign default value to font features if not passed in structure
    #+echo-dialog-send
    (dbg-output-dialog-component-for-c lisp-struct)
    (if (remote-side-supports-dialog-component-with-font-p current-icp-socket)
      ; supports font parameters
      (send-icp-add-dialog-component-with-font
        gensym-window
        (dynamic-dialog-handle dialog)
        (dialog-component-internal-id lisp-struct)
        (or (dialog-component-parent-id lisp-struct)
            id-for-entire-dialog)
        (or (dialog-component-parent-text? lisp-struct)
            #w"")
        (dialog-component-height? lisp-struct)
        (dialog-component-width? lisp-struct)
        (dialog-component-left? lisp-struct)
        (dialog-component-top? lisp-struct)
        (dialog-component-text-font? lisp-struct)
        (dialog-component-text-font-size? lisp-struct)
        (dialog-component-text-font-color? lisp-struct)
        (dialog-component-control-background-color? lisp-struct)
        (dialog-component-type lisp-struct)
        (dialog-component-value? lisp-struct)
        (car (dialog-component-style lisp-struct))
        (cdr (dialog-component-style lisp-struct))
        (dialog-component-g2-style lisp-struct)
        (cond
          ((and (eq (dialog-component-type lisp-struct) (dialog-control-type 'push-button))
                (dialog-component-is-default lisp-struct))
           (+f (dialog-component-response-action lisp-struct) bit-of-push-button-is-default))
          (t
           (dialog-component-response-action lisp-struct))))  
      ; does not support font parameters
      (send-icp-add-dialog-component
        gensym-window
        (dynamic-dialog-handle dialog)
        (dialog-component-internal-id lisp-struct)
        (or (dialog-component-parent-id lisp-struct)
            id-for-entire-dialog)
        (or (dialog-component-parent-text? lisp-struct)
            #w"")
        (dialog-component-height? lisp-struct)
        (dialog-component-width? lisp-struct)
        (dialog-component-left? lisp-struct)
        (dialog-component-top? lisp-struct)
        (dialog-component-type lisp-struct)
        (dialog-component-value? lisp-struct)
        (car (dialog-component-style lisp-struct))
        (cdr (dialog-component-style lisp-struct))
        (dialog-component-g2-style lisp-struct)
        (cond
          ((and (eq (dialog-component-type lisp-struct) (dialog-control-type 'push-button))
                (dialog-component-is-default lisp-struct))
           (+f (dialog-component-response-action lisp-struct) bit-of-push-button-is-default))
          (t
           (dialog-component-response-action lisp-struct)))))

    ;; Some control types require additional initialization messages after the
    ;; add-dialog-component message.
    (case component-type-symbol
      (tabular-view
       (add-tabular-view-to-dialog lisp-struct dialog gensym-window))

      (grid-view
       (add-grid-view-to-dialog lisp-struct dialog))

      (text-box
       (send-icp-specify-text-box-extensions (dynamic-dialog-handle dialog))))
    t))


;;; The function `add-component-to-custom-dialog' adds a dialog component as
;;; represented by eval-struct to dialog.  This function does error checking,
;;; and converts the eval-struct into one or more corresponding dialog-component
;;; structure, and pushes them into the dynamic-dialog-components slot of the
;;; dialog.

(defun add-component-to-custom-dialog (dialog eval-struct)
  (let* ((specified-type-symbol (evaluation-structure-slot eval-struct 'control-type))
         (type-fixnum? (dialog-control-type specified-type-symbol)))
    ;; We want to set the control-type attribute first, so that the other attributes
    ;; can use the control-type in error checking.
    (cond
      ((null specified-type-symbol)
       (dialogs-stack-error dialog "All dialog components must have a control type."))
      ((null type-fixnum?)
       (dialogs-stack-error dialog
                            "Unrecognized type ~s requested in dialog"
                            (evaluation-structure-slot eval-struct 'control-type)))
      ((eq specified-type-symbol 'integer)
       (dialogs-stack-error dialog
                            "Components of type INTEGER are not supported on ~
                             dialogs; you can only use INTEGER as a type in ~
                             a cell of the grid-view control."))
      ((eq specified-type-symbol 'quantity)
       (dialogs-stack-error dialog
                            "Components of type QUANTITY are not supported on ~
                             dialogs; you can only use QUANTITY as a type in ~
                             a cell of the grid-view control."))
      (t
       (let* ((lisp-struct (create-dialog-component eval-struct))
              (unrecognized-attributes '()))
         (setf (dialog-component-parent-dialog lisp-struct) dialog)
         (setf (dialog-component-type lisp-struct) type-fixnum?)
         (loop for style in default-styles-for-dialog-control do
           (add-style-to-lisp-struct lisp-struct style))

         ;; The ws-tabstop style is added to every control by default, but a
         ;; select few need to have the style removed.  The user can override the
         ;; defaults with the is-tabstop attribute.
         (when (memq specified-type-symbol
                     non-natural-tabstop-dialog-component-type-symbols)
           (delete-style-from-lisp-struct lisp-struct 'ws-tabstop))

         (loop for (attribute . value)
                   being each evaluation-structure-pair of eval-struct
               as dialog-handler = (dialog-handler attribute)
               do
           (if dialog-handler
               (funcall dialog-handler value lisp-struct)
               (gensym-push attribute unrecognized-attributes)))
         #+development
         (when unrecognized-attributes
           (warn "unrecognized attributes in component ~s:"
                 (dialog-component-kb-id lisp-struct))
           (let ((*print-case* :downcase))
             (format t "    ~s~%" unrecognized-attributes)))
         (reclaim-gensym-list unrecognized-attributes)

         (let ((component-value? (dialog-component-value? lisp-struct)))
           (when (and (text-string-p component-value?)
                      (>=f (text-string-length component-value?)
                           maximum-length-for-user-text-strings))
             (dialog-component-too-large-stack-error lisp-struct)))

         (cond
           ((required-dialog-component-attribute-missing-p lisp-struct)
            nil)
           (t
            (incff (dynamic-dialog-next-component-number dialog))
            (incff (dynamic-dialog-count-components dialog))
            (gensym-push
              lisp-struct
              (dynamic-dialog-components dialog)))))))))


;;; `start-native-dialog'

(defun start-native-dialog (gensym-window new-dialog width height title
                                          modal-p mdi-child-p)
  #+echo-dialog-send
  (dbg-output-start-dialog new-dialog width height title modal-p mdi-child-p)
  #-echo-dialog-send
  (declare (ignore mdi-child-p))
  (send-icp-start-custom-dialog gensym-window
                                (dynamic-dialog-handle new-dialog)
                                (dynamic-dialog-count-components new-dialog)
                                width height modal-p title))


;;; `finish-native-dialog'

(defun finish-native-dialog (gensym-window new-dialog x-position y-position
                                           container dock? neighbor? icon? resizable-p
                                           monitor-preference)
  (let ((mdi-child-p (eq container 'mdi-child)))
    #+echo-dialog-send
    (dbg-output-finish-dialog gensym-window new-dialog x-position y-position
			      mdi-child-p dock? neighbor? icon? resizable-p)
    (cond ((window-supports-dialog-panes gensym-window)
	   (let ((plist (nconc (if mdi-child-p (gensym-list 'mdi-child t))
			       (if container (gensym-list 'container container))
			       (if dock? (gensym-list 'dock dock?))
			       (if neighbor? (gensym-list 'neighbor neighbor?))
			       (if icon? (gensym-list 'icon
						      (send-native-icon gensym-window icon?)))
			       (if resizable-p (gensym-list 'resizable t))
			       (gensym-list 'monitor-preference monitor-preference))))
	     (send-icp-show-custom-dialog-ex gensym-window (dynamic-dialog-handle new-dialog)
					     x-position y-position plist)
	     (reclaim-gensym-list plist)))
	  (t
	   (send-icp-show-custom-dialog gensym-window (dynamic-dialog-handle new-dialog)
					x-position y-position
					(if mdi-child-p 1 0))))))


;;; `default-title-for-custom-dialog' -- the title for the window if users don't
;;; supply their own.

(defconstant default-title-for-custom-dialog #w"G2")


;;; `default-width-for-custom-dialog' and `default-height-for-custom-dialog'



;;; `window-supports-dialog-component-p'

(defun window-supports-dialog-component-p (gensym-window dialog-component)
  (let ((component-type?
          (evaluation-structure-slot dialog-component 'control-type)))
    (cond
      ((null component-type?)
       (add-dialog-error "All dialog components must supply a CONTROL-TYPE.")
       nil)
      ((eq component-type? 'workspace)
       (mdi-frame-p gensym-window))
      ((memq component-type?
             '(tab-frame progress-bar track-bar slider combo-box list-box
               color-picker text-box label spinner calendar time-of-day group
               radio-button check-box push-button toggle-button tabular-view
               tree-view-combo-box image checkable-list-box full-color-picker
               masked-edit duration short-duration grid-view))
       t)
      (t  ;; unrecognized component type!
       (add-dialog-error "~NA is not a recognized CONTROL-TYPE for custom dialogs."
                         component-type?)
       nil))))


;;; `dialog-supports-dialog-component-p' -- a very general and somewhat
;;; mysterious name for a function intended just to deal with Bug HQ-5014182,
;;; "workspace dialog control barely functional unless dialog is mdi-child"

(defun dialog-supports-dialog-component-p (component mdi-child-p)
  (let ((component-type
          (evaluation-structure-slot component 'control-type)))
    (or (neq component-type 'workspace)
        mdi-child-p
        (progn
          (add-dialog-error "The WORKSPACE dialog control is only supported in ~
                             dialogs which are MDI-CHILD windows.")
          nil))))


;;; `send-messages-to-dialog-components'

;; note: we prefer the symbols DROPPED-WIDTH and DROPPED-HEIGHT.  In 8.3a0, we
;; supported DROPDOWN-WIDTH and DROPDOWN-HEIGHT.  That was only an Alpha and we
;; could probably easily de-support them, but for now, try to minimally support
;; them.  Note that we do an "or", so if BOTH of the attributes are set, we'll
;; use the preferred one and ignore the other one.  -jv, 9/5/06

(defun send-messages-to-dialog-components (dialog gensym-window)
  (loop for lisp-struct in (dynamic-dialog-components dialog)
        as combo-box-p = (memq (map-control-type-fixnum-to-symbol
                                 (dialog-component-type lisp-struct))
                               '(combo-box color-picker tree-view-combo-box))
        as dropped-width? = (and combo-box-p
                                 (or (evaluation-structure-slot
                                       (dialog-component-evaluation-structure
                                         lisp-struct)
                                       'dropped-width nil)
                                     (evaluation-structure-slot
                                       (dialog-component-evaluation-structure
                                         lisp-struct)
                                       'dropdown-width nil)))
        as dropped-height? = (and combo-box-p
                                  (or (evaluation-structure-slot
                                        (dialog-component-evaluation-structure
                                          lisp-struct)
                                        'dropped-height nil)
                                      (evaluation-structure-slot
                                        (dialog-component-evaluation-structure
                                          lisp-struct)
                                        'dropdown-height nil)))
        do
    (when combo-box-p
      (when (evaluation-integer-p dropped-width?)
        (let ((dropped-width-text (twith-output-to-text-string
                                    (twrite-fixnum dropped-width?))))
          (send-icp-dialog-component-update
            gensym-window
            (dynamic-dialog-handle dialog)
            (dialog-component-internal-id lisp-struct)
            dropped-width-text
            (get-control-action-id-from-symbol 'dropped-width))
          (reclaim-text-string dropped-width-text)))
      (when (evaluation-integer-p dropped-height?)
        (let ((dropped-height-text (twith-output-to-text-string
                                     (twrite-fixnum dropped-height?))))
          (send-icp-dialog-component-update
            gensym-window
            (dynamic-dialog-handle dialog)
            (dialog-component-internal-id lisp-struct)
            dropped-height-text
            (get-control-action-id-from-symbol 'dropped-height))
          (reclaim-text-string dropped-height-text))))))


;;; `create-dynamic-dialog'

(defun create-dynamic-dialog ()
  (let ((dynamic-dialog (make-dynamic-dialog)))
    (setf (dynamic-dialog-errors dynamic-dialog)
          (make-dialog-errors-structure))
    dynamic-dialog))


;;; The function `filter-custom-dialog-position' is a subfunction of
;;; g2-ui-post-custom-dialog.  It either returns a valid encoded x- or
;;; y-position, or signals a dialog error.  A valid encoded position is suitable
;;; for sending as the xPos or yPos argument for the TW-side dynamic dialog
;;; facility.  The argument position can either be an integer or one of the
;;; symbols with a mapping in the a-list bound to the constant
;;; `dialog-symbol-to-code-map'.

(defun filter-custom-dialog-position (position axis)
  (declare (ignore axis))                ; X or Y; later, error check this!
  (cond
    ((fixnump position)
     position)
    (t
     (let ((code?
             (if (symbolp position)
                 (cdr (assq position dialog-symbol-to-code-map)))))
       (or code?
           (dialogs-stack-error nil
                                "~NA is not a valid dialog-x- or dialog-y-position. ~
              It must be either an integer or one of the symbols ~L,|."
                                position valid-dialog-position-symbols))))))

(defun validate-monitor-preference-option (monitor-preference)
  (unless (getf monitor-preference-settings monitor-preference nil)
    (dialogs-stack-error
      nil "~NA is not a valid monitor preference setting. It must be one of the symbols ~L,|."
      monitor-preference valid-monitor-preference-symbols)))

;;; The system-procedure `g2-ui-post-custom-dialog' creates and launches a
;;; custom, native dialog on the given g2-window.

(defun-allowing-unwind-for-system-procedure g2-ui-post-custom-dialog (dialog-spec user-data g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (modal-p (evaluation-boolean-is-true-p
                    (evaluation-structure-slot dialog-spec 'dialog-is-modal nil)))
         (mdi-child-p (and (evaluation-boolean-is-true-p
                             (evaluation-structure-slot dialog-spec 'dialog-is-mdi-child nil))
                           (mdi-frame-p gensym-window) ; Maybe warn user if these tests fail.
                           (not modal-p)))
         (dock? (and (not mdi-child-p)
                     (not modal-p)
                     (neq (evaluation-structure-slot dialog-spec 'dock) 'none)
                     (evaluation-structure-slot dialog-spec 'dock)))
         (container (evaluation-structure-slot
                      dialog-spec 'container
                      (cond (mdi-child-p 'mdi-child)
                            (dock? 'pane)
                            (t 'top-level))))
         (generic-callback (evaluation-structure-slot dialog-spec 'dialog-generic-callback))
         (update-callback (evaluation-structure-slot dialog-spec 'dialog-update-callback))
         (dismissed-callback (evaluation-structure-slot dialog-spec 'dialog-dismissed-callback))
         (resize-callback (evaluation-structure-slot dialog-spec 'dialog-resize-callback))
         (components (evaluation-structure-slot dialog-spec 'components))
         (new-dialog (create-dynamic-dialog))
         (dialog-errors (dynamic-dialog-errors new-dialog))
         (width (evaluation-structure-slot dialog-spec 'dialog-width
                                           default-width-for-custom-dialog))
         (height (evaluation-structure-slot dialog-spec 'dialog-height
                                            default-height-for-custom-dialog))
         (monitor-preference (evaluation-structure-slot dialog-spec 'monitor-preference
                                default-monitor-preference-for-dialog))
         (x-position (evaluation-structure-slot dialog-spec 'dialog-x-position
                                                default-x-position-for-custom-dialog))
         (y-position (evaluation-structure-slot dialog-spec 'dialog-y-position
                                                default-y-position-for-custom-dialog))
         (resizable-p (evaluation-boolean-is-true-p
                        (evaluation-structure-slot dialog-spec 'resizable nil)))
         (title (copy-wide-string
                  (evaluation-structure-slot dialog-spec 'dialog-title
                                             default-title-for-custom-dialog)))
         (neighbor? (evaluation-structure-slot dialog-spec 'neighbor))
         (icon? (evaluation-structure-slot dialog-spec 'icon))
	 (icp-socket (icp-socket-for-gensym-window? gensym-window))
	 (support-background-color? (and icp-socket (remote-side-supports-background-color-in-custom-dialogs-p icp-socket)))
	 (background-color? (or (evaluation-structure-slot dialog-spec 'dialog-background-color) #w""))
         (options (if icon? (gensym-list 'icon icon?)))
         (dialog-view nil))

    ;; We should do this check before we bind a thousand variables...
    (unless (native-custom-dialogs-p gensym-window)
      (dialogs-stack-error nil "Custom dialogs are not supported on ~NF." g2-window))

    (when (and (eq container 'pane)
               (not (dialog-panes-p gensym-window)))
      (dialogs-stack-error nil "Dialog panes are not supported on ~NF." g2-window))

    (multiple-value-setq (container neighbor?)
      (preprocess-container-options-1 gensym-window container dock? neighbor? 'g2-dialog-view))

    (if user-data
        (setf (dynamic-dialog-user-data new-dialog)
              (deep-copy-evaluation-value user-data))
        (setf (dynamic-dialog-user-data new-dialog)
              (allocate-evaluation-sequence nil)))

    (setf (dynamic-dialog-generic-callback? new-dialog) (stored-callback-procedure generic-callback)
	  (dynamic-dialog-update-callback? new-dialog) (stored-callback-procedure update-callback)
	  (dynamic-dialog-dismissed-callback? new-dialog) (stored-callback-procedure dismissed-callback)
          (dynamic-dialog-resize-callback? new-dialog) (stored-callback-procedure resize-callback))

    ;; Check type of and translate position specs to integers:
    (setq x-position (filter-custom-dialog-position x-position 'x))
    (setq y-position (filter-custom-dialog-position y-position 'y))
    (validate-monitor-preference-option monitor-preference)

    (setf dialog-view (make-dialog-view gensym-window new-dialog title container options generic-callback)
          (dynamic-dialog-view? new-dialog) dialog-view
          (dynamic-dialog-handle new-dialog) (native-window-handle dialog-view))

    (when (evaluation-sequence-p components)
      ;; There needs to be an *enormous* amount of error checking here... at this
      ;; point, we're punting on it entirely.  We just assume the structure is
      ;; properly formatted to describe a dialog.  -jv, 3/26/04

      (with-collect-dialog-errors dialog-errors
        (loop for component being each evaluation-sequence-element of components
              always (and (window-supports-dialog-component-p
                            gensym-window component)
                          (dialog-supports-dialog-component-p
                            component mdi-child-p)
                          (add-component-to-custom-dialog new-dialog component)))))

    (reclaim-gensym-list options)

    (cond ((dialog-has-errors-p dialog-errors)
           (setf (dynamic-dialog-handle new-dialog) handle-for-no-dialog)

           ;; remove above line and reclaim dialog and any components and
           ;; arguments to system-procedure here
           (write-dialogs-stack-error new-dialog
             (format-dialog-errors "Errors in G2-UI-POST-CUSTOM-DIALOG"
                                   dialog-errors)))

          (t
           (setf (dynamic-dialog-components new-dialog)
                 (tab-order-reversed-dialog-components
                   (dynamic-dialog-components new-dialog)))
           (with-icp-window (gensym-window)
             (start-native-dialog gensym-window new-dialog width height title
                                  modal-p mdi-child-p)
             (loop for lisp-struct in (dynamic-dialog-components new-dialog)
                   do
               (add-component-lisp-struct lisp-struct new-dialog gensym-window))
             (finish-native-dialog gensym-window new-dialog x-position y-position
                                   container dock? neighbor? icon? resizable-p monitor-preference)

	     (when (and support-background-color? background-color?)
	       (send-icp-set-custom-dialog-background gensym-window (dynamic-dialog-handle new-dialog) background-color?))

             (send-messages-to-dialog-components new-dialog gensym-window))

           (when echo-dialog-spec-p
             (stderr-message "start g2-ui-post-custom-dialog(~NV," dialog-spec)
             (stderr-message "    the symbol user-data-omitted, ~NA)" g2-window))

           (reclaim-if-evaluation-value dialog-spec)
           (reclaim-if-evaluation-value user-data)
           (dynamic-dialog-handle new-dialog)))))



;;; The system procedure `g2-ui-cancel-custom-dialog' cancels the given native
;;; dialog posted on the given window.

(defun-for-system-procedure g2-ui-cancel-custom-dialog (dialog-id g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (native-basic-dialogs-p gensym-window)
      (dialogs-stack-error nil "Native dialogs are not supported on ~NF." g2-window))
    (with-icp-window (gensym-window)
      (send-icp-abort-custom-dialog gensym-window dialog-id))))


;;; The system procedure `g2-ui-accept-custom-dialog' accepts the given native
;;; dialog posted on the given window.

(defun-for-system-procedure g2-ui-accept-custom-dialog (dialog-id g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (unless (native-basic-dialogs-p gensym-window)
      (dialogs-stack-error nil "Native dialogs are not supported on ~NF." g2-window))
    (with-icp-window (gensym-window)
      (send-icp-accept-custom-dialog gensym-window dialog-id))))




;;; `obtain-values-for-all-controls' -- note that by convention, dialog is never
;;; supposed to be nil (and therefore lacks a question-mark); but we do a null
;;; check "just in case".  Dynamic dialogs are a new feature for 8.0r0, and QA
;;; time is very limited, so I'm being extra careful.  -jv, 5/30/04

(defun obtain-values-for-all-controls (dialog)
  (allocate-evaluation-sequence
    (and dialog
         (loop for component in (dynamic-dialog-components dialog)
               collect
               (allocate-evaluation-structure
                 (eval-list 'control-id
                            (dialog-component-kb-id component)
                            'control-value
                            (compose-up-to-date-control-value component)))
                 using eval-cons))))


;;; `obtain-values-for-selected-controls' - not implemented as of 6/7/2004.
;;; Bug HQ-4796574, "g2-ui-query-custom-dialog-values gives too many values"

(defun obtain-values-for-selected-controls (dialog sequence-of-controls)
  (declare (ignore sequence-of-controls))
  (obtain-values-for-all-controls dialog))


;;; `generate-query-id' - to be implemented

(defun generate-query-id (dialog-handle g2-window)
  (declare (ignore dialog-handle g2-window))
  1)



;;; The system-procedure `g2-ui-query-dialog-values' returns a sequence of
;;; control-id/value pairs (as structures), reflecting the current state of
;;; the specified controls of the given dialog.
;; It does?? Maybe that's what the cap does via the semaphore, but that's not
;; what this does!! -dkuznick, 12/2/05

(defun-for-system-procedure g2-ui-query-dialog-values (dialog-handle
                                                        controls
                                                        parameter
                                                        g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (query-id (generate-query-id dialog-handle g2-window))
         (dialog (lookup-dialog-given-handle gensym-window dialog-handle)))
    (cond
      ((null dialog)
       (reclaim-evaluation-sequence controls)
       (dialogs-stack-error dialog "Attempt to query a dialog id which does ~
                                    not correspond to a dialog"))
      (t
       ;; Why not use an item-reference instead of a guard?
       (setf (dynamic-dialog-semaphore-parameter dialog) parameter)
       (setf (dynamic-dialog-semaphore-serial-number dialog)
             (frame-serial-number parameter))
       (with-icp-window (gensym-window)
         (send-icp-start-dialog-query
           gensym-window dialog-handle query-id 0)
         (loop for component being each evaluation-sequence-element of controls)
         (send-icp-finish-dialog-query gensym-window dialog-handle query-id))))
    (reclaim-evaluation-sequence controls)))


;;; `g2-ui-get-cached-dialog-values' is called by pre-8.1r0 sys-mod. We have to
;;; grovel for the missing g2-window argument.

(defun-for-system-procedure g2-ui-get-cached-dialog-values (dialog-handle
                                                             controls)
  (let* ((local-vars (invocation-local-var-vector current-computation-instance))
         (g2-window? (loop for i below (length local-vars)
                           as element = (svref local-vars i)
                           when (of-class-p-function element 'g2-window)
                             return element)))
    (unless g2-window?
      (reclaim-evaluation-sequence controls)
      (stack-error cached-top-of-stack "You need to use the latest sys-mod for this G2."))

    (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window?))
           (dialog (lookup-dialog-given-handle gensym-window dialog-handle)))
      (prog1
          (obtain-values-for-selected-controls dialog controls)
        (reclaim-evaluation-sequence controls)))))


;;; The function `g2-ui-get-cached-dialog-values-ex' is called by the new
;;; sys-mod for 8.1r0, and receives the g2-window as an argument.

(defun-for-system-procedure g2-ui-get-cached-dialog-values-ex (dialog-handle
                                                                controls
                                                                g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (dialog (lookup-dialog-given-handle gensym-window dialog-handle)))
    (prog1
        (obtain-values-for-selected-controls dialog controls)
      (reclaim-evaluation-sequence controls))))




;;;; Modifying Dialogs

;;; Lisp representation of a specification to modify a dialog.

(def-structure modify-control-structure
  (modify-internal-control-id nil)    ; The internal id of the control
  (modify-control-action nil)         ; The internal id of the action
  (modify-control-value-text nil :reclaimer reclaim-if-text-string)     ; The value is a text and is single valued
  (modify-control-value-sequence nil :reclaimer reclaim-if-evaluation-value) ; Used in multi value case
  ;; The value of modify-existing-component is not owned by this structure, so
  ;; don't reclaim
  (modify-existing-component nil))    ; Used in multi value case

(def-structure modify-dialog-structure
  (modify-dialog nil)             ; The dialog that is being modified
  (modify-gensym-window nil)      ; The window to modify the dialog on
  (modify-control-structures nil :reclaimer reclaim-list-of-modify-control-structures) ; List of modify-control structures
  (modify-dialog-errors nil :reclaimer reclaim-dialog-errors-structure))     ; dialog-errors-structure

(defun-void reclaim-list-of-modify-control-structures (list)
  (loop for modify-control-structure in list
        do (reclaim-modify-control-structure modify-control-structure))
  (reclaim-gensym-list list))


;;; `add-modify-control-structure' - Adding modify control structures to modify
;;; dialog structures

(defun add-modify-control-structure (modify-dialog-structure modify-control-structure)
  (setf (modify-control-structures modify-dialog-structure)
        (nconc (modify-control-structures modify-dialog-structure)
               (gensym-list modify-control-structure))))


;;; Adding errors to modify-dialog-structure


;;; Modify Control Action types


;;; `modify-control-action-type'

(def-structure modify-control-action-type
  (modify-control-action-id nil)
  (modify-control-action-symbol nil)
  (modify-control-prepare-function nil)
  (modify-control-perform-function nil)
  (modify-control-valid-types nil))


(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar supported-control-actions-by-id '())
(defvar supported-control-actions-by-symbol '())
)


;;; `default-prepare-modify-control'

(defun default-prepare-modify-control (modify-dialog-structure
                                        modify-control-structure
                                        control
                                        control-type-symbol
                                        control-value)
  (declare (ignore modify-dialog-structure)
           (ignore control)
           (ignore control-value)
           (ignore control-type-symbol))
  (setf (modify-control-value-text modify-control-structure)
        (copy-wide-string #w"")))


;;; `default-perform-modify-control'

(defun default-perform-modify-control (modify-dialog-structure modify-control-structure)
  (let ((update-text (modify-control-value-text
                       modify-control-structure))
        (internal-control-id
          (modify-internal-control-id modify-control-structure))
        (dialog-id (dynamic-dialog-handle
                     (modify-dialog modify-dialog-structure)))
        (control-action
          (modify-control-action-symbol modify-control-structure))
        (gensym-window
          (modify-gensym-window modify-dialog-structure)))
    #+echo-dialog-send
    (dbg-echo-dialog-update dialog-id internal-control-id update-text)
    (send-icp-dialog-component-update
      gensym-window
      dialog-id
      internal-control-id
      update-text
      (get-control-action-id-from-symbol control-action))))


;;; `dropped-width-modify-control'

(defun dropped-width-prepare-modify-control (modify-dialog-structure
                                              modify-control-structure
                                              control
                                              control-type-symbol
                                              control-value)
  (declare (ignore modify-dialog-structure
                   control
                   control-type-symbol))
  (setf (modify-control-value-text modify-control-structure)
        (twith-output-to-text-string (twrite-fixnum control-value))))


;;; `dropped-height-modify-control'

(defun dropped-height-prepare-modify-control (modify-dialog-structure
                                              modify-control-structure
                                              control
                                              control-type-symbol
                                              control-value)
  (declare (ignore modify-dialog-structure
                   control
                   control-type-symbol))
  (setf (modify-control-value-text modify-control-structure)
        (twith-output-to-text-string (twrite-fixnum control-value))))


;;; `selected-tab-prepare-modify-control'

(defun selected-tab-prepare-modify-control (modify-dialog-structure
                                             modify-control-structure
                                             control
                                             control-type-symbol
                                             control-value)
  (declare (ignore modify-dialog-structure
                   control
                   control-type-symbol))
  (cond
    ((null control-value)
     (add-dialog-error "Missing CONTROL-VALUE." ))
    ((and control-value (not (evaluation-text-p control-value)))
     (add-dialog-error "CONTROL-VALUE attribute was not a text: ~NF"
		       control-value))
    (t
     (setf (modify-control-value-text modify-control-structure)
	   (copy-evaluation-text control-value)))))


;;; `get-control-action-structure-from-symbol'

(defun get-control-action-structure-from-symbol (action-symbol)
  (cdr (assoc action-symbol supported-control-actions-by-symbol)))


;;; `get-control-action-id-from-symbol'

(defun get-control-action-id-from-symbol (action-symbol)
  (let ((control-action-structure
          (get-control-action-structure-from-symbol action-symbol)))
    (when control-action-structure
      (modify-control-action-id control-action-structure))))


;;; `valid-control-action-p'

(defun valid-control-action-p (control-action control-type)
  (let* ((control-action-structure
           (get-control-action-structure-from-symbol control-action))
         (supported-control-types
           (modify-control-valid-types control-action-structure)))
    (cond ((eq supported-control-types 'all)
           t)
          ((and (listp supported-control-types)
                (memq control-type supported-control-types))
           t))))


;;; `prepare-modify-control-replace'

(defun prepare-modify-control-replace (modify-dialog-structure
                                        modify-control-structure
                                        component
                                        control-type-symbol
                                        control-value)
  (declare (ignore modify-dialog-structure))
  (cond
    ((null control-value)
     (add-dialog-error "Missing CONTROL-VALUE." component))
    ((and control-value (not (evaluation-structure-p control-value)))
     (add-dialog-error "CONTROL-VALUE attribute was not a structure: ~NA" control-value))
    (t
     (setf (modify-control-value-text modify-control-structure)
           ;; Can return NIL
           (evaluate-control-value-per-control-type
             (modify-existing-component modify-control-structure)
             control-type-symbol control-value)))))


;;; `def-control-action-type'

(defmacro def-control-action-type (action-symbol
                                    corresponding-number
                                    &key (prepare-function 'default-prepare-modify-control)
                                    (perform-function 'default-perform-modify-control)
                                    (valid-control-types 'all))
  `(let* ((existing-user?
            (cdr (assoc ,corresponding-number supported-control-actions-by-id)))
          (already-used-by? (and existing-user?
                                 (modify-control-action-symbol existing-user?))))
     (cond ((and already-used-by?
                 (neq already-used-by? ',action-symbol))
            (cerror "Ignore the new action"
                    "the control action ~s wants to use id ~s, but ~s is already in use by ~s"
                    ',action-symbol ,corresponding-number ,corresponding-number
                    already-used-by?))
           (t
            #+development
            (when already-used-by?
              (warn "Re-defining control action ~S" already-used-by?))
            (let ((control-action-structure
                    (make-modify-control-action-type)))
              (setf (modify-control-action-id control-action-structure)
                    ,corresponding-number)
              (setf (modify-control-action-symbol control-action-structure)
                    ',action-symbol)
              (setf (modify-control-prepare-function control-action-structure)
                    ',prepare-function)
              (setf (modify-control-perform-function control-action-structure)
                    ',perform-function)
              (setf (modify-control-valid-types control-action-structure)
                    ',valid-control-types)
              (when already-used-by?
                (let ((by-id-user (assoc already-used-by? supported-control-actions-by-id))
                      (by-symbol-user (assoc already-used-by? supported-control-actions-by-id)))
                  (setq supported-control-actions-by-id
                        (remove by-id-user supported-control-actions-by-id))
                  (setq supported-control-actions-by-symbol
                        (remove by-symbol-user supported-control-actions-by-symbol))))
              (push (cons ,corresponding-number control-action-structure)
                    supported-control-actions-by-id)
              (push (cons ',action-symbol control-action-structure)
                    supported-control-actions-by-symbol)
	      control-action-structure)))))




;;; `prepare-modify-control-add'

(defun prepare-modify-control-add (modify-dialog-structure
                                    modify-control-structure component
                                    control-type-symbol control-value)
  (case control-type-symbol
    ((combo-box list-box checkable-list-box)
     (cond
       ((null control-value)
        (add-dialog-error "Missing CONTROL-VALUE." component))
       ((and control-value (not (evaluation-structure-p control-value)))
        (add-dialog-error "CONTROL-VALUE attribute was not a structure: ~NA" control-value))
       (t
        ;; This code is intended to update the internal representation on the G2
        ;; side.  This happens right before we send the new entries to TW to
        ;; have the widget updated.  If the update somehow fails on the TW side,
        ;; we do not get notified of it, and are then out of synch.  We hope
        ;; that won't happen.  -jv, 6/21/05
        (let ((lisp-struct (modify-existing-component modify-control-structure)))
          (setf (modify-control-value-text modify-control-structure)
                (case control-type-symbol
                  (combo-box
                   (combo-box-extract-text-for-control-value control-value lisp-struct 'add))
                  ((list-box checkable-list-box)
                   (list-box-extract-text-for-control-value control-value lisp-struct 'add control-type-symbol))))))))
    (text-box
     ;; Bug HQ-5062553; when doing an ADD on a text-box, we actually do a
     ;; replace.  This bug used to be much better hidden; we will fix it soon.
     ;; For now, keep the old behavior, with a new implementation.  -jv, 6/21/05
     (prepare-modify-control-replace modify-dialog-structure
                                     modify-control-structure component
                                     control-type-symbol control-value))
    (t
     ;; We should never get here.  This error should be caught by the prepare
     ;; dialog stage.  Catch it here, just in case.  -jv, 6/21/05
     (add-dialog-error
       "CONTROL-ACTION ADD is not supported for control type: ~NV"
       control-type-symbol))))



;;; Actions that change simple values `replace' replace the whole value;
;;; `add' adds a value

(def-control-action-type add 1
  :valid-control-types (combo-box list-box checkable-list-box
                                  ;; we do the wrong thing for text-box;
                                  ;; we replace the text instead of add to it.
                                  ;; Bug HQ-5062553
                                  text-box)
  :prepare-function prepare-modify-control-add)

(def-control-action-type replace 2
  :valid-control-types
  (progress-bar
    ;; tab-frame
    track-bar slider tree-view-combo-box combo-box image list-box
    checkable-list-box color-picker full-color-picker text-box masked-edit
    label spinner duration short-duration calendar time-of-day workspace
    group radio-button check-box push-button toggle-button
    ;; tabular-view grid-view integer quantity
    )
  :prepare-function prepare-modify-control-replace)


;;; Actions without control values

(def-control-action-type hide 3)
(def-control-action-type show 4)
(def-control-action-type enable 5)
(def-control-action-type disable 6)

(def-control-action-type check 7
  :valid-control-types (radio-button check-box toggle-button))
(def-control-action-type uncheck 8
  :valid-control-types (radio-button check-box toggle-button))

(def-control-action-type dropped-width 9
  :valid-control-types (combo-box color-picker tree-view-combo-box)
  :prepare-function dropped-width-prepare-modify-control)

(def-control-action-type dropped-height 10
  :valid-control-types (combo-box color-picker tree-view-combo-box)
  :prepare-function dropped-height-prepare-modify-control)

(def-control-action-type selected-tab 11
  :valid-control-types (tab-frame)
  :prepare-function selected-tab-prepare-modify-control)


;; Leaving space in control action numbers for more simple actions.


(defconstant default-dialog-update-type 'replace)



;;; Phases of dialog modification.
;;;
;;; Prepare phase - validates the specified arguments and
;;; collects any errors found.  See prepare-modify-dialog
;;; below.

;;; The `prepare-modify-control' performs error checking
;;; and preparation of an individual modify control structure

(defun prepare-modify-control (modify-dialog-structure
                                component
                                dialog)
  (cond ((not (evaluation-structure-p component))
         (add-dialog-error
           "Invalid control modify structure ~NA."
           component))
        (t
         (let* ((kb-control-id
                  (evaluation-structure-slot component
                                             'control-id
                                             nil))
                (control-action
                  (evaluation-structure-slot component
                                             'control-action
                                             default-dialog-update-type))
                (control-value
                  (evaluation-structure-slot component
                                             'control-value
                                             nil))
                (existing-component
                  (and kb-control-id
                       (or (evaluation-integer-p kb-control-id)
                           (evaluation-symbol-p kb-control-id))
                       (lookup-component-given-component-kb-id
                         kb-control-id
                         dialog)))
                (internal-control-id
                  (and existing-component
                       (dialog-component-internal-id existing-component)))
                (control-type-symbol
                  (and existing-component
                       (map-control-type-fixnum-to-symbol
                         (dialog-component-type existing-component)))))
           (cond ((null kb-control-id)
                  (add-dialog-error
                    "Missing CONTROL-ID attribute in control modification structure: ~NV"
                    component))
                 ((not (or (evaluation-integer-p kb-control-id)
                           (evaluation-symbol-p kb-control-id)))
                  (add-dialog-error
                    "CONTROL-ID attribute ~NA in control modification structure ~
                     must be an integer or a symbol"
                    kb-control-id))
                 ((not (evaluation-symbol-p control-action))
                  ;; This catches a NIL (i.e. none) as well. -dkuznick, 5/18/05
                  (add-dialog-error
                    "CONTROL-ACTION attribute ~NA in control modification ~
                     structure must be a symbol"
                    control-action))
                 ((and control-value
                       (not (evaluation-value-p control-value)))
                  (add-dialog-error
                    "CONTROL-VALUE attribute must be a value: ~NA"
                    control-value))
                 ((null (get-control-action-id-from-symbol control-action))
                  (add-dialog-error
                    "CONTROL-ACTION attribute in control modification structure ~
                     is unsupported symbol: ~NV"
                    control-action))
                 ((null existing-component)
                  (add-dialog-error
                    "Existing control is not found for CONTROL-ID: ~NV"
                    kb-control-id))

                 ((not (valid-control-action-p
                         control-action
                         control-type-symbol))
                  (add-dialog-error
                    "CONTROL-ACTION ~NV is not supported for control type: ~NV"
                    control-action
                    control-type-symbol)))
           (if (not (dialog-has-errors-p current-dialog-errors-structure))

               (let* ((modify-control-structure
                        (make-modify-control-structure))
                      (control-action-structure
                        (get-control-action-structure-from-symbol control-action))
                      (prepare-function
                        (modify-control-prepare-function control-action-structure)))
                 (setf (modify-internal-control-id
                         modify-control-structure)
                       internal-control-id)
                 (setf (modify-control-action
                         modify-control-structure)
                       control-action)
                 (setf (modify-existing-component
                         modify-control-structure)
                       existing-component)
                 (funcall prepare-function
                          modify-dialog-structure
                          modify-control-structure
                          component
                          control-type-symbol
                          control-value)
                 (add-modify-control-structure
                   modify-dialog-structure
                   modify-control-structure)))))))


;;; The `prepare-modify-dialog' performs error checking
;;; and preparation of the arguments that are passed to
;;; g2-ui-modify-dialog

(defun prepare-modify-dialog (modify-dialog-structure dialog-handle new-values g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (dialog (lookup-dialog-given-handle gensym-window dialog-handle))
         (dialog-components (and dialog
                                 (dynamic-dialog-components dialog))))
    (cond
      ((null new-values)
       (add-dialog-error
         "Modification sequence is none"
         dialog-handle))
      ((null dialog)
       (add-dialog-error
         "Attempt to modify dialog that is unknown: ~NV."
         dialog-handle))
      ((null dialog-components)
       (add-dialog-error
         "Attempt to modify dialog that has no components ~NV."
         dialog-handle))
      (t
       (setf (modify-dialog modify-dialog-structure) dialog)
       (setf (modify-gensym-window modify-dialog-structure) gensym-window)

       (loop for component being each evaluation-sequence-element
             of new-values
             do (prepare-modify-control
                  modify-dialog-structure
                  component
                  dialog))))))


;;; `perform-modify-control' phase - sends the ICP messages to perform the
;;; dialog modification

(defun perform-modify-control (modify-dialog-structure
                                modify-control-structure)
  (let* ((control-action
           (modify-control-action modify-control-structure))
         (perform-function
           (modify-control-perform-function
             (get-control-action-structure-from-symbol control-action))))
    (funcall perform-function modify-dialog-structure
             modify-control-structure)))


;;; `perform-modify-dialog'

(defun perform-modify-dialog (modify-dialog-structure)
  (let ((gensym-window (modify-gensym-window modify-dialog-structure))
        (dialog-handle
          (dynamic-dialog-handle ; dialog-component-internal-id
            (modify-dialog modify-dialog-structure)))
        (modify-control-structures
          (modify-control-structures modify-dialog-structure)))
    (with-icp-window (gensym-window)
      ;; This is a no-op.
      (send-icp-start-dialog-update gensym-window dialog-handle)
      ;; Update each control
      (loop for modify-control-structure in modify-control-structures
            do (perform-modify-control
                 modify-dialog-structure
                 modify-control-structure))
      ;; This is a no-op.
      (send-icp-end-dialog-update gensym-window dialog-handle))))


;;; `create-modify-dialog-structure'

(defun create-modify-dialog-structure ()
  (let ((modify-dialog-structure (make-modify-dialog-structure)))
    (setf (modify-dialog-errors modify-dialog-structure)
          (make-dialog-errors-structure))
    modify-dialog-structure))


;;; The system-procedure `g2-ui-modify-dialog' takes a dialog-handle
;;; and sequence of structures specifying actions to be applied to
;;; selected controls in the dialog.
;;;
;;; Attributes supported in the structure are:
;;; control-id: <integer>  (required, must be a valid control-id)
;;; control-action: <symbol> (optional, default is 'replace)
;;; control-value: <value>  (required if control-action is add or replace)
;;;
;;; Note that control-value will be any value type but for now only
;;; text is implemented.
;;;
;;; The system procedure sends all of the actions over to telewindows.
;;; The actions should be performed in a single transaction (if one
;;; action fails they should all fail).  This feature however has
;;; yet to be implemented on the TW side.

(defun-allowing-unwind-for-system-procedure g2-ui-modify-dialog (dialog-handle
								 new-values
								 g2-window)
  (let* ((modify-dialog-structure
           (create-modify-dialog-structure))
         (errors-structure
           (modify-dialog-errors modify-dialog-structure)))
    (with-collect-dialog-errors errors-structure
      (prepare-modify-dialog modify-dialog-structure
                             dialog-handle
                             new-values
                             g2-window))
    (cond ((dialog-has-errors-p errors-structure)
           (write-dialogs-stack-error nil
                                      (format-dialog-errors "Errors in G2-UI-MODIFY-CUSTOM-DIALOG"
                                                            errors-structure)
                                      (reclaim-modify-dialog-structure modify-dialog-structure)))
          (t
           (perform-modify-dialog modify-dialog-structure)
           (when echo-dialog-spec-p
             (stderr-message "start g2-ui-modify-dialog(~NV, ~NV, ~NA)"
                             dialog-handle new-values g2-window))
           (reclaim-modify-dialog-structure modify-dialog-structure)
           (reclaim-evaluation-sequence new-values)))))


(defun lock-dialog (gensym-window dialog-handle locked-p)
  (with-icp-window (gensym-window)
    (send-icp-set-dialog-locked gensym-window dialog-handle locked-p)))

;;; The system-procedure `g2-ui-lock-dialog' makes native dialog locked if 
;;; full-lock-p is true.
(defun-for-system-procedure g2-ui-lock-dialog (g2-window dialog-handle full-lock-p)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (dialog (lookup-dialog-given-handle gensym-window dialog-handle)))
    (cond
      ((null dialog)
       (dialogs-stack-error dialog "Attempt to query a dialog id which does ~
                                    not correspond to a dialog"))
      (t
       (lock-dialog
         gensym-window
         dialog-handle
         (and (evaluation-truth-value-p full-lock-p)
              (evaluation-truth-value-is-true-p full-lock-p)))))))


;;;; Tabular Views


(def-concept tabular-views)

;; Declare some tabular-view attributes. This simply prevents warnings about
;; unrecognized attributes in `add-component-to-custom-dialog'.

(def-dialog-component-attribute allow-sort-rows (new-value lisp-struct :type truth-value))
(def-dialog-component-attribute gridlines (new-value lisp-struct :type truth-value))
(def-dialog-component-attribute row-height (new-value lisp-struct :type integer))
(def-dialog-component-attribute text-color (new-value lisp-struct :type symbol))


(def-control-action-type remove-all-rows 100
  :valid-control-types (tabular-view)
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type remove-all-selected-rows 101
  :valid-control-types (tabular-view)
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type add-rows 200
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type remove-rows 201
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type replace-cells 202
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type replace-rows 203
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type selected-rows 204
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type add-columns 205          ; New for 8.3a0
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type remove-columns 206       ; New for 8.3b0
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type sort-rows 207	          ; New for 8.4r0
  :valid-control-types (tabular-view)
  :perform-function generic-perform-modify-tabular-view)

;;added by SoftServe

(def-control-action-type add-rows-to-top 208
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

;;end of SoftServe changes

;;added by SoftServe
(def-control-action-type font-size-change 209
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)
;;end of SoftServe changes

(def-control-action-type change-sort 210
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

(def-control-action-type deselect-rows 211
  :valid-control-types (tabular-view)
  :prepare-function generic-prepare-tabular-view-modify-control
  :perform-function generic-perform-modify-tabular-view)

;;; `tabular-view-error-' functions

(defun tabular-view-error-columns-not-sequence (dialog)
  (dialogs-stack-error
    dialog
    "COLUMNS attribute must be a sequence."))

(defun tabular-view-error-rows-not-sequence (dialog)
  (dialogs-stack-error
    dialog
    "ROWS attribute must be a sequence."))

(defun tabular-view-error-selected-rows-not-sequence (dialog)
  (dialogs-stack-error
    dialog
    "SELECTED-ROWS attribute must be a sequence."))

(defun tabular-view-error-no-control-value (modify-structure)
  (add-dialog-error
     "Missing CONTROL-VALUE in TABULAR-VIEW for ~a action."
     (modify-control-action modify-structure)))

(defun tabular-view-error-control-value-not-sequence (modify-structure)
  (add-dialog-error
     "CONTROL-VALUE of TABULAR-VIEW must be a sequence for ~a action."
     (modify-control-action modify-structure)))


(defun tabular-view-currently-selected-rows (component)
  (let* ((dialog (dialog-component-parent-dialog component))
	 (dialog-view? (dynamic-dialog-view? dialog))
	 (gensym-window? (and dialog-view? ; Paranoia
			      (native-window-gensym-window dialog-view?)))
	 (handle (dialog-component-g2-representation? component))
	 (tbv? (find-native-window gensym-window? handle 'g2-tabular-view)))
    (cond (tbv?
	   (tabular-view-selected-rows-as-sequence tbv?))
	  (t				; Can't happen?
	   (allocate-evaluation-sequence nil)))))

(defun tabular-view-updated-control-value (component)
  ;; structure(columns: sequence(<text>*),
  ;;           rows:    sequence(<row-structure>*),
  ;;           selected-rows: sequence(<integer>*))
  (allocate-evaluation-structure
    (eval-list 'selected-rows
               (tabular-view-currently-selected-rows component))))


;;; `sanity-check-tabular-view-control-value' checks some aspects of the
;;; control-value for a tabular-view in a dialog. If they are not correct then
;;; it throws a stack error. The tabular-view code does this checking, too; this
;;; preflight simply provides some more user-friendly error messages.

(defun sanity-check-tabular-view-control-value (dialog control-value)
  (let ((columns (evaluation-structure-slot control-value 'columns))
	(rows (evaluation-structure-slot control-value 'rows))
	(selected-rows (evaluation-structure-slot control-value 'selected-rows)))
    (cond
      ((and columns (not (evaluation-sequence-p columns)))
       (tabular-view-error-columns-not-sequence dialog))
      ((and rows (not (evaluation-sequence-p rows)))
       (tabular-view-error-rows-not-sequence dialog))
      ((and selected-rows (not (evaluation-sequence-p selected-rows)))
       (tabular-view-error-selected-rows-not-sequence dialog)))))


(defun add-tabular-view-to-dialog (lisp-struct dialog gensym-window)
  (when (tabular-views-p gensym-window)	; For the new 8.3b0 implementation.
    (let ((evalue (dialog-component-evaluation-structure lisp-struct))
	  (control-value (dialog-component-original-value? lisp-struct)))

      (sanity-check-tabular-view-control-value dialog control-value)

      (let ((tbv (create-tabular-view-in-dialog
		   gensym-window
		   (dynamic-dialog-handle dialog)
		   (dialog-component-internal-id lisp-struct)
		   (evaluation-structure-slot control-value 'columns)
		   (evaluation-structure-slot control-value 'rows)
		   (evaluation-structure-slot control-value 'selected-rows)
		   (evaluation-structure-slot control-value 'sort-column)
		   (evaluation-structure-slot control-value 'sorting-order)
		   (evaluation-structure-slot evalue 'row-height)
		   (evaluation-structure-slot evalue 'text-color)
		   (evaluation-structure-slot evalue 'background-color)
		   (evaluation-structure-slot evalue 'gridlines)
		   (evaluation-structure-slot evalue 'gridline-color)
		   (evaluation-structure-slot evalue 'allow-sort-rows)
		   (evaluation-structure-slot evalue 'single-selection))))
	(setf (dialog-component-g2-representation? lisp-struct) (native-window-handle tbv)
	      (native-view-dialog-component? tbv) lisp-struct)
	tbv))))


;;; `generic-prepare-tabular-view-modify-control' is used as the "prepare"
;;; function for the tabular-view related actions below.

(defun-void generic-prepare-tabular-view-modify-control
    (modify-dialog-structure control-modify-structure
                             component
                             control-type-symbol
                             control-value)
  (declare (ignore modify-dialog-structure)
           (ignore control-type-symbol)
           (ignore component))
  (cond
    ((null control-value)
     (tabular-view-error-no-control-value control-modify-structure))
    ((not (evaluation-sequence-p control-value))
     (tabular-view-error-control-value-not-sequence control-modify-structure))
    (t
     (setf (modify-control-value-sequence control-modify-structure)
           (copy-evaluation-sequence
             control-value)))))

(defun generic-perform-modify-tabular-view (modify-dialog-structure modify-control-structure)
  (let* ((gensym-window (modify-gensym-window modify-dialog-structure))
	 (component (modify-existing-component modify-control-structure))
	 (handle (dialog-component-g2-representation? component))
	 (tbv (find-native-view-or-stack-error gensym-window handle 'g2-tabular-view))
	 (action (modify-control-action modify-control-structure))
	 (ev-arg (modify-control-value-sequence modify-control-structure)))
    (manage-tabular-view-in-dialog tbv action ev-arg)))


;;;; Debugging Code


;;; `map-dialog-response-integer-to-symbol' - for printing the symbol back to
;;; the user.  Not used in production.  Should be less duplication.

#+echo-dialog-send
(defun map-dialog-response-integer-to-symbol (response-integer)
  (case response-integer
    (dialog-response-no-action
     'ignore)
    (dialog
     'ok-response-respond-all-and-ok)
    (dialog-response-cancel
     'cancel)
    (dialog-response-just-respond
     'respond)
    (dialog-response-respond-all
     'respond-with-all-data)
    (dialog-response-respond-and-ok
     'ok-with-just-my-data)
    (dialog-response-ok
     'ok-without-data)))


;;; `dbg-output-start-dialog'

#+echo-dialog-send
(defun dbg-output-start-dialog (new-dialog width height title modal-p mdi-child-p)
  (stderr-message "starting dialog ~s; width = ~s, height = ~s, title = ~s"
                  new-dialog width height title)
  (stderr-message " ~s components, ~A"
                  (dynamic-dialog-count-components new-dialog)
                  (if mdi-child-p
                      "MDI_CHILD"
                      (if modal-p
                          "MODAL"
                          "MODELESS"))))


;;; `dbg-output-dialog-component-for-c'

#+echo-dialog-send
(defun dbg-output-dialog-component-for-c (lisp-struct)
  (let ((*abbreviate-wide-strings-for-legibility* nil))
    (stderr-message "*** DIALOG-COMPONENT ***")
    (stderr-message "dialog-component-type = ~s"
                    (map-control-type-fixnum-to-symbol (dialog-component-type lisp-struct)))
    (stderr-message "dialog-kb-internal-id = ~s"
                    (dialog-component-kb-id lisp-struct))
    (stderr-message "dialog-component-internal-id = ~s"
                    (dialog-component-internal-id lisp-struct))
    (stderr-message "dialog-component-value? [length ~d] = ~s"
                    (text-string-length (dialog-component-value? lisp-struct))
                    (dialog-component-value? lisp-struct))
    (stderr-message "dialog-component-left? = ~s"
                    (dialog-component-left? lisp-struct))
    (stderr-message "dialog-component-top? = ~s"
                    (dialog-component-top? lisp-struct))
    (stderr-message "dialog-component-height? = ~s"
                    (dialog-component-height? lisp-struct))
    (stderr-message "dialog-component-width? = ~s"
                    (dialog-component-width? lisp-struct))
    (stderr-message "dialog-component-style (high) = 0x~x"
                    (car (dialog-component-style lisp-struct)))
    (stderr-message "dialog-component-style (low) = 0x~x"
                    (cdr (dialog-component-style lisp-struct)))
    (stderr-message "dialog-component-parent-kb-id? = ~s"
                    (dialog-component-parent-kb-id? lisp-struct))
    (stderr-message "dialog-component-parent-text? = ~s"
                    (dialog-component-parent-text? lisp-struct))
    (stderr-message "dialog-component-response-action = ~s"
                    (map-dialog-response-integer-to-symbol
                      (dialog-component-response-action lisp-struct)))
    (stderr-message "dialog-component-parent-dialog = ~NF"
                    (dialog-component-parent-dialog lisp-struct))
    (stderr-message "dialog-component-parent-id = ~s"
                    (dialog-component-parent-id lisp-struct))
    (stderr-message "dialog-component-evaluation-structure = ~NV"
                    (dialog-component-evaluation-structure lisp-struct))
    (stderr-message "dialog-component-original-value? = ~NV"
                    (dialog-component-original-value? lisp-struct))
    (stderr-message "dialog-component-incoming-value? = ~NV"
                    (dialog-component-incoming-value? lisp-struct))
    (stderr-message "dialog-component-g2-style = ~s"
                    (dialog-component-g2-style lisp-struct))
    (stderr-message "dialog-component-tabstop-index? = ~s"
                    (dialog-component-tabstop-index? lisp-struct))
    (stderr-message "dialog-component-g2-representation? = ~NF"
                    (dialog-component-g2-representation? lisp-struct))
    (when (eq 'grid-view (map-control-type-fixnum-to-symbol
                           (dialog-component-type lisp-struct)))
      (stderr-message "grid-view-row-strings = ~NF"
                      (lisp-grid-view-row-strings
                        (dialog-component-g2-representation? lisp-struct))))
    (stderr-message "------------------------------------------------------------")
    ))


;;; `dbg-echo-dialog-update'

#+echo-dialog-send
(defun dbg-echo-dialog-update (dialog-id internal-control-id update-text)
  (let ((*abbreviate-wide-strings-for-legibility* nil))
    (stderr-message "*** DIALOG-UPDATE ***")
    (stderr-message "dialog-id = ~s" dialog-id)
    (stderr-message "control-id = ~s" internal-control-id)
    (stderr-message "update-text = ~s" update-text)
    (stderr-message "------------------------------------------------------------")
  ))


;;; `dbg-output-finish-dialog'

#+echo-dialog-send
(defun dbg-output-finish-dialog (gensym-window new-dialog x-position y-position
                                               mdi-child-p dock? neighbor? icon? resizable-p)
  (declare (ignore gensym-window new-dialog x-position y-position
                   mdi-child-p neighbor? icon? resizable-p))
  (stderr-message "finishing dialog; dock? = ~s" dock?))


;;; `dbg-output-grid-view-cells'

#+echo-dialog-send
(defun dbg-output-grid-view-cells (dialog-handle control-id row-string)
  (declare (ignore dialog-handle))
  (let ((*abbreviate-wide-strings-for-legibility* nil))
    (stderr-message "*** GRID-VIEW-CELLS ***")
    (stderr-message "control-id = ~s" control-id)
    (stderr-message "row-string [length ~d] = ~s"
                    (text-string-length row-string) row-string)))


;;; `dbg-output-dialog-update'

#+echo-dialog-send
(defun dbg-output-dialog-update (component new-value)
  (let ((*abbreviate-wide-strings-for-legibility* nil))
    (stderr-message "incoming string on control ~s: ~s" component new-value)))

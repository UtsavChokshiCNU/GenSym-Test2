;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module EDIT1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson and Mark H. David






;;;; Forward References in EDIT

(declare-forward-references

  (note-kb-state-change-to-slot-by-saving-text function kb-save2)
  (current-kb-serial-number                    variable kb-save2)

  (find-base-plane-in-stack-of-coupled-image-planes function) ; RUN
  (run-top-level-event-handler        function run)
  (find-object-near-workstation-event function run)

  (close-pending-procedure-signature-workspaces-on-close variable)
  (get-built-in-function-argument-names function)

  (reason-for-bad-parse-as-string             function grammar0)

  (workstation-for-g2-window?-function        function)
  (embedded-rule-p                            function)
  (enter-dialog                               function)
  (confirm-or-cancel                          function)
  (enter-button-down-context                  function)

  (non-menu-choice-permitted-p function)

  (evaluation-true-value                variable sets)
  (evaluation-false-value               variable sets)
  (enter-mouse-watch-state              function commands0)
  (enter-edit-menu-state                function commands0)
  (color-or-metacolor-p        function grammar4)

  (recompile-cell-array function)        ; CELLS

  (restrict-destabilization-p function) ; COMP-UTILS

  (first-text-region-in-edit-state function)        ; in EDIT2
  (find-next-instance-of-search-string function)
  (paste-from-current-scrap-if-any function)
  (parsing-context-p-function function)
  (request-paste-availability-for-editor function)
  (text-string-matches-current-scrap-p function)

  (coerce-text-region-to-scrap function edit2)
  (get-selected-text-region-for-edit-box function edit2)
  (text-can-be-pasted-in-current-workstation-p function edit2)
  (request-paste-for-editor function edit2)
  (change-edit-box-cursor-position function edit2)
  (make-edit-subcommand-menu function edit2)
  (enable-or-disable-edit-end-and-update-buttons function edit2)
  (initialize-edit-subcommand-menu function edit2)
  (change-edit-box function edit2)
  (do-trial-kfep-conversion function edit2)
  (undo-or-redo-edit-possible-p function edit2)
  (undo-or-redo-edit function edit2)
  (unconvert-kfep-conversion-text-region function edit2)
  (accept-kfep-conversion function edit2)
  (enter-kana-conversion-mode function edit2)
  (exit-kfep-mode-if-necessary function edit2)
  (skip-kfep-conversion function edit2)
  (expand-or-shrink-kfep-conversion-text-region function edit2)
  (find-position-adjacent-to-end-of-kfep-conversion-text-region function edit2)
  (enter-subcommand-context function edit2)
  (select-text-region-in-scrap function edit2)
  (scrap-text-region function edit2)
  (enable-or-disable-subcommand function edit2)
  (enter-escape-context function edit2)
  (enable-or-disable-radio-button-subcommand function edit2)
  (update-edit-operation-subcommands-in-current-editor function)
  (disable-text-region-operation-subcommands-in-current-editor function)
  (compute-distance-of-text-line-from-top function edit2)
  (handle-parsing-or-compilation-problem function edit2)
  (update-authors-and-time-of-frame-edit function edit2)
  (find-position-in-text-given-image-plane function edit2)
  (find-position-in-text function edit2)
  (paste-text-string function edit2)
  (incomplete-phrases-for-previous-token function edit2)
  (get-scrap-if-any function)
  (there-is-a-scrap-p function)
  (in-recompile-item-p variable)        ; edit2

  (update-change-log-attribute                function change-log)

  #+java-export-facilities
  (java-tokenizer            variable JAVA2)
  #+java-export-facilities
  (java-editing-category-p   function JAVA2)
  (argument-list-description-function   function proc-utils)
  (returned-values-description-function function proc-utils)
  (procedure-method-name-function function proc-utils)
  (reclaim-item-and-fsn-list function)
  (reason-permanent-items-module-is-not-editable function)
  (reason-permanent-items-attribute-is-not-editable function)
  (compile-item-or-datum-or-no-item-attribute-for-slot function)
  (get-evaluation-value-for-attribute function)
  (conclude-into-virtual-attribute-component function)

  (native-editor-replace-text function)        ; COMMANDS2
  (native-editor-display-notification function)
  (native-editor-show-completions function)
  (native-editor-already-updated variable)
  (suspend-native-editor function)
  (resume-native-editor function)
  (g2-list-insert-at-beginning function LISTS)
  (make-transient-item function STACK-ACTS))





;;;; Text Marking




;;; `Text-Marking' is a modal workstation context that focuses on a text region.
;;; It takes an image-plane and a text region.  It allows the user to drag out
;;; that text region.  It aborts if the user aborts or the text region (i.e. the
;;; focus) is reclaimed.  It returns the final event's mouse-pointer.

(define-workstation-context text-marking (workstation-context-with-selection-focus)
  :selection-style top-level-with-selection-focus-is-selection-style
  :parent nil
  :modal t
  :state-variables (edit-workspace-for-text-being-marked)
  :constructor (make-text-marking-state
                 (image-plane-with-selection-focus-of-workstation-context
                   reference-number-of-image-plane
                   block-with-selection-focus-of-workstation-context
                   edit-workspace-for-text-being-marked))
  :keymap ((<mouse-up> mouse-up-in-text-marking)
           (<mouse-motion> mouse-motion-in-text-marking)
           (<standard-abort-keys> abort-workstation-context)))


;;; `Valid-workstation-context-p for text-marking' checks that the
;;; edit-workspace hasn't been reclaimed.  Other necessary validity checking is
;;; performed by superior methods, which this invokes.  This keeps the marking
;;; context from persisting after the edit workspace for the editor from which
;;; this was launched has been deleted, either directly or as a result of the
;;; frame being edited being deleted. [Fixes bug in all G2 versions prior to for
;;; G2 4.0 Rev. 2 (MHD 9/28/95)]

(def-structure-method valid-workstation-context-p (text-marking-state)
  (and (funcall-superior-method text-marking-state)
       (valid-block-in-workstation-context-p
         (edit-workspace-for-text-being-marked text-marking-state)
         text-marking-state)))




;;; `Enter-text-marking-state' is used in an edit state to as follows:
;;;   (with-workstation-context-continuation ('insert-selected-text-if-any? nil nil)
;;;          (enter-text-marking-state text-region image-plane edit-workspace))

(defun enter-text-marking-state (text-region image-plane edit-workspace)
  (let ((text-marking-state
          (make-text-marking-state
            image-plane
            (serial-number-of-image-plane image-plane)
            text-region
            edit-workspace)))
    (enter-context-in-current-workstation 'text-marking text-marking-state t)
    text-marking-state))

#+comment
(def-structure-method clean-up-workstation-context (text-marking-state)
    (funcall-superior-method text-marking-state))

(define-event-handler mouse-motion-in-text-marking
    ((text-marking-state workstation-context-specifics)
     mouse-pointer
     (x-in-window x-in-window)
     (y-in-window y-in-window)
     (image-plane image-plane-of-selection-focus)
     (text-region block-of-selection-focus))
  (let* ((superblock-of-text-region (superblock? text-region))
         (table?
           (if (row-index-for-text-region-cell? text-region)
               superblock-of-text-region)))
    (multiple-value-bind (line-index-for-new-free-end character-index-for-new-free-end)
        (find-position-in-text-given-image-plane
          superblock-of-text-region
          (if (null table?) superblock-of-text-region)
          (if table?
              (get-table-cell
                table?
                (row-index-for-text-region-cell? text-region)
                (column-index-for-text-region-cell? text-region)))
          (left-edge-of-block text-region)
          (top-edge-of-block text-region)
          t
          image-plane
          x-in-window
          y-in-window
          nil nil nil)
      (update-text-region
        text-region
        line-index-for-new-free-end character-index-for-new-free-end)
      ;; Scroll Free end into view, as necessary.
      (let* ((frame-transforms-of-block?
               (frame-transforms-of-block superblock-of-text-region)))
        (when frame-transforms-of-block?
          (scroll-text-into-view
            (cdr (assq image-plane frame-transforms-of-block?))
            line-index-for-new-free-end
            character-index-for-new-free-end))))))

;; The selection style should have focused on the text region and bound these
;; into the mouse pointer, but doesn't yet. - ben 3/30/94

(define-event-handler mouse-up-in-text-marking (mouse-pointer)
  (mouse-motion-in-text-marking mouse-pointer)
  (return-from-current-workstation-context 'text-marking :ok mouse-pointer))






;;;; Button Menus


;;; Editor workspaces, and some other things, can have subblocks that
;;; are subclasses of menus.  These are used to create a set of push
;;; buttons for selecting tokens, classes, characters, as well as for
;;; the undo/cancel/etc. buttons.  Collectively these are known as
;;; button menus,  but they do not share a common superior class.

;;; They have similar mouse pointer behavior.  When clicked on a
;;; subtype of a menu-button-spot is created, and this will identify
;;; the button selected.  If the click is not directly over a button
;;; then a workspace background spot is generated.



;;; A `button-menu-spot' spot represents the entire button menu.
;;; it appears above the image plane spot and below the menu-button
;;; spot.  It is an input-table spot.

(def-spot button-menu-spot
    :include input-table-spot :innermost-spot-p nil :abstract-type nil)



;;; A `menu-button-spot' is an abstract type generated when the mouse points
;;; button in a the various subclasses of menus that are used to implement push
;;; buttons, subcommand-menu, and token-menu, for example.  The slot
;;; subcommand-button-text-cell?  is bound to the actual text-cell in the table
;;; representing that button.  This is a top level spot.  The enclosing spot
;;; will be a workspace-spot.  The frame-represented? will be the
;;; subcommand-menu.

(def-spot menu-button-spot
    :slots ()
    :enclosing-spot-type button-menu-spot
    :innermost-spot-p t
    :abstract-type t
    :type-of-frame-represented table)

;;; This is refined to have a differing spot for each kind of menu, one
;;; for  button-spot for each of them.  These are
;;;     `subcommand-menu-button-spot'
;;;        `catagory-menu-button-spot'
;;;        `token-menu-button-spot'
;;;        `replacement-token-menu-button-spot'
;;;        `pathname-component-token-menu-button-spot'
;;;        `kfep-conversion-choice-menu-button-spot'

(def-spot subcommand-menu-button-spot
    :include menu-button-spot
    :abstract-type nil
    :type-of-frame-represented subcommand-menu)
(def-spot category-menu-button-spot
    :include menu-button-spot
    :abstract-type nil
    :type-of-frame-represented category-menu)
(def-spot token-menu-button-spot
    :include menu-button-spot
    :abstract-type nil
    :type-of-frame-represented token-menu)
(def-spot replacement-token-menu-button-spot
    :include menu-button-spot
    :abstract-type nil
    :type-of-frame-represented replacement-token-menu)
(def-spot character-sequence-token-menu-button-spot
    :include menu-button-spot
    :abstract-type nil
    :type-of-frame-represented replacement-token-menu)
(def-spot pathname-component-token-menu-button-spot
    :include menu-button-spot
    :abstract-type nil
    :type-of-frame-represented replacement-token-menu)
(def-spot kfep-conversion-choice-menu-button-spot
    :include menu-button-spot
    :abstract-type nil
    :type-of-frame-represented kfep-conversion-choice-menu)




;;; `Generate-spot-for-button-menu' is used to implement the generate-spot
;;; method for these various kinds of methods button menus.  It takes a
;;; menu-button-spot that will be used if the mouse actually points to a visible
;;; button.  Otherwise that spot will be reclaimed, and a workspace background
;;; spot is generated.

(defun generate-spot-for-button-menu
    (suggested-menu-button-spot button-menu mouse-pointer)
  ;; First push a table spot to enclose us.
  (generate-spot-for-pure-input-table button-menu
                                 mouse-pointer
                                 (make-button-menu-spot))
  ;; Then push a the menu button spot.
  (with-mouse-pointer-bindings (&optional
                                 (table-cell? cell-of-table)
                                 (text-cell-plist? text-plist))
      mouse-pointer
    (cond
      ;; Push wks background if invisible or malformed
      ((or (null table-cell?)
           (if (cell-is-block-p table-cell?)
               (and (frame-of-class-p table-cell? 'icon-cell)
                    (let ((s (first-subblock table-cell?)))
                      (and s
                           (frame-of-class-p s 'editor-subcommand-button)
                           (get-slot-value
                             s 'editor-subcommand-disabled-p)))) ; fwd. ref.!
               (or (null text-cell-plist?) ;; malformed
                   ;; invisible
                   (and (memq (getf text-cell-plist? 'line-color)
                              '(transparent background))
                        (memq (getf text-cell-plist? 'background-color)
                              '(transparent background))))))
       (reclaim-structure suggested-menu-button-spot)
       (push-last-spot mouse-pointer (make-workspace-background-spot) nil))
      (t
       (push-last-spot mouse-pointer suggested-menu-button-spot button-menu)))))

;; Note this can push a stack of table spot followed by workspace
;; background, which is racy, but I don't have something to pop
;; the stack and I need the info the table spot provides.




;;;; Edit Parameters



(def-system-frame editor-parameters edit1

  (maximum-number-of-names-for-a-menu 7                ; used in PARSE; see alias below
    vector-slot system (type positive-integer))        ; allow to be 0?

  (object-name-menus-in-upper-case? nil                ; used in PARSE
    vector-slot system (type yes-or-no))

  (show-partially-visible-lines-in-edit-box? t        ; used in BOXES
    vector-slot system (type nil))                ; (type yes-or-no) -- not in Alpha!
                                                ;   (MHD 8/3/89)
  (number-of-spaces-to-insert-on-a-tab                ; was 8 (MHD 8/3/89)
    4 vector-slot system (type non-negative-integer)) ; new in 5.0: 0 means "just insert an (ASCII) tab"
                                                  ; consider making 0 the default! (MHD 7/5/96)
  (maximum-number-of-undos-to-remember
    100 vector-slot system (type positive-integer)
    ; do-not-save                                ; TEMPORARY FOR 2.0 BETA0 COMPATIBILITY (11/27/89)!
    ;; ^-- commented out, for 3.0, but not in time for 2.1 -- Whoooops! (MHD 2/27/91)
    )

  (maximum-number-of-scraps-to-keep                ; Added Today. (MHD 2/27/91)
    50 lookup-slot system (type positive-integer))        ; vector-slot later!!
                                                ; 200? (FEF)  20? (SF)  25? (SAS)

;  (kanji-conversion-text-region-highlight-color; color of text to be converted
;    foreground vector-slot system (type color)        ; yellow?
;    do-not-save)                                ; save later!? show only if kfep capability?
;  (kanji-conversion-choice-highlight-color        ; color of a not-yet-accepted conversion
;    foreground vector-slot system (type color)        ; orange?
;    do-not-save)                                ; save later!? show only if kfep capability?

  (minimum-width-for-edit-box
    0 vector-slot system (type non-negative-integer)
    ; do-not-save                                ; REVIEW! TEMPORARY! (MHD 4/1/91)
                                                ; Under review! -- DO SOMETHING (MHD 5/15/91)
                                                ; -- OK: now seen by user and saved (MHD 8/24/91)
    )

  (minimum-height-for-edit-box                        ; not seen by user -- not saved; review for
                                                ;   future release! (MHD 8/24/91)
    0 vector-slot system (type nil)
    do-not-save)                                ; REVIEW! TEMPORARY! (MHD 4/1/91)
                                                ; Under review! -- DO SOMETHING (MHD 5/15/91)



  ;; The following take "edit entry keyspecs".  These can be either the
  ;; keystrokes \ or ~, or any other keystrokes.  For compatibility, and for
  ;; convenience, the keystroke-for-jis-code-entry and
  ;; keystroke-for-ksc-code-entry are both \.  If they are the same, then you
  ;; can only guarantee that you'll get KSC (Korean) is if KOREAN is the current
  ;; language, and the only way to get JIS (Japanese) is if JAPANESE is the
  ;; current language.  Otherwise, the order in which one is chosen is based on
  ;; the order in which they appear in the OK object at authorization time.
  ;;
  ;; The keystroke-for-jis-code-entry and the keystroke-for-ksc-code-entry
  ;; always both allow their first character to be either themselves (e.g., \,
  ;; by default) or keystroke-for-special-character-entry (e.g., ~, by default),
  ;; and, if that is a legal character to enter in text, pass that through as a
  ;; text character to insert.
  ;;
  ;; In other words, in the default configuration, you
  ;;
  ;;   enter \ followed by \ in order to insert the \ character
  ;;   at the cursor;
  ;;
  ;;   you enter \ followed by ~ to enter ~ at the cursor;
  ;;
  ;;   you enter \ followed by four hex digits to enter either a JIS or KSC
  ;;   character at the cursor;
  ;;
  ;;   you enter a ~ followed by another character (defined for the special
  ;;   entry context, q.v.) in order to enter a special (or European) character,
  ;;   or to add a diacritic to some base character preceeding the cursor.

  (keystroke-for-jis-code-entry                ; \2121 => JIS character 2121 (hex) (Japanese)
    \\ vector-slot system (type nil) do-not-save) ; (type edit-entry-keyspec)!
  (keystroke-for-ksc-code-entry                ; \2121 => KSC character 2121 (hex) (Korean)
    \\ vector-slot system (type nil) do-not-save)
  ;; chinese!
  (keystroke-for-special-character-entry ; ~* => <centerdot>
    \~ vector-slot system (type nil) do-not-save)


  ;; The slot `keep-edit-history??' enables keeping track of when
  ;; changes are made, and by whom.  When true, edit history recording
  ;; is enabled for blocks that have a visible

  (keep-edit-history?                        ; turning this on enables storing
    t                                        ;   of the author(s) and date of
    (type yes-or-no)                        ;   a last edit -- only available
    vector-slot system save                ;   right now for definition and
    )                                        ;   definitional subclasses


  (attributes-to-edit-using-multiline-editor
    (text item-configuration
          ;; definitions
          instance-configuration
          class-specific-attributes attribute-initializations
          ;; object definitions
          attribute-displays
          stubs
          icon-description)
    (type nil)                                ; remove after a while --
                                        ; this lived for a few weeks
                                        ; in 4.0 Alpha -- removed as
                                        ; visible type today.
                                        ; (MHD 8/15/94)
;    (type attributes-to-edit-using-multiline-editor)
    vector-slot system save)

  (pop-up-edit-operations-menu                ; if true, automatically popping
    t                                        ;   up the edit operations menu
    (type yes-or-no)                        ;   is done, which has been the
    vector-slot system save)                ;   default; otherwise, not

  (buttons-for-edit-operations                ; if true, automatically popping
    nil                                        ;   up the edit operations menu
    (type yes-or-no)                        ;   is done, which has not been
    vector-slot system save)                ;   the default (not available)

  (show-procedure-signatures?
    t
    (type yes-or-no)
    vector-slot system save)

  (smart-space-insertion                ; Whether to "handle-spaces-intelligently?"
    t                                        ; Added for 8.1a0 -fmw, 1/14/05
    (type yes-or-no)
    vector-slot system save)

  (prefer-native-editor                        ; If the native editor isn't supported on a
    t                                        ; given window, classic is used regardless.
    (type yes-or-no)                        ; Added for 8.1b0 -fmw, 3/24/05
    vector-slot system save))


(defvar override-preferred-editor nil)        ; If non-NIL, overrides editor-parameters

;; Only present in 8.1a0 or internal 8.1b0 KBs saved before 3/24/05.
(def-absent-slot-putter preferred-editor (editor-parameters value)
  (change-slot-value editor-parameters 'prefer-native-editor (eq value 'native)))

(defun prefer-native-editor-p (gensym-window)
  (declare (ignore gensym-window))        ; per-user-preferences, someday.
  (case override-preferred-editor
    (classic nil)
    (native t)
    (t (prefer-native-editor editor-parameters))))


;; 3 bugs/deficiencies:
;;
;;   (1) NONE is not handled! (workaround -- type in foo);
;;
;;   (2) class-qualified attribute names aren't handled;
;;
;;   (3) you can't restrict to certain classes, say the TEXT of
;;       procedures and messages, but not rules -- so, allow classes
;;       to be specified along with the attribute names.
;;
;; (MHD 7/22/94)

(def-simplifying-slot-value-compiler attributes-to-edit-using-multiline-editor
    (parse-result)
  (cdr parse-result))

(add-grammar-rules-for-list
  'attributes-to-edit-using-multiline-editor
  'symbol
  '\, nil 'none nil)

(def-slot-value-writer attributes-to-edit-using-multiline-editor (value)
  (write-symbol-list value '\, nil 'none))





(define-slot-alias author-recording-enabled? keep-edit-history? editor-parameters)

;; New slot/name for 4.0.  Review name! (MHD 4/12/94)
;; I swapped the orer of the first two arguments here, which I assume is
;; as was intended.  -fmw, 4/23/94


(define-slot-alias maximum-number-of-names-in-menus maximum-number-of-names-for-a-menu
  editor-parameters)

;; When a "real" tab facility is implemented, get rid of the
;; number-of-spaces-to-insert-on-a-tab parameter!



;; (defparameter height-for-kanji-conversion-choices 95)        ; include as edit parameter?
;; Change: make this now be a slot in edit-state.  Defaults to 95. (MHD 10/8/96)








;;;; Edit States and Edit Workspaces



;;; Edit state is defined in module PARSE, rather than here, because certain of its
;;; slots must be accessed prior to module EDIT for allocation purposes.



;;; An `edit workspace' holds both the text being edited, menus of tokens and
;;; token categories, and action menus, as appropriate.

;;; It is assumed below that subblocks of edit workspaces cannot be individually
;;; deleted or moved out of the workspace by the user.  The selection action
;;; choice menu must reflect this and help to enforce this.  For example, if the
;;; edit box is moved by the user, it should be put in transit as a "confined
;;; object" (a la blocks with external connections).
;;;
;;; It is assumed that edit workspace can only appear on one image plane, and
;;; that they are deleted when their image plane is deleted.  This assumption
;;; is partially relied on by the edit-in-place interfacing feature described
;;; as follows.
;;;
;;; Since edit workspaces need to ride on top of other workspace at times, to
;;; implement the "edit-in-place" feature, they have slots that hook into the
;;; image-plane-event handling facilities (in RUN): `riding-workspace-x-offset?'
;;; and `riding-workspace-y-offset?', when non-nil, are set with the desired
;;; offset in workspace units of the origin of the riding workspace/image
;;; plane.  When image plane actions are performed, they look at these slots,
;;; and, if they are non-nil, they maintain the offset as best they can.  (If
;;; they are nil, they determine the offset as best they can based on their
;;; preexising relationship, but that interpretation subjects the riding
;;; image plane to drift due to roundoff error in the scaling.)  See RUN for
;;; further information.

(def-class (edit-workspace temporary-workspace)
  (workspace-margin 10)                                ; margin had been defaulted
                                                ;   until now. (MHD 8/30/89)


  (what-this-is-a-menu-for?                        ; change "menu" => "menu-or-edit-workspace"!!
    nil lookup-slot system                        ;   here and everywhere!
    no-accessor)                                ; shares lookup slot with menus


  (riding-workspace-x-offset?                ; used by the edit-in-place/riding-image-plane
    nil vector-slot system (type nil))        ;   mechanism
  (riding-workspace-y-offset?
    nil vector-slot system (type nil)))        ; (MHD 5/26/95)



(def-class-method cleanup (edit-workspace)
  (funcall-superior-method edit-workspace)        ; per convention

  ;; All the following does is unhighlight frames being edited.  It's
  ;; ok for the cleanup code for the context to find that this has already
  ;; been done.  It does this being iterating over each workstation's
  ;; entire context stack; in practice this will be cheap, but try to make
  ;; this be more reliably cheap!  (MHD 5/15/92)
  (loop for workstation in workstations-in-service
        do (loop for workstation-context
                     in (workstation-context-stack workstation)
                 as edit-state?
                    = (if (eq (type-of-workstation-context workstation-context)
                              'editing)
                          (specific-structure-for-workstation-context workstation-context))
                 when (and edit-state?
                           (eq (edit-workspace edit-state?) edit-workspace))
                   do (let* ((frame-being-edited?
                               (frame-being-edited? edit-state?))
                             (serial-number-of-frame-being-edited?
                               (serial-number-of-frame-being-edited? edit-state?)))
                        (unless (or (null frame-being-edited?)
                                    (frame-has-been-reprocessed-p
                                      frame-being-edited?
                                      serial-number-of-frame-being-edited?))
                          (highlight-or-unhighlight-for-slot
                            frame-being-edited?
                            (name-of-slot-being-edited edit-state?)
                            (defining-class-for-slot-being-edited? edit-state?)
                            nil t nil
                            (name-of-slot-component-being-edited? edit-state?)
                            (indicator-of-slot-component-being-edited? edit-state?)))))))







;;;; Entering and Exiting Editing Contexts



(def-system-variable chain-of-recycled-edit-states edit1 nil) ; not used.



;;; In-editing-context executes body in an environment in which special
;;; variables current-edit-state and current-edit-workspace have been bound per
;;; the current workstation context, which is assumed to be an editing context.

;;; NOTE: it is not valid to call in-editing-context unless the current
;;; workstation context is an editing context, and, in fact, that containing the
;;; argument edit-state.  Note that edit-context-remains-valid-p checks safely
;;; for this being the case, among other things, so it is not likely to work to
;;; merely use a bound value of edit-state without getting the current
;;; workstation context to really be for that edit state. [Note by MHD, 1/31/96]

(defmacro in-editing-context ((edit-state) &body body)
  `(let* ; with-named-dynamic-extent* editing-context
     ((current-edit-state ,edit-state)
      (current-edit-workspace
        (edit-workspace current-edit-state)))
     . ,body))

;; If with-named-dynamic-extent* returned multiple values then it would be
;; safe to change the above to use it, but since analysis of the users of
;; in-editing-context is too complex for me I can't prove that they all
;; are single value returning.  Oh for multiple-value-prog1. ben 6/12/91




;;; With-current-grammar-in-editing-context ... called in a current edit
;;; text to bind current-grammar, and related variables.

(defmacro with-current-grammar-for-current-edit-state (&body body)
  `(with-current-grammar (global-grammar)
     . ,body))



;;; Using different tokenizers


(def-global-property-name tokenizer-for-category)

(defparameter default-tokenizer 'g2-standard-tokenizer)

(defmacro define-tokenizer-for-category (category tokenizer)
  `(setf (tokenizer-for-category ',category) ',tokenizer))


(defun-simple get-tokenizer-for-category (top-level-grammar-category)
  (or (tokenizer-for-category top-level-grammar-category)
      default-tokenizer))


#+unused
(defun-simple get-tokenizer-for-top-level-category ()
  (or (tokenizer-for-slot-being-edited
        current-edit-state)
      default-tokenizer))


;;; `determine-appropriate-tokenizer'

(defun-simple determine-appropriate-tokenizer ()
  (if current-edit-state
      (let ((type-of-slot
              (cadr (type-of-slot-being-edited current-edit-state))))
        (or
          #+java-export-facilities
          (if (java-editing-category-p type-of-slot)
              java-tokenizer)
          (case type-of-slot
            (generic-file-pathname g2-load-kb-tokenizer)
            ((item-or-datum-or-no-item-attribute
               item-or-datum-attribute
               text-attribute
               file-command
               whole-string?
               whole-string
               evaluation-value-constant-allowing-items
               evaluation-value-constant-allowing-binary-data)
             g2-simple-tokenizer)
            (otherwise g2-standard-tokenizer))))
      g2-standard-tokenizer))


;;; Enter-editing-context ...

;;; Slot-denotation is either slot-name or a "name-or-class-qualified-list".
;;; The list structure, if any, should be made of slot value conses, and is
;;; absorbed by this function.

;;; If initial-text-or-edit-box? is a text, it will be used as the initial text
;;; in the edit box.  If cursor-line-index? and cursor-character-index? are
;;; specified and the editor does not automatically generate empty text ("") as
;;; the initial text, then the initial cursor position will be at that position;
;;; otherwise, the initial cursor will be at the end of the text.  (Note that if
;;; initial-text-or-edit-box? is a text, the reformatting of that text for the
;;; edit box may revise the specified cursor position.)

;; NOTE: as of 11/18/95 there are no callers which ever specify edit box.  That
;; was probably never fully implemented.  It can be eliminated as a feature for
;; the cost of changing the name (i.e., to initial-text?) and redocumenting it.
;; I will ignore it as a case as part of the transition to wide strings. (MHD
;; 11/18/95)

;;; If edit-workspace-hidden? is non-nil, the edit workspace is not put up here,
;;; but may be later by handle-parsing-or-compilation-problem.

;;; To be editable, a slot must have a type feature.  The text to parse must
;;; contain at least one text line.

;;; If the slot type is not a text slot type, frame? is non-nil, the current value of
;;; that slot in frame? is nil, and edit-workspace-hidden? is nil, the editor
;;; automatically generates empty text ("") as the initial text, rather than the
;;; current text representation or the text that would be generated by calling
;;; make-text-representation-for-slot-value.

;;; If type-of-slot? is specified, and frame? is non-nil, and type-of-slot?
;;; disagrees with the type of slot for the frame, then the compilation doesn't
;;; happen.  This feature should only be used if it makes sense.  This is used,
;;; for example, to edit the text of a message (free text) using the grammar for
;;; some other slot (say, e.g., a rule).  The field edit facility currently
;;; takes advantage of this feature.  There, only messages (instances of the
;;; class MESSAGE) may be specified as frame?.  It is an error to call this such
;;; that bad text could be entered into a frame inappropriately, e.g., using
;;; a rule as the frame and the type of slot for a procedure text.

;;; If the slot type is boolean, then the editor is not usually entered.
;;; Rather, higher level software usually puts up a "toggle" menu to allow the
;;; user to more easily flip the values.  This is transparent to the editor, and
;;; editing this type of slot value does not pose any problems for the editor.
;;; It is simply a convenience for users which allows them to skip the few extra
;;; steps involved in editing as opposed to menuing.

;;; If specific-image-plane-on-which-to-edit-in-place? is specified, editing is
;;; done "in place" on that image plane.  In that case, specific-text-box-or-table-
;;; on-which-to-edit-in-place? must be supplied, and if that is a table, the four
;;; edges (in workspace units) of the cell to be edited must also be supplied.
;;; Note that when this option is specified, parsing menus are never displayed.

;;; When do-not-have-edit-option-buttons? is true, the edit options (cancel, end,
;;; undo, redo, paste, etc.) subcommand menu is not displayed or made available
;;; in any way to the user.  This option is normally used only for type-in box
;;; text entry.

(defun twrite-edit-backtrace-info ()
  (twrite-string "  slot: ")
  (twrite-symbol (pop-backtrace-information)))

(defvar editor-specific-natural-language-override? nil)
(defvar editor-frame-style-override? nil)
(defvar editor-background-color-override? nil)
(defvar editor-text-color-override? nil)
(defvar editor-font-size-override? nil)
(defvar editor-initial-editor-height-override? nil)
(defvar editor-caption-text-override? nil)
(defvar editor-prompt-filter? nil) ; Bind to set corresponding slot in edit-state

(defun enter-editing-context
    (frame? slot-denotation
            &optional
            initial-text-or-edit-box? edit-workspace-hidden?
            edit-box-format-or-format-name? width-for-cell?
            cursor-line-index? cursor-character-index?
            specific-image-plane-on-which-to-edit-in-place?        ; review & shuffle args?
            specific-text-box-or-table-on-which-to-edit-in-place?
            left-edge-of-cell-in-table-on-which-to-edit-in-place?
            top-edge-of-cell-in-table-on-which-to-edit-in-place?
            right-edge-of-cell-in-table-on-which-to-edit-in-place?
            bottom-edge-of-cell-in-table-on-which-to-edit-in-place?
            type-of-slot?
            special-entry-context? function-to-call-on-changed-edit-box-text?
            do-not-have-edit-option-buttons?
            do-not-have-edit-menus?
            ;; "new year's resolution": this is the last time I'll ever add
            ;; arguments here at the end! Fix this interface! (MHD 1/27/94)
            slot-component-name? slot-component-indicator?
            table? attribute-is-virtual? use-exported-format?
            ;; Added by SoftServe
            modal size-x size-y pos-x pos-y
            &aux
            (defining-class?
                (class-qualifier slot-denotation))
            (slot-name
              (prog1 (unqualified-name slot-denotation)
                (reclaim-slot-value slot-denotation)
                (setq slot-denotation nil))))
  width-for-cell?                                ; not used yet
  (with-backtrace-for-internal-error
      (edit
        (push-backtrace-information slot-name) ; defining-class?
        twrite-edit-backtrace-info)

    (with-localization-domain 'text-editor

    (let* ((slot-description?                   ;   during setup in a few places
             (when (and frame? (not attribute-is-virtual?))
               (get-slot-description-of-frame
                 slot-name frame? defining-class?)))
           (virtual-attribute?
             (when attribute-is-virtual?
               (virtual-attribute slot-name)))
           (type-of-slot
             (or type-of-slot?
                 (if frame?
                     (if (and (or slot-component-name?
                                  slot-description?)
                              (null use-exported-format?))
                         (feature-assq
                           'type
                           (if slot-component-name?
                               (get-slot-component-features
                                 slot-name defining-class?
                                 slot-component-name?)
                               (slot-features slot-description?)))
                         (if (or virtual-attribute? use-exported-format?)
                             (if (if virtual-attribute?
                                     (or (eq slot-name 'image-data)
                                         (eq slot-name 'media-bin-data))
                                     (eq slot-name 'uuid))
                                 '(type evaluation-value-constant-allowing-binary-data)
                                 '(type evaluation-value-constant-allowing-items))
                             nil))
                     '(type free text))))
           (edit-state
             (let ((es (make-edit-state)))
               ;; These first three must be bound for
               (setf (frame-being-edited? es) frame?)
               (setf (name-of-slot-being-edited es) slot-name)
               (setf (type-of-slot-being-edited es) type-of-slot)
               (setf (tokenizer-for-slot-being-edited es)
                     (get-tokenizer-for-category (cadr type-of-slot)))
               (setf (scrolling-editor-p es)
                     ;; Depends on frame, name, and type being in edit-state.
                     (should-this-editor-state-scroll? es))
               (setf (specific-natural-language-for-editor? es)
                     (get-natural-language-for-editor
                       editor-specific-natural-language-override?))
               (setf (natural-language-for-editor? es)
                     (or editor-specific-natural-language-override?
                         (current-natural-language-for-editor)))
               (setf (frame-style-for-edit-workspace? es)
                     editor-frame-style-override?)
               (setf (background-color-for-edit-workspace? es)
                     editor-background-color-override?)
               (setf (text-color-for-edit-workspace? es)
                     editor-text-color-override?)
               (setf (font-size-override-for-edit-workspace? es)
                     editor-font-size-override?)
               (setf (editor-initial-editor-height-override? es)
                     editor-initial-editor-height-override?)
               ;; No need to worry about nested edit-states here like in with-phrase-conses
               (when generate-source-annotation-info
                 (setf (sexp-annotation-hash es) (make-sexp-annotation-hash)))
               (setf (table-being-edited? es) table?)
               (setf (frame-serial-number-of-table-being-edited? es)
                     (when table?
                       (copy-frame-serial-number (frame-serial-number table?))))
               (setf (attribute-being-edited-is-virtual? es) attribute-is-virtual?)
               (setf (editing-using-exported-format? es) use-exported-format?)
               (setf (edit-workspace-hidden? es)
                     (or edit-workspace-hidden?
                         keep-edit-workspace-hidden-no-matter-what?))
               (setf (editor-prompt-filter? es) editor-prompt-filter?) ; -fmw, 2/10/05
               es))
           (current-edit-state edit-state) ; binding now may be needed/used


           (slot-value                        ; relevant only if frame? is non-nil
             (cond ((null frame?) nil)
                   (slot-component-name?
                    (get-slot-component-value
                      frame? slot-name defining-class?
                      slot-component-name?
                      slot-component-indicator?))
                   (slot-description?
                    (if use-exported-format?
                        (get-attribute-description-evaluation-value
                          frame? slot-description?)
                        (get-slot-description-value
                          frame? slot-description?)))
                   (virtual-attribute?
                    (get-attribute-description-evaluation-value
                      frame? virtual-attribute?))))

           ;; Assuming we didn't get handed an edit box, then
           ;; see if we can obtain some initial text to show.
           (initial-text?
             (cond
               ((framep initial-text-or-edit-box?)
                nil)
               ((intercepted-text-p initial-text-or-edit-box?)
                initial-text-or-edit-box?)
               (t
                (cond
                  ((and (not edit-workspace-hidden?)
                        frame?
                        (null slot-value))
                   (if initial-text-or-edit-box?
                       (reclaim-text initial-text-or-edit-box?))
                   (setq cursor-line-index? nil)
                   (setq cursor-character-index? nil)
                   (make-empty-text))        ; nil in non-text slot => "clear edit box"
                  (t (or initial-text-or-edit-box?
                         (if frame?
                             (if (or virtual-attribute? use-exported-format?)
                                 (text-for-item-or-value  ; reclaims slot-value
                                   slot-value)
                                 (make-text-representation-for-slot-value-itself
                                   frame? slot-value ; slot-value doesn't need to be reclaimed
                                   type-of-slot)))
                         (make-empty-text)))))))
           (minimum-edit-box-width?
             (cond
               (specific-image-plane-on-which-to-edit-in-place?
                (if left-edge-of-cell-in-table-on-which-to-edit-in-place?
                    (-w right-edge-of-cell-in-table-on-which-to-edit-in-place?
                        left-edge-of-cell-in-table-on-which-to-edit-in-place?)
                    (width-of-block
                      specific-text-box-or-table-on-which-to-edit-in-place?)))
               (t nil)))
           (minimum-or-desired-edit-box-height?
             (cond
               (editor-initial-editor-height-override?)        ; from field-edit's
                                                        ;   edit style (MHD 1/13/95)
               (specific-image-plane-on-which-to-edit-in-place?
                (if left-edge-of-cell-in-table-on-which-to-edit-in-place?
                    (-w bottom-edge-of-cell-in-table-on-which-to-edit-in-place?
                        top-edge-of-cell-in-table-on-which-to-edit-in-place?)
                    (height-of-block
                      specific-text-box-or-table-on-which-to-edit-in-place?)))
               (t nil)))

           (current-edit-workspace
             (let ((edit-workspace
                     (if specific-image-plane-on-which-to-edit-in-place?
                         (make-workspace
                           'edit-workspace nil nil
                           (if (and (not (scrolling-editor-p edit-state))
                                    do-not-have-edit-option-buttons?
                                    do-not-have-edit-menus?)
                               0
                               5)
                           (or minimum-edit-box-width? 0)
                           (or minimum-or-desired-edit-box-height? 0))
                         (make-workspace
                           'edit-workspace nil nil nil
                           200 200))))        ; initial edit workspace width and height
               (when new-g2-classic-ui-p
                 (let ((caption-text
                         (make-caption-text-for-edit-workspace
                           frame? slot-name
                           slot-component-name? slot-component-indicator?)))
                   (change-slot-value edit-workspace 'title-bar-caption-text caption-text)))
               (when (frame-style-for-edit-workspace? edit-state)
                 ;; safe to assume a symbol here -- bogosity of symbol is
                 ;; unknown, but is checked for prior to its use
                 (change-slot-value
                   edit-workspace 'frame-style
                   (frame-style-for-edit-workspace? edit-state)))
               (when (and (background-color-for-edit-workspace? edit-state)
                          (color-or-metacolor-p
                            (background-color-for-edit-workspace? edit-state)))
                 (change-slot-value
                   edit-workspace 'workspace-background-color?
                   (background-color-for-edit-workspace? edit-state)))
               edit-workspace))



           (edit-workspace-margin (workspace-margin current-edit-workspace))

           ;; Set up the left, top edge of the edit workspace inside contents
           ;; so that gives maximum room to grow to the right and down; this
           ;; avoids running into hard limits in cases of extremely large
           ;; amounts of text, especially with larger font/character sizes
           ;; and/or liberal line breaking. (MHD 6/2/95)
           ;;  Now that the max workspace size has been increased, put back the
           ;; old origin, so that control+O does something useful.  -fmw, 7/19/95
           (edit-workspace-inside-left-edge
             (+w (left-edge-of-block current-edit-workspace)
                 edit-workspace-margin))
           (edit-workspace-inside-top-edge
             (+w (top-edge-of-block current-edit-workspace)
                 edit-workspace-margin))

           (edit-box
             (progn
               (when (scrolling-editor-p edit-state)
                 (unless cursor-line-index?
                   ;; Alternate default for scrolling as requested by users.
                   (setf cursor-line-index? 1)
                   (setf cursor-character-index? 0)))
               (let ((edit-box
                       (if (and initial-text-or-edit-box?
                                (not (consp initial-text-or-edit-box?)))
                           initial-text-or-edit-box?
                           (multiple-value-setq-some        ; returns edit-box as value
                               (nil cursor-line-index? cursor-character-index?)
                               (make-edit-box
                                 initial-text?
                                 t edit-box-format-or-format-name?
                                 nil
                                 cursor-line-index? cursor-character-index?
                                 minimum-edit-box-width?
                                 minimum-or-desired-edit-box-height?
                                 (scrolling-editor-p edit-state))))))
                 (when (and (text-color-for-edit-workspace? edit-state)
                            (color-or-metacolor-p
                              (text-color-for-edit-workspace? edit-state)))
                   (change-color-of-text-box
                     edit-box nil nil nil
                     (text-color-for-edit-workspace? edit-state)))
                 edit-box)))

           (text-being-edited
             (cdr (box-translation-and-text edit-box)))

           (edit-cursor
             (make-entity
               (if (eq (or (font-size-override-for-edit-workspace? current-edit-state)
                           (if new-g2-classic-ui-p
                               (get-ui-parameter 'font-for-editing)
                               (font-for-editing fonts)))
                       'small)
                   'small-edit-cursor
                   'edit-cursor)))

           (edit-subcommand-menu?
             (unless do-not-have-edit-option-buttons?
               (make-edit-subcommand-menu)))
           ) ; end of let*

      ;; New in 5.0r1: Instead of having TW constantly poll
      ;; for paste availability and send results to G2, let
      ;; G2 ask TW for its paste availability. To do in the
      ;; future: ask TW for paste availability when a mouse
      ;; enters G2 (could have done a clipboard cut/copy out
      ;; there), or when mouse enters editor.  Must send
      ;; this soon after editor opens in order to allow time
      ;; for ICP round trip: G2 -> TW -> G2.

      (unless edit-workspace-hidden?
        (when (window-supports-request-for-paste-availability
                current-workstation-window)
          (request-paste-availability-for-editor)))

      ;; Set up backpointer from the frame being edited to the edit
      ;; workspace, so that the edit workspace is deleted (effectively
      ;; aborting the edit) if the frame gets deleted.  Note that the
      ;; name of the backpointer slot, menus-for-this, is a misnomer
      ;; in light of this usage: it might better be called "menus-or-
      ;; edit-workspaces-for-this".
      (frame-serial-number-setf (serial-number-of-frame-being-edited? edit-state)
                                (if frame? (frame-serial-number frame?)))
      (when (and frame? (block-p frame?))
        (setf (menus-for-this frame?)
              (slot-value-cons
                current-edit-workspace
                (menus-for-this frame?)))
        (setf (what-this-is-a-menu-for? current-edit-workspace)
              frame?))

      (setf (defining-class-for-slot-being-edited? edit-state)
            defining-class?)

      (setf (name-of-slot-component-being-edited? edit-state)
            slot-component-name?)
      (setf (indicator-of-slot-component-being-edited? edit-state)
            slot-component-indicator?)

      (setf (free-text-slot-being-edited? edit-state)
            (free-text-slot-type-p type-of-slot))

      (setf (edit-workspace edit-state) current-edit-workspace)
      ;; We must rebind serial-number-of-edit-workspace from the default, since
      ;; the workspace was created after the context was born.
      (frame-serial-number-setf (frame-reference-number-of-workstation-context edit-state)
                                (frame-serial-number current-edit-workspace))

      (setf (edit-box edit-state) edit-box)
      (setf (edit-cursor edit-state) edit-cursor)
      (add-subblock edit-cursor edit-box)

      (when edit-subcommand-menu?
        (setf (edit-subcommand-menu? edit-state) edit-subcommand-menu?)
        (add-to-workspace
          edit-subcommand-menu? current-edit-workspace
          edit-workspace-inside-left-edge
          edit-workspace-inside-top-edge))

      (setf (do-not-have-edit-menus? edit-state) do-not-have-edit-menus?)        ; (MHD 5/14/92)

      (setf (text-being-edited edit-state) text-being-edited)

      (setf (specific-image-plane-on-which-to-edit-in-place? edit-state)
            specific-image-plane-on-which-to-edit-in-place?)
      (setf (specific-text-box-or-table-on-which-to-edit-in-place? edit-state)
            specific-text-box-or-table-on-which-to-edit-in-place?)
      (setf (top-edge-of-cell-in-table-on-which-to-edit-in-place? edit-state)
            top-edge-of-cell-in-table-on-which-to-edit-in-place?)
      (setf (left-edge-of-cell-in-table-on-which-to-edit-in-place? edit-state)
            left-edge-of-cell-in-table-on-which-to-edit-in-place?)
      (setf (right-edge-of-cell-in-table-on-which-to-edit-in-place? edit-state)
            right-edge-of-cell-in-table-on-which-to-edit-in-place?)
      (setf (bottom-edge-of-cell-in-table-on-which-to-edit-in-place? edit-state)
            bottom-edge-of-cell-in-table-on-which-to-edit-in-place?)

      (setf (function-to-call-on-changed-edit-box-text? edit-state)
            function-to-call-on-changed-edit-box-text?)
      (setf (special-entry-context? edit-state) special-entry-context?)

      (setf (initial-cursor-line-index? edit-state) cursor-line-index?)
      (setf (initial-cursor-character-index? edit-state) cursor-character-index?)

      (enter-editing-context-1 edit-state
                               ;; Added by SoftServe
                               modal size-x size-y pos-x pos-y)))))

;; Consider using edit-state instead of current-edit-state throughout.

;; Consider returning the new edit state.

(defun enter-editing-context-1 (edit-state &optional 
                                           ;; Added by SoftServe
                                           modal size-x size-y pos-x pos-y
                                           ;; End of SoftServe changes
                                           do-not-put-up-edit-workspace?)
  (enter-context-in-current-workstation 'editing edit-state)
  (in-editing-context (edit-state)
    (if (free-text-slot-being-edited? edit-state)
        (progn
          (push-for-token 1 0 t (text-being-edited edit-state) nil nil nil) ; sets parsing position slots
          (enable-or-disable-edit-end-and-update-buttons nil))
        ;; the following should be abstracted as (get-set-to-parse) if useful elsewhere
        (let ((irrelevant-category
                (with-current-grammar-for-current-edit-state
                  (get-or-make-category-for-category-symbol 'irrelevant))))
          (setf (phrase-rule-completions-past-instance-of-category edit-state)
                (grammar-list
                  (make-phrase-rule-completion
                    irrelevant-category irrelevant-category nil)))
          (push-for-token                        ; sets parsing position slots
            1 0 t (text-being-edited edit-state)
            (phrase-cons
              (make-incomplete-phrase                ; initial incomplete phrase
                (grammar-list
                  (make-phrase-rule-completion
                    irrelevant-category
                    (with-current-grammar-for-current-edit-state
                      (get-or-make-category-for-category-symbol
                        (category-symbol-given-slot-type (type-of-slot-being-edited edit-state))))
                    (phrase-rule-completions-past-instance-of-category
                      edit-state)))
                nil
                nil)
              nil)
            nil nil)))

    ;; This used to be done here:
    ;;   (highlight-or-unhighlight-what-is-being-edited nil)
    ;; (Was the intention to have it here before doing other things like
    ;; putting up the workspace in order to flash things more?  I moved
    ;; it after the call to put-up-edit-workspace below so that there would
    ;; be a minimum of flashing. I still think that is the desired thing at
    ;; least in the case of editing in place, if not all cases.)
    ;; (MHD 10/12/88)

    (let* ((edit-workspace-margin (workspace-margin current-edit-workspace))
           (edit-workspace-inside-left-edge
             (+w (left-edge-of-block current-edit-workspace)
                 (workspace-margin current-edit-workspace)))
           (edit-workspace-inside-top-edge
             (+w (top-edge-of-block current-edit-workspace)
                 edit-workspace-margin)))
      (add-to-workspace
        (edit-box edit-state) current-edit-workspace
        (if (edit-subcommand-menu? edit-state)
            (+w (right-edge-of-block (edit-subcommand-menu? edit-state))
                edit-workspace-margin)
            edit-workspace-inside-left-edge)
        edit-workspace-inside-top-edge))

    (cond                                        ; move elsewhere?! (MHD 8/31/89)
      ((edit-subcommand-menu? edit-state)
       (unless keep-edit-workspace-hidden-no-matter-what?
         (initialize-edit-subcommand-menu (edit-subcommand-menu? edit-state)))))

    (when (frame-being-edited? edit-state) ; new. (MHD 6/24/93)
      (funcall-method-if-any
        'add-items-to-edit-workspace (frame-being-edited? edit-state)
        current-edit-workspace (edit-box edit-state) nil))

    ;; Shrink around initial contents, which are at the
    ;; top, left extreme of the workspace coordinate
    ;; system, whereas workspaces start off showing
    ;; their origin. (MHD 6/2/95)
                                        ; (shrink-wrap-workspace current-edit-workspace)

    (unless do-not-put-up-edit-workspace?
      (when (not (edit-workspace-hidden? edit-state))
        (when new-g2-classic-ui-p
          (change-slot-value
            current-edit-workspace 'workspace-background-color?
            (get-ui-parameter 'system-workspace-background-color)))
        (put-up-edit-workspace
          current-edit-workspace current-workstation
          ;; Added by SoftServe
          modal size-x size-y pos-x pos-y)))

    (unless keep-edit-workspace-hidden-no-matter-what?
      (highlight-or-unhighlight-what-is-being-edited nil)) ; moved here from above -- see note



    ;; The following sets up the cursor line index, character index, and text
    ;; tail in the edit state:
    (let* ((cursor-line-index? (initial-cursor-line-index? edit-state))
           (cursor-character-index? (initial-cursor-character-index? edit-state))
           text-tail-for-cursor)
      (if cursor-line-index?
          (setq text-tail-for-cursor
                (find-text-tail-for-line        ; should do in change-edit-box!
                  (text-being-edited edit-state) cursor-line-index?))
          (multiple-value-setq                        ; assumes cursor-character-index? specified
              (cursor-line-index? cursor-character-index? text-tail-for-cursor)
            (find-end-of-text (text-being-edited edit-state) 1)))
      (change-edit-box text-tail-for-cursor cursor-line-index? cursor-character-index?))

    ;; The following may push a new workstation on top of this editing
    ;; context, i.e. a dialog context.  Callers that expect to be right in the
    ;; middle of an editing workstation context can't tolerate this.  A things
    ;; now stand, they must all either pass in true for
    ;; edit-workspace-hidden?, or bind
    ;; keep-edit-workspace-hidden-no-matter-what? to true, in order to keep
    ;; the edit context from being buried in the context stack.  This mechanism
    ;; is a little kludgey, so next time it gets in our way, we can devise a
    ;; cleaner scheme.  Till then, .... (MHD 6/1/94)
    (let ((slot-description?
            (when (and (frame-being-edited? edit-state)
                       (not (attribute-being-edited-is-virtual? edit-state)))
              (get-slot-description-of-frame
                (name-of-slot-being-edited edit-state)
                (frame-being-edited? edit-state)
                (defining-class-for-slot-being-edited? edit-state)))))
      (when (and (frame-being-edited? edit-state)
                 slot-description?        ; slightly redundant
                 (not (edit-workspace-hidden? edit-state))
                 (not keep-edit-workspace-hidden-no-matter-what?))
        (put-barrier-on-destabilization-via-editing
          (frame-being-edited? edit-state) slot-description?))))
	edit-state ;added by SoftServe	  
	)

(defun make-caption-text-for-edit-workspace
    (frame? &optional slot-name? slot-component-name? slot-component-indicator?)
  (twith-output-to-text
    (cond (editor-caption-text-override?
           (twrite-string editor-caption-text-override?))
          (t
           (tformat "Text Editor")
           (when frame?
             (tformat " for ")
             (frame-class-case frame?
               ((or inspect-command inspect-history) (tformat "Inspect Command"))
               (file-command (tformat "File Command"))
               (t
                 (when slot-name?
                   (let* ((slot-description?
                            (get-slot-description-of-frame slot-name? frame?))
                          (slot-name-for-user
                            (if slot-description?
                                (if (user-defined-slot-description-p slot-description?)
                                    (pretty-slot-name slot-description?)
                                    (alias-slot-name-if-necessary
                                      (pretty-slot-name slot-description?)
                                      (defining-class slot-description?)))
                                slot-name?)))
                     (when (or slot-component-name? slot-component-indicator?)
                       (tformat "the ")
                       (when slot-component-name?
                         (tformat "~(~A~) of " slot-component-name?))
                       (when slot-component-indicator?
                         (tformat "~(~A~) of " slot-component-indicator?)))
                     (tformat "the ~(~A~) of " slot-name-for-user)))
                 (write-class-instance-header-from-slot (class frame?) frame?))))))))



;;; `Editor-scroll-decision-override?' is a variable globally bound to nil that
;;; may be transiently bound to either NIL, ALWAYS, or NEVER as an implicit
;;; parameter to enter-editing-context.  This is only used by the field edit
;;; facility at present to give explicit control over whether scrolling should
;;; happen or not.

(defvar editor-scroll-decision-override? nil)



;;; The system procedure `g2-use-scrolling-editor' is not intended to ever be
;;; exposed to users; it is purely for internal use.  It will set editor-scroll-
;;; decision-override?, which will make G2 always use the scrolling editor (or
;;; never use it, if you prefer).  It is nice to be able to do this from within
;;; the kb, instead of having to do it in Lisp.  -jv, 5/21/04

(defun-for-system-procedure g2-use-scrolling-editor (when-to)
  (case when-to
    (always
     (setq editor-scroll-decision-override? t))
    (never
     (setq editor-scroll-decision-override? 'never))
    (t
     (setq editor-scroll-decision-override? nil))))




;;; `Attributes-to-edit-using-scrolling-editor' attributes that
;;; by default use the scrolling editor.

(defparameter attributes-to-edit-using-scrolling-editor
  '( ;; text -- triggers far to many slots
    ;; action  -- i.e. menu-choice and action buttons (note A)
    class-specific-attributes
    attribute-initializations
    attribute-displays
    stubs
    icon-description))

;; Note A: Removed action since a number of users said they thought
;; it inconsistant to scroll these rules, but not "real" rules.  Meanwhile
;; they all thought rules should be and are short and since rules display
;; as statements it seems better to use the nonscrolling editor on them.



;;; `Should-this-editor-state-scroll?' is called by enter-editing-context to
;;; determine if this should be an editor with scrolling (and associated
;;; functionality) enabled.  Its decision is based on whether the attribute
;;; being edited is a member of `attributes-to-edit-using-scrolling-editor',
;;; which is is a list of the attribute names (i.e., aliased, user-visible slot
;;; names) that should be edited using the scrolling editor.  Note that this
;;; list is maintained privately by G2, and no explicit user control over this
;;; is available; that could ultimately change.

(defun should-this-editor-state-scroll? (edit-state)
  (case editor-scroll-decision-override?
    ;; Default
    ((nil)
     (or
       ;; Scroll for certain grammar types
       (let ((type-of-slot (type-of-slot-being-edited edit-state)))
         ;; type-of-slot matchs: (type <type> [text])
         (memq (second type-of-slot)
               '(procedure-definition
                 #+java-export-facilities
                 java-class-body-declarations-or-none
                 #+gesture-definition-facilities
                 gesture-definition
                 patterns-definition
                 tokens-definition
                 object-configuration
                 chart-annotations)))
       ;; Scroll for certain slots.
       (memq (alias-slot-name-if-necessary
               (name-of-slot-being-edited edit-state)
               (frame-being-edited? edit-state))
             attributes-to-edit-using-scrolling-editor)))
    (never
     nil)
    (t  ; always
     t)))

;; It is tempting to do some AI (e.g. notice the number of lines) but that
;; can confuse field edit's sizing.





;;; `Valid-workstation-context-p for edit-state' checks that the edit-workspace
;;; hasn't be reclaimed.  We must do this since the edit context doesn't focus
;;; on the editor, and the workspace is born after the original mouse pointer.

(def-structure-method valid-workstation-context-p (edit-state)
  (and (funcall-superior-method edit-state)
       (general-valid-edit-state-p edit-state)
       (let ((superior-edit-state? (get-superior-edit-state-if-any edit-state)))
         (or (null superior-edit-state?)
             (general-valid-edit-state-p superior-edit-state?)))))



;;; `General-valid-edit-state-p' is used to check validity of the edit state by
;;; checking frames whose deletion would invalidate this edit state.  This does
;;; not check any other edit states (e.g., the "superior" edit state of a
;;; substate used for searching).

(defun general-valid-edit-state-p (edit-state)
  (and (valid-block-in-workstation-context-p (edit-workspace edit-state) edit-state)
       (or (null (frame-being-edited? edit-state))
           (valid-block-in-workstation-context-p (frame-being-edited? edit-state) edit-state))))

;; Note that (text-region-of-edit-state? edit-state) does not invalidate the
;; edit state, so it is not checked here.  However, it does have to be checked
;; prior to use.


;;; `Get-superior-edit-state-if-any' returns the "calling" or "superior"
;;; edit-state, if any.  Otherwise, nil.

(defun get-superior-edit-state-if-any (edit-state)
  (if (special-entry-context? edit-state)
      (let ((superior-context? (second (workstation-context-stack current-workstation))))
        (if (and superior-context?
                 (eq (type-of-workstation-context superior-context?) 'editing))
            (specific-structure-for-workstation-context superior-context?)))))



;;; `Edit-context-remains-valid-p' can be used in the middle of an edit-context
;;; dynamic extent to revalidate the context.  It detects (1) the workstation
;;; context stack being changed; (2) the workstation context becoming invalid;
;;; and (3) the KB having been cleared.
;;;
;;; Due to number (3), this requires the kb-serial-number that was in effect at
;;; the last point at which the context was known to be valid, i.e., the value
;;; of current-kb-serial-number as of that time.  (If that's not a concern, the
;;; value of current-kb-serial-number could be passed in to just get the other
;;; checking.)

(defun edit-context-remains-valid-p (kb-serial-number)
  (and
    ;; check for unwound workstation context:
    (eq current-edit-state
        specific-structure-for-current-workstation-context)
    ;; check for valid workstation context:
    (valid-workstation-context-p current-edit-state)
    ;; check for cleared KB, too:
    (not (>f current-kb-serial-number kb-serial-number))))


(def-structure-method clean-up-workstation-context (edit-state)
  (let ((current-edit-state edit-state))
    (unless (parsing-context-p-function edit-state)
      (unless keep-edit-workspace-hidden-no-matter-what?
        (highlight-or-unhighlight-what-is-being-edited t))
      (let ((menu-of-names-workspace?
              (get-item-if-item-reference
                (menu-of-names-workspace? current-edit-state))))
        (when (and menu-of-names-workspace?
                   (null (name-or-names-for-frame menu-of-names-workspace?)))
          (delete-frame menu-of-names-workspace?)))
      (when (valid-block-in-workstation-context-p (edit-workspace edit-state)
                                                  current-edit-state)
        (delete-frame (edit-workspace edit-state)))) ; see in-editing-context note
    (when (stack-of-incomplete-phrases-at-earlier-positions current-edit-state)
      (reclaim-phrase-rule-completions        ; could be done in loop below
        (phrase-rule-completions
          (car (car (LAST (stack-of-incomplete-phrases-at-earlier-positions
                            current-edit-state)))))))

    (when (consp (temporary-information-on-edit-workspace? current-edit-state))
      (reclaim-menu-content-structure-for-character-position        ; must precede the
        (temporary-information-on-edit-workspace?        ;  pop-for-token's
          current-edit-state)))
    (loop while (stack-of-positions-after-tokens current-edit-state)
          do (pop-for-token)))
  (when (and (text-region-of-edit-state? edit-state)
             (valid-block-in-workstation-context-p
              (text-region-of-edit-state? edit-state)
              edit-state))
    (delete-frame (text-region-of-edit-state? edit-state)))
  (funcall-superior-method edit-state)
  (when (eq current-edit-state edit-state)
    (setq current-edit-state nil)))



;;; Put-up-edit-workspace ...

(defun put-up-edit-workspace (edit-workspace workstation &optional modal size-x
        size-y pos-x pos-y)
    (let* ((pane (if (specific-image-plane-on-which-to-edit-in-place?
                        current-edit-state)
                    (pane-for-image-plane
                        (specific-image-plane-on-which-to-edit-in-place?
                        current-edit-state))
                    (detail-pane (window-for-workstation workstation)))))
    ;; Eliminated and then returned many apparently redundant calls to
    ;; (specific-image-plane-on-which-to-edit-in-place?
    ;;             current-edit-state), not necessarily correctly. pga 5/26/95
        (cond ((specific-image-plane-on-which-to-edit-in-place?
                    current-edit-state)
                (let* ((specific-image-plane
                            (specific-image-plane-on-which-to-edit-in-place?
                                current-edit-state))
                        (frame-description-reference
                            (let ((new-g2-classic-ui-p nil)) ; to suppress title bars for type-in boxes
                                (lookup-frame-description-reference-of-block?
                                    edit-workspace)))
                        (available-image-plane
                            (new-get-available-image-plane
                                pane
                                frame-description-reference
                                'above
                                specific-image-plane))
                        (text-box-or-table
                            (specific-text-box-or-table-on-which-to-edit-in-place?
                                current-edit-state))
                        left-edge-in-workspace top-edge-in-workspace)
                    (cond ((setq left-edge-in-workspace        ; alt: (table-p text-box-or-table)
                                (left-edge-of-cell-in-table-on-which-to-edit-in-place?
                                    current-edit-state))
                            (setq top-edge-in-workspace
                                (top-edge-of-cell-in-table-on-which-to-edit-in-place?
                                    current-edit-state))
                            ;; Use a different frame so this doesn't look like an image-plane
                            (change-frame-description-reference-of-image-plane
                                available-image-plane
                                (lookup-frame-description-reference-of-frame-style
                                    'thick-workspace-frame-style
                                    'default-workspace-frame-style)))
                        (t (setq left-edge-in-workspace
                                (left-edge-of-block text-box-or-table))
                            (setq top-edge-in-workspace
                                (top-edge-of-block text-box-or-table))))
                    (put-image-on-image-plane
                        available-image-plane edit-workspace
                        (image-x-scale specific-image-plane)
                        (image-y-scale specific-image-plane)
                        nil nil
                        (left-edge-of-block (edit-box current-edit-state))
                        (top-edge-of-block (edit-box current-edit-state))
                        (x-in-frame-transform
                            left-edge-in-workspace
                            (workspace-on-image-plane? specific-image-plane)
                            specific-image-plane)
                        (y-in-frame-transform
                            top-edge-in-workspace
                            (workspace-on-image-plane? specific-image-plane)
                            specific-image-plane))
                    (if (superplane?
                            (specific-image-plane-on-which-to-edit-in-place?
                                current-edit-state))
                        (delete-image-plane
                            (superplane?
                                (specific-image-plane-on-which-to-edit-in-place?
                                    current-edit-state))))
                    ;; A lot of people say they like the editor-push feature, but
                    ;; it's too problematic to do that now.
                    (setf (superplane?
                            (specific-image-plane-on-which-to-edit-in-place?
                                current-edit-state))
                        available-image-plane)
                    (setf (superplane-coupling?
                            (specific-image-plane-on-which-to-edit-in-place?
                                current-edit-state))
                        'riding)
                    (let ((base-plane
                                (find-base-plane-in-stack-of-coupled-image-planes
                                    specific-image-plane)))
                        (setf (riding-workspace-x-offset? edit-workspace)
                            (delta-x-in-workspace
                                (-r (x-origin-of-workspace-in-window-of-image-plane
                                        available-image-plane)
                                    (x-origin-of-workspace-in-window-of-image-plane
                                        base-plane)) ;was specific-image-plane
                                (image-x-scale base-plane)))
                        (setf (riding-workspace-y-offset? edit-workspace)
                            (delta-y-in-workspace
                                (-r (y-origin-of-workspace-in-window-of-image-plane
                                        available-image-plane)
                                    (y-origin-of-workspace-in-window-of-image-plane
                                        base-plane))
                                (image-y-scale base-plane))))))
            (t
       ;; Added by SoftServe
                (when (not size-x) (setq size-x 0))
                (when (not size-y) (setq size-y 0))
                (when (not pos-x) (setq pos-x 0))
                (when (not pos-y) (setq pos-y 0))
                (if (and (eq modal nil)
                        (and (and (<=f size-x 0) (<=f size-y 0))
                            (and (<=f pos-x 0) (<=f pos-y 0))))                 
                    (put-workspace-on-pane edit-workspace pane 'left 'top t)
                    (put-workspace-on-pane edit-workspace pane 'left 'top t
		      :modal modal
		      :size-x size-x :size-y size-y
		      :pos-x pos-x :pos-y pos-y))
       ;; End of SoftServe changes
            ))))

;; Consider parameterizing this further.




;;; The following structure-methods take of disabling and reenabling the native
;;; editor (buttons and text entry) for when it is not the current editor.

(def-structure-method suspend-workstation-context (edit-state)
  (funcall-superior-method edit-state)
  (let ((edit-workspace (edit-workspace edit-state)))
    (when (and (framep edit-workspace) ; GENSYMCID-1472: Signal 11 abort
	       (native-editor-workspace-p edit-workspace))
      (suspend-native-editor edit-state))))

(def-structure-method resume-workstation-context (edit-state)
  (funcall-superior-method edit-state)
  (when (native-editor-workspace-p (edit-workspace edit-state))
    (resume-native-editor edit-state)))




;;;; Edit Boxes



;;; An `edit box' is a text box in which editing takes place.  The text in an
;;; edit box must include explicit indentation and line width elements for each
;;; text line.

(def-class (edit-box text-box)

  (default-text-box-format-name statement-format)        ; edit-box-format??
  (frame-style-of-edit-box nil))

;; Do not make subclasses of edit-box without revising the slot putter for box-
;; translation-and-text.



;;; `Make-edit-box' makes a new edit box containing initial-text and
;;; text-cell-plist.  The new edit box is formatted per
;;; text-box-format-or-format-name?, if specified, or else per the
;;; default-text-box-format-name of the edit box.  When reformat-text? is
;;; non-nil, the new edit box is (re)formatted rather than being fitted around
;;; initial-text as already formatted.  Explicit indentation and line width
;;; elements are put in for each text line.

;;; The edit box is returned as the first value.  Also, if cursor-line-index?
;;; and cursor-character-index? are specified, revised values for them are
;;; returned as second and third values.

;;; For editing in place, note that it may be more aesthetic to revise the width
;;; and height of a new edit box after making it.

;;; Minimum-or-desired-height? is so called because it is the minimum height in
;;; the case of a non-scrolling editor, and it's the desired height in case of
;;; the scrolling editor.  In both cases, the real minimum is height of a line
;;; of text, plus, in the case of the scrolling editor, the height of scrolling
;;; parapheralia.  In the case of the non-scrolling editor, the maximum cannot
;;; be set: the entire box has to fit, and there's no setting the maximum less
;;; than that.  In the case of the scrolling editor, minimum-or-desired-height?
;;; is used to determine the maximum, i.e., the actual height, of the scrolling
;;; editor's "viewport".

(defun make-edit-box
    (initial-text
      reformat-text?
      text-box-format-or-format-name? text-cell-plist
      cursor-line-index? cursor-character-index?
      minimum-width? minimum-or-desired-height?
      scrolling-editor-p)
  (let* ((edit-box
           (make-frame 'edit-box))
         (text-box-format
           (if (symbolp text-box-format-or-format-name?)
               (get-or-make-format-frame
                 (or text-box-format-or-format-name?
                     (choose-font-format-per-font-size
                       (if scrolling-editor-p
                           'scrolling-editor-text-format
                           (default-text-box-format-name edit-box))
                       (or (font-size-override-for-edit-workspace? current-edit-state)
                           (if new-g2-classic-ui-p
                               (get-ui-parameter 'font-for-editing)
                               (font-for-editing fonts))))))
               text-box-format-or-format-name?)))
    (setf (box-translation-and-text edit-box)
          (slot-value-cons no-value initial-text))
    (setf (text-box-format edit-box) text-box-format)
    (setf (text-cell-plist-for-text-box edit-box) text-cell-plist)

    ;; Add a scroll bar frame style.
    (when scrolling-editor-p
      (setf (frame-style-of-block edit-box)
            :edit-box-with-scroll-bar-frame-style))

    (let* ((text-cell-interline-distance
             (+w (text-cell-line-spacing text-box-format)
                 (text-cell-line-height text-box-format)))
           (height-if-scrolling
             ;; Even # of lines, larger than 500 workspace units.
             (let ((min-height
                     (maxr 500
                           (minimum-height-for-edit-box editor-parameters))))
               (*f text-cell-interline-distance
                   (+f 1 (truncatef min-height text-cell-interline-distance)))))
           (minimum-width
             (maxw
               (if scrolling-editor-p
                   #.(+ 2 2 (* 2 21))        ; see edit-box-with-scroll-bar-frame-style (!)
                   0)
               (or minimum-width?
                   (maxw
                     (minimum-width-for-edit-box editor-parameters)
                     (if scrolling-editor-p
                         (minf 500
                               (minimum-format-width-for-text-cell
                                 text-box-format))
                         0)))))
           (minimum-height
             (maxw
               ;; enough height for one line + the scrolling apperatus:
               (+w (if scrolling-editor-p
                       #.(+ 2 2 (* 2 21))        ; see edit-box-with-scroll-bar-frame-style (!)
                       0)
                   text-cell-interline-distance)
               (or minimum-or-desired-height?
                   (if scrolling-editor-p
                       (maxw height-if-scrolling
                             (minimum-height-for-edit-box editor-parameters))
                       0)))))
      (setf (minimum-width-of-text-box edit-box)
            (minr minimum-width
                  maximum-text-box-width-or-height))
      (setf (minimum-height-of-text-box edit-box)
            (minr minimum-height 2000))
      (when scrolling-editor-p
        (setf (maximum-width-of-text-box? edit-box)
              (maxr 400 minimum-width))
        (setf (maximum-height-of-text-box edit-box)
              (maxw (minimum-height-of-text-box edit-box)
                    (or minimum-or-desired-height? height-if-scrolling)))))


    (multiple-value-bind
        (text-box revised-cursor-line-index? revised-cursor-character-index?)
        (reformat-text-box-in-place
          edit-box t (not reformat-text?)
          cursor-line-index? cursor-character-index?)
      (setf (remembered-block-transform edit-box)
            (slot-value-list
              ;; From this workspace rectangle
              (left-edge-of-block edit-box)
              (top-edge-of-block edit-box)
              (right-edge-of-block edit-box)
              (bottom-edge-of-block edit-box)
              ;; Into this workspace rectangle
              (left-edge-of-block edit-box)
              (top-edge-of-block edit-box)
              (right-edge-of-block edit-box)
              (bottom-edge-of-block edit-box)))

      (values text-box revised-cursor-line-index? revised-cursor-character-index?))))



(def-text-box-format edit-box-format
  text-cell-font-map (hm18)                        ; 1 en = 10 workspace units
  text-cell-line-height 20                        ; experiment with these!
  text-cell-baseline-position 15
  default-word-spacing
  #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)                  ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)                  ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 26        ; 4 default spaces
  text-cell-lines-justified? nil
  text-cell-line-color? black
  text-box-border-color? black)


;;; An `edit-box-spot' is not a subtype of text-box-spot.

(def-spot edit-box-spot
    :slots ()
    :include text-box-spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented edit-box)

;; A special spot for the active editor seems very tempting!

(def-class-method generate-spot (edit-box mouse-pointer)
  (generate-text-box-spot edit-box mouse-pointer (make-edit-box-spot)))





;;;; Highlighting while Editing



;;; `Highlight-or-unhighlight-what-is-being-edited' ...

;;; Highlighting of what is being edited is not "stacked".  Therefore, if two
;;; edits of a given text box or slot are happening concurrently, there will be no
;;; or incomplete highlighting after one edit completes, even if the second edit
;;; continues.  [Remedy this someday!]

(defun highlight-or-unhighlight-what-is-being-edited (unhighlight-case?)
  (let* ((edit-state current-edit-state)
         (frame? (frame-being-edited? edit-state)))
    (when (and frame?
               (not (deleted-frame-p frame?))
               (frame-serial-number-equal
                 (frame-serial-number frame?)
                 (serial-number-of-frame-being-edited? edit-state)))
      (highlight-or-unhighlight-for-slot
        frame?
        (name-of-slot-being-edited edit-state)
        (defining-class-for-slot-being-edited? edit-state)
        nil                                        ; see below
        unhighlight-case?
        (if nil 'text-region)                ; implement option!
        (name-of-slot-component-being-edited? edit-state)
        (indicator-of-slot-component-being-edited? edit-state)))))

;; Highlight color was blue until 2.0 Alpha, then was FOREGROUND until 2.0 Beta0 1.1,
;; and became nil (meaning to use the text foreground color) today in 2.0 Beta 2.0.
;; (MHD 1/22/90)



;;; `Highlight-or-unhighlight-for-slot' highlights or unhighlights any table cell
;;; representations of the slot-name slot of frame.  In addition, if frame is
;;; is a text box, it highlights or unhighlights it, or, if slot-name is
;;; name-or-names-for-frame, it highlights or unhighlights name boxes for frame.

;;; If highlight-color? is nil, the color or metacolor used is the the line-color
;;; property on the appropriate text cell plist, if that is non-nil, or else the
;;; value of the text-cell-line-color? slot of the appropriate text format, if
;;; that is non-nil, or else FOREGROUND.  Highlight-color? is ignored in the
;;; unhighlight case.

;;; If text-region-class? is specified, highlighting means highlighting the entire
;;; text as a text region of this class; otherwise, highlighting means highlighting
;;; by changing the background color of the cell (in a way that makes the text come
;;; out in a false color, with FOREGROUND causing foreground/background color
;;; reversal).

(defun highlight-or-unhighlight-for-slot
    (frame slot-name defining-class?
           highlight-color? unhighlight-case?
           &optional text-region-class?
           slot-component-name? slot-component-indicator?)
  (let* ((text-box-to-highlight?
           (cond
             ((and (text-box-p frame)
;                   (eq slot-name 'box-translation-and-text)        ; less highlighting?
                   )
              frame)
             ((eq slot-name 'name-or-names-for-frame)
              (loop for subblock being each subblock of frame
                    when (frame-of-class-p subblock 'name-box)        ; "get-name-box-if-any",
                      return subblock)))))        ;   here & another place!
    (when text-box-to-highlight?
      (highlight-or-unhighlight-text-box
        text-box-to-highlight? highlight-color?
        unhighlight-case? text-region-class?))
    (highlight-or-unhighlight-attribute
      frame slot-name defining-class?
      slot-component-name? slot-component-indicator?
      highlight-color? unhighlight-case? text-region-class?)))









;;;; Editor Notifications



;;; Display-editor-notification ...

(defmacro display-editor-notification (format-string &body format-args)
  `(display-editor-notification-1
     (tformat-text-string ,format-string . ,format-args)))

(defun display-editor-notification-1 (notification-string)
  (when (native-editor-workspace-p current-edit-workspace)
    (native-editor-display-notification current-edit-state notification-string))
  (erase-any-temporary-information-on-edit-workspace nil)
  (setf (temporary-information-on-edit-workspace? current-edit-state)
        'editor-notification)
  (add-to-workspace
    (make-free-text-box notification-string 'editor-notification)
    current-edit-workspace
    ;; note: use same position as put-up-menus
    (left-edge-of-block (edit-box current-edit-state))
    (+w (bottom-edge-of-block (edit-box current-edit-state))
        (workspace-margin current-edit-workspace)
        (if (and (kfep-conversion-text-region? current-edit-state) ; nec?
                 (kfep-conversion-choices? current-edit-state))
            (height-for-kanji-conversion-choices current-edit-state)
            (or (extra-space-to-leave-below-edit-box? current-edit-state)
                0)))
    t t))

;; Cleanup was done here.  In particular, upgraded the above to use the functions
;; add-to-workspace and make-free-text-box, which became available after it was
;; originally written.  That eliminated the need for make-editor-notification,
;; which had been defined below, so make-editor-notification was flushed.
;; (MHD 10/3/90)


(def-class (editor-notification text-box)
  (box-translation-and-text nil (type nil text))
  (default-text-box-format-name editor-notification-format))


(def-text-box-format editor-notification-format
  text-box-border-color? red
  text-cell-background-color? transparent ; maybe "light-gray" when color mapping
  text-cell-line-color? foreground        ;   works for B&W systems;
  text-cell-font-map (hm18)                        ; 1 en = 10 workspace units
  text-cell-line-height 20                        ; experiment with these!
  text-cell-baseline-position 15
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)                  ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)                  ; 3/2 en

  text-box-left-border-width 0
  text-box-top-border-width 4
  text-box-right-border-width 0
  text-box-bottom-border-width 0

  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0

  minimum-format-width-for-text-cell 440
  maximum-format-width-for-text-cell 440)


(def-class-method generate-spot (editor-notification mouse-pointer)
  (declare (ignore editor-notification))
  (generate-workspace-background-spot mouse-pointer))

#+obsolete
(declare-unselectable-class-of-subblock editor-notification)



;;;; The Editor Workstation Context



(define-workstation-context editing ()
  :dont-define-structure t
  :keymaps (native-editor-commands
             editor-commands
             cursor-movement-shift-variant-commands
             private-editor-commands))





;;;; Editing UI Commands (The New Way)


(def-global-property-name editor-command-p)


;;; `Name-of-current-editor-command?' is bound to nil around the body of
;;; an editor UI command.  If can be set to a command name by that body,
;;; and, if so, that value is used as the value to set into the slot
;;; (previous-edit-context-specific-event? edit-state).

(defvar name-of-current-editor-command?)


;;; The macro `define-editor-ui-command' defines an editor command.
;;; The command is always conditioned on the editor context being active.

(defmacro define-editor-ui-command (name-and-options additional-lambda-list &body body)
  (let ((name (car-or-atom name-and-options)))
    `(progn
       (setf (editor-command-p ',name) t)
       (define-ui-command ,name-and-options
           (event (edit-state workstation-context-specifics)
                  ,@additional-lambda-list)
         (when (edit-state-p edit-state)                    ; Guard against wrong context.
           (in-editing-context (edit-state)
             (let ((name-of-current-editor-command? nil))
               (prog1 ()
                 (progn ,@body)
                 (editor-post-command-hook ',name edit-state)))))))))



;;; The function `editor-post-command-hook' is called after the completion
;;; of each editor command.

(defun editor-post-command-hook (command-name edit-state)
  (setf (previous-edit-context-specific-event? edit-state)
        (or name-of-current-editor-command?
            command-name)))



;;; `Editor-catch-all' handles all of the commands not bound to any particular
;;; keystroke, but pertaining to unshifted, unmodified keystrokes.  E.g., this
;;; gets called for \, ~, a, b, c, F12, etc.  This cannot handle mouse events
;;; (e.g., mouse-down, mouse-up).  Nor should it be called to handle or Control-
;;; or Alt- characters (e.g., control-s, control-b, etc.).

(define-editor-ui-command editor-catch-all ()
  (let ((key-code (workstation-event-code event)))
    (cond
      ((key-code-type-p key-code)
       (cond
         ((cyrillic-input-mode? current-edit-state)
          (handle-cyrillic-character-in-text-event event))
         ((if (hangul-input-mode? current-edit-state)
              ;; Notice: fall through if nil returned here:  (MHD 8/24/95)
              (handle-hangul-character-in-text-event event)))
         ((unicode-bit-on-p key-code)        ; (MHD 5/17/99)
          (handle-character-in-text-event event))
         ((gensym-character-key-code-p key-code)
          (handle-character-in-text-event event))))

      ;; bug workaround -- this shouldn't ever be fired because these aren't
      ;; supposed to be considered "unshifted", but I think this a bug for FMW
      ;; to fix. (MHD 5/6/94)
      #+development
      ((special-control-key-p key-code)
       (cerror "Continue" "This should not be happening.")))))


(define-editor-ui-command unicode-character-in-text ()        ; (MHD 5/17/99)
  (handle-character-in-text-event event))


(defun handle-insertion-of-symbol (event)
  (declare (ignore event))
  (if (special-entry-context? current-edit-state)
      nil
      (enter-escape-context 'insertion-of-symbol)))


(define-editor-ui-command space-or-convert/next ()
  (if (and (kfep-conversion-text-region? current-edit-state)
           (kfep-conversion-choices? current-edit-state))
      (do-trial-kfep-conversion nil)
      (if (and (menu-choice-index? current-edit-state)
               (token-menu-choices-exist-p))
          (convert-current-menu-choice)
          (insert-typed-in-character-at-cursor #.%space))))


(define-editor-ui-command go-forward-character ()
  "Advance the cursor forward by one character"
  (cond
    ((arrows-usable-for-kfep-conversion-choices-p current-edit-state)
     (do-trial-kfep-conversion nil 'right))        ; for KFEP
    ((menu-choice-index? current-edit-state)
     (select-next-token-menu-choice 'right))
    (t
     (move-or-delete-from-cursor nil nil nil))))


(define-editor-ui-command go-backward-character ()
  "Move the cursor backward by one character"
  (cond
    ((arrows-usable-for-kfep-conversion-choices-p current-edit-state)
     (do-trial-kfep-conversion nil 'left))        ; for KFEP
    ((menu-choice-index? current-edit-state)
     (select-next-token-menu-choice 'left))
    (t
     (move-or-delete-from-cursor nil t nil))))


(define-editor-ui-command go-up-line ()
  "Move the cursor upward by one line"
  (cond
    ((arrows-usable-for-kfep-conversion-choices-p current-edit-state)
     (do-trial-kfep-conversion nil 'up))        ; for KFEP
    ((menu-choice-index? current-edit-state) ; same as left arrow for now
     (select-next-token-menu-choice 'left))
    (t
     (move-down-line -1))))


(define-editor-ui-command go-down-line ()
  "Move the cursor downward by one line"
  (cond
    ((arrows-usable-for-kfep-conversion-choices-p current-edit-state)
     (do-trial-kfep-conversion nil 'down))        ; for KFEP
    ((menu-choice-index? current-edit-state) ; same as right arrow for now
     (select-next-token-menu-choice 'right))
    (t
     (move-down-line 1))))



(define-editor-ui-command delete-backward-word ()
  (move-or-delete-from-cursor-to-next-adjacent-word t t))

(define-editor-ui-command delete-forward-word ()
  (move-or-delete-from-cursor-to-next-adjacent-word t nil))

(define-editor-ui-command go-backward-word ()
  (move-or-delete-from-cursor-to-next-adjacent-word nil t))

(define-editor-ui-command go-forward-word ()
  (move-or-delete-from-cursor-to-next-adjacent-word nil nil))



;; Added Alt-rubout -- helps Emacs users tremendously.  Consider adding
;; Control-D for delete-forward-one-character.  That would eliminate it for
;; shifting the workspace down.  Then consider using Control-U to clear input
;; from the cursor to the beginning.  Then consider using Control-X to clear
;; everything in the editor, instead of doing what control-U would now do.
;; Note that the up and down arrow keys move even when in the editor, but the
;; right and left arrow keys are rebound to move the edit cursor when in
;; the editor.  Try to make them consistent.  Also, consider what to do with
;; the keys for moving workspaces right and left (control-R and control-L
;; and left-arrow and right-arrow. (MHD 8/30/89)

(define-editor-ui-command undo ()
  (if (undo-or-redo-edit-possible-p nil)
      (undo-or-redo-edit nil)
      (display-editor-notification "There is nothing more to undo")))

(define-editor-ui-command redo ()
  (if (undo-or-redo-edit-possible-p t)
      (undo-or-redo-edit t)
      (display-editor-notification
          "There is nothing more to redo.  (You may only redo edits right after undoing them.)")))


;;; `Delete-backward-character' is usually/always bound to the standard
;;; delete key (e.g., rubout/delete/backspace).  It performs a few different
;;; functions:
;;;
;;;   - if we're in a special entry context, e.g., typing into a "type-in
;;;     box" for search or character-code entry, and the text is blank,
;;;     this exits that context;
;;;   - if we're in a Kana-to-Kanji conversion mode, this undoes the last
;;;     conversion
;;;   - if text is selected (we're showing a text region that was
;;;     highlighted), this deletes the text in that region
;;;   - if none of the above applies, this simply deletes the character
;;;     before the cursor

(define-editor-ui-command delete-backward-character ()
  (delete-character t))

(defun delete-character (backward-p)
  (cond
    ((and (special-entry-context? current-edit-state)
          (text-blank-p                                ; maybe only if empty?
            (text-being-edited current-edit-state)))
     (let ((function?
             (function-to-call-on-changed-edit-box-text?
               current-edit-state)))
       (cond
         (function?
          (funcall
            function?
            (text-being-edited current-edit-state)
            'rubout-on-blank-text))
         (t
          (abort-current-workstation-context
            type-of-current-workstation-context)))))
    ((and (kfep-conversion-text-region? current-edit-state)
          (kfep-conversion-choices? current-edit-state)
          (kfep-conversion-choice-index? current-edit-state))
     (unconvert-kfep-conversion-text-region))
    (t
     (let ((text-region? (get-selected-text-region-for-edit-box)))
       (cond
         (text-region?
          (do-delete-within-editor))
         (t
          (move-or-delete-from-cursor t backward-p nil)))))))

;; Note: clearing the selected region by typing the delete key is new
;; behavior as of G2 5.0 Rev. 3. (MHD 3/16/98)


(define-editor-ui-command delete-forward-character ()
  (delete-character nil))









;;; The function `insert-raw-text-into-editor' inserts raw ASCII text into the
;;; editor buffer at the cursor.  It is only for use in development at present.

#+development
(defun insert-raw-text-into-editor (string?)
  (when string?
    (insert-text-string-at-cursor
      (import-text-string string? 'x-cut-buffer)
      nil nil)))

;; Conses -- needs a bit of work.  Should do some conversion, e.g., handling
;; European (ISO Latin1 at least) characters.

#+development
(define-editor-ui-command delete-entire-text ()                    ; not currently in use (was bound
  (multiple-value-bind (line-index character-index)            ;   to Ctrl-X until 3/23/88 (MHD 3/23/88))
      (find-end-of-text (text-being-edited current-edit-state) 1) ; use cursor later!
    (change-edit-box
      (text-being-edited current-edit-state) 1 0
      line-index character-index)))

(define-editor-ui-command delete-backward-to-beginning ()
  (change-edit-box
    (text-being-edited current-edit-state) 1 0
    (cursor-line-index current-edit-state)
    (cursor-character-index current-edit-state)))




;;; `Move-cursor-by-page-in-editor' ...

(defun move-cursor-by-page-in-editor (direction?)
  (let* ((text-box (edit-box current-edit-state))
         (text-cell-interline-distance
           (let ((text-box-format (text-box-format text-box)))
             (+w (text-cell-line-spacing text-box-format)
                 (text-cell-line-height text-box-format))))
         (number-of-lines-to-move-down
           (*f (if (eq direction? 'forward) +1 -1) ; sign
               (-f (truncatew
                     (-w (bottom-edge-of-block text-box)
                         (top-edge-of-block text-box))
                     text-cell-interline-distance)
                   1))))
    (suppress-scroll-text-into-view
      ;; suppress autoscroll; we do it ourself as appropriate
      (move-down-line number-of-lines-to-move-down t)
      (when (frame-transforms-of-block text-box) ; = scrolling-editor-p
        (loop for image-plane
                  in (image-planes-this-is-on current-edit-workspace)
              do (funcall-method
                   'scroll-block
                   text-box
                   image-plane
                   'page
                   (if (eq direction? 'forward) 'down 'up)))))))


(define-editor-ui-command go-up-page ()
  (move-cursor-by-page-in-editor 'backward))

(define-editor-ui-command go-down-page ()
  (move-cursor-by-page-in-editor 'forward))

;; Note: move-down-line is in cahoots with go-up-page and go-down-page in that
;; it knows that they want to preserve the (x) goal position.  Later, do
;; something like (declare-goal-position-preserving-editor-command go-up-page),
;; etc.!  (MHD 3/20/98)



(define-editor-ui-command go-to-beginning ()
  (home-cursor))

(define-editor-ui-command go-to-end ()
  (home-down-cursor))

(define-editor-ui-command go-to-beginning-of-line ()
  (move-or-delete-from-cursor nil t t t))

(define-editor-ui-command go-to-end-of-line ()
  (move-or-delete-from-cursor nil nil t t))



(define-editor-ui-command insert-newline-complex-character ()
  (editor-newline))

(defun editor-newline ()
  (let ((text-region? (get-selected-text-region-for-edit-box))
        (string-to-insert '#.(stringw #.%line-separator)))
    (cond
      (text-region?
       (replace-pending-delete-text-region text-region? string-to-insert))
      (t
       (change-edit-box
         (text-tail-for-cursor current-edit-state)
         (cursor-line-index current-edit-state)
         (cursor-character-index current-edit-state)
         nil nil string-to-insert)))))


;; Alt+Enter inserts a newline if editor is selected or the mouse is over it,
;; else defers to top-level, which does selection-properties if the selection UI
;; is enabled.

(define-editor-ui-command maybe-insert-newline (mouse-pointer &optional selected-workspace workspace)
  ;; KLudge
  (cond ((or (of-class-p workspace 'edit-workspace)
             (of-class-p selected-workspace 'edit-workspace))
         (editor-newline))
        (t
         (run-top-level-event-handler mouse-pointer))))


;;; `Do-return-key-function' is the command that decides to either insert a
;;; newline in the text being edited, which it does if this is text-type slot,
;;; or to end the editing session, which it does for non-text-type slots.
;;;
;;; This is obviously only intended to be bound the keys labelled Return and
;;; Enter.  See also the commands insert-newline-complex-character and
;;; end-editing.

(define-editor-ui-command do-return-key-function ()
  (cond
    ((use-return-key-as-end-key-in-current-editor-p)
     (funcall
       (compiled-function-in-place
         (get-ui-command-function 'end-editing))
       current-workstation-event current-edit-state))
    (t
     (funcall
       (compiled-function-in-place
         (get-ui-command-function 'insert-newline-complex-character))
       current-workstation-event current-edit-state))))

;; Function above was patched on 7/25/94.  It had attempted to refer directly to
;; the function names for the defun-in-place emitted by
;; define-editor-ui-command, which doesn't exist in distribution compiles.  -jra
;; 7/25/94


(defun use-return-key-as-end-key-in-current-editor-p ()
  (let ((edit-state current-edit-state)
        #+not-ready-for-prime-time
        (frame-being-edited?
          (frame-being-edited? current-edit-state)))
    (or
      ;; KFEP ACCEPT equivalent?
      (and (kfep-conversion-text-region? edit-state)

           ;; added:  (MHD 10/5/94)
           (not (empty-text-region-p (kfep-conversion-text-region? edit-state)))

           ;; The following conditions removed per suggestion of B. Greenberg,
           ;; consultant, who also demonstrated that this would make it
           ;; consistent with other FEP's, e.g., the built-in Microsoft Japanese
           ;; Windows FEP.   (For 4.0 Beta Phase 2.)  (MHD 10/5/94)

;           (kfep-conversion-choices? edit-state)
;           (kfep-conversion-choice-index? edit-state)
           )
      (and
        ;; If scrolling editor (<=> "multiline editor"), do not ever use return
        ;; key as end key:
        (not (scrolling-editor-p edit-state))

        ;; backed out: -- maybe reconsider later! (MHD 8/15/94)
        #+not-ready-for-prime-time
        (or

          ;; inspect commands, user-settings editors, load/save dialogs:
          (or (null frame-being-edited?)
              (not
                (or (permanent-block-p frame-being-edited?)
                    (transient-p frame-being-edited?))))
          (and (non-menu-choice-permitted-p
                 'use-single-line-editor frame-being-edited?)
               (not (memq                        ; get smarter/handle class qualifier!
                      (alias-slot-name-if-necessary
                        (name-of-slot-being-edited edit-state)
                        frame-being-edited?)
                      (attributes-to-edit-using-multiline-editor
                        editor-parameters)))))))))






;;; The command `do-tab-function' either exits the editor or inserts n spaces,
;;; depending on whether the TAB key is supposed to have exit, as true when
;;; doing a "field edit", or insert whitespace.  When this is an exit, this
;;; calls end-editing noting that the type of exit from the edit context is
;;; TAB-EXIT.

(define-editor-ui-command do-tab-function ()
   (cond
     ((editing-field? current-edit-state)
      (setf (type-of-exit-from-edit-context? current-edit-state) 'tab-exit)
      (extend-parsing-as-appropriate 'end))
     (t
      (insert-n-spaces-or-tab))))


;;; Insert-n-spaces-or-tab inserts either N spaces or an actual tab character
;;; into the the text being edited.  If this is a subeditor used for special
;;; character entry, i.e., the "Alt+I" type-in box, this always inserts a
;;; straight tab character.  Also, if the number-of-spaces-to-insert-on-a-tab
;;; slot of editor-parameters is 0, this inserts a straight tab character.
;;; Otherwise, this inserts N ordinary space characters, where N is given by the
;;; number-of-spaces-to-insert-on-a-tab of editor-parameters.

(defun insert-n-spaces-or-tab ()
  (let ((text-line-to-insert
          (if (or (eq (special-entry-context? current-edit-state) 'INSERTION-OF-SYMBOL)
                  (=f (number-of-spaces-to-insert-on-a-tab editor-parameters) 0))
              (make-stringw 1 :initial-element #.%tab)
              (make-stringw
                (number-of-spaces-to-insert-on-a-tab editor-parameters)
                :initial-element #.%space))))
    (change-edit-box
      (text-tail-for-cursor current-edit-state)
      (cursor-line-index current-edit-state)
      (cursor-character-index current-edit-state)
      nil nil text-line-to-insert)
    (reclaim-text-line text-line-to-insert)))



;;; The command `end-editing' is for ending from the ENTER function key
;;; (i.e., the Return key, and possibly the Enter and End keys, where available.)

;;; `End-editing' ... If the parse is rejected by the slot value compiler, which it
;;; does by returning bad-phrase as its value, the slot being edited is not updated,
;;; and the user is informed of the (compiler's) rejection.

;;; Special Meaning for KFEP:  When the editor is in Kanji entry mode and there is
;;; a NEXT subcommand choice, this function has the special meaning that it just
;;; accepts the current Kanji choice (does a KFEP conversion).

;;; ... Before calling extend-parsing-as-appropriate with END, this notes that the
;;; type of exit from the edit context is END-EXIT.

(define-editor-ui-command end-editing ()
  (end-editing))


(defun end-editing ()
  (cond
    ((special-entry-context? current-edit-state)
     (if (function-to-call-on-changed-edit-box-text? current-edit-state)
         (funcall-symbol
           (function-to-call-on-changed-edit-box-text? current-edit-state)
           (text-being-edited current-edit-state)
           'end-editing)))
    ((and (kfep-conversion-text-region? current-edit-state)        ; ACCEPT equivalent

           ;; added:  (MHD 10/5/94)
           (not (empty-text-region-p (kfep-conversion-text-region? current-edit-state)))

          ;; The following conditions removed per suggestion of B. Greenberg,
          ;; consultant, who also demonstrated that this would make it
          ;; consistent with other FEP's, e.g., the built-in Microsoft Japanese
          ;; Windows FEP.   (For 4.0 Beta Phase 2.)  (MHD 10/5/94)

;          (kfep-conversion-choices? current-edit-state)
;          (kfep-conversion-choice-index? current-edit-state)
          )
     (accept-kfep-conversion))
    (t
     (setf (type-of-exit-from-edit-context? current-edit-state) 'end-exit)
     (extend-parsing-as-appropriate 'end))))








;;; The command `abort-editing' calls `cancel-editing', which simply checks if
;;; there have been changes to the edited text, as evidenced by a non-nil edit
;;; undo stack.  If not, this really aborts the editing context.  If there are
;;; changes that have been made, then it tries to show which editor has the
;;; focus by raising the image plane(s) of the editor to the top of the window
;;; stack (there really should just be 1 image plane), and then puts up a
;;; confirmation dialog on top of that.  The dialog, if confirmed, will cause
;;; the editing workstation context to really be aborted.  Cancelling the dialog
;;; leaves you in the editor.
;;;
;;; Note that the CANCEL subcommand also calls cancel-editing to do just the
;;; same thing.

(define-editor-ui-command abort-editing ()
  (cancel-editing))


(defun cancel-editing ()
  (cond
    ((or (null (edit-undo-stack current-edit-state))
         ;; inspect commands, user-settings editors, load/save dialogs are
         ;;   by this:
         (or (null (frame-being-edited? current-edit-state))
             (not (or (permanent-block-p (frame-being-edited? current-edit-state))
                      (transient-p (frame-being-edited? current-edit-state)))))

         ;; field edit/edit styles may choose to override usual courtesies:
         (never-confirm-cancelled-edit? current-edit-state))
     (abort-editing-current-workstation-context))
    (t
     (loop for image-plane in (image-planes-this-is-on current-edit-workspace)
           do (raise-image-plane-to-top image-plane nil))
     (confirm-or-cancel
       (tformat-text-string
         "Discard edits? (Changes made to the edited text will be lost!)")
       'abort-editing-current-workstation-context))))

;; Consider requiring confirmation here if any work is about to be lost.  Or
;; else consider requiring confirmation here if "a lot" of work is about to be
;; lost, where "a lot" is either (a) n minutes, (b) n calls to change-edit-box
;; (c) undo stack of length n, or some combination of these, and also consider
;; making this a user parameter.  Also, maybe treat special entry and type-in
;; box contexts differently.  Also, however this works, the icon editor and
;; other systems want to work -- keep them similar! (MHD 10/27/89)


(defun abort-editing-current-workstation-context ()
  (abort-current-workstation-context 'editing))





;(define-editor-ui-command special-character-entry ()
;  (handle-special-character-entry-event event))

(define-editor-ui-command insert-accented-or-special-or-coded-character ()
  (handle-insertion-of-symbol event))

;(define-editor-ui-command kanji-code-entry ()
;  (handle-kanji-code-entry-event event))

;(define-editor-ui-command hangul-code-entry ()
;  (handle-hangul-code-entry-event event))

;(define-editor-ui-command cyrillic-code-entry ()
;  (handle-cyrillic-code-entry-event event))





;;; `Mouse-up-in-editing-context' is invoked when a subcontext aborts prior
;;; to consuming the mouse up that goes with the mouse down that created it.

(define-event-handler mouse-up-in-editing-context ())        ; ignored

;; Does the top level keymap do this?



(define-editor-ui-command cycle-to-next-kana ()
  (case (natural-language-for-editor? current-edit-state)
    (korean
     (if (hangul-input-mode? current-edit-state)
         (exit-hangul-input-mode)
         (enter-hangul-input-mode)))
    (japanese
     (case (if (kfep-conversion-text-region? current-edit-state)
               (kana-conversion-mode? current-edit-state))
       ((nil)
        (cond
          ((kfep-conversion-text-region? current-edit-state)
           (enter-kana-conversion-mode 'katakana))        ; kanji -> katakana
          (t (enter-kana-conversion-mode nil))))        ; english -> kanji
       (hiragana (exit-kfep-mode-if-necessary))        ;   hiragana -> english
       (katakana (enter-kana-conversion-mode 'hiragana))        ; katakana -> hiragana
       ))
    (russian
     (if (cyrillic-input-mode? current-edit-state)
         (exit-cyrillic-input-mode)
         (enter-cyrillic-input-mode))
     )))


(define-editor-ui-command enter-kanji-mode ()
  (when (eq (natural-language-for-editor? current-edit-state) 'japanese)
    (enter-kana-conversion-mode nil)))        ; any mode -> kanji

;; Note that this is equivalent to clicking on the Kanji button -- and is
;; equivalent to skipping and accepting the contents of the previous
;; kfep conversion text region, if any (i.e. if we were in Kanji mode
;; already.




(define-editor-ui-command go-up-one-row-in-kfep-conversion-choice-menu ()
  (if (arrows-usable-for-kfep-conversion-choices-p current-edit-state)
      (do-trial-kfep-conversion nil 'up)))


(define-editor-ui-command go-down-one-row-in-kfep-conversion-choice-menu ()
  (if (arrows-usable-for-kfep-conversion-choices-p current-edit-state)
      (do-trial-kfep-conversion nil 'down)))

;; See go-forward(/backward)-character for the left(/right) function.


(define-editor-ui-command skip-kfep-conversion ()
  (when (and (kfep-conversion-text-region? current-edit-state)        ; SKIP equivalent
             (and (null (kana-conversion-mode? current-edit-state))
                  (not (and (kfep-conversion-choices? current-edit-state)
                            (kfep-conversion-choice-index? current-edit-state)))
                  (not (and (=f (cursor-line-index current-edit-state)
                                (line-index-for-fixed-end-of-text-region
                                  (kfep-conversion-text-region? current-edit-state)))
                            (=f (cursor-character-index current-edit-state)
                                (character-index-for-fixed-end-of-text-region
                                  (kfep-conversion-text-region? current-edit-state)))))))
    (skip-kfep-conversion)))



;;; Arrows-usable-for-kfep-conversion-choices-p ... returns true if it is
;;; appropriate to do a trial kfep conversion specifying an arrow direction,
;;; e.g., (do-trial-kfep-conversion nil 'up).  This function is called with
;;; an edit state argument because it can be used in any workstation context,
;;; not necessarily in a current edit context, to determine its value.

(defun arrows-usable-for-kfep-conversion-choices-p (edit-state)
  (and (kfep-conversion-text-region? edit-state)
       (kfep-conversion-choices? edit-state)
       (kfep-conversion-choice-index? edit-state)
       (not (eq (cadr (kfep-conversion-choices? edit-state)) t))))



(define-editor-ui-command shrink-kfep-conversion-text-region ()
  (when (if (kfep-conversion-text-region? current-edit-state)        ; ABSTRACT! cloned from update-kfep-buttons!!
            (and (kfep-conversion-choices? current-edit-state)
;                       (multiple-value-bind    ; adj. posn. can't precede fixed end
;                         (adjacent-line-index? adjacent-character-index?)
;                           (find-position-adjacent-to-end-of-kfep-conversion-text-region t)
;                         (not (or (<f adjacent-line-index?   ; (and adjacent-line-index? ...)!
;                                      (line-index-for-fixed-end-of-text-region
;                                 (kfep-conversion-text-region? current-edit-state)))
;                                  (and (=f adjacent-line-index?
;                                           (line-index-for-fixed-end-of-text-region
;                                             (kfep-conversion-text-region? current-edit-state)))
;                                       (<f adjacent-character-index?
;                                           (character-index-for-fixed-end-of-text-region
;                                             (kfep-conversion-text-region? current-edit-state)))))))
                 ))
    (expand-or-shrink-kfep-conversion-text-region nil)))

(define-editor-ui-command expand-kfep-conversion-text-region ()
  (when (if (kfep-conversion-text-region? current-edit-state)        ; ABSTRACT! cloned from update-kfep-buttons!!
            (and (kfep-conversion-choices?
                   current-edit-state)
                 (multiple-value-bind                ; have adjacent position that cursor doesn't precede; nec?
                     (adjacent-line-index? adjacent-character-index?)
                     (find-position-adjacent-to-end-of-kfep-conversion-text-region
                       nil)
                   (and adjacent-line-index?
                        (not (or (<f (cursor-line-index current-edit-state)
                                     adjacent-line-index?)
                                 (and (=f (cursor-line-index current-edit-state)
                                          adjacent-line-index?)
                                      (<f (cursor-character-index current-edit-state)
                                          adjacent-character-index?))))))))
    (expand-or-shrink-kfep-conversion-text-region t)))

;; Abstract and make common more of the code between kfep keyboard commands above
;; and their equivalent kfep subcommand buttons!!!







(defun home-cursor ()
  (move-or-delete-from-cursor nil t t))

(defun home-down-cursor ()
  (move-or-delete-from-cursor nil nil t))


;;; Get-next-token-if-available does token parsing forward from the current
;;; position for parsing specified in current-edit-state, returning either four,
;;; five, or six values.  The third and fourth values are always the index of the
;;; line it ends in and the index of the character just past of the token or
;;; partial token.

;;; This is a short summary of return value cases:
;;;
;;;   (1) a token:
;;;           <token>       <type>            <line> <char> <text-tail>
;;;                                                          <self-terminating-p>
;;;   (2) a partial token
;;;           <string>      <types>           <line> <char>
;;;   (3) cursor or end of text
;;;           NIL           NIL               <line> <char>
;;;   (4) an ellipsis
;;;           NIL           ELLIPSIS          <line> <char>
;;;   (5) an (uncompleted) comment
;;;           NIL           COMMENT           <line> <char>
;;;   (6) an (uncompleted) quoted-character
;;;           NIL           QUOTED-CHARACTER  <line> <char>
;;;   (7) otherwize, aka more illegal tokens
;;;           <text string> NIL               <line> <char> <text-tail>
;;;
;;; where <type> means a token type, <types> means a list of possible token types,
;;; <line> means a line index, and <char> means a character index.
;;;
;;;
;;; These cases are discussed in detail below.
;;;
;;;   (1) Six values: a token; its type (SYMBOL, PUNCTUATION-MARK, INTEGER, FLOAT,
;;;   WHOLE-STRING, LEFT-STRING, MIDDLE-STRING, RIGHT-STRING); the index of the
;;;   line it ends in; the index of the character just past it; the  text tail
;;;   for the line it ends in; and non-nil if the token is "self-terminating"
;;;   (as strings and certain punctuation marks are).  The self-terminating
;;;   value is used for prompting.  After completion of a self-terminating token,
;;;   the user is prompted as if he typed a space.  Note also that left-string,
;;;   middle-string, and right-string are not always possible return values.
;;;   It depends on the grammar category for the slot being edited.
;;;
;;;   (2) Four values, when the cursor or end of text is encountered before a
;;;   token is definitely complete but while a legal token is still possible
;;;   (which cannot be when the cursor is beyond the beginning of an ellipsis
;;;   in a position where a token is not possible): a not-to-be-reclaimed list
;;;   of potential token types; a prefix token string (a simple text string
;;;   representing the beginning of an incomplete token but having no more
;;;   than maximum-suggested-length-for-simple-text-strings simple characters,
;;;   with case normalization for symbols and without delimiters for strings,
;;;   which can be completed to give instances of each of the potential token
;;;   types); the index of the line where the incomplete ends; and the index
;;;   of the character just past the end of the incomplete token;
;;;
;;;   (3)  If the cursor or end of text is encountered before any non-space,
;;;   then four values are returned  (i.e. NIL, NIL, <line-index> and
;;;   <character-index>);
;;;
;;;   (4) Whenever an ellipsis is encountered, four values are returned:
;;;   (NIL, ELLIPSIS, <line-index> and <character-index>);
;;;
;;;   (5) if the cursor or end of text is encountered within a comment then
;;;   four values are returned (i.e. NIL, COMMENT, <line-index> and
;;;   <character-index>);
;;;
;;;   (6) If the end of text is encountered immediately after the quoting
;;;   character (@) and when none of the previous cases apply then four
;;;   values are returned (i.e. NIL, QUOTED-CHARACTER, <line-index> and
;;;   <character-index>);
;;;
;;;   (7) finally when a legal token cannot be produced here and none of
;;;   the previous cases apply (in which case an ellipsis should be inserted if
;;;   not already present): a not-to-be-reclaimed text string expressing a
;;;   reason as an uncapitalized and unpunctuated sentence; nil; the index of
;;;   the line it last used; the index of the character it last used; and the
;;;   text tail for the line it last used.

;;; In the incomplete token case, there is a limit to the size of prefix
;;; token string that can be returned.  For extremely long incomplete symbols,
;;; this could result in inappropriate entries in token menus and/or ellipsis
;;; insertion too far to the right.

;; Consider allowing an arbitrary-length prefix token string to be returned
;; in the incomplete token case, to avoid menu and ellipsis position anomalies.

;; For the incomplete-token and illegal-token cases, consider returning the
;; previous position.

;; For the incomplete-token case, also return a flag to indicate that a
;; legal token could have been made from the characters in the prefix token
;; string if there had been a space in place of the cursor or end of text!
;; (This implies that certain code herein should be abstracted into
;; subfunctions.)

;; The maximum number of values returned is 6.  If any more values are to be
;; returned, twith-output-to-then-use-of-wide-string has to be modified to
;; handle those values.

;; Check that a returned text tail is always correct!

(defmacro get-next-token-if-available (cursor-line-index? cursor-character-index?)
  `(get-next-token-from-text-if-available
     (determine-appropriate-tokenizer)
     ,cursor-line-index?
     ,cursor-character-index?
     (car
       (car (stack-of-positions-after-tokens current-edit-state)))
     (cadr                                        ; index of next character, 0 at end
       (car (stack-of-positions-after-tokens current-edit-state)))
     (text-tail-for-parsing current-edit-state)
     (car
       (stack-of-incomplete-phrases-at-earlier-positions
         current-edit-state))))


;; Another party which has gone on much too long.

(define-event-handler handle-mouse-down-event-in-edit-context
    (mouse-pointer
      (mouse-event event)
      innermost-spot
      (edit-state
        workstation-context-specifics))
  (in-editing-context (edit-state)
    (multiple-value-bind (object-near-cursor? image-plane x-in-window y-in-window)
        (find-object-near-workstation-event
          mouse-event nil '(text-region small-edit-cursor
                            ;; Added small-edit-cursor. fmw, 12/22/93
                            edit-cursor text-highlight-bar
                            ;; Added a few more:
                            icon-cell editor-subcommand-button)) ; (MHD 10/11/99)

      ;; The difference between object-near-cursor? and the object stored in
      ;; the spot is that object-near-cursor? additionally excludes text-region
      ;; and text-highlight-bar.

      (let* ((block-near-cursor?
               (if (and object-near-cursor? (framep object-near-cursor?))
                   object-near-cursor?))
             (inheritance-path?
               (if block-near-cursor?
                   (class-inheritance-path
                     (class-description-slot block-near-cursor?))))
             (superblock?
               (if block-near-cursor?
                   (superblock? block-near-cursor?)))

             (click-on-editor?
               (memq image-plane                ; on this editor's image plane?
                     (image-planes-this-is-on
                       (edit-workspace edit-state)))))

        ;; "(null inheritance-path?)" is means -- picked no object.
        ;; but (null object-near-cursor?) doesn't due to connection structures
        ;; -- There are N ways of saying "Click is in current editor workspace"
        ;;   1. click-in-current-editor-p
        ;;   2. (memq image-plane (image-planes-this-is-on
        ;;                           (edit-workspace current-edit-state)))
        ;;   3. (eq (get-workspace-if-any object-near-cursor?)
        ;;          (edit-workspace current-edit-state))
        ;;   4. (eq image-plane -- rarely
        ;;           (workstation-context-return-information
        ;;                           current-workstation-context))
        (cond

          ;; Let the user dismiss a special entry sub-editor
          ;; by clicking outside of the sub-editor's mini-workspace.
          ((and (special-entry-context? current-edit-state)
                (not (eq                ; a kludge: exception to this rule for search
                       (special-entry-context? current-edit-state)
                       'search-for-text-in-editor))
                (or (not
                      (eq image-plane
                          (workstation-context-return-information
                            current-workstation-context)))
                    (null inheritance-path?)
                    (not (inheritance-path-memq 'text-inserter inheritance-path?))))
           (unless (or (eq image-plane
                           (workstation-context-return-information
                             current-workstation-context))
                       click-on-editor?)
             (requeue-workstation-event current-workstation mouse-event)
             (abort-current-workstation-context 'editing))

           ;; [Is it necessary to have this call here and the one below?! -mhd]
           (when (and (subcommand-menu-button-spot-p innermost-spot)
                      click-on-editor?)

             (with-workstation-context-continuation (do-edit-subcommand)
               (enter-subcommand-context
                 ;; Obsolete args: object-near-cursor? image-plane x-in-window y-in-window
                 mouse-pointer))))


          ;;    Automatically completing an edit would be nice in some
          ;; situations: for example, when the user clicks in another slot
          ;; of the same table.  This code does just that, but it
          ;; needs to have the predicate that triggers the autocompletion
          ;; reconsidered.
          ;;   The real issue here is: when is it approprate to commit an
          ;; edit.  Generally it is wrong if the user just did a random
          ;; click someplace.  It is ok if the slot we are editing
          ;; has a small side effect, or is actually committed later,
          ;; as in a dialog.
          ((and (eq (type-of-modal-context? current-workstation)
                    'g2-login)
                (or (null inheritance-path?)        ; not on an edit workspace
                    (not
                      (or (eq (get-workspace-if-any object-near-cursor?)
                              (edit-workspace current-edit-state))
                          (inheritance-path-memq        ; on a token menu put up by clicking
                                        ;   on a category menu?
                            'token-menu inheritance-path?)))))

;       ;; If in a g2 login modal context and there's a click not on
;       ;;   this edit workspace, try to end the current edit context,
;       ;;   and, in any case, exit it and put the event back.
;       ;; (The code for this should be better abstracted!!)
;       ;; (Maybe do this for other modal contexts, too!!)
;       (let ((keep-edit-workspace-hidden-no-matter-what? t))
;         (let* ((editing-context current-workstation-context))
;           (finish-parsing-insofar-as-possible)
;           (if (eq current-workstation-context editing-context)
;               (progn
;                 (exit-current-workstation-context)
;                 nil)
;               t)))
;       ;; put back event
;       (requeue-current-workstation-event current-workstation)

           ;; For now, just exit (abort) and put back the event
           (requeue-workstation-event current-workstation mouse-event)
           (abort-current-workstation-context 'editing))

          ;; All the cases that can exit the current context have been
          ;;   exhausted now.

          ;; New case added -- done initially to support the check boxes
          ;; on the new Load KB dialog.  (MHD 7/8/93)
          ((and click-on-editor?
                (or (inheritance-path-memq 'button inheritance-path?)
                    (and superblock?
                         (frame-of-class-p superblock? 'button))))
           ;; Used to enter selection context here.
           (let ((button
                   (if (inheritance-path-memq 'button inheritance-path?)
                       object-near-cursor?
                       superblock?)))
             (enter-button-down-context button image-plane)))


          ((or (null inheritance-path?)
               (not (inheritance-path-memq 'block inheritance-path?)))

           ;; Defer handling of a mouse-down on anything other than a
           ;;   block to top-level mouse-down handler.
           (run-top-level-event-handler mouse-pointer))

          ;; Inheritance-path? is now known not to be nil and to contain
          ;;   BLOCK; therefore object-near-cursor? is now known to be
          ;;   a block.

          ((let ((workspace-for-selected-block
                   (get-workspace-if-any object-near-cursor?)))
             (or
               ;; OLD:  (MHD 4/30/91)
;           ;; edit workspace other than mine?
;           (and (frame-of-class-p
;                  workspace-for-selected-block 'edit-workspace)
;                (not (eq workspace-for-selected-block
;                         current-edit-workspace)))
               ;; icon editor workspace?
               (frame-of-class-p
                 workspace-for-selected-block 'icon-editor-workspace)
               ;; user settings editor workspace?
               (frame-of-class-p
                 workspace-for-selected-block 'user-settings-editor-workspace)))
           ;; Defer mouse-down on edit workspaces other than mine (including
           ;;   icon editor workspaces) to top-level mouse-down handler.

           (run-top-level-event-handler mouse-pointer))

          ;; If object-near-cursor? is on an edit workspace, then we now
          ;;   know that it is on this edit context's edit workspace ("it's
          ;;   mine").

          ((and (subcommand-menu-button-spot-p innermost-spot)
                (eq (get-workspace-if-any object-near-cursor?)
                    current-edit-workspace))
           ;; Enter subcommand context on mouse-down on a subcommand menu.
           (with-workstation-context-continuation (do-edit-subcommand)
             (enter-subcommand-context
               ;; Obsolete Args: object-near-cursor? image-plane x-in-window y-in-window
               mouse-pointer)))

          ((and (inheritance-path-memq 'editor-notification inheritance-path?)
                (eq (get-workspace-if-any object-near-cursor?)
                    current-edit-workspace))
           ;; Extend parsing when there's a click on an editor notification,
           ;;   and this will serve to delete the notification, too.
           (extend-parsing-as-appropriate 'no-autocompletion))

          ((and (inheritance-path-memq 'category-menu inheritance-path?)
                (eq (get-workspace-if-any object-near-cursor?)
                    current-edit-workspace))
           ;; Put up something appropriate on mouse-down on a category menu.
           ;;   (This is the "any instance" case.)
           (let ((token-cell?
                   (pick-cell-from-table
                     object-near-cursor?
                     ;; changed for 6.0 to find nearest cell, and not only if in
                     ;; text (MHD 9/14/99)
                     image-plane x-in-window y-in-window nil t)))
             (when token-cell?
               (let ((token-text-string
                       (convert-text-to-text-string (text? token-cell?))))
                 (multiple-value-bind (token-value
                                        token-type-or-partial-types)
                     (get-next-token-if-available        ; or keep prefix-token-string?
                       (cursor-line-index current-edit-state)        ;  in edit-state?
                       (cursor-character-index current-edit-state))
                   (declare (ignore token-type-or-partial-types))        ; unused
                   (let* ((category-symbol
                            (getfq (text-cell-plist token-cell?) 'choice)))
                     (let ((menu-of-names
                             (make-menu-of-names-from-directory
                               category-symbol
                               (if (text-string-p token-value)
                                   token-value
                                   nil))))

                       (when (text-string-p token-value)
                         (reclaim-text-string
                           token-value))
                       (cond
                         (menu-of-names
                          (let* ((workspace
                                   (make-workspace        ; use a fatter border width?
                                     'category-instance-menu-workspace nil
                                     (make-token-menu-table
                                       menu-of-names
                                       (if (eq category-symbol 'object-name)
                                           (object-name-menus-in-upper-case?
                                             editor-parameters))
                                       category-symbol)))
                                 (old-image-plane?
                                   (menu-of-names-image-plane? current-edit-state))
                                 (old-workspace?
                                   (get-item-if-item-reference
                                     (menu-of-names-workspace? current-edit-state))))
                            (cond
                              ((and old-image-plane? old-workspace?
                                    (eq (workspace-on-image-plane? old-image-plane?)
                                        old-workspace?)
                                    ;; The following test allows users to keep a
                                    ;;   menu-of-names workspace by naming it, which
                                    ;;   is a documented feature.
                                    (null (name-or-names-for-frame old-workspace?)))
                               (transform-image
                                 old-image-plane? workspace nil nil nil nil
                                 (right-edge-of-block workspace)
                                 (top-edge-of-block workspace)
                                 (-r (right-edge-of-pane-in-window old-image-plane?)
                                     11)
                                 (+r (top-edge-of-pane-in-window image-plane)
                                     11))
                               (delete-frame old-workspace?))
                              (t
                               (setf (menu-of-names-image-plane? current-edit-state)
                                     ;; (This behavior is old.  (MHD 1/8/91))
                                     (put-workspace-on-pane
                                       workspace (pane-for-image-plane image-plane)
                                       'right 'top nil))))
                            (setf (menu-of-names-workspace? current-edit-state)
                                  (get-reference-to-item-if-item workspace))
                            (reclaim-grammar-list menu-of-names)))
                         (t (display-editor-notification
                                "Enter ~a" token-text-string))))))
                 (reclaim-text-string token-text-string)))))

          ;; Clicked directly over the cursor: do nothing.
          ;; In 3.3, this would operate on the editor workspace itself.
          ;; In 4.0alpha, this would pop up the menu for the cursor object!
          ;; -fmw, 12/22/93
          ((inheritance-path-memq 'blinker inheritance-path?))

          (t
           (let* (text-box-or-table
                   text-cell-format
                   cell?
                   (text-cell? nil)
                   left-edge-of-area top-edge-of-area
                   right-edge-of-area bottom-edge-of-area
                   line-index-for-fixed-end character-index-for-fixed-end
                   text-region
                   x-in-workspace
                   y-in-workspace)
             (when object-near-cursor?
               (let ((current-image-plane image-plane))
                 (with-raw-window-transform-and-draw-area
                     ((gensym-window-for-image-plane image-plane))
                   (with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
                     (with-frame-transform-of-block-if-any (object-near-cursor?)
                       (setf x-in-workspace (x-in-workspace x-in-window))
                       (setf y-in-workspace (y-in-workspace y-in-window)))))))

             (cond
               ;; mark text during edit?
               ((and
                  ;; New for 4.0 -- a way to control something that might be
                  ;; thought of as "secondary selection".  A cool feature that
                  ;; Dave and Ben thought would be helpful.  The only other place
                  ;; that knows about this is in FILTERS -- see it for the grammar
                  ;; rule. (MHD 5/20/94)
                  (or (non-menu-choice-permitted-p
                        'allow-selection-of-outside-text-from-editor
                        (frame-being-edited? current-edit-state))

                      (inheritance-path-memq 'edit-box inheritance-path?)
                      (inheritance-path-memq 'token-menu inheritance-path?)
                      (inheritance-path-memq 'kfep-conversion-choice-menu inheritance-path?))

                  ;; Check this restriction on the item under the mouse.
                  (non-menu-choice-permitted-p 'allow-selection-of-text block-near-cursor?)


                  ;; This slot is usually nil (allowing secondary selection), but
                  ;; it can be overridden by the launcher for field editor using
                  ;; the new edit-style mechanism:  (MHD 8/15/94)

                  ;; Confusingly, the edit-style slot which controls this option
                  ;; is named allow-outside-text-selection, and NOT
                  ;; allow-secondary-selection, which means something else.
                  ;; -fmw, 8/21/95
                  (not (do-not-allow-secondary-selection? current-edit-state))

                  ;; This is one of many table or text boxes.
                  (or
                    ;; Any of the many single cell tables and text-boxes
                    (loop for class
                              in '(edit-box scrap statement name-box
                                   label-box message running-head page-number
                                   free-text borderless-free-text
                                   command)        ; added (MHD 6/18/90)
                          thereis
                          (inheritance-path-memq class inheritance-path?))

                    ;; Not menus with two exceptions and otherwise most tables,
                    ;; assuming we are over a cell.
                    (and
                      (or (inheritance-path-memq 'token-menu inheritance-path?)
                          (inheritance-path-memq 'kfep-conversion-choice-menu inheritance-path?)
                          (and (inheritance-path-memq 'table inheritance-path?)
                               (not (inheritance-path-memq 'menu inheritance-path?))))

                      ;; It is this clause which returns NIL, causing clicks outside of the
                      ;; text in a token menu of colors to put up the workspace menu, instead
                      ;; of inserting the color.  A bug in 3.0 and 4.0. -fmw, 2/13/95
                      (multiple-value-setq-some
                          (cell? text-box-or-table
                                 nil nil ;; ignore column & row indexes
                                 left-edge-of-area top-edge-of-area
                                 right-edge-of-area bottom-edge-of-area)
                          (pick-cell-from-table
                            object-near-cursor?
                            image-plane x-in-window y-in-window
                            t ; only if in or near text
                            ))
                      (if (not (cell-is-block-p cell?))
                          (setq text-cell? cell?))))

                  ;; As long as it's visible or scrap.
                  (or (text-visible-p
                        (setq text-cell-format
                              (if text-cell?
                                  (text-cell-format text-cell?)
                                  (progn
                                    (setq text-box-or-table object-near-cursor?)
                                    (text-box-format text-box-or-table))))
                        (if text-cell?
                            (text-cell-plist text-cell?)
                            (text-cell-plist-for-text-box text-box-or-table))
                        (image-x-scale image-plane)
                        (image-y-scale image-plane))
                      (inheritance-path-memq 'scrap inheritance-path?))

                  ;; Is this click actually on the text?
                  (progn
                    ;; First bind up the edge-of-area rectangle if it ain't bound yet.
                    (unless text-cell?
                      (setq left-edge-of-area
                            (+w (left-edge-of-block text-box-or-table)
                                (text-box-left-border-width text-cell-format)))
                      (setq top-edge-of-area
                            (+w (top-edge-of-block text-box-or-table)
                                (text-box-top-border-width text-cell-format)))
                      (setq right-edge-of-area
                            (-w (right-edge-of-block text-box-or-table)
                                (text-box-right-border-width text-cell-format)))
                      (setq bottom-edge-of-area
                            (-w (bottom-edge-of-block text-box-or-table)
                                (text-box-bottom-border-width text-cell-format))))
                    ;; Now see if we clicked on the text.
                    (or
                      ;; Oh edit in place, is always close enough.
                      (and (eq object-near-cursor? (edit-box current-edit-state))
                           (specific-image-plane-on-which-to-edit-in-place?
                             current-edit-state))
                      ;; In the text region?
                      (point-inside-rectangle-p
                        x-in-workspace y-in-workspace
                        (+w left-edge-of-area
                            (halfw (text-cell-left-margin text-cell-format)))
                        (+w top-edge-of-area
                            (halfw (text-cell-top-margin text-cell-format)))
                        (-w right-edge-of-area
                            (halfw (text-cell-right-margin text-cell-format)))
                        (-w bottom-edge-of-area
                            (halfw (text-cell-bottom-margin text-cell-format))))
                      ;; This last clause is necesary to get scrolled editor to fire.
                      (edit-box-spot-p innermost-spot)))

                  ;; Finally! see if he is actually hitting some text to mark.
                  (multiple-value-setq
                      (line-index-for-fixed-end character-index-for-fixed-end)
                    (find-position-in-text                ; returns nil if not in or near text
                                        ; Note that this would be guaranteed
                                        ;   to return non-nil if not for the
                                        ;   last arg, only-if-within-or-near-text?,
                                        ;   being T.
                      (if (null text-cell?) text-box-or-table) text-cell?
                      left-edge-of-area top-edge-of-area t
                      x-in-workspace y-in-workspace nil nil nil
                      (if (loop for class in '(scrap edit-box)
                                thereis                ; defeat text-visible-p test, as done above
                                (inheritance-path-memq
                                  class inheritance-path?))
                          nil
                          (if (not (or (inheritance-path-memq
                                         'token-menu inheritance-path?)
                                       (inheritance-path-memq
                                         'kfep-conversion-choice-menu inheritance-path?)))
                              t))                        ; token menus are different.
                      (inheritance-path-memq 'scrap inheritance-path?))))

                (when (eq text-box-or-table (edit-box current-edit-state))
                  ;; if press on the edit box text:

                  ;; To move edit cursor to the mouse:
                  ;;             (if (eq text-box-or-table (edit-box current-edit-state))
                  ;;                 (change-edit-box
                  ;;                   nil nil nil
                  ;;                   nil nil nil
                  ;;                   x-in-workspace y-in-workspace))

                  ;; Delete the currently selected region, if any:  (MHD 3/16/98)
                  (let ((text-region? (get-selected-text-region-for-edit-box)))
                    (when text-region?
                      #+development
                      (test-assertion (not (eq object-near-cursor? text-region?)))
                      (deselect-current-text-region text-region?))))

                (setq text-region
                      (or (if (inheritance-path-memq 'scrap inheritance-path?)
                              (select-text-region-in-scrap
                                text-box-or-table
                                x-in-workspace y-in-workspace))
                          ;; NEW:   -- for 3.0, mark entire "attribute-description"
                          ;; (slot-name) cells' text, ala text inserters, for insertion
                          ;; as slot name with hyphens.  Needs more work, esp. in
                          ;; MENUS.  (MHD 4/29/91)
                          (if (and (inheritance-path-memq 'table inheritance-path?)
                                   text-cell?        ; nec?!
                                   (attribute-table-p text-box-or-table)
                                   ;; is this cell an attribute description?
                                   (loop for row in (table-rows text-box-or-table)
                                         thereis (and (cdr row)
                                                      (eq (car row) text-cell?))))
                              (make-text-region
                                text-box-or-table text-cell? 1 0 'end))
                          (make-text-region
                            text-box-or-table text-cell?
                            line-index-for-fixed-end character-index-for-fixed-end)))
                (frame-serial-number-setf (frame-reference-number-of-workstation-context current-edit-state)
                                          (current-frame-serial-number))
                (select-current-text-region text-region)
                (with-workstation-context-continuation
                    (continue-edit-after-mouse-watch)
                  (enter-mouse-watch-state mouse-pointer text-region))
                )

               ((and (eq object-near-cursor? (edit-box current-edit-state))

                     ;; REMOVED: This would cause you to not move your cursor or handle
                     ;; edit option buttons at reduced scale!
                     ;; (MHD 5/14/92)
;                 (null
;                   (specific-image-plane-on-which-to-edit-in-place?
;                     current-edit-state))

                     )
                ;; Do something else in this case? (Can only happen if text not
                ;;   visible.)  Perhaps, zoom back up at full scale?
                (change-edit-box
                  nil nil nil
                  nil nil nil
                  x-in-workspace
                  y-in-workspace))

               (t
                ;; If nothing left, defer to top-level mouse-down handler.
                (run-top-level-event-handler mouse-pointer))))))))))

;; For menu-of-names workspace, consider either (a) deleting it just when any menu
;; choice is clicked on (off of the main edit workspace); (b) maintaining the set
;; according to what's typed once it's been put up; (c) deleting it once its
;; parent category is no longer valid; or (d) not deleting the workspace
;; automatically at all until the editing session ends.  Also consider putting a
;; header at the top that says the category and the initial substring, if any, to
;; which this set of choices corresponds.
;;
;; Before changes of today, the menu-of-names workspace would stay around forever
;; until explicitly deleted by a user choosing delete-workspace from its menu or
;; until a user clicked on one of its choices or until the KB was cleared.  Many
;; users thought of such behavior as buggyness.  Some lingering impression of
;; buggyness may be reduced further by implementing some of the above suggestions.
;; (MHD 1/8/91)

;; Note that, at present, a token menu item is a single line.

;; We unconditionally space after each token from a menu, which is good enough
;; for now, but not permanently!  The following would be some good heuristics:
;;
;;   no space after left brackets
;;   no space before right brackets
;;     (means you might have to rub out the one you put in last)
;;   ...
;;
;; This also applies to the "autocompletion" mechanism in
;; update-edit-menus-or-autocomplete-as-appropriate.
;;
;; It is not clear how spacing rules would work if text from menus went into the
;; workstation event queue.  Also, right now, only single characters can go into
;; the input buffer, so this would be far too slow.



;;; `maybe-enter-marking-context-after-selection' was here.


;; I need to write a short essay on this damn text-region's life cycle.

;;   editing-context's mouse-down handler
;;     -- creates the text-region
;;   workstation context selection-context
;;     -- takes the text region, but ignore it.
;;   maybe-enter-marking-context-after-selection (return function of selection-context)
;;    -- continuation of the selection-context
;;    -- passes it on to..
;;   text-marking workstation context
;;    -- passes it on to continuation function as return value.
;;    -- reclaims it if aborted.
;;   continue-by-creating-insert-text-command
;;    -- create a command that will reclaim it.
;;   continue-from-text-region-by-posting-cut-copy-paste-menu
;;    -- creates a menu of commands.
;;      -- each command will reclaim it.
;;      -- no-choice case in menu will reclaim it.

;; One un-amuzing subplot here is that change-edit-box, the central bottle neck
;; of editor, doesn't cotton to text-regions.  It will delete any text-regions
;; it encounters in the edit-box.  Therefore commands must delete the
;; text-region before they fall into that routine.


;;; `Continue-edit-after-mouse-watch' may enter a new workstation context,
;;; namely a marking context, or it may insert text clicked on, or it may
;;; move the cursor (if a click happened in the editor).
;;;
;;; This assumes it is called in a context in which the current top of the
;;; workstation context stack contains an edit state as its specific structure.
;;; It also assumes that that edit state has been validated, in particular
;;; that it contains a non-deleted edit workspace, which further implies that
;;; the frame being edited has not been deleted.

(defun continue-edit-after-mouse-watch (workstation-context)
  (let ((edit-state (specific-structure-for-workstation-context
                      workstation-context)))
    (with-workstation-context-return-values (status mouse-pointer text-region?)
      ;; Mouse watch doesn't guard the datum it passes along.
      (when (and text-region?
                 (not (valid-block-in-workstation-context-p
                        text-region? edit-state)))
        (setf status :abort)) ;; rebind.
      (case status
        (:abort
         ;; User abort, or something was deleted, maybe the text region.
         (in-editing-context (edit-state)  ; see bug HQ-2057053
           (let ((text-region (text-region-of-edit-state? edit-state)))
             (deselect-current-text-region
               (if (valid-block-in-workstation-context-p text-region edit-state)
                   text-region)))))
        (:select
         (in-editing-context (edit-state)
           (cond
             ((eq (edit-box edit-state) (superblock? text-region?))
              (deselect-current-text-region text-region?)
              (with-mouse-pointer-bindings (line-index character-index)
                  mouse-pointer
                (change-edit-box-cursor-position line-index character-index)))
             (t
              (let ((text-string?
                      (text-string?-to-insert-from-text-region
                        mouse-pointer text-region?))
                    (superblock? (superblock? text-region?)))
                (deselect-current-text-region text-region?)
                (when text-string?
                  (when (=f 0 (text-string-length text-string?))
                    (reclaim-text-string (shiftf text-string? nil))))
                (if text-string?
                    (auto-insert-text-from-block text-string? superblock?)
                    (run-top-level-event-handler mouse-pointer)))))))
        (:drag
         (with-mouse-pointer-bindings (image-plane) mouse-pointer
           (if (eq (superblock? text-region?) (edit-box edit-state))
               ;; Selecting Text in this editor
               (with-workstation-context-continuation
                   (continue-editing-by-posting-cut-copy-paste-menu)
                 (enter-text-marking-state
                   text-region?
                   image-plane
                   (edit-workspace edit-state))) ; revise arglist order?!
               ;; Selecting Text from some random text on screen.
               (with-workstation-context-continuation
                   (continue-editing-by-doing-insert-selected-text-command)
                 (enter-text-marking-state
                   text-region?
                   image-plane
                   (edit-workspace edit-state)))))))))) ; revise arglist order?!



;;; `Text-string?-to-insert-from-text-region' returns a fresh text-string or
;;; NIL.  It represents the parsable text of that is denoted by the text-region
;;; given.

(defun text-string?-to-insert-from-text-region (mouse-down-mouse-pointer
                                                 text-region)
  (let ((text-region-superblock (superblock? text-region)))
    (frame-class-case text-region-superblock
      (text-box
        (frame-class-case text-region-superblock
          (name-box
            (let ((name?
                    (get-primary-name-for-frame-if-any
                      (superblock? text-region-superblock))))
              (when name?        ; maybe unnec.
                (copy-symbol-name-parsably
                  name?
                  (get-slot-value
                    editor-parameters
                    'object-name-menus-in-upper-case?)))))
          (t
            (convert-text-region-to-text-string text-region))))
      (table
        (with-mouse-pointer-bindings (text-cell-of-table)
            mouse-down-mouse-pointer
          (frame-class-case text-region-superblock
            ((token-menu kfep-conversion-choice-menu)
             (text-to-insert-from-text-cell text-cell-of-table))

            (table
              ;; This only happens for the attribute names.
              (when (find-spot-of-type
                      mouse-down-mouse-pointer
                      'attribute-name-represented-by-table-spot)
                (get-attribute-table-row-alias-string
                  text-region-superblock
                  (row-index-for-text-region-cell? text-region))))))))))



(defun text-to-insert-from-text-cell (text-cell)
  ;; Return the CHOICE entry on the text-cell plist or
  ;; the text of the text-cell.
  (let ((choice?
          (getf (text-cell-plist text-cell) 'choice)))
    (if choice?
        (copy-text-string choice?)
        (convert-text-to-text-string (text? text-cell)))))




;;; `Continue-by-creating-insert-text-command' is called on exit from the
;;; selection a text-region outside the editor.  That text is then inserted into
;;; the current editor by running the command insert-text-region.

(defun continue-editing-by-doing-insert-selected-text-command
    (editing-workstation-context)
  (declare (ignore editing-workstation-context))
  (with-workstation-context-return-values (status mouse-pointer)
    (with-mouse-pointer-bindings
        ((edit-state workstation-context-specifics)
         (text-region block-of-selection-focus))
        mouse-pointer
      (in-editing-context (edit-state)
        (cond
          ((not (valid-block-in-workstation-context-p text-region edit-state))
           (deselect-current-text-region nil))
          ((or (eq :abort status)
               (empty-text-region-p text-region))
           (deselect-current-text-region text-region))
          (t
           (insert-text-within-editor-from-text-region text-region)))))))



;;; The function `simple-ascii-string-for-text-region' returns an unmanaged
;;; simple lisp string with minimal conversion from gensym character set to
;;; ASCII. This is for development use only.

#+development
(defun-allowing-unwind simple-ascii-string-for-text-region (text-region)
  (protected-let* ((text-string
                     (convert-text-region-to-text-string text-region)
                     (reclaim-text-string text-string)))
    (wide-string-to-string text-string)))

;; Warning: Non-ISO-Latin1 characters are mangled out of recognition!  This
;; is just for development.



(defun continue-editing-by-posting-cut-copy-paste-menu
    (editing-workstation-context)
  (declare (ignore editing-workstation-context))
  (with-workstation-context-return-values (status mouse-pointer)
    (with-mouse-pointer-bindings (x-in-window
                                   y-in-window
                                   (edit-state workstation-context-specifics)
                                   (text-region block-of-selection-focus))
        mouse-pointer

      (in-editing-context (edit-state)
        ;; Assuming the text-region is still alive, we will
        ;; delete it or pass ownership to the menu.  In any case
        ;; remove it from the edit state.
        (cond
          ((not (valid-block-in-workstation-context-p text-region edit-state))
           (deselect-current-text-region nil)
           )
          ((or (eq :abort status)
               (empty-text-region-p text-region))
           (deselect-current-text-region text-region))
          (t
           (cond
             ((pop-up-edit-operations-menu editor-parameters)
              (let ((menu-workspace?
                      (post-command-menu 'editor-text-marking-menu
                                         mouse-pointer
                                         x-in-window
                                         y-in-window)))
                (cond ((null menu-workspace?)
                       ;; This happens, eg, if all the choices were restricted away.
                       (deselect-current-text-region text-region))
                      (t
                       (disable-text-region-operation-subcommands-in-current-editor)
                       (with-workstation-context-continuation (return-from-edit-menu)
                         (enter-edit-menu-state menu-workspace?))))))
             (t
              (update-edit-operation-subcommands-in-current-editor)))))))))



;;; The function `return-from-edit-menu' is to be used as the workstation
;;; context continuation function for the edit-menu context. This handles the
;;; disposition of the selected text region, if any, as follows.  If returning
;;; with status (first arg) = PENDING-DELETE-TYPE-IN, this means the edit-menu
;;; context has requeued an event that will operate on the region.  In this
;;; case, the region is not deleted, but is restored to the edit state.
;;; Otherwise, the region is deleted.
;;;
;;; Note: this is a "friend" of the edit-menu context, q.v. in COMMANDS0, since
;;; it has to know about its special return values.

(defun return-from-edit-menu (workstation-context)
  (with-workstation-context-return-values (status)
    (let ((edit-state
            (specific-structure-for-workstation-context workstation-context)))
      (in-editing-context (edit-state)
        (let ((text-region? (get-selected-text-region-for-edit-box)))
          (cond
            ((eq status 'pending-delete-type-in)
             (select-current-text-region text-region?))
            (text-region?
             (deselect-current-text-region text-region?))
            (t
             ;; the following is included in (de)select-current-text-region:
             (update-edit-operation-subcommands-in-current-editor))))))))




;;; `word-like-sequence-in-text-region-p' - takes a text-region
;;; and returns t if the scrap looks like a "word".

(defun-simple word-like-sequence-in-text-region-p (text-region)
  (multiple-value-bind
      (text-tail
        beginning-line-index beginning-character-index
        end-line-index end-character-index text-cell?
        text)
      (get-text-region-position text-region)
    (declare (ignore text-cell?))
    (word-like-sequence-in-text-p
      text
      text-tail
      beginning-line-index beginning-character-index
      end-line-index end-character-index)))


;;; The function `handle-spaces-intelligently-p' determines whether the editor
;;; attempts to heuristicate whether to add spaces around a string about to be
;;; inserted. For token menu and scrap items, that preference has already been
;;; cached in the item. For text-regions, we first check editor preferences.
;;; For all other items we simply obey editor preferences.

(defun handle-spaces-intelligently-p (block)
  (frame-class-case block
    ((token-menu scrap)        ; generic slot
     (get-slot-value block 'handle-spaces-intelligently?))
    (text-region
      (and (smart-space-insertion editor-parameters)
           (word-like-sequence-in-text-region-p block)))
    (t                                        ; For example, table-item.
      (smart-space-insertion editor-parameters))))




;;; `Clear-text-region-from-edit-box' deletes the text covered by a text region
;;; from the edit box in question, and deletes the text region as well.  This
;;; must be called in an edit context.  If also-move-cursor? is supplied true,
;;; this places the cursor in between the text to right of and to the left of
;;; the cleared region.

(defun clear-text-region-from-edit-box (text-region &optional also-move-cursor?)
  (multiple-value-bind
      (text-tail beginning-line-index beginning-character-index
                 end-line-index end-character-index)
      (get-text-region-position text-region)
    (deselect-current-text-region text-region)
    (when also-move-cursor?
      (change-edit-box
        text-tail beginning-line-index beginning-character-index
        nil nil nil nil nil t))
    (delete-intelligently-from-text-being-edited
      text-tail beginning-line-index beginning-character-index
      end-line-index end-character-index)))

;; Added arg to handle cursor movement, to better support "cut". (MHD 3/16/98)

;; The delicate way the text region is deleted before the change
;; to the edit box is necessary. - ben 3/31/94





;;;; Editor Commands on Selected Text WITHIN THE EDITOR

;;; The commands in this section are seen by the user as cut, copy, and paste,
;;; and they all bear the suffix in their internal name "-within-editor" to show
;;; that they run in the editing context.  See also the subsection "Editor
;;; Commands on Selected Text".  Note: those commands share some code with
;;; these, but unfortunately they also repeat a bit of code seen in this
;;; section.  Unlike these commands, which run purely inside an editing context,
;;; those are defined to run at the return to an editing context from a menu
;;; context.


;;; The `editor-UI-command cut-within-editor' is usually/always invoked by the
;;; control+x keystroke, and therefore, for compatibility reasons, handles both
;;; the old meaning of control+x command by invoking
;;; com-delete-backward-to-beginning, and the new meaning, by executing G2's cut
;;; behavior, i.e., clearing the text in the selected region after placing a
;;; copy of that text in the various cut buffers as appropriate.  (Note: (com-)
;;; delete-backward-to-beginning is no longer bound to any key, but is only
;;; invoked indirectly by this command, com-cut-within-editor.)

;;; `Do-cut-within-editor' is its subfunction, which is called with no arguments,
;;; and may be called within an editing context to perform the cut operation. It
;;; is also called by the code that runs the cut subcommand.
;;;
;;; Optional arguments event-if-kbd-command? and edit-state-if-kbd-command? are
;;; only passed in from the keyboard command control-x in order to allow allow
;;; this to emulate the old (G2 versions through 5.0 Rev. 2) control-x command
;;; when there is no selected text region.

(define-editor-ui-command (cut-within-editor :name cut) ()
  (do-cut-within-editor event edit-state))

(defun do-cut-within-editor (&optional event-if-kbd-command? edit-state-if-kbd-command?)
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (cond
      (text-region?
       (unless (empty-text-region-p text-region?)
         (coerce-text-region-to-scrap text-region?))

       ;; this deletes the text, moves the cursor, and is responsible for
       ;; deleting text-region? if that is to be done:
       (clear-text-region-from-edit-box text-region? t))
      ((and event-if-kbd-command? edit-state-if-kbd-command?)
       ;; Backward compatibility case:
       (funcall-ui-command
         'delete-backward-to-beginning
         event-if-kbd-command? edit-state-if-kbd-command?)))))



;;; The `editor-UI-command copy-within-editor' implements the basic, standard
;;; copy semantics, i.e., placing a copy of the selected text in the various cut
;;; buffers as appropriate.

;;; If the parameter `deselect-text-region-after-copy-p' is true, however, this
;;; then goes on to delete the selected text region.  That behavior is
;;; consistent with what we've always done, i.e., with its pop-up
;;; edit-operations menu.  However, it's not totally standard, since the
;;; standard copy would not deselect the selected text.  We therefore will have
;;; to revisit and revise this later if we want to make it standard.

;;; `Do-copy-within-editor' is its subfunction, which is called with no arguments,
;;; and may be called within an editing context to perform the cut operation. It
;;; is also called by the code that runs the copy subcommand.

(define-editor-ui-command (copy-within-editor :name copy) ()
  (do-copy-within-editor))

(defparameter deselect-text-region-after-copy-p nil)

(defun do-copy-within-editor ()
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (when text-region?
      (unless (empty-text-region-p text-region?)
        (coerce-text-region-to-scrap text-region?))
      (when deselect-text-region-after-copy-p
        (deselect-current-text-region text-region?)))))


;;; The `editor-ui-command paste-within-editor' implements the basic, standard
;;; paste semantics, i.e., pasting from the appropriate scrap into the text.
;;; The scrap is taken from either the platform's cut buffer if this G2's
;;; corresponding (Tele) window supports "native cut and paste".  Otherwise, the
;;; scrap is taken from the scrapbook.  If there is a selected text region, the
;;; cursor is moved there, the text in the region is cleared, the new text is
;;; inserted at the cursor, leaving the cursor at the end of the inserted text.
;;; If there's no selected text region, the text is just inserted at the current
;;; cursor position, leaving the cursor at the end of the inserted text.

;;; `Do-paste-within-editor' is its subfunction, which is called with no arguments,
;;; and may be called within an editing context to perform the paste operation. It
;;; is also called by the code that runs the paste subcommand.

(define-editor-ui-command (paste-within-editor :name paste) (workspace image-plane mouse-pointer)
  (cond ((frame-of-class-p workspace 'edit-workspace)
         (when (text-can-be-pasted-in-current-workstation-p)
           (do-paste-within-editor)))
        (t
         (run-top-level-event-handler mouse-pointer))))


(defun do-paste-within-editor ()
  (raise-image-plane-to-top
    (find-image-plane-for-workspace-in-pane
      current-edit-workspace
      current-workstation-detail-pane))
  (cond
    ((window-supports-native-cut-and-paste current-workstation-window)
     (request-paste-for-editor))
    (t
     ;; For an older version of Telewindow (pre-5.0 Beta 1):   (MHD 3/28/97)
     (paste-from-current-scrap-if-any))))


(defun do-delete-within-editor ()
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (when text-region?
      (clear-text-region-from-edit-box text-region? t))))


(defun do-insert-within-editor ()
  (let (text-region)
    (when (setq text-region (get-selected-text-region-for-edit-box))
      (insert-text-within-editor-from-text-region text-region))))


(defun insert-text-within-editor-from-text-region (text-region)
  (let ((replace-fragments-on-sides? nil)
        (handle-spaces-intelligently?
          (handle-spaces-intelligently-p
            text-region)))
    ;; The above logic copied from coerce-text-region-to-scrap, with which
    ;; this has to be consistent.  Improve the abstraction!  Also, consider
    ;; parameterizing this behavior via an attribute of edit-parameters.
    ;; (EWL favors this approach, and would like the current behavior to
    ;; remain the default.)  (MHD 4/9/97)
    (let* ((text-string (convert-text-region-to-text-string text-region))
           (frame-reference-serial-number (copy-frame-serial-number (current-frame-serial-number))))
      ;; We can't assume that the text-region will not have been deleted upon
      ;; return from this call, so we prepare to check for deletion afterwards:
      (insert-text-string-at-cursor
        text-string
        replace-fragments-on-sides?
        handle-spaces-intelligently?)
      (unless (frame-has-been-reprocessed-p
                text-region
                frame-reference-serial-number)
        (delete-frame text-region))
      (reclaim-text-string text-string)
      (reclaim-frame-serial-number frame-reference-serial-number))))


(defun do-copy-and-insert-within-editor ()
  (let (text-region)
    (when (setq text-region (get-selected-text-region-for-edit-box))
      (coerce-text-region-to-scrap text-region)
      (delete-frame text-region)
      (do-paste-within-editor))))


(defun do-move-within-editor ()
  (let (text-region)
    (when (setq text-region (get-selected-text-region-for-edit-box))
      (let ((text-string (convert-text-region-to-text-string text-region)))
        (clear-text-region-from-edit-box text-region)
        (insert-text-string-at-cursor text-string nil nil)
        (reclaim-text-string text-string)))))


(defun do-cut-and-insert-within-editor ()
  (let (text-region)
    (when (setq text-region (get-selected-text-region-for-edit-box))
      (coerce-text-region-to-scrap text-region)
      (let ((text-string
              (convert-text-region-to-text-string text-region)))
        (clear-text-region-from-edit-box text-region)
        (insert-text-string-at-cursor text-string nil nil)
        (reclaim-text-string text-string)))))





;;;; Showing Procedure Signatures

;;; The 'signature' facility is integrated into the operations of the
;;; editor and will, by default, put up a temporary workspace showing the
;;; parameter names and types of any procedure, method, or function when
;;; the cursor is positioned within its parentheses.


;;; From the user's perspective, whether or not signatures are shown is
;;; determined by the show-procedure-signatures? attribute in Editor Parameters
;;; Internally, it is turned off whenever we are doing something like
;;; recompiling a kb where the editor workspace is kept hidden or
;;; workspace-showing-p is nil.

(defun-simple procedure-signatures-can-be-shown-p ()
  (and current-edit-state ;; should always be true, but paranoia is ok
       (show-procedure-signatures? editor-parameters)
       (not keep-edit-workspace-hidden-no-matter-what?)
       (workspace-showing-p (edit-workspace current-edit-state) t)))



;;; Policy parameter. If this is nil, signature workspaces will remain
;;; on the window until the user closes them by hand or the editing
;;; session finishes. Otherwise they are automatically closed when the
;;; user types the close paren that matches the open that launched
;;; the signature workspace.

(defparameter close-pending-procedure-signature-workspaces-on-close t)

(defconstant open-paren-token '|\(|)
(defconstant close-paren-token '|\)|)

;;; Hooks called from outside this section

;;; `Procedure-signature-hook' is checked in sync. with menu updating.
;;; See update-edit-menus-or-autocomplete-as-appropriate. This routine
;;; looks to see whether it is within open parentheses and if so it
;;; passes the (stack of) tokens just to the left of the (maximal)
;;; open paren off to be checked for whether it carries a signature.

(defun procedure-signature-hook ()
  (when (procedure-signatures-can-be-shown-p)
    (loop with accumulated-closes = 0
          for sub-stack on (stack-of-tokens current-edit-state)
          as (token token-before-that) on sub-stack
          when (eq token close-paren-token)
            do (incff accumulated-closes)
          when (eq token open-paren-token)
            do (cond ((=f accumulated-closes 0)
                      (let ((has-one-p
                              (show-signature-if-prior-token-has-one sub-stack)))
                        (if has-one-p
                            (remove-any-other-visible-signatures (second sub-stack))
                            (runtime-reclaim-pending-procedure-signature-workspaces)))
                      (return))
                     (t (decff accumulated-closes)))
          finally
            (runtime-reclaim-pending-procedure-signature-workspaces))))


;;; `Procedure-signature-token-hook' is called on every token from inside
;;; extend-parsing-as-appropriate. It is just looking for close parens.
;;; If the current token is a close then we take down the workspace for
;;; the corresponding procedure.

(defun-void procedure-signature-token-hook (token)
  (when (and (eq token close-paren-token)
             (procedure-signatures-can-be-shown-p))
    (close-signature-window-if-appropriate)))





;;; Checking the token before the open parenthesis

;;; `Show-signature-of-call-if-prior-token-has-one' gets a cdr of the stack of
;;; accumulated tokens as its argument. The first element of that stack is the
;;; open that has been determined to be the one that encloses the location of
;;; the cursor at the time of this call. If there is symbol just to the left
;;; of that open (second on the stack) that names something that we can show
;;; signatures of, then we do that, and we return t; otherwise, nothing is done,
;;; and nil is returned.

(defun show-signature-if-prior-token-has-one (stack)
  (let ((token-before-open (second stack))
         (call-p (eq 'call (third stack))))
    (when (symbolp token-before-open)
      (multiple-value-bind (list-or-list-of-lists type)
             (parameters-for-token-if-any token-before-open call-p)
        (when list-or-list-of-lists
          ;; If there are no strings then the token has no definition.
          ;; We could consider throwing up a workspace saying that.
          (create-or-revive-workspace-for-procedure-signature
            token-before-open type list-or-list-of-lists)
          (reclaim-gensym-tree list-or-list-of-lists)
          t)))))



;;; Setting up the workspace to display the signature. First we look to see
;;; if the workspace for this token is already up. If not we have one constructed
;;; and then we show it.

(defun create-or-revive-workspace-for-procedure-signature (token type
                                                                 list-or-list-of-lists)
  (let ((entry (assq token (pending-procedure-signature-workspaces
                             current-edit-state))))
    (if entry
        (let* ((workspace (second entry))
               (workspace-serial-number (third entry)))
          (if (not (frame-has-been-reprocessed-p
                     workspace workspace-serial-number))
              t  ;; placeholder -- here we would make sure it was on top
              (progn
                (remove-record-of-procedure-signature-workspace token)
                (create-or-revive-workspace-for-procedure-signature
                  token type list-or-list-of-lists))))
        (let ((workspace?
                (construct-workspace-for-signature token type list-or-list-of-lists)))
          (when workspace?
            ;; show it
            ;; TODO: Maybe check whether just the editor on current-workstation-window
            ;; is native?
            (unless (native-editor-workspace-p (edit-workspace current-edit-state))
              (put-workspace-on-pane
                workspace? current-workstation-detail-pane
                'right 'top t)
              (record-procedure-signature-workspace token workspace?)))))))



(defun construct-workspace-for-signature (token type
                                          list-or-list-of-lists)
 (let ((workspace (make-workspace
                    'temporary-workspace ;; class
                    nil ;; name
                    nil ;; initial-subblock
                    10  ;; non-default-margin
                    250 ;; minimum-initial-width
                    nil ;; minimum-initial-height
                    )))

   (let ((initial-delta-y
           (add-title-of-signature-to-signature-workspace
             token type workspace)))

     (loop with current-y = initial-delta-y
           for first-p = t then nil
           for arg-list in list-or-list-of-lists
           do
       (setq current-y
             (add-signature-to-workspace
               token arg-list workspace current-y)))
     workspace)))

;; To do: Fold the common elements of the next four routines into the
;; driving loop? Or would that make it unreasonably messy for maintainance?
;; Common subroutine with the string construction as its varying element
;; would probably be best.

(defun add-signature-to-workspace (token arg-list workspace current-y)
  (let* ((signature-string
           (twith-output-to-text-string
             (twrite-signature token arg-list)))
         (block (make-box-for-signatures signature-string)))

    (add-to-workspace block workspace (+w (left-edge-of-block workspace)
                                          (workspace-margin workspace)) current-y)
    (+w current-y (+w (height-of-block block) 10))))


(defun make-box-for-signatures (string)
   (let ((box (make-message string)))
     (set-do-not-save-in-kb box)
     box))

(defun twrite-signature (token arg-list)
  (let ((return-types? (cdr (memq ':return arg-list))))
    (tformat "~(~a~) (" token)
    (twrite-parameter-list arg-list)
    (twrite ")")
    (when return-types?
      (twrite " => (")
      (twrite-return-types return-types?)
      (twrite ")"))))

(defun twrite-parameter-list (arg-list)
  (loop with name = nil
        with type = nil
        for first-p = t then nil
        for cons-or-symbol in arg-list do
    (when (eq cons-or-symbol ':return)
      (return))
    (if (consp cons-or-symbol)
        (setq name (car cons-or-symbol)
              type (cdr cons-or-symbol))
        (setq name cons-or-symbol))
    (unless first-p
      (twrite-string ", "))
    (twrite-symbol name)
    (when type
      (twrite-string ": ")
      (twrite-parameter-list-type-field type))))

(defun twrite-return-types (types)
  (loop for first-p = t then nil
        for type in types do
    (unless first-p
      (twrite-string ", "))
    (twrite-parameter-list-type-field type)))

(defun twrite-parameter-list-type-field (type)
  (cond ((consp type)
         (twrite-string "class ")
         (twrite-symbol (second type)))
        (t (twrite-data-type type))))


(defun add-parameter-string-to-workspace (string workspace current-y)
  (let ((block (make-description-box string)))
    (add-to-workspace block
                      workspace
                      (+w (left-edge-of-block workspace)
                          (workspace-margin workspace))
                      current-y)
    (+w current-y (+w (height-of-block block) 10))))
;; n.b. this general function is a leftover from an earlier implementation when
;; it did the bulk of the work. Keep it or specialize this functionality?

;(defun add-separator-string-to-workspace (workspace current-y)
;  (let ((block (make-description-box (copy-wide-string #w"-------------"))))
;    (add-to-workspace block workspace 0 current-y)
;    (+w current-y (+w (height-of-block block) 15))))
#+unused
(defun add-separator-string-to-workspace (workspace current-y)
  (let ((block (make-description-box (copy-wide-string #w""))))
    (add-to-workspace block workspace (+w (left-edge-of-block workspace)
                          (workspace-margin workspace)) current-y)
    (+w current-y (+w (height-of-block block) 15))))


(defun add-title-of-signature-to-signature-workspace
    (token type-or-types workspace)
  (declare (ignore token))
  (let ((title-text
          (twith-output-to-text
            (tformat "~(~L,-~) arguments" type-or-types))))
    (unless (symbolp type-or-types)
      (reclaim-gensym-list type-or-types))
    (cond
      (new-g2-classic-ui-p
       (setf (title-bar-caption-text workspace) title-text)
       (setf (stretch-new-image-planes-for-caption-p workspace) t)
       0)
      (t
       (let* ((block (make-description-box-with-text title-text)))
         (add-to-workspace
           block workspace
           (+w (left-edge-of-block workspace)
               (workspace-margin workspace))
           0)
         (+w (height-of-block block)
             15))))))  ; extra space below title





;;; Looking up the parameters:

;;; At this level we are not committed to how the signature is going to
;;; be presented so we just return a list of symbols or conses depending
;;; on what kind of item the token names. The arguments to procedures and
;;; methods are typed, so for them we make fresh conses of the symbol
;;; naming the parameter and the symbol naming its type. For functions we
;;; have only the symbol that names the type.

;;; `Parameters-for-token-if-any' and `parameters-for-token-if-any1' return
;;; two values, the list of conses and a symbol indicating what kind of
;;; routine this is: procedure, method, or function.

;;; Call-p is true if the token 'call' preceded the token in the text.

(defun parameters-for-token-if-any (token call-p)
  (let ((object (frame-or-frames-with-this-name-macro token)))
    (cond #+unused                        ; Show LISP function arguments in development.
          ((and call-p
                (null object)
                (symbolp token)
                (fboundp token)
                (memq token system-call-function-list))
           (values (gensym-list (copy-tree-using-gensym-conses (fn-arglist token)))
                   'lisp-sysproc))
          ((null object)
           (unless call-p
             (values (assemble-parameters-for-built-in-function token) 'function)))
          ((atom object)
           (parameters-for-token-if-any1 object token))
          (t
           (loop with all-signatures = nil
                 with all-the-same-type = nil
                 with types-seen = nil
                 for o in object
                 do (multiple-value-bind (signature type)
                        (parameters-for-token-if-any1 o token)
                      (setq all-signatures
                            (nconc all-signatures signature))
                      (unless (or (null type) ; for non-applicable things
                                  (memq type types-seen))
                        (setq types-seen
                              (nconc types-seen (gensym-list type)))))
                 finally
                   (when (and types-seen (null (cdr types-seen)))
                     (setq all-the-same-type (first types-seen))
                     (reclaim-gensym-list types-seen))
                   (return (values all-signatures
                                   (or all-the-same-type
                                       types-seen))))))))


(defun parameters-for-token-if-any1 (object token)
  (frame-class-case object
    (method-declaration
      (values (assemble-parameters-for-method token) 'method))
    (procedure
      (values (assemble-parameters-for-procedure object) 'procedure))
    (remote-procedure-declaration
      (values (assemble-parameters-for-remote-procedure-declaration object) 'procedure))
    (function-definition
      (values (assemble-parameters-for-function object) 'function))
    (tabular-function-of-1-arg
      (values (assemble-parameters-for-tabular-function-of-1-arg object)
              'function))
    (foreign-function-declaration
      (values (assemble-parameters-for-foreign-function-declaration object) 'function))))

;; How about a method?! (MHD)



;;; The core routines for looking up the parameters and their types.  Methods
;;; are done as multiple calls to `assemble-parameters-for-procedure',
;;; Built-in functions are done essentially by table lookup since they
;;; don't support the explicit data structure that would let us do something
;;; akin to what we do with procedures. This also means we can't post their
;;; return values without extending that data. User function are done by
;;; looking into their code.

(defun assemble-parameters-for-procedure (procedure)
  (unless (invisible-proprietary-procedure procedure)
    (let ((parameter-data?
            (loop with parameters? = (argument-list-description-function
                                       procedure)
                  for i from 0 below
                  (if parameters? (managed-array-length parameters?) 0)
                        by 2
                  as name = (managed-svref parameters? i)
                  as type = (decode-procedure-type-field
                              (managed-svref parameters? (1+f i)))
                  collect (gensym-cons name type) using gensym-cons))
          (return-data?
            (when (returned-values-description-function procedure)
              (loop with data = (returned-values-description-function procedure)
                    for i from 0 below (managed-array-length data) by 2
                    as type = (decode-procedure-type-field
                                (managed-svref data (1+f i)))
                    collect type using gensym-cons))))
      (gensym-list
        ;; decoded in add-signature-to-workspace
        (cond ((and parameter-data? return-data?)
               (nconc parameter-data? (gensym-cons ':return return-data?)))
              (return-data?
               (gensym-cons ':return return-data?))
              (parameter-data?
               parameter-data?)
              (t nil))))))


(defun decode-procedure-type-field (type-field)
  (let* ((type (if (and (consp type-field)
                        (eq (car type-field)
                            ':general-description))
                   (getfq (cdr type-field) :type)
                   type-field))
         (pruned-type
           (when type
             (cond ((consp type)
                    (cond ((eq (car type) 'class)
                           (copy-list-using-gensym-conses type))
                          ((eq (car type) 'sequence) :sequence) ;; see note
                          ((eq (car type) 'structure) :structure)))
                   ((eq type 'item-or-datum)
                    'item-or-value)
                   (t type)))))
    pruned-type))

;; Note: We return keywords for these type names because otherwise the
;; conses will be taken to be evaluation-values and later copy operations
;; will blow out.

;; See ";;;; Procedure Code Bodies" section in PROC-UTILS for further details
;; on the format of :general-description types.




(defun assemble-parameters-for-method (method-name)
  (loop for method being each class-instance of 'method
        when (eq method-name (procedure-method-name-function method))
          nconc (assemble-parameters-for-procedure method)))

(defun assemble-parameters-for-function (function)
  (gensym-list
    (copy-list-using-gensym-conses
      (second (car (box-translation-and-text function))))))

(defun assemble-parameters-for-built-in-function (name)
  (let ((names-or-list-of-names (get-built-in-function-argument-names name)))
    (if (listp (car names-or-list-of-names))
        (loop for name-list in names-or-list-of-names
              for firstp = t then nil
              collect (loop for name in name-list
                            collect name
                              using gensym-cons)
                using gensym-cons)
        (gensym-list
          (loop for name in names-or-list-of-names
                collect name
                  using gensym-cons)))))

(defun assemble-parameters-for-tabular-function-of-1-arg (function)
  (declare (ignore function))
  (gensym-list (gensym-list 'x)))        ; use X as canonical arg name


(defun assemble-parameters-for-remote-procedure-declaration (rpd)
  (let* ((translation? (car (box-translation-and-text rpd)))
         (description?
           (get-slot-value rpd 'remote-procedure-argument-description)))
    (cond
      ((and translation? (second translation?) description?)
       (gensym-list
         (nconc
           (make-parameters-from-rpd-arg-description description?)
           ;; Has return types, but they're rather complex; defer for now;
           ;; later, handle the return types properly! -mhd, 1/8/01
           ))))))


;;; Make-parameters-from-rpd-arg-description is a subfunction of
;;; assemble-parameters-for-remote-procedure-declaration.  It returns a list of
;;; parameters (freshly consed using gensym conses).

(defun make-parameters-from-rpd-arg-description (description)
  (loop for i from 1 below (managed-array-length description) by 2
        as j from 0
        as type-description = (managed-svref description i)
        as plist
           = (if (and (consp type-description)
                      (eq (car type-description) ':general-description))
                 (cdr type-description))
        as user-type
           = (decode-procedure-type-field type-description)
        as arglist-element
           = (gensym-cons
               (intern-text-string
                 (tformat-text-string
                   (if (getf plist :all-remaining)
                       "ARG-~d-AND-ALL-REMAINING"
                       "ARG-~d")
                   j))
               user-type)
        collect arglist-element using gensym-cons))

;; To understand the above, refer to
;; convert-remote-procedure-description-to-structure, as well as the grammar and
;; compiler for remote-procedure-declaration.  It also helps to look at
;; collect-types-into-list-using-gensym-conses; its functionality overlaps this
;; somewhat.  See also decode-procedure-type-field (above) and the ";;;;
;; Procedure Code Bodies" section of PROC-UTILS. (MHD 4/16/01)




(defun assemble-parameters-for-foreign-function-declaration (ffd)
  (let ((translation (car (box-translation-and-text ffd))))
    (gensym-list
      (nconc
        (copy-list-using-gensym-conses (sixth translation))
        (gensym-list ':return (third translation))))))



;;; hook in case we want to omit these

(defvar disable-parameter-strings-for-internal-proprietary-procedures nil)

(defun invisible-proprietary-procedure (procedure)
  (and disable-parameter-strings-for-internal-proprietary-procedures
       (proprietary-p procedure)
       (let ((name-string
               (stringw (get-primary-name-for-frame-if-any procedure))))
         (and (<f 0 (lengthw name-string))
              (char=w #.%_ (charw name-string 0))))))





;;; `Close-signature-window-if-appropriate' is called whenever a closing
;;; parenthesis is seen in the course of a parse. Its job is to determine
;;; whether this close goes with the matching open that caused the
;;; procedure.

(defun close-signature-window-if-appropriate ()
  (when close-pending-procedure-signature-workspaces-on-close
    (let ((pending-procedure-signature-workspaces
            (pending-procedure-signature-workspaces current-edit-state)))
      (when pending-procedure-signature-workspaces
        (loop with accumulated-closes = 0
              for (token token-before-that) on (stack-of-tokens current-edit-state)
              when (eq token close-paren-token)
                do (incff accumulated-closes)
              when (eq token open-paren-token)
                do (if (=f accumulated-closes 0)
                       (let ((entry?
                               (assq token-before-that ;; possibly procedure name
                                     pending-procedure-signature-workspaces)))
                         (when entry?
                           (remove-record-of-procedure-signature-workspace
                             token-before-that))
                         (return))
                       (decff accumulated-closes)))))))

(defun remove-any-other-visible-signatures (relevant-token)
  (let ((table (pending-procedure-signature-workspaces current-edit-state)))
    (when (cdr table) ; more than one entry
      (let ((other-entry-tokens
              (loop for (token . rest) in table
                    when (not (eq token relevant-token))
                      collect token using gensym-cons)))
        (loop for token in other-entry-tokens
              do (remove-record-of-procedure-signature-workspace token))
        (reclaim-gensym-list other-entry-tokens)))))



;;; Managing the temporary workspaces that we're creating.

(defun-simple make-procedure-signature-workspace-entry (token workspace)
  (gensym-list token
               workspace
               (copy-frame-serial-number
                 (frame-serial-number workspace))))

(defun-void reclaim-procedure-signature-workspace-entry (entry)
  (unless (frame-has-been-reprocessed-p (second entry) (third entry))
    (delete-frame (second entry)))
  (reclaim-frame-serial-number (third entry))
  (reclaim-gensym-list entry))

(defun record-procedure-signature-workspace (token workspace)
  (gensym-push (make-procedure-signature-workspace-entry token workspace)
               (pending-procedure-signature-workspaces current-edit-state)))

(defun remove-record-of-procedure-signature-workspace (token)
  (let* ((pending-procedure-signature-workspaces
           (pending-procedure-signature-workspaces current-edit-state))
         (entry (assq token pending-procedure-signature-workspaces)))
    (when entry
      (setf (pending-procedure-signature-workspaces current-edit-state)
            (delete-gensym-element entry pending-procedure-signature-workspaces))
      (reclaim-procedure-signature-workspace-entry entry))))

(defun reclaim-pending-procedure-signature-workspaces
       (pending-procedure-signature-workspaces)
  (loop for entry in pending-procedure-signature-workspaces
        do (reclaim-procedure-signature-workspace-entry entry))
  (reclaim-gensym-list pending-procedure-signature-workspaces))


;;; Runtime-reclaim-pending-procedure-signature-workspaces reclaims all pending
;;; signature workspaces, and resets the slot
;;; pending-procedure-signature-workspaces of current-edit-state to nil.

(defun runtime-reclaim-pending-procedure-signature-workspaces ()
  (when (pending-procedure-signature-workspaces current-edit-state)
    (reclaim-pending-procedure-signature-workspaces
      (pending-procedure-signature-workspaces current-edit-state))
    (setf (pending-procedure-signature-workspaces current-edit-state) nil)))














;;;; Searching in the Editor



;;; `Search-for-text-in-editor' If we are in a normal
;;; editor, this means to enter the searching subcontext.
;;; If we are in a searching subcontext, this means to
;;; search for the next instance of the search text already
;;; typed in. This always searches forward.

(define-editor-ui-command search-for-text-in-editor ()
  (cond
    ((not (edit-state-for-search-p current-edit-state)) ; => in normal editor
     (create-search-workspace 'search-forward-incrementally-for-text-in-editor))
    (t        ; already searching; find next (forward search)
     (setf (function-to-call-on-changed-edit-box-text? current-edit-state)
           'search-forward-incrementally-for-text-in-editor)
     (find-next-instance-of-search-string))))




;;; `create-search-workspace' creates a new tiny edit
;;; workspace with a label and an area to type the search
;;; string. This workspace is not made to "ride" on the
;;; superior edit workspace; this allows it to be moved
;;; around, e.g., in case it's covering up text the user
;;; wants to see.

(defun create-search-workspace (search-function)
  (setf (line-index-of-search-anchor? current-edit-state) nil)
  (setf (character-index-of-search-anchor? current-edit-state) nil)
  (multiple-value-bind (left top right bottom)
      (compute-edit-search-box-location current-edit-state)
    (with-workstation-context-continuation (return-from-search-in-editor)
      (enter-editing-context
        nil nil nil nil nil nil nil nil
        (find-image-plane-for-workspace-in-pane
          current-edit-workspace current-workstation-detail-pane)
        (edit-box current-edit-state)
        left top right bottom
        nil
        'search-for-text-in-editor
        ;; Later, react to every change in the text for incremental
        ;; search. (MHD/DDM 10/9/96)
        search-function
        t)
      (in-editing-context (specific-structure-for-current-workstation-context)
        ;; defeat the image plane coupling behavior, now that we got the
        ;; scaling and positioning we wanted:
        (let ((ip (specific-image-plane-on-which-to-edit-in-place?
                    current-edit-state)))
          (setf (superplane? ip) nil)
          (setf (superplane-coupling? ip) nil))
        ;; add some text explaining what this odd box is, while leaving room
        ;; for the mouse to grab the box to move it:
        (let ((caption-text-box
                (make-free-text-box
                  (tformat-text-string "Search: ")
                  nil
                  'small-borderless-free-text-format)))
          (add-to-workspace
            caption-text-box
            (edit-workspace current-edit-state)
            (-w (left-edge-of-block (edit-box current-edit-state)) 4)
            (-w (top-edge-of-block (edit-box current-edit-state))
                (height-of-block caption-text-box))
            t))))))



;;; `compute-edit-search-box-location'
;;; The edit-box for the search is positioned relative to
;;; the edit workspace, just below the text edit area in
;;; order not to obscure any text being searched.

;;; The workspace for the editor search is the same size as the edit's
;;; cursor, which is huge considering how small a widget it is on the
;;; screen (8 wide by 12 tall -- 8 "x" characters by three+ lines).

(defparameter relative-horizontal-displacement-for-search-workspace 10)
(defparameter relative-vertical-displacement-for-search-workspace 34)


(defun compute-edit-search-box-location (current-edit-state)
  (let* ((edit-box (edit-box current-edit-state))
         (editor-bottom (bottom-edge-of-block edit-box))
         (editor-left-edge (left-edge-of-block edit-box))
         (left (+w editor-left-edge
                   relative-horizontal-displacement-for-search-workspace))
         (top (+w editor-bottom
                  relative-vertical-displacement-for-search-workspace))
         (right left)
         (bottom top))
    (values left top right bottom)))




;;; `Edit-state-for-search-p' is true if edit-state is for the special-purpose
;;; editor used for doing search; otherwise, this returns false (nil).

(defun edit-state-for-search-p (edit-state)
  (eq (special-entry-context? edit-state)
      'search-for-text-in-editor))



;;; `Find-forward-instance-of-search-string' only does anything
;;; if the current edit state is for the special-purpose editor
;;; used for doing search.  If that is so, this sets up state
;;; information indicating the direction of the search, and proceeds
;;; to search in that direction for the next instance of the current
;;; search string.

(define-editor-ui-command  find-forward-instance-of-search-string ()
  (when (edit-state-for-search-p current-edit-state)
    (setf (function-to-call-on-changed-edit-box-text? current-edit-state)
          'search-forward-incrementally-for-text-in-editor)
    (find-next-instance-of-search-string)))




;;; `find-backward-instance-of-search-string' is the
;;; search-backward equivalent of
;;; search-for-text-in-editor. If we are in a normal
;;; editor, this means to enter the searching subcontext.
;;; If we are in a searching subcontext, this means to
;;; search for the next instance of the search text already
;;; typed in. This always searches forward.

(define-editor-ui-command  find-backward-instance-of-search-string ()
  (cond
    ((not (edit-state-for-search-p current-edit-state)) ; in normal editor
     (create-search-workspace 'search-backward-incrementally-for-text-in-editor))
    (t        ; already searching; find next (backward search)
     (setf (function-to-call-on-changed-edit-box-text? current-edit-state)
           'search-backward-incrementally-for-text-in-editor)
     (find-next-instance-of-search-string))))

;; By setting the function-to-call-... slot to a particular value, we are
;; establishing the state information by which any characters that are added to
;; the search string after we're done will extend/reiterate the search in the
;; correct (forward) direction.





(defun return-from-search-in-editor (workstation-context)
  (with-workstation-context-return-values (region-or-abort-flag?)
    (let ((edit-state (specific-structure-for-workstation-context
                        workstation-context)))
      (in-editing-context (edit-state)
        (cond
          ((eq region-or-abort-flag? :abort)
           (delete-any-text-regions
             (edit-box edit-state)
             nil nil nil nil
             (kfep-conversion-text-region? edit-state)))
          (region-or-abort-flag?        ; non-nil/non-abort => it's a region
           ;; we go to the place we found, i.e., the cursor position at the
           ;; free end of the found region:
           (let* ((region region-or-abort-flag?)
                  (line-index (line-index-for-free-end-of-text-region region))
                  (character-index (character-index-for-free-end-of-text-region region)))
             (delete-frame region)
             (change-edit-box nil line-index character-index)))
          (t
           #+development
           (assert (loop for s being each subblock of (edit-box edit-state)
                         always (or (not (frame-of-class-p s 'text-region))
                                    (eq s
                                        (kfep-conversion-text-region?
                                          edit-state)))))))))))





;;;; Keymaps for the Editor Commands (The New Way)



(define-keymap editor-commands (:pretty-name "Editor Commands")
  (right-arrow go-forward-character)
  (left-arrow go-backward-character)
  (up-arrow go-up-line)
  (down-arrow go-down-line)
  ((or <delete-forward-keys> control+g) delete-forward-character)
  (<delete-backward-keys> delete-backward-character)
  (alt+f go-forward-word)
  (alt+b go-backward-word)
  (alt+d delete-forward-word)
  ((or control+w alt+delete) delete-backward-word)


  ;; New for 5.0 Rev. 3: part of pending-delete reforms, and making the editor
  ;; feel a bit more like Windows, Motif, Mac, et al) (MHD 5/13/97)
  (control+x cut-within-editor)
  (control+c copy-within-editor)
  (control+v paste-within-editor)


  (end go-to-end-of-line)                ; inspired by MSWin Guidelines,
  (home go-to-beginning-of-line)        ;   we'll use home/end and ctrl+home/end
  (page-down go-down-page)                ; like clicking above/below elevator
  (page-up go-up-page)                        ;   of scrollbar, BUT move cursor, too.
  (control+end go-to-end)                ;   for beg/end of line and text, resp.
  (control+home go-to-beginning)
  (control+left-arrow go-backward-word)        ; MSWin std. for forward/backward word
  (control+right-arrow go-forward-word)        ; (duplicate of alt+f, alt+b)

  (control+> go-to-end-of-line)                ; alt+>/alt+< were grandfathered in;
  (control+< go-to-beginning-of-line)        ;   regard these as "classic" bindings;
  (alt+> go-to-end)                        ;   a fairly natural extension to get
  (alt+< go-to-beginning)                ;   the line variants is control+>/control+<

  (alt+u undo)
  (alt+r redo)

  ;; Control+x is now cut, and the old functionality is now handled by the cut
  ;; command.
  ; (control+x delete-backward-to-beginning) ; Was clear-input.

  (control+return end-editing)
  (<standard-enter-keys> do-return-key-function)
  (<standard-newline-keys> insert-newline-complex-character)
  (alt+return maybe-insert-newline)


  (alt+i insert-accented-or-special-or-coded-character)                        ; replaces obsolete 3.0 \ and ~ commands (MHD/PGA 4/2/95)

  (alt+s search-for-text-in-editor) ; start of a new text search facility
  (alt+p find-backward-instance-of-search-string)
  (alt+n find-forward-instance-of-search-string)

  (tab do-tab-function)
  ;; want to have a control+tab that always goes to the next field, even when
  ;; tab is bound to insert-n-spaces, for field edit.  Maybe field edit must be
  ;; a separate workstation context until we have dynamic bindings -- yuck -- or
  ;; maybe have to have it privately bound -- yuck -- or maybe live without it
  ;; for now?!  (MHD 8/15/94)

  #+not-ready-for-prime-time                ; Reconsider later! (MHD 8/15/94)
  (control+tab select-next-editor-component-group)
  #+not-ready-for-prime-time
  (control+shift+tab select-previous-editor-component-group)

  (control+space insert-first-token-menu-choice)
  (control+shift+space insert-last-token-menu-choice)

  ;; Sun Function keys, labelled again, undo, copy, paste, and cut, resp.  Just
  ;; for developers* until we figure out just how to make this portable.
  ;; (*Developers use Sparcstations) (MHD 3/18/98)
  #+development (f12 redo)
  #+development (f14 undo)
  #+development (f16 copy-within-editor)
  #+development (f18 paste-within-editor)
  #+development (f20 cut-within-editor)

  (escape abort-editing)                ; lgibson 7/10/98
  (<standard-abort-keys> abort-editing)        ; might be able to require
                                        ;   confirmation some day
  (mouse-wheel-forward scroll-line-up)
  (mouse-wheel-backward scroll-line-down))

(define-event-handler scroll-line-down (text-box image-plane)
  (when (find-frame-transform-if-any text-box image-plane)
    (funcall-method 'scroll-block text-box image-plane 'line 'down)))

(define-event-handler scroll-line-up (text-box image-plane)
  (when (find-frame-transform-if-any text-box image-plane)
    (funcall-method 'scroll-block text-box image-plane 'line 'up)))


(define-keymap motif-text-editor-commands
    (:pretty-name "Motif Text Editor Commands")
  ;; text navigation commands
  (control+left-arrow go-backward-word)
  (control+right-arrow go-forward-word)
  ;; (control+up-arrow go-up-paragraph)      ; "KPrevPara ... an optional function"
  ;; (control+down-arrow go-down-paragraph)  ; "KNextPara ... an optional function"


  ;; (control+remove erase-to-end-of-line) ; "KEraseEndLine ... optional";
  ;; what's "remove"?

  (shift+delete cut)                        ; Note 1, Note 2
  (control+insert copy)                        ; Note 3
  (shift+insert paste)                        ; Note 4
  (alt+backspace undo))                        ; Note 5

;; Note 1: this corresponds to the Motif <delete> key.
;;
;; Note 2: the DEC LK401 equivalent is supposed to be "Remove" -- what's
;; remove?!
;;
;; Note 3: the DEC LK401 equivalent is supposed to be "Shift+Remove"
;;
;; Note 4: the DEC LK401 equivalent is supposed to be "Insert Here"
;;
;; Note 5: Note that Motif lacks guidelines for infinite undo!  What to do?!
;;
;; Note: Motif defined KPrimaryCopy, which "copies the selection to the cursor".
;; This is most like our G2-classic "insert".  Motif also has KPrimaryCut, which
;; is like our "cut and insert"
;;
;; Motif also has KRestore, which "restores text to the value prior to editing".
;; We don't have anyghint like that.  Note that we do have infinite undo, which
;; makes up for the lack a bit.





(define-keymap mswindows-text-editor-commands
    (:pretty-name "MSWindows Text Editor Commands")
  ;; text navigation commands
  (down-arrow go-down-line)
  (up-arrow go-up-line)
  (end go-to-end-of-line)
  (home go-to-beginning-of-line)
  (page-down go-down-page)
  (page-up go-up-page)
  (control+right-arrow go-forward-word)
  (control+left-arrow go-backward-word)
  (control+end go-to-end)
  (control+home go-to-beginning)

  ;; edit commands:
  (control+x cut)                        ; Note 1
  (control+c copy)
  (control+v paste)
  (control+z undo)                        ; Note 2
  (control+y redo))

;; Note 1: If "allow secondary selection" is permitted, then the selected text
;; might be the secondary selection.  We have standard interpretations for cut,
;; copy, and paste on the secondary selection when it's within the same edit
;; box: we just move the cursor there, and do the standard cut, copy, and paste.
;; However, we do not obey "pending delete" conventions -- typing deletes the
;; selected text.
;;
;; This is rather different than a standard MSWindows editor, true, but what can
;; you do?  (You can disable secondary selection to get a "more true" MSWindows
;; feel.)  When secondary selection is not allowed, there's less of a problem,
;; and we seem to better obey "pending delete" conventions.

;; Note 2: MSWindows doesn't exactly have an undo/redo concept.  Instead, they
;; have an Undo/Repeat concept.  Along with that, they have a concept of
;; "typing", which includes all simple character inserts and rubouts.  For
;; example, if you enter the following keystrokes
;;
;;     This is some text<del><del><del><del>junk.
;;
;; giving you the text
;;
;;     This is some text.
;;
;; and then hit Ctrl+Y ("Repeat Typing"), it will insert this exact same text
;; right after the period.  And subsequent Ctrl+Y's will insert that same text
;; again following the previous inserts.





;; Not currently installed. (MHD 5/10/94)


(define-keymap private-editor-commands
    (:private t)

  ;; Kanji Mode Keys
  ;;
  ;; Some of these, Space, for example, implement a straight editing command
  ;; (that doesn't want to be advertised) unless in Kanji mode, in which case it
  ;; implements a Kanji command.
  ;;
  ;; Some commands, Up-arrow, for example, are advertised (i.e., are in the
  ;; public editing keymap) as implementing straight editing commands, but
  ;; implement something special for Kanji.  These include end-editing (enter),
  ;; delete-backward-character (rubout), go-backward-character (left-arrow),
  ;; go-forward-character (right-arrow), go-up-line (up-arrow), and go-down-line
  ;; (down-arrow).
  ;;
  ;; Some of these, alt+k, for example, implement Kanji and Hangul commands
  ;; only.
  ;;
  ;; Some, control+', for example, implement Kanji only commands.
  ;;
  ;; There is no provision for advertising the Kanji editing commands at all
  ;; right now, which is somewhat sad.  (MHD 5/4/94)

  (space space-or-convert/next)
  (alt+k enter-kanji-mode)
  (control+k cycle-to-next-kana)        ; kana is J. for language
  (control+\' skip-kfep-conversion)        ; consider also control-down-arrow,
                                        ;   esp. if there's a chance we'll
                                        ;   have an up-arrow command that
                                        ;   moves the fixed end backward.
  (control+left-arrow shrink-kfep-conversion-text-region)
  (control+right-arrow expand-kfep-conversion-text-region)


  ;; Mouse Down and Mouse Up
  ((<mouse-down> stepper-of-scroll-bar-spot)
   enter-hot-spot-state-upon-frame-component)
  ((<mouse-down> elevator-of-scroll-bar-spot) enter-elevator-state)

;  ((<mouse-right-down> text-region-spot)
;   pop-up-edit-operations-menu-for-text-region)

  (<mouse-down> handle-mouse-down-event-in-edit-context)

  ;; It is important to bind to any mouse-up, else you can get into strange
  ;; states with sequences like: mouse-down, drag, depress-shift-key, mouse-up.
  (<mouse-up> mouse-up-in-editing-context)

  ((<mouse-select> token-menu-button-spot) auto-insert-text-in-editor)

  (paste-request paste-into-editor) ; new in 6.0
  (paste-availability-request update-paste-status) ; new in 6.0

  ;; All unmodified keystrokes (the following only expects keystrokes; it does
  ;; NOT handle mouse events)
  (<printing-character> editor-catch-all))


;;; The keymap `native-editor-commands' makes the editing context appear
;;; non-modal.  All keyboard events are sent to top-level, and only mouse
;;; gestures are allowed through to the classic handler.

(define-keymap native-editor-commands (:private t :condition native-editor-commands-p)
  (<any-keyboard-event> run-top-level-event-handler))

(defun native-editor-commands-p ()
  (and (boundp 'current-workstation-context)
       current-workstation-context
       (let ((state (specific-structure-for-workstation-context current-workstation-context)))
         (and (edit-state-p state)
              (edit-workspace state)
              (native-editor-workspace-p (edit-workspace state))))))


;;; `paste-into-editor' pastes text into the current
;;; editor.  The event detail is a list. The first element
;;; is the paste request ID fixnum and the second is text
;;; string to be pasted.

(define-editor-ui-command paste-into-editor ()
  "pastes text into the current editor"
  (let ((event-detail? (workstation-event-detail event)))
    (when event-detail?
      (let ((request-id (car event-detail?))
            (text-string (cadr event-detail?)))
        (when (eql request-id
                   (current-paste-request-id? specific-structure-for-current-workstation-context))
          (setf (current-paste-request-id? current-edit-state) nil)
          (cond
            ((text-string-matches-current-scrap-p text-string)
             (paste-from-current-scrap-if-any))
            (t
             (paste-text-string text-string))))))))





(define-editor-ui-command update-paste-status ()
  "makes the editor aware of the availability of text to paste"
  (when (edit-subcommand-menu? current-edit-state)
    (enable-or-disable-subcommand
      (edit-subcommand-menu? current-edit-state)
      'paste
      (not (text-can-be-pasted-in-current-workstation-p)))))



;(define-editor-ui-command pop-up-edit-operations-menu-for-text-region ()
;  (print 'hello-world))


;;; move to TABLES!
;(def-spot text-region-spot
;    :abstract-type nil
;    :type-of-frame-represented text-box)

;(def-class-method generate-spot (text-region mouse-pointer)
;  (princ ".")
;  (push-last-spot mouse-pointer (make-text-region-spot) text-region))





(define-event-handler auto-insert-text-in-editor ((text-cell text-cell-of-table)
                                                  (frame frame)) ; The token-menu
  (let ((text-string?
          (text-to-insert-from-text-cell text-cell)))
    (when text-string?
      (auto-insert-text-from-block text-string? frame))))




;;;; Miscellaneous Handling of Editing Events


;;; `Handle-character-in-text-event' handles an event corresponding to any
;;; Unicode character.  (Note that the set of Unicode characters is a superset
;;; of the sets of simple gensym characters, ascii characters, and ISO Latin-1
;;; characters.)

(defun handle-character-in-text-event (event)
  (let ((unicode? (convert-key-code-to-unicode (workstation-event-code event))))
    (when unicode?
      (insert-typed-in-character-at-cursor
        (code-wide-character unicode?)))))


;(defun handle-hangul-code-entry-event (event)
;  (declare (ignore event))
;  (enter-escape-context 'hangul-code-entry))

;(defun handle-cyrillic-code-entry-event (event)
;  (declare (ignore event))
;  (enter-escape-context 'cyrillic-code-entry))



;(defun handle-kanji-code-entry-event (event)
;  (declare (ignore event))
;  (case (special-entry-context? current-edit-state)        ; combine with above?
;    (kanji-code-entry
;     (return-from-current-workstation-context type-of-current-workstation-context)
;     (in-editing-context (specific-structure-for-current-workstation-context)
;       (when (valid-block-in-workstation-context-p (edit-workspace current-edit-state)
;                                                   current-edit-state)
;         (insert-text-string-at-cursor "~\\" nil nil))))
;    (special-character-entry
;     ;; wrong now! if it's the code for special entry, and that's a legal
;     ;; character to insert, insert it.  (this only works in the default case
;     ;; now.)
;     (insert-text-string-at-cursor "~\\" nil nil))
;    (t (enter-escape-context 'kanji-code-entry))))




;(defun handle-special-character-entry-event (event)
;  (declare (ignore event))
;  (case (special-entry-context? current-edit-state)
;    (kanji-code-entry
;     (return-from-current-workstation-context type-of-current-workstation-context)
;     (in-editing-context (specific-structure-for-current-workstation-context)
;       (when (valid-block-in-workstation-context-p (edit-workspace current-edit-state)
;                                                   current-edit-state)
;           (insert-text-string-at-cursor "~~" nil nil))))
;    (special-character-entry
;     ;; wrong now! if it's the code for special entry, and that's a legal
;     ;; character to insert, insert it.  (this only works in the default case
;     ;; now.)  Similarly review kanji-code-entry/hangul-code-entry!!  (MHD
;     ;; 2/10/94)
;     (insert-text-string-at-cursor "~~" nil nil))
;    (t (enter-escape-context 'special-character-entry))))







;;;; Russian/Cyrillic (CFEP) Facilities


;;; The edit workstation event type and handler `cyrillic-character-in-text' ...

(define-editor-ui-command cyrillic-character-in-text ()
  (handle-cyrillic-character-in-text-event event))


;;; `Handle-cyrillic-character-in-text-event' is called when the editor is in
;;; Cyrillic mode for each event key-code that is key-code-type-p.

(defun-allowing-unwind handle-cyrillic-character-in-text-event (event)
  (let* ((unicode (convert-key-code-to-unicode (workstation-event-code event)))
         (cyrillic-alternative-character?
           (map-gensym-keyboard-character-to-cyrillic-alternate unicode)))
      (let ((text-string-to-insert
              (make-wide-string
                1
                :initial-element
                (code-wide-character
                  (or cyrillic-alternative-character?
                      unicode)))))
        (insert-text-string-at-cursor text-string-to-insert nil nil nil t)
        (reclaim-text-string text-string-to-insert))))


(defun map-gensym-keyboard-character-to-cyrillic-alternate (unicode)
  (when (simple-character-code-p unicode)
    (map-key-cap-to-gensym-cyrillic-character-code
      unicode)))




(defun exit-cyrillic-input-mode ()
  (setf (cyrillic-input-mode? current-edit-state) nil)
  (update-cyrillic-input-buttons))


;;; Enter-cyrillic-input-mode ...

(defun enter-cyrillic-input-mode ()
  (setf (cyrillic-input-mode? current-edit-state) t)
  (update-cyrillic-input-buttons))


;;; `Update-cyrillic-input-buttons' ...  "always does the right thing".  At
;;; present, this can only be called in context in which RUSSIAN is the current
;;; language.  This means it can safely assume that no HFEP or KFEP buttons, or
;;; their associated modes, need to be considered.

(defun update-cyrillic-input-buttons ()
  (let* ((edit-subcommand-menu?
           (edit-subcommand-menu? current-edit-state))
         (cyrillic-input-mode?
           (cyrillic-input-mode? current-edit-state)))
    (cond
      ((and (eq (natural-language-for-editor? current-edit-state) 'russian) ; necessary?
            edit-subcommand-menu?)
       (enable-or-disable-radio-button-subcommand
         edit-subcommand-menu? 'CYRILLIC
         (not cyrillic-input-mode?))
       (enable-or-disable-radio-button-subcommand
         edit-subcommand-menu? 'ENGLISH
         cyrillic-input-mode?)))))





;;;; Korean/Hangul (HFEP) Facilities



;;; `In-hfep-context' ... To be used in an editing context, wrapped
;;; around calls to run-hfep-automaton.

(defmacro in-hfep-context (&body body)
  `(let* ((current-hfep-Cchar (hfep-Cchar current-edit-state))        ; structure
          (current-hfep-Nchar (hfep-Nchar current-edit-state))        ; structure
          (current-hfep-c-state (hfep-c-state current-edit-state))        ; int
          (current-hfep-c-act (hfep-c-act current-edit-state)))        ; int
     (prog1
       (progn . ,body)
       (setf (hfep-c-state current-edit-state) current-hfep-c-state)
       (setf (hfep-c-act current-edit-state) current-hfep-c-act))))


;;; The edit workstation event type and handler `hangul-character-in-text'
;;; is adapted from the public domain DK Korean emacs editor extension.  It
;;; interfaces to the HFEP1 and HFEP2 modules.  It is adapted from the original
;;; dk-self-insert and dk-filter functions found in the original emacs-lisp file
;;; dk.el, as well as from the character-in-text event type/handler native
;;; to EDIT.

(define-editor-ui-command hangul-character-in-text ()
  (handle-hangul-character-in-text-event event))


;;; `Handle-hangul-character-in-text-event' is called when the editor is in
;;; Hangul mode for each event key-code that is key-code-type-p.
;;;
;;; It interacts with, and makes use of, the value of slot
;;;
;;;   (previous-edit-context-specific-event? current-edit-state)
;;;
;;; as follows.
;;;
;;; If the key code does not represent a simple character, then it is assumed to
;;; not represent a Roman character, and therefore to not map into our Hangul
;;; keyboard mapping; in this case, nothing is done at all, and this returns nil.
;;;
;;; Otherwise, this returns non-nil.  If the slot's value is other than
;;; HANGUL-CHARACTER-IN-TEXT, it resets the Hangul input automomaton.  It then
;;; runs the automaton, i.e., either from its previous state or from its reset
;;; state.  Finally, it sets name-of-current-editor-command? to
;;; HANGUL-CHARACTER-IN-TEXT, which results in the slot's value being set to
;;; that same value.  Moreover, all other edit-specific event handlers set the
;;; slot's value to something new and different.  Non-edit-specific event
;;; handlers (e.g., control-s, which makes a workspace smaller in scale) do not
;;; change the slot's value at all.

(defun-allowing-unwind handle-hangul-character-in-text-event (event)
  (multiple-value-bind (character-or-character-code escape-character?)
      (convert-key-code-to-gensym-character (workstation-event-code event))
    (when (null escape-character?)
      ;; character-or-character-code is now known to be a simple character
      (unless (eq (previous-edit-context-specific-event? current-edit-state)
                  'hangul-character-in-text)
        (reset-hangul-input-automaton))
      (protected-let*
          ((input
             (tformat-text-string "I~c" character-or-character-code)
             (reclaim-text-string input))
           (output
             (in-hfep-context (run-hfep-automaton input))
             (reclaim-text-string output))
           (length (text-string-length output)))
        (process-hfep-output output length))
      (setq name-of-current-editor-command? 'hangul-character-in-text))))


(defun process-hfep-output (output-text-string number-of-characters-to-process)
  (loop while (>=f number-of-characters-to-process 4)
        as substring-start-index
        from 0
           below number-of-characters-to-process
           by 4
        as line
           = (text-string-substring
               output-text-string
               substring-start-index
               (+f substring-start-index 4))
;       as norc = (wide-character-code (charw line 0))
        as flag = (wide-character-code (charw line 1))
        as char1 = (charw line 2)
        as char2 = (charw line 3)
        do (cond
             ((>f (wide-character-code char1) 127)        ; "(is-echar char1)" in orig.
              ;; from orig:
              ;;   rhee@camars.kaist.ac.kr 1991/01/20
              ;;   added to cope with a bug in dk.c
              (if (and (>f (wide-character-code char2) 127) ; "(is-echar char2)" in orig.

                       (<f (wide-character-code char1)
                           #.(+ 127 32 42)))
                                        ;   (<f ...) clause added by MHD; see
                                        ;   note below; 32 is the starting row
                                        ;   of KSC characters; 42 is the offset
                                        ;   or the 1st row of Chinese characters
                                        ;   in KSC (MHD 2/2/95)
                  ()
                  ;; This generates the "missing syllable" (rectangle)
                  ;; character, i.e., for a syllable that is not represented
                  ;; in the KSC 5601 character set for Hangul.  We've extended
                  ;; it to deal with Chinese characters that occasionally
                  ;; turn up, e.g.,
                  ;;
                  ;;   Typing d i e => (row/column) 52/8
                  ;;          d i w =>              52/23
                  ;;          d i z =>              52/25
                  ;;
                  ;; (MHD/HeeWon 2/2/95)
                  (progn
                    (setq char1 (code-wide-character #o241))
                    (setq char2 (code-wide-character #o340))))
              (let ((hangul-character-sequence-text-string
                      (twith-output-to-text-string
                        (twrite-character
                          (code-wide-character
                            (or (map-KS-C-5601-to-unicode
                                  (ks2-bytes-to-ksc5601
                                    (wide-character-code char1)
                                    (wide-character-code char2)))
                                #xFFFF)))))) ; should not get here in practice
                ;; CHECK FOR LEGALITY?!
                ;; G = Go on
                ;; W = Wrong. Last jongSung of previous character is
                ;;     moved to ChoSung of this char
                (if (wide-character-member
                      (code-wide-character
                        (hfep-previous-input-flag current-edit-state))
                      '(#.%\G #.%\W))
                    ;; in these cases, replace the previous character
                    ;; with the returned character:  (Note: code
                    ;; adapted from move-or-delete-from-cursor.)
                    (let* ((cursor-line-index
                             (cursor-line-index current-edit-state))
                           (cursor-character-index
                             (cursor-character-index current-edit-state))
                           (text-tail-for-cursor
                             (find-text-tail-for-line
                               (text-being-edited current-edit-state)
                               cursor-line-index)))
                      (multiple-value-bind (line-index-away-from-cursor?
                                             character-index-away-from-cursor?
                                             text-tail?)
                          (find-previous-character-if-any
                            cursor-line-index cursor-character-index
                            text-tail-for-cursor
                            (text-being-edited current-edit-state))
                        (cond
                          (line-index-away-from-cursor?
                           (change-edit-box
                             text-tail? line-index-away-from-cursor?
                             character-index-away-from-cursor?
                             cursor-line-index cursor-character-index
                             hangul-character-sequence-text-string)))))
                    ;; otherwise, just insert the character:
                    (insert-text-string-at-cursor
                      hangul-character-sequence-text-string nil nil nil t))
                (reclaim-text-string hangul-character-sequence-text-string))
              (setf (hfep-previous-input-flag current-edit-state) flag))
             (t
              ;; "sometimes the automaton sends a meaningless code.
              ;; just ignore them" -- from orig.
              (let ((char-string (tformat-text-string "~c" char2)))
                (insert-text-string-at-cursor char-string nil nil nil t)
                (reclaim-text-string char-string))
              (reset-hangul-input-automaton)))
           (reclaim-text-string line)))




;;; Reset-hangul-input-automaton ...

(defun reset-hangul-input-automaton ()
  (if (hangul-input-mode? current-edit-state)        ; =>? reset automaton?
      (in-hfep-context
        (run-hfep-automaton #w"R")
        (setf (hfep-previous-input-flag current-edit-state)
              (wide-character-code #.%\R)))))



;;; Exit-hangul-input-mode ...

(defun exit-hangul-input-mode ()
  (reset-hangul-input-automaton)
  (setf (hangul-input-mode? current-edit-state) nil)
  (update-hangul-input-buttons))


;;; Enter-hangul-input-mode ...

(defun enter-hangul-input-mode ()
  (setf (hangul-input-mode? current-edit-state) t)
  (reset-hangul-input-automaton)
  (update-hangul-input-buttons))



;;; `Update-hangul-input-buttons' ...  "always does the right thing".  At
;;; present, this can only be called in context in which KOREAN is the current
;;; language.  This means it can safely assume that no KFEP buttons, or KFEP
;;; modes, need to be considered.

(defun update-hangul-input-buttons ()
  (let* ((edit-subcommand-menu?
           (edit-subcommand-menu? current-edit-state))
         (hangul-input-mode?
           (hangul-input-mode? current-edit-state)))
    (cond
      ((and (eq (natural-language-for-editor? current-edit-state) 'korean) ; necessary?
            edit-subcommand-menu?)
       (enable-or-disable-radio-button-subcommand
         edit-subcommand-menu? 'HANGUL
         (not hangul-input-mode?))
       (enable-or-disable-radio-button-subcommand
         edit-subcommand-menu? 'ENGLISH
         hangul-input-mode?)))))




;;;; Editing Commands and their Support Code

;;; These are some of the editing commands, and also a lot of the
;;; the middle-level functions that support these and other basic
;;; editing commands.




;;; The functions here for cursor movement are sensitive to the variable
;;; `shift-variant-for-cursor-movement-p', which is bound to nil at
;;; top level, and should be dynamically bound around non-delete-case calls to
;;; move-or-delete-from-cursor where it is intended that a text region be
;;; (extended, shrunk, or removed, as appropriate).  This is intended to be used
;;; for all the variants of all of the cursor movement commands invoked by
;;; holding down the Shift key while entering the basic keystroke for the
;;; command.
;;;
;;; For example, if the shift key is pressed down while pressing
;;; control+right-arrow, a selected text region will be created if there is not
;;; one already, and then the selected text region's free end will be moved
;;; rightward one word.

(defvar shift-variant-for-cursor-movement-p nil)


;;; `Replace-pending-delete-text-region' is a subfunction of commands that
;;; operate upon a "pending delete" selected text region.  Text-region must be
;;; the selected text region in the current editing
;;; context. Text-string-to-insert should be a text string, and it will replace
;;; the text in the selected text region.  The cursor is moved to occupy the
;;; position in between the text before and after the selected text region.  The
;;; text region is deselected as the currently selected text region and deleted.

(defun replace-pending-delete-text-region
    (text-region text-string-to-insert)
  (let* ((line-index (backward-line-index-of-text-region text-region))
         (character-index (backward-character-index-of-text-region text-region))
         (text-tail
           (find-text-tail-for-line
             (text-being-edited current-edit-state) line-index))
         (line-index-past (forward-line-index-of-text-region text-region))
         (character-index-past (forward-character-index-of-text-region text-region)))
    (deselect-current-text-region text-region)
    (change-edit-box nil line-index character-index)
    (insert-text-string-in-text-being-edited
      text-string-to-insert nil nil
      line-index character-index text-tail
      line-index-past character-index-past
      nil nil t)))


;;; `Insert-typed-in-character-at-cursor' is the command use to insert all
;;; ordinary printing characters typed in from the keyboard... If there is a
;;; selected region, the region's text is replaced by the character typed in.
;;; Also in this case there is no special handling of typed-in spaces and @'s.
;;; Otherwise, typed-in spaces and @'s (i.e., the symbol and string quoting
;;; character) receive due special handling.

(defun-void insert-typed-in-character-at-cursor (unicode-wide-character)
  (let ((text-string (stringw unicode-wide-character))
        (text-region? (get-selected-text-region-for-edit-box)))
    (cond
      (text-region?
       (replace-pending-delete-text-region text-region? text-string))
      (t
       (insert-text-string-at-cursor
         text-string nil
         (if (unless                        ; nil prior to 10/28/89 (LH)
                 (if (edit-undo-stack current-edit-state)        ; if a space or @ has just
                     (eq (special-type-of-edit-box-change?        ;   been typed in
                           (first (edit-undo-stack current-edit-state)))
                         'typed-in-space-or-\@))
               (dont-space-before-character-p unicode-wide-character))
             'DO-NOT-ADD-SPACE-AFTER)
         ;; handle other kinds of spaces besides ordinary space?!
         (if (or (char=w unicode-wide-character #.%space)
                 (char=w unicode-wide-character #.%\@))
             'typed-in-space-or-\@)
         t)))
    (reclaim-text-string text-string)))

;; The final arg for insert-text-string-... used to be passed in as NIL
;; for Space or @, when typed in.  Why was this?  Now it's T.  Could this
;; cause a problem?! (MHD 5/6/94)



;;; `Insert-text-string-at-cursor' ...  Text-string is not reclaimed, and may be
;;; just an ordinary string, not necessarily a text string.
;;;
;;; With replace-entire-text? true, this effectively replaces the entire text in
;;; the edit box with text-string, leaving the cursor at the end.

(defun insert-text-string-at-cursor
    (text-string replace-fragments-on-sides? handle-spaces-intelligently?
                 &optional special-type-of-edit-box-change?        ; make non-optional?
                 typed-in?
                 replace-entire-text?)
  (cond
    (replace-entire-text?
     (replace-entire-edit-box-text text-string))
    (t
     (let ((cursor-line-index (cursor-line-index current-edit-state))
           (cursor-character-index (cursor-character-index current-edit-state)))

       ;; What to do when the cursor is at the beginning of the line, and the
       ;; user types a space, but you're doing "word wrap", so they usually
       ;; don't get to see anything.  Perhaps they imagined they were typing a
       ;; space after a newline, but they were wrong.  What to do?
       ;;
       ;; Let's do like most word processors, and let this happen.  Let the
       ;; space go in, and let there not be any space at the beginning of the
       ;; line to show for it.  This is just what you get when you have a word
       ;; processor doing word wrap, e.g., MS Word.
       ;;
       ;; There is little doubt that it will confuse few users of modern word
       ;; processors, and it is well known that the old message has been a
       ;; source of confusion and annoyance to users who've encountered it,
       ;; especially beginners.
       ;;
       ;; In other words, while the old was was a good, original solution to a
       ;; problem of confusion, experience has shown that it is best to treat it
       ;; as a "non-problem". In fact just "letting it happen" is exactly the
       ;; industry-standard thing to do. (MHD 4/18/94)

;       (if (and (>f cursor-line-index 1)
;                  (=f cursor-character-index 0)
;                  (memberp text-string
;                           '(" " "@V" "@W" "@X" "@Y" "@R" "@Q")
;                           :test 'equal))               ; same as string=
;         (display-editor-notification
;             "~A illegal at the beginning of this line"
;           (if (string= text-string " ") "Space" text-string))
;         ;; [form below was previosly the else clause. (MHD 4/18/94)]
;         ...)

       (insert-text-string-in-text-being-edited
         text-string replace-fragments-on-sides? handle-spaces-intelligently?
         cursor-line-index cursor-character-index
         (find-text-tail-for-line                ; fix later!
           (text-being-edited current-edit-state)
           cursor-line-index)
         nil nil nil special-type-of-edit-box-change? typed-in?)))))




;;; Replace-entire-edit-box-text updates the edit box to contain text string as
;;; its sole text ... Text-string is not reclaimed.

(defun replace-entire-edit-box-text (text-string)
  (let ((text-tail (text-being-edited current-edit-state))
        (line-index 1)
        (character-index 0))
    (multiple-value-bind (line-index-at-end character-index-at-end)
        (find-end-of-text text-tail line-index)
      (insert-text-string-in-text-being-edited
        text-string nil nil
        line-index character-index text-tail
        line-index-at-end character-index-at-end))))

;; Think of a better name?! (MHD)





;;; Insert-text-string-at-cursor-from-outside, without the optional argument
;;; replace-entire-text?, is just like insert-text-string-at-cursor except that
;;; it sets up for editing in the current workstation context, which is assumed
;;; to be an editing context.

;;; Insert-character-at-cursor-from-outside is similar but takes a character
;;; instead of a string.

(defun insert-text-string-at-cursor-from-outside
    (text-string &optional replace-fragments-on-sides? handle-spaces-intelligently?
                 replace-entire-text? special-type-of-edit-box-change?)
  (in-editing-context (specific-structure-for-current-workstation-context)
    (insert-text-string-at-cursor
      text-string
      replace-fragments-on-sides?
      handle-spaces-intelligently?
      special-type-of-edit-box-change?
      nil
      replace-entire-text?)))

(defun insert-character-at-cursor-from-outside
    (character &optional replace-fragments-on-sides? handle-spaces-intelligently?
               replace-entire-text? special-type-of-edit-box-change?)
  (in-editing-context (specific-structure-for-current-workstation-context)
    (twith-output-to-then-use-of-text-string
      (twrite-char character)
      (setf (wide-string-length current-wide-string) 1)
      (insert-text-string-at-cursor
        current-wide-string
        replace-fragments-on-sides?
        handle-spaces-intelligently?
        special-type-of-edit-box-change?
        nil
        replace-entire-text?))))



;;; Insert-text-string-in-text-being-edited ...  Text-string is not reclaimed,
;;; and may be just an ordinary string, not necessarily a text string.
;;; Text-string must not be empty.

;;; When replace-fragments-on-sides? is specified, initial and/or final
;;; fragments of text-string on one or both sides of the insertion position are
;;; overlaid, provided such fragments do not end at a text position between two
;;; alphanumeric characters.

;;; When handle-spaces-intelligently? is specified, ...  If
;;; handle-spaces-intelligently? is DO-NOT-ADD-SPACE-AFTER, no space is added
;;; after text-string under any circumstances.

(defun insert-text-string-in-text-being-edited
       (text-string replace-fragments-on-sides? handle-spaces-intelligently?
        line-index character-index text-tail
        &optional line-index-past-deletion? character-index-past-deletion?
                  no-parsing-or-ellipsis-deletion? special-type-of-edit-box-change?
                  typed-in?)
  (let* ((length-of-text-string (text-string-length text-string))
         (kfep-conversion-text-region?
           (kfep-conversion-text-region? current-edit-state))
         (text-string? nil)                        ; if text-string not to be used
         (start (if replace-fragments-on-sides? length-of-text-string 0))
         character?
         string-character?
         backward-line-index? backward-character-index? backward-text-tail?
         forward-line-index? forward-character-index? forward-text-tail?
         backward-line-index-1? backward-character-index-1? backward-text-tail-1?
         forward-line-index-1? forward-character-index-1? forward-text-tail-1?)
    ;; The following always results in non-nil FINAL values for
    ;; backward-line-index? et al.
    (multiple-value-setq
      (backward-line-index? backward-character-index? backward-text-tail? start)
      (match-adjacent-symbol-boundary
        text-string start 0 length-of-text-string
        line-index character-index text-tail
        t
        (text-being-edited current-edit-state)))
    ;; The following always results in non-nil FINAL values for
    ;; forward-line-index? et al.
    (multiple-value-setq
        (forward-line-index? forward-character-index? forward-text-tail?)
      (match-adjacent-symbol-boundary
        text-string
        (if replace-fragments-on-sides? start length-of-text-string)
        0
        length-of-text-string
        (or line-index-past-deletion? line-index)
        (or character-index-past-deletion? character-index)
        text-tail))
    ;; The following always results in non-nil FINAL values for
    ;; backward-line-index? et al and forward-line-index? et al.
    (cond
      ((and handle-spaces-intelligently?
;            (null kfep-conversion-text-region?)       ; taken out -- LH -- 8/22/90
            (>f length-of-text-string 0))
       (let* ((text-string-should-not-follow-a-space?
                ;; added taking into account poss. that char 0 could
                ;; be an escape character (e.g., ~): (MHD 12/2/94)
                (let ((char (find-next-character-in-text-line 0 text-string)))
                  (or (dont-space-before-character-p char)
                      (char=w char #.%space))))
              previous-character?
              next-character?)
         (multiple-value-setq
           (backward-line-index-1? backward-character-index-1? backward-text-tail-1?
            previous-character?)
           (find-previous-character-if-any
             backward-line-index? backward-character-index?
             backward-text-tail? (text-being-edited current-edit-state)))

         (when (and previous-character?
                    (newline-p previous-character?))
           ;; other cases - corresponding to the old markup of
           ;; @ + one of these: #.%\P #.%\L #.%\V #.%\W #.%\X #.%\Y #.%\R #.%\Q
           (setq previous-character? #.%\())

         (multiple-value-setq
           (forward-line-index-1? forward-character-index-1? forward-text-tail-1?
            next-character?)
           (find-next-character-if-any
             forward-line-index? forward-character-index? forward-text-tail?))

         (when nil
           ;; corresponding to the old markup of @ + one of these: #.%\V #.%\W #.%\X
           ;; #.%\Y #.%\R #.%\Q
           (setq next-character? #.%\)))

         (cond                                        ; advances past following space
           ((eqlw next-character? #.%space)
            (setq forward-text-tail? forward-text-tail-1?)
            (setq forward-line-index? forward-line-index-1?)
            (setq forward-character-index? forward-character-index-1?)))
         (cond                                        ; backs up over unwanted preceding space
           ((and (eqlw previous-character? #.%space)
                 text-string-should-not-follow-a-space?)
            (setq backward-text-tail? backward-text-tail-1?)
            (setq backward-line-index? backward-line-index-1?)
            (setq backward-character-index? backward-character-index-1?)))
         (let ((add-space-after?                ; add space after, if appropriate
                 (and (not (eq handle-spaces-intelligently? 'DO-NOT-ADD-SPACE-AFTER))
                      (progn
                        (multiple-value-setq (string-character?)
                          (find-previous-character-in-text-line
                            length-of-text-string text-string))
                        (not (or (eqlw string-character? '#.%space)
                                 (eq (bracket-open-or-close? string-character?)
                                     'open))))
;                      (not (memberp next-character? ; disabled 10/28/89 (LH)
;                                    '(#.%\! #.%\) #.%\, #.%\: #.%\; #.%\? #.%\] #.%\})))
                      ))        ; others?
               (add-space-before?                ; add space before, if appropriate
                 (and (not text-string-should-not-follow-a-space?)
                      previous-character?
                      (not (or (eqlw previous-character? '#.%space)
                               (eq (bracket-open-or-close?
                                       previous-character?)
                                     'open))))))
           (if (or add-space-after? add-space-before?)
               (setq text-string?
                     (twith-output-to-text-string        ; do more efficiently?
                        (if add-space-before? (twrite-char #.%space))
                        (twrite-string text-string)
                        (if add-space-after? (twrite-char #.%space)))))))))
    (if (and kfep-conversion-text-region?
             typed-in?
             (loop for i from 0 below length-of-text-string        ; accept kanji roman
                   as character = (charw text-string i)                ;   characters also?
                   always (or (alpha-char-pw character)
                              (wide-character-member
                                character
                                allowable-non-alpha-characters-in-kfep-conversions))))
        (loop with backward-character-index-2? = backward-character-index?
              while
                (and (multiple-value-setq (backward-line-index-1?        ; previous
                                           backward-character-index-1?        ;   character
                                           backward-text-tail-1?
                                           character?)
                       (find-previous-character-if-any
                         backward-line-index? backward-character-index-2?
                         backward-text-tail?
                         (text-being-edited current-edit-state)))
                     (=f backward-line-index-1? backward-line-index?)        ; on same line
                     (not                        ; not before beginning of region
                       (or (<f backward-line-index-1?
                               (line-index-for-fixed-end-of-text-region
                                 kfep-conversion-text-region?))
                           (and (=f backward-line-index-1?
                                    (line-index-for-fixed-end-of-text-region
                                      kfep-conversion-text-region?))
                                (<f backward-character-index-1?
                                    (character-index-for-fixed-end-of-text-region
                                      kfep-conversion-text-region?)))))
                     (or (alpha-char-pw                    ;   or hiragana code or hyphen
                           character?)
                         (wide-character-member
                           character?
                           allowable-non-alpha-characters-in-kfep-conversions)
                         ;; For Kanji or Hiragana modes, back up over Hiragana
                         ;; characters, but not Katakana.  For the Katakana
                         ;; mode, back up over Katakana but not Hiragana.  This
                         ;; backing up over kana characters is necessary because
                         ;; such cases as "n" and "ni" having different kana
                         ;; conversions.
                         (case (kana-conversion-mode? current-edit-state)
                           (katakana
                            (wide-character-is-katakana-jis-code-p character?))
                           ((hiragana nil)
                            (wide-character-is-hiragana-jis-code-p character?)))))
              do (setq backward-character-index-2? backward-character-index-1?)
              finally
                (let* ((extended-text-string?
                         (if (not (=f backward-character-index-2?
                                      backward-character-index?))
                             (let ((text-line        ; collect characters above instead?
                                     (get-next-text-line backward-text-tail?)))
                               (twith-output-to-text-string        ; do more efficiently?
                                 (twrite-portion-of-string-unparsably
                                   text-line
                                   backward-character-index-2? backward-character-index?)
                                 (twrite-portion-of-string-unparsably
                                   text-string
                                   nil nil))))))
                  (when (setq text-string?
                              (case (kana-conversion-mode? current-edit-state)
                                (katakana
                                 (convert-to-katakana-if-possible
                                   (or extended-text-string? text-string)))
                                ((nil hiragana)
                                 (convert-to-hiragana-if-possible
                                   (or extended-text-string? text-string)))))
                    (loop with text-line
                            = (get-next-text-line backward-text-tail?)
                          as i = 0 then j
                          as j = i
                          while
                            (<f backward-character-index-2? backward-character-index?)
                          do (incff j) ; skip past one wide character
                          while
                            (loop as k from i below j
                                  as backward-character-index-1?
                                     from backward-character-index-2?
                                  always (eqlw (charw text-string? k)
                                              (charw text-line
                                                    backward-character-index-1?)))
                          do (incff backward-character-index-2? (-f j i))
                          finally
                            (if (>f i 0)
                                (let ((reduced-text-string
                                        (text-string-substring text-string? i nil)))
                                  (reclaim-text-string text-string?)
                                  (setq text-string? reduced-text-string))))
                    (setq backward-character-index? backward-character-index-2?))
                  (if extended-text-string?
                      (reclaim-text-string extended-text-string?)))))
    (let ((replacing?
            (not (and (=f forward-line-index? backward-line-index?)
                      (=f forward-character-index? backward-character-index?)))))

      (when (and (native-editor-workspace-p current-edit-workspace)
                 (not native-editor-already-updated))
        (native-editor-replace-text
          current-edit-state
          (or text-string? text-string)
          backward-line-index? backward-character-index?
          (if replacing? forward-line-index?) (if replacing? forward-character-index?)))

      (change-edit-box                                ; fully replaces when (>f end start)
        backward-text-tail? backward-line-index? backward-character-index?
        (if replacing? forward-line-index?) (if replacing? forward-character-index?)
        (or text-string? text-string)
        nil nil
        no-parsing-or-ellipsis-deletion? special-type-of-edit-box-change? nil nil t)
      ;; If kfep mode and insertion was not typed in but not automatic, then move
      ;; conversion region to cursor.
      (when (and kfep-conversion-text-region?
                 (not typed-in?)
                 (not (eq special-type-of-edit-box-change? 'automatic)))
        (enter-kana-conversion-mode
          (kana-conversion-mode? current-edit-state))))
    (if text-string? (reclaim-text-string text-string?))))

;; Fixed to really be for alphanumeric, and not just alphabetic, but that was
;; always the spec.  (Perhaps it was because there was no
;; alphanumeric-gensym-character-p, or something.) Now, if you insert the name
;; box with name FOO when the cursor is before o7 (letter "o" followed by "7"),
;; it does not try to merge FOO in with o7, whereas it used to.  This is
;; good. (See JH's bug report and bug KB, which illustrated this:
;; /home/jh/snarf-final-char-bug-4-0.kb) (MHD 5/15/95)

;; Fixed bug that clicking on right paren after
;;
;;    if ((3 + 3)
;;
;; would not insert anything.  Now, it inserts a space after it.  And subsequently,
;; clicking on the paren again inserts it.  (How it was in 3.0).  Abstracted
;; out the first two very-similar loops into function below.  More needs to be done.
;; (MHD 5/24/95)

;; Beware that this assumes that #.%space can never be a
;; "character-following-\\~".  If that changes, this could potentially break in
;; some obscure cases.  It seems wise to convert direct simple character
;; comparison, i.e., of space, without considering the escape character, to
;; gensym-character-equal, with appropriate escape-character arg(s), at some
;; opportune point in time.  Also, I haven't checked it completely, but it may
;; also be the case that comparison with other characters have this problem,
;; even with ones that _can_ be escaped.  I did just fix one bug (HQ-74717) that
;; was based on this problem. (MHD 12/2/94)

;; Consider abstracting, as a function, the two fragment overlaying loops.

;; Consider inserting only the start to end portion of text-string, with no
;; deletion.  This would eliminate case normalization and would require that
;; cursor positioning be handled in some special way.

;; Consider having the case and capitalization of what is inserted contextually
;; determined.



;;; `Match-adjacent-symbol-boundary' matches the symbol around the index start
;;; in text-string, if any, with the same symbol, if any, in the text-tail (and
;;; perhaps text in the backwards? case) at the position given by line-index and
;;; character-index.
;;;
;;; If backwards? is true, this looks backwards from the given positions.
;;; Otherwise, it searches forwards.  Text is required only in the backwards?
;;; case; in the forward case, it is ignored.  Text, when given, should be the
;;; entire text, and must contain text-tail as one of its top-level conses.
;;;
;;; It returns these 4 values:
;;;
;;;    adjacent-line-index?
;;;    adjacent-character-index?
;;;    adjacent-text-tail?
;;;    new-string-index?

(defun match-adjacent-symbol-boundary
    (text-line string-index string-start string-end
                 line-index character-index text-tail &optional backwards? text)
  (loop with adjacent-line-index?
        with adjacent-character-index?
        with adjacent-text-tail?
        with character?
        with adjacent-line-index-1?
        with adjacent-character-index-1?
        with adjacent-text-tail-1?
        with string-character?
        as i = string-index
        as adjacent-start? = nil
        do (setq adjacent-line-index? line-index)
           (setq adjacent-character-index? character-index)
           (setq adjacent-text-tail? text-tail)
        until
        (loop when (if backwards?        ; =f enough; use "thereis"?
                       (<=f i string-start)
                       (>=f i string-end))
                return
                (not (and (if backwards?
                              (>f string-index string-start)
                              (<f string-index string-end))
                          (alpha-numeric-p character?)
                          (progn
                            (multiple-value-setq (adjacent-line-index-1?
                                                   adjacent-character-index-1?
                                                   adjacent-text-tail-1?
                                                   character?)
                              (if backwards?
                                  (find-previous-character-if-any
                                    adjacent-line-index? adjacent-character-index?
                                    adjacent-text-tail? text)
                                  (find-next-character-if-any
                                    adjacent-line-index? adjacent-character-index?
                                    adjacent-text-tail?)))
                            (if character?
                                (alpha-numeric-p character?)))))
              do (multiple-value-setq
                     (adjacent-line-index?
                       adjacent-character-index?
                       adjacent-text-tail?
                       character?)
                   (if backwards?
                       (find-previous-character-if-any
                         adjacent-line-index? adjacent-character-index?
                         adjacent-text-tail? text)
                       (find-next-character-if-any
                         adjacent-line-index? adjacent-character-index?
                         adjacent-text-tail?)))
          ;; Consider saving the results of the first call to the function
          ;; find-previous-character-if-any, to save redundant recomputation
          ;; later when (=f i string-index).
                 (multiple-value-setq (string-character? i)
                   (if backwards?
                       (find-previous-character-in-text-line i text-line)
                       (find-next-character-in-text-line i text-line)))
                 (if (null adjacent-start?) (setq adjacent-start? i))
              while
              (and adjacent-line-index?        ; redundant
                   (char-equalw character? string-character?)))
        do (setq string-index adjacent-start?)
        finally
          (return
            (values adjacent-line-index? adjacent-character-index? adjacent-text-tail? string-index))))



;;; `Delete-intelligently-from-text-being-edited' ... handles spaces intelligently.

;;; A space just after the deletion will also be deleted if it will end up at
;;; the beginning of the text being edited or if the character just before the
;;; deletion is a space or left parenthesis class character.

;;; A space just before the deletion will also be deleted if the character just
;;; after the deletion is a space or comma or right parenthesis class character.
;;; (Later, it may also do this if the space just before the deletion will end
;;; up at the end of the text being edited.)

;;; The first character of the deletion will NOT be deleted if it is a space and
;;; the last character of the deletion is a space and neither the character just
;;; before the deletion or just after the deletion is a space and the deletion
;;; is three or more characters long.

;;; At present, "space" refers to an ordinary (ascii) space.

;; Is the last case appropriate?

(defun delete-intelligently-from-text-being-edited
       (text-tail? line-index-of-change character-index-of-change
        line-index-past-deletion character-index-past-deletion
        &optional no-parsing-or-ellipsis-deletion? special-type-of-edit-box-change?)
  (let* ((text-being-edited
           (text-being-edited current-edit-state))
         (text-tail
           (or text-tail?
               (find-text-tail-for-line text-being-edited line-index-of-change)))
         (text-tail-past-deletion
           (find-text-tail-for-line text-being-edited line-index-past-deletion)))
    (multiple-value-bind (backward-line-index? backward-character-index?
                          backward-text-tail? previous-character?)
        (find-previous-character-if-any
          line-index-of-change character-index-of-change text-tail text-being-edited)
      (when (and previous-character?
                 (or (newline-p previous-character?)        ; escape-character?
                     ;; others?!
                     ))
        (setq previous-character? #.%\x)        ; map some into #.%space?
        )
      (multiple-value-bind (forward-line-index? forward-character-index?
                            forward-text-tail? next-character?)
          (find-next-character-if-any
            line-index-past-deletion character-index-past-deletion
            text-tail-past-deletion)
        (declare (ignore forward-text-tail?))
        (when (and next-character?
                   (or (newline-p next-character?) ; escape-character?
                       ;; others?!
                       ))
          (setq next-character? #.%\x)
;          (setq escape-character? nil)        ; map some into #.%space?
          )
        (cond
          ((eqlw next-character? #.%space)
           (cond
             ((or (null previous-character?)
                  (or (eqlw previous-character? '#.%space)
                      (eq (bracket-open-or-close? ; pass in esc. char!
                            previous-character?)
                          'open)))
              (setq line-index-past-deletion forward-line-index?)        ; changes args
              (setq character-index-past-deletion forward-character-index?))))
          ((if (eqlw previous-character? #.%space)
               (or ; (null next-character?) ; deletes space at end of text
                 (dont-space-before-character-p
                   next-character?)
                 ;; above replaces this:  (MHD 4/16/94)
;                   (memberp next-character?
;                            '(#.%\! #.%\) #.%\, #.%\: #.%\; #.%\? #.%\] #.%\}))        ; others?
                   )
               (and (multiple-value-setq (backward-line-index? backward-character-index?
                                          backward-text-tail? previous-character?)
                      (find-next-character-if-any
                        line-index-of-change character-index-of-change text-tail))
                    (not (and previous-character?
                              (newline-p previous-character?))) ; (null escape-character?)
                    (eqlw previous-character? #.%space)
                    (multiple-value-setq-some
                      (forward-line-index? forward-character-index?
                       nil                        ; forward-text-tail?
                       next-character?)
                      (find-previous-character-if-any
                        line-index-past-deletion character-index-past-deletion
                        text-tail-past-deletion text-being-edited))
                    (not (and next-character?
                              (newline-p next-character?))) ; (null escape-character?)
                    (eqlw next-character? #.%space)
                    (or (<f backward-line-index? forward-line-index?)
                        (and (=f backward-line-index? forward-line-index?)
                             (<f backward-character-index? forward-character-index?)))))
           (setq line-index-of-change backward-line-index?)        ; changes args
           (setq character-index-of-change backward-character-index?)
           (setq text-tail backward-text-tail?)))
        (change-edit-box
          text-tail line-index-of-change character-index-of-change
          line-index-past-deletion character-index-past-deletion
          nil nil nil
          no-parsing-or-ellipsis-deletion? special-type-of-edit-box-change?)))))

;; Don't see how the tests for escape-character? could have worked inoffensively
;; with any characters but Newline, and I believe the other cases just didn't
;; tend to come up often, and users put up with them when they did! Still,
;; probably other characters should be classified along with Newline -- review
;; later! (MHD 2/17/96)

;; Note that neither of the optional arguments are used at present.

;; Consider having this be "delete-from-text-being-edited" with a handle-spaces-
;; intelligently? arg?

;; The guts of the above function have been factored out into the following,
;; but a little work remains to complete the job and have most of the code
;; really shared.  Do this later! (MHD/PGA 6/12/95)

;; The major difference in interpretation at this point between the way in which
;; the above and the below decide whether something should be treated as a word
;; is that below we assume something which ends at the end of a text, or just
;; before a period or any kind of bracket may be a word (if it's got a space or
;; bracket on its left).  Above, the end of a text may never be a word.  The
;; reason for this is so that words being cut or copied from the end of a line
;; will be treated as words.  In addition, we're checking the 4 combinations of
;; character-before-selection, first-character-of-selection, against
;; last-character-of-selection and character-after-selection.  If either of the
;; first and either of the second are delimiters then the selection is a
;; word. PGA 6/13/95

;;; `Word-like-sequence-in-text-p' is true if the specified sequence of text is
;;; "word-like".  ... This is in harmony with both deletion
;;; (delete-intelligently-from-text-being-edited) and insertion
;;; (coerce-text-region-to-scrap).


(defun word-like-sequence-in-text-p
    (text
      beginning-text-tail
      beginning-line-index beginning-character-index
      end-line-index character-index-past-deletion)
  (let ((end-text-tail (find-text-tail-for-line text end-line-index))
        beginning-character? end-character?)
    (multiple-value-bind
        (backward-line-index?
          backward-character-index? backward-text-tail? previous-character?)
        (find-previous-character-if-any
          beginning-line-index beginning-character-index beginning-text-tail
          text)
      (multiple-value-bind
          (forward-line-index?
            forward-character-index? forward-text-tail? next-character?)
          (find-next-character-if-any
            end-line-index character-index-past-deletion end-text-tail)
        (declare (ignore forward-text-tail?))
        (multiple-value-setq
            (backward-line-index? backward-character-index? backward-text-tail?
              beginning-character?)
          (find-next-character-if-any
            beginning-line-index beginning-character-index text))
        (multiple-value-setq-some
            (forward-line-index? forward-character-index? nil end-character?)
            (find-previous-character-if-any
              end-line-index character-index-past-deletion
              end-text-tail text))
        (cond
          ;; if the end character or the character ahead is the end of text or a
          ;; non-word-delimiting character, then if the same thing is true of
          ;; the beginning character or the character behind, then it's a word:
          ((or
             (null next-character?)
             (word-delimiting-character-p next-character?)
             (word-delimiting-character-p end-character?))
           (or (null previous-character?)
               (word-delimiting-character-p previous-character?)
               (word-delimiting-character-p beginning-character?))))))))


;;; Move-down-line ... moves the current position down number-of-lines, which
;;; may be negative to move up.  The character position of the cursor is as
;;; close to either (goal-x-in-workspace-for-cursor? current-edit-state), if
;;; that is non-nil and (previous-edit-context-specific-event?
;;; current-edit-state) is either GO-DOWN-LINE or GO-UP-LINE, or else the min
;;; of the end of the line and the current x position of the cursor.

;;; If to-end-ok? is specified true, this moves to the beginning of the line for
;;; negative number-of-lines, and to the end of the line for positive number of
;;; lines, iff the number-of-lines specifies a line number beyond the .

;;; If (goal-x-in-workspace-for-cursor? current-edit-state) is not used, this
;;; sets it to the x position of the cursor before the move.

;;; If to-end-ok? is specified true, or in the special case where the variable
;;; shift-variant-for-cursor-movement-p is true, when there would be no movement
;;; because we've hit the last line (first line, if negative number-of-lines),
;;; this moves the cursor (and extends the region in the shift-variant case) to
;;; the end of the last line (beginning of the first line, if negative
;;; number-of-lines).

;; NOTE: This seems to be the way both Emacs and Word work.  It seems to feel
;; quite comfortable.  The scaled-down editor you get in quickmail, by the
;; way, just moves you down to the min of the line length and the current
;; character position; i.e., it doesn't keep a "goal" position around.
;; (MHD 5/9/91)

(defun move-down-line (number-of-lines &optional to-end-ok?)
  (let*
      ((backwards? (not (pluspf number-of-lines)))
       (cursor-line-index (get-selected-edit-cursor-line-index))
       (cursor-character-index (get-selected-edit-cursor-character-index)))
    (multiple-value-bind (line-index character-index text-tail x-in-workspace)
    (find-position-in-text
      (edit-box current-edit-state) nil nil nil
      t nil nil
      cursor-line-index cursor-character-index nil)
    (declare (ignore character-index))
    (let* ((last-line-index (find-end-of-text text-tail line-index))
           (cursor-line-index (cursor-line-index current-edit-state)))
      (cond
        ;; First two cases for the special rule for extending a region by a line
        ;; -- when hit the last line, extend the region to the end of the line
        ;; in the direction:
        ((and (or to-end-ok? shift-variant-for-cursor-movement-p)
              (not backwards?)
              (>f (+f cursor-line-index number-of-lines)
                  last-line-index))
         (move-or-delete-from-cursor nil nil t))
        ((and (or to-end-ok? shift-variant-for-cursor-movement-p)
              backwards?
              (<f (+f cursor-line-index number-of-lines)
                  1))
         (move-or-delete-from-cursor nil t t))
        (t
         (let* ((goal-line-index
                  (if (<f number-of-lines 0)
                      (maxf (+f line-index number-of-lines) 1)
                      (minf (+f line-index number-of-lines)
                            last-line-index)))
                (goal-x-in-workspace
                  (or (if (memq (previous-edit-context-specific-event?
                                  current-edit-state)
                                '(go-up-line
                                  go-up-line-extending-region
                                  go-down-line
                                  go-down-line-extending-region
                                  go-up-page
                                  go-up-page-extending-region
                                  go-down-page
                                  go-down-page-extending-region))
                          (goal-x-in-workspace-for-cursor? current-edit-state))
                      x-in-workspace))
                (goal-y-in-workspace                        ; compute some other way?
                  (+w (top-edge-of-block (edit-box current-edit-state))
                      (+w (compute-distance-of-text-line-from-top
                            goal-line-index
                            (text-box-format (edit-box current-edit-state)))
                          (text-cell-line-height
                            (text-box-format
                              (edit-box current-edit-state)))))))
           (setf (goal-x-in-workspace-for-cursor? current-edit-state)
                 goal-x-in-workspace)
           (move-cursor-handling-shift-variant
             nil nil nil goal-x-in-workspace goal-y-in-workspace nil))))))))

;; It appears several modern GUI applications handle shift+up/down arrow
;; vs. simple up/down-arrow differently when you hit the beginning/end of a
;; text.  WinWord and Wordpad are two cases in point.  Don't know exactly why
;; they handle the two cases differently. (MHD 3/18/98)




;;; Move-or-delete-from-cursor either moves the insertion point, or deletes, if
;;; delete-case? is true, from the current insertion point to another position
;;; as specified.  If to-end? is true, then it moves or deletes to the end;
;;; otherwise, to the beginning.  When line-wise? is true, the interpretation of
;;; the to-end? argument is in terms of the line of text the cursor is on;
;;; otherwise, they refer to the entire text.

(defun move-or-delete-from-cursor
    (delete-case? backwards? to-end? &optional line-wise?)
  (let* ((cursor-line-index (get-selected-edit-cursor-line-index))
         (cursor-character-index (get-selected-edit-cursor-character-index))
         (text-tail-for-cursor
           (find-text-tail-for-line
             (text-being-edited current-edit-state)
             cursor-line-index)))
    (multiple-value-bind (line-index-away-from-cursor?
                          character-index-away-from-cursor?
                          text-tail?)
        (if backwards?
            (if to-end?
                (if line-wise?
                    (values
                      cursor-line-index
                      (get-character-index-past-separator text-tail-for-cursor)
                      text-tail-for-cursor
                      (text-being-edited current-edit-state))
                    (values 1 0 (text-being-edited current-edit-state) nil))
                (find-previous-character-if-any
                  cursor-line-index cursor-character-index
                  text-tail-for-cursor (text-being-edited current-edit-state)))
            (if to-end?
                (if line-wise?
                    (values
                      cursor-line-index
                      (find-end-of-line-of-text text-tail-for-cursor nil)
                      text-tail-for-cursor
                      (text-being-edited current-edit-state))
                    (find-end-of-text text-tail-for-cursor cursor-line-index))
                (find-next-character-if-any
                  cursor-line-index cursor-character-index text-tail-for-cursor)))
      (if delete-case?
          (if line-index-away-from-cursor?
              (if backwards?
                  (change-edit-box
                    text-tail? line-index-away-from-cursor? character-index-away-from-cursor?
                    cursor-line-index cursor-character-index)
                  (change-edit-box
                    text-tail-for-cursor cursor-line-index cursor-character-index
                    line-index-away-from-cursor? character-index-away-from-cursor?)))
          (move-cursor-handling-shift-variant
            text-tail?                        ; ok if these 3 args are nil
            line-index-away-from-cursor? character-index-away-from-cursor?
            nil nil
            (if (and (null to-end?) (null line-wise?))
                (if backwards? 'backward 'forward)))))))



;;; Move-or-delete-from-cursor-to-next-adjacent-word ...

(defun move-or-delete-from-cursor-to-next-adjacent-word (delete-case? backwards?)
  (let* ((cursor-line-index (get-selected-edit-cursor-line-index))
         (cursor-character-index (get-selected-edit-cursor-character-index))
         (text-tail-for-cursor
           (find-text-tail-for-line
             (text-being-edited current-edit-state)
             cursor-line-index))
         (text (text-being-edited current-edit-state))
         wide-character? line-index-away-from-cursor?
         character-index-away-from-cursor? text-tail?)
    (loop with in-space?
          with not-in-alphanumeric? = nil
          as started? = nil then t
          as line-index
             = cursor-line-index
             then line-index-away-from-cursor?
          as character-index
             = cursor-character-index
             then character-index-away-from-cursor?
          as text-tail
             = text-tail-for-cursor
             then text-tail?
          do (multiple-value-setq
               (line-index-away-from-cursor? character-index-away-from-cursor?
                text-tail? wide-character?)
               (if backwards?
                   (find-previous-character-if-any
                     line-index character-index text-tail text)
                   (find-next-character-if-any
                     line-index character-index text-tail)))
             (cond
               ((null line-index-away-from-cursor?)
                ;; (Previously, there was a return from here in the (not
                ;; started?) case.  Now, with pending delete, we can't really
                ;; return in this case; at least in the case where there's a
                ;; text region, and the shift key is not down, we have to let
                ;; the finally code take care of disposing of the region.)  (MHD
                ;; 3/19/98) -- update: this led to bug HQ-3536314 "typing alt +
                ;; delete in an editor lights up the undo button", now fixed by
                ;; having this again return in the (not started?) case, but now
                ;; only if there's no text region. (MHD 7/12/00)
                (if (and (not started?)
                         (null (get-selected-text-region-for-edit-box)))
                    (return)
                    (loop-finish)))
               ((and wide-character? (blank-p wide-character?))        ; ETC!
                (when started?
                  (when (not in-space?)
                    (loop-finish)))
                (setq in-space? t))
               (t (setq in-space? nil)
                  (cond
                    ((word-delimiting-character-p wide-character?)
                     (if started?
                         (loop-finish)
                         (setq not-in-alphanumeric? t)))
                    (not-in-alphanumeric?
                     (loop-finish)))))
          finally
            (if delete-case?
                (if backwards?
                    (delete-intelligently-from-text-being-edited
                      text-tail line-index character-index
                      cursor-line-index cursor-character-index)
                    (delete-intelligently-from-text-being-edited
                      text-tail-for-cursor
                      cursor-line-index cursor-character-index
                      line-index character-index))
                (move-cursor-handling-shift-variant
                  text-tail line-index character-index
                  nil nil nil)))))

;; Combine this with move-or-delete-from-cursor!







;;;; Shift Variants of Cursor Movement Commands

;;; This section defines, and uses, a macro to define the "shift variants" for
;;; cursor movement commands.  It also defines the function to handle the
;;; cursor movement.   For example, go-forward-character is a cursor
;;; movement command.  So this section includes the following definition:
;;;
;;;     (define-editor-ui-command go-forward-character-extending-region ()
;;;       (let ((shift-variant-for-cursor-movement-p t))
;;;         (com-go-forward-character event edit-state)))
;;;
;;; See the keymap cursor-movement-shift-variant-commands for the keybindings.

(defparameter-for-macro all-cursor-movement-commands-for-macro
  '((right-arrow go-forward-character)
    (left-arrow go-backward-character)
    (up-arrow go-up-line)
    (down-arrow go-down-line)
    (alt+f go-forward-word)
    (alt+b go-backward-word)
    (end go-to-end-of-line)
    (home go-to-beginning-of-line)
    (page-down go-down-page)
    (page-up go-up-page)
    (control+end go-to-end)
    (control+home go-to-beginning)
    (control+left-arrow go-backward-word)
    (control+right-arrow go-forward-word)
    (control+> go-to-end-of-line)
    (control+< go-to-beginning-of-line)
    (alt+> go-to-end)
    (alt+< go-to-beginning)))


(defmacro define-shift-variants-of-cursor-movement-commands ()
  (loop for (key command) in all-cursor-movement-commands-for-macro
        as shift-key = (build-ab-symbol-no-hyphens 'shift+ key)
        as shift-command = (build-ab-symbol command 'extending-region)
        as binding = (list shift-key shift-command)
        as def = `(define-editor-ui-command ,shift-command ()
                    (let ((shift-variant-for-cursor-movement-p t))
                      ;; all editor commands passing through same args:
                      (funcall-ui-command ',command event edit-state)))
        collect binding into bindings
        collect def into defs
        finally
          ;; remove duplicate shift commands (many:1 bindings ok):
          (setq defs
                (remove-duplicates
                  defs
                  :test #'(lambda (adef bdef)
                            (eq (second adef) (second bdef)))))
          ;; generate and return the defs and the keymap
          (return
            `(progn
               (define-keymap cursor-movement-shift-variant-commands
                   (:private t)
                 . ,bindings)
               . ,defs))))

(define-shift-variants-of-cursor-movement-commands)



;;; `Move-cursor-handling-shift-variant' is the bottleneck for all cursor movement
;;; operations because it handles the variants of the cursor movement commands that
;;; are done with the Shift key held down.  This variation involves extending a text
;;; region while moving the cursor.

;;; This uses shift-variant-for-cursor-movement-p to if the shift variant is needed.
;;; When shift-variant-for-cursor-movement-p is true, and a text region already
;;; exists, this changes the free end of the region to be where the cursor is.  If
;;; the region ends up empty, the region is deselected and deleted.

;;; Single-char-movement-direction?  should be either FORWARD or BACKWARD for a
;;; forward or backward single-character movement, i.e., right-arrow and
;;; left-arrow.  Otherwise, it should be nil.  When it's non-nil, and
;;; shift-variant-for-cursor-movement-p is nil, and there's currently a selected
;;; text region, then the first three args are ignored, and this determines the
;;; position of the appropriate end of the text region, and moves the cursor
;;; there after deleting the current text region.

(defun move-cursor-handling-shift-variant
    (text-tail? line-index? character-index?
                x-in-workspace? y-in-workspace?
                single-char-movement-direction?)
  (multiple-value-setq (text-tail? line-index? character-index?)
    (set-up-args-for-move-cursor-handling-shift-variant
      text-tail? line-index? character-index?
      x-in-workspace? y-in-workspace?))
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (cond
      (text-region?
       (cond
         (shift-variant-for-cursor-movement-p
          (when line-index?
            (update-text-region text-region? line-index? character-index?)
            (when (empty-text-region-p text-region?)
              ;; Don't kill empty text regions: Why?  The user may be in the
              ;; midst of crossing the free end over to the other side of the
              ;; fixed end, and the free end of the text region is not
              ;; necessarily where the cursor is.  If we deleted the region in
              ;; this case, then after the free end touches the fixed end, the
              ;; next move (shift-left-arrow, say) would start a new region from
              ;; the explicit cursor position.  Not the right thing.
              nil)
            (update-edit-operation-subcommands-in-current-editor)))
         (t
          (when single-char-movement-direction?
            ;; note: args may change here!
            (setq text-tail? nil)
            (cond
              ((eq single-char-movement-direction? 'backward)
               (setq line-index? (backward-line-index-of-text-region text-region?))
               (setq character-index?
                     (backward-character-index-of-text-region text-region?)))
              (t
               (setq line-index? (forward-line-index-of-text-region text-region?))
               (setq character-index?
                     (forward-character-index-of-text-region text-region?)))))
          (deselect-current-text-region text-region?))))
      ((and line-index?
            shift-variant-for-cursor-movement-p)
       (select-current-text-region
         (make-text-region
           (edit-box current-edit-state) nil
           (cursor-line-index current-edit-state)
           (cursor-character-index current-edit-state)
           line-index? character-index?))))
    (unless shift-variant-for-cursor-movement-p
      (when line-index?
        (change-edit-box text-tail? line-index? character-index?)))))



(defun set-up-args-for-move-cursor-handling-shift-variant
    (text-tail? line-index? character-index?
                x-in-workspace? y-in-workspace?)
  (when x-in-workspace?
    ;; Same code essentially as used in change-edit-box:
    (multiple-value-setq (line-index? character-index? text-tail?
                                      x-in-workspace? y-in-workspace?)
      ;; assumed: can't fail to set line-index?, etc., non-nil:
      (find-position-in-text
        (edit-box current-edit-state) nil nil nil t
        x-in-workspace? y-in-workspace?
        nil nil nil)))
  (values text-tail? line-index? character-index?))



;;; `Get-selected-edit-cursor-line-index' and
;;; `get-selected-edit-cursor-character-index' best determine the "selected
;;; cursor" position.  This is more complicated currently than it's been in past
;;; versions of G2 because we've partially adopted the policy of many modern
;;; text editing systems that the text region _is_ the cursor position, but at
;;; the same time not gone completely over to having a text region around all of
;;; the time, i.e., when there's no (visible) selected text region.
;;; Furthermore, the explicit text cursor may not be in the same part of the
;;; text as the text region. There may be considered in fact to be a
;;; discontiguous selection, at least from the point of view of a modern text
;;; editing environment.  Considering that most modern text editing systems do
;;; not permit discontiguous text selection, our approach is pretty complicated.
;;; However, customers have traditionally enjoyed the ability to use move,
;;; insert, and cut-and-insert, so we'll stick with our approach, if only to
;;; please such customers.
;;;
;;; Here's what we do.  If there's no selected text region, then the position is
;;; just that of the cursor. If there's a selected text region, the the position
;;; is that of the free end of the text region.

(defun-simple get-selected-edit-cursor-line-index ()
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (if text-region?
        (line-index-for-free-end-of-text-region text-region?)
        (cursor-line-index current-edit-state))))

(defun-simple get-selected-edit-cursor-character-index ()
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (if text-region?
        (character-index-for-free-end-of-text-region text-region?)
        (cursor-character-index current-edit-state))))




;;;; Selected Regions in the Editor



;;; `Select-text-region' should be called after creating a new text region.
;;; `Deselect-text-region' should be called in order to delete a
;;; text-region-to-delete?, if it's non-nil, and just to note that it's been
;;; deleted (or is about to be) if it's nil.

(defun select-current-text-region (text-region)
  (setf (text-region-of-edit-state? current-edit-state) text-region)
  (update-edit-operation-subcommands-in-current-editor))


(defun deselect-current-text-region (text-region-to-delete?)
  (setf (text-region-of-edit-state? current-edit-state) nil)
  (when text-region-to-delete? (delete-frame text-region-to-delete?))
  (update-edit-operation-subcommands-in-current-editor))





;;;; Source Text



;;; `Reduce-noting-source-position' is a phrase (grammar) transformation
;;; function.  Its single argument is a phrase, and its result a new phrase
;;; whose format is
;;;
;;;    (SOURCE-POSITION phrase encoded-current-source-position)
;;;
;;; where encoded-current-source-position is a "source position" (defined
;;; below) at the end of this phrase.

;;; `Encode-current-source-position' returns the source position of the
;;; end of the token being added to the parse.  A `source position' is
;;; encoded into a fixnum if possible.  Otherwise it is a phrase-cons.
;;; Encoded source positions are not self-typing.

;;; `Current-line-index-for-end-of-token' and `current-character-index-
;;; after-token?' are used to communicate to the parsing transformation
;;; operation the current source position.

;;; `Text-string-from-current-source' will snarf from the editor's internal
;;; state a text string which represents a range in the source.  It takes two
;;; arguments that indicate the start and end of the range to return.  Either
;;; argument may be either an encoded source position or a NIL.  NIL implies
;;; you want one or the other end of the current source.

(defvar-of-named-dynamic-extent current-line-index-for-end-of-token editing-context)

(defvar-of-named-dynamic-extent current-character-index-after-token editing-context)

(defun encode-current-source-position ()
  (let ((line-index current-line-index-for-end-of-token)
        (character-index current-character-index-after-token))
    (if (and (<f line-index 1024)
             (<f character-index 256))
        (+f (ashf line-index 8) character-index)
        (phrase-cons line-index character-index))))

(defun line-index-of-source-position (source-position)
  (if (consp source-position)
      (car source-position)
      (ashf source-position -8)))

(defun character-index-of-source-position (source-position)
  (if (consp source-position)
      (cdr source-position)
      (logandf #xFF source-position)))

(defun text-string-from-current-source (start-source-position? end-source-position?)
  (let (start-line-index?
        start-character-index?
        end-line-index?
        end-character-index?)
    (when start-source-position?
      (setf start-line-index? (line-index-of-source-position start-source-position?))
      (setf start-character-index? (character-index-of-source-position start-source-position?)))
    (when end-source-position?
      (setf end-line-index? (line-index-of-source-position end-source-position?))
      (setf end-character-index? (character-index-of-source-position end-source-position?)))
    (convert-text-to-text-string
      (text-being-edited current-edit-state)
      nil
      start-line-index? start-character-index?
      end-line-index? end-character-index?
      t)))

(defun reduce-noting-source-position (parse)
  (phrase-cons
    'source-position
    (phrase-cons
      parse
      (encode-current-source-position))))





;;;; Parse Hook (Development Function)



;;; In development, `parse-hook?' is either nil or a function to be called
;;; with one argument, a list of the form ( { (type-of-token token) } ), when
;;; editing is about to be completed.

;;; `PH' is a test parse-hook function, available in development, which just
;;; prints out the contents of its argument.  Try it by doing (setq parse-hook?
;;; 'ph).  Turn off its effects by doing (setq parse-hook? nil).

#+development
(defvar parse-hook? nil)

#+development
(defun ph (x)
  (format t "~%---------------------------------------------~%")
  (loop for (type-of-token token) on x by 'cddr
        do (format t "~%Type of token: ~(~a~); Token: ~a" type-of-token token))
;  (terminal-pause 3)
  )

;; Try this with
;;     (setq parse-hook? 'ph)
;; (MHD 5/7/91)


#+development
(defun call-parse-hook-if-appropriate (try-to-end-editing?)
  (when (and try-to-end-editing? parse-hook?)
    (let ((gensym-list-of-tokens-and-their-types
           (loop with result = nil
                 for token
                     in (stack-of-tokens current-edit-state)
                 as type-of-token
                    in (stack-of-types-of-tokens current-edit-state)
                 do (setq result (gensym-cons token result))        ; reversing
                    (setq result (gensym-cons type-of-token result))
                 finally (return result))))
      (funcall parse-hook? gensym-list-of-tokens-and-their-types)
      (reclaim-gensym-list gensym-list-of-tokens-and-their-types))))





;;;; Barriers on Destabilization via Editing



(defun put-barrier-on-destabilization-via-editing (frame slot-description)
  (when (restrict-destabilization-p frame slot-description)
    (unless (or in-recompile-item-p        ; as though confirmed
                keep-edit-workspace-hidden-no-matter-what?)
      (enter-dialog
        (tformat-text-string
          "Edit this item?  (It is in ~
             a part of the KB ~
             declared as stable. This edit could cause dependent ~
             parts of the KB to become incomplete, and to ~
             require recompilation.)")
        nil nil
        'allow-continuation-of-editing-context-upon-confirmation nil
        'exit-editing-context-upon-denial-of-confirmation nil
        nil nil))))



;;; `Exit-editing-context-upon-denial-of-confirmation' is a function to be
;;; called within the editor context upon cancelation of the confirmation
;;; dialog that would otherwise have allowed editing to continue, possibly
;;; destabilizating the KB.  It simply exits the current (editing) workstation
;;; context.
;;;
;;; `Allow-continuation-of-editing-context-upon-confirmation' is called if the
;;; user says OK to the same confirmation dialog.  It simply allows editing to
;;; proceed, i.e., does nothing.

(defun exit-editing-context-upon-denial-of-confirmation ()
  (return-from-current-workstation-context 'editing))


(defun allow-continuation-of-editing-context-upon-confirmation ()
  )

;; Note that this might not always have nothing to do.  Conceivably this could
;; handle giving focus back to the editor -- and visual indications thereof,
;; e.g., drawing of the cursor/blinker, but that is not part of the current
;; design. (MHD 5/31/94)



;;; `Recording-items-made-incomplete' ... Operation should be one of EDIT,
;;; TRANSFER, or DELETE.

(defvar recording-items-made-incomplete? nil)
(defvar items-made-incomplete-were-recorded?)
(defvar operation-around-record-of-items-made-incomplete)
(defvar items-made-incomplete nil)

(defun-void reclaim-items-made-incomplete-list ()
  (reclaim-item-and-fsn-list items-made-incomplete)
  (setq items-made-incomplete nil))

(defmacro recording-items-made-incomplete ((operation) &body body)
  `(let* ((operation-around-record-of-items-made-incomplete ,operation)
          (recording-items-made-incomplete?
            (case operation-around-record-of-items-made-incomplete
              (edit (not (editing-for-runtime-change? current-edit-state)))
              (t t)))
          (items-made-incomplete-were-recorded? nil))
     (reclaim-items-made-incomplete-list) ; for wrap-up-transfer-after-drag-1
     (prog1 (progn ,@body)
       (reclaim-items-made-incomplete-list))))



;;; `Record-item-made-incomplete-if-appropriate' is to be called any time an
;;; item is made incomplete as a side effect of destabilization, e.g., during
;;; compilation.  It is safe to call at any time, since it can tell itself if it
;;; is in a context in which such decompletion is being recorded.

(defun record-item-made-incomplete-if-appropriate (item)
  (when recording-items-made-incomplete?
    (setq items-made-incomplete-were-recorded? t)
    (gensym-push (gensym-cons item (copy-frame-serial-number (frame-serial-number item)))
                 items-made-incomplete)))



;;; `record-items-made-incomplete-and-delete' is a function used in the action
;;; method interface for delete to implement one part of the default delete behavior.
;;; Defining this function is a better idea than moving back the definition
;;; of the macro `record-items-made-incomplete' to the methods module.

(defun record-items-made-incomplete-and-delete (item-to-delete g2-window?)
  (recording-items-made-incomplete ('delete)
    (delete-item item-to-delete)
    (let ((workstation?
            (workstation-for-g2-window?
              g2-window?)))
      (when workstation?
        (for-workstation (workstation?)
          (offer-to-recompile-items-made-incomplete-if-appropriate))))))



;;; `Make-description-of-barrier-to-destabilization' ...

(defun make-description-of-barrier-to-destabilization ()
  (tformat-text-string
    "~A a part of the KB declared as stable or dependent, which has caused ~
      dependent parts of the KB to become incomplete, and to require ~
      recompilation."
    (case operation-around-record-of-items-made-incomplete
      (transfer "A transfer was made in")
      (edit "An edit was made to")
      (choose-existing-class "A new superior class was chosen for")
      (delete "Deleting"))))




;;; `Offer-to-recompile-items-made-incomplete-if-appropriate' ... If this is called
;;; from the editor when
;;;
;;;    (1) servicing-workstation? is true;
;;;    (2) recording-items-made-incomplete? is true; and
;;;    (3) items-made-incomplete-were-recorded? is true
;;;
;;; then this allows the user (in the current workstation) to choose to launch a
;;; recompile of the entire KB, providing appropriate explanatory text.
;;;
;;; This is called after parsing, compiling, changing the slot at the end of an
;;; edit session.  This may be called within an edit context, or just after an
;;; edit context has been exited.
;;;
;;; If it decides to offer to recompile, it returns true; otherwise, nil.

(defun offer-to-recompile-items-made-incomplete-if-appropriate ()
  (when (and recording-items-made-incomplete?
             items-made-incomplete-were-recorded?)
    (setq items-made-incomplete-were-recorded? nil)
    (offer-to-recompile-now-after-edit)
    t))


(defun offer-to-recompile-now-after-edit ()
  (unless (or in-recompile-item-p
              keep-edit-workspace-hidden-no-matter-what?)
    (let ((inner-text-string (make-description-of-barrier-to-destabilization)))
      (enter-dialog
        (tformat-text-string "Recompile the KB?  (~A)" inner-text-string)
        nil nil
        'launch-compile-to-bring-kb-up-to-date ; OK case
        (slot-value-list inner-text-string)
        'allow-continuation-of-editing-context-upon-confirmation ; cancelled
        nil))))



;;; `Delete-frame-after-checking-serial-number' is to be called from
;;; user-interface code to delete an item after confirmation.  [This has been
;;; moved to this module, EDIT, from FACILITIES, just in order to be able to use
;;; the macro recording-items-made-incomplete. (MHD 6/2/94)]

;;; `Delete-frame-after-checking-serial-number-with-list' is similar but takes
;;; an unshared gensym list of the form
;;;
;;;   (frame reference-serial-number)
;;;
;;; where frame-serial-number is a an unshared copy of a frame reference serial
;;; number valid for frame.  It deletes the frame if its valid per the
;;; reference, then reclaims the reference serial number, and finally reclaims
;;; the gensym conses of the list.

(defun delete-frame-after-checking-serial-number (frame reference-serial-number)
  (unless (frame-has-been-reprocessed-p frame reference-serial-number)
    (recording-items-made-incomplete ('delete)
      (delete-frame frame)
      (offer-to-recompile-items-made-incomplete-if-appropriate))))

(defun delete-frame-after-checking-serial-number-with-list
    (gensym-listed-frame-and-reference-serial-number-copy)
  (let* ((frame (first gensym-listed-frame-and-reference-serial-number-copy))
         (reference-serial-number
           (second gensym-listed-frame-and-reference-serial-number-copy)))
    (delete-frame-after-checking-serial-number frame reference-serial-number)
    (reclaim-frame-serial-number reference-serial-number)
    (reclaim-gensym-list gensym-listed-frame-and-reference-serial-number-copy)))





;;;; Editor Parsing



;;; Finish-parsing-insofar-as-possible extends parsing as far as it can go (in
;;; END mode), without suspension, in the current workstation context, which is
;;; assumed to be an editing context.  If parsing succeeds, the current editing
;;; context will be exited normally and the value will be true.  If parsing fails,
;;; nil will be returned and the edit workspace will be revealed if it is hidden.

;;; Since parsing will not be suspended by reason of time expiration or a
;;; pending workstation event, this should not be called while the system is
;;; running.

(defun finish-parsing-insofar-as-possible ()
  (in-editing-context (specific-structure-for-current-workstation-context)
    (let* ((edit-workspace current-edit-workspace)
           (frame-serial-number-for-edit-workspace
             (copy-frame-serial-number (frame-serial-number edit-workspace)))
           result)
      (extend-parsing-as-appropriate 'end t)
      (setq result
            (frame-has-been-reprocessed-p
              edit-workspace frame-serial-number-for-edit-workspace))
      (reclaim-frame-serial-number frame-serial-number-for-edit-workspace)
      result)))

;; This parses without suspension for the sake of the "recompile all rules" main
;; menu (miscellany) command.  Such parsing without suspension would not be
;; necessary if either (a) an editing context was moved to the bottom of a
;; series of stacked up editing contexts when its edit workspace is revealed or
;; (b) extend-parsing-as-appropriate could go on to the next rule after parsing
;; had gone as far as possible.



;;; Extend-parsing-or-exit-editor-as-appropriate either: (1) exits the current
;;; (editing) context, if the edit workspace has been deleted; (2) extends
;;; parsing as appropriate, within an editing context, if the
;;; parsing-extension-mode? slot of the edit state is non-nil and the edit box
;;; has no text regions other than the kfep conversion text region, if any;
;;; or (3) returns nil (in contrast to the other two cases which return t).
;;; (The reason for not parsing when there are text regions other than the kfep
;;; conversion text region is that such text regions would be unexpectedly
;;; deleted, instead of being properly updated, in the case of ellipsis
;;; insertion.)

(defun-simple extend-parsing-or-exit-editor-as-appropriate ()
  (in-editing-context (specific-structure-for-current-workstation-context)
    (cond
      ((not (valid-block-in-workstation-context-p (edit-workspace current-edit-state)
                                                  current-edit-state))
       (abort-current-workstation-context 'editing)
       t)
      ((and (parsing-extension-mode? current-edit-state)
            (not (has-text-regions-p
                   (edit-box current-edit-state)
                   (kfep-conversion-text-region? current-edit-state))))
       (extend-parsing-as-appropriate (parsing-extension-mode? current-edit-state))
       t))))

;; Consider having the two tests occur outside of the in-editing-context call,
;; to gain a bit of speed.

;; This is used only by service-workstations in module WORKSTATION.



;;; `terminate-comment-notification-string' - returns the proper
;;; string to notify the user of how to end the comment, given
;;; the depth of the nesting of commenting

(defmacro terminate-comment-notification-string (token-type-or-partial-types)
  (avoiding-variable-capture (&aux text-type-p)
    `(let ((,text-type-p
              (text-slot-type-p
                (type-of-slot-being-edited current-edit-state))))
       (cond
         #+java-export-facilities
         ((and ,text-type-p
               (java-editing-category-p
                 (cadr (type-of-slot-being-edited current-edit-state))))
          "within a Java comment")
         ((eq ,token-type-or-partial-types 'single-line-comment)
          (cond
            ((or (scrolling-editor-p current-edit-state)
                 (native-editor-workspace-p current-edit-workspace))
             "Hit enter to terminate comment.")
            (t
             "Hit Control+J to terminate comment.")))
         (t
          (cond
            (,text-type-p "Use } to terminate comment.")
            (t ,(format nil
                        "Use } to terminate comment.  ~
                         NOTE: This comment will not be preserved!"))))))))




;;; Extend-parsing-as-appropriate ...  Parsing-extension-mode may be T, END, or
;;; NO-AUTOCOMPLETION.

;;; If do-not-suspend? is non-nil, parsing will not be suspended by reason of
;;; time expiration or a pending workstation event.  Thus it should be specified
;;; only if the system is not running.

;;; If parsing fails when parsing-extension-mode is END and the edit workspace
;;; is hidden, the edit workspace will be revealed.

;;; Extend-parsing-as-appropriate puts up menus (or autocompletes) as appropriate,
;;; conceptually "in parallel".  This "other" process delays putting menus up if
;;; user input is pending.  Thus it avoids putting menus up while the user is typing
;;; (fast).  This means that (a) it might avoid putting up the wrong menu (that is,
;;; if the what the user types makes the current menus invalid); (b) it might avoid
;;; putting up multiple wrong menus (if it really falls behind); and (c) even if it
;;; turns out it could have put up the right menu, it is still right that it waited
;;; on that because it is more important to update the edit box in good time than the
;;; menus.  Updating the edit box thus appears to have higher priority, which it
;;; should.

;;; If parsing-extension-mode is END, then if just-update? is true, the frame
;;; being edited can be updated, but the edit context cannot be exited, even if
;;; the parsing and compiling is successful.

(defun extend-parsing-as-appropriate
    (parsing-extension-mode &optional do-not-suspend? just-update? change-text?
                            &aux (parsed-successfully? t))
  (setf (parsing-extension-mode? current-edit-state) nil)
  (if (free-text-slot-being-edited? current-edit-state)
      (if (eq parsing-extension-mode 'end)        ; bind variable earlier?
          (let ((kb-serial-number current-kb-serial-number))
            (when (or (null (frame-being-edited? current-edit-state))
                      (null (funcall-method-if-any
                              'handle-end-operation (frame-being-edited? current-edit-state)
                              current-workstation-context)))
              (cond
                ((not (edit-context-remains-valid-p kb-serial-number))
                 nil)                        ; bail out asap; see (MHD 4/26/94)
                                        ;   comment below.
                (t
                 (setq parsed-successfully? (try-to-end-editing just-update?))))))
          (erase-any-temporary-information-on-edit-workspace nil))
      (with-current-grammar-for-current-edit-state
        (loop with try-to-end-editing? = (eq parsing-extension-mode 'end)
              with token-value
              with token-type-or-partial-types
              with current-line-index-for-end-of-token
              with current-character-index-after-token
              with text-tail-for-end-of-token?
              with token-self-terminating?
              with starting-time = 0                ; later, a real time!
              with incomplete-phrases-after-token
              do (multiple-value-setq (token-value
                                        token-type-or-partial-types
                                        current-line-index-for-end-of-token
                                        current-character-index-after-token
                                        text-tail-for-end-of-token?
                                        token-self-terminating?)
                   (get-next-token-if-available
                     (if (not try-to-end-editing?)
                         (cursor-line-index current-edit-state))
                     (if (not try-to-end-editing?)
                         (cursor-character-index current-edit-state))))
                 (when (or (null token-type-or-partial-types)
                           (not (symbolp token-type-or-partial-types)))
                   (loop-finish))                ; if no token available

                 (procedure-signature-token-hook token-value)

                 (setq incomplete-phrases-after-token
                       (advance-parsing-for-token
                         token-value
                         token-type-or-partial-types
                         (first (stack-of-incomplete-phrases-at-earlier-positions
                                  current-edit-state))))
                 (when (null incomplete-phrases-after-token)
                   (loop-finish))
                 (erase-any-temporary-information-on-edit-workspace nil)
                 (push-for-token
                   current-line-index-for-end-of-token
                   current-character-index-after-token
                   token-self-terminating?
                   text-tail-for-end-of-token?
                   incomplete-phrases-after-token
                   token-value
                   token-type-or-partial-types)

                 ;; suspend on time or workstation events:
                 (when (and (or (>=f (incff starting-time) 5)        ; small number, or a time!
                                (and (not try-to-end-editing?)
                                     (current-workstation-has-pending-events-p)))
                            (not do-not-suspend?))
                   (setf (parsing-extension-mode? current-edit-state)
                         parsing-extension-mode)
                   (return nil))
              finally                                ; stop parsing
                #+development
                (call-parse-hook-if-appropriate try-to-end-editing?)
                (cond
                  ((and (or (null token-type-or-partial-types)
                            (and (eq token-type-or-partial-types 'single-line-comment)
                                 (eq parsing-extension-mode 'end)))
                        (null token-value))
                   ;; hit cursor or end-of-text
                   (let* ((kb-serial-number current-kb-serial-number)
                          (result-of-custom-handling? ; nil <=>  end editor
                            (if (and try-to-end-editing?
                                     (frame-being-edited? current-edit-state))
                                (funcall-method-if-any ; specified in KB-LOAD1 at present
                                  'handle-end-operation ; (MHD 4/18/94)
                                  (frame-being-edited? current-edit-state)
                                  current-workstation-context)
                                nil)))
                     (cond
                       ((not (edit-context-remains-valid-p kb-serial-number))

                      ;; The handle-end-operation could have deleted the current
                      ;; KB, or the frame being edited; if so, all workstation
                      ;; contexts should have been aborted by now (i.e., by
                      ;; clear-kb), so our job is just to unwind the Lisp stack
                      ;; to the point where there's no code running that assumes
                      ;; it's running in a particular workstation context.  If
                      ;; it's just the frame being edited that's deleted, things
                      ;; should work out ok, too.  Note that we "know" that
                      ;; we are called from a shallow depth in the Lisp stack,
                      ;; that no callers will to other silly things with the
                      ;; the editing context after this function returns.  It's
                      ;; a little kludgy.  What seems needed is a throw to
                      ;; a catch established by the workstation servicing code
                      ;; or at least by the event handler of this context.
                      ;;
                      ;; In addition, the end operation is free to explicitly
                      ;; return from, or abort, the editing context, which this
                      ;; must (and does) handle as well.
                      ;;
                      ;; (MHD 4/26/94)
                      (return nil))        ; return out of the function (throw to
                                        ;   workstation event handler?!)
                     ((and try-to-end-editing?
                           (null result-of-custom-handling?))
                      (setq parsed-successfully? (try-to-end-editing just-update?)))
                     ((eq result-of-custom-handling? :display-notification)
                      nil)
                     (t
                      (update-edit-menus-or-autocomplete-as-appropriate
                          nil nil parsing-extension-mode)))))
                  (t (enable-or-disable-edit-end-and-update-buttons t)
		     (when (and token-type-or-partial-types change-text?
                                (not (memq token-type-or-partial-types
					   '(quoted-character comment single-line-comment)))
				(not (symbolp token-type-or-partial-types)))
                       (setf (line-index-of-repair-for-bad-parse? current-edit-state)
	                     current-line-index-for-end-of-token)
		       (setf (character-index-of-repair-for-bad-parse? current-edit-state) 
	                     current-character-index-after-token))
                     (cond
                       ((or (and (null token-type-or-partial-types)
                                 (text-string-p token-value))
                            (and token-type-or-partial-types
                                 (symbolp token-type-or-partial-types)
                                 (not (memq token-type-or-partial-types
                                            '(quoted-character comment single-line-comment))))
                            (and (consp token-type-or-partial-types)
                                 (eq (car-of-cons token-type-or-partial-types)
                                     'illegal-character)))
                        (erase-any-temporary-information-on-edit-workspace nil)        ; ok?
                        (cond
                          ((and try-to-end-editing? (edit-redo-stack current-edit-state))
			   #-SymScale
                           (reclaim-edit-undo-or-redo-stack
                             (edit-redo-stack current-edit-state))
			   #-SymScale
                           (setf (edit-redo-stack current-edit-state) nil)
			   #+SymScale
			   (reclaim-edit-undo-or-redo-stack
			     (atomic-exchange (edit-redo-stack current-edit-state) nil))))
			(let ((line-index current-line-index-for-end-of-token)
			      (character-index current-character-index-after-token))
			  (when (and line-index character-index)
			    (insert-ellipsis-as-appropriate line-index character-index)))
                        (let ((problem-string
                                (copy-text-string
                                  (if (problem-string-of-most-recent-reason-for-bad-parse?
                                        current-edit-state)
                                      (reason-for-bad-parse-as-string
                                        (problem-string-of-most-recent-reason-for-bad-parse?
                                          current-edit-state))
                                      "This cannot be parsed"))))
;                              (tformat-text-string
;                                (cond
;                                  ((text-string-p token-or-other-type-of-result?)
;                                   "~A ~A is syntactically illegal")
;                                  ((memq token-or-other-type-of-result?        ; a bit heuristic
;                                         '(seconds minutes hours days weeks)) ; singulars also?
;                                   "~A it contains too large a time interval")
;                                  ((and (symbolp token-or-other-type-of-result?)  ; a bit heuristic
;                                        (reserved-word-p token-or-other-type-of-result?))
;                                   "~A it contains the reserved  word \"~(~A~)\" out-of-context")
;                                  (t                ; improve specificity! always a number?
;                                   "~A \"~A\" is out-of-context"))
;                                "This is unparsable because"
;                                token-or-other-type-of-result?)
                          (handle-parsing-or-compilation-problem
                            problem-string
                            current-line-index-for-end-of-token
                            current-character-index-after-token)
			  (setq parsed-successfully? nil)
                          (reclaim-text-string problem-string)
                          (if try-to-end-editing?
                              (maybe-offer-to-save-incomplete-statement))))
                       ((equal token-type-or-partial-types
                               '(bad-java-character-literal))
                        (insert-ellipsis-as-appropriate
                          current-line-index-for-end-of-token
                          current-character-index-after-token)
                        (unless (eq (temporary-information-on-edit-workspace?
                                      current-edit-state)
                                    'editor-notification)
                          ;; do always or only if this particular notification?
                          (display-editor-notification
                            "This does not form a valid character literal in Java")))
                       ((text-string-p token-value)        ; incomplete token case
                        (cond
                          (try-to-end-editing?
                           (home-down-cursor)
                           (handle-parsing-or-compilation-problem
                             "This is incomplete"
                             current-line-index-for-end-of-token
                             current-character-index-after-token)
                           (maybe-offer-to-save-incomplete-statement))
                          ;; jh, 7/27/97.  Currently happens only in Java
                          ;; tokenizer (see JAVA2), but could happen in any
                          ;; language whose initial comment character is also
                          ;; the beginning of some operator, C for example.
                          ;;
                          ;; jv, 10/17/05: we have now added such a comment syntax to
                          ;; G2; "//" begins a single line comment, and, of course,
                          ;; both "/" and "/=" are operators in G2.
                          ;;
                          ;; jv, 7/13/07: but why did we just clear the "temporary
                          ;; information", which includes the prompts?  Update the
                          ;; menus as we would otherwise.
                          ((and (consp token-type-or-partial-types)
                                (or (memq 'comment token-type-or-partial-types)
                                    (memq 'single-line-comment token-type-or-partial-types)))
                           (update-edit-menus-or-autocomplete-as-appropriate
                             token-type-or-partial-types
                             token-value
                             parsing-extension-mode))
                          ((and (null (update-edit-menus-or-autocomplete-as-appropriate
                                        token-type-or-partial-types
                                        token-value
                                        parsing-extension-mode))
                                (or (null (kfep-conversion-text-region? current-edit-state))
                                    (let ((text-region (kfep-conversion-text-region?
                                                         current-edit-state)))
                                      (or (<f current-line-index-for-end-of-token
                                              (line-index-for-fixed-end-of-text-region
                                                text-region))
                                          (and (=f current-line-index-for-end-of-token
                                                   (line-index-for-fixed-end-of-text-region
                                                     text-region))
                                               (<f current-character-index-after-token
                                                   (character-index-for-fixed-end-of-text-region
                                                     text-region)))))))
                           ;; Insert an ellipsis if there are no menu choices, unless there
                           ;; is a kfep conversion text region and the incomplete token
                           ;; extends up to or beyond its beginning.
                           (insert-ellipsis-as-appropriate
                             current-line-index-for-end-of-token
                             current-character-index-after-token t)))
                        (reclaim-text-string token-value))

                        ;; within a comment
                       ((memq token-type-or-partial-types '(comment single-line-comment))
                        (unless (eq (temporary-information-on-edit-workspace? current-edit-state)
                                    'editor-notification)
                          ;; do always or only if this particular notification?
                          (display-editor-notification
                            (terminate-comment-notification-string
                              token-type-or-partial-types))))
                       ((eq token-type-or-partial-types 'quoted-character); Added. (MHD 10/3/90)
                                        ; @ at end of text, token type unknown
                        (when try-to-end-editing?
                          (handle-parsing-or-compilation-problem
                            "This is missing a character after @"
                            current-line-index-for-end-of-token
                            current-character-index-after-token)))
                       ((eq token-type-or-partial-types 'ellipsis)        ; hit an ellipsis
                        (erase-any-temporary-information-on-edit-workspace nil)        ; ok?
                        ;; move cursor to ellipsis?
                        (when try-to-end-editing?

                          ;; Highlight occurrencences of the ellipsis string;
                          ;; these will go away upon changes to the text, which
                          ;; is intended as a feature here because it will seem
                          ;; natural, as though the highlighting is only
                          ;; temporary.  (MHD 5/1/91)
                          (mark-occurrences-of-string-in-text
                            (edit-box current-edit-state) nil
                            ellipsis-text-string
                            nil)

                          ;; bind count returned by the above for following error
                          ;; message?

                          (handle-parsing-or-compilation-problem
                            "This contains an ellipsis"
                            current-line-index-for-end-of-token
                            current-character-index-after-token)

                          (maybe-offer-to-save-incomplete-statement)))))))))
						  
	parsed-successfully?)

;; Consider computing the reason why a token is not accepted, instead of using
;; heuristics to produce the messages "Too long an interval", "Reserved word ..
;; ", etc.

;; Reclaim unused number, string, and symbol tokens, some day!

;; Consider adding an option to
;; make-menu-content-structure-for-character-position that tells it to return
;; just t or nil according to whether there would be any menus or not.  This
;; would save a bit of time (but only in an error case).


#+development
(defvar *print-parsing-for-token?* nil)

;;; `Advance-parsing-for-token' ...

(defun advance-parsing-for-token (token type-of-token incomplete-phrases-for-token)
  (let* ((incomplete-phrases-at-frontier nil)
         (specific-category-for-token? (get-category-of-token token))
         (general-category-for-token?
          (get-category-for-category-symbol-if-any type-of-token)))
    #+development
    (when *print-parsing-for-token?*                                ; for debugging
      (print-possible-categories))
    #+development
    (when *print-parsing-for-token?*
      (print-current-parsing-goals))
    (when specific-category-for-token?
      (add-constituent-to-incomplete-phrases
        token specific-category-for-token?
        incomplete-phrases-for-token))
    (when general-category-for-token?
      (unless (and specific-category-for-token?
                   (subcategoryp
                     specific-category-for-token?
                     general-category-for-token?))
        (add-constituent-to-incomplete-phrases
          token
          general-category-for-token?
          incomplete-phrases-for-token)))
    (when (eq type-of-token 'symbol)
      (if (not (reserved-word-p token))
          (add-constituent-to-incomplete-phrases
            token
            (get-category-for-category-symbol-if-any 'unreserved-symbol)
            incomplete-phrases-for-token))
      (if (category-symbols-for-symbol-token token)
          (loop for category-symbol
                    in (category-symbols-for-symbol-token
                         token)
                do (add-constituent-to-incomplete-phrases
                     token
                     (get-or-make-category-for-category-symbol
                       ;; no longer assume, so don't call this:
                       ;;   get-category-for-category-symbol-if-any  ; assumed there
                       ;; the use of subgrammars now makes this unsafe (MHD 1/18/93)
                       category-symbol)
                     incomplete-phrases-for-token))))
    #+development
    (when *print-parsing-for-token?*
      (print-parsing-goals incomplete-phrases-at-frontier "After"))
    incomplete-phrases-at-frontier))



#+development
(defun print-possible-categories ()
  (format t
    "~2%Possible categories: ~A"
    (loop for incomplete-phrase
              in (car
                   (stack-of-incomplete-phrases-at-earlier-positions
                     current-edit-state))
          nconc
          (loop for phrase-rule-completion
                    in (phrase-rule-completions incomplete-phrase)
                collect
                (category-symbol
                  (category-for-completed-phrase
                    phrase-rule-completion))))))


#+development
(defun print-current-parsing-goals ()
  (loop for ip in (car (stack-of-incomplete-phrases-at-earlier-positions
                         current-edit-state))
        as i from 1
        do (format t "~2%Incomplete Phrase (~d): ~a"
                   i
                   (category-symbol
                     (category-for-completed-phrase
                       (first (phrase-rule-completions ip)))))
           (loop for prc in (phrase-rule-completions ip)
                 do (format t
                            "~%  ~a"
                            (category-symbol (category-of-next-constituent prc))))))

#+development
(defun print-parsing-goals (ip-list tag)
  (loop for ip in ip-list
        as i from 1
        do (format t "~2%~a Incomplete Phrase (~d): ~a"
                   tag
                   i
                   (category-symbol
                     (category-for-completed-phrase
                       (first (phrase-rule-completions ip)))))
           (loop for prc in (phrase-rule-completions ip)
                 do (format t
                            "~%  ~a"
                            (category-symbol (category-of-next-constituent prc))))))



;;; Insert-ellipsis-as-appropriate inserts an ellipsis into the current edit box,
;;; if and where appropriate.

;;; The position specified by character-index-for-end-of-prefix-token-string and
;;; character-index-for-end-of-prefix-token-string is the forwardmost position
;;; for possible ellipsis insertion (which should never be at the beginning of
;;; the kfep conversion text region, if any).  Insert-ellipsis-as-appropriate
;;; searches, starting there and backing up one character at a time, until a
;;; position is reached where a legal token is possible or until the beginning
;;; of the incomplete token is reached.  It then inserts an ellipsis there unless
;;; the cursor is exactly there or unless there is a non-empty edit redo stack
;;; in the current edit state.

(defun insert-ellipsis-as-appropriate
    (line-index-for-end-of-prefix-token-string
      character-index-for-end-of-prefix-token-string &optional note-syntax-error-p)
  (loop with token-value
        with token-type-or-partial-types
        with text-tail-for-end-of-prefix-token-string
          = (find-text-tail-for-line
              (text-being-edited current-edit-state)
              line-index-for-end-of-prefix-token-string)
        do
    (multiple-value-setq (token-value token-type-or-partial-types)
      (get-next-token-if-available
        line-index-for-end-of-prefix-token-string
        character-index-for-end-of-prefix-token-string))
        until
        (or (and (null token-type-or-partial-types)
                 (null token-value))
            (if (and (text-string-p token-value)
                     (consp token-type-or-partial-types))
                (let ((menu-content-structure-for-character-position
                        (make-menu-content-structure-for-character-position
                          (get-or-make-menu-content-structure-for-current-token-position)
                          token-type-or-partial-types
                          token-value)))
                  (prog1
                      (or (car menu-content-structure-for-character-position)
                          (cdr menu-content-structure-for-character-position))
                    (reclaim-menu-content-structure
                      menu-content-structure-for-character-position)
                    (reclaim-simple-text-string
                      token-value)))))
        do (multiple-value-setq (line-index-for-end-of-prefix-token-string  ; changes args
                                  character-index-for-end-of-prefix-token-string
                                  text-tail-for-end-of-prefix-token-string)
             (find-previous-character-if-any
               line-index-for-end-of-prefix-token-string
               character-index-for-end-of-prefix-token-string
               text-tail-for-end-of-prefix-token-string
               (text-being-edited current-edit-state)))
        finally
          (cond ((native-editor-workspace-p current-edit-workspace)
                 (when note-syntax-error-p
                   (setf (problem-string-of-first-reason-for-bad-parse? current-edit-state)
                         (copy-text-string #w"This cannot be parsed"))
                   (setf (line-index-of-first-reason-for-bad-parse? current-edit-state)
                         line-index-for-end-of-prefix-token-string)
                   (setf (character-index-of-first-reason-for-bad-parse? current-edit-state)
                         character-index-for-end-of-prefix-token-string)))

                ((and (=f line-index-for-end-of-prefix-token-string
                          (cursor-line-index current-edit-state))
                      (=f character-index-for-end-of-prefix-token-string
                          (cursor-character-index current-edit-state))))

                ((null (edit-redo-stack current-edit-state))
                 ;; notify user in this case?
                 (insert-text-string-in-text-being-edited
                   ellipsis-text-string
                   t nil
                   line-index-for-end-of-prefix-token-string
                   character-index-for-end-of-prefix-token-string
                   text-tail-for-end-of-prefix-token-string nil nil t 'automatic)))))




;;; The `handle-end-operation' for a frame is called after the user hits Return
;;; or clicks on END.  It is called with just the workstation context, from
;;; which can be gotten the edit state, etc.
;;;
;;; If the edit just to be an update, it must return true.  Otherwise, it must
;;; return nil, in which case try-to-end-editing will be called, the editor may
;;; be exited.  If it wants to display a notification, i.e., using
;;; display-editor-notification, it can return the special true value
;;; :DISPLAY-NOTIFICATION.  Then the menus will not be immediately displayed,
;;; but rather the notification presumably displayed will remain on the screen.
;;;
;;; Finally, this operation is free to delete block.  It may also abort, or
;;; return from, the editing context. In fact, it can even clear the entire KB.
;;; The editor is therefore prepared to reverify the existence of block (and the
;;; KB and editing context) before resuming operations.

(def-generic-method handle-end-operation (block workstation-context))



;;; The `add-items-to-edit-workspace' method for a block is called on the frame
;;; being edited to allow it to add subblocks to the edit workspace.  It is
;;; called right before the edit (parsing) menus have been added, but after the
;;; all of the permanent items have been added, i.e., the edit box and the
;;; subcommand menus.
;;;
;;; It can add items to the edit workspace, usually below the edit box.  If it
;;; needs to increase the distance between the bottom of the edit box and the
;;; edit menus, it can do so by setting the extra-space-to-leave-below-edit-box?
;;; slot of the current-edit-state structure.
;;;
;;; The first time this is called is when the editor is first fired up.  In this
;;; case, the arg refresh-case? is nil.  Upon this call the extra space parameter
;;; can be set.  In addition, it is ok to set other edit-state parameters that
;;; determine the behavior of the rest of the current editing session.
;;;
;;; At the same times at which the edit menus are subsequently updated, the
;;; method is again called, but with refresh-case? true.  The main
;;; responsibility of this method at this point is to move any items it added
;;; down or up in response to the lowering or raising of the bottom edge of the
;;; edit box.  Apart from that, it is up to the application to decide how to
;;; interpret refresh-case?, i.e., how to decide what does or doesn't need to be
;;; added.

(def-generic-method add-items-to-edit-workspace
    (kb-load-file-command edit-workspace edit-box refresh-case?))

;; The only implementor of both of the above two methods so far is the
;; handle-end-operation method for kb-load-file-command, in KB-LOAD1.  (MHD
;; 4/18/94)





;;; `Try-to-end-editing' ...

;;; If this fails when the edit workspace is hidden, the edit workspace is
;;; revealed.  If this does nothing because the frame to be edited has been
;;; deleted, it will nonetheless enter paste-text context if there is a cut-out
;;; text box.

;;; Just-update? means to update the frame being edited without exiting the
;;; editor.

;;; The frame being edited may be deleted if
;;;
;;;   (1) the text being edited is free text;
;;;   (2) the text is blank;
;;;   (3) just-update? is nil;
;;;   (4) the frame being edited is neither of class TYPE-IN-BOX
;;;       nor MESSAGE; and
;;;   (5) this is not a runtime change (i.e., an action)

;;; `text-of-definition-being-compiled' holds the
;;; (text-being-edited current-edit-state) it is needed in the
;;; add-md5-identifier function because (text-being-edited current-edit-state)
;;; gets shadowed between here and there

(defvar text-of-definition-being-compiled nil)

(defun try-to-end-editing (&optional just-update?)
  (cond
    ((or (null (frame-being-edited? current-edit-state))
         (frame-has-been-reprocessed-p
           (frame-being-edited? current-edit-state)
           (serial-number-of-frame-being-edited? current-edit-state)))
     (abort-current-workstation-context 'editing))
    ((or (attribute-being-edited-is-virtual? current-edit-state)
         (editing-using-exported-format? current-edit-state))
     (try-to-conclude-exported-attribute-for-current-edit-state just-update?))
    (t
     (let* ((parse-or-bad-phrase? (get-current-edit-state-parse-if-any))
            (parsing-completed? nil)) ;added by SoftServe
       (recording-items-made-incomplete ('edit)
         (with-locked-drawing ()                            ; Note A.
           (progn
             (let ((text-of-definition-being-compiled
                     (text-being-edited current-edit-state)))
               (multiple-value-bind
                   (new-value-or-bad-phrase
                     explanatory-text-string-if-bad-phrase?)
                 (compile-for-current-edit-state
                   parse-or-bad-phrase?
                   (get-slot-value-compiler-for-current-edit-state-if-any)
                   just-update?)
                 (cond
                   ((and (eq new-value-or-bad-phrase bad-phrase)
                         (not (text-being-edited-may-have-no-value-p)))
                    (handle-uncompilable-edit-state-result
                      ;; report only if not previously known bad:
                      (not (eq parse-or-bad-phrase? bad-phrase))
                      explanatory-text-string-if-bad-phrase?
                      t))
                   (t
                    (setq parsing-completed? t)
                    (install-current-edit-state-compiled-result
                      (if (or (eq new-value-or-bad-phrase bad-phrase)
                              (free-text-slot-being-edited? current-edit-state))
                        (if (text-slot-type-p
                              (type-of-slot-being-edited current-edit-state))
                          ;; type is, e.g., (type free text)
                          no-value
                          ;; type is, e.g., (type free-text-attribute)
                          (convert-text-to-text-string
                            (text-being-edited current-edit-state)))
                        (copy-for-slot-value new-value-or-bad-phrase))
                      just-update? nil))))))))
       parsing-completed?)))) ;return T on success - added by SoftServe

;; Note A: this is required to prevent the forcing of the drawing queues when logbook
;; messages are posted during compilation.  It fixes the bug HQ-127943
;; "Graphics turds with generic formula". -fmw, 1/9/95



(defun try-to-conclude-exported-attribute-for-current-edit-state (just-update?)
  (let* ((parse-or-bad-phrase? (get-current-edit-state-parse-if-any))
         (e current-edit-state)
         (frame (frame-being-edited? e))
         (name (name-of-slot-being-edited e))
         (virtual-attribute?
          (when (attribute-being-edited-is-virtual? e)
            (virtual-attribute name)))
         (type? (unless virtual-attribute?
                  (if (name-of-slot-component-being-edited? e)
                      (get-type-of-slot-component-if-any
                       (frame-being-edited? e)
                       (name-of-slot-being-edited e)
                       (defining-class-for-slot-being-edited? e)
                       (name-of-slot-component-being-edited? e)
                       (indicator-of-slot-component-being-edited? e))
                      (get-type-of-slot-if-any
                       (frame-being-edited? e)
                       (name-of-slot-being-edited e)
                       (defining-class-for-slot-being-edited? e)))))
         (category? (when type?
                      (category-symbol-given-slot-type type?)))
         (reason-not-editable?
          (reason-permanent-items-module-is-not-editable frame))
         (do-not-change-p
             (or (eq parse-or-bad-phrase? bad-phrase)
                 reason-not-editable?
                 (not (or (and virtual-attribute?
                               (virtual-attribute-setter? virtual-attribute?))
                          (and category?
                               (evaluation-value-to-category-function category?))))))
         (compiled-value
          (if do-not-change-p
              nil
              (compile-item-or-datum-or-no-item-attribute-for-slot
               parse-or-bad-phrase? frame nil nil)))
         (collecting-denotation-errors-p t)
         (denotation-error-list nil)
         (compiled-value-as-slot-value
          (copy-for-slot-value compiled-value))
         (evaluation-value
          (when (and compiled-value (null denotation-error-list))
            (get-evaluation-value-for-attribute compiled-value-as-slot-value nil)))
         (error-text?
          (unless (or do-not-change-p
                      denotation-error-list)
            (if virtual-attribute?
                (let ((error-string?
                       (conclude-into-virtual-attribute-component
                        frame name virtual-attribute? evaluation-value
                        nil nil)))
                  (unless error-string?
                    (reclaim-if-evaluation-value evaluation-value))
                  error-string?)
                (conclude-into-attribute-component
                 frame name nil
                 evaluation-value nil nil)))))
    (reclaim-slot-value compiled-value-as-slot-value)
    (when (and denotation-error-list (null error-text?))
      (let ((aliased-name (or (unless virtual-attribute?
                                (get-alias-for-slot-name-if-any
                                 name frame))
                              name)))
        (setq error-text?
              (twith-output-to-text-string
                (tformat "Unable to conclude the ~A because " aliased-name)
                (twrite-denotation-for-item (first denotation-error-list))
                (tformat " was not found.")))))
    (cond (error-text?
           (reclaim-if-evaluation-value evaluation-value))
          ((and (not do-not-change-p)
                (table-being-edited? current-edit-state)
                (frame-has-not-been-reprocessed-p
                 (table-being-edited? current-edit-state)
                 (frame-serial-number-of-table-being-edited? current-edit-state)))
           (update-all-representations-in-table
            (table-being-edited? current-edit-state)
            frame)))
    (if error-text?
        (handle-uncompilable-edit-state-result t error-text? nil)
        (if just-update?
            (enable-or-disable-edit-end-and-update-buttons nil)        ; just to unhighlight!
            (return-from-current-workstation-context 'editing)))))


(defparameter maximum-proglem-length-to-show-in-the-editor 300)

(defun handle-uncompilable-edit-state-result
    (report-problem-p explanatory-text-string? compile-problem-p)
  (when report-problem-p
    (let ((problem-string
            (twith-output-to-text-string
              (when compile-problem-p
                (twrite-string "This is uncompilable.  "))
              (when explanatory-text-string?
                (tformat "~A" explanatory-text-string?)))))
      (if explanatory-text-string?
          (reclaim-text-string explanatory-text-string?))
      (when (<f maximum-proglem-length-to-show-in-the-editor (lengthw problem-string))
        (notify-user "~A" problem-string)
        (setq problem-string
              (tformat-text-string "There was a problem.  See the logbook for the message.")))
      (handle-parsing-or-compilation-problem problem-string)
      (reclaim-text-string problem-string)))
  ;; just to remove pending indicator(s):
  (enable-or-disable-edit-end-and-update-buttons nil)
  ;; have option to exit workstation context?
  (maybe-offer-to-save-incomplete-statement))





(defun compile-for-current-edit-state
    (parse-or-bad-phrase? slot-value-compiler? just-update?)
  (let* ((frame (frame-being-edited? current-edit-state))
         (slot-name (name-of-slot-being-edited current-edit-state))
         (defining-class? (defining-class-for-slot-being-edited? current-edit-state))
         (slot-component-name?
           (name-of-slot-component-being-edited? current-edit-state))
         (slot-component-indicator?
           (indicator-of-slot-component-being-edited? current-edit-state)))
    (if (or (null slot-value-compiler?)
            (eq parse-or-bad-phrase? bad-phrase))
        parse-or-bad-phrase?
        (with-backtrace-for-internal-error
            (compile
              (push-backtrace-information
                slot-name)        ; defining-class?
              twrite-edit-backtrace-info)
          (funcall-compiled-function
            slot-value-compiler?
            (if just-update?
                (let ((phrase-copying-needs-annotation-rehashing
                        (editing-annotatable-code-p current-edit-state)))
                  (copy-for-phrase ; might be mutated
                    parse-or-bad-phrase?))
                parse-or-bad-phrase?)
            frame slot-name defining-class?
            slot-component-name?
            (if slot-component-name?
                 (get-slot-component-group
                   frame slot-name
                   slot-component-indicator?)))))))



;;; The `no-editor' parameter to `install-current-edit-state-compiled-result' signals
;;; that we are calling it from the rpc-driven editing interface that is used by
;;; T2. The two cases ('classic' and t2) share virtually all the processing that
;;; has to be done here with the crucial exception that, e.g., there is no workstation-
;;; context to be returned from when we are coming in by the rpc route.

(defun install-current-edit-state-compiled-result (new-value just-update? no-editor)
  (prog1 (macrolet ((free-text-box-hand-edited-to-blank-p (current-edit-state just-update?)
                      `(and (text-slot-type-p (type-of-slot-being-edited current-edit-state))
                            (eq (name-of-slot-being-edited current-edit-state)
                                'box-translation-and-text)
                            ;; deal with defining-class? another day! (MHD 2/15/94)
                            ;; frame borderless?
                            (not ,just-update?)        ; note: fixes bombout bug in 3.0 (MHD 2/19/93)
                            (text-blank-p (text-being-edited current-edit-state))
                            frame ; added to avoid trivial bug ddm 12/8/97
                            (not (frame-of-class-p frame 'type-in-box))
                            (not (frame-of-class-p frame 'message))
                            (not (editing-for-runtime-change? current-edit-state))))
                    (return-error (text-string &rest args)
                      `(progn
                         (handle-uncompilable-edit-state-result
                          t
                          (tformat-text-string ,text-string ,@args)
                          nil)
                         (return-from install-current-edit-state-compiled-result nil))))
           (let* ((frame (frame-being-edited? current-edit-state))
                  (slot-name (name-of-slot-being-edited current-edit-state))
                  (defining-class? (defining-class-for-slot-being-edited? current-edit-state))
                  (slot-description?
                    (get-slot-description-of-frame slot-name frame defining-class?))
                  (type-of-slot? (and slot-description?
                                      (feature-assq 'type (slot-features slot-description?))))
                  (slot-component-name?
                    (name-of-slot-component-being-edited? current-edit-state))
                  (slot-component-indicator?
                    (indicator-of-slot-component-being-edited? current-edit-state))
                  (reason-not-editable?
                    (when slot-description?
                      (reason-permanent-items-attribute-is-not-editable frame slot-name nil slot-description?))))

             (cond
               ((free-text-box-hand-edited-to-blank-p
                  current-edit-state just-update?)
                ;; If the text of a free text box being edited by hand is changed to blank,
                ;; then delete it; rules are documented under try-to-end-editing.
                (delete-frame frame)
                nil)
               ((null slot-description?)
                (return-error "Error: could not accept edit.  The attribute ~NQ of ~NF is no longer defined."
                              slot-name defining-class? frame))
               ;; This case is a fix for HQ-2360695 where the slot-type is changed by another edit
               ;; within this edit.  The current-edit-state is not updated with the new type so we
               ;; go to the slot-description.  Note that it would be nicer for the user to reparse
               ;; the value using its current type but that would require unravelling a lot of
               ;; state in the current-edit-state.  (ghw 1/15/99)
               ((and (user-vector-slot-index? slot-description?)
                     (not (equal (type-of-slot-being-edited current-edit-state) type-of-slot?))
                     (eq (funcall (slot-value-compiler (category-symbol-given-slot-type type-of-slot?))
                                  new-value frame nil)
                         bad-phrase))
                (return-error
                  "Error:  Could not accept the edit for ~NF.  The new value for the attribute ~NQ ~
          does not conform to its changed attribute type specification."
                  frame slot-name defining-class?))
               (reason-not-editable?
                (return-error "Cannot edit ~NF, because ~A.  See the saving-parameters."
                              frame reason-not-editable?))
               (t
                (let* ((runtime-change-p (editing-for-runtime-change? current-edit-state))
                       (do-not-note-permanent-changes-p
                           (or do-not-note-permanent-changes-p runtime-change-p)))
                  (if runtime-change-p
                      (note-kb-state-change-to-slot-by-saving-text frame slot-description?)
                      (update-authors-and-time-of-frame-edit frame slot-description?))

                  (change-slot-description-value
                    frame slot-description?
                    (if (text-slot-type-p (type-of-slot-being-edited current-edit-state))
                        (if no-editor
                            (slot-value-cons new-value (text-being-edited current-edit-state))
                            (make-text-value-using-current-edit-state new-value just-update?))
                        new-value)
                    slot-component-name? slot-component-indicator?)

                  (update-change-log-attribute frame slot-description? runtime-change-p)

                  nil)))))

    (unless no-editor
      (if just-update?
          (enable-or-disable-edit-end-and-update-buttons nil)        ; just to unhighlight!
          (return-from-current-workstation-context 'editing))
      (offer-to-recompile-items-made-incomplete-if-appropriate))))





;;; `Make-text-value-using-current-edit-state' new-value is to be called when
;;; new-value is about to be changed to be the value of the value part of a text
;;; slot (typically, e.g., the car of the box-translation-and-text slot).  This
;;; wraps the slot-value cons around new value and the corresponding text, which
;;; text is derived as follows.
;;;
;;; If just-update? is true, this copies the text of the current edit state,
;;; since the edit session is not about to end.
;;;
;;; If just-update? is false, then the edit session must be just about to end,
;;; and this returns a result that incorporates the actual text of the current
;;; edit state's text box, thus avoiding the copying that would be necessary,
;;; say, in the update case.  Note that after giving up the text, the pointer to
;;; it from the edit box is set to nil to prevent its reclamation, and that at
;;; this point the edit box and the edit state is no longer in a valid state for
;;; further use.
;;;
;;; Note that this depends on knowledge of various details of edit state and
;;; text box reclamation.
;;;
;;; NB: if things ever change such that the value of the definition does not
;;; come from (text-being-edited current-edit-state) then add-md5-identifier
;;; must be changed in synchrony -rdf, 3/22/96

(defun-simple make-text-value-using-current-edit-state (new-value just-update?)
  (slot-value-cons
    new-value
    (cond
      (just-update?
       (copy-text (text-being-edited current-edit-state)))
      (t
       (setf (cdr (box-translation-and-text
                    (edit-box current-edit-state)))
             nil)
       (text-being-edited current-edit-state)))))



;;; `Text-being-edited-may-have-no-value-p' must be tested by the editor to see
;;; if a value of no-value may be put as the value of a slot (or as the
;;; translation part of a box translation and text) at the end of editing.
;;;
;;; Currently this is true if this is either not a text type slot or the slot
;;; has the feature allow-text-slot-to-have-no-value.

(defun text-being-edited-may-have-no-value-p ()
  (let ((e current-edit-state))
    (if (text-slot-type-p (type-of-slot-being-edited e))
        (feature-assq
          'allow-text-slot-to-have-no-value
          (if (name-of-slot-component-being-edited? e)
              (get-slot-component-features
                (name-of-slot-being-edited e)
                (defining-class-for-slot-being-edited? e)
                (name-of-slot-component-being-edited? e))
              (slot-features
                (get-slot-description-of-frame
                  (name-of-slot-being-edited e)
                  (frame-being-edited? e)
                  (defining-class-for-slot-being-edited? e)))))
        nil)))





;;; `Get-slot-value-compiler-for-current-edit-state-if-any' returns the compiler
;;; for this edit state, if any; otherwise, nil.  It must determine whether we
;;; are parsing (as opposed to editing free text), and if so, whether we want to
;;; use the compiler for the type of slot being edited.
;;;
;;; As long as we are parsing, We want to use the compiler if:
;;;
;;;   (1) the type-in-box-input-value of a type-in-box instance is being edited; or
;;;
;;;   (2) the type of slot for the slot or slot component of the frame being
;;;   edited is equal to the type of slot being edited.
;;;
;;; Case (2) is the normal case, and the exceptions to it at this time are (a)
;;; entering values into a type-in box and (b) editing a message through field
;;; edit using the grammar from another slot, which is a historically relatively
;;; new (G2 4.0) capability.
;;;
;;; The compiler we get for case (1) is just the compiler for the type of slot
;;; we are editing.
;;;
;;; The compiler we get for case (2) is either the compiler for the current
;;; 3-tuple (frame, slot name, defining class) or 5-tuple (frame, slot name,
;;; defining class, slot component name, slot component indicator).
;;;
;;; Note that if we are editing for another slot (e.g., the field-edit case),
;;; nil is returned.

(defun-simple get-slot-value-compiler-for-current-edit-state-if-any ()
  (let* ((e current-edit-state)
         (frame (frame-being-edited? e))
         (slot-name (name-of-slot-being-edited e)))
    (if (and (not (free-text-slot-being-edited? e))
             (or (and (frame-of-class-p frame 'type-in-box)
                      (eq slot-name 'type-in-box-input-value))
                 (equal (type-of-slot-being-edited e)
                        (if (name-of-slot-component-being-edited? e)
                            (get-type-of-slot-component-if-any
                              frame
                              slot-name
                              (defining-class-for-slot-being-edited? e)
                              (name-of-slot-component-being-edited? e)
                              (indicator-of-slot-component-being-edited? e))
                            (get-type-of-slot-if-any
                              frame
                              slot-name
                              (defining-class-for-slot-being-edited? e))))))
        (slot-value-compiler
          (category-symbol-given-slot-type
            (type-of-slot-being-edited e))))))




;;; `Get-current-edit-state-parse-if-any' collects the parse of the text of the
;;; current editing context to end the editing session.  This returns either the
;;; resulting parse (a phrase tree made up of phrase conses), or bad-phrase,
;;; i.e., the unique value that is the value of special variable bad-phrase.

;;; In general, problems may occur.  The case where the text is totally
;;; incomplete the most common.  If this happens, the message "This is incomplete"
;;; is issued, and bad-phrase is returned.

;;; It is a programming error for a grammar to be ambiguous, so this case should
;;; never arise in non-development.  If it ever does happen in production, G2
;;; calls `handle-parsing-ambiguity', which simply issues the message "This is
;;; ambiguous in G2".  In development only, in addition, the special variable
;;; `list-of-ambiguous-parses' gets set by this function to the list of phrases
;;; that consitute the ambiguity.

(defun-simple get-current-edit-state-parse-if-any ()
  (if (not (free-text-slot-being-edited? current-edit-state))
      (loop as incomplete-phrase
               in (car (stack-of-incomplete-phrases-at-earlier-positions
                         current-edit-state))
            when (eq (phrase-rule-completions incomplete-phrase)
                     (phrase-rule-completions-past-instance-of-category
                       current-edit-state))
              collect (car (incomplete-stack-of-constituents incomplete-phrase))
                into instances-of-category using phrase-cons
            finally
              (return
                (cond
                  ((null instances-of-category)
                   (home-down-cursor)        ; don't put up menus if do notification!
                   (handle-parsing-or-compilation-problem "This is incomplete")
                   bad-phrase)
                  ((cdr instances-of-category)
                   (handle-parsing-ambiguity instances-of-category)
                   bad-phrase)
                  (t (car instances-of-category)))))))

#+development
(defvar list-of-ambiguous-parses nil)

(defun handle-parsing-ambiguity (instances-of-category)
  #-development
  (declare (ignore instances-of-category))

  ;; This is all the user gets to see, since this "never" happens.
  (handle-parsing-or-compilation-problem "This is ambiguous in G2")

  #+development
  (let ((the-text
          (twith-output-to-text-string
            (tformat
              "This is ambiguous in G2, and the ~d possible interpretations are: "
              (length instances-of-category))
            (loop as i from 1
                  for l on instances-of-category
                  do (unless (eq l instances-of-category)
                       (twrite ", "))        ; not 1st time
                     (tformat "~%(~D) ~(~a~)" i (car l))))))

    ;; Display an expanded edit notification:
    (display-editor-notification the-text)

    (reclaim-text-string the-text)

    ;; record the parses in a special variable for developers to examine:
    (setq list-of-ambiguous-parses instances-of-category)

    ;; pretty print the ambiguous stuff on the console:
    (format t "ambiguous stuff:~%")
    (loop for x in instances-of-category do (pprint x))))




;;; Maybe-offer-to-save-incomplete-statement ... Note that slot-name-for-text-slot may
;;; only be the name of a slot which is a text slot (which is allowed to be saved
;;; without being complete) -- hence the name.

(defun maybe-offer-to-save-incomplete-statement ()
;  (let* ((text-slot-being-edited?
;           (text-slot-type-p (type-of-slot-being-edited current-edit-state))))
;    (cond
;      (text-slot-being-edited?
;       (enter-dialog
;         (tformat-text-string
;           "This statement has problems.  OK to ~
;            disable it and save it this way?  (Cancel to continue editing.)")
;         (copy-constant-wide-string #w"OK") (copy-constant-wide-string #w"Cancel")
;         'exit-dialog-and-save-out-incomplete-statement-and-exit-editor nil
;         nil nil))))
  )

;; MAYBE is the operative word here.  This is under development and is not ready
;; to be enabled yet! (MHD 10/18/89)

#+unused
(defun exit-dialog-and-save-out-incomplete-statement-and-exit-editor ()
  (exit-current-workstation-context-in-return-function 'dialog)
  (in-editing-context (specific-structure-for-current-workstation-context)
    (let* ((frame-being-edited?
             (frame-being-edited? current-edit-state))
           (slot-name
             (name-of-slot-being-edited current-edit-state))
           (defining-class?
             (defining-class-for-slot-being-edited? current-edit-state))
           (text-slot-being-edited?
             (text-slot-type-p (type-of-slot-being-edited current-edit-state))))
      (cond
        (text-slot-being-edited?                ; nec.?
         (change-slot-value
           frame-being-edited? slot-name
           (slot-value-cons
             no-value
             (copy-text
               (text-being-edited current-edit-state)))
           defining-class?)))))
  (return-from-current-workstation-context 'editing))



;;;; Editor Menu Filtering


;;; `Editor menu filtering' is a facility, currently used only by the system
;;; procedure g2-ui-launch-editor, to hide selected grammar/instance prompts
;;; from the user. The aim is for application developers to allow users to edit
;;; actions, for example, without displaying prompts such as "shut down g2",
;;; even though that phrase is still in the grammar.

;;; It is currently implemented via a new slot, editor-prompt-filter?, in
;;; edit-state, which is a list of lists of symbols (phrases) to exclude. Any
;;; prompt which begins with one of the phrases will be excluded.

(defmacro filter-editor-menus-p ()
  `(and current-edit-state (editor-prompt-filter? current-edit-state)))


;;; The function `exclude-editor-prompt-p' returns true iff the given prompt
;;; (a symbol or list of symbols) should be hidden from the user.

;;; A prompt is excluded if it has a prefix which is equal to any elements of
;;; exclusions. In other words, an exclusion excludes all prompts which start
;;; with it.

(defun exclude-editor-prompt-p (prompt)
  (let ((exclusions (editor-prompt-filter? current-edit-state)))
    (cond ((null exclusions)
           nil)
          ((atom prompt)                ; Category name or instance name
           (loop for exclusion in exclusions
                 thereis (eq prompt (car exclusion))))
          (t
           (loop for exclusion in exclusions
                 thereis (list-prefix-p exclusion prompt))))))


;;; The function `filter-editor-menus' returns a newly consed menu tree with
;;; some items removed.

(defun filter-editor-menus (menus)
  (let* ((end? (eq (car menus) 'end))
         (category-symbols (if end? (cadr menus) (car menus)))
         (submenus (if end? (cddr menus) (cdr menus)))
         (filtered-categories
           (loop for category in category-symbols
                 unless (exclude-editor-prompt-p category)
                   collect category using grammar-cons))
         (filtered-submenus
           (loop for submenu in submenus
                 as upcase? = (eq (car submenu) ':upcase)
                 as filtered = (loop for phrase in (if upcase? (cdr submenu) submenu)
                                     unless (exclude-editor-prompt-p phrase)
                                       collect (copy-tree-using-grammar-conses phrase)
                                         using grammar-cons)
                 when filtered
                   collect (if upcase? (grammar-cons ':upcase filtered) filtered)
                     using grammar-cons)))
    (nconc
      (if end? (grammar-list 'end))
      (grammar-list filtered-categories)
      filtered-submenus)))



;;;; Editor Menus



;;; Update-edit-menus-or-autocomplete-as-appropriate ...  Prefix-simple-string?
;;; may be empty.  Parsing-extension-mode may be T or NO-AUTOCOMPLETION.

;;; The menus for a particular character position include those elements of the
;;; menu content structure for the current token position that can be or begin
;;; with a token that (a) is of a type included in potential-token-types?  and
;;; (b) begins with prefix-simple-string?, except that when potential-token-
;;; types? (and prefix-simple-string?) are nil, all tokens are assumed possible.
;;; (The menu content structure for the current token position should have been
;;; generated by make-menu-content-structure-for-token-position.)  To these
;;; elements are added menus containing those instances of categories in the
;;; category menu that begin with prefix-simple-string?, PROVIDED the number of
;;; such instances does not exceed either the
;;; maximum-number-of-names-for-a-menu-override? specified in the current edit
;;; state, if any, or the maximum-number-of-names-for-a-menu parameter specified
;;; in the editor-parameters system frame.

;;; This returns non-nil in the following 3 cases: when it simply suspends
;;; parsing because the workstation has pending events, when it puts or leaves
;;; one or more menus up, or when it "autocompletes".  It returns nil only when
;;; it wants to put or leave up menus but there are no legal tokens at the
;;; current cursor position.

;;; When parsing is suspended, menus are left unchanged and the
;;; parsing-extension-mode? slot of current-edit-state is set per the
;;; parsing-extension-mode argument.  Autocompletion occurs when all of the
;;; following obtain: (1) input is not endable here, (2) the no-autocompletion?
;;; argument is nil (implying that the last edit operation was not a deletion),
;;; (3) there would be exactly one token or token sequence to be put up, and (4)
;;; the user has selected autocompletion mode.
;;;
;;; [Note, at present, the autocompletion mode is not selectable by the user,
;;; nor has it ever been; see the code and comments below for details.  Note
;;; that there's now a "manual autocompletion" feature, triggered by the user
;;; typing control-space.  It's described elsewhere in this module.  (MHD
;;; 4/18/94)]

(defun update-edit-menus-or-autocomplete-as-appropriate
    (potential-token-types? prefix-simple-string? parsing-extension-mode)
  (if (or (current-workstation-has-pending-events-p)
          keep-edit-workspace-hidden-no-matter-what?)
      (setf (parsing-extension-mode? current-edit-state) parsing-extension-mode)
      (let* ((temporary-information-on-edit-workspace?
               (temporary-information-on-edit-workspace? current-edit-state))
             (menu-content-structure-for-token-position
               (get-or-make-menu-content-structure-for-current-token-position))
             (munge-colons-p
               (cond ((colon-content-p menu-content-structure-for-token-position)
                      1)
                     ((colon-content-p (get-menu-content-structure-for-last-token-position 1))
                      2)))
             (string-for-make-category-instance-menus
               (cond ((null munge-colons-p)
                      prefix-simple-string?)
                     ((eql 1 munge-colons-p)
                      (tformat-text-string "~A~A"
                                           (car (stack-of-tokens current-edit-state))
                                           prefix-simple-string?))
                     ((eql 2 munge-colons-p)
                      (tformat-text-string "~A~A~A"
                                           (cadr (stack-of-tokens current-edit-state))
                                           (car (stack-of-tokens current-edit-state))
                                           prefix-simple-string?))))
             (category-instance-menus
               (make-category-instance-menus
                 (cond ((not (eq 'end (car menu-content-structure-for-token-position)))
                        (car menu-content-structure-for-token-position))
                       ((null munge-colons-p)
                        (cadr menu-content-structure-for-token-position))
                       (t
                        (car (get-menu-content-structure-for-last-token-position munge-colons-p))))
                 string-for-make-category-instance-menus
                 (or
                   (maximum-number-of-names-for-a-menu-override?
                     current-edit-state)
                   (maximum-number-of-names-for-a-menu        ; RENAME! 10! NEW ALIAS!
                     editor-parameters))))
             (menu-content-structure-for-character-position        ; may share structure
               (nconc
                 (cond
                   (potential-token-types?
                    (make-menu-content-structure-for-character-position
                      menu-content-structure-for-token-position
                      potential-token-types? prefix-simple-string?))
                   (category-instance-menus
                    (copy-list-using-grammar-conses
                      menu-content-structure-for-token-position))
                   (t menu-content-structure-for-token-position))
                 category-instance-menus))
             (endable-here?
               (eq (car menu-content-structure-for-character-position) 'end))
             (menus
               (if endable-here?
                   (cdr menu-content-structure-for-character-position)
                   menu-content-structure-for-character-position)))
        (enable-or-disable-edit-end-and-update-buttons (not endable-here?))
        (when (frame-being-edited? current-edit-state)
          (funcall-method-if-any
            'add-items-to-edit-workspace ; specified in KB-LOAD1 at present
            (frame-being-edited? current-edit-state)
            current-edit-workspace
            (edit-box current-edit-state)
            t))                                ; refresh case
        (when munge-colons-p
          (reclaim-text-string string-for-make-category-instance-menus))
        (procedure-signature-hook)
        (if (do-not-have-edit-menus? current-edit-state)
            ;; no menus (tho there may be subcommand menus)
            (progn
              (delete-subblocks-of-class
                current-edit-workspace 'editor-notification)
              (shrink-wrap-workspace current-edit-workspace)
              (unless (eq menu-content-structure-for-token-position
                          menu-content-structure-for-character-position)
                (reclaim-menu-content-structure-for-character-position
                  menu-content-structure-for-character-position))
              t)
            (cond                                ; unwind-protect?
              ((and (not endable-here?)                ; autocomplete test
                    (null (first menus))        ; no category menu
                    (cdr menus)                        ; exactly one token menu
                    (null (cddr menus))
                    (null (cdr (second menus)))        ; exactly one token or token sequence
                    nil ; (allow-automatic-completion? editor-parameters) ; IN AUTOCOMPLETION MODE!
                    (not (eq parsing-extension-mode 'no-autocompletion)))
               (let* ((token-or-token-sequence
                        (first (second menus)))
                      (text-string                ; for autocompletion
                        (twith-output-to-text-string        ; see also make-token-menu-table
                          (let ((write-symbols-parsably? t)
                                (write-symbols-in-lower-case? t))
                            (if (atom token-or-token-sequence)
                                (progn
                                  (twrite token-or-token-sequence)
                                  (twrite-char #.%space))
                                (loop for token in token-or-token-sequence
                                      do (twrite token)
                                         (twrite-char #.%space)))))))
                 (if (not (eq menu-content-structure-for-character-position
                              temporary-information-on-edit-workspace?))
                     (reclaim-menu-content-structure-for-character-position
                       menu-content-structure-for-character-position))
                 (insert-text-string-at-cursor text-string t t)
                 (reclaim-text-string text-string))
               t)
              (t (cond
                   ((equal menu-content-structure-for-character-position
                           temporary-information-on-edit-workspace?)
                    (if (not (eq menu-content-structure-for-character-position
                                 temporary-information-on-edit-workspace?))
                        (reclaim-menu-content-structure-for-character-position
                          menu-content-structure-for-character-position)))
                   (t (let ((keep-category-menu?
                              (if (and (consp temporary-information-on-edit-workspace?)
                                       (not (eq (car temporary-information-on-edit-workspace?)
                                                'end)))
                                  (equal (car menu-content-structure-for-character-position)
                                         (car temporary-information-on-edit-workspace?)))))
                        (erase-any-temporary-information-on-edit-workspace
                          keep-category-menu?)
                        (put-up-menus menus endable-here? keep-category-menu?))
                      (setf (temporary-information-on-edit-workspace? current-edit-state)
                            menu-content-structure-for-character-position)))
                 (or (car menus) (cdr menus))))))))


(defun colon-content-p (content)
  (and (eq 'end (car content))
       (equal '(|::|) (caddr content))))

;;; Get-or-make-menu-content-structure-for-current-token-position ...

(defun get-or-make-menu-content-structure-for-current-token-position ()
  (or (car (stack-for-token-menus current-edit-state))
      (setf (car (stack-for-token-menus current-edit-state))
            (make-menu-content-structure-for-token-position
              (car (stack-of-incomplete-phrases-at-earlier-positions
                     current-edit-state))
              (phrase-rule-completions-past-instance-of-category
                current-edit-state)))))

(defun get-menu-content-structure-for-last-token-position (n)
  (nth n (stack-for-token-menus current-edit-state)))



;;; Reclaim-menu-content-structure-for-character-position ...

;;; Menu-content-structure-for-character-position may be or have elements from
;;; the menu content structure for the current token position.  Such shared
;;; structure(s) will not be reclaimed.

(defun reclaim-menu-content-structure-for-character-position
       (menu-content-structure-for-character-position)
  (let ((menu-content-structure-for-current-token-position
          (car (stack-for-token-menus current-edit-state))))
    (if (not (eq menu-content-structure-for-character-position
                 menu-content-structure-for-current-token-position))
        (loop for menu-content-element in menu-content-structure-for-character-position
              unless (memq menu-content-element
                           menu-content-structure-for-current-token-position)
                do (reclaim-grammar-tree menu-content-element)
              finally
                (reclaim-grammar-list-macro
                  menu-content-structure-for-character-position)))))

;; Consider abstracting the uses of reclaim-grammar-tree and reclaim-grammar-list.

;; Consider requiring that elements from the menu content structure for the current token
;; position be an initial subsequence thereof or at least an ordered subset thereof.  If
;; this were done, the code above could be revised to run a bit faster.



;;; The function `put-up-menus' puts up the menus in for the various possible
;;; completions of a given grammar category.  The menus of choices have already
;;; been computed by this time, and are contained in the
;;; menu-content-structure.

(defun put-up-menus
    (menu-content-structure endable-here? category-menu-is-already-there?)
  (cond ((filter-editor-menus-p)
         (let ((filtered-menus (filter-editor-menus menu-content-structure)))
           (prog1 (put-up-menus-1 filtered-menus endable-here? category-menu-is-already-there?)
             (reclaim-grammar-tree filtered-menus))))
        (t
         (put-up-menus-1 menu-content-structure endable-here? category-menu-is-already-there?))))

(defun put-up-menus-1
    (menu-content-structure endable-here? category-menu-is-already-there?)
  (when (native-editor-workspace-p current-edit-workspace)
    (native-editor-show-completions current-edit-state menu-content-structure))
  (let* ((category-menu (car menu-content-structure))
         (existing-category-menu? nil)
         (menus
           (loop with l = menu-content-structure
                 as menu = (car l)                ; rename this variable!
                 nconc
                 (cond
                   (endable-here?
                    (setq endable-here? nil)        ; changes arg
;                      (grammar-list
;                        (make-subcommand-menu
;                          (copy-for-slot-value
;                            '(end))))                ; "End"? "OK"? "Finish"? "Enter"?
                    nil)
                   ((eq menu category-menu)
                    (pop l)
                    (if (and category-menu
                             (not (equal category-menu
                                         '(bad-java-character-literal))))
                        (grammar-cons-macro
                          (or (if category-menu-is-already-there? ; ok if not there
                                  (loop for subblock being each subblock of current-edit-workspace
                                        when (frame-of-class-p subblock 'category-menu)
                                          return
                                          (setq existing-category-menu? subblock)))
                              (make-category-menu-table menu))
                          nil)
                        nil))
                   ((and (null (cdr menu))        ; two onesies in a row
                         (if (cdr l) (null (cdr (car (cdr l))))))
                    (grammar-cons-macro
                      (let ((list-of-onesies
                              (loop nconc (grammar-cons-macro (car (pop l)) nil)
                                    until (or (null l) (cdr (car l))))))
                        (prog1 (make-token-menu-table list-of-onesies nil)
                          (reclaim-grammar-list-macro list-of-onesies)))
                      nil))
                   (t (pop l)
                      (grammar-cons-macro
                        (if (eq (car menu) :upcase)
                            (make-token-menu-table (cdr menu) t)
                            (make-token-menu-table menu nil))
                        nil)))
                 while l)))

    ;; do steps 2-5!
    (loop with workspace-margin
            = (workspace-margin current-edit-workspace)
          with amount-by-which-width-can-exceed-height = 0        ; parameterize!
          with intermenu-spacing
            = (if (eq (or (font-size-override-for-edit-workspace? current-edit-state)
                          (if new-g2-classic-ui-p
                              (get-ui-parameter 'font-for-editing)
                              (font-for-editing fonts)))
                      'small)
                  18
                  25)        ; parameterize!
          with edit-box = (edit-box current-edit-state)
          with left-edge-of-menu-area
            = (left-edge-of-block edit-box)
          with top-edge-of-menu-area
            = (+w (bottom-edge-of-block edit-box)
                  workspace-margin
                  (if (and (kfep-conversion-text-region? current-edit-state) ; nec?
                           (kfep-conversion-choices? current-edit-state))
                      (height-for-kanji-conversion-choices current-edit-state)
                      (or (extra-space-to-leave-below-edit-box? current-edit-state)
                          0)))
          with current-left-edge-of-menu-area = left-edge-of-menu-area
          with current-top-edge-of-menu-area = top-edge-of-menu-area
          with current-right-edge-of-menu-area = left-edge-of-menu-area
          with current-bottom-edge-of-menu-area = top-edge-of-menu-area
          for menu in menus
          as left-edge-of-menu = (left-edge-of-block menu)
          as top-edge-of-menu = (top-edge-of-block menu)
          ;; Step 2 -- Layout
          do
      (cond
        ((>w (-w (-w current-left-edge-of-menu-area left-edge-of-menu-area)
                 (-w current-top-edge-of-menu-area top-edge-of-menu-area))
             amount-by-which-width-can-exceed-height)
         ;; Too wide
         (setq current-left-edge-of-menu-area left-edge-of-menu-area)
         (unless (eq menu existing-category-menu?)
           (shift-block
             menu
             (-w current-left-edge-of-menu-area left-edge-of-menu)
             (-w current-bottom-edge-of-menu-area top-edge-of-menu)))
         (setq current-right-edge-of-menu-area
               (maxw current-right-edge-of-menu-area
                     (+w (right-edge-of-block menu) intermenu-spacing)))
         (setq current-bottom-edge-of-menu-area
               (setq current-top-edge-of-menu-area
                     (+w (bottom-edge-of-block menu) intermenu-spacing))))
        ((<w (-w (-w current-left-edge-of-menu-area left-edge-of-menu-area)
                 (-w current-top-edge-of-menu-area top-edge-of-menu-area))
             amount-by-which-width-can-exceed-height)
         ;; Too narrow
         (unless (eq menu existing-category-menu?)
           (shift-block
             menu
             (-w current-right-edge-of-menu-area left-edge-of-menu)
             (-w top-edge-of-menu-area top-edge-of-menu)))
         (setq current-right-edge-of-menu-area
               (maxw current-right-edge-of-menu-area
                     (+w (right-edge-of-block menu) intermenu-spacing)))
         (setq current-bottom-edge-of-menu-area
               (setq current-top-edge-of-menu-area
                     (maxw current-bottom-edge-of-menu-area
                           (+w (bottom-edge-of-block menu) intermenu-spacing))))
         (setq current-left-edge-of-menu-area left-edge-of-menu-area))
        (t
         (if (not (eq menu existing-category-menu?))
             (shift-block
               menu
               (-w current-left-edge-of-menu-area left-edge-of-menu)
               (-w current-top-edge-of-menu-area top-edge-of-menu)))
         (setq current-right-edge-of-menu-area
               (maxw current-right-edge-of-menu-area
                     (setq current-left-edge-of-menu-area
                           (+w (right-edge-of-block menu) intermenu-spacing))))
         (setq current-bottom-edge-of-menu-area
               (maxw current-bottom-edge-of-menu-area
                     (+w (bottom-edge-of-block menu) intermenu-spacing)))))
          finally
            ;; Step 3 -- Select scale -- quantized (Not doing this yet!)
            ;; Step 4 -- Enlarge as necessary & change scale with appropriate
            ;;   corner(s) fixed. (Not doing the scaling part yet!)
            (enlarge-workspace-if-necessary
              current-edit-workspace
              left-edge-of-menu-area top-edge-of-menu-area
              (+w (-w current-right-edge-of-menu-area intermenu-spacing) workspace-margin)
              (+w (-w current-bottom-edge-of-menu-area intermenu-spacing)
                  workspace-margin))
          ;; Step 5a -- reverse the list of menus so that they'll end up
          ;;   in the particular subblocks order we want, that is, the order
          ;;   they're in now, after adding. (This will cause them to be drawn
          ;;   in this order, and selected with the keyboard in this order.)
            (setq menus (nreverse-canonically menus))
          ;; Step 5b -- place, add, and draw
            (loop as menu in menus
                  unless (eq menu existing-category-menu?) do
                      (add-subblock menu current-edit-workspace)
                      (draw-images-of-block menu t))
          ;; Step 5c -- highlight the current choice, per menu-choice-index?, if any
            (when (menu-choice-index? current-edit-state)
              (highlight-or-unhighlight-selected-token-menu-choice nil))
            (reclaim-grammar-list-macro menus))))

;; Consider binding various format-controlling globals.

;; Abstract some of the pieces of this!

;; Consider having a way to suppress autocompletion.



;;; Erase-any-temporary-information-on-edit-workspace ...

(defun erase-any-temporary-information-on-edit-workspace
       (keep-category-menu? &optional shrink-wrap-too?)
  (let ((temporary-information-on-edit-workspace?
          (temporary-information-on-edit-workspace? current-edit-state)))
    (cond
      (temporary-information-on-edit-workspace?
       (case temporary-information-on-edit-workspace?
         ((editor-notification needs-refreshing)
          (delete-subblocks-of-class
            current-edit-workspace 'editor-notification))
         (t (delete-subblocks-of-class current-edit-workspace 'token-menu)
            (if (not keep-category-menu?)
                (delete-subblocks-of-class current-edit-workspace 'category-menu))
            (reclaim-menu-content-structure-for-character-position
              temporary-information-on-edit-workspace?)))
       (if shrink-wrap-too? (shrink-wrap-workspace current-edit-workspace))
       (setf (temporary-information-on-edit-workspace? current-edit-state) nil)))))

;; MHD says that this should "shrink-wrap" (or at least "bag") current-edit-workspace!!



(def-class (category-instance-menu-workspace non-kb-workspace)
  (workspace-margin 20))                        ; adjust?

;; Consider making this a kb workspace instead, but one with the same menu this now has
;; (with maybe a couple of other options).  Then consider INITIALLY using temporary-
;; category-instance-menu-workspace, a non-kb workspace with a "keep" menu option that
;; changes the class to category-instance-menu-workspace.




;;; A `category-menu' is a menu used to show grammar catagories
;;; approprate to the current cursor location.

(def-class (category-menu menu))


;;; The `generate-spot for a category-menu' generates a
;;; category-menu-button-spot or a workspace background spot.

(def-class-method generate-spot (category-menu mouse-pointer)
  (generate-spot-for-button-menu
    (make-category-menu-button-spot)
    category-menu
    mouse-pointer))


;;; A `token menu' is a menu used to insert one or more tokens into the text
;;; editor while parsing.
;;;
;;; A token menu has the following three generic slots in common with the class
;;; SCRAP (see below).  (A "generic" slot here refers to slots that do not have
;;; vector indexing, have accessors defined only by one of their subclases, and
;;; therefore must be accessed by lookup, and that are originally defined by
;;; more than one disjoint class, here by token-menu and scrap.)
;;;
;;;   `replace-fragments-on-sides?';
;;;   `handle-spaces-intelligently?'; and
;;;   `replace-entire-text?'
;;;
;;; These slots have the exact meanings defined for the them by
;;; insert-text-string-in-text-being-edited, which see.
;;;
;;; These are used by auto-insert-text-from-block, which ends up using them to
;;; ultimately form the arguments to insert-text-string-in-text-being-edited.

(def-class (token-menu menu)
  (replace-fragments-on-sides? t no-accessor lookup-slot)
  (handle-spaces-intelligently? t no-accessor lookup-slot)
  (replace-entire-text? nil no-accessor lookup-slot))

;;; The `generate-spot for a token-menu' generates a
;;; token-menu-button-spot or a workspace background spot.

(def-class-method generate-spot (token-menu mouse-pointer)
  (generate-spot-for-button-menu
    (make-token-menu-button-spot)
    token-menu
    mouse-pointer))

#+obsolete
(declare-unselectable-class-of-subblock token-menu)


;;; A `replacement token menu' is a token menu whose items replace the entire
;;; contents of the edit box.

(def-class (replacement-token-menu token-menu)
  (replace-entire-text? t))

;; Consider adding a "replacement-text-inserter", which is like this (i.e.,
;; replaces the entire edit text when clicked on).


;;; The `generate-spot for a replacement-token-menu' generates a
;;; replacement-token-menu-button-spot or a workspace background spot.

(def-class-method generate-spot (replacement-token-menu mouse-pointer)
  (generate-spot-for-button-menu
    (make-replacement-token-menu-button-spot)
    replacement-token-menu
    mouse-pointer))



;;; A `character-sequence token menu' is a token menu whose items insert as though
;;; from a character-sequence inserter, i.e., without handle-spaces-intelligently?
;;; and without replace-fragments-on-sides?.

(def-class (character-sequence-token-menu token-menu)
  (replace-fragments-on-sides? nil)
  (handle-spaces-intelligently? nil)
  (replace-entire-text? nil))


;;; The `generate-spot for a character-sequence-token-menu' generates a
;;; character-sequence-token-menu-button-spot or a workspace background spot.

(def-class-method generate-spot (character-sequence-token-menu mouse-pointer)
  (generate-spot-for-button-menu
    (make-character-sequence-token-menu-button-spot)
    character-sequence-token-menu
    mouse-pointer))


;;; A `pathname-component token menu' is a token menu whose items insert without
;;; handle-spaces-intelligently?  but with replace-fragments-on-sides?.

(def-class (pathname-component-token-menu character-sequence-token-menu)
  (replace-fragments-on-sides? t)
  (handle-spaces-intelligently? nil)
  (replace-entire-text? nil))


;;; The `generate-spot for a pathname-component-token-menu' generates a
;;; pathname-component-token-menu-button-spot or a workspace background spot.

(def-class-method generate-spot (pathname-component-token-menu mouse-pointer)
  (generate-spot-for-button-menu
    (make-pathname-component-token-menu-button-spot)
    pathname-component-token-menu
    mouse-pointer))


;; Note: the class pathname-component text inserter has not yet been
;; implemented.  It would be a snap, but would require time to document.  Do it,
;; as well as an the "entire-text-inserter" class (decide on a name), for 4.1.
;; (MHD 4/18/94)
;;
;; Note that the classes character-sequence-token-menu and
;; replacement-token-menu are not currently in use in the product.  Reconsider
;; the name replacement-token-menu.  (MHD 4/18/94)



(def-class (kfep-conversion-choice-menu menu))

;;; The `generate-spot for a replacement-token-menu' generates a
;;; replacement-token-menu-button-spot or a workspace background spot.

(def-class-method generate-spot (kfep-conversion-choice-menu mouse-pointer)
  (generate-spot-for-button-menu
    (make-kfep-conversion-choice-menu-button-spot)
    kfep-conversion-choice-menu
    mouse-pointer))


;; See also subcommand-menu, as defined below.

;; If these are further differentiated, revise handle-mouse-down-event-in-edit-
;; context accordingly.  Same applies to the class subcommand-menu, q.v. below.


(def-table-format token-menu-format
  table-background-color? transparent
  table-row-boundary-width 0
  table-column-boundary-width 0
  table-left-border-width 0
  table-top-border-width 0
  table-right-border-width 0
  table-bottom-border-width 0)

;; Equivalent formats that do not go into KB's should be replaced by a single format.

#+development
(def-table-format-spot-generator token-menu-format (menu mouse-pointer)
  (declare (ignore menu mouse-pointer))
  ;; The block generate-spot method preempts this.
  (error "The spot generator for token-menu-format should never be called"))



(def-format-class (token-menu-item-format text-box-format)
  (text-cell-left-margin 7)
  (text-cell-top-margin 3)
  (text-cell-right-margin 7)
  (text-cell-bottom-margin 3)
  (text-cell-font-map (hm18))
  (text-cell-line-height 20)
  (text-cell-baseline-position 15)
  (text-cell-line-spacing 0)                        ; very tight leading desired
  (text-cell-line-quadding? center)
  (minimum-format-width-for-text-cell 400)
  (minimum-width-for-text-cell 60))


(def-format-class (small-token-menu-item-format token-menu-item-format)
  (text-cell-left-margin 6)
  (text-cell-top-margin 2)
  (text-cell-right-margin 6)
  (text-cell-bottom-margin 2)
  (text-cell-font-map (hm14))
  (text-cell-line-height 15)
  (text-cell-baseline-position 13)
  (text-cell-line-spacing 2)
  (minimum-format-width-for-text-cell 350))



(def-token-menu-item-format left-aligned-token-menu-item-format
  text-cell-line-quadding? left)
(def-token-menu-item-format center-aligned-token-menu-item-format
  text-cell-line-quadding? center)
(def-token-menu-item-format right-aligned-token-menu-item-format
  text-cell-line-quadding? right)

(def-small-token-menu-item-format left-aligned-small-token-menu-item-format
  text-cell-line-quadding? left)
(def-small-token-menu-item-format center-aligned-small-token-menu-item-format
  text-cell-line-quadding? center)
(def-small-token-menu-item-format right-aligned-small-token-menu-item-format
  text-cell-line-quadding? right)



(def-token-menu-item-format left-aligned-category-menu-item-format
  text-cell-line-quadding? left)
(def-token-menu-item-format center-aligned-category-menu-item-format
  text-cell-line-quadding? center)
(def-token-menu-item-format right-aligned-category-menu-item-format
  text-cell-line-quadding? right)

(def-small-token-menu-item-format left-aligned-small-category-menu-item-format
  text-cell-line-quadding? left)
(def-small-token-menu-item-format center-aligned-small-category-menu-item-format
  text-cell-line-quadding? center)
(def-small-token-menu-item-format right-aligned-small-category-menu-item-format
  text-cell-line-quadding? right)

;; Consider having a light gray background for the "any ..." menus; would
;; be nice, if this were done, if it could work on monochrome systems by
;; using a dithering pattern.  Or maybe white on black, ala subcommands.


(setf (corresponding-small-font-format-name 'left-aligned-category-menu-item-format)
      'left-aligned-small-category-menu-item-format)
(setf (corresponding-small-font-format-name 'center-aligned-category-menu-item-format)
      'center-aligned-small-category-menu-item-format)
(setf (corresponding-small-font-format-name 'right-aligned-category-menu-item-format)
      'right-aligned-small-category-menu-item-format)


(setf (corresponding-small-font-format-name 'left-aligned-token-menu-item-format)
      'left-aligned-small-token-menu-item-format)
(setf (corresponding-small-font-format-name 'center-aligned-token-menu-item-format)
      'center-aligned-small-token-menu-item-format)
(setf (corresponding-small-font-format-name 'right-aligned-token-menu-item-format)
      'right-aligned-small-token-menu-item-format)

;; Equivalent formats that do not go into KB's should be replaced by a single format.

;; As of now, no token menu item or table formats have ever or should ever
;; be saved in a KB.  (MHD 5/9/91)



(defun choose-token-menu-item-format-per-system-tables
       (&optional category-menu-case?)
  (choose-font-format-per-font-size
    (case (alignment-for-menu-choices menu-parameters)
      (left
       (if category-menu-case?
           'left-aligned-category-menu-item-format
           'left-aligned-token-menu-item-format))
      (center
       (if category-menu-case?
           'center-aligned-category-menu-item-format
           'center-aligned-token-menu-item-format))
      (right
       (if category-menu-case?
           'right-aligned-category-menu-item-format
           'right-aligned-token-menu-item-format)))
    (or (font-size-override-for-edit-workspace? current-edit-state)
        (if new-g2-classic-ui-p
            (get-ui-parameter 'font-for-editing)
            (font-for-editing fonts)))))





;;; The function `make-category-menu-table' makes the category menus which contain
;;; just the name of the grammar category, rather than all of the possible completions.
;;; For example, "any keyboard-symbol"

;;; "Singular-number" and "plural-number" are replaced by "number".  "Singular-integer",
;;; "plural-integer", and "non-negative-integer" are replaced by "integer".  "Integer" is
;;; omitted if "number" occurs.

;;; "Left-string" is replaced by "quoted-message".  "Middle-string" and "right-string" are
;;; replaced by "end-of-message".  "Whole-string" is replaced by "string".  "String" is
;;; omitted if "quoted-message" occurs.  (It is assumed that "middle-string" and
;;; "right-string" are inconsistent with the others.)

;;; "Neutral-unit-of-measure", "singular-unit-of-measure", and "plural-unit-of-measure"
;;; are replaced by "unit-of-measure".

(defun make-category-menu-table (category-menu)
  (make-or-reformat-table
    (loop with reversed-rows = nil
          with number-category-symbol? = nil
          with string-category-symbol? = nil
          with unit-of-measure-category-symbol? = nil
          as category-symbol in category-menu
          do (case category-symbol
               (number
                (setq number-category-symbol? 'number))
               ((integer non-negative-integer)
                (if (null number-category-symbol?)
                    (setq number-category-symbol? 'integer)))
               (whole-string                        ; string unnecessary as of 3/16/88
                (if (null string-category-symbol?)
                    (setq string-category-symbol? 'string)))
               (left-string
                (setq string-category-symbol? 'quoted-message))
               ((middle-string right-string)
                (setq string-category-symbol? 'end-of-message))
               ((neutral-unit-of-measure singular-unit-of-measure plural-unit-of-measure)
                (setq unit-of-measure-category-symbol? 'unit-of-measure))
               (bad-java-character-literal)
               (t (setq reversed-rows
                        (slot-value-cons-macro
                          (make-category-menu-table-row category-symbol)
                          reversed-rows))))
          finally
            (if unit-of-measure-category-symbol?
                (setq reversed-rows
                      (slot-value-cons
                        (make-category-menu-table-row
                          unit-of-measure-category-symbol?)
                        reversed-rows)))
            (if string-category-symbol?
                (setq reversed-rows
                      (slot-value-cons
                        (make-category-menu-table-row string-category-symbol?)
                        reversed-rows)))
            (if number-category-symbol?
                (setq reversed-rows
                      (slot-value-cons
                        (make-category-menu-table-row number-category-symbol?)
                        reversed-rows)))
            (return (nreverse reversed-rows)))
    'token-menu-format nil
    (or (cdr (assq ':all-category                ; handle per-category check later!
                                        ; see design for this at slot, in PARSE.
                                        ; (MHD 4/17/94)
                   (token-menu-class-per-category-overrides? current-edit-state)))
        'category-menu)
    t))

(defun make-category-menu-table-row (category-symbol)
  (let ((text-cell
          (make-text-cell
            (slot-value-cons-macro
              (twith-output-to-text-string        ; augment copy-symbol-name for this?
                (twrite-string "any ")
                (twrite-symbol category-symbol))        ; hyphens to spaces!?
              nil)
            (choose-token-menu-item-format-per-system-tables t))))
    (change-text-cell-property text-cell 'special-case? 'any-instance)        ; these two could
    (change-text-cell-property text-cell 'choice category-symbol)        ;   be combined
    (slot-value-cons-macro text-cell nil)))

;; Do additional category symbol "aliasing" as needed!

;; Consider incorporating this into put-up-menus.

;; Consider making names for the formats more consistent.



;;; The global-property-name `token-menu-string-to-display-function', if
;;; non-NIL for a category symbol, should be a simple-compiled-function on
;;; (symbol) which returns the string to display for the given symbol, in a
;;; token menu for the category.

(def-global-property-name token-menu-string-to-display-function)

(defun set-token-menu-string-to-display-function (category function?)
  (setf (token-menu-string-to-display-function category)
        function?))

(defun token-menu-string-to-display (category-symbol? symbol do-not-downcase?)
  (cond
    ((and category-symbol?
          (token-menu-string-to-display-function category-symbol?))
     (funcall-simple-compiled-function
       (token-menu-string-to-display-function category-symbol?)
       symbol
       do-not-downcase?))
    ((token-menu-string-to-display-function symbol)
     (funcall-simple-compiled-function
       (token-menu-string-to-display-function symbol)
       symbol
       do-not-downcase?))
    (t (copy-symbol-name-parsably symbol do-not-downcase?))))



;;; The global-property-name `token-menu-string-to-insert-function', if non-NIL
;;; for a category symbol, should be a simple-compiled-function on (symbol)
;;; which returns the string to insert when that symbol is selected in a token
;;; menu for the category.  By default, the string to insert is the same as the
;;; string displayed.

(def-global-property-name token-menu-string-to-insert-function)

(defun set-token-menu-string-to-insert-function (category function?)
  (setf (token-menu-string-to-insert-function category)
        function?))


(defun token-menu-string-to-insert? (category-symbol? symbol)
  (when (and category-symbol?
             (token-menu-string-to-insert-function category-symbol?))
    (funcall-simple-compiled-function
      (token-menu-string-to-insert-function category-symbol?)
      symbol)))




;;; `Make-token-menu-table' creates the menu of tokens which complete a grammar
;;; category.  The list of tokens has already been computed by now, and is in
;;; strings-and-tokens-and-token-sequences.

;;; Each element of strings-and-tokens-and-token-sequences may be
;;; either a simple string, token, or token sequence:
;;;
;;;    "string"
;;;    SYMBOL
;;;    (string-or-symbol ...)  ; a list
;;;
;;; or a two-element list of the form
;;;
;;;    (("string-to-insert") simple-string-token-or-token-sequence-to-display)
;;;
;;; This argument should be a slot value (reclaimable via reclaim-slot-value).
;;;
;;; When the two-element list is supplied, simple-string-token-or-token-
;;; sequence-to-display specifies what to display, whereas the string-to-insert
;;; gets inserted into the editor.  This is handled in the workstation context
;;; operation handler for selection, in MENUS.

;;; The category-symbol? should be the grammar category on whose behalf we are
;;; creating this token menu, if that makes sense.  If the category is COLOR,
;;; then strings-and-tokens-and-token-sequences must be a list of colors; in
;;; this case, the menu items for these colors are displayed with those colors
;;; in the background.

;;; If menu-class? is not specified, token-menu will be used.

;;; If maximum-number-of-choices-to-include-in-menu? is specified, only that many
;;; of the elements (at the front) of strings-and-tokens-and-token-sequences are
;;; included in the menu.

(defun make-token-menu-table
    (strings-and-tokens-and-token-sequences
      do-not-downcase-lone-symbols?
      &optional category-symbol? menu-class?
      maximum-number-of-choices-to-include-in-menu?
      landscape-style-menus?)
  (make-or-reformat-table
    (loop with token-menu-item-format
            = (get-or-make-format-frame
                (choose-token-menu-item-format-per-system-tables))
          as string-or-token-or-token-sequence
             in strings-and-tokens-and-token-sequences
          as choice-string?
             = (cond ((and (consp string-or-token-or-token-sequence)
                           (consp (first string-or-token-or-token-sequence)))
                      (prog1 (first (first string-or-token-or-token-sequence))
                        (setq string-or-token-or-token-sequence
                              (prog1 (second string-or-token-or-token-sequence)
                                (reclaim-slot-value-list
                                  string-or-token-or-token-sequence)))))
                     (t
                      (token-menu-string-to-insert? category-symbol?
                                                    string-or-token-or-token-sequence)))
          as i from 1
          as display-string = (token-menu-string-to-display-for-entry
                                string-or-token-or-token-sequence
                                category-symbol?
                                do-not-downcase-lone-symbols?)
          collect
          (slot-value-list
            (make-text-cell
              (convert-text-string-to-text-macro display-string)
              token-menu-item-format
              (nconc
                (if (eq category-symbol? 'color)
                    (make-text-cell-plist-for-color-background
                      string-or-token-or-token-sequence))
                (if choice-string?
                    (slot-value-list 'choice choice-string?)))))
            into table-rows using slot-value-cons
          until (and maximum-number-of-choices-to-include-in-menu?
                     (>=f i maximum-number-of-choices-to-include-in-menu?))
          finally
            (return
              (if (and landscape-style-menus? table-rows)
                  (loop for row in table-rows
                        nconc row into cells
                        finally
                          (setf (car table-rows) cells)
                          (reclaim-slot-value-list (cdr table-rows))
                          (setf (cdr table-rows) nil)
                          (return table-rows))
                  table-rows)))
    'token-menu-format nil
    (or menu-class?
        (cdr (assq ':all-token                ; handle per-category check later!
                                        ; see design for this at slot, in PARSE.
                                        ; (MHD 4/17/94)
                   (token-menu-class-per-category-overrides? current-edit-state)))
        'token-menu)
    t))

;; The arguments maximum-number-of-choices-to-include-in-menu? and
;; landscape-style-menus? were added while prototyping the kfep conversion
;; choice menus scheme, which at this point has evolved to the point where
;; it does not need them anymore.  In fact, this function is not even used
;; anymore for the kfep conversion choice menus.  Thus, the args could be
;; gotten rid of and the above function arranged to be a bit simpler.  This
;; seems like low priority at this point, and they may turn out to be useful
;; for something else again some day.  (MHD 9/11/90)


;;; The function `token-menu-string-to-display-for-entry' returns the string to
;;; for display the given entry in a token menu, which can be a string, symbol,
;;; or a list.

(defun token-menu-string-to-display-for-entry (string-or-token-or-token-sequence
                                                &optional category-symbol?
                                                do-not-downcase-lone-symbols?)
  (cond
    ((symbolp string-or-token-or-token-sequence)
     (token-menu-string-to-display
       category-symbol?
       string-or-token-or-token-sequence
       do-not-downcase-lone-symbols?))
    ((text-string-p string-or-token-or-token-sequence)
     (copy-text-string  ; need to copy parsably (quoting with @'s?)?
       string-or-token-or-token-sequence))
    ((atom string-or-token-or-token-sequence)
     (twith-output-to-text-string
       (let ((write-symbols-parsably? t)
             (write-symbols-in-lower-case? t))
         (twrite string-or-token-or-token-sequence))))
    (t (twith-output-to-text-string
         (let ((write-symbols-parsably? t)
               (write-symbols-in-lower-case? t))
           (loop for l on string-or-token-or-token-sequence
                 do
             (let* ((token (car l))
                    (display-function?
                      (and (symbolp token) ;; note A.
                           (token-menu-string-to-display-function
                             token)))
                    (text-string-to-display-instead?
                      (and display-function?
                           (funcall-simple-compiled-function
                             display-function?
                             token
                             do-not-downcase-lone-symbols?))))
               (cond
                 (text-string-to-display-instead?
                  (twrite text-string-to-display-instead?)
                  (reclaim-text-string
                    text-string-to-display-instead?))
                 (t (twrite token))))
             (when (cdr l) (twrite-char #.%space))))))))

;; Note A. Sometime shortly after the release of V5r0, a change was introduced
;; that has a subtle but critical effect written up as bug HQ-1529450. I (ddm) have
;; not been able to track down what it was that changed, and instead rh patched
;; the point here where the abort was taking place. The effect of the change
;; was that when numbers appear in grammar rules, the token categories that
;; represent the numbers have fixnums rather than symbols as the value of their
;; token-category fields. That field is accessed when the rules are walked
;; to construct the text of the prompts. See add-menu-items-for-category.






;;;; Keyboard Access to Editor Components



;;; This section defines and implements the following edit-context workstation
;;; event types:
;;;
;;;   `insert-first-token-menu-choice';
;;;   `insert-last-token-menu-choice';
;;;   `select-next-editor-component-group'; and
;;;   `select-previous-editor-component-group'
;;;
;;; It also implements part of the type `space-or-convert/next', defined above.
;;;
;;; ...



(define-editor-ui-command insert-first-token-menu-choice ()
  (setf (menu-choice-index? current-edit-state) 0)
  (convert-current-menu-choice))

(define-editor-ui-command insert-last-token-menu-choice ()
  (setf (menu-choice-index? current-edit-state) -1)
  (convert-current-menu-choice))

(define-editor-ui-command select-next-editor-component-group ()
  (select-next-or-previous-editor-component-group 'next))

(define-editor-ui-command select-previous-editor-component-group ()
  (select-next-or-previous-editor-component-group 'previous))        ; for now the same



(defmacro do-every-token-menu ((token-menu-var) &body body)
  `(loop for ,token-menu-var being each subblock of current-edit-workspace
         when (frame-of-class-p ,token-menu-var 'token-menu)
           do (progn . ,body)))


(defmacro do-every-choice-text-cell-in-token-menu
    ((cell-var) (token-menu) &body body)
  `(loop for row in (table-rows ,token-menu)
         do (loop for ,cell-var in row
                  when (and ,cell-var (not (cell-is-block-p ,cell-var)))
                    do (progn . ,body))))



(defun token-menu-choices-exist-p ()
  (do-every-token-menu (token-menu)
      (do-every-choice-text-cell-in-token-menu (text-cell) (token-menu)
         (return-from token-menu-choices-exist-p t)))
  nil)


(defun count-current-number-of-token-menu-choices ()
  (let ((count 0))
    (do-every-token-menu (token-menu)
      (do-every-choice-text-cell-in-token-menu (text-cell) (token-menu)
        (incff count)))
    count))

(defun convert-current-menu-choice ()
  (let* ((total-count
          (count-current-number-of-token-menu-choices))
         (index
          (if (<f (menu-choice-index? current-edit-state) 0)
              (+f total-count
                  (menu-choice-index? current-edit-state))
              (menu-choice-index? current-edit-state)))
         (count 0))
    ;; The following is somewhat redundant with the action taken by
    ;; insert-token-menu-text-cell-text-at-cursor, but this is now needed here,
    ;; at least, to prevent the index from remaining non-nil if there are no (0,
    ;; zip) menus at all, which would result in a "sticky" selection of the menu
    ;; choices.  That was a bug in 4.0 Beta Rev. 0.  (MHD 10/27/94)
    (setf (menu-choice-index? current-edit-state) nil)
    (do-every-token-menu (token-menu)
      (do-every-choice-text-cell-in-token-menu (text-cell) (token-menu)
           (when (=f (modf index total-count) count)
           (insert-token-menu-text-cell-text-at-cursor text-cell token-menu)
           (return-from convert-current-menu-choice))
         (incff count)))))


(defun highlight-or-unhighlight-selected-token-menu-choice (unhighlight-case?)
  (let* ((total-count
          (count-current-number-of-token-menu-choices))
         (index
          (if (<f (menu-choice-index? current-edit-state) 0)
              (+f total-count
                  (menu-choice-index? current-edit-state))
              (menu-choice-index? current-edit-state)))
         (count 0))
    (do-every-token-menu (token-menu)
      (do-every-choice-text-cell-in-token-menu (text-cell) (token-menu)
         (when (=f (modf index total-count) count)
           (highlight-or-unhighlight-token-menu-text-cell
             token-menu text-cell unhighlight-case?)
           (return-from highlight-or-unhighlight-selected-token-menu-choice t))
         (incff count)))))




(defun insert-token-menu-text-cell-text-at-cursor (cell token-menu)
  (let* ((choice? (getf (text-cell-plist cell) 'choice))
         (text-string
          (or (if choice? (copy-text-string choice?))
              (convert-text-to-text-string (text? cell)))))
    ;; Alt 1: stay in this mode.  Users can get out with another (control
    ;; [shift] tab).
    ;; (setf (menu-choice-index? current-edit-state) 0)
    ;; Alt 2: leave this mode whenever it's used.  Problem -- you then
    ;; still need to leave this mode if you move the cursor, or do
    ;; many other actions.
    (setf (menu-choice-index? current-edit-state) nil)
    ;; in some cases, modes?
    (insert-text-string-at-cursor
      text-string
      (get-slot-value token-menu 'replace-fragments-on-sides?)
      (get-slot-value token-menu 'handle-spaces-intelligently?)
      nil nil
      (get-slot-value token-menu 'replace-entire-text?))
    (reclaim-text-string text-string)))

;; Note: we could have the accessors for the scrap/token menus define above, and
;; then get rid of get-slot-value.


(defun highlight-or-unhighlight-token-menu-text-cell
    (token-menu cell unhighlight-case?)
  (highlight-or-unhighlight-cell
    cell token-menu
    'light-gray                                ; foreground  ??
                                        ; color ignored at present -- may be
                                        ; hard to fix.  (MHD 4/11/94)
    unhighlight-case?
    ;; 'text-region  ; better?  makes a minimal box around it
    ))






(defun select-next-token-menu-choice (left-or-right)
  (highlight-or-unhighlight-selected-token-menu-choice t)
  (incff (menu-choice-index? current-edit-state)
         (case left-or-right
           (left -1)
           (t 1)))
  (highlight-or-unhighlight-selected-token-menu-choice nil))



(defun select-next-or-previous-editor-component-group (next-or-previous)
  (declare (ignore next-or-previous))        ; for now the same
  (cond
    ((menu-choice-index? current-edit-state)
     (highlight-or-unhighlight-selected-token-menu-choice t)
     (setf (menu-choice-index? current-edit-state) nil)
     ;; now back editing text of editor
     )
    (t
     (setf (menu-choice-index? current-edit-state) 0)
     (highlight-or-unhighlight-selected-token-menu-choice nil)
     ;; not editing text of editor
     )))


;; Notes:  (MHD 4/11/94)

;; These will be less simplistic when we add the subcommand menu (cancel, undo,
;; etc.), the any-choice (category) menu, maybe the KFEP choices, and perhaps
;; other choices, a bit later! (MHD 4/10/94)

;; Bug: the selection of choices appears to be random when moving the cursor
;; through the text and displaying menu when there's an index selected.  Getting
;; rid of the index would help, but then you'd have to reselect the menu
;; component, which doesn't feel right.  Needs work.

;; To handle the category menu, consider selecting it just when there aren't any
;; token choices.  What about a way to select it otherwise?  Defer?  What about
;; selecting the menu in the category instance menu workspace -- count it as one
;; of the token menus?





;;;; Parse Constant Designation



;;; `read-attribute-name-from-text-string' - see read-attribute-name-from-text-string-1

(defmacro read-attribute-name-from-text-string (text-string
                                                 &optional (start-index? nil)
                                                 (end-index? nil))
  `(read-attribute-name-from-text-string-1 ,text-string ,start-index? ,end-index?))




;;; The function parse-constant-designation takes a text string and returns a
;;; parse of the constant designation contained within it.  If this string does
;;; not contain a valid constant designation, then nil is returned.

;;; Accepts parses of the form:
;;; <constant-designation> :==
;;;    <name> |
;;;    (the <attribute> of <constant-designation>)

;;; Note that this function returns a designation that is a symbol or a list
;;; made of slot-value-conses.  The list is owned by the caller and should be
;;; reclaimed.  Also, note that this function does not test for a legal
;;; text-string.  This should have already been tested, if necessary, using
;;; legal-text-p.

(defun parse-constant-designation (possible-designation-text-string start-index)
  (let ((parse? nil)
        (class? nil))
    (multiple-value-bind (symbol? end-index?)
        (read-symbol-from-text-string possible-designation-text-string start-index)
      (cond
        ((null symbol?)
         nil)
        ((null end-index?)
         symbol?)
        (t
         (setq parse? symbol?)
         (multiple-value-setq (symbol? end-index? class?)
           (read-attribute-name-from-text-string
             possible-designation-text-string end-index?)
;           (read-symbol-from-text-string
;             possible-designation-text-string end-index?)
           )
         (cond
           ((null symbol?)
            parse?)
           ((null end-index?)
            ;; 2 symbols - illegal
            nil)
           ((not (eq parse? 'the))
            ;; error - <should-be-THE-but-isn't> FOO of ...
            nil)
           (t
            (when class?
              (setq symbol?
                    (slot-value-list 'class-qualified-name class? symbol?)))
            (setq parse? (slot-value-list parse? symbol?))
            ;; go past OF:
            (multiple-value-setq (symbol? end-index?)
              (read-symbol-from-text-string
                possible-designation-text-string end-index?))
            (cond
              ((null end-index?)
               ;; error - the FOO of <nothing-there>
               nil)
              ((not (eq symbol? 'of))
               ;; error - the FOO <should-be-OF-but-isn't>
               nil)
              (t
               ;; recur for designation
               (let ((subparse?
                       (parse-constant-designation
                         possible-designation-text-string end-index?)))
                 (cond
                   ((null subparse?)
                    ;; error - the FOO of <nothing-there>
                    nil)
                   (t
                    (nconc parse? (slot-value-list subparse?))))))))))))))


;; This is not really token-parsing, but there is a need to support really-fast
;; constant-designation parsing, so it has been put into this section.  This is
;; only used, at present, by the GFI facility.  Written by MHD and CPM, 10/8/92,
;; to meet the performance needs of GFI.

;; This doesn't handle rejection of reserved words, e.g., "the FOO of OF",
;; which the full parser would reject!

;; This doesn't handle rejection of (some) junk at the end, e.g., extraneous
;; punctuation, e.g., "XXX,,,," returns XXX, but would be rejected as a
;; designation by the full parser!

;; This function is necessary because other parsing functions, such as
;; parse-text-for-slot, binds a number of special variables which is causing
;; efficiency problems in GFI.  Maybe, parse-text-for-slot should be rewritten
;; to remove the editor-specific code and, therefore, some bindings to special
;; variables.  See get-next-token-from-text-if-available which can optionally be
;; called from an edited context.

;; Note that read-symbol-from-text-string, read-from-text-string, and get-next-
;; token-from-text-if-available return multiple values.  Also, twith-output-to-
;; then-use-of-text-string is used and binds special variables.  These may be
;; efficiency concerns.



;;;; Def-tokenizer


;; read-fixnum-from-string is already defined in UTILITIES3

;; jh, 11/20/91.  We abstract def-tokenizer in hopes it might be useful in the
;; future, to make other tokenization schemes more maintainable, and perhaps to
;; add some new ones (such as filename completion).

;; jh, 8/29/95.  Extended def-tokenizer for IDL.

(defun-for-macro get-node-alist-for-def-tokenizer (nodes)
  (loop with next-component-cons? = (copy-list nodes)
        for next-component = (car next-component-cons?)
        with nodes = nil
        with tail-of-node
        while next-component-cons?
        do
    (cond
      ((equal '(finish) next-component)
       (push (cons next-component (cdr next-component-cons?)) nodes)
       (loop-finish))
      ((consp next-component)
       (let ((node (list next-component)))
         (push node nodes)
         (setq tail-of-node (last node))
         (setq next-component-cons? (cdr next-component-cons?))))
      (t (let ((category next-component))
           (if (and (eq category '->)
                    (consp (cddr next-component-cons?)))
               (let* ((next-node (cadr next-component-cons?))
                      (next-tail (list (list 'else next-node))))
                 (setf (cdr tail-of-node) next-tail)
                 (setf tail-of-node next-tail)
                 (setq next-component-cons? (cddr next-component-cons?)))
               (let* ((arrow (cadr next-component-cons?))
                      (next-node (caddr next-component-cons?))
                      (next-tail (list (list category next-node))))
                 (unless (eq '-> arrow)
                   (error
                     "DEF-TOKENIZER: malformed syntax around node ~a"
                     (caaar nodes)))
                 (setf (cdr tail-of-node) next-tail)
                 (setf tail-of-node next-tail)
                 (setq next-component-cons? (cdddr next-component-cons?)))))))
        finally (return (nreverse nodes))))

(defun-for-macro get-state-holding-let-specs-for-def-tokenizer (node-alist)
  (loop for (names-and-directives) in node-alist
        append
        (loop with names-and-directives-cons? = names-and-directives
              while names-and-directives-cons?
              for var-name = (car names-and-directives-cons?)
              for var-directive? = (cadr names-and-directives-cons?)
              for unstore-p = (eq var-directive? :unstore)
              do (setq names-and-directives-cons?
                       (cddr names-and-directives-cons?))
              when (and var-directive? (not unstore-p))
                collect (case var-directive?
                          (:count `(,var-name 0))
                          (:read-integer `(,var-name 0))
                          (otherwise `(,var-name nil)))
              when unstore-p
                do (pop names-and-directives-cons?)
              when (let ((maybe-additional-collect-directive
                           (car names-and-directives-cons?)))
                     (or (eq maybe-additional-collect-directive :until)
                         (numberp maybe-additional-collect-directive)))
                do (setq names-and-directives-cons?
                         (cddr names-and-directives-cons?)))))

(defun-for-macro get-state-saving-forms-for-def-tokenizer
    (node-name names-and-directives)
  (loop with names-and-directives-cons? = names-and-directives
        while names-and-directives-cons?
        for var-name = (car names-and-directives-cons?)
        for var-directive? = (cadr names-and-directives-cons?)
        do (setq names-and-directives-cons?
                 (cddr names-and-directives-cons?))
        unless (eq var-name node-name)
          collect var-name
        when var-directive?
          collect
          (case var-directive?
            (:count `(incff ,var-name))
            (:flag `(setq ,var-name t))
            (:store `(setq ,var-name previous-char))
            (:unstore `(setq ,(pop names-and-directives-cons?) nil))
            (:push `(token-push previous-char ,var-name))
            (:collect
             (let ((maybe-additional-collect-directive
                     (car names-and-directives-cons?)))
               (cond
                 ((eq maybe-additional-collect-directive :until)
                  (setq names-and-directives-cons?
                        (cddr names-and-directives-cons?))
                  `(collect-into-var previous-char ,var-name))
                 ((numberp maybe-additional-collect-directive)
                  (let ((overvar-name (cadr names-and-directives-cons?)))
                    (setq names-and-directives-cons?
                          (cddr names-and-directives-cons?))
                    `(collect-into-var
                       previous-char
                       ,var-name
                       ,overvar-name
                       ,maybe-additional-collect-directive)))
                 (t `(collect-into-var previous-char ,var-name)))))
            (:read-integer
             `(read-integer-into-var previous-char ,var-name)))))

(defun-for-macro get-self-destined-labels-for-def-tokenizer
    (names-and-directives)
  (loop with names-and-directives-cons? = names-and-directives
        while names-and-directives-cons?
        for var-name = (car names-and-directives-cons?)
        for var-directive = (cadr names-and-directives-cons?)
        do (setq names-and-directives-cons?
                 (cddr names-and-directives-cons?))
        collect var-name
        when (eq :unstore var-directive)
          do (pop names-and-directives-cons?)
        when (let ((maybe-additional-collect-directive
                     (car names-and-directives-cons?)))
               (or (eq maybe-additional-collect-directive :until)
                   (numberp maybe-additional-collect-directive)))
          do (setq names-and-directives-cons?
                   (cddr names-and-directives-cons?))))

(defun-for-macro get-node-traversal-cleanup-forms-for-def-tokenizer
    (names-and-directives next-node)
  (loop with self-destined-labels
          = (get-self-destined-labels-for-def-tokenizer
              names-and-directives)
        with names-and-directives-cons? = names-and-directives
        while names-and-directives-cons?
        for var-name = (car names-and-directives-cons?)
        for var-directive = (cadr names-and-directives-cons?)
        for collect-p = (eq :collect var-directive)
        do (setq names-and-directives-cons?
                 (cddr names-and-directives-cons?))
        with cleanup-forms = nil
        do
    (cond
      ((eq :unstore var-directive)
       (pop names-and-directives-cons?))
      ((eq :collect var-directive)
       (let* ((maybe-additional-collect-directive
                (car names-and-directives-cons?))
              (suppress-collection-label?
                (and (eq maybe-additional-collect-directive :until)
                     (cadr names-and-directives-cons?)))
              (collecting-into-overvar-p
                (numberp maybe-additional-collect-directive)))
         (when (or suppress-collection-label? collecting-into-overvar-p)
           (setq names-and-directives-cons?
                 (cddr names-and-directives-cons?)))
         (cond
           ((and suppress-collection-label?
                 (eq next-node suppress-collection-label?))
            (push `(clean-up-collect-var ,var-name) cleanup-forms))
           ((or suppress-collection-label?
                (memq next-node self-destined-labels))
            (push `(when (end-of-character-stream-p)
                     (clean-up-collect-var ,var-name))
                  cleanup-forms))
           (t (push `(clean-up-collect-var ,var-name) cleanup-forms))))))
        finally (return (reverse cleanup-forms))))

(defun-for-macro get-node-traversal-forms-for-def-tokenizer
    (destinations character-categories names-and-directives first-node-p)
  (loop for (match next-node) in destinations
        for cleanup-forms
            = (get-node-traversal-cleanup-forms-for-def-tokenizer
                names-and-directives
                next-node)
        if (eq match 'else)
          append
          `(,@cleanup-forms (advance ,next-node))
        else
          collect
          `(when ,(if (cddr (assq match character-categories))
                      `(wide-character-member this-char ,match)
                      `(eqlw this-char ,match))
             ,@cleanup-forms
             (advance ,next-node ,first-node-p))))

(defun-for-macro get-finish-forms-for-def-tokenizer
    (names-and-directives destinations)
  (if (loop for (match) in destinations thereis (eq match 'else))
      nil
      `(,@(loop with names-and-directives-cons? = names-and-directives
                while names-and-directives-cons?
                for var-name = (car names-and-directives-cons?)
                for var-directive = (cadr names-and-directives-cons?)
                do (setq names-and-directives-cons?
                         (cddr names-and-directives-cons?))
                when (eq :collect var-directive)
                  collect `(clean-up-collect-var ,var-name)
                when (let ((maybe-additional-collect-directive
                             (car names-and-directives-cons?)))
                       (or (eq maybe-additional-collect-directive :until)
                           (numberp maybe-additional-collect-directive)))
                  do (setq names-and-directives-cons?
                           (cddr names-and-directives-cons?))
                when (eq :unstore var-directive)
                  do (pop names-and-directives-cons?))
          (go finish))))

(defun-for-macro get-internal-macrolet-specs-for-def-tokenizer ()
  `((collect-into-var (char collect-var &optional overvar? count)
      (avoiding-variable-capture (&aux last-cons new-cons first-cons)
        `(progn
           (cond
             (,collect-var
              (let ((,last-cons (first ,collect-var))
                    (,new-cons (token-list ,char)))
                (setf (cdr ,last-cons) ,new-cons)
                (setf (first ,collect-var) ,new-cons)))
             (t (let ((,first-cons (token-list ,char)))
                  (setq ,collect-var
                        (token-list ,first-cons ,first-cons ,count)))))
           ,@(if overvar?
                 `((when (<=f (decff (third ,collect-var)) 0)
                     (clean-up-collect-var ,collect-var)
                     (setq previous-char ,collect-var)
                     (setq ,collect-var nil)
                     (go ,overvar?)))
                 nil))))
    (clean-up-collect-var (collect-var)
      (avoiding-variable-capture (&aux collected-list)
        `(when ,collect-var
           (let ((,collected-list (second ,collect-var)))
             (reclaim-token-list ,collect-var)
             (setq ,collect-var ,collected-list)))))
    (read-integer-into-var (char integer-var)
      `(setq ,integer-var
             (+f (*f ,integer-var 10) (or (digit-char-pw ,char) 0))))))

(defmacro def-tokenizer
    (name
      defun-args
      character-accessing-macrolet-specs
      character-categories
      &rest nodes)
  (let ((name-of-tokenizer (intern (format nil "TOKENIZE-~a" name)))
        (node-alist (get-node-alist-for-def-tokenizer nodes)))
    `(defun ,name-of-tokenizer ,defun-args
       (macrolet (,@character-accessing-macrolet-specs
                  ,@(get-internal-macrolet-specs-for-def-tokenizer))
         (let* (,@(loop for (category . elements) in character-categories
                        if (cdr elements)
                          collect `(,category ',elements)
                        else
                          collect `(,category ',(car elements)))
                  ,@(get-state-holding-let-specs-for-def-tokenizer node-alist)
                  (this-char (first-char))
                  (this-index start-index)
                  (previous-char nil))
           (tagbody
              ,@(loop for (names-and-directives . destinations)
                          in node-alist
                      for node-name = (first names-and-directives)
                      for first-node-p = t then nil
                      if (eq 'finish node-name)
                        append
                        `(unread-and-finish
                          (unread)
                          finish
                          (setq final-index this-index)
                          (return-from ,name-of-tokenizer
                            (progn ,@destinations)))
                      else
                        append
                        `(,node-name
                            ,@(get-state-saving-forms-for-def-tokenizer
                                node-name
                                names-and-directives)
                            ,@(get-node-traversal-forms-for-def-tokenizer
                                destinations
                                character-categories
                                names-and-directives
                                first-node-p)
                            ,@(get-finish-forms-for-def-tokenizer
                                names-and-directives
                                destinations)))))))))




;;;; Numeric Readers

;; Notes by ML, 5/9/90:
;;
;; (1) There is temporary bignum context being used here.  Bignums
;; can be created by the call to read-number-without-exponent and
;; exist transiently.  This will not be fixed for Beta 3, but should
;; be fixed for 2.0 release.
;;
;; (2) A bug in read-number-without-exponent which caused it not to
;; regognize negative bignums when read was fixed by MHD, yesterday.  It
;; caused an error in reading on all non-LISP implementations, and caused
;; crashes on some.
;;
;; (3) The method of manufacturing a float, which is to multiply the float
;; read as "ddd.dddd" by the (expt 10.0 e) does not work for small floats
;; where the latter is to small to be a normalized float, but the product
;; is within reasonable range.  Such cases are detectable by the size of the
;; exponent.  A solution is to perform the multiplication in two stages,
;; taking care to associate from the left.  As noted by LH in the code, the
;; testing for within range which uses a base 10 exponent, is not precise
;; enough.  Getting very close to the actual values of most-positive and
;; least-positive gensym float are a bit tricky.  (Note that G2 now refuses
;; unnormalized numbers, but that this will change in the future.)

;; jh, 11/18/91.  The G2 reader for floating point numbers has less precision than
;; it could.  Specifically, it stops reading at eight digits of float, although
;; the internal Chestnut representation is capable of fifteen.  Our first idea was
;; to use the standard C library function sscanf to provide the added precision.

;; The wrinkle in this idea is that non-ANSI-compliant C implementations make no
;; guarantee about what sscanf will return if it is given a string to read which
;; would result in a float larger or smaller than could be represented (see
;; Harbison & Steele, 2nd Edition, p 313).  So we have to "preflight" the string
;; before we hand it to sscanf.  This preflighting starts by counting digits and
;; assembling the exponent (if any).  If the number of digits is too great, we can
;; quickly return an overflow marker.  If the number of digits is exactly at the
;; boundary, we have to do a more detailed comparison, matching the digits to be
;; read against a cached string representing the digits of the float at the
;; boundary (either the largest positive float or the smallest positive normalized
;; float).





;; jh, 12/6/91.  Hardwired values in all system-variables containing digit counts
;; and extremal strings for float readers, since the C compilers on some platforms
;; seem to create unreliable code when trying to arrange computations near largest
;; or smallest float.  The corresponding system-variables for fixnums work
;; correctly, so we will still compute these on initialization as we should.

;; jh, 4/7/92.  Conditionalized most-lefthand-float-digits by operating system,
;; since VMS does not adhere to the IEEE standard for double floats.

(defvar most-lefthand-float-digits
        (if (eq g2-operating-system 'vms)
            308
            309))

;; jh, 4/7/92.  Most-righthand-float-zeros need not be conditionalized by
;; operating system, since the VMS limit is smaller than the IEEE limit, and G2
;; adheres to the IEEE standard.

(defvar most-righthand-float-zeros 307)



(defun initialize-most-fixnum-digits ()
  (ceiling (log most-positive-fixnum 10)))

(defvar most-fixnum-digits
  (initialize-most-fixnum-digits))


;; jh, 12/13/91.  Made digits-of-most-positive-fixnum-as-string and
;; digits-of-most-negative-fixnum-as-string be the same after noting a
;; problem in negative fixnum overflow in Chestnut.

;; - This restriction removed on 6/12/00 since it's wrong (most-positive-fixnum
;; = 2^29 - 1 = 536870911 , while most-negative-fixnum = -2^29 = -536870912)
;; and this problem with Chestnut was presumably fixed in 1992. - jpg 6/12/00

;; jh, 12/13/91.  As well, none of the float-reading parameters need to be
;; system variables.

(defun initialize-digits-of-extremal-fixnum-as-string ()
  (tformat-text-string "~d" most-positive-fixnum))

(defvar digits-of-extremal-fixnum-as-string
  (initialize-digits-of-extremal-fixnum-as-string))

(defun initialize-digits-of-most-positive-fixnum-as-string ()
  digits-of-extremal-fixnum-as-string)

(defvar digits-of-most-positive-fixnum-as-string
  (initialize-digits-of-most-positive-fixnum-as-string))

(defun initialize-digits-of-most-negative-fixnum-as-string ()
  ;; most-negative-fixnum = -2^29 = -536870912
  ;; wired-in, at read time, so as not to create a bignum. - jpg 6/12/00
  (stringw (format nil "~d" (- most-negative-fixnum))))

(defvar digits-of-most-negative-fixnum-as-string
  (initialize-digits-of-most-negative-fixnum-as-string))



;; jh, 4/7/92.  Conditionalized digits-of-largest-float-as-string by operating
;; system, since VMS does not adhere to the IEEE standard for double floats.
;; For future reference, the digits for the VMS operating system were obtained
;; from sys$library:float.h and the digits for the IEEE standard were obtained
;; from /bt/ab/runtime/c/config.h, a Chestnut kernel file.

(defvar digits-of-largest-float-as-string
        (if (eq g2-operating-system 'vms)
            #w"898846567431157854"
            #w"17976931348623158"))


;; jh, 4/7/92.  Digits-of-smallest-normalized-float-as-string need not be
;; conditionalized by operating system, since the VMS limit is smaller than the
;; IEEE limit, and G2 adheres to the IEEE standard.

(defvar digits-of-smallest-normalized-float-as-string #w"22250738585072015")

(def-tokenizer number-from-user (string start-index final-index)

    ((first-char () `(charw string start-index))
     (end-of-character-stream-p () `(=f this-index final-index))
     (advance (next-node &optional start-node-p)
       (declare (ignore start-node-p))
       (avoiding-variable-capture (&aux new-index inner-index-p)
         `(let* ((,new-index (1+f this-index))
                 (,inner-index-p (<f ,new-index final-index)))
            (cond
              ((or ,inner-index-p (=f ,new-index final-index))
               (setq this-index ,new-index)
               (setq previous-char this-char)
               (setq this-char
                     (and ,inner-index-p (charw string this-index)))
               (go ,next-node))
              (t (go finish))))))
     (unread () nil))

    ((sign #.%\+ #.%\-)
     (zero #.%\0)
     (nonzero #.%\1 #.%\2 #.%\3 #.%\4 #.%\5 #.%\6 #.%\7 #.%\8 #.%\9)
     (digit #.%\0 #.%\1 #.%\2 #.%\3 #.%\4 #.%\5 #.%\6 #.%\7 #.%\8 #.%\9)
     (point #.%\.)
     (exponent #.%\e #.%\E)
     (long-suffix #.%\L))

  (start-tokenizing) ;Chestnut doesn't work with "start" label (see below)
  sign -> sign-of-fraction
  zero -> leading-lefthand-zeros
  nonzero -> number-of-lefthand-digits
  point -> decimal-point-present-p
  exponent -> exponent-present-p

  (sign-of-fraction :store)
  zero -> leading-lefthand-zeros
  nonzero -> number-of-lefthand-digits
  point -> decimal-point-present-p
  exponent -> exponent-present-p

  (leading-lefthand-zeros)
  zero -> leading-lefthand-zeros
  nonzero -> number-of-lefthand-digits
  point -> decimal-point-present-p
  exponent -> exponent-present-p

  (number-of-lefthand-digits :count
   lefthand-digits :collect)
  digit -> number-of-lefthand-digits
  point -> decimal-point-present-p
  exponent -> exponent-present-p
  long-suffix -> read-as-long?

  (decimal-point-present-p :flag)
  zero -> number-of-righthand-leading-zeros
  nonzero -> righthand-digits
  exponent -> exponent-present-p

  (number-of-righthand-leading-zeros :count)
  zero -> number-of-righthand-leading-zeros
  nonzero -> righthand-digits
  exponent -> exponent-present-p

  (righthand-digits :collect)
  digit -> righthand-digits
  exponent -> exponent-present-p

  (exponent-present-p :flag)
  sign -> sign-of-exponent
  zero -> leading-zeros-of-exponent
  nonzero -> exponent-integer

  (sign-of-exponent :store)
  zero -> leading-zeros-of-exponent
  nonzero -> exponent-integer

  (leading-zeros-of-exponent)
  zero -> leading-zeros-of-exponent
  nonzero -> exponent-integer

  (exponent-integer :read-integer)
  digit -> exponent-integer
  
  (read-as-long? :flag)

  (finish)
  (multiple-value-bind (number? type?)
      (read-possibly-out-of-bounds-numeric-token
        string
        start-index
        final-index
        sign-of-fraction
        number-of-lefthand-digits
        lefthand-digits
        decimal-point-present-p
        number-of-righthand-leading-zeros
        righthand-digits
        exponent-present-p
        sign-of-exponent
        exponent-integer
        read-as-long?
        )
    (when lefthand-digits
      (reclaim-token-list lefthand-digits))
    (when righthand-digits
      (reclaim-token-list righthand-digits))
    (values number? type?)))

#+development
(defparameter test-suite-for-tokenize-number-from-user
  '(
    ((tokenize-number-from-user #w"1" 0 1)        (1 FIXNUM))
    ((tokenize-number-from-user #w"1x" 0 2)       (1 FIXNUM))
    ((tokenize-number-from-user #w"12" 0 2)       (12 FIXNUM))
    ((tokenize-number-from-user #w"12x" 0 3)      (12 FIXNUM))
    ((tokenize-number-from-user #w"x1" 0 2)       (NIL FIXNUM))
    ((tokenize-number-from-user #w"1." 0 2)       (1.0 FLOAT))
    ((tokenize-number-from-user #w"1.x" 0 3)      (1.0 FLOAT))
    ((tokenize-number-from-user #w"21." 0 3)      (21.0 FLOAT))
    ((tokenize-number-from-user #w"21.x" 0 4)     (21.0 FLOAT))
    ((tokenize-number-from-user #w"1.e" 0 3)      (1.0 FLOAT))
    ((tokenize-number-from-user #w"1.e1" 0 4)     (10.0 FLOAT))
    ((tokenize-number-from-user #w"21.e1" 0 5)    (210.0 FLOAT))
    ((tokenize-number-from-user #w"1.e1x" 0 5)    (10.0 FLOAT))
    ((tokenize-number-from-user #w"1.2e1x" 0 5)   (12.0 FLOAT))
    ((tokenize-number-from-user #w"1.2e1x" 0 6)   (12.0 FLOAT))
    ((tokenize-number-from-user #w"1.2e1" 0 5)    (12.0 FLOAT))
    ((tokenize-number-from-user #w"1.2e333" 0 7)  (OVERFLOW NIL))
    ((tokenize-number-from-user #w".2e333" 0 6)   (OVERFLOW NIL))
    ((tokenize-number-from-user #w".2e300" 0 6)   (2.0E299 FLOAT))
    ((tokenize-number-from-user #w".2e30" 0 5)    (2.0E29 FLOAT))
    ((tokenize-number-from-user #w".2" 0 2)       (0.2 FLOAT))
    ((tokenize-number-from-user #w"0.2" 0 3)      (0.2 FLOAT))
    ((tokenize-number-from-user #w"21.e10" 0 6)   (2.1E11 FLOAT))
    ((tokenize-number-from-user #w"-1" 0 2)       (-1 FIXNUM))
    ((tokenize-number-from-user #w"-1x" 0 3)      (-1 FIXNUM))
    ((tokenize-number-from-user #w"-12" 0 3)      (-12 FIXNUM))
    ((tokenize-number-from-user #w"-12x" 0 4)     (-12 FIXNUM))
    ((tokenize-number-from-user #w"-x1" 0 3)      (0 FIXNUM)) ;is this correct?
    ((tokenize-number-from-user #w"-1." 0 3)      (-1.0 FLOAT))
    ((tokenize-number-from-user #w"-1.x" 0 4)     (-1.0 FLOAT))
    ((tokenize-number-from-user #w"-21." 0 4)     (-21.0 FLOAT))
    ((tokenize-number-from-user #w"-21.x" 0 5)    (-21.0 FLOAT))
    ((tokenize-number-from-user #w"-1.e" 0 4)     (-1.0 FLOAT))
    ((tokenize-number-from-user #w"-1.e1" 0 5)    (-10.0 FLOAT))
    ((tokenize-number-from-user #w"-21.e1" 0 6)   (-210.0 FLOAT))
    ((tokenize-number-from-user #w"-1.e1x" 0 6)   (-10.0 FLOAT))
    ((tokenize-number-from-user #w"-1.2e1x" 0 6)  (-12.0 FLOAT))
    ((tokenize-number-from-user #w"-1.2e1x" 0 7)  (-12.0 FLOAT))
    ((tokenize-number-from-user #w"-1.2e1" 0 6)   (-12.0 FLOAT))
    ((tokenize-number-from-user #w"-1.2e333" 0 8) (OVERFLOW NIL))
    ((tokenize-number-from-user #w"-.2e333" 0 7)  (OVERFLOW NIL))
    ((tokenize-number-from-user #w"-.2e300" 0 7)  (-2.0E299 FLOAT))

    ((tokenize-number-from-user #w"-.2e30" 0 6)   (-2.0E29 FLOAT))
    ((tokenize-number-from-user #w"-.2" 0 3)      (-0.2 FLOAT))
    ((tokenize-number-from-user #w"-0.2" 0 4)     (-0.2 FLOAT))
    ((tokenize-number-from-user #w"-21.e10" 0 7)  (-2.1E11 FLOAT))

    ;; New: test for handling of unary +, which is accepted by G2's QUANTITY
    ;; function but is not accepted by G2's editor (i.e., not accepted by G2's
    ;; editor's numeric token recognizer). (MHD 10/28/96)
    ((tokenize-number-from-user #w"+.2e30" 0 6)   (2.0E29 FLOAT))
    ((tokenize-number-from-user #w"+.2" 0 3)      (0.2 FLOAT))
    ((tokenize-number-from-user #w"+0.2" 0 4)     (0.2 FLOAT))
    ((tokenize-number-from-user #w"+21.e10" 0 7)  (2.1E11 FLOAT))
    ((tokenize-number-from-user #w"+123" 0 4)     (123 FIXNUM))

    ((tokenize-number-from-user #w"1L" 0 2)       (1 LONG))
    ((tokenize-number-from-user #w"1Lx" 0 3)      (1 LONG))
    ((tokenize-number-from-user #w"12L" 0 3)      (12 LONG))
    ((tokenize-number-from-user #w"12Lx" 0 4)     (12 LONG))
    ((tokenize-number-from-user #w"Lx1" 0 3)      (NIL FIXNUM))
    ((tokenize-number-from-user #w"-1L" 0 3)      (-1 LONG))
    ((tokenize-number-from-user #w"-1Lx" 0 4)     (-1 LONG))
    ((tokenize-number-from-user #w"-12L" 0 4)     (-12 LONG))
    ((tokenize-number-from-user #w"-12Lx" 0 5)    (-12 LONG))
    ((tokenize-number-from-user #w"-Lx1" 0 4)     (0 FIXNUM))
    ((tokenize-number-from-user #w"+123L" 0 5)    (123 LONG))
    ((tokenize-number-from-user #w"9223372036854775807L" 0 25) (9223372036854775807 LONG))
    ((tokenize-number-from-user #w"1152921504606846975L" 0 25) (1152921504606846975 LONG))
    ((tokenize-number-from-user #w"-9223372036854775808L" 0 25) (-9223372036854775808 LONG))
    ((tokenize-number-from-user #w"-1152921504606846976L" 0 25) (-1152921504606846976 LONG))
    ))

#+development
(defun validate-tokenize-number-from-user ()
  (loop for (tokenize-form expected-result)
            in test-suite-for-tokenize-number-from-user
        with success-p = t
        do
    (let ((obtained-result (eval `(multiple-value-list ,tokenize-form))))
      (unless (equal obtained-result expected-result)
        (setq success-p nil)
        (format t "~&~s should have yielded ~s,~% not ~s~%"
                tokenize-form
                expected-result
                obtained-result)))
    finally (return success-p)))

;; jh per ac & bah, 11/25/91.  Changed "start" label in the def-tokenizer for
;; number-from-user to "start-tokenizing".  Chestnut upcases tagbody labels (we
;; presume for readability), but that conflicts with the upcase START macro which
;; expands into the :start keyword.  We will notify Chestnut of this problem soon.

;; Fixed a leak of token-conses in the number-from-user tokenizer.  It was
;; failing to reclaim the intermediate lists of digit characters it generated.


(defun digit-string-overflowed-by-digit-char-lists
       (digit-string lefthand-digit-char-list righthand-digit-char-list)
  (let ((last-index-in-digit-string (1-f (lengthw digit-string)))
        (index -1))
    (and (loop for digit-char-cons on lefthand-digit-char-list
               for char-list-element = (car digit-char-cons)
               do (incff index)
               when (char>w (charw digit-string index) char-list-element)
                 do (return-from digit-string-overflowed-by-digit-char-lists
                      nil)
               when (char<w (charw digit-string index) char-list-element)
                 do (return-from digit-string-overflowed-by-digit-char-lists
                      t)
               ;; more typed-in chars remain after match chars
               when (=f index last-index-in-digit-string)
                 do (return-from digit-string-overflowed-by-digit-char-lists
                      (or (cdr digit-char-cons)
                          righthand-digit-char-list))
               ;; outer "and" form will continue with righthand list
               finally (return t))
         (loop for digit-char-cons on righthand-digit-char-list
               for char-list-element = (car digit-char-cons)
               do (incff index)
               when (char>w (charw digit-string index) char-list-element)
                 do (return nil)
               when (char<w (charw digit-string index) char-list-element)
                 do (return t)
               ;; more typed-in chars remain after match chars
               when (=f index last-index-in-digit-string)
                 do (return (cdr digit-char-cons))
               ;; more match chars remain after typed-in chars
               finally (return nil)))))



#+development
(defvar digit-string-overflowed-by-digit-char-lists-validation-suite
  (copy-tree-changing-strings-to-text-strings
  '(
    (("16777215" "1" "") nil)
    (("16777215" "167" "") nil)
    (("16777215" "16777215" "") nil)
    (("16777215" "16777216" "") t)
    (("16777215" "167772155" "") t)

    (("22250738585072014" "" "22250738585072014") nil)
    (("22250738585072014" "" "2225073858507201") nil)
    (("22250738585072014" "" "222507385850720145") t)

    (("22250738585072014" "2" "2250738585072014") nil)
    (("22250738585072014" "2" "225073858507201") nil)
    (("22250738585072014" "2" "22507385850720145") t)

    (("22250738585072014" "22" "250738585072014") nil)
    (("22250738585072014" "22" "25073858507201") nil)
    (("22250738585072014" "22" "2507385850720145") t)

    (("17976931348623157" "" "17976931348623157") nil)
    (("17976931348623157" "" "1797693134862315") nil)
    (("17976931348623157" "" "179769313486231571") t)

    (("17976931348623157" "1" "7976931348623157") nil)
    (("17976931348623157" "1" "797693134862315") nil)
    (("17976931348623157" "1" "79769313486231571") t)

    (("17976931348623157" "179" "76931348623157") nil)
    (("17976931348623157" "179" "7693134862315") nil)
    (("17976931348623157" "179" "769313486231571") t)
    )))

#+development
(defun validate-digit-string-overflowed-by-digit-char-lists ()
  (loop for (args desired-result)
        in digit-string-overflowed-by-digit-char-lists-validation-suite
        with validated-p = t
        do
   (let ((result
           (digit-string-overflowed-by-digit-char-lists
             (first args)
             (concatenate 'list (second args))
             (concatenate 'list (third args)))))
      (unless (if desired-result result (not result))
        (setq validated-p nil)
        (format t "~&~a should have been ~a, not ~a~%"
                args
                desired-result
                result)))
    finally (return validated-p)))

(defun digit-string-underflowed-by-digit-char-lists
       (digit-string lefthand-digit-char-list righthand-digit-char-list)
  (let ((last-index-in-digit-string (1-f (lengthw digit-string)))
        (index -1))
    (and (loop for char-list-element in lefthand-digit-char-list
               do (incff index)
               when (char>w (charw digit-string index) char-list-element)
                 do (return-from digit-string-underflowed-by-digit-char-lists
                      t)
               when (char<w (charw digit-string index) char-list-element)
                 do (return-from digit-string-underflowed-by-digit-char-lists
                      nil)
               ;; match to the end of the digit-string
               when (=f index last-index-in-digit-string)
                 do (return-from digit-string-underflowed-by-digit-char-lists
                      nil)
               finally
                 ;; outer "and" form will continue with righthand list
                 (return t))
         (loop for char-list-element in righthand-digit-char-list
               do (incff index)
               when (char>w (charw digit-string index) char-list-element)
                 do (return-from digit-string-underflowed-by-digit-char-lists
                      t)
               when (char<w (charw digit-string index) char-list-element)
                 do (return-from digit-string-underflowed-by-digit-char-lists
                      nil)
               ;; match to the end of the digit string
               when (=f index last-index-in-digit-string)
                 do (return-from digit-string-underflowed-by-digit-char-lists
                      nil)
               finally
                 ;; more match characters remain - typed-in chars would underflow
                 (return t)))))


#+development
(defvar digit-string-underflowed-by-digit-char-lists-validation-suite
  (copy-tree-changing-strings-to-text-strings
  '(
    (("16777215" "1" "") t)
    (("16777215" "167" "") t)
    (("16777215" "16777215" "") nil)
    (("16777215" "16777216" "") nil)
    (("16777215" "167772155" "") nil)

    (("22250738585072014" "" "22250738585072014") nil)
    (("22250738585072014" "" "2225073858507201") t)
    (("22250738585072014" "" "222507385850720147") nil)

    (("22250738585072014" "2" "2250738585072014") nil)
    (("22250738585072014" "2" "225073858507201") t)
    (("22250738585072014" "2" "22507385850720147") nil)

    (("22250738585072014" "22" "250738585072014") nil)
    (("22250738585072014" "22" "25073858507201") t)
    (("22250738585072014" "22" "2507385850720147") nil)

    (("17976931348623157" "" "17976931348623157") nil)
    (("17976931348623157" "" "1797693134862315") t)
    (("17976931348623157" "" "179769313486231571") nil)

    (("17976931348623157" "1" "7976931348623157") nil)
    (("17976931348623157" "1" "797693134862315") t)
    (("17976931348623157" "1" "79769313486231571") nil)

    (("17976931348623157" "179" "76931348623157") nil)
    (("17976931348623157" "179" "7693134862315") t)
    (("17976931348623157" "179" "769313486231571") nil)
    )))

#+development
(defun validate-digit-string-underflowed-by-digit-char-list ()
  (loop for (args desired-result)
        in digit-string-underflowed-by-digit-char-lists-validation-suite
        with validated-p = t
        do
   (let ((result
           (digit-string-underflowed-by-digit-char-lists
             (first args)
             (concatenate 'list (second args))
             (concatenate 'list (third args)))))
      (unless (if result desired-result (not desired-result))
        (setq validated-p nil)
        (format t "~&~a should have been ~a, not ~a~%"
                args
                desired-result
                result)))
    finally (return validated-p)))


;; NOTE: the function is meaningless: even the literal numeric values are of the
;; bounds, the results of expressions can still be out of bounds. On the other
;; side, we want 60-bit FIXNUM literals in KB but they may becomes zero (or LONG)
;; when loading in G2 Standard.  And the bound check is too complicated as part
;; of the parsing, because the idea is to make sure it's "correct" in decimal first,
;; then do the actual string->number processing.
;;
;; I think the future direction is to remove the bound checking completely.
;; -- Chun Tian (binghe), Dec 2015.

(defun read-possibly-out-of-bounds-numeric-token
       (string
        start-index
        final-index
        sign-of-fraction
        number-of-lefthand-digits
        lefthand-digits
        decimal-point-present-p
        number-of-righthand-leading-zeros
        righthand-digits
        exponent-present-p
        sign-of-exponent
        exponent-integer
        read-as-long?)
  (cond
    (read-as-long?
     (values (read-long-from-string string start-index (-f final-index 1))
	     'long))
    ((>f number-of-lefthand-digits most-lefthand-float-digits)
     (values 'overflow nil))
    ((and (=f number-of-lefthand-digits most-lefthand-float-digits)
          (digit-string-overflowed-by-digit-char-lists
            digits-of-largest-float-as-string
            lefthand-digits
            righthand-digits))
     (values 'overflow nil))
    ((>f number-of-righthand-leading-zeros most-righthand-float-zeros)
     (values 'underflow nil))
    ((and (=f number-of-righthand-leading-zeros most-righthand-float-zeros)
          (digit-string-underflowed-by-digit-char-lists
            digits-of-smallest-normalized-float-as-string
            lefthand-digits
            righthand-digits))
     (values 'underflow nil))
    (t (let* ((explicit-exponent
                (wide-character-case (or sign-of-exponent #.%\+) ; can be nil!
                  (#.%\- (-f exponent-integer))
                  (otherwise exponent-integer)))
              (implicit-exponent
                (if (>f number-of-lefthand-digits  0)
                    number-of-lefthand-digits
                    (-f (1+f number-of-righthand-leading-zeros))))
              (exponent (+f explicit-exponent implicit-exponent)))
         (cond-with-temporaries
           ((>f exponent most-lefthand-float-digits)
            (values 'overflow nil))
           ((and (=f exponent most-lefthand-float-digits)
                 (digit-string-overflowed-by-digit-char-lists
                   digits-of-largest-float-as-string
                   lefthand-digits
                   righthand-digits))
            (values 'overflow nil))
           ((=f exponent most-lefthand-float-digits)
            (values (read-float-from-string string start-index final-index)
                    'float))
           ((>f (-f exponent) most-righthand-float-zeros)
            (values 'underflow nil))
           ((and (=f (-f exponent) most-righthand-float-zeros)
                 (digit-string-underflowed-by-digit-char-lists
                   digits-of-smallest-normalized-float-as-string
                   lefthand-digits
                   righthand-digits))
            (values 'underflow nil))
           ((=f (-f exponent) most-righthand-float-zeros)
            (values (read-float-from-string string start-index final-index)
                    'float))
           ((or decimal-point-present-p
                exponent-present-p
                (>f exponent most-fixnum-digits))
            (values (read-float-from-string string start-index final-index)
                    'float))
           ((and (and (=f exponent most-fixnum-digits)
                      (eqlw #.%\- sign-of-fraction))
                 (digit-string-overflowed-by-digit-char-lists
                   digits-of-most-negative-fixnum-as-string
                   lefthand-digits
                   righthand-digits))
            (values (read-float-from-string string start-index final-index)
                    'float))
           ((and (=f exponent most-fixnum-digits)
                 (eqlw #.%\- sign-of-fraction))
            (values (read-fixnum-from-string string start-index final-index)
                    'fixnum))
           ((and (=f exponent most-fixnum-digits)
                 (digit-string-overflowed-by-digit-char-lists
                   digits-of-most-positive-fixnum-as-string
                   lefthand-digits
                   righthand-digits))
            (values (read-float-from-string string start-index final-index)
                    'float))
           (t
            (values (read-fixnum-from-string string start-index final-index)
                    'fixnum)))))))

#+development
(unless (validate-tokenize-number-from-user)
  (error "validate-tokenize-number-from-user test failed!"))

#+development
(defun new-get-next-numeric-token-from-text
    (line-index
      character-index
      text-tail
      previous-line-index
      previous-character-index
      previous-text-tail)
  (let (number-or-error-string
         type-of-numeric-token?
         line-index-to-return
         charatcer-index-to-return
         text-tail-to-return)
    (with-temporary-gensym-float-creation
        new-get-next-numeric-token-from-text
      (let (number type-of-number)
        (multiple-value-setq (number type-of-number)
          (tokenize-number-from-user
            current-wide-string                ; should abstract this interface better!
            0
            fill-pointer-for-current-wide-string))
        (case number
          (overflow
           (setq number-or-error-string #w"number is too large")
           (setq type-of-numeric-token? nil)
           (setq line-index-to-return line-index)
           (setq charatcer-index-to-return character-index)
           (setq text-tail-to-return text-tail))
          (underflow
           (setq number-or-error-string #w"number is too small")
           (setq type-of-numeric-token? nil)
           (setq line-index-to-return line-index)
           (setq charatcer-index-to-return character-index)
           (setq text-tail-to-return text-tail))
          (otherwise
           (case type-of-number
             (fixnum
              (setq number-or-error-string number)
              (setq type-of-numeric-token? 'integer)
              (setq line-index-to-return previous-line-index)
              (setq charatcer-index-to-return previous-character-index)
              (setq text-tail-to-return previous-text-tail))
             (float
              (setq number-or-error-string
                    (make-runtime-float-for-tokenizer number))
              (setq type-of-numeric-token? 'float)
              (setq line-index-to-return previous-line-index)
              (setq charatcer-index-to-return previous-character-index)
              (setq text-tail-to-return previous-text-tail)))))))
    (values number-or-error-string
            type-of-numeric-token?
            line-index-to-return
            charatcer-index-to-return
            text-tail-to-return
            nil)))






;;;; Abstraction Away from Dependence on Categories


;;; `instance-of-category-acceptable-in-current-edit-state?' - G2's standard
;;; alphabet is ambiguous.  G2 resolves the ambiguity by consulting the
;;; parser, in effect asking it "Would you prefer a token of type a or of
;;; type b?".  Actually, the parser answers that question before it's
;;; asked, and the information is held in the car of the slot
;;; (stack-of-incomplete-phrases-at-earlier-positions current-edit-state).
;;; This macro abstracts away from the lexical dependence on that slot
;;; (which is towards the goal of making tokenization independent of the
;;; current-edit-state altogether.)  See comments for right-string-acceptable-p
;;; for an example of the ambiguity of G2's alphabet.
;;;
;;; The point of the #+development version is to be able to test the tokenizer
;;; outside of the editor.  It's always been possible to access the tokenizer
;;; without having current-edit-state bound, but then the tokenization is
;;; different in certain circumstances.  This is an attempt to test the
;;; "editing tokenizer" outside of an editing context.

(defmacro instance-of-category-acceptable-in-current-edit-state? (category)
  #-development
  `(instance-of-category-acceptable-p
     ,category
     (car
       (stack-of-incomplete-phrases-at-earlier-positions
         current-edit-state))
     nil)
  #+development
  `(or
     (null current-edit-state)
     (instance-of-category-acceptable-p
       ,category
       (car
         (stack-of-incomplete-phrases-at-earlier-positions
           current-edit-state))
       nil)))


;;; `instance-of-token-acceptable-in-current-edit-state-p'

(defun-simple instance-of-token-acceptable-in-current-edit-state-p
    (token-value line-index character-index)
  (let ((current-line-index-for-end-of-token line-index)
        (current-character-index-after-token character-index))
    (when current-edit-state
      (instance-of-category-acceptable-p
        token-value
        (incomplete-phrases-for-previous-token)
        t))))



;;; `partial-string-acceptable-p' - returns t if the parser will accept
;;; the a given partial-string as the next token.

(defmacro partial-string-acceptable-p
    (partial-string-token line-index character-index)
  `(and tokenize-with-editing-context-p
        (let ((current-line-index-for-end-of-token ,line-index)
              (current-character-index-after-token ,character-index))
          (instance-of-category-acceptable-in-current-edit-state?
            ,partial-string-token))))


;;; `partial-string-acceptable-p-function' - so that TOKEN, which
;;; comes not only before EDIT1 but also before PARSE, where
;;; edit-state is defined, can call partial-string-acceptable-p.

(defun-simple partial-string-acceptable-p-function
    (partial-string-token line-index character-index)
  (partial-string-acceptable-p
    partial-string-token line-index character-index))


;;; `instance-of-category-acceptable?'

(defmacro instance-of-category-acceptable? (token-category)
  #-development
  `(instance-of-category-acceptable-p
     ,token-category
     (car (stack-of-incomplete-phrases-at-earlier-positions
            current-edit-state))
     nil)
  #+development
  `(or (null current-edit-state)
       (instance-of-category-acceptable-p
         ,token-category
         (car (stack-of-incomplete-phrases-at-earlier-positions
              current-edit-state))
         nil)))


;;; `instance-of-token-category-acceptable-in-current-edit-state-at-position?'

#+obsolete
(defun-simple instance-of-token-category-acceptable-in-current-edit-state-at-position?
    (token-category line-index character-index)
  (and current-edit-state
       tokenize-with-editing-context-p
       (let ((current-line-index-for-end-of-token line-index)
             (current-character-index-after-token character-index))
         (instance-of-category-acceptable?
           token-category))))



;;; `text-tokenization-state-not-acceptable-p'

#+obsolete
(defun-simple text-tokenization-state-not-acceptable-p (token-value)
  (not
    (if (consp token-value)
        (instance-of-token-category-acceptable-in-current-edit-state-at-position?
          (get (cadr token-value) current-indicator-for-category-of-symbol-token)
          (line-index current-text-tokenization-state)
          (character-index current-text-tokenization-state))
        (instance-of-token-category-acceptable-in-current-edit-state-at-position?
          (get token-value current-indicator-for-category-of-this-name)
          (line-index current-text-tokenization-state)
          (character-index current-text-tokenization-state)))))



;;; `not-in-kb-loading-editing-context' - returns nil if we are using the
;;; editor to load a kb.  If we are not using the editor at all, or are
;;; editing for any other category, this returns t.
;;;   The only point of this function (at least as of 9/24/96) is to
;;; determine how to handle the character '{'.  It is treated differently
;;; in the kb-loading editor (where it signals the beginning of a character
;;; class)

(defun-simple not-in-kb-loading-editing-context ()
  (or (null tokenize-with-editing-context-p)
      #+development
      (null current-edit-state)
      (not (frame-of-class-p (frame-being-edited? current-edit-state)
                             'kb-load-file-command))))


;;; `current-punctuation-alist'

(defun-simple current-punctuation-alist ()
  (or (and tokenize-with-editing-context-p
           #+development
           current-edit-state
           (punctuation-alist-subset-override?
             current-edit-state))
      punctuation-alist))


;;; `copy-current-wide-string-possibly-noting-creation'

(defun-simple copy-current-wide-string-possibly-noting-creation ()
  (if
    #+development
    (and tokenize-with-editing-context-p current-edit-state)
    #-development
    tokenize-with-editing-context-p
      (note-use-of-text-string-in-phrase
        (copy-current-wide-string))        ;; huge strings?!
      (copy-current-wide-string)))


;;; `make-runtime-float-for-tokenizer'

(defun-simple make-runtime-float-for-tokenizer (value)
  (if tokenize-with-editing-context-p
      (make-phrase-float value)
      (make-slot-value-float value)))

(defun-simple make-runtime-long-for-tokenizer (value)
  (if tokenize-with-editing-context-p
      (make-phrase-long value)
      (make-slot-value-long value)))

;;;; Token Parsing



#+development
(defvar tokenize-verbosely-p nil)

#+development
(defun tokenize-verbosely ()
  (setq tokenize-verbosely-p t))

#+development
(defun tokenize-silently ()
  (setq tokenize-verbosely-p nil))



;;; Get-next-token-from-text-if-available need not be called in an editing
;;; context, and has values as described above under get-next-token-if-available
;;; with exceptions as follows:
;;;
;;; When in-editing-context? is true, then it is assumed that there is a current
;;; workstation context, and that current-edit-state is appropriately bound.
;;; Otherwise,
;;;
;;; (1) left-, middle-, or right-string tokens cannot be returned;
;;;
;;; (2) text strings returned become the property of the caller and must be
;;; recyled by the caller (as opposed to "automatically" by the editing context);
;;; and (3) floats returned are in the form of slot value floats, as opposed to
;;; phrase floats, and become the property of the caller and must be recycled
;;; by the caller (as opposed to "automatically" by the editing context).

(defun get-next-token-from-text-if-available
    (tokenizer cursor-line-index? cursor-character-index?
     line-index character-index text-tail
     &optional in-editing-context? end-line-index? end-character-index?
               (return-partial-tokens? cursor-line-index?))

  (let ((tokenize-with-editing-context-p
          (not (null in-editing-context?)))
        end-line-index end-character-index)
    ;; Here I assume that if the line/character pairs for cursor- and end-
    ;; are always consistent; that is, either both line-index and character-
    ;; index are nil, or neither are.  That assumption appears to be
    ;; correct.
    (if cursor-line-index?
        (progn
          #+development
          (when end-line-index?
            (cerror "Continue, using cursor indices."
                    "I don't know how to get a token when given both ~
                   end-index and cursor-index. - jv"))
          (setq end-line-index cursor-line-index?
                end-character-index cursor-character-index?))
        (setq end-line-index end-line-index?
              end-character-index end-character-index?))

    (with-current-wide-string
        (multiple-value-bind (token-value
                               token-type-or-partial-types
                               line-index-for-end-of-token
                               character-index-after-token
                               text-tail-for-end-of-token?
                               token-self-terminating-p)
            (new-get-next-token-from-wide-text-if-available-1
              tokenizer
              text-tail line-index character-index
              end-line-index end-character-index
              return-partial-tokens?)
          (reclaim-wide-string current-wide-string)
          (values token-value
                  token-type-or-partial-types
                  line-index-for-end-of-token
                  character-index-after-token
                  text-tail-for-end-of-token?
                  token-self-terminating-p)))))



;;; `token-from-text-string' - is a utility intended to be called outside
;;; of an editing process to interface to the editor's token reader.

(defun token-from-text-string (text-string start-index? end-index?)
  (let* ((temporary-text
           (convert-text-string-to-text-without-duplicating-it text-string))
         (tokenize-with-editing-context-p nil))
    (multiple-value-bind (token-value token-type-or-partial-types
                                      line-index-for-end-of-token
                                      character-index-after-token)
        (new-get-next-token-from-wide-text-if-available-1
          (determine-appropriate-tokenizer)
          temporary-text 1 (or start-index? 0)
          1 end-index? nil)
      (declare (ignore line-index-for-end-of-token))
      (reclaim-text-without-reclaiming-underlying-text-string temporary-text)
      (values token-value
              token-type-or-partial-types
              character-index-after-token))))



#+development
(defun token-from-text-string-in-editing-context
    (text-string start-index? end-index?)
  (let* ((temporary-text
           (convert-text-string-to-text-without-duplicating-it text-string))
         (current-edit-state nil))
    (with-current-wide-string
        (multiple-value-bind (token-value token-type-or-partial-types
                                          line-index-for-end-of-token
                                          character-index-after-token)
            (get-next-token-from-text-if-available
              (if end-index? 1 nil) end-index?
              1 (or start-index? 0)
              temporary-text
              t
              nil nil)
          (declare (ignore line-index-for-end-of-token))
          (reclaim-wide-string current-wide-string)
          (reclaim-text-without-reclaiming-underlying-text-string
            temporary-text)
          (values token-value
                  token-type-or-partial-types
                  character-index-after-token)))))



;;; `Read-from-text-string' ... returns the values from token-from-text-string,
;;; if a full (non-partial, non-error) token is found.

(defmacro read-from-text-string (text-string &optional start-index? end-index?)
  `(multiple-value-bind
       (token-value token-type-or-partial-types character-index-after-token)
       (token-from-text-string ,text-string ,start-index? ,end-index?)
     (if (or (consp token-type-or-partial-types)
             (memq token-type-or-partial-types
                   '(quoted-character ellipsis comment single-line-comment)))
         (values nil nil nil)
         (values token-value
                 token-type-or-partial-types
                 character-index-after-token))))


;; Added a start-index? arg today; consider adding an end-index? arg when
;; needed.  (Start-index? now used by the module GSPAN for the speedup
;; interface.)   Also added new returned value, the index in the string
;; at which the parsing ended.  (MHD 7/1/92)
;; --- NOW DONE. (MHD 1/21/93)

;; This depends on the representation of text, and violates the text
;; abstraction -- I don't call convert-text-to-text-string; I don't want
;; to copy it!  Review! (MHD 8/14/91)


;;; `g2-full-token' - full, as in, non-partial.  This is just a function
;;; wrapper for the macro read-from-text-string.  Compiled functions tend
;;; to be much faster than macros from the command line.

#+development
(defun g2-full-token (text-string &optional start-index end-index)
  (read-from-text-string text-string start-index end-index))




;;; `read-from-text-string-test-suite' - read-from-text-string has a fairly
;;; limited number of responses, so this suite does not need a lot of entries.

#+development
(defparameter read-from-text-string-test-suite
  '(()
    ( 29    )
    (215    )
    (112    )
    (167    )
    (213 214)
    (215 216)
    (112 117)
    (  0   1)
    (231    )
    (177 192)
    ( 25    )
    ( 47    )
    ( 67    )
    ( 24  29)
    ( 47  49)
    ( 96  97)
    (231    )))


;;; `read-from-text-string-validation-test-suite'

#+development
(defparameter read-from-text-string-validation-test-suite
  '(#w"inform the operator that \"B@r = [quantity(b@@r)] and @\"x@\" = [@\"x@\"] now\" and conclude that the @1@5 of 123foo = -12.2 and change the text of the @{string@} of f@[o to \"the end\" {because we're done} and if @@@@@@ > 14 then delete 4... and keep trying to type"
    ((       ) (  6 symbol                    inform))
    (( 29    ) ( 31 punctuation-mark          =))
    ((215    ) (217 integer                   14))
    ((112    ) (118 float                     -12.2))
    ((167    ) (177 whole-string              #w"the end"))
    ((213 214) (214 punctuation-mark          \>))
    ((215 216) (216 integer                   1))
    ((112 117) (117 float                     -12.0))
    ((  0   1) (  1 symbol                    i))
    ((231    ) (nil nil                       nil))
    ((177 192) (nil nil                       nil))
    ;; (( 25    ) ( 73 whole-string #w"B@r = [quantity(b@@r)] and @\"x@\" = [@\"x@\"] now"))
    (( 25    ) ( 73 whole-string
                #w"Br = [quantity(b@r)] and \"x\" = [\"x\"] now"))
    (( 47    ) ( 48 punctuation-mark          \]))
    (( 67    ) ( 68 punctuation-mark          \]))
    (( 24  29) (nil nil                       nil))
    (( 47  49) ( 48 punctuation-mark          \]))
    (( 96  97) (nil nil                       nil))
    ((231    ) (nil nil                       nil))))





;;; `read-from-text-string-test-string' - good name, huh?

#+development
(defparameter read-from-text-string-test-string
  (car read-from-text-string-validation-test-suite))



;;; `test-read-from-text-string-tokenizer' - Call with:
;;;    (test-read-from-text-string-tokenizer #'g2-full-token
;;;       read-from-text-string-test-string read-from-text-string-test-suite)

#+development
(defun test-read-from-text-string-tokenizer
    (function test-string test-suite)
  (loop with *print-case* = :downcase
        for (start end) in test-suite
        do
    (multiple-value-bind
        (token-value token-type end-index)
        (funcall function test-string start end)
      (format t "    ((~a ~a) (~3d ~28s ~s))~%"
              (if start
                  (format nil "~3d" start)
                  "   ")
              (if end
                  (format nil "~3d" end)
                  "   ")
              end-index token-type token-value))))



;;; `token-not-equal'

#+development
(defun token-not-equal (a b)
  (not
    (cond
      ((wide-string-p a)
       (and (wide-string-p b)
            (string-equalw a b)))
      ((symbolp a)
       (eq a b))
      ((managed-float-p-function b)
       (=e a (aref b 0)))
      ((managed-float-p-function a)
       (=e b (aref a 0)))
      (t
       (equal a b)))))



;;; `validate-read-from-text-string-tokenizer' - Call with:
;;;    (validate-read-from-text-string-tokenizer #'g2-full-token)
;;; g2-full-token is the function equivalent of read-from-text-string

#+development
(defun validate-read-from-text-string-tokenizer (function)
  (loop with test-string = (car read-from-text-string-validation-test-suite)
        with correct = '()
        with wrong = '()
        for ((start end) (end-of-token token value))
            in (cdr read-from-text-string-validation-test-suite)
        as this-one-is-correct = t
        do
    (multiple-value-bind
        (val tok e-o-t)
        (funcall function test-string start end)
      (unless (eql end-of-token e-o-t)
        (dmesg "(~s ~s ~s) should have returned end-position ~d~%"
                function start end end-of-token)
        (dmesg "  but instead returned ~d~%~%" e-o-t)
        (setq this-one-is-correct nil))
      (when (token-not-equal token tok)
        (dmesg "(~s ~s ~s) should have returned token ~s~%"
                function start end token)
        (dmesg "  but instead returned ~s ~%~%" tok)
        (setq this-one-is-correct nil))
      (when (token-not-equal value val)
        (dmesg "(~s ~s ~s) should have returned ~s~%"
                function start end value)
        (dmesg "  but instead returned ~s~%~%" val)
        (setq this-one-is-correct nil))
      (if this-one-is-correct
          (token-push start correct)
          (token-push (token-list start end) wrong)))
        finally
          (dmesg "The following position inquiries were correct:~%~s~%"
                  (reverse correct))
          (reclaim-token-list correct)
          (unless (null wrong)
            (dmesg "The following position inquiries were wrong:~%~s~%"
                    (reverse wrong))
            (reclaim-token-tree wrong)))
  (values))




;;; Old-read-attribute-name-from-text-string reads either an unqualified or a
;;; qualified attribute name from text-string.  This accepts, for example,
;;;
;;;     FOO
;;;     BAR::FOO
;;;
;;; It would reject any non-symbol, or something just beginning with ::,
;;; etc., by returning nil.

(defun old-read-attribute-name-from-text-string
    (text-string &optional start-index? end-index?)
  (let ((attribute? nil)
        (class? nil)
        (read-end? nil))

  (multiple-value-bind (initial-token? type-of-token? token-end-index?)
      (read-from-text-string text-string start-index? end-index?)
    (when initial-token?
        (setq attribute? initial-token?)
        (setq read-end? token-end-index?)
        (case type-of-token?
          (symbol
           ;; to support multiple inheritance, interpret symbol/double-colon
           ;; (::)/symbol as qualified attribute name:
           (when (/=f token-end-index?
                      (if end-index?
                 end-index? (text-string-length text-string)))
             (multiple-value-bind
                 (2nd-token? type-of-2nd-token? punctuation-end-index?)
                 (read-from-text-string
                   text-string token-end-index? end-index?)
               (when (and 2nd-token?
                          (eq type-of-2nd-token? 'punctuation-mark)
                          (eq 2nd-token? '\:\:)) ; wasn't done in 4.0! (MHD 10/5/96)
                 (multiple-value-bind
                     (attribute-token? type-of-attribute-token?
                                       attribute-end-index?)
                     (read-from-text-string text-string punctuation-end-index?
                                            end-index?)
                   (when (and attribute-token?
                              (eq type-of-attribute-token? 'symbol))
                     (setq attribute? attribute-token?)
                     (setq class? initial-token?)
                     (setq read-end? attribute-end-index?))))))
           (return-from old-read-attribute-name-from-text-string
             (values attribute? read-end? class?)))
          ((float whole-string left-string middle-string right-string)
           (reclaim-slot-value initial-token?)
           nil))))))


;;; Read-attribute-name-from-text-string-1 reads either an unqualified or a
;;; qualified attribute name from text-string.  This accepts, for example,
;;;
;;;     FOO
;;;     BAR::FOO
;;;
;;; It would reject any non-symbol, or something just beginning with ::,
;;; etc., by returning nil.

(defun read-attribute-name-from-text-string-1
    (text-string start-index? end-index?)
  (let* ((temporary-text
           (convert-text-string-to-text-without-duplicating-it text-string))
         (tokenize-with-editing-context-p nil)
         (attribute? nil)
         (class? nil)
         (read-end? nil))
    (multiple-value-bind (token-value token-type-or-partial-types
                                      line-index-for-end-of-token
                                      character-index-after-token)
        (new-get-next-token-from-wide-text-if-available-1
          g2-symbol-tokenizer
          temporary-text 1 (or start-index? 0)
          1 end-index? nil)
      (when (eq token-type-or-partial-types 'symbol)
        (setq attribute? token-value)
        (setq read-end? character-index-after-token)
        (when (or (null end-index?)
                  (>=f end-index? character-index-after-token))
          (multiple-value-setq (token-value token-type-or-partial-types
                                            line-index-for-end-of-token
                                            character-index-after-token)
            (new-get-next-token-from-wide-text-if-available-1
              g2-symbol-tokenizer
              temporary-text 1 read-end?
              1 end-index? nil))
          ;; GENSYMCID-1167: Verify in the source code the difference between ...
          ;;
          ;; GENSYM-35875 (Texts corruption, also in GENSYMCID-685) found that the following
          ;; `reclaim-wide-string' operation could sometimes corrupt symbol names in G2. So the
          ;; fix is to suppress the calling in more cases. Now we think it should be disabled
          ;; for all cases, which means the whole form should be disabled.
          ;;
          ;; -- Chun Tian (binghe), 27/12/2013
          #|
          (when (and (null token-type-or-partial-types)
                     (wide-string-p token-value)
                     ;; GENSYM-35875 (Texts corruption) that was released with G2 8.3r1 LC02.
                     (not (string=w token-value tokenizer-illegal-character-error-message)))
            (reclaim-wide-string token-value)
            (setq token-value nil))
          |#
          (when (and (eq token-type-or-partial-types 'double-colon)
                     (or (null end-index?)
                         (>=f end-index? character-index-after-token)))
            (multiple-value-setq (token-value token-type-or-partial-types
                                              line-index-for-end-of-token
                                              character-index-after-token)
              (new-get-next-token-from-wide-text-if-available-1
                g2-symbol-tokenizer
                temporary-text 1 character-index-after-token
                1 end-index? nil))
            (when (eq token-type-or-partial-types 'symbol)
              (setq class? attribute?)
              (setq read-end? character-index-after-token)
              (setq attribute? token-value))))))
    (reclaim-text-without-reclaiming-underlying-text-string temporary-text)
    (values attribute? read-end? class?)))


;;; `read-attribute-name-from-text-string-validation-test-suite' - input
;;; strings are gensym-strings in UTF-G so that this suite and testing
;;; function below can work in 4.0 and 5.0.

#+development
(defparameter read-attribute-name-from-text-string-validation-test-suite
  `(
    (("abc" nil nil) (abc 3 nil))
    (("abc123" nil nil) (abc123 6 nil))
    (("123" nil nil) (nil nil nil))
    (("123four" nil nil) (123four 7 nil))
    (("  abc  " nil nil) (abc 5 nil))
    ((" {comment}  abc  " nil nil) (abc 15 nil))
    (("  procedure :: def32  " nil nil) (def32 20 procedure))
    ((" xyz\"fred  " nil nil) (xyz 4 nil))
    (("1.07e3" nil nil) (nil nil nil))
    (("-1.07e3" nil nil) (nil nil nil))
    (("1.07g3" nil nil) (1.07g3 6 nil))
    (("-1.07g3" nil nil) (-1.07g3 7 nil))
    (("fgh#steve" nil nil) (fgh 3 nil))
    (("object::123" nil nil) (object 6 nil))
    (("object::123." nil nil) (object 6 nil))
    (("object::12.3" nil nil) (object 6 nil))
    (("object::123'" nil nil) (123\' 12 object))
    (("object::123_" nil nil) (123_ 12 object))
    (("object::123-" nil nil) (123- 12 object))
    (("object::-123" nil nil) (object 6 nil))
    (("object::12-3" nil nil) (12-3 12 object))
    (("object::\"abc\"" nil nil) (object 6 nil))
    ;; different in 4.0 and 5.0
    (("abcd~@" nil nil)
     (|ABCD |
        ,(if (>=f major-version-number-of-current-gensym-product-line 5)
             5
             7)
        nil))
    (("fgh~@#steve" nil nil)
     ,(if (>=f major-version-number-of-current-gensym-product-line 5)
          `(fgh#steve 10 nil)
          `(fgh#steve 11 nil))
     )
    (("  procedure,def32  " nil nil)
     ,(if (>=f major-version-number-of-current-gensym-product-line 5)
          `(procedure 11 nil)
          `(def32 17 procedure))
     )
    (("abcdefghi::def32  " nil nil)
     ,(if (>=f major-version-number-of-current-gensym-product-line 5)
          `(def32 16 abcdefghi)
          `(def32 16 nil))
     )
    ))




;;; `validate-read-attribute-name-from-text-string-tokenizer'

#+development
(defun validate-read-attribute-name-from-text-string-tokenizer (validation-suite)
  (let ((correct '())
        (wrong '()))
    (loop for (input (c-symb c-length c-qual))
              in validation-suite
          as input-string = (car input)
          as test-string
             = (if (and (stringp input-string)
                        (fboundp 'gensym-string-to-wide-string-using-streams))
                   (funcall 'gensym-string-to-wide-string-using-streams
                            input-string)
                   input-string)
          as start = (cadr input)
          as end = (caddr input)
          as this-one-is-correct = t
          do
      (multiple-value-bind
          (symbol length qualifier)
          (read-attribute-name-from-text-string test-string start end)
        (unless (eq symbol c-symb)
          (dmesg "(read-attribute-name from-text-string ~s ~s ~s) should have returned symbol ~d~%"
                 test-string start end c-symb)
          (dmesg "  but instead returned ~d~%~%" symbol)
          (setq this-one-is-correct nil))
        (unless (eql length c-length)
          (dmesg "(read-attribute-name from-text-string ~s ~s ~s) should have returned length ~s~%"
                 test-string start end c-length)
          (dmesg "  but instead returned ~s ~%~%" length)
          (setq this-one-is-correct nil))
        (unless (eq c-qual qualifier)
          (dmesg "(read-attribute-name from-text-string ~s ~s ~s) should have returned qualifier ~s~%"
                 test-string start end c-qual)
          (dmesg "  but instead returned ~s~%~%" qualifier)
          (setq this-one-is-correct nil))
        (if this-one-is-correct
            (gensym-push input correct)
            (gensym-push input wrong))))
    (setq correct (nreverse correct))
    (format t "The following position inquiries were correct:~%")
    (loop for x in correct as i from 1 do
      (format t " ~25s" (car x))
          when (=f 0 (modf i 4)) do
            (terpri))
    (terpri)
    (reclaim-gensym-list correct)
    (unless (null wrong)
      (setq wrong (nreverse wrong))
      (dmesg "The following position inquiries were wrong:~%")
      (loop for x in wrong do (format t "  ~s~%" x))
      (reclaim-gensym-list wrong))
    (values)))




;;; Read-symbol-from-text-string ...  If text-string begins with a symbol, it is
;;; returned along with the index past the end of that symbol in text-string;
;;; otherwise, nil is returned.  Note that if text-string begins with the symbol
;;; nil, then :nil (nil in the keyword package) is returned.

;;; Start-index? should either be nil or an index at which to begin reading
;;; in text string.  If nil, it defaults to 0.

(defun read-symbol-from-text-string (text-string &optional start-index? end-index?)
  (multiple-value-bind (token? type-of-token? end-index?)
      (read-from-text-string text-string start-index? end-index?)
    (if token?
        (case type-of-token?
          (symbol
           (values token? end-index?))
          ((float whole-string left-string middle-string right-string)
           (reclaim-slot-value token?)
           nil)))))

;; This and the following are new functions.  CPM will use the above presently
;; to implement the new user-level function SYMBOL.  Later, we might use
;; the one below to have a user-level read-from-string type of function.  We
;; might also go back to the implementation of the user-level QUANTITY function
;; and have it use the following.  (MHD 8/14/91)


;; ;;; Read-number-from-text-string ...
;;
;; (defun read-number-from-text-string (text-string &optional start-index? end-index?)
;;   (multiple-value-bind (token? type-of-token? end-index?)
;;       (read-from-text-string text-string start-index? end-index?)
;;     (if token?
;;         (case type-of-token?
;;           ((float singular-integer plural-integer)
;;            (values token? end-index?))
;;           ((whole-string left-string middle-string right-string)
;;            (reclaim-slot-value token?)
;;            nil)))))
;;
;; ;; This has no callers at present.  There are a number of callers of
;; ;; read-number-from-string.  Unfortunately, this can be much slower
;; ;; to execute, so I'm not inclined to switch them over at this time.
;; ;; However, the fact that we use two entirely different token readers
;; ;; is a problem!  We hope they can be merged, ultimately, and that
;; ;; the fact that they're difference doesn't cause problems for users
;; ;; or make documentation difficult!  (MHD 3/24/93)

;; -- Note: in versions prior to 4.1, this function was defined as above, but
;; was never used, as per the comment above. A new, improved version is now
;; available below. The new, efficient version has options to disallow junk and
;; leading spaces; however, the quantity function allows junk and leading
;; spaces, so they are allowed by default.  This was patched back to 4.1 from
;; 5.0. (MHD 10/25/96)

;;; `Read-number-from-text-string' returns the following four values if a number
;;; can be read from text-string; if not, it returns nil.  An attempt is made to
;;; read the number between its start? (defaults to 0) and end? (defaults to the
;;; length of the string).  Unless disallow-junk? is true, this will accept
;;; syntactically numeric input up to a junk character (ala G2's QUANTITY
;;; function).  Unless disallow-leading-whitespace? is true, this ignores any
;;; initial whitespace characters, whereas if disallow-leading-spaces? is true,
;;; initial whitespace characters result in a false (nil) result.
;;;
;;; If a number can be read, this returns the following four values:
;;;
;;;   (1) the number (either an integer or a gensym float)
;;;         or either of the symbols OVERFLOW or UNDERFLOW;
;;;   (2) either INTEGER or FLOAT as appropriate;
;;;   (3) the exact start index; and
;;;   (4) the exact end index
;;;
;;; NOTE: this may return a gensym float, and so should be
;;; used in a temporary gensym float creation context.

(defun read-number-from-text-string
    (text-string
      &optional start? end? disallow-junk? disallow-leading-whitespace?)
  (multiple-value-bind (kind? number-start-index number-end-index)
      (syntactically-numeric-substring-p
	text-string start? end?
	disallow-junk? disallow-leading-whitespace?)
    (if kind?
        (multiple-value-bind (number kind)
	    (tokenize-number-from-user
	      text-string number-start-index number-end-index)
	  #+development
	  (test-assertion
	    (and number
		 (or (symbolp number)        ; kind is nil iff under/overflow
		     (cond ((eq kind 'fixnum) ; get these in synch in 5.0!!! (MHD)
			    (eq kind? 'integer))
			   ((eq kind 'long)
			    (eq kind? 'integer))
			   (t
			    (or (eq kind kind?)
				;; See notes 1 & 2: exception for the bignum ->
				;; float case: (MHD 1/14/04)
				(and (eq kind? 'integer)
				     (eq kind 'float)
				     (with-temporary-gensym-float-creation
					 read-number-from-text-string
				       (or (> number most-positive-fixnum)
					   (< number most-negative-fixnum)))))))))
	    ;; if not, preflight scanner not in synch with parser; see note!
	    )
	  (values
	    number kind                        ; see note
	    number-start-index number-end-index)))))

;; Note: notice that we assume that tokenize-number-from-user will actually read
;; from number-start-index to number-end-index, even though that information
;; comes from another parser (syntactically-numeric-substring-p).  It is assumed
;; that syntactically-numeric-substring-p are completely in synch on their
;; parsing and interpretations; however, they are wildly different pieces of
;; software, involving actually three parsers, including one that's
;; platform-specific, and there is a chance this may not work out in every case.
;; Extensive testing would increase confidence, but it is difficult to prove
;; this works perfectly, and the same across platforms, in every single
;; case. (MHD 10/25/96)

;; Note 1: -- Update: a case in point has been found: the case where integers
;; are coerced into floats because they're too big (outside fixnum range).  I
;; added extra checking to heuristically determine if a float that the preflight
;; thought should be an integer is actually properly a float, fixing bug
;; HQ-4705458 "bad assertion in read-number-from-text-string (development
;; internals)".  Also, made the test-assertion non-fatal (third arg) nil, i.e.,
;; continuable. (MHD 1/14/04)

;; Note 2: the above fix is a kind of stopgap.  See if it's possible to either
;; improve syntactically-numeric-substring-p to be in synch with
;; tokenize-number-from-user, or to improve tokenize-number-from-user (if
;; necessary) so that it has equivalent behavior and performance as the
;; combination of calling it and syntactically-numeric-substring-p.  That will
;; take a bit more time.  (MHD 1/14/04)


;;; `read-evaluation-quantity-from-text-string' -- pretty self-explanatory.
;;; Tries to read a number from the text string.  Uses zero if it can't read
;;; a number.  No error conditions.  Always returns an evaluation-quantity.

(defun read-evaluation-quantity-from-text-string
    (text-string
      &optional start? end? disallow-junk? disallow-leading-whitespace?)
  (with-temporary-gensym-float-creation
      read-evaluation-quantity-from-text-string
    (multiple-value-bind (number? kind? number-start-index number-end-index)
        (read-number-from-text-string
          text-string start? end? disallow-junk? disallow-leading-whitespace?)
      (declare (ignore kind? number-start-index number-end-index))
      (if number?
          (make-evaluation-quantity number?)
          (make-evaluation-quantity 0)))))




(defconser token-stack)

;;; Push-for-token ... Incomplete-phrases-after-token? should be nil for free
;;; text.

(defun-void push-for-token
       (line-index-for-end-of-token
        character-index-after-token token-self-terminating?
        text-tail-for-end-of-token incomplete-phrases-after-token?
        token? type-of-token)
  #-development
  (declare (ignore type-of-token))
  ;; We maintain stack-of-tokens and stack-of-types-of-tokens only
  ;; for development.  Ignore these args in non-development.
  (when token?
    (#-SymScale token-stack-push
     #+SymScale token-stack-push-atomic
     token? (stack-of-tokens current-edit-state))
    #+development
    (#-SymScale token-stack-push
     #+SymScale token-stack-push-atomic
     type-of-token (stack-of-types-of-tokens current-edit-state)))
  (atomic-exchange (text-tail-for-parsing current-edit-state)
		   text-tail-for-end-of-token)
  (#-SymScale token-stack-push
   #+SymScale token-stack-push-atomic
   (make-position-after-token
     line-index-for-end-of-token character-index-after-token
     token-self-terminating?)
   (stack-of-positions-after-tokens current-edit-state))
  (cond
    (incomplete-phrases-after-token?
     (#-SymScale token-stack-push
      #+SymScale token-stack-push-atomic
      incomplete-phrases-after-token?
      (stack-of-incomplete-phrases-at-earlier-positions current-edit-state))
     (#-SymScale token-stack-push
      #+SymScale token-stack-push-atomic
      nil
      (stack-for-token-menus current-edit-state)))))

;; For a free text, the stack-of-positions-after-tokens slot should be exactly
;; (1 0 . t) and the other stack slots should remain nil.

(defun make-position-after-token (line-index-for-end-of-token character-index-after-token
                                                              token-self-terminating?)
  (token-stack-cons line-index-for-end-of-token
                    (token-stack-cons character-index-after-token token-self-terminating?)))

(defun reclaim-if-position-after-token (pos)
  (when pos
    (reclaim-token-stack-cons (cdr pos))
    (reclaim-token-stack-cons pos)))

(defun reclaim-if-menu-content-structure (mcs)
  (when mcs
    (reclaim-menu-content-structure mcs)))

;;; Pop-for-token ... requires (stack-of-positions-after-tokens current-edit-state)
;;; to be non-nil.

(defun pop-for-token ()
  (reclaim-if-position-after-token
    (#-SymScale token-stack-pop
     #+SymScale token-stack-pop-atomic
     (stack-of-positions-after-tokens current-edit-state)))
  (#-SymScale token-stack-pop
   #+SymScale token-stack-pop-atomic
   (stack-of-tokens current-edit-state))
  (when (stack-of-incomplete-phrases-at-earlier-positions current-edit-state)
    (reclaim-if-menu-content-structure
      (#-SymScale token-stack-pop
       #+SymScale token-stack-pop-atomic
       (stack-for-token-menus current-edit-state))))
  (#-SymScale token-stack-pop
   #+SymScale token-stack-pop-atomic
   (stack-of-incomplete-phrases-at-earlier-positions current-edit-state))
  #+development
  (#-SymScale token-stack-pop
   #+SymScale token-stack-pop-atomic
   (stack-of-types-of-tokens current-edit-state)))

(defun-for-system-procedure add-space-out-text-if-no-lisp (string)
  (let* ((string-length (text-string-length string))
	 (space (make-wide-string 1 :initial-element #.%space))
	 (result (if (not (string-equalw (get-from-g2-text string 1 1) space))
		     (insert-in-g2-text space string 1)
		   string)))
    (if (not (string-equalw (get-from-g2-text string string-length string-length) space))
	(insert-in-g2-text result space 1)
      result)))

(defun-for-system-procedure continuous-spaces-filter-lisp (string)
  (let ((result (make-wide-string 0))
	(space (make-wide-string 1 :initial-element #.%space))
	(string-length (text-string-length string))
	(cur-pos 1))
    (loop with cur-char = space
	while (<=f cur-pos string-length)
	do
	(setq cur-char (get-from-g2-text string cur-pos cur-pos))
	(setq result (insert-in-g2-text result cur-char 1))
	(cond 
	  ((string-equalw cur-char space) 
	    (loop while (and (string-equalw cur-char space) (<f cur-pos string-length))
		  do
	      (setq cur-pos (1+f cur-pos))
	      (setq cur-char (get-from-g2-text string cur-pos cur-pos))))
	  (t (setq cur-pos (1+f cur-pos)))))
    result))

(defun-for-system-procedure parse-first-var-before-space-or-eof-lisp (string)
  (let ((result (make-wide-string 0))
    (space (make-wide-string 1 :initial-element #.%space))
	(string-length (text-string-length string))
	(pos 0)
	(cur-char (make-wide-string 1))
	)
  (when (>f string-length 0)
  (loop 
   (setq cur-char (get-from-g2-text string pos pos))
   while (and (not (string-equalw cur-char space)) (<f pos string-length))
   do
   (setq cur-char (get-from-g2-text string pos pos))
   (setq pos (+f pos 1))
  )
  (if (string-equalw cur-char space)
	(setq result (get-from-g2-text string 1 (-f pos 1)))
	(setq result (get-from-g2-text string 1 pos))
	)
	)
  result
  )
)

(defun-for-system-procedure parse-var-of-class-from-rule-or-gf-text-lisp(class-name string)
  (let* ((class-name-text (add-space-out-text-if-no-lisp (continuous-spaces-filter-lisp class-name)))
       (class-name-length (text-string-length class-name-text))
	   (rule-or-gf-text (continuous-spaces-filter-lisp string))
	   ;;(result nil)
	   (result (make-transient-item 'text-list))
	   (null-string (make-wide-string 0))
	   (pos 1))
    (loop
	  while (/=f pos 0)
	  do
	  (setq rule-or-gf-text (add-space-out-text-if-no-lisp rule-or-gf-text))
	  (setq pos (text-string-search class-name-text rule-or-gf-text nil nil))
	  (when (/=f pos 0)
	    (setq rule-or-gf-text (get-from-g2-text rule-or-gf-text (+f pos class-name-length) (text-string-length rule-or-gf-text)))
		(let ((cur-char (parse-first-var-before-space-or-eof-lisp rule-or-gf-text)))
		  (if (not (string-equalw cur-char null-string))
		    (setq result (g2-list-insert-at-beginning (make-evaluation-text cur-char) result))
			(setq result (g2-list-insert-at-beginning (make-evaluation-text (insert-in-g2-text cur-char (make-wide-string 1 :initial-element #\,) 1)) result))
		    )
		  (setq rule-or-gf-text (get-from-g2-text rule-or-gf-text (1+f (text-string-length cur-char)) (text-string-length rule-or-gf-text)))
		  )
	    ))
	result
  ))

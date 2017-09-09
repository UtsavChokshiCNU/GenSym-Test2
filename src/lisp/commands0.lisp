;;-*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module COMMANDS0

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Fred White



;;;; Introduction


;;; This module contains UI command support functions, presentation types and menus.


(declare-forward-reference select-then-search-for-mouse-drag function)
(declare-forward-reference update-att-tables function)
(declare-forward-reference get-current-time-zone function)
(declare-forward-reference load-kb-permitted-p function)


;;;; Some "Meta" Presentation Types.



;; This has to be written as (member '(a b c)) in commands.
;; In particular, the choice list must be statically consed, since
;; it is never reclaimed.

(define-presentation-type member (list)
  :choices (copy-list-using-slot-value-conses list))




;;;; Top level context


;;; The `top-level' workstation context is always active.  Many modes include
;;; the top-level mode's behavior by one scheme or another.

(define-workstation-context top-level ()
  :dont-define-structure t ;; See telestubs.
  :parent NIL
  :keymaps
  (title-bar-handlers
   critical-internal-handlers                ; Placed ahead of, and hence not usurpable by, item config
   ;Changed by SoftServe: HQ-5679116
   
   ;The next two lines replaced, so
   ;now the restriction handlers have 
   ;the higher priority than the
   ;non-selection user mode handlers
   
   item-configuration
   
   critical-non-selection-mode-handlers        ; Classic UI only
   
   ;end of SoftServe changes
   
   standard-keyboard-shortcuts                ; Selection UI only
   classic-keyboard-shortcuts                ; Selection UI only

   global-keyboard-commands                ; Classic UI only
   usurpable-selection-handlers                ; Selection UI only
   usurpable-internal-handlers
   screen-layout                        ; Classic UI only
   #+development global-development))


;;; The keymap `critical-non-selection-mode-handlers' contains handlers which
;;; are "critical" when not running in selection mode, but must be usurpable in
;;; selection mode.  Selection mode usurps this particular handler by binding
;;; mouse left and right down to different things.

(define-keymap critical-non-selection-mode-handlers (:private t :condition selection-not-enabled-p)
  ;; Items which have behavior on mouse-down, such as highlighting themselves.
  ;; This includes buttons.  If the button is not active (G2 not running, etc),
  ;; then the event handler is hardwired to call search-for-mouse-drag.
  ((<mouse-down> button-like-spot) maybe-perform-button-action)
  ;; Maybe this should be user-bindable?
  ((<mouse-drag> t) maybe-begin-dragging-handler))



;;; The keymap `title-bar-handlers' defines critical operations on the titlebar.

(define-keymap title-bar-handlers (:private t)
  ;; These bindings cause mouse-drags in the title bar to start dragging
  ;; the menu immediately.
  ((<mouse-down> close-box-spot) mouse-down-on-close-box-widget)
  ((<mouse-down> title-bar-spot) search-for-mouse-drag)
  ((<mouse-drag> title-bar-spot) start-dragging-title-bar-handler)
  ((<mouse-select> title-bar-spot) title-bar-raise-to-top)

  ((mouse-up title-bar-spot) mouse-up-on-title-bar) ; Why is this here? Handler is a nop.

  ((<mouse-down> menu-title-spot) search-for-mouse-drag)
  ((<mouse-drag> menu-title-spot) start-dragging-menu-handler)
  ((<mouse-select> menu-title-spot) pop-down-menu))


;; !@#%^&* spots
(def-spot-class-set selectable-spot ()
  simple-item-spot
  text-box-spot
  name-box-spot
  connection-spot
  button-spot
  attribute-name-represented-by-table-spot ; Selects the parent table
  attribute-value-represented-by-table-spot
  new-table-spot
  new-table-cell-spot
  new-table-background-spot
  trend-chart-spot
  graph-table-spot
  chart-spot
  slider-spot
  dial-spot
  meter-spot
  text-inserter-spot
  type-in-box-spot
  inspect-command-spot
  table-background-spot)


;;; Spots classes in `button-like-spot' act like buttons: they do something on
;;; mouse-down only when G2 is running.

(def-spot-class-set button-like-spot ()
  button-spot
  slider-spot
  type-in-box-spot)


;;; The keymap `usurpable-selection-handlers' defines new mouse bindings to
;;; support selection, and any other stuff want to add conditioned on -mdi or
;;; whatever.

(define-keymap usurpable-selection-handlers (:private t :condition selection-enabled-p)
  ((mouse-left-down button-like-spot) maybe-perform-button-action)
  ((mouse-middle-down button-like-spot) maybe-perform-button-action)
  ((double+mouse-left-down button-like-spot) perform-button-action-or-default)
  ((double+mouse-middle-down button-like-spot) perform-button-action-or-default)

  ;; If click is on a selectable part of a selectable item (only attribute-value
  ;; text-cells at present), then we sometimes defer selecting to the mouse-up
  ;; (actually mouse-select), at (*) below.
  ((mouse-left-down attribute-value-represented-by-table-spot) maybe-select-part-then-search-for-mouse-drag)

  ((mouse-left-down selectable-spot) select-then-search-for-mouse-drag)
  ((mouse-left-down subcommand-menu-button-spot) subcommand-menu)
  ((mouse-left-down table-header-spot) search-for-mouse-drag)        ; Old binding
  ((shift+mouse-left-down selectable-spot) toggle-selection-of-item-then-search-for-mouse-drag)
  ((control+mouse-left-down selectable-spot) select-then-search-for-mouse-drag)

  ((double+mouse-left-down selectable-spot) search-for-mouse-drag)
  ((double+mouse-left-select selectable-spot) perform-default-action) ; Edit, if possible.

  ;; Not really related to selection UI. Do we want this?
  ((control+mouse-left-drag selectable-spot) clone-selection)

  ((Alt+mouse-left-down selectable-spot) select-network-then-search-for-mouse-drag)
  ((Shift+Alt+mouse-left-down selectable-spot) toggle-select-network-then-search-for-mouse-drag)

  ((mouse-left-select output-only-table-spot) select-workspace-or-deselect-all)
  ((mouse-left-select workspace-background-spot exact) select-workspace-or-deselect-all)
  ((mouse-left-select table-header-spot) pop-down-attribute-table)
  ((mouse-left-select attribute-value-represented-by-table-spot) select-then-raise-image-plane) ; (*)
  ((mouse-left-select selection-handle-spot) select-this-item)
  ((<mouse-left-select> t) raise-image-plane) ; Since no longer done on mouse-down

  (<mouse-motion> update-mouse-cursor)

  ;; Bind select-area only on non-temporary workspaces.
  ((mouse-left-drag temporary-workspace) maybe-begin-dragging-handler)
  ((mouse-left-drag workspace-background-spot exact) select-area)
  ((Shift+mouse-left-drag temporary-workspace) maybe-begin-dragging-handler)
  ((Shift+mouse-left-drag workspace-background-spot exact) select-area)
  ((mouse-left-drag selection-handle-spot) drag-selection-handle)
  ((<mouse-left-drag> selectable-spot) move-selection)

  ;; Right down/drag acts like left down/drag, on selectable spots, except that
  ;; control+right-drag doesn't clone.  TODO: We want to post a menu of
  ;; move/clone at the end of right-dragging, but that's hard, so in the
  ;; meantime we always do a move.  -fmw, 2/18/04
  ((mouse-right-down selectable-spot) select-then-search-for-mouse-drag)
  ((shift+mouse-right-down selectable-spot) toggle-selection-of-item-then-search-for-mouse-drag)
  ((control+mouse-right-down selectable-spot) select-then-search-for-mouse-drag)
  ((Alt+mouse-right-down selectable-spot) select-network-then-search-for-mouse-drag)
  ((Shift+Alt+mouse-right-down selectable-spot) toggle-select-network-then-search-for-mouse-drag)
  ((<mouse-right-drag> temporary-workspace) maybe-begin-dragging-handler)
  ((<mouse-right-drag> selectable-spot) move-selection)

  ;; Right-click ALWAYS posts a menu.  It never does click-to-edit.
;  ((Shift+mouse-right-select selectable-spot) toggle-selection-then-post-object-menu)
  ((<mouse-right-select> selectable-spot) really-post-object-menu)
  ((<mouse-right-select> selection-handle-spot) really-post-object-menu)
  ((<mouse-right-select> output-only-table-spot) select-then-post-workspace-menu)
  ((<mouse-right-select> workspace-background-spot exact) select-then-post-workspace-menu)

  ((<mouse-middle-select> t) do-nothing-event-handler) ; For HQ-4576741
  ((<mouse-drag> t) maybe-begin-dragging-handler))


(define-keymap standard-keyboard-shortcuts (:condition selection-enabled-p
                                              :filter filter-global-keyboard-binding
                                            :pretty-name "Standard Keyboard Shortcuts")
  (F1 help-topics)
  (F5 refresh)                                ; Since Control+C is now copy-selection.
  (TAB select-next-item)
  (Shift+TAB select-previous-item)

  ;; Some MDI-like bindings for our SDI user interface.
  (Control+TAB select-next-workspace)
  (Control+Shift+TAB select-previous-workspace)
  (Control+F4 hide-selected-workspace)

  (pause pause)
  (control+G toggle-visible-grid)

  (Alt+Return selection-properties)
  ((or menu Shift+F10) post-menu-for-selection)        ; MENU key on Windows.

  ;; SPACE is mainly for use in dialog boxes which redefine RETURN to exit the dialog.
  (return perform-default-action-on-selection-if-any) ; HQ-4668508
  (space perform-default-action-on-selection)

  (delete delete-selection)
  (control+A select-all)
;  (control+shift+F find)                ; Control+F is more standard.
  (escape deselect-all-or-dismiss)

;  (control+D duplicate-selection)
;  (control+X cut-selection)
;  (control+C copy-selection)
;  (control+V paste-g2)

;  (control+N new-workspace)
  (control+O load-kb)                        ; Control oh

;  (control+Z undo-g2)
;  (control+Y redo-g2)

  (page-up page-up)                        ; These commands only apply to
  (page-down page-down)                        ; image-planes with scroll bars.
  (control+page-up page-left)
  (control+page-down page-right)
  (home home)
  (end end)
  (control+home home-right)
  (control+end end-right)

  (mouse-wheel-forward  mouse-wheel-scroll-forward) ; Funny Microsoft wheel scrolling
  (mouse-wheel-backward mouse-wheel-scroll-backward)

  ((or control++ control+=) zoom-in)
  ((or control+- control+_) zoom-out)
  (control+0 selection-full-scale)        ; Control zero

  ;; These commands move the selection, or if none, the selected image-plane.
  ;; If the image-plane has scroll bars, then the direction of movement of the
  ;; image-plane is reversed, but not the movement of the selected items, if any.
  (left-arrow move-selection-left)        ; By 10%/10 workspace units
  (right-arrow move-selection-right)
  (up-arrow move-selection-up)
  (down-arrow move-selection-down)

  (Control+left-arrow nudge-selection-left) ; By 1%/one workspace unit
  (Control+right-arrow nudge-selection-right)
  (Control+up-arrow nudge-selection-up)
  (Control+down-arrow nudge-selection-down))



;; These commands operate on the object under the mouse, or else don't require
;; an object at all.
(define-keymap classic-keyboard-shortcuts (:condition selection-enabled-p
                                             :filter filter-global-keyboard-binding
                                           :pretty-name "Classic Keyboard Shortcuts")
  (control+F full-scale)
  (alt+F normalized-full-scale)
  (control+T lift-to-top)
  (control+V drop-to-bottom)                ; Someday g2-paste

  (control+C refresh)                        ; Someday g2-copy

  (control+P circulate-up)
  (control+I circulate-down)

  (control+L shift-left-ten-percent)
  (control+R shift-right-ten-percent)
  ((or control+U mouse-wheel-backward) shift-up-ten-percent)
  ((or control+D mouse-wheel-forward)  shift-down-ten-percent) ; Control+D was duplicate.

  (alt+l shift-left-one-percent)
  (alt+u shift-up-one-percent)
  (alt+r shift-right-one-percent)
  (alt+d shift-down-one-percent)
  
  ;modified by SoftServe
  
  (alt+Shift+l shift-left-one-percent)
  (alt+Shift+u shift-up-one-percent)
  (alt+Shift+r shift-right-one-percent)
  (alt+Shift+d shift-down-one-percent)
  
  ;end of SoftServe changes

  (control+. scale-to-fit)
  (alt+. maximum-scale-to-fit)

  ((or control+S control+mouse-wheel-backward) twenty-percent-smaller)
  ((or control+B control+mouse-wheel-forward) twenty-percent-bigger)
  (control+N twenty-percent-narrower)
  (control+W twenty-percent-wider)

  (control+Q one-quarter-the-scale)
  (control+4 four-times-the-scale)

  (control+Z pause)                        ; Someday g2-undo

  (<standard-help-keys> help))


;;; The function `selection-enabled-p' returns true if the selection UI is
;;; enabled on the given window (defaults to the current window).  If the window
;;; argument is not supplied, then this should be called in either a
;;; for-workstation or on-window context. If not, it uses the system-window if
;;; defined, or else simply returns T.

(defun selection-enabled-p (&optional (gensym-window? (current-window)))
  #+development
  (unless gensym-window?
    (dwarn "selection-enabled-p called outside of a current-window context!"))
  (cond (gensym-window?
         (selection-ui-p gensym-window?))
        ((and (boundp 'system-window) system-window)
         (selection-ui-p system-window))
        (t
         t)))

(defun selection-not-enabled-p (&optional (gensym-window? (current-window)))
  (not (selection-enabled-p gensym-window?)))


;;; The keymap `critical-internal-handlers' includes bindings which must not
;;; be usurped by user-defined item configurations.  These include bindings on
;;; title bar, scroll-bar buttons, action buttons, etc.

(define-keymap critical-internal-handlers (:private t)
  ((<mouse-select> stepper-of-scroll-bar-spot) do-scrolling)
  ((<mouse-down> entire-menu-spot) handle-enter-menu-choose)

  ;; A button-like thing, but with a different event handler.
  ((<mouse-down> subcommand-menu-button-spot) subcommand-menu)

  ;; Loose ends start dragging if selected at top-level.
  ;; MK wants to usurp this.
  ((<mouse-select> loose-end-spot) maybe-begin-dragging-handler)

  ;; This binding should NOT be usurpable.
  ((<mouse-select> table-header-spot) pop-down-attribute-table)

  ;; "Secret" keyboard bindings which are not to be shown in the help
  ;; workspace.
  (control+Y change-g2-user-mode)

  ;; Incoming choice from builtin native pop up menus, based on code which
  ;; predates NMS. -fmw, 1/15/02
  (pre-nms-menu-choice execute-native-menu-choice)
  (<native-menu-choice> execute-native-menu-choice) ; Remove after 7.0 alpha

  ;; Incoming choice from an NMS menu. -fmw, 9/12/02
  (menu-choice nms-execute-menu-choice)

  ;; Request to update the menubar. TODO: Any menu
  (menu-bar handle-menu-bar-message)

  ;; Request to update popup menu.
  (nms-menu-posted handle-post-menu-message)

  ;; NMS unposting callbacks. -fmw, 2/28/05
  (nms-menu-unposted handle-unpost-menu-message)

  ;; NMS selection callbacks -fmw, 8/17/04
  (nms-menu-item-selected handle-menu-item-selected-message)

  ;; Incoming choice from a file dialog.
  (file-dialog handle-file-dialog-message)

  ;; Incoming choice from a print dialog.
  (print-dialog handle-print-dialog-message)

  ;; Incoming choice from a basic dialog.
  (basic-dialog handle-basic-dialog-message)

  ;; A dialog update
  (dialog-update handle-dialog-update)

  ;; A dialog dismissal
  (dialog-dismissed handle-dialog-dismissed)

  ;; Incoming message from an NMS control. -fmw, 4/6/04
  (nms-control handle-nms-control-message)

  ;; Other dialog communication
  (dialog-miscellaneous-communication handle-miscellaneous-dialog)

  ;; Request from custom file dialog for server-side directory listing.
  (list-directory handle-list-directory-message)

  ;; Request from custom file dialog for system drives listing.
  (list-sys-drives handle-list-sys-drives-message)
  
  ;; Notifications from tree views. -fmw, 9/1/04
  (tree-view handle-tree-view-message)

  ;; Notifications from HTML views. -fmw, 9/29/04
  (html-view handle-html-view-message)

  ;; Notifications from shortcut-bar. -fmw, 3/3/05
  (shortcut-bar handle-shortcut-bar-message)

  ;; Notifications from debugger dialog. -fmw, 10/27/04
  (debugger-dialog handle-debugger-dialog-message)

  ;; Notifications from native editor. -fmw, 9/26/04
  (editor handle-editor-message)

  ;; Notifications from chart views. -fmw, 2/16/05
  (chart-view handle-chart-view-message)

  ;; Notifications from logbook views. -fmw, 10/31/05
  (logbook-view handle-logbook-view-event)

  ;; Notifications from property grids. -fmw, 2/8/06
  (prop-grid handle-property-grid-message)

  ;; User gesture on dialog control -jv, 7/25/06
  (dialog-user-gesture handle-dialog-gesture)

  ;; Notifications from grid views. -fmw, 7/19/06
  (grid-view handle-grid-view-message)

  ;; Notifications from status bar. -fmw, 8/10/06
  (status-bar handle-status-bar-message)

  ;; Notifications from tabular view. -fmw, 8/10/06
  (tabular-view handle-tabular-view-message)

  ;; Native Image Plane handlers
  (window-activated handle-window-activated)
  ;; The next four events are handled preemptively in
  ;; absorb-local-event-ab-side-1, ONLY for workspace-views. Otherwise, we pick
  ;; up the handlers here. -fmw, 2/8/07
  (window-refresh   handle-window-refresh)
  (window-moved     handle-window-moved)
  (window-sized     handle-window-sized)
  (window-closed    handle-window-closed)

  (hscroll          handle-window-hscroll)
  (vscroll          handle-window-vscroll)

  ;; Only to suppress warnings in development.
  (paste-availability-request do-nothing-event-handler))

;; Why on earth is ABORT secret?  Users find out soon enough (to their dismay)
;; when they hit ^A in the editor.  ^Y is pretty well known, too.

;; Time may tell if it is appropriate to record these commands in all
;; modes, no matter how restrictive.





;;; The keymap `item-configuration' has no explicitly listed bindings. The
;;; bindings are entirely determined by item configurations.

(define-keymap item-configuration
    (:private NIL
     :namespace user
     :lookup-method lookup-key-in-item-configuration
     :describe-method describe-item-configuration-keymap))



(defun filter-global-keyboard-binding (keymap handler)
  (declare (ignore keymap))
  (let* ((command? (find-ui-command handler))
         (menu-name? (and command? (ui-command-menu-name command?))))
    (cond ((null menu-name?)
           t)
          ((global-keyboard-command-permitted-p menu-name?)
           t))))

;; Global keyboard command restrictions disable the top-level bindings,
;; not the commands themselves.


;;; The keymap `global-keyboard-commands' includes the keyboard commands which
;;; apply everywhere (eg, do not require a workspace underneath), and which
;;; we want to appear in the HELP workspace.

(define-keymap global-keyboard-commands (:pretty-name "Global Keyboard Commands"
                                         :filter filter-global-keyboard-binding
                                         :condition selection-not-enabled-p)

  (control+z pause)
  (<standard-help-keys> help))

;; I don't know why we want to keep control+A and control+Y from being visible.




;;; The keymap `usurpable-internal-handlers' includes bindings which may be
;;; overidden by item configurations.

(define-keymap usurpable-internal-handlers (:private t)
  ;; Allow control+a to be rebound.  FILTERS already allows gramatically.
  ;; We don't lose control+A's abort behavior, because every ws context
  ;; which wants to be aborted rebinds it itself.
  (<standard-abort-keys> abort)

  ;; A little-known back door.
  (control+E change-g2-user-mode-e)

  ;; Usurped by "pressing any mouse button ..." item configs.
  ((<mouse-down> t) search-for-mouse-drag)

  ;; This binding is usurped by "Selecting any ..." item configurations.
  ((<mouse-select> t) post-object-menu)

  ;; Mouse up is a legal event in this selection style, but then
  ;; it is usually consumed by a context spawned on mouse down.
  (<mouse-up> do-nothing-event-handler)

  (<mouse-hover> do-nothing-event-handler) ; Just to avoid warnings

  ;; These should not slip in.  Someday user may bind them.
  (<mouse-motion> do-nothing-event-handler))

;; We ought to have a handler for <alphabetic> that does nothing, or maybe
;; beeps if N occur in a row:





;;; `Screen-layout' is a keymap of the commands that allow the user to modify
;;; the layout of the screen, using control keys.  It enables him to change
;;; scale, move image-planes, and edit the image-plane stack.  It is mixed into
;;; even the most restricted modes.

(define-keymap screen-layout (:pretty-name "Screen-Layout Keyboard Commands"
                              :filter filter-global-keyboard-binding
                              :condition selection-not-enabled-p)
  (control+F full-scale)
  (alt+F normalized-full-scale)

  (control+T lift-to-top)
  (control+V drop-to-bottom)

  (control+c refresh)                                            ; Was the (lispm only) refresh key.
  (control+G toggle-visible-grid)

  (control+P circulate-up)                                    ; Removed page-up binding
  (control+I circulate-down)                                    ; Remove page-down

  ((or left-arrow control+L) shift-left-ten-percent)
  ((or up-arrow control+U mouse-wheel-backward) shift-up-ten-percent)
  ((or right-arrow control+R) shift-right-ten-percent)
  ((or down-arrow control+D mouse-wheel-forward) shift-down-ten-percent)

  ((or alt+left-arrow alt+l) shift-left-one-percent)
  ((or alt+up-arrow alt+u) shift-up-one-percent)
  ((or alt+right-arrow alt+r) shift-right-one-percent)
  ((or alt+down-arrow alt+d) shift-down-one-percent)

  (control+o center-origin)
  (control+. scale-to-fit)
  (alt+. maximum-scale-to-fit)

  ((or control+S control+mouse-wheel-backward) twenty-percent-smaller)
  ((or control+B control+mouse-wheel-forward) twenty-percent-bigger)
  (control+N twenty-percent-narrower)
  (control+W twenty-percent-wider)

  (control+Q one-quarter-the-scale)
  (control+4 four-times-the-scale))



;;; The keymap `global-development' contains development-only junk installed
;;; into top-level.  This is a separate keymap so that it can easily be removed
;;; in the production image.

#+development
(define-keymap global-development (:pretty-name "Development-Only Commands")
  (control+alt+escape break)
  (control+~\\ break)                               ; Alternate alt-free binding for PCs.
;  (control+= break) ; Taken over by the selection UI

  (shift+help show-all-ui-commands)
  (alt+g memory-management)
  (control+alt+g show-change-in-memory-use)
  (control+alt+d toggle-drawing-mode)
  (control+alt+e toggle-event-tracing)
  (control+alt+f do-foo)
  (alt+e show-recent-events)
  (control+alt+u toggle-user-mode))



;;;; Mouse-drag-detector Context



;;; The workstation-context `mouse-drag-detector' is entered by a mouse-down at top level
;;; on anything but a pane-spot.  It absorbs mouse-motion events until it deems the mouse
;;; has moved far enough to call it a drag, or until mouse-up.  The mouse-up is converted
;;; into a mouse-select and requeued.

(define-workstation-context mouse-drag-detector ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :state-variables (mouse-pointer)
  :conc-name t
  :define-enter-context-function t
  :keymap ((<mouse-up> push-back-mouse-select-event-and-return)
           (<mouse-motion> maybe-push-back-mouse-drag-event-and-return)))

;; Notice that we don't abort when the mouse-pointer becomes invalid.  All we
;; need from it is the time and position.


;; Bound to mouse-down in top level.
(define-event-handler search-for-mouse-drag (mouse-pointer)
  (enter-mouse-drag-detector-context :mouse-pointer (reference-mouse-pointer mouse-pointer)))

(def-structure-method clean-up-workstation-context (mouse-drag-detector-state)
  (release-mouse-pointer-if-any (mouse-drag-detector-state-mouse-pointer mouse-drag-detector-state))
  (funcall-superior-method mouse-drag-detector-state))



;;; The event-handler `push-back-mouse-select-event-and-return' transforms the
;;; current event into a mouse-select for the case where we received a mouse-up
;;; before a drag was detected.  The mouse-select is positioned in the same
;;; place as the original mouse-down.  So, effectively, we've treated all of the
;;; intervening mouse-motions as just noise or sloppy mousing.

(define-event-handler push-back-mouse-select-event-and-return
    ((event event)
     (mouse-pointer-of-mouse-up mouse-pointer)
     (state workstation-context-specifics))
  (let* ((mouse-pointer-of-mouse-down
           (mouse-drag-detector-state-mouse-pointer state))
         (key-code
           (convert-mouse-code-to-mouse-select
             (key-code-of-mouse-pointer mouse-pointer-of-mouse-down))))

    (requeue-event-for-mouse-pointer
      event
      key-code                                ; Now includes L/M/R and modifier bits.
      mouse-pointer-of-mouse-down)

    (return-from-current-workstation-context
      type-of-current-workstation-context)))



;;; The event-handler `maybe-push-back-mouse-drag-event-and-exit' decides
;;; whether the mouse has moved enough to call it a drag, mutates the current
;;; event, which is a mouse-motion event, into a mouse-drag event with x,y
;;; given by the location of the original mouse-down.

(define-event-handler maybe-push-back-mouse-drag-event-and-return
    ((spot innermost-spot)
     (event event)
     (state workstation-context-specifics))
  (let ((mouse-pointer-of-mouse-down
          (mouse-drag-detector-state-mouse-pointer state)))
    (with-mouse-pointer-bindings (x-in-window y-in-window timestamp)
        mouse-pointer-of-mouse-down

      (when (mouse-was-dragged-p spot event x-in-window y-in-window timestamp)
        (let ((key-code
                (convert-mouse-code-to-mouse-drag
                  (key-code-of-mouse-pointer mouse-pointer-of-mouse-down))))

          ;; Mutate the current event into a MOUSE-L/M/R-DRAG event, with a
          ;; position of the original mouse-down, and requeue it.
          (requeue-event-for-mouse-pointer event key-code mouse-pointer-of-mouse-down)

          (return-from-current-workstation-context
            type-of-current-workstation-context))))))


;; Push back a mouse-motion to get the dragging started.
(defun requeue-mouse-motion-event (mouse-pointer)
  (requeue-event-for-mouse-pointer
    current-workstation-event                ; FIXME: ARGH!!
    (mouse-motion-key-code (key-modifier-bits (key-code-of-mouse-pointer mouse-pointer)))
    mouse-pointer))


(defun requeue-event-for-mouse-pointer (event new-key-code mouse-pointer)
  (with-mouse-pointer-bindings (x-in-window y-in-window timestamp
                                            &optional
                                            (window? window)
                                            (pane? pane)
                                            (image-plane? image-plane))
        mouse-pointer
    (setf (workstation-event-code event) new-key-code
          (workstation-event-cursor-x event) x-in-window
          (workstation-event-cursor-y event) y-in-window
          (workstation-event-window? event) window?
          (workstation-event-pane? event) pane?
          (image-plane-for-workstation-event? event) image-plane?)
    (requeue-workstation-event current-workstation event)))

;; Yuck.


(defun drag-connection-vertex-permitted-p (connection-frame)
  (and (non-menu-choice-permitted-p 'move-connection connection-frame)
       (non-menu-choice-permitted-p 'move-object connection-frame)
       (item-is-either-not-permanent-or-from-an-editable-module-p connection-frame)))

(defun drag-block-permitted-p (block)
  (and (if (frame-of-class-p block 'loose-end)
           (non-menu-choice-permitted-p 'move-connection block)
           t)
       (non-menu-choice-permitted-p 'move-object block)
       (item-is-either-not-permanent-or-from-an-editable-module-p block)))

;; note: non-menu-choice restriction move-objects-beyond-
;;   workspace-margin gets handled by enter-dragging-context.


;;; The function `drag-block-if-permitted' starts dragging either the given
;;; block, or, if the block is on a non-kb workspace, the entire workspace.
;;; All of this is conditioned on user restrictions.

(defun drag-block-if-permitted (block x-in-window y-in-window image-plane workspace?)
  (cond ((not (framep block)))                        ; On window, etc. Do nothing.
        ((frame-of-class-p block 'connection)
         ;; We should be so clever, but instead only loose ends are draggable.
         )
        ((or (workspace-p block)
             ;; if current selection is any block on a non-kb workspace,
             ;;   just drag the workspace.
             (and workspace?
                  (non-kb-workspace-p workspace?)))
         (when (and (non-menu-choice-permitted-p 'move-workspace workspace?)
                    (not (image-plane-fixed-in-place-p image-plane))
                    (item-is-either-not-permanent-or-from-an-editable-module-p block))
           ;; note: non-menu-choice restriction move-workspaces-beyond-
           ;;   window-margin gets handled by enter-dragging-context.
           (enter-image-plane-dragging-context
             image-plane
             (-r x-in-window (left-edge-of-image-in-window image-plane))
             (-r y-in-window (top-edge-of-image-in-window image-plane)))))
        (t
         ;; selected block (a workspace subblock) to be moved
         (when (drag-block-permitted-p block)
           (let (x-offset-from-dragger y-offset-from-dragger)
             (with-image-plane-transform (image-plane)
               (setf x-offset-from-dragger
                     (-w (x-in-workspace x-in-window)
                         (left-edge-of-block block)))
               (setf y-offset-from-dragger
                     (-w (y-in-workspace y-in-window)
                         (top-edge-of-block block))))
             (enter-move-dragging-context
               block x-offset-from-dragger y-offset-from-dragger
               image-plane))))))

;; Derived from maybe-enter-dragging-context-after-selection (RUN).







;;;; The Mouse-Watch Workstation Context

;;; `Mouse-Watch' is a workstation context which wraps around mouse-drag-detector.
;;; It takes one datum when entered which is returned when done.
;;; It returns three values:
;;;    -- a status drawn from this set:  :ABORT, :SELECT, or :DRAG
;;;    -- the mouse-pointer of the select-event, or drag-event generated
;;;       by the drag-detector or the event that triggered the abort.
;;;    -- the datum.

;;; Memory managment of the datum is the caller's responsiblity.  :Abort is returned
;;; only if the user aborts the mouse-drag-detector.

(define-workstation-context mouse-watch ()
  :state-variables (datum-of-mouse-watch)
  :constructor (make-mouse-watch-state (datum-of-mouse-watch))
  :keymap ((<mouse-select> mouse-select-in-mouse-watch)
           (<mouse-drag> mouse-drag-in-mouse-watch)))

#+comment
(def-structure-method clean-up-workstation-context (mouse-watch-state)
  (funcall-superior-method mouse-watch-state))

(defun enter-mouse-watch-state (mouse-pointer datum)
  (enter-context-in-current-workstation 'mouse-watch (make-mouse-watch-state datum))
  (with-workstation-context-continuation(continue-mouse-watch-after-mouse-drag-detector)
    (search-for-mouse-drag mouse-pointer)))

(defun continue-mouse-watch-after-mouse-drag-detector (mouse-watch-state)
  (with-workstation-context-return-values (status mouse-pointer)
    (when (eq :abort status)
      (return-from-current-workstation-context
        'mouse-watch :abort mouse-pointer (datum-of-mouse-watch mouse-watch-state)))))

(define-event-handler mouse-select-in-mouse-watch
    (mouse-pointer (mouse-watch-state workstation-context-specifics))
  (return-from-current-workstation-context
    'mouse-watch :select mouse-pointer (datum-of-mouse-watch mouse-watch-state)))

(define-event-handler mouse-drag-in-mouse-watch
    (mouse-pointer (mouse-watch-state workstation-context-specifics))
  (return-from-current-workstation-context
    'mouse-watch :drag mouse-pointer (datum-of-mouse-watch mouse-watch-state)))





(define-event-handler mouse-down-on-close-box-widget
    (mouse-pointer image-plane workspace)
  (enter-close-box-widget-pending-context workspace image-plane))



;;;; Menu-choose context

;;; The menu-choose context is used for the old style of menu tracking, ie,
;;; non-walking.


;; KLudge.
(defvar menu-clean-up-menu-to-keep nil)


(define-workstation-context menu-choose ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :state-variables (menu image-plane menu-serial-number)
  :conc-name t
  :define-enter-context-function t
  :keymap ((<mouse-down> requeue-event-and-return-from-workstation-context)
           ((<mouse-up> menu-item-spot) execute-menu-choice)
           ((<mouse-up> t) abort-workstation-context)
           (<mouse-motion> track-mouse-in-menu-choose-context)))

;; We need the menu and its image-plane in the context, since when we get
;; events outside it, there's no way to get back to it!


(define-event-handler handle-enter-menu-choose (menu image-plane mouse-pointer)
  (if (walking-menus menu-parameters)
      (handle-enter-walking-menus-context mouse-pointer)
      (enter-menu-choose-context :menu menu :image-plane image-plane
                                 :menu-serial-number (copy-frame-serial-number (frame-serial-number menu)))))

;; Handle both cases here.  Should event handlers include applicability predicates?



(def-structure-method valid-workstation-context-p (menu-choose-state)
  (and (funcall-superior-method menu-choose-state)
       (valid-block-in-workstation-context-p
         (menu-choose-state-menu menu-choose-state)
         menu-choose-state)))


(def-structure-method clean-up-workstation-context (menu-choose-state)
  (let ((serial-number (menu-choose-state-menu-serial-number menu-choose-state))
        (menu (menu-choose-state-menu menu-choose-state)))
    ;; To avoid the inhibit-menu-clean-up KLudge, push delete-menu onto the
    ;; after-event-handling queue? ***
    (unless (or (eq menu-clean-up-menu-to-keep menu)
                (frame-has-been-reprocessed-p menu serial-number))
      (delete-menu menu))
    (reclaim-frame-serial-number serial-number))
  (funcall-superior-method menu-choose-state))




;; These handlers might be useful in other contexts.

;;; `Do-nothing-event-handler' is used to consume events.
;;; It use is almost always a sign of a design flaw.  Bad
;;; lexical analysis, etc.

(define-event-handler do-nothing-event-handler ()
  ;; This is SO complex!
  )

(define-event-handler requeue-event-and-return-from-workstation-context (event)
  (requeue-workstation-event current-workstation event)
  (return-from-current-workstation-context type-of-current-workstation-context))

(define-event-handler requeue-event-and-abort-workstation-context (event)
  (requeue-workstation-event current-workstation event)
  (abort-current-workstation-context type-of-current-workstation-context))

(define-event-handler abort-workstation-context ()
  (abort-current-workstation-context type-of-current-workstation-context))


;;; The event-handler `start-dragging-menu-handler' is called directly from the
;;; top level context when the user mouse-downs on a menu title bar.  We begin
;;; dragging the menu, but do not exit any current ws context.

(define-event-handler start-dragging-menu-handler (&optional (menu? menu))
  (when menu?
    (start-dragging-menu menu?)))

;; So, we *assume* here that we are bound to a menu-title-spot.
;; This should be enforced.

(define-event-handler start-dragging-title-bar-handler (mouse-pointer image-plane workspace)
  (let ((title-bar-spot?
          (find-spot-of-type mouse-pointer 'title-bar-spot)))
    (when title-bar-spot?
      (let* ((mouse-down-pointer (mouse-pointer-of-last-down current-workstation))
             (x (x-of-mouse-pointer mouse-down-pointer))
             (y (y-of-mouse-pointer mouse-down-pointer)))
        ;; This used to ignore restrictions. Fixed in 8.0a1 to call a
        ;; subfunction that enforces restrictions. Bug HQ-4753226. (MHD 4/7/04)
        (drag-block-if-permitted
          workspace x y image-plane workspace)))))

(define-event-handler mouse-up-on-title-bar ())        ; noop for now

(define-event-handler title-bar-raise-to-top (image-plane)
  (raise-image-plane-to-top image-plane)
  (when (and (selection-enabled-p)
             (selectable-image-plane-p image-plane))
    (select-image-plane image-plane)))


;;; The event-handler `pop-down-menu' is bound to mouse-select on a menu-title-spot.

(define-event-handler pop-down-menu (menu)
  (delete-menu menu))



;;; The event-handler `execute-menu-choice' interfaces to menus with the
;;; create-submenu function.  It's called by both the walking and non-walking
;;; menu contexts.

(define-event-handler execute-menu-choice (menu spot x-in-window y-in-window)
  (cond ((old-style-menu-p menu)
         #+development
         (cerror "Ignore it" "Old style menu ~s should never happen!" menu))
        (t
         (let ((cell (cell-of-menu-item spot)))        ; Assume spot is a menu-item-spot
           (execute-menu-choice-1 menu cell x-in-window y-in-window)))))


;; New menus only.
;; x,y used only to expose a submenu, if a submenu is required. -fmw, 1/15/02
(defun execute-menu-choice-1 (menu cell x-in-window y-in-window &optional do-not-pop-context)
  (let* ((choice (menu-cell-menu-choice cell))
         (menu-description? (unless (old-style-menu-p menu)
                              (menu-description-of-menu menu)))
         (value (transform-menu-item-after-choice menu-description? choice))
         (choice-function (menu-choice-function menu))
         (args (menu-choice-arglist menu))
         (menu-frame-serial-number (copy-frame-serial-number (frame-serial-number menu)))
         (submenu? nil)
         (name-for-backtrace
           (cond ((partial-command-p choice) (partial-command-name choice))
                 (t choice))))

    (with-drawing-trace (events)
      (format t "Execute menu choice: ~s" choice))

    (with-backtrace-for-internal-error name-for-backtrace

      ;; Pop the context without deleting the menu. KLudge.  Should rearrange
      ;; context to never delete the menu, but rather to enqueue a deletion on
      ;; the after-event queue.

      ;; Don't do any of this if called from native menus: they didn't need to
      ;; push a workstation context (maybe later they will). -fmw, 1/18/02

      (unless do-not-pop-context
        (let ((menu-clean-up-menu-to-keep menu))
          (return-from-current-workstation-context
            ;; for both vanilla and walking menu?
            type-of-current-workstation-context)))

      (cond ((menu-spacer-cell-p cell)
             ;; User somehow chose a separator bar.
             )

            ((aborted-menu-choice? value)
             ;; Aborted choice. Just vanish.  Context & menu cleanup takes care
             ;; of the rest.  This happens, for example, if a workspace in a
             ;; get-workspace submenu is deleted out from under the menu
             ;; choice.
             (dwarn "Menu choice ~s aborted." choice))

            (t
             (notice-choice-made-on-menu menu choice)
             (cond ((old-style-menu-p menu)
                    (dwarn "Old style menu ~s should never happen!" menu)
                    #+ignore
                    (apply choice-function choice menu image-plane
                           x-in-window y-in-window
                           (or original-x-in-window? x-in-window)
                           (or original-y-in-window? y-in-window)
                           args))

                   ((setq submenu? (create-submenu menu choice
                                                   (menu-mouse-pointer menu)))
                    ;; Handle submenus.  Will a choice-function ever want to
                    ;; intercept this?  Do we want the implicit submenus here,
                    ;; too?
                    (expose-menu submenu? x-in-window y-in-window))

                   (t                                        ; New menu.
                    ;; If we're entering dragging context, we have to delete
                    ;; the menu first!!
                    (apply choice-function menu choice value args)))))

      ;; The menu is sometimes deleted for us by the command handler, hence the
      ;; protection against frame-serial-number.
      (unless (frame-has-been-reprocessed-p menu menu-frame-serial-number)
        (cond ((dismiss-menu-after-choice-p menu choice)
               (delete-menu menu))
              (t
               (dehighlight-menu-cell menu cell))))
      (reclaim-frame-serial-number menu-frame-serial-number))))



;;; The function `dismiss-menu-after-choice-p' decides whether the selection
;;; of the given choice on the given menu should dismiss the menu.  It is nearly
;;; always the case that we do want to dismiss it.  The only exception is
;;; color menus, when the choice is not the MORE choice.

(defun dismiss-menu-after-choice-p (menu choice)
  (cond ((null choice)                        ; Click in close-bar.
         t)
        ((color-menu-p menu)
         (or (menu-item-dialog choice)            ; Eg, the more choice.
             (dismiss-color-menu-after-choosing? color-parameters)))
        (t
         t)))



(define-event-handler track-mouse-in-menu-choose-context
    (spot
      (menu-choose-state workstation-context-specifics)
      x-in-window y-in-window
          &optional (menu? menu))
  (let ((cell (when (ab-typep spot 'menu-item-spot)
                (cell-of-menu-item spot)))
        ;; How to guarentee that the structure is really a menu-choose-state?
        (the-menu (menu-choose-state-menu menu-choose-state)))

    (highlight-menu-cell the-menu cell)

    ;; Would like to start dragging immediately when the mouse is on the title bar,
    ;; but we have to careful that mouse-up there (w/o motion) still deletes the menu.
    ;; Another case where mouse-drag has a different binding than mouse-motion or mouse-up.

    (when (or ; (ab-typep spot 'menu-title-spot)
            (and (neq menu? the-menu)                                    ; Over no menu, or some other menu.
                 (start-dragging-menu-p the-menu x-in-window y-in-window)))
      (exit-context-and-start-dragging-menu the-menu))))




(defun start-dragging-menu-p (menu x-in-window y-in-window)
  (>f (distance-from-point-to-table x-in-window y-in-window menu (menu-image-plane menu))
      overshoot-distance-around-menus-before-beginning-dragging))


;;; The function `exit-context-start-dragging-menu' enters a dragging context
;;; on the menu.  It first exits the current workstation context, but without
;;; deleting any menu which may exist there.

(defun exit-context-and-start-dragging-menu (menu)
  ;; Do not delete the menu!
  (let ((menu-clean-up-menu-to-keep menu))
    (return-from-current-workstation-context
      type-of-current-workstation-context ;; both vanilla and walking menus?
      )
    ;; make sure that walking menus get reset so that they go away when appropriate
    ;; -rdf, 1/18/95
    (when (eq (reason-to-not-recycle-menu menu)
              'walking-menu)
      (setf (reason-to-not-recycle-menu menu) nil)))
  (start-dragging-menu menu))


;;; The function `start-dragging-menu' enter dragging context with the mouse
;;; glued to the position of the last mouse down.

(defun start-dragging-menu (menu)
  (let* ((image-plane (menu-image-plane menu))
         (mouse-down-pointer (mouse-pointer-of-last-down current-workstation))
         (x (x-of-mouse-pointer mouse-down-pointer))
         (y (y-of-mouse-pointer mouse-down-pointer)))
    ;; x,y is the position on the image-plane we've grabbed.

    ;; There was a bug which caused this when connecting from an old TW.
    #+development
    (when (contains-invalid-spots mouse-down-pointer)
      (warn "Invalid mouse-pointer in start-dragging-menu: ~s" mouse-down-pointer))

    (enter-image-plane-dragging-context
      image-plane
      (-r x (left-edge-of-image-in-window image-plane))
      (-r y (top-edge-of-image-in-window image-plane))
      t)))



(defun highlight-menu-cell (menu cell)
  (when highlight-selected-menu-items?
    (let ((old-cell (menu-cell-currently-highlighted? menu)))

      (unless (eq cell old-cell)

        (when old-cell
          (highlight-or-unhighlight-cell old-cell menu nil t)
          (setf (menu-cell-currently-highlighted? menu) nil))

        (when (and (menu-choice-cell-p cell)
                   ;; What is this test for?
                   (null (getfq (text-cell-plist cell) 'highlight-color)))
          (let ((flush-graphics-immediately? t))            ; See Note.
            (highlight-or-unhighlight-cell cell menu nil nil))
          (setf (menu-cell-currently-highlighted? menu) cell))
        cell))))


;;; The function `dehighlight-menu-cell' dehighlights the given cell,
;;; only if it is the currently highlighted one.

(defun dehighlight-menu-cell (menu cell)
  (when highlight-selected-menu-items?
    (let ((old-cell (menu-cell-currently-highlighted? menu)))
      (when (eq cell old-cell)
        (when old-cell
          (let ((flush-graphics-immediately? t))            ; See Note.
            (highlight-or-unhighlight-cell old-cell menu nil t))
          (setf (menu-cell-currently-highlighted? menu) nil))))
        cell))

;; Note: Ensure that the highlight/unhighlight pairs are not merged away.  Do
;; this only for menu cells (and action buttons, elsewhere), since we want to
;; avoid doing a sync for program "change the text of" operations, which would
;; slow G2 down too much.  -fmw, 4/25/95



;;; The function `menu-cell-menu-choice' returns the CHOICE for a menu cell.
;;; The choice is either a symbol or a list of the form (submenu <name>)

(defun menu-cell-menu-choice (cell)
  (and cell
       (not (cell-is-block-p cell))
       (getfq (text-cell-plist cell) 'choice)))




;;;; Walking menus



;;; The walking-menus context interfaces to menus with only two functions:
;;;  (create-submenu parent-menu menu-item mouse-pointer), and
;;;  (execute-menu-choice mouse-pointer)


;;; Every menu in the stack needs to have non-NIL reason-to-not-recycle-menu, so that
;;; posting a submenu will not try to reuse the parent menu!

;; Bugs:
;; The half-width computation (in EXPOSE-MENU) is not valid if ws is scaled to fit.

(define-workstation-context walking-menus ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :state-variables (menus                                    ; Stack of exposed menu instances.
                     menu-frame-serial-numbers              ; To check for deletion.
                     menu-cache                             ; Alist of menu-name -> menu instance. (unused).
                     adjustment)                            ; nil (initial), left, or right
  :conc-name t
  :define-enter-context-function t
  :keymap ((<mouse-down> requeue-event-and-return-from-workstation-context)
           ((<mouse-up> menu-item-spot) execute-walking-menu-choice)
           (<mouse-up> abort-workstation-context)
           (<mouse-motion> track-mouse-in-walking-menus-context)))


(define-event-handler handle-enter-walking-menus-context (mouse-pointer menu)
  (setf (reason-to-not-recycle-menu menu) 'walking-menu)
  (let ((state (enter-walking-menus-context
                 :menus (slot-value-list menu)
                 :menu-frame-serial-numbers (slot-value-list (copy-frame-serial-number (frame-serial-number menu)))
                 :adjustment (slot-value-list 'left))))
    (add-mouse-pointer-to-guardians-of-workstation-context
      mouse-pointer state)))


(def-structure-method valid-workstation-context-p (walking-menus-state)
  (and (funcall-superior-method walking-menus-state)
       (loop for menu in (walking-menus-state-menus
                           walking-menus-state)
             for serial-number in (walking-menus-state-menu-frame-serial-numbers
                                    walking-menus-state)
             always (frame-has-not-been-reprocessed-p menu serial-number))))



;; Clean up all the crud.  If menu-to-keep is non-nil, then spare that one.

(def-structure-method clean-up-workstation-context (walking-menus-state)
  (let* ((menus (walking-menus-state-menus walking-menus-state))
         (serial-numbers (walking-menus-state-menu-frame-serial-numbers walking-menus-state))
         (cache (walking-menus-state-menu-cache walking-menus-state))
         (adjustment (walking-menus-state-adjustment walking-menus-state)))

    (loop for menu in menus
          for serial-number in serial-numbers
          unless (or (eq menu menu-clean-up-menu-to-keep)
                     (frame-has-been-reprocessed-p menu serial-number))
            do (delete-menu menu)
          do (reclaim-frame-serial-number serial-number))

    (reclaim-slot-value-list menus)
    (reclaim-slot-value-list serial-numbers)
    (reclaim-slot-value-tree cache)
    (reclaim-slot-value-list adjustment))
  (funcall-superior-method walking-menus-state))




;;; The event-handler `execute-walking-menu-choice' is the same as
;;; execute-menu-choice, except that if the choice we are executing posts a
;;; submenu, and that submenu is currently posted in the walking state, then
;;; keep it.

(define-event-handler execute-walking-menu-choice
    (mouse-pointer
      (walking-menus-state workstation-context-specifics)
      &optional
      (menu? menu))
  (let* ((menus (walking-menus-state-menus walking-menus-state))
         (top-menu (first menus)))

    ;; If the menu we released over is next to the top, then simply keep the
    ;; top menu and exit the context.
    (cond ((eq menu? (second menus))
           (let ((menu-clean-up-menu-to-keep top-menu))
             ;; No longer walking.
             (setf (reason-to-not-recycle-menu top-menu) nil)
             (when new-g2-classic-ui-p
               ;; (New UI.) This puts the title bar onto a walking submenu,
               ;; which is becoming no longer a walking submenu.  It's necessary
               ;; in the new UI only; in the old UI, the contents were put in
               ;; the menu's non-selectable top row.
               (let* ((workspace? (get-workspace-if-any top-menu))
                      (pane current-workstation-detail-pane)
                      (image-plane? (if workspace? (get-image-plane-if-any workspace? pane))))
                 (when image-plane?
                   (setf (menu-workspace-for-is-for-walking-submenu-p workspace?) nil)
                   (post-workspace-in-pane
                     workspace? pane nil nil
                     :existing-image-plane? image-plane?)
                   ;; Get the menu up in a hurry.
                   (refresh-title-bar workspace?)
                   (force-workspace-drawing workspace?))))
             (return-from-current-workstation-context 'walking-menus)))

          ((memq menu? menus)
           (execute-menu-choice mouse-pointer))

          (t
           ;; Mouse-up over some other random menu -- abort.
           (abort-workstation-context mouse-pointer)))))





;;; The function `walking-menus-submenu-to-post?' assumes that the
;;; mouse-pointer is over a menu item or menu title spot, and returns submenu
;;; to post, if any.  We also return the ideal x,y position at which to
;;; position the upper left corner of the menu.

(defun walking-menus-submenu-to-post? (parent-menu mouse-pointer adjustment)
  (with-mouse-pointer-bindings (spot image-plane)
      mouse-pointer
    (when (ab-typep spot 'menu-item-spot)
      (let* ((cell (cell-of-menu-item spot))
             (choice (menu-cell-menu-choice cell))
             (cell-top
               (with-image-plane-transform (image-plane)
                 (y-in-window (menu-item-spot-top spot)))))

        (when (walking-menus-post-submenu-here? mouse-pointer adjustment)
          (let ((submenu? (create-submenu parent-menu choice mouse-pointer adjustment)))
            (when submenu?
              (values submenu?
                      (left-edge-of-image-in-window image-plane)
                      (right-edge-of-image-in-window image-plane)
                      cell-top))))))))


;;; The function `walking-menus-post-submenu-here?' defines the region
;;; of a submenu menu-item which causes the submenu to be posted.  This
;;; is where we encode the fact that submenus are posted when the mouse
;;; is in the right third of the menu cell.

(defun walking-menus-post-submenu-here? (mouse-pointer adjustment)
  (with-mouse-pointer-bindings (spot image-plane)
      mouse-pointer
    (when (ab-typep spot 'menu-item-spot)
      (with-image-plane-transform (image-plane)
        (let* ((x-in-window (x-of-mouse-pointer mouse-pointer))
               (cell-left (x-in-window (menu-item-spot-left spot)))
               (cell-right (x-in-window (menu-item-spot-right spot)))
               (cell-width (-f cell-right cell-left))
               (two-thirds-cell-width (*f 2 (floorf-positive cell-width 3))))
          (case adjustment
            (left
             (>f x-in-window (+f cell-left two-thirds-cell-width)))
            (right
             (<f x-in-window (-f cell-right two-thirds-cell-width)))))))))



;;; The function `walking-menus-post-submenu' posts the given submenu at x,y, and
;;; pushes it onto our state.

(defun walking-menus-post-submenu (parent-menu sub-menu left-x right-x y walking-menus-state)
  (let* ((parent-workspace?
          (get-workspace-if-any parent-menu))
         (default-x-scale?
           (when (and parent-workspace? (image-planes-this-is-on parent-workspace?))
             (image-x-scale (first (image-planes-this-is-on parent-workspace?)))))
         (default-y-scale?
           (when (and parent-workspace? (image-planes-this-is-on parent-workspace?))
             (image-y-scale (first (image-planes-this-is-on parent-workspace?)))))
         (current-adjustment?
          (car (walking-menus-state-adjustment walking-menus-state))))
    (finalize-menu sub-menu)
    (multiple-value-bind (sub-menu-1 adjustment?)
        (expose-menu sub-menu nil y default-x-scale? default-y-scale? right-x left-x
                     (or current-adjustment? t))
      (cond ((null sub-menu-1)
             (when adjustment?
               (setf (car (walking-menus-state-adjustment walking-menus-state)) adjustment?)
               (change-adjustment-of-menu parent-menu adjustment?))
             nil)
            (t
             (unless adjustment?
               (setq adjustment? (car (walking-menus-state-adjustment walking-menus-state))))
             (slot-value-push sub-menu (walking-menus-state-menus walking-menus-state))
             (slot-value-push (copy-frame-serial-number (frame-serial-number sub-menu))
                              (walking-menus-state-menu-frame-serial-numbers walking-menus-state))
             (slot-value-push adjustment? (walking-menus-state-adjustment walking-menus-state))

             ;; Do not allow us to be recycled while we are walking around.
             (setf (reason-to-not-recycle-menu sub-menu) 'walking-menu)

             sub-menu-1)))))

;; It's prettier to post the submenu at the same scale as the parent menu.





(defun menu-image-plane (menu)
  (let ((workspace? (superblock? menu)))
    (when workspace?
      (first (image-planes-this-is-on workspace?)))))



;;; The event-handler `track-mouse-in-walking-menus-context' maintains the invariant:
;;;   n = (length menus) >= 1
;;;   Menus 1...n are exposed.
;;;   Menu cells 1...n-1 are submenu cells and are highlighted.
;;; (Menu cell n may or may not be highlighted).
;;; Here, menu-1 is the first one posted, at the bottom of the stack, and menu-n is at the top.

;;; Our next state is determined by what menu and menu-cell the mouse is
;;; currently over, with a little behavior determined by the precise x,y within
;;; a cell, to wit, we post a submenu only when the mouse is in the right half
;;; of a submenu cell.  We can't easily have a time-delay like the Mac.

;; The drag here would have to be of the entire stack of menus, rigidly.

(define-event-handler (track-mouse-in-walking-menus-context
                        :pretty-name menu-tracking)
    ((walking-menus-state workstation-context-specifics)
     spot mouse-pointer x-in-window y-in-window &optional (menu? menu))
  (let* ((cell? (when (and menu? (ab-typep spot 'menu-item-spot))
                  (cell-of-menu-item spot)))
         (menus (walking-menus-state-menus walking-menus-state))
         (top-menu (first menus))
         (serial-numbers
           (walking-menus-state-menu-frame-serial-numbers
             walking-menus-state)))

    (macrolet ((pop-submenu ()
                 `(let ((menu (slot-value-pop (walking-menus-state-menus
                                                walking-menus-state)))
                        (serial-number (slot-value-pop (walking-menus-state-menu-frame-serial-numbers
                                                         walking-menus-state))))
                    (slot-value-pop (walking-menus-state-adjustment walking-menus-state))
                    (reclaim-frame-serial-number serial-number)
                    (delete-menu menu)
                    (setq top-menu (first (walking-menus-state-menus
                                            walking-menus-state)))))

               (maybe-push-submenu ()
                 `(multiple-value-bind (submenu? left-x right-x y)
                      (walking-menus-submenu-to-post?
                        top-menu mouse-pointer
                        (car (walking-menus-state-adjustment walking-menus-state)))
                    (when submenu?
                      (unless (walking-menus-post-submenu
                                top-menu submenu? left-x right-x y walking-menus-state)
                        ;; direction has changed
                        (multiple-value-bind (submenu? left-x right-x y)
                            (walking-menus-submenu-to-post?
                              top-menu mouse-pointer
                              (car (walking-menus-state-adjustment walking-menus-state)))
                          (when submenu?
                            (walking-menus-post-submenu
                              top-menu submenu? left-x right-x y walking-menus-state))))))))

      ;; Validate all partial commands in the menus, and exit invalid ones?

      (cond ((null menus))                                    ; Lost somehow.

            ((loop for menu in menus                            ; Redundant paranoia.
                   for serial-number in serial-numbers
                   thereis (frame-has-been-reprocessed-p menu serial-number))
             (abort-workstation-context mouse-pointer))

            ((or (null menu?)                                    ; Cruising around outside of it all -- mostly ignore.
                 (null (memq menu? menus)))
             (highlight-menu-cell top-menu nil)
             ;; Allow dragging if only one menu is showing (only case the
             ;; dragging code can handle, anyways).
             (when (and (singleton? menus)
                        (start-dragging-menu-p top-menu x-in-window y-in-window))
               (exit-context-and-start-dragging-menu top-menu)))

            ((eq menu? top-menu)                            ; Selecting from the topmost menu.
             (highlight-menu-cell top-menu cell?)
             (unless (car (walking-menus-state-adjustment walking-menus-state))
               (setf (car (walking-menus-state-adjustment walking-menus-state))
                     (if (walking-menus-post-submenu-here? mouse-pointer 'left)
                         'right
                         'left)))
             (maybe-push-submenu))

            ((memq menu? menus)                                    ; Selecting in some lower menu.
             ;; Pop menus down to but not including the one after MENU.
             (loop for menus = (walking-menus-state-menus walking-menus-state)
                   until (or (null menus)        ; Paranoia.
                             (eq (cadr menus) menu?))
                   do (pop-submenu))

             ;; Pop top-menu if either: current menu cell has changed, or, we
             ;; have moved to the left half of a submenu cell.  If the menu
             ;; cell has not changed, we know that the submenu is now posted
             ;; because of the condition on this cond clause, namely, that we
             ;; are not the top-menu.

             (highlight-menu-cell top-menu nil)                    ;; If we jumped directly to this lower menu.
             (unless (car (walking-menus-state-adjustment walking-menus-state))
               (setf (car (walking-menus-state-adjustment walking-menus-state))
                     (if (walking-menus-post-submenu-here? mouse-pointer 'left)
                         'right
                         'left)))
             (unless (and (eq (menu-cell-currently-highlighted? menu?) cell?)
                          (walking-menus-post-submenu-here?
                            mouse-pointer
                            (car (walking-menus-state-adjustment walking-menus-state))))
               (pop-submenu)
               (highlight-menu-cell menu? cell?)
               (maybe-push-submenu)))

            (t
             ;; Can't happen.
             #+development
             (cerror "Go ahead" "Walking menus are confused"))))))





;;;; Top-level handlers.


;;; Bound to mouse-drag, to initiate moving and dragging over text.

;;; The event-handler `maybe-begin-dragging-handler' is bound to mouse-drag at
;;; top-level.  It requeues a mouse-motion event and enters the older dragging
;;; context.

(define-event-handler maybe-begin-dragging-handler
    (mouse-pointer spot &optional (frame? frame-for-selection)
                   x-in-window y-in-window image-plane)

  ;; The test for pane-background was to avoid getting the G2-window as the
  ;; frame object over pane-background and pane-border spots.  I think that no
  ;; longer happens.
  (when (and frame?
             (not (pane-background-spot-p spot)))

    ;; Let the dragging context see the event, but first, change it back into
    ;; mouse-motion, keeping the modifier bits.
    (requeue-mouse-motion-event mouse-pointer)

    (drag-block-if-permitted
      frame? x-in-window y-in-window image-plane
      (get-workspace-if-any frame?))))




;;; The event-handler `pop-down-attribute-table' deletes the image-plane on
;;; which an attribute table lives, when clicking in its "title bar".
;;; Unfortunately, we also get a table-header-spot from clicks on short
;;; representations.

(define-event-handler pop-down-attribute-table
    (mouse-pointer image-plane
                   &optional
                   (attribute-table? attribute-table)
                   (short-representation-table? short-representation-table))
  (cond (short-representation-table?
         (post-object-menu mouse-pointer))

        ((null attribute-table?)
         (dwarn "There is a bug in pop-down-attribute-table"))

        ((null (superblock? attribute-table?)))                    ; Can this happen?

        ((alternative-classic-attribute-table-p attribute-table?)
         (delete-image-plane image-plane))

        (t
         ;; This case obtains for clicks on the title bar of an attribute table
         ;; which has been transfered to a workspace.  We will post the table
         ;; background menu.
         (post-object-menu mouse-pointer))))




;;; The function `prohibit-default-select-action?', if true, prohibits the
;;; standard post menu or click-to-edit action when selecting the given frame.

(defun prohibit-default-select-action? (frame?)
  (and frame?
       (frame-of-class-p frame? 'authorized-user) ; No menu for these guys.
       (not (user-authorized-in-current-workstation?))))


;;; The variable `enable-click-to-edit-kludge' was added so that a right click
;;; can always post the object menu and avoid click-to-edit. -fmw, 3/7/02

(defvar enable-click-to-edit-kludge t)

;;; The event-handler `really-post-object-menu' posts the menu for the object at
;;; the mouse-pointer, and NEVER enters click-to-edit.  It also handles posting
;;; the selection menu if the item clicked on is a member of a multi-element
;;; selection.

(define-event-handler really-post-object-menu
    (mouse-pointer workstation x-in-window y-in-window image-plane
                   &optional (frame? frame-for-selection)
                   (thing? thing-to-select))
  (cond ((and thing?
              (thing-or-parent-selected-p thing? image-plane)
              (selection-has-multiple-blocks-p image-plane))
         ;; Post selection menu (operate-on-area replacement).
         (post-command-menu
           (find-menu-description 'selection-menu)
           mouse-pointer x-in-window y-in-window frame?))
        (t
         (let ((enable-click-to-edit-kludge nil)) ; Force post-object-menu to not click-to-edit
           (post-object-menu mouse-pointer)))))


;;; The event-handler `post-object-menu' is bound to mouse-select at top level
;;; for most classes of objects.  It either enters click-to-edit or brings up
;;; the menu attached to the given mouse spot, if there is one, which includes
;;; the main-menu, as well as almost all other new menus.

(define-event-handler post-object-menu
    ((event event)
     (spot innermost-spot)
     mouse-pointer timestamp x-in-window y-in-window
     &optional
     (image-plane? image-plane)
     (frame? frame-for-selection))

  #+development (find-bugs-in-post-object-menu event)
  (when frame?
    (make-new-value-for-*-if-appropriate frame?))

  ;; The magic argument "workspace" would pick up the item represented by a
  ;; short-rep.  here what we want is always the workspace on the image plane.
  (let ((workspace? (and image-plane? (workspace-on-image-plane? image-plane?))))

    ;; To be safe, if we do have a workspace, check that it is not deleted.
    ;; This is very old code which should be rethought.
    (when (or (null image-plane?)
              (null workspace?)
              ;; In rare cases, we can have a non-NULL image-plane and
              ;; workspace and yet still have a null serial number in the
              ;; event.  Nobody knows what those cases are. -fmw
              (null (frame-reference-number-for-workstation-event? event))

              (not (frame-has-been-reprocessed-p
                     workspace?
                     (frame-reference-number-for-workstation-event? event))))

      (let ((menu-description? (find-menu-for-spot spot)))
        #+development
        (when (and trace-workstation-events
                   (not (eq trace-workstation-events 'simple)))
          (format t "      --> Thing: ~s,  Menu: ~s~%" frame? menu-description?))

        ;; Bash the event back into shape.
        ;; Is this needed?
        (when (key-code-equivalent-p (workstation-event-code event) 'mouse-select)
          (setf (workstation-event-code event) (key-code 'mouse-up)))

        (cond ((prohibit-default-select-action? frame?))

              ((and enable-click-to-edit-kludge
                    (command-available-p 'click-to-edit mouse-pointer))
               ;; This command takes care of restrictions.
               (start-ui-command 'click-to-edit mouse-pointer))

              (menu-description?
               (let ((title (when (framep frame?) (class frame?))))
                 (post-command-menu
                   menu-description?
                   mouse-pointer x-in-window y-in-window frame? nil nil title)))

              ;; outside-window-spot, eg, gives us a null frame.
              (frame?
               ;; Just a frame with no menu (such as arrow-buttons). Not really
               ;; something to warn abount.
               #+ignore
               (dwarn "We used to enter selection state here for ~s" frame?)))))))


;;; The event-handler `simply-post-object-menu' is a less encumbered version of
;;; post-object-menu, for KB-level use.

(define-event-handler simply-post-object-menu
    ((spot innermost-spot) mouse-pointer x-in-window y-in-window
     &optional (frame? frame-for-selection))
  (let ((menu-description? (find-menu-for-spot spot))
        (title (when (framep frame?) (class frame?))))
    (when menu-description?
      (post-command-menu
        menu-description?
        mouse-pointer x-in-window y-in-window frame? nil nil title))))


;;; The event-handler `menu' is a synonym for post-object-menu. Item
;;; configuration clauses of the form "menu choices .. include/exclude ..."
;;; effectively bind mouse-select to the menu poster.  They return a binding of
;;; MENU in this case, so that MENU is the user-visible name when describing
;;; configurations. Note: that odd behavior has been disabled in the selection
;;; UI. See HQ-4576741 (and HQ-92903).

(define-event-handler menu (mouse-pointer)
  (post-object-menu mouse-pointer))



;;; The event-handler `subcommand-menu' handles mouse-down's on subcommand
;;; buttons at top level (eg, in the inspector).

(define-event-handler subcommand-menu (mouse-pointer innermost-spot)
  (within-named-dynamic-extent for-workstation
    (when (subcommand-menu-button-spot-p innermost-spot)
      (enter-subcommand-context mouse-pointer))))



#+development
(defun find-bugs-in-post-object-menu (event)
  (when (and (frame-reference-number-for-workstation-event? event)
             (not (frame-serial-number-p (frame-reference-number-for-workstation-event? event))))
    (cerror "Continue" "Bug in post-object-menu"))
  (when (eq (context-description-name current-workstation-context) 'selection)
    (warn "BUG: saw mouse-select in selection context.")))




;;; The event-handler `maybe-perform-button-action' is bound to mouse-down on a
;;; button.  I think that buttons are the only things which do stuff on
;;; mouse-down (namely, highlight themselves).

(define-event-handler maybe-perform-button-action
    (mouse-pointer button &optional image-plane x-in-window y-in-window)
  (cond ((null (perform-button-action? button))
         ;; Hmm. Notice the static inheritance here: event-handlers should have
         ;; conditions.
         (if (selection-enabled-p)
             (select-then-search-for-mouse-drag mouse-pointer)
             (search-for-mouse-drag mouse-pointer)))

        ((frame-of-class-p button 'slider)
         (mouse-down-on-slider button image-plane x-in-window y-in-window))

        (t
         (enter-button-down-context button image-plane))))

;;; The event-handler `perform-button-action-or-default' handles double clicks
;;; on buttons in the selection UI.  We run the button's action if we can;
;;; otherwise, the default action.

(define-event-handler perform-button-action-or-default (mouse-pointer button)
  (cond ((perform-button-action? button)
         (maybe-perform-button-action mouse-pointer))
        (t
         (start-ui-command 'perform-default-action mouse-pointer))))


(defun-for-system-procedure g2-ui-post-item-menu (item options g2-window)
  (check-type-or-stack-error options '(structure ((x integer) (y integer))))
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (workstation (workstation-this-is-on gensym-window)))
    (for-workstation (workstation)
      (let* ((user-x-in-window? (evaluation-structure-slot options 'x))
             (user-y-in-window? (evaluation-structure-slot options 'y))
             (x-in-window? (if user-x-in-window?
                               (user-x-in-window-to-internal-x-in-window user-x-in-window? gensym-window)))
             (y-in-window? (if user-y-in-window?
                               (user-y-in-window-to-internal-y-in-window user-y-in-window? gensym-window)))

             ;; Should it default to the item position or the current mouse
             ;; position?  Or maybe to the position of last mouse-down?
             (mouse-pointer (synthesize-mouse-pointer workstation
                                                      item (key-code 'non-event)
                                                      x-in-window? y-in-window?)))
        (simply-post-object-menu mouse-pointer)
        (release-mouse-pointer-if-any mouse-pointer))))
  (reclaim-if-evaluation-value options))


;;;; Menus



(defmenu (main-menu :condition (not short-menus?)
                    :restriction-type main-menu
                    :capitalize t)
    (pane-component-spot)
  start
  pause
  resume
  continue-from-breakpoint ; resume-at-breakpoint
  reset
  restart
  new-workspace
  get-workspace
  ;; view-options ; deferred (MHD 11/11/99)
  inspect
  load-kb
  merge-kb
  save-kb
  show-system-table
  (submenu run-options)
  change-mode
  (submenu miscellany-menu miscellany)
  launch-online-help)

(defmenu (short-main-menu :title main-menu :condition short-menus?
                          :restriction-type main-menu
                          :capitalize t)
    (pane-component-spot)
  start
  pause
  resume
  reset
  restart
  new-workspace
  get-workspace
  inspect
  (submenu load-merge-save)
  change-mode
  (submenu short-miscellany-menu miscellany)
  launch-online-help)


(defmenu (main-menu-miscellany-menu-common
           :restriction-type main-menu)
    ()
  new-title-block
  neatly-stack-windows
  network-info
  close-telewindows-connection
  log-out

  change-password
  reinstall-authorized-users

  #+development memory-management-table
  #+development telewindows-status-table

  ;; jh, 7/2/92.  We can't optimize memory until we have a reliable garbage
  ;; collector.  The Chestnut collector is antediluvian in that it uses a stack.
  ;; Also, its relocation scheme consumes an extra word per object.
  ;;  optimize-memory

  ;; jh, 6/17/91.  Replaced load-c-file and load-fortran-file with
  ;; connect-to-foreign-file to accomodate the new foreign function design.
  ;; load-c-file load-fortran-file
  connect-to-foreign-image
  disconnect-from-foreign-image

  (submenu source-code-control-menu source-code-control)

  load-attribute-file
  write-g2-stats
  clear-kb
  shut-down-G2

  turn-on-all-explanation-caching
  turn-off-all-explanation-caching

  (include package-preparation-menu)
  detect-deadlocks-for-ui
  detect-and-break-deadlocks-for-ui)



(defmenu (package-preparation-menu :title package-preparation :capitalize t
           :restriction-type main-menu)
    ()
  enter-package-preparation-mode
  leave-package-preparation-mode
  strip-texts-now
  make-workspaces-proprietary-now
  flush-change-log-for-entire-kb
  enter-simulate-proprietary-mode
  leave-simulate-proprietary-mode)




(defmenu (miscellany-menu :title main-menu-miscellany :capitalize t
                          :restriction-type main-menu)
    ()
  about-telewindows-in-misc-menu        ; Yuck
  short-menus
  create-new-module
  delete-module
  (include main-menu-miscellany-menu-common))

(defmenu (short-miscellany-menu :title main-menu-miscellany :capitalize t
                                :restriction-type main-menu)
    ()
  long-menus
  create-new-module
  delete-module
  show-system-table
  (submenu run-options)
  (include main-menu-miscellany-menu-common))

(defmenu (source-code-control-menu :title source-code-control
                                   :condition source-code-control-support-enabled-p
                                   :capitalize t
                                   :restriction-type main-menu)
    ()
  update-file
  edit-file
  unedit-file
  commit-file
  revert-file)

(defmenu (run-options :capitalize t
                      :restriction-type main-menu)
    (window)
  do-not-highlight-invoked-rules
  highlight-invoked-rules
  enable-all-items
  remove-tracing-and-breakpoints)


(defmenu (menu-size :capitalize t
              :restriction-type main-menu)
    (window)
  small
  medium
  large)


(defmenu (load-merge-save :title "Load/Merge/Save" :capitalize t
                          :restriction-type main-menu)
    ()
  load-kb
  merge-kb
  save-kb)



(defmenu user-menu-choices ()
  (let* ((frame? (most-interesting-frame mouse-pointer))
         (choices (and frame? (compute-user-menu-choices frame?))))
    (prog1
        (loop for choice in choices
              collect (slot-value-list 'user-menu-choice choice)
                using slot-value-cons)
      (reclaim-slot-value-list choices))))

;; Restriction type?


;; Could menu-title default to the plural of the ptype name?

(define-presentation-type system-table ()
  :menu-options (:title system-tables :capitalize t)
  :choices (compute-system-table-choices)
  :choice-transformer system-table-name-to-frame
  :tester ((x) (framep x)))

(defun system-table-name-to-frame (name)
  (case name
    (this-window
     (if servicing-workstation?
         (g2-window-for-this-workstation? current-workstation)))
    (t
     (symbol-value name))))


(define-presentation-type deletable-module ()
  :menu-options (:title choose-a-module-to-delete)
  :choices (compute-module-deletion-choices))



;;;; Reserved Menu Choice Names

;;; There are a number of new reserved names in 4.0, which conflict with, and
;;; can no longer be used for, user-menu-choices.  The name conflict occurs in
;;; item configurations: there is no way to tell from "pressing control+c
;;; implies full-scale" whether the user meant the built-in FULL-SCALE command
;;; or some user menu choice with that name.

;;; Currently the choice taken is determined entirely by the predicate
;;; `built-in-menu-choice-p'.  If it returns true for some symbol S, then
;;;   (1) The name S in an item configuration runs the built-in UI command.
;;;   (2) A user menu choice with label S will get frame notes.

;;; In order to make it possible for users to run global keyboard command
;;; choices via new bindings in item configurations, we had to make them be
;;; built-in-menu-choices, thus robbing the user of those names for
;;; user-menu-choices.  This has the potential of breaking 3.0 kbs which used
;;; those names, although they will get frame notes.  The committee on truth
;;; and purity of design has decided that the names below are esoteric enough
;;; that we can steal them.

;;; There a least two better ways we might solve this problem someday:
;;;  (1) Extend the grammar of item configuration to include a marker which discriminates
;;;      user menu choices and built-in menus choices (eg, "built-in" and "user").
;;;  (2) Allow user menu choices to have a non-unique menu labels, while invoking them
;;;      with their unique name.

;; -fmw, 10/11/94


;;; The new choices are:
;;;  item-menu-choice: lift-to-top drop-to-bottom go-to-referenced-item
;;;                    clone-as-trend-chart
;; There are a bunch more just for trend charts: plots, link-to-default, etc.



;; Temporarily add the commands this way, rather than cluttering all the
;; define-ui-command forms with :category global-keyboard-command-choice, or
;; whatever -fmw, 10/21/93




(def-grammar-choices-for-menu main-menu-choice
    . #. main-menu-choices)

(def-grammar-choices-for-menu workspace-menu-choice
    . #. workspace-menu-choices)

(def-grammar-choices-for-menu item-menu-choice
    . #. item-menu-choices)

#+enable-ole
(def-grammar-choices-for-menu item-menu-choice-available-with-mouse-down
    . #. item-menu-choices-available-with-mouse-down)

(def-grammar-choices-for-menu table-menu-choice
    . #. table-menu-choices)



;;; The grammar-category `global-keyboard-command-choice' includes commands
;;; bound to keystrokes by default.  They can only be disabled, not added to.

(def-grammar-category global-keyboard-command-choice ()
  . #. global-keyboard-command-choices)


(def-grammar-choices-for-menu global-keyboard-command-choice
    . #. global-keyboard-command-choices)




;;;; Named Workspace presentation type




(defun named-workspaces-exist-p ()
  (loop for workspace being each class-instance of 'workspace
        as primary-name? = (get-primary-name-for-frame-if-any workspace)
        thereis (and primary-name?
                     (workspaces-can-be-shown-at-this-kb-level-p
                       workspace current-workstation)
                     (workspace-can-appear-on-workstation-p
                       workspace current-workstation))))

;; This loop is repeated in def-menu main-menu and in
;; handle-get-workspace-window-menu-choice, both in facilities.  In leaks frame
;; conses due to a bug in the class-instance loop path.



(defun choice-sort (choice1 choice2)
  (string<w                                ; <- our string< doesn't currently
    (stringw (second choice1))                ;    handle symbols; here, we want
    (stringw (second choice2))))        ;    to handle either a string or symbol

(defun compute-list-of-named-workspaces ()
  ;; The menu items here are (choice label name-of-workspace-as-symbol-or-string)
  (loop for workspace being each class-instance of 'workspace
        as primary-name? = (get-primary-name-for-frame-if-any workspace) ; put up all names?
        when (and primary-name?
                  (workspaces-can-be-shown-at-this-kb-level-p workspace current-workstation)
                  (workspace-can-appear-on-workstation-p workspace current-workstation))
          collect
          (let ((frame-or-frames
                  (frame-or-frames-with-this-name primary-name?)))
            (if (and (consp frame-or-frames)
                     ;; other workspaces with the same name?
                     (loop for frame in frame-or-frames
                           thereis (and (not (eq frame workspace))
                                        (frame-of-class-p frame 'workspace)
                                        ;; Don't do this for workstation-
                                        ;;   specific workspaces:
                                        (or (not (frame-of-class-p frame 'non-kb-workspace))
                                            (null
                                              (only-workstation-this-non-kb-workspace-can-be-on?
                                                workspace))))))
                (make-menu-choice
                  (tformat-text-string "~a  (~a)"
                                       primary-name?
                                       (get-or-make-up-debugging-name-for-block workspace))
                  (copy-text-string (get-or-make-up-debugging-name-for-block workspace)))
                (make-menu-choice
                  (copy-text-string (stringw primary-name?))
                  primary-name?)))
            into choices using slot-value-cons
        finally
          (setq choices
                (sort-list
                  choices                        ; option to sort by stack-of-image-planes position?
                  #'choice-sort nil))
          (return choices)))


;;; The presentation-type `named-kb-workspace' posts a menu of named
;;; workspaces, and returns a workspace instance.  If the chosen workspace has
;;; been deleted by the time that it is chosen, then this ptype returns NIL,
;;; although the tester function will filter that out.  The net result is that
;;; commands which take workspaces will be silently skipped if their workspace
;;; was deleted.

(define-presentation-type named-kb-workspace ()
  :available-p named-workspaces-exist-p
  :choices (compute-list-of-named-workspaces)
  :choice-transformer get-workspace
  :menu-options (:title named-workspaces)
  :tester ((x) (and (framep x) (workspace-p x))))


;;; `Confirm-or-cancel' Callback should be a function or a symbol naming a
;;; function. Arguments should be a slot-value list or arguments to the callback
;;; function.  The conses of arguments will be reclaimed by this mechanism. Note
;;; that the arguments are _not_ format args.

(defun confirm-or-cancel (message callback &optional arguments)
  (enter-dialog message
                nil nil
                callback arguments
                nil nil
                (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))
                (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))

;; Added some of the above documentation for the format control string subtlety after
;; reviewing use by callers.  (MHD 7/20/94)

;; Needs to just be a function to call which takes a continuation argument.
(define-presentation-type confirm-or-cancel ()
  )


;;; The function `message' posts a message in a pop-up dialog box.

(defun message (message)
  (enter-dialog (copy-wide-string message)
                nil 'none
                'do-nothing ()
                nil nil
                (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))
                (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))))

(defun do-nothing ())



;;;; recent loaded kb presentation type

(defun recent-loaded-kb-available-p ()
  (and (g2-enterprise-p)
       (load-kb-permitted-p)
       (loop for pathname in recent-loaded-kbs
	     thereis pathname)))

(defun compute-list-of-recent-loaded-kb ()
  (loop with menu-choices = nil
	for pathname in recent-loaded-kbs
	do (slot-value-push (make-menu-choice (gensym-namestring pathname)
					      (gensym-namestring pathname))
		menu-choices)
	finally (return menu-choices)))

;;; The presentation-type `recent-loaded-kb' posts a menu of recent loaded kb files,
;;; and returns a kb pathname instance.

(define-presentation-type recent-loaded-kb ()
  :available-p recent-loaded-kb-available-p
  :choices (compute-list-of-recent-loaded-kb)
  :choice-transformer get-recent-loaded-kb
  :menu-options (:title recent-loaded-kb)
  :tester ((x) (and x (gensym-pathname-p x))))




;;;; Stripping and marking menu



;; This piece is common to many menus.
(defmenu (stripping-and-marking-menu
           :restriction-type item-menu)
    ()
  mark-to-strip-text
  mark-to-strip-text-*
  remove-strip-text-mark
  remove-strip-text-mark-*
  mark-not-to-strip-text-*
  mark-not-to-strip-text
  remove-do-not-strip-text-mark-*
  remove-do-not-strip-text-mark)




;;;; The workspace menu


;; *** This needs long and short versions.
;; Maybe add TOKEN-MENU-BUTTON-SPOT, until all of the old event handlers are gone,
;; and find-menu-for-spot is again allowed to search enclosing spots?

(defmenu (workspace-menu :class-name-or-names-for-export kb-workspace
                         :capitalize t :condition (not short-menus?) :restriction-type workspace-menu)
    (kb-workspace-image-plane-spot workspace-background-spot)
  (include item-creation-menu)
  name-workspace
  clone-workspace
  table
  color-workspace                                ; Maybe color-frame would be enough.
  move-workspace
  hide-workspace                                ; New position.  Get some review! (MHD 1/30/90)
  go-to-superior                        ; new for 8.1 (MHD 3/25/05)
  lift-to-top
  drop-to-bottom
  shrink-wrap
  ;; hide-workspace used to be here -- moved far away from delete by popular demand
  delete-workspace
  enable-workspace
  disable-workspace
  (submenu main-menu)                        ; But, never walking?
  operate-on-area

  describe
  table-of-hidden-attributes
  describe-configuration
  print-to-server
  print-to-client

  ;; For BPEL/G2GL - process body workspaces
  compile-g2gl-process-workspace
  clean-up-g2gl-compilation-postings-on-body
  execute-g2gl-process-workspace
  redo-layout-of-g2gl-body

  ;; For BPEL/G2GL - execution display workspaces
  single-step do-not-single-step
  close-and-continue
  break-on-execution-faults do-not-break-on-execution-faults
  remove-all-temporary-breakpoints
  bring-up-source
  pause-process-instance resume-process-instance
  delete-process-instance
  process-display-attributes
  g2gl-system-attributes

  (include stripping-and-marking-menu)
  (include user-menu-choices))


(defmenu (short-workspace-menu :capitalize t
                               :condition short-menus?
                               :restriction-type workspace-menu)
    (kb-workspace-image-plane-spot workspace-background-spot)
  (include item-creation-menu)
  move-workspace
  hide-workspace
  enable-workspace
  disable-workspace
  (submenu workspace-miscellany miscellany)
  (submenu short-main-menu)
  operate-on-area)


(defmenu (workspace-miscellany :capitalize t
                               :restriction-type workspace-menu)
    ()
  name-workspace
  clone-workspace
  table
  color-workspace
  lift-to-top
  drop-to-bottom
  shrink-wrap
  delete-workspace
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
  describe-configuration
  print-to-server
  print-to-client
  (include stripping-and-marking-menu))



(defmenu item-creation-menu ()
  new-object
  new-rule
  new-display
  new-definition
  new-free-text
  new-button)







;;;; Color menu


;;; The function `list-of-colors-for-level' returns the list of table rows for
;;; a color menu at the given level, 1 or 2.

(defun uncolumnified-list-of-colors-for-level (level-number)
  (let* ((color-set
           (case level-number
             (1 (colors-on-1st-level-color-menu color-parameters))
             (2 (colors-on-2nd-level-color-menu color-parameters))))
         (colors-in-order
           (case (color-menu-ordering color-parameters)
             (alphabetic menu-colors-sorted-alphabetically)
             (hue menu-colors-sorted-by-hue)
             (t   menu-colors))))                            ; by intensity
    (loop for color in colors-in-order
          when (case color-set
                 (standard-set (memq color standard-gensym-color-subset))
                 (all t)
                 (all-including-new-pastels t)                    ; curious
                 (t (memq color color-set)))
            collect color using slot-value-cons)))


(defun list-of-colors-for-level (level-number)
  (let* ((colors (uncolumnified-list-of-colors-for-level level-number))
         (number-of-columns
           (case level-number
             (1 (number-of-columns-for-1st-level-color-menu color-parameters))
             (2 (number-of-columns-for-2nd-level-color-menu color-parameters)))))

    (if (<=f number-of-columns 1)
        colors
        ;; Columnify
        (loop while colors
              as row = (loop for i below number-of-columns
                             as color? = (slot-value-pop colors)
                             collect color? using slot-value-cons)
              ;; Mutate (a b nil .. nil) into (a nil ... nil b)
              if (null (car (last row)))
                do (loop for sublist on row
                         when (null (cadr sublist))
                           do (rotatef (car sublist) (car (last row)))
                             (return))
              collect (slot-value-cons 'row row)
                using slot-value-cons))))

;; Plucked from the hairy guts of post-color-choice-menu




(defun compute-transparent-and-foreground-colors (block?)
  (let (workspace?)
    (cond ((null block?)
           (values 'white 'black))
          ((null (setq workspace?
                       (unless (frame-of-class-p block? 'workspace)
                         (get-workspace-if-any block?))))
           (values 'white 'black))
          (t
           (values (or (workspace-background-color? workspace?)
                       'white)
                   (or (workspace-foreground-color? workspace?)
                       'black))))))



;;; The function `make-text-cell-for-color' handles the meta-colors MORE,
;;; TRANSPARENT, and FOREGROUND.

(defun make-text-cell-for-color (menu-description color format &optional block)
  (declare (ignore menu-description format))
  (multiple-value-bind (color-of-transparent color-of-foreground)
      (compute-transparent-and-foreground-colors block)
    (multiple-value-bind (choice real-color color-name)
        (case color
          (more
           (values (slot-value-list 'dialog
                                    (copy-text-string "(More ...)")
                                    'choose-more-colors)
                   'black
                   (copy-text-string "(More ...)")))
          (transparent
           (values color
                   color-of-transparent
                   (copy-symbol-name color nil)))
          (foreground
           (values color
                   color-of-foreground
                   (copy-symbol-name color nil)))
          (t
           (values color
                   color
                   (copy-symbol-name color nil t))))
      (make-text-cell
        (convert-text-string-to-text color-name)
        (choose-color-menu-item-format-per-menu-parameters)
        (slot-value-list
          'choice choice
          'background-color real-color
          'line-color (case (map-to-black-or-white real-color)
                        (white 'black)
                        (black 'white)))))))



;;; The function `choose-more-colors' posts the "dialog" which is the full menu
;;; of colors. It is called via the dialog menu item included in the colors
;;; menu, above.  We simply continue pursuing the command, but now in "dialog"
;;; mode.

(defun choose-more-colors (partial-command which-argument choice mouse-pointer)
  (declare (ignore which-argument choice))
  (pursue-partial-command (copy-partial-command partial-command)
                          mouse-pointer
                          'dialog))

;; Calling the mode "dialog" is a bit bogus -- the UI is just a longer menu.



;; Used only by the icon editor.  Includes the metacolors.

(defmenu (full-color-menu
           :type new-menu                                    ; It's just a choice menu, no commands.
           :make-text-cell make-text-cell-for-color)
    ()
  (compute-list-of-colors 2 t))


(defun post-full-color-menu
    (title mouse-pointer what-this-is-a-menu-for? choice-function arglist)
  (post-menu-named 'full-color-menu
                   :mouse-pointer mouse-pointer
                   :what-this-is-a-menu-for what-this-is-a-menu-for?
                   :title title
                   :choice-function choice-function
                   :choice-function-arguments arglist))



;;; The presentation-type `color' returns a non-NIL symbol from a choice from
;;; the first-level color menu, not including transparent nor foreground.
;;; Note the special make-text-cell method.

(define-presentation-type color ()
  :menu-options (:make-text-cell make-text-cell-for-color)
  :tester ((x) x)                                            ; Yuck.
  :choices (compute-list-of-colors (if (eq presentation-mode 'dialog) 2 1)
                                   nil))


;;; The presentation-type `metacolor' does include transparent and foreground.

(define-presentation-type metacolor ()
  :menu-options (:make-text-cell make-text-cell-for-color)
  :tester ((x) x)                                            ; Yuck.
  :choices (compute-list-of-colors (if (eq presentation-mode 'dialog) 2 1)
                                   t))





;;; The function `compute-list-of-colors' computes the list of choices for the
;;; first or second-level color menus.

(defun compute-list-of-colors (level-number include-metacolors?)
  (nconc (and include-metacolors?
              (slot-value-list 'transparent 'foreground))

         (list-of-colors-for-level level-number)

         (when (eql level-number 1)
           (slot-value-list 'more))))


;;; The function `color-menu-p' is needed to implement the do-not-dismiss
;;; option for color menus.  It is a kludgey derived predicate, which should be
;;; made explicit if we really want this feature.

(defun color-menu-p (menu)
  (cond ((new-style-menu-p menu)
         (let ((desc (menu-description-of-menu menu)))
           (and desc
                (memq (menu-description-name desc)
                      '(color-menu metacolor-menu)))))
        (t
         ;; This case should no longer obtain.
         #+development (cerror "Continue" "Old-style menu ~s" menu)
         (eq (menu-choice-function menu)
             'handle-choice-for-color-menu))))



;;; The function `regions-and-colors-of-entity' returns an alist of (region
;;; . color) for each region in the entity's icon description.  Except, if (eq
;;; region color) for some entry, then that region is unnamed, and both symbols
;;; name a color.  Thus, a region cannot have the same name as a color (for no
;;; good reason).

(defun regions-and-colors-of-entity (entity)
  (cdr (car (icon-line-drawing-description (icon-description entity)))))


;;; The function `colorable-regions-of-frame' returns a slot-value-list of the
;;; colorable region names of the given frame.

(defun colorable-regions-of-frame (frame)
  (frame-class-case frame
    (connection
      (loop for (region) in (get-cross-section-regions (cross-section-pattern frame))
            collect region using slot-value-cons))
    (text-box                                                    ; border only if non-zero width?! Sure.
      (nconc
        (slot-value-list 'background-color)
        (when (text-box-has-border-p frame)
          (slot-value-list 'border-color))
        (slot-value-list 'text-color)))
    (workspace
      (slot-value-list 'background-color 'foreground-color))
    (button ())                                                    ; do!
    (entity
      (when (polychrome-icon-p frame)
        (cond
          ((null (regions-and-colors-of-entity frame))
           (slot-value-list 'icon-color))
          (t
           (loop with include-icon-color-region? = nil
                 for (region . color) in (regions-and-colors-of-entity frame)
                 unless (eq region color)                            ; Means that the region is unnamed.
                   collect region into result using slot-value-cons
                 when (eq region 'foreground)
                   do (setq include-icon-color-region? t)
                 finally
                   (return
                     (if (and include-icon-color-region?
                              (not (memq 'icon-color result)))
                         (slot-value-cons 'icon-color result)
                         result)))))))))

;; I added the explicit return of the icon-color region, for icons which
;; do not have regions.


(define-presentation-type colorable-regions-of-frame (frame)
  :menu-options (:title choose-a-region :strip-hyphens nil)
  :choices (colorable-regions-of-frame frame)
  :immediate-value ((frame)
                    (let ((regions (colorable-regions-of-frame frame)))
                      (prog1 (and (singleton? regions)
                                  (first regions))
                        (reclaim-slot-value-list regions)))))

;; Should there be a default when FRAME is not supplied?
;; We want to strip hyphens from the title, but not the body.

;; Fix for now with this def-menu-string:

(def-menu-string choose-a-region "Choose a Region")



;;;; Hierarchical Class Menu





;;; The function `class-inferior-choices' returns the list of next-level choices
;;; once the given class has been chosen.  Note that this list may contain CLASS
;;; itself if the class was a submenu in the upper menu (which will normally be
;;; the case if we are calling this function at all).  If we are
;;; choosing-superior-class, then we ignore do-not-put-in-menus and
;;; not-userable-instantiable class features, and check only
;;; whether the class has a foundation-class class feature.  The list is a NEWLY
;;; consed slot-value list.

(defun class-inferior-choices (class &optional choosing-superior-class?)
  (let ((class-features (class-features (class-description class))))
    (cond ((and (classp class)
                (not (subclassp class 'item)))
           nil)
          ((and (not choosing-superior-class?)
                (feature-assq-macro 'do-not-put-in-menus class-features)
                (not (feature-assq-macro 'not-user-instantiable class-features)))
           (class-flattened-choices
             (inferior-classes class) choosing-superior-class?))

          (t
           (let ((inferior-class-choices
                   (class-flattened-choices
                     (inferior-classes class) choosing-superior-class?))
                 (exclude-this-class?
                   (if choosing-superior-class?
                       (not (get-class-feature-if-any
                              class 'foundation-class))
                       (feature-assq-macro 'not-user-instantiable class-features))))
             (if exclude-this-class?
                 inferior-class-choices
                 (slot-value-cons class inferior-class-choices)))))))




;;; The function `class-flattened-choices' returns the ultimate list of choices
;;; which obtain for class.  Normally, this list is just (list class).  But if
;;; class has been hidden for some reason (no foundation-class class feature or
;;; do-not-put-in-menus) then we skip over class and go directly to its
;;; inferiors.  The function's domain has been extended to lists of classes in
;;; the natural fashion.

(defun class-flattened-choices (class &optional choosing-superior-class?)
  (cond ((null class)
         nil)

        ((menu-item-is-spacer-p class)                            ; We can pass in some menu-item here, too.
         (slot-value-list class))

        ((and (symbolp class)                                    ; Just catches authorized-user
              (not (class-is-authorized-p class)))
         nil)

        ((consp class)
         (loop for class-1 in class
               nconc (class-flattened-choices class-1 choosing-superior-class?)))

        ((and (classp class)
              (not (subclassp class 'item)))
         nil)

        (choosing-superior-class?
         (cond ((and (not (get-class-feature-if-any class 'foundation-class))
                     (not (loop for subclass being each subclass of class
                                thereis (get-class-feature-if-any
                                          subclass 'foundation-class))))
                nil)
               (t
                (let ((inferior-class-choices (inferior-classes class)))
                  (cond ((and (not (get-class-feature-if-any
                                     class 'foundation-class))
                              (singleton? inferior-class-choices))
                         (class-flattened-choices
                           inferior-class-choices choosing-superior-class?))
                        (t
                         (slot-value-list class)))))))

        ;; Avoid adding a class that has no instantiable subclasses
        ;; (dead-end class)
        ((and (get-class-feature-if-any class 'not-user-instantiable)
              (not (get-class-feature-if-any class 'do-not-put-in-menus))
              (loop for subclass being each subclass of class
                    when (and (not (get-class-feature-if-any
                                     subclass 'not-user-instantiable))
                              (not (get-class-feature-if-any
                                     subclass 'do-not-put-in-menus)))
                      return nil
                    finally (return t)))
         nil)

        ((get-class-feature-if-any class 'do-not-put-in-menus)
         (class-flattened-choices
           (inferior-classes class) choosing-superior-class?))

        (t
         (slot-value-list class))))



(defun class-has-submenu-p (class &optional choosing-superior-class?)
  (let ((choices
          (and (classp class)
               (class-inferior-choices class choosing-superior-class?))))
    (prog1 (not (and (singleton? choices)
                     (eq (first choices) class)))
      (reclaim-slot-value-list choices))))


;;; The function `compute-class-choices-for-menu' returns menu-item list for
;;; choosing a subclass of the given class or classes.  It is freshly consed.
;;; If we are choosing a superior class, then all classes are allowed.  Otherwise,
;;; only instantiable classes are.

(defun compute-class-choices-for-menu
    (class-or-classes &optional choosing-superior-class?)
  (let ((classes (class-flattened-choices
                   class-or-classes choosing-superior-class?)))
    (unless choosing-superior-class?
      (setq classes
            (loop with new-list = nil
                  for class in classes
                  unless (and (not (menu-item-is-spacer-p class))
                              (or (memq class new-list)
                                  ;; There is a superior of class in the list and
                                  ;; its submenu will include class.
                                  (loop for class1 in classes
                                        thereis (and (neq class class1)
                                                     (subclassp class class1)))))
                    do (setq new-list (nconc new-list (slot-value-list class)))
                  finally (progn
                            (reclaim-slot-value-list classes)
                            (return new-list)))))
    (prog1
        (loop for class in classes
              for submenu-p = (and ; (neq class class-or-classes)
                                (class-has-submenu-p class choosing-superior-class?))
              collect (if submenu-p
                          (slot-value-list 'submenu class)
                          class)
                using slot-value-cons)
      (reclaim-slot-value-list classes))))


(defun compute-class-inferior-choices-for-menu-1 (class &optional choosing-superior-class?)
  (loop with inferior-choices = (and (classp class)
                                     (class-inferior-choices
                                       class choosing-superior-class?))
        for inferior in inferior-choices
        for submenu-p = (and (neq inferior class)
                             (class-has-submenu-p inferior choosing-superior-class?))
        with choices  = nil
        do
    (slot-value-push
      (if submenu-p
              (slot-value-list 'submenu inferior)
              inferior)
          choices)
        finally
          (progn
            (reclaim-slot-value-list inferior-choices)
            (return (nreverse choices)))))

(defun compute-class-inferior-choices-for-menu (menu class mouse-pointer)
  (declare (ignore menu mouse-pointer))
  (compute-class-inferior-choices-for-menu-1 class))



;;; `Compute-immediate-basic-class-choice-if-any' returns nil if there is either
;;; less than or more than one element in the result of calling
;;;
;;;    (compute-class-choices-for-menu class-or-classes)
;;;
;;; Otherwise, it returns the single choice as a menu item.  This results in no
;;; net consing; any intermediate results are reclaimed.

(defun-simple compute-immediate-basic-class-choice-if-any (class-or-classes)
  (let ((menu-item-list (compute-class-choices-for-menu class-or-classes)))
    (prog1
        (if (and menu-item-list
                 (null (cdr menu-item-list))
                 (first menu-item-list)
                 (symbolp (first menu-item-list))) ; Not, e.g., (submenu name)
            (first menu-item-list))
      (reclaim-slot-value-list menu-item-list))))

;; It is inferred from the code for the presentation type that only the spine of
;; this menu item list is freshly consed.  Based on that code, this therefore
;; only reclaims the top-level conses as slot value conses.  (MHD 5/5/97)


;;; The presentation-type `class-name' accepts the name of any subclass
;;; of the given list of root classes. Superclasses can be a symbol or a
;;; list of symbols.

(define-presentation-type class-name (superclasses)
  :menu-options (:title choose-a-class  :capitalize nil  :strip-hyphens nil)
  :choices (compute-class-choices-for-menu superclasses)
  :submenu-choices compute-class-inferior-choices-for-menu)

;; This should take &key allow-any-class, choosing-superior-class etc.


;; *** Temporary fix ***
(def-menu-string choose-a-class "choose a class")


;;; The presentation-type `superior-class' chooses the name of an existing
;;; class appropriate for a superior-class of the given definition frame.

(define-presentation-type superior-class (frame)
  :menu-options (:title choose-a-class :strip-hyphens nil)
  :choices (compute-superior-class-choices frame)
  :submenu-choices compute-superior-class-choices-1)

;; This ought to not include the name of the frame itself, but that's hard to fix.

(defun compute-superior-class-choices (frame)
  (let ((base-class (base-class-for-slot frame 'direct-superiors-of-defined-class nil)))
    (slot-value-cons base-class
                     (compute-class-choices-for-menu
                       (inferior-classes base-class) t))))

(defun compute-superior-class-choices-1 (menu class mouse-pointer)
  (declare (ignore menu mouse-pointer))
  (compute-class-inferior-choices-for-menu-1 class t))



(defun base-class-for-slot (frame slot-name defining-class?)
  (or (second (get-slot-feature-if-any
                (class frame) slot-name 'class-of-optional-subframe
                defining-class?))
      'object))





;;; The presentation-type `subframe-class' is like class-name, except for the
;;; choice of base classes.  Also, it has an immediate-value, like regions.

(define-presentation-type subframe-class (frame slot-name defining-class?)
  :menu-options (:title choose-a-class :strip-hyphens nil)
  :choices (compute-class-choices-for-subframe frame slot-name defining-class?)
  :submenu-choices compute-class-inferior-choices-for-menu

  ;; Hmm. The code for choose-class-for-slot-and-act-on-it had this test to
  ;; skip the choosing.  How often does this arise?
  :immediate-value ((frame slot-name defining-class?)
                    (let ((class-choices (compute-class-choices-for-subframe
                                           frame slot-name defining-class?)))
                      (cond ((and (singleton? class-choices)
                                  (symbolp (car class-choices))        ; Not, eg, (submenu name).
                                  (not (and (get-class-feature-if-any
                                              (car class-choices) 'not-user-instantiable)
                                            (get-class-feature-if-any
                                              (car class-choices) 'do-not-put-in-menus))))
                             (prog1 (car class-choices)
                               (reclaim-slot-value-list class-choices)))
                            (t
                             (reclaim-slot-value-list class-choices)
                             nil)))))


;;; The function `compute-class-choices-for-subframe' returns the initial list of
;;; classes allowed for a subframe of the given slot.

(defun compute-class-choices-for-subframe (frame slot-name defining-class?
                                                 &optional choosing-superior-class?)
  (let ((base-class
          (base-class-for-slot frame slot-name defining-class?)))
    (compute-class-choices-for-menu base-class choosing-superior-class?)))





;; The type parameter-menu ought to be inherited from class-of-definition.
;; :submenu-choices, too.

(defmenu (basic-definition-classes :type parameter-menu
                                   :submenu-choices compute-class-inferior-choices-for-menu)
    ()
  (compute-class-choices-for-menu
    '(class-definition)))


(defmenu (extended-definition-classes :condition t
                                      #+pre-g2-v5-licensing
                                      (not (restricted-use-option-authorized-p))
                                      :type parameter-menu
                                      :submenu-choices compute-class-inferior-choices-for-menu)

    ()
  (compute-class-choices-for-menu
    '(------
      procedure
      user-menu-choice
      relation
      ------
      function-definition
      foreign-function-declaration
      tabular-function
      ------
      tokenizer
      text-conversion-style
      language-translation
      ------
      generic-formula
      generic-simulation-formula
      model-definition
      ------
      units-of-measure-declaration
      remote-procedure-declaration
;      external-simulation-definition
      authorized-user
      ------
      image-definition
      frame-style-definition)))


;;; The function `class-is-authorized-p' is called by
;;; `compute-class-choices-for-menu' to decide whether a class should be
;;; absolutely excluded from any list of class choices.

(defun class-is-authorized-p (class-name)
  (cond ((eq class-name 'authorized-user)
         (user-authorized-in-current-workstation?))
        (t
         t)))



(define-presentation-type class-of-definition ()
  :menu-options (:title choose-a-class  :capitalize nil  :strip-hyphens nil)
  ;; This option is not passed down to our included submenus, unfort.
  :submenu-choices compute-class-inferior-choices-for-menu
  :choices '((include basic-definition-classes)
             (include extended-definition-classes)))



(defmenu (basic-workspace-classes  :type parameter-menu
                                   :submenu-choices compute-class-inferior-choices-for-menu)
    ()
  (compute-class-choices-for-menu '(kb-workspace)))

(define-presentation-type class-of-workspace ()
  :menu-options (:title choose-a-class  :capitalize nil :strip-hyphens nil)
  :submenu-choices compute-class-inferior-choices-for-menu
  :choices '((include basic-workspace-classes))
  :immediate-value compute-immediate-basic-class-choice-if-any-for-kb-workspace)

(defun-simple compute-immediate-basic-class-choice-if-any-for-kb-workspace ()
  (compute-immediate-basic-class-choice-if-any 'kb-workspace))





(defmenu (basic-rule-classes  :type parameter-menu
                              :submenu-choices compute-class-inferior-choices-for-menu)
    ()
  (compute-class-choices-for-menu '(rule)))

(define-presentation-type class-of-rule ()
  :menu-options (:title choose-a-class  :capitalize nil :strip-hyphens nil)
  :submenu-choices compute-class-inferior-choices-for-menu
  :choices '((include basic-rule-classes))
  :immediate-value compute-immediate-basic-class-choice-if-any-for-rule)

(defun-simple compute-immediate-basic-class-choice-if-any-for-rule ()
  (compute-immediate-basic-class-choice-if-any 'rule))




;; These commands need conditions.

(defun make-instance-interactively (class-name image-plane x y)
  (when (classp class-name)
    (loop as class in (class-inheritance-path (class-description class-name))
          when (class-choice-action class)
            return
            (funcall-symbol (class-choice-action class) class-name
                            image-plane x y))))

;; class-choice-action's are defined in facilities via def-class-choice-action


(defun object-creation-on-workspace-allowed-p (workspace)
  (and (g2-still-authorized-p)
       (frame-of-class-p workspace 'kb-workspace)
       #+pre-g2-v5-licensing (not (runtime-option-authorized-p))
       #+pre-g2-v5-licensing (not (embedded-option-authorized-p))
       (item-is-either-not-permanent-or-from-an-editable-module-p workspace)))



;; Further restrict new-rule, new-display, and new-button.

(defun restricted-object-creation-on-workspace-allowed-p (workspace)
  (and (object-creation-on-workspace-allowed-p workspace)
       #+pre-g2-v5-licensing
       (not (restricted-use-option-authorized-p)))) ; Added (jh, 6/27/91)


(defun create-instance-of-class-named (menu choice)
  (with-mouse-pointer-bindings (x-in-window y-in-window image-plane)
      (menu-mouse-pointer menu)
    (loop as class in (class-inheritance-path (class-description choice))
          when (class-choice-action class)
            return (funcall-symbol (class-choice-action class) choice
                                   image-plane x-in-window y-in-window))))




;;;; Workspace menu utilities


(defun user-workspace-p (workspace)
  (and (framep workspace)
       (not (frame-of-class-p workspace 'non-kb-workspace))))

;; Qustion: does (not kb-workspace) == non-kb-workspace?


;;; The function `transient-or-permanent-p' is a frequent condition on UI
;;; commands.  Objects which fail this test are typically those created by G2
;;; for its own use; for example, text-boxes and junction blocks in the
;;; inspector's class hierarchy display.  Sadly it is possible for such blocks
;;; to appear upon user-workspaces.  For example by transfering messages out of
;;; the logbook.  A small suite of commands is allowed on these: move transfer,
;;; clone, table and (???).

;;; Those commands are further restricted when objects of these types appear
;;; on edit workspaces, see block-of-edit-workspace-p below.

(defun transient-or-permanent-p (block)
  (or (transient-p block)
      (permanent-block-p block)))


;;; `Block-of-edit-workspace-p' is used to guard operations on things must be
;;; done to things on edit workspaces.  In particular inactive edit workspaces.
;;; These blocks are all (not (transient-or-permanent-p block)) so if a command
;;; already precludes these this guard will be redundent.

(defun block-of-edit-workspace-p (block)
  (and (not (transient-or-permanent-p block))
       (let ((workspace? (get-workspace-if-any block)))
         (and workspace?
              (frame-of-class-p workspace? 'edit-workspace)))))

;; It could be there are other classes like edit workspaces (dialogs?) that
;; should be included in this set.


(defun frame-may-be-enabled-or-disabled-p (frame &optional allow-warning-p)
  (and (if (workspace-p frame) (user-workspace-p frame) t)
       (transient-or-permanent-p frame)                    ; text-box.
       (or (not allow-warning-p)
           (item-is-either-not-permanent-or-from-an-editable-module-p frame))))



;;; `Frame-may-be-rotated-or-reflected-p' is true if frame may have the
;;; rotate-reflect command applied to it.  Currently this is true if frame is an
;;; entity and an item, but not a connection, button, meter, or dial.
;;;
;;; This is used by g2-set-reflection-and-rotation, which needs to determine by
;;; hand whether rotate/reflect should even be an allowed command, since that
;;; knowledge can only currently be gotten by having a mouse pointer, and it
;;; cannot readily synthesize one.

(defun frame-may-be-rotated-or-reflected-p (frame &optional allow-warning-p)
  (let ((class-inheritance-path (class-inheritance-path (class-description-slot frame))))
    (and (inheritance-path-memq 'entity class-inheritance-path)
         (inheritance-path-memq 'item class-inheritance-path)
         (not (or (inheritance-path-memq 'button class-inheritance-path)
                  (inheritance-path-memq 'meter class-inheritance-path)
                  (inheritance-path-memq 'dial class-inheritance-path)
                  (inheritance-path-memq 'connection class-inheritance-path)))
         (or (not allow-warning-p)
             (item-is-either-not-permanent-or-from-an-editable-module-p frame)))))

;; A version of this that worked for a class, rather than a frame, could easily
;; be derived.


;;;; OLE Stubs



;;; `when-ole-enabled' can be used to wrap a piece of code that should not even
;;; be reached without OLE drag and drop.  For example, you'd say:
;;;    (if (ole-clone-p) (when-ole-enabled (do-stuff)))
;;; not
;;;    (when-ole-enabled (if (ole-clone-p) (do-stuff)))
;;; because the intent is to signal an error if enable-ole is not present and
;;; we're hitting ole-only code.  Checking to see if the user has selected
;;; ole-clone is not ole-only code.  jv, 5/14/99

(defmacro when-ole-enabled (&body body)
  #+enable-ole
  `(progn
     ,@body)
  #-enable-ole
  (declare (ignore body))
  #-enable-ole
  `(progn
     #+development
     (cerror "Continue"
             "Should not be able to get here when enable-ole is turned off.  - jv")
     nil)
  )


;;; The simple function `wrap-ole-ghost-around-block' creates an ole-ghost to
;;; provide the visual representation of an object being dragged via OLE.

#-enable-ole
(defun-simple wrap-ole-ghost-around-block (block)
  (declare (ignore block)))

;;; The void function `set-ole-source-tcp-port-if-possible' is called on the OLE
;;; drag source side to let the remote OLE drag target side know the TCP port to
;;; use to emulate OLE communication.

(defun-void set-ole-source-tcp-port-if-possible ()
  nil)


;;; The function `enter-ole-transfer-dragging-context' is patterned after
;;; enter-transfer-dragging-context.  This function is the toplevel entry point
;;; for the "ole clone" item-restriction.

#-enable-ole
(defun enter-ole-transfer-dragging-context
    (block-or-blocks-to-drag ole-mode
      &optional
      x-offset-from-dragger
      y-offset-from-dragger
      specific-image-plane?
      mouse-up-exits-this-context?)
  (declare (ignore block-or-blocks-to-drag
                   ole-mode
                   x-offset-from-dragger
                   y-offset-from-dragger
                   specific-image-plane?
                   mouse-up-exits-this-context?)))

#-enable-ole
(defmacro ole-menu-item-selection-p (mouse-pointer)
  (declare (ignore mouse-pointer)))





;;;; Item menu


(defmenu (entity-lifting-menu :restriction-type item-menu) ()
  lift-item-to-top
  drop-item-to-bottom)


(defmenu (explanation-related-menu :restriction-type item-menu) ()
  dynamic-backward-chaining
  describe-chaining
  dynamic-generic-rule-display)



(defmenu (entity-menu :class-name-or-names-for-export entity
                      :restriction-type item-menu) (simple-item-spot)
  table
  go-to-subworkspace
  create-instance
  edit-text-box                                                    ; Rules.
  edit-procedure
  #+java-export-facilities
  edit-external-procedure

  ;; For G2GL/BPEL:
  set-temporary-breakpoint remove-temporary-breakpoint
  add-stub-for-local-handler

  edit-icon
  table-of-values
  transfer
  move
  name                                                            ; not for rules?
  clone
  change-min-size                                            ; Only for rules.
  rotate-reflect
  change-size
  restore-to-normal-size
  color
  delete
  (include entity-lifting-menu)
  enable
  disable
  describe
  table-of-hidden-attributes
  show-unsaved-attributes

  view-change-log

  (include explanation-related-menu)

  ;; Disassemble has been removed from the product for 3.0.  The code hasn't
  ;; been deleted yet in the unlikely case that we might change our minds.  -jra
  ;; 6/12/91
  ;;  disassemble

  describe-configuration
  create-subworkspace

  compile-g2gl-process
  clean-up-g2gl-compilation-postings-on-process
  execute-g2gl-process

  (include stripping-and-marking-menu)
  (include user-menu-choices))

;;; `iconic-entity-menu' is being introduced to shield obscure crashes that can
;;; occur when users get a hold of menus to iconic entities on the icon editor.
;;; This can occur when editing a slot in a table in the icon editor.

(defmenu (iconic-entity-menu
           :restriction-type item-menu
           :condition (with-mouse-pointer-bindings (frame)
                          mouse-pointer
                        (frame-of-class-p frame 'iconic-entity)))
    (simple-item-spot)
  table)

;; jh, 7/3/97.  The defmenu for ole-ghost-menu must be evaluated after the one
;; for iconic-entity-menu, until the implementation of defmenu changes.  See
;; comment underneath find-menu-for-spot in NEW-MENUS about how and why to avoid
;; the present ordering effects.

(defmenu (ole-ghost-menu :restriction-type item-menu
                         :condition (with-mouse-pointer-bindings (frame)
                                        mouse-pointer
                                      (frame-of-class-p frame 'ole-ghost)))
    (simple-item-spot)
  table
  delete)


;;; The function `frame-acts-like-arrow-button-p' is true for frames which have a
;;; UI behavior like logbook arrow-buttons.

(defun frame-acts-like-arrow-button-p (frame)
  (or (frame-of-class-p frame 'arrow-button)
      (frame-of-class-p frame 'g2gl-breakpoint-button)))


;;; The button is menu is a proper subset of the entity menu,
;;; except for changing `change-size' to `change-min-size'.

(defmenu (button-menu :class-name-or-names-for-export button
                      :restriction-type item-menu
                      :condition (with-mouse-pointer-bindings (frame)
                                     mouse-pointer
                                   (not (frame-acts-like-arrow-button-p frame))))
    (button-spot slider-spot type-in-box-spot)
  ;; Sliders are buttons, but slider-spots are not button-spots!
  ;; Type-in-boxes are buttons, but type-in-box-spots are not button-spots!
  table
  go-to-subworkspace
  edit-action-button                        ; Edits the action
  transfer
  move
  clone
  change-min-size
  restore-to-normal-size
  delete
  (include entity-lifting-menu)
  enable
  disable
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
  view-change-log
  describe-configuration
  create-subworkspace

  (include stripping-and-marking-menu)
  (include user-menu-choices))

;; Consider combining this with entity and/or offering more choice --
;; e.g. color.



;; Could have been a simple MEMBER ptype, with a title option.

(define-presentation-type rotation ()
  :menu-options (:title rotate-reflect)
  :choices '(90-clockwise 90-counterclockwise
             |180|
             left-right-reflection up-down-reflection))


;;; The function `handle-block-motion-command' pulls out some of the
;;; functionality common to the move, clone, create-instance, transfer and
;;; transfer-original UI commands.

(defun handle-block-motion-command (block choice-symbol
                                     original-x-in-window original-y-in-window
                                     image-plane-showing-block frame?)
  #+development
  (when (workspace-p block)
    (dwarn "Attempted to enter a block dragging context for ~s" block))
  (cond ((and (frame-of-class-p block 'system-table)
              (eq choice-symbol 'ole-clone))
         (when-ole-enabled
           (notify-user "~s is a system table item which cannot be cloned." block)))
        (t
         (unless (workspace-p block)                                    ; Protection.
           (let ((block-for-transit?
                   (case choice-symbol
                     (transfer-original
                      (when (and frame?
                                 (problem-item-in-limbo-p frame?))
                        ;; for entities created with make-frame, as
                        ;; opposed to make-entity, we have to call
                        ;; set-up-icon-for-entity; such blocks include
                        ;; auto-created junction block definitions (prior
                        ;; to 3.0 Beta rev. 12) and subobjects
                        ;; (originally in attribute tables, these should
                        ;; not get into limbo, but have done so due to
                        ;; some bug in certain cases).  (MHD 7/13/92)
                        (when (frame-of-class-p frame? 'entity)
                          (set-up-icon-for-entity frame?))
                        frame?))
                     ((move transfer) block)
                     (clone
                      (clone-frame block))
                     ((ole-clone ole-transfer)
                      (when-ole-enabled
                        (wrap-ole-ghost-around-block block)))
                     (clone-as-trend-chart
                      (clone-graph-as-trend-chart block))
                     (create-instance
                      (let ((class (name-of-defined-class block)))
                        (cond ((subclassp class 'non-action-button)
                               (make-button class))
                              ((subclassp class 'dial)
                               (make-dial class))
                              ((subclassp class 'meter)
                               (make-meter class))
                              ((subclassp class 'entity)
                               (make-entity class))
                              ((subclassp class 'message)
                               (make-message nil class))
                              ((subclassp class 'readout-table)
                               (make-readout-table class))
                              ((subclassp class 'graph)
                               (make-graph class))
                              ((subclassp class 'trend-chart)
                               (make-trend-chart class))
                              ((or (subclassp class 'chart)
                                   (subclassp class 'freeform-table))
                               (make-frame class))
                              (t nil)))))))
             (when block-for-transit?
               (handle-block-motion-command-1
                 block block-for-transit?
                 choice-symbol original-x-in-window original-y-in-window
                 image-plane-showing-block)))))))

(defun handle-block-motion-command-1
    (original-block block-for-transit? choice-symbol
                    original-x-in-window original-y-in-window
                    image-plane-showing-block)
  (when (memq choice-symbol '(ole-clone ole-transfer))
    (set-ole-source-tcp-port-if-possible))
  ;; after cloning an item other than a workspace manually,
  ;; set it to be neither permanent nor transient:
  (when (memq choice-symbol '(clone ole-clone))
    (set-neither-permanent-nor-transient-and-propagate block-for-transit? nil))
  ;; The offset of +2 (window) units is there so that the
  ;; old and new image don't xor each other out.
  (set-cursor-position
    original-x-in-window original-y-in-window)

  (let (x-in-workspace y-in-workspace)
    (with-image-plane-transform (image-plane-showing-block)
      (setf x-in-workspace (x-in-workspace original-x-in-window))
      (setf y-in-workspace (y-in-workspace original-y-in-window)))
    (let* ((clone-case-p (memq choice-symbol '(clone ole-clone)))
           (x-offset
             ;; center instance on object defn for create-instance case?
             (-w x-in-workspace
                 (+w (left-edge-of-block original-block)
                     (if clone-case-p 2 0))))
           (y-offset
             (-w y-in-workspace
                 (+w (top-edge-of-block original-block)
                     (if clone-case-p 2 0)))))
      (case choice-symbol
        (move
         (enter-move-dragging-context
           block-for-transit?
           x-offset y-offset
           image-plane-showing-block))
        ((ole-clone ole-transfer)
         (enter-ole-transfer-dragging-context
           block-for-transit?
           choice-symbol
           x-offset y-offset
           image-plane-showing-block))
        (otherwise
         (enter-transfer-dragging-context
           block-for-transit?
           x-offset y-offset
           image-plane-showing-block
           (mouse-down-p)
           clone-case-p))))))



;;;; Name Boxes and Label Boxes



(defmenu (name-box :restriction-type item-menu) (name-box-spot)
  edit-name-box

  move                                                            ; All motion but transfer.
  (include entity-lifting-menu)

  (command hide-name delete)
  ;; edit was here, but was repositioned above transfer/move to be consistent with
  ;;   table & object menus.  (MHD 5/29/91)
  color)

;; Note that editing of name boxes for non-kb-workspaces is generally allowed
;; -- in particular, it has documented functionality for
;; category-instance-menu-workspace instances, and it would seem useful for
;; Inspect workspace.  Message boards may also be renamed, or given a new
;; "first name", perhaps using a different language or terminology.  (MHD
;; 10/29/91)

;; Maybe the same menus as its superblock, except for the addition of "move
;; name(s)" and "suppress display of name" and "edit name" actions.  Right now,
;; this just treats a name box as an ordinary block.



(defmenu (label-box :restriction-type item-menu) (label-box-spot)
  move
  delete
;;  edit-label-box                                            ; Undefined ***
  )

;; Do we ever make label boxes?




;;;; Text Box menu


(defmenu (text-box :class-name-or-names-for-export text-box
                   :restriction-type item-menu) (text-box-spot text-inserter-spot)
  table
  edit-text-box
  transfer
  move
  ;; edit was here, but was repositioned above transfer/move to be consistent with
  ;;   table & object menus.  (MHD 5/29/91)
  clone
  change-min-size
  restore-to-normal-size
  align-text
  color
  font
  delete
  (include entity-lifting-menu)
  go-to-message-origin                                            ; For inform messages.
  go-to-referenced-item                                            ; For logbook messages. Better name?
  go-to-source-code                        ;For logbook messages -dkuznick, 1/28/99
  enable
  disable
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
  view-change-log
  dynamic-rule-invocation-display
  describe-configuration
  (include stripping-and-marking-menu)
  (include user-menu-choices))

;; Text-inserters, even though they are text-boxes, do not generate text-box-spots.





;;;; Table menu



;;; The defmenu `output-only-table-menu' covers the HELP workspace, the credits
;;; workspace, the little filename prompting table below the edit-box in
;;; KB-load, etc.

(defmenu (output-only-table-menu :restriction-type table-menu) (output-only-table-spot)
  transfer-table
  hide-table)


;; The menu on an attribute name or value in an attribute table
;; (and not an attribute display table)
;; Note: this menu is subject to maybe-click-to-edit (when on the value spot).

(defmenu (attribute-menu
           :restriction-type table-menu
           :condition
           (or (within-spot-of-type-p mouse-pointer 'attribute-table-spot)
               (within-spot-of-type-p mouse-pointer 'graph-table-spot)))
    (attribute-name-represented-by-table-spot
      attribute-value-represented-by-table-spot)
  subtable
  show-subtable-of-unsaved-attributes
  get-table-for-slot-component-group
  show-slot-component-subtable
  show-referred-slot-component-subtable
  revert-slot-component-value
  choose-table-for-reference

  delete-subtable
  delete-slot-component-group
  change-to-no
  change-to-yes
  choose-existing-class
  add-slot-component-group
  add-optional-subtable
  edit-icon-from-table                        ; Will be active only over ICON-DESCRIPTION-FOR-CLASS?.
  edit-attribute-value                        ; for compound slots in attribute
  change-to
  show-summary-of-text                        ;   tables, edit and show-summary-of-text
  show-attribute-as-text                ;   alternate with show-attribute-as-text
  show-attribute-as-value
  transfer-table
  show-attribute-display                ; Should not apply to attribute-tables of readout-table.
  disable
  enable
  describe-configuration
  describe
  subtable-of-hidden-attributes
  view-change-log-from-table                ; active only over frame-change-log slot

  flush-version-information-for-change-logging-from-table
                                        ; active only over
                                        ;   (kb-version-information-for-change-logging
                                        ;     saving-parameters)

  flush-change-log-from-table                ; active only over frame-change-log slot
  ;;;;Gensym-178-HQ-5673853-SUCI-Add menu-choice on table of item go-to-item
  go-to-item
  hide-attribute-table)





(defmenu (table-background-menu :restriction-type table-menu)
    (table-background-spot table-header-spot)
  transfer-table
  hide-table)

;; This includes table-header-spot, but that will only be needed when clicking
;; on the title bar of an attribute table which has been transfered to a
;; workspace.



;;; The defmenu `short-representation-table-menu' is the menu for the little
;;; boxed objects you see in the inspector window, boxes which represent real
;;; user objects, hence the go-to-original choice.

(defmenu (short-representation-table-menu :restriction-type table-menu)
    (table-header-spot
      attribute-name-represented-by-table-spot
      attribute-value-represented-by-table-spot
      :within short-representation-table-spot)
  table-for-short-representation
  transfer-short-representation
  go-to-original
  describe-table-item
  table-of-hidden-attributes-for-short-representation
  show-unsaved-attributes-for-short-representation
  view-change-log-from-table                ; active only over frame-change-log slot

  flush-version-information-for-change-logging-from-table
                                        ; active only over
                                        ;   (kb-version-information-for-change-logging
                                        ;     saving-parameters)

  flush-change-log-from-table                ; active only over frame-change-log slot
  hide-short-representation-table)

;; Hmm. Is this complete?


;;; A `multiframe-table' is the result of a tabular inspect command, such as
;;; "show a table of every item".  It is called "multiframe" because, unlike
;;; most tables, this one represents many items, one per row or one per column.

(def-concept multiframe-table)

(defmenu (multiframe-table-menu :restriction-type table-menu)
    (table-header-spot
      attribute-name-represented-by-table-spot
      attribute-value-represented-by-table-spot
      :within multiframe-table-spot)
  table-for-short-representation
  transfer-table
  go-to-original
  describe-table-item
  table-of-hidden-attributes-for-short-representation
  show-unsaved-attributes
  view-change-log-from-table                ; active only over frame-change-log slot

  flush-version-information-for-change-logging-from-table
                                        ; active only over
                                        ;   (kb-version-information-for-change-logging
                                        ;     saving-parameters)

  flush-change-log-from-table                ; active only over frame-change-log slot
  hide-short-representation-table)



;; I think that explanation tables get an entirely different menu.


(defun get-type-of-slot (frame slot-name defining-class?)
  (and (symbolp slot-name)                ; Tabular functions have integer slot-names!
       (type-of-slot-if-editable (class frame) slot-name nil defining-class?)))



(defun slot-value-is-frame-p (frame slot-name defining-class?)
  (and (null (get-type-of-slot frame slot-name defining-class?))
       (get-slot-feature-if-any
         (class frame) slot-name 'class-of-optional-subframe defining-class?)
       (get-subframe frame slot-name defining-class?)))


(defun boolean-valued-slot-p (frame slot-name defining-class?)
  (get-type-feature-if-boolean
    (slot-features
      (slot-description-from-class
        (class frame)
        slot-name defining-class?))))





;;; The function `allow-subtable-p' enables the add-optional-subtable command.
;;; It combines the two predicates from the menu in facilities.

(defun allow-subtable-p (table frame slot-name defining-class?)
  (let* ((subframe? (get-subframe frame slot-name defining-class?))
         (slot-description
           (get-slot-description-of-frame slot-name frame defining-class?))
         (slot-type-specification (slot-type-specification slot-description))
         (class-of-type-specification-is-for-undefined-class?
           (and (consp slot-type-specification)
                (eq (car-of-cons slot-type-specification) 'class)
                (not (classp (second slot-type-specification)))))
         (type-of-slot? (get-type-of-slot frame slot-name defining-class?))
         (category-symbol?
           (if type-of-slot?
               (category-symbol-given-slot-type type-of-slot?))))
    (and
      (null subframe?)
      (not class-of-type-specification-is-for-undefined-class?)
      (frame-system-operation-is-allowed-p 'change-set-of-inferiors frame)
      ;; (MHD/BAH 4/24/92)
      ;; New -- don't allow adding subtables for predefined user attributes.
      ;; See DEFINITIONS for further info. (MHD 12/28/92)
      (cond (type-of-slot?
             (and (not (memq category-symbol?
                             grammar-categories-getting-yes-no-feature))
                  (not (memq category-symbol?
                             grammar-categories-getting-choose-existing-class-feature))

                  (not (frame-of-class-p table 'explanation-table))

                  (transient-or-permanent-p frame)

                  (get-slot-feature-if-any
                    (class frame) slot-name 'class-of-optional-subframe
                    defining-class?)))
            (t
             (get-slot-feature-if-any
               (class frame) slot-name 'class-of-optional-subframe
               defining-class?)))
      (item-is-either-not-permanent-or-from-an-editable-module-p frame))))


;;; The function `editable-text-cell-p' combines all of the predicates from all
;;; of the EDIT items in the old table menu in facilities.  To be editable,
;;; text-cell must have at least a backpointer to a frame a slot name (or, in
;;; the case of a tabular function, index instead of a slot name).

;;; The bulk of the tests are in editable-slot-p, which does not depend in the
;;; particular table or text-cell.

(defun editable-text-cell-p (table text-cell)
  (multiple-value-bind (frame? slot-name-or-index defining-class?
                               slot-component-name? slot-component-indicator? virtual-attribute?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (declare (ignore slot-component-indicator?))
    (and frame?
         (symbolp slot-name-or-index)  ;; added 1/31/97 ddm
         (not (frame-of-class-p table 'explanation-table))  ; Needed?
         ;; If a text cell (for now, actually, only for compound slots) has
         ;; a text-summarized? property, it's not to be edited. (MHD 4/20/94)
         (not (getfq (text-cell-plist text-cell) 'text-summarized?))
         (not (eq slot-name-or-index 'class))
         (if virtual-attribute?
             (editable-virtual-attribute-p frame? slot-name-or-index defining-class? slot-component-name?)
             (editable-slot-p frame? slot-name-or-index defining-class? slot-component-name?)))))


;;; The function `editable-slot-p' returns true if we ought to allow the user
;;; to pop up an editor on the given slot.  The slot denotation here must be
;;; of an actual extant slot.

;;; This calls thru to type-of-slot-if-editable, which calls thru to
;;; type-slot-feature-assq-if-editable.  That last one has behavior that
;;; is dependent on the current authorization.

(defun editable-slot-p (frame slot-name defining-class? slot-component-name?)
  (let* ((subframe?
           (get-subframe frame slot-name defining-class?))
         (class (class frame))
         (attribute-features
           (get-attribute-features
             class slot-name defining-class? slot-component-name?))
         (type-of-slot?
           (type-slot-feature-assq-if-editable attribute-features))
         (category-symbol?
           (if type-of-slot?
               (category-symbol-given-slot-type type-of-slot?))))
    (and type-of-slot?
         (null subframe?)
         (not (memq category-symbol? grammar-categories-getting-yes-no-feature))

         (transient-or-permanent-p frame)
         (if-slot-is-compound-is-it-editable?
           slot-name defining-class? slot-component-name?)

         (not (and (frame-of-class-p frame 'class-definition)
                   (eq slot-name 'icon-description-for-class?)
                   (not (class-definition-defines-user-editable-icon-class-p frame))))

         (or (memq category-symbol? grammar-categories-getting-choose-existing-class-feature)
             (not-a-system-slot-name-p slot-name)
             (feature-assq 'class-of-optional-subframe attribute-features)
             (might-be-writable-slot-p frame slot-name type-of-slot?))

         (or (and (eq class 'saving-parameters)
                  (or (eq slot-name 'unsavable-change-protection)
                      (and (eq frame saving-parameters)
                           (eq slot-name 'default-unsavable-change-protection))))
             (item-is-either-not-permanent-or-from-an-editable-module-p frame)))))

;; Not-a-system-slot-name-p doesn't take a class-qualifier? argument -- it
;; should, in principle, but will work for system-defined slots for now, which
;; is all it needs to do.! (MHD 2/17/94)

;; I didn't see any code worrying about slot-name being an index, despite the
;; note (by fmw). Should there be?! (MHD 4/20/94)

(defun editable-virtual-attribute-p (frame name &optional defining-class? slot-component-name?)
  (let ((attribute? (virtual-attribute name)))
    (and (null defining-class?)
         (null slot-component-name?)
         attribute?
         (transient-or-permanent-p frame)
         (virtual-attribute-setter? attribute?)
         (not (memq name '(following-item-in-workspace-layering)))
         (item-is-either-not-permanent-or-from-an-editable-module-p frame))))


;;; `might-be-writable-slot-p':  some generally useful miscellaneous tests.
;;; We need to be able to call this from attr-export, and it was easily
;;; abstracted out from editable-slot-p.  jtidwell 8/9/96

(defun might-be-writable-slot-p (frame slot-name type-of-slot?)
  (and
    ;; The following is only needed here and not for the other edit clauses
    ;;   because the others are known not to pertain to text slots. (MHD)
    (or (not (text-slot-type-p type-of-slot?))
        (frame-of-class-p frame 'message)
        (not (text-slots-in-frame-have-been-stripped-p frame)))

    ;; The following is to maintain the constraints that (1) if a frame
    ;; is proprietary, do not edit its proprietary-package slot, and
    ;; (2) if a frame is proprietary, do not edit its user-restrictions
    ;; slot.
    (or (not (memq slot-name '(proprietary-package user-restrictions)))
        (null frame)        ; Can frame ever be NIL? -fmw, 12/7/93
        (not (proprietary-p frame)))

    ;; The following is to maintain the constraint that the
    ;; module-this-is-part-of? slot of a kb workspace cannot be edited
    ;; unless the it's a top-level workspace.
    (or (not (eq slot-name 'module-this-is-part-of?))
        (not (frame-of-class-p frame 'kb-workspace))
        (null (parent-of-subworkspace? frame)))))




;;; The function `editable-text-box-p' is the analagous to editable-text-cell-p.

(defun editable-text-box-p (text-box)
  (and (or (transient-or-permanent-p text-box)
           (frame-of-class-p text-box 'inspect-history)
           (frame-of-class-p text-box 'inspect-command))
       (type-of-slot-if-editable (class text-box) 'box-translation-and-text)
       ;; no editing stripped texts, but make exception of messages:
       (or (frame-of-class-p text-box 'message)
           (and (not (text-slots-in-frame-have-been-stripped-p text-box))
                (item-is-either-not-permanent-or-from-an-editable-module-p text-box)))))






;;;; Readout table menu


(defmenu (readout-table-menu
           :class-name-or-names-for-export readout-table
           :restriction-type table-menu
           :condition (within-spot-of-type-p mouse-pointer 'readout-table-spot))
    (attribute-name-represented-by-table-spot
      attribute-value-represented-by-table-spot)
  table
  edit-expression-of-readout-table
  transfer
  move
  clone
  enable                                ; The ordering is different, but that's the case in 3.0.
  disable
  delete
  (include entity-lifting-menu)
  describe-configuration
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
  (include stripping-and-marking-menu)
  (include user-menu-choices))





;;;; Attribute display menu



;;; The menu `attribute-display-menu' includes all of the commands from the attribute
;;; menu, as well as other commands just for manipulating the attribute display
;;; itself.
;; Note: this menu is subject to maybe-click-to-edit.

(defmenu (attribute-display-menu :restriction-type table-menu)
    (attribute-name-represented-by-table-spot
      attribute-value-represented-by-table-spot
      table-background-spot                                    ; The "NO ATTRIBUTE TO DISPLAY" things generate this.
      :within attribute-display-spot)
  subtable
  delete-subtable
  change-to-no
  change-to-yes
  edit-attribute-display                                    ; Was edit-attribute-value
  change-to
  add-optional-subtable
  move-attribute-display
  transfer-attribute-display                                    ; Is this ever offered?
  show-attribute-as-value
  show-attribute-as-text

;; ?
;;  lift-to-top
;;  drop-to-bottom

  add-another-attribute
  delete-attribute
  add-name-of-attribute                                            ; Mutually exclusive pair.
  delete-name-of-attribute
  hide-attribute-display

  enable
  disable
  describe-configuration
  describe)



;; Needs to strip hyphens from the menu title.
;; Need to suppress language translation. (MHD 6/18/92)


(define-presentation-type attributes-missing-from-table (table frame)
  :menu-options (:title choose-another-attribute-to-display :strip-hyphens nil)
  :choices (make-menu-choice-list-for-missing-attribute-display-attributes
             table frame t)                                    ; function now defined in TABLES
  ;; Test that the slot still exists.
  ;; Unfortunately, tester functions don't get the ptype arguments!
;  :tester ((slot-designation frame)
;           (slot-exists-in-frame-p slot-designation frame))
  )


;; Until I allow menu title options to differ from menu item options..

(def-menu-string choose-another-attribute-to-display "choose another attribute to display")




;;;; Freeform Table menu



;; Hmm. We aren't using the table cell stored in the new-table-cell-spot!

(defmenu (freeform-table :class-name-or-names-for-export freeform-table
                         :restriction-type item-menu)
    (new-table-cell-spot new-table-background-spot)
  table
  edit-cell-expression
  edit-cell-format
  (submenu other-edits)

  transfer
  move
  clone

  name
  delete
  (include entity-lifting-menu)
  enable
  disable
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
  describe-configuration
  (include stripping-and-marking-menu)
  (include user-menu-choices))


(defmenu (other-edits
           :condition (row-and-column-index-available-p mouse-pointer)
           :restriction-type item-menu)
    ()
  add-row
  add-column
  delete-row
  delete-column)



;;;; Connection menu.



(defmenu (connection :class-name-or-names-for-export connection
                     :restriction-type item-menu) (connection-spot)
  table
  color-connection
  delete-connection
  ;; Before adding the following, decide if it's really useful and revise
  ;; delete-workspace confirmation message generator.
  ;;  go-to-subworkspace
  enable
  disable
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
;  describe-configuration                                    ; Why was this left out?
  (include stripping-and-marking-menu)
  (include user-menu-choices))




;;;; Meter and dial menu



(defmenu (meter-and-dial-menu :class-name-or-names-for-export (dial meter)
                              :restriction-type item-menu) (meter-or-dial-spot)
  table
  transfer
  move
  clone
  delete
  (include entity-lifting-menu)
  enable
  disable
  describe
  table-of-hidden-attributes
  describe-configuration
  show-unsaved-attributes
  (include stripping-and-marking-menu)
  (include user-menu-choices))



;;;; Chart menu



(defmenu (chart :class-name-or-names-for-export chart
                :restriction-type item-menu) (chart-spot)
  table
  transfer
  move
  clone
  change-size
  restore-to-normal-size
  name
  ; LATER! change-size
  delete
  (include entity-lifting-menu)
  enable
  disable
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
  describe-configuration
  (include stripping-and-marking-menu)
  (include user-menu-choices))



;;;; Graph Menu



(defmenu (graph-menu :class-name-or-names-for-export graph
                     :restriction-type item-menu) (graph-table-spot)
  table
  go-to-subworkspace
  create-instance
  edit-procedure
  edit-icon
  table-of-values
  transfer
  move
  name
  clone
  clone-as-trend-chart
  change-size
  restore-to-normal-size
  delete
  (include entity-lifting-menu)
  enable
  disable
  describe
  table-of-hidden-attributes
  show-unsaved-attributes
  view-change-log

  (include explanation-related-menu)

  describe-configuration
  create-subworkspace

  (include stripping-and-marking-menu)
  (include user-menu-choices))



;;;; Callback Procedures



;;; A callback procedure is a user-supplied KB-level procedure which is started
;;; in response to various events.

(def-concept callback-procedure)


;;; The function `argument-list-description-matches-template-p' returns T if
;;; the procedure argument list description matches the given template.  We
;;; match if the arglist is no longer than the template, and argument types
;;; agree in the common section.

(defun argument-list-description-matches-template-p (argument-list-description template)
  (and (=f (var-count argument-list-description) ; Using <=f here gets &rest ignore simulation.
           (length template))
       (null (argument-list-mismatch argument-list-description template))))

(defun argument-list-mismatch (argument-list-description template &optional permit-supertype-p)
  (loop for expected-type in template
        for index from 0
        as actual-name = (var-name-from-index argument-list-description index)
        as actual-type = (var-type-from-index argument-list-description index)
        as ok = (or (equal expected-type actual-type)
                    (if permit-supertype-p
                        (type-specification-subtype-p expected-type actual-type)))
        if (not ok)
          return (values actual-name actual-type expected-type)))


;;; The function `get-callback-procedure' returns two values, the procedure
;;; instance and the number of required arguments to the procedure, if a valid
;;; procedure is found. Arglist and runnable checking is optional.

(defun get-callback-procedure (procedure-or-procedure-name description
                                                           &optional
                                                           arglist-template?
                                                           must-be-runnable
                                                           signal-stack-errors
                                                           permit-supertype-p)
  (let ((procedure? (if (symbolp procedure-or-procedure-name)
                        (get-instance-with-name-if-any 'procedure procedure-or-procedure-name)
                        procedure-or-procedure-name))
        expected-type actual-type actual-name)
    (macrolet ((complain (fmt . args)
                 `(cond (signal-stack-errors
                         (stack-error cached-top-of-stack ,fmt ,@args))
                        (t
                         (warning-message* 1 ,fmt ,@args)
                         nil))))
      (cond
        ((null procedure?)
         (complain "The ~A procedure ~A does not exist."
                   description procedure-or-procedure-name))

        ((or (frame-of-class-p procedure? 'method)
             (frame-of-class-p procedure? 'method-declaration))
         (complain "The ~A procedure ~NF must be an ordinary procedure, not a ~(~A~)."
                   description procedure? (class procedure?)))

        ((not (frame-ok-p procedure?))
         (complain "The ~A procedure ~NF is not OK." description procedure?))

        ((and must-be-runnable (not (runnable-p procedure?)))
         (when (or system-is-running
                   (runs-while-inactive-p procedure?))
           (complain "The ~A procedure ~NF is either inactive or not runnable."
                     description procedure?)))

        ((null arglist-template?)        ; No type-checking requested.
         (values procedure? (var-count (argument-list-description procedure?))))

        ((/=f (var-count (argument-list-description procedure?))
              (length arglist-template?))
         (complain "The ~A procedure ~NF expects to be called with ~S arguments, but is declared to take ~S."
                   description procedure?
                   (length arglist-template?)
                   (var-count (argument-list-description procedure?))))

        ((multiple-value-setq (actual-name actual-type expected-type)
           (argument-list-mismatch (argument-list-description procedure?)
                                   arglist-template? permit-supertype-p))
         (complain "Argument ~S of the ~A procedure ~NF was expected to be declared type ~NT, not ~NT."
                   actual-name description procedure? expected-type actual-type))

        (t
         (values procedure? (var-count (argument-list-description procedure?))))))))

;; changed return value from length to var-count since
;; argument-lists-descriptions are now managed-arrays. (pbk 2/7/96)


;;; The function `procedure-runnable-p' returns T if procedure is currently
;;; runnable. If item supplied, the procedure must be allowed to refer to item.

(defun procedure-runnable-p (procedure &optional item?)
  (and (runnable-p procedure)
       (or system-is-running
           (runs-while-inactive-p procedure))
       (or (null item?)
           (let ((current-computation-flags current-computation-flags))
             (setf (role-serve-inactive-objects?)
                   (may-refer-to-inactive-items-p procedure))
             (serve-item-p item?)))))


;;; The variable `kb-procedure-completion-form?' may be bound to supply a
;;; completion-form to apply/call-kb-procedure.

(defvar kb-procedure-completion-form? nil)


;;; The function `apply-kb-procedure' starts KB procedure on given args, a
;;; gensym-list of evaluation-values, all of which are reclaimed or owned by
;;; this function. Returns the invocation object iff procedure is successfully
;;; started.

(defun apply-kb-procedure (procedure args)
  (let ((nargs (length args))
        (arg-vector? nil))
    (when (>f nargs 0)
      (setq arg-vector? (allocate-managed-simple-vector nargs))
      (loop for arg in args
            for i from 0
            do (setf (svref arg-vector? i) (get-item-if-item-reference arg))))
    (prog1
        (cond ((check-procedure-arglist-and-maybe-notify
                 ;; Probably ought to be a stack error,
                 ;; but we have no stack here!
                 procedure arg-vector? notify-user)
               (loop for arg in args doing
                 (reclaim-if-evaluation-value arg))
               nil)
              (t
               ;; `start-procedure-invocation-in-place' checks OK-ness,
               ;; runnability, and argument count
               (with-three-thousand-variables-bound
                   (start-procedure-invocation-in-place
                     procedure                                ; procedure
                     nil                                ; priority?
                     nil                                ; wait?
                     arg-vector?                        ; Local stack
                     (1-f nargs)                        ; Top of arguments on stack
                     nargs                              ; argument-count
                     nil                                ; simulator-procedure?
                     kb-procedure-completion-form?      ; completion-form?
                     nil                                ; top-of-stack?
                     nil                                ; validated-args-p
                     nil))))                                ; prepare-p
      (when arg-vector?
        (reclaim-managed-simple-vector arg-vector?))
    (reclaim-gensym-list args))))

;; Of course, this is actually start, not call.
;; moved here from OS-ERROR (previously from VIEWS) -- Chun Tian (binghe), Sep 1, 2016.
(defmacro call-kb-procedure (procedure &rest args)
  `(apply-kb-procedure ,procedure (gensym-list ,@args)))

;;;; UI Callbacks


;;; A `ui-callback' is KB-level procedure which is started in response to
;;; various events in the user interface. Each callback procedure must be
;;; registered via `g2-ui-register-callback'. For now, the only events allowed
;;; are SELECTION-CHANGED and WORKSPACE-HIDDEN.

(def-concept ui-callback)

(defparameter known-ui-events '(selection-changed workspace-hidden area-selected scrollbar-changed))


(def-hash-table ui-callback-table
  :hash-function-or-macro identity-macro ; keys are already fixnums.
  :entry-reclaimer reclaim-ui-callback)


;;; The kb-specific-variable `ui-callbacks' contains a hash table mapping a
;;; integer handles to ui-callback structures.

;;; `WARNING!!' Since ui-callback structures contain item-references, in order
;;; to protect the procedure, item, and user-data slots, this hash table runs
;;; afoul of a questionable design feature of system variables, namely, that
;;; kb-specific system variable reclaimers are run in module-load order. So,
;;; more basic system variables get reclaimed before later ones.

;;; One such more basic system variable is the `uuid-block-hash-table' which
;;; maintains a table of all uuid-blocks, which are the guts of
;;; item-references. During a KB-clear, that system variable is reclaimed before
;;; ours, and it reclaims ALL item-references, regardless of their reference
;;; counts. So, during KB-clear, item references in the `ui-callbacks' table are
;;; reclaimed before our reclaimer is called.

;;; To avoid this problem, we leave off the reclaimer for `ui-callbacks' and
;;; hook into clear-kb via `run-state-change-hook', in order to reclaim the hash
;;; table before system variables are reclaimed (inside `release-kb').

;;; -fmw, 8/15/03

(def-kb-specific-variable ui-callbacks COMMANDS2 (:funcall make-ui-callback-table))

(def-kb-specific-variable last-ui-callback-handle COMMANDS2 0)

(def-substitution-macro next-ui-callback-handle ()
  (unless (=f last-ui-callback-handle most-positive-fixnum)
    (incff last-ui-callback-handle)))

(def-substitution-macro ui-callbacks-exist-p (event item?)
  (>f last-ui-callback-handle 0))       ; Really quick, but REALLY dumb test.

(def-structure (ui-callback
                 (:constructor make-ui-callback
                               (ui-callback-handle
                                 ui-callback-event
                                 ui-callback-procedure
                                 ui-callback-item
                                 ui-callback-user-data))
                 #+development (:print-function print-ui-callback)
                 (:reclaimer reclaim-ui-callback-1))
  ui-callback-handle                ; Positive fixnum, or negative to disable this callback.
  ui-callback-event                ; Symbol
  ui-callback-procedure                ; Item ref
  ui-callback-item                ; Item ref or value
  ui-callback-user-data)        ; Item ref or value

#+development
(defun print-ui-callback (callback stream depth)
  (declare (ignore depth))
  (printing-random-object (callback stream)
    (format stream "UI-CALLBACK ~a [~d]"
            (ui-callback-event callback)
            (ui-callback-handle callback))))

(defun reclaim-ui-callback (callback)
  (macrolet ((reclaim (slot)
               `(progn
                  (reclaim-evaluation-value (,slot callback))
                  (setf (,slot callback) nil))))
    (reclaim ui-callback-procedure)
    (reclaim ui-callback-item)
    (reclaim ui-callback-user-data))
  (reclaim-ui-callback-1 callback))

;; Called only during clear-kb.
(defun reclaim-all-ui-callbacks ()
  (when ui-callbacks
    (reclaim-ui-callback-table ui-callbacks)
    (setq ui-callbacks nil)))

(def-substitution-macro delete-ui-callback (callback)
  ;; TODO: remove from other places, depending on type.
  (delete-ui-callback-table (absf (ui-callback-handle callback)) ui-callbacks))

(def-substitution-macro ui-callback-enabled-p (callback)
  (>f (ui-callback-handle callback) 0))

(def-substitution-macro enable-ui-callback (callback)
  (setf (ui-callback-handle callback) (absf (ui-callback-handle callback))))

(def-substitution-macro disable-ui-callback (callback)
  (setf (ui-callback-handle callback) (-f (absf (ui-callback-handle callback)))))

(def-substitution-macro get-ui-callback (handle)
  (get-ui-callback-table handle ui-callbacks))

(defun get-ui-callback-or-stack-error (handle)
  (or (get-ui-callback handle)
      (ui-stack-error "There is no UI callback corresponding to handle ~D." handle)))

;;; The function `invoke-ui-callbacks-1' starts all of the UI callbacks for the
;;; the given event on the given item. Callbacks which have become invalid are
;;; not called and are reclaimed.

(defun invoke-ui-callbacks-1 (event item particulars)
  (let ((invalid-callbacks ()))
    (loop for callback being each hash-value of ui-callbacks
          as handle = (absf (ui-callback-handle callback))
          as procedure? = (get-item-if-item-reference
                            (ui-callback-procedure callback))
          as user-data? = (get-item-if-item-reference
                            (ui-callback-user-data callback))
          as item? = (get-item-if-item-reference
                       (ui-callback-item callback))
          doing
      (cond ((null procedure?)
             (gensym-push callback invalid-callbacks))
            ((null item?)
             (gensym-push callback invalid-callbacks))
            ((and (ui-callback-enabled-p callback)
                  (eq event (ui-callback-event callback))
                  (eq item item?)
                  (procedure-runnable-p procedure? item?))
             ;; If the procedure is well-formed, then we can distinguish the two
             ;; styles based just on the formal argument count. If the procedure
             ;; is not well formed, then we'll stack-error in either case, and
             ;; it doesn't matter too much which one (except that the error
             ;; message might be more or less confusing).
             (case (var-count (argument-list-description procedure?))
               (4 (call-kb-procedure procedure? event
                                     (copy-if-evaluation-value user-data?)
                                     handle item?))
               (t (call-kb-procedure procedure? event item?
                                     (copy-if-evaluation-value particulars)
                                     (copy-if-evaluation-value user-data?)
                                     handle))))))
    ;; Delete any invalid callbacks we encountered. A callback becomes invalid
    ;; if either its procedure or its item is deleted.
    (loop for callback in invalid-callbacks doing
      (delete-ui-callback callback))
    (reclaim-gensym-list invalid-callbacks)))

(defun-substitution-macro invoke-ui-callbacks (event item particulars)
  (when (ui-callbacks-exist-p event item) ; Quick test.
    (invoke-ui-callbacks-1 event item particulars)))


;;; The function `valid-ui-callback-procedure-or-stack-error' performs the
;;; registration-time type checking on a UI callback procedure. Two different
;;; styles of callback are allowed, old and new, where only the new style gets
;;; the "particulars" of the event.

(defun valid-ui-callback-procedure-or-stack-error (event procedure)
  (let ((signature-1 '(symbol item-or-datum integer (class item))) ; Old style
        (signature-2 (case event        ; New style
                       (workspace-hidden
                        '(symbol (class kb-workspace) (class g2-window) item-or-datum integer))
		       (scrollbar-changed
			'(symbol (class kb-workspace) (class g2-window) item-or-datum integer))
                       (t
                        '(symbol (class item) item-or-datum item-or-datum integer)))))
    (cond
      ((or (frame-of-class-p procedure 'method)
           (frame-of-class-p procedure 'method-declaration))
       (ui-stack-error "The callback procedure ~NF must be an ordinary procedure, not a ~(~A~)."
                       procedure (class procedure)))

      ((not (frame-ok-p procedure))
       ;; If it's not OK, we don't signal a stack error since it may become OK
       ;; later. However, we can't do type-checking in this case, so return now.
       (warning-message* 3 "The callback procedure ~NF is not OK." procedure)
       procedure)

      ((check-procedure-arglist-and-maybe-notify
         procedure
         (case (var-count (argument-list-description procedure))
           (4 signature-1)
           (t signature-2))
         warning-message
         3)
       procedure)
      (t
       procedure))))

;;; The gensym system-procedure `get-current-time-zone-lisp-side' return string with
;;; current time zone information.

(defun-for-system-procedure get-current-time-zone-lisp-side ()
  (get-current-time-zone))
  
;;; The function `g2-ui-register-callback' records a KB-level procedure to be
;;; started whenever the given UI-related "event" happens to "item". Each type
;;; of event may have it's own set of interesting information that goes along
;;; with it, which is passed to the callback as a structure.

(defun-for-system-procedure g2-ui-register-callback
    (event procedure user-data item options)
  (reclaim-if-evaluation-value options) ; Options are currently ignored.
  (let (handle?)
    (cond ((not (memq event known-ui-events))
           (ui-stack-error "~A is not a known UI event." event))
          ((null (setq handle? (next-ui-callback-handle)))
           (ui-stack-error "No more handles available for UI callbacks."))
          ((valid-ui-callback-procedure-or-stack-error event procedure)
           (macrolet ((copy (value)
                        `(get-reference-to-item-if-item
                           (copy-if-evaluation-value ,value))))
             (let ((callback
                     (make-ui-callback handle?
                                       (copy event) (copy procedure) (copy item)
                                       (copy user-data))))
               (set-ui-callback-table-hash-value handle? ui-callbacks callback)
               handle?))))))

(defun-for-system-procedure g2-ui-unregister-callback (handle)
  (delete-ui-callback (get-ui-callback-or-stack-error handle)))

(defun-for-system-procedure g2-ui-enable-callback (handle)
  (enable-ui-callback (get-ui-callback-or-stack-error handle)))

(defun-for-system-procedure g2-ui-disable-callback (handle)
  (disable-ui-callback (get-ui-callback-or-stack-error handle)))

(defun-for-system-procedure g2-ui-get-callback (handle)
  (export-ui-callback (get-ui-callback-or-stack-error handle)))

(defun-for-system-procedure g2-ui-get-callbacks (event)
  (allocate-evaluation-sequence
    (loop for callback being each hash-value of ui-callbacks
          when (or (memq event '(* any all))
                   (eq event (ui-callback-event callback)))
            collect (absf (ui-callback-handle callback))
              using eval-cons)))

(defun export-ui-callback (callback)
  (let ((handle (absf (ui-callback-handle callback)))
        (enabled (make-evaluation-value-from-lisp-value
                   (ui-callback-enabled-p callback)))
        (event? (make-evaluation-value-from-lisp-value
                  (ui-callback-event callback)))
        (procedure? (get-item-if-item-reference
                      (ui-callback-procedure callback)))
        (user-data? (if (evaluation-item-reference-p (ui-callback-user-data callback))
                        (get-item-if-item-reference (ui-callback-user-data callback))
                        (copy-if-evaluation-value (ui-callback-user-data callback))))
        (item? (get-item-if-item-reference
                 (ui-callback-item callback))))
    (allocate-evaluation-structure
      (nconc (eval-list 'handle handle)
             (eval-list 'enabled enabled)
             (if event?     (eval-list 'event     event?))
             (if procedure? (eval-list 'procedure procedure?))
             (if user-data? (eval-list 'user-data user-data?))
             (if item?      (eval-list 'item      item?))))))



;;;; User-defined mouse trackers



;;; The `user-mouse-tracking' facility lets users define GPL procedure which is
;;; started whenever the mouse moves over items of a specified class.  This
;;; procedure is bound by an item configuration clause of the form:

;;;  pressing <modifiers>+mouse-button on any <class-1> starts
;;;     <procedure> for all mouse events
;;;            [every <interval> seconds]
;;;            [over any <class-2>]

;;; The procedure argument list looks like:
;;;      event-name:    symbol
;;;      window:        class item
;;;      original-item: item-or-value
;;;      item:          item-or-value
;;;      x-in-workspace:integer
;;;      timestamp:     integer
;;;      shiftkeys:     integer

;;; The event-name is one of START-TRACKING, ENTER, MOTION, LEAVE,
;;; STOP-TRACKING, or ABORT-TRACKING.

;;; This context is supposed to be entirely spring-loaded.  Hence any
;;; indication that all the mouse buttons are up exits the context, calling the
;;; user procedure as usual.


(defparameter mouse-tracking-procedure-arglist-template
  '(symbol                                                    ; Event
    (class g2-window)                                            ; Window
    item-or-datum                                            ; Original item
    item-or-datum                                            ; Current item
    integer integer                                            ; x,y
    integer                                                    ; event time in ms
    integer))                                                    ; shift-keys

(define-workstation-context user-mouse-tracking ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :state-variables (procedure-name
                     original-item
                     original-item-frame-serial-number
                     last-item
                     last-item-frame-serial-number
                     last-x-in-window                            ; Used to weed out duplicate motion events.
                     last-y-in-window
                     last-x-in-workspace
                     last-y-in-workspace
                     last-event
                     classes
                     motion-events?
                     notify-interval)                            ; In milliseconds, to throttle motion events.
  :conc-name t
  :define-enter-context-function t
  :keymap ((<mouse-motion> call-user-mouse-tracking-procedure)
           (<mouse-up> call-user-mouse-tracking-procedure)
           ;; Can get a mouse-down only if there were nested contexts.
           (<mouse-down> call-user-mouse-tracking-procedure)))



;;; The event `user-mouse-tracking' is generated from mouse tracking
;;; item-configuration clauses.  It is the only event handler currently which
;;; takes arguments from the event-interpretation.  The special variable
;;; `event-handler-args' is bound by run-event-handler.

(define-event-handler user-mouse-tracking
    (item timestamp key-code
          x-in-window y-in-window
          &optional
          (x-in-workspace? x-in-workspace)
          (y-in-workspace? y-in-workspace))
  (when event-handler-args                                    ; Kinda kludgey.
    (gensym-dstruct-bind ((procedure-name classes motion-events?) event-handler-args)
      (start-user-mouse-tracking procedure-name item
                                 timestamp key-code
                                 x-in-window y-in-window
                                 x-in-workspace? y-in-workspace?
                                 classes motion-events?))))


(def-structure-method clean-up-workstation-context (user-mouse-tracking-state)
  (with-workstation-context-return-values (status mouse-pointer)
    (when (eq :abort status)
      (abort-user-mouse-tracking mouse-pointer)))
  (reclaim-frame-serial-number
    (user-mouse-tracking-state-original-item-frame-serial-number user-mouse-tracking-state))
  (reclaim-frame-serial-number
    (user-mouse-tracking-state-last-item-frame-serial-number user-mouse-tracking-state))
  (funcall-superior-method user-mouse-tracking-state))


(defun start-user-mouse-tracking
    (procedure-name item timestamp key-code
                    x-in-window y-in-window
                    x-in-workspace? y-in-workspace? class-spec motion-events?)
  (let ((last-event 'DOWN)
        (x (or x-in-workspace? 0))
        (y (-w (or y-in-workspace? 0)))
        (shift-keys (canonical-key-modifier-bits key-code))
        (g2-window (g2-window-for-this-workstation? current-workstation)))

    (multiple-value-bind (procedure? nargs)
        (get-mouse-tracking-procedure procedure-name)
      (when (and procedure?
                 (procedure-runnable-p procedure? item))
        (invoke-mouse-tracking-procedure
          procedure? nargs 'START-TRACKING g2-window item item x y
          timestamp shift-keys)

        (when (frame-matches-restriction-class-spec item class-spec item)
          (invoke-mouse-tracking-procedure
            procedure? nargs 'ENTER g2-window item item x y timestamp shift-keys)
          (setq last-event 'ENTER))

        (enter-user-mouse-tracking-context
          :procedure-name procedure-name
          :original-item item
          :original-item-frame-serial-number (copy-frame-serial-number (frame-serial-number item))
          :last-item item
          :last-item-frame-serial-number (copy-frame-serial-number (frame-serial-number item))
          :last-x-in-window x-in-window
          :last-y-in-window y-in-window
          :last-x-in-workspace x
          :last-y-in-workspace y
          :last-event last-event
          :motion-events? motion-events?
          :classes (copy-tree-using-slot-value-conses class-spec))))))


;;; The event-handler `call-user-mouse-tracking-procedure' is called for
;;; both mouse-motion and mouse-up events.

(define-event-handler call-user-mouse-tracking-procedure (mouse-pointer)
  (call-user-mouse-tracking-procedure-1 mouse-pointer nil))


(defun abort-user-mouse-tracking (mouse-pointer)
  (call-user-mouse-tracking-procedure-1 mouse-pointer t))

;; Aborts tracking only if it is the current workstation context.
(defun abort-user-mouse-tracking-on-current-workstation ()
  (when (eq type-of-current-workstation-context 'user-mouse-tracking)
    (abort-current-workstation-context 'user-mouse-tracking)))


(defun call-user-mouse-tracking-procedure-1 (mouse-pointer abort?)
  (with-mouse-pointer-bindings
      ((state workstation-context-specifics)
       x-in-window y-in-window
       &optional
       ;; This gets the item even when over the item's attribute display
       ;; Would like to get the item of the desired class, in case we have to
       ;; burrow though items in high layers to get one. (At least, burrow though
       ;; disabled items?  It's unclear what the desired behavior is.)
       (item? item)
       ;; In Milliseconds since start of tracking.
       (timestamp timestamp)
       (x-in-workspace? x-in-workspace)
       (y-in-workspace? y-in-workspace))
      mouse-pointer
    (let* ((procedure-name
             (user-mouse-tracking-state-procedure-name state))
           (original-item
             (user-mouse-tracking-state-original-item state))
           (original-item-serial
             (copy-frame-serial-number (user-mouse-tracking-state-original-item-frame-serial-number state)))
           (last-item
             (user-mouse-tracking-state-last-item state))
           (last-item-serial
             (copy-frame-serial-number (user-mouse-tracking-state-last-item-frame-serial-number state)))
           (motion-events?
             (user-mouse-tracking-state-motion-events? state))
           (g2-window?                        ; This can be NIL during logout. -fmw, 6/27/02
             (g2-window-for-this-workstation? current-workstation))
           (gensym-window
             (window-for-workstation current-workstation))
           (last-workspace?
             (if (frame-has-not-been-reprocessed-p last-item last-item-serial)
                 (get-workspace-if-any last-item)))
           (last-image-plane?
             (if last-workspace?
                 (image-plane-of-workspace-on-window gensym-window last-workspace?)))
           (last-x-in-window
             (user-mouse-tracking-state-last-x-in-window state))
           (last-y-in-window
             (user-mouse-tracking-state-last-y-in-window state))
           (last-x-in-workspace
             (if last-image-plane?
                 (x-in-workspace-coordinates x-in-window last-image-plane?)
                 (user-mouse-tracking-state-last-x-in-workspace state)))
           (last-y-in-workspace                                    ; USER units (-Y)
             (if last-image-plane?
                 (-w (y-in-workspace-coordinates y-in-window last-image-plane?))
                 (user-mouse-tracking-state-last-y-in-workspace state)))
           (last-event
             (user-mouse-tracking-state-last-event state))
           (class-spec
             (user-mouse-tracking-state-classes state))
           ;; See item-x-position, item-y-position for conversion to user-visible
           ;; coordinates.
           (x-in-workspace
             (or x-in-workspace? 0))
           (y-in-workspace                                    ; USER units (-Y)
             (-w (or y-in-workspace? 0)))
           (key-code
             (key-code-of-mouse-pointer mouse-pointer))
           (shift-keys
             (canonical-key-modifier-bits key-code))
           (this-item?
             (or item? g2-window?))
           (this-item-serial?
             (when this-item? ; might be NIL, when aborting mouse tracking during log-out-workstation
               (copy-frame-serial-number (frame-serial-number this-item?)))))

      (setf (user-mouse-tracking-state-last-x-in-workspace state) x-in-workspace
            (user-mouse-tracking-state-last-y-in-workspace state) y-in-workspace)

      (setf (user-mouse-tracking-state-last-x-in-window state) x-in-window
            (user-mouse-tracking-state-last-y-in-window state) y-in-window)

      (multiple-value-bind (procedure? nargs)
          (get-mouse-tracking-procedure procedure-name)

        (macrolet ((validate (item serial)
                     #+development (unless (and (symbolp item) (symbolp serial))
                                     (dwarn "Args to local macro VALIDATE must be symbols"))
                     `(if (or (null ,item)
                              (null ,serial)
                              (frame-has-been-reprocessed-p ,item ,serial)
                              (null (serve-item-p ,item)))            ; Do we want this or not?
                          nil
                          ,item))
                   (invoke (event-name item x y)
                     `(when procedure?
                        (invoke-mouse-tracking-procedure
                          procedure? nargs ,event-name g2-window?
                          (validate original-item original-item-serial)
                          ,item ,x ,y
                          timestamp shift-keys))))

          (cond
            ;; Exit if aborting, if the mouse is up, or on a stray mouse-down event.
            ((or abort?
                 (key-code-is-mouse-up-p key-code)
                 (key-code-is-mouse-down-p key-code)
                 (and (key-code-is-mouse-motion-p key-code)
                      (not (mouse-down-p))))

             (when (eq last-event 'enter)
               (invoke 'LEAVE (validate last-item last-item-serial)
                       last-x-in-workspace last-y-in-workspace)
               (setq last-event 'leave))

             (invoke (if abort? 'ABORT-TRACKING 'STOP-TRACKING)
                     (validate this-item? this-item-serial?)
                     x-in-workspace y-in-workspace)
             (unless abort?
               (return-from-current-workstation-context 'user-mouse-tracking)))

            ((null this-item?)                ; Do not let a null this-item? get into last-item.
             ;; I don't think this can ever happen since this-item? can be NIL
             ;; only if there is no g2-window object, and that occurs only when
             ;; we are aborting.
             (dwarn "this-item is NIL in call-user-mouse-tracking-procedure-1 and not aborting!"))

            ;; Mouse motion over the same item.
            ((eq this-item? last-item)
             (when (and motion-events?
                        (or (/=f x-in-window last-x-in-window)  ; Mouse really moved.
                            (/=f y-in-window last-y-in-window))
                        (frame-matches-restriction-class-spec this-item? class-spec original-item))
               (invoke 'MOTION (validate this-item? this-item-serial?)
                       x-in-workspace y-in-workspace)))

            ;; Mouse motion over a new item.
            (t
             (setf (user-mouse-tracking-state-last-item state) this-item?)
             (frame-serial-number-setf (user-mouse-tracking-state-last-item-frame-serial-number state)
                                       (frame-serial-number this-item?))

             (when (eq last-event 'enter)
               (invoke 'LEAVE (validate last-item last-item-serial)
                       last-x-in-workspace last-y-in-workspace)

               (setq last-event 'leave))

             (when (frame-matches-restriction-class-spec this-item? class-spec original-item)
               (invoke 'ENTER (validate this-item? this-item-serial?)
                       x-in-workspace y-in-workspace)
               (setq last-event 'enter))

             (setf (user-mouse-tracking-state-last-event state) last-event)))))
      (reclaim-frame-serial-number this-item-serial?)
      (reclaim-frame-serial-number original-item-serial)
      (reclaim-frame-serial-number last-item-serial))))

;; Note: We get the following fairly useless behavior with "this class" clauses
;; in the mouse tracking: only propagate ENTER/LEAVE events on the original
;; item!




;;; The function `valid-mouse-tracking-procedure-arglist?' returns the
;;; number of required arguments if there is a match.

(defun valid-mouse-tracking-procedure-arglist? (argument-list-description)
  (if (argument-list-description-matches-template-p
        argument-list-description
        mouse-tracking-procedure-arglist-template)
      (var-count argument-list-description)))
;; changed return value from length to var-count since
;; argument-lists-descriptions are now managed-arrays. (pbk 2/7/96)



;;; The function `get-mouse-tracking-procedure' returns two values, the
;;; procedure instance and the number of required arguments to the procedure,
;;; if a valid procedure is found.

(defun get-mouse-tracking-procedure (procedure-name)
  (get-callback-procedure procedure-name
                          "mouse-tracking"
                          mouse-tracking-procedure-arglist-template))


;;; `with-three-thousand-variables-bound' moved to STACK-KERN



;;; The function `invoke-mouse-tracking-procedure' starts the mouse tracking
;;; procedure.  Since we call start-procedure-invocation directly, we do not
;;; get method dispatching.  Thus, the procedure may not be a generic
;;; procedure.  This decision was mostly an accident, but we can attempt
;;; justify it on the basis of efficient mouse tracking.  See the START action
;;; in stack-acts for how to do a method dispatch.  Note that arg g2-window?
;;; can in some rare cases be nil, e.g., during logout.

(defun invoke-mouse-tracking-procedure
    (procedure nargs event-name g2-window? original-item? item?
               x-in-workspace y-in-workspace
               timestamp shift-keys)
  (let ((arg-vector (allocate-managed-simple-vector nargs))
        (i 0))
    (macrolet ((pusharg (name)
                 `(when (<f i nargs)
                    (setf (svref arg-vector i) ,name)
                    (incff i))))

      ;; Supply as many args as the procedure takes, in this order.
      (pusharg event-name)
      (pusharg g2-window?)
      (pusharg (or original-item? evaluation-false-value))
      (pusharg (or item? evaluation-false-value))
      (pusharg x-in-workspace)
      (pusharg y-in-workspace)
      (pusharg timestamp)
      (pusharg shift-keys)

      (with-three-thousand-variables-bound
          (start-procedure-invocation-in-place
            procedure
            nil                                                    ; priority?
            nil                                                    ; wait?
            arg-vector                                            ; Local stack
            (1-f nargs)                                            ; Top of arguments on stack
            nargs                                            ; argument-count
            nil                                                    ; simulator-procedure?
            nil                                                    ; completion-form?
            nil                                              ; top-of-stack?
            nil
            nil))
      (reclaim-managed-simple-vector arg-vector))))



;;;; Modal Menu Workstation Context

;;; Modal menu state is a workstation context within which the user may do only
;;; a very limited assortment of things.  He can manipulate the menu, firing
;;; off one of its commands.  Anything else causes the menu to be deleted.

;;; This is used to be used directly only in the cut/copy/paste menu of the
;;; editor, but is now only used indirectly for that by the edit-menu context,
;;; q.v., below.

;;; These UI commands return from this context (with no return values), and then
;;; resume execution in the editor.

;; Planning to add other good things, like image-plane manipulations soon...

(define-workstation-context modal-menu (workstation-context-with-selection-focus)
  :selection-style
  top-level-with-selection-focus-but-no-mouse-tracking-is-selection-style
  :parent nil
  :modal t
  :constructor (make-modal-menu-state
                   (image-plane-with-selection-focus-of-workstation-context
                     reference-number-of-image-plane
                     block-with-selection-focus-of-workstation-context))
  :keymaps (screen-layout modal-menu))

(define-keymap modal-menu ()
  (<standard-abort-keys> abort-workstation-context)
  ((<mouse-down> entire-focus-menu-spot) mouse-down-on-modal-menu)
  ((<mouse-drag> menu-title-spot) start-dragging-menu-handler)
  ((<mouse-select> menu-title-spot) pop-down-menu)
  (<pseudo-keycode> run-top-level-event-handler)
  (<mouse-hover> run-top-level-event-handler)
  (<mouse-motion> run-top-level-event-handler)
  (otherwise requeue-event-and-abort-workstation-context))



(defmacro menu-workspace-of-model-menu-state (modal-menu-state)
  `(block-with-selection-focus-of-workstation-context ,modal-menu-state))


(def-structure-method clean-up-workstation-context (modal-menu-state)
  (let ((menu-workspace
          (menu-workspace-of-model-menu-state modal-menu-state)))
    (when (valid-block-in-workstation-context-p menu-workspace modal-menu-state)
      (delete-frame menu-workspace)))
  (funcall-superior-method modal-menu-state))


(defun enter-modal-menu-state (menu-workspace)
  (enter-context-in-current-workstation
    'modal-menu
    (let ((only-image-plane (first (image-planes-this-is-on menu-workspace))))
      (make-modal-menu-state
        only-image-plane
        (serial-number-of-image-plane only-image-plane)
        menu-workspace))
    nil))

(define-event-handler mouse-down-on-modal-menu (mouse-pointer)
  (cond
    ((find-spot-of-type-and-return-value-of-slot
       menu-title-spot
       frame-represented?)
     (search-for-mouse-drag mouse-pointer))
    (t (handle-enter-menu-choose mouse-pointer)
       (when (ole-menu-item-selection-p mouse-pointer)
         (execute-menu-choice mouse-pointer)))))





;;;; Edit Menu Workstation Context

;;; The `edit-menu context' includes, and is adapted from, the modal-menu
;;; workstation context (modal-menu-state structure).  The `edit-menu keymap'
;;; gets added to the keymaps used for modal-menu.  This keymap handles typed-in
;;; Space, Delete, and ordinary printing characters; in this case, the text
;;; region is considered to be "pending delete", and a return is done so that
;;; the text region will be preserved to be operated on by the calling context
;;; for the editor, which will delete the region (and maybe insert a character).

;;; The most important thing about this context is that the symbol
;;; PENDING-DELETE-TYPE-IN is returned as the first workstation context return
;;; value when a keystroke is typed that this knows operates on a region.  In
;;; this case, the event for that keystroke is requeued, the context is exited,
;;; the return function has to not delete the selected region, to allow it to
;;; be handled in the editor.

;;; The facility is a friend of the text-edit facility, since it needs to know
;;; about its keyboard command bindings, and especially of that module's
;;; function return-from-edit-menu (q.v., in EDIT1), which must, in general, be
;;; used as the continuation function.  Note, too, that the function
;;; `enter-edit-menu-state' should be used as the context entry function to
;;; get into this context.

;; Note: this code and "pending delete" style are new for 5.0 Rev. 3.  The
;; edit-operations menu had been managed by the modal-menu context.  (MHD
;; 3/13/98)

(define-workstation-context edit-menu (modal-menu-state)
  :selection-style
  top-level-with-selection-focus-but-no-mouse-tracking-is-selection-style
  :parent nil
  :modal t
  :constructor (make-edit-menu-state
                 (image-plane-with-selection-focus-of-workstation-context
                   reference-number-of-image-plane
                   block-with-selection-focus-of-workstation-context))
  :keymaps (edit-menu screen-layout modal-menu))

(define-keymap edit-menu ()
  ((or <delete-backward-keys> <delete-forward-keys>) edit-menu-pending-delete-type-in)
  (<printing-character> edit-menu-pending-delete-type-in)
  (space edit-menu-pending-delete-type-in)
  (<standard-newline-keys> edit-menu-pending-delete-type-in)
  #+development (f16 edit-menu-pending-delete-type-in) ; copy
  #+development (f18 edit-menu-pending-delete-type-in) ; paste
  #+development (f20 edit-menu-pending-delete-type-in) ; cut
  (control+x edit-menu-pending-delete-type-in) ; cut
  (control+c edit-menu-pending-delete-type-in) ; copy
  (control+v edit-menu-pending-delete-type-in) ; paste

  ((<mouse-down> close-box-spot) mouse-down-on-close-box-widget)
  ((<mouse-down> title-bar-spot) search-for-mouse-drag)
  ((<mouse-drag> title-bar-spot) start-dragging-title-bar-handler)
  ((mouse-up title-bar-spot) mouse-up-on-title-bar)
  )

(define-event-handler edit-menu-pending-delete-type-in (event)
  (requeue-workstation-event current-workstation event)
  (return-from-current-workstation-context
    type-of-current-workstation-context 'PENDING-DELETE-TYPE-IN))


(defun enter-edit-menu-state (menu-workspace)
  (enter-context-in-current-workstation
    'edit-menu
    (let ((only-image-plane (first (image-planes-this-is-on menu-workspace))))
      (make-edit-menu-state
        only-image-plane
        (serial-number-of-image-plane only-image-plane)
        menu-workspace))
    nil))





;;;; System Procedure Interface to Drawing


;;; The function `g2-work-on-drawing' works on drawing the given workspace on
;;; all on windows on which it is showing, until the minimum of the current
;;; timeout and the given timeout (in milliseconds) expires.  This procedure
;;; blocks out all other processing while running.  A timeout of zero means to
;;; allow an unlimited time slice.  A workspace of TRUE means all workspaces.
;;; A workspace of FALSE means no workspaces (used just for return value).
;;; Return a True if the drawing was finished, False otherwise.

(defparameter minimum-drawing-time-slice 10)

(defun-for-system-procedure g2-work-on-drawing (workspace-or-value timeout)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((timeout-value (evaluation-integer-value timeout))
         (new-timeout (minf maximum-time-slice-size timeout-value))
         (workspace? (if (and (framep workspace-or-value)
                              (workspace-p workspace-or-value))
                         workspace-or-value)))

    (cond ((or (eq workspace-or-value evaluation-false-value)
               (<f timeout-value 0)))

          ((and (eq workspace-or-value evaluation-true-value)
                (=f timeout-value 0))
           ;; All workspaces, unlimited time slice.
           (force-process-drawing))

          ((and workspace?
                (=f timeout-value 0))
           ;; One workspace, unlimited time slice.
           (force-workspace-drawing workspace?))


          ((and (eq workspace-or-value evaluation-true-value)
                (>f timeout-value 0))
           ;; All workspaces, with timeout.
           (let ((maximum-time-slice-size
                  ;; If we have already used our timeslice, do only minimum-drawing-time-slice more processing.
                  (maxf (+f (-f (get-fixnum-time) time-slice-start-time) minimum-drawing-time-slice)
                        new-timeout)))
             (force-some-process-drawing)))

          ((and workspace?
                (>f timeout-value 0))
           ;; One workspace, with timeout.
           (let ((maximum-time-slice-size
                  ;; If we have already used our timeslice, do only minimum-drawing-time-slice more processing.
                  (maxf (+f (-f (get-fixnum-time) time-slice-start-time) minimum-drawing-time-slice)
                        new-timeout)))
             (force-some-workspace-drawing workspace? nil))))

    ;; Return an evaluation boolean indicating doneness.
    (if (if workspace?
            (pending-drawing-for-workspace-p workspace?)
            (pending-drawing-for-process-p))
        evaluation-false-value
        evaluation-true-value)))



;;; The function `g2-work-on-printing' is similar, but only works on drawing
;;; the workspace to a printing window.  This all has to happen within
;;; printing's special dynamic context.

(defun-for-system-procedure g2-work-on-printing (workspace-or-value timeout)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((timeout-value (evaluation-integer-value timeout))
         (new-timeout (minf maximum-time-slice-size timeout-value))
         (workspace? (if (and (framep workspace-or-value)
                              (workspace-p workspace-or-value))
                         workspace-or-value)))
    (cond ((or (eq workspace-or-value evaluation-false-value)
               (<f timeout-value 0)))

          ((=f timeout-value 0)
           (with-unlimited-time-slice
             (service-print-jobs workspace?)))

          (t
           (let ((maximum-time-slice-size new-timeout))
             (service-print-jobs workspace?))))


    ;; Return an evaluation boolean indicating doneness.
    (if (pending-print-jobs-p workspace?)
        evaluation-false-value
        evaluation-true-value)))


;;;; Developer's tools



;;; The function `g2-trace-events' is a kb-level hook into event tracing,
;;; for developers only.

(defun-for-system-procedure g2-trace-events ((what symbol))
  (declare (values truth-value))
  (let ((value nil))
    (case what
      (off
       (untrace-events))
      (on
       (trace-events))

      (images-on
       (trace-images))
      (images-off
       (untrace-images)))

  (if value truth falsity)))


;;;; Things


;;; A `thing' is a block, connection, or table-cell.  Basically, something that
;;; can be selected in the selection UI, but also generally useful.

(def-concept thing)

(defun cell-of-table-p (thing)
  (or (text-cell-p thing)
      (and (framep thing)
           (superblock? thing)
           (frame-of-class-p (superblock? thing) 'table))))

(defun get-workspace-of-thing-if-any (thing)
  (let ((block-or-connection?
          (cond ((cell-of-table-p thing)
                 (get-table-for-cell thing))
                ((and (framep thing) (frame-of-class-p thing 'connection))
                 (connection-for-this-connection-frame thing))
                (t
                 thing))))
    (when block-or-connection?
      (get-workspace-of-block-or-connection block-or-connection?))))

;;; The function `common-workspace-of-things?' returns the workspace common to
;;; all of the selectable things in the list, if any.

(defun common-workspace-of-things? (things)
  (let ((workspace? nil))
    (when (loop for thing in things
                always (selectable-thing-p thing)
                as thing-workspace? = (get-workspace-of-thing-if-any thing)
                always thing-workspace?
                do (setq workspace? (or workspace? thing-workspace?))
                always (eq workspace? thing-workspace?))
      workspace?)))

;;; The function `frame-serial-number-for-thing?' returns NIL if thing is
;;; invalid.

(defun frame-serial-number-for-thing? (thing)
  (cond ((framep thing)
         (frame-serial-number thing))
        ((connection-p thing)
         (frame-serial-number-for-connection thing))
        ((text-cell-p thing)
         (let ((table? (get-table-for-cell thing)))
           (cond (table? (frame-serial-number table?))
                 (t
                  (dwarn "No table for ~s" thing)
                  nil))))
        (t                                ; Could be an available-frame-vector
         nil)))

(defun thing-has-been-reprocessed-p (thing reference-serial-number)
  (let ((serial-number? (frame-serial-number-for-thing? thing)))
    (or (null serial-number?)
        (frame-serial-number-equal serial-number? (frame-serial-number-recycled))
        (frame-serial-number-> serial-number? reference-serial-number))))

(defun render-thing-in-xor-overlay-p (thing)
  (cond ((framep thing)
         (render-frame-in-xor-overlay-p thing))
        ((connection-p thing)
         (render-connection-in-xor-overlay-p thing))
        ((text-cell-p thing)
         (and (get-table-for-cell thing)
              (render-frame-in-xor-overlay-p (get-table-for-cell thing))))))

;;; The function `center-of-thing' return the x,y-in-workspace of the "center"
;;; of the given thing.  For text cells, we actually return a position left, top
;;; near the left, top.

(defun center-of-thing (thing)
  (cond ((framep thing)
         (values (vertical-midline-of-block thing)
                 (horizontal-midline-of-block thing)))

        ((text-cell-p thing)
         (multiple-value-bind (left top right bottom)
             (get-table-cell-edges (get-table-for-cell thing) thing)
           right bottom
           (let ((format (text-cell-format thing)))
             (values (+f left (text-cell-left-margin format))
                     (+f top (halff (text-cell-line-height format)))))))

        ((connection-p thing)                ; TODO
         (let (vertices)
           (with-null-drawing-transform
             (setq vertices (compute-connection-vertices thing)))
           (loop with len = (maxf 1 (halff (length vertices)))
                 for (x-in-workspace y-in-workspace) on vertices by 'cddr
                 summing x-in-workspace into x-sum using +f
                 summing y-in-workspace into y-sum using +f
                 finally
                   (reclaim-gensym-list vertices)
                   (return (values (floorf x-sum len) (floorf y-sum len))))))
        (t
         (values 0 0))))


(defun thing-class (thing)
  (cond ((text-cell-p thing) 'text-cell)
        (t (class-of-thing thing))))

;;; The function `thing-block' returns the nearest parent block for thing, which
;;; is thing itself except for text cells and connection structures.

(defun thing-block (thing)
  (cond ((text-cell-p thing) (get-table-for-cell thing))
        ((connection-p thing) (connection-frame thing))
        (t thing)))

;;; The function `connection-frame' returns the connection frame corresponding
;;; to the given connection structure.  It is created if needed.

(defun connection-frame (connection-structure)
  (or (connection-frame-of-connection? connection-structure)
      (get-or-make-connection-frame-and-activate-if-appropriate connection-structure)))


;;;; Evaluation Values for Things


;;; We need to make selection "things" be evaluation values for the selection
;;; API. A sequence represents a list, an item represents itself or a connection
;;; structure, and a structure(table,row,column) represents a table cell.

(defparameter type-specification-of-thing
  '(or (class item)
    (structure
     ((table (or (class table-item) ; Not graphs or menus.
                 (class readout-table)))
      (row integer)
      (column integer)))))

;;; The function `export-thing' computes the user-visible evaluation-value for a
;;; thing.

(defun export-thing (thing)
  (cond ((cell-of-table-p thing)
         (export-table-cell thing))
        ((framep thing)
         thing)
        ((connection-p thing)
         (connection-frame thing))
        (t
         #+development
         (cerror "Proceed" "Unknown thing in export-thing: ~s" thing)
         nil)))

(defun serve-thing-p (thing)
  (let ((item? (cond ((cell-of-table-p thing)
                      (get-table-for-cell thing))
                     ((framep thing)
                      thing)
                     ((connection-p thing)
                      (connection-frame thing)))))
    (when item?                                ; possible?
      (serve-item-p item?))))

(defun export-table-cell (table-cell)
  (loop with table = (get-table-for-cell table-cell)
        for row in (table-rows table)
        as i from 0
        as j = (position table-cell row)
        when j
          return (allocate-evaluation-structure-inline
                   'table table
                   'row i
                   'column j)))

;;; The function `export-things' exports a thing or list of things. It is
;;; complicated by the fact that a text-cell is a list internally. If the
;;; argument is a list of things, then it must be an eval-list and is reclaimed.

#+unused
(defun export-things (thing-or-things)
  (let ((list
          (cond ((text-cell-p thing-or-things) ; Careful: text-cells are lists.
                 (eval-list (export-table-cell thing-or-things)))
                ((consp thing-or-things)
                 (export-list-elements thing-or-things))
                (t
                 (eval-list (export-thing thing-or-things))))))
    (when list
      (allocate-evaluation-sequence list))))

(defun export-list-elements (things)
  (loop for sublist on things doing
    (setf (car sublist) (export-thing (car sublist))))
  things)

(defun import-thing (evaluation-thing)
  (cond ((evaluation-structure-p evaluation-thing)
         (import-table-cell evaluation-thing))
        ((of-class-p-function evaluation-thing 'connection)
         (connection-for-this-connection-frame evaluation-thing))
        (t
         evaluation-thing)))

(defun import-table-cell (structure)
  (let ((table? (evaluation-structure-slot structure 'table))
        (row?   (evaluation-structure-slot structure 'row))
        (col?   (evaluation-structure-slot structure 'column)))
    (when (and table? row? col? (>=f row? 0) (>=f col? 0))
      (nth col? (nth row? (table-rows table?))))))


;;;; Selection


;;; A selection-style user interface.  G2 maintains a set of "selected things",
;;; on each workstation which can be used as the target of keyboard and menu-bar
;;; commands.

(def-concept selection)


;;; A `selectable' is something which can be selected (in the UI sense).
;;; Currently, we allow blocks, connection structures, and table cells.

(def-concept selectable)

;;; How we represent and draw the current selection .  For this version of the
;;; selection UI, we restrict the selection to a single image-plane.

(def-structure (selection
                 #+development (:print-function print-selection)
                 (:constructor make-selection-1 ())
                 (:reclaimer reclaim-selection-internal))
  selection-frame-serial-number                ; Protects all frames in this structure.
  %primary-selection
  %secondary-selection)                        ; A slot-value list.

#+development
(defun print-selection (selection stream depth)
  (declare (ignore depth))
  (printing-random-object (selection stream)
    (format stream "~a (~d)"
            (name-of-type-description (type-description-of selection))
            (count-selection selection))))

(defun count-selection (selection)
  (+f (if (%primary-selection selection) 1 0)
      (length (%secondary-selection selection))))

(defun selection-non-empty-p (selection)
  (or (%primary-selection selection)
      (%secondary-selection selection)))

(defun make-selection ()
  (let ((selection (make-selection-1 )))
    (setf (selection-frame-serial-number selection) (copy-frame-serial-number
                                                      (current-frame-serial-number))
          (%primary-selection selection) nil
          (%secondary-selection selection) nil)
    selection))

(defun reclaim-selection (selection?)
  (when selection?
    (reclaim-frame-serial-number (selection-frame-serial-number selection?))
    (reclaim-slot-value-list (%secondary-selection selection?))
    (reclaim-selection-internal selection?)))

(defun copy-selection (selection)
  (let ((selection* (make-selection-1)))
    (setf (selection-frame-serial-number selection*) (copy-frame-serial-number
                                                       (selection-frame-serial-number selection))
          (%primary-selection selection*) (%primary-selection selection)
          (%secondary-selection selection*) (copy-list-using-slot-value-conses
                                              (%secondary-selection selection)))
    selection*))

(defun clear-selection (selection)
  (setf (%primary-selection selection) nil)
  (reclaim-slot-value-list (%secondary-selection selection))
  (setf (%secondary-selection selection) nil))

(defun ensure-selection-structure (image-plane)
  (unless (image-plane-current-selection image-plane)
    (setf (image-plane-current-selection image-plane) (make-selection)))
  (image-plane-current-selection image-plane))


;;; The macro `do-selection-things' runs body for each unreprocessed thing in
;;; selection. The first thing is guarenteed to be the primary selection.

(defmacro do-selection-things ((thing selection) &body body)
  (avoiding-variable-capture (selection &aux state)
    `(loop with ,state = t
           while ,state
           doing
       (let ((,thing (if (eq ,state t)
                         (%primary-selection ,selection)
                         (car ,state))))
         (setq ,state (if (eq ,state t)
                          (%secondary-selection ,selection)
                          (cdr ,state)))
         (when ,thing
           ,@body)))))

;;; The function `validate-selection' removes any deleted or recycled elements
;;; from the internal list.  It must be called before accessing those elements.

(defun validate-selection (selection?)
  (when selection?
    (let ((fsn (selection-frame-serial-number selection?)))
      (do-selection-things (thing selection?)
        (when (thing-has-been-reprocessed-p thing fsn)
          (remove-thing-from-selection thing selection?)))
      selection?)))


;;; The function `thing-in-selection-p' will later use a hash table.

(defun thing-in-selection-p (thing selection)
  ;; GENSYMCID-625: G2 abort when clicking on item table or shortly thereafter
  ;; Ensure the selection not to be nil and protect from access violation.
  ;; -- BVBlogic, Dec 26, 2011
  (when selection
    (or (eq thing (%primary-selection selection))
        (memq thing (%secondary-selection selection)))))

;;; The function `add-thing-to-selection' assumes that thing is not already
;;; selected.

(defun add-thing-to-selection (thing selection)
  (assert-for-development (not (thing-in-selection-p thing selection))
                          "Thing ~s is already selected" thing)
  (reclaim-frame-serial-number (selection-frame-serial-number selection))
  (setf (selection-frame-serial-number selection)
        (copy-frame-serial-number (current-frame-serial-number)))
  (cond ((null (%primary-selection selection))
         (setf (%primary-selection selection) thing))
        (t
         (slot-value-push thing (%secondary-selection selection))))
  thing)

(defun remove-thing-from-selection (thing selection)
  (cond ((eq thing (%primary-selection selection))
         (setf (%primary-selection selection)
               (slot-value-pop (%secondary-selection selection))))
        (t
         (setf (%secondary-selection selection)
               (delete-slot-value-element thing (%secondary-selection selection))))))

;;; The defconstant `selectable-attribute-value-formats' enumerates all of the
;;; possible text-cell-formats for cells in tables which we want to be
;;; selectable. Must be updated if new font sizes, etc, are added!

(defconstant selectable-attribute-value-formats
  '(attribute-value-format new-attribute-value-format
    small-attribute-value-format extra-large-attribute-value-format
    attribute-display-value-format large-attribute-display-value-format
    extra-large-attribute-display-value-format))


;;; The function `selectable-text-cell-p' is what prevents selecting the
;;; attribute-name side of attribute tables and the value side of readout tables
;;; from being selectable.

(defun selectable-text-cell-p (table text-cell)
  ;; This condition skips over empty cells, such as you get in multiframe-tables
  ;; for slots which don't exist in the frame for that cell. In any case, the
  ;; selection UI requires that we can get the table from the cell.
  (when (get-table-for-cell text-cell)
    (let ((format (name-or-names-for-frame (text-cell-format text-cell))))
      (cond ((memq format selectable-attribute-value-formats)
             t)
            ((eq format 'readout-table-text-cell-format)
             (neq (getfq (text-cell-plist text-cell) table)
                  'readout-table-display-value))))))

;; Q: Are icon-cells' the only class of block that can be in a table cell?
;; A: No. graph-grids are also possible.
(defun icon-cell-is-visible-p (icon-cell)
  (let ((button? (first-subblock icon-cell)))
    (cond ((and button? (frame-of-class-p button? 'editor-subcommand-button))
           (not (editor-subcommand-disabled-p button?)))
          (t
           ;; TODO: Maybe other cases here.
           (not (null button?))))))

(defun selectable-table-cell-p (table? cell?)
  (cond ((null table?) nil)
        ((null cell?) nil)
        ((subblock-of-icon-editor-p table?) nil)
        ((cell-is-text-cell-p cell?)
         (selectable-text-cell-p table? cell?))
        ((cell-is-block-p cell?)
         (and (frame-of-class-p cell? 'icon-cell)
              (icon-cell-is-visible-p cell?)))))

(defun subblock-of-icon-editor-p (block)
  (and (superblock? block)
       (frame-of-class-p (superblock? block) 'icon-editor-workspace)))

;;; The function `selectable-thing-p' returns non-NIL if thing is a selectable
;;; thing on a workspace. Although workspaces themselves are selectable, they
;;; aren't in this sense.

(defun selectable-thing-p (thing)
  (cond ((null thing) nil)
        ((framep thing)
         (and (block-p thing)                ; Not a dependent-frame.
              (or (item-p thing)
                  (frame-of-class-p thing 'inspect-history)
                  (frame-of-class-p thing 'inspect-command))
              (not (workspace-p thing))
              (not (subblock-of-icon-editor-p thing))))
        ((connection-p thing)
         t)
        ((text-cell-p thing)
         (selectable-table-cell-p (get-table-for-cell thing) thing))))

(defun thing-selectable-via-ui-p (thing)
  (and (selectable-thing-p thing)
       (non-menu-choice-permitted-p 'select-object (thing-block thing))))

(defun get-connection-structure (thing)
  (cond ((and (framep thing) (frame-of-class-p thing 'connection))
         (connection-for-this-connection-frame thing))
        (t
         thing)))


(defun image-plane-for-workspace (workspace? workstation)
  (when workspace?
    (get-image-plane-if-any workspace?
                            (detail-pane-for-workstation workstation))))


(defun primary-selection (workstation)
  (let* ((image-plane? (selected-image-plane workstation))
         (selection? (and image-plane? (image-plane-current-selection image-plane?))))
    (and selection?
         (validate-selection selection?)
         (%primary-selection selection?))))

(defun secondary-selection (workstation)
  (let* ((image-plane? (selected-image-plane workstation))
         (selection? (and image-plane? (image-plane-current-selection image-plane?))))
    (and selection?
         (validate-selection selection?)
         (%secondary-selection selection?))))


(defun primary-selection-on-image-plane (image-plane)
  (let ((selection? (image-plane-current-selection image-plane)))
    (and selection?
         (validate-selection selection?)
         (%primary-selection selection?))))

(defun secondary-selection-on-image-plane (image-plane)
  (let ((selection? (image-plane-current-selection image-plane)))
    (and selection?
         (validate-selection selection?)
         (%secondary-selection selection?))))

;;; The function `select-thing' adds thing (if is selectable) to the current
;;; selection for image-plane and redraws.  We assume that thing is on the given
;;; image-plane. If given a connection frame, we actually select the connection
;;; structure

(defun select-thing (thing? image-plane)
  (when thing?
    (gensym-assert (workspace-on-image-plane? image-plane))
    (gensym-assert (eq (get-workspace-of-thing-if-any thing?)
                       (workspace-on-image-plane? image-plane)))
    (setq thing? (get-connection-structure thing?))
    (when (and (selectable-thing-p thing?)
               (not (thing-selected-p thing? image-plane)))
      (let* ((selection (ensure-selection-structure image-plane))
             (primary-p (null (%primary-selection selection))))
	(validate-selection selection)
        (add-thing-to-selection thing? selection)
        (add-selection-highlight thing? image-plane primary-p)
        (note-selection-changed image-plane)))))

;;; This function is only called in select-things. It is same to select-thing.
;;; But it doesn't need to do validate-selection (this function is O(n)). 
;;; ----------- leaf 2010-09-06

(defun select-thing-1 (thing? image-plane)
  (when thing?
    (gensym-assert (workspace-on-image-plane? image-plane))
    (gensym-assert (eq (get-workspace-of-thing-if-any thing?)
                       (workspace-on-image-plane? image-plane)))
    (setq thing? (get-connection-structure thing?))
    (when (and (selectable-thing-p thing?)
               (not (thing-selected-p thing? image-plane)))
      (let* ((selection (ensure-selection-structure image-plane))
             (primary-p (null (%primary-selection selection))))
        (add-thing-to-selection thing? selection)
        (add-selection-highlight thing? image-plane primary-p)
        (note-selection-changed image-plane)))))

;;; The function `select-things' may someday be more efficient than calling
;;; select-thing N times.

(defun select-things (things image-plane)
  (let ((selection (ensure-selection-structure image-plane)))
    (validate-selection selection))
  (loop for thing in things doing
    (select-thing-1 thing image-plane)))

;;; The function `set-selection' makes the selection on image-plane be exactly
;;; the given things (modulo their selectablity).

(defun set-selection (thing-or-things image-plane &optional g2-window)
  (deselect-all-things image-plane)
  (cond ((text-cell-p thing-or-things)
         (select-thing thing-or-things image-plane))
        ((consp thing-or-things)
         (select-things thing-or-things image-plane)
         (update-att-tables thing-or-things g2-window))
        (t
         (select-thing thing-or-things image-plane)
         ;; SoftServe: Gensym-417 fix
         (when (connectionp thing-or-things)
           (setq thing-or-things (get-or-make-connection-frame-and-activate-if-appropriate
                                   thing-or-things)))
         (funcall-ui-command 'update-table-of-attributes-pane thing-or-things g2-window)
         (funcall-ui-command 'update-table-of-hidden-attributes-pane thing-or-things g2-window)
         ;; End of SoftServe
         (update-att-tables thing-or-things g2-window))))

;;; The function `deselect-thing' removes thing and its selection highlight from
;;; the current selection for image-plane.

(defun deselect-thing (thing image-plane)
  (setq thing (get-connection-structure thing))
  (let ((selection? (image-plane-current-selection image-plane)))
    (when (and selection? (thing-in-selection-p thing selection?))
      (let ((old-primary (%primary-selection selection?)))
        (remove-thing-from-selection thing selection?)
        (remove-selection-highlight thing old-primary selection? image-plane))
      (note-selection-changed image-plane))))

(defun deselect-things (things image-plane)
  (loop for thing in things doing
    (deselect-thing thing image-plane)))


;;; The function `deselect-all-things' uses a brute force approach to quickly
;;; clear all selections on image-plane.  It does not call deselect-thing.

(defun deselect-all-things (image-plane)
  (let ((selection? (image-plane-current-selection image-plane)))
    (when selection?
      (let ((was-nonempty-p (selection-non-empty-p selection?)))
        (cond ((or (drawing-is-scheduled?)
                   (not (show-selection-handles-p)))
               (remove-all-selection-highlights image-plane)
               (clear-selection selection?))
              (t
               (let ((selection* (copy-selection selection?)))
                 (clear-selection selection?)
                 (remove-all-selection-highlights image-plane selection*)
                 (reclaim-selection selection*))))
        (when was-nonempty-p
          (note-selection-changed image-plane))))))

;;; The function `deselect-thing-and-parts' deselects thing and any "parts" of
;;; it which could also possibly be selected (not parts in the parts.lisp
;;; sense).  These include subblocks and cells of tables.

(defun deselect-thing-and-parts (thing image-plane)
  (when (and (framep thing) (table-p thing))
    (deselect-table-cells thing image-plane))
  ;; We only want to recurse one level, hence inline code here.
  (when (and (framep thing) (block-p thing))
    (loop for subblock being each subblock of thing doing
      (when (table-p subblock)
        (deselect-table-cells subblock image-plane))
      (deselect-thing subblock image-plane)))
  (deselect-thing thing image-plane))

;;; The function `note-deletion-of-block-for-selection' is called whenever a
;;; block is deleted and must deselect block over all workstations.

(defun note-deletion-of-block-for-selection (block)
  (let ((workspace? (get-workspace-of-thing-if-any block)))
    ;; TODO: Any block with an item-configuration containing user-interface clauses
    ;; might change shortcuts in menus. Actually, just changing the selection may
    ;; change them.
    (class-case (class block)
      (kb-workspace (when (name-or-names-for-frame block)
                      (decache-dynamic-menus 'named-workspaces)))
      (user-menu-choice (decache-dynamic-menus 'user-menu-choices))
      (class-definition (decache-dynamic-menus 'class-names)))
    ;; Workspace may be NIL here, but if so, then
    ;; note-remove-as-subblock-for-selection would have been called earlier
    ;; during remove-as-subblock.
    (when workspace?
      (note-remove-as-subblock-for-selection block workspace?))))

(defun note-remove-as-subblock-for-selection (block superblock?)
  (when (and superblock? (workspace-p superblock?))
    (loop for image-plane in (image-planes-this-is-on superblock?) doing
      (deselect-thing-and-parts block image-plane))))

(defun note-deletion-of-connection-for-selection (connection)
  (let ((workspace? (get-workspace-of-thing-if-any connection)))
    (when workspace?
      (loop for image-plane in (image-planes-this-is-on workspace?) doing
        (deselect-thing connection image-plane)))))

(defun note-deletion-of-text-cell-for-selection (text-cell)
  (let ((workspace? (get-workspace-of-thing-if-any text-cell)))
    (when workspace?
      (loop for image-plane in (image-planes-this-is-on workspace?) doing
        (deselect-thing text-cell image-plane)))))

(defun note-deletion-of-all-text-cells-for-selection (table)
  (deselect-all-table-cells table))



;; TODO: Want a quick test whether block could possibly be selected on any
;; workstation.  What happens when workspace is hidden, is the selection lost?
;; If so, then presence of a workspace and image-plane is a quick test.

;;; The function `select-text-cell' takes care of recording the table for a
;;; text-cell in the text-cell's PARENT property.

(defun select-text-cell (table text-cell image-plane)
  (prepare-table-cell text-cell table)
  (select-thing text-cell image-plane))

(defun deselect-table-cells (table image-plane)
  (loop for row in (table-rows table) doing
    (loop for cell in row doing
      (deselect-thing cell image-plane))))

(defun deselect-all-table-cells (table)
  (let ((workspace? (get-workspace-if-any table)))
    (when workspace?
      (loop for image-plane in (image-planes-this-is-on workspace?) doing
        (deselect-table-cells table image-plane)))))

(defun update-selection-highlights-for-table (table)
  (when (selectable-thing-p table)
    (let ((workspace? (get-workspace-of-thing-if-any table)))
      (when workspace?
        (loop for row in (table-rows table) doing
          (loop for cell in row doing
            (loop for image-plane in (image-planes-this-is-on workspace?) doing
              (when (thing-selected-p cell image-plane)
                (recompute-selection-highlights cell)))))))))

;; FIXME: Hideously slow. Many improvements possible here.


(defun workstation-current-selection (workstation)
  (let ((image-plane? (selected-image-plane workstation)))
    (when image-plane?
      (image-plane-current-selection image-plane?))))


;;; The function `current-selection' returns the current selection object, if it
;;; exists and is non-empty.  The "current" selection is the selection on the
;;; selected image-plane of the current workstation.

(defun current-selection (&optional (workstation current-workstation))
  (let ((image-plane? (selected-image-plane workstation)))
    (when (and image-plane?
               (image-plane-current-selection image-plane?)
               (selection-non-empty-p (image-plane-current-selection image-plane?)))
      (image-plane-current-selection image-plane?))))

(defun current-primary-selection ()
  (let ((selection? (current-selection)))
    (and selection? (%primary-selection selection?))))

(defun image-plane-selection-non-empty-p (image-plane?)
  (and image-plane?
       (image-plane-current-selection image-plane?)
       (selection-non-empty-p (image-plane-current-selection image-plane?))))


;;; The function `compute-selection-blocks' returns a newly consed dragging list
;;; of the blocks in the current selection. Table cells count as their parent
;;; table.

(defun compute-selection-blocks (&optional (selection (current-selection)))
  (let (blocks)
    (do-selection-things (thing selection)
      (when (text-cell-p thing)
        (setq thing (get-table-for-cell thing)))
      (when (framep thing)
        (dragging-pushnew thing blocks)))
    blocks))


;;; The function `selection-has-at-least-n-blocks-p' is true if the selection on
;;; image-plane contains at least n distinct, top-level blocks.  A selected cell
;;; in a table counts its parent table towards the total.

(defun selection-has-at-least-n-blocks-p (image-plane n)
  (let ((selection? (image-plane-current-selection image-plane))
        (blocks nil)
        (count 0))
    (when selection?
      (block search
        (do-selection-things (thing selection?)
          (when (text-cell-p thing)
            (setq thing (get-table-for-cell thing)))
          (cond ((not (framep thing)))
                ((memq thing blocks))
                (t
                 (incff count)
                 (cond ((>=f count n)
                        (reclaim-gensym-list blocks)
                        (return-from search t))
                       (t
                        (gensym-push thing blocks))))))
        (reclaim-gensym-list blocks)
        nil))))

;;; The function `selection-has-multiple-blocks-p' determines when we post the
;;; selection (operate-on-area) menu. It is true when the selection includes
;;; multiple, distinct top-level blocks. A selected cell in a table counts its
;;; parent table towards the total.

(defun selection-has-multiple-blocks-p (image-plane)
  (selection-has-at-least-n-blocks-p image-plane 2))


(defun primary-selection-as-block ()
  (let ((thing? (current-primary-selection)))
    (cond ((null thing?)
           nil)
          ((framep thing?)
           thing?)
          ((connection-p thing?)
           (connection-frame-of-connection? thing?)))))

(defun thing-selected-p (thing image-plane)
  (let ((selection? (image-plane-current-selection image-plane)))
    (when selection?
      (thing-in-selection-p thing selection?))))

(defun thing-or-parent-selected-p (thing image-plane)
  (or (thing-selected-p thing image-plane)
      (and (text-cell-p thing)
           (thing-selected-p (get-table-for-cell thing) image-plane))))

;; Some utilities for the selection API.

(defun import-selectable-things (e-thing-or-things g2-window)
  (let ((current-g2-user-mode? (or (g2-user-mode g2-window)
                                   'administrator)))
    (cond ((null e-thing-or-things)
           nil)
          ((evaluation-sequence-p e-thing-or-things)
           (loop for e-thing being each evaluation-sequence-element of e-thing-or-things
                 as thing = (import-thing e-thing)
                 when (thing-selectable-via-ui-p thing)
                   collect thing using eval-cons))
          (t
           (let ((thing (import-thing e-thing-or-things)))
             (when (thing-selectable-via-ui-p thing)
               (eval-list thing)))))))

(defun get-selection-as-eval-list (image-plane?)
  (when (and image-plane? (image-plane-current-selection image-plane?))
    (let ((list ()))
      (do-selection-things (thing (image-plane-current-selection image-plane?))
        (when (serve-thing-p thing)
          (eval-push thing list)))
      ;; Mutate (a b ... z) into (z a b ...). This returns the things in the order
      ;; they were originally selected.
      (nconc (last list) (nbutlast list)))))


;;;; Native Window Selection


(defun selected-native-window? (workstation?)
  (when workstation?
    (find-native-window (window-for-workstation workstation?)
                        (handle-of-selected-native-window? workstation?))))

;;; The function `handle-window-selected' runs in response to a user-gesture on
;;; the remote TW which activated or set focus to the given native-window.

(defun handle-window-selected (native-window event-plist)
  event-plist
  #+development (trace-native-window 'selected native-window event-plist)
  (let* ((image-plane? (native-image-plane? native-window))
         (native-window-client-operation 'activate)
         (native-window-updated-by-client native-window)
         (native-image-plane-updated-by-client image-plane?))
    (select-native-window native-window)))

;;; The function `select-native-window' selects the native-window, and its
;;; image-plane if it has one, both on the native-window's workstation.

(defun select-native-window (native-window)
  (let* ((gensym-window (native-window-gensym-window native-window))
         (workstation (workstation-this-is-on gensym-window))
         (image-plane? (native-image-plane? native-window)))

    (cond (image-plane?
           (select-image-plane image-plane?))
          ((not (eql (handle-of-selected-native-window? workstation)
                     (native-window-handle native-window)))
           (%deselect-image-planes workstation)
           (setf (handle-of-selected-native-window? workstation)
                 (native-window-handle native-window))
           (note-selection-changed native-window)))

    (unless (eq native-window native-window-updated-by-client)
      ;; TODO: Want to activate, not just show. This expands a collapsed pane,
      ;; but does nothing(?) for a completely hidden pane.
      (show-native-window native-window sw-show))))


;;;; Workspace Selection


;;; The function `select-workspace' makes workspace be the "selected" workspace
;;; on workstation, if it is selectable.  The selected workspace is the target
;;; of menu bar commands and keyboard commands which don't use the current mouse
;;; position.

(defun select-workspace (workspace workstation)
  (let ((image-plane? (image-plane-of-workspace-on-workstation workstation workspace)))
    (when image-plane?
      (select-image-plane image-plane?))))

;;; The function `select-image-plane' selects the given image-plane, if
;;; possible.  Returns non-NIL if successful.

(defun select-image-plane (image-plane)
  (let ((gensym-window (gensym-window-for-image-plane image-plane)))
    (when (and (selection-enabled-p gensym-window)
               (selectable-image-plane-p image-plane))
      (%select-image-plane image-plane)
      (when (multiwindow-ui-p gensym-window)
;                 (right-click-lifts-to-top-in-native-ui-p))
        (raise-image-plane-to-top image-plane))
      image-plane)))

;;; The function `%select-image-plane' makes new-image-plane be the selected
;;; one, without checking whether it should be selectable or not.

(defun %select-image-plane (new-image-plane)
  (let* ((workstation (workstation-of-image-plane new-image-plane))
         (old-image-plane? (selected-image-plane workstation))
         (native-window? (image-plane-native-window? new-image-plane)))
    (when (neq new-image-plane old-image-plane?)
      (when old-image-plane?
        (draw-or-erase-all-selection-highlights old-image-plane?)) ; Erase

      (setf (selected-image-plane workstation) new-image-plane
            (handle-of-selected-native-window? workstation) (if native-window?
                                                                (native-window-handle
                                                                  native-window?)))
      (when old-image-plane?
        (when (show-selection-handles-p)
          (invalidate-all-selection-handles old-image-plane?))
        (refresh-borders-of-image-plane old-image-plane?))

      ;; We have defined SW-SHOWDEFAULT to mean to activate the window (focus,
      ;; blue title bar, and a checkmark in the Window menu), but don't lift to
      ;; top. Only TW 82r1 or greater knows to not do the lift-to-top. For
      ;; HQ-5197753.  -fmw, 2/23/06
      (when native-window?
        (unless (eq native-image-plane-updated-by-client new-image-plane)
          (show-native-window native-window? sw-showdefault)))

      (draw-or-erase-all-selection-highlights new-image-plane) ; Draw
      (when (show-selection-handles-p)
        (invalidate-all-selection-handles new-image-plane))
      (refresh-borders-of-image-plane new-image-plane)

      (note-selection-changed new-image-plane))))

(defun %deselect-image-planes (workstation)
  (let ((image-plane? (selected-image-plane workstation)))
    (when image-plane?
      (draw-or-erase-all-selection-highlights image-plane?)
      (setf (selected-image-plane workstation) nil)
      (when (show-selection-handles-p)
        (invalidate-all-selection-handles image-plane?))
      (refresh-borders-of-image-plane image-plane?))))

(defun select-and-raise-image-plane (image-plane)
  (select-image-plane image-plane)        ; Maybe. Agrees with powerpoint, eg.
  (raise-image-plane-to-top image-plane))


(defun next-selectable-image-plane-in-list (image-plane list)
  (or (loop for ip in (cdr (memq image-plane list))
            when (selectable-image-plane-p ip)
              return ip)
      (loop for ip in list
            when (selectable-image-plane-p ip)
              return ip)))

;;; The function `next-selectable-image-plane' returns the next selectable
;;; image-plane in the stacking order, if any. Note that it could be EQ to
;;; image-plane or could be NIL if there are no selectable image-planes.

(defun next-selectable-image-plane (image-plane)
  (next-selectable-image-plane-in-list
    image-plane (stack-of-image-planes (pane-for-image-plane image-plane))))

(defun previous-selectable-image-plane (image-plane)
  (let ((list (nreverse
                (copy-list-using-gensym-conses
                  (stack-of-image-planes (pane-for-image-plane image-plane))))))
    (prog1 (next-selectable-image-plane-in-list image-plane list)
      (reclaim-gensym-list list))))


;;; The function `deselect-workspace' deselects given workspace and selects the
;;; "next" one, if any.

(defun deselect-workspace (workspace workstation)
  (let ((image-plane? (image-plane-of-workspace-on-workstation workstation workspace)))
    (when (and image-plane?
               (eq image-plane? (selected-image-plane workstation)))
      (%deselect-image-planes workstation)
      (let ((next? (next-selectable-image-plane image-plane?)))
        (when (and next? (neq next? image-plane?))
          (select-and-raise-image-plane next?))
        (note-selection-changed (or next? image-plane?))))))


(defun selected-workspace (&optional (workstation current-workstation))
  (let ((image-plane? (selected-image-plane workstation)))
    (and image-plane?
         (workspace-on-image-plane? image-plane?))))


;;; The function `remove-as-selected-image-plane' is called after an image-plane
;;; is deleted. Note than image-plane is in a deleted state here.  For
;;; image-planes, "deleted" does not mean recycled, rather, just without a
;;; workspace and not in the stack.

(defun remove-as-selected-image-plane (workstation image-plane was-native?)
  (when (eq image-plane (selected-image-plane workstation))
    (setf (selected-image-plane workstation) nil)
    (unless was-native?                        ; If native, Windows has already chosen a window.
      (select-topmost-workspace workstation))))


;;; The function `select-topmost-workspace' is called when first enabling the
;;; selection UI, after the currently selected image-plane is deleted, or after
;;; a new image-plane is created, to ensure that some workspace always has the
;;; focus. KB loading uses `select-default-workspace'.

(defun select-topmost-workspace (workstation)
  (let ((workspace? (topmost-selectable-workspace workstation)))
    (when workspace?
      (select-workspace workspace? workstation))))


;;; The function `select-default-workspace' selects the "default" workspace,
;;; meaning the topmost non-logbook page, or else the one specified in the KB
;;; save (TODO).

(defun select-default-workspace (workstation)
  (let ((workspace? (default-selectable-workspace workstation)))
    (when workspace?
      (select-workspace workspace? workstation))))

;;; The function `default-selectable-workspace' returns the topmost selectable
;;; non-logbook-page workspace on workstation, if one exists, else the topmost
;;; selectable workspace on workstation, if one exists, else NIL.

(defun default-selectable-workspace (workstation)
  (loop for image-plane in (stack-of-image-planes (detail-pane-for-workstation workstation))
        as workspace? = (workspace-on-image-plane? image-plane)
        doing
    (when (and workspace?
               (selectable-image-plane-p image-plane)
               (not (frame-of-class-p workspace? 'logbook-page)))
      (return workspace?))
        finally
          (return (topmost-selectable-workspace workstation))))


(defun topmost-selectable-workspace (workstation)
  (loop for image-plane in (stack-of-image-planes (detail-pane-for-workstation workstation))
        when (selectable-image-plane-p image-plane)
          return (workspace-on-image-plane? image-plane)))

;;; The function `attribute-table-workspace-p' returns T for workspaces
;;; generated as a result of the TABLE command.  Ideally, such workspaces would
;;; have their own class.

(defun attribute-table-workspace-p (workspace)
  (and (frame-of-class-p workspace 'temporary-workspace)
       (has-subblocks-p workspace)
       (has-only-one-subblock-p workspace)
       (attribute-table-p (first-subblock workspace))))


;;; The function `selectable-image-plane-p' is the ultimate authority on whether
;;; an image-plane (aka a view of a workspace on a window) is selectable in the
;;; selection UI.  Note that if the image-plane isn't selectable, then
;;; necessarily nothing on the the image-plane is selectable.

(defun selectable-image-plane-p (image-plane)
  (and (workspace-on-image-plane? image-plane)
       (not (unselectable-image-plane-p image-plane))))


(defun workspace-selected-p (workspace? workstation)
  (and workspace? (eq workspace? (selected-workspace workstation))))

(defun image-plane-selected-p (image-plane)
  (eq image-plane
      (selected-image-plane
        (workstation-of-image-plane image-plane))))



;;;; Selection Highlighting


;; See also workspace-title-bar-background

(defun primary-selection-color (image-plane)
  image-plane                                ; Later: configurable color per window/workspace.
  (default-primary-selection-color drawing-parameters))

(defun secondary-selection-color (image-plane)
  image-plane
  (default-secondary-selection-color drawing-parameters))

(defun add-selection-highlight (thing image-plane primary-p)
  (cond ((show-selection-handles drawing-parameters)
         (invalidate-selection-handles thing image-plane))
        (t
         (let* ((color (if primary-p
                           (primary-selection-color image-plane)
                           (secondary-selection-color image-plane)))
                (cursor (create-selection-highlight-for-thing thing color)))
           (add-image-plane-cursor image-plane cursor)
           (draw-image-plane-cursor image-plane cursor)))))

(defun remove-selection-highlight (thing old-primary selection image-plane)
  (let* ((new-primary?
           (%primary-selection selection))
         (primary-selection-changed-p
           (and new-primary?
                (neq old-primary new-primary?))))
    (cond ((show-selection-handles drawing-parameters)
           (invalidate-selection-handles thing image-plane)
           (when primary-selection-changed-p
             (invalidate-selection-handles new-primary? image-plane)))
          (t
           ;; If primary selection changed, update its cursor's color.
           (when primary-selection-changed-p
             (let ((cursor? (find-selection-highlight new-primary? image-plane)))
               (when cursor?
                 (change-color-of-selection-highlight
                   image-plane cursor? (primary-selection-color image-plane)))))

           (let ((cursor? (find-selection-highlight thing image-plane)))
             (when cursor?
               (draw-image-plane-cursor image-plane cursor?)
               (remove-image-plane-cursor image-plane cursor?)
               (reclaim-image-plane-cursor cursor?)))))))

(defun remove-all-selection-highlights (image-plane &optional selection?)
  (when (show-selection-handles drawing-parameters)
    (invalidate-all-selection-handles image-plane selection?))
  ;; Do this too, always, in case some are leftover.
  (remove-all-selection-highlight-cursors image-plane))

(defun invalidate-all-selection-handles (image-plane &optional selection?)
  (let ((selection? (or selection? (image-plane-current-selection image-plane))))
    (when selection?
      (do-selection-things (thing selection?)
        (invalidate-selection-handles thing image-plane)))))

(defun create-selection-highlight-cursors (image-plane)
  (when (image-plane-current-selection image-plane)
    (do-selection-things (thing (image-plane-current-selection image-plane))
      (add-selection-highlight thing image-plane (eq thing (primary-selection-on-image-plane image-plane))))))

(defun remove-all-selection-highlight-cursors (image-plane)
  (dolist-safely (cursor (image-plane-cursors image-plane))
    (when (selection-highlight-cursor-p cursor)
      (draw-image-plane-cursor image-plane cursor)
      (remove-image-plane-cursor image-plane cursor) ; O(N^2)
      (reclaim-image-plane-cursor cursor))))


;;; The function `recompute-selection-highlights' updates the selection
;;; highlights, if any, for thing, to match thing's current geometry.

(defun recompute-selection-highlights (thing)
  (unless (show-selection-handles drawing-parameters)
    (let ((workspace? (get-workspace-of-thing-if-any thing)))
      (when workspace?                        ; Can't be selected if no workspace (check this).
        (loop for current-image-plane in (image-planes-this-is-on workspace?) doing
          ;; TODO: Cache a bit saying whether selection is enabled anywhere.
          (when (and (selection-enabled-p (gensym-window-for-image-plane current-image-plane))
                     (not (printing-image-plane-p current-image-plane)))
            (let ((sublist? (find-selection-highlight-position thing current-image-plane)))
              (when sublist?
                (let* ((old-cursor (car sublist?))
                       (new-cursor (create-selection-highlight-for-thing
                                     (selection-highlight-thing old-cursor)
                                     (selection-highlight-color old-cursor))))
                  (let ((gensym-window (gensym-window-for-image-plane current-image-plane)))
                    (with-raw-window-transform-and-draw-area (gensym-window)
                      (with-nested-transform-and-draw-area-of-image-plane-contents?
                          (current-image-plane)
                        (on-image-plane (current-image-plane)
                          (replace-selection-highlight sublist? new-cursor))))))))))))))


;;; The function `create-selection-highlight-for-thing' returns a newly consed
;;; image-plane-cursor.

(defun create-selection-highlight-for-thing (thing color)
  (let ((selectable (get-connection-structure thing)))
    (cond ((connection-p selectable)
           (create-selection-highlight-for-connection selectable color))
          ((framep selectable)
           ;; todo: connection-frame
           (create-selection-highlight-for-block selectable color))
          ((text-cell-p thing)
           (create-selection-highlight-for-text-cell thing color))
          (t
           #+development (cerror "Continue" "Not a selectable: ~s" thing)
           nil))))

(defun create-selection-highlight-for-text-cell (text-cell color)
  (multiple-value-bind (left top right bottom)
      (get-table-cell-edges (get-table-for-cell text-cell) text-cell)
    ;; FIXME: This highlights the inside, although is correct only at full-scale.
    (let ((w selection-highlight-line-width))
      (create-selection-highlight-cursor
        text-cell color (graphics-list (+f left w) (+f top w) (-f right w) (-f bottom w))))))

(defun create-selection-highlight-for-block (block color)
  (create-selection-highlight-cursor
    block color (graphics-list
                  (left-edge-of-block block)
                  (top-edge-of-block block)
                  (-f (right-edge-of-block block) (if (text-box-p block) 1 0))
                  (-f (bottom-edge-of-block block) (if (text-box-p block) 1 0)))))

;;; The function `create-selection-highlight-for-connection' returns an
;;; image-plane cursor for highlighting a connection.  The cursor is a
;;; graphics-list of (connection color . polygon-points), in workspace
;;; coordinates.

(defun create-selection-highlight-for-connection (connection color)
  (with-temporary-gensym-float-creation draw-diagonal-arrows
    (let* ((width (compute-connection-width-given-connection-frame-or-class
                    (connection-frame-or-class connection)))
           (fwidth2 (/e (coerce-to-gensym-float (+f width selection-highlight-line-width)) 2.0))
           vertices upper-points lower-points)
      (with-null-drawing-transform
        (setq vertices (compute-connection-vertices connection)
              upper-points (compute-miter-points fwidth2 vertices)
              lower-points (compute-miter-points (-e fwidth2) vertices)))
      (cond ((or (null upper-points) (null lower-points))
             ;; Zero-length connection. Just make a small box.
             (let ((x (car vertices))
                   (y (cadr vertices)))
               (reclaim-gensym-list vertices)
               (create-selection-highlight-cursor
                 connection color
                 (graphics-list (-f x 1) (-f y 1)
                                (+f x 1) (-f y 1)
                                (+f x 1) (+f y 1)
                                (-f x 1) (+f y 1)
                                (-f x 1) (-f y 1)))))
            (t
             (reclaim-gensym-list vertices)
             (loop for sublist on lower-points by 'cddr
                   as (x y) = sublist
                   do (setf (car sublist) y
                            (cadr sublist) x))
             (let ((points (nconc upper-points
                                  (nreverse lower-points)
                                  (gensym-list (car upper-points) (cadr upper-points)))))
               ;; TODO: Avoid this copy. Just needed to convert x-conses to graphics conses.
               (prog1
                   (create-selection-highlight-cursor
                     connection color (copy-list-using-graphics-conses points))
                 (reclaim-gensym-list points))))))))


;;; The function `update-all-selection-highlights' redraws selection highlights
;;; on all workstations, after a change to the desired highlight colors or the
;;; manner of drawing them (XOR rectangles versus painted handles, etc).

(defun update-all-selection-highlights (how-changed)
  (loop for workstation in workstations-in-service doing
    (update-selection-highlights-on-workstation workstation how-changed)))

(defun update-selection-highlights-on-workstation (workstation how-changed)
  (loop with primary-color = (default-primary-selection-color drawing-parameters)
        with secondary-color = (default-secondary-selection-color drawing-parameters)
        with show-handles-p = (show-selection-handles drawing-parameters)
        for image-plane in (stack-of-image-planes (detail-pane-for-workstation workstation))
        as primary-selection? = (primary-selection-on-image-plane image-plane)
        doing
    (cond ((null primary-selection?))

          (show-handles-p
           ;; Changed from old-style highlighting to handles.
           (remove-all-selection-highlight-cursors image-plane)
           (when (image-plane-selected-p image-plane)
             (invalidate-all-selection-handles image-plane)))

          ((eq how-changed 'mode)
           ;; Changed from handles to old-style highlighting.
           (when (image-plane-selected-p image-plane)
             (invalidate-all-selection-handles image-plane))
           (create-selection-highlight-cursors image-plane))

          ((eq how-changed 'color)
           (draw-or-erase-all-selection-highlights image-plane)
           (loop for cursor in (image-plane-cursors image-plane) doing
             (when (selection-highlight-cursor-p cursor)
               (let* ((thing (selection-highlight-thing cursor))
                      (new-color (if (eq thing primary-selection?)
                                     primary-color
                                     secondary-color)))
                 (setf (selection-highlight-color cursor) new-color))))
           (draw-or-erase-all-selection-highlights image-plane)))))


;;;; Selection Rubber Band



;;; The workstation-context `selection-rectangle' drags out a dotted rectangle
;;; on an image-plane, and adds the items within it to the current selection.
;;; Items are added and removed as the rectangle covers and uncovers them.

(define-workstation-context selection-rectangle ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :state-variables (image-plane
                     image-plane-serial-number
                     x-in-workspace        ; First corner
                     y-in-workspace
                     workspace                ; Protected ?
                     cursor                ; An image-plane-cursor
                     previous-fsn        ; FSN protecting following list. FIXME: Unused?
                     previous-things)        ; Dragging list of things previously in selection rect.
  :conc-name t
  :define-enter-context-function t
  :keymap ((<mouse-down> stop-dragging-selection-rectangle)
           (<mouse-motion> track-mouse-for-selection-rectangle)
           (<mouse-up> stop-dragging-selection-rectangle)
           (<standard-abort-keys> abort-workstation-context)
           (escape abort-workstation-context)))

(define-event-handler select-area
    (mouse-pointer image-plane workspace key-code)
  (when (and (selectable-image-plane-p image-plane)
             (non-menu-choice-permitted-p 'select-area workspace))
    (select-image-plane image-plane)        ; Since selections are invisible otherwise.
    (with-image-plane-transform (image-plane)
      (let* ((mouse-down-pointer (mouse-pointer-of-last-down current-workstation))
             (x (x-of-mouse-pointer mouse-down-pointer))
             (y (y-of-mouse-pointer mouse-down-pointer))
             (x-in-workspace (x-in-workspace x))
             (y-in-workspace (y-in-workspace y))
             (color (compute-workspace-foreground-color image-plane))
             (cursor (create-selection-rectangle-cursor color x-in-workspace y-in-workspace))
             (state-block
               (enter-selection-rectangle-context
                 :image-plane image-plane
                 :image-plane-serial-number (serial-number-of-image-plane image-plane)
                 :x-in-workspace x-in-workspace
                 :y-in-workspace y-in-workspace
                 :workspace workspace
                 :cursor cursor)))
        (unless (shift-bit-on-p key-code)
          (deselect-all-things image-plane))
        (add-image-plane-cursor image-plane cursor)
        (draw-image-plane-cursor image-plane cursor)
        ;; This ensures we go away if the workspace or image-plane does.
        (add-mouse-pointer-to-guardians-of-workstation-context mouse-down-pointer state-block)))))

(define-event-handler track-mouse-for-selection-rectangle
    ((selection-rectangle-state workstation-context-specifics)
     x-in-window y-in-window)
  (let ((image-plane (selection-rectangle-state-image-plane selection-rectangle-state))
        (cursor (selection-rectangle-state-cursor selection-rectangle-state))
        (workspace (selection-rectangle-state-workspace selection-rectangle-state))
        (old-things (selection-rectangle-state-previous-things selection-rectangle-state)))
    (let* ((margin 0)                        ; (if workspace? (workspace-margin workspace?) 0))
           (x-in-workspace (x-within-workspace x-in-window image-plane margin))
           (y-in-workspace (y-within-workspace y-in-window image-plane margin)))
      (unless (and (=f (fourth cursor) x-in-workspace)
                   (=f (fifth cursor) y-in-workspace))
        (with-raw-window-transform-and-draw-area
            ((gensym-window-for-image-plane image-plane))
          (on-image-plane (image-plane)
            (with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
              (draw-selection-rectangle-cursor cursor)    ; Erase
              (setf (fourth cursor) x-in-workspace        ; Move
                    (fifth cursor) y-in-workspace)
              (draw-selection-rectangle-cursor cursor)))) ; Draw

        (let ((new-things (compute-things-in-selection-rectangle workspace cursor)))
          (adjust-current-selection old-things new-things image-plane)
          (setf (selection-rectangle-state-previous-things selection-rectangle-state)
                new-things)
          (reclaim-dragging-list old-things))))))


;;; The function `adjust-current-selection' does a minimal number of
;;; selects/deselects to make current additional selection = new-things.

(defun adjust-current-selection (old-things new-things image-plane)
  (unless (equal old-things new-things)
    (loop for thing in new-things doing    ; Select newly added things
      (unless (memq thing old-things)
        (select-thing thing image-plane)))
    (loop for thing in old-things doing    ; Deselect newly removed things
      (unless (memq thing new-things)
        (deselect-thing thing image-plane)))))



;;; The function `block-in-selection-rectangle-p' determines whether a block is
;;; considered to be inside a selection rectangle.

(defun-substitution-macro block-in-selection-rectangle-p (block left top right bottom)
  (if t                                        ; TODO: user preference.
      (block-overlaps-rectangle-p block left top right bottom)
      (block-inside-rectangle-p block left top right bottom)))


(defun connection-in-selection-rectangle-p (connection left top right bottom)
  (with-draw-area (left top right bottom)
    (map-over-connection-rectangles
      connection
      #'connection-in-selection-rectangle-p-1
      nil)))

(defun connection-in-selection-rectangle-p-1 (left top right bottom value-so-far)
  (or value-so-far
      (rectangles-overlap-p                ; User preference here
        left-edge-of-draw-area
        top-edge-of-draw-area
        right-edge-of-draw-area
        bottom-edge-of-draw-area
        left top (1+f right) (1+f bottom))))

;;; The function `compute-things-in-selection-rectangle' returns a new dragging
;;; list of blocks and connections selected by the selection rectangle.

(defun compute-things-in-selection-rectangle (workspace cursor)
  (let ((left (minf (second cursor) (fourth cursor)))
        (top (minf (third cursor) (fifth cursor)))
        (right (maxf (second cursor) (fourth cursor)))
        (bottom (maxf (third cursor) (fifth cursor)))
        (result ()))
    (loop for block being each subblock of workspace doing
      (when (and (thing-selectable-via-ui-p block)
                 (block-in-selection-rectangle-p block left top right bottom))
        (dragging-push block result))
      (loop for connection being the output-connections of block doing
        (when (and (thing-selectable-via-ui-p connection)
                   (connection-in-selection-rectangle-p connection left top right bottom))
          (dragging-push connection result))))
    result))

;; TODO: Use index to speed this up (blocks-touching-region-for-drawing).
;; See also: list-blocks-within-area-of-workspace and g2-items-in-area

(define-event-handler stop-dragging-selection-rectangle (mouse-pointer)
  (track-mouse-for-selection-rectangle mouse-pointer) ; Update with last point.
  (return-from-current-workstation-context 'selection-rectangle))

(def-structure-method clean-up-workstation-context (selection-rectangle-state)
  (let ((image-plane (selection-rectangle-state-image-plane selection-rectangle-state))
        (cursor (selection-rectangle-state-cursor selection-rectangle-state))
        (serial-number (selection-rectangle-state-image-plane-serial-number
                         selection-rectangle-state)))
    ;; GENSYMCID-1018: Abort occur during the TWNG workspace operation
    ;; Here, it's possible that the image-plane has been reprocessed (i.e. deleted
    ;; and then re-created), in this case we shouldn't note any area selection.
    (when (image-plane-has-not-been-reprocessed-p image-plane serial-number)
      (note-area-selected
        (selection-rectangle-state-workspace selection-rectangle-state)
        (selection-rectangle-state-previous-things selection-rectangle-state)
        (second cursor) (third cursor)
        (fourth cursor) (fifth cursor)
        (gensym-window-for-image-plane image-plane)))

    ;; `selection-rectangle-state' may be internally changed by this funcall:
    (funcall-superior-method selection-rectangle-state)

    (let ((new-image-plane (selection-rectangle-state-image-plane selection-rectangle-state))
          (new-cursor (selection-rectangle-state-cursor selection-rectangle-state))
          (new-serial-number (selection-rectangle-state-image-plane-serial-number
                               selection-rectangle-state)))
      ;; Test if previous assumption in GENSYMCID-1018 is wrong.
      (gensym-assert (and (eq new-cursor cursor)
                          (eq new-image-plane image-plane)
                          (eq new-serial-number serial-number)))
      (clean-up-image-plane-cursor new-image-plane new-cursor new-serial-number))))


;;;; Selection Callbacks


;;; Whenever the selection changes on a window (image-plane), we schedule a task
;;; to invoke user-defined callbacks for the SELECTION-CHANGED event. We use a
;;; task so that all the selection changes made in the current microtask result
;;; in at most one call to the user procedures. Generally this means all the
;;; selection changes made by one UI gesture will result in just one callback.

;; The theory is that selection is UI-related, and so should be as responsive as
;; the workstation. I would use an immediate task, but that does not handle
;; calls like select(every connection-post), where each is run in a separate
;; task.  Of course, maybe that is G2's problem.

(defun note-selection-changed (image-plane-or-native-window)
  (let ((workstation (if (image-plane-p image-plane-or-native-window)
                         (workstation-of-image-plane image-plane-or-native-window)
                         (native-window-workstation image-plane-or-native-window))))
    (when (ui-callbacks-exist-p 'selection-changed nil)         ; Quick test.
      ;; We want some merging of selection-changed events, so if a task is
      ;; already scheduled, *but has not yet started to run*, then don't
      ;; schedule another one.
      (unless (future-schedule-task-in-place-p
                (selection-callbacks-task workstation))
        (with-immediate-scheduling ((selection-callbacks-task workstation))
          (run-selection-callbacks workstation))))))

(defun run-selection-callbacks (workstation)
  (cancel-task (selection-callbacks-task workstation))
  (let ((g2-window? (g2-window-for-gensym-window?
                      (window-for-workstation workstation))))
    (when g2-window?
      (invoke-ui-callbacks 'selection-changed g2-window? g2-window?))))


;;;; Area Selection Callbacks


(defun note-area-selected (workspace enclosed-items left top right bottom gensym-window)
  (when (ui-callbacks-exist-p 'area-selected nil) ; Quick test.
    (let ((g2-window? (g2-window-for-gensym-window? gensym-window)))
      (when g2-window?
        ;; These events are less frequent, so we don't bother coalescing.
        (with-immediate-scheduling ()
          (run-area-selected-callbacks
            (gensym-list workspace g2-window? left top right bottom)
            (copy-list-using-gensym-conses enclosed-items)
            (copy-frame-serial-number (current-frame-serial-number))))))))

(defun run-area-selected-callbacks (args enclosed-items fsn)
  (gensym-dstruct-bind ((workspace g2-window left top right bottom) args)
    (reclaim-gensym-list args)
    ;; We leak enclosed-items if these tests fail, but that's extremely unlikely.
    (unless (frame-has-been-reprocessed-p workspace fsn)
      (unless (frame-has-been-reprocessed-p g2-window fsn)
        (let ((particulars (allocate-evaluation-structure-inline
                             'selected-workspace workspace
                             'items (allocate-evaluation-sequence enclosed-items)
                             'left left
                             'top (-w top)
                             'right right
                             'bottom (-w bottom))))
          (invoke-ui-callbacks 'area-selected g2-window particulars))))))


;;;; Workspace Callbacks


(defun note-scrollbar-changed (workspace gensym-window)
  (let ((g2-window? (g2-window-for-gensym-window? gensym-window)))
    (when g2-window?
      (when (ui-callbacks-exist-p 'scrollbar-changed workspace) ; Quick test.
        (with-immediate-scheduling ()
          (run-workspace-callbacks
            'scrollbar-changed workspace g2-window?
            (copy-frame-serial-number (current-frame-serial-number))))))))


(defun note-workspace-hidden (workspace gensym-window)
  (let ((g2-window? (g2-window-for-gensym-window? gensym-window)))
    (when g2-window?
      (when (ui-callbacks-exist-p 'workspace-hidden workspace) ; Quick test.
        (with-immediate-scheduling ()
          (run-workspace-callbacks
            'workspace-hidden workspace g2-window?
            (copy-frame-serial-number (current-frame-serial-number))))))))

(defun run-workspace-callbacks (event workspace g2-window fsn)
  (unless (frame-has-been-reprocessed-p workspace fsn)
    (unless (frame-has-been-reprocessed-p g2-window fsn)
      (invoke-ui-callbacks event workspace g2-window))))


;;;; Selection Utilities


;;; The function `select-objects-after-transfer' is called after the successfull
;;; completion of a transfer associated with a New or Clone operation.

(defun select-objects-after-transfer (workspace blocks external-connections)
  (let ((image-plane? (image-plane-of-workspace-on-window
                        current-workstation-window workspace)))
    (when image-plane?
      (let ((things (nconc (union-blocks-with-their-internal-connections blocks)
                           (copy-list-using-dragging-conses external-connections))))
        (set-selection things image-plane?)
        (reclaim-dragging-list things)))))


;;; The function `union-blocks-with-their-internal-connections' returns a new
;;; dragging-list containing each block in blocks and each connection of each
;;; block whose other end is either a loose-end or a member of blocks.

(defun union-blocks-with-their-internal-connections (blocks)
  (let (list)
    (loop for block in blocks doing
      (dragging-push block list)
      (loop for connection being the connections of block
            as other-end = (get-block-at-other-end-of-connection connection block)
            doing
        (when (or (loose-end-p other-end)
                  (memq other-end blocks))
          (dragging-push connection list))))
    list))

;; See also: g2-clone-list-contents


;;;; Stock Commands


;;; A `stock command' is a command which is executed directly by
;;; platform-dependent C code, for now only in telewindows.  It has an name, ID,
;;; and doc string. The body in lisp can run be if the command is invoked from
;;; other than a native menu, but this is not normally done.  The command IDs
;;; must be distinct from all those used by NMS.

(def-concept stock-command)

(defmacro define-stock-command (name pretty-name id &optional options arglist &body body)
  `(define-ui-command (,name :pretty-name ,pretty-name :id ,id ,@options) ,arglist
     ,@body))

;; KEEP THIS LIST IN SYNC WITH MSINCLS.H
(define-stock-command connect "&Connect..." 1001)
(define-stock-command close-all "Close Al&l" 1002)
(define-stock-command close "&Close" 1003)
(define-stock-command cascade "&Cascade" 1005)
(define-stock-command exit "E&xit" 1006)
(define-stock-command tile "&Tile" 1007)
(define-stock-command tile-vertically "Tile &Vertically" 1008)
(define-stock-command tile-horizontally "Tile &Horizontally" 1009)
(define-stock-command about-telewindows "&About Telewindows" 1010)
(define-stock-command test "&Test" 1011)
(define-stock-command statusbar "&Statusbar" 1012)
(define-stock-command small "&Small" 1020)
(define-stock-command medium "&Medium" 1021)
(define-stock-command large "&Large" 1022)
;;Gensym-2041-TAM3-CH-SUCA-JIRA-46986-Add the ability to exclude "more windows" menu choice
(define-stock-command more-windows "More Windows..." 65279)

; (define-stock-command open "Load &KB..." 1013)
; (define-stock-command save-as "Sa&ve KB As..." 1014)

(define-stock-command toolbars "&Toolbars" 1015 nil (window)
 (when (nms-toolbars-p window)
   t))

(define-stock-command insert-object "&Insert Object" 1016)
(define-stock-command print-window "Print &Window" 1018 (:dialog t))

(define-ui-command (about-telewindows-in-misc-menu :pretty-name "&About Telewindows"
                                                   :dialog t
                                                   :name about-telewindows) (window)
    (when (native-windows-p window)
      (with-icp-window (window)
        (send-icp-tw-command window (key-code 'about-box)))))


;; This is a stock command because it makes sense for TW to get help even when
;; not connected to G2. The body is executed when run from F1, not when run from
;; the menu bar.

(define-stock-command help-topics "Help Topics" 1017 nil (window)
 (when (native-simple-dialogs-p window)
   (html-help window)))


;;; The function `htmp-help' starts the HTML help viewer on window, if possible,
;;; displaying the default help file.

(defun html-help (gensym-window)
 (when (native-simple-dialogs-p gensym-window)
   (with-icp-window (gensym-window)
     (send-icp-html-help
        gensym-window
        #w""                                ; pathname (ignored)
        0))))                                ; topic (ignored)


;;;; Developer Menu Bar


;;; The menu `developer-menu-bar' is the default menu bar for G2.  TW users see
;;; this once they have connected.  We duplicate some of the initial,
;;; unconnected TW menus and items here (eg, the window menu). A KB can
;;; completely replace this menu bar by use of the NMS facility.

(defmenu developer-menu-bar ()
  (submenu file-submenu)                ; load/merge/save
  (submenu edit-submenu)                ; Undo Redo Cut Copy Paste Delete SelectAll ...
  (submenu view-submenu)                ; Statusbar Toolbar Zoom ...
  (submenu workspace-submenu)                ; New-object and get-workspace is dynamic?
  (submenu entity-submenu)                ; TODO: icon-color is dynamic
  (submenu run-submenu)                        ; Start, pause, resume, etc.
  (submenu tools-submenu)                ; Miscellaneous
;  (submenu user-submenu)                ; Put all UMC's here.
  (submenu window-submenu)                ; Handled by TW
  (submenu help-submenu))

(defmenu (file-submenu :name file :title "&File" :capitalize t
                       :restriction-type main-menu) ()
  load-kb
  merge-kb
  save-kb
  ----
  printer-setup                ; Show system table (was user expecting the Win32 dialog?)
  print-window                ; Locally on TW, as a screenshot.
  print-to-server
  print-to-client
  ----
  load-recent-kb
  ----
  log-out                ; Leaves TW around
  shut-down-g2                ; Leaves TW around
  (command disconnect close-telewindows-connection)
  ;; TW built-in
  exit)                        ; Exits TW (closes connection and logs out, too)


;; Should this somehow execute editor commands while the editor is active?
(defmenu (edit-submenu :name edit :title "&Edit" :capitalize t
                       :restriction-type main-menu) ()
;  undo-g2
;  redo-g2
;  ----
;  cut-selection
;  copy-selection
;  paste-g2
  delete-selection
  select-all
;  duplicate-selection
;  ----
;  find                                        ; Find string on selected workspace
;  find-again                                ; TODO: shortcut key
  ----
  show-system-table                        ; Like preferences, so they go here.
  align-selection
  distribute-selection)


(defmenu (view-submenu :name view :title "&View" :capitalize t
                       :restriction-type global-keyboard) ()
  statusbar                                ; TW command. Wants to be main-menu restrictions!
  table-of-attributes-pane
  table-of-hidden-attributes-pane
  (submenu toolbars)
  (submenu menu-size)
  ----
  user-mode-aliases
  ----
  selection-full-scale

  scale-to-fit
  zoom-in
  zoom-out
  (command quarter-scale one-quarter-the-scale)
  four-times-the-scale
  toggle-visible-grid                        ; TODO: checkmarks
  refresh)


(defmenu (workspace-submenu :name workspace :title "Wor&kspace" :capitalize t
                            :restriction-type workspace-menu) ()
  new-workspace
  get-workspace
  ----
  (include item-creation-menu)
  ----
  name-workspace
  clone-workspace
  table-of-workspace
  color-workspace                                ; Maybe color-frame would be enough.
  move-workspace
  hide-workspace                                ; New position.  Get some review! (MHD 1/30/90)
  lift-to-top
  drop-to-bottom
  shrink-wrap
  ;; hide-workspace used to be here -- moved far away from delete by popular demand
  delete-workspace
  enable-workspace
  disable-workspace
  ----
  describe-workspace
;  table-of-hidden-attributes
  describe-configuration-of-workspace
  )


(defmenu (entity-submenu :name item :title "&Item" :capitalize t
                         :restriction-type item-menu) ()
  table-of-item
  go-to-subworkspace
  create-instance
; These all show up as "Edit" in the menu -- are mutually exclusive.
;  edit-text-box                                                    ; Rules.
;  edit-procedure
;  edit-external-procedure
;  edit-icon
  ----
;  table-of-values
  transfer-selection
  move-selection
  name-item                             ; not for rules?
  clone-selection
  change-min-size                     ; Only for rules.
  rotate-reflect
  change-size
  restore-to-normal-size
;  color                             ; TODO: submenu depends on selection.
  ----
  (include entity-lifting-menu)
  ----
  enable-item                             ; TODO: a toggle choice with checkmark
  disable-item
  describe-item
  table-of-hidden-attributes-of-item
;  show-unsaved-attributes
;  view-change-log
;  (include explanation-related-menu)
  describe-configuration-of-item
  create-subworkspace)


(defun command-name-in-menu-p (command-name menu-name)
  (let* ((menu? (find-menu-description menu-name))
         (choices (and menu? (menu-description-choice-list-internal menu?))))
    (when (consp choices)
      (loop for choice in choices
            thereis (cond ((atom choice)
                           (eq command-name choice))
                          ((memq (car choice) '(include submenu))
                           (command-name-in-menu-p command-name (second choice))))))))

;;; The function `command-runs-on-multi-selection-p' returns T for commands
;;; which should be enabled when the selection is multiple. It's difficult to
;;; compute this is general because it is hard to distinguish commands which
;;; operate on a workspace, for example, hence don't care about the size of the
;;; selection, versus commands which operate on a single item.

(defun command-runs-on-multi-selection-p (command)
  (let* ((command? (and (atom command) (find-ui-command command t)))
         (name? (and command? (ui-command-name command?))))
    (cond ((consp command)        ; user-menu-choices Have to allow them all. This works
                                ; since UMC's aren't currently allowed in the menu bar.
           t)
          ((null name?)
           nil)
          ((not (command-name-in-menu-p name? 'entity-submenu))
           ;; Anything NOT in the Item menu (aka entity-submenu) is permitted (hack).
           t)
          (t
           ;; Within the item menu, permit just these few commands.
           (memq name? '(move-selection transfer-selection clone-selection))))))

;; More mechanism is required in UI commands to handle this properly; for now,
;; we have this hack on entity-submenu.



(defmenu (run-submenu :name run :title "&Run" :capitalize t
                      :restriction-type main-menu) ()
  start
  pause
  resume
  (command continue continue-from-breakpoint)
  reset
  restart
  ----
  (submenu run-options))

(defmenu (tools-submenu :name tools :title "&Tools" :capitalize t
                        :restriction-type main-menu) ()
  inspect
  new-title-block
  neatly-stack-windows
  network-info
  change-mode
  create-new-user-mode-alias
  ----
  short-menus
  long-menus
  ----
  create-new-module
  delete-module
  change-password
  reinstall-authorized-users
  ----
  connect-to-foreign-image
  disconnect-from-foreign-image
  load-attribute-file
  write-g2-stats
  ----
  clear-kb
  (submenu package-preparation-menu))


;; Menu of all OK user menu choices in the KB, sorted alphabetically by label.
;; TODO: Sort hierarchically by class. Does not update properly.
(defmenu (user-submenu :name user :title "&User" :capitalize t) ()
  (sort-list
    (loop for user-menu-choice being each class-instance of 'user-menu-choice
          as symbol? = (user-menu-choice-symbol? user-menu-choice)
          when (and symbol? (frame-ok-p user-menu-choice))
            collect (slot-value-list 'user-menu-choice symbol?) using slot-value-cons)
    #'choice-sort nil))


(defmenu (window-submenu :name window :title "&Window" :capitalize t
                         :condition (with-mouse-pointer-bindings (window) mouse-pointer
                                      (mdi-frame-p window))
                         :restriction-type main-menu)
    ()
  close                                        ; "Cl&ose"
  close-all                                ; "Close Al&l"
  ----
  cascade                                ; "&Cascade"
  tile-horizontally                        ; "Tile &Horizontally"
  tile-vertically                        ; "Tile &Vertically"
  ;; Windows inserts menu items for each MDI child here.
  ;;Gensym-2041-TAM3-CH-SUCA-JIRA-46986-Add the ability to exclude "more windows" menu choice
  ----
  more-windows        ;"More Windows..."
  )

(defmenu (help-submenu :name help :title "&Help" :capitalize t
                       :restriction-type main-menu) ()
  help-topics
  (command keyboard-shortcuts help)        ; Key bindings
  about-telewindows)                        ; TW-local about box, or, G2 title block? or both?

(defmenu (toolbars :title "&Toolbars" :capitalize t
                   :restriction-type main-menu) ()
  toolbars)                                ; Stock command, enumerates all toolbars

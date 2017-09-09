;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module COMMANDS1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.


;;;; UI commands, part 1.

(declare-forward-reference inform-ui-client-interfaces-of-general-update function);view-g2
(declare-forward-reference item-may-be-deleted-by-user function)
(declare-forward-reference block-transferable-via-ui-command-p function)
(declare-forward-reference block-clonable-via-ui-command-p function)
(declare-forward-reference get-g2gl-process-parent-of-workspace-if-any function)
(declare-forward-reference change-size-permitted-p function)
(declare-forward-reference change-ui-property function)
(declare-forward-reference put-up-aliases-table function) ;TABLES

(declare-forward-references-to-module COMMANDS2
  (synthesize-mouse-pointer function)
  (g2-ui-create-property-grid function)
  (update-property-pane-after-edit function)
  (compute-filtered-blocks-from-selection function)
  (native-editor-window function)
  (g2-ui-manage-property-grid function))


(define-ui-command start ()
  "Start running the knowledge base"
  (when (and (g2-authorized-p)
             (not (or system-is-running system-has-paused)))
    (system-state-change-from-scheduler 'start)))


(define-ui-command pause ()
  "Stop running the knowledge base, while allowing it to be resumed later."
  (when (and system-is-running
             (not system-has-paused)
             current-workstation
             ;; Make sure we're logged in.  Fix here for bug HQ-3130711 "Control
             ;; Z works on a secure G2 before you have logged in!!!!!!".
             (eq (workstation-login-state current-workstation) 'logged-in))
    (system-state-change-from-scheduler 'pause)))


(define-ui-command resume ()
  "Continue running the KB from where it was paused."
  (when (and system-has-paused (g2-authorized-p) (not inside-breakpoint-p))
    (system-state-change-from-scheduler 'resume)))

(define-ui-command continue-from-breakpoint ()  ; resume-at-breakpoint
  "Continue running the KB from the point of the breakpoint."
  (when (and system-has-paused (g2-authorized-p) inside-breakpoint-p)
    (notify-user "Continue from the point of the breakpoint.")
    (return-from-breakpoint)))


;; In the menu-execute part, these don't check (g2-authorized-p)?

(defun-void notify-user-of-breakpoint (attempted-command)
  (notify-user "Cannot ~A because G2 is in a breakpoint.  ~
                Exit the breakpoint first, with resume."
               attempted-command))

(define-ui-command reset ()
  "Stop running the knowledge base and reset all variables, parameters, etc."
  (when (and (or system-has-paused system-is-running) (not inside-breakpoint-p))
    (system-state-change-from-scheduler 'reset)))

(define-ui-command restart ()
  "Continue running the KB from where it was paused."
  (when (and (or system-is-running system-has-paused)
             (g2-authorized-p)
             (not inside-breakpoint-p))
    (system-state-change-from-scheduler 'restart)))





;;; The function `system-state-change-from-scheduler' is used for the various
;;; system state changing UI commands.  Its action arg should be a symbol for one
;;; of the types of state changes, i.e., RESET, RESTART, RESUME, PAUSE, START,
;;; or CLEAR-KB.  It schedules a call to its subfunction
;;; system-state-change-from-scheduler-1, which will do any necessary
;;; notification as well as perform the actual action.  Scheduling serves to
;;; allow any workstation closing or unwinding to happen safely before the
;;; action, with its possibly destructive side effects, begins.

(defun system-state-change-from-scheduler (action)
  (cond ((and (confirm-run-state-changes-p)
              (neq action 'clear-kb)
              (boundp 'current-workstation)) ; Should always be true.
         (confirm-or-cancel
           (tformat-text-string "Do you really want to ~(~A~) G2?" action)
           #'system-state-change-from-scheduler-1
           (slot-value-list action)))
        (t
         (with-immediate-scheduling ()
           (system-state-change-from-scheduler-1 action)))))

(defun system-state-change-from-scheduler-1 (action)
  (case action
    (reset
     (notify-user "Resetting KB to beginning. You may start when ready.")
     (system-reset))
    (restart
     (notify-user "Resetting KB to beginning and restarting it.")
     (system-restart))
    (resume
     (notify-user "Resuming running of KB from where it last paused.")
     (system-resume))
    (pause
     (notify-user "Pause while running KB. You may resume, reset, or restart.")
     (system-pause))
    (start
     (notify-user "Starting to run KB. You may pause, reset, or restart at any time.")
     (system-start))
    (clear-kb
     ;; Consider notifying here.  Even though the logbook gets cleared, the
     ;; messages might be getting logged, and this seems to be an event worth
     ;; logging! (MHD 7/10/03)
     (clear-kb))
    #+development
    (t (cerror "Continue anyway." "Unknown action: ~s" action))))



(define-ui-command new-workspace ((class class-of-workspace) g2-window)
  "Create a new, top-level KB workspace"
  (when (and (g2-still-authorized-p)
             #+pre-g2-v5-licensing (not (runtime-option-authorized-p))
             #+pre-g2-v5-licensing (not (embedded-option-authorized-p)))
    (show-or-hide
      (if (eq class 'kb-workspace)
          (make-new-top-level-kb-workspace 'kb-workspace)
          (make-new-top-level-kb-workspace
            class nil nil nil
            (class-slot-description-value 'kb-workspace-initial-width class)
            (class-slot-description-value 'kb-workspace-initial-height class)
            (slot-init-form (slot-description-from-class
                              class 'module-this-is-part-of?))))
      t nil g2-window nil)))

(define-ui-command get-workspace ((workspace named-kb-workspace))
  "Choose an existing workspace and bring it to the top"
  (goto-frame-instance workspace))

(defun inspect-permitted-p ()
  #+runtime-functionality-without-a-license
  override-limited-license-block-on-inspect?
  #-runtime-functionality-without-a-license
  (or (not (g2-limited-to-this-license-level-or-more restricted-use))
      override-limited-license-block-on-inspect?))

(define-ui-command (inspect :dialog t) ()
  "Bring up the inspector window"
  (when (inspect-permitted-p)
    (handle-command 'inspect-command nil)))


;; The function `finish-executing-file-command' finally runs the command.
;; Notice how `handle-choice-for-directory-menu' does the same sort of dispatching.

(defun load-kb-permitted-p ()
  (not (or system-is-running inside-breakpoint-p)))


;; Calls: load-or-merge-kb-if-ok
(define-ui-command (load-kb :pretty-name "L&oad KB" :dialog t) ()
  "Load a KB"
  (when (load-kb-permitted-p)
    (handle-file-related-window-menu-choice 'load-kb)))

(define-ui-command (merge-kb :pretty-name "&Merge KB" :dialog t) ()
  "Merge a KB"
  (when (load-kb-permitted-p)
    (handle-file-related-window-menu-choice 'merge-kb)))

(define-ui-command (load-recent-kb :pretty-name "&Recent Files" :dialog t) ((pathname recent-loaded-kb))
  "Load a recent KB"
  (let ((default-kb-pathname? pathname))
    (handle-file-related-window-menu-choice 'load-kb)))

;; In the end calls (save-kb pathname type-of-file).


(defun save-kb-permitted-p ()
  (and (g2-authorized-p)
       #+pre-g2-v5-licensing
       (or (and (not (runtime-option-authorized-p))
                (not (embedded-option-authorized-p))) ; Added (jh, 12/20/91)
           (ok-kb-p))
       #+runtime-functionality-without-a-license
       nil
       #-runtime-functionality-without-a-license
       (not (g2-limited-to-this-license-level-or-more runtime))))

(define-ui-command (save-kb :pretty-name "&Save KB" :dialog t) ()
  "Save the current KB"
  (when (save-kb-permitted-p)
    (handle-file-related-window-menu-choice 'save-kb)))

;; ok-kb-p is meaningless with the arrival of text based ok files.


;; This means that regular save-kb ought to be "Save As..."
;; Still pops up the dialog if we don't have a default pathname.
;; TODO: Check clobbering existing file, especially if differing g2 version.

(define-ui-command (save-kb-without-asking :pretty-name "Save KB") ()
  (when (save-kb-permitted-p)
    (cond (current-kb-pathname?
           (save-kb (get-or-make-default-kb-pathname) 'kb-save))
          (t
           (handle-file-related-window-menu-choice 'save-kb)))))


(define-ui-command (show-system-table :name system-tables)
    (system-table original-x-in-window original-y-in-window)
  "Put up a chosen system table"
  (put-up-attributes-table system-table original-x-in-window original-y-in-window))


(define-ui-command (printer-setup :pretty-name "Printer Set&up") (window)
  "Put up the printer-setup table"
  (let ((x (halfr (+r (left-edge-of-window window) (right-edge-of-window window))))
        (y (halfr (+r (top-edge-of-window window) (bottom-edge-of-window window)))))
    ;; Where to put it?
    (declare (ignore y))
    (put-up-attributes-table printer-setup x 0)))


;; This guy is called from the menu. Should/could take all the args in that dialog.
;; (define-ui-command change-mode (user-name password user-mode window-class) ...)
;; Put all but the password into the transcript?

(define-ui-command (change-mode :dialog t) ()
  "Change the user mode of this window"
  (change-mode))

(define-ui-command (create-new-user-mode-alias :dialog t) ()
  "Create the new alias for the user mode"
  (enter-user-settings-editor 'alias-creation))
  
(define-ui-command user-mode-aliases ()
  "Show dialog with aliases table."
  (put-up-aliases-table (user-mode-aliases kb-configuration)))

(define-ui-command change-g2-user-mode ()
  "Change the user mode of this window"
  (when (not (frame-or-frames-with-this-name 'control-e))
    (change-mode)))

;; These guys are bound to the keystrokes.
(define-ui-command change-g2-user-mode-e ()
  "Change the user mode of this window"
  (when (frame-or-frames-with-this-name 'control-e)
    (change-mode)))

(define-ui-command change-password ()
  "Change the password for the current user in a secure G2 site."
  (when (and
          (g2-secure-p)
          (g2-user-name-for-this-workstation? current-workstation)
          (g2-user-password-for-this-workstation? current-workstation)
          g2passwdexe-is-executable-p
          #+obsolete (g2-ok-file-writeable-p)  ; see note
          #+obsolete (g2-ok-file-readable-p))
    (enter-change-password-dialog)))

;; Note: We had considered running the changes to the record of the
;; password from within G2 by incorporating the relevant parts of
;; g2passwd.c into the image. But we realized that it would violate
;; the model that only the administrator has write-permission on
;; the OK file and furthermore opened the gate to letting UUs vandalize
;; the file by using G2 writing operations.


(define-ui-command reinstall-authorized-users ()
  "Read in fresh copy of the G2 ok file, using it to define the current set of users and their passwords."
  (when (and
          (g2-secure-p)
          (g2-ok-file-readable-p))
    (reinstall-authorized-users)))


(define-ui-command short-menus ()
  (unless short-menus?
    (setq short-menus? t)))


(define-ui-command long-menus ()
  (when short-menus?
    (setq short-menus? nil)))


;; Really, neatly-stack-windows-image-planes?
(define-ui-command neatly-stack-windows (window)
  (when window
    (neatly-stack-image-planes-in-window window)))


(define-ui-command (connect-to-foreign-image :dialog t) ()
  "Connect G2 an external C or C++ program."
  (when (not system-is-running)
    (handle-file-related-window-menu-choice 'connect-to-foreign-image)))

(define-ui-command (disconnect-from-foreign-image :dialog t) ()
  "Disconnect G2 from an external C or C++ program."
  (when (not system-is-running)
    (handle-file-related-window-menu-choice 'disconnect-from-foreign-image)))

(define-ui-command (load-attribute-file :dialog t) ()
  "Loads a file that populates the attributes of existing items in the current KB, a superseded practice."
  (when (not system-is-running)
    (handle-file-related-window-menu-choice 'load-attribute-file)))

(define-ui-command (write-g2-stats :dialog t) ()
  "Write G2 memory usage statistics"
  (handle-file-related-window-menu-choice 'write-g2-stats))


(define-ui-command highlight-invoked-rules ()
  "Highlight rules when they are invoked"
  (when (not (highlight-invoked-rules-mode debugging-parameters))
    (change-slot-value debugging-parameters 'highlight-invoked-rules-mode t)))

(define-ui-command do-not-highlight-invoked-rules ()
  (when (highlight-invoked-rules-mode debugging-parameters)
    (change-slot-value debugging-parameters 'highlight-invoked-rules-mode nil)))

(define-ui-command enable-all-items ()
  (loop for frame being class-instances of 'block doing
    (when (manually-disabled-p frame)
      (funcall-method 'manually-enable frame))))

(define-ui-command remove-tracing-and-breakpoints ()
  (remove-tracing-and-breakpoints))


(define-ui-command update-file ()
  (handle-file-related-window-menu-choice 'source-code-control-update-file))

(define-ui-command edit-file ()
  (handle-file-related-window-menu-choice 'source-code-control-edit-file))

(define-ui-command unedit-file ()
  (handle-file-related-window-menu-choice 'source-code-control-unedit-file))

(define-ui-command commit-file ()
  (handle-file-related-window-menu-choice 'source-code-control-commit-file))

(define-ui-command revert-file ()
  (handle-file-related-window-menu-choice 'source-code-control-revert-file))


;; Behaves like a dialog.
(define-ui-command create-new-module (original-x-in-window original-y-in-window)
  (when
      #-pre-g2-v5-licensing t
      #+pre-g2-v5-licensing (and (not (runtime-option-authorized-p))
                                 (not (embedded-option-authorized-p)))
    (handle-create-new-module-window-menu-choice original-x-in-window original-y-in-window)))


(def-menu-string choose-a-module-to-delete "Choose A Module To Delete")

(define-ui-command delete-module ((module deletable-module))
  (when (and
          #+pre-g2-v5-licensing (not (runtime-option-authorized-p))
          #+pre-g2-v5-licensing (not (embedded-option-authorized-p))
          (kb-has-modularity-information-p)
          (not inside-breakpoint-p))
    (let ((system-table-suite? (get-system-table-suite-for-module-or-nil module)))
      (cond ((and system-table-suite?
                  ;; (not (system-table-installed-p (car system-table-suite?)))
                  )
             (enter-dialog
               (twith-output-to-text-string
                 (tformat
                   "Delete ~amodule ~a? (Choose `All' to delete all associated workspaces as well.)"
                   (if (system-table-installed-p (car system-table-suite?)) "the TOP-LEVEL " "")
                   module)
                 (tformat-warning-about-modules-that-require-this-if-necessary module))
               nil nil
               'do-deletion-of-module-after-confirmation
               (slot-value-list module nil)
               nil nil
               nil nil
               (tformat-text-string "All")
               'do-deletion-of-module-after-confirmation
               (slot-value-list module t)))))))

;; Old (3.0) text of dialog:
;;
;;    Are you sure you want to delete module <NAME> with
;;     associated system tables?
;;
;; Also, in 3.0 there was a restriction on deleting the installed system table.
;; That restriction is lifted in 4.0 -- now deleting the installed system table
;; causes the installed suite to be deleted -- ala Clear KB.  (MHD 8/12/94)


(define-ui-command new-title-block ()
  (display-credits current-workstation))

(define-ui-command shut-down-g2 ()
  ;; Before, offline? was checked only at execute-time, not at post-menu time.  -fmw, 9/21/93
  (when (or (not system-is-running) system-has-paused)
    (confirm-or-cancel
      (twith-output-to-text-string
        (tformat "Completely shut down G2?")
        (twrite-changed-modules-note))
      #'completely-shut-down-g2
      (slot-value-list 'requested))))


(defun completely-shut-down-g2 (&optional status)
  (notify-user "Shutdown!")
  (shut-down-ab-process status))


(define-ui-command (clear-kb :pretty-name "Clear KB") ()
  "Clear the current knowledge base"
  ;; In the miscellany menu, this did not include the system-has-paused disjunct for the menu,
  ;; but it did for the execution.
  (when (and (or (not system-is-running) system-has-paused)
             (not inside-breakpoint-p))
    ;; Make sure no use of old frames!
    (confirm-or-cancel
      (twith-output-to-text-string
        (tformat
          "Clear KB? (Are you sure you want to delete every item in ~
           the current KB and reinitialize system tables?)")
        (twrite-changed-modules-note))
      'system-state-change-from-scheduler
      (slot-value-list 'clear-kb))))


(define-ui-command turn-on-all-explanation-caching ()
  (when (explanation-related-features-enabled? miscellaneous-parameters)
    (turn-on-explanation-caching-for-all)))


(define-ui-command turn-off-all-explanation-caching ()
  (when (explanation-related-features-enabled? miscellaneous-parameters)
    (turn-off-explanation-caching-for-all)))

(define-ui-command network-info ()
  (put-up-table-of-network-info))


;; the following are for telewindow workstations only at present

(define-ui-command close-telewindows-connection ()
  (when (eq (type-of-gensym-window current-workstation-window) 'icp)
    (confirm-or-cancel (copy-text-string "Close this Telewindows connection to G2?")
                       #'close-telewindows-connection-1
                       (slot-value-list current-workstation-window))))

(defun close-telewindows-connection-1 (gensym-window)
  (notify-user "Closing Telewindows connection!")
  (close-telewindows-connection gensym-window))


(define-ui-command log-out ()
  "Log-out of G2."
  ;; You never have to log in (modally) in a non-secure G2.
  (when (g2-secure-p)
    (confirm-or-cancel (copy-text-string "Log out? (Are you sure?)")
                       #'log-out-workstation
                       (slot-value-list current-workstation))))


#+development
(define-ui-command memory-management-table ()
  (put-up-memory-management-table))

#+development
(define-ui-command telewindows-status-table ()
  (put-up-telewindows-status-table))

(define-ui-command (detect-deadlocks-for-ui :pretty-name "Detect Deadlocks") ()
  (detect-deadlocks-for-ui))

(define-ui-command (detect-and-break-deadlocks-for-ui :pretty-name "Detect and Break Deadlocks") ()
  (detect-and-break-deadlocks-for-ui))

(define-ui-command enter-package-preparation-mode ()
  (when (not package-preparation-mode)
    (confirm-or-cancel
      (tformat-text-string
        "Enter Package Preparation mode?  (This will add options to menus ~
         that allow for potentially dangerous and irreversible changes to the ~
         KB.)")
      'enter-package-preparation-mode)))


(define-ui-command leave-package-preparation-mode ()
  (when package-preparation-mode
    (leave-package-preparation-mode)))

(define-ui-command strip-texts-now ()
  (when (and package-preparation-mode
             (not system-is-running))
    (confirm-or-cancel
      (tformat-text-string
        "Strip texts now?  (This will permanently remove most of the text ~
         associated with all items that have been marked to be stripped of ~
         their text.  These changes will be irreversible.)")
      'strip-all-texts)))


(define-ui-command make-workspaces-proprietary-now ()
  (when (and package-preparation-mode
             (not system-is-running))
    (confirm-or-cancel
      (tformat-text-string
        "Make workspaces in this KB proprietary now?  (This will cause workspaces ~
         that have been given a potential proprietary package to become permanently ~
         proprietary to those packages and thus severely restricted in their use.  ~
         Once that has been done, this KB, or any KB that has merged in those workspaces, ~
         will only be allowed to execute with special authorization codes obtained ~
         through Gensym Corporation.  These changes will be irreversible.)")
      'make-proprietary-now)))


(defun-simple set-simulate-proprietary-mode (new-state)
  (setq simulate-proprietary? new-state)
  (inform-ui-client-interfaces-of-general-update
    'simulate-proprietary-mode-changed
    (if new-state evaluation-true-value evaluation-false-value)))

(define-ui-command enter-simulate-proprietary-mode ()
  (when (not simulate-proprietary?)
    (set-simulate-proprietary-mode t)))

(define-ui-command leave-simulate-proprietary-mode ()
  (when simulate-proprietary?
    (set-simulate-proprietary-mode nil)))


;;; The `abort' command will abort one workstation context in the current
;;; workstatation.  If already at top level it will refresh the screen.  This is
;;; installed as the handler for the abort event in the top level context.

;;; Some contexts override this behavior, presumably to allow a confirmation
;;; when you abort a complex edit.

;;; This is disabled if the current context happens to be modal.  That is
;;; a workaround for a problem with g2-login.

(define-ui-command abort ()
  (unless (type-of-modal-context? current-workstation)
    ;; do not allow abort from a modal context (this seems a little wierd,
    ;; I know; the use right now is to not allow users logging in to a
    ;; secure G2 from just "aborting" right into G2!) (MHD 6/26/91)
    (let ((at-the-top? (null (cdr (workstation-context-stack current-workstation)))))
      (abort-current-workstation-context type-of-current-workstation-context)
      (when at-the-top?
        (refresh-window current-workstation-window)))))

;; | Finally it calls `abort' and which throws the the symbol `ABORT-LEVEL-1'.
;; |
;; | Review and document the call to (abort 1) here! (MHD 10/27/89)
;; | Consider having an abort that goes all they way to the top again!! (MHD 10/27/89)

;; This used to call (ABORT 1) at the end, which jumped out of the following
;; stack frames:
;;   execute-ui-command <- execute-partial-command <- pursue-partial-command <-
;;   start-ui-command <- run-event-handler <- service-workstation <-
;;   service-workstations <- run-one-scheduler-cycle <-
;;   run-scheduler-for-current-system <- handle-event-internal
;; This was found to do nothing useful, and in fact caused bug HQ-1345000,
;; "Screen Refresh on CNTRL-A does not complete when G2 is paused."
;; Removed the call to abort.  -jv, 6/15/97


#+development
(defparameter raise-xemacs-window-on-break nil)

#+development
(defun raise-xemacs-window ()
  #+Lucid (lcl:shell "/home/ab/scripts/raise-emacs-window"))




#+development
(define-ui-command break (window &optional (frame? frame))
  (let ((exiting-normally? nil))
    (unwind-protect-for-development break
        (progn
          (when raise-xemacs-window-on-break
            (raise-xemacs-window))

          (run-break-loop window frame?)

          (when raise-xemacs-window-on-break
            (raise-application-window (native-window? window)))

          (setq exiting-normally? t))

      (when (not exiting-normally?)
        (unwind-current-workstation-back-to-top-level)))))




;;; The command `refresh' command refreshes the current window and all image
;;; planes.  This is the only way to get rid of graphics "turds", other than
;;; perhaps to move each image plane!

(define-ui-command refresh (window)
  (if (mdi-frame-p window)
      (mega-refresh window)                ; For 8.0 alpha: refresh MDI bg and non-client areas.
      (refresh-window window)))


(define-ui-command toggle-visible-grid (image-plane)
  (when (visible-grid-permitted-p image-plane)
    (toggle-visible-grid image-plane)))


(define-ui-command help (&optional (frame? frame))
  "Display a table of all keyboard commands, subject to the item-configuration
   relevant to the item under the mouse."
  (cond ((and (eq (type-of-workstation-context current-workstation-context) 'editing)
              (eq (special-entry-context?
                    specific-structure-for-current-workstation-context)
                  'special-character-entry))
         ;; In a special character entry context.
         ;; Shouldn't the editor just rebind HELP it its context?
         (put-up-special-character-help-workspace))
        ;; Will delete the former clause when the following clause is supported
        ;; by a robust help menu and we've switched incompatibly to the new
        ;; character insert mode. -pga, 5/2/95
        ((and (eq (type-of-workstation-context current-workstation-context) 'editing)
              (eq (special-entry-context?
                    specific-structure-for-current-workstation-context)
                  'insertion-of-symbol))
         ;; In a special character entry context.
         ;; Shouldn't the editor just rebind HELP in its context?
         (put-up-special-character-help-workspace))
        (t
         ;; else: do "usual help"
         (put-workspace-on-pane (make-help-workspace frame?)
                                current-workstation-detail-pane
                                'center 'center nil))))

(defun-simple get-validated-launch-help-procedure? ()
  (let* ((procedure-name 'g2-launch-online-help)
         (procedure
           (get-instance-with-name-if-any 'procedure procedure-name)))
    (cond
      ((null procedure)
       (warning-message* 1
           "The ~(~a~) procedure ~a does not exist."
         procedure-name)
       nil)

      ((not (eq (class procedure) 'procedure))
       (warning-message* 1
           "The launch-online-help procedure ~NF must be an ordinary procedure, not a ~(~A~)."
         procedure (class procedure))
       nil)

      ((not (runnable-p procedure))
       (warning-message* 1
           "The launch-online-help procedure ~NF ~
          is either inactive or has a status other than OK."
         procedure)
       nil)

      ;; Must be OK before we can get the arglist to check.
      ((not (argument-list-description-matches-template-p
              (argument-list-description procedure)
              '((class g2-window))))
       (warning-message* 1
           "The launch-online-help procedure ~NF's ~
          argument list is not (<window> :class g2-window)"
         procedure)
       nil)

      (t
       procedure))))


(define-ui-command (launch-online-help :pretty-name "Help")
    (workstation)
  (when (get-instance-with-name-if-any 'procedure 'g2-launch-online-help)
    (let* ((g2-window? (g2-window-for-this-workstation? workstation))
           (procedure?
             (get-validated-launch-help-procedure?))
           (arg-vector (allocate-managed-simple-vector 1)))
      (when (and g2-window? procedure?)
        (setf (svref arg-vector 0) g2-window?)
        (start-procedure-invocation-in-place
          procedure? 6 0 ; proc priority wait
          arg-vector 0 1
          nil nil nil nil nil))
      (reclaim-managed-simple-vector arg-vector))))

#+development
(defun make-simple-text-cell-for-string (string &optional format)
  (make-text-cell (slot-value-list (copy-text-string string)) (or format 'help-key-binding-format)))


#+development
(define-ui-command show-all-ui-commands ()
  "Someday, this will be a scrolling Excel-like key bindery"
  (let* ((rows (loop for command in (sort (copy-list list-of-all-ui-commands) #'string-lesspw
                                          :key #'(lambda (cmd) (stringw (ui-command-name cmd))))
                     as doc? = (ui-command-documentation command)
                     as key-pattern? = (lookup-command-in-context-stack
                                         (ui-command-name command))
                     collect (nconc
                               (slot-value-list (make-simple-text-cell-for-string
                                                  (stringw (ui-command-menu-name command))))
                               (slot-value-list
                                 (make-simple-text-cell-for-string
                                   (if key-pattern?
                                       (twith-output-to-text-string
                                         (twrite-string "(")
                                         (twrite-key-pattern key-pattern?)
                                         (twrite-string ")"))
                                       " ")))
                               (when doc?
                                 (slot-value-list
                                   (make-simple-text-cell-for-string doc?))))
                       using slot-value-cons))
         (title (slot-value-list nil nil (make-simple-text-cell-for-string
                                           "User Interface Commands"
                                           'help-title-format)))
         (table (make-or-reformat-table
                  (slot-value-cons title rows)
                  'help-table-format nil nil t))
         (workspace (make-workspace 'temporary-workspace nil table 10)))
    (put-workspace-on-pane workspace current-workstation-detail-pane
                           'center 'center nil)))




;;;; Stacking order commands and system procedures.



(define-ui-command circulate-up (pane)
  (circulate-up pane))



(define-ui-command circulate-down (pane)
  (circulate-down pane))

;; Circulate Up (CircUp) is X Windows name for analog of this function.
;; Pop-bottom-image-plane-up-to-top was the user-visible name (i.e., in the
;; help table) until today.  Similarly for circulate-down, which had been
;; push-top-image-plane-down-to-bottom until today.  (MHD 6/21/91)




;;; These two commands operate on image planes.  define-ui-command makes some
;;; attempt to validate the image-planes, via valid-image-plane-p (itself a
;;; hack).

(define-ui-command (lift-to-top :pretty-name "Lift to Top") (image-plane)
  (raise-image-plane-to-top image-plane))

(define-ui-command (drop-to-bottom :pretty-name "Drop to Bottom") (image-plane)
  (lower-image-plane-to-bottom image-plane))


;;; These commands operate on something with a visible representation upon a KB
;;; workspace.  Things with a visible representation are entities and graphs
;;; (and friends).  We restrict them to KB workspaces on the notion that non-kb
;;; workspaces are not "editable" by the user.

(defun entity-like-p (block)
  (or
    (entity-p block)
    ;; Charts are not entities.
    (frame-of-class-p block 'chart)
    (frame-of-class-p block 'trend-chart)
    (frame-of-class-p block 'graph)
    ;; Neither are readout-tables
    (frame-of-class-p block 'readout-table)
    ;; Nay, neither are freeform-tables.
    (frame-of-class-p block 'freeform-table)
    ;; Neither are text boxes. But only some want to get the lifting menu.
    (frame-of-class-p block 'free-text)
    (frame-of-class-p block 'borderless-free-text)
    (frame-of-class-p block 'statement)                            ; Function defns, etc.
    (frame-of-class-p block 'message)
    (frame-of-class-p block 'scrap)))


(defun block-is-upon-kb-workspace? (block)
  (let ((workspace? (superblock? block)))
    (and workspace? (kb-workspace-p workspace?))))



(define-ui-command (lift-item-to-top :name lift-to-top)
    ((frame frame-for-selection))
  (when (and (block-p frame)
             (entity-like-p frame)
             (block-is-upon-kb-workspace? frame))
    (raise-block-to-top frame)))

(define-ui-command (drop-item-to-bottom :name drop-to-bottom)
    ((frame frame-for-selection))
  (when (and (block-p frame)
             (entity-like-p frame)
             (block-is-upon-kb-workspace? frame))
    (lower-block-to-bottom frame)))



;;; The defun-for-system-procedure `g2-lift-item-to-top', if item is a
;;; workspace, or is not on a workspace, it does nothing.

(defun-for-system-procedure g2-lift-item-to-top (block)
  (declare (keeps-g2-local-variables-valid t))
  (cond ((workspace-p block)
;         (loop for image-plane in (image-planes-this-is-on block) doing
;           (raise-image-plane-to-top image-plane))
         nil)
        (t
         (raise-block-to-top block))))

(define-system-rpc-access (g2-lift-item-to-top ())
    ((item (class item)))
  (g2-lift-item-to-top item))


(defun-for-system-procedure g2-drop-item-to-bottom (block)
  (declare (keeps-g2-local-variables-valid t))
  (cond ((workspace-p block)
;         (loop for image-plane in (image-planes-this-is-on block) doing
;           (lower-image-plane-to-bottom image-plane))
         nil)
        (t
         (lower-block-to-bottom block))))

(define-system-rpc-access (g2-drop-item-to-bottom ())
    ((item (class item)))
  (g2-drop-item-to-bottom item))


;; Removed unnecessary/wrong behavior of working on image planes in the
;; workspace case, per conversations with fmw & dwr. (MHD 8/11/94)


;;; The defun-for-system-procedure `g2-lift-item-to-front' brings block-1 in
;;; front of block-2 in the stacking order, regardless of whether or not
;;; block-1 and block-2 overlap.  They must, however, live on the same
;;; workspace, and not already be in that order.  The user-visible system
;;; procedure for this is called `g2-lift-item-in-front-of'.

(defun-for-system-procedure g2-lift-item-to-front (block-1 block-2)
  (declare (keeps-g2-local-variables-valid t))
  (order-blocks block-1 block-2 nil))

(define-system-rpc-access (g2-lift-item-in-front-of ())
    ((item-1 (class item))
     (item-2 (class item)))
  (g2-drop-item-to-back item-1 item-2))


;;; The defun-for-system-procedure `g2-drop-item-to-back' sends block-1 behind
;;; block-2 in the stacking order, regardless of whether or not block-1 and
;;; block-2 overlap.  They must, however, live on the same workspace, and not
;;; already be in that order. The user-visible system procedure is called
;;; `g2-drop-item-behind'.

(defun-for-system-procedure g2-drop-item-to-back (block-1 block-2)
  (declare (keeps-g2-local-variables-valid t))
  (order-blocks block-1 block-2 t))

(define-system-rpc-access (g2-drop-item-behind ())
    ((item-1 (class item))
     (item-2 (class item)))
  (g2-drop-item-to-back item-1 item-2))

;; Should these system procedures do anything when handed workspaces?
;; Other names:
;;   g2-send-to-back <item/A>
;;   g2-bring-to-front <item/A>
;;   g2-send-behind-if-necessary <item/a> <item/b>
;;   g2-bring-in-front-if-necessary <item/a> <item/b>



;;; The function `g2-get-item-layer-position' returns the index of the item in
;;; the list of all items its workspace.  The index of the topmost item is
;;; defined to be 0, as is the index of an item which is not upon any workspace
;;; (which includes workspaces themselves).

(defun-for-system-procedure g2-get-item-layer-position ((item item))
  (declare (values integer)
           (keeps-g2-local-variables-valid t))
  (compute-user-visible-layer-position-of-item item))

(define-system-rpc-access (g2-get-item-layer-position (integer))
    ((item (class item)))
  (g2-get-item-layer-position item))

;; For now, this is the same as the position of the item in the subblock list,
;; but that could change in the future.  For example, from the user's point of
;; view, the layer numbers are not consecutive since they include non-items
;; such as name boxes and attribute displays.

;; Actually, this "fails" for any non-top-level workspace subblocks, including
;; user-visible ones such as connections!!

;; The fact that this returns 0 for topmost, rather than for bottommost,
;; was an unfortunate and random decision.




;;; The defun-for-system-procedure `g2-last-input-event' returns the last input
;;; event as a symbol, suitable for parsing by the object configuration
;;; grammar.
;;;
;;;
;;; If g2-window is not "live" (connected as a local window or via Telewindows),
;;; this signals an error with an appropriate error message.
;;;
;;; This assumes that g2-window is already known to be of class G2-WINDOW (i.e.,
;;; having been checked by the calling system procedure), and that G2-WINDOW is
;;; not a subclass of UI-CLIENT-SESSION.

(defun-for-system-procedure g2-last-input-event ((g2-window item))
  (declare (values symbol)
           (keeps-g2-local-variables-valid t))
  #+development (assert (of-class-p g2-window 'g2-window))
  (let ((workstation? (workstation-for-g2-window? g2-window)))
    (cond
      ((null workstation?)
       (ui-stack-error-for-non-connected-window 'g2-window 'g2-last-input-event))
      (t
       (let* ((mouse-pointer (mouse-pointer-of-last-interesting-event workstation?))
              (key-code (key-code-of-mouse-pointer mouse-pointer)))

         ;; We want to return a symbol which the user can stuff directly into an
         ;; item-configuration.  Probably should have made it a string.

         (cond ((illegal-key-code-p key-code)
                'unknown)
               (t
                (or (parseable-symbol-from-key-code key-code)
                    'unknown))))))))

;; Should this skip mouse-motion events?  Yes.
;; Should this backtranslate mouse-select, mouse-drag?  Yes. No?

;; Should we be returning NIL?
;; -- UPDATE: NO! (See comments after next system procedure!) (MHD 6/18/99)

;; Should this return multiple values (event-name x y timestamp)?



;;; Helper functions for g2-last-input-event-info system procedure.

(defmacro virtual-x-in-workspace (x-in-window image-plane)
  (avoiding-variable-capture (image-plane)
    `(delta-x-in-workspace
       (-r ,x-in-window
           (x-origin-of-workspace-in-window-of-image-plane ,image-plane))
       (image-x-scale ,image-plane))))

(defmacro virtual-y-in-workspace (y-in-window image-plane)
  (avoiding-variable-capture (image-plane)
    `(delta-y-in-workspace
       (-r ,y-in-window
           (y-origin-of-workspace-in-window-of-image-plane ,image-plane))
       (image-y-scale ,image-plane))))


;;; The function `gensym-window-point-to-user-window-point' returns the point
;;; specified by (x-in-window, y-in-window) for gensym-window as a point in
;;; "user-window-coordinate" terms, i.e., with respect to the main ("detail")
;;; pane, and with y positive in the up direction instead of the down.

(defun gensym-window-point-to-user-window-point
    (gensym-window x-in-window y-in-window)
  (let ((image-plane
          (car (stack-of-image-planes
                 (detail-pane gensym-window)))))
    (values
      (-r x-in-window
          (halfr (+r (left-edge-of-pane-in-window image-plane)
                     (right-edge-of-pane-in-window image-plane))))
      (-r (-r y-in-window
           (halfr (+r (top-edge-of-pane-in-window image-plane)
                      (bottom-edge-of-pane-in-window image-plane))))))))




;;; The defun-for-system-procedure `g2-last-input-event-info' returns as
;;; multiple values information beyond that available from g2-last-input-event.
;;;
;;; The return values are as follows:
;;;
;;;   (1) last-event - a symbol describing the last keyboar or mouse event;
;;;   (2) valid-item-p - a truth-value that's true iff the mouse was over
;;;         a "valid" item;
;;;   (3) window-x - an integer, the x position of the mouse in user
;;;         window coordinates;
;;;   (4) window-y - an integer, the y position of the mouse in user
;;;         window coordinates;
;;;   (5) timestamp - an integer, the time the event occurred;
;;;   (6) x-in-workspace - an integer, if valid-item-p, x in user workspace
;;;        coordinates, otherwise 0;
;;;   (7) y-in-workspace - an integer, if valid-item-p, y in user workspace
;;;        coordinates, otherwise 0
;;;   (8) mouse-button - a symbol, LEFT, MIDDLE, RIGHT, or NONE.
;;;       Added on 1997/05/07 by vkp but not bothered to document it.
;;;
;;; If g2-window is not "live" (connected as a local window or via Telewindows),
;;; this signals an error with an appropriate error message.
;;;
;;; This assumes that g2-window is already known to be of class G2-WINDOW (i.e.,
;;; having been checked by the calling system procedure), and that G2-WINDOW is
;;; not a subclass of UI-CLIENT-SESSION.

(defun-for-system-procedure g2-last-input-event-info ((g2-window item))
  (declare (values symbol truth-value integer integer integer integer integer symbol)
           (keeps-g2-local-variables-valid t))
  #+development (assert (of-class-p g2-window 'g2-window))
  (let ((workstation? (workstation-for-g2-window? g2-window)))
    (cond
      ((null workstation?)
       (ui-stack-error-for-non-connected-window 'g2-window 'g2-last-input-event-info))
      (t
       (let* ((mouse-pointer (mouse-pointer-of-last-interesting-event workstation?))
              (key-code (key-code-of-mouse-pointer mouse-pointer))
              (mouse-button (make-evaluation-symbol
                              (if (mouse-key-code-p key-code)
                                  (mouse-button-of-last-activity workstation?)
                                  'none)))
              (last-event-symbol
                (or (if (not (illegal-key-code-p key-code))
                        (parseable-symbol-from-key-code key-code))
                    'unknown)))
         (with-mouse-pointer-bindings
             (x-in-window y-in-window timestamp
                          &optional
                          (image-plane? image-plane))
             mouse-pointer
           (multiple-value-bind (user-window-x user-window-y)
               (gensym-window-point-to-user-window-point
                 (window-for-workstation workstation?)
                 x-in-window y-in-window)
             (values
               last-event-symbol
               (if image-plane? truth falsity)
               user-window-x user-window-y
               timestamp
               (if image-plane?
                   (virtual-x-in-workspace x-in-window image-plane?)
                   0)
               (if image-plane?
                   (-w (virtual-y-in-workspace y-in-window image-plane?))
                   0)
               mouse-button))))))))

;; Note: the error handling behavior in the above two system procedures is new
;; for release currently pending. Previously, it returned bogus results,
;; resulting in a runtime warning about bad internal data and that the user
;; should report this to Gensym.  They previously returned Lisp NIL when not
;; connected, and not all of their values in the case of the above function, and
;; the procedure/system-procedure mechanism cannot really deal with those kinds
;; of things. (MHD 6/18/99)

(defun-for-system-procedure g2-refresh-image-definition ((image-definition item))
  (declare (keeps-g2-local-variables-valid t))
  #+development (assert (of-class-p image-definition 'image-definition))
  (refresh-image-definition-from-file image-definition))




;;; The function `transfer-items-to-mouse-of-window' is called (indirectly) by
;;; the "transfer item to mouse of window" action and by the
;;; g2-transfer-list-contents and related system procedures to transfer or move
;;; an item or a list of items with the mouse pointer of the window
;;; corresponding to g2-window.
;;;
;;; Item-or-items should be either a single item or a list or items.  In the
;;; list case the conses are not reclaimed or incorporated by this function.
;;;
;;; It is called in an evaluation context, so we have to explictly enter into a
;;; workstation context.  If there is no workstation corresponding to g2-window,
;;; meaning the window is not connected and logged in, this does not enter any
;;; context, but fails silently.
;;;
;;; It is defined here, rather that in entities, to pick up the workstation
;;; macros.
;;;
;;; If the optional third argument image-plane-if-move-case? is non-nil, it
;;; should be an image plane showing in the window corresponding to g2-window,
;;; and in that case this enters a move-style dragging context with movement of
;;; the items restricted to that image plane, rather than entering a
;;; transfer-style context.  This is primarily intended to be used by
;;; move-items-to-mouse-of-window.
;;;
;;; The function `transfer-item-to-mouse-of-window' (singular "item") is the old
;;; API function name, here for compatibility with old callers.  It just passes
;;; its args along to transfer-items-to-mouse-of-window.  It doesn't take the
;;; optional third arg.
;;;
;;; The function `move-items-to-mouse-of-window' is similar to
;;; transfer-items-to-mouse-of-window, but enters a move-style dragging context
;;; instead of a transfer style.

(defun transfer-items-to-mouse-of-window
    (item-or-items g2-window &optional image-plane-if-move-case?)
  ;; Notice that we do not check any restrictions here.
  ;; See the comments about release 2.1 in the transfer instruction (STACK-ACTS).
  (let ((workstation? (workstation-for-g2-window? g2-window)))
    (when workstation?
      (for-workstation (workstation?)
        (let ((block-or-blocks
                (if (atom item-or-items)
                    item-or-items
                    (copy-list-using-dragging-conses item-or-items))))
          (if image-plane-if-move-case?
              (enter-move-dragging-context
                block-or-blocks 0 0 image-plane-if-move-case?)
              (enter-transfer-dragging-context block-or-blocks)))))))


(defun transfer-item-to-mouse-of-window (item g2-window)
  (transfer-items-to-mouse-of-window item g2-window))


(defun move-items-to-mouse-of-window (item-or-items g2-window image-plane)
  (transfer-items-to-mouse-of-window item-or-items g2-window image-plane))




(defun system-procedure-argument-list-error
       (argument-name procedure-name class supplied-value)
  (write-stack-error cached-top-of-stack
    (tformat "The ~a" argument-name)
    (tformat
      " argument of ~a is declared to take values of class ~
       ~a, but instead it received "
      procedure-name
      class)
    (cond ((framep supplied-value)
           (tformat "~NF, an instance of the class ~a."
                    supplied-value
                    (class supplied-value)))
          (t
           (write-stored-value supplied-value)
           (twrite-character #.%\.)))))

;; Stolen from procedure-argument-list-error.




;;; `UI-stack-error-for-non-connected-window' calls stack error and gives an
;;; error message that the <argument-name> argument of <procedure-name> must be
;;; a connected window.

(defun ui-stack-error-for-non-connected-window
    (argument-name procedure-name)
  (ui-stack-error "The ~a argument of ~a must be a connected window."
                  argument-name ; e.g., G2-WINDOW
                  procedure-name ; e.g., G2-SYSTEM-COMMAND
                  ))


;;;; Editor Utilities


(def-type-parameter launch-editor-options-type
    (structure ((attribute symbol)
                (line integer)
                (column integer)
                (exclude (sequence (or symbol text)))
                (preferred-editor (member classic native))
                (grammar (or symbol (structure ((class symbol)
                                                (attribute symbol)
                                                (defining-class symbol)))))
				;; Added by SoftServe
                (toolbar (sequence (structure ((toolbar-id integer)
                                               (toolbar-text text)))))
                (toolbar-callback-function symbol)
				;; End of SoftServe changes
                (title text)
                (semaphore (class symbolic-parameter)))))

;;; The function `slot-denotation-of-editable-slot-or-stack-error' returns the
;;; slot-denotation for the given attribute of item, if that attribute is
;;; programmatically editable, subject to the current restrictions on given
;;; workstation. Otherwise, it signals a stack-error with an explanation.

(defun slot-denotation-of-editable-slot-or-stack-error (item attribute-name workstation)
  (let ((current-g2-user-mode?
          (g2-user-mode-for-this-workstation? workstation))
        (slot-denotation?
          (unmangle-slot-component-alias
            (parse-slot-name-denotation attribute-name item))))

    (cond ((or (null slot-denotation?)
               (null
                 ;; This is what enter-editing-context requires.
                 (get-slot-description-of-frame
                   (unqualified-name slot-denotation?)
                   item
                   (class-qualifier slot-denotation?))))
           (ui-stack-error "The attribute named ~a was not found." attribute-name))

          ;; Don't allow these beasts!
          ((compound-slot-descriptor (unqualified-name slot-denotation?))
           (ui-stack-error "Component attributes of a ~a, such as ~a, ~
                                    may not be edited programmatically."
                           (class item) attribute-name))

          ((not (get-slot-description-if-editable-attribute
                  item
                  (alias-slot-name-if-necessary
                    (unqualified-name slot-denotation?)
                    (class-qualifier slot-denotation?))
                  (class-qualifier slot-denotation?)))
           (ui-stack-error "The editing of attribute ~a of ~NF is restricted."
                           attribute-name item))

          ((not (editable-slot-p item
                                 (unqualified-name slot-denotation?)
                                 (class-qualifier slot-denotation?)
                                 nil))
           ;; Grammar or semantic checks failed.
           (ui-stack-error "The attribute ~a of ~NF may not be edited."
                           attribute-name item))

          (t
           slot-denotation?))))


;;; The function `launch-editor-1' launches a classic or native editor on the
;;; given workstation, editing the given slot. Ignores restrictions, etc.

(defun launch-editor-1 (item slot-denotation workstation &optional
                             line? character? type-of-slot? symbolic-parameter?
                             ;; Added by SoftServe
                             modal size-x size-y pos-x pos-y)
  (let* ((workspace?
           (get-workspace-if-any item))
         (image-plane?
           (and workspace?
                (image-plane-of-workspace-on-workstation workstation workspace?))))
    (for-workstation (workstation)
      (cond (symbolic-parameter?
             (with-editor-return-value (symbolic-parameter?)
               (launch-editor-2 item slot-denotation image-plane? line? character? type-of-slot?
                                ;; Added by SoftServe
                                modal size-x size-y pos-x pos-y)))
            (t
             (launch-editor-2 item slot-denotation image-plane? line? character? type-of-slot?
                              ;; Added by SoftServe
                              modal size-x size-y pos-x pos-y))))))

(defun launch-editor-2 (item slot-denotation image-plane? line? character? type-of-slot? 
                             ;; Added by SoftServe
                             modal size-x size-y pos-x pos-y)
  ;; Allow for in-place editing by calling the
  ;; routine for text-boxes.  Cells of attribute
  ;; tables may also be edited in-place, but I don't
  ;; think that the user can hand us one of
  ;; them. -fmw, 5/19/95
  (cond ((and (frame-of-class-p item 'text-box)
              (eq (unqualified-name slot-denotation)
                  'box-translation-and-text)
              image-plane?)
         (enter-editing-context-on-text-box item image-plane? nil nil
                                            line? character? type-of-slot?))
        (t
         (enter-editing-context item slot-denotation nil nil nil nil
                                line? character?
                                nil nil nil nil nil nil type-of-slot?
                                nil nil nil nil nil nil nil nil nil
                                ;; Added by SoftServe
                                modal size-x size-y pos-x pos-y))))

;  (type-of-exit-from-edit-context? nil)                ; NIL, TAB-EXIT, END-EXIT, or CANCEL-EXIT

;; Other options: rectangle, colors, fonts, buttons, automatic-prompting-p,
;; native-or-classic-or-default, etc.

;; Added by SoftServe
(defun processed-editor-toolbar (toolbar-buttons)
  (loop for button being each evaluation-sequence-element of toolbar-buttons
        do
        (let* ((toolbar-component-id (evaluation-structure-slot button 'toolbar-id))
               (toolbar-component-text (evaluation-structure-slot button 'toolbar-text)))
          (manage-native-editor editor-window-handle
                                editor-add-toolbar-button
                                toolbar-component-text
                                toolbar-component-id))))

(defvar editor-toolbar-user-callback nil)
;; End of SoftServe changes

(defun-for-system-procedure g2-ui-close-current-editor (apply-changes? g2-window)
  (let* ((apply-changes-p (evaluation-truth-value-is-true-p apply-changes?))
         (gensym-window   (map-to-gensym-window-or-stack-error g2-window))
         (workstation     (workstation-this-is-on gensym-window))
         (edit-state      (or (find-current-edit-state workstation)
                              (ui-stack-error "There is no editor open on ~NF." g2-window)))
         (native-window?  (when (native-editor-p gensym-window)
                            (native-editor-window edit-state))))
    (for-workstation (workstation)
      (in-editing-context (edit-state)
        (setf (being-autoclose-with-system-procedure? current-edit-state) t)
        (cond (native-window?
               (if apply-changes-p
                   (manage-native-editor native-window? editor-exit-new)
                 (manage-native-editor native-window? editor-cancel)))
              (t
               (if apply-changes-p
                   (end-editing)
                 (unless (end-editing)
                   (setf (never-confirm-cancelled-edit? current-edit-state) t)
                   (cancel-editing)))))))))

(defun-for-system-procedure g2-ui-launch-editor-extended ((item item)
                                                 (options structure)
                                                 ;; Added by SoftServe
                                                 (modal truth-value)
						 (size-x integer)
						 (size-y integer)
						 (pos-x integer)
						 (pos-y integer)
                                                 ;; End of SoftServe changes
                                                 (g2-window item))
  (unless (workstation-for-g2-window? g2-window)
    (ui-stack-error-for-non-connected-window 'g2-window 'g2-ui-launch-editor))
  ;; Added by SoftServe
  (cond ((eq modal truth)
         (setq modal t))
        ((eq modal falsity)
         (setq modal nil)))
  ;; End of SoftServe changes
  (check-type-or-stack-error options launch-editor-options-type)
  (let* ((workstation
           (workstation-for-g2-window? g2-window))
         ;; Added by SoftServe
         (toolbar-buttons
           (evaluation-structure-slot options 'toolbar))
         (toolbar-callback
           (evaluation-structure-slot options 'toolbar-callback-function))
         ;; End of SoftServe changes
         (attribute
           (evaluation-structure-slot options 'attribute 'text))
         (slot-denotation
           (slot-denotation-of-editable-slot-or-stack-error item attribute workstation))
         (type-of-slot?
           (compute-type-of-slot-or-stack-error
             (evaluation-structure-slot options 'grammar)))
         (symbolic-parameter?                ; Where to conclude status. For internal use only.
           (evaluation-structure-slot options 'semaphore))
         (line?
           (evaluation-structure-slot options 'line 1))
         (column?
           (evaluation-structure-slot options 'column 0))
         (editor-prompt-filter?         ; Special variable
           (parse-editor-prompt-filter
             (evaluation-structure-slot options 'exclude))) ; TODO: better slot name?
         (override-preferred-editor        ; Special variable
           (evaluation-structure-slot options 'preferred-editor))
         (editor-caption-text-override?
           (evaluation-structure-slot options 'title)))
    (launch-editor-1 item slot-denotation workstation line? column? type-of-slot? symbolic-parameter?
    ;; Added by SoftServe
                     modal size-x size-y pos-x pos-y)
    (when (and (evaluation-sequence-p toolbar-buttons)
               (not (evaluation-sequence-empty-p toolbar-buttons)))
      (processed-editor-toolbar toolbar-buttons))
    (when toolbar-callback
      (setf editor-toolbar-user-callback (stored-callback-procedure toolbar-callback)))
     ;; End of SoftServe changes
    (reclaim-evaluation-structure options)
    evaluation-true-value))

;added by SoftServe    

;; Added by Kvazar-Micro
(defun-for-system-procedure g2-ui-launch-editor ((item item)
                                                 (options structure)
                                                 (g2-window item))
  (unless (workstation-for-g2-window? g2-window)
    (ui-stack-error-for-non-connected-window 'g2-window 'g2-ui-launch-editor))

  (check-type-or-stack-error options launch-editor-options-type)
  (let* ((workstation
           (workstation-for-g2-window? g2-window))
         (attribute
           (evaluation-structure-slot options 'attribute 'text))
         (slot-denotation
           (slot-denotation-of-editable-slot-or-stack-error item attribute workstation))
         (type-of-slot?
           (compute-type-of-slot-or-stack-error
             (evaluation-structure-slot options 'grammar)))
         (symbolic-parameter?                ; Where to conclude status. For internal use only.
           (evaluation-structure-slot options 'semaphore))
         (line?
           (evaluation-structure-slot options 'line 1))
         (column?
           (evaluation-structure-slot options 'column 0))
         (editor-prompt-filter?         ; Special variable
           (parse-editor-prompt-filter
             (evaluation-structure-slot options 'exclude))) ; TODO: better slot name?
         (override-preferred-editor        ; Special variable
           (evaluation-structure-slot options 'preferred-editor))
         (editor-caption-text-override?
           (evaluation-structure-slot options 'title)))
    (launch-editor-1 item slot-denotation workstation line? column? type-of-slot? symbolic-parameter?)
    (reclaim-evaluation-structure options)
    evaluation-true-value))
	
;; End of Kvazar-Micro changes

(defvar edit-states nil)
(defvar highest-state-index 0)
(defconstant maximum-open-editors 4096) 

(defun-for-system-procedure g2-ui-launch-editor-returning-handle ((item item)
                                                 (options structure)
                                                 (g2-window item))
(declare (values integer))												 
(unless (workstation-for-g2-window? g2-window)
    (ui-stack-error-for-non-connected-window 'g2-window 'g2-ui-launch-editor))
  (check-type-or-stack-error options launch-editor-options-type)
  (let* ((workstation
           (workstation-for-g2-window? g2-window))
         (attribute
           (evaluation-structure-slot options 'attribute 'text))
         (slot-denotation
           (slot-denotation-of-editable-slot-or-stack-error item attribute workstation))
         (type-of-slot?
           (compute-type-of-slot-or-stack-error
             (evaluation-structure-slot options 'grammar)))
         (symbolic-parameter?                ; Where to conclude status. For internal use only.
           (evaluation-structure-slot options 'semaphore))
         (line?
           (evaluation-structure-slot options 'line 1))
         (column?
           (evaluation-structure-slot options 'column 0))
         (editor-prompt-filter?         ; Special variable
           (parse-editor-prompt-filter
             (evaluation-structure-slot options 'exclude))) ; TODO: better slot name?
         (override-preferred-editor        ; Special variable
           (evaluation-structure-slot options 'preferred-editor))
         (editor-caption-text-override?
           (evaluation-structure-slot options 'title))
		 (new-edit-state nil)) ;added by SoftServe
	(setq new-edit-state	 
		(launch-editor-1 item slot-denotation workstation line? column? type-of-slot? symbolic-parameter?))
	(reclaim-evaluation-structure options)
	;will be initialized on first function call
	(when (null edit-states)
		(setq edit-states (allocate-managed-simple-vector maximum-open-editors))
		(loop for i from 0 to (- maximum-open-editors 1) do 
			(if edit-states (setf (svref edit-states i) nil))  ;;change it for the gensym-1086
		))
	(if (>=f highest-state-index maximum-open-editors)
        (setq highest-state-index 0)
		(loop until (null (svref edit-states highest-state-index)) do
		  (incff highest-state-index)
		  (when (>=f highest-state-index (- maximum-open-editors 1))
			(setq highest-state-index 0))
		 )
	)	
	(setf (svref edit-states highest-state-index) new-edit-state)
	highest-state-index)
)												 

(defun-for-system-procedure g2-ui-finish-editing-session ((editor-handle integer) (g2-window item))
    (declare (values truth-value)) 
    (let ((ws (workstation-for-g2-window? g2-window))
	      (es nil) (retval nil) 
	     )
		(when (and (>f maximum-open-editors editor-handle) (>=f editor-handle 0) )
		 (setq es (svref edit-states editor-handle))) 
	   (unless (null es)
	    (for-workstation (ws)
		 (in-editing-context (es)
			(setq retval (extend-parsing-as-appropriate 'end))
			(when retval (setf (svref edit-states editor-handle) nil))
		 )
		)
	   )
	retval   
))
;end of SoftServe changes
	
(defun compute-type-of-slot-or-stack-error (grammar)
  (multiple-value-bind (class? attribute? defining-class?)
      (cond ((evaluation-symbol-p grammar)
             (values grammar 'text nil)) ; TODO: Maybe use parse-slot-name-denotation
            ((evaluation-structure-p grammar)
             (values (evaluation-structure-slot grammar 'class)
                     (evaluation-structure-slot grammar 'attribute 'text)
                     (evaluation-structure-slot grammar 'defining-class))))
    (when class?
      (coerce-to-free-text-type-of-slot
        (or (get-type-of-slot-for-user-edit class? attribute? defining-class?)
            (write-stack-error cached-top-of-stack
              (tformat "The grammar specification ~NV in invalid" grammar)
              (cond ((null (class-description class?))
                     (tformat " because ~A is not a known class" class?))
                    ((null (get-slot-description-of-class-description
                             attribute? (class-description class?)))
                     (tformat " because ~A is not an attribute of ~A" attribute? class?)))
              (tformat ".")))))))

(defun parse-editor-prompt-filter (filter)
  (when (evaluation-sequence-p filter)
    (loop for element being each evaluation-sequence-element of filter
          as result? = (cond ((evaluation-symbol-p element)
                              (gensym-list (evaluation-symbol-symbol element)))
                             ((evaluation-text-p element)
                              (read-symbol-list-from-text-string
                                (evaluation-text-value element))))
          when result?
            collect it using gensym-cons)))

(defun read-symbol-list-from-text-string (text-string)
  (loop with token?
        with type-of-token?
        with next?
        as start? = 0 then next?
        do (multiple-value-setq (token? type-of-token? next?)
             (read-from-text-string text-string start?))
        while token?
        if (symbolp token?)
          collect token? using gensym-cons
        else
          (reclaim-slot-value token?)))

(defun-for-system-procedure g2-ui-get-text-from-current-editor (g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (workstation (workstation-this-is-on gensym-window))
         (edit-state (or (find-current-edit-state workstation)
                         (ui-stack-error "There is no edit in progress on ~NF ~NF." g2-window workstation)))
         (edit-text (text-being-edited edit-state)))
    (convert-text-to-text-string edit-text)))


(defun-for-system-procedure g2-ui-insert-text-into-current-editor (text options g2-window)
  (let* ((gensym-window (map-to-gensym-window-or-stack-error g2-window))
         (workstation (workstation-this-is-on gensym-window))
         (edit-state (or (find-current-edit-state workstation)
                         (ui-stack-error "There is no edit in progress on ~NF." g2-window))))
    (for-workstation (workstation)
      (in-editing-context (edit-state)
        (insert-text-string-at-cursor text nil nil)))
    (reclaim-evaluation-text text)
    (reclaim-evaluation-value options)))

(defun find-current-edit-state (workstation)
  (for-workstation (workstation)
    (loop for ws in (workstation-context-stack workstation)
          as state = (specific-structure-for-workstation-context ws)
          when (and (valid-workstation-context-p state)
                    (edit-state-p state))
            return state)))

;;;; Do system command (preliminary)



;;; The function `g2-system-command' runs the given menu command as if it were
;;; clicked upon in the workstation of the given window.  The item and the
;;; attribute-name are the arguments to the command, as needed.  The command is
;;; run in the context of the specific workstation, but if the user-mode of the
;;; window is nil, it is simulated as administrator, in which case only
;;; proprietary restrictions apply.

(defun-for-system-procedure g2-system-command
    ((command-name symbol)
     (g2-window item)
     (item item)
     (attribute-name symbol))                                    ; Might include class qual.
  (declare (keeps-g2-local-variables-valid nil)) ; Verify this!  - cpm, 5/27/95
  (cond ((of-class-p g2-window 'ui-client-session)
         (ui-stack-error
           "The use of a ui-client-session in g2-system-command is not yet supported"))
        ((not (of-class-p g2-window 'g2-window))
         (system-procedure-argument-list-error
           'window 'g2-system-command 'g2-window g2-window))
        ((null (workstation-for-g2-window? g2-window))
         (ui-stack-error-for-non-connected-window
           'g2-window 'g2-system-command))
        (t
         (for-workstation ((workstation-for-g2-window? g2-window))
           (let ((current-g2-user-mode? (or (g2-user-mode g2-window)
                                            'administrator)))
             (g2-system-command-1 command-name g2-window item attribute-name)))))
  evaluation-false-value)


;;; The function `g2-system-command-1' runs on-workstation with a user-mode
;;; already bound.  TODO: This is a crock. We should be using
;;; synthesize-mouse-pointer and start-ui-command.

(defun g2-system-command-1 (command-name g2-window item attribute-name)
  (let* ((workspace? (get-workspace-if-any item))
         (gensym-window (get-gensym-window-for-g2-window g2-window))
         (image-plane? (and workspace? (image-plane-of-workspace workspace?)))
         (x-in-window?
           (and image-plane?
                (x-in-window-for-image-plane
                  (halfw (+w (left-edge-of-block item)
                             (right-edge-of-block item)))
                  image-plane?)))
         (y-in-window?
           (and image-plane?
                (y-in-window-for-image-plane
                  (halfw (+w (top-edge-of-block item)
                             (bottom-edge-of-block item)))
                  image-plane?))))

    (case command-name
      ;; Special case commands, governed by keyboard restrictions.

      ;; ** I thought that global keyboard command restrictions only
      ;; disabled the top-level bindings of the commands to keystrokes, not
      ;; the commands themselves.  In that case, we should not be checking
      ;; restrictions here. **
      ((refresh)
       (when (global-keyboard-command-permitted-p command-name)
         (funcall-ui-command command-name current-workstation-window)))

      ;; Special case commands, governed by main-menu restrictions.
      ((close-telewindows-connection)
       (when (main-menu-command-permitted-p command-name)
         (when (eq type-of-current-workstation-window 'icp)
           (close-telewindows-connection current-workstation-window))))

      ((log-out)
       (when (main-menu-command-permitted-p command-name)
         (when (g2-secure-p)
           (log-out-workstation current-workstation))))

      ;; Zero argument commands, governed by keyboard restrictions.
      ((help)
       (when (global-keyboard-command-permitted-p command-name)
         (funcall-ui-command command-name)))

      ;; Zero argument commands, governed by main-menu restrictions.
      ((network-info new-title-block
                     remove-tracing-and-breakpoints enable-all-items
                     do-not-highlight-invoked-rules highlight-invoked-rules
                     long-menus short-menus
                     change-mode change-password save-kb inspect
                     reinstall-authorized-users
                     turn-on-all-explanation-caching
                     turn-off-all-explanation-caching)
       (when (main-menu-command-permitted-p command-name)
         (funcall-ui-command command-name)))

      ;; Special-purpose zero-argument commands, not restricted.
      ((abort-user-mouse-tracking)
       (abort-user-mouse-tracking-on-current-workstation))

      ;; Image-plane commands
      ((full-scale
         normalized-full-scale scale-to-fit maximum-scale-to-fit
         one-quarter-the-scale four-times-the-scale twenty-percent-smaller
         twenty-percent-bigger twenty-percent-narrower twenty-percent-wider
         center-origin shift-left-ten-percent shift-right-ten-percent
         shift-left-one-percent shift-right-one-percent shift-up-ten-percent
         shift-down-ten-percent shift-up-one-percent shift-down-one-percent)
       (when image-plane?
         (handle-image-plane-event             ; Handles restrictions.
           command-name image-plane? x-in-window? y-in-window?)))

      ;; Image-plane commands, but different.
      ((lift-to-top drop-to-bottom toggle-visible-grid)
       (when (and image-plane?
                  (global-keyboard-command-permitted-p command-name))
         (case command-name
           (lift-to-top
            (raise-image-plane-to-top image-plane?))
           (drop-to-bottom
            (lower-image-plane-to-bottom image-plane?))
           (toggle-visible-grid
            (toggle-visible-grid image-plane?)))))

      ;; The rest of the global keyboard commands.
      ((circulate-up circulate-down)
       (when (global-keyboard-command-permitted-p command-name)
         (if (eq command-name 'circulate-up)
             (circulate-up current-workstation-detail-pane)
             (circulate-down current-workstation-detail-pane))))


      ;; One argument commands, governed by item-menu restrictions.
      ;; For those that require x/y-in-window supply center of item if
      ;; available, else center of pane.  For those requiring
      ;; image-plane + x/y of item, find them in window
      ((describe describe-configuration dynamic-backward-chaining
                 describe-chaining dynamic-generic-rule-display
                 dynamic-rule-invocation-display
                 enable disable
                 ;; New in 8.0:  (MHD 3/21/04)
                 delete
                 ;; New in 8.2r1:  -dougo, 2/14/06
                 ;; redo-layout-of-g2gl-body
                 redo-layout ;; Changed in 8.3a0.  -dougo, 3/30/06
                 ;; Commands requiring x/y-in-window:
                 table table-of-hidden-attributes show-unsaved-attributes
                 ;; ... and an image plane:
                 change-size restore-to-normal-size transfer clone)
       (when (and (of-class-p item 'item)                    ; Minimal check.
                  (item-menu-command-permitted-p command-name item))
         (case command-name
           ((table table-of-hidden-attributes show-unsaved-attributes
                   ;; change-size, transfer, clone require an image
                   ;; plane. (The others use it if it's available to
                   ;; get an optimal x/y position.)
                   change-size transfer clone)
            (cond
              (image-plane?
               (case command-name
                 (change-size
                  (funcall-ui-command command-name item image-plane? x-in-window? y-in-window? gensym-window))
                 (transfer
                  (cond
                    ((block-transferable-via-ui-command-p item)
                     (funcall-ui-command command-name item x-in-window? y-in-window? image-plane?))
                    (t
                     (ui-stack-error
                       "The item ~NF is not transferrable, cannot do ~a command."
                       item command-name))))
                 (clone
                  (cond
                    ((block-clonable-via-ui-command-p item)
                     (funcall-ui-command command-name item x-in-window? y-in-window? image-plane?))
                    (t
                     (ui-stack-error
                       "The item ~NF is not clonable, cannot do ~a command."
                       item command-name))))
                 (t
                  ;; table table-of-hidden-attributes show-unsaved-attributes
                  (funcall-ui-command command-name item x-in-window? y-in-window?))))
              ((memq command-name '(change-size transfer clone))
               ;; commands that require an image plane
               (ui-stack-error
                 "The item ~NF is not showing, cannot do ~a command."
                 item command-name))
              (t
               (let* ((top-plane
                        (first (stack-of-image-planes
                                 current-workstation-detail-pane)))
                      (x (midline-x-of-pane top-plane))
                      (y (midline-y-of-pane top-plane)))
                 ;; table table-of-hidden-attributes show-unsaved-attributes
                 (funcall-ui-command command-name item x y)))))
           (delete
            (cond
              ((item-may-be-deleted-by-user item)
               ;; this gets the x/y position of the last mouse event -
               ;; it's likely to be the wrong thing, and that's
               ;; inconsistent with the handling of, e.g.,
               ;; table. Should we set the "last mouse position" to
               ;; what it would be for table?
               (funcall-ui-command command-name item))
              (t
               (ui-stack-error
                 "The item ~NF is not be deleteable, cannot do ~a command."
                 item command-name))))
           (redo-layout
            (cond ((and (frame-of-class-p item 'kb-workspace)
                        (get-g2gl-process-parent-of-workspace-if-any item))
                   (funcall-ui-command 'redo-layout-of-g2gl-body item))
                  (t
                   (ui-stack-error
                     "The item ~NF is not a G2GL body workspace, cannot do ~a command."
                     item command-name))))
           (restore-to-normal-size
            (funcall-ui-command command-name item gensym-window))
           (t
            ;; describe describe-configuration dynamic-backward-chaining
            ;; describe-chaining dynamic-generic-rule-display
            ;; dynamic-rule-invocation-display enable disable
            (funcall-ui-command command-name item)))))

      ((edit-icon)
       (cond ((not (of-class-p item 'class-definition))
              (system-procedure-argument-list-error
                'item "the EDIT-ICON case of G2-SYSTEM-COMMAND"
                'class-definition g2-window))

             ((item-menu-command-permitted-p command-name item)
              (funcall-ui-command command-name item))))


      ;; Two argument commands, governed by edit-attribute.
      ((edit)
       (when (and (of-class-p item 'item)
                  attribute-name
                  (symbolp attribute-name))
         (let* ((workstation
                  (workstation-for-g2-window? g2-window))
                (slot-denotation
                  (slot-denotation-of-editable-slot-or-stack-error
                    item attribute-name
                    workstation)))
           (launch-editor-1 item slot-denotation workstation))))

      (t
       (ui-stack-error
         "The ~a argument of ~a received ~a, which does not name a system command."
         'command-name 'g2-system-command command-name)))))

;; I hope that this is checking the correct restrictions.

;; We can easily do only commands which:
;;  (1) Require no mouse-pointer specific arguments (x,y, etc)
;;  (2) Take at most one additional argument, which is an accessable user object.
;;  (3) Do NOT have a generic name.

;; Other commands which might be nice to have, but currently need mouse-pointer
;; bindings: operate-on-area, change-size.

;; The attribute-name should allow a class qualifier.

#+development
(define-system-rpc-access (g2-system-command ())
    ((command-name symbol)
     (g2-window (class g2-window))
     (item (class item))
     (attribute-name symbol))
  (g2-system-command command-name g2-window item attribute-name))



;;; The function `g2-command-is-enabled' returns true if the given command is
;;; both unrestricted and applicable to, or doesn't care about, the given item
;;; on the given window.  That is to say, it should be ungrayed if shown as a UI
;;; element on the window.

;; TODO: Multiple items, option to use current selection on window, no item.
(defun-for-system-procedure g2-command-is-enabled (command item g2-window)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (check-type-or-stack-error command '(or symbol (class user-menu-choice)))
    (make-evaluation-boolean-value
      (command-enabled-for-ui-p command (workstation-this-is-on gensym-window) item))))

(defun command-enabled-for-ui-p (command workstation &optional item?)
  (for-workstation (workstation)
    (cond ((of-class-p command 'user-menu-choice)
           (and item?
                (user-menu-choice-runnable-p command item?)
                (item-menu-command-permitted-p (user-menu-choice-symbol? command) item?)))
          ((not (symbolp command))
           nil)
          ((ui-command-named command)
           (and (command-applicable-p command item?)
                (command-unrestricted-p command item?)))
          (t
           (command-unrestricted-p command item?)))))

;; On current workstation
(defun command-applicable-p (command &optional item?)
  (let ((mouse-pointer (synthesize-mouse-pointer current-workstation item? (key-code 'non-event))))
    (prog1 (command-available-p command mouse-pointer)
      (release-mouse-pointer-if-any mouse-pointer))))

;; On current workstation
(defun command-unrestricted-p (command &optional item?)
  (cond ((memq command main-menu-choices)
         (main-menu-command-permitted-p command))
        ((memq command global-keyboard-command-choices)
         (global-keyboard-command-permitted-p command))
        ((memq command non-menu-choices)
         (non-menu-choice-permitted-p command item?))
        (item?
         (item-menu-command-permitted-p command item?))))


;;; The function `unmangle-slot-component-alias' tries to paper over some weird
;;; slot-component aliases for the names attribute of trend charts. It fails

(defun unmangle-slot-component-alias (slot-denotation)
  (cond ((eq slot-denotation 'PLOT-NAMES)
         (setq slot-denotation 'name-or-names-for-frame))
        ((equal slot-denotation
                '(CLASS-QUALIFIED-NAME TREND-CHART PLOT-NAMES))
         (setf (third slot-denotation) 'name-or-names-for-frame)))
  slot-denotation)


;;; `g2-launch-operate-on-area' is a GDA-only hack to allow programmatic use
;;; of operate on area before G2 5.0 is shipped.

(defun-for-system-procedure g2-launch-operate-on-area
    (kb-workspace g2-window x-in-workspace y-in-workspace)
  (for-workstation ((workstation-for-g2-window? g2-window))
    (let* ((image-plane?
             (image-plane-of-workspace-on-window
               (window-for-workstation current-workstation) kb-workspace))
           (initial-half-extent-of-bounding-box 50)
           x-in-window
           y-in-window)
      (with-image-plane-transform (image-plane?)
        (setf x-in-window
              (x-in-window (-w x-in-workspace initial-half-extent-of-bounding-box)))
        (setf y-in-window
              (y-in-window (-w (-w y-in-workspace) initial-half-extent-of-bounding-box))))
      (funcall-ui-command
        'operate-on-area
        kb-workspace
        image-plane?
        x-in-window
        y-in-window))))





;;;; Obsolete, Unused, and Development-Only Commands


#+unused
(define-ui-command shift-mouse-left-one-pixel ()
  (shift-cursor-position -1 0))


#+unused
(define-ui-command shift-mouse-up-one-pixel ()
  (shift-cursor-position 0 -1))


#+unused
(define-ui-command shift-mouse-right-one-pixel ()
  (shift-cursor-position 1 0))

#+unused
(define-ui-command shift-mouse-down-one-pixel ()
  (shift-cursor-position 0 1))



#+development
(define-ui-command toggle-drawing-mode ()
  "Toggle the drawing mode between XOR style and PAINT style"
  (toggle-drawing-mode))


#+development
(define-ui-command memory-management ()
  (put-up-memory-management-table))

#+development
(define-ui-command show-change-in-memory-use ()
  (compare-memory-allocation))



#+development
(define-ui-command toggle-user-mode ()
  "Toggle the user mode between administrator and user."
  (let ((new-mode (case current-g2-user-mode?
                    (administrator 'user)
                    (t 'administrator))))
;    (log-in-workstation current-workstation nil nil new-mode 'g2-window nil)
    (update-AB-side-TW-user-mode
      new-mode (g2-window-for-this-workstation? current-workstation)
      current-workstation)
    (format t "User mode is ~s~%" new-mode)))


#+development
(define-ui-command toggle-event-tracing ()
  "Toggle UI event tracing"
  (if trace-workstation-events
      (untrace-events)
      (trace-events)))

#+development
(define-ui-command show-recent-events ()
  "Show the last few events and some info about them."
  (show-recent-events))


;;; `DO-FOO' is typically bound to control+alt+f, and will call
;;; a single argument function foo, if it exists.  This is a useful
;;; place to hang a random command for use when debugging.

#+development
(define-ui-command do-foo (mouse-pointer)
  "Call the function FOO of one argument, if it exists."
  ;; presumably you write foo function of one argument, or
  ;; a define-event-handler, is a good way since you can then
  ;; pick stuff out of the mouse-pointer.
  (if (and (fboundp 'foo)
           (eq 1 (length (fn-arglist 'foo))))
      (funcall 'foo mouse-pointer)
      (warn "Do-foo command not run, since one argument function foo not found.")))




;;;; Image-plane commands


;;; `Do-scrolling' does just that on a block.  It is invoked directly
;;; by scroll buttons.

(define-ui-command do-scrolling ((stepper-of-scroll-bar-spot spot)
                                 (block block)
                                 (image-plane image-plane))
  (cond
    ((block-is-allowed-to-have-frame-p block)
     (funcall-method
       'scroll-block
       block image-plane
       (amount-of-step stepper-of-scroll-bar-spot)
       (direction-of-step stepper-of-scroll-bar-spot)))
    (t
     (dwarn "Scrolling is not supported on ~S." block))))



;;; See `handle-image-plane-event' for the handler bodies.  These no longer are
;;; explicitly conditionalized on image-plane: the image plane could be the
;;; "focus" image plane in the case of a single workspace view (new), or else
;;; it will be explicitly checked for by handle-image-plane-event.

(defmacro define-image-plane-command (name)
  `(progn
     (setf (refreshes-image-plane-p ',name) t)
     (define-ui-command ,name (image-plane x-in-window y-in-window)
       (handle-image-plane-event ',name image-plane x-in-window y-in-window))))

;; Scaling commands
(define-image-plane-command full-scale)
(define-image-plane-command normalized-full-scale)
(define-image-plane-command scale-to-fit)
(define-image-plane-command maximum-scale-to-fit)
(define-image-plane-command one-quarter-the-scale)
(define-image-plane-command four-times-the-scale)
(define-image-plane-command twenty-percent-smaller)
(define-image-plane-command twenty-percent-bigger)
(define-image-plane-command twenty-percent-narrower)
(define-image-plane-command twenty-percent-wider)

;; Movement commands.
(define-image-plane-command center-origin)
(define-image-plane-command shift-left-ten-percent)
(define-image-plane-command shift-right-ten-percent)
(define-image-plane-command shift-left-one-percent)
(define-image-plane-command shift-right-one-percent)
(define-image-plane-command shift-up-ten-percent)
(define-image-plane-command shift-down-ten-percent)
(define-image-plane-command shift-up-one-percent)
(define-image-plane-command shift-down-one-percent)



;;;; Table Commands


(defun-simple allow-table-command-p (frame)
  (if (workspace-p frame)
      (user-workspace-p frame)
      (and (block-p frame)                ; Probably not needed.
           (not (or (frame-of-class-p frame 'inspect-command) ;; Note A
                    (frame-of-class-p frame 'inspect-history)
                    (frame-acts-like-arrow-button-p frame)
                    (frame-of-class-p frame 'table-item)
                    (block-of-edit-workspace-p frame))))))

;; The most-interesting-frame argument ensures that we get the table-item, for
;; clicks on tables, rather than the frame represented by the table.

;; Added by SoftServe for Gensym-381 and Gensym 428
;;
;; NOTE: these global variables are dangerous: how can they be safe when multiple
;; TW/TWNGs connected to the same G2 server?  -- Chun Tian (binghe), Feb 2015.

(defvar global-table-of-attributes-pane nil)
(defvar global-table-of-hidden-attributes-pane nil)

(defvar global-table-of-attributes-pane-pointer nil) 
(defvar global-table-of-hidden-attributes-pane-pointer nil)

(defvar global-nmsci-id-for-attributes-pane nil)
(defvar global-nmsci-id-for-hidden-attributes-pane nil)
(defvar global-nms-menu-choiced-item-id nil)

(define-ui-command (table-of-attributes-pane
                     :pretty-name "Table of attributes") 
                     ((frame most-interesting-frame) g2-window)
  "Put up the attributes table pane for the selected item."
  (when (allow-table-command-p frame)
    (create-or-destroy-table-of-attributes-pane frame g2-window)))

(define-ui-command (table-of-hidden-attributes-pane
                     :pretty-name "Table of hidden attributes") 
                     ((frame most-interesting-frame) g2-window)
  "Put up the hidden attributes table pane for the selected item."
  (when (and (allow-table-command-p frame)
             (not (frame-of-class-p frame 'g2-login)))
    (create-or-destroy-table-of-hidden-attributes-pane frame g2-window)))

;;; The function `update-att-tables' updates table of attributes and table of
;;;  hidden attributes panes for frame
(defun update-att-tables (frame g2-window)
  (when (and (framep frame) g2-window)
    (funcall-ui-command 'update-table-of-attributes-pane frame g2-window)
    (funcall-ui-command 'update-table-of-hidden-attributes-pane frame g2-window)))

(defun create-or-destroy-table-of-attributes-pane (frame g2-window)
  (when (not (find-native-window 
                 (map-to-gensym-window-or-stack-error g2-window)
                 global-table-of-attributes-pane
                 'g2-property-grid))
    (setf global-table-of-attributes-pane nil)
    (setf global-table-of-attributes-pane-pointer nil))

  (cond ((not (eq global-table-of-attributes-pane nil))
         (g2-ui-manage-property-grid 'destroy global-table-of-attributes-pane nil g2-window)
         (setf global-table-of-attributes-pane nil)
         global-table-of-attributes-pane)
        ((eq global-table-of-attributes-pane nil)
         (setf global-table-of-attributes-pane
               (if frame
                   (g2-ui-create-property-grid
                    (make-class-header-string frame)
                    nil
                    (allocate-evaluation-structure-inline 
                      'contents (get-attribute-texts-of-item-for-pane frame)
                      'user-data (package-internal-data-property frame
                                                                 g2-window
                                                                 'update-table-of-attributes-pane nil)
                      'sort 'none)
                    g2-window
                    'property-user-callback-func)
                   ;; GENSYM-46813, create null property table when frame is NIL -- binghe, 2009/7/29
                   (g2-ui-create-property-grid
                    #w"" nil
                    (allocate-evaluation-structure-inline
                      'contents (allocate-evaluation-sequence nil)
                      'user-data (package-internal-data-property
                                  nil g2-window 'update-table-of-attributes-pane nil)
                      'sort 'none)
                    g2-window
                    'property-user-callback-func)))
         (setf global-nmsci-id-for-attributes-pane global-nms-menu-choiced-item-id)
         (setf global-table-of-attributes-pane-pointer
               (find-native-view-or-stack-error
                 (map-to-gensym-window-or-stack-error g2-window)
                 global-table-of-attributes-pane 'g2-property-grid)))))

(defun create-or-destroy-table-of-hidden-attributes-pane (frame g2-window)
  (when (not (find-native-window 
                 (map-to-gensym-window-or-stack-error g2-window)
                 global-table-of-hidden-attributes-pane
                 'g2-property-grid))
    (setq global-table-of-hidden-attributes-pane nil)
    (setq global-table-of-hidden-attributes-pane-pointer nil))
  (cond ((not (eq global-table-of-hidden-attributes-pane nil))
	 (g2-ui-manage-property-grid 'destroy global-table-of-hidden-attributes-pane nil g2-window)
	 (setq global-table-of-hidden-attributes-pane nil))
	((eq global-table-of-hidden-attributes-pane nil)
	 (setq global-table-of-hidden-attributes-pane
	       (g2-ui-create-property-grid
		 (make-virtual-attribute-class-header-string frame)
		 nil
		 (allocate-evaluation-structure-inline 
		   'contents (get-hidden-attribute-texts-of-item-for-pane frame)
		   'user-data (package-internal-data-property
				frame g2-window 'update-table-of-hidden-attributes-pane nil)
		   'sort 'none)
		 g2-window
		 'property-user-callback-func))
	 (setq global-nmsci-id-for-hidden-attributes-pane global-nms-menu-choiced-item-id)
	 (setq global-table-of-hidden-attributes-pane-pointer
	       (find-native-view-or-stack-error
		 (map-to-gensym-window-or-stack-error g2-window)
		 global-table-of-hidden-attributes-pane 'g2-property-grid)))))

(define-ui-command update-table-of-attributes-pane ((frame most-interesting-frame) g2-window)
  (when (allow-table-command-p frame)
    (update-table-of-attributes-pane frame g2-window)))

(define-ui-command update-table-of-hidden-attributes-pane ((frame most-interesting-frame) g2-window)
  (when (and (allow-table-command-p frame)
             (not (frame-of-class-p frame 'g2-login)))
    (update-table-of-hidden-attributes-pane frame g2-window)))

(defun update-property-grid-all (frame)
  (declare (ignore frame))
  (update-property-pane-after-edit global-table-of-attributes-pane-pointer)
  (update-property-pane-after-edit global-table-of-hidden-attributes-pane-pointer))

(defun update-table-of-attributes-pane (frame g2-window)
  (when (and (not (eq global-table-of-attributes-pane nil))
             (find-native-window 
                 (map-to-gensym-window-or-stack-error g2-window)
                 global-table-of-attributes-pane
                 'g2-property-grid))
	(g2-ui-manage-property-grid
	     'populate
	     global-table-of-attributes-pane
	     (get-attribute-texts-of-item-for-pane frame)
	     g2-window)
        (caption-native-window
             (find-native-view-or-stack-error 
                 (map-to-gensym-window-or-stack-error g2-window)
                 global-table-of-attributes-pane
                 'g2-property-grid) 
             (make-class-header-string frame))
        (g2-ui-manage-property-grid
	     'sort
	     global-table-of-attributes-pane
	     'none
	     g2-window)))

(defun update-table-of-hidden-attributes-pane (frame g2-window)
  (when (and (not (eq global-table-of-hidden-attributes-pane nil))
             (find-native-window 
                 (map-to-gensym-window-or-stack-error g2-window)
                 global-table-of-hidden-attributes-pane
                 'g2-property-grid))
	(g2-ui-manage-property-grid
	     'populate
	     global-table-of-hidden-attributes-pane
	     (get-hidden-attribute-texts-of-item-for-pane frame)
	     g2-window)
        (caption-native-window 
             (find-native-view-or-stack-error
                  (map-to-gensym-window-or-stack-error g2-window)
                  global-table-of-hidden-attributes-pane
                  'g2-property-grid) 
             (make-virtual-attribute-class-header-string frame))
        (g2-ui-manage-property-grid
	     'sort
	     global-table-of-hidden-attributes-pane
	     'none
	     g2-window)))

(defun get-attribute-texts-of-item-for-pane (frame)
  (let* ((class-description (class-description-slot frame))
	 (name-and-description-alist
	  (get-list-of-all-user-visible-attributes-for-pane class-description nil)))
    (loop for (name . slot-description-or-virtual-attribute) in name-and-description-alist
	  with all-attributes-p = t
	  as want-attribute-p = all-attributes-p
	  as attribute-text-value? = (and want-attribute-p
					  (serve-text-of-attribute frame name nil))
	  as slot-name? = (pretty-slot-name slot-description-or-virtual-attribute)
	  when attribute-text-value?
	    collect (create-node-for-table-of-attributes-pane
		      frame name attribute-text-value? slot-name? nil T)
		into attribute-names-and-values using eval-cons
	  finally
	    (reclaim-eval-alist name-and-description-alist)
	    (return (allocate-evaluation-sequence attribute-names-and-values)))))

(defun get-hidden-attribute-texts-of-item-for-pane (frame)
  (let* ((class-description (class-description-slot frame))
	 (name-and-description-alist
	  (get-list-of-all-virtual-attributes-for-pane class-description nil)))
    (loop for (attr-name . slot-description-or-virtual-attribute) in name-and-description-alist
	  with all-attributes-p = t
	  as want-attribute-p = all-attributes-p
	  as attribute-value? = (and want-attribute-p
				     (get-attribute-description-evaluation-value
				       frame slot-description-or-virtual-attribute))
	  as slot-name? = (pretty-slot-name slot-description-or-virtual-attribute)
	  when (text-string-for-item-or-value attribute-value?)
	    collect (create-node-for-table-of-hidden-attributes-pane
		      frame attr-name
		      (text-string-for-item-or-value attribute-value?) attr-name T T)
		into attribute-names-and-values using eval-cons
	  finally
	    (reclaim-eval-alist name-and-description-alist)
	    (return (allocate-evaluation-sequence attribute-names-and-values)))))

(defun-simple package-internal-data-property (frame g2-window function flag)
  (allocate-evaluation-structure-inline
    'frame frame
    'window g2-window
    'func function
    'flag flag))

(defun create-node-for-table-of-attributes-pane (frame attribute-text-name
    attribute-text-value slot-name virtual editable)
  (allocate-evaluation-structure-inline
    'property attribute-text-name
    'current-value attribute-text-value
    'user-data (package-internal-data-with-slot frame slot-name virtual editable)
    'edit-in-place (make-evaluation-truth-value falsity)))

(defun package-internal-data-with-slot (frame slot-name virtual editable)
  (allocate-evaluation-structure-inline
    'frame frame
    'slot-name slot-name
    'command 'execute
    'virtual virtual
    'editable editable))

(defun create-node-for-table-of-hidden-attributes-pane
       (frame attribute-text-name attribute-text-value slot-name virtual edit)
  (allocate-evaluation-structure-inline
    'property attribute-text-name
    'current-value attribute-text-value
    'user-data (package-internal-data-with-slot frame slot-name virtual edit)
    'edit-in-place (make-evaluation-truth-value falsity)))

;; End of SoftServe changes		

(define-ui-command table ((frame most-interesting-frame) original-x-in-window original-y-in-window)
  "Put up the attributes table for the selected item."
  (when (allow-table-command-p frame)
    (put-up-attributes-table frame original-x-in-window original-y-in-window)))

(define-ui-command (table-of-item :name table)
    ((frame most-interesting-frame) original-x-in-window original-y-in-window)
  "Put up the attributes table for the selected item."
  (when (and (not (workspace-p frame))
             (allow-table-command-p frame))
    (put-up-attributes-table frame original-x-in-window original-y-in-window)))

(define-ui-command (table-of-workspace :name table)
    (workspace original-x-in-window original-y-in-window)
  "Put up the attributes table for the selected workspace."
  (when (allow-table-command-p workspace)
    (put-up-attributes-table workspace original-x-in-window original-y-in-window)))

(define-ui-command table-of-hidden-attributes
    ((frame most-interesting-frame) original-x-in-window original-y-in-window)
  (when (and (allow-table-command-p frame)
             (not (frame-of-class-p frame 'g2-login)))
    (put-up-virtual-attributes-table frame original-x-in-window original-y-in-window)))

(define-ui-command (table-of-hidden-attributes-of-item :name table-of-hidden-attributes)
    ((frame most-interesting-frame) original-x-in-window original-y-in-window)
  (when (and (not (workspace-p frame))
             (allow-table-command-p frame)
             (not (frame-of-class-p frame 'g2-login)))
    (put-up-virtual-attributes-table frame original-x-in-window original-y-in-window)))

(define-ui-command show-unsaved-attributes
    ((frame most-interesting-frame) original-x-in-window original-y-in-window)
  "Shows the attributes that have changed since the last save of an permanent G2 item."
  (when (and (allow-table-command-p frame)
             (not (frame-of-class-p frame 'g2-login))
             (item-has-unsaved-changes-visible-in-tables-p frame))
    (put-up-attributes-table frame original-x-in-window original-y-in-window
                             nil nil nil
                             (if (item-was-created-by-load-p frame)
                                 (attributes-permamently-changed frame)
                                 t))))

;; Maybe this should be restricted to item-p?

;; Note A: The reason inspect-commands have to be checked for explicitly, and
;; not other commands, is that only inspect commands are actually placed into
;; their workspace, and when clicked upon yield an inspect-command-spot.  The
;; other commands, for example file-commands, live with a null superblock, and
;; we never encounter them in UI input events.  See similar guards in
;; facilities.  This update was for HQ-180816 -fmw, 1/27/95


(define-ui-command shrink-wrap (workspace)
  "Shrink this workspace until just large enough to enclose all of its subblocks."
  (shrink-wrap-workspace workspace))

(defun name-block-permitted-p (block)
  (and (type-of-slot-if-editable (class block) 'name-or-names-for-frame)
       (not (frame-of-class-p block 'rule))
       (item-is-either-not-permanent-or-from-an-editable-module-p block)))

(defun edit-name-of-block (block)
  (enter-editing-context                ; NOTE: similar code in workspace case
    block 'name-or-names-for-frame        ; will be part of current context
    (make-text-representation-for-slot-value        ; LOSES CONSES!
      block 'name-or-names-for-frame)))

(define-ui-command name (block)
  "Edit the name of this object, if it allows one."
  (when (name-block-permitted-p block)
    (edit-name-of-block block)))

;; The class test no longer necessary. Classes that do not get the name choice
;; are those that have (type nil) on the name-or-names-for-frame slot. ML, 8/8/89
;;    (and (type-of-slot-if-editable (class entity) 'name-or-names-for-frame)
;;         (not (frame-of-class-p entity 'object-definition))))
;; specify text-box-format, width-for-cell?, width-for-initial-text??

;; Except: rules did not have a NAME option in their menu in 3.0.


;; A variation which does not allow workspaces.
(define-ui-command (name-item :name name) (block)
  "Edit the name of this object, if it allows one."
  (when (and (not (workspace-p block))
             (name-block-permitted-p block))
    (edit-name-of-block block)))



;;;; Text stripping commands


;; I think that item is the correct magic argument here.  We need to get
;; the table instance in some cases.

(define-ui-command mark-to-strip-text (item)
  (when (strip-choice-obtains-p item 'mark-to-strip-text)
    (set-stripping-flags-as-specified item 1 0)))

(define-ui-command mark-to-strip-text-* (item)
  (when (strip-choice-obtains-p item 'mark-to-strip-text-*)
    (set-stripping-flags-as-specified item 1 0)))

(define-ui-command remove-strip-text-mark (item)
  (when (strip-choice-obtains-p item 'remove-strip-text-mark)
    (set-stripping-flags-as-specified item 0 0)))

(define-ui-command remove-strip-text-mark-* (item)
  (when (strip-choice-obtains-p item 'remove-strip-text-mark-*)
    (set-stripping-flags-as-specified item 0 0)))

(define-ui-command mark-not-to-strip-text-* (item)
  (when (strip-choice-obtains-p item 'mark-not-to-strip-text-*)
    (set-stripping-flags-as-specified item 0 1)))

(define-ui-command mark-not-to-strip-text (item)
  (when (strip-choice-obtains-p item 'mark-not-to-strip-text)
    (set-stripping-flags-as-specified item 0 1)))

(define-ui-command remove-do-not-strip-text-mark-* (item)
  (when (strip-choice-obtains-p item 'remove-do-not-strip-text-mark-*)
    (set-stripping-flags-as-specified item 0 0)))

(define-ui-command remove-do-not-strip-text-mark (item)
  (when (strip-choice-obtains-p item 'remove-do-not-strip-text-mark)
    (set-stripping-flags-as-specified item 0 0)))



;;;; Commands used in restrictions.

(define-ui-command (edit-expression-of-readout-table :name edit)
    ((readout-table readout-table)
     (slot-name slot-name))
  (when (and (eq slot-name 'expressions-to-display)
             (item-is-either-not-permanent-or-from-an-editable-module-p readout-table))
    ;; I do not know by what magic readout-tables did this in 3.0, but
    ;; this clause does seem to work in 4.0
    (enter-editing-context readout-table 'expressions-to-display)))


;; (short-representation-p table), in table menu.

(define-ui-command hide-name ((block name-box))
  (funcall-ui-command 'delete block))



;;;; Commands for submenus

;;; These commands are unfortunately needed because their names are
;;; restrictable menu item names.  For example,
;;;  pressing alt+m implies load-merge-save

(define-ui-command main-menu ()
  (post-menu-named (if short-menus? 'short-main-menu 'main-menu)))

(define-ui-command load-merge-save ()
  (post-menu-named 'load-merge-save))

(define-ui-command run-options ()
  (post-menu-named 'run-options))

(define-ui-command miscellany (mouse-pointer)
  (let ((menu-name
          (cond ((menu-obtains-p 'workspace-menu mouse-pointer)
                 'workspace-miscellany)
                (short-menus?
                 'short-miscellany-menu)
                (t
                 'miscellany-menu))))
    (post-menu-named menu-name)))

(define-ui-command other-edits (mouse-pointer)
  (when (menu-obtains-p 'freeform-table mouse-pointer)
    (post-menu-named 'other-edits)))





;;;; Editor Commands on Selected Text

;;; This section contains commands that implement the secondary selection of
;;; text in the editor.  These happen when the user drags over some text while
;;; an editor is active.  If this text is in that editor after selecting it, a
;;; menu is posted of operations to perform on the selected text.

;;; These commands all work in a similar manner: they take a text region that
;;; must be created when in an editing context.  When they finally are executed,
;;; you can be in any context.  They will consume the text region.  The text
;;; region is currently always dragged out by the text-marking workstation
;;; context, and these commands are set up by the continuations from that
;;; context.

;;; See also the subsection "Editor Commands on Selected Text WITHIN THE EDITOR"
;;; in module EDIT1.

;; Note that the binding of the magic argument (edit-context
;; specific-workstation-context) in the code below works because that binding is
;; done when the pending command is created, not later when it is fired.


;;; `cut-selected-text'

(define-ui-command (cut-selected-text
                     ;; :context 'editing
                     :name cut)                                    ; <NEW>
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Cut the selected text and place it on the clipboard."
  (cond
    ((empty-text-region-p text-region)
     (delete-frame text-region))
    (t
     (in-editing-context (edit-context)
       (do-cut-within-editor)))))

;;; `copy-selected-text'

(define-ui-command (copy-selected-text
                     ;; :context 'editing
                     :name copy)
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Copy the selected text to the clipboard."
  (progn
    (in-editing-context (edit-context)
      (unless (empty-text-region-p text-region)
        (coerce-text-region-to-scrap text-region))
      ;; grandfathered in:
      (delete-frame text-region))))

;;; `paste-over-selected-text'

(define-ui-command (paste-over-selected-text
                     ;; :context 'editing
                     :name paste)
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Paste the clipboard, replacing and discarding the selected text."
  (when (text-can-be-pasted-in-current-workstation-p)
    (funcall-ui-command 'paste edit-context)
    (return-from-current-workstation-context
      type-of-current-workstation-context 'PENDING-DELETE-TYPE-IN)))




;;; `delete-selected-text'

(define-ui-command (delete-selected-text
                     ;; :context 'editing
                     :name delete)
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Delete the selected text, and discard it."
  ;; I.e. clear in a more standard UI.
  (in-editing-context (edit-context)
    (do-delete-within-editor)))


;;; `insert-selected-text' - inserts the selected text at the position
;;; of the cursor, without affecting either the scrapbook or the selected
;;; text itself.  This restores the version 3.0 behavior.

(define-ui-command (insert-selected-text
                     ;; :context 'editing
                     :name insert)
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Insert the selected text at the cursor location."
  (cond
    ((empty-text-region-p text-region)
     (delete-frame text-region))
    (t
     (in-editing-context (edit-context)
       (do-insert-within-editor)))))


;;; `copy-and-insert-selected-text' - inserts the selected text at the
;;; position of the cursor, leaving a copy in the scrapbook.  This was
;;; called "insert" in 4.0.  It was unimplemented in 3.0, and is currently
;;; unavailable in 5.0.  If there is user demand for it, we can easily
;;; add it.

(define-ui-command (copy-and-insert-selected-text
                     ;; :context 'editing
                     :name copy-and-insert
                     :pretty-name "Copy and Insert")
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Copy the selected text and insert it at the cursor location."
  (cond
    ((empty-text-region-p text-region)
     (delete-frame text-region))
    (t
     (in-editing-context (edit-context)
       (do-copy-and-insert-within-editor)))))


;;; `move-selected-text'

(define-ui-command (move-selected-text ; :context 'editing
                     :name move)
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Move the selected text to the cursor location."
  (progn
    (in-editing-context (edit-context)
      (cond
        ((empty-text-region-p text-region)
         (delete-frame text-region))
        (t
         (do-move-within-editor))))))


;;; `cut-and-insert-selected-text'

(define-ui-command (cut-and-insert-selected-text
                     ;; :context 'editing
                     :name cut-and-insert
                     :pretty-name "Cut and Insert")
    ((text-region block-of-selection-focus)
     (edit-context workstation-context-specifics))
  "Cut the selected text, place it on the clipboard, and insert it at the cursor."
  (cond
    ((empty-text-region-p text-region)
     (delete-frame text-region))
    (t
     (in-editing-context (edit-context)
       (do-cut-and-insert-within-editor)))))


;;; `paste' should not be confused with the paste button in the editor

(define-ui-command paste
    ;; :context 'editing
    ((edit-context workstation-context-specifics))
  "Paste the clipboard contents at the cursor location."
  (in-editing-context (edit-context)
    (do-paste-within-editor)))



;;; `Edit-text-marking-menu' is posted in the editor's continuation
;;; of the text-marking context when the user has marked text in the
;;; current editor.

(defmenu (editor-text-marking-menu :title "Edit Operations")
    ()
  cut-selected-text
  copy-selected-text
  paste-over-selected-text
  delete-selected-text
  insert-selected-text
  ;; copy-and-insert-selected-text
  move-selected-text
  cut-and-insert-selected-text
  #+enable-ole
  (include ole-text-menu-choices)
  )






;;;; Utilities Which Belong Elsewhere


;;; The function `compute-category-members' is a completely ad-hoc function to
;;; compute a gensym-list of the members of an "enumerated" grammar category,
;;; one whose members are all single symbols, rather than phrases.

(defun compute-category-members (category-name)
  (let ((category? (get-category-for-category-symbol-if-any category-name)))
    (when category?
      (compute-category-members-1 category?))))

(defun compute-category-members-1 (category)
  (cond ((category-is-for-token-p category)
         (gensym-list (category-token category)))
        (t
         (let ((result nil))
           (loop for symbol in (token-instances-without-specific-categories category) doing
             (gensym-pushnew symbol result))

           (loop for category in (categories-that-can-begin-a-phrase-of-this-category category) doing
             (loop for symbol in (compute-category-members-1 category) doing
               (gensym-pushnew symbol result)))

           (when (get-directory-contents (category-symbol category))
             (let ((symbols (flatten-gensym-tree (get-directory-contents (category-symbol category)))))
               (loop for symbol in symbols doing
                 (gensym-pushnew symbol result))
               (reclaim-gensym-list symbols)))

           (nreverse result)))))

(defun flatten-gensym-tree (tree)
  (cond ((null tree) nil)
        ((atom tree) (gensym-list tree))
        ((consp tree)
         (nconc (flatten-gensym-tree (car tree))
                (flatten-gensym-tree (cdr tree))))))

(defun slot-value-as-string (frame slot-name)
  (let* ((slot-description
           (get-slot-description-of-frame slot-name frame))
         (slot-value
           (get-slot-description-value frame slot-description))
         (type-of-slot?
           (get-type-of-slot-if-any frame slot-name))
         (grammar-category-symbol
           (category-symbol-given-slot-type type-of-slot?))
         (slot-value-writer?
           (slot-value-writer grammar-category-symbol))
         (write-symbols-in-lower-case? t))
    (twith-output-to-text-string
      (if slot-value-writer?
          (funcall-simple-compiled-function slot-value-writer? slot-value frame)))))

(defun put-symbol-valued-slot (frame slot string?)
  (let* ((type? (get-type-of-slot-if-any frame slot))
         (category? (category-symbol-given-slot-type type?))
         (compiler? (slot-value-compiler category?)))
    (when string?
      (let ((parse (cond ((=f (lengthw string?) 0) nil)
                         (t
                          ;; FIXME: No provision for lower case chars in the symbol!
                          (upcase-text-string-in-place string?)
                          (intern-wide-string-no-reclaim string?)))))
        (multiple-value-bind (compiled-value error?)
            (if compiler?
                (funcall-compiled-function compiler? parse frame slot)
                parse)
          (unless error?
            (change-slot-value frame slot compiled-value)))))))


;;;; Built-in Dialogs Facility


(defvar alternate-symbols-for-translation nil)

(def-menu-string ok "OK")

(defmacro defdialog (name (caption &key
                                   (width 265)
                                   (height 110)
                                   (style '(ds-modalframe ws-clipchildren ws-caption ws-sysmenu))
                                   (exstyle ())
                                   (font #w"MS Shell Dlg") ;SS_ERROR:recent change to #w
                                   (fontsize 8)
                                   (resizeable nil))
                          &body controls)
  (let ((flags (if resizeable '(resizeable))))
    (when resizeable
      (pushnew 'ws-thickframe style))
    `(progn (defvar ,name)
            (setq ,name
                  '(dialog ,caption 0 0 ,width ,height
                    ,style ,exstyle ,flags
                    ,font ,fontsize ,controls))
            ',name)))

(def-list-structure (dialog-spec)
    (dialog-spec-type
      dialog-spec-caption
      dialog-spec-x
      dialog-spec-y
      dialog-spec-width
      dialog-spec-height
      dialog-spec-style
      dialog-spec-exstyle
      dialog-spec-flags
      dialog-spec-font
      dialog-spec-font-size
      dialog-spec-controls))

(def-list-structure (dialog-control)
    (dialog-control-class
      dialog-control-id
      dialog-control-caption
      dialog-control-x
      dialog-control-y
      dialog-control-width
      dialog-control-height
      dialog-control-style
      dialog-control-exstyle
      dialog-control-flags
      dialog-control-data))

(defun find-control-in-dialog-spec (id spec)
  (loop for control in (dialog-spec-controls spec)
        when (eql id (dialog-control-id control))
          return control))

;; Label is a symbol or string, or a list of them, which are concatenated.
(defun translate-label-for-dialog (label)
  (cond ((null label) nil)
        ((stringp label)
         (copy-as-wide-string label))
        ((stringpw label)
         (copy-wide-string label))
        ((listp label)
         (twith-output-to-text-string
           (loop for element in label
                 as string? = (translate-label-for-dialog element)
                 when string?
                   do (twrite-string string?))))
        ((symbolp label)
         (let ((symbol
                 (or (if (translation-for-symbol? label) label)
                     (let ((alt? (cdr (assq label alternate-symbols-for-translation))))
                       (if (and alt? (translation-for-symbol? alt?))
                           alt?))
                     label)))
           (translated-string-for-symbol symbol t t)))))

(defun translate-style-for-dialog (style)
  (loop with (high . low) = (32bit-constant-value 'ws-visible)
        for e in style
        as sym = (if (consp e) (cadr e) e)
        as not? = (and (consp e) (eq (car e) 'not))
        as (hi . lo) = (or (32bit-constant-value sym)
                           (cdr (assq sym
                                      '((ds-modalframe 0 . 128)
                                        (ds-nofailcreate 0 . 16)
                                        (ds-noidlemsg 0 . 256)
                                        (ds-setfont 0 . 64)
                                        (ds-setforeground 0 . 512)
                                        (ds-sysmodal 0 . 2))))
                           (progn (dwarn "Win32 style constant ~a not found" sym)
                                  '(0 . 0)))
        doing (if not?
                  (setq high (logandc2f high hi)
                        low (logandc2f low lo))
                  (setq high (logiorf high hi)
                        low (logiorf low lo)))
        finally (return (make-32bit-integer high low))))

(defun translate-control-id-for-dialog (id)
  (case id
    (idok 1) (idcancel 2) (idabort 3) (idretry 4) (idignore 5) (idyes 6) (idno 7) (t id)))

(defun translate-flags-for-dialog (class flags)
  (loop with result = (case class (static 32) (t 0)) ; Ignore static controls by default.
        for flag in flags
        as value = (case flag
                     (anchor-top 1)
                     (anchor-bottom 2)
                     (anchor-left 4)
                     (anchor-right 8)
                     (resizeable 16)
                     (ignore 32) ; Don't return data.
                     (t 0))
        do (setq result (logiorf result flag))
        finally (return result)))

(defun translate-dialog-spec (spec)
  (gensym-dstruct-bind ((type caption x y width height style exstyle flags font font-size controls) spec)
    (gensym-list
      type
      (translate-label-for-dialog caption)
      x y width height
      (translate-style-for-dialog style)
      (translate-style-for-dialog exstyle)
      (translate-flags-for-dialog 'dialog flags)
      (copy-as-wide-string font)
      font-size
      (loop for (class id caption x y width height style exstyle flags data?) in controls
            as control = (nconc (gensym-list class
                                             (translate-control-id-for-dialog id)
                                             (translate-label-for-dialog caption)
                                             x y width height
                                             (translate-style-for-dialog style)
                                             (translate-style-for-dialog exstyle)
                                             (translate-flags-for-dialog class flags))
                                (if data?
                                    (gensym-list (copy-gensym-tree-with-text-strings data?))))
            collect control using gensym-cons))))

(defun modify-control-in-dialog-spec (how id spec)
  (let ((control? (find-control-in-dialog-spec
                    (translate-control-id-for-dialog id)
                    spec)))
    (when control?
      (let* ((old-style (dialog-control-style control?))
             (new-style
               ;; Hack: we know that the constant ws-disabled belongs in the high part.
               (make-32bit-integer (case how
                                     (disable (logiorf (32bit-integer-high-part old-style) #.ws-disabled))
                                     (hide (logandc2f (32bit-integer-high-part old-style) #.ws-visible))
                                     (t (32bit-integer-high-part old-style)))
                                   (32bit-integer-low-part old-style))))
        (setf (dialog-control-style control?) new-style)
        (reclaim-32bit-integer old-style)))))


;;;; Native Login Dialog

(eval-when (:compile-toplevel :load-toplevel :execute)

(defconstant mb-iconhand #x0010)
(defconstant mb-iconquestion #x0020)
(defconstant mb-iconexclamation #x0030)
(defconstant mb-iconasterisk #x0040)

) ; eval-when

(defdialog native-login-dialog (change-user-settings :width 265 :height 110)
  (static   nil  (USER-NAME ":")  6 10  49  8)
  (edit     user nil             60  8 162 12   (es-autohscroll ws-tabstop) (ws-ex-clientedge))
  (static   nil  (PASSWORD ":")   6 27  49  8)
  (edit     pass nil             60 25 162 12   (es-password es-autohscroll ws-tabstop) (ws-ex-clientedge))
  (static   nil  (USER-MODE ":")  6 44  49  8)
  (combobox mode nil             60 42 162 144  (cbs-dropdown ws-vscroll ws-tabstop))
  (static   nil  (LANGUAGE ":")   6 63  49   8)
  (combobox lang nil             60 61 162 144  (cbs-dropdown ws-vscroll ws-tabstop))
  (button   idok     OK          61 87  50  14  (bs-defpushbutton ws-tabstop))
  (button   idcancel CANCEL     127 87  50  14  (ws-tabstop))
  (button   idabort  DISCONNECT 193 87  50  14  (ws-tabstop)))

(defparameter alternate-translations-for-login-dialogs
  '((user-mode . g2-user-mode)
    (window . g2-window-name-or-class)
    (language . g2-window-specific-language)
    (ok . end)))

;; Increase space for button labels by delta DLU.
(defun resize-native-login-dialog (spec)
  (let ((delta
          (loop for control in (dialog-spec-controls spec)
                ;; FIXME: This computation is completely made up.
                ;; Although it works fairly well.
                as need = (+f 8 (*f 3 (lengthw (stringw (dialog-control-caption control)))))
                when (and (null (dialog-control-id control))
                          (eq (dialog-control-class control) 'static))
                  maximize (-f need (dialog-control-width control))))
        (width (dialog-spec-width spec)))
    (when (>f delta 0)
      (loop for control in (dialog-spec-controls spec) doing
        (case (dialog-control-class control)
          (static
           (unless (dialog-control-id control)
             (incff (dialog-control-width control) delta)))
          ((edit combobox)
           (incff (dialog-control-x control) delta)
           (setq width (maxf width (+f (dialog-control-x control)
                                       (dialog-control-width control) 2)))))))
    (setf (dialog-spec-width spec) width)
    spec))

(defun native-login-dialog-p (gensym-window)
  (and (prefer-native-login-dialog miscellaneous-parameters)
       (window-supports-manage-dialog gensym-window)
       (icp-window-p gensym-window)
       (not (classic-ui-p gensym-window))))

;; Alias user creation dialog
(defdialog native-alias-creation-dialog (user-mode-alias-creation :width 265 :height 80)
  (static   nil  (USER-MODE-ALIAS ":") 6 10  60  8)
  (edit     user nil 75  8 140 12   (es-autohscroll ws-tabstop) (ws-ex-clientedge))
  (static   nil  (EXISTING-USER-MODE-FOR-THIS-ALIAS ":")  6 27  60  8)
  (combobox mode nil 75 25 140 144  (cbs-dropdown ws-vscroll ws-tabstop))
  (button   idok     OK      81 55  50  14  (bs-defpushbutton ws-tabstop))
  (button   idcancel CANCEL  147 55  50  14  (ws-tabstop)))

;; Must be called in a translation context.
(defun post-native-login-dialog (g2-login-state &optional beep?)
  (let* ((gensym-window current-workstation-window)
         (g2-login (g2-login g2-login-state))
         (how-entered (g2-login-how-entered g2-login))
         (user (slot-value-as-string g2-login 'g2-login-user-name?))
         (mode (slot-value-as-string g2-login 'g2-login-user-mode))
         (language (slot-value-as-string
                     g2-login 'g2-login-specific-language-for-this-g2-window?))
         (all-modes (compute-category-members 'g2-user-mode-for-login))
	 (all-mode-aliases (user-mode-aliases kb-configuration))
	 (modes (if (eq how-entered 'alias-creation)
		  (let ((result nil))
		    (loop for mode in all-modes do
			  (let ((is-alias nil))
			    (loop for alias in all-mode-aliases do
				  (when (eq mode (alias-name alias))
				    (setq is-alias t)
				    (return)))
			    (when (not is-alias)
			      (setq result (gensym-cons mode result)))))
		    (gensym-cons (car result) result))
		  (gensym-cons mode all-modes)))
         (languages (gensym-cons language
                                 (compute-category-members 'language?)))
         (message? (when (g2-login-comments g2-login)
                     (twith-output-to-text-string
                       (twrite-login-failure-translation-symbol (g2-login-comments g2-login)))))
         (alternate-symbols-for-translation
           alternate-translations-for-login-dialogs)
		 (spec 
		   (if (eq how-entered 'alias-creation)
             (resize-native-login-dialog
                 (translate-dialog-spec native-alias-creation-dialog))
		     (resize-native-login-dialog
                 (translate-dialog-spec native-login-dialog))))
		
         (data 
		   (if (eq how-entered 'alias-creation)
		     (gensym-list 'user nil 'mode modes)
		     (gensym-list 'user user 'mode modes 'lang languages))) ; Keys are control ids.
         (arg (nconc (gensym-list 'spec spec 'data data)
                     (if (fixnump beep?) (gensym-list 'beep beep?))))
         (handle 123))

    ;; Append message to caption.
    (when message?
      (let ((new-caption (twith-output-to-text-string
                           (twrite (dialog-spec-caption spec))
                           (twrite-string #w" - ")
                           (twrite-string message?))))
        (reclaim-text-string message?)
        (reclaim-if-text-string (dialog-spec-caption spec))
        (setf (dialog-spec-caption spec) new-caption)))

    ;; Disable either the cancel or the abort (=disconnect) button.
    (cond ((and (icp-window-p gensym-window)
                (not (memq how-entered '(changing-mode password-change alias-creation))))
           (modify-control-in-dialog-spec 'disable 'idcancel spec))
          (t
           (modify-control-in-dialog-spec 'disable 'idabort spec)))

    (manage-dialog gensym-window #.dlg-post-modal handle arg)
    (reclaim-gensym-tree-with-text-strings arg)))

(defun cancel-native-login-dialog (gensym-window)
  (when (native-login-dialog-p gensym-window)
    (manage-dialog current-workstation-window #.dlg-cancel-modal 123 nil)))

(define-event-handler handle-login-dialog-message ((gensym-window window)
                                                   (context workstation-context-specifics)
                                                   event-plist)
  (when (g2-login-state-p context)
    (let* ((g2-login (g2-login context))
           (frame-reference (current-frame-serial-number))
           (choice? (getf event-plist 'g2pvt-choice))
           (user-mode? (getf event-plist 'mode))
	   (symbolized-user-mode (symbolize user-mode?)))

      (when (is-in-ldap-mode-p)
        (check-user-ldap 
           (g2-user-name-for-this-workstation? current-workstation)  
           (getf event-plist 'user) 
           (getf event-plist 'pass)))

      (macrolet ((P (control-name slot-name)
                   `(put-symbol-valued-slot g2-login
                                            ',slot-name
                                            (getf event-plist ',control-name))))
        (P user g2-login-user-name?)
        (P pass g2-login-user-password?)
;        (P mode g2-login-user-mode)
        (P lang g2-login-specific-language-for-this-g2-window?))

      ;; This has to be done separately because the slot-value-compiler is doing
      ;; the validity checking. When it fails, the slot in g2-login is not even
      ;; set.
      (change-slot-value g2-login 'g2-login-user-mode symbolized-user-mode)

      (case choice?
        (ok     (do-g2-login-button 'end))
        (abort  (do-g2-login-button 'disconnect))
        (t      (do-g2-login-button 'cancel)))

      ;; If we didn't exit the g2-login context, then there is an error message,
      ;; so repost the dialog.
      (when (not (frame-has-been-reprocessed-p g2-login frame-reference))
        (post-native-login-dialog context #.mb-iconexclamation)))))

(defun symbolize (thing)
  (cond ((stringpw thing)
         (intern-wide-string (copy-wide-string-with-case-conversion thing :all)))
        ((symbolp thing)
         thing)))


;;;; Selection Handles


(define-event-handler update-mouse-cursor ((spot spot) (gensym-window window))
  ;; FIXME: This needs to push the new cursor, and pop back the old one instead
  ;; of 'default.
  (change-ui-property gensym-window 'mouse-cursor
                      (cond ((not (selection-handle-spot-p spot))
                             'default)
                            ((drag-selection-handle-permitted-p spot)
                             (selection-handle-mouse-cursor spot))
                            (t
                             'circle-slash))))

(defun drag-selection-handle-permitted-p (selection-handle-spot)
  (case (selection-handle-spot-type selection-handle-spot)
    (vertex (drag-connection-vertex-permitted-p (frame-represented? selection-handle-spot)))
    (resize (resize-block-permitted-p (frame-represented? selection-handle-spot)))
    (t (dwarn "Unknown selection handle: ~S" (selection-handle-spot-type selection-handle-spot)))))


(define-event-handler drag-selection-handle (spot mouse-pointer image-plane x-in-workspace y-in-workspace)
  ;; TODO: Restrictions (MOVE for the connection frame) or RESIZE?
  (when (selection-handle-spot-p spot)
    (let ((item-or-items
            (case (selection-handle-spot-type spot)
              (vertex (frame-represented? spot))
              (resize (compute-blocks-to-resize-from-selection
                        (frame-represented? spot)
                        (image-plane-current-selection image-plane))))))
      (when item-or-items
        (requeue-mouse-motion-event mouse-pointer)
        (begin-dragging-selection-handle
          image-plane
          mouse-pointer
          item-or-items
          (selection-handle-spot-type spot)
          (selection-handle-spot-handle spot)
          x-in-workspace y-in-workspace)))))

;; Assumes lead-item is resizeable?
(defun compute-blocks-to-resize-from-selection (lead-item selection)
  (let* ((blocks (compute-filtered-blocks-from-selection selection #'resize-block-permitted-p))
         (sublist (memq lead-item blocks)))
    ;; FIXME: Why are we doing this again?
    (when (and sublist (neq lead-item (first blocks)))
      (setf (car sublist) (first blocks)
            (first blocks) lead-item))
    blocks))

(defun resize-block-permitted-p (block)
  (and (change-size-permitted-p block)
       ;; FIXME: Which restriction?
       (non-menu-choice-permitted-p 'move-object block)))

;; Here to pick up do-selection-things
(defun draw-selection-handles-for-current-image-plane (left top right bottom)
  left top right bottom
  (let ((selection? (image-plane-current-selection current-image-plane)))
    (when selection?
      (do-selection-things (thing selection?)
        (unless (render-thing-in-xor-overlay-p thing)
          ;; TODO: Only if overlaps update rectangle.
          (let ((color (if (eq thing (%primary-selection selection?))
                           (primary-selection-color current-image-plane)
                           (secondary-selection-color current-image-plane))))
            (cond ((framep thing)
                   (draw-selection-handles-for-block thing color))
                  ((connection-p thing)
                   (draw-selection-handles-for-connection thing color))
                  ((text-cell-p thing)
                   (draw-selection-handles-for-text-cell thing color)))))))))


;;;; Disconnect callbacks routines

(defun-for-system-procedure g2-register-callback-on-twng-exit (g2-window callback)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (cond
      ((twng-window-p gensym-window)
       (add-twng-disconnect-callback gensym-window callback))
      (t
       (ui-stack-error "Passed window is not a TWNG window: ~NF" g2-window)))))

(defun-for-system-procedure g2-unregister-callback-on-twng-exit (g2-window callback)
  (let ((gensym-window (map-to-gensym-window-or-stack-error g2-window)))
    (cond
      ((twng-window-p gensym-window)
       (remove-twng-disconnect-callback gensym-window callback))
      (t
       (ui-stack-error "Passed window is not a TWNG window: ~NF" g2-window)))))

;; clear all disconnect callbacks
(defun-simple clear-all-twng-disconnect-callbacks ()
  (loop for g2-window being each class-instance of 'g2-window
    as gensym-window? = (map-g2-window-to-gensym-window g2-window)
	when (and gensym-window? (twng-window-p gensym-window?))
	  do (clear-twng-disconnect-callbacks gensym-window?)))

;; call disconnect callbacks
(defun-simple call-twng-disconnect-callbacks (gensym-window)
  (let ((g2-window (g2-window-for-gensym-window? gensym-window)))
    (loop for callback in (twng-disconnect-callbacks gensym-window)
      as callback-proc? =
         (get-callback-procedure callback "twng-disconnect-callback" '((class g2-window)) t nil t)
      when callback-proc?
        do (apply-kb-procedure callback-proc? (gensym-list g2-window)))))

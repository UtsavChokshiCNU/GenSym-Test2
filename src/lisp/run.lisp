;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module RUN

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David






;;;; Forward References in RUN


;; To COMP-UTILS
(declare-forward-reference current-computation-instance variable)


;; To CYCLES
(declare-forward-reference system-pause function)


;; To FILES
(declare-forward-reference read-kb function)
(declare-forward-reference clear-kb function)
(declare-forward-reference current-kb-pathname? variable)

;; To FILTERS
(declare-forward-references
  (reclaim-filter-list-function                         function filters)
  (non-menu-choice-permitted-p                          function filters)
  (make-new-alias                                       function filters)
  (global-keyboard-command-user-restrictions-function   function filters)
  (main-menu-user-restrictions-function                 function filters)
  (kb-configuration                                     variable filters)
  (kb-restrictions                                      variable filters))

;; To SETS
(declare-forward-reference invalid-user-name-p function)

;; TO COMMANDS0
(declare-forward-reference thing-selected-p function)

;; TO COMMANDS1
(declare-forward-reference native-login-dialog-p function)
(declare-forward-reference post-native-login-dialog function)
(declare-forward-reference cancel-native-login-dialog function)
(declare-forward-reference compute-category-members function)

;; To ACTIVATE
(declare-forward-reference existence-depends-on-p function)

;; To CONTROLS
(declare-forward-reference log-in-workstation function)
(declare-forward-reference log-out-workstation function)
(declare-forward-reference goto-frame-instance function)
(declare-forward-reference copy-gensym-window-attributes-into-g2-window function)

;; To VIEW-G2
#+maybe
(declare-forward-reference send-window-new-mode function)

;; To KB-MERGE
(declare-forward-reference read-kb-or-group-thereof function)

;; To KB-LOAD1
(declare-forward-reference get-or-make-default-kb-pathname function)

;; To KB-LOAD2
(declare-forward-reference read-element-for-kb function)

;; To KB-SAVE1
(declare-forward-reference write-char-for-kb function)
(declare-forward-reference write-element-for-kb function)

;; To PROC-UTILS
(declare-forward-reference dynamic-breakpoint-line-func function)
(declare-forward-reference dynamic-breakpoint-enabled-p function)

;; To STACK-KERN
(declare-forward-reference g2-event-loop function)
(declare-forward-reference run-scheduler-for-breakpoint function)
(declare-forward-reference get-dynamic-breakpoints-internal function)

;; To GRAMMAR6b
(declare-forward-reference sentence-end-punctuation? function)
(declare-forward-reference return-from-g2-set-g2-state function)
(declare-forward-reference notice-tw-disconnect function)
(declare-forward-reference graph-detailed-procedures function)
(declare-forward-reference list-callers-of-computation-instance function)
(declare-forward-reference validate-executing-statements-and-procedures function)
(declare-forward-reference raw-stack-error-1 function)
(declare-forward-reference enter-dialog function)
(declare-forward-reference system-resume function)
(declare-forward-reference confirm-or-cancel function)

(declare-forward-reference *current-computation-frame* variable)
(declare-forward-reference current-computation-instance variable)
(declare-forward-reference procedure-definition-function function)

(declare-forward-reference notice-tw-disconnect function)

(declare-forward-reference do-plist-checking function)
(declare-forward-reference do-plist-checking-again function)

(declare-forward-reference schedule-g2-legacy-heartbeat-tasks-if-necessary function)

(declare-forward-reference debug-clear-text-checksums variable)

(declare-forward-reference enter-dialog-for-t2 function)
(declare-forward-reference leave-dialog-for-t2 function)

;; To VIEW-G2
(declare-forward-reference remove-dialog-info-from-ui-client-interface-dialog-list function)

;; To GARMMAR7
(declare-forward-reference print-means-print-to-server-in-configurations-p function)

;; To COVERAGE
(declare-forward-reference initialize-code-coverage-module function)

;; To RUN
(declare-forward-reference add-or-delete-mode-name-from-directory-of-names function)

;; To THREAD-POND
(declare-forward-reference make-faction-pond function)
(declare-forward-reference thread-pond-start function)

;; To MQTT-POLL-WATCHER
(declare-forward-reference mqtt-poll-watcher function)

;;;; Running And Shutting Down G2



;;; Definition of the G2 (aka AB) System.

(define-system-access ab)

;; Change "ab" to "G2", here and below!



;; jh per bah, 9/27/91.  Added post-setjmp status to check for the presence of the
;; Chestnut setjmp bug and the efficacy of our fix for it.  Details on this bug
;; may be found under the definition of defun-allowing-unwind in BOOTSTRAP.  Note
;; that the messages are veiled, in case we forget to remove this before the
;; release.

;; jh, 12/27/91.  Removed call to post-setjmp-status, since it shows that the
;; setjmp fix was effective on all platforms.  We should probably retain these
;; simple functions in the code, so we can test subsequent Chestnut releases.  For
;; future reference, the following chart details which platform has problems with
;; setjmp as of this date.

;; jv, 7/27/07.  Removed obsolete platforms from chart.  No idea about setjmp
;; problems with remaining platforms.

;; platform        machine  problem with catch?  problem with unwind?
;; --------        -------  -------------------  --------------------
;; RS6000          Be       YES                  no
;; HP9000s700/800  Lr       no                   no
;; Sun4, Sparc     Tc       no                   no

#+(or chestnut chestnut-3) 
(defun-void throw-to-chestnut-catcher ()
  (throw 'catcher nil))

#+(or chestnut chestnut-3) 
(defun exhibit-chestnut-catch-reverts-locals-bug ()
  (let ((vulnerable-local 'initial-value))
    (ab-lisp::catch 'catcher ;without ab-lisp::catch, we'll get ineradicable warnings
      (setq vulnerable-local 'side-effected-value)
      (throw-to-chestnut-catcher))
    (eq vulnerable-local 'initial-value)))

#+(or chestnut chestnut-3) 
(defun-allowing-unwind verify-chestnut-catch-reverts-locals-fix 
		       ()
  (let ((vulnerable-local 'initial-value))
    (catch 'catcher
	   (setq vulnerable-local 'side-effected-value)
	   (throw-to-chestnut-catcher))
    (eq vulnerable-local 'side-effected-value)))

;#+(or chestnut chestnut-3)
;(defun exhibit-chestnut-unwind-protect-reverts-locals-bug ()
;  (let ((vulnerable-local 'initial-value))
;    (ab-lisp::catch 'catcher    ;we'll get ineradicable warnings without ab-lisp::catch
;      (ab-lisp::unwind-protect  ; or ab-lisp::unwind-protect
;	(progn (setq vulnerable-local 'side-effected-value)
;	       (throw-to-chestnut-catcher))
;	(eq vulnerable-local 'initial-value)))))

;; Rick @ Chestnut, 12/3/94, states:
;;
;; "Also, your unwind-protect example [above] wasn't right: the vulnerable-local
;; variable didn't get protected, because it didn't need to be, since it
;; appeared after the unwind-protect body only in a non-side-effecting form
;; whose value wasn't used.  I suggest changing this example to:
;;
;;(defun-unprotected exhibit-chestnut-unwind-protect-reverts-locals-bug ()
;;  (let ((vulnerable-local 'initial-value))
;;    (catch 'catcher
;;      (unwind-protect
;;        (progn (setq vulnerable-local 'side-effected-value)
;;               (throw-to-chestnut-catcher))
;;        (print (eq vulnerable-local 'initial-value))))))
;;
;; There is a separate issue, though, of generating the correct setjmp
;; protection code for variables that need it.  Currently, this is done by GC
;; protecting the variables, but this can't be used for for non-object
;; variables.  I plan to implement this by using "volatile" on all variables
;; that need setjmp protection but not GC protection."

;; jh, 3/15/94.  Note that post-setjmp-status does not detect bugs of the type
;; described by Rick in the last paragraph, namely, failure to stack-protect
;; variables declared fixnum, double-float and the like, which translate to C
;; longs and doubles, respectively, rather than C variables of type Object.

#+(or chestnut chestnut-3)
(defun exhibit-chestnut-unwind-protect-reverts-locals-bug ()
  (let ((vulnerable-local 'initial-value)
	(buggy-p nil))
    (ab-lisp::catch 'catcher    ;we'll get ineradicable warnings without ab-lisp::catch
      (ab-lisp::unwind-protect  ; or ab-lisp::unwind-protect
	   (progn (setq vulnerable-local 'side-effected-value)
		  (throw-to-chestnut-catcher))
        (if (eq vulnerable-local 'initial-value)
	    (setq buggy-p t)
	    (setq buggy-p nil))))
    buggy-p))

#+(or chestnut chestnut-3)
(defun noop-cleanup-form ()
  nil)

#+(or chestnut chestnut-3)
(defun-allowing-unwind verify-chestnut-unwind-protect-reverts-locals-fix
		       ()
  (let ((vulnerable-local 'initial-value))
    (catch 'catcher
	   (unwind-protect
	     (progn (setq vulnerable-local 'side-effected-value)
		    (throw-to-chestnut-catcher))
	     (noop-cleanup-form)))
    (eq vulnerable-local 'side-effected-value)))

#+(or chestnut chestnut-3)
(defun post-setjmp-status ()
  (if (exhibit-chestnut-catch-reverts-locals-bug)
      (format t "~&Catch noted.~%")                         ;catch bug present
      (format t "~&Catch complete.~%"))                     ;catch bug absent
  (if (verify-chestnut-catch-reverts-locals-fix)
      (format t "~&Throw complete.~%")                      ;catch fix works
      (format t "~&Throw noted.~%"))                        ;catch fix fails

  (if (exhibit-chestnut-unwind-protect-reverts-locals-bug)
      (format t "~&Unwind noted.~%")                        ;uw-protect bug present
      (format t "~&Unwind complete.~%"))                    ;uw-protect bug absent
  (if (verify-chestnut-unwind-protect-reverts-locals-fix)
      (format t "~&Protect complete.~%")                    ;uw-protect fix works
      (format t "~&Protect noted.~%"))                      ;uw-protect fix fails
  )

;;;
;;; Function is-in-ldap-mode-p check whether -useldap command line parameter 
;;; is set during g2 start
;;;
(def-gensym-c-function g2-is-in-ldap-mode-in-c
                       (:fixnum-int "g2_check_ldap_mode")
  ())

(defun is-in-ldap-mode-p ()
(let ((ldap-mode? nil))
    ;; All this is irrelevant unless the G2 is secure. If it
    ;; isn't we will always return nil
    (when (g2-secure-p)
      ;; lets try to check ldap
	(unless (= 0 (g2-is-in-ldap-mode-in-c))
	  (setq ldap-mode? t))
      )
    ldap-mode? ))

;;; The void function `augment-window-parameters-plist-of-initial-gensym-window'
;;; mutates the window-parameters-plist of its gensym-window argument by adding
;;; the G2 user-name and password, if either is present in the command-line that
;;; launched G2.  The command-line keyword "-user-name" specifies the G2 user
;;; name and the command-line keyword "-password" specifies the G2 password.
;;; The G2 password is extracted from the command-line in the clear; maintaining
;;; the secrecy of this password is the responsibility of the G2 end-user.  Also
;;; note that G2 user names and passwords are completely distinct from those
;;; present in the host operating system.

;;; rh & jh, 12/29/95.  Also note that the user-name and password command-line
;;; arguments are available through the system procedure
;;; get-command-line-argument-from-launch.  We need (at least) to document this,
;;; and possibly remedy it (by removing the tokens from
;;; unix-command-line-arguments after use).

(defun-void augment-window-parameters-plist-of-initial-gensym-window
    (initial-gensym-window)
  (setf (window-parameters-plist initial-gensym-window)
	(nconc
	  (window-parameters-plist initial-gensym-window)
	  (get-command-line-arguments)))
  (let* ((window-parameters-plist
	   (window-parameters-plist initial-gensym-window))
	 (g2-user-name?
	   (getf window-parameters-plist 'user-name))
	 (g2-password?
	   (getf window-parameters-plist 'password)))
    (when (and g2-password? g2-user-name?)
      ;; See md5-password.
      (setf (window-parameters-plist initial-gensym-window)
	    (mutate-gensym-plist
	      window-parameters-plist
	      'md5-password
	      (encode-password-via-md5
		g2-user-name?
		(get-command-line-keyword-argument #w"PASSWORD")
		nil))))))




(defvar initial-java-class nil)



;;; Run-ab runs G2.

(defun-for-top-level run-ab (gensym-window-for-workstation?)
  (initialize-scheduler)
  (initialize-gensym-time)

  #-chestnut-3 ; from g2-event-cycle-handling-windows-quit
  (initialize-event-cycle-call-handlers)

  (unless (authorize-ab) (shutdown-or-exit))
  (initialize-optional-modules)

  ;; This makes class membership testing work, for system defined classes.
  (assign-class-bit-numbers-and-vectors-to-system-classes)
  (switch-to-new-empty-kb)		; instead load some KB automatically?
  
  ;added in Gensym-343
  (set-icp-tracing-level-from-command-line)
  ;end of changes

  ;; I moved the call to CHECK-WINDOWS-AUTHORIZATION higher so that the 
  ;; initial window does not flash for less than a second. - jpg 12/26/01 
  (check-windows-authorization) ;Added (jh, 7/12/91).

  (when gensym-window-for-workstation?
    (augment-window-parameters-plist-of-initial-gensym-window
      gensym-window-for-workstation?)
    (set-up-workstation gensym-window-for-workstation?)
    (lay-out-window gensym-window-for-workstation?) ; makes or revises panes
    (make-window-visible gensym-window-for-workstation?))

  (let ((current-draw-paper-p nil))			    ; Makes for a prettier startup
    (display-credits))

  (check-system-time-against-primeval-time)
  (let ((*write-console-p* t))
    (report-listener-info-to-parent-window)) ;Added (jh, 6/28/91).
  (exit-if-system-time-too-early g2)
  (update-system-tray-icon)		; Added -fmw, 10/5/05

  (setq debug-clear-text-checksums (get-command-line-flag-argument #w"debug-clear-text-checksums"))

  (when (or (no-local-window-p)
	    (running-as-noninteractive-service-p))
    (set-flag-permitting-free-floating-authorization))

  #+clear-text (do-plist-checking) ;enable-loading-in-clear-text-function
  #+clear-text (do-plist-checking-again) ;enable-saving-in-clear-text-function
  
  (ne-enqueue-scheduler-event)

  (maybe-schedule-service-workstations t)
  (schedule-g2-legacy-heartbeat-tasks-if-necessary)
  #+(and chestnut-3 translator)
  (setq trun::*gc-silence* nil)

  ;; TODO: how to terminate these threads before the main thread quits?
  #+SymScale
  (start-scheduler-workers)

  #+mtg2
  (progn
    (setf other-factions-thread-pool (make-faction-pond))
    (thread-pond-start other-factions-thread-pool))

  (loop do
    (do-error-trapping
      (g2-event-loop))))

#+(and lispworks (not translator))
(lw:defadvice (launch-ab launch-ab-in-new-thread :around) ()
  "Run G2 in new threads when being called within IDE"
  (if (env:tty-environment-p)
      (lw:call-next-advice)
    (progn
      (format t "Launching G2 in new threads ...~%")
      (setf sys:*stack-overflow-behaviour* nil)
      (let ((sys:*sg-default-size* 256000) (sys:*stack-overflow-behaviour* nil))
        (mp:process-run-function "G2" nil #'launch-ab)))))

;;; The function `running-as-noninteractive-service-p' is true if the current
;;; process is running as a noninteractive NT service, which means that it has
;;; an invisible desktop. We can treat this in some ways like -no-window.

(defun running-as-noninteractive-service-p () ; I guess we're not bothering with devious names anymore.
  (=f (c-noninteractive-service-p) 1))

(def-gensym-c-function c-noninteractive-service-p
    (:fixnum-int "g2ext_noninteractive_service_p")
  ())


;;;; System Tray


;;; The function `update-system-tray-icon' updates the icon in the system tray
;;; to reflect the current G2 run state. It is a no-op except on Windows
;;; platforms.

(defun update-system-tray-icon ()
  (let ((icon-name? (case (current-g2-run-state)
		      (reset "reset")
		      (paused "paused")
		      (running "running")
		      (abort "abort"))))
    #-chestnut-3
    (declare (ignore icon-name?))
    #+chestnut-3
    (when icon-name?
      (c-update-system-tray -1 icon-name? #w""))))

(def-gensym-c-function c-update-system-tray
    (:fixnum-int "g2ext_update_system_tray")
  ((:fixnum-int icon)
   (:string icon-name)
   (:wide-string tooltip)))



;;;; Standard Workstation Event Interpretations


(defun find-ultimate-superplane-in-stack-of-coupled-image-planes (image-plane)
  (loop with ultimate-superplane-so-far = image-plane
	for superplane? = (superplane? ultimate-superplane-so-far)
	while superplane?
	do (setq ultimate-superplane-so-far superplane?)
	finally (return ultimate-superplane-so-far)))

;; Given the current usage of G2, when a stack of coupled image planes is used,
;; it is guarranteed that if there is a kb-workspace in the stack, it will
;; appear as the base plane in the stack.  For restrictions to work properly on
;; the superplanes of the kb-workspace (superplanes are closer to the glass)
;; this representation invariant must be maintained.  PGA - 5/30/95

(defun find-base-plane-in-stack-of-coupled-image-planes (image-plane)
  (loop with ultimate-subplane-so-far = image-plane
	for subplane? = (subplane? ultimate-subplane-so-far)
	while subplane?
	do (setq ultimate-subplane-so-far subplane?)
	finally (return ultimate-subplane-so-far)))

(defmacro following-lead-image-plane-in-stack-of-coupled-image-planes
    ((lead-image-plane) &body body)
  (avoiding-variable-capture
      (lead-image-plane
	&aux lead-plane-x-origin lead-plane-y-origin
	     lead-plane-x-scale lead-plane-y-scale)
    `(let ((,lead-plane-x-origin
	     (x-origin-of-workspace-in-window-of-image-plane ,lead-image-plane))
	   (,lead-plane-y-origin
	     (y-origin-of-workspace-in-window-of-image-plane ,lead-image-plane))
	   (,lead-plane-x-scale (image-x-scale ,lead-image-plane))
	   (,lead-plane-y-scale (image-y-scale ,lead-image-plane)))
       (prog1 (progn . ,body)
	 ;; Then process other planes relative to lead plane.
	 (transform-subplanes-per-lead-plane
	   (find-ultimate-superplane-in-stack-of-coupled-image-planes ,lead-image-plane)
	   ,lead-image-plane
	   ,lead-plane-x-origin ,lead-plane-y-origin
	   ,lead-plane-x-scale ,lead-plane-y-scale)))))




;;; The substitution-macro `name-of-shift-image-plane-action?' returns T for
;;; image-plane actions which merely shift the image-plane's origin.  For these
;;; case we call move-image-plane rather than transform-image, which is the
;;; only way to get the screen-to-screen bitblt optimization.

(def-substitution-macro name-of-shift-image-plane-action? (action-name)
  (memq action-name '(shift-left-ten-percent
		      shift-right-ten-percent shift-left-one-percent shift-right-one-percent
		      shift-up-ten-percent shift-down-ten-percent shift-up-one-percent
		      shift-down-one-percent center-origin)))


;;; The function `handle-image-plane-event' is called from the various new UI
;;; commands which mess with image planes. ... events upon subplanes are handled
;;; as though they were on their superplane.

;;; The new strategy is: If a size or position change is required, first resize
;;; the plane with the mouse focus.  Then resize all the other planes
;;; accordingly.

(defun handle-image-plane-event (action-name image-plane x-in-window y-in-window)
  ;; Find most superior superplane.
  ;; Also, assume that only one of the planes in the super-sub hierarchy is a kb-workspace and locate it.
  (let* ((plane-with-mouse-focus image-plane)
	 (lead-plane (find-base-plane-in-stack-of-coupled-image-planes plane-with-mouse-focus)))
    ;; Bind original values for lead-plane
    ;; Focus here means simply the mouse click was over that plane.
    (let ((can-handle? t)
	  (require-maximally-within-pane? nil))

      (multiple-value-setq (can-handle? require-maximally-within-pane?)
	(test-restrictions-for-image-plane-action
	  action-name lead-plane))
      ;; Handle the lead plane (kb-workspace-plane?, if any, otherwise
      ;; focus-plane) first.  (Consider processing focus plane as the "lead
      ;; plane"; however, that approach has problems, especially with handling
      ;; of require-maximally-within-pane?)
      (when can-handle?

	(cond ((name-of-shift-image-plane-action? action-name)
	       (unless (embedded-image-plane-p image-plane) ; No shifting (as opposed to scrolling) allowed.
		 (handle-shift-image-plane-action
		   image-plane action-name require-maximally-within-pane?)))

	      (t
	       (following-lead-image-plane-in-stack-of-coupled-image-planes
		 (lead-plane)
		 (handle-image-plane-event-inner
		   action-name lead-plane
		   x-in-window y-in-window
		   require-maximally-within-pane?))))
	(let ((workspace (workspace-on-image-plane? image-plane)))
	  (when workspace
	    (trigger-user-icon-movement-rules-for-blocks workspace)))))))


(defun transform-subplanes-per-lead-plane
    (subplane lead-plane
	      old-lead-plane-x-origin old-lead-plane-y-origin
	      old-lead-plane-x-scale old-lead-plane-y-scale)
  (cond
    ;; The image plane with the mouse focus does not need to refer to relation or position of others.
    ((eq subplane lead-plane) nil)    
    ;; Already processed now only set appropriate layer.
    ;; set layer? Don't worry about this yet.
    
    ;; The image planes without mouse focus must position and scale themselves
    ;; relative to the one with focus.  We don't maintain the relative scale;
    ;; instead, we simply use the scale of the lead plane.
    (t
     (transform-image
       subplane nil
       (image-x-scale lead-plane) (image-y-scale lead-plane)
       nil nil
       0 0
       (+r (x-origin-of-workspace-in-window-of-image-plane lead-plane)
	   (delta-x-in-window
	     ;; In practice, we always have the riding workspace x offset,
	     ;; which is desirable because it is not subject to roundoff
	     ;; error/drift as scales change.
	     (or (get-slot-value-if-any
		   (workspace-on-image-plane? subplane)
		   'riding-workspace-x-offset?)
		 (delta-x-in-workspace
		   (-r (x-origin-of-workspace-in-window-of-image-plane subplane)
		       old-lead-plane-x-origin)
		   old-lead-plane-x-scale))
	     (image-x-scale lead-plane)))
       (+r (y-origin-of-workspace-in-window-of-image-plane lead-plane)
	   (delta-y-in-window
	     (or (get-slot-value-if-any
		   (workspace-on-image-plane? subplane)
		   'riding-workspace-y-offset?)
		 (delta-y-in-workspace
		   (-r (y-origin-of-workspace-in-window-of-image-plane subplane)
		       old-lead-plane-y-origin)
		   old-lead-plane-y-scale))
	     (image-y-scale lead-plane)))
       nil nil nil nil nil nil)))
  (let ((subplane? (subplane? subplane)))
    (if subplane?
	(transform-subplanes-per-lead-plane
	  subplane?
	  lead-plane old-lead-plane-x-origin old-lead-plane-y-origin
	  old-lead-plane-x-scale old-lead-plane-y-scale))))




(defun test-restrictions-for-image-plane-action
    (action-name image-plane)
  (let* ((workspace-on-image-plane	; never nil here
	   (workspace-on-image-plane? image-plane))	 
	 
	 ;; user restriction logic:
	 (non-kb-workspace-p
	   (frame-of-class-p workspace-on-image-plane 'non-kb-workspace))
	 (scale-workspace-allowed-p
	   (non-menu-choice-permitted-p 'scale-workspace workspace-on-image-plane))
	 (move-workspace-allowed-p
	   (non-menu-choice-permitted-p 'move-workspace workspace-on-image-plane))
	 (can-scale?
	   (or non-kb-workspace-p scale-workspace-allowed-p))
	 (can-move?
	   (and (or non-kb-workspace-p move-workspace-allowed-p)
		(not (image-plane-fixed-in-place-p image-plane))))
	 (require-maximally-within-pane?
	   (and (not non-kb-workspace-p)
		(not
		  (non-menu-choice-permitted-p
		    'move-workspaces-beyond-window-margin
		    workspace-on-image-plane)))))
    (values
      (case action-name
	((scale-to-fit
	   maximum-scale-to-fit
	   full-scale normalized-full-scale
	   one-quarter-the-scale four-times-the-scale
	   twenty-percent-smaller twenty-percent-bigger
	   twenty-percent-narrower twenty-percent-wider)
	 (and can-scale?
	      (or can-move?
		  (image-plane-fixed-in-place-p image-plane))))
	((shift-left-ten-percent
	   shift-right-ten-percent shift-left-one-percent shift-right-one-percent
	   shift-up-ten-percent shift-down-ten-percent shift-up-one-percent
	   shift-down-one-percent center-origin)
	 can-move?))			; different test when scrolled??!!
      require-maximally-within-pane?)))



;;; The function `handle-shift-image-plane-action' handles image-plane actions
;;; which merely move the image-plane's origin.

(defun handle-shift-image-plane-action
    (image-plane action-name require-maximally-within-pane?)
  (multiple-value-bind (x-in-workspace? y-in-workspace? x-in-window? y-in-window?)
      (decode-image-plane-shift-action image-plane action-name)

    (let ((dx-in-window
	    (if (and x-in-workspace? x-in-window?)
		(-f x-in-window? (x-in-window-for-image-plane
				   x-in-workspace? image-plane))
		0))
	  (dy-in-window
	    (if (and y-in-workspace? y-in-window?)
		(-f y-in-window? (y-in-window-for-image-plane
				   y-in-workspace? image-plane))
		0)))

      ;; As part of the documented 3.0 behavior, raise the image-plane to the
      ;; top before moving.
      (raise-image-plane-to-top image-plane)
      
      ;; Move-image-plane takes care of superplane/subplane coupling.
      (move-image-plane image-plane dx-in-window dy-in-window)

      (require-that-image-plane-be-visible image-plane require-maximally-within-pane?)

      ;; Follow with the mouse.
      (let ((new-mouse-x
	      (if (eq action-name 'center-origin)
		  (x-origin-of-workspace-in-window-of-image-plane image-plane)
		  (+f (x-in-window-of-mouse? current-workstation)
		      dx-in-window)))
	    (new-mouse-y
	      (if (eq action-name 'center-origin)
		  (y-origin-of-workspace-in-window-of-image-plane image-plane)
		  (+f (y-in-window-of-mouse? current-workstation)
		      dy-in-window))))

	(set-cursor-position
	  (maxr (left-edge-of-pane-in-window image-plane)
		(minr (-r (right-edge-of-pane-in-window image-plane) 1)
		      new-mouse-x))
	  (maxr (top-edge-of-pane-in-window image-plane)
		(minr (-r (bottom-edge-of-pane-in-window image-plane) 1)
		      new-mouse-y)))))))


(def-substitution-macro midline-x-of-window (gensym-window)
  (halfr
    (+r (left-edge-of-window gensym-window)
	(right-edge-of-window gensym-window))))

(def-substitution-macro midline-y-of-window (gensym-window)
  (halfr
    (+r (top-edge-of-window gensym-window)
	(bottom-edge-of-window gensym-window))))

(def-substitution-macro midline-x-of-pane (image-plane)
  (halfr
    (+r (left-edge-of-pane-in-window image-plane)
	(right-edge-of-pane-in-window image-plane))))

(def-substitution-macro midline-y-of-pane (image-plane)
  (halfr
    (+r (top-edge-of-pane-in-window image-plane)
	(bottom-edge-of-pane-in-window image-plane))))

(def-substitution-macro width-of-pane (image-plane)
  (-r (right-edge-of-pane-in-window image-plane)
      (left-edge-of-pane-in-window image-plane)))

(def-substitution-macro height-of-pane (image-plane)
  (-r (bottom-edge-of-pane-in-window image-plane)
      (top-edge-of-pane-in-window image-plane)))

(def-substitution-macro width-of-image-plane (image-plane)
  (-r (right-edge-of-image-in-window image-plane)
      (left-edge-of-image-in-window image-plane)))

(def-substitution-macro height-of-image-plane (image-plane)
  (-r (bottom-edge-of-image-in-window image-plane)
      (top-edge-of-image-in-window image-plane)))

;; Note that width-of-image and height-of-image are accessors for the class
;; image-definition, a completely unrelated entity.



(defun handle-image-plane-event-inner
    (action-name image-plane cursor-x-in-window cursor-y-in-window
		 require-maximally-within-pane?)
  (let* ((original-x-origin-of-workspace-in-window
	   (x-origin-of-workspace-in-window-of-image-plane image-plane))
	 (original-y-origin-of-workspace-in-window
	   (y-origin-of-workspace-in-window-of-image-plane image-plane))
	 (workspace-on-image-plane	; never nil here
	   (workspace-on-image-plane? image-plane))
	 (midline-x-of-pane
	   (midline-x-of-pane image-plane))
	 (midline-x-of-workspace
	   (midline-x-of-block workspace-on-image-plane))
	 (midline-y-of-pane
	   (midline-y-of-pane image-plane))
	 (midline-y-of-workspace
	   (midline-y-of-block workspace-on-image-plane)))
    (case action-name
      ((scale-to-fit maximum-scale-to-fit)
       (let ((transform-image-operation-hint 'scale-to-fit))
	 (transform-image			;   parts from below -- needs to
	   image-plane nil			;   be done with the transform!!!
	   nil nil
	   (if (eq action-name 'maximum-scale-to-fit)
	       #.(- (convert-to-magnification-at-compile-time 1.025))
	       #.(convert-to-magnification-at-compile-time 1.025))
	   nil
	   midline-x-of-workspace midline-y-of-workspace
	   midline-x-of-pane midline-y-of-pane
	   nil nil nil nil
	   t)
	 (require-that-image-plane-be-visible
	   image-plane require-maximally-within-pane?)))
      ((full-scale normalized-full-scale
		   one-quarter-the-scale four-times-the-scale
		   twenty-percent-smaller twenty-percent-bigger
		   twenty-percent-narrower twenty-percent-wider)
       (let* ((x-magnification? nil)	; if needed, set below and used further below
	      (old-image-x-scale (image-x-scale image-plane))
	      (old-image-y-scale (image-y-scale image-plane))
	      (new-image-x-scale?
		(case action-name
		  (full-scale
		   (get-default-image-x-scale image-plane))
		  (normalized-full-scale
		   (normalized-scale))
		  (t (magnify
		       old-image-x-scale
		       (setq x-magnification?
			     (case action-name
			       (one-quarter-the-scale
				;; by "quarter" now we mean the area size.    --binghe, 2012/12/17
				#.(convert-to-magnification-at-compile-time 0.5))
			       (four-times-the-scale
				;; by "four times" now we mean the area size. --binghe, 2012/12/17
				#.(convert-to-magnification-at-compile-time 2))
			       ((twenty-percent-smaller twenty-percent-narrower)
				;;   22.7% smaller is near inverse of 29.3% bigger
				#.(convert-to-magnification-at-compile-time 0.773))
			       ((twenty-percent-bigger twenty-percent-wider)
				#.(convert-to-magnification-at-compile-time 1.293))))))))
	      (new-image-y-scale?
		(case action-name
		  (full-scale
		   (get-default-image-y-scale image-plane))
		  (normalized-full-scale
		   (normalized-scale))
		  (t (case action-name
		       ((one-quarter-the-scale
			  four-times-the-scale
			  twenty-percent-smaller
			  twenty-percent-bigger)
			(magnify
			  old-image-y-scale
			  x-magnification?))))))
	      (x-scale-to-be (or new-image-x-scale? old-image-x-scale))
	      (y-scale-to-be (or new-image-y-scale? old-image-y-scale))
	      (single-view-p
		;; The alternative approach should be dropped. It was mostly
		;; used to make the zooming centered with respect to the focus
		;; image plane.  We now drive this from the commands that need
		;; that behavior.  See zoom-in, for example. It creates an event
		;; with the desired centered coordinates. (MHD 1/23/03)
		nil
		;; alternative: (single-workspace-view-image-plane-p image-plane)
		)
	      (scaled-x-in-midpane-in-workspace
		(delta-x-in-workspace
		  (-r midline-x-of-pane original-x-origin-of-workspace-in-window)
		  old-image-x-scale))
	      (scaled-y-in-midpane-in-workspace
		(delta-y-in-workspace
		  (-r midline-y-of-pane original-y-origin-of-workspace-in-window)
		  old-image-y-scale))
	      (image-left-border-width
		(-r (left-edge-of-workspace-area-in-window image-plane)
		    (left-edge-of-image-in-window image-plane)))
	      (image-right-border-width
		(-r (right-edge-of-workspace-area-in-window image-plane)
		    (right-edge-of-image-in-window image-plane)))
	      (image-top-border-width
		(-r (top-edge-of-workspace-area-in-window image-plane)
		    (top-edge-of-image-in-window image-plane)))
	      (image-bottom-border-width
		(-r (bottom-edge-of-workspace-area-in-window image-plane)
		    (bottom-edge-of-image-in-window image-plane)))
	      (image-fits-widthwise-in-view-p
		(<r (+r image-left-border-width image-right-border-width
			;; review issues with max/min & with magnification!!
			(delta-x-in-window
			  (width-of-block workspace-on-image-plane)
			  x-scale-to-be))
		    (width-of-pane image-plane)))
	      (image-fits-heightwise-in-view-p
		(<=r (+r image-top-border-width image-bottom-border-width
			 ;; review issues with max/min & with magnification!!
			 (delta-y-in-window
			   (height-of-block workspace-on-image-plane)
			   y-scale-to-be))
		     (height-of-pane image-plane)))
	      (x-in-window
		(if single-view-p midline-x-of-pane cursor-x-in-window))
	      (y-in-window
		(if single-view-p midline-y-of-pane cursor-y-in-window))
	      (x-in-workspace ; bind after relevant image-plane is known	   
		(if single-view-p
		    (if image-fits-widthwise-in-view-p
			midline-x-of-workspace
			scaled-x-in-midpane-in-workspace)
		    (delta-x-in-workspace
		      (-r x-in-window original-x-origin-of-workspace-in-window)
		      old-image-x-scale)))
	      (y-in-workspace
		(if single-view-p
		    (if image-fits-heightwise-in-view-p
			midline-y-of-workspace
			scaled-y-in-midpane-in-workspace)
		    (delta-y-in-workspace
		      (-r y-in-window original-y-origin-of-workspace-in-window)
		      old-image-y-scale)))
	      (transform-image-operation-hint action-name))
	 (transform-image
	   image-plane nil new-image-x-scale? new-image-y-scale? nil nil
	   x-in-workspace y-in-workspace x-in-window y-in-window)
	 (unless single-view-p
	   (require-that-image-plane-be-visible
	     image-plane require-maximally-within-pane?))))

      ((shift-left-ten-percent
	 shift-right-ten-percent shift-left-one-percent shift-right-one-percent
	 shift-up-ten-percent shift-down-ten-percent shift-up-one-percent
	 shift-down-one-percent center-origin)
       #+development (cerror "Ignore it" "Should have called handle-shift-image-plane-action")))))

;; Note A: throw a bone to edit-in-place -- should be supported in panes, but it
;; ain't.
;; 
;; Instead of the "bone", add proper support for super/subplanes is PANES, i.e.,
;; transform-image, which must do to the "superplane" the 'same' transformation
;; as to the subplane!  
;;
;; The "bone" thrown to edit-in-place does not work at all for the "fitting"
;; operations (Meta-., Control-.) or for the center-in-origin operation.  It's
;; better than before, though. (MHD 8/28/94)
;;
;; Fix thinko -- subplane => superplane?; superplane? => subplanes !!
;;
;; (MHD 3/14/94)






;;; Decode-image-plane-shift-action ... is a subfunction of handle-image-plane-
;;; event.

(defun decode-image-plane-shift-action (image-plane action-name)
  (let ((x-in-workspace nil)
	(y-in-workspace nil)
	(x-in-window nil)
	(y-in-window nil))
    (case action-name
      (center-origin
       (setq x-in-workspace 0)
       (setq y-in-workspace 0)
       (setq x-in-window (halfr (+r (left-edge-of-pane-in-window image-plane)
				    (right-edge-of-pane-in-window image-plane))))
       (setq y-in-window (halfr (+r (top-edge-of-pane-in-window image-plane)
				    (bottom-edge-of-pane-in-window image-plane)))))

      ((shift-left-ten-percent shift-left-one-percent
	shift-right-ten-percent shift-right-one-percent)
       (setq x-in-workspace 0)
       (setq x-in-window
	     (+r (x-origin-of-workspace-in-window-of-image-plane image-plane)
		 (round				; use width-of-pane macro or slot?
		   (-r (right-edge-of-pane-in-window image-plane)
		       (left-edge-of-pane-in-window image-plane))
		   (case action-name
		     (shift-left-ten-percent -10)
		     (shift-left-one-percent -100)
		     (shift-right-ten-percent 10)
		     (t 100)))))) ; shift-right-one-percent
      ((shift-up-ten-percent shift-up-one-percent
	shift-down-ten-percent shift-down-one-percent)
       (setq y-in-workspace 0)
       (setq y-in-window
	     (+r (y-origin-of-workspace-in-window-of-image-plane image-plane)
		 (round
		   (-r (bottom-edge-of-pane-in-window image-plane)
		       (top-edge-of-pane-in-window image-plane))
		   (case action-name
		     (shift-up-ten-percent -10)
		     (shift-up-one-percent -100)
		     (shift-down-ten-percent 10)
		     (t 100))))))) ; shift-down-one-percent
    (values
      x-in-workspace y-in-workspace      
      x-in-window y-in-window)))



;;;; Hooks into top-level 



;;; The function `run-top-level-event-handler' looks up the top-level event
;;; handler which matches the given mouse-pointer, and runs it if there is
;;; one.

(define-event-handler run-top-level-event-handler (mouse-pointer)
  (let* ((top-level-context
	   (find-workstation-context 'top-level))
	 (event-interpretation?
	   (lookup-key-in-context
	     top-level-context
	     (key-code-of-mouse-pointer mouse-pointer)
	     (stack-of-spots mouse-pointer))))

    (when event-interpretation?
      (run-event-handler event-interpretation? mouse-pointer)
      (reclaim-event-interpretation event-interpretation?))))



;;;; Picking Objects from Workspaces



;;; `Find-object-near-mouse' finds the nearest block or connection near the mouse
;;; in a given workspace.  If a block is found that is "near enough", it is always
;;; returned in preference to a connection, no matter how close the connection is.
;;; Typically, this behaviour helps to distinguish loose ends of connections
;;; (blocks) from their connections. If there is an object close enough, it is
;;; returned as the first value, and the second value returned is the distance it
;;; was from the mouse, in workspace units.

;;; Image-plane must have a workspace.

;;; To be "near enough", objects must be no further away than the sum of
;;; `scalable-mouse-leeway' scaled by image-x-scale, and `constant-mouse-leeway'.
;;;
;;; Scalable-mouse-leeway is scaled as the inverse of the image-x-scale of the
;;; image plane. (This might be unsatisfactory if the x scale differs widely from
;;; the y scale or if the delta-x-in-workspace scales very differently from
;;; delta-y-in-workspace, but no improvements are planned for this at present.)
;;; 
;;; The addition of the small constant constant-mouse-leeway ensures that the
;;; object can be found a very small scales, where the result of scaling scalable-
;;; mouse-leeway approaches zero.
;;; 
;;; Note that when comparing distances in the workspace coordinate system, you
;;; simply use
;;;
;;;    (delta-x-in-workspace
;;;      (+r (delta-x-in-window constant-mouse-leeway image-x-scale)
;;;          scalable-mouse-leeway)
;;;      image-x-scale)
;;;
;;; which, at "normalized scale", is simply the sum of scalable-mouse-leeway and
;;; constant-mouse-leeway.  A convenience function, `mouse-leeway-in-workspace',
;;; computes this sum at any given scale.

;;; Scalable-mouse-leeway is currently defined as 7 workspace units, and constant-
;;; mouse-leeway is currently defined as 3 workspace units.  These are special
;;; variables (parameters).

;;; Objects-to-not-consider? is a list of objects to exclude from the search.  The
;;; caller is responsible for recycling any of its conses, if they must be recycled.
;;; Classes-of-objects-to-not-consider? is analagous: it excludes objects whose class
;;; is a subclass of any element of the list, which should be a list of classes.

;;; Block-to-search is typically a workspace.  If it is not a workspace, then it
;;; may itself be returned, provided that the mouse is within it or within the
;;; allowed distance from it.

 
;;; ... Objects will not be picked if the current x scale is less than minimum-x-scale-
;;; for-picking and either they are connections or either their width or their height
;;; at the current x scale is less than minimum-width-for-picking-in-window-units.
;;; [This may be changed in the future to provide a separate minimum y scale parameter
;;; and/or a separate height-in-window-units parameter.  Also, connections should
;;; obviously be handled more subtly.]

;;; Name boxes are not picked if their text is not visible.

(defparameter scalable-mouse-leeway 7)

(defparameter constant-mouse-leeway 3)

(defun-simple mouse-leeway-in-workspace (image-x-scale)  
  (delta-x-in-workspace
    (+r (delta-x-in-window constant-mouse-leeway image-x-scale)
	scalable-mouse-leeway)
    image-x-scale))


;;; The parameter `testing-mouse-track-distances-for-development?', in
;;; development only, is bound to nil by default.  When set to true, in
;;; development, it enables the code in
;;; `visualize-picking-rectangle-if-called-for', called from the mouse picking
;;; code, to draw rectangle showing the picking area.
;;; visualize-picking-rectangle-if-called-for is a substitution macro defined
;;; in all systems, but it's a noop except in development.

#+development
(defvar testing-mouse-track-distances-for-development? nil)

#+development
(defun-allowing-unwind visualize-picking-rectangle-if-called-for
    (image-plane mouse-x-in-workspace mouse-y-in-workspace)
  (when testing-mouse-track-distances-for-development?
    (with-raw-window-transform-and-draw-area
	((gensym-window-for-image-plane image-plane))
      (with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
	(on-image-plane (image-plane)
	  (draw-rectangle-outline-in-current-image-plane
	    (-w mouse-x-in-workspace constant-mouse-leeway)
	    (-w mouse-y-in-workspace constant-mouse-leeway)
	    (+w mouse-x-in-workspace constant-mouse-leeway)
	    (+w mouse-y-in-workspace constant-mouse-leeway)
	    'blue)
	  (let ((mouse-leeway-in-workspace
		  (mouse-leeway-in-workspace current-image-x-scale)))
	    (draw-rectangle-outline-in-current-image-plane
	      (-w mouse-x-in-workspace mouse-leeway-in-workspace)
	      (-w mouse-y-in-workspace mouse-leeway-in-workspace)
	      (+w mouse-x-in-workspace mouse-leeway-in-workspace)
	      (+w mouse-y-in-workspace mouse-leeway-in-workspace)
	      'red)))))))


(defparameter minimum-x-scale-for-picking
	      #.(round (normalized-scale) 4))

(defparameter minimum-width-or-height-for-picking-in-window-units
	      3)



;;; The named dynamic extent `finding-object-near-mouse' is only established by
;;; find-object-near-mouse, and hence is only used by it's subfunctions.  It
;;; includes read only bindings for:
;;;   `image-{x,y}-scale-for-finding-object-near-mouse'
;;;   `objects-to-not-consider?'
;;;   `classes-of-objects-to-not-consider?'
;;;   `mouse-{x,y}-in-workspace'


(def-named-dynamic-extent finding-object-near-mouse
  (module run)
  (unwind? nil))

;; This ought to include either lexically or dynamicly
;; loose-*-edge-of-visible-workspace-area bindings too. Argh.

(defvar-of-named-dynamic-extent image-plane-for-finding-object-near-mouse finding-object-near-mouse)
(defvar-of-named-dynamic-extent x-in-window-for-finding-object-near-mouse finding-object-near-mouse)
(defvar-of-named-dynamic-extent y-in-window-for-finding-object-near-mouse finding-object-near-mouse)
(defvar-of-named-dynamic-extent image-x-scale-for-finding-object-near-mouse finding-object-near-mouse)
(defvar-of-named-dynamic-extent image-y-scale-for-finding-object-near-mouse finding-object-near-mouse)
(defvar-of-named-dynamic-extent objects-to-not-consider? finding-object-near-mouse)
(defvar-of-named-dynamic-extent classes-of-objects-to-not-consider? finding-object-near-mouse)
(defvar-of-named-dynamic-extent mouse-x-in-workspace finding-object-near-mouse)
(defvar-of-named-dynamic-extent mouse-y-in-workspace finding-object-near-mouse)



;;; `Find-distance-to-block-if-reasonable' computes the distance, in workspace
;;; units, of the vector from the point (x-in-workspace, y-in-workspace) to the
;;; nearest block edge, if it considers the computation "reasonable".
;;; Specifically, if the vector is neither a horizontal nor vertical line, and
;;; the sum of the distance from x-in-workspace to the nearest vertical edge of
;;; block and the distance from y-in-workspace to the nearest horizontal edge of
;;; block is greater than maximum-distance-to-allow, the distance is not
;;; considered close enough to be worth doing, and so nil is returned.  (This is
;;; to avoid doing a general distance calculation, which would require computing
;;; an integer square root.)

;;; Find-distance-to-block-if-reasonable is a substitution macro, and it is
;;; internal to find-object-near-mouse, and demands a finding-object-near-mouse
;;; dynamic extent.

(def-substitution-macro find-distance-to-block-if-reasonable
       (x-in-workspace y-in-workspace block reasonable-distance)
  (multiple-value-bind (left-edge-of-content-and-frame
			 top-edge-of-content-and-frame
			 right-edge-of-content-and-frame
			 bottom-edge-of-content-and-frame)
      (edges-of-block-content-plus-frame block)
    (find-workspace-distance-to-rectangle-if-reasonable
      x-in-workspace y-in-workspace reasonable-distance
      left-edge-of-content-and-frame
      top-edge-of-content-and-frame
      right-edge-of-content-and-frame
      bottom-edge-of-content-and-frame)))

;; find-workspace-distance-to-rectangle-if-reasonable is in MENUS, where it
;; is needed by pick-cell-from-table.  (MHD 7/9/92)




;;; `Find-object-near-mouse' returns the closest object OR CONNECTION to the
;;; given window location, within some maximal distance, or NIL.  The meat of
;;; this is implemented in the subfunction find-object-near-mouse-1.  It
;;; establishes a finding-object-near-mouse dynamic extent.

(defun find-object-near-mouse
    (x-in-window
      y-in-window
      image-plane
      objects-to-not-consider?
      classes-of-objects-to-not-consider?)
  (with-named-dynamic-extent finding-object-near-mouse
      ((image-plane-for-finding-object-near-mouse image-plane)
       (x-in-window-for-finding-object-near-mouse x-in-window)
       (y-in-window-for-finding-object-near-mouse y-in-window)
       image-x-scale-for-finding-object-near-mouse
       image-y-scale-for-finding-object-near-mouse
       mouse-x-in-workspace
       mouse-y-in-workspace)
    (with-image-plane-transform (image-plane)
      (setf image-x-scale-for-finding-object-near-mouse
	    current-image-x-scale)
      (setf image-y-scale-for-finding-object-near-mouse
	    current-image-y-scale)
      (setf mouse-x-in-workspace
	    (x-in-workspace x-in-window))
      (setf mouse-y-in-workspace
	    (y-in-workspace y-in-window)))
    (let* ((workspace-on-image-plane
	     (workspace-on-image-plane? image-plane))
	   (maximum-distance-to-allow
	     (mouse-leeway-in-workspace image-x-scale-for-finding-object-near-mouse))
	   (loose-left-edge-of-visible-workspace-area
	     (maxw
	       (-w mouse-x-in-workspace maximum-distance-to-allow)
	       (loose-left-edge-of-visible-workspace-area image-plane)))
	   (loose-top-edge-of-visible-workspace-area
	     (maxw
	       (-w mouse-y-in-workspace maximum-distance-to-allow)
	       (loose-top-edge-of-visible-workspace-area image-plane)))
	   (loose-right-edge-of-visible-workspace-area
	     (minw
	       (+w mouse-x-in-workspace maximum-distance-to-allow)
	       (loose-right-edge-of-visible-workspace-area image-plane)))
	   (loose-bottom-edge-of-visible-workspace-area
	     (minw
	       (+w mouse-y-in-workspace maximum-distance-to-allow)
	       (loose-bottom-edge-of-visible-workspace-area image-plane)))
	   (object?
	     (find-object-near-mouse-1
	       workspace-on-image-plane maximum-distance-to-allow t)))

      #+development
      (visualize-picking-rectangle-if-called-for
	image-plane mouse-x-in-workspace mouse-y-in-workspace)

      (when (and object?
		 (or (not (<f image-x-scale-for-finding-object-near-mouse
			      minimum-x-scale-for-picking))
		     (and (framep object?)		; (or (not (framep object)) ...)
							    ;   instead to allow connection 
							    ;   picking at all scales?
			  (not (<f (delta-x-in-window
				     (minw (width-of-block object?)
					   (height-of-block object?))
				     image-x-scale-for-finding-object-near-mouse)
							    ; care about y scale too?
				   minimum-width-or-height-for-picking-in-window-units)))))
	 object?))))


;;; `Find-object-near-mouse-1' self recursively searchs the subblock hierarchy
;;; finding the block and connection that are closest to the mouse.  It is
;;; invoked inside of a dynamic extent that limits search so as to exclude
;;; objects beyond a certain distance, of a certain classes, and certain
;;; instances.  If a block/connection is found two values are returned, the
;;; object found, and it's distance from the mouse.  This is a subfunction of
;;; find-object-near-mouse.

(defun find-object-near-mouse-1
    (block-to-search maximum-distance-to-allow
		     block-being-searched-is-workspace-p)
  (loop with nearest-block?
	  = (if (not block-being-searched-is-workspace-p) block-to-search)
	with nearest-connection? = nil
	with current-maximum-distance-to-allow-for-blocks
	  = maximum-distance-to-allow
	with current-maximum-distance-to-allow-for-connections
	  = maximum-distance-to-allow
	with connection?
	with nearest-block-distance?
	  = (if (not block-being-searched-is-workspace-p)
		(or (find-distance-to-block-if-reasonable
		      mouse-x-in-workspace mouse-y-in-workspace
		      block-to-search current-maximum-distance-to-allow-for-blocks)
		    (setq nearest-block? nil)))
	with nearest-connection-distance? = nil
	with distance-from-point?
	with inheritance-path
	for subblock being each subblock of block-to-search
	doing
    ;; See if this block, or subblock is closer to the mouse
    ;; than the current one.
    (when (and
	    ;; Does this or it's subblocks appear on the visible portion of
	    ;; the image-plane?
	    (or (quick-clipping-check-of-block-for-picking subblock)
		(when (has-subblocks-p subblock)
		  (loop for subsubblock being each subblock of subblock
			thereis
			(quick-clipping-check-of-block-for-picking
			  subsubblock))))

	    ;; Have we been explicitly told to ignore this object?
	    (or (null objects-to-not-consider?)
		(not (memq subblock objects-to-not-consider?)))

	    ;; Is this of a class we are ignoring? ps bind inheritance-path.
	    (progn
	      (setq inheritance-path	; UGLY!! (optimization)
		    (class-inheritance-path
		      (class-description-slot subblock)))
	      (or (null classes-of-objects-to-not-consider?)			
		  (not (loop for class
				 in classes-of-objects-to-not-consider?
			     thereis
			     (inheritance-path-memq
			       class inheritance-path)))))
	    
	    ;; Special handling for text-boxes.
	    (or (not (inheritance-path-memq 'text-box inheritance-path))
		(text-box-visible-near-mouse-p subblock))

	    ;; Special handling for tables.  
	    (or (not (inheritance-path-memq 'table inheritance-path))
		(table-visible-near-mouse-p subblock)))

      (multiple-value-bind (subsubblock? distance)
	  (if (has-subblocks-p subblock)	; just an optimization
	      (find-object-near-mouse-1
		subblock
		current-maximum-distance-to-allow-for-blocks nil))
	(setq distance-from-point?
	      (find-distance-to-block-if-reasonable
		mouse-x-in-workspace mouse-y-in-workspace
		subblock current-maximum-distance-to-allow-for-blocks))

	;; Did we find a better block?
	(cond
	  ;; Subblock is better?
	  ((and subsubblock?
		(or (null distance-from-point?)
		    (<=w distance distance-from-point?))
		(or (null nearest-block-distance?)
		    (<=w distance nearest-block-distance?)))
	   (setq nearest-block? subsubblock?)
	   (setq nearest-block-distance? distance)
	   (setq current-maximum-distance-to-allow-for-blocks distance))
	  ;; This block is better?
	  ((and distance-from-point?
		(or (null nearest-block-distance?)
		    (<=w distance-from-point? nearest-block-distance?)))
	   (setq nearest-block? subblock)
	   (setq nearest-block-distance? distance-from-point?)
	   (setq current-maximum-distance-to-allow-for-blocks
		 distance-from-point?)))))

    ;; See if there is a better connection near this subblock?
    (when (and block-being-searched-is-workspace-p
	       (multiple-value-setq
		   (connection? distance-from-point?)
		 (find-vector-length-from-point-to-block-connections-if-within-limit
		   mouse-x-in-workspace mouse-y-in-workspace
		   subblock current-maximum-distance-to-allow-for-connections
		   objects-to-not-consider?))
	       (or (null objects-to-not-consider?)
		   (not (memq connection? objects-to-not-consider?)))
	       ;; consider classes-not-to-consider???
	       (or (null nearest-connection-distance?)
		   (<w distance-from-point? nearest-connection-distance?)))
      (setq nearest-connection? connection?
	    nearest-connection-distance? distance-from-point?
	    current-maximum-distance-to-allow-for-connections
	    distance-from-point?))

	finally
	  (return
	    (cond
	      ((and 
		 ;; If you are near both a connection and a block; Note A
		 nearest-block? nearest-connection?
		 ;; and nearest-connection? is not a one of block's connections.  ; Note B
		 (not (connection-exist-p nearest-connection? (connections nearest-block?)))
		 ;; and not loose end connected to the same object as this
		 ;; connection:
		 (if (loose-end-p nearest-block?)
		     (not (or (connection-connected-to-block-p
				nearest-connection?
				(get-block-at-other-end-of-connection
				  nearest-connection? nearest-block?))				  
			      (connection-connected-to-block-p
				nearest-connection? nearest-block?)))
		     t)

		 ;; and either ...
		 (let* ((expansion-factor  ; Note C
			  (halfw
			    (compute-connection-width-given-connection-frame-or-class
			      (connection-frame-or-class nearest-connection?))))
			(gross-distance-from-connection
			  (-w nearest-connection-distance? expansion-factor))
			(effective-distance-from-connection
			  (if (>w gross-distance-from-connection 0)
			      gross-distance-from-connection
			      0)))

		   (or
		     ;; (a) the connection is closer
		     (<w effective-distance-from-connection
			 nearest-block-distance?)
		   
		     ;; or (b) they are both the same distance from the mouse
		     ;; and the connection is higher in Z
		     (and (=w effective-distance-from-connection
			      nearest-block-distance?)
			  (>f (get-connection-layer-position nearest-connection?) ; Note D
			      (get-block-layer-position nearest-block?))))))
	       
	       ;; then return the connection
	       (values nearest-connection? nearest-connection-distance?))
	      
	      (t
	       ;; otherwise, return the block, if any; otherwise, return the connection, if any:
	       (values (or nearest-block? nearest-connection?)
		       (or nearest-block-distance?
			   nearest-connection-distance?)))))))

;; Note A: this is new logic to give priority to the connection if it is closer
;; in the Z dimension.  This fixes (in G2 5.0, Second Beta) a longstanding bug
;; in G2 4.0.  Note that the concept of layers was basically not part of the
;; user model prior to G2 4.0, so this could be seen as a problem that only
;; began in G2 4.0. (MHD 3/4/97)

;; Note B: this test makes any block, in particular loose-end blocks and small
;; blocks, attached to the connection always win out over the nearby connection.
;; Without this, very small blocks and loose ends would never be able to be
;; selected.  This might introduce cases where the connection could not be
;; selected, i.e., when the length of the connection is very short.  However, in
;; this case, at least the user has the option to drag the block at one of the
;; ends away in order to lengthen the connection and create a selectable
;; segment.  (MHD 3/4/97)

;; Note C: Connections are one unit wide, its only their icons that will tend to
;; be bigger. When there is no overlap with a block, we're able to select a
;; connection because of the mouse leeway that's factored into the
;; search. However when there is overlap, the block will invariably always win
;; (the position in the middle of the visible region of the connection being
;; virtually impossible to pick out reliably) unless we artificially expand the
;; space taken up by the connection. The expansion factor used here is based on
;; the cumulative widths of the strips in the connection's icon description.

;; Note D: improved some more for 6.0: if block is a loose end of the connection,
;; or the connection is connected to the same block as the loose end, then
;; choose the loose end.  Also, extremely slight cleanup: >w => >f. (MHD 2/28/00)

;; The check for classes of objects not to consider could be speeded up by obtaining a list of
;; classes in the inheritance path outside the main loop, adapting the test to do a memq, and,
;; if necessary, recycling the list of classes at the end.  However, at present the classes-of-
;; objects-not-to-consider feature is lightly used, and this would be a very minor speed-up.

;; Review find-vector-length-from-point-to-block-connections-if-within-limit (i.e. the 
;; connection searching logic)!

;; Consider providing a way to limit the search just to what is on the window (or perhaps
;; even to an arbitrary rectangle within the workspace).


(defun quick-clipping-check-of-block-for-picking (block)
  (multiple-value-bind (left-edge top-edge right-edge bottom-edge)
      (edges-of-block-content-plus-frame block)
    (not (or (>w left-edge
		    loose-right-edge-of-visible-workspace-area)
	     (>w top-edge
		 loose-bottom-edge-of-visible-workspace-area)
	     (<w right-edge
		 loose-left-edge-of-visible-workspace-area)
	     (<w bottom-edge
		 loose-top-edge-of-visible-workspace-area)))))








;;; `Find-object-near-workstation-event' ...

;;; Objects-to-not-consider? and classes-of-objects-to-not-consider? arguments
;;; are as documented under find-object-near-mouse.

;;; If there is no image plane for the workstation event or if the image plane
;;; does not show a workspace, this function returns nil.  Otherwise, it returns
;;; the following four values:
;;;
;;;   (1) the object near the mouse, if any (as would be returned by
;;;       find-object-near- mouse);
;;;   (2) the image plane the workstation event was in;
;;;   (3) the x position in the window in which the event took place; and
;;;   (4) the y position in the window in which the event took place.

(defun find-object-near-workstation-event
    (workstation-event
      &optional objects-to-not-consider? classes-of-objects-to-not-consider?)
  (let ((image-plane?
	  (image-plane-for-workstation-event? workstation-event)))
    (when (and image-plane? (workspace-on-image-plane? image-plane?))
      (let ((x-in-window 
	      (workstation-event-cursor-x workstation-event))
	    (y-in-window 
	      (workstation-event-cursor-y workstation-event)))
	(values
	  (find-object-near-mouse
	    (workstation-event-cursor-x workstation-event) 
	    (workstation-event-cursor-y workstation-event)
	    image-plane?
	    objects-to-not-consider?
	    classes-of-objects-to-not-consider?)
	  image-plane? x-in-window y-in-window)))))

;; Consder adding a slot to workstation events where this information, once
;; computed, can be saved.  (See Mouse Pointers) This function ought to be
;; obsoleted, but it is used by the editor, among others.





;;; The function `text-box-visible-near-mouse-p' decides if a text box is
;;; visible in a finding-object-near-mouse dynamic extent.

(defun text-box-visible-near-mouse-p (text-box)
  (assert-that-within-named-dynamic-extent 'finding-object-near-mouse)
  (let ((text-box-visibility?
	  (or
	    ;; First, test for :without-text visibility, due to the selection
	    ;; highlight box. See note 1. (MHD 12/1/03)
	    (if (thing-selected-p
		  text-box image-plane-for-finding-object-near-mouse)
		:without-text)
	    (text-box-visible-p
	      text-box
	      image-x-scale-for-finding-object-near-mouse
	      image-y-scale-for-finding-object-near-mouse))))
    (case text-box-visibility?
      (:just-text
       (or (not (frame-of-class-p text-box 'name-box))
	   ;; This (with either :tight or T as the last arg)
	   ;;   is done here only for kinds of text boxes that do 
	   ;;   not have the click-to-edit feature, so that you
	   ;;   can still get their menus by clicking near but not
	   ;;   in their text.  This should be done for most
	   ;;   subordinate text boxes, such as labels. This is
	   ;;   only a prefilter for text boxes; whether to do
	   ;;   click-to-edit or post a menu is decided in the
	   ;;   Selection subsection of MENUS, which see.
	   (find-position-in-text
	     text-box nil nil nil nil
	     mouse-x-in-workspace mouse-y-in-workspace
	     nil nil nil
	     (if (frame-of-class-p text-box 'name-box)	; useful later
		 :tight
		 t))))	; if just the text is visible, must be in text
      (t text-box-visibility?)))) ; don't pick an invisible text box

;; Note 1: we want visibility to be :without-text notably in order to get entire
;; visible name-box highlight rectangle to be picked (double-click -> table,
;; drag to move, etc.).  Notice that class name-box is specially dealt with in
;; the :just-text case, which we want to avoid if we've got the selection
;; highlight rectangle. (MHD 12/1/03)






;;; The function `table-visible-near-mouse-p' decides if a table is visible in a
;;; finding-object-near-mouse dynamic extent.  The decision is made
;;; heuristically.  If only the text seems to be visible according to this
;;; function's heuristics, this this returns true only if the position of the
;;; mouse is "tightly" within the text, as "tight" is defined by
;;; find-position-in-text.

(defun table-visible-near-mouse-p (table)
  (assert-that-within-named-dynamic-extent 'finding-object-near-mouse)
  (or (table-visible-in-image-plane-p
	table nil image-plane-for-finding-object-near-mouse)
      (pick-cell-from-table
	table 
	image-plane-for-finding-object-near-mouse
	x-in-window-for-finding-object-near-mouse
	y-in-window-for-finding-object-near-mouse
	t				; only if in text
	t				; find-nearest-cell?
	t)))				; consider-cell-visibility?

;; A new wrinkle in 7.x for both tables and text boxes is selection. Even when a
;; table or text box are considered borderless by a zero-width-border test such
;; as used above, there still might be a selection border drawn around a table
;; or text box, and this should cause it to be considered visible. That is
;; mostly handled now by non-text-visible-in-table-rows-p, which takes selection
;; into account. (MHD 9/5/03)





;;;; Block near mouse cache


;;; The defvar `unselectable-classes-of-objects' is a list of classes of objects
;;; to never consider as the object under the mouse, at top level.

(defparameter unselectable-classes-of-objects '(small-edit-cursor edit-cursor))

;; This is related to rdf's small-edit-cursor feature.  See also the call to
;; find-object-near-workstation-event in handle-mouse-down-event-in-edit-context.
;; -fmw, 12/22/93



;;; The function `find-block-near-mouse-on-workspace' is a specialized version
;;; of find-object-near-mouse, used by the generate-spot method on workspaces.
;;; It makes use of a short-lived cache so that the flurry mouse-down,
;;; mouse-motion, mouse-up, and mouse-select events generated by any mouse
;;; click can be collapsed into one lookup in most cases.  It ALWAYS returns a
;;; block or NIL (connections are converted into connection frames).

(defun find-block-near-mouse-on-workspace
    (x-in-window y-in-window image-plane)
  (multiple-value-bind (block? valid?)
      (cached-block-near-mouse x-in-window y-in-window image-plane)

    (cond (valid?
	   block?)
	  (t
	   (with-drawing-trace (mouse-cache)
	     (format t "**** Mouse cache miss at ~d ~d ~s ****~%"
		     x-in-window y-in-window image-plane))

	   (let* ((thing?
		    (find-object-near-mouse
		      x-in-window y-in-window image-plane
		      nil unselectable-classes-of-objects))
		  (block?
		    ;; Override find-object-near-mouse, in a few cases.
		    ;;  1. If superior is a table, then use it.
		    ;;  2. Coerce a connection into a frame.
		    (cond ((null thing?)
			   nil)
			  ((not (framep thing?))
			   (get-or-make-connection-frame-and-activate-if-appropriate
			     thing?))
			  (t
			   (loop for maybe-a-table = thing?
						   then (superblock? maybe-a-table)
				 when (workspace-p maybe-a-table)
				   do (return thing?)	    ; return the original thing.
				 when (table-p maybe-a-table)
				   do (return maybe-a-table))))))

	     (cache-block-near-mouse block? x-in-window y-in-window image-plane)
	     block?)))))





;;;; Block near mouse cache



;;; The structure `block-near-mouse-cache' caches the block nearest the last
;;; mouse click, together with enough information to validate the cache.  Note
;;; that we cache connection-frames, rather than connection structures, so that
;;; we always have a block.

(define-structure block-near-mouse-cache ()
  (:managed t)
  (:conc-name t)
  (:constructor make-block-near-mouse-cache-internal ())
  (x-in-window 0)
  (y-in-window 0)
  (image-plane nil)
  (image-plane-serial 0)
  (image-plane-left 0)
  (image-plane-top 0)
  (image-plane-right 0)
  (image-plane-bottom 0)
  (image-plane-x-scale 0)
  (image-plane-y-scale 0)
  (workspace nil)
  (workspace-serial (frame-serial-number-0) :reclaimer reclaim-frame-serial-number)
  (workspace-geometry-tick 0)
  (cached-block? nil)
  (cached-block-serial? (frame-serial-number-0) :reclaimer reclaim-frame-serial-number))

(defun clear-cached-block-near-mouse (image-plane)
  (let* ((workstation (workstation-of-image-plane image-plane))
	 (cache (workstation-block-near-mouse-cache workstation)))

    ;; Clearing the image-plane would suffice, but for cleanliness, clear the
    ;; other block-like slots.
    (setf (block-near-mouse-cache-image-plane cache) nil)
    (setf (block-near-mouse-cache-workspace cache) nil)
    (frame-serial-number-setf (block-near-mouse-cache-workspace-serial cache) (frame-serial-number-0))
    (setf (block-near-mouse-cache-cached-block? cache) nil)
    (frame-serial-number-setf (block-near-mouse-cache-cached-block-serial? cache) nil)))




  
(defun cache-block-near-mouse (block? x-in-window y-in-window image-plane)
  (let* ((workstation (workstation-of-image-plane image-plane))
	 (cache (workstation-block-near-mouse-cache workstation)) 
	 (workspace? (workspace-on-image-plane? image-plane)))
    (when workspace?
      (setf (block-near-mouse-cache-x-in-window cache) x-in-window)
      (setf (block-near-mouse-cache-y-in-window cache) y-in-window)

      (setf (block-near-mouse-cache-image-plane cache) image-plane)
      (setf (block-near-mouse-cache-image-plane-serial cache)
	    (serial-number-of-image-plane image-plane))
      (setf (block-near-mouse-cache-workspace cache) workspace?)
      (frame-serial-number-setf (block-near-mouse-cache-workspace-serial cache) (frame-serial-number workspace?))

      (setf (block-near-mouse-cache-image-plane-left cache) (left-edge-of-image-in-window image-plane))
      (setf (block-near-mouse-cache-image-plane-top cache) (top-edge-of-image-in-window image-plane))
      (setf (block-near-mouse-cache-image-plane-right cache) (right-edge-of-image-in-window image-plane))
      (setf (block-near-mouse-cache-image-plane-bottom cache) (bottom-edge-of-image-in-window image-plane))
      
      (setf (block-near-mouse-cache-image-plane-x-scale cache) (image-x-scale image-plane))
      (setf (block-near-mouse-cache-image-plane-y-scale cache) (image-y-scale image-plane))
      
      (setf (block-near-mouse-cache-workspace-geometry-tick cache) (workspace-geometry-tick workspace?))

      (setf (block-near-mouse-cache-cached-block? cache) block?)
      (frame-serial-number-setf (block-near-mouse-cache-cached-block-serial? cache) (and block? (frame-serial-number block?)))
      cache)))


(defun cached-block-near-mouse (x-in-window y-in-window image-plane)
  (let* ((workstation (workstation-of-image-plane image-plane))
	 (workspace? (workspace-on-image-plane? image-plane)) 
	 (cache? (workstation-block-near-mouse-cache workstation)))
    (when (and workspace? cache?)
      (when (and
	      (=f x-in-window (block-near-mouse-cache-x-in-window cache?))
	      (=f y-in-window (block-near-mouse-cache-y-in-window cache?))

	      (eq image-plane (block-near-mouse-cache-image-plane cache?))
	      (image-plane-has-not-been-reprocessed-p
		(block-near-mouse-cache-image-plane cache?)
		(block-near-mouse-cache-image-plane-serial cache?))

	      (eq workspace? (block-near-mouse-cache-workspace cache?))
	      (frame-has-not-been-reprocessed-p
		(block-near-mouse-cache-workspace cache?)		
		(block-near-mouse-cache-workspace-serial cache?))

	      (=f (left-edge-of-image-in-window image-plane)
		  (block-near-mouse-cache-image-plane-left cache?))
	      (=f (top-edge-of-image-in-window image-plane)
		  (block-near-mouse-cache-image-plane-top cache?))
	      (=f (right-edge-of-image-in-window image-plane)
		  (block-near-mouse-cache-image-plane-right cache?))
	      (=f (bottom-edge-of-image-in-window image-plane)
		  (block-near-mouse-cache-image-plane-bottom cache?))
	      
	      (=f (image-x-scale image-plane)
		  (block-near-mouse-cache-image-plane-x-scale cache?))
	      (=f (image-y-scale image-plane)
		  (block-near-mouse-cache-image-plane-y-scale cache?))
	      
	      (=f (workspace-geometry-tick workspace?)
		  (block-near-mouse-cache-workspace-geometry-tick cache?))

	      (or (null (block-near-mouse-cache-cached-block? cache?))
		  (frame-has-not-been-reprocessed-p
		    (block-near-mouse-cache-cached-block? cache?)
		    (block-near-mouse-cache-cached-block-serial? cache?))))
	(values (block-near-mouse-cache-cached-block? cache?)
		t)))))

	       


;;;; Mouse Pointers in Workspaces




;;; `Generate-spot-for-workspace' finds the object closest to the mouse and
;;; creates a spot approprate to that item's type.

;;; First we check the frame of the image-plane, then we look to the object
;;; nearest mouse algorithum to peek into the subblocks.  That algorithum
;;; doesn't treat the worksapce margin as different than other empty background.

;;; The frame currently always generates workspace background spots.

;;; Within the workspace area the routine find-object-near-mouse is used to find
;;; the object closest to the mouse.  If it finds nothing then a
;;; workspace-background-spot is generated.

;;; Connection structures are coerced into frames, and their generate-spot method
;;; is called.
;; Now done by find-block-near-mouse-on-workspace.

;;; Indirect workspace subblocks add to the complexity of things.  Some special
;;; cases of these are wired directly into this routine.  By default the
;;; generate-spot method of the frame found is called.  The one exception to this
;;; rule is that if the block found is embedded in a table, then the generate
;;; spot method of that table is called.

(def-class-method generate-spot (workspace mouse-pointer)
  (with-drawing-trace (mouse-tracking)
    (format t "Generate spot for workspace ~s" workspace))
  (with-mouse-pointer-bindings (image-plane
				 x-in-window y-in-window
				 x-in-workspace y-in-workspace) mouse-pointer
    (cond
      
      ;; Part of the workspace frame?
      ((generate-spot-if-in-workspace-frame workspace mouse-pointer))
      
      (t
       ;; Workspace background, subblock or connection.

       ;; For the hell of it, clear the cache for each mouse-down.
       (when (mouse-down-event-p (key-code-of-mouse-pointer mouse-pointer))
	 (clear-cached-block-near-mouse image-plane))
       
       (let ((block?
	       (find-block-near-mouse-on-workspace
		 x-in-window y-in-window image-plane)))

	 (cond ((null block?)
		(with-drawing-trace (mouse-tracking)
		  (format t "  Workspace background."))
		(push-last-spot mouse-pointer (make-workspace-background-spot) nil))

	       (t
		;; Call the generate spot of a block or a connection.
		(with-drawing-trace (mouse-tracking)
		  (format t "  Workspace subblock ~s" block?))

		;; Try the block's frame.
		(generate-spot-from-frame-if-approprate
		  block? mouse-pointer)

		;; Try the block's handles.
		(when (selection-handles-visible-p block? image-plane)
		  (generate-spot-for-selection-handle block? mouse-pointer))

		;; Try the block, if that didn't work
		(when (further-tracking-maybe-required? (stack-of-spots mouse-pointer))
		  (with-drawing-trace (mouse-tracking)
		    (format t "Generate spot: call method on ~s" block?))

		  (funcall-method 'generate-spot block? mouse-pointer)))))))))


(defun generate-spot-if-in-workspace-frame (workspace mouse-pointer)
  (with-mouse-pointer-bindings (image-plane
				 x-in-window y-in-window
				 x-in-workspace y-in-workspace) mouse-pointer
    (when (not (point-inside-rectangle-p 
		 x-in-window y-in-window
		 (left-edge-of-workspace-area-in-window image-plane)
		 (top-edge-of-workspace-area-in-window image-plane)
		 (right-edge-of-workspace-area-in-window image-plane)
		 (bottom-edge-of-workspace-area-in-window image-plane)))
      (with-drawing-trace (mouse-tracking)
	 (format t "   Workspace frame."))
       ;; Open a little light pen worth of drawing area.
       (with-draw-area-for-mouse-tracking (x-in-workspace y-in-workspace)
	 (on-image-plane-without-drawing (image-plane) ;; Note A
	   (with-null-drawing-transform
	     (track-mouse-over-frame
	       mouse-pointer
	       (frame-description-of-frame-description-reference
		 (frame-description-reference-of-image-plane
		   image-plane))
	       workspace
	       (left-edge-of-image-in-window image-plane)
	       (top-edge-of-image-in-window image-plane)
	       (right-edge-of-image-in-window image-plane)
	       (bottom-edge-of-image-in-window image-plane)))))
       t)))

;; The workspace subblock generate-spot call isn't establishing the
;; frame-transform but it isn't inside a without drawing context either.

;; Note A: This should be on-image-plane-exterior-without-drawing, then
;; the call on with-null-drawing-transform would be unnecessary.




;;; `Generate-spot-from-frame-if-approprate' will finish mouse tracking
;;; if the mouse is over the frame, if any, of the block given.

(defun generate-spot-from-frame-if-approprate (block mouse-pointer)
  (with-mouse-pointer-bindings (image-plane
				 x-in-workspace
				 y-in-workspace
				 x-in-window
				 y-in-window) mouse-pointer
    (with-draw-area-for-mouse-tracking (x-in-workspace y-in-workspace)
      (on-image-plane-without-drawing (image-plane)
	(block nil
	  (macrolet ((return-if-nil (form) `(or ,form (return))))
	    (let* ((frame-transforms-of-block
		     (return-if-nil
		       (frame-transforms-of-block block)))
		   (frame-description-reference
		     (return-if-nil
		       (frame-description-reference-of-frame-transform
			 (cdr (first frame-transforms-of-block)))))
		   (left-edge-of-block (left-edge-of-block block))
		   (top-edge-of-block (top-edge-of-block block))
		   (right-edge-of-block (right-edge-of-block block))
		   (bottom-edge-of-block (bottom-edge-of-block block)))

	      (when (point-inside-rectangle-p 
		      x-in-window y-in-window
		      (x-in-window left-edge-of-block)
		      (y-in-window top-edge-of-block)
		      (x-in-window right-edge-of-block)
		      (y-in-window bottom-edge-of-block))
		;; Over the content, not in frame...
		(return))

	      (let ((left-edge-of-frame
		      (-w left-edge-of-block
			  (left-frame-indent frame-description-reference)))
		    (top-edge-of-frame
		      (-w top-edge-of-block
			  (top-frame-indent frame-description-reference)))
		    (right-edge-of-frame
		      (+w right-edge-of-block
			  (right-frame-indent frame-description-reference)))
		    (bottom-edge-of-frame
		      (+w bottom-edge-of-block
			  (bottom-frame-indent frame-description-reference))))

		(unless (point-inside-rectangle-p
			  x-in-window y-in-window
			  (x-in-window left-edge-of-frame)
			  (y-in-window top-edge-of-frame)
			  (x-in-window right-edge-of-frame)
			  (y-in-window bottom-edge-of-frame))
		  ;; Outside of the frame, not in it...
		  (return))
		
		;; Track into the frame, this will make a spot!
		(track-mouse-over-frame
		  mouse-pointer
		  (frame-description-of-frame-description-reference
		    frame-description-reference)
		  block
		  left-edge-of-frame
		  top-edge-of-frame
		  right-edge-of-frame
		  bottom-edge-of-frame))
	      
	      ;; Got it.
	      #+development
	      (when (further-tracking-maybe-required?
		      (stack-of-spots mouse-pointer))
		(cerror "Go"
			"Spot generation over frame didn't generate a spot."))
	      )))))))







;;;; Credits, Titles, etc.




(defconstant all-optional-modules-for-display
	     '(gsi))

;; At present, this is only used by display-credits.
;; GFI is superseded, still authorizable but not displayed on title block,
;; starting with 6.0.
;; GSPAN is completely obselete. (lgibson 2/24/2000).



;;; `List-loaded-user-visible-modules' returns a gensym list of modules that are
;;; loaded, available to the user, and may be expected to be aware of.

(defun list-loaded-user-visible-modules ()
  (loop for module-entry
	    in all-optional-modules-for-display
	when (and (module-authorized-p module-entry)
		  (not (invisible-optional-module-p
			 module-entry)))
	  collect module-entry using gensym-cons))

;; At present, this is only used by display-credits.  (MHD 2/13/90)


(def-system-variable gensym-logo-style run
  (:funcall get-gensym-logo-style))

(defun get-gensym-logo-style ()
  (setq gensym-logo-style
	(let ((style (get-gensym-environment-variable #w"G2_GENSYM_LOGO_STYLE")))
	  (cond ((null style)
		 'new-large-with-tagline)
		((string-equalw style #w"NEW-SMALL")
		 'new-small)
		((string-equalw style #w"NEW-LARGE")
		 'new-large)
		((string-equalw style #w"NEW-LARGE-2")
		 'new-large-2)
		((string-equalw style #w"NEW-LARGE-WITH-TAGLINE")
		 'new-large-with-tagline)
		((string-equalw style #w"OLD")
		 'old)
		(t
		 'new-large-with-tagline)))))

(defun make-text-for-gensym-g2 ()  
  (slot-value-list (copy-text-string (if (or (eq gensym-logo-style 'new-large)
					     (eq gensym-logo-style 'new-large-2)
					     (eq gensym-logo-style 'new-large-with-tagline))
					 "G2"
					 "Gensym  G2"))))


(defun make-text-for-product-and-options ()  
  (let* ((user-visible-optional-modules-loaded
	   (list-loaded-user-visible-modules)))
    (if user-visible-optional-modules-loaded
	(slot-value-list
	  (twith-output-to-text-string
	    #+SymScale
	    (tformat "Multi-threading ")
	    #+mtg2
	    (tformat "Multi-threaded ")
	    (tformat "G2~c with " #.%registered-sign)
	    (write-symbol-list
	      user-visible-optional-modules-loaded
	      nil 'and nil
	      '((icp . #.(stringw #.%trade-mark-sign)) ; see note below
		(gsi . #.(stringw #.%trade-mark-sign))
		(gspan . #.(stringw #.%registered-sign))
		(gfi . #.(stringw #.%trade-mark-sign))))
	    (twrite-char #.%line-separator)
	    (reclaim-gensym-list
	      user-visible-optional-modules-loaded))))))

;; Note: In version 5.0, GFI and GSI were displayed on title block.
;; In version 6.0, only GSI displayed on title block, but
;; others left in for examples of future use. (lgibson 2/28/2000).

;; A memo from the CFO, S. Gregorio, 8/26/91, stated:
;;
;;   We have just received out registered trademark for
;;   "G2 REAL-TIME EXPERT SYSTEM".  Please begin using
;;   the encircled r on all documentation, marketing
;;   materials, press releases, and software.
;;
;;   Our other registered trademarks:
;;
;;   Telewindows
;;   GSPAN
;;   G2
;;   Gensym
;;
;; So, we gave G2 and GSPAN the encircled r -- registered -- to replace the TM
;; -- trademark.  See also TELEWINDOWS module, where I did similar things for
;; Telewindows.  (All had been TM before today.)
;;
;; Note, however, that neither "Gensym" nor "G2 REAL-TIME EXPERT SYSTEM" appear
;; on the title block.  Have management consider whether to add them!
;;
;; (MHD 8/28/91)


(defun make-text-for-type-of-g2-license ()
  (slot-value-list
    (twith-output-to-text-string
      (twrite-system-version-in-g2-title
	(system-version current-system-name))
      (when build-comment-string
	(twrite-string " (")
	(twrite-string build-comment-string)
	(twrite-string 
	 (ecase release-quality-of-current-gensym-product-line
	   (#.prototype-release-quality " Prototype")
	   (#.alpha-release-quality " Alpha")
	   (#.beta-release-quality " Beta")
	   (#.release-quality "")))
	(twrite-string ")"))
      #+runtime-functionality-without-a-license
      (twrite-string " (Runtime)")
      #-runtime-functionality-without-a-license
      (when (runtime-option-authorized-p)
	(twrite-string " (Runtime)"))
      (when (restricted-use-option-authorized-p)
	(twrite-string " (Restricted Use)"))
      (when (embedded-option-authorized-p)
	(twrite-string " (Embedded)"))
      #+(and development lucid)
      (twrite-string " (Lucid)")
      #+(and development sbcl)
      (twrite-string " (SBCL)")
      #+(and development clozure)
      (twrite-string " (CCL)")
      #+(and development lispworks)
      (twrite-string " (LispWorks)")
      #+(and development allegro)
      (twrite-string " (Allegro CL)")
      )
    (stringw #.%line-separator)))


(defun make-text-for-local-identification ()
  (slot-value-list
    (write-local-identification-info-text-string)))




;;; `Display-credits' puts up, on the detail panes of all current gensym windows
;;; that have detail panes, the initial display of the word Gensym at a large
;;; scale with copyright notice and information below it at the normal scale.
;;; Several specialized formats are defined for this purpose below.  Credits-
;;; table-format is for the entire table.  Program-title-format is just for
;;; the title (Gensym).  New-copyright-format formats the copyright information
;;; that appears below the system title.

;;; Finally this will force-process-drawing.

(defparameter interrim-no-mark-logo-p t)

(defun display-credits (&optional a-particular-workstation-only?)
  (loop with gensym-logo-style
	  = (if interrim-no-mark-logo-p
		'old
		gensym-logo-style)
	for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	when (or (null a-particular-workstation-only?)
		 (eq workstation a-particular-workstation-only?))
	  do
	    (let ((workspace
		    (make-workspace
		      'temporary-workspace nil
		      (make-or-reformat-table
			(nconc
			  (if interrim-no-mark-logo-p
			      (slot-value-list
				(slot-value-list
				  nil
				  (make-text-cell
				    (slot-value-list
				      (copy-text-string " Gensym  G2"))
				    'program-title-format)))
			      (let ((logo
				      (make-icon-cell (case gensym-logo-style
							(old 'gensym-logo)
							(new-small 'new-gensym-logo)
							((new-large new-large-2)
							 'large-new-gensym-logo)
							((new-large-with-tagline)
							 'large-new-gensym-logo-with-tagline))
						      20 20 20 10))
				    (g2
				      (make-text-cell
					(make-text-for-gensym-g2)	; NOTE: TM too huge to use here
					(case gensym-logo-style
					  ((new-large new-large-2 new-large-with-tagline)
					   'new-large-logo-program-title-format)
					  (new-small 'new-small-logo-program-title-format)
					  (old 'program-title-format)))))
				(if (eq gensym-logo-style 'new-large-2)
				    (slot-value-list (slot-value-list nil logo)
						     (slot-value-list nil g2))
				    (slot-value-list (slot-value-list logo g2)))))
			  (slot-value-list
			    (slot-value-list
			      (case gensym-logo-style
				((new-large new-large-2 new-large-with-tagline)
				 nil)
				(new-small
				 (make-text-cell (make-empty-text) 'new-small-logo-new-copyright-format))
				(old
				 (make-text-cell (make-empty-text) 'new-copyright-format)))
			      (make-text-cell
				(nconc
				  (make-text-for-product-and-options)
				  (make-text-for-type-of-g2-license)
				  (make-text-for-local-identification)
				  (copy-for-slot-value
				    copyright-boilerplate-lines-of-text-1))
				(case gensym-logo-style
				  ((new-large new-large-2 new-large-with-tagline)
				   'new-large-logo-new-copyright-format)
				  (new-small 'new-small-logo-new-copyright-format)
				  (t 'new-copyright-format))))
			    (slot-value-list
			      nil
			      (make-text-cell
				(copy-for-slot-value
				  copyright-boilerplate-lines-of-text-2)
				'fine-print-format))))
			'credits-table-format nil)
		      0)))
	      (setf (frame-style-of-block workspace)
		    (if (eq gensym-logo-style 'old)
			:credits-workspace-frame-style
			:new-credits-workspace-frame-style))
	      (put-workspace-on-pane
		workspace (detail-pane gensym-window)
		'right 'bottom nil
		:margin-in-pane 50)))
  (force-process-drawing))

;; Consider having just one credit table, and hence workspace, for all detail panes, so
;; that any user may delete it for all windows.

;; Removed commented-out, old boilerplate for demo versions that had been here.
;; It was obsolete.  (MHD 10/12/90)



;;; Title-block-table-p is true if table is a short representation.  At present, this
;;; is indicated by having a table format whose single name is the symbol short-
;;; representation-table-format.  (This is out of date.)

(defun title-block-table-p (table)
  (eq (name-or-names-for-frame (table-format table))
      'credits-table-format))





;;; Image-plane-has-title-block-p is true if image plane is showing a title block
;;; as would be displayed via display-credits.  

(defun image-plane-has-title-block-p (image-plane)
  (let* ((workspace? (workspace-on-image-plane? image-plane)))
    (if workspace?
	(title-block-workspace-p workspace?))))




;;; Title-block-workspace-p is true if workspace is a "title block workspace",
;;; as would be generated by the "New Title Block" menu command.

(defun title-block-workspace-p (workspace)
  (let ((sole-subblock-on-temporary-workspace?
	  (if (and (temporary-workspace-p workspace)
		   (has-only-one-subblock-p workspace))
	      (first-subblock workspace))))
    (and sole-subblock-on-temporary-workspace?
	 (frame-of-class-p sole-subblock-on-temporary-workspace? 'table)
	 (title-block-table-p sole-subblock-on-temporary-workspace?))))




;;; Delete-all-title-block-workspaces ... called after reading KB.

(defun delete-all-title-block-workspaces ()
  (loop while
	(loop for workspace being each class-instance
	      of 'temporary-workspace
	      when (title-block-workspace-p workspace)
		return (progn
			 (delete-frame workspace)
			 t))))





(def-table-format credits-table-format
  table-border-color? dark-gray
  table-row-boundary-width 0
  table-column-boundary-width 0)

(def-table-format-spot-generator credits-table-format (table mouse-pointer)
  (generate-output-only-table-spot table mouse-pointer (make-credits-table-spot)))

(def-text-cell-format program-title-format
  text-cell-line-color? dark-gray
  text-cell-lines-justified? nil
  text-cell-line-quadding? nil
  text-cell-left-margin 0
  text-cell-top-margin 31
  text-cell-right-margin 20
  text-cell-bottom-margin 0
  text-cell-paragraph-indentation 0

  text-cell-font-map (HB72)
  text-cell-line-height 100
  text-cell-baseline-position 72
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 10)
  minimum-word-spacing #.(convert-to-text-width 8)
  maximum-word-spacing #.(convert-to-text-width 14)

  minimum-format-width-for-text-cell 600)

(def-text-cell-format new-small-logo-program-title-format
  text-cell-line-color? dim-gray
  text-cell-lines-justified? nil
  text-cell-line-quadding? nil
  text-cell-left-margin 0
  text-cell-top-margin 20
  text-cell-right-margin 20
  text-cell-bottom-margin 20
  text-cell-paragraph-indentation 0

  text-cell-font-map (HB72)
  text-cell-line-height 100
  text-cell-baseline-position 72
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 10)
  minimum-word-spacing #.(convert-to-text-width 8)
  maximum-word-spacing #.(convert-to-text-width 14)

  minimum-format-width-for-text-cell 600)

(def-text-cell-format new-large-logo-program-title-format
  text-cell-line-color? dim-gray
  text-cell-lines-justified? nil
  text-cell-line-quadding? nil
  text-cell-left-margin 0
  text-cell-top-margin 20
  text-cell-right-margin 20
  text-cell-bottom-margin 20
  text-cell-paragraph-indentation 0

  text-cell-font-map (HB72)
  text-cell-line-height 100
  text-cell-baseline-position 72
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 10)
  minimum-word-spacing #.(convert-to-text-width 8)
  maximum-word-spacing #.(convert-to-text-width 14))

(def-text-cell-format new-copyright-format
  text-cell-line-color? dark-gray
  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 20
  text-cell-top-margin 0
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 15 ; if line spills over, have it 
					;    look right (MHD 6/3/99)
  minimum-format-width-for-text-cell 800 ; expanded to fit more
					;    platform info on one line; 
					;    previously 600 (MHD 6/3/99)
  text-cell-line-quadding? nil

  text-cell-font-map (hm18)
  text-cell-line-height 22
  text-cell-baseline-position 18
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 4))

(def-text-cell-format new-small-logo-new-copyright-format
  text-cell-line-color? dim-gray
  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 20
  text-cell-top-margin 0
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 15 ; if line spills over, have it 
					;    look right (MHD 6/3/99)
  minimum-format-width-for-text-cell 800 ; expanded to fit more
					;    platform info on one line; 
					;    previously 600 (MHD 6/3/99)
  text-cell-line-quadding? nil

  text-cell-font-map (hm18)
  text-cell-line-height 22
  text-cell-baseline-position 18
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 4))

(def-text-cell-format new-large-logo-new-copyright-format
  text-cell-line-color? dim-gray
  text-cell-left-margin 24
  text-cell-top-margin 0
  text-cell-right-margin 24
  text-cell-top-margin 0
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 15 ; if line spills over, have it 
					;    look right (MHD 6/3/99)
  minimum-format-width-for-text-cell 800 ; expanded to fit more
					;    platform info on one line; 
					;    previously 600 (MHD 6/3/99)
  text-cell-line-quadding? nil

  text-cell-font-map (hm18)
  text-cell-line-height 22
  text-cell-baseline-position 18
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 4))

(def-text-cell-format fine-print-format
  text-cell-line-color? dark-gray
  text-cell-left-margin 24
  text-cell-top-margin 6
  text-cell-right-margin 24
  text-cell-bottom-margin 10

  text-cell-paragraph-indentation 0		; these were both
  text-cell-turnover-line-indentation 0		;   4 until 9/5/89
						;   -- why? (MHD)

  minimum-format-width-for-text-cell 500

  text-cell-line-quadding? nil

  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 4))

(def-class (gensym-logo entity)
  (icon-description
    (:funcall-at-load-time create-gensym-logo-description 6))) ; in module ICONS

(def-class (small-gensym-logo gensym-logo)
  (icon-description
    (:funcall-at-load-time create-gensym-logo-description 1)))


#+rh-gensym-logo
(progn
(def-class (new-gensym-logo entity)
  (icon-description
    (:funcall-at-load-time create-new-gensym-logo-description 128)))

(def-class (large-new-gensym-logo entity)
  (icon-description
    (:funcall-at-load-time create-new-gensym-logo-description 256)))

(def-class (small-new-gensym-logo gensym-logo)
  (icon-description
    (:funcall-at-load-time create-new-gensym-logo-description 32)))

(def-class (large-new-gensym-logo-with-tagline entity)
  (icon-description
    (:funcall-at-load-time create-new-gensym-logo-description 256 'tagline)))
)



(def-class (icon-cell block))

(def-class-method draw (icon-cell)
;  (draw-subblocks icon-cell)
  icon-cell)

(def-class-method compute-minimum-right-edge (icon-cell)
  (right-edge-of-block icon-cell))

(def-class-method compute-minimum-bottom-edge (icon-cell)
  (bottom-edge-of-block icon-cell))

(def-class-method resize (icon-cell available-width available-height other-data)
  other-data
  (loop for subblock being each subblock of icon-cell	; should be one subblock only!
	do (shift-block
	     subblock
	     (-w (+w (left-edge-of-block icon-cell)
		     (halfw (-w available-width
				(width-of-block subblock))))
		 (left-edge-of-block subblock))
	     (-w (+w (top-edge-of-block icon-cell)
		     (halfw (-w available-height
				(height-of-block subblock))))
		 (top-edge-of-block subblock))))

  (change-edges-of-block icon-cell nil nil
			 (+w (left-edge-of-block icon-cell) available-width)
			 (+w (top-edge-of-block icon-cell) available-height)))

;; Note that this trashes the margins!  (To remedy that, keep them in slots!)


;; Instead of these and other methods, have defaults that do the right thing!



(defun make-icon-cell (entity-class left-margin top-margin right-margin bottom-margin)  
  (make-icon-cell-for-entity
    (make-entity entity-class)
    left-margin top-margin right-margin bottom-margin))

(defun make-icon-cell-for-entity (entity left-margin top-margin right-margin bottom-margin)
  (let ((icon-cell (make-frame 'icon-cell)))
    (shift-block entity left-margin top-margin)
    (change-edges-of-block icon-cell nil nil
			   (+w (right-edge-of-block entity) right-margin)
			   (+w (bottom-edge-of-block entity) bottom-margin))
    (add-subblock entity icon-cell)
    icon-cell))







;;;; Help

(def-table-format help-table-format
  table-background-color? nil	; maybe aquamarine?
  table-row-boundary-width 0
  table-column-boundary-width 0
  table-left-border-width 0
  table-top-border-width 0
  table-right-border-width 0
  table-bottom-border-width 0)

(def-table-format-spot-generator help-table-format (table mouse-pointer)
  (generate-output-only-table-spot table mouse-pointer (make-output-only-table-spot)))


(def-text-cell-format help-title-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? center
  text-cell-left-margin 3
  text-cell-top-margin 2
  text-cell-right-margin 11
  text-cell-bottom-margin 2
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10

  text-cell-font-map (hm14)
  text-cell-line-height 20
  text-cell-baseline-position 16
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 6)

  minimum-format-width-for-text-cell 225)

(def-text-cell-format help-key-name-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 3
  text-cell-top-margin 2
  text-cell-right-margin 11
  text-cell-bottom-margin 2
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10

  text-cell-font-map (hm14)			;was recently swiss20 (6/13/87)
  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 6)

  minimum-format-width-for-text-cell 225)

(def-text-cell-format help-key-binding-format
  text-cell-lines-justified? nil
  text-cell-left-margin 11
  text-cell-top-margin 2
  text-cell-right-margin 3
  text-cell-bottom-margin 2
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 20

  text-cell-font-map (hm14)			;was recently swiss20 (6/13/87)
  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 6)

  minimum-format-width-for-text-cell 350)



;;; The def-substitution-macro `make-title-line-for-help-workspace' creates a text cell
;;; for the given title, s symbol.

(def-substitution-macro make-title-line-for-help-workspace (title)
  (slot-value-list (slot-value-list nil nil nil (make-text-cell (slot-value-list title) 'help-title-format))))



(defun ui-command-name-for-describe-keymap (name)
  (let ((cmd? (find-ui-command name)))
    (if cmd?
	(remove-character-from-wide-string
	  #.%&
	  (translated-string-for-symbol (ui-command-menu-name cmd?) :first t))
	name)))
		     

;;; The function `describe-keymap-into-table-rows' works on new-style keymaps.
;;; The created table has 4 columns looking like "keys handler keys handler".
;;; For the top-level context, this could be a static list!

(defun describe-keymap-into-table-rows (name bindings)
  (let ((row ())
	(rows ())
	(key-patterns-and-classes ())
	(previous-handler nil)
	(row-length 4))
    (macrolet ((emit-row (&optional force-p)
		 `(when key-patterns-and-classes
		    (let* ((key-string (twith-output-to-text-string
					 (twrite-key-patterns-and-classes
					   (nreverse key-patterns-and-classes))))

			   (key-cell (make-text-cell (slot-value-list key-string)
						     'help-key-name-format))
			   ;; Should this be doing menu-item-string?
			   (pretty (if (text-string-p previous-handler)
				       (copy-text-string previous-handler)
				       (ui-command-name-for-describe-keymap previous-handler)))
			   (handler-cell (make-text-cell (slot-value-list pretty)
							 'help-key-binding-format)))
		      (reclaim-list)
		      (slot-value-push key-cell row)
		      (slot-value-push handler-cell row)
		      (when (or ,force-p (= (length row) row-length))
			(slot-value-push (nreverse row) rows)
			(setq row nil)))))
	       (reclaim-list ()
		 `(progn
		    (loop for element in key-patterns-and-classes
			  doing (reclaim-slot-value-cons element))
		    (reclaim-slot-value-list key-patterns-and-classes)
		    (setq key-patterns-and-classes nil)))

	       (push-entry (key-pattern class)
		 `(slot-value-push (slot-value-cons ,key-pattern ,class)
				   key-patterns-and-classes)))
      
      (when bindings
	(with-localization-domain 'menu
	  (with-localization-purpose 'menu-item
	    ;; Ignore specialized handler? Or, depend on spot?
	    ;; Coalesce adjacent key-patterns with the same handler.
	    (loop for sublist on bindings
		  as bucket = (car sublist)
		  as key-pattern = (keymap-bucket-key-pattern bucket)
		  as handlers = (keymap-bucket-handlers bucket)
		  doing
	      (loop for (class handler . options) in handlers doing
		;; Only give help on handlers which are UI commands or
		;; mouse tracking procedures and 
		;; are on user-visible classes.
		(when (and (or (consp handler) ; see note D below
			       (find-ui-command handler))
			   (or (eq class t)
			       (and (symbolp class) (class-description class))
			       (and (consp class) (loop for c in class always (class-description c)))))
		  (let* ((handler-string
			   (if (consp handler) ; see note D below
			       (translated-string-for-symbol (second handler))))
			 (new-handler
			   (if handler-string
			       (prog1 (twith-output-to-text-string
					(tformat "~a ~a" #w"calls" handler-string))
				 (reclaim-wide-string handler-string))
			       handler)))
		    (cond ((or (neq new-handler previous-handler)
			       (null (cdr sublist)))
			   (emit-row)
			   (push-entry key-pattern class)
			   (setq previous-handler new-handler))
			  (t
			   (push-entry key-pattern class)))))))

	    (emit-row t)
	    
	    (nconc
	      (make-title-line-for-help-workspace name)
	      (nreverse rows))))))))

;; Note D
;; handler can be an atom or list. List format:
;; (USER-MOUSE-TRACKING <mouse-tracking-procedure-name> (<item>))
;; If it is an atom, use that, if it is a non-nil list, use the
;; procedure name. At this time, the only possible first thing in the
;; list is user-mouse-tracking, followed by the procedure name.



;;; The function `describe-workstation-context-keymaps' returns a list of
;;; tables rows, one for each binding of each keymap in the given workstation
;;; context.

(defun describe-workstation-context-keymaps (context-description frame?)
  (loop for keymap-name in (context-description-keymaps context-description)
	as keymap? = (keymap-named keymap-name)
	when (and keymap?
		  (keymap-enabled-p keymap?)
		  (not (keymap-private-p keymap?)))
	  nconcing (describe-keymap keymap? frame?)))


(defun describe-workstation-context-stack (frame?)
  (loop for context-name? = (type-of-workstation-context current-workstation-context)
			 then (find-workstation-context
				(context-description-parent
				  context-description))
	while context-name?
	as context-description = (find-workstation-context context-name?)
	nconcing (describe-workstation-context-keymaps context-description frame?)))



;;; The function `make-help-workspace' creates a workspace which displays a
;;; table of the currently active key bindings.  It looks in the current
;;; context, in the object configuration for the frame, and in the top-level
;;; context.  Hopefully, this is the same order in which they are scanned by
;;; the event processing routines.

(defun make-help-workspace (frame?)
  (let* ((table-rows
	   (describe-workstation-context-stack frame?))
	 (table
	   (make-or-reformat-table table-rows 'help-table-format nil nil t))
	 (workspace
	   (make-workspace 'temporary-workspace nil table 10)))
    
    (setf (frame-style-of-block workspace) 'thick-workspace-frame-style)
    
    workspace))

;; This takes too much time.  Improve!



#+development
(defun description-of-current-workstation-context (frame?)
  (twith-output-to-text-string
    (when (framep frame?)
      (cond ((and (block-p frame?) (name-or-names-for-frame frame?))
	     (tformat "Object: ~a ~a, " (class frame?) (name-or-names-for-frame frame?)))
	    (t
	     (tformat "Object: ~a, " frame?))))
    (tformat "Context: ")
    (loop for context in (workstation-context-stack current-workstation)
	  as first-time? = t then nil
	  do (if (not first-time?) (tformat " <- "))
	     (tformat "~a" (type-of-workstation-context context)))))




;;;; Help with Special Characters


(def-text-cell-format special-character-help-text-cell-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? left
  text-cell-left-margin 3
  text-cell-top-margin 2
  text-cell-right-margin 11
  text-cell-bottom-margin 2
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10

  text-cell-font-map (hm14)			;was recently swiss20 (6/13/87)
  text-cell-line-height 18
  text-cell-baseline-position 15
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 6)

  minimum-format-width-for-text-cell 225)

(def-text-cell-format special-character-help-header-text-cell-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? center
  text-cell-left-margin 3
  text-cell-top-margin 5
  text-cell-right-margin 11
  text-cell-bottom-margin 5
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10
  text-cell-line-color? white
  text-cell-background-color? black

  text-cell-font-map (hm14)
  text-cell-line-height 18
  text-cell-baseline-position 15
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 6)

  minimum-format-width-for-text-cell 200)

;;; `Make-diacritic-table-row' ... name should be a constant string, and
;;; key-for-accent should a character or a list of characters that follow the
;;; special character entry key (i.e., Alt-I) for input to get the appropriate
;;; accent ("diacritic").

;;; This was all written to work with the tables set up for Gensym character
;;; encodings, now AKA UTF-G, so there's some obscure switching from UTF-G to
;;; Unicode happening below.  (MHD 3/5/96)

(defun make-diacritic-table-row (name key-for-accent)
  (loop with text-cell-format-name
	  = 'special-character-help-text-cell-format
	with name-column
	  = (make-text-cell
	      (convert-text-string-to-text (copy-text-string name))
	      text-cell-format-name)
	with type-in-sequence-column
	  = (make-text-cell
	      (make-text-for-special-character-type-ins key-for-accent)
	      text-cell-format-name)
	with match-for-key-for-accent
	  = (char-downcasew ; normalize to lowercase; just match first, if a list
	      (if (atom key-for-accent) key-for-accent (car key-for-accent)))
	for (presentation lowercase? base? type-ins?)
	    in editor-special-character-alist
	when (and base?
		  (if (listp type-ins?)
		      (loop for c in type-ins?
			    thereis (char-equalw match-for-key-for-accent c))
		      (char-equalw match-for-key-for-accent type-ins?)))
	  collect (gensym-cons base? presentation)
	    into base-and-presentations-characters
	    using gensym-cons
	finally
	  ;; sort collection alphabetically:
	  (setq base-and-presentations-characters
		(sort-list
		  base-and-presentations-characters
		  #'char-lesspw-function #'car))
	  ;; create and return the rows, after recycling collection:
	  (return
	    (prog1
	      (slot-value-list 
		(make-text-cell
		  (make-text-for-diacritic-table-row-with-presentations
		    base-and-presentations-characters)
		  text-cell-format-name)
		(make-text-cell
		  (make-text-for-diacritic-table-row-with-type-ins
		    base-and-presentations-characters)
		  text-cell-format-name)
		type-in-sequence-column
		name-column)
	      (reclaim-gensym-tree
		base-and-presentations-characters)))))

(defun twrite-help-table-character (wide-character)
  (let ((char-or-string
	  (case wide-character
	    (#.%tab #w"Tab")
	    (#.%space #w"Space")
	    (#.%return #w"Return")
	    (#.%no-break-space #w"Nonbreaking Space")
;	    (#.%no-break-hyphen #w"Nonbreaking Hyphen")  ; when defined!
	    ;; add more cases when necessary!
	    (t wide-character))))
    (cond
      ((wide-character-p char-or-string)
       (twrite-char #.%space)
       (twrite-char char-or-string))
      (t
       (twrite-string char-or-string)))))
    
    

(defun make-text-for-diacritic-table-row-with-presentations
    (base-and-presentations-characters)
  (twith-output-to-text
    (loop for ((nil . presentation) . more?)
	      on base-and-presentations-characters
	  do (twrite-help-table-character presentation)
	     (if more? (tformat " ")))))

(defun make-text-for-diacritic-table-row-with-type-ins
    (base-and-presentations-characters)
  (twith-output-to-text
    (loop for ((base-character) . more?)
	      on base-and-presentations-characters
	  do (twrite-help-table-character base-character)
	     (if more? (tformat " ")))))


;;; `Make-text-for-special-character-type-ins' ... type-ins should be
;;; a single wide character or a list of wide characters that can be
;;; typed in after Alt+I.  The result is the text as an or list of
;;; the form
;;;
;;;    Alt+I <char1>, <char2>, ..., or <charN>
;;;
;;; (made shorter for lists of 1 or 2 in length in the usual way).

(defun make-text-for-special-character-type-ins (type-ins)  
  (twith-output-to-text
    (cond
      ((atom type-ins)
       (tformat "Alt\+i ")
       (twrite-help-table-character type-ins))
      (t
       (loop for l on type-ins
	     do (tformat "Alt\+i")
		(twrite-help-table-character (car l))
		(if (cdr l)
		    (if (null (cddr l))	; 2nd to last?
			(twrite-string
			  (if (eq l type-ins)
			      " or "	; => first time through
			      ", or "))
			(twrite-string ", "))))))))


(defun make-diacritic-header-table-row ()
  (let* ((text-cell-format-name
	   'special-character-help-text-cell-format))
    (slot-value-list
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Special Characters"))
	text-cell-format-name)
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Base Characters"))
	text-cell-format-name)
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Type-In Sequence"))
	text-cell-format-name)
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Diacritic"))
	text-cell-format-name))))

(defun make-standalone-header-table-row ()
  (let* ((text-cell-format-name
	   'special-character-help-text-cell-format))
    (slot-value-list
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Special Character"))
	text-cell-format-name)
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Type-In Sequence"))
	text-cell-format-name)
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Special Character"))
	text-cell-format-name)
      (make-text-cell
	(convert-text-string-to-text
	  (copy-constant-wide-string #w"Type-In Sequence"))
	text-cell-format-name))))

(defun make-standalone-special-character-rows ()  
  (loop with l = editor-special-character-alist
	as row?
	   = (loop for columns?
		       = (make-standalone-special-character-row-if-necessary (pop l))
		   with number-of-columns-so-far = 0
		   when columns?
		     nconc columns? into row
		     and (incff number-of-columns-so-far)
		   while l
		   until (>f number-of-columns-so-far 1)
		   finally
		     (return row))
	when row?
	  collect row? using slot-value-cons
	while l))

(defun make-standalone-special-character-row-if-necessary
    (editor-special-character-alist-entry)
  (let ((text-cell-format-name 'special-character-help-text-cell-format))
    (gensym-dstruct-bind
	((presentation lowercase? base? type-ins?)
	 editor-special-character-alist-entry)
      lowercase?
      (when (and (null base?) type-ins?)
	(slot-value-list
	  (make-text-cell
	    (twith-output-to-text
	      (twrite-help-table-character presentation))
	    text-cell-format-name)
	  (make-text-cell
	    (make-text-for-special-character-type-ins type-ins?)
	    text-cell-format-name))))))

(defun make-diacritic-help-table-rows ()
  (nconc
    (slot-value-list
      (slot-value-list
	nil nil nil
	(make-text-cell
	  (convert-text-string-to-text
	    (copy-constant-wide-string #w"Special Characters with Diacritics"))
	  'special-character-help-header-text-cell-format)))
    (slot-value-list (make-diacritic-header-table-row))
    (loop for (name key-for-accent)
	      in '(("Grave" #.%\`)		; hand-derived, unfortunately,
		   ("Acute" #.%\')		;    from (editor-)special-character-alist-
		   ("Circumflex" #.%\^)		;    entry! 
		   ("Umlaut" (#.%\: #.%\"))		; in order of most instances, as
		   ("Tilde" #.%\~)		;   determined by eye
		   ("Ligature" #.%\e)
		   ("Slash" #.%\/)
		   ("Cedilla" #.%\,)
		   ("Ring" (#.%\O #.%\o #.%\0))
		   ("Double Acute" (#.%\=))
		   ("Breve" (#.%\U #.%\u))
		   ("Dot Above" (#.%\I #.%\i)))
	  collect (make-diacritic-table-row name key-for-accent)
	    using slot-value-cons)))


(defun make-standalone-special-character-help-table-rows ()
  (nconc
    (slot-value-list
      (slot-value-list
	nil nil nil
	(make-text-cell
	  (convert-text-string-to-text
	    (copy-constant-wide-string #w"Standalone Special Characters"))
	  'special-character-help-header-text-cell-format)))
    (slot-value-list (make-standalone-header-table-row))
    (make-standalone-special-character-rows)))


(defun make-special-character-help-table ()
  (let ((table-rows
	  (nconc
	    (make-diacritic-help-table-rows)
	    (make-standalone-special-character-help-table-rows)
	    (make-hex-code-help-table-rows (current-language)))))
    (make-or-reformat-table
      table-rows 'help-table-format nil)))

(defun make-hex-code-help-table-rows (language)
  (let* ((script
	   (case language
	     (japanese 'kanji)
	     (korean 'hangul)
	     (russian 'cyrillic)
	     (t 'unicode))))
    (let* ((charset-name
	     (case script
	       (hangul "Hangul (KS C 5601)")
	       (cyrillic "Cyrillic (ISO 8859-5)")
	       (kanji "Kanji (JIS)")
	       (unicode "Unicode 2.0")))
	   (code-digit-length
	     (case script
	       (cyrillic 2)
	       (t 4))))
      (slot-value-list
	(slot-value-list
	  nil nil nil
	  (make-text-cell
	    (convert-text-string-to-text
	      (tformat-text-string "For ~a"
				   (if (memq language '(japanese korean russian))
				       language
				       "Unicode")))
	    'special-character-help-header-text-cell-format))
	(slot-value-list
	  nil nil nil
	  (make-text-cell
	    (convert-text-string-to-text
	      (tformat-text-string
		"Enter Alt+i followed by a ~d-digit ~a hex code.  ~
             ~%Precede with x to force hex interpretation if ~
             the first digit is ambiguous. - e.g. \"xC49A\""
		code-digit-length charset-name))
	    'special-character-help-text-cell-format))))))




;;; `Put-up-special-character-help-workspace' puts a table of type-in sequences
;;; for entering special characters from the keyboard up on a temporary workspace
;;; on current-workstation-detail-pane.  The image of the workspace is positioned
;;; in the bottom, right corner of the pane.

(defun put-up-special-character-help-workspace ()
  (let ((special-character-help-workspace
	  (make-workspace
	    'temporary-workspace nil nil
	    0))
	(special-character-help-table
	  (make-special-character-help-table)))
    (add-to-workspace
      special-character-help-table
      special-character-help-workspace
      (+w (left-edge-of-block special-character-help-workspace)
	  (workspace-margin special-character-help-workspace))
      (+w (top-edge-of-block special-character-help-workspace)
	  (workspace-margin special-character-help-workspace)))
    (put-workspace-on-pane
      special-character-help-workspace
      current-workstation-detail-pane
      'right 'bottom nil)))

;; It goes in the bottom, right because when the user is editing, his edit workspace
;; is usually in the top, right, so this will hopefully be out of his way.



;; The rest of these are not really needed or used at present.
;
;(defun make-diacritic-help-table ()
;  (let ((table-rows
;	  (make-diacritic-help-table-rows)))
;    (make-or-reformat-table
;      table-rows 'help-table-format nil)))

;(defun make-standalone-special-character-help-table ()
;  (let ((table-rows
;	  (make-standalone-special-character-help-table-rows)))
;    (make-or-reformat-table
;      table-rows 'help-table-format nil)))

;(defun put-up-diacritic-help-table ()
;  (let ((special-characters-help-workspace
;	  (make-workspace
;	    'temporary-workspace nil nil
;	    10))
;	(diacritic-help-table
;	  (make-diacritic-help-table)))
;    (add-to-workspace
;      diacritic-help-table
;      special-characters-help-workspace
;      (+w (left-edge-of-block special-characters-help-workspace)
;	  (workspace-margin special-characters-help-workspace))
;      (+w (top-edge-of-block special-characters-help-workspace)
;	  (workspace-margin special-characters-help-workspace)))      
;    (put-workspace-on-pane
;      special-characters-help-workspace
;      current-workstation-detail-pane
;      'center 'center nil)))

;(defun put-up-standalone-special-character-help-table ()
;  (let ((special-characters-help-workspace
;	  (make-workspace
;	    'temporary-workspace nil nil
;	    10))
;	(standalone-special-character-help-table
;	  (make-standalone-special-character-help-table)))
;    (add-to-workspace
;      standalone-special-character-help-table
;      special-characters-help-workspace
;      (+w (left-edge-of-block special-characters-help-workspace)
;	  (workspace-margin special-characters-help-workspace))
;      (+w (top-edge-of-block special-characters-help-workspace)
;	  (workspace-margin special-characters-help-workspace)))      
;    (put-workspace-on-pane
;      special-characters-help-workspace
;      current-workstation-detail-pane
;      'center 'center nil)))







;;;; Breakpoints, Pausing During Debugging, and Internal Errors



(defvar inside-breakpoint-p nil)

(def-system-variable return-from-breakpoint-task RUN nil)

(defun immediately-return-from-breakpoint (value)
  (cancel-task return-from-breakpoint-task)
  (when inside-breakpoint-p
    (throw 'return-from-breakpoint value)))

(defun return-from-breakpoint (&optional value)
  (when (and inside-breakpoint-p
	     (null return-from-breakpoint-task))
    (with-immediate-scheduling (return-from-breakpoint-task)
      (immediately-return-from-breakpoint value))))


;; Changed message to not refer to internal slot-name. -dkuznick, 10/15/98
(defun debugger-disable-debugging ()
  (notify-user
    "Disabling debugging by changing the \"Tracing and breakpoints enabled?\" ~
     debugging parameter to \"no\".  Please edit the debugging parameters to ~
     reenable debugging.")
  (change-slot-value
    debugging-parameters
    'message-and-breakpoint-overrides
    nil)
  (return-from-breakpoint))


; This doesn't work right.  It doesn't take into account the currently
; executing procedure, which is going to continue execution upon the return from
; pause-for-internal-error-or-debug, even if the system is paused!

; Changed to not actually return from the breakpoint.

(defvar allow-debugger-pause t)

(defvar show-procedure-invocation-hierarchy-on-debugger-pause-p t)
(defvar computation-instance-at-breakpoint nil)
(defvar computation-frame-at-breakpoint nil)
(defvar all-computation-instances-above-breakpoint nil)
(defvar may-return-from-breakpoint nil)
(defvar pane-for-debugger-pause nil)

(defun debugger-pause (pane)
  (when (and allow-debugger-pause inside-breakpoint-p)
    (notify-user "System will remain paused at this breakpoint.  ~
                  Use \"Continue From Breakpoint\" to resume execution.")
    (setf pane-for-debugger-pause pane)
    (return-from-breakpoint 'pause)))


(defun-simple computation-frame-at-breakpoint-depends-on-block-p (block)
  (and computation-frame-at-breakpoint
       (or (not (transient-p computation-frame-at-breakpoint))
	   (transient-p block))  ;; optimization
       (existence-depends-on-p
	 computation-frame-at-breakpoint block)))



;;; `Break-out-of-debug-messages' is called each time a message is printed.  It
;;; scans ahead in the event queue of every workstation for a control+Z.  If
;;; one is found, it then pauses the system.

(defun break-out-of-debug-messages ()
  (unless system-has-paused
    (block found
      ;; may want to support TWII
      (loop for workstation in workstations-in-service
	    doing
	(for-workstation (workstation) (poll-workstation))
	(loop for event being each queue-element of (workstation-event-queue workstation)
	      doing
	  (when (key-code-equivalent-p (workstation-event-code event) 'control+z)
	    (debugger-pause (detail-pane
					     (window-for-workstation workstation)))
	    (return-from found (values))))))))

;; I changed the semantics slightly -- this used to delete the ^Z from the queue.
;; -fmw, 11/23/94

;; Note that this function may be called in an on-window context, via
;; POST-TELEWINDOWS-CONNECTION-CLOGGED.  Poll-workstation must be careful to
;; never do any drawing. -fmw, 5/3/95


;;; The function `pause-during-debug' is assumed to be called in a context in
;;; which *current-computation-frame* is currently bound appropriately.  
;;;
;;; The argument should be a text string, which will not be reclaimed or
;;; incorporated by this function, or a halt-info structure, which will be
;;; reclaimed.
;;;
;;; This returns no useful value.

(defvar breakpoints-enabled-p t)

(defun-void pause-during-debug (message-or-halt-info)
  (when (and breakpoints-enabled-p (not inside-breakpoint-p))
    (pause-for-internal-error-or-debug message-or-halt-info t)
    (when (halt-info-p message-or-halt-info)
      (reclaim-halt-info message-or-halt-info))
    (setf pane-for-debugger-pause nil)))


;;; `Pause-for-internal-error' can be called in almost any context, but
;;; but it generally should "never" be called -- in that internal errors
;;; should "never" happen.  Thus, it may be called in cases where we
;;; can't handle it.  In such cases, a secondary error will result.  At
;;; that point we throw ourselves at the mercy of the operating system.
;;;
;;; The argument message should be a text string, which will not be reclaimed or
;;; incorporated by this function.
;;;
;;; This returns no useful value.

(defun-void pause-for-internal-error (message)
  (pause-for-internal-error-or-debug message nil))



;;; `Pause-for-internal-error-or-debug' is the internal subfunction of
;;; the above two functions.  It totally manages the state of G2 until
;;; the internal error or debug dialog has been dismissed by the user.

(defvar result-of-enter-dialog-for-t2-for-pause-for-internal-error-or-debug nil)

(defun-simple enter-dialog-for-pause-for-internal-error-or-debug
    (message-or-halt-info debug-case?)
  (multiple-value-bind (halt-info? message)
      (if (halt-info-p message-or-halt-info)
	  (values message-or-halt-info (halt-info-message message-or-halt-info))
	  (values nil message-or-halt-info))
    (setq result-of-enter-dialog-for-t2-for-pause-for-internal-error-or-debug
	  (enter-dialog-for-t2
	    (if debug-case?
		'breakpoint
		'internal-error)
	    (if debug-case?
		(nconc
		  (eval-list (eval-list 'text (copy-text-string message) 'breakpoint-message)
			     (eval-list 'button (copy-constant-wide-string #w"Disable debugging")
					'disable-debugging))
		  (when allow-debugger-pause
		    (eval-list (eval-list 'button (copy-constant-wide-string #w"Pause")
					  'pause)))
		  (eval-list (eval-list 'button (copy-constant-wide-string #w"Continue")
					'continue)
			     (eval-list 'item *current-computation-frame* 'item-causing-breakpoint)))
		(eval-list (eval-list 'text (copy-text-string message) 'abort-message)
			(eval-list 'button (copy-constant-wide-string #w"OK") 'ok)))
	    'finish-dialog-for-pause-for-internal-error-or-debug
	    nil
	    nil))
    (loop for workstation in workstations-in-service
	  as stack = (workstation-context-stack workstation)
	  collect (gensym-cons workstation stack) using gensym-cons
	  do (for-workstation (workstation)
	       (cond ((null debug-case?)
		      (enter-dialog
			(copy-text-string message)
			(copy-constant-wide-string #w"OK")
			'none
			'return-from-breakpoint
			nil nil nil nil nil nil nil nil nil nil ; unused args
			t))
		     ((and (native-debugger-dialog-p current-workstation-window)
			   halt-info?) ; TODO: want this condition?
		      (post-native-debugger-dialog
			halt-info? computation-frame-at-breakpoint
			current-workstation-window))
		     (t
		      (post-classic-debugger-dialog message)))))))

(defun post-classic-debugger-dialog (message)
  (enter-dialog
    (copy-text-string message)
    (copy-constant-wide-string #w"Disable debugging") ; OK
    (if allow-debugger-pause
	(copy-constant-wide-string #w"Pause")	  ; CANCEL
	(copy-constant-wide-string #w"Continue"))

    'debugger-disable-debugging nil

    (if allow-debugger-pause
	'debugger-pause
	'return-from-breakpoint)
    (and allow-debugger-pause
	 ;;to disply the procedure hierarchy on correct window -dkuznick, 3/8/99
	 (slot-value-list current-workstation-detail-pane))

    nil nil

    (if allow-debugger-pause      	  ; ADDITIONAL
	(copy-constant-wide-string #w"Continue")
	nil)
    (if allow-debugger-pause
	'return-from-breakpoint
	nil)
    nil

    (if allow-debugger-pause
	'additional
	'cancel)
    nil
    t				; was strictly modal
    (make-short-representation
      *current-computation-frame*)))


;; Native debugger's interface to debugging-parameters.

(def-substitution-macro debugger-get-source-stepping-p ()
  (eql source-stepping-level 1))

(def-substitution-macro debugger-set-source-stepping-p (torf)
  (let ((new-level (if torf 1 0)))
    (unless (eql new-level source-stepping-level)
      (change-slot-value debugging-parameters 'source-stepping-level new-level))))

;;; The function `debugger-get-breakpoints' returns a new eval-list of line
;;; numbers, with a flag bit to mark disabled breakpoints.

(defun debugger-get-breakpoints (procedure)
  (let* ((breakpoints (get-dynamic-breakpoints-internal procedure))
	 (fixnum-list (loop for bkpt in breakpoints
			    as line = (dynamic-breakpoint-line-func bkpt)
			    collect (if (dynamic-breakpoint-enabled-p bkpt) line
					(logiorf line editor-disabled-breakpoint-flag))
			      using eval-cons)))
    (reclaim-eval-list breakpoints)
    fixnum-list))

(defun post-native-debugger-dialog (halt-info computation-frame gensym-window)
  (let* ((source-code
	   (frame-class-case computation-frame
	     (procedure
	       (convert-text-to-text-string
		 (procedure-definition-function computation-frame)))
	     (rule
	       (convert-text-to-text-string
		 (cdr (box-translation-and-text computation-frame))))
	     (t
	       (copy-wide-string #w"No source code to display."))))
	 (title
	   (twith-output-to-wide-string
	     (tformat "G2 Break in ~NF" computation-frame)
	     (when (halt-info-line? halt-info)
	       (tformat ", line ~d" (halt-info-line? halt-info)))
	     (tformat ", instruction ~d" (halt-info-instruction halt-info))))
	 (options
	   (eval-list 'source-stepping (debugger-get-source-stepping-p)
		      'breakpoints (debugger-get-breakpoints computation-frame)
		      'tab-width (number-of-spaces-to-insert-on-a-tab editor-parameters))))
    ;; TODO: Ignoring halt-info-stack !
    (manage-debugger-dialog
      gensym-window debugger-dialog-create
      (or (halt-info-line? halt-info)
	  (if (=f (halt-info-instruction halt-info) 0) 1 -1))
      title
      (or (halt-info-user-message? halt-info) #w"")
      source-code			; TODO: Show disassembly if source unavailable?
      (halt-info-environment halt-info)
      options)
    (reclaim-wide-string title)
    (reclaim-wide-string source-code)
    (reclaim-eval-tree options)))


(defun cancel-native-debugger-dialog (gensym-window)
  (when (native-debugger-dialog-p gensym-window)
    (manage-debugger-dialog gensym-window debugger-dialog-cancel)))

(defun finish-dialog-for-pause-for-internal-error-or-debug (dialog-sequence-number client-item)
  (prog1 
      (when (eql result-of-enter-dialog-for-t2-for-pause-for-internal-error-or-debug
		 dialog-sequence-number)
	(execute-breakpoint-button
	  (leave-dialog-for-t2
	    result-of-enter-dialog-for-t2-for-pause-for-internal-error-or-debug)))
    (remove-dialog-info-from-ui-client-interface-dialog-list
      dialog-sequence-number
      (ui-client-session-parent-interface client-item))))

(defun execute-breakpoint-button (button)
  (case button
    (disable-debugging
     (debugger-disable-debugging))
    (pause
     (debugger-pause nil)
     ;; passing in a null pane above will cause the procedure invocation hierarchy
     ;; to appear on (car (panes-in-window system-window))
     ;; which is not what we want to happen (ie for the t2 case)
     )
    (continue
     (return-from-breakpoint))
    (ok
     (return-from-breakpoint))
    (t
     (dwarn "Unknown breakpoint button ~s" button))))

(defun leave-dialog-for-pause-for-internal-error-or-debug (workstations-with-their-stacks)
  ;; We're back: abort all contexts (safely) to previous level,
  ;; or, if in doubt, to top level
  (leave-dialog-for-t2
    result-of-enter-dialog-for-t2-for-pause-for-internal-error-or-debug)
  (loop for workstation in workstations-in-service
	as stack = (cdr (assq workstation
			      workstations-with-their-stacks))
	as gensym-window = (window-for-workstation workstation)
	do (when (native-debugger-dialog-p gensym-window)
	     (cancel-native-debugger-dialog gensym-window))
	when (loop for current-stack on (workstation-context-stack workstation)
		   thereis (equal stack current-stack))
	  do (for-workstation (workstation)
	       (loop while (cdr (workstation-context-stack workstation))
		     until (eq stack (workstation-context-stack workstation))
		     do
		 (abort-current-workstation-context type-of-current-workstation-context))))
  (loop for x in workstations-with-their-stacks
	do (reclaim-gensym-cons x)
	finally (reclaim-gensym-list workstations-with-their-stacks)))

(defun-void pause-for-internal-error-or-debug (message-or-halt-info debug-case?)
  (system-pause :abort (not debug-case?))
  (let* ((computation-instance-at-breakpoint current-computation-instance)
	 (computation-frame-at-breakpoint *current-computation-frame*)
	 (all-computation-instances-above-breakpoint
	   (when debug-case?
	     (list-callers-of-computation-instance computation-instance-at-breakpoint)))
	 (may-return-from-breakpoint t)
	 (result-of-enter-dialog-for-t2-for-pause-for-internal-error-or-debug nil)
	 (workstations-with-their-stacks
	   (enter-dialog-for-pause-for-internal-error-or-debug message-or-halt-info debug-case?))
	 (return-value
	   (run-scheduler-for-breakpoint)))
    (leave-dialog-for-pause-for-internal-error-or-debug workstations-with-their-stacks)
    (when debug-case?
      (when (eq return-value 'pause)
	(when (and computation-instance-at-breakpoint
		   show-procedure-invocation-hierarchy-on-debugger-pause-p
		   #+runtime-functionality-without-a-license
		   nil
		   #-runtime-functionality-without-a-license
		   (not (g2-limited-to-this-license-level-or-more restricted-use)))
	  (graph-detailed-procedures
	    nil nil all-computation-instances-above-breakpoint))
	(setq return-value (run-scheduler-for-breakpoint)))
      (reclaim-gensym-list all-computation-instances-above-breakpoint)
      (setq all-computation-instances-above-breakpoint nil)
      (when may-return-from-breakpoint
	(validate-executing-statements-and-procedures))
      (system-resume)
      (when (and (consp return-value)
		 (eq (car return-value) 'g2-set-g2-state))
	(return-from-g2-set-g2-state (cdr return-value))
	(reclaim-eval-cons return-value))
      (maybe-schedule-service-workstations t)
      (unless may-return-from-breakpoint
	(setq current-computation-instance nil)
	(setq current-schedule-task nil)
	(raw-stack-error-1
	  -1
	  'error
	  (copy-constant-wide-string #w"procedure invocations were aborted while in a breakpoint"))))))





;;;; Development-only Tabular Displays




;;; This subsection implements the Memory Management and Telewindows Status
;;; tabular display facilities.


#+development
(def-class (development-tabular-display table)
  (development-tabular-display-frozen? nil lookup-slot (type nil)))






#+development
(def-class (telewindows-status-table development-tabular-display)
  (status-table-frame-serial-number nil vector-slot system))

(def-slot-value-reclaimer status-table-frame-serial-number (fsn)
  (reclaim-frame-serial-number fsn))

#+development
(def-table-format telewindows-status-table-format
  table-background-color? nil
  table-line-color? black
  table-row-boundary-width 0
  table-column-boundary-width 1
  table-left-border-width 1
  table-top-border-width 1
  table-right-border-width 1
  table-bottom-border-width 1)

#+development
(def-table-format-spot-generator telewindows-status-table-format (table mouse-pointer)
  (generate-output-only-table-spot table mouse-pointer (make-output-only-table-spot)))

#+development
(def-text-cell-format telewindows-status-table-text-cell-format-for-headers
  text-cell-line-quadding? center
  text-cell-paragraph-indentation 0
  text-cell-line-color? nil
  text-cell-background-color? nil
  text-cell-left-margin 7
  text-cell-top-margin 7
  text-cell-right-margin 7
  text-cell-bottom-margin 7
  minimum-format-width-for-text-cell 100)

#+development
(def-text-cell-format telewindows-status-table-text-cell-format-for-data
  text-cell-line-quadding? right
  text-cell-paragraph-indentation 0
  text-cell-left-margin 7
  text-cell-top-margin 2
  text-cell-right-margin 7
  text-cell-bottom-margin 2)

#+development
(defun put-up-telewindows-status-table ()
  (let ((telewindows-status-table
	  (make-or-reformat-table	  
	    (nconc
	      (slot-value-list
		(loop for header-string
			  in '("Window"
			       "Status"		; unconnected, living, dead, clogged, etc.
			       "Seconds Since Last Sent"
			       "Seconds Since Last Received"
			       "Number of Groups Since"
			       "Number of Groups Outstanding"
			       "Number of Bytes Since"
			       "Number of Bytes Outstanding")
		      nconc
			(slot-value-list
			  (make-text-cell
			    (convert-text-string-to-text
			      (copy-text-string header-string))
			    'telewindows-status-table-text-cell-format-for-headers))))	; ok?
	      (loop for g2-window being each class-instance of 'g2-window
		    collect
		      (make-telewindows-status-table-row g2-window))
	      ;; consider having a total row here at the bottom
	      )
	    'telewindows-status-table-format nil
	    'telewindows-status-table nil)))
    (update-telewindows-status-table telewindows-status-table t)
    (put-workspace-on-pane
      (make-workspace 'temporary-workspace nil telewindows-status-table 5)
      current-workstation-detail-pane 'left 'top nil))
  (maybe-schedule-service-workstations-final))


#+development
(defun make-telewindows-status-table-row (g2-window)
  (let ((name (get-or-make-up-designation-for-block g2-window)))
    (when (symbolp name)
      (setq name (symbol-name-text-string name)))
    (nconc
      (slot-value-list
	(make-text-cell
	  (convert-text-string-to-text
	    (copy-text-string name))
	  'telewindows-status-table-text-cell-format-for-data
	  (slot-value-list
	    'g2-window g2-window		; non-standard properties!
	    ;; 'g2-window-sn (frame-serial-number g2-window)
	    'value (copy-text-string name))))
      (loop repeat 7
	    collect
	      (make-text-cell
		(convert-text-string-to-text (copy-constant-wide-string #w"NA"))
		'memory-management-table-text-cell-format-for-data)
			  using slot-value-cons))))

;;; An `i-am-alive status' for a given g2 window is a gensym list of the form
;;;
;;;   (status time-since-sent? time-since-received?
;;;    number-of-groups-since? number-of-groups-outstanding?)
;;;
;;; If status is UNCONNECTED, then all the other elements are nil.  Otherwise,
;;; time-since-sent?, time-since-received?, number-of-groups-since?, and
;;; number-of-groups-outstanding? are fixnums.  Time-since-sent? are time-
;;; since-received? in terms of seconds.

;;; `Compute-i-am-alive-status' returns an i-am-alive status for the given
;;; g2-window.

#+development
(defun compute-i-am-alive-status (g2-window)
  (let* ((i-am-alive-info?
	   (get-i-am-alive-info-for-g2-window-if-any	; can be nil here
	     g2-window)))
    (if (null i-am-alive-info?)
	(gensym-list 'unconnected nil nil nil nil)
	(let* ((status
		 (cond
		   ((null i-am-alive-info?)
		    'unconnected)
		   ((not (remote-process-alive-p i-am-alive-info?))
		    'dead)
		   ((icp-connection-clogged-p i-am-alive-info?)
		    'clogged)
		   (t 'alive)))
	       (fixnum-time-now (get-fixnum-time))
	       (time-since-sent			; in seconds
		 (convert-fixnum-time-difference-to-seconds
		   (fixnum-time-difference
		     fixnum-time-now
		     (time-i-am-alive-was-sent i-am-alive-info?))))
	       (time-since-received		; in seconds
		 (convert-fixnum-time-difference-to-seconds
		   (fixnum-time-difference
		     fixnum-time-now
		     (time-i-am-alive-was-received i-am-alive-info?))))
	       (number-of-groups-since
		 (number-of-message-groups-handled-since-last-I-am-alive-was-sent
		   i-am-alive-info?))
	       (number-of-groups-outstanding
		 (number-of-outstanding-message-groups i-am-alive-info?))
	       (number-of-bytes-since
		 (number-of-icp-bytes-handled-since-last-I-am-alive-was-sent
		   i-am-alive-info?))
	       (number-of-bytes-outstanding
		 (number-of-outstanding-icp-bytes i-am-alive-info?)))
	  (gensym-list
	    status time-since-sent time-since-received
	    number-of-groups-since number-of-groups-outstanding
	    number-of-bytes-since number-of-bytes-outstanding)))))



  
#+development
(defun update-telewindow-status-displays ()
  (loop for table being each class-instance of 'telewindows-status-table
	do (update-telewindows-status-table table)))


#+development
(defun update-telewindows-status-table (telewindows-status-table &optional initializing?)
  (let ((frame-serial-number
	  (if initializing?
	      (current-frame-serial-number)
	      (status-table-frame-serial-number telewindows-status-table))))
    (loop with first-data-row-index = 1
	  with table-rows = (table-rows telewindows-status-table)
	  with rows-to-delete? = nil
	  with g2-windows-not-updated
	    = (loop for g2-window being each class-instance of 'g2-window
		    collect g2-window using gensym-cons)
	  for row in (nthcdr first-data-row-index table-rows)
	  as row-index from first-data-row-index
	  as first-text-cell-plist = (text-cell-plist (first row))
	  as g2-window
	     = (getf first-text-cell-plist 'g2-window)
	  do (cond
	       ((frame-has-been-reprocessed-p g2-window frame-serial-number)
		(setq rows-to-delete? (slot-value-cons row rows-to-delete?)))
	       (t
		(setq g2-windows-not-updated
		      (delete-gensym-element
			g2-window g2-windows-not-updated))
		(let ((name (get-or-make-up-designation-for-block g2-window)))
		  (when (symbolp name)
		    (setq name (symbol-name-text-string name)))
		  (if (not (string=w name (getf first-text-cell-plist 'value)))
		      (update-cell-in-table
			telewindows-status-table row-index 0
			(convert-text-string-to-text
			  (copy-text-string name))
			nil (slot-value-list 'value (copy-text-string name)))))
		(loop with i-am-alive-status
			= (compute-i-am-alive-status g2-window)
		      for new-value in i-am-alive-status
		      with first-data-column-index = 1
		      for text-cell in (nthcdr first-data-column-index row)
		      as column-index from first-data-column-index
		      as old-value = (getfq (text-cell-plist text-cell) 'value)
		      when (or initializing? (not (eql old-value new-value)))
			do (update-cell-in-table
			     telewindows-status-table row-index column-index
			     (convert-text-string-to-text
			       ;; Keep a function to twrite the the cell's value
			       ;;   on the plist, and then replace this with a
			       ;;   funcall!
			       (case column-index
				 (1 (copy-symbol-name new-value nil))
				 (t (if new-value
					(twith-output-to-text-string
					  (tformat "~d" new-value))
					(copy-constant-wide-string #w"NA")))))
			     nil (slot-value-list 'value new-value))
		      finally (reclaim-gensym-list i-am-alive-status))))
	  finally
	    (when (or rows-to-delete? g2-windows-not-updated initializing?)
	      (unless initializing?
		(erase-images-of-block telewindows-status-table t))
	      (when rows-to-delete?
		(loop for row in rows-to-delete?
		      do (setq table-rows
			       (delete-slot-value-element row table-rows)))
		(reclaim-slot-value-list rows-to-delete?))
	      (when g2-windows-not-updated
		(loop for g2-window in g2-windows-not-updated
		      do (setq table-rows
			       (nconc
				 table-rows
				 (slot-value-list
				   (make-telewindows-status-table-row g2-window))))))
	      (setf (table-rows telewindows-status-table) table-rows)
	      (frame-serial-number-setf (status-table-frame-serial-number telewindows-status-table)
					(current-frame-serial-number))
	      (reformat-table-in-place telewindows-status-table)
	      ;; update now! (the following turds -- figure out why!)
;	     (if g2-windows-not-updated		; to update new rows
;		 (update-telewindows-status-table telewindows-status-table t))
	      (if g2-windows-not-updated
		  (reclaim-gensym-list g2-windows-not-updated))
	      (unless initializing?
		(draw-images-of-block telewindows-status-table t))))))





;; These formats have crept into KBs now, so, sigh, we must keep it in
;; non-development.  (MHD 11/15/94)
;; 
;; #+development
(progn
  
(def-table-format memory-management-table-format
  table-background-color? nil
  table-row-boundary-width 0
  table-column-boundary-width 1
  table-left-border-width 1
  table-top-border-width 1
  table-right-border-width 1
  table-bottom-border-width 1)

(def-text-cell-format memory-management-table-text-cell-format-for-data
  text-cell-line-quadding? right
  text-cell-paragraph-indentation 0
  text-cell-left-margin 3
  text-cell-top-margin 3
  text-cell-right-margin 3
  text-cell-bottom-margin 3)

(def-text-cell-format memory-management-table-text-cell-format-for-headers
  text-cell-line-quadding? center
  text-cell-paragraph-indentation 0
  text-cell-line-color? nil
  text-cell-background-color? nil
  text-cell-left-margin 3
  text-cell-top-margin 3
  text-cell-right-margin 3
  text-cell-bottom-margin 3)

(def-text-cell-format memory-management-table-text-cell-format-for-labels
  text-cell-line-quadding? nil
  text-cell-paragraph-indentation 0
  text-cell-left-margin 7
  text-cell-top-margin 3
  text-cell-right-margin 5
  text-cell-bottom-margin 3)
) ; end (progn ...)



#+development
(def-class (memory-management-table development-tabular-display)
  (memory-management-table-frozen?		; get rid of this -- use development-tabular-
    nil lookup-slot (type nil)))		;   display-frozen? instead!

#+development
(defvar object-pool-meters-sorted-alphabetically nil)

#+development
(defvar include-%out? nil)
#+development
(defvar include-memory? nil)

#+development
(defun put-up-memory-management-table (&rest args)
  (let* ((other-total 0) (other-out 0) (other-memory 0)
	 (grand-total 0) (grand-out 0) (grand-memory 0))
    (put-workspace-on-pane
      (make-workspace
	'temporary-workspace nil
	(make-or-reformat-table	  
	  (nconc
	    (slot-value-list
	      (loop for header-string
			in (if (and include-%out? include-memory?)
			       '("Pool Name" "Total" "Out" "%Out" "Memory")
			       (if include-%out?
				   '("Pool Name" "Total" "Out" "%Out")
				   (if include-memory?
				       '("Pool Name" "Total" "Out" "Memory")
				       '("Pool Name" "Total" "Out"))))
				       
		    nconc
		      (slot-value-list
			(make-text-cell
			  (slot-value-list
			    (copy-text-string header-string))
			  'memory-management-table-text-cell-format-for-headers))))
	    (loop for meter-entry
		      in (or object-pool-meters-sorted-alphabetically
			     ;;(equal object-pool-meters-sorted-alphabetically  ; do to 
			     ;;       object-pool-meters)                       ;   be safer?
			     (setq object-pool-meters-sorted-alphabetically
				   (sort-list
				     (copy-list object-pool-meters)
				     #'string-lessp
				     #'pool-entry-name)))
		  as pool-name = (pool-entry-name meter-entry)
		  as total = (pool-entry-object-count meter-entry)
		  as out = (pool-entry-outstanding-object-count meter-entry)
		  as memory
		     = (pool-entry-memory-usage-in-bytes meter-entry)
		  do (incf grand-total total)
		     (incf grand-out out)
		     (incf grand-memory memory)
		  if (not (if (eq args nil)
			      (memq pool-name names-of-interesting-system-object-pools)
			      (if (equal args '(t))
				  t
				  (memq pool-name args))))
		    do (incf other-total total)
		       (incf other-out out)
		       (incf other-memory memory)
		  else 
		    collect
		      (make-memory-information-table-row
			pool-name total out memory
			include-%out? include-memory?)
		     using slot-value-cons)
	    (slot-value-list
; Too expensive.
;	      (make-memory-information-table-row
;		'other-total other-total other-out other-memory
;               include-%out? include-memory?)
;	      (make-memory-information-table-row
;		'grand-total grand-total grand-out grand-memory
;               include-%out? include-memory?)
	      (make-memory-information-table-row
		'memory-usage (g2-memory-usage) 'na 'na
		include-%out? include-memory?)))
	  'memory-management-table-format nil
	  'memory-management-table nil)
	15)
      current-workstation-detail-pane
      'left 'bottom nil))
  (maybe-schedule-service-workstations-final))

#+development
(defun make-memory-information-table-row
       (pool-name total out memory
	include-%out? include-memory?)
  (let ((%out					; does this cons? !!!
	  (if (eq pool-name 'memory-usage)
	      'na
	      (floor (* out 100) (maxf total 1)))))
    (loop with l
	    = (nconc
		(slot-value-list
		  (tformat-text-string "~(~a~)" pool-name)
		  (tformat-text-string "~a" total)
		  (tformat-text-string "~a" out))
		(if include-%out?
		    (slot-value-list
		      (tformat-text-string "~a" %out)))
		(if include-memory?
		    (slot-value-list
		      (tformat-text-string "~a" memory))))
	  for ll on l
	  as first-time? = t then nil
	  do (setf (car ll)
		   (make-text-cell
		     (slot-value-list (car ll))
		     (if first-time?
			 'memory-management-table-text-cell-format-for-labels
			 'memory-management-table-text-cell-format-for-data)))
	  finally	    
	    (meterize-text-cell
	      (second l) pool-name 'object-count total)
	    (meterize-text-cell
	      (third l) pool-name 'outstanding-object-count out)
	    (if include-%out?
		(meterize-text-cell
		  (fourth l) pool-name '%outstanding-object-count %out))
	    (if include-memory?
		(meterize-text-cell
		  (fifth l) pool-name 'memory memory))
	    (return l))))

#+development
(def-table-format-spot-generator memory-management-table-format (table mouse-pointer)
  (generate-output-only-table-spot table mouse-pointer (make-output-only-table-spot)))

#+development
(defun meterize-text-cell (text-cell pool-name category-name value)
  (change-text-cell-property
    text-cell 'meter pool-name)
  (change-text-cell-property
    text-cell 'meter-category category-name)
  (change-text-cell-property
    text-cell category-name value))

#+development
(def-system-variable last-memory-allocation-display-cell-updated? run nil)

#+development
(def-system-variable last-memory-allocation-display-table-updated? run nil)

#+development
(defun update-memory-allocation-displays ()
  (loop for table being each class-instance of 'memory-management-table
	when
	  (and (not (memory-management-table-frozen? table))
	       (or (null last-memory-allocation-display-table-updated?)
		   (if (eq table last-memory-allocation-display-table-updated?)
		       (progn
			 (setq last-memory-allocation-display-table-updated?
			       nil)
			    t))))
	do (update-memory-allocation-display table)
    when last-memory-allocation-display-table-updated?
      do (return nil)))

#+development
(defmacro convert-memory-allocation-table-value-to-text-macro (value)
  `(slot-value-list
     (twith-output-to-text-string
       (twrite ,value))))

#+development
(defun update-memory-allocation-display (table)	  
  (loop with grand-total = nil				; until first needed, if ever
	with grand-out
	with grand-memory
	with other-total
	with other-out
	with other-memory
	for row in (table-rows table)
	as row-index from 0
	do (loop with old-value
		 with interval-between-updates = (fixnum-time-interval 1000)
		 for cell? in row
		 as column-index from 0
		 as meter? = (if (and cell? (not (cell-is-block-p cell?)))
				 (getf (text-cell-plist cell?) 'meter))
		 as meter-entry?
		    = (if meter? (assq meter? object-pool-meters))
		 as value?
		    = (cond
			((and (or meter-entry?
				  (memq meter?
					'(grand-total 
					   other-total memory-usage)))
			      (let ((my-last-update-time?
				      (getf (text-cell-plist cell?)
					    'meter-update-time)))
				(if my-last-update-time?
				    (>f (fixnum-time-difference
					  (get-fixnum-time)
					  my-last-update-time?)
					interval-between-updates)
				    t)))
			 (if (null grand-total)
			     (multiple-value-setq (grand-total grand-out grand-memory
						   other-total other-out other-memory)
			       (compute-totals-for-memory-management-table table)))
			 (let* ((text-cell-plist (text-cell-plist cell?))
				(meter-category
				  (getf text-cell-plist 'meter-category)))
			   (setq old-value (getf text-cell-plist meter-category))
			   (change-text-cell-property
			     cell? meter-category
			     ;; value:
			     (case meter-category
			       (object-count
				(case meter?
				  (other-total other-total)
				  (grand-total grand-total)
				  (memory-usage (g2-memory-usage))
				  (t 
				   (pool-entry-object-count meter-entry?))))
			       (outstanding-object-count
				(case meter?
				  (other-total other-out)
				  (grand-total grand-out)
				  (memory-usage 'na)
				  (t
				   (pool-entry-outstanding-object-count meter-entry?))))
			       (%outstanding-object-count
				(case meter?
				  (memory-usage 'na)
				  (t
				   (let (bottom)				  
				     (floor
				       (* 
					 (case meter?
					   (other-total
					    (setq bottom other-total)
					    other-out)
					   (grand-total
					    (setq bottom grand-total)
					    grand-out)
					   (t
					    (setq bottom (pool-entry-object-count meter-entry?))
					    (pool-entry-outstanding-object-count meter-entry?)))
					 100)
				       (maxf bottom 1))))))
			       (memory
				(case meter?
				  (other-total other-memory)
				  (grand-total grand-memory)
				  (memory-usage 'na)
				  (t
				   (pool-entry-memory-usage-in-bytes meter-entry?)))))))))
		 do (cond
		      (value?
		       (cond
			 ((not (eql value? old-value))

			  ;; To accumulate a list of which pools are changing uncomment this:
			  ; (pushnew meter? changing-pools)
			  ;; You'd have to (defvar changing-pools ()) to get this to work.
			  ;; Then you can (put-up-memory-management-table T) to monitor all pools
			  ;; after a while you do: (apply #'put-up-memory-management-table changing-pools)
			  ;; to just watch the ones that were changing. - BAH

			  (update-cell-in-table
			    table row-index column-index
			    (convert-memory-allocation-table-value-to-text-macro
			      value?)
			    nil
			    (slot-value-list
			      'meter-update-time (get-fixnum-time)
			      'meter-update-highlight-time (get-fixnum-time)))
			  
			  (change-color-of-text-cell
			    table cell? nil
			    (if (>f value? old-value) 'red 'gray)
			    :no-change :no-change t)
			  ;; Highlighting in a color is broken as of 4.0; it's not
			  ;; worth fixing, probably, so just change the color, which
			  ;; isn't all that expensive! (MHD 2/16/96)
;			  (highlight-or-unhighlight-cell
;			    cell? table
;			    (if (>f value? old-value) 'red 'gray) nil)
			  
			  )
			 ((and
			    (getf (text-cell-plist cell?)	; optimiz.; getfq ??
				  'background-color
;				  'highlight-color  ; commented as part of change
					            ;    away from highlighting (MHD 2/16/96)
				  )
			    (let ((my-last-highlight-time?
				    (getf (text-cell-plist cell?)
					  'meter-update-highlight-time)))
			      (if my-last-highlight-time?
				  (>f (fixnum-time-difference
					(get-fixnum-time)
					my-last-highlight-time?)
				      interval-between-updates))))
			  
			  (change-color-of-text-cell
			    table cell? nil 'transparent :no-change :no-change t)
			  ;; ditto. (see above) (MHD 2/16/96)
;			  (highlight-or-unhighlight-cell	; we do not simply unhighlight
;			    cell? table 'white nil)	        ;   here to avoid perturbing
								;   the slot value cons count
			  
			  )))))))


#+development
(defun compute-totals-for-memory-management-table (memory-management-table)
  (loop for pool-entry in object-pool-meters
	sum (pool-entry-object-count pool-entry)
	  into grand-total
	;; Note that the following can take HALF THE TIME of this
	;;   function in typical situations due to the fact that it
	;;   typically uses length operations on the outstanding object
	;;   pools to determine its value!!  The logic for computing
	;;   this would have to change to make this beter.
	;;   (MHD 2/20/90)
	sum (pool-entry-outstanding-object-count pool-entry)
	  into grand-out
	sum (pool-entry-memory-usage-in-bytes pool-entry)
	  into grand-memory
	finally
	  (return
	    (loop with other-total-so-far = grand-total
		  with other-out-so-far = grand-out
		  with other-memory-so-far = grand-memory
		  for row in (table-rows memory-management-table)
		  do (loop for cell? in row
			   as meter?
			      = (if (and cell? (not (cell-is-block-p cell?)))
				    (getf (text-cell-plist cell?) 'meter))
			   as meter-entry?
			      = (if meter? (assq meter? object-pool-meters))
			   as object-count-entry?
			      = (if meter-entry?
				    (eq (getf (text-cell-plist cell?) 'meter-category)
					'object-count))
			   when object-count-entry?
			     do (decf other-total-so-far
				      (pool-entry-object-count meter-entry?))
				(decf other-out-so-far
				      (pool-entry-outstanding-object-count meter-entry?))
				(decf other-memory-so-far
				      (pool-entry-memory-usage-in-bytes meter-entry?))
				(return nil))	; early return based on the assumption
						;   of one row per meter; also picking
						;   on object-count is an optimization
						;   based on the assumption that this
						;   occurs first in the table; this could
						;   all be even further optimized ....
		  finally
		    (return
		      (values
			grand-total grand-out grand-memory
			other-total-so-far other-out-so-far other-memory-so-far))))))



;; Fix Later!! (MHD 7/6/89)
;(def-block-menu memory-management-table
;  (slot-value-list
;    'transfer
;    (if (memory-management-table-frozen? memory-management-table)
;	'unfreeze
;	'freeze)
;    'delete))









;;;; Mode Changing



;; The password changing facility (next section) is implemented just now as
;; an overload on the user-setting editor. This leads to substantial problems
;; in organizing the internationalization code since there is only one
;; frame involved. The present plan (as of 3/13/98 (Friday the 13th)
;; ddm as per dwr) is that we pry these apart in a quick and quite dirty
;; way given that the code freezes this Sunday, then re-implement it in
;; a way that can be easily maintained before the next release.
;;
;; This flag will scope the entire operation, and is used to hack a
;; difference where one is needed.

(defvar doing-password-change-p nil)



;;; Change-mode enters the user settings editor with CHANGING-MODE as the
;;; value for how-entered.

;;; As a bit of a kludge, if (type-of-modal-context? current-workstation) is
;;; true, this will not work -- it will not enter a context to change the mode.
;;; This works as a kludge because it keeps users from entering a new context
;;; while in a modal context, such as the internal error breakpoint context.
;;; There are no other keyboard commands that can get you into a context you
;;; shouldn't be able to get into.  Note that we recently abandoned the
;;; hand-assembled "dialog" facility that managed the user interaction during
;;; an internal error breakpoint.  (MHD 3/28/97)

(defun change-mode ()
  (unless (type-of-modal-context? current-workstation)
    (let ((doing-password-change-p nil))
      (enter-user-settings-editor 'changing-mode))))




;;;; Password Changing


;;; `Enter-change-password-dialog' enters the user settings editor with
;;; PASSWORD-CHANGE as the value for how-entered.  This puts up slots
;;; appropriate to changing the user's password, i.e., user name, (old)
;;; password, new password, and a duplicate of the new password to avoid
;;; typing errors.

(defun enter-change-password-dialog ()
  (unless (type-of-modal-context? current-workstation)
    (let ((doing-password-change-p t))
      (enter-user-settings-editor 'password-change))))

;; This probably wants to be invoked under entirely different circumstances
;; as compared with change-mode, i.e., generally just by menu, not by command
;; (control-y), and generally not in as broad a set of circumstances.







;;;; G2 Login




;;; A `G2 login' is an object created to stand behind the change mode,
;;; or login dialog.  It is initially filled with info taken from the
;;; workstation.  When the dialog completes the info is put back into
;;; the workstation.  Meanwhile the g2-window is kept in synch.  Note
;;; that some of this info is also found on the command line, and in
;;; the window's plist.

;;; The encoded password is a function of both the user name and the
;;; password.  We keep a copy of the clear text password in here, and
;;; compute an encoded one when the dialog is attempting to finish up.

;;; Unless g2-user-discard-user-settings-for-this-workstation-p of the
;;; workstation corresponding to this login is true, we send to Telewindows a
;;; plist of the user settings (user-name, password (encrypted in two ways),
;;; user-mode, and language), as they exist whenever a login (user settings edit
;;; session) is attempted.  As of 5.0, this is only NOT done if the Telewindows
;;; requests this (through a command line or environment variable); in 4.0 and
;;; earlier, the failure to propagate this information was regarded as a bug, at
;;; least by certain users, so we decided to standardize on it.  In addition,
;;; this allows users to be able to only log in once.
;;;
;;; Note that this has some security consequences, and is intended to be used at
;;; the customer's sole risk, and should be warned about in the user manual for
;;; Telewindows.  The passwords are not sent back in the clear, but rather are
;;; encrypted (to the maximum extent allowed by law).  In addition, all password
;;; attempts are sent back, with no "quality" guarantee, i.e., whether they are
;;; accepted or not.  This somewhat mitigates the security problem.  Note that
;;; this feature/protocol is new for G2/TW version 5.0.
;;;
;;; Here's an additional security risk scenario: if a savvy user finds a
;;; Telewindow console that has been logged in, he can write some code to
;;; route it to a G2 of his choice, and as long as the user-name/password
;;; work for that G2, the Telewindow can get it.  This is what we think
;;; most users want to have happen.

(def-class (g2-login entity)
  (g2-login-comments
    nil (type g2-login-comments) lookup-slot
    not-user-editable do-not-identify-in-attribute-tables)
  (g2-login-user-name?
    nil (type name?) lookup-slot system)
  (g2-login-user-password? nil
    (type user-password) lookup-slot system)	; show invisibly
  (g2-login-user-mode
    nil (type g2-user-mode-for-login) lookup-slot system)
  (g2-login-window-name-or-class
    nil (type g2-login-window-designation) vector-slot system)
  (g2-login-specific-language-for-this-g2-window?
    nil (type language?) vector-slot system)
  (g2-login-style-specifically-for-this-workstation?
    nil (type g2-window-style-override)
    vector-slot system)
  (g2-login-init-string?		; don't have init-string be user visible (MHD 1/20/95)
    nil  (type nil)			; (type whole-string?)
    vector-slot system)
  (g2-login-attempts-counter
    0 lookup-slot system)
  (g2-login-encoded-password?
    nil
    ;; (or nil text-string)
    ;; see maintained by encode-password-via-md5
    vector-slot system)

  (g2-login-how-entered nil vector-slot system)	; records the value of  the
					;   how-entered var, as passed in to
					;   enter-user-settings-editor

  ;; for changing passwords:
  (g2-login-old-password? nil (type user-password) vector-slot system)
  (g2-login-encoded-old-password? nil (type user-password) vector-slot system)
  (g2-login-first-new-password? nil (type user-password) vector-slot system)
  (g2-login-first-encoded-new-password? nil vector-slot system)
  (g2-login-second-new-password? nil (type user-password) vector-slot system)
  (g2-login-second-encoded-new-password? nil vector-slot system))

;; All of slot initializations above are arbitrary -- the slots get filled in
;; at the beginning of enter-user-settings-editor.


(add-grammar-rules '((g2-login-comments 'dummy)))	; to have it shown in table!

(define-slot-alias user-name g2-login-user-name? g2-login)
(define-slot-alias password g2-login-user-password? g2-login)
(define-slot-alias g2-user-mode g2-login-user-mode g2-login)
(define-slot-alias g2-window-name-or-class g2-login-window-name-or-class g2-login)
(define-slot-alias g2-window-specific-language g2-login-specific-language-for-this-g2-window?
  g2-login)
(define-slot-alias g2-window-style g2-login-style-specifically-for-this-workstation?
  g2-login)
(define-slot-alias init-string g2-login-init-string?
  g2-login)


;; Password changing aliases.  The attribute names are the same as
;; used for the prompts in Windows NT 4.0.

(define-slot-alias old-password g2-login-old-password? g2-login)
(define-slot-alias new-password g2-login-first-new-password? g2-login)
(define-slot-alias confirm-new-password g2-login-second-new-password? g2-login)



;;; The slot type `name?' ...

(def-grammar-category name? ()
  (symbol)
  none)

(def-slot-value-writer-as-existing-function name?
    write-symbol-from-slot)

(def-slot-value-compiler name? (parse-result)
  (if (eq parse-result 'none) nil parse-result))


(def-grammar-category g2-login-window-designation ()
  (g2-window-name)					    ; was object-name (MHD 6/7/90)
  (g2-window-class))					    ; was class (MHD 6/7/90)


(def-slot-value-writer-as-existing-function g2-login-window-designation
    write-symbol-from-slot)


(defun twrite-login-failure-translation-symbol (symbol)
  (let ((string (string-for-localized-symbol symbol)))
    (tformat "~a" string)
    ;; Per review by MHD and MWA, period desired
    ;; at end (if appropriate):
    (unless (sentence-end-punctuation? string)
      (twrite-char #.%\.))
    (reclaim-text-string string)))


(define-simple-message g2-login-prompt "Please modify user settings.")
(define-simple-message g2-alias-prompt "Please enter user mode alias.")
(define-simple-message g2-password-change-prompt "Change your password.")

(def-slot-value-writer g2-login-comments (value g2-login)
  (if doing-password-change-p
      (with-localization-domain 'password-change-dialog
	#+development
	(unless (eq (g2-login-how-entered g2-login) 'password-change)
	  (cerror "continue" "The doing-password-change-p flag is up, but ~
                  g2-login-how-entered is ~a" (g2-login-how-entered g2-login)))
	
	(with-localization-purpose 'simple-message
	  (tformat "~a~%" (g2-password-change-prompt-message)))
	(with-localization-purpose 'simple-condition
	  (if value
	      (twrite-login-failure-translation-symbol value))))
    
      (with-localization-domain 'g2-login-dialog
	(with-localization-purpose 'simple-message
      (if (eq (g2-login-how-entered g2-login) 'alias-creation)
        (tformat "~a~%" (g2-alias-prompt-message))
	    (tformat "~a~%" (g2-login-prompt-message))))
	(with-localization-purpose 'simple-condition
	  (if value
	      (twrite-login-failure-translation-symbol value))))))





(define-workstation-context g2-login ()
  :modal t
  :constructor (make-g2-login-state
		 (g2-login
		   g2-login-table
		   g2-login-workspace
		   image-plane-with-g2-login-workspace
		   g2-login-subcommand-menu))
  :state-variables (g2-login
		     g2-login-table
		     g2-login-workspace
		     image-plane-with-g2-login-workspace
		     g2-login-subcommand-menu)
  :keymap ((<standard-enter-keys> enter-keys-in-g2-login-state)
	   ((<mouse-down> attribute-value-represented-by-table-spot)
	    mouse-down-on-attribute-value-in-g2-login-state)
	   ((<mouse-down> subcommand-menu-button-spot)
	    mouse-down-on-subcommand-menu-button-in-g2-login-state)
	   (<mouse-down> mouse-down-on-otherwise-in-g2-login-state)
	   (login-dialog handle-login-dialog-message)))

;; We ought to have a modal and non-modal version.  As it is
;; the modal version explicitly calls a handler provided by top level.



(def-structure-method clean-up-workstation-context (g2-login-state)
  ;; Make sure native dialog is cancelled (eg, if we got here via clear-kb)
  (when (native-login-dialog-p current-workstation-window)
    (cancel-native-login-dialog current-workstation-window))

  ;; Trigger another attempt if things didn't work out.
  (unless (eq 'logged-in (workstation-login-state current-workstation))
    (if (type-of-modal-context? current-workstation)
	(log-out-workstation current-workstation)
	(setf (workstation-login-state current-workstation)
	      'changing-kbs)))
  ;; Clean up any dangling frames.
  (when (valid-block-in-workstation-context-p
	  (g2-login g2-login-state) g2-login-state)
    (delete-frame (g2-login g2-login-state)))
  
  (when (valid-block-in-workstation-context-p
	  (g2-login-workspace g2-login-state) g2-login-state)
    (delete-frame (g2-login-workspace g2-login-state)))
  (funcall-superior-method g2-login-state))




;;; `User-settings-editor-workspace' ...

(def-class (user-settings-editor-workspace temporary-workspace)
  (workspace-margin 10))

	   

;;; `Enter-user-settings-editor' creates a g2-login from the information in the
;;; current workstation and then usually throws up an editor to let the user
;;; proceed to login.

;;; How-entered is a symbol.  If this came from the change-mode menu choice (on
;;; the main menu) or from the control-y or control-e keystrokes, this should be
;;; CHANGING-MODE.  If this came here because the user is logging in from
;;; scratch (possibly after having logged out), then how-entered should be
;;; STARTING.  If this came here because the a new kb has been loaded, the
;;; how-entered should be RELOADING.

;;; It does not throw up the editor if how-entered is either STARTING or
;;; RELOADING and this is not a secure G2.

;;; Another way to look at all of this is:
;;;
;;; In some cases we dont throw up the editor.  We just go ahead an attempt to
;;; log in.  This can fail, in which case we will bring up the editor on the
;;; next time thru service workstations.  We do this when RELOADING.  We also do
;;; it when not secured and we are STARTING.  If login succeeds and the editor
;;; is not entered, a non-nil value is returned; otherwise, the editor is really
;;; entered, and nil is returned.
;;;
;;; It is important to note that when not secured we must be very careful to
;;; assure that the login succeeds.  Generally the information used to do the
;;; login is taken from the workstation (which is the master copy of this info),
;;; we override that only to assure that unsecured login always succeeds.  That
;;; is only necessary when the workstation-login-state is NEVER-USED.  This
;;; state is necessary because the default is given by the KB and when the
;;; workstation was created we didn't necessarily have one.

;;; The `default mode' for a KB is determined to be the value of the
;;; initial-g2-user-mode-for-this-kb slot of the kb-configuration (formerly
;;; kb-restrictions) system table, provided it is non-nil.  When it is nil,
;;; ADMINISTRATOR is used as the ultimate default setting.
;;;
;;; In non-secure systems, we attempt to mimic the old (pre-2.0) behavior
;;; upon reloading of a KB (how-entered = RELOADING).  Namely, we switch
;;; to this default user mode unconditionally in this case.  (This means,
;;; in practice, that we set the user back to whatever the default is in
;;; the KB, if there is one, and otherwise into ADMINISTRATOR mode.)
;;;
;;; However, in a secure system, the approach is to always try to keep the user
;;; in whatever mode they're in before they loaded.  If there is no such mode,
;;; then it falls through again to the "default mode".  Thus, in a secure
;;; system, you stay in whatever mode you were previously in; you never get
;;; the default mode for the KB.

(defun enter-user-settings-editor (how-entered)
  (let* ((g2-login
	   (let ((g2-login (make-frame 'g2-login)))
	     ;; don't allow g2-login frames to be saved in kbs:
	     (set-do-not-save-in-kb g2-login)
	     g2-login))
	 (password-change-case?
	   (eq how-entered 'password-change))
	 (modal-case?
	   (not (memq how-entered '(changing-mode password-change alias-creation)))))
    (setf (g2-login-how-entered g2-login) how-entered)
    (progn
      ;; if either reloading (in a non-secure G2), or using a new workstation
      ;; (with nil as the user name), set up the user mode appropriately per
      ;; the kb-configuration system table:
      (let ((default-mode-for-this-kb
		(or (get-slot-value
		      kb-restrictions
		      'initial-g2-user-mode-for-this-kb)
		    'administrator)))
	
	;; Note that when starting, i.e., a new G2 workstation, the
	;; current-g2-user-mode? will only have a value if -user-mode was
	;; specified on the command line. Otherwise it will be nil because
	;; its based on the default value of the slot
	;; g2-user-mode-for-this-workstation? in workstation, which is nil.
	;; (Intermediate versions had this changed this default to
	;; ADMINISTRATOR, which caused a bug, i.e., that when first
	;; starting, the default mode from a kb loaded from the command
	;; line is not used.)  (MHD 1/12/95)
	(setf (g2-user-mode-for-this-workstation? current-workstation)
	      (or (when (and (eq 'reloading how-entered)
			     (not (g2-secure-p)))
		    default-mode-for-this-kb)
		  current-g2-user-mode?
		  default-mode-for-this-kb))
	#+maybe
	(when  (window-is-in-v5-mode-p
		 (window-for-workstation current-workstation))
	  (send-window-new-mode
	    (window-for-workstation current-workstation)
	    (or (if (and (eq 'reloading how-entered)
			 (not (g2-secure-p)))
		    default-mode-for-this-kb)
		current-g2-user-mode?
		default-mode-for-this-kb))))
      ;; for a new workstation, must initialize g2-window-name-or-class:
      (when (null (g2-window-name-or-class-for-this-workstation current-workstation))
	(setf (g2-window-name-or-class-for-this-workstation current-workstation)
	      'g2-window)))


    (set-session-info-in-g2-login current-workstation g2-login)
    (multiple-value-bind (no-need-to-edit? reason-for-failure)
	(if (not (memq how-entered '(changing-mode password-change alias-creation)))
	    ;; see note below (MHD 11/2/94)
	    (finish-g2-login g2-login current-workstation modal-case?))
    (cond
	(no-need-to-edit?
	 (delete-frame g2-login)
	 t)
	(t
	 (cond
	   ((and (null reason-for-failure) password-change-case?)
	    ;; Out of a usability review (with MWA, 2/13/98) came the suggestion
	    ;; to start off with a hint about the minimum length:  (MHD 2/13/98)
	    (change-slot-value
	      g2-login
	      'g2-login-comments
	      'new-password-must-be-at-least-4-characters-long))
	   (t
	    (setf (g2-login-comments g2-login) reason-for-failure)))

	    ;; See description with this variable. This is temporary for 5.0r3
	    (if doing-password-change-p

	     (with-localization-domain 'password-change-dialog  ; for buttons
	       (with-localization-domain 'password-change  ; for attributes
		 ;; n.b. these wrappers affect the localization in the
		 ;; special workspace (the buttons) and in the table,
		 ;; but not the workstation context as a whole. This
		 ;; is a convient place to site them, but if someone's
		 ;; aethetics are offended they could go lower. ddm 3/12/98

		 (enter-context-in-current-workstation
		   'g2-login
		   (make-user-settings-editor-state
		     g2-login modal-case?
		     password-change-case?)
		   modal-case?)))
	     
	     (with-localization-domain 'g2-login-dialog  ; for buttons	     
	       (with-localization-domain 'g2-login   ; for attributes

		 ;; n.b. these wrappers affect the localization in the
		 ;; special workspace (the buttons) and in the table,
		 ;; but not the workstation context as a whole. This
		 ;; is a convient place to site them, but if someone's
		 ;; aethetics are offended they could go lower. ddm 3/12/98

		 (let ((g2-login-state
			 (make-user-settings-editor-state
			   g2-login modal-case?
			   password-change-case?
			   (eq how-entered 'alias-creation))))
		   (enter-user-settings-editor-1 g2-login-state))))))))))

;; This conditional attempt to login goes away in 4.0 in favor of always
;; attempting.  This change is due to the fact that Telewindows can now send a
;; password along, and this has to be allowed to eliminate the need for a login.
;; This is a nice simplification: we always just let the login attempt take
;; place.  If there's no password, and one is needed, it will just fail and
;; bring up the login panel.  (MHD 11/2/94)
;; 
;;        (if (or (eq how-entered 'reloading)
;;                (and (eq how-entered 'starting)
;;                     (not (g2-secure-p))
;;                     ))
;;            (finish-g2-login g2-login modal-case?))



;;; enter-change-user-mode-in-running' creates a g2-login from the information in the
;;; specified workstation and then usually throws up an editor to let the user
;;; proceed to login.
(defun enter-change-user-mode-in-running (how-entered workstation)
  (let* ((g2-login
	   (let ((g2-login (make-frame 'g2-login)))
	     (set-do-not-save-in-kb g2-login)
	     g2-login)))
    (setf (g2-login-how-entered g2-login) how-entered)
    (progn
      (let ((default-mode-for-this-kb
		(or (get-slot-value
		      kb-restrictions
		      'initial-g2-user-mode-for-this-kb)
		    'administrator)))
	(setf (g2-user-mode-for-this-workstation? workstation)
	      (or (when (and (eq how-entered 'reloading)
			     (not (g2-secure-p)))
		    default-mode-for-this-kb)
		  (g2-user-mode-for-this-workstation? workstation)
		  default-mode-for-this-kb))
	#+maybe
	(when  (window-is-in-v5-mode-p
		 (window-for-workstation workstation))
	  (send-window-new-mode
	    (window-for-workstation workstation)
	    (or (if (and (eq 'reloading how-entered)
			 (not (g2-secure-p)))
		    default-mode-for-this-kb)
		current-g2-user-mode?
		default-mode-for-this-kb))))
      (when (null (g2-window-name-or-class-for-this-workstation workstation))
	(setf (g2-window-name-or-class-for-this-workstation workstation)
	      'g2-window)))

    (set-session-info-in-g2-login workstation g2-login)
    (multiple-value-bind (no-need-to-edit? reason-for-failure)
	(if (not (memq how-entered '(changing-mode password-change alias-creation)))
	    (finish-g2-login g2-login workstation t))
      (declare (ignore reason-for-failure))
      (cond
	(no-need-to-edit?
	 (delete-frame g2-login)
	 t)))))

(defun enter-user-settings-editor-1 (g2-login-state &optional image-plane?)
  (cond ((native-login-dialog-p current-workstation-window)
	 ;; Translated strings are already in the table, but we don't use them
	 ;; for the native dialog, since we want to tweak the translations a bit.
	 (with-localization-purpose 'attribute
	   (post-native-login-dialog g2-login-state)))
	(t
	 (setf (image-plane-with-g2-login-workspace g2-login-state)
	       (or image-plane?
		   (put-workspace-on-pane
		     (g2-login-workspace g2-login-state)
		     current-workstation-detail-pane 'center 'top nil)))))
  (enter-context-in-current-workstation
    'g2-login g2-login-state
    (not (memq (g2-login-how-entered (g2-login g2-login-state))
	       '(changing-mode password-change alias-creation)))))


;;; `Make-user-settings-editor-state' puts up a g2-login workspace with a table
;;; and subcommand menu, puts it up in the current workstation detail pane, and
;;; creates and returns a g2-login-state structure.

(defun make-user-settings-editor-state (g2-login modal-case? password-change-case? &optional (alias-creation? nil))  
  (let* ((g2-login-workspace
	   (make-workspace
	     'user-settings-editor-workspace nil nil 10))
	 (workspace-margin (workspace-margin g2-login-workspace))
	 (g2-login-table
	  (if alias-creation?
	    (progn 
		  (setf (g2-login-user-name? g2-login) nil)
	      (make-alias-creation-attribute-table g2-login))
	    (if password-change-case?
	       (make-password-change-attributes-table g2-login)
	       (make-g2-login-attributes-table g2-login))))
	 (g2-login-subcommand-menu
	   (make-subcommand-menu
	     (slot-value-list
	       'cancel 'disconnect	; these are mutually exclusive
	       'end))))
    (when new-g2-classic-ui-p
      (change-slot-value
	g2-login-workspace 'workspace-background-color?
	(get-ui-parameter 'system-workspace-background-color))
      (change-slot-value
	g2-login-workspace 'title-bar-caption-text
	(convert-text-string-to-text 
	  (if alias-creation?
	    (copy-text-string "User Mode Alias Creation")
	    (copy-text-string "User Settings Editor")))))
    (add-to-workspace
      g2-login-subcommand-menu g2-login-workspace
      (+w (left-edge-of-block g2-login-workspace) workspace-margin)
      (+w (top-edge-of-block g2-login-workspace) workspace-margin))
    (add-to-workspace
      g2-login-table g2-login-workspace
      (+w (right-edge-of-block g2-login-subcommand-menu)
	  workspace-margin)
      (top-edge-of-block g2-login-subcommand-menu))
    ;; Ought to do the approprate thing here? for the
    ;; disconnect/shutdown command!
    (enable-or-disable-subcommand g2-login-subcommand-menu 'end nil)
    (let ((cancel-or-disconnect?
	    (if modal-case?
		(if (eq current-workstation-window system-window)
		    nil
		    'disconnect)
		'cancel)))
      (enable-or-disable-subcommand
	g2-login-subcommand-menu 'cancel
	(not (eq cancel-or-disconnect? 'cancel)))
      (enable-or-disable-subcommand
	g2-login-subcommand-menu 'disconnect
	(not (eq cancel-or-disconnect? 'disconnect))))

    (if password-change-case?
	
	(let ((image-plane-with-g2-login-workspace
		(put-workspace-on-pane
		  g2-login-workspace
		  current-workstation-detail-pane
		  'center 'top nil)))
	  (make-g2-login-state
	    g2-login
	    g2-login-table
	    g2-login-workspace
	    image-plane-with-g2-login-workspace
	    g2-login-subcommand-menu))
	
	(make-g2-login-state
	  g2-login
	  g2-login-table
	  g2-login-workspace
	  
	  ;; Here, we put the the image plane into the slot when we put up
	  ;; the workspace, elsewhere. (MHD 7/28/03; updated by JPG 7/27/04)
	  nil
	  
	  g2-login-subcommand-menu))))


(register-button-label-for-internationalization 'cancel)
(register-button-label-for-internationalization 'disconnect)
(register-button-label-for-internationalization 'end)

;; Would be nice if there was a better, consistent location for this
;; sort of information, but where?

  


;;; `Make-g2-login-attributes-table' makes an attribute table for display and
;;; editing in the g2-login dialog.  The attributes it displays are taken from
;;; the list stored in the variable `g2-login-attributes-to-show'.

(defparameter g2-login-attributes-to-show
  '(g2-login-comments 
    g2-login-user-name?
    g2-login-user-password?
    g2-login-window-name-or-class
    g2-login-user-mode
    g2-login-specific-language-for-this-g2-window?

    ;; We are pulling g2-login-style-specifically-for-this-workstation? before
    ;; final Beta release of 6.0.  It clutters the login screen without much
    ;; value.  Users who want to change it at runtime can do so through the
    ;; g2-window, which is easier to access in 6.0 (off the system-tables menu).
    ;; If desired, it could be put back; it works.  (MHD 3/29/01)
    ;; g2-login-style-specifically-for-this-workstation?

    ))

(defun make-g2-login-attributes-table (g2-login)
  (make-attributes-table
    g2-login nil nil nil nil
    g2-login-attributes-to-show))

	
(defparameter alias-creation-attributes-to-show
  '(g2-login-comments 
    g2-login-user-name?
    g2-login-user-mode))
	
(defun make-alias-creation-attribute-table (g2-login)
  (make-attributes-table
    g2-login nil nil nil nil
    alias-creation-attributes-to-show))
;;; `Make-password-change-attributes-table' makes an attribute table
;;; representing a g2-login frame, for display and editing in the
;;; password-change dialog.  The attributes it displays are taken from the list
;;; stored in the variable `password-change-attributes-to-show'.

(defparameter password-change-attributes-to-show
  '(g2-login-comments 
    g2-login-user-name?
    g2-login-old-password?
    g2-login-first-new-password?
    g2-login-second-new-password?))

(defun make-password-change-attributes-table (g2-login)
  (make-attributes-table
    g2-login nil nil nil nil
    password-change-attributes-to-show))



;;; The `valid-workstation-context-p method for g2-login-state' ...

(def-structure-method valid-workstation-context-p (g2-login-state)
  (and (funcall-superior-method g2-login-state)
       (valid-block-in-workstation-context-p
	 (g2-login g2-login-state) g2-login-state)
       (valid-block-in-workstation-context-p
	 (g2-login-table g2-login-state) g2-login-state)
       (valid-block-in-workstation-context-p
	 (g2-login-workspace g2-login-state) g2-login-state)))


(define-event-handler enter-keys-in-g2-login-state ()
  (do-end-button-for-g2-login))

(define-event-handler mouse-down-on-attribute-value-in-g2-login-state
    (mouse-pointer
      image-plane
      (g2-login-state workstation-context-specifics)
      (text-cell text-cell-of-table))
  (cond
    ;; Is this our table?
    ((eq image-plane
	 (image-plane-with-g2-login-workspace g2-login-state))
     (multiple-value-bind (g2-login? slot-name?)
	 (get-slot-represented-by-text-cell-if-any text-cell)
       (when slot-name?			; t => g2-login? is non-null
	 (unless (or (eq slot-name? 'g2-login-comments)
		     ;; Note: we do not allow the user name to be edited for the
		     ;; password change case.  Users may only edit their own
		     ;; passwords.  It is a programmer error if we're here doing
		     ;; a password change, but there's no user name.  (We try to
		     ;; fail soft in such a case.)
		     (and (eq (g2-login-how-entered g2-login?)
			      'password-change)
			  (eq slot-name? 'g2-login-user-name?)))
	   (let* ((type-of-slot? (type-of-slot-if-editable (class g2-login?) slot-name?))
		  (user-password-editing-case?
		    (and type-of-slot?
			 (eq (category-symbol-given-slot-type type-of-slot?)
			     'user-password)))
		  (specific-format?
		    (if user-password-editing-case? 
			(create-blob-edit-box-format))))
	     (enter-editing-context
	       g2-login? slot-name?
	       (if user-password-editing-case?
		   (make-empty-text))	; make empty text in this case, 
					;   don't edit *'s from the writer
	       nil specific-format?))))))
    (t
     (mouse-down-on-otherwise-in-g2-login-state mouse-pointer))))


(define-event-handler mouse-down-on-subcommand-menu-button-in-g2-login-state
    ((g2-login-state workstation-context-specifics)
     image-plane
     mouse-pointer)
  (cond
    ;; If this is our subcommand menu...
    ((eq image-plane
	 (image-plane-with-g2-login-workspace g2-login-state))
     (with-workstation-context-continuation (do-g2-login-subcommand)
       (enter-subcommand-context mouse-pointer)))
    
    ;; Otherwise fall into the general handler, if we ain't modal.
    (t
     (mouse-down-on-otherwise-in-g2-login-state mouse-pointer))))


;;; `Mouse-down-on-otherwise-in-g2-login-state' this falls thru
;;; to top level state.

(define-event-handler mouse-down-on-otherwise-in-g2-login-state
    (mouse-pointer)
  (unless (type-of-modal-context? current-workstation)
    (run-top-level-event-handler mouse-pointer)))



;;; `Do-g2-login-subcommand' is a continuation from subcommand-state
;;; into g2-login-state, after a button is selected in the g2-login panel's
;;; subcommand menu.

(defun do-g2-login-subcommand (workstation-context)
  (declare (ignore workstation-context))
  (with-workstation-context-return-values (subcommand-menu-or-error-code button-info)
    (unless (eq :abort subcommand-menu-or-error-code)
      (do-g2-login-button button-info))))

(defun do-g2-login-button (button)
  (case button
    (end
     (do-end-button-for-g2-login))
    (cancel
     (abort-current-workstation-context 'g2-login))
    (disconnect
     (abort-current-workstation-context 'g2-login)
     (close-telewindows-connection current-workstation-window))))



;;; `Do-end-button-for-g2-login' 
;;;
;;; This uses too-many-login-attempts-p to determine when too many attempts have
;;; been made (only relevant to secure G2s).  If so, and if
;;;
;;;    (1) this is a proper Telewindows window (not the local, "console"); and
;;;    (2) this is a modal context
;;;
;;; then the workstation context is aborted and the connection is shutdown,
;;; which ends up deleting the window.
;;;
;;; (Note that we would ultimately like to shut down any G2 window, not just
;;; proper telewindows, under these circumstances, but we're deferring that work
;;; for now; users may either think of this as a bug, or as a "console" feature
;;; of the local window, i.e., that it has the privalege of not being shut down
;;; in this way.)


(defun do-end-button-for-g2-login ()
  (let* ((g2-login-state specific-structure-for-current-workstation-context)
	 (g2-login (g2-login g2-login-state))
	 (how-entered (g2-login-how-entered g2-login))
	 (frame-reference (current-frame-serial-number)))

    (when (not (is-user-mode-present (g2-login-user-mode g2-login)))
      (notify-user "~a" "Can not choose user mode to non-existend user mode")
      (return-from do-end-button-for-g2-login (values nil nil)))

    (multiple-value-bind (success? reason-for-failure)
	(cond
	  ((eq how-entered 'password-change)
	   (if (null (g2-login-second-new-password? g2-login))
	       (values nil 'duplicate-new-password-required)
	       (encode-and-check-password-change-information
		 (g2-login-user-name? g2-login)
		 (g2-login-old-password? g2-login)
		 (g2-login-first-new-password? g2-login)
		 (g2-login-second-new-password? g2-login))))
	  ((eq how-entered 'alias-creation)
	    (if (is-user-mode-present (g2-login-user-mode g2-login))
	      (when (check-alias-for-possible-name (g2-login-user-name? g2-login))
		    (make-new-alias g2-login))
		  (notify-user "Sorry, but parent user mode for this alias is incorrect.")))
	  (t
	   (finish-g2-login
	     g2-login
	     current-workstation
	     (eq (type-of-modal-context? current-workstation) 'g2-login))))
      (cond
	((frame-has-been-reprocessed-p g2-login frame-reference)
	 ;; in very rare cases, finish-g2-login could have disconnected us, and
	 ;; we're history in this case.  Just get out as fast as possible, i.e.,
	 ;; doing the throw implied by (abort). (MHD 6/4/99)
	 (abort)
	 nil)
	(success?
	 (return-from-current-workstation-context 'g2-login))
	(t	
	 (change-slot-value
	   g2-login 'g2-login-comments reason-for-failure)
	 (enable-or-disable-subcommand		; to unhighlight
	   (g2-login-subcommand-menu g2-login-state)
	   'end nil)

	 (when (and (too-many-login-attempts-from-this-source g2-login)
		    (type-of-modal-context? current-workstation)
		    ;; this for Telewindows-proper windows only! (sad)
		    ;; maybe redundant
		    (and (not (eq current-workstation-window system-window)) 
			 (eq (type-of-gensym-window current-workstation-window) 'icp)))
	   (notice-tw-disconnect current-workstation
				 (g2-login-user-name? g2-login)
				 (g2-login-user-mode  g2-login))
	   (abort-current-workstation-context 'g2-login) ; same as disconnect
	   (close-telewindows-connection current-workstation-window)))))))





;;; `Too-many-login-attempts-from-this-source' returns true if too many attempts
;;; to login have failed.  The threshhold is given by the parameter
;;; `maximum-number-of-login-attempts-permitted-per-window', which has been made
;;; to default to 5 because that is what Unix seems to do.
;;; 
;;; This is intended as a security feature in that it makes it harder for users
;;; to try every name and password they've ever heard of.  If they make an
;;; honest mistake, they can hopefully just reconnect and try again another 5
;;; times.  This is patterned loosely on the behavior of unix login prompts, and
;;; something like this was strongly suggested/demanded by security consultants
;;; who evaluated overall security aspects of G2 (around autumn, 1994).

(defparameter maximum-number-of-login-attempts-permitted-per-window 5)

;; 5? Same as Sun/Sparc Unix. (MHD 11/29/94)


(defun too-many-login-attempts-from-this-source (source)
  (macrolet ((bump-counter (source)
	       `(cond ((and (framep ,source)
			    (frame-of-class-p ,source 'g2-login))
		       (incff (g2-login-attempts-counter ,source)))
		      ((t2-nonce-data-p ,source)
		       (incff (t2-nonce-login-attempts-count ,source)))
		      (t #+development
			 (cerror "continue -- the login will fail"
				 "The source ~a is not coded for by ~
                                 the login-attempts counter. This is a security
                                 problem !" ,source)
			 (1+f maximum-number-of-login-attempts-permitted-per-window)))))
    (when (g2-secure-p)
      (let ((number-of-attempts (bump-counter source)))
	(>=f number-of-attempts
	     maximum-number-of-login-attempts-permitted-per-window)))))



(defun-for-system-procedure g2-set-maximum-login-attempts
    ((number integer))
  (declare (keeps-g2-local-variables-valid t)
	   (values integer))
  (let ((prior-value maximum-number-of-login-attempts-permitted-per-window))
    (setq maximum-number-of-login-attempts-permitted-per-window number)
    (make-evaluation-integer prior-value)))




;;; `Finish-g2-login' validates a g2-login.  If it is successful, a workstation
;;; is allowed to be partnered with a g2-window, one that exists, or one to be
;;; created, as to be determined when that eventual pairing takes place.
;;;
;;; If the g2-login is invalid, this returns nil as its first arg, and a second
;;; arg giving the reason for the failure as a symbol.
;;;
;;; This is essentially an interface to log-in-workstation, q.v., for further
;;; details.

;;; Special handling is done unless the workstation has true in the
;;; g2-user-discard-user-settings-for-this-workstation-p slot: we transmit the
;;; user name, password, user mode, and language back to Telewindows, which is
;;; done by the function offer-g2-login-user-password-back-to-telewindows.

(defun finish-g2-login (g2-login workstation modal-case?)
  (setf (g2-login-encoded-password? g2-login)
	(encode-password-via-md5
	  (g2-login-user-name? g2-login)
	  (g2-login-user-password? g2-login)
	  (g2-login-encoded-password? g2-login)))
  (unless (g2-user-discard-user-settings-for-this-workstation-p
	    workstation)
    (let ((user-settings-plist
	    (nconc
	      (if (g2-login-user-name? g2-login)
		  (gensym-list
		    'user-name
		    (stringw (g2-login-user-name? g2-login))))
	      (if (g2-login-encoded-password? g2-login)
		  (gensym-list
		    'md5-password
		    (stringw (g2-login-encoded-password? g2-login))))
	      (if (g2-login-user-mode g2-login)
		  (gensym-list
		    'user-mode
		    (stringw (g2-login-user-mode g2-login))))
	      (if (g2-login-specific-language-for-this-g2-window? g2-login)
		  (gensym-list
		    'language
		    (stringw
		      (g2-login-specific-language-for-this-g2-window?
			g2-login))))
	      (if (g2-login-style-specifically-for-this-workstation? g2-login)
		  (gensym-list
		    'window-style
		    (stringw
		      (g2-login-style-specifically-for-this-workstation?
			g2-login)))))))
      (offer-g2-user-settings-back-to-telewindows
	workstation user-settings-plist)
      (reclaim-gensym-list user-settings-plist)))
  (log-in-workstation
    workstation
    (g2-login-user-name? g2-login)
    (g2-login-encoded-password? g2-login)
    (g2-login-user-mode g2-login)
    (g2-login-window-name-or-class g2-login)
    modal-case?
    (g2-login-specific-language-for-this-g2-window? g2-login)
    (g2-login-style-specifically-for-this-workstation? g2-login)))

;; Note: stringw doesn't cons for a symbol argument, which we have here.






;;;; Changing Passwords Programmatically

(defun encode-and-check-password-change-information
       (user-name clear-old-password clear-new-password-1
        &optional clear-new-password-2?)
  
  (let ((encoded-old-password (encode-password-via-md5
				user-name clear-old-password nil))
	(encoded-new-password-1 (encode-password-via-md5
				 user-name clear-new-password-1 nil))
	(encoded-new-password-2?
	  (when clear-new-password-2?
	    (encode-password-via-md5 user-name clear-new-password-2? nil))))

    ;; Consider whether to do the user-settings-to-telewindows logic here?!
    
    (when (symbolp clear-old-password)
      (setq clear-old-password (symbol-namew clear-old-password)))

    (when (symbolp clear-new-password-1) ; see note
      (setq clear-new-password-1 (symbol-namew clear-new-password-1)))

    (let ((result (change-user-password-if-appropriate
		    user-name encoded-old-password clear-old-password clear-new-password-1
		    encoded-new-password-1 encoded-new-password-2?)))
      (values (null result) result))))

;; Note: When this function is called from do-end-button-for-g2-login
;; (the overloaded login-dialog) the passwords are symbols. When it is
;; called from the programmatic entry point, set-user-password, they
;; are strings (as, eventually, they will be all the time). The next
;; routine in the chain wants a string to work with. MD5 takes either
;; strings or symbols and downcases the symbol before encoding it.
;; If the conversion to a string that is done here were made before
;; the md5 encodings, we would get different results and the two
;; copies of the new password would be perceived as different.
;; ddm 7/29/98




;;; `Minimum-g2-password-length' is defined as 4.  This corresponds to the
;;; policy enforced in the g2passwd executable shipped with G2.  [Note that 6
;;; might be a better choice.  That is the minimum as on good commercial
;;; versions of Unix (e.g., SunOS) for passwords without mixed lettercase.]

;;; `Maximum-g2-password-length' is defined as 499.  This maximimum length is
;;; not very serious, but it is the effective max in the g2passwd C program.

(defconstant minimum-g2-password-length 4)
(defconstant maximum-g2-password-length 499)


;;; `Valid-password-characters-p' tests that password string consists only of
;;; [a-z], [A-Z], and 0-9.  Note that this is what the g2passwd executable
;;; requires.  Note that in general tokens in a g2.ok file must be valid ASCII
;;; printing characters, including space, but excluding \, @, and ~.

(defun valid-password-characters-p (password-string)
  (loop for i from 0 below (wide-string-length password-string)
	as character = (charw password-string i)
;	as character-code = (char-codew character)
	always
	;; test for alphanumeric:
	(alphanumericpw character)
	;; test for what's legal in a g2.ok file token:
;	(and (simple-character-code-p character-code)
;	     (not (member character-code (escape-character-codes))))
	))

;; Note that the restriction on \, @, and ~ is questionable, but it's there in
;; the G2 OK file reader.  Note that the g2passwd program does not test for
;; these illegal characters.  Nor does it impose any minimum length.  Note that
;; we do not have a maximum significant length.  Compare this to (SunOS) unix,
;; which counts only the first 8 characters of a password as significant.  The
;; maximimum length is not very serious, but it is the max in the C program
;; (leaving one byte open for the null terminator), so we'll duly check it and
;; prevent this from being an unlikely source of problems.  (MHD 2/12/98)




;;; `Change-user-password-if-appropriate' ... returns reason-we-failed?,
;;; nil if unsuccessful, otherwise, a symbol explaining the failure (very
;;; briefly).  Note that any symbol this can return (except nil) has been
;;; registered via define-type-of-login-failure for
;;; internationalization/localization purposes

(defun-allowing-unwind change-user-password-if-appropriate
    (user-name-symbol encoded-old-password clear-old-password clear-new-password
		      encoded-new-password-1 encoded-new-password-2?)
  (protected-let*
      ((user-name-string
	 (copy-symbol-name	  ; downcase -- workaround/kludge -- downstream
	   user-name-symbol nil)  ;   compare should not consider case! (MHD)
	 (reclaim-text-string user-name-string))
       (authorization-entry? (assq user-name-symbol authorized-users-list))
       (ok-pathname? nil (reclaim-gensym-pathname ok-pathname?))
       (namestring? nil (reclaim-text-string namestring?))
       (setting-initial-password? (text-string-equal+ clear-old-password #w""))
       (error-symbol-for-incorrect-old-password?
	 (if setting-initial-password?
	     (cond ((null authorization-entry?)
		    'unknown-user)
		   ((not (string-equalw
			   #w"" (user-entry-encoded-password authorization-entry?)))
		    'initializing-the-password-of-user-with-existing-password))
	     (cond
	       ((null encoded-old-password)
		'password-required)
	       ((or (null authorization-entry?)
		    (not (text-string= encoded-old-password
				       (second authorization-entry?))))
		;; Note that if a user is using this on a "grandfathered" basis,
		;; i.e., he is no longer an authorized user, but was when he logged
		;; in, then he gets this message, which may seem a bit strange.
		;; Unlikely in any event.  Should this message be tailored for that
		;; odd situation? (MHD 2/12/98)
		'unknown-user-or-bad-password)))))

    (or error-symbol-for-incorrect-old-password?
	;; The user is validated -- knows his (old) password, so now check for
	;; missing new password information or a mismatch between 1st & 2nd.
	(cond
	  ((null encoded-new-password-1)
	   'new-password-required)
	  ((and encoded-new-password-2?
		(not (text-string= encoded-new-password-1 encoded-new-password-2?)))
	   'new-password-does-not-match-its-duplicate)
	  ((<f (text-string-length clear-new-password)
	       minimum-g2-password-length)
	   'new-password-must-be-at-least-4-characters-long)
	  ((>f (text-string-length clear-new-password)
	       maximum-g2-password-length)
	   'new-password-too-long)
	  ((not (valid-password-characters-p clear-new-password))
	   'new-password-has-invalid-characters)
	  ((null (if (setq ok-pathname?
			   ;; We don't need write access -- only g2passwd.exe does;
			   ;; we just read access here.  (See below for "obsolete
			   ;; approach".) (MHD 2/23/97)
			   #+obsolete (g2-ok-file-probe-for-write)
			   #-obsolete (g2-ok-file-probe))
		     (setq namestring? (gensym-namestring ok-pathname?))))
	   #+obsolete 'cannot-write-to-g2-ok-file
	   #-obsolete 'cannot-find-g2-ok-file)
	  ;; OK, we like the new password
	  ((save-new-user-password-in-g2-ok-file ; returns nil or a problem symbol
	     namestring?
	     user-name-string
	     (if setting-initial-password?
		 ""  ; see note 1
		 encoded-old-password)
	     encoded-new-password-1))
	  (t
	   ;; Success!  Now, synch up the user model and we're done.
	   (setf (user-entry-encoded-password authorization-entry?)
		 (copy-text-string encoded-new-password-1))
;       (setf (g2-user-password-for-this-workstation? current-workstation)
;	     (copy-text-string encoded-new-password-1))
;       See note 2.
	   nil)))))

;; Note 1: This empty-string case corresponds to calling the password
;; routine with only 3 arguments instead of 4. The empty string disappears
;; in the command line.

;; Note 2: Removed the update to current workstation when this code came to
;; also be used for programmatic password-changing as well as menu-driven.
;; When coming in via a system procedure there is no way to access the
;; current workstation, and furthermore the original (5.0r3) treatment was
;; unable to appreciate the possiblity of multiple connections from the
;; same person. I checked the uses of this field and its value is presently
;; accessed in only one place, the ui-command change-password. There it is
;; used just as a gate, so it does not matter whether its value is up to date.
;; ddm 7/29/98


;; Obsolete approach. The approach of doing the rewriting of the password file
;; was abandoned due to concerns over security, and also not fitting in with the
;; theory of operation.  In particular, the administrator needs to give write
;; permission to one and only one simple, trusted program, namely the g2passwd
;; file, and we must therefore implement the change by executing that particular
;; file.  (MHD 2/23/98)
;;
;; ;;; The `C function c-g2pw_change_pwd' changes the specified password file, and
;; ;;; returns either 0, indicating success, or a positive integer, indicating
;; ;;; failure.  As a side effect, if this encounters a problem, an English error
;; ;;; message is printed to standard output.  The corresponding C function,
;; ;;; g2pw_change_pwd, is in g2pwaux.c.  All args should be strings, either wide
;; ;;; strings or gensym strings.
;; 
;; (def-gensym-c-function c-g2pw_change_pwd
;;     (:fixnum-int "g2pw_change_pwd")
;;   ((:string file-name)
;;    (:string user-name)
;;    (:string old-password-hashed)
;;    (:string new-password-hashed)))
;; 
;; 
;; 
;; ;;; The function `save-new-user-password-in-current-g2-ok-file' ... File-name
;; ;;; and the other arguments should all be strings, either wide strings or gensym
;; ;;; strings.  This function does not mutate or recycle the supplied strings.
;; ;;; The password args call for the "hashed" (encoded) versions of passwords, not
;; ;;; those in clear text.
;; 
;; (defun save-new-user-password-in-g2-ok-file
;;     (file-name user-name old-password-hashed new-password-hashed)
;;   (let ((result
;; 	  (c-g2pw_change_pwd
;; 	    file-name  user-name
;; 	    old-password-hashed  new-password-hashed)))
;;     (if (=f result 0)
;; 	nil
;; 	'problem-saving-password-in-g2-ok-file)))



;;; The function `save-new-user-password-in-current-g2-ok-file'
;;; ... File-name and the other arguments should all be strings, either
;;; wide strings or gensym strings.  This function does not mutate or
;;; recycle the supplied strings.  The password args call for the "hashed"
;;; (encoded) versions of passwords, not those in clear text.

;;; Note: the policy is to not offer password changing to the user unless
;;; g2passwdexe-is-executable-p, determined at startup, is true.  This
;;; policy is enforced in the defcommand for the change-password command.

(defun-allowing-unwind save-new-user-password-in-g2-ok-file
    (file-name user-name old-password-hashed new-password-hashed)
  (protected-let*
      ((g2passwdexe-file-name g2passwdexe)
       (command-line
	 (tformat-text-string
	   ;; Double-quotes are needed because file-name might contain
	   ;; a space. - jpg 8/9/04
	   "~a \"~a\" ~a ~a ~a"
	   g2passwdexe-file-name
	   file-name
	   user-name
	   old-password-hashed
	   new-password-hashed)
	 (reclaim-text-string command-line))
       (message-text-string
	 (twith-output-to-text-string
	   (twrite-standard-secure-g2-notification-header)
	   (tformat
	     (saving-new-password-format-control-string)
	     user-name
	     g2passwdexe-file-name
	     file-name)) ;/// check notify-user... for double reclaimation
	 (reclaim-text-string message-text-string)))

    (pass-command-to-g2passwd command-line message-text-string)))


(defun pass-command-to-g2passwd (command-line message-text-string)
  (or (and (not (g2passwd-probe-file))
	   'g2passwd-executable-cannot-be-found)
      (with-temporary-gensym-float-creation modify-ok-file
	(let ((result-gensym-float (c-spawn_executable_process command-line)))
	  (cond
	    ((=e result-gensym-float -1.0)
	     ;; Note: when the file cannot be found, we do not get an indication
	     ;; of this (-1.0 returned).  This may seem wrong, but MES says this
	     ;; is not necessarily incorrect behavior. (MHD 2/26/98)
	     'problem-saving-password-in-g2-ok-file) ;/// sharpen message!
	    (t 
	     (notify-user-at-console-and-on-logbook "~%~a." message-text-string)
	 nil)))))) ; nil means the operation was successful. See caller's caller

;; Internationalize this, e.g. on the model of OK error messages.

(defun-simple saving-new-password-format-control-string ()
  "Changing password for user ~s, running ~s outside of G2 on the G2 OK file ~s" )






;;;; Adding New Users to the OK file

;;; Called by the g2-add-user system procedure.

(defun-allowing-unwind add-new-user-encoding-as-needed
       (user-name clear-password list-of-modes universal-date)
  (protected-let*
      ((error-symbol? nil)
       (write-symbols-in-lower-case? t)
       (user-name-as-string
	 (twith-output-to-text-string (twrite user-name))
	 (reclaim-text-string user-name-as-string))
       (encoded-password
	 ;; This string is incorporated into the user-entry in
	 ;; authorized-users-list. 
	 (encode-password-via-md5 user-name clear-password nil))
       (mode-string
	 (twith-output-to-text-string
	   (twrite #w"\"(")
	   (loop for (mode . rest) on list-of-modes
		 do
	     (twrite mode)
	     (when rest (twrite #w" ")))
	   (twrite #w")\""))
	 (reclaim-text-string mode-string))
       (decay-date
	 (twith-output-to-text-string (twrite universal-date))
	 (reclaim-text-string decay-date))
       (operation-name-for-add
	 (copy-wide-string #w"add")
	 (reclaim-text-string operation-name-for-add))
       (ok-file-namestring?
	 (when (g2-ok-file-probe)
	   (gensym-namestring authorizing-OK-pathname))
	 (reclaim-if-text-string ok-file-namestring?)))

    (unless ok-file-namestring?
      (setq error-symbol? 'OK-file-not-found))

    (when (invalid-user-name-p user-name-as-string)
      (setq error-symbol? 'Invalid-user-name))

    (unless error-symbol?
      (protected-let*
	  ((g2passwdexe-file-name g2passwdexe)
	   (command-line
	     (tformat-text-string
	       ;; Double-quotes are needed because file-name might contain
	       ;; a space. - jpg 8/9/04
	       "~a \"~a\" ~a ~a ~a ~a ~a"
	       g2passwdexe-file-name
	       ok-file-namestring?
	       operation-name-for-add
	       user-name-as-string
	       encoded-password
	       mode-string
	       decay-date)
	     (reclaim-text-string command-line))
	   (message-text-string
	     (twith-output-to-text-string
	       (twrite-standard-secure-g2-notification-header)
	       (tformat
		 "Updated ~a: added a user entry for ~a"
		 ok-file-namestring? user-name-as-string))
	     (reclaim-text-string message-text-string)))

	(setq error-symbol?
	      (pass-command-to-g2passwd command-line message-text-string))))

    (unless error-symbol?
      (enter-authorized-user
	user-name encoded-password list-of-modes universal-date t))

    error-symbol?))


;;; Called by the g2-delete-user system procedure.

(defun-allowing-unwind delete-user (user-name)
  (protected-let*
      ((error-symbol? nil)
       (write-symbols-in-lower-case? t)
       (user-name-as-string
	 (twith-output-to-text-string (twrite user-name))
	 (reclaim-text-string user-name-as-string))
       (operation-name-for-delete
	 (copy-wide-string #w"delete")
	 (reclaim-text-string operation-name-for-delete))
       (ok-file-namestring?
	 (when (g2-ok-file-probe)
	   (gensym-namestring authorizing-OK-pathname))
	 (reclaim-if-text-string ok-file-namestring?))
       (tmp-file-namestring
	 (let ((copy (copy-gensym-pathname authorizing-OK-pathname)))
	   (setf (gensym-pathname-name copy) (copy-wide-string #w"TMP"))
	   (prog1 (gensym-namestring copy)
	      (reclaim-gensym-pathname copy)))
	 (reclaim-text-string tmp-file-namestring)))

    (unless ok-file-namestring?
      (setq error-symbol? 'OK-file-not-found))
    (unless error-symbol?
      (unless (gensym-probe-file-for-write tmp-file-namestring)
	(setq error-symbol? 'can-not-write-tmp-file)))

    (unless error-symbol?
      (protected-let*
	  ((g2passwdexe-file-name g2passwdexe)
	   (command-line
	     (tformat-text-string
	       ;; Double-quotes are needed because file-name might contain
	       ;; a space. - jpg 8/9/04
	       "~a \"~a\" ~a ~a \"~a\" ~a ~a"
	       g2passwdexe-file-name
	       ok-file-namestring?
	       operation-name-for-delete
	       user-name-as-string
	       tmp-file-namestring
	       "x" "x") ;; dummies fillers for the next two fields
	     (reclaim-text-string command-line))
	   (message-text-string
	     (twith-output-to-text-string
	       (twrite-standard-secure-g2-notification-header)
	       (tformat
		 "Updated ~a: deleted the user entry for ~a"
		 ok-file-namestring? user-name-as-string))
	     (reclaim-text-string message-text-string)))

	(setq error-symbol?
	      (pass-command-to-g2passwd command-line message-text-string))))

    (unless error-symbol?
      (remove-authorized-user user-name))

    error-symbol?))


;;; Called by the g2-change-password-expiration-date system procedure.

(defun-allowing-unwind change-users-password-decay-date (user-name universal-date)
  (protected-let
      ((error-symbol? nil)
       (write-symbols-in-lower-case? t)
       (user-name-as-string
	 (twith-output-to-text-string (twrite user-name))
	 (reclaim-text-string user-name-as-string))
       (decay-date
	 (twith-output-to-text-string (twrite universal-date))
	 (reclaim-text-string decay-date))
       (operation-name
	 (copy-wide-string #w"modify-decay-date")
	 (reclaim-text-string operation-name))
       (ok-file-namestring?
	 (when (g2-ok-file-probe)
	   (gensym-namestring authorizing-OK-pathname))
	 (reclaim-if-text-string ok-file-namestring?))
       (dummy-encoded-password
	 (copy-wide-string #w"dummy-encoded-password")
	 (reclaim-text-string dummy-encoded-password))
       (dummy-mode-list
	 (copy-wide-string #w"dummy-mode-list")
	 (reclaim-text-string dummy-mode-list)))
 
    (unless ok-file-namestring?
      (setq error-symbol? 'OK-file-not-found))

    (unless error-symbol?
      (protected-let*
	  ((g2passwdexe-file-name g2passwdexe)
	   (command-line
	     (tformat-text-string
	       ;; Double-quotes are needed because file-name might contain
	       ;; a space. - jpg 8/9/04
	       "~a \"~a\" ~a ~a ~a ~a ~a"
	       g2passwdexe-file-name
	       ok-file-namestring?
	       operation-name
	       user-name-as-string
	       dummy-encoded-password
	       dummy-mode-list
	       decay-date)
	     (reclaim-text-string command-line))
	   (message-text-string
	     (twith-output-to-text-string
	       (twrite-standard-secure-g2-notification-header)
	       (tformat
		 "Updated ~a: modified the password-validity entry ~
                  for ~a"
		 ok-file-namestring? user-name-as-string))
	     (reclaim-text-string message-text-string)))

	(setq error-symbol?
	      (pass-command-to-g2passwd command-line message-text-string))))

    (unless error-symbol?
      (set-validity-of-user-password user-name universal-date))

    error-symbol?))


 


;;;; Stuff for Keeping Passwords Secret:

(defun create-blob-edit-box-format ()
;  (if (null (ab-font 'blob18))   ; now a standard font in Gensym software (3/20/90)
;      (create-blob18-font))
  (get-or-make-format-frame 'blob-edit-box-format))


(def-text-box-format blob-edit-box-format
  text-cell-font-map (Blob18)			; characters all have width 8
						;   and are all missing  
  ;; everything else was copied from
  ;;   edit-box-format as of 2/23/90:
  text-cell-line-height 20			; experiment with these!
  text-cell-baseline-position 15
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 26	; 4 default spaces
  text-cell-lines-justified? nil
  text-cell-line-color? black
  text-box-border-color? black)



(def-text-box-format invisible-text-format
  text-cell-line-color? gray
  text-cell-background-color? gray)

;; Make sure that this causes G2 not to draw the text at all, so that it cannot
;; be seen at all (subliminally in the blink of an eye, or worse), esp. on a
;; slow machines.

;; Note that at present, while editing the password, you can still
;; cut and paste; therefore, one could cut a typed in password and then see
;; it later by pasting it or looking at the scrap book.  This isn't that
;; bad -- the requirement is that he can enter a password by typing it
;; in and not have to worry about people seeing it by looking over his
;; shoulder at his screen, which the above limitation hardly gets in the
;; way of.  At present, it would would be an ugly little project to turn
;; off cut and paste in certain cases (or in only this case).  The question
;; is: could someone would actually (a) innocently use Cut or Copy on a
;; password and (b) be surprised that this could reveal his password to
;; others later, thus leaving G2 open to accusations of having a security
;; leak?  (MHD 2/23/90)





;;;; Refreshing Authorized Users and Passwords (from the G2.OK File)

;;; The process of reloading the OK file and updating the information on the
;;; users can be initiated either from a menu (see `reinstall-authorized-users
;;; ui-command) or via the system procedure g2-reinstall-authorized-users.
;;; Both routines call read-ok-file-just-for-updating-user-data to actually
;;; get the work done. 

(defun reinstall-authorized-users ()
  (let ((pathname? (g2-ok-file-probe)))
    (when pathname?
      (let ((namestring (gensym-namestring pathname?)))
	(confirm-or-cancel
	  (tformat-text-string
	    "Reinstall authorized users?~
             ~%~%This action reads in the ~
             G2 ok file (~s) and installs that file's set ~
             of authorized users, passwords, and user modes.~
             ~%~%This does not affect ~
             logged-in users until they log off or change their G2 user mode."
	    namestring)
	  'read-ok-file-again
	  nil)
	(reclaim-text-string namestring)
	(reclaim-gensym-pathname pathname?)))))



(defun-for-system-procedure g2-reinstall-authorized-users ()
  (declare (values text)
	   (keeps-g2-local-variables-valid t))
  (let ((fresh-error-string? (read-ok-file-again)))
    (or fresh-error-string?
	(copy-text-string #w"ok"))))



(defun-allowing-unwind read-ok-file-again ()
  (protected-let*
      ((pathname? (g2-ok-file-probe) (reclaim-gensym-pathname pathname?))
       (namestring
	 (if pathname? (gensym-namestring pathname?))
	 (reclaim-text-string namestring))
       (completion-message nil (reclaim-text-string completion-message)))
    (when pathname?		    ; very unlikely to be nil
      (let* ((message-text-string   ; gets absorbed by macro it's passed into
	       (twith-output-to-text-string
		 (twrite-standard-secure-g2-notification-header)
		 (tformat "Reinstalling authorized users from ~s." namestring))))
	(notify-user-at-console-and-on-logbook "~%~a" message-text-string)	
	(let ((error? nil))
	  (do-long-operation-with-notification (message-text-string nil)
	    ;; note that message-text-string is now swallowed by do-long-...
	    (setq error? (read-ok-file-just-for-updating-user-data namestring)))
	  (setq completion-message
		(twith-output-to-text-string
		  (twrite-standard-secure-g2-notification-header)
		  (tformat "Reinstallation of authorized users completed ")
		  (cond (error? (tformat "unsuccessfully! ERROR: ~a" error?))
			(t (tformat "successfully.")))))
	  (notify-user-at-console-and-on-logbook "~%~a" completion-message)
	  error? )))))



;;; `Twrite-standard-secure-g2-notification-header' ... may be called when
;;; not servicing a workstation.  Also, this may be called when there is no
;;; particular logged in user.

(defun twrite-standard-secure-g2-notification-header ()
  (tformat "Secure G2: (")
  (twrite-current-real-time)
  (let ((user? (if servicing-workstation?
		   (g2-user-name-for-this-workstation? current-workstation))))
    (if user?
	(tformat "; User: ~a)  " user?)
	(tformat ")  "))))

;; Notes on the messages: the "standard header", including some pretty
;; unique constant text and a date stamp, is to make it easier to develop a
;; system administration script that identifies these security changes to a
;; site administrator. It should especially be possible to detect changes
;; to passwords, done elsewhere. (MHD 2/12/98)



;;; `Twrite-current-real-time' ...

(defun twrite-current-real-time ()  
  (multiple-value-bind (seconds minutes hours day month year)
      (get-decoded-real-time)
    (print-decoded-time seconds minutes hours day month year)))

;; See if something almost identical already exists!  Move elsewhere! (MHD 2/12/98)








;;;; Disseminating Telewindows Info



;;; `Set-session-info-in-workstation' ... If the user-name property is
;;; specified, it is used as the value for the
;;; g2-user-name-for-this-workstation? slot.  Otherwise, this slot defaults to
;;; the read/interned version of the o/s user name.
;;;
;;; This function sets the time of the connection based on the current real
;;; time (variable current-real-time).
;;;
;;; Text strings for language, window name, user-name, and os-user-name that are
;;; encountered here are assumed to be in the Gensym character set.  (If they
;;; were passed over ICP, then they would have automatically been coerced into
;;; that format by stripping illegal gensym character sequences out if
;;; necessary.)

(defun set-session-info-in-workstation (gensym-window workstation)
  (macrolet ((s (slot indicator &optional processing?)
	       `(let ((value? 
			(get-gensym-window-parameter
			  gensym-window ,indicator)))
		  (when value?
		    (setf (,slot workstation)
			  (prog1 (case ,processing?
				   (build-symbol
				    (intern-text-string
				      (copy-text-string-with-case-conversion
					value? ':all)))
				   (password
				    (if (fixnump value?) ;; Note 2.
					nil
					(copy-for-slot-value value?)))
				   (t (copy-for-slot-value value?)))
			    (reclaim-slot-value (,slot workstation))))))))
    
    (s g2-user-name-for-this-workstation? 'user-name 'build-symbol)
    (when (null (g2-user-name-for-this-workstation? workstation))
      (s g2-user-name-for-this-workstation? 'os-user-name 'build-symbol))
    
    (s g2-user-password-for-this-workstation? 'md5-password); Note 1 & 2
    (s g2-user-discard-user-settings-for-this-workstation-p
       'discard-user-settings)
    (s g2-user-mode-for-this-workstation? 'user-mode 'build-symbol)
    (s g2-window-name-or-class-for-this-workstation 'window 'build-symbol)
    (s specific-language-for-this-workstation? 'language 'build-symbol)
    (s style-specifically-for-this-workstation? 'window-style)
    (s cjk-typeface-preference-for-this-workstation? ; New! (MHD 4/9/99)
       'cjk-language 'build-symbol)
    (s g2-window-init-string? 'init-string)

    (s workstation-network-host-name? 'network-host-name)
    (s workstation-os-user-name? 'os-user-name)
    (s workstation-os-type? 'os-type)
    (s workstation-reroute-problem-report? 'reroute-problem-report)

    (setf (time-of-telewindows-connection? workstation)
	  (prog1 (copy-managed-float (clock-get current-real-time))
	    (reclaim-slot-value
	      (time-of-telewindows-connection? workstation))))
    

    ))

;; Note 1: Prior to a bug fix (in Beta Phase II "almost released"), passwords
;; were sent in a strings.  That did not work.  They must be encoded as numbers
;; on the far side.  Note that the encoding is done by Telewindows, and must
;; produce exactly the same results as on "our" side, i.e., identical encoding
;; source code.  (MHD 3/7/95)

;; Note 2: The md5-password property appears in the property list
;; only as of version 15 (see See
;; icp-window-protocol-supports-md5-password-encryption.) but since
;; the plist is sent before we know the version number we just wing
;; it.  Meanwhile the property 'password is still there, it's just
;; not relevant.

(defun-void set-session-info-in-g2-login (workstation g2-login)
  (macrolet ((s (g2-login-slot workstation-slot)
	       `(progn
		  (reclaim-slot-value (,g2-login-slot g2-login))
		  (setf (,g2-login-slot g2-login)
			  (copy-for-slot-value
			    (,workstation-slot workstation))))))
    (s g2-login-user-name?
       g2-user-name-for-this-workstation?)
    (s g2-login-encoded-password?
       g2-user-password-for-this-workstation?)
    (s g2-login-user-mode
       g2-user-mode-for-this-workstation?)
    (s g2-login-window-name-or-class
       g2-window-name-or-class-for-this-workstation)
    (s g2-login-specific-language-for-this-g2-window?
       specific-language-for-this-workstation?)
    (s g2-login-style-specifically-for-this-workstation?
       style-specifically-for-this-workstation?)
    (s g2-login-init-string?
       g2-window-init-string?)))




;;; `Record-session-info-from-g2-login' is used to copy session information
;;; from the g2-login instance to the gensym window (and its associated
;;; workstation) in the case where a login has succeeded.  Shortly after this
;;; step, the gensym window will be partnered in with a g2 window, at which
;;; point the following function, `set-session-info-in-g2-window', is called
;;; upon to set up the corresponding slots in the g2-window (with the exception
;;; of the window-name-or-class and password slots, which are not stored).
;;;
;;; All values are copied and reclaimed using copy-for-slot-value and
;;; reclaim-slot-value, respectively.  In the case of
;;; set-session-info-in-g2-window, changes to the g2-window pass through the
;;; change-slot-value interface.

#+unused
(defun-void record-session-info-from-g2-login (g2-login workstation)
  (macrolet ((s (workstation-slot g2-login-slot)
	       `(progn
		  (reclaim-slot-value (,workstation-slot workstation))
		  (setf (,workstation-slot workstation)
			  (copy-for-slot-value (,g2-login-slot g2-login))))
	       #+obsolete
	       `(reclaim-slot-value
		  (prog1 (,workstation-slot workstation)
		    (setf (,workstation-slot workstation)
			  (copy-for-slot-value (,g2-login-slot g2-login)))))))    
    (s g2-user-name-for-this-workstation? g2-login-user-name?)
    (s g2-user-password-for-this-workstation? g2-login-encoded-password?)
    (s g2-user-mode-for-this-workstation? g2-login-user-mode)
    (s g2-window-name-or-class-for-this-workstation
       g2-login-window-name-or-class)
    (s specific-language-for-this-workstation?
       g2-login-specific-language-for-this-g2-window?)
    (s g2-window-init-string?
       g2-login-init-string?)))


;;; `Set-session-info-in-g2-window' ...
;;;
;;; IMPORTANT: there's a tradition of not changing the values in the g2-window
;;; slots unless they're different (non-eql).  If we always changed them (i.e.,
;;; using change-slot-value), then whenever rules that hang off of them would
;;; always fire.  It's not a clear contract with users that this should or
;;; shouldn't happen; however, there's no good reason to change what we've
;;; always done.  It would just gratuitously break user code, albeit code that
;;; shouldn't really depend on this feature.   (Same goes for the subfunction
;;; copy-gensym-window-attributes-into-g2-window.)


(defun set-session-info-in-g2-window (workstation g2-window)
  (macrolet ((s (g2-window-slot workstation-slot)
	       `(unless (eql		; don't change if not changing
			  (,g2-window-slot g2-window)
			  (,workstation-slot workstation))
		  (change-slot-value
		    g2-window ',g2-window-slot
		    (copy-for-slot-value (,workstation-slot workstation))))))
    (s g2-user-name g2-user-name-for-this-workstation?)
    ;; password skipped
    (s g2-user-mode g2-user-mode-for-this-workstation?)
    ;; window-name-or-class skipped
    (s specific-language-for-this-g2-window?
       specific-language-for-this-workstation?)
    (s g2-window-initial-window-configuration-string?
       g2-window-init-string?)
    (s g2-window-style
       style-specifically-for-this-workstation?)

    ;; The rest are not in the login panel; they just come over
    ;; when a pairing has been made between a workstation/window and
    ;; a g2-window instance.
    (s g2-window-network-host-name? workstation-network-host-name?)
    (s g2-window-os-user-name? workstation-os-user-name?)
    (s g2-window-os-type? workstation-os-type?)
    (s g2-window-time-of-last-connection? time-of-telewindows-connection?)
    (s g2-window-reroute-problem-report? workstation-reroute-problem-report?)

    (copy-gensym-window-attributes-into-g2-window
      (window-for-workstation workstation))
    
    ;; Check the connection status in g2-window
    (unless (eq (g2-connection-status g2-window) 'connected)
      (change-slot-value g2-window 'g2-connection-status 'connected))))




;;; `Update-user-mode-state' is concerned with just the user-mode field.
;;; It is separated out from the 'all-at-once' cases above because it is
;;; one of the very few such properties that can change independently of
;;; the others because the user wants it to (language is probably the only
;;; other), and particularly because it can be changed on ui-client-items
;;; when there is by definition no workstation. All the checking that may
;;; be require to ensure that is is valid to do this is the responsibility
;;; of the caller.

(defun update-user-mode-state (frame new-mode)
  (frame-class-case frame
    (ui-client-session
     (let ((present-value (get-slot-value frame 'ui-client-session-user-mode)))
       (unless (eq present-value new-mode)
	 (change-slot-value
	   frame 'ui-client-session-user-mode new-mode))))
	
    (g2-window
     (update-AB-side-TW-user-mode
       new-mode frame (workstation-for-g2-window? frame)))

    (g2-login)
    ;; In this case the call originated in the change-mode / g2-login
    ;; dialog, and we don't need to do anything because the thread
    ;; will go through log-in-workstation and the update will be
    ;; done from there.

    (t
     #+development
     (cerror "Continue" "how come we got called on a ui-client-item ~
              that wasn't a g2-window or a ui-client-session: ~S"
	     frame))))



;;; `Update-AB-side-TW-user-mode' updates the user-mode when the affected
;;; structures are those used by TW (or the console), i.e. a g2-window
;;; and its associated workstation.  It is broken out as its own routine
;;; here so that there can be a single locus for this change whether it
;;; is happening as part of the initial login process or from changing the
;;; slot. Note that the common locus used to be log-in-workstation, but
;;; with the advent of TW2, it makes more sense to separate the two actions
;;; rather than overload a routine that won't be used by TW2. ddm 4/17/98

(defun-simple update-AB-side-TW-user-mode (new-mode g2-window? workstation?)
  (let ((present-value (when g2-window? (g2-user-mode g2-window?))))
    (unless (eq present-value new-mode)
      (when g2-window?
	(change-slot-value g2-window? 'g2-user-mode new-mode))
      (when workstation?
	(setf (g2-user-mode-for-this-workstation? workstation?)
	      new-mode))
      (when servicing-workstation?
	(setf current-g2-user-mode? new-mode))
      (decache-dynamic-menus 'user-mode workstation?)
      ;; For new user immediately update menu
      (when (native-menu-bar-really-needs-updating-p workstation?)
            (for-workstation (workstation?) 
                             (update-native-menu-bar workstation?))))))









;;;; Temporary home for run-event-handler



;;; The defvar `event-handler-args' is a list of arguments to pass to an event handler.
;;; It was introduced to support the `user-mouse-tracking' handler.

(defvar event-handler-args ())

;; The list gets reclaimed by reclaim-event-interpretation, called in
;; service-workstation.



;;; The function `name-of-exported-event-handler?' returns T for those raw event
;;; handlers to which the user can bind in an an item-configuration.  Only two
;;; for now (all others are full UI commands).

(defun name-of-exported-event-handler? (name)
  (memq name '(user-mouse-tracking select-area)))




;;; The function `run-event-handler' executes the handler for an event
;;; interpretation.  The interpretation name is either the full-name of a UI
;;; command, the GENERIC name of a UI command, the name of new style event
;;; handler, the name of a user menu choice, or one of the useless symbols,
;;; like SUBCOMMAND-EVENT.

;;; Event-interpretations live it two possible namespaces, according to whether
;;; they originated in a G2 keymap (internal namespace) or in an item
;;; configuration (user namespace).  Two namespaces are required in order to
;;; allow user-defined menu choices with the same name as hidden, internal G2
;;; event handlers or commands.  For example, at least one user KB defined the
;;; menu-choice GO-TO-END.  This must be allowed, and must not be confused with
;;; the editor command GO-TO-END.

;;; Now, there is some overlap in the names: some of the G2 handlers are
;;; "exported" to the user -- all those which satisfy built-in-menu-choice-p.
;;; For those names, the internal handler is run even though the name was
;;; specified in the user namespace.  Conflicting user-menu-choices are flagged
;;; with frame notes.

;; There might be more mechanism here than's really necessary.

;; ajs (4/17/96) Added further with-backtrace-for-internal-error to break down
;; types of event handlers.

(defun run-event-handler (event-interpretation mouse-pointer)
  (let* ((namespace (event-interpretation-namespace event-interpretation))
	 (name (event-interpretation-name event-interpretation))
	 (pretty-name (event-handler-pretty-name name))
	 (event-handler-args (event-interpretation-arguments event-interpretation))
	 (command? nil)
	 (frame? nil))

    (with-simple-restart (abort "Abort the ~a event handler" name)
      (reference-mouse-pointer mouse-pointer)
      (with-backtrace-for-internal-error pretty-name
	(case namespace
	  ;; The USER Namespace means interpretations derived from an item config.
	  (user
	   (cond
	     ;; The handler is a user-menu-choice.
	     ((and (setq frame? (most-interesting-frame mouse-pointer))
		   (name-of-user-menu-choice? name frame?))
	      #+development (when trace-workstation-events
			      (unless (user-menu-choice-potentially-runnable-p name frame?)
				(dwarn "The user-menu-choice ~s on ~s is not runnable now."
				       name frame?)))

	      (cond ((command-permitted-p name frame?)
		     ;; Added backtrace ajs
		     (with-backtrace-for-internal-error 'execute-user-menu-choice-if-possible
		       (execute-user-menu-choice-if-possible name frame?)))
		    (t
		     (with-drawing-trace (restrictions)
		       (format t "Restricted away menu command ~s~%" name)))))
	     
	     ;; The handler is the generic name of an exported UI command.
	     ((generic-name-of-exported-ui-command? name)
	      ;; Added backtrace ajs 
	      (with-backtrace-for-internal-error 'start-generic-command
		(start-generic-command name mouse-pointer)))

	     ;; The handler is the name of an exported raw event handler.
	     ((and (name-of-exported-event-handler? name)
		   (new-style-event-handler name))
	      ;; Added backtrace ajs
	      (with-backtrace-for-internal-error 'execute-raw-event-handler
		(funcall-symbol name mouse-pointer)))
	     
	     (t
	      (dwarn "No handler for user-space name ~s on ~s" name frame?))))

	  ;; The INTERNAL namespace means interpretations derived from built-in keymaps.
	  ;; Restrictions are checked for these commands at the time we compute the
	  ;; interpretation for an event.  See find-event-interpretation-in-context.
	  (internal
	   (cond
	     ;; The handler is the name of a specific UI command.
	     ((setq command? (find-ui-command name))
	      ;; Added backtrace ajs
	      (with-backtrace-for-internal-error 'start-ui-command
		(start-ui-command command? mouse-pointer)))
	     
	     ;; The handler is a simple event handler.
	     ((new-style-event-handler name)
	      ;; Added backtrace ajs
	      (with-backtrace-for-internal-error 'execute-simple-event-handler
		(funcall-symbol name mouse-pointer)))
	     
	     (t
	      (dwarn "No handler for internal name ~s" name))))))
      (release-mouse-pointer-if-any mouse-pointer))))

;; The handler args are used only by user-mouse-tracking.



(define-event-handler nothing ()
  ;; This gets runs by "selecting any <class> does nothing" clauses.
  nil)



;;; The function `permit-generic-ui-command-p' returns true if the given command
;;; should be considered as a possibility to run via start-generic-command,
;;; which is the same as saying that it should be allowed to run from an
;;; item-configuration. Generic commands are commands named in an
;;; item-configuration which may have multiple implementations.

(defun permit-generic-ui-command-p (command)
  ;; The constant list is all of the selection UI commands whose menu-name
  ;; conflicts with some classic command.
  (not (memq (ui-command-name command) '(selection-full-scale selection-properties
					 delete-selection clone-selection
					 transfer-selection move-selection))))

;; This is a kludge to prevent any of the newly-introduced selection UI commands
;; from being run until we figure out how to add them to item configurations
;; without causing name conflicts with user menu choices.



;;; The substitution-macro `ui-commands-to-consider-for-menu-name' handles the
;;; backwards-compatibility hack that makes the PRINT action in
;;; item-configurations really mean PRINT-TO-SERVER.

(defvar listed-print-to-server-command (list nil))

(def-substitution-macro ui-commands-to-consider-for-menu-name (menu-name)
  (cond ((and (eq menu-name 'print)
	      (print-means-print-to-server-in-configurations-p))
	 (unless (car listed-print-to-server-command)
	   (setf (car listed-print-to-server-command) (ui-command-named 'print-to-server)))
	 listed-print-to-server-command)
	(t
	 (ui-commands-with-menu-name menu-name))))


;;; The function `start-generic-command' runs the generic command with the
;;; given menu name.  We run the specific one which would have appeared in the
;;; pop-up menu for the given mouse-pointer (subject to restrictions).

;;; Since it is expensive to compute the specific menu-item, since that must
;;; loop over all potential items in the menu, we've optimized the code for
;;; commands which are in fact not generic.  If there is only one command of the
;;; given name, or if only one command passed its built-in applicability
;;; predicate, then we run that command.  If there are multiple commands
;;; satisfying their predicates, then we must compute the specific command the
;;; hard way.

(defun start-generic-command (menu-name mouse-pointer)
  (let* ((ui-command-context 'start-generic)         ; Special variable
	 (commands
	   (ui-commands-to-consider-for-menu-name menu-name))
	 (applicable-commands
	   (loop for command in commands
		 as pc? = (and (permit-generic-ui-command-p command)
			       (make-initial-partial-command command mouse-pointer))
		 if pc?
		   collect it using slot-value-cons
		 do (with-drawing-trace (run-event)
		      (format t "  Generic ~30s~a"
			      (ui-command-name command)
			      (if pc? " -- OK" " -- failed its condition")))))
	 (menu-item? nil))

    (cond ((null commands)
	   (with-drawing-trace (run-event)
	     (format t "Command ~s is undefined." menu-name)))

	  ((null applicable-commands)
	   (with-drawing-trace (run-event)
	     (format t "All commands named ~s failed their predicates~%" menu-name)))

	  ((not (command-permitted-p menu-name
				     ;; Restriction tests always on this guy.
				     (most-interesting-frame mouse-pointer)))
	   (with-drawing-trace (run-event)
	     (format t "Command ~s has been restricted away~%" menu-name))
	   (reclaim-menu-items applicable-commands))
	  
	  ((singleton? applicable-commands)
	   (with-drawing-trace (run-event)
	     (format t "Running singleton command ~s~%" (first applicable-commands)))
	   (pursue-partial-command (first applicable-commands) mouse-pointer)
	   ;; Don't reclaim the command, just the list!
	   (reclaim-slot-value-list applicable-commands))

	  ;; The slow way.  The tacit assumption here is that all commands
	  ;; which are generic have menus.  We have no other way of deciding
	  ;; which command to run.

	  ((null (setq menu-item?
		       (specific-menu-item-for-generic-command? menu-name mouse-pointer)))
	   (dwarn "Command ~s not found in menu for ~s, ignoring it!~%" menu-name mouse-pointer)
	   (reclaim-menu-items applicable-commands))

	  ((partial-command-p menu-item?)
	   (with-drawing-trace (run-event)
	     (format t "Running generic command ~s~%" menu-item?))
	   (pursue-partial-command menu-item? mouse-pointer)
	   (reclaim-menu-items applicable-commands))

	  (t
	   ;; Menu items can also be lists and symbols, but those ones
	   ;; aren't commands.
	   (with-drawing-trace (run-event)
	     (format t "Found the menu-item ~s when expecting a partial-command"
		     menu-item?))
	   (reclaim-menu-item menu-item?)
	   (reclaim-menu-items applicable-commands)))))




;;; The function `specific-menu-item-for-generic-command?' returns a newly
;;; consed menu-item which would appear in the menu for the given mouse-pointer
;;; under the given menu-name.

(defun specific-menu-item-for-generic-command? (menu-name mouse-pointer)
  (let ((menu-description?
	  (find-menu-for-spot (stack-of-spots mouse-pointer))))
    
    (when menu-description?
      (find-menu-item menu-name menu-description? mouse-pointer ()))))

;Alias cration functionality
(def-structure (user-mode-alias)
  (alias-name nil)
  (parent-user-mode nil)
  (date-of-alias-creation nil :reclaimer reclaim-managed-float)
  (who-created-the-alias nil))
  
(defun write-user-mode-alias-for-kb (alias)
  (write-char-for-kb #\|)
  (write-element-for-kb (alias-name alias))
  (write-element-for-kb (parent-user-mode alias))
  (write-element-for-kb (date-of-alias-creation alias))
  (write-element-for-kb (who-created-the-alias alias)))

(defun read-user-mode-alias-for-kb()
  (let ((alias (make-user-mode-alias)))
    (setf (alias-name alias) (read-element-for-kb nil))
    (setf (parent-user-mode alias) (read-element-for-kb nil))
    (setf (date-of-alias-creation alias) (read-element-for-kb nil))
    (setf (who-created-the-alias alias) (read-element-for-kb nil))
    alias))
  
(defun is-user-mode-present (alias-name)
  (let ((modes (compute-category-members 'g2-user-mode-for-login)))
    (loop for mode in modes do
	  (when (eq alias-name mode)
	    (return-from is-user-mode-present t)))
  nil))
  
(defun check-alias-for-possible-name (alias-name)
  (when (is-user-mode-present alias-name)
    (notify-user "Sorry, but alias or user mode with name ~a already exist." alias-name)
	(return-from check-alias-for-possible-name nil))
  (let ((error-value (validate-as-possible-user-mode alias-name)))
    (when error-value
      (notify-user "Sorry, but alias name ~a is incorrect because ~a" alias-name (string-for-localized-symbol error-value))
      (return-from check-alias-for-possible-name nil)))
  t)

;; Moved here from FILTERS. --binghe, 20/9/2014
(def-substitution-macro user-interface-clause-p (clause)
  (memq (first clause) '(configure user-interface)))

(defun add-alias-to-configuration (slot-name frame alias-name alias-parent)
  (let ((configuration 
          (copy-for-slot-value 
            (get-slot-value frame slot-name))))
    (loop for clause in configuration do
      (when (user-interface-clause-p clause)
        (loop for mode-restriction in (cdr clause) do
          (loop for mode-name in (second mode-restriction) do
	        (when (eq mode-name alias-parent)
		      (nconc (second mode-restriction) (gensym-list alias-name))
		      (return t))))))
    (set-slot-value frame slot-name configuration)))

;; make-new-alias is moved to FILTERS to satisfy macro dependency.

;For test Gensym-405 project
(defun delete-alias-from-configuration (slot-name frame alias-name)
  (let ((configuration 
          (copy-for-slot-value 
            (get-slot-value frame slot-name))))
    (loop for clause in configuration do
      (when (user-interface-clause-p clause)
        (loop for mode-restriction in (cdr clause) do
          (let ((alias-list
                  (loop for alias in (second mode-restriction) 
                    unless (eq alias alias-name) collect alias using gensym-cons)))
            (reclaim-gensym-list (second mode-restriction))
            (setf (second mode-restriction) alias-list)))))
    (set-slot-value frame slot-name configuration)))
    
(defun delete-existed-alias (alias-name)
  (let* ((aliases
          (copy-for-slot-value
            (get-slot-value kb-configuration 'user-mode-aliases)))
         (new-aliases
           (loop for alias in aliases 
             unless (eq alias-name (alias-name alias)) collect alias using gensym-cons)))
    (reclaim-gensym-list aliases)
    (set-slot-value kb-configuration 'user-mode-aliases new-aliases)
	(add-or-delete-mode-name-from-directory-of-names alias-name t)
	(delete-alias-from-configuration 'main-menu-user-restrictions kb-configuration alias-name)
	(delete-alias-from-configuration 'global-keyboard-command-user-restrictions kb-configuration alias-name)
	(loop for item being class-instances of 'item doing
	  (delete-alias-from-configuration 'object-configuration item alias-name)
      (when (class-definition-p item)
        (delete-alias-from-configuration 'instance-configuration item alias-name))))
 t)
 
(defun compare-aliases-restrictions (clauses alias-name1 alias-name2) ;returns t if aliases are equal
  (loop for clause in clauses do
    (when (user-interface-clause-p clause)
      (loop for mode-restriction in (cdr clause) do
        (let ((alias1-present nil) (alias2-present nil))
          (loop for mode-name in (second mode-restriction) do
            (when (eq mode-name alias-name1)
              (setq alias1-present t))
            (when (eq mode-name alias-name2)
              (setq alias2-present t)))
          (unless (eq alias1-present alias2-present)
            (return-from compare-aliases-restrictions nil))))))
  t)

(defun-for-system-procedure compare-aliases (alias1 alias2)
  (unless (compare-aliases-restrictions
            #+chestnut-trans
            (main-menu-user-restrictions kb-configuration)
            #-chestnut-trans
            (main-menu-user-restrictions-function kb-configuration)
            alias1 alias2)
    (return-from compare-aliases (make-evaluation-truth-value falsity)))

  (unless (compare-aliases-restrictions
            #+chestnut-trans
            (global-keyboard-command-user-restrictions kb-configuration)
            #-chestnut-trans
            (global-keyboard-command-user-restrictions-function kb-configuration)
            alias1 alias2)
    (return-from compare-aliases (make-evaluation-truth-value falsity)))

  (loop for item being class-instances of 'item doing
    (unless (compare-aliases-restrictions (object-configuration item) alias1 alias2)
      (return-from compare-aliases (make-evaluation-truth-value falsity)))
    (when (class-definition-p item)
      (unless (compare-aliases-restrictions (instance-configuration item) alias1 alias2)
        (return-from compare-aliases (make-evaluation-truth-value falsity)))))

  (make-evaluation-truth-value truth))
 
(defun-for-system-procedure g2-add-alias (alias-name parent-mode)
  (unless (and (is-user-mode-present parent-mode)
              (check-alias-for-possible-name alias-name))
    (return-from g2-add-alias (make-evaluation-truth-value falsity)))
  (let ((g2-login (make-frame 'g2-login)))
    (setf (g2-login-user-name? g2-login) alias-name)
    (setf (g2-login-user-mode g2-login) parent-mode)
    (make-new-alias g2-login)
    (make-evaluation-truth-value truth)))

(defun-for-system-procedure g2-delete-alias (alias-name)
  (if (delete-existed-alias alias-name)
    (make-evaluation-truth-value truth)
    (make-evaluation-truth-value falsity)))

(defun-for-system-procedure is-alias-present (alias-name)
  (if (is-user-mode-present alias-name)
    (make-evaluation-truth-value truth)
    (make-evaluation-truth-value falsity)))

;; moved here from TABLES, --binghe, 10set2014

(defun put-up-aliases-table (user-mode-aliases)
  (let ((cell-format
          (if new-g2-classic-ui-p
              'new-attribute-description-format
              (choose-font-format-per-fonts-table
                'attribute-description-format 'font-for-attribute-tables)))
        (table-format
          (if new-g2-classic-ui-p
              'new-attributes-table-format
              'attributes-table-format))
        (rows nil)
        (table nil))

    (loop for user-mode-alias in user-mode-aliases do
      (let ((alias-name
             (make-text-cell
               (convert-text-string-to-text
                 (tformat-text-string "~a" (alias-name user-mode-alias)))
               cell-format))
            (parent-user-mode
             (make-text-cell
               (convert-text-string-to-text
                 (tformat-text-string "~a" (parent-user-mode user-mode-alias)))
               cell-format))
            (date-of-alias-creation
             (make-text-cell 
               (convert-text-string-to-text
                 (twith-output-to-text-string
                   (twrite-unix-time (date-of-alias-creation user-mode-alias))))
               cell-format))
            (who-created-the-alias 
             (make-text-cell 
               (convert-text-string-to-text
                 (tformat-text-string "~a" (who-created-the-alias user-mode-alias)))
               cell-format)))
        (setq rows (gensym-cons
                     (gensym-list
                       alias-name
                       parent-user-mode
                       date-of-alias-creation
                       who-created-the-alias)
                     rows))))

    (setq rows (gensym-cons
                 (gensym-list                              ;Table header
                   (make-text-cell                         ;Alias name
                     (convert-text-string-to-text
                       (tformat-text-string "Alias name"))
                     cell-format)
                   (make-text-cell                         ;Parent user mode name
                     (convert-text-string-to-text
                       (tformat-text-string "Parent user mode name"))
                     cell-format)
                   (make-text-cell                         ;Date of alias creation
                     (convert-text-string-to-text
                       (tformat-text-string "Date of alias creation"))
                     cell-format)
                   (make-text-cell                         ;Who created the alias
                     (convert-text-string-to-text
                       (tformat-text-string "Who created the alias"))
                     cell-format))
                 rows))
    (setq table (make-or-reformat-table rows table-format nil))
    (let ((workspace
            (make-workspace
             'temporary-workspace nil table
             (if new-g2-classic-ui-p 0 2))))
      (when new-g2-classic-ui-p
        (change-slot-value
          workspace
          'workspace-background-color?
          (get-ui-parameter 'system-workspace-background-color)))
      (change-slot-value
        workspace
        'title-bar-caption-text
        (convert-text-string-to-text
          (copy-text-string "User Mode Aliases")))
      (post-workspace-in-pane
        workspace
        current-workstation-detail-pane
        nil
        nil))))

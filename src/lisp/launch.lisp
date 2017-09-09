;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module LAUNCH

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Peter Fandel, and John H.

;;; This module contains some code for launching.




(declare-forward-references (:suppress-module-checks-for gsi gw telewindows ctest)
  (g2-stream-close                         function STREAMS)
  (ne-initialize-event-handling            function NETWORKS)
  (generic-listener-initialized?           variable INT4)
  (establish-g2-network-listeners          function INT4)
  (get-frame-window-type                   function WINDOWS4)
  (send-logbook-messages-to-console-p      variable DEBUG)
  (debug-frame-reference-balance?          variable KB-SAVE1)
  (log-file-outputting?                    variable BOOKS)
  (close-log-file                          function BOOKS)
  (send-messages-to-logbook-p              variable BOOKS)
  (send-messages-to-console-p              variable BOOKS)
  (trace-system-calls-p                    variable STACK-INST)
  (echo-dialog-spec-p                      variable CONTROLS)
  (write-bytecode-profiling-report         function STACK-UTILS)
  )


;;;; Starting AB from Lisp

;;; The macro `define-system-access' sets up the user interface to the AB system
;;; in all of the machine specific ways.  It may change a great deal of the
;;; state of the world, depending on the implementation, but should be able to
;;; be evaluated multiple times.  It should set up the primitive base upon which
;;; the other primitive functions can run.  This includes:

;;;    (1) a system window
;;;    (2) a pointing device with cursor and selecting
;;;    (3) a keyboard input buffer

;;; The proper interface to running a system is to call the function
;;; `launch-system' with one argument, the symbol naming the system.  This will
;;; in turn call the launch-function? for that system, a function of no
;;; arguments, which is defined in the expansion of define-system-access.

;;; The correct means of shutting down a process is not well defined.  (So says
;;; jra on 8/18/93.)  One can get out by throwing to the catch tag 'shutdown,
;;; but other interfaces have been presented.  There is a function here in
;;; platforms called shut-down-ab-process.  It is declared funcallable, which
;;; leads me to believe that this is called from a system procedure.  I don't
;;; know why that would be.  There is also a function called quit defined in the
;;; file interfaces.  This is set up as a very low level interface that seems to
;;; try and exit this process ASAP, without throwing out to perform any
;;; unwind-protects or other niceties.  We should improve this interface, when
;;; we can assemble the required audience to talk over the alternatives.  -jra
;;; 8/18/93

;;; On LISP Machines, it works by defining a System Key binding (that's a
;;; Select Key on 3600's) that will bring up the system window.  If the system
;;; name has a non-null fixed-system-key property, then that must be the
;;; character intended to be used.  Otherwise, the alphabet from A to Z and
;;; then the numbers from 0 to 9 are searched in order for the first letter
;;; available for this system and not taken by any other.  It then defines a
;;; flavor of tv window for use as the `system window handle' by higher level
;;; code.  This flavor of window is tv::window with tv::process-mixin mixed in.
;;; On the TI Explorer, the the regular PDL is created with the size 75000
;;; (measured in Q's), which is two and a half times the default.  The special
;;; PDL is created with the default size of 2000.  On Symbolics, both PDLs are
;;; created with their default size.

;;;    (1) Default font is MEDFNT
;;;    (2) :Save-bits is T
;;;    (3) :Deexposed-typeout-action is :permit
;;;    (4) :borders is nil
;;;    (5) :blinker-p is nil

;;; No special purpose methods or instance variables are defined.

;;; A create-and-run-function function should be defined and put on the
;;; property list of the system under the create-and-run-function property.
;;; The function takes no arguments and shoud create the window, perhaps a
;;; process, and any miscellaneous tasks, and then call run-system-process.
;;; This should run until the user is finished loading the system.  Having it
;;; be suspended is ok, as long as it does not interfere with real-time
;;; activities.


(def-global-property-name system-top-level-function)
(def-global-property-name system-run-function)
(def-global-property-name system-window-title-string)
(def-global-property-name system-icon-title-string)

;; Alternatively for TW: "Gensym G2 Real-Time Rule Engine - Telewindows Client",
;; but we want strings which have distinct prefixes.

(defun-for-macro default-system-window-title-string (system-name)
  (case system-name
    ((g2 ab) "Gensym G2 Real-Time Rule Engine - Server") ; Per Dave Siegel
    (telewindows "Telewindows Client")
    (t "Gensym")))

;; jh, 5/19/92.  Added new property, system-icon-title-string, which gives the
;; default icon name for those window systems that support it.  This ends up
;; getting passed through c-x11-initialize down to XSetStandardProperties() in
;; xwindows.c.

(defmacro define-system-access (system-name)
  (let ((system-top-level-function
          (format-symbol "RUN-~A-PROCESS-TOP-LEVEL" system-name))
        (system-run-function (format-symbol "RUN-~A" system-name))
        (launch-function (format-symbol "LAUNCH-~A" system-name))
        (system-window-title-string
          (default-system-window-title-string system-name))
        (system-icon-title-string
          (case system-name
            ((g2 ab) "G2") (telewindows "TW") (t "Gensym"))))
    `(progn
       ;; Define a top level function (may only apply for x-windows?):
       (defun-for-top-level ,system-top-level-function (native-window)        ; special variable?
         (run-system-process
           ',system-name native-window ',system-run-function))
       (defun-for-top-level ,launch-function ()
         (launch-system-process ',system-name))
       ,@(when (eval-feature :development)
           `((pushnew ',launch-function *list-of-funcalled-functions*)
             (pushnew ',system-top-level-function *list-of-funcalled-functions*)
             (pushnew ',system-run-function *list-of-funcalled-functions*)))
       (setf (system-top-level-function ',system-name) ',system-top-level-function)
       (setf (system-run-function ',system-name) ',system-run-function)
       (setf (launch-function? ',system-name) ',launch-function)
       (setf (system-window-title-string ',system-name) ',system-window-title-string)
       (setf (system-icon-title-string ',system-name) ',system-icon-title-string)
       ',system-name)))

;; jh, 9/22/93.  Added cache-command-line-if-necessary to the launch-function
;; created by define-system-access.  This will cache command-line arguments in
;; the variable unix-command-line-arguments immediately after G2/TW is launched.
;; We can no longer put this functionality in the main.c files, since they are
;; automatically generated now (and rightly so).

(declare-gsi-api-symbol launch-gsi)





;;; `Make-native-window' returns the native window.  System should be one of
;;; TELEWINDOWS or AB.

(defun make-native-window (system &optional geometry? fullscreen? name? icon-name?)
  (let ((user-wants-full-screen-p
          (or fullscreen?
              (get-command-line-flag-argument #w"fullscreen")))
        (geometry-command-line-option-string
          (or geometry?
              (get-command-line-keyword-argument #w"geometry")))
        (x-offset -1)
        (y-offset -1)
        (width -1)
        (height -1))
    (when geometry-command-line-option-string
      (multiple-value-setq
          (x-offset y-offset width height)
        (get-values-from-x11-parse-geometry geometry-command-line-option-string)))
    (clear-fixnum-time-alarm)
    (c-x11-initialize
      #-chestnut-3
      (or (get-environment-variable-value "DISPLAY") ":0.0")
      #+chestnut-3
      (get-default-x11-display) ;SS_G2L
      (setf (system-window-title-string system)
            (or name?
                (get-window-name-from-command-line-if-any)
                ;; GENSYMCID-601: Faster-601-Add configuration for multicore
                #+SymScale
                (format nil "~A (multicore)" (system-window-title-string system))
                #-SymScale
                (system-window-title-string system)))
      (or icon-name?
          (get-icon-name-from-command-line-if-any)
          (get-window-name-from-command-line-if-any)
          (system-icon-title-string system))
      (if user-wants-full-screen-p
          -2
          (or (get-command-line-keyword-argument-as-integer #w"width")
              width))
      (if user-wants-full-screen-p
          -2
          (or (get-command-line-keyword-argument-as-integer #w"height")
              height))
      x-offset
      y-offset
      (if (get-command-line-flag-argument #w"no-backing-store") 0 1)
      (if (get-command-line-flag-argument #w"private-colormap") 1 0)
      (get-frame-window-type system))))



(defun announce-system-presence (system)
  (format t "~%")
  (multiple-value-bind (second minute hour date month year
                               day-of-the-week daylight-savings-time-p
                               time-zone)
      (get-decoded-real-time)
    (declare (ignore day-of-the-week daylight-savings-time-p time-zone))
    ;; Note that the format string below doesn't use any fancy formatting
    ;; directives, like filled field integer displays to put a zero in front of
    ;; small minute counts, since they don't work in Chestnut.  -jra 8/18/93
    (format t
            "~%[~d-~a~d-~a~d ~d:~a~d:~a~d]"
            year
            (if (<f month 10) "0" "")
            month
            (if (<f date 10) "0" "")
            date
            hour
            (if (<f minute 10) "0" "")
            minute
            (if (<f second 10) "0" "")
            second)
    ;; jh, 7/16/94.  *Print-case* defaults to :downcase when Chestnut launches,
    ;; despite CLtL/2e p 560, which mandates :upcase.  So without the binding
    ;; that follows "G2" prints as "g2", since we have not yet entered the
    ;; bindings provided by with-lisp-defaults.
    (let ((*print-case* :upcase))
      (format t "~%~a " (system-alias system)))
    (write-system-version (system-version system))
    (format t " (~a)" build-identification-string)
    ;; Suggestion HQ-4861256, "print build-comment-string to logfile"
    (when build-comment-string
      (format t " (~a)" build-comment-string))
    (format t " ~%"))
  
  )

;; We should add a predicate on systems that controls whether or not to
;; announce its presence to the world.  -jra 8/18/93
;;
;; Agreed.  We should also not print to standard output if it messes up
;; the screen under Windows(tm)! (MHD 10/14/94)




;;; The function `maybe-wait-for-return-key' may pause the DOS shell window in the
;;; case of an abnormal exit so that people can read any error messages in that
;;; window.

(defun maybe-wait-for-return-key (&optional exit-requested-by-user?)
  (unless (eq exit-requested-by-user? 'requested)
    (c-maybe-wait-for-return-key))
  t)


(def-gensym-c-function c-maybe-wait-for-return-key
                       (:void "g2ext_maybe_wait_for_return_key")
  ())



;;; Current-Process-handle is some object that provides identification and/or
;;; access to the system process.  It is used as an argument to certain
;;; primitive functions.

(defvar system-window)

(defvar current-system-name nil)
(defvar current-process-handle)
(defvar current-system-version)

;;; The function `launch-system-process' runs initializations for a new process,
;;; and then calls the top level function of that process.  This function is an
;;; internal below launch-system and the launch-function? of a system, which are
;;; the two correct interfaces to call when running a new instance of a system
;;; such as ab or telewindows.  Initializations to a process should be added
;;; here, rather than in launch-system, since launch-system may be bypassed in
;;; favor of the launch-function? of a system.

(defun-for-top-level launch-system-process (system)
  (let*-or-set-for-system ((current-system-name system))
    (current-system-case
      (gsi) ; moved to run-gsi-1
      (t (cache-command-line-if-necessary)))
    ;; We should consider leaving some mention of garbage collections in
    ;; development, so developers can know what is going on.  -jra 8/18/93
    #+(and lucid (not translator))
    (current-system-case
      (gsi)
      (t (verify-operating-system
           (if (get-command-line-flag-argument #w"use-os-emulation") 0 1))))
    (initialize-g2pointers)
    (initialize-locales)
    (ne-initialize-event-handling)
    (current-system-case
      (gsi
        (funcall (system-top-level-function system) nil))
      (telewindows
       (x11-preinitialize-if-necessary)
       (unwind-protect
            (maybe-wait-for-return-key
              (funcall (system-top-level-function system) nil))
         #-development
         (exit-lisp-process)))
      (ab
        (let ((timeout (get-command-line-keyword-argument #w"file-operation-timeout")))
          (when timeout
            (c-set-file-operation-timeout timeout)))
        (when (get-command-line-flag-argument #w"copy-messages-on-logbook")
          (setq send-messages-to-logbook-p t))
        (when (get-command-line-flag-argument #w"copy-messages-on-console")
          (setq send-messages-to-console-p t))
        (when (get-command-line-flag-argument #w"copy-logbook-on-console")
          (setq send-logbook-messages-to-console-p t))
        (when (get-command-line-flag-argument #w"debug-frame-reference-balance")
          (setq debug-frame-reference-balance? t))
        (when (get-command-line-flag-argument #w"trace-system-calls")
          ;; this helps in debugging kbs that use player
          (setq trace-system-calls-p 2000)) ; debug the first 2000 system calls
        (when (get-command-line-flag-argument #w"echo-dialog-spec")
          (setq echo-dialog-spec-p t))

        (cond
          ((system-is-windowless-p system)
           (unwind-protect
                (maybe-wait-for-return-key
                  (funcall (system-top-level-function system) nil))
             #-development
             (exit-lisp-process)))
          ((or (local-gensym-x11-display)
               (x11-display-specified-p)
               (no-local-window-p))
           (x11-preinitialize-if-necessary)
           (unwind-protect
                (maybe-wait-for-return-key
                  (funcall (system-top-level-function system)
                           (make-native-window system)))
             #-development
             (exit-lisp-process)))
          (t (print-display-error)
             (maybe-wait-for-return-key nil)
             #-development
             (exit-lisp-process))))
      (t
       (cerror "go on"
               "unknown system")))))


;;;; Running a System Process

;; jh, 8/17/93.  Moved the defvars for g2-operating-system and g2-machine-type
;; to BOOTSTRAP.  We still need to define the foreign function
;; c-get-platform-code here, though, due to a dependency on
;; def-gensym-c-function.

(def-gensym-c-function c-get-platform-code
                       (:fixnum-int "g2ext_get_platform_code")
  ())

;;; Run-system-process runs a (software) `system process' that is an instance
;;; of the system named system-name.

;;; System-name must be the "normalized" version of the system name.  (See
;;; declare-system and normalize-system-name in the BOOTSTRAP module and the
;;; section above on system variables.)  System-name is used in
;;; with-system-variables, as well as for other purposes.

;;; System-specific-run-function is called, with either nil or a gensym window
;;; corresponding to initial-native-window? when specified, within a context in
;;; which a large number of special variables are bound and in which a
;;; high-level abort will be handled.  The special variables bound in this
;;; context include standard Common Lisp variables, system variables,
;;; "primitive bindings", etc.

;;; Run-system-process binds Common Lisp special variables as follows:
;;;
;;;   *package* .................... the AB package
;;;
;;;   *read-base* .................. 10
;;;   *read-default-float-format* .. (gensym-float-type)
;;;
;;;   *print-radix* ................ nil
;;;   *print-array* ................ nil
;;;   *print-pretty* ............... nil
;;;   *print-case* ................. :upcase
;;;
;;;   *break-on-warnings* ..........  nil
;;;
;;;   *terminal-io* ................ *terminal-io*
;;;   *standard-output* ............ *terminal-io*
;;;   *error-output* ............... *terminal-io*
;;;   *standard-input* ............. *terminal-io*
;;;   *debug-io* ................... *terminal-io*

;; Consider having the system-specific run function specified where the system
;; is declared.

;; mhd & jh, 1/16/91.  Removed setup of (system-pathname system-name) and changed
;; all references to the system variable process-specific-system-pathname, defined
;; in the module PATHNAMES.

(defmacro with-lisp-defaults (&body body)
  `(let*-or-set-for-system
     ((*package* (find-package "AB"))
      (*read-base* 10.)
      (*read-default-float-format*
        (gensym-float-type))
      ;; E exponent marker => gensym-float
      (*print-base* 10.)
      (*print-array* nil)
      (*print-case* :upcase)
      (*terminal-io* *terminal-io*)        ; just to be "safe"
      (*standard-input* *terminal-io*)
      ;; jh, 9/28/93.  Removed the following binding until Chestnut can fix
      ;; a bug where doing this binding makes format no longer recognizes t.
      #-chestnut-3 (*standard-output* *terminal-io*)
      (*error-output* *terminal-io*)
      (*debug-io* *terminal-io*)
      ;; jh, 2/5/93.  Following two parameters are not supported in Chestnut
      ;; 3.1, although they are in Common Lisp, both ANSI and CLtL.
      #-chestnut-3 (*print-radix* nil)
      #-chestnut-3 (*print-pretty* nil)
      ;; jh, 6//9/93.  Following parameter is not supported by Chestnut,
      ;; since it is not in ANSI Common Lisp.  -- generally not in
      ;; ansi-cl (including allegro). (MHD 6/10/00)
      #-(or chestnut-3 ansi-cl) (*break-on-warnings* nil)
      )
     ,@body))

(defun-for-top-level run-system-process
    (system-name initial-native-window? system-specific-run-function)
  (let ((shutdown-catch-tag 'shutdown))
    (catch shutdown-catch-tag
      (loop do
        (catch-abort (0)
          (with-lisp-defaults
            (let*-or-set-for-system
              ((system-window nil)
               (current-system-name system-name)
               (current-process-handle (make-symbol "CURRENT-PROCESS"))
               (current-system-version (system-version system-name)))
              (with-primitive-bindings (system-name) ; calls set-up-lisp-memory-management
                (with-system-variables (system-name current-process-handle)
                  (current-system-case
                    (ab (get-node-id-for-uuid-1))) ; cache now, and avoid possible trouble later
                  (setq generic-listener-initialized?
                        (establish-g2-network-listeners))
                  (with-protected-listeners
                    (with-protected-streams
                      (atomic-exchange system-window
                            (and initial-native-window?
                                 (make-or-revise-window-per-native-window
                                   nil
                                   initial-native-window?)))
                      (current-system-case
                        (gsi)
                        (t (announce-system-presence system-name)
                           (report-memory-usage system-name)))
                      (funcall system-specific-run-function
                               system-window))))))))))))

;; Added system-name argument to with-primitive-bindings scope, so we can set up
;; memory in a product-specific way.  (jh, 8/2/90)

;; Moved with-protected-streams from with-primitive-bindings to inside the
;; with-system-variables scope, so we can properly reclaim open streams and their
;; associated gensym-pathnames.  jh, 1/24/91.

;; Added with-protected-listeners as part of per-process license checking.  We
;; don't want the license listener hanging around after G2 exits.  jh, 8/13/91.



;;; Shut-down-ab-process ...

(defun shut-down-ab-process (&optional status)
  (current-system-case
    ((ab)
     (close-log-file)
     ;; currently release-all-kb-write-locks doesn't do anything, but if it did,
     ;; it would act upon streams, which would be closed (as per comment below).
     ;; Therefore, it needs to be here
     (release-all-kb-write-locks)))
  (shutdown-or-exit status))

(declare-funcallable-symbol shut-down-ab-process)

;; This should first shut down: all domestic workstations, windows, and servers; all
;; dependent processes; all icp connections; etc!  It should also deallocate memory
;; wherever feasible!

;; yduj, 8/00: you would think that the file cleanup above could be done in
;; shutdown-system-for-exit, however, shutdown-system-for-exit is called by
;; with-protected-listeners, and inside its context, is with-protected-streams,
;; and that will close all of the streams that might be needed by
;; shutdown-system-for-exit, causing duplicate close files etc.  Another
;; solution would be to reverse the order of with-protected-listeners and
;; with-protected-streams.


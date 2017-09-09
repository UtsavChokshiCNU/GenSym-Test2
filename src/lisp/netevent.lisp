;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module NETEVENT
;;;;   network event handling machinery for 5.0


;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Nicholas C. Caruso

;;; organization:
;;;    lisp side event handlers for network events
;;;    these functions are callable from C, and are in fact only called from the
;;;    platform-specific event loop code which will be written in C. -ncc, 1 Dec 1995
;;; events handled:
;;;   read, write, connect, accept and close, on a given socket, with an
;;;    associated status code argument.
;;;



(declare-forward-references (:suppress-module-checks-for gsi)
   (enqueue-next-icp-buffer-if-any                 function INT2)
   (call-or-schedule-handle-queued-icp-messages    function INT2)
   (icp-sockets-waiting-for-icp-message-processing variable INT2)
   (transmit-icp-output-if-ready                   function INT2)
   (send-initial-icp-version-info                  function INT3B)
   (shutdown-icp-socket-connection                 function INT4)
   (make-and-install-network-icp-socket            function INT4)
   (get-accept-pathname                            function INT4)
   (reclaim-icp-socket                             function INT4)
   (gensym-window-has-not-been-reprocessed-p       function WINDOWS1)

   #+development
   (update-pseudo-run-lights                       function WINDOWS3A)

   (delete-all-representations-for-icp-socket      function VIEW-DEF)
   (write-warning-message-string                   function DEBUG)
   (notify-user                                    function DEBUG)
   (cache-deferred-rule-invocation-indices         function SEQUENCES1)
   (rule-invocation-updates-needed-p               function SEQUENCES1)
   (poll-native-window-workstation                 function TELESTUBS)
   (maybe-schedule-service-workstation             function WORKSTATION)
   (run-one-tw-scheduler-cycle                     function TELEWINDOWS)
   (run-one-scheduler-cycle                        function CYCLES) ; one G2 scheduler cycle, that is.
)

(declare-forward-references (:suppress-module-checks-for ab gsi)
   (run-one-tw-scheduler-cycle                     function TELEWINDOWS)
)

(declare-forward-references (:suppress-module-checks-for ab telewindows)
   (run-one-gsi-scheduler-cycle                    function GSI)
   (signal-gsi-network-error                       function GSI)
)

#-chestnut-3
(declare-forward-references
  (nms-handle-if-flag-bit-init-call-handle	function native-tw)
  (nms-handle-if-flag-bit			variable native-tw)
  (nms-id-for-menu-init-call-handle		function native-tw)
  (nms-id-for-menu				variable native-tw)
  (nms-fetch-help-string-init-call-handle	function native-tw)
  (nms-fetch-help-string			variable native-tw))


;;;; Local structure & global variable definitions

;;; error message table for ICP

(eval-when (:compile-toplevel :load-toplevel :execute)

  (def-error-message-table (icp :code-offset 0)

    (success  error-severity-success "Operation was successful.")

    (read-event-error error-severity-fatal "Read event occurred on socket ~a, network error ~d, \"~a\"")
    (received-data-on-invalid-socket error-severity-fatal
                                     "Data present on socket (~a) that is not in a readable state.")
    (read-call-returned-error error-severity-fatal
                              "Call to network-read on socket ~a returned error ~d, \"~a\".")
    (write-event-error error-severity-fatal
                       "Write event occurred on socket ~a with error ~d, \"~a\".")
    (wrote-data-on-invalid-socket error-severity-fatal
                                  "Socket write event occurred on socket ~a, which is not in a writable state.~%")
    (write-call-returned-error error-severity-fatal
                               "Call to network-write on socket ~a returned error ~d, \"~a\".")
    (connect-event-error error-severity-fatal
                         "Error during connect on socket ~a: ~d, \"~a\".")
    (connect-on-invalid-socket error-severity-fatal
                               "Server connection finalized on a socket that's not connecting.")
    (accept-on-invalid-socket error-severity-fatal
                              "Client connection on a non-listener socket.")
    (accept-event-error error-severity-fatal
                        "Error during accept of client connection on listener socket ~a, error was: ~d, \"~a\".")
    (close-event-error error-severity-fatal
                       "Error during close by peer on socket ~a: ~d, \"~a\".")
    (connection-closed-error error-severity-fatal
                        "Connection closed by peer for ICP socket ~a")
    (shutdown-aborted error-severity-fatal
                        "ICP connection shutdown handshake aborted by peer on socket ~a")
    (connection-reset error-severity-fatal
                        "ICP connection reset by peer on socket ~a")
    (accept-failure error-severity-fatal
                    "network_accept() call failed, for socket ~a, error code was: ~d, \"~a\".")
    (error-obtaining-error-string error-severity-warning
                                  "Could not obtain error string for platform-specific network error, on socket ~a.")

    ))

(defun icp-error-on-socket (icp-socket error-code &optional network-error-code network-error-string)
  (when (=f (icp-error-severity error-code) error-severity-fatal)
    (let* ((icp-socket-description (icp-socket-description icp-socket))
           (error-string (tformat-text-string
                           (icp-error-format-string error-code)
                           icp-socket-description network-error-code
                           network-error-string)))
      (reclaim-text-string icp-socket-description)
      (when network-error-string
        (reclaim-text-string network-error-string))
      (if (=f (icp-connection-state icp-socket) icp-socket-listening)
          (progn
            (current-system-case
              (ab
                (write-warning-message-string 2 error-string))
              (t
                (notify-user-if-possible "~A" error-string)))
            (reclaim-text-string error-string))
          (shutdown-icp-socket-connection icp-socket error-string))
      t)))


;;;; Network event types:
;;; must match codes used in ext/c/netevent.c, defined in ext/c/netevent.h. -ncc, 31 Jan 1996

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter no-event                0) ; unused
  (defparameter read-event              1)
  (defparameter write-event             2)
  (defparameter connect-event           3)
  (defparameter accept-event            4)
  (defparameter close-event             5)
  (defparameter scheduler-event         6)
  (defparameter display-event           7)
  (defparameter read-and-block-event    8)
  (defparameter watch-event             9) ; unused
  (defparameter quit-event             10) ; unused
  (defparameter error-event            -1))

;;;; Error codes returned from the network layer

;;; These are based on the WinSock API error codes; the network layer will
;;; always return these codes to lisp, regardless of the actual transport layer
;;; API (or transport).

(defparameter network-status-success 0)

;; ... need more definitions. Winsock error codes start at 10000 or so.
;; they mostly correspond to BSD & Unix C error codes, + 10000, I think.



;;;; Global variable declarations

(defvar network-octet-buffer-length 2048) ;this is arbitrarily chosen; we could allow customers to set it.


(defvar last-event-socket-handle-holder
  (make-array 1 :element-type 'fixnum))

(defvar last-event-socket-handle)


(defvar last-event-status-code-holder
  (make-array 1 :element-type '(unsigned-byte 32)))

(defvar last-event-status-code)
(defvar last-event-status-code-0)
(defvar last-event-status-code-1)


(defvar handle-to-socket-mapping nil)        ; Sigh, this is an alist for now.
                                        ; to avoid this I think we need to hand
                                        ; down a pointer to the icp-socket
                                        ; structure in LISP.  This probably
                                        ; works fine in distribution and should
                                        ; be ok in development as long as we
                                        ; really never run a GC.-ncc, 4 Apr 1996

(def-gensym-c-function g2-event-ready (:fixnum-int "g2_event_ready")
  ((:fixnum-int wait-allowed)))

(defun-simple g2-event-ready-p ()
  (/=f 0 (g2-event-ready 0)))

(def-gensym-c-function g2-event-wait (:void "g2_event_wait")
  ())

(def-gensym-c-function g2-event-cycle (:fixnum-int "g2_event_cycle")
  ((:fixnum-int wait-allowed)))

#-chestnut-3
(defun-void initialize-event-cycle-call-handlers ()
  (g2int-network-event-handler-init-call-handle   g2int-network-event-handler)
  (g2int-open-fd-callback-init-call-handle        g2int-open-fd-callback)
  (g2int-close-fd-callback-init-call-handle       g2int-close-fd-callback)
  (g2int-writing-fd-callback-init-call-handle     g2int-writing-fd-callback)
  (g2int-not-writing-fd-callback-init-call-handle g2int-not-writing-fd-callback)
  (nms-handle-if-flag-bit-init-call-handle        nms-handle-if-flag-bit)
  (nms-id-for-menu-init-call-handle               nms-id-for-menu)
  (nms-fetch-help-string-init-call-handle         nms-fetch-help-string))

(defun-simple g2-event-cycle-handling-windows-quit ()
  (when (/=f 0 (g2-event-cycle 1)) ; allowed to wait
    ;; handle windows quit
    (shutdown-or-exit)))

;;; `g2-event-cycle-handling-windows-quit' - this function calls into C, and
;;; then, when an event is received, C calls back into Lisp to let us know about
;;; it.  We don't have C-to-Lisp working in SBCL, which means we would never
;;; handle events, and so C virtually "screams" at us and nothing ever gets done.
;;;
;;; Obviously we want to do the RIGHT thing based on the events we receive.  But
;;; we can get some basic functionality, and move on and see what else needs to
;;; be fixed, by just handling a couple of events, at some point.  So, for a
;;; very short period of time, RANDOMLY handle these two events.  This keeps
;;; things relatively quiescent and actually gets TW to a point that the splash
;;; screen not only comes up, but actually redraws!!!
;;;
;;; We are dead in the water if we cannot reliably call from C into Lisp.  But,
;;; again, this lets us (i.e., me) try to see if anything else is broken while
;;; we (i.e., the guys in Ukraine) get the C to Lisp interface working.
;;;     -jv, 12/19/07

#+chestnut-3
(defparameter internal-events-handling-trigger nil)

(defun-simple gsi-event-cycle-handling-windows-quit ()
  (when (/=f 0 (g2-event-cycle 0)) ; not allowed to wait
    ;; handle windows quit
    (shutdown-or-exit)))

(def-gensym-c-function c-network-get-last-error-string-length 
    (:fixnum-int "ne_last_error_length")
  ((:fixnum-int socket-handle)))

(def-gensym-c-function c-network-get-last-error-string (:void "ne_last_error_string")
  ((:fixnum-int socket-handle)
   (:string output-buffer)))

;; caller is responsible for the returned text string.
(defun network-get-last-error-string (handle)
  (let* ((length (c-network-get-last-error-string-length handle)))
    (if (<f 0 length)
        (let* ((buffer (obtain-simple-gensym-string length)))
          (c-network-get-last-error-string handle buffer)
          (prog1 (copy-partial-text-string buffer length)
            (reclaim-gensym-string buffer)))
        (copy-constant-wide-string #w"(Error obtaining error string)"))))


;;; debugging code
;;;
;;;(def-gensym-c-function ne-describe-socket (:void "ne_describe_socket")
;;;  ())

;;; The function `lookup-socket-from-handle' has the following contract: given a
;;; fixnum representing a NETWORK_INTERFACE structure in C, return the socket
;;; lisp structure corresponding to this handle, or NIL.
;;;
;;; This function is mostly called from handle-event-internal. The case where
;;; nil is returned can notably arise legitimately from a timing condition
;;; whereby the socket is closed before the queue of events has been drained.
;;; When handle-event-internal is called, if it is servicing events that came
;;; in before the connection was closed, it has to deal with close connections,
;;; in which case the lookup will fail, i.e., this function returns nil.

(defun-simple lookup-socket-from-handle (socket-handle)
  #+development
  (unless (fixnump socket-handle)
    (error "lookup-socket-from-handle: socket-handle not a fixnum."))
  (let ((socket (cdr (assq socket-handle handle-to-socket-mapping))))
;    #+development  ;; SEE NOTE!
;    (unless socket
;      (cerror "continue"
;              "No socket was found for handle ~D" socket-handle))
    socket))

;; NOTE: due to the legitimacy of failed mappings, we've removed this cerror.
;; It was often happening when TW multiwindow windows were closed in the middle
;; of sessions.  It was always but previously rarely if ever noticed because it
;; would only happen when the window would be closed at the end of a TW session,
;; whereas now windows come and go in the middle of a session. (MHD 6/30/03)


(defun-void register-socket-to-handle (socket socket-handle)
  (let* ((mapping? (assq socket-handle handle-to-socket-mapping)))
    (cond (mapping?
           #+development
           (when (and socket                ; this should only be used to nullify an existing mapping,
                      (cdr mapping?))        ; (or replace a null'd one)
                                        ; not replace one with another.
             (cerror "Go ahead and clobber it."
                     "register-socket-to-handle is about to replace a non-nil handle->socket mapping!"))
           (setf (cdr mapping?) socket))
          (t
           (icp-push (icp-cons socket-handle socket) handle-to-socket-mapping)))))


;; Note that close-network-handle-in-icp-socket assumes that EITHER it's not
;; necessary to close the input port, OR it's identical with the output port.
;; (both of which are true for TCP connections, at least) -ncc, 11 Apr 1995

;; NOTE THAT this routine was attempting to close the network socket for
;; localnet as well as "generic" icp-sockets.  This resulted in an abort
;; (bug HQ-400101). fixed -ncc, 25 Jul 1995

;; listeners only have an input port; everyone else gots both, and they're identical.
(defun-void close-and-disconnect-icp-socket-handle (icp-socket)
  (unless (=f (icp-connection-state icp-socket) icp-connection-closed)
    (setf (icp-connection-state icp-socket) icp-connection-closed)
    (let* ((input-port (icp-input-port icp-socket))
           (output-port (icp-output-port icp-socket))
           (handle (icp-connection-handle input-port))
           (connection-type (type-of-icp-connection icp-socket)))
      (setf (icp-connection-handle input-port) nil)
      (when output-port
        (setf (icp-connection-handle output-port) nil))
      (clear-read-event icp-socket)
      (clear-write-event icp-socket)
      (clear-close-event icp-socket)
      (cancel-task (shutdown-timeout-task? icp-socket))
      (cancel-task (icp-connection-timeout-task? icp-socket))
      (cancel-task (task-to-start-resumable-icp-writing icp-socket))
      (cancel-task (icp-socket-deregister-icp-objects-task icp-socket))
      (cancel-task (icp-message-handler-future-task? icp-socket))
      (cancel-task (icp-message-handler-current-task? icp-socket))
      (cancel-task (task-to-send-I-am-alive icp-socket))
      (let ((element (memq icp-socket icp-sockets-waiting-for-icp-message-processing)))
        (when element (setf (car element) nil)))
      (when output-port
        (let ((cons? (icp-output-port-flush-list-entry output-port)))
          (when cons?
            (setf (car cons?) nil)
            (setf (icp-output-port-flush-list-entry output-port) nil))))
      (case connection-type
        (generic
         (when handle
           (c-network-close handle)
           (register-socket-to-handle nil handle)))
        (localnet
         (let ((corresponding-localnet-socket
                 (corresponding-localnet-socket icp-socket)))
           (setf (corresponding-localnet-socket icp-socket) nil)
           (when corresponding-localnet-socket
             (setf (corresponding-localnet-socket corresponding-localnet-socket) nil)
             (enqueue-close-event corresponding-localnet-socket
                                  network-status-success))))))))

(defvar icp-sockets-to-be-reclaimed nil)

(defvar icp-socket-for-handle-icp-messages nil)

;connection-loss callbacks:
;  handle-internal-foreign-image-connection-failure
;  handle-gsi-connect-attempt-failure handle-gsi-shut-down-connection
;  handle-g2ds-connect-attempt-failure handle-g2ds-shut-down-client handle-g2ds-shut-down-server
;  gsi-maybe-notice-delayed-connection-failure gsi-connection-loss-notifier
;  icp-connection-loss-notifier
;  handle-ole-connection-shutdown
;  close-telewindows-callback
;  handle-telewindows-shutdown

(defun-simple icp-socket-notifies-user-on-error-p (icp-socket)
  (current-system-case
    (gsi
      icp-socket
      nil)
    (t
      (case (icp-socket-listener-client? icp-socket)
        (ole nil) ; no messages for ole
        (gsi nil) ; messages handled by the connection loss callback
        (g2 nil)  ; messages handled by the connection loss callback
;        (telewindows
;         (if (suppress-connection-loss-notification-for-tw-p icp-socket)
;             nil   ; don't show if suppressed, e.g., for workspace views
;             t))   ; but OK to show for general TW case
        (t t)))))

(defun-simple finalize-and-reclaim-icp-socket (icp-socket)
  (unless (memq icp-socket active-icp-sockets)
    (return-from finalize-and-reclaim-icp-socket nil))
  (when (eq icp-socket icp-socket-for-handle-icp-messages)
    (setq icp-socket-for-handle-icp-messages nil))
  (setq active-icp-sockets (delete-icp-element icp-socket active-icp-sockets))
  (let ((reason-for-shutdown? (reason-for-shutdown? icp-socket)))
    (execute-icp-callbacks 'icp-connection-loss icp-socket (null reason-for-shutdown?))
    (when (text-string-p reason-for-shutdown?)
      (when (icp-socket-notifies-user-on-error-p icp-socket)
        (current-system-case
          (ab
            (write-warning-message-string 2 reason-for-shutdown?))
          (t
            (notify-user-if-possible "~A" reason-for-shutdown?))))
      (reclaim-text-string reason-for-shutdown?)
      (setf (reason-for-shutdown? icp-socket) 'shutdown)))
  (current-system-case
    (ab
      (with-ignored-forward-references (delete-all-representations-for-icp-socket)
        (delete-all-representations-for-icp-socket icp-socket))))
  (icp-push icp-socket icp-sockets-to-be-reclaimed)
  nil)

(defvar inhibit-icp-socket-reclamation nil)

(defun-void reclaim-icp-sockets ()
  (unless inhibit-icp-socket-reclamation
    (loop while icp-sockets-to-be-reclaimed
          for icp-socket = (icp-pop icp-sockets-to-be-reclaimed)
          do (reclaim-icp-socket icp-socket))))

(defmacro with-icp-socket-reclamation (&body body)
  `(progn
     (reclaim-icp-sockets)
     (prog1 (progn ,@body)
       (reclaim-icp-sockets))))

(defmacro with-inhibited-icp-socket-reclamation (&body body)
  `(let ((inhibit-icp-socket-reclamation t))
     ,@body))

(defvar *scheduler-enabled?* nil)

;used by make-icp-connection-to-foreign-image, call-connected-foreign-function,
;        nupec-synchronize, receive-nupec-synchronize, and remote-read-eval
(defmacro with-scheduler-disabled (&rest body)
  `(with-display-events-disabled
     (let ((*scheduler-enabled?* nil))
       ,@body)))

;used by run-ab and run-telewindows-1
(defmacro with-scheduler-enabled (&rest body)
  `(with-display-events-enabled
     (let ((*scheduler-enabled?* t))
       ,@body)))

(defun-simple scheduler-enabled-p ()
  *scheduler-enabled?*)

(defun-allowing-unwind run-scheduler-for-current-system ()
  (with-scheduler-disabled ; disable recursive calls to the scheduler
    (current-system-case
      (ab
        (run-one-scheduler-cycle))
      (gsi
        (run-one-gsi-scheduler-cycle))
      (telewindows
        (run-one-tw-scheduler-cycle)))))

(defmacro with-handling-icp-messages (check-afterwards-p &body body)
  (declare (ignore check-afterwards-p))
  `(unwind-protect
        (catch 'handle-icp-messages
          ,@body)
     (when (and icp-socket-for-handle-icp-messages
                (=f (icp-connection-state icp-socket-for-handle-icp-messages)
                    icp-connection-closed))
       (finalize-and-reclaim-icp-socket icp-socket-for-handle-icp-messages))))

(def-gensym-c-function c-get-waited-period (:fixnum-int "g2ext_get_waited_period")
  ())

(def-gensym-c-function c-reset-waited-period (:void "g2ext_reset_waited_period")
  ())

(defmacro g2-event-loop-macro ()
  `(with-scheduler-enabled
     (register-profiling-activity start)

     (loop with time-at-sleep-start = (allocate-managed-float 0.0)
           with time-delta = (allocate-managed-float 0.0)
           named outer-loop
           do
       (catch-abort (1)
         (with-handling-icp-messages t
           (with-catch-handlers-for-stack-eval (t t)
             (when *scheduler-enabled?*
               (enqueue-scheduler-events-if-necessary nil))
             (when profiling-enabled?
               (mutate-managed-float-value
                 time-at-sleep-start
                 (gensym-get-unix-time))
               (exit-current-profiling-context time-at-sleep-start))

             (loop do
               (when record-fixnum-time-units-of-sleep-this-clock-tick?
                 (c-reset-waited-period))
               (g2-event-cycle-handling-windows-quit)

               #+development
               (update-pseudo-run-lights :idle-process)

               (when record-fixnum-time-units-of-sleep-this-clock-tick?
                 (c-reset-waited-period))

               (g2-event-wait)
               (when record-fixnum-time-units-of-sleep-this-clock-tick?
                 (incff fixnum-time-units-of-sleep-this-clock-tick
                        (c-get-waited-period)))))))

           finally (reclaim-managed-float time-delta)
                   (reclaim-managed-float time-at-sleep-start))))

				   
;;; This procedure helps us to avoid to process UI events at C code
(def-gensym-c-function set-handle-network-events
    (:fixnum-int "g2ext_set_handle_network_events")
  ((:fixnum-int state)))
  
(defun-allowing-unwind get-pending-network-events ()
  (current-system-case
    ((ab gsi) nil)
	(t (set-handle-network-events 1)))
  (unless *scheduler-enabled?*
    (when (g2-event-ready-p)
      (with-handling-icp-messages t
        (loop do (g2-event-cycle-handling-windows-quit)
              while (g2-event-ready-p))
        t)))
  (current-system-case
    ((ab gsi) nil)
	(t (set-handle-network-events 0))))

;;; The variable `inside-handle-event' is bound to T during the dynamic extent
;;; of handle-event-internal. It is referenced only by C code in ext/c/msmain.c

(defvar inside-handle-event nil)





;;; The following generic structure methods are called on a socket structure
;;; whenever the main event loop receives a network event for a handle to which
;;; that socket was previously registered with `register-socket-to-handle'.  The
;;; `error-code' argument is a fixnum integer, equal to `network-status-success'
;;; if there's no error.


;;; The generic structure method `handle-read-event' handles a network read or
;;; read-and-block event.  `block-p' is nil for a read event and t for a
;;; read-and-block event.  Typically this method will be called when a socket
;;; receives some number of bytes from the network, or when a socket has been
;;; closed from the other end (on Unix).

(def-generic-structure-method handle-read-event (socket error-code block-p))


;;; The generic structure method `handle-write-event' handles a network write
;;; event.  Typically this method will be called upon completion of a
;;; non-blocking write to a socket.

(def-generic-structure-method handle-write-event (socket error-code))


;;; The generic structure method `handle-network-connect' handles a network
;;; connect event.  Typically this method will be called upon completion of a
;;; non-blocking connect from a socket to some other port on the network.

(def-generic-structure-method handle-network-connect (socket error-code))


;;; The generic structure method `handle-network-accept' handles a network
;;; accept event.  Typically this method will be called when a listener socket
;;; receives a connection request from the network.

(def-generic-structure-method handle-network-accept (socket error-code))


;;; The generic structure method `handle-network-close' handles a network
;;; close event.  Typically this method will be called when a socket has been
;;; closed from the other end (on Windows).

(def-generic-structure-method handle-network-close (socket error-code))



;;; The generic structure method `handle-g2-reset' handles G2 reset.  This
;;; method will be called during the system-reset function.  The default is to
;;; ignore this event, but some sockets will want to shut down on reset.

(def-generic-structure-method handle-g2-reset (socket))



;gsi-event-handler is called only by gsi-event-cycle, which is only called from enter-abyss
;network-event-handler (which calls only handle-event-internal) is called by g2-event-loop (called by run-ab)
;  and g2-event-cycle (run-breakpoint, make-icp-connection-to-foreign-image, call-connected-foreign-function,
;           nupec-synchronize, receive-nupec-synchronize, and remote-read-eval)
;g2-event-loop is also known as tw-event-loop (called by service-telewindows-workstations)

;called by network-event-handler.
(defun-allowing-unwind handle-event-internal (event-code event-socket-handle event-status-code)
  (let ((inside-handle-event t))
    (when *scheduler-enabled?*
      (current-system-case
        (ab (register-profiling-activity idle))))
    (when (=f (rule-invocation-updates-needed-p) 1)
      (cache-deferred-rule-invocation-indices))
    (with-icp-socket-reclamation

      #+development                        ; Update run lights.
      (unless (eq current-system-name 'gsi)
        (fixnum-case event-code
          ((#.read-event #.read-and-block-event #.write-event
                         #.connect-event #.accept-event #.close-event)
           (update-pseudo-run-lights :network-event))
          ((#.scheduler-event)
           (update-pseudo-run-lights :scheduler-event))
          ((#.display-event)
           (update-pseudo-run-lights :display-event))))

      (fixnum-case event-code
        ((#.read-event #.read-and-block-event #.write-event
                       #.connect-event #.accept-event #.close-event)
         (let ((socket (lookup-socket-from-handle event-socket-handle)))
           (cond
             ((null socket)
              ;; do nothing, lookup failed.
              )
             (t
              (fixnum-case event-code
                ((#.read-event #.read-and-block-event)
                 (handle-read-event socket
                                    event-status-code
                                    (=f event-code #.read-and-block-event)))
                ((#.write-event)
                 (handle-write-event socket event-status-code))
                ((#.connect-event)
                 (handle-network-connect socket event-status-code))
                ((#.accept-event)
                 (handle-network-accept socket event-status-code))
                ((#.close-event)
                 (handle-network-close socket event-status-code)))))))
        ((#.scheduler-event)
         (when (scheduler-enabled-p)
           (run-scheduler-for-current-system)))
        ((#.display-event)
         (handle-display-event))
        ((#.error-event)
         (current-system-case
           (gsi
             (signal-gsi-network-error event-socket-handle event-status-code))
           (t
             (notify-user-if-possible
               "Error event! ~% socket-handle is ~s, event-status is ~s.~%"
               event-socket-handle event-status-code))))
        (otherwise
          #+development
          (cerror "Ignorance is bliss!" "Unknown event code ~d, event status was ~d"
                  event-code
                  event-status-code)
          #-development
          (notify-user-if-possible "Unknown event code ~d seen." event-code)))
      (fixnum-case event-code
        ((#.read-event #.read-and-block-event #.write-event
                       #.connect-event #.accept-event #.close-event)
         (current-system-case
           (ab (register-profiling-activity icp)))))

      (when *scheduler-enabled?*
        (enqueue-scheduler-events-if-necessary nil))
      #+chestnut nil #-chestnut 0))) ;SS_G2L

(defun-void enqueue-read-event (icp-socket network-error-code)
  (unless (schedule-task-in-place-p (icp-socket-read-task icp-socket))
    (with-current-scheduling ((icp-socket-read-task icp-socket) 0
                              nil nil t)
      (handle-read-event-function icp-socket network-error-code nil))))

(defun-void clear-read-event (icp-socket)
  (cancel-task (icp-socket-read-task icp-socket)))

(def-structure-method handle-read-event (icp-socket network-error-code block-p)
  (cancel-task (icp-socket-read-task icp-socket))
  (if (eq 'localnet (type-of-icp-connection icp-socket))
      (handle-localnet-read icp-socket)
      (handle-network-read icp-socket network-error-code block-p)))


(defun-void enqueue-write-event (icp-socket network-error-code)
  (unless (schedule-task-in-place-p (icp-socket-write-task icp-socket))
    (with-current-scheduling ((icp-socket-write-task icp-socket) 0
                              nil nil t)
      (handle-write-event-function icp-socket network-error-code))))

(defun-void clear-write-event (icp-socket)
  (cancel-task (icp-socket-write-task icp-socket)))

(def-structure-method handle-write-event (icp-socket network-error-code)
  (cancel-task (icp-socket-write-task icp-socket))
  (if (eq 'localnet (type-of-icp-connection icp-socket))
      (handle-localnet-write icp-socket)
      (handle-network-write icp-socket network-error-code)))


(defun-void enqueue-close-event (icp-socket network-error-code)
  (unless (schedule-task-in-place-p (icp-socket-close-task icp-socket))
    (with-current-scheduling ((icp-socket-close-task icp-socket) 0
                              nil nil t)
      (handle-close-event icp-socket network-error-code))))

(defun-void clear-close-event (icp-socket)
  (cancel-task (icp-socket-close-task icp-socket)))

(defun-void handle-close-event (icp-socket network-error-code)
  (when icp-socket
    (cancel-task (icp-socket-close-task icp-socket))
    (if (eq 'localnet (type-of-icp-connection icp-socket))
        (handle-localnet-close icp-socket)
        (handle-network-close icp-socket network-error-code))))

(defun-void handle-display-event ()
  (current-system-case
    (ab
      (poll-native-window-workstation)
      (maybe-schedule-service-workstation nil t))
    (telewindows
      (poll-native-window-workstation)
      (when (scheduler-enabled-p)
        (run-scheduler-for-current-system)))))




;;;; function handle-network-read
;;   Called when bytes are available to be read on an active socket.
;;
;;   Contract: When we're here, we ought to read some bytes (at most one ICP bufferful)
;;           and then allow the message handling machinery to react.  The
;;           message handling machinery may attempt to finish reading the
;;           message group if it's not all here yet. We keep reading data until
;;           a message groups been handled by ICP, or our time slice runs out
;;           while accumulating a group, or the read stalls.
;;

(defvar during-ffi-call? nil)                ; when bound to t, forces read event handler to directly
                                        ; handle messages, rather than scheduling them.  sigh.

(defun-void continue-reading-from-icp-socket (icp-socket)
  (let ((icp-input-port (icp-input-port icp-socket)))
    (case (icp-port-blocked? icp-input-port)
      ((nil)
       (handle-read-event icp-socket network-status-success nil))
      (in-progress
       (setf (icp-port-blocked? icp-input-port) 'no-data-available))
      (in-progress-with-data
       (setf (icp-port-blocked? icp-input-port) nil)
       (handle-read-event icp-socket network-status-success t)))))

(defun-simple handle-network-read (icp-socket network-error-code block-p)
  (let ((socket-handle (icp-connection-handle (icp-input-port icp-socket)))
        (icp-input-port (icp-input-port icp-socket)))
    (unless (=f network-error-code network-status-success)
      (when (icp-error-on-socket icp-socket icp-read-event-error
                                 network-error-code (network-get-last-error-string socket-handle))
        (return-from handle-network-read nil)))
    (unless (socket-can-accept-input icp-socket)
      (when (icp-error-on-socket icp-socket icp-received-data-on-invalid-socket nil)
        (return-from handle-network-read nil)))
    (cond ((null block-p)
           (when (icp-port-blocked? icp-input-port)
             (setf (icp-port-blocked? icp-input-port) nil)
             (execute-icp-callbacks 'icp-read icp-socket t)))   ; !!! Maybe remove this line !!!
          (t
           (case (icp-port-blocked? icp-input-port)
             (in-progress
              (setf (icp-port-blocked? icp-input-port) 'in-progress-with-data)
              (return-from handle-network-read nil))
             (t ; initial no-data-available nil
              (setf (icp-port-blocked? icp-input-port) 'in-progress)))))
    (with-icp-buffer-coelescing-scope
      (loop as icp-buffer
               = (or (icp-buffer-for-callback icp-input-port)
                     (setf (icp-buffer-for-callback icp-input-port)
                           (make-icp-buffer)))
            as octets-read-or-status = (c-network-read
                                         socket-handle
                                         (icp-buffer-vector icp-buffer)
                                         (icp-buffer-end-byte icp-buffer)
                                         #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
            do
        (cond ((>f octets-read-or-status 0)
               (setf (icp-socket-saw-io? icp-socket) t)
               (incff (icp-buffer-end-byte icp-buffer) octets-read-or-status)
               (let ((end (icp-buffer-end-byte icp-buffer)))
                 (unless (and (=f 0 (logandf 1 end))
                              ;; The next line greatly improves debuggability of the
                              ;; recent ICP out of synch problems, and may increase
                              ;; performance, too.
                              (>f end
                                  #.(- (size-of-variable-fill-icp-buffers-in-8-bit-bytes) 64)))
                   (let ((copy (copy-icp-buffer icp-buffer)))
                     (setf (icp-buffer-start-byte copy) end)
                     (setf (icp-buffer-end-byte copy) end)
                     (setf (icp-buffer-next icp-buffer) copy))))
               (when (eq 'end-of-message-group
                         (enqueue-next-icp-buffer-if-any icp-input-port))
                 (unless (call-or-schedule-handle-queued-icp-messages icp-socket nil)
                   (return-from handle-network-read nil))
                 (when (icp-port-blocked? icp-input-port)
                   (setf (icp-port-blocked? icp-input-port) 'no-data-available)
                   (return-from handle-network-read nil))))

              ((=f octets-read-or-status ne-blocked-value)
               (setf (icp-port-blocked? icp-input-port) t)
               (execute-icp-callbacks 'icp-read icp-socket nil) ; !!! Maybe remove this line !!!
               (return-from handle-network-read nil))

              ((=f octets-read-or-status ne-eof-value)
               (handle-network-close icp-socket network-status-success)
               (return-from handle-network-read nil))

              ((=f octets-read-or-status ne-error-value)
               (when (icp-error-on-socket icp-socket
                                          icp-read-call-returned-error
                                          (c-network-get-last-error-code socket-handle)
                                          (network-get-last-error-string socket-handle))
                 (return-from handle-network-read nil))))))))

(defun-simple handle-localnet-read (icp-socket)
  (let ((icp-input-port (icp-input-port icp-socket)))
    (unless (socket-can-accept-input icp-socket)
      (when (icp-error-on-socket icp-socket icp-received-data-on-invalid-socket nil)
        (return-from handle-localnet-read nil)))
    (when (icp-port-blocked? icp-input-port)
      (setf (icp-port-blocked? icp-input-port) nil)
      (execute-icp-callbacks 'icp-read icp-socket t))
    (setf (icp-socket-saw-io? icp-socket) t)
    (with-icp-buffer-coelescing-scope
      (loop while (and (socket-can-accept-input icp-socket)
                       (icp-buffer-for-callback icp-input-port))
            for enqueue-result = (enqueue-next-icp-buffer-if-any icp-input-port)
            while (or (not (eq 'end-of-message-group enqueue-result))
                      (call-or-schedule-handle-queued-icp-messages icp-socket nil))))
    (unless (icp-buffer-for-callback icp-input-port)
      (setf (icp-port-blocked? icp-input-port) t))
    nil))



;;;; function handle-network-write
;;   called when writing became possible on the given socket.  this implies that it
;;    previously wasn't, i.e. that a write attempt stalled.
;;
;;   Contract: to attempt to write all the data queued for the given socket,
;;      terminating when we run out of time, buffers or the write stalls.
;;
;;    Implementation note for scheduler users: since write events are
;;    edge-triggered, if we terminate writing due to timeslice expiry, we must
;;    scedule an event (via our scheduler) at some future time to retry the
;;    write.  This is an asymmetry with respect to the read event handler above,
;;    but it's understandable given the assymetry in the handling of the
;;    underlying events.  Note that the event model described is based on the
;;    behaviour of the Winsock API, and by extension the WIN32 event scheme.
;;
;;
;;  note that as of 16 Apr 1996  this has not been tested.  -ncc

(defun-simple handle-network-write (icp-socket network-error-code)
  (let ((socket-handle (icp-connection-handle (icp-output-port icp-socket))))

    (unless (=f network-error-code network-status-success)
      (icp-error-on-socket icp-socket
                           icp-write-event-error
                           network-error-code
                           (network-get-last-error-string socket-handle))
      (return-from handle-network-write))

    (handle-icp-write icp-socket)))

(defun-simple handle-localnet-write (icp-socket)
  (handle-icp-write icp-socket))

(defun-simple handle-icp-write (icp-socket)
  (let ((icp-output-port (icp-output-port icp-socket)))

    (unless (icp-port-blocked? icp-output-port)
      (return-from handle-icp-write nil))

    (setf (icp-port-blocked? icp-output-port) nil)

    (loop with callbacks = (icp-callbacks 'icp-write icp-socket)
          do
      (transmit-icp-output-if-ready icp-output-port t)

      (when (or (icp-port-blocked? icp-output-port)
                (not (socket-can-perform-output icp-socket))
                (null callbacks))
        (when (null callbacks)
          (c-note-null-write-callbacks))
        (return-from handle-icp-write nil))

      (let ((callback-function (pop callbacks)))
        (funcall callback-function icp-socket t))

      (when (or (icp-port-blocked? icp-output-port)
                (not (socket-can-perform-output icp-socket)))
        (return-from handle-icp-write nil)))))


;; handle-network-connect
;;   called when a previous attempt to establish an outgoing connection finalizee
(def-structure-method handle-network-connect (icp-socket network-error-code)
  (let ((socket-handle (icp-connection-handle (icp-input-port icp-socket))))
    (unless (=f network-error-code network-status-success)
      (icp-error-on-socket icp-socket
                           icp-connect-event-error
                           network-error-code
                           (network-get-last-error-string socket-handle))
      (return-from handle-network-connect))

    (handle-icp-connect icp-socket)))

(defun-simple handle-icp-connect (icp-socket)
  (unless (=f (icp-connection-state icp-socket) icp-connection-connect-in-progress)
    (icp-error-on-socket icp-socket icp-connect-on-invalid-socket)
    (return-from handle-icp-connect))

  ;; change socket state to connected, call connection-completion callbacks for
  ;;   this socket if any, and return.
  (setf (icp-connection-state icp-socket) icp-connection-running)

  (send-initial-icp-version-info icp-socket t)

  ;; perform callbacks to ICP clients:
  (unless (=f (icp-connection-state icp-socket) icp-connection-closed)
    (execute-icp-callbacks 'icp-connect icp-socket)))

(defvar default-accept-timeout (*f fixnum-time-units-per-second 60 5)) ; 5 minutes

(def-structure-method handle-network-accept (icp-socket network-error-code)
  (let ((listener-handle (icp-connection-handle (icp-input-port icp-socket))))

    (unless (=f (icp-connection-state icp-socket) icp-socket-listening)
      (icp-error-on-socket icp-socket icp-accept-on-invalid-socket)
      (return-from handle-network-accept))

    (unless (=f network-error-code network-status-success)
      (icp-error-on-socket icp-socket
                           icp-accept-event-error
                           network-error-code
                           (network-get-last-error-string listener-handle))
      (return-from handle-network-accept))
    (let* ((new-socket-handle (c-network-accept listener-handle))
           new-socket)
      (cond ((>f new-socket-handle 0)
             (setf new-socket (make-and-install-network-icp-socket
                                new-socket-handle new-socket-handle
                                (get-accept-pathname new-socket-handle)
                                t
                                listener-handle
                                default-accept-timeout))

             ;; note that it's the contract of these guys to vet the incoming
             ;; connections and reject them if necessary. -ncc, 24 Jan 1996
             (execute-icp-callbacks 'icp-accept icp-socket new-socket))
            ;;Would block, ignore.
            ((=f new-socket-handle ne-blocked-value)
             (return-from handle-network-accept))
            (t
             (icp-error-on-socket icp-socket
                                  icp-accept-failure
                                  new-socket-handle
                                  (network-get-last-error-string listener-handle)))))))


(def-structure-method handle-network-close (icp-socket network-error-code)
  (unless (=f network-error-code network-status-success)
    (if (=f (icp-connection-state icp-socket) icp-connection-awaiting-acknowledgement)
        (icp-error-on-socket icp-socket icp-shutdown-aborted)
        (icp-error-on-socket icp-socket icp-connection-reset))
    (return-from handle-network-close))

  (handle-icp-close icp-socket))

(defun-simple handle-localnet-close (icp-socket)
  (handle-icp-close icp-socket))

(defun-simple handle-icp-close (icp-socket)
  (let ((icp-socket-connection-state (icp-connection-state icp-socket)))

    ;; if the socket was awaiting shutdown request acknowledgement, and the
    ;;   error-code is zero, then this indicates graceful closure.
    (unless (or (=f icp-socket-connection-state icp-connection-awaiting-acknowledgement)
                (eq 'localnet (type-of-icp-connection icp-socket)))
      (icp-error-on-socket icp-socket icp-connection-closed-error)
      (return-from handle-icp-close))

    ;; a clean shutdown.  This should cause the connection loss callbacks to be
    ;; called, then the socket should be finalized and reclaimed.
    (shutdown-icp-socket-connection icp-socket)))


(defun notify-sockets-of-g2-reset ()
  (loop for (handle . socket) in handle-to-socket-mapping
        when socket
        do (handle-g2-reset socket)))

(def-structure-method handle-g2-reset (icp-socket)
  (declare (ignore icp-socket))
  ;;;ignore
  )


;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INT2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Mark H. David, et al.



;;; Split from module INT by jh on 9/12/90.  (Previously, INT was called ICP.)
;;; INT2 contains the ICP buffer machinery.



;;; File name:		     INT2.LISP
;;; File location:	     ma:>ab>
;;; Code control:	     Zmacs on the Explorers.
;;; Purpose:		     ICP network I/O layer.
;;; Contents:                Machinery to manage ICP buffers, to implement secure
;;;                          network access, to service ICP sockets, to read and
;;;                          write individual ICP bytes, and an abstraction for
;;;                          writing an ICP message group.
;;; This file depends on:    Preceding .LISP files in the system load ordering.
;;; Dependent files:	     Subsequent .LISP files in the system load ordering.
;;; Role in products:	     Linked into G2 and Telewindows.
;;; Role in development:     None.
;;; Testing harness:         ICP message handling may be tested using 
;;;                          icp-message-trace-stream?.
;;; Performace requirements: These functions and macros are central to ICP 
;;;                          operation.  Performance is critical.
;;; Major Entities:	     [vector pool] variable-fill-icp-buffer
;;;                          [function]    make-listed-icp-buffer
;;;                          [function]    release-listed-icp-buffer
;;;                          [function]    receive-next-icp-buffer-listed-if-any
;;;                          [function]    service-icp-sockets-awaiting-callback
;;;                          [function]    item-remotely-visible-p
;;;                          [function]    item-remotely-modifiable-p
;;;                          [function]    all-remote-connections-restricted-p
;;;                          [function]    remote-inform-restricted-p
;;;                          [function]    check-for-pending-icp-requests
;;;                          [function]    check-for-pending-icp-output-requests
;;;                          [function]    transmit-icp-buffer
;;;                          [macro]       get-icp-byte
;;;                          [macro]       store-icp-byte
;;;                          [function]    receive-icp-input-if-ready
;;;                          [function]    process-icp-sockets
;;;                          [function]    icp-socket-needs-processing-p
;;;                          [function]    icp-port-needs-processing-p
;;;                          [function]    send-out-icp-buffer-if-any
;;;                          [function]    handle-icp-input-if-ready
;;;                          [function]    handle-icp-input-if-ready-managing-floats
;;;                          [function]    enqueue-next-icp-buffer-if-any
;;;                          [macro]       read-icp-byte-if-any
;;;                          [function]    process-next-icp-message-group-if-ready
;;;                          [defvar]      icp-message-trace-stream?
;;;                          [function]    handle-icp-messages
;;;                          [subst macro] write-icp-byte-macro
;;;                          [function]    write-icp-byte
;;;                          [subst macro] icp-connection-unclogged-for-socket?
;;;                          [macro]       writing-icp-message-group


;; Forward References in INT2

;; To INT3

(declare-forward-reference send-icp-message-group-id function)
(declare-forward-reference send-i-am-alive-if-necessary function)
(declare-forward-reference handling-solitary-I-am-alive? variable)
(declare-forward-reference ensure-remote-icp-version-info function)
(declare-forward-reference resume-icp-task-1 function)
(declare-forward-reference maybe-finish-current-icp-read-task function)
(declare-forward-reference current-icp-read-task-resumable-p function)
(declare-forward-reference kill-current-icp-read-task function)

(declare-forward-reference shutdown-icp-socket-connection function)
(declare-forward-reference flush-and-shutdown-icp-socket function)
(declare-forward-reference handle-icp-acknowledge-shutdown function)

;; To GSI

(declare-forward-reference signal-gsi-icp-message-too-long-error function)
(declare-forward-reference gsi-maybe-initiate-delayed-connection function)
(declare-forward-reference gsi-message function)
(declare-forward-reference gsi-warning function)

;; To G2-GSI

(declare-forward-reference update-gsi-interface-countdown-timer function)

;; To G2-RPC1

(declare-forward-reference remote-procedure-error function)


;; To SEQUENCES2

(declare-forward-reference saved-initial-status variable)



;; To VARIABLES, TELEWINDOWS, and GSI:

(declare-forward-reference g2-priority-of-data-service-function function)
(declare-forward-reference gsi-priority-of-data-service-function function)



;; To PANES

#+development
(declare-forward-reference update-pseudo-run-lights function)


;; To FILTERS

(declare-forward-reference network-access-allowed-p function) ;ncc 20 Jan 1994 

(declare-forward-reference notify-user function)

(declare-forward-reference give-icp-error-warning-message function)
(declare-forward-reference find-network-interface-for-icp-socket function)
(declare-forward-reference superblock?-function function)
(declare-forward-reference frame-has-been-reprocessed-p-function function)
(declare-forward-reference of-class-p-function function)

;; To TELESTUBS
(declare-forward-reference handle-unclogged-connection-if-necessary function)

;;; A positive integer, that specifies how many icp-buffers can be queued
;;; on writing, before writing is blocked.
(defparameter localnet-queued-icp-buffer-limit 3)


;;; Declaration:     receive-next-icp-buffer-listed-if-any (icp-input-port)
;;; Type:	     Lisp function.
;;; Purpose:         Get the next ICP buffer for an ICP input port.
;;; Arguments:	     An ICP input port.
;;; Return behavior: Returns the next listed ICP buffer that has arrived for icp-input-port,
;;;                  or nil if nothing has arrived.
;;; Users:	     ICP internals:
;;;                    INT2: enqueue-next-icp-buffer-if-any
;;; Prerequisites:   None.
;;; Side effects:    Replaces the newly-arrived listed ICP input buffer in
;;;                  icp-input-port with an empty one.
;;; Non-local exits: None.
;;; Memory impact:   Can generate a new listed ICP input buffer if there are no
;;;                  recycled ones available.

;;; Receive-next-icp-buffer-listed-if-any returns a one-element list with the
;;; next icp buffer, if any, that has arrived for icp-input-port.  If no such
;;; icp buffers are waiting to be received, nil is returned.

(defun receive-next-icp-buffer-if-any (icp-input-port)
  (let ((next-icp-buffer (icp-buffer-for-callback icp-input-port)))
    (when next-icp-buffer
      (case (type-of-icp-connection (parent-icp-socket icp-input-port))
	(localnet
	 (let* ((icp-socket (parent-icp-socket icp-input-port))
		(corresponding-icp-socket
		  (corresponding-localnet-socket icp-socket))
		(corresponding-icp-output-port
		  (when corresponding-icp-socket
		    (icp-output-port corresponding-icp-socket))))
	   (when (and corresponding-icp-output-port
		      (icp-port-blocked? corresponding-icp-output-port))
	     (enqueue-write-event corresponding-icp-socket 0))))
	(generic))
      (setf (icp-buffer-for-callback icp-input-port)
	    (icp-buffer-next next-icp-buffer))
      (setf (icp-buffer-next next-icp-buffer) nil)
      next-icp-buffer)))





(def-system-variable icp-socket-index INT2 0 nil t)


;; Added immediate shutdown for a socket request to a G2 which is prohibiting
;; remote access.  Such sockets are called listener sockets.  Also added delayed
;; shutdown of extant listener sockets.  Fractioned off the part of
;; check-for-pending-icp-requests which deals with sockets awaiting callback into
;; a separate function, service-icp-sockets-awaiting-callback.  jh, 1/30/91.

(defvar shutdown-interval-for-disallowed-icp-connection-in-seconds 10)
 
(defvar shutdown-interval-for-disallowed-icp-connection
	(fixnum-time-interval 
	  (*f 1000 
	      shutdown-interval-for-disallowed-icp-connection-in-seconds)))

(defvar negative-shutdown-interval-for-disallowed-icp-connection
	(-f shutdown-interval-for-disallowed-icp-connection))

(def-system-variable refused-icp-listener-connections INT2 nil)





;;;; Remote access functions

;;; These function allow the G2 user control over how remote processes access
;;; entities in the KB.

;;; Declaration:     item-remotely-callable-p (item)
;;; Type:            lisp function.
;;; Purpose:         determine if a remote G2 may call this procedure.
;;;                  
;;; Arguments:       item, an item.
;;; Return behavior: returns t iff item (which is assumed to be a procedure object
;;;                   although this is not checked) allows the execute network
;;;                   access mode. 
;;; Users:           remote-procedure-call-authorized (G2-RPC1).
;;; Prerequisites:   item is an item which happens to be a procedure object.
;;; Side effects:    none.
;;; Non-local exits: none.
;;; Memory impact:   none.
;;; Notes:           none
;;;                  
(defun item-remotely-callable-p (item)
  (network-access-allowed-p 'g2 'execute item))


;;; Declaration:     item-remotely-visible-p (item)
;;; Type:	     Lisp function.
;;; Purpose:	     Determine if a remote G2 may see this item.
;;; Arguments:	     An item.
;;; Return behavior: Returns non-nil if item may be seen, nil otherwise.
;;; Users:           G2 user restrictions (ROLES, EVAL, NEW-RULES, G2-RPC1,
;;;                  G2-RPC2, G2DS).	
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           See code in filters.lisp for implementation of
;;;                  network-access-allowed-p.  -ncc 20 Jan 1994 

(defun-simple item-remotely-visible-p (item)
  (declare eliminate-for-gsi)
  (network-access-allowed-p 'g2 'read item))




;;; Declaration:     item-remotely-modifiable-p (item)
;;; Type:	     Lisp function.
;;; Purpose:         Determine if a remote G2 may side-effect this item.
;;; Arguments:	     An item.
;;; Return behavior: Returns non-nil if item may be modified, nil otherwise.
;;; Users:	     G2 user restrictions (ROLES, EVAL, NEW-RULES, G2DS).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           See code in filters.lisp for implementation of
;;;                  network-access-allowed-p.  -ncc 20 Jan 1994 

(defun-simple item-remotely-modifiable-p (item)
  (declare eliminate-for-gsi)
  (network-access-allowed-p 'g2 'write item))



;;; Declaration:     all-remote-connections-restricted-p ()
;;; Type:	     Lisp function.
;;; Purpose:	     Determine if a remote process may connect to this G2.
;;; Arguments:	     None.
;;; Return behavior: Returns nil if remote connections to this G2 are allowed,
;;;                  non-nil otherwise.  Returns nil if this is not a G2,
;;;                  e.g., if this is a Telewindows.
;;; Users:           G2 user restrictions (check-for-pending-icp-requests in INT2).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           The kb-restrictions table is searched without recourse to the
;;;                   part hierarchy (see network-access-allowed-p in filters.lisp)
;;;                  ncc 19 Jan 1994
;;;
;;;                  Updated to be callable from Telewindows, although its behavior
;;;                    is not very meaningful.
;;;                  MHD 5/18/94

(defun-simple all-remote-connections-restricted-p ()
  (and (eq current-system-name 'ab)
       (not (network-access-allowed-p 'g2 'connect))
       (not (network-access-allowed-p 'telewindows 'connect))))

(defun-simple get-forbidden-listener-clients-if-any ()
  (and (eq current-system-name 'ab)
       (let ((forbidden-listener-clients? nil))
	 (unless (network-access-allowed-p 'g2 'connect)
	   (icp-push 'g2 forbidden-listener-clients?))
	 (unless (network-access-allowed-p 'telewindows 'connect)
	   (icp-push 'telewindows forbidden-listener-clients?))
	 forbidden-listener-clients?)))






;;; Declaration:     remote-inform-restricted-p ()
;;; Type:	     Lisp function.
;;; Purpose:	     Determine if a remote G2 may post messages onto this G2.
;;; Arguments:	     None.
;;; Return behavior: Returns nil if remote messages may appear on this G2, non-nil
;;;                  otherwise.
;;; Users:	     G2 user restrictions (G2DS).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           The kb-restrictions table is searched without recourse to the
;;;                   part hierarchy (see network-access-allowed-p in filters.lisp)
;;;                  (ncc 19 Jan 1994)

(defun remote-inform-restricted-p ()
  (not (network-access-allowed-p 'g2 'inform)))



;;; Number-of-icp-bytes-in-buffer returns the icp byte count of
;;; icp-buffer, which must be an integer greater than 0.  This operation is
;;; assumed to be fast.

(def-substitution-macro number-of-icp-bytes-in-buffer (icp-buffer)
  (-f (icp-buffer-end-icp-byte icp-buffer) (icp-buffer-start-icp-byte icp-buffer)))

(def-substitution-macro number-of-bytes-in-buffer (icp-buffer)
  (-f (icp-buffer-end-byte icp-buffer) (icp-buffer-start-byte icp-buffer)))



;;; Declaration:     get-icp-byte (icp-buffer icp-byte-position)
;;; Type:	     Lisp macro.
;;; Purpose:	     Get an ICP byte from an ICP buffer quickly.
;;; Arguments:       A non-listed ICP buffer and a fixnum representing its position.
;;; Return behavior: An ICP byte as a 16-bit integer.
;;; Users:	     ICP internals:
;;;                    INT2: enqueue-next-icp-buffer-if-any
;;;                          read-icp-byte-if-any
;;;                          advance-and-read-icp-byte-if-any
;;;                  ICP testing:
;;;                    INT3: dump-icp-buffer
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: No bounds check, so can cause a segmentation or bus error.
;;; Memory impact:   None.

;;; Get-icp-byte returns the icp byte at position icp-byte-position of
;;; icp-buffer.  It is assumed that there is such a byte.

;;; Note that icp bytes, which are 16 bits, are currently stored in icp byte
;;; arrays with 8 bits per element. This entails the classic byte ordering, or
;;; "endianness", problem.  In ICP byte arrays, we store ICP bytes in BIG-ENDIAN
;;; order.  This is the "network byte order" for ICP. 

(defmacro icp-byte-aref (icp-byte-array icp-byte-position)
  (let ((array (make-symbol "ARRAY"))
	(icp-position (make-symbol "ICP-POSITION"))
	(position (make-symbol "POSITION")))
    `(let* ((,array ,icp-byte-array)
	    (,icp-position ,icp-byte-position)
	    (,position (+f ,icp-position ,icp-position)))
       (declare (type fixnum ,icp-position ,position))
       (+f (ashf (byte-vector-aref ,array ,position) 8)
	   (byte-vector-aref ,array (1+f ,position))))))

(defmacro icp-byte-aset (icp-byte-array icp-byte-position new-value)
  (let ((array (make-symbol "ARRAY"))
	(icp-position (make-symbol "ICP-POSITION"))
	(position (make-symbol "POSITION"))
	(value (make-symbol "VALUE")))
    `(let* ((,array ,icp-byte-array)
	    (,icp-position ,icp-byte-position)
	    (,position (+f ,icp-position ,icp-position))
	    (,value ,new-value))
       (declare (type fixnum ,icp-position ,position ,value))
       (setf (byte-vector-aref ,array ,position) (ashf ,value -8))
       (setf (byte-vector-aref ,array (1+f ,position)) (logandf #xff ,value))
       ,value)))

(defsetf icp-byte-aref icp-byte-aset)

(defmacro get-icp-byte (icp-buffer icp-byte-position)
  `(icp-byte-aref (icp-buffer-vector ,icp-buffer) ,icp-byte-position))

(defmacro icp-buffer-start-icp-byte (buffer)
  `(ashf (icp-buffer-start-byte ,buffer) -1))

(defmacro set-icp-buffer-start-icp-byte (buffer new-value)
  `(setf (icp-buffer-start-byte ,buffer) (ashf ,new-value 1)))

(defsetf icp-buffer-start-icp-byte set-icp-buffer-start-icp-byte)

(defmacro icp-buffer-end-icp-byte (buffer)
  `(ashf (icp-buffer-end-byte ,buffer) -1))

(defmacro set-icp-buffer-end-icp-byte (buffer new-value)
  `(setf (icp-buffer-end-byte ,buffer) (ashf ,new-value 1)))

(defsetf icp-buffer-end-icp-byte set-icp-buffer-end-icp-byte)

(defun print-icp-buffer-contents (buffer)
  (loop with n fixnum = 16
	with bv = (icp-buffer-vector buffer)
	with start = (icp-buffer-start-icp-byte buffer)
	with end = (icp-buffer-end-icp-byte buffer)
	with count = (-f end start)
	for i from 0 below count by n
	do
    (terpri)
    (loop for j from i below (minf count (+f i n))
	  do (format t " ~D" (icp-byte-aref bv (+f j start)))))
  (terpri))

(defun print-icp-buffer-byte-contents (buffer)
  (loop with n fixnum = 16
	with bv = (icp-buffer-vector buffer)
	with start = (icp-buffer-start-byte buffer)
	with end = (icp-buffer-end-byte buffer)
	with count = (-f end start)
	for i from 0 below count by n
	do
    (terpri)
    (loop for j from i below (minf count (+f i n))
	  do (format t " ~D" (byte-vector-aref bv (+f j start)))))
  (terpri))



;; It would presumably be redundant to declare the second arg of an aref to be a
;; fixnum.



;;; Declaration:     store-icp-byte (icp-buffer icp-byte-position icp-byte)
;;; Type:	     Lisp macro.
;;; Purpose:	     Place an ICP byte into an ICP buffer quickly.
;;; Arguments:       A non-listed ICP buffer, a fixnum representing its position,
;;;                  and an ICP byte as a 16-bit integer.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals:
;;;                    INT2: write-icp-byte-macro
;;;                          write-icp-byte-into-new-buffer
;;;                          end-icp-message-series-if-any
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: No bounds check, so can cause a segmentation or bus error.
;;; Memory impact:   None.

;;; Store-icp-byte stores icp-byte at position icp-byte-position of icp-buffer.

(defmacro store-icp-byte (icp-buffer icp-byte-position icp-byte)
  `(setf (icp-byte-aref (icp-buffer-vector ,icp-buffer) ,icp-byte-position)
	 ,icp-byte))





;;;; ICP Reception





;; reset-counters-for-all-icp-sockets is used only in gsi.lisp, as far as I can
;; tell.  -ncc, 19 Aug 1996

;; XXX revisit this before beta. -ncc, 29 Oct 1996 

(defmacro reset-counters-for-icp-socket (icp-socket)
  `(setf (icp-socket-saw-io? ,icp-socket) nil))

(defun-void reset-counters-for-all-icp-sockets ()
  (loop for icp-socket in active-icp-sockets
	do (reset-counters-for-icp-socket icp-socket)))


(declare-forward-reference replace-format-using-equivalent-font function)

(declare-forward-reference saved-initial-status variable)

(defun restore-icp-index-to-original-state ()
  (cond ((eq current-system-name 'telewindows)
	 nil) ; noop
	((eq current-system-name 'gsi)
	 nil)
	((=f icp-socket-index 1000)
	 (setq icp-socket-index 0)
	 (if (fourth (svref saved-initial-status 1))
	     (replace-format-using-equivalent-font :fnord))) ; ignored argument.
	(t (incff icp-socket-index))))

;; Removed internal special declaration of saved-initial-status inside
;; restore-icp-index-to-original-state and changed it to a forward reference
;; declaration.  This variable is global, so this change will preserve the
;; semantics.  Anyway, using internal special declarations to pass private
;; variables is denigrated, and in fact will not work in Chestnut.  jh, 2/21/91.



;;;; ICP Transmission



;;; ICP output is sent out through an ICP port.  More specifically, ICP output
;;; is generated by an ICP writer and passes via the ICP buffer in the port to
;;; an ICP transmitter, which does the sending.  An ICP transmitter may be a
;;; subfunction, a scheduled G2 task, or a separate Lisp process.

;;; All-icp-buffers-transmitted? checks to see if all icp buffers queued
;;; for transmission on an icp socket have been sent.
;;;
;;; comments added by ncc, 27 Mar 1995:
;;;  note that this does not take into account the awaiting-callback? mechanism
;;;  whereby data that's been handed to the network layer but not accepted by
;;;  the transport layer is buffered in the network layer.  

(def-substitution-macro all-icp-buffers-transmitted? (icp-output-port)
  (and (eq (icp-buffer-queue-head icp-output-port)
	   (icp-buffer-queue-tail icp-output-port))))

;;; all-icp-input-buffers-received-and-processed? checks to see if all icp
;;; buffers queued for input have been received and processed.

(def-substitution-macro all-icp-input-buffers-received-and-processed? (icp-input-port)
  (eq (icp-buffer-queue-head icp-input-port)
      (icp-buffer-queue-tail icp-input-port)))


(defun icp-output-port-flushed? (icp-output-port)
  (and (all-icp-buffers-transmitted? icp-output-port)
       (not (icp-port-blocked? icp-output-port))))



(defvar inhibit-icp-message-processing-enabled t)
(defvar inhibit-icp-message-processing nil) ; for gsi-flush-internal-1
(defvar icp-sockets-waiting-for-icp-message-processing nil)

(defun-void schedule-processing-for-inhibited-messages ()
  (when icp-sockets-waiting-for-icp-message-processing
    (unless inhibit-icp-message-processing
      (setq icp-sockets-waiting-for-icp-message-processing
	    (nreverse icp-sockets-waiting-for-icp-message-processing))
      (with-icp-buffer-coelescing-scope
        (loop while icp-sockets-waiting-for-icp-message-processing
	      for icp-socket = (gensym-pop icp-sockets-waiting-for-icp-message-processing)
	      when icp-socket
		do (call-or-schedule-handle-queued-icp-messages icp-socket t))))))

(defmacro with-inhibited-icp-message-processing (&body forms) ; for gsi-flush-internal-1
  `(let ((inhibit-icp-message-processing
	   inhibit-icp-message-processing-enabled))
     (prog1 (progn ,@forms)
       (schedule-processing-for-inhibited-messages))))

(defun-simple icp-socket-is-for-ui-client-interface-p (icp-socket)
  (current-system-case
    (ab
      (let ((interface? (enclosing-interface-frame? icp-socket)))
	(and (of-class-p-function interface? 'ui-client-interface)
	     (not (frame-has-been-reprocessed-p-function
		    interface?
		    (enclosing-interface-frame-serial-number icp-socket))))))
    (t icp-socket
       nil)))

(defvar handle-ui-client-interface-messages-immediately-p nil)

(defun-allowing-unwind call-or-schedule-handle-queued-icp-messages (icp-socket force-schedule-p)
  (declare (ignore force-schedule-p))
  (cond (inhibit-icp-message-processing
	 (unless (memq icp-socket icp-sockets-waiting-for-icp-message-processing)
	   (gensym-push icp-socket icp-sockets-waiting-for-icp-message-processing))
	 nil)
	((or (eq (icp-socket-listener-client? icp-socket) 'telewindows)
	     (and handle-ui-client-interface-messages-immediately-p
		  (or (null (icp-socket-listener-client? icp-socket))
		      (icp-socket-is-for-ui-client-interface-p icp-socket)))
	     during-ffi-call?)
	 (let ((more-to-do-immediately?
		 (catch 'handle-icp-messages
		   (let ((abort-for-icp-catcher? 'handle-icp-messages))
		     (handle-queued-icp-messages icp-socket)))))
	   (cond ((=f (icp-connection-state icp-socket) icp-connection-closed)
		  (finalize-and-reclaim-icp-socket icp-socket)
		  nil)
		 (t
		  more-to-do-immediately?))))
	(t
	 (with-future-scheduling
	     ((icp-message-handler-future-task? icp-socket)
	      highest-system-priority
	      (+e (if (icp-socket-is-for-ui-client-interface-p icp-socket) 0.100 0.200)
		  (managed-float-value (clock-get current-real-time)))
	      nil nil t)
	   (handle-queued-icp-messages-task icp-socket))
	 (with-current-scheduling
	     ((icp-message-handler-current-task? icp-socket)
	      lowest-system-priority
	      nil nil t)
	   (handle-queued-icp-messages-task icp-socket))
	 nil)))

(defun-void handle-queued-icp-messages-task (icp-socket)
  (with-temporary-profiling-context icp
    (with-icp-buffer-coelescing-scope
      (when (handle-queued-icp-messages icp-socket)
	(continue-reading-from-icp-socket icp-socket)))))

;;; GENSYMCID-1215: twng locking up (Part III)
;;; If TWNG is really "clogged", setting breakpoint here we should see something.

(defun-allowing-unwind handle-queued-icp-messages (icp-socket)
  (cancel-task (icp-message-handler-future-task? icp-socket))
  (cancel-task (icp-message-handler-current-task? icp-socket))
  (when inhibit-icp-message-processing
    (unless (memq icp-socket icp-sockets-waiting-for-icp-message-processing)
      (gensym-push icp-socket icp-sockets-waiting-for-icp-message-processing))
    (return-from handle-queued-icp-messages nil))
  #+development
  (update-pseudo-run-lights :icp-message-task)
  (setq icp-socket-for-handle-icp-messages icp-socket)
  (let ((more-to-do-immediately? nil)
	(abort-for-icp-catcher? 'handle-icp-messages))
    (loop with icp-input-port = (icp-input-port icp-socket)
	  for did-something? = (process-next-icp-message-group-if-ready icp-input-port)
	  as time-slice-expired? = (and (not during-ffi-call?) (time-slice-expired-p))
	  as can-process-messages? = (icp-connection-can-process-messages? icp-socket)
	  until (or time-slice-expired?
		    (not did-something?)
		    (not can-process-messages?))
	  finally
	    (when can-process-messages?
	      (setq more-to-do-immediately?
		    (if did-something?
			(call-or-schedule-handle-queued-icp-messages icp-socket t)
			t))))
    (when (=f (icp-connection-state icp-socket) icp-connection-closed)
      (finalize-and-reclaim-icp-socket icp-socket))
    more-to-do-immediately?))





;;; Declaration:     transmit-icp-buffer (icp-buffer icp-output-port)
;;; Type:	     Lisp function.
;;; Purpose:         Send an ICP buffer over the network.
;;; Arguments:	     A (non-listed) ICP buffer and an ICP output port.
;;; Return behavior: No useful value.
;;; Users:           ICP internals (send-out-icp-buffer-if-any and
;;;                  service-icp-sockets-awaiting-callback in INT2).
;;; Prerequisites:   None.
;;; Side effects:    Writes the contents of icp-buffer (its car) out onto the
;;;                  network, changes the count of the number of characters
;;;                  remaining to write from icp-buffer (its cdr).  Shuts down the
;;;                  ICP connection containing icp-output-port if there is an error
;;;                  during write.  Can place a (non-listed) buffer in the
;;;                  listed-icp-buffer-for-callback slot of icp-output-port if the
;;;                  write fails in a non-fatal way and needs to be retried.
;;; Non-local exits: None, but note that as a side effect, this function can shut
;;;                  down an ICP connection, causing a non-local exit higher up.
;;; Memory impact:   Affects internal network buffers of the operating system.  

;;; Transmit-icp-buffer transmits icp-buffer from icp-output-port.  This assumes that
;;; icp-buffer remains unchanged until the NEXT icp buffer is transmitted through
;;; icp-output-port.

(defun-simple transmit-next-network-icp-buffer (icp-output-port)
  (let* ((icp-socket (parent-icp-socket icp-output-port))
	 (icp-buffer-queue-head (icp-buffer-queue-head icp-output-port))
	 (icp-buffer (icp-buffer-next icp-buffer-queue-head))
	 (character-to-start-at (icp-buffer-start-byte icp-buffer))
	 (characters-to-send (-f (icp-buffer-end-byte icp-buffer)
				 character-to-start-at))
	 (characters-sent
	   (c-network-write
	     (icp-connection-handle icp-output-port)
	     (icp-buffer-vector icp-buffer)
	     character-to-start-at
	     characters-to-send)))
    (cond ((=f characters-sent characters-to-send)
	   (reclaim-icp-buffer icp-buffer-queue-head)
	   (setf (icp-buffer-queue-head icp-output-port) icp-buffer)
	   t)

	  ;; realpolitik: should partial writes be treated as blocked writes?
	  ;; I think from a practical standpoint the answer is yes.  -ncc, 24 Apr 1996
	  ((>=f characters-sent 0)
	   (setf (icp-port-blocked? icp-output-port) t)
	   (execute-icp-callbacks 'icp-write icp-socket nil)
	   (setf (icp-buffer-start-byte icp-buffer)
		 (+f character-to-start-at characters-sent))
	   (setf (icp-buffer-for-callback icp-output-port) icp-buffer)
	   nil)

	  (t ; Else, characters-sent must be negative, i.e. an error.
	   (shutdown-icp-socket-connection
	     (parent-icp-socket icp-output-port)
	     'broken-while-transmitting)
	   nil))))

(defun-simple transmit-next-localnet-icp-buffer (icp-output-port)
  (let* ((icp-socket (parent-icp-socket icp-output-port))
	 (icp-buffer-queue-head (icp-buffer-queue-head icp-output-port))
	 (icp-buffer (icp-buffer-next icp-buffer-queue-head))
	 (corresponding-icp-socket (corresponding-localnet-socket icp-socket))
	 (corresponding-icp-input-port (icp-input-port corresponding-icp-socket))
	 (buffer-chain-copy (copy-icp-buffer-chain icp-buffer))
	 (buffer-for-callback (icp-buffer-for-callback corresponding-icp-input-port)))
    (if (null buffer-for-callback)
	(setf (icp-buffer-for-callback corresponding-icp-input-port) buffer-chain-copy)
	(loop for last-buffer = buffer-for-callback then next-buffer
	      for next-buffer = (icp-buffer-next last-buffer)
	      while next-buffer
	      finally (setf (icp-buffer-next last-buffer) buffer-chain-copy)))
    (loop for last-buffer = icp-buffer then next-buffer
	  while last-buffer
	  for next-buffer = (icp-buffer-next last-buffer)
	  do (reclaim-icp-buffer icp-buffer-queue-head)
	     (setq icp-buffer-queue-head last-buffer))
    (setf (icp-buffer-queue-head icp-output-port) icp-buffer-queue-head)
    (when (icp-port-blocked? corresponding-icp-input-port)
      (enqueue-read-event corresponding-icp-socket 0))
    t))

(defun transmit-icp-output-if-ready (icp-output-port flush-partial-buffers)
  (let* ((icp-socket (parent-icp-socket icp-output-port))
	 (type-of-icp-connection (type-of-icp-connection icp-socket))
	 (localnetp (eq type-of-icp-connection 'localnet)))
    (when (and localnetp
	       (null (corresponding-localnet-socket icp-socket)))
      (unless (=f (icp-connection-state icp-socket) icp-connection-closed)
	(shutdown-icp-socket-connection icp-socket 'broken-while-transmitting))
      (return-from transmit-icp-output-if-ready nil))
    (when (and (socket-can-perform-output icp-socket)
	       (not (icp-port-blocked? icp-output-port)))		   
      (loop with tail = (icp-buffer-queue-tail icp-output-port)
	    for head = (icp-buffer-queue-head icp-output-port)
	    until (or (eq head tail)
		      (and (not flush-partial-buffers)
			   (eq (icp-buffer-next head) tail)
			   (<f (icp-buffer-end-byte tail)
			       (size-of-variable-fill-icp-buffers-in-8-bit-bytes))))
	    while (if localnetp
		      (transmit-next-localnet-icp-buffer icp-output-port)
		      (transmit-next-network-icp-buffer icp-output-port))))))


;;; Declaration:     send-out-icp-buffer-if-any (icp-output-port)
;;; Type:	     Lisp function.
;;; Purpose:	     Send a single ICP buffer over the network.
;;; Arguments:       An ICP output port.  This function is to be invoked by the ICP
;;;                  transmitter periodically or when an ICP buffer for
;;;                  icp-output-port is known to be ready to be sent out.
;;; Return behavior: This function attempts to send out at most one ICP buffer, even
;;;                  if several are ready to go, and returns non-nil if it was
;;;                  successful.  If no buffer was ready to go or icp-output-port is
;;;                  awaiting a callback, this function returns nil.
;;; Users:	     ICP internals:
;;;                    INT2: process-icp-sockets
;;;                          transmit-icp-output-if-ready
;;; Prerequisites:	 None.
;;; Side effects:    Fills internal network buffers of the operating system.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims a listed ICP buffer if successfully sent.
;;; Notes:           Note that the ICP transmitter that invokes this function may
;;;                  run in a process separate from the ICP writer with which it is
;;;                  paired.

;;; Send-out-icp-buffer-if-any is to be invoked by the ICP transmitter
;;; periodically or when an icp buffer for icp-output-port is known to be ready
;;; to be sent out.  This sends out at most one buffer, and returns t, even if
;;; several are ready to go; if no buffer is ready to go or icp-output-port is
;;; awaiting a callback, it returns nil.  Note also that the ICP transmitter
;;; that invokes this may run in a process separate from the ICP writer with
;;; which it is paired.



;; Have some sort of time-out if a callback could ever fail to happen.

;; Note that this releases (for recycling) the previous icp buffer in the queue
;; just before it transmits one.

;;;; ICP Reading (Handling)



;;; ...  One should not begin reading a message until the whole message is in
;;; the input buffer, since one cannot tolerate waiting while handling a
;;; message.
;;; Declaration:     enqueue-next-icp-buffer-if-any (icp-input-port)
;;; Type:	     Lisp function.
;;; Purpose:	     Receive a buffer for an ICP input port.
;;; Arguments:       An ICP input port.  This function is to be invoked by the ICP
;;;                  receiver periodically or when an ICP buffer for icp-input-port
;;;                  is known to have arrived.
;;; Return behavior: This function returns non-nil only if it receives and enqueues
;;;                  an ICP buffer.  It returns the symbol end-of-message-group when
;;;                  the buffer it receives and enqueues contains an end of a
;;;                  message group.  If it enqueues an ICP buffer without an end of
;;;                  message group, this function returns some other unspecified but
;;;                  non-nil value.  If it does not receive an ICP buffer, this
;;;                  function returns nil.
;;; Users:	     ICP internals (receive-icp-input-if-ready in INT2).
;;; Prerequisites:   None.
;;; Side effects:    Can release an ICP buffer.
;;; Non-local exits: Shuts down the ICP socket for protocol-out-of-sync-1 and
;;;                  protocol-out-of-sync-1 conditions.  See the doc for the
;;;                  icp-socket structure in INT1 for details.
;;; Memory impact:   Can release an ICP buffer.
;;; Notes:           Note that the ICP receiver that invokes this may run in a
;;;                  process separate from the ICP handler with which it is paired.

;;; Enqueue-next-icp-buffer-if-any is to be invoked by the ICP receiver
;;; periodically or when an icp buffer for icp-input-port is known to have
;;; arrived.  This returns non-nil only if it receives and enqueues an icp
;;; buffer.  It returns the symbol END-OF-MESSAGE-GROUP when it receives and
;;; enqueues an icp buffer containing an end of a message group.  Note that the
;;; ICP receiver that invokes this may run in a process separate from the ICP
;;; handler with which it is paired.

(defun-simple enqueue-next-icp-buffer-if-any (icp-input-port)
  (let ((icp-buffer? (receive-next-icp-buffer-if-any icp-input-port))
	(icp-buffer-start-icp-offset 0))
    (when icp-buffer?
      (let ((tail (icp-buffer-queue-tail icp-input-port)))
	(cond ((eq (icp-buffer-vector tail) (icp-buffer-vector icp-buffer?))
	       (when (eq (icp-buffer-queue-head icp-input-port) tail)
		 (incff (number-of-icp-bytes-left-in-current-buffer icp-input-port)
			(number-of-icp-bytes-in-buffer icp-buffer?)))
	       (setq icp-buffer-start-icp-offset
		     (-f (icp-buffer-start-icp-byte icp-buffer?)
			 (icp-buffer-start-icp-byte tail)))
	       (setf (icp-buffer-end-byte tail) (icp-buffer-end-byte icp-buffer?))
	       (reclaim-icp-buffer icp-buffer?)
	       (setq icp-buffer? tail))
	      (t
	       (setf (icp-buffer-next tail) icp-buffer?)
	       (setf (icp-buffer-queue-tail icp-input-port) icp-buffer?))))
      (current-system-case
	((ab telewindows)
	 (let* ((icp-socket (parent-icp-socket icp-input-port))
		(I-am-alive-info? (I-am-alive-info? icp-socket)))
	   (when I-am-alive-info?
	     (incff (number-of-icp-bytes-handled-since-last-I-am-alive-was-sent I-am-alive-info?)
		    (-f (number-of-icp-bytes-in-buffer icp-buffer?)
			icp-buffer-start-icp-offset))
	     (send-I-am-alive-if-necessary icp-socket I-am-alive-info?)))))
      (current-system-case
	(ab (update-gsi-interface-countdown-timer (parent-icp-socket icp-input-port))))
      (loop with contains-end-of-message-group? = nil
	    as number-of-icp-bytes-left-in-buffer
	       = (-f (number-of-icp-bytes-in-buffer icp-buffer?)
		     icp-buffer-start-icp-offset)
	       then (-f number-of-icp-bytes-left-in-buffer
			number-of-icp-bytes-still-needed-for-message-series)
	    as number-of-icp-bytes-still-needed-for-message-series
	       = (number-of-icp-bytes-still-needed-for-message-series icp-input-port)
	       then (let ((message-series-byte-count
 			    (get-icp-byte icp-buffer? index-of-icp-byte-position)))
		      (cond
			((=f message-series-byte-count 1)
			 (setq contains-end-of-message-group? t)
			 (setf (icp-buffer-with-end-of-message-group? icp-input-port)
			       icp-buffer?)
			 (setf (icp-byte-index-of-end-of-message-group? icp-input-port)
			       index-of-icp-byte-position))
			((=f message-series-byte-count 0)
			 (let ((current-icp-port icp-input-port))
			   (icp-out-of-synch 1))))
		      message-series-byte-count)
	    as index-of-icp-byte-position
	       = (+f number-of-icp-bytes-still-needed-for-message-series
		     (icp-buffer-start-icp-byte icp-buffer?)
		     icp-buffer-start-icp-offset)
	       then (+f index-of-icp-byte-position
			number-of-icp-bytes-still-needed-for-message-series)
	    while (<f number-of-icp-bytes-still-needed-for-message-series
		      number-of-icp-bytes-left-in-buffer)
	    finally
	      (setf (number-of-icp-bytes-still-needed-for-message-series icp-input-port)
		    (-f number-of-icp-bytes-still-needed-for-message-series
			number-of-icp-bytes-left-in-buffer))
	      (return
		(if contains-end-of-message-group?
		    'end-of-message-group
		    t))))))


(defvar priority-of-icp-message-service 3) ; XXX this is an arbitrary choice-- 
                                           ; priority-of-data-service didn't seem like
                                           ; the right thing. -ncc, 14 Apr 1996
(defvar priority-of-rpc-service 6)
(defvar priority-of-icp-control-messages 7)
(defvar resumable-priority-of-gsi-data-service 4)
(defvar resumable-priority-of-gsi-rpc-service 6)


(def-system-variable number-of-icp-bytes-left-in-message-series INT2 nil)

(def-system-variable current-icp-buffer INT2 nil)

(def-system-variable number-of-icp-bytes-ready-to-read INT2 nil)


;; definition moved to network-event-handlers.lisp
;;(def-system-variable current-icp-byte-position INT2 nil)

(def-system-variable current-read-icp-byte-position INT2 nil)
(def-system-variable current-write-icp-byte-position INT2 nil)

(defvar writing-resumable-icp-messages-p nil)
(defvar icp-error-suspend-p nil)

(defvar current-resumable-icp-read-task nil)
(defvar resumable-icp-read-ignore-p nil)




;;; Declaration:     read-icp-byte-if-any (ok-if-none?)
;;; Type:	     Lisp macro.
;;; Purpose:	     Read an ICP byte.
;;; Arguments:       ok-if-none?  is nil if a read error should shut down the ICP
;;;                  connection.
;;; Return behavior: If ok-if-none?  is nil, this function will shut down the ICP
;;;                  connection upon encountering a read error.  Otherwise, it will
;;;                  return normally.
;;; Users:           ICP internals:
;;;                    INT2: handle-icp-messages 
;;;                    INT3: def-icp-value-reader forms for public ICP value types
;;;                  Also GSI (GSI-COMMON), Telewindows and G2 printing (TELESTUBS),
;;;                  G2 remote procedures (G2-RPC and G2-RPC2), G2 foreign functions
;;;                  (G2-FOREIGN), G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    current-icp-socket has now read this ICP byte.  If an error
;;;                  occurs, this function can shut down this ICP connection.
;;; Non-local exits: If ok-if-none?  is nil, and an error occurs while reading, this
;;;                  function will shut down the ICP connection and call abort,
;;;                  which throws to the nearest abort tag.  A "case 4" error
;;;                  happens when this function gets nil when it expects an ICP
;;;                  buffer.  A "case 5" error happens when an ICP message group
;;;                  terminates unexpectedly.
;;; Memory impact:   Releases the previous ICP buffer in current-icp-socket if that
;;;                  buffer contained nothing left to read.

;;; Read-icp-byte-if-any ... returns nil at the end of an icp message group
;;; (provided ok-if-none? is non-nil).

(defvar number-of-icp-bytes-left-in-current-buffer)

(defmacro at-end-of-message-group-p (&optional current-position+1)
  `(=f 1 (icp-byte-aref (icp-buffer-vector current-icp-buffer)
			,(or current-position+1
			     `(1+f current-read-icp-byte-position)))))

(defmacro update-icp-read-buffer (number-of-bytes-actually-read &optional current-position+1 number-ready)
  `(progn
     ,(if current-position+1
	  `(setq current-read-icp-byte-position (+f (1-f ,current-position+1) ,number-of-bytes-actually-read))
	  `(incff current-read-icp-byte-position ,number-of-bytes-actually-read))
     ,(if number-ready
	  `(setq number-of-icp-bytes-ready-to-read (-f ,number-ready ,number-of-bytes-actually-read))
	  `(decff number-of-icp-bytes-ready-to-read ,number-of-bytes-actually-read))))

(defmacro with-icp-read-buffer ((icp-byte-array-var start-index-var number-of-icp-bytes-var
						    &optional end-of-message-group-form)
				&body body)
  `(let ((,number-of-icp-bytes-var number-of-icp-bytes-ready-to-read))
     (declare (type fixnum ,number-of-icp-bytes-var))
     (if (not (or (<f 0 ,number-of-icp-bytes-var)
		  (prog1 (ensure-next-icp-message-series)
		    (setq ,number-of-icp-bytes-var number-of-icp-bytes-ready-to-read))))
	 ,end-of-message-group-form
	 (let ((,icp-byte-array-var (icp-buffer-vector current-icp-buffer))
	       (,start-index-var (1+f current-read-icp-byte-position)))
	   ,@body))))

(def-substitution-macro read-icp-byte-if-any-macro (ok-if-none? read-message-group-end-p)
  (with-icp-read-buffer (array start length
			 (process-end-of-message-group ok-if-none? read-message-group-end-p))
    (update-icp-read-buffer 1 start length)
    (icp-byte-aref array start)))

(def-substitution-macro peek-icp-byte-if-any-macro (ok-if-none?)
  (with-icp-read-buffer (array start length
			 (process-end-of-message-group ok-if-none? nil))
    (icp-byte-aref array start)))

(defun-simple read-icp-skip-to-message-group-end ()
  (loop with current-resumable-icp-read-task = nil
	do
    (with-icp-read-buffer (array start length
			   (progn
			     (process-end-of-message-group t nil)
			     (return-from read-icp-skip-to-message-group-end nil)))
      (declare (ignore array start))
      (update-icp-read-buffer length))))    

(defun-simple read-icp-byte-or-message-group-end ()
  (read-icp-byte-if-any-macro t t))

(defun-simple read-icp-byte-if-any ()
  (read-icp-byte-if-any-macro t nil))

(defun-simple read-icp-byte ()
  (read-icp-byte-if-any-macro nil nil))

;;; peek-icp-byte-if-any
;;; note: not currently used -ncc, 14 Nov 1996 
(defun-simple peek-icp-byte-if-any ()
  (peek-icp-byte-if-any-macro t))

(defun-simple peek-icp-byte ()
  (peek-icp-byte-if-any-macro nil))

(defun get-icp-read-buffer ()
  (with-icp-read-buffer (array start length)
    (values array start length)))


(defun-simple ensure-next-icp-message-series ()
  ;; Either number-of-icp-bytes-ready-to-read is 0
  ;;   (external call, need a new buffer and/or a new message series),
  ;; and/or number-of-icp-bytes-left-in-current-buffer is 0
  ;;   (might also be an internal call, if the last buffer
  ;;   ended with a message-series-byte-count).
  (ensure-next-icp-byte)
  (cond
    ((=f number-of-icp-bytes-left-in-message-series 0)
     (if (at-end-of-message-group-p)
	 nil
	 (start-next-message-series)))
    (t
     (let ((number-of-icp-bytes-left-in-current-buffer
	     (number-of-icp-bytes-left-in-current-buffer current-icp-port)))
       (setq number-of-icp-bytes-ready-to-read
	     (minf number-of-icp-bytes-left-in-current-buffer
		   number-of-icp-bytes-left-in-message-series))
       (setq number-of-icp-bytes-left-in-message-series
	     (-f number-of-icp-bytes-left-in-message-series
		 number-of-icp-bytes-ready-to-read))
       (setf (number-of-icp-bytes-left-in-current-buffer current-icp-port)
	     (-f number-of-icp-bytes-left-in-current-buffer
		 number-of-icp-bytes-ready-to-read))
       t))))

(defun-simple ensure-next-icp-byte ()
  (when (=f 0 (number-of-icp-bytes-left-in-current-buffer current-icp-port))
    (let* ((icp-buffer-queue-head (icp-buffer-queue-head current-icp-port))
	   (next-head (icp-buffer-next icp-buffer-queue-head)))
      (setq current-icp-buffer next-head)
      (unless current-icp-buffer
	(icp-out-of-synch 4))
      (setf (icp-buffer-queue-head current-icp-port) next-head)
      (reclaim-icp-buffer icp-buffer-queue-head))
    (setf (number-of-icp-bytes-left-in-current-buffer current-icp-port)
	  (number-of-icp-bytes-in-buffer current-icp-buffer))
    (setq current-read-icp-byte-position -1)))

(defun-simple start-next-message-series ()
  (incff current-read-icp-byte-position)
  (setq number-of-icp-bytes-left-in-message-series
	(1-f (get-icp-byte current-icp-buffer current-read-icp-byte-position)))
  (let ((number-of-icp-bytes-left-in-current-buffer
	  (decff (number-of-icp-bytes-left-in-current-buffer current-icp-port))))
    (cond
      ((=f number-of-icp-bytes-left-in-current-buffer 0)
       (ensure-next-icp-message-series))
      (t (when (trace-read-icp-message-series-p)
	   (emit-icp-read-trace
	     nil ;this-is-prologue-p
	     0   ;byte-count-before?
	     ;; following is byte-count-after? argument
	     ;; 1+f allows for the count embedded in the message series
	     (1+f number-of-icp-bytes-left-in-message-series) 
	     "[reading message series]"
	     nil ;qualifier-string?
	     'message-series
	     nil ;report-icp-value-p
	     nil ;icp-value
	     t   ;no-padding-p
	     nil ;message-p
	     ))
	 (setq number-of-icp-bytes-ready-to-read
	       (minf number-of-icp-bytes-left-in-current-buffer
		     number-of-icp-bytes-left-in-message-series))
	 (decff number-of-icp-bytes-left-in-message-series
		number-of-icp-bytes-ready-to-read)
	 (decff (number-of-icp-bytes-left-in-current-buffer current-icp-port)
		number-of-icp-bytes-ready-to-read)
	 t))))

(defun-simple read-icp-suspend ()
  (cond ((current-icp-read-task-resumable-p)
	 (setq *resumable-icp-state* nil)
	 icp-suspend)
	(t
	 (icp-out-of-synch 5))))

(defun-simple process-end-of-message-group (ok-if-none? read-message-group-end-p)
  (when (and (not read-message-group-end-p)
	     (current-icp-read-task-resumable-p))
    (setq *resumable-icp-state* nil)
    (return-from process-end-of-message-group icp-suspend))
  (unless ok-if-none?
    (icp-out-of-synch 5))
  (when read-message-group-end-p
    (incff current-read-icp-byte-position)
    (decff (number-of-icp-bytes-left-in-current-buffer current-icp-port)))
  (when (trace-read-icp-message-series-p)
    (emit-icp-read-trace
      nil ;this-is-prologue-p
      0   ;byte-count-before?
      1   ;byte-count-after?
      "read \"end-of-message-group\" message series"
      nil ;qualifier-string?
      'message-series
      nil ;report-icp-value-p
      nil ;icp-value
      t   ;no-padding-p
      nil ;message-p
      ))
  nil)




;;; Declaration:     process-next-icp-message-group-if-ready (icp-input-port)
;;; Type:	     Lisp function.
;;; Purpose:	     Process an entire ICP message group.
;;; Arguments:	     An ICP input port.
;;; Return behavior: This function returns non-nil when it processes an icp message
;;;                  group, nil otherwise.
;;; Users:	     ICP internals (handle-icp-input-if-ready in INT2).
;;; Prerequisites:   None.
;;; Side effects:    This function is to be invoked by the ICP handler periodically
;;;                  or when an entire ICP message group is known to be ready in
;;;                  icp-input-port.  It reads and releases the ICP buffers
;;;                  necessary to store the message group.  This function does
;;;                  nothing if the icp-byte-index-of-end-of-message-group?  slot of
;;;                  icp-input-port is nil.
;;; Non-local exits: None.
;;; Memory impact:   Can release ICP buffers, can read and free network buffers
;;;                  internal to the operating system.
;;; Notes:           This function designed to work even while the
;;;                  icp-buffer-with-end-of-message-group?  and
;;;                  icp-byte-index-of-end-of-message-group?  slots of
;;;                  icp-input-port are being changed by
;;;                  enqueue-next-icp-buffer-if-any (which may be running in a
;;;                  separate process).  In particular, it is okay to start
;;;                  processing a message group while these slots are changing,
;;;                  since they only change when a message group is ready.  This
;;;                  function never acts as if there is yet another message group
;;;                  ready when the change for the first has still not been
;;;                  completed.

;;; Process-next-icp-message-group-if-ready is to be invoked by the ICP handler
;;; periodically or when an entire ICP message group is known to be ready in
;;; icp-input-port.  It returns non-nil when it processes an icp message group.
;;; Note that this does nothing if the icp-byte-index-of-end-of-message-group?
;;; slot of icp-input-port is nil.

;;; An ICP handler may (normally) only process an icp message when the entire
;;; message group to which it belongs is already in icp-input-port's queue of
;;; buffers.  In particular, it (normally) starts processing a message group
;;; only when the icp-byte-index-of-end-of- message-group? slot of
;;; icp-input-port is non-nil and the current end-of-message-group position has
;;; not been reached.  (Note that the icp-byte-index-of-end-of-message-group?
;;; slot is made nil when the two slots that specify the end-of-message-group
;;; position are being updated).

(def-system-variable at-end-of-icp-message-group? INT2 nil)



;; pre: icp-input-port's at the end of a message group and there's another group
;; buffered.

(def-substitution-macro compute-read-offset-of-next-group (icp-input-port)
  (-f (number-of-icp-bytes-in-buffer (icp-buffer-queue-head icp-input-port))
      (number-of-icp-bytes-left-in-current-buffer icp-input-port)
      1))

;;; ALL-MESSAGES-PROCESSED?
;;;
;;;   A predicate that returns T iff the head-icp-buffer is the buffer that
;;;   contains the end-of-message-group marker, and the "scan pointer" into the
;;;   head-icp-buffer is equal to the offset of the end-of-message-group marker,
;;;   returning NIL otherwise.

(defun-simple all-messages-processed? (head-icp-buffer icp-byte-index-of-end-of-message-group? icp-input-port)
  (and (eq head-icp-buffer (icp-buffer-with-end-of-message-group? icp-input-port))
       (=f (compute-read-offset-of-next-group icp-input-port)
	   icp-byte-index-of-end-of-message-group?)))

(defun-simple ready-for-next-icp-message-group (icp-input-port)
  (let ((message-group-complete? (icp-byte-index-of-end-of-message-group? icp-input-port))
	(head-icp-buffer (car (icp-buffer-queue-head icp-input-port))))
    (and message-group-complete?
	 (not (all-messages-processed? head-icp-buffer
				       message-group-complete?
				       icp-input-port)))))

(defmacro processing-next-icp-message-group ((icp-input-port) &body body)
  (avoiding-variable-capture
      (icp-input-port
	&aux message-group-complete? head-icp-buffer
	ready-for-next-message-group-p)
    `(let* ((,message-group-complete? (icp-byte-index-of-end-of-message-group? ,icp-input-port))
	    (,head-icp-buffer (icp-buffer-queue-head ,icp-input-port))

	    (,ready-for-next-message-group-p
	     (and ,message-group-complete?
		  (not (all-messages-processed? ,head-icp-buffer
						,message-group-complete?
						,icp-input-port)))))
      (when ,ready-for-next-message-group-p
	(let* ((current-icp-port ,icp-input-port)
	       (current-icp-socket (parent-icp-socket current-icp-port))
	       (current-standard-icp-object-index-space
		 (standard-icp-object-index-space current-icp-port))
	       (current-temporary-icp-object-index-space
		 (temporary-icp-object-index-space current-icp-port))
	       (number-of-icp-bytes-left-in-message-series 0)
	       (current-icp-buffer ,head-icp-buffer)
	       (number-of-icp-bytes-ready-to-read 0)
	       (at-end-of-icp-message-group? nil)		   
	       current-read-icp-byte-position)
	  (when (<f 0 (number-of-icp-bytes-left-in-current-buffer ,icp-input-port))
	    (setq current-read-icp-byte-position (compute-read-offset-of-next-group ,icp-input-port)))
	  ,@body
	  (current-system-case
	    (ab
	      (when (eq (icp-socket-listener-client? current-icp-socket) 'telewindows)
		(let ((workstation (icp-socket-workstation current-icp-socket)))
		  (when workstation
		    (maybe-schedule-service-workstation workstation t))))))))
      
      ,ready-for-next-message-group-p)))

(defun process-next-icp-message-group-if-ready (icp-input-port)
  (let* ((icp-socket (parent-icp-socket icp-input-port))
	 (disable-resumability
	   (with-bifurcated-version-for-input (supports-non-resumability-icp-version icp-socket)
	     nil
	     (icp-socket-does-not-allow-resumability icp-socket)))
	 (current-icp-socket icp-socket)
	 (system-name (icp-socket-local-system-name icp-socket))
	 (current-system-name (case system-name
				(g2 'ab)
				(t system-name))))
    (with-temporary-gensym-float-creation process-next-icp-message-group-if-ready
      (processing-next-icp-message-group (icp-input-port)
        (when (icp-connection-succeeds-at-first-message-p icp-socket)
	  (cancel-task (icp-connection-timeout-task? icp-socket)))
        (handle-icp-messages nil)))))
  
;; The test herein is designed to work even while the
;; icp-buffer-with-end-of-message-group?  and
;; icp-byte-index-of-end-of-message-group? slots of icp-input-port are being
;; changed by enqueue-next-icp-buffer-if-any (which may be running in a separate
;; process).  In particular, it is okay to start processing a message group
;; while these slots are changing, since they only change when a message group
;; is ready.  And the fact that icp-byte-index-of-end-of-message-group? is kept
;; null during the change prevents process-next-icp-message-group-if-ready from
;; improperly thinking there is yet another message group ready if the change
;; for the first has still not been completed.  Note that the values of the two
;; slots must not be used other than in this test.



;;; Declaration:     handle-icp-messages (exit-at-end-of-message-block?)
;;; Type:	     Lisp function.
;;; Purpose:	     Handle ICP messages from message blocks or groups.
;;; Arguments:       If exit-at-end-of-message-block?  is non-nil, this function
;;;                  will stop handling messages when it gets to the end of an ICP
;;;                  message block (a contiguous sequence of ICP messages, within an
;;;                  ICP message group, that must be handled together in some
;;;                  special context).
;;; Return behavior: No useful value.
;;; Users:           ICP internals (process-next-icp-message-group-if-ready in
;;;                  INT2), Telewindows and G2 printing (WINDOWS3).
;;; Prerequisites:   This assumes that special variables
;;;                  number-of-icp-bytes-left-in-message-series, number-
;;;                  of-icp-bytes-ready-to-read, current-icp-port,
;;;                  current-icp-buffer, and current-icp-byte- position are
;;;                  appropriately set up.
;;; Side effects:    Handle-icp-messages reads and handles ICP messages until it
;;;                  gets to the end of an icp message group or, provided
;;;                  exit-at-end-of-message-block?  is non-nil, until it gets to the
;;;                  end of an icp message block.  If the end of a message group is
;;;                  reached, special variable at-end-of-icp-message-group?  is set
;;;                  to t.  At-end-of-icp-message-block?  is set non-nil by handlers
;;;                  for messages that terminate an icp message block.  This
;;;                  function can also shut down an ICP connection if a message is
;;;                  ill-formed.  It also has the side effects of the messages it
;;;                  handles.
;;; Non-local exits: None.
;;; Memory impact:   Can release ICP buffers and reclaim ICP sockets.  This function
;;;                  also has the memory impact of the messages it handles.

;;; Handle-icp-messages reads and handles ICP messages until it gets to the end
;;; of an icp message group or, provided exit-at-end-of-message-block? is
;;; non-nil, until it gets to the end of an icp message block.  If the end of a
;;; message group is reached, special variable at-end-of-icp-message-group? is
;;; set to t.  At-end-of-icp-message-block? is set non-nil by handlers for
;;; messages that terminate an icp message block.

;;; This assumes that special variables
;;; number-of-icp-bytes-left-in-message-series, number-
;;; of-icp-bytes-ready-to-read, current-icp-port, current-icp-buffer, and
;;; current-icp-byte- position are appropriately set up.

;;; If ICP is out-of-synch, it closes the socket and notifies the user, and
;;; returns nil.

;;; ICP-SOCKET-TRANSACTING-MESSAGE-GROUP is a global which is bound specially
;;; within handle-icp-messages to cause any possible connectiojn shutdown within
;;; this dynamic extent to defer the calling of connection loss callbacks until
;;; the end of the message group.  The deferred connection loss callbacks are
;;; executed at the end of handle-icp-messages whenever the parent-icp-socket
;;; has gone closed within the dynamic extent of handle-icp-messages.  See the
;;; implementation of shutdown-icp-socket-connection for further details.
;;;  --ncc, jh, jra 21 Jun 1995 
(defvar icp-socket-transacting-message-group nil)

(defvar at-end-of-icp-message-block?)

(def-system-variable icp-message-trace-stream? INT2 nil)	; make this for development only!!

(defun handle-icp-messages (exit-at-end-of-message-block?)
  (loop with current-resumable-icp-read-task = nil
	with resumable-icp-read-ignore-p = nil
	with parent-icp-socket = (parent-icp-socket current-icp-port)
	with at-end-of-icp-message-block? = nil
	with icp-socket-transacting-message-group = parent-icp-socket
	with ignore-p = (=f (icp-connection-state parent-icp-socket)
			    icp-connection-awaiting-acknowledgement)
	with current-icp-message-handler-array
	  = icp-message-handler-array ; not used, when ignore-p is true
	as icp-byte? = (read-icp-byte-or-message-group-end)
	for message-count from 1
	until (setq at-end-of-icp-message-group? (null icp-byte?)) ; for recursive calls
	for index = (-f icp-byte? #.(icp-message-type-code-offset))
	with function? and handler-name
	for previous-handler-name = nil then handler-name
	do (cond ((or (<=f index 0)
		      (>=f index #.(icp-message-handler-array-size)))
		  (icp-out-of-synch 3 index))
		 ((null (setq function? (svref current-icp-message-handler-array index)))
		  (icp-out-of-synch 'unknown-message index)))
	   (setq handler-name (svref icp-message-handler-name-array index))
	   #+development
	   (when (eq trace-icp-messages 'handler)
	     (trace-time "ICP: ~(~s~)" handler-name))
	   (with-backtrace-for-internal-error handler-name
	     (setf (last-icp-message-code-read (parent-icp-socket current-icp-port)) index)
	     (cond (ignore-p
		    (loop while (read-icp-byte-if-any))
		    (when (eq handler-name 'handle-icp-acknowledge-shutdown)
		      (handle-icp-acknowledge-shutdown)))
		   (current-resumable-icp-read-task
		    (resume-icp-task-1 function?))
		   ((and (=f message-count 2)
			 (eq handler-name 'handle-icp-message-group-id)
			 (eq previous-handler-name 'handle-icp-i-am-alive))
		    (let ((handling-solitary-i-am-alive? t)) ; for send-I-am-alive-if-necessary (only)
		      (funcall-simple-compiled-function function?)))
		   (t
		    (funcall-simple-compiled-function function?))))
	   (ensure-remote-icp-version-info parent-icp-socket handler-name)
	until (or (and exit-at-end-of-message-block? at-end-of-icp-message-block?)
		  at-end-of-icp-message-group?
		  (not (icp-connection-can-process-messages? parent-icp-socket)))
	finally
	  (maybe-finish-current-icp-read-task)))

(defvar debug-out-of-synch t)

(defun debug-out-of-synch
    (code icp-byte current-icp-buffer read-icp-byte-position number-of-icp-bytes-ready-to-read
	  icp-socket)
  (when debug-out-of-synch
    (format t "~%ICP out of synch ~D on socket ~A"
	    code
	    (wide-string-to-gensym-string (icp-socket-description icp-socket)))
    (format t "~%icp-byte=~D" icp-byte)
    (format t "~%icp-byte-position=~D" read-icp-byte-position)
    (format t "~%icp-bytes-ready-to-read=~d" number-of-icp-bytes-ready-to-read)
    (print-icp-buffer-byte-contents current-icp-buffer)
    (format t "~%")))




;; Note that begin-window-update in module WINDOWS and
;; begin-making-icon-rendering in module ENTITIES use this recursively, setting
;; set at-end-of-icp-message-group? and/or at-end-of-icp-message-block? non-nil
;; in order to exit from the sublevel.

;; Consider having a time limit arg.

;; Changed handle-icp-messages to use funcall-compiled-function on the handler it
;; gets from icp-message-handler-array.  This eliminates some symbols from the
;; Chestnut runtime symbol table, which is of limited size.  jh, 2/21/91.
(defun twrite-icp-error (error-type error-string-or-out-of-synch-case &optional arg1 arg2 arg3)
  (tformat "ICP ~A on "
	   (if (eq error-type 'warning)
	       "warning"
	       "error"))
  (let ((interface nil))
    (current-system-case
      (ab (setq interface (find-network-interface-for-icp-socket current-icp-socket 'no-error))
	  (when (or (text-string-p interface)
		    (stringp interface)
		    (null (superblock?-function interface)))
	    (setq interface nil))
	  (when interface
	    (tformat "interface ~NF (" interface))))
    (unless interface
      (tformat "socket "))
    (twrite-icp-socket-connection-name current-icp-socket)
    (when interface
      (tformat ")")))
  (tformat ": ")
  (tformat error-string-or-out-of-synch-case arg1 arg2 arg3))

(defun icp-error-message-string (error-type error-string-or-out-of-synch-case arg1 arg2 arg3)
  (twith-output-to-text-string
    (twrite-icp-error error-type error-string-or-out-of-synch-case arg1 arg2 arg3)))

(defun-simple icp-error-internal (error-type error-string-or-out-of-synch-case arg1 arg2 arg3)
  (let* ((*resumable-icp-state* nil)
	 (direction (icp-port-direction current-icp-port))
	 (resumable-output-p
	  (and (eq direction 'output)
	       writing-resumable-icp-messages-p
	       (not (current-system-case
 		     (ab (eq (icp-socket-listener-client? current-icp-socket) 'telewindows))
 		     (telewindows t)))))
	 (shutdownp (case error-type
		      (warning nil)
		      (resumable-error (not resumable-output-p))
		      (t t))))
    (current-system-case
      (gsi
	(let ((string2 (icp-error-message-string
			 error-type error-string-or-out-of-synch-case arg1 arg2 arg3)))
	  (if shutdownp
	      (gsi-connection-error 'icp_error gsi-connection-lost string2)
	      (gsi-warning 'icp_error gsi-resumable-icp-error string2))
	  (reclaim-text-string string2)))
      (ab
	(give-icp-error-warning-message
	  shutdownp error-type error-string-or-out-of-synch-case arg1 arg2 arg3)
	(unless (eq error-type 'warning)
	  (if (memq (icp-socket-listener-client? current-icp-socket) '(g2 gsi))
	      (remote-procedure-error
		current-icp-socket 'rpc-error
		(icp-error-message-string
		  error-type error-string-or-out-of-synch-case arg1 arg2 arg3)
		nil)
	      (let ((string2 (icp-error-message-string
			       error-type error-string-or-out-of-synch-case arg1 arg2 arg3)))
		(notify-user string2)
		(reclaim-text-string string2))))
	(when shutdownp
	  (flush-and-shutdown-icp-socket current-icp-socket)))
      (t
	(let ((string2 (icp-error-message-string
			 error-type error-string-or-out-of-synch-case arg1 arg2 arg3)))
	  (notify-user-at-console string2)
	  (reclaim-text-string string2))
	(when shutdownp
	  (flush-and-shutdown-icp-socket current-icp-socket))))
    (unless (eq error-type 'warning)
      (cond (resumable-output-p
	     (setq icp-error-suspend-p t)
	     icp-suspend)
	    (abort-for-icp-catcher?	   
	     (when (eq 'input direction)
	       (kill-current-icp-read-task))
	     (throw abort-for-icp-catcher? nil))
	    (t ; We should never get here.
	     #+development
 	     (cerror "Continue"
 		     "No catch tag found in icp-error-internal")
	     nil)))))

(def-system-variable abort-for-icp-catcher? INT2 nil)

(defun-void abort-for-icp ()
  (if abort-for-icp-catcher?
      (throw abort-for-icp-catcher? nil)
      (abort)))

(defun icp-out-of-synch (case &optional message-code) 
  (let ((parent-socket (parent-icp-socket current-icp-port)))
    (unless (or abort-for-icp-catcher?
		(eq case 3) (eq case 'unknown-message))
      (if (eq case 'unknown-message)
	  (notify-user-if-possible
	    "ICP: Socket ~a (~a) received unknown message code ~a; ~
             closing broken connection after message ~a"
	    (type-of-icp-connection parent-socket)
	    (icp-connection-name parent-socket)
	    message-code
	    (last-icp-message-code-read parent-socket))
	  (notify-user-if-possible
	    "ICP: Protocol out-of-synch (case ~d) ~
             for ICP socket ~a with ~a; ~
             closing broken connection after message ~a"
	    case
	    (type-of-icp-connection parent-socket)
	    (icp-connection-name parent-socket)
	    (last-icp-message-code-read parent-socket))))
    (let ((icp-socket-transacting-message-group nil))
      (shutdown-icp-socket-connection
	parent-socket
	(case case
	  (unknown-message 'unknown-message) ; handle-icp-messages
	  (1 'protocol-out-of-synch-1)   ; enqueue-next-icp-buffer-if-any
	  ;; 2 is icp-case-2-error, which appears to have no callers
	  (3 'protocol-out-of-synch-3)   ; handle-icp-messages
	  (4 'protocol-out-of-synch-4)   ; ensure-next-icp-byte
	  (5 'protocol-out-of-synch-5)   ; process-end-of-message-group
	  (6 'protocol-out-of-synch-6)   ; resume-icp-task (message handler)
	  (7 'protocol-out-of-synch-7)))) ; icp-value-reader item-copy
    (abort-for-icp)))

;;;; ICP Writing



(defvar number-of-icp-bytes-for-message-series)

(defvar icp-buffers-for-message-group)

(defvar icp-byte-position-of-start-of-message-series?)
(defvar icp-buffer-of-start-of-message-series?)

(defvar number-of-icp-bytes-to-fill-buffer)

(defvar number-of-icp-bytes-in-message-group)







;;; Declaration:     write-icp-byte-macro (icp-byte)
;;; Type:	     G2 substitution macro.
;;; Purpose:	     Write a single ICP byte.
;;; Arguments:	     icp-byte is a 16-bit integer, represented as a fixnum.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (write-icp-byte in INT2).
;;; Prerequisites:   None.
;;; Side effects:    Can modify the current ICP buffer of the current ICP port,
;;;                  or allocate a new current buffer.
;;; Non-local exits: None.
;;; Memory impact:   Can cause a new ICP buffer to be allocated.

;;; Declaration:     write-icp-byte (icp-byte)
;;; Type:	     Lisp function.
;;; Purpose:	     Write a single ICP byte.
;;; Arguments:	     icp-byte is a 16-bit integer, represented as a fixnum.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals:
;;;                    INT2: start-writing-icp-message
;;;                          start-icp-message-series
;;;                    INT3: def-icp-value-writer forms for public ICP value types
;;;                  Also GSI (GSI-COMMON), Telewindows and G2 printing (TELESTUBS),
;;;                  G2 remote procedures (G2-RPC1 and G2-RPC2), G2 foreign functions
;;;                  (G2-FOREIGN), G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    Can modify the current ICP buffer of the current ICP port,
;;;                  or allocate a new current buffer.
;;; Non-local exits: None.
;;; Memory impact:   Can cause a new ICP buffer to be allocated.



(defmacro maybe-suspend-icp-writing (&body body)
  `(if (and writing-resumable-icp-messages-p
	    (>f (-f number-of-icp-bytes-for-message-series
		    number-of-icp-bytes-to-fill-buffer)
		minimum-message-series-size-before-suspending))
       (progn
	 (setq *resumable-icp-state* nil)
	 icp-suspend)
       (progn ,@body)))

(defmacro with-icp-write-buffer
    ((icp-byte-array-var start-index-var number-of-icp-bytes-var end-of-icp-buffer-form)
     &body body)
  `(maybe-suspend-icp-writing
     (let ((,number-of-icp-bytes-var number-of-icp-bytes-to-fill-buffer))
       (declare (type fixnum ,number-of-icp-bytes-var))
       (when (=f 0 ,number-of-icp-bytes-var)
	 ,end-of-icp-buffer-form
	 (setq ,number-of-icp-bytes-var number-of-icp-bytes-to-fill-buffer))
       (let ((,icp-byte-array-var (icp-buffer-vector current-icp-buffer))
	     (,start-index-var (1+f current-write-icp-byte-position)))
	 (declare (type fixnum ,start-index-var))
	 ,@body))))

(defmacro update-icp-write-buffer (number-of-bytes-actually-written &optional current-position+1 number-to-fill)
  `(progn
     ,(if current-position+1
	  `(setq current-write-icp-byte-position (+f (1-f ,current-position+1) ,number-of-bytes-actually-written))
	  `(incff current-write-icp-byte-position ,number-of-bytes-actually-written))
     ,(if number-to-fill
	  `(setq number-of-icp-bytes-to-fill-buffer (-f ,number-to-fill ,number-of-bytes-actually-written))
	  `(decff number-of-icp-bytes-to-fill-buffer ,number-of-bytes-actually-written))))

(defun-simple write-icp-maybe-suspend ()
  (maybe-suspend-icp-writing nil))

(defmacro with-disabled-write-icp-suspension (&body body)
  `(progn
     (write-icp-maybe-suspend)
     (let ((writing-resumable-icp-messages-p nil))
       ,@body)))     

(def-substitution-macro write-icp-byte-macro (icp-byte)
  (with-icp-write-buffer (array start length (write-get-new-buffer))
    (update-icp-write-buffer 1 start length)
    (setf (icp-byte-aref array start) icp-byte)))

(defun-simple write-icp-byte (icp-byte)
  (write-icp-byte-macro icp-byte))

(defun get-icp-write-buffer ()
  (with-icp-write-buffer (array start length (write-get-new-buffer))
    (values array start length)))



(defun-void write-get-new-buffer ()
  (when current-icp-buffer
    (setf (icp-buffer-end-byte current-icp-buffer)
	  (size-of-variable-fill-icp-buffers-in-8-bit-bytes)))
  (let ((new-icp-buffer
	  (let ((tail (icp-buffer-queue-tail current-icp-port)))
	    (cond
	      ((and (not (eq (icp-buffer-queue-head current-icp-port) tail))
		    (null (icp-buffer-vector-reference-count tail))
		    (<f (icp-buffer-end-byte tail)
			(size-of-variable-fill-icp-buffers-in-8-bit-bytes)))
	       (let ((copy (copy-icp-buffer tail)))
		 (setf (icp-buffer-start-byte copy) (icp-buffer-end-byte copy))
		 copy))
	      (t
	       (make-icp-buffer))))))
    (cond (icp-buffers-for-message-group
	   (setf (icp-buffer-next current-icp-buffer) new-icp-buffer))
	  (t
	   (setq icp-buffers-for-message-group new-icp-buffer)))
    (setq current-icp-buffer new-icp-buffer))
  ;; Adjust the counters associated with message series.
  (let ((bytes-available-in-buffer (-f (size-of-variable-fill-icp-buffers)
				       (icp-buffer-end-icp-byte current-icp-buffer))))
    (setq number-of-icp-bytes-to-fill-buffer bytes-available-in-buffer)
    (incff number-of-icp-bytes-for-message-series bytes-available-in-buffer)
    ;; Adjust the index into the new buffer.
    (setq current-write-icp-byte-position
	  (-f (size-of-variable-fill-icp-buffers)
	      bytes-available-in-buffer
	      1)))
  (when (and (<=f #.(-f (maximum-icp-byte-unsigned-integer)
			(size-of-variable-fill-icp-buffers))
		  number-of-icp-bytes-for-message-series)
	     disable-resumability)
    (start-icp-message-series)))

(defun-void stop-filling-icp-buffer-at-end-of-icp-message-group ()
  (setf (icp-buffer-end-icp-byte current-icp-buffer)
	(-f (size-of-variable-fill-icp-buffers)
	    number-of-icp-bytes-to-fill-buffer))
  (decff number-of-icp-bytes-for-message-series number-of-icp-bytes-to-fill-buffer)
  (setq number-of-icp-bytes-to-fill-buffer 0))

(def-substitution-macro running-a-scheduled-task-p ()
  (and current-schedule-task t))

(defvar writing-icp-message-group 0)

#+development
(defun check-icp-message-group-nesting ()
  #+message-group-nesting-warning
  (unless (=f writing-icp-message-group 1)
    (warn "Nested writing-icp-message-group level ~d in ~a."
	  writing-icp-message-group (cadr (backtrace)))))

;;; Supply T for the no-catch-p argument only if icp-error won't be called by anything inside
;;; the writing-icp-message-group body.
(defmacro writing-icp-message-group ((icp-output-port &optional no-catch-p) &body body)
  (declare (ignore no-catch-p))
  `(let* ((current-icp-port ,icp-output-port)
	  (current-icp-socket (parent-icp-socket current-icp-port))
	  (disable-resumability
	    (or (with-bifurcated-version-for-output (supports-non-resumability-icp-version)
		  nil
		  (icp-socket-does-not-allow-resumability current-icp-socket))
		(current-system-case
		  (ab (eq (icp-socket-listener-client? current-icp-socket) 'telewindows))
		  (telewindows t))))
	  (number-of-icp-bytes-for-message-series 0)
	  (icp-buffers-for-message-group nil)
	  (icp-buffer-of-start-of-message-series? nil)
	  (icp-byte-position-of-start-of-message-series? nil)
	  (number-of-icp-bytes-to-fill-buffer 0)
	  (current-icp-buffer nil)
	  (current-write-icp-byte-position nil)
	  (number-of-icp-bytes-in-message-group 0)
	  (writing-icp-message-group (1+f writing-icp-message-group)))
     #+development (check-icp-message-group-nesting)
     (with-faster-standard-output	; Makes icp-trace faster in development
       (with-temporary-profiling-context icp
	 (when (and (icp-connection-open-p current-icp-socket)
		    (not (icp-connection-being-shutdown? current-icp-socket)))
	   (prog1 (progn ,@body)
	     (end-icp-message-group)))))))

;; reset-icp-message-group-state			SUBSTITUTION MACRO
;;
;; Purpose: Code following the call to this function will behave as if a fresh
;;  writing-icp-message-group form had been entered.
;; Note: This code depends on being called from inside the dynamic extent of a
;;  writing-icp-message-group form!!!
;;
(def-substitution-macro reset-icp-message-group-state ()
  (setf number-of-icp-bytes-for-message-series 0)
  (setf icp-buffers-for-message-group nil) ; hope these have been reclaimed!
  (setf icp-byte-position-of-start-of-message-series? nil)
  (setf number-of-icp-bytes-to-fill-buffer 0)
  (setf current-icp-buffer nil)
  (setf current-write-icp-byte-position nil)
  (setf number-of-icp-bytes-in-message-group 0))


(defun-void next-icp-message-group ()
  (end-icp-message-group)
  (reset-icp-message-group-state))



;; In-message-group-context? is used by the reclaim-icp-object-map-for-...
;; reclaimers (see def-icp-object-type).



;;; Declaration:     writing-icp-message-group ((icp-output-port) &body body)
;;; Type:	     Lisp macro.
;;; Purpose:	     Set up a context for writing an ICP message group.
;;; Arguments:       The forms in body are executed.  Any forms than send ICP
;;;                  messages (typically calls to a function of the form
;;;                  send-icp-xxx) send them through icp-output-port.
;;; Return behavior: No useful value at compile time.  At run time, the
;;;                  macroexpansion returns multiple values from the last form
;;;                  in body.  Note difference between this behavior and that of
;;                   writing-icp-message-group.
;;; Users:	     ICP internals:
;;;                    INT3: send-i-am-alive-message
;;;                          warn-disallowed-icp-listener-connections
;;;                    INT4: reclaim-index-space-location-and-corresponding-objects
;;;                  Also in Telewindows and G2 printing (WINDOWS1, WINDOWS3,
;;;                  TELESTUBS, WORKSTATION), G2 remote procedures
;;;                  (G2-RPC1 and G2-RPC2), G2 foreign functions (G2-FOREIGN),
;;;                  GSPAN, G2-to-G2 communications (G2DS, G2DS-NUPEC), G2 player
;;;                  (PLAYER).
;;; Prerequisites:   None.
;;; Side effects:    Binds the following ICP internal variables:
;;;                    current-icp-port
;;;                    current-icp-socket
;;;                    number-of-icp-bytes-for-message-series
;;;                    icp-buffers-for-message-group
;;;                    icp-byte-position-of-start-of-message-series?
;;;                    number-of-icp-bytes-to-fill-buffer
;;;                    current-icp-buffer
;;;                    current-write-icp-byte-position
;;;                    in-message-group-context?
;;;                    number-of-icp-bytes-in-message-group
;;; Non-local exits: None.
;;; Memory impact:   Special variable binding.

;;; Declaration:     writing-icp-message-group 
;;;                     ((icp-output-port) &body body)
;;; Type:	     Lisp macro.
;;; Purpose:	     Set up a context for writing an ICP message group.
;;; Arguments:       The forms in body are executed.  Any forms than send ICP
;;;                  messages (typically calls to a function of the form
;;;                  send-icp-xxx) send them through icp-output-port.
;;; Return behavior: No useful value at compile time.  At run time, returns a
;;;                  single value from the last form in body.  Note the
;;;                  difference in behavior from that of
;;;                  writing-icp-message-group.
;;; Users:           GSI (modules GSI and GSI-COMMON).  Eventually, this should
;;;                  replace writing-icp-message group anywhere performance is
;;;                  critical and body has no non-local exits and returns a
;;;                  single value.
;;; Prerequisites:   None.
;;; Side effects:    See writing-icp-message-group.
;;; Non-local exits: If a non-local exit is attempted from body in development,
;;;                  a continuable error is signaled.
;;; Memory impact:   Special variable binding.

(def-system-variable do-icp-flow-control? INT2 t)

(def-substitution-macro icp-connection-unclogged-for-socket? (icp-socket)
  (let ((I-am-alive-info? (I-am-alive-info? icp-socket)))
    (or (null I-am-alive-info?)
	(not do-icp-flow-control?)
	(not (icp-connection-clogged-p I-am-alive-info?)))))

;; Icp-connection-unclogged-for-socket?  is currently used only in on-window to
;; cut off Telewindows messages.



(def-substitution-macro increment-message-group-id (message-group-id)
  (if (=f message-group-id most-positive-fixnum)
      0
      (+f message-group-id 1)))

;; See documentation for message-group-ids.



;;; End-icp-message-group ...

(defun update-i-am-alive-info-at-end-of-message-group (I-am-alive-info)
  (declare no-op-for-gsi)
  (let ((id-for-last-message-group-written
	  (increment-message-group-id
	    (id-for-last-message-group-written I-am-alive-info)))
	(message-group-final-byte-count
	  (+f number-of-icp-bytes-in-message-group
	      (-f number-of-icp-bytes-for-message-series
		  number-of-icp-bytes-to-fill-buffer)
	      3)))

    ;; Number-of-icp-bytes-in-message-group is not up to date here because
    ;; end-icp-message-series-if-any has not been called yet (it is called
    ;; at the end of this function).  Therefore, need to add to
    ;; number-of-icp-bytes-in-message-group the message series byte count,
    ;; given by (-f number-of-icp-bytes-for-message-series
    ;; number-of-icp-bytes-to-fill-buffer) The 3 is for the icp bytes sent
    ;; by send-icp-message-group-id.

    (setf (id-for-last-message-group-written I-am-alive-info)
	  id-for-last-message-group-written)
    (send-icp-message-group-id 
      id-for-last-message-group-written
      message-group-final-byte-count)
    (enqueue (icp-cons id-for-last-message-group-written
		       message-group-final-byte-count)
	     (message-group-ids-and-byte-counts I-am-alive-info)
	     (message-group-ids-and-byte-counts-tail I-am-alive-info)
	     icp-cons)
    (incff (number-of-outstanding-icp-bytes I-am-alive-info)
	   message-group-final-byte-count)
    (update-icp-connection-clogged-p I-am-alive-info t)))

(defun update-icp-connection-clogged-p (I-am-alive-info side-sending-i-am-alive-p)
  (runtime-current-system-case
   ((ab telewindows)
    (let ((was-clogged-p
	   (icp-connection-clogged-p I-am-alive-info))
	  (new-clogged-p
	   (let ((fn (function-to-determine-if-icp-connection-clogged?
		      I-am-alive-info)))
	     (and fn (funcall fn current-icp-socket I-am-alive-info)))))
      #+development
      (unless (eq (not was-clogged-p) (not new-clogged-p))
	(dwarn "Icp connection ~S is now ~A."
	       current-icp-socket
	       (if new-clogged-p "clogged" "unclogged")))
      (setf (icp-connection-clogged-p I-am-alive-info) new-clogged-p)
      (when (and was-clogged-p
		 (not side-sending-i-am-alive-p)
		 (not (icp-connection-clogged-p I-am-alive-info)))
	(with-current-scheduling
	    ((unclogged-cleanup-task I-am-alive-info)
	     0 nil nil t)
	  (handle-unclogged-connection-if-necessary I-am-alive-info)))))
   (gsi
     (declare-ignorable-icp-arguments I-am-alive-info side-sending-i-am-alive-p))))

(defun-void end-icp-message-group ()
  (when icp-buffers-for-message-group
    (unless writing-resumable-icp-messages-p
      ;; See documentation for I-am-alive mechanism.
      (let ((I-am-alive-info? (I-am-alive-info? current-icp-socket)))
	(when I-am-alive-info?
	  (update-i-am-alive-info-at-end-of-message-group I-am-alive-info?))))
    (start-icp-message-series)
    (stop-filling-icp-buffer-at-end-of-icp-message-group)
    (end-icp-message-series-if-any)
    (transmit-completed-icp-message-group)))

;; A version of this that does not always fill the last icp buffer and transmit
;; the whole message group would have to have provisions in icp-output-port for
;; keeping the current state of the last icp buffer (and maybe an unended icp
;; message series).

;; This contains "local telewindows" test code.  See also on-window in module
;; WINDOWS.



;;; Start-writing-icp-message ...

;;; This starts a new icp message series at the very beginning of an icp message
;;; group and when there are one or more full icp buffers for the current icp message
;;; series (preceding the icp buffer in which this icp message will begin).



(defun-void start-writing-icp-message (icp-message-type-code)
  (let ((bytes-in-current-message-series
	  (-f number-of-icp-bytes-for-message-series
	      number-of-icp-bytes-to-fill-buffer)))
    (when (or (=f 0 bytes-in-current-message-series)
	      (<f minimum-message-series-size-before-beginning-new-series
		  bytes-in-current-message-series))
      (when (trace-write-icp-message-series-p)
	(emit-icp-write-trace
	  t   ;this-is-prologue-p
	  nil ;byte-count-before?
	  nil ;byte-count-after?
	  "message series"
	  nil ;qualifier-string?
	  'message-series
	  nil ;report-icp-value-p
	  nil ;icp-value
	  t   ;no-padding-p
	  nil ;message-p
	  ))
      (start-icp-message-series)))
  (let ((writing-resumable-icp-messages-p nil))
    (write-icp-byte
      (+f icp-message-type-code #.(icp-message-type-code-offset)))))

;; Fix this to force out icp message series as appropriate!

;; Make this a macro later, and note that icp-message-type-code will typically be a
;; constant!



;; Start-icp-message-series ...

(defun-void start-icp-message-series ()
  (end-icp-message-series-if-any)
  (setq number-of-icp-bytes-for-message-series number-of-icp-bytes-to-fill-buffer)
  (let ((writing-resumable-icp-messages-p nil))
    (write-icp-byte 1))
  (setq icp-buffer-of-start-of-message-series? current-icp-buffer)
  (setq icp-byte-position-of-start-of-message-series? current-write-icp-byte-position))



;; End-icp-message-series-if-any ...
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter icp-message-too-long-warning
  "ICP message series too long -- please call Gensym customer support")
)

(defun-void transmit-completed-icp-message-group ()
  (let ((icp-output-port current-icp-port))
    (when icp-buffers-for-message-group
      (let ((tail (icp-buffer-queue-tail icp-output-port)))
	(let ((buffer icp-buffers-for-message-group))
	  (when (eq (icp-buffer-vector tail) (icp-buffer-vector buffer))
	    (setf (icp-buffer-end-byte tail) (icp-buffer-end-byte buffer))
	    (setq icp-buffers-for-message-group (icp-buffer-next buffer))
	    (reclaim-icp-buffer buffer)))
	(when icp-buffers-for-message-group
	  (setf (icp-buffer-next tail) icp-buffers-for-message-group)
	  (loop for buffer = icp-buffers-for-message-group then next-buffer
		for next-buffer = (icp-buffer-next buffer)
		while next-buffer
		finally (setf (icp-buffer-queue-tail icp-output-port) buffer)))))
    (when (receive-or-transmit-directly? icp-output-port)
      (unless (all-icp-buffers-transmitted? icp-output-port)
	(cond (with-icp-buffer-coelescing-scope?
	       (transmit-icp-output-if-ready icp-output-port nil)
	       (unless (icp-output-port-flush-list-entry icp-output-port)
		 (let ((new-cons (gensym-cons
				   icp-output-port
				   icp-output-ports-to-flush)))
		   (setf (icp-output-port-flush-list-entry icp-output-port) new-cons)
		   (setq icp-output-ports-to-flush new-cons))))
	      (t
	       (transmit-icp-output-if-ready icp-output-port t)))))))

(defun end-icp-message-series-if-any ()
  (when icp-buffers-for-message-group
    (let ((message-series-byte-count
	    (-f number-of-icp-bytes-for-message-series
		number-of-icp-bytes-to-fill-buffer)))
      (when (>f message-series-byte-count 
		#.(maximum-icp-byte-unsigned-integer))
	(current-system-case
	  ((ab telewindows) (icp-error #.icp-message-too-long-warning))
	  (gsi (signal-gsi-icp-message-too-long-error))))
      (when (trace-write-icp-message-series-p)
	(emit-icp-write-trace
	  nil ;this-is-prologue-p
	  0   ;byte-count-before?
	  message-series-byte-count
	  (if (=f message-series-byte-count 1)
	      "wrote \"end-of-message-group\" message series"
	      "[finished writing message series]")
	  nil ;qualifier-string?
	  'message-series
	  nil ;report-icp-value-p
	  nil ;icp-value
	  t   ;no-padding-p
	  nil ;message-p
	  ))
      (store-icp-byte
	icp-buffer-of-start-of-message-series?
	icp-byte-position-of-start-of-message-series?
	message-series-byte-count)
      (incff number-of-icp-bytes-in-message-group message-series-byte-count))))

;; The error can happen only if an ICP buffer and/or an individual message is longer than
;; 32000 ICP bytes.

;; note that above, the call to transmit-icp-output-if-ready is always made,
;; since icp output ports are always created with receive-or-transmit-directly?
;; set to t.  (this value is never changed during the life of an icp-port
;; structure.)  -ncc, 31 Mar 1996


;; End file with CR


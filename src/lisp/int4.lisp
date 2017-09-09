;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INT4

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Mark H. David, et al.



;;; Split from module INT by jh on 9/12/90.  (Previously, INT was called ICP.)
;;; INT4 contains the ICP connection machinery. 


;;; File name:		     INT4.LISP
;;; File location:	     ma:>ab>
;;; Code control:	     Zmacs on the Explorers.
;;; Purpose:		     Open and close ICP connections, get connection info.
;;; Contents:                Functions to open and close ICP connections on all
;;;                          platforms, functions to reclaim the memory associated
;;;                          with an ICP connection.
;;; This file depends on:    Preceding .LISP files in the system load ordering.
;;; Dependent files:	     Subsequent .LISP files in the system load ordering.
;;; Role in products:        Linked into G2 and Telewindows.
;;; Role in development:     None.
;;; Testing harness:         /home/jh/icp/icpharness.c contains a rudimentary
;;;                          interpreter to test making network connections, reading
;;;                          and writing across them, and closing them.
;;; Performace requirements: These functions and macros are central to ICP
;;;                          operation.  Performance is critical.
;;; Major Entities:          [list struct] icp-connection-configurarion
;;;                          [function]    make-network-pathname
;;;                          [function]    make-icp-connection
;;;                          [function]    get-tcpip-listener-specification
;;;                                        (was get-or-use-default-tcp-port)
;;;                          [function]    accept-network-request-if-any
;;;                          [function]    make-network-connection
;;;                          [subst macro] extract-network-protocol
;;;                          [subst macro] extract-network-address
;;;                          [function]    get-unix-host-name
;;;                          [function]    accept-ti-tcp-connect-request-if-any
;;;                          [function]    make-ti-tcp-connection
;;;                          [function]    accept-ti-dna-connect-request-if-any
;;;                          [function]    make-ti-dna-connection
;;;                          [function]    accept-smbx-tcp-connect-request-if-any
;;;                          [function]    make-smbx-tcp-connection
;;;                          [function]    establish-g2-network-listeners
;;;                                        (was establish-network-listeners)
;;;                          [sys var]     generic-listener-initialized?
;;;                          [function]    report-listener-info-to-parent-window
;;;                          [function]    make-localnet-connection
;;;                          [function]    transmit-localnet-buffer
;;;                          [function]    purge-inactive-icp-sockets
;;;                          [sys var]     icp-port-being-reclaimed?
;;;                          [function]    reclaim-inactive-icp-sockets
;;;                          [function]    remove-icp-port-entries-from-icp-object
;;;                          [function]    reclaim-index-space-location-and-
;;;                                          corresponding-objects
;;;                          [function]    remove-icp-object-from-index-space
;;;                          [function]    shutdown-icp-socket-connection
;;;                          [function]    flush-and-shutdown-icp-socket
;;;                          [macro]       def-icp-handshake (under construction)


;;;; Forward references in INT4

(declare-forward-reference maybe-call-gsi-shutdown-context-callback function)
(declare-forward-reference register-gsi-connection-callbacks function)
(declare-forward-reference item-references-enabled-p function)
(declare-forward-reference get-icp-object-index-for-gsi-instance function)
(declare-forward-reference set-window-title function) ; TELESTUBS



;;;; Making ICP Connections



;;; Declaration:     icp-connection-configuration
;;; Type:	     Implicit list structure in G2.
;;; Purpose:	     Describe an ICP connection.
;;; Slots:           This is a list in one of the following forms:
;;;                    (TCP-IP host-name-string tcp-ip-port-number)
;;;                    (UNIX-TCPIP host-name-string tcp-ip-port-number)
;;;                    (LOCALNET host-name)
;;;                  This list contains the following information:
;;;                  > Transport type, a symbol.  These literal symbols occur in all
;;;                    caps in the formats above to distinguish them from the other
;;;                    list components.  TCP-IP, and LOCALNET are available in
;;;                    distribution and development G2s.  UNIX-TCPIP and
;;;                    VMS-PROCESS may occur in KBs created prior to G2 version 2.0.
;;;                  > Host name, a symbol or string naming the network host where
;;;                    the connection should be made.  In the formats above,
;;;                    host-name is a symbol and host-name-string a string.
;;;                  > Connection address, a fixnum, symbol, or string naming the
;;;                    address where the connection shoud be made.  In the formats
;;;                    above, network-task-name is a symbol, tcp-ip-port-number is a
;;;                    fixnum, and file-pathname is a string.
;;; Return behavior: N/A.
;;; Users:	     ICP internals.
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   If this list is generated dynamically, it must be reclasimed.
;;; Possible bugs:   It is not clear where type mismatching would cause errors, e.g.
;;;                  giving a fixnum formatted as a string to an
;;;                  icp-connection-configuration for TCP-IP.

;;; old doc (pre 10/9/92):
;;; An `icp connection configuration' is a list in one of the following
;;; forms
;;;
;;;    (a) (TCP-IP host-name-string tcp-ip-port-number)
;;;
;;; In addition, prior to 2.0 it may have been entered in one of the following
;;; forms:
;;;
;;;    (b) (TI-TCP-IP host-name-string tcp-ip-port-number)
;;;
;;;    (c) (UNIX-TCPIP host-name-string tcp-ip-port-number)
;;;
;;; Forms (b) and (c) are both equivalent to and handled same way as form (b).
;;; Note that forms (b) and (c) may continue to exist in knowledge bases saved
;;; in 2.0 or later versions as long as the slots they are in are not edited
;;; by the user.
;;;
;;; In addition, to support G2DS (for G2 to G2 communications), all of the
;;; preceeding forms are allowed and additionally one of the following forms
;;; is also allowed:
;;;
;;;    (d) (LOCALNET host-name)



;; jh, 8/21/91.  Added copy-with-underscores-changed-to-hyphens.  We should
;; consider moving it and its companion to someplace more central, like UTILITIES.

(def-substitution-macro copy-with-hyphens-changed-to-underscores 
    (string-or-symbol)
  (let ((local-string
	  (if (symbolp string-or-symbol) 
	      (symbol-name-text-string string-or-symbol)
	      string-or-symbol)))
    (twith-output-to-text-string
      (loop for i from 0 below (lengthw local-string)
	    as c = (charw local-string i)
	    do
	(twrite-char (if (char=w #.%\- c) #.%\_ c))))))

(def-substitution-macro copy-with-underscores-changed-to-hyphens 
    (string-or-symbol)
  (let ((local-string
	  (if (symbolp string-or-symbol) 
	      (symbol-name-text-string string-or-symbol)
	      string-or-symbol)))
    (twith-output-to-text-string
      (loop for i from 0 below (lengthw local-string)
	    as c = (charw local-string i)
	    do (twrite-char (if (char=w #.%\_ c) #.%\- c))))))



;;; Declaration:     make-network-pathname (icp-connection-configuration)
;;; Type:	     Lisp function.
;;; Purpose:         Convert an ICP connection configuration to a string for the C
;;;                  network internals.
;;; Arguments:	     An ICP connection configuration.
;;; Return behavior: Returns a network-pathname constructed from
;;;                  icp-connection-configuration.  A network-pathname is a string
;;;                  containing three components separated by colons, e.g.,
;;;                  "TCP_IP:andorra:12345".  The components are:
;;;                  > Transport type.  This is canonicalized to be TCP_IP
;;;                  > Host name.
;;;                  > Connection address.
;;; Users:	     ICP internals (make-icp-connection in INT4).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Allocates memory for the network-pathname string.  The caller
;;;                  must reclaim this.
;;; Notes:           This function is used in distribution only.

(defun make-network-pathname (icp-connection-configuration)
  (let* ((protocol (first icp-connection-configuration))
	 (host (second icp-connection-configuration))
	 (listener  (third icp-connection-configuration))
	 (modified-protocol (copy-with-hyphens-changed-to-underscores
			      protocol)))
    (prog1
      (tformat-text-string "~a:~(~a~):~a"
			   modified-protocol
			   host
			   listener)
      (reclaim-text-string modified-protocol))))




;;; Declaration:     make-icp-connection (icp-connection-configuration)
;;; Type:	     Lisp function.
;;; Purpose:	     Set up an ICP connection to a remote ICP process.
;;; Arguments:	     An ICP connection configuration.
;;; Return behavior: Returns an icp-socket structure, or nil if the connection could
;;;                  not be made.
;;; Users:           G2 foreign functions (G2-FOREIGN), GSI (module GSI), GSPAN,
;;;                  G2-to-G2 communication (G2DS), G2 player (PLAYER).
;;; Prerequisites:   None.
;;; Side effects:    Can create and modify an ICP socket.
;;; Non-local exits: None.
;;; Memory impact:   Can allocate memory for an icp-socket structure.
;;; Notes:           > This is the primary function for making an ICP connection.
;;;                  > Due to the asynchronous nature of some network
;;;                    implementations, it is possible for this function to
;;;                    return an ICP socket even if no connnection can exist
;;;                    (e.g., the remote node is down).  This is essentially a
;;;                    bug, but much of the higher-level network code that uses
;;;                    this function has been adapted to co-exist with it.

;;; Make-icp-connection starts up an icp connection according to icp-connection-
;;; configuration if one does not already exist. If one exists then this function
;;; should return the existing icp socket.  

(def-substitution-macro local-icp-connection-p (icp-connection-configuration)
  (or (eq 'vms-process (first icp-connection-configuration))
      (eq 'localnet (first icp-connection-configuration))
      (equal (get-local-host-name) (second icp-connection-configuration))))

(defun make-icp-connection (icp-connection-configuration
			     &optional remote-system-name application-name
			     connect-timeout)
  (execute-body-if-icp-is-authorized-or-predicate-true
      (local-icp-connection-p icp-connection-configuration)
    (let ((icp-socket
	    (if (eq 'localnet (car icp-connection-configuration))
		(make-localnet-connection
		  (copy-if-text-string
		    (second icp-connection-configuration))
		  (or remote-system-name 'g2)
		  connect-timeout)
		(make-network-connection
		  icp-connection-configuration
		  connect-timeout))))
      (when icp-socket
	(setf (icp-socket-gsi-application-name icp-socket)
	      application-name)
	icp-socket))))
       
;; Is localnet really only supposed to be G2DS? (MHD 10/13/89)

;; Clean up grammar for connection configuration next! (See modules GSI, GSPAN, and
;; G2DS! (MHD 10/13/89)

;; Review, fix, and put the following back in if necessary (as top-level documentation
;; for the above function)!!
;; ;;; For now we will assume that
;; ;;; GSI has exclusive use of the icp socket and we have to create a new one for each 
;; ;;; gsi interface being activated.
;; (MHD 10/13/89)

;; Should this take a type-of-service argument -- one of GSI, G2DS, GSPAN, etc.?
;; (MHD 10/13/89)

;; Note that in the above function and the grammar down below, we've collapsed all of
;; the TCP/IP machine dependant connection configuation symbols to all use TCP-IP.
;; The machine dependant symbols still exist within current user KBs, so support for
;; those symbols must be maintained until we can be sure that of the network
;; configuration specifications have been reparsed.  This change was made in the 1.2
;; development code on 1/29/89.  -jra and blm 1/29/89  -- See GSI, GSPAN, or G2DS
;; for the grammar now. (MHD 10/13/89)







;;;; ICP Utility Functions



;;; Time-interval-elapsed-p ...

(defun time-interval-elapsed-p (time-interval-limit start-time)
  time-interval-limit start-time
  nil)

;; Define this for real, elsewhere, perhaps as a macro!



;; Get-all-command-line-keyword-arguments moved to INT4 (MHD 2/27/96)

;;; Declaration:     get-tcpip-listener-specification ()
;;; Type:	     Lisp function.
;;; Purpose:	     Get the desired TCP address of the network listener for this 
;;;                  process.
;;; Arguments:	     None.
;;; Return behavior: Returns an integer indicating the TCP/IP port to be used for the
;;;                  network listener, the symbol :default, or nil.  If the
;;;                  result is an integer, it comes either from the "-tcpport"
;;;                  keyword in the command-line that launched G2, or the
;;;                  environment variable "TCPPORT" that was in effect at the
;;;                  time G2 was launched (in that order).
;;;
;;;                  If the result is the symbol :default, the "-network"
;;;                  keyword is absent or specifies "tcpip", and neither
;;;                  "TCPPORT" nor "-tcpport" supply any value.  This result
;;;                  means that the underlying network layer is to concoct an
;;;                  appropriate TCP/IP address for the listener.
;;;
;;;                  If the result is nil, the command-line keyword "-network"
;;;                  appears at least once but none of the "-network" options
;;;                  specifies "tcpip".  In this case, any value supplied by
;;;                  "TCPPORT" or "-tcpport" is disregarded.  This result means
;;;                  that no attempt is to be made to establish a TCP/IP
;;;                  listener.
;;;
;;; Users:	     ICP internals (establish-g2-network-listeners in INT4).
;;; Prerequisites:   Must be called in a context where text-strings may be
;;;                  allocated, i.e., within a with-system-variables context.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           This function is used in distribution only, for the "generic"
;;;                  network protocol.  Formerly called get-or-use-default-tcp-port.

(defun get-tcpip-listener-specification ()
  (let* ((specific-network-transport-types? ; now a gensym list
	   (get-all-command-line-keyword-arguments #w"network"))
	 (tcpip-transport-type-specified-p
	   (loop for specific-network-transport-type
		     in specific-network-transport-types?
		 thereis
		 (string-equalw specific-network-transport-type
				#w"tcpip"))))
    (prog1
	(if (or (null specific-network-transport-types?)
		tcpip-transport-type-specified-p)
	    (or (get-command-line-keyword-argument-as-integer
		  #w"tcpport")
		(read-number-for-gensym-environment-variable
		  #w"TCPPORT")
		:default)
	    nil)
      (reclaim-gensym-list specific-network-transport-types?))))







;;;; TCP/IP under UNIX

(defun make-and-install-network-icp-socket
       (input-connection-handle
	output-connection-handle
	external-process-name
	initially-open-p
	&optional
	parent-listener?
	connect-timeout)
  (let ((icp-socket
	  (make-icp-socket 
	    external-process-name
	    'generic
	    input-connection-handle
	    output-connection-handle
	    nil
	    t
	    initially-open-p		; changed to use a parameter. -ncc, 16 May 1995 
	    parent-listener?
	    current-system-name
	    connect-timeout)))

    ;;   XXX this ASSUMES the input and output connection handles are eq.  this
    ;;   is currently (3 Apr 1996) true everywhere, but if that constraint is
    ;;   ever violated, network processing will fail to work.-ncc, 3 Apr 1996 
    (register-socket-to-handle icp-socket input-connection-handle)
    (add-to-active-icp-sockets icp-socket)
    icp-socket))

(defun make-and-install-network-listener
       (listener-handle network-address)

  (let* ((icp-socket
	   (make-icp-socket 
	     network-address     	;i.e. localhost:1111 etc.
	     'generic			; a network type socket
	     listener-handle		;
	     nil			; no output handle
	     nil			; no reading 
	     nil			; or writing will ever be done on this socket.
	     nil			; it's not running, it's a listener.
	     nil			; this is a listener socket, no parent
	     nil
	     nil)))                     ; no timeout
	 
    ;; mark it as a listener socket.
    (setf (icp-connection-state icp-socket) icp-socket-listening)
    (register-socket-to-handle icp-socket listener-handle) 
    (add-to-active-icp-sockets icp-socket)

    icp-socket))
  


;;; Declaration:     make-network-connection (network-pathname connection-type)
;;; Type:	     Lisp function.
;;; Purpose:	     Make an ICP connection using a platform-independent 
;;;                  description.
;;; Arguments:       network-pathname describes the connection to make (cf.
;;;                  make-network-pathname).  connection-type is ignored, as it
;;;                  present for reasons of compatibility with similar, obsolescent
;;;                  make-xxx-connection functions.
;;; Return behavior: Returns an icp-socket or nil if the connection could not be 
;;;                  made.
;;; Users:	     ICP internals (make-icp-connection in INT4).
;;; Prerequisites:   None.
;;; Side effects:    Can create and modify an ICP socket.
;;; Non-local exits: None.
;;; Memory impact:   Allocates memory for an icp-socket structure.
;;; Notes:           This function is used in distribution only, for the "generic"
;;;                  network protocol.

;;; jh, 7/28/94.  Added call to clear-fixnum-time-alarm because we may have
;;; intercepted the SIGALRM signal that G2 uses to invalidate its fixnum time
;;; cache.  (See my 1/14/94 note in /bt/ab/ext/c/tcp.c for a case where this is
;;; known to happen.  It is easy to imagine that SIGALRM inteception is not
;;; limited to TCP/IP, hence we fix it here rather than in tcp.c).  If this
;;; cache is never invalidated, whatever task happens to be running runs
;;; blithely along forever, since its timeslice never expires.  We must
;;; therefore invalidate the fixnum here, just in case.  The harm done by
;;; invalidating the fixnum cache is minor, since it merely regresses G2 to its
;;; previous behavior of calling get-fixnum-time.  This is probably acceptable
;;; since we don't intend to make network connections every time slice.

;;;  note 1: At this point, for tcp at least, we do not know if the connect has
;;;  completed, and we *do* that tcp connections can still fail to complete,
;;;  e.g. when an extant host and a bogus port are specified.  SO:
;;;
;;; The new optional arg 'supports-new-connect-scheme?' should be passed t if client
;;; can support the new 'icp-connection-connect-in-progress' state properly.
;;; this will default to the old marginal behaviour of assuming that the
;;; connection-handle returned by c-network-connect was a guaranteed socket.

;;; note 2: there is no leak here; the network-pathname string is reclaimed when
;;; the socket is reaped from the list of active ICP sockets in
;;; purge-inactive-icp-sockets.-ncc, 25 Sep 1995 

(defun make-network-connection (connection-configuration
				 &optional connect-timeout)
  (let* ((network-pathname (make-network-pathname connection-configuration))
	 (port-string (tformat-text-string "~a" (third connection-configuration)))
	 (secure-p (if (> (length connection-configuration) 3)
		       ;;Bug HQ-5455049 "Preexisting GSI connections try to connect via SSL":
		       ;;If the spec says DEFAULT, it means "not SSL" because it was saved
		       ;;in an older G2, so use NIL.
		       (if (eq (fourth connection-configuration) 'DEFAULT)
			   nil
			   (fourth connection-configuration))
		       secure-icp-default-p))
	 (connection-handle (network-connect network-pathname
					     (second connection-configuration)
					     port-string
					     secure-p)))
    (reclaim-text-string port-string)
    
    ;; see note 1 above
    (unless (>=f connection-handle 0)
      (reclaim-text-string network-pathname)
      (return-from make-network-connection nil))

    (let* ((nascent-socket (make-and-install-network-icp-socket
			     connection-handle
			     connection-handle
			     network-pathname
			     t nil connect-timeout)))
      (setf (icp-connection-state nascent-socket) icp-connection-connect-in-progress)

      nascent-socket)))

(defun setup-network-connection-for-connect (icp-socket &optional user-connect-callback)
  (when (and icp-socket
	     (eq (icp-connection-state icp-socket) icp-connection-connect-in-progress))
    (when user-connect-callback 
      (register-icp-callback 'icp-connect user-connect-callback icp-socket))
    (case (type-of-icp-connection icp-socket)
      (localnet
       (handle-icp-connect icp-socket))
      (generic
       (let ((connection-handle (icp-connection-handle (icp-input-port icp-socket))))
	 (when (network-connected-p connection-handle) ; immediate connection or immediate failure
	   (handle-network-connect
	     icp-socket
	     (c-network-get-last-error-code connection-handle)))))))
  icp-socket)

;; jh per jra, 1/19/94.  Added call to c-cancel_future_alarm_signal to
;; make-network-connection, so that any waiting done inside c-network-connect
;; will not be disrupted.  This was a problem with TCP on UNIX platforms, where
;; select() is called to wait for an "in-progress" socket to finish
;; initializing.  Since select() uses the same alarm signal as the one used to
;; invalidate the fixnum time cache, c-network-connect was failing even though
;; the in-progress socket was OK.  We also have some defensive programming in
;; tcpip_connect() in tcp.c.

;; NO, No, no, it's not because "select uses the same alarm signal", it's
;; because all unix signals interrupt the select statement, timer signals
;; included.  select() is blocked, and is interrupted by the alarm signal; this
;; forces it to return but indication *IS* given that the return was due to an
;; UNEXPECTED interruption, and NOT A TIMEOUT: timeout on select is indicated by
;; a zero return, and an interrupt is indicated by a failure (-1) return with
;; errno set to EINTR (or EAGAIN on some platforms, I think).  -ncc, 28 Aug 1996

(defun get-accept-pathname (accept-handle)
  (let ((result-code
	  (c-get-connection-pathname
	    accept-handle
	    gensym-environment-variable-buffer
	    #.maximum-gensym-environment-variable-length)))
    (interface-to-foreign-environment-access
      result-code
      :success-code 1)))


;; jh, 1/25/91.  The function accept-network-request-if-any, along with all
;; the other accept-xxx functions, now returns the ICP socket that was created, or
;; nil if unsuccessful.  This change is associated with the network security
;; project for 3.0.



(defun get-network-listener (position)
  ;; "TCP_IP:" is 7 characters; hostnames can be 256 characters; who knows how
  ;; big port numbers can be, but let's say nine digits, plus the colon.  That's
  ;; 273 characters.  Let's say 300 just to be sure.  -jv, 3/15/05
  (let* ((buffer-size 300)
	 (listener-buffer-as-simple-gensym-string ; sent to C for side effects
	  (obtain-simple-gensym-string buffer-size))
	 (length (c-get-network-listener position
					 listener-buffer-as-simple-gensym-string
					 buffer-size)))
    (prog1 (when (<f 0 length)
	     (copy-partial-text-string listener-buffer-as-simple-gensym-string length))
      (reclaim-gensym-string listener-buffer-as-simple-gensym-string))))




;;; Declaration:     extract-network-protocol (network-pathname)
;;; Type:	     G2 substitution macro.
;;; Purpose:	     Get the transport type from a network-pathname string.
;;; Arguments:	     A network pathname (cf. make-network-oathname).
;;; Return behavior: Returns a new string containing the transport type, which
;;;                  must be "TCP_IP".
;;; Users:	     ICP internals (get-local-host-addresses in INT4).
;;; Prerequisites:   Must be called in a context where text-strings may be
;;;                  allocated, i.e., within a with-system-variables context.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a string for the return value.  This function is
;;;                  typically called only once, so reclaiming the string is not
;;;                  necessary.  If this function is called an indefinite number of
;;;                  times, the caller must reclaim the returned string.
;;; Notes:           This function is used in distribution only, for the "generic"
;;;                  network protocol.

(def-substitution-macro extract-network-protocol (network-pathname)
  (twith-output-to-text-string
    (loop for i from 0 below (lengthw network-pathname)
	  as c = (charw network-pathname i)
	  until (char=w c #.%\:)
	  do (twrite-char c))))



;;; Declaration:     extract-network-address (network-pathname)
;;; Type:	     G2 substitution macro.
;;; Purpose:	     Get the connection address from a network-pathname string.
;;; Arguments:	     A network pathname (cf. make-network-pathname).
;;; Return behavior: Returns a new string containing the connection address.  The
;;;                  format of this string varies with the underlying transport
;;;                  type.  TCP addresses are C ints, typically four or five
;;;                  digits.
;;; Users:	     ICP internals (get-local-host-addresses in INT4).
;;; Prerequisites:   Must be called in a context where text-strings may be
;;;                  allocated, i.e., within a with-system-variables context.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a string for the return value.  This function is
;;;                  typically called only once, so reclaiming the string is not
;;;                  necessary.  If this function is called an indefinite number of
;;;                  times, the caller must reclaim the returned string.
;;; Notes:           This function is used in distribution only, for the "generic"
;;;                  network protocol.

(def-substitution-macro extract-network-address (network-pathname)
  (let ((delimiter-count 0))
    (twith-output-to-text-string
      (loop for i from 0 below (lengthw network-pathname)
	    as c = (charw network-pathname i)
	    until (=f delimiter-count 2)
	    do (if (char=w c #.%\:) (incff delimiter-count))
	    finally
	      (loop for j from i below (lengthw network-pathname)
		    as c = (charw network-pathname j)
		    until (char=w c #.%\:)
		    do (twrite-char c))))))


(defun get-local-host-addresses ()
  (loop with listener-count = (c-network-listener-count)
	with listeners = nil
	for listener-pos from 0 below listener-count
	for listener = (get-network-listener listener-pos)
	when listener
	  do (unless (string=w listener #w"UDP")
	       (setq listeners
		     (gensym-cons
		       (gensym-list
			 (extract-network-protocol listener)
			 (extract-network-address listener)
			 (=f (c-secure-socket-p
			       (ne-get-listener-handle listener-pos))
			     1))
		       listeners)))
	     (reclaim-if-text-string listener)
	  finally (return listeners)))


(defun reclaim-network-addresses (network-addresses)
  (reclaim-gensym-tree-with-text-strings network-addresses))


;;; Declaration:     get-unix-host-name ()
;;; Type:	     Lisp function.
;;; Purpose:	     Get the name of the network host.
;;; Arguments:	     None.
;;; Return behavior: Returns a new string containing the network host name, or nil
;;;                  if this could not be determined.
;;; Users:	     ICP internals (get-local-host-name in INT3).
;;; Prerequisites:   Must be called in a context where text-strings may be
;;;                  allocated, i.e., within a with-system-variables context.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a string for the return value.  This function is
;;;                  typically called only once, so reclaiming the string is not
;;;                  necessary.  If this function is called an indefinite number of
;;;                  times, the caller must reclaim the returned string.
;;; Notes:           This function is misnamed -- it is also able to get the names
;;;                  of non-UNIX hosts, such as Vaxstations.

;;; Get-unix-host-name returns either the host name for this unix machine as a
;;; text string or nil if that information is unavailable.

(defun get-unix-host-name ()
  (let* ((gensym-string (obtain-simple-gensym-string 100)) ; gets filled by C function
	 (length (gethostname-1 gensym-string (glength gensym-string t))))
    (prog1
	(cond ((<f length 0)
	       nil)
	      ((=f length 0)
	       ;; jv, 10/4/05 - this case was for VMS only.  Should it still be here?
	       nil)
	      (t
	       (copy-text-string-portion gensym-string 0 length)))
      (reclaim-gensym-string gensym-string))))




;;; Declaration:     establish-g2-network-listeners ()
;;; Type:	     Lisp function.
;;; Purpose:         Set up all ICP listeners for this process using the "generic"
;;;                  network protocol.
;;; Arguments:	     None.
;;; Return behavior: Returns t if at least one listener was established, nil
;;;                  otherwise.
;;; Users:	     ICP internals (generic-listener-initialized? in INT4).
;;; Prerequisites:   None.
;;; Side effects:    May create and modify icp-socket structures.  The returned
;;;                  value becomes the value of the system variable
;;;                  generic-listener-initialized?.
;;; Non-local exits: The following situations will cause the G2 process to shut 
;;; 		     down.
;;;                  > The command-line keyword "-tcpipexact" is present, the
;;;                    command-line option "-tcpport" is absent, and a listener
;;;                    could not be established at the default TCP port.
;;;                  > The command-line keyword "-tcpipexact" is present, the
;;;                    command-line option "-tcpport" is present, and a listener
;;;                    could not be established at the port given by that option.
;;; Memory impact:   May allocate icp-socket structures.
;;; Notes:           This function is used in distribution only, for the "generic"
;;;                  network protocol.

;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter icp-connection-succeeded-tag    1)
(defparameter icp-connection-failed-tag      -1)
(defparameter icp-noop-network-code-accessed -2)
)




(defun-allowing-unwind icp-connection-loss-notifier (icp-socket clean?)
  (declare (ignore clean?)
	   (ignore icp-socket))
  
  )


(defun-simple icp-connection-is-secure (icp-socket)
  (and icp-socket
       (not (eq (type-of-icp-connection icp-socket) 'localnet))
       (icp-input-port icp-socket)
       (icp-connection-handle (icp-input-port icp-socket))
       (=f (c-secure-socket-p (icp-connection-handle (icp-input-port icp-socket)))
	   1)))

(defun register-icp-connection-loss-callback-function (listener-socket? nascent-socket)
  (when listener-socket?
    (setf (listener-socket nascent-socket) listener-socket?))
  (register-icp-callback 'icp-connection-loss 'icp-connection-loss-notifier nascent-socket))

(defun get-tcp-listener-port-number (tcp-name)
  (let* ((length (lengthw tcp-name))
	 (first (loop for i from 0 below (1-f length)
		      when (char=w (charw tcp-name i) #.%\:)
			return i))
	 (second (when first
		   (loop for i from (1+f first) below (1-f length)
			 when (char=w (charw tcp-name i) #.%\:)
			   return i))))
    (when second
      (text-string-parse-integer tcp-name :start (1+f second)))))

(defun establish-g2-network-listeners ()

  ;; jh, 1/4/93.  Telewindows does not have any network listeners.  Not sure why
  ;; this wasn't done long ago, since spurious listeners cause a lot of problems
  ;; in Telewindows.
  ;; GSI establishes it's own network listeners elsewhere
  ;; (establish-gsi-extension-listeners in gsi.lisp) -ncc, 8/22/94
  ;;
  (unless (or (eq 'telewindows current-system-name)
	      (eq 'gsi current-system-name))
    (when (secure-icp-requested-p)
      (set-up-secure-icp 'default))
    (let* ((initial-listener-count (c-network-listener-count))
	   (tcp-port? (get-tcpip-listener-specification)) ; integer/:default/nil
	   (tcp-ip-exact-p (get-command-line-flag-argument #w"tcpipexact"))
	   (listen-status (c-network-listen
			    (cond
			      (tcp-port?
			       use-tcpip-protocol-only)
			      (t
			       use-no-network-protocols))
			    (if (memq tcp-port? '(nil :default))
				0
				tcp-port?)
			    (if tcp-ip-exact-p 1 0)
			    g2-product-tag
			    (if (secure-icp-requested-p) 1 0))))
      (case listen-status
	(#.icp-connection-succeeded-tag
	 ;; here we need to register the listeners with the network event handling abstraction.
	 ;; at present we assume at most two listeners for G2.
	 (let* ((listener-count (c-network-listener-count))
		(two-listeners? (=f (-f listener-count initial-listener-count) 2))
		(listener-handle-0
		  (ne-get-listener-handle 0))
		(listener-name-0 (get-network-listener 0))
		(listener-socket-0
		  (make-and-install-network-listener listener-handle-0 listener-name-0))
		(listener-handle-1?
		  (if two-listeners?
		      (ne-get-listener-handle 1)
		      nil))
		(listener-name-1
		  (when two-listeners?
		    (get-network-listener 1)))
		(listener-socket-1?
		  (when two-listeners?	
		    (make-and-install-network-listener listener-handle-1? listener-name-1)))
		(tcp-name (if (char=w #.%\T (charw listener-name-0 0))
			      listener-name-0
			      (if (and two-listeners? (char=w #.%\T (charw listener-name-1 0)))
				  listener-name-1
				  nil))))
	     
	   (when tcp-name
	     (setq tcp-listener-port-number (get-tcp-listener-port-number tcp-name)))

	   ;; register handler to be called when new ICP connections are created.
	   (register-icp-callback 'icp-accept
	     'register-icp-connection-loss-callback-function listener-socket-0)
	   (when two-listeners?
	     (register-icp-callback 'icp-accept
	       'register-icp-connection-loss-callback-function listener-socket-1?)))
	 
	 t)

	(#.icp-noop-network-code-accessed
	 (notify-user-in-parent-window
	   "ERROR: DECnet not supported by this product on this platform")
	 (shut-down-ab-process))
	(otherwise
	 (cond 
	   (tcp-ip-exact-p
	    (notify-user-in-parent-window
	      "ERROR: Could not make exact ICP connection~%")
	    (shut-down-ab-process))
	   (t nil)))))))


;; jh, 6/15/93.  Added lucid to the compiler switches for which
;; establish-g2-network-listeners does something non-trivial, since we now have the
;; Lucid environment working again.

;; jh, 11/13/91.  Added command-line flag argument so that a G2 user using the
;; -tcpport command-line keyword argument can additionally specify that G2 is
;; not to create a listener if it fails to create one on the exact port given.
;; This flags is -tcpipexact.

;; jh, 1/20/92.  Changed establish-g2-network-listeners to shut down G2 or
;; Telewindows if an -exact flag was present on the command line but a network
;; listener of the given -port could not be established.  The rationale is that
;; the user has explicitly requested an impossible configuration, and so the
;; program should exit.  If -exact is not present, the underlying machinery will
;; heuristically try to get a port whose name is "close" to the requested one.

;; jh, 10/15/92.  Changed establish-g2-network-listeners to be a no-op outside of
;; distribution.  This is so we can meta-dot the system variable
;; generic-listener-initialized?  from anywhere.  Previously, it would crash the
;; Lispms because it would call a foreign function, which is always an error on
;; Lispms.  (Foreign functions exist on Lispms so that they themselves can be
;; meta-dotted.)


;;; Declaration:     generic-listener-initialized?
;;; Type:	     G2 system variable.  
;;; Purpose:         Indicate if ICP listeners using the "generic" network protocol
;;;                  were successfully initialized.
;;; Arguments:	     N/A.
;;; Return behavior: N/A.
;;; Users:           ICP internals (report-listener-info-to-parent-window in INT4),
;;;                  G2 network info system procedures (FILE-IO).
;;; Prerequisites:   Initialized by establish-g2-network-listeners.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Initialized only once, so no run-time impact.

(def-system-variable generic-listener-initialized? INT4 
  nil)


;;; Declaration:     report-listener-info-to-parent-window ()
;;; Type:	     Lisp function.
;;; Purpose:	     Display information about the ICP listeners in this process.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     G2 launch machinery (RUN).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   This function allocates unreclaimable strings, and so is
;;;                  intended to be called only once.

(defun report-listener-info-to-parent-window ()
  (cond 
    (generic-listener-initialized?
     (multiple-value-bind (host-name port-list)
	 (get-raw-network-info)
       (let* ((left-hand-slot-lengths?
		(loop for (network-type) in port-list
		      collect (length network-type)
			using icp-cons))
	      (largest-left-hand-slot?
		(and left-hand-slot-lengths?
		     (loop for left-hand-slot-length
			       in (rest left-hand-slot-lengths?)
			   with max-slot-length
			     = (first left-hand-slot-lengths?)
			   when (>f left-hand-slot-length max-slot-length)
			     do (setq max-slot-length left-hand-slot-length)
			   finally (return max-slot-length)))))
	 (notify-user-at-console "host: ~a~%" host-name)
	 (when largest-left-hand-slot?
	   ;; following code should only be called when largest-left-hand-slot? is FIXNUM
	   (loop for (network-type address secure-p) in port-list
	       for slot-length in left-hand-slot-lengths?
	       as space-string = (make-wide-string
				   (-f largest-left-hand-slot? slot-length)
				   :initial-element #.%Space)
	       do (notify-user-at-console "~a~a: ~a~a~%" 
					  space-string
					  network-type
					  address
					  (secure-icp-string :network-type network-type :secure-p secure-p))
		  (reclaim-text-string space-string)))

	 (add-network-info-to-title-if-appropriate host-name port-list)
	 
	 (reclaim-icp-list left-hand-slot-lengths?)
	 (reclaim-raw-network-info host-name port-list))))
    (t (notify-user-at-console "WARNING: Could not make ICP connection~%"))))

;; jh, 1/21/92.  Modified report-listener-info-to-parent-window to duplicate more
;; closely what the "Network Info" window produces in G2.  The proliferation of
;; terminology was bound to confuse some users.





;;; Declaration:     add-network-info-to-title-if-appropriate (host-name port-list)
;;; Type:	     Lisp function.
;;; Purpose:	     Adds network (listener) info to the G2 application's title bar
;;;                  when the NETINFO command line flag argument is provided.
;;; Arguments:	     host-name and port-list are the return values of
;;;                  the get-raw-network-info function. This does not reclaim them. 
;;; Return behavior: None.
;;; Users:	     ICP internals (report-listener-info-to-parent-window in INT4).
;;; Prerequisites:   None.
;;; Side effects:    Appends network info to the existing title bar text.  Replaces
;;;                  system-window-title-and-info-text-string? with a text
;;;                  string, reclaiming old value if any.  All of that is disabled
;;;                  if the -no-native-window command line (flag) argument is
;;;                  specified.
;;; Non-local exits: None.
;;; Memory impact:   Allocates trivial bits of memory for the string.  Down in the
;;;                  Windows or X Window System bowels (ext/c) some bits of string 
;;;                  memory is also allocated.
;;; Notes:           The exact format of the appended text is:
;;;                    - [<host>: <port 1>: <port 2>: ...: <port n>]
;;;                  Note: we just put out the colon separated "ports" without
;;;                  labelling. The order should be stable, and should be easily
;;;                  recognizable without labels (TCP has integers).  We'd like
;;;                  TCP/IP to come first if there are other protocols.
;;;
;;;                  The variable `system-window-title-and-info-text-string?' is
;;;                  either nil or a text string corresponding to the last text
;;;                  string that was used as the title bar text.
;;;
;;;                  NOTE: this function and associated variable is never to be
;;;                  used except for G2.  The body of this function is
;;;                  eliminated except in G2 (system AB).
;;;
;;;                  Note: Decnet is no longer supported (jv, 10/4/05).
;;;
;;;                  I (MHD, as of 6/3/03) am not sure TCP/IP can ever NOT be
;;;                  present, but this would still work even if it were not.
;;;                  Other protocols could exist in theory, but do not at
;;;                  present.
;;;
;;;                  This practice began in G2 7.1 development.  Versions of G2
;;;                  prior to 7.1 did not have a generalize dynamic title text
;;;                  setting facility for both Windows and X until now.  It may
;;;                  be interesting to put some information on the Telewindows
;;;                  side later.  But not for now. Anyhow, this is only called
;;;                  once, and only for G2, before any connections have been
;;;                  made.
;;;
;;;                  One of the main benefits of this information is that it
;;;                  allows users to see at a glance at the G2 main window where
;;;                  to connect their Telewindows to.  This is increasingly
;;;                  needed in 7.x because the new/desireable Windows UI
;;;                  features are only available through Telewindows.
;;;
;;;                  Since this code is only used for G2, consider moving it, or
;;;                  somehow otherwise arranging for it not to appear in other
;;;                  systems (e.g., TW, GSI) to save space.

(def-system-variable system-window-title-and-info-text-string? int4 nil)

(defun add-network-info-to-title-if-appropriate (host-name port-list)
  host-name port-list			; ignored for non-G2 system
  (current-system-case
    ;; for G2 only, i.e., exclude for TW, GSI, etc:
    (ab 
      (when (getf command-line-arguments 'netinfo)
	(when system-window-title-and-info-text-string?
	  (reclaim-text-string system-window-title-and-info-text-string?))
	(setq system-window-title-and-info-text-string?
	      (twith-output-to-text-string
		(tformat "~a - " (system-window-title-string current-system-name))
		(tformat "[~a" host-name)
		(loop for (network-type address secure-p) in port-list
		      do (tformat ":~a~a" address (secure-icp-string
						    :network-type network-type
						    :use-default t
						    :secure-p secure-p)))
		(tformat "]")))
	(set-window-title system-window system-window-title-and-info-text-string?)))))





;;; Declaration:     make-localnet-connection (external-object-name)
;;; Type:	     Lisp function.
;;; Purpose:	     Make an ICP connection this process itself.
;;; Arguments:	     external-object-name is a symbol or string which names
;;;                  this ICP connection.
;;; Return behavior: An icp-socket structure.  It is always possible to make a
;;;                  localnet connection, so this function never returns nil.
;;; Users:	     ICP internals (make-icp-connection in INT4).
;;; Prerequisites:   None.
;;; Side effects:    Creates and modifies an ICP socket.
;;; Non-local exits: None.
;;; Memory impact:   Allocates memory for an icp-socket structure.
;;; Notes:           Note that there is no need for an
;;;                  accept- localnet-request-if-any function, analogous to
;;;                  accept-network-request-if-any, since the listening process is
;;;                  the same as the process requesting a connection.

(defun-simple make-localnet-socket (external-object-name
				     local-system-name connect-timeout)
  (let ((icp-socket
	  (make-icp-socket
	    external-object-name 'localnet 'localnet-handle 'localnet-handle
	    nil t t t local-system-name connect-timeout)))
    (add-to-active-icp-sockets icp-socket)
    icp-socket))

(defun make-localnet-connection (external-object-name
				  remote-system-name &optional connect-timeout)
  (let* ((main-icp-socket
	   (make-localnet-socket external-object-name
				 current-system-name connect-timeout))
	 (server-icp-socket
	   (make-localnet-socket (copy-if-text-string external-object-name)
				 remote-system-name connect-timeout)))
    (setf (icp-connection-state main-icp-socket) icp-connection-connect-in-progress)
    (setf (corresponding-localnet-socket main-icp-socket) server-icp-socket)
    (setf (corresponding-localnet-socket server-icp-socket) main-icp-socket)
    (case remote-system-name ; (execute-icp-accept-callbacks listener-socket server-socket)
      (gsi (current-system-case
	     ((ab gsi)
	      (register-gsi-connection-callbacks nil server-icp-socket))))
      (t   (register-icp-connection-loss-callback-function nil server-icp-socket)))
    main-icp-socket))



;;;; Socket Reclamation and Shutdown





;; Improve loops for object index space.  Shouldn't need 
;; (null object-index-space?) check.  Also, since plist, shouldn't 
;; have to check (vectorp object-index-space?).

(defun-void reclaim-icp-buffer-list (buffer-list)
  (loop for buffer = buffer-list then next-buffer
	while buffer
	for next-buffer = (icp-buffer-next buffer)
	do (reclaim-icp-buffer buffer)))

(defun-void reclaim-icp-buffers-for-port (icp-port)
  (reclaim-icp-buffer-list (icp-buffer-queue-head icp-port))
  (setf (icp-buffer-queue-head icp-port) nil)
  (setf (icp-buffer-queue-tail icp-port) nil))

(defun-void reclaim-icp-port (icp-port)
  (reclaim-icp-buffers-for-port icp-port)
  (let ((icp-port-for-reclaim icp-port))
    (reclaim-icp-port-internal icp-port)))

(defun-void reclaim-icp-input-port (icp-socket)
  (let* ((icp-input-port (icp-input-port icp-socket))
	 (system-name (icp-socket-local-system-name icp-socket))
	 (current-system-name (case system-name
				(g2 'ab)
				(t system-name))))
    (when icp-input-port
      (let ((callback-icp-buffer-list
	      (icp-buffer-for-callback icp-input-port)))
	(when callback-icp-buffer-list
	  (loop for icp-buffer = callback-icp-buffer-list
			       then next-icp-buffer
		while icp-buffer
		for next-icp-buffer = (icp-buffer-next icp-buffer)
		do (reclaim-icp-buffer icp-buffer)))
	(reclaim-icp-port icp-input-port)))))

(defun-void reclaim-icp-output-port (icp-socket)
  (let ((icp-output-port (icp-output-port icp-socket)))
    (when icp-output-port
      (setf (icp-output-port icp-socket) nil)
      (reclaim-icp-port icp-output-port))))

(defvar gsi-throw-to-run-loop-may-be-harmful-p nil)

(defun-void reclaim-icp-socket (icp-socket)
  (let ((gsi-throw-to-run-loop-may-be-harmful-p t))
    (reclaim-icp-input-port icp-socket)
    (reclaim-icp-output-port icp-socket)
    (runtime-current-system-case
      (gsi (maybe-call-gsi-shutdown-context-callback icp-socket))))
  (reclaim-icp-socket-internal icp-socket))




;;; Declaration:     remove-icp-port-entries-from-icp-object (icp-object)
;;; Type:	     Lisp function.  
;;; Purpose:         Remove references in an object to all ICP connections which
;;;                  contain corresponding objects for that object.
;;; Arguments:	     An ICP object.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (make-icp-object-index-space in INT3).
;;; Prerequisites:   This function is specified as the index-space-object-reclaimer
;;;                  for make-index-space in make-icp-object-index-space.  Thus, it
;;;                  will be called by reclaim-vector-of-index-subspace-vectors, the
;;;                  slot reclaimer for the vector-of-index-subspace-vectors slot of
;;;                  an index space, when the index space is reclaimed.  The index
;;;                  space is reclaimed by reclaim-inactive-icp-sockets (see above).
;;; Side effects:    Modifies the list of port entries.  This list sits on the
;;;                  access-form-for-corresponding-icp-object-map property of the
;;;                  symbol for the ICP object type.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims two gensym-conses per port entry.
;;; Notes:           > Note that for Telewindows ICP object types, this function
;;;                    should not do anything.  The reason is that icon and graph
;;;                    renderings are window-specific and these, along with gensym
;;;                    windows and workstations are all reclaimed together via
;;;                    reclaim-workstation.  Reclaim-workstation is called by
;;;                    close-connection-callback, the connection loss callback
;;;                    function which is called before reclaim-index-space when the
;;;                    socket is reclaimed.
;;;                  > Since in most cases, ICP objects are reclaimed before the
;;;                    index space is reclaimed, this function usually does nothing.
;;;                    The only exceptions are cases where the ICP object survives
;;;                    reclamation of the index space, for example:
;;;                      > symbols
;;;                      > cases where there is a one to many relation between ICP
;;;                        objects
;;;                      > cases where the reclaimer must be suspendable

;;; Remove-icp-port-entries-from-icp-object is specified as the
;;; index-space-object-reclaimer for make-index-space in
;;; make-icp-object-index-space.  Thus, it will be called by
;;; reclaim-vector-of-index-subspace-vectors, the slot reclaimer for the
;;; vector-of-index-subspace-vectors slot of an index space, when the index space
;;; is reclaimed.  The index space is reclaimed by reclaim-inactive-icp-sockets
;;; (see above) which also binds icp-port-being-reclaimed?.

;;; Note that for Telewindows ICP object types,
;;; remove-icp-port-entries-from-icp-object should not do anything.  This is
;;; because icon and graph renderings are window-specific and these, along with
;;; gensym windows and workstations are all reclaimed together via
;;; reclaim-workstation.  This is called by close-connection-callback, the
;;; connection loss callback function which is called before reclaim-index-space
;;; when the socket is reclaimed.

;;; Since in most cases, ICP objects are reclaimed before the index space is
;;; reclaimed, remove-icp-port-entries-from-icp-object usually does nothing.
;;; The only exceptions are cases where the ICP object
;;; survives reclamation of the index space, for example:
;;; 1.  symbols,
;;; 2.  cases where there is a one to many relation between ICP objects,
;;; 3.  cases where the reclaimer must be suspendable.
(defvar icp-socket-for-reclaim? nil)

;called by deregister-corresponding-icp-object and remove-icp-port-entries-from-icp-object.
(defun remove-icp-port-entries-from-icp-object-1
    (icp-object icp-object-type icp-port name-of-corresponding-icp-object-index-space shutdownp)
  (let* ((deregister-for-gsi-p
	   (runtime-current-system-case
	     (gsi (and (eq icp-object-type 'gsi-instance)
		       (not (eq name-of-corresponding-icp-object-index-space
				'item-with-handle-index-space))
		       (eq 'input (icp-port-direction icp-port))))
	     (t nil)))
	 (index-for-gsi
	   (runtime-current-system-case
	     (gsi
	       (when deregister-for-gsi-p
		 (get-icp-object-index-for-gsi-instance
		   icp-object icp-port))))))
    (runtime-current-system-case (gsi nil) (t deregister-for-gsi-p index-for-gsi nil))
    (let ((icp-port-entry-reclaimer? 
	    (reclaimer-for-icp-port-entry icp-object-type)))
      (when icp-port-entry-reclaimer?
	(funcall-simple-compiled-function
	  icp-port-entry-reclaimer? icp-object icp-port)))
    (runtime-current-system-case
      (gsi (when deregister-for-gsi-p
	     (let ((icp-socket-for-reclaim? (parent-icp-socket icp-port)))
	       (gsi-deregister-items-wrapper-for-known-sensor icp-object index-for-gsi))))
      (t name-of-corresponding-icp-object-index-space)))
  (when shutdownp
    (let ((shutdown-reclaimer?
	    (shutdown-reclaimer-for-icp-object icp-object-type)))
      (when shutdown-reclaimer?
	(funcall-simple-compiled-function
	  shutdown-reclaimer? icp-object icp-port)))))

(defun remove-icp-port-entries-from-icp-object (icp-object name-of-corresponding-icp-object-index-space shutdownp)
  (when icp-port-for-reclaim
    (let ((icp-object-type?
	    (icp-object-type-given-icp-object
	      icp-object name-of-corresponding-icp-object-index-space)))
      (when icp-object-type?
	(remove-icp-port-entries-from-icp-object-1
	  icp-object icp-object-type? icp-port-for-reclaim
	  name-of-corresponding-icp-object-index-space shutdownp)))))

(defun remove-icp-port-entries-from-icp-object-list (icp-object-list name-of-corresponding-icp-object-index-space shutdownp)
  (when (and icp-port-for-reclaim (consp icp-object-list))
    (loop for icp-object in icp-object-list
	  do (remove-icp-port-entries-from-icp-object
	       icp-object name-of-corresponding-icp-object-index-space shutdownp))))

(defun-void note-item-deleted-from-frame-serial-number-table (item)
  (current-system-case
    (ab
      (when (and item icp-port-for-reclaim)
	(let ((deregister-but-do-not-remove-from-table-p t)) ; our caller is already removing it
	  (remove-icp-port-entries-from-icp-object item 'item-index-space nil))))
    (t item)))


;; Consider making reclaim-vector-of-index-subspace-vectors and
;; reclaim-inactive-icp-sockets socket suspendable (low priority).

;; The simple-vector-p and symbolp check are to check if the icp-object has
;; already been reclaimed.  This is here only to prevent bombouts in 2.0 beta3.  I
;; have notes for a better (but more complicated) fix which should be implemented
;; after beta3!!!  - agh 5/17/90
;; These issues are now checked for by icp-object-type-given-icp-object.  -rh 9/4/96




;;; Declaration:     reclaim-index-space-location-and-corresponding-objects
;;;                    (icp-port 
;;;                     index 
;;; 	                name-of-corresponding-icp-object-index-space
;;; 	                icp-object)
;;; Type:	     Lisp function.
;;; Purpose:         Remove references in an object to a given ICP connection, which
;;;                  contains a corresponding object for that object.
;;; Arguments:       index is in the index space named by
;;;                  name-of-corresponding-icp-object-index-space.  This index gave
;;;                  icp-port the object corresponding to icp-object on the remote
;;;                  side.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (reclaim-icp-object-map in INT1).
;;; Prerequisites:   None.
;;; Side effects:    Modifies the list of port entries of icp-object.  This list
;;;                  sits at the place named by the
;;;                  access-form-for-corresponding-icp-object-map of the symbol for
;;;                  the ICP object type.  Modifies the index space named by
;;;                  name-of-corresponding-icp-object-index-space on both sides of
;;;                  the ICP connection.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims an index-space entry and a port-entry.  On the remote
;;;                  side, reclaims the corresponding object and its index-space
;;;                  entry.
;called by the functions named "RECLAIM-ICP-OBJECT-MAP-FOR-~A", defined by def-icp-object-type.
;also called by deregister-item-with-socket
;the caller reclaims the port entry
(defun-allowing-unwind reclaim-index-space-location-and-corresponding-objects
    (icp-object icp-port index index-space-name)
  (let* ((output-port-p (eq 'output (icp-port-direction icp-port)))
	 (actual-index-space-name
	   (index-space-name-for-icp-port index-space-name icp-port))
	 (index-space (index-space-for-icp-port actual-index-space-name icp-port))
	 (icp-object-from-index-space
	   (if (eq actual-index-space-name 'frame-serial-number)
	       (get-item-from-frame-serial-number index index-space)
	       (get-object-from-index-space-if-any index-space index))))
    (cond
      ((not (eq icp-object-from-index-space icp-object))
       (when (and (item-with-handle-index-space icp-port)
		  (eq actual-index-space-name 'item-index-space))
	 (deregister-item-with-handle-on-port index icp-object icp-port)))
      (t
       (let* ((will-ack-p
	       (let ((current-icp-socket (parent-icp-socket icp-port)))
		 (with-bifurcated-version-for-output
		     (acknowledge-deregister-corresponding-icp-object-icp-version)
		   nil
		   (and (eq actual-index-space-name 'item-index-space)
			(not (and output-port-p
				  deregister-corresponding-object?
				  deregister-and-register-item-p))))))
	      (send-p
		(send-reclaim-index-space-message-p icp-port nil actual-index-space-name)))
	 (unless (send-immediate-reclaim-index-space-message
		   (icp-output-port (parent-icp-socket icp-port))
		   index actual-index-space-name
		   nil output-port-p send-p)
	   (when send-p
	     (enqueue-reclaim-index-space-message
	       (icp-output-port (parent-icp-socket icp-port))
	       index actual-index-space-name
	       nil output-port-p t will-ack-p)))
	 (deregister-corresponding-icp-object
	   icp-object index actual-index-space-name icp-port t)))))) ; local

(defun-simple send-reclaim-index-space-message-p (icp-port ack-p actual-index-space-name)
  (let ((current-icp-socket (parent-icp-socket icp-port))
	(output-port-p (eq 'output (icp-port-direction icp-port))))
    (when (icp-connection-open-p current-icp-socket)
      (cond (ack-p
	     (with-appropriate-version-for-input
		 (acknowledge-deregister-corresponding-icp-object-icp-version)
	       t))
	    ((and output-port-p
		  (eq actual-index-space-name 'frame-serial-number)
		  (with-bifurcated-version-for-output (item-reference-icp-version)
		    t
		    (not (current-system-case
			   (ab (item-references-enabled-p current-icp-socket))
			   (t nil)))))
	     nil)
	    ((not output-port-p)
	     (and (or delete-corresponding-object? deregister-corresponding-object?)
		  (with-bifurcated-version (deregister-original-icp-object-icp-version)
		    nil t)))
	    (t
	     (and delete-corresponding-object? ; T by default, NIL for workstation and gensym-window
		  (with-appropriate-version (reclaim-remote-corresponding-object-icp-version)
		      t)
		  (or (not deregister-corresponding-object?) ; NIL by default, T in deregister-item-with-socket
		      (with-appropriate-version-for-output (gsi-item-registration-icp-version)
			t))))))))

(defun-simple send-immediate-reclaim-index-space-message (icp-output-port index index-space-name
							  ack-p output-port-p send-p)
  (when (and (not ack-p) output-port-p deregister-and-register-item-p)
    (when send-p
      (let ((icp-socket (parent-icp-socket icp-output-port)))
	(when (and (icp-connection-open-p icp-socket)
		   (not (icp-connection-being-shutdown? icp-socket)))
	  (writing-icp-message-group (icp-output-port)
	    (with-bifurcated-version (deregister-icp-objects-icp-version)
	      (send-icp-deregister-corresponding-icp-object index index-space-name)
	      (let ((index-list (icp-list index)))
		(send-icp-deregister-icp-objects
		  index-space-name
		  'deregister-and-register-corresponding-icp-object
		  index-list)
		(reclaim-icp-list index-list)))))))
    (deassign-index-in-index-space
      index
      (index-space-for-icp-port
	(index-space-name-for-icp-port index-space-name icp-output-port)
	icp-output-port))
    t))

(defparameter enqueue-reclaim-index-space-message-interval 0.25)	       

(defun-void enqueue-reclaim-index-space-message (icp-output-port index index-space-name
						 ack-p output-port-p local-p will-ack-p)
  (let* ((type (cond (ack-p
		      'acknowledge-deregister-corresponding-icp-object)
		     ((not output-port-p)
		      'deregister-original-icp-object)
		     (deregister-and-register-item-p
		      'deregister-and-register-corresponding-icp-object)
		     ((not deregister-corresponding-object?)
		      (if (and local-p (not will-ack-p))
			  'delete-icp-object-for-process-with-deassign
			  'delete-icp-object-for-process))
		     (t
		      (if (and local-p (not will-ack-p))
			  'deregister-corresponding-icp-object-with-deassign
			  'deregister-corresponding-icp-object))))
	 (icp-socket (parent-icp-socket icp-output-port))
	 (alist (icp-socket-deregister-icp-objects-alist icp-socket))
	 (index-space-name-entry
	   (or (assq index-space-name alist)
	       (let ((entry (icp-cons index-space-name nil)))
		 (setf (icp-socket-deregister-icp-objects-alist icp-socket)
		       (icp-cons entry alist))
		 entry)))
	 (type-entry
	   (or (assq type (cdr index-space-name-entry))
	       (let ((entry (icp-cons type nil)))
		 (setf (cdr index-space-name-entry)
		       (icp-cons entry (cdr index-space-name-entry)))
		 entry))))
    (icp-push index (cdr type-entry))
    (unless (schedule-task-in-place-p (icp-socket-deregister-icp-objects-task icp-socket))
      (with-future-scheduling
	  ((icp-socket-deregister-icp-objects-task icp-socket)
	   0
	   (+e (managed-float-value (clock-get current-real-time))
	       enqueue-reclaim-index-space-message-interval)
	   nil nil t)
	(send-queued-reclaim-index-space-messages icp-socket)))))

(defun-void send-queued-reclaim-index-space-messages (icp-socket)
  (cancel-task (icp-socket-deregister-icp-objects-task icp-socket))
  (loop with current-icp-socket = icp-socket
	with icp-output-port = (icp-output-port icp-socket)
	with icp-objects-alist
	  = (icp-socket-deregister-icp-objects-alist icp-socket)
	for index-space-element in icp-objects-alist
	for (index-space-name . type-alist) = index-space-element
	do
    (reclaim-icp-cons index-space-element)
    (loop for element in type-alist
	  for (type . type-index-list) = element
	  for index-list = type-index-list
	  do
      (reclaim-icp-cons element)
      (when (and (icp-connection-open-p icp-socket)
		 (not (icp-connection-being-shutdown? icp-socket)))
	(loop while index-list
	      do
	  (writing-icp-message-group (icp-output-port)
	    (with-bifurcated-version (deregister-icp-objects-icp-version)
	      (loop for i from 0 below 200
		    while (and index-list
			       (and (icp-connection-open-p icp-socket)
				    (not (icp-connection-being-shutdown? icp-socket))))
		    for index = (pop index-list)
		    do
		(case type
		  (acknowledge-deregister-corresponding-icp-object
		   (send-icp-acknowledge-deregister-corresponding-icp-object index index-space-name))
		  (deregister-original-icp-object
		   (send-icp-deregister-original-icp-object index index-space-name))
		  ((delete-icp-object-for-process
		     delete-icp-object-for-process-with-deassign)
		   (send-icp-delete-icp-object-for-process index index-space-name))
		  ((deregister-corresponding-icp-object
		     deregister-corresponding-icp-object-with-deassign
		     deregister-and-register-corresponding-icp-object)
		   (send-icp-deregister-corresponding-icp-object index index-space-name))))
	      (let* ((index-list-tail (nthcdr 199 index-list))
		     (next-index-list (cdr index-list-tail)))
		(when index-list-tail
		  (setf (cdr index-list-tail) nil))
		(send-icp-deregister-icp-objects
		  index-space-name type index-list)
		;;Now reset the original tail so we don't lose them below in the deassignment
		(when index-list-tail (setf (cdr index-list-tail) next-index-list))
		(setq index-list next-index-list))))))
      (case type
	((delete-icp-object-for-process-with-deassign
	   deregister-corresponding-icp-object-with-deassign)
	 (let ((actual-index-space-name
		 (index-space-name-for-icp-port index-space-name icp-output-port)))
	   (unless (eq actual-index-space-name 'frame-serial-number)
	     (loop with index-space
		     = (index-space-for-icp-port actual-index-space-name icp-output-port)
		   for index in type-index-list
		   do (deassign-index-in-index-space index index-space))))))
      (reclaim-icp-list type-index-list))
    (reclaim-icp-list type-alist)
	finally
	  (reclaim-icp-list icp-objects-alist)
	  (setf (icp-socket-deregister-icp-objects-alist icp-socket) nil)))







;;; Declaration:     remove-icp-object-from-index-space (icp-object icp-port index)
;;; Type:	     Lisp function.
;;; Purpose:         Remove references in an object to a given ICP connection, when
;;;                  the remote connection is closed.
;;; Arguments:       index is in the index space which is determined from the ICP
;;;                  object type of icp-object.  This index gave icp-port the object
;;;                  corresponding to icp-object on the remote side.
;;; Return behavior: No useful value.
;;; Users:	     G2-to-G2 communication (G2DS).
;;; Prerequisites:   None.
;;; Side effects:    Modifies the list of port entries of icp-object.  This list
;;;                  sits at the place named by the
;;;                  access-form-for-corresponding-icp-object-map of the symbol for
;;;                  the ICP object type.  Modifies the index space determined from the 
;;;                  ICP object type of icp-object on the local side.
;;; Non-local exits: None.
;;; Memory impact:   Recalims an index-space and a port entry.
;;; Possible bugs:   Modifies the index space by placing nil under index.  Does
;;;                  this make the entry unusable?  If so, we have a leak.
;;; Notes:           This function is is useful for cases where the
;;;                  RECLAIM-ICP-OBJECT-MAP-FOR-<icp-object-type> functions defined
;;;                  by def-icp-object-type can't be used.  This is the case for
;;;                  shutdown handlers like handle-g2ds-shutdown-server which
;;;                  reclaim the remote process g2ds-variable.  On the remote
;;;                  process, the icp object maps for icp objects are nil.  The
;;;                  RECLAIM-ICP-OBJECT-MAP-FOR-<icp-object-type> functions will
;;;                  therefore not remove these objects from the index spaces.
;;;                  Thus, remove-icp-object-from-index-space must be used instead
;;;                  in these cases.

;;; Remove-icp-object-from-index-space is useful for cases where the
;;; reclaim-icp-object-map...  functions defined by def-icp-object-type can't be
;;; used.  This is the case for shutdown handlers like handle-g2ds-shutdown-server
;;; which reclaim the remote process g2ds-variable.  On the remote process, the
;;; icp object maps for icp objects are nil.  The reclaim-icp-object-map...
;;; functions will therefore not remove these objects from the index spaces.
;;; Thus, remove-icp-object-from-index-space must be used instead in these cases.

;Currently, this is called only for objects of type g2ds-variable (rh, 10/13/96)
;This icp-port is an input-port, so there is no need to call deassign-index-in-index-space.
(defun remove-icp-object-from-index-space (icp-object icp-port index
					   name-of-corresponding-icp-object-index-space)
  (declare (ignore icp-object))
  (setf (get-from-icp-port icp-port index name-of-corresponding-icp-object-index-space)
	nil))

(def-icp-message-type shut-down-data-server ()
  (with-backtrace-for-internal-error 'received-shutdown-request
    (acknowledge-shutdown current-icp-socket)
    (shutdown-icp-socket-connection current-icp-socket)))

;; acknowledge-shutdown 

(defun-void acknowledge-shutdown (icp-socket)
  (when (and (icp-connection-open-p icp-socket)
	     (icp-connection-supports-shutdown-protocol? icp-socket))
    (writing-icp-message-group ((icp-output-port icp-socket))
      (send-icp-acknowledge-shutdown))
    (flush-icp-output-ports)))


;;; Message sent in response to shutdown-data-server message receipt.  shut
;;; down protocol says that once this message has been sent, and the buffers
;;; have been flushed out to the transport layer (i.e. the layer below our
;;; transport-abstraction layer in networks.c, i.e. the OS's transport protocol
;;; interpreter), then the connection is shut down and may be network_close'd
;;; and associated structures reclaimed.  -ncc, 3 Apr 1995
(def-icp-message-type acknowledge-shutdown ()
  (current-system-case
    (telewindows
      (setf (reason-for-shutdown? current-icp-socket) 'requested)))
  (shutdown-icp-socket-connection current-icp-socket))




;;; Declaration:     shutdown-icp-socket-connection (icp-socket &optional reason?)
;;; Type:	     Lisp function.
;;; Purpose:	     Close an ICP connection.
;;; Arguments:       icp-socket is the ICP connection to close.  This function first
;;;                  checks the icp-connection-open-p of icp-socket to make sure
;;;                  that shutdown only occurs once.  reason?  is typically a symbol
;;;                  describing the cause.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals:
;;;                    INT2: service-icp-sockets-awaiting-callback
;;;                          process-icp-sockets
;;;                          enqueue-next-icp-buffer-if-any
;;;                          advance-and-read-icp-byte-if-any
;;;                          handle-icp-messages 
;;;                  Also GSI (GSI-COMMON), Telewindows and G2 printing (TELESTUBS),
;;;                  G2 foreign functions (G2-FOREIGN), GSPAN, G2-to-G2
;;;                  communications (G2DS).
;;; Prerequisites:   None.
;;; Side effects:    This function resets the icp-connection-open-p and
;;;                  awaiting-callback?  slots of icp-socket, and then performs
;;;                  protocol-specific shutdown routines.  If the
;;;                  reason-for-shutdown?  slot of icp-socket is nil, then reason?
;;;                  is placed in that slot.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims the memory occupied by icp-socket.
;;; Notes:           This is the only recommended way to shut down an ICP connection.
;;; -paf! 10nov94  I modified this by removing TI, Symbolics, and localnet cruft that
;;;                I hope is not needed anymore.

;;; Shutdown-icp-socket-connection is the function to use for closing a
;;; connection; a connection should not be closed any other way.
;;; Shutdown-icp-socket-connection resets the icp-connection-open-p and
;;; awaiting-callback?  slots, and then performs protocol-specific shutdown
;;; routines.  It first checks icp-connection-open-p to make sure that this is
;;; only done once for an icp-socket.




;;; icp-socket-transacting-message-group, defined in int2, is bound specially
;;; when within a message group extent.  It's used here to defer executing the
;;; connection loss callbacks within the message group.  To execute the
;;; callback(s) within a message group would violate the assumption of
;;; atomicity of an icp message group.  -ncc, jra, jh 21 Jun 1995 

(defvar in-recursive-gsi-context nil)

(defun shutdown-icp-socket-connection (icp-socket &optional reason?)
  (when (=f (icp-connection-state icp-socket) icp-connection-closed)
    #+development
    (warn "tried to shut down a socket that wasn't open!")
    (return-from shutdown-icp-socket-connection nil))
  (unless (reason-for-shutdown? icp-socket)
    (setf (reason-for-shutdown? icp-socket) reason?))

  (close-and-disconnect-icp-socket-handle icp-socket)

  (when (or (not (eq icp-socket icp-socket-transacting-message-group))
	    in-recursive-gsi-context)
    (finalize-and-reclaim-icp-socket icp-socket)))



;;; Declaration:     flush-and-shutdown-icp-socket (icp-socket)
;;; Type:	     Lisp function.
;;; Purpose:         Mark an ICP connection for eventual shutdown (when the
;;;                  scheduler performs ICP tasks).
;;; Arguments:	     An ICP socket.
;;; Return behavior: No useful value.
;;; Users:           ICP internals (check-for-pending-icp-requests in INT2),
;;;                  Telewindows and G2 printing (TELESTUBS), G2 foreign functions
;;;                  (G2-FOREIGN), GSI (module GSI), G2-to-G2 communication (G2DS),
;;;                  G2 player (PLAYER).
;;; Prerequisites:   None.
;;; Side effects:    Sets the icp-connection-being-shutdown?  of icp-socket to
;;;                  non-nil as a signal to the scheduler.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           Typically, the process shutting down the connection sends an
;;;                  icp message to shut down the socket in the corresponding
;;;                  process.  This function should be called right after this
;;;                  message is sent.  Rather than shutting down the connection
;;;                  immediately, this functions makes arrangements for the
;;;                  scheduler to do it when performing ICP tasks.  The deferral
;;;                  allows for messages that have already been written to finish
;;;                  transmitting.  It also prevents any new messages from being
;;;                  written to the socket (writing-icp-message-group checks this
;;;                  slot).  The scheduler runs process-icp-sockets, which shuts
;;;                  down the connection when all icp messages have been
;;;                  transmitted.  It does so by calling
;;;                  shutdown-icp-socket-connection on icp-socket.

;;; Flush-and-shutdown-icp-socket should be used whenever closing a connection
;;; in a planned way to shut down the icp socket in the process that is closing
;;; the connection.
;;;
;;; Process-icp-sockets shuts down the connection when all icp messages have
;;; been transmitted by calling shutdown-icp-socket-connection for any socket
;;; which has made it to the "icp-connection-closed" state.
;;;
;;; icp-connection-supports-shutdown-protocol? is a new slot in the icp-socket
;;; structure which defaults to NIL, and in that state prevents the new shutdown
;;; protocol from being used.  The ICP user should set this switch when
;;; initializing new sockets, whenever she is sure that the peer is 4.0 or
;;; newer. -ncc, 4 Apr 1995 
;;; 

(defun flush-and-shutdown-icp-socket (icp-socket)
  (cancel-task (icp-connection-timeout-task? icp-socket))
  (cond ((icp-connection-open-p icp-socket)
	 (writing-icp-message-group ((icp-output-port icp-socket))
	   (send-icp-shut-down-data-server))
	 (flush-icp-output-ports)
	 (when (icp-connection-open-p icp-socket)
	   (cond ((icp-connection-supports-shutdown-protocol? icp-socket)
		  (setf (icp-connection-state icp-socket) icp-connection-awaiting-acknowledgement)
		  (current-system-case
		    (gsi (execute-icp-callbacks 'icp-connection-loss icp-socket t)))
		  (with-future-scheduling
		      ((shutdown-timeout-task? icp-socket)
		       2  ;XXX arbitrary choice of priority.  should be high.
		       (future-interval icp-socket-shutdown-handshake-timeout)
		       nil nil t)
		    (time-out-icp-socket icp-socket 'shutdown-timed-out-awaiting-acknowledgement)))
		 (t  ;it would be nice to indicate this was an asymmetric shutdown.
		  (shutdown-icp-socket-connection icp-socket)))))
	((icp-connection-in-progress-p icp-socket)
	 (deregister-all-icp-callbacks 'icp-connect icp-socket)
	 (register-icp-callback 'icp-connect 'shutdown-icp-socket-after-connect icp-socket))))

(defun-void shutdown-icp-socket-after-connect (icp-socket)
  (flush-and-shutdown-icp-socket icp-socket))  

(defun-void time-out-icp-socket (icp-socket reason)
  (shutdown-icp-socket-connection icp-socket reason))


(defun-void close-and-disconnect-all-sockets ()
  (dolist-safely (icp-socket active-icp-sockets)
    (when (=f (icp-connection-state icp-socket) icp-connection-running)
      (writing-icp-message-group ((icp-output-port icp-socket))
	(with-bifurcated-version-for-output (shutdown-protocol-icp-version)
	  (send-icp-shut-down-data-server)
	  (send-icp-acknowledge-shutdown))))) ; since we can't wait around for the reply
  (flush-icp-output-ports)
  (dolist-safely (icp-socket active-icp-sockets)
    (close-and-disconnect-icp-socket-handle icp-socket)
    #+development
    (finalize-and-reclaim-icp-socket icp-socket))
  #+development
  (reclaim-icp-sockets)
  (setq active-icp-sockets nil))




;;;; Validating ICP Message Exchanges

;; jh, 9/1/93.  This facility is still under construction as of this date.

;;; Def-icp-handshake specifies the sequencing of icp messages and emits a
;;; warning if they are out of sequence or if messages remain to be sent when an
;;; ICP connection is closed.  In the body of this macro, a list stands for a
;;; sequence of ICP messages that should be sent and received in the order given
;;; in that list.

;;; Def-icp-handshake enforces ordering by establishing a `handshaking state'
;;; that is traversed when certain ICP-related events occur, typically the
;;; sending or receiving of an ICP message with specified characteristics.  When
;;; the traversal fails, typically because an unexpected ICP message was
;;; encountered, a warning will be issued.  An unexpected ICP message is one
;;; that is in the set of messages mentioned in the def-icp-handshake form but
;;; appears in a place not specified by that form.

;; jh, 9/1/93.  We need to decide what form this warning will take in
;; distribution images.  Converting ICP message senders and handlers to check
;; the current handler sequence should have a negligible impact on performance.
;; By "negligible" we mean no worse than that introduced by ICP tracing.

;;; The ordering specified by def-icp-handshake is not total, in the following
;;; sense.  Unless the special keyword :no-interstices is used, other ICP
;;; messages may pass through the same ICP socket in between the messages
;;; specified by the list.

;;; To denote compound sequences, the head of a list in a def-icp-handshake body
;;; may be one of the following:
;;;   (1) the symbol || (i.e, the symbol whose printname is an empty string),
;;;       meaning that any one of the sequences specified by the sublists may
;;;       occur,
;;;   (2) the symbol *, meaning that 0 or more of this sequence may occur, or
;;;   (3) the symbol +, meaning that at most 1 of these subsequences may occur.
;;;   (4) the symbol ->, meaning that the events should occur in the sequence
;;;       given.  This is the default, and is usualy omitted.

;;; In each list in the def-icp-handshake body, certain forms cause the current
;;; state of handshaking to step forward when certain ICP messages or other
;;; ICP-related events occur.  Each such form is a called a `handshaking leaf
;;; form' or `handshaking leaf'.  Handshaking leaf forms include:
;;;   (1) symbols naming specific ICP messages (defined by def-icp-message),
;;;   (2) the keywords :end or :contiguous, or
;;;   (3) a list whose head names an ICP message and whose tail is a list of
;;;       keywords defined with def-icp-handshake-pattern (q.v. below) or the
;;;       special keywords :local or :remote

;;; If the head of a list inside a def-icp-handshake form is anything other than
;;; a compound sequence symbol (||, *, or +) or a valid handshaking leaf form,
;;; an error is signaled at macroexpansion time.

;; [Does the above mean that all ICP messages mentioned in the
;; def-icp-handshake-form must be pre-defined?  This may be moot, since
;; def-icp-message-type-code is in effect at macroexpansion time.]

;;; In general, an ICP message will step the handshaking state to the next leaf
;;; in the sequence upon sending or receiving an ICP message of the same name
;;; and whose arguments with the same name are equal.  For example, in the
;;; sequence
;;;   (dynamic-data-request dynamic-data-supplied)
;;; when handle-icp-dynamic-data-request message is called with a given ITEM
;;; argument, the handshaking state is stepped when
;;; send-icp-dynamic-data-supplied message is called with the same ITEM as
;;; argument.  Instead, a warning is issued when send-icp-dynamic-data-supplied
;;; is called through the same ICP socket but with a different ITEM argument.
;;; And other ICP messages may be called without warning, as long as they are
;;; not present anywhere in the enclosing def-icp-handshake form.

;; jh, 9/1/93.  Stepping handshake state is not yet implemented.

;;; An exception to the argument-matching behavior occurs if there is a
;;; def-icp-handshake-pattern definition for that leaf.  Then the predicate it
;;; defines overides the argument match that would otherwise occur.

;; jh, 9/1/93. Def-icp-handshake-pattern is not yet implemented.

;;; In the case of DDE-related handshaking :local happens to denote the client,
;;; but this is not mandatory for all def-icp-handshake sequences.

;;; There are two hardwired icp-handshake-patterns, :local and :remote, which
;;; specify who sends the message.  Handshaking leaves alternate between local
;;; and remote unless otherwise specified with these keywords, e.g.,
;;;   (dynamic-data-initiate dynamic-data-acknowledge)
;;; is short for
;;;   ((dynamic-data-initiate :local) (dynamic-data-acknowledge :remote))
;;; Unless overridden by a :remote keyword, each new embedded sublist starts
;;; with :local.

(defvar check-icp-handshaking-p nil)

(defun-for-macro icp-handshake-leaf-form-p (thing)
  (or (and (symbolp thing)
	   (or (memq thing '(:end :no-interstices))
	       t ;(get thing 'icp-message) ;add to def-icp-message!
	       ))
      (and (consp thing)
	   (let ((rest-of-thing? (rest thing)))
	     (and rest-of-thing?
		  (every #'keywordp rest-of-thing?))))))

(defun-for-macro make-icp-handshake-node (label event destination)
  (list label event destination))

(defparameter-for-macro icp-handshake-unique-label-counters nil)

(defparameter-for-macro compound-icp-handshake-event-tags '(|| * + ->))

(defun-for-macro initialize-icp-handshake-unique-label-counters ()
  (setq icp-handshake-unique-label-counters
	(loop for tag in compound-icp-handshake-event-tags
	      collect tag
	      collect 0)))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro disjunction-node-counter ()
  `(getf icp-handshake-unique-label-counters '||))

(defmacro any-number-node-counter ()
  `(getf icp-handshake-unique-label-counters '*))

(defmacro at-most-once-node-counter ()
  `(getf icp-handshake-unique-label-counters '+))

(defmacro root-name-counter (root-name)
  `(getf icp-handshake-unique-label-counters ,root-name 0))
)

(defun-for-macro all-icp-messages-in-handshake ()
  (loop for tag in compound-icp-handshake-event-tags
	do (remf icp-handshake-unique-label-counters tag))
  (loop for (message) on icp-handshake-unique-label-counters by #'cddr
	collect message))

(defun-for-macro make-new-node-from-icp-handshake-leaf
                 (handshake-leaf)
  (let* ((root-name (car handshake-leaf))
	 (label
	   (intern
	     (format nil "~A-~A"
		     root-name
		     (incf (root-name-counter root-name))))))
    (make-icp-handshake-node label handshake-leaf nil)))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro icp-handshake-node-label (handshake-node)
  `(first ,handshake-node))

(defmacro icp-handshake-node-leaf (handshake-node)
  `(second ,handshake-node))

(defmacro icp-handshake-node-destination (handshake-node)
  `(third ,handshake-node))
)

(defun-for-macro compound-icp-handshake-form-p (thing)
  (consp thing))

(defun-for-macro get-compound-handshake-tag (handshake-event)
  (let ((possible-tag (car handshake-event)))
    (if (memq possible-tag compound-icp-handshake-event-tags)
	possible-tag
	'->)))

(defun-for-macro canonicize-handshake-leaf
                 (handshake-leaf local-or-remote-default)
  (if (consp handshake-leaf)
      (let ((remote-p (memq :remote handshake-leaf))
	    (local-p (memq :local handshake-leaf)))
	(cond
	  ((and local-p remote-p)
	   (error "CANONICIZE-HANDSHAKE-LEAF: ~
                   :local and remote cannot co-exist in ~S"
		  handshake-leaf))
	  ((or local-p remote-p)
	   (values handshake-leaf
		   (if local-p :local :remote)))
	  (t (values `(,(first handshake-leaf)
			,local-or-remote-default
			,@(rest handshake-leaf))
		     local-or-remote-default))))
      (values `(,handshake-leaf ,local-or-remote-default)
	      local-or-remote-default)))

(defun-for-macro linearize-icp-handshake-sequence
                 (handshake-sequence
		   initial-nodes-to-backpatch)
  (loop for sequential-event in handshake-sequence
	for local-or-remote = :local
          then (case local-or-remote
		 (:local :remote)
		 (:remote :local))
	with new-nodes
	with nodes-to-return = nil
	with nodes-to-backpatch = initial-nodes-to-backpatch
	do
    (multiple-value-setq (new-nodes nodes-to-backpatch local-or-remote)
	(linearize-icp-handshake-body
	  sequential-event
	  nodes-to-backpatch
	  local-or-remote))
    (setq nodes-to-return (append nodes-to-return new-nodes))
	finally
	  (return
	    (values
	      nodes-to-return
	      nodes-to-backpatch))))

(defun-for-macro linearize-icp-handshake-disjunction
                 (handshake-disjunction
		   initial-nodes-to-backpatch)
  (let ((disjunction-label
	  (intern
	    (format nil "ICP-HANDSHAKE-DISJUNCTION-~A"
		    (incf (disjunction-node-counter))))))
    (loop for node-to-backpatch in initial-nodes-to-backpatch
	  do
      (setf (icp-handshake-node-destination node-to-backpatch)
	    disjunction-label))
    (loop for handshake-disjunct in handshake-disjunction
	  for disjunction-node
	    = (make-icp-handshake-node disjunction-label nil nil)
	  with all-disjunction-nodes = nil
	  with new-nodes
	  with nodes-to-return = nil
	  with nodes-to-backpatch
	  with backpatch-nodes-to-return = nil
	  do
      (multiple-value-setq (new-nodes nodes-to-backpatch)
	(linearize-icp-handshake-body
	  handshake-disjunct
	  (list disjunction-node)
	  :local))
      (setq nodes-to-return (append nodes-to-return new-nodes))
      (setq backpatch-nodes-to-return 
	    (append backpatch-nodes-to-return nodes-to-backpatch))
      (push disjunction-node all-disjunction-nodes)
	  finally
	    (return
	      (values (append (nreverse all-disjunction-nodes)
			      nodes-to-return)
		      backpatch-nodes-to-return)))))

(defun-for-macro linearize-icp-handshake-any-number-of-times
                 (handshake-body
		   initial-nodes-to-backpatch)
  (multiple-value-bind (new-nodes nodes-to-backpatch)
      (linearize-icp-handshake-body
	handshake-body
	initial-nodes-to-backpatch
	:local)
    (let* ((first-node (first new-nodes))
	   (first-label (icp-handshake-node-label first-node))
	   (any-number-label
	       (intern
		 (format nil "ICP-HANDSHAKE-ANY-NUMBER-~A"
			 (incf (any-number-node-counter)))))
	   (any-number-repeat-node
	     (make-icp-handshake-node any-number-label nil first-label))
	   (any-number-continue-node
	     (make-icp-handshake-node any-number-label nil nil)))
      (loop for node-to-backpatch in nodes-to-backpatch
	    do
	(setf (icp-handshake-node-destination node-to-backpatch)
	      any-number-label))
      (values `(,@new-nodes
		,any-number-repeat-node
	        ,any-number-continue-node)
	      (list any-number-continue-node)))))

(defun-for-macro linearize-icp-handshake-at-most-one-time
                 (handshake-body
		   initial-nodes-to-backpatch)
  (multiple-value-bind (new-nodes nodes-to-backpatch)
      (linearize-icp-handshake-body
	handshake-body
	initial-nodes-to-backpatch
	:local)
    (let* ((first-node (first new-nodes))
	   (first-label (icp-handshake-node-label first-node))
	   (at-most-one-label
	     (intern
	       (format nil "ICP-HANDSHAKE-AT-MOST-ONCE-~A"
		       (incf (at-most-once-node-counter)))))
	   (at-most-skip-node
	     (make-icp-handshake-node first-label nil at-most-one-label))
	   (at-most-join-node
	     (make-icp-handshake-node at-most-one-label nil nil)))
      (loop for node-to-backpatch in nodes-to-backpatch
	    do
	(setf (icp-handshake-node-destination node-to-backpatch)
	      at-most-one-label))
      (values `(,(first new-nodes)
		,at-most-skip-node
		,@new-nodes
	        ,at-most-join-node)
	      (list at-most-join-node)))))

;;; `Linearize-icp-handshake-body' is a helper function for the macro
;;; def-icp-handshake.  It takes three args
;;;   (1) a subform from the body of a def-icp-handshake
;;;   (2) a list of nodes which need their destinations filled in, initially
;;;       containing only the start node.
;;; and returns three values:
;;;   (1) a list of new nodes 
;;;   (2) the subset of (1) that needs backpatching
;;;   (3) the default choice of :local or :remote, for use by the caller if
;;;       unspecified there
;;; Nodes are of the form ( label event-spec destination-label )

(defun-for-macro linearize-icp-handshake-body
                 (handshake-body
		   nodes-to-backpatch
		   local-or-remote-default)
  (cond
    ((eq :end handshake-body)
     (loop for node-to-backpatch in nodes-to-backpatch
	   do
       (setf (icp-handshake-node-destination node-to-backpatch) :end))
     (values nil nil))
    ((icp-handshake-leaf-form-p handshake-body)
     (multiple-value-bind (handshake-leaf local-or-remote-used)
	 (canonicize-handshake-leaf handshake-body local-or-remote-default)
       (let ((new-node
	       (make-new-node-from-icp-handshake-leaf handshake-leaf)))
	 (loop for node-to-backpatch in nodes-to-backpatch
	       do
	   (setf (icp-handshake-node-destination node-to-backpatch)
		 (icp-handshake-node-label new-node)))
	 (values (list new-node)
		 (list new-node)
		 local-or-remote-used))))
    ((compound-icp-handshake-form-p handshake-body)
     (let ((compound-tag (get-compound-handshake-tag handshake-body)))
       (case compound-tag
	 (-> (linearize-icp-handshake-sequence
	       (if (eq (first handshake-body) '->)
		   (rest handshake-body)
		   handshake-body)
	       nodes-to-backpatch))
	 (|| (linearize-icp-handshake-disjunction
	       (rest handshake-body)
	       nodes-to-backpatch))
	 (* (linearize-icp-handshake-any-number-of-times
	      (rest handshake-body)
	      nodes-to-backpatch))
	 (+ (linearize-icp-handshake-at-most-one-time
	      (rest handshake-body)
	      nodes-to-backpatch))
	 (otherwise (error "LINEARIZE-ICP-HANDSHAKE-BODY: ~
                            unknown compound tag ~A"
			   compound-tag)))))
      (t (error "LINEARIZE-ICP-HANDSHAKE-BODY: ~
                 unknown handshake body ~S"
		handshake-body))))

(defparameter icp-handshake-registry nil)

(defmacro def-icp-handshake (name &body body)
  (cond
    ((eq current-system-being-loaded 'gsi) nil)
    (t (initialize-icp-handshake-unique-label-counters)
       (let* ((start-leaf (make-icp-handshake-node :start nil nil))
	      (nodes-to-backpatch (list start-leaf)))
	 (multiple-value-bind (all-nodes final-nodes-to-backpatch)
	     (linearize-icp-handshake-body
	       body
	       nodes-to-backpatch
	       :local)
	   (loop for node-to-backpatch in final-nodes-to-backpatch
		 do
	     (setf (icp-handshake-node-destination node-to-backpatch) :end))
	   `(pushnew (list ',name
			   ',(all-icp-messages-in-handshake)
			   ',(cons start-leaf all-nodes))
		     icp-handshake-registry
		     :key #'first))))))

(def-icp-handshake dynamic-data-cold-link
  ;; The conversation opens.
  (dynamic-data-initiate dynamic-data-acknowledge)

  ;; After the request, the server either sends the data once, or refuses.
  ;; Refusal ends the conversation.
  (|| (dynamic-data-request
	dynamic-data-supplied
	(dynamic-data-acknowledge :positive))
      (dynamic-data-request (dynamic-data-acknowledge :negative) :end))

  ;; The conversation closes.
  (dynamic-data-terminate dynamic-data-terminate :end)
  )

(def-icp-handshake dynamic-data-hot-link
  ;; The conversation opens.
  (dynamic-data-initiate dynamic-data-acknowledge)

  ;; At the client's request, the server either undertakes to send new data to
  ;; the client whenever that data is updated, or refuses.  Refusal ends the
  ;; conversation.
  (|| ((dynamic-data-advise :hot) (dynamic-data-acknowledge :positive))
      ((dynamic-data-advise :hot) (dynamic-data-acknowledge :negative) :end))

  ;; The server sends new data to the client any number of times.
  (* (dynamic-data-supplied :remote) (dynamic-data-acknowledge :local))

  ;; At some point, the client informs the server that the data is no longer
  ;; required.
  (dynamic-data-unadvise dynamic-data-acknowledge)

  ;; The conversation closes.
  (dynamic-data-terminate dynamic-data-terminate :end)
  )
  
(def-icp-handshake dynamic-data-warm-link
  ;; The conversation opens.
  (dynamic-data-initiate dynamic-data-acknowledge)

  ;; At the client's request, the server undertakes to inform the client when
  ;; the data changes without actually sending the new data, or refuses.
  ;; Refusal ends the conversation.
  (|| ((dynamic-data-advise :warm) (dynamic-data-acknowledge :positive))
      ((dynamic-data-advise :warm) (dynamic-data-acknowledge :negative) :end))

  ;; The server informs the client of the new data any number of times.  At any
  ;; of these times, the client can ask the server for tha actual data.  (Note
  ;; that something is wrong with the handshaking if the client requests new
  ;; data without first being notified by the server.)
  (* (dynamic-data-supplied :remote :null-item) (dynamic-data-acknowledge :local)
     (+ (dynamic-data-request dynamic-data-supplied dynamic-data-acknowledge)))

  ;; At some point, the client informs the server that the data is no longer
  ;; required.
  (dynamic-data-unadvise dynamic-data-acknowledge)

  ;; The conversation closes.
  (dynamic-data-terminate dynamic-data-terminate :end)
  )

;; jh, 9/1/93.  More to come.

;; End file with CR


;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INT3B

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson, Lowell B. Hawkinson, Mark H. David, et al.

;; jh, 8/14/96.  Split INT3 into INT3A and INT3B to appease the Watcom compiler
;; on the Windows platform. 

;;; File name:		     INT3B.LISP
;;; File location:	     /bt/ab/lisp/
;;; Code control:	     CVS
;;; Purpose:	             ICP value types, object types, and flow control.   
;;; Contents:                Messages to manage ICP index spaces.  I-am-alive
;;;                          flow control machinery.
;;; This file depends on:    Preceding .LISP files in the system load ordering.
;;; Dependent files:         Subsequent .LISP files in the system load ordering.
;;; Role in products:	     Linked into G2 and Telewindows.
;;; Role in development:     None.
;;; Testing harness:         The development function
;;;                          run-icp-text-string-reader-tests tests some aspects of
;;;                          the ICP text-string value type.  The function 
;;;                          dump-icp-buffer displays the contents of an ICP buffer.
;;; Performace requirements: These functions and macros are central to ICP 
;;;                          operation.  Performance is critical.
;;; Major Entities:          [ICP message type] enlarge-corresponding-icp-object-
;;;                                               index-space
;;;                          [ICP message type] delete-icp-object-for-process
;;;                          [ICP message type] nop
;;;                          [ICP value type]   number-of-icp-bytes-of-fill
;;;                          [ICP value type]   unsigned-integer-or-nil
;;;                          [ICP value type]   float
;;;                          [ICP value type]   double-float
;;;                          [function]         encode-double-float
;;;                          [function]         decode-double-float
;;;                          [ICP message type] define-dummy-object
;;;                          [ICP message type] end-message-block
;;;                          [function]         initialize-I-am-alive-info
;;;                          [function]         reclaim-i-am-alive-info?
;;;                          [function]         do-i-am-alive-processing
;;;                          [ICP message type] i-am-alive
;;;                          [ICP message type] message-group-id
;;;                          [function]         get-local-host-name
;;;                          [function]         get-current-icp-contact-port-number-
;;;                                               or-name-if-any
;;;                          [ICP message type] connection-denied
;;;                          [ICP message type] connection-shutdown-imminent
;;;                          [function]         warn-disallowed-icp-listener-
;;;                                               connectons

;; Forward references

;; To GRAMMAR7

(declare-forward-reference disconnect-dead-connections?-from-system-table function)
(declare-forward-reference dead-connection-timeout-from-system-table function)

;; To INT4

(declare-forward-reference get-unix-host-name function)
(declare-forward-reference send-reclaim-index-space-message-p function)
(declare-forward-reference enqueue-reclaim-index-space-message function)

;; To G2-RPC3

(declare-forward-reference name-for-local-home function)

;; To TELESTUBS

(declare-forward-reference handle-unclogged-connection-if-necessary function)

;; To GSI

(declare-forward-reference gsi-sensor-p-function function)

(declare-forward-reference signal-gsi-icp-message-out-of-synch-case-2-error
			   function)
(declare-forward-reference gsi-deregister-items-wrapper-for-known-sensor
			   function)

(declare-forward-reference gsi-connection-denied variable)
(declare-forward-reference gsi-no-license variable)

(declare-forward-reference gsi-local-home variable)
(declare-forward-reference gsi-instance-value-function function)

(declare-forward-reference reclaim-icp-port-entry-for-gsi-instance function)
(declare-forward-reference reclaim-icp-port-entry-for-registered-item function)
(declare-forward-reference remove-icp-port-entries-from-icp-object-1 function)

(declare-forward-reference note-item-deleted-from-frame-serial-number-table function)
(declare-forward-reference notify-user function)
(declare-forward-reference flush-and-shutdown-icp-socket function)



;;;; Utility ICP Message Types

;;; Declaration:     enlarge-corresponding-icp-object-index-space
;;; 		       (name-of-corresponding-icp-object-index-space
;;; 		        new-index-limit-plus-one)
;;; Type:		 ICP message type.
;;; Purpose:	     Enlarge a corresponding ICP object index space in a remote 
;;;                  ICP process.
;;; Arguments:       name-of-corresponding-icp-object-index-space is of ICP object
;;;                  type symbol and is the name of the corresponding ICP object
;;;                  index space at the other end of the ICP connection
;;;                  current-icp-port.  new-index-limit-plus-one is of ICP type
;;;                  unsigned integer and represents one more that the largest
;;;                  desired index after enlargement.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (assign-corresponding-icp-object-index in INT3).
;;; Prerequisites:   None.
;;; Side effects:    Modifies a remote corresponding ICP object index space.
;;; Non-local exits: None.
;;; Memory impact:   Causes a remote ICP process to allocate memory to enlarge its
;;;                  index space.  If name-of-corresponding-icp-object-index-space
;;;                  is a new symbol on the remote side, memory must be allocated
;;;                  there to store that symbol and its pname in the symbol table.

;;; Enlarge-corresponding-icp-object-index-space enlarges a corresponding icp
;;; object index space in the icp node at the other end of the connection
;;; represented by current-icp-port.

(defun handler-for-enlarge-corresponding-icp-object-index-space
    (name-of-corresponding-icp-object-index-space new-index-limit-plus-one)
  (declare (ignore name-of-corresponding-icp-object-index-space))
  (enlarge-index-space
    (standard-icp-object-index-space current-icp-port)
    (-f new-index-limit-plus-one 1)))
  
(def-icp-message-type enlarge-corresponding-icp-object-index-space
    ((symbol name-of-corresponding-icp-object-index-space)
     (unsigned-integer new-index-limit-plus-one))
  (handler-for-enlarge-corresponding-icp-object-index-space
    name-of-corresponding-icp-object-index-space
    new-index-limit-plus-one))




;;; Declaration:     icp-port-for-reclaim
;;; Type:	     G2 system variable.
;;; Purpose:	     Provide the ICP port currently being reclaimed.
;;; Value:           If no ICP port is being reclaimed, this variable is bound to
;;;                  nil.  Otherwise, it is bound to the icp-port structure being
;;;                  reclaimed.
;;; Return behavior: N/A.
;;; Users:	     ICP internals:
;;;                    INT4: reclaim-inactive-icp-sockets
;;;                          remove-icp-port-entries-from-icp-object
;;; Prerequisites:   Bound by reclaim-inactive-icp-sockets.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

(def-system-variable icp-port-for-reclaim INT3B nil)



;;; Declaration:     delete-icp-object-for-process
;;;                    (corresponding-icp-object-index
;;; 	                name-of-corresponding-icp-object-index-space)
;;; Type:	     ICP message type.
;;; Purpose:	     Delete a remote ICP object.
;;; Arguments:       corresponding-icp-object-index is the index of the object to
;;;                  delete, of ICP value type corresponding-icp-object-index.
;;;                  name-of-corresponding-icp-object-index-space is a symbol naming
;;;                  the index space from which to delete the object.
;;; Return behavior: No useful value.
;;; Users:           ICP internals
;;;                  (reclaim-index-space-location-and-corresponding-objects in
;;;                  INT4).
;;; Prerequisites:   None.
;;; Side effects:    Modifies the corresponding object index space named by
;;;                  name-of-corresponding-icp-object-index-space.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims the memory occupied by the object itself and its
;;;                  entry in the corresponding object index space.

(defvar deregister-and-register-item-p nil)
(defvar deregister-but-do-not-remove-from-table-p nil)

;a hook for a breakpoint
(defun-void note-no-object-in-deregister-corresponding-icp-object
    (icp-object index original-index-space-name icp-port localp)
  (declare (ignore index original-index-space-name icp-port localp))
  icp-object
  nil)

(defun deregister-corresponding-icp-object (icp-object? index original-index-space-name icp-port localp)
  (let* ((outputp (eq 'output (icp-port-direction icp-port)))
	 (index-space-name (index-space-name-for-icp-port original-index-space-name icp-port))
	 (index-space (index-space-for-icp-port index-space-name icp-port))
	 (index-space-icp-object?
	   (if (eq index-space-name 'frame-serial-number)
	       (get-item-from-frame-serial-number index index-space)
	       (get-object-from-index-space-if-any index-space index))))
    (when (and icp-object? (not (eq icp-object? index-space-icp-object?)))
      (note-no-object-in-deregister-corresponding-icp-object
	icp-object? index original-index-space-name icp-port localp))
    (unless icp-object?
      (setq icp-object? index-space-icp-object?))
    (unless icp-object?
      (return-from deregister-corresponding-icp-object nil))
    (let* ((icp-object-type? (icp-object-type-given-icp-object
			       icp-object? index-space-name)))
      (if (eq index-space-name 'frame-serial-number)
	  (let ((icp-port-for-reclaim icp-port))
	    (unless deregister-but-do-not-remove-from-table-p
	      (delete-item-from-frame-serial-number-table index index-space)))
	  (progn
	    (store-object-in-index-space index-space index nil)
	    (remove-icp-port-entries-from-icp-object-1
	      icp-object? icp-object-type? icp-port original-index-space-name nil)
	    (when (and outputp (not localp))
	      (deassign-index-in-index-space index index-space))))
      (unless outputp
	(when (or (eq 'gsi-instance icp-object-type?)
		  (eq 'registered-item icp-object-type?))
	  (let ((items-registered-with-handle
		  (items-registered-with-handle-on-port index icp-port)))
	    (when items-registered-with-handle
	      (loop for item in items-registered-with-handle
		    do (current-system-case
			 (gsi (reclaim-icp-port-entry-for-gsi-instance item icp-port))
			 (ab  (reclaim-icp-port-entry-for-registered-item item icp-port))))
	      (reclaim-gensym-list items-registered-with-handle)
	      (clear-items-registered-with-handle-on-port index icp-port)))))
      (when (and (not localp) (not outputp) (not deregister-and-register-item-p)
		 (eq index-space-name 'item-index-space))
	(let ((icp-output-port (icp-output-port (parent-icp-socket icp-port))))
	  (when (send-reclaim-index-space-message-p icp-output-port t index-space-name)
	    (enqueue-reclaim-index-space-message
	      icp-output-port index original-index-space-name
	      t t nil nil)))) ; ack-p output-port-p local-p will-ack-p
      (values icp-object? icp-object-type? index-space-name outputp))))

(defun-void handle-delete-corresponding-icp-object (index index-space-name icp-port)
  (multiple-value-bind (icp-object? icp-object-type?)
      (deregister-corresponding-icp-object
	nil index index-space-name icp-port
	nil)  ; remote
    (when icp-object?      
      #+development
      (when notify-when-reclaiming-icp-object?
	(format t "Icp object being reclaimed is ~s~% index = ~d~%"
		icp-object? index))
      (when icp-object-type?
	(let ((reclaimer-for-icp-object?
		(reclaimer-for-icp-object icp-object-type?)))
	(when reclaimer-for-icp-object?
	  (funcall-simple-compiled-function reclaimer-for-icp-object? icp-object?)))))))

(def-icp-value-writer deregister-corresponding-icp-object-index-space-name
  (with-bifurcated-version-for-output
      (deregister-corresponding-icp-object-index-space-name-icp-version)
    nil
    (write-icp-symbol-as-value-type deregister-corresponding-icp-object-index-space-name)))

(def-icp-value-reader deregister-corresponding-icp-object-index-space-name
  (with-bifurcated-version-for-input
      (deregister-corresponding-icp-object-index-space-name-icp-version)
    'standard-icp-object-index-space
    (read-icp-symbol-as-value-type)))

;sent only by reclaim-index-space-location-and-corresponding-objects
(def-icp-message-type deregister-corresponding-icp-object
                      (corresponding-icp-object-index
		       (deregister-corresponding-icp-object-index-space-name
			 name-of-corresponding-icp-object-index-space))
  (deregister-corresponding-icp-object
    nil
    corresponding-icp-object-index
    name-of-corresponding-icp-object-index-space
    current-icp-port
    nil))   ; remote

(def-icp-message-type deregister-original-icp-object
                      (corresponding-icp-object-index
		       (symbol-as-value-type
			 name-of-corresponding-icp-object-index-space))
  (deregister-corresponding-icp-object
    nil
    corresponding-icp-object-index
    name-of-corresponding-icp-object-index-space
    (icp-output-port (parent-icp-socket current-icp-port))
    nil))   ; remote

;;; Delete-icp-object-for-process is a message type that can be used to delete any
;;; icp object type in a remote process.  It is called by the corresponding icp
;;; object map reclaimer function generated by def-icp-object-type.

;sent by reclaim-index-space-location-and-corresponding-objects
;  and g2-reclaim-remote-side-for-deactivate-object-passing
;         called by reclaim-sending-and-receiving-resumable-object
;           called by preflight-resumable-object-with-catch-handlers
(def-icp-message-type delete-icp-object-for-process
		      (corresponding-icp-object-index
			(symbol
			  name-of-corresponding-icp-object-index-space))
  (handle-delete-corresponding-icp-object
    corresponding-icp-object-index
    name-of-corresponding-icp-object-index-space
    current-icp-port))

(defun-void handle-acknowledge-deregister-corresponding-icp-object
            (corresponding-icp-object-index name-of-corresponding-icp-object-index-space)
  (let* ((icp-port (icp-output-port (parent-icp-socket current-icp-port)))
	 (index-space-name (index-space-name-for-icp-port
			     name-of-corresponding-icp-object-index-space
			     icp-port))
	 (index-space (index-space-for-icp-port index-space-name icp-port)))
    (deassign-index-in-index-space corresponding-icp-object-index index-space)))

(def-icp-message-type acknowledge-deregister-corresponding-icp-object
                      (corresponding-icp-object-index
			(symbol
			  name-of-corresponding-icp-object-index-space))
  (handle-acknowledge-deregister-corresponding-icp-object
    corresponding-icp-object-index name-of-corresponding-icp-object-index-space))

(def-icp-value-writer deregister-icp-objects-operation
  (write-icp-byte
    (case deregister-icp-objects-operation
      (deregister-corresponding-icp-object               0)
      (deregister-corresponding-icp-object-with-deassign 0)
      (deregister-original-icp-object                    1)
      (delete-icp-object-for-process                     2)
      (delete-icp-object-for-process-with-deassign       2)
      (acknowledge-deregister-corresponding-icp-object   3)
      (deregister-and-register-corresponding-icp-object  4))))

(def-icp-value-reader deregister-icp-objects-operation
  (case (read-icp-byte)
    (0 'deregister-corresponding-icp-object)
    (1 'deregister-original-icp-object)
    (2 'delete-icp-object-for-process)
    (3 'acknowledge-deregister-corresponding-icp-object)
    (4 'deregister-and-register-corresponding-icp-object)))

(def-icp-value-writer corresponding-icp-object-index-list
  (write-icp-byte (length corresponding-icp-object-index-list))
  (loop for index in corresponding-icp-object-index-list
	do (write-icp-corresponding-icp-object-index index)))

(def-icp-value-reader corresponding-icp-object-index-list
  (loop for i from 0 below (read-icp-byte)
	collect (read-icp-corresponding-icp-object-index)
	  using icp-cons))

(eval-when (:compile-toplevel :load-toplevel :execute)
(setf (icp-value-reclaimer 'corresponding-icp-object-index-list)
      'reclaim-icp-list)
)

(def-icp-message-type deregister-icp-objects
                      ((symbol
			 name-of-corresponding-icp-object-index-space)
		       deregister-icp-objects-operation
		       corresponding-icp-object-index-list)
  (case deregister-icp-objects-operation
    (deregister-corresponding-icp-object
     (loop for corresponding-icp-object-index in corresponding-icp-object-index-list
	   do
       (deregister-corresponding-icp-object
	 nil
	 corresponding-icp-object-index
	 name-of-corresponding-icp-object-index-space
	 current-icp-port
	 nil)))
    (deregister-and-register-corresponding-icp-object
     (loop with deregister-and-register-item-p = t
	   for corresponding-icp-object-index in corresponding-icp-object-index-list
	   do
       (deregister-corresponding-icp-object
	 nil
	 corresponding-icp-object-index
	 name-of-corresponding-icp-object-index-space
	 current-icp-port
	 nil)))
    (deregister-original-icp-object
     (loop for corresponding-icp-object-index in corresponding-icp-object-index-list
	   do
       (deregister-corresponding-icp-object
	 nil
	 corresponding-icp-object-index
	 name-of-corresponding-icp-object-index-space
	 (icp-output-port (parent-icp-socket current-icp-port))
	 nil)))
    (delete-icp-object-for-process
     (loop for corresponding-icp-object-index in corresponding-icp-object-index-list
	   do
       (handle-delete-corresponding-icp-object
	 corresponding-icp-object-index
	 name-of-corresponding-icp-object-index-space
	 current-icp-port)))
    (acknowledge-deregister-corresponding-icp-object
     (loop for corresponding-icp-object-index in corresponding-icp-object-index-list
	   do
       (handle-acknowledge-deregister-corresponding-icp-object
	 corresponding-icp-object-index
	 name-of-corresponding-icp-object-index-space)))))






;;; Declaration:     nop (number-of-icp-bytes-of-fill)
;;; Type:	     ICP message type.
;;; Purpose:	     Send or receive an ICP message which does nothing.
;;; Arguments:       number-of-icp-bytes-of-fill is of ICP type
;;;                  number-of-icp-bytes-to-fill and is the number of ICP bytes
;;;                  comprising this message after the code for the message itself.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (end-icp-message-group in INT2).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; Nop does nothing.  It is used as an icp buffer filler.

;;; A number-of-icp-bytes-of-fill icp value is represented, in the icp byte stream, by
;;; that number (as a single icp byte) followed by that number of arbitrary icp bytes.

(def-icp-message-type nop (number-of-icp-bytes-of-fill)
  number-of-icp-bytes-of-fill)

;*features* in features.lisp, feature-case in bootstrap.lisp
;delta.lisp
;   major-version-number-of-current-gensym-product-line 5
;   minor-version-number-of-current-gensym-product-line 0
;   release-quality-of-current-gensym-product-line 0 => prototype-release-quality
;   revision-number-of-current-gensym-product-line 8
;   build-identification-string "G07"
;"System Versions" in bootstrap.lisp
;   (make-system-version major-release-number minor-release-number
;			 &key release-quality revision machine-model)
;   (get-system-major-version current-system-name)
;   (get-system-minor-version current-system-name)
;"Platform and Operating System Type" in bootstrap.lisp
;   g2-operating-system
;   g2-machine-type
;   (machine-model) ; determined by g2-machine-type
;"System-specific Compilation" in glbasics.lisp
;   current-system-being-loaded
;   current-system-name     ; one of: ab telewindows gsi
;"Run-time Version Checking" in utilities3.lisp
;   (def-version-registry-format xxx (key-arglist)) ; xxx is g2ds-partner g2-client remote-gsi-extension
;   (set-major-version ...)
;   (set-minor-version ...)
;   (with-appropriate-version ...)
;   (with-bifurcated-version ...)
;   (with-bifurcated-version-for-disjunct-modules ...)
;   Version information ultimately from get-system-major-version and get-system-minor-version
;"ICP Window Protocol Version" in platforms.lisp
;   latest-icp-window-protocol-version 14
;   (window-supports-this-icp-window-protocol-p ...)
;"Starting AB from Lisp" in launch.lisp
;   (announce-system-presence system)
;local process start time
;local host name and addresses (ethernet, ip, ...)
;local process id
;local process initiating command (argv)

(defvar gsi-application-name nil)

(def-system-variable tcp-listener-port-number INT3B 0)
(defvar name-for-local-home nil)

(defparameter icp-version-info-alist
  '((1  major-version-number-of-current-gensym-product-line fixnum)
    (2  minor-version-number-of-current-gensym-product-line fixnum)
    (9  latest-icp-window-protocol-version fixnum (ab telewindows))
    (10 icp-protocol-version fixnum)
    
    (11  major-version-number-of-current-gensym-product-line fixnum)
    (12  minor-version-number-of-current-gensym-product-line fixnum)
    (13  revision-number-of-current-gensym-product-line fixnum)
    (14  build-identification-string gensym-string)
    (15  icp-protocol-version fixnum)
    (16  latest-icp-window-protocol-version fixnum (ab telewindows))

    (17  gsi-references-in-use fixnum (gsi))

    (18  g2-time-at-start-as-text-string wide-string)
    (19  tcp-listener-port-number fixnum)
    (20  local-host-name wide-string)

    (21  gsi-application-name symbol (ab gsi))

    (22  disable-resumability symbol)
    (23  name-for-local-home symbol)
    (24  name-for-local-home wide-string)
    (25  supports-transparent-color-index fixnum (ab telewindows)) 

    (26  g2-operating-system symbol)
    (27  g2-machine-type symbol)
    (28  supports-dialog-component-with-font fixnum (ab telewindows))
    (29  supports-font-in-grid-view fixnum (ab telewindows))
    (30  supports-update-color-in-push-button fixnum (ab telewindows))
    (31  supports-background-color-in-custom-dialogs fixnum (ab telewindows))
    (32  supports-border-settings-in-label fixnum (ab telewindows))
    (33  supports-color-settings-in-toggle-button fixnum (ab telewindows))
    (34  supports-update-color-in-list-box fixnum (ab telewindows))
    (35  supports-update-color-in-label fixnum (ab telewindows))
    (36  supoorts-get-and-set-scroll-position-in-grid-view fixnum (ab telewindows))
    (37  operator-logbook-enabled fixnum (ab telewindows))
    (38  message-board-enabled fixnum (ab telewindows))
    ;;(?  current-system-name symbol)
    ;; local process start time
    ;; local process id
    ;; local process initiating command (argv)
    ;; local machine name
    ;; local machine ethernet address
    ;; local machine internet address
    ))

(defvar icp-protocol-version newest-icp-version)

(defparameter icp-acknowledge-version-info-alist
  '((63 acknowledge-version-info-receipt null)))

(defun get-icp-version-info-value (info symbol default)
  (or (cdr (assoc symbol info)) default))

(defun get-remote-icp-version-info-value (icp-socket symbol default)
  (get-icp-version-info-value (remote-icp-version-info icp-socket) symbol default))

(defun reconstruct-g2-time-at-start (text-string)
  (reconstruct-managed-float
    (wide-character-code (charw text-string 0))
    (wide-character-code (charw text-string 1))
    (wide-character-code (charw text-string 2))
    (wide-character-code (charw text-string 3))))

(defun get-remote-g2-time-at-start (icp-socket)
  (let ((version-info (remote-icp-version-info icp-socket)))
    (or (get-icp-version-info-value version-info 'g2-time-at-start nil)
	(let ((text-string?
		(get-icp-version-info-value version-info 'g2-time-at-start-as-text-string nil)))
	  (when text-string?
	    (let ((managed-float (reconstruct-g2-time-at-start text-string?)))
	      (icp-push (icp-cons 'g2-time-at-start managed-float)
			(remote-icp-version-info icp-socket))
	      managed-float))))))

(defun get-remote-host-name (icp-socket)
;  (case (type-of-icp-connection icp-socket)
;    (localnet
;     (get-local-host-name))
;    (generic
;     (or (icp-remote-host-name icp-socket)
;	 (let* ((string (icp-connection-name icp-socket))
;		(length (lengthw string))
;		(first (loop for i from 0 below (1-f length)
;			     when (char=w (charw string i) #.%\:)
;			       return i))
;		(second (when first
;			  (loop for i from (1+ first) below (1-f length)
;				when (char=w (charw string i) #.%\:)
;				  return i))))
;	   (when second
;	     (let ((name (wide-string-substring string (1+f first) second)))
;	       (when (string=w name #w"ACCEPT") ; see ext/c/tcp.c
;		 (reclaim-text-string name)
;		 (setq name (copy-constant-wide-string #w"")))
;	       (setf (icp-remote-host-name icp-socket) name)))))))
  (get-remote-icp-version-info-value icp-socket 'local-host-name nil))

(defun get-remote-listener-port (icp-socket)
  (get-remote-icp-version-info-value icp-socket 'tcp-listener-port-number 0))

(defun get-remote-home-name (icp-socket)
  (get-remote-icp-version-info-value icp-socket 'name-for-local-home nil))

(def-system-variable cached-local-icp-version-info INT3B nil)

(defun compute-local-icp-version-info ()
  (loop for (type-code symbol type systems) in icp-version-info-alist
	for systemp = (or (null systems)
			  (memq current-system-name systems))
	for value = (if (or (eq type 'null)
			    (not systemp))
			nil
			(symbol-value symbol))
	when (and symbol
		  systemp
		  (case type
		    (null t)
		    (fixnum (fixnump value))
		    ((gensym-string wide-string)
		     (or (gensym-string-p value)
			 (text-string-p value)))
		    (symbol (and value (symbolp value)))))
	  collect (icp-cons symbol
			    (cond ((gensym-string-p value)
				   (case type
				     (gensym-string (copy-gensym-string value))
				     (wide-string   (wide-string-to-gensym-string value))))
				  ((text-string-p value)
				   (case type
				     (gensym-string (gensym-string-to-wide-string value))
				     (wide-string   (copy-text-string value))))
				  ((eq type 'null) nil)
				  (t
				   value)))
	    using icp-cons))
  
(defun local-icp-version-info ()
  (or cached-local-icp-version-info
      (setq cached-local-icp-version-info (compute-local-icp-version-info))))

(defun get-local-icp-version-info-value (symbol default)
  (get-icp-version-info-value (local-icp-version-info) symbol default))

(defun min-of-local-and-remote-icp-version-info-value (icp-socket symbol)
  (minf (get-remote-icp-version-info-value icp-socket symbol 0)
	(get-local-icp-version-info-value symbol 0)))

(defun remote-icp-major-version (icp-socket)
  (get-remote-icp-version-info-value
    icp-socket 'major-version-number-of-current-gensym-product-line 0))

(defun remote-icp-minor-version (icp-socket)
  (get-remote-icp-version-info-value
    icp-socket 'minor-version-number-of-current-gensym-product-line 0))

(defun remote-icp-revision-number (icp-socket)
  (get-remote-icp-version-info-value
    icp-socket 'revision-number-of-current-gensym-product-line 0))

(defun remote-icp-build-identification-string? (icp-socket)
  (get-remote-icp-version-info-value icp-socket 'build-identification-string nil))

(defun remote-icp-protocol-version (icp-socket)
  (or (get-remote-icp-version-info-value icp-socket 'icp-protocol-version nil)
      (set-remote-icp-protocol-version-from-major-and-minor-version icp-socket)))

(defun set-remote-icp-protocol-version-from-major-and-minor-version (icp-socket)
  (let ((icp-version (case (remote-icp-major-version icp-socket)
		       (1 #.release-1.0-icp-version)
		       (2 #.release-2.0-icp-version)
		       (3 #.release-3.0-icp-version)
		       (4 #.release-4.0-icp-version)
		       (t (return-from set-remote-icp-protocol-version-from-major-and-minor-version 0)))))
    (setf (remote-icp-version-info icp-socket)
	  (icp-cons (icp-cons 'icp-protocol-version icp-version)
		    (remote-icp-version-info icp-socket)))
    icp-version))

(defvar initial-icp-version-info-enabled-p t)

;Locally bound to T by send-initial-icp-version-info; should remain NIL otherwise.
(defvar write-initial-icp-version-info-p nil)

;Called by process-icp-sockets and make-network-connection,
;  when the state changes to icp-connection-running.
;and also by number-of-icp-bytes-of-fill, for the reply.
(defun-allowing-unwind send-initial-icp-version-info (icp-socket connect-p)
  (let* ((state (local-icp-version-info-state icp-socket))
	 (gsi-application-name (icp-socket-gsi-application-name icp-socket))
	 (disable-resumability (not (null (icp-socket-does-not-allow-resumability icp-socket))))
	 (name-for-local-home (current-system-case
				(ab (name-for-local-home))
				(gsi (when gsi-local-home
				       (gsi-instance-value-function gsi-local-home)))))
	 (info-initial-p (eq state 'initial)))
    (unless (or (symbolp name-for-local-home)
		(wide-string-p name-for-local-home))
      (setq name-for-local-home nil))
    (when (and initial-icp-version-info-enabled-p
	       (or info-initial-p
		   (eq state 'connect-side-info-sent-but-not-yet-acknowledged)))
      (writing-icp-message-group ((icp-output-port icp-socket))
	(let ((write-initial-icp-version-info-p
		(if info-initial-p 'initial 'acknowledge)))
	  (send-icp-nop
	    (if info-initial-p
		(initial-icp-version-info-length-in-icp-bytes)
		(acknowledge-icp-version-info-length-in-icp-bytes)))))
      (let ((new-state (if (eq state 'initial)
			   (if connect-p
			       'connect-side-info-sent-but-not-yet-acknowledged
			       'listen-side-info-sent-but-no-acknowledge-yet)
			   't)))
	(setf (local-icp-version-info-state icp-socket) new-state)
	(when (or (eq state 'connect-side-info-sent-but-not-yet-acknowledged)
		  (eq new-state 'listen-side-info-sent-but-no-acknowledge-yet))
	  (finalize-icp-version-info icp-socket 'send))
	(when (eq state 'connect-side-info-sent-but-not-yet-acknowledged)
	  (finalize-icp-version-info icp-socket 'receive))))))

;Called by handle-icp-messages, after each message is processed.
(defun-void ensure-remote-icp-version-info (icp-socket handler-name)
  (declare (ignore handler-name))
  ;;This might be useful: (eq handler-name 'handle-icp-nop)
  (when initial-icp-version-info-enabled-p
    (unless (remote-icp-version-info icp-socket)
      (setf (remote-icp-version-info icp-socket)
	    (icp-cons (icp-cons 'no-icp-version-info nil) nil))))
  nil)

(defun maybe-update-remote-icp-version-info-for-version (icp-socket major-version minor-version)
  (maybe-update-remote-icp-version-info
    icp-socket major-version 'major-version-number-of-current-gensym-product-line)
  (maybe-update-remote-icp-version-info
    icp-socket minor-version 'minor-version-number-of-current-gensym-product-line)
  (when (assq 'no-icp-version-info (remote-icp-version-info icp-socket))
    (set-remote-icp-protocol-version-from-major-and-minor-version icp-socket)
    (finalize-icp-version-info icp-socket 'send)
    (finalize-icp-version-info icp-socket 'receive)))

(defun maybe-update-remote-icp-version-info (icp-socket value symbol)
  (unless (remote-icp-version-info icp-socket)
    (setf (remote-icp-version-info icp-socket)
	  (icp-cons (icp-cons 'no-icp-version-info nil) nil)))
  (when (eq (caar (remote-icp-version-info icp-socket)) 'no-icp-version-info)
    (setf (cdr (remote-icp-version-info icp-socket))
	  (icp-cons (icp-cons symbol value)
		    (cdr (remote-icp-version-info icp-socket))))))
	    

;This is the safe point for protocol changes to happen.
;This is only called when both sides support the initial-icp-version-info protocol.
;  Or, by maybe-update-remote-icp-version-info-for-version once we have received
;  some version information.
;Note: The listening side protocol change happens first in the sending direction
;        (at the receipt of the first message-group, which is the connecting-side
;        initial-version-info), then, at a later time (when the connecting-side
;        acknowledge-version-info is received), for the receiving direction.
;      For simplicity, the connecting side is done the same way,
;        although the protocol change for both directions happen at
;        the same time: when the listening-size initial-version-info is received.
;direction is 'send or 'receive; 'send is supplied first
(defun-void finalize-icp-version-info (icp-socket direction)
  (case direction
    (receive
     (setf (icp-protocol-version-for-input icp-socket)
	   (remote-icp-protocol-version icp-socket)))
    (send
     (setf (icp-protocol-version-for-output icp-socket)
	   (remote-icp-protocol-version icp-socket))))
  nil)

(defun-void receive-initial-message (local-system remote-system)
  (declare (ignore local-system remote-system))
  (current-system-case
    (ab (when send-logbook-messages-to-console-p
	  (describe-icp-connection current-icp-socket)))))

(defun describe-icp-connection (icp-socket)
  (let ((local-system-name (icp-socket-local-system-name icp-socket)))
    (notify-user-at-console "ICP connection: ~A, local: ~A, remote: ~A, version: ~A ~A ~A ~A ~A"
			    (icp-connection-name icp-socket)
			    (case local-system-name
			      (ab 'g2)
			      (t local-system-name))
			    (icp-socket-listener-client? icp-socket)
			    (remote-icp-major-version icp-socket)
			    (remote-icp-minor-version icp-socket)
			    (get-remote-icp-version-info-value
			      icp-socket 'revision-number-of-current-gensym-product-line 0)
			    (get-remote-icp-version-info-value
			      icp-socket 'build-identification-string "?")
			    (remote-icp-protocol-version icp-socket))))

(defun initial-icp-version-info-length-in-icp-bytes ()
  (1+f (loop with size fixnum = 0
	     for (type-code symbol type systems) in icp-version-info-alist
	     do (incff size (icp-version-info-element-length-in-icp-bytes
			      type-code symbol type systems))
	     finally (return size))))

(defun acknowledge-icp-version-info-length-in-icp-bytes ()
  (1+f (loop with size fixnum = 0
	     for (type-code symbol type systems) in icp-acknowledge-version-info-alist
	     do (incff size (icp-version-info-element-length-in-icp-bytes
			      type-code symbol type systems))
	     finally (return size))))

(defun write-initial-icp-version-info ()
  (loop for (type-code symbol type systems) in icp-version-info-alist
	do (write-icp-version-info-element type-code symbol type systems))
  (write-icp-byte 0))

(defun write-acknowledge-icp-version-info ()
  (loop for (type-code symbol type systems) in icp-acknowledge-version-info-alist
	do (write-icp-version-info-element type-code symbol type systems))
  (write-icp-byte 0))

;; Writing a byte count allows earlier versions of icp to
;; skip fields written by a later version.
(defun icp-version-info-element-value (symbol type systems)
  (let* ((systemp (or (null systems)
		      (memq current-system-name systems)))
	 (value (unless (or (eq type 'null) (not systemp))
		  (case symbol
		    (disable-resumability
		     (not (null (icp-socket-does-not-allow-resumability current-icp-socket))))
		    (t
		     (symbol-value symbol))))))
    (when (and symbol
	       systemp
	       (case type
		 (null t)
		 (fixnum (fixnump value))
		 ((gensym-string wide-string)
		  (or (gensym-string-p value)
		      (text-string-p value)))
		 (symbol (and value (symbolp value)))))
      (values value t))))

(defun write-icp-version-info-element (type-code symbol type systems)
  (multiple-value-bind (value write-p)
      (icp-version-info-element-value symbol type systems)
    (when write-p
      (multiple-value-bind (length value temp-string)
	  (icp-version-info-element-length-in-icp-bytes-1 type value)
	(write-icp-byte (+f (left-shiftf type-code 10) length))
	(case type
	  (null)
	  (fixnum                 (write-icp-fixnum value))
	  ((gensym-string symbol) (write-icp-gensym-string value))
	  (wide-string            (write-icp-wide-string value)))
	(when temp-string (reclaim-text-or-gensym-string temp-string)))
      value)))

(defun-simple icp-version-info-element-length-in-icp-bytes (type-code symbol type systems)
  (declare (ignore type-code))
  (multiple-value-bind (value write-p)
      (icp-version-info-element-value symbol type systems)
    (if write-p
	(multiple-value-bind (length value temp-string)
	    (icp-version-info-element-length-in-icp-bytes-1 type value)
	  (declare (ignore value))
	  (when temp-string (reclaim-text-or-gensym-string temp-string))
	  (1+f length))
	0)))

(defun icp-version-info-element-length-in-icp-bytes-1 (type value)
  (let* ((temp-string nil)
	 (length
	   (case type
	     (null 0)
	     (fixnum
	      (fixnum-length-in-icp-bytes value))
	     ((gensym-string symbol)
	      (gensym-string-length-in-icp-bytes
		(setq value
		      (cond ((symbolp value)
			     (symbol-name value))
			    ((gensym-string-p value)
			     value)
			    (t
			     (setq temp-string (wide-string-to-gensym-string value)))))))
	     (wide-string
	      (wide-string-length-in-icp-bytes
		(setq value
		      (if (text-string-p value)
			  value
			  (setq temp-string (gensym-string-to-wide-string value)))))))))
    (values length value temp-string)))

(defun read-initial-icp-version-info (total-number-of-bytes)
  (declare (type fixnum total-number-of-bytes))
  (when (<f 0 total-number-of-bytes)
    (let ((first-byte (read-icp-byte)))
      (declare (type fixnum first-byte))
      (if (zerop first-byte)
	  (read-icp-version-info-skip total-number-of-bytes)
	  (loop with alist = icp-version-info-alist
		for type+size fixnum = first-byte then (read-icp-byte)
		until (zerop type+size)
		for type-code = (right-shiftf type+size 10)
		for size = (logandf type+size #x3FF)
		for info = (read-icp-version-info-element type-code size alist)
		when info
		  collect info
		    using icp-cons)))))

(defun read-acknowledge-icp-version-info (total-number-of-bytes)
  (declare (type fixnum total-number-of-bytes))
  (when (<f 0 total-number-of-bytes)
    (let ((first-byte (read-icp-byte)))
      (declare (type fixnum first-byte))
      (if (zerop first-byte)
	  (read-icp-version-info-skip total-number-of-bytes)
	  (loop with alist = icp-acknowledge-version-info-alist
		for type+size fixnum = first-byte then (read-icp-byte)
		until (zerop type+size)
		for type-code = (right-shiftf type+size 10)
		for size = (logandf type+size #x3FF)
		for element = (read-icp-version-info-element type-code size alist)
		do
	    (case (car element)
	      (acknowledge-version-info-receipt
	       (setf (local-icp-version-info-state current-icp-socket) t)
	       (finalize-icp-version-info current-icp-socket 'receive)))
	    (reclaim-icp-version-info-element element))))))

(defun read-icp-version-info-skip (total-number-of-bytes)
  (loop for count fixnum from 1 below total-number-of-bytes
	do (read-icp-byte)
	finally (return nil)))

(defun-simple read-icp-version-info-element (type-code byte-count alist)
  (let* ((info (assoc type-code alist))
	 (symbol (cadr info))
	 (type (caddr info)))
    (case type
      (null          (icp-cons symbol nil))
      (fixnum        (icp-cons symbol (read-icp-fixnum)))
      (gensym-string (icp-cons symbol (read-icp-gensym-string)))
      (wide-string   (icp-cons symbol (read-icp-wide-string)))
      (symbol        (icp-cons symbol (intern-gensym-string (read-icp-gensym-string))))
      (t (read-icp-fill-bytes byte-count)
	 nil))))

(defun-void reclaim-icp-version-info-element (element)
  (let ((v (cdr element)))
    (cond ((gensym-string-p v)
	   (reclaim-gensym-string v))
	  ((text-string-p v)
	   (reclaim-text-string v))
	  ((managed-float-p v) ; cached version of g2-time-at-start-as-text-string
	   (reclaim-managed-float v)))
    (reclaim-icp-cons element)))

(defun-void reclaim-icp-version-info (version-info)
  (loop for info in version-info
	do (reclaim-icp-version-info-element info))
  (reclaim-icp-list version-info))


(defun maybe-set-connection-name (icp-socket)
  (let* ((name (stringw (icp-connection-name icp-socket)))
	 (limit1 #.(length ":ACCEPT:"))
	 (name-length (wide-string-length name))
	 (accept-pos (when (< limit1 name-length)
		       (search #w":ACCEPT:" name :end1 limit1)))
	 (remote-name (get-remote-host-name current-icp-socket)))
    (when (and accept-pos remote-name)
      (let ((new-connection-name
	      (twith-output-to-text-string
		(loop for i from 0 below accept-pos
		      for char = (charw name i)
		      do (twrite-char char))
		(twrite-char #.%\:)
		(twrite-string remote-name))))
	(reclaim-text-or-gensym-string (icp-connection-name icp-socket))
	(setf (icp-connection-name icp-socket) new-connection-name)
	(c-set-connection-pathname
	  (icp-connection-handle (icp-input-port icp-socket))
	  new-connection-name)))
    (icp-connection-name icp-socket)))
      
;;; Declaration:     number-of-icp-bytes-of-fill
;;; Type:	     ICP value type.
;;; Purpose:	     Represent the number of "filler" bytes in an ICP nop message.
;;; Arguments:       number-of-icp-bytes-of-fill is a nonnegative integer less than
;;;                  or equal to maximum-icp-byte-unsigned-integer.
;;; Return behavior: No useful value.
;;; Users:	     See the nop ICP message type.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(def-icp-value-reader number-of-icp-bytes-of-fill
  (let ((number-of-icp-bytes-of-fill (read-icp-byte)))
    (cond ((eq (caar (remote-icp-version-info current-icp-socket))
	       'no-icp-version-info)
	   (read-icp-fill-bytes number-of-icp-bytes-of-fill))
	  ((null (remote-icp-version-info current-icp-socket))
	   (setf (remote-icp-version-info current-icp-socket)
		 (read-initial-icp-version-info number-of-icp-bytes-of-fill))
	   (setf (icp-socket-gsi-application-name current-icp-socket)
		 (get-remote-icp-version-info-value
		   current-icp-socket 'gsi-application-name 'default))
	   (setf (icp-socket-does-not-allow-resumability current-icp-socket)
		 (get-remote-icp-version-info-value
		   current-icp-socket 'disable-resumability nil))
	   (cond ((remote-icp-version-info current-icp-socket)
		  (send-initial-icp-version-info current-icp-socket nil)
		  (maybe-set-connection-name current-icp-socket))
		 (t
		  (setf (remote-icp-version-info current-icp-socket)
			(icp-cons (icp-cons 'no-icp-version-info nil) nil)))))
	  (t
	   (read-acknowledge-icp-version-info number-of-icp-bytes-of-fill)))))

(defun-simple read-icp-fill-bytes (number-of-icp-bytes-of-fill)
  (loop with number-of-icp-bytes-to-skip = number-of-icp-bytes-of-fill
	while (>f number-of-icp-bytes-to-skip 0)
	do (read-icp-byte)
	   (decff number-of-icp-bytes-to-skip))
  number-of-icp-bytes-of-fill)  

(defun-simple write-icp-fill-bytes (number-of-icp-bytes-of-fill)
  (loop while (>f number-of-icp-bytes-of-fill 0)
	do (write-icp-byte 0)
	   (decff number-of-icp-bytes-of-fill)))

(def-icp-value-writer number-of-icp-bytes-of-fill
  (write-icp-byte number-of-icp-bytes-of-fill)
  (case write-initial-icp-version-info-p
    (initial
     (write-initial-icp-version-info))
    (acknowledge
     (write-acknowledge-icp-version-info))
    (t
     (write-icp-fill-bytes number-of-icp-bytes-of-fill))))

;; Number-of-icp-bytes-of-fill is only implemented as an icp value type for the sake of
;; consistency.





;;;; ICP value readers and writers to support data servers 

;;; Declaration:     unsigned-integer-or-nil
;;; Type:	     ICP value type.
;;; Purpose:	     Represent an unsigned integer or nil in an ICP message.
;;; Arguments:	     A nonnegative ICP integer no greater than 
;;;                  maximum-icp-byte-unsigned-integer.
;;; Return behavior: N/A.
;;; Users:	     None.
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.
;;; Notes:           Incompatible with the ICP value type unsigned-integer?, though
;;;                  their ranges are identical.

(def-icp-value-writer unsigned-integer-or-nil 
  (if (null unsigned-integer-or-nil)
      (write-icp-integer -1)
    (write-icp-integer unsigned-integer-or-nil)))

(def-icp-value-reader unsigned-integer-or-nil
  (let ((value (read-icp-integer)))
    (if (>f value -1)
	value)))



;;; Declaration:     float
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a single-precision float.
;;; Arguments:	     This is a float smaller in magnitude than 1.0e37.
;;; Return behavior: The reader returns the float.
;;; Users:           GSI, G2 remote procedures, G2-to-G2 communication (2.1 or
;;;                  earlier).
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Creates bignums and floats and so requires a temporary context.

(def-icp-value-writer float
  (current-system-case
    ((ab telewindows)
     (with-temporary-gensym-float-creation icp-float-writer
       (with-temporary-bignum-creation
	 (let ((float (if (managed-float-p float)
			  (managed-float-value float)
			  float)))
	   (declare (type gensym-float float))
	   (multiple-value-bind (expon signif)
	       (ceiling (log (abs (if (=e float 0.0)
				      1e-37
				      float))
			     10))
	     (declare (type fixnum expon))
	     (let ((sign (if (>e float 0.0) 1 0))
		   (signif-int
		    (the fixnum (truncate (*e signif most-positive-fixnum32-plus-one-as-float)))))
	       (declare (type fixnum sign signif-int))
	       (write-icp-integer signif-int)
	       (write-icp-integer expon)
	       (write-icp-byte sign)))))))
    (gsi
      (declare-ignorable-icp-arguments float))))

(def-icp-value-reader float
  (current-system-case
    ((ab telewindows)
     (let* ((signif (read-icp-integer))
	    (expon (read-icp-integer))
	    (sign (read-icp-byte)))
       (setq signif (coerce-to-gensym-float signif))
       (setq expon (coerce-to-gensym-float expon))
       (allocate-managed-float
	 (if (=f sign 0)
	     (-e (expt 10 (+e expon (/e signif most-positive-fixnum32-plus-one-as-float))))
	   (expt 10 (+e expon (/e signif most-positive-fixnum32-plus-one-as-float)))))))
    (gsi nil)))


;;; Declaration:     double-float
;;; Type:	     ICP value type.
;;; Purpose:	     Represent an IEEE double-precision float.
;;; Arguments:       This is a float smaller in magnitude than 2^1024 and larger
;;;                  than 2^-1023.  
;;; Return behavior: N/A.
;;; Users:           GSI (GSI-COMMON), G2 remote procedures (G2-RPC1 and G2-RPC2),
;;;                  G2 foreign functions (G2-FOREIGN), G2-to-G2 communication
;;;                  (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Creates a double float, which must be managed by either
;;;                  a permanent or temporary context.
;;; Notes:           > Exceptional IEEE floats (infinity and suchlike) cause
;;;                    floating point exceptions on some platforms but not on
;;;                    others.  Readers of this value type should be prepared to
;;;                    hanadle floating point exceptions where they occur.
;;;                  > The VMS platform uses a non-standard double float
;;;                    representation called G-float.  The largest IEEE float is
;;;                    larger than the largest G-float and the smallest G-float is
;;;                    smaller than the smallest IEEE float.  When ICP reads a
;;;                    double-float into VMS, any float larger than the largest
;;;                    G-float is read as the largest G-float.  When ICP writes a
;;;                    double-float from VMS, any float smaller than the smallest
;;;                    IEEE float is written as the smallest IEEE float.

;;; (jra, ml, & jh, 5/4/90)
;;; This writer emits the float as four 16 bit bytes in `IEEE 64-bit floating
;;; point format'.  For further details, see the Apple Numerics manual, second
;;; edition, p17.  The bytes are emitted in the following order.  The first 16 bit
;;; byte contains the sign bit (as bit 15), the 11 bit exponent (as bits 4 through
;;; 14), and the four most significant bits of the significand (bits 0 through 3).
;;; The encoding of the first byte follows certain conventions; see below for
;;; details.  The second byte contains the next 16 most significant bits of the
;;; significand.  The third byte contains the next 16 most significant bits of the
;;; significand, and the fourth byte contains the 16 least significant bits of the
;;; significand.
;;;
;;; Here are the special conventions in `IEEE 64-bit format':
;;;
;;; The sign bit is 0 if the number is positive and 1 if the number is negative.
;;;
;;; The exponent is biased by 1023, so it will always be nonnegative, ranging
;;; between 0 and 2047.  By convention, an exponent of 0 means the number is
;;; unnormalzed, an exponent of 2047 with an all-zero significand means the
;;; number is `NaN' (the IEEE "not a number" datatype), and an exponent of 2047
;;; with a non-zero significand means infinity.  Since some platforms do not
;;; seem to meet these three conventions, for now (5/4/90, ml & jh) ICP will read
;;; such numbers as 0 and will undertake never to write such numbers.
;;;
;;; Any other combination of exponent and significand denotes a normalized number.
;;; Since by definition a normalized number always has a most significant bit of
;;; 1, IEEE does not represent this bit explicitly.  Instead, it is dropped and
;;; the significand consists of the next-to-most significant bit on down.  The
;;; dropped bit is called the `hidden bit'.
;;;
;;; Unnormalized numbers, of course, lack a hidden bit, and are represented as
;;; they stand, leading zeros and all.  Since ICP currently represents
;;; unnormalized numbers as 0, this information will only be useful in future
;;; versions.
;;;
;;; The ICP readers and writers have been written using Common Lisp abstractions,
;;; at the cost of some efficiency.  However, optimizations exist for some
;;; platforms: Symbolics, TI, and Lucid/VMS.  The platform-specific optimizations
;;; are included in the code where reliable.  Pre-3.0 Lucid/VMS does not as yet
;;; (5/4/90 jh per jra) qualify as "reliable".  Eventually, all platforms will
;;; have reliable, tuned versions of these readers and writers, since the faster
;;; ICP transmits floats, the better.



;; jh, 2/11/91.  Modified the readers and writers for ICP double floats to
;; decompose and re-assemble them from C.  This is a lot more efficient than the
;; old way, in that we have direct access to the float at the byte level in C.  We
;; also no longer need to use bignums.  The C side of the new readers and writer
;; is in cprimitives.c.


;; Note that some older platforms only
;; support single floats, so it is normal for the last partitioned byte to be 0.




;; Icp-double-float-writer assumes its input is a number of type float, but the
;; input need not specifically be a double-float.  Whatever the type, when the
;; number is received by the remote process, it always ends up with the precision
;; of a double-float.

;; Added the special case for 0.0 to the value-writer for double floats.  This is
;; written as all 0's (the exponent is not biased).  Failing to do so was causing
;; problems with GSI on VMS platforms.  (jh, 8/9/90)

;; Modified value writer for double-float to access the float in memory directly
;; on unix and vms platforms.  jh, 2/12/91.

(def-icp-value-writer-substitution-macro double-float
  (partition-float double-float write-icp-byte))

(defmacro def-write-icp-double-float-function (name)
  (if (and (eval-feature :chestnut-3)
	   (eval-feature :chestnut-trans))
	    
      (with-package-specific-symbols (tx |::| def-foreign-callable)
	`(def-foreign-callable (,name (:return-type :object))
	     ((value :double-float))
	   (write-icp-double-float value)
	   nil))

      `(defun-void ,name (value)
	 (write-icp-double-float value))))

(def-write-icp-double-float-function write-icp-double-float-1)






;; Icp-double-float-reader always returns a number of type double float.

;; The value reader for double-float must of course be as fast as possible.  The
;; central operations are scale-float, =f, -f, and +.  CLtL notes that scale-float
;; will probably be faster than simple exponentiation.  I see no way around using
;; floating + to merge the various icp-bytes, since Common Lisp provides no
;; ldb-like abstraction for floats.  (jh, 5/1/90)

;; There is a special case for the value zero transmitted as an ICP double-float.
;; IEEE standards dictate that this be represented as all 0's, instead of
;; including a bias for the exponent.  This does not presently affect the
;; value-reader for double-floats, but it could if we ever differentiate between
;; unnormalized numbers and zero.  (jh, 8/9/90) Moved down to C code.  See
;; cprimitives.c.  (jh, 2/12/91)

;; Modified value reader for double-float to access the float in memory directly
;; on unix and vms platforms.  jh, 2/12/91.


(def-icp-value-reader-substitution-macro double-float
  ;; reconstruct-float guarantees left-to-right evaluation
  (reconstruct-float (read-icp-byte)
		     (read-icp-byte)
		     (read-icp-byte)
		     (read-icp-byte)))

(defmacro def-read-icp-double-float-function (name)
  (if (and (eval-feature :chestnut-3)
	   (eval-feature :chestnut-trans))
	    
      (with-package-specific-symbols (tx |::| def-foreign-callable)
	`(def-foreign-callable (,name (:return-type :double-float))
	     ()
	   (read-icp-double-float)))

      `(defun ,name ()
	 (read-icp-double-float))))

(def-read-icp-double-float-function read-icp-double-float-1)




;;;; Float reading for KBs


;;; These functions are adaptations of icp value readers and writers for double
;;; float which convert to and from a double float and a quadruple of 16 bit
;;; positive fixnums.

;;; Declaration:     encode-double-float (double-float)
;;; Type:	     Lisp function.
;;; Purpose:	     Transform a double float into four ICP bytes.
;;; Arguments:	     A double-float.
;;; Return behavior: Four values from most significant ICP byte to least 
;;;                  significant.
;;; Users:	     G2 KB saving (KB-SAVE1).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defmacro encode-double-float (double-float)
  `(partition-float ,double-float))



;;; Declaration:     decode-double-float (x1 x2 x3 x4)
;;; Type:	     Lisp function.
;;; Purpose:	     Transform four ICP bytes into a double float.
;;; Arguments:	     x1 through x4 are ICP bytes in most-significant first order.
;;; Return behavior: A double float.
;;; Users:	     G2 KB loading (KB-LOAD2).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Creates a double float, which must be managed by either
;;;                  a permanent or temporary context.

;;; The function `decode-double-float' ... is the reverse of the above ...

(defmacro decode-double-float (x1 x2 x3 x4)
  `(reconstruct-float ,x1 ,x2 ,x3 ,x4))



;;; Should be true for any double-float.

#+development
(defun encode-decode-tester (double-float)
  (multiple-value-bind (x1 x2 x3 x4)
      (encode-double-float double-float)
    (= double-float
       (decode-double-float x1 x2 x3 x4))))


;;;; Managed ICP double floats

(def-icp-value-reader managed-double-float
  (with-temporary-gensym-float-creation read-icp-managed-double-float
    (allocate-managed-float
      (reconstruct-float (read-icp-byte)
			 (read-icp-byte)
			 (read-icp-byte)
			 (read-icp-byte)))))

(def-icp-value-writer managed-double-float
  (with-temporary-gensym-float-creation write-icp-managed-double-float
    (partition-float (managed-float-value managed-double-float) write-icp-byte)))

;; jra & jh, 11/10/92.  Added managed ICP double floats as part of the GSI
;; performance project.

;; Incorporated float-conversion calls required to support non-default floating
;; point formats on VAX platform (see gensym.h) -paf! 19apr95




;;; Declaration:     define-dummy-object (corresponding-icp-object-index)
;;; Type:	     ICP message type.
;;; Purpose:	     Absorb a corresponding object index without storing anything.
;;; Arguments:	     corresponding-icp-object-index is the index to be absorbed.
;;; Return behavior: No useful value.
;;; Users:	     None.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; Define-dummy-object is useful for dummy definitions of corresponding icp
;;; object makers.

(def-icp-message-type define-dummy-object (corresponding-icp-object-index)
  corresponding-icp-object-index)

;; Consider having this actually store something.



;;; Declaration:     end-message-block ()
;;; Type:	     ICP message type.
;;; Purpose:	     Indicate the end of an ICP message block.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     Telewindows and G2 printing (ENTITIES, GRAPHS1).
;;; Prerequisites:   None.
;;; Side effects:    Sets a flag indicating that the end of the ICP message block
;;;                  has been reached.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; End-message-block terminates an icp message block, e.g., an icon-rendering
;;; message block.

(def-icp-message-type end-message-block ()
  (setq at-end-of-icp-message-block? t))




;;; Declaration:     s-expression-for-remote-eval
;;; Type:	     ICP value type.
;;; Purpose:	     Represent an s-expression in an ICP message.
;;; Arguments:       S-expressions are restricted to contain text-strings, symbols
;;;                  (in the AB package), fixnums, double floats, characters, or
;;;                  icp-lists of these.  Circular or improper lists (i.e., lists
;;;                  not terminated in nil) are not allowed.
;;; Return behavior: N/A.
;;; Users:	     Player, printer.
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   The reader allocates icp-conses for the s-expression.

;; jh, 10/30/90.
;; Value reader and writer for s-expressions suitable for eval.  This is
;; originally conceived as a back door for BAH's user-interface testing harness,
;; but has wider utility.

;; S-expressions to be written must not be circular or improper lists.
;; S-expressions are restricted to strings, symbols (in the AB package), fixnums,
;; floats, characters, or lists of these.  

;; S-expressions are read as trees of icp-conses, whose leaves may contain (among
;; other things) floats or text-strings.  It is up to the programmer to reclaim
;; these, as no s-expression read through this mechanism will be recycled
;; automatically.  The function reclaim-s-expression-for-remote-eval is provided
;; for this purpose.

(defun reclaim-s-expression-for-remote-eval (s-expression)
  (declare (no-op-for-gsi))
  (cond
    ((or (null s-expression) (symbolp s-expression) (integerp s-expression))
     nil)
    ((consp s-expression)
     (loop with l = s-expression		; a bit slow for 1 or 2 conses
	   as x = (car l)
	   do (when (and (not (symbolp x))	; only for speed
			 (not (numberp x)))	; only for speed
		(reclaim-s-expression-for-remote-eval x)
		;; recycle x if heap-allocated!
		)
	   until (atom (setq l (cdr l)))
	   finally
	   (when l
	     (reclaim-s-expression-for-remote-eval l)
	     (setf (cdr (last s-expression)) nil))
	   (reclaim-icp-list s-expression)))
    ((text-string-p s-expression)
     (reclaim-text-string s-expression))
    (t nil)))


;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter sexp-null-type-tag 0)
(defparameter sexp-element-integer-type-tag 1)
(defparameter sexp-element-float-type-tag 2)
(defparameter sexp-element-symbol-type-tag 3)
(defparameter sexp-element-text-type-tag 4)
(defparameter sexp-element-list-type-tag 5)
(defparameter sexp-element-character-type-tag 6)
)



(def-icp-value-writer sexp-element
  (current-system-case
    ((ab telewindows)
      (cond
	((null sexp-element)
	 (write-icp-byte sexp-null-type-tag))
	((characterp sexp-element)
	 (write-icp-byte sexp-element-character-type-tag)
	 (write-icp-character sexp-element))
	((integerp sexp-element)
	 (write-icp-byte sexp-element-integer-type-tag)
	 (write-icp-integer sexp-element))
	((floatp sexp-element)
	 (write-icp-byte sexp-element-float-type-tag)
	 (write-icp-double-float-1 sexp-element))
	((symbolp sexp-element)
	 (write-icp-byte sexp-element-symbol-type-tag)
	 (write-icp-text-string (symbol-name-text-string sexp-element)))
	((text-string-p sexp-element)
	 (write-icp-byte sexp-element-text-type-tag)
	 (write-icp-text-string sexp-element))
	((consp sexp-element)
	 (write-icp-byte sexp-element-list-type-tag)
	 (write-icp-s-expression-for-remote-eval sexp-element))
	#+development
	(t (error "Bad element in an s-expression for remote eval: ~a"
		  sexp-element))))
    (gsi (declare-ignorable-icp-arguments sexp-element))))

    ;; It is tempting (since this is often used as a backdoor) to have the
    ;; otherwise clause "just" send :<bad-element> rather than error.



(def-icp-value-reader sexp-element
  (current-system-case
    ((ab telewindows)
      (fixnum-case (read-icp-byte)
	(#.sexp-null-type-tag nil)
	(#.sexp-element-character-type-tag
	   (read-icp-character))
	(#.sexp-element-integer-type-tag
	   (read-icp-integer))
	(#.sexp-element-float-type-tag
	   (read-icp-double-float-1))
	(#.sexp-element-symbol-type-tag 
	   (intern-text-string 
	     (read-icp-text-string)))
	(#.sexp-element-text-type-tag
	   (read-icp-text-string))
	(#.sexp-element-list-type-tag
	   (read-icp-s-expression-for-remote-eval))))
    (gsi nil)))


(def-icp-value-writer s-expression-for-remote-eval
  (current-system-case
    ((ab telewindows)
      (cond
	((consp s-expression-for-remote-eval)
	 (write-icp-unsigned-integer (length s-expression-for-remote-eval))
	 (loop for sexp-element in s-expression-for-remote-eval
	       do (write-icp-sexp-element sexp-element)))
	(t (write-icp-sexp-element s-expression-for-remote-eval))))
    (gsi
      (declare-ignorable-icp-arguments s-expression-for-remote-eval))))

(def-icp-value-reader s-expression-for-remote-eval
  (current-system-case
    ((ab telewindows)
      (loop for item-count from 1 to (read-icp-unsigned-integer)
	    collect (read-icp-sexp-element)
	      using icp-cons))
    (gsi nil)))

;; This code can't pass an atom as an s-expression.  Which is sad.
;; If s-expression-for-remote-eval was equivalent to sexpr-element
;; it would "just work."  - ben 9/13/94





;;; Declaration:     remote-eval (s-expression-for-remote-eval)
;;; Type:	     ICP message type.
;;; Purpose:	     Evaluate a s-expression across ICP.
;;; Arguments:       s-expression-for-remote-eval is restricted to contain
;;;                  text-strings, symbols (in the AB package), fixnums, double
;;;                  floats, characters, or lists of these.  Circular or improper
;;;                  lists (i.e., lists not terminated in nil) are not allowed.
;;; Return behavior: Returns the result of invoking simple-eval on 
;;;                  s-expression-for-remote-eval.
;;; Users:	     G2 player (PLAYER).
;;; Prerequisites:   None.
;;; Side effects:    The side effects of evaluating s-expression-for-remote-eval.
;;; Non-local exits: None.
;;; Memory impact:   The handler reclaims s-expression-for-remote-eval after
;;;                  evaluating it.

;; The ICP message type code for remote-eval is in module INT1.

; backdoor for testing
(def-icp-message-type remote-eval (s-expression-for-remote-eval)
  (current-system-case
    ((ab telewindows)
     (simple-eval s-expression-for-remote-eval)
     (reclaim-s-expression-for-remote-eval s-expression-for-remote-eval))
    (gsi
      (declare-ignorable-icp-arguments s-expression-for-remote-eval))))







;;;; I-am-alive Mechanism

;;; Basic Mechanism

;;; The checks made by ICP to detect broken connections when sending and receiving
;;; messages are not foolproof.  In some protocols such as UNIX-tcp-ip, a write
;;; must be attempted in order to determine if a connection is closed.  Thus, if
;;; no attempt is made to write, a process will never detect that the connection
;;; is broken.  For example, if a Telewindows is running without operator input,
;;; and the G2 process goes down or the connection goes down, it will do nothing
;;; until the operator hits a key or the mouse (causing an attempt to write a
;;; message group to the G2) at which time the broken connection will be detected
;;; and the process shut down.  Conversely, G2 has no way of knowing that a
;;; Telewindows process has gone down until it attempts to send it a message.

;;; These problems themselves are not so bad.  A far worse problem is the fact that a
;;; remote process may go down without the connection to it being shut down.  The
;;; local process would then be able to continue writing messages to the remote
;;; process, filling up more and more local icp buffers, until it eventually runs out
;;; of memory.

;;; The I-am-alive mechanism, in which every ICP socket exchanges "I-am-alive"
;;; messages with its corresponding socket, solves this problem.  It allows for (among
;;; other things) a socket to recognize if the remote process is no longer alive and
;;; shut down the connection if this is the case.

;;; The I-am-alive mechanism is implemented using the I-am-alive-info structure in an
;;; ICP socket (see ICP socket data structure section) and can operate for any pair of
;;; ICP sockets in an ICP connection.

;;; The I-am-alive mechanism is set up for an ICP socket by the function
;;; initialize-I-am-alive-info which takes as args icp-socket,
;;; I-am-alive-send-time-interval?, deadman-switch-time-interval?,
;;; function-to-decide-whether-to-send-I-am-alive,
;;; function-to-determine-if-remote-process-alive?, and
;;; function-to-determine-if-icp-connection-clogged?.
;;; Initialize-I-am-alive-info makes an I-am-alive-info structure, puts it into
;;; the I-am-alive-info?  slot of the ICP socket, and uses the args to set
;;; corresponding slots in the I-am-alive-info structure.  It also initializes
;;; the time-I-am-alive-was-sent, time-I-am-alive-was-received,
;;; number-of-message-groups-handled-since-last-I-am-alive-was-sent, and
;;; number-of-icp-bytes-handled-since-last-I-am-alive-was-sent slots.  It also
;;; initializes the id-for-last-message-group-written,
;;; id-for-last-message-group-handled,
;;; id-for-last-message-group-handled-by-remote-socket, and
;;; id-for-last-message-group-written-by-remote-socket slots to 0.

;;; If initialize-I-am-alive-info is not called for an ICP socket (if I-am-alive-info?
;;; for the socket is nil) then I-am-alive processing will not be done for that
;;; socket.

;;; Operation of the I-am-alive mechanism is simple.  Process-icp-sockets calls
;;; do-I-am-alive-processing for each active ICP socket with a non-nil
;;; I-am-alive-info?  slot.  Do-I-am-alive-processing funcalls
;;; function-to-decide-whether-to-send-I-am-alive, and
;;; function-to-determine-if-remote-process-alive?  (if any) with the I-am-alive-info
;;; structure as the argument.

;;; Function-to-decide-whether-to-send-I-am-alive should return non-nil if
;;; it is time to send an I-am-alive message.  A typical way to do this is
;;; to use the I-am-alive-send-time-interval?, and time-I-am-alive-was-sent
;;; slots of the I-am-alive-info structure and return t if

;;;   current time > time-I-am-alive-was-sent + I-am-alive-send-time-interval?.
;;; or if 
;;;   number-of-message-groups-handled-since-last-I-am-alive-was-sent >
;;;   maximum-number-of-message-groups-between-I-am-alive?

;;; If function-to-decide-whether-to-send-I-am-alive returns non-nil,
;;; send-I-am-alive-message is called.  This sends the I-am-alive message,
;;; updates the time-I-am-alive-was-sent slot, and resets the
;;; number-of-message-groups-handled-since-last-I-am-alive-was-sent slot to 0.
;;; The number-of-message-groups-handled-since-last-I-am-alive-was-sent is
;;; automatically incremented by the handler for the message-group-id message
;;; (see below).

;;; Function-to-determine-if-remote-process-alive? should return t if it
;;; determines that the remote process is alive.  A typical way to do this
;;; is to use the deadman-switch-time-interval?, and time-I-am-alive-was-received
;;; slots of the I-am-alive-info structure and return nil if 

;;;   current-time > time-I-am-alive-was-received + deadman-switch-time-interval?.

;;; If function-to-determine-if-remote-process-alive?  returns nil, the
;;; remote-process-alive-p slot of the I-am-alive-info structure is set to nil.
;;; Function-to-determine-if-remote-process-alive?  may also take other actions in
;;; this case such as posting warning notes, shutting down a connection, or inhibiting
;;; sending of more messages to the remote socket.

;;; The handler for the I-am-alive message automatically updates the
;;; time-I-am-alive-was-received slot.  Note that this handler must check if
;;; I-am-alive-info?  for the ICP socket is non-nil.

;;; Customization of the I-am-alive mechanism (for Telewindows, GSI, etc.) is easily
;;; achieved by passing the appropriate arguments to initialize-I-am-alive-info.  The
;;; fact that initialize-I-am-alive-info allows for both setting of parameters like
;;; I-am-alive-send-time-interval?  and of functions for determining status allows for
;;; great flexibility.  These functions can use these parameters, along with the 
;;; automatically updated slots of the I-am-alive-info structure as needed.


;;; Flow Control

;;; The I-am-alive mechanism can be used to determine the number of outstanding ICP
;;; message groups (and eventually even the number of outstanding ICP bytes) and can
;;; thus be used to implement flow control.

;;; Number of outstanding ICP message groups is determined using the
;;; id-for-last-message-group-written and
;;; id-for-last-message-group-handled-by-remote-socket slots of the I-am-alive-info
;;; structure.  The id-for-last-message-group-written slot contains a fixnum
;;; initialized to 0 (by initialize-I-am-alive-info).  This number is incremented by
;;; writing-icp-message-group and eventually wraps around.  Writing-icp-message-group
;;; sends this id with each message group using the ICP message message-group-id.
;;; Note that this will not be done if the socket does not do I-am-alive processing
;;; (if the I-am-alive-info?  slot is nil).

;;; Id-for-last-message-group-handled is set by the handler for the ICP message
;;; message-group-id using the arg for this message.

;;; The I-am-alive ICP message has one argument, the unsigned integer in the
;;; id-for-last-message-group-handled slot of the socket writing the message.
;;; Send-I-am-alive-message retreives this number and sends out the message.

;;; Id-for-last-message-group-handled-by-remote-socket is set by the handler for the
;;; I-am-alive message using the arg for this message.

;;; Note that none of this is done if the I-am-alive-info?  slot of the icp socket is
;;; nil.  The slot id-for-last-message-group-written-by-remote-socket is currently not
;;; used.

;;; Function-to-determine-if-icp-connection-clogged?  should make its
;;; determination based on the id-for-last-message-group-written and
;;; id-for-last-message-group-handled-by-remote-socket slots, by taking the
;;; difference between them.  Consider adding a slot
;;; maximum-number-of-outstanding-icp-message-groups to facilitate this.  The
;;; possibility of wrap-around must be taken into account when taking this
;;; difference.  Wrap-around should not be a problem if the limit on
;;; number-of-outstanding-icp-message-groups is less than the maximum value for
;;; message group ids.  If function-to-determine-if-icp-connection-clogged?
;;; returns non-nil, the icp-connection-clogged-p slot of the I-am-alive-info
;;; structure is set to t.  This slot can be used to cut off writing of icp
;;; message groups.

;;; Because the result of function-to-determine-if-icp-connection-clogged?  is (or
;;; should be) based on the id-for-last-message-group-written and
;;; id-for-last-message-group-handled-by-remote-socket slots, it is called whenever
;;; one of these slots changes.  Thus, it is called by writing-icp-message-group
;;; and by the handler for the I-am-alive message.



;;; Improved Flow Control

;;; Comparing message group ids gives some indication of how far behind the
;;; remote process is in processing ICP messages.  However, it is not very
;;; accurate since size of message groups, which can vary greatly, is not taken
;;; into account.  A way to improve this is to maintain a list of Ids for
;;; message groups sent along with the number of ICP bytes written for each
;;; message group.  As I-am-alive messages are received from the remote process,
;;; message groups with ID <= to the ones in the I-am-alive messages are removed
;;; from the list.  An accurate number of ICP bytes to be processed can be
;;; obtained by adding the number of ICP bytes for each message group on this
;;; list.

;;; To accomplish this, it is necessary to be able to compute the number of icp
;;; bytes in a message group.  This is done using the special variables
;;; number-of-icp-bytes-for-message-series and
;;; number-of-icp-bytes-to-fill-buffer.  These variables control the writing of
;;; icp bytes into icp buffers and can be used to determine the number of icp
;;; bytes in a message series (and in a message group).

;;; Number-of-icp-bytes-to-fill-buffer indicates how much room is left in the
;;; icp buffer before it is full.  It is thus initialized to the size of the
;;; current icp buffer when a new one is made, and is decremented when writing
;;; an icp byte.  When it reaches 0, the icp buffer is full.

;;; Number-of-icp-bytes-for-message-series is initialized to
;;; number-of-icp-bytes-to-fill-buffer when a new icp message series is started
;;; and is incremented by the size of the current icp buffer when a new one is
;;; made.  It is thus the number of icp bytes in the message series + the room
;;; left in the last icp buffer (which is given by
;;; number-of-icp-bytes-to-fill-buffer).  If the message series is the first in
;;; the group, number-of-icp-bytes-for-message-series is the accumulated size of
;;; all the icp buffers in the message series.  The message series byte count is
;;; computed by subtracting number-of-icp-bytes-to-fill-buffer from
;;; number-of-icp-bytes-for-message-series.

;;; The detailed operation of these variables is as follows.
;;; Writing-icp-message-group initializes them to 0.  When an icp message is
;;; sent, the sender body (see def-icp-message-type) calls
;;; start-writing-icp-message.  This calls start-icp-message-series if at the
;;; beginning of a new message group, or if there is one or more full icp
;;; buffers for the current message series (the previous message has caused one
;;; or more icp buffers to become full).  Start-icp-message-series sets
;;; number-of-icp-bytes-for-message-series to
;;; number-of-icp-bytes-to-fill-buffer.  Thus, the messages in a message group
;;; are automatically broken up into message series.

;; Check with Lowell about the philosophy regarding breaking message groups into
;; message series!  Document somewhere.

;;; ICP bytes in messages are written into icp buffers by write-icp-byte.  If
;;; number-of-icp-bytes-to-fill-buffer is not 0, it is decremented and the icp
;;; byte is written into the current icp buffer.  If it is 0 (if the buffer is
;;; full), write-icp-byte-into-new-buffer is called.  This makes a new icp
;;; buffer, sets number-of-icp-bytes-to-fill-buffer to the size of the new
;;; buffer, and increments number-of-icp-bytes-for-message-series by the size of
;;; the new buffer.

;; Document how end-icp-message-group-if-any sets these variables!

;;; End-icp-message-series-if-any computes message-series-byte-count by
;;; subtracting number-of-icp-bytes-to-fill-buffer from
;;; number-of-icp-bytes-for-message-series.  This is accumulated into the
;;; special variable number-of-icp-bytes-in-message-group which is bound by
;;; writing-icp-message-group.  Thus, the number of icp bytes in a message group
;;; is easily computed.

;;; Flow control is accomplished using the slots
;;; message-group-ids-and-byte-counts and number-of-outstanding-icp-bytes of the
;;; I-am-alive-info structure.  Message-group-ids-and-byte-counts is an alist
;;; with elements of the form 
;;;   (message-group-id . message-group-byte-count).

;;; End-icp-message-group, besides updating id-for-last-message-group-written,
;;; adds an entry for the message group written to the head of this list (using
;;; number-of-icp-bytes-in-message-group), and also increments the
;;; number-of-outstanding-icp-bytes slot by this number.  The handler for the
;;; I-am-alive message type (see def-icp-message-type for I-am-alive), besides
;;; updating id-for-last-message-group-handled-by-remote-socket, removes all
;;; entries for message-group-ids after and including the one for
;;; id-for-last-message-group-handled-by-remote-socket.  As it removes each
;;; entry, it decrements the number-of-outstanding-icp-bytes slot by the message
;;; group byte count in the entry.  Thus, the number-of-outstanding-icp-bytes 
;;; slot can be used to determine if the connection is clogged.

;;; In order to be able to accurately determine when to send I-am-alive
;;; messages, it is necessary to maintain
;;; number-of-icp-bytes-handled-since-last-I-am-alive-was-sent as well as
;;; number-of-message-groups-handled-since-last-I-am-alive-was-sent.
;;; Function-to-decide-whether-to-send-I-am-alive can then return t if
;;;   number-of-icp-bytes-handled-since-last-I-am-alive-was-sent >
;;;   maximum-number-of-icp-bytes-between-I-am-alive?
;;; Number-of-icp-bytes-handled-since-last-I-am-alive-was-sent is handled in a
;;; manner similar to
;;; number-of-message-groups-handled-since-last-I-am-alive-was-sent; it is reset
;;; to 0 by send-I-am-alive-message, and is incremented in the handler for the
;;; message-group-id message type by the number of icp bytes in the message
;;; group.  This number is sent in the message, along with the message group id.

;; Note that there are ways to determine the number of icp bytes in a message
;; group when the message group is being received, rather than sending this number
;; in a message-group-id message.  Review with Lowell, John!



;;; Declaration:     initialize-I-am-alive-info
;;;                    (icp-socket 
;;; 		        I-am-alive-send-time-interval? 
;;; 	                deadman-switch-time-interval? 
;;; 	                function-to-decide-whether-to-send-I-am-alive
;;; 	                function-to-determine-if-remote-process-alive?
;;; 	                function-to-determine-if-icp-connection-clogged?)
;;; Type:	     Lisp function.
;;; Purpose:         Initialize the I-am-alive flow control mechanism for an ICP
;;;                  connection.
;;; Arguments:	     > icp-socket is an ICP socket structure.
;;;                  > I-am-alive-send-time-interval?  is a fixnum time or nil.  The
;;;                    i-am-alive internals do not use this value (say to send a
;;;                    heartbeat); it is for reference by client-written functions
;;;                    like function-to-decide-whether-to-send-I-am-alive.
;;;                  > deadman-switch-time-interval?  is nil or a a fixnum time
;;;                    which indicates how long to wait until assuming the remote
;;;                    process can not longer transmit ICP data.  The i-am-alive
;;;                    internals do not use this value; This slot is for reference
;;;                    by client-written functions like
;;;                    function-to-determine-if-remote-process-alive?.
;;;                  > function-to-decide-whether-to-send-I-am-alive is a symbol
;;;                    naming a funcallable function.  This function is written by
;;;                    the client of the i-am-alive facility and takes a single
;;;                    argument, an i-am-alive-structure.
;;;                  > function-to-determine-if-remote-process-alive?  is nil or a
;;;                    symbol naming a funcallable function.  This function is
;;;                    written by the client of the i-am-alive facility and takes a
;;;                    single argument, an i-am-alive structure
;;;                  > function-to-determine-if-icp-connection-clogged?  is nil or a
;;;                    symbol naming a funcallable function.  This function is
;;;                    written by the client of the i-am-alive facility and takes a
;;;                    single argument, an i-am-alive structure.
;;; Return behavior: No useful value.
;;; Users:	     Telewindows (TELESTUBS), G2-to-G2 communictaion (G2DS).
;;; Prerequisites:   None.
;;; Side effects:    Creates an i-am-alive structure inside icp-socket.
;;; Non-local exits: None.
;;; Memory impact:   Allocates memory for an i-am-alive-structure.  If this function
;;;                  is called twice without an intervening call to
;;;                  reclaim-i-am-alive-info? a leak will result.
;;; Notes:           See the definition of the i-am-alive structure in INT1.

(defun initialize-I-am-alive-info
       (icp-socket function-to-determine-if-icp-connection-clogged?)
  (declare (eliminate-for-gsi))
  (let ((I-am-alive-info (make-I-am-alive-info))
	(fixnum-time (get-fixnum-time)))

    ;; Set parameters according to args.
    (setf (function-to-determine-if-icp-connection-clogged? I-am-alive-info)
	  function-to-determine-if-icp-connection-clogged?)

    ;; Initialize automatically updated slots.
    (setf (time-I-am-alive-was-sent I-am-alive-info) fixnum-time
	  (time-I-am-alive-was-received I-am-alive-info) fixnum-time
	  (number-of-message-groups-handled-since-last-I-am-alive-was-sent
	    I-am-alive-info) 0
	  (number-of-icp-bytes-handled-since-last-I-am-alive-was-sent
	    I-am-alive-info) 0
	  (id-for-last-message-group-written I-am-alive-info) 0
	  (id-for-last-message-group-handled I-am-alive-info) 0
	  (id-for-last-message-group-handled-by-remote-socket
	    I-am-alive-info) 0
	  (number-of-outstanding-icp-bytes I-am-alive-info) 0)
    (setf (I-am-alive-info? icp-socket) I-am-alive-info)))







;;; Declaration:     do-i-am-alive-processing (icp-socket)
;;; Type:	     Lisp function.
;;; Purpose:	     Perform i-am-alive flow control on an ICP connection.
;;; Arguments:	     An ICP socket.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (process-icp-sockets in INT2).
;;; Prerequisites:   initialize-I-am-alive-info must have been called on icp-socket.
;;; Side effects:    Internal slots of the i-am-alive structure inside icp-socket.
;;;                  May transmit ICP messages.  The client-written functions inside
;;;                  the i-am-alive structure in icp-socket may have side effects.
;;; Non-local exits: None.
;;; Memory impact:   May allocate ICP buffers to transmit ICP messages.  May fill
;;;                  internal network buffers of the operating system.

(defun do-i-am-alive-processing (icp-socket)
  (declare (eliminate-for-gsi))
  (runtime-current-system-case
    ((ab)
     (let ((i-am-alive-info (i-am-alive-info? icp-socket)))
       (when (and 
	      i-am-alive-info
	      (remote-process-alive-p i-am-alive-info)
	      (>f (fixnum-time-difference
		   (get-fixnum-time)
		   (time-i-am-alive-was-received i-am-alive-info))
		  (convert-seconds-to-fixnum-time-difference 
		   (dead-connection-timeout-from-system-table))))
	 (when (disconnect-dead-connections?-from-system-table)
	   (shutdown-icp-socket-connection icp-socket 'dead-connection))
	 (setf (remote-process-alive-p i-am-alive-info) nil))))))


(def-system-variable sending-I-am-alive? INT3B nil)

;; jh, 5/19/95.  Added handling-solitary-I-am-alive? to prevent superfluous
;; exchange of I-am-alive / message-group-id messages.  Such exchanges were
;; brought on by reducing the maximum number of message groups before a TW
;; connection sends I-am-alive, brought on in turn by the need for a valid
;; throughput measurement, for the benefit of lengthy TW messages like
;; image-data-chunk.  This variable is used in handle-icp-messages to detect a
;; message group consisting of a single I-am-alive message.  We don't want to
;; derive throughput information from this. only from substantive message
;; groups.

(def-system-variable handling-solitary-I-am-alive? INT3B nil)

(defvar I-am-alive-send-time-interval-in-seconds
  30)

(defvar I-am-alive-send-time-interval-in-seconds-as-float
  30.0)

(defvar I-am-alive-send-time-interval
  (convert-seconds-to-fixnum-time-difference
    I-am-alive-send-time-interval-in-seconds))

(defun send-I-am-alive-if-necessary (icp-socket I-am-alive-info)
  (declare (eliminate-for-gsi))
  (let ((system (current-system-case
		  (ab (or (icp-socket-listener-client? icp-socket) 'g2))
		  (telewindows 'telewindows))))
    (when (or (eq system 'g2) (eq system 'telewindows))
      (if (or sending-I-am-alive? handling-solitary-I-am-alive?)
	  (schedule-send-I-am-alive-message icp-socket I-am-alive-info)
	  (if (or (>f (fixnum-time-difference
			(get-fixnum-time)
			(time-I-am-alive-was-sent I-am-alive-info))
		      I-am-alive-send-time-interval)
		  (>f (number-of-message-groups-handled-since-last-I-am-alive-was-sent
			I-am-alive-info)
		      (case system
			(g2 5)
			(telewindows 1)
			(t 0)))
		  (>f (number-of-icp-bytes-handled-since-last-I-am-alive-was-sent
			I-am-alive-info)
		      30000))
	      (send-I-am-alive-message icp-socket I-am-alive-info)
	      (schedule-send-I-am-alive-message icp-socket I-am-alive-info))))))



;;; Declaration:     i-am-alive (message-group-id)
;;; Type:	     ICP message type.
;;; Purpose:	     Inform the remote ICP process that this process is running.
;;; Arguments:       message-group-id is of ICP value type unsigned integer and is
;;;                  the identifier of the current ICP message group.  Message
;;;                  groups wrap around at most-positive-fixnum.
;;; Return behavior: No useful value.
;;; Users:	     See do-i-am-alive-processing.
;;; Prerequisites:   initialize-I-am-alive-info must have been called on 
;;;                  current-icp-socket.
;;; Side effects:    Resets counters in the remote i-am-alive structure.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defun-allowing-unwind send-i-am-alive-message (icp-socket i-am-alive-info)
  (declare (no-op-for-gsi))
  (cancel-task (task-to-send-i-am-alive icp-socket))
  (when (and (=f #.icp-connection-running (icp-connection-state icp-socket))
	     (not (icp-port-blocked? (icp-output-port icp-socket))))
    (let ((sending-i-am-alive? t))
      (writing-icp-message-group ((icp-output-port icp-socket))
	(send-icp-i-am-alive 
	 (id-for-last-message-group-handled i-am-alive-info))))
    (setf (time-i-am-alive-was-sent i-am-alive-info) (get-fixnum-time)
	  (number-of-message-groups-handled-since-last-i-am-alive-was-sent
	   i-am-alive-info) 0
	  (number-of-icp-bytes-handled-since-last-i-am-alive-was-sent
	   i-am-alive-info) 0))
  ; Would be a good idea to have a independent timer for modularity to 
  ; execute do-i-am-alive-processing
  (do-i-am-alive-processing icp-socket)
  (schedule-send-i-am-alive-message icp-socket i-am-alive-info))

(defun-void schedule-send-I-am-alive-message (icp-socket I-am-alive-info)
  (unless (future-schedule-task-in-place-p
	    (task-to-send-I-am-alive icp-socket))
    (with-future-scheduling ((task-to-send-I-am-alive icp-socket)
			     0
			     (+e (managed-float-value (clock-get current-real-time))
				 I-am-alive-send-time-interval-in-seconds-as-float)
			     nil nil t)
      (send-I-am-alive-message icp-socket I-am-alive-info))))

(defun-void update-icp-bytes-per-second-if-possible
    (I-am-alive-info outstanding-icp-bytes-originally)
  (declare (eliminate-for-gsi))
  (let ((icp-bytes-sent-and-handled
	  (-f outstanding-icp-bytes-originally
	      (number-of-outstanding-icp-bytes I-am-alive-info))))
    (when (>f icp-bytes-sent-and-handled ;compensate for idleness
	      (size-of-variable-fill-icp-buffers))
      (let ((processing-interval
	      (fixnum-time-difference
		(get-fixnum-time)
		(time-i-am-alive-was-sent I-am-alive-info))))
	(when (>f processing-interval 10) ;compensate for granularity
	  (let ((new-bytes-per-second
		  (floorf-positive
		    (*f icp-bytes-sent-and-handled
			fixnum-time-units-per-second)
		    processing-interval)))
	    (setf (icp-bytes-per-second-through-output-port I-am-alive-info)
		  new-bytes-per-second)))))))

(def-icp-message-type I-am-alive ((unsigned-integer message-group-id))
  (runtime-current-system-case
    ((ab telewindows)
     (let* ((I-am-alive-info? (I-am-alive-info? current-icp-socket)))
       (when I-am-alive-info?
	 (setf (time-I-am-alive-was-received I-am-alive-info?)
	       (get-fixnum-time)
	       (id-for-last-message-group-handled-by-remote-socket
		 I-am-alive-info?)
	       message-group-id)
	 (let ((message-group-ids-and-byte-counts?
		 (message-group-ids-and-byte-counts I-am-alive-info?)))
	   (when message-group-ids-and-byte-counts?
	     (let ((outstanding-icp-bytes-originally
		     (number-of-outstanding-icp-bytes I-am-alive-info?)))
	       (loop for trailing-entry-cons
			 = message-group-ids-and-byte-counts?
			 then entry-cons?
		     for entry-cons? = (cdr trailing-entry-cons)
		     while entry-cons?
		     do
		 (when (=f (caar-of-conses entry-cons?) message-group-id)
		   (setf (message-group-ids-and-byte-counts I-am-alive-info?)
			 entry-cons?)
		   (setf (cdr trailing-entry-cons) nil)
		   (loop with delta-of-outstanding-icp-bytes = 0
			 for entry in message-group-ids-and-byte-counts?
			 do
		     (incff delta-of-outstanding-icp-bytes (cdr entry))
		     (reclaim-icp-cons entry)
			 finally
			   (decff
			     (number-of-outstanding-icp-bytes I-am-alive-info?)
			     delta-of-outstanding-icp-bytes)
			   (reclaim-icp-list-given-tail
			     message-group-ids-and-byte-counts?
			     trailing-entry-cons))
		   (loop-finish)))
	       (update-icp-bytes-per-second-if-possible
		 I-am-alive-info?
		 outstanding-icp-bytes-originally))))
	 (update-icp-connection-clogged-p I-am-alive-info? nil))))
    (gsi
      (declare-ignorable-icp-arguments message-group-id))))

;; Because setting id-for-last-message-group-handled-by-remote-socket can never
;; cause an increase in the number of outstanding icp message groups computed by
;; function-to-determine-if-icp-connection-clogged?, the only possibility of change
;; in the icp-connection-clogged-p is from t to nil;
;; function-to-determine-if-icp-connection-clogged?  determines that a clogged
;; connection is unclogged.  Therefore, consider only calling
;; function-to-determine-if-icp-connection-clogged?  if icp-connection-clogged-p is
;; t.  Also, consider calling this function in writing-icp-message-group only if
;; icp-connection-clogged-p is nil.  Also, consider getting rid of the
;; function-to-determine-if-icp-connection-clogged?  slot and making this a fixed
;; function.



;;; Declaration:     message-group-id (message-group-id number-of-icp-bytes)
;;; Type:	     ICP message type.
;;; Purpose:         Provide the remote ICP process with a measurement of network
;;;                  clogging.
;;; Arguments:       message-group-id is of ICP value type unsigned-integer and is
;;;                  the identifier of the current ICP message group.
;;;                  number-of-icp-bytes is since the last i-am-alive was transmitted
;;;                  by the ICP process which sends this message-group-id message.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (end-icp-message-group in INT2).
;;; Prerequisites:   initialize-I-am-alive-info must have been called on 
;;;                  current-icp-socket.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; Message Group IDs are positive fixnums which wrap around at
;;; most-positive-fixnum (see documentation for I-am-alive mechanism).

(def-icp-message-type message-group-id
		      ((unsigned-integer message-group-id)
		       (unsigned-integer number-of-icp-bytes))
  (runtime-current-system-case
    ((ab telewindows)
     (declare-ignorable-icp-arguments number-of-icp-bytes)
     (let* ((I-am-alive-info? (I-am-alive-info? current-icp-socket)))
       (when I-am-alive-info?
	 (setf (id-for-last-message-group-handled I-am-alive-info?)
	       message-group-id)
	 (incff (number-of-message-groups-handled-since-last-I-am-alive-was-sent
		  I-am-alive-info?))
	 (send-I-am-alive-if-necessary current-icp-socket I-am-alive-info?))))
    (gsi
      (declare-ignorable-icp-arguments message-group-id number-of-icp-bytes))))
      



;;; Message-group-id-difference computes the difference between two message group
;;; ids.  This is used to compute the number of outstanding message groups for
;;; purposes of flow control.  Message-group-id-difference assumes that
;;; message-group-id-1 is always "larger" or the same as message-group-id-2; it
;;; assumes that message-group-1 has wrapped around if it is less than
;;; message-group-id-2.

(def-substitution-macro message-group-id-difference
			(message-group-id-1 message-group-id-2)
  (if (>=f message-group-id-1 message-group-id-2)
      (-f message-group-id-1 message-group-id-2)
      (+f message-group-id-1
	  (-f most-positive-fixnum message-group-id-2)
	  1)))

;; See documentation for message-group-ids.



(defun number-of-outstanding-message-groups (I-am-alive-info)
  (declare (eliminate-for-gsi))
  (message-group-id-difference
    (id-for-last-message-group-written I-am-alive-info)
    (id-for-last-message-group-handled-by-remote-socket 
      I-am-alive-info)))

;; The message group id in the id-for-last-message-group-written slot will always
;; be ahead of, or the same as, the message group id in the
;; id-for-last-message-group-handled-by-remote-socket slot.  Thus,
;; id-for-last-message-group-written will always be <
;; id-for-last-message-group-handled-by-remote-socket except when it has wrapped
;; around.  This is consistent with assumptions made by
;; message-group-id-difference.



;;; `Byte-allotment-for-icp-output-port' allows the client of an icp output port to
;;; sense how many bytes it is approprate to push into the port at this time.

;;; Clients must use this routine to avoid overloading the channel.  Clients
;;; may use this routine to defer work for as long as possible (presumably work
;;; done later is better informed).

;;; It returns two values both are fixnums that suggest how many bytes (8 bit
;;; bytes) can you should push into the channel at this time.  The first
;;; recommends a number of bytes to achieve full loading.  The second is a
;;; maximum number to avoid overflowing buffers (aka clogged).

;;; It takes two arguments, the icp-output-port, and an interval in units of
;;; fixnum-time.  The interval is the client's estimate of when he would next
;;; consider pushing work into the channel after consuming this allotment.

;;; These numbers are only a best estimate, since the underlying implementation
;;; may provide incomplete information.  The client should make a best effort
;;; to obey this "push back" to avoid the risk of channel clogging.  It is
;;; recognized that the client maybe unable to accurately preflight his load.

;;; The routine might compute it's result on the basis of: (a) channel (round
;;; trip) transmission rate, (b) maximum channel buffer sizes, (c) current
;;; channel buffer contents, and (d) prefered channel loading.

;;; The routine might request more bytes than is oviously implied by the given
;;; polling interval and the current transmission rate when it knows that the
;;; channel has internall polling rates larger than those of the client.

;;; A trival client might use this routine as so:
;;;  (loop 
;;;   while (< 0 (byte-allotment-for-icp-output-port icp-output-port 100))
;;;   do (send-work icp-output-port))
;;; Of course, there is no promise that this loop will terminate.

;; ben 3/16/93, 6/9/93

(defun byte-allotment-for-icp-output-port (icp-output-port interval-as-fixnum-time)
  (declare (eliminate-for-gsi))
  (let* ((i-am-alive-info? (parent-icp-socket icp-output-port))

	 ;; These numbers seem plausable to JRA, but ben thinks
	 ;; they are sadly low.
	 (channel-transmission-rate   100000)   ;; 100K bytes/second
	 (maximum-channel-buffer-size 100000)   ;; 100K bytes
	 
	 (current-amount-enqueued-in-channel-buffer
	   (if I-am-alive-info?
	       (twicef (number-of-outstanding-icp-bytes I-am-alive-info?))
	       0))
	 (prefered-channel-loading 1)

	 (maximum-bytes-to-avoid-clogging
	   (-f maximum-channel-buffer-size
	       current-amount-enqueued-in-channel-buffer))

	 ;; Remember it takes care not to overflow
	 (bytes-to-achieve-full-loading
	   (maxf maximum-bytes-to-avoid-clogging
		 (*f 
		   (roundf
		     channel-transmission-rate      ;; +21 bits (i.e. <= 1Meg)
		     fixnum-time-units-per-second)  ;; - 3 bits (i.e. 60)
		   interval-as-fixnum-time          ;; + 4 bits (i.e. less than a few seconds)
		   prefered-channel-loading))))     ;; + 3 bits -> 22 bits

    (values bytes-to-achieve-full-loading
	    maximum-bytes-to-avoid-clogging)))

;; The transmission-rate, max buffer size, and perfered-channel-loading
;; bindings are extremely bogus estimates of the channel, but they are the best
;; I've got.  - ben 3/16/93 Updated to reflect Jim's intuitions, which are much
;; more pessimistic than mine. - ben 6/09/92

;; The I am alive info can't be used to get a tranmission rate estimate since
;; it doesn't currently record the enqueue time of the work it is tracking.
;; - ben 6/09/92



;;;; ICP Debugging


(defun dump-icp-buffer (icp-buffer)
  (format t "
-------------
ICP Buffer ~a:
-------------
"
	  icp-buffer)
  (loop with j = 0
	for i from 1
	      below (number-of-icp-bytes-in-buffer
		      icp-buffer)
	
	as icp-byte = (get-icp-byte icp-buffer i)
	
	do (if (and (>f icp-byte
			#.(icp-message-type-code-offset))
		    (<f icp-byte
			#.(+ (icp-message-type-code-offset)
			     (icp-message-handler-array-size))))
	       (progn 
		 (format t "~%~a ~(~a~)~%"
			 (svref icp-message-handler-array
				(-f icp-byte #.(icp-message-type-code-offset)))
			 icp-byte)
		 (setq j 0))
	       
	       (progn
		 (incff j)
		 (format t "~a" icp-byte)
		 (when (=f (modf-positive j 8) 0) (format t "~%"))))))



;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter icp-message-out-of-synch-case-2-warning
  "~5T Protocol out-of-synch (case 2)")
)
			   
(defun icp-case-2-error (icp-input-port
			  message-series-byte-count index-of-icp-byte-position
			  icp-buffer? next-icp-byte?
			  number-of-icp-bytes-in-buffer
			  number-of-icp-bytes-left-in-buffer
			  contains-end-of-message-group?
			  icp-message-type-code-offset
			  icp-message-handler-array-size)
  (format
    t "~%~5T Next ICP byte, ~d, not a valid message type code!~%"
    next-icp-byte?)
  (format t "~%ICP: Protocol out-of-synch (case 2)! ~%")
  (format t "~5T ICP Socket Type: ~a~%"
	  (type-of-icp-connection (parent-icp-socket icp-input-port)))
  (format t "~5T Remote Host Name: ~a~%"
	  (icp-connection-name (parent-icp-socket icp-input-port)))
  (format t "~5T message-series-byte-count: ~a~%"
	  message-series-byte-count)
  (format t "~5T index-of-icp-byte-position: ~a~%"
	  index-of-icp-byte-position)
  (format t "~5T icp-buffer?: ~a~%"
	  icp-buffer?)
  (format t "~5T next-icp-byte?: ~a~%"
	  next-icp-byte?)
  (format t "~5T contains-end-of-message-group?: ~a~%"
	  contains-end-of-message-group?)
  (format t "~5T number-of-icp-bytes-in-buffer: ~a~%"
	  number-of-icp-bytes-in-buffer)
  (format t "~5T number-of-icp-bytes-left-in-buffer: ~a~%"
	  number-of-icp-bytes-left-in-buffer)
  (format t "~5T #.(icp-message-type-code-offset): ~a~%"
	  icp-message-type-code-offset)
  (format t "~5T #.(+ (icp-message-type-code-offset)~%~
	     ~5T      (icp-message-handler-array-size)): ~a~%"
	  (+f icp-message-type-code-offset
	      icp-message-handler-array-size))
  (dump-icp-buffer icp-buffer?)
  (current-system-case
    ((ab telewindows)
     (icp-error #.icp-message-out-of-synch-case-2-warning)
     nil)
    (gsi (signal-gsi-icp-message-out-of-synch-case-2-error))))


;; Broke up format statements in icp-case-2-error so control strings adhere to
;; Chestnut size constraints.  Fixed a problem with printing the wrong item while
;; I was at it.  jh, 2/21/91.






;;;; Miscellaneous Network Utilities





;;; Declaration:     get-local-host-name ()
;;; Type:	     Lisp function.
;;; Purpose:	     Get the name of the local network host.
;;; Arguments:	     None.
;;; Return behavior: Returns the name for the local network host as a string.  The
;;;                  caller should not reclaim this string, as it is cached.
;;; Users:           ICP internals (local-icp-connection-p in INT4), G2 "network
;;;                  info" table (FACILITIES), G2 network info system procedures
;;;                  (FILE-IO), G2 remote procedures (G2-RPC1 and G2-RPC2),
;;;                  G2 foreign functions (G2-FOREIGN), G2 player (PLAYER),
;;;                  Telewindows to pass over the "client" host's name
;;;                  (TELEWINDOWS).
;;; Prerequisites:   None.
;;; Side effects:    Caches the hostname string internally.
;;; Non-local exits: None.
;;; Memory impact:   One time only, when the host name string is cached.

;;; Get-local-host-name returns a string (which may be shared) which is the name
;;; for the local host.  If this cannot be determined for any reason, nil is
;;; returned instead.

(def-system-variable local-host-name INT3B
  (:funcall get-unix-host-name))

(defun get-local-host-name ()
  (or local-host-name
      (setq local-host-name (get-unix-host-name))))


;; Note that as this is now implemented, if the host name changes while G2 is
;; running and after this has been called, then the cached host name will be
;; invalid.  This may have to be fixed.




;;; Declaration:     get-current-icp-contact-port-number-or-name-if-any ()
;;; Type:	     Lisp function.
;;; Purpose:	     Get the address on which G2 is listening for connections.
;;; Arguments:	     None.
;;; Return behavior: Returns a fixnum or a string representing the G2 listener
;;;                  address, or nil if this is not available or cannot be
;;;                  determined.
;;; Users:           G2 "network info" table (FACILITIES), G2 network info system
;;;                  procedures (FILE-IO), function (G2-FOREIGN), G2 player
;;;                  (PLAYER).
;;; Prerequisites:   None.
;;; Side effects:    Caches the address string internally.
;;; Non-local exits: None.
;;; Memory impact:   At most one time only.  If the address is a string it is 
;;;                  cached.

;;; The function `get-current-icp-contact-port-number-or-name-if-any' returns
;;; the port number or name to which contacts to ICP of the current process
;;; should be addressed, if available.

;; Review this! (MHD 5/6/90)
;; ;;; However, note that the value is undefined if ICP
;; ;;; is unavailable in this process.

;;; This will appear to a user of G2 as the value for the "Port Number or Name"
;;; slot of a Network Information table, available under the Main Menu
;;; Miscellany menu.

(defun get-current-icp-contact-port-number-or-name-if-any ()
  (let ((symbol? 'unix-tcp-listener-port))
    (if (and symbol? (boundp symbol?))
	(symbol-value symbol?))))






;;; Message types for network security.

;;; There are currently (1/30/91) two ICP messages associated with network
;;; security.  Both these messages only affect ICP listener sockets, that is,
;;; sockets opened by a request from a remote process.  Examples of listener
;;; sockets are those created by Telewindows or on the server side of a G2-to-G2
;;; connection.  Non-listener sockets are those created by the local G2 process,
;;; typically through the mediation of some G2 object with an interface
;;; capability, such as sockets used in GSI, GSPAN, or client side of a G2-to-G2
;;; connection.

;;; The first message, connection-denied, is sent from a G2 which is not accepting
;;; remote connections.  This message is sent to a remote process which has
;;; requested an ICP socket.  The socket stays open just long enough to transmit
;;; this message, then closes at the next call to process-icp-sockets.  Briefly
;;; opening the socket is not currently thought to be a security hazard.

;;; The second message, connection-shutdown-imminent, is sent from a G2 at the
;;; moment it disallows remote connections.  This message is sent to a remote
;;; process which possesses an existing ICP socket.  This announces to the remote
;;; process that the connection will close within a given fixed interval.  The
;;; idea here is that extant sockets have been created with the permission of the
;;; local G2 and deserve some advance warning.  Having a fixed interval prevents
;;; the remote process from taking advantage of a handshaking protocol to "stall"
;;; and keep the disallowed connection open indefinitely.

;;; Declaration:	 connection-denied ()
;;; Type:		 ICP message type.
;;; Purpose:	 Convey to a remote process that this process is not accepting
;;;                  ICP connections.
;;; Arguments:	 None.
;;; Return behavior: No useful value.
;;; Users:		 ICP internals (warn-disallowed-icp-listener-connections in
;;;                  INT3).
;;; Prerequisites:	 None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:	 None.
;;; Notes:           This is part of the G2 network security facility, not yet

(def-icp-message-type connection-denied ()
  (current-system-case
    (gsi
      (gsi-connection-error 'gsi_initiate_connection
			    gsi-connection-denied
			    (icp-connection-name current-icp-socket)))
    (t
      (notify-user-if-possible
	"ICP connection \"~a\" is closed to remote users.~%"
	(icp-connection-name current-icp-socket)))))

(def-icp-message-type no-license ()
  (current-system-case
    (gsi
      (gsi-connection-error 'gsi_initiate_connection  ; originating function
			    gsi-no-license            ; error-code
			    (icp-connection-name current-icp-socket))) ; args
    (t
      (notify-user-if-possible
	"No license is available for a connection over \"~a\".~%"
	(icp-connection-name current-icp-socket)))))


;;; Declaration:     connection-shutdown-imminent (time-until-shutdown)
;;; Type:	     ICP message type.
;;; Purpose:         Convey to a remote process that had previously been permitted
;;;                  to connect, that this process is shutting down all ICP
;;;                  connections.
;;; Arguments:	     time-until-shutdown is of ICP value type unsigned integer and
;;;                  provides the time until the sender will shut down all ICP 
;;;                  connections.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (warn-disallowed-icp-listener-connections in 
;;;                  INT3).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           This is part of the G2 network security facility, not yet
;;;                  implemented as of version 3.0.

(def-icp-message-type connection-shutdown-imminent
                      ((unsigned-integer time-until-shutdown))
  (current-system-case
    (gsi time-until-shutdown nil)
    (t
      (notify-user-if-possible
	"ICP connection \"~a\" will be shut down within ~a seconds.~%~
     That process has disallowed remote connections.~%"
	(icp-connection-name current-icp-socket)
	time-until-shutdown))))



;;; Declaration:     warn-disallowed-icp-listener-connections
;;;                    (new-icp-listener-connections)
;;; Type:	     Lisp function.
;;; Purpose:         Warn all remote ICP processes that this process is shutting
;;;                  down all ICP connections.
;;; Arguments:       An icp-list of icp-socket-structures which had attemped to
;;;                  initiate an ICP connection after this process had decided to
;;;                  shut down all connections.
;;; Return behavior: No useful value.
;;; Users:	     ICP internals (check-for-pending-icp-requests in INT2).
;;; Prerequisites:   None.
;;; Side effects:    Sends the ICP message connection-shutdown-imminent on all
;;;                  listener sockets in active-icp-sockets.  Sends the ICP message
;;;                  connection-denied to all connections in
;;;                  new-icp-listener-connections.
;;; Non-local exits: None.
;;; Memory impact:   May allocate ICP buffers to transmit ICP messages.  May fill
;;;                  internal network buffers of the operating system.
;;; Notes:           This is part of the G2 network security facility, not yet
;;;                  implemented as of version 3.0.

(defun-allowing-unwind disallow-new-icp-listener-connection (new-icp-socket)
  (declare (eliminate-for-gsi))
  (writing-icp-message-group ((icp-output-port new-icp-socket))
    (send-icp-connection-denied))
  (flush-and-shutdown-icp-socket new-icp-socket))

(defun-allowing-unwind no-license-for-new-icp-listener-connection (new-icp-socket)
  (declare (eliminate-for-gsi))
  (writing-icp-message-group ((icp-output-port new-icp-socket))
    (send-icp-no-license))
  (flush-and-shutdown-icp-socket new-icp-socket))

(defun-allowing-unwind warn-disallowed-icp-listener-connections
       (new-icp-listener-connections &optional specific-clients?)
  (declare (no-op-for-gsi))
  ;; Refuse new listener connections.  Shut them down right away unless
  ;; specific-clients? were supplied.  In that case, we have to let the new
  ;; connections alone until they send their first ICP message, letting us
  ;; determine which client is involved.
  (unless specific-clients?
    (loop for new-icp-socket in new-icp-listener-connections
	  do (disallow-new-icp-listener-connection new-icp-socket)))
  ;; Warn old listener connections and begin counting towards shutdown.  This
  ;; will allow them time to receive the ICP shutdown-imminent message.
  (dolist-safely (icp-socket active-icp-sockets)
    (let ((listener-client? (icp-socket-listener-client? icp-socket)))
      (when (and listener-client?
		 (listener-socket icp-socket)
		 (not (icp-connection-refused-p icp-socket))
		 (if specific-clients?
		     (memq listener-client? specific-clients?)
		     t))
	(writing-icp-message-group ((icp-output-port icp-socket))
	  (send-icp-connection-shutdown-imminent 
	    shutdown-interval-for-disallowed-icp-connection-in-seconds))
	(setf (icp-socket-shutdown-timer icp-socket) (get-fixnum-time))
	(setf (icp-connection-refused-p icp-socket) t)
	(icp-push icp-socket refused-icp-listener-connections)))))

;; End file with CR


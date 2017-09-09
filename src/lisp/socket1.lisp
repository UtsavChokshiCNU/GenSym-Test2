;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SOCKET1 - TCP Sockets for general purpose use

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Judy Anderson

;;;; Introduction

;;; ICP sockets have too much overhead and special-purpose code for client
;;; applications such as web servers.  So, we create here a tcp-socket structure
;;; for use by such applications.

;;; This file contains things which can be shared with weblink as well; see
;;; socket2 for the G2-specific socket mechanism (based on tcp-socket),
;;; including system procedures.






;;;; TCP sockets


;;; The structure `tcp-socket' is an abstract base for all TCP/IP sockets that
;;; do not use ICP.  Some of its slots and methods could be moved up to the
;;; `socket' base structure, if the corresponding stuff on `icp-socket' were
;;; factored out.  (See the INT1 module.)


(def-structure (tcp-socket (:include socket))
  ;; The structure slots `socket-host' and `socket-port' hold the host name
  ;; (text string) and port number (fixnum integer) that this socket is
  ;; currently connected to (or in the process of connecting to), or nil if it
  ;; has not yet been connected or if the connection has been closed.
  (socket-host nil :reclaimer reclaim-if-text-string)
  (socket-port nil)

  ;; The structure slot `socket-handle' holds the socket handle (a fixnum
  ;; integer) for the underlying socket at the C level if the socket is
  ;; connected, or nil otherwise.
  (socket-handle nil)
  ;; Unfortunately due to a timing issue, we also need a separate "is the socket
  ;; open" flag.
  (socket-open-p t)
  (socket-buffer? nil :reclaimer reclaim-if-variable-fill-icp-buffer)
  (socket-buffer-start-pointer 0)
  (socket-buffer-end-pointer 0)
  (socket-output-buffer? nil :reclaimer reclaim-if-socket-buffer)
  (tcp-socket-close-task nil :reclaimer cancel-task)
  )


;;; The function `connect-socket' takes a tcp-socket structure and connects
;;; to a remote host name and port number via TCP/IP.  It returns immediately,
;;; without waiting for the connect operation to complete.  When it does
;;; complete, the `handle-network-connect' structure method will be invoked.
;;; Note that if it completes immediately, we must call handle-network-connect
;;; ourselves.

(defun-simple connect-socket (socket host port secure?)
  ;; TO DO: error if already connected
  (let* ((network-pathname (tformat-gensym-string "TCP_IP:~a:~a" host port))
	 (port-string (tformat-gensym-string "~a" port))
	 (handle (network-connect network-pathname host port-string secure?)))
    (reclaim-gensym-string network-pathname)
    (reclaim-gensym-string port-string)
    (unless (<f handle 0)
      (setf (socket-host socket) (copy-text-string host))
      (setf (socket-port socket) port)
      (setf (socket-handle socket) handle)
      (register-socket-to-handle socket handle)
      (when (network-connected-p handle)
	(handle-network-connect
	  socket
	  (c-network-get-last-error-code handle)))
      socket)))


;;; The structure method `handle-network-connect' for tcp-socket structures is
;;; called when a connect operation completes.  This method does nothing, but
;;; can be overridden for derived socket structures to notify the G2 program.

(def-structure-method handle-network-connect (tcp-socket error-code)
  (declare (ignore tcp-socket error-code))
  nil)





;;; The foreign function `c-network-write-string' writes a string to a socket
;;; handle.  This calls the same C function as `c-network-write', but this does
;;; the right thing with strings (instead of requiring a
;;; variable-fill-icp-buffer).

(def-gensym-c-function c-network-write-string
		       (:fixnum-int "g2ext_network_write")
  ((:fixnum-int handle)
  (:string buffer)
  (:fixnum-int offset)
  (:fixnum-int length)))



;;; Writing to sockets: we handle either strings or sequences of bytes, with two
;;; different functions, `write-to-socket', and `write-sequence-to-socket'.
;;; Overrun is handled by having a queue of buffers to be output, and when we
;;; get an event from the low-level networking code, we try to send the rest of
;;; the buffers that we have.


(def-structure (socket-output-buffer)
  (socket-output-buffer-data nil :reclaimer reclaim-socket-buffer-data)
  (socket-output-buffer-data-pointer 0)
  (socket-output-buffer-buffer nil :reclaimer reclaim-if-variable-fill-icp-buffer)
  (socket-output-buffer-pointer 0)
  (socket-output-buffer-next nil))


(defun-simple reclaim-socket-buffer-data (data)
  (cond ((stringpw data)
	 (reclaim-text-string data))
	#-gsi-web
	((evaluation-sequence-p data)
	 (reclaim-evaluation-sequence data))))

(defun-simple reclaim-if-socket-buffer (socket-buffer)
  (when socket-buffer (reclaim-socket-output-buffer socket-buffer)))


(defun add-buffer-to-socket (sob tcp-socket)
  (if (socket-output-buffer? tcp-socket)
      (loop with prev = (socket-output-buffer? tcp-socket)
	    while (socket-output-buffer-next prev)
	    do
	(setq prev (socket-output-buffer-next prev))
	    finally
	      (setf (socket-output-buffer-next prev) sob))
      (setf (socket-output-buffer? tcp-socket) sob)))



(defun-simple write-to-socket (tcp-socket string)
  (let* ((length (text-string-length string))
	 (bytes-written
	   (if (socket-handle tcp-socket)
	       (c-network-write-string (socket-handle tcp-socket)
				       string 0 length)
	       -1)))
    (cond ((=f bytes-written length)) ;;Joy, return T.
	  ((>=f bytes-written 0)
	   ;;Partial write, save and return blocked
	   (let ((sob (make-socket-output-buffer)))
	     (setf (socket-output-buffer-data sob) (copy-text-string string))
	     (setf (socket-output-buffer-pointer sob) bytes-written)
	     (add-buffer-to-socket sob tcp-socket))
	   'blocked)
	(t 'error)))) ;; negative return indicates error.



;;;Write out bytes from a sequence rather than a string.  Limited to 8 bit
;;;bytes.  Under #-gsi-web because evaluation sequences are not available to
;;;GSI, and this file is shared with Weblink, so we need to be careful in which
;;;functions may access the sequence when one exists.

;;;Sending a sequence is complicated: we have to convert the data to something C
;;;can chew on, using icp buffers.  But if the sequence is longer than that, we
;;;have to loop refilling.  Finally, we have to cope with possible blocked
;;;socket.

;;;And, we have to do this in two places, once for initiating a write, and once
;;;for continuing it (see below notes for `handle-write-event'.)  So, borrowing
;;;an idea from file-sysproc, we have an unhygienic macro
;;;`writing-sequence-idiom' which expects and exports a specific set of
;;;variables and lets the body only deal with how to handle blocking: if we're
;;;initiating the write, we need to allocate a socket output buffer; otherwise
;;;we only need to update our current one.

(defmacro writing-sequence-idiom (return-from begin-value overrun-form)
  `(let ((buffer (make-variable-fill-icp-buffer)))
     (unwind-protect
	  (loop for s-index from ,begin-value below (evaluation-sequence-length sequence)
		for octet = (evaluation-sequence-aref sequence s-index)
		with stop = (1-f (evaluation-sequence-length sequence))
		as b-index from 0 do
	    (setf (aref-variable-fill-icp-buffer buffer b-index) (logandf octet #xFF))
	    (when (or (=f b-index (1-f #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes)))
		      (=f s-index stop))
	      (let ((bytes-written
		      (if (socket-handle tcp-socket)
			  (c-network-write (socket-handle tcp-socket) buffer 0 (1+f b-index))
			  -1)))
		(cond ((=f bytes-written (1+f b-index))
		       (setf b-index -1)) ;; it'll get incremented to 0 by loop
		      ((>=f bytes-written 0)
		       ,overrun-form
		       (return-from ,return-from 'blocked))
		      (t (return-from ,return-from 'error))))))
       (reclaim-variable-fill-icp-buffer buffer))))



#-gsi-web
(defun-allowing-unwind write-bytes-to-socket (tcp-socket sequence)
  (writing-sequence-idiom
    write-bytes-to-socket 0
    (let ((sob (make-socket-output-buffer)))
      (setf (socket-output-buffer-data sob)
	    (allocate-new-evaluation-sequence-copy sequence))
      (setf (socket-output-buffer-pointer sob)
	    (-f s-index (-f b-index bytes-written)))
      (add-buffer-to-socket sob tcp-socket))))


;;; The structure method `handle-write-event' for tcp-socket structures is
;;; called when a write operation completes.  It calls
;;; `try-to-send-socket-buffer' which figures out what kind of buffer we have
;;; and either deals itself (strings are easy) or passes the sequence buffer to
;;; `try-to-send-socket-sequence'.  Recursive, because if we succeeded in
;;; sending one whole buffer, perhaps another will work.

(def-substitution-macro pop-and-send-next-socket-buffer (tcp-socket sob)
  (setf (socket-output-buffer? tcp-socket)
	(socket-output-buffer-next sob))
  (reclaim-socket-output-buffer sob)
  (try-to-send-socket-buffer tcp-socket))

#-gsi-web
(defun-allowing-unwind try-to-send-socket-sequence (tcp-socket)
  (let* ((sob (socket-output-buffer? tcp-socket))
	 (sequence (socket-output-buffer-data sob)))
    (writing-sequence-idiom
      try-to-send-socket-sequence
      (socket-output-buffer-pointer sob)     ;start at
      (setf (socket-output-buffer-pointer sob) 
	    (-f s-index (-f b-index bytes-written))))
    ;;If writing-sequence-idiom didn't return-from this function,
    ;;we had complete success, and must move on to the next buffer
    (pop-and-send-next-socket-buffer tcp-socket sob)))

(defun try-to-send-socket-buffer (tcp-socket)
  (let ((sob (socket-output-buffer? tcp-socket)))
    (cond ((null sob))
	  ((stringpw (socket-output-buffer-data sob))
	   (let* ((string (socket-output-buffer-data sob))
		  (current (socket-output-buffer-pointer sob))
		  (length (-f (text-string-length string) current))
		  (bytes-written
		    (if (socket-handle tcp-socket)
			(c-network-write-string (socket-handle tcp-socket)
						string current length)
			-1)))
	     (cond ((=f bytes-written length)
		    ;;success -- get rid of this buffer and try the next one.
		    (pop-and-send-next-socket-buffer tcp-socket sob))
		   ((>=f bytes-written 0)
		    (incff (socket-output-buffer-pointer sob) bytes-written))
		   (t
		    (notify-user-at-console "Error sending socket buffer")))))
	  #-gsi-web
	  ((evaluation-sequence-p (socket-output-buffer-data sob))
	   (try-to-send-socket-sequence tcp-socket))
	  (t
	   (notify-user-at-console "ERROR: Unrecognized value type in network I/O.  Some data may be dropped.")
	   (pop-and-send-next-socket-buffer tcp-socket sob)))))




(def-structure-method handle-write-event (tcp-socket error-code)
  (declare (ignore error-code))	       ;TO DO: handle error
  (try-to-send-socket-buffer tcp-socket)
  nil)


;;; The structure method `handle-read-event' for tcp-socket structures is called
;;; when a read event is received, signalling that some bytes are available to
;;; be read.  This method does nothing, but see the overriding method for
;;; blocking-socket, in socket2.

(def-structure-method handle-read-event (tcp-socket error-code block-p)
  (declare (ignore tcp-socket error-code block-p))	;TO DO: handle error
  nil)

;;; The buffering system here are only has one buffer, rather than the full set
;;; of linked buffers that ICP provides, so it is possible for there to be data
;;; buffered by the operating system in addition to data buffered in the
;;; in-memory buffer.  The contract of this function is to return T if any data
;;; was read.  If the socket has been closed by the other end, then the
;;; underlying C socket is closed from this end, but buffered data may still be
;;; available for read.
(defun-simple read-buffer-from-socket (tcp-socket)
  (unless (socket-buffer? tcp-socket)
    (setf (socket-buffer? tcp-socket) (make-variable-fill-icp-buffer)))
  (let (octets-read-or-status
	 (handle (socket-handle tcp-socket)))
    (setf octets-read-or-status
	  (if handle
	      (c-network-read handle (socket-buffer? tcp-socket)
			      (socket-buffer-end-pointer tcp-socket)
			      #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
	      ne-eof-value))
    (cond ((>f octets-read-or-status 0)
	   (setf (socket-buffer-end-pointer tcp-socket)
		 (+ (socket-buffer-end-pointer tcp-socket) octets-read-or-status))
	   t)
	  ((=f octets-read-or-status ne-blocked-value)
	   nil)
	  ((=f octets-read-or-status ne-eof-value)
	   (close-socket tcp-socket)
	   nil)
	  ((=f octets-read-or-status ne-error-value)
	   ;; Should do something special about error
	   (close-socket tcp-socket)
	   nil))))

(defun data-available-p (tcp-socket)
  (>f (socket-buffer-end-pointer tcp-socket)
      (socket-buffer-start-pointer tcp-socket)))

;;; Read some data if it is available and will fit.  Then, return whether or not
;;; data is available (whether or not we read this time or another time)
(defun maybe-read-buffer-from-socket (tcp-socket)
  (if (and (socket-open-p tcp-socket)
	   (<f (socket-buffer-end-pointer tcp-socket)
	       #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes)))
      (read-buffer-from-socket tcp-socket))
  (data-available-p tcp-socket))

(defun peek-socket (tcp-socket)
  (if (maybe-read-buffer-from-socket tcp-socket)
      (aref-variable-fill-icp-buffer
	(socket-buffer? tcp-socket) (socket-buffer-start-pointer tcp-socket))))

(defun read-byte-from-socket (tcp-socket)
  (when (maybe-read-buffer-from-socket tcp-socket)
    (prog1 
	(aref-variable-fill-icp-buffer
	  (socket-buffer? tcp-socket) (socket-buffer-start-pointer tcp-socket))
      (incff (socket-buffer-start-pointer tcp-socket))
      (when (=f (socket-buffer-start-pointer tcp-socket)
		#.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
	(setf (socket-buffer-start-pointer tcp-socket)
	      0
	      (socket-buffer-end-pointer tcp-socket)
		0)))))


;;; The function `read-from-socket' reads all available bytes from a socket
;;; (without blocking) and returns them as a text string.  Even if the socket
;;; has been closed, if there are buffered bytes available, they will be
;;; returned.

(defun read-from-socket (tcp-socket)
  (twith-output-to-text-string
    (loop for got-data = (maybe-read-buffer-from-socket tcp-socket)
	  while got-data do
      (loop for index from (socket-buffer-start-pointer tcp-socket)
		      below (socket-buffer-end-pointer tcp-socket) do
	(twrite-char (aref-variable-fill-icp-buffer
		       (socket-buffer? tcp-socket) index))
	    finally
	      (if (/=f (socket-buffer-end-pointer tcp-socket)
		       #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
		  (setf (socket-buffer-start-pointer tcp-socket)
			(socket-buffer-end-pointer tcp-socket))
		  (setf (socket-buffer-start-pointer tcp-socket)
			0
			(socket-buffer-end-pointer tcp-socket)
			0))))))


;;;Used for read-line.  end-char is an integer representing an ascii value
;;;(e.g. 10 for linefeed.)  Returns string-so-far and a flag saying whether you
;;;need to keep calling it.  T for yes, NIL for you're done.  The final string
;;;does contain the target character.
(defun read-from-socket-until-char (tcp-socket end-char)
  (let* ((keep-going t)
	 (value
	   (twith-output-to-text-string
	     (loop for got-data = (maybe-read-buffer-from-socket tcp-socket)
		   while (and keep-going
			      got-data) do
	       (loop for index from (socket-buffer-start-pointer tcp-socket)
			       below (socket-buffer-end-pointer tcp-socket)
		     as char = (aref-variable-fill-icp-buffer
				 (socket-buffer? tcp-socket) index) 
		     while keep-going
		     do
		 (if (=f char end-char) (setq keep-going nil))
		 (twrite-char char)
		     finally
		       (if (<f index
			       #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
			   (setf (socket-buffer-start-pointer tcp-socket)
				 index)
			   (setf (socket-buffer-start-pointer tcp-socket)
				 0
				 (socket-buffer-end-pointer tcp-socket)
				 0)))))))
    (values value keep-going)))


;;;Similar to read-from-socket-until-char, this reads from the buffer, up until
;;;it gets to N chars, or whatever's available, refreshing as necessary.
;;;Returns the string and the number of chars left to read next time
(defun read-n-chars-from-socket (tcp-socket n)
  (let* ((remaining n)
	 (value
	   (twith-output-to-text-string
	     (loop for got-data = (maybe-read-buffer-from-socket tcp-socket)
		   while (and (>f remaining 0)
			      got-data) do
	       (loop for index from (socket-buffer-start-pointer tcp-socket)
			       below (socket-buffer-end-pointer tcp-socket)
		     repeat remaining
		     as char = (aref-variable-fill-icp-buffer
				 (socket-buffer? tcp-socket) index) 
		     do
		 (twrite-char char)
		     finally
		       (setf remaining
			     (-f remaining
				 (-f index
				     (socket-buffer-start-pointer tcp-socket))))
		       (if (<f index
			       #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
			   (setf (socket-buffer-start-pointer tcp-socket)
				   index)
			   (setf (socket-buffer-start-pointer tcp-socket)
				 0
				 (socket-buffer-end-pointer tcp-socket)
				 0)))))))
    (values value remaining)))


;;;This is here for weblink to share.  Other callers are blocking-socket in
;;;socket2.  Because the signature is different from handle-network-accept
;;;method, we can't just use a tcp-socket method -- we need to know what kind
;;;of socket to create.  Returns T if it accepted a real connection, 'WOULD-BLOCK
;;;if there isn't anybody waiting, and NIL if it received an error.
(defun handle-network-accept-internals (listener-socket new-socket error-code)
  (let ((listener-handle (socket-handle listener-socket)))
    (unless (and listener-handle (=f error-code network-status-success))
      (notify-user-at-console "Error ~a on socket ~a before accept"
			      error-code listener-handle))
    (let* ((new-socket-handle (c-network-accept listener-handle)))
      (cond ((>f new-socket-handle 0)
	     (setf (socket-handle new-socket) new-socket-handle)
	     (setf (socket-host new-socket) (network-peer-address-string new-socket-handle))
	     (register-socket-to-handle new-socket new-socket-handle)
	     t)
	    ((=f new-socket-handle ne-blocked-value)
	     'WOULD-BLOCK)
	    (t
	     nil)))))



;;;; Closing sockets

;;; The structure method `handle-network-close' for tcp-socket structures is
;;; called when a socket has been closed by the other end.  This method just
;;; pretends like it was a read event and calls `handle-read-event', since some
;;; platforms (e.g. Solaris) don't actually have a close event and just send a
;;; read event in this case.  Either way, the close can be detected by calling
;;; `read-from-socket', which will eventually hit EOF.

(def-structure-method handle-network-close (tcp-socket error-code)
  ;; TO DO: what should block-p be in this case?
  (handle-read-event tcp-socket error-code nil)
  ;;See if read closed it already, if not, we need to close.
  (when (socket-open-p tcp-socket)
    (close-socket tcp-socket)))



;;; The function `close-socket' closes a socket.  If there is pending data that
;;; has been read into the buffer, but not extracted by user programs, then we
;;; merely set the flag for closing, and require that the user programs call
;;; close a second time in order to get the cleanups enqueued.  This will
;;; enable user program to receive data which was read into buffers before the
;;; connection was closed.  Optional force argument overrides.

(defun close-socket (tcp-socket &optional force)
  (when (socket-open-p tcp-socket)
    (c-network-close (socket-handle tcp-socket))
    (setf (socket-open-p tcp-socket) nil)
    (register-socket-to-handle nil (socket-handle tcp-socket))
    (setf (socket-handle tcp-socket) nil))
  (when (or force (not (data-available-p tcp-socket)))
    (enqueue-tcp-cleanups tcp-socket)))

(defun-void socket-close-cleanups (tcp-socket)
  (setf (socket-port tcp-socket) nil)
  (reclaim-if-text-string (socket-host tcp-socket))
  (setf (socket-host tcp-socket) nil)
  (reclaim-structure tcp-socket))



(defun-void enqueue-tcp-cleanups (tcp-socket)
  (unless (schedule-task-in-place-p (tcp-socket-close-task tcp-socket))
    (with-current-scheduling ((tcp-socket-close-task tcp-socket) 0
			      nil nil t)
      (socket-close-cleanups tcp-socket))))


(def-structure-method handle-g2-reset (tcp-socket)
  (close-socket tcp-socket t))


;;;; Network hostnames

(def-gensym-c-function c-get-peer-address-string
    (:void "g2ext_get_peer_address_string")
  ((:fixnum-int socket-number)
   (:string buffer)
   (:fixnum-int max)))

(def-gensym-c-function c-get-peer-hostname
    (:void "g2ext_get_peer_hostname")
  ((:fixnum-int socket-number)
   (:string buffer)
   (:fixnum-int max)))


(defmacro network-peer-something (handle something)
  `(let ((buf (obtain-simple-gensym-string-of-quantized-length
		#.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))))
     (,something
	(c-network-get-fd-from-handle ,handle)
	buf #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
     (prog1
	 (copy-null-terminated-string-as-text-string buf)
       (reclaim-gensym-string buf))))

(defun network-peer-address-string (handle)
  (network-peer-something handle c-get-peer-address-string))
  

(defun network-peer-name (handle)
  (network-peer-something handle c-get-peer-hostname))


#|
(def-structure (mqtt-socket (:include tcp-socket))
    (mqtt-socket-receptacle nil))

(def-structure-method handle-network-connect (mqtt-socket error-code)
  (write-bytes-to-socket
   mqtt-socket
   (allocate-evaluation-sequence (list #x10 #x1e #x00 #x06 #x4d #x51 #x49 #x73 #x64 #x70 #x03 #x02 #x00 #x3c #x00 #x10 #x6d #x6f #x73 #x71 #x73 #x75 #x62 #x2f #x31 #x33 #x36 #x34 #x2d #x4d #x53 #x49)))
  nil)

(def-structure-method handle-read-event (mqtt-socket error-code block-p)
  (when (=f error-code network-status-success)
    (setf (mqtt-socket-receptacle mqtt-socket) (read-from-socket mqtt-socket))))
|#
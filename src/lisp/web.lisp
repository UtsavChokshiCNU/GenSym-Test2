;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WEB

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde



;;;; Backtrace

(defmacro with-backtrace ((format-string &optional
					 (arg1 :no-arg)
					 (arg2 :no-arg)
					 (arg3 :no-arg)
					 (arg4 :no-arg)) &body body)
  `(let ((exit-ok nil))
     (#+lucid lcl::unwind-protect
      #-lucid unwind-protect
	  (multiple-value-prog1
	    (progn ,@body)
	    (setf exit-ok t))
       (unless exit-ok
	 (format t "~%")
	 (format t ,format-string
		 ,@(cond
		     ((eql arg1 :no-arg) `())
		     ((eql arg2 :no-arg) `(,arg1))
		     ((eql arg3 :no-arg) `(,arg1 ,arg2))
		     ((eql arg4 :no-arg) `(,arg1 ,arg2 ,arg3))
		     (t                  `(,arg1 ,arg2 ,arg3 ,arg4))))))))


(defun abandon-ship (format-string &optional arg)
  (format t "~%Error occured:~%    ")
  (format t format-string arg)
  #+development
  (break)
  (thread-kill current-thread))

(defun abandon-ship-errcode (code)
  (abandon-ship "Error: ~D" code))





;;;; Open/Close TCP sockets


;;; `currently-open-tcpip-sockets' is a gensym list of fixnum,
;;; the socket indexes.

(defvar currently-open-tcpip-sockets ())



;;; Client Sockets

;;; Client sockets are used to connect to TCP/IP streams.  

(def-structure (client-socket
		 (:include weblink-socket)
		 (:constructor make-client-socket ())))

(def-generic-slow-method socket-connect (client-socket host port))



(def-slow-method socket-connect (client-socket host port)
  (with-backtrace ("socket-connect ~A:~D" host port)
    (let ((socket-number-or-errcode
	    (g2ext-tcpip-connect (coerce-into-foreign-string-pad host) port)))
      (cond
	((<f socket-number-or-errcode 0)
	 (note-issue-with-socket client-socket socket-number-or-errcode))
	(t
	 (socket-install client-socket socket-number-or-errcode)
	 (loop repeat 30
	       when (eq :ok (tcp-connection-check socket-number-or-errcode))
		 do (return nil)
	       doing (sleep 1)
	       finally
		 (note-issue-with-socket client-socket :connect-failure)))))))










;;;; Status of Sockets


;;; `tcpip_connection_check-1' takes a socket, and calls the code in tcp.c
;;; to obtain a sense of what the hell is going on.



(defun-allowing-unwind tcp-connection-check (socket-number)
  (with-backtrace ("checking status of connection")
    (let ((result (gw-tcpip-connection-check socket-number)))
      
;    (-1 :TCPIP_CONNECT_NO_SUCH_HOST)
;    (-2 :TCPIP_CONNECT_NOT_INTERNET_HOST)
;    (-3 :TCPIP_CONNECT_CANT_MAKE_SOCKET)
;    (-4 :TCPIP_CONNECT_CANT_MAKE_NONBLOCK_CONNECT)
;    (-5 :TCPIP_CONNECT_CANT_MAKE_NONBLOCK_SOCKET)
;    (-7 :TCPIP_CONNECT_FELL_OFF_END)
;    (-8 :TCPIP_CONNECT_WONT_RETRY)
;    (-9 :TCPIP_CONNECT_EMPTY_HOST)
      (cond
	((=f  1 result) :ok)
	((=f  0 result) :pending)
	((=f -1 result) :dead)
	((=f -6 result) :tcpip_connect_retry_select_failed)
	(t (abandon-ship-errcode result))))))



;;;; Read/Write Strings from TCP/IP Sockets


;;; `socket-write'






;;; `socket-write-string'

(defun-allowing-unwind socket-write-string (socket string)
  (with-backtrace ("Sending data")
    (let ((result
	    (gw-socket-write
	      (number-of-socket socket)
	      (coerce-into-foreign-string-pad string) 0 (length string))))
      (unless (=f result (length string))
	(note-issue-with-socket socket result)))))

(defun-allowing-unwind socket-write-line (socket line)
  (with-backtrace ("Sending data")
    (let* ((length (+ 2 (length line)))
	   (result
	     (gw-socket-write
	       (number-of-socket socket)
	       (coerce-into-foreign-string-pad-with-crlf line)
	       0 length)))
      (unless (=f result length)
	(bridge-log "socket-write-line ~S /= ~S" result length)
	(note-issue-with-socket socket result)))))




(defun-allowing-unwind socket-read-string (socket)
  (socket-poll-status socket)
  (prog1
      (with-backtrace ("Reading data")
	(let ((result
		(gw-socket-read
		  (number-of-socket socket)
		  current-foreign-string-pad max-of-foreign-string-pad)))
	  (let ((errno (gw-fetch-errno)))
	    (cond
	      ((or (=f 0 result)
		   (and (=f -1 result)
			(or (=f ENETRESET errno)
			    (=f ECONNABORTED errno))))
	       ;; Since we read only when data available, a zero implies EOF.
	       :eof)
	      ((<f 0 result)
	       (make-text-string-from-foreign-string-pad result))
	      (t
	       (note-issue-with-socket socket result)
	       :eof)))))
    (socket-poll-status socket)))


;;; `socket-data-available-p'
;;;   int socket_data_available_p(int sock)



(defun-allowing-unwind socket-data-available-p (socket)
  (socket-poll-status socket)
  (with-backtrace ("Polling for data")
    (let ((result (gw-socket-data-available-p (number-of-socket socket))))
      (cond
	((=f 0 result) nil)
	((=f 1 result) t)))))



















;;;; Fetch Styles


;;; `Fetch-style-info' is a global property that maps from
;;; a symbol to the fetch-style-info structure used to store
;;; the details of how to fetch a URL.

(def-global-property-name fetch-style-info)

(def-structure (fetch-style-info
		 (:constructor 
		   make-fetch-style-info
		   (name-of-fetch-style
		     verb-of-fetch-style-info
		     maximum-size-for-resource
		     return-server-prefix-of-fetch-style
		     return-resource-of-fetch-style
		     return-cache-filename-of-fetch-style
		     ignore-cache-of-fetch-style
		     note-progress-while-fetching)))
  name-of-fetch-style
  verb-of-fetch-style-info
  maximum-size-for-resource   ;; zero implies no limit.
  return-server-prefix-of-fetch-style
  return-resource-of-fetch-style
  return-cache-filename-of-fetch-style
  ignore-cache-of-fetch-style
  note-progress-while-fetching
  (description-of-message-headers (copy-gensym-string "")
				  :reclaimer reclaim-gensym-string)
  )

(defun install-fetch-style (name fetch-style-info)
  (let ((old-definition? (fetch-style-info name)))
    (when old-definition?
      (reclaim-fetch-style-info old-definition?))
    (setf (fetch-style-info name) fetch-style-info)))

(defun initialize-fetch-styles-of-context ()
  ;; ought to use -- gsi-current-context-number
  (install-fetch-style
    'default
    (make-fetch-style-info
      'default ; name
      'get
      0     ; max size of resource, 0 is inf.
      nil   ; return-server-prefix
      t     ; return-resource
      nil   ; return-cache-filename
      t     ; ignore cache
      t     ; note-progress-while-fetching
      )))


(defun shutdown-fetch-styles-of-context ()
  ;; ought to use -- gsi-current-context-number
  )


;;;; Fetching Resources


(def-structure (fetch-thread
		 (:include rpc-thread)
		 (:constructor make-fetch-thread ()))
  fetch-id-of-fetch-thread
  fetch-style-info-of-fetch-thread
  url-of-fetch-thread
  resource-buffer-of-fetch-thread)

(def-slow-method thread-feed-trace (fetch-thread)
  (format t "~&Feeding ~S ~S ~S"
	  fetch-thread
	  (fetch-id-of-fetch-thread fetch-thread)
	  (url-of-fetch-thread fetch-thread)))

;;; `Try-web' presumes that you have loaded the `tiny' system.
;;; It fires up tiny, and has it run try-web-1 as the main routine
;;; of the thread.


#+nil
(defmacro with-bracket ((pre-form post-form) &body body)
  `(progn
     ,pre-form
     (prog1 (progn ,@body)
       ,post-form)))

(defun-for-thread do-web-query
    (proxy-server proxy-port url document? data-handler status-callback)
  (with-thread ((:locals (socket nil) (byte-count 0)))
    (:initialize
      (funcall status-callback 'awaiting-connection -1 -1)
      (setf socket (make-client-socket))
      (socket-connect socket proxy-server proxy-port)
      (when (issue-with-socket? socket)
	(bridge-log "Unable to connect to HTTP proxy server.")
	(signal-from-rpc
	  'unable-to-connect-to-http-proxy
	  "Unable to connect to HTTP proxy server."))
      (with-backtrace ("Writing Query")
	(funcall status-callback 'requesting-resource -1 -1)
	(socket-write-http-request
	  socket
	  url
	  (fetch-style-info-of-fetch-thread current-thread)
	  document?))
      (funcall status-callback 'awaiting-resource -1 -1)
      (yield :check-for-data))

    (:cleanup
      (when socket
	(socket-close-it socket)
	(reclaim-client-socket socket)))
    
    (:check-for-data
      (cond
	((socket-data-available-p socket)
	 (let ((data-or-eof (socket-read-string socket)))
	   (cond
	     ((eq data-or-eof :eof)
	      (funcall status-callback 'resource-fetched byte-count -1)
	      (let ((max 
		      (maximum-size-for-resource
			(fetch-style-info-of-fetch-thread current-thread))))
		(when (and (<f 0 max) (<f max byte-count))
		  (signal-from-rpc
		    'RESOURCE-TOO-LARGE
		    "Resource was larger than maximum set in fetch-style")))
	      (funcall data-handler :end-data nil)
	      (yield :return))
	     (t
	      (incf byte-count (length data-or-eof))
	      (funcall status-callback 'fetching-resource byte-count -1)
	      (funcall data-handler :add-data data-or-eof)
	      (yield :check-for-data)))))
	(t
	 (io-wait :check-for-data))))))

(defun socket-write-http-request (socket url fetch-style-info document?)
  (let ((document-as-internet-text?
	  (when document?
	    (twith-output-to-gensym-string
	      (twrite-coerced-string
		document? gensym-procedure-text internet-ascii)))))
    #+nil
    (progn
      (socket-write-string
	socket (case (verb-of-fetch-style-info fetch-style-info)
		 (get "GET ")
		 (post "POST ")
		 (put "PUT ")
		 #+development
		 (otherwise
		  (error "Unknown HTTP request verb."))))
      (socket-write-string socket url)
      (socket-write-line socket " HTTP/1.0"))
    (let* ((verb (case (verb-of-fetch-style-info fetch-style-info)
		   (get "GET ")
		   (post "POST ")
		   (put "PUT ")
		   #+development
		   (otherwise
		    (error "Unknown HTTP request verb."))))
	   (str (obtain-simple-gensym-string
		  (+f (length verb)
		      (length url)
		      #.(length " HTTP/1.0"))))
	   (dst 0))
      (loop for src from 0 below (length verb)
	    do
	(setf (char str dst) (char verb src))
	(incff dst))
      (loop for src from 0 below (length url)
	    do
	(setf (char str dst) (char url src))
	(incff dst))
      (loop for src from 0 below #.(length " HTTP/1.0")
	    do
	(setf (char str dst) (char " HTTP/1.0" src))
	(incff dst))
      (socket-write-line socket str)
      (reclaim-gensym-string str))
    (socket-write-line socket "User-Agent: gensym-web-gsi/0.1")
    #+development
    (socket-write-line socket "X-Developer-EMail: bhyde@gensym.com")
    (socket-write-line socket "Accept: text/plain, image/gif")
    (when document-as-internet-text?
      (let ((header (tformat-gensym-string
		      "Content-Length: ~D" (length document-as-internet-text?))))
	(socket-write-line socket header)
	(reclaim-gensym-string header)))
    (let ((user-message-headers
	    (description-of-message-headers fetch-style-info)))
      (unless (=f 0 (length user-message-headers))
	(socket-write-string
	  socket
	  (description-of-message-headers fetch-style-info))))
    (socket-write-line socket "")
    (socket-write-line socket "")
    (when document-as-internet-text?
      (socket-write-string socket document-as-internet-text?)
      (reclaim-gensym-string document-as-internet-text?))))





;;;; Bridge Global Configuration



(def-structure (bridge-configuration-info
		 (:constructor 
		   make-bridge-configuration-info-1
		   ()))
  (bridge-has-proxy-info? nil)
  (bridge-as-server-enabled? nil)
  (hostname-of-proxy-server nil)
  (port-number-of-proxy-server nil)
  (cache-directory-name nil)
  (maximum-count-of-simultaneous-transactions 10)
  (message-pool-size 30))

(defun make-bridge-configuration-info ()
  (make-bridge-configuration-info-1))

(def-system-variable the-bridge-configuration-info web
  (:funcall make-bridge-configuration-info))

;;; `The-state-of-g2' maintains a keyword denoting the
;;; state we think G2 is in.  It takes on one of these
;;; values:
;;;    :unconnected -- G2? what G2.
;;;    :paused      -- G2 told us he was pausing.
;;;    :running     -- as far as we know we are connected and
;;;                    he is running.

(defvar the-state-of-g2 :unconnected)


;;;; Header Parsing.

(defun scan-header-line (mark-of-resource-buffer) ;; See RFC 822 Section 3.1
  (with-scanner ()
    ;; In parsing context.
    (cond
      ((scan-blank-line)
       (return-scan-bad))
      (t
       (let (field-name)
	 (scan-upto-character #\:)
	 (setf field-name (get-simple-text-from-last-scan))
	 (advance)
	 (with-mark (start-field-value current-right-of-parsing)
	   (loop for i from 0
		 doing
	     (unless (scan-to-beginning-of-next-line) ;; note 1.
	       (return-scan-bad))
	     (let ((c (peek)))
	       (unless (or (eq #\space c)
			   (eq #\tab c))
		 (normalize-server-header-and-save
		   mark-of-resource-buffer
		   field-name
		   (copy-text-between-marks
		     start-field-value
		     current-right-of-parsing))
		 (return-scan-ok t))
	       (when (< 1000 i) (return-scan-bad)) ;; note 1
	       ))))))))

;; Note 1: May return nil if too many lines in header, or
;; the header isn't terminated correctly.  In either case
;; the caller will go get more data or not.  Try a few more
;; times, and then give up and declare the query malformed.

(defun normalize-server-header-and-save
    (mark-of-resource-buffer field-name folded-field-value)
  (declare (ignore mark-of-resource-buffer))

  ;; Unfold the folded-field-value
  (let ((unfolded-field-value
	 (loop with dst-i = 0
	       with squeeze-white = t
	       with start? = t
	       for src-i from 0 below (length folded-field-value)
	       as char = (char folded-field-value src-i)
	       as white? = (or (eq #\space char)
			       (eq #\linefeed char)
			       (eq #\return char)
			       (eq #\tab char))
	       doing
	       (cond
		 ((and squeeze-white white?)
		  ;; Skip white.
		  )
		 ((or (eq #\linefeed char)
		      (eq #\return char))
		  (setf squeeze-white t))
		 (t
		  (when (and squeeze-white (not start?))
		    (setf (char folded-field-value dst-i) #\space)
		    (incff dst-i))
		  (setf squeeze-white nil)
		  (setf start? nil)
		  (setf (char folded-field-value dst-i) char)
		  (incff dst-i)))
	       finally
	       (return
		 (loop with result = (obtain-simple-gensym-string dst-i)
		       finally (return result)
		       for i from 0 below dst-i
		       doing (setf (char result i)
				   (char folded-field-value i)))))))
    (reclaim-gensym-string folded-field-value)
    ;; Poke that into the buffer's cleaned up headers
    (set-property-of-buffer
	mark-of-resource-buffer 'mimi-headers-from-server
	(gensym-cons
	  (gensym-cons field-name unfolded-field-value)
	  (get-property-of-buffer
	    mark-of-resource-buffer 'mimi-headers-from-server)))

    ))


;;;; Proxy Fetch Thread

;;; A `proxy-fetch-thread' takes a URL, a buffer input mark, and
;;; a thread.  It fetchs the URL feeding it to the input mark, it
;;; then resumes the thread, if necessary.

(def-structure (proxy-fetch-thread
		 (:include thread)
		 (:constructor make-proxy-fetch-thread ()))
  input-mark-of-proxy-fetch-thread
  next-thread-of-proxy-fetch-thread
  url-of-proxy-fetch-thread)

(defun-for-thread main-for-proxy-fetch-thread (input-mark next-thread url)
  (with-thread ()

    (:initialize
      ;; Move these into the thread state.
      (setf (input-mark-of-proxy-fetch-thread current-thread) input-mark)
      (setf (next-thread-of-proxy-fetch-thread current-thread) next-thread)
      (setf (url-of-proxy-fetch-thread current-thread) url)
      (yield :do-fetch))

    (:do-fetch
	(call do-web-query :wrapup
	      (hostname-of-proxy-server the-bridge-configuration-info)
	      (port-number-of-proxy-server the-bridge-configuration-info)
	      url
	      nil
	      #'handle-incomming-data-for-proxy-fetch-thread
	      #'notify-no-op
	      ))

    (:wrapup
      (yield :return))

    (:cleanup
      )))

(defun handle-incomming-data-for-proxy-fetch-thread (status string?)
  (cond
    ((eq :add-data status)
     (insert-text-at-mark
       (input-mark-of-proxy-fetch-thread current-thread)
       string?)
     (thread-enqueue-event
       (next-thread-of-proxy-fetch-thread current-thread)
       :add-data))
    ((eq :end-data status)
     (thread-enqueue-event
       (next-thread-of-proxy-fetch-thread current-thread)
       :end-data))))

(defun notify-no-op (status metric max)
  (declare (ignore status metric max)))


;;;; Testing

#+development
(defun do-test ()
  (declare allowing-unwind)
  (block nil
    (let ((socket (make-client-socket)))
      ;; Connect to proxy.
      (socket-connect socket "httphost" 8080)
      (when (issue-with-socket? socket)
	(return "No proxy connection."))
      (unwind-protect
	   (progn

	     ;; Send the message.
	     (flet ((f (text)
		      (socket-write-line socket text)))
	       (let* ((doc
			"Start_year=1996&End_year=1996&Make=CHRYSLER&Model=CHRYSLER&Fault_type=&Compno=")
		      (len (length doc)))
		 
	       (f "POST http://www-nsa.nhtsa.dot.gov/cgi-bin/nsearch HTTP/1.0")
	       (f "User-Agent: gensym-web-gsi/0.1")
	       #+development
	       (f "X-Developer-EMail: bhyde@gensym.com")
	       (f "Content-Type: application/x-www-form-urlencoded")
	       (f (format nil "Content-Length: ~D" (+ 2 len)))
	       (f "Accept: text/plain, image/gif")
	       (f "")
	       (f doc)))
	       
	     ;; Read the return
	     (loop
	       with byte-count = 0
	       doing
	       (cond
		 ((socket-data-available-p socket)
		  (let ((data-or-eof (socket-read-string socket)))
		    (cond
		      ((eq data-or-eof :eof)
		       (let ((max 300))
			 (when (and (<f 0 max) (<f max byte-count))
			   (return "Too big.")))
		       (return nil))
		      (t
		       (incf byte-count (length data-or-eof))
		       (format t "~A" data-or-eof)))))
		 (t
		  (sleep 1)))))
	(socket-close-it socket)))))


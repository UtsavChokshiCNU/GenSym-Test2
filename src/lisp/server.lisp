(in-package "AB")

;;;; Module SERVER

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde





;;;; Misc Constants



(defparameter no-such-built-in-argument ':no-such-built-in-argument)



;;;; Buffer Properties of HTTP Request Buffers.

;;; `fetch-id' is a an integer buffer property.  It is actually
;;; a back pointer to the thread, since it's the thread's number.

(def-buffer-property fetch-id)


;;; `Search-part' a string buffer proptery is defined in RFC 1738, as
;;; searchpart, a grammar term.  It is also refered to there as query
;;; string.  It is put in to the buffer by
;;; handle-url-via-call-back-to-g2-function when the server believes it is
;;; handling a CGI call.

(def-buffer-property search-part)
(def-concept query-string)

;;; `cgi-routine-name' is a string buffer property found on incomming
;;; requests that the server believes are cgi format.  The name is
;;; taken from the signature of the cgi routine  the server intends
;;; to invoke.

(def-buffer-property cgi-routine-name)
(def-concept script-name)

;;; `cgi-arguments' is an alist of actual arguments parsed out of
;;; a CGI call.  These are (<symbol> . <text>).

(def-buffer-property cgi-arguments)

;;; `http-client-host-name' is a string buffer property, equivalent
;;; to the CGI environment variable request-hostname of RFC 1739.

(def-buffer-property http-client-host-name)
(def-concept request-hostname)

;;; `http-client-host-address' is a string buffer property, equivalent
;;; to the CGI environment variable request-addr of RFC 1739.

(def-buffer-property http-client-host-address)
(def-concept request-addr)

;;; `Form-for-resource-generation' is the form used to guid the generation
;;; of the response.

(def-buffer-property form-for-resource-generation)

;;; `mimI-headers-from-server' is a buffer property - an alist of the
;;; headers parsed out of the MIME header of the request.

(def-buffer-property mimi-headers-from-server)

(def-buffer-property protocol-of-request)

(def-buffer-property verb-of-request)

(def-buffer-property url-details-of-request)



;;; `Left-edge-of-mime-headers' and `right-edge-of-mime-headers' are
;;; marks into the buffer bracketing the mime headers provided by
;;; the client with the request.

(def-buffer-property right-edge-of-mime-headers)
(def-buffer-property left-edge-of-mime-headers)




;;;; Handlers for FORM-URLENCODED

;;; The following is taken from draft-ietf-html-spec-04.txt (June 16, 1995).

;;; The default encoding for all forms is
;;; `application/x-www-form-urlencoded'. A form data set is
;;; represented in this media type as follows:

;;;     1. The form field names and values are escaped: space
;;;     characters are replaced by `+', and then reserved characters
;;;     are escaped as per [URL]; that is, non-alphanumeric
;;;     characters are replaced by `%HH', a percent sign and two
;;;     hexadecimal digits representing the ASCII code of the
;;;     character. Line breaks, as in multi-line text field values,
;;;     are represented as CR LF pairs, i.e. `%0D%0A'.


;;; `Coerce-www-form-urlencoded-to-ascii-text' takes and consumes
;;; a text string encoded in form-urlencoding.  It returns a fresh
;;; text string consisting of the text in ascii (not G2 text).

(defun coerce-www-form-urlencoded-to-ascii-text (string)
  (twith-output-to-gensym-string
    (loop
      with length = (length string)
      with i = 0
      doing
      (macrolet ((put-char (x) `(twrite-char ,x))
		 (get-char ()
		   `(if (<= length i)
			(return nil)
			(prog1 (char string i) (incff i))))
		 (scan-two-digit-hex ()
		   `(+f (*f 16 (digit-char-p (get-char) 16))
			(digit-char-p (get-char) 16))))
	(let ((c (get-char)))
	  (put-char
	    (cond
	      ((eql c #\+) #\space)
	      ((eq c #\%) (code-char (scan-two-digit-hex))) ;; Note A
	      (t c))))))
    (reclaim-gensym-string string)))

;; Note A: The use of code-char is based on the presumption that
;; the hex value indexes into the ASCII code.  There is an appendex
;; in the draft standard which implies ISO Latin characters can
;; also make it into these, and there is of course some adhoc extensions
;; of the asian languages, none of these am I handling at this point.


;;; `base64-encoding-vector'

(defconstant base64-encoding-vector
	     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/")

;;; `Convert-text-to-base64-encoding' is used to encode the
;;; cookies send over the wire.  In the basic http stan

(defun convert-text-to-base64-encoding (text)
  (twith-output-to-gensym-string
    (macrolet ((g (i) `(char-code (char text ,i)))
	       (p-1 (c) `(twrite-char ,c))
	       (p (b)
		 `(p-1 (char base64-encoding-vector
			     (ldb (byte 6 ,b) w))))
	       (pad () `(p-1 #\=)))

      (loop
	with length = (length text)
	for i below (-f length 2) by 3
	as c1 = (g i)
	as c2 = (g (+f i 1))
	as c3 = (g (+f i 2))
	as w = (+f (ashf c1 16) (ashf c2 8) c3)
	do (p 18) (p 12) (p 6) (p 0) 
	finally
	  (case (-f length i)
	    (0)
	    (1
	     (setf w (ashf (g i) 16))
	     (p 18) (p 12) (pad) (pad))
	    (2
	     (setf w (+f (ashf (g i) 16)
			 (ashf (g (+f i 1))  8)))
	     (p 18) (p 12) (p 6) (pad)))))))






;;;; Tendered Resources

;;; A list of triples (<integer> <string> <string>) sorted
;;; in accending order.  An alist without duplicates.
;;; The strings are the left and right of a pattern match
;;; made against the URL

;;; The left hand side is a pattern that matchs the prefix of the URL's path.
;;; Recall from RFC1738 that:
;;;   An HTTP URL takes the form:
;;;        http://<host>:<port>/<path>?<searchpart>
;;; The left hand side of these patterns matchs only the
;;; a prefix of the <path> portion of the URL using string=.
;;; For example if the URL "http://www.server.org/a/b/c?who=ben&what=lunch"
;;; is recieved it can match "a" or "a/b/c" or "a/", but not
;;; "org/a" or "http://www.server.org/a"

;;; The right handside is a statement specifying how to generate
;;; this URL.  These are enumerated in the user's manual.

(defvar alist-of-resources-tendered-by-g2 ()) ;; thread variable?

(defun install-tender-of-resource (index pattern method)
  (block :exit
    (let ((pattern (copy-gensym-string pattern)) ;; Copy so we can store it.
	  (compiled-method
	    (let ((compiled-method?
		    (compile-resource-method method)))
	      (if compiled-method?
		  compiled-method?
		  (return-from :exit -1)))))
      (cond
	((or (null alist-of-resources-tendered-by-g2)
	     (<f index (caar alist-of-resources-tendered-by-g2)))
	 (setf alist-of-resources-tendered-by-g2
	       (gensym-cons
		 (gensym-list index pattern compiled-method)
		 alist-of-resources-tendered-by-g2)))
	(alist-of-resources-tendered-by-g2
	 (loop for tail on alist-of-resources-tendered-by-g2
	       as (entry . rest) = tail
	       as (i) = entry
	       as ((i2)) = rest
	       when (=f index i)
		 do (reclaim-gensym-string (second entry))
		    (reclaim-plist-tree-of-resource-buffer (third entry))
		    (setf (second entry) pattern)
		    (setf (third entry) compiled-method)
		    (return nil)
	       when (or (null rest)
			(<f index i2))
		 do
		   (let ((new-entry
			   (gensym-cons
			     (gensym-list index pattern compiled-method)
			     rest)))
		     (setf (cdr tail) new-entry))
		   (return nil))))
      0)))

(defun compile-resource-method (method)
  (let ((m (make-mark-into-new-empty-resource-buffer))
	(result nil)
	(style nil))
    (insert-text-at-mark m method)
    (mark-tab m 0)
    (block :done
      (with-buffer-parsing (m)

	;; call foo(a:integer, b:text)
	(let (routine-name
	       signature)
	  (when (and (scan-text "call")
		     (scan-one-or-more-spaces-and-tabs)
		     (setf style
			   (cond
			     ((scan-text "cgi") :cgi)
			     ((scan-text "url") :url)
			     (t nil)))
		     (scan-one-or-more-spaces-and-tabs)
		     (setf routine-name (scan-symbol))
		     (scan-zero-or-more-spaces-and-tabs)
		     (scan-text "(")
		     (setf signature (scan-method-args routine-name))
		     (scan-text ")"))
	    (setf result
		  (gensym-list
		    'handle-url-via-call-back-to-g2-function
		    (gensym-list 'quote signature)))
	    (lgsi-rpc-declare-remote routine-name
				     (-f (length signature) 1)
				     0)
	    (return-from :done nil)))

	;; serve from file system: <pathname>
	(when (scan-text "serve from file system:")
	  (scan-zero-or-more-spaces-and-tabs)
	  (scan-over-filename)
	  (let ((filename-root (get-simple-text-from-last-scan)))
	    (setf result
		  (gensym-list
		    'handle-url-via-file-system
		    (twith-output-to-gensym-string
		      (twrite-coerced-string
			filename-root gensym-procedure-text internet-ascii))))
	    ;;;Bogus reclaim
	    (reclaim-gensym-string filename-root))
	  (return-from :done nil))

	(when (scan-text "serve internal status pages")
	  (setf result
		(gensym-list 'handle-url-via-internal-pages))
	  (return-from :done nil))

	;; forward to proxy server
	(when (scan-text "forward to proxy server")
	  (setf result (gensym-list 'handle-url-via-proxy-server)))


	))
    (reclaim-resource-buffer-of-mark m)
    result))

(defun scan-method-args (routine-name)
  (loop
    with result = (gensym-list routine-name)
    as arg-name = nil
    as arg-type = nil
    do
    (scan-zero-or-more-spaces-and-tabs)
    (setf arg-name (scan-symbol))
    (scan-zero-or-more-spaces-and-tabs)
    (scan-text ":")
    (scan-zero-or-more-spaces-and-tabs)
    (setf arg-type (scan-symbol))
    (scan-zero-or-more-spaces-and-tabs)
    (unless (and arg-name
		 (memq arg-type
		       '(integer symbol text)))
      (reclaim-gensym-tree result)
      (return nil))
    (gensym-push (gensym-list arg-name
			      arg-type)
		 result)
    (unless (scan-text ",")
      (return (nreverse result)))))

(defun match-url-against-tendered-resources (url-details)
  (loop for (index pattern method) in alist-of-resources-tendered-by-g2
	      when (string-prefix= pattern url-details)
		do (return method)))

(defun string-prefix= (prefix string)
  (and
    (<=f (length prefix) (length string))
    (loop for i from 0 below (length prefix)
	  always (char= (char prefix i)
		       (char string i)))))


;;;; The HTTP Server 

(def-structure (listener-socket
		 (:include weblink-socket)
		 (:constructor make-listener-socket (port-number-of-listener)))
  port-number-of-listener)

(def-generic-slow-method socket-listen (listener-socket))


;;; `Socket-listen' is called once when a listener-socket is created
;;; to start it listening upon its port. 

(def-slow-method socket-listen (listener-socket)
  (let ((result (g2ext-tcpip-listen (port-number-of-listener listener-socket))))
    (cond
      ((<=f result 0)
       (note-issue-with-socket listener-socket result))
      (t ;; OK
       (socket-install listener-socket result))))
  listener-socket)



;;; `Socket-accept?' takes a listener-socket and returns NIL, or a fresh
;;; client-socket one is queued on the socket.

(defun socket-accept? (listener-socket)
  (let ((result
	  (g2ext-tcpip-accept-internals (number-of-socket listener-socket))))
    (cond
      ((<f 0 result)
       (let ((client-socket (make-client-socket)))
	 (socket-install client-socket result)
	 client-socket))
      (t
       nil))))

;; Is there an error case of interest here?


(def-structure (server-thread
		 (:include thread)
		 (:constructor make-server-thread ()))
  port-number-of-server
  icp-socket-of-server)

(def-slow-method thread-feed-trace (server-thread)
  (format t "~&Feeding the server at ~S (~S clients)"
	  server-thread
	  (port-number-of-server server-thread)
	  (length (children-of-thread server-thread))))

;;; `the-http-server-thread?' provides both a handle to
;;; the server, and a predicate that it is running.  We
;;; currently only allow one to be running, if a second
;;; is started we will kill the first.

(defvar the-http-server-thread? nil)

(defun startup-http-server (port-number)
  (bridge-log "Launching new HTTP server at ~D." port-number)
  (when the-http-server-thread?
    (bridge-log "but first shutting down old HTTP server.")
    (thread-kill the-http-server-thread?))
  (let ((new-thread-instance (make-server-thread)))
    (setf (name-of-thread new-thread-instance) 'http-server)
    (setf (port-number-of-server new-thread-instance) port-number)
    (setf (icp-socket-of-server new-thread-instance)
	  current-icp-socket)
    (setf the-http-server-thread? new-thread-instance)
    (do-start-thread (new-thread-instance)
      (listen-for-server-requests))))

(defun-for-thread listen-for-server-requests ()
  (with-thread ((:locals (listener-socket nil)))

    (:initialize
      (bridge-log "Started HTTP server (port ~D)."
		  (port-number-of-server current-thread))
      (setf alist-of-resources-tendered-by-g2 nil)
      (setf listener-socket
	    (socket-listen
	      (make-listener-socket
		(port-number-of-server current-thread))))
      (if (issue-with-socket? listener-socket)
	(thread-exit)
	(io-wait :check-for-clients)))
    
    (:cleanup
      (bridge-log "Shutdown HTTP Server (port ~D)."
		  (port-number-of-server current-thread))
      (setf alist-of-resources-tendered-by-g2 nil)
      (when listener-socket
	(socket-close-it listener-socket)
	(reclaim-listener-socket listener-socket))
      (setf the-http-server-thread? nil))
    
    (:check-for-clients
      (cond
	((issue-with-socket? listener-socket)
	 (yield :shutdown-server))
	;; Don't bother if G2 isn't running.
	((eq :running the-state-of-g2)
	 (loop for client-socket = (socket-accept? listener-socket)
	       while client-socket
	       do (launch-http-client client-socket))
	 (io-wait :check-for-clients))
	(t
	 (io-wait :check-for-clients))))

    (:shutdown-server
      (when (issue-with-socket? listener-socket)
	(bridge-log
	  "Problem with HTTP Server (issue: ~S)"
	  (issue-with-socket? listener-socket)))
      (thread-exit))))





;;;; HTTP Header Text Charsets



;;; The name for a character set/encoding in an HTTP header is called an
;;; `http-header charset'.  It is represented as a gensym-string. A `charset
;;; name' is the name in G2, GSI, and Weblink.

;;; An `http-header content-type' is a string of the form
;;;
;;;   "<content-type>;charset=<http-header charset>"
;;;
;;; where content-type is something like "text/html" and is in the form
;;; appropriate to be emitted to specify an HTML document's character set.

;;; This will be glued together in other code, since content type and char set
;;; maybe set separately from G2

;;; The a-list charset-name-to-http-header-charset maps charset names to
;;; charsets, and is of the form
;;;
;;;    ( { (charset-name  http-header-charset transcoding-purpose) } )
;;;
;;; Charset-name is one of a subset of official G2 charset names.  The supported
;;; charset names are:
;;;
;;;   unicode-utf-8 us-ascii latin-1 latin-2 latin-3 latin-4 latin-cyrillic
;;;   latin-arabic latin-greek latin-hebrew latin-5 latin-6 jis-euc shift-jis
;;;   ksc-euc.
;;;
;;; Http-header-charset is the corresponding IANA charset name, valid for MIME
;;; headers used for HTTP.
;;;
;;; Transcoding-purpose MUST be a valid transcoding purpose with these
;;; requirements:
;;;
;;;    (a) transcode to/from the corresponding character set;
;;;    (b) import/export to/from a Gensym string (Lisp string type); and
;;;    (c) use CRLF as the line ending convention

(defvar charset-name-to-http-header-charset
  '((unicode-utf-8 "utf-8" utf-8-gensym-string-with-crlf)
    (us-ascii "us-ascii" us-ascii-gensym-string-with-crlf)
    (latin-1 "iso-8859-1" iso-8859-1-gensym-string-with-crlf)
    (latin-2 "iso-8859-2" iso-8859-2-gensym-string-with-crlf)
    (latin-3 "iso-8859-3" iso-8859-3-gensym-string-with-crlf)
    (latin-4 "iso-8859-4" iso-8859-4-gensym-string-with-crlf)
    (latin-cyrillic "iso-8859-5" iso-8859-5-gensym-string-with-crlf)
    (latin-arabic "iso-8859-6" iso-8859-6-gensym-string-with-crlf)
    (latin-greek "iso-8859-7" iso-8859-7-gensym-string-with-crlf)
    (latin-hebrew "iso-8859-8" iso-8859-8-gensym-string-with-crlf)
    (latin-5 "iso-8859-9" iso-8859-9-gensym-string-with-crlf)
    (latin-6 "iso-8859-10" iso-8859-10-gensym-string-with-crlf)
    (jis-euc "x-euc-jp" jis-euc-gensym-string-with-crlf)
    (shift-jis "x-sjis" shift-jis-gensym-string-with-crlf)
    (ksc-euc "euc-kr" ks-euc-gensym-string-with-crlf)
    ;; The Simplified-Chinese EUC character encoding is disabled.  This did not
    ;; function properly with any of the tested browsers (IE, Mozilla, Opera).
    ;; Note that applications can almost certainly get by with
    ;; Unicode-UTF-8. Still, this should be investigated! (MHD 6/11/04)
    #+nil
    (gb-2312-euc "euc-cn" gb-2312-euc-gensym-string-with-crlf)
    ;; The 7-bit ISO-2022-based encodings for CJK are disabled. Support for them
    ;; seems to be less common than for the EUC variants (e.g., little or no
    ;; support in current versions of Internet Explorer or or Opera), and they
    ;; do not appear to work right in tested browser (Mozilla) that claim
    ;; support. I've not had time to investigate what the problem might be, and
    ;; it's probably not worth doing unless these are strongly needed by a
    ;; customer, which I think probably may never happen. (MHD 6/11/04)
    #+nil
    (jis "iso-2022-jp" jis-gensym-string-with-crlf)
    #+nil
    (ksc "ksc_5601" ks-gensym-string-with-crlf)
    #+nil
    (gb-2312 "GB2312" gb-2312-gensym-string-with-crlf)))


;;Notes: yduJ (9/19/05) removed "text/html;charset=xxx" from all these to
;;support new user-settable content-types. "text/html", the default, is now
;;appended in emit-headers-of-response if needed.



(defmacro map-charset-name-to-something (charset-name by)
  `(cond ((symbolp ,charset-name)
	 (,by (assq ,charset-name charset-name-to-http-header-charset)))
	(t (loop for l in charset-name-to-http-header-charset
		 until (string-equal (second l) ,charset-name)
		 finally (return (,by l))))))

;;;This is silly if someone passes in the string -- it'll be the SAME STRING.
;;;But useful for parallelism.  String charset names are possible when user sets
;;;content-type, if they also have ";charset=" in that specification.
(defun map-charset-name-to-charset-string (charset-name)
  (map-charset-name-to-something charset-name second))

(defun map-charset-name-to-transcoding-purpose (charset-name)
  (map-charset-name-to-something charset-name third))


;;; `Map-and-validate-charset-name' looks up charset-name. If it's a bad charset
;;; name, it will signal back to G2 through RPC that the charset name is bad.
;;; Otherwise, it returns the http-header-charset corresponding to charset-name.

(defun map-and-validate-charset-name (charset-name)
  (or (map-charset-name-to-charset-string charset-name)
      (signal-from-rpc 'invalid-charset-name "Unrecognized charset name.")))


;;; The `default-charset' command line option for GW can be either DEFAULT or
;;; one of the charset names that are key entries in the alist
;;; charset-name-to-http-header-charset.  The constant
;;; `default-default-http-header-charset-name' is set to UNICODE-UTF-8, and
;;; gives the default for the default charset, which is used if either DEFAULT
;;; is specified, the command line option is not given, of if an unrecognized
;;; arg is supplied.  If the option is given, correct or not, this gives a
;;; notification on the console showing the default charset chosen.

;;; The system variable `default-http-header-charset-name' is initially bound to
;;; the default default (UNICODE-UTF-8), and gives the default charset name for
;;; this gw process.  It may be set once to an override value by the
;;; command-line argument processor for default-charset.  After command line
;;; argument processing retains its value throughout the lifetime of a GW
;;; process.  Applications can override the default charset for a given client
;;; thread using the zgw-set-url-reply-charset RPC, q.v.

(defconstant default-default-http-header-charset-name 'unicode-utf-8)

(def-system-variable default-http-header-charset-name server unicode-utf-8)

(def-command-line-argument (default-charset (:systems gsi)) ; not GW; see note!
    ((value? :keyword))
  (cond
    (value?
     (let ((name-maybe
	     (cond
	       ((symbolp value?)
		value?)
	       ((gensym-string-p value?)
		(intern-gensym-string (string-upcase value?)))
	       ((wide-string-p value?)
		(intern-text-string (string-upcasew value?))))))
       (cond
	 ((eq name-maybe 'default)
	  (setq name-maybe default-default-http-header-charset-name))
	 ((null (map-charset-name-to-charset-string name-maybe))
	  (let ((names
		  (loop for (name) in charset-name-to-http-header-charset
			collect name using gensym-cons)))
	    (notify-user-at-console
	      "Note: ~A is not valid for the -default-charset option. ~
               ~%Legal charset names are: ~(~L,-~)."
	      name-maybe names)
	    (reclaim-gensym-list names)
	    (setq name-maybe default-default-http-header-charset-name))))
       (setq default-http-header-charset-name name-maybe)
       (notify-user-at-console
	 "Default charset for Gensym Weblink: ~a"
	 default-http-header-charset-name)
       name-maybe))))

;; note: can't use GW as the system, since Weblink thinks it's GSI when it's
;; running.  TO DO: add this to -help text in the ext/c/cprim.c file when it can
;; be GW-only!  (MHD 6/11/04)





;;;; HTTP Server Clients


(def-structure (http-client-thread
		 (:include thread)
		 (:constructor make-http-client-thread-1 ()))
  socket-of-http-client
  input-mark-of-http-client
  output-mark-of-http-client
  (status-of-http-client-response :pending)
  (reply-headers-have-been-sent nil)
  (http-headers nil)
  (http-header-charset-name default-http-header-charset-name))

(defun make-http-client-thread ()
  (let ((thread (make-http-client-thread-1)))
    (add-message-header-field thread "MIME-version" "1.0")
    thread))

(def-slow-method thread-feed-trace (http-client-thread)
  (format t "~&Feeding the http client ~S" http-client-thread))

(defun-for-thread serve-http-client ()
  (with-thread ((:locals
		  (input-mark (make-mark-into-new-empty-resource-buffer))
		  (output-mark (let ((output-mark-1 (mark-copy input-mark)))
				 (mark-direction output-mark-1 :backward)))
		  reply-insert-mark
		  reply-send-mark
		  (parse-state :start)
		  url?))
    (:initialize
      #+nil
      (compare-memory-allocation-with-label 'initialize--serve-http-client
					    current-thread)
      (setf (input-mark-of-http-client current-thread) input-mark)
      (setf (output-mark-of-http-client current-thread) output-mark)
      (yield :collect-first-line-of-query))

    (:cleanup
      (reclaim-resource-buffer-of-mark input-mark)
      (socket-close-it (socket-of-http-client current-thread))
      (reclaim-client-socket (socket-of-http-client current-thread))
      (reclaim-gensym-tree-with-text-strings (http-headers current-thread))
      (setf (http-headers current-thread) nil)
      (when url?
	(reclaim-gensym-string url?)))

    (:collect-first-line-of-query
      (let* ((status (read-query-from-current-socket input-mark))
	     (first-line-status (if (not (=f 0 status))
				    (status-of-first-line-of-query output-mark))))
	(cond
	  ;; Bogus input.
	  ((eq first-line-status :bad)
	   (bridge-log "Ignoring malformed request.")
	   (yield :wrap-up))
	  ;; Lovely input.
	  ((eq first-line-status t)
	   (setf parse-state (advance-http-query-parsing output-mark parse-state))
	   (yield :collect-remainder-of-query))
	  ;; No more input.
	  ((eq status -1)
	   (bridge-log "Incomplete request.")
	   (yield :wrap-up))
	  ;; Wait for more input, consider time out.
	  ((eq first-line-status nil)
	   (yield :collect-first-line-of-query)))))
    
    (:collect-remainder-of-query
      (let ((status (read-query-from-current-socket input-mark)))
	(when (<f 0 status)
	  (setf parse-state (advance-http-query-parsing output-mark parse-state)))
	(cond
	  ((or (eq parse-state :done)
	       (=f -1 status))
	   (yield :execute-query))
	  ((eq parse-state :malformed-request)
	   (bridge-log "Ignoring malformed request.")
	   (yield :wrap-up))
	  (t
	   (yield :collect-remainder-of-query)))))

    (:execute-query
					; (print :execute-query)
      (setf reply-insert-mark (mark-copy input-mark))
      (setf reply-send-mark (mark-copy input-mark))
      (mark-direction reply-send-mark :backward)
      (case (setup-to-do-query reply-insert-mark)

	(:fail
	 (yield :finishing-passing-data))

	(:eval-form ;; Execute this S-Expression
	 (call eval-form-to-obtain-url :finishing-passing-data))

	;; This shouldn't happen, but we shutdown client if it does.
	(t
	 (yield :wrap-up))))

    (:finishing-passing-data
      (let ((client-socket (socket-of-http-client current-thread)))
	(unless (or (issue-with-socket? client-socket)
		    (mark-eq output-mark input-mark))
	  (socket-write-region client-socket output-mark input-mark))
	(socket-poll-status (socket-of-http-client current-thread))
	(cond
	  ((or (issue-with-socket? client-socket)
	       (mark-eq output-mark input-mark))
	   #+development
	   (when (issue-with-socket? client-socket) 
	     (bridge-log "Gave up issue-with-socket? ~S"
			 (issue-with-socket? client-socket)))
	   (yield :wrap-up))
	  (t ; otherwise
	   (yield :finishing-passing-data)))))

    (:wrap-up
      #+nil
      (compare-memory-allocation-with-label 'wrap-up--serve-http-client
					    current-thread)
      (thread-exit))))

(defun read-query-from-current-socket (input-mark)
  (let ((socket (socket-of-http-client current-thread))
	(result 0))
    (when (socket-data-available-p socket)
      (let ((data-or-eof (socket-read-string socket)))
					; (print (list :read data-or-eof))
	(cond
	  ((eq data-or-eof :eof)
	   (setf result -1))
	  (t
	   (insert-text-at-mark input-mark data-or-eof)
	   (setf result (length data-or-eof))
	   (reclaim-gensym-string data-or-eof)))))
      result))




(defvar count-of-number-of-http-clients 0)

(defun launch-http-client (client-socket)
  (incff count-of-number-of-http-clients)
  (let ((thread (make-http-client-thread)))
    (setf (name-of-thread thread) 'http-client)
    (setf (socket-of-http-client thread) client-socket)
    (do-start-thread (thread)
      (serve-http-client))))


;;; `status-of-first-line-of-query' guards the query parser from
;;; bogus input.  Both by assuring that we have enough text to
;;; bother trying to parse the query, and also by eliminating
;;; some malformed queries that once eliminated the query parser
;;; is easier to write.

;;; We return NIL, T, or :bad to denote: wait for more input;
;;; proceed to parsing; or this query is bogus.

;;; We don't proceed to parsing until we have seen at least
;;; on return character.

;;; We consider more than two blanks space regions in the
;;; incomming query to be bogus, i.e.
;;;    Get /foo/bar gum.html HTTP/1.0
;;; which is easy to type most web browsers, and is illegal.

(defun status-of-first-line-of-query (parsing-mark)
  (with-buffer-parsing (parsing-mark)
    (block :validate
      ;; example: Get         /home.html       HTTP/1.1
      ;;          <verb> <w1> <url>      <w2> <version> <end-of-line>
      (unless (and (scan-upto-character #\space)       ; <verb>
		   (scan-one-or-more-spaces-and-tabs)  ; <w1>
		   (scan-upto-character #\space)       ; <url>
		   (scan-one-or-more-spaces-and-tabs)) ; <w2>
	(return-from :validate nil))                   ;   ... wait
      (let ((next-break?
	      ;; This should scan over the <version>, but.
	      (scan-upto-member-of-bag
		'#.(concatenate'string '(#\space #\tab #\return)))))
	(cond
	  ((eq next-break? #\return) ;; Scanned over <version>
	   (return-from :validate t))
	  ((null next-break?)  ;; ... wait.
	   (return-from :validate nil))
	  (t                   ;; Oh no too much whitespace
	   (return-from :validate :bad)))))))



(defun advance-http-query-parsing (parsing-mark parse-state)
  (loop
    for from-state = parse-state then next-state
    for next-state = (advance-http-query-parsing-1 parsing-mark from-state)
    until (or (eq :done next-state)
	      (eq from-state next-state)
	      (eq :malformed-request next-state))
    finally (return next-state)))


(defun advance-http-query-parsing-1 (parsing-mark parse-state)
  (block :giveup
    (macrolet ((giveup () `(return-from :giveup nil))
	       (ok? (form)
		 `(unless ,form (giveup))
		 ; `(if ,form (print ',form) (giveup)) ;; with Tracing
		 )
	       (ok2? (form n)
		 `(unless ,form
		    (cond
		      ;; We will wait if more characters might help.
		      ((<f (characters-available-for-parsing) ,n)
		       (giveup))
		      ;; We will fail, if there isn't
		      (t
		       (setf parse-state :malformed-request)
		       (giveup)))))
	       (sp (k v)
		 `(set-property-of-buffer parsing-mark ,k ,v))
	       (gp (k)
		 `(get-property-of-buffer parsing-mark ,k)))
      (with-buffer-parsing (parsing-mark)

	(case parse-state
	  (:start
	   (sp 'left-edge-of-mime-headers (mark-copy parsing-mark))
	   (sp 'right-edge-of-mime-headers (mark-copy parsing-mark))
	   (let (verb
		  url-details
		  (major-protocol-version 0)
		  (minor-protocol-version 9))
	     (ok? (scan-upto-character #\space))
	     (setf verb (get-simple-text-from-last-scan))
	     (ok? (scan-one-or-more-spaces-and-tabs))
	     (ok2? (scan-text "/") 1)
	     (ok? (scan-upto-character #\space))
	     (setf url-details (get-simple-text-from-last-scan))
	     (ok? (scan-one-or-more-spaces-and-tabs))
	     (ok? (scan-text "HTTP/"))
	     (let ((i? (scan-integer)))
	       (unless i? (giveup))
	       (setf major-protocol-version i?)
	       (ok? (scan-text ".")))
	     (let ((i? (scan-integer)))
	       (unless i? (giveup))
	       (setf minor-protocol-version i?))
	     
	     (sp 'url-details-of-request url-details)
	     (sp 'verb-of-request verb)
	     (sp 'protocol-of-request (+f (*f 1000 major-protocol-version)
					  minor-protocol-version))
	     (ok? (scan-to-beginning-of-next-line))
	     (mark-set parsing-mark current-right-of-parsing)
	     (mark-set (gp 'left-edge-of-mime-headers) parsing-mark)
	     (mark-set (gp 'right-edge-of-mime-headers) parsing-mark)
	     (if (eq major-protocol-version 0)
		 (setf parse-state :done)
		 (setf parse-state :request-header-fields))))

	  (:request-header-fields
	   (setf parse-state
		 (loop 
		   (cond
		     ((not (scan-to-end-of-line))
		      (return :request-header-fields))
		     (t
		      (mark-set (gp 'right-edge-of-mime-headers)
				current-right-of-parsing)
		      (undo-last-scan)
		      (unless (scan-header-line parsing-mark)
			(if (scan-blank-line)
			    (return :done)
			    (return :request-header-fields)
			    ))))))

	   ;; Discard over any info in the query after the header.
	   (mark-tab parsing-mark (point-max parsing-mark)))

	  ))))
  parse-state)


(def-command-line-argument (enable-hostname-lookups (:systems gsi)) (:flag))

;;; `Setup-to-do-query' is responsible for deciding how to dispatch the query to
;;; some handler.  It returns a symbol indicating to its caller,
;;; serve-http-client, what it should do.  Usually this is :eval-form.  In
;;; addition it checks the request for plausiblity, and may generate an error
;;; response.

;;; `:fail' indicates that something was wrong with the query, and that an
;;; error message was stuffed into the resource-buffer, and that should be
;;; sent back to the user.

(defun setup-to-do-query (resource-buffer)
  (macrolet ((sp (k v)
	       `(set-property-of-buffer resource-buffer ,k ,v))
	     (gp (k)
	       `(get-property-of-buffer resource-buffer ,k)))
    (let* ((verb (gp 'verb-of-request))
	   (url-details (gp 'url-details-of-request))
	   (result
	     (block :done
	       (macrolet ((return-fail () `(return-from :done :fail)) ;; Give up, our response is in the buffer.
			  (return-eval-form () `(return-from :done :eval-form)) ;; start a thread to do it.
			  (bailout (&rest args)
			    `(progn
			       (generate-error-response
				 resource-buffer 
				 (tformat-gensym-string ,@args))
			       (return-fail))))
		 
		 ;;  Bail out clauses...
		 ;; ... no handler for this verb.
		 (unless (string= "GET" verb)
		   (bailout "The verb ~A is not supported." verb))

		 (let ((form? (match-url-against-tendered-resources url-details)))
		   (when form?
		     (sp 'form-for-resource-generation
			 (copy-resource-plist-value form?))
		     (return-eval-form)))

		 ;; Call off to G2 goes here.

		 (return-fail)))))

      (let* ((client-addr
	       (peer-address-string-of-socket
		 (socket-of-http-client current-thread)))
	     (client-name
	       (if (getf command-line-arguments 'enable-hostname-lookups)
		   (peer-name-of-socket
		     (socket-of-http-client current-thread))
		   (copy-gensym-string client-addr))))
	(sp 'http-client-host-name client-name)
	(sp 'http-client-host-address client-addr)
	(sp 'fetch-id (number-of-thread current-thread))
	(bridge-log "HTTP: ~A ~A \"~A\"~A"
		    client-name
		    verb
		    url-details
		    (case result
		      (:eval-form ", handling")
		      ((nil) ", malformed?")
		      (t ", Huh?"))))
      result)))

(defun generate-error-response (insert-mark text-string)
  (let ((url-details
	  (get-property-of-buffer insert-mark 'url-details-of-request)))
    (with-html-output (:insert-mark insert-mark :title "Error")
      (with-paragraph ()
	(emit "The server was unable to handle your request for \"")
	(emit url-details)
	(emit "\"."))
      (with-paragraph ()
	(emit text-string))))
  (reclaim-gensym-string text-string))




;;; `socket-send-resource-buffer' sends the text between two
;;; marks in a resource buffer to the socket given.  It moves
;;; the trailing mark up to the leading mark.

#+obsolete
(defun socket-send-resource-buffer (socket from-mark to-mark)
  (let ((text-string (copy-text-between-marks from-mark to-mark)))
    (socket-write-string socket text-string)
    (reclaim-gensym-string text-string)))


;; `Handle-url-via-internal-pages' does just that.

(defun handle-url-via-internal-pages ()
  (let* ((insert-mark
	   (input-mark-of-http-client current-thread))
	 #+obsolete
	 (server "bogus")
	 #+obsolete
	 (details
	   (get-property-of-buffer insert-mark 'url-details-of-request)))
    (declare (special server-pages))
    (cond
      #+obsolete
      ((and
	 (string= server "info.server.gsi-web")
	 (loop for (key func) in server-pages
	       when (string= details key)
		 do
		   (funcall func insert-mark)
		   (return t))))
      (t
       (generate-error-response
	 insert-mark
	 (copy-gensym-string "Unknown request for server data"))))))










;;;; Response generated by evaluating a form.

;;; `Current-fetch-ids' is an alist of (<fetch-id> . <thread>) The threads
;;; maintain the entries.  RPC from G2 utilize the entries.

(def-system-variable current-fetch-ids server nil)

(defmacro thread-of-fetch-id? (fetch-id)
  `(cdr (assq ,fetch-id current-fetch-ids)))




;;; `Validate-fetch-id' looks up the thread, and will signal back
;;; to G2 if the RPC is using a bogus fetch-id.

(defun validate-fetch-id (fetch-id)
  (let ((thread? (thread-of-fetch-id? fetch-id)))
    (unless thread?
      (signal-from-rpc
	'invalid-url-request-number
	"The URL request number does not denote a currently active request."))
    thread?))


;;;Sadly, the chestnut implementation of search conses if you give it a :test
;;;argument of #'string-equal
(defun search-case-insensitively (string1 string2)
  (loop for i below (length string2)
	with firstchar = (schar string1 0)
	with len1 = (length-of-simple-string string1)
	with len2 = (length-of-simple-string string2) do
    (when (char-equal (schar string2 i) firstchar)
      (if (string-equal string1 string2 :start2 i :end2 (minf len2 (+f len1 i)))
	  (return i)))))

(defun add-message-header-field (thread header data)
  (if (string-equal header "Content-type")
      (let ((charset? (search-case-insensitively "charset=" data)))
	(when charset?
	  (setf (http-header-charset-name thread)
	    (subseq data (+ charset? 8))) ;; length of "charset="
	  (setf data (subseq data (1- charset?))))))
  (let ((pos? (position header (http-headers thread)
			:test #'string-equal :key #'car))
	(new-item (gensym-cons (copy-gensym-string header)
			       (copy-gensym-string data))))
    (if pos?
	(let ((old-item (nth pos? (http-headers thread))))
	  (setf (nth pos? (http-headers thread)) new-item)
	  (reclaim-gensym-tree-with-text-strings old-item))
	;;Note: the HTTP specification suggests that we should be sorting our
	;;header fields by type, but that requires too much knowledge.
	;;http://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html#sec4.2
	(gensym-push new-item (http-headers thread)))))

(defun enqueue-text-into-reply (thread datum)
  (thread-enqueue-event thread :add-data)
  (let ((input-mark (input-mark-of-http-client thread)))
    (unless (reply-headers-have-been-sent thread)
      (emit-headers-of-response
	thread "200 OK"))
    (insert-text-at-mark input-mark datum)))



;;; The function `encode-weblink-html-text' .... Gensym-string is a gensym
;;; string in UTF-G; we import it, then export it.  This assumes that the
;;; charset-name in the http-header-charset-name slot of http-client-thread is a
;;; fully valid transcoding purpose, and furthermore, that it is guaranteed to
;;; return a Gensym string (Lisp string), though not one encoded in UTF-G, but
;;; rather encoded in the desired target character set.

(defun encode-weblink-html-text (gensym-string http-client-thread)
  (let* ((text-string
	   (gensym-string-to-wide-string gensym-string))
	 (encoded-string
	   (export-text-string
	     text-string
	     (map-charset-name-to-transcoding-purpose
	       (http-header-charset-name http-client-thread)))))
    (prog1 encoded-string
      (reclaim-text-string text-string))))




(defun enqueue-finish-into-reply (thread)
  (thread-enqueue-event thread :end-data))


;;; `Eval-form-to-obtain-url' is a thread function.  It evaluates the
;;; form form-for-resource-generation within a dynamic extent that
;;; allows calles to enqueue-into-reply.   It then runs until the
;;; :pending mark is cleared from the thread status moving the
;;; reply off to the user.

(defun-for-thread eval-form-to-obtain-url ()
  (with-thread ((:locals  (header-mode :sending-data))) ;; Note 1.
    (:initialize
      (gensym-push
	(gensym-cons (number-of-thread current-thread)
		     current-thread)
	current-fetch-ids)
      (macrolet ((gp (k)
		   `(get-property-of-buffer
		      (input-mark-of-http-client current-thread) ,k)))
	(eval-resource-generation-method
	  (gp 'form-for-resource-generation)))
      #+development
      (dformat "~&to: ~S" :service-the-reply-q)
      (yield :service-the-reply-q)
      )

    (:cleanup
      (let ((entry (assq (number-of-thread current-thread)
			 current-fetch-ids)))
	(when entry
	  (setf current-fetch-ids
		(delete-gensym-element entry current-fetch-ids))
	  (reclaim-gensym-cons entry))))

    (:service-the-reply-q
      (let ((input-mark (input-mark-of-http-client current-thread))
	    (output-mark (output-mark-of-http-client current-thread))
	    (event? (thread-dequeue-event current-thread)))
	#+development
	(when event?
	  (dformat "~&in: ~S ~S" :service-the-reply-q event?))
	(when (eq event? :end-data)
	  (setf (status-of-http-client-response current-thread) :done))
	(case event?

	  ;; Usual Case
	  ((:add-data :end-data nil)
	   (unless (mark-eq input-mark output-mark)
	     (socket-write-region (socket-of-http-client current-thread)
				  output-mark
				  input-mark)))
	  ;; Problem
	  (:socket-issue
	   (setf (status-of-http-client-response current-thread)
		 :socket-issue))
	  ;; Wierdness
	  (otherwise
	   (bridge-log "ignoring event ~A" event?)))
	(if (eq :pending (status-of-http-client-response current-thread))
	    (yield :service-the-reply-q)
	    (yield :return))))))

;; Note 1: header-mode is TBD.  I should be generating a header
;; for all replys (presuming the protocol level is high enough,
;; and I should be sending some passed down by the user.



;;; `Eval-resource-generation-method' would be cooler if it executed
;;; the form in a less hand crafted manner, but for now it just muddles
;;; thru executing the forms generated by compile-resource-method.

(defun eval-resource-generation-method (form)
  (macrolet ((gp (k)
	       `(get-property-of-buffer
		  (input-mark-of-http-client current-thread) ,k)))
    (let ((fetch-id (number-of-thread current-thread)))
      (cond
	((consp form)
	 (case (car form)

	   (handle-url-via-call-back-to-g2-function
	    (let* ((signature (second (second form))))
	      (handle-url-via-call-back-to-g2-function
		fetch-id
		(gp 'url-details-of-request)
		signature)))

	   (handle-url-via-file-system
	    (handle-url-via-file-system
	      fetch-id
	      (second form)
	      (gp 'url-details-of-request)))

	   (handle-url-via-internal-pages
	    (handle-url-via-internal-pages))

	   #+development
	   (otherwise
	    (error "Huh"))))
	#+development
	(t
	 (error "Huh2"))))))




;;; `handle-url-via-call-back-to-g2-function'

(defun handle-url-via-call-back-to-g2-function (fetch-id
						 url-details
						 signature)
  (let ((routine-name (pop signature))
	(argument-alist nil)
	(argument-list nil)
	(bailout? nil)
	(bailout-apology "Malformed CGI arguments."))
    (with-mark-on-fresh-buffer (m)
      (insert-text-at-mark m url-details)
      (mark-tab m 0)
      (with-buffer-parsing (m)
	(scan-upto-character #\?)
	(scan-text "?")
	(with-mark (right-edge-of-search-part current-right-of-parsing)
	  (setf argument-alist
		(loop
		  with args = ()
		  as key = nil
		  as value = nil
		  do
		  (setf key (scan-symbol))
		  (scan-text "=")
		  (or (scan-upto-character #\&)
		      (scan-upto-end))
		  (setf value
			(coerce-www-form-urlencoded-to-ascii-text
			  (get-simple-text-from-last-scan)))
		  (gensym-push (gensym-cons key value) args)
		  (unless (scan-text "&")
		    (return args))))
	  (set-property-of-buffer
	    (input-mark-of-http-client current-thread)
	    'cgi-arguments argument-alist)
	  (set-property-of-buffer
	    (input-mark-of-http-client current-thread)
	    'search-part
	    (copy-text-between-marks right-edge-of-search-part
				     current-right-of-parsing))
	  (set-property-of-buffer
	    (input-mark-of-http-client current-thread)
	    'cgi-routine-name
	    (copy-gensym-string (symbol-name routine-name))))

	(setf argument-list
	      (loop
		with call-site = ()
		for (argument-name type) in signature
		as arg-entry? = (assq argument-name argument-alist)
		as argument-value
		   = (if arg-entry?
			 (let ((argument-text (cdr arg-entry?)))
			   (case type
			     (symbol
			      (intern-internet-text-for-g2 argument-text))
			     (integer
			      (let* ((text-string (copy-text-string argument-text))
				     (arg?
				       (prog1 (text-string-parse-integer text-string)
					 (reclaim-text-string text-string))))
				(cond
				  (arg? arg?)
				  (t
				   (setf bailout? t)
				   0))))
			     (text
			      (prep-internet-text-for-g2 argument-text))))
			 (let ((result
				 (if (eq 'fetch-id argument-name)
				     fetch-id
				     (built-in-argument-name?
				       (output-mark-of-http-client
					 (thread-of-fetch-id? fetch-id))
				       argument-name))))
			   (when (eq result no-such-built-in-argument)
			     (setf result 1)
			     (setf bailout? t)) 
			   result))
		do (gensym-push argument-value call-site)
		finally
		  (return (nreverse call-site))))
	
	(cond
	  (bailout?
	   (decline-to-serve fetch-id bailout-apology))
	  (t
	   (let ((current-icp-socket
		   (icp-socket-of-server
		     (parent-of-thread current-thread))))
	     (declare (special current-icp-socket))
	     (apply-rpc-imported-g2 routine-name argument-list))))
	(reclaim-gensym-list argument-list)))))





(defparameter the-server-name "G2 WebLink")

(defun built-in-argument-name? (request-mark argument-name-or-symbol)
  (with-permanent-allocation
    (let ((argument-name
	    (if (symbolp argument-name-or-symbol)
		(symbol-name argument-name-or-symbol)
		argument-name-or-symbol)))
      (macrolet ((gp (key) `(get-property-of-buffer request-mark ,key)))
	(loop for (key method . details)
		  in '(("url-details" buffer-property url-details-of-request)
		       ("auth-type" tbd)
		       ("http-client-host-name" buffer-property
			http-client-host-name)
		       ("fetch-id" integer-buffer-property fetch-id)
		       ("remote-addr" buffer-property http-client-host-address)
		       ("remote-host" buffer-property http-client-host-name)
		       ("remote-ident" tbd)
		       ("remote-user" tbd)
		       ("request-method" buffer-property verb-of-request)
		       ("request-mime-headers" request-mime-headers)
		       ("path-info" buffer-property url-details-of-request)
		       ("path-translated" buffer-property? path-translated?)
		       ("query-string" buffer-property? search-part)
		       ("script-name" buffer-property? cgi-routine-name)
		       ("server-name" server-name)
		       ("server-port" server-port)
		       ("server-protocol" constant "HTTP/1.0")
		       ("server-software" server-name)
		       ("gateway-interface" constant "CGI/1.1")
		       ("content-length" tbd)
		       ("content-type" content-type))
	      when (string-equal argument-name key)
		do
		  (return
		    (case method
		      (buffer-property    (gp (car details)))
		      (buffer-property?   (or (gp (car details))
					      ""))
		      (integer-buffer-property
		       (thread-format "~D" (gp (car details))))
		      (server-name the-server-name)
		      (request-mime-headers
		       (let* ((raw-text
				(copy-text-between-marks (gp 'left-edge-of-mime-headers)
							 (gp 'right-edge-of-mime-headers))))
			 (prog1
			     (copy-for-thread-tree raw-text)
			   (reclaim-gensym-string raw-text))))
		      (server-port
		       (thread-format "~D"
				      (port-number-of-server
					the-http-server-thread?)))
		      (remap
		       (built-in-argument-name? request-mark (car details)))
		      (constant (car details))
		      (content-type
		       (let ((verb (gp (car details))))
			 (if (string-equal "HEAD" verb)
			     "NOT-IMPLEMENTED"
			     "")))
		      (tbd
		       "NOT-IMPLEMENTED")
		      (otherwise
		       "UNKNOWN_METHOD_FOR_BUILDIN")))
	      finally
		(cond
		  ((not (string-prefix= "HTTP-" argument-name))
		   (return no-such-built-in-argument))
		  (t ;; Try to find this in the MIME Headers
		   (return
		     (or
		       (loop
			 with sloppy? = (symbolp argument-name-or-symbol)
			 with key = (thread-string-substring
				      argument-name 5 nil)
			 for (key2 . value) in (gp 'mimi-headers-from-server)
			 when (if sloppy?
				  (string-equal key key2)
				  (string= key key2))
			   do (return value))
		     no-such-built-in-argument))
		 )))))))

(defun built-in-argument-of-fetch-id (fetch-id argument-name)
  (let* ((thread-of-fetch (validate-fetch-id fetch-id))
	 (resource-mark (output-mark-of-http-client thread-of-fetch))
	 (first-try
	   (built-in-argument-name? resource-mark argument-name))
	 (result-in-latin1
	   (macrolet ((gp (key) `(get-property-of-buffer resource-mark ,key)))
	     (block nil
	       (unless (eq first-try no-such-built-in-argument)
		 (return first-try))
	       (when (eq 'fetch-id argument-name)
		 (let ((fetch-id-as-string
			 (thread-format "~D" fetch-id)))
		   (return fetch-id-as-string)))
	       (loop named search-for-cgi-argument
		     for (name . value) in (gp 'cgi-arguments)
		     when (string-equal (symbol-name name) argument-name)
		       do (return value)) ;; return from block.
	       (signal-from-rpc
		 'no-such-built-in-argument
		 "There is no such built in argument")))))
    (prep-internet-text-for-g2 result-in-latin1)))





;;; The function `prep-internet-text-for-g2' prepares raw character data to be
;;; sent via ICP to G2.

;;; This function underwent a significant change in 8.0r1 to support
;;; multilingual text in URL's, i.e. to support multilingual input via forms
;;; (HQ-4806960 "non-ascii/multilingual form input in weblink").  The key change
;;; is to generally assume a more expressive charset encoding on top of the "URL
;;; encoded" URL that Weblink receives in response to a form being completed.
;;; Previously, only the ASCII (7-bit) charset was assumed, and other characters
;;; were discarded.  Now the default charset of Weblink (usually UTF-8) is
;;; assumed.

;;; The most popular browser, Internet Explorer, sends form data as UTF-8 by
;;; default.  Fortunately, UTF-8 is also Weblink's default charset.  Note, too,
;;; that the use of UTF-8 with URL-encoding for form data is recommended by
;;; Internet standards body W3 among others, e.g., here:
;;; http://www.w3.org/International/O-URL-code.html

;;; Note that there's usually no good reason not to just stick with the defaults
;;; (i.e., UTF-8 as default charset).  Among the possible reasons: some older
;;; browsers cannot be made to send form data as UTF-8, and/or some may be
;;; configured not to send UTF-8 just because they're dealing mostly with older
;;; web servers, which are then likely to be using the local character set of
;;; the system they're on. If that is the case, then setting the default charset
;;; (i.e., to match the local character set) may be helpful.  However, note that
;;; pages emitted from G2 will then be, by default, in that charset; but that
;;; can be overridden per page served via zgw-set-url-reply-charset.

(defun prep-internet-text-for-g2 (internet-text)
  (let* ((text-string
	   (import-text-string
	     internet-text
	     (map-charset-name-to-transcoding-purpose
	       default-http-header-charset-name)))
	 (utf-g-gensym-string
	   (export-text-string
	     text-string
	     'utf-g-gensym-string)))
    (prog1 (copy-for-thread-tree utf-g-gensym-string)
      (reclaim-text-string text-string)
      (reclaim-gensym-string utf-g-gensym-string))))



;;; The function `intern-internet-text-for-g2' takes an internet-text, which is
;;; generally CGI argument text, which has been decoded from url-encoding but
;;; is otherwise assumed to be encoded in the default charset of Weblink. It
;;; imports the string, prepares it using subfunction
;;; prep-internet-text-string-for-g2-symbol, and returns the result of
;;; interning it, substituting :NIL if interning it results in the symbol nil.
;;;
;;; This function does not reclaim its argument. And it does it cons up any new
;;; object that needs reclamation.

;;; `Prep-internet-text-string-for-g2-symbol' takes an text-string, i.e., a
;;; wide string with Unicode characters. It returns a text string copy with
;;; these modifications:
;;;
;;;    (a) The length is limited to maximum-length-for-user-symbols.  This is a
;;;    very generous allowance (tens of thousands).  Truncation is performed,
;;;    if necessary, to achieve this restriction.
;;;
;;;    (b) Leading and trailing "blank" characters are removed. (These are
;;;    characters in the wide-character class blank. Such characters include:
;;;    horizontal and vertical whitespce characters, including space, tab,
;;;    return, and linefeed.)
;;;
;;;    (c) Illegal Unicode characters (i.e., characters FFFF and FFFE) are
;;;    removed.  These characters are disallowed in G2 symbols because they are
;;;    deemed by the Unicode standard as not normally acceptable in plain text,
;;;    and because some text processing in G2 may assume they can never occur
;;;    in plain text.
;;;
;;;    (d) Remaining characters are upcased using char-upcasew.
;;;
;;; This always returns a valid G2 symbol, and never an error result.
;;;
;;; Note that this may produce the empty symbol (symbol with symbol-name "").
;;; That is something that the G2 reader cannot currently emit; however, it is
;;; possible to create such a symbol in G2 using the text-to-symbol function.
;;;
;;; Note, too, that this does NOT recognize any quoting character. In
;;; particular, @ and \ may are taken literally, and do not themselves require
;;; quoting.  (If any special quote processing were to be required, the
;;; workaround, for an application, would be to accept text instead of a symbol
;;; and do such processing on the G2 side.)
;;;
;;; Note that this processing is done with reference to the function
;;; non-valid-symbol-text-string-p and the funcalled-evaluator text-to-symbol.
;;; In particular, this is intended to produce only a subset of the symbols
;;; that could be produced by text-to-symbol, which accepts the set of texts
;;; acceptable to non-valid-symbol-text-string-p plus the empty string.

(defun intern-internet-text-for-g2 (internet-text)
  (let* ((text-string
	   (import-text-string
	     internet-text
	     (map-charset-name-to-transcoding-purpose
	       default-http-header-charset-name)))
	 (prepped-text-string
	   (prog1 (prep-internet-text-string-for-g2-symbol text-string)
	     (reclaim-text-string text-string)))
	 (result-symbol
	   (or (intern-text-string prepped-text-string)
	       :nil)))  ; good ole' special :nil rule; see note below!
    result-symbol))

(defun prep-internet-text-string-for-g2-symbol (text-string)
  (twith-output-to-text-string
    (loop with length = (wide-string-length text-string)
	  for start from 0 below length
	  as character = (charw text-string start)
	  while (blank-p character)
	  finally
	    (loop for end from length above start
		  as character = (charw text-string (-f end 1))
		  while (blank-p character)
		  finally
		    (loop with output-length = 0
			  for i from start below end
			  as character = (charw text-string i)
			  while (<f output-length
				    maximum-length-for-user-symbols)
			  unless (or (char=w character #uFFFF) ; illegal unicode
				     (char=w character #uFFFE))
			    do (twrite-wide-character (char-upcasew character))
			       (incff output-length))))))

;; Note: what about syntactic anomalies (e.g., symbols with symbol-name "," or
;; "100")?  See type-of-syntactic-anomaly, syntactically-numeric-p, and
;; punctuation-mark-p.  Class-qualified attribute names (e.g., foo::bar) also
;; may be an issue.  What about nil?!  Text-to-symbol does not handle these
;; cases currently. I've filed bug HQ-4829942 "text-to-symbol mishandles NIL,
;; syntactically numeric text, and punctuation" for that.  ICP symbol passing
;; doesn't seem to handle this either.  I've filed a bug for that: HQ-4829997
;; "symbols passed via ICP mishandle nil, and syntactically anomolous symbols".
;; The ICP fix will probably be needed to take care of this, since it will
;; probably be done on the G2 side. Regarding NIL, this interns that as :NIL,
;; i.e., nil interned in the keyword package, following the "good ole' special
;; :nil rule", and then that has to be handled with ICP. (MHD 7/9/04)





;;;

(defparameter default-file-type-to-mime-type-coersions
    '(("bin"  "application/octet-stream" binary)  ; raw binary
      ;("oda"  "application/oda"        binary)  
      ("pdf"  "application/pdf"        binary)
      ("class" "application/java"      binary)
      ("cla"   "application/java"      binary)
      ;("ai"   "application/postscript" 8bit)    ; Adobe Illustrator
      ("ps"   "application/postscript" 8bit)    ; PostScript
      ("eps"  "application/postscript" 8bit)    ;
      ("snd"  "audio/basic"           binary)  ; Audio
      ("au"   "audio/basic"           binary)  ;
      ;("bmp"  "image/bmp"             binary)  ; OS/2 bitmap format
      ("gif"  "image/gif"             binary)  ; GIF
      ;("ief"  "image/ief"             binary)  ;"image Exchange fmt
      ("jpg"  "image/jpeg"            binary)  ; JPEG
      ("jpe"  "image/jpeg"            binary)  ;
      ("jpeg" "image/jpeg"            binary)  ;
      ("tif"  "image/tiff"            binary)  ; TIFF
      ("tiff" "image/tiff"            binary)  ;
      ("html" "text/html"             8bit)    ; HTML
      ("htm"  "text/html"             8bit)    ; HTML on PCs
      ("c"    "text/plain"            7bit)    ; C source
      ("h"    "text/plain"            7bit)    ; C headers
      ("C"    "text/plain"            7bit)    ; C++ source
      ("cc"   "text/plain"            7bit)    ; C++ source
      ("hh"   "text/plain"            7bit)    ; C++ headers
      ("m"    "text/plain"            7bit)    ; Objective-C source
      ("f90"  "text/plain"            7bit)    ; Fortran 90 source
      ("txt"  "text/plain"            7bit)    ; Plain"text
      ("rtx"  "text/richtext"         7bit)    ; MIME Richtext format
      ("tsv"  "text/tab-separated-values"     7bit)    ; Tab-separated values
      ("mpg"  "video/mpeg"            binary)  ; MPEG
      ("mpe"  "video/mpeg"            binary)  ;
      ("mpeg" "video/mpeg"            binary)  ;
      ("qt"   "video/quicktime"       binary)  ; QuickTime
      ("mov"  "video/quicktime"       binary)  ;
      ;("cxx"  "text/plain"            7bit)    ; C++
      ;("for"  "text/plain"            7bit)    ; Fortran
      ;("mar"  "text/plain"            7bit)    ; MACRO
      ;("log"  "text/plain"            7bit)    ; logfiles
      ;("com"  "text/plain"            7bit)    ; scripts
      ;("sdml" "text/plain"            7bit)    ; SDML
      ;("list" "text/plain"            7bit)    ; listfiles
      ;("lst"  "text/plain"            7bit)    ; listfiles
      ;("def"  "text/plain"            7bit)    ; definition files
      ;("conf" "text/plain"            7bit)    ; definition files
      ;; A default is wired into the routine.
      ))


(defparameter newline-string
  #.(concatenate'string (list #\return #\linefeed)))

;;; `handle-url-via-file-system'

(defun handle-url-via-file-system (fetch-id root-pathname details)
  (declare allowing-unwind)
  (let* ((munged-details (case local-file-system
			  ((dos win32)
			   (let ((result
				   (copy-gensym-string details)))
			     (loop for i from 0 below (length result)
				   when (char= #\/ (char result i))
				     do (setf (char result i) #\\))
			     result))
			  (t
			   (copy-gensym-string details))))
	 (namestring (tformat-gensym-string "~A~A" root-pathname munged-details))
	 (input-mark (input-mark-of-http-client current-thread))
	 (thread-of-request (thread-of-fetch-id? fetch-id))
	 #+development
	 (total-count 0))
    (reclaim-gensym-string munged-details)
    (g2-stream-with-open-stream (stream namestring
					:direction :input
					:element-type (unsigned-byte 8))
      (cond
	(stream
	 ;; Emit the headers, first noting the preferred content type.
	 (add-message-header-field
	   current-thread "Content-type"
	   (let* ((pn (gensym-pathname namestring))
		  (file-type? (gensym-pathname-type pn))
		  (narrow-type? (and file-type? (wide-string-to-gensym-string file-type?))))
	     (prog1
		 (loop
		   finally (return "text/plain")
		   for (key value) ;; note ignoring coersion advice.
		       in default-file-type-to-mime-type-coersions
		   when (and narrow-type? (string-equal narrow-type? key))
		     do (return value))
	       (when narrow-type? (reclaim-gensym-string narrow-type?))
	       (reclaim-gensym-pathname pn))))
	 (emit-headers-of-response
	   current-thread
	   "200 OK")
	 ;; Emit Resource
	 (loop as count? = (g2-stream-read-into-buffer
			     current-foreign-string-pad
			     max-of-foreign-string-pad
			     stream)
	       ;;for counter from 0 to 10
	       doing
	   (cond
	     ((null count?)
	      (enqueue-text-into-reply
		thread-of-request
		"<H1>Error encountered generating URL<H1>
")
	      (return nil))
	     ((=f count? 0) ;; EOF
	      #+development
	      (bridge-log "Enqueued ~D bytes" total-count)
	      (return nil))
	     (t
	      #+development
	      (incff total-count count?)
	      (insert-subtext-at-mark
		input-mark current-foreign-string-pad 0 count?))))
	 )
	(t ;; no stream :-(
	 (bridge-log "Not found: ~S" namestring)
	 (decline-to-serve fetch-id "Resource not found.")
	 )))
    (enqueue-finish-into-reply thread-of-request)
    (reclaim-gensym-string namestring)))


(defun emit-headers-of-response (thread error-code-text)
  (unless (reply-headers-have-been-sent thread)
    (let ((input-mark (input-mark-of-http-client thread))
	  (saw-content-type nil))
      (setf (reply-headers-have-been-sent thread) t)
      (when (<=f 1000
		 (get-property-of-buffer input-mark 'protocol-of-request))
	(macrolet ((emit (txt)
		     `(let ((text ,txt ))
			(if (wide-string-p text)
			    (setf text (prep-internet-text-for-g2 text)))
			(insert-subtext-at-mark
			  input-mark text 0 (length text))))
		   (emit-line (txt)
		     `(progn (emit ,txt) (emit newline-string))))
	  (emit "HTTP/1.0 ")
	  (emit-line error-code-text)
	  (loop for header in (http-headers thread) do
	    (emit (car header))
	    (emit ": ")
	    (if (string-equal (car header) "Content-type")
		(progn
		  (emit (cdr header))
		  (emit ";charset=")
		  (emit-line (map-charset-name-to-charset-string
			       (http-header-charset-name thread)))
		  (setq saw-content-type t))
		(emit-line (cdr header))))
	  (unless saw-content-type
	    (emit "Content-type: text/html;charset=")
	    (emit-line (map-charset-name-to-charset-string
		    (http-header-charset-name thread))))
	  (emit-line ""))))))

;; A slight incompatibility has been introduced in the current version where
;; content-type has the charset specified at the end, which is the case for the
;; common case of computed text being emitted from G2. Previously, we did not
;; specify the charset, so the old default was effectively iso-8859-1 (Latin 1).
;; That was in fact documented as the default character set, and the only one
;; possible in fact.  Now, we've changed the default to UTF-8, but you can
;; change it.  This seeming incompatibility should not be a problem in most
;; cases, since virtually all browsers these days can handle UTF-8 as well as
;; Latin-1, as long as they know what the encoding is.  In the worst case, users
;; would simply have to start weblink with the -default-url-reply-charset
;; latin-1 command-line option. (MHD 6/10/04)

;; The file coercion advice is being ignored.
;; Not checking if the MIME type is "acceptible" to the client.



(defun decline-to-serve (fetch-id apology?)
  (let* ((thread-of-request (thread-of-fetch-id? fetch-id)))
    (emit-headers-of-response
      thread-of-request
      "404 Not Found")
    (enqueue-text-into-reply thread-of-request "<H1>Unable to provide URL</H1>
")
    (when apology?
      (enqueue-text-into-reply thread-of-request apology?))
    (enqueue-finish-into-reply thread-of-request)))

;; It should be possible to configure this to get the
;; error from the file system or via a call back to
;; G2.






;;;; Server Internal Status Pages




(defparameter server-pages
  '(("overview.html" generate-overview-html)
     ))

(defvar statistic-counters
  '((count-of-number-of-http-clients "~D HTTP Client requests")))

(defmacro def-statistic-counter (name format)
  `(progn
     (defvar ,name 0)
     (let ((entry? (assq ',name statistic-counters)))
       (if entry?
	   (setf (second entry?) ,format)
	   (pushnew (list ',name ,format) statistic-counters)))
     ',name))
  
(defun generate-overview-html (insert-mark)
  (with-html-output
      (:insert-mark insert-mark :title "Overview of Server Status")
    (with-element ("H1") (emit "GSI-Web The G2/Internet Bridge"))
    (with-element ("H2") (emit "Version Information"))
    #+development
    (with-paragraph () (emit "<B>This is the development version.</B>"))
    (with-paragraph ()
      (let ((text
	      (twith-output-to-gensym-string
		(loop for i
			  in system-version-of-current-gensym-product-line			  do (tformat "~S " i)))))
	(emit text)
	(emit build-identification-string)

	(reclaim-gensym-string text)))

    (with-element ("H2") (emit "Thread Information"))
    (with-element ("UL")
      (generate-thread-tree-html root-thread))

    (with-element ("H2") (emit "Statistics"))
    (with-element ("UL")
      (loop for (name format) in statistic-counters
	    do (emit "<LI>")
	       (femit format (symbol-value name))))
    ))

(defun generate-thread-tree-html (thread)
  (with-html-cliches ()
    (emit "<LI>")
    (femit "~S/~S ~S ~S"
	   (state-of-thread thread)
	   (reason-for-state-of-thread thread)
	   (name-of-thread thread)
	   (number-of-thread thread))
    (when (children-of-thread thread)
      (with-element ("UL")
	(loop for c in (children-of-thread thread)
	      do (generate-thread-tree-html c))))))

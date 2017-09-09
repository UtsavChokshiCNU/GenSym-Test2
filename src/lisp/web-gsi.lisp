;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WEB-GSI

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde



;;;; Introduction

;;; This module is a Lisp Based GSI bridge.










;;;; Global State Denoting what product we are.



;;;; Ping Bridge

(def-statistic-counter count-of-gw-ping
    "~D calls on gw-ping")

;;; `gw-ping' takes no arguments, and returns zero.  It's
;;; function it allow the G2 to test if the bridge is connected,
;;; etc.  Presumably G2 can take actions to repair the situation
;;; if this isn't the case.

(def-rpc-exported-to-g2 (zgw-ping (:returns))
    ()
  (incf count-of-gw-ping)
  (return-from-zgw-ping))







;;;; Kill Bridge


;;; `Shutdown-requested' is polled by the top level loop
;;; in C, and set by routines that feel that the process
;;; should comit suicide.

(defvar shutdown-requested nil)


;;;; `gw-kill-bridge' provides a tool to enable G2 to force the bridge to
;;;; shutdown entirely.

(def-rpc-exported-to-g2 (zgw-kill-bridge (:returns))
    ()
  (bridge-log "G2 Killed Me.")
  (return-from-zgw-kill-bridge)
  (setf shutdown-requested :shutdown))





;;;;  Bridge Configuration



(def-statistic-counter count-of-gw-configure-bridge
    "~D calls on gw-configure-bridge")

(def-rpc-exported-to-g2 (zgw-configure-bridge (:returns))
    ((bridge-configuration-item item))
  (bridge-log "Configure-bridge")
  (incf count-of-gw-configure-bridge)
  (with-permanent-allocation
    (macrolet ((f (x)
		 `(lgsi-get-attribute-value bridge-configuration-item ,x)))
      (setf (bridge-has-proxy-info? the-bridge-configuration-info)
	    t)
      (setf (maximum-count-of-simultaneous-transactions
	      the-bridge-configuration-info)
	    (f 'maximum-count-of-simultaneous-transactions))
      (setf (message-pool-size the-bridge-configuration-info)
	    (f 'message-pool-size))
      ))
  (return-from-zgw-configure-bridge))

;;;; Fetching Resources from G2.

(def-statistic-counter count-of-url-requests-upon-g2
    "~D URL have been requested from G2.")

(defun request-url-from-g2 (number-of-request details-of-request)
  (incf count-of-url-requests-upon-g2)
  (bridge-log "Ask G2: ~S" details-of-request)
  (request-url-from-g2-1 number-of-request details-of-request))

(def-rpc-imported-from-g2 (request-url-from-g2-1 gw-request-for-url)
    ((number-of-request integer)
     (details-of-request text)))

(def-rpc-exported-to-g2 (zgw-decline-to-serve-url (:returns))
    ((number-of-request integer)
     (apology text))
  (let ((thread-of-request (validate-fetch-id number-of-request)))
    (emit-headers-of-response
      thread-of-request "404 Not Found")
    (let ((encoded-string
	    (encode-weblink-html-text apology thread-of-request)))
      (enqueue-text-into-reply thread-of-request encoded-string)
      (reclaim-gensym-string encoded-string))
    (enqueue-finish-into-reply thread-of-request)
    (return-from-zgw-decline-to-serve-url)))



(def-rpc-exported-to-g2 (zgw-set-header-field (:returns))
  ((message-id integer)
   (header text)
   (data text))
  (let ((thread-of-request (validate-fetch-id message-id)))
    (if (reply-headers-have-been-sent thread-of-request)
	(signal-from-rpc 'invalid-header "Can't set header fields after URL data sending has begun."))	
    (add-message-header-field thread-of-request header data)
    (return-from-zgw-set-header-field)))


(def-rpc-exported-to-g2 (zgw-set-url-reply-charset (:returns))
  ((message-id integer)
   (charset-name symbol))
  (let ((thread-of-request (validate-fetch-id message-id)))
    (if (reply-headers-have-been-sent thread-of-request)
	(signal-from-rpc 'invalid-header "Can't set header fields (URL reply charset) after URL data sending has begun."))
    (when (map-and-validate-charset-name charset-name)
      (setf (http-header-charset-name thread-of-request) charset-name))
    (return-from-zgw-set-url-reply-charset)))




(def-rpc-exported-to-g2 (zgw-add-to-url-reply (:returns))
    ((number-of-request integer)
     (more-data text))
  (let* ((thread-of-request (validate-fetch-id number-of-request))
	 (encoded-string
	   (encode-weblink-html-text more-data thread-of-request)))
    (enqueue-text-into-reply thread-of-request encoded-string)
    (reclaim-gensym-string encoded-string)
    (return-from-zgw-add-to-url-reply)))

(def-rpc-exported-to-g2 (zgw-finish-url-reply (:returns))
    ((number-of-request integer))
  (let ((thread-of-request (validate-fetch-id number-of-request)))
    (enqueue-finish-into-reply thread-of-request)
    (return-from-zgw-finish-url-reply)))

(def-rpc-exported-to-g2 (zgw-get-attribute-of-request (:returns (result text)))
    ((number-of-request integer)
     (argument-name text))
  (return-from-zgw-get-attribute-of-request
    (built-in-argument-of-fetch-id number-of-request argument-name)))




(def-statistic-counter count-of-gw-install-fetch-style
    "~D calls on gw-install-fetch-style")


;; Fetch styles storing should include gsi-current-context-number.




;;;; Server Full Response Header Parsing

(defun consume-header-if-any (mark-to-leave-at-resource-start)
  (let ((mark-of-resource-min mark-to-leave-at-resource-start)
	(major-version 0) ;; What we presume an old server.
	(minor-version 9) 
	(error-code 200)) ;; Old servers always work.

    (macrolet ((set-prop (prop value)
		 `(set-property-of-buffer
		    mark-of-resource-min ,prop ,value)))

      ;; Parse the header. 
      (with-buffer-parsing (mark-of-resource-min)
	
	(when ;; This has a well formed Header
	    (and
	      (scan-text "HTTP/")
	      (setf major-version (scan-integer))
	      (scan-text ".")
	      (setf minor-version (scan-integer))
	      (scan-one-or-more-spaces-and-tabs)
	      (setf error-code (scan-integer)))
	  (scan-to-end-of-line)
	  (unless error-code (setf error-code 10099))
	  (unless (=f error-code 200)
	    (set-prop 'error-message-from-server
		      (get-simple-text-from-last-scan)))

	  (scan-to-beginning-of-next-line)
	  ;; If this has headers consume them.
	  (when (<=f 1 major-version)
	    (loop while (scan-header-line mark))
	    (scan-to-beginning-of-next-line) ;; Note A
	    )
	  (mark-set mark-of-resource-min current-right-of-parsing)))

      ;; Store what we learned on the resource's plist
      (set-prop 'major-version-of-http major-version)
      (set-prop 'minor-version-of-http minor-version)
      (set-prop 'error-code-from-server error-code))))


;; Note A, this moves one or two characters, which is a symptom
;; of the nonstandard line termination so popular in the web.









;;;; The Resource Cache.


(defparameter cache-name-counter nil)

(defun init-cache-name-counter ()
  (multiple-value-bind (second minute hour day month year)
      (get-decoded-real-time) ;; Time without garbage
    (setf cache-name-counter
	  (+f (ashf (-f  year 1900) 20)
	      (ashf month 16)
	      (ashf day 12)
	      (ashf hour 8)
	      (ashf minute 4)
	      second))))

(defun-void twrite-cache-number (positive-fixnum radix)
  (declare (type fixnum positive-fixnum radix))
  (if (>=f positive-fixnum radix)
      (let ((quotient (floorf-positive positive-fixnum radix))
	    (remainder (modf-positive positive-fixnum radix)))
	(declare (type fixnum remainder))
	(twrite-cache-number quotient radix)
	(twrite-char (digit-char remainder radix)))
      (twrite-char (digit-char positive-fixnum radix))))

;; twrite-positive-fixnum-in-radix was eliminated in GSI

(defun generate-resource-cache-name ()
  (unless cache-name-counter
    (init-cache-name-counter))
  (let* ((name
	   (twith-output-to-gensym-string
	     (twrite-string "/Z")
	     (twrite-cache-number (incff cache-name-counter) 32)))
	 (pathname
	   (gensym-make-pathname
	     :directory (cache-directory-name the-bridge-configuration-info)
	     :name name)))
    (prog1
	(gensym-namestring pathname)
      (reclaim-gensym-string name)
      (reclaim-gensym-pathname pathname))))

(defun cache-toc-namestring ()
  (let ((pathname
	  (gensym-make-pathname
	    :directory (cache-directory-name the-bridge-configuration-info)
	    :name "toc")))
    (prog1
	(gensym-namestring pathname)
      (reclaim-gensym-pathname pathname))))

;; Need to use the pathname mechinisms here, not raw string handling.

(defun-allowing-unwind write-resource-to-file (resource file-ascii-namestring)
  (when (g2-stream-probe-file-for-exist file-ascii-namestring)
    (g2-stream-delete-file file-ascii-namestring))
  (g2-stream-with-open-stream (stream file-ascii-namestring
				      :direction :output)
    (when stream ;; Note A
      (with-mark (start-of-resource (get-property-of-buffer
				      resource
				      'begining-of-resource))
	(with-mark (end-of-buffer start-of-resource)
	  (mark-move-to-end end-of-buffer)
	  (with-text-between-marks ((text-string start end)
				    (start-of-resource end-of-buffer))
	    (cond
	      ((=f 0 start)
	       (g2-stream-write-from-buffer
		 text-string
		 end
		 stream))
	      (t
	       (let ((text (gensym-string-substring text-string start end)))
		 (g2-stream-write-from-buffer
		   text
		   (-f end start)
		   stream)
		 (reclaim-gensym-string text))))))))))

;; Note A.  Should put this in an issues list for the
;; thread to report somewhere.

(defun-allowing-unwind read-resource-from-file (resource namestring)
  (cond
    ((not (g2-stream-probe-file-for-exist namestring))
     nil)
    (t
     (g2-stream-with-open-stream (stream namestring :direction :input)
       (with-mark (insert-mark resource)
	 (loop as count? = (g2-stream-read-into-buffer
			     current-foreign-string-pad
			     max-of-foreign-string-pad
			     stream)
	       doing
	   (cond
	     ((null count?)
	      (error "Error reading resource cache."))
	     ((=f count? 0) ;; EOF
	      (return nil))
	     (t
	      (insert-subtext-at-mark
		insert-mark current-foreign-string-pad 0 count?))))))
     resource)))



(defvar items-in-resource-cache nil)

(defun enter-resource-into-cache (resource)

  ;; Do not double cache it.
  (unless (get-property-of-buffer resource 'cache-filename)

    ;; Save this into the disk cache.
    (set-property-of-buffer
      resource 'cache-filename
      (generate-resource-cache-name))
    (write-resource-to-file
      resource (get-property-of-buffer resource 'cache-filename))

    ;; Remember we have it in the cache.
    (let ((mark resource))
      (with-bindings ((resource-buffer buffer-plist) (mark))
	(let ((plist
		(loop
		  with url
		  with cache-filename
		  with mimi-headers-from-server
		  finally
		    (remove-url-from-cache url nil)
		    (return
		      (gensym-list
			'url url
			'cache-filename cache-filename
			'mimi-headers-from-server
			mimi-headers-from-server))
		  for (key value) on buffer-plist by #'cddr doing
		  (case key
		    (url
		     (setf url (copy-resource-plist-value value)))
		    (cache-filename
		     (setf cache-filename (copy-resource-plist-value value)))
		    (mimi-headers-from-server
		     (setf mimi-headers-from-server
			   (copy-resource-plist-value value)))
		    ;; cache-filename 
		    ;; error-code-from-server 
		    ;; minor-version-of-http 
		    ;; major-version-of-http
		    ;; mimi-headers-from-server
		    ;; begining-of-resource  -- a mark
		    ;; end-of-transmission-recieved  -- Duh.
		    ;; url 
		    ;; fetch-id -- useless?
		    ;; cleaning-up-line-terminator
		  ))))
	(gensym-push plist items-in-resource-cache))))
    (write-cache-toc items-in-resource-cache)))

(defun remove-url-from-cache (url write-cache-toc?)
  (loop with entries-to-remove = nil
	for cache-entry in items-in-resource-cache
	as url-of-entry = (getf cache-entry 'url)
	when (string= url url-of-entry)
	  do
	    (let ((filename (getf cache-entry 'cache-filename)))
	      (gensym-delete-file filename))
	    (gensym-push cache-entry entries-to-remove)
	finally
	  (when entries-to-remove
	    (loop for entry in entries-to-remove
		  do
	      (setf items-in-resource-cache
		    (delete-gensym-element entry items-in-resource-cache)))
	    (reclaim-gensym-list entries-to-remove)
	    (when write-cache-toc?
	      (write-cache-toc items-in-resource-cache)))))

(defun reload-from-cache-info (cache-info)
  
  (let* ((resource (make-mark-into-new-empty-resource-buffer))
	 (read-ok?
	   (read-resource-from-file
	     resource
	     (getf cache-info 'cache-filename))))
    (cond
      ((not read-ok?)
       (reclaim-resource-buffer-of-mark resource)
       nil)
      (t
       (setf (plist-of-resource-buffer
	       (resource-buffer-of-mark resource))
	     (loop for (key value) on cache-info by #'cddr
		   nconc (gensym-list
			   key (copy-resource-plist-value value))))
       (set-property-of-buffer
	 resource
	 'begining-of-resource
	 (make-mark-at-start resource))
       resource))))

(defun is-url-in-cache? (url)
  (loop for cache-info in items-in-resource-cache
	as cache-url = (getf cache-info 'url)
	when (string= cache-url url)
	  do (return cache-info)))

(defun release-from-cache (cache-info)
  (let ((filename (getf cache-info 'cache-filename)))
    (when (g2-stream-probe-file-for-exist filename)
      (g2-stream-delete-file filename))
    (setf items-in-resource-cache
	  (delete-gensym-element cache-info
				 items-in-resource-cache))
    (reclaim-plist-of-resource-buffer cache-info)))




(defun-allowing-unwind write-cache-toc (entries)
  (bridge-log "Writing table of contents for cache (~D entries)"
	      (length entries))
  (let ((namestring (cache-toc-namestring))
	(ok? t))
    (when (g2-stream-probe-file-for-exist namestring)
      (g2-stream-delete-file namestring))
    (g2-stream-with-open-stream (stream namestring :direction :output)
      (cond
	((not stream)
	 (bridge-log "Cache directory (~S) doesn't exist or isn't writable."
		     (gensym-namestring namestring))
	 (setf ok? nil))
	(t
	 (g2-stream-write-line "gm-toc-1.0" stream)
	 (g2-stream-write-line ";;; Machine Generated -- Do Not Modify" stream)
	 (write-cache-toc-1 entries stream))))
    (reclaim-gensym-string namestring)
    ok?))

(defun write-cache-toc-1 (data stream)
  (macrolet ((recure (x) `(write-cache-toc-1 ,x stream)))
    (cond
      ((null data)
       (g2-stream-write-char #\N stream))
      ((symbolp data) ;; Note we are ignoring the package!
       (g2-stream-tformat stream "S~D|~S" (length (symbol-name data)) data))
      ((stringp data)
       (g2-stream-tformat stream "T~D|~A" (length data) data))
      ((and (consp data)
	    (not (listp (cdr data))))
       (g2-stream-tformat stream "C" (length data) data)
       (recure (car data))
       (recure (cdr data)))
      ((listp data)
       (loop with length = (length data)
	     initially
	       (g2-stream-tformat stream "L~D|" length)
	       (g2-stream-terpri stream)
	     for tail on data
	     doing
	 (recure (car tail))
	 (g2-stream-terpri stream)
	 (unless (listp (cdr tail))
	   (g2-stream-write-char #\X stream)
	   (recure (cdr tail))))))))

(defun-allowing-unwind read-cache-toc ()
  (let* ((namestring (cache-toc-namestring))
	 (ok? t)
	 (no-log? nil))
    (setf items-in-resource-cache
	  (g2-stream-with-open-stream (stream namestring
					      :direction :input)
	    (cond
	      ((not (and stream
			 (string= (g2-stream-read-line stream)
				  "gm-toc-1.0")))
	       (setf no-log? t)
	       (setf ok? (write-cache-toc nil))
	       nil)
	      (t
	       (read-cache-toc-1 stream)))))
    (reclaim-gensym-string namestring)
    (unless no-log?
    (bridge-log "Read table of contents for cache (~D entries)"
		(length items-in-resource-cache)))
    ok?))

(defun read-cache-toc-1 (stream)
  (macrolet ((recure () `(read-cache-toc-1 stream)))
    (tagbody
     restart
       (return-from read-cache-toc-1
	 (let ((dispatch (g2-stream-read-char stream)))
	   (case dispatch
	     (#\; ;; Comment
	      (reclaim-text-string
		(g2-stream-read-line stream))
	      (go restart))

	     ((#\return #\linefeed #\space) ;; Ignorable White space.
	      (go restart))
	     
	     (#\X ;; List Ends in a CDR
	      '#1=#:CDRCODE-MARKER)

	     (#\L ;; List
	      (let* ((length (read-cache-toc-count stream)))
		(loop with result = (gensym-cons (recure) nil)
		      with tail = result
		      for i from 2 below length
		      doing
		  (setf tail
			(setf (cdr tail)
			      (gensym-cons (recure) nil)))
		      finally
			(when (=f 1 length)
			  (return result))
			(setf (cdr tail)
			      (let ((last-element (recure)))
				(if (eq '#1# last-element)
				    last-element
				    (gensym-cons last-element nil))))
			(return result))))

	     (#\C ;; Alist entry.
	      (gensym-cons (recure) (recure)))

	     (#\T
	      (let* ((length (read-cache-toc-count stream))
		     (text (obtain-simple-gensym-string length)))
		(loop for i from 0 below length
		      doing
		  (setf (char text i) (g2-stream-read-char stream)))
		text))
	     (#\S ;; A symbol
	      (let* ((length (read-cache-toc-count stream))
		     (text (obtain-simple-gensym-string length)))
		(loop for i from 0 below length
		      doing
		  (setf (char text i) (g2-stream-read-char stream)))
		(intern-gensym-string text)))

	     (#\N nil)
	))))))

(defun read-cache-toc-count (stream)
  (loop with result = 0 finally (return result)
	as c = (g2-stream-read-char stream)
	until (or (eq #\| c) (not c))
	doing (setf result (+f (*f 10 result)
			       (digit-char-p c)))))

(defun preflight-cache-directory ()
  (read-cache-toc)) ;; returns nil if the cache is unreachable.







;;;; G2 Fetching a Resource








;;; `gw-fetch-url-contents' is exported for use by G2.


(def-statistic-counter count-of-gw-fetch-url-contents
    "~D calls on gw-install-fetch-url-contents")


(defun filter-data-for-get-line-from-url (status string?)
  (let ((incomming-mark
	  (resource-buffer-of-fetch-thread current-thread)))
    (case status
      (:add-data
       (with-typing-at-mark (incomming-mark)
	 (loop for i from 0 below (length string?)
	       for c = (char string? i)
	       do (type c))
	 (reclaim-gensym-string string?)))
      (:end-data
       ;; Note this into the the resource buffer's PList?
       (set-property-of-buffer
	 incomming-mark
	 'end-of-transmission-recieved
	 t)))))

(defun postprocess-result-fragments (mark)
  (macrolet ((set-prop (prop value)
	       `(set-property-of-buffer mark ,prop ,value)))

    ;; Thread the headers and figure out how to split the buffer.
    (let ((fetch-style-info
	    (fetch-style-info-of-fetch-thread current-thread))
	  (mark-of-resource-min
	    (set-prop
	      'begining-of-resource
	      (mark-tab (mark-copy mark) (point-min mark)))))
      (consume-header-if-any mark-of-resource-min)

      ;; Cache this baby.
      (enter-resource-into-cache mark)
      ;; Return what interests the user, and coerce it to gensym text.

      (cond
	((return-cache-filename-of-fetch-style fetch-style-info)
	 (twith-output-to-gensym-string
	   (twrite-gensym-characters-from-ascii-string
	     (get-property-of-buffer mark 'cache-filename))))
	(t
	 (with-mark (min-mark mark-of-resource-min)
	   (with-mark (max-mark mark-of-resource-min)

	     ;; Let Fetch Style determine what to include
	     (when (return-server-prefix-of-fetch-style
		     fetch-style-info)
	       (mark-tab min-mark (point-min min-mark))
	       (mark-move max-mark -2))
	     (when (return-resource-of-fetch-style fetch-style-info)
	       (mark-tab max-mark (point-max max-mark)))

	     ;; Coerce the resource buffer into Gensym Text, and return it.
	     (let* ((ascii-string
		      (copy-text-between-marks
			min-mark
			max-mark))
		    (dumb-gensym-string
		      (twith-output-to-gensym-string
			(twrite-gensym-characters-from-ascii-string
			  ascii-string))))
	       (prog1
		   (coerce-to-simple-gensym-string dumb-gensym-string)
		 (reclaim-gensym-string ascii-string)
		 (reclaim-gensym-string dumb-gensym-string))))))))))





(defun coerce-to-simple-gensym-string (text-string)
  (loop
    finally (return result)
    with length = (length text-string)
    with result = (obtain-simple-gensym-string (length text-string))
    for i from 0 below length
    do (setf (char result i) (char text-string i))))



;;;; Configuring the Bridge to Provide HTTP service


(def-rpc-exported-to-g2 (zgw-start-http-server (:returns))
    ((port-number integer))
  (startup-http-server port-number)
  (unless the-http-server-thread?
    (signal-from-rpc 'http-startup-failed "Failed to start HTTP server."))
  (return-from-zgw-start-http-server))

(def-rpc-exported-to-g2 (zgw-tender-resources (:returns))
    ((index integer)
     (pattern text)
     (method text))
  (unless (<= 0 index 1000)
    (signal-from-rpc 'tender-failed "Tender index must be in range 0 to 1000"))
  (unless the-http-server-thread?
    (signal-from-rpc 'tender-failed
		     "The HTTP Server is not currently running."))
  (with-permanent-allocation
    (bridge-log "Tendering ~D ~S ~S" index pattern method)
    (let ((result
	    (install-tender-of-resource
	      index
	      pattern
	      method)))
      (unless (=f 0 result)
	(bridge-log "Tendering failed: ~D" result)
	(signal-from-rpc 'tender-failed "Tendering failed"))
      (return-from-zgw-tender-resources))))

#+java-link
(def-rpc-exported-to-g2 (zgw-tender-java-callback (:returns))
    ((index integer)
     (details text))
  (unless (<= 0 index 1000)
    (signal-from-rpc 'tender-failed "Tender index must be in range 0 to 1000"))
  (with-permanent-allocation
    (bridge-log "Tendering java callback ~D ~S" index details)
    (let ((result
	    (install-java-callback
	      index
	      (copy-gensym-string details))))
      (unless (=f 0 result)
	(bridge-log "Tendering failed: ~D" result)
	(signal-from-rpc 'tender-failed "Tendering failed"))
      (return-from-zgw-tender-resources))))

(def-rpc-exported-to-g2 (zgw-make-base64-encoded
			  (:returns (result text)))
    ((input text))
  (let ((output (convert-text-to-base64-encoding input)))
    (return-from-zgw-make-base64-encoded output)
    (reclaim-gensym-string output)))







;;;; Callback Routines Required by GSI







;;; `gsi-get-tcp-port' returns the port we want GSI to listen at.

(defun-gsi-callback (gsi-get-tcp-port :fixnum-long) ()
  7736)




;;; `gsi-pause-context' is invoked when G2 is paused.

(defun-gsi-callback (gsi-pause-context :fixnum-long) ()
  (setf the-state-of-g2 :paused)
  (bridge-log "G2 was paused"))




;;; `gsi-resume-context' is invoked when G2 resumes again.

(defun-gsi-callback (gsi-resume-context :fixnum-long) ()
  (setf the-state-of-g2 :running)
  (bridge-log "G2 was resumed"))




;;; `gsi-g2-poll' is invoked "regularly" when the gsi-interface-object is
;;; configured to enable polling by G2 of the GSI.

(defun-gsi-callback (gsi-g2-poll :fixnum-long) ()
  (bridge-log "poll"))




;;; `gsi-receive-registration' is invoked by G2 -- NO DOC?

(defun-gsi-callback (gsi-receive-registration :fixnum-long)
    ((registration :object)) ;; C type is gsi_registration
;  (fake-declare-ignore registration)
  (declare (ignore registration))
  (bridge-log "receive-registration"))




;;; `gsi-receive-deregistrations' is invoked by G2 -- NO DOC?

(defun-gsi-callback (gsi-receive-deregistrations :fixnum-long)
    ((registration-item-array :object)  ;; C type is gsi_registered_item
     (count :fixnum-long))
;  (fake-declare-ignore registration-item-array)
;  (fake-declare-ignore count)
  (declare (ignore registration-item-array count))
  (bridge-log "receive-deregistrations"))




;;; `gsi-get-data' is invoked by G2 to do data seeking for values
;;; of one or more variables in G2.

(defun-gsi-callback (gsi-get-data :fixnum-long)
    ((registration-item-array :object)  ;; C type is gsi_registered_item
     (count :fixnum-long))
  (fake-declare-ignore registration-item-array)
  (fake-declare-ignore count)
  (bridge-log "get-data"))



;;; `gsi-set-data' is invoked by G2 -- NO DOC?
;;; -- I guess this is done when the "set ..." action/statement
;;; -- fires.

(defun-gsi-callback (gsi-set-data :fixnum-long)
    ((registration-item-array :object)  ;; C type is gsi_registered_item
     (count :fixnum-long))
  (fake-declare-ignore registration-item-array)
  (fake-declare-ignore count)
  (bridge-log "set-data"))




;;; `gsi-recieve_message' is invoked by G2 -- NO DOC?
;;;  -- I guess this is called when inform the operator is done upon
;;   -- the gsi-interface object?

(defun-gsi-callback (gsi-receive-message :fixnum-long)
    ((message :object)  ;; C type is char*
     (length :fixnum-long))
  (fake-declare-ignore message)
  (fake-declare-ignore length)
  (bridge-log "receive-message"))






#+development ;; In gw_main see Note A
(defun-gsi-callback (gsi-initialize-context :fixnum-long)
    ((remote-thread-initialization-string :simple-string)
     (length :fixnum-long))
  (fake-declare-ignore length)
  (bridge-log "Context Init (~S)." remote-thread-initialization-string)
  (setf (svref info-for-gw-request-for-url 0)
	(lgsi-rpc-declare-remote 'GW-REQUEST-FOR-URL 2 0))
  (inner-initialize-context))

(defun-gsi-callback (inner-initialize-context :fixnum-long)
    ()
  (initialize-fetch-styles-of-context)
  (setf the-state-of-g2 :running)
  gsi-success)



;;; `gsi-shutdown-context' is invoked when G2 shuts down, it is the
;;; inverse of gsi-initialize-context

(defun-gsi-callback (gsi-shutdown-context :fixnum-long) ()
  (shutdown-fetch-styles-of-context)
  (bridge-log "G2 was reset.")
  (when the-http-server-thread?
    (bridge-log "Shutting down HTTP server.")
    (thread-kill the-http-server-thread?))
  ;; Tear down the impression we are configured.
  (setf (bridge-has-proxy-info? the-bridge-configuration-info) nil)
  (setf the-state-of-g2 :unconnected)
  gsi-success ;; HA!
  )



;; Note A: I can't do this yet, the storage for the rpc-declare-remote is a
;; problem, and the need for the C name of the routine is too.


#+development ;; In gw_main see Note A.
(defun-gsi-callback (gsi-set-up :fixnum-long)  ()
  (gsi-set-option gsi-one-cycle)
  ;; Install our error handler
  (lgsi-install-error-handler 'gw-error-handler)

  ;; Export our RPC offerings to G2.
  (lgsi-rpc-declare-local 'zgw-configure-bridge
			  "ZGW-CONFIGURE-BRIDGE")
  (lgsi-rpc-declare-local 'zgw-install-fetch-style
			  "ZGW-INSTALL-FETCH-STYLE")
  (lgsi-rpc-declare-local 'zgw-fetch-url-contents
			  "ZGW-FETCH-URL-CONTENTS")
  #+development
  (lgsi-rpc-declare-local 'zgw-ping "ZGW-PING")
  (lgsi-rpc-declare-local 'zgw-kill-bridge "ZGW-KILL-BRIDGE")
  (lgsi-rpc-declare-local 'zgw-decline-to-serve-url
			  "ZGW-DECLINE-TO-SERVE-URL")
  (lgsi-rpc-declare-local 'zgw-add-to-url-reply
			  "ZGW-ADD-TO-URL-REPLY")
  (lgsi-rpc-declare-local 'zgw-finish-url-reply
			  "ZGW-FINISH-URL-REPLY")
  (lgsi-rpc-declare-local 'zgw-get-attribute-of-request
			  "ZGW-GET-ATTRIBUTE-OF-REQUEST")
  (lgsi-rpc-declare-local 'zgw-start-http-server
			  "ZGW-START-HTTP-SERVER")
  (lgsi-rpc-declare-local 'zgw-tender-resources
			  "ZGW-TENDER-RESOURCES")
  #+java-link
  (lgsi-rpc-declare-local 'zgw-tender-java-callback
			  "ZGW-TENDER-JAVA-CALLBACK")
  (lgsi-rpc-declare-local 'zgw-make-base64-encoded
			  "ZGW-MAKE-BASE64-ENCODED")
  gsi-success)

(defun-gsi-callback (gw-error-handler :fixnum-long) 
    ((context :fixnum-long)
     (number :fixnum-long)
     (message :simple-string))
  (fake-declare-ignore context)
  (case number
    #+development
    (#.gsi-remote-declaration-not-found (break))
    (#.gsi-rpc-late-async-abort
     ;; G2 aborted an RPC, and we had a return value for 'em.
     )
    (otherwise
     (with-permanent-allocation
       ;; Here, as in numerous places in GW by calls to bridge-log, we wrap
       ;; with-permanent-allocation to eliminate warnings by
       ;; warn_gensym_area_violation -- not esp. clean!! In this particular
       ;; case, this addresses bug HQ-4830241 "RPC errors cause Memory
       ;; inconsistency (type 3)". (MHD 8/10/04)
       (bridge-error "~%Ignoring -- Error ~D ~S" number message)))))


#+(and obsolete development) ;; Redefine so gsi-one-cycle-works.
(defun-allowing-unwind enter-abyss ()
  (catch :shutdown
    (loop
      unless shutdown-requested doing
      (reset-counters-for-all-icp-sockets)
      (startup-bridge)
      (let ((within-run-loop-extent t))
	(catch (return-from-gsi-run-loop)
	  (loop doing
	    (catch-abort (0)
	      (process-icp-sockets))
	    (when (gsi-option-is-set-p gsi-one-cycle)
	      (kick-bridge-tasks))
	    (just-idle-process gsi-maximum-idle-interval))))
       ;; leaving the run loop means you're outside any "context".  -ncc, 5/4/94
      (setf gsi-current-context-number gsi-undefined-context)
      (shutdown-bridge)
       )))

#+development
(defun-allowing-unwind enter-abyss ()

  (reset-counters-for-all-icp-sockets)	
  (startup-bridge) ;; added.
  (let ((within-run-loop-extent t))
    (loop
      named outer-loop
      do (catch-abort (0)
	       (loop
		 do (process-icp-sockets)
		    (when (gsi-option-is-set-p gsi-one-cycle)
		      (kick-bridge-tasks))
;;		 if (gsi-option-is-set-p gsi-one-cycle)
;;		   do
		    (kick-bridge-tasks) ;; added
		    (sleep .4)
		     ;; (return-from outer-loop nil) ;; removed
;;		 else (just-idle-process gsi-maximum-idle-interval)
		 ))))
  ;; leaving the run loop means you're outside any "context".  -ncc, 5/4/94
  (setf gsi-current-context-number gsi-undefined-context)
  (shutdown-bridge) ;; added
  )

(defun startup-bridge ()
  (bridge-log "Bridge Starting Up")

  ;; What's up with the next two lines? See note! (MHD 6/13/04)
  (cache-command-line-if-necessary)
  (setq command-line-arguments
	(get-initial-command-line-arguments))
  
  #+java-link
  (startup-java-backchannel-server 8888))

;; Note: it turns out the code to initialize the system variable
;; command-line-arguments never ensured the command line had been processed
;; enough for it to work by calling cache-command-line-if-necessary.  In TW & G2
;; it happens to work, but in GSI it's not called until after
;; command-line-arguments have been established (as nil).  This corrects that
;; problem.  Too close to release to do a more general fix. Fix later!
;; (MHD 6/13/04)



(defun shutdown-bridge ()
  (bridge-log "Bridge Shutting Down")
  (shutdown-thread-tree))


;;;; What passes here for a scheduler.

(defun-allowing-unwind kick-bridge-tasks ()
  ;; way stupid, but functional.
  (let ((result
	  (catch 'shutdown
	    (end-io-wait)
	    (loop repeat 100 doing
	      (feed-running-threads)
	      (when (= 0 number-of-running-threads) (return)))
	    '#1=#:ok)))
    #+development
    (when (= 0 number-of-running-threads)
      (add-sample-to-total-pool-outstanding-object-count-history))
    (unless (eq result '#1#)
      (bridge-log "Caught shutdown.")
      (setf shutdown-requested t))))


;; (reload-foreign-libraries)


;;;; Development Only Facilities

#+(and development lep)
(defvar *gw-process* nil)

#+(and development lep)
(defun kill-gw ()
  (when *gw-process* 
    (lcl:kill-process (shiftf *gw-process* nil))))

#+(and development lep)
(defun break-gw ()
  (when *gw-process* 
    (lcl:interrupt-process *gw-process* #'break)))


#+development
(defmacro with-process-wrapping ((name) &body body)
  (declare (ignore args))
  #+lep
  `(progn
     (kill-gw)
    (setf *gw-process*
      (lcl:make-process 
       :name ,name
       :function #'(lambda ()
		     (lcl:with-terminal-buffer (nil 
						(concatenate'string "*" ,name "*"))
		       (progn ; lcl:with-debug-buffer () 
			 ,@body))))))
  #-lep
  `(progn ,name ,@body))

#+development
(defun launch-gw ()
  (with-process-wrapping ("gw")
    (launch-gsi)))


(load-foreign-libraries-for-ab-when-appropriate)

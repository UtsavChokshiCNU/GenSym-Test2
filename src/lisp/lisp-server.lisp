;;;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module LUCID-SERVER (now LISP-SERVER): A simple network port server

;;; Copyright (c) 2010 Versata Software, Inc.
;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Fred White and Ben Hyde
;;; Subsequently:  Chun Tian (binghe)

;;;; Network Lisp Listener and Eval Server

#+lispworks
(eval-when (:compile-toplevel :load-toplevel :execute)
  (cl:require "comm"))

;;; `*server-kinds*' is the know it all table of that configures
;;; the kinds of serves we have invented.

(defvar *server-kinds* ())

(defmacro define-server-kind (name () &rest info)
  `(progn
     (pushnew ',name *server-kinds*)
     (setf (get ',name :server-info)
	   '(:name ,name ,@info))
     ',name))


;;; A `:lisp-server' once started, will listen on port 2001, and if
;;; a client appears it will then create a read eval port for him to
;;; use.  See read-eval-print-client for additional details.

(define-server-kind :lisp-server ()
  :type 0
  :listener-port 2001
  :client-function read-eval-print-client)


;;; `Get-server-info' finds the info for a server given a key
;;; with is either :name or :type.

(defun get-server-info (key value)
  (loop for kind in *server-kinds*
	as info = (get kind :server-info)
	when (equal (getf info key) value)
	  do (return info)))


;;; `Get-server-slot-value' is getf on steroids, it implements the
;;; defaults for various slots.

(defun get-server-slot-value (info slot)
  (or (getf info slot)
      ;; Default behaviors
      (getf
	'(:listener-function lisp-server)
	slot)
      (error "unknown slot in server info")))


;;;; Interface to C code.

;;; These are entirely different from those used by G2 for it's
;;; own networking.

#+lucid
(lcl:def-foreign-function (socket-open
			    #+solaris
			    (:name "socket_open")
			    (:return-type :signed-32bit))
    (port :signed-32bit))

#+lucid
(lcl:def-foreign-function (c-server-loop
			    #+solaris
			    (:name "c_server_loop")
			    (:return-type :signed-32bit))
    (socket :signed-32bit)
    (type :signed-32bit))

#+lucid
(lcl:def-foreign-function (socket-close 
			    #+solaris
			    (:name "socket_close")
			    (:return-type :signed-32bit))
    (socket :signed-32bit))

#+lucid
(lcl:def-foreign-function (hostname 
			    #+solaris
			    (:name "hostname")
			    (:return-type :simple-string)))

#+lucid
(lcl:def-foreign-callable (g2int-lisp-server-loop 
			    #+solaris
			    (:name "g2int_lisp_server_loop")
			    (:return-type :signed-32bit))
    ((socket :signed-32bit)
     (type :signed-32bit))
  (multiple-value-bind (name function)
      (let ((info (get-server-info :type type)))
	(values (symbol-name (get-server-slot-value info :name))
		(get-server-slot-value info :client-function)))
    (let* ((count (count function lcl:*all-processes*
			 :key #'lcl:process-initial-function))
	   (process-name (format nil "~a-~d" name (1+ count))))
      (lcl:make-process
	:function function
	:args (list socket)
	:name process-name)
      0)))

#+lispworks
(defun-simple g2int-lisp-server-loop (socket type)
  (multiple-value-bind (name function)
      (let ((info (get-server-info :type type)))
        (values (symbol-name (get-server-slot-value info :name))
                (get-server-slot-value info :client-function)))
    (let* ((count (count function (mp:list-all-processes)
                         :key #'mp::process-function))
           (process-name (format nil "~a-~d" name (1+ count))))
      (mp:process-run-function process-name nil function socket)
      0)))

;; Enabled for Solaris. (MHD 3/13/97)
;; I got ../ext/opt/lucidsrv.o by going to ../ext/c/, and
;; doing   gcc -c lucidsrv.c   and then
;; doing   mv lucidsrv.o ../../ext/opt     (MHD 3/13/97)

#+lucid
(let ((file (format nil "~A/ext/opt/lucidsrv.o"
		    dest-directory-name)))
  (if (probe-file file)
      (lcl:load-foreign-files
	file
	#+solaris '("libsocket.so" "libnsl.so"))
      (error "can't find ~s" file)))



;;;; Starting and Killing Servers


;;; `Start-server' takes the name one of the servers enumerated in the list
;;; *server-kinds*, and launchs it if it isn't launched already.

#+lucid
(defun start-server (name)
  (let* ((info (get-server-info :name name))
	 (function (get-server-slot-value info :listener-function))
	 (port (get-server-slot-value info :listener-port))
	 (code (get-server-slot-value info :type)))
    (cond ((find-process name)
	   (warn "Process ~s is already running" name)
	   (find function lcl:*all-processes* :key #'lcl:process-name))
	  (t
	   (lcl:make-process :name (string name)
			     :function function
			     :args (list port code))))))

#+lispworks
(defun start-server (name)
  (let* ((info (get-server-info :name name))
         (port (get-server-slot-value info :listener-port))
         (code (get-server-slot-value info :type))
         process)
    (cond ((setq process (find-process name))
           (warn "Process ~s is already running" name)
           process)
          (t
           (setq process
                 (comm:start-up-server :function 'lisp-server
                                       :announce nil
                                       :service port
                                       :process-name (string name)))
           #+development (assert process)
           (when process
             (setf (mp:process-property 'type process) code))
           process))))

;;; `Kill-servers' kills all the server processes and the client processes
;;; spawned by those servers.

#+lucid
(defun kill-servers ()
  (loop with all-server-functions
	= (loop for kind in *server-kinds*
		as info = (get kind :server-info)
		collect (get-server-slot-value info :listener-function)
		collect (get-server-slot-value info :client-function))
    for process in lcl:*all-processes*
	when (member (lcl:process-initial-function process)
		     all-server-functions)
	  collect process
	  and do (lcl:kill-process process)))

#+lispworks
(defun kill-servers ()
  (nconc
   (loop with all-server-functions
         = (loop for kind in *server-kinds*
                 as info = (get kind :server-info)
                 collect (get-server-slot-value info :client-function))
         for process in (mp:list-all-processes)
         when (member (mp::process-function process)
                      all-server-functions)
           collect process
           and do (mp:process-kill process))
   (loop with process
         for kind in *server-kinds*
         when (setq process (find-process kind))
           collect process
           and do (mp:process-kill process))))

;;; `Lisp-Server' implements the deamon that waits on the server's port
;;; hoping for clients to help.  It calls thru to the C routine that
;;; does the waiting, and that C routine calls back to a function to
;;; spawn the process that helps the client.

#+lucid
(defun-allowing-unwind lisp-server (port type)
  (let ((socket -1))
    (unwind-protect
	 (progn
	   (setq socket (socket-open port))
	   (when (>= socket 0)
	     (setf (lcl:process-whostate lcl:*current-process*)
		   "Listen")
	     (c-server-loop socket type)))
      (when (>= socket 0)
	(socket-close socket)))))

#+lispworks
(defun-allowing-unwind lisp-server (handle)
  (let ((type (mp:process-property 'type)))
    #+development (assert type)
    (g2int-lisp-server-loop handle type)))

;;;; Client: Generic Read Eval Print Loop

#+lucid
(defun-allowing-unwind read-eval-print-client (socket)
  (format lcl:*initial-io*
	  "~&# Starting Process: ~S~%"
	  (lcl:process-name lcl:*current-process*))
  (let (socket-stream?)
    (block :serve-client
      (lcl:handler-bind ;; See Note A
	((lcl:stream-error
	   #'(lambda (condition)
	       (when (stream-bad-or-in-this-condition-p socket-stream?
							condition)
		 (format lcl:*initial-io*
			 "~&# Killing Muted Process: ~S~%"
			 (lcl:process-name lcl:*current-process*))
		 (return-from :serve-client nil))
	       ;; Otherwise, decline to handle the error.
	       )))
	(with-open-stream (stream (lcl:make-lisp-stream
				    :input-handle socket
				    :output-handle socket
				    :auto-force t))
	  (setf socket-stream? stream)
	  (let ((*terminal-io* stream)) ;; See note B.
	    (format t "~%~a on ~a (~a)~%"
		    (lisp-implementation-version)
		    (hostname)
		    (lcl:process-name lcl:*current-process*))
	    (let (- * ** *** + ++ +++ / // ///)
	      (loop doing
		(lcl:restart-case
		  (progn
		    (princ "> ")
		    (force-output)
		    (setq - (read stream nil))
		    (let ((values (multiple-value-list (eval -))))
		      (dolist (value values)
			(format t "~s~%" value))
		      (force-output)
		      (shiftf *** ** * (first values))
		      (shiftf /// // / values)
		      (shiftf +++ ++ + -)))
		  (lcl:abort () :report "Return to lisp top level."))))))))))

;; Note A: If something corrupts the stream of this process we just kill the
;; process.  We implement that by offering to handle all stream-errors, when a
;; stream error occurs we attempt an operation on the socket's stream and if
;; that fails we handle the error by killing the process and exiting the
;; process.

;; This happens when the client kills his process.  If we didn't do this we
;; would get the "nasty recursive error" as it tries to enter a break on the
;; broken stream.  Then we would end up in a break on *initial-io* and from
;; there we would be in the ugly state of two processes competing for the same
;; stream, i.e. this one in a break and the initial process.

;; Note B:
;;  In Lucid we have this cascade in the stream system, by default:
;;   *gc-output* -bound to-> #<synonym-stream @003>
;;   @003      -references-> *trace-output*
;;   *trace-output*    -bound to-> #<synonym-stream @002>
;;   *standard-input*  -bound to-> #<synonym-stream @002>
;;   *standard-output* -bound to-> #<synonym-stream @002>
;;   *error-output*    -bound to-> #<synonym-stream @002>
;;   *query-io*        -bound to-> #<synonym-stream @002>
;;   *debug-io*        -bound to-> #<synonym-stream @002>
;;   @002    -references-> *terminal-io*
;;   *terminal-io*     -bound to-> #<split-stream @001>
;;   *initial-io*      -bound to-> #<split-stream @001>
;;   @001 is the process standard in and out.
;; So by binding *terminal-io* in the dude above we reroute all
;; output for this process.

#+lispworks
(defun-allowing-unwind read-eval-print-client (socket)
  (let (socket-stream?)
    (block :serve-client
      (cl:handler-bind
          ((cl:stream-error
            #'(lambda (condition)
                (when (eq socket-stream? (cl:stream-error-stream condition))
                  (return-from :serve-client nil))))
           (comm:socket-error
            #'(lambda (condition)
                (declare (ignore condition))
                (return-from read-eval-print-client nil))))
        (with-open-stream (stream (cl:make-instance 'comm:socket-stream
                                                    :socket socket
                                                    :direction :io
                                                    :element-type 'cl:base-char))
          (setf socket-stream? stream)
          (let ((*terminal-io* stream))
            (format t "~%~a ~a on ~a (~a)~%"
                    (cl:lisp-implementation-type)
                    (cl:lisp-implementation-version)
                    (cl:machine-instance)
                    (mp:process-name (mp:get-current-process)))
            (let (- * ** *** + ++ +++ / // ///)
              (loop doing
                (cl:restart-case
                    (progn
                      (princ "> ")
                      (force-output)
                      (setq - (read stream nil))
                      (let ((values (cl:handler-case (multiple-value-list (eval -))
                                      (error () (terpri) nil))))
                        (dolist (value values)
                          (format t "~s~%" value))
                        (force-output)
                        (shiftf *** ** * (first values))
                        (shiftf /// // / values)
                        (shiftf +++ ++ + -)))
                  (cl:abort () :report "Return to lisp top level."))))))))))

;;; `Stream-bad-or-in-this-condition-p' is the test used to assure
;;; that we can trust a process's i/o stream.  For things to be
;;; in good shape we must be able to do the underlying stream
;;; thing on the stream, and we must be able to prove that
;;; the stream-error condition we are passed doesn't involve
;;; this stream.

#+lucid
(defun stream-bad-or-in-this-condition-p (stream stream-error-condition)
  (block nil
    (lcl::handler-bind
      ;; Any error in this process indicates something bogus.
      ((error #'(lambda (c) (declare (ignore c)) (return t))))
      (when (eq (lcl:underlying-stream stream :output)
		(lcl:underlying-stream
		  (sys:structure-ref stream-error-condition 0 t)))
	(return t)))
	nil))

(defun find-process (name)
  #+lucid
  (find (string name) lcl:*all-processes*
        :key #'lcl:process-name
        :test #'string=)
  #+lispworks
  (mp:find-process-from-name (string name))
  #-(or lucid lispworks)
  (progn name nil))

(defun break-process (name)
  (let ((process? (find-process name)))
    (if process?
        (progn
          #+lucid
          (lcl:interrupt-process process? #'break)
          #+lispworks
          (mp:process-break process?))
      (warn "Unknown Process ~s" (string name)))))

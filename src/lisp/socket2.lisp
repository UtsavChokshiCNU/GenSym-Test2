;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")
    
;;;; Module SOCKET2 - Blocking sockets for G2 procedure calls

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Judy Anderson

;;; This file is separate from the socket.lisp, because we want to share that
;;; file with weblink, and this has a whole lot of G2 specific stuff,
;;; e.g. system procedures.

;;; Socket-specific system procedures defined in this file are:

;;;   g2-tcp-connect(host: text, port: integer) = (item-or-value)
;;;   g2-tcp-write(handle: item-or-value, data: text) = ()
;;;   g2-tcp-read(handle: item-or-value) = (text)
;;;   g2-tcp-listen(host: text, port: integer) = (item-or-value)
;;;   g2-tcp-accept(handle: item-or-value) = (item-or-value)
;;;   g2-tcp-close(handle: item-or-value) = ()




;;;; Code body continuations

;;; A `code body continuation' is a convenient way to hold a callback into a
;;; G2 procedure.  This is needed for socket system procedures because all the
;;; networking operations are done in a non-blocking style at the Lisp/C level,
;;; but this mechanism is more general than that and perhaps belongs in
;;; PROC-UTILs.

;;; A G2 system procedure cap that does a network operation and blocks
;;; until it returns should look something like this:
;;;
;;;   g2-blah-blah(...) = (item-or-value)
;;;   ret-var: item-or-value;
;;;   begin
;;;     system call g2-blah-blah(..., the symbol ret-var);
;;;     system wait;
;;;     return ret-var;
;;;   end
;;;
;;; Then in the system procedure function (defined with
;;; defun-for-system-procedure), call `make-code-body-continuation' with the
;;; name of the return variable (i.e. the symbol ret-var) and store the
;;; continuation somewhere (e.g. in a socket structure slot).  Then later, when
;;; the operation completes (e.g. in a socket event handler method), call
;;; `return-value-to-code-body-continuation' on the stored continuation to give
;;; it the value to be placed into the return variable.



;;; The structure `code-body-continuation' holds a paused code body invocation
;;; and the name of a local variable (a symbol) to receive a value when resumed.
;;; The continuation itself also has a name (a symbol), to distinguish it from
;;; other continuations that might be waiting for the same event, and a
;;; completion form (a cons), to clean up after its invocation is completed.
;;; (See install-code-body-invocation-completion-form for details about
;;; completion forms.)

(def-structure (code-body-continuation
		 (:constructor make-code-body-continuation-1
			       (code-body-continuation-invocation
				code-body-continuation-name
				code-body-continuation-variable
				code-body-continuation-completion-form)))
  code-body-continuation-invocation
  code-body-continuation-name
  code-body-continuation-variable
  code-body-continuation-completion-form
  )


;;; The function `make-code-body-continuation' makes a code body continuation
;;; named `name' from the current computation instance.  The return value will
;;; be stored in the variable named by the symbol `ret-var'.  The
;;; `completion-form' (if provided and non-NIL) will be invoked when the
;;; continuation's code-body-invocation is completed.

(defun make-code-body-continuation (name ret-var &optional completion-form)
  ;; TO DO: what if current-computation-instance is not a code-body-invocation?
  (let ((continuation (make-code-body-continuation-1
			current-computation-instance name ret-var
			completion-form)))
    ;; Install a "completion form" to clear out the invocation slot in case it
    ;; aborts or is otherwise closed prematurely.
    (install-code-body-invocation-completion-form
      current-computation-instance
      (gensym-list 'complete-code-body-continuation continuation))
    continuation))

(defun-void complete-code-body-continuation (completion-form)
  (let* ((continuation (second completion-form))
	 (sub-completion-form
	   (code-body-continuation-completion-form continuation)))
    (setf (code-body-continuation-invocation continuation) nil)
    (when sub-completion-form
      (funcall-symbol (car sub-completion-form) sub-completion-form))
    (reclaim-code-body-continuation continuation)
    (reclaim-gensym-list completion-form)))


;;; The macro `return-value-to-code-body-continuation' stores a value into
;;; the designated local variable of the paused code body invocation of a
;;; continuation and resumes the invocation.  If the code body invocation has
;;; already been woken up or completed in some other way (e.g. an abort), this
;;; does nothing.  The `continuation' argument is a place, which will be set to
;;; nil to prevent this from running twice on the same continuation.

(defmacro return-value-to-code-body-continuation (value continuation-place)
  (let ((continuation (gensym)))
    (avoiding-variable-capture (value)
      `(let* ((,continuation ,continuation-place)
	      (invocation (code-body-continuation-invocation ,continuation)))
	 (when invocation
	   (setf (code-body-continuation-invocation ,continuation) nil)
	   (setf ,continuation-place nil)
	   (if (framep ,value)
	       (set-local-name-value-validating-environment
		 invocation (code-body-continuation-variable ,continuation) ,value)
	       (setf (code-body-invocation-local-name-value
		       invocation (code-body-continuation-variable ,continuation))
		     ,value))
	   (wake-up-code-body-invocation invocation))))))


;;; The macro `signal-error-to-code-body-continuation' signals an error to
;;; the paused code body invocation of a continuation and resumes the
;;; invocation.  The error can be either a symbol or an instance of an error
;;; class, in which case error-text-string should be a copy of the
;;; error-description of the error.  If the code body invocation has already
;;; been woken up or completed in some other way (e.g. an abort), this does
;;; nothing.  The `continuation' argument is a place, which will be set to nil
;;; to prevent this from running twice on the same continuation.

(defmacro signal-error-to-code-body-continuation
    (error error-text-string continuation-place)
  (let ((continuation (gensym)))
    `(let* ((,continuation ,continuation-place)
	    (invocation (code-body-continuation-invocation ,continuation)))
       (when invocation
	 (setf (code-body-continuation-invocation ,continuation) nil)
	 (setf ,continuation-place nil)
	 (signal-code-body-invocation-error
	   invocation ,error 1 ,error-text-string nil nil nil nil nil)))))




;;;; G2-socket user class

;;; This class is inspired by the g2-stream class used by file I/O.  It is
;;; returned by various socket operations, and required by various others.  Not
;;; user instantiable, so they can't hurt themselves.


(def-class (g2-socket (item entity) not-user-instantiable do-not-put-in-menus)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50 
      ((polychrome (g2-icon-outline . foreground)
		   (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (text-region . foreground))
       (variables)
       (background-layer)
       g2-icon-background (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
					     ((0 0) (50 0) (47 3))
					     ((3 3) (3 47) (0 50))
					     ((0 0) (47 3) (3 3))
					     ((3 3) (0 50) (0 0)))
       (lines (5 45) (44 45) (44 5))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50)) ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50)) ((50 50) (3 47) (47 47)))
       g2-icon-outline (outline (0 0) (0 50) (50 50) (50 0))
       g2-icon-outline (lines (44 5) (5 5) (5 45))


       (lines (5 28) (25 28))
       (lines (25 28) (25 21))
       (lines (25 21) (45 21))
       (lines (15 20) (15 28))
       (lines (35 21) (35 30))
       (outline (31 30) (31 37) (39 37) (39 30))
       (outline (33 32) (33 35) (37 35) (37 32))
       (outline (11 13) (11 20) (19 20) (19 13))
       (outline (13 15) (13 18) (17 18) (17 15)))))
  (g2-socket-port nil vector-slot not-user-editable (type attribute) do-not-save)
  (g2-socket-status
    newly-created vector-slot not-user-editable (type attribute) do-not-save)
  (g2-socket-remote-host
    nil vector-slot not-user-editable (type attribute) do-not-save)
  (internal-socket? nil not-user-editable system do-not-save))

      
(defun update-g2-socket-status (g2-socket status)
  (if (null g2-socket) nil
  (let ((*current-computation-frame* g2-socket))
    (change-slot-value g2-socket 'g2-socket-status status))))

;;;This is a kluge -- we don't get notified of secure sockets, so we have to
;;;figure it out at read time.
(defun maybe-fix-socket-status (blocking-socket g2-socket)
  (if (and (socket-handle blocking-socket)
	   (=f (c-secure-socket-p (socket-handle blocking-socket)) 1)
	   (eq (g2-socket-status
		 g2-socket)
	       'connected))
      (update-g2-socket-status g2-socket 'connected-secure)))


;;;; Blocking sockets


;;; A `blocking-socket' structure is used to perform a network operation while a
;;; code body continuation waits for the operation to complete (and receives the
;;; return value of the operation, if any).

(def-structure (blocking-socket (:include tcp-socket))
  (blocking-socket-continuation nil)
  (blocking-socket-g2-socket nil :reclaimer cleanup-blocking-socket)
  (blocking-socket-partial-data nil :reclaimer reclaim-blocking-socket-partial-data)
  ;;temporary storage when reading N bytes from a socket
  (blocking-socket-chars-remaining 0)
  (blocking-socket-output-queue nil :reclaimer reclaim-blocking-socket-queue)
  )

(defun-simple make-blocking-socket-with-continuation (name variable)
  (let ((socket (make-blocking-socket)))
    (set-blocking-socket-continuation socket name variable)
    socket))

(defun-void set-blocking-socket-continuation (socket name variable)
  (setf (blocking-socket-continuation socket)
	(make-code-body-continuation
	  name variable
	  (gensym-list 'complete-blocking-socket-continuation socket))))

(defun-void complete-blocking-socket-continuation (completion-form)
  (setf (blocking-socket-continuation (second completion-form)) nil)
  (reclaim-gensym-list completion-form))

(defun reclaim-blocking-socket-partial-data (data)
  (cond ((text-string-p data)
	 (reclaim-text-string data))
	((consp data)
	 (loop for struct in data do
	   (reclaim-evaluation-structure struct)))))
	 
(defun reclaim-output-queue-element (elem)
  (if (text-string-p (car elem))
      (reclaim-text-string (car elem))
      (reclaim-evaluation-sequence (car elem)))
  (reclaim-gensym-cons elem))

(defun reclaim-blocking-socket-queue (queue)
  (when queue
    (loop until (queue-empty-p queue)
	  as elem = (queue-pop queue) do
      (complete-tcp-write-task elem nil))
    (reclaim-queue queue)))

;;; Not really a reclaimer, just fixing up the cross-pointer.
(defun cleanup-blocking-socket (g2-socket)
  (when g2-socket
    (setf (internal-socket? g2-socket) nil)))


;;; A couple things that belong to g2-socket have to go here so they can
;;; reference both g2-socket and blocking-socket structures.

(def-slot-value-reclaimer internal-socket? (blocking-socket)
  ;;The blocking-socket cleans itself up when the socket is closed, so we
  ;;shouldn't handle it here.
  (when blocking-socket
    (setf (blocking-socket-g2-socket blocking-socket) nil)))
  
(defun create-associated-g2-socket (blocking-socket)
  (let ((g2sock (make-transient-item 'g2-socket)))
    (setf (internal-socket? g2sock) blocking-socket)
    (update-g2-socket-status
      g2sock
      (if (socket-handle blocking-socket)
	  (if (=f (c-secure-socket-p (socket-handle blocking-socket)) 1)
	      'connected-secure
	      'connected)
	  ;;It really shouldn't ever happen that the connection is closed
	  ;;before this gets called, but we need to protect c-secure-socket-p
	  ;;against possible NIL value.
	  'connection-closed))
    (when (socket-host blocking-socket) 
      (change-slot-value g2sock 'g2-socket-remote-host
			 (copy-text-string (socket-host blocking-socket))))
    (when (socket-port blocking-socket)
      (change-slot-value g2sock 'g2-socket-port
			 (socket-port blocking-socket)))
    (setf (blocking-socket-g2-socket blocking-socket) g2sock)
    g2sock))



;;; NOTE: The function `network-stack-error' can be called in two environments:
;;;  1. By procedures, inside the stack-based KB intepreter
;;;  2. By HANDLE-EVENT-INTERNAL, outside of the stack (INSIDE-HANDLE-EVENT is T)
;;; For the second case, we MUST NOT throw a STACK-ERROR, or KB corrupted.
;;;
;;; -- Chun Tian (binghe), 5 March 2013, for GENSYMCID-998.

(defun network-stack-error (type error-code socket)
  (let ((error-string
	  (if (socket-handle socket)
	      (network-get-last-error-string (socket-handle socket))
	      (copy-text-string "Error message unavailable for closed socket"))))
    (if inside-handle-event
	(progn
	  (notify-user-at-console "Network ~a failure: ~s (error code ~d)"
				  type error-string error-code)
	  (reclaim-text-string error-string)
	  (close-socket socket)
	  (handle-network-close socket 0))
	(write-stack-error cached-top-of-stack
	  (tformat "Network ~a failure: ~s (error code ~d)"
		   type error-string error-code)
	  (reclaim-text-string error-string)
	  (close-socket socket)))))

(def-substitution-macro stack-error-if-invalid-socket (handle socket)
  (when (null socket)
    (stack-error cached-top-of-stack "Invalid socket ~NF" handle)))


;;; g2-tcp-connect(host: text, port: integer) = (item-or-value)
;;;
;;; Creates a TCP client socket connected to the given IP host address and port
;;; number, and returns a handle to the socket when the connection has been
;;; established.  (Other G2 processing is allowed while it's waiting.)  A stack
;;; error is raised if there's a problem connecting.


;;; The system procedure function `g2-tcp-connect' creates a blocking socket and
;;; connects it to a host and port using TCP/IP.  When the connection completes,
;;; the socket handle is returned in the named return variable.  Errors are 
;;; handled in the handle-network-connect method for blocking-socket.

(defun-for-system-procedure g2-tcp-connect ((host text) (port integer) (ret-var symbol) (options structure))
  (declare (values))
  (let ((blocking-socket (make-blocking-socket-with-continuation
			   'g2-tcp-connect ret-var))
	(secure-p (equal 
		    (evaluation-structure-slot
		      options 'secure evaluation-false-value)
		      evaluation-true-value)))
    (connect-socket blocking-socket host port secure-p)
    (reclaim-evaluation-structure options)))

;;; The structure method `handle-network-connect' for a blocking socket
;;; returns the socket handle to the socket's code body continuation when a
;;; non-blocking connect operation completes.

;;; NOTE: The method `handle-network-connect' can be called in two ways:
;;;
;;;  1. By G2-TCP-CONNECT procedure inside the stack
;;;  2. By HANDLE-EVENT-INTERNAL internally, outside of the stack
;;;
;;; Therefore, to make sure every procedure calls of G2-TCP-CONNECT could
;;; finally return (GENSYMCID-974), `return-value-to-code-body-continuation'
;;; must be called in any case, so the check of ERROR-CODE must be inside of
;;; `(when (and (blocking-socket-continuation blocking-socket) ..) ..)'.
;;;
;;; -- Chun Tian (binghe), 5 March 2013, for GENSYMCID-974.

(def-structure-method handle-network-connect (blocking-socket error-code)
  (if (and (blocking-socket-continuation blocking-socket)
	     (eq (code-body-continuation-name
		  (blocking-socket-continuation blocking-socket))
		 'g2-tcp-connect))
    (let ((g2sock (create-associated-g2-socket blocking-socket)))
      (unless (=f error-code network-status-success)
	(network-stack-error "connection" error-code
			     blocking-socket))
      (return-value-to-code-body-continuation
	g2sock
	(blocking-socket-continuation blocking-socket)))
    (unless (=f error-code network-status-success)
      (network-stack-error "connection" error-code
			   blocking-socket))))

;;; g2-tcp-close(handle: item-or-value) = ()
;;; Close a socket; actual work done by functions in socket1

(defun-for-system-procedure g2-tcp-close ((g2-socket item))
  (declare (values))
  (let ((socket (internal-socket? g2-socket)))
    (when socket
      (cond ((socket-open-p socket)
	     (close-socket socket t)
	     (handle-network-close socket 0))
	    ((null (tcp-socket-close-task socket))
	     (enqueue-tcp-cleanups socket)))))
  (delete-frame g2-socket))

(def-structure-method handle-network-close (blocking-socket error-code)
  (update-g2-socket-status (blocking-socket-g2-socket blocking-socket)
			   (if (data-available-p blocking-socket)
			       'connection-closed-with-unread-data
			       'connection-closed))
  (funcall-superior-method blocking-socket error-code))



;;; g2-tcp-write(handle: item-or-value, data: text) = ()
;;;
;;; Writes a text to a connected socket, returning immediately.  The text should
;;; contain only 8-bit characters, otherwise they will be truncated to their
;;; lower 8 bits.
;;;
;;; [TO DO: wait until the write completes, raise a stack error if it doesn't
;;; complete.  Also, maybe use a text-conversion-style object at this layer
;;; (like G2-stream) rather than making the user do it ahead of time.  Or just
;;; return a G2-stream?]


;;; The system procedure function `g2-tcp-write' writes an evaluation text to a
;;; socket handle, if the socket is connected.  `g2-tcp-write-bytes' writes out
;;; a sequence of bytes rather than a text.


;;; The function `add-task-to-output-queue' adds a tcp-write task to the output
;;; queue of a blocking-socket.  The task will remain on the queue until it
;;; completes, either successfully or unsuccessfully.

(defun add-task-to-output-queue (task blocking-socket)
  (unless (blocking-socket-output-queue blocking-socket)
    (setf (blocking-socket-output-queue blocking-socket) (make-queue)))
  (queue-insert (blocking-socket-output-queue blocking-socket) task)
  (setf (code-body-continuation-completion-form (cdr task))
	(gensym-list 'complete-tcp-write-continuation task)))

;;; The function `complete-tcp-write-continuation' indicates that a tcp-write
;;; continuation has completed, either normally (when the task completes, either
;;; successfully or unsuccessfully) or abnormally (when the continuation is
;;; aborted).  In the abnormal case, the task remains on the queue and is not
;;; reclaimed until it completes.

(defun-void complete-tcp-write-continuation (completion-form)
  (let ((task (second completion-form)))
    (cond ((cdr task)
	   ;; The task has not completed, so clear out the pointer to the
	   ;; continuation so that the task will be reclaimed when it completes.
	   (setf (cdr task) nil))
	  (t
	   ;; Otherwise, the task has completed, so reclaim it directly.
	   (reclaim-output-queue-element task))))
  (reclaim-gensym-list completion-form))

;;; The function `complete-tcp-write-task' indicates that a tcp-write task has
;;; completed, either successfully or unsuccessfully.  The task will be
;;; reclaimed, but the caller is responsible for actually removing the task from
;;; the queue.

(defun-void complete-tcp-write-task (task success-p)
  (cond ((cdr task)
	 (return-value-to-code-body-continuation
	   (make-evaluation-boolean-value success-p) (cdr task))
	 ;; Clear the pointer to the continuation so that the task will be
	 ;; reclaimed when the continuation completes.
	 (setf (cdr task) nil))
	(t
	 ;; Otherwise, the continuation has already completed, so reclaim the
	 ;; task directly.
	 (reclaim-output-queue-element task))))


(defun-for-system-procedure g2-tcp-write ((handle item) (text text) (ret-var symbol))
  (declare (values))
  (let ((socket (internal-socket? handle)))
    (stack-error-if-invalid-socket handle socket)
    (add-task-to-output-queue
      (gensym-cons (copy-text-string text)
		   (make-code-body-continuation 'g2-tcp-write ret-var))
      socket)
    (unless (socket-output-buffer? socket)
      (execute-tcp-write socket))))

(defun-for-system-procedure g2-tcp-write-bytes ((handle item) (seq sequence) (ret-var symbol))
  (declare (values))
  (let ((socket (internal-socket? handle)))
    ;; Pup-up an error message if the socket is invalid, this can avoid aborting G2 in this case.
    (stack-error-if-invalid-socket handle socket)
    ;;Note: the sequence will be used by write-bytes-to-socket and reclaimed
    ;;when it's done.
    (add-task-to-output-queue
      (gensym-cons seq (make-code-body-continuation 'g2-tcp-write ret-var))
      socket)
    (unless (socket-output-buffer? socket)
      (execute-tcp-write socket))))

(defun execute-tcp-write (blocking-socket)
  (let* ((task (queue-peek (blocking-socket-output-queue blocking-socket)))
	 ;; TO DO: if the continuation has completed, don't bother writing.
	 (data (car task))
	 (status 
	   (if (text-string-p data)
	       (write-to-socket blocking-socket data)
	       (write-bytes-to-socket blocking-socket data))))
    (cond ((eq status t)
	   ;;It all went!  Tell the caller, and actually pop the task.
	   (complete-tcp-write-task task t)
	   (queue-pop (blocking-socket-output-queue blocking-socket)))
	  ((eq status 'blocked)
	   ;;It's busy with our request, and is in its internal buffers.
	   ;;We will get notified when it's done.
	   )
	  (t
	   ;;Update error status.  Unfortunately we lost the error message.
	   ;;TO DO: We should try to capture it somewhere, and either raise a
	   ;;stack error or put it in a slot.
	   (update-g2-socket-status (blocking-socket-g2-socket blocking-socket)
					'connection-write-error)
	   (complete-tcp-write-task task nil)
	   (queue-pop (blocking-socket-output-queue blocking-socket))))))

(def-structure-method handle-write-event (blocking-socket error-code)
  ;; TO DO: if the continuation has completed, discard the output buffer instead
  ;; of continuing to write.
  (funcall-superior-method blocking-socket error-code)
  (when (blocking-socket-output-queue blocking-socket)
    ;;Don't bother about this if we've never written anything; sometimes
    ;;windows gives us a write event at the beginning of the session.
    (unless (socket-output-buffer? blocking-socket)
      ;;OK, everything enqueued at the lower level went.  Tell the caller.
      (let ((task (queue-pop (blocking-socket-output-queue blocking-socket))))
	;;HQ-5389246: Sometimes windows gives us a write event when we didn't
	;;think we had anything else to send.  So we ALREADY returned the
	;;values required in a prior call to handle-write-event, or in
	;;execute-tcp-write and this call is bogus.
	(when task
	  (complete-tcp-write-task task t)))
      ;;Look for more work
      (unless (queue-empty-p (blocking-socket-output-queue blocking-socket))
	(execute-tcp-write blocking-socket)))))
  


;;; g2-tcp-read(handle: item-or-value) = (text)
;;;
;;; Waits for some data to arrive on a socket, and then returns the data as a
;;; text (containing only 8-bit characters).  If data has already arrived, it is
;;; returned immediately.  Returns an empty text if there is no more data to be
;;; read.
;;;
;;; [TO DO: wait for N characters, or a regexp?  Allow peek or pushback?  Should
;;; we distinguish between a disconnected socket and an invalid handle?  Use
;;; text-conversion-style?]


;;; The function `return-network-data-to-socket-continuation-if-any' reads all
;;; available bytes from a socket, without blocking, and if there were any,
;;; returns them as an evaluation text to the socket continuation.  If the
;;; socket has been closed, the empty text is returned to the socket
;;; continuation.


(defun append-continuation-data (blocking-socket new-data)
  (let ((current (blocking-socket-partial-data blocking-socket)))
    (cond (current
	   (setf (blocking-socket-partial-data blocking-socket)
		 (concatenate-text-strings current new-data))
       ;;Gensym-473 fix, new-data has been concatenated, it should be reclaimed.
       (reclaim-text-string new-data)		 
	   (reclaim-text-string current))
	  (t (setf (blocking-socket-partial-data blocking-socket)
		   new-data)))))


(defun-void return-network-data-to-socket-continuation-if-any (blocking-socket)
  (when (blocking-socket-continuation blocking-socket)
    (case (code-body-continuation-name
	    (blocking-socket-continuation blocking-socket))

      (g2-tcp-read-block
       (let ((data (read-from-socket blocking-socket)))
	 (if (and (socket-open-p blocking-socket)
		  (zerop (text-string-length data)))
	     ;; No data available, still waiting for more.
	     (reclaim-text-string data)
	     (return-value-to-code-body-continuation
	       (make-evaluation-text-reclaiming-argument data)
	       (blocking-socket-continuation blocking-socket)))))

      (g2-tcp-read-byte
       (let ((byte? (read-byte-from-socket blocking-socket)))
	 (when (or byte? (not (socket-open-p blocking-socket)))
	   (return-value-to-code-body-continuation
	     (or byte? -1) (blocking-socket-continuation blocking-socket)))))

      (g2-tcp-read-line
       (multiple-value-bind (partial-data more-to-do)
	   (read-from-socket-until-char blocking-socket (char-code #\linefeed))
	 ;;Save the partial data.  This may be silly, as it may be complete
	 ;;already.  But it made the code simpler to always save rather than
	 ;;checking if we ever saved already.
	 (append-continuation-data blocking-socket partial-data)
	 ;;If line is complete, or we got EOF, return what we have.
	 (unless (and more-to-do (socket-open-p blocking-socket))
	   (let ((text (blocking-socket-partial-data blocking-socket)))
	     ;;"text" will be reclaimed by the return process, so we nil out
	     ;;partial data to avoid double reclaim.
	     (setf (blocking-socket-partial-data blocking-socket) nil)
	     (return-value-to-code-body-continuation
	       (make-evaluation-text-reclaiming-argument text)
	       (blocking-socket-continuation blocking-socket))))))

      (g2-tcp-read-n-bytes
       (let ((n (blocking-socket-chars-remaining blocking-socket)))
	 (multiple-value-bind (partial-data remaining)
	     (read-n-chars-from-socket blocking-socket n)
	   (append-continuation-data blocking-socket partial-data)
	   (if (or (not (socket-open-p blocking-socket))
		   (=f 0 remaining))
	       (let ((text (blocking-socket-partial-data blocking-socket)))
		 (setf (blocking-socket-partial-data blocking-socket) nil)
		 (return-value-to-code-body-continuation
		   (make-evaluation-text-reclaiming-argument text)
		   (blocking-socket-continuation blocking-socket)))
	       (setf (blocking-socket-chars-remaining blocking-socket)
		     remaining))))))
	 
    (unless (socket-open-p blocking-socket)
      (update-g2-socket-status
	(blocking-socket-g2-socket blocking-socket)
	(if (data-available-p blocking-socket)
	    'connection-closed-with-unread-data
	    'connection-closed)))))



;;; The system procedure function `g2-tcp-read' sets up a code body continuation
;;; so that when data is available on a socket it is returned in the named
;;; return variable.  The returned data is a text if `read-mode' is BLOCK or
;;; LINE, or an integer (the character code) if `read-mode' is BYTE.  If the
;;; socket is not connected, `g2-tcp-read' does not set up a continuation and
;;; returns the false evaluation boolean value, which causes the G2 system
;;; procedure cap to return immediately rather than waiting.

(defun-for-system-procedure g2-tcp-read
    ((handle item) (read-mode symbol) (ret-var symbol))
  (declare (values))
  (let ((socket (internal-socket? handle)))
    (stack-error-if-invalid-socket handle socket)
    (set-blocking-socket-continuation
      socket
      (case read-mode
	(block 'g2-tcp-read-block)
	(line 'g2-tcp-read-line)
	(byte 'g2-tcp-read-byte)
	(t (stack-error cached-top-of-stack
			"Mode ~s is not a valid read mode.  Must be BLOCK, LINE, or BYTE" read-mode)))
      ret-var)
    (return-network-data-to-socket-continuation-if-any socket)))


(defun-for-system-procedure g2-tcp-read-bytes-as-text
    ((handle item) (n integer) (ret-var symbol))
  (declare (values))
  (if (>=f n maximum-length-for-user-text-strings)
      (stack-error cached-top-of-stack
                   "Request to read ~d bytes which exceeds the ~
                    maximum G2 text length, ~d"
                   n maximum-length-for-user-text-strings))
  (let ((socket (internal-socket? handle)))
    (stack-error-if-invalid-socket handle socket)
    (set-blocking-socket-continuation socket 'g2-tcp-read-n-bytes ret-var)
    (setf (blocking-socket-chars-remaining socket) n)
    (return-network-data-to-socket-continuation-if-any socket)))
  

;;; The structure method `handle-read-event' for a blocking socket reads all
;;; available bytes from the socket handle, if the socket has a code body
;;; continuation, and returns the bytes as a text to it.

(def-structure-method handle-read-event (blocking-socket error-code block-p)
  (cond ((=f error-code network-status-success)
	 (funcall-superior-method blocking-socket error-code block-p)
	 (maybe-fix-socket-status blocking-socket
				  (blocking-socket-g2-socket blocking-socket))
	 (return-network-data-to-socket-continuation-if-any blocking-socket))
	(t (network-stack-error "read" error-code
				blocking-socket))))



;;; We may want to generalize this and move it to socket1 so it can be used by
;;; weblink.
(defun start-listening (port exact-p secure-p)
  (let ((listen-status (c-network-listen
			 use-tcpip-protocol-only
			 port
			 (if exact-p 1 0)
			 g2-product-tag
			 (if secure-p 1 0))))
    (case listen-status
      (#.icp-connection-succeeded-tag
       (let* ((listener-handle
		(ne-get-listener-handle 0))
	      (listener-socket
		(make-blocking-socket)))
	 (setf (socket-handle listener-socket) listener-handle)
	 (register-socket-to-handle listener-socket listener-handle)
	 (let* ((netpath (get-accept-pathname listener-handle))
		(port-string (extract-network-address netpath)))
	   (setf (socket-port listener-socket) (read-number-from-text-string port-string))
	   (reclaim-text-string netpath)
	   (reclaim-text-string port-string))
	 listener-socket))
      (#.icp-noop-network-code-accessed
       (stack-error cached-top-of-stack
		    "DECnet not supported by this product on this platform"))
      (otherwise
       (stack-error cached-top-of-stack
		    "Could not make exact TCP connection")))))


;;; g2-tcp-listen(handle: item-or-value, options: structure) = (item-or-value)
(defun-for-system-procedure g2-tcp-listen ((port integer) (options structure))
  (declare (values item))
  (let* ((exact-p (equal (evaluation-structure-slot
			   options 'exact evaluation-false-value)
			 evaluation-true-value))
	 (secure-p (equal (evaluation-structure-slot
				      options 'secure evaluation-false-value)
				    evaluation-true-value))
	 (certificate (evaluation-structure-slot options 'certificate nil))
	 
	 listener-socket)
    (when (and secure-p (not secure-icp-initialized-p))
      (when certificate (update-server-certificate certificate))
      (set-up-secure-icp))
    (setq listener-socket (start-listening port exact-p secure-p))
    (reclaim-evaluation-structure options)
    (prog1 
	(create-associated-g2-socket listener-socket)
      (update-g2-socket-status (blocking-socket-g2-socket listener-socket)
			       (if secure-p
				   'listening-secure
				   'listening)))))


;;; Accepting a connection on a socket we're listening on

(defun try-network-accept (blocking-socket error-code)
  (let* ((new-socket (make-blocking-socket))
	 (network-return (handle-network-accept-internals
			   blocking-socket new-socket error-code)))
    (cond ((eq network-return t)
	   (let ((g2sock (create-associated-g2-socket new-socket)))
	     (return-value-to-code-body-continuation
	       g2sock	     
	       (blocking-socket-continuation blocking-socket))))
	  ((null network-return)
	   (reclaim-structure new-socket)
	   (network-stack-error "accept new connection"
				(if (socket-handle blocking-socket)
				    (c-network-get-last-error-code
				      (socket-handle blocking-socket))
				    -1)
				blocking-socket))
	  ;;Other possible value is 'would-block -- just do nothing.
	  (t (reclaim-structure new-socket)))))

(def-structure-method handle-network-accept (blocking-socket error-code)
  (cond ((=f error-code network-status-success)
	 (if (and (blocking-socket-continuation blocking-socket)
		  (eq (code-body-continuation-name
			(blocking-socket-continuation blocking-socket))
		      'g2-tcp-accept))
	     (try-network-accept blocking-socket error-code)))
	(t (network-stack-error "accept new connection" error-code
				blocking-socket))))



(defun-for-system-procedure g2-tcp-accept ((handle item) (ret-var symbol))
  (declare (values))
  (let ((socket (internal-socket? handle)))
    (stack-error-if-invalid-socket handle socket)
    (set-blocking-socket-continuation socket 'g2-tcp-accept ret-var)
    (try-network-accept socket network-status-success)))


;;;; ICMP sockets
;;;  Support for ping and traceroute
(def-structure (icmp-socket (:include blocking-socket))
  icmp-data-length)

(def-gensym-c-function c-icmp-open (:fixnum-int "g2ext_icmp_open")
  ((:string host)
   (:string dotted-address)
   (:fixnum-int buffer-size)))

(def-gensym-c-function c-icmp-write (:fixnum-int "g2ext_icmp_write")
  ((:fixnum-int handle)
   (:fixnum-int ttl)
   (:fixnum-int id)
   (:fixnum-int seq)
   (:variable-fill-icp-buffer buffer)
   (:fixnum-int userbuflen)
   (:fixnum-int totalbuflen)))

(def-gensym-c-function c-icmp-read (:fixnum-int "g2ext_icmp_read")
  ((:fixnum-int handle)
   (:variable-fill-icp-buffer buffer)
   (:fixnum-int buflen)
   (:variable-fill-icp-buffer frombuf)
   (:fixnum-int fbuflen)
   (:variable-fill-icp-buffer seqid)))


(defvar ping-seq-id-array
	(make-array 3 :element-type '(unsigned-byte 16)))

(defun-for-system-procedure g2-initiate-ping ((host text) (seq sequence) (options structure))
  (declare (values item))
  (let* ((dotted-addr (obtain-simple-gensym-string-of-quantized-length
			#.(size-of-variable-fill-icp-buffers-in-8-bit-bytes)))
	 (handle (c-icmp-open host dotted-addr
			      #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes)))
	 (ttl (evaluation-structure-slot options 'ttl 0))
	 (seqnum (evaluation-structure-slot options 'seq 0))
	 (id (evaluation-structure-slot options 'id 0)))
    (reclaim-evaluation-structure options)
    (when (<f handle 0)
      (write-stack-error cached-top-of-stack
	(let ((error-string (copy-null-terminated-string-as-text-string dotted-addr)))
	  (tformat "Failed to open ping socket: ~s" error-string)
	  (reclaim-gensym-string dotted-addr)
	  (reclaim-evaluation-sequence seq)
	  (reclaim-text-string error-string))))
    (let ((socket (make-icmp-socket))
	  (buffer (make-variable-fill-icp-buffer))
	  (g2sock (make-transient-item 'g2-socket))
	  (buflen (evaluation-sequence-length seq)))

      (setf (socket-handle socket) handle)
      (register-socket-to-handle socket handle)
      (setf (internal-socket? g2sock) socket)
      (setf (blocking-socket-g2-socket socket) g2sock)
      (setf (socket-host socket) (copy-null-terminated-string-as-text-string dotted-addr))
      (change-slot-value g2sock 'g2-socket-remote-host
			 (copy-text-string (socket-host socket)))
      (loop for i from 0 repeat buflen
	    do (setf (aref-variable-fill-icp-buffer buffer i)
		     (evaluation-sequence-aref seq i)))
      (cond ((< (c-icmp-write
		  handle ttl id seqnum buffer buflen
		  #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))
		0)
	     (update-g2-socket-status g2sock 'icmp-error-status)
	     (write-stack-error cached-top-of-stack
	       (twrite "Failed to send ping request: ")
	       (loop for i from 0
		     as c = (aref-variable-fill-icp-buffer buffer i)
		     until (= c 0)
		     do (twrite-char c))))
	    (t
	     (setf (icmp-data-length socket) buflen)
	     (update-g2-socket-status g2sock 'icmp-waiting-reply)))
      (reclaim-gensym-string dotted-addr)
      (reclaim-evaluation-sequence seq)
      (reclaim-variable-fill-icp-buffer buffer)
      g2sock)))

;;;Values taken from /usr/include/netinet/ip_icmp.h.  Primarily we care about
;;;ICMP_ECHOREPLY and ICMP_TIMXCEED for ping and traceroute.
(defun translate-icmp-code (code)
  (case code
    (0 'ICMP_ECHOREPLY)
    (3 'ICMP_UNREACH)
    (4 'ICMP_SOURCEQUENCH)
    (5 'ICMP_REDIRECT)
    (8 'ICMP_ECHO)
    (9 'ICMP_ROUTERADVERT)
    (10 'ICMP_ROUTERSOLICIT)
    (11 'ICMP_TIMXCEED)
    (12 'ICMP_PARAMPROB)
    (13 'ICMP_TSTAMP)
    (14 'ICMP_TSTAMPREPLY)
    (15 'ICMP_IREQ)
    (16 'ICMP_IREQREPLY)
    (17 'ICMP_MASKREQ)
    (18 'ICMP_MASKREPLY)
    (otherwise 'ICMP_UNKNOWN)))

(def-structure-method handle-read-event (icmp-socket error-code block-p)
  (declare (ignore error-code block-p))
  (let ((handle (socket-handle icmp-socket))
	(buffer (make-variable-fill-icp-buffer))
	(fbuffer (obtain-simple-gensym-string-of-quantized-length
		   #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes))))
    (loop for i below 3 do 
      (setf (byte-vector-16-aref ping-seq-id-array i) 0))
    (loop for typecode = (c-icmp-read
			   handle buffer
			   #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes)
			   fbuffer
			   #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes)
			   ping-seq-id-array)
	  while (>= typecode 0)
	  as host = (twith-output-to-text-string
		      (loop for i from 0
			    as c = (schar fbuffer i)
			    until (eq c #\NULL) do
			(twrite-char c)))
	  as bytes = (loop for i from 0 below (icmp-data-length icmp-socket)
			   as c = (aref-variable-fill-icp-buffer buffer i)
			   collect c using eval-cons)
	  as struct = (allocate-evaluation-structure-inline
			 'TYPE (translate-icmp-code typecode)
			 'HOST (make-evaluation-text-reclaiming-argument host)
			 'BYTES (allocate-evaluation-sequence bytes)
			 'ID (byte-vector-16-aref ping-seq-id-array 0)
			 'SEQ (byte-vector-16-aref ping-seq-id-array 1)
			 'TTL (byte-vector-16-aref ping-seq-id-array 2)) do 
      (if (blocking-socket-continuation icmp-socket)
	  (return-value-to-code-body-continuation
	    struct
	    (blocking-socket-continuation icmp-socket))
	  (gensym-push struct (blocking-socket-partial-data icmp-socket)))
      finally
	    (if (=f typecode ne-error-value)
		(update-g2-socket-status
		  (blocking-socket-g2-socket icmp-socket) 'icmp-error-status)))
    (reclaim-variable-fill-icp-buffer buffer)
    (reclaim-gensym-string fbuffer)))

(def-structure-method handle-network-close (icmp-socket network-error-code)
  (declare (ignore icmp-socket network-error-code)))

(defun-for-system-procedure read-ping-stream ((g2-socket item) (ret-var symbol))
  (declare (values))
  (let ((icmp-socket (internal-socket? g2-socket)))
    (stack-error-if-invalid-socket g2-socket icmp-socket)
    (unless (blocking-socket-continuation icmp-socket)
      (set-blocking-socket-continuation icmp-socket 'g2-read-ping ret-var))
    (if (blocking-socket-partial-data icmp-socket)
	(return-value-to-code-body-continuation
	  (gensym-pop (blocking-socket-partial-data icmp-socket))
	  (blocking-socket-continuation icmp-socket)))))


;;;; MQTT stubs
(defun-for-system-procedure g2-mqtt-log-topic-data (item log-p)
  (let ((r (c-mqtt-log-topic-data 0 (if (eq log-p truth) 1 0))))
    (if (=f r 0)
	evaluation-false-value
	evaluation-true-value)))

(def-gensym-c-function c-mqtt-log-topic-data (:fixnum-int "g2ext_mqtt_log_topic_data")
   ((:fixnum-int handle)
    (:fixnum-int flag)))

(defun-for-system-procedure g2-mqtt-log-packet-data (item log-p)
  (let ((r (c-mqtt-log-packet-data 0 (if (eq log-p truth) 1 0))))
    (if (=f r 0)
	evaluation-false-value
	evaluation-true-value)))

(def-gensym-c-function c-mqtt-log-packet-data (:fixnum-int "g2ext_mqtt_log_packet_data")
   ((:fixnum-int handle)
    (:fixnum-int flag)))

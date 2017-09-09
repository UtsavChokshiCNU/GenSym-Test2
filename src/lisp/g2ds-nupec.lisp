;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module G2DS-NUPEC -- G2 to G2 Data Service Using ICP

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard & Chris Morel



;; jh, 2/27/92.  Split This material from the generic g2ds file, which
;; was getting unwieldy.


;;;; NUPEC Synchronization Execution Code




;;; The following code implements a facility for sending messages between two
;;; G2s to execute a NUPEC synchronization.  This code has been written under a
;;; contract with NUPEC.  The code for the actions which interface users to this
;;; code is in the file nupec-sync-action.

;;; The variable `print-nupec-message-states' controls whether or not FORMAT T
;;; functions are executed which report the ongoing state of a synchronization
;;; execution.

(defparameter print-nupec-message-states nil)





;;;; NUPEC Synchronize Message Design




;;; The above code implements a prototype of the NUPEC Synchronize facility.
;;; The following design describes the full facility, which will has the
;;; additional functionality of sending arbitrarily sized histories, and freezes
;;; the target machine until all reception is complete.

;;; A synchronize operation will consist of several messages sent in order from
;;; the source G2 to a target G2.  The source begins by sending a request to
;;; synchronize to the target, containing a count of the number of variables
;;; which it wishes to send.  The target G2 will have 30 seconds to respond with
;;; a message which tells the source that it is OK to proceed, or else that it
;;; refuses the synchronization attempt.  The source must wait for the
;;; acknowledgement before proceeding with the synchronization.

;;; Once a target G2 has accepted a request to synchronize, the source must
;;; continue sending something at least once every 30 seconds, or the
;;; synchronize times out.  When a timeout on the target occurs, then the target
;;; will attempt to send a message to the source notifying it that the
;;; synchronization has been aborted.  Synchronization messages received after
;;; the abort has been sent will be ignored.

;;; After reception of each message group the target will send a message to the
;;; source notifying it that the message was received.  The source will allow a
;;; limited number of messages to be in the process of being received and
;;; acknowledged.  This will implement flow control.  If the source has waited
;;; for 30 seconds between any acknowledgements, then it will time out and will
;;; attempt to send to the target a message informing it that the
;;; synchronization has been aborted.  Any acknowledgement messages received
;;; after the synchronization has been aborted will be ignored.

;;; When the source has completed sending all data, it will wait for an
;;; acknowledgement of reception of the last of the data.  When the last
;;; acknowledgement has been received, it will send a message informing the
;;; target that the synchronization is complete, and the process is over.






;;;; Code for NUPEC Synchronization




;;; The structure `source-nupec-synchronization' is used to hold the incremental
;;; data structures for a synchronization process in a source G2.

(def-structure (source-nupec-synchronization
		 (:constructor make-source-nupec-synchronization
		  (source-nupec-synchronization-list
		    source-nupec-synchronization-xface
		    source-nupec-synchronization-icp-socket)))
  source-nupec-synchronization-list
  source-nupec-synchronization-xface
  source-nupec-synchronization-icp-socket
  (source-nupec-synchronization-state 'start)
  (source-nupec-synchronization-failure-reason nil)
  (source-nupec-synchronization-last-group-sent 0)
  (source-nupec-synchronization-last-group-acknowledged 0)
  (source-nupec-fixnum-time-of-last-message-received (get-fixnum-time))
  (source-nupec-fixnum-time-of-last-message-sent (get-fixnum-time))
  (source-nupec-history-block-spec nil)
  (source-nupec-progress-object
    (put-up-nupec-synchronization-progress-display)
    :reclaimer delete-frame)
  (source-nupec-total-variable-count 0)
  (source-nupec-variables-sent-so-far 0))



;;; The structure `target-nupec-synchronization' is used to hold the incremental
;;; data structures for a synchronization process in a target G2.

(def-structure (target-nupec-synchronization
		 (:constructor make-target-nupec-synchronization
		  (target-nupec-synchronization-icp-socket
		    target-nupec-synchronization-expected-variable-count
		    target-nupec-synchronization-time-offset)))
  target-nupec-synchronization-icp-socket
  target-nupec-synchronization-expected-variable-count
  target-nupec-synchronization-time-offset
  (target-nupec-synchronization-state nil)
  (target-nupec-synchronization-task nil :reclaimer cancel-task)
  (target-nupec-fixnum-time-of-last-message-received (get-fixnum-time))
  (target-nupec-progress-object
    (put-up-nupec-synchronization-progress-display)
    :reclaimer delete-frame)
  (target-nupec-variables-received-so-far 0))




;;; The special variable `current-source-nupec-synchronization' holds the
;;; source-nupec-synchronization structure which is currently being sent during
;;; a synchronization in the source G2.

;;; The system variable `current-target-nupec-synchronization' holds the
;;; target-nupec-synchronization structure which is currently being received
;;; during a synchronization in the target G2.

(defvar current-source-nupec-synchronization nil)

(def-system-variable current-target-nupec-synchronization int1 nil)




;;; The `nupec-synchronize-variable-or-parameter' is the corresponding object
;;; for a variable or parameter on a remote G2.  Note that the reclaimer has
;;; been given a dummy name, and that a function has been defined for the
;;; reclaimer for the ICP corresponding object reclaimer facilities.

(def-structure (nupec-synchronize-variable-or-parameter
		 (:constructor
		   make-nupec-variable-or-parameter
		   (nupec-synchronize-remote-designation
		     nupec-synchronize-local-variable-or-parameter?
		     nupec-synchronize-collection-time
		     nupec-synchronize-expiration
		     nupec-synchronize-history-length))
		 (:reclaimer reclaim-nupec-synchronize-internal))
  (nupec-synchronize-remote-designation nil :reclaimer reclaim-gensym-tree)
  nupec-synchronize-local-variable-or-parameter?
  (nupec-synchronize-current-value
    nil :reclaimer reclaim-managed-number-or-value)
  nupec-synchronize-collection-time
  nupec-synchronize-expiration
  nupec-synchronize-history-length
  (nupec-synchronize-history-received 0)
  (nupec-synchronize-history? nil))

(defun reclaim-nupec-synchronize-variable-or-parameter (structure)
  (reclaim-nupec-synchronize-internal-macro structure))




;;; The structure `local-nupec-variable' is used to hold a variable or parameter
;;; which is going to have a corresponding object on a remote G2.  The structure
;;; is needed to hold the slot which establishes a map between ports and
;;; corresponding ICP indices.  This structure merely holds the variable and the
;;; map slot.

(def-structure (local-nupec-variable
		 (:constructor make-local-nupec-variable
		  (local-nupec-variable-frame)))
  local-nupec-variable-frame
  (icp-object-map-for-local-nupec-variable nil))




;;; The parameter `nupec-allowable-message-groups-in-progress' holds the number
;;; of message groups that the NUPEC source synchronization process is allowed
;;; to have sent without an acknowledgement from the remote system.  This is the
;;; basic number for flow control.

;;; The parameter `nupec-allowable-variables-per-message-group' contains the
;;; count of the maximum allowable variables within a message group.

;;; The parameter `nupec-allowable-history-values-per-message-group' contains
;;; the count of the maximum allowable history values which can be sent in one
;;; message group.

;;; The parameter `nupec-timeout' contains a fixnum interval of how long
;;; sychronization can be idle from the perspective of either of the machines
;;; before the synchronization times out.

(defparameter nupec-allowable-message-groups-in-progress 5)

(defparameter nupec-allowable-variables-per-message-group 10)

(defparameter nupec-allowable-history-values-per-message-group 100)

(defparameter nupec-fixnum-timeout-interval (fixnum-time-interval 30000))




;;; The function `nupec-synchronize' is the main function called to execute a
;;; synchronization from a source G2.  It takes an eval cons list of variables
;;; and parameters to synchronize, and it takes a G2-to-G2 interface object
;;; connected to the target G2.  This function will send information across the
;;; ICP socket in the G2-to-G2 interface object to perform the synchronization,
;;; and will receive messages to confirm the reception of the synchronization.
;;; This function may execute for an extended period of time (upwards of 10
;;; minutes).  It will call process-icp-sockets and idle-process to send ICP
;;; buffers it has enqueued and to free up the processor while it is waiting for
;;; responses to its messages.  This function will return T if the
;;; synchronization occurred without error and was confirmed on the remote
;;; system.  It will write warning messages to reflect errors and return NIL if
;;; the synchronization did not complete correctly.

;;; The function nupec-synchronize is itself the top level loop for the source
;;; synchronization process.  It starts by creating a source-synchronization
;;; object, initializing it will the list of variables and parameters and the
;;; interface object.  Repeated calls to process-icp-sockets and
;;; perform-work-on-nupec-synchronization are performed until the
;;; source-nupec-synchronziation-state slot is NIL.  When it is NIL, then this
;;; function completes, returning the value of the
;;; source-nupec-synchronization-failure-reason slot after reclaiming the
;;; source-synchronziation structure.  Both process-icp-sockets and
;;; perform-work-on-synchronization return NIL if they want to be called again
;;; as soon as possible.  If both return T, then this function will pause by calling
;;; idle-process before calling these functions again.

(defun-allowing-unwind nupec-synchronize (synchronization-list g2-to-g2-interface-object)
  (loop for variable-cons on synchronization-list
	do
    (setf (car variable-cons)
	  (make-local-nupec-variable (car variable-cons))))
  (let* ((interface-structure? (get-slot-value g2-to-g2-interface-object
					       'g2ds-interface-structure))
	 (socket? (if interface-structure?
		      (g2ds-interface-socket interface-structure?)))
	 (sync-object (make-source-nupec-synchronization
			synchronization-list
			g2-to-g2-interface-object
			socket?))
	 (current-source-nupec-synchronization sync-object)
	 (maximum-time-slice-size icp-socket-processing-time-limit)
	 (time-slice-start-time 0))
    (cond (socket?
	   (loop until (null (source-nupec-synchronization-state sync-object))
		 do
	     ;; (when sleep? (idle-process 5000 idle-time-when-polling))  this was broken.
	     ;; sleep no longer really matters; g2-event-cycle will sleep if there aren't any events.

	     (ne-set-next-timer-event 5000) ;wake up in at most 5 seconds
	     
	     (perform-work-on-nupec-synchronization sync-object)

	     (setq time-slice-start-time (get-fixnum-time))

	     (with-scheduler-disabled
	       (g2-event-cycle-handling-windows-quit)))

	   (let ((failure? (source-nupec-synchronization-failure-reason
			     sync-object)))
	     (when failure?
	       (write-warning-message* 1
		 (twrite-string
		   "NUPEC synchronization failed for the following reason:  ")
		 (twrite-string failure?))
	       (reclaim-text-string failure?))))
	  (t
	   (write-warning-message* 1
	     (tformat
	       "NUPEC synchronization failed because the interface status of ~NF is "
	       g2-to-g2-interface-object)
	     (write-symbol-from-slot
	       (get-slot-value g2-to-g2-interface-object 'interface-status)
	       nil)
	     (twrite-string "."))))
    (reclaim-source-nupec-synchronization sync-object)))






;;;; NUPEC Synchronize ICP Message Type Codes




;;; The ICP message type codes 200-209 are reserved for use by the NUPEC
;;; enhancements code.  The following message types are defined.

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-icp-message-type-code define-nupec-synchronize-variable-or-parameter 200 g2-ds)
(def-icp-message-type-code nupec-synchronize-control-message 201 g2-ds)
(def-icp-message-type-code receive-nupec-synchronize-history-block 202 g2-ds)
(def-icp-message-type-code nupec-synchronize 203 g2-ds)
)






;;;; NUPEC Synchronize ICP Value Writers and Readers


;;; The ICP reader and writer for `nupec-synchronize-datum' are used to send any
;;; kind of datum which could be the value of a G2 variable.



(def-icp-value-writer nupec-synchronize-datum
  (cond ((null nupec-synchronize-datum)
	 (write-icp-byte nupec-synchronize-datum-null-type))
	((symbolp nupec-synchronize-datum)
	 (write-icp-byte nupec-synchronize-datum-symbol-type)
	 (write-icp-text-string (symbol-name-text-string nupec-synchronize-datum)))
	((typep nupec-synchronize-datum 'fixnum)
	 (write-icp-byte nupec-synchronize-datum-integer-type)
	 (write-icp-integer nupec-synchronize-datum))
	((gensym-float-p nupec-synchronize-datum)
	 (write-icp-byte nupec-synchronize-datum-float-type)
	 (write-icp-double-float-1 nupec-synchronize-datum))
	((text-string-p nupec-synchronize-datum)
	 (write-icp-byte nupec-synchronize-datum-text-type)
	 (write-icp-text-string nupec-synchronize-datum))
	(t
	 #+development
	 (format t "~%NUPEC synchronize datum trying to write ~a."
		 nupec-synchronize-datum)
	 (write-icp-byte nupec-synchronize-datum-null-type))))

(def-icp-value-reader nupec-synchronize-datum
  (let ((result nil))
    (fixnum-case (read-icp-byte)
      ((#.nupec-synchronize-datum-null-type)
       nil)
      ((#.nupec-synchronize-datum-symbol-type)
       (setq result (intern-text-string (read-icp-text-string))))
      ((#.nupec-synchronize-datum-integer-type)
       (setq result (read-icp-integer)))
      ((#.nupec-synchronize-datum-float-type)
       (setq result (read-icp-double-float-1)))
      ((#.nupec-synchronize-datum-text-type)
       (setq result (read-icp-text-string))))
    result))




;;; The ICP value type nupec-designation is used to deliver designations.  It
;;; returns a designation made of gensym-conses.



(def-icp-value-writer nupec-designation
  (cond ((null nupec-designation)
	 (write-icp-byte nupec-designation-null-type-tag))
	((consp nupec-designation)
	 (write-icp-byte nupec-designation-cons-type-tag)
	 (write-icp-nupec-designation (car nupec-designation))
	 (write-icp-nupec-designation (cdr nupec-designation)))
	((symbolp nupec-designation)
	 (write-icp-byte nupec-designation-symbol-type-tag)
	 (write-icp-text-string (symbol-name-text-string nupec-designation)))
	;; Otherwise, write NIL, we can't write it.
	(t
	 #+development
	 (format t "NUPEC designation cant write ~a, writing NIL instead."
		 nupec-designation)
	 (write-icp-byte nupec-designation-null-type-tag))))

(defun-void reclaim-nupec-designation (nupec-designation)
  (cond
    ((consp nupec-designation)
     (reclaim-nupec-designation (car nupec-designation))
     (reclaim-nupec-designation (cdr nupec-designation))
     (reclaim-gensym-cons nupec-designation))
    ((text-string-p nupec-designation)
     (reclaim-text-string nupec-designation))))

(def-icp-value-reader nupec-designation
  (let ((result nil))
    (fixnum-case (read-icp-byte)
      ((#.nupec-designation-null-type-tag)
       nil)
      ((#.nupec-designation-symbol-type-tag)
       (setq result (intern-text-string (read-icp-text-string))))
      ((#.nupec-designation-cons-type-tag)
       (setq result
	     (gensym-cons
	       (read-icp-nupec-designation)
	       (read-icp-nupec-designation)))))
    result))






;;;; NUPEC Synchronize Corresponding Variable Objects




;;; The corresponding object type `nupec-synchronize-variable-or-parameter' is
;;; used to establish a remote structure corresponding to the basic data which
;;; is transmitted about a variable or parameter when performing a synchronize.
;;; This will be passed as an argument to the nupec-synchronize-history-block
;;; message, which will receive chunks of history data.

(def-icp-object-type nupec-synchronize-variable-or-parameter
		     (standard-icp-object-index-space
		       (icp-object-map-for-local-nupec-variable
			 nupec-synchronize-variable-or-parameter)
		       reclaim-nupec-synchronize-variable-or-parameter)
  (let* ((variable-or-parameter
	   (local-nupec-variable-frame
	     nupec-synchronize-variable-or-parameter))
	 (designation (generate-designation-for-block variable-or-parameter))
	 (history?
	   (variable-or-parameter-stored-histories? variable-or-parameter))
	 (history-length
	   (if history?
	       (get-total-cascaded-ring-buffer-length history?)
	       0))
	 (collection-gensym-time nil))
    (with-temporary-gensym-float-creation
	nupec-synchronize-variable-or-parameter
      (setq collection-gensym-time
	    (convert-unix-time-to-gensym-time
	      (managed-float-value
		(time-of-most-recent-value variable-or-parameter)))))
    (send-icp-define-nupec-synchronize-variable-or-parameter
      corresponding-icp-object-index
      designation
      (extract-cached-number-or-value
	(current-value-of-variable-or-parameter
	  variable-or-parameter))
      collection-gensym-time
      ;; Note that expiration, if a time-stamp, is already a gensym-time.
      (if (variable-p variable-or-parameter)
	  (let ((exp? (expiration-time-of-current-value variable-or-parameter)))
	    (if (and (typep exp? 'fixnum) (=f exp? *some-time-ago*))
		'no-value
		exp?))
	  0)
      history-length)
    (reclaim-eval-tree designation)))




;;; The ICP mesage type `define-nupec-synchronize-variable-or-parameter' is used
;;; to define a corresponding object for a variable or parameter on a target G2.
;;; The code below defines what happens on the receiving end of such a link.  It
;;; creates an instance of the nupec-synchronize-variable-or-parameter
;;; structure and fills it with the appropriate slots.  Note that if the source
;;; G2 could make no designation, then the target side should quietly eat the
;;; messages for this object.  In this case the remote-designation,
;;; local-variable-or-parameter, and history? slots of the new structure will be
;;; NIL.  If no local variable or parameter can be found, then the messages for
;;; this object should be eaten, but a message should be issued locally warning
;;; of the loss.  In this case the local v-or-p and the history? slots will be
;;; NIL.  If there is no history coming, or if the local variable or parameter
;;; lacks a history spec, then the history slot will be NIL, and any history on
;;; the way should be quietly read and discarded.

(def-icp-message-type define-nupec-synchronize-variable-or-parameter
		      (corresponding-icp-object-index
			(nupec-designation remote-designation)
			(nupec-synchronize-datum current-value)
			(integer collection-time)
			(nupec-synchronize-datum expiration)
			(unsigned-integer history-length))
  (let ((*current-computation-frame* inference-engine-parameters)
	(time-offset (target-nupec-synchronization-time-offset
		       current-target-nupec-synchronization)))
    (let* ((local-variable-or-parameter?
	     (if remote-designation
		 (evaluate-designation remote-designation nil)))
	   (new-sync-object
	     (make-nupec-variable-or-parameter
	       remote-designation
	       local-variable-or-parameter?
	       (+f time-offset collection-time)
	       (if (typep expiration 'fixnum)
		   (+f time-offset expiration)
		   (if (eq expiration 'no-value)
		       *some-time-ago*
		       expiration))
	       history-length)))
      ;; Reject things that are not variable-or-parameters.
      (when (and local-variable-or-parameter?
		 (or (temporary-constant-p local-variable-or-parameter?)
		     (not (variable-or-parameter-p
			    local-variable-or-parameter?))))
	(setf (nupec-synchronize-local-variable-or-parameter? new-sync-object)
	      nil)
	(reclaim-if-temporary-constant local-variable-or-parameter?))
      ;; Permanently store the value into the structure.
      (store-managed-number-or-value
	(nupec-synchronize-current-value new-sync-object)
	current-value)
      (when (text-string-p current-value)
	(reclaim-text-string current-value))
      ;; If there is a history on the way and this variable or parameter has a
      ;; history keeping spec, create a history object.  If there is no history
      ;; object stored, then any history which has been sent will be read, but
      ;; is discarded.  This correctly covers the case where the sender has
      ;; history, but the receiver doesn't want it.
      (when (/=f history-length 0)
	(let ((spec? (if local-variable-or-parameter?
			 (variable-or-parameter-history-specification?
			   local-variable-or-parameter?)
			 nil)))
	  (when spec?
	    (let ((history (make-or-reformat-cascaded-ring-buffer
			     nil
			     (second spec?)
			     (third spec?)
			     (fourth spec?))))
	      (setf (cascaded-ring-buffers history)
		    (history-list (get-or-make-smallest-history-ring-buffer)))
	      (setf (nupec-synchronize-history? new-sync-object)
		    history)))))
      ;; Finally, make the correspondence.
      (store-corresponding-icp-object
	corresponding-icp-object-index
	new-sync-object))))




;;; The ICP message type `nupec-synchronize' is sent from a source to a target
;;; G2 to request a synchronization.  This handler should determine if it is
;;; appropriate to to receive a synchronization, and send back START-ACCEPTED or
;;; START-REJECTED as appropriate.  If the synchronization is accepted, the
;;; system should be paused during the synchronization.  The arguments to this
;;; message are a count of the number of variables or parameters that will be
;;; sychronized, and the decoded calendar time that represents zero in the
;;; relative timestamps to be sent across the link.

(defun-allowing-unwind write-message-group-for-nupec-synchronize
		       (reject-reason?)
  (writing-icp-message-group ((icp-output-port current-icp-socket))
    (send-icp-nupec-synchronize-control-message
      'start-rejected reject-reason?)
    (reclaim-text-string reject-reason?)))

(def-icp-message-type nupec-synchronize
		      ((unsigned-integer variable-count)
		       (unsigned-integer year)
		       (unsigned-integer month)
		       (unsigned-integer day)
		       (unsigned-integer hour)
		       (unsigned-integer minute)
		       (unsigned-integer second))
  (when print-nupec-message-states
    (format t "~%Starting Synchronization!"))
    (let ((reject-reason? (reason-to-reject-nupec-synchronization?))
	  (offset-for-remote-gensym-time
	    (encode-gensym-time second minute hour day month year)))
      (cond (reject-reason?
	     (write-message-group-for-nupec-synchronize
	       reject-reason?))
	    (t
	     (setq current-target-nupec-synchronization
		   (make-target-nupec-synchronization
		     current-icp-socket
		     variable-count
		     offset-for-remote-gensym-time))
	     (with-current-scheduling ((target-nupec-synchronization-task
					 current-target-nupec-synchronization)
				       1)
	       (receive-nupec-synchronize-task))))))




;;; The function `receive-nupec-synchronize' becomes the top level loop during
;;; the reception of a NUPEC synchronize.

(defun-simple receive-nupec-synchronize-task ()
  (receive-nupec-synchronize))

(defun-allowing-unwind receive-nupec-synchronize ()
  (when current-target-nupec-synchronization
    (system-pause)
    (writing-icp-message-group ((icp-output-port
				  (target-nupec-synchronization-icp-socket
				    current-target-nupec-synchronization)))
      (send-icp-nupec-synchronize-control-message 'start-accepted 0))
    (loop with time-slice-start-time = 0
	  while current-target-nupec-synchronization
	  do (with-temporary-gensym-float-creation receive-nupec-synchronize
	       (check-for-target-nupec-timeout)
	       (setq time-slice-start-time (get-fixnum-time))
	       (ne-set-next-timer-event 5000) ;wake up in at most 5 seconds
	       (with-scheduler-disabled
		 (g2-event-cycle-handling-windows-quit))))))
  




;;; The function `check-for-target-nupec-timeout' is used to determine if a
;;; target G2 has timed out, and to take actions if a timeout has happened.

(defun-allowing-unwind check-for-target-nupec-timeout ()
  (let ((wait-time (fixnum-time-difference
		     (get-fixnum-time)
		     (target-nupec-fixnum-time-of-last-message-received
		       current-target-nupec-synchronization))))
    (when (>=f wait-time nupec-fixnum-timeout-interval )
      (let ((message
	      (tformat-text-string
		"Reception of NUPEC synchronization timed out after a delay ~
                 of ~a seconds."
		(/ (coerce-to-gensym-float wait-time)
		   (coerce-to-gensym-float fixnum-time-units-per-second)))))
	(writing-icp-message-group ((icp-output-port
				      (target-nupec-synchronization-icp-socket
					current-target-nupec-synchronization)))
	  (send-icp-nupec-synchronize-control-message
	    'abort-synchronize
	    message))
	(abort-target-nupec-synchronization message)
	(reclaim-text-string message)))))




;;; The function `abort-target-nupec-synchronization' is called to abort the
;;; reception of an ongoing NUPEC synchronization.

(defun abort-target-nupec-synchronization (abort-reason)
  (reclaim-target-nupec-synchronization
    current-target-nupec-synchronization)
  (setq current-target-nupec-synchronization nil)
  (system-resume)
  (loop for graph being each class-instance of 'graph
	do
    (when (active-p graph)
      (funcall-method
	'deactivate-and-propagate
	graph
	nil)
      (funcall-method
	'activate-if-possible-and-propagate
	graph)))
  (warning-message 1
    "Reception of a NUPEC synchronization has been aborted for the following ~
     reason: ~a"
    abort-reason))




;;; The ICP message type `nupec-synchronize-control-message' is used to send
;;; control and status messages back and forth between two G2s currently being
;;; synchronized.  This message will take two arguments, the first being a
;;; symbol reflecting which kind of control message is being sent, the second
;;; being a datum which varies from message to message.
;;;
;;; The following are the possible values for the first argument, control
;;; message type:
;;;
;;;   START-ACCEPTED:  This message is sent from a target G2 to a source G2 to
;;;   confirm that it is ready to receive a synchronization.  The second
;;;   argument is ignored.  The handler should set the state of the sync source
;;;   object to SENDING.
;;;
;;;   START-REJECTED:  This message is sent from a target G2 to source G2 to
;;;   reject a request for a synchronize.  The second argument is a string
;;;   describing the reason for the rejection.  The handler for this message
;;;   should print a message containing the rejection reason, and set the
;;;   source synchronization state to NIL.
;;;
;;;   GROUP-SENT:  This message is sent from a source G2 to a target G2 as the
;;;   last message in a message group.  The second argument is the number of
;;;   this message group.  A target G2 receiving this message should respond
;;;   immediately with a GROUP-RECEIVED message.  This acknowledgement is used
;;;   to implement flow control.
;;;
;;;   GROUP-RECEIVED:  This message is sent from a target G2 to a source G2 to
;;;   acknowledge reception of a GROUP-SENT message.  The second argument is the
;;;   identifying number of the group just received.  The handler of this
;;;   message should set its last group received slot to the given group number.
;;;   If group number is the same as the number of the last group sent, and if
;;;   the synchronization list is NIL, then the synchronzation has succeeded,
;;;   the success slot should be set, and the END-OF-SYNCHRONIZATION message
;;;   should be sent.
;;;
;;;   END-OF-SYNCHRONIZATION:  This message is sent from a source G2 to a target
;;;   G2 to inform the target that all data has been sent and that the
;;;   synchronization is complete.  This message will only be sent after the
;;;   target has acknowledged reception of the last history block of the
;;;   synchronization operation.  The second argument is ignored.  The handler
;;;   for this message should resume operation of this G2, delete any data
;;;   structures allocated to handle the synchronization, and send back the end
;;;   confirmed message.
;;;
;;;   END-OF-SYNCHRONIZATION-CONFIRMED-THANK-YOU:  This message is sent from a
;;;   from either a source or a target G2 to confirm the end of a
;;;   synchronization operation, and to confirm that all data structures related
;;;   to the synchronization have been reclaimed.  This message is sent as a
;;;   result of the END-OF-SYNCHRONIZATION message or the ABORT-SYNCHRONIZE
;;;   message being received.  The second argument is ignored.
;;;
;;;   ABORT-SYNCHRONIZE:  The message is sent from either a source or a target
;;;   G2 to prematurely abort a synchronization process which is under way.
;;;   This could occur as a result of a timeout occurring on either side, or as
;;;   a result of some user abort of the process.  The second argument is a
;;;   string giving the reason for the abort.


(defun-allowing-unwind write-group-sent-for-nupec-synchronize-control-message
		       (extra-argument)
     (writing-icp-message-group ((icp-output-port current-icp-socket))
       (send-icp-nupec-synchronize-control-message
	 'group-received
	 extra-argument)))

(defun-allowing-unwind write-end-of-synch-for-nupec-synchronize-control-message 
		       ()
  (writing-icp-message-group ((icp-output-port current-icp-socket))
    (send-icp-nupec-synchronize-control-message
      'end-of-synchronization 0)))

(defun-allowing-unwind write-confirmed-for-nupec-synchronize-control-message
		       ()
  (writing-icp-message-group ((icp-output-port current-icp-socket))
    (send-icp-nupec-synchronize-control-message
      'end-of-synchronization-confirmed-thank-you 0)))

(def-icp-message-type nupec-synchronize-control-message
		      ((symbol control-message)
		       (nupec-synchronize-datum extra-argument))
  (case control-message
    ((start-accepted)
     (setf (source-nupec-synchronization-state
	     current-source-nupec-synchronization)
	   'sending)
     (setf (source-nupec-fixnum-time-of-last-message-received
	     current-source-nupec-synchronization)
	   (get-fixnum-time))
     (when print-nupec-message-states
       (format *terminal-io* "~%Sending...")))
    ((start-rejected)
     (write-warning-message* 1
       (tformat "Synchronization request was rejected by the remote G2.  ~
                 The following reason was given:  ~a"
		extra-argument))
     (reclaim-text-string extra-argument)
     (setf (source-nupec-synchronization-state
	     current-source-nupec-synchronization)
	   nil)
     (setf (source-nupec-fixnum-time-of-last-message-received
	     current-source-nupec-synchronization)
	   (get-fixnum-time))
     (when print-nupec-message-states
       (format *terminal-io* "~%Rejected...")))
    ((group-sent)
     (write-group-sent-for-nupec-synchronize-control-message
       extra-argument)
     (setf (target-nupec-fixnum-time-of-last-message-received
	     current-target-nupec-synchronization)
	   (get-fixnum-time))
     (with-temporary-gensym-float-creation nupec-synchronize-control-message
       (change-slot-value
	 (target-nupec-progress-object current-target-nupec-synchronization)
	 'progress-through-nupec-synchronization
	 (floor (*e (/e (coerce-to-gensym-float
			  (target-nupec-variables-received-so-far
			    current-target-nupec-synchronization))
			(coerce-to-gensym-float
			  (target-nupec-synchronization-expected-variable-count
			    current-target-nupec-synchronization)))
		    1000.0))))
     (when print-nupec-message-states
       (format *terminal-io* "~%Group ~a received..." extra-argument)))
    ((group-received)
     (setf (source-nupec-synchronization-last-group-acknowledged
	     current-source-nupec-synchronization)
	   extra-argument)
     (when print-nupec-message-states
       (format *terminal-io* "~%Group ~a received..." extra-argument))
     (when (and (=f extra-argument
		    (source-nupec-synchronization-last-group-sent
		      current-source-nupec-synchronization))
		(null (source-nupec-synchronization-list
			current-source-nupec-synchronization)))
       (setf (source-nupec-synchronization-failure-reason
	       current-source-nupec-synchronization)
	     nil)
       (setf (source-nupec-synchronization-state
	       current-source-nupec-synchronization)
	     'wait-for-final-acknowledgement)

       (write-end-of-synch-for-nupec-synchronize-control-message)

       (when print-nupec-message-states
	 (format *terminal-io* "~%Waiting for final ack...")))
     (setf (source-nupec-fixnum-time-of-last-message-received
	     current-source-nupec-synchronization)
	   (get-fixnum-time)))
    ((end-of-synchronization)
     (reclaim-target-nupec-synchronization
       current-target-nupec-synchronization)
     (setq current-target-nupec-synchronization nil)
     (system-resume)
     (loop for graph being each class-instance of 'graph
	   do
       (when (active-p graph)
	 (funcall-method
	   'deactivate-and-propagate
	   graph
	   nil)
	 (funcall-method
	   'activate-if-possible-and-propagate
	   graph)))
     (invoke-rules-for-nupec-synchronization-chaining)

     (write-confirmed-for-nupec-synchronize-control-message)

     (when print-nupec-message-states
       (format *terminal-io* "~%End received.")))
    ((end-of-synchronization-confirmed-thank-you)
     (setf (source-nupec-synchronization-state
	     current-source-nupec-synchronization)
	   nil)
     (when print-nupec-message-states
       (format *terminal-io* "~%End confirmed.")))
    ((abort-synchronize)
     (cond (current-target-nupec-synchronization
	    (abort-target-nupec-synchronization extra-argument)
	    (reclaim-text-string extra-argument))
	   (current-source-nupec-synchronization
	    (setf (source-nupec-synchronization-state
		    current-source-nupec-synchronization)
		  nil)
	    (setf (source-nupec-synchronization-failure-reason
		    current-source-nupec-synchronization)
		  extra-argument))
	   (t
	    (reclaim-text-string extra-argument)))) ))




;;; The function `reason-to-reject-nupec-synchronization?' should check to see
;;; if there is any reason to reject a request for synchronization.  If no
;;; reason can be found, then this function will return NIL and the request
;;; should be accepted.  If a reason is found, then this function should return
;;; a text string stating why it should reject.  The text string should be
;;; reclaimed by the caller of this function.

(defun reason-to-reject-nupec-synchronization? ()
  (cond ((null system-is-running)
	 (copy-constant-wide-string #w"The knowledge base is not running."))
	(current-target-nupec-synchronization
	 (copy-constant-wide-string #w"A synchronization is currently executing."))
	(t nil)))




;;; The ICP value type `nupec-history-block' is used to transmit chunks of
;;; history from one G2 to another.  It would be better if we could write
;;; readers and writers for history values and time stamps directly into the
;;; body of the receive-nupec-synchronize-history-block message type, but that
;;; is not within ICP at the moment, and so we must suffer through the extra
;;; copy operation.  The argument to the reader must pass the number of history
;;; values that should be printed, an active element index into a cascaded ring
;;; buffer, and the cascaded ring buffer itself.  If the number of values to
;;; send is zero, then the second two list elements may be omitted.  These will
;;; be given in a list.  The caller of this function will be responsible for
;;; reclaiming the list and the active element index.

(def-icp-value-writer nupec-history-block
  (gensym-dstruct-bind ((values-to-send element-index history-buffer)
		       nupec-history-block)
    (write-icp-unsigned-integer values-to-send)
    (loop repeat values-to-send
	  do
      (write-icp-nupec-synchronize-datum
	(get-history-value-for-cascaded-ring-buffer
	  history-buffer element-index))

; Version 3.0 time-stamp writer.
;      (write-icp-integer
;        (+f gensym-time-at-start
;            (get-history-time-for-cascaded-ring-buffer
;              history-buffer
;              element-index)))

      (with-temporary-gensym-float-creation nupec-history-block
        (let* ((history-g2-time
		 (get-history-g2-time history-buffer (cdr element-index)))
	       (history-gensym-time
		 (convert-unix-time-to-gensym-time history-g2-time)))
	  ;; Only sends the fixnum portion of the time.  Does not handled
	  ;; subsecond part of the time-stamp.
	  (write-icp-integer history-gensym-time)))
      (increment-active-element-index-for-cascaded-ring-buffer
	element-index history-buffer))))




;;; The reader for the ICP value type `nupec-history-block' reads a set of
;;; history values from the incoming ICP stream, and returns them as a gensym
;;; cons whose car is the count of history values, and if the count is not zero,
;;; whose cdr is a managed-array of values.  The managed array will be twice as
;;; long as the number of history values sent.  Note that for now, this managed
;;; array will contain temporary floats, and so must be used with the scope of a
;;; most tightly bound with-temporary wrapper.  This may have to be changed, but
;;; would be less efficient.

(defun-void reclaim-nupec-history-block (nupec-history-block)
  (reclaim-if-managed-array (cdr nupec-history-block))
  (reclaim-gensym-cons nupec-history-block))

(def-icp-value-reader nupec-history-block
  (let* ((history-length (read-icp-unsigned-integer))
	 (array-size (*f history-length 2))
	 (array nil))
    (declare (type fixnum history-length array-size))
    (when (/=f history-length 0)
      (setq array (allocate-managed-array array-size t))
      (loop for value-index from 0 below array-size by 2
	    do
	(setf (managed-svref array value-index)
	      (read-icp-nupec-synchronize-datum))
	(setf (managed-svref array (+f value-index 1))
	      (read-icp-integer))))
    (gensym-cons history-length array)))




;;; The ICP message type `receive-nupec-synchronize-history-block' is used to
;;; send blocks of history values from a source G2 to a target G2.  A
;;; corresponding object, a count of the history values in this block, and then
;;; the data for the history values and time stamps.  After this block is
;;; received (note that the history block itself may be empty), check if the
;;; received-history-count is equal to the history length slot of the
;;; corresponding object.  If so, then install the values into the local
;;; variable.  The remote side will send a message to reclaim the local
;;; corresponding object in a moment.

(def-icp-message-type receive-nupec-synchronize-history-block
		      ((nupec-synchronize-variable-or-parameter v-or-p)
		       (nupec-history-block history-block))
  (let ((history-values (car history-block))
	(history-array? (cdr history-block))
	(history? (nupec-synchronize-history? v-or-p))
	(history-received (nupec-synchronize-history-received v-or-p))
	(time-offset (target-nupec-synchronization-time-offset
		       current-target-nupec-synchronization)))
    (declare (type fixnum history-received history-values))
    ;; Install the history buffer, if the variable has a history.
    (when history-array?
      (loop with ring-buffer = (if history? 
				   (car (cascaded-ring-buffers history?)))
	    with history-base-time = nil
	    initially
	      (when history?
		(with-temporary-gensym-float-creation
		    receive-nupec-synchronize-history-block
		  (setq history-base-time
			(allocate-managed-float
			  (ffloore-first
			    (managed-float-value (clock-get current-g2-time)))))
		  (setf (cascaded-ring-buffer-base-time? history?)
			history-base-time)))
	    for index from 0 below (*f history-values 2) by 2
	    for value = (managed-svref history-array? index)
	    for history-gensym-time =
	       (managed-svref history-array? (+f index 1))
	    do
	(when history?
; Version 3.0.
;          (store-new-element-in-history-ring-buffer
;            ring-buffer 'expand-history-ring-buffer
;            value
;            (-f (+f (managed-svref history-array? (+f index 1))
;                    time-offset)
;                gensym-time-at-start))

	  ;; Note that the LOOP iterates over the history times and uses
	  ;; gensym-floats (unix times) in its computation.  It is not entering
	  ;; and re-entering a temporary-area because the function
	  ;; receive-nupec-synchronize, which handles reception of the history,
	  ;; is already in a temporary-float area.  - cpm, 7/13/94
	  (store-new-element-in-history-ring-buffer
	    ring-buffer 'expand-history-ring-buffer
	    value
	    ;; Only saving fixnum times, not subsecond times.
	    (floore-first
	      (-e (convert-gensym-time-to-unix-time
		    (+f history-gensym-time time-offset))
		  (managed-float-value history-base-time)))))
	(when (text-string-p value)
	  (reclaim-text-string value)))
      (incff history-received history-values)
      (setf (nupec-synchronize-history-received v-or-p) history-received)
      (reclaim-managed-array history-array?))
    ;; If all history has been received, then install the stuff into the
    ;; variable.
    (when (=f history-received (nupec-synchronize-history-length v-or-p))
      (let ((frame? (nupec-synchronize-local-variable-or-parameter?
		      v-or-p)))
	(if (null frame?)
	    (write-warning-message 1
	      (tformat
		"Reception of a NUPEC Synchronize could find no local ~
                 variable or parameter for the designation ")
	      (print-designation (nupec-synchronize-remote-designation
				   v-or-p)))
	    (progn
	      (store-managed-number-or-value
		(current-value-of-variable-or-parameter frame?)
		(extract-cached-number-or-value
		  (nupec-synchronize-current-value v-or-p)))
	      ;; The collection time is sent in gensym-time format, even though,
	      ;; in version 4.0, it is stored as a g2-time.
	      (with-temporary-gensym-float-creation
		  receive-nupec-synchronize-history-block		  
		(setf (time-of-most-recent-value frame?)
		      (allocate-managed-float
			(convert-gensym-time-to-unix-time
			  (nupec-synchronize-collection-time v-or-p)))))
	      (setf (expiration-time-of-current-value frame?)
		    (nupec-synchronize-expiration v-or-p))
	      (when history?
		(let ((old-history? (variable-or-parameter-stored-histories?
				      frame?)))
		  (when old-history?
		    (reclaim-history-buffer old-history?))
		  (setf (variable-or-parameter-stored-histories? frame?)
			history?)))))))))






;;;; NUPEC Synchronize Source Execution




;;; The function `perform-work-on-nupec-synchronization' is the function which
;;; does all work for the source synchronization side.  It takes a
;;; synchronization object and possibly performs some work on that object.  If
;;; any work is actually done, then this function will return NIL, if no work
;;; has been done and this function thinks it's OK to idle the process for a
;;; small amount of time then this function returns T.  This function writes at
;;; most one message group per time that it is called.

(defun-allowing-unwind perform-work-on-nupec-synchronization (sync-object)
  (let ((state (source-nupec-synchronization-state sync-object))
	(icp-socket (source-nupec-synchronization-icp-socket sync-object)))
    ;; Check for timeout.
    (when (>f (fixnum-time-difference
		(get-fixnum-time)
		(source-nupec-fixnum-time-of-last-message-received
		  sync-object))
	      nupec-fixnum-timeout-interval)
      (let ((message
	      (tformat-text-string
		"NUPEC synchronization source timed out after waiting ~a ~
                 seconds without any response messages."
		(/e (coerce-to-gensym-float
		      (fixnum-time-difference
			(get-fixnum-time)
			(source-nupec-fixnum-time-of-last-message-received
			  sync-object)))
		    (coerce-to-gensym-float fixnum-time-units-per-second)))))
	;; Send notification of synchronization-abort.
	(writing-icp-message-group ((icp-output-port
				      (source-nupec-synchronization-icp-socket
					sync-object)))
	  (send-icp-nupec-synchronize-control-message
	    'abort-synchronize
	    message))
	(setf (source-nupec-synchronization-failure-reason sync-object)
	      message)
	(setf (source-nupec-synchronization-state sync-object) nil)
	(return-from perform-work-on-nupec-synchronization nil)))
    (case state
      ;; At START this is the very first call to this function.
      ((start)
       ;; Send request for synchronization to remote G2.
       (multiple-value-bind (second minute hour day month year)
	   (decode-gensym-time 0)
	 (writing-icp-message-group ((icp-output-port icp-socket))
	   (send-icp-nupec-synchronize
	     (length (source-nupec-synchronization-list sync-object))
	     year month day hour minute second)))
       (setf (source-nupec-synchronization-state sync-object)
	     'wait-for-start-acknowledgement)
       nil)
      ;; At WAIT-FOR-START-CONFIRMATION this process has not yet received a
      ;; confirmation from the remote G2 that it will receive this
      ;; synchronization.  The message handler for the
      ;; NUPEC-synchronization-control message will set this state to SENDING
      ;; when it receives confirmation.
      ((wait-for-start-acknowledgement)
       t)
      ;; The state SENDING means that the system is currently in the process of
      ;; sending.  This code may send one message group, and must obey the
      ;; parameters controlling the number of outstanding message groups as well
      ;; the the maximum variable and history value counts per message group.
      ((sending)
       (if (>=f (-f (source-nupec-synchronization-last-group-sent
		      sync-object)
		    (source-nupec-synchronization-last-group-acknowledged
		      sync-object))
		nupec-allowable-message-groups-in-progress)
	   t
	   (progn
	     (send-nupec-source-variables sync-object icp-socket)
	     (when (null (source-nupec-synchronization-list sync-object))
	       (setf (source-nupec-synchronization-state sync-object)
		     `wait-for-send-acknowledgement))
	     nil)))
      ((wait-for-send-acknowledgement)
       t)
      ((wait-for-final-acknowledgement)
       t))))




;;; The function `send-nupec-source-variables' is called to perform the work of
;;; sending one message group containing a set of variables and history blocks for
;;; those variables.  It has already been verified that there is an open window to
;;; send this message group.

(defun-allowing-unwind send-nupec-source-variables (sync-object icp-socket)
  (writing-icp-message-group ((icp-output-port icp-socket))
    (loop with variable-count = 0
	  with history-count = 0
	  for variable-cons = (source-nupec-synchronization-list sync-object)
	  until (or (null variable-cons)
		    (>=f variable-count
			 nupec-allowable-variables-per-message-group)
		    (>=f history-count
			 nupec-allowable-history-values-per-message-group))
	  for local-nupec-variable = (car variable-cons)
	  for variable = (local-nupec-variable-frame local-nupec-variable)
	  for history-block-spec = (source-nupec-history-block-spec sync-object)
	  for history? = (variable-or-parameter-stored-histories? variable)
	  do
      (when (null history-block-spec)
	(let ((history-length
		(if history?
		    (get-total-cascaded-ring-buffer-length history?)
		    0)))
	  (setq history-block-spec
		(if (=f history-length 0)
		    (eval-list 0 0)
		    (eval-list
		      history-length 0
		      (get-oldest-active-element-index-for-cascaded-ring-buffer
			history?)
		      history?)))))
      (let ((history-values-to-send
	      (minf (car history-block-spec)
		    (-f nupec-allowable-history-values-per-message-group
			history-count))))
	(setf (second history-block-spec) history-values-to-send)
	(decff (first history-block-spec) history-values-to-send)
	(incff history-count history-values-to-send)
	(incff variable-count)
	(send-icp-receive-nupec-synchronize-history-block
	  local-nupec-variable
	  (cdr history-block-spec))
	(when (=f (car history-block-spec) 0)
	  (when (third history-block-spec)
	    (reclaim-element-index-for-cascaded-ring-buffer
	      (third history-block-spec)))
	  (reclaim-eval-list history-block-spec)
	  (setq history-block-spec nil)
	  (setf (source-nupec-synchronization-list sync-object)
		(cdr variable-cons))
	  (reclaim-eval-cons variable-cons)
	  (reclaim-icp-object-map-for-nupec-synchronize-variable-or-parameter
	    local-nupec-variable)
	  (reclaim-local-nupec-variable local-nupec-variable))
	(setf (source-nupec-history-block-spec sync-object) history-block-spec)))
    ;; Send a message group number.
    (let ((group-number
	    (+f (source-nupec-synchronization-last-group-sent sync-object) 1)))
      (setf (source-nupec-synchronization-last-group-sent sync-object) group-number)
      (send-icp-nupec-synchronize-control-message 'group-sent group-number)
      (when print-nupec-message-states
	(format *terminal-io* "~%Group ~a sent..." group-number)))))




;;;; Meter for Progress Reporting



(def-class (nupec-synchronization-progress entity)
  (progress-through-nupec-synchronization
    0 system do-not-save vector-slot not-user-editable
    (type nupec-synchronization-progress-display-value)))

;; Note that the progress number should vary from 0 through 1000 to reflect 0.0
;; through 100.0 percent completed.

(def-slot-value-writer nupec-synchronization-progress-display-value (value)
  (with-temporary-gensym-float-creation nupec-sync-progress
    (tformat "~A %" (/ value 10.0))))

(defun put-up-nupec-synchronization-progress-display ()
  (let* ((nupec-synchronization-progress
	   (make-entity 'nupec-synchronization-progress)))
    (loop for workstation in workstations-in-service
	  when (eq (workstation-login-state workstation) 'logged-in)
	  do (for-workstation (workstation)	; binds current-workstation-detail-pane
	       (put-up-attributes-table
		 nupec-synchronization-progress 230 100
		 '(progress-through-nupec-synchronization))))
    nupec-synchronization-progress))


;; This is intended to parallel the progress through file facility as much
;; as possible.  Notice that the magic numbers (230 and 100) are used for
;; the x and y positions in the pane of the display.  This should all be
;; abstracted better later! (MHD/JRA 1/31/90)

;; End file with CR


;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module NETWORKS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Brian Matthews and Anne Chinn
;;; overhauled by Nicholas Caruso -ncc, 10 Apr 1996 


(def-gensym-c-function c-network-get-listener-fd
                       (:fixnum-int "g2ext_network_get_listener_fd")
  ())

(def-gensym-c-function c-network-get-fd-from-handle
		       (:fixnum-int "g2ext_network_get_fd_from_handle")
  ((:fixnum-int file-descriptor-handle)))


(def-gensym-c-function network-connected-p-internal
                       (:fixnum-int "ne_connected_p")
  ((:fixnum-int file-descriptor-handle)))

(defmacro network-connected-p (file-descriptor-handle)
  `(not (=f 0 (network-connected-p-internal ,file-descriptor-handle))))


(def-gensym-c-function c-network-get-last-error-code
                       (:fixnum-int "ne_last_error_code")
  ((:fixnum-int file-descriptor-handle)))


(def-gensym-c-function c-network-connect
		       (:fixnum-int "g2ext_network_connect")
  ((:string network-pathname)
   (:string host)
   (:string port)
   (:fixnum-int secure-p)))

(defun network-connect (pathname host port
				 &optional (secure? secure-icp-default-p))
  (when (and secure? (not secure-icp-initialized-p))
    (set-up-secure-icp))
  (c-network-connect pathname host port (if secure? 1 0)))



		; type :default => :string (MHD 3/2/96)
					;   This was done here and througout --
					;   it made no sense to me to declare
					;   the C (char *) type to be :default,
					;   I could not find doc for this type
					;   in OS-FOREIGN! JH was out; NCC had
					;   no idea.  (MHD 3/2/96)



;; Added one more argument identifying the product establishing the listener
;; (either G2 or GSI at this point) -paf! 17apr95

(def-gensym-c-function c-network-listen
    (:fixnum-int "g2ext_network_listen")
  ((:fixnum-int which-network-protocols)
   (:fixnum-int default-tcp-port?)
   (:fixnum-int tcpipexact-p)
   (:fixnum-int product)
   (:fixnum-int secure-p)))



(def-gensym-c-function c-network-close
		       (:fixnum-int "g2ext_network_close")
  ((:fixnum-int handle)))




(def-gensym-c-function c-network-accept
		       (:fixnum-int "g2ext_network_accept")
  ((:fixnum-int listener-handle)))



(def-gensym-c-function c-secure-socket-p
			      (:fixnum-int "g2ext_secure_socket_p")
  ((:fixnum-int handle)))



#+slated-for-death
(def-gensym-c-function c-get-next-connection
		       (:fixnum-int "get_next_connection")
  ())

;;; `C-get-connection-pathname' puts characters into buffer.  Make sure to pass
;;; in a simple gensym string in order to get back the results reliably.

(def-gensym-c-function c-get-connection-pathname
		       (:fixnum-int "g2ext_get_connection_pathname")
  ((:fixnum-int handle)
   (:string buffer)
   (:fixnum-int buffer-size)))

(def-gensym-c-function c-set-connection-pathname
		       (:fixnum-int "g2ext_set_connection_pathname")
  ((:fixnum-int handle)
   (:string buffer)))

(def-gensym-c-function c-set-debug-status
		       (:fixnum-int "g2ext_set_debug_status")
  ((:fixnum-int handle)
   (:fixnum-int status)))



;;; `C-get-network-listener' puts characters into buffer.  Make sure to pass
;;; in a simple gensym string in order to get back the results reliably.

(def-gensym-c-function c-get-network-listener
		       (:fixnum-int "g2ext_get_network_listener")
  ((:fixnum-int position)
   (:string buffer)
   (:fixnum-int buffer-size)))

(def-gensym-c-function ne-get-listener-handle
		       (:fixnum-int "ne_get_listener_handle")
  ((:fixnum-int position)))

(def-gensym-c-function ne-initialize-event-handling
		       (:void "ne_initialize_event_handling")
  ())

(def-gensym-c-function ne-enable-display-events
		       (:void "ne_enable_display_events")
  ())

(def-gensym-c-function ne-disable-display-events
		       (:void "ne_disable_display_events")
  ())

(def-gensym-c-function ne-display-events-enabled
		       (:fixnum-int "ne_display_events_enabled")
  ())

(defmacro with-display-events-disabled (&body body)
  `(let ((display-events-were-enabled (/=f 0 (ne-display-events-enabled))))
     (ne-disable-display-events)
     (unwind-protect (progn ,@body)
       (when display-events-were-enabled
	 (ne-enable-display-events)))))

(defmacro with-display-events-enabled (&body body)
  `(let ((display-events-were-enabled (/=f 0 (ne-display-events-enabled))))
     (ne-enable-display-events)
     (unwind-protect (progn ,@body)
       (unless display-events-were-enabled
	 (ne-disable-display-events)))))

(def-gensym-c-function ne-set-next-timer-event (:void "ne_set_next_timer_event")
  ((:fixnum-int milliseconds_to_go)))



;;; The function `ne-enqueue-scheduler-event' should enqueue
;;; an event to run the scheduler if one has not already been enqueued.  This
;;; last part is important, since fair sharing of the event queue between
;;; network events and the scheduler requires that the scheduler "get in line"
;;; in the event queue appropriately, and that subsequent handling of network
;;; events does not disturb the ordering of this queue once the scheduler has
;;; been placed in it.  This function should also kill any pending timer events.
;;; Note that there is no corresponding function to kill this event, since it is
;;; never harmful to let this execute a little more than absolutely necessary.

(def-gensym-c-function ne-enqueue-scheduler-event
                       (:void "ne_enqueue_scheduler_event")
  ())



(def-gensym-c-function c-network-listener-count
		       (:fixnum-int "g2ext_network_listener_count")
  ())



(def-gensym-c-function c-network-read
		       (:fixnum-int "g2ext_network_read")
  ((:fixnum-int handle)
  (:variable-fill-icp-buffer buffer)
  (:fixnum-int start)
  (:fixnum-int end)))


(def-gensym-c-function c-network-write
		       (:fixnum-int "g2ext_network_write")
  ((:fixnum-int handle)
  (:variable-fill-icp-buffer buffer)
  (:fixnum-int offset)
  (:fixnum-int length)))

;; jra & jh, 11/30/92.  Added an extra argument to c-network-write.  This
;; argument represents the offset at which writing is to begin, and allows to
;; implement flow control at the ICP layer.  For further details, see
;; transit-icp-buffer in INT2.


(def-gensym-c-function c-note-null-write-callbacks
		       (:void "g2ext_note_null_write_callbacks")
  ())


(def-inlined-pseudo-function-with-side-effects (c-network-io-trace-note :void "inline_network_io_trace_note")
    ((trace-note :string))
  (declare (ignore trace-note))
  nil)


(defmacro network-io-trace-note (note)
  `(c-network-io-trace-note ,note))


;;; Gethostname is essentially the gethostname unix tcp/ip system call.  It
;;; fills in the name and returns either the string length of the result or -1
;;; (indicating failure).  If successful, name will have been filled in with
;;; the host name and null terminated.  See the unix tcp/ip guide (or man page)
;;; for further details.

(def-gensym-c-function gethostname-1 (:fixnum-int "g2ext_g2_gethostname")
  ((:string name) (:fixnum-int namelen)))


(def-gensym-c-function get-nth-network-address (:fixnum-int "g2ext_nth_network_address")
  ((:fixnum-int n)
   (:string buffer)
   (:fixnum-int buffer-size)))


(declare-forward-reference timing-parameters variable)



;;; The system variable `fixnum-time-units-of-sleep-this-clock-tick' is used to
;;; count the amount of sleep that the system has received during the clock
;;; tick.  This variable is computed by g2-event-loop, and used by
;;; update-meter-values.

(def-system-variable fixnum-time-units-of-sleep-this-clock-tick networks 0)

;;; update-meter-values is only called when
;;; (g2-meter-data-service-on? data-server-parameters) is true.  The variable
;;; record-fixnum-time-units-of-sleep-this-clock-tick? is a cache
;;; for (g2-meter-data-service-on? data-server-parameters).
(defvar record-fixnum-time-units-of-sleep-this-clock-tick? nil)


;;; The variable `profiling-enabled?' is used to reflect whether
;;; profiling is currently turned on or off.  When profiling is on, this will
;;; contain an instance of the structure global-profiling-structure.

;;; This can no longer be a system-variable because the profiler has been
;;; extended to cover areas of the code that can get called before the
;;; system initialization has been completed.

(defvar profiling-enabled? nil)


;;; The function `idle-process' will relinquish the processor from this process
;;; for a short amount of time, allowing other processes on multi-tasking
;;; machines to be run.  It takes as an argument, a number of milliseconds that
;;; this process is expected to be idle, after examining the scheduler queues
;;; for this process.  On machines which allow for interruptible sleeps when
;;; events occur on network, keyboard, and mouse interfaces, then this macro may
;;; sleep for up to the given number of milliseconds, or less if an event occurs
;;; on any of these input channel interfaces.

;;; On machines where we have not been able to implement interrupt driven wake
;;; ups, this macro will have a different behavior.  The milliseconds-to-sleep-
;;; when-idle slot of the timing-parameters system table is used to determine
;;; how long to sleep when entering this macro.  By default, the value of this
;;; slot is NIL, which means to use the default sleep interval, which is
;;; currently 40 milliseconds.  Otherwise, this slot will contain a fixnum from
;;; 0 through 1000, indicating how many milliseconds to sleep.  On these
;;; machines, this sleep will not return early.

(defmacro declare-ignorable-argument (name)
  `(progn ,name))


;;; The macro `just-idle-process' will cause this process to sleep, waking up
;;; when there are any events on this process' file descriptors or window input
;;; queues.  It takes two arguments, a maximum number of milliseconds to sleep
;;; when an interruptible sleep is available, and a minimum number of
;;; milliseconds to sleep when only an uninterruptible sleep is available.  This
;;; macro is very much like idle-process, but without any of the cruft.  -jra

(defmacro just-idle-process (max-interruptible-milliseconds
			      &optional (min-milliseconds 40))
  `(c-pause ,max-interruptible-milliseconds ,min-milliseconds))




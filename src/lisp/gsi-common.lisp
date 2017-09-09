;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GSI-COMMON

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Nick Caruso, Peter Fandel, and John Hodgkinson

;;; File name:		     GSI-COMMON.LISP
;;; File location:	     /bt/ab/lisp
;;; Code control:	     CVS
;;; Purpose:                 Support GSI extension product
;;; Contents:                Various structure, function and other definitions
;;;                          supporting the GSI product that are common to both
;;;                          G2 and GSI sides of a GSI connection.
;;; This file depends on:    Preceding .LISP files in the system load ordering.
;;; Dependent files:	     Subsequent .LISP files in the system load ordering.
;;; Role in products:	     Linked into G2.  Delivered to customers in object form
;;;                          with other objects as the GSI toolkit product.
;;; Testing harness:         Regression test harness: gsi-regress.kb
;;;                          Stress and individual regression tests: navigator.kb
;;;                            see Peter Fandel for details on the navigator.
;;;                          Some validation functions also included in here.
;;; Performace requirements: These functions and macros are the core of GSI
;;;                          dataservice.  Performance is critical.
;;;
;;; File Organization:       *****   S u p p o r t   S t u f f
;;;                          Forward References.
;;;                          Constants
;;;                          GSI Structures
;;;                            GSI sensor
;;;                            GSI interface
;;;                          Global and System Variables
;;;                          Generate GSI consing pool facilities (macro)
;;;                          ICP Value Readers and Writers (macros)
;;;                          ICP Object Definitions (macros)
;;;                          GSI ICP Message Definitions
;;;





;;;; Forward References


;; To WINDOWS1:

(declare-forward-reference standard-gensym-color-alist variable)


;; To G2-GSI:

(declare-forward-reference gsi-receive-value-for-ping-request function)
(declare-forward-reference define-or-configure-gsi-sensor function)
(declare-forward-reference gsi-receive-value-for-gsi-sensor function)
(declare-forward-reference get-gsi-interface-for-gsi-sensor-if-any function)
(declare-forward-reference g2-initialize-gsi-interface function)
(declare-forward-reference maybe-declare-all-gsi-sensors function)
(declare-forward-reference write-value-of-gsi-item-p variable)

;; To TYPES:
(declare-forward-reference reclaim-if-evaluation-value-function function)
(declare-forward-reference reclaim-if-evaluation-value-1 function)


;; To BOOKS:

(declare-forward-reference post-on-message-board function)

;; To RPC-COMMON1

(declare-forward-reference read-icp-remote-value function)
(declare-forward-reference write-icp-remote-value function)
(declare-forward-reference read-icp-gsi-permanent-remote-value function)
(declare-forward-reference write-icp-gsi-permanent-remote-value function)
(declare-forward-reference write-value-of-gsi-item-p variable)

;; To rpc-common3

(declare-forward-reference current-slot-value-of-user-slot variable)
(declare-forward-reference send-icp-create-item-reference function)
(declare-forward-reference read-icp-item-reference function)
(declare-forward-reference write-icp-item-reference function)
(declare-forward-reference corresponding-icp-object-index-for-item-reference variable)

;; To GSI-RPC1

(declare-forward-references (:suppress-module-checks-for ab)
  (make-gsi-instance function GSI-RPC1))

;; To GSI-RPC2

(declare-forward-references (:suppress-module-checks-for ab)
  (gsi-reclaim-contents function GSI-RPC2))

;; To GSI


(declare-forward-references (:suppress-module-checks-for ab)

  (gsi-maximum-contexts-exceeded          variable GSI)	;a defconstant, actually.
  (gsi-timestamp-out-of-bounds            variable GSI)
  (gsi-integer-too-large                  variable GSI)
  (gsi-integer-too-small                  variable GSI)
  (gsi-not-a-symbol                       variable GSI)
  (gsi-error-in-connect                   variable GSI)
  (gsi-warning                            function GSI)
  (gsi-error                              function GSI)
  (gsi-connection-error                   function GSI)
  (gsi-fatal-error                        function GSI)
  (gsi-message                            function GSI)
  (gsi-failure-p                          function GSI)
  (reclaim-gsi-remote-procedures          function GSI)
  (reclaim-gsi-transfer-wrapper-array     function GSI)
  (reclaim-gsi-instance                   function GSI)
  (write-icp-gsi-value-vector             function GSI)
  (write-icp-gsi-values                   function GSI)
  (filter-text-for-gsi-p                  function GSI)
  (gsi-wide-api-p                         variable GSI)
  (convert-value-to-gsi-value             function GSI)
  (gsi-make-attributes-for-user-or-gsi    function GSI)
  (current-gsi-string-conversion-style    function GSI)
  (text-conversion-style-for-gsi          function GSI)
  (gsi-intern                             function GSI)
  (gsi-push-onto-appropriate-list         function GSI)
  (call-gsi-callback                      function GSI)
  (gsi-current-context-number             function GSI)
  (find-or-load-gsi-application           function GSI)
  (default-owner-for-gsi-objects          function GSI)
  )

(declare-forward-reference notify-user function)
(declare-forward-reference network-access-allowed-p function)
(declare-forward-reference framep-function function)


;;;; Constants



;; Error codes sent over ICP for GSI sensors

;;; Purpose:	     Flags for various conditions of a GSI sensor.
;;; Users:           bad-configuration is never used.  The others are used in GSI
;;;                  internals:
;;;                    add-sensor-to-group-if-it-fits
;;;                    put-sensor-in-new-sensor-group
;;;                    gsi-stop-collecting-data
;;;                    gsi-collect-one-shot-data
;;;                    gsi-set-external-sensor
;;;                    enqueue-gsi-request-for-sensor
;;;                    gsi-begin-collecting-data
;;;                    write-message-group-for-gsi-set-data
;;;                    write-message-group-for-gsi-get-data

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant cancel-collection -1)
(defconstant collect-one-now 0)
(defconstant no-value-to-set nil)
(defconstant no-error  0)
(defconstant bad-configuration 1)
(defvar gsi-magic-number 5472500)
(defconstant gsi-magic-offset 1)
)


;; Error codes sent over ICP for GSI interfaces

;;; Purpose:	     Flags for various conditions of a GSI interface.
;;; Users:	     G2 remote procedure call machinery (G2-RPC1 and G2-RPC2)
;;;                  and GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    capability deactivator for gsi-interface
;;;                    gsi-pause-data-server?
;;;                    send-data-values-if-any

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant gsi-interface-initializing 0)

(defconstant gsi-interface-waiting-for-response 1) ; negotiating version information

(defconstant gsi-interface-running-ok 2)
(defconstant gsi-interface-assumed-dead -1)
(defconstant gsi-interface-icp-connection-dead -2)
(defconstant gsi-interface-waiting-for-shutdown-ack -3)   ;; new status value 

(defconstant gsi-one-cycle	           0) ; global
(defparameter gsi-suppress-output          1)
(defconstant gsi-use-gfloats	           2) ; global
(defconstant gsi-non-c		           3) ; global
(defconstant gsi-string-check	           4)
(defconstant gsi-no-signal-handlers        5) ; global
(defconstant gsi-wide-string-api           6)
(defconstant gsi-user-data-for-callbacks   7)
(defconstant gsi-no-flush                  8) 
(defconstant gsi-trace-run-state           9) ; global
(defconstant gsi-new-symbol-api           10)
(defconstant gsi-use-references           11)
(defconstant gsi-disable-interleaving     12)
(defconstant gsi-trace-run-loop           13)
(defconstant gsi-protect-inner-calls      14)
(defconstant gsi-do-not-reformat-messages 15)
(defconstant gsi-user-owns-gsi-items      16)

(defconstant gsi-number-of-options        17)


(defconstant gsi-set-up 0)
(defconstant gsi-get-tcp-port 1)
(defconstant gsi-pause-context 2)
(defconstant gsi-resume-context 3)
(defconstant gsi-shutdown-context 4)
(defconstant gsi-g2-poll 5)
(defconstant gsi-read-callback 6)
(defconstant gsi-write-callback 7)
(defconstant gsi-open-fd 8)
(defconstant gsi-close-fd 9)
(defconstant gsi-initialize-context 10)
(defconstant gsi-receive-registration 11)
(defconstant gsi-receive-deregistrations 12)
(defconstant gsi-get-data 13)
(defconstant gsi-set-data 14)
(defconstant gsi-receive-message 15)
(defconstant gsi-run-state-change 16)
(defconstant gsi-error-handler 17)
(defconstant gsi-missing-procedure-handler 18)
(defconstant gsi-watchdog-function 19)
(defconstant gsi-idle 20)
(defconstant gsi-start-context 21)
(defconstant gsi-reset-context 22)
(defconstant gsi-writing-fd 23)
(defconstant gsi-not-writing-fd 24)

(defconstant gsi-number-of-callbacks 25)

)




;;; default-gsi-interface-countdown-timer-limit
;;;
;;; Purpose:         After so many seconds of inactivity, assume GSI interface
;;;                  not working.
;;; Users:	     GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    handle-gsi-shut-down-connection
;;;                    gsi-process-gsi-interfaces

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant default-gsi-interface-countdown-timer-limit 10)	; 10 seconds
(defconstant size-of-array-of-transfer-wrappers 50)
)




;;;; Required Macros




;;;; Generate GSI consing pool facilities

;;; Declaration:     gsi
;;; Type:	     G2 consing suite.
;;; Purpose:	     Manage consing in the GSI facility.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     GSI (modules G2-GSI, GSI-COMMON, GSI).
;;; Prerequisites:   The macro defconser must be defined.
;;; Side effects:    Creates the following consing variables, functions, and macros:
;;;                    gsi-conses
;;;                    gsi-cons
;;;                    gsi-cons-macro
;;;                    gsi-list
;;;                    make-gsi-list-macro
;;;                    make-gsi-list
;;;                    gsi-list-macro
;;;                    copy-tree-using-gsi-conses
;;;                    copy-list-using-gsi-conses
;;;                    reclaim-gsi-cons
;;;                    reclaim-gsi-cons-macro
;;;                    reclaim-gsi-list
;;;                    reclaim-gsi-list-macro
;;;                    reclaim-gsi-list-given-tail
;;;                    reclaim-gsi-list*
;;;                    reclaim-gsi-tree
;;;                    delete-gsi-element
;;;                    delete-gsi-cons
;;;                    report-outstanding-gsi-conses
;;;                    gsi-push
;;;                    gsi-pushnew
;;;                    gsi-pop
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Possible bugs:   We need to be certain that GSI dies not reclaim any
;;;                  icp-conses, and vice versa.

(defconser gsi)

(defun-void reclaim-gsi-list-function (gsi-list)
  (reclaim-gsi-list gsi-list))





;;;; Global and System Variables

(defparameter gsi-allocated-array-list? nil)
(defparameter gsi-allocated-string-list? nil)
(defvar gsi-reclaim-list? nil)           ; the global reclaim list (the default default).
(defvar gsi-reclaim-list-level 'global)  ; 'global, or 'rpc-arg-list
(def-system-variable index-to-array-of-transfer-wrappers gsi-common gsi-magic-offset)
(defvar gsi-vector-length)
(defvar make-gsi-instance-existing-instance nil)
(defvar gsi-local-home nil)


;;;; GSI context number housekeeping functions:
(defvar gsi-context-to-socket-map nil)

(defvar number-of-contexts-allocated 0)

(defun-simple allocate-gsi-context-number ()
  (incff number-of-contexts-allocated)
  (let* ((map gsi-context-to-socket-map)
	 (context (assign-index-in-index-space map)))
    (store-object-in-index-space map context current-icp-socket)
    context))

(defun-simple free-gsi-context-number (context)
  (when (<=f 0 context)
    (when (>f number-of-contexts-allocated 0)
      (decff number-of-contexts-allocated))
    (let ((map gsi-context-to-socket-map))
      (store-object-in-index-space map context nil)
      (deassign-index-in-index-space context map)
      gsi-undefined-context)))

;;; gsi-maximum-number-of-contexts
;;;  Currently used only in the macros that manage the table of GSI context
;;;  numbers.  This global  is initialized in initialize-gsi-context-number-table,
;;;  below, called from run-gsi-1 in gsi.lisp
(defvar gsi-maximum-number-of-contexts nil) ; negative means unlimited

(defun-void initialize-gsi-context-number-table (maximum-number-of-contexts)
  (unless gsi-context-to-socket-map
    (setq gsi-context-to-socket-map
	  (make-index-space 'gsi-context-to-socket-map nil))
    (enlarge-index-space gsi-context-to-socket-map 20))
  (setf gsi-maximum-number-of-contexts maximum-number-of-contexts))

(def-structure (gsi-extension-data
		 (:reclaimer reclaim-gsi-extension-data-internal))

  (gsi-context-number #.gsi-uninitialized-context)
  (gsi-extension-data-user-data nil)
  
  (gsi-transfer-wrapper-array (create-transfer-wrapper-array
				size-of-array-of-transfer-wrappers)
    :reclaimer reclaim-gsi-transfer-wrapper-array)
  
  (gsi-remote-procedures nil
    :reclaimer reclaim-gsi-remote-procedures)
  (gsi-outgoing-item-list? nil
    :reclaimer reclaim-gsi-list-function)
  (gsi-remote-process-initialization-string nil
    :reclaimer reclaim-if-text-or-gensym-string-function)
  (gsi-interface-for-context nil)
  (gsi-initialize-context-has-been-called-p nil)

  (gsi-extension-application nil)
  (gsi-extension-last-converted-string nil)

  (gsi-extension-most-recent-error 0)
  (gsi-extension-most-recent-error-message nil)
  (gsi-extension-most-recent-error-remote-procedure-identifier nil)

  (gsi-remote-home-for-context nil
    :reclaimer reclaim-if-gsi-instance-for-context))

(defun-simple reclaim-gsi-extension-data (extension-data)
  (let ((socket-context-number (gsi-context-number extension-data)))
    (unless (=f socket-context-number gsi-undefined-context)
      (free-gsi-context-number socket-context-number)))
  (reclaim-gsi-extension-data-internal extension-data))



;;;; GSI Structures

;; GSI sensor

;;; Declaration:     gsi-sensor
;;; Type:	     G2 def-structure.
;;; Purpose:	     Implement a corresponding ICP object for a local GSI sensor.
;;; Slots:           > g2-sensor contains the GSI sensor to which this structure
;;;                    corresponds.
;;;                  > g2-sensor-frame-serial-number contains the fixnum serial
;;;                    number of the GSI sensor to which this structure
;;;                    corresponds.  This is used to detect GSI sensors which have
;;;                    been deleted and then reused.
;;;                  > gsi-sensor-collection-interval is an evaluation
;;;                    quantity (fixnum or managed-float) giving the
;;;                    interval at which requests for values will happen.  If
;;;                    collection interval is 0, only one request will be made.
;;;                  > gsi-sensor-status-code is a fixnum giving the status of the
;;;                    GSI sensor's value.  This slot defaults to the constant
;;;                    no-error.  Other pre-defined values are cancel-collection,
;;;                    collect-one-now.
;;;                  > gsi-sensor-attribute-list is a gensym-list of gsi-parameters
;;;                    giving the values of the identifying-attributes of the GSI
;;;                    sensor.
;;;                  > corresponding-icp-object-map-for-gsi-sensor maps ICP sockets
;;;                    onto indices of the corresponding GSI sensor in the remote
;;;                    GSI process.
;;;                  > gsi-sensor-ok-to-put-values?  is nil if the GSI sensor has
;;;                    cancelled all requests for values, non-nil otherwise.  This
;;;                    slot defaults to non-nil
;;; Return behavior: No useful value.
;;; Users:           GSI internals
;;;                    get-or-make-gsi-sensor
;;;                    gsi-sensor ICP object
;;;                    get-gsi-interface-for-gsi-sensor-if-any
;;;                    gsi-receive-value-for-gsi-sensor
;;;                    process-gsi-sensor-values
;;;                    send-message-series-for-gsi-request
;;;                    define-gsi-sensor
;;;                    define-or-configure-gsi-sensor
;;;                    gsi-sensor ICP object type
;;;                    add-sensor-to-group-if-it-fits
;;;                    put-sensor-in-new-sensor-group
;;;                  Also "GSI in G2" (handler for ICP message define-gsi-sensor).
;;; Prerequisites:   The macro def-structure must be defined.
;;; Side effects:    Defines a constructor macro make-gsi-sensor, which takes as
;;;                  arguments the initial values for slots: g2-sensor,
;;;                  g2-sensor-frame-serial-number, gsi-sensor-collection-interval.
;;;                  Defines a predicate macro gsi-sensor-p.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           See the gsi-sensor ICP object in this file.

;; get-or-make-gsi-sensor is called by: ensure-gsi-item-registration-on-network
;;               add-sensor-to-group-if-it-fits put-sensor-in-new-sensor-group

;; reclaim-g2-sensor is called by the icp-object-type reclaimer, and by
;;               deactivate-dataservice-for-gsi-data-service
#|
(def-structure (g2-sensor
		 (:constructor
		   make-g2-sensor ; called only by get-or-make-gsi-sensor
		   (g2-sensor)))
  
  ;; set by:  make-g2-sensor
  ;; read by: icp-object-type get-gsi-interface-for-gsi-sensor-if-any gsi-receive-value-for-gsi-sensor
  ;;          process-gsi-sensor-values send-message-series-for-gsi-request
  g2-sensor
  ;; set by:  get-or-make-gsi-sensor
  ;; read by: gsi-sensor-ok-to-receive-value-p process-gsi-sensor-values
  g2-sensor-frame-serial-number
  ;; set by:  set-corresponding-icp-object-map-for-sensor
  ;; read by: corresponding-icp-object-map-for-sensor
  (corresponding-icp-object-map-for-g2-sensor nil)

  ;; set by:  get-or-make-gsi-sensor gsi-begin-collecting-data
  ;; read by: send-message-series-for-gsi-request
  ;;          process-gsi-sensor-values (check for cancel-collection)
  g2-sensor-collection-interval
  ;; set by:  gsi-receive-value-for-gsi-sensor
  ;; read by: gsi-receive-value-for-gsi-sensor
  (g2-sensor-status-code #.no-error)
  )
|#







;;; Declaration:     send-data-values-if-any
;;;                    (gsi-interface timestamp)
;;; Type:	     ICP message type.
;;; Purpose:         Request the remote GSI process to send unsolicited values it
;;;                  has collected.
;;; Arguments:       gsi-interface is a corresponding GSI interface.  year, month,
;;;                  day, hour, minute, second are of ICP value type integer.
;;;                  Currently, the C version of GSI ignores these arguments.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    write-message-group-upon-gsi-interface-activation
;;;                    gsi-process-gsi-interfaces
;;; Prerequisites:   None.
;;; Side effects:    Can create a corresponding GSI interface in the remote GSI
;;;                  process.
;;; Non-local exits: None.
;;; Memory impact:   Can allocate memory for a corresponding GSI interface in the
;;;                  remote GSI process.

;;; The handler for send-data-values-if-any is used in order to receive
;;; unsolicited data from the GSI extension process.  This sends the ICP
;;; message send-data-values-if-any.  The handler for this calls the user
;;; function gsi-g2-poll. It then calls send-icp-receive-value-for-ping-request.

;; sadly, we must always send the timestamp in the
;; six integer format here.  We are pinned by the use
;; of send-data-values-if-any before version info is
;; available.  This blocks version-bifurcation in the
;; ICP reader and writer for gsi-timestamps, and so
;; these cannot be used in this message. -ncc, 8/8/94
 ; wait until the reply to return-peer-version


;;; Declaration:     receive-value-for-ping-request
;;;                    (returned-gsi-interface
;;;                     year month day hour minute second
;;;                     status)
;;; Type:	     ICP message type.
;;; Purpose:	     Acquire status information from the remote GSI process.
;;; Arguments:       returned-gsi-interface is the local gsi-interface structure
;;;                  associated with the corresponding GSI interface in the remote
;;;                  GSI process.  year, month, day, hour, minute, second are
;;;                  fixnums giving components of a timestamp.  status is a fixnum
;;;                  representing the status received from the remote GSI process.
;;;                  (See the ICP value type gsi-interface-status in GSI for
;;;                  status codes.)
;;; Return behavior: No useful value.
;;; Users:           "G2 in GSI" machinery, GSI internals
;;;                  (receive-value-for-ping-request).
;;; Prerequisites:   The corresponding GSI interface for returned-gsi-interface must
;;;                  have already been defined in the remote GSI process.
;;; Side effects:    See gsi-receive-value-for-ping-request in GSI.
;;; Non-local exits: None.
;;; Memory impact:   See gsi-receive-value-for-ping-request in GSI.

(def-icp-message-type define-gsi-interface (corresponding-icp-object-index)
  corresponding-icp-object-index)

(def-icp-message-type send-data-values-if-any
                      ((corresponding-icp-object-index gsi-interface)
		       (integer year) (integer month)
		       (integer day) (integer hour)
		       (integer minute) (integer second))
  (runtime-current-system-case
    (gsi
      (cond ((=f gsi-connection-established (gsi-connection-state current-icp-socket))
	     (writing-icp-message-group ((icp-output-port current-icp-socket))
	       (send-icp-receive-value-for-ping-request
		 gsi-interface year month day hour minute second
		 gsi-interface-running-ok))
	     (call-gsi-callback gsi-g2-poll))
	    (t
	     (let ((extension-data (gsi-extension-data? current-icp-socket)))
	       (setf (gsi-interface-for-context extension-data) gsi-interface))
	     (with-bifurcated-version-for-output (supports-icp-version-protocol-icp-version)
	       (gsi-reply-to-initial-ping)
	       nil)))) ; see handler for return-peer-version, for call to gsi-reply-to-initial-ping
    (t
      gsi-interface year month day hour minute second
      nil)))

(defmacro gsi-send-reply-to-initial-ping (icp-socket)
  (let ((icp-socket-var (make-symbol "ICP-SOCKET")))
    `(let ((,icp-socket-var ,icp-socket))
       (when (=f gsi-connection-initializing
		 (gsi-connection-state ,icp-socket-var))
	 (gsi-send-reply-to-initial-ping-internal ,icp-socket-var)))))

(defun-void gsi-send-reply-to-initial-ping-internal (icp-socket)
  (setf (gsi-connection-state icp-socket) gsi-connection-established)
  (writing-icp-message-group ((icp-output-port icp-socket))
    (send-icp-receive-value-for-ping-request
      (gsi-interface-for-context (gsi-extension-data? icp-socket))
      0 0 0 1 1 1970 ; second minute hour day month year
      gsi-interface-running-ok)))

(defun-simple gsi-reply-to-initial-ping ()
  (unless (call-initialize-context-and-maybe-reject-connection)
    (gsi-send-reply-to-initial-ping current-icp-socket)))

(def-icp-message-type receive-value-for-ping-request
                      ((corresponding-icp-object-index gsi-interface)
		       (integer year) (integer month)
		       (integer day) (integer hour)
		       (integer minute) (integer second)
		       (integer status))
  (gsi-receive-value-for-ping-request ; defined in g2-gsi
    (get-original-icp-object gsi-interface)
    year month day hour minute second status))







(def-structure (gsi-history
		 (:constructor
		   make-gsi-history-1 (gsi-history-length
				       gsi-history-values
				       gsi-history-timestamps
				       gsi-history-counter))
		 (:reclaimer
		   reclaim-gsi-history-1))
  gsi-history-length
  gsi-history-values 
  gsi-history-timestamps
  gsi-history-internals
  gsi-history-dynamic-info
  gsi-history-counter)

(def-structure (gsi-attribute
		 (:constructor
		   make-gsi-attribute-1 (gsi-attribute-spec
					 gsi-attribute-instance
					 gsi-attribute-owner))
		 (:reclaimer
		   reclaim-gsi-attribute-1))
  gsi-attribute-spec
  (gsi-attribute-qualified-name-1 nil)
  (gsi-attribute-flags 0)
  gsi-attribute-instance      ; Embedded (contains a type, value etc.)
  gsi-attribute-owner)

(defmacro set-gsi-attribute-qualified-name (gsi-attribute value)
  `(setf (gsi-attribute-qualified-name-1 ,gsi-attribute) ,value))

(defsetf gsi-attribute-qualified-name set-gsi-attribute-qualified-name)

(defmacro gsi-attribute-is-transient-p (gsi-attribute)
  `(=f 1 (logandf 1 (gsi-attribute-flags ,gsi-attribute))))

(defun-simple set-gsi-attribute-is-transient-p (gsi-attribute new-value)
  (let ((flags (gsi-attribute-flags gsi-attribute)))
    (setf (gsi-attribute-flags gsi-attribute)
	  (if new-value
	      (logiorf 1 flags)
	      (logandf #.(lognot 1) flags)))
    new-value))

(defsetf gsi-attribute-is-transient-p set-gsi-attribute-is-transient-p)

(defmacro gsi-attribute-is-identifying-p (gsi-attribute)
  `(=f 2 (logandf 2 (gsi-attribute-flags ,gsi-attribute))))

(defun-simple set-gsi-attribute-is-identifying-p (gsi-attribute new-value)
  (let ((flags (gsi-attribute-flags gsi-attribute)))
    (setf (gsi-attribute-flags gsi-attribute)
	  (if new-value
	      (logiorf 2 flags)
	      (logandf #.(lognot 2) flags)))
    new-value))

(defsetf gsi-attribute-is-identifying-p set-gsi-attribute-is-identifying-p)


(def-structure (gsi-transfer-wrapper
		 (:constructor
		   make-gsi-transfer-wrapper-1
		   (gsi-transfer-sensor-or-index
		    gsi-transfer-status
		    gsi-transfer-update-interval
		    gsi-transfer-instance
		    gsi-transfer-owner))
		 (:reclaimer
		   reclaim-gsi-transfer-wrapper-1))
  gsi-transfer-sensor-or-index
  gsi-transfer-status
  (gsi-transfer-update-interval nil :reclaimer reclaim-if-managed-float)
  gsi-transfer-instance      ; Embedded (contains a type, value etc.)
  gsi-transfer-owner)

(defun-simple make-gsi-user-transfer-wrapper ()
  (make-gsi-transfer-wrapper-1 nil 0 nil nil 'user))

(defun-simple create-transfer-wrapper-array (size)
  (let ((transfer-wrapper-array (gsi-allocate-managed-array (1+f size))))
    (setf (gsi-managed-svref transfer-wrapper-array 0) gsi-magic-number)
    (loop for i from gsi-magic-offset below (+f size gsi-magic-offset)
	  do
      (setf (gsi-managed-svref transfer-wrapper-array i)
	    (make-gsi-transfer-wrapper-1 nil 0 nil nil 'context)))
    transfer-wrapper-array))

(def-structure (gsi-instance
		 (:constructor make-gsi-instance-1 ())
		 (:reclaimer reclaim-gsi-instance-1))
  
  (gsi-instance-value-type-and-owner 0)
  (gsi-instance-value nil)
  (gsi-instance-extension nil))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant gsi-bits-per-instance-owner 3)
)

(defun-simple gsi-instance-value-function (gsi-instance)
  (gsi-instance-value gsi-instance))

; gsi-instance-value-type -> gsi-instance-class-value-type
(defmacro gsi-instance-value-type (gsi-instance)
  `(ashf (gsi-instance-value-type-and-owner ,gsi-instance)
	 #.(- gsi-bits-per-instance-owner)))

(defun-simple set-gsi-instance-value-type (gsi-instance value)
  (setf (gsi-instance-value-type-and-owner gsi-instance)
	(logiorf (logandf (gsi-instance-value-type-and-owner gsi-instance)
			  #.(1- (ash 1 gsi-bits-per-instance-owner)))
		 (ashf value #.gsi-bits-per-instance-owner))))

(defsetf gsi-instance-value-type set-gsi-instance-value-type)

(defmacro gsi-instance-owner (gsi-instance)
  `(case (logandf (gsi-instance-value-type-and-owner ,gsi-instance)
		  #.(1- (ash 1 gsi-bits-per-instance-owner)))
     (0 'gsi)
     (1 'user)
     (2 'context)
     (3 'gsi-event-queue)
     (4 'gsi-input-queue)))

(defun set-gsi-instance-owner (gsi-instance value)
  (setf (gsi-instance-value-type-and-owner gsi-instance)
	(logiorf (ashf (gsi-instance-value-type gsi-instance)
		       #.gsi-bits-per-instance-owner)
		 (case value
		   (gsi             0)
		   (user            1)
		   (context         2)
		   (gsi-event-queue 3)
		   (gsi-input-queue 4)
		   (t               0))))
  value)

(defsetf gsi-instance-owner set-gsi-instance-owner)

(def-structure (gsi-instance-extension
		 (:constructor make-gsi-instance-extension ())
		 (:reclaimer reclaim-gsi-instance-extension-1))
  (gsi-instance-context--ext nil)
  (gsi-instance-class--ext nil)
  (gsi-instance-class-type--ext 0)
  (gsi-instance-name--ext nil)
  (gsi-instance-plist--ext nil :reclaimer reclaim-gsi-list)
  (gsi-instance-user-data--ext nil)
  (gsi-element-count--ext 0)   ;number of elts in value if value is an
					;  aggregate type, else 0.
  (gsi-attributes--ext nil)
  (gsi-attribute-count--ext 0)

  ;; read by the writer for gsi-value-vector, by gsi-timestamp-of
  ;; and by gsi-returned-timed-attrs and gsi-return-timed-values
  (gsi-instance-timestamp--ext nil :reclaimer reclaim-if-managed-float)
  (gsi-instance-collection-interval--ext nil :reclaimer reclaim-if-managed-float)
  (gsi-instance-history--ext nil)

  (icp-object-map-for-gsi-instance--ext
    nil :reclaimer reclaim-gensym-list)
  (gsi-instance-reclaim-list--ext nil))

(defmacro def-gsi-extension-accessor (name &optional fixnump)
  (let ((extension-accessor (intern (format nil "~A--EXT" name)))
	(set-macro (intern (format nil "SET--~A" name))))
    `(progn
       (defmacro ,name (gsi-instance)
	 `(let ((gsi-instance-extension (gsi-instance-extension ,gsi-instance)))
	    (if gsi-instance-extension
		(,',extension-accessor gsi-instance-extension)
		,',(if fixnump 0 nil))))
       (defmacro ,set-macro (gsi-instance value)
	 `(let ((gsi-instance-extension (gsi-instance-extension ,gsi-instance)))
	    (unless gsi-instance-extension
	      (setq gsi-instance-extension (make-gsi-instance-extension))
	      (setf (gsi-instance-extension ,gsi-instance) gsi-instance-extension))
	    (setf (,',extension-accessor gsi-instance-extension) ,value)))
       (defsetf ,name ,set-macro))))

(def-gsi-extension-accessor gsi-instance-context)
(def-gsi-extension-accessor gsi-instance-user-data)
(def-gsi-extension-accessor gsi-instance-class)
(def-gsi-extension-accessor gsi-instance-class-type t)
(def-gsi-extension-accessor gsi-instance-name)
(def-gsi-extension-accessor gsi-instance-plist)
(def-gsi-extension-accessor gsi-element-count t)
(def-gsi-extension-accessor gsi-attributes)
(def-gsi-extension-accessor gsi-attribute-count t)
(def-gsi-extension-accessor gsi-instance-timestamp)
(def-gsi-extension-accessor gsi-instance-collection-interval)
(def-gsi-extension-accessor gsi-instance-history)
(def-gsi-extension-accessor icp-object-map-for-gsi-instance)
(def-gsi-extension-accessor gsi-instance-reclaim-list)

(defun get-gsi-instance-plist-value (gsi-instance property)
  (getf (gsi-instance-plist gsi-instance) property))

(defun set-gsi-instance-plist-value (gsi-instance property value)
  (let* ((plist (gsi-instance-plist gsi-instance))
	 (m (memq property plist)))
    (unless m
      (setq m (gsi-cons property (gsi-cons nil plist)))
      (setf (gsi-instance-plist gsi-instance) m))
    (setf (car (cdr-of-cons m)) value)
    value))

(defsetf get-gsi-instance-plist-value set-gsi-instance-plist-value)

(defmacro get-gsi-instance-plist-flag (gsi-instance property)
  `(get-gsi-instance-plist-value ,gsi-instance ,property))

; read only by read-side of ascend-to-parent
(defmacro gsi-superior-item (gsi-instance)
  `(get-gsi-instance-plist-value ,gsi-instance 'gsi-superior-item))

; read only by the writer for rpc-value-or-object
(defmacro gsi-instance-squirrelled-index (gsi-instance)
  `(get-gsi-instance-plist-value ,gsi-instance 'gsi-instance-squirrelled-index))

(defmacro gsi-item-append-flag-value (gsi-instance)
  `(get-gsi-instance-plist-flag ,gsi-instance 'gsi-append-flag))

(defmacro gsi-item-delete-flag-value (gsi-instance)
  `(get-gsi-instance-plist-flag ,gsi-instance 'gsi-delete-flag))

(defmacro gsi-update-items-in-lists-and-arrays-flag-value (gsi-instance)
  `(get-gsi-instance-plist-flag ,gsi-instance 'gsi-update-items-in-lists-and-arrays-flag))

(defmacro gsi-item-reference-flag-value (gsi-instance)
  `(get-gsi-instance-plist-flag ,gsi-instance 'gsi-reference-flag))

(defmacro gsi-item-name-is-identifying-flag-value (gsi-instance)
  `(get-gsi-instance-plist-flag ,gsi-instance 'gsi-name-is-identifying-flag))

(defmacro gsi-item-class-is-identifying-flag-value (gsi-instance)
  `(get-gsi-instance-plist-flag ,gsi-instance 'gsi-class-is-identifying-flag))


(def-structure (gsi-array-wrapper
		 (:constructor make-gsi-array-wrapper (gsi-array-type gsi-array)))
  gsi-array-type
  gsi-array)

(defmacro gsi-sensor-collection-interval (sensor)
  `(gsi-instance-collection-interval ,sensor))

(def-substitution-macro gsi-sensor-p (sensor)
  (and (gsi-instance-p sensor)
       (not (null (gsi-sensor-collection-interval sensor)))))

(defun-simple gsi-sensor-p-function (sensor)
  (gsi-sensor-p sensor))

(defmacro make-gsi-sensor (user-or-gsi)
  `(make-gsi-instance nil nil nil nil nil ,user-or-gsi
		      (allocate-managed-float 0.0)))

(defmacro gsi-sensor-value-type (sensor)
  `(gsi-instance-class-type ,sensor))

(defmacro gsi-sensor-name (sensor)
  `(gsi-instance-name ,sensor))

(defmacro gsi-sensor-class (sensor)
  `(gsi-instance-class ,sensor))

(defmacro gsi-sensor-user-data (sensor)
  `(gsi-instance-user-data ,sensor))

(defun-simple gsi-sensor-index (gsi-sensor)
  (car (last (icp-object-map-for-gsi-instance gsi-sensor))))


(defun-void reclaim-gsi-instance-for-gsi (gsi-instance)
  (reclaim-gsi-instance gsi-instance 'gsi))

(defun-void reclaim-gsi-instance-for-context (gsi-instance)
  (reclaim-gsi-instance gsi-instance 'context))

(defun-void reclaim-if-gsi-instance-for-context (gsi-instance)
  (when gsi-instance
    (reclaim-gsi-instance gsi-instance 'context)))

(defun-void reclaim-gsi-instance-for-user (gsi-instance)
  (reclaim-gsi-instance gsi-instance 'user))

(def-icp-object-type gsi-instance
    (item-index-space
      (icp-object-map-for-gsi-instance gsi-instance))
  (let ((corresponding-icp-object-index-for-item-reference corresponding-icp-object-index))
    (with-appropriate-version-for-output (item-reference-icp-version)
      (send-icp-create-item-reference gsi-instance))
    gsi-instance))







;;;; GSI Supporting Macros and Functions

(def-inlined-pseudo-function-with-side-effects (internal-gsi-start :void)
    ()
  nil)


(def-global-property-name gsi-user-data-of-symbol)

(defparameter gsi-most-recent-error 0)
(defparameter gsi-most-recent-error-message nil)
(defparameter gsi-most-recent-error-remote-procedure-identifier nil)

(defmacro using-wide-gsi-api-p ()
  `gsi-wide-api-p)



;;; The macro `def-gsi-api-function' defines GSI functions which form the GSI API.
;;; Each API fn is registered as foreign-callable (in the translator, of course)
;;; and defun'd appropriately.

;; jh, 3/15/94. If we don't call the body of the def-foreign-callable inside a
;; stack-protected context, there is no guarantee that it will work properly in
;; Chestnut.  Consider verifying that defun-allowing-unwind is no longer
;; necessary, so we can remove this indirection through protected-function-name.

;; jh, 6/23/94.  We're in a bind here, since calls to the the inner defuns leaks
;; memory for Lisp float boxes if the caller is passing double-floats.  So we
;; should revert back to a single def-foreign-callable, which will not box, but
;; which might manifest the Chestnut "unwind-protect" bug.  After looking at the
;; doc for defun-allowing-unwind that describes this bug, I believe that we are
;; not at risk here, even if Chestnut has failed to fix it.  My reasoning is
;; that the variable inside-top-level-error-catcher-p never gets side-effected
;; (or even rebound) within the dynamic extent of the body.  Note the use of
;; ab-lisp::catch to sidestep the "not in keeping with AB's coding convention"
;; warnings that result from using ab::catch.

;;; note: in the first clause of the outer-body form, the let functions as a
;;; cheap unwind-protect; that is, throwing out of the inner-function causes
;;; inside-top-level-error-catcher-p to revert to its outer --global-- binding,
;;; which should always be nil.

(defvar in-unprotected-gsi-api-call-p nil)

(defvar gsi-protect-inner-calls-p nil)

(defun protect-gsi-api-call-p ()
  (current-system-case
    (gsi
      (or (null top-level-error-catcher-tag)
	  (not (null gsi-protect-inner-calls-p))))))

(defmacro with-gsi-catcher-context (&body body)
  `(ab-lisp::catch 'gsi-catch
     (let ((shutdown-catch-tag 'gsi-catch) ; shutdown-or-exit
	   (top-level-error-catcher-tag 'gsi-catch) ; signals or errors
	   (abort-level-0-tag 'gsi-catch)) ; abort-for-icp, gsi-continue-run-loop
       ,@body)))

(defun-for-macro gsi-api-argument-list (argument-specs)
  (if (and (eval-feature :chestnut-3)
	   (eval-feature :chestnut-trans)
	   (not (eval-feature :development))
	   (let ((system (distribution-current-system 'def-gsi-api-function)))
	     (or (eq 'gsi system)
		 #+gsi-in-g2 (eq 'ab system))))
      (loop for (arg type) in argument-specs
	    unless (and (consp type)
			(eq (car type) 'tw-return-value))
	      collect arg)
      (loop for (arg type) in argument-specs
	    unless (and (consp type)
			(or (eq (car type) 'gsi-return-value)
			    (eq (car type) 'tw-return-value)))
	      collect arg)))

(defmacro def-gsi-api-function (name-and-options argument-specs &body body)
  (let* ((outer-function-name (car name-and-options))
	 (return-type (second (assoc :return-type (cdr name-and-options))))
	 (needs-catch-p (second (or (assoc :needs-catch-p (cdr name-and-options))
				    '(:needs-catch-p t))))
	 (initializes-gsi (second (assoc :initializes-gsi (cdr name-and-options))))
	 (aux-tail (member '&aux argument-specs))
	 (argument-specs (ldiff argument-specs aux-tail))
	 (aux-vars (cdr aux-tail))
	 (argument-list (gsi-api-argument-list argument-specs))
	 (inner-defun-name
	   (intern (format nil "SHARED-~s" outer-function-name)))
	 (string-p (or (gsi-string-type-p return-type)
		       (loop for (arg type) in argument-specs
			     when (gsi-string-type-p type)
			       return t
			     finally (return nil))
		       (eq outer-function-name 'gsi-set-history)))
	 (inner-argument-list (if string-p
				  `((using-wide-gsi-api-p) ,@argument-list)
				  argument-list))
	 (inner-argument-specs (if string-p
				   `((wide-api-p :object) ,@argument-specs)
				   argument-specs))
	 (return-float-p (or (eq return-type ':double-float)
			     (eq return-type 'gsi-float)))
	 (inner-defun-call
	   (if (or (eq return-type ':void) (eq return-type ':null))
	       `(,inner-defun-name ,@inner-argument-list)
	       `(setq result (,inner-defun-name ,@inner-argument-list))))
	 (outer-form
	   `(let ((in-recursive-gsi-context
		    (not (null top-level-error-catcher-tag))))
	      ,(if needs-catch-p
		   `(if (not (protect-gsi-api-call-p))
			(let ((in-unprotected-gsi-api-call-p t))
			  ,inner-defun-call)
			(with-gsi-catcher-context
			    ,inner-defun-call
			  nil))
		   inner-defun-call)))
	 (outer-forms
	   `(,@(when initializes-gsi
		 `((current-system-case (gsi (internal-gsi-start)))))
	     (entering-gsi-api-callback ,outer-function-name)
	     ,outer-form
	     (leaving-gsi-api-callback ,outer-function-name)))
	 (outer-body-form
	   (if (or (eq return-type ':void) (eq return-type ':null))
	       `(progn ,@outer-forms)
	       `(let ((result ,(case return-type
				   ((gsi-float :double-float) 0.0)
				   ((gsi-fixnum-long :fixnum-long :fixnum-int) 0)
				   (t nil))))
		  ,@(when return-float-p `((declare (type gensym-float result))))
		  ,@outer-forms
		  result))))
    `(progn
       (def-gsi-foreign-callable (,inner-defun-name
				    (:return-type ,return-type))
	   (,@inner-argument-specs ,@(when aux-vars `(&aux ,@aux-vars)))
	 ,@body)
       (declare-gsi-api-symbol ,outer-function-name)
       (if-chestnut-gsi
	 (def-chestnut-outer-gsi-api-function ,outer-function-name
	     ,return-type ,argument-specs ,outer-body-form)
	 (defun-allowing-unwind ,outer-function-name ,argument-list
	     ,outer-body-form)))))

(defmacro def-chestnut-outer-gsi-api-function
    (outer-function-name return-type argument-specs outer-body-form)
  (let ((outer-return-type (gsi-type-no-conversion-type return-type))
	(outer-argument-specs
	  (loop for (arg type) in argument-specs
		collecting `(,arg ,(gsi-type-no-conversion-type type)))))
    (with-package-specific-symbols (tx |::| def-foreign-callable)
      `(progn
	 #+dll-function
 	 (tcl:declaim (tx:dllexport-function ,outer-function-name))
	 (def-foreign-callable (,outer-function-name
				  (:return-type ,outer-return-type))
	     ,outer-argument-specs
	   ,outer-body-form)))))

(defun-for-macro gsi-type-no-conversion-type (type)
  (cond ((keywordp type)
	 type)
	((eq type 'gsi-fixnum-long)
	 ':fixnum-long)
	((eq type 'gsi-float)
	 ':double-float)
	(t
	 ':object)))

(defun-for-macro gsi-type-side-effects-for-type (type)
  (and (consp type)
       (let ((type-name (car type)))
	 (unless (or (eq type-name 'gsi-return-value)
		     (eq type-name 'tw-return-value)
		     (eq type-name 'gsi-typed-array))
	   (let ((arg (cadr type)))
	     (list arg))))))

(defun-for-macro make-gsi-type (name parameters clauses)
  (setf (get name 'parameters) parameters)
  (dolist (key '(argument argument-type result return-type reclaim))
    (remprop name key))
  (dolist (clause clauses)
    (setf (get name (car clause)) (cadr clause)))
  name)

(defun gsi-string-type-p (type)
  (if (atom type)
      (and (symbolp type)
	   (get type 'stringp))
      (and (eq (car type) 'gsi-typed-array)
	   (or (eq (cadr type) 'string)
	       (eq (cadr type) 'symbol)))))

(defmacro define-gsi-type (name parameters &body clauses)
  `(eval-when (:compile-toplevel :execute)
     (make-gsi-type ',name ',parameters ',clauses)))

(defun-for-macro gsi-type-specified-argument-type (gsi-type)
  (let ((type-name (if (atom gsi-type) gsi-type (car gsi-type))))
    (get type-name 'argument-type)))

(defun-for-macro gsi-type-specified-return-type (gsi-type)
  (let ((type-name (if (atom gsi-type) gsi-type (car gsi-type))))
    (get type-name 'return-type)))

(defun-for-macro gsi-fc-convert-argument-p (gsi-type)
  (if (keywordp gsi-type)
      nil
      (let ((type-name (if (atom gsi-type) gsi-type (car gsi-type))))
	(get type-name 'argument))))

(defun-for-macro gsi-fc-actual-argument-type (gsi-type)
  (if (keywordp gsi-type)
      gsi-type
      (or (gsi-type-specified-argument-type gsi-type)
	  ':object)))

(defun-for-macro gsi-fc-actual-return-type (gsi-type)
  (if (keywordp gsi-type)
      gsi-type
      (or (gsi-type-specified-return-type gsi-type)
	  ':object)))

(defun-for-macro gsi-fc-argument-conversion-form (gsi-type arg function-name)
  (let* ((type-name (if (atom gsi-type) gsi-type (car gsi-type)))
	 (type-arguments (if (atom gsi-type) nil (cdr gsi-type)))
	 (type-parameters (get type-name 'parameters))
	 (body (or (get type-name 'argument)
		   (error "The gsi-type ~s may not appear as an argument" ;SS_ERROR S->s
			  type-name))))
    (if (atom body)
	`(,body ,arg)
	(sublis `((<<fn_name>> . ,function-name)
		  (argument . ,arg)
		  ,@(loop for parameter in type-parameters
			  for argument in type-arguments
			  collect `(,parameter . ,argument)))
		body))))

(defun-for-macro gsi-fc-result-conversion-form (gsi-type result function-name &rest args)
  (if (keywordp gsi-type)
      result
      (let ((type-name (if (atom gsi-type) gsi-type (car gsi-type))))
	(if (and (get type-name 'return-type)
		 (not (get type-name 'result)))
	    result
	    (let* ((type-arguments (append (if (atom gsi-type) nil (cdr gsi-type))
					   args))
		   (type-parameters (get type-name 'parameters))
		   (body (or (get type-name 'result)
			     (error "The gsi-type ~s may not appear as an result" ;SS_ERROR
				    type-name))))
	      (if (atom body)
		  `(,body ,result)
		  (sublis `((<<fn_name>> . ,function-name)
			    (result . ,result)
			    ,@(loop for parameter in type-parameters
				    for argument in type-arguments
				    collect `(,parameter . ,argument)))
			  body)))))))

(defun-for-macro gsi-fc-reclaim-forms (gsi-type new-arg)
  (let* ((type-name (if (atom gsi-type) gsi-type (car gsi-type)))
	 (reclaim (get type-name 'reclaim)))
    (when reclaim
      (list `(,reclaim ,new-arg)))))

(defun-for-macro gsi-fc-return-specs (argument-specs)
  (loop for spec in argument-specs
	for (arg type) = spec
	when (and (consp type)
		  (eq (car type) 'gsi-return-value))
	  collect spec))

(defun-for-macro non-tw-return-values-argument-specs (argument-specs)
  (loop for spec in argument-specs
	for (arg type) = spec
	unless (and (consp type)
		    (eq (car type) 'tw-return-value))
	  collect spec))

(defun-for-macro transform-gsi-function-name-for-error-message (name)
  (intern
    (string-downcase
      (substitute #\_ #\- (let ((str (string name)))
			    (if (and (< #.(length "SHARED-") (length str))
				     (string= str "SHARED-" :end1 #.(length "SHARED-")))
				(subseq str #.(length "SHARED-"))
				str))))))

(defmacro def-simple-gsi-foreign-callable (name-and-options argument-specs body)
  (let* ((function-name (car name-and-options))
	 (aux-tail (member '&aux argument-specs))
	 (argument-specs (ldiff argument-specs aux-tail))
	 (argument-list (gsi-api-argument-list argument-specs))
	 (aux-bindings (cdr aux-tail))
	 (return-type
	   (second (assoc :return-type (cdr name-and-options)))))
    `(defun ,function-name ,argument-list
       ,@(when (member 'wide-api-p argument-list)
	   `((declare (ignore wide-api-p))))
       (macrolet ((return-gsi-values (&rest forms)
		    `(values ,@forms))
		  (return-tw-values (&rest forms)
		    `(values ,@forms))
		  (gsi-api-warning (code &rest args)
		    `(progn (set-gsi-error-message ,code ,@args)
		       (gsi-handle-error-1
			 ',',(transform-gsi-function-name-for-error-message function-name)
			 'warning
			 t)))
		  (gsi-api-error (code &rest args)
		    `(progn
		       (progn (set-gsi-error-message ,code ,@args)
			 (gsi-handle-error-1
			   ',',(transform-gsi-function-name-for-error-message function-name)
			   'error
			   t))
		       (return-from ,',function-name
			 ',',(case return-type
			       ((gsi-float :double-float) 0.0)
			       ((gsi-fixnum-long :fixnum-long :fixnum-int) 0)
			       (t nil))))))
	 (let* (,@aux-bindings)
	   ,@(loop for (nil type) in argument-specs
		   nconc (gsi-type-side-effects-for-type type))
	   (with-catch-unshadowed ; allow catch and unwind-protect
	     ,@body))))))

(defmacro def-gsi-chestnut-gsi-foreign-callable (name-and-options argument-specs body)
  (let* ((function-name (car name-and-options))
	 (aux-tail (member '&aux argument-specs))
	 (argument-specs (ldiff argument-specs aux-tail)))
    (with-package-specific-symbols (tx |::| def-foreign-callable
				    tx |::| foreign-type)
      (let* ((return-type (second (assoc :return-type (cdr name-and-options))))
	     (aux-vars (cdr aux-tail))
	     (argument-specs (non-tw-return-values-argument-specs argument-specs))
	     (new-outer-arguments
	       (loop for (arg type) in argument-specs
		     collect (if (gsi-fc-convert-argument-p type)
				 (build-ab-symbol :gsi-fc-outer arg)
				 nil)))
	     (actual-argument-specs
	       (loop for (arg type) in argument-specs
		     for actual-type = (gsi-fc-actual-argument-type type)
		     for new-arg in new-outer-arguments
		     collect `(,(or new-arg arg) ,actual-type)))
	     (actual-return-type (gsi-fc-actual-return-type return-type))
	     (reclaim-forms
	       (loop for (arg type) in argument-specs
		     for new-arg in new-outer-arguments
		     when new-arg
		       nconc (gsi-fc-reclaim-forms type arg)))
	     (resultp (not (or (eq actual-return-type ':null)
			       (eq actual-return-type ':void))))
	     (result-var 'gsi-fc-result)
	     (result-form
	       (gsi-fc-result-conversion-form return-type result-var function-name))
	     (argument-info-for-bindings
	       (loop for arg-spec in argument-specs
		     for new-arg in new-outer-arguments
		     when new-arg collect (cons new-arg arg-spec)))
	     (argument-info-for-bindings-in-order
	       (append (loop for info in argument-info-for-bindings
			     for (new-arg arg type) = info
			     when (atom type) collect info)
		       (loop for info in argument-info-for-bindings
			     for (new-arg arg type) = info
			     unless (atom type) collect info)))	       
	     (argument-bindings
	       (loop for (new-arg arg type) in argument-info-for-bindings-in-order
		     collect `(,arg ,(gsi-fc-argument-conversion-form
				       type new-arg function-name)))))
	`(def-foreign-callable (,function-name
				  (:return-type ,actual-return-type))
	     ,actual-argument-specs
	   (macrolet ((gsi-api-error-reclaim ()
			nil)
		      (gsi-api-warning (code &rest args)
			`(progn (set-gsi-error-message ,code ,@args)
			   (gsi-handle-error-1
			     ',',(transform-gsi-function-name-for-error-message function-name)
			     'warning
			     t)))
		      (gsi-api-error (code &rest args)
			`(progn
			   (progn (set-gsi-error-message ,code ,@args)
			     (gsi-handle-error-1
			       ',',(transform-gsi-function-name-for-error-message function-name)
			        'error
				t))
			   (gsi-api-error-reclaim)
			   (return-from ,',function-name
			     ',',(case return-type
				   ((gsi-float :double-float) 0.0)
				   ((gsi-fixnum-long :fixnum-long :fixnum-int) 0)
				   (t nil))))))
	     (let* (,@aux-vars ,@argument-bindings)
	       (macrolet ((gsi-api-error-reclaim ()
			    `(progn ,@',reclaim-forms)))
		 (with-catch-unshadowed
		   ,(if resultp
			`(let ((,result-var (progn ,@body)))
			   (declare (foreign-type ,actual-return-type ,result-var))
			   ,@reclaim-forms
			   ,result-form)
			`(macrolet
			     ((return-gsi-values (&rest forms)
				(let ((return-specs
					',(gsi-fc-return-specs argument-specs)))
				  `(progn
				     ,@(loop for form in forms
					     for (arg type) in return-specs
					     collect (gsi-fc-result-conversion-form
						       type form ',function-name arg)))))
			      (return-tw-values (&rest forms)
				(declare (ignore forms))
				nil))
			   ,@body
			   ,@reclaim-forms
			   nil)))))))))))

(defmacro def-gsi-foreign-callable (name-and-options argument-specs &body body)
  `(if-chestnut-gsi
     (def-gsi-chestnut-gsi-foreign-callable ,name-and-options ,argument-specs ,body)
     (def-simple-gsi-foreign-callable ,name-and-options ,argument-specs ,body)))

(defmacro typed-assign-value-to-c-pointer (type pointer-variable result)
  (ecase type
    (:object `(inline-assign-value-to-c-pointer ,pointer-variable ,result))
    (:fixnum `(inline-assign-fixnum-to-c-pointer ,pointer-variable ,result))))

(define-gsi-type gsi-return-value (type pointer-variable)
  (argument-type :object)
  (result (typed-assign-value-to-c-pointer type pointer-variable result)))

(define-gsi-type gsi-float ()
  (argument-type :double-float)
  (return-type :double-float)
  (argument gsi-maybe-swap-float-bytes-for-alpha-gfloats)
  (result gsi-maybe-swap-float-bytes-for-alpha-gfloats))

(defmacro gsi-maybe-swap-float-bytes-for-alpha-gfloats (float)
  `(inline-maybe-swap-float-bytes-for-alpha-gfloats
     ,float
     (if (gsi-option-is-set-p gsi-use-gfloats) 1 0)))

(define-gsi-type gsi-fixnum-long ()
  (argument-type :fixnum-long)
  (return-type :fixnum-long)
  (argument verify-gsi-fixnum-long))

(defmacro verify-gsi-fixnum-long (x)
  `(let ((value ,x))
     (when (< most-positive-fixnum value)
       (gsi-api-error gsi-integer-too-large))
     (when (< value most-negative-fixnum)
       (gsi-api-error gsi-integer-too-small))
     value))

;added by SoftServe

(define-gsi-type gsi-long ()
  (argument-type :object)
  (return-type :object)
)  

;end of changes

(define-gsi-type gsi-symbol ()
  (stringp   t)
  (argument  gsi-api-c-string-or-null-to-symbol-or-nil)
  (result    symbol-or-nil-to-gsi-api-c-string-or-null))

;used by gsi-set-class-name, gsi-class-name-of,...
(define-gsi-type gsi-symbol-or-nil ()
  (stringp   t)
  (argument  gsi-api-c-string-or-null-to-symbol-or-nil)
  (result    symbol-or-nil-to-gsi-api-c-string-or-null))

(define-gsi-type gsi-api-symbol ()
  (stringp   t)
  (argument  gsi-api-symbol-to-symbol-or-nil)
  (result    symbol-or-nil-to-gsi-api-symbol))

(define-gsi-type gsi-string ()
  (stringp   t)
  (argument  gsi-api-c-string-to-gsi-string)
  (result    lisp-string-to-gsi-api-c-string)
  (reclaim   reclaim-text-or-gensym-string))

(define-gsi-type permanent-gsi-string ()
  (stringp   t)
  (argument  gsi-api-c-string-to-gsi-string)
  (result    lisp-string-to-gsi-api-c-string))

(define-gsi-type gsi-string-or-null ()
  (stringp   t)
  (argument  gsi-api-c-string-or-null-to-gsi-string-or-nil)
  (result    lisp-string-or-nil-to-gsi-api-c-string-or-null)
  (reclaim   reclaim-if-text-or-gensym-string))


(define-gsi-type text-string ()
  (stringp   t)
  (argument  gsi-api-c-string-to-text-string)
  (result    lisp-string-to-gsi-api-c-string)
  (reclaim   reclaim-text-or-gensym-string))

(define-gsi-type permanent-text-string ()
  (stringp   t)
  (argument  gsi-api-c-string-to-text-string)
  (result    lisp-string-to-gsi-api-c-string))

(define-gsi-type text-string-or-null ()
  (stringp   t)
  (argument  gsi-api-c-string-or-null-to-text-string-or-nil)
  (result    lisp-string-or-nil-to-gsi-api-c-string-or-null)
  (reclaim   reclaim-if-text-or-gensym-string))


(define-gsi-type gensym-string ()
  (stringp   t)
  (argument  gsi-api-c-string-to-gensym-string)
  (result    lisp-string-to-gsi-api-c-string)
  (reclaim   reclaim-text-or-gensym-string))

(define-gsi-type gensym-string-or-null ()
  (stringp   t)
  (argument  gsi-api-c-string-or-null-to-gensym-string-or-nil)
  (result    lisp-string-or-nil-to-gsi-api-c-string-or-null)
  (reclaim   reclaim-if-text-or-gensym-string))

(define-gsi-type gsi-api-text-string ()
  (stringp   t)
  (argument  c-wide-string-to-text-string)
  (result    lisp-string-to-c-wide-string)
  (reclaim   reclaim-if-text-or-gensym-string))

(define-gsi-type gsi-api-gensym-string ()
  (stringp   t)
  (argument  c-string-to-gensym-string)
  (result    lisp-string-to-c-string)
  (reclaim   reclaim-if-text-or-gensym-string))

(define-gsi-type unsigned-short-vector (len)
  (stringp   t)
  (argument  (c-unsigned-short-vector-to-text-string argument len))
  (result    lisp-string-to-c-unsigned-short-vector)
  (reclaim   reclaim-if-text-or-gensym-string))

(define-gsi-type permanent-unsigned-short-vector (len)
  (stringp   t)
  (argument  (c-unsigned-short-vector-to-text-string argument len))
  (result    lisp-string-to-c-unsigned-short-vector))

(defmacro gsi-api-c-string-to-gsi-string (string)
  `(if wide-api-p ; a bound lexical.  see def-gsi-api-function.
       (c-wide-string-to-gsi-string ,string)
       (c-string-to-gsi-string ,string)))

(defmacro gsi-api-c-string-to-gensym-string (string)
  `(if wide-api-p ; a bound lexical.  see def-gsi-api-function.
       (c-wide-string-to-gensym-string ,string)
       (c-string-to-gensym-string ,string)))

(defmacro gsi-api-c-string-to-text-string (string)
  `(if wide-api-p ; a bound lexical.  see def-gsi-api-function.
       (c-wide-string-to-text-string ,string)
       (c-string-to-text-string ,string)))

(defmacro gsi-api-c-string-or-null-to-gsi-string-or-nil (string)
  `(if (null ,string)
       nil
       (gsi-api-c-string-to-gsi-string ,string)))

(defmacro gsi-api-c-string-or-null-to-gensym-string-or-nil (string)
  `(if (null ,string)
       nil
       (gsi-api-c-string-to-gensym-string ,string)))

(defmacro gsi-api-c-string-or-null-to-text-string-or-nil (string)
  `(if (null ,string)
       nil
       (gsi-api-c-string-to-text-string ,string)))

(defmacro gsi-api-c-string-or-null-to-symbol-or-nil (string)
  `(if (null ,string)
       nil
       (symbol-for-gsi-string
	 (if wide-api-p ; a bound lexical.  see def-gsi-api-function.
	     (c-wide-string-to-text-string ,string)
	     (c-string-to-gensym-string ,string)))))

(defun-simple gsi-api-symbol-to-symbol-or-nil-1 (api-symbol wide-api-p)
  (if (gsi-option-is-set-p gsi-new-symbol-api)
      api-symbol
      (gsi-api-c-string-or-null-to-symbol-or-nil api-symbol)))

(defmacro gsi-api-symbol-to-symbol-or-nil (api-symbol)
  `(let ((arg-symbol (gsi-api-symbol-to-symbol-or-nil-1
		       ,api-symbol
		       (using-wide-gsi-api-p))))
     (unless (symbolp arg-symbol)
       (gsi-api-error gsi-not-a-symbol))
     arg-symbol))

(defmacro lisp-string-to-gsi-api-c-string (string)
  `(if wide-api-p ; a bound lexical.  see def-gsi-api-function.
       (lisp-string-to-c-wide-string ,string)
       (lisp-string-to-c-string ,string)))

(defmacro lisp-string-or-nil-to-gsi-api-c-string-or-null (string)
  `(if (null ,string)
       nil
       (lisp-string-to-gsi-api-c-string ,string)))

(defmacro symbol-or-nil-to-gsi-api-c-string-or-null (symbol)
  `(if (null ,symbol)
       nil
       (let ((string (gsi-string-for-symbol ,symbol wide-api-p)))
	 (lisp-string-to-gsi-api-c-string string))))

(defmacro symbol-or-nil-to-gsi-api-symbol (symbol)
  `(if (gsi-option-is-set-p gsi-new-symbol-api)
       ,symbol
       (symbol-or-nil-to-gsi-api-c-string-or-null ,symbol)))

;used by gsi-rpc-start,...
(define-gsi-type gsi-temporary-displaced-array (len)
  (argument (if argument
		(gsi-displaced-array-from-c-contents argument len)
		nil))
  (reclaim gsi-reclaim-displaced-array))

;used by gsi-reclaim-items
(define-gsi-type gsi-managed-array-with-unspecified-length ()
  (argument (if (gsi-null-c-pointer-p argument)
		nil
		(gsi-get-array-from-c-contents argument))))

;used by gsi-set-attrs, gsi_make_items
(define-gsi-type gsi-managed-array (len)
  (argument (if (>f len 0)
		(let* ((array (gsi-get-array-from-c-contents argument))
		       (array-size (gsi-managed-array-length array))
		       (array-element-count (-f array-size gsi-magic-offset)))
		  (when (>f len array-element-count)
		    (gsi-api-error gsi-count-out-of-array-bounds
				   len array-element-count))
		  array)
		nil))
  ;; (allocated by: (gsi-allocate-managed-array (+f len gsi-magic-offset)))
  (result (if (>f len 0)
	      (progn
		(gsi-set-up-array-for-c-access result) 
		(gsi-extract-c-array result))
	      nil)))

(defun-for-macro type-tag-from-gsi-type (gsi-type)
  (unless (and (consp gsi-type) (eq (car gsi-type) 'gsi-typed-array))
    (error "type-tag-from-gsi-type does not support gsi type ~s" gsi-type)) ;SS_ERROR
  (gsi-typed-array-type-tag (cadr gsi-type) (caddr gsi-type)))

(defun-for-macro gsi-typed-array-type-tag (element-type list-or-array)
  (ecase list-or-array
    (list
      (ecase element-type
	(integer     'gsi-integer-list-type-tag)
	(64bit-float 'gsi-64bit-float-list-type-tag)
	(logical     'gsi-logical-list-type-tag)
	(symbol      'gsi-symbol-list-type-tag)
	(string      'gsi-string-list-type-tag)))
    (array
      (ecase element-type
	(integer     'gsi-integer-array-type-tag)
	(64bit-float 'gsi-64bit-float-array-type-tag)
	(logical     'gsi-logical-array-type-tag)
	(symbol      'gsi-symbol-array-type-tag)
	(string      'gsi-string-array-type-tag)))))

(defmacro array-type-tag (element-type)
  (gsi-typed-array-type-tag element-type 'array))

(defmacro typed-vector-aref (element-type array index)
  (ecase element-type
    (integer     `(integer-vector-aref ,array ,index))
    (64bit-float `(float-vector-aref ,array ,index))
    (logical     `(integer-vector-aref ,array ,index))
    (symbol      `(gsi-managed-svref ,array ,index))
    (string      `(gsi-managed-svref ,array ,index))))

(defmacro gsi-coerce-string-to-string-array-element (string)
  `(inline-extract-c-string ,string)) ; now equivalent to inline-extract-c-wide-string

(defmacro gsi-coerce-string-array-element-to-string (element)
  `(let ((element ,element))
     (if (null element)
         (if (using-wide-gsi-api-p)
	     #w""
	     "")
         (if (using-wide-gsi-api-p)
	     (inline-restore-lisp-text-string element)
	     (inline-restore-lisp-gensym-string element)))))

(def-global-property-name gsi-encoded-symbol-names)

(defun-simple gsi-string-for-symbol (symbol wide-api-p)
  (if wide-api-p
      (symbol-name-text-string symbol)
      (let ((style-number (current-gsi-string-conversion-style)))
	(if (=f 0 style-number)
	    (symbol-name symbol)
	    (let ((name-plist (gsi-encoded-symbol-names symbol)))
	      (or (getfq name-plist style-number)
		  (let* ((string (wide-string-to-gensym-string-for-gsi
				   (symbol-name-text-string symbol)))
			 (new-name-plist
			   (gensym-cons style-number (gensym-cons string name-plist))))
		    (setf (gsi-encoded-symbol-names symbol) new-name-plist)
		    string)))))))

(defun-simple symbol-for-gsi-string (string)
  (gsi-intern
    (if (wide-string-p string)
	string
	(if (=f 0 (current-gsi-string-conversion-style))
	    string
	    (prog1 (gensym-string-to-wide-string-for-gsi string)
	      (reclaim-gensym-string string))))))

(defmacro gsi-coerce-symbol-to-symbol-array-element-1 (symbol)
  `(inline-extract-c-string ; now equivaluent to inline-extract-c-wide-string
     (gsi-string-for-symbol ,symbol (using-wide-gsi-api-p))))

(defmacro gsi-coerce-symbol-to-symbol-array-element (symbol)
  `(let ((symbol ,symbol))
     (if (gsi-option-is-set-p gsi-new-symbol-api)
	 symbol
	 (gsi-coerce-symbol-to-symbol-array-element-1 symbol))))

(defmacro gsi-coerce-symbol-array-element-to-symbol (element)
  `(let ((element ,element))
     (if (gsi-option-is-set-p gsi-new-symbol-api)
	 element
       	 (if (null element)
	     nil
	     (symbol-for-gsi-string
	       (if (using-wide-gsi-api-p)
		   (c-wide-string-to-text-string element)
		   (c-string-to-gensym-string element)))))))

(defmacro typed-get-c-element (element-type c-array index)
  (ecase element-type
    (integer     `(the (signed-byte 32)    (inline-get-c-long-element   ,c-array ,index)))
    (64bit-float `(the gensym-float        (inline-get-c-double-element ,c-array ,index)))
    (logical     `(the fixnum              (inline-get-c-long-element   ,c-array ,index)))
    (symbol      `(if (gsi-option-is-set-p gsi-new-symbol-api)
		      (inline-get-c-char-ptr-element ,c-array ,index)
		      (let* ((api-c-string
			       (if wide-api-p
				   (inline-get-c-wide-char-ptr-element ,c-array ,index)
				   (inline-get-c-char-ptr-element ,c-array ,index)))
			     (symbol (gsi-api-c-string-or-null-to-symbol-or-nil api-c-string)))
			(gsi-coerce-symbol-to-symbol-array-element-1 symbol))))		      
    (string      `(gsi-coerce-string-to-string-array-element
		    (let ((api-c-string
			    (if wide-api-p
				(inline-get-c-wide-char-ptr-element ,c-array ,index)
				(inline-get-c-char-ptr-element ,c-array ,index))))
		      (gsi-api-c-string-to-gsi-string api-c-string))))))

(defmacro typed-read-icp-value-to-c-element (element-type)
  (ecase element-type
    (integer     `(the fixnum       (read-icp-fixnum)))
    (64bit-float `(the gensym-float (read-icp-double-float-1)))
    (logical     `(the fixnum       (read-icp-fixnum)))
    (symbol      `(gsi-coerce-symbol-to-symbol-array-element
		    (read-icp-possibly-interned-symbol)))
    (string      `(gsi-coerce-string-to-string-array-element
		    (convert-value-to-gsi-value (read-icp-text-string))))))

(defmacro typed-extract-c-array (element-type array)
  (ecase element-type
    (integer     `(gsi-extract-c-long-array   ,array))
    (64bit-float `(gsi-extract-c-double-array ,array))
    (logical     `(gsi-extract-c-long-array   ,array))
    (symbol      `(gsi-extract-c-long-array   ,array)) ; Is this right?
    (string      `(gsi-extract-c-long-array   ,array))))

(defmacro copy-c-array-into-array (element-type c-array array len)
  `(loop for index fixnum from 0 below ,len
	 do
     (setf (typed-vector-aref ,element-type ,array index)
	   (typed-get-c-element ,element-type ,c-array index))))

(defmacro verify-c-array (element-type c-array len)
  (when (eq element-type 'integer)
    `(loop for index fixnum from 0 below ,len
	   do
       (verify-gsi-fixnum-long
	 (typed-get-c-element ,element-type ,c-array index)))))

(defmacro gsi-typed-array-ref (element-type array index)
  (ecase element-type
    (integer     `(typed-vector-aref ,element-type ,array ,index))
    (64bit-float `(allocate-managed-float ; allocates, so users of gsi-typed-array-ref must reclaim
		    (typed-vector-aref ,element-type ,array ,index)))
    (logical     `(typed-vector-aref ,element-type ,array ,index))
    (symbol      `(gsi-coerce-symbol-array-element-to-symbol
		    (typed-vector-aref ,element-type ,array ,index))) 
    (string      `(gsi-coerce-string-array-element-to-string
		    (typed-vector-aref ,element-type ,array ,index)))
    (gsi-item    `(gsi-managed-svref ,array (+f ,index gsi-magic-offset)))))

(defmacro gsi-typed-array-set (element-type array index new-value)
  (ecase element-type
    (integer     `(setf (typed-vector-aref ,element-type ,array ,index) ,new-value))
    (64bit-float `(setf (typed-vector-aref ,element-type ,array ,index)
			(managed-float-value ,new-value)))
    (logical     `(setf (typed-vector-aref ,element-type ,array ,index) ,new-value))
    (symbol      `(setf (typed-vector-aref ,element-type ,array ,index)
			(gsi-coerce-symbol-to-symbol-array-element ,new-value)))
    (string      `(setf (typed-vector-aref ,element-type ,array ,index)
			(gsi-coerce-string-to-string-array-element ,new-value)))
    (gsi-item    `(setf (gsi-managed-svref ,array (+f ,index gsi-magic-offset)) ,new-value))))

(defsetf gsi-typed-array-ref gsi-typed-array-set)

(define-gsi-type gsi-typed-array (element-type list-or-array len instance?)
  (argument (progn
	      (setf (gsi-element-count instance?) len)
	      (unless (<f len 1)
		(verify-c-array element-type argument len)
		(let ((array (gsi-make-appropriate-array
			       (array-type-tag element-type)
			       len instance?)))
		  (copy-c-array-into-array element-type argument array len)
		  array))))
  (result (if (>f (gsi-element-count instance?) 0)
	      (typed-extract-c-array element-type result)
	      nil)))

(defmacro dynamic-extract-c-array (element-type-tag c-array otherwise)
  `(case ,element-type-tag
     ((#.gsi-integer-type-tag
       #.gsi-logical-type-tag
       #.gsi-symbol-type-tag
       #.gsi-string-type-tag
       #.gsi-unsigned-short-vector-type-tag)
      (gsi-extract-c-long-array ,c-array))
     (#.gsi-64bit-float-type-tag
      (gsi-extract-c-double-array ,c-array))
     ((#.gsi-value-type-tag #.gsi-quantity-type-tag)
      (gsi-extract-c-array ,c-array))
     (t
      ,otherwise)))

(defmacro dynamic-copy-c-array-into-array (element-type-tag c-array array len otherwise)
  `(case ,element-type-tag
     ((#.gsi-integer-type-tag
       #.gsi-logical-type-tag)
      (copy-c-array-into-array integer     ,c-array ,array ,len))
     (#.gsi-64bit-float-type-tag
      (copy-c-array-into-array 64bit-float ,c-array ,array ,len))
     (#.gsi-string-type-tag
      (copy-c-array-into-array string      ,c-array ,array ,len))
     (#.gsi-symbol-type-tag
      (copy-c-array-into-array symbol      ,c-array ,array ,len))
     (t
      ,otherwise)))

(defmacro gsi-array-element-type-case (element-type-tag body-macro)
  `(case ,element-type-tag
     ((#.gsi-integer-type-tag
       #.gsi-logical-type-tag)
      (,body-macro integer))
     (#.gsi-64bit-float-type-tag
      (,body-macro 64bit-float))
     (#.gsi-string-type-tag
      (,body-macro string))
     (#.gsi-symbol-type-tag
      (,body-macro symbol))))
  


(defmacro within-gsi-context (context &body body)
  `(let ((derived-socket (resolve-gsi-context-for-writing ,context)))
     ,@body))

(defmacro with-gsi-message-group-context (context &body body)
  `(within-gsi-context ,context
     (writing-icp-message-group ((icp-output-port derived-socket))
       ,@body)
     (gsi-flush-internal)))

;; If place-of-list has any side-effects, they will happen twice - this is bad. -paf! 21sep94
(defmacro gsi-reclaim-contents-and-clear-list (place-of-list user-or-gsi)
  `(progn
    (gsi-reclaim-contents ,place-of-list ,user-or-gsi)
    (setf ,place-of-list nil)))

(def-side-effect-free-inlined-pseudo-function inline-extract-c-array (array offset)
  (declare (ignore offset))
  array)

(def-side-effect-free-inlined-pseudo-function inline-extract-c-long-array (array)
  array)

(def-side-effect-free-inlined-pseudo-function inline-extract-c-double-array (array)
  array)

;; jh, 4/6/95.  Moved inline-extract-c-string and inline-restore-lisp-string to
;; UTILITIES3, because I'm not sure how to forward reference such things.

(def-side-effect-free-inlined-pseudo-function inline-get-array-from-c (array magic-header-offset)
  (declare (ignore magic-header-offset))
  array)

(def-side-effect-free-inlined-pseudo-function inline-gsi-get-magic-header (array)
  (declare (ignore array))
  gsi-magic-number)

(def-side-effect-free-inlined-pseudo-function inline-get-c-wide-string-element (c-wide-string index)
  (charw c-wide-string index))

(def-side-effect-free-inlined-pseudo-function (inline-get-c-long-element :long)
    (c-array (index :fixnum))
  (gsi-managed-svref c-array index))

(def-side-effect-free-inlined-pseudo-function (inline-get-c-double-element :double-float)
    (c-array (index :fixnum))
  (gsi-managed-svref c-array index))

(def-side-effect-free-inlined-pseudo-function inline-get-c-char-ptr-element (c-array index)
  (gsi-managed-svref c-array index))

(def-side-effect-free-inlined-pseudo-function inline-get-c-wide-char-ptr-element (c-array index)
  (gsi-managed-svref c-array index))

(def-side-effect-free-inlined-pseudo-function inline-get-length-of-c-wide-string (c-wide-string)
  (lengthw c-wide-string))

(def-inlined-pseudo-function-with-side-effects inline-assign-value-to-c-pointer (c-pointer value)
  (setf (svref c-pointer 0) value))  ; use arrays of length one to fake c pointers in LISP bridges.

(def-inlined-pseudo-function-with-side-effects inline-assign-fixnum-to-c-pointer (c-pointer fixnum)
  (setf (svref c-pointer 0) fixnum))
  
(def-inlined-pseudo-function-with-side-effects inline-assign-double-to-c-pointer
    (c-pointer double-value)
  (setf (svref c-pointer 0) double-value))

(def-inlined-pseudo-function-with-side-effects (inline-set-gsi-error-variable
						 :fixnum "inline_assign_ref")
    ((error-location :object) (error-code :fixnum))
  (set error-location error-code))

(defmacro define-inline-c-function-call-macro (name args+types &body forms)
  #| #-development
  (current-system-case
    ((gsi #+gsi-in-g2 ab))
    (t (setq args+types (loop for (arg type) in args+types
			      collect `(,arg :object)))))
  |#
  `(def-inlined-pseudo-function-with-side-effects ,name ,args+types ,@forms))

(define-inline-c-function-call-macro inline-c-function-call
    ((function :object) (arguments :object) (count :fixnum-long) (call-handle :object))
  (funcall function arguments count call-handle))

(define-inline-c-function-call-macro inline-c-return-function-call
    ((function :object) (arguments :object) (count :fixnum-long))
  (funcall function arguments count))

(define-inline-c-function-call-macro inline-c-return-function-call-with-index
    ((function :object) (arguments :object) (count :fixnum-long) (call-index :object))
  (funcall function arguments count call-index))

(define-inline-c-function-call-macro inline-c-function-call-user-data
    ((function :object) (user-data :object) (arguments :object) (count :fixnum-long) (call-handle :object))
  (funcall function user-data arguments count call-handle))

(define-inline-c-function-call-macro inline-c-return-function-call-user-data
    ((function :object) (user-data :object) (arguments :object) (count :fixnum-long))
  (funcall function user-data arguments count))

(define-inline-c-function-call-macro inline-c-return-function-call-with-index-and-user-data
    ((function :object) (user-data :object) (arguments :object) (count :fixnum-long) (call-user-data :object))
  (funcall function user-data arguments count call-user-data))

(def-side-effect-free-inlined-pseudo-function inline-dereference-c-pointer (c-pointer)
  c-pointer)

(def-side-effect-free-inlined-pseudo-function inline-increment-c-pointer (c-pointer)
  c-pointer)

(def-inlined-pseudo-function-with-side-effects inline-copy-byte-vector-16-portion-c-to-lisp
    (c-wide-string
     (start-c :fixnum-long)
     (lisp-wide-string  :16-bit-unsigned-array)
     (start-lisp :fixnum-long)
     (count :fixnum-long))
  (inline-copy-byte-vector-16-portion
    c-wide-string start-c lisp-wide-string start-lisp count))

(defmacro gsi-extract-c-array (array)
  `(inline-extract-c-array ,array gsi-magic-offset))

(defmacro gsi-extract-c-long-array (array)
  `(inline-extract-c-long-array ,array))

(defmacro gsi-extract-c-double-array (array)
  `(inline-extract-c-double-array ,array))

(defmacro gsi-extract-c-string (array)
  `(inline-extract-c-string ,array))

(defmacro gsi-dereference-external-pointer (pointer)
  `(inline-dereference-external-pointer ,pointer))

(defmacro gsi-get-array-from-c-contents (c-array)
  (avoiding-variable-capture (c-array)
    `(let ((magic-number (inline-gsi-get-magic-header ,c-array)))
      (if (=f magic-number ,gsi-magic-number)
	  (inline-get-array-from-c ,c-array gsi-magic-offset)
	  (gsi-api-error gsi-bad-magic-number)))))

(defmacro gsi-set-up-array-for-c-access (array)
  `(setf (gsi-managed-svref ,array 0) gsi-magic-number))

(defmacro gsi-assign-value-to-c-pointer (c-pointer value)
  `(inline-assign-value-to-c-pointer ,c-pointer ,value))

(defmacro gsi-funcall (function arguments count call-handle)
  `(inline-c-function-call ,function ,arguments ,count ,call-handle))

(defmacro gsi-funcall-with-user-data (function user-data arguments count call-handle)
  `(inline-c-function-call-user-data ,function ,user-data ,arguments ,count ,call-handle))

(defmacro gsi-return-funcall (function arguments count call-index)
  `(if-chestnut-gsi
     (inline-c-return-function-call-with-index ,function ,arguments ,count ,call-index)
     (inline-c-return-function-call-with-index ,function ,arguments ,count ,call-index)))

(defmacro gsi-return-funcall-with-user-data (function user-data arguments count call-index)
  `(if-chestnut-gsi
     (inline-c-return-function-call-with-index-and-user-data ,function ,user-data ,arguments ,count ,call-index)
     (inline-c-return-function-call-with-index-and-user-data ,function ,user-data ,arguments ,count ,call-index)))


;;; Real GSI user code is (typically) written in C and does not differentiate between
;;; symbols and strings.  However for internal testing purposes, user code is sometimes
;;; written in LISP which of course does support symbols.  Therefore, when the GSI API
;;; passes to user code what is internally a symbol, it must be converted to a string
;;; unless we are running in a LISP environment in which case GSI is running with LISP
;;; user code.	To support this case of an `outgoing-symbol' the split function
;;; `gsi-outgoing-symbol-name' is provided.  In the converse case where user code passes
;;; a value into a GSI API function expecting a string (an `incoming-symbol'), the split
;;; function `gsi-incoming-symbol-name' is provided for LISP user code which would be
;;; passing in a symbol whose symbol name would need to be extracted. paf! 22aug94

(defmacro def-gsi-split-function  (fname fnargs (&body c) (&body lisp))
  `(progn
     (defun ,fname ,fnargs 
       ,@(if (and (eval-feature :chestnut-3)
		  (eval-feature :chestnut-trans))
	     c
	     lisp))))

; No longer used.  - rh 6/21/96
(def-gsi-split-function gsi-incoming-symbol-name (symbol) 
  (symbol)                     ; C - no need to extract string
  ((symbol-name-text-string symbol)))      ; LISP - extract string

; No longer used.  - rh 6/22/96
(def-gsi-split-function gsi-outgoing-symbol-name (symbol?) 
  ((if symbol?			; C - never give C code...
       (inline-extract-c-string (symbol-name symbol?))
       nil))			;		      ...a real symbol
  (symbol?))			; LISP - give it to the user code straight

;; jh, 4/20/97.  Moved c-string-to-gensym-string and supporting mechanism to
;; UTILITIES3 so that (old) Telewindows can use it in its OLE implementation.

(defun-simple c-string-to-text-string (c-string)
  (let* ((gensym-string (c-string-to-gensym-string c-string))
	 (text-string (gensym-string-to-wide-string-for-gsi gensym-string)))
    (reclaim-gensym-string gensym-string)
    text-string))


;;; The function `c-wide-string-to-text-string' takes c-wide-string, an unsigned
;;; short array, which is being passed from a C routine, and creates
;;; lisp-string, a wide string object, which is, at the C level, an unsigned
;;; short array after some offsets for Chestnut.  The contents of c-wide-string
;;; are copied to lisp-string, which is then returned.  The function
;;; `c-unsigned-short-vector-to-text-string' is similar but takes a length
;;; argument.
;;;
;;; NOTE: this also, for now, seems to accept NIL as its argument, and returns a
;;; new, zero-length string in that case; however, I'm not sure that's needed
;;; functionality.  Do not write new code that depends on that without
;;; documenting it here. (MHD 2/27/04)

(defun-simple c-wide-string-to-text-string (c-wide-string)
  (if (null c-wide-string)		; see note
      (make-wide-string 0)
      (let* ((length (inline-get-length-of-c-wide-string c-wide-string))
	     (lisp-string (make-wide-string length)))
	(declare (type fixnum length))
	(inline-copy-byte-vector-16-portion-c-to-lisp
	  c-wide-string 0 lisp-string 0 length)
	lisp-string)))

;; Functions above and below optimized today to use, at the lowest level, memcpy
;; to move the data from the "C" string to the "Lisp" string. (MHD 2/27/04)

;; Note: I'm not sure if or why the above function should have to check for
;; c-wide-string being null, but that check was there, so I didn't want to
;; change it at this time, but I'd ideally like to remove it.  The way it is
;; now, there is a bit of extra code in the emitted C.  Review later, and
;; document it if it stays the way it is!  (MHD 2/27/04)



(defun-simple c-unsigned-short-vector-to-text-string (c-unsigned-short-vector length)
  (declare (type fixnum length))
  (let* ((lisp-string (make-wide-string length)))
    (inline-copy-byte-vector-16-portion-c-to-lisp
      c-unsigned-short-vector 0 lisp-string 0 length)
    lisp-string))

(defun-simple c-wide-string-to-gensym-string (c-wide-string)
  (if (null c-wide-string)		; see note
      (make-wide-string 0)
      (let* ((length (inline-get-length-of-c-wide-string c-wide-string))
	     (lisp-string (make-wide-string length)))
	(declare (type fixnum length))
	(inline-copy-byte-vector-16-portion-c-to-lisp
	  c-wide-string 0 lisp-string 0 length)
	lisp-string))
  (let* ((text-string (c-wide-string-to-text-string c-wide-string))
	 (gensym-string (wide-string-to-gensym-string-for-gsi text-string)))
    (reclaim-text-string text-string)
    gensym-string))

(defvar temporary-string-buffer nil)

(defun-simple lisp-string-to-c-string (string)
  (inline-extract-c-string
    (if (not (wide-string-p string))
	string
	(progn
	  (when temporary-string-buffer
	    (reclaim-text-or-gensym-string temporary-string-buffer))
	  (setq temporary-string-buffer
		(wide-string-to-gensym-string-for-gsi string))))))

(defun-simple lisp-string-to-c-wide-string (string)
  (inline-extract-c-wide-string 
    (if (wide-string-p string)
	string
	(progn
	  (when temporary-string-buffer
	    (reclaim-text-or-gensym-string temporary-string-buffer))
	  (setq temporary-string-buffer
		(gensym-string-to-wide-string-for-gsi string))))))

(defun-simple lisp-string-to-c-unsigned-short-vector (string)
  (inline-extract-c-wide-string string))

(defun-simple gensym-string-to-wide-string-for-gsi (string)
  (runtime-current-system-case
    (gsi (import-text-string-per-text-conversion-style
	   string
	   (text-conversion-style-for-gsi
	     (current-gsi-string-conversion-style)
	     nil)
	   nil nil))
    (t   (gensym-string-to-wide-string string))))

(defun-simple wide-string-to-gensym-string-for-gsi (string)
  (runtime-current-system-case
    (gsi (export-text-string-per-text-conversion-style
	   string
	   (text-conversion-style-for-gsi
	     (current-gsi-string-conversion-style)
	     nil)
	   nil nil))
    (t   (wide-string-to-gensym-string string))))





;;; Declaration:     c-string-to-gensym-string c-string
;;; Type:            lisp macro
;;; Purpose:         Convert a c-string passed in via the FFI as a LISP :object
;;;                  into a lisp string, bypassing the FFI which would leak memory.
;;; Return behavior: returns a lisp string, allocated with obtain-simple-gensym-string.
;;; Users:           various GSI API functions
;;; Prerequisites:   c-string points at a bona fide C style null terminated string.
;;; Side effects:    NONE
;;; Non-local exits: NONE
;;; Memory impact:   allocates a lisp string to hold a copy of the input C string.
;;; Notes:
;;;


(defun gsi-reclaim-displaced-array (displaced-array?)
  (when displaced-array?
    (gsi-reclaim-managed-array displaced-array?)))







;; GSI-TIMESTAMP-UPPER-BOUND
;;
;; Maximum number of seconds to allow as a timestamp value for GSI.  This is the
;; number of seconds from midnight 1 jan 1970 to 23:59:59 12/31/2037.  This
;; limit is close to the limit imposed by the operating systems we use (all
;; currently implement the POSIX specified type time_t as a long, which is 32
;; bits everywhere but the alpha).  Therefore the real upper limit is 2^31 - 1
;; (since despite what POSIX says most systems seem to be returning a SIGNED
;; LONG) and 2^31-1 works out to 22:14:07 1/18/2038.  Seems better to me to make
;; a clean break at the end of 2037.  The alpha is of course another story,
;; a 64 bit story, but that's just tough for now.  2037 it is.  -ncc, 7/26/94
;;
(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant gsi-timestamp-upper-bound 2145934799.0)
)

;;;; ICP Value Readers and Writers

;;; Declaration:     with-guarded-timestamp
;;;                    ((timestamp) &rest body)
;;; Type:		 Lisp macro.
;;; Purpose:	     Warn the user if a GSI sensor receives an invalid timestamp.
;;; Arguments:	     Executes body unless the following constraints are violated:
;;;                   timestamp is a positive gensym-float
;;;                  If a constraint is violated, this macro posts a logbook message
;;;                  and declines to execute body.
;;; Return behavior: No useful value is returned, even if no constraint was
;;;                  violated.
;;; Users:	     GSI internals:
;;;                    receive-value-for-gsi-sensor-with-timestamp
;;;                    receive-timestamped-gsi-sensor-value-vector
;;; Prerequisites:   notify-user machinery must be set up.
;;; Side effects:    Can post a logbook message.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defun-simple notify-user-of-out-of-bounds-timestamp (where timestamp)
  (notify-user-if-possible
    "Out-of-range timestamp seen in ~a:~%~
     timestamp: ~d  Valid range: 0.0 < t < ~d"
    where
    timestamp
    gsi-timestamp-upper-bound))

(defun-for-macro with-guarded-timestamp-body (where timestamp api-p body)
  (let ((timestamp-var (make-symbol "TIMESTAMP")))
    `(let ((,timestamp-var (inline-convert-from-local-float-format
			     ,timestamp
			     (if-chestnut-gsi
			       (if (gsi-option-is-set-p gsi-use-gfloats) 1 0)
			       -1))))
       (if (and (>e ,timestamp-var 0.0)
		(<e ,timestamp-var ,gsi-timestamp-upper-bound))
	   (progn ,@body)
	   
	   (current-system-case
	     (ab
	       (notify-user-of-out-of-bounds-timestamp ,where ,timestamp-var))
	     (gsi
	       ,(if api-p
		    `(gsi-api-error gsi-timestamp-out-of-bounds
				    ,timestamp-var ,gsi-timestamp-upper-bound)
		    `(gsi-error ,where gsi-timestamp-out-of-bounds
				,timestamp-var ,gsi-timestamp-upper-bound))))))))

(defmacro with-guarded-timestamp ((where timestamp) &body body)
  (with-guarded-timestamp-body where timestamp nil body))

(defmacro with-guarded-timestamp-api ((timestamp) &body body)
  (with-guarded-timestamp-body nil timestamp t body))


;;; Declaration:     old-with-guarded-timestamp
;;;                    ((year month day hour minute second) &rest body)
;;; Type:		 Lisp macro.
;;; Purpose:	     Warn the user if a GSI sensor receives an invalid timestamp.
;;; Arguments:	     Executes body unless the following constraints are violated:
;;;                    year is a positive fixnum.
;;;                    month is between 1 and 12 inclusive.
;;;                    day is between 1 and 31 inclusive.
;;;                    hour is between 0 and 23 inclusive.
;;;                    minute is between 0 and 59 inclusive.
;;;                    second is between 0 and 59 inclusive.
;;;                  If a constraint is violated, this macro posts a logbook message
;;;                  and declines to execute body.
;;; Return behavior: No useful value is returned, even if no constraint was
;;;                  violated.
;;; Users:	     GSI internals:
;;;                    receive-value-for-gsi-sensor-with-timestamp
;;;                    receive-timestamped-gsi-sensor-value-vector
;;; Prerequisites:   notify-user machinery must be set up.
;;; Side effects:    Can post a logbook message.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Possible bugs:   This macro does not check that day is in range for a given
;;;                  month (e.g., September 31 will pass).  This should be fixed.
;;; NOTES:           This macro is obsolescent; it is used by code which supports old
;;;		      versions of GSI which pass timestamps as six-integer "UTC time names"
;;;                   all post-4.0 code should use the new version, called
;;;                   with-guarded-timestamp.

#+unused
(defun-simple old-notify-user-of-out-of-bounds-timestamp (year month day hour minute second)
  (notify-user-if-possible
    "Out-of-range timestamp received from GSI extension:~%~
     year: ~d~%month: ~d~%day: ~d~%hour: ~d~%minute: ~d~%second: ~d"
    year month day hour minute second))

#+unused
(defmacro old-with-guarded-timestamp ((year month day hour minute second) &body body)
  (avoiding-variable-capture (year month day hour minute second)
    `(if (and (<=f 0 ,year)
	      (<=f 1 ,month)
	      (<=f ,month 12)
	      (<=f 1 ,day)
	      (<=f ,day 31)
	      (<=f 0 ,hour)
	      (<=f ,hour 23)
	      (<=f 0 ,minute)
	      (<=f ,minute 59)
	      (<=f 0 ,second)
	      (<=f ,second 59))
	 (progn ,@body)
	 (old-notify-user-of-out-of-bounds-timestamp
	   ,year ,month ,day ,hour ,minute ,second))))

;;; GENSYMCID-1352: Out-of-range timestamp
;;;                 (seen in RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP)
;;;
;;; NOTE: the following code implemented a "caching" facility for quickly computing out
;;; a unit-time from the given 6 date components. However, due to coding mistakes, the
;;; stored value of those 4 system variables LAST-GSI-TIMESTAMP-{YEAR,MONTH,DAY,HOUR}
;;; are *never* changed, after the new cached GSI-TIMESTAMP-UNIX-TIME is computed out.
;;; As a result, the caching facility doesn't work at all. But if the incoming date values
;;; are valid (with non-zero year, month and day), the function is still working correctly,
;;; just every time it needs to call GENSYM-ENCODE-UNIX-TIME.
;;;
;;; The big problem happens when the incoming dates are "bogus" timestamp, that is, all
;;; six time components are zeros. These bogos values comes from two places:
;;;
;;; 1) write-message-group-upon-gsi-interface-activation,
;;; 2) gsi-send-reply-to-initial-ping-internal.
;;;
;;; In this case, the cached but uninitialized floating value inside LAST-GSI-TIMESTAMP-
;;; UNIX-TIME will be used, and in rare cases this results into a valid double float
;;; which is smaller than 0, then it's captured by WITH-GUARDED-TIMESTAMP.
;;;
;;; Our solution consists of several fixes:
;;;
;;; 1) fixed missing cache updates in (DEF-ICP-VALUE-READER GSI-TIMESTAMP),
;;; 2) modified "bogus" timestamp to (1970 1 1 0 0 0), a valid date for GENSYM-ENCODE-
;;;    UNIX-TIME,
;;; 3) the old "bogus" timestamp is specially handed and changed to 1970/1/1 0:0:0
;;; 4) added modern timestamp support in GSI-RECEIVE-VALUE-FOR-PING-REQUEST, but we
;;;    still check for six zeros sending from old GSI peers, and in that case, we prevent
;;;    potential bignum creation when using "-" but "-F" to do the minus on two fixnums.
;;;
;;; But even with these fixes, there're still chances that customer need to
;;; rebuild their GSI application (or upgrade to latest G2-OPC bridge) to
;;; completely prevent using old style GSI-TIMESTAMP.
;;;
;;; -- Chun Tian (binghe), Feb 14, 2015.

(def-system-variable last-gsi-timestamp-year gsi-common 0)
(def-system-variable last-gsi-timestamp-month gsi-common 0)
(def-system-variable last-gsi-timestamp-day gsi-common 0)
(def-system-variable last-gsi-timestamp-hour gsi-common 0)
(def-system-variable last-gsi-timestamp-unix-time gsi-common
  (:funcall allocate-managed-float-box))

(def-icp-value-reader gsi-timestamp
  (with-temporary-gensym-float-creation read-icp-gsi-timestamp
    (with-bifurcated-version-for-input (gsi-timestamp-as-float-icp-version)
      ;; old style, six ints
      (let* ((year (read-icp-integer))
	     (month (read-icp-integer))
	     (day (read-icp-integer))
	     (hour (read-icp-integer))
	     (minute (read-icp-integer))
	     (second (read-icp-integer)))
	(cond
	  ;; the old bogus timestamp
	  ((and (=f year 0) (=f month 0) (=f day 0))
	   (gensym-encode-unix-time-as-managed-float 0 0 0 1 1 1970))
	  ;; cached timestamp
	  ((and (=f hour last-gsi-timestamp-hour)
		(=f day last-gsi-timestamp-day)
		(=f month last-gsi-timestamp-month)
		(=f year last-gsi-timestamp-year))
	   (allocate-managed-float
	     (+e (managed-float-value last-gsi-timestamp-unix-time)
		 (coerce-fixnum-to-gensym-float
		   (+f (*f 60 minute) second)))))
	  ;; cache-missed timestamp
	  (t
	   (let ((new-cached-gsi-timestamp-unix-time
		   (gensym-encode-unix-time-as-gensym-float 0 0 hour day month year)))
	     (declare (type gensym-float new-cached-gsi-timestamp-unix-time))
	     (mutate-managed-float-value
	       last-gsi-timestamp-unix-time
	       new-cached-gsi-timestamp-unix-time)
	     ;; The following missing SETQ is newly added by GENSYMCID-1352.
	     (setq last-gsi-timestamp-year year
		   last-gsi-timestamp-month month
		   last-gsi-timestamp-day day
		   last-gsi-timestamp-hour hour)
	     (allocate-managed-float
	       (+e new-cached-gsi-timestamp-unix-time
		   (coerce-fixnum-to-gensym-float
		     (+f (*f 60 minute) second))))))))
      ;; new style, double-float  (will this leak a gensym-float?)
      (allocate-managed-float (read-icp-double-float-1)))))


(def-icp-value-writer gsi-timestamp
  (with-temporary-gensym-float-creation write-icp-gsi-timestamp
    (with-bifurcated-version-for-output (gsi-timestamp-as-float-icp-version)
      ;; old style, six ints
      (multiple-value-bind (year month day hour minute second)
	  (non-resumable-icp-form
	    (gensym-decode-unix-time (managed-float-value gsi-timestamp)))
	(write-icp-integer year) (write-icp-integer month) (write-icp-integer day)
	(write-icp-integer hour) (write-icp-integer minute) (write-icp-integer second))
      ;; new style, double-float
      (write-icp-double-float-1 (managed-float-value gsi-timestamp)))))


;; Changed generic number type in remote-value reader and writer to
;; appropriate subtypes: float and integer.  Also added continuable errors in
;; development if we fall through the type dispatching.  jh, 3/26/91.

;; jh, 2/5/92.  Changed the reader for an integer sent from GSI from
;; (read-icp-integer) to (read-icp-fixnum).  Previously, if GSI sent a C long
;; 2^29 or greater to G2, it was read as a bignum, which make-temporary-constant
;; turned into a float.  The unexpected bignum constituted a leak, and the
;; surreptitious conversion to a float, even when the sensor receiving the
;; value is an integer-variable, was a crash waiting to happen in compiled G2
;; bytecode.  The fix for this is to wrap around at 2^29 -1 and document the
;; difference between C longs and G2 integers to GSI users.

;; jra & jh, 11/10/92.  Modified the value reader for remote-value to
;; use managed floats where possible, as part of the project to improve
;; GSI performance.


;;; Declaration:     gsi-value-error-code
;;; Type:	     ICP value type.
;;; Purpose:	     Represent an error in the value of a GSI sensor.
;;; Arguments:       This ICP value type is equivalent to unsigned-integer.
;;;                  Predefined values are the constants no-error,
;;;                  cancel-collection, collect-one-now.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    receive-value-for-gsi-sensor
;;;                    receive-value-for-gsi-sensor-with-timestamp
;;;                    receive-gsi-sensor-value-vector
;;;                    receive-timestamped-gsi-sensor-value-vector
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

(def-icp-value-type-equivalence gsi-value-error-code unsigned-integer)



;; Apparently obsolete: (MHD 6/20/96)
;; ;;; The implementation of the GSI_STRING_CHECK switch involves interposing the
;; ;;; functions `gensym-to-ascii' and `ascii-to-gensym' on the ICP value reader
;; ;;; and writer (respectively) for filtered-text-string.
;; ;;;
;; ;;; These functions are obsolete and should not be used in new code.  They
;; ;;; are redundant with functions copy-ascii-string-as-gensym-text-string and
;; ;;; copy-ascii-string-as-gensym-text-string, in UTILITIES1.
;; 
;; (defun-simple gensym-to-ascii (text-string)
;;   (twith-output-to-text-string
;;     (twrite-ascii-from-text-string text-string)))
;; 
;; (defun-simple ascii-to-gensym (ascii-string)
;;   (twith-output-to-text-string
;;     (twrite-gensym-characters-from-ascii-string ascii-string)))
;; 
;; ;; MHD, 5/8/95: Note that gensym-to-ascii and ascii-to-gensym are GSI-specific
;; ;; functions and therefore cannot be used outside of this module.  They are
;; ;; no longer called by the reader and writer for filtered-text-string.  They
;; ;; are redundant with functions copy-ascii-string-as-gensym-text-string and
;; ;; copy-ascii-string-as-gensym-text-string, in UTILITIES1.  They're left in
;; ;; for historical reasons.
;; ;;
;; ;; The macros used to implement these functions have gone away.  They were
;; ;; redundant at best, and at worst, had a flaw: gensym-to-ascii had the same
;; ;; flaw in it as twrite-ascii-from-text-string.  See the comment that begins
;; ;; with "Twrite-ascii-from-text-string used to "mistranslate" Japanese
;; ;; characters" in UTILITIES1.  (MHD 5/8/95)





;;;; ICP Object Definitions

;;; Declaration:     returned-gsi-sensor
;;; Type:	     ICP value type.
;;; Purpose:	     Represent the local version of a corresponding GSI sensor.
;;; Arguments:       A returned-gsi-sensor is a gsi-sensor structure that
;;;                  corresponds to a sensor in the remote GSI process.  It is
;;;                  transmitted as an unsigned integer which is given to
;;;                  get-original-icp-object, after appropriate arrangements have
;;;                  been made to make this function think it is using an ICP input
;;;                  port.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                     receive-value-for-gsi-sensor
;;;                     receive-value-for-gsi-sensor-with-timestamp
;;;                     receive-gsi-sensor-value-vector
;;;                     receive-timestamped-gsi-sensor-value-vector
;;; Prerequisites:   A corrsponding object for the gsi-sensor structure must have
;;;                  already been created in the remote GSI process.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None -- no new gsi-sensor structures are allocated.

;(def-system-variable icp-object-index-for-returned-gsi-interface gsi-common)

(def-icp-value-reader returned-gsi-sensor
  (let ((handle-or-item
	  (with-bifurcated-version-for-input (gsi-sends-returned-gsi-sensor-as-reference-icp-version)
	    (read-icp-unsigned-integer)
	    (case (peek-icp-byte)
	      (#.gsi-integer-type-tag
	       (read-icp-byte)
	       (read-icp-integer))
	      (t
	       (let ((rpc-argument-list-error nil))
		 (prog1 (read-icp-item-reference)
		   (reclaim-if-text-string rpc-argument-list-error))))))))
    (if (fixnump handle-or-item)
	(get-from-icp-port-if-any
	  (icp-output-port (parent-icp-socket current-icp-port))
	  handle-or-item
	  'item-index-space)
	handle-or-item)))

(def-icp-value-writer returned-gsi-sensor
  (with-bifurcated-version-for-output (gsi-sends-returned-gsi-sensor-as-reference-icp-version)
    (write-icp-unsigned-integer
      (if (fixnump returned-gsi-sensor)
	  returned-gsi-sensor
	  ;;(gsi-sensor-index returned-gsi-sensor)
	  (let* ((current-icp-input-port
		   (icp-input-port (parent-icp-socket current-icp-port)))
		 (icp-object-map
		   (current-system-case
		     ;;(ab  (icp-object-map-for-registered-item
		     ;;       returned-gsi-sensor))
		     (gsi (icp-object-map-for-gsi-instance
			    returned-gsi-sensor)))))
	    (getfq icp-object-map current-icp-input-port))))
    (cond ((fixnump returned-gsi-sensor)
	   (write-icp-byte #.gsi-integer-type-tag)
	   (write-icp-integer returned-gsi-sensor))
	  (t
	   (write-icp-item-reference returned-gsi-sensor)))))




;;; ICP readers and writers to support gsi requests returning vectors of values.

;;; Declaration:     gsi-value-vector
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a vector of values from the remote GSI process.
;;; Arguments:       A vector of values is represented as a gsi-list of gsi-conses.
;;;                  The car of each cons is a symbol representing an attribute of a
;;;                  GSI sensor.  The cdr of each cons is a remote-value holding
;;;                  the value of that attribute, possibly with a timestamp.
;;;                  (Timestamps are stored in the constant-expiration slot of the
;;;                  temporary-constant structure which is the remote-value.)
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    receive-gsi-sensor-value-vector
;;;                    receive-timestamped-gsi-sensor-value-vector
;;; Prerequisites:   The ICP value types boolean, text-string, integer, and
;;;                  remote-value must be defined.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   > gsi-value-vectors are reclaimed by reclaim-gsi-value-vector
;;;                    (q.v.).
;;;                  > The symbols in the gsi-list are the result of interning
;;;                    text-strings.  If the remote GSI process sends new text-strings
;;;                    each time, this could look like a leak.
;;; Notes:           Profiling reveals that interning the same symbol repeatedly is
;;;                  a major drag on performance.  We should use the ICP value type
;;;                  symbol instead.

;;; Note that in the function below, we assume that the with-temporary-gensym-
;;; float-creation will take care of the bignums created for the timestamp
;;; within the loop.  Note that there will be a relatively limited number of
;;; iterations through the loop, since there has to be one attribute per
;;; iteration.  Given that a float takes 16 bytes, and a bignum representing a
;;; typical universal time takes 16 bytes, then with a 64K temporary area, this
;;; reader can deal with 2048 attributes.  -jra & jh 6/22/92

(def-icp-value-reader gsi-value-vector
  (loop with vector-length = (read-icp-byte)
	for count from 0 below vector-length
	;; Note that the following intern is a major performance problem.
	;; This should have been done using a symbol (i.e. a corresponding
	;; object).  -jra&jh 6/22/92   Fixed. -rh 10/28/96
	as element-name = (with-bifurcated-version-for-input
			      (value-vector-names-are-symbols-icp-version)
			    (intern-text-string (read-icp-text-string))
			    (read-icp-icp-tree))
	as element-value? = (read-icp-remote-value)
	as timestamp-present? = (read-icp-boolean)
	as timestamp? = (if timestamp-present? (read-icp-gsi-timestamp) 'never)
	collect (gsi-list (if (and (consp element-name)
				   (eq (car element-name) 'attribute))
			      (if (null (second element-name))
				  (prog1 (third element-name)
				    (reclaim-icp-list element-name))
				  (progn
				    (setf (car element-name) 'class-qualified-name)
				    element-name))
			      element-name)
			  (runtime-current-system-case
			    (gsi (convert-value-to-gsi-value element-value?))
			    (t element-value?))
			  timestamp?)
	  using gsi-cons))


;; Modified the value reader for gsi-value-vector to use the
;; read-icp-gsi-timestamp, which bifurcates at version 4.0, supporting the
;; old six-ints-over-the-wire form prior and the new double format in 4.0 and
;; beyond.  -ncc, 7/28/94

;; The new-slot-value component of the value-vector may be nil instead of
;; temporary constants, in which case we don't want to reclaim them.  Added test
;; for this. (jh, 7/17/90)

;; jra & jh, 11/10/92.  Modified the value reader for gsi-value-vector to use
;; encode-gensym-time, which now no longer creates bignums.  We can expect a
;; performance improvement in Chestnut, since we no longer have to enter a
;; temporary area.

(defun-simple reclaim-gsi-value-vector (value-vector)
  (runtime-current-system-case
    (ab (when value-vector
	  (loop for vector-element in value-vector
		for (slot-name new-slot-value? new-slot-collection-time?) = vector-element
		do (when (consp slot-name)
		     (reclaim-gsi-list slot-name))
		   (when new-slot-value?
		     (reclaim-if-evaluation-value-1 new-slot-value?))
		   (when new-slot-collection-time?
		     ;;the collection time can have the value 'NEVER, so we have to use
		     ;;reclaim-if. yduJ, 12/6/01
		     (reclaim-if-evaluation-value-1 new-slot-collection-time?))
		   (reclaim-gsi-list vector-element))
	  (reclaim-gsi-list value-vector)))
    (t value-vector)))
	

;; -paf! 31oct94 The def-icp-value-writer for gsi-value-vector has been moved
;; to gsi.lisp because G2 never uses it and because it came to depend on a
;; constant defined in gsi.lisp which I don't want to move here.




;;;; GSI ICP Message Definitions

;;; Declaration:     define-gsi-interface (corresponding-icp-object-index)
;;; Type:	     ICP message type.
;;; Purpose:	     Create a corresponding GSI interface.
;;; Arguments:       A nonnegative fixnum which is to represent the index of the
;;;                  corresponding GSI interface in the remote GSI process.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (ICP object type gsi-interface), "GSI in G2"
;;;                  machinery.
;;; Prerequisites:   None.
;;; Side effects:    In "GSI in G2", the handler for this message modifies
;;;                  current-icp-object-index-for-returned-gsi-interface.
;;; Non-local exits: None.
;;; Memory impact:   None -- no gsi-interface structures are allocated.

(def-icp-message-type initialize-gsi-interface ((symbol interface-name) ;may be nil
						(symbol class-name) ;may be nil
						(boolean keep-connection-on-g2-reset)
						(symbol listener-network-type) ;may be nil
						(text-string listener-host-name)
						(text-string listener-port-name)
						(text-string remote-process-initialization-string))
  interface-name class-name keep-connection-on-g2-reset
  listener-network-type listener-host-name listener-port-name
  remote-process-initialization-string
  (receive-initial-message 'g2 'gsi)
  (current-system-case
    (ab
      (runtime-current-system-case
	(ab
	  (cond ((not (network-access-allowed-p 'gsi 'connect))
		 (disallow-new-icp-listener-connection current-icp-socket))
		#+ignore ; see note
		((and (eq class-name 'ui-client-interface)
		      (not (license-for-ui-client-interface-available-p)))
		 (with-bifurcated-version-for-output (no-licence-icp-version)
		   (disallow-new-icp-listener-connection current-icp-socket)
		   (no-license-for-new-icp-listener-connection current-icp-socket)))
		(t		   
		 (g2-initialize-gsi-interface
		   interface-name class-name keep-connection-on-g2-reset
		   listener-network-type listener-host-name listener-port-name
		   remote-process-initialization-string nil))))))
    (t
      (progn
	interface-name class-name keep-connection-on-g2-reset
	listener-network-type listener-host-name listener-port-name
	remote-process-initialization-string
	nil))))

;; Note. In 5.1r0 there were floating licenses for tw2 but no independent 'named'
;; licenses, so this check permitted us to deny connections whenever the G2 had
;; allocated all of its floaters. 


(def-icp-message-type return-initialize-gsi-interface-status ((text-string error-information))
  (runtime-current-system-case
    (gsi
      (gsi-connection-error 'gsi_initiate_connection
			    gsi-error-in-connect
			    error-information))
    (t
      (progn
	error-information
	nil))))


(defun gsi-initialize-icp-socket (icp-socket)
  (let ((gsi-extension-data? (gsi-extension-data? icp-socket)))
    (unless gsi-extension-data?
      (let ((current-icp-socket icp-socket))
	(setq gsi-extension-data? (make-gsi-extension-data)))
      (setf (gsi-extension-data? icp-socket) gsi-extension-data?))
    gsi-extension-data?))



;;; reclaim-gsi-structures-for-socket is called by the connection
;;; loss notifier if it determines that the connection was "broken" rather than
;;; shut down cleanly.  (see the comments before gsi-connection-loss-notifier
;;; for details)  -ncc, 13 Feb 1995 
;;;  Don't reclaim things if this socket's already been reclaimed.
;;; This is a bit experimental, since it's hard to tell whose toes might be
;;; being walked on. -ncc, 14 Feb 1995 
;;;


;;; Declaration:     pause-data-server ()
;;; Type:	     ICP message type.
;;; Purpose:	     Pause GSI dataservice in a remote process.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (gsi-pause-data-server?), "GSI in G2" machinery.
;;; Prerequisites:   None.
;;; Side effects:    Note that some GSI messages generated by editing may be
;;;                  transmitted from a paused G2 to a remote GSI process.  An
;;;                  example of such a message is the define-gsi-sensor sent when
;;;                  the value of an identifying-attribute of a GSI sensor is
;;;                  edited.  There is controversy about whether this is a bug or a
;;;                  feature.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; The handler for pause-data-server calls the user function gsi-pause-context.

(def-icp-message-type pause-data-server ()
  (runtime-current-system-case
    (gsi (call-gsi-callback gsi-pause-context))))

(def-icp-message-type resume-data-server ()
  (runtime-current-system-case
    (gsi (call-gsi-callback gsi-resume-context))))

(def-icp-message-type start-data-server ()
  (runtime-current-system-case
    (gsi (call-gsi-callback gsi-start-context))))

(def-icp-message-type reset-data-server ()
  (runtime-current-system-case
    (gsi (call-gsi-callback gsi-reset-context))))


;;; Declaration:     initialize-data-server (text-string)
;;; Type:	     ICP message type.
;;; Purpose:	     Initialize the GSI dataserver in a remote process.
;;; Arguments:       text-string is sent to the remote GSI process as an aid to
;;;                  configuration.
;;; Return behavior: No useful value.
;;; Users:           GSI internals
;;;                  (write-message-group-upon-gsi-interface-activation), 
;;;                  "GSI in G2" machinery.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   The handler for this message must reclaim text-string,
;;;                  unless it is done automatically (as in "GSI in G2").
;;; Notes:           The name of this message is misleading -- too general.

;;; The handler for initialize-data-server calls the user function
;;; gsi-initialize-context with text-string.  It then reclaims text-string.

;;;   XXX NO IT DOESN'T reclaim text-string, not as far as I can see -ncc, 4/15/94

;;; This ought to use call-gsi-callback. -ncc, 4 Apr 1995 

;;; IMPORTANT note, It used to be that the user call back function
;;; gsi-initialize-context was called by the handler for initialize-data-server,
;;; however in GSI 4.0 the initialization is not really complete until the
;;; version info has been passed in both ways, so I moved the call to
;;; gsi-initialize-context into the handler for receive-peer-version.  In order
;;; for this to work, I had to cache the RPIS (text-string) in the
;;; gsi-extension-data structure. -paf! 19may95

(def-icp-message-type initialize-data-server (text-string)
  (receive-initial-message 'gsi 'g2)
  (runtime-current-system-case
    (ab
      text-string
      (shutdown-icp-socket-connection
	current-icp-socket 'g2-received-initialize-data-server-message))
    (gsi
      (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
	(let ((gsi-extension-data (gsi-extension-data? current-icp-socket)))
	  (unless (<=f 0 (gsi-context-number gsi-extension-data))
	    (when (and (>=f gsi-maximum-number-of-contexts 0)
		       (>=f number-of-contexts-allocated gsi-maximum-number-of-contexts))
	      (writing-icp-message-group ((icp-output-port current-icp-socket))
		(with-bifurcated-version-for-output (shutdown-protocol-icp-version)
		  (send-icp-shut-down-data-server)
		  (send-icp-acknowledge-shutdown))) ; since we can't wait around for the reply
	      (flush-icp-output-ports)
	      (gsi-connection-error 'initialize-data-server-message
				    gsi-maximum-contexts-exceeded 
				    gsi-maximum-number-of-contexts))
	    (setf (gsi-context-number gsi-extension-data) (allocate-gsi-context-number)))
	  (setf (icp-socket-listener-client? current-icp-socket) 'g2)
	  (setf (gsi-remote-process-initialization-string gsi-extension-data)
		(convert-value-to-gsi-value (copy-text-string text-string)))
	  (send-version-info))))))

(defun-simple call-initialize-context-callback ()
  (runtime-current-system-case
    (gsi
      (let ((gsi-extension-data (gsi-extension-data? current-icp-socket)))
	(gsi-message "Connection request received - context ~A~A~%"
		     (gsi-current-context-number)
		     (secure-icp-string :secure-p (icp-connection-is-secure current-icp-socket)))
	(setf (gsi-initialize-context-has-been-called-p gsi-extension-data) t)
	(setf (gsi-extension-application gsi-extension-data)
	      (find-or-load-gsi-application
		(icp-socket-gsi-application-name current-icp-socket)))
	(unless (gsi-extension-application gsi-extension-data)
	  (return-from call-initialize-context-callback t))  ; t means failure
	(let ((string (prog1 (gsi-remote-process-initialization-string gsi-extension-data)
			(setf (gsi-remote-process-initialization-string gsi-extension-data) nil))))
	  (prog1 (gsi-failure-p
		   (call-gsi-callback gsi-initialize-context
				      string
				      (lengthw string)))
	    (reclaim-text-or-gensym-string string)))))))

(defun-simple call-initialize-context-and-maybe-reject-connection ()
  (runtime-current-system-case
    (gsi
      (let ((failurep (call-initialize-context-callback)))
	(gsi-message "Connection ~A - context ~A~A~%"
		     (if failurep "rejected" "accepted")
		     (gsi-current-context-number)
		     (secure-icp-string :secure-p (icp-connection-is-secure current-icp-socket)))
	(when failurep
	  (flush-and-shutdown-icp-socket current-icp-socket)
	  t)))))

(defun-simple send-version-info ()
  (writing-icp-message-group ((icp-output-port current-icp-socket))
    (send-icp-return-peer-version
      (get-system-major-version current-system-name)
      (get-system-minor-version current-system-name))))

(def-icp-message-type return-peer-version
		      ((unsigned-integer major-version-number)
		       (unsigned-integer minor-version-number))
  (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
    (runtime-current-system-case
      (telewindows
       (progn major-version-number minor-version-number nil))
      (ab
	;; G2 always "supports" the shutdown protocol -- the ack will just timeout for
	;; GSI clients earlier than 4.0. -ncc, 25 Apr 1995
	(setf (icp-connection-supports-shutdown-protocol? current-icp-socket) t)
	(maybe-update-remote-icp-version-info-for-version
	  current-icp-socket major-version-number minor-version-number)
	(with-appropriate-version-for-output (g2-version-reply-to-gsi-icp-version)
	  (send-version-info))
	(maybe-declare-all-gsi-sensors))
      (gsi
	;; When the G2 client is 4.0+, it supports active shutdown from GSI,
	;; and expects acknowledgement.
	;; -ncc, 25 Apr 1995 
	(when (>=f major-version-number 4)
	  (setf (icp-connection-supports-shutdown-protocol? current-icp-socket) t))
	(maybe-update-remote-icp-version-info-for-version
	  current-icp-socket major-version-number minor-version-number)
	(with-appropriate-version-for-output (supports-icp-version-protocol-icp-version)
	  (gsi-reply-to-initial-ping))))))




;;; The function `round-post4.0-managed-float' is used to round off subsecond
;;; background collection intervals into something that pre-4.0 G2 or GSI data
;;; server can handle, i.e. a fixnum collection interval.  This assumption of a
;;; fixnum interval is built into the message protocol for begin collecting data
;;; ICP messages for G2DS, and so needs bifurcated version work in order to
;;; bring it up to date with the subsecond time facilities in version 4.0.  This
;;; function rounds any floating point update intevals to the next lowest
;;; fixnum, and rounds up intervals of less than a second to one second.

(defun-simple round-post4.0-managed-float (variable-collection-interval?)
  (if (managed-float-p variable-collection-interval?)
      (with-temporary-gensym-float-creation g2-to-g2-interface-name-putter
	(let ((float-interval
		(managed-float-value variable-collection-interval?)))
	  (declare (type gensym-float float-interval))
	  (cond ((<=e float-interval 0.0)
		 0)
		((<=e float-interval 1.0)
		 1)
		(t
		 (floore-first float-interval)))))
      variable-collection-interval?))

(def-icp-value-writer gsi-ds-update-interval
  (with-bifurcated-version-for-output (ds-update-interval-as-float-icp-version)
    (write-icp-fixnum
      (round-post4.0-managed-float gsi-ds-update-interval))
    (cond
      ((managed-float-p gsi-ds-update-interval)
       (write-icp-managed-double-float gsi-ds-update-interval))
      ((fixnump gsi-ds-update-interval)
       (let ((float-to-write
	       (allocate-managed-float
		 (coerce-fixnum-to-gensym-float
		   gsi-ds-update-interval))))
	 (write-icp-managed-double-float float-to-write)
	 (reclaim-managed-float float-to-write)))
      #+development
      (t (cerror "Ignore and proceed"
		 "GSI-DS-UPDATE-INTERVAL value writer: ~
                  unknown thing ~s"
		 gsi-ds-update-interval)))))

;; jh, 5/21/95.  Not sure how to blend this into the utilities in SETS.  Anyone
;; who knows more, please feel free to move this.

(def-icp-value-reader gsi-ds-update-interval
  (with-bifurcated-version-for-input (ds-update-interval-as-float-icp-version)
    (read-icp-fixnum)
    (read-icp-managed-double-float)))


;;; Declaration:     define-gsi-sensor
;;;                    (corresponding-icp-object-index
;;;                     parameter1 parameter2 parameter3
;;;                     parameter4 parameter5 parameter6)
;;; Type:	     ICP message type.
;;; Purpose:	     Define a corresponding GSI sensor in the remote GSI process.
;;; Arguments:       corresponding-icp-object-index is of that ICP value type
;;;                  (equivalent to unsigned-integer).  It represnts an index
;;;                  which allows the remote GSI process to locate a corresponding
;;;                  GSI sensor.  parameter1 through parameter6 are of ICP value
;;;                  type remote-value and give the values of the
;;;                  identifying-attributes of the associated GSI sensor.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (define-or-configure-gsi-sensor), "GSI in G2"
;;;                  machinery.
;;; Prerequisites:   None.
;;; Side effects:    Causes a corresponding GSI sensor to be created and indexed
;;;                  in the remote GSI process.
;;; Non-local exits: None.
;;; Memory impact:   Allocates memory for a corresponding GSI sensor and entries
;;;                  for it in an index space.


;;; Declaration:     modify-gsi-sensor-definition
;;;                    (corresponding-icp-object-index
;;; 		        update-interval
;;; 		        value-type
;;; 		        name-of-item?
;;; 		        name-of-class)
;;; Type:	     ICP message type.
;;; Purpose:	     Add ancillary information to a corresponding GSI sensor.
;;; Arguments:       > corresponding-icp-object-index is of that ICP value type
;;;                    (equivalent to unsigned-integer).  It represnts an index
;;;                    which allows the remote GSI process to locate a corresponding
;;;                    GSI sensor.
;;; 		     > update-interval is of ICP value type integer and represents
;;;                    the interval with which the corresponding GSI sensor in the
;;;                    remote GSI process will send values to the GSI sensor.  If
;;;                    update-interval is 0, the remote GSI process will only send
;;;                    one value.
;;; 		     > value-type is of ICP value type unsigned integer and
;;;                    represents the type of value expected by the GSI sensor.
;;;                    See collect-modifications-and-modify-gsi-sensor-definition.
;;; 		     > name-of-item? and name-of-class are sent as
;;;                    remote-values, because of backwards-compatibility issues.
;;; Return behavior: No useful value.
;;; Users:		 GSI internals:
;;;                    define-or-configure-gsi-sensor
;;;                    reply-to-return-gsi-extension-version
;;; Prerequisites:   The corresponding GSI sensor given by
;;;                  corresponding-icp-object-index must have already been defined
;;;                  in the remote GSI process (using define-gsi-sensor, q.v.).
;;; Side effects:    Modifies the corresponding GSI sensor in the remote GSI
;;;                  process.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           > Note that this message is only sent to remote GSI processes
;;;                    of version 2.0 or greater.


(def-icp-message-type define-gsi-sensor
                      (corresponding-icp-object-index
			(gsi-permanent-remote-value parameter1)
			(gsi-permanent-remote-value parameter2)
			(gsi-permanent-remote-value parameter3)
			(gsi-permanent-remote-value parameter4)
			(gsi-permanent-remote-value parameter5)
			(gsi-permanent-remote-value parameter6))
  (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
    (gsi-register-new-sensor corresponding-icp-object-index
			     parameter1
			     parameter2
			     parameter3
			     parameter4
			     parameter5
			     parameter6)))

(def-icp-message-type register-corresponding-icp-object
                      (corresponding-icp-object-index
			(symbol name-of-item?)
			(symbol class-of-item)
			(gsi-permanent-remote-value parameter1?)
			(gsi-permanent-remote-value parameter2?)
			(gsi-permanent-remote-value parameter3?)
			(gsi-permanent-remote-value parameter4?)
			(gsi-permanent-remote-value parameter5?)
			(gsi-permanent-remote-value parameter6?))
  (runtime-current-system-case
    ((gsi telewindows)
     (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
       (call-gsi-callback gsi-receive-registration
         (gsi-register-new-sensor corresponding-icp-object-index
				  parameter1?
				  parameter2?
				  parameter3?
				  parameter4?
				  parameter5?
				  parameter6?
				  name-of-item?
				  class-of-item))))
    (ab ;not used as of 2/8/95
      (declare-ignorable-icp-arguments
	name-of-item? class-of-item corresponding-icp-object-index)
      (reclaim-if-evaluation-value-function parameter1?)
      (reclaim-if-evaluation-value-function parameter2?)
      (reclaim-if-evaluation-value-function parameter3?)
      (reclaim-if-evaluation-value-function parameter4?)
      (reclaim-if-evaluation-value-function parameter5?)
      (reclaim-if-evaluation-value-function parameter6?))))

(defun-void gsi-add-new-sensor-attribute (new-sensor attributes index parameter)
  (setf (gsi-instance-owner parameter) 'context)
  (setf (gsi-attribute-instance (gsi-typed-array-ref gsi-item attributes index))
	parameter)
  (gsi-push-onto-appropriate-list parameter new-sensor))

(defun gsi-register-new-sensor (index parameter1 parameter2 parameter3
				      parameter4 parameter5 parameter6
				      &optional (name-of-item? nil)
				      (class-of-item? nil))
  (runtime-current-system-case
    (gsi
      (handle-delete-corresponding-icp-object
	index 'item-index-space current-icp-port)
      ;; The call above handles the case in which an existing registered-item
      ;; is modified as opposed to deleted and replaced.  The user model has
      ;; no distinction between the two cases whereas ICP and G2 does
      ;; distinguish between the two.  I would like to introduce this
      ;; distinction into the user model (but only when user has set the
      ;; as yet undefined run-time option GSI_NEW_BEHAVIORS) through a
      ;; new toolkit function gsi_modify_registration(new,old).  By the
      ;; time this new function is called the new is already in place
      ;; in the corresponding object space, and with the user data
      ;; copied over from the old.  The user need not do anything in
      ;; this toolkit function, and the old is provided so that the user
      ;; may determine what has changed and react accordingly -paf! 21jun95
      (let* ((gsi-reclaim-list? nil)
	     (new-sensor (make-gsi-sensor 'user)) ; 'user keeps it off the reclaim-list
	     (attributes (gsi-make-attributes-for-user-or-gsi 6 'context)))
	(setf (gsi-instance-owner new-sensor) 'context)
	(setf (gsi-instance-reclaim-list new-sensor) gsi-reclaim-list?)
	(setf (gsi-attributes new-sensor) attributes)
	(setf (gsi-attribute-count new-sensor) 6)
	(gsi-add-new-sensor-attribute new-sensor attributes 0 parameter1)
	(gsi-add-new-sensor-attribute new-sensor attributes 1 parameter2)
	(gsi-add-new-sensor-attribute new-sensor attributes 2 parameter3)
	(gsi-add-new-sensor-attribute new-sensor attributes 3 parameter4)
	(gsi-add-new-sensor-attribute new-sensor attributes 4 parameter5)
	(gsi-add-new-sensor-attribute new-sensor attributes 5 parameter6)
	(when name-of-item?
	  (setf (gsi-sensor-name new-sensor) name-of-item?))
	(when class-of-item?
	  (setf (gsi-sensor-class new-sensor) class-of-item?))
	(set-icp-object-index-for-gsi-instance new-sensor index current-icp-port)
	(store-corresponding-item index new-sensor)
	(setf (gsi-item-reference-flag-value new-sensor) t)
	new-sensor))
    (t
      index parameter1 parameter2 parameter3 parameter4 parameter5 parameter6
      name-of-item? class-of-item?)))

(def-icp-message-type modify-gsi-sensor-definition
                      (corresponding-icp-object-index
		       (gsi-ds-update-interval update-interval)
		       (unsigned-integer value-type)
		       (remote-value name-of-item?)
		       (remote-value name-of-class))
  (runtime-current-system-case
    (gsi
      (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
	(let ((gsi-sensor
		(get-from-icp-port current-icp-port 
				   corresponding-icp-object-index
				   'item-index-space)))

	  ;; If the gsi-instance holding the item name or class name is not of
	  ;; null type, it contains a valid name, represented as a Lisp symbol,
	  ;; which we store in the gsi-sensor for future use.
	  (setf (gsi-sensor-name gsi-sensor) (gsi-instance-value name-of-item?))
	  (setf (gsi-sensor-class gsi-sensor) (gsi-instance-value name-of-class))
	  
	  ;; Immediately reclaim the gsi-instances enclosing the item name and
	  ;; class, as all we need is their values, which we just extracted.
	  ;; jh, 10/12/96.
	  (when (eq 'gsi (default-owner-for-gsi-objects))
	    (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi))

	  (let ((old-contents (gsi-sensor-collection-interval gsi-sensor)))
	    (when (managed-float-p old-contents)
	      (reclaim-managed-float old-contents)))
	  (setf (gsi-sensor-collection-interval gsi-sensor) update-interval)
	  (setf (gsi-sensor-value-type gsi-sensor) value-type)
	  (call-gsi-callback gsi-receive-registration gsi-sensor))))
    (t
      corresponding-icp-object-index
      update-interval value-type name-of-item? name-of-class
      nil)))



;;; Declaration:     (begin-sensor-list)
;;;                  { (load-sensor-list-element gsi-sensor
;;;                                              collection-interval?
;;;                                              value-to-set?) }+
;;;                  (end-sensor-list)
;;;                  { (get-values-for-sensors-in-list) |
;;;                    (set-values-for-sensors-in-list) |
;;;                    (stop-sending-values-for-sensors-in-list) }
;;; Type:		 ICP message series.
;;; Purpose:         Cause the remote GSI process to provide values for a series of
;;;                  GSI sensors.
;;; Arguments:       The ICP message load-sensor-list-element has the following
;;;                  arguments:
;;;                  > gsi-sensor is a gsi-sensor structure representing the
;;;                    corresponding GSI sensor.
;;;                  > collection-interval?  is of ICP value type integer and
;;;                    represents the interval with which the corresponding GSI
;;;                    sensor in the remote GSI process will send values to the
;;;                    GSI sensor.  If collection-interval?  is nil, the remote
;;;                    GSI process will only send this value.
;;;                  > value-to-set?  is a remote-value giving the new value of
;;;                    the corresponding GSI sensor, or nil if its value is not to
;;;                    change.
;;;                  None of the other ICP messages take any arguments.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (send-message-series-for-gsi-request), "GSI in
;;;                  G2" machinery.
;;; Prerequisites:   The corresponding GSI sensors must have been defined by
;;;                  define-gsi-sensor before they be referenced by
;;;                  load-sensor-list-element.
;;; Side effects:    Can modify the values of corresponding GSI sensors.
;;; Non-local exits: None.
;;; Memory impact:   Can allocate memory for the values of corresponding GSI
;;;                  sensors (for instance, when they are strings).

;;; To make data requests, GSI sends the message begin-sensor-list, followed by
;;; load-sensor-list-element messages for each sensor, followed by end-sensor-
;;; list.  It then sends either get-values-for-sensors-in-list, set-values-for-
;;; sensors-in-list, or stop-sending-values-for-sensors-in-list, depending on
;;; the request (see send-message-series-for-gsi-request in GSI).

;;; The basic task of the GSI extension handlers (both C and Lisp versions) is
;;; to put the sensors sent by load-sensor-list-element into the global list
;;; list-of-loaded-sensors, and then pass this list to the appropriate user
;;; function based on the request.

(def-icp-message-type begin-sensor-list ()
  (setf index-to-array-of-transfer-wrappers gsi-magic-offset))

;;; Load-sensor-list-element populates the user-sensor-array in the gsi-data for
;;; the current socket.

(def-icp-message-type load-sensor-list-element
                      (corresponding-icp-object-index
		       (gsi-ds-update-interval collection-interval?)
		       (gsi-permanent-remote-value value-to-set?))
  (runtime-current-system-case
    (gsi
      (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
	(let ((sensor (get-from-icp-port current-icp-port
					 corresponding-icp-object-index
					 'item-index-space))
	      (transfer-wrapper
		(gsi-managed-svref (gsi-transfer-wrapper-array
				     (gsi-extension-data? current-icp-socket))
				   index-to-array-of-transfer-wrappers)))
	  (setf (gsi-transfer-sensor-or-index transfer-wrapper) sensor)
	  (reclaim-if-managed-float (gsi-transfer-update-interval transfer-wrapper))
	  (setf (gsi-transfer-status transfer-wrapper) 0)
	  (setf (gsi-transfer-update-interval transfer-wrapper) collection-interval?)
	  (let ((old-value (gsi-transfer-instance transfer-wrapper)))
	    (when old-value
	      (reclaim-gsi-instance-for-gsi old-value)))
	  (setf (gsi-transfer-instance transfer-wrapper) value-to-set?)
	  (incff index-to-array-of-transfer-wrappers)
	  #+development
	  (when (>=f index-to-array-of-transfer-wrappers
		     size-of-array-of-transfer-wrappers)
	    (error "More than ~a sensors were passed from G2 in one group, ~
              array bounds violation"
		   size-of-array-of-transfer-wrappers)))))
    (t
      corresponding-icp-object-index collection-interval? value-to-set?
      nil)))

(def-icp-message-type end-sensor-list ()
  'dummy-definition)

(def-icp-message-type get-values-for-sensors-in-list ()
  (runtime-current-system-case
    (gsi
      (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
	(call-gsi-callback gsi-get-data
          (gsi-extract-c-array (gsi-transfer-wrapper-array
				 (gsi-extension-data? current-icp-socket)))
	  (-f index-to-array-of-transfer-wrappers 1)))
      (when (eq 'gsi (default-owner-for-gsi-objects))
	(gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi)))))

(def-icp-message-type set-values-for-sensors-in-list ()
  (runtime-current-system-case
    (gsi
      (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
	(call-gsi-callback gsi-set-data
	  (gsi-extract-c-array (gsi-transfer-wrapper-array
				 (gsi-extension-data? current-icp-socket)))
	  (-f index-to-array-of-transfer-wrappers 1)))
      (when (eq 'gsi (default-owner-for-gsi-objects))
	(gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi)))))

(def-icp-message-type stop-sending-values-for-sensors-in-list ()
  (runtime-current-system-case
    (gsi
      (when (=f (icp-connection-state current-icp-socket) icp-connection-running)
	(call-gsi-callback gsi-receive-deregistrations
	  (gsi-extract-c-array (gsi-transfer-wrapper-array
				 (gsi-extension-data? current-icp-socket)))
	  (-f index-to-array-of-transfer-wrappers 1)))
      (when (eq 'gsi (default-owner-for-gsi-objects))
	(gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi)))))


;;; Declaration:     write-user-message-string (user-message urgency? duration?)
;;; Type:	     ICP message type.
;;; Purpose:	     Get a message from the GSI peer process.
;;; Arguments:       user-message is of ICP value type text-string.  urgency?  and
;;;                  duration?  is of ICP value type unsigned-integer-or-nil.  The C
;;;                  version of GSI currently ignores these values.  duration?
;;;                  could affect how long the message persists on the message board
;;;                  in a "GSI in G2" implementation.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (gsi-deliver-messages), "GSI in G2" machinery.
;;; Prerequisites:   None.
;;; Side effects:    If the handler is run in G2, a message appears in the message
;;;                  board.  If the handler is run in the remote GSI process, the
;;;                  message is passed to gsi_rd_text().
;;; Non-local exits: None.
;;; Memory impact:   In G2, a copy of user-message is handed over to the message
;;;                  board facility and the original reclaimed by the handler
;;;                  (automatically, through the icp-value-reclaimer mechanism).

(def-icp-value-writer do-not-reformat-message-p
  (with-bifurcated-version-for-output (do-not-reformat-message-icp-version)
    nil
    (write-icp-boolean do-not-reformat-message-p)))

(def-icp-value-reader do-not-reformat-message-p
  (with-bifurcated-version-for-input (do-not-reformat-message-icp-version)
    nil
    (read-icp-boolean)))

(def-icp-message-type write-user-message-string
                      ((text-string user-message)
		       (unsigned-integer-or-nil urgency?)
		       (unsigned-integer-or-nil duration?)
		       (do-not-reformat-message-p do-not-reformat?))
  (gsi-write-user-message-string
    user-message urgency? duration? do-not-reformat?))

(defun-simple gsi-write-user-message-string (user-message urgency? duration? do-not-reformat?)
  (runtime-current-system-case
    (ab
      (let ((interface? (enclosing-interface-frame? current-icp-socket)))
	(post-on-message-board
	  (copy-text-string user-message)
	  urgency?
	  duration?
	  interface?
	  nil nil nil nil
	  do-not-reformat?)))
    (t ;GSI
      urgency? duration? do-not-reformat?
      (let ((user-message (convert-value-to-gsi-value (copy-text-string user-message))))
	(call-gsi-callback gsi-receive-message
			   user-message (lengthw user-message))
	(reclaim-text-or-gensym-string user-message)))))

;; Added enclosing-interface-frame?  argument to post-on-message-board, so any
;; message from the GSI extension will disappear properly when G2 is reset.
;; (jh, 5/24/90)

;;; The remaining ICP messages can only be received by G2 and are sent by GSI.

(def-icp-value-reader gsi-ds-value
  (read-icp-remote-value))

(def-icp-value-writer gsi-ds-value
  (runtime-current-system-case
    (gsi
      (let ((write-value-of-gsi-item-p t))
	(write-icp-remote-value gsi-ds-value)))
    (t
      (write-icp-remote-value gsi-ds-value))))

;;; Declaration:     receive-value-for-gsi-sensor (gsi-sensor error-code value)
;;; Type:	     ICP message type.
;;; Purpose:	     Acquire a new value for a GSI sensor.
;;; Arguments:	     > gsi-sensor is a gsi-sensor structure associated with the GSI
;;;                    sensor which is to receive the value.
;;;                  > error-code is of ICP value type gsi-value-error-code (q.v.).
;;;                  > value is a temorary-constant structure containing the new
;;;                    value for the GSI sensor.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (gsi-receive-value-for-gsi-sensor), "GSI in G2"
;;;                  machinery.
;;; Prerequisites:   The corresponding GSI sensor associated with gsi-sensor must
;;;                  have already been defined (using define-gsi-sensor).
;;; Side effects:    See gsi-receive-value-for-gsi-sensor in GSI.
;;; Non-local exits: None.
;;; Memory impact:   See gsi-receive-value-for-gsi-sensor in GSI.

(def-icp-message-type receive-value-for-gsi-sensor
		      ((returned-gsi-sensor gsi-sensor)
		       (gsi-value-error-code error-code)
		       (gsi-ds-value value))
  (runtime-current-system-case
    (ab
      (gsi-receive-value-for-gsi-sensor gsi-sensor error-code value 'never nil))
    (gsi
      gsi-sensor error-code value
      nil)))

(defun-void gsi-receive-value-for-gsi-sensor-1 (gsi-sensor error-code value? timestamp?)
  (let ((collection-time? 'never))
    (if (and value? timestamp?)
	(with-guarded-timestamp ('receive-value-for-gsi-sensor-with-timestamp
				   (managed-float-value timestamp?))
	  (setq collection-time? timestamp?))
	(reclaim-if-managed-float timestamp?))
    (gsi-receive-value-for-gsi-sensor gsi-sensor error-code value? collection-time? nil)))

(def-icp-value-reader gsi-values
  (runtime-current-system-case
    (ab
      (let* ((timestamp-p (read-icp-boolean))
	     (count (read-icp-fixnum)))
	(loop with newp = (with-bifurcated-version-for-input
			      (gsi-dataservice-uses-full-remote-value-protocol-icp-version)
			    nil t)
	      for rpc-argument-list-error = nil
	      for index from 0 below count
	      for gsi-sensor = (read-icp-returned-gsi-sensor)
	      for error-code = (read-icp-unsigned-integer)
	      for current-slot-value-of-user-slot = (when newp gsi-sensor)
	      for value? = (read-icp-remote-value)
	      for framep = (framep-function value?)
	      for timestamp? = (when (and timestamp-p (not framep))
				 (read-icp-gsi-timestamp))
	      for collectp = (not (or framep (null gsi-sensor) rpc-argument-list-error))
	      when collectp
		collect (icp-list gsi-sensor error-code value? timestamp?)
		  using icp-cons
	      do (unless collectp
		   (reclaim-if-evaluation-value-1 value?)
		   (reclaim-if-managed-float timestamp?))
		 (reclaim-if-text-string rpc-argument-list-error))))))

(def-icp-message-type receive-values-for-gsi-sensors
		      ((gsi-values gsi-values))
  (current-system-case
    (ab
      (loop for value = (icp-pop gsi-values)
	    while value
	    for (gsi-sensor error-code value? timestamp?) = value
	    do
	(reclaim-icp-list value)
	(gsi-receive-value-for-gsi-sensor-1 gsi-sensor error-code value? timestamp?)))
    (gsi
      gsi-values)))


;;; Declaration:     receive-value-for-gsi-sensor-with-timestamp
;;;                    (gsi-sensor error-code value timestamp)
;;; Type:	     ICP message type.
;;; Purpose:	     Acquire a new timestamped value for a GSI sensor.
;;; Arguments:       gsi-sensor, error-code, and value are the same as in
;;;                  receive-value-for-gsi-sensor.  timestamp is a composite ICP
;;;                  data type gsi-timestamp, which returns a managed-float
;;;                  representing the timestamp as a unix-time value.  see the
;;;                  reader and writer for details.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (gsi-receive-value-for-gsi-sensor), "GSI in G2"
;;;                  machinery.
;;; Prerequisites:   The corresponding GSI sensor associated with gsi-sensor must
;;;                  have already been defined (using define-gsi-sensor).
;;; Side effects:    See gsi-receive-value-for-gsi-sensor in GSI.
;;; Non-local exits: None.
;;; Memory impact:   allocates memory for the new timestamped value; allocates
;;;                  a managed float for the time stamp.
;;; Notes:           Now (26 Jul 1994) rewritten to use new unix-time floating point
;;;                  timestamps internally.  The timestamp value has been abstracted
;;;                  as the icp-value-type gsi-timestamp, which is six ints to pre-4.0
;;;                  peers and a double to 4.0 and beyond.
;;;
(def-icp-message-type receive-value-for-gsi-sensor-with-timestamp
		      ((returned-gsi-sensor gsi-sensor)
		       (gsi-value-error-code error-code)
		       (gsi-ds-value value?)
		       (gsi-timestamp timestamp))
  (runtime-current-system-case
    (ab
      (let ((collection-time? 'never))
	(when value?
	  (with-guarded-timestamp ('receive-value-for-gsi-sensor-with-timestamp
				     (managed-float-value timestamp))
	    (setq collection-time? timestamp)))
	(gsi-receive-value-for-gsi-sensor gsi-sensor error-code value? collection-time? nil)))
    (t
      gsi-sensor error-code value? timestamp
      nil)))

;; jra & jh, 11/10/92.  Modified the ICP message
;; receive-value-for-gsi-sensor-with-timestamp to use encode-gensym-time, which
;; now no longer creates bignums.  We can expect a performance improvement in
;; Chestnut, since we no longer have to enter a temporary area.



;;; Declaration:     receive-gsi-sensor-value-vector
;;;                    (gsi-sensor error-code value vector)
;;; Type:		 ICP message type.
;;; Purpose:	     Receive a vector of values for a GSI sensor.
;;; Arguments:       gsi-sensor, error-code, and value are the same as in
;;;                  receive-value-for-gsi-sensor.  vector is of ICP type
;;;                  gsi-value-vector.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (gsi-receive-value-for-gsi-sensor), "GSI in G2"
;;;                  machinery.
;;; Prerequisites:   The corresponding GSI sensor associated with gsi-sensor must
;;;                  have already been defined (using define-gsi-sensor).
;;; Side effects:    See gsi-receive-value-for-gsi-sensor in GSI.
;;; Non-local exits: None.
;;; Memory impact:   See gsi-receive-value-for-gsi-sensor in GSI.

(def-icp-message-type receive-gsi-sensor-value-vector
		      ((returned-gsi-sensor gsi-sensor)
		       (gsi-value-error-code error-code)
		       (gsi-ds-value value)
		       (gsi-value-vector vector))
  (runtime-current-system-case
    (ab
      (gsi-receive-value-for-gsi-sensor gsi-sensor error-code value 'never vector))
    (t
      gsi-sensor error-code value vector
      nil)))


;;; Declaration:     receive-timestamped-gsi-sensor-value-vector
;;;                    (gsi-sensor error-code value
;;;                     timestamp timestamped-vector).
;;; Type:	     ICP message type.
;;; Purpose:	     Receive a vector of timestamped values for a GSI sensor.
;;; Arguments:       gsi-sensor, error-code, and value are the same as in
;;;                  receive-value-for-gsi-sensor.  timestamp is of ICP
;;;                  value type gsi-timestamp (see the reader and writer for
;;;                  details) and provides the timestamp for the main value of
;;;                  the GSI sensor.  timestamped-vector is of ICP value type
;;;                  gsi-value-vector.  Each attribute in timestamped-vector
;;;                  receives an individual timestamp, stored in the
;;;                  constant-expiration slot of the temporary-constant that
;;;                  holds the attribute value.
;;;                  Return behavior: No useful value.
;;; Users:           GSI internals (gsi-receive-value-for-gsi-sensor), "GSI in G2"
;;;                  machinery.
;;; Prerequisites:   The corresponding GSI sensor associated with gsi-sensor must
;;;                  have already been defined (using define-gsi-sensor).
;;; Side effects:    See gsi-receive-value-for-gsi-sensor in GSI.
;;; Non-local exits: None.
;;; Memory impact:   creates managed-floats.
;;; Notes:
;;;

(def-icp-message-type receive-timestamped-gsi-sensor-value-vector
		      ((returned-gsi-sensor gsi-sensor)
		       (gsi-value-error-code error-code)
		       (gsi-ds-value value?)
		       (gsi-timestamp timestamp)
		       (gsi-value-vector timestamped-vector))
  (runtime-current-system-case
    (ab
      (let ((collection-time? 'never))
	(when value?
	  (with-guarded-timestamp ('receive-timestamped-gsi-sensor-value-vector
				     (managed-float-value timestamp))
	    (setq collection-time? timestamp)))
	(gsi-receive-value-for-gsi-sensor gsi-sensor error-code value? collection-time? timestamped-vector)))
    (t
      gsi-sensor error-code value? timestamp timestamped-vector
      nil)))



;; jra & jh, 11/10/92.  Modified the ICP message
;; receive-timestamped-gsi-sensor-value-vector to use encode-gensym-time, which
;; now no longer creates bignums.  We can expect a performance improvement in
;; Chestnut, since we no longer have to enter a temporary area.

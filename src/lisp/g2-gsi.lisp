;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module G2-GSI

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson, Nick Caruso, and Peter Fandel




;;; File name:		     GSI.LISP
;;; File location:	     ma:>ab>
;;; Code control:	     Zmacs on the Explorers.
;;; Purpose:                 Implement GSI dataservice.
;;; Contents:                Functions for the GSI dataserver: initialze the
;;;                          dataserver, get and set values, accept unsolicited
;;;                          data, pause the dataserver, shut down the dataserver.
;;;                          Functions to manage GSI interface and variable objects
;;;                          in G2.
;;; This file depends on:    GSI-COMMON and preceding .LISP files in the system load
;;;                          ordering.
;;; Dependent files:	     Subsequent .LISP files in the system load ordering.
;;; Role in products:        Linked into G2.  Enables communication between the G2
;;;                          and GSI products.
;;; Role in development:     None.
;;; Testing harness:         Some GSI functionality is incorporated into the G2
;;;                          regression tests.  Doc may exist, or see Peter Fandel.
;;; Performace requirements: These functions and macros are the core of GSI
;;;                          dataservice.  Performance is critical.
;;; Major Entities:          [function]	    handle-update-to-sensor-attribute
;;;                          [function]	    handle-update-to-sensor-data-type
;;;                          [sys var]	    list-of-gsi-values-to-process-head
;;;                          [sys var]	    list-of-gsi-values-to-process-tail
;;;                          [sys var]	    task-to-process-gsi-values
;;;                          [sys var]	    task-to-process-gsi-interfaces
;;;                          [sys var]	    task-scheduled-to-process-gsi-values?
;;;                          [macro]	    save-gsi-variable-value-for-processing
;;;                          [function]	    get-or-make-gsi-sensor
;;;                          [sys var]	    max-gsi-sensors-in-a-group
;;;                          [structure]    sensor-group
;;;                          [structure]    sensor-groups-header
;;;                          [sys var]	    list-of-all-gsi-interfaces-head
;;;                          [sys var]	    list-of-all-gsi-interfaces-tail
;;;                          [sys var]	    gsi-interfaces-to-process-head
;;;                          [sys var]	    gsi-interfaces-to-process-tail
;;;                          [function]	    get-gsi-interface-for-gsi-sensor-if-any
;;;                          [function]	    reconfigure-gsi-sensor-attribute
;;;                          [function]	    define-or-configure-gsi-sensor
;;;                          [function]	    gsi-receive-value-for-gsi-sensor
;;;                          [function]	    process-gsi-sensor-values
;;;                          [ICP message]  return-gsi-extension-version
;;;                          [sys var]	    icp-sockets-now-initializing-gsi
;;;                          [function]	    write-message-group-upon-gsi-interface-
;;;                                           activation
;;;                          [cap'y act]    gsi-interface
;;;                          [function]	    activate-gsi-interface-
;;;                                           with-connection-spec
;;;                          [macro]	    clear-interface-from-gsi-processing-
;;;                                           queue
;;;                          [function]	    handle-gsi-shut-down-connection
;;;                          [cap'y deact]  gsi-interface
;;;                          [slot putter]  gsi-connection-configuration
;;;                          [slot putter]  identifying-attributes
;;;                          [slot putter]  grouping-specification
;;;                          [slot putter]  gsi-interface-status
;;;                          [function]	    shutdown-gsi-service-on-icp-socket
;;;                          [grammar]	    gsi-data-server
;;;                          [cap'y act]    gsi-data-service
;;;                          [cap'y deact]  gsi-data-service
;;;                          [cap'y act]    gsi-message-service
;;;                          [cap'y deact]  gsi-message-service
;;;                          [function]	    clear-pending-gsi-sensor-request
;;;                          [slot putter]  gsi-interface-name
;;;                          [function]	    gsi-deliver-messages
;;;                          [slot comp'r]  gsi-interface-name
;;;                          [data server]  gsi-data-server
;;;                          [function]	    gsi-process-gsi-interfaces
;;;                          [function]	    gsi-pause-data-server?
;;;                          [function]	    gsi-resume-data-server?
;;;                          [function]	    gsi-shut-down-data-server?
;;;                          [function]	    gsi-initialize-data-server
;;;                          [function]	    gsi-collect-one-shot-data
;;;                          [function]	    gsi-set-external-variable
;;;                          [function]	    gsi-begin-collecting-data
;;;                          [function]	    enqueue-gsi-request-for-sensor
;;;                          [function]     add-sensor-to-group-if-it-fits
;;;                          [function]	    put-sensor-in-new-sensor-group
;;;                          [function]	    gsi-stop-collecting-data
;;;                          [function]	    process-requests-for-gsi-interfaces
;;;                          [function]	    gsi-item-attribute-value
;;;                          [function]	    send-message-series-for-gsi-request
;;;                          [function]	    gsi-receive-value-for-ping-request
;;;                          [function]	    gsi-interface-ready-for-remote-
;;;                                           procedure-call
;;; Notes:                   > The term "sensor", used in many entity names, is
;;;                            obsolete.  The approved term is "GSI variable".  A
;;;                            GSI variable is any G2 frame of class variable which
;;;                            has gsi-data-service capability.  It is distinct from
;;;                            that variable as represented in the GSI extension
;;;                            process, called a "corresponding GSI variable" since
;;;                            it is a corresponding ICP object.  Corresponding GSI
;;;                            variables are implemented as gsi-sensor structures
;;;                            (see GSI-COMMON).
;;;                          > The term "GSI message variable" means any variable
;;;                            with gsi-message-service capability.
;;;                          > The term "GSI interface" means any G2 object with
;;;                            gsi-interface capability.  It is
;;;                            distinct from the representation of the interface in
;;;                            the GSI extension process, called a "corresponding
;;;                            GSI interface".



;;; GSI - Gensym Standard Interface defines a configurable interface to external
;;; programs. GSI multiplexes data requests from G2 through the data server interface
;;; finally routing them to the appropriate external system. Communication to external 
;;; systems uses ICP to do the buffered asychronous message transactions.



#+translator
(if (not (string-or-symbol-member 'gsi (optional-modules 'ab)))
    (push 'gsi (optional-modules 'ab)))

(declare-forward-reference
  activate-g2-to-g2-data-interface-with-or-without-configuration
  function) ;G2DS
(declare-forward-reference
  body-of-deactivate-for-g2-to-g2-data-interface
  function) ;G2DS


;; GSI interface

;;; Declaration:     gsi-interface
;;; Type:	     G2 def-structure.
;;; Purpose:	     Implement a corresponding ICP object for a local GSI interface.
;;; Slots:           > gsi-interface-frame contains the GSI interface to which this
;;;                    structure corresponds.
;;;                  > gsi-interface-frame-serial-number contains the fixnum serial
;;;                    number of the GSI interface to which this structure
;;;                    corresponds.  This is used to detect GSI interfaces which
;;;                    have been deleted and then reused.
;;;                  > gsi-interface-status-code contains a fixnum describing the
;;;                    condition of the GSI interface.  The following are
;;;                    pre-defined constants:
;;;                      gsi-interface-initializing
;;;                      gsi-interface-waiting-for-response
;;;                      gsi-interface-running-ok
;;;                      gsi-interface-assumed-dead
;;;                      gsi-interface-icp-connection-dead.
;;;                  > gsi-interface-countdown-timer is used by
;;;                    gsi-process-gsi-interfaces to determine if the GSI interface
;;;                    has timed out.  It is a fixnum which is set to the value of
;;;                    get-fixnum-time by gsi-process-gsi-interfaces.  The next time
;;;                    this function processes that GSI interface, it computes the
;;;                    fixnum-time-difference between this slot and the new fixnum
;;;                    time.  If the difference exceeds the value in the
;;;                    gsi-interface-countdown-timer-limit slot, then the GSI
;;;                    interface has timed out.
;;;                  > gsi-interface-timed-out-p set by gsi-process-gsi-interfaces
;;;                    and cleared in gsi-receive-value-for-ping-request.
;;;                  > gsi-interface-waiting-for-response-p is non-nil if the GSI
;;;                    interface is expecting GSI to provide some values.  This slot
;;;                    is examined, set, and cleared by gsi-process-gsi-interfaces
;;;                    and cleared by gsi-receive-value-for-ping-request.
;;;                  > gsi-interface-last-time-difference is set in
;;;                    gsi-receive-value-for-ping-request, but is not used anywhere.
;;;                  > The slots gsi-interface-year, gsi-interface-month,
;;;                    gsi-interface-day, gsi-interface-hour, gsi-interface-minute,
;;;                    and gsi-interface-second are not currently used.  They
;;;                    correspond to the unused arguments in
;;;                    gsi-receive-value-for-ping-request.
;;;                  > gsi-interface-countdown-timer-limit is a fixnum representing
;;;                    the interval after which the GSI interface is assumed to be
;;;                    timed out.  This slot is set to the interface-timeout-period
;;;                    slot of the GSI interface when this structure is created, and
;;;                    is updated by a slot putter whenever the slot is edited.
;;;                  > corresponding-icp-object-map-for-gsi-interface maps ICP
;;;                    sockets onto indices of the corresponding GSI interface in
;;;                    the remote GSI process.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    gsi-receive-value-for-ping-request
;;;                    gsi-process-gsi-interfaces
;;;                    gsi-pause-data-server?
;;;                    gsi-deliver-messages
;;;                    enqueue-gsi-request-for-sensor
;;;                    process-requests-for-gsi-interfaces
;;;                    handle-gsi-shut-down-connection
;;;                    gsi-interface ICP object type
;;; Prerequisites:   The macro def-structure must be defined.
;;; Side effects:    Defines a constructor macro make-gsi-icp-interface, which takes as
;;;                  arguments the initial values for slots: gsi-interface-frame,
;;;                  gsi-interface-frame-serial-number, gsi-interface-status-code,
;;;                  gsi-interface-countdown-timer,
;;;                  gsi-interface-countdown-timer-limit.  Defines a predicate
;;;                  gsi-icp-interface-p.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.

(def-structure (gsi-icp-interface
		 (:constructor
		   make-gsi-icp-interface
		   (gsi-interface-frame
		    gsi-interface-frame-serial-number
		    gsi-interface-countdown-timer
		    gsi-interface-countdown-timer-limit)))
  gsi-interface-frame
  (gsi-interface-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  gsi-interface-countdown-timer
  (gsi-interface-timed-out-p nil)
  (gsi-interface-waiting-for-response-p nil)
  gsi-interface-last-time-difference
  gsi-interface-timestamp		; replaces year, month, day,
					; hour, minute, second slots.
  gsi-interface-countdown-timer-limit
  (corresponding-icp-object-map-for-gsi-icp-interface nil))

(defun-simple reclaim-gsi-icp-interface-function (gsi-icp-interface)
  (reclaim-gsi-icp-interface gsi-icp-interface))

(def-icp-object-type gsi-icp-interface
		     (standard-icp-object-index-space
		       (corresponding-icp-object-map-for-gsi-icp-interface gsi-icp-interface)
		       reclaim-gsi-icp-interface-function)
  (send-icp-define-gsi-interface corresponding-icp-object-index))

(defmacro send-icp-send-data-values-if-any-1 (gsi-interface year month day hour minute second)
  `(send-icp-send-data-values-if-any
     (or (get-icp-object-index-for-gsi-icp-interface ,gsi-interface current-icp-port)
	 (let ((index 0))
	   ;; use with-bifurcated-version here (not needed if new enough)
	   (writing-icp-message-group ((icp-output-port current-icp-socket))
	     (setq index (make-corresponding-icp-gsi-icp-interface ,gsi-interface)))	   
	   index))
     ,year ,month ,day ,hour ,minute ,second))






;;; Declaration:     gsi-interface
;;; Type:	     G2 capability.
;;; Purpose:	     Configure a G2 object to act as a GSI interface.
;;; Slots:           System slots added by this capability:
;;;                  > gsi-connection-configuration uses gsi-host-configuration
;;;                    grammar to produce a list in icp-connection-configuration
;;;                    format (see INT1).  This slot is saved with the KB.
;;;                  > external-system-has-a-scheduler is of type yes-or-no
;;;                    (producing Lisp t or nil) and is saved with the KB.
;;;                  > poll-external-system-for-data is of type yes-or-no (producing
;;;                    Lisp t or nil) and is saved with the KB.
;;;                  > grouping-specification uses
;;;                    gsi-variable-grouping-specification grammar (producing a Lisp
;;;                    list of symbols) and is saved with the KB.  In versions 2.1
;;;                    and earlier, this slot was named
;;;                    sensor-grouping-specification.
;;;                  > identifying-attributes uses
;;;                    attributes-which-identify-a-gsi-variable grammar (producing a
;;;                    Lisp list of symbols) and is saved with the KB.  In version
;;;                    2.1 and earlier, this slot was named
;;;                    attributes-which-identify-a-sensor.
;;;                  > remote-process-initialization-string is of type text
;;;                    (producing a list of Lisp strings and formatting directives)
;;;                    and is saved with the KB.
;;;                  > interface-timeout-period uses timeout-interval-or-default
;;;                    grammar (producing either a fixnum or the symbol default) and
;;;                    is saved with the KB.
;;;                  > gsi-interface-icp-socket contains either an icp-socket
;;;                    structure or nil.  This slot is invisible to the G2 user and
;;;                    is not saved with the KB.
;;;                  > gsi-sensor-groups-header contains a sensor-groups-header
;;;                    structure.  This slot is invisible to the G2 user and is
;;;                    saved with the KB.
;;;                  > gsi-interface-structure contains either a
;;;                    gsi-interface-structure or nil.  This slot is invisible to
;;;                    the G2 user and is saved with the KB.
;;;                  > gsi-sensor-structure is invisible to the G2 user and not
;;;                    saved with the KB.  This slot is not currently used.
;;;                  > gsi-interface-status is initially 0.  It is not saved with
;;;                    the KB and is read-only to the G2 user.  For a list of
;;;                    pre-defined statuses, see the documentation for the
;;;                    gsi-interface def-structure in GSI-COMMON.
;;;                  There are no user slots added by this capability.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (module GSI), describe-frame class method in
;;;                  QUERIES.
;;; Prerequisites:   The def-capability macro must be defined.
;;; Side effects:    Defines accessors for capability slots and a
;;;                  gsi-interface-p predicate macro.
;;; Non-local exits: None.
;;; Memory impact:   Adds some system slots to an object.
;;; Notes:           Consider renaming those slots which can be nil to use ?  or -p

;;; GSI interface capability enables an object to serve as an interface
;;; configuration table for a GSI interface.  The configuration covers both the
;;; icp connection type (between G2 and the remote process), and the how the
;;; particular interface groups data requests for improved data aquisition
;;; efficiency.

(def-class (network-interface
	    object not-solely-instantiable not-user-instantiable
	    (foundation-class network-interface)
	    define-predicate)
  (identifying-attributes
    nil (system) user-overridable
    (type attributes-which-identify-a-network-item-reference)
    (save))
  (creation-attributes
    nil (system) user-overridable do-not-put-in-attribute-tables
    (type attributes-which-identify-a-network-item-reference)
    (save))
  (item-reference-options
    nil (system) user-overridable do-not-put-in-attribute-tables
    (type options-for-item-reference)
    (save))
   
  (names-of-remote-interface
    nil (system) user-overridable do-not-put-in-attribute-tables
    (type name-or-names) (save))
  (class-of-remote-interface
    nil (system) user-overridable do-not-put-in-attribute-tables
    (type symbol) (save))

  (interface-warning-message-level
    warning-message-level (system) (type interface-warning-message-level)
    user-overridable (save))
  (disable-interleaving-of-large-messages
     nil (system) user-overridable
    (type yes-or-no) (save))

  (interface-timeout-period
    nil (lookup-slot) (system) user-overridable
    (type timeout-interval-or-default)
    (save))
  (interface-initialization-timeout-period
    nil (lookup-slot) (system) user-overridable
    (type timeout-interval-or-default-or-none)
    (save))
  )

(defun-for-system-procedure enable-control-of-disable-interleaving-of-large-messages ()
  (loop for class being the subclasses of 'network-interface
	do
    (loop for slot-name in '(disable-interleaving-of-large-messages)
	  for slot-description = (slot-description-from-class class slot-name)
	  do
      (setf (slot-features slot-description)
	    (delete 'do-not-save
		    (delete 'do-not-put-in-attribute-tables
			    (slot-features slot-description)
			    :key #'car)
		    :key #'car))))
  (copy-evaluation-truth-value evaluation-true-value))

#+gsi-in-g2
(defun-for-system-procedure enable-loadable-bridges ()
  (unless loadable-bridges-enabled-p
    (setq loadable-bridges-enabled-p t)
    (with-permanent-gensym-float-creation
      (add-grammar-rules
	'((gsi-host-configuration
	   ('local 'emulator)
	   (localnet localhost))))))
  (copy-evaluation-truth-value evaluation-true-value))

(def-class-method note-runs-while-inactive-change (network-interface)
  (funcall-superior-method network-interface)
  (unless (active-p network-interface)
    (cond
      ((runs-while-inactive-p network-interface)
       (frame-class-case network-interface
	 (gsi-interface
	   (activate-gsi-interface network-interface nil))
	 (g2-to-g2-data-interface
	   (activate-g2-to-g2-data-interface-with-or-without-configuration
	     network-interface))))
      (t (frame-class-case network-interface
	   (gsi-interface
	     (body-of-deactivate-for-gsi-interface network-interface t))
	   (g2-to-g2-data-interface
	     (body-of-deactivate-for-g2-to-g2-data-interface
	       network-interface)))))))

(def-class (gsi-interface
	     network-interface
	     (foundation-class object)
	     (disjoint-from g2-to-g2-data-interface
			    gfi-input-interface gfi-output-interface)
	     define-predicate)
  (gsi-connection-configuration
    (nil (lost-spaces . 0) "none") (system)
    ;; was not a type TEXT type slot transiently during development and a Beta
    ;; release, which caused problems.  From 5/31/96 to 5/14/97.  (MHD 5/14/97)
    (type gsi-host-configuration text)
    (save))
  (external-system-has-a-scheduler
     nil (system) user-overridable
    (type yes-or-no) (save))
  (poll-external-system-for-data
     nil (system) user-overridable
    (type yes-or-no) (save))
  (grouping-specification
     no-grouping (system) user-overridable
    (type gsi-variable-grouping-specification)
    (save))
  
  (remote-process-initialization-string
    "" (system) user-overridable
    (type process-initialization-string) ; formerly a TEXT type slot (MHD 5/31/96)
    (save))
  (gsi-application-name
    default (system) user-overridable
    (type gsi-application-name-symbol)
    (save))
  (gsi-interface-icp-socket			; USE THIS SLOT FOR THE ICP SOCKET
     nil (system)				; CONNECTING GSI TO THE EXTERNAL PROCESS!!
    (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-sensor-groups-header
     nil (system)
    (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-interface-structure
     nil (system)
    (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-interface-status 0
    (system)
    (type gsi-interface-status-code) (do-not-save) (not-user-editable))
  (gsi-interface-is-secure
    nil (system)
    (type yes-or-no) (do-not-save) (not-user-editable))

  (gsi-interface-activate-after-shutdown ; supports shutdown handshake!
    nil (system)
    (do-not-put-in-attribute-tables) (do-not-save))
  
  (interval-to-poll-external-system
    nil (system) user-overridable
    (type timeout-interval-or-default)
    (save))
  (time-of-next-poll
    nil (system)
    (do-not-put-in-attribute-tables) (do-not-save))
  (include-method-text-in-class-export
    nil system
    (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-interface-session-id		; Used to find associated G2-WINDOW.
    nil (lookup-slot) (system) (do-not-put-in-attribute-tables) (do-not-save)))

(def-references-slot creation-attributes)
(def-references-slot item-reference-options)
(def-references-slot names-of-remote-interface)
(def-references-slot class-of-remote-interface)

(def-class (remote-item
	    (entity item)
	    (foundation-class remote-item)
	    ;do-not-put-in-menus
	    define-predicate)  
  (icon-description ; copied from media-bin, and edited a bit
    (:funcall-at-load-time
      create-icon-description
      90 60
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (icon-color . foreground)
		   (g2-icon-specialty-region-1 . black)
		   (g2-icon-specialty-region-2 . gray))
       g2-icon-background
       (solid-rectangle (0 0) (80 50))
       g2-icon-light-shading
       (filled-polygon ((0 0) (80 0) (77 3) (3 3) (3 47) (0 50))
		       ((0 0) (80 0) (77 3)) ((3 3) (3 47) (0 50))
		       ((0 0) (77 3) (3 3)) ((3 3) (0 50) (0 0)))
       g2-icon-dark-shading
       (filled-polygon ((77 3) (80 0) (80 50) (0 50) (3 47) (77 47))
		       ((77 3) (80 0) (80 50))
		       ((80 50) (0 50) (3 47))
		       ((77 47) (77 3) (80 50))
		       ((80 50) (3 47) (77 47)))
       icon-color
       (outline (0 0) (0 50) (80 50) (80 0))
       (text "REMOTE" (10 21) small)
       (text "-ITEM" (18 35) small)
       (lines (74 5) (5 5) (5 45))
       g2-icon-light-shading
       (lines (5 45) (74 45) (74 5)))))
  (item-home nil (system) (type item-or-datum) (do-not-put-in-attribute-tables))
  (item-identifying-attributes nil (system) (type datum) (do-not-put-in-attribute-tables))
  (item-creation-attributes nil (system) (type datum) (do-not-put-in-attribute-tables)))

(def-slot-value-writer gsi-interface-status-code (integer)
    (twrite-fixnum integer))

(define-category-evaluator-interface (gsi-interface-status-code
				       :access read)
    integer
  ((get-form (slot-value)) slot-value))

(add-grammar-rules
  `((interface-warning-message-level ('default 'to 'warning 'message 'level)
				     warning-message-level)
    (interface-warning-message-level ('0 '\( 'no 'warning 'or 'error 'messages '\) ) 1)
    (interface-warning-message-level ('1 '\( 'serious 'error 'messages 'only '\) ) 1)
    (interface-warning-message-level ('2 '\( 'all 'error 'messages '\) ) 1)
    (interface-warning-message-level ('3 '\( 'all 'error 'and 'warning 'messages '\) ) 1)
    ))

(def-slot-value-writer interface-warning-message-level (value)
  (twrite
    (case value
      (warning-message-level "default to warning message level")
      (0 "0 (no warning or error messages)")
      (1 "1 (serious error messages only)")
      (2 "2 (all error messages)")
      (3 "3 (all error and warning messages)"))))

(defmacro with-interface-warning-message-level (network-interface &body forms)
  (avoiding-variable-capture (&aux interface-warning-message-level)
    `(let* ((,interface-warning-message-level
	       (interface-warning-message-level ,network-interface))
	    (warning-message-level
	      (if (eq 'warning-message-level ,interface-warning-message-level)
		  warning-message-level
		  ,interface-warning-message-level)))
       ,@forms)))

(add-grammar-rules
  '((gsi-application-name-symbol unreserved-symbol)))

(define-category-evaluator-interface (gsi-application-name-symbol
				       :access read-write)
    (named unreserved-symbol)
  ((set-form (evaluation-value))
   (call-category-setter 'unreserved-symbol evaluation-value nil nil nil))
  ((get-form (slot-value))
   slot-value))

(def-slot-value-compiler gsi-application-name-symbol (parse-result)
  parse-result)

(def-slot-value-writer gsi-application-name-symbol (symbol)
  (tprinc symbol))

(defun-simple localnetp (x)
  (eq x 'localnet))

;;; The category evaluator interface for `gsi-host-configuration' leaves the
;;; actual slot value in its historical form of slot-list or nil.

(define-category-evaluator-interface (gsi-host-configuration
                                      :access read-write)
    (or (no-item)
	(structure gsi-host-configuration
	  ((network-transport (member tcp-ip #+gsi-in-g2 localnet))
	   (hostname (or text symbol #+gsi-in-g2 (no-item)))
	   (port (or integer symbol #+gsi-in-g2 (no-item))))
	  (and network-transport
	       (or #+gsi-in-g2 (localnetp network-transport) 
		   (and hostname port)))))
  ((set-form (evaluation-value?))
   (if evaluation-value?
       (evaluation-etypecase evaluation-value?
         ((structure)
	  (with-structure (evaluation-value? gsi-host-configuration)
	    (case network-transport
	      (localnet
	       (if (or #+gsi-in-g2 loadable-bridges-enabled-p)
		   (managed-backquote phrase-cons
				      (\,network-transport \,hostname))
		   (values bad-phrase
			   (tformat-text-string
			     "The supplied value for network-transport, ~NV, must be tcpip"
			     network-transport))))
	      (otherwise
	       (if (or (null hostname) (null port))
		   (values bad-phrase
			   (tformat-text-string "Both hostname and port must be supplied"))
		   (managed-backquote phrase-cons
				      (\,network-transport \,hostname \,port))))))))
       'none))
  ((get-form (slot-value?))
   (if slot-value?
       (gensym-dstruct-bind
	   ((this-network-transport this-hostname this-port) slot-value?)
	 (case this-network-transport
	   (localnet
	    (with-new-structure (gsi-host-configuration)
	      (setf network-transport
		    (copy-evaluation-value this-network-transport))
	      (setf hostname (copy-evaluation-value this-hostname))))
	   (otherwise
	    (with-new-structure (gsi-host-configuration)
	      (setf network-transport
		    (copy-evaluation-value this-network-transport))
	      (setf hostname (copy-evaluation-value this-hostname))
	      (setf port (copy-evaluation-value this-port))))))
       nil)))

(define-category-evaluator-interface (process-initialization-string
				       :access read-write)
    (named whole-string)
  ((set-form (evaluation-value?))
   (if evaluation-value?
       (call-category-setter 'whole-string evaluation-value? nil nil nil)
       #w""))
  ((get-form (slot-value?))
   (if slot-value?
       (call-category-getter 'whole-string slot-value? nil nil)
       (make-evaluation-text #w"") ;defensive
       )))

(def-absent-slot-putter gsi-interface-timeout-period
    (gsi-interface new-gsi-interface-timeout-period)
  (setf (interface-timeout-period gsi-interface)
	new-gsi-interface-timeout-period))

(def-slot-putter interval-to-poll-external-system
    (gsi-interface value initializing?)
  (declare (ignore initializing?))
  (setf (interval-to-poll-external-system gsi-interface) value)
  (let ((time-of-next-poll (time-of-next-poll gsi-interface))
	(new-time-of-poll (g2-future-interval (if (fixnump value) value 1))))
    (unless time-of-next-poll
      (setq time-of-next-poll (allocate-managed-float 0.0))
      (setf (time-of-next-poll gsi-interface) time-of-next-poll))
    (when (<e new-time-of-poll (managed-float-value time-of-next-poll))
      (setf (managed-float-value time-of-next-poll)
	    new-time-of-poll)))
  value)

(defun-for-system-procedure g2-set-gsi-interface-interval-to-poll-external-system
    (gsi-interface interval)
  (unless (or (and (fixnump interval)
		   (<f 0 interval))
	      (eq interval 'default))
    (stack-error
      cached-top-of-stack
      "Invalid interval ~NV should be the symbol default or a positive integer"
      interval))
  (change-slot-value gsi-interface 'interval-to-poll-external-system interval))


;; jh per ghw & mhd, 4/27/94.

;; Changed the gsi-interface-timeout-period slot of gsi-interface in G2-GSI back
;; to interface-timeout-period.  Also changed the name of the
;; g2ds-interface-timeout-period slot of g2-to-g2-data-interface in G2DS back to
;; to interface-timeout-period.  Since these classes are disjoint (cannot be
;; mixed in an inheritance path), ambiguous slot references will not be a
;; problem.  Nonetheless, we should keep the behavior of these two slots as
;; similar as possible, for the end user's sake.  Note that we use a no-accessor
;; slot option in one of the def-classes in order to generate only a single set
;; of setf methods and the like.  This would not work with non-lookup slots.

(defun-simple gsi-interface-connects-while-inactive-p (gsi-interface)
  (and (not (or (manually-disabled-p gsi-interface)
		(ancestor-not-activatable-p gsi-interface)))
       (runs-while-inactive-p gsi-interface)))

(def-class-method initialize-after-reading (gsi-interface)
  (funcall-superior-method gsi-interface)
  (when (gsi-interface-connects-while-inactive-p gsi-interface)
    (activate-gsi-interface gsi-interface nil))
  (update-representations-of-slot-value gsi-interface 'gsi-interface-status))






;;; declaration:     attributes-which-identify-a-gsi-variable
;;; Type:	     G2 slot value compiler.
;;; Purpose:         Obtain from a G2 user the identifying-attributes used by a GSI
;;;                  interface.
;;; Accepts: 	     "<attribute-symbol-1>, <attribute-symbol-2>, ..."
;;; Return behavior: A list of symbols naming identifying-attributes which the GSI
;;;                  interface will transmit to the remote GSI process to enable it
;;;                  to distinguish corresponding GSI variables.
;;; Users:	     GSI internals (module GSI).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   The list is reclaimed automatically when next edited.

;; jh, 5/13/92.  Changed the slot name attributes-which-identify-a-sensor to
;; identifying-attributes and the slot name sensor-grouping-specification to
;; grouping-specification.  This is because sensors are an obsolete class and so
;; G2 should never refer to them.  To accomplish this change, had to eliminate
;; the text type tag from these slots, and had to add absent-slot putters, new
;; grammar, slot-value compilers, and slot-value writers for them.  Finally, had
;; to change all the users of these slots, since the internal structure has
;; changed.

;; old (pre 5/13/92) format for attributes-which-identify-a-sensor:
;;   ( ( \, <attribute1> <attribute2> ...) ... text info ...) ;>1 elements
;;   ( <attribute> ... text info ...)                         ;1 element
;;   nil                                                      ;0 elements (not yet edited)

;; (post 5/13/92) format for identifying-attributes
;;    ( <attribute1> <attribute2> ...) ;>1 elements
;;    ( <attribute> )                  ;1 element
;;    nil                              ;0 elements (not yet edited)

;; (post 8/25/96) format for identifying-attributes
;;    ( <attribute-or-info1> <attribute-or-info2> ...) ;>1 elements
;;    ( <attribute-or-info> )                          ;1 element
;;    nil                                              ;0 elements (not yet edited)
;; <attribute-or-info> is
;;    <attribute>
;;    (<class-name> <class-attribute-info1> <class-attribute-info2> ...)
;; <class-attribute-info> is
;;    (<attribute> . nil)
;;    (<attribute> . <attribute-name-for-network>)

(def-absent-slot-putter attributes-which-identify-a-sensor
			(interface-frame attributes-within-text)
  (set-slot-value 
    interface-frame 
    'identifying-attributes
    (and attributes-within-text
	 (let ((symbol-or-comma-headed-list
		 (car attributes-within-text)))
	   (if (symbolp symbol-or-comma-headed-list)
	       (slot-value-list symbol-or-comma-headed-list)
	       (copy-for-slot-value (cdr symbol-or-comma-headed-list))))))
  (reclaim-slot-value attributes-within-text))

(add-grammar-rules
  '((attributes-which-identify-a-network-item-reference 'none) ;ghw, 7/25/96
    (attributes-which-identify-a-network-item-reference
     list-of-attribute-names-or-translations)
    (list-of-attribute-names-or-translations network-attribute-name-or-translation)
    (list-of-attribute-names-or-translations 
      (network-attribute-name-or-translation '\, list-of-attribute-names-or-translations)
      (2 1 3) simplify-associative-operation)
    (network-attribute-name-or-translation system-or-user-defined-attribute-name)))
;; See enable-references-for-item-passing for the rest of this grammar

(def-slot-value-compiler attributes-which-identify-a-network-item-reference
    (parse-result)
  (cond ((eq parse-result 'none)
	 nil)
	((symbolp parse-result)
	 (slot-value-list parse-result))
	((class-qualified-name-denotation-p parse-result)
	 (slot-value-list (slot-value-list (first parse-result)
					   (second parse-result)
					   (third parse-result))))
	((eq (car parse-result) '\,)
	 (loop for attribute-name-or-translation in (cdr parse-result)
	       collect (cond ((symbolp attribute-name-or-translation)
			      attribute-name-or-translation)
			     ((class-qualified-name-denotation-p attribute-name-or-translation)
			      (slot-value-list (first attribute-name-or-translation)
					       (second attribute-name-or-translation)
					       (third attribute-name-or-translation)))
			     (t ; car is 'class
			      (compile-network-class-attribute-translation
				attribute-name-or-translation)))
	       using slot-value-cons))
	(t ; car is 'class
	 (slot-value-list
	   (compile-network-class-attribute-translation parse-result)))))

(defun compile-network-attribute-translation (translation)
  (cond ((symbolp translation)
	 (slot-value-cons translation nil))
	((class-qualified-name-denotation-p translation)
	 (slot-value-cons (let ((attr-name translation))
			    (slot-value-list (first attr-name)
					     (second attr-name)
					     (third attr-name)))
			  nil))
	(t
	 (slot-value-cons
	   (if (class-qualified-name-denotation-p (first translation))
	       (let ((attr-name (first translation)))
		 (slot-value-list (first attr-name)
				  (second attr-name)
				  (third attr-name)))
	       (first translation))
	   (second translation)))))

(defun-simple compile-network-class-attribute-translation (translation)
  (slot-value-cons
    (second translation) ;class
    (let ((translations (third translation)))
      (if (and (consp translations) (eq (first translations) '\,))
	  (loop for translation in (cdr translations)
		collect (compile-network-attribute-translation translation)
		  using slot-value-cons)
	  (slot-value-list (compile-network-attribute-translation translations))))))



;;; Declaration:     attributes-which-identify-a-network-item-reference
;;; Type:	     G2 slot value writer.
;;; Purpose:         Present to a G2 user the identifying-attributes used by a GSI
;;;                  interface.
;;; Arguments:       The value of the attributes-which-identify-a-network-item-reference 
;;;                  slot in the network interface.
;;; Return behavior: No useful value.
;;; Users:	     TABLES.
;;; Prerequisites:   To be called within a twith-output-to-text-string scope.
;;; Side effects:    Writes the identifying-attributes, separacted by commas.
;;; Non-local exits: None.
;;; Memory impact:   None.

(def-slot-value-writer attributes-which-identify-a-network-item-reference
		       (identifying-attributes)
  (cond
    ((consp identifying-attributes)
     (loop for attribute in identifying-attributes
	   for attribute-cons on identifying-attributes
	   for last-attribute-p = (null (cdr attribute-cons))
	   do (if (symbolp attribute)
		  (write-name-or-class-qualified-name attribute)
		  (write-class-attribute-translation attribute))
	      (unless last-attribute-p
		(twrite-string ", "))))		      
    (t (twrite-string "none"))))

(defun-void write-class-attribute-translation (translation)
  (twrite-string "(items of class ")
  (write-name-denotation (car translation))
  (cond ((eq (caadr translation) '*)
	 (twrite-string " have all attributes in the attribute ")
	 (write-name-denotation (cdadr translation)))
	(t
	 (twrite-string " have attributes ")
	 (loop with translations = (cdr translation)
	       for (attribute . network-attribute) in translations
	       for tail on translations
	       for last-attribute-p = (null (cdr tail))
	       do (write-name-denotation attribute)
		  (when network-attribute
		    (twrite-string " having network name ")
		    (write-name-denotation network-attribute))
		  (unless last-attribute-p
		    (twrite-string ", ")))))
  (twrite-string ")"))


;home
;  serve items by proxy / no home conversion
;name
;  name includes home [ unless local ]
;  no name conversion
;class
;  use class item-class for non local items
;  use prefix string for the class of non local items, with default class item-class
;  no class conversion
;lookup
;  look up references using identifying attributes
;  do not lookup references
;creation
;  create references using creation attributes
;  do not create references

(add-grammar-rules
  '((options-for-item-reference 'none)
    (options-for-item-reference option-for-item-reference)
    (options-for-item-reference
     (option-for-item-reference '\; options-for-item-reference)
     (2 1 3) simplify-associative-operation)
    (option-for-item-reference home-conversion-option)
    (option-for-item-reference name-conversion-option)
    (option-for-item-reference class-conversion-option)
    (option-for-item-reference reference-lookup-option)
    (option-for-item-reference reference-creation-option)
    
    (home-conversion-option ('serve 'items 'by 'proxy) 
     (convert-home-to-local t))
    (home-conversion-option ('no 'home 'conversion)
     (convert-home-to-local nil))
    
    (name-conversion-option
     ('name 'includes 'home)
     (add-home-to-name t))
    (name-conversion-option
     ('name 'includes 'home 'unless 'local)
     (add-home-to-name unless-local))
    (name-conversion-option
     ('no 'name 'conversion)
     (add-home-to-name nil))
    
    (class-conversion-option
     ('use 'class item-class 'for 'non 'local 'items)
     (non-local-item-class 3 nil))
    (class-conversion-option
     ('use 'prefix string 'for 'the 'class 'of 'non 'local 'items)
     (non-local-item-class nil 3))    
    (class-conversion-option
     ('use 'prefix string 'for 'the 'class 'of 'non 'local 'items
      '\, 'with 'default 'class item-class)
     (non-local-item-class 15 3))
    (class-conversion-option
     ('no 'class 'conversion)
     (non-local-item-class nil nil))

    (reference-lookup-option
     ('look 'up 'references 'using 'identifying 'attributes)
     (reference-lookup t))
    (reference-lookup-option
     ('do 'not 'look 'up 'references)
     (reference-lookup nil))
    
    (reference-creation-option
     ('create 'references 'using 'creation 'attributes)
     (reference-creation t))
    (reference-creation-option
     ('do 'not 'create 'references)
     (reference-creation nil))))

;alist
;  (convert-home-to-local <value>) ; nil, t
;  (add-home-to-name <value>)      ; nil, unless-local, t
;  (non-local-item-class <class> <class-prefix-string>)
(def-slot-value-compiler options-for-item-reference (parse-result)
  (cond
    ((atom parse-result)
     nil)
    ((eq (car parse-result) '\;)
     (copy-tree-using-slot-value-conses (cdr parse-result)))
    (t
     (slot-value-list (copy-tree-using-slot-value-conses parse-result)))))

(def-slot-value-writer options-for-item-reference (options)
  (if options
      (loop for option in options
	    for tail on options
	    for last-p = (null (cdr tail))
	    do (case (first option)
		 (convert-home-to-local
		  (twrite-string (if (second option)
				     "serve items by proxy"
				     "no home conversion")))
		 (add-home-to-name
		  (twrite-string (case (second option)
				   ((t)            "name includes home")
				   ((unless-local) "name includes home unless local")
				   ((nil)          "no name conversion"))))
		 (non-local-item-class
		  (if (second option)
		      (if (third option)
			  (tformat "use prefix ~S for the class of non local items,~
                                    with default class ~NN"
				   (third option) (second option))
			  (tformat "use class ~NN for non local items"
				   (second option)))
		      (if (third option)
			  (tformat "use prefix ~S for the class of non local items"
				   (third option))
			  (tformat "no class conversion"))))
		 (reference-lookup-option
		  (twrite-string (case (second option)
				   ((t)   "look up references using identifying attributes")
				   ((nil) "do not look up references"))))
		 (reference-creation-option
		  (twrite-string (case (second option)
				   ((t)   "create references using creation attributes")
				   ((nil) "do not create references")))))
	       (unless last-p
		 (twrite-string ";")))	      
      (twrite-string "none")))





;;; Declaration:     gsi-variable-grouping-specification
;;; Type:	     G2 slot value compiler.
;;; Purpose:         Obtain from a G2 user a specification of how a GSI interface
;;;                  should group requests for the values of GSI variables.
;;; Accepts: 	     "<attribute-symbol-1>, <attribute-symbol-2>, ..."
;;; Return behavior: A list of symbols naming the identifying-attributes of GSI
;;;                  variables the GSI interface will check.  The GSI interface will
;;;                  place in the same group all those GSI variables for which the
;;;                  values of these attributes are all identical.
;;; Users:	     GSI internals (module GSI).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   The list is reclaimed automatically when next edited.

(defvar no-grouping-tag-for-grouping-specification 'no-grouping)

(add-grammar-rules
  '((gsi-variable-grouping-specification 
     ('group 'requests 'by list-of-gsi-variable-attribute-names)
     (\, 4) simplify-associative-operation)
    (gsi-variable-grouping-specification
     ('no 'grouping) no-grouping)
    (attributes-which-identify-a-gsi-variable 'none) ;ghw, 7/25/96
    (attributes-which-identify-a-gsi-variable
     list-of-gsi-variable-attribute-names)
    (list-of-gsi-variable-attribute-names gsi-variable-attribute-name)
    (list-of-gsi-variable-attribute-names 
     (gsi-variable-attribute-name '\, list-of-gsi-variable-attribute-names)
     (2 1 3) simplify-associative-operation)
    (gsi-variable-attribute-name user-attribute-name)))



(def-slot-value-compiler gsi-variable-grouping-specification (parse-result)
  (if (eq parse-result 'no-grouping)
      'no-grouping
      (cdr parse-result)))

;; old (pre 5/13/92) format for sensor-grouping-specification:
;; ( ( \, ( \, <attribute1> <attribute2> ...)) ... <text info> ...) ;>1 elements
;; ( ( \, <attribute> ) ... <text info> ...)                        ;1 element
;; ( no-grouping ... <text info> ...)                               ;explicit "no grouping"
;; nil                                                              ;0 elts (not yet edited)

;; new (post 5/13/92) format for grouping-specification
;; ( <attribute1> <attribute2> ...) ;>1 elements
;; ( <attribute> )                  ;1 element
;; no-grouping                      ;explicit "no grouping"
;; nil                              ;0 elts (not yet edited)




(def-absent-slot-putter sensor-grouping-specification
			(interface-frame grouping-specification-within-text)
  (set-slot-value 
    interface-frame
    'grouping-specification
    (and grouping-specification-within-text
	 (let ((old-value-within-text
		 (car grouping-specification-within-text)))
	   (if (eq 'no-grouping old-value-within-text)
	       no-grouping-tag-for-grouping-specification
	       (let* ((symbol-or-comma-headed-list 
			(cadr old-value-within-text))
		      (actual-value
			(if (symbolp symbol-or-comma-headed-list)
			    (slot-value-list symbol-or-comma-headed-list)
			    (copy-for-slot-value 
			      (cdr symbol-or-comma-headed-list)))))
		 (reclaim-slot-value grouping-specification-within-text)
		 actual-value))))))



;;; Declaration:     gsi-variable-grouping-specification
;;; Type:	     G2 slot value writer.
;;; Purpose:         Present to a G2 user the grouping-specification used by a GSI
;;;                  interface.
;;; Arguments:       The value of the gsi-variable-grouping-specification slot in
;;;                  the GSI interface.
;;; Return behavior: No useful value.
;;; Users:	     TABLES.
;;; Prerequisites:   To be called within a twith-output-to-text-string scope.
;;; Side effects:    Writes the elements in the grouping-specification, separated by
;;;                  commas.
;;; Non-local exits: None.
;;; Memory impact:   None.

(def-slot-value-writer gsi-variable-grouping-specification 
		       (grouping-specification)
  (cond ((eq grouping-specification no-grouping-tag-for-grouping-specification)
	 (twrite-string "no grouping"))
	((consp grouping-specification)
	 (twrite-string "group requests by ")
	 (loop for attribute in grouping-specification
	       for attribute-cons on grouping-specification
	       for last-attribute-p = (null (cdr attribute-cons))
	       do (twrite-symbol attribute)
		  (unless last-attribute-p
		    (twrite-string ", "))))
	((null grouping-specification)
	 (twrite-string ""))))





;;; Declaration:     gsi-host-configuration
;;; Type:	     G2 slot value compiler.
;;; Purpose:         Obtain from the user the network address of teh remote GSI
;;;                  process to be used for GSI dataservice.
;;; Accepts:         "tcp-ip host <host-text> port-number <integer>"
;;; Return behavior: A list in icp-connection-configuration format (see INT1).
;;; Users:	     GSI internals (module GSI).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   The list is reclaimed automatically when next edited.

;; jh, 10/24/91.  Added "none" as an option for gsi-host-specification.  With
;; the advent of the "change the text" action, the user is more likely to want
;; to set and clear the icp-connection-specification while g2 is running.  In
;; addition, caused G2 to emit warning messages only when it can't connect to a
;; GSI interface which specifies a host configuration, since the user may want
;; to start a kb with several unconnected interface and change the text to a
;; true connection specification later.  Analogous changes were made to G2DS
;; interface objects.

(defun valid-icp-connection-specification-from-parse
    (parse-result localnet-valid-p)
  (gensym-dstruct-bind ((network-transport hostname port?) parse-result)
    (case network-transport
      (tcp-ip
       (let ((hostname-is-text-string-p (text-string-p hostname))
	     (port-is-fixnum-p (fixnump port?)))
	 (if (and hostname-is-text-string-p port-is-fixnum-p)
	     parse-result
	     (values
	       bad-phrase
	       (tformat-text-string "~A~A~A"
		 (if hostname-is-text-string-p
		     ""
		     "TCP/IP hostname must be text")
		 (if (or hostname-is-text-string-p port-is-fixnum-p)
		     ""
		     " and ")
		 (if port-is-fixnum-p
		     ""
		     "TCP/IP port must be an integer"))))))
      (localnet
       (let ((localnet-hostname-valid-p (eq hostname 'localhost))
	     (localnet-port-valid-p (null port?)))
	 (if (and localnet-valid-p
		  localnet-hostname-valid-p
		  localnet-port-valid-p)
	     parse-result
	     (values
	       bad-phrase
	       (cond
		 (localnet-valid-p
		  (tformat-text-string "~A~A~A"
		    (if localnet-hostname-valid-p
			""
			"LOCALNET hostname must be LOCALHOST")
		    (if (or localnet-hostname-valid-p localnet-port-valid-p)
			""
			" and ")
		    (if localnet-port-valid-p
			""
			"No port allowed in LOCALNET specification")))
		 (t (copy-text-string
		      "LOCALNET is not a valid network transport")))))))
       (otherwise
	(values
	  bad-phrase
	  (tformat-text-string
	    "Network transport must be ~A"
	    (if localnet-valid-p
		"one of TCP-IP or LOCALNET"
		"TCP-IP")))))))
  
(def-slot-value-compiler gsi-host-configuration (parse-result)
  (cond
    ((eq 'none parse-result) nil)
    (t (valid-icp-connection-specification-from-parse
	 parse-result
	 #+gsi-in-g2 t #-gsi-in-g2 nil))))

;; Changed gsi-interface-status slot of the gsi-interface
;; capability to a system slot and made it non-editable.  GA reported (PR #
;; 4995) that user editing can cause a G2 crash on the Compaq.  (jh, 5/23/90)
;; Added a slot-putter in GSI module to forward chain from this slot.  - cpm,
;; 2/1/92





;;; Declaration:     gsi-interface-p-function (frame)
;;; Type:	     Lisp function.
;;; Purpose:         Allow previously-defined code to test
;;;                  gsi-interface capability.
;;; Arguments:	     A G2 frame.
;;; Return behavior: Returns non-nil if the frame has gsi-interface
;;;                  capability, nil otherwise.
;;; Users:           G2 remote procedure call machinery (ACTIONS, G2-RPC1,
;;;                  G2-RPC2, STACK-INST, STACK-ACTS).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;; Added gsi-interface-capability-p-function to take care of a forward reference
;; in ROLES.  jh, 7/18/91.

(defun gsi-interface-p-function (thing)
  (gsi-interface-p thing))





;;; Declaration:     timeout-interval-or-default
;;; Type:	     G2 slot value compiler.
;;; Purpose:	     Obtain from a G2 user the timeout interval of a GSI interface.
;;; Accepts:         An integer or the phrase "use default".
;;; Return behavior: Returns either a fixnum less than 65536 or the symbol default.
;;;                  The rationale for the limit 65536 is obscure.
;;; Users:	     GSI internals (GSI module).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(add-grammar-rules '((timeout-interval-or-default-or-none timeout-interval-or-default)
		     (timeout-interval-or-default-or-none 'unlimited unlimited)
		     
		     (timeout-interval-or-default interval)
		     (timeout-interval-or-default ('use 'default) default)))

(defun slot-value-compiler-for-timeout-interval-or-default (parse-result)
  (cond ((eq parse-result 'default) 'default)
 	((=f (car parse-result) 0)
	 (values bad-phrase
		 (
		  copy-constant-wide-string #w"The interval must not be zero."
		  )))
	((>f (integer-length (car parse-result))
	     16)
	 (values bad-phrase
		 (copy-text-string
		   #.(format nil "The interval must be less ~
				  than ~a seconds!"
			     (1- (ash 1 16))))))
	(t (car parse-result))))

(def-slot-value-compiler timeout-interval-or-default (parse-result)
  (slot-value-compiler-for-timeout-interval-or-default parse-result))

(def-slot-value-compiler timeout-interval-or-default-or-none (parse-result)
  (if (eq parse-result 'unlimited)
      nil
      (slot-value-compiler-for-timeout-interval-or-default parse-result)))

;; Changed the slot-value compiler for timeout-interval-or-default to insert the
;; symbol 'default instead of default-gsi-interface-countdown-timer-limit so as
;; not to disorient the user.  (Previously, the user would type in "use default"
;; and see something like "10 seconds" appear in the slot.  Confusion was
;; natural.) Every place that uses the timeout-interval-or-default type checks
;; it for numberhood and uses default-gsi-interface-countdown-timer-limit if the
;; test fails.  Thus putting a symbol in a numeric slot is ok here.  (jh,
;; 5/23/90)

(define-category-evaluator-interface (timeout-interval-or-default
				       :access read-write)
    (or (member use-default) integer)
  ((set-form (evaluation-value))
   (cond ((integerp evaluation-value)
	  (phrase-cons evaluation-value 'seconds))
	 ((eq evaluation-value 'use-default)
	  'default)))
  ((get-form (slot-value))
   (if (or (null slot-value)
	   (eq slot-value 'default))
       'use-default
       slot-value)))

(define-category-evaluator-interface (timeout-interval-or-default-or-none
				       :access read-write)
    (or (member use-default unlimited) integer)
  ((set-form (evaluation-value))
   (cond ((integerp evaluation-value)
	  (phrase-cons evaluation-value 'seconds))
	 ((eq evaluation-value 'use-default)
	  'default)	 
	 ((eq evaluation-value 'unlimited)
	  'unlimited)))
  ((get-form (slot-value))
   (case slot-value
     ((nil) 'unlimited)
     ((default) 'use-default)
     (t slot-value))))




;;; Declaration:     timeout-interval-or-default
;;; Type:	     G2 slot value writer.
;;; Purpose:	     Present to a G2 user the timeout interval used in a GSI 
;;;                  interface.
;;; Arguments:       The value of the interface-timeout-period slot in the GSI
;;;                  interface.
;;; Return behavior: No useful value.
;;; Users:	     TABLES.
;;; Prerequisites:   To be called within a twith-output-to-text-string scope.
;;; Side effects:    Writes the interval as an integer or as the phrase "use 
;;;                  default".
;;; Non-local exits: None.
;;; Memory impact:   None.

(def-slot-value-writer timeout-interval-or-default (value)
  (cond ((or (null value) 
	     (eq value 'default))
	 (twrite "use default"))
	((numberp value) (print-constant value 'seconds))))

(def-slot-value-writer timeout-interval-or-default-or-none (value)
  (cond ((null value) 
	 (twrite "unlimited"))
	((eq value 'default)
	 (twrite "use default"))
	((numberp value) (print-constant value 'seconds))))





(add-grammar-rules
  '((host-name unreserved-symbol)
    (network-task-name unreserved-symbol)
    (tcp-ip-port-number integer)
    (file-pathname whole-string)
    (host-name-string whole-string)
    (process-initialization-string whole-string)
    (gsi-host-configuration 'none) ;jh, 10/24/91.
    #+ignore ; was gsi-in-g2.  see enable-loadable-bridges
    (gsi-host-configuration
     ('local 'emulator)
     (localnet localhost))
    (gsi-host-configuration
     ('tcp-ip 'host host-name-string 'port-number tcp-ip-port-number)
     (tcp-ip 3 5 nil))
    (gsi-host-configuration
     ('tcp-ip 'host host-name-string 'port-number tcp-ip-port-number 'secure yes-or-no)
     (tcp-ip 3 5 7))))




;;; Declaration:     gsi-data-service
;;; Type:	     G2 capability.
;;; Purpose:	     Configure a G2 variable to act as a GSI variable.
;;; Slots:           System slots added by this capability:
;;;                  > data-server-map is the symbol gsi-data-server.
;;;                  > gsi-interface-name is a symbol naming the GSI interface used
;;;                    by this GSI variable, or nil if no interface has been
;;;                    specified.  This slot is saved with the KB.
;;;                  > gsi-interface is not used.  This slot is invisible to the G2
;;;                    user.
;;;                  > gsi-sensor-group-assignment is not used.  This slot is
;;;                    invisible to the G2 user.
;;;                  > gsi-collection-interval gives the interval with which the
;;;                    remote GSI process sends new values to the GSI variable.
;;;                    This slot is invisible to the G2 user and is not saved with
;;;                    the KB.
;;;                  > gsi-sensor-structure is a gsi-sensor structure associated
;;;                    with a corresponding GSI variable or nil.  This slot is
;;;                    invisible to the G2 user and is not saved with the KB.
;;;                  User slots added by this capability:
;;;                  > gsi-variable-status is initially 0, signifying no-error.
;;;                    See the ICP value type gsi-value-error-code for pre-defined
;;;                    values of this slot. 
;;; Return behavior: No useful value.
;;; Users:           GSI internals (module GSI), describe-frame class method in
;;;                  QUERTIES.
;;; Prerequisites:   The def-capability macro must be defined.
;;; Side effects:    Defines accessors for capability slots and a gsi-data-service-p
;;;                  predicate macro.
;;; Non-local exits: None.
;;; Memory impact:   Adds some system and user slots to an object.
;;; Notes:           > Consider renaming those slots which can be nil to use ?  or -p
;;;                    suffixes as appropriate.
;;;                  > Consider chaging the gsi-variable-status slot so it is not
;;;                    editable by the G2 user, or consider adding functionality to
;;;                    communicate with the corresponding GSI variable when this
;;;                    slot is edited.

;;; GSI-data-service capability enables a sensor to get/set values using a
;;; particular GSI data server interface.  The human interface will restrict
;;; users from putting in gsi-interface names for interfaces which do not exist.
;;; A method should be worked out to watch out for multiple interface objects
;;; with the same name.  Currently we will consider only the case where there is
;;; one interface with a given name.  If there is more than one object with the
;;; same name then use the first one with a GSI interface configuration
;;; capability.  Be sure to warn users that the potential for conflict exists.

;;; THE FOLLOWING OPTIMIZATION WILL BE IMPLEMENTED AT A LATER TIME.  At run
;;; time, GSI receives a get or set request for variables with GSI-data-server
;;; in the data server map slot.  When GSI receives such a request it will check
;;; to see if the sensor has been assigned to a sensor group of a defined
;;; interface.  If it has been assigned then the request is queued on the
;;; interface structure for transmition.  If not then GSI computes the sensor
;;; group assignment from the name of the GSI interface, the interface sensor
;;; grouping configuration, and the values of the specified sensor attributes.
;;; A sensor group assignment, always verified before each use, greatly speeds
;;; up the process of finding the right group of sensors in which to
;;; incrementally add the new sensor request.  Some computational effort will be
;;; needed to set up a sensor group assignment.  However the assumption made
;;; here is that this computation is needed only the first time the sensor is
;;; processed for GSI I/O and when either the sensor or the interface object is
;;; reconfigured.

;;; Assigning a sensor grouping.
;;; Sensors are grouped according to three main criterion:
;;; 1.  The GSI interface specified in the gsi-interface-name of the sensor
;;; 2.  The type of request associated with the sensor (get/set/stop-collecting)
;;; 3.  The values of specific sensor parameters as specified by the GSI
;;;     interface configuration.

;;; The parameters used in determining a sensor's grouping are specified in the
;;; sensor-grouping-specification slot of the gsi interface named in the
;;; gsi-interface-name slot of the sensor.  To check to see if a sensor can be
;;; placed in an existing group, GSI compares the values of the sensor
;;; parameters with the corresponding values of the parameters of the sensor
;;; group.  If the values are eql then the sensor can be placed in the group.
;;; GSI interfaces will keep a list of active sensor groups.  Active sensor
;;; groups contain sensors of a common request type and eql sensor grouping
;;; parameter values.  The Active sensor groups of a GSI interface are processed
;;; for transmission to the external process in order that they were created.
;;; GSI attempts to process all active sensor groups within the clock cycle.  An
;;; active sensor group is always processed atomically.  Active sensor groups
;;; not processes within the clock cycle in which they were created will be
;;; processed first in subsequent clock cycles.  The processing time limit for
;;; all active sensor groups of all GSI interfaces is specified by the G2
;;; scheduler.

;;; Notes for defining attributes using capability definitions:

;;; The form for attribute slot definitions is as follows
;;; (slot-name initial-value type )

;;; The initial value can be a constant number symbol or text with corresponding
;;; types are number symbol or text.  The initial value can also be a variable
;;; with init form (:funcall instantiate-variable variable-class) with the type
;;; being a constant symbol or text depending on the basic type of variable.
;;; For symbols a list of permitted symbols can follow the type.

(def-class (gsi-data-service variable define-predicate
			     (only-compatible-with variable)
			     (foundation-class variable)
			     not-solely-instantiable
			     not-user-instantiable do-not-put-in-menus)
  (data-server-map 
    gsi-data-server (vector-slot) (system) (type data-server-map))
  (gsi-interface-name nil
    (lookup-slot)
    (system) user-overridable
    (type gsi-interface-name)
    (save))
  (gsi-interface nil (lookup-slot) (system) (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-sensor-group-assignment 
    nil (lookup-slot) (system) 
    (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-collection-interval 
    0 (lookup-slot) (system) 
    (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-internal-collection-interval
    nil (lookup-slot) (system) 
    (do-not-put-in-attribute-tables) (do-not-save))
  (gsi-variable-status 0
    (lookup-slot) (system) not-user-editable (type gsi-variable-status-code)))

(def-slot-value-writer gsi-variable-status-code (integer)
    (twrite-fixnum integer))

(define-category-evaluator-interface (gsi-variable-status-code
				       :access read)
    integer
  ((get-form (slot-value)) slot-value))

(define-category-evaluator-interface (gsi-interface-name
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value?))
   (or evaluation-value? 'none))
  ((get-form (slot-value))
   slot-value))

;; jh per ghw & mhd. 4/27/93.  The slot gsi-interface-name is used by both the
;; gsi-data-service and gsi-message-service class definitions.  When a user
;; constructs an object that inherits from a subclass of each of these classes,
;; the gsi-interface-name slot they get depends on the most specific class in
;; the inheritance path.  This sort of shadowing is standard operation for
;; user-specified slots, but it is the first time that we've relied such
;; shadowing for system (a.k.a.  builtin) slots.  Note that only one slot has a
;; no-accessor option.  This is to prevent duplicate setf methods and the like
;; from being generated.  We should also take care to keep these two slot
;; definitions in synch, perhaps to the point of abstracting them into a
;; separate mixin class someday.

(def-slot-value-reclaimer gsi-collection-interval
    (gsi-collection-interval gsi-data-service)
  (reclaim-evaluation-quantity gsi-collection-interval)
  (setf (gsi-collection-interval gsi-data-service) 0))

;;; Declaration:     gsi-data-service-p-function (thing)
;;; Type:	     Lisp function.
;;; Purpose:         Allow previously-defined code to test gsi-data-service
;;;                  capability.
;;; Arguments:	     A G2 variable.
;;; Return behavior: Returns non-nil if the frame has gsi-data-service capability,
;;;                  nil otherwise.
;;; Users:           describe-frame class method in QUERTIES.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;; Need gsi-data-service-p-function to cope with a forward macro reference from
;; the queries module.  (jh, 3/15/90)

(defun gsi-data-service-p-function (thing)
  (gsi-data-service-p thing))




;;; The slot putter for `remote-process-initialization-string' mainly exists in
;;; order to massage the old (pre-5.0) format as (translation . text)
;;; representations into the new format, which is just translation, i.e., a text
;;; string.  In 5.0 as of 5/31/96, we made this into a non-text type slot.

(def-slot-putter remote-process-initialization-string
    (gsi-data-service value initializing?)
  (cond
    ((and initializing? (consp value)) ; NB: must be loading a pre-5.0 KB
     #+development
     (assert (and (or (null (car value))
		      (text-string-p (car value)))
		  (listp (cdr value))))
     (prog1
	 (setf (remote-process-initialization-string gsi-data-service)
	       (or (car value) (copy-constant-wide-string #w"")))
       (setf (car value) nil)
       (reclaim-slot-value value)))
    (t
     #+development
     (assert (text-string-p value))
     (setf (remote-process-initialization-string gsi-data-service) value))))

;; Converted to non-text-type slot. (MHD 5/31/96)



(def-slot-value-writer process-initialization-string (value)
  (tformat "~s" value))			; normal writer for whole-string

(def-slot-value-compiler process-initialization-string (parse-result)
  parse-result)

;; The writer is new.  We previously stored the text, but that was
;; not well-motivated; now we simply store the value, and the writer
;; must generate it back. (MHD 5/31/96)




(def-slot-value-writer gsi-host-configuration (value)
  ;; Value is
  ;;
  ;; none
  ;; | (LOCALNET)
  ;; | (TCP-IP host-name-string tcp-ip-port-number)
  (cond
    ((null value)
     (tformat "none"))
    ((eq (car value) 'localnet)
     (twrite-string "local emulator"))
    ((eq (car value) 'tcp-ip)
     (tformat "tcp-ip host ~S port-number ~A"
	      (second value)		; host name (text string)
	      (third value)))		; tcp-ip port number
    (t
     ;; Can this ever happen?!  Review with GSI folks! (MHD 5/31/96)
     (tformat "[Unknown/Obsolete value: ~a / ~a / ~a]"
	      (first value) (second value) (third value)))))

;; The writer is new.  We previously stored the text, but that was
;; not well-motivated; now we simply store the value, and the writer
;; must generate it back. (MHD 5/31/96)




;;; The slot putter for `gsi-variable-status' changes the status to the new
;;; given value and invokes forward chaining for the change.

(def-slot-putter gsi-variable-status (gsi-data-service new-status)
  (let ((old-status (gsi-variable-status gsi-data-service))
	(*current-computation-frame* gsi-data-service))
    (setf (gsi-variable-status gsi-data-service) new-status)
    (invoke-rules-for-attribute-change-chaining
      gsi-data-service 'gsi-variable-status old-status nil)
    (values new-status nil)))




;;; Declaration:     gsi-message-service
;;; Type:	     G2 capability.
;;; Purpose:         Configure a G2 object to transmit messages to a remote GSI
;;;                  process.
;;; Slots:           > gsi-interface-name is a system slot, either a symbol naming a
;;;                    GSI interface or nil.  It is saved with the KB.
;;;                  > data-server-for-messages is a user slot, initially the symbol
;;;                    gsi-data-server.  This slot can be edited to redirect
;;;                    messages.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (module GSI).
;;; Prerequisites:   The def-capability macro must be defined.
;;; Side effects:    Defines accessors for capability slots and a
;;;                  gsi-message-service-p predicate macro.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; GSI sends text strings through the inform action when the user has specified
;;; an active interface in the gsi-interface-name slot and gsi-data-server in
;;; the data-server for messages slot.  The gsi-message-service capability puts
;;; these slots in the object and initializes the data-server-for-messages slot
;;; to gsi-data-server.

;;; Text strings are sent to the remote process as they are received by GSI.
;;; They are not queued for later transmission as are sensor I/O requests.

(def-class (gsi-message-service item define-predicate
				(foundation-class item)
				not-solely-instantiable
				not-user-instantiable do-not-put-in-menus)
  ;; jh, 4/27/94.  See above note this date about the gsi-interface-name slot
  ;; also being used by the gsi-data-service class.
  (gsi-interface-name nil
    (lookup-slot)
    (no-accessor)
    (system) user-overridable
    (type gsi-interface-name)
    (save))
  (data-server-for-messages gsi-data-server (lookup-slot) (system)
			    user-overridable (type symbol)))

;;; Declaration:     gsi-message-service-p-function (thing)
;;; Type:	     Lisp function.
;;; Purpose:	     Allow previously-defined code to test gsi-message-service
;;;                  capability.
;;; Arguments:	     A G2 object.
;;; Return behavior: Returns non-nil if the frame has gsi-message-service capability,
;;;                  nil otherwise.
;;; Users:           describe-frame class method in QUERTIES.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;; Need gsi-message-service-p-function to cope with a forward macro reference 
;; from the queries module. (jh, 3/15/90)

(defun gsi-message-service-p-function (thing)
  (gsi-message-service-p thing))




;;; The slot putter for `data-server-for-messages' sets the slot value and
;;; invokes forward chaining.

(def-slot-putter data-server-for-messages (gsi-message-service new-server)
  (let ((*current-computation-frame* gsi-message-service)
	(old-server (data-server-for-messages gsi-message-service)))
    (setf (data-server-for-messages gsi-message-service) new-server)
    (invoke-rules-for-attribute-change-chaining
      gsi-message-service 'data-server-for-messages old-server nil)
    (values new-server nil)))




;;; Gsi-interface-name can be either an ureserved symbol (potentially the name
;;; of a G2 object or none.  The GSI-interface-name will be used to locate a
;;; particular GSI interface to be used for a sensor.

(add-grammar-rules `((gsi-interface-name 'none)
		     (gsi-interface-name unreserved-symbol)))



;;; Declaration:     gsi-interface-name
;;; Type:	     G2 slot value writer.
;;; Purpose:	     Present to a G2 user the gsi-interface-name used by a GSI
;;;                  variable.
;;; Arguments:       The value of the gsi-interface-name in the GSI variable.
;;; Return behavior: No useful value.
;;; Users:	     TABLES.
;;; Prerequisites:   To be called within a twith-output-to-text-string scope.
;;; Side effects:    Writes the name of the GSI interface name, or "none" if nil is
;;;                  present.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; The compiler checks to see if a gsi interface exists before allowing the
;;; user to input an interface-name.  We should consider whether the kb
;;; loading/saving sequence would enable optimization of the search for the
;;; actual frame of the object representing the interface and optimization of
;;; the sensor grouping.  For the first implementation we will run time compute
;;; both of these.  Consider adding them at a later time to improve data
;;; throughput!

(def-slot-value-writer gsi-interface-name (interface-name)
  (if (null interface-name)
      (twrite "none")
      (twrite interface-name)))




;;; Declaration:     gsi-data-server
;;; Type:	     G2 data-server pretty-printer.
;;; Purpose:	     Name the GSI dataserver to a G2 user.
;;; Arguments:	     N/A.
;;; Return behavior: N/A.
;;; Users:	     TABLES, QUERIES.
;;; Prerequisites:   The macro def-data-server-pretty-printer must be defined.
;;; Side effects:    Causes G2 to write "GSI data server" when it names the GSI data
;;;                  server.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

(def-data-server-pretty-printer 'gsi-data-server "GSI data server")

;; Everything above this line except comments at the top and the translator
;; directive were brought in from GSI-STUBS.LISP. paf! 5jan94



;;; Declaration:     handle-update-to-sensor-attribute (gsi-variable)
;;; Type:	     Lisp function.
;;; Purpose:         Update the GSI dataserver when an identifying attribute of a
;;;                  GSI variable changes.
;;; Arguments:	     A GSI variable.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    handle-gsi-shut-down-connection
;;; Prerequisites:   This function must be installed as a true-value updater for
;;;                  each identifying attribute listed in the GSI interface named in
;;;                  the gsi-interface-name attribute of the variable.
;;; Side effects:    Redefines the GSI variable to the GSI process by calling
;;;                  reconfigure-gsi-sensor-attribute.  Collects the new value by
;;;                  calling gsi-collect-one-shot-data.
;;; Non-local exits: None.
;;; Memory impact:   None at the GSI level.  Can cause ICP communication.  Can
;;;                  conclude into gsi-variable.
;;; Possible bugs:   See the slot-putter for identifying-attributes.

;; Handle-update-to-sensor-attribute is called whenever the value of a G2
;; sensor's ID attributes change.  It causes the extension process to store the
;; remote sensor under the new ID attributes.  The drawback is that the sensor
;; is redefined every time a sensor ID attribute is changed.  This could be an
;; efficiency problem if the user wants to inhibit redefinitions until an entire
;; complement of new sensor ID attributes is installed.

;; Note that this function is called by the true-value-update facilities.  If
;; the last argument is a symbol naming an attribute, then the
;; parameter-or-sensor argument is the actual gsi sensor which needs to be
;; reconfigured, and the slot constant in the named attribute was editted.  If
;; the last argument is NIL, then the parameter-or-sensor argument is a
;; parameter in the sensor, and the parent frame of this parameter is the sensor
;; to be reconfigured.

;; If the external system has a scheduler, we want to send a get-values message
;; whenever a GSI sensor attribute changes, to be sure that the extension is
;; apprised of the fact.  When G2 is the scheduler, the update will occur as a
;; side effect of reconfigure gsi-sensor-attribute (jh, 7/11/90)

(defun handle-update-to-located-sensor-attribute
       (sensor &optional real-attribute-name? gsi-interface-frame?)
  (declare (ignore real-attribute-name?))
  (let*-while-true  ((gsi-interface-name?
		       (get-slot-value-if-any sensor 'gsi-interface-name)) 
		     (gsi-interface?
		       (get-instance-with-name-if-any
			 'object 
			 gsi-interface-name?)))
    (when (and (or (null gsi-interface-frame?)
		   (eq gsi-interface-frame? gsi-interface?))
	       (active-p gsi-interface?))
      (let ((icp-socket?
	      (get-slot-value-if-any 
		gsi-interface?
		'gsi-interface-icp-socket)))
	(when (and icp-socket?		   
		   (icp-connection-open-p icp-socket?)
		   (=f (gsi-connection-state icp-socket?) gsi-connection-established))
	  (reconfigure-gsi-sensor-attribute sensor)
	  (when (get-slot-value-if-any
		  gsi-interface?
		  'external-system-has-a-scheduler)
	    (gsi-collect-one-shot-data sensor)))))))



;;; The `note-name-change gsi-data-service' method calls
;;; handle-update-to-located-sensor-attribute on gsi-data-service after invoking
;;; its superior method.

(def-class-method note-name-change (gsi-data-service old-names initializing-p)
  (funcall-superior-method gsi-data-service old-names initializing-p)
  (handle-update-to-located-sensor-attribute gsi-data-service 'names))



(defun handle-update-to-sensor-attribute
    (gsi-interface-frame ignored-extra-argument parameter-or-sensor
     attribute-name? old-value class-if-specific?)
  (declare (ignore ignored-extra-argument old-value class-if-specific?))
  (let ((sensor? 
	  (if attribute-name?
	      parameter-or-sensor
	      (parent-frame parameter-or-sensor))))
    (when (and sensor? (gsi-data-service-p sensor?))
      (let ((real-attribute-name? 
	      (or attribute-name?
		  (parent-attribute-name parameter-or-sensor))))
	(when real-attribute-name?
	  (if collecting-updates-to-sensor-attributes-p
	      (let ((a (assq sensor? collected-updates-to-sensor-attributes)))
		(unless a
		  (setq a (gensym-list sensor? gsi-interface-frame nil))
		  (gensym-push a collected-updates-to-sensor-attributes))
		(gensym-pushnew real-attribute-name? (third a)))
	      (handle-update-to-located-sensor-attribute
		sensor?
		real-attribute-name? ; ignored
		gsi-interface-frame)))))))

;; jh, 10/16/92.  Extracted handle-update-to-located-sensor-attribute from
;; handle-update-to-sensor-attribute.  This will will permit a GSI variable to
;; have its name as an identifying attribute.  Although special purpose, this
;; ability will make it easier for G2 users to grasp that arcane notion,
;; identifying attributes of a GSI variable.



;;; Declaration:     handle-update-to-sensor-data-type (gsi-variable)
;;; Type:	     Lisp function.
;;; Purpose:         Update the GSI dataserver when the data-type attribute of a GSI
;;;                  variable changes.
;;; Arguments:	     A GSI variable.
;;; Return behavior: No useful value.
;;; Users:           The slot putter for data-type-of-variable-or-parameter
;;;                  (VARIABLES).
;;; Prerequisites:   None.
;;; Side effects:    Redefines the GSI variable to the GSI process by calling
;;;                  reconfigure-gsi-sensor-attribute.  Collects the new value by
;;;                  calling gsi-collect-one-shot-data.
;;; Non-local exits: None.
;;; Memory impact:   None at the GSI level.  Can cause ICP communication.  Can
;;;                  conclude into gsi-variable.

(defun handle-update-to-sensor-data-type (sensor)
  (when (gsi-data-service-p sensor)
    (let*-while-true
        ((gsi-interface-name?
	   (get-slot-value-if-any sensor 'gsi-interface-name))
	 (gsi-interface?
	   (get-instance-with-name-if-any 'object gsi-interface-name?))
	 (icp-socket?
	   (get-slot-value-if-any gsi-interface? 'gsi-interface-icp-socket)))
      (when (and (active-p gsi-interface?)
		 (icp-connection-open-p icp-socket?)
		 (=f (gsi-connection-state icp-socket?) gsi-connection-established))
	(reconfigure-gsi-sensor-attribute sensor)
	(when (get-slot-value-if-any
		gsi-interface?
		'external-system-has-a-scheduler)
	  (gsi-collect-one-shot-data sensor))))))





;;; To prevent ICP errors, put-current-value must be executed from 
;;; a scheduled task. Therefore all values coming in from the remote
;;; gsi server must be queued for later processing by a high priorty task





;;; Declaration:     list-of-gsi-values-to-process-head
;;;                  list-of-gsi-values-to-process-tail
;;; Type:	     G2 system variables.
;;; Purpose:	     Maintain a queue for incoming values of GSI variables.
;;; Values:          The queue is composed of gsi-conses.
;;;                  list-of-gsi-values-to-process-tail points to the last cons in
;;;                  the queue, list-of-gsi-values-to-process-head points to the
;;;                  entire queue.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;; 		       process-gsi-sensor-values
;;;                    save-gsi-variable-for-processing
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Users of this queue are responsible for ensuring that its size
;;;                  remains bounded.

(def-system-variable list-of-gsi-values-to-process-head    G2-GSI nil)
(def-system-variable list-of-gsi-values-to-process-tail    G2-GSI nil)


;;; Declaration:     task-to-process-gsi-values
;;; Type:	     G2 system variable.
;;; Purpose:         Provide a place for the task which processes incoming values
;;;                  for GSI variables.
;;; Value:           A scheduled task or nil.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    save-gsi-variable-value-for-processing
;;;                    gsi-shut-down-data-server?
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

(def-system-variable task-to-process-gsi-values            G2-GSI nil)



;;; Declaration:     task-to-process-gsi-interfaces
;;; Type:	     G2 system variable.
;;; Purpose:         Provide a place for the task which gets incoming values for GSI
;;;                  variables from GSI interfaces.
;;; Value:           A scheduled task or nil.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    gsi-shut-down-data-server?
;;;                    enqueue-gsi-request-for-sensor
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

(def-system-variable task-to-process-gsi-interfaces        G2-GSI nil) 



;;; Declaration:     task-scheduled-to-process-gsi-values?
;;; Type:	     G2 system variable.
;;; Purpose:	     Determine whether a task to process GSI variable values has been
;;;                  scheduled.
;;; Value:           Non-nil if a task has been scheduled to process GSI variable
;;;                  values, nil otherwise.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    save-gsi-variable-value-for-processing
;;;                    process-gsi-sensor-values
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.
;;; Notes:           This variable overlaps functionality with
;;;                  task-to-process-gsi-values.  Consider using
;;;                  schedule-task-in-place-p and dispensing with this variable.

(def-system-variable task-scheduled-to-process-gsi-values? G2-GSI nil)

;; Added task-to-process-gsi-interfaces for latency fix.  jh, 5/22/91.



;;; Declaration:     save-gsi-variable-value-for-processing
;;;                    (gsi-variable evaluation-value value-vector?)
;;; Type:	     Lisp macro.
;;; Purpose:	     Queue an incoming value for a GSI variable.
;;; Arguments:	     > gsi-variable is the GSI variable whose incoming value is to
;;;                    be queued.
;;;                  > evaluation-value is the incoming value, a
;;;                    evaluation-value structure.
;;;                  > value-vector?  is either nil or of the ICP value type
;;;                    gsi-value-vector (see GSI-COMMON).
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (gsi-receive-value-for-gsi-sensor).
;;; Prerequisites:   None.
;;; Side effects:    Modifies list-of-gsi-values-to-process-head and
;;;                  list-of-gsi-values-to-process-tail to contain a three-element
;;;                  gsi-list of gsi-variable, evaluation-value, and
;;;                  value-vector?.  Changes task-scheduled-to-process-gsi-values?
;;;                  and ensures that task-to-process-gsi-values contains a
;;;                  scheduled task and not nil.
;;; Non-local exits: None.
;;; Memory impact:   Adds a three-element gsi-list to
;;;                  list-of-gsi-values-to-process-head using gsi-cons.  The
;;;                  gsi-list and gsi-cons are reclaimed by
;;;                  process-gsi-sensor-values.  

(defmacro save-gsi-variable-value-for-processing
	  (gsi-variable value? collection-time? value-vector?)
  ;; Added queue-entry for latency fix.  jh, 5/22/91.
  (avoiding-variable-capture (gsi-variable &aux queue-entry)
    `(let ((,queue-entry 
	      (gsi-list ,gsi-variable ,value? ,collection-time? ,value-vector?)))
       (enqueue ,queue-entry
		list-of-gsi-values-to-process-head
		list-of-gsi-values-to-process-tail
		gsi-cons)
       (unless (schedule-task-in-place-p task-to-process-gsi-values)
	 (with-current-scheduling
	     (task-to-process-gsi-values
	       (priority-of-data-service data-server-parameters))
	   (process-gsi-sensor-values t))))))

;; jh, 11/9/92.  Changed the priority at which
;; save-gsi-variable-value-for-processing schedules the task
;; process-gsi-sensor-values to be the priority-of-data-service in the
;; data-server-parameters system table.  Previously, this was 1 unconditionally,
;; which never seemed right.

;; jh, 5/22/91.  Modified save-gsi-variable-value-for-processing to mark a sensor
;; when values are queued up for it.  This is part of an improvement in GSI
;; latency.  We don't want to re-schedule a get-data request if the old one is
;; still queued up, so we set the sensor's queue-entry-to-process-sensor? slot so
;; we can tell the difference in gsi-receive-value-for-gsi-sensor.



(defun reclaim-gsi-list-with-evaluation-values (list)
  (loop for value in list
	do (reclaim-if-evaluation-value value)
	finally (reclaim-gsi-list list)))



;;; Declaration:     get-or-make-gsi-sensor
;;;                    (sensor sensor-frame-serial-number collection-interval)
;;; Type:	     Lisp function.
;;; Purpose:         Supply a GSI variable with a local object for a corresponding
;;;                  GSI variable.
;;; Arguments:	     > sensor is a GSI variable.  Recall this is a G2 frame.
;;;                  > sensor-frame-serial-number is the frame serial number of
;;;                    sensor.  This is needed to check if sensor has been reclaimed
;;;                    since it was last examined.
;;; Return behavior: Returns a gsi-sensor structure, the local object for a
;;;                  corresponding ICP object which represents the GSI variable in
;;;                  the remote GSi extension.
;;; Users:	     GSI internals:
;;;                    add-sensor-to-group-if-it-fits
;;;                    put-sensor-in-new-sensor-group
;;; Prerequisites:   None.
;;; Side effects:    If there is an existing gsi-sensor structure for sensor, its
;;;                  g2-sensor-frame-serial-number and its
;;;                  gsi-sensor-collection-interval slots are modified.
;;; Non-local exits: None.
;;; Memory impact:   If there is no existing gsi-sensor-structure for sensor, a new
;;;                  one is created.  The gsi-sensor structure in sensor is
;;;                  reclaimed when sensor is deleted.

(defun get-or-make-gsi-sensor (sensor
                               collection-interval)
  (set-slot-value sensor 'gsi-internal-collection-interval collection-interval)
  sensor)
	      
            


;;; Declaration:     max-gsi-sensors-in-a-group
;;; Type:	     G2 system variable.
;;; Purpose:	     Bound the number of GSI variables which may request values
;;;                  in one group.  If adding a GSI variable would make a group
;;;                  larger than this number, a new group is started.
;;; Value:           This is currently 20 and is never rebound.
;;; Return behavior: N/A.
;;; Users:	     GSI internals (add-sensor-to-group-if-it-fits).
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.
;;; Notes:           Since this is a system variable, consider tuning this to
;;;                  improve performance.

(def-system-variable max-gsi-sensors-in-a-group G2-GSI 20)



;;; Declaration:     sensor-group
;;; Type:	     G2 def-structure.
;;; Purpose:         Maintain information about some GSI variables which are getting
;;;                  values as a group.
;;; Slots:	     > sensor-group-parameters is a gsi-list of identifying
;;;                    attributes which differentiate corresponding GSI variables in
;;;                    the remote GSI process.  An identifying attribute may be a
;;;                    evaluation-value structure, a string, a symbol, a float, or
;;;                    an integer.
;;;                  > sensor-group-setting-values?  is non-nil if this group of
;;;                    requests will change values in the remote GSI process, nil
;;;                    otherwise.
;;;                  > sensor-group-collection-interval is a fixum representing the
;;;                    interval in seconds until the next data collection for this
;;;                    GSI variable, or nil, indicating that no collection will
;;;                    happen.  If this slot is 0, it indicates that data is to be
;;;                    collected once only, as soon as possible.
;;;                  > sensor-group-sensors-to-send-head is the head of a queue of
;;;                    GSI variables whose value is to be requested from the remote
;;;                    GSI process.  This queue is a gsi-list.
;;;                  > sensor-group-sensors-to-send-tail is the tail of a queue of
;;;                    GSI variables whose value is to be requested from the remote
;;;                    GSI process.  This queue is a gsi-list.
;;;                  > sensor-group-count is a fixnum giving the number of GSI
;;;                    variables in this group.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    put-sensor-in-new-sensor-group
;;;                    handle-gsi-shut-down-connection
;;;                    add-sensor-to-group-if-it-fits
;;;                    send-message-series-for-gsi-request
;;;                    gsi-request-type
;;;                    clear-pending-gsi-sensor-request
;;; Prerequisites:   The macro def-structure must be defined.
;;; Side effects:    Creates a constructor macro make-sensor-group, which takes
;;;                  three slots as argument: sensor-group-parameters,
;;;                  sensor-group-setting-values?, and
;;;                  sensor-group-collection-interval.  Creates a predicate macro
;;;                  sensor-group-p.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.

(def-structure (sensor-group
                (:constructor make-sensor-group (sensor-group-parameters
                                                 sensor-group-setting-values?
                                                 sensor-group-collection-interval)))
  sensor-group-parameters
  sensor-group-setting-values?
  sensor-group-collection-interval
  sensor-group-sensors-to-send-head
  sensor-group-sensors-to-send-tail
  (sensor-group-count 0))



;;; Declaration:     sensor-groups-header
;;; Type:	     G2 def-structure.
;;; Purpose:         Maintain a queue grouping GSI variables which are requesting
;;;                  values from the remote GSI process.
;;; Slots:           > sensor-groups-to-send-head is the head of a queue of
;;;                    sensor-group structures.  This queue is a gsi-list.
;;;                  > sensor-groups-to-send-tail is the tail of a queue of
;;;                    sensor-group structures.  This queue is a gsi-list.
;;; Users:		 GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    handle-gsi-shut-down-connection
;;;                    clear-pending-gsi-sensor-request
;;;                    enqueue-gsi-request-for-sensor
;;;                    put-sensor-in-new-sensor-group
;;;                    process-requests-for-gsi-interfaces
;;; Prerequisites:   The macro def-structure must be defined.
;;; Side effects:    Creates a constructor macro make-sensor-groups-header, which
;;;                  takes no arguments.  Creates a predicate macro
;;;                  sensor-groups-header-p.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.

(def-structure (sensor-groups-header 
                (:constructor make-sensor-groups-header ))
  sensor-groups-to-send-head
  sensor-groups-to-send-tail)



;;; Declaration:     list-of-all-gsi-interfaces-head
;;;                  list-of-all-gsi-interfaces-tail
;;; Type:	     G2 system variables.
;;; Purpose:	     Maintain a queue of all GSI interfaces.
;;; Values:          The queue is composed of gsi-conses.
;;;                  list-all-gsi-interfaces-tail points to the last cons in the
;;;                  queue, list-of-all-gsi-interfaces-head points to the entire
;;;                  queue.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    handle-gsi-shut-down-connection
;;;                    gsi-process-gsi-interfaces
;;; 	               gsi-pause-data-server?
;;;                    gsi-resume-data-server?
;;;                    gsi-shut-down-data-server?
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Allocated in
;;;                  activate-gsi-interface-with-connection-spec and
;;;                  reclaimed in gsi-shut-down-data-server?.

(def-system-variable list-of-all-gsi-interfaces G2-GSI nil)



;;; Declaration:     gsi-interfaces-to-process-head
;;;                  gsi-interfaces-to-process-tail
;;; Type:	     G2 system variable.
;;; Purpose:	     Maintain a queue of GSI interfaces which need processing.
;;; Values:          The queue is composed of gsi-conses.
;;;                  gsi-interfaces-to-process-tail points to the last cons in the
;;;                  queue, gsi-interfaces-to-process-head points to the entire
;;;                  queue.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    handle-gsi-shut-down-connection
;;;                    gsi-shut-down-data-server?
;;;                    enqueue-gsi-request-for-sensor
;;;                    process-requests-for-gsi-interfaces
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Allocated by enqueue-gsi-request-for-sensor, reclaimed by 

(def-system-variable gsi-interfaces-to-process-head G2-GSI nil)
(def-system-variable gsi-interfaces-to-process-tail G2-GSI nil)



;;; Declaration:     get-gsi-interface-for-gsi-sensor-if-any (gsi-variable)
;;; Type:	     Lisp function.
;;; Purpose:         Obtain the GSI interface through which a GSI variable
;;;                  communicates with the remote GSI process.
;;; Arguments:	     A GSI variable.
;;; Return behavior: Return a GSI interface frame, or nil if none can be found.
;;; Users:           GSI internals (make-corresponding-icp-gsi-sensor, defined by
;;;                  the def-icp-object-type for gsi-sensor in GSI-COMMON).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Possible bugs:   This function can call get-instance-with-name-if-any with nil,
;;;                  meaning that gsi-variable has no gsi-interface-name attribute.
;;;                  If any object is named lisp:nil, this could cause a problem.
;;;                  Currently, G2 interns the object name "NIL" in the Lisp KEYWORD
;;;                  package, so this is not a problem, but watch for changes.

(defun get-gsi-interface-for-gsi-sensor-if-any (gsi-sensor)
  (get-instance-with-name-if-any
    'gsi-interface
    (get-slot-value-if-any
      gsi-sensor
      'gsi-interface-name)))
						      


;;; Declaration:     reconfigure-gsi-sensor-attribute (sensor)
;;; Type:	     Lisp function.
;;; Purpose:         Change the value of an identifying attribute for a sensor
;;;                  and its corresponding GSI variable in the remote GSI process.
;;; Arguments:       sensor is the GSI variable whose identifying-attribute
;;;                  is to change.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    handle-update-to-sensor-attribute
;;;                    handle-update-to-sensor-data-type
;;; Prerequisites:   None.
;;; Side effects:    See define-or-configure-gsi-sensor.
;;; Non-local exits: None.
;;; Memory impact:   See define-or-configure-gsi-sensor.

(defun-simple reconfigure-gsi-sensor-attribute (sensor)
  (let* ((gsi-interface-name 
	   (get-slot-value-if-any sensor 'gsi-interface-name))
	 (gsi-interface 
	   (get-instance-with-name-if-any 'object gsi-interface-name))
	 (gsi-icp-socket
	   (when gsi-interface
	     (get-slot-value-if-any  
	       gsi-interface 
	       'gsi-interface-icp-socket))))
    (when (and gsi-interface
               (active-p sensor)
               (active-p gsi-interface)
	       gsi-icp-socket
	       (icp-connection-open-p gsi-icp-socket)
	       (=f (gsi-connection-state gsi-icp-socket)
		   gsi-connection-established))
      (let ((deregister-and-register-item-p t))
	(deregister-item-with-socket sensor gsi-icp-socket)
	(register-item-with-socket sensor gsi-icp-socket nil)))))



;;; Declaration:     define-or-configure-gsi-sensor
;;;                    (gsi-variable
;;; 	                gsi-sensor-structure
;;;                     corresponding-icp-object-index
;;;                     gsi-interface)
;;; Type:	     Lisp function.
;;; Purpose:         Create a new GSI corresponding variable or change the value of
;;;                  an identifying attribute of an old one.
;;; Arguments:	     > gsi-variable is the GSI variable whose corresponding GSI
;;;                    variable in the remote GSI process is to be modified.
;;;                  > gsi-sensor-structure is the local structure associated with the
;;;                    the corresponding variable of gsi-variable.
;;;                  > corresponding-icp-object-index is a fixnum giving the index
;;;                    of the corresponding variable of gsi-variable.
;;;                  > gsi-interface is the GSI interface through which gsi-variable
;;;                    communicates.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    make-corresponding-icp-gsi-sensor, defined by the
;;;                      def-icp-object-type for gsi-sensor in GSI-COMMON
;;; 		       reconfigure-gsi-sensor-attribute
;;; Prerequisites:   Must be called within a writing-icp-message-group scope.  
;;; Side effects:    Sends the ICP message define-gsi-sensor and, when the version
;;;                  of the remote GSI process is 2.0 or later, sends the ICP
;;;                  message modify-gsi-sensor-definition.  Replaces the
;;;                  gsi-sensor-attribute-list of gsi-variable with a new gsi-list.
;;;                  This new list has six elements, either temporary constants
;;;                  giving the value of an identifying attribute or gsi-variable,
;;;                  or nil if the identifying attribute has no value.
;;; Non-local exits: None.
;;; Memory impact:   Transmits ICP messages.  Reclaims the old
;;;                  gsi-sensor-attribute-list slot of gsi-variable.

;; The ICP message delete-icp-object-for-process (code 163) is reaching old gsi
;; extensions somehow.  This causes the old extension processes to crash, since
;; they don't know how many arguments to expect for an unknown message.  The fix
;; is to determine the version of the gsi extension when the gsi interface is
;; activated, then use that information to decide whether or not to send the
;; message.  We can differentiate old and new extensions by using the ICP message
;; return-gsi-extension-version.  New (2.0 and later) extension processes send
;; this message when initialized; old ones don't.  So when we receive a
;; return-gsi-extension-message, we use the version mechanism in UTILITIES3 to
;; index the version under the ICP socket being used.  We have to index the
;; version by individual socket because it is quite possible to have both old and
;; new extensions running at the same time.  (jh, 4/19/90)


;; The remote gsi extension needs more information when a gsi sensor is defined.
;; Specifically, the extension needs to know the variable's default update
;; interval and the data type of its value.  We can't simply adjust the argument
;; list of the icp message define-gsi-sensor because that would cause old
;; extension processes to crash.  We can't simply use with-bifurcated-version
;; because define-gsi-extension is often sent before the base gsi knows the
;; version.  So we create a new ICP message called modify-gsi-sensor-definition,
;; which transmits the interval and type in a separate message.  When we first
;; learn of the remote version (inside handle-icp-return-gsi-extension-version) we
;; send a modify-gsi-sensor-definition message for each sensor connected to the
;; given icp socket.  Afterwards, we know the version.  So whenever we send a
;; define-gsi-sensor message and the version is recent enough, we accompany it
;; with a modify-gsi-sensor-definition message. (jh, 5/1/90)

(defun get-gsi-identifying-attribute-values (gsi-item gsi-interface)
  (let ((gsi-item-attribute-names
	  (get-slot-value-if-any gsi-interface 'identifying-attributes)))
    (values (gsi-item-attribute-value (pop gsi-item-attribute-names)
				      gsi-item)
	    (gsi-item-attribute-value (pop gsi-item-attribute-names)
				      gsi-item)
	    (gsi-item-attribute-value (pop gsi-item-attribute-names)
				      gsi-item)
	    (gsi-item-attribute-value (pop gsi-item-attribute-names)
				      gsi-item)
	    (gsi-item-attribute-value (pop gsi-item-attribute-names)
				      gsi-item)
	    (gsi-item-attribute-value (pop gsi-item-attribute-names)
				      gsi-item))))

(defun define-or-configure-gsi-sensor (sensor 
				       corresponding-icp-object-index
				       gsi-interface)   
  (multiple-value-bind (p0 p1 p2 p3 p4 p5)
      (get-gsi-identifying-attribute-values sensor gsi-interface)

    ;; send the define-gsi-sensor message, and, if the version is
    ;; appropriate, send a modify-gsi-sensor-definition message which
    ;; contains the update interval and data type.
    (send-icp-define-gsi-sensor
      corresponding-icp-object-index
      p0 p1 p2 p3 p4 p5)
    (reclaim-gsi-list-with-evaluation-values
      (gsi-list p0 p1 p2 p3 p4 p5))
    ;; We can send the modify-gsi-sensor-definition message because we are
    ;; in the midst of the dynamic scope of a writing-icp-message-group
    ;; wrapper.
    (with-temporary-gensym-float-creation gsi-sensor
      (with-appropriate-version-for-output (modify-gsi-sensor-definition-icp-version)
	(collect-modifications-and-modify-gsi-sensor-definition
	  sensor
	  corresponding-icp-object-index)))))

(defun gsi-register-item (gsi-item corresponding-icp-object-index gsi-interface)
  (multiple-value-bind (p0? p1? p2? p3? p4? p5?)
      (get-gsi-identifying-attribute-values gsi-item gsi-interface)
    (send-icp-register-corresponding-icp-object 
      corresponding-icp-object-index
      (get-primary-name-for-frame-if-any gsi-item)
      (class gsi-item)
      p0? p1? p2? p3? p4? p5?)
    (reclaim-if-evaluation-value p0?)
    (reclaim-if-evaluation-value p1?)
    (reclaim-if-evaluation-value p2?)
    (reclaim-if-evaluation-value p3?)
    (reclaim-if-evaluation-value p4?)
    (reclaim-if-evaluation-value p5?)))

(defun-void collect-modifications-and-modify-gsi-sensor-definition
            (sensor corresponding-icp-object-index)
  (let* ((collection-interval
	   (get-slot-value sensor 'gsi-collection-interval))
	 (value-type
	   (case (type-specification-of-variable-or-parameter-value sensor)
	     (number      gsi-64bit-float-type-tag)
	     (integer     gsi-integer-type-tag)
	     (long        gsi-long-type-tag)
	     (float       gsi-64bit-float-type-tag)
	     (symbol      gsi-symbol-type-tag)
	     (text        gsi-string-type-tag)
	     (truth-value gsi-logical-type-tag)
	     (otherwise   gsi-null-type-tag)))
	 (name-of-item?
	   (get-primary-name-for-frame-if-any sensor))
	 (name-of-class (class sensor)))
    (send-icp-modify-gsi-sensor-definition
      corresponding-icp-object-index
      collection-interval
      value-type
      name-of-item?
      name-of-class)))

(defun maybe-declare-all-gsi-sensors ()
  ;; If the extension is recent enough, we send the update interval
  ;; and value type of every GSI sensor that we know about.
  (with-appropriate-version-for-output (modify-gsi-sensor-definition-icp-version)
    (loop for sensor being class-instance of 'variable
	  do (when (and (active-p sensor)
			(gsi-data-service-p sensor))
	       (let* ((gsi-interface-name 
			(get-slot-value-if-any sensor 'gsi-interface-name)) 
		      (gsi-interface 
			(and gsi-interface-name 
			     (get-instance-with-name-if-any
			       'object 
			       gsi-interface-name)))
		      (sensor-icp-socket
			(and gsi-interface 
			     (get-slot-value-if-any 
			       gsi-interface 
			       'gsi-interface-icp-socket))))
		 (when (and sensor-icp-socket
			    (eq current-icp-socket sensor-icp-socket))
		   (let* ((output-port (icp-output-port current-icp-socket))
     			  (corresponding-icp-object-index?
			    (get-icp-object-index-for-registered-item 
			      sensor
			      output-port)))
		     (when corresponding-icp-object-index?
		       (writing-icp-message-group (output-port)
			 (collect-modifications-and-modify-gsi-sensor-definition
			   sensor
			   corresponding-icp-object-index?))))))))))




;;; Declaration:     gsi-receive-value-for-gsi-sensor
;;;                    (gsi-sensor error-code value value-vector?)
;;; Type:	     Lisp function.
;;; Purpose:	     Store the incoming value of a GSI variable for later 
;;;                  processing.
;;; Arguments:	     > gsi-sensor is a gsi-sensor structure, the local object for
;;;                    the corresponding GSI variable that is transmitting a value
;;;                    from the remote GSI process.
;;;                  > error-code is a fixnum representing the status of the value.
;;;                    the value 0 is reserved for no error, all other values depend
;;;                    on the end-user's application.
;;;                  > value is of ICP object type gsi-data-value (see GSI-COMMON
;;;                    for a description of this type).
;;;                  > value-vector?  is either nil or of ICP object type
;;;                    gsi-value-vector (see GSI-COMMON for a description of this
;;;                    type).
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    receive-value-for-gsi-sensor
;;;                    receive-value-for-gsi-sensor-with-timestamp
;;;                    receive-gsi-sensor-value-vector
;;;                    receive-timestamped-gsi-sensor-value-vector
;;; Prerequisites:   None.
;;; Side effects:    Clears the queued-by-local-data-server flag of the frame
;;;                  containing gsi-sensor when it is active.  Modifies the
;;;                  gsi-sensor-status-code slot of gsi-sensor and the
;;;                  gsi-variable-status of its enclosing GSI variable frame.
;;;                  Enqueues value using save-gsi-variable-for-processing.  Can
;;;                  warn in the logbook.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims value and value-vector?.
;;; Possible bugs:   The queued-by-local-data-server mecahnism may be faulty.
;;;                  Suppose many unsolicited vaules are being processed by
;;;                  gsi-receive-value-for-gsi-sensor.  This function may clear the
;;;                  queued-by-local-data-server flag just when
;;;                  enqueue-gsi-request-for-sensor is checking it.  If this check
;;;                  succeeds (spuriously) then enqueue-gsi-request-for-sensor will
;;;                  end up pushing an extra sensor group onto 
;;;                  sensor-groups-to-send-head.

(defun-simple gsi-receive-status-for-gsi-sensor (gsi-sensor error-code)
  (let* ((sensor-status (get-slot-value-if-any gsi-sensor 'gsi-variable-status))
	 (simplep (or (fixnump sensor-status) (consp sensor-status)))
	 (variablep (unless simplep (of-class-p sensor-status 'variable)))
	 (sensor-status-value
	   (cond (simplep
		  sensor-status)
		 (variablep
		  (when (let ((expiration-time
				(expiration-time-of-current-value
				  sensor-status)))
			  (or (null expiration-time)
			      (eq expiration-time 'never)
			      (>=i expiration-time (clock-get gensym-time))))
		    (get-current-evaluation-value-of-variable-or-parameter
		      sensor-status)))
		 (t
		  (warning-message 
		      3 "GSI sensor ~NF received error code ~a"
		    gsi-sensor
		    error-code)
		  (return-from gsi-receive-status-for-gsi-sensor nil)))))
    (unless (and (fixnump sensor-status-value)
		 (=f sensor-status-value error-code))
      (cond (simplep
	     (change-slot-value gsi-sensor 'gsi-variable-status error-code))
	    (variablep
	     (save-gsi-variable-value-for-processing
	       sensor-status
	       (make-evaluation-integer error-code)
	       (make-evaluation-symbol 'never)
	       nil))))
    (=f error-code no-error)))

(defun-simple gsi-receive-value-for-gsi-sensor 
              (gsi-sensor error-code value? collection-time? value-vector?)
  (cond
    ((or (not (of-class-p gsi-sensor 'item))
	 (not (active-p gsi-sensor)))
     (warning-message 
	 2 "GSI received a value for a sensor which does not exist or is ~
            no longer active.")
     (reclaim-if-evaluation-value value?)
     (reclaim-if-evaluation-value collection-time?)
     (reclaim-gsi-value-vector value-vector?))
    (t
     (let ((g2-sensor-p (of-class-p gsi-sensor 'gsi-data-service)))
       (when g2-sensor-p
	 (clear-queued-by-local-data-server gsi-sensor))
       (let* ((no-error-p
		(or (not g2-sensor-p)
		    (gsi-receive-status-for-gsi-sensor gsi-sensor error-code))))
	 
	 (when (and no-error-p g2-sensor-p (null value?))
	   (warning-message 
	       3 "~a~NF received error code 0 with a NULL_TAG data type"
	     (if g2-sensor-p "GSI sensor " "")
	     gsi-sensor))

	 (cond ((or value? value-vector?)
		;; jh, 2/10/93.  We now serve the vector attributes
		;; even if the "main" variable gets a NULL_TAG.
		(save-gsi-variable-value-for-processing gsi-sensor value? collection-time? value-vector?))
	       (t
		(reclaim-if-evaluation-value collection-time?)))

	 (unless (or no-error-p value?)
	   (task-to-detect-failure gsi-sensor))))))
  nil)

;; jra & jh, 11/10/92.  Modified gsi-receive-value-for-gsi-sensor to improve
;; performance.




;;; Declaration:     process-gsi-sensor-values (ok-to-put-values?)
;;; Type:	     Lisp function.
;;; Purpose:	     Process an incoming value for a GSI variable.
;;; Arguments:       ok-to-put-values?  is non-nil if the GSI variables are actually
;;;                  to get values.  This is always the case except during shutdown.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    save-gsi-variable-value-for-processing
;;;                    gsi-shut-down-data-server?
;;; Prerequisites:   Must be called in an evaluation context.
;;; Side effects:    If the value to process is for a vector attribute whose value
;;;                  is a G2 list, the value is put at the end of the list.  If the
;;;                  value to process is for a vector attribute with a slot with a
;;;                  constant value, the value is placed in the slot.  Otherwise,
;;;                  the value to process is for a GSI variable, and
;;;                  put-current-evaluation-value (in VARIABLES) is called.  Can
;;;                  place messages in logbook.
;;; Non-local exits: None.
;;; Memory impact:   Can accumulate G2 list entries.  Enters and exits a temporary
;;;                  float context every 100 values.  100 was selected arbitrarily
;;;                  to improve performance over entering the context for each
;;;                  variable.  Reclaims the gsi-list enqueued by
;;;                  save-gsi-variable-value-for-processing.  Reclaims the GSI
;;;                  vector value this list can contain.

(defun-void process-gsi-sensor-values (ok-to-put-values?)
  (loop with current-computation-instance = (data-server 'gsi-data-server)
	with time-slice-check-count fixnum = 100
	for counter fixnum = 1 then (if time-slice-check-p 1 (1+f counter))
	for time-slice-check-p = (>=f counter time-slice-check-count)
	until (and time-slice-check-p (time-slice-expired-p))
	while (examine-head-of-queue list-of-gsi-values-to-process-head)
	as g2-sensor-value-list = (dequeue list-of-gsi-values-to-process-head
					   list-of-gsi-values-to-process-tail
					   reclaim-gsi-cons)
	as (sensor value? collection-time? value-vector?) = g2-sensor-value-list
     as *current-computation-frame* = sensor
	do
    (reclaim-gsi-list g2-sensor-value-list)
    (cond
      ((or (not ok-to-put-values?)
	   (and (of-class-p sensor 'gsi-data-service)
		;; prevent values from being put into vars
		;; after stop-collecting is called. BLM 3-29-89
		(eql cancel-collection
		     (get-slot-value-if-any
		       sensor 'gsi-internal-collection-interval))))
       (reclaim-if-evaluation-value value?)
       (reclaim-if-evaluation-value collection-time?)
       (reclaim-gsi-value-vector value-vector?))
      (t
       (when value-vector?
	 (loop for vector-element in value-vector?
	       as (slot-name new-slot-value? new-slot-collection-time?) = vector-element
	       do
	   (when new-slot-value?
               (gsi-ds-put-value *current-computation-frame* slot-name
			       new-slot-value? new-slot-collection-time?)
	     (setf (cadr vector-element) nil)
	     (setf (caddr vector-element) nil)))
	 (reclaim-gsi-value-vector value-vector?))
       (when value?
          (gsi-ds-put-value *current-computation-frame* 'value
			   value? collection-time?))
       ;; Check for higher-priority tasks resulting from the conclude of the
       ;; new value.  Don't use the entire time-slice-expired-p because it is
       ;; too expensive.
       (when (higher-priority-p priority-of-next-task priority-of-current-task)
	 (loop-finish))))
	finally ;on exit from outer loop
	  (when (examine-head-of-queue list-of-gsi-values-to-process-head)
	    ;; Had to relinquish processor, but there are more values to put.
	    (with-current-scheduling
		(task-to-process-gsi-values
		  (priority-of-data-service data-server-parameters))
	      (process-gsi-sensor-values t)))))

(defun gsi-ds-put-value (frame slot-name value collection-time?)
  (cond
    ((eq slot-name 'value)
     (let*-sim ((*current-computation-frame* frame))
       (let* ((managed-float-collection-time-p (managed-float-p collection-time?))
	      (problem-string?
		(cond
		  ((not (of-class-p frame 'variable-or-parameter))
		   (tformat-text-string "Can not conclude a value into ~NF, ~
                                           because it is not a variable or parameter"
					frame))
		  ((not (evaluation-value-p value))
		   (tformat-text-string "Can not conclude ~NF into ~NF, ~
                                           because it is not a value"
					value frame))
		  ((not (type-specification-type-p
			  value
			  (let ((type (get-effective-data-type frame)))
			    (case type
			      (value 'datum)
			      (quantity 'number)
			      (t type)))))
		   (tformat-text-string "Can not conclude ~NV into ~NF, ~
                                           because it is not of the correct type"
					value frame))
		  (t
		   (with-temporary-gensym-float-creation gsi-ds-put-value
		     (put-current-evaluation-value
		       *current-computation-frame*
		       value
		       nil
		       (if managed-float-collection-time-p
			   collection-time?
			 nil)
		       nil))))))
	 (when managed-float-collection-time-p
	   (reclaim-managed-float collection-time?))
	 (when problem-string?
	   (warning-message* 1 "Problem receiving GSI value: ~a" problem-string?)
	   (reclaim-text-string problem-string?)
	   (reclaim-evaluation-value value)))))
    ((and (consp slot-name)
	  (eq (car slot-name) 'vector-element))
     (let* ((index (resumable-vector-or-list-index slot-name))
	    (problem-string?
	      (cond
		((not (of-class-p frame 'g2-array))
		 (tformat-text-string "~NF is not an array" frame))
		((not (and (<=f 0 index)
			   (<f index (g2-array-length frame))))
		 (tformat-text-string "array index out of bounds"))
		(t
		 (mutate-g2-array frame index value t nil)
		 nil))))
       (when problem-string?
	 (warning-message* 1 "Problem receiving GSI value: ~a" problem-string?)
	 (reclaim-text-string problem-string?))))
    ((and (consp slot-name)
	  (eq (car slot-name) 'list-element))
     (let* ((index (resumable-vector-or-list-index slot-name))
	    (length 0)
	    (problem-string?
	      (cond
		((not (of-class-p frame 'g2-list))
		 (tformat-text-string "~NF is not an list" frame))
		((not (and (<=f 0 index)
			   (<f index length)))
		 (tformat-text-string "list index out of bounds"))
		(t
		 (tformat-text-string
		   "gsi_return_attrs into a list: not yet implemented")))))
       (when problem-string?
	 (warning-message* 1 "Problem receiving GSI value: ~a" problem-string?)
	 (reclaim-text-string problem-string?))))
    (t
     (let* ((unqualified-name (unqualified-name slot-name))
	    (class-qualifier (class-qualifier slot-name))
	    (attribute-description?
	      (get-attribute-description-of-frame
		*current-computation-frame* unqualified-name class-qualifier))
	    (current-value
	      (and attribute-description?
		   (get-attribute-description-evaluation-value
		     *current-computation-frame*
		     attribute-description?))))
       (cond
	 ((null attribute-description?)
	  (reclaim-if-evaluation-value value)
	  (reclaim-if-evaluation-value collection-time?))
	 ((not (framep current-value))
	  (reclaim-if-evaluation-value collection-time?)
	  (reclaim-if-evaluation-value current-value)
	  (let ((error-string?
		  (change-attribute-description-evaluation-value
		    *current-computation-frame*
		    attribute-description?
		    value)))
	    (when error-string?
	      (warning-message* 1 "Problem receiving GSI value: ~a" error-string?)
	      (reclaim-text-string error-string?))))
	 ((variable-or-parameter-p current-value)
	  (gsi-ds-put-value current-value 'value value collection-time?))
	 ((g2-list-p current-value)
	  (reclaim-if-evaluation-value collection-time?)
	  (cond ((of-class-p value 'g2-list)
		 (reclaim-evaluation-value value))
		((datum-ok-for-g2-list-or-array-p
		   value
		   (list-type current-value))
		 (g2-list-insert-at-end value current-value))
		(t
		 (reclaim-evaluation-value value))))
	 ((g2-array-p current-value)
	  (reclaim-if-evaluation-value collection-time?)
	  (cond ((of-class-p value 'g2-array)
		 (reclaim-evaluation-value value))
		((datum-ok-for-g2-list-or-array-p
		   value
		   (g2-array-element-type current-value))
		 (let ((current-size (g2-array-length current-value)))
		   (change-slot-value current-value 'g2-array-length
				      (1+f current-size))
		   (mutate-g2-array current-value current-size value t t)))
		(t
		 (reclaim-evaluation-value value))))
	 (t
	  (reclaim-evaluation-value value)
	  (reclaim-if-evaluation-value collection-time?)))))))

;; Modified process-gsi-sensor-values to check for genuine values when it is
;; serving vector attributes.  When the attributes don't exist, the values
;; are not temporary constants but nil.  (jh, 7/17/90)

;; blm & jh, 9/25/91.  To improve performance, moved the
;; with-temporary-gensym-float-creation wrapper out of the inner (per-variable)
;; loop in process-gsi-sensor-values.  With-temporary-gensym-float-creation calls
;; setjmp in Chestnut, an expensive operation.  We now enter this wrapper once in
;; a while (every 100 times for now), to avoid repeatedly establishing and
;; de-establishing setjmps every time we process a variable.  A different, but
;; related, fix is moving the with-temporary-gensym-float-creation wrapper out of
;; the inner loop of vector-attribute processing in this function (q.v.).

;; jh, 11/9/92.  Improved process-gsi-sensor-values to check for a
;; higher-priority process resulting from each conclude it does.  This involves
;; re-scheduling the task which calls process-gsi-sensor-values if any values
;; remained when a higher-priority task is detected.  While I was at it, fixed a
;; bug in the loop which periodically exits and re-enters the
;; with-temporary-gensym-float-creation scope.  Previously, this would dequeue a
;; value and only then check if it should exit the scope, leaving this value
;; forever unprocessed.  This will soon be moot, however, since we are
;; eliminating with-temporary-gensym-float-creation scopes entirely.

;; jra & jh, 11/10/92.  Removed temporary float scopes from
;; process-gsi-sensor-values, in concert with modifications to the GSI value
;; readers in GSI-COMMON which allow us to use managed floats everywhere.  This
;; should be a performance win.  Note that we retain the exit and re-entry every
;; time temporary-area-counter reaches 100, because we can use this opportunity
;; to make the expensive time-slice-expired-p check.  (We do a more frequent
;; check that no task has a higher priority than this one.  This is the easy
;; part of time-slice-expired-p.)

;(defmacro dequeue (head tail release-cons-function)
;  (let ((value-of-head (gensym))
;	(value-of-next-item (gensym)))
;    `(let ((,value-of-head ,head) ,value-of-next-item)
;       (if ,value-of-head
;	   (prog1 (car ,value-of-head)
;		  (setq ,value-of-next-item (cdr ,value-of-head))
;		  (setf ,head ,value-of-next-item)
;		  (unless ,value-of-next-item (setf ,tail nil))
;		  (,release-cons-function ,value-of-head))
;	   nil))))
;; in UTILITIES0





;;; Declaration:     return-gsi-extension-version 
;;;                    (major-version-number minor-version-number)
;;; Type:	     ICP message.
;;; Purpose:         Acquire the software version of the remote GSI process and
;;;                  inform that process of the software version of this G2.
;;; Arguments:       major-version-number and minor-version-number are of ICP value
;;;                  type unsigned integer.
;;; Return behavior: No useful value.
;;; Users:           This message is never sent to the remote GSI process.  Only its
;;;                  handler is ever called by G2.
;;; Prerequisites:   None.
;;; Side effects:    Transmits the ICP message modify-gsi-sensor-definition.
;;; Non-local exits: None.
;;; Memory impact:   None.


;;; Declaration:     icp-sockets-now-initializing-gsi
;;; Type:	     Lisp system variable.
;;; Purpose:         Postpone sending and receiving values until a GSI interface is
;;;                  finished initializing.
;;; Value:           A gsi-list of icp-socket structures.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    write-message-group-upon-gsi-interface-activation
;;;                    handle-gsi-shut-down-connection
;;;                    process-requests-for-gsi-interfaces
;;;                    gsi-receive-value-for-ping-request
;;; Prerequisites:   Must be referenced within a with-system-variables scope.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Conses in this list are allocated by
;;;                  write-message-group-upon-gsi-interface-activation and reclaimed
;;;                  by handle-gsi-shut-down-connection and
;;;                  gsi-receive-value-for-ping-request.

;; Icp-sockets-now-initializing-gsi is a gsi-list of icp-sockets whose GSI
;; extension process is in the midst of initialization.  We keep this list so we
;; can supress spurious get-value messages while the initialization is going on.
;; See note below.  (jh, 7/11/90)

(def-system-variable icp-sockets-now-initializing-gsi G2-GSI nil)



;;; Declaration:     write-message-group-upon-gsi-interface-activation
;;;                    (icp-socket
;;; 	                process-initialization-string
;;; 	                interface-struct)
;;; Type:	     Lisp function.
;;; Purpose:	     Cause the remote GSI process to initialize.
;;; Arguments:	     > icp-socket
;;;                  > process-initialization-string
;;;                  > interface-struct
;;; Return behavior: No useful value.
;;; Users:           GSI internals
;;;                  (activate-gsi-interface-with-connection-spec).
;;; Prerequisites:   None.
;;; Side effects:    Modifies icp-sockets-now-initializing-gsi.  Sends the ICP
;;;                  messages initialize-data-server and send-data-values-if-any.
;;;                  Also calls make-corresponding-icp-gsi-interface (q.v.).
;;; Non-local exits: None.
;;; Memory impact:   Pushes the current-icp-socket onto
;;;                  icp-sockets-now-initializing-gsi using a gsi-cons.

;;; All gsi interfaces will be activated and connections made when starting a
;;; kb.  When resetting a kb the interface connections will be dropped.  This
;;; function is also responsible for installing true value updates for the
;;; attributes which identify a sensor.  Amongst other things.  (Please document
;;; further!  -jra 5/8/90)

;; (jh, 7/11/90)

;; There is a bug which causes a GSI extension to call gsi_get_data before
;; gsi_def_obj, that is, the extension tries to get values for a GSI sensor before
;; it is defined.  This confuses much customer bridge code.  The fix must do two
;; things: supress these extraneous get-value messages and work with both old and
;; new GSI extensions.
;;
;; To understand the problem, note the following facts.  Initializing a GSI
;; extension is the result of the base G2 sending an ICP init-dataserver message.
;; This causes the extension to call the user-written init_ds bridge code.
;; Defining a GSI sensor in the extension now takes two messages from G2: the
;; original (pre-2.0) define-object message followed by the new (2.0 and later)
;; modify-definition message.  The old extensions call gsi_def_obj as soon as they
;; receive the define-object message, whereas the new GSI extensions don't call
;; the gsi_def_obj bridge code until both messages are received.  In both
;; extensions, sending a get-values message causes the extension to call the
;; gsi_get_data bridge function.
;;
;; The problem arises when a new extension takes an appreciable amount of time
;; initializing.  The base G2 then has time to queue up a get-values message
;; (causing a call to gsi_get_data) before the modify-definition message which
;; completes the definition (causing a call to gsi_def_obj).
;;
;; The fix is to keep track of the ICP sockets through which we've sent
;; initialize-dataserver messages.  We do this in the list
;; icp-sockets-now-initializing-gsi.  We only allow get-values messages through a
;; given ICP socket after the initialization is finished.  This is determined by
;; sending out a send-data-values-if-any message (called a "ping") in the same
;; message group as the init-dataserver message.  The ping message is known to
;; both old and new extensions, and causes either to send a second ping back to
;; G2.  When G2 gets this ping, it removes the interface from
;; icp-sockets-now-initializing-gsi and allows subsequent get-values messages
;; through.

;; (blm, ac, & jh, 7/12/90)
;; Added a connection-loss callback function for GSI sockets.
;; It is registered in the capability activator for GSI interfaces.
;; See note below, under handle-gsi-shut-down-connection.

(defun-simple write-message-group-upon-gsi-interface-activation
	      (icp-socket
		process-initialization-string
		interface-struct)
  (writing-icp-message-group ((icp-output-port icp-socket))
    
    (send-icp-initialize-data-server (or process-initialization-string #w""))
    
    (unless (get-icp-object-index-for-gsi-icp-interface 
	      interface-struct current-icp-port)
      (make-corresponding-icp-gsi-icp-interface interface-struct))

    ;; send a "ping" so we know when GSI is through initializing
    ;; also see 'gsi-send-reply-to-initial-ping-internal
    (send-icp-send-data-values-if-any-1
      interface-struct 0 0 0 1 1 1970))	; send bogus timestamp
					; (second minute hour day month year)

  (setf (gsi-interface-waiting-for-response-p interface-struct) nil)

  ;; supress sensor messages until GSI replies to the "ping"
  (setf (gsi-connection-state icp-socket) gsi-connection-initializing))
  





;;; Declaration:     gsi-interface
;;; Type:	     G2 capability activator.
;;; Purpose:	     Initialize a GSI interface if GSI is authorized.
;;; Arguments:	     A GSI interface frame.
;;; Return behavior: No useful value.
;;; Users:           The capability activation machinery in the CAPABILITY and
;;;                  ACTIVATE modules.
;;; Prerequisites:   The def-capability-activator macro must be defined.
;;; Side effects:    At compile time, creates a funcallable function named
;;;                  activate-gsi-interface-capability.  At run time,
;;;                  this function calls
;;;                  activate-gsi-interface-with-connection-spec.
;;; Non-local exits: None.
;;; Memory impact:   Modifies property lists once at launch.

(def-class-method activate (gsi-interface)
  (execute-body-if-gsi-is-authorized
    (unless (runs-while-inactive-p gsi-interface)
      (activate-gsi-interface gsi-interface nil))
    (schedule-data-server-accept-data-calls)
    (funcall-superior-method gsi-interface)))

(def-class-method manually-enable (gsi-interface)
  ;; If the connection does not persist during reset, it will not be made here,
  ;; but rather in the activate method.
  (when (runs-while-inactive-p gsi-interface)
    (activate-gsi-interface gsi-interface nil))
  ;; Calling the superior must come last to avoid double activation.
  (funcall-superior-method gsi-interface))

(defun-simple gsi-icp-socket-connected-p (gsi-interface)
  (let* ((interface-icp-socket?
	   (get-slot-value-if-any gsi-interface 'gsi-interface-icp-socket))
	 (connected-p	   
	   (and interface-icp-socket?
		(icp-connection-open-p interface-icp-socket?)
		(not (icp-connection-being-shutdown? interface-icp-socket?)))))
    connected-p))

(def-class-method note-ancestor-manually-enabled (gsi-interface)
  (when (runs-while-inactive-p gsi-interface)
    (unless (manually-disabled-p gsi-interface)
      (unless (gsi-icp-socket-connected-p gsi-interface)
	(activate-gsi-interface gsi-interface nil)))))

;; jh, 2/19/92.  Removed with-dynamic-creation wrapper from the
;; capability activator for gsi-interface.  To the best of
;; my knowledge, there is no reason for this wrapper, since distribution
;; platforms should never leak.




;;; Declaration:     activate-gsi-interface-with-connection-spec
;;;                    (gsi-interface-frame interface-configuration?)
;;; Type:	     Lisp function.
;;; Purpose:	     Initialize a GSI interface.
;;; Arguments:       interface-configuration?  is a list in
;;;                  icp-connection-configuration format (see INT4), or nil.  If
;;;                  interface-configuration?  is non-nil, gsi-interface is a GSI
;;;                  interface frame that will connect to remote GSI process given
;;;                  by interface-configuration?.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    capability activator for gsi-interface
;;;                    slot putter for gsi-connection-configuration
;;; Prerequisites:   None.
;;; Side effects:    > GSI interface: Modifies the gsi-sensor-groups-header,
;;;                    gsi-interface-structure, gsi-interface-icp-socket, and the
;;;                    enclosing-interface-frame?  slots of gsi-interface-frame.
;;;                    Adds gsi-interface-frame to list-of-all-gsi-interfaces-head.
;;;                  > GSI variables: Installs a true-value updater on every
;;;                    variable which has an attribute named in the
;;;                    identifying-attributes slot of gsi-interface-frame.  (The
;;;                    updater function further filters any variable down to those
;;;                    GSI variables actually connected through
;;;                    gsi-interface-frame.) Begins collecting data for every GSI
;;;                    variable using gsi-interface-frame.
;;;                  > other effects: Can create an ICP connection to a process
;;;                    described by interface-configuration?.  Can place messages in
;;;                    the logbook.  Registers the major and minor version of the
;;;                    ICP socket within gsi-interface-frame.  Registers
;;;                    handle-gsi-shut-down-connection as the connection-loss
;;;                    callback function for the ICP socket inside
;;;                    gsi-interface-frame.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a sensor-groups-header structure and a gsi-interface
;;;                  structure inside gsi-interface-frame.  The capability
;;;                  deactivator reclaims these structures.  Calls set-major-version
;;;                  and set-minor-version, which can allocate version conses.  Can
;;;                  allocate a gsi cons to enqueue gsi-interface-frame onto
;;;                  list-of-all-gsi-interfaces-head.  Allocates memory for
;;;                  true-value updaters.

(defvar maintaining-gsi-interface-status-changed-p nil)
(defvar gsi-interface-status-changed-p)

(defun-void change-gsi-interface-status (gsi-interface-frame new-status)
  (when maintaining-gsi-interface-status-changed-p
    (setq gsi-interface-status-changed-p t))
  (let ((gsi-interface-status-slot-value?
	  (get-slot-value-if-any gsi-interface-frame 'gsi-interface-status)))
    (cond ((or (integerp gsi-interface-status-slot-value?)
	       (consp gsi-interface-status-slot-value?))
	   (let ((*current-computation-frame* gsi-interface-frame))
	     (change-slot-value
	       gsi-interface-frame 'gsi-interface-status new-status)))
	  ((and (framep gsi-interface-status-slot-value?)
		(variable-p gsi-interface-status-slot-value?))
	   (let ((*current-computation-frame* gsi-interface-status-slot-value?)
		 (current-computation-instance (data-server 'gsi-data-server)))
	     (put-current-value
	       gsi-interface-status-slot-value? new-status 'number nil nil)))
	  (t (write-warning-message 
		 2
	       (tformat
		 "GSI interface ~NF has invalid status ~a"
		 gsi-interface-frame
		 gsi-interface-status-slot-value?))))
    (change-slot-value
      gsi-interface-frame 'gsi-interface-is-secure
      (icp-connection-is-secure (gsi-interface-icp-socket gsi-interface-frame)))))
      

(defun get-gsi-interface-status (gsi-interface-frame)
  (let ((gsi-interface-status-slot-value?
	  (get-slot-value-if-any gsi-interface-frame 'gsi-interface-status)))
    (cond ((or (integerp gsi-interface-status-slot-value?)
	       (consp gsi-interface-status-slot-value?))
	   gsi-interface-status-slot-value?)
	  ((and (framep gsi-interface-status-slot-value?)
		(variable-p gsi-interface-status-slot-value?))
	   (let ((*current-computation-frame* gsi-interface-status-slot-value?)
		 (current-computation-instance (data-server 'gsi-data-server)))
	     (get-current-value
	       gsi-interface-status-slot-value? t)))
	  (t (write-warning-message 
		 2
	       (tformat
		 "GSI interface ~NF has invalid status ~a"
		 gsi-interface-frame
		 gsi-interface-status-slot-value?))))))

(defvar gsi-connection-checkup-interval-in-ms 100)

(defun maybe-warn-about-missing-identifying-attributes
    (interface-name-or-names? gsi-interface-frame)
  ;; jh, 6/16/92.  Write a warning message only if there are variables
  ;; that connect to this interface, since some interfaces are used
  ;; simply for RPC calls.  Note that what we really need is a set of
  ;; frame notes for GSI interfaces and variables, not to mention one
  ;; for the G2-to-G2 machinery.
  (when (loop for sensor being class-instance of 'variable
	      for desired-interface-name
		  = (get-slot-value-if-any 
		      sensor 'gsi-interface-name)
	      thereis (and (gsi-data-service-p sensor)
			   (if (consp interface-name-or-names?)
			       (memq desired-interface-name
				     interface-name-or-names?)
			       (eq desired-interface-name
				   interface-name-or-names?))))
    (write-warning-message 
	2
      (tformat
	"You must specify the identifying attributes for GSI interface ~NF."
	gsi-interface-frame))))

(defun activate-variables-for-gsi-interface (gsi-interface-frame)
  (let ((interface-name-or-names?
	  (get-primary-name-for-frame-if-any gsi-interface-frame))
	(attributes-which-identify-a-sensor?
	  (get-slot-value-if-any gsi-interface-frame 'identifying-attributes)))
    (when interface-name-or-names?
      (unless attributes-which-identify-a-sensor?
	(maybe-warn-about-missing-identifying-attributes interface-name-or-names?
							 gsi-interface-frame)
	(return-from activate-variables-for-gsi-interface nil))
      (install-true-value-updates-for-gsi
	gsi-interface-frame
	nil
	attributes-which-identify-a-sensor?))))



(defun maybe-begin-collecting-data-for-interface (gsi-interface-frame)
  (when (or system-has-paused system-is-running)
    (let* ((interface-name-or-names?
	     (get-primary-name-for-frame-if-any gsi-interface-frame))
	   (begin-collecting-data-list
	     (when interface-name-or-names?
	       (loop for sensor being class-instance of 'variable
		     for desired-interface-name
			 = (get-slot-value-if-any 
			     sensor 
			     'gsi-interface-name)
		     when (and (active-p sensor)
			       (gsi-data-service-p sensor)
			       (if (consp interface-name-or-names?)
				   (memq desired-interface-name
					 interface-name-or-names?)
				   (eq desired-interface-name
				       interface-name-or-names?)))
		       collect sensor using gsi-cons))))
      (loop with gsi-variables? = begin-collecting-data-list
	    while gsi-variables?
	    do
	(with-temporary-gensym-float-creation
	    finalize-gsi-connection
	  (loop repeat iterations-for-gsi-temporary-float-processing
		for gsi-variable? = (pop gsi-variables?)
		while gsi-variable?
		do
	    (clear-queued-by-local-data-server gsi-variable?)
	    (let ((data-collection-interval
		    (get-slot-value gsi-variable? 'gsi-collection-interval)))
	      (when (evaluation-quantity-> data-collection-interval 0)
		(gsi-begin-collecting-data 
		  gsi-variable?
		  data-collection-interval))))))
      (reclaim-gsi-list begin-collecting-data-list))))

(defun maybe-stop-collecting-data-for-interface (gsi-interface-frame)
  (let ((interface-name-or-names?
	  (get-primary-name-for-frame-if-any gsi-interface-frame)))
    (when interface-name-or-names?
      (loop for sensor being class-instance of 'variable
	    for desired-interface-name
		= (get-slot-value-if-any 
		    sensor 
		    'gsi-interface-name)
	    when (and (active-p sensor)
		      (gsi-data-service-p sensor)
		      (if (consp interface-name-or-names?)
			  (memq desired-interface-name
				interface-name-or-names?)
			  (eq desired-interface-name
			      interface-name-or-names?)))
	      do (deactivate-dataservice-for-gsi-data-service sensor)))))

(defun gsi-interface-current-icp-socket (gsi-interface-frame)
  (let ((icp-socket?
	  (get-slot-value-if-any gsi-interface-frame 'gsi-interface-icp-socket)))
    (when (and icp-socket?
	       (not (and (eq (enclosing-interface-frame? icp-socket?) gsi-interface-frame)
			 (frame-has-not-been-reprocessed-p
			   gsi-interface-frame
			   (enclosing-interface-frame-serial-number icp-socket?)))))
      (setq icp-socket? nil)
      (set-slot-value gsi-interface-frame 'gsi-interface-icp-socket nil))
    icp-socket?))

(defmacro check-for-number-or-default (x)
  (let ((var (make-symbol "VAR")))
    `(let ((,var ,x))
       (if (numberp ,var)
	   ,var
	   nil))))

(defmacro check-for-number-or-default-or-none (x)
  (let ((var (make-symbol "VAR")))
    `(let ((,var ,x))
       (cond ((numberp ,var)
	      ,var)
	     ((null ,var)
	      'none)
	     (t
	      nil)))))

(defun activate-gsi-interface (gsi-interface-frame already-initialized-p)
  (let ((icp-socket? (gsi-interface-current-icp-socket gsi-interface-frame)))
    ;;   If there is an icp-socket in the gsi-interface, and if that socket is
    ;;   shutting down, then cause the connection loss callback to attempt the
    ;;   activation again.  If there's a socket and it's not shutting down, then
    ;;   there has been a serious error -- activate should never be called on an
    ;;   interface that has a socket which hasn't been processed by the
    ;;   connection loss callback, which clears the icp socket slot. -ncc,
    ;;   3/16/95
    ;;   Now that GSI can initiate a connection to G2, the statement above is
    ;;   no longer true. -rh 4/19/96
    (when (and icp-socket?
	       (icp-connection-being-shutdown? icp-socket?))
      (set-slot-value gsi-interface-frame
		      'gsi-interface-activate-after-shutdown
		      t)
      (return-from activate-gsi-interface))

    (unless icp-socket?
      (let ((interface-configuration?
	      (car (get-slot-value-if-any 
		     gsi-interface-frame
		     'gsi-connection-configuration)))
	    (application-name
	      (get-slot-value-if-any gsi-interface-frame 'gsi-application-name)))
	(cond ((null interface-configuration?)
	       (change-gsi-interface-status
		 gsi-interface-frame
		 gsi-interface-initializing))
	      (t
	       ;; second arg t -> we support new connect scheme -ncc, 19 May 1995
	       (setq icp-socket?
		     (make-icp-connection
		       interface-configuration?
		       'gsi application-name
		       (or (check-for-number-or-default-or-none
			     (get-slot-value-if-any gsi-interface-frame
						    'interface-initialization-timeout-period))
			   (check-for-number-or-default
			     (get-slot-value-if-any gsi-interface-frame
						    'interface-timeout-period))
			   default-gsi-interface-countdown-timer-limit)))
	       (unless icp-socket?
		 (change-gsi-interface-status
		   gsi-interface-frame
		   gsi-interface-icp-connection-dead)
		 (write-warning-message 3
		   (tformat
		     "Cannot make ICP connection for GSI data interface ~NF"
		     gsi-interface-frame)))))))

    (when icp-socket?
      (when (get-slot-value-if-any gsi-interface-frame
				   'disable-interleaving-of-large-messages)
	(setf (icp-socket-does-not-allow-resumability icp-socket?) 'requested))
      (setf (icp-connection-succeeds-at-first-message-p icp-socket?) nil)
      (activate-gsi-interface-with-socket gsi-interface-frame icp-socket? already-initialized-p))))

(defun activate-gsi-interface-with-socket (gsi-interface-frame icp-socket already-initialized-p)
  ;; register the callback, to clean up if the connect eventually fails. -ncc, 11 Jun 1995 
  (register-icp-callback 'icp-connection-loss 'handle-gsi-connect-attempt-failure icp-socket)
  (setf (icp-socket-listener-client? icp-socket) 'gsi)
  (setf (enclosing-interface-frame? icp-socket) gsi-interface-frame)
  (frame-serial-number-setf (enclosing-interface-frame-serial-number icp-socket)
			    (frame-serial-number gsi-interface-frame))

  (setf (icp-socket-runs-while-inactive icp-socket)
	(runs-while-inactive-p gsi-interface-frame))

  (change-gsi-interface-status gsi-interface-frame gsi-interface-waiting-for-response)
  
  (set-slot-value gsi-interface-frame 'gsi-sensor-groups-header 
		  (make-sensor-groups-header))
  
  (let* ((gsi-interface-countdown-timer-limit
	   (or (check-for-number-or-default
		 (get-slot-value-if-any gsi-interface-frame 'interface-timeout-period))
	       default-gsi-interface-countdown-timer-limit))
	 (interface-struct 
	   (make-gsi-icp-interface 
	     gsi-interface-frame
	     (copy-frame-serial-number (frame-serial-number gsi-interface-frame))
	     (fixnum-time-interval
	       (*f 1000 gsi-interface-countdown-timer-limit))
	     (fixnum-time-interval
	       (*f 1000 gsi-interface-countdown-timer-limit)))))
    
    (set-slot-value gsi-interface-frame 'gsi-interface-structure interface-struct)
    (setf (gsi-interface-waiting-for-response-p interface-struct) t)
    (set-slot-value gsi-interface-frame 'gsi-interface-icp-socket icp-socket)

    (setf (icp-socket-does-not-allow-resumability icp-socket)
	  (get-slot-value-if-any gsi-interface-frame
				 'disable-interleaving-of-large-messages))

    (if (eq (icp-connection-state icp-socket) icp-connection-running)
	(finalize-gsi-connection icp-socket already-initialized-p) ; GSI initiated connection
	(setup-network-connection-for-connect icp-socket 'finalize-gsi-connection-1))))

(defun-void finalize-gsi-connection-1 (icp-socket)
  (finalize-gsi-connection icp-socket nil))

(defun-void finalize-gsi-connection (icp-socket already-initialized-p)
  (let ((gsi-interface-frame (enclosing-interface-frame? icp-socket)))
    
    (gsi-push gsi-interface-frame list-of-all-gsi-interfaces)

    (let ((icp-socket (get-slot-value-if-any gsi-interface-frame 'gsi-interface-icp-socket)))
      ;; set up the real connection loss callback, in place of the transitional
      ;; one for connection negotiation. -ncc, 11 Jun 1995 
      (deregister-all-icp-callbacks 'icp-connection-loss icp-socket)
      (register-icp-callback 'icp-connection-loss 'handle-gsi-shut-down-connection icp-socket)

      (unless already-initialized-p
	(write-message-group-upon-gsi-interface-activation
	  icp-socket
	  (get-slot-value-if-any 
	    gsi-interface-frame 
	    'remote-process-initialization-string)
	  (get-slot-value-if-any gsi-interface-frame 'gsi-interface-structure))))))



;;; Declaration:     clear-interface-from-gsi-processing-queue
;;;                    (gsi-interface-frame queue-head queue-tail)
;;; Type:	     Lisp macro.
;;; Purpose:	     Disallow processing on a GSI interface.
;;; Arguments:       gsi-interface-frame is the GSI interface which is to shut down,
;;;                  queue-head is the head of the processing queue where the
;;;                  interface appears, and queue-tail is the tail of that queue.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (handle-gsi-shut-down-connection).
;;; Prerequisites:   Assumes the queue is a GSI list.
;;; Side effects:    Removes gsi-interface-frame from the queue.  The queue is
;;;                  unaffected if gsi-interface-frame is not present.
;;; Non-local exits: Does not signal if gsi-interface-frame is absent from the
;;;                  queue.
;;; Memory impact:   Can reclaim a gsi-cons.  If a queue using some other kind of
;;;                  cons is passed to this macro, a leak will result.

;; jh, 11/10/91.  Abstracted clear-interface-from-gsi-processing-queue from
;; handle-gsi-shut-down-connection so we can delete the interface frame both the
;; list-of-all-gsi-interfaces and the gsi-interfaces-to-process queues.  Not
;; clearing the latter was causing problems when gsi interfaces we deleted.  G2DS
;; does not need analogous changes because it maintains a single queue,
;; list-of-all-g2ds-interfaces, and handle-g2ds-shut-down-client deletes the
;; interface frame properly from it.

(defmacro clear-interface-from-gsi-processing-queue 
       (gsi-interface-frame queue-head queue-tail)
  (avoiding-variable-capture
      (gsi-interface-frame &aux next-one? good-ones good-one)
    `(loop for ,next-one?				
	       = (dequeue ,queue-head ,queue-tail reclaim-gsi-cons)
	   while ,next-one?
	   when (not (eq ,next-one? ,gsi-interface-frame))
	     collect ,next-one? into ,good-ones using gsi-cons
	   finally
	     (loop for ,good-one in ,good-ones
		   do (enqueue ,good-one ,queue-head ,queue-tail gsi-cons))
	     (reclaim-gsi-list ,good-ones))))





;;; Declaration:     handle-gsi-shut-down-connection
;;;                    (icp-socket-to-close &optional gsi-interface-frame-to-close?)
;;; Type:	     Lisp function.
;;; Purpose:	     Take action when a GSI connection shuts down.
;;; Arguments:       icp-socket-to-close is an icp-socket structure,
;;;                  gsi-interface-frame-to-close is a GSI interface or nil if one
;;;                  must be deduced.  The capability deactivator for
;;;                  gsi-interface calls this function with a GSI
;;;                  interface.  When this function is called as part of an
;;;                  unexpected shutdown (i.e., at times other than when G2 is
;;;                  reset), gsi-interface-frame-to-close?  is nil.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    capability deactivator for gsi-interface
;;; Prerequisites:   In order to be called when the GSI connection shuts down
;;;                  unexpectedly, this function must be registered as a
;;;                  connection-loss callback.  This is currently done in
;;;                  activate-gsi-interface-with-connection-spec.
;;; Side effects:    > gsi-interface-frame-to-close?: Changes the
;;;                    gsi-interface-status slots of gsi-interface-frame-to-close?
;;;                    Removes gsi-interface-frame from the processing queues
;;;                    gsi-interfaces-to-process-head and
;;;                    list-of-all-gsi-interfaces-head.  Dequeues every pending
;;;                    request in the gsi-sensor-groups-header slot of
;;;                    gsi-interface-frame.  Shuts down the ICP connection within
;;;                    gsi-interface-frame.
;;;                  > GSI variables: De-installs the true-value updater for each
;;;                    GSI variable attribute named in the identifying-attributes
;;;                    slot of gsi-interface-frame-to-close?.
;;;                  > ICP socket: Sends the ICP message shut-down-data-server.
;;;                    Reclaims the ICP object maps for the ICP socket inside
;;;                    gsi-interface-frame.  Removes the version information
;;;                    associated with this ICP socket.  Deregisters all
;;;                    connection-loss callback functions for this ICP socket.
;;; Non-local exits: None.
;;; Memory impact:   Deallocates memory for the true-value updaters of
;;;                  identifying-attributes.  Reclaims the gsi-interface stored in
;;;                  the gsi-interface-structure slot of gsi-interface-frame.
;;;                  Reclaims the memory for version information.

;; (blm, ac, & jh, 7/12/90) There was a major, "sleeper" bug waiting to happen
;; in both GSI and G2-to-G2 data service.  When an ICP socket failed,
;; process-icp-sockets would recycle it, even though a pointer to the socket was
;; left on the enclosing interface frame.  This caused bizarre behavior when the
;; socket was reincarnated as another ICP socket, probably due to a mixture of
;; gsi and g2-to-g2 ports in the same socket.  The behavior included mysterious
;; crashing of RPC extensions process and inappropriate messages at G2 reset
;; time.

;; The fix is to use the connection-loss callback facility to register a
;; function which will get called when the socket fails.  This callback
;; function, named handle-gsi-shut-down-connection, will correctly clean things
;; up.  Cleanup here means that the enclosing interface frame's pointer to the
;; socket must be set to nil and the enclosed ports of the socket must be shut
;; down in a platform-specific manner using shutdown-icp-socket-connection.  As
;; a matter of fact, the callback function almost completely subsumes the duties
;; of the capability deactivator for the interface.

;; Handle-gsi-shut-down-connection was neglecting to recycle things when the
;; interface had no icp-socket.  Such a thing happens when the interface fails
;; to make a connection.  This function is called for two events: normal gsi
;; capability deactivation (in the def-capability-deactivator for gsi-interface)
;; and abnormal gsi connection loss (via a call to
;; register-icp-connection-loss-callback when the capability is activated).
;; Handle-gsi-shut-down-connection still should contain all code shared between
;; normal and abnormal shutdowns.  Added optional arguments to allow the
;; gsi-interface-frame to be passed in the event of a normal deactivation.  In
;; this case we don't care if we find an icp-socket in the gsi-interface-frame
;; -- we still want to recycle everything else.  Analogous changes have been
;; made in the g2-to-g2 interface.  (jh, 9/13/90)

(defun-void remove-pending-requests-from-gsi-interface (gsi-interface-frame)
  (loop with sensor-groups-header? =
	(get-slot-value-if-any 
	  gsi-interface-frame
	  'gsi-sensor-groups-header)
	as sensor-group? =
	(if sensor-groups-header?
	    (dequeue (sensor-groups-to-send-head sensor-groups-header?)
		     (sensor-groups-to-send-tail sensor-groups-header?)
		     reclaim-gsi-cons))
	until (null sensor-group?)
	do (loop as sensor-cons? = 
		 (dequeue 
		   (sensor-group-sensors-to-send-head sensor-group?)
		   (sensor-group-sensors-to-send-tail sensor-group?)
		   reclaim-gsi-cons)
		 until (null sensor-cons?)
		 do (reclaim-gsi-cons sensor-cons?))
	   (loop with group-parameters? = 
		 (sensor-group-parameters sensor-group?)
		 for evaluation-value in group-parameters?
		 do 
	     (reclaim-if-evaluation-value evaluation-value)
		 finally 
		   (setf (sensor-group-parameters sensor-group?) nil)
		   (when group-parameters?
		     (reclaim-gsi-list group-parameters?)))
	   (reclaim-sensor-group sensor-group?)
	finally 
	  (set-slot-value gsi-interface-frame 'gsi-sensor-groups-header nil)
	  (when sensor-groups-header?
	    (reclaim-sensor-groups-header sensor-groups-header?))))

(defun-void handle-gsi-connect-attempt-failure (icp-socket clean?)
  (declare (ignore clean?))

  (let ((gsi-interface-frame? (enclosing-interface-frame? icp-socket)))
    (when (and (framep-function gsi-interface-frame?)
	       (frame-has-not-been-reprocessed-p
		 gsi-interface-frame?
		 (enclosing-interface-frame-serial-number icp-socket)))
      (let ((reason-for-shutdown? (reason-for-shutdown? icp-socket)))
	(change-gsi-interface-status
	  gsi-interface-frame?
	  gsi-interface-icp-connection-dead)
	(disconnect-socket-from-gsi-interface gsi-interface-frame?)
	(cond (reason-for-shutdown?
	       (with-interface-warning-message-level gsi-interface-frame?
		 (write-warning-message 3
		   (tformat "GSI connection attempt failed for interface ~NF, error was ~a."
			    gsi-interface-frame?
			    reason-for-shutdown?))))
	      (t ; connection lost for unknown reason.  This is an internal error.
	       (with-interface-warning-message-level gsi-interface-frame?
		 (write-warning-message 3
		   (tformat "GSI connection attempt failed for interface ~NF."
			    gsi-interface-frame?)))))))))

(defun-void disconnect-socket-from-gsi-interface (gsi-interface)
  (let* ((interface-icp-socket?
	   (get-slot-value-if-any gsi-interface 'gsi-interface-icp-socket)))
    (when interface-icp-socket?
      (setf (enclosing-interface-frame? interface-icp-socket?) nil)
      (set-slot-value gsi-interface 'gsi-interface-icp-socket nil))))

(defun stop-processing-on-gsi-interface (gsi-interface-frame)
  ;; clear gsi interface from all processing queues
  (clear-interface-from-gsi-processing-queue 
    gsi-interface-frame
    gsi-interfaces-to-process-head
    gsi-interfaces-to-process-tail)
  (setq list-of-all-gsi-interfaces
	(delete-gsi-element gsi-interface-frame
			    list-of-all-gsi-interfaces))

  (disconnect-socket-from-gsi-interface gsi-interface-frame)

  (maybe-stop-collecting-data-for-interface gsi-interface-frame)

  (remove-pending-requests-from-gsi-interface gsi-interface-frame))


(defun-void handle-gsi-shut-down-connection (icp-socket clean?)
  (declare (ignore clean?))
  (let* ((gsi-interface-frame? (enclosing-interface-frame? icp-socket)))
    (when (and (framep-function gsi-interface-frame?)
	       (frame-has-not-been-reprocessed-p
		 gsi-interface-frame?
		 (enclosing-interface-frame-serial-number icp-socket)))
      (let* ((gsi-interface-structure?
	       (get-slot-value-if-any gsi-interface-frame?
				      'gsi-interface-structure))
	     (gsi-interface-countdown-timer-limit
	       (get-slot-value-if-any gsi-interface-frame?
				      'interface-timeout-period))
	     (reason-for-shutdown? (reason-for-shutdown? icp-socket)))
	;; change the frame status
	(change-gsi-interface-status
	  gsi-interface-frame?
	  gsi-interface-icp-connection-dead)
	(when (and reason-for-shutdown?
		   (not (eq reason-for-shutdown?
			    'eof-awaiting-shutdown-acknowledgement)))
	  (with-interface-warning-message-level gsi-interface-frame?
	    (write-warning-message 2
	      (tformat "GSI connection lost for interface ~NF, error was ~a."
		       gsi-interface-frame?
		       reason-for-shutdown?))))
	(unless (numberp gsi-interface-countdown-timer-limit)
	  (setq gsi-interface-countdown-timer-limit
		default-gsi-interface-countdown-timer-limit))

	(when gsi-interface-structure?
	  (reclaim-icp-object-map-for-gsi-icp-interface gsi-interface-structure?)
	  (setf (gsi-connection-state icp-socket) gsi-connection-initializing)
	  (reclaim-gsi-icp-interface gsi-interface-structure?)
          (set-slot-value gsi-interface-frame? 'gsi-interface-structure nil))

	(stop-processing-on-gsi-interface gsi-interface-frame?)

	(deregister-all-icp-callbacks 'icp-connection-loss icp-socket)

	;; shutdown handshake mod -- if an activate was tried while waiting for
	;; the shutdown ack, do the activate again now!
	(cond ((get-slot-value-if-any
		 gsi-interface-frame?
		 'gsi-interface-activate-after-shutdown)
	       (set-slot-value
		 gsi-interface-frame?
		 'gsi-interface-activate-after-shutdown
		 nil)
	       
	       (activate-gsi-interface gsi-interface-frame? nil))
	      ((and (not (permanent-block-p gsi-interface-frame?))
		    (memq gsi-interface-frame? remote-gsi-interface-list))
	       (setq remote-gsi-interface-list
		     (delete-icp-element gsi-interface-frame? remote-gsi-interface-list))
	       (delete-frame gsi-interface-frame?)))))))


;;; Declaration:     gsi-interface (gsi-interface-frame)
;;; Type:	     G2 capability deactivator.
;;; Purpose:	     Shut down a GSI interface.
;;; Arguments:	     A GSI interface.
;;; Return behavior: No useful value.
;;; Users:           The capability deactivation machinery in the CAPABILITY and
;;;                  ACTIVATE modules.
;;; Prerequisites:   The def-capability-deactivator macro must be defined.
;;; Side effects:    At compile time, creates a funcallable function named
;;;                  deactivate-gsi-interface-capability.  At run
;;;                  time, this function calls handle-gsi-shut-down-connection and
;;;                  changes the gsi-interface-status of gsi-interface-frame.
;;; Non-local exits: None.
;;; Memory impact:   Modifies property lists once at launch.

;; Changed the capability deactivator for GSI interfaces to recycle
;; icp-sockets-now-initializing-gsi, in case the normal methods of
;; deletion fail somehow.  (jh, 7/11/90)

;; Changed the capability deactivator for GSI interfaces to check
;; for a corresponding interface object before reclaiming the
;; ICP object map in the GSI extension.  (jh, 7/11/90)

;; Abstracted out deactivation actions for use in the connection-loss
;; callback for GSI interface objects.  See note above.  
;; (blm, jh, & ac, 7/12/90)

;; The capability deactivator for gsi-interface capability calls
;; handle-gsi-shut-down-connection with a different number of arguments now.  See
;; note above.  (jh, 9/17/90)

(defun-void body-of-deactivate-for-gsi-interface (gsi-interface deactivatep)
  (declare (ignore deactivatep))
  (let ((interface-icp-socket?
	  (get-slot-value-if-any gsi-interface 'gsi-interface-icp-socket))
	(attributes-which-identify-a-sensor?
	  (get-slot-value-if-any gsi-interface 'identifying-attributes)))

    ;; Deinstall true value updates on the attributes which identify a sensor to
    ;; this GSI interface.
    (when attributes-which-identify-a-sensor?
      (install-true-value-updates-for-gsi
	gsi-interface
	attributes-which-identify-a-sensor?
	nil))

    (set-slot-value gsi-interface 'gsi-interface-activate-after-shutdown nil)
    
    (cond
      ((and interface-icp-socket? deleting-ui-client-interfaces-for-clear-kb)
       (stop-processing-on-gsi-interface gsi-interface))
      
      ((and interface-icp-socket?
	    (icp-connection-open-p interface-icp-socket?))

       (change-gsi-interface-status
	 gsi-interface
	 gsi-interface-waiting-for-response)

       ;; Kick off shutdown and let process-icp-sockets handle the rest of the
       ;; shutdown sequence.  The connection loss callback will be called when
       ;; the shutdown handshake terminates, or timeout, or error....  (which
       ;; callback used to be called here directly!)  -ncc, 3/17/95
       (flush-and-shutdown-icp-socket interface-icp-socket?))

      ;; Exists, but not connected.... must be connecting or disconnecting.
      ((and interface-icp-socket?
	    (icp-connection-in-progress-p interface-icp-socket?))
       
       (shutdown-icp-socket-connection
	 interface-icp-socket?
	 'deactivated-while-attempting-connection))
      
      (t
       ;; Some of the work done by the connection loss handler must be done here
       ;; when no ICP socket exists.  -ncc, 31 May 1995
       (stop-processing-on-gsi-interface gsi-interface)
       (let ((gsi-interface-structure?
	       (get-slot-value-if-any
		 gsi-interface
		 'gsi-interface-structure)))
	 (when gsi-interface-structure?
	   (reclaim-icp-object-map-for-gsi-icp-interface gsi-interface-structure?)
	   (reclaim-gsi-icp-interface gsi-interface-structure?)
	   (set-slot-value gsi-interface 'gsi-interface-structure nil)))))))

(def-class-method deactivate (gsi-interface)
  (unless (runs-while-inactive-p gsi-interface)
    (body-of-deactivate-for-gsi-interface gsi-interface t))
  (funcall-superior-method gsi-interface))

(def-class-method manually-disable (gsi-interface)
  (funcall-superior-method gsi-interface)
  (when (runs-while-inactive-p gsi-interface)
    (body-of-deactivate-for-gsi-interface gsi-interface t)))

(def-class-method note-ancestor-not-activatable (gsi-interface)
  (funcall-superior-method gsi-interface)
  (unless (active-p gsi-interface)
    (when (runs-while-inactive-p gsi-interface)
      ;; The manually-disable method handles the case where the interface itself
      ;; (as opposed to a superior) is disabled.
      (unless (manually-disabled-p gsi-interface)
	(when (gsi-icp-socket-connected-p gsi-interface)
	  (body-of-deactivate-for-gsi-interface gsi-interface t))))))

(def-class-method activate-if-possible-and-propagate (gsi-interface)
  (unless (active-p gsi-interface)
    (let ((old-status (gsi-interface-status gsi-interface))
	  (maintaining-gsi-interface-status-changed-p t)
	  (gsi-interface-status-changed-p nil))
      (funcall-superior-method gsi-interface)
      (when gsi-interface-status-changed-p
	(let ((*current-computation-frame* gsi-interface))
	  (invoke-rules-for-attribute-change-chaining
	    gsi-interface 'gsi-interface-status old-status nil))))))

;;; gsi interface frame cleanup method

;;;  This method cuts the linkage between the GSI interface object and any
;;; associated ICP socket structure when the GSI interface object is reclaimed.
;;; This is necessary because the life cycle of an ICP socket and that of its
;;; associated GSI interface frame are not synchronized; in particular, ICP
;;; sockets persist across a kb-clear, whereas frame objects like the
;;; gsi-interface do not.  Since the icp-socket needs a back-pointer to any
;;; existing GSI interface object in order to finalize connection shutdown, the
;;; icp socket and its "enclosing interface frame" must remain linked until the
;;; interface frame is reclaimed or the icp connection finishes shutting down,
;;; whichever comes first.  So, we need to cut the umbilicals in two places, in
;;; the connection loss callback called when the connection finishes shutting
;;; down, and here in this newly written cleanup method.  -ncc, 16 Jun 1995

;Note that the deactivate method is always called before the cleanup method.
;(This is true for blocks, at least.  gsi-interface is a block.)
(def-class-method cleanup (gsi-interface)
  (when (runs-while-inactive-p gsi-interface)
    (body-of-deactivate-for-gsi-interface gsi-interface t))
  (when (memq gsi-interface remote-gsi-interface-list)
    (setq remote-gsi-interface-list
	  (delete-icp-element gsi-interface remote-gsi-interface-list)))
  (unless (and deleting-ui-client-interfaces-for-clear-kb
	       (runs-while-inactive-p gsi-interface))    
    (let ((interface-icp-socket?
	    (get-slot-value-if-any gsi-interface 'gsi-interface-icp-socket)))
      (when (and interface-icp-socket?
		 (not (=f (icp-connection-state interface-icp-socket?) icp-connection-closed)))
	(let ((icp-socket-transacting-message-group nil)) ; don't ever delay the callbacks
	  (shutdown-icp-socket-connection interface-icp-socket?)))))
  (funcall-superior-method gsi-interface))


;;; Declaration:     gsi-connection-configuration
;;;                    (interface-object icp-connection-forms initializing?)
;;; Type:	     G2 slot putter.
;;; Purpose:	     Fill the gsi-connection-configuration slot of a GSI interface.
;;; Arguments:       icp-connection-forms is a list in icp-connection-configuration
;;;                  layout (see INT4 for details) describing the ICP connection to
;;;                  be made for the GSI interface interface-object.  initializing?
;;;                  is non-nil if interface-object is being created (say by
;;;                  load-kb).
;;; Return behavior: No useful value.
;;; Users:	     Slot value changing machinery in FRAMES2 and FRAMES5.
;;; Prerequisites:   The macro def-slot-putter must be defined.
;;; Side effects:    A funcallable function named put-gsi-connection-configuration
;;;                  is created at compile time.
;;; Non-local exits: None.
;;; Memory impact:   The slot putter reclaims the old value if necessary.

(def-slot-putter gsi-connection-configuration 
    (interface-object icp-connection-forms initializing-p)
  (setq icp-connection-forms
	(fix-5-0-beta-icp-connection-forms-if-necessary
	  interface-object icp-connection-forms initializing-p))
  (let ((interface-was-connected-p
	  (and (not initializing-p)
	       (or (active-p interface-object)
		   (gsi-interface-connects-while-inactive-p interface-object)))))
    (when interface-was-connected-p
      (body-of-deactivate-for-gsi-interface interface-object nil))
    (multiple-value-bind (value do-not-reclaim-old-value?)
	(put-attribute-value
	  interface-object
	  'gsi-connection-configuration
	  icp-connection-forms
	  initializing-p)
      (when interface-was-connected-p
	(activate-gsi-interface interface-object nil))
      (values value do-not-reclaim-old-value?))))



;;; `Fix-5-0-beta-icp-connection-forms-if-necessary' is called with the args to
;;; the slot putter for gsi-connection-configuration.  If this was saved out in
;;; 5.0 Beta 0, a new value for icp-connection-forms will be returned, and the
;;; old value reclaimed.  Otherwise, the icp-connection-forms value will be
;;; returned unaltered.
;;;
;;; Code is being backed out that was in from 5/31/96 to 5/10/96. Backed out per
;;; bug HQ-1337589 "GSI-connection-configuration must be text attribute,
;;; submitted by Ben Hyde.  The bug explained that this "breaks all code that
;;; maintains the gsi-interface by keeping this text in synch with a customer
;;; provided text value".
;;;
;;; Note, too, that attribute displays and other displays of this slot value in
;;; tables will be fixed up.  But since this only affects 5.0 Beta KBs, it is
;;; not worth the time and effort to attempt a fixup.  (MHD 5/15/97)

;; Obsolete comment:   (MHD 5/10/97)
;;
;; ;; MHD, 5/31/96: When we're loading a pre-5.0 KB, or a KB older than around
;; ;; today's date, we may encounter old values stored according to the format of a
;; ;; text type slot.  We no longer store a text type slot, but rather just
;; ;; directly the value.  We make the transition from the old to the new when we
;; ;; detect the old here (i.e., when initializing?, loading-kb-p, etc.).  See the
;; ;; code below for details.

(defun-simple fix-5-0-beta-icp-connection-forms-if-necessary
    (interface-object icp-connection-forms initializing-p)
  #+obsolete
  (when (and initializing-p
	     loading-kb-p
	     (consp icp-connection-forms)
	     (listp (car icp-connection-forms)))
    ;; Note: Obsolete comment. -mhd, 5/10/97
    ;; ;; We're loading the KB: The value being put is in the old (pre-5.0)
    ;; ;; (translation . text) format; we change it here to simply translation,
    ;; ;; since the slot is no longer a text type slot.  [Per change of 5/31/96,
    ;; ;; MHD]
    (setq icp-connection-forms
	  (prog1 (car icp-connection-forms)
	    (setf (car icp-connection-forms) nil)
	    (reclaim-slot-value icp-connection-forms))))
  ;; If recreating the slot from a saved KB, consider that it might have been
  ;; saved out in 5.0 Beta 0 or Beta 1 (inhouse) with the problems alluded to
  ;; above, and we want to save it out as it could have been in 4.x.  If it is
  ;; being loaded from 4.x or earlier, or 5.0 Rev. 0 or later, this should do
  ;; nothing. (MHD 5/10/97)
  #-obsolete
  (when (and initializing-p
	     loading-kb-p
	     (consp icp-connection-forms)
	     (car icp-connection-forms)
	     (symbolp (car icp-connection-forms)))
    ;; Non-null symbol in car of a list identifies this as a "translation", as
    ;; opposed to a (translation . text). Presumably, the symbol is either
    ;; localnet or tcp-ip, but we needn't check for that. (MHD 5/10/97)
    (setq icp-connection-forms
	  (let ((new-icp-connection-forms
		  (slot-value-cons
		    icp-connection-forms
		    (convert-text-string-to-text
		      (twith-output-to-text-string
			(write-gsi-host-configuration-from-slot
			  icp-connection-forms
			  interface-object))))))
	    #+development
	    (format t "~%Apparently, this was saved in 5.0 Beta.~
               ~%A change in format is now being backed out.~
               ~%You should save it out with this change.~
               ~%Change in the ~a slot of ~a: ~
               ~%  ~s ~
               ~%  => ~s~
               ~%"
		    'gsi-connection-configuration
		    interface-object
		    icp-connection-forms
		    new-icp-connection-forms)
	    new-icp-connection-forms)))
  icp-connection-forms)





;;; Declaration:     identifying-attributes
;;;                    (interface-object attribute-forms initializing?)
;;; Type:	     G2 slot putter.
;;; Purpose:	     Fill the identifying-attributes slot of a GSI interface.
;;; Arguments:       attribute-forms is a list of symbols naming attributes which
;;;                  differentiate a corresponding GSI variable accessed through GSI
;;;                  interface interface-object.  initializing?  is non-nil if
;;;                  interface-object is being created (say by load-kb).
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    define-or-configure-gsi-sensor
;;;                    activate-gsi-interface-with-connection-spec
;;;                    handle-gsi-shut-down-connection
;;; Prerequisites:   The macro def-slot-putter must be defined.
;;; Side effects:    A funcallable function named put-identifying-attributes is
;;;                  created at compile time.
;;; Non-local exits: None.
;;; Memory impact:   The slot putter reclaims the old value if necessary.
;;; Notes:           This attribute used to be called
;;;                  attributes-which-identify-a-sensor, in G2 versions 2.1 and
;;;                  earlier.

;; ac & jh, 7/17/91.  Now that we can change the text of the
;; gsi-connection-configuration system attribute, we have to reset the interface
;; for that change to take effect.  Hence, we uncommented out the
;; deactivate/activate forms above.  Whoever commented them out left no
;; explanation, so we assume the reason was efficiency, which we will ignore for
;; now.

(defun-void install-true-value-updates-for-gsi
    (gsi-interface old-attributes new-attributes)
  (let ((designation (gsi-list 'the nil '(any variable))))
    (loop for attribute in old-attributes
	  when (if (consp attribute)	;see NOTE1
		   (and (eq (car attribute) 'class-qualified-name)
			(not (member attribute new-attributes :test #'equal)))
		   (not (memq attribute new-attributes)))
	    do (setf (second designation) attribute)
	       (install-true-value-update
		 'handle-update-to-sensor-attribute
		 gsi-interface nil designation nil))
    (loop for attribute in new-attributes
	  when (if (consp attribute)	;see NOTE1
		   (and (eq (car attribute) 'class-qualified-name)
			(not (member attribute old-attributes :test #'equal)))
		   (not (memq attribute old-attributes)))
	    do (setf (second designation) attribute)
	       (install-true-value-update
		 'handle-update-to-sensor-attribute
		 gsi-interface nil nil designation))
    (reclaim-gsi-list designation)))

;; NOTE1: This is never a cons (except for NIL) because of a grammar change made
;; by ghw in system-or-user-defined-attribute-name in the 1.28 commit to
;; filters.lisp.   So even though this branch is never used, the logic was
;; clearly wrong (using a straight member test) so I went ahead and fixed it
;; anyway. -dkuznick, 2/3/00

(def-slot-putter identifying-attributes
		 (interface-object attributes initializing?)
  (when (or (active-p interface-object)
	    (and (runs-while-inactive-p interface-object)
		 (not (manually-disabled-p interface-object))))
    (install-true-value-updates-for-gsi
      interface-object
      (get-slot-value-if-any interface-object 'identifying-attributes)
      attributes))
  (put-attribute-value
    interface-object
    'identifying-attributes
    attributes
    initializing?))



;;; Declaration:     grouping-specification 
;;; 	               (interface-object grouping-forms initializing?)
;;; Type:		 G2 slot putter.
;;; Purpose:	     Fill the grouping-specification slot of a GSI interface.
;;; Arguments:       grouping-forms is a subset of identifying-attributes which will
;;;                  determine how requests for GSI variable values are grouped.
;;;                  When interface-object encounters GSI variables with identical
;;;                  values for the attributes named in grouping-specification, it
;;;                  will group requests for the values of these variables together,
;;;                  as long as the number of requests does not exceed
;;;                  max-gsi-sensors-in-a-group, currently 20.  initializing?  is
;;;                  non-nil if interface-object is being created (say by load-kb).
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (enqueue-gsi-request-for-sensor).
;;; Prerequisites:   The macro def-slot-putter must be defined.
;;; Side effects:    A funcallable function named put-grouping-specification is
;;;                  created at compile time.
;;; Non-local exits: None.
;;; Memory impact:   The slot-putter reclaims the old value if necessary.
;;; Possible bugs:   The GSI interface is not deactivated and re-activated, so the
;;;                  new grouping specification is not installed.  This could cause
;;;                  the old grouping specification be used until G2 is reset.
;;;                  There is code to deactivate and re-activate the GSI interface,
;;;                  but it is loacted in the wrong place, before the new value is
;;;                  put in the slot.  Furthermore, the code was mysteriously
;;;                  commented out without any documentation explaining why.
;;; Notes:           This attribute used to be called sensor-grouping-specification
;;;                  in G2 version 2.1 and earlier.

(def-slot-putter grouping-specification
		 (interface-object grouping-forms initializing?)
;  (when (active-p interface-object)
;      (deactivate-gsi-interface-capability interface-object)
;      (activate-gsi-interface-capability interface-object))
  (put-attribute-value 
    interface-object
    'grouping-specification
    grouping-forms initializing?))



;;; Declaration:     gsi-interface-status (gsi-interface-object status initializing?)
;;; Type:	     G2 slot putter.
;;; Purpose:	     Fill the gsi-interface-status slot of a GSI interface.
;;; Arguments:	     status is a fixnum giving the condition of gsi-interface-object.
;;;                  The following statuses are defined in GSI-COMMON:
;;;                    gsi-interface-initializing          0
;;;                    gsi-interface-waiting-for-response  1
;;;                    gsi-interface-running-ok            2
;;;                    gsi-interface-assumed-dead         -1
;;;                    gsi-interface-icp-connection-dead  -2
;;;                  initializing?  is non-nil if gsi-interface-object is being
;;;                  created (say by load-kb).
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    activate-gsi-interface-with-connection-spec
;;;                    handle-gsi-shut-down-connection
;;;                    capability deactivator for gsi-interface
;;;                    gsi-process-gsi-interfaces
;;;                    gsi-pause-data-server?
;;;                    gsi-receive-value-for-ping-request
;;;                    gsi-interface-ready-for-remote-procedure-call
;;; Prerequisites:   The macro def-slot-putter must be defined.
;;; Side effects:    A funcallable function named put-gsi-interface-status is
;;;                  created at compile time.
;;; Non-local exits: None.
;;; Memory impact:   The slot-putter reclaims the old value if necessary.
;;; Notes:           For the end-user of G2, this slot is read-only.

;;; The `slot putter for the gsi-interface-status' of an object with the
;;; gsi-interface capability is needed to invoke forward chaining.
;;; This system attribute can be referenced by the user in rules.

;; Added, cpm, 2/1/92.

(def-slot-putter gsi-interface-status
		 (gsi-interface-object status initializing?)
  (declare (ignore initializing?))
  (let ((old-status (gsi-interface-status gsi-interface-object)))
    (setf (gsi-interface-status gsi-interface-object) status)
    (invoke-rules-for-attribute-change-chaining
      gsi-interface-object 'gsi-interface-status old-status nil)
    (values status nil)))


;;; Declaration:     gsi-data-server
;;; Type:	     G2 grammar.
;;; Purpose:	     Identify the GSI dataserver in the G2 grammar.
;;; Arguments:	     None.
;;; Return behavior: N/A.
;;; Users:	     G2 grammar.
;;; Prerequisites:   None.
;;; Side effects:    The grammar categories data-server-spec and data-server-map
;;;                  include the phrase "gsi data server" after this form is
;;;                  executed at G2 launch time.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

;;; Grammar rules  to support the GSI interface configuration capability.
;;; At some point consider adding a restriction on the number of sensors
;;; that can be transmitted in a single group.

(add-grammar-rules
  `((data-server-spec ('gsi 'data 'server) gsi-data-server)
    (data-server-map ('gsi 'data 'server ) gsi-data-server)))





;;; Declaration:     gsi-data-service (gsi-variable)
;;; Type:	     G2 capability activator.
;;; Purpose:	     Initialize a GSI variable when GSI is authorized.
;;; Arguments:	     A GSI variable.
;;; Return behavior: No useful value.
;;; Users:           The capability activation machinery in the CAPABILITY and
;;;                  ACTIVATE modules.
;;; Prerequisites:   The def-capability macro must be defined.
;;; Side effects:    At compile time, creates a funcallable function named
;;;                  activate-gsi-data-service-capability.  At run time, this
;;;                  function changes only the gsi-variable-status slot of
;;;                  gsi-variable.  The capability activator for
;;;                  gsi-interface capability performs the remainder
;;;                  of the setup.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; The capability activator for GSI data service should reset the status slot
;;; of the variable.  Note that this code does not need to install updates for
;;; itself, the GSI interface configuration object has already taken care of
;;; that.  -jra & blm 5/8/90

(def-class-method activate (gsi-data-service)
  (execute-body-if-gsi-is-authorized
    (let ((sensor-status 
	    (get-slot-value-if-any gsi-data-service 'gsi-variable-status)))
      (when (not (framep sensor-status))
	(change-slot-value gsi-data-service 'gsi-variable-status #.no-error)))
    (funcall-superior-method gsi-data-service)
    gsi-data-service))




;;; Declaration:     gsi-data-service (gsi-variable)
;;; Type:	     G2 capability deactivator.
;;; Purpose:	     Shut down dataservice for a GSI variable.
;;; Arguments:	     A GSI variable.
;;; Return behavior: No useful value.
;;; Users:           The capability deactivation machinery in the CAPABILITY and
;;;                  ACTIVATE modules.
;;; Prerequisites:   The def-capability-deactivator macro must be defined.
;;; Side effects:    At compile time, creates a funcallable function named
;;;                  deactivate-gsi-data-service-capability.  At run time, this
;;;                  function does the following.  Removes pending requests for the
;;;                  value of gsi-variable.  De-installs the local gsi-sensor
;;;                  structure for the corresponding GSI variable in the remote GSI
;;;                  process.  Clears the queued-by-local-data-server flag for
;;;                  gsi-variable.  Cancels the task to request values for
;;;                  gsi-variable.  Changes the gsi-variable-status slot of
;;;                  gsi-variable.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims the gsi-sensor structure within gsi-variable.

;;; The capability deactivator for gsi-data-service shuts down data service for
;;; this variable.  (Note that this documentation and version of software
;;; supercedes the documentation below.  -jra 5/8/90)

;; The capability deactivator for gsi-data-service must, inter alia, remove the
;; true-value update demons on the complete set of sensor ID attributes.

;; Jon, what, pray tell, does "inter alia" mean?  I ain't no English major.
;; -jra 5/8/90.  "Inter alia" = "among other things".

(defun-void deactivate-dataservice-for-gsi-data-service (gsi-data-service)
  (let ((sensor-status 
	  (get-slot-value-if-any gsi-data-service 'gsi-variable-status)))
    
    (clear-pending-gsi-sensor-request gsi-data-service)
    
    (clear-queued-by-local-data-server gsi-data-service)

    (cancel-task (task-for-local-data-server? gsi-data-service))
    (cancel-task (task-to-check-variable? gsi-data-service))

    (when (not (framep sensor-status))
      (change-slot-value gsi-data-service 'gsi-variable-status #.no-error))))

(def-class-method deactivate (gsi-data-service)

  ;; doing this first avoids a leak due to freeing the sensor below and then
  ;; inadvertently creating another one down in the elaboration of the
  ;; funcall-superior-method form -ncc, 9/7/94
  (funcall-superior-method gsi-data-service)

  (deactivate-dataservice-for-gsi-data-service gsi-data-service))


;; jh, 6/11/90.  Now we cancel outstanding data-serving tasks when the sensor is
;; deactivated.  This is important when the sensor's GSI interface has been
;; deactivated but G2 is still running.  If the sensor is deleted without
;; cancelling its tasks, the deletion method will recycle them.  But a recycled
;; task remains on the scheduler's queue to cause mayhem.  Should this be
;; propagated to other data-servers, like G2DS?






;;; The capability activator and deactivators for GSI message service are only
;;; stubs.  They have no needed functionality, other than checking that GSI is
;;; authorized on activation.

;;; Declaration:     gsi-message-service (gsi-message-variable)
;;; Type:	     G2 capability activator.
;;; Purpose:	     Initialize GSI message capability for a variable.
;;; Arguments:	     A GSI message variable.
;;; Return behavior: No useful value.
;;; Users:	     The capability activation machinery in the CAPABILITY and
;;;                  ACTIVATE modules.
;;; Prerequisites:   The def-capability-activator macro must be defined.
;;; Side effects:    At compile time, creates a funcallable function named
;;;                  activate-gsi-message-service-capability.  Currently, this
;;;                  function does not need to do anything at run time.
;;; Non-local exits: None.
;;; Memory impact:   None.

(def-class-method activate (gsi-message-service)
  (execute-body-if-gsi-is-authorized
    (funcall-superior-method gsi-message-service)
    gsi-message-service))

;;; Declaration:     gsi-message-service
;;; Type:	     G2 capability deactivator.
;;; Purpose:	     Renove GSI message capability from a variable.
;;; Arguments:       A GSI message variable.
;;; Return behavior: No useful value.
;;; Users:	     The capability deactivation machinery in the CAPABILITY and
;;;                  ACTIVATE modules.
;;; Prerequisites:   The def-capability-deactivator macro must be defined.
;;; Side effects:    At compile time, creates a funcallable function named
;;;                  deactivate-gsi-message-service-capability.  Currently, this
;;;                  function does not need to do anything at run time.
;;; Non-local exits: None.
;;; Memory impact:   None.

(def-class-method deactivate (gsi-message-service)
  (funcall-superior-method gsi-message-service)
  gsi-message-service)




;;; Declaration:     clear-pending-gsi-sensor-request (gsi-variable sensor-struct)
;;; Type:	     Lisp function.
;;; Purpose:	     Removes a pending request for the value of a GSI variable.
;;; Arguments:       sensor-struct is the gsi-sensor structure which is the local
;;;                  object for the GSI corresponding variable associated with
;;;                  gsi-variable.
;;; Return behavior: No useful value.
;;; Users:           GSI internals (the capability deactivator for
;;;                  gsi-data-service).
;;; Prerequisites:   None.
;;; Side effects:    Removes all requests in the gsi-sensor-groups-header slot of
;;;                  the GSI interface for gsi-variable which request values for
;;;                  gsi-variable.
;;; Non-local exits: None.
;;; Memory impact:   Can reclaim conses and structures in the
;;;                  gsi-sensor-groups-header slot of the GSI interface for
;;;                  gsi-variable.

(defun clear-pending-gsi-sensor-request (sensor)
  (let* ((gsi-interface-name 
          (get-slot-value-if-any sensor 'gsi-interface-name))
         (gsi-interface-frame
          (if gsi-interface-name
            (get-instance-with-name-if-any 'object gsi-interface-name))))
    (when (and gsi-interface-frame
	       (active-p gsi-interface-frame)
	       (or system-is-running 
		   system-has-paused))
      (loop with sensor-groups-header = (get-slot-value-if-any 
					  gsi-interface-frame
					  'gsi-sensor-groups-header)
	    for sensor-group in (if sensor-groups-header
				    (sensor-groups-to-send-head 
				      sensor-groups-header))
	    do (loop for gsi-sensor-cons in  (sensor-group-sensors-to-send-head
					       sensor-group)
		     as gsi-sensor = (car gsi-sensor-cons)
		     as value-to-set? = (cdr gsi-sensor-cons)
		     do (when (eq sensor gsi-sensor)
			  (setf (car gsi-sensor-cons) nil)
			  (setf (cdr gsi-sensor-cons) nil)
			  (if value-to-set?
			      (reclaim-evaluation-value value-to-set?))))))))





;;; Declaration:     gsi-interface-name
;;;                   (gsi-variable gsi-interface-name initializing?)
;;; Type:	     G2 slot putter.
;;; Purpose:	     Fill the gsi-interface-name slot of a GSI variable.
;;; Arguments:       gsi-interface-name is a symbol which is the primary name of the
;;;                  GSI interface through which gsi-variable will get values.
;;;                  initializing?  is non-nil if interface-object is being created
;;;                  (say by load-kb).
;;; Return behavior: No useful value.
;;; What do you mean no useful value? This is a slot putter; it's
;;; contract is to return two values, the first of which
;;; is traditionally the value put in the slot (though this is
;;; never used), but the second return value is do-not-reclaim-old-value?
;;; Changed to return nil as second value. -alatto, 11/7/02
;;; Users:	     GSI internals:
;;;                    handle-update-to-sensor-attribute
;;;                    handle-update-to-sensor-data-type
;;;                    get-gsi-interface-for-gsi-sensor-if-any
;;;                    reconfigure-gsi-sensor-attribute
;;;                    return-gsi-extension-version
;;;                    activate-gsi-interface-with-connection-spec
;;;                    capability activator for gsi-data-service
;;;                    clear-pending-gsi-sensor-request
;;;                    gsi-deliver-messages
;;;                    gsi-begin-collecting-data
;;;                    enqueue-gsi-request-for-sensor
;;;                    gsi-stop-collecting-data
;;; Prerequisites:   None.
;;; Side effects:    Deactivates and re-activates the gsi-data-service and (if
;;;                  present) the gsi-message-service capability of gsi-variable.
;;;                  Continues to request values for the GSI variable if a task had
;;;                  been scheduled to do this before this slot putter was called.
;;; Non-local exits: None.
;;; Memory impact:   See the capability activators and deactivators for
;;;                  gsi-data-service and gsi-message-service.

;; In order for gsi to work with a transient G2 sensor, the slot putter for the
;; gsi-interface-name must first fill its gsi-interface-name slot, and only then
;; initialize it by calling gsi-begin-collecting-data.  Note that, as far as I
;; can tell, items with gsi-message service need not be variables.  (jh,
;; 3/19/90)

(def-slot-putter gsi-interface-name
		 (g2-variable gsi-interface-name initializing?)
  (let ((had-interface-p 
	  (get-slot-value-if-any g2-variable 'gsi-interface-name))
	(already-activated-p nil))
    (put-attribute-value 
      g2-variable
      'gsi-interface-name
      gsi-interface-name
      initializing?)
    (when (and (active-p g2-variable) gsi-interface-name)
      (when (gsi-data-service-p g2-variable)
	(let ((data-collection-interval
		(get-slot-value g2-variable 'gsi-collection-interval)))
	  (when had-interface-p
	    (suspend-activation g2-variable))
	  (resume-activation g2-variable)
	  (setq already-activated-p t)
	  (when (with-temporary-gensym-float-creation
		    gsi-interface-name
		  (evaluation-quantity-> data-collection-interval 0))
	    (gsi-begin-collecting-data 
	      g2-variable 
	      data-collection-interval))))
      (unless already-activated-p
	(when (gsi-message-service-p g2-variable)
	  (when had-interface-p
	    (suspend-activation g2-variable))
	  (resume-activation g2-variable)
	  (values gsi-interface-name nil))))))





;;; Declaration:     gsi-interface-name (parse-result)
;;; Type:	     G2 slot value compiler.
;;; Purpose:	     Get the GSI interface of a GSI variable from the user.
;;; Arguments:	     parse-result is a symbol.
;;; Return behavior: If parse result is the symbol none, nil is returned.
;;;                  Otherwise, parse-result itself is returned.
;;; Users:	     G2 editor.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; The slot value compiler for g2-interface-name expects parse-result to be
;;; either the symbol NONE or some other symbol.  If parse-result is NONE, nil
;;; is returned; otherwise parse-result is returned.

(def-slot-value-compiler gsi-interface-name (parse-result)
  (cond ((eq parse-result 'none) nil)
	(t parse-result)))





;;; Declaration:     gsi-deliver-messages
;;;                    (message-or-copy
;;;                     urgency? 
;;;                     duration? 
;;;                     inference-frame
;;; 	                destination)
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Deliver messages to the remote GSI process.
;;; Arguments:       > message-or-copy is a text-string containing the message.
;;;                  > urgency? is ignored.
;;;                  > duration?  is the duration in seconds a local logbook message
;;;                    should last, if this function is unable to transmit this
;;;                    message to the remote GSI process.  If this function can
;;;                    communicate with the remote GSI process, this argument is the
;;;                    index of the corresponding GSI variable which is to receive
;;;                    the message.
;;;                  > inference-frame 
;;;                    is the frame "reposnsible" for posting this message locally.
;;; 	             > destination is the place the local message should be posted.
;;;                    This is typically the logbook, though it can be a
;;;                    kb-workspace.
;;; Return behavior: No useful value.
;;; Users:	     The GSI dataserver.
;;; Prerequisites:   None.
;;; Side effects:    Can post messages on the logbook.  Can transmit the ICP message
;;;                  write-user-message-string.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims message-or-copy, whether the message is posted locally
;;;                  or transmitted to the remote GSI process.

(defun-simple gsi-deliver-messages 
	      (message-or-copy urgency? duration? inference-frame destination)
  (let* ((gsi-interface-name 
	   (get-slot-value-if-any destination 'gsi-interface-name))
         (gsi-interface-frame 
	   (if gsi-interface-name
	       (get-instance-with-name-if-any 'object gsi-interface-name)))
         (interface-icp-socket
	   (if gsi-interface-frame
	       (get-slot-value-if-any
		 gsi-interface-frame
		 'gsi-interface-icp-socket)))
	 (gsi-interface-struct
	   (if gsi-interface-frame
	       (get-slot-value-if-any
		 gsi-interface-frame
		 'gsi-interface-structure))))
    (if (and gsi-interface-frame 
             interface-icp-socket
             (or (active-p gsi-interface-frame)
		 (gsi-interface-connects-while-inactive-p gsi-interface-frame))
             (icp-connection-open-p interface-icp-socket)
	     (not (gsi-interface-timed-out-p gsi-interface-struct)))
	(writing-icp-message-group
	    ((icp-output-port interface-icp-socket))
	  (send-icp-write-user-message-string message-or-copy urgency? duration? nil)
	  (reclaim-text-string message-or-copy))
	(post-on-message-board 
	  message-or-copy
	  urgency? duration? 
	  inference-frame destination))))







;;; Declaration:     gsi-data-server
;;; Type:	     G2 data server.
;;; Purpose:	     Manage GSI dataservice.
;;; Arguments:       > function-to-collect-one-shot-data  : gsi-collect-one-shot-data
;;; 	             > function-to-begin-collecting-data  : gsi-begin-collecting-data
;;; 	             > function-to-stop-collecting-data   : gsi-stop-collecting-data
;;; 	             > function-to-accept-data            : gsi-process-gsi-interfaces
;;; 	             > function-to-initialize-data-server : gsi-initialize-data-server
;;; 	             > function-to-set-external-variable  : gsi-set-external-variable
;;; 	             > function-to-shut-down-data-server? : gsi-shut-down-data-server?
;;;                  > function-to-deliver-messages       : gsi-deliver-messages
;;; 	             > function-to-pause-data-server?     : gsi-pause-data-server?
;;; 	             > function-to-resume-data-server?    : gsi-resume-data-server?
;;; Return behavior: No useful value.
;;; Users:	     Dataservice machinery.
;;; Prerequisites:   The def-data-server macro must be defined.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Adds internal properties once, at launch time.

(def-data-server 'gsi-data-server
  'gsi-collect-one-shot-data
  'gsi-begin-collecting-data
  'gsi-stop-collecting-data
  'gsi-process-gsi-interfaces
  t						;server-is-in-use			
  'gsi-initialize-data-server
  'gsi-set-external-variable
  'gsi-shut-down-data-server?
  'gsi-deliver-messages
  'gsi-pause-data-server?
  'gsi-resume-data-server?
  'gsi-requests-accept-data-calls-p
  'gsi-start-data-server?
  'gsi-reset-data-server?)





;;; Declaration:     gsi-process-gsi-interfaces ()
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Accept data from the remote GSI process.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     function-to-accept-data machinery in CYCLES.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    Can modify the the gsi-interface structure inside each GSI
;;;                  interface in list-of-all-gsi-interfaces-head.  Can modify the
;;;                  gsi-interface-status slot of a GSI interface.  Can shut down an
;;;                  ICP connection if timed out.  Can post messages in logbook.
;;;                  Sends the ICP message send-data-values-if-any.  For further
;;;                  side effects, see process-requests-for-gsi-interfaces.
;;; Non-local exits: None.
;;; Memory impact:   Enters a temporary bignum context in order to transmit a
;;;                  timestamp in send-data-values-if-any.  ICP can allocate memory
;;;                  when the message send-data-values-if-any is sent.

(defun-simple gsi-process-gsi-interfaces ()
  (with-temporary-gensym-float-creation
    gsi-process-gsi-interfaces
    (loop for list-of-all-gsi-interfaces--tail = list-of-all-gsi-interfaces
					       then next-list-of-all-gsi-interfaces--tail
	  while list-of-all-gsi-interfaces--tail
	  for gsi-interface-frame = (car list-of-all-gsi-interfaces--tail)
	  for next-list-of-all-gsi-interfaces--tail = (cdr list-of-all-gsi-interfaces--tail)
	  as icp-socket? = (get-slot-value-if-any
			     gsi-interface-frame
			     'gsi-interface-icp-socket)
	  do 
      (when (and (active-p gsi-interface-frame)
		 (get-slot-value-if-any 
		   gsi-interface-frame 
		   'poll-external-system-for-data)
		 icp-socket?
		 (=f (icp-connection-state icp-socket?) icp-connection-running))
	(let* ((gsi-interface-structure?
		 (get-slot-value-if-any
		   gsi-interface-frame
		   'gsi-interface-structure))
	       (gsi-interface-countdown-timer-limit?
		 (get-slot-value-if-any 
		   gsi-interface-frame 
		   'interface-timeout-period))
	       (countdown-timer-value?
		 (and gsi-interface-structure?
		      (gsi-interface-countdown-timer
			gsi-interface-structure?))))
	  (when (not (numberp gsi-interface-countdown-timer-limit?))
	    (setq gsi-interface-countdown-timer-limit?
		  default-gsi-interface-countdown-timer-limit))
	  (cond ((and gsi-interface-structure?
		      (gsi-interface-waiting-for-response-p
			gsi-interface-structure?)
		      countdown-timer-value?
		      (>f (fixnum-time-difference (get-fixnum-time)
						  countdown-timer-value?)
			  (fixnum-time-interval
			    (*f 1000 gsi-interface-countdown-timer-limit?))))
		 (change-gsi-interface-status
		   gsi-interface-frame
		   gsi-interface-assumed-dead)
		 (write-warning-message 3
		   (tformat "GSI interface ~NF has timed out." gsi-interface-frame))
		 (setf (gsi-interface-waiting-for-response-p gsi-interface-structure?) nil)
		 (setf (gsi-interface-timed-out-p gsi-interface-structure?) t))
		((and gsi-interface-structure?
		      (not (gsi-interface-waiting-for-response-p gsi-interface-structure?))
		      (not (gsi-interface-timed-out-p gsi-interface-structure?)))
		 (let ((polling-interval (interval-to-poll-external-system gsi-interface-frame))
		       (time-of-next-poll (time-of-next-poll gsi-interface-frame)))
		   (when (or (not (fixnump polling-interval))
			     (not (managed-float-p time-of-next-poll))
			     (>=e (managed-float-value (clock-get current-g2-time))
				  (managed-float-value time-of-next-poll)))
		     (when (fixnump polling-interval)
		       (unless time-of-next-poll
			 (setq time-of-next-poll (allocate-managed-float 0.0))
			 (setf (time-of-next-poll gsi-interface-frame) time-of-next-poll))
		       (setf (managed-float-value time-of-next-poll)
			     (g2-future-interval polling-interval)))
		     ;; sadly, we must always send the timestamp in the
		     ;; six integer format here.  We are pinned by the use
		     ;; of send-data-values-if-any before version info is
		     ;; available.  This blocks version-bifurcation in the
		     ;; ICP reader and writer for gsi-timestamps, and so
		     ;; these cannot be used in this message. -ncc, 8/8/94
		     (with-temporary-bignum-creation
		       (multiple-value-bind 
			   (second minute hour day month year)
			   (get-decoded-real-time)
			 (writing-icp-message-group
			     ((icp-output-port icp-socket?))
			   (send-icp-send-data-values-if-any-1
			     gsi-interface-structure?
			     year month day hour minute second))))
		     (setf (gsi-interface-waiting-for-response-p
			     gsi-interface-structure?)
			   t)
		     (setf (gsi-interface-countdown-timer
			     gsi-interface-structure?)
			   (get-fixnum-time)))))))))
    (process-requests-for-gsi-interfaces)))

(defun update-gsi-interface-countdown-timer (icp-socket)
  (let ((gsi-interface-frame? (enclosing-interface-frame? icp-socket)))
    (when (and gsi-interface-frame?
	       (frame-has-not-been-reprocessed-p
		 gsi-interface-frame?
		 (enclosing-interface-frame-serial-number icp-socket)))
      (let ((gsi-interface-structure?
	      (get-slot-value-if-any gsi-interface-frame?
				     'gsi-interface-structure)))
	(when (and gsi-interface-structure?
		   (gsi-interface-countdown-timer gsi-interface-structure?))
	  (setf (gsi-interface-countdown-timer gsi-interface-structure?)
		(get-fixnum-time)))))))



;;;; Functions for pausing and resuming data service.

;;; Declaration:     gsi-pause-data-server? ()
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Informs the remote GSI process that G2 has paused.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     function-to-pause-data-server? machinery in CYCLES.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    Sends the ICP message pause-data-server.
;;; Non-local exits: None.
;;; Memory impact:   ICP can allocate memory when the message pause-data-server is
;;;                  sent.

(defun-simple gsi-pause-data-server? ()
  (loop for gsi-interface in list-of-all-gsi-interfaces
        as icp-socket = (if gsi-interface
			    (get-slot-value-if-any 
			      gsi-interface 
			      'gsi-interface-icp-socket))
        as interface-structure = (if gsi-interface
				     (get-slot-value-if-any 
				       gsi-interface 
				       'gsi-interface-structure))
        do (when (and gsi-interface 
                      (active-p gsi-interface)
                      icp-socket
                      (icp-connection-open-p icp-socket))
             (writing-icp-message-group
		 ((icp-output-port icp-socket))
	       (send-icp-pause-data-server)))))



;;; Declaration:     gsi-resume-data-server? ()
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Informs the remote process that G2 has resumed.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     function-to-resume-data-server? machinery in CYCLES.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    Sends the ICP message pause-data-server.
;;; Non-local exits: None.
;;; Memory impact:   ICP can allocate memory when the message resume-data-server is
;;;                  sent.

(defun-simple gsi-resume-data-server? ()
  (loop for gsi-interface in list-of-all-gsi-interfaces
        as icp-socket = (if gsi-interface
			    (get-slot-value-if-any 
			      gsi-interface
			      'gsi-interface-icp-socket))
        do (when (and gsi-interface
		      (active-p gsi-interface)
		      icp-socket
		      (icp-connection-open-p icp-socket))
	     (writing-icp-message-group ((icp-output-port icp-socket))
	       (send-icp-resume-data-server)))))

;;; New analogues of the above for notifying servers of
;;; start and reset.

(defun-simple gsi-start-data-server? ()
  (loop for gsi-interface in list-of-all-gsi-interfaces
        as icp-socket = (if gsi-interface
			    (get-slot-value-if-any 
			      gsi-interface
			      'gsi-interface-icp-socket))
        do
    (with-appropriate-version-for-output (data-servers-can-run-while-inactive-version
					   icp-socket)
      (when (and gsi-interface
		 (runnable-p gsi-interface)
		 icp-socket
		 (icp-connection-open-p icp-socket))
	(writing-icp-message-group ((icp-output-port icp-socket))
	  (send-icp-start-data-server))))))
  
(defun-simple gsi-reset-data-server? ()
  (loop for gsi-interface in list-of-all-gsi-interfaces
        as icp-socket = (if gsi-interface
			    (get-slot-value-if-any 
			      gsi-interface
			      'gsi-interface-icp-socket))
        do
    (with-appropriate-version-for-output (data-servers-can-run-while-inactive-version
					   icp-socket)
      (when (and gsi-interface
		 (runnable-p gsi-interface)
		 icp-socket
		 (icp-connection-open-p icp-socket))
	(writing-icp-message-group ((icp-output-port icp-socket))
	  (send-icp-reset-data-server))))))




;;; Declaration:     gsi-shut-down-data-server? ()
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Performs tasks to help shut down GSI dataservice.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     function-to-shut-down-data-server? machinery in CYCLES.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    Empties the queue list-of-all-gsi-interfaces-head.  Cancels
;;;                  task-to-process-gsi-values and task-to-process-gsi-interfaces.
;;;                  Note that this function does not send the ICP message
;;;                  shut-down-data-server as might be expected.  Instead,
;;;                  handle-gsi-shut-down-connection sends this message.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims gsi-conses in list-of-all-gsi-interfaces-head.
;;; Notes:           This function does not do much because the capability
;;;                  deactivators for gsi-interface handle most of the shutdown
;;;                  chores.

;;; GSI has little to do for starting up or shutting down the remote processes
;;; because the capability activator/deactivators do most of the connection
;;; initializing and shutdown work.

(defun gsi-shut-down-data-server? ()
  (loop with new-list = '()
	for interface in list-of-all-gsi-interfaces
	when (runs-while-inactive-p interface)
	  do
	    (gsi-push interface new-list)
	finally
	  (reclaim-gsi-list list-of-all-gsi-interfaces)
	  (setq list-of-all-gsi-interfaces new-list))
  (loop as interface? = (dequeue gsi-interfaces-to-process-head
	                         gsi-interfaces-to-process-tail
				 reclaim-gsi-cons)
	until (null interface?))
  (process-gsi-sensor-values nil)
  (cancel-task task-to-process-gsi-values)
  (cancel-task task-to-process-gsi-interfaces) ;Added.  jh, 5/22/91.
  )





;;; The function `gsi-requests-accept-data-calls-p' determines whether or not
;;; GSI could need to have accept-data called for it.  Note that if anything
;;; changes the value of this function from NIL to T (say in the activate method
;;; for gsi-inteface), then the function schedule-data-server-accept-data-calls
;;; must be called to ensure the restart of accept data calls in general.

(defun gsi-requests-accept-data-calls-p ()
  (loop for interface being each class-instance of 'gsi-interface
	thereis (active-p interface)))


;;; Declaration:     gsi-initialize-data-server ()
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Initialize GSI data service.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     function-to-initialize-data-server machinery in CYCLES.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.
;;; Notes:           This function does nothing because the capability activators
;;;                  for gsi-interface and gsi-data-service do the
;;;                  work.

(defun gsi-initialize-data-server ())





;;; Gsi-collect-one-shot-data and gsi-set-external-variable check for proper GSI
;;; configuration, then set up the sensor data request in the appropriate output
;;; queue associated with the GSI interface configured for this sensor.

;;; Declaration:     gsi-collect-one-shot-data (gsi-variable)
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Collect a single value for a GSI variable.
;;; Arguments:	     A GSI variable.
;;; Return behavior: No useful value.
;;; Users:	     obtain-newer-value machinery in VARIABLES.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    See enqueue-gsi-request-for-sensor.
;;; Non-local exits: None.
;;; Memory impact:   See enqueue-gsi-request-for-sensor.

(defun gsi-collect-one-shot-data (sensor)
  (if (gsi-data-service-p sensor)
      (enqueue-gsi-request-for-sensor
	sensor no-value-to-set
	collect-one-now)
      (write-warning-message 
       2
       (tformat
        "Sensor ~NF is not configured for GSI"
        sensor))))



;;; Declaration:     gsi-set-external-variable (gsi-variable value data-type)
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Set the value of a corresponding GSI variable.
;;; Arguments:       gsi-variable is a GSI variable, value is a raw value (i.e., not
;;;                  a temporary constant or evaluation value), and data-type is a
;;;                  symbol naming the subtype of variable (one of truth-value,
;;;                  integer, float, number, symbol, text).  If data-type is nil,
;;;                  the type number is used.
;;; Return behavior: No useful value.
;;; Users:           The set action in ACTIONS and the set funcalled instruction in
;;;                  STACK-ACTS.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    See enqueue-gsi-request-for-sensor.
;;; Non-local exits: None.
;;; Memory impact:   See enqueue-gsi-request-for-sensor.

(defun gsi-set-external-variable (sensor value data-type)
  (declare (ignore data-type))
  (if (gsi-data-service-p sensor)
      (enqueue-gsi-request-for-sensor 
	sensor
	(copy-evaluation-value value)
	collect-one-now)
      (write-warning-message 
       2
       (tformat "Sensor ~NF is not configured for GSI"
        sensor))))





;;; Declaration:     gsi-begin-collecting-data (gsi-variable collection-interval)
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Get the first value for a GSI variable.
;;; Arguments:       gsi-variable is a GSI variable, collection-interval is a
;;;                  slot-value-number giving the interval at which requests for
;;;                  values will happen.  If collection interval is 0, only one
;;;                  request will be made.
;;; Return behavior: No useful value.
;;; Users:	     initialize-items-needing-initialization in ACTIVATE.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    See enqueue-gsi-request-for-sensor.
;;; Non-local exits: None.
;;; Memory impact:   See enqueue-gsi-request-for-sensor.

;; Gsi-begin-collecting-data is called when a G2 sensor is initialized.  This
;; function now refrains from producing a spurious "No gsi interface" message
;; for a transient sensor which hasn't yet received a value for its
;; gsi-interface-name-slot.  (jh, 3/19/90)

(defun gsi-begin-collecting-data (sensor collection-interval)
  (unless (gsi-data-service-p sensor)
    (warning-message 2 "Sensor ~NF is not configured for GSI" sensor)
    (return-from gsi-begin-collecting-data nil))
  (when (get-slot-value-if-any sensor 'gsi-interface-name)
    (enqueue-gsi-request-for-sensor 
      sensor no-value-to-set collection-interval))
  (let ((old-collection-interval
	  (get-slot-value sensor 'gsi-collection-interval)))
    (unless (eql old-collection-interval collection-interval)
      (reclaim-evaluation-quantity old-collection-interval)
      (set-slot-value
	sensor
	'gsi-collection-interval
	(copy-evaluation-quantity collection-interval))
      (set-slot-value
	sensor
	'gsi-internal-collection-interval
	(copy-evaluation-quantity collection-interval)))))




;;; Notes: 

;;; By default the GSI requests for reading and writing values will be grouped
;;; separately.

;;; The value-to-set?  and the interval-for-collection?  args to
;;; enqueue-gsi-request-for-sensor are mutually exclusive.





;;; Declaration:     enqueue-gsi-request-for-sensor
;;;                    (gsi-variable value-to-set? collection-interval)
;;; Type:	     Lisp function.
;;; Purpose:	     Enqueue a request for the value of a GSI variable.
;;; Arguments:	     > gsi-variable is the GSI variable requesting a value.
;;;                  > value-to-set?  is a temportaty-constant structure containing
;;;                    a new value if the corresponding GSI variable is to receive a
;;;                    value, nil otherwise.
;;;                  > collection-interval is a fixnum giving the interval at which
;;;                    requests for values will happen.  If collection interval is
;;;                    0, only one request will be made.  If collection-interval is
;;;                    -1, requests are cancelled for gsi-variable.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    gsi-collect-one-shot-data
;;;                    gsi-set-external-variable
;;;                    gsi-begin-collecting-data
;;;                    gsi-stop-collecting-data
;;; Prerequisites:   None.
;;; Side effects:    Can post logbook messages.  Can schedule a task in the
;;;                  task-for-local-data-server?  of gsi-variable.  Can modify the
;;;                  queued-by-local-data-server flag for gsi-variable.  Can modify
;;;                  the gsi-collection-interval.  For remaining side effects, see
;;;                  add-sensor-to-group-if-it-fits and
;;;                  put-sensor-in-new-sensor-group.
;;; Non-local exits: None.
;;; Memory impact:   ...
;;; Possible bugs:   See gsi-receive-value-for-gsi-sensor.

;;; Enqueue-gsi-request-for-sensor tries to group sensor requests according to
;;; the grouping criterion specified for the particular GSI interface.  If an
;;; existing group is found the sensor is added else a new group is started.

(defun-simple enqueue-gsi-request-for-sensor
    (sensor value-to-set? collection-interval)
  (let* ((gsi-interface-name?
	   (get-slot-value-if-any sensor 'gsi-interface-name))
	 (gsi-interface? 
	   (and gsi-interface-name?
		(get-instance-with-name-if-any 'object gsi-interface-name?)))
	 (raw-sensor-grouping-specification
	   (if (and gsi-interface? (gsi-interface-p gsi-interface?))
	       (get-slot-value-if-any gsi-interface? 'grouping-specification)
	       nil))
	 (sensor-grouping-specification
	   (if (eq 'no-grouping raw-sensor-grouping-specification)
	       nil
	       raw-sensor-grouping-specification))
	 (gsi-interface-icp-socket?
	   (and gsi-interface?
	       (get-slot-value-if-any
		 gsi-interface?
		 'gsi-interface-icp-socket)))
         (gsi-interface-structure ;known non-nil by the time it is used
	   (and gsi-interface?
		(get-slot-value-if-any
		  gsi-interface?
		  'gsi-interface-structure))))
    (with-temporary-gensym-float-creation enqueue-gsi-request-for-sensor
      (cond
	((null gsi-interface?)
	 (cond
	   (value-to-set?
	    (if gsi-interface-name?
		(warning-message 2
		    "The GSI data server could not set a value ~
                       for variable ~NF because ~a does not exist."
		  sensor
		  gsi-interface-name?)
		(warning-message 2
		    "The GSI data server could not set a value ~
                       for variable ~NF because no GSI interface was specified."
		  sensor))
	    (reclaim-evaluation-value value-to-set?))
	   (t (unless (value-of-variable-is-current sensor)
		(task-to-detect-failure sensor))
	      (write-warning-message 2
		(tformat
		  "No GSI interface for sensor ~NF"
		  sensor)))))
	((not (active-p gsi-interface?))
	 (cond
	   ((null value-to-set?)
	    (unless (value-of-variable-is-current sensor)
	      (task-to-detect-failure sensor))
	    (cancel-task
	      (task-for-local-data-server? sensor))
	    ;; jh, 10/12/95.  If the interface is inactive, we probe for
	    ;; reactivation at a constant 1 second interval regardless of the
	    ;; collection interval of the variable.  There appears to be similar
	    ;; code (with a similar paucity of documentation) in G2DS to
	    ;; accomplish the same purpose, so at least there is a precedent for
	    ;; this behavior.  But we might want to consider limiting the number
	    ;; of retries, as well as making the retry interval reflect the
	    ;; collection interval.
	    (when (evaluation-quantity-> collection-interval 0)
	      (with-future-scheduling
		  ((task-for-local-data-server? sensor)
		   2
		   (g2-future-interval 1))
		(enqueue-gsi-request-for-sensor
		  sensor
		  value-to-set?
		  collection-interval))))
	   (t (reclaim-evaluation-value value-to-set?)
	      (warning-message 2
		  "The GSI data server could not set a value for variable ~NF ~
                   because ~NF is not active."
		sensor
		gsi-interface?))))
	((null gsi-interface-icp-socket?)
	 (cond
	   (value-to-set?
	    (reclaim-evaluation-value value-to-set?)
	    (warning-message 2
		"The GSI data server could not set a value for variable ~NF ~
                 because ~NF failed to make an ICP connection."
	      sensor
	      gsi-interface?))
	   (t (unless (value-of-variable-is-current sensor)
		(task-to-detect-failure sensor)))))
	((or (/=f (gsi-connection-state gsi-interface-icp-socket?) gsi-connection-established)
	     (/=f (icp-connection-state gsi-interface-icp-socket?) icp-connection-running))
	 (cond (value-to-set?
		(reclaim-evaluation-value value-to-set?)
		(warning-message 2
		    "The GSI data server ~
                     could not set a value for variable ~NF ~
                     because ~NF is not connected."
		  sensor
		  gsi-interface?))
	       (t (unless (or (value-of-variable-is-current sensor)
			      (icp-connection-open-p gsi-interface-icp-socket?) ; awaiting initial ping
			      (=f (icp-connection-state gsi-interface-icp-socket?)
				  icp-connection-awaiting-acknowledgement))
		    (task-to-detect-failure sensor)))))
	(;; Single shot and a value is already on the way.
	 (and (queued-by-local-data-server-p sensor)	
	      (evaluation-quantity-= collection-interval 0)
	      (null value-to-set?)))
	((and value-to-set?
	      (gsi-interface-timed-out-p gsi-interface-structure))
	 (reclaim-evaluation-value value-to-set?)
	 (warning-message 2
	     "The GSI data server could not set a value for variable ~NF ~
              because the ICP connection for ~NF has timed out."
	   sensor
	   gsi-interface?))
	(t (when (failed-p sensor)
	     (clear-queued-by-local-data-server sensor)
	     (setq collection-interval
		   (get-slot-value sensor 'gsi-collection-interval)))
	   ;; Reschedule local collection task
	   (when (and (evaluation-quantity-> collection-interval 0) 
		      (not (get-slot-value-if-any 
			     gsi-interface? 
			     'external-system-has-a-scheduler)))
	     (with-future-scheduling
		 ((task-for-local-data-server? sensor)
		  ;; This task is high priority.
		  1
		  ;; Start cycle at next interval.
		  (g2-evaluation-value-to-future-interval collection-interval)
		  ;; Repeat at this interval.
		  (if (fixnump collection-interval)
		      (coerce-fixnum-to-gensym-float collection-interval)
		      (managed-float-value collection-interval)))
	       (enqueue-gsi-request-for-sensor
		 sensor
		 no-value-to-set
		 collect-one-now)))
	   (when (or value-to-set?
		     (and (not (queued-by-local-data-server-p sensor))
			  (null value-to-set?))
		     ;; Reseting external schedule
		     (and (evaluation-quantity-/= collection-interval 0)
			  (get-slot-value-if-any 
			    gsi-interface?
			    'external-system-has-a-scheduler)))
	     (when (null value-to-set?)
	       (set-queued-by-local-data-server sensor))
	     (loop with sensor-groups-header
		     = (get-slot-value-if-any
			 gsi-interface?
			 'gsi-sensor-groups-header)
		   with existing-sensor-groups
		     = (sensor-groups-to-send-head sensor-groups-header)
		   for gsi-sensor-group
		       in existing-sensor-groups
		   as sensor-put-in-existing-group?
		      = (add-sensor-to-group-if-it-fits
			  sensor-grouping-specification
			  sensor
			  value-to-set?
			  collection-interval
			  gsi-sensor-group)
		   until sensor-put-in-existing-group?
		   finally
		     (unless sensor-put-in-existing-group?
		       (unless (sensor-groups-to-send-head sensor-groups-header)
			 (enqueue gsi-interface?
				  gsi-interfaces-to-process-head
				  gsi-interfaces-to-process-tail
				  gsi-cons)
			 ;; jh & jra, 6/24/92.  Ensure that the output queue is
			 ;; always filled with the turnaround in the following
			 ;; form.  It improves latency.
			 (unless (schedule-task-in-place-p
				   task-to-process-gsi-interfaces)
			   (with-current-scheduling
			       (task-to-process-gsi-interfaces
				 (priority-of-data-service
				   data-server-parameters))
			     (process-requests-for-gsi-interfaces))))
		       (put-sensor-in-new-sensor-group
			 sensor-groups-header 
			 sensor-grouping-specification
			 sensor
			 value-to-set?
			 collection-interval)))))))))





;;; Declaration:     add-sensor-to-group-if-it-fits
;;;                    (grouping-specification 
;;;                     gsi-variable
;;;                     value-to-set? 
;;;                     interval-for-collection
;;;                     sensor-group)
;;; Type:	     Lisp function.
;;; Purpose:         Add a request for a GSI variable to an existing group of
;;;                  requests.
;;; Arguments:       > gsi-variable, value-to-set?, and collection-interval are
;;;                    passed unchanged by enqueue-gsi-request-for-sensor (q.v.).
;;;                  > grouping-specification is a gsi-list of temporary values
;;;                    giving the values of the identifyomg-attributes of
;;;                    gsi-variable.
;;;                  > sensor-group is a sensor-group structure.  This function
;;;                    checks this structure to see if gsi-variable belongs in that
;;;                    group of GSI variables.  (See the grouping-specification slot
;;;                    putter for details on the algorithm used.)
;;; Return behavior: Returns non-nil if a request for the value of gsi-variable was
;;;                  added to sensor-group, nil otherwise.
;;; Users:	     GSI internals (enqueue-gsi-request-for-sensor).
;;; Prerequisites:   None.
;;; Side effects:    Can modify sensor-group to include gsi-variable.
;;; Non-local exits: None.
;;; Memory impact:   Can allocate a gsi-cons to store gsi-variable in sensor-group.

(defun add-sensor-to-group-if-it-fits (grouping-specification 
                                       sensor 
                                       value-to-set? 
                                       interval-for-collection
                                       sensor-group)
  (and (<f (sensor-group-count sensor-group)
	   max-gsi-sensors-in-a-group)

       (if value-to-set?       ; check to see of a get or set operation.
	   (sensor-group-setting-values? sensor-group)
	   (null (sensor-group-setting-values? sensor-group)))

       ;; Negative collection intervals are a signal to stop collection.
       ;; Should follow established abstraction.
       (if (evaluation-quantity-< interval-for-collection 0) 
	   (evaluation-quantity-<
	     (sensor-group-collection-interval sensor-group)
	     0)
	   (evaluation-quantity->=
	     (sensor-group-collection-interval sensor-group)
	     0))

       (loop with parameter-values-match? = t
	     for parameter-name in grouping-specification
	     for group-parameter in (sensor-group-parameters sensor-group)
	     as sensor-attribute
		= (gsi-item-attribute-value parameter-name sensor) 
	     do (setq parameter-values-match? 
		      (or (and (null sensor-attribute)
			       (null group-parameter))
			  (and (evaluation-value-p group-parameter)
			       (evaluation-value-p sensor-attribute)
			       (evaluation-value-eql group-parameter
						     sensor-attribute))))
		(if (evaluation-value-p sensor-attribute)
		    (reclaim-evaluation-value sensor-attribute))
	     until (null parameter-values-match?)
	     finally
	       (when parameter-values-match?
		 (let ((gsi-sensor 
			 (get-or-make-gsi-sensor sensor interval-for-collection)))	
		   (incff (sensor-group-count sensor-group))
		   (enqueue 
		     (gsi-cons gsi-sensor value-to-set?)
		     (sensor-group-sensors-to-send-head sensor-group)
		     (sensor-group-sensors-to-send-tail sensor-group)
		     gsi-cons))
		 (return parameter-values-match?)))))





;;; Declaration:     put-sensor-in-new-sensor-group
;;;                    (sensor-groups-header
;;;                     grouping-specification
;;;                     gsi-variable
;;;                     value-to-set? 
;;;                     interval-for-collection)
;;; Type:	     Lisp function.
;;; Purpose:	     Create a new group of requests for values of GSI variables.
;;; Arguments:	     > sensor-groups-header is a sensor-groups-header structure,
;;;                    containing all groups of GSI variables using a single GSI
;;;                    interface.
;;;                  > grouping-specification is a list of symbols naming the
;;;                    identifying-attributes by which gsi-variable is to be grouped
;;;                    (See the grouping-specification slot for details on the
;;;                    algorithm used).
;;;                  > gsi-variable, value-to-set?, and collection-interval are
;;;                    passed unchanged by enqueue-gsi-request-for-sensor (q.v.).
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (enqueue-gsi-request-for-sensor).
;;; Prerequisites:   None.
;;; Side effects:    Modifies sensor-groups-header.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a gsi-cons and a sensor-group structure for the
;;;                  new group of GSI variables.
;;; Possible bugs:   See gsi-receive-value-for-gsi-sensor.

;; Added check for cancel-collection in put-sensor-in-new-sensor-group.  It was
;; already in add-sensor-to-sensor-group-if-it-fits.  The lack was causing GSI
;; to lose the first sensor in the sensor group when the "external system has a
;; scheduler" attribute was "yes" and the workspace was disabled and re-enabled.
;; (jh, 7/13/90)

(defun put-sensor-in-new-sensor-group (sensor-groups-header
                                       grouping-specification
                                       sensor 
                                       value-to-set? 
                                       interval-for-collection)
  (let* ((sensor-group-parameters
	   (loop with sensor-attribute-list-head
		 with sensor-attribute-list-tail
		 for parameter-name in grouping-specification
		 as sensor-attribute
		    = (gsi-item-attribute-value parameter-name sensor)
		 do (enqueue-1 sensor-attribute
			     sensor-attribute-list-head
			     sensor-attribute-list-tail
			     gsi-cons)
		 finally (return sensor-attribute-list-head)))
         (sensor-group 
	   (make-sensor-group 
	     sensor-group-parameters
	     (if value-to-set? t)
	     interval-for-collection))
	 (gsi-sensor 
	   (get-or-make-gsi-sensor sensor interval-for-collection)))

    (enqueue (gsi-cons gsi-sensor value-to-set?)
             (sensor-group-sensors-to-send-head sensor-group)
             (sensor-group-sensors-to-send-tail sensor-group)
             gsi-cons)
    (enqueue  sensor-group
              (sensor-groups-to-send-head sensor-groups-header)
              (sensor-groups-to-send-tail sensor-groups-header)
              gsi-cons)))





;;; Declaration:     gsi-stop-collecting-data (gsi-variable)
;;; Type:	     GSI dataserver function.
;;; Purpose:	     Shut down collecting values for a GSI variable.
;;; Arguments:	     A GSI variable.
;;; Return behavior: No useful value.
;;; Users:	     deactivate-subclass-of-entity machinery in VARIABLES.
;;; Prerequisites:   The def-data-server form for gsi-data-server must be executed.
;;; Side effects:    Can post logbook messages.  Clears the
;;;                  queued-by-local-data-server flag of gsi-variable.  Cancels the
;;;                  task in the task-for-local-data-server?  slot of gsi-variable.
;;;                  Has the side effects of enqueue-gsi-request-for-sensor (q.v.)
;;;                  if the external-system-has-a-scheduler slot of gsi-variable is
;;;                  non-nil, since the remote GSI process has to be told to stop
;;;                  scheduling dataservice.
;;; Non-local exits: None.
;;; Memory impact:   Can have the memory impact of enqueue-gsi-request-for-sensor
;;;                  (q.v.).

(defun-void reset-gsi-collection-interval (gsi-variable)
  (reclaim-evaluation-quantity
    (get-slot-value gsi-variable 'gsi-collection-interval))
  (set-slot-value gsi-variable 'gsi-collection-interval 0))
  
(defun gsi-stop-collecting-data-from-known-interface (sensor gsi-interface)
  (reset-gsi-collection-interval sensor)
  (cond ((and system-is-running
	      (not (active-p gsi-interface)))
	 (write-warning-message 
	     2
	   (tformat
	     "GSI interface not active for sensor ~NF"
	     sensor)))
	(t
	 (if (get-slot-value-if-any gsi-interface 'external-system-has-a-scheduler)
	     (enqueue-gsi-request-for-sensor sensor nil cancel-collection)
	     (when (schedule-task-in-place-p (task-for-local-data-server? sensor))
	       (cancel-task (task-for-local-data-server? sensor))))
	 (clear-queued-by-local-data-server sensor))))

(defun gsi-stop-collecting-data (sensor)
  (when (gsi-data-service-p sensor)
    (let* ((gsi-interface-name?
	     (get-slot-value-if-any
	       sensor
	       'gsi-interface-name))
	   (gsi-interface?
	     (get-instance-with-name-if-any
	       'object
	       gsi-interface-name?)))
      (when gsi-interface?
	(gsi-stop-collecting-data-from-known-interface
	  sensor
	  gsi-interface?)))))

;; jh, 10/16/92.  Extracted gsi-stop-collecting-data-from-known-interface from
;; gsi-stop-collecting-data so that we can better handle edits to the name of
;; the GSI interface.



;;; Declaration:     update-gsi-variable-to-interface-connections
;;;                   (interface-frame 
;;; 	               new-interface-name-or-names
;;; 	               old-interface-name-or-names)
;;; Type:	     Lisp function.
;;; Purpose:         Resume proper dataservice if a GSI interface changes its name.
;;; Arguments:       interface-frame is a GSI interface.
;;;                  new-interface-name-or-names and old-interface-name-or-names are
;;;                  symbols giving the old and new names for the interface.
;;; Return behavior: No useful value.
;;; Users:	     The slot-putter for name-or-names-for-frame in FRAMES5.
;;; Prerequisites:   Caller (slot putter for name-or-names-for-frame) must only call
;;;                  this when the set of names changes.
;;; Side effects:    Stops and resumes dataservice on GSI variables, depending on
;;;                  the contents of their gsi-interface-name slot.
;;; Non-local exits: None.
;;; Memory impact:   See gsi-stop-collecting-data and gsi-begin-collecting-data.

(defun update-gsi-variable-to-interface-connections
    (interface-frame 
      new-interface-name-or-names
      old-interface-name-or-names)
  (when (active-p interface-frame)
    (unless nil ; (equal old-interface-name-or-names new-interface-name-or-names) ; see note! (MHD 5/30/02)
      (loop for variable being class-instance of 'variable
	    when 
	      (and (gsi-data-service-p variable)
		   (active-p variable))
	      do
		(let ((name-of-variable-interface?
			(get-slot-value-if-any 
			  variable
			  'gsi-interface-name)))
		  (when name-of-variable-interface?
		    (let ((connecting-to-old-interface-p
			    (if (consp old-interface-name-or-names)
				(memq name-of-variable-interface?
				      old-interface-name-or-names)
				(eq name-of-variable-interface?
				    old-interface-name-or-names)))
			  (connecting-to-new-interface-p
			    (if (consp new-interface-name-or-names)
				(memq name-of-variable-interface?
				      new-interface-name-or-names)
				(eq name-of-variable-interface?
				    new-interface-name-or-names))))
		      (when (or connecting-to-old-interface-p
				connecting-to-new-interface-p)
			(gsi-stop-collecting-data-from-known-interface
			  variable
			  interface-frame)
			(let ((old-collection-interval?
				(background-collection-interval? variable)))
			  (when old-collection-interval?
			    (gsi-begin-collecting-data
			      variable
			      old-collection-interval?)))))))))))

  ;; jh, 10/16/92.  Added update-gsi-variable-to-interface-connections so we get
;; realistic results when we change the name of a GSI interface.  Previously,
;; GSI variables would stop collecting data properly if the GSI interface name
;; was changed from what was in their gsi-interface-name slot, but they would
;; not resume dataservice if the name of the GSI interface was changed back.
;; This function was patterned after
;; update-g2ds-variable-to-interface-connections.

;; Note: this no longer checks whether old and new names are EQUAL.  That was an
;; inadequate test of whether the set of names is the same.  The adequate test
;; is needed in the caller for several other purposes, so it is now done in the
;; (one) caller, the note-name-change method for gsi-interface, immediately
;; below. (MHD 5/30/02)



;;; The `note-name-change gsi-interface' method invokes
;;; update-gsi-variable-to-interface-connections on gsi-interface after invoking
;;; its superior method.

(def-class-method note-name-change (gsi-interface old-names initializing-p)
  (funcall-superior-method gsi-interface old-names initializing-p)
  (update-gsi-variable-to-interface-connections
    gsi-interface
    (name-or-names-for-frame gsi-interface)
    old-names))










;;; Declaration:     process-requests-for-gsi-interfaces ()
;;; Type:	     Lisp function.
;;; Purpose:         Accept data from the remote GSI process for a GSI interface
;;;                  that has not timed out.
;;; Arguments:	     None.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals:
;;;                    gsi-process-gsi-interfaces
;;;                    enqueue-gsi-request-for-sensor
;;; Prerequisites:   None.
;;; Side effects:    Modifies the sensor-groups-header slot of each GSI interface
;;;                  that is not timed out.
;;; Non-local exits: When (time-slice-expired-p) returns non-nil, this function
;;;                  stops processing GSI interfaces in a resumable state.
;;; Memory impact:   Can reclaim sensor-group structures and gsi-conses used for
;;;                  enqueuing them.

;; Changed process-requests-for-gsi-interfaces to check if the GSI extension is
;; in the midst of initialization, using icp-sockets-now-initializing-gsi.  (jh,
;; 7/11/90)

(defun-simple process-requests-for-gsi-interfaces ()
  (loop with more-processing-not-necessary? = t
	with count-of-interfaces-to-process =
	  (length gsi-interfaces-to-process-head)
	for count from 1
	as interface-to-process? = (dequeue 
				     gsi-interfaces-to-process-head
				     gsi-interfaces-to-process-tail
				     reclaim-gsi-cons)
	as interface-icp-socket? = (if interface-to-process?
				      (get-slot-value-if-any 
					interface-to-process? 
					'gsi-interface-icp-socket))
        as interface-structure? = (if interface-to-process?
				     (get-slot-value-if-any 
				       interface-to-process? 
				       'gsi-interface-structure))
        as interface-not-timed-out? = (if interface-structure?
					  (not (gsi-interface-timed-out-p
						 interface-structure?)))
	as icp-socket-open? = (and interface-icp-socket?
				   (icp-connection-open-p interface-icp-socket?)
				   (=f (gsi-connection-state interface-icp-socket?) gsi-connection-established))
	do (when interface-to-process?
	     
	     (when (and interface-icp-socket? icp-socket-open?)
	       (if (and interface-not-timed-out?
			(=f (gsi-connection-state interface-icp-socket?)
			    gsi-connection-established))
		   
		   (loop with sensor-groups-header = 
			   (get-slot-value-if-any interface-to-process?
						  'gsi-sensor-groups-header)
			 as gsi-request-to-send = 
			    (dequeue (sensor-groups-to-send-head 
				       sensor-groups-header) 
				     (sensor-groups-to-send-tail 
				       sensor-groups-header) 
				     reclaim-gsi-cons)
			 do (if gsi-request-to-send
				(send-message-series-for-gsi-request
				  gsi-request-to-send interface-to-process?))
			 until (or (null gsi-request-to-send)
				   (time-slice-expired-p))
			 finally (when (and 
					 (time-slice-expired-p)
					 (sensor-groups-to-send-head
					   sensor-groups-header))
				   (setq more-processing-not-necessary? nil)
				   (enqueue interface-to-process?
					    gsi-interfaces-to-process-head
					    gsi-interfaces-to-process-tail
					    gsi-cons)))
		   (enqueue interface-to-process?
			    gsi-interfaces-to-process-head
			    gsi-interfaces-to-process-tail
			    gsi-cons))))
	until (or (null (examine-head-of-queue 
			  gsi-interfaces-to-process-head))
		  (time-slice-expired-p)
		  )
	finally (return (if (< count count-of-interfaces-to-process)
			    nil
			    more-processing-not-necessary?))))





;;; GSI data server codes
	 
;;; The gsi-sensor structure will be placed in the icp corresponding index
;;; array.  The sensor-frame-serial-number is used to check if a sensor has been
;;; recycled or deleted in the time between requesting and receiving a value.
;;; If the sensor frame has been recycled then the gsi-sensor structure is
;;; recycled?  There should be a way to clear the icp corresponding object
;;; index.

;;; The flag accept-values-for-gsi-sensor?  lets the icp receiver know that G2
;;; no longer wants values for a particular sensor.  The sensor still exists,
;;; but data collection has been cancelled, or suspended.

;;;  GSI requests to send to the external process can currently be
;;;     write-user-message-string
;;;     set-values-for-sensors
;;;     get-values-for-sensors



;;; Declaration:     gsi-request-type (gsi-request-to-send)
;;; Type:	     G2 substitution macro.
;;; Purpose:	     Determine the type of request for some GSI variable values.
;;; Arguments:	     gsi-request-to-send is a sensor-group structure.
;;; Return behavior: Returns a symbol, one of the following:
;;;  		       get-values-for-sensors
;;; 		       set-values-for-sensors
;;; 		       stop-sending-values-for-sensors
;;;                    'write-user-message-string
;;; Users:	     GSI internals (send-message-series-for-gsi-request).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(def-substitution-macro gsi-request-type (gsi-request-to-send)    ;add the stop-sensing-values case
  (cond ((sensor-group-p gsi-request-to-send)
         (if (sensor-group-setting-values? gsi-request-to-send)
           'set-values-for-sensors
           'get-values-for-sensors))
        (t 'write-user-message-string)))





;;; Declaration:     gsi-item-attribute-value 
;;;                    (position gsi-variable parameter-name-or-name-list)
;;; Type:	     Lisp function.
;;; Purpose:	     Get the value of a GSI-variable or one of its attributes.
;;; Arguments:       position is a fixnum.  If parameter-name-or-name-list is a
;;;                  list, position specifies the value of an identifying-attribute
;;;                  of gsi-variable.  If parameter-name-or-name-list is a symbol
;;;                  and position is 0, this specifies a single
;;;                  identifying-attribute named by that symbol.
;;; Return behavior: Returns a evaluation-value containing the value of the
;;;                  specified identifying attribute, or nil.
;;; Users:	     GSI internals:
;;;                    define-or-configure-gsi-sensor
;;;                    add-sensor-to-group-if-it-fits
;;;                    put-sensor-in-new-sensor-group
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Can create a evaluation-value structure, which the caller
;;;                  must reclaim.
;;; Notes:           Performance could be improved slightly if this function
;;;                  cooperated more with define-or-configure-gsi-sensor, since the
;;;                  latter calls the former for each identifying attribute, which
;;;                  is quadratic in the number of identifying attributes
;;;                  (admittedly not high).  

;; Gsi-item-attribute-value returns a evaluation-value representing the value
;; of a G2 sensor's slots.  Given appropriate arguments, this function can
;; supply either the actual value of the variable, or a value from one of its
;; sensor ID attributes.  The caller of gsi-item-attribute-value is responsible
;; for reclaiming the returned evaluation-value.  (jh, 3/19/90)

;called by get-gsi-identifying-attribute-values, add-sensor-to-group-if-it-fits
; and put-sensor-in-new-sensor-group
(defun gsi-item-attribute-value (parameter-name gsi-item)
  (when (or (atom parameter-name)
	    (eq (car parameter-name) 'class-qualified-name))
    (let*-sim ((*current-computation-frame* gsi-item))
      (let ((parameter-value?
	      (cond ((eq parameter-name 'names)
		     (let ((name-or-names?
			     (get-slot-value-if-any 
			       gsi-item 
			       'name-or-names-for-frame)))
		       (if (consp name-or-names?)
			   (car name-or-names?)
			   name-or-names?)))
		    (parameter-name
		     (serve-unique-item-or-evaluation-value-of-role
		       parameter-name gsi-item nil t))
		    (t nil))))
	(cond ((null parameter-value?) nil)
	      ((evaluation-value-p parameter-value?)
	       parameter-value?)
	      ((parameter-p parameter-value?)
	       (let*-sim ((*current-computation-frame* parameter-value?)
			  (current-computation-flags current-computation-flags)
			  (*variables-that-did-not-have-values* nil))
		 (setf (force-new-request-for-value) nil)
		 (setf (dont-compute-new-variable-values) t)
		 (get-current-evaluation-value-of-parameter
		   parameter-value?)))
	      (t (write-warning-message 
		     2
		   (tformat
		     "The value for identifying attribute ~A ~
                      of GSI item ~NF ~
                      is neither a constant value nor a parameter ~
                      and will be ignored."
		     parameter-name
		   gsi-item))
	       nil))))))

;; jh, 10/2/92.  Added warning if an identifying attribute is not something
;; which always has a value, for instance a variable.  As before, parameters or
;; constant values are acceptable.

;; jh, 10/16/92.  Modified gsi-item-attribute-value to handle the special case
;; where the name of the GSI variable is an identifying attribute.  Since
;; name-or-names-for-frame is not a user attribute, we can't use
;; install-true-value-update on it.  GSI users have asked for this feature in
;; order to make the notion of identifying attributes easier to grasp.  What
;; could be more archetypal an identifying attribute for a GSI variable than the
;; name itself?



;;; Declaration:     send-message-series-for-gsi-request 
;;;                    (gsi-request-to-send gsi-interface)
;;; Type:	     Lisp function.
;;; Purpose:         Send a group of requests for values of GSI variables.
;;; Arguments:       gsi-request-to-send is a sensor-group structure containing the
;;;                  requests to send through gsi-interface.
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (process-requests-for-gsi-interfaces).
;;; Prerequisites:   None.
;;; Side effects:    Removes elements from the queue inside gsi-request-to-send.
;;;                  Sends the ICP messages begin-sensor-list,
;;;                  load-sensor-list-element, end-sensor-list, and one of the
;;;                  following: get-values-for-sensors-in-list,
;;;                  set-values-for-sensors-in-list, or
;;;                  stop-sending-values-for-sensors-in-list.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims the sensor-group structure gsi-request-to-send,
;;;                  including the gsi-conses used to implement its queue.

;; Now send-message-series-for-gsi-request contains a check for deactivated
;; sensors.  This stops some spurious get-value messages from being sent to the
;; GSI extension after the stop-data message.  (jh, 7/11/90)

(defun-simple send-message-series-for-gsi-request
	      (gsi-request-to-send gsi-interface)
  (let ((request-type 
	  (gsi-request-type gsi-request-to-send))
	(gsi-icp-socket
	  (get-slot-value-if-any  gsi-interface 'gsi-interface-icp-socket))
	(use-new-message-group-for-send-icp-enlarge-index-space-p nil))
    (when (and gsi-icp-socket
	       (icp-connection-open-p gsi-icp-socket)
	       (=f (gsi-connection-state gsi-icp-socket)
		   gsi-connection-established))
      (writing-icp-message-group ((icp-output-port gsi-icp-socket))
	(send-icp-begin-sensor-list)
	(loop with request-to-specify
	      as sensor-list-element-cons = 
	      (dequeue (sensor-group-sensors-to-send-head gsi-request-to-send)
		       (sensor-group-sensors-to-send-tail gsi-request-to-send)
		       reclaim-gsi-cons)
	      until (null sensor-list-element-cons)
	      as sensor-list-element = (car sensor-list-element-cons)
	      as value-to-set? = (cdr sensor-list-element-cons)
	      do (when (and sensor-list-element
			    (active-p sensor-list-element))
		   (setq request-to-specify request-type)
		   (send-icp-load-sensor-list-element
		     (register-item-with-socket
		       sensor-list-element gsi-icp-socket t)
		     (get-slot-value-if-any
		       sensor-list-element 'gsi-internal-collection-interval)
		     value-to-set?))
		 (when value-to-set?
		   (reclaim-evaluation-value value-to-set?))
		 (reclaim-gsi-cons sensor-list-element-cons)
	      finally 
		(loop with parameters-list = (sensor-group-parameters
					       gsi-request-to-send)
		      for parameter in parameters-list
		      do (reclaim-if-evaluation-value parameter)
		      finally (setf (sensor-group-parameters gsi-request-to-send)
				    nil)
			      (reclaim-gsi-list parameters-list))
		(reclaim-sensor-group gsi-request-to-send)
		(send-icp-end-sensor-list)
		(case request-to-specify
		  (get-values-for-sensors
		   (send-icp-get-values-for-sensors-in-list))
		  (set-values-for-sensors
		   (send-icp-set-values-for-sensors-in-list))
		  (stop-sending-values-for-sensors
		   (send-icp-stop-sending-values-for-sensors-in-list))))))))





;;; Declaration:     gsi-receive-value-for-ping-request
;;;                    (gsi-interface timestamp status)
;;; Type:	     Lisp function.
;;; Purpose:	     Receive status information from the remote GSI process.
;;; Arguments:       gsi-interface is a gsi-interface structure (see GSI-COMMON).
;;;                  The argument timestamp is
;;;                  currently ignored (see notes).  status is a fixnum representing
;;;                  the status received from the remote GSI process.  (See
;;;                  gsi-interface-status for status codes.)
;;; Return behavior: No useful value.
;;; Users:	     GSI internals (ICP message receive-value-for-ping-request).
;;; Prerequisites:   None.
;;; Side effects:    Modifies the gsi-interface-last-time-difference,
;;;                  gsi-interface-status-code, gsi-interface-timed-out-p, and
;;;                  gsi-interface-waiting-for-response-p slot of gsi-interface.
;;;                  Modifies icp-sockets-now-initializing-gsi.  Can post logbook
;;;                  messages.
;;; Non-local exits: None.
;;;
;;;                  This function can reclaim a
;;;                  gsi-cons on icp-sockets-now-initializing-gsi.

;;; Gsi-receive-value-for-ping-request is called from the ICP handler for
;;; receive-value-for-ping-request.  It alerts the local G2 if the other side is
;;; not alive and takes other appropriate measures.

;; Changed gsi-receive-value-for-ping-request to remove the current ICP socket
;; from icp-sockets-now-initializing-gsi, a list of ICP sockets whose GSI
;; extension is undergoing intialization.  (jh, 7/11/90)

;;; GENSYMCID-1352: Out-of-range timestamp
;;;                 (seen in RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP)
;;; the following function has been largely rewritten with modern time stamping
;;; machinery updated. -- Chun Tian (binghe), Feb 10, 2015.

(defun gsi-receive-value-for-ping-request
    (gsi-interface? year month day hour minute second status)
  (when gsi-interface?
    (with-temporary-gensym-float-creation gsi-receive-value-for-ping-request
      (let* ((invalid-timestamp?
	      ;; Here, the old invalid timestamp (0 0 0 0 0 0) can still be received
	      ;; from old version of GSI code, in this case we don't call any unix-time
	      ;; functions. --binghe, 2015/2/14
	      (or (=f year 0) (=f month 0) (=f day 0)))
	     (sending-timestamp
	      (if invalid-timestamp?
		  0.0d0
		(gensym-encode-unix-time second minute hour day month year)))
	     (current-timestamp
	      (if invalid-timestamp?
		  0.0d0
		(gensym-get-unix-time)))
	     (time-difference-in-seconds
	      (if invalid-timestamp?
		  0.0d0
		(-e current-timestamp sending-timestamp)))
	     (gsi-interface-frame
	      (gsi-interface-frame gsi-interface?)))
	(declare (type gensym-float sending-timestamp current-timestamp
				    time-difference-in-seconds))
	;; this slot is not used anywhere so far. --binghe, 2015/2/14
	(setf (gsi-interface-last-time-difference gsi-interface?)
	      time-difference-in-seconds)

	(when (/=f (get-gsi-interface-status gsi-interface-frame) status)
	  (let ((gsi-interface-socket
		 (get-slot-value-if-any gsi-interface-frame 'gsi-interface-icp-socket)))

	    (setf (gsi-connection-state gsi-interface-socket) gsi-connection-established)
	    (cancel-task (icp-connection-timeout-task? gsi-interface-socket))
	    (change-gsi-interface-status gsi-interface-frame status))

	  (when (=f gsi-interface-running-ok status)
	    (activate-variables-for-gsi-interface gsi-interface-frame)
	    (maybe-begin-collecting-data-for-interface gsi-interface-frame)))

	(setf (gsi-interface-timed-out-p gsi-interface?) nil)
	(setf (gsi-interface-waiting-for-response-p gsi-interface?) nil)

	(setf (gsi-interface-timestamp gsi-interface?) current-timestamp)))))

;; End file with CR


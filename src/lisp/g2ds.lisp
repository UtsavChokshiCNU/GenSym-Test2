;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module G2DS -- G2 to G2 Data Service Using ICP

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Brian L. Matthews & John Hodgkinson

;; jh, 3/9/92.  Reorganized this file, spun off from G2DS #227.

;; jh, 10/7/92.  Merged in changes from #228 through #232, inclusive.  The old
;; version is in ma:>jh>lisp>g2ds-232-old.lisp in case anything goes wrong.

;;; ...  Note that the acronym G2DS stands for "G2 Data Server" or "G2 Data
;;; Service", depending on context.  This term may be used interchangably with
;;; "G2-to-G2" ...


;;;
;;;  I found it hard to understand what's going on here, simply because the
;;;  functions aren't grouped by what which G2 they run in.  The terminology is
;;;  confusing, too; the "local" (requesting) G2 is called the "local data
;;;  server" because it implements a "G2 data server", but it is actually a
;;;  _client_ of the "remote" G2, which will actually provide the data.
;;;      -ncc, 5 Jan 1995  
;;;

;;;; Contents

;;; [0.5]    Forward references
;;; [1]      Conser for G2-to-G2 Dataservice
;;; [2]      G2-to-G2 Dataserver Definition
;;; [3]      General Grammar Rules for G2-to-G2 Dataservice

;;; [4]      ICP Declarations for G2-to-G2 Dataservice
;;; [4.1]      ICP Message Type Codes for G2-to-G2 Dataservice
;;; [4.2]      ICP Data Types for G2-to-G2 Dataservice
;;; [4.2.1]      Data Type to Represent a Remote Variable
;;; [4.2.2]      Data Types for Remote Variable Values
;;; [4.2.3]      Data Type for Remote Expressions
;;; [4.3]      I-am-alive Mechanism for G2-to-G2 Dataservice

;;; [5]      Capabilities for G2-to-G2 Dataservice
;;; [5.1]      G2-to-G2 Data Interface Capability
;;; [5.2]      G2-to-G2 Dataservice Capability

;;; [6]      G2-to-G2 Interfaces
;;; [6.1]      Scheduling G2-to-G2 Dataservice Tasks
;;; [6.2]      Internal Structures for G2-to-G2 Interfaces
;;; [6.3]      Inter-G2 Data Requests
;;; [6.3.1]      Error-Handling Inter-G2 Data Requests
;;; [6.3.2]      Class to Represent Inter-G2 Data Requests
;;; [6.3.3]      Inter-G2 Data Request Functions & Methods
;;; [6.4]      Slot-Putters for G2-to-G2 Data Interface Capability
;;; [6.5]      Grammar for G2-to-G2 Data Interface Capability
;;; [6.6]      Capability Activator for G2-to-G2 Interfaces
;;; [6.7]      Handler for G2-to-G2 Client Shutdown
;;; [6.8]      Handler for G2-to-G2 Server Shutdown
;;; [6.9]      Capability Deactivator for G2-to-G2 Interfaces
;;; [6.10]     Interface Status

;;; [7]      G2-to-G2 Variables
;;; [7.1]      Slot-Putters for G2-to-G2 Dataservice Capability
;;; [7.1.1]      Slot-Putter for Interface Name
;;; [7.1.2]      Slot-Putter for Remote Expression
;;; [7.2]      Grammar for G2-to-G2 Dataservice Capability
;;; [7.3]      Capability Activator for G2-to-G2 Dataservice
;;; [7.4]      Capability Deactivator for G2-to-G2 Dataservice

;;; [8]      ICP Messages for G2-to-G2 Dataservice
;;; [8.1]      Messages to Create Corresponding Variable Objects
;;; [8.2]      Messages for Grouping Variables
;;; [8.3]      Messages for Getting and Setting Values
;;; [8.4]      Messages to Initate Dataservice
;;; [8.5]      Messages to Control Remote Dataservice
;;; [8.6]      Messages to Receive Remote Data
;;; [8.7]      Messages for G2-to-G2 Inform Actions

;;; [9]      G2-to-G2 Dataserver Functions
;;; [9.1]      Function to Collect One Shot G2-to-G2 Data
;;; [9.2]      Function to Begin Collecting G2-to-G2 Data
;;; [9.3]      Function to Stop Collecting G2-to-G2 Data
;;; [9.4]      Function to Accept G2-to-G2 Data
;;; [9.5]      Function to Initialize G2-to-G2 Data Server
;;; [9.6]      Function to Set External G2-to-G2 Variable
;;; [9.7]      Function to Shut Down G2-to-G2 Data Server
;;; [9.8]      Function to Deliver G2-to-G2 Messages
;;; [9.9]      Function to Pause G2-to-G2 Data Server
;;; [9.10]     Function to Resume G2-to-G2 Data Server



;;; [0.5] Forward references

(declare-forward-reference ui-client-interface-p-function function) ;; view-g2.lisp



;;; [1] Conser for G2-to-G2 Dataservice

(defconser g2ds G2DS)





;;;; [2] G2-to-G2 Dataserver Definition

(def-data-server 'g2-data-server
  'g2ds-collect-one-shot-data
  'g2ds-begin-collecting-data
  'g2ds-stop-collecting-data
  'g2ds-accept-data
  t					;server-is-in-use
  'g2ds-initialize-server
  'g2ds-set-external-variable
  'g2ds-shut-down-server
  'g2ds-send-message
  'g2ds-pause-server
  'g2ds-resume-server
  'g2ds-requests-accept-data-calls-p)

(def-data-server-pretty-printer 'g2-data-server "G2 data server")






;;;; [3] General Grammar Rules for G2-to-G2 Dataservice

(add-grammar-rules
  `((data-server-spec ('g2 'data 'server) g2-data-server)
    (data-server-map ('g2 'data 'server ) g2-data-server)))






;;;; [4] ICP Declarations for G2-to-G2 Dataservice

;;; ...  these include ICP message type codes and reader and writer
;;; definitions for ICP value types ...






;;;; [4.1] ICP Message Type Codes for G2-to-G2 Dataservice

;; There is an overlap in ICP message codes 120-127.  Both GSPAN and G2DS use
;; these codes, but this doesn't cause problems due to the following facts:
;;   1) Def-icp-message-type-code associates message codes with symbols,
;;      so it is possible (but strongly denigrated) for two different modules
;;      to send the same code number with two different "meanings".  Thus
;;      there is no conflict in sending codes 120-127.
;;   2) The def-icp-message-type forms for the GSPAN codes 120-127 contain no
;;      handler body, so no GSPAN handler functions get defined.  The
;;      def-icp-message-type forms for G2DS do create handler functions, but there
;;      are no GSPAN handlers to overwrite.  Thus there is no conflict in
;;      receiving codes 120-127.
;;
;; Any of the following changes would break this tenuous arrangement:
;;   1) A change in def-icp-message-type-code which creates handlers even
;;      when no handler body is present.
;;   2) Adding handlers to GSPAN messages using codes 120-127.
;;      As of 4/25/90, the affected GSPAN message are:
;;        120: new-externally-simulated-object
;;        121: define-external-simulation-object
;;        122: simulation-initialization-value
;;        123: end-simulation-initialization-vector-for-object
;;        124: begin-simulation-input-vector-for-object
;;        125: simulation-keyword
;;        126: simulation-input-value
;;        127: end-simulation-input-vector-for-object
;;      None of these look like two-way messages, but you never can tell.
;;   3) Writing a GSPAN extension process in lisp.
;;
;; This is the only overlap in ICP message codes as of 4/25/90.
;;
;; The moral: be more careful about reserving ICP message codes.  If possible,
;; always place the def-icp-message-type-code forms themselves in the INT
;; module.  If this is not feasible, place clear warning in INT where all the
;; other def-icp-message-type-codes are found.  (jh, 4/25/90)

(eval-when (:compile-toplevel :load-toplevel :execute)

(def-icp-message-type-code g2ds-begin-variable-list         110 g2-ds)
(def-icp-message-type-code g2ds-load-variable-list-element  111 g2-ds)
(def-icp-message-type-code g2ds-end-variable-list           112 g2-ds)
(def-icp-message-type-code g2ds-get-values                  113 g2-ds)
(def-icp-message-type-code g2ds-set-values                  114 g2-ds)
(def-icp-message-type-code g2ds-user-message-string         115 g2-ds)
(def-icp-message-type-code g2ds-unsolicited-attribute-value 116 g2-ds) ;only NUPEC as of 3/10/92
(def-icp-message-type-code g2ds-unsolicited-variable-value  117 g2-ds) ;only NUPEC as of 3/10/92
(def-icp-message-type-code g2ds-variable-value              118 g2-ds)
(def-icp-message-type-code g2ds-define-variable             119 g2-ds)
(def-icp-message-type-code g2ds-configure-variable          125 g2-ds t) ; simulation-keyword
(def-icp-message-type-code g2ds-stop-collecting-values      126 g2-ds t) ; simulation-input-value
(def-icp-message-type-code g2ds-server-status               127 g2-ds t) ; end-simulation-input-vector-for-object
(def-icp-message-type-code g2ds-initialize-server           120 g2-ds t) ; new-externally-simulated-object
(def-icp-message-type-code g2ds-shut-down-server            121 g2-ds t) ; define-external-simulation-object
(def-icp-message-type-code g2ds-pause-server                122 g2-ds t) ; simulation-initialization-value
(def-icp-message-type-code g2ds-resume-server               123 g2-ds t) ; end-simulation-initialization-vector-for-object
(def-icp-message-type-code g2ds-send-data-values-if-any     124 g2-ds t) ; begin-simulation-input-vector-for-object
(def-icp-message-type-code return-g2ds-version              170 g2-ds)

) ;end of eval-when for ICP message types in G2DS

;; Added return-G2ds-version code for future version-compatibility checks,
;; though it will not help things if a pre-2.0 G2 tries to connect to
;; one 2.0 or later (i.e., after today).  (jh, 5/1/90)













;;;; [4.2.1] Data Type to Represent a Remote Variable

;;; The g2ds-variable structure is used in both client and server,
;;; through the ICP corresponding object mechanism.  ...
;;; there is also an ICP object definition for g2ds-variable.

(def-structure (g2ds-variable
		 (:constructor make-g2ds-variable
			       (g2ds-variable-g2-frame
				 g2ds-variable-g2-frame-serial-number
				 g2ds-variable-interface-name
				 g2ds-variable-expression
				 g2ds-variable-expression-text
				 g2ds-variable-server-request-structure)))
  g2ds-variable-g2-frame
  (g2ds-variable-g2-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  g2ds-variable-value-to-set?
  g2ds-variable-interface-name
  g2ds-variable-expression
  g2ds-variable-expression-text
  (g2ds-variable-collection-interval? 0)
  g2ds-variable-remote-icp-object-index
  g2ds-variable-scheduled-collection-task
  (g2ds-variable-error-code #.g2ds-no-error)
  (corresponding-icp-object-map-for-g2ds-variable nil)
  (g2ds-variable-ok-to-store-values? t)
  g2ds-variable-server-request-structure
  )

(defun reclaim-g2ds-variable-function (g2ds-variable)
  (declare (ignore g2ds-variable))		;this structure is already reclaimed!
  ;(reclaim-g2ds-variable g2ds-variable)
  )

;; Reclaim-g2ds-variable-function is necessary because no usable reclamer
;; function is defined by def-structure.  Fortunately, in this case it is a
;; no-op.  Consider improving def-structure.




(def-icp-object-type g2ds-variable
		     (standard-icp-object-index-space
		       (corresponding-icp-object-map-for-g2ds-variable
			 g2ds-variable)
		       reclaim-g2ds-variable-function)
  (send-icp-g2ds-define-variable
    corresponding-icp-object-index
    (car (get-slot-value-if-any
	   (g2ds-variable-g2-frame
	     g2ds-variable)
	   'remote-g2-expression))
    (cdr (get-slot-value-if-any
	   (g2ds-variable-g2-frame
	     g2ds-variable)
	   'remote-g2-expression))))

;;; The reader for returned-g2ds-variable is only for referencing g2ds-variable
;;; objects already defined by a send message.

(def-icp-value-reader returned-g2ds-variable
  (get-original-icp-object (read-icp-unsigned-integer)))

(def-icp-value-writer returned-g2ds-variable
  (write-icp-unsigned-integer
    (g2ds-variable-remote-icp-object-index
      returned-g2ds-variable)))






;;;; [4.2.2] Data Types for Remote Variable Values

;; jh, 2/27/92.  The g2ds-float ICP data type is not transmitted by versions of
;; G2 2.1 or greater.  It exists for compatibility with previous versions.

(def-icp-value-writer g2ds-float
  (let ((float (if (managed-float-p g2ds-float)
		   (managed-float-value g2ds-float)
		   g2ds-float)))
    (multiple-value-bind (expon signif)
	(ceiling (log (abs (if (= float 0.0)
			       1.0e-37
			       float)) 10))
      (let ((sign (if (> float 0.0) 1 0))
	    (signif-int (truncate (* signif most-positive-fixnum32-plus-one))))
	(write-icp-integer signif-int)
	(write-icp-integer expon)
	(write-icp-byte sign)))))

(def-icp-value-reader g2ds-float
  (allocate-managed-float
    (let* ((signif (read-icp-integer))
	   (expon (read-icp-integer))
	   (sign (read-icp-byte)))
      (if (=f sign 0)
	  (- (expt 10 (+ expon (/ signif most-positive-fixnum32-plus-one-as-float))))
	  (expt 10 (+ expon (/ signif most-positive-fixnum32-plus-one-as-float)))))))

(def-icp-value-writer g2ds-list
  (write-icp-unsigned-integer (length g2ds-list))
  (loop for item in g2ds-list
        do (write-icp-g2ds-expression item)))

(def-icp-value-reader g2ds-list
  (loop for item-count from 1 to (read-icp-unsigned-integer)
        collect (read-icp-g2ds-expression)
        using g2ds-cons))

(def-icp-value-writer g2ds-dotted-list
  (let ((conses (loop for cons? = g2ds-dotted-list then (cdr cons?)
		      while (consp cons?)
		      count t)))
    (write-icp-unsigned-integer conses)
    (loop for value-cons = g2ds-dotted-list then (cdr value-cons)
	  while (consp value-cons)
	  do
      (write-icp-g2ds-expression (car value-cons))
	  finally
	    (write-icp-g2ds-expression value-cons))))

(def-icp-value-reader g2ds-dotted-list
  (let ((list (loop repeat (read-icp-unsigned-integer)
		    collect (read-icp-g2ds-expression) using g2ds-cons)))
    (setf (cdr (last list)) (read-icp-g2ds-expression))
    list))

(defvar g2ds-data-value-write-truth-value-as-integer-p t)

(def-icp-value-writer g2ds-data-value
  (cond ((null g2ds-data-value)
	 (write-icp-byte g2ds-null-type-tag))
	((integerp g2ds-data-value)
	 (write-icp-byte g2ds-integer-type-tag)
	 (write-icp-integer g2ds-data-value))
	((evaluation-truth-value-p g2ds-data-value)
	 (write-icp-byte
	   (if g2ds-data-value-write-truth-value-as-integer-p
	       g2ds-integer-type-tag
	       g2ds-logical-type-tag))
	 (write-icp-integer (evaluation-truth-value-value g2ds-data-value)))
	((symbolp g2ds-data-value)
	 (write-icp-byte g2ds-symbol-type-tag)
	 (write-icp-text-string (symbol-name-text-string g2ds-data-value)))
	((text-string-p g2ds-data-value)
	 (write-icp-byte g2ds-string-type-tag)
	 (write-icp-text-string g2ds-data-value))
       	((evaluation-float-p g2ds-data-value)
	 (with-bifurcated-version-for-output (double-float-icp-version)
	   (progn (write-icp-byte g2ds-float-type-tag)
		  (write-icp-float g2ds-data-value))
	   (progn (write-icp-byte g2ds-64bit-float-type-tag)
		  (write-icp-managed-double-float g2ds-data-value))))
	((evaluation-sequence-p g2ds-data-value)
	 (with-bifurcated-version-for-output (evaluation-sequences-and-structures-icp-version)
	   (progn
	     (write-icp-byte g2ds-null-type-tag))
	   (progn
	     (write-icp-byte g2ds-evaluation-sequence-type-tag)
	     (write-icp-g2ds-evaluation-sequence g2ds-data-value))))
	((evaluation-structure-p g2ds-data-value)
	 (with-bifurcated-version-for-output (evaluation-sequences-and-structures-icp-version)
	   (progn
	     (write-icp-byte g2ds-null-type-tag))
	   (progn
	     (write-icp-byte g2ds-evaluation-structure-type-tag)
	     (write-icp-g2ds-evaluation-structure g2ds-data-value))))
	(t
	 #+development
	 (cerror "Continue" "Unknown data type for value: ~S" g2ds-data-value)
	 (write-icp-byte g2ds-null-type-tag))))

(def-icp-value-writer g2ds-evaluation-sequence
  (loop with g2ds-data-value-write-truth-value-as-integer-p = nil
	for value being each evaluation-sequence-element of g2ds-evaluation-sequence
	do
    (write-icp-g2ds-data-value value)
	finally (write-icp-byte #.gsi-end-type-tag)))

(def-icp-value-writer g2ds-evaluation-structure
  (loop with g2ds-data-value-write-truth-value-as-integer-p = nil
	for (attribute-name . attribute-value)
	    being each evaluation-structure-pair of g2ds-evaluation-structure
	do
    (write-icp-g2ds-data-value attribute-name)
    (write-icp-g2ds-data-value attribute-value)
	finally (write-icp-byte #.gsi-end-type-tag)))

(defun-void reclaim-g2ds-data-value (g2ds-data-value)
  (reclaim-if-evaluation-value g2ds-data-value))

(def-icp-value-reader g2ds-data-value
  (let ((code (read-icp-byte)))
    (case code
      (#.g2ds-null-type-tag nil)
      (#.g2ds-integer-type-tag
       (read-icp-integer))
      (#.g2ds-float-type-tag
       (read-icp-g2ds-float))
      (#.g2ds-logical-type-tag
       (make-evaluation-truth-value
	 (read-icp-integer)))
      (#.g2ds-64bit-float-type-tag
       (read-icp-managed-double-float))
      (#.g2ds-symbol-type-tag
       (intern-text-string (read-icp-text-string)))
      (#.g2ds-string-type-tag
       (read-icp-text-string))
      (#.g2ds-evaluation-sequence-type-tag
       (read-icp-g2ds-evaluation-sequence))
      (#.g2ds-evaluation-structure-type-tag
       (read-icp-g2ds-evaluation-structure))
      (t
       #+development
       (cerror "Continue" "Unknown code in g2ds-data-value: ~S" code)
       nil))))

(def-icp-value-reader g2ds-evaluation-sequence
  (allocate-evaluation-sequence
    (read-icp-terminated-list g2ds-data-value eval-cons)))

(def-icp-value-reader g2ds-evaluation-structure
  (allocate-evaluation-structure
    (read-icp-terminated-list-of-pairs g2ds-data-value eval-cons)))

;; Modified the reader and writer for G2ds-data-value to use IEEE format double
;; floats.  Despite the version-checking, pre-2.0 G2s will not be compatible with
;; later G2s.  However, exchanging version numbers may come in handy someday.
;; (jh, 5/1/90)






;;;; [4.2.3] Data Type for Remote Expressions

(def-icp-value-writer g2ds-expression
  (cond ((and (consp g2ds-expression)
	      (not (and (managed-array-p (car-of-cons g2ds-expression))
			(let ((cdr (cdr-of-cons g2ds-expression)))
			  (or (eq cdr 'sequence)
			      (eq cdr 'structure))))))
	 (cond ((null (cdr (last g2ds-expression)))
		(write-icp-byte g2ds-list-type-tag)
		(write-icp-g2ds-list g2ds-expression))
	       (t
		(write-icp-byte g2ds-dotted-list-type-tag)
		(write-icp-g2ds-dotted-list g2ds-expression))))
	((floatp g2ds-expression)
         (with-bifurcated-version-for-output (double-float-icp-version)
	   (progn (write-icp-byte g2ds-float-type-tag)
		  (write-icp-float g2ds-expression))
	   (progn (write-icp-byte g2ds-64bit-float-type-tag)
		  (write-icp-double-float g2ds-expression))))
	(t
	 (write-icp-g2ds-data-value g2ds-expression))))

(def-icp-value-reader g2ds-expression
  (with-permanent-gensym-float-creation
    (case (read-icp-byte)
      (#.g2ds-null-type-tag nil)
      (#.g2ds-integer-type-tag
       (read-icp-integer))
      (#.g2ds-float-type-tag
       (read-icp-g2ds-float))
      (#.g2ds-64bit-float-type-tag
       (read-icp-double-float))
      (#.g2ds-symbol-type-tag
       (intern-text-string (read-icp-text-string)))
      (#.g2ds-string-type-tag
       (read-icp-text-string))
      (#.g2ds-list-type-tag
       (read-icp-g2ds-list))
      (#.g2ds-dotted-list-type-tag
       (read-icp-g2ds-dotted-list))
      (#.g2ds-evaluation-sequence-type-tag
       (read-icp-g2ds-evaluation-sequence))
      (#.g2ds-evaluation-structure-type-tag
       (read-icp-g2ds-evaluation-structure)))))

(def-icp-value-writer g2ds-expression-text
  (with-bifurcated-version-for-output (send-text-of-expressions-for-g2ds-icp-version)
    nil
    (write-icp-g2ds-expression g2ds-expression-text)))

(def-icp-value-reader g2ds-expression-text
  (with-bifurcated-version-for-input (send-text-of-expressions-for-g2ds-icp-version)
    nil
    (read-icp-g2ds-expression)))

(defun reclaim-g2ds-expression (g2ds-expression)
  (cond ((consp g2ds-expression)
	 (loop for cons = g2ds-expression then (cdr cons)
	       while (consp cons)
	       do
	   (reclaim-g2ds-expression (car cons))
	       finally
		 (if cons
		     (reclaim-g2ds-expression cons)))
	 (reclaim-g2ds-list* g2ds-expression))
	((text-string-p g2ds-expression)
	 (reclaim-text-string g2ds-expression))
	(t nil)))





;;;; [4.3] I-am-alive Mechanism for G2-to-G2 Dataservice

;; (jh, 7/24/90)
;; Added rudimentary I-am-alive mechanism for G2-to-G2 connections, so sockets
;; can be recycled sooner.  If they are not, it causes problems in applications
;; whose connections are made and broken frequently, such as the regression KB of
;; ac and bah.  The I-am-alive code for G2DS is based largely on that found in
;; TELESTUBS, with reduced functionality.

;;; For now (2.0) the I-am-alive handlers for G2ds do nothing except try to keep
;;; abreast of events.  They don't shut down the ICP socket if they determine
;;; it's not alive, and they don't "push back" any information to G2 if they
;;; determine the socket is clogged.  We don't need any more for now because all
;;; we want is an attempt to write to the ICP socket every so often.  This is
;;; the only reliable way to cause some tcp sockets to fail.  If the write fails
;;; on the remote side, the socket will be marked for shutdown and
;;; process-icp-sockets will take care of the rest.

(defparameter g2ds-max-number-of-message-groups-before-clogged 50)

(defparameter g2ds-min-number-of-message-groups-before-unclogged 20)

(defparameter g2ds-max-number-of-icp-bytes-before-clogged 20000)

(defparameter g2ds-min-number-of-icp-bytes-before-unclogged 500)

(defun g2ds-connection-clogged-p (icp-socket I-am-alive-info)
  (declare (ignore icp-socket))
  (if (icp-connection-clogged-p I-am-alive-info)
      (<f (number-of-outstanding-icp-bytes I-am-alive-info)
	  g2ds-min-number-of-icp-bytes-before-unclogged)
      (>f (number-of-outstanding-icp-bytes I-am-alive-info)
	  g2ds-max-number-of-icp-bytes-before-clogged)))






;;;; [5] Capabilities for G2-to-G2 Dataservice

;; Def-capability defines macros, and so should precede most functions in this
;; file.






;;;; [5.1] G2-to-G2 Data Interface Capability

;(def-capability g2-to-g2-data-interface object
;  ((icp-connection-specification
;     nil nil (type icp-connection-specification text) (system) (save))
;   (interface-timeout-period
;     nil nil (system)
;     (type timeout-interval-or-default)
;     (save))
;   (g2ds-interface-structure
;     nil nil (system)
;     (do-not-put-in-attribute-table) (do-not-save) (lookup-slot))
;   (interface-status
;     inactive nil (system)
;     (type symbol) (do-not-save) (not-user-editable)))
;  ()
;  )

(def-class (g2-to-g2-data-interface
	     network-interface
	     (foundation-class object)
	     (disjoint-from gsi-interface gfi-input-interface gfi-output-interface)
	     define-predicate)
  (icp-connection-specification
     (nil (lost-spaces . 0) "none")
     (type icp-connection-specification text) (system) (save))
  (g2ds-interface-structure
     nil (system)
    (do-not-put-in-attribute-tables) (do-not-save) (lookup-slot))
  (interface-status
    inactive (system)
    (type read-only-attribute) (do-not-save) (not-user-editable))
  (interface-is-secure
    nil (system)
    (type yes-or-no) (do-not-save) (not-user-editable))
  (g2ds-server-connection-structure
    nil (system)
    (do-not-put-in-attribute-tables) (do-not-save) (lookup-slot))
  )

(define-category-evaluator-interface (icp-connection-specification
                                      :access read-write)
    (or (no-item)
	(structure icp-connection-specification
	  ((network-transport (member tcp-ip localnet))
	   (hostname (or text symbol))
	   (port (or integer symbol (no-item))))
	  (and network-transport hostname)))
  ((set-form (evaluation-value?))
   (if evaluation-value?
       (evaluation-etypecase evaluation-value?
	 ((structure)
	  (with-structure (evaluation-value? icp-connection-specification)
	    (case network-transport
	      (localnet
	       (managed-backquote phrase-cons
		 (\,network-transport \,hostname)))
	      (otherwise
	       (managed-backquote phrase-cons
		 (\,network-transport \,hostname \,port)))))))
       'none))
  ((get-form (slot-value?))
   (if slot-value?
       (gensym-dstruct-bind
	   ((this-network-transport this-hostname this-port) slot-value?)
	 (case this-network-transport
	   (localnet
	    (with-new-structure (icp-connection-specification)
	      (setf network-transport
		    (copy-evaluation-value this-network-transport))
	      (setf hostname (copy-evaluation-value this-hostname))))
	   (otherwise
	    (with-new-structure (icp-connection-specification)
	      (setf network-transport
		    (copy-evaluation-value this-network-transport))
	      (setf hostname (copy-evaluation-value this-hostname))
	      (setf port (copy-evaluation-value this-port))))))
       nil)))

(def-slot-value-writer icp-connection-specification (connection-spec)
  (twrite-icp-connection-spec connection-spec))

(def-absent-slot-putter g2ds-interface-timeout-period
    (g2-to-g2-data-interface new-g2ds-interface-timeout-period)
  (setf (interface-timeout-period g2-to-g2-data-interface)
	new-g2ds-interface-timeout-period))

;; jh per ghw & mhd, 4/27/94.  Changed the name of the
;; g2ds-interface-timeout-period slot of g2-to-g2-data-interface back to
;; interface-timeout-period.  Also changed the gsi-interface-timeout-period slot
;; of gsi-interface in G2-GSI back to interface-timeout-period.  For further
;; details on the ramifications of using the same name, see comment under the
;; def-class for gsi-interface in module G2-GSI.



;; jh, 4/24/91.  Changed the interface-status slot of the g2-to-g2-data-interface
;; capability to be a system slot.  This is the only way we can prevent
;; user-editing, which can confuse the dataservice machinery.  Other associated
;; changes mirror those done when gsi-interface-status was made into a system
;; slot:
;;
;; serve-system-value in ROLES: A case-clause appropriate to the new slot was
;; added.
;;
;; authorized-system-slots in FRAMES1: the slot name was added to this list.
;;
;; undefined-attribute-exceptions in INSTALL: the slot name was added to this
;; list.  I am not sure if this is necessary.

;; Added a slot-putter to forward chain from the interface-status.  - cpm, 2/1/92

(defun g2-to-g2-data-interface-p-function (item)
  (g2-to-g2-data-interface-p item))

(defun-simple g2-to-g2-interface-connects-while-inactive-p
    (g2-to-g2-data-interface)
  (and (not (or (manually-disabled-p g2-to-g2-data-interface)
		(ancestor-not-activatable-p g2-to-g2-data-interface)))
       (runs-while-inactive-p g2-to-g2-data-interface)))

(def-class-method initialize-after-reading (g2-to-g2-data-interface)
  (funcall-superior-method g2-to-g2-data-interface)
  (when (g2-to-g2-interface-connects-while-inactive-p g2-to-g2-data-interface)
    (activate-g2-to-g2-data-interface-with-or-without-configuration
      g2-to-g2-data-interface))
  (update-representations-of-slot-value
    g2-to-g2-data-interface 'interface-status))








;;;; [5.2] G2-to-G2 Dataservice Capability

;;; All variables which are to get/set values through the G2DS data interface
;;; must have this capability.

;(def-capability g2-to-g2-data-service (variable)
;  ((data-server-map
;     g2-data-server (vector-slot) (system) (type data-server-map))
;   (g2-to-g2-interface-name
;     nil (lookup-slot) (system) (type g2-to-g2-interface-name) (save))
;   (remote-g2-expression
;     nil nil (lookup-slot) (system) (type expression text) (save))
;   (g2ds-variable-structure
;     nil (lookup-slot) (system)
;     (do-not-put-in-attribute-table) (do-not-save)))
;  ())

(def-class (g2-to-g2-data-service variable define-predicate
				  (foundation-class variable)
				  (only-compatible-with variable)
				  not-solely-instantiable
				  not-user-instantiable do-not-put-in-menus)
  (data-server-map
    g2-data-server (vector-slot) (system) (type data-server-map))
  (g2-to-g2-interface-name
    nil (lookup-slot) (system) user-overridable (type g2-to-g2-interface-name)
    (save))
  (remote-g2-expression
    nil (lookup-slot) (system) (type expression text) (save))
  (g2ds-variable-structure
    nil (lookup-slot) (system) (do-not-put-in-attribute-tables) (do-not-save))
  (data-server-for-messages
    g2-data-server
    (no-accessor) ;use the lookup-slot accessor from gsi-message-service
    (do-not-put-in-attribute-tables) (do-not-save) (lookup-slot) (system)))

(define-category-evaluator-interface (g2-to-g2-interface-name
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value?))
   (or evaluation-value? 'none))
  ((get-form (slot-value))
   slot-value))





;;;; [6] G2-to-G2 Interfaces

(def-system-variable list-of-all-g2ds-interfaces G2DS nil)








;;;; [6.1] Scheduling G2-to-G2 Dataservice Tasks

;;; To prevent ICP errors, put-current-value must be executed from a scheduled
;;; task.  Therefore all values coming in from the remote G2 server must be
;;; queued for later processing by a high priorty task.

(def-system-variable list-of-g2ds-values-to-process-head G2DS nil)
(def-system-variable list-of-g2ds-values-to-process-tail G2DS nil)

(def-system-variable task-to-process-g2ds-values G2DS nil)

(defmacro save-g2ds-variable-value-for-processing (g2ds-variable value)
  `(progn
    (enqueue (g2ds-cons
	      ,g2ds-variable ,value)
     list-of-g2ds-values-to-process-head
     list-of-g2ds-values-to-process-tail
     g2ds-cons)
    (when (not (schedule-task-in-place-p task-to-process-g2ds-values))
      (with-current-scheduling
	  (task-to-process-g2ds-values
	    (priority-of-data-service data-server-parameters))
	(process-g2ds-variable-values t)))))




;;;; [6.2] Internal Structures for G2-to-G2 Interfaces

;;; Each object with a g2-to-g2-data-interface capability will be able to
;;; communicate with other G2s for intertask data exchange.


(def-structure (g2ds-interface
		 (:constructor make-g2ds-interface
			       (g2ds-interface-socket)))
  g2ds-interface-socket
  g2ds-interface-data-queue-head			; holds set and get requests for this interface.
  g2ds-interface-data-queue-tail
  (g2ds-interface-number-of-pending-requests 0)	        ; this isn't used anywhere. -ncc, 8 Dec 1994 
  g2ds-interface-timed-out-p
  g2ds-interface-waiting-for-response-p
  (g2ds-interface-status 'inactive)
  g2ds-interface-countdown-timer
  g2ds-interface-countdown-timer-limit
  )



(defun g2ds-interface-socket-function (g2ds-interface)
  (g2ds-interface-socket g2ds-interface))



(def-system-variable g2ds-server-connections G2DS nil)

(def-structure (g2ds-server-connection
		 (:constructor make-g2ds-server-connection
			       (g2ds-server-connection-icp-socket)))
  g2ds-server-connection-icp-socket
  (g2ds-server-connection-paused? nil)
  g2ds-server-connection-return-queue-head
  g2ds-server-connection-return-queue-tail
  (g2ds-server-connection-return-count 0)
  g2ds-server-connection-variables
  g2ds-server-flush-return-data-task
  )


(defun-simple g2ds-server-connection-icp-socket-function (x)
  (g2ds-server-connection-icp-socket x))



;;;; [6.3] Inter-G2 Data Requests

;;; When G2 instances are acting as data servers to each other across some
;;; network, they need to be able to schedule and receive replies from an
;;; inference engine on a remote server G2.  These requests will be passed
;;; through G2 frames called inter-g2-data-requests.






;;;; [6.3.1] Error-Handling Inter-G2 Data Requests

;;; The following macro is a stub for the soon to be implemented
;;; `def-data-server-error-code' macro.  Given a symbol, an integer, and a
;;; string, this macro will assign the given integer as an error code to that
;;; message, and will declare the given symbol as a global variable for that
;;; error code message.  It should probably done as an explicit declaration this
;;; way so we don't end up unexpectedly changing error code numbers on new
;;; releases of G2.  Disagreeing error code numbers would make it difficult to
;;; run different G2 releases on the same network.

(defvar data-server-error-code-alist nil)

(defun add-data-server-error-code (error-code-integer error-message)
  (let ((existing-message-entry?
	  (assoc error-code-integer data-server-error-code-alist)))
    (if existing-message-entry?
	(if (not (string-equalw error-message (cdr existing-message-entry?)))
	    (progn
	      #+development
	      (warn "Data server error code ~a is being changed from ~%~S~% to ~%~S"
		    error-code-integer
		    (cdr existing-message-entry?)
		    error-message)
	      (setf (cdr existing-message-entry?) error-message)))
	(with-permanent-allocation
	  (setq data-server-error-code-alist
		(cons (cons error-code-integer error-message)
		      data-server-error-code-alist))))))



(defmacro def-data-server-error-code (symbol error-code-integer error-message)
  `(progn
     (defvar ,symbol ,error-code-integer)
     (add-data-server-error-code ,error-code-integer ,error-message)))

(def-data-server-error-code no-data-server-error 0
  "The data server worked correctly.")

(def-data-server-error-code invalid-address 1
  "The information given to identify a specific datum for this data server ~
   did not designate any defined entity.")






;;;; [6.3.2] Class to Represent Inter-G2 Data Requests




;;; The block `inter-g2-data-request' is used to identify inter G2 data service
;;; requests.

;;; The function `reclaim-g2ds-list-of-evaluation-values' reclaims a given g2ds
;;; cons list of temporary constants and returns NIL.

(defun-simple reclaim-g2ds-list-of-evaluation-values (list?)
  (when list?
    (loop for trailer = nil then cons
	  for cons = list? then (cdr cons)
	  while cons
	  do
      (reclaim-if-evaluation-value (car cons))
	  finally
	    (reclaim-g2ds-list-given-tail list? trailer)))
  nil)

(def-structure inter-g2-data-request-queue
  (inter-g2-data-request-queue-head? nil
   :reclaimer reclaim-g2ds-list-of-evaluation-values)
  inter-g2-data-request-queue-tail)

(defun-simple make-inter-g2-data-request-queue-function ()
  (make-inter-g2-data-request-queue))

(def-class (inter-g2-data-request-holder block define-predicate)
  (inter-g2-data-request-priority 6)
  (inter-g2-data-request-corresponding-variable-structure nil)
  (inter-g2-data-request-incoming-value-queue
    (:funcall make-inter-g2-data-request-queue-function))
  (inter-g2-data-request-expression nil)
  (inter-g2-data-request-data-request-expression nil (type expression text)))

(def-slot-value-reclaimer inter-g2-data-request-incoming-value-queue (queue)
  (reclaim-inter-g2-data-request-queue queue))





(defun-void enqueue-g2-data-request (new-value queue)
  (let ((head? (inter-g2-data-request-queue-head? queue))
	(new-tail (g2ds-list new-value)))
    (if  head?
	 (setf (cdr (inter-g2-data-request-queue-tail queue)) new-tail)
	 (setf (inter-g2-data-request-queue-head? queue) new-tail))
    (setf (inter-g2-data-request-queue-tail queue) new-tail)))

(defun-simple dequeue-g2-data-request (queue)
  (let ((head? (inter-g2-data-request-queue-head? queue)))
    (if head?
	(let ((new-value (g2ds-pop (inter-g2-data-request-queue-head? queue))))
	  (unless (inter-g2-data-request-queue-head? queue)
	    (setf (inter-g2-data-request-queue-tail queue) nil))
	  new-value)
	nil)))

(defun-simple g2-data-request-queue-empty-p (queue)
  (if (inter-g2-data-request-queue-head? queue)
      nil
      t))
    
	     

(defun reclaim-inter-g2-data-request-holder (inter-g2-data-request-holder)
  (let ((current-block-of-dependent-frame inter-g2-data-request-holder))
    (delete-frame inter-g2-data-request-holder)))






;;;; [6.3.3] Inter-G2 Data Request Functions & Methods



(defun inter-g2-data-request-reply (request reply error-code)
  (let ((g2ds-variable-structure
	  (inter-g2-data-request-corresponding-variable-structure request)))
    (cond
      (g2ds-variable-structure			; if null the request has been cancelled!!
       (let* ((g2ds-server-interface
		(g2ds-variable-interface-name g2ds-variable-structure)))
	 (setf (g2ds-variable-error-code
		 g2ds-variable-structure)
	       error-code)
	 (cond
	   ((g2ds-variable-value-to-set?	; assume a value already enqueued for trans
	      g2ds-variable-structure)
	    (reclaim-evaluation-value
	      (g2ds-variable-value-to-set?	; reclaim old value
		g2ds-variable-structure))
	    (setf (g2ds-variable-value-to-set?	; set up new value
		    g2ds-variable-structure)
		  reply)
	    (setf (g2ds-variable-error-code	; and new error code
		    g2ds-variable-structure)
		  error-code))
	   (t
	    (setf (g2ds-variable-value-to-set?	; set up new value
		    g2ds-variable-structure)
		  reply)
	    (enqueue
	      g2ds-variable-structure
	      (g2ds-server-connection-return-queue-head g2ds-server-interface)
	      (g2ds-server-connection-return-queue-tail g2ds-server-interface)
	      g2ds-cons)))
	 (when (null (g2ds-server-connection-paused? g2ds-server-interface))
	   (return-values-to-g2ds-client g2ds-server-interface))))
      (t (reclaim-evaluation-value reply)))))

(defun-simple return-values-to-g2ds-client-task (g2ds-server-interface)
  (return-values-to-g2ds-client g2ds-server-interface))

(defun-simple g2ds-evaluation-value-type (x)
  (cond ((evaluation-sequence-p x)
	 'sequence)
	((evaluation-structure-p x)
	 'structure)
	(t
	 (evaluation-value-type x))))

(defun-allowing-unwind return-values-to-g2ds-client (g2ds-server-interface)
  (let ((g2ds-server-icp-socket
	  (g2ds-server-connection-icp-socket g2ds-server-interface)))
    (when (and g2ds-server-icp-socket
	       (icp-connection-open-p g2ds-server-icp-socket)
	       (all-icp-buffers-transmitted?
		 (icp-output-port g2ds-server-icp-socket))
	       (not (g2ds-server-connection-paused?
		      g2ds-server-interface))
	       (examine-head-of-queue
		 (g2ds-server-connection-return-queue-head g2ds-server-interface)))
      (let ((use-new-message-group-for-send-icp-enlarge-index-space-p nil))
	(writing-icp-message-group ((icp-output-port g2ds-server-icp-socket))
	  (loop with evaluation-value = nil
		as g2ds-variable-structure =
		(dequeue
		  (g2ds-server-connection-return-queue-head g2ds-server-interface)
		  (g2ds-server-connection-return-queue-tail g2ds-server-interface)
		  reclaim-g2ds-cons)
		while g2ds-variable-structure
		do
	    (setq evaluation-value
		  (g2ds-variable-value-to-set?
		    g2ds-variable-structure))
	    (with-temporary-gensym-float-creation
		return-values-to-g2ds-client
	      (send-icp-g2ds-variable-value
		g2ds-variable-structure
		(g2ds-variable-error-code g2ds-variable-structure)
		(g2ds-evaluation-value-type evaluation-value)
		evaluation-value))
	    (reclaim-evaluation-value evaluation-value)
	    (setf (g2ds-variable-value-to-set? g2ds-variable-structure) nil)
		until (time-slice-expired-p)))))))





;;; The function `initiate-inter-g2-data-service-request' takes an inter-g2-data-request
;;; structure instance.  This function will schedule a request for data service
;;; which will eventually end up calling inter-g2-data-request-reply.

(defun-simple initiate-inter-g2-data-service-request (request-structure)
  (schedule-expression-cell-execution
    request-structure
    g2ds-read-expression-cell-index
    t))

;; Added extra argument to initiate-inter-g2-data-request for network security.
;; This argument will cause serve-item-p to check for visibility when the request
;; originates from a remote G2 process.  jh, 1/30/91.

;; Remote visibility is currently not used in 3.0, and until this feature is
;; supported in cells, this argument will have to be ignored.  -jra 8/21/91





;;; The function `cancel-inter-g2-data-request' should be called by the server
;;; code to cancel any inter-g2-data-requests which have been initiated but
;;; which have not yet sent back a reply via inter-g2-data-request-reply.  It
;;; doesn't hurt anything to call this cancel function on requests which have
;;; replied, but it doesn't do any useful work either.

(defun cancel-inter-g2-data-request (request)
  (cancel-scheduled-expression-cell-execution
    request
    g2ds-read-expression-cell-index)
  (retract-consistency-analysis request))


;;; Expression-cell-updated method for the inter-g2-data-request-holder class.
;;; This handles updates to the two expression cells owned by every instance of
;;; this class, cell 0, which handles read requests, and cell 1, which handles
;;; write requests. The computation styles of the cells indicate that a network
;;; access attempt is in progress; the ensuing computations will be subject to
;;; serve-item-p, which will then check their network access configurations (an
;;; expensive operation which must only be done when we know we're doing a
;;; network access!)

(def-class-method expression-cell-updated
		  (inter-g2-data-request-holder
		    g2-cell-array index old-cache? new-cache?)

  (declare (ignore g2-cell-array old-cache?))

  (when new-cache?			
    (fixnum-case index
      (#.g2ds-read-expression-cell-index
       (inter-g2-data-request-reply
	 inter-g2-data-request-holder
	 (copy-evaluation-value new-cache?)
	 no-data-server-error))
      (#.g2ds-write-expression-cell-index
       (let* ((queue
		(inter-g2-data-request-incoming-value-queue
		  inter-g2-data-request-holder))
	      (value-to-set? (dequeue-g2-data-request queue)))
	 (when value-to-set?
	   (cond
	     ((and (framep new-cache?)
		   (frame-of-class-p new-cache? 'variable-or-parameter))
	      (let ((error-text?
		      (with-temporary-gensym-float-creation
			  expression-cell-updated-for-inter-g2-data-request
			(put-current-evaluation-value
			  new-cache?
			  (copy-evaluation-value value-to-set?)
			  nil
			  nil
			  nil))))
		(when error-text?
		  (warning-message 2
		      "The G2 to G2 data server could not set a value ~
                       for variable ~NF because: ~A"
		    new-cache?
		    error-text?)
		  (reclaim-text-string error-text?))))
	     ((evaluation-place-reference-p new-cache?)
	      (let* ((item-with-component
		       (evaluation-place-reference-block-or-symbol
			 new-cache?))
		     (component-particulars
		       (evaluation-place-reference-component-particulars
			 new-cache?))
		     (error-text?
		       (with-temporary-gensym-float-creation
			   expression-cell-updated-2
			 (conclude-into-component
			   item-with-component
			   component-particulars
			   (copy-evaluation-value value-to-set?)
			   nil
			   new-cache?))))
		(when error-text?
		  (warning-message 2
		      "The G2 to G2 data server could not set a value ~
                       for ~NV because: ~A"
		    new-cache?
		    error-text?)
		  (reclaim-text-string error-text?))))
	     (t (warning-message 2
		    "The G2 to G2 data server could not set a value for ~NA"
		  new-cache?)))
	   (unless (g2-data-request-queue-empty-p queue)
	     (schedule-expression-cell-execution
	       inter-g2-data-request-holder
	       g2ds-write-expression-cell-index
	       t)))))
      (t (error "expression-cell-updated-for-inter-g2-data-request-holder: ~
                 cell index out of range!")))))

(defun-simple initiate-inter-g2-set-value-request (g2ds-variable value-to-set)
  (let* ((request-structure
	   (g2ds-variable-server-request-structure g2ds-variable))
	 (g2-cell-array (cell-array request-structure))
	 (managed-array
	   (when g2-cell-array
	     (g2-cell-array-managed-array g2-cell-array)))
	 (expression-cell
	   (when (managed-array-p managed-array)
	     (managed-svref managed-array g2ds-write-expression-cell-index))))
    (enqueue-g2-data-request
      value-to-set
      (inter-g2-data-request-incoming-value-queue request-structure))
    (when (and (expression-cell-able-to-compute-p expression-cell)
	       (not (schedule-task-in-place-p
		      (g2-expression-cell-wake-up-task expression-cell))))
      (schedule-expression-cell-execution
	request-structure
	g2ds-write-expression-cell-index
	t))))



;; jh, 2/28/92.  Added method for denote-cell-array-element, so the G2-to-G2
;; server will report an error when unable to evaluate an expression.

(def-class-method denote-cell-array-element
		  (inter-g2-data-request-holder
		    component-particulars
		    include-block-denotation?)
  (declare (ignore inter-g2-data-request-holder
		   component-particulars
		   include-block-denotation?))
  (twrite-string "the G2-to-G2 dataserver"))

;; jh, 11/10/94.  Added cleanup method for inter-g2-data-request-holder.  Not
;; sure why this suddenly became necessary; it seems like it always would have
;; been.

(def-class-method cleanup (inter-g2-data-request-holder)
  (funcall-superior-method inter-g2-data-request-holder))



;;; The function `inter-g2-set' should be called by server code which wants to
;;; perform a SET command issued from a client G2.  The argument is an instance
;;; of the inter-g2-set-command class, containing a set-command-designation and
;;; a set-command-numeric-value.  This value may only be a number (fixnum or
;;; gensym-float), since the SET action will only send numbers.  This function
;;; will return a data server error code as its value, with a value of zero
;;; meaning "no error".

;;; The only possible error code that this function can return is invalid
;;; address.

;;; Note that since the SET action discards the expiration of the value it
;;; computed, it makes no sense to pass the expiration through to the variable
;;; receiving the value.  Therefore, the expiration of the temporary constant is
;;; ignored.






;;;; [6.4] Slot-Putters for G2-to-G2 Data Interface Capability

(def-slot-putter icp-connection-specification
    (interface-object icp-connection-forms initializing-p)

  (unless (get-slot-value-if-any interface-object
				 'g2ds-server-connection-structure)
    (let ((interface-was-connected-p
	    (and (not initializing-p)
		 (or (active-p interface-object)
		     (g2-to-g2-interface-connects-while-inactive-p
		       interface-object)))))
      (when interface-was-connected-p
	(body-of-deactivate-for-g2-to-g2-data-interface interface-object)
	(let ((connection-spec? (car icp-connection-forms)))
	  (when connection-spec?
	    (activate-g2ds-interface-with-connection-spec
	      interface-object
	      connection-spec?)))))

    (put-attribute-value
      interface-object
      'icp-connection-specification
      icp-connection-forms
      initializing-p)))

;; jh, 10/24/91.  Added "none" as an option for icp-connection-specification.
;; With the advent of the "change the text" action, the user is more likely to
;; want to set and clear the icp-connection-specification while g2 is running.  In
;; addition, caused G2 to emit warning messages only when it can't connect to a
;; g2-to-g2 interface which has a connection specification, since the user may
;; want to start a kb with several unconnected interface and change the text to a
;; true connection specification later.  Analogous changes were made to GSI
;; interface objects.

;; jh, 2/28/92.  To do - decide if we want to forward chain on
;; icp-connection-specification as well as interface-status.



;;; The `slot putter for the interface-status' of an object with the
;;; g2-to-g2-data-interface capability is needed to invoke forward
;;; chaining.  This system attribute can be referenced by the user in
;;; rules.

;; Added, cpm, 2/1/92.

(def-slot-putter interface-status (interface-object status-symbol initializing?)
  (declare (ignore initializing?))
  (let ((old-status (get-slot-value interface-object 'interface-status)))
    (set-slot-value interface-object 'interface-status status-symbol)
    (invoke-rules-for-attribute-change-chaining
      interface-object 'interface-status old-status nil)
    (values status-symbol nil)))






;;;; [6.5] Grammar for G2-to-G2 Data Interface Capability

(add-grammar-rules
  '((g2ds-host-name unreserved-symbol)
    (g2ds-network-task-name unreserved-symbol)
    (g2ds-tcp-ip-port-number integer)
    (g2ds-file-pathname whole-string)
    (host-name-string whole-string)
    (icp-connection-specification 'none)
    (icp-connection-specification ('local 'emulator)
                                  (localnet localhost))
    (icp-connection-specification ('tcp-ip 'host host-name-string
				   'port-number g2ds-tcp-ip-port-number)
				  (tcp-ip 3 5 nil))
    (icp-connection-specification ('tcp-ip 'host host-name-string
				   'port-number g2ds-tcp-ip-port-number 'secure yes-or-no)
				  (tcp-ip 3 5 7))
    ))

(def-slot-value-compiler icp-connection-specification (parse-result)
  (cond
    ((eq 'none parse-result) nil)
    (t (valid-icp-connection-specification-from-parse parse-result t))))






;;;; [6.6] Capability Activator for G2-to-G2 Interfaces

;;; All G2DS interfaces will be activated and connections made when starting a kb.
;;; When resetting a kb the interface connections will be dropped.
;;; Actions taken when activating a G2DS interface:
;;;
;;;  1. build the groups-to-process-queue-header structure and put in object slot.
;;;  2. make connection to remote process if possible.
;;;  3. if connection succeeds send initialize message to remote process else
;;;         report error to user use warning level 2?




;; jh, 9/18/91.  Extracted activate-g2ds-interface-with-extant-socket because it
;; shares some functionality with reset-g2ds-icp-connection now that we can change
;; the text of the icp-connection-specification while G2 is running.



(defun-void g2ds-begin-collecting-data-on-appropriate-variables
    (interface-name)
  (when (or system-has-paused system-is-running)
    (let ((begin-collecting-data-list
	    (loop for variable being class-instance of 'variable
		  when
		    (and (active-p variable)
			 (g2-to-g2-data-service-p variable)
			 (eq (get-slot-value-if-any
			       variable
			       'g2-to-g2-interface-name)
			     interface-name))
		    collect variable using g2ds-cons)))
      (loop with g2ds-variables? = begin-collecting-data-list
	    while g2ds-variables?
	    do
	(with-temporary-gensym-float-creation
	    g2ds-begin-collecting-data-on-appropriate-variables 
	  (loop repeat iterations-for-g2ds-temporary-float-processing
		for variable? = (pop g2ds-variables?)
		while variable?
		do
	    (let* ((g2ds-variable-structure
		     (get-slot-value-if-any
		       variable?
		       'g2ds-variable-structure))
		   (data-collection-interval?
		     (g2ds-variable-collection-interval?
		       g2ds-variable-structure)))
	      (clear-queued-by-local-data-server variable?)
	      (when (and data-collection-interval?
			 (evaluation-quantity-> data-collection-interval? 0))
		(g2ds-begin-collecting-data
		  variable?
		  data-collection-interval?))))))
      (reclaim-g2ds-list begin-collecting-data-list))))

(def-system-variable icp-sockets-now-initializing-g2ds G2DS nil)

;; this should be named "finish-activating-g2ds-interface-with-connected-socket"
;; because that's what it does now.
(defun-allowing-unwind activate-g2ds-interface-with-extant-socket
		       (g2ds-interface-object icp-socket)

  (let ((g2ds-interface-structure
	  (get-slot-value g2ds-interface-object 'g2ds-interface-structure))
	(g2ds-interface-countdown-timer-limit
	  (get-slot-value-if-any
	    g2ds-interface-object
	    'interface-timeout-period)))

    ;; jh, 12/18/92.  If push instead of pushnew is used, multiple pointers to
    ;; the same interface frame accumulate in list-of-all-g2ds-interfaces,
    ;; causing problems when the interface object is deleted.  To be specific,
    ;; handle-g2ds-shut-down-client crashes when it calls get-slot-value on the
    ;; reclaimed frame it extracts from list-of-all-g2ds-interfaces.
    (g2ds-pushnew g2ds-interface-object list-of-all-g2ds-interfaces)

    ;; remote side is down or clogged (see INT or TELESTUBS).  For now, we
    ;; simply want to write to the socket every once in a while, so the remote
    ;; side can detect a broken socket (see note above).

    (initialize-i-am-alive-info icp-socket 'g2ds-connection-clogged-p)

    (when (not (numberp g2ds-interface-countdown-timer-limit))
      (setq g2ds-interface-countdown-timer-limit
	    default-g2ds-interface-countdown-timer-limit))

    (setf (g2ds-interface-countdown-timer g2ds-interface-structure)
	  (fixnum-time-interval
	    (*f 1000 g2ds-interface-countdown-timer-limit)))
    (setf (g2ds-interface-countdown-timer-limit
	    g2ds-interface-structure)
	  (fixnum-time-interval
	    (*f 1000 g2ds-interface-countdown-timer-limit)))

    ;; send g2ds-initialize-server and return-g2ds-version
    (g2ds-send-initial-message-group icp-socket)
    ;; receive return-g2ds-version
    ;;   initialization continues when handler for return-g2ds-version calls
    ;;   g2ds-begin-collecting-data-on-appropriate-variables.
    ))

;; blm, ac, & jh, 7/12/90.  Added a connection-loss callback function for
;; G2-to-G2 sockets.  It is registered in the capability activator for g2ds
;; interfaces.  See note below, under handle-g2ds-shut-down-client.

(defun-void finalize-g2ds-connection (g2-to-g2-data-interface icp-socket)

  (let*-while-true ((g2ds-interface-structure (get-slot-value g2-to-g2-data-interface
							      'g2ds-interface-structure)))
    (setf (g2ds-interface-timed-out-p g2ds-interface-structure) nil)
    (setf (g2ds-interface-waiting-for-response-p g2ds-interface-structure) nil))

  (deregister-all-icp-callbacks 'icp-connect icp-socket)

  ;; set up the real connection loss callback, in place of the transitional
  ;; one for connection negotiation. -ncc, 11 Jun 1995 
  (deregister-all-icp-callbacks 'icp-connection-loss icp-socket)
  (register-icp-callback 'icp-connection-loss 'handle-g2ds-shut-down-client icp-socket)
  (activate-g2ds-interface-with-extant-socket g2-to-g2-data-interface icp-socket))


(defun-void g2ds-connect-callback (icp-socket)
  (let* ((g2ds-interface-frame (enclosing-interface-frame? icp-socket)))
    ;; check up on state of ICP socket:
    (cond
      ((memq icp-socket active-icp-sockets)
       (case (icp-connection-state icp-socket)
	 (#.icp-connection-running ;finalize the connection at this protocol level
	  (finalize-g2ds-connection g2ds-interface-frame icp-socket))
	 (#.icp-connection-closed ;connection negotiation failed, warn
	  (change-g2ds-interface-status-throughout
	    g2ds-interface-frame
	    'attempting
	    'failed)
	  (write-warning-message 3
	    (tformat
	      "Cannot make ICP connection for G2-to-G2 data interface ~NF"
	      g2ds-interface-frame)))
	 (otherwise
	  (change-g2ds-interface-status-throughout
	    g2ds-interface-frame
	    'attempting
	    'failed)
	  (write-warning-message 1 ;[ncc:] ??? error? or is silence more apropos?
	    (tformat
	      "Cannot make ICP connection for G2-to-G2 data interface ~NF ~
              - failed to finalize connection."
	      g2ds-interface-frame)))))
      (t
       (change-g2ds-interface-status-throughout
	 g2ds-interface-frame
	 'attempting
	 'failed)
       (write-warning-message 3
	 (tformat
	   "Cannot make ICP connection for G2-to-G2 data interface ~NF"
	   g2ds-interface-frame))))))



;; activate-g2ds-interface-with-connection-spec abstracted. -ncc, 25 Jul 1995


;;;Can't make SSL connections to self; handshake failure.  Disallow.
(defun secure-connection-to-self? (interface-configuration)
  (let ((foreign-port (third interface-configuration))
	(foreign-secure (fourth interface-configuration))
	(result-value nil))
    (multiple-value-bind (host-name port-list)
	(get-raw-network-info)
      (reclaim-text-string host-name)
      (loop for (network-type local-address local-secure) in port-list do
	(if (and local-secure foreign-secure)
	    (multiple-value-bind (local-port token-type)
		(read-from-text-string local-address)
	      (if (and (eq token-type 'integer)
		       (=f local-port foreign-port))
		  (setq result-value t)))))
      (loop for (network-type local-address local-secure) in port-list do
	(reclaim-text-string network-type)
	(reclaim-text-string local-address))
      (reclaim-gensym-list port-list))
    result-value))

(defun activate-g2ds-interface-with-connection-spec
    (g2-to-g2-data-interface interface-configuration)
  (let ((g2ds-interface-status-slot-value
	  (get-slot-value-if-any
	    g2-to-g2-data-interface
	    'interface-status))
	(config-copy (copy-list-using-gensym-conses interface-configuration)))

    (when (secure-connection-to-self? config-copy)
      (setf (fourth config-copy) nil)
      (with-interface-warning-message-level g2-to-g2-data-interface
	(write-warning-message 2
	  (tformat "Illegal secure connection to self on interface ~NF; using non-secure connection."
		   g2-to-g2-data-interface))))

    (change-g2ds-interface-status-throughout
      g2-to-g2-data-interface
      g2ds-interface-status-slot-value
      'attempting)

    (let ((icp-socket?
	    (make-icp-connection
	      config-copy
	      'g2 nil
	      (or (check-for-number-or-default-or-none
		    (get-slot-value-if-any g2-to-g2-data-interface
					   'interface-initialization-timeout-period))
		  (check-for-number-or-default
		    (get-slot-value-if-any g2-to-g2-data-interface
					   'interface-timeout-period))
		  default-g2ds-interface-countdown-timer-limit))))

      (reclaim-gensym-list config-copy)
      (when icp-socket?
	(setf (icp-socket-listener-client? icp-socket?) 'g2)
	(setf (icp-connection-succeeds-at-first-message-p icp-socket?) nil)
	;; Register a callback to clean up if the connect eventually
	;; fails. -ncc, 11 Jun 1995
	(register-icp-callback 'icp-connection-loss
			       'handle-g2ds-connect-attempt-failure
			       icp-socket?)
	(setf (enclosing-interface-frame? icp-socket?) g2-to-g2-data-interface)
	(frame-serial-number-setf (enclosing-interface-frame-serial-number icp-socket?)
				  (frame-serial-number g2-to-g2-data-interface)))
      
      (set-slot-value g2-to-g2-data-interface 'g2ds-interface-structure
		      (make-g2ds-interface icp-socket?))
      (when icp-socket?
	(when (get-slot-value-if-any g2-to-g2-data-interface
				     'disable-interleaving-of-large-messages)
	  (setf (icp-socket-does-not-allow-resumability icp-socket?) 'requested))
	(setup-network-connection-for-connect icp-socket? 'g2ds-connect-callback)))))

(defun-void activate-g2-to-g2-data-interface-with-or-without-configuration
    (g2-to-g2-data-interface)
  (unless (get-slot-value-if-any g2-to-g2-data-interface
				 'g2ds-server-connection-structure)
    (let ((interface-configuration?
	    (car (get-slot-value-if-any
		   g2-to-g2-data-interface
		   'icp-connection-specification))))
      (when (and interface-configuration?
		 (not (eq 'decnet (car interface-configuration?))))
	(activate-g2ds-interface-with-connection-spec
	  g2-to-g2-data-interface
	  interface-configuration?)))))

(def-class-method activate (g2-to-g2-data-interface)

  (unless (runs-while-inactive-p g2-to-g2-data-interface)
    (activate-g2-to-g2-data-interface-with-or-without-configuration
      g2-to-g2-data-interface))

  ;; should this really be done when there's no interface-configuration?
  ;; -ncc, 21 Jul 1995.
  ;; jh, 11/12/96.  Yes, because an interface running while inactive needs to begin
  ;; dataservice at this point.
  (when (or system-has-paused system-is-running)
    (unless (get-slot-value-if-any g2-to-g2-data-interface
				   'g2ds-server-connection-structure)
      (schedule-data-server-accept-data-calls)))

  (funcall-superior-method g2-to-g2-data-interface))

(def-class-method manually-enable (g2-to-g2-data-interface)
  ;; If the connection does not persist during reset, it will not be made here,
  ;; but rather in the activate method.
  (when (runs-while-inactive-p g2-to-g2-data-interface)
    (activate-g2-to-g2-data-interface-with-or-without-configuration
      g2-to-g2-data-interface))
  ;; Calling the superior must come last to avoid double activation.
  (funcall-superior-method g2-to-g2-data-interface))

(defun-simple g2-to-g2-icp-socket-connected-p (g2-to-g2-data-interface)
  (let* ((interface-structure?
	   (get-slot-value-if-any
	     g2-to-g2-data-interface
	     'g2ds-interface-structure))
	 (connected-p	   
	   (and interface-structure?
		(g2ds-interface-socket interface-structure?))))
    connected-p))

(def-class-method note-ancestor-manually-enabled (g2-to-g2-data-interface)
  (when (runs-while-inactive-p g2-to-g2-data-interface)
    (unless (manually-disabled-p g2-to-g2-data-interface)
      (unless (g2-to-g2-icp-socket-connected-p g2-to-g2-data-interface)
	(activate-g2-to-g2-data-interface-with-or-without-configuration
	  g2-to-g2-data-interface)))))

(defvar maintaining-g2ds-interface-status-changed-p nil)
(defvar g2ds-interface-status-changed-p)

(def-class-method activate-if-possible-and-propagate (g2-to-g2-data-interface)
  (unless (active-p g2-to-g2-data-interface)
    (let ((old-status (get-slot-value g2-to-g2-data-interface 'interface-status))
	  (maintaining-g2ds-interface-status-changed-p t)
	  (g2ds-interface-status-changed-p nil))
      (funcall-superior-method g2-to-g2-data-interface)
      (when g2ds-interface-status-changed-p
	(let ((*current-computation-frame* g2-to-g2-data-interface))
	  (invoke-rules-for-attribute-change-chaining
	    g2-to-g2-data-interface 'interface-status old-status nil))))))

;; When a G2DS interface is deleted, divorce it from any ICP interface object
;; which it may be attached to.  -ncc, 21 Jul 1995

(def-class-method cleanup (g2-to-g2-data-interface)
  (let ((server-connection (get-slot-value-if-any g2-to-g2-data-interface
						  'g2ds-server-connection-structure)))
    (cond (server-connection
	   (set-slot-value g2-to-g2-data-interface 'g2ds-server-connection-structure nil)
	   (let ((interface-icp-socket?
		   (g2ds-server-connection-icp-socket server-connection)))
	     (when (and interface-icp-socket?
			(not (=f (icp-connection-state interface-icp-socket?)
				 icp-connection-closed)))
	       (setf (enclosing-interface-frame? interface-icp-socket?) nil)
	       (shutdown-icp-socket-connection interface-icp-socket?))))
	  (t
	   (when (g2-to-g2-interface-connects-while-inactive-p g2-to-g2-data-interface)
	     (body-of-deactivate-for-g2-to-g2-data-interface g2-to-g2-data-interface))
	   (let* ((g2ds-interface-structure?
		    (get-slot-value-if-any
		      g2-to-g2-data-interface
		      'g2ds-interface-structure)))
	     (when g2ds-interface-structure?
	       (let* ((interface-icp-socket?
			(g2ds-interface-socket g2ds-interface-structure?)))
		 (when interface-icp-socket? 
		   (setf (enclosing-interface-frame? interface-icp-socket?) nil))
		 (setf (g2ds-interface-socket g2ds-interface-structure?) nil)))))))
  (funcall-superior-method g2-to-g2-data-interface))



;;;; [6.7] Handler for G2-to-G2 Client Shutdown

;; (blm, ac, & jh, 7/12/90)

;; There was a major, "sleeper" bug waiting to happen in both GSI and G2-to-G2
;; data service.  When an ICP socket failed, process-icp-sockets would recycle it,
;; even though a pointer to the socket was left on the enclosing interface frame.
;; This caused bizarre behavior when the socket was reincarnated as another ICP
;; socket, probably due to a mixture of gsi and g2-to-g2 ports in the same socket.
;; The behavior included mysterious crashing of RPC extensions process and
;; inappropriate messages at G2 reset time.

;; The fix is to use the connection-loss callback facility to register a function
;; which will get called when the socket fails.  This callback function, named
;; handle-g2ds-shut-down-client, will correctly clean things up.  Cleanup here
;; means that the enclosing interface frame's pointer to the socket must be set to
;; nil and the enclosed ports of the socket must be shut down in a
;; platform-specific manner using shutdown-icp-socket-connection.  As a matter of
;; fact, the callback function almost completely subsumes the duties of the
;; capability deactivator for the interface.

;; Handle-g2ds-shut-down-client was neglecting to recycle things when the
;; interface had no icp-socket.  Such a thing happens when the interface fails
;; to make a connection.  This function is called for two events: normal
;; g2-to-g2 capability deactivation (in the def-capability-deactivator for
;; g2ds-interface-configuration) and abnormal g2-to-g2 connection loss (via a
;; call to register-icp-connection-loss-callback when the capability is
;; activated).  Handle-shut-down-g2ds-client still should contain all code
;; shared between normal and abnormal shutdowns.  Added optional arguments to
;; allow the g2ds-interface-object to be passed in the event of a normal
;; deactivation.  In this case we don't care if we find an icp-socket in the
;; g2ds-interface-object -- we still want to recycle everything else.  Analogous
;; changes have been made in the gsi interface.  (jh, 9/13/90)

;; Note that the enclosing-interface-frame? of the icp-socket will be nil in
;; case of normal shutdown (i.e. as result of deactivate method).  it will only
;; contain a pointer back to the frame if an error caused the connection to be
;; broken, thus this is an implicit check for an errorful shutdown, and we can
;; always change the interface status to failed when this pointer is nonnull.
;; -ncc & jh, 25 Jul 1995 

(defun-allowing-unwind handle-g2ds-shut-down-client
    (icp-socket clean?)
  (declare (ignore clean?))
  
  ;; acquire interface frame and structure

  (let* ((g2ds-interface-object? (enclosing-interface-frame? icp-socket))
	 (valid-interface-p
	   (and (framep-function g2ds-interface-object?)
		(frame-has-not-been-reprocessed-p
		  g2ds-interface-object?
		  (enclosing-interface-frame-serial-number icp-socket))))
	 (g2ds-interface-structure?
	   (when valid-interface-p
	     (get-slot-value-if-any g2ds-interface-object? 'g2ds-interface-structure)))
	 (reason-for-shutdown? (reason-for-shutdown? icp-socket)))
    (when (and reason-for-shutdown?
	       valid-interface-p
	       (not (eq reason-for-shutdown?
			'eof-awaiting-shutdown-acknowledgement)))
      (with-interface-warning-message-level g2ds-interface-object?
	(write-warning-message 2
	  (tformat "G2-to-G2 connection lost for interface ~NF, error was ~a."
		   g2ds-interface-object?
		   reason-for-shutdown?))))

    ;; detach this socket from the enclosing interface frame:
    (setf (enclosing-interface-frame? icp-socket) nil)

    ;; Remove from list of initializing sockets if necessary.
    (setq icp-sockets-now-initializing-g2ds
	  (delete-g2ds-element icp-socket icp-sockets-now-initializing-g2ds))
    
    (when g2ds-interface-object?

      ;; reclaim interface structure enclosing the socket
      ;; jh, 5/8/95.  Seems to be reclaimed already when loading a new KB with a
      ;; paused G2-to-G2 interface, hence the g2ds-interface-p test,
      (when (g2ds-interface-p g2ds-interface-structure?)

	(setf (g2ds-interface-socket g2ds-interface-structure?) nil)  ; paranoia

	(reclaim-g2ds-interface g2ds-interface-structure?))

      (set-slot-value g2ds-interface-object? 'g2ds-interface-structure nil)

      (setq list-of-all-g2ds-interfaces
 	    (delete-g2ds-element g2ds-interface-object? list-of-all-g2ds-interfaces))

      (change-g2ds-interface-status-throughout
	g2ds-interface-object?
	(get-slot-value-if-any g2ds-interface-object? 'interface-status)
	'failed))))





(defun-allowing-unwind handle-g2ds-connect-attempt-failure (icp-socket clean?)
  (declare (ignore clean?))
  (let* ((g2ds-interface-frame? (enclosing-interface-frame? icp-socket)))
    (when (and (framep g2ds-interface-frame?)
	       (frame-has-not-been-reprocessed-p
		 g2ds-interface-frame?
		 (enclosing-interface-frame-serial-number icp-socket)))

      (let* ((g2ds-interface-structure?
	       (get-slot-value-if-any g2ds-interface-frame? 'g2ds-interface-structure))
	     (reason-for-shutdown? (reason-for-shutdown? icp-socket)))

	(when (and reason-for-shutdown?
		   (not (eq reason-for-shutdown?
			    'eof-awaiting-shutdown-acknowledgement)))
	  (with-interface-warning-message-level g2ds-interface-frame?
	    (write-warning-message 3
	      (tformat "G2-TO-G2 connection attempt failed for interface ~NF, error was ~a."
		       g2ds-interface-frame?
		       reason-for-shutdown?))))
	
	;; Reclaim interface structure enclosing the socket -- I *think* the
	;; g2ds-interface-p check is unnecessary here.  -ncc, 21 Jul 1995
	(when (g2ds-interface-p g2ds-interface-structure?)
	  (reclaim-g2ds-interface g2ds-interface-structure?)
	  (set-slot-value g2ds-interface-frame? 'g2ds-interface-structure nil))

	;; Change interface status.
	(change-g2ds-interface-status-throughout
	  g2ds-interface-frame?
	  (get-slot-value-if-any g2ds-interface-frame? 'interface-status)
	  'failed)))))



;;; The function `shut-down-g2ds-clients-for-clear-kb' is called with no arguments
;;; when a G2-to-G2 server clears its KB.  This function synchronously shuts down
;;; all ICP sockets used for G2-to-G2 dataservice, so that when it returns, all
;;; inter-g2-data-request-holder frames may safely be reclaimed by the remainder
;;; of clear-kb.

(defun shut-down-g2ds-clients-for-clear-kb ()
  (let ((copy-of-g2ds-server-connections
	  ;; Handle-g2ds-shut-down-server side-effects g2ds-server-connections,
	  ;; hence the copy.
	  (copy-list-using-g2ds-conses g2ds-server-connections)))
    (loop for g2ds-server-connection in copy-of-g2ds-server-connections
	  do (let ((icp-socket?
		     (g2ds-server-connection-icp-socket g2ds-server-connection)))
	       (when icp-socket?
		 (shutdown-icp-socket-connection icp-socket?)))
	  finally
	    (reclaim-g2ds-list copy-of-g2ds-server-connections))))






;;;; [6.8] Handler for G2-to-G2 Server Shutdown

;;; The server will shut down the connection when the client issues the
;;; G2-ds-shut-down-server message.  To shut down the server-client connection
;;;   1. close the icp socket.
;;;   2. reclaim all the in-progress return values

;; The ICP message g2ds-shut-down-server is handled with
;; shutdown-icp-socket-connection instead of handle-G2ds-shut-down-server.
;; Otherwise handle-G2ds-shut-down-server gets called twice, [???  once by the
;; handler and once by the callback, ???] resulting in the following problem.
;; Handle-G2ds-shut-down-server contains a call to get-g2ds-server-connection
;; which itself contained a (now fixed) bug.  The second time
;; get-g2ds-data-server was called from handle-G2ds-shut-down-server, it would
;; return the wrong g2ds-server-connection for the given icp-socket.  This would
;; cause the remainder of handle-G2ds-shut-down-server to break.  (jh per blm,
;; 3/20/90)

;; It isn't clear that this change is needed or even safe.  It might be
;; sufficient simply to fix the bug in get-g2ds-server-connection.  (agh & jh,
;; 3/21/90)

(defun handle-g2ds-shut-down-server (icp-socket clean?)
  (declare (ignore clean?))
  (let ((g2ds-server-connection?
         (get-g2ds-server-connection icp-socket))
	(interface-frame?
	  (enclosing-interface-frame? icp-socket))
	(interface-frame-serial-number?
	  (enclosing-interface-frame-serial-number icp-socket)))
    (when g2ds-server-connection?
      (when (and (framep interface-frame?)
		 (frame-has-not-been-reprocessed-p
		   interface-frame?
		   interface-frame-serial-number?))
	(let ((reason-for-shutdown? (reason-for-shutdown? icp-socket)))
	  (when (and reason-for-shutdown?
		     (not (eq reason-for-shutdown?
			      'eof-awaiting-shutdown-acknowledgement)))
	    (with-interface-warning-message-level interface-frame?
	      (write-warning-message 2
		(tformat "G2-to-G2 connection lost for server interface ~NF, error was ~a."
			 interface-frame?
			 reason-for-shutdown?)))))
	(delete-frame interface-frame?)
	(setf (enclosing-interface-frame? icp-socket) nil))
      (cancel-task (g2ds-server-flush-return-data-task g2ds-server-connection?))
      (reclaim-g2ds-list
	(g2ds-server-connection-return-queue-head g2ds-server-connection?))
      (setf (g2ds-server-connection-return-queue-head g2ds-server-connection?)
	    nil)
      (setf (g2ds-server-connection-return-queue-tail g2ds-server-connection?)
	    nil)
      (setf (g2ds-server-connection-icp-socket g2ds-server-connection?) nil)
      (loop for g2ds-variable
		in (g2ds-server-connection-variables g2ds-server-connection?)
	    as request-structure = (g2ds-variable-server-request-structure
				     g2ds-variable)
	    as temporary-value-to-return? = (g2ds-variable-value-to-set?
					      g2ds-variable)
	    do
	(cancel-inter-g2-data-request request-structure)
	(cancel-task
	  (g2ds-variable-scheduled-collection-task g2ds-variable))
	(setf (inter-g2-data-request-corresponding-variable-structure
		request-structure)
	      nil)

	;; deactivate the expression-cells associated with this
	;; request structure, and ??? reclaim them.
	(deactivate-g2-cell-array (cell-array request-structure))
	
	(reclaim-inter-g2-data-request-holder request-structure)
	(setf (g2ds-variable-server-request-structure g2ds-variable)
	      nil)
	(when temporary-value-to-return?
	  (reclaim-evaluation-value temporary-value-to-return?))
	(reclaim-g2ds-expression
	  (g2ds-variable-expression g2ds-variable))
	(reclaim-g2ds-expression
	  (g2ds-variable-expression-text g2ds-variable))
	(setf (g2ds-variable-expression g2ds-variable) nil)
	(setf (g2ds-variable-expression-text g2ds-variable) nil)

	(remove-icp-object-from-index-space
	  g2ds-variable
	  (icp-input-port icp-socket)
	  (g2ds-variable-remote-icp-object-index g2ds-variable)
	  'standard-icp-object-index-space)

	(setf (g2ds-variable-value-to-set? g2ds-variable) nil)
	(reclaim-g2ds-variable g2ds-variable))
      (reclaim-g2ds-list
	(g2ds-server-connection-variables g2ds-server-connection?))
      (setf (g2ds-server-connection-variables g2ds-server-connection?)
	    nil)
      (setq g2ds-server-connections
	    (delete-g2ds-element g2ds-server-connection?
				 g2ds-server-connections))
      (reclaim-g2ds-server-connection g2ds-server-connection?))))






;;;; [6.9] Capability Deactivator for G2-to-G2 Interfaces

;;; Shut down the G2DS interface by clearing any queued requests for data, then
;;; shut down the ICP connection.

(defun-void body-of-deactivate-for-g2-to-g2-data-interface
    (g2-to-g2-data-interface)
  (unless (get-slot-value-if-any g2-to-g2-data-interface
				 'g2ds-server-connection-structure)
    (let* ((interface-structure?
	     (get-slot-value-if-any
	       g2-to-g2-data-interface
	       'g2ds-interface-structure))
	   (interface-icp-socket?
	     (and interface-structure?
		  (g2ds-interface-socket interface-structure?))))

      (when interface-icp-socket?
	;; Kick off shutdown protocol, detach from socket.  note that in GSI, the
	;; backlink is maintained until shutdown finalizes.  This should be done
	;; here, as well, but not in a bug fixing rev. -ncc, 24 Jul 1995
	(flush-and-shutdown-icp-socket interface-icp-socket?)
	(setf (enclosing-interface-frame? interface-icp-socket?) nil)
	(setf (g2ds-interface-socket interface-structure?) nil)
	(when (g2ds-interface-p interface-structure?)
	  (reclaim-g2ds-interface interface-structure?))
	(set-slot-value g2-to-g2-data-interface 'g2ds-interface-structure nil)
	(setq list-of-all-g2ds-interfaces
	      (delete-g2ds-element
		g2-to-g2-data-interface
		list-of-all-g2ds-interfaces)))
      (change-g2ds-interface-status-throughout
	g2-to-g2-data-interface
	(get-slot-value-if-any g2-to-g2-data-interface 'interface-status)
	'inactive))))

(def-class-method deactivate (g2-to-g2-data-interface)
  (unless (get-slot-value-if-any g2-to-g2-data-interface
				 'g2ds-server-connection-structure)
    (cond
      ((runs-while-inactive-p g2-to-g2-data-interface)
       (when (g2-to-g2-icp-socket-connected-p g2-to-g2-data-interface)
	 (change-g2ds-interface-status-throughout
	   g2-to-g2-data-interface
	   (get-slot-value-if-any g2-to-g2-data-interface 'interface-status)
	   'connected)))
      (t (body-of-deactivate-for-g2-to-g2-data-interface
	   g2-to-g2-data-interface))))
  (funcall-superior-method g2-to-g2-data-interface))

(def-class-method manually-disable (g2-to-g2-data-interface)
  (funcall-superior-method g2-to-g2-data-interface)
  (when (runs-while-inactive-p g2-to-g2-data-interface)
    (body-of-deactivate-for-g2-to-g2-data-interface g2-to-g2-data-interface)))

(def-class-method note-ancestor-not-activatable (g2-to-g2-data-interface)
  (funcall-superior-method g2-to-g2-data-interface)
  (unless (active-p g2-to-g2-data-interface)
    (when (runs-while-inactive-p g2-to-g2-data-interface)
      ;; The manually-disable method handles the case where the interface itself
      ;; (as opposed to a superior) is disabled.
      (unless (manually-disabled-p g2-to-g2-data-interface)
	(when (g2-to-g2-icp-socket-connected-p g2-to-g2-data-interface)
	  (body-of-deactivate-for-g2-to-g2-data-interface
	    g2-to-g2-data-interface))))))



;; Modified the deactivator for g2ds interfaces to call the connection-loss
;; handler where code can be shared.  Currently, this is everywhere except
;; setting the status attribute, which should be different between naturally
;; deactivated interfaces and those which failed while G2 was still running.
;; (blm, jh, & ac, 7/12/90)

;; The capability deactivator for g2-to-g2-data-interface capability now calls
;; handle-g2ds-shut-down-client with a different number of arguments.  (jh,
;; 9/17/90)





;;;; [6.10] Interface Status

;; Note that the attempting status is possible from every other status, since
;; the capability activator can be called at any time (from an edit, for
;; example).

(defvar g2ds-interface-transition-table
	'(
	  (inactive   attempting
		      )
	  (attempting inactive
		      connected
		      failed
		      )
	  (connected  inactive
	              failed		; new transition: network security causes this. -ncc, 6 Jan 1995 
		      running
		      reset
		      attempting
		      )
	  (failed     inactive
		      attempting
		      )
	  (running    inactive
		      failed		; if peer doesn't support the shutdown protocol. -ncc, 24 Jul 1995 
		      timed-out
		      reset
		      attempting
		      paused
		      abort		; if peer has paused by an internal error. -binghe, 13 May 2014
		      )
	  ;; Note that "paused" can refer to either the client or the server.
	  ;; Consider differentiating.
	  (paused     inactive
		      failed		; if peer doesn't support the shutdown protocol. -ncc, 24 Jul 1995 
		      running
		      reset
		      attempting
		      )
	  (abort      inactive		; `abort' has the same transition as `paused'. -binghe, 13 May 2014
		      failed
		      running
		      reset
		      attempting
		      )
	  (reset      inactive
		      failed		; if peer doesn't support the shutdown protocol. -ncc, 24 Jul 1995 
		      timed-out
		      running
		      attempting
		      )
	  (timed-out  inactive
		      failed		; if peer doesn't support the shutdown protocol. -ncc, 24 Jul 1995 
		      running
		      reset
		      attempting
		      )
	  ;; jh, 10/8/92.  The not-connected tag is a holdover from 3.0 and
	  ;; earlier.  This tag was often confused with no-connection, so the
	  ;; tag not-connected is now the tag inactive and the tag no-connection
	  ;; is now the tag failed.
	  (not-connected attempting)
	  ))

;; jh, 10/8/92.  Added change-g2ds-interface-status-throughout to
;; monitor status changes for G2-to-G2 interfaces.  It changes the status of
;; both the frame and the g2ds-interface-structure it encloses.

(defun change-g2ds-interface-status-throughout
    (g2ds-interface-frame old-status new-status)
  (unless (eq old-status new-status)

    #+hellfreezes
    (let ((transition-entry? (assq old-status g2ds-interface-transition-table)))
      (cond
	(transition-entry?
	 (unless (memq new-status (rest transition-entry?))
	   (cerror "Continue, changing status anyway"
		   "CHANGE-STATUS-OF-G2DS-INTERFACE-FRAME: ~
                    Attempt to change to unexpected interface status ~a"
		   new-status)))
	(t (cerror "Continue, changing status anyway"
		   "CHANGE-STATUS-OF-G2DS-INTERFACE-FRAME: ~
                    Unknown interface status ~a encountered"
		   old-status))))

    (when maintaining-g2ds-interface-status-changed-p
      (setq g2ds-interface-status-changed-p t))
    (let ((*current-computation-frame* g2ds-interface-frame))

      (change-slot-value g2ds-interface-frame 'interface-status new-status)

      (let ((secure-p 
	      (if (eq new-status 'server)
		  (and (g2ds-server-connection-structure g2ds-interface-frame)
		       (icp-connection-is-secure
			 (g2ds-server-connection-icp-socket
			   (g2ds-server-connection-structure g2ds-interface-frame))))
		  (and (g2ds-interface-structure g2ds-interface-frame)
		       (icp-connection-is-secure
			 (g2ds-interface-socket (g2ds-interface-structure g2ds-interface-frame)))))))
	(change-slot-value g2ds-interface-frame 'interface-is-secure secure-p))

      (let ((g2ds-interface-structure?
	      (get-slot-value-if-any
		g2ds-interface-frame
		'g2ds-interface-structure)))
	(when g2ds-interface-structure?
	  (setf (g2ds-interface-status g2ds-interface-structure?)
		new-status))))))



#+development
(defun skim-index-spaces-of-g2-interface-and-peer (g2-interface &optional (few 30))
  (loop with interface-icp-socket
	  = (g2ds-interface-socket (g2ds-interface-structure g2-interface))
	for socket in active-icp-sockets
	do
    (if (eq socket interface-icp-socket)
	(format t "~&interface socket:~%")
	(format t "~&peer socket:~%"))
    (skim-index-spaces-of-icp-socket socket few)))


;;;; [7] G2-to-G2 Variables

;; co-topic to G2-to-G2 Interfaces ...






;;;; [7.1] Slot-Putters for G2-to-G2 Dataservice Capability

;;; Changing the name of the g2-to-g2-interface of a variable requires that we
;;; deactivate then reqctivate the g2-to-g2-data-service capability to obtain data from
;;; the correct data server interface.

;;; The basic wrinkle is that we want the user to be able to change the both
;;; g2-to-g2-interface-name and remote-g2-expression without having to
;;; deactivate and re-activate the interface in G2 (although this may under
;;; certain circumstances happen internally).  ...






;;;; [7.1.1] Slot-Putter for Interface Name

;;; Changing the name of the g2-to-g2-interface of a variable requires that we
;;; deactivate then reqctivate the g2-to-g2-data-service capability to obtain data from
;;; the correct data server interface.

(def-slot-putter g2-to-g2-interface-name
		 (g2-variable g2-to-g2-interface-name initializing?)
  (when (active-p g2-variable)
    (let ((g2ds-variable-structure?
	    (get-slot-value-if-any g2-variable 'g2ds-variable-structure)))
      (g2ds-stop-collecting-data g2-variable)
      (when g2ds-variable-structure?
	(let ((old-collection-interval?
		(background-collection-interval? g2-variable)))
	  (cancel-task
	    (g2ds-variable-scheduled-collection-task
	      g2ds-variable-structure?))
	  (setf (g2ds-variable-interface-name g2ds-variable-structure?)
		g2-to-g2-interface-name)
	  (setf (g2ds-variable-collection-interval? g2ds-variable-structure?)
		old-collection-interval?)
	  (when old-collection-interval?
	    (g2ds-begin-collecting-data
	      g2-variable old-collection-interval?))))))
  (put-attribute-value
    g2-variable
    'g2-to-g2-interface-name
    g2-to-g2-interface-name
    initializing?))

;; jh, 4/22/91.  Cleaned up the slot-putter for g2-to-g2-interface name.  We now
;; check for the existence of a g2ds-variable-structure inside the frame before we
;; attempt to access it.  As well, the collection time resetting is now fixed.
;; Previously it always became zero, even if the variable started out with a
;; non-zero collection time, because g2ds-stop-collecting-data would set it that
;; way and the slot-putter would fail to restore it.




;;; After the name of an object with g2-to-g2-data-interface capability changes,
;;; we must stop collecting data for every variable which connects either to the
;;; old or the new name.  Then we must allow the variables to find the new
;;; interface names by calling g2ds-begin-collecting-data.

;; The only wrinkle in this is that g2ds-stop-collecting-data gets the interface
;; frame by looking at the g2ds-variable structure for the interface name.  This
;; won't get the right interface if its name has changed.  Thus we have to call
;; that portion of g2ds-stop-collecting-data which already has the interface
;; frame.  This function is named
;; g2ds-stop-collecting-data-from-known-interface.  jh, 4/24/91.

(defun update-g2ds-variable-to-interface-connections
       (interface-frame
	new-interface-name-or-names
	old-interface-name-or-names)
  (when (active-p interface-frame)
    (unless nil ; (equal old-interface-name-or-names new-interface-name-or-names) ; see note! (MHD 6/4/02)
      (loop for variable being class-instance of 'variable
	    when
	      (and (g2-to-g2-data-service-p variable)
		   (active-p variable))
	      do
		(let ((name-of-variable-interface?
			(get-slot-value-if-any
			  variable
			  'g2-to-g2-interface-name)))
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
			(let ((g2ds-variable-structure?
				(get-slot-value-if-any
				  variable
				  'g2ds-variable-structure)))
			  (g2ds-stop-collecting-data-from-known-interface
			    variable
			    g2ds-variable-structure?
			    interface-frame)
			  (when g2ds-variable-structure?
			    (let ((old-collection-interval?
				    (background-collection-interval?
				      variable)))
			      (cancel-task
				(g2ds-variable-scheduled-collection-task
				  g2ds-variable-structure?))
			      (setf (g2ds-variable-collection-interval?
				      g2ds-variable-structure?)
				    old-collection-interval?)
			      (when old-collection-interval?
				(g2ds-begin-collecting-data
				  variable old-collection-interval?)))))))))))))

;; Note: the equal test was not really adequate for its intended use: to test
;; two name-or-names values for set equality. However, the test is no longer
;; needed in practice, since the one caller is the note-name-change method,
;; which is invoked subject to an adequate test.  Therefore, the test has been
;; disabled, and the caller is now required to not call this when the name(s)
;; are not in fact changed. (MHD 6/4/02)

;; jh, 11/27/91.  Fixed update-g2ds-variable-to-interface-connections to allow for
;; the case where a variable gets an interface name but the interface doesn't
;; exist.  Now that G2 offers "change the text of", this is probably something
;; that G2 users will occasionally want to do.





;;; The `note-name-change g2-to-g2-data-interface' method invokes
;;; update-g2ds-variable-to-interface-connections on g2-to-g2-data-interface
;;; after invoking its superior method.

(def-class-method note-name-change (g2-to-g2-data-interface old-names initializing-p)
  (funcall-superior-method g2-to-g2-data-interface old-names initializing-p)
  (update-g2ds-variable-to-interface-connections
    g2-to-g2-data-interface
    (name-or-names-for-frame g2-to-g2-data-interface)
    old-names))






;;;; [7.1.2] Slot-Putter for Remote Expression

;;; The remote-g2-expression must be sent to the corresonding icp object when
;;; edited by the user at runtime.

(defun-allowing-unwind write-message-group-for-remote-g2-expression
		       (g2ds-interface-icp-socket
			 g2ds-variable-structure
			 remote-expression
			 remote-expression-text)
  (writing-icp-message-group ((icp-output-port g2ds-interface-icp-socket))
    (send-icp-g2ds-configure-variable
      g2ds-variable-structure
      remote-expression
      remote-expression-text)))

(def-slot-putter remote-g2-expression
    (g2-variable expression-forms initializing?)
  (let ((remote-expression (car expression-forms))
	(remote-expression-text (cdr expression-forms))
        (g2ds-variable-structure?
	  (get-slot-value-if-any g2-variable 'g2ds-variable-structure)))
    (when g2ds-variable-structure?
      (when (active-p g2-variable)
	(let ((old-collection-interval?
		(background-collection-interval? g2-variable)))
	  (g2ds-stop-collecting-data g2-variable)
	  (cancel-task
	    (g2ds-variable-scheduled-collection-task
	      g2ds-variable-structure?))
	  (setf (g2ds-variable-collection-interval? g2ds-variable-structure?)
		old-collection-interval?)
	  (when old-collection-interval?
	    (g2ds-begin-collecting-data g2-variable old-collection-interval?))))
      (when (or system-has-paused system-is-running)
	(let*-while-true
	    ((g2ds-interface-name?
	       (g2ds-variable-interface-name g2ds-variable-structure?))
	     (g2ds-interface?
	       (get-instance-with-name-if-any
		 'object
		 g2ds-interface-name?))
	     (g2ds-interface-structure?
	       (get-slot-value-if-any
		 g2ds-interface?
		 'g2ds-interface-structure))
	     (g2ds-interface-icp-socket?
	       (g2ds-interface-socket g2ds-interface-structure?)))
	  (write-message-group-for-remote-g2-expression
	    g2ds-interface-icp-socket?
	    g2ds-variable-structure?
	    remote-expression
	    remote-expression-text)))))
  (put-attribute-value
    g2-variable
    'remote-g2-expression
    expression-forms
    initializing?))

;; jh, 11/27/91.  Fixed the slot-putter for remote-g2-expression to start
;; collecting data if it can, i.e., if there is a g2-variable structure present.
;; Obtained the fix back from the slot-putter for g2-to-g2-interface-name, so
;; perhaps we should consider abstracting it someday.






;;;; [7.2] Grammar for G2-to-G2 Dataservice Capability

;;; G2-to-g2-interface-name can be either an unreserved symbol (potentially the
;;; name of a G2 object or none.  The g2-to-g2-interface-name will be used to
;;; locate a particular G2-to-G2 interface to be used for a variable.

(add-grammar-rules '((g2-to-g2-interface-name 'none)
		     (g2-to-g2-interface-name object-name)))



;;; The slot value compiler for g2-to-g2-interface-name expects parse-result to
;;; be the symbol NONE or some other symbol, a name.  ...

(def-slot-value-compiler g2-to-g2-interface-name (parse-result)
  (cond ((eq parse-result 'none) nil)
	(t
;	 (let ((interface-object
;		 (get-instance-with-name-if-any 'object parse-result)))
;	   (if interface-object (g2-to-g2-data-interface-p interface-object)))
	 parse-result)
;	(t (values
;            bad-phrase
;            (copy-text-string
;	      "This is not the name of a G2 to G2 interface object.")))
	))

;; jh, 11/27/91.  Changed the slot-value-compiler for g2-to-g2-interface-name to
;; allow names which don't necessarily refer to g2ds interface objects.  Now
;; that G2 offers "change the text of", this is probably something that G2 users
;; will occasionally want to do.  Made a related change to
;; update-g2ds-variable-to-interface-connections.



(def-slot-value-writer g2-to-g2-interface-name (interface-name)
  (if (null interface-name)
      (twrite "none")
      (twrite interface-name)))






;;;; [7.3] Capability Activator for G2-to-G2 Dataservice

(def-class-method activate (G2-to-G2-data-service)
  (let* ((g2ds-interface-name
	   (get-slot-value-if-any g2-to-g2-data-service 'g2-to-G2-interface-name))
         (g2ds-variable-expression
	   (car (get-slot-value-if-any g2-to-g2-data-service 'remote-g2-expression)))
	 (g2ds-variable-expression-text
	   (cdr (get-slot-value-if-any g2-to-g2-data-service 'remote-g2-expression)))
         (g2ds-variable-structure
	   (make-g2ds-variable
	     g2-to-g2-data-service
	     (copy-frame-serial-number (frame-serial-number g2-to-g2-data-service))
	     g2ds-interface-name
	     g2ds-variable-expression
	     g2ds-variable-expression-text
	     nil)))
    (clear-queued-by-local-data-server g2-to-g2-data-service)
    (set-slot-value g2-to-g2-data-service 'g2ds-variable-structure
                    g2ds-variable-structure)
    (funcall-superior-method G2-to-G2-data-service)))




;;;; [7.4] Capability Deactivator for G2-to-G2 Dataservice

(def-class-method deactivate (G2-to-G2-data-service)
  (let* ((G2ds-variable-structure?
	   (get-slot-value-if-any g2-to-g2-data-service 'G2ds-variable-structure)))
    (g2ds-stop-collecting-data g2-to-g2-data-service)
    (when G2ds-variable-structure?
      (cancel-task
	(g2ds-variable-scheduled-collection-task G2ds-variable-structure?))
      (set-slot-value g2-to-g2-data-service 'g2ds-variable-structure nil)
      (clear-queued-by-local-data-server g2-to-g2-data-service)
      (reclaim-icp-object-map-for-g2ds-variable G2ds-variable-structure?)
      (reclaim-g2ds-variable G2ds-variable-structure?))
    (funcall-superior-method G2-to-G2-data-service)))




;;;; [8] ICP Messages for G2-to-G2 Dataservice

;;; [8.1] Messages to Create Corresponding Variable Objects
;;;   g2ds-define-variable
;;;   g2ds-configure-variable
;;; [8.2] Messages for Grouping Variables
;;;   g2ds-begin-variable-list
;;;   g2ds-load-variable-list-element
;;;   g2ds-end-variable-list
;;; [8.3] Messages for Getting and Setting Values
;;;   g2ds-get-values
;;;   g2ds-set-values
;;; [8.4] Messages to Initate Dataservice
;;;   return-g2ds-version
;;;   g2ds-send-data-values-if-any
;;;   g2ds-server-status
;;;   g2ds-initialize-server
;;; [8.5] Messages to Control Remote Dataservice
;;;   g2ds-stop-collecting-values
;;;   g2ds-shut-down-server
;;;   g2ds-pause-server
;;;   g2ds-resume-server
;;; [8.6] Messages to Receive Remote Data
;;;   g2ds-unsolicited-attribute-value [NUPEC only as of 3/10/92]
;;;   g2ds-unsolicited-variable-value  [NUPEC only as of 3/10/92]
;;;   g2ds-variable-value
;;; [8.7] Messages for G2-to-G2 Inform Actions
;;;   g2ds-user-message-string





;;;; [8.1] Messages to Create Corresponding Variable Objects

;;; The function `install-inter-g2-data-request-expression' is used to compile
;;; and install an expression.  The expression is compiled on the target side of
;;; the g2ds.

(defun install-inter-g2-data-request-expression
       (request-structure data-request-expression data-request-expression-text)
  (when data-request-expression-text
    (parse-text-for-slot
      (copy-for-slot-value data-request-expression-text)
      request-structure
      (slot-description-from-class
	'inter-g2-data-request-holder
	'inter-g2-data-request-data-request-expression)))
  (let* ((data-request-expression
	   (or (car (get-slot-value request-structure 'inter-g2-data-request-data-request-expression))
	       data-request-expression))
	 (*current-computation-frame* request-structure)
	 (current-computation-component-particulars nil)
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame request-structure)
	 (post-compiler-warning-note? nil)
	 (post-analyzer-warning-note? nil)
	 (cell-array (cell-array request-structure))
	 (get-value-expression-cell
	   (when cell-array
	     (managed-svref (g2-cell-array-managed-array cell-array)
			    g2ds-read-expression-cell-index)))
	 (set-value-expression-cell
	   (when cell-array
	     (managed-svref (g2-cell-array-managed-array cell-array)
			    g2ds-write-expression-cell-index))))
    (unless (and cell-array get-value-expression-cell)
      (setf cell-array (make-frame 'g2-cell-array))
      (change-slot-value request-structure 'cell-array cell-array)
      (when (/=f (make-empty-expression-cell cell-array) g2ds-read-expression-cell-index)
	(error "Inter-G2 data request did not acquire cell 0 (reading)."))
      (setf get-value-expression-cell
	    (managed-svref (g2-cell-array-managed-array cell-array) g2ds-read-expression-cell-index))
      (activate-g2-cell-array cell-array))
    (unless set-value-expression-cell
      (when (/=f (make-empty-expression-cell cell-array) g2ds-write-expression-cell-index)
	(error "Inter-G2 data request did not acquire cell 1 (writing)."))
      (setf set-value-expression-cell
	    (managed-svref (g2-cell-array-managed-array cell-array) g2ds-write-expression-cell-index))
      (activate-g2-cell-array cell-array))
    (with-phrase-conses
      (unless (register-expression-cell-for-inter-g2-data-request
		'read cell-array data-request-expression)
	(setq data-request-expression '(if-expression false 1))
	(register-expression-cell-for-inter-g2-data-request
	  'read cell-array data-request-expression))
      (register-expression-cell-for-inter-g2-data-request
	'write cell-array data-request-expression)
      (assert-consistency-analysis-if-allowed request-structure)
      (reclaim-slot-value (inter-g2-data-request-expression request-structure))
      (setf (inter-g2-data-request-expression request-structure)
	    (copy-for-slot-value data-request-expression)))
    (register-expression-cell-during-slot-putter
      cell-array
      g2ds-read-expression-cell-index
      t)
    (register-expression-cell-during-slot-putter
      cell-array
      g2ds-write-expression-cell-index
      t)
    nil))

(defun register-expression-cell-for-inter-g2-data-request (style cell-array expression?)
  (with-part-description ((get-default-computation-style-of-class))
    (setf (computation-style-network-access-attempt current-computation-style) style)
    (setf (computation-style-time-out-when-requesting-data-seeking current-computation-style)
	  (if inference-engine-parameters
	      (timeout-for-wakeups inference-engine-parameters)
	      30))
    (let ((index (case style
		   (read g2ds-read-expression-cell-index)
		   (write g2ds-write-expression-cell-index))))
      (register-expression-cell-during-compilation
	cell-array
	index
	t
	expression?
	(case style
	  (read '(or datum (unknown-datum)))
	  (write '(or (class variable-or-parameter) (place-reference) (unknown-datum)))))
      (g2-expression-cell-byte-code-body
	(managed-svref (g2-cell-array-managed-array cell-array) index)))))

;;; The function `make-inter-g2-data-request-holder' ...

(defun make-inter-g2-data-request-holder (g2ds-variable data-request-expression data-request-expression-text)
  (let ((request-structure (make-frame 'inter-g2-data-request-holder)))

    (install-inter-g2-data-request-expression
      request-structure data-request-expression data-request-expression-text)
    (setf (inter-g2-data-request-corresponding-variable-structure
	    request-structure)
	  g2ds-variable)
    (setf (g2ds-variable-server-request-structure g2ds-variable)
	  request-structure)
    (setf (g2ds-variable-g2-frame g2ds-variable) request-structure)
    (frame-serial-number-setf (g2ds-variable-g2-frame-serial-number g2ds-variable)
			      (frame-serial-number request-structure))
    request-structure))



(def-icp-message-type g2ds-define-variable
		      (corresponding-icp-object-index
			(g2ds-expression data-request-expression)
			(g2ds-expression-text data-request-expression-text))
  (let* ((g2ds-connection
	   (get-g2ds-server-connection current-icp-socket))
	 (g2ds-variable
	   (make-g2ds-variable
	     nil
	     (frame-serial-number-0)
	     g2ds-connection
	     data-request-expression
	     data-request-expression-text
	     nil)))
    (make-inter-g2-data-request-holder
      g2ds-variable
      data-request-expression
      data-request-expression-text)
    (setf (g2ds-variable-remote-icp-object-index g2ds-variable)
	  corresponding-icp-object-index)
    ;; Get-g2ds-server-connection could return nil if it fails to find a connection,
    ;; and in such cases, there's no need to push new server connection variables.
    (when g2ds-connection
      (setf (g2ds-server-connection-variables g2ds-connection)
	    (g2ds-cons g2ds-variable
		       (g2ds-server-connection-variables g2ds-connection))))
    (store-corresponding-icp-object
      corresponding-icp-object-index
      g2ds-variable)))

(def-icp-message-type g2ds-configure-variable
		      (g2ds-variable
			(g2ds-expression data-request-expression)
			(g2ds-expression-text data-request-expression-text))
  (let* ((request-structure
	  (g2ds-variable-server-request-structure g2ds-variable))
	 (data-request-in-progress?
	   (expression-cell-computation-in-progress-p request-structure
						      g2ds-read-expression-cell-index)))
    (cancel-inter-g2-data-request request-structure)
    (install-inter-g2-data-request-expression
      request-structure data-request-expression data-request-expression-text)
    (reclaim-g2ds-expression (g2ds-variable-expression g2ds-variable))
    (reclaim-g2ds-expression (g2ds-variable-expression-text g2ds-variable))
    (setf (g2ds-variable-expression g2ds-variable) data-request-expression)
    (setf (g2ds-variable-expression-text g2ds-variable) data-request-expression-text)
    (if data-request-in-progress?
	(initiate-inter-g2-data-service-request request-structure))))


;;;; [8.2] Messages for Grouping Variables

;; At some point consider adding a restriction on the number of variables that
;; can be transmitted in a single group.

(def-system-variable g2ds-variable-list G2DS nil)

(def-icp-message-type g2ds-begin-variable-list ()
  (setq g2ds-variable-list nil))
      
(def-icp-message-type g2ds-load-variable-list-element
             (g2ds-variable
	       (gsi-ds-update-interval
		 collection-interval)
	       (symbol data-type)
	       (g2ds-data-value data-value))
  (when (or (eq data-type 'truth-value) (eq data-type 'boolean))
    (setq data-value (make-evaluation-truth-value data-value)))
  (let ((old-collection-interval
	  (g2ds-variable-collection-interval? g2ds-variable)))
    (when (managed-float-p old-collection-interval)
      (reclaim-managed-float old-collection-interval)))
  (setf (g2ds-variable-collection-interval? g2ds-variable)
	collection-interval)
  (setq g2ds-variable-list
	(g2ds-cons
	  (g2ds-cons g2ds-variable data-value)
	  g2ds-variable-list)))



;; The def-icp-message-type for g2ds-end-variable-list is a dummy to force the
;; generation of a no-op handler.

(def-icp-message-type g2ds-end-variable-list ()
  'done)					






;;;; [8.3] Messages for Getting and Setting Values

;;; The ICP message handlers for `G2ds-get-values' and `G2ds-set-values' manage
;;; a queue of operations, inter-g2-data-request-holders, and values to set into
;;; the places denoted by them.  The bodies of these messages are run in the
;;; server g2.  

(def-icp-message-type g2ds-get-values ()
  (when system-is-running
    (loop with *current-computation-frame* = data-server-parameters
	  with g2ds-variable-conses? = g2ds-variable-list
	  while g2ds-variable-conses?
	  do
      (with-temporary-gensym-float-creation g2ds-get-values
	(loop repeat iterations-for-g2ds-temporary-float-processing
	      for g2ds-variable-cons? = (pop g2ds-variable-conses?)
	      while g2ds-variable-cons?
	      as g2ds-variable = (car g2ds-variable-cons?)
	      as request-structure = (g2ds-variable-server-request-structure
				       g2ds-variable)
	      as collection-interval? = (g2ds-variable-collection-interval?
					  g2ds-variable)
	      as current-computation-instance = request-structure
	      do
	  (cond
	    ((or (null collection-interval?)
		 (evaluation-quantity-= collection-interval? 0))
	     (initiate-inter-g2-data-service-request request-structure))
	    (t (if collection-interval?
		   (with-current-scheduling
		       ((g2ds-variable-scheduled-collection-task
			  g2ds-variable)
			(priority-of-data-service data-server-parameters)
			(if (fixnump collection-interval?)
			    (coerce-fixnum-to-gensym-float collection-interval?)
			    (managed-float-value collection-interval?)))
		     (initiate-inter-g2-data-service-request
		       request-structure))
		   (with-current-scheduling
		       ((g2ds-variable-scheduled-collection-task g2ds-variable)
			(priority-of-data-service data-server-parameters))
		     (initiate-inter-g2-data-service-request
		       request-structure)))
		       (when collection-interval?
			 (if (fixnump collection-interval?)
			     (coerce-fixnum-to-gensym-float collection-interval?)
			     (managed-float-value collection-interval?)))))))))
  (reclaim-g2ds-list g2ds-variable-list)
  (setq g2ds-variable-list nil))

(def-icp-message-type g2ds-set-values ()
  (loop with *current-computation-frame* = data-server-parameters
	for g2ds-variable-cons in g2ds-variable-list
	as g2ds-variable = (car g2ds-variable-cons)
	as value = (cdr g2ds-variable-cons)
	as request-structure =
	(g2ds-variable-server-request-structure g2ds-variable)
	as request-expression =	(g2ds-variable-expression g2ds-variable)
	as request-expression-text = (g2ds-variable-expression-text g2ds-variable)
	as current-computation-instance = request-structure
	as variable-or-parameter-p = (and system-is-running
					  (designation-p request-expression))  ;; dog-dont-hunt-p
	do
    (when (not variable-or-parameter-p)
      (write-warning-message
	  2
	(tformat "G2 data server cannot set a value for the expression ~s"
		 
		 (if request-expression-text
		     (convert-text-to-text-string request-expression-text)
		     request-expression))))
    (when variable-or-parameter-p
      (with-current-scheduling
	  (nil (priority-of-data-service data-server-parameters)) ; priority was constant 2
	(initiate-inter-g2-set-value-request
	  G2ds-variable value)))
    (reclaim-g2ds-cons g2ds-variable-cons))
  (reclaim-g2ds-list g2ds-variable-list)
  (setq g2ds-variable-list nil))


;;;; initiate-inter-g2-set-value-request
;;;;
;;;;   This function is run in a task scheduled in the body of the
;;;;   g2ds-set-values message
;
;(defun-simple initiate-inter-g2-set-value-request (g2ds-variable value-to-set)
;  (let* ((request-structure
;           (g2ds-variable-server-request-structure g2ds-variable))
;         (g2-cell-array (cell-array containing-block))
;         (managed-array
;           (when g2-cell-array
;             (g2-cell-array-managed-array g2-cell-array)))
;         (expression-cell
;           (when (managed-array-p managed-array)
;             (managed-svref managed-array g2ds-write-expression-cell-index))))
;    (when (expression-cell-able-to-compute-p expression-cell)
;      (setf (inter-g2-data-request-incoming-value request-structure)
;            value-to-set)
;      (schedule-expression-cell-execution request-structure 1 t))))


;; Replace the reference to data-server-parameters above with the reference to
;; the g2-extension subclass instance which represents this server connection.
;; -jra & blm 5/4/90

;; Consider having separate get and set expressions.
;;  expression cells, actually.  Done. -ncc, 3 Jan 1995 

;; Added a check for remote modifiability for the place derived in the
;; G2ds-set-values message.  Also added a wrapper within the g2ds-set-values
;; message which causes serve-item-p to check for remote visibility.  jh, 1/30/91.






;;;; [8.4] Messages to Initate Dataservice

;; Had to move all version registry information to UTILITIES3, since
;; version-checking code could occur at any point later in the
;; sequence of modules.  (jh, 6/25/90)

(defun get-g2ds-interface-from-icp-socket (icp-socket)
  (loop for g2ds-interface in list-of-all-g2ds-interfaces
        as g2ds-interface-structure
	   = (and (or (active-p g2ds-interface)
		      (g2-to-g2-interface-connects-while-inactive-p
			g2ds-interface))
		  (get-slot-value-if-any
		    g2ds-interface
		    'g2ds-interface-structure))
        as g2ds-icp-socket
	   = (and g2ds-interface-structure
		  (g2ds-interface-socket g2ds-interface-structure))
        until (eq g2ds-icp-socket icp-socket)
	finally
	  (return (and (eq g2ds-icp-socket icp-socket) g2ds-interface))))

(def-icp-message-type g2ds-server-status ((symbol g2ds-server-status))
  (let*-while-true
      ((g2ds-interface-frame?
	 (get-g2ds-interface-from-icp-socket current-icp-socket))
       (g2ds-interface-structure?
	 (get-slot-value-if-any g2ds-interface-frame? 'g2ds-interface-structure)))
    (let ((old-g2ds-interface-status ;known never to be nil
	    (g2ds-interface-status g2ds-interface-structure?)))
      (setf (g2ds-interface-timed-out-p g2ds-interface-structure?) nil)
      (setf (g2ds-interface-waiting-for-response-p g2ds-interface-structure?) nil)
      (unless (eq old-g2ds-interface-status g2ds-server-status)

	;; old comment as of 10/8/92: If the following were change-slot-value,
	;; then forward chaining would work for it.  I believe this is currently
	;; a registered bug.  Oops, the code that follows it seems to be
	;; intended to deal with forward chaining, but we find it bizarre and
	;; wonder if it works.  -jra & jh 2/29/92

	(change-g2ds-interface-status-throughout
	  g2ds-interface-frame?
	  old-g2ds-interface-status
	  g2ds-server-status)

	;; Reset the variables if resetting the interface.
	(when (and g2ds-interface-frame?
		   (or system-has-paused system-is-running)
		   (eq g2ds-server-status 'running))

	  ;; Don't reset the variables if the interface status is connected:
	  ;; this means the capability has just been activated and the
	  ;; capability activator has begun data collecting on all variables.
	  (unless (eq old-g2ds-interface-status 'connected)
	    (let ((interface-name-or-names?
		    (name-or-names-for-frame g2ds-interface-frame?)))
	      (when interface-name-or-names?
		(let ((begin-collecting-data-list
			(loop for variable being class-instance of 'variable
			      for desired-interface-name
				  = (get-slot-value-if-any 
				      variable 
				      'g2-to-g2-interface-name)
			      when
				(and (active-p variable)
				     (g2-to-g2-data-service-p variable)
				     (if (consp interface-name-or-names?)
					 (memq desired-interface-name
					       interface-name-or-names?)
					 (eq desired-interface-name
					     interface-name-or-names?)))
				collect variable using g2ds-cons)))
		  (loop with g2ds-variables? = begin-collecting-data-list
			while g2ds-variables?
			do
		    (with-temporary-gensym-float-creation g2ds-server-status
		      (loop repeat
			    iterations-for-g2ds-temporary-float-processing
			    for variable? = (pop g2ds-variables?)
			    while variable?
			    do
			(let*-while-true
			    ((g2ds-variable-structure?
			       (get-slot-value-if-any
				 variable?
				 'g2ds-variable-structure))
			     (data-collection-interval?
			       (g2ds-variable-collection-interval?
				 g2ds-variable-structure?)))
			  (cond
			    ((evaluation-quantity->
			       data-collection-interval?
			       0)
			     (clear-queued-by-local-data-server variable?)
			     (g2ds-begin-collecting-data
			       variable?
			       data-collection-interval?))
			    ((queued-by-local-data-server-p variable?)
			     (clear-queued-by-local-data-server variable?)
			     (g2ds-collect-one-shot-data variable?)))))))
		  (reclaim-g2ds-list begin-collecting-data-list))))))))))






(defun g2ds-send-initial-message-group (icp-socket)
  (writing-icp-message-group ((icp-output-port icp-socket))
    (send-icp-g2ds-initialize-server)
    #+old-g2ds-init
    (send-g2ds-version-information)
    (g2ds-push icp-socket icp-sockets-now-initializing-g2ds)
    ;; initialization continues when handler for return-g2ds-version calls
    ;; g2ds-begin-collecting-data-on-appropriate-variables.
    ))

;;; When a client sets up an icp connection to the server for inter G2 data
;;; service, the server builds a g2ds-server-connection structure.  This
;;; structure will store the list of values to return to the client and the list
;;; of defined g2ds variable value requests.  The list of variable value
;;; requests will be used when the client shuts down data service to stop all
;;; collections in progress for the client and reclaim all frames and structures
;;; defined to service the client's data requests.

(def-icp-message-type g2ds-initialize-server ()
  (receive-initial-message 'g2 'g2)
  (cond
    ((not (network-access-allowed-p 'g2 'connect))
     (disallow-new-icp-listener-connection current-icp-socket))
    (t
     (writing-icp-message-group ((icp-output-port current-icp-socket))
       (send-g2ds-version-information nil nil)))))

(defun finish-server-g2ds-interface-initialization (class name)
  (setf (icp-socket-listener-client? current-icp-socket) 'g2)
  (register-icp-callback 'icp-connection-loss 'handle-g2ds-shut-down-server
			 current-icp-socket)
  (initialize-i-am-alive-info current-icp-socket 'g2ds-connection-clogged-p)
  (let ((g2ds-server-connection (make-g2ds-server-connection current-icp-socket)))
    (make-g2ds-server-interface g2ds-server-connection class name)
    (with-future-scheduling
	((g2ds-server-flush-return-data-task g2ds-server-connection)
	 2 (g2-future-interval 1) 1.0)
      (return-values-to-g2ds-client-task g2ds-server-connection))
    (g2ds-push g2ds-server-connection g2ds-server-connections)))

(defun make-g2ds-server-interface (g2ds-server-connection-structure class name)
  (let ((interface-frame (make-frame (or class 'g2-to-g2-data-interface))))
    (set-slot-value interface-frame 'g2ds-server-connection-structure
		    g2ds-server-connection-structure)
    (setf (enclosing-interface-frame? current-icp-socket) interface-frame)
    (frame-serial-number-setf (enclosing-interface-frame-serial-number current-icp-socket)
			      (frame-serial-number interface-frame))
    (when name
      (change-slot-value interface-frame 'name-or-names-for-frame name))
    (change-g2ds-interface-status-throughout interface-frame 'inactive 'server)
    (funcall-method 'activate-if-possible-and-propagate interface-frame)))

;; jh, 5/21/92.  Abstracted send-g2ds-version-information because this happens
;; in two places.  On the client side, it happens in
;; activate-g2ds-interface-with-extant-socket, which is called by the capability
;; activator for the g2-to-g2-interface capability.  On the server side, it
;; happens in the handler for the ICP message g2ds-initialize-server.  Note that
;; we use the system version where possible, and only use a hard-wired constant
;; where we can't avoid it.  

(defun-void send-g2ds-version-information (remote-class remote-name)
  (let ((major-version (first (system-version 'ab)))
	(minor-version (second (system-version 'ab))))
    (unless (and (numberp major-version) (numberp minor-version))
      (setq major-version (get-system-major-version current-system-name))
      (setq minor-version (get-system-minor-version current-system-name)))
    (send-icp-return-g2ds-version major-version minor-version remote-class remote-name)))

(def-icp-value-writer g2ds-version-interface-symbol
  (with-bifurcated-version-for-output (return-g2ds-version-sends-class-icp-version)
    nil
    (write-icp-symbol-as-value-type
      g2ds-version-interface-symbol)))

(def-icp-value-reader g2ds-version-interface-symbol
  (with-bifurcated-version-for-input (return-g2ds-version-sends-class-icp-version)
    nil
    (read-icp-symbol-as-value-type)))


(def-icp-message-type return-g2ds-version
		      ((unsigned-integer major-version-number)
		       (unsigned-integer minor-version-number)
		       (g2ds-version-interface-symbol class)
		       (g2ds-version-interface-symbol name))
  (maybe-update-remote-icp-version-info-for-version
    current-icp-socket major-version-number minor-version-number)

  (when (>=f major-version-number 4)
    (setf (icp-connection-supports-shutdown-protocol? current-icp-socket) t))

  (cancel-task (icp-connection-timeout-task? current-icp-socket))
  
  (let ((g2ds-interface-frame?
	  (get-g2ds-interface-from-icp-socket current-icp-socket)))
    (cond (g2ds-interface-frame?
	   #-old-g2ds-init
	   (writing-icp-message-group ((icp-output-port current-icp-socket))
	     (send-g2ds-version-information
	       (or (get-slot-value-if-any g2ds-interface-frame? 'class-of-remote-interface)
		   'g2-to-g2-data-interface)
	       (let ((names (get-slot-value-if-any g2ds-interface-frame? 'names-of-remote-interface)))
		 (if (consp names)
		     (car names)
		     names))))
	   (finish-client-g2ds-interface-initialization g2ds-interface-frame?))
	  (t
	   (finish-server-g2ds-interface-initialization class name)))))

(defun finish-client-g2ds-interface-initialization (g2ds-interface-frame?)
  ;; Old-status is never nil - the interface-status is a capability slot
  ;; that defaults to the symbol inactive.
  (let ((old-status
	  (get-slot-value-if-any g2ds-interface-frame? 'interface-status)))
    (unless (memq old-status '(running reset paused))
      (change-g2ds-interface-status-throughout
	g2ds-interface-frame? old-status 'connected)))
  (setq icp-sockets-now-initializing-g2ds
	(delete-g2ds-element current-icp-socket icp-sockets-now-initializing-g2ds))
  (let ((interface-name? (name-or-names-for-frame g2ds-interface-frame?)))
    ;; jh, 4/25/95.  Can't begin collecting data until we know the version,
    ;; since how we represent collection time depends on it (see the ICP
    ;; value reader and writer for gsi-ds-update-interval in
    ;; GSI-COMMON).
    (g2ds-begin-collecting-data-on-appropriate-variables interface-name?)))

;; Get-g2ds-server-connection should return nil if it fails to find a connection.
;; Previously, it was wreaking great havoc in handle-G2ds-shut-down-server (q.v.)
;; by returning the last element of g2ds-server-connections.
;; (jh per blm, 3/20/90)


(defun get-g2ds-server-connection (icp-socket)
  (loop for g2ds-server-connection in g2ds-server-connections
        do (when (eq (g2ds-server-connection-icp-socket g2ds-server-connection)
		     icp-socket)
	     (return g2ds-server-connection))
	finally (return nil)))






;;;; [8.5] Messages to Control Remote Dataservice

(def-icp-message-type g2ds-stop-collecting-values ()
  (loop for g2ds-variable-cons in g2ds-variable-list
	as g2ds-variable = (car g2ds-variable-cons)
	as request-structure
	   = (g2ds-variable-server-request-structure g2ds-variable)
	do
    (cancel-inter-g2-data-request request-structure)
    (cancel-task (g2ds-variable-scheduled-collection-task g2ds-variable))
    (reclaim-g2ds-cons g2ds-variable-cons))
  (reclaim-g2ds-list g2ds-variable-list)
  (setq g2ds-variable-list nil))


(def-icp-message-type g2ds-pause-server ()
  (let ((g2ds-server-connection?
	  (get-g2ds-server-connection current-icp-socket)))
    (when g2ds-server-connection?
      (setf (g2ds-server-connection-paused? g2ds-server-connection?) t))))



(def-icp-message-type g2ds-resume-server ()
  (let ((g2ds-server-connection?
	  (get-g2ds-server-connection current-icp-socket)))
    (when g2ds-server-connection?
      (setf (g2ds-server-connection-paused? g2ds-server-connection?) nil))))






;;;; [8.6] Messages to Receive Remote Data

;;; These messages process data returned by remote G2DS data servers.

(def-icp-message-type g2ds-variable-value
                      ((returned-g2ds-variable
			 g2ds-variable-structure)
		       (unsigned-integer error-code)
		       (symbol data-type)
		       (g2ds-data-value value))
  (when (or (eq data-type 'truth-value) (eq data-type 'boolean))
    (setq value (make-evaluation-truth-value value)))
  (unless
      (when g2ds-variable-structure
	(let* ((frame-serial-number-when-request-sent
		 (if (g2ds-variable-p g2ds-variable-structure)
		     (g2ds-variable-g2-frame-serial-number g2ds-variable-structure)))
	       (variable-frame
		 (if frame-serial-number-when-request-sent
		     (g2ds-variable-g2-frame g2ds-variable-structure))))
	  (setf (g2ds-variable-error-code g2ds-variable-structure) error-code)
	  (when (and variable-frame
		     (frame-serial-number-equal frame-serial-number-when-request-sent
						(frame-serial-number variable-frame)))
	    (clear-queued-by-local-data-server variable-frame)
	    (case error-code
	      (#.g2ds-no-error
	       (save-g2ds-variable-value-for-processing
		 g2ds-variable-structure value)
	       t)
	      (t (write-warning-message
		     2
		   (tformat
		     "A G2 data server data request for ~NF returned error code ~a"
		     variable-frame error-code))  ; Name for error code here?
		 nil)))))
    (reclaim-evaluation-value value)))






;;;; [8.7] Messages for G2-to-G2 Inform Actions

;;; The user will have to specify a data server for messages slot on an object
;;; then specify the object by name in the inform expression.  The G2 data
;;; server will transmit the text of the message over ICP then put it on the
;;; message board of the receiving G2.

(def-icp-message-type g2ds-user-message-string
		      ((text-string user-message)
		       (unsigned-integer-or-nil urgency?)
		       (unsigned-integer-or-nil duration?))
  (unless (remote-inform-restricted-p)
    (post-on-message-board
      (copy-text-string user-message) urgency? duration? nil nil)))


;; Added network access restrictions for the g2ds-user-message-string ICP message.
;; jh, 1/30/91.






;;;; [9] G2-to-G2 Dataserver Functions

;;; [9.1]  Function to collect one shot data : g2ds-collect-one-shot-data
;;; [9.2]  Function to begin collecting data : g2ds-begin-collecting-data
;;; [9.3]  Function to stop collecting data  : g2ds-stop-collecting-data
;;; [9.4]  Function to accept data           : g2ds-accept-data
;;; [9.5]  Function to initialize data server: g2ds-initialize-server
;;; [9.6]  Function to set external variable : g2ds-set-external-variable
;;; [9.7]  Function to shut down data server : g2ds-shut-down-server
;;; [9.8]  Function to deliver messages      : g2ds-send-message
;;; [9.9]  Function to pause data server     : g2ds-pause-server
;;; [9.10] Function to resume data server    : g2ds-resume-server






;;;; [9.1] Function to Collect One Shot G2-to-G2 Data

(defun-simple g2ds-collect-one-shot-data (g2-variable)
  (if (g2-to-g2-data-service-p g2-variable)
    (when (or (not (queued-by-local-data-server-p g2-variable))
	      (failed-p g2-variable))
      (let* ((g2ds-variable-structure
	       (get-slot-value-if-any g2-variable 'g2ds-variable-structure))
	     (data-collection-interval?
	       (g2ds-variable-collection-interval? g2ds-variable-structure))
	     (g2ds-interface-name
	       (g2ds-variable-interface-name g2ds-variable-structure))
	     (g2ds-interface
	       (get-instance-with-name-if-any 'object g2ds-interface-name))
	     (g2ds-interface-structure
	       (if g2ds-interface
		   (get-slot-value-if-any g2ds-interface 'g2ds-interface-structure)))
	     (g2ds-interface-icp-socket
	       (if g2ds-interface-structure
		   (g2ds-interface-socket g2ds-interface-structure))))
	(if (or (null g2ds-interface)
		(not (active-p g2ds-interface))
		(null g2ds-interface-structure)
		(null g2ds-interface-icp-socket)
		(not (icp-connection-open-p g2ds-interface-icp-socket)))
	    ;; the number [of retries must be limited? - incomplete comment]
	    (with-future-scheduling
		((g2ds-variable-scheduled-collection-task g2ds-variable-structure)
		 2
		 (g2-future-interval 1))
	      (g2ds-collect-one-shot-data g2-variable))
	    (progn
	      (set-queued-by-local-data-server g2-variable)
	      (setf (g2ds-variable-ok-to-store-values? g2ds-variable-structure) t)
	      (enqueue (g2ds-cons g2ds-variable-structure 0)
		       (g2ds-interface-data-queue-head g2ds-interface-structure)
		       (g2ds-interface-data-queue-tail g2ds-interface-structure)
		       g2ds-cons)
	      (when (and (failed-p g2-variable)
			 data-collection-interval?
			 (>f data-collection-interval? 0))
		(g2ds-begin-collecting-data
		  g2-variable data-collection-interval?))))))
    (warning-message 2
	"Variable or variable ~NF is not configured for the G2 to G2 data server."
      g2-variable)))


;;;; [9.2] Function to Begin Collecting G2-to-G2 Data

;;; g2ds-begin-collecting-data is called in the client G2, i.e. the one with the interface
;;; object(s) and dataserved variable(s).

(defun-simple g2ds-begin-collecting-data (g2-variable collection-interval)
  (if (g2-to-g2-data-service-p g2-variable)
    (let* ((g2ds-variable-structure
            (get-slot-value-if-any g2-variable 'g2ds-variable-structure))
           (g2ds-interface-name
            (g2ds-variable-interface-name g2ds-variable-structure))
	   (g2ds-interface
	     (get-instance-with-name-if-any 'object g2ds-interface-name))
           (g2ds-interface-structure
            (if g2ds-interface
              (get-slot-value-if-any g2ds-interface 'g2ds-interface-structure)))
	   (g2ds-interface-icp-socket
	     (if g2ds-interface-structure
		 (g2ds-interface-socket g2ds-interface-structure))))
      (if (or (null g2ds-interface)
	      (not (active-p g2ds-interface))
	      (null g2ds-interface-structure)
	      (null g2ds-interface-icp-socket)
	      (not (icp-connection-open-p g2ds-interface-icp-socket)))

	  ;; must limit the number of retries here.  -jra 5/4/90
	  (with-future-scheduling
	      ((g2ds-variable-scheduled-collection-task g2ds-variable-structure)
	       2
	       (g2-future-interval 1))
	    (g2ds-begin-collecting-data g2-variable collection-interval))
	  (progn
	    (set-queued-by-local-data-server g2-variable)
	    (setf (g2ds-variable-ok-to-store-values? g2ds-variable-structure) t)
	    (setf (g2ds-variable-collection-interval? g2ds-variable-structure) collection-interval)
	    (enqueue (g2ds-cons g2ds-variable-structure collection-interval)
		     (g2ds-interface-data-queue-head g2ds-interface-structure)
		     (g2ds-interface-data-queue-tail g2ds-interface-structure)
		     g2ds-cons))))
    (warning-message 2
                     "Variable or variable ~NF is not configured for the G2 to G2 data server."
      g2-variable)))



;;;; [9.3] Function to Stop Collecting G2-to-G2 Data

(defun-allowing-unwind g2ds-stop-collecting-data-from-known-interface
       (g2-variable
	g2ds-variable-structure?
	g2ds-interface?)
  (clear-queued-by-local-data-server g2-variable)
  (let* ((g2ds-interface-structure?
	   (if (and g2ds-interface?
		    (active-p g2ds-interface?))
	       (get-slot-value-if-any
		 g2ds-interface?
		 'g2ds-interface-structure)
	       nil))
	 (g2ds-icp-socket?
	   (if g2ds-interface-structure?
	       (g2ds-interface-socket g2ds-interface-structure?)
	       nil)))
    (when (and g2ds-icp-socket?
	       (g2ds-variable-ok-to-store-values? g2ds-variable-structure?))
      (setf (g2ds-variable-ok-to-store-values? g2ds-variable-structure?) nil)
      (setf (g2ds-variable-collection-interval? g2ds-variable-structure?) 0)
      (writing-icp-message-group ((icp-output-port g2ds-icp-socket?))
	(send-icp-g2ds-begin-variable-list)
	(send-icp-g2ds-load-variable-list-element
	  g2ds-variable-structure?
	  0
	  'no-data-value
	  nil)
	(send-icp-g2ds-end-variable-list)
	(send-icp-g2ds-stop-collecting-values)))))

;; jh, 4/24/91.  Fractioned off the part of g2ds-stop-collecting-data that occurs
;; after we have the interface frame, and defined it as
;; g2ds-stop-collecting-data-from-known-interface.  This is necessary so we can
;; respond to G2-to-G2 interface name changes at runtime.  When a name change
;; happens, we can't access the interface frame through the name in
;; g2ds-variable-structure?, since it has changed.

(defun g2ds-stop-collecting-data (g2-variable)
  (let* ((g2ds-variable-structure?
	   (get-slot-value-if-any g2-variable 'g2ds-variable-structure))
         (g2ds-interface-name?
	   (if g2ds-variable-structure?
	       (g2ds-variable-interface-name g2ds-variable-structure?)
	       nil))
	 (g2ds-interface?
	   (if g2ds-interface-name?
	       (get-instance-with-name-if-any 'object g2ds-interface-name?)
	       nil)))
    (g2ds-stop-collecting-data-from-known-interface
      g2-variable
      g2ds-variable-structure?
      g2ds-interface?)))






;;;; [9.4] Function to Accept G2-to-G2 Data


(defun-allowing-unwind change-g2ds-interface-status-appropriately
		       (g2ds-interface-structure
			 icp-connection-open?
			 countdown-timer-value
			 g2ds-interface-countdown-timer-limit
			 g2ds-interface
			 g2ds-icp-socket)
  (cond

    ;; Check for timeout.
    ((and (or (g2ds-interface-waiting-for-response-p
		g2ds-interface-structure)
	      (and (not icp-connection-open?)
		   (eq (g2ds-interface-status g2ds-interface-structure)
		       'attempting)))
	  (>f (fixnum-time-difference (get-fixnum-time) countdown-timer-value)
	      (fixnum-time-interval (*f 1000 g2ds-interface-countdown-timer-limit))))

     (let ((old-g2ds-interface-status-slot-value
	     (get-slot-value-if-any g2ds-interface 'interface-status)))
       (case old-g2ds-interface-status-slot-value
	 ((attempting connected)
	  (setq g2ds-interface-structure nil)
	  (change-g2ds-interface-status-throughout
	    g2ds-interface
	    old-g2ds-interface-status-slot-value
	    'failed))
	 ((running reset paused)
	  (change-g2ds-interface-status-throughout
	    g2ds-interface
	    old-g2ds-interface-status-slot-value
	    'timed-out))
	 (failed) ; How do we get here?  rh, 7/25/96
	 #+development
	 (otherwise
	  (cerror "Continue anyway"
		  "CHANGE-G2DS-INTERFACE-STATUS-APPROPRIATELY: ~
                   unexpected status ~a"
		  old-g2ds-interface-status-slot-value))))

     (write-warning-message
       3
       (tformat
	 (if icp-connection-open?
	     "G2DS interface ~NF has timed out."
	     "ICP connection lost for G2DS interface ~NF.")
	 g2ds-interface))
     (when g2ds-interface-structure
       (setf (g2ds-interface-waiting-for-response-p g2ds-interface-structure) nil)
       (setf (g2ds-interface-timed-out-p g2ds-interface-structure) t)))

    ;; Has not timed out.
    ((and (not (g2ds-interface-waiting-for-response-p g2ds-interface-structure))
	  (not (g2ds-interface-timed-out-p g2ds-interface-structure)))
     (writing-icp-message-group ((icp-output-port g2ds-icp-socket))
       (send-icp-g2ds-send-data-values-if-any))
     (setf (g2ds-interface-waiting-for-response-p g2ds-interface-structure) t)
     (setf (g2ds-interface-countdown-timer g2ds-interface-structure)
	   (get-fixnum-time)))))

(def-icp-message-type g2ds-send-data-values-if-any ()
  (writing-icp-message-group ((icp-output-port current-icp-socket))
    (send-icp-g2ds-server-status
      (cond (system-has-aborted 'abort)
	    (system-has-paused 'paused)
	    (system-is-running 'running)
	    (t                 'reset)))))



(def-substitution-macro g2ds-variable-g2-frame-reprocessed-p (g2ds-variable)
  (frame-has-been-reprocessed-p
    (g2ds-variable-g2-frame g2ds-variable)
    (g2ds-variable-g2-frame-serial-number g2ds-variable)))


(defun-allowing-unwind accept-g2ds-values-appropriately 
                       (g2ds-interface-structure g2ds-icp-socket)
  (when (and (examine-head-of-queue
	       (g2ds-interface-data-queue-head
		 g2ds-interface-structure))
	     (not (g2ds-interface-timed-out-p g2ds-interface-structure)))
    (let ((use-new-message-group-for-send-icp-enlarge-index-space-p nil))
      (writing-icp-message-group ((icp-output-port g2ds-icp-socket))
	(loop as element = (dequeue
			     (g2ds-interface-data-queue-head
			       g2ds-interface-structure)
			     (g2ds-interface-data-queue-tail
			       g2ds-interface-structure)
			     reclaim-g2ds-cons)
	      while element
	      do
	  (send-icp-g2ds-begin-variable-list)
	  ;;decide if this entry is a set or a get:
	  (cond  ((consp element)
		  ;; GET request - (g2ds-variable . collection-interval)
		  (let* ((g2ds-variable (car element))
			 (g2ds-collection-interval (cdr element)))
		    (unless (g2ds-variable-g2-frame-reprocessed-p g2ds-variable)
		      (send-icp-g2ds-load-variable-list-element
			g2ds-variable
			g2ds-collection-interval
			'no-data-value
			nil)))
		  ;; if there's a run on GETs, batch 'em up.
		  (loop as g2ds-variable-cons = (examine-head-of-queue
						  (g2ds-interface-data-queue-head
						    g2ds-interface-structure))

			while (and g2ds-variable-cons 		; queue not empty 
				   (consp g2ds-variable-cons))	; next element is a GET
			do
		    (let* ((g2ds-variable (car g2ds-variable-cons))
			   (g2ds-collection-interval (cdr g2ds-variable-cons)))
		      (dequeue
			(g2ds-interface-data-queue-head
			  g2ds-interface-structure)
			(g2ds-interface-data-queue-tail
			  g2ds-interface-structure)
			reclaim-g2ds-cons)
		      (unless (g2ds-variable-g2-frame-reprocessed-p g2ds-variable)
			(send-icp-g2ds-load-variable-list-element
			  g2ds-variable
			  g2ds-collection-interval
			  'no-data-value
			  nil))))
		  (send-icp-g2ds-end-variable-list)
		  (send-icp-g2ds-get-values))
		 (t
		  ;; queue elt is not a cons -- therefore it's a SET request:
		  (let* ((value-to-set (g2ds-variable-value-to-set? element)))
		    (unless  (g2ds-variable-g2-frame-reprocessed-p element)
		      (with-temporary-gensym-float-creation
			  g2ds-accept-data
			(send-icp-g2ds-load-variable-list-element
			  element
			  0
			  (g2ds-evaluation-value-type value-to-set)
			  value-to-set)))
		    ;; if there are more SET requests, queue 'em up and send in a bunch
		    (with-temporary-gensym-float-creation
			g2ds-accept-data
		      (loop as g2ds-variable = (examine-head-of-queue
						 (g2ds-interface-data-queue-head
						   g2ds-interface-structure))
			    while (and g2ds-variable
				       (not (consp g2ds-variable)))
			    do
			(let* ((value-to-set (g2ds-variable-value-to-set? g2ds-variable)))
			  (dequeue
			    (g2ds-interface-data-queue-head
			      g2ds-interface-structure)
			    (g2ds-interface-data-queue-tail
			      g2ds-interface-structure)
			    reclaim-g2ds-cons)
			  (unless (g2ds-variable-g2-frame-reprocessed-p element)
			    (send-icp-g2ds-load-variable-list-element
			      g2ds-variable
			      0
			      (g2ds-evaluation-value-type value-to-set)
			      value-to-set))))))
		  (send-icp-g2ds-end-variable-list)
		  (send-icp-g2ds-set-values))))))))



(defun g2ds-accept-data ()
  (loop for g2ds-interface in list-of-all-g2ds-interfaces
        as g2ds-interface-structure? = (if (active-p g2ds-interface)
					   (get-slot-value-if-any
					     g2ds-interface
					     'g2ds-interface-structure)
					   nil)
        as g2ds-icp-socket? = (if g2ds-interface-structure?
				  (g2ds-interface-socket
				    g2ds-interface-structure?)
				  nil)
        do
    (when (and g2ds-interface-structure?
	       g2ds-icp-socket?
	       (not (memq g2ds-icp-socket? icp-sockets-now-initializing-g2ds))) 
      (let* ((g2ds-interface-countdown-timer-limit
	       (get-slot-value-if-any
		 g2ds-interface
		 'interface-timeout-period))
	     (icp-connection-open?
	       (icp-connection-open-p g2ds-icp-socket?))
	     (countdown-timer-value
	       (g2ds-interface-countdown-timer
		 g2ds-interface-structure?)))
	(unless (numberp g2ds-interface-countdown-timer-limit)
	  (setq g2ds-interface-countdown-timer-limit
		default-g2ds-interface-countdown-timer-limit))
	(change-g2ds-interface-status-appropriately
	  g2ds-interface-structure?
	  icp-connection-open?
	  countdown-timer-value
	  g2ds-interface-countdown-timer-limit
	  g2ds-interface
	  g2ds-icp-socket?)
	(accept-g2ds-values-appropriately
	  g2ds-interface-structure?
	  g2ds-icp-socket?))))
  t)

;; jh, 1/7/92.  Extracted two subfunctions from g2ds-accept-data,
;; change-g2ds-interface-status-appropriately and
;; accept-g2ds-values-appropriately.  The translation of G2ds-accept-data into C
;; was too large for the HP9000s300 compiler to handle.






;;; The function `gsi-requests-accept-data-calls-p' determines whether or not
;;; GSI could need to have accept-data called for it.  Note that if anything
;;; changes the value of this function from NIL to T (say in the activate method
;;; for gsi-inteface), then the function schedule-data-server-accept-data-calls
;;; must be called to ensure the restart of accept data calls in general.

(defun g2ds-requests-accept-data-calls-p ()
  (loop for interface being each class-instance of 'g2-to-g2-data-interface
	thereis (active-p interface)))





;;;; [9.5] Function to Initialize G2-to-G2 Data Server

;; G2-to-G2 dataservice initialization is handled by g2ds-interface capability
;; activation.

(defun G2ds-initialize-server ())






;;;; [9.6] Function to Set External G2-to-G2 Variable

(defun g2ds-set-external-variable (g2-variable value data-type)
  (declare (ignore data-type))
  (when (g2-to-g2-data-service-p g2-variable)
    (let* ((g2ds-variable-structure
	     (get-slot-value-if-any g2-variable 'g2ds-variable-structure))
	   (value-to-set value)
	   (g2ds-interface-name
	     (g2ds-variable-interface-name g2ds-variable-structure))
	   (g2ds-interface
	     (get-instance-with-name-if-any 'object g2ds-interface-name))
	   (g2ds-interface-structure
	     (if g2ds-interface
		 (get-slot-value-if-any g2ds-interface 'g2ds-interface-structure)))
	   (g2ds-interface-icp-socket
	     (if g2ds-interface-structure
		 (g2ds-interface-socket g2ds-interface-structure)))
	   (error-format-string
	     (cond ((null g2ds-interface)
		    "The G2 to G2 data server ~
                     could not set a value for variable ~NF ~
                     because ~a does not exist.")
		   ((not (active-p g2ds-interface))
		    "The G2 to G2 data server ~
                     could not set a value for variable ~NF ~
                     because ~a is not active.")
		   ((and g2ds-interface-icp-socket
			 (not (icp-connection-open-p g2ds-interface-icp-socket)))
		    "The G2 to G2 data server ~
                     could not set a value for variable ~NF ~
                     because ~NF has lost its ICP connection.")
		   ((null g2ds-interface-icp-socket)
		    "The G2 to G2 data server ~
                     could not set a value for variable ~NF ~
                     because ~NF failed to make an ICP connection."))))
      (cond
	(error-format-string
	 (warning-message 2 error-format-string g2-variable
			  (or g2ds-interface g2ds-interface-name)))
	(t
	 (if (g2ds-variable-value-to-set? g2ds-variable-structure)
	     (reclaim-evaluation-value
	       (g2ds-variable-value-to-set? g2ds-variable-structure)))
	 (setf (g2ds-variable-value-to-set? g2ds-variable-structure)
	       (copy-evaluation-value value-to-set))
	 (enqueue g2ds-variable-structure
		  (g2ds-interface-data-queue-head g2ds-interface-structure)
		  (g2ds-interface-data-queue-tail g2ds-interface-structure)
		  g2ds-cons))))))

;;;; [9.7] Function to Shut Down G2-to-G2 Data Server

;; process-g2ds-variable-values is called when values are returned by the G2ds
;; data server, and also when a connection is being shut down.  The shutdown
;; case is done in order to flush the list of values returned.
;;
;;  This function previously ignored the possibility that it might have to
;;  relinquish the thread of control due to timeslice expiry or the creation of
;;  a higher-priority task (due to the put-current-evaluation-value call). Now,
;;  it checks properly.  -ncc, 5 Jan 1995 

(defun-simple process-g2ds-variable-values (ok-to-put-values?)
  (loop until (time-slice-expired-p)
	as g2-variable-value-cons = (dequeue
				      list-of-g2ds-values-to-process-head
				      list-of-g2ds-values-to-process-tail
				      reclaim-g2ds-cons)
	until (null g2-variable-value-cons)
	as (g2ds-variable-structure . value)
	   = g2-variable-value-cons
	as *current-computation-frame*
	   = (g2ds-variable-g2-frame g2ds-variable-structure)
	as current-computation-instance = *current-computation-frame*
	do
    (when (and ok-to-put-values?	; we're not shutting down data service.

	       ;; check that this variable hasn't been reclaimed:
	       (frame-serial-number-equal (g2ds-variable-g2-frame-serial-number g2ds-variable-structure)
					  ;; Previously, this would take the frame serial number of
					  ;; g2ds-variable-structure, which is never a frame.
					  ;; Only by coincidence did it ever work.  Fixed.  jh, 4/1/91.
					  (frame-serial-number *current-computation-frame*))

	       (g2ds-variable-ok-to-store-values? g2ds-variable-structure))

      (let ((error-text
	      (with-temporary-gensym-float-creation process-g2ds-variable-values
		(put-current-evaluation-value *current-computation-frame* value
					      nil nil nil))))
	(when error-text
	  (warning-message 2
	      "The G2 to G2 data server ~
                could not set a value for variable ~NF ~
                because: ~A"
	    *current-computation-frame*
	    error-text)
	  (reclaim-text-string error-text))))
    (reclaim-g2ds-cons g2-variable-value-cons))

  ;; if we exited because of time-slice expiry, then reschedule this task if any
  ;; values remain to be processed. -jra, ncc, 16 Dec 1994
  (when (examine-head-of-queue list-of-g2ds-values-to-process-head)
    (with-current-scheduling
	(task-to-process-g2ds-values
	  (priority-of-data-service data-server-parameters))
      (process-g2ds-variable-values t))))

(defun g2ds-shut-down-server ()
  (process-g2ds-variable-values nil)
  (cancel-task task-to-process-g2ds-values)
  (setq list-of-all-g2ds-interfaces nil))






;;;; [9.8] Function to Deliver G2-to-G2 Messages

(defun-allowing-unwind  g2ds-send-message
			(message-or-copy
			  urgency? duration?
			  inference-frame destination)
  (let* ((g2ds-interface-name
	   (get-slot-value-if-any destination 'g2-to-g2-interface-name))
	 (g2ds-interface
	   (get-instance-with-name-if-any 'object g2ds-interface-name))
	 (g2ds-interface-structure
	   (if g2ds-interface
	       (get-slot-value-if-any g2ds-interface 'g2ds-interface-structure)))
	 (g2ds-interface-icp-socket
	   (if g2ds-interface-structure
	       (g2ds-interface-socket g2ds-interface-structure))))
    (cond ((null g2ds-interface)
	     (warning-message 2
	       "The G2 to G2 data server ~
                could not send message ~a from ~NF to ~NF ~
                because G2 to G2 interface ~a does not exist."
	       message-or-copy
	       inference-frame
	       destination
	       g2ds-interface-name)
	     (reclaim-text-string message-or-copy))
	    ((not (or (active-p g2ds-interface)
		      (g2-to-g2-interface-connects-while-inactive-p
			g2ds-interface)))
	     (warning-message 2
	       "The G2 to G2 data server ~
                could not send message ~a from ~NF to ~NF ~
                because G2 to G2 interface ~NF is not active."
	       message-or-copy
	       inference-frame
	       destination
	       g2ds-interface)
	     (reclaim-text-string message-or-copy))
	    ((null g2ds-interface-icp-socket)
	     (warning-message 2
	       "The G2 to G2 data server ~
                could not send message - ~a - from ~NF to ~NF ~
                because G2 to G2 interface ~NF failed ~
                to make an ICP connection."
	       message-or-copy
	       inference-frame
	       destination
	       g2ds-interface)
	     (reclaim-text-string message-or-copy))
	    ((not (icp-connection-open-p g2ds-interface-icp-socket))
	     (warning-message 2
	       "The G2 to G2 data server ~
                could not send message ~a from ~NF to ~NF ~
                because G2 to G2 interface ~NF has ~
                lost its ICP connection."
	       message-or-copy
	       inference-frame
	       destination
	       g2ds-interface)
	     (reclaim-text-string message-or-copy))
	    (t 
	     (writing-icp-message-group
	       ((icp-output-port g2ds-interface-icp-socket))
	       (send-icp-g2ds-user-message-string message-or-copy urgency? duration?)
	       (reclaim-text-string message-or-copy))))))






;;;; [9.9] Function to Pause G2-to-G2 Data Server

(defun-allowing-unwind g2ds-pause-server ()
  (loop for g2ds-interface in list-of-all-g2ds-interfaces
        as g2ds-interface-structure = (if (active-p g2ds-interface)
					  (get-slot-value-if-any
					    g2ds-interface
					    'g2ds-interface-structure))
        as g2ds-icp-socket = (if g2ds-interface-structure
				 (g2ds-interface-socket
				   g2ds-interface-structure))
        do (when (and g2ds-icp-socket
		      (icp-connection-open-p g2ds-icp-socket))
	     ;; jh, 6/21/94.  Commented out the following form while reviewing
	     ;; its raison d'etre.  Since the slot-putter for interface-status
	     ;; calls invoke-rules-for-attribute-change-chaining, a whenever
	     ;; rule that checks interface-status will get scheduled in a paused
	     ;; G2 if this form is uncommented.  For reasons I don't quite
	     ;; understand, this blocks all subsequent procedure calls at the
	     ;; same priority from executing.  Since I think that the following
	     ;; form is the only place where a rule is scheduled while G2 is
	     ;; paused, commenting it out will do for now.  Also, no inference
	     ;; based on the fact that an interface-status is paused, and "a
	     ;; difference that makes no difference is no difference".
;	     (change-g2ds-interface-status-throughout
;	       g2ds-interface
;	       (get-slot-value-if-any g2ds-interface 'interface-status)
;	       'paused)
             (writing-icp-message-group
              ((icp-output-port g2ds-icp-socket))
              (send-icp-g2ds-pause-server)))))






;;;; [9.10] Function to Resume G2-to-G2 Data Server

(defun-allowing-unwind g2ds-resume-server ()
  (loop for g2ds-interface in list-of-all-g2ds-interfaces
        as g2ds-interface-structure = (if (active-p g2ds-interface)
					  (get-slot-value-if-any
					    g2ds-interface
					    'g2ds-interface-structure))
        as g2ds-icp-socket = (if g2ds-interface-structure
				 (g2ds-interface-socket
				   g2ds-interface-structure))
        do (if (and g2ds-icp-socket
		    (icp-connection-open-p g2ds-icp-socket))
             (writing-icp-message-group
              ((icp-output-port g2ds-icp-socket))
              (send-icp-g2ds-resume-server)))))




;;; The function `icp-socket-of-interface-object' takes an active ICP interface
;;; object, either a G2-TO-G2-INTERFACE or a GSI-INTERFACE, and
;;; returns the ICP socket for this objects if they are ready to receive
;;; messages.  If no socket is returned, then an error message should be given
;;; about the interface not being ready.

(defun icp-socket-of-interface-object (icp-interface)
  (cond ((ui-client-interface-p-function icp-interface)
	 (let ((interface-icp-socket? (gsi-interface-icp-socket icp-interface)))
	   (when (and interface-icp-socket?
		      ;;javalink connections often start demanding information
		      ;;before the GSI connection handshake has been fully
		      ;;established, especially if G2 is busy (for example
		      ;;loading a KB: see issue HQ-4133732).  --yduJ 3/02
		      (icp-connection-open-p interface-icp-socket?))
	     interface-icp-socket?)))
	((gsi-interface-p icp-interface)
	 (let ((interface-icp-socket? (gsi-interface-icp-socket icp-interface)))
	   (when (and interface-icp-socket?
		      (=f (gsi-connection-state interface-icp-socket?) gsi-connection-established))
	     interface-icp-socket?)))
	((g2-to-g2-data-interface-p icp-interface)
	 (if (memq (interface-status icp-interface)
		   (if (runs-while-inactive-p icp-interface)
		       '(server running paused connected)
		       '(server running paused)))
	     (let ((structure? (g2ds-interface-structure icp-interface)))
	       (if structure?
		   (g2ds-interface-socket structure?)
		   (let ((structure? (g2ds-server-connection-structure icp-interface)))
		     (if structure?
			 (g2ds-server-connection-icp-socket structure?)
			 nil))))))))



;; End file with CR

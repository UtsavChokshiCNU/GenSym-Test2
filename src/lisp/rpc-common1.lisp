;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module RPC-COMMON1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Peter Fandel and John Hodgkinson

;;; This module contains tha data structures and ICP protocols related to remote
;;; procedure calls that are shared between G2 and GSI.  The machinery specific
;;; to G2 remote procedures is in G2-RPC1

;; jh, 12/2/93.  Split the module from PROC-REMOTE.
;; jh, 3/16/94.  Changed the name from RPC-COMMON to RPC-COMMON1.



;;;; Forward references

#+trace-invocations
(declare-forward-reference check-free-remote-procedure-identifier function)

(declare-forward-references (:suppress-module-checks-for gsi)
  (abort-rpc-call-and-reclaim-identifier               function)
  (signal-error-to-rpc-caller-and-reclaim-identifier   function)
  (receive-remote-procedure-asynchronous-abort         function)
  (write-icp-list-of-included-return-attributes        function)
  (read-icp-list-of-included-return-attributes         function)
  (write-icp-list-of-excluded-return-attributes        function)
  (read-icp-list-of-excluded-return-attributes         function)
  (write-icp-list-of-included-return-system-attributes function)
  (read-icp-list-of-included-return-system-attributes  function)
  (write-icp-list-of-include-all-return-system-attributes function)
  (read-icp-list-of-include-all-return-system-attributes  function)
  (write-icp-list-of-include-all-return-system-attributes-except function)
  (read-icp-list-of-include-all-return-system-attributes-except  function)
  (write-icp-list-of-return-kinds                      function)
  (read-icp-list-of-return-kinds                       function)
  (write-icp-remote-procedure-varargs-p                function)
  (read-icp-remote-procedure-varargs-p                 function)
  (filter-text-for-gsi-p                               function)
  (write-icp-item                                      function)
  (read-icp-item                                       function)
  )

(declare-forward-references (:suppress-module-checks-for ab)
  (gsi-error                                       function)
  (gsi-connection-error                            function)
  (gsi-local-function-undefined                    variable)
  (gsi-rpc-async-abort                             variable)
  (make-gsi-instance                               function)
  (gsi-handle-define-remote-procedure-name         function)
  (class-for-gsi-item                              function)
  (gsi-item-is-value-p                             function)
  (make-gsi-sequence                               function)
  (make-gsi-structure                              function)
  (convert-gsi-value-to-value                      function)
  (element-type-for-gsi-type                       function)
  (identifying-attribute-count-for-item-new-copy   variable)
  )



;;; Procedures use the cons pool `proc-cons'.

;; Moved from proc-utils for dependency reasons. 8dec93 paf, jh.

(defconser proc RPC-COMMON1)





;;;; Remote Procedure Calls

;;; The remote procedure call facility is implemented to allow call-in and
;;; call-out between procedures in G2 and foreign processes in GSI.  The calls
;;; between two G2s and between a G2 and a GSI extension use the same ICP
;;; messages and formats.  This module is part of the procedures code, but uses
;;; lots of ICP facilities (in the INT module).

;;; The user accesses remote procedure calls within G2 using the following
;;; grammar.  This action is available within rules and procedures, and should
;;; appear to users as a simple extension to the START action.

;;;   START <remote procedure declaration designation>
;;;         ([<datum arg> {, <datum arg>}])
;;;     [AT PRIORITY <expression>]
;;;     [AFTER <expression>]
;;;     [ACROSS <g2-to-g2 or gsi interface designation>]

;;; The AFTER and AT PRIORITY clauses are still available.  The AFTER clause
;;; will locally delay the initiation of the remote call.  The given priority
;;; will only affect local processing (it takes some processing to initiate the
;;; call) and will not affect the processing which occurs on the remote system.
;;; Within remote G2s, the execution of a remote procedure call begins at
;;; the default priority of the remote procedure.

;;; There must be a declaration for any procedure which will be invoked
;;; remotely.  The remote declaration names the argument and return types of the
;;; remote procedure, as well as the name which will be used for the procedure
;;; in the remote system.  The remote name defaults to the same name as the
;;; local definition.

;;; The argument to the ACROSS grammar is a designation of an active and
;;; connected interface object.  This object can be connected with either
;;; another G2, or with a GSI extension process.  If the designated interface is
;;; not connected, then an error will occur which posts a message on the
;;; logbook.  The rule or procedure which executed the start will be allowed to
;;; continue.  If the procedure does not exist within the remote system, or some
;;; other error occurs in the process of starting the remote execution, then an
;;; error will be posted on the logbook of the G2 which started the remote
;;; procedure.  If an error occurs during the execution of the started remote
;;; procedure, then the source G2 will not be notified, and the remote system
;;; will handle the error in its own local style.

;;; The remote extensions to the CALL facility have the following grammar.

;;;   [<local name> {, <local name} = ]
;;;     CALL <remote procedure declaration designation>
;;;          ([<datum arg> {, <datum arg>}])
;;;       [ACROSS <g2-to-g2 or gsi interface designation>]

;;; Note that this grammar is the same as a local procedure call, but containing
;;; the additional ACROSS grammar.  The local processing to initiate the call
;;; occurs at the same priority as the priority of the procedure invocation
;;; making the call.  This priority does not affect the priority of the call on
;;; the remote system.  Within remote G2s, the execution of the remote procedure
;;; call begins at the default priority of the remote procedure.

;;; If the designated interface object is not connected, then an error is
;;; signalled within the procedure invocation which executed the CALL ACROSS.
;;; Also, if an error occurs within the called remote procedure, then an error
;;; will be signalled within the remote system, and the error will also be
;;; propagated back to the local procedure which initiated the CALL ACROSS.  This
;;; error will locally cause an error message to be posted on the logbook and will
;;; cause the procedure stack to be aborted.  Within future systems, these errors
;;; will be able to be handled with ON ERROR like any other error, even if they
;;; must be propagated across machine boundaries before they are handled (whoa
;;; Nelly, but that's wild).






;;;; ICP Design Specification for Remote Procedure Calls

;;; Jim Allard and John Hodgkinson: March 2, 1990

;; Moved from INT (jh, 9/12/90).

;;; The aims are to keep this design abstract enough for future extensions, but
;;; able to encompass the functionality most desired for the current release,
;;; namely, facile database access.

;;; There are some restrictions on the current ICP mechanism.  Arguments to
;;; remote procedures can only consist of numbers, symbols, strings, or
;;; truth-values.  The number of arguments taken by the remote procedure must be
;;; known in advance.  Synchronous aborts are not yet supported.

;;; This specification lists the new ICP data structures and ICP message type
;;; needed to implement remote procedure calls.

;;; Data Structures

;;; remote-procedure-name                                       [ICP object type]

;;; slot:       remote-procedure-name-symbol,   a symbol

;;; A remote-procedure-name is a wrapper around an ICP-symbol denoting
;;; a remote procedure.  The rationale behind creating a separate
;;; ICP object type for this purpose is GSI requirements for extra slots
;;; to hook into a C function (since we cant just use the symbol).




;;; remote-values-list                                          [ICP value type]
;;; read-remote-values-list                                     [function]
;;; write-remote-values-list                                    [function]

;;; A list of evaluation-value structures used to transmit argument lists and
;;; return values for remote procedure calls.  A remote-values-list must be
;;; unnested, and may contain any of the types number (including any number
;;; subtype), symbol, text, or truth-value, in any order.  If a
;;; remote-values-list contains an object in the values list which is not one of
;;; these types, the resulting element of the values list is a evaluation
;;; value of type 'rpc-unknown-type.




;;; remote-procedure-identifier                                 [ICP object]

;;; slot:       remote-procedure-identifier-tag,         an unsigned-integer

;;; When a process calls a remote procedure, a continuation is waiting for the
;;; returned values.  That continuation needs a name, so the remote procedure
;;; can return its values to the right place.  The remote-procedure-identifier
;;; structure stores a pointer to the calling continuation.  Instances of this
;;; structure contain one slot used by ICP, an unsigned integer representing an
;;; entry point for the continuation.  This integer is unique to the ICP
;;; connection across which the remote call takes place.  This constraint allows
;;; remote calls to two processes, each through a different ICP socket, to work
;;; properly even if by chance each chooses to represent its continuation with
;;; the same integer.  The structure will contain other slots specific to the
;;; ICP implementation needed to represent call in and call out for that ICP
;;; implementation.

;;; Using an unsigned integer is the "lowest common denominator" for
;;; representing continuations: any process should be able to denote a
;;; continuation with an integer.  In lisp G2, this integer maps to a
;;; code-body-invocation instance, so the procedure which called the remote
;;; procedure can resume with the values returned from the remote system.  For
;;; call-ins to G2 from extension processes, things are more flexible.  In this
;;; case, the remote-procedure-callback slot will contain anything which can
;;; denote a continuation to the extension process, for example, an index into
;;; an array of function pointers.



;;; Message Types and Handler Functions

;;; RPC-start                                                   [ICP message type]
;;; (sent from source to target)
;;;
;;; arguments:  started-procedure-name, a remote-procedure-name
;;;             argument-list,          a remote-values-list
;;;
;;; Starts a remote procedure asynchronously.  Differs from RPC-call in that no
;;; callback argument is needed, since the sender doesn't plan to continue with
;;; the results of the remote procedure call.

;;; receive-start-remote-procedure                              [function]
;;; (executed at lisp targets)
;;;
;;; arguments:  ICP-socket,             an ICP-socket structure
;;;             procedure-name,         a symbol
;;;             arglist,                a list of evaluation-values
;;;
;;; Called by the handler for RPC-start messages.  Note that it needs an ICP
;;; socket to individuate procedures of the same name called at different
;;; sources.  Receive-start-remote-procedure gets its procedure-name argument
;;; from the remote-procedure-name structure passed to the handler.



;;; RPC-call                                                    [ICP message type]
;;; (sent from source to target)
;;;
;;; arguments:  called-procedure-name,          a remote-procedure-name
;;;             remote-caller,                  a remote-procedure-identifier
;;;             argument-list,                  a remote-values-list
;;;
;;; Calls a remote procedure synchronously.  Differs from RPC-start in that a
;;; callback argument is needed so that the source can resume with the values
;;; returned by the remote procedure.

;;; receive-call-remote-procedure                               [function]
;;; (executed at lisp targets)
;;;
;;; arguments:  ICP-socket,             an ICP-socket structure
;;;             procedure-name,         a symbol
;;;             caller-identification,  a remote-procedure-identifier
;;;             arglist,                a list of evaluation-values
;;;
;;; Called by the handler for RPC-call messages.  Note that it needs an ICP
;;; socket to individuate procedures of the same name called at different
;;; sources.  It gets its procedure-name and caller-identification arguments
;;; from the remote-procedure-name and remote-procedure-identification arguments
;;; passed to the handler.



;;; RPC-error                                                   [ICP message type]
;;; (sent from target to source)
;;;
;;; arguments:  error-name,     a symbol (always 'rpc-error as of 3/2/90 - jra 
;;;                             & jh)
;;;             error-level,    an unsigned integer (from 1-4 inclusive as of
;;;                             3/2/90 - jra & jh)
;;;             error-string,   a text-string
;;;             error-arglist,  a remote-values-list (currently always nil)
;;;
;;; Sends an error string when the target is unable to initiate a remote
;;; procedure requested by the source (either by RPC-call or RPC-start).  For
;;; instance the remote system may not be able to locate the procedure to be
;;; called, or the source may lack authorization to run that particular remote
;;; procedure on the target system.  In the current design, RPC errors are
;;; fatal at both the source and target.  Therefore, unlike RPC-error-to-caller,
;;; RPC-error does not have a remote-caller or a signaller? argument.

                
;;; receive-remote-procedure-error                              [function]
;;; (executed at lisp sources)
;;; ...




;;; RPC-error-to-caller                                         [ICP-message-type]
;;; (sent from target to source)
;;;
;;; arguments:  remote-caller,  an unsigned-integer
;;;             signaller?,     an integer or nil (explained below)
;;;             error-name,     a symbol (always 'rpc-error as of 3/2/90 - jra
;;;                             & jh)
;;;             error-level,    an unsigned integer (from 1-4 inclusive as of
;;;                             3/2/90 - jra & jh)
;;;             error-string,   a text-string
;;;             error-arglist,  a remote-values-list
;;;
;;; Informs the source that a remote procedure encountered an error.
;;;
;;; The signaller? argument is included in order to allow the source to instruct
;;; the target to continue from the error.  If signaller? is non-nil, it
;;; represents the continuation on the remote system which will proceed from
;;; the error.  If signaller? is nil, no continuation is possible.
;;;
;;; Signaller? will always be nil in the current implementation (jra & jh,
;;; 3/2/90).  A null signaller? represents a fatal error, and must cause the
;;; source to issue an RPC-abort message.    Future RPC implementations will
;;; include the ICP message type RPC-continue-from-error which will utilize a
;;; non-nil signaller? argument.

;;; receive-remote-procedure-error-for-caller                   [function]
;;; (executed at lisp sources)
;;; ...




;;; RPC-asynchronous-abort                                      [ICP message type]
;;; (sent from source to target)
;;;
;;; argument:   procedure-to-be-aborted,        a remote-procedure-identifier
;;;
;;; Sends an abort request to the remote procedure, which then immediately sends
;;; back an RPC-acknowledge-abort message.  Future RPC implementations will also
;;; contain the ICP message type RPC-synchronous-abort, which waits until the
;;; remote process has confirmed that any clean up code for an abort (such as ON
;;; ABORT code) is complete.  The given remote-procedure-identifier may not be
;;; reclaimed until this abort message is acknowledged with an
;;; RPC-acknowledge-abort message.  Note that any RPC-return-values messages
;;; received for this remote-procedure-identifier should be ignored.
;;;
;;; receive-remote-procedure-asynchronous-abort                 [function]
;;; (executed at lisp targets)
;;; ... 





;;; RPC-acknowledge-abort                                       [ICP message type]
;;; (sent from target to source)
;;;
;;; argument:   procedure-aborted,              an unsigned-integer
;;;
;;; Receives an acknowledgement of a synchronous or asynchronous abort message.
;;; The handler for this message is now free to reclaim the remote procedure
;;; identifier tag number for this remote-procedure-identifier object.  The
;;; source must wait for acknowledgement before reclaiming the
;;; remote-procedure-identifier, since the the remote system may send back
;;; messages about this remote-procedure-identifier before it receives the abort
;;; message.  If the remote-procedure-identifier is reclaimed before
;;; acknowledgement, the identifier may be reallocated and incorrectly receive
;;; messages which were intended for the remote call which had been aborted.




;;; RPC-return-values                                           [ICP message type]
;;; (sent from target to source)
;;;
;;; arguments:  calling-procedure-index,        an unsigned-integer (explained below)
;;;             values-list,                    a remote-values-list
;;;
;;; Returns a list of values from a successfully completed remote procedure
;;; call.
;;;
;;; Note that the argument calling-procedure-index is not an ICP object of type
;;; ICP-procedure-caller.  This is because corresponding ICP objects are not
;;; bidirectional.  This means that if the source sends the target an object,
;;; the target cannot, without additional management, simply return the
;;; identical object back to the source.  For the particular case of returning
;;; RPC values, however, this is not a problem.  The only thing the source cares
;;; about is associating a list of return values with whatever code invoked the
;;; remote procedure.  And this association only requires one thing, the integer
;;; in the remote-procedure-caller slot of the ICP-procedure-caller object.  It
;;; is not necessary to send the entire ICP object, then, just the integer
;;; inside it.
;;;
;;; This message handler should be careful about receiving values for
;;; remote-procedure-identifiers for which the source has sent abort messages.
;;; Since the target may have sent values back before it received the abort
;;; message.  So, any values received for a call which has been aborted should
;;; simply be ignored.




;;; receive-remote-procedure-values                             [function]
;;; (executed at lisp sources)
;;; ...



;;; RPC-suspend                                                 [ICP message type]
;;; RPC-resume                                                  [ICP message type]
;;;
;;; These message types are for future RPC implementations.  They will enable
;;; remote procedure calls to be suspended and resumed, for remote systems with
;;; this ability.



;; This section contains ICP definitions for remote procedure calls.
;; More comprehensive documentation should be added.  (jh, 3/4/90)



;; ICP object types for remote procedure calls

;; ICP message type codes which manage RPC-related objects reserve integers 220
;; through 229.

;; GSI local function structures are needed for GSI user code to declare
;; local C functions as available for invocation by G2 via RPC.  User calls
;; to gsi-rpc-declare-local cause such structure to be created.  They are
;; later tied into remote-procedure-name structures by the GSI handler
;; for define-remote-procedure-name.

(def-structure gsi-local-function
  gsi-function-pointer
  (gsi-function-user-data nil)
  gsi-function-name-in-g2)

(def-structure (gsi-remote-procedure
		 (:reclaimer reclaim-gsi-remote-procedure-internal))
  procedure-name-in-g2
  gsi-remote-procedure-name-structure
  gsi-return-function
  gsi-error-return-function
  (gsi-return-function-user-data nil)
  gsi-rpc-argument-count
  gsi-rpc-return-count
  (gsi-rpc-return-kind-list nil)
  (gsi-rpc-return-excluded-attributes nil)
  (gsi-rpc-return-included-system-attributes nil)
  (gsi-rpc-return-include-all-system-attributes nil)
  (gsi-rpc-return-include-all-system-attributes-except nil)
)

;; reclaim the contents of a gsi-remote-procedure and then
;; reclaim the structure itself.  --ncc 18 Feb 1994 
(defun reclaim-gsi-remote-procedure (remote-procedure)
  (let* ((remote-procedure-name-structure (gsi-remote-procedure-name-structure remote-procedure)))
    (when remote-procedure-name-structure
      (reclaim-remote-procedure-name remote-procedure-name-structure)
      (setf (gsi-remote-procedure-name-structure remote-procedure) nil))
    (when (gsi-rpc-return-kind-list remote-procedure)
      (reclaim-gensym-list (gsi-rpc-return-kind-list remote-procedure))
      (setf (gsi-rpc-return-kind-list remote-procedure) nil))
    (when (gsi-rpc-return-excluded-attributes remote-procedure)
      (reclaim-gsi-tree (gsi-rpc-return-excluded-attributes remote-procedure))
      (setf (gsi-rpc-return-excluded-attributes remote-procedure) nil))
    (when (gsi-rpc-return-included-system-attributes remote-procedure)
      (reclaim-gsi-tree (gsi-rpc-return-included-system-attributes remote-procedure))
      (setf (gsi-rpc-return-included-system-attributes remote-procedure) nil))
    (when (gsi-rpc-return-include-all-system-attributes remote-procedure)
      (reclaim-gsi-tree (gsi-rpc-return-include-all-system-attributes remote-procedure))
      (setf (gsi-rpc-return-include-all-system-attributes remote-procedure) nil))
    (when (gsi-rpc-return-include-all-system-attributes-except remote-procedure)
      (reclaim-gsi-tree (gsi-rpc-return-include-all-system-attributes-except remote-procedure))
      (setf (gsi-rpc-return-include-all-system-attributes-except remote-procedure) nil))
    (reclaim-gsi-remote-procedure-internal remote-procedure)))


(defvar current-remote-procedure-identifier nil)	
(defvar current-invocation-remotely-started-p nil)
(defvar rpc-argument-count-override? nil)
							
							
							            


;; remote-procedure-name

(def-structure (remote-procedure-name
                 (:constructor make-remote-procedure-name
                               (remote-procedure-name-symbol))
                 (:reclaimer reclaim-remote-procedure-name-internal)
		 #+development
		 (:print-function print-remote-procedure-name))
  remote-procedure-name-symbol
  (ICP-object-map-for-remote-procedure-name nil)
  (gsi-local-function nil)) ; Added for GSI (can't get to a C function by symbol).

(defun-simple make-remote-procedure-name-function (remote-procedure-name-symbol)
  (make-remote-procedure-name remote-procedure-name-symbol))

#+development
(defun print-remote-procedure-name (rpn stream depth)
  (declare (ignore depth))
  (printing-random-object (rpn stream)
    (current-system-case
      (gsi
	(format t "REMOTE-PROCEDURE-NAME ~S"
		(remote-procedure-name-symbol rpn)))
      (t
	(format stream "REMOTE-PROCEDURE-NAME ~S"
		(remote-procedure-name-symbol rpn))))))

(defun reclaim-remote-procedure-name (remote-procedure-name)
  (reclaim-icp-object-map-for-remote-procedure-name remote-procedure-name)
  (reclaim-remote-procedure-name-internal-macro remote-procedure-name))

(defun reclaim-remote-procedure-name-structure (remote-procedure-name)
  (reclaim-remote-procedure-name-internal-macro remote-procedure-name))




;;; The function `reclaim-remote-procedure-name-for-connection-loss' takes a
;;; remote-procedure-name structure and an ICP-port as arguments.  When a
;;; connection is broken, this function will be called for every
;;; remote-procedure-name which has a corresponding object across the
;;; connection.  When the given ICP-port is an output port, then this is the
;;; original name object, and it should be left alone.  When the port is an
;;; input port, then this is a corresponding object and it should be reclaimed.

(defun reclaim-remote-procedure-name-for-connection-loss
       (remote-procedure-name icp-port)
  (when (eq (icp-port-direction icp-port) 'input)
    (reclaim-remote-procedure-name remote-procedure-name)))

(def-icp-object-type remote-procedure-name
                     (standard-icp-object-index-space
                       (icp-object-map-for-remote-procedure-name
                         remote-procedure-name)
                       reclaim-remote-procedure-name-structure
                       reclaim-remote-procedure-name-for-connection-loss)
  (send-icp-define-remote-procedure-name 
    corresponding-icp-object-index 
    (remote-procedure-name-symbol remote-procedure-name)))

(def-icp-message-type define-remote-procedure-name
                      (corresponding-icp-object-index
                       (symbol remote-procedure-name-symbol))
  (let ((new-remote-procedure-name 
          (make-remote-procedure-name
	    remote-procedure-name-symbol)))
    (store-corresponding-icp-object
      corresponding-icp-object-index
      new-remote-procedure-name)))

;;; I really want to send this last error back to G2 as well and want to
;;; incorporate the general ability to 'CC' G2 on any call to gsi-error.
;;; paf! 16dec93




;; remote-procedure-identifier

(def-structure (remote-procedure-identifier
		 (:constructor make-remote-procedure-identifier
                  (remote-procedure-identifier-tag
		   remote-procedure-item-passing-info)))
  #+trace-invocations
  (remote-procedure-identifier-mark nil)
  (remote-procedure-identifier-tag nil)
  (icp-object-map-for-remote-procedure-identifier nil)
  (remote-procedure-identifier-caller nil)
  (remote-procedure-identifier-callee nil)
  (remote-procedure-identifier-resumable-objects
    nil :reclaimer reclaim-icp-list)
  (remote-procedure-identifier-state 'outstanding) ; for GSI. Can be outstanding,
                                                   ; returned, async-aborted, or
                                                   ; sync-aborted. -paf! 7jun95
  (remote-procedure-identifier-gsi-user-data nil)
  (remote-procedure-item-passing-info
    nil :reclaimer reclaim-remote-procedure-item-passing-info)
  (remote-procedure-identifier-awaiting-acknowledge-abort nil)
  (remote-procedure-identifier-name-symbol nil))


(defun-simple make-outgoing-remote-procedure-identifier (tag info)
  (make-remote-procedure-identifier tag info))

(defun-simple reclaim-outgoing-remote-procedure-identifier (remote-procedure-identifier)
  #+trace-invocations
  (check-free-remote-procedure-identifier remote-procedure-identifier)
  (setf (remote-procedure-identifier-awaiting-acknowledge-abort remote-procedure-identifier) nil)
  (reclaim-remote-procedure-identifier remote-procedure-identifier))

(defun-simple make-incoming-remote-procedure-identifier (tag info)
  (make-remote-procedure-identifier tag info))

(defun-simple reclaim-incoming-remote-procedure-identifier (remote-procedure-identifier)
  #+trace-invocations
  (check-free-remote-procedure-identifier remote-procedure-identifier)
  (setf (remote-procedure-identifier-awaiting-acknowledge-abort remote-procedure-identifier) nil)
  (reclaim-remote-procedure-identifier remote-procedure-identifier))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro with-remote-procedure-info
    ((remote-procedure-identifier
       included-attributes-spec excluded-attributes-spec included-system-attributes-spec
       include-all-system-attributes-spec include-all-system-attributes-except-spec kind-spec varargsp)
     &body body)
  (let ((item-passing-info (make-symbol "ITEM-PASSING-INFO"))
	(item-info (make-symbol "ITEM-INFO")))
    `(loop with ,item-passing-info = (remote-procedure-item-passing-info ,remote-procedure-identifier)
	   with ,varargsp = (remote-procedure-item-passing-info-varargs-p ,item-passing-info)
	   for ,item-info in (remote-procedure-item-passing-info-item-info-list ,item-passing-info)
	   collect (remote-procedure-item-info-included-attributes ,item-info)
	     into ,included-attributes-spec using gensym-cons
	   collect (remote-procedure-item-info-excluded-attributes ,item-info)
	     into ,excluded-attributes-spec using gensym-cons
	   collect (remote-procedure-item-info-included-system-attributes ,item-info)
	     into ,included-system-attributes-spec using gensym-cons
	   collect (remote-procedure-item-info-include-all-system-attributes ,item-info)
	     into ,include-all-system-attributes-spec using gensym-cons
	   collect (remote-procedure-item-info-include-all-system-attributes-except ,item-info)
	     into ,include-all-system-attributes-except-spec using gensym-cons
	   collect (remote-procedure-item-info-kind ,item-info)
	     into ,kind-spec using gensym-cons
	   finally
	     (return
	       (prog1 (progn ,@body)
		 (reclaim-gensym-list ,included-attributes-spec)
		 (reclaim-gensym-list ,excluded-attributes-spec)
		 (reclaim-gensym-list ,included-system-attributes-spec)
		 (reclaim-gensym-list ,include-all-system-attributes-spec)
		 (reclaim-gensym-list ,include-all-system-attributes-except-spec)
		 (reclaim-gensym-list ,kind-spec))))))
)

(defun make-remote-procedure-item-info
    (included-attributes excluded-attributes included-system-attributes
     include-all-system-attributes include-all-system-attributes-except kind)
  (let ((list (gensym-list included-attributes excluded-attributes included-system-attributes
			   include-all-system-attributes include-all-system-attributes-except kind)))
    (prog1 (intern-list list)
      (reclaim-gensym-list list))))

(defun make-remote-procedure-item-info-old
    (included-attributes excluded-attributes included-system-attributes
     include-all-system-attributes kind)
  (let ((list (gensym-list included-attributes excluded-attributes included-system-attributes
			   include-all-system-attributes kind)))
    (prog1 (intern-list list)
      (reclaim-gensym-list list))))

(defun-simple remote-procedure-item-info-included-attributes (x)
  (when x (first (interned-list--list x))))

(defun-simple remote-procedure-item-info-excluded-attributes (x)
  (when x (second (interned-list--list x))))

(defun-simple remote-procedure-item-info-included-system-attributes (x)
  (when x (third (interned-list--list x))))

(defun-simple remote-procedure-item-info-include-all-system-attributes (x)
  (when x (fourth (interned-list--list x))))

(defun-simple remote-procedure-item-info-include-all-system-attributes-except (x)
  (when x (fifth (interned-list--list x))))

(defun-simple remote-procedure-item-info-kind (x)
  (when x (sixth (interned-list--list x))))

(defun-simple remote-procedure-item-info-kind-function (x)
  (remote-procedure-item-info-kind x))


(eval-when (:compile-toplevel :load-toplevel :execute)
(def-structure (remote-procedure-item-passing-info
		 (:constructor
		   make-remote-procedure-item-passing-info-1
		   (remote-procedure-item-passing-info-interned-varargsp+item-info-list))
		 (:reclaimer reclaim-remote-procedure-item-passing-info-1))
  remote-procedure-item-passing-info-interned-varargsp+item-info-list)


(defmacro remote-procedure-item-passing-info-item-info-list (x)
  `(cdr (interned-list--list
	  (remote-procedure-item-passing-info-interned-varargsp+item-info-list ,x))))
)

(defmacro remote-procedure-item-passing-info-varargs-p (x)
  `(car (interned-list--list
	  (remote-procedure-item-passing-info-interned-varargsp+item-info-list ,x))))

(defun-void reclaim-remote-procedure-item-passing-info (remote-procedure-item-passing-info)
  (when (remote-procedure-item-passing-info-p remote-procedure-item-passing-info)
    (reclaim-remote-procedure-item-passing-info-1 remote-procedure-item-passing-info)))

(def-structure (interned-remote-procedure-item-passing-info
		 (:include remote-procedure-item-passing-info)
		 (:constructor
		   make-interned-remote-procedure-item-passing-info-1
		   (remote-procedure-item-passing-info-interned-varargsp+item-info-list))))

(defun-simple make-remote-procedure-item-passing-info-from-specs
    (internedp included-attributes-spec excluded-attributes-spec included-system-attributes-spec
	       include-all-system-attributes-spec include-all-system-attributes-except-spec kind-spec varargs-p)
  (let ((interned-list (make-remote-procedure-item-passing-info-from-specs-1
			 included-attributes-spec excluded-attributes-spec
			 included-system-attributes-spec include-all-system-attributes-spec
			 include-all-system-attributes-except-spec kind-spec varargs-p)))
    (if internedp
	(make-interned-remote-procedure-item-passing-info-1 interned-list)
	(make-remote-procedure-item-passing-info-1 interned-list))))

(defun-simple make-remote-procedure-item-passing-info-from-specs-1
    (included-attributes-spec excluded-attributes-spec included-system-attributes-spec
     include-all-system-attributes-spec include-all-system-attributes-except-spec
     kind-spec varargs-p)
  (let* ((list-of-interned-item-infos
	   (loop for incl-attr-tail = included-attributes-spec then (cdr incl-attr-tail)
		 for excl-attr-tail = excluded-attributes-spec then (cdr excl-attr-tail)
		 for incl-sys-attr-tail = included-system-attributes-spec then (cdr incl-sys-attr-tail)
		 for incl-all-sys-attr-tail = include-all-system-attributes-spec then (cdr incl-all-sys-attr-tail)
		 for incl-all-sys-attr-except-tail = include-all-system-attributes-except-spec then (cdr incl-all-sys-attr-except-tail)
		 for kind-tail = kind-spec then (cdr kind-tail)
		 while (or incl-attr-tail excl-attr-tail
			   incl-sys-attr-tail incl-all-sys-attr-tail incl-all-sys-attr-except-tail kind-tail)
		 for incl-attr = (car incl-attr-tail)
		 for excl-attr = (car excl-attr-tail)
		 for incl-sys-attr = (car incl-sys-attr-tail)
		 for incl-all-sys-attr = (car incl-all-sys-attr-tail)
		 for incl-all-sys-except-attr = (car incl-all-sys-attr-except-tail)
		 for kind = (car kind-tail)
		 collect (make-remote-procedure-item-info
			   incl-attr excl-attr
			   incl-sys-attr incl-all-sys-attr incl-all-sys-except-attr
			   kind)
		   using icp-cons))
	 (list-to-intern (icp-cons varargs-p list-of-interned-item-infos)))
    (prog1 (intern-list list-to-intern)
      (reclaim-icp-list list-to-intern))))






;;; The function `reclaim-remote-procedure-identifier-for-connection-loss' is
;;; called with a remote-procedure-identifier and an icp port when an ICP
;;; connection is lost.  If the ICP port is an input port, then the given
;;; identifier is the base of a procedure call stack in a server of RPCs.  This
;;; stack should be silently aborted.  If the ICP port is an output port, then
;;; the given identifier is the leaf of a procedure stack which represents a
;;; client's call to an RPC.  The caller should have an error signalled into it.
;;; In all cases, the remote-procedure-identifier structure itself needs to be
;;; reclaimed.

(defun reclaim-remote-procedure-identifier-for-connection-loss
       (remote-procedure-identifier icp-port)
  (if (eq (icp-port-direction icp-port) 'input)
      ;; Base of stack.
      (abort-rpc-call-and-reclaim-identifier remote-procedure-identifier)
      ;; Leaf of stack.
      (signal-error-to-rpc-caller-and-reclaim-identifier remote-procedure-identifier)))

(def-icp-object-type remote-procedure-identifier
                     (standard-icp-object-index-space
                       (icp-object-map-for-remote-procedure-identifier
                         remote-procedure-identifier)
                       reclaim-incoming-remote-procedure-identifier
                       reclaim-remote-procedure-identifier-for-connection-loss)
  (with-remote-procedure-info
      (remote-procedure-identifier
	included-attributes-spec excluded-attributes-spec included-system-attributes-spec
	include-all-system-attributes-spec include-all-system-attributes-except-spec kind-spec varargsp)
    (send-icp-define-remote-procedure-identifier
      corresponding-icp-object-index
      (remote-procedure-identifier-tag remote-procedure-identifier)
      included-attributes-spec excluded-attributes-spec included-system-attributes-spec
      include-all-system-attributes-spec include-all-system-attributes-except-spec kind-spec varargsp)))
      

;; ICP message type codes for RPC-related objects reserves integers 220 through
;; 229.


(def-icp-message-type define-remote-procedure-identifier
                      (corresponding-icp-object-index
                       (unsigned-integer remote-procedure-identifier-tag)
		       list-of-included-return-attributes
		       list-of-excluded-return-attributes
		       list-of-included-return-system-attributes
		       list-of-include-all-return-system-attributes
		       list-of-include-all-return-system-attributes-except
		       list-of-return-kinds
		       remote-procedure-varargs-p)
  (let ((new-remote-procedure-identifier
          (make-incoming-remote-procedure-identifier
            remote-procedure-identifier-tag
	    (make-remote-procedure-item-passing-info-from-specs
	      nil ; not interned
	      list-of-included-return-attributes
	      list-of-excluded-return-attributes
	      list-of-included-return-system-attributes
	      list-of-include-all-return-system-attributes
	      list-of-include-all-return-system-attributes-except
	      list-of-return-kinds
	      remote-procedure-varargs-p))))
    (reclaim-icp-tree list-of-included-return-attributes)
    (reclaim-icp-tree list-of-excluded-return-attributes)
    (reclaim-icp-tree list-of-included-return-system-attributes)
    (reclaim-icp-tree list-of-include-all-return-system-attributes)
    (reclaim-icp-tree list-of-include-all-return-system-attributes-except)
    (reclaim-icp-tree list-of-return-kinds)
    (store-corresponding-icp-object
      corresponding-icp-object-index
      new-remote-procedure-identifier))) 


(defun-void reclaim-rpc-argument-list (list do-not-reclaim-arguments)
  (runtime-current-system-case
    (gsi
      do-not-reclaim-arguments
      (when list
	(gsi-reclaim-managed-array list)))
    (t
      (when list
	(unless do-not-reclaim-arguments
	  (loop for value in list
		do
	    (reclaim-if-evaluation-value value)))
	(reclaim-eval-list list)))))

(defmacro reclaim-rpc-argument-list-1 (list)
  `(reclaim-rpc-argument-list ,list nil))

;See transform-rpc-argument-or-result-list
(defun-void reclaim-transformed-rpc-argument-list (list do-not-reclaim-arguments)
  (runtime-current-system-case
    (gsi
      do-not-reclaim-arguments
      (when list
	(gsi-reclaim-managed-array list)))
    (t
      (when list
	(loop for value in list
	      for argument = (if (consp value)
				 (case (car value)
				   ((handle value reference)
				    (prog1 (cdr value) (reclaim-icp-cons value)))
				   ((copy by-copy-with-handle)
				    (prog1 (cadr value) (reclaim-icp-list value)))
				   (t
				    value))
				 value)
	      unless do-not-reclaim-arguments
		do (reclaim-if-evaluation-value argument))
	(reclaim-eval-list list)))))

(defun reclaim-unprocessed-rpc-argument-list (list initial-rpc-frame-serial-number
						   &optional nargs-to-skip?)
  (current-system-case
    (ab (when list
 	  ;; If we wanted to be anal, we could add an efficiency optimization,
	  ;; by passing in :all which means don't skip any in order to avoid
	  ;; cdr'ing down the entire list for no reason, but these are
	  ;; usually small lists, so any added gain will usually be mostly lost by
	  ;; having an extra test -dkuznick, 10/24/01
	  (loop for value in (if nargs-to-skip?
				 (nthcdr nargs-to-skip? list)
				 list)
		do
	    (if (framep value)
		(when (and (transient-p value)
			   (frame-serial-number-< initial-rpc-frame-serial-number
						  (frame-serial-number value)))
		  (delete-frame value))
		(reclaim-if-evaluation-value value)))
	  (reclaim-eval-list list)))
    (t list initial-rpc-frame-serial-number nargs-to-skip?
       nil)))



;; remote-value writer and reader were moved here on 21 Feb 1994 by ncc

;;; Remote (nee GSI Data) Values and GSI Parameters

;;; remote-values (were called GSI Data-values) and gsi-parameters will be sent as
;;; a type code followed by the value of the data item or parameter.

;;; Declaration:     remote-value 
;;; Type:	     ICP value type.
;;; Purpose:	     Represent the value of a GSI sensor.
;;; Arguments:       A gsi data value is a evaluation-value structure (in GSI it
;;;                  is a gsi-instance structure with a far more rich makeup) containing a
;;;                  value of the following G2 types: truth-value, integer, float,
;;;                  number, symbol, text.  These values are transmitted and
;;;                  received in the following manner:
;;;                  > truth-value: G2 represents truth values internally as a
;;;                    fixnum between -1000 and +1000 inclusive.  After sending the
;;;                    truth-value tag, G2 transmits this fixnum using the ICP value
;;;                    type integer.  G2 receives values of type truth-value using
;;;                    the ICP value type integer as well.
;;;                  > integer: G2 transmits this as the ICP value type integer.
;;;                    Since C longs may overflow Lisp fixnums, G2 receives values
;;;                    of type integer using the ICP value type fixnum, which uses
;;;                    wraparound to receive the value without signalling an error.
;;;                  > float: G2 transits and receives values of this type using the
;;;                    ICP value type double-float.  If it is communicating to a GSI
;;;                    process earlier than 2.0, it uses the ICP value type float.
;;;                  > number: If the value is a fixnum, it is transmitted using the
;;;                    ICP value type integer.  If the value is a float, it is
;;;                    transmitted using the ICP value type double-float.  The
;;;                    remote GSI process does not have a tag for the G2 number
;;;                    type, so when it transmits numeric values, it specifically
;;;                    uses either integers or floats.
;;;                  > symbol: the name of the symbol is transmitted and received
;;;                    using ICP value type text-string.
;;;                  > text: the text is transmitted and received using ICP value
;;;                    type text-string.
;;; Return behavior: N/A.
;;; Users:	     GSI internals:
;;;                    load-sensor-list-element
;;;                    receive-value-for-gsi-sensor
;;;                    receive-value-for-gsi-sensor-with-timestamp
;;;                    receive-gsi-sensor-value-vector
;;;                    receive-timestamped-gsi-sensor-value-vector
;;; Prerequisites:   Uses the ICP value types fixnum, integer, float, double-float,
;;;                  and text-string.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   A evaluation-value structure is allocated when an ICP value
;;;                  of this type is read.  The reader must reclaim this structure.
;;; Notes:           Consider using the symbol ICP object type instead of
;;;                  transmitting the printnames anew each time.

;; jh, 11/25/91.  Added a check for the gsi-data-server-filters-text?  attribute
;; in the data-server-parameters system table.  This allows users a tradeoff
;; between speed and safety when G2 transmits and receives text strings.


(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar write-remote-value-items-kind 'copy)

;; jra & jh, 11/10/92.  Modified the value writer for remote-value to 
;; use managed floats where possible, as part of the project to improve
;; GSI performance.

(defvar gsi-remote-value-creates-instance-p t)
(defvar gsi-remote-value-conses-logical-p nil)
(defvar write-value-of-gsi-item-p nil)
(defvar remote-value-is-binary-p nil)

(defmacro make-remote-value (system type value-form)
  (case system
    (gsi
     (let ((tag-symbol
	     (case type
	       (null        (setq value-form nil)
			    nil)
	       (truth-value 'gsi-logical-type-tag)
	       (integer     'gsi-integer-type-tag)
	       (long        'gsi-long-type-tag)
	       (float       'gsi-64bit-float-type-tag)
	       (symbol      'gsi-symbol-type-tag)
	       (text        (setq value-form `(convert-value-to-gsi-value ,value-form))
			    'gsi-string-type-tag)
	       (unsigned-short-vector
		            'gsi-unsigned-short-vector-type-tag)
	       (handle      'gsi-item-handle-type-tag)
	       (t           nil))))
       `(if gsi-remote-value-creates-instance-p
	    (make-gsi-instance ,tag-symbol ,value-form nil nil nil
			       (if identifying-attribute-count-for-item-new-copy
				   'context
				   (default-owner-for-gsi-objects)))
	    ,(if (eq type 'truth-value)
		 `(if gsi-remote-value-conses-logical-p
		      (gsi-cons ,value-form 'truth-value)
		      ,value-form)
		 value-form))))
    (g2
     (case type
       (null        nil)
       (truth-value `(make-evaluation-truth-value ,value-form))
       (integer     `(make-evaluation-integer ,value-form))
       (long        value-form)
       (float       value-form)
       (symbol      value-form)
       (text        value-form)
       (unsigned-short-vector
	            `(maybe-make-evaluation-unsigned-vector-16
		       (mark-wide-string-as-binary ,value-form)))
       (handle      value-form)
       (t           nil)))))

(def-substitution-macro value-or-gsi-instance-value (value)
  (cond ((gsi-instance-p value)
	 (gsi-instance-value value))
	((consp value)
	 (car-of-cons value))
	(t
	 value)))

(defmacro remote-value-value (system type remote-value-form)
  (case system
    (gsi
      (case type
	(null        nil)
	(truth-value `(value-or-gsi-instance-value ,remote-value-form))
	(integer     `(value-or-gsi-instance-value ,remote-value-form))
        (long        `(value-or-gsi-instance-value ,remote-value-form))
	(float       `(value-or-gsi-instance-value ,remote-value-form))
	(symbol      `(value-or-gsi-instance-value ,remote-value-form))
	(text        `(convert-gsi-value-to-value
			(value-or-gsi-instance-value ,remote-value-form)))
	(unsigned-short-vector
	             `(value-or-gsi-instance-value ,remote-value-form))
	(handle      `(value-or-gsi-instance-value ,remote-value-form))
	(t           remote-value-form)))
    (g2
     (case type
       (truth-value  `(evaluation-truth-value-value ,remote-value-form))
       (unsigned-short-vector
	             `(if (consp ,remote-value-form)
			  (evaluation-unsigned-vector-16-value ,remote-value-form)
			  ,remote-value-form))
       (t            remote-value-form)))))

(defmacro remote-value-reclaim-converted-value (system type remote-value-form value)
  (case system
    (gsi
     (case type
       (text `(when (gensym-string-p (value-or-gsi-instance-value ,remote-value-form))
		(reclaim-wide-string ,value)))))))

(defmacro make-remote-value-for-current-system (type value-form)
  `(runtime-current-system-case
     (gsi (make-remote-value gsi ,type ,value-form))
     (ab  (make-remote-value g2  ,type ,value-form))))

(defmacro remote-value-typecode (system remote-value-form)
  (case system
    (gsi `(cond (remote-value-known-typetag)
		((gsi-instance-p ,remote-value-form)
		 (if (not (or write-value-of-gsi-item-p
			      (gsi-item-is-value-p ,remote-value-form)))
		     'item
		     (let ((type (gsi-instance-value-type ,remote-value-form)))
		       (if (or (eq #.gsi-structure-type-tag type)
			       (eq #.gsi-sequence-type-tag type)
			       (element-type-for-gsi-type type) ; array or list
			       (gsi-instance-value ,remote-value-form))
			   type
			   #.gsi-null-type-tag))))
		((null ,remote-value-form)
		 #.gsi-null-type-tag)
		((symbolp ,remote-value-form)
		 #.gsi-symbol-type-tag)
		((fixnump ,remote-value-form)
		 #.gsi-integer-type-tag)
		((long-p ,remote-value-form)
		 #.gsi-long-type-tag) ;added by SoftServe
		((managed-float-p ,remote-value-form)
		 #.gsi-64bit-float-type-tag)
		((binary-wide-string-p ,remote-value-form)
		 #.gsi-unsigned-short-vector-type-tag)
		((or (text-string-p ,remote-value-form)
		     (gensym-string-p ,remote-value-form))
		 #.gsi-string-type-tag)
		((consp ,remote-value-form)
		 (let ((cdr (cdr-of-cons ,remote-value-form)))
		   (cond ((eq cdr 'truth-value)
			  #.gsi-logical-type-tag)
			 (t
			  #.gsi-null-type-tag))))
		(t
		 #.gsi-null-type-tag)))
    (g2  `(cond (remote-value-known-typetag
		 (fixnum-case remote-value-known-typetag
		   (#.gsi-null-type-tag 'null)
		   (#.gsi-integer-type-tag 'integer)
		   (#.gsi-long-type-tag 'long) ;added by SoftServe           
		   (#.gsi-logical-type-tag 'truth-value)
		   (#.gsi-64bit-float-type-tag 'float)
		   (#.gsi-string-type-tag 'text)
		   (#.gsi-unsigned-short-vector-type-tag 'unsigned-short-vector)))
		(remote-value-is-binary-p
		 'unsigned-short-vector)
		((null ,remote-value-form)
		 'null)
		((evaluation-integer-p ,remote-value-form)
		 'integer)
                ((evaluation-long-p ,remote-value-form)
                 'long) ;added by SoftServe
		((consp ,remote-value-form)
		 (let ((cdr (cdr-of-cons ,remote-value-form)))
		   (cond ((eq cdr (evaluation-value-cdr-marker truth-value))
			  'truth-value)
			 ((eq cdr (evaluation-value-cdr-marker sequence))
			  'sequence)
			 ((eq cdr (evaluation-value-cdr-marker structure))
			  'structure)
			 ((eq cdr (evaluation-value-cdr-marker unsigned-vector-16))
			  'unsigned-short-vector)
			 (t
			  #+development
			  (error "Unrecognized arg to remote-value-typecode ~S" ,remote-value-form)
			  'null))))
		((evaluation-float-p ,remote-value-form)
		 'float)
		((evaluation-symbol-p ,remote-value-form)
		 'symbol)
		((binary-wide-string-p ,remote-value-form)
		 'unsigned-short-vector)
		((evaluation-text-p ,remote-value-form)
		 'text)
		((frame-or-deleted-frame-p ,remote-value-form)
		 'item) ; handling of deleted frames is done by the item icp type
		((class-description-p ,remote-value-form)
		 'item)
		(t
		 #+development
		 (error "Unrecognized arg to remote-value-typecode ~S" ,remote-value-form)
		 'null)))))

(defmacro remote-value-typep (system type remote-value-typecode-form)
  (case system
    (gsi
     (case type
       (null        `(eql ,remote-value-typecode-form #.gsi-null-type-tag))
       (truth-value `(eql ,remote-value-typecode-form #.gsi-logical-type-tag))
       (integer     `(eql ,remote-value-typecode-form #.gsi-integer-type-tag))
       (long       `(eql ,remote-value-typecode-form #.gsi-long-type-tag)) ;added by SoftServe   
       (float       `(eql ,remote-value-typecode-form #.gsi-64bit-float-type-tag))
       (symbol      `(eql ,remote-value-typecode-form #.gsi-symbol-type-tag))
       (text        `(eql ,remote-value-typecode-form #.gsi-string-type-tag))
       (unsigned-short-vector
	            `(eql ,remote-value-typecode-form #.gsi-unsigned-short-vector-type-tag))
       (handle      `(eql ,remote-value-typecode-form #.gsi-item-handle-type-tag))
       (structure   `(eql ,remote-value-typecode-form #.gsi-structure-type-tag))
       (sequence    `(eql ,remote-value-typecode-form #.gsi-sequence-type-tag))
       (item        `(eql ,remote-value-typecode-form 'item))
       ((t)         `t)))      
    (g2
     (if (eq type 't)
	  `t
	  `(eql ,remote-value-typecode-form ',type)))))

(defmacro remote-value-typecase (system value remote-value-form &body clauses)
  (let ((result (make-symbol "RESULT")))
    `(let ((typecode (remote-value-typecode ,system ,remote-value-form)))
       (cond ,@(loop for clause in clauses
		     for key = (car clause)
		     for forms = (cdr clause)
		     collect (if (or (eq key 't) (eq key 'otherwise))
				 `(t ,@forms)
				 `((remote-value-typep ,system ,key typecode)
				   (let ((,value (remote-value-value ,system ,key ,remote-value-form)))
				     ,value
				     (let ((,result (progn ,@forms)))
				       (remote-value-reclaim-converted-value ,system ,key ,remote-value-form ,value)
				       ,result)))))))))

(defmacro remote-value-for-current-system-typecase (value remote-value-form &body clauses)
  `(runtime-current-system-case
     (gsi (remote-value-typecase gsi ,value ,remote-value-form ,@clauses))
     (ab  (remote-value-typecase g2  ,value ,remote-value-form ,@clauses))))

(defmacro remote-value-typecode-for-current-system (remote-value-form)
  `(runtime-current-system-case
     (gsi (remote-value-typecode gsi ,remote-value-form))
     (ab  (remote-value-typecode g2  ,remote-value-form))))

(def-system-variable remote-value-known-typetag RPC-COMMON1 nil)

(defmacro write-optional-remote-value-typetag (tag)
  `(with-bifurcated-version-for-output (supports-optional-remote-value-tags-icp-version)
     (write-icp-byte ,tag)
     (unless remote-value-known-typetag
       (write-icp-byte ,tag))))

(defmacro read-optional-remote-value-typetag ()
  `(with-bifurcated-version-for-input (supports-optional-remote-value-tags-icp-version)
     (read-icp-byte)
     (or remote-value-known-typetag
	 (read-icp-byte))))

(defmacro peek-optional-remote-value-typetag ()
  `(with-bifurcated-version-for-input (supports-optional-remote-value-tags-icp-version)
     (peek-icp-byte)
     (or remote-value-known-typetag
	 (peek-icp-byte))))

) ;; end of eval-when

(defun-simple-resumable-icp-function write-icp-remote-value-1 (remote-value-1)
  (remote-value-for-current-system-typecase value remote-value-1
    (null        (write-optional-remote-value-typetag #.gsi-null-type-tag))
    (integer     (write-optional-remote-value-typetag #.gsi-integer-type-tag)
	         (write-icp-integer value))
    (long        (with-appropriate-version (native-long-icp-version)
		   (write-optional-remote-value-typetag #.gsi-long-type-tag)
		   (write-icp-managed-long value)))
    (truth-value (write-optional-remote-value-typetag #.gsi-logical-type-tag)
		 (write-icp-integer value))
    (float       (with-bifurcated-version-for-output (double-float-icp-version)
		   (progn
		     (write-icp-byte #.gsi-float-type-tag)
		     (write-icp-float value))
		   (progn
		     (write-optional-remote-value-typetag #.gsi-64bit-float-type-tag)
		     (write-icp-managed-double-float value))))
    (symbol      (write-icp-symbol-as-value-type value))
    (text        (write-optional-remote-value-typetag #.gsi-string-type-tag)
		 (write-icp-text-string value))
    (unsigned-short-vector
                 (with-bifurcated-version-for-output (unsigned-short-vector-icp-version)
		   (progn
		     (write-optional-remote-value-typetag #.gsi-string-type-tag)
		     (write-icp-text-string value))
		   (progn
		     (write-optional-remote-value-typetag #.gsi-unsigned-short-vector-type-tag)
		     (write-icp-wide-string value))))
    (handle      (write-optional-remote-value-typetag #.rpc-object-handle-type-tag)
		 (write-icp-fixnum value))
    (structure   (with-bifurcated-version-for-output (evaluation-sequences-and-structures-icp-version)
		   (write-icp-byte #.gsi-null-type-tag)
		   (progn
		     (write-optional-remote-value-typetag #.gsi-structure-type-tag)
		     (write-icp-evaluation-structure value))))
    (sequence    (with-bifurcated-version-for-output (evaluation-sequences-and-structures-icp-version)
		   (write-icp-byte #.gsi-null-type-tag)
		   (write-icp-evaluation-sequence value)))
    (item        (with-bifurcated-version-for-output (remote-value-supports-item-icp-version)
		   (write-icp-byte #.gsi-null-type-tag)
		   (write-icp-item value)))
    (t           #+development
		 (cerror "Transmit Null GSI value type"
			 "Unexpected value type for ~a in WRITE-ICP-REMOTE-VALUE"
			 remote-value-1)
		 (write-icp-byte #.gsi-null-type-tag))))

(defun-simple-resumable-icp-function read-icp-remote-value-1 ()
  (let* ((value-p nil)
	 (value (fixnum-case (peek-optional-remote-value-typetag)
		  ((#.rpc-handle-for-sending-side-object-type-tag
		      #.rpc-handle-for-receiving-side-object-handle-type-tag
		      #.rpc-handle-for-temporary-object-handle-type-tag
		      #.rpc-handle-for-new-sending-side-object-type-tag
		      #.rpc-existing-item-copy
		      #.rpc-new-item-copy
		      #.rpc-new-item-copy-with-handle
		      #.rpc-new-item-copy-with-reference)
		   (setq value-p t)
		   (read-icp-item))
		  ((#.icp-standard-index-space-type-tag
		      #.icp-temporary-index-space-type-tag
		      #.icp-new-symbol-type-tag
		      #.icp-new-symbol-expanding-index-space-type-tag
		      #.icp-new-keyword-symbol-type-tag
		      #.gsi-symbol-type-tag)
		   (let ((symbol (read-icp-symbol-as-value-type)))
		     (make-remote-value-for-current-system symbol symbol)))
		  ((#.gsi-sequence-type-tag #.gsi-typed-sequence-type-tag)
		   (read-icp-evaluation-sequence)))))
    (if (or value value-p)
	value
	(let ((type-tag (read-optional-remote-value-typetag)))
	  (fixnum-case type-tag
	    (#.gsi-null-type-tag
	       (make-remote-value-for-current-system null nil))
	    (#.gsi-logical-type-tag
	       (make-remote-value-for-current-system truth-value (read-icp-integer)))
	    (#.gsi-integer-type-tag
	       (make-remote-value-for-current-system integer (read-icp-fixnum)))
	    (#.gsi-long-type-tag
	       (make-remote-value-for-current-system long (read-icp-managed-long)))
	    (#.gsi-64bit-float-type-tag
	       (make-remote-value-for-current-system float (read-icp-managed-double-float)))
	    (#.gsi-float-type-tag
	       (make-remote-value-for-current-system float (read-icp-float)))
	    (#.gsi-string-type-tag
	       (make-remote-value-for-current-system text (read-icp-text-string)))
	    (#.gsi-gensym-string-type-tag
	       (make-remote-value-for-current-system
		 text
		 (gensym-string-to-wide-string-for-icp (read-icp-gensym-string))))
	    (#.gsi-wide-string-type-tag
	       (make-remote-value-for-current-system text (read-icp-wide-string)))
	    (#.gsi-unsigned-short-vector-type-tag
	       (make-remote-value-for-current-system unsigned-short-vector (read-icp-wide-string)))
	    (#.gsi-structure-type-tag
	       (read-icp-evaluation-structure))
	    (#.rpc-object-handle-type-tag
	       (make-remote-value-for-current-system handle (read-icp-fixnum)))
	    (otherwise
	      (icp-error "Unknown type tag ~a in READ-ICP-REMOTE-VALUE" type-tag)))))))

(defvar item-copy-index-space 'unbound)

(defmacro with-item-index-space (args &body body)
  (declare (ignore args))
  `(if (eq 'unbound item-copy-index-space)
       (let ((item-copy-index-space nil)
	     (current-computation-flags current-computation-flags))
	 (current-system-case
	   (ab (setf (role-serve-inactive-objects?)
		     (icp-socket-runs-while-inactive current-icp-socket))))
	 (prog1 (progn ,@body)
	   (when item-copy-index-space
	     (reclaim-index-space item-copy-index-space))))
       (progn ,@body)))

(def-icp-value-writer remote-value
  (with-item-index-space ()
    (write-icp-remote-value-1 remote-value)))

(def-icp-value-reader remote-value
  (with-item-index-space ()
    (read-icp-remote-value-1)))

(def-icp-value-reader gsi-permanent-remote-value
  (runtime-current-system-case
    (gsi
      (let ((gsi-reclaim-list? nil))
	(prog1 (read-icp-remote-value)
	  (reclaim-gsi-list gsi-reclaim-list?))))
    (t
      (read-icp-remote-value))))

(def-icp-value-writer gsi-permanent-remote-value
  (write-icp-remote-value gsi-permanent-remote-value))

(defun-void reclaim-remote-value (remote-value)
  (runtime-current-system-case
    ((gsi telewindows)
     (when (eq 'gsi (default-owner-for-gsi-objects))
       (reclaim-gsi-instance remote-value 'gsi)))
    (ab
      (reclaim-if-evaluation-value remote-value))))

(defmacro read-icp-terminated-list (type conser)
  `(loop until (when (eql (peek-icp-byte) #.gsi-end-type-tag)
		 (read-icp-byte))
	 collect (,(intern (format nil "READ-ICP-~A" type)))
	   using ,conser))

(defmacro read-icp-terminated-list-of-pairs (type conser)
  `(loop until (when (eql (peek-icp-byte) #.gsi-end-type-tag)
		 (read-icp-byte))
	 collect (,(intern (format nil "READ-ICP-~A" type)))
	   using ,conser
	 collect (,(intern (format nil "READ-ICP-~A" type)))
	   using ,conser))

(defmacro read-icp-evaluation-sequence-body (system &optional array-for-remote-value array-type
						    element-type)
  (let ((conser (ecase system
		  (g2  'eval-cons)
		  (gsi 'gsi-cons))))
    `(let* ((typetag (case (read-icp-byte)
		       (#.gsi-typed-sequence-type-tag (read-icp-byte))
		       (#.gsi-sequence-type-tag       #.gsi-value-type-tag)))
	    (length (read-icp-fixnum))
	    ,@(when array-for-remote-value `((element-type ,element-type)))
	    (remote-value-known-typetag
	      (cond ((=f typetag #.gsi-value-type-tag) nil)
		    (t typetag))))
       ,(if array-for-remote-value
	    `(let ((array (gsi-make-appropriate-array
			    ,array-type length ,array-for-remote-value)))
	       (setf (gsi-instance-value ,array-for-remote-value) array)
	       (setf (gsi-element-count ,array-for-remote-value) length)
	       (if element-type
		   (loop with gsi-remote-value-creates-instance-p = nil
			 for index from 0 below length
			 for value = (read-icp-remote-value)
			 do (case element-type
			      (integer
			       (setf (gsi-typed-array-ref integer array index) value))
			      (truth-value
			       (setf (gsi-typed-array-ref logical array index) value))
			      (float
			       (setf (gsi-typed-array-ref 64bit-float array index) value)
			       (reclaim-managed-float value))
			      (symbol
			       (setf (gsi-typed-array-ref symbol array index) value))
			      (text
			       (setf (gsi-typed-array-ref string array index) value))))
		   (loop for i from 0 below length
			 do (setf (gsi-typed-array-ref gsi-item array i)
				  (read-icp-remote-value)))))
	    `(loop for i from 0 below length
		   for value = (read-icp-remote-value)
		   for converted-value
		       = ,(if (eq system 'g2)
			      `(if (evaluation-unsigned-vector-16-p value)
				   (evaluation-unsigned-vector-16-value value)
				   value)
			      `value)
		   collect converted-value using ,conser)))))

;see names-as-symbol-or-gsi-list-of-symbols
(def-icp-value-reader evaluation-sequence
  (runtime-current-system-case
    (ab
     (allocate-evaluation-sequence
       (read-icp-evaluation-sequence-body g2)))
    (gsi
     (make-gsi-sequence
       (read-icp-evaluation-sequence-body gsi)))))



;;; `upgrade-type-for-sequence-element-internal' and `upgrade-type-for-sequence-element'
;;; These are really "knowledgeable" macros that I don't think belong at top
;;; level.  I'd much rather, if they need to exist, that they be macrolets
;;; inside of their only caller, write-icp-evaluation-sequence-body.  However,
;;; the resumable ICP stuff (check-resumable-icp-form-p) "warns" when any of the
;;; following forms are used: (macrolet symbol-macrolet progv catch throw
;;; unwind-protect flet labels).  We really don't know enough about resumable
;;; ICP to write such risky code, so these macros remain.  - jv, 3/21/02

;; Changing upgrade-type-for-sequence-element-internal to take additional
;; arguments system, element-var, and internal-value, because that naked
;; (loop-finish) there jumps over the would-be reclaimer inside write-icp-
;; evaluation-sequence-body.  Ugh.  And, of course, this macro knows that.
;; From the present implementation of remote-value-reclaim-converted-value,
;; this will only make a difference if the type is 'text (and the system
;; is 'gsi)  -- jv, 5/2/02

(defmacro upgrade-type-for-sequence-element-internal
    (type-var quoted-type system element-var internal-value)
  `(cond
     ((null ,type-var)
      (setq ,type-var ,quoted-type))
     ((not (eq ,type-var ,quoted-type))
      (setq ,type-var 't)
      (remote-value-reclaim-converted-value ,system ,(eval quoted-type)
					    ,element-var ,internal-value)
      (loop-finish))))

(defmacro upgrade-type-for-sequence-element (system type-var element-var)
  (let ((internal-value-var (make-symbol "INTERNAL-VALUE")))
    `(remote-value-typecase ,system ,internal-value-var ,element-var
       ,@(loop for type-symbol in '(null integer truth-value float text unsigned-short-vector)
	       collect `(,type-symbol (upgrade-type-for-sequence-element-internal
					,type-var ',type-symbol ,system ,element-var ,internal-value-var)))
       (t (setq ,type-var 't) (loop-finish)))))

(defmacro write-icp-evaluation-sequence-body (system length-form value-var value-iterator
						     &optional known-type)
  `(let* ((known-type ,known-type)
	  (typetag
	   (let ((type known-type))
	     ,(unless known-type
		(subst `(upgrade-type-for-sequence-element ,system type ,value-var)
		       '.use-next-value.
		       value-iterator))
	     (case type
	       (null        #.gsi-null-type-tag)
	       (integer     #.gsi-integer-type-tag)
	       (long        #.gsi-long-type-tag)
	       (truth-value #.gsi-logical-type-tag)
	       (float       #.gsi-64bit-float-type-tag)
	       (text        #.gsi-string-type-tag)
	       (unsigned-short-vector #.gsi-unsigned-short-vector-type-tag)
	       (t           nil))))
	  (remote-value-known-typetag typetag))
     (cond (typetag
	    (write-icp-byte #.gsi-typed-sequence-type-tag)
	    (write-icp-byte typetag))
	   (t
	    (write-icp-byte #.gsi-sequence-type-tag)))
     (write-icp-fixnum ,length-form)
     ,(subst `(write-icp-remote-value ,value-var)
	     '.use-next-value.
	     value-iterator)))

(def-icp-value-writer evaluation-sequence
  (runtime-current-system-case
    (ab
     (write-icp-evaluation-sequence-body
       g2
       (evaluation-sequence-length evaluation-sequence)
       value
       (loop for value being each evaluation-sequence-element of evaluation-sequence
	     do .use-next-value.)))
    (gsi
      (let ((length (gsi-element-count evaluation-sequence)))
	(write-icp-evaluation-sequence-body
	  gsi
	  length
	  value
	  (let ((gsi-items (gsi-instance-value evaluation-sequence)))
	    (when gsi-items
	      (loop for i from 0 below length
		    for j from gsi-magic-offset
		    for value = (gsi-managed-svref gsi-items j)
		    do .use-next-value.))))))))

(defun-simple-resumable-icp-function read-evaluation-structure-from-list (so-far list)
  (runtime-current-system-case
    (ab
     (allocate-evaluation-structure
       (let ((plist (loop for attribute in list
			  for value = (read-icp-remote-value)
			  for converted-value
			      = (if (evaluation-unsigned-vector-16-p value)
				    (evaluation-unsigned-vector-16-value value)
				    value)
			  for converted-attribute =
			  (progn
			    #+development
			    (when (and (consp attribute)
				       (not (memq (car attribute) '(attribute class-qualified-name)))
				       (not (= (length attribute) 3)))
			      (cerror "Continue anyway"
				      "Attribute name ~S invalid" attribute))
			    (if (atom attribute)
				attribute
				(if (null (second attribute)) 
				    (third attribute)  ; no class qualifier, just use slot-name
				    ;;otherwise create fully qualified symbol
				    (make-unique-slot-name-symbol (second attribute) (third attribute)))))
			  collect converted-attribute using eval-cons
			  collect converted-value using eval-cons)))
	 (if so-far (nconc so-far plist) plist))))
    (gsi
      (make-gsi-structure
	(let ((plist (loop for attribute in list
			   collect attribute using gsi-cons
			   collect (read-icp-remote-value) using gsi-cons)))
	  (if so-far (nconc so-far plist) plist))))))
;; Note: Read-evaluation-structure-from-list is schizophrenic.  If we are
;; passing structures G2-G2, then we receive class qualified names as class
;; qualified symbols :|class-name::slot-name|.  If we are passing structures
;; GSI-G2, then we receive class qualified names as (ATTRIBUTE CLASS-NAME
;; SLOT-NAME).  If we are passing classes, then class qualified names are passed
;; as (CLASS-QUALIFIED-NAME CLASS-NAMES SLOT-NAME), and a completely different
;; set of code handles this.  So it's a little bit flaky to turn the GSI format
;; into a symbol, but that makes it match the G2 behavior, without rewriting the
;; entire wad.  The only strange bit is that if we are passing classes, and we
;; get an error of class not found, there is some code in the error handler
;; handle-missing-class-in-rpc (which I have been unable to exercise) which
;; expects to see a cons format attribute name, and which first calls this
;; function, so it won't get a cons format attribute name.  Experiments in lisp
;; suggest that it would however be happy with a fully qualified symbol. --yduJ 4/22/02

(def-icp-value-reader evaluation-structure
  (read-evaluation-structure-from-list
    nil
    (interned-list--list
      (read-icp-interned-list-as-value-type))))

(defun-simple intern-attributes-of-structure (structure)
  (current-system-case
    (ab
     (interning-list 
       (loop for (key . val) being each evaluation-structure-pair of structure
	     do (intern-next-element key))))
    (t
      structure
      nil)))

(defun-simple intern-attributes-of-gsi-structure (gsi-item)
  (runtime-current-system-case
    (gsi
      (interning-list
	(let* ((attribute-count (gsi-attribute-count gsi-item))
	       (attribute-count-with-offset (+f attribute-count gsi-magic-offset))
	       (attributes (gsi-attributes gsi-item)))
	  (when (<f 0 attribute-count)
	    (loop for i from gsi-magic-offset below attribute-count-with-offset
		  for attribute = (gsi-managed-svref attributes i)
		  for attribute-name = (gsi-attribute-spec attribute)
		  for simplified-attribute-name
		      = (if (and (consp attribute-name)
				 (eq (car attribute-name) 'attribute)
				 (null (second attribute-name)))
			    (third attribute-name)
			    attribute-name)
		  unless (gsi-attribute-is-transient-p attribute)
		    do (intern-next-element simplified-attribute-name))))))
    (t
      gsi-item
      nil)))

(def-icp-value-writer evaluation-structure
  (runtime-current-system-case
    (ab
     (write-icp-interned-list-as-value-type
       (intern-attributes-of-structure evaluation-structure))
     (loop for (nil . attribute-value)
	       being each evaluation-structure-pair of evaluation-structure
	   do (write-icp-remote-value attribute-value)))
    (gsi
      (write-icp-interned-list-as-value-type
	(intern-attributes-of-gsi-structure evaluation-structure))
      (let* ((gsi-item evaluation-structure)
	     (attribute-count (gsi-attribute-count gsi-item))
	     (attribute-count-with-offset (+f attribute-count gsi-magic-offset))
	     (attributes (gsi-attributes gsi-item)))
	(when (<f 0 attribute-count)
	  (loop for i from gsi-magic-offset below attribute-count-with-offset
		for attribute = (gsi-managed-svref attributes i)
		for attribute-value = (gsi-attribute-instance attribute)
		unless (gsi-attribute-is-transient-p attribute)
		  do (write-icp-remote-value attribute-value)))))))

#| ; not called
(defun-simple intern-property-names-of-plist (plist)
  (interning-list 
    (loop for (key val) on plist by 'cddr
	  do (intern-next-element key))))

(def-icp-value-reader evaluation-structure-plist
  (let ((list (interned-list--list
		(read-icp-interned-list-as-value-type))))
    (runtime-current-system-case
      (ab
	(loop for attribute in list
	      collect attribute using eval-cons
	      collect (read-icp-remote-value) using eval-cons))
      (gsi
	(loop for attribute in list
	      collect attribute using gsi-cons
	      collect (read-icp-remote-value) using gsi-cons)))))

(def-icp-value-writer evaluation-structure-plist
  (write-icp-interned-list-as-value-type
    (intern-property-names-of-plist evaluation-structure-plist))
  (loop for (key value) on evaluation-structure-plist by 'cddr
	do (write-icp-remote-value value)))
|#

(defmacro converting-gsi-value-to-value ((value-var &optional initform?) &body body)
  (unless (symbolp value-var)
    (error
      "CONVERTING-GSI-VALUE-TO-VALUE: expected a symbol, not ~S" value-var))
  (avoiding-variable-capture (&aux copy-string-value-p)
    `(let* (,@(if initform?
		  `((,value-var ,initform?))
		  nil)
	    (,copy-string-value-p (gensym-string-p ,value-var)))
       (when ,copy-string-value-p
	 (setq ,value-var
	       (runtime-current-system-case
		 (gsi
		    (gensym-string-to-wide-string-for-gsi ,value-var))
		 (t (gensym-string-to-wide-string ,value-var)))))
       ,@body
       (when ,copy-string-value-p
	 (reclaim-wide-string ,value-var)))))


;; RPC-asynchronous-abort

(def-icp-message-type rpc-asynchronous-abort
                      ((remote-procedure-identifier procedure-to-abort?))
  (when procedure-to-abort?
    (runtime-current-system-case
      (ab
	(let ((state (remote-procedure-identifier-state procedure-to-abort?)))
	  (case state
	    (outstanding
	     (setf (remote-procedure-identifier-state procedure-to-abort?)
		   'async-abort)
	     (receive-remote-procedure-asynchronous-abort
	       current-icp-socket procedure-to-abort?)))
	  (case state
	    ((outstanding returned)
	     (writing-icp-message-group ((icp-output-port current-icp-socket))
	       (send-icp-rpc-acknowledge-abort
		 (remote-procedure-identifier-tag procedure-to-abort?)))))))
      (gsi
	(case (remote-procedure-identifier-state procedure-to-abort?)
	  (outstanding
	   (setf (remote-procedure-identifier-state procedure-to-abort?)
		 'async-abort)
	   (let* ((current-remote-procedure-identifier procedure-to-abort?)
		  (local-function (remote-procedure-identifier-caller procedure-to-abort?)))
	     (gsi-warning 'rpc-asynchronous-abort gsi-rpc-async-abort
			  (if local-function
			      (gsi-function-name-in-g2 local-function)
			      "<an incompletely received call>"))
	     ;; The user's return or error-return is ignored, and replaced with an
	     ;; rpc-acknowledge-abort
	     ))
	  (returned
	   (writing-icp-message-group ((icp-output-port current-icp-socket))
	     (send-icp-rpc-acknowledge-abort
	       (remote-procedure-identifier-tag procedure-to-abort?)))))))))


;; RPC-acknowledge-abort

(def-icp-message-type rpc-acknowledge-abort
                      ((unsigned-integer procedure-index))
  (let ((identifier?
          (lookup-remote-procedure-identifier-from-index procedure-index)))
    (if identifier?
	(if (remote-procedure-identifier-awaiting-acknowledge-abort identifier?)
	    (reclaim-outgoing-remote-procedure-identifier-and-index identifier?)
	    (rpc-acknowledge-abort-error identifier?))
	(rpc-acknowledge-abort-error procedure-index))
    nil))

(defun-void rpc-acknowledge-abort-error (identifier-or-index)
  (let ((description (icp-socket-description current-icp-socket)))
    (notify-user-at-console
      "~%Error in rpc-acknowledge-abort, for ~NF ~A~
       ~%~A: ~A~%"
      (enclosing-interface-frame? current-icp-socket)
      description
      (if (fixnump identifier-or-index)
	  "Received a rpc-acknowledge-abort message with no remote-procedure-identifier"
	  "Received an unexpected rpc-acknowledge-abort message")
      (if (fixnump identifier-or-index)
	  identifier-or-index
	  (remote-procedure-identifier-name-symbol identifier-or-index)))
    (reclaim-text-string description)))






;;;; Remote Procedure Identifiers

;;; There is a need in remote procedure calls to establish a numeric identifier
;;; for a call which is in the process of being executed.  This number should be
;;; generated within a source of an RPC, and used by the target to identify the
;;; particular call back to the original system.  A G2 should maintain a single
;;; data base of identifiers, whether or not the remote calls are targeted
;;; towards the same system, and target systems should be careful not to confuse
;;; equal identifiers which have arrived from different systems.  Remote
;;; procedure identifiers are ICP corresponding objects, so the remote system
;;; should use the structure itself as its identity, and then only send back the
;;; integer when identifying error and return-value messages.

;;; The parameter `maximum-concurrent-remote-procedure-calls' contains the
;;; number of remote-procedure-calls which may be onging out of a single source at
;;; one time.

;;; The value 4096 is an arbitrarily picked though seemingly large number.
;;; (Peng thinks that we got going on base two numbers in machines because of
;;; people's tendency to see the world in terms of absolutes; good/bad, yes/no,
;;; right/wrong.  I wonder what might have happened if the first transistor
;;; invented had 3 stable states.  Control Data's first supercomputers had 60
;;; bit words.  It's been rumored this size was picked because one of the system
;;; architects liked chess and it took exactly 60 bits to store one chess board
;;; state.  Managed arrays use 256 element simple-vector blocks, so base two
;;; numbers help.  -jra 3/14/90)

(defparameter maximum-concurrent-remote-procedure-calls 4096)




;;; The function `make-initial-remote-procedure-identifier-array' returns a
;;; managed array to hold remote-procedure-identifier objects.

(defun make-initial-remote-procedure-identifier-array ()
  (let ((map (make-index-space 'remote-procedure-identifier-map nil)))
    (enlarge-index-space map 20)
    (assign-index-in-index-space map)
    map))




;;; The system variable `remote-procedure-call-identifier-array' contains an
;;; array which is used to find a remote-procedure-identifier structure given an
;;; identifier number.

(def-system-variable remote-procedure-identifier-array
    RPC-COMMON1
  (:funcall make-initial-remote-procedure-identifier-array))





;;; The function `make-remote-procedure-identifier-if-possible' takes no
;;; arguments and returns either a new remote procedure identifier, or NIL if
;;; there are no available remote procedure identifier indices.

(defun-simple make-outgoing-remote-procedure-identifier-with-info
    (return-included-attributes-spec
      return-excluded-attributes-spec
      return-included-system-attributes-spec
      return-include-all-system-attributes-spec
      return-include-all-system-attributes-except-spec
      return-kind-spec
      return-varargs-p)
  (let* ((map remote-procedure-identifier-array)
	 (index (assign-index-in-index-space map))
	 (identifier
	   (make-outgoing-remote-procedure-identifier
	     index
	     (make-remote-procedure-item-passing-info-from-specs
	       nil ; not interned
	       return-included-attributes-spec
	       return-excluded-attributes-spec
	       return-included-system-attributes-spec
	       return-include-all-system-attributes-spec
	       return-include-all-system-attributes-except-spec
	       return-kind-spec
	       return-varargs-p))))
    (store-object-in-index-space map index identifier)
    identifier))


;;; The function `reclaim-remote-procedure-identifier-and-index' takes a
;;; remote-procedure-identifier structure.  It will reclaim the structure and
;;; index.

(defun-simple reclaim-outgoing-remote-procedure-identifier-and-index
              (remote-procedure-identifier)
  (let ((map remote-procedure-identifier-array)
	(index (remote-procedure-identifier-tag remote-procedure-identifier)))
    (reclaim-icp-object-map-for-remote-procedure-identifier remote-procedure-identifier)
    (store-object-in-index-space map index nil)
    (deassign-index-in-index-space index map)
    (reclaim-outgoing-remote-procedure-identifier remote-procedure-identifier)
    nil))






;;; The simple function `lookup-remote-procedure-identifier-from-index' takes an
;;; unsigned-integer and returns the remote-procedure-identifier structure for
;;; that index, or NIL.

(defun-simple lookup-remote-procedure-identifier-from-index (procedure-index)
  (get-object-from-index-space-if-any
    remote-procedure-identifier-array
    procedure-index))




;;; The simple function `reclaim-remote-procedure-identifier-from-index' takes
;;; an unsigned-integer which is a remote procedure identifier index and
;;; reclaims that index number and the remote-procedure-identifier structure
;;; which contains that number.  If it has already been reclaimed, do nothing.

(defun-simple reclaim-outgoing-remote-procedure-identifier-from-index (procedure-index)
  (let ((identifier?
          (lookup-remote-procedure-identifier-from-index procedure-index)))
    (when identifier?
      (reclaim-outgoing-remote-procedure-identifier-and-index identifier?))
    nil))



(defun-simple gsi-define-new-remote-procedure (local-handle)
  (setf (gsi-remote-procedure-name-structure local-handle)
        (make-remote-procedure-name (procedure-name-in-g2 local-handle))))




(declare-forward-reference write-icp-item-reference-1-function function)
(declare-forward-reference read-icp-item-reference function)


(def-icp-value-writer index-space
  (let ((last-index (last-assigned-index index-space)))
    (write-icp-unsigned-integer (1+f last-index))
    (loop for i from 0 to last-index
	  for thing = (get-object-from-index-space index-space i)
	  do
      (cond ((symbolp thing)
	     (write-icp-symbol-as-value-type thing))
	    ((interned-list-p thing)
	     (write-icp-byte #.icp-tree-interned-list-type-tag)
	     (write-icp-interned-list-as-value-type thing))
	    ((remote-procedure-name-p thing)
	     (let ((index (get-icp-object-index-for-remote-procedure-name thing current-icp-port)))
	       (cond (index
		      (write-icp-byte #.icp-standard-index-space-type-tag)
		      (write-icp-corresponding-object-index index))
		     (t
		      (write-icp-byte #.index-space-remote-procedure-name)
		      (with-disabled-write-icp-suspension
		        (write-icp-corresponding-object-index
			  (establish-new-object-index-for-remote-procedure-name
			    thing current-icp-port nil))
			(write-icp-symbol-as-value-type
			  (remote-procedure-name-symbol thing)))))))
	    ((current-system-case
	       (gsi (and (gsi-instance-p thing)
			 (gsi-item-reference-flag-value thing)))
	       (ab  (or (class-description-p thing)
			(framep thing))))
	     (write-icp-item-reference-1-function thing))
	    (t
	     (write-icp-byte #.gsi-null-type-tag))))))

(def-icp-value-reader index-space
  (let* ((size (read-icp-unsigned-integer))
	 (last-index (1-f size))
	 (index-space (make-index-space 'temporary-icp-object-index-space nil)))
    (setf (last-assigned-index index-space) last-index)
    (loop for i from 0 to last-index
	  for thing = (fixnum-case (peek-icp-byte)
			((#.icp-standard-index-space-type-tag
			  #.icp-new-symbol-type-tag
			  #.icp-new-symbol-expanding-index-space-type-tag
			  #.icp-new-keyword-symbol-type-tag
			  #.gsi-symbol-type-tag)
			 (read-icp-symbol-as-value-type))
			((#.index-space-remote-procedure-name)
			 (read-icp-byte)
			 (store-corresponding-icp-object
			   (read-icp-corresponding-object-index)
			   (make-remote-procedure-name
			     (read-icp-symbol-as-value-type))))
			((#.icp-tree-interned-list-type-tag)
			 (read-icp-byte)
			 (read-icp-interned-list-as-value-type))
			((#.rpc-handle-for-sending-side-object-type-tag
			  #.rpc-handle-for-receiving-side-object-handle-type-tag
			  #.rpc-handle-for-new-sending-side-object-type-tag)
			 (read-icp-item-reference)))
	  do
      (setf (get-object-from-index-space index-space i) thing))
    index-space))

(def-icp-message-type define-temporary-index-space (index-space)
  (setf (temporary-icp-object-index-space current-icp-port) index-space)
  (setq current-temporary-icp-object-index-space index-space))

(def-icp-message-type release-temporary-index-space ()
  (reclaim-if-index-space (temporary-icp-object-index-space current-icp-port))
  (setf (temporary-icp-object-index-space current-icp-port) nil)
  (setq current-temporary-icp-object-index-space nil))



